#pragma once
#include "../../lt_renderer_abi.h"
#include <GL/gl.h>
#include <cstddef>
#include <cstdint>
namespace avp2::render
{
    class Shader;
}

struct FXRendererState
{
    avp2::render::Shader *shader = nullptr;
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint streamFallbackVbo = 0;
    void *streamMapped = nullptr;
    size_t streamCursorBytes = 0;
    uint32_t streamFrameSlot = 0;
    void *streamFences[3]{};
    bool streamUsedThisFrame = false;
    GLint uTanHalfFovX = -1, uTanHalfFovY = -1, uNearZ = -1, uFarZ = -1;
    GLint uTextured = -1, uFogEnabled = -1, uFogColor = -1, uFogNear = -1, uFogFar = -1, uFogAdditive = -1;
    GLint uVFogEnabled = -1, uVFogMinY = -1, uVFogMaxY = -1, uVFogMinYVal = -1, uVFogMaxYVal = -1, uVFogDensity = -1, uVFogMax = -1;
    GLint uEnvMapEnabled = -1, uEnvMap = -1;
    GLint uCanvasOps = -1, uCanvasColorOp = -1, uCanvasAlphaOp = -1;
    RenderStruct *renderStruct = nullptr;
    int psSrcBlendOverride = -1;
    int psDestBlendOverride = -1;
    bool envMapPolyGrids = true;
};

class FXRenderer final
{
public:
    static FXRenderer &Instance();
    bool Init();
    void Term();
    void SetRenderStruct(RenderStruct *rs);
    RenderStruct *GetRenderStruct() const { return m_state.renderStruct; }
    void ReadConsoleVariables();
    bool RenderParticleSystem(SceneDesc *scene, ParticleSystemCompat *system);
    bool RenderPolyGrid(SceneDesc *scene, PolyGridCompat *grid);
    bool RenderLineSystem(SceneDesc *scene, LineSystemCompat *system);
    bool RenderCanvas(SceneDesc *scene, CanvasCompat *canvas);
    void AdvanceStreamFrame();
    FXRendererState &State() { return m_state; }
    const FXRendererState &State() const { return m_state; }

private:
    FXRenderer() = default;
    FXRendererState m_state{};
};
