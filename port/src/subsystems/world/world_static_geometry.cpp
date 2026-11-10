#include "world_static_geometry.h"
#include "world_renderer.h"
#include "world_pvs.h"
#include "../../gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "utils/log.h"
#include <algorithm>

WorldStaticGeometryRenderer &WorldStaticGeometryRenderer::Instance()
{
    static WorldStaticGeometryRenderer v;
    return v;
}

void WorldStaticGeometryRenderer::RebuildVisibilityMask(WorldBspCompat *bsp)
{
    if (!WorldPVS::Instance().State().haveStaticPVS || !bsp || !bsp->m_pPolies || !bsp->m_dwPolies)
    {
        WorldPVS::Instance().State().visibleStaticMaskBsp = nullptr;
        WorldPVS::Instance().State().visibleStaticMask.clear();
        m_state.staticMaskGeneration = 0;
        m_state.staticMaskGenerationBsp = nullptr;
        return;
    }

    if (m_state.staticMaskGeneration == WorldPVS::Instance().State().staticPvsGeneration &&
        m_state.staticMaskGenerationBsp == bsp && WorldPVS::Instance().State().visibleStaticMaskBsp == bsp &&
        WorldPVS::Instance().State().visibleStaticMask.size() == bsp->m_dwPolies)
        return;

    WorldPVS::Instance().State().visibleStaticMaskBsp = bsp;
    if (WorldPVS::Instance().State().visibleStaticMask.size() != bsp->m_dwPolies)
        WorldPVS::Instance().State().visibleStaticMask.assign(bsp->m_dwPolies, 0u);
    else
        std::fill(WorldPVS::Instance().State().visibleStaticMask.begin(), WorldPVS::Instance().State().visibleStaticMask.end(), uint8_t{0});

    for (WorldPolyCompat *poly : WorldPVS::Instance().State().visibleStaticPolys)
    {
        if (!poly)
            continue;
        const uint32 index = static_cast<uint32>(poly->m_wIndex);
        // Validate the disk/runtime index before trusting it.  If a malformed
        // or non-static polygon reaches the visible set, the draw helper falls
        // back to the pointer set instead of marking the wrong polygon.
        if (index < bsp->m_dwPolies && bsp->m_pPolies[index] == poly)
            WorldPVS::Instance().State().visibleStaticMask[index] = 1u;
    }

    m_state.staticMaskGeneration = WorldPVS::Instance().State().staticPvsGeneration;
    m_state.staticMaskGenerationBsp = bsp;
}

bool WorldStaticGeometryRenderer::IsPolyVisible(WorldPolyCompat *poly) const
{
    if (!WorldPVS::Instance().State().haveStaticPVS)
        return true;
    if (!poly)
        return false;

    if (WorldPVS::Instance().State().visibleStaticMaskBsp && !WorldPVS::Instance().State().visibleStaticMask.empty())
    {
        const uint32 index = static_cast<uint32>(poly->m_wIndex);
        if (index < WorldPVS::Instance().State().visibleStaticMask.size() &&
            WorldPVS::Instance().State().visibleStaticMaskBsp->m_pPolies &&
            WorldPVS::Instance().State().visibleStaticMaskBsp->m_pPolies[index] == poly)
            return WorldPVS::Instance().State().visibleStaticMask[index] != 0u;
    }

    return WorldPVS::Instance().State().visibleStaticPolys.find(poly) != WorldPVS::Instance().State().visibleStaticPolys.end();
}

void WorldStaticGeometryRenderer::RebuildVisibleBatchCache(WorldBspCompat *bsp)
{
    if (!WorldPVS::Instance().State().haveStaticPVS || !bsp)
    {
        m_state.staticVisibleBatchCache.clear();
        m_state.staticDrawCacheGeneration = 0;
        m_state.staticDrawCacheBsp = nullptr;
        return;
    }

    if (m_state.staticDrawCacheGeneration == WorldPVS::Instance().State().staticPvsGeneration &&
        m_state.staticDrawCacheBsp == bsp &&
        m_state.staticVisibleBatchCache.size() == m_state.batches.size())
        return;

    m_state.staticVisibleBatchCache.clear();
    m_state.staticVisibleBatchCache.resize(m_state.batches.size());

    // Geometry is immutable.  On a PVS transition, compile the exact visible
    // polygon set into one compact index stream ordered by material.  Each
    // visible material then becomes a single DrawElements call instead of one
    // MultiDrawArrays call containing hundreds of discontiguous sub-draws.
    //
    // This is the useful form of "rebuilding the mesh" for static BSP: only
    // the tiny index/command stream changes; vertex data never moves.
    std::vector<uint32> indices;
    indices.reserve(std::min<size_t>(m_state.totalVerts, 65536u));

    uint32 sourceRuns = 0;
    uint32 visiblePolys = 0;
    uint64_t visibleTris = 0;
    uint32 visibleMaterials = 0;

    for (size_t bi = 0; bi < m_state.batches.size(); ++bi)
    {
        const WorldBatch &b = m_state.batches[bi];
        StaticVisibleBatchCache &out = m_state.staticVisibleBatchCache[bi];
        out.firstIndex = static_cast<uint32>(indices.size());

        uint32 prevEnd = 0;
        bool haveRun = false;

        for (const PolySpan &span : b.spans)
        {
            if (!IsPolyVisible(span.poly))
                continue;

            if (!haveRun || prevEnd != span.firstVertex)
                ++out.sourceRuns;
            haveRun = true;
            prevEnd = span.firstVertex + span.vertexCount;

            ++out.visiblePolys;
            ++visiblePolys;
            out.tris += span.vertexCount / 3;

            const uint32 end = span.firstVertex + span.vertexCount;
            for (uint32 vi = span.firstVertex; vi < end; ++vi)
                indices.push_back(vi);
        }

        out.indexCount = static_cast<uint32>(indices.size()) - out.firstIndex;
        sourceRuns += out.sourceRuns;
        visibleTris += out.tris;
        if (out.indexCount)
            ++visibleMaterials;
    }

    const size_t bytes = indices.size() * sizeof(uint32);
    const size_t wantedCapacity = std::max<size_t>(
        sizeof(uint32),
        std::max<size_t>(m_state.totalVerts * sizeof(uint32), bytes));

    if (!m_state.staticPvsEbo || m_state.staticPvsEboCapacity < wantedCapacity)
    {
        if (m_state.staticPvsEbo)
            glf.DeleteBuffers(1, &m_state.staticPvsEbo);
        m_state.staticPvsEbo = 0;
        glf.CreateBuffers(1, &m_state.staticPvsEbo);
        if (m_state.staticPvsEbo)
        {
            glf.NamedBufferStorage(m_state.staticPvsEbo,
                                   static_cast<GLsizeiptr>(wantedCapacity), nullptr, GL_DYNAMIC_STORAGE_BIT_);
            m_state.staticPvsEboCapacity = wantedCapacity;
            glf.VertexArrayElementBuffer(WorldRenderer::Instance().State().vao, m_state.staticPvsEbo);
        }
    }

    if (m_state.staticPvsEbo && bytes)
        GLTrackedWorldNamedBufferSubData(m_state.staticPvsEbo, 0,
                                         static_cast<GLsizeiptr>(bytes), indices.data(), GLWorldUploadKind::PvsStatic);

    m_state.staticDrawCacheGeneration = WorldPVS::Instance().State().staticPvsGeneration;
    m_state.staticDrawCacheBsp = bsp;
    ++m_state.staticDrawCacheRebuilds;

    static uint32 budget = 96;
    if (LogIsSessionEnabled() && (budget && (--budget, true)))
        LOG_SESSION("World3D PVS-DRAWCACHE generation=%llu rebuild=%u batches=%u visibleMaterials=%u sourceRuns=%u indices=%u visiblePolys=%u tris=%llu path=IMMUTABLE-MESH/MATERIAL-INDEX-CACHE",
                    static_cast<unsigned long long>(WorldPVS::Instance().State().staticPvsGeneration), m_state.staticDrawCacheRebuilds,
                    static_cast<unsigned>(m_state.staticVisibleBatchCache.size()), visibleMaterials,
                    sourceRuns, static_cast<unsigned>(indices.size()), visiblePolys,
                    static_cast<unsigned long long>(visibleTris));
}
