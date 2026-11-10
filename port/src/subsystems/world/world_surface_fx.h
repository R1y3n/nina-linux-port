#pragma once
#include "world_render_types.h"
#include <unordered_map>
#include <vector>
#include <cstddef>

struct SurfaceFxUvStream
{
    GLuint buffer = 0;
    void *mapped = nullptr;
    size_t segmentBytes = 0;
    std::vector<float> cpuUv; // vec4 per source vertex: u,v,valid,pad
};

struct WorldSurfaceFxState
{
    std::unordered_map<SurfaceCompat *, std::vector<SurfaceFxTarget>> targets;
    std::unordered_map<GLuint, SurfaceFxUvStream> uvStreams;
    uint32 frameSlot = 0;
    void *fences[3]{};
    bool usedThisFrame = false;
    GLuint dummyUvBuffer = 0;
};

class WorldSurfaceFxSystem final
{
public:
    static WorldSurfaceFxSystem &Instance();
    void RegisterTargets(WorldBspCompat *bsp, const std::vector<WorldBatch> &batches, bool staticBsp);
    void Update(MainWorldCompat *world, WorldBspCompat *mainBsp);
    void BindUvOverride(GLuint sourceVbo);
    void AdvanceStreamFrame();
    void Clear();
    WorldSurfaceFxState &State() { return m_state; }
    const WorldSurfaceFxState &State() const { return m_state; }

private:
    WorldSurfaceFxSystem() = default;
    uint32 UpdateSpan(std::vector<WorldVertexGPU> &cpu, const PolySpan &span, SharedTexture *texture);
    WorldSurfaceFxState m_state{};
};
