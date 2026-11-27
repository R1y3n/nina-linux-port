#pragma once
#include "../../lt_renderer_abi.h"
#include <GL/gl.h>
#include <cstddef>
#include <cstdint>
#include <vector>

struct World3DPerfStats
{
    bool pvsActive = false;
    uint32 visibleLeaves = 0;
    uint32 totalLeaves = 0;
    uint32 leafPolyRefs = 0;
    uint32 uniqueVisiblePolys = 0;
    uint32 renderedPolys = 0;
    uint64_t visibleTriangles = 0;
    uint32 apiDrawCalls = 0;
    uint32 worldModels = 0;
    uint32 models = 0;
    uint32 sprites = 0;
    uint32 dynamicLights = 0;
};

struct ModelStaticLightInfo
{
    LTVector pos;
    float radius;
    LTVector innerColor;
    LTVector dir;
    float fov;
    LTVector outerColor;
};

struct ModelLightAnimInfo
{
    LTVector pos;
    LTVector color;
    float radius;
    uint32 animIndex;
};

struct WorldVertexGPU
{
    float x, y, z;
    float u, v;
    float lmU, lmV;
    float r, g, b, a;
    float hasLightmap;
    float hasVertexLight;
    float polyCenterX, polyCenterY, polyCenterZ;
    float normalX, normalY, normalZ;
    // Precomputed +lightmap-U tangent in polygon/model space. Deluxe direction
    // RGB is stored in the T,-V,N frame, so carrying T per vertex avoids
    // reconstructing the lightmap basis with fragment derivatives every pixel.
    float lmTangentX, lmTangentY, lmTangentZ;
    // base-texture-U tangent, precomputed per triangle for cached material normals.
    float baseTangentX, baseTangentY, baseTangentZ;
};

enum class WorldBlendMode : uint8
{
    Solid = 0,
    Alpha = 1,
    Additive = 2,
    Multiply = 3
};

// Stock Talon world dynamic lights are spherical additive lights.  The
// D3D renderer builds an attenuation texture equivalent to
// max(0, 1 - distance^2/radius^2); modern GL can evaluate that directly.
struct DynamicWorldLightGPU
{
    float posRadius[4];  // xyz world position, radius
    float colorFlags[4]; // rgb 0..1, flags bitcast through float not used yet
};

constexpr uint32 MAX_WORLD_DYNAMIC_LIGHTS = 40; // stock MAX_VISIBLE_LIGHTS

enum WorldTexFxBits : uint32
{
    WTFX_NONE = 0,
    WTFX_PAN = 1u << 0,
    WTFX_ROTATE = 1u << 1,
    WTFX_WARBLE = 1u << 2,
    WTFX_PANSKY = 1u << 3
};

struct WorldTexFx
{
    uint32 mask = 0;
    float panU = 0.0f, panV = 0.0f;
    float rotateDegPerSec = 0.0f;
    float warbleScale = 0.0f, warbleSpeed = 0.0f;
    uint32 hash = 0;
};

struct PolySpan
{
    WorldPolyCompat *poly = nullptr;
    uint32 firstVertex = 0;
    uint32 vertexCount = 0;
};

struct WorldBatch
{
    SharedTexture *texture = nullptr;
    // SURF_SPRITEANIMATE is engine-driven in Talon: Surface::m_pTexture is
    // replaced with the current SPR frame.  Keep the live surface instead of
    // freezing the SharedTexture pointer in the geometry cache.
    SurfaceCompat *animatedSurface = nullptr;
    float uvNormWidth = 1.0f;
    float uvNormHeight = 1.0f;
    uint32 firstVertex = 0;
    uint32 vertexCount = 0;
    WorldBlendMode blend = WorldBlendMode::Solid;
    float alphaRef = 0.0f;
    bool noLight = false;
    bool hasLightmap = false;
    bool extraShade = false;
    bool lightmapGouraud = false;
    bool gouraudNoLightmap = false;
    WorldTexFx texFx{};
    float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;
    std::vector<PolySpan> spans;
};

struct BatchKey
{
    SharedTexture *texture = nullptr;
    SurfaceCompat *animatedSurface = nullptr;
    WorldBlendMode blend = WorldBlendMode::Solid;
    uint32 fxHash = 0;
    bool lightmapGouraud = false;
    bool gouraudNoLightmap = false;

    bool operator==(const BatchKey &other) const
    {
        return texture == other.texture && animatedSurface == other.animatedSurface &&
               blend == other.blend && fxHash == other.fxHash &&
               lightmapGouraud == other.lightmapGouraud &&
               gouraudNoLightmap == other.gouraudNoLightmap;
    }
};

struct BatchKeyHash
{
    size_t operator()(const BatchKey &k) const
    {
        return (reinterpret_cast<size_t>(k.texture) >> 4) ^
               (reinterpret_cast<size_t>(k.animatedSurface) >> 5) ^
               (static_cast<size_t>(k.blend) * 0x9E3779B1u) ^
               (static_cast<size_t>(k.fxHash) * 0x85EBCA6Bu) ^
               (static_cast<size_t>(k.lightmapGouraud) << 29) ^
               (static_cast<size_t>(k.gouraudNoLightmap) << 30);
    }
};

struct WorldModelVertexLightRef
{
    WorldPolyCompat *poly = nullptr;
    uint16 vert = 0;
    uint16 pad = 0;
};

struct VertexLightSourceKey
{
    WorldPolyCompat *poly = nullptr;
    uint16 vert = 0;

    bool operator==(const VertexLightSourceKey &o) const
    {
        return poly == o.poly && vert == o.vert;
    }
};

struct VertexLightSourceKeyHash
{
    size_t operator()(const VertexLightSourceKey &k) const
    {
        return (reinterpret_cast<size_t>(k.poly) >> 4) ^
               (static_cast<size_t>(k.vert) * 0x9E3779B1u);
    }
};

struct BatchBuild
{
    SharedTexture *texture = nullptr;
    SurfaceCompat *animatedSurface = nullptr;
    float uvNormWidth = 1.0f;
    float uvNormHeight = 1.0f;
    WorldBlendMode blend = WorldBlendMode::Solid;
    float alphaRef = 0.0f;
    bool noLight = false;
    bool hasLightmap = false;
    bool extraShade = false;
    bool lightmapGouraud = false;
    bool gouraudNoLightmap = false;
    WorldTexFx texFx{};
    bool haveBounds = false;
    float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;
    std::vector<WorldVertexGPU> vertices;
    std::vector<WorldModelVertexLightRef> lightRefs;
    std::vector<PolySpan> spans;
};

struct WorldModelCache
{
    // Modern path: all brush WorldModel geometry is appended into one shared
    // immutable-ish arena VBO.  A small per-cache fallback VBO is only created
    // if the arena cannot be allocated.
    GLuint vbo = 0;
    // Keep the dedicated per-cache SSBO as a compatibility fallback, but also
    // append the same immutable Gouraud descriptor payload to a global SSBO
    // arena so GPU-lit WorldModels can participate in cross-object MDI.
    GLuint vertexLightSsbo = 0;
    uint32 vertexLightArenaWordOffset = 0;
    bool vertexLightArenaResident = false;
    uint32 arenaFirstVertex = 0;
    bool arenaResident = false;
    std::vector<WorldBatch> batches;
    std::vector<WorldVertexGPU> cpuVertices;
    std::vector<WorldModelVertexLightRef> lightRefs;
    uint32 totalVerts = 0;
    uint32 totalPolys = 0;
};

struct StaticVisibleBatchCache
{
    uint32 firstIndex = 0;
    uint32 indexCount = 0;
    uint32 sourceRuns = 0;
    uint32 visiblePolys = 0;
    uint64_t tris = 0;
};

struct TerrainVisibleBspCache
{
    WorldBspCompat *bsp = nullptr;
    std::vector<StaticVisibleBatchCache> batches;
    uint32 visiblePolys = 0;
    uint64_t tris = 0;
};

struct SurfaceFxTarget
{
    WorldBspCompat *bsp = nullptr;
    SharedTexture *texture = nullptr;
    PolySpan span{};
    bool staticBsp = false;
};
