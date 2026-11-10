#include "../renderer/talon_render_state.h"
#include "subsystems/renderer/stock_render_options.h"
#include "world_model_renderer.h"
#include "world_renderer.h"
#include "world_pvs.h"
#include "world_lightmap_system.h"
#include "world_lighting.h"
#include "world_static_geometry.h"
#include "world_material_system.h"
#include "material_authoring.h"
#include "world_surface_fx.h"
#include "deluxe_lightmap_baker.h"
#include "../textures/texture_manager.h"
#include "../../gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "subsystems/renderer/fog_state.h"
#include "../../shaders/shader.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils/log.h"
#include <cstring>

namespace
{
    constexpr size_t WM_STREAM_FRAMES = 3;
    constexpr size_t WM_STATE_MIN_SEGMENT_BYTES = 1024u * 1024u;
    constexpr size_t WM_COMMAND_MIN_SEGMENT_BYTES = 256u * 1024u;
    constexpr size_t WM_COLOR_MIN_SEGMENT_BYTES = 2u * 1024u * 1024u;
    constexpr size_t WM_COLOR_MAX_SEGMENT_BYTES = 64u * 1024u * 1024u;
    static size_t AlignUp(size_t v, size_t a) { return a ? ((v + a - 1u) / a) * a : v; }
}

bool WorldModelRenderer::HasPhase(const WorldModelInstanceCompat *wm, WorldModelPhase phase) const
{
    if (!wm || !wm->m_pOriginalBsp)
        return false;

    const WorldBspCompat *bsp = wm->m_pOriginalBsp;
    const bool chroma = (wm->m_Base.m_dwFlags2 & FLAG2_CHROMAKEY) != 0;
    const uint32 instFlags2 = wm->m_Base.m_dwFlags2;
    const bool instAlpha = wm->m_Base.m_nColorA < 255;

    if (!bsp->m_pPolies || !bsp->m_dwPolies)
        return phase == WorldModelPhase::Opaque && !chroma && !instAlpha;

    for (uint32 i = 0; i < bsp->m_dwPolies; ++i)
    {
        const WorldPolyCompat *poly = bsp->m_pPolies[i];
        const SurfaceCompat *sf = poly ? poly->m_pSurface : nullptr;
        if (!sf)
            continue;
        const uint32 flags = sf->m_dwFlags;
        if (flags & (SURF_INVISIBLE | SURF_SKY | SURF_NONEXISTANT))
            continue;

        WorldBlendMode blend = WorldMaterialSystem::Instance().ClassifyBlend(flags);
        if (instFlags2 & (1u << 2))
            blend = WorldBlendMode::Additive;
        else if (instFlags2 & (1u << 3))
            blend = WorldBlendMode::Multiply;
        else if (instAlpha)
            blend = WorldBlendMode::Alpha;

        WorldModelPhase batchPhase = WorldModelPhase::Opaque;
        if (blend != WorldBlendMode::Solid)
            batchPhase = WorldModelPhase::Translucent;
        else if (chroma)
            batchPhase = WorldModelPhase::ChromaKey;

        if (batchPhase == phase)
            return true;
    }
    return false;
}

WorldModelPhase WorldModelRenderer::Classify(const WorldModelInstanceCompat *wm) const
{
    // Preserve the legacy single-phase answer for callers that only need an
    // object-level classification, but derive it from all authored surfaces.
    // A mixed brush can now participate in opaque *and* translucent rendering
    // through HasPhase(), instead of its first surface forcing the entire BSP
    // into one bucket.
    if (HasPhase(wm, WorldModelPhase::Translucent))
        return WorldModelPhase::Translucent;
    if (HasPhase(wm, WorldModelPhase::ChromaKey))
        return WorldModelPhase::ChromaKey;
    return WorldModelPhase::Opaque;
}

namespace
{
    static WorldPVSState &PVSState() { return WorldPVS::Instance().State(); }
    static WorldLightmapSystemState &LightmapState() { return WorldLightmapSystem::Instance().State(); }
    static WorldRendererState &WorldState() { return WorldRenderer::Instance().State(); }
    static WorldStaticGeometryState &StaticState() { return WorldStaticGeometryRenderer::Instance().State(); }
    static GLint U(const char *name)
    {
        auto *shader = WorldRenderer::Instance().State().worldShader;
        return shader ? shader->Uniform(name) : -1;
    }
    static bool IsTerrainBsp(const WorldBspCompat *bsp)
    {
        return bsp && (bsp->m_dwWorldInfoFlags & WIF_TERRAIN) != 0;
    }
    static void EnableWorldBackfaceCulling()
    {
        GLStateFrontFace(GL_CW);
        GLStateCullFace(GL_BACK);
        GLStateEnable(GL_CULL_FACE);
    }
    static void DisableWorldBackfaceCulling() { GLStateDisable(GL_CULL_FACE); }

    struct WmDrawStateGPU
    {
        float world[16];
        float objectColor[4];
        uint32 info[4];
    };
    static_assert(sizeof(WmDrawStateGPU) == 96, "WmDrawStateGPU std430 mismatch");
    struct DrawArraysIndirectCommandGPU
    {
        uint32 count = 0, instanceCount = 1, first = 0, baseInstance = 0;
    };
    static_assert(sizeof(DrawArraysIndirectCommandGPU) == 16, "DrawArraysIndirectCommandGPU mismatch");
    struct WmMdiMaterialKey
    {
        SharedTexture *texture = nullptr;
        SurfaceCompat *animatedSurface = nullptr;
        uint32 fxHash = 0, alphaBits = 0;
        uint8 noLight = 0, extraShade = 0, lightmapGouraud = 0, gouraudNoLightmap = 0, phase = 0, pad = 0;
        bool operator==(const WmMdiMaterialKey &o) const { return texture == o.texture && animatedSurface == o.animatedSurface && fxHash == o.fxHash && alphaBits == o.alphaBits && noLight == o.noLight && extraShade == o.extraShade && lightmapGouraud == o.lightmapGouraud && gouraudNoLightmap == o.gouraudNoLightmap && phase == o.phase; }
    };
    struct WmMdiMaterialKeyHash
    {
        size_t operator()(const WmMdiMaterialKey &k) const { return (reinterpret_cast<size_t>(k.texture) >> 4) ^ (reinterpret_cast<size_t>(k.animatedSurface) >> 5) ^ (size_t(k.fxHash) * 0x85EBCA6Bu) ^ (size_t(k.alphaBits) * 0xC2B2AE35u) ^ (size_t(k.noLight) << 5) ^ (size_t(k.extraShade) << 11) ^ (size_t(k.lightmapGouraud) << 15) ^ (size_t(k.gouraudNoLightmap) << 16) ^ (size_t(k.phase) << 17); }
    };
    struct WmMdiGroup
    {
        WmMdiMaterialKey key{};
        const WorldBatch *material = nullptr;
        float alphaRef = 0.0f;
        uint32 firstCommand = 0, commandCount = 0;
    };

    static void SetIdentityWorldTransform()
    {
        static const float I[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        GLUniform1i(U("uUseWmDrawState"), 0);
        GLUniform1i(U("uUseWorld"), 0);
        GLUniformMatrix4fv(U("uWorld"), 1, GL_FALSE, I);
        GLUniform4f(U("uObjectColor"), 1, 1, 1, 1);
        GLUniform1ui(U("uLegacyDrawFlags"), 0u);
        GLUniform1i(U("uSkyDxt5AlphaOnly"), 0);
        GLUniform1i(U("uSkyHorizonFogGradient"), 0);
        GLUniform1i(U("uSkyClipCameraSpace"), 0);
    }
    static void SetWorldModelTransform(const WorldModelInstanceCompat *wm)
    {
        GLUniform1i(U("uUseWmDrawState"), 0);
        GLUniform1ui(U("uLegacyDrawFlags"), 1u);
        GLUniform1i(U("uUseWorld"), 1);
        GLUniformMatrix4fv(U("uWorld"), 1, GL_TRUE, &wm->m_mTransform.m[0][0]);
        const auto &o = wm->m_Base;
        GLUniform4f(U("uObjectColor"), o.m_nColorR / 255.0f, o.m_nColorG / 255.0f, o.m_nColorB / 255.0f, o.m_nColorA / 255.0f);
    }
    static void BindGpuVertexLight(GLuint ssbo, uint32 vertexBase = 0, uint32 dataBase = 0)
    {
        const bool enabled = ssbo != 0;
        glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 6, enabled ? ssbo : 0);
        GLUniform1i(U("uGpuVertexLight"), enabled ? 1 : 0);
        GLUniform1ui(U("uVertexLightVertexBase"), enabled ? vertexBase : 0u);
        GLUniform1ui(U("uVertexLightDataBase"), enabled ? dataBase : 0u);
    }

    static void BindCpuWorldModelColor(bool enabled)
    {
        auto &st = WorldRenderer::Instance().WorldModels().State();
        const bool active = enabled && st.cpuColorSsbo && st.cpuColorMapped;
        glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 9, active ? st.cpuColorSsbo : 0);
        GLUniform1i(U("uCpuWorldModelColor"), active ? 1 : 0);
        GLUniform1ui(U("uCpuWorldModelColorBase"), active
                                                       ? static_cast<uint32>((size_t(st.submissionFrameSlot) * st.cpuColorCapacity) / sizeof(float))
                                                       : 0u);
        if (active)
            st.cpuColorUsedThisFrame = true;
    }
}

void WorldModelRenderer::AdvanceStreamFrame()
{
    auto &st = m_state;
    if (!glf.FenceSync || !glf.ClientWaitSync || !glf.DeleteSync)
    {
        st.drawStateCursorBytes = 0;
        st.indirectCursorBytes = 0;
        st.submissionUsedThisFrame = false;
        st.cpuColorUsedThisFrame = false;
        return;
    }

    const bool haveSubmissionStream = st.drawStateMapped && st.indirectMapped;
    const bool haveColorStream = st.cpuColorMapped && st.cpuColorSsbo;
    if (!haveSubmissionStream && !haveColorStream)
    {
        st.drawStateCursorBytes = 0;
        st.indirectCursorBytes = 0;
        st.submissionUsedThisFrame = false;
        st.cpuColorUsedThisFrame = false;
        return;
    }

    if (st.submissionUsedThisFrame || st.cpuColorUsedThisFrame)
    {
        if (st.submissionFences[st.submissionFrameSlot])
            glf.DeleteSync(st.submissionFences[st.submissionFrameSlot]);
        st.submissionFences[st.submissionFrameSlot] = glf.FenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE_, 0);
    }

    const uint32 next = (st.submissionFrameSlot + 1u) % static_cast<uint32>(WM_STREAM_FRAMES);
    if (st.submissionFences[next])
    {
        const GLenum wait = glf.ClientWaitSync(st.submissionFences[next], GL_SYNC_FLUSH_COMMANDS_BIT_, GL_TIMEOUT_IGNORED_);
        if (wait == GL_WAIT_FAILED_)
            LOG_SESSION("World3D WM submission stream: glClientWaitSync failed on slot %u", next);
        glf.DeleteSync(st.submissionFences[next]);
        st.submissionFences[next] = nullptr;
    }
    st.submissionFrameSlot = next;

    // The slot is no longer in flight. Seed it from the authoritative CPU RGB
    // arena so a LightAnim change made while another slot was active is never
    // lost when this slot rotates back in. This is a CPU memcpy into coherent
    // mapped memory, not a driver upload call.
    if (st.cpuColorMapped && !st.cpuColorArena.empty() && st.cpuColorCapacity)
    {
        const size_t bytes = st.cpuColorArena.size() * sizeof(float);
        if (bytes <= st.cpuColorCapacity)
        {
            auto *dst = static_cast<unsigned char *>(st.cpuColorMapped) + size_t(next) * st.cpuColorCapacity;
            std::memcpy(dst, st.cpuColorArena.data(), bytes);
        }
    }

    st.drawStateCursorBytes = 0;
    st.indirectCursorBytes = 0;
    st.submissionUsedThisFrame = false;
    st.cpuColorUsedThisFrame = false;
}

void WorldModelRenderer::Term()
{
    for (auto &kv : m_state.caches)
    {
        if (kv.second.vbo)
            glf.DeleteBuffers(1, &kv.second.vbo);
        if (kv.second.vertexLightSsbo)
            glf.DeleteBuffers(1, &kv.second.vertexLightSsbo);
    }
    m_state.caches.clear();

    if (m_state.arenaVbo)
        glf.DeleteBuffers(1, &m_state.arenaVbo);
    m_state.arenaVbo = 0;
    m_state.arenaCapacityBytes = 0;
    m_state.arenaUsedVertices = 0;

    if (m_state.vertexLightArenaSsbo)
        glf.DeleteBuffers(1, &m_state.vertexLightArenaSsbo);
    m_state.vertexLightArenaSsbo = 0;
    m_state.vertexLightArenaCapacityBytes = 0;
    m_state.vertexLightArenaCpu.clear();
    if (m_state.cpuColorSsbo)
        glf.DeleteBuffers(1, &m_state.cpuColorSsbo);
    m_state.cpuColorSsbo = 0;
    m_state.cpuColorMapped = nullptr;
    m_state.cpuColorCapacity = 0;
    m_state.cpuColorArena.clear();
    m_state.cpuColorUsedThisFrame = false;

    for (void *&fence : m_state.submissionFences)
    {
        if (fence && glf.DeleteSync)
        {
            glf.DeleteSync(fence);
            fence = nullptr;
        }
    }
    m_state.drawStateMapped = nullptr;
    m_state.indirectMapped = nullptr;
    if (m_state.drawStateSsbo)
        glf.DeleteBuffers(1, &m_state.drawStateSsbo);
    if (m_state.indirectBuffer)
        glf.DeleteBuffers(1, &m_state.indirectBuffer);
    if (m_state.drawStateFallbackSsbo)
        glf.DeleteBuffers(1, &m_state.drawStateFallbackSsbo);
    if (m_state.indirectFallbackBuffer)
        glf.DeleteBuffers(1, &m_state.indirectFallbackBuffer);
    m_state.drawStateSsbo = m_state.indirectBuffer = 0;
    m_state.drawStateFallbackSsbo = m_state.indirectFallbackBuffer = 0;
    m_state.drawStateCapacity = m_state.indirectCapacity = 0;
    m_state.drawStateCursorBytes = m_state.indirectCursorBytes = 0;
    m_state.submissionFrameSlot = 0;
    m_state.submissionUsedThisFrame = false;

    WorldSurfaceFxSystem::Instance().Clear();
    PVSState().visibleWorldModels.clear();
    PVSState().visibleWorldModelCount = 0;

    // Terrain PVS entries reference batch/span layouts owned by the caches
    // above.  Force their compact command stream to be rebuilt after cache
    // destruction even if the visible leaf generation itself did not change.
    StaticState().terrainVisibleBspCache.clear();
    StaticState().terrainDrawCacheGeneration = 0;
    StaticState().terrainDrawCacheWorld = nullptr;
    StaticState().terrainDrawCacheHadPvs = false;
}

static bool EnsureLightGridTexture(MainWorldCompat *world)
{
    if (!world)
        return false;

    const LightTableCompat &lt = world->m_LightTable;
    const uint32 sx = lt.m_adwLookupSize[0];
    const uint32 sy = lt.m_adwLookupSize[1];
    const uint32 sz = lt.m_adwLookupSize[2];

    if (!lt.m_pLookup || sx == 0 || sy == 0 || sz == 0 ||
        sx > 4096 || sy > 4096 || sz > 4096 ||
        static_cast<uint64_t>(sx) * sy * sz > 64ull * 1024ull * 1024ull)
        return false;

    if (LightmapState().lightGridTexture && LightmapState().lightGridWorld == world &&
        LightmapState().lightGridX == sx && LightmapState().lightGridY == sy && LightmapState().lightGridZ == sz)
        return true;

    if (LightmapState().lightGridTexture)
        GLStateDeleteTextures(1, &LightmapState().lightGridTexture);

    LightmapState().lightGridTexture = 0;
    LightmapState().lightGridWorld = world;
    LightmapState().lightGridX = sx;
    LightmapState().lightGridY = sy;
    LightmapState().lightGridZ = sz;

    // Talon's LTRGB is B,G,R,A. Upload with GL_BGRA so GLSL samples R,G,B.
    const uint32 texW = sx;
    const uint32 texH = sy * sz;

    glf.CreateTextures(GL_TEXTURE_2D_, 1, &LightmapState().lightGridTexture);
    glf.TextureStorage2D(LightmapState().lightGridTexture, 1, GL_RGBA8_,
                         static_cast<GLsizei>(texW), static_cast<GLsizei>(texH));
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glf.TextureSubImage2D(LightmapState().lightGridTexture, 0, 0, 0,
                          static_cast<GLsizei>(texW), static_cast<GLsizei>(texH),
                          GL_BGRA_, GL_UNSIGNED_BYTE, lt.m_pLookup);

    // Original d3d.ren performs explicit trilinear interpolation.
    // Keep the texture nearest and reproduce the interpolation in GLSL.
    glf.TextureParameteri(LightmapState().lightGridTexture, GL_TEXTURE_MIN_FILTER_, GL_NEAREST);
    glf.TextureParameteri(LightmapState().lightGridTexture, GL_TEXTURE_MAG_FILTER_, GL_NEAREST);
    glf.TextureParameteri(LightmapState().lightGridTexture, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
    glf.TextureParameteri(LightmapState().lightGridTexture, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);

    LOG_SESSION("World3D LIGHTGRID uploaded world=%p dims=%ux%ux%u pixels=%u start=(%.2f %.2f %.2f) block=(%.2f %.2f %.2f) recip=(%.6f %.6f %.6f)",
                world, sx, sy, sz, lt.m_dwFullLookupSize,
                lt.m_vLookupStart.x, lt.m_vLookupStart.y, lt.m_vLookupStart.z,
                lt.m_vBlockSize.x, lt.m_vBlockSize.y, lt.m_vBlockSize.z,
                lt.m_vReciBlockSize.x, lt.m_vReciBlockSize.y, lt.m_vReciBlockSize.z);

    return true;
}

static bool HasAnyVertexLightRef(const std::vector<WorldModelVertexLightRef> &refs)
{
    for (const WorldModelVertexLightRef &r : refs)
        if (r.poly)
            return true;
    return false;
}

static bool EnsureWorldModelVertexLightArenaCapacity(size_t requiredBytes)
{
    if (WorldRenderer::Instance().WorldModels().State().vertexLightArenaSsbo &&
        requiredBytes <= WorldRenderer::Instance().WorldModels().State().vertexLightArenaCapacityBytes)
        return true;

    constexpr size_t ARENA_MIN_BYTES = 8u * 1024u * 1024u;
    constexpr size_t ARENA_MAX_BYTES = 128u * 1024u * 1024u;
    if (requiredBytes > ARENA_MAX_BYTES)
        return false;

    size_t newCapacity = std::max(ARENA_MIN_BYTES,
                                  WorldRenderer::Instance().WorldModels().State().vertexLightArenaCapacityBytes);
    while (newCapacity < requiredBytes && newCapacity < ARENA_MAX_BYTES)
        newCapacity = std::min(ARENA_MAX_BYTES, newCapacity * 2u);
    if (newCapacity < requiredBytes)
        return false;

    GLuint newSsbo = 0;
    glf.CreateBuffers(1, &newSsbo);
    if (!newSsbo)
        return false;
    glf.NamedBufferStorage(newSsbo, static_cast<GLsizeiptr>(newCapacity),
                           nullptr, GL_DYNAMIC_STORAGE_BIT_);

    if (!WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.empty())
    {
        const size_t usedBytes =
            WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.size() * sizeof(uint32);
        if (usedBytes > newCapacity)
        {
            glf.DeleteBuffers(1, &newSsbo);
            return false;
        }
        GLTrackedWorldNamedBufferSubData(newSsbo, 0, static_cast<GLsizeiptr>(usedBytes),
                                         WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.data(), GLWorldUploadKind::CacheBuild);
    }

    if (WorldRenderer::Instance().WorldModels().State().vertexLightArenaSsbo)
        glf.DeleteBuffers(1, &WorldRenderer::Instance().WorldModels().State().vertexLightArenaSsbo);
    WorldRenderer::Instance().WorldModels().State().vertexLightArenaSsbo = newSsbo;
    WorldRenderer::Instance().WorldModels().State().vertexLightArenaCapacityBytes = newCapacity;

    static uint32 budget = 16;
    if (LogIsSessionEnabled() && (budget))
    {
        --budget;
        LOG_SESSION("World3D WM VERTEX-LIGHT ARENA resize bytes=%llu usedWords=%u path=GLOBAL-SSBO",
                    static_cast<unsigned long long>(newCapacity),
                    static_cast<unsigned>(WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.size()));
    }
    return true;
}

static bool AppendWorldModelVertexLightArena(WorldModelCache &cache,
                                             const std::vector<uint32> &blob)
{
    cache.vertexLightArenaResident = false;
    cache.vertexLightArenaWordOffset = 0;
    if (blob.empty())
        return false;

    // Give every cache header 16-byte alignment.  The payload itself is uint32
    // addressed, but this keeps captures/debugging friendly and future-proofs
    // the arena for wider descriptor headers.
    const uint64_t currentWords = static_cast<uint64_t>(WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.size());
    const uint64_t alignedWords64 = (currentWords + 3ull) & ~uint64_t(3ull);
    const uint64_t endWords64 = alignedWords64 + static_cast<uint64_t>(blob.size());
    if (endWords64 > 0xFFFFFFFFull ||
        endWords64 > static_cast<uint64_t>(std::numeric_limits<size_t>::max() / sizeof(uint32)))
        return false;

    const size_t alignedWords = static_cast<size_t>(alignedWords64);
    const size_t endWords = static_cast<size_t>(endWords64);
    const size_t requiredBytes = endWords * sizeof(uint32);
    if (!EnsureWorldModelVertexLightArenaCapacity(requiredBytes) ||
        !WorldRenderer::Instance().WorldModels().State().vertexLightArenaSsbo)
        return false;

    if (WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.size() < alignedWords)
        WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.resize(alignedWords, 0u);

    cache.vertexLightArenaWordOffset = static_cast<uint32>(alignedWords);
    cache.vertexLightArenaResident = true;
    WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.insert(
        WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.end(), blob.begin(), blob.end());

    GLTrackedWorldNamedBufferSubData(WorldRenderer::Instance().WorldModels().State().vertexLightArenaSsbo,
                                     static_cast<GLintptr>(alignedWords * sizeof(uint32)),
                                     static_cast<GLsizeiptr>(blob.size() * sizeof(uint32)), blob.data(), GLWorldUploadKind::CacheBuild);
    return true;
}

bool WorldModelRenderer::BuildGpuVertexLightBuffer(MainWorldCompat *world,
                                                   const std::vector<WorldModelVertexLightRef> &lightRefs,
                                                   GLuint &outBuffer,
                                                   const char *label,
                                                   WorldModelCache *arenaCache)
{
    if (outBuffer)
    {
        glf.DeleteBuffers(1, &outBuffer);
        outBuffer = 0;
    }

    if (!LightmapState().gpuReady || !LightmapState().animStateSsbo || !world ||
        !world->m_LMAnims.m_pArray || lightRefs.empty() ||
        !HasAnyVertexLightRef(lightRefs))
        return false;

    // One descriptor per actual GPU vertex.  Triangulation duplicates source
    // polygon vertices, so deduplicate the expensive animation/color payload by
    // (WorldPoly*, sourceVertex) and let duplicate GPU vertices share it.
    std::vector<uint32> desc(lightRefs.size() * 2u, 0u);
    std::vector<uint32> packedRefs; // animIndex, colorStart, frameCount, pad
    std::vector<uint32> colors;     // packed 0x00RRGGBB, one per source frame
    std::unordered_map<VertexLightSourceKey, std::array<uint32, 2>, VertexLightSourceKeyHash> shared;
    shared.reserve(lightRefs.size() / 2u + 1u);

    uint32 dynamicVerts = 0;
    uint32 uniqueSources = 0;

    for (size_t vi = 0; vi < lightRefs.size(); ++vi)
    {
        const WorldModelVertexLightRef &lr = lightRefs[vi];
        if (!lr.poly)
            continue;

        ++dynamicVerts;
        const VertexLightSourceKey key{lr.poly, lr.vert};
        auto found = shared.find(key);
        if (found != shared.end())
        {
            desc[vi * 2u + 0u] = found->second[0];
            desc[vi * 2u + 1u] = found->second[1];
            continue;
        }

        const uint32 refStart = static_cast<uint32>(packedRefs.size() / 4u);
        uint32 refCount = 0;

        WorldPolyCompat *poly = lr.poly;
        if (poly->m_pPolyAnimRefs && poly->m_dwPolyAnimRefs &&
            poly->m_dwPolyAnimRefs <= 256)
        {
            for (uint32 pr = 0; pr < poly->m_dwPolyAnimRefs; ++pr)
            {
                const PolyAnimRefCompat &pref = poly->m_pPolyAnimRefs[pr];
                const uint32 animIndex = static_cast<uint32>(pref.m_wRefs[0]);
                const uint32 dataIndex = static_cast<uint32>(pref.m_wRefs[1]);
                if (animIndex >= world->m_LMAnims.m_dwElements)
                    continue;

                LMAnimCompat &anim = world->m_LMAnims.m_pArray[animIndex];
                const uint32 frameCount = static_cast<uint32>(anim.m_nFrames);
                if (!anim.m_pFrames || !frameCount || frameCount > 4096u ||
                    dataIndex >= anim.m_wPolyRefs)
                    continue;

                std::vector<uint32> localColors(frameCount, 0xFFFFFFFFu);
                bool any = false;
                for (uint32 fi = 0; fi < frameCount; ++fi)
                {
                    LMFramePolyDataCompat *list = anim.m_pFrames[fi].m_pPolyDataList;
                    if (!list)
                        continue;
                    LMFramePolyDataCompat &d = list[dataIndex];
                    if (!d.m_pReds || !d.m_pGreens || !d.m_pBlues ||
                        lr.vert >= d.m_nVertices)
                        continue;

                    localColors[fi] =
                        (uint32(d.m_pReds[lr.vert]) << 16) |
                        (uint32(d.m_pGreens[lr.vert]) << 8) |
                        uint32(d.m_pBlues[lr.vert]);
                    any = true;
                }

                if (!any)
                    continue;

                const uint32 colorStart = static_cast<uint32>(colors.size());
                colors.insert(colors.end(), localColors.begin(), localColors.end());

                packedRefs.push_back(animIndex);
                packedRefs.push_back(colorStart);
                packedRefs.push_back(frameCount);
                packedRefs.push_back(0u);
                ++refCount;
            }
        }

        desc[vi * 2u + 0u] = refStart;
        desc[vi * 2u + 1u] = refCount;
        shared.emplace(key, std::array<uint32, 2>{refStart, refCount});
        if (refCount)
            ++uniqueSources;
    }

    if (!uniqueSources || packedRefs.empty() || colors.empty())
        return false;

    // Single immutable SSBO:
    //   header[4] = descriptorBase, refBase, colorBase, vertexCount
    //   descriptors = {refStart, refCount} per GPU vertex
    //   refs        = {animIndex, colorStart, frameCount, pad}
    //   colors      = packed RGB source bytes for every frame
    const uint32 descBase = 4u;
    const uint32 refBase = descBase + static_cast<uint32>(desc.size());
    const uint32 colorBase = refBase + static_cast<uint32>(packedRefs.size());

    std::vector<uint32> blob;
    blob.reserve(size_t(colorBase) + colors.size());
    blob.push_back(descBase);
    blob.push_back(refBase);
    blob.push_back(colorBase);
    blob.push_back(static_cast<uint32>(lightRefs.size()));
    blob.insert(blob.end(), desc.begin(), desc.end());
    blob.insert(blob.end(), packedRefs.begin(), packedRefs.end());
    blob.insert(blob.end(), colors.begin(), colors.end());

    const bool globalArenaOK = arenaCache
                                   ? AppendWorldModelVertexLightArena(*arenaCache, blob)
                                   : false;

    constexpr size_t GPU_VERTEX_LIGHT_CAP = 64u * 1024u * 1024u;
    const size_t bytes = blob.size() * sizeof(uint32);
    if (bytes > GPU_VERTEX_LIGHT_CAP)
    {
        LOG_SESSION("World3D GPU VERTEX-LIGHT rejected label='%s' bytes=%llu cap=%llu; CPU VBO fallback retained",
                    label ? label : "?", static_cast<unsigned long long>(bytes),
                    static_cast<unsigned long long>(GPU_VERTEX_LIGHT_CAP));
        return false;
    }

    glf.CreateBuffers(1, &outBuffer);
    if (!outBuffer)
        return false;
    glf.NamedBufferStorage(outBuffer, static_cast<GLsizeiptr>(bytes), blob.data(), 0);

    LOG_SESSION("World3D GPU VERTEX-LIGHT ready label='%s' gpuVerts=%u uniqueSources=%u refs=%u sourceColors=%u bytes=%llu globalArena=%d wordOffset=%u path=IMMUTABLE-SSBO/VERTEX-SHADER",
                label ? label : "?", dynamicVerts, uniqueSources,
                static_cast<unsigned>(packedRefs.size() / 4u),
                static_cast<unsigned>(colors.size()),
                static_cast<unsigned long long>(bytes),
                globalArenaOK ? 1 : 0,
                (arenaCache && arenaCache->vertexLightArenaResident)
                    ? arenaCache->vertexLightArenaWordOffset
                    : 0u);
    return true;
}

static bool EnsureCpuWorldModelColorCapacity(size_t requiredBytes)
{
    auto &st = WorldRenderer::Instance().WorldModels().State();
    if (st.cpuColorSsbo && st.cpuColorMapped && requiredBytes <= st.cpuColorCapacity)
        return true;
    if (!glf.MapNamedBufferRange || requiredBytes > WM_COLOR_MAX_SEGMENT_BYTES)
        return false;

    size_t cap = std::max(WM_COLOR_MIN_SEGMENT_BYTES, st.cpuColorCapacity);
    while (cap < requiredBytes && cap < WM_COLOR_MAX_SEGMENT_BYTES)
        cap = std::min(WM_COLOR_MAX_SEGMENT_BYTES, cap * 2u);
    cap = AlignUp(cap, 256u);
    if (cap < requiredBytes)
        return false;

    GLuint buffer = 0;
    glf.CreateBuffers(1, &buffer);
    if (!buffer)
        return false;
    const GLbitfield storageFlags = GL_MAP_WRITE_BIT_ | GL_MAP_PERSISTENT_BIT_ | GL_MAP_COHERENT_BIT_ | GL_DYNAMIC_STORAGE_BIT_;
    const GLsizeiptr total = static_cast<GLsizeiptr>(cap * WM_STREAM_FRAMES);
    glf.NamedBufferStorage(buffer, total, nullptr, storageFlags);
    void *mapped = glf.MapNamedBufferRange(buffer, 0, total,
                                           GL_MAP_WRITE_BIT_ | GL_MAP_PERSISTENT_BIT_ | GL_MAP_COHERENT_BIT_);
    if (!mapped)
    {
        glf.DeleteBuffers(1, &buffer);
        return false;
    }

    const size_t used = st.cpuColorArena.size() * sizeof(float);
    if (used)
        for (size_t slot = 0; slot < WM_STREAM_FRAMES; ++slot)
            std::memcpy(static_cast<unsigned char *>(mapped) + slot * cap, st.cpuColorArena.data(), used);

    if (st.cpuColorSsbo)
        glf.DeleteBuffers(1, &st.cpuColorSsbo);
    st.cpuColorSsbo = buffer;
    st.cpuColorMapped = mapped;
    st.cpuColorCapacity = cap;
    LOG_SESSION("World3D WM CPU-COLOR stream resize segmentBytes=%llu totalBytes=%llu usedRGBBytes=%llu path=PERSISTENT-SSBO",
                static_cast<unsigned long long>(cap),
                static_cast<unsigned long long>(cap * WM_STREAM_FRAMES),
                static_cast<unsigned long long>(used));
    return true;
}

static bool AppendCpuWorldModelColors(WorldModelCache &cache, const std::vector<WorldVertexGPU> &vertices)
{
    if (!cache.arenaResident || vertices.empty())
        return false;
    auto &st = WorldRenderer::Instance().WorldModels().State();
    const size_t firstFloat = size_t(cache.arenaFirstVertex) * 3u;
    const size_t endFloat = firstFloat + vertices.size() * 3u;
    if (!EnsureCpuWorldModelColorCapacity(endFloat * sizeof(float)))
        return false;
    if (st.cpuColorArena.size() < endFloat)
        st.cpuColorArena.resize(endFloat, 1.0f);
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        st.cpuColorArena[firstFloat + i * 3u + 0u] = vertices[i].r;
        st.cpuColorArena[firstFloat + i * 3u + 1u] = vertices[i].g;
        st.cpuColorArena[firstFloat + i * 3u + 2u] = vertices[i].b;
    }
    const size_t bytes = vertices.size() * 3u * sizeof(float);
    for (size_t slot = 0; slot < WM_STREAM_FRAMES; ++slot)
    {
        float *dst = reinterpret_cast<float *>(static_cast<unsigned char *>(st.cpuColorMapped) + slot * st.cpuColorCapacity);
        std::memcpy(dst + firstFloat, st.cpuColorArena.data() + firstFloat, bytes);
    }
    return true;
}

static bool EnsureWorldModelArenaCapacity(size_t requiredBytes)
{
    if (WorldRenderer::Instance().WorldModels().State().arenaVbo && requiredBytes <= WorldRenderer::Instance().WorldModels().State().arenaCapacityBytes)
        return true;

    constexpr size_t ARENA_MIN_BYTES = 8u * 1024u * 1024u;
    constexpr size_t ARENA_MAX_BYTES = 256u * 1024u * 1024u;
    if (requiredBytes > ARENA_MAX_BYTES)
        return false;

    size_t newCapacity = std::max(ARENA_MIN_BYTES, WorldRenderer::Instance().WorldModels().State().arenaCapacityBytes);
    while (newCapacity < requiredBytes && newCapacity < ARENA_MAX_BYTES)
        newCapacity = std::min(ARENA_MAX_BYTES, newCapacity * 2u);
    if (newCapacity < requiredBytes)
        return false;

    GLuint newVbo = 0;
    glf.CreateBuffers(1, &newVbo);
    if (!newVbo)
        return false;
    glf.NamedBufferStorage(newVbo, static_cast<GLsizeiptr>(newCapacity), nullptr, GL_DYNAMIC_STORAGE_BIT_);

    // Arena offsets never change.  If the append-only arena grows, rebuild the
    // new GPU storage from the immutable CPU cache copies.  Growth only occurs
    // while a new BSP cache is being adopted, never in the steady-state draw
    // loop.
    for (const auto &kv : WorldRenderer::Instance().WorldModels().State().caches)
    {
        const WorldModelCache &c = kv.second;
        if (!c.arenaResident || c.cpuVertices.empty())
            continue;
        const size_t offset = size_t(c.arenaFirstVertex) * sizeof(WorldVertexGPU);
        const size_t bytes = c.cpuVertices.size() * sizeof(WorldVertexGPU);
        if (offset + bytes > newCapacity)
        {
            glf.DeleteBuffers(1, &newVbo);
            return false;
        }
        GLTrackedWorldNamedBufferSubData(newVbo, static_cast<GLintptr>(offset),
                                         static_cast<GLsizeiptr>(bytes), c.cpuVertices.data(), GLWorldUploadKind::CacheBuild);
    }

    if (WorldRenderer::Instance().WorldModels().State().arenaVbo)
        glf.DeleteBuffers(1, &WorldRenderer::Instance().WorldModels().State().arenaVbo);
    WorldRenderer::Instance().WorldModels().State().arenaVbo = newVbo;
    WorldRenderer::Instance().WorldModels().State().arenaCapacityBytes = newCapacity;

    static uint32 budget = 32;
    if (LogIsSessionEnabled() && (budget && (--budget, true)))
        LOG_SESSION("World3D WM ARENA resize bytes=%llu usedVerts=%u path=GLOBAL-VBO",
                    static_cast<unsigned long long>(newCapacity), WorldRenderer::Instance().WorldModels().State().arenaUsedVertices);
    return true;
}

static bool AppendWorldModelArena(WorldModelCache &cache,
                                  const std::vector<WorldVertexGPU> &vertices)
{
    if (vertices.empty())
        return false;

    const uint64_t first = WorldRenderer::Instance().WorldModels().State().arenaUsedVertices;
    const uint64_t end = first + vertices.size();
    if (end > 0xFFFFFFFFull)
        return false;

    const size_t requiredBytes = size_t(end) * sizeof(WorldVertexGPU);
    if (!EnsureWorldModelArenaCapacity(requiredBytes) || !WorldRenderer::Instance().WorldModels().State().arenaVbo)
        return false;

    cache.arenaFirstVertex = static_cast<uint32>(first);
    cache.arenaResident = true;
    GLTrackedWorldNamedBufferSubData(WorldRenderer::Instance().WorldModels().State().arenaVbo,
                                     static_cast<GLintptr>(size_t(cache.arenaFirstVertex) * sizeof(WorldVertexGPU)),
                                     static_cast<GLsizeiptr>(vertices.size() * sizeof(WorldVertexGPU)),
                                     vertices.data(), GLWorldUploadKind::CacheBuild);
    WorldRenderer::Instance().WorldModels().State().arenaUsedVertices = static_cast<uint32>(end);
    return true;
}

static bool EnsureWmSubmissionBuffers(size_t drawCount)
{
    if (drawCount == 0)
        return false;

    auto &st = WorldRenderer::Instance().WorldModels().State();
    const size_t wantedStates = drawCount * sizeof(WmDrawStateGPU);
    const size_t wantedCmds = drawCount * sizeof(DrawArraysIndirectCommandGPU);

    auto grow = [](size_t current, size_t wanted, size_t minimum, size_t alignment) -> size_t
    {
        size_t cap = std::max(current, minimum);
        while (cap < wanted)
            cap *= 2u;
        return AlignUp(cap, alignment);
    };

    // Do not replace a persistent buffer after this frame has already emitted
    // draws from it. If a pathological frame exhausts the segment, the upload
    // helper below falls back to the driver-managed SubData buffers instead.
    const bool canRebuild = !st.submissionUsedThisFrame &&
                            st.drawStateCursorBytes == 0 && st.indirectCursorBytes == 0;
    const bool needState = !st.drawStateSsbo || wantedStates > st.drawStateCapacity;
    const bool needCmd = !st.indirectBuffer || wantedCmds > st.indirectCapacity;

    if ((needState || needCmd) && canRebuild)
    {
        for (void *&fence : st.submissionFences)
        {
            if (fence && glf.DeleteSync)
            {
                glf.DeleteSync(fence);
                fence = nullptr;
            }
        }

        const size_t stateCap = grow(st.drawStateCapacity, wantedStates,
                                     WM_STATE_MIN_SEGMENT_BYTES, sizeof(WmDrawStateGPU));
        const size_t cmdCap = grow(st.indirectCapacity, wantedCmds,
                                   WM_COMMAND_MIN_SEGMENT_BYTES, 64u);
        const GLbitfield flags = GL_MAP_WRITE_BIT_ | GL_MAP_PERSISTENT_BIT_ | GL_MAP_COHERENT_BIT_ | GL_DYNAMIC_STORAGE_BIT_;

        if (st.drawStateSsbo)
            glf.DeleteBuffers(1, &st.drawStateSsbo);
        if (st.indirectBuffer)
            glf.DeleteBuffers(1, &st.indirectBuffer);
        if (st.drawStateFallbackSsbo)
            glf.DeleteBuffers(1, &st.drawStateFallbackSsbo);
        if (st.indirectFallbackBuffer)
            glf.DeleteBuffers(1, &st.indirectFallbackBuffer);
        st.drawStateSsbo = st.indirectBuffer = 0;
        st.drawStateFallbackSsbo = st.indirectFallbackBuffer = 0;
        st.drawStateMapped = st.indirectMapped = nullptr;

        glf.CreateBuffers(1, &st.drawStateSsbo);
        glf.CreateBuffers(1, &st.indirectBuffer);
        glf.CreateBuffers(1, &st.drawStateFallbackSsbo);
        glf.CreateBuffers(1, &st.indirectFallbackBuffer);
        if (!st.drawStateSsbo || !st.indirectBuffer ||
            !st.drawStateFallbackSsbo || !st.indirectFallbackBuffer)
            return false;

        glf.NamedBufferStorage(st.drawStateSsbo,
                               static_cast<GLsizeiptr>(stateCap * WM_STREAM_FRAMES), nullptr, flags);
        glf.NamedBufferStorage(st.indirectBuffer,
                               static_cast<GLsizeiptr>(cmdCap * WM_STREAM_FRAMES), nullptr, flags);
        glf.NamedBufferStorage(st.drawStateFallbackSsbo,
                               static_cast<GLsizeiptr>(stateCap), nullptr, GL_DYNAMIC_STORAGE_BIT_);
        glf.NamedBufferStorage(st.indirectFallbackBuffer,
                               static_cast<GLsizeiptr>(cmdCap), nullptr, GL_DYNAMIC_STORAGE_BIT_);

        st.drawStateMapped = glf.MapNamedBufferRange
                                 ? glf.MapNamedBufferRange(st.drawStateSsbo, 0,
                                                           static_cast<GLsizeiptr>(stateCap * WM_STREAM_FRAMES), flags)
                                 : nullptr;
        st.indirectMapped = glf.MapNamedBufferRange
                                ? glf.MapNamedBufferRange(st.indirectBuffer, 0,
                                                          static_cast<GLsizeiptr>(cmdCap * WM_STREAM_FRAMES), flags)
                                : nullptr;
        st.drawStateCapacity = stateCap;
        st.indirectCapacity = cmdCap;
        st.drawStateCursorBytes = st.indirectCursorBytes = 0;
        st.submissionFrameSlot = 0;
        st.submissionUsedThisFrame = false;

        LOG_SESSION("World3D WM submission stream state=%s cmd=%s stateSeg=%zuKB cmdSeg=%zuKB frames=%zu",
                    st.drawStateMapped ? "PERSISTENT" : "FALLBACK",
                    st.indirectMapped ? "PERSISTENT" : "FALLBACK",
                    stateCap / 1024u, cmdCap / 1024u, WM_STREAM_FRAMES);
    }

    return st.drawStateSsbo && st.indirectBuffer &&
           st.drawStateFallbackSsbo && st.indirectFallbackBuffer;
}

struct WmSubmissionUpload
{
    GLuint stateBuffer = 0;
    GLuint commandBuffer = 0;
    uint32 stateBaseInstance = 0;
    size_t commandByteOffset = 0;
    bool persistent = false;
};

static bool UploadWmSubmission(std::vector<WmDrawStateGPU> &states,
                               std::vector<DrawArraysIndirectCommandGPU> &commands,
                               WmSubmissionUpload &out)
{
    auto &st = WorldRenderer::Instance().WorldModels().State();
    const size_t stateBytes = states.size() * sizeof(WmDrawStateGPU);
    const size_t commandBytes = commands.size() * sizeof(DrawArraysIndirectCommandGPU);
    if (!stateBytes || !commandBytes || !EnsureWmSubmissionBuffers(commands.size()))
        return false;

    const size_t stateCursor = AlignUp(st.drawStateCursorBytes, sizeof(WmDrawStateGPU));
    const size_t commandCursor = AlignUp(st.indirectCursorBytes, 64u);
    const bool canStream = st.drawStateMapped && st.indirectMapped &&
                           stateCursor + stateBytes <= st.drawStateCapacity &&
                           commandCursor + commandBytes <= st.indirectCapacity;

    if (canStream)
    {
        const size_t stateAbsolute = st.submissionFrameSlot * st.drawStateCapacity + stateCursor;
        const size_t commandAbsolute = st.submissionFrameSlot * st.indirectCapacity + commandCursor;
        const uint32 baseInstance = static_cast<uint32>(stateAbsolute / sizeof(WmDrawStateGPU));
        for (auto &cmd : commands)
            cmd.baseInstance += baseInstance;

        std::memcpy(static_cast<unsigned char *>(st.drawStateMapped) + stateAbsolute,
                    states.data(), stateBytes);
        std::memcpy(static_cast<unsigned char *>(st.indirectMapped) + commandAbsolute,
                    commands.data(), commandBytes);
        st.drawStateCursorBytes = stateCursor + stateBytes;
        st.indirectCursorBytes = commandCursor + commandBytes;
        st.submissionUsedThisFrame = true;
        GLUploadStats::Instance().RecordWorldStreamWrite(GLWorldUploadKind::MdiState, stateBytes);
        GLUploadStats::Instance().RecordWorldStreamWrite(GLWorldUploadKind::MdiCommands, commandBytes);

        out.stateBuffer = st.drawStateSsbo;
        out.commandBuffer = st.indirectBuffer;
        out.stateBaseInstance = baseInstance;
        out.commandByteOffset = commandAbsolute;
        out.persistent = true;
        return true;
    }

    // Overflow and mapping failures retain the old driver-managed behavior.
    // These fallback buffers are separate so they cannot overwrite persistent
    // data already referenced by earlier draws in the same frame.
    if (stateBytes > st.drawStateCapacity || commandBytes > st.indirectCapacity)
        return false;
    GLTrackedWorldNamedBufferSubData(st.drawStateFallbackSsbo, 0,
                                     static_cast<GLsizeiptr>(stateBytes), states.data(), GLWorldUploadKind::MdiState);
    GLTrackedWorldNamedBufferSubData(st.indirectFallbackBuffer, 0,
                                     static_cast<GLsizeiptr>(commandBytes), commands.data(), GLWorldUploadKind::MdiCommands);
    out.stateBuffer = st.drawStateFallbackSsbo;
    out.commandBuffer = st.indirectFallbackBuffer;
    out.stateBaseInstance = 0;
    out.commandByteOffset = 0;
    out.persistent = false;
    return true;
}

static WmDrawStateGPU MakeWmDrawState(const WorldModelInstanceCompat *wm,
                                      const WorldModelCache *cache,
                                      uint32 materialParamIndex)
{
    WmDrawStateGPU s{};
    // ILTMatrix is row-major.  glUniformMatrix4fv(..., transpose=TRUE) was the
    // legacy path, so explicitly transpose into std430/GLSL column-major form.
    for (uint32 row = 0; row < 4; ++row)
        for (uint32 col = 0; col < 4; ++col)
            s.world[col * 4u + row] = wm->m_mTransform.m[row][col];

    const LTObjectCompat &o = wm->m_Base;
    s.objectColor[0] = o.m_nColorR / 255.0f;
    s.objectColor[1] = o.m_nColorG / 255.0f;
    s.objectColor[2] = o.m_nColorB / 255.0f;
    s.objectColor[3] = o.m_nColorA / 255.0f;
    if (cache)
    {
        s.info[0] = cache->arenaFirstVertex;
        s.info[1] = cache->vertexLightArenaWordOffset;
        s.info[2] = cache->vertexLightArenaResident ? 1u : 0u;
    }
    s.info[3] = materialParamIndex;
    return s;
}

static bool BuildWorldModelCache(MainWorldCompat *world, WorldBspCompat *bsp, WorldModelCache &cache)
{
    if (!world || !bsp || !bsp->m_pPolies || !bsp->m_dwPolies || bsp->m_dwPolies > 1000000)
        return false;

    std::vector<BatchBuild> builds;
    std::unordered_map<BatchKey, size_t, BatchKeyHash> batchMap;
    const bool forceNoLight = IsTerrainBsp(bsp);
    uint32 lmColorVerts = 0, lmTextureVerts = 0, fallbackLitVerts = 0, unlitVerts = 0;
    uint32 gouraudNoLmRawVerts = 0, gouraudNoLmDirtyVerts = 0;

    for (uint32 pi = 0; pi < bsp->m_dwPolies; ++pi)
    {
        WorldPolyCompat *poly = bsp->m_pPolies[pi];
        if (!poly || !poly->m_pSurface || poly->m_wNumVerts < 3 || poly->m_wNumVerts > 512)
            continue;
        SurfaceCompat *sf = poly->m_pSurface;
        uint32 flags = sf->m_dwFlags;
        const LTPlaneCompat *polyPlane = poly->m_pPlane
                                             ? reinterpret_cast<const LTPlaneCompat *>(poly->m_pPlane)
                                             : nullptr;
        const LTVector polyNormal = polyPlane ? polyPlane->m_vNormal : LTVector{0.0f, 0.0f, 0.0f};
        if ((flags & SURF_INVISIBLE) || (flags & SURF_SKY))
            continue;

        SharedTexture *tex = sf->m_pTexture;
        if (tex)
            // WorldModel materials are part of the active map's material set too.
            MaterialAuthoringSystem::Instance().Resolve(tex);
        Texture *glTex = TextureManager::Instance().Ensure(tex, false);
        SurfaceCompat *animatedSurface = (flags & SURF_SPRITEANIMATE) ? sf : nullptr;
        WorldBlendMode blend = WorldMaterialSystem::Instance().ClassifyBlend(flags);
        WorldTexFx texFx = WorldMaterialSystem::Instance().BuildTexFx(sf);
        const bool lightmapGouraud = ((flags & SURF_LIGHTMAP) != 0) && ((flags & SURF_GOURAUDSHADE) != 0);
        const bool gouraudNoLightmap = ((flags & SURF_GOURAUDSHADE) != 0) && ((flags & SURF_LIGHTMAP) == 0);

        if (lightmapGouraud)
        {
            static uint32 s_lmgProbeBudget = 96;
            if (LogIsSessionEnabled() && (s_lmgProbeBudget))
            {
                --s_lmgProbeBudget;
                float rawMin = 1.0f, rawMax = 0.0f, animMin = 1.0f, animMax = 0.0f;
                uint32 animVerts = 0;
                for (uint32 vv = 0; vv < poly->m_wNumVerts; ++vv)
                {
                    const SPolyVertexCompat &sv = poly->m_Vertices[vv];
                    const float rr = sv.m_nColorR / 255.0f, gg = sv.m_nColorG / 255.0f, bb = sv.m_nColorB / 255.0f;
                    rawMin = std::min(rawMin, std::min(rr, std::min(gg, bb)));
                    rawMax = std::max(rawMax, std::max(rr, std::max(gg, bb)));
                    float ar = 0, ag = 0, ab = 0;
                    if (WorldRenderer::Instance().Lighting().SampleAnimatedVertexColor(world, poly, vv, ar, ag, ab))
                    {
                        ++animVerts;
                        animMin = std::min(animMin, std::min(ar, std::min(ag, ab)));
                        animMax = std::max(animMax, std::max(ar, std::max(ag, ab)));
                    }
                }
                LTVector grid = WorldRenderer::Instance().Lighting().SampleLightTable(world->m_LightTable, poly->m_vCenter);
                LOG_SESSION("World3D D3D-LMG-PROBE bsp='%s' poly=%u surf=%08X lmFlags=%04X dirty4000=%u verts=%u rawRange=%.3f..%.3f animVerts=%u animRange=%.3f..%.3f center=(%.2f %.2f %.2f) grid255=(%.1f %.1f %.1f)",
                            bsp->m_szWorldName, pi, flags, unsigned(poly->m_wLMPlaneAndFlags),
                            (poly->m_wLMPlaneAndFlags & 0x4000u) ? 1u : 0u, unsigned(poly->m_wNumVerts),
                            rawMin, rawMax, animVerts, animVerts ? animMin : 0.0f, animVerts ? animMax : 0.0f,
                            poly->m_vCenter.x, poly->m_vCenter.y, poly->m_vCenter.z, grid.x, grid.y, grid.z);
            }
        }
        BatchKey key{tex, animatedSurface, blend, texFx.hash, lightmapGouraud, gouraudNoLightmap};
        size_t bi;
        auto it = batchMap.find(key);
        if (it == batchMap.end())
        {
            bi = builds.size();
            batchMap.emplace(key, bi);
            builds.push_back({});
            builds.back().texture = tex;
            builds.back().animatedSurface = animatedSurface;
            builds.back().uvNormWidth = (glTex && glTex->scaledWidth) ? float(glTex->scaledWidth) : ((glTex && glTex->width) ? float(glTex->width) : 1.0f);
            builds.back().uvNormHeight = (glTex && glTex->scaledHeight) ? float(glTex->scaledHeight) : ((glTex && glTex->height) ? float(glTex->height) : 1.0f);
            builds.back().blend = blend;
            builds.back().noLight = forceNoLight || ((flags & SURF_BRIGHT) != 0);
            builds.back().extraShade = (flags & SURF_TRANSPARENT) != 0;
            builds.back().lightmapGouraud = lightmapGouraud;
            builds.back().gouraudNoLightmap = gouraudNoLightmap;
            builds.back().texFx = texFx;
            builds.back().alphaRef = glTex ? glTex->alphaRef : 0.0f;
        }
        else
            bi = it->second;

        float iw = (glTex && glTex->scaledWidth) ? 1.0f / float(glTex->scaledWidth) : ((glTex && glTex->width) ? 1.0f / float(glTex->width) : 1.0f);
        float ih = (glTex && glTex->scaledHeight) ? 1.0f / float(glTex->scaledHeight) : ((glTex && glTex->height) ? 1.0f / float(glTex->height) : 1.0f);
        SPolyVertexCompat *pv = poly->m_Vertices;
        auto &out = builds[bi].vertices;
        const uint32 polyFirstVertex = static_cast<uint32>(out.size());
        SPolyVertexCompat base = pv[0];

        LTVector deluxeLmT{0.0f, 0.0f, 0.0f}, deluxeLmV{0.0f, 0.0f, 0.0f};
        if (poly->m_pPlane)
        {
            auto *deluxePlane = reinterpret_cast<LTPlaneCompat *>(poly->m_pPlane);
            WorldLightmapSystem::SetupPlaneVectors((poly->m_wLMPlaneAndFlags >> 11) & 7u,
                                                   deluxePlane->m_vNormal, deluxeLmT, deluxeLmV);
            const float tl = std::sqrt(deluxeLmT.x * deluxeLmT.x + deluxeLmT.y * deluxeLmT.y + deluxeLmT.z * deluxeLmT.z);
            if (tl > 0.00001f)
            {
                deluxeLmT.x /= tl;
                deluxeLmT.y /= tl;
                deluxeLmT.z /= tl;
            }
        }

        for (uint32 j = 1; j + 1 < poly->m_wNumVerts; ++j)
        {
            SPolyVertexCompat tri[3] = {base, pv[j], pv[j + 1]};
            uint32 vi[3] = {0, j, j + 1};
            if (!tri[0].m_pPoints || !tri[1].m_pPoints || !tri[2].m_pPoints)
                continue;
            LTVector baseTexT{0.0f, 0.0f, 0.0f};
            {
                const LTVector &p0 = tri[0].m_pPoints->m_vVec;
                const LTVector &p1 = tri[1].m_pPoints->m_vVec;
                const LTVector &p2 = tri[2].m_pPoints->m_vVec;
                const float u0 = tri[0].m_fScaledU * iw, v0 = tri[0].m_fScaledV * ih, u1 = tri[1].m_fScaledU * iw, v1 = tri[1].m_fScaledV * ih, u2 = tri[2].m_fScaledU * iw, v2 = tri[2].m_fScaledV * ih;
                const float e1x = p1.x - p0.x, e1y = p1.y - p0.y, e1z = p1.z - p0.z, e2x = p2.x - p0.x, e2y = p2.y - p0.y, e2z = p2.z - p0.z;
                const float du1 = u1 - u0, dv1 = v1 - v0, du2 = u2 - u0, dv2 = v2 - v0, det = du1 * dv2 - du2 * dv1;
                if (std::fabs(det) > 1e-20f)
                {
                    const float inv = 1.0f / det;
                    baseTexT.x = (e1x * dv2 - e2x * dv1) * inv;
                    baseTexT.y = (e1y * dv2 - e2y * dv1) * inv;
                    baseTexT.z = (e1z * dv2 - e2z * dv1) * inv;
                    const float tl = std::sqrt(baseTexT.x * baseTexT.x + baseTexT.y * baseTexT.y + baseTexT.z * baseTexT.z);
                    if (tl > 1e-10f)
                    {
                        baseTexT.x /= tl;
                        baseTexT.y /= tl;
                        baseTexT.z /= tl;
                    }
                }
            }
            for (int k = 0; k < 3; ++k)
            {
                const LTVector &q = tri[k].m_pPoints->m_vVec;
                float lu = 0, lv = 0;
                const bool lm = WorldLightmapSystem::Instance().GetUV(world, poly, vi[k], lu, lv);
                if (lm)
                {
                    builds[bi].hasLightmap = true;
                    ++lmTextureVerts;
                }

                float vr = 0.0f, vg = 0.0f, vb = 0.0f;
                // d3d.ren WorldModel path keeps texture-LightMap metadata and
                // animated vertex diffuse independent. A polygon may carry
                // lightmap UVs while its WorldModel draw still sources RGB
                // from the LightAnim vertex-color buffer.
                const bool lmVertexDirty = (poly->m_wLMPlaneAndFlags & 0x4000u) != 0;
                // d3d.ren 0x1002F579..0x1002F58E only refreshes the polygon's
                // SPolyVertex diffuse from the LightAnim vertex-colour payload
                // when WorldPoly::m_wLMPlaneAndFlags has bit 0x4000 set.  If the
                // bit is clear, stock relies on the RGB retained by the previous
                // refresh. Our cache can be created after the engine has cleared
                // this transient bit, so a Gouraud-only brush must still recover
                // the authoritative compiled RGB from its current LightAnim data.
                // Otherwise it can cache the raw white polygon colors and appear
                // full-bright in an unlit area.
                //
                // SURF_LIGHTMAP still has higher dispatch precedence and skips
                // this Gouraud refresh branch entirely when a texture payload
                // exists. If the current polygon has no atlas tile, stock's
                // lightmap draw falls back to LMFramePolyData vertex colors.
                const bool lightmapColorFallback =
                    !lm && ((flags & SURF_LIGHTMAP) != 0);
                const bool compiledGouraudColor = gouraudNoLightmap;
                bool vertexLM = (lightmapColorFallback || compiledGouraudColor ||
                                 (!lightmapGouraud && lmVertexDirty)) &&
                                WorldRenderer::Instance().Lighting().SampleAnimatedVertexColor(world, poly, vi[k], vr, vg, vb);

                if (vertexLM)
                {
                    ++lmColorVerts;
                    if (!(flags & SURF_LIGHTMAP) && (flags & SURF_GOURAUDSHADE))
                        ++gouraudNoLmDirtyVerts;
                }
                else
                {
                    if (!(flags & SURF_LIGHTMAP) && (flags & SURF_GOURAUDSHADE))
                        ++gouraudNoLmRawVerts;
                    vr = tri[k].m_nColorR / 255.0f;
                    vg = tri[k].m_nColorG / 255.0f;
                    vb = tri[k].m_nColorB / 255.0f;
                    if (vr > 0.001f || vg > 0.001f || vb > 0.001f)
                        ++fallbackLitVerts;
                    else
                        ++unlitVerts;
                }

                out.push_back({q.x, q.y, q.z,
                               tri[k].m_fScaledU * iw, tri[k].m_fScaledV * ih,
                               lu, lv,
                               vr, vg, vb, tri[k].m_nColorA / 255.0f,
                               lm ? 1.0f : 0.0f,
                               vertexLM ? 1.0f : 0.0f,
                               poly->m_vCenter.x, poly->m_vCenter.y, poly->m_vCenter.z,
                               polyNormal.x, polyNormal.y, polyNormal.z,
                               deluxeLmT.x, deluxeLmT.y, deluxeLmT.z,
                               baseTexT.x, baseTexT.y, baseTexT.z});
                if (!builds[bi].haveBounds)
                {
                    builds[bi].haveBounds = true;
                    builds[bi].minX = builds[bi].maxX = q.x;
                    builds[bi].minY = builds[bi].maxY = q.y;
                    builds[bi].minZ = builds[bi].maxZ = q.z;
                }
                else
                {
                    builds[bi].minX = std::min(builds[bi].minX, q.x);
                    builds[bi].maxX = std::max(builds[bi].maxX, q.x);
                    builds[bi].minY = std::min(builds[bi].minY, q.y);
                    builds[bi].maxY = std::max(builds[bi].maxY, q.y);
                    builds[bi].minZ = std::min(builds[bi].minZ, q.z);
                    builds[bi].maxZ = std::max(builds[bi].maxZ, q.z);
                }
                builds[bi].lightRefs.push_back(
                    vertexLM ? WorldModelVertexLightRef{poly, static_cast<uint16>(vi[k]), 0}
                             : WorldModelVertexLightRef{});
            }
        }
        const uint32 polyVertexCount = static_cast<uint32>(builds[bi].vertices.size()) - polyFirstVertex;
        if (polyVertexCount)
            builds[bi].spans.push_back({poly, polyFirstVertex, polyVertexCount});
        ++cache.totalPolys;
    }

    std::vector<WorldVertexGPU> all;
    uint32 first = 0;
    for (const BatchBuild &b : builds)
    {
        if (b.vertices.empty())
            continue;
        WorldBatch wb{};
        wb.texture = b.texture;
        wb.animatedSurface = b.animatedSurface;
        wb.uvNormWidth = b.uvNormWidth;
        wb.uvNormHeight = b.uvNormHeight;
        wb.firstVertex = first;
        wb.vertexCount = uint32(b.vertices.size());
        wb.blend = b.blend;
        wb.alphaRef = b.alphaRef;
        wb.noLight = b.noLight;
        wb.hasLightmap = b.hasLightmap;
        wb.extraShade = b.extraShade;
        wb.lightmapGouraud = b.lightmapGouraud;
        wb.gouraudNoLightmap = b.gouraudNoLightmap;
        wb.texFx = b.texFx;
        wb.minX = b.minX;
        wb.minY = b.minY;
        wb.minZ = b.minZ;
        wb.maxX = b.maxX;
        wb.maxY = b.maxY;
        wb.maxZ = b.maxZ;
        wb.spans.reserve(b.spans.size());
        for (const PolySpan &span : b.spans)
            wb.spans.push_back({span.poly, wb.firstVertex + span.firstVertex, span.vertexCount});
        cache.batches.push_back(std::move(wb));
        all.insert(all.end(), b.vertices.begin(), b.vertices.end());
        cache.lightRefs.insert(cache.lightRefs.end(), b.lightRefs.begin(), b.lightRefs.end());
        first += uint32(b.vertices.size());
    }
    if (all.empty())
        return false;

    if (cache.lightRefs.size() != all.size())
        cache.lightRefs.assign(all.size(), {});

    cache.cpuVertices = all;
    cache.totalVerts = uint32(all.size());

    // Prefer one shared append-only VBO for every brush WorldModel in the
    // level.  This removes per-object VAO vertex-buffer rebinding and is the
    // prerequisite for cross-WorldModel MDI submission.  Keep an individual
    // fallback buffer only if the arena cannot be allocated.
    if (!AppendWorldModelArena(cache, all))
    {
        glf.CreateBuffers(1, &cache.vbo);
        if (cache.vbo)
            glf.NamedBufferStorage(cache.vbo,
                                   GLsizeiptr(all.size() * sizeof(WorldVertexGPU)),
                                   all.data(), GL_DYNAMIC_STORAGE_BIT_);
    }
    const bool cpuColorStream = cache.arenaResident && AppendCpuWorldModelColors(cache, all);

    // WorldModel Gouraud/LightAnim vertex colours are deliberately kept in the
    // cache VBO instead of sampled from the shared GPU LightAnim SSBO.  The
    // cache builder above has already sampled the exact current Talon RGB for
    // every dirty Gouraud vertex, and UpdateVertexLighting() refreshes those
    // VBO vertices whenever the corresponding LightAnim changes.
    //
    // This makes a brush WorldModel's colour independent of PVS-visible cache
    // ordering / SSBO arena state.  The static PhysicsBSP retains the GPU
    // LightAnim path; only independently-instanced WorldModels use this
    // deterministic CPU-sampled VBO path.
    cache.vertexLightArenaResident = false;
    cache.vertexLightArenaWordOffset = 0;
    if (cache.vertexLightSsbo)
    {
        glf.DeleteBuffers(1, &cache.vertexLightSsbo);
        cache.vertexLightSsbo = 0;
    }

    if (LogIsSessionEnabled())
    {
        float minLight = 1.0f, maxLight = 0.0f;
        for (const BatchBuild &b : builds)
        {
            for (const WorldVertexGPU &v : b.vertices)
            {
                minLight = std::min(minLight, std::min(v.r, std::min(v.g, v.b)));
                maxLight = std::max(maxLight, std::max(v.r, std::max(v.g, v.b)));
            }
        }

        LOG_SESSION("World3D WORLDMODEL CACHE bsp=%p name='%s' flags=%08X polies=%u verts=%u batches=%u bakedLightRange=%.3f..%.3f lmColorVerts=%u lmTextureVerts=%u fallbackLitVerts=%u unlitVerts=%u gouraudNoLmRaw=%u gouraudNoLmDirty=%u arena=%d arenaFirst=%u gpuLightArena=%d gpuLightWord=%u cpuColorStream=%d",
                    bsp, bsp->m_szWorldName, bsp->m_dwWorldInfoFlags, cache.totalPolys, cache.totalVerts,
                    unsigned(cache.batches.size()), minLight, maxLight,
                    lmColorVerts, lmTextureVerts, fallbackLitVerts, unlitVerts,
                    gouraudNoLmRawVerts, gouraudNoLmDirtyVerts,
                    cache.arenaResident ? 1 : 0, cache.arenaFirstVertex,
                    cache.vertexLightArenaResident ? 1 : 0, cache.vertexLightArenaWordOffset, cpuColorStream ? 1 : 0);
    }

    return cache.arenaResident || cache.vbo != 0;
}

static GLint WorldModelFirstVertex(const WorldModelCache *c, const WorldBatch &b)
{
    const uint64_t base = (c && c->arenaResident) ? c->arenaFirstVertex : 0u;
    return static_cast<GLint>(base + b.firstVertex);
}

static WorldBlendMode InstanceBlend(const WorldModelInstanceCompat *wm, WorldBlendMode surf)
{
    uint32 f = wm->m_Base.m_dwFlags2;
    if (f & (1u << 2))
        return WorldBlendMode::Additive;
    if (f & (1u << 3))
        return WorldBlendMode::Multiply;
    if (wm->m_Base.m_nColorA < 255)
        return WorldBlendMode::Alpha;
    return surf;
}

static WorldModelPhase BatchPhase(const WorldModelInstanceCompat *wm, const WorldBatch &b)
{
    if (InstanceBlend(wm, b.blend) != WorldBlendMode::Solid)
        return WorldModelPhase::Translucent;
    if (wm && (wm->m_Base.m_dwFlags2 & FLAG2_CHROMAKEY))
        return WorldModelPhase::ChromaKey;
    return WorldModelPhase::Opaque;
}

static void ApplyWorldBatchCull(const TalonRenderState &state, bool translucentPhase = false)
{
    (void)state;

    if (translucentPhase)
    {
        DisableWorldBackfaceCulling();
        return;
    }

    // Talon's world winding maps to clockwise front faces in this renderer.
    EnableWorldBackfaceCulling();
}

static float WorldBatchDistanceSq(const WorldModelInstanceCompat *wm, const WorldBatch &b, const LTVector &camera)
{
    const float lx = (b.minX + b.maxX) * 0.5f;
    const float ly = (b.minY + b.maxY) * 0.5f;
    const float lz = (b.minZ + b.maxZ) * 0.5f;
    const LTMatrix &m = wm->m_mTransform;
    const float x = m.m[0][0] * lx + m.m[0][1] * ly + m.m[0][2] * lz + m.m[0][3];
    const float y = m.m[1][0] * lx + m.m[1][1] * ly + m.m[1][2] * lz + m.m[1][3];
    const float z = m.m[2][0] * lx + m.m[2][1] * ly + m.m[2][2] * lz + m.m[2][3];
    const float dx = x - camera.x, dy = y - camera.y, dz = z - camera.z;
    return dx * dx + dy * dy + dz * dz;
}

void WorldModelRenderer::BindGpuVertexLight(const WorldModelCache *c) const
{
    if (c && c->vertexLightArenaResident && m_state.vertexLightArenaSsbo)
    {
        ::BindGpuVertexLight(m_state.vertexLightArenaSsbo,
                             c->arenaResident ? c->arenaFirstVertex : 0u,
                             c->vertexLightArenaWordOffset);
        return;
    }

    ::BindGpuVertexLight(c ? c->vertexLightSsbo : 0,
                         (c && c->arenaResident) ? c->arenaFirstVertex : 0u, 0u);
}

void WorldModelRenderer::UpdateVertexLighting(MainWorldCompat *world)
{
    if (!world || LightmapState().changedLightAnimPolys.empty())
        return;

    uint32 touchedCaches = 0;
    uint32 touchedVerts = 0;

    // The main/static PhysicsBSP uses LightAnim vertex colours for authored
    // Gouraud/flat-shaded polygons that have no texture lightmap.  This is the
    // same compiled data source as the WorldModel path below; update it when a
    // LightAnim/LightGroup state changes instead of leaving the initial colours
    // frozen in the VBO.
    if (!StaticState().vertexLightSsbo && WorldState().vbo && !StaticState().cpuVertices.empty() &&
        StaticState().vertexLightRefs.size() == StaticState().cpuVertices.size())
    {
        bool dirty = false;
        size_t dirtyFirst = StaticState().cpuVertices.size();
        size_t dirtyLast = 0;
        for (size_t i = 0; i < StaticState().cpuVertices.size(); ++i)
        {
            const WorldModelVertexLightRef &ref = StaticState().vertexLightRefs[i];
            if (!ref.poly || LightmapState().changedLightAnimPolys.find(ref.poly) == LightmapState().changedLightAnimPolys.end())
                continue;

            float r = 0.0f, g = 0.0f, b = 0.0f;
            if (!WorldRenderer::Instance().Lighting().SampleAnimatedVertexColor(world, ref.poly, ref.vert, r, g, b))
                continue;

            WorldVertexGPU &v = StaticState().cpuVertices[i];
            if (fabsf(v.r - r) > 0.0005f || fabsf(v.g - g) > 0.0005f || fabsf(v.b - b) > 0.0005f)
            {
                v.r = r;
                v.g = g;
                v.b = b;
                dirty = true;
                dirtyFirst = std::min(dirtyFirst, i);
                dirtyLast = std::max(dirtyLast, i);
                ++touchedVerts;
            }
        }

        if (dirty)
        {
            const size_t count = dirtyLast - dirtyFirst + 1;
            GLTrackedWorldNamedBufferSubData(WorldState().vbo,
                                             static_cast<GLintptr>(dirtyFirst * sizeof(WorldVertexGPU)),
                                             static_cast<GLsizeiptr>(count * sizeof(WorldVertexGPU)),
                                             StaticState().cpuVertices.data() + dirtyFirst, GLWorldUploadKind::VertexStatic);
            ++touchedCaches;
        }
    }

    for (auto &kv : WorldRenderer::Instance().WorldModels().State().caches)
    {
        WorldModelCache &c = kv.second;
        const GLuint targetVbo = (c.arenaResident && WorldRenderer::Instance().WorldModels().State().arenaVbo)
                                     ? WorldRenderer::Instance().WorldModels().State().arenaVbo
                                     : c.vbo;
        if (c.vertexLightSsbo || c.vertexLightArenaResident ||
            !targetVbo || c.cpuVertices.empty() ||
            c.lightRefs.size() != c.cpuVertices.size())
            continue;

        bool dirty = false;
        size_t dirtyFirst = c.cpuVertices.size();
        size_t dirtyLast = 0;

        for (size_t i = 0; i < c.cpuVertices.size(); ++i)
        {
            const WorldModelVertexLightRef &ref = c.lightRefs[i];
            if (!ref.poly || LightmapState().changedLightAnimPolys.find(ref.poly) == LightmapState().changedLightAnimPolys.end())
                continue;

            float r = 0.0f, g = 0.0f, b = 0.0f;
            if (!WorldRenderer::Instance().Lighting().SampleAnimatedVertexColor(world, ref.poly, ref.vert, r, g, b))
                continue;

            WorldVertexGPU &v = c.cpuVertices[i];
            if (fabsf(v.r - r) > 0.0005f || fabsf(v.g - g) > 0.0005f || fabsf(v.b - b) > 0.0005f)
            {
                v.r = r;
                v.g = g;
                v.b = b;
                dirty = true;
                dirtyFirst = std::min(dirtyFirst, i);
                dirtyLast = std::max(dirtyLast, i);
                ++touchedVerts;
            }
        }

        if (dirty)
        {
            const size_t count = dirtyLast - dirtyFirst + 1;
            auto &st = WorldRenderer::Instance().WorldModels().State();
            if (c.arenaResident && st.cpuColorSsbo && st.cpuColorMapped && st.cpuColorCapacity)
            {
                const size_t globalFirst = size_t(c.arenaFirstVertex) + dirtyFirst;
                const size_t firstFloat = globalFirst * 3u;
                const size_t neededFloats = (globalFirst + count) * 3u;
                if (st.cpuColorArena.size() >= neededFloats)
                {
                    float *dst = reinterpret_cast<float *>(
                        static_cast<unsigned char *>(st.cpuColorMapped) + size_t(st.submissionFrameSlot) * st.cpuColorCapacity);
                    for (size_t j = 0; j < count; ++j)
                    {
                        const WorldVertexGPU &v = c.cpuVertices[dirtyFirst + j];
                        const size_t f = firstFloat + j * 3u;
                        st.cpuColorArena[f + 0u] = v.r;
                        st.cpuColorArena[f + 1u] = v.g;
                        st.cpuColorArena[f + 2u] = v.b;
                        dst[f + 0u] = v.r;
                        dst[f + 1u] = v.g;
                        dst[f + 2u] = v.b;
                    }
                    GLUploadStats::Instance().RecordWorldStreamWrite(
                        GLWorldUploadKind::VertexUpdates, count * 3u * sizeof(float));
                }
                else
                {
                    GLTrackedWorldNamedBufferSubData(targetVbo,
                                                     static_cast<GLintptr>((size_t(c.arenaFirstVertex) + dirtyFirst) * sizeof(WorldVertexGPU)),
                                                     static_cast<GLsizeiptr>(count * sizeof(WorldVertexGPU)),
                                                     c.cpuVertices.data() + dirtyFirst, GLWorldUploadKind::VertexFallback);
                }
            }
            else
            {
                GLTrackedWorldNamedBufferSubData(targetVbo,
                                                 static_cast<GLintptr>((size_t(c.arenaResident ? c.arenaFirstVertex : 0u) + dirtyFirst) * sizeof(WorldVertexGPU)),
                                                 static_cast<GLsizeiptr>(count * sizeof(WorldVertexGPU)),
                                                 c.cpuVertices.data() + dirtyFirst, GLWorldUploadKind::VertexFallback);
            }
            ++touchedCaches;
        }
    }

    static uint32 budget = 120;
    if (LogIsSessionEnabled() && ((touchedCaches || touchedVerts) && budget && (--budget, true)))
        LOG_SESSION("World3D LM VERTEX UPDATE caches=%u verts=%u", touchedCaches, touchedVerts);
}

static bool DrawOneWorldModelPhase(MainWorldCompat *world,
                                   WorldModelInstanceCompat *wm,
                                   WorldModelPhase phase,
                                   uint32 &draws, uint64_t &tris,
                                   uint32 &batchesDrawn, uint32 &polys,
                                   const LTVector *cameraPos = nullptr)
{
    if (!world || !wm || !(wm->m_Base.m_dwFlags & FLAG_VISIBLE) || !wm->m_pOriginalBsp)
        return false;
    WorldModelCache *c = WorldRenderer::Instance().WorldModels().GetOrCreateCache(world, wm->m_pOriginalBsp);
    if (!c || !WorldRenderer::Instance().WorldModels().BindGeometry(c))
        return false;

    WorldRenderer::Instance().WorldModels().BindGpuVertexLight(c);
    BindCpuWorldModelColor(c->arenaResident);
    SetWorldModelTransform(wm);
    const bool gridOK = EnsureLightGridTexture(world);
    GLStateBindTextureUnit(2, gridOK ? LightmapState().lightGridTexture : 0);
    const bool ck = (wm->m_Base.m_dwFlags2 & FLAG2_CHROMAKEY) != 0;
    const bool stockTranslucent = (phase == WorldModelPhase::Translucent);

    // A WorldModel may contain a mix of opaque and translucent surfaces.
    // Retail sorts the object into the translucent list if it has transparent
    // content, but that does not mean every surface in the brush becomes alpha
    // blended.  Select only batches that actually belong to this phase.
    std::vector<const WorldBatch *> phaseBatches;
    phaseBatches.reserve(c->batches.size());
    for (const WorldBatch &b : c->batches)
        if (BatchPhase(wm, b) == phase)
            phaseBatches.push_back(&b);
    if (phaseBatches.empty())
        return false;

    // Within one translucent brush, render coarse material batches back to
    // front.  The outer Talon translucent queue already sorts whole objects;
    // this fixes the second level of ordering that was previously left in cache
    // construction order.
    if (stockTranslucent && cameraPos && phaseBatches.size() > 1)
    {
        std::stable_sort(phaseBatches.begin(), phaseBatches.end(),
                         [&](const WorldBatch *a, const WorldBatch *b)
                         {
                             return WorldBatchDistanceSq(wm, *a, *cameraPos) >
                                    WorldBatchDistanceSq(wm, *b, *cameraPos);
                         });
    }

    // d3d.ren's outer translucent object list disables ZWRITE before invoking
    // the WorldModel callback.  Individual authored render states may still
    // provide explicit depth overrides below.
    if (stockTranslucent)
    {
        GLStateEnable(GL_BLEND);
        GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLStateDepthMask(GL_FALSE);
    }

    for (const WorldBatch *bp : phaseBatches)
    {
        const WorldBatch &b = *bp;
        WorldMaterialSystem::Instance().ApplyTexFx(b);
        const WorldBlendMode blend = InstanceBlend(wm, b.blend);

        Texture *t = WorldMaterialSystem::Instance().Apply(b);
        SharedTexture *stateTexture = WorldMaterialSystem::Instance().ResolveBatchTexture(b);
        const TalonRenderState d3dState = TalonRenderStateSystem::Instance().Decode(stateTexture);
        ApplyWorldBatchCull(d3dState, stockTranslucent);
        GLStateBindTextureUnit(1, LightmapState().atlas);
        GLUniform1i(U("uTextured"), t && t->texture ? 1 : 0);
        GLUniform1i(U("uLightmapped"), LightmapState().atlas ? 1 : 0);
        GLUniform1i(U("uNoLight"), b.noLight ? 1 : 0);
        GLUniform1i(U("uWorldModelLightmapGouraud"), b.lightmapGouraud ? 1 : 0);
        GLUniform1i(U("uWorldModelGouraud"), (b.lightmapGouraud || b.gouraudNoLightmap) ? 1 : 0);
        // Gouraud-only WorldModels carry their compiled static lighting in the
        // authored/LightAnim vertex stream. Adding the world LightTable again
        // makes dark brush ends bright and exposes a discontinuity at every
        // polygon boundary.
        GLUniform1i(U("uWorldModelBakedOnly"), b.gouraudNoLightmap ? 1 : 0);
        GLUniform1i(U("uUseGridLight"), gridOK ? 1 : 0);
        // d3d.ren classifies a WorldModel into the chromakey visible set from
        // FLAG2_CHROMAKEY.  A texture carrying alpha/AlphaRef by itself does
        // NOT turn BSP-backed WorldModel geometry into chromakey.
        float ar = 0.0f;
        if (ck && phase == WorldModelPhase::ChromaKey)
        {
            ar = t ? t->alphaRef : b.alphaRef;
            if (ar <= 0.0f)
                ar = 0.5f + (0.5f / 255.0f);
        }
        const bool stateAlphaTest = d3dState.hasAlphaTestEnable && d3dState.alphaTestEnable;
        const bool alphaTest = (ar > 0.0f) || stateAlphaTest;
        if (stateAlphaTest)
            ar = TalonRenderStateSystem::Instance().AlphaRef01(
                d3dState, ar > 0.0f ? ar : (0.5f + 0.5f / 255.0f));
        GLUniform1i(U("uAlphaTest"), alphaTest ? 1 : 0);
        GLUniform1f(U("uAlphaRef"), ar);
        GLUniform1i(U("uAlphaFunc"), alphaTest
                                         ? static_cast<GLint>(d3dState.hasAlphaFunc ? d3dState.alphaFunc : 7u)
                                         : 7);

        // against d3d.ren without regressing ordinary doors/brushes.
        if (stockTranslucent && b.hasLightmap)
        {
            static uint32 s_twmLightDiagBudget = 256;
            if (LogIsSessionEnabled() && (s_twmLightDiagBudget))
            {
                --s_twmLightDiagBudget;
                const char *wmName = wm->m_pOriginalBsp ? wm->m_pOriginalBsp->m_szWorldName : "";
                uint32 firstSurf = 0;
                if (wm->m_pOriginalBsp && wm->m_pOriginalBsp->m_pPolies &&
                    wm->m_pOriginalBsp->m_dwPolies &&
                    wm->m_pOriginalBsp->m_pPolies[0] &&
                    wm->m_pOriginalBsp->m_pPolies[0]->m_pSurface)
                    firstSurf = wm->m_pOriginalBsp->m_pPolies[0]->m_pSurface->m_dwFlags;
                LOG_SESSION("World3D TWM-LIGHT-DIAG name='%s' obj=%p firstSurf=%08X flags=%08X flags2=%08X batchLightmap=%u extraShade=%u noLight=%u batchBlend=%u instBlend=%u alphaRef=%.4f grid=%u atlas=%u",
                            wmName, wm, firstSurf, wm->m_Base.m_dwFlags, wm->m_Base.m_dwFlags2,
                            b.hasLightmap ? 1u : 0u, b.extraShade ? 1u : 0u, b.noLight ? 1u : 0u,
                            unsigned(b.blend), unsigned(blend), ar, (gridOK && b.extraShade) ? 1u : 0u,
                            LightmapState().atlas ? 1u : 0u);
            }
        }
        WorldMaterialSystem::Instance().ApplyBlend(blend);
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);
        if (d3dState.hasAlphaBlendEnable)
        {
            if (d3dState.alphaBlendEnable)
            {
                GLStateEnable(GL_BLEND);
                const uint32 src = d3dState.hasSrcBlend ? d3dState.srcBlend : 5u;
                const uint32 dst = d3dState.hasDestBlend ? d3dState.destBlend : 6u;
                GLStateBlendFunc(
                    static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(src)),
                    static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(dst)));
            }
            else
                GLStateDisable(GL_BLEND);
        }
        if (d3dState.hasZEnable && !d3dState.zEnable)
            GLStateDisable(GL_DEPTH_TEST);
        else if (d3dState.hasZFunc)
            GLStateDepthFunc(static_cast<GLenum>(TalonRenderStateSystem::Instance().MapCompareToGL(d3dState.zFunc)));
        if (d3dState.hasZWriteEnable)
            GLStateDepthMask(d3dState.zWriteEnable ? GL_TRUE : GL_FALSE);
        if (stockTranslucent && !d3dState.hasZWriteEnable)
            GLStateDepthMask(GL_FALSE);
        GLUniform1i(U("uFogEnabled"),
                    (d3dState.hasFogEnable ? (d3dState.fogEnable && g_fogState.enabled) : g_fogState.enabled) ? 1 : 0);
        glf.DrawArrays(GL_TRIANGLES_, WorldModelFirstVertex(c, b), GLsizei(b.vertexCount));
        ++draws;
        tris += b.vertexCount / 3;
        ++batchesDrawn;
    }

    polys += c->totalPolys;
    return true;
}

static void RestoreWorldModelDrawState()
{
    glf.VertexArrayVertexBuffer(WorldState().vao, 0, WorldState().vbo, 0, sizeof(WorldVertexGPU));
    WorldSurfaceFxSystem::Instance().BindUvOverride(WorldState().vbo);
    BindGpuVertexLight(StaticState().vertexLightSsbo);
    BindCpuWorldModelColor(false);
    GLUniform1i(U("uUseGridLight"), 0);
    GLUniform1ui(U("uLegacyDrawFlags"), 0u);
    GLUniform1i(U("uWorldModelLightmapGouraud"), 0);
    GLUniform1i(U("uWorldModelGouraud"), 0);
    GLUniform1i(U("uWorldModelBakedOnly"), 0);
    SetIdentityWorldTransform();
}

static uint32 FloatBits(float v)
{
    uint32 u = 0;
    std::memcpy(&u, &v, sizeof(u));
    return u;
}

static bool WmInstanceFullyMdiEligible(MainWorldCompat *world,
                                       WorldModelInstanceCompat *wm,
                                       WorldModelPhase phase,
                                       WorldModelCache *&outCache)
{
    outCache = nullptr;
    if (!world || !wm || !(wm->m_Base.m_dwFlags & FLAG_VISIBLE) ||
        !wm->m_pOriginalBsp || !WorldRenderer::Instance().WorldModels().State().arenaVbo ||
        !glf.MultiDrawArraysIndirect || !glf.BindBuffer)
        return false;
    if (phase != WorldModelPhase::Opaque &&
        phase != WorldModelPhase::ChromaKey)
        return false;
    WorldModelCache *c = WorldRenderer::Instance().WorldModels().GetOrCreateCache(world, wm->m_pOriginalBsp);
    if (!c || !c->arenaResident)
        return false;

    // Keep any WorldModel that consumes authored/LightAnim vertex colours out
    // of the global MDI submission path.  The MDI draw-state array is rebuilt
    // from the current PVS-visible set, while Gouraud vertex-light descriptors
    // are cache-local.  Crossing a PVS boundary can therefore reorder MDI
    // commands and make a coloured WorldModel sample another cache's lighting
    // payload if either base is ever mismatched.  The per-cache path is still
    // fully modern OpenGL (VAO/VBO/SSBO/shaders); it simply binds the matching
    // vertex-light buffer/base explicitly for that cache and is deterministic
    // across PVS changes.
    if (HasAnyVertexLightRef(c->lightRefs))
        return false;

    for (const WorldBatch &b : c->batches)
    {
        // The MDI submission currently emits every batch in the cache.  Keep
        // mixed-phase brushes on the per-cache path until MDI carries a phase
        // mask per command; otherwise an opaque submission could accidentally
        // draw the brush's translucent surfaces too.
        if (BatchPhase(wm, b) != phase)
            return false;
    }

    outCache = c;
    return !c->batches.empty();
}

static uint32 DrawVisibleWorldModelsMdi(MainWorldCompat *world,
                                        WorldModelPhase phase,
                                        uint32 &draws, uint64_t &tris,
                                        uint32 &batchesDrawn, uint32 &polys,
                                        std::unordered_set<WorldModelInstanceCompat *> &batchedInstances,
                                        uint32 &outGroups, uint32 &outCommands)
{
    outGroups = 0;
    outCommands = 0;
    if (!world || (phase != WorldModelPhase::Opaque && phase != WorldModelPhase::ChromaKey) ||
        !WorldRenderer::Instance().WorldModels().State().arenaVbo || !glf.MultiDrawArraysIndirect || !glf.BindBuffer)
        return 0;

    struct TempDraw
    {
        WorldModelInstanceCompat *wm = nullptr;
        WorldModelCache *cache = nullptr;
        const WorldBatch *batch = nullptr;
        float alphaRef = 0.0f;
    };
    struct TempGroup
    {
        WmMdiMaterialKey key{};
        const WorldBatch *material = nullptr;
        float alphaRef = 0.0f;
        std::vector<TempDraw> draws;
    };

    std::vector<TempGroup> groups;
    std::unordered_map<WmMdiMaterialKey, size_t, WmMdiMaterialKeyHash> groupMap;
    groups.reserve(64);
    groupMap.reserve(128);

    uint32 renderedInstances = 0;
    uint32 gpuVertexLightInstances = 0;
    uint32 mdiPolys = 0;
    for (WorldModelInstanceCompat *wm : PVSState().visibleWorldModels)
    {
        WorldModelCache *c = nullptr;
        if (!WmInstanceFullyMdiEligible(world, wm, phase, c))
            continue;

        ++renderedInstances;
        if (c->vertexLightArenaResident)
            ++gpuVertexLightInstances;
        batchedInstances.insert(wm);
        mdiPolys += c->totalPolys;

        const bool ck = (phase == WorldModelPhase::ChromaKey);
        for (const WorldBatch &b : c->batches)
        {
            float alphaRef = 0.0f;
            if (ck)
            {
                SharedTexture *liveTexture = WorldMaterialSystem::Instance().ResolveBatchTexture(b);
                Texture *liveGl = TextureManager::Instance().GetOrEnsure(liveTexture);
                alphaRef = liveGl ? liveGl->alphaRef : b.alphaRef;
                if (alphaRef <= 0.0f)
                    alphaRef = 0.5f + (0.5f / 255.0f);
            }

            WmMdiMaterialKey key{};
            key.texture = b.texture;
            key.animatedSurface = b.animatedSurface;
            key.fxHash = b.texFx.hash;
            key.alphaBits = FloatBits(alphaRef);
            key.noLight = b.noLight ? 1u : 0u;
            key.extraShade = b.extraShade ? 1u : 0u;
            key.lightmapGouraud = b.lightmapGouraud ? 1u : 0u;
            key.gouraudNoLightmap = b.gouraudNoLightmap ? 1u : 0u;
            key.phase = (phase == WorldModelPhase::ChromaKey) ? 1u : 0u;

            size_t gi = 0;
            auto it = groupMap.find(key);
            if (it == groupMap.end())
            {
                gi = groups.size();
                groupMap.emplace(key, gi);
                groups.push_back({});
                groups.back().key = key;
                groups.back().material = &b;
                groups.back().alphaRef = alphaRef;
            }
            else
            {
                gi = it->second;
            }

            groups[gi].draws.push_back({wm, c, &b, alphaRef});
        }
    }

    size_t totalCommands = 0;
    for (const TempGroup &g : groups)
        totalCommands += g.draws.size();
    if (totalCommands == 0 || !EnsureWmSubmissionBuffers(totalCommands))
    {
        batchedInstances.clear();
        return 0;
    }

    std::vector<DrawArraysIndirectCommandGPU> commands;
    std::vector<WmDrawStateGPU> states;
    commands.reserve(totalCommands);
    states.reserve(totalCommands);

    std::vector<WmMdiGroup> flatGroups;
    flatGroups.reserve(groups.size());

    for (const TempGroup &g : groups)
    {
        WmMdiGroup fg{};
        fg.key = g.key;
        fg.material = g.material;
        fg.alphaRef = g.alphaRef;
        fg.firstCommand = static_cast<uint32>(commands.size());

        uint32 materialParamIndex = 0;
        if (g.material)
            WorldMaterialSystem::Instance().PrepareMaterialParamIndex(*g.material, materialParamIndex);

        for (const TempDraw &d : g.draws)
        {
            DrawArraysIndirectCommandGPU cmd{};
            cmd.count = d.batch->vertexCount;
            cmd.instanceCount = 1u;
            cmd.first = d.cache->arenaFirstVertex + d.batch->firstVertex;
            cmd.baseInstance = static_cast<uint32>(states.size());
            commands.push_back(cmd);
            states.push_back(MakeWmDrawState(d.wm, d.cache, materialParamIndex));
            tris += d.batch->vertexCount / 3;
            ++batchesDrawn;
        }

        fg.commandCount = static_cast<uint32>(commands.size()) - fg.firstCommand;
        if (fg.commandCount)
            flatGroups.push_back(std::move(fg));
    }

    if (commands.empty())
    {
        batchedInstances.clear();
        return 0;
    }

    WmSubmissionUpload submission{};
    if (!UploadWmSubmission(states, commands, submission))
    {
        batchedInstances.clear();
        return 0;
    }

    glf.VertexArrayVertexBuffer(WorldState().vao, 0, WorldRenderer::Instance().WorldModels().State().arenaVbo, 0, sizeof(WorldVertexGPU));
    WorldSurfaceFxSystem::Instance().BindUvOverride(WorldRenderer::Instance().WorldModels().State().arenaVbo);
    BindGpuVertexLight(WorldRenderer::Instance().WorldModels().State().vertexLightArenaSsbo);
    BindCpuWorldModelColor(true);
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 7, submission.stateBuffer);
    glf.BindBuffer(GL_DRAW_INDIRECT_BUFFER_, submission.commandBuffer);
    GLUniform1i(U("uUseWmDrawState"), 1);
    GLUniform1i(U("uUseWorld"), 1);

    const bool gridOK = EnsureLightGridTexture(world);
    GLStateBindTextureUnit(2, gridOK ? LightmapState().lightGridTexture : 0);
    GLStateDisable(GL_BLEND);
    GLStateDepthMask(GL_TRUE);

    for (const WmMdiGroup &g : flatGroups)
    {
        if (!g.material)
            continue;
        const WorldBatch &b = *g.material;
        WorldMaterialSystem::Instance().ApplyTexFx(b);
        Texture *t = WorldMaterialSystem::Instance().Apply(b, true);
        SharedTexture *stateTexture = WorldMaterialSystem::Instance().ResolveBatchTexture(b);
        const TalonRenderState d3dState = TalonRenderStateSystem::Instance().Decode(stateTexture);
        // The MDI path bypasses DrawOneWorldModelPhase(), so it must establish
        // the same one-sided WorldModel cull state explicitly per material group.
        ApplyWorldBatchCull(d3dState);
        GLStateBindTextureUnit(1, LightmapState().atlas);
        GLUniform1i(U("uTextured"), t && t->texture ? 1 : 0);
        GLUniform1i(U("uLightmapped"), LightmapState().atlas ? 1 : 0);
        GLUniform1i(U("uNoLight"), b.noLight ? 1 : 0);
        GLUniform1i(U("uWorldModelLightmapGouraud"), b.lightmapGouraud ? 1 : 0);
        GLUniform1i(U("uWorldModelGouraud"), (b.lightmapGouraud || b.gouraudNoLightmap) ? 1 : 0);
        GLUniform1i(U("uWorldModelBakedOnly"), b.gouraudNoLightmap ? 1 : 0);
        GLUniform1i(U("uUseGridLight"), gridOK ? 1 : 0);
        GLUniform1i(U("uFogAdditive"), 0);
        const bool stateAlphaTest = d3dState.hasAlphaTestEnable && d3dState.alphaTestEnable;
        float mdiAlphaRef = g.alphaRef;
        if (stateAlphaTest)
            mdiAlphaRef = TalonRenderStateSystem::Instance().AlphaRef01(
                d3dState, mdiAlphaRef > 0.0f ? mdiAlphaRef : (0.5f + 0.5f / 255.0f));
        const bool mdiAlphaTest = mdiAlphaRef > 0.0f || stateAlphaTest;
        GLUniform1i(U("uAlphaTest"), mdiAlphaTest ? 1 : 0);
        GLUniform1f(U("uAlphaRef"), mdiAlphaRef);
        GLUniform1i(U("uAlphaFunc"), mdiAlphaTest
                                         ? static_cast<GLint>(d3dState.hasAlphaFunc ? d3dState.alphaFunc : 7u)
                                         : 7);
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);
        GLStateDisable(GL_BLEND);
        GLStateDepthMask(GL_TRUE);
        if (d3dState.hasAlphaBlendEnable)
        {
            if (d3dState.alphaBlendEnable)
            {
                GLStateEnable(GL_BLEND);
                const uint32 src = d3dState.hasSrcBlend ? d3dState.srcBlend : 5u;
                const uint32 dst = d3dState.hasDestBlend ? d3dState.destBlend : 6u;
                GLStateBlendFunc(
                    static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(src)),
                    static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(dst)));
            }
            else
                GLStateDisable(GL_BLEND);
        }
        if (d3dState.hasZEnable && !d3dState.zEnable)
            GLStateDisable(GL_DEPTH_TEST);
        else if (d3dState.hasZFunc)
            GLStateDepthFunc(static_cast<GLenum>(TalonRenderStateSystem::Instance().MapCompareToGL(d3dState.zFunc)));
        if (d3dState.hasZWriteEnable)
            GLStateDepthMask(d3dState.zWriteEnable ? GL_TRUE : GL_FALSE);
        GLUniform1i(U("uFogEnabled"),
                    (d3dState.hasFogEnable ? (d3dState.fogEnable && g_fogState.enabled) : g_fogState.enabled) ? 1 : 0);

        const uintptr_t offset = static_cast<uintptr_t>(submission.commandByteOffset) +
                                 static_cast<uintptr_t>(g.firstCommand) * sizeof(DrawArraysIndirectCommandGPU);
        glf.MultiDrawArraysIndirect(GL_TRIANGLES_,
                                    reinterpret_cast<const void *>(offset),
                                    static_cast<GLsizei>(g.commandCount), 0);
        ++draws;
    }

    glf.BindBuffer(GL_DRAW_INDIRECT_BUFFER_, 0);
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 7, 0);
    GLUniform1i(U("uUseWmDrawState"), 0);

    outGroups = static_cast<uint32>(flatGroups.size());
    outCommands = static_cast<uint32>(commands.size());
    polys += mdiPolys;

    static uint32 budget = 120;
    if (LogIsSessionEnabled() && (budget))
    {
        --budget;
        LOG_SESSION("World3D WM-MDI phase=%s instances=%u gpuVertexLightInstances=%u commands=%u materialGroups=%u arenaVerts=%u vertexLightWords=%u path=GLOBAL-VBO/GLOBAL-LIGHT-SSBO/TRANSFORM-SSBO/MULTIDRAW-INDIRECT",
                    phase == WorldModelPhase::ChromaKey ? "chromakey" : "opaque",
                    renderedInstances, gpuVertexLightInstances, outCommands, outGroups,
                    WorldRenderer::Instance().WorldModels().State().arenaUsedVertices,
                    static_cast<unsigned>(WorldRenderer::Instance().WorldModels().State().vertexLightArenaCpu.size()));
    }

    return renderedInstances;
}

void WorldModelRenderer::RenderVisiblePhase(MainWorldCompat *world,
                                            WorldModelPhase phase,
                                            uint32 &draws, uint64_t &tris)
{
    if (!StockRenderOptions::Instance().DrawWorldModels())
        return;
    uint32 rendered = 0, polys = 0, batchesDrawn = 0, classVisible = 0;
    for (WorldModelInstanceCompat *wm : PVSState().visibleWorldModels)
    {
        if (wm && (wm->m_Base.m_dwFlags & FLAG_VISIBLE) && wm->m_pOriginalBsp &&
            WorldRenderer::Instance().WorldModels().HasPhase(wm, phase))
            ++classVisible;
    }

    std::unordered_set<WorldModelInstanceCompat *> mdiInstances;
    mdiInstances.reserve(classVisible * 2u + 1u);
    uint32 mdiGroups = 0, mdiCommands = 0;
    rendered += DrawVisibleWorldModelsMdi(world, phase, draws, tris, batchesDrawn, polys,
                                          mdiInstances, mdiGroups, mdiCommands);

    for (WorldModelInstanceCompat *wm : PVSState().visibleWorldModels)
    {
        if (!wm || !(wm->m_Base.m_dwFlags & FLAG_VISIBLE) || !wm->m_pOriginalBsp)
            continue;
        if (!WorldRenderer::Instance().WorldModels().HasPhase(wm, phase))
            continue;
        if (mdiInstances.find(wm) != mdiInstances.end())
            continue;
        if (DrawOneWorldModelPhase(world, wm, phase, draws, tris, batchesDrawn, polys))
            ++rendered;
    }

    RestoreWorldModelDrawState();

    if (LogIsSessionEnabled())
    {
        static uint32 prevOpaque = 0xFFFFFFFFu, prevCK = 0xFFFFFFFFu, prevTrans = 0xFFFFFFFFu;
        static uint32 prevOpaqueVisible = 0xFFFFFFFFu, prevCKVisible = 0xFFFFFFFFu, prevTransVisible = 0xFFFFFFFFu;
        uint32 *prev = &prevOpaque;
        uint32 *prevVisible = &prevOpaqueVisible;
        const char *phaseName = "opaque";
        if (phase == WorldModelPhase::ChromaKey)
        {
            prev = &prevCK;
            prevVisible = &prevCKVisible;
            phaseName = "chromakey";
        }
        else if (phase == WorldModelPhase::Translucent)
        {
            prev = &prevTrans;
            prevVisible = &prevTransVisible;
            phaseName = "translucent";
        }
        if (*prev != rendered || *prevVisible != classVisible)
        {
            *prev = rendered;
            *prevVisible = classVisible;
            LOG_SESSION("World3D WORLDMODEL PHASE %s classVisible=%u rendered=%u batches=%u cachedPolys=%u totalPVS=%u mdiGroups=%u mdiCommands=%u classifier=PER_BATCH",
                        phaseName, classVisible, rendered, batchesDrawn, polys, PVSState().visibleWorldModelCount,
                        mdiGroups, mdiCommands);
        }
    }

}

bool WorldModelRenderer::NeedsCpuVertexLightFallback() const
{
    if (!StaticState().vertexLightSsbo)
    {
        for (const WorldModelVertexLightRef &r : StaticState().vertexLightRefs)
            if (r.poly)
                return true;
    }

    for (const auto &kv : WorldRenderer::Instance().WorldModels().State().caches)
    {
        const WorldModelCache &c = kv.second;
        if (c.vertexLightSsbo || c.vertexLightArenaResident)
            continue;
        for (const WorldModelVertexLightRef &r : c.lightRefs)
            if (r.poly)
                return true;
    }
    return false;
}

bool WorldModelRenderer::BindGeometry(const WorldModelCache *c) const
{
    if (!c)
        return false;
    if (c->arenaResident && WorldRenderer::Instance().WorldModels().State().arenaVbo)
    {
        glf.VertexArrayVertexBuffer(WorldState().vao, 0, WorldRenderer::Instance().WorldModels().State().arenaVbo, 0, sizeof(WorldVertexGPU));
        WorldSurfaceFxSystem::Instance().BindUvOverride(WorldRenderer::Instance().WorldModels().State().arenaVbo);
        return true;
    }
    if (c->vbo)
    {
        glf.VertexArrayVertexBuffer(WorldState().vao, 0, c->vbo, 0, sizeof(WorldVertexGPU));
        WorldSurfaceFxSystem::Instance().BindUvOverride(c->vbo);
        return true;
    }
    return false;
}

WorldModelCache *WorldModelRenderer::GetOrCreateCache(MainWorldCompat *world, WorldBspCompat *bsp)
{
    auto it = WorldRenderer::Instance().WorldModels().State().caches.find(bsp);
    if (it != WorldRenderer::Instance().WorldModels().State().caches.end())
        return &it->second;
    WorldModelCache c{};
    if (!BuildWorldModelCache(world, bsp, c))
        return nullptr;
    auto r = WorldRenderer::Instance().WorldModels().State().caches.emplace(bsp, std::move(c));
    WorldSurfaceFxSystem::Instance().RegisterTargets(bsp, r.first->second.batches, false);
    return &r.first->second;
}

void WorldModelRenderer::RenderDeferred(SceneDesc *scene, WorldModelPhase phase)
{
    if (!StockRenderOptions::Instance().DrawWorldModels())
        return;
    if (!scene || scene->m_nDrawMode == DRAWMODE_OBJECTLIST || !scene->m_pRenderContext ||
        !scene->m_pRenderContext->m_pMainWorld)
        return;

    auto *world = reinterpret_cast<MainWorldCompat *>(scene->m_pRenderContext->m_pMainWorld);
    WorldRenderer::Instance().SetupScene(scene);

    uint32 draws = 0;
    uint64_t tris = 0;
    RenderVisiblePhase(world,
                       phase,
                       draws, tris);
    DisableWorldBackfaceCulling();
    GLStateDepthMask(GL_TRUE);
    GLStateDisable(GL_BLEND);
}

void WorldModelRenderer::RenderTranslucent(SceneDesc *scene, WorldModelInstanceCompat *wm)
{
    if (!StockRenderOptions::Instance().DrawWorldModels())
        return;
    if (!scene || !wm || scene->m_nDrawMode == DRAWMODE_OBJECTLIST ||
        !scene->m_pRenderContext || !scene->m_pRenderContext->m_pMainWorld)
        return;

    auto *world = reinterpret_cast<MainWorldCompat *>(scene->m_pRenderContext->m_pMainWorld);
    WorldRenderer::Instance().SetupScene(scene);

    uint32 draws = 0, batches = 0, polys = 0;
    uint64_t tris = 0;
    DrawOneWorldModelPhase(world, wm, WorldModelPhase::Translucent,
                           draws, tris, batches, polys, &scene->m_vPos);
    static int transNameBudget = 128;
    if (LogIsSessionEnabled() && ((transNameBudget > 0 && transNameBudget--)))
        LOG_SESSION("World3D TRANS-WM DRAW name='%s' obj=%p draws=%u batches=%u polys=%u tris=%llu flags=%08X flags2=%08X",
                    wm->m_pOriginalBsp ? wm->m_pOriginalBsp->m_szWorldName : "", wm, draws, batches, polys,
                    static_cast<unsigned long long>(tris), wm->m_Base.m_dwFlags, wm->m_Base.m_dwFlags2);
    RestoreWorldModelDrawState();
    DisableWorldBackfaceCulling();
    // Keep the outer sorted-translucent contract intact.  The caller may draw
    // a model/sprite immediately after this object.
    GLStateDepthMask(GL_FALSE);
}
