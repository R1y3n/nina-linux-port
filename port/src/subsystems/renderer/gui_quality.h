#pragma once

#include "../../gl_renderer.h"
#include <GL/gl.h>

namespace avp2::render
{
    class Shader;
}

struct GUIQualityState
{
    // Shader ownership remains centralized in ShaderManager.  GUIQuality keeps
    // non-owning handles for its post-processing pipelines.
    avp2::render::Shader *ssaoShader = nullptr;
    avp2::render::Shader *ssrShader = nullptr;
    avp2::render::Shader *blurShader = nullptr;
    avp2::render::Shader *ssaoCompositeShader = nullptr;
    avp2::render::Shader *ssrCompositeShader = nullptr;
    avp2::render::Shader *debugShader = nullptr;
    avp2::render::Shader *bloomExtractShader = nullptr;
    avp2::render::Shader *bloomBlurShader = nullptr;
    avp2::render::Shader *exposureShader = nullptr;
    avp2::render::Shader *exposureCompositeShader = nullptr;

    // Quality feature toggles/state.
    bool msaa4xEnabled = true;
    bool ssaoEnabled = true;
    bool ssrEnabled = true;
    bool bloomEnabled = false;
    bool dynamicExposureEnabled = false;
    bool tuningMenuOpen = false;
    bool imguiReady = false;

    // SSAO tuning.
    float ssaoStrength = 2.15f;
    float ssaoRadiusPixels = 8.0f;
    float ssaoBias = 0.08f;
    float ssaoMinAO = 0.35f;
    float ssaoBlurRadius = 7.2f;
    float ssaoBlurDepth = 93.2f;

    // SSR tuning.
    float ssrStrength = 0.30f;
    float ssrMaxDistance = 341.0f;
    float ssrThicknessBase = 0.10f;
    float ssrThicknessScale = 0.0088f;
    float ssrNormalBias = 0.28f;
    int ssrSteps = 34;
    float ssrBlurRadius = 4.9f;
    float ssrBlurDepth = 44.8f;
    bool ssrFilterEnabled = true;
    bool ssrFilterInvert = true;
    float ssrHueCenter = 0.166f;
    float ssrHueWidth = 0.376f;
    float ssrSatMin = 0.02f;
    float ssrSatMax = 0.30f;
    float ssrValueMin = 0.0f;
    float ssrValueMax = 0.60f;
    float ssrAlphaMin = 0.09f;
    float ssrFilterSoftness = 0.060f;
    // Bloom tuning.
    float bloomThreshold = 0.72f;
    float bloomSoftKnee = 0.18f;
    float bloomIntensity = 0.55f;
    float bloomRadius = 1.25f;

    // Dynamic exposure tuning. This is deliberately color-neutral: the final
    // scene RGB is multiplied by one scalar exposure value only.
    float exposureBaseline = 1.00f;
    float exposureDarkMax = 1.35f;
    float exposureDarkThreshold = 0.20f;
    float exposureAdaptSpeed = 2.0f;
    float currentExposure = 1.0f;

    int qualityDebugView = 0;
    float lastQualityNear = 1.0f;
    float lastQualityFar = 10000.0f;

    // MSAA target.
    GLuint msaaFBO = 0;
    GLuint msaaColorRB = 0;
    GLuint msaaReflectionMaskRB = 0;
    GLuint msaaDepthStencilRB = 0;
    bool msaaReady = false;
    bool sceneRenderingToMSAA = false;
    bool sceneOpaqueQualityApplied = false;

    // Post-process targets.
    GLuint postFBO = 0;
    GLuint postColorTex = 0;
    GLuint postDepthFBO = 0;
    GLuint postDepthTex = 0;
    GLuint ssaoFBO = 0;
    GLuint ssaoTex = 0;
    GLuint ssaoBlurFBO = 0;
    GLuint ssaoBlurTex = 0;
    GLuint ssrFBO = 0;
    GLuint ssrTex = 0;
    GLuint ssrBlurFBO = 0;
    GLuint ssrBlurTex = 0;
    GLuint ssrInputFBO = 0;
    GLuint ssrInputTex = 0;
    GLuint debugFBO = 0;
    GLuint debugTex = 0;
    GLuint bloomExtractFBO = 0;
    GLuint bloomExtractTex = 0;
    GLuint bloomBlurFBO = 0;
    GLuint bloomBlurTex = 0;
    GLuint bloomScratchFBO = 0;
    GLuint bloomScratchTex = 0;
    GLuint exposureFBO[2] = {0, 0};
    GLuint exposureTex[2] = {0, 0};
    int exposureIndex = 0;
    bool postFxReady = false;
    bool postReady = false;

    // Cached shader uniforms.
    GLint uSSAOParams0 = -1;
    GLint uSSAOParams1 = -1;
    GLint uSSAOParams2 = -1;
    GLint uSSRParams0 = -1;
    GLint uSSRParams1 = -1;
    GLint uSSRParams2 = -1;
    GLint uSSRFilter0 = -1;
    GLint uSSRFilter1 = -1;
    GLint uSSRFilter2 = -1;
    GLint uBlurParams0 = -1;
    GLint uBlurParams1 = -1;
    GLint uSSRCompositeStrength = -1;
    GLint uDebugParams = -1;
    GLint uDebugMode = -1;
    GLint uBloomParams = -1;
    GLint uBloomBlur = -1;
    GLint uBloomRadius = -1;
    GLint uExposureParams0 = -1;
    GLint uCompositeParams = -1;
};

class GUIQuality final
{
public:
    static GUIQuality &Instance();

    bool Init();
    void Term();

    void SetMSAA4xEnabled(bool v);
    bool IsMSAA4xEnabled() const;
    void SetSSAOEnabled(bool v);
    bool IsSSAOEnabled() const;
    void SetSSREnabled(bool v);
    bool IsSSREnabled() const;
    void SetBloomEnabled(bool v);
    bool IsBloomEnabled() const;
    void SetDynamicExposureEnabled(bool v);
    bool IsDynamicExposureEnabled() const;

    void SetTuningMenuOpen(bool v);
    bool IsTuningMenuOpen() const;
    bool HandleImGuiWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, LRESULT *result);
    void DrawTuningMenu();

    void BeginScene(const SceneDesc *scene);
    void ApplyOpaqueScene(const SceneDesc *scene);
    void EndScene(const SceneDesc *scene);
    void ApplyGlobalLightScale(const LTVector &scale, bool invertHack);
    void ApplyGlobalLightAdd(const LTVector &add);

    GUIQualityState &State() { return m_state; }
    const GUIQualityState &State() const { return m_state; }

private:
    GUIQuality() = default;
    GUIQualityState m_state{};
};
