#pragma once
#include "../../lt_renderer_abi.h"
#include <GL/gl.h>
#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace avp2::render
{
    class Shader;
}

struct WorldLightmapTile
{
    uint32 x = 0, y = 0, w = 0, h = 0;
    uint16 modelIndex = 0;
    uint16 polyIndex = 0;
    WorldPolyCompat *bakePoly = nullptr;
};

struct GpuLmTileDesc
{
    uint32 x = 0, y = 0, w = 0, h = 0;
    uint32 refStart = 0, refCount = 0, pad0 = 0, pad1 = 0;
};

struct GpuLmRefDesc
{
    uint32 animIndex = 0;
    uint32 frameOffsetStart = 0;
    uint32 pixelCount = 0;
    uint32 pad = 0;
};

struct GpuLmAnimState
{
    uint32 frame0 = 0, frame1 = 0, enabledFlag = 0, shadowFlag = 0;
    float between = 0.0f, blend = 0.0f;
    uint32 pad0 = 0, pad1 = 0;
};

static_assert(sizeof(GpuLmTileDesc) == 32, "GpuLmTileDesc std430 mismatch");
static_assert(sizeof(GpuLmRefDesc) == 16, "GpuLmRefDesc std430 mismatch");
static_assert(sizeof(GpuLmAnimState) == 32, "GpuLmAnimState std430 mismatch");

struct WorldLightmapSystemState
{
    avp2::render::Shader *computeShader = nullptr;
    GLuint atlas = 0;
    GLuint lightGridTexture = 0;
    MainWorldCompat *lightGridWorld = nullptr;
    uint32 lightGridX = 0, lightGridY = 0, lightGridZ = 0;
    std::vector<uint32> atlasPixels;
    std::unordered_map<WorldPolyCompat *, WorldLightmapTile> tiles;
    std::unordered_set<WorldPolyCompat *> changedLightAnimPolys;
    uint32 lightmapPolys = 0;
    uint32 lightmapAnims = 0;
    uint32 atlasUsedHeight = 0;

    GLuint tileSsbo = 0;
    GLuint refSsbo = 0;
    GLuint frameOffsetSsbo = 0;
    GLuint sourcePixelSsbo = 0;
    GLuint animStateSsbo = 0;
    GLuint dirtyTileSsbo = 0;
    bool gpuReady = false;
    std::unordered_map<WorldPolyCompat *, uint32> gpuTileIndex;
    std::vector<std::vector<uint32>> gpuAnimTiles;
    std::vector<std::vector<WorldPolyCompat *>> gpuAnimPolys;
    std::vector<uint32> gpuTileDirtyStamp;
    uint32 gpuDirtyStamp = 1;
    uint64_t gpuSourceBytes = 0;
};

class WorldLightmapSystem final
{
public:
    static constexpr uint32 AtlasDims = 4096;
    static constexpr float MinAnimBlend = 0.02f;
    static WorldLightmapSystem &Instance();

    bool BuildAtlas(MainWorldCompat *world, WorldBspCompat *targetBsp);
    uint32 UpdateAnimated(MainWorldCompat *world);
    void DestroyGpuResources();

    bool GetUVAtPoint(MainWorldCompat *world, WorldPolyCompat *poly, const LTVector &point, float &outU, float &outV) const;
    bool GetUV(MainWorldCompat *world, WorldPolyCompat *poly, uint32 vert, float &outU, float &outV) const;

    GLuint AtlasTexture() const { return m_state.atlas; }
    GLuint LightGridTexture() const { return m_state.lightGridTexture; }
    MainWorldCompat *LightGridWorld() const { return m_state.lightGridWorld; }
    uint32 LightGridX() const { return m_state.lightGridX; }
    uint32 LightGridY() const { return m_state.lightGridY; }
    uint32 LightGridZ() const { return m_state.lightGridZ; }
    uint32 AtlasUsedHeight() const { return m_state.atlasUsedHeight; }
    const std::vector<uint32> &AtlasPixels() const { return m_state.atlasPixels; }
    std::vector<uint32> &AtlasPixels() { return m_state.atlasPixels; }
    const std::unordered_set<WorldPolyCompat *> &ChangedLightAnimPolys() const { return m_state.changedLightAnimPolys; }
    float StockBlend(const LMAnimCompat &anim) const;
    float StockPercentBetween(const LMAnimCompat &anim) const;
    // Talon byte-combine helpers are shared with animated vertex-light sampling.
    uint8 StockMulByte(uint8 a, uint8 b) const;
    uint8 StockSatAddByte(uint8 a, uint8 b) const;
    // Shared lightmap-plane basis used by atlas UV projection and deluxe baking.
    static void SetupPlaneVectors(uint32 index, const LTVector &normal, LTVector &outU, LTVector &outV);
    bool HasTile(WorldPolyCompat *poly) const { return m_state.tiles.find(poly) != m_state.tiles.end(); }

    WorldLightmapSystemState &State() { return m_state; }
    const WorldLightmapSystemState &State() const { return m_state; }

private:
    WorldLightmapSystem() = default;

    bool DecompressLightmap(const uint8 *compressed, uint32 len, uint32 *out, uint32 maxPixels) const;
    bool DecompressShadowMap(const uint8 *compressed, uint32 len, uint32 *out, uint32 maxPixels) const;
    bool FindPolyAnimDataIndex(const WorldPolyCompat *poly, uint32 animIndex, uint32 &outDataIndex) const;
    void AddLightPixel(uint32 &dst, uint32 src, float mod) const;
    bool EnsureGpuProgram();
    GpuLmAnimState MakeGpuAnimState(const LMAnimCompat &anim) const;
    bool CreateGpuBuffer(GLuint &out, const void *data, size_t bytes, GLbitfield flags) const;
    bool BuildGpuResources(MainWorldCompat *world);
    bool DispatchGpuUpdate(MainWorldCompat *world, const std::vector<uint32> &changedAnims, uint32 liveAnims);

    WorldLightmapSystemState m_state{};
};
