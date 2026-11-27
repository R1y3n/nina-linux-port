#pragma once
#include "world_render_types.h"
#include <unordered_map>
#include <vector>
#include <cstddef>

enum class WorldModelPhase
{
    Opaque,
    ChromaKey,
    Translucent
};

struct WorldModelRendererState
{
    std::unordered_map<WorldBspCompat *, WorldModelCache> caches;
    GLuint arenaVbo = 0;
    size_t arenaCapacityBytes = 0;
    uint32 arenaUsedVertices = 0;
    GLuint vertexLightArenaSsbo = 0;
    size_t vertexLightArenaCapacityBytes = 0;
    std::vector<uint32> vertexLightArenaCpu;
    GLuint drawStateSsbo = 0;
    size_t drawStateCapacity = 0; // bytes per persistent frame segment
    GLuint indirectBuffer = 0;
    size_t indirectCapacity = 0; // bytes per persistent frame segment
    GLuint drawStateFallbackSsbo = 0;
    GLuint indirectFallbackBuffer = 0;
    void *drawStateMapped = nullptr;
    void *indirectMapped = nullptr;
    size_t drawStateCursorBytes = 0;
    size_t indirectCursorBytes = 0;
    uint32 submissionFrameSlot = 0;
    void *submissionFences[3]{};
    bool submissionUsedThisFrame = false;

    // CPU-sampled WorldModel Gouraud/LightAnim colours. Geometry remains in
    // the immutable arena VBO; only RGB is streamed here (3 floats/vertex).
    GLuint cpuColorSsbo = 0;
    void *cpuColorMapped = nullptr;
    size_t cpuColorCapacity = 0; // bytes per persistent frame segment
    std::vector<float> cpuColorArena;
    bool cpuColorUsedThisFrame = false;
};

// Brush WorldModel submission is separate from static BSP/world orchestration.
class WorldModelRenderer final
{
public:
    WorldModelPhase Classify(const WorldModelInstanceCompat *worldModel) const;
    bool HasPhase(const WorldModelInstanceCompat *worldModel, WorldModelPhase phase) const;
    void RenderDeferred(SceneDesc *scene, WorldModelPhase phase);
    void RenderTranslucent(SceneDesc *scene, WorldModelInstanceCompat *worldModel);
    void RenderVisiblePhase(MainWorldCompat *world, WorldModelPhase phase, uint32 &draws, uint64_t &tris);
    void UpdateVertexLighting(MainWorldCompat *world);
    void AdvanceStreamFrame();
    bool BuildGpuVertexLightBuffer(MainWorldCompat *world, const std::vector<WorldModelVertexLightRef> &lightRefs, GLuint &outBuffer, const char *label, WorldModelCache *arenaCache = nullptr);
    void Term();
    bool NeedsCpuVertexLightFallback() const;
    WorldModelCache *GetOrCreateCache(MainWorldCompat *world, WorldBspCompat *bsp);
    bool BindGeometry(const WorldModelCache *cache) const;
    void BindGpuVertexLight(const WorldModelCache *cache) const;
    WorldModelRendererState &State() { return m_state; }
    const WorldModelRendererState &State() const { return m_state; }

private:
    WorldModelRendererState m_state{};
};
