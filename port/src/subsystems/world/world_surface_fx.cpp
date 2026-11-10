#include "world_surface_fx.h"
#include "world_renderer.h"
#include "world_static_geometry.h"
#include "world_model_renderer.h"
#include "../textures/texture_manager.h"
#include "../../gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "utils/log.h"
#include "../../shaders/shader.h"
#include <algorithm>
#include <cstring>
#include <limits>
#include <unordered_map>
#include <unordered_set>

WorldSurfaceFxSystem &WorldSurfaceFxSystem::Instance()
{
    static WorldSurfaceFxSystem v;
    return v;
}

static WorldStaticGeometryState &StaticState() { return WorldStaticGeometryRenderer::Instance().State(); }
static WorldRendererState &WorldState() { return WorldRenderer::Instance().State(); }

namespace
{
    constexpr size_t SURFACEFX_STREAM_FRAMES = 3u;
    constexpr size_t SURFACEFX_STREAM_MIN_SEGMENT = 256u * 1024u;

    static size_t AlignSurfaceFx(size_t v) { return (v + 255u) & ~size_t(255u); }

    static bool EnsureUvStream(GLuint sourceVbo, size_t requiredVertices)
    {
        if (!sourceVbo || !requiredVertices || !glf.MapNamedBufferRange ||
            !glf.FenceSync || !glf.ClientWaitSync || !glf.DeleteSync)
            return false;

        auto &state = WorldSurfaceFxSystem::Instance().State();
        SurfaceFxUvStream &stream = state.uvStreams[sourceVbo];
        const size_t requiredBytes = requiredVertices * 4u * sizeof(float);
        if (stream.buffer && stream.mapped && requiredBytes <= stream.segmentBytes)
        {
            const size_t oldFloats = stream.cpuUv.size();
            const size_t newFloats = requiredVertices * 4u;
            if (oldFloats < newFloats)
            {
                stream.cpuUv.resize(newFloats, 0.0f);
                const size_t growBytes = (newFloats - oldFloats) * sizeof(float);
                for (size_t slot = 0; slot < SURFACEFX_STREAM_FRAMES; ++slot)
                    std::memset(static_cast<unsigned char *>(stream.mapped) + slot * stream.segmentBytes + oldFloats * sizeof(float), 0, growBytes);
            }
            return true;
        }

        size_t segment = std::max(SURFACEFX_STREAM_MIN_SEGMENT, stream.segmentBytes);
        while (segment < requiredBytes)
            segment *= 2u;
        segment = AlignSurfaceFx(segment);

        GLuint newBuffer = 0;
        glf.CreateBuffers(1, &newBuffer);
        if (!newBuffer)
            return false;
        const GLbitfield flags = GL_MAP_WRITE_BIT_ | GL_MAP_PERSISTENT_BIT_ | GL_MAP_COHERENT_BIT_;
        glf.NamedBufferStorage(newBuffer, static_cast<GLsizeiptr>(segment * SURFACEFX_STREAM_FRAMES), nullptr, flags);
        void *mapped = glf.MapNamedBufferRange(newBuffer, 0, static_cast<GLsizeiptr>(segment * SURFACEFX_STREAM_FRAMES), flags);
        if (!mapped)
        {
            glf.DeleteBuffers(1, &newBuffer);
            return false;
        }

        if (stream.cpuUv.size() < requiredVertices * 4u)
            stream.cpuUv.resize(requiredVertices * 4u, 0.0f);
        const size_t used = stream.cpuUv.size() * sizeof(float);
        if (used)
            for (size_t slot = 0; slot < SURFACEFX_STREAM_FRAMES; ++slot)
                std::memcpy(static_cast<unsigned char *>(mapped) + slot * segment, stream.cpuUv.data(), used);

        if (stream.buffer)
            glf.DeleteBuffers(1, &stream.buffer);
        stream.buffer = newBuffer;
        stream.mapped = mapped;
        stream.segmentBytes = segment;
        LOG_SESSION("World3D SURFACEFX UV stream resize sourceVbo=%u segmentBytes=%llu totalBytes=%llu path=PERSISTENT-SSBO",
                    unsigned(sourceVbo), static_cast<unsigned long long>(segment),
                    static_cast<unsigned long long>(segment * SURFACEFX_STREAM_FRAMES));
        return true;
    }

    static bool StageUvSpan(GLuint sourceVbo, uint32 baseVertex,
                            const std::vector<WorldVertexGPU> &cpu, const PolySpan &span,
                            size_t &outFirstVertex, size_t &outLastVertex)
    {
        if (!sourceVbo || span.firstVertex + span.vertexCount > cpu.size() || !span.vertexCount)
            return false;
        const size_t globalFirst = size_t(baseVertex) + span.firstVertex;
        const size_t requiredVertices = globalFirst + span.vertexCount;
        if (!EnsureUvStream(sourceVbo, requiredVertices))
            return false;

        auto &state = WorldSurfaceFxSystem::Instance().State();
        SurfaceFxUvStream &stream = state.uvStreams[sourceVbo];
        const size_t firstFloat = globalFirst * 4u;
        for (size_t i = 0; i < span.vertexCount; ++i)
        {
            const WorldVertexGPU &v = cpu[span.firstVertex + i];
            const size_t f = firstFloat + i * 4u;
            stream.cpuUv[f + 0u] = v.u;
            stream.cpuUv[f + 1u] = v.v;
            stream.cpuUv[f + 2u] = 1.0f;
            stream.cpuUv[f + 3u] = 0.0f;
        }
        outFirstVertex = globalFirst;
        outLastVertex = globalFirst + span.vertexCount - 1u;
        return true;
    }

    struct SurfaceFxDirtyRange
    {
        size_t firstVertex = 0;
        size_t lastVertex = 0;
    };

    static void FlushStagedUvRanges(
        std::unordered_map<GLuint, std::vector<SurfaceFxDirtyRange>> &dirtyRanges)
    {
        auto &state = WorldSurfaceFxSystem::Instance().State();
        constexpr size_t kMergeGapVertices = 32u;

        for (auto &kv : dirtyRanges)
        {
            const GLuint sourceVbo = kv.first;
            auto streamIt = state.uvStreams.find(sourceVbo);
            if (streamIt == state.uvStreams.end() || !streamIt->second.mapped)
                continue;
            SurfaceFxUvStream &stream = streamIt->second;
            auto &ranges = kv.second;
            if (ranges.empty())
                continue;

            std::sort(ranges.begin(), ranges.end(), [](const SurfaceFxDirtyRange &a, const SurfaceFxDirtyRange &b)
                      { return a.firstVertex < b.firstVertex; });

            unsigned char *frameBase = static_cast<unsigned char *>(stream.mapped) +
                                       size_t(state.frameSlot) * stream.segmentBytes;
            size_t first = ranges[0].firstVertex;
            size_t last = ranges[0].lastVertex;

            auto flush = [&](size_t a, size_t b)
            {
                if (b < a)
                    return;
                const size_t firstFloat = a * 4u;
                const size_t floatCount = (b - a + 1u) * 4u;
                const size_t bytes = floatCount * sizeof(float);
                std::memcpy(frameBase + firstFloat * sizeof(float),
                            stream.cpuUv.data() + firstFloat, bytes);
                GLUploadStats::Instance().RecordWorldStreamWrite(
                    GLWorldUploadKind::SurfaceFx, bytes);
                state.usedThisFrame = true;
            };

            for (size_t i = 1; i < ranges.size(); ++i)
            {
                const auto &r = ranges[i];
                if (r.firstVertex <= last + 1u + kMergeGapVertices)
                    last = std::max(last, r.lastVertex);
                else
                {
                    flush(first, last);
                    first = r.firstVertex;
                    last = r.lastVertex;
                }
            }
            flush(first, last);
        }
    }
}

void WorldSurfaceFxSystem::RegisterTargets(WorldBspCompat *bsp,
                                           const std::vector<WorldBatch> &batches,
                                           bool staticBsp)
{
    if (!bsp)
        return;
    for (const WorldBatch &b : batches)
    {
        for (const PolySpan &span : b.spans)
        {
            if (!span.poly || !span.poly->m_pSurface || !span.vertexCount)
                continue;
            m_state.targets[span.poly->m_pSurface].push_back(
                SurfaceFxTarget{bsp, b.texture, span, staticBsp});
        }
    }
}

// Update one span which is already known to be referenced by a live
// SurfaceEffect.  Do not search the effect chain again here; UpdateSurfaceEffects
// now performs the reverse lookup once from Surface* -> affected geometry.
uint32 WorldSurfaceFxSystem::UpdateSpan(std::vector<WorldVertexGPU> &cpu,
                                        const PolySpan &span,
                                        SharedTexture *texture)
{
    WorldPolyCompat *poly = span.poly;
    if (!poly || !poly->m_pSurface ||
        span.firstVertex + span.vertexCount > cpu.size())
        return 0;

    // d3d.ren never reconstructs animated surface coordinates from
    // Surface::O/P/Q in the renderer.  Its polygon builders consume the live
    // SPolyVertex::m_fScaledU/V values supplied by the engine and multiply
    // those by the active RTexture U/V scale.  The engine's SurfaceEffect
    // update has already applied PAN/ROTATE/WARBLE to these per-vertex values
    // by the time the renderer is called.
    Texture *t = TextureManager::Instance().Ensure(texture, false);
    const float iw = (t && t->scaledWidth) ? 1.f / float(t->scaledWidth) : ((t && t->width) ? 1.f / float(t->width) : 1.f);
    const float ih = (t && t->scaledHeight) ? 1.f / float(t->scaledHeight) : ((t && t->height) ? 1.f / float(t->height) : 1.f);
    SPolyVertexCompat *pv = poly->m_Vertices;
    if (!pv)
        return 0;

    uint32 out = 0;
    for (uint32 j = 1; j + 1 < poly->m_wNumVerts && out + 3 <= span.vertexCount; ++j)
    {
        const uint32 vi[3] = {0, j, j + 1};
        for (int k = 0; k < 3; ++k, ++out)
        {
            const SPolyVertexCompat &sv = pv[vi[k]];
            if (!sv.m_pPoints)
                continue;
            cpu[span.firstVertex + out].u = sv.m_fScaledU * iw;
            cpu[span.firstVertex + out].v = sv.m_fScaledV * ih;
        }
    }

    if (LogIsSessionEnabled())
    {
        static uint32 s_surfaceFxUvBudget = 96;
        if (LogIsSessionEnabled() && (s_surfaceFxUvBudget && poly->m_wNumVerts))
        {
            --s_surfaceFxUvBudget;
            const SPolyVertexCompat &sv = pv[0];
            LOG_SESSION("World3D SURFACEFX-UV poly=%u tex=%p texDim=%ux%u scaled=%ux%u rawUV=(%.6f %.6f) finalUV=(%.6f %.6f) path=LIVE-SPOLYVERTEX/D3D",
                        unsigned(poly->m_wIndex), texture,
                        t ? t->width : 0u, t ? t->height : 0u, t ? t->scaledWidth : 0u, t ? t->scaledHeight : 0u,
                        sv.m_fScaledU, sv.m_fScaledV, sv.m_fScaledU * iw, sv.m_fScaledV * ih);
        }
    }
    return span.vertexCount;
}

void WorldSurfaceFxSystem::Update(MainWorldCompat *world, WorldBspCompat *mainBsp)
{
    if (!world || !world->m_pSurfaceEffects)
        return;

    struct DirtyBuffer
    {
        GLuint vbo = 0;
        std::vector<WorldVertexGPU> *cpu = nullptr;
        uint32 baseVertex = 0;
        size_t first = std::numeric_limits<size_t>::max();
        size_t last = 0;
        uint32 spans = 0;
    };

    uint32 liveEffects = 0, matchedEffects = 0, targets = 0, verts = 0;
    std::unordered_set<WorldPolyCompat *> touchedPolys;
    touchedPolys.reserve(256);
    std::vector<DirtyBuffer> dirtyBuffers;
    dirtyBuffers.reserve(16);
    std::unordered_map<uintptr_t, size_t> dirtyByCache;
    dirtyByCache.reserve(16);
    std::unordered_map<GLuint, std::vector<SurfaceFxDirtyRange>> uvDirtyRanges;
    uvDirtyRanges.reserve(8);

    auto markDirty = [&](GLuint vbo, std::vector<WorldVertexGPU> &cpu,
                         const PolySpan &span, uint32 baseVertex)
    {
        // Multiple WorldModel caches now share one arena VBO, so the VBO name
        // alone is no longer a unique dirty-upload key.  The stable CPU vector
        // address identifies the cache while baseVertex identifies its arena
        // slice.
        const uintptr_t key = reinterpret_cast<uintptr_t>(&cpu);
        auto it = dirtyByCache.find(key);
        size_t index = 0;
        if (it == dirtyByCache.end())
        {
            index = dirtyBuffers.size();
            dirtyByCache.emplace(key, index);
            dirtyBuffers.push_back(DirtyBuffer{});
            dirtyBuffers.back().vbo = vbo;
            dirtyBuffers.back().cpu = &cpu;
            dirtyBuffers.back().baseVertex = baseVertex;
        }
        else
            index = it->second;

        DirtyBuffer &d = dirtyBuffers[index];
        d.first = std::min(d.first, static_cast<size_t>(span.firstVertex));
        d.last = std::max(d.last, static_cast<size_t>(span.firstVertex + span.vertexCount - 1));
        ++d.spans;
    };

    // Modern hot path: iterate the engine's live SurfaceEffect list, then use
    // the cache-time reverse index to find only geometry attached to that
    // Surface.  The old implementation did the exact inverse -- every polygon
    // in every cache scanned this linked list -- which was O(polys*effects)
    // even when no effect matched the current BSP.
    for (SurfaceEffectCompat *e = world->m_pSurfaceEffects; e; e = e->m_pPrev)
    {
        ++liveEffects;
        if (!e->m_pSurface)
            continue;

        auto fit = m_state.targets.find(e->m_pSurface);
        if (fit == m_state.targets.end())
            continue;
        ++matchedEffects;

        for (const SurfaceFxTarget &target : fit->second)
        {
            if (e->m_pWorldBsp && target.bsp != e->m_pWorldBsp)
                continue;
            if (!target.span.poly || !touchedPolys.insert(target.span.poly).second)
                continue;

            if (target.staticBsp)
            {
                if (target.bsp != mainBsp || !WorldState().vbo || StaticState().cpuVertices.empty())
                    continue;
                const uint32 changed = UpdateSpan(
                    StaticState().cpuVertices, target.span, target.texture);
                if (changed)
                {
                    verts += changed;
                    ++targets;
                    size_t uvFirst = 0, uvLast = 0;
                    if (StageUvSpan(WorldState().vbo, 0, StaticState().cpuVertices, target.span, uvFirst, uvLast))
                        uvDirtyRanges[WorldState().vbo].push_back({uvFirst, uvLast});
                    else
                        markDirty(WorldState().vbo, StaticState().cpuVertices, target.span, 0);
                }
            }
            else
            {
                auto ci = WorldRenderer::Instance().WorldModels().State().caches.find(target.bsp);
                if (ci == WorldRenderer::Instance().WorldModels().State().caches.end() || ci->second.cpuVertices.empty())
                    continue;
                WorldModelCache &c = ci->second;
                const GLuint targetVbo = (c.arenaResident && WorldRenderer::Instance().WorldModels().State().arenaVbo)
                                             ? WorldRenderer::Instance().WorldModels().State().arenaVbo
                                             : c.vbo;
                if (!targetVbo)
                    continue;
                const uint32 changed = UpdateSpan(
                    c.cpuVertices, target.span, target.texture);
                if (changed)
                {
                    verts += changed;
                    ++targets;
                    const uint32 baseVertex = c.arenaResident ? c.arenaFirstVertex : 0u;
                    size_t uvFirst = 0, uvLast = 0;
                    if (StageUvSpan(targetVbo, baseVertex, c.cpuVertices, target.span, uvFirst, uvLast))
                        uvDirtyRanges[targetVbo].push_back({uvFirst, uvLast});
                    else
                        markDirty(targetVbo, c.cpuVertices, target.span, baseVertex);
                }
            }
        }
    }

    FlushStagedUvRanges(uvDirtyRanges);

    // Collapse potentially hundreds of tiny glNamedBufferSubData calls to at
    // most one upload per affected VBO.  SurfaceFX spans in a brush are usually
    // close together, and a single DSA transfer is substantially cheaper than
    // bouncing through the driver once per polygon.
    uint32 uploadCalls = 0;
    uint64_t uploadVerts = 0;
    for (const DirtyBuffer &d : dirtyBuffers)
    {
        if (!d.vbo || !d.cpu || d.first == std::numeric_limits<size_t>::max() || d.last < d.first)
            continue;
        const size_t count = d.last - d.first + 1;
        GLTrackedWorldNamedBufferSubData(d.vbo,
                                         static_cast<GLintptr>((size_t(d.baseVertex) + d.first) * sizeof(WorldVertexGPU)),
                                         static_cast<GLsizeiptr>(count * sizeof(WorldVertexGPU)),
                                         d.cpu->data() + d.first, GLWorldUploadKind::SurfaceFx);
        ++uploadCalls;
        uploadVerts += count;
    }

    static uint32 lastEffects = ~0u, lastMatched = ~0u, lastTargets = ~0u, lastUploads = ~0u;
    if (lastEffects != liveEffects || lastMatched != matchedEffects ||
        lastTargets != targets || lastUploads != uploadCalls)
    {
        lastEffects = liveEffects;
        lastMatched = matchedEffects;
        lastTargets = targets;
        lastUploads = uploadCalls;
        LOG_SESSION("World3D SURFACEFX-INDEX liveEffects=%u matchedEffects=%u activeSpans=%u updatedVerts=%u uploadCalls=%u uploadVerts=%llu indexedSurfaces=%u path=REVERSE-BATCHED",
                    liveEffects, matchedEffects, targets, verts, uploadCalls,
                    static_cast<unsigned long long>(uploadVerts),
                    static_cast<unsigned>(m_state.targets.size()));
    }
}

void WorldSurfaceFxSystem::BindUvOverride(GLuint sourceVbo)
{
    auto *shader = WorldRenderer::Instance().State().worldShader;
    if (!shader)
        return;
    auto it = m_state.uvStreams.find(sourceVbo);
    if (it != m_state.uvStreams.end())
    {
        size_t requiredVertices = 0;
        if (sourceVbo == WorldState().vbo)
            requiredVertices = StaticState().cpuVertices.size();
        else if (sourceVbo == WorldRenderer::Instance().WorldModels().State().arenaVbo)
            requiredVertices = WorldRenderer::Instance().WorldModels().State().arenaUsedVertices;
        else
        {
            for (const auto &kv : WorldRenderer::Instance().WorldModels().State().caches)
                if (kv.second.vbo == sourceVbo)
                {
                    requiredVertices = kv.second.cpuVertices.size();
                    break;
                }
        }
        if (requiredVertices)
        {
            EnsureUvStream(sourceVbo, requiredVertices);
            it = m_state.uvStreams.find(sourceVbo);
        }
    }
    const bool active = (it != m_state.uvStreams.end() && it->second.buffer && it->second.mapped);
    if (!active && !m_state.dummyUvBuffer)
    {
        const float zero[4] = {0, 0, 0, 0};
        glf.CreateBuffers(1, &m_state.dummyUvBuffer);
        if (m_state.dummyUvBuffer)
            glf.NamedBufferStorage(m_state.dummyUvBuffer, sizeof(zero), zero, 0);
    }
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 10, active ? it->second.buffer : m_state.dummyUvBuffer);
    GLUniform1ui(shader->Uniform("uSurfaceFxUvBase"), active
                                                          ? static_cast<uint32>((size_t(m_state.frameSlot) * it->second.segmentBytes) / (4u * sizeof(float)))
                                                          : 0u);
    if (active)
        m_state.usedThisFrame = true;
}

void WorldSurfaceFxSystem::AdvanceStreamFrame()
{
    if (m_state.uvStreams.empty() || !glf.FenceSync || !glf.ClientWaitSync || !glf.DeleteSync)
    {
        m_state.usedThisFrame = false;
        return;
    }
    if (m_state.usedThisFrame)
    {
        if (m_state.fences[m_state.frameSlot])
            glf.DeleteSync(m_state.fences[m_state.frameSlot]);
        m_state.fences[m_state.frameSlot] = glf.FenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE_, 0);
    }
    const uint32 next = (m_state.frameSlot + 1u) % static_cast<uint32>(SURFACEFX_STREAM_FRAMES);
    if (m_state.fences[next])
    {
        const GLenum wait = glf.ClientWaitSync(m_state.fences[next], GL_SYNC_FLUSH_COMMANDS_BIT_, GL_TIMEOUT_IGNORED_);
        if (wait == GL_WAIT_FAILED_)
            LOG_SESSION("World3D SURFACEFX UV stream: glClientWaitSync failed on slot %u", next);
        glf.DeleteSync(m_state.fences[next]);
        m_state.fences[next] = nullptr;
    }
    m_state.frameSlot = next;
    for (auto &kv : m_state.uvStreams)
    {
        SurfaceFxUvStream &stream = kv.second;
        if (!stream.mapped || stream.cpuUv.empty())
            continue;
        const size_t bytes = stream.cpuUv.size() * sizeof(float);
        if (bytes <= stream.segmentBytes)
            std::memcpy(static_cast<unsigned char *>(stream.mapped) + size_t(next) * stream.segmentBytes,
                        stream.cpuUv.data(), bytes);
    }
    m_state.usedThisFrame = false;
}

void WorldSurfaceFxSystem::Clear()
{
    for (void *&fence : m_state.fences)
    {
        if (fence && glf.DeleteSync)
            glf.DeleteSync(fence);
        fence = nullptr;
    }
    for (auto &kv : m_state.uvStreams)
        if (kv.second.buffer)
            glf.DeleteBuffers(1, &kv.second.buffer);
    m_state.uvStreams.clear();
    if (m_state.dummyUvBuffer)
        glf.DeleteBuffers(1, &m_state.dummyUvBuffer);
    m_state.dummyUvBuffer = 0;
    m_state.targets.clear();
    m_state.frameSlot = 0;
    m_state.usedThisFrame = false;
}
