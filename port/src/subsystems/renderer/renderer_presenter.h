#pragma once
#include "../../gl_renderer.h"
#include <GL/gl.h>
#include <array>
#include <vector>
#include <cstdint>

struct RendererPresenterVertex
{
    float x, y;
    float u, v;
};

struct RendererPresenterState
{
    static constexpr size_t kMaxBatchQuads = 4096;
    static constexpr size_t kMaxBatchVerts = kMaxBatchQuads * 6;

    std::array<RendererPresenterVertex, kMaxBatchVerts> batchVerts{};
    size_t batchVertCount = 0;
    GLuint batchTexture = 0;
    LTSurfaceBlend batchBlend = LTSURFACEBLEND_ALPHA;
    HLTCOLOR batchColor = 0xFFFFFFFFu;
    float batchAlpha = 1.0f;
    bool batchUseKey = false;
    uint32 batchKey = 0;
    bool batchUseTexAlpha = false;

    uint64_t frameBlits = 0;
    uint64_t frameOptimizedBlits = 0;
    uint64_t frameDirectBlits = 0;
    uint64_t frameDrawCalls = 0;
    uint64_t frameTextureUploads = 0;
    bool frameHasPresentableContent = false;
    uint64_t skippedEmptyPresents = 0;
    ULONGLONG lastPerfLog = 0;

    bool emulateDiscardSwap = true;
    uint64_t discardColorResets = 0;
    uint64_t clearScreenCount = 0;
    uint64_t clearRenderOnlyCount = 0;
    uint64_t clearScreenRenderCount = 0;

    bool dirtyAny = false;
    bool dirtyFull = false;
    uint32 dirtyRectCount = 0;

    std::vector<uint8_t> screenPixels;
    std::vector<uint8_t> screenReadbackScratch;
    std::vector<uint8_t> screenUploadScratch;
    LTRect screenLockRect{0, 0, 0, 0};
    bool screenShadowValid = false;
    uint64_t screenShadowReuseCount = 0;
    uint64_t screenShadowReadbackCount = 0;
    bool screenLocked = false;
    size_t screenVisibleBytes = 0;
    size_t screenBackingBytes = 0;
};

class RendererPresenter final
{
public:
    static RendererPresenter &Instance();

    void Init(bool windowed, int width, int height);
    void Term();
    void MarkFrameContent();
    bool IsFullScreenRect(const LTRect *rect) const;
    void InvalidateScreenRect(const LTRect *rect);
    void ClearInvalidScreenRects();
    void ConfigureSwapModel(bool windowed);
    void ResetScreenStorage(int width, int height);
    void FlushBatch();

    void PresentSurface(GLSurface *surface, const LTRect *src, const LTRect *dst, float alpha, bool colorKey, uint32 key, bool textureAlpha = false);
    bool PresentWarp(GLSurface *surface, const BlitRequest *request);
    bool LockScreen(int left, int top, int right, int bottom, void **data, int *pitch);
    void UnlockScreen();
    void BlitToScreen(BlitRequest *request);
    bool WarpToScreen(BlitRequest *request);
    void BlitFromScreen(BlitRequest *request);
    void SwapBuffers(uint32 flags);

    RendererPresenterState &State() { return m_state; }
    const RendererPresenterState &State() const { return m_state; }

private:
    RendererPresenter() = default;
    RendererPresenterState m_state{};
};
