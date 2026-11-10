#pragma once
#include "../../gl_renderer.h"
#include <GL/gl.h>
#include <array>
#include <cstdint>
#include <cstddef>
namespace avp2::render
{
    class Shader;
}

enum class PerfTimingSystem : uint8_t
{
    World = 0,
    ModelPrep,
    SolidFx,
    Shadows,
    Models,
    WorldModels,
    Translucent,
    NoZ,
    ReallyClose,
    ObjectList,
    Quality,
    Streaming,
    Present,
    Count
};

constexpr size_t kPerfTimingSystemCount = static_cast<size_t>(PerfTimingSystem::Count);
constexpr size_t kPerfHistorySamples = 180;

struct RendererCoreState
{
    HWND hwnd = nullptr;
    HDC hdc = nullptr;
    HGLRC glrc = nullptr;
    int width = 0;
    int height = 0;
    bool in3D = false;
    bool perfOverlayEnabled = false;
    bool vsyncEnabled = true;
    DWORD initThread = 0;
    DWORD lastContextThread = 0;
    uint64_t contextBindCount = 0;
    uint64_t contextThreadChangeCount = 0;
    bool pixelFormatSwapCopy = false;
    GLuint screenQuadVao = 0;
    GLuint screenQuadVbo = 0;
    GLuint perfFontTexture = 0;
    GLuint perfWhiteTexture = 0;
    LARGE_INTEGER perfQpcFreq{};
    LARGE_INTEGER perfLastQpc{};
    double perfFps = 0.0;
    double perfFrameMs = 0.0;
    std::array<double, kPerfHistorySamples> perfFrameHistory{};
    std::array<double, kPerfHistorySamples> perfFpsHistory{};
    size_t perfHistoryWrite = 0;
    size_t perfHistoryCount = 0;
    std::array<double, kPerfTimingSystemCount> perfSystemMs{};
    std::array<double, kPerfTimingSystemCount> perfLastSystemMs{};
    double perfLastHostMs = 0.0;
    double perfLastUntypedMs = 0.0;
    double perfPeakHostMs = 0.0;
    double perfPeakUntypedMs = 0.0;
    double perfPeakFrameMs = 0.0;
    ULONGLONG perfPeakWindowTick = 0;
    ULONGLONG perfLastHostSpikeLogTick = 0;
    std::array<double, kPerfTimingSystemCount> perfPeakSystemMs{};
    LARGE_INTEGER perfFrameStartQpc{};
    bool perfFrameStartSeen = false;
    double perfWorstFrameMs = 0.0;
    ULONGLONG perfLastSlowLogTick = 0;
    uint32_t perfModelPvs = 0;
    uint32_t perfModelOpaque = 0;
    uint32_t perfModelChroma = 0;
    uint32_t perfModelTranslucent = 0;
    uint32_t perfModelReallyClose = 0;
    uint32_t perfWorldModelTranslucent = 0;
    uint32_t perfSprites = 0;
    uint32_t perfParticles = 0;
    uint32_t perfPolyGrids = 0;
    uint32_t perfLineSystems = 0;
    uint32_t perfCanvases = 0;

    // Authored material profiling (F12). These are CPU times accumulated across
    // all world-material applications in the completed frame.
    double perfMaterialApplyMs = 0.0;
    double perfMaterialResolveMs = 0.0;
    double perfMaterialStateMs = 0.0;
    double perfMaterialDerivedMs = 0.0;
    double perfMaterialNameMs = 0.0;
    double perfMaterialLookupMs = 0.0;
    double perfMaterialLoadMs = 0.0;
    uint32_t perfMaterialApplyCalls = 0;
    uint32_t perfMaterialResolveCalls = 0;
    uint32_t perfMaterialBindings = 0;
    uint32_t perfMaterialRecordsLoaded = 0;

    avp2::render::Shader *scenePostShader = nullptr;
    GLint scenePostColorUniform = -1;
};

class RendererCore final
{
public:
    static RendererCore &Instance();
    bool Init(HWND hwnd, int width, int height, bool windowed);
    void Term();
    bool AcquireThreadContext();
    void ReleaseThreadContext();
    // Resolution/mode changes unload and rebuild the renderer while the game may
    // still have map/loading callers on other threads.  Lifecycle operations
    // use the same lock as every normal GL call so teardown/init is atomic.
    void AcquireLifecycleExclusive();
    void ReleaseLifecycleExclusive();
    void Clear(const LTRect *rect, uint32 flags, const LTVector *color);
    bool Start3D();
    bool End3D();
    bool IsIn3D() const;
    int Width() const;
    int Height() const;
    HWND Window() const;
    HDC DeviceContext() const;
    DWORD InitThread() const;
    uint64_t GLContextBindCount() const;
    uint64_t GLContextThreadChangeCount() const;
    GLuint ScreenQuadVao() const;
    GLuint ScreenQuadVbo() const;
    avp2::render::Shader *ScenePostShader() const { return m_state.scenePostShader; }
    GLint ScenePostColorUniform() const { return m_state.scenePostColorUniform; }
    bool PerfTimingActive() const { return m_state.perfOverlayEnabled; }
    int64_t PerfTimingBegin() const;
    void PerfTimingEnd(PerfTimingSystem system, int64_t startTicks);
    void PerfSetSceneObjectCounts(uint32_t modelPvs, uint32_t opaque, uint32_t chroma, uint32_t translucent, uint32_t reallyClose,
                                  uint32_t translucentWorldModels, uint32_t sprites, uint32_t particles, uint32_t polyGrids,
                                  uint32_t lineSystems, uint32_t canvases);
    void PerfMarkFrameStart();
    void PerfFrameComplete();
    void DrawPerfOverlay();
    void GetScreenFormat(PFormat *format) const;
    void SetVSyncEnabled(bool enabled);
    bool IsVSyncEnabled() const;
    void SetPerfOverlayEnabled(bool enabled);
    bool IsPerfOverlayEnabled() const;
    RendererCoreState &State() { return m_state; }
    const RendererCoreState &State() const { return m_state; }

private:
    RendererCore() = default;
    RendererCoreState m_state{};
};

class RendererContextScope final
{
public:
    RendererContextScope() : m_acquired(RendererCore::Instance().AcquireThreadContext()) {}
    ~RendererContextScope()
    {
        if (m_acquired)
            RendererCore::Instance().ReleaseThreadContext();
    }
    RendererContextScope(const RendererContextScope &) = delete;
    RendererContextScope &operator=(const RendererContextScope &) = delete;
    explicit operator bool() const { return m_acquired; }

private:
    bool m_acquired = false;
};
