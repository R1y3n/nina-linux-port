#pragma once
#include "../../gl_renderer.h"
#include <GL/gl.h>
#include <vector>
namespace avp2::render
{
    class Shader;
}

struct Renderer2DState
{
    bool optimized = false;
    LTSurfaceBlend blend = LTSURFACEBLEND_ALPHA;
    HLTCOLOR color = 0xFFFFFFFFu;
    avp2::render::Shader *blitShader = nullptr;
    GLint uTex = -1;
    GLint uColor = -1;
    GLint uAlpha = -1;
    GLint uUseKey = -1;
    GLint uKey = -1;
    GLint uUseTexAlpha = -1;
    std::vector<uint8_t> optimizedUploadScratch;
};

class Renderer2D final
{
public:
    static Renderer2D &Instance();
    bool Init();
    void Term();
    bool StartOptimized();
    void EndOptimized();
    bool IsOptimized() const;
    bool SetBlend(LTSurfaceBlend blend);
    bool GetBlend(LTSurfaceBlend &blend) const;
    bool SetColor(HLTCOLOR color);
    bool GetColor(HLTCOLOR &color) const;
    GLSurface *CreateSurface(int width, int height);
    void DeleteSurface(GLSurface *surface);
    void EnsureTexture(GLSurface *surface);
    void Flush();
    avp2::render::Shader *BlitShader() const { return m_state.blitShader; }
    GLint BlitTexUniform() const { return m_state.uTex; }
    GLint BlitColorUniform() const { return m_state.uColor; }
    GLint BlitAlphaUniform() const { return m_state.uAlpha; }
    GLint BlitUseKeyUniform() const { return m_state.uUseKey; }
    GLint BlitKeyUniform() const { return m_state.uKey; }
    GLint BlitUseTexAlphaUniform() const { return m_state.uUseTexAlpha; }
    Renderer2DState &State() { return m_state; }
    const Renderer2DState &State() const { return m_state; }

private:
    Renderer2D() = default;
    Renderer2DState m_state{};
};
