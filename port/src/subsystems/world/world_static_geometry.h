#pragma once
#include "world_render_types.h"
#include <GL/gl.h>
#include <array>
#include <cstddef>
#include <vector>

struct WorldStaticGeometryState
{
    WorldBspCompat *cachedBsp = nullptr;
    std::vector<WorldBatch> batches;
    // Immutable batch lists compiled with the BSP. Rendering can walk only
    // the requested blend phase instead of filtering every batch four times.
    std::array<std::vector<uint32>, static_cast<size_t>(WorldBlendMode::Multiply) + 1u> batchIndicesByBlend;
    std::vector<WorldVertexGPU> cpuVertices;
    std::vector<WorldModelVertexLightRef> vertexLightRefs;
    GLuint vertexLightSsbo = 0;
    GLuint staticPvsEbo = 0;
    size_t staticPvsEboCapacity = 0;
    GLuint terrainPvsEbo = 0;
    size_t terrainPvsEboCapacity = 0;

    uint32 totalVerts = 0;
    uint32 totalPolys = 0;
    uint32 badPolys = 0;
    uint32 missingTextures = 0;
    uint32 skippedInvisible = 0;
    uint32 skippedSky = 0;
    uint32 solidPolys = 0;
    uint32 alphaPolys = 0;
    uint32 addPolys = 0;

    uint64_t staticMaskGeneration = 0;
    WorldBspCompat *staticMaskGenerationBsp = nullptr;
    std::vector<StaticVisibleBatchCache> staticVisibleBatchCache;
    uint64_t staticDrawCacheGeneration = 0;
    WorldBspCompat *staticDrawCacheBsp = nullptr;
    uint32 staticDrawCacheRebuilds = 0;

    std::vector<TerrainVisibleBspCache> terrainVisibleBspCache;
    uint64_t terrainDrawCacheGeneration = 0;
    MainWorldCompat *terrainDrawCacheWorld = nullptr;
    bool terrainDrawCacheHadPvs = false;
    uint32 terrainDrawCacheRebuilds = 0;
};

class WorldStaticGeometryRenderer final
{
public:
    static WorldStaticGeometryRenderer &Instance();
    WorldStaticGeometryState &State() { return m_state; }
    const WorldStaticGeometryState &State() const { return m_state; }
    void RebuildVisibilityMask(WorldBspCompat *bsp);
    bool IsPolyVisible(WorldPolyCompat *poly) const;
    void RebuildVisibleBatchCache(WorldBspCompat *bsp);

private:
    WorldStaticGeometryRenderer() = default;
    WorldStaticGeometryState m_state{};
};
