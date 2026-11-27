#pragma once
#include "world_render_types.h"
#include <GL/gl.h>
#include <cstddef>
#include <vector>

struct SkyPortalSpan
{
    WorldPolyCompat *poly = nullptr;
    uint32 firstVertex = 0;
    uint32 vertexCount = 0;
};

struct SkyRendererState
{
    GLuint portalVbo = 0;
    GLuint clipVbo = 0;
    GLuint clipFallbackVbo = 0;
    void *clipMapped = nullptr;
    size_t clipCursorBytes = 0;
    uint32 clipFrameSlot = 0;
    void *clipFences[3]{};
    bool clipUsedThisFrame = false;
    std::vector<WorldVertexGPU> portalVertices;
    std::vector<SkyPortalSpan> portalSpans;
};

class SkyRenderer final
{
public:
    static SkyRenderer &Instance();

    void Render(SceneDesc *scene, MainWorldCompat *world, uint32 &draws, uint64_t &tris);
    void UploadPortalGeometry();
    void AdvanceStreamFrame();
    void Term();

    SkyRendererState &State() { return m_state; }
    const SkyRendererState &State() const { return m_state; }

private:
    SkyRenderer() = default;
    SkyRendererState m_state{};
};
