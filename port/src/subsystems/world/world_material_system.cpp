#include "subsystems/renderer/Console.h"
#include "world_material_system.h"
#include "world_renderer.h"
#include "../textures/texture_manager.h"
#include "deluxe_lightmap_baker.h"
#include "material_authoring.h"
#include "../../gl_loader.h"
#include "utils/log.h"
#include "subsystems/renderer/fog_state.h"
#include "../../shaders/shader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "subsystems/renderer/renderer_core.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <unordered_set>
#include <unordered_map>

WorldMaterialSystem &WorldMaterialSystem::Instance()
{
    static WorldMaterialSystem v;
    return v;
}

void WorldMaterialSystem::Init(avp2::render::Shader *shader)
{
    Reset();
    if (!shader)
        return;
    m_state.uTexFxMask = shader->Uniform("uTexFxMask");
    m_state.uTexFxParams0 = shader->Uniform("uTexFxParams0");
    m_state.uTexFxParams1 = shader->Uniform("uTexFxParams1");
    m_state.uTexFxParams2 = shader->Uniform("uTexFxParams2");
    m_state.uTexFxTime = shader->Uniform("uTexFxTime");
    m_state.uPanSkyEnabled = shader->Uniform("uPanSkyEnabled");
    m_state.uLinkedTexMode = shader->Uniform("uLinkedTexMode");
    m_state.uLinkedParams0 = shader->Uniform("uLinkedParams0");
    m_state.uLinkedParams1 = shader->Uniform("uLinkedParams1");
    m_state.uLinkedParams2 = shader->Uniform("uLinkedParams2");
    m_state.uUseWorldMaterialParams = shader->Uniform("uUseWorldMaterialParams");
    m_state.uWorldMaterialParamIndex = shader->Uniform("uWorldMaterialParamIndex");
    m_state.uFogAdditive = shader->Uniform("uFogAdditive");
    m_state.uFullBrightTexture = shader->Uniform("uFullBrightTexture");
    m_state.uAuthoredNormalEnabled = shader->Uniform("uAuthoredNormalEnabled");
    m_state.uAuthoredSpecularEnabled = shader->Uniform("uAuthoredSpecularEnabled");
    m_state.uAuthoredNormalStrength = shader->Uniform("uAuthoredNormalStrength");
    m_state.uAuthoredSpecularStrength = shader->Uniform("uAuthoredSpecularStrength");
    m_state.uAuthoredGlossMinPower = shader->Uniform("uAuthoredGlossMinPower");
    m_state.uAuthoredGlossMaxPower = shader->Uniform("uAuthoredGlossMaxPower");
    m_state.uAuthoredGlossBias = shader->Uniform("uAuthoredGlossBias");
    m_state.uAuthoredReflectionMode = shader->Uniform("uAuthoredReflectionMode");
    m_state.uAuthoredReflectionMapEnabled = shader->Uniform("uAuthoredReflectionMapEnabled");
    m_state.uAuthoredReflectionStrength = shader->Uniform("uAuthoredReflectionStrength");
}

namespace
{
    constexpr size_t WORLD_MATERIAL_STREAM_FRAMES = 3u;
    constexpr size_t WORLD_MATERIAL_SEGMENT_ENTRIES = 4096u;
    constexpr size_t WORLD_MATERIAL_SEGMENT_BYTES = WORLD_MATERIAL_SEGMENT_ENTRIES * 64u;
    constexpr GLuint WORLD_MATERIAL_SSBO_BINDING = 11u;

    struct WorldMaterialParamGPU
    {
        float linked0[4];
        float linked1[4];
        float linked2[4];
        uint32 info[4]; // x=linked texture mode, y=DTX_FULLBRITE
    };
    static_assert(sizeof(WorldMaterialParamGPU) == 64, "WorldMaterialParamGPU std430 mismatch");

    struct WorldMaterialParamKey
    {
        uint32 bits[16]{};
        bool operator==(const WorldMaterialParamKey &o) const
        {
            return std::memcmp(bits, o.bits, sizeof(bits)) == 0;
        }
    };
    struct WorldMaterialParamKeyHash
    {
        size_t operator()(const WorldMaterialParamKey &k) const
        {
            size_t h = 2166136261u;
            for (uint32 v : k.bits)
            {
                h ^= size_t(v);
                h *= 16777619u;
            }
            return h;
        }
    };

    GLuint g_worldMaterialParamSsbo = 0;
    void *g_worldMaterialParamMapped = nullptr;
    uint32 g_worldMaterialFrameSlot = 0;
    size_t g_worldMaterialCursor = 0;
    void *g_worldMaterialFences[WORLD_MATERIAL_STREAM_FRAMES]{};
    bool g_worldMaterialUsedThisFrame = false;
    bool g_worldMaterialBoundThisFrame = false;
    std::unordered_map<WorldMaterialParamKey, uint32, WorldMaterialParamKeyHash> g_worldMaterialParamCache;
    WorldMaterialPerfStats g_materialPerf{};

    static int64_t MaterialPerfNow()
    {
        if (!RendererCore::Instance().PerfTimingActive()) return 0;
        LARGE_INTEGER q{}; QueryPerformanceCounter(&q); return q.QuadPart;
    }
    static double MaterialPerfMs(int64_t a, int64_t b)
    {
        if (!a || !b || b <= a) return 0.0;
        static LARGE_INTEGER f = []{ LARGE_INTEGER v{}; QueryPerformanceFrequency(&v); return v; }();
        return f.QuadPart ? (1000.0 * double(b-a) / double(f.QuadPart)) : 0.0;
    }

    static void DestroyWorldMaterialParamStream()
    {
        for (void *&fence : g_worldMaterialFences)
        {
            if (fence && glf.DeleteSync)
                glf.DeleteSync(fence);
            fence = nullptr;
        }
        if (g_worldMaterialParamSsbo && glf.DeleteBuffers)
            glf.DeleteBuffers(1, &g_worldMaterialParamSsbo);
        g_worldMaterialParamSsbo = 0;
        g_worldMaterialParamMapped = nullptr;
        g_worldMaterialFrameSlot = 0;
        g_worldMaterialCursor = 0;
        g_worldMaterialUsedThisFrame = false;
        g_worldMaterialBoundThisFrame = false;
        g_worldMaterialParamCache.clear();
    }

    static bool EnsureWorldMaterialParamStream()
    {
        if (g_worldMaterialParamSsbo && g_worldMaterialParamMapped)
            return true;
        if (!glf.CreateBuffers || !glf.NamedBufferStorage || !glf.MapNamedBufferRange ||
            !glf.FenceSync || !glf.ClientWaitSync || !glf.DeleteSync || !glf.BindBufferBase)
            return false;

        GLuint buffer = 0;
        glf.CreateBuffers(1, &buffer);
        if (!buffer)
            return false;
        const size_t total = WORLD_MATERIAL_SEGMENT_BYTES * WORLD_MATERIAL_STREAM_FRAMES;
        const GLbitfield flags = GL_MAP_WRITE_BIT_ | GL_MAP_PERSISTENT_BIT_ | GL_MAP_COHERENT_BIT_;
        glf.NamedBufferStorage(buffer, static_cast<GLsizeiptr>(total), nullptr, flags);
        void *mapped = glf.MapNamedBufferRange(buffer, 0, static_cast<GLsizeiptr>(total), flags);
        if (!mapped)
        {
            glf.DeleteBuffers(1, &buffer);
            return false;
        }
        g_worldMaterialParamSsbo = buffer;
        g_worldMaterialParamMapped = mapped;
        LOG_SESSION("World3D MATERIAL-PARAM stream ready segmentBytes=%llu totalBytes=%llu binding=%u path=PERSISTENT-SSBO",
                    static_cast<unsigned long long>(WORLD_MATERIAL_SEGMENT_BYTES),
                    static_cast<unsigned long long>(total), unsigned(WORLD_MATERIAL_SSBO_BINDING));
        return true;
    }

    static bool StreamWorldMaterialParams(const WorldMaterialParamGPU &params, uint32 &outIndex)
    {
        if (!EnsureWorldMaterialParamStream())
            return false;

        WorldMaterialParamKey key{};
        std::memcpy(key.bits, &params, sizeof(params));
        const auto found = g_worldMaterialParamCache.find(key);
        if (found != g_worldMaterialParamCache.end())
        {
            outIndex = found->second;
            return true;
        }

        const size_t aligned = ((g_worldMaterialCursor + sizeof(WorldMaterialParamGPU) - 1u) / sizeof(WorldMaterialParamGPU)) * sizeof(WorldMaterialParamGPU);
        if (aligned + sizeof(params) > WORLD_MATERIAL_SEGMENT_BYTES)
            return false;
        const size_t absolute = size_t(g_worldMaterialFrameSlot) * WORLD_MATERIAL_SEGMENT_BYTES + aligned;
        std::memcpy(static_cast<unsigned char *>(g_worldMaterialParamMapped) + absolute, &params, sizeof(params));
        GLUploadStats::Instance().RecordWorldStreamWrite(GLWorldUploadKind::Other, sizeof(params));
        g_worldMaterialCursor = aligned + sizeof(params);
        outIndex = static_cast<uint32>(absolute / sizeof(WorldMaterialParamGPU));
        g_worldMaterialParamCache.emplace(key, outIndex);
        g_worldMaterialUsedThisFrame = true;
        return true;
    }
}

void WorldMaterialSystem::Reset()
{
    DestroyWorldMaterialParamStream();
    MaterialAuthoringSystem::Instance().Reset();
    m_state = WorldMaterialSystemState{};
}

uint32 WorldMaterialSystem::HashTexFx(const WorldTexFx &fx) const
{
    auto bits = [](float f)
    {uint32 u=0;memcpy(&u,&f,4);return u; };
    uint32 h = 2166136261u;
    auto mix = [&](uint32 v)
    {h^=v;h*=16777619u; };
    mix(fx.mask);
    mix(bits(fx.panU));
    mix(bits(fx.panV));
    mix(bits(fx.rotateDegPerSec));
    mix(bits(fx.warbleScale));
    mix(bits(fx.warbleSpeed));
    return h;
}

WorldTexFx WorldMaterialSystem::BuildTexFx(const SurfaceCompat *sf) const
{
    WorldTexFx fx{};
    if (!sf)
        return fx;

    // Talon does NOT derive world-surface pan/rotate/warble timing from the
    // texture command string in the renderer.  The engine updates the live
    // Surface::O/P/Q basis for entries in MainWorld::m_pSurfaceEffects.
    // Keep only the separate SURF_PANNINGSKY path here.
    if (sf->m_dwFlags & SURF_PANNINGSKY)
        fx.mask |= WTFX_PANSKY;

    fx.hash = HashTexFx(fx);
    static std::unordered_set<uint32> logged;
    if (LogIsSessionEnabled() && (fx.mask && logged.insert(fx.hash).second))
    {
        auto *st = reinterpret_cast<const SharedTextureCompat *>(sf->m_pTexture);
        LOG_SESSION("World3D TEXFX mask=%08X stockPanningSky=1 cmd='%s' surfFlags=%08X",
                    fx.mask, st ? st->m_szCommandString : "", sf->m_dwFlags);
    }
    return fx;
}

WorldBlendMode WorldMaterialSystem::ClassifyBlend(uint32 f) const
{
    if (f & SURF_ADDITIVE)
        return WorldBlendMode::Additive;
    if (f & SURF_TRANSPARENT)
        return WorldBlendMode::Alpha;
    return WorldBlendMode::Solid;
}

void WorldMaterialSystem::ApplyTexFx(const WorldBatch &b)
{
    uint32 mask = b.texFx.mask;
    float offX = 0.0f, offZ = 0.0f;
    float stockScaleU = 0.0f, stockScaleV = 0.0f;
    int panSkyEnabled = 0;

    // SURF_PANNINGSKY does NOT replace the polygon's base texture UVs.
    // Stock Talon renders the normal world polygon first, then projects the
    // registered global cloud texture over that polygon as a modulation pass
    // to simulate moving cloud-cover shadows.
    if ((mask & WTFX_PANSKY) != 0u)
    {
        const GlobalPanInfo *pi = nullptr;
        RenderStruct *rs = WorldRenderer::Instance().GetRenderStruct();
        if (rs)
        {
            // d3d.ren points its panning-sky renderer at the first
            // GlobalPanInfo entry (RenderStruct + the GlobalPanInfo offset).
            // The surface's own texture remains the base texture; m_pTexture
            // here is the separate cloud-shadow overlay texture.
            const GlobalPanInfo &cand = rs->m_GlobalPanInfo[0];
            if (cand.m_pTexture)
                pi = &cand;
        }

        if (pi && std::fabs(pi->m_fPanSkyScaleX) > 1e-8f &&
            std::fabs(pi->m_fPanSkyScaleZ) > 1e-8f)
        {
            Texture *pan = TextureManager::Instance().Ensure(pi->m_pTexture, false);
            if (pan && pan->texture)
            {
                const float invW = pan->scaledWidth ? 1.0f / float(pan->scaledWidth)
                                                    : (pan->width ? 1.0f / float(pan->width) : 1.0f);
                const float invH = pan->scaledHeight ? 1.0f / float(pan->scaledHeight)
                                                     : (pan->height ? 1.0f / float(pan->height) : 1.0f);

                offX = pi->m_fCurSkyXOffset;
                offZ = pi->m_fCurSkyZOffset;

                // d3d.ren 0x10007930 + 0x10007C26 computes the projected
                // overlay coordinates from world X/Z.  The base UV remains
                // untouched and is still used for the world texture.
                stockScaleU = invW / pi->m_fPanSkyScaleX;
                stockScaleV = invH / pi->m_fPanSkyScaleZ;

                GLStateBindTextureUnit(3, pan->texture);
                panSkyEnabled = 1;

                static SharedTexture *s_lastPanTexture = nullptr;
                if (LogIsSessionEnabled() && (s_lastPanTexture != pi->m_pTexture))
                {
                    s_lastPanTexture = pi->m_pTexture;
                    LOG_SESSION("World3D PANNINGSKY overlay tex=%p GL=%u size=%ux%u offset=(%.3f %.3f) scale=(%.6f %.6f) mode=cloud-shadow-modulate",
                                pi->m_pTexture, pan->texture, pan->scaledWidth, pan->scaledHeight,
                                offX, offZ, pi->m_fPanSkyScaleX, pi->m_fPanSkyScaleZ);
                }
            }
        }

        if (!panSkyEnabled)
            mask &= ~WTFX_PANSKY;
    }

    if (!panSkyEnabled)
        GLStateBindTextureUnit(3, 0);

    GLUniform1ui(m_state.uTexFxMask, mask);
    GLUniform1i(m_state.uPanSkyEnabled, panSkyEnabled);
    GLUniform4f(m_state.uTexFxParams0, b.texFx.panU, b.texFx.panV, b.texFx.rotateDegPerSec, b.texFx.warbleScale);
    GLUniform4f(m_state.uTexFxParams1, b.texFx.warbleSpeed, offX, offZ, 0.0f);
    GLUniform4f(m_state.uTexFxParams2, stockScaleU, stockScaleV, 0.0f, 0.0f);
    GLUniform1f(m_state.uTexFxTime, float(GetTickCount64() * 0.001));
}

SharedTexture *WorldMaterialSystem::ResolveBatchTexture(const WorldBatch &b) const
{
    if (b.animatedSurface &&
        (b.animatedSurface->m_dwFlags & SURF_SPRITEANIMATE) &&
        b.animatedSurface->m_pTexture)
    {
        // Talon advances the Surface pointer in the engine.  Do not cache the
        // frame in the BSP batch: each SharedTexture already caches its GLuint
        // directly in m_pRenderData, so this hot path is just two pointer loads.
        // No map lookup, DTX parse, allocation, or GL upload occurs for a frame
        // that has already been seen.
        return b.animatedSurface->m_pTexture;
    }
    return b.texture;
}

struct TalonMaterialConsoleState
{
    float detailTextures = 1.0f;
    float detailTextureAdd = 1.0f;
    float detailTextureScale = 0.2f;
    float envMapWorld = 1.0f;
    std::uint64_t lastReadMs = ~std::uint64_t(0);
};

static const TalonMaterialConsoleState &GetTalonMaterialConsoleState()
{
    static TalonMaterialConsoleState s{};
    const std::uint64_t now = static_cast<std::uint64_t>(GetTickCount64());
    if (s.lastReadMs == ~std::uint64_t(0) || now - s.lastReadMs >= 100u)
    {
        s.detailTextures = Console::Instance().GetFloat("DetailTextures", 1.0f);
        s.detailTextureAdd = Console::Instance().GetFloat("DetailTextureAdd", 1.0f);
        s.detailTextureScale = Console::Instance().GetFloat("DetailTextureScale", 0.2f);
        s.envMapWorld = Console::Instance().GetFloat("EnvMapWorld", 1.0f);
        s.lastReadMs = now;
    }
    return s;
}

// Bind the Talon base/linked texture pair and reproduce the stock fixed-function
// linked-texture modes recovered from AVP2 d3d.ren 0x1000A538:
//   m_eTexType 0 + linked = detail texture
//   m_eTexType 1          = environment map
//   m_eTexType 2          = environment-map-alpha
// DetailTextureAdd defaults to 1 in the renderer, selecting
// D3DTOP_ADDSIGNED for detail and ordinary environment maps.
Texture *WorldMaterialSystem::Apply(const WorldBatch &b, bool materialIndexFromDrawState, uint32 *outMaterialParamIndex)
{
    const bool materialPerf = RendererCore::Instance().PerfTimingActive();
    const int64_t materialApplyStart = materialPerf ? MaterialPerfNow() : 0;
    if (materialPerf) ++g_materialPerf.applyCalls;

    SharedTexture *baseShared = ResolveBatchTexture(b);
    // Sky must validate against Talon's current TextureData every draw/batch;
    // authored sky UVs are source-texel coordinates and stale dimensions are catastrophic.
    Texture *base = TextureManager::Instance().Ensure(baseShared, false);
    GLStateBindTextureUnit(0, base ? base->texture : 0);

    // Loose authored material companions live below ./textures and take
    // precedence over the albedo-derived fallback when present.
    const int64_t authoredResolveStart = materialPerf ? MaterialPerfNow() : 0;
    const AuthoredMaterialBinding *authored = baseShared ? MaterialAuthoringSystem::Instance().Resolve(baseShared) : nullptr;
    const int64_t authoredResolveEnd = materialPerf ? MaterialPerfNow() : 0;
    if (materialPerf)
    {
        g_materialPerf.authoredResolveMs += MaterialPerfMs(authoredResolveStart, authoredResolveEnd);
        if (authored) ++g_materialPerf.authoredBindings;
    }
    const int64_t authoredStateStart = materialPerf ? MaterialPerfNow() : 0;
    const GLuint authoredNormal = authored ? authored->normalTexture : 0;
    const GLuint authoredSpecular = authored ? authored->specularTexture : 0;
    GLStateBindTextureUnit(12, authoredNormal);
    GLStateBindTextureUnit(13, authoredSpecular);
    const GLuint authoredReflection = authored ? authored->reflectionTexture : 0;
    GLStateBindTextureUnit(14, authoredReflection);
    if (m_state.uAuthoredNormalEnabled >= 0) GLUniform1i(m_state.uAuthoredNormalEnabled, authoredNormal ? 1 : 0);
    if (m_state.uAuthoredSpecularEnabled >= 0) GLUniform1i(m_state.uAuthoredSpecularEnabled, authoredSpecular ? 1 : 0);
    const AuthoredMaterialSettings authoredDefaults{};
    const AuthoredMaterialSettings &ams = authored ? authored->settings : authoredDefaults;
    if (m_state.uAuthoredNormalStrength >= 0) GLUniform1f(m_state.uAuthoredNormalStrength, ams.normalStrength);
    if (m_state.uAuthoredSpecularStrength >= 0) GLUniform1f(m_state.uAuthoredSpecularStrength, ams.specularStrength);
    if (m_state.uAuthoredGlossMinPower >= 0) GLUniform1f(m_state.uAuthoredGlossMinPower, ams.glossMinPower);
    if (m_state.uAuthoredGlossMaxPower >= 0) GLUniform1f(m_state.uAuthoredGlossMaxPower, ams.glossMaxPower);
    if (m_state.uAuthoredGlossBias >= 0) GLUniform1f(m_state.uAuthoredGlossBias, ams.glossBias);
    // Reflection mode 0 preserves the legacy SSR receiver heuristic for materials
    // without a .mat. Once a .mat exists, reflection_strength/map become authoritative.
    if (m_state.uAuthoredReflectionMode >= 0) GLUniform1i(m_state.uAuthoredReflectionMode, (authored && authored->materialFileExists) ? 1 : 0);
    if (m_state.uAuthoredReflectionMapEnabled >= 0) GLUniform1i(m_state.uAuthoredReflectionMapEnabled, authoredReflection ? 1 : 0);
    if (m_state.uAuthoredReflectionStrength >= 0) GLUniform1f(m_state.uAuthoredReflectionStrength, ams.reflectionStrength);
    const int64_t authoredStateEnd = materialPerf ? MaterialPerfNow() : 0;
    if (materialPerf) g_materialPerf.authoredStateMs += MaterialPerfMs(authoredStateStart, authoredStateEnd);

    const int64_t derivedStart = materialPerf ? MaterialPerfNow() : 0;
    // Cached albedo-derived gradient/luminance map for deluxe material response.
    // Build lazily only while the deluxe material path can actually consume it.
    GLuint derivedMaterial = base ? base->materialTexture : 0;
    const auto &deluxe = DeluxeLightmapBaker::Instance();
    const bool needDerived = deluxe.Texture() != 0 && deluxe.SpecularEnabled() &&
                             (deluxe.GeneratedNormalEnabled() || deluxe.GeneratedSpecularEnabled());
    if (needDerived && !derivedMaterial && baseShared)
        derivedMaterial = TextureManager::Instance().GetOrCreateDerivedMaterial(baseShared);
    GLStateBindTextureUnit(6, needDerived ? derivedMaterial : 0);
    const int64_t derivedEnd = materialPerf ? MaterialPerfNow() : 0;
    if (materialPerf) g_materialPerf.derivedMs += MaterialPerfMs(derivedStart, derivedEnd);

    const float baseW = (base && base->scaledWidth) ? float(base->scaledWidth)
                                                    : ((base && base->width) ? float(base->width) : 1.0f);
    const float baseH = (base && base->scaledHeight) ? float(base->scaledHeight)
                                                     : ((base && base->height) ? float(base->height) : 1.0f);

    // Cached SPolyVertex UVs were normalized by the frame that was active when
    // the BSP cache was built. Talon SPR animation changes Surface::m_pTexture
    // live, so compensate if a later frame has a different scaled size.
    const float uvScaleX = (b.animatedSurface && baseW > 0.0f) ? (b.uvNormWidth / baseW) : 1.0f;
    const float uvScaleY = (b.animatedSurface && baseH > 0.0f) ? (b.uvNormHeight / baseH) : 1.0f;

    const TalonMaterialConsoleState &materialCV = GetTalonMaterialConsoleState();
    int linkedMode = 0;
    Texture *linked = nullptr;
    SharedTexture *linkedShared = nullptr;
    uint32 texType = 0;

    if (baseShared)
    {
        auto *st = reinterpret_cast<SharedTextureCompat *>(baseShared);
        linkedShared = reinterpret_cast<SharedTexture *>(st->m_pLinkedTexture);
        texType = st->m_eTexType;
        if (linkedShared)
        {
            linked = TextureManager::Instance().GetOrEnsure(linkedShared);
            if (linked && linked->texture)
            {
                // Exact Talon console switches recovered from d3d.ren. Query
                // the engine parameter table so user overrides behave like
                // stock; the fallback values are the defaults.
                if (texType == 0u && materialCV.detailTextures != 0.0f)
                    linkedMode = 1;
                else if (texType == 1u && materialCV.envMapWorld != 0.0f)
                    linkedMode = 2;
                else if (texType == 2u && materialCV.envMapWorld != 0.0f)
                    linkedMode = 3;
            }
            else
            {
                static std::unordered_set<uintptr_t> s_failedLinkedTextures;
                const uintptr_t key = reinterpret_cast<uintptr_t>(linkedShared);
                if (LogIsSessionEnabled() && (s_failedLinkedTextures.size() < 64 && s_failedLinkedTextures.insert(key).second))
                    LOG_SESSION("TALON-LINKTEX unresolved base=%p linked=%p texType=%u",
                                baseShared, linkedShared, static_cast<unsigned>(texType));
            }
        }
    }

    GLStateBindTextureUnit(4, (linkedMode != 0 && linked) ? linked->texture : 0);

    float detailScale = 1.0f, detailCos = 1.0f, detailSin = 0.0f, linkedInvW = 1.0f, linkedInvH = 1.0f;
    if (linked)
    {
        const float linkedW = linked->scaledWidth ? float(linked->scaledWidth)
                                                  : (linked->width ? float(linked->width) : 1.0f);
        const float linkedH = linked->scaledHeight ? float(linked->scaledHeight)
                                                   : (linked->height ? float(linked->height) : 1.0f);
        linkedInvW = 1.0f / linkedW;
        linkedInvH = 1.0f / linkedH;
        // d3d.ren 0x1000A682 reads RTexture+0x34/+0x38/+0x3C from
        // texture stage 0 -- the BASE texture -- after binding the linked
        // detail texture on stage 1.  Detail scale/angle therefore belong to
        // the base DTX, not the linked detail DTX.
        detailScale = materialCV.detailTextureScale * (base ? base->detailScale : 1.0f);
        detailCos = base ? base->detailCos : 1.0f;
        detailSin = base ? base->detailSin : 0.0f;
    }
    const float detailAdd = materialCV.detailTextureAdd;

    WorldMaterialParamGPU materialParams{};
    materialParams.linked0[0] = uvScaleX;
    materialParams.linked0[1] = uvScaleY;
    materialParams.linked0[2] = baseW;
    materialParams.linked0[3] = baseH;
    materialParams.linked1[0] = detailScale;
    materialParams.linked1[1] = detailCos;
    materialParams.linked1[2] = detailSin;
    materialParams.linked1[3] = linkedInvW;
    materialParams.linked2[0] = linkedInvH;
    materialParams.linked2[1] = detailAdd;
    materialParams.info[0] = static_cast<uint32>(linkedMode);
    materialParams.info[1] = (base && base->fullBright) ? 1u : 0u;

    uint32 materialParamIndex = 0;
    if (outMaterialParamIndex)
        *outMaterialParamIndex = 0;
    if (StreamWorldMaterialParams(materialParams, materialParamIndex))
    {
        if (!g_worldMaterialBoundThisFrame)
        {
            glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, WORLD_MATERIAL_SSBO_BINDING, g_worldMaterialParamSsbo);
            g_worldMaterialBoundThisFrame = true;
        }
        GLUniform1i(m_state.uUseWorldMaterialParams, 1);
        if (outMaterialParamIndex)
            *outMaterialParamIndex = materialParamIndex;
        if (!materialIndexFromDrawState)
            GLUniform1ui(m_state.uWorldMaterialParamIndex, materialParamIndex);
    }
    else
    {
        GLUniform1i(m_state.uUseWorldMaterialParams, 0);
        GLUniform1i(m_state.uLinkedTexMode, linkedMode);
        GLUniform4f(m_state.uLinkedParams0, uvScaleX, uvScaleY, baseW, baseH);
        GLUniform4f(m_state.uLinkedParams1, detailScale, detailCos, detailSin, linkedInvW);
        GLUniform4f(m_state.uLinkedParams2, linkedInvH, detailAdd, 0.0f, 0.0f);
        GLUniform1i(m_state.uFullBrightTexture, (base && base->fullBright) ? 1 : 0);
    }

    if (LogIsSessionEnabled() && linkedMode != 0)
    {
        static std::unordered_set<uint64_t> s_logged;
        const uint64_t key = (uint64_t(reinterpret_cast<uintptr_t>(baseShared)) << 3) ^
                             uint64_t(reinterpret_cast<uintptr_t>(linkedShared)) ^ uint64_t(linkedMode);
        if (LogIsSessionEnabled() && (s_logged.size() < 256 && s_logged.insert(key).second))
        {
            const char *mode = (linkedMode == 1) ? "DETAIL" : ((linkedMode == 2) ? "ENVMAP" : "ENVMAPALPHA");
            LOG_SESSION("TALON-LINKTEX mode=%s base=%p GL=%u linked=%p GL=%u texType=%u baseSize=%.0fx%.0f detailScale=%.4f angle=%d",
                        mode, baseShared, base ? base->texture : 0, linkedShared, linked ? linked->texture : 0,
                        texType, baseW, baseH, detailScale, base ? int(base->detailAngle) : 0);
        }
    }

    if (materialPerf) g_materialPerf.applyMs += MaterialPerfMs(materialApplyStart, MaterialPerfNow());
    return base;
}

WorldMaterialPerfStats WorldMaterialSystem::ConsumePerfStats()
{
    WorldMaterialPerfStats out = g_materialPerf;
    g_materialPerf = {};
    return out;
}

bool WorldMaterialSystem::PrepareMaterialParamIndex(const WorldBatch &b, uint32 &outIndex)
{
    SharedTexture *baseShared = ResolveBatchTexture(b);
    Texture *base = TextureManager::Instance().Ensure(baseShared, false);
    const float baseW = (base && base->scaledWidth) ? float(base->scaledWidth)
                                                    : ((base && base->width) ? float(base->width) : 1.0f);
    const float baseH = (base && base->scaledHeight) ? float(base->scaledHeight)
                                                     : ((base && base->height) ? float(base->height) : 1.0f);
    const float uvScaleX = (b.animatedSurface && baseW > 0.0f) ? (b.uvNormWidth / baseW) : 1.0f;
    const float uvScaleY = (b.animatedSurface && baseH > 0.0f) ? (b.uvNormHeight / baseH) : 1.0f;

    const TalonMaterialConsoleState &materialCV = GetTalonMaterialConsoleState();
    int linkedMode = 0;
    Texture *linked = nullptr;
    if (baseShared)
    {
        auto *st = reinterpret_cast<SharedTextureCompat *>(baseShared);
        auto *linkedShared = reinterpret_cast<SharedTexture *>(st->m_pLinkedTexture);
        const uint32 texType = st->m_eTexType;
        if (linkedShared)
        {
            linked = TextureManager::Instance().GetOrEnsure(linkedShared);
            if (linked && linked->texture)
            {
                if (texType == 0u && materialCV.detailTextures != 0.0f)
                    linkedMode = 1;
                else if (texType == 1u && materialCV.envMapWorld != 0.0f)
                    linkedMode = 2;
                else if (texType == 2u && materialCV.envMapWorld != 0.0f)
                    linkedMode = 3;
            }
        }
    }

    float detailScale = 1.0f, detailCos = 1.0f, detailSin = 0.0f, linkedInvW = 1.0f, linkedInvH = 1.0f;
    if (linked)
    {
        const float linkedW = linked->scaledWidth ? float(linked->scaledWidth)
                                                  : (linked->width ? float(linked->width) : 1.0f);
        const float linkedH = linked->scaledHeight ? float(linked->scaledHeight)
                                                   : (linked->height ? float(linked->height) : 1.0f);
        linkedInvW = 1.0f / linkedW;
        linkedInvH = 1.0f / linkedH;
        detailScale = materialCV.detailTextureScale * (base ? base->detailScale : 1.0f);
        detailCos = base ? base->detailCos : 1.0f;
        detailSin = base ? base->detailSin : 0.0f;
    }

    WorldMaterialParamGPU materialParams{};
    materialParams.linked0[0] = uvScaleX;
    materialParams.linked0[1] = uvScaleY;
    materialParams.linked0[2] = baseW;
    materialParams.linked0[3] = baseH;
    materialParams.linked1[0] = detailScale;
    materialParams.linked1[1] = detailCos;
    materialParams.linked1[2] = detailSin;
    materialParams.linked1[3] = linkedInvW;
    materialParams.linked2[0] = linkedInvH;
    materialParams.linked2[1] = materialCV.detailTextureAdd;
    materialParams.info[0] = static_cast<uint32>(linkedMode);
    materialParams.info[1] = (base && base->fullBright) ? 1u : 0u;
    return StreamWorldMaterialParams(materialParams, outIndex);
}

void WorldMaterialSystem::AdvanceStreamFrame()
{
    if (!g_worldMaterialParamSsbo || !g_worldMaterialParamMapped ||
        !glf.FenceSync || !glf.ClientWaitSync || !glf.DeleteSync || !glf.BindBufferBase)
    {
        g_worldMaterialCursor = 0;
        g_worldMaterialParamCache.clear();
        g_worldMaterialBoundThisFrame = false;
        g_worldMaterialUsedThisFrame = false;
        return;
    }

    if (g_worldMaterialUsedThisFrame)
    {
        if (g_worldMaterialFences[g_worldMaterialFrameSlot])
            glf.DeleteSync(g_worldMaterialFences[g_worldMaterialFrameSlot]);
        g_worldMaterialFences[g_worldMaterialFrameSlot] = glf.FenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE_, 0);
    }

    const uint32 next = (g_worldMaterialFrameSlot + 1u) % static_cast<uint32>(WORLD_MATERIAL_STREAM_FRAMES);
    if (g_worldMaterialFences[next])
    {
        const GLenum wait = glf.ClientWaitSync(g_worldMaterialFences[next], GL_SYNC_FLUSH_COMMANDS_BIT_, GL_TIMEOUT_IGNORED_);
        if (wait == GL_WAIT_FAILED_)
            LOG_SESSION("World3D MATERIAL-PARAM stream: glClientWaitSync failed on slot %u", next);
        glf.DeleteSync(g_worldMaterialFences[next]);
        g_worldMaterialFences[next] = nullptr;
    }
    g_worldMaterialFrameSlot = next;
    g_worldMaterialCursor = 0;
    g_worldMaterialParamCache.clear();
    g_worldMaterialBoundThisFrame = false;
    g_worldMaterialUsedThisFrame = false;
}

void WorldMaterialSystem::ApplyBlend(WorldBlendMode b)
{
    GLUniform1i(m_state.uFogAdditive, b == WorldBlendMode::Additive ? 1 : 0);
    if (b == WorldBlendMode::Solid)
    {
        GLStateDisable(GL_BLEND);
        GLStateDepthMask(GL_TRUE);
    }
    else if (b == WorldBlendMode::Alpha)
    {
        GLStateEnable(GL_BLEND);
        GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLStateDepthMask(GL_FALSE);
    }
    else if (b == WorldBlendMode::Additive)
    {
        GLStateEnable(GL_BLEND);
        GLStateBlendFunc(GL_ONE, GL_ONE);
        GLStateDepthMask(GL_FALSE);
    }
    else
    {
        GLStateEnable(GL_BLEND);
        GLStateBlendFunc(GL_DST_COLOR, GL_ZERO);
        GLStateDepthMask(GL_FALSE);
    }
}
