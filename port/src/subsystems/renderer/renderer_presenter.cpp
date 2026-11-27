#include "renderer_presenter.h"
#include "renderer_core.h"
#include "Framebuffer.h"
#include "renderer_2d.h"
#include "gui_quality.h"
#include "../../gl_loader.h"
#include "gl_upload_stats.h"
#include "utils/log.h"
#include "../../shaders/shader.h"

#include <GL/gl.h>
#include <algorithm>
#include <cmath>
#include <cstring>

#ifndef GL_READ_FRAMEBUFFER
#define GL_READ_FRAMEBUFFER 0x8CA8
#endif
#ifndef GL_DRAW_FRAMEBUFFER
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#endif
#ifndef GL_FRAMEBUFFER
#define GL_FRAMEBUFFER 0x8D40
#endif
#ifndef GL_COLOR_ATTACHMENT0
#define GL_COLOR_ATTACHMENT0 0x8CE0
#endif

namespace
{
    constexpr size_t SCREEN_LOCK_GUARD_BYTES = 1024 * 1024;
    constexpr uint8_t SCREEN_LOCK_CANARY = 0xCD;

    RendererPresenter &Presenter() { return RendererPresenter::Instance(); }
    RendererPresenterState &PState() { return Presenter().State(); }
    RendererCore &Core() { return RendererCore::Instance(); }
    Framebuffer &FB() { return Framebuffer::Instance(); }
    Renderer2D &TwoD() { return Renderer2D::Instance(); }

    LTSurfaceBlend CurrentBlend()
    {
        LTSurfaceBlend blend = LTSURFACEBLEND_ALPHA;
        TwoD().GetBlend(blend);
        return blend;
    }

    HLTCOLOR CurrentColor()
    {
        HLTCOLOR color = 0xFFFFFFFFu;
        TwoD().GetColor(color);
        return color;
    }

    void GetPresentClientSize(int &width, int &height)
    {
        width = Core().Width();
        height = Core().Height();
        HWND hwnd = Core().Window();
        if (!hwnd)
            return;
        RECT rc{};
        if (GetClientRect(hwnd, &rc))
        {
            const int w = rc.right - rc.left;
            const int h = rc.bottom - rc.top;
            if (w > 0 && h > 0)
            {
                width = w;
                height = h;
            }
        }
    }

    void ComputePresentClientRect(int presentW, int presentH, RECT &outRc)
    {
        int dstX0 = 0, dstY0 = 0, dstX1 = presentW, dstY1 = presentH;
        const int logicalW = Core().Width();
        const int logicalH = Core().Height();
        if (logicalW > 0 && logicalH > 0 && presentW > 0 && presentH > 0)
        {
            const double logicalAspect = static_cast<double>(logicalW) / logicalH;
            const double clientAspect = static_cast<double>(presentW) / presentH;
            int scaledW = presentW, scaledH = presentH;
            if (clientAspect > logicalAspect)
                scaledW = std::max(1, static_cast<int>(presentH * logicalAspect + 0.5));
            else if (clientAspect < logicalAspect)
                scaledH = std::max(1, static_cast<int>(presentW / logicalAspect + 0.5));
            dstX0 = (presentW - scaledW) / 2;
            dstY0 = (presentH - scaledH) / 2;
            dstX1 = dstX0 + scaledW;
            dstY1 = dstY0 + scaledH;
        }
        outRc.left = dstX0;
        outRc.right = dstX1;
        outRc.top = presentH - dstY1;
        outRc.bottom = presentH - dstY0;
    }

    void ApplyBlend(LTSurfaceBlend blend)
    {
        avp2::render::GLStateCache::Instance().SetBlendEquation(GL_FUNC_ADD_);
        GLStateEnable(GL_BLEND);
        switch (blend)
        {
        case LTSURFACEBLEND_SOLID:
            GLStateBlendFunc(GL_ONE_, GL_ZERO_);
            break;
        case LTSURFACEBLEND_ADD:
            GLStateBlendFunc(GL_ONE_, GL_ONE_);
            break;
        case LTSURFACEBLEND_MULTIPLY:
            GLStateBlendFunc(GL_DST_COLOR_, GL_ZERO_);
            break;
        case LTSURFACEBLEND_MULTIPLY2:
            GLStateBlendFunc(GL_DST_COLOR_, GL_SRC_COLOR_);
            break;
        case LTSURFACEBLEND_MASK:
            GLStateBlendFunc(GL_ZERO_, GL_ONE_MINUS_SRC_COLOR_);
            break;
        case LTSURFACEBLEND_MASKADD:
            GLStateBlendFunc(GL_ONE_, GL_ONE_MINUS_SRC_COLOR_);
            break;
        case LTSURFACEBLEND_ALPHA:
        default:
            GLStateBlendFunc(GL_SRC_ALPHA_, GL_ONE_MINUS_SRC_ALPHA_);
            break;
        }
    }

    float ToNdcX(float x) { return (x / static_cast<float>(Core().Width())) * 2.0f - 1.0f; }
    float ToNdcY(float y) { return 1.0f - (y / static_cast<float>(Core().Height())) * 2.0f; }

    bool BatchStateMatches(GLuint texture, float alpha, bool useKey, uint32 key, bool useTexAlpha)
    {
        const auto &s = PState();
        return s.batchVertCount > 0 && s.batchTexture == texture && s.batchBlend == CurrentBlend() &&
               s.batchColor == CurrentColor() && s.batchAlpha == alpha && s.batchUseKey == useKey &&
               s.batchKey == key && s.batchUseTexAlpha == useTexAlpha;
    }

    void BeginBatchState(GLuint texture, float alpha, bool useKey, uint32 key, bool useTexAlpha)
    {
        auto &s = PState();
        s.batchTexture = texture;
        s.batchBlend = CurrentBlend();
        s.batchColor = CurrentColor();
        s.batchAlpha = alpha;
        s.batchUseKey = useKey;
        s.batchKey = key;
        s.batchUseTexAlpha = useTexAlpha;
    }
}

RendererPresenter &RendererPresenter::Instance()
{
    static RendererPresenter v;
    return v;
}

void RendererPresenter::Init(bool windowed, int width, int height)
{
    m_state = RendererPresenterState{};
    ConfigureSwapModel(windowed);
    ResetScreenStorage(width, height);
}

void RendererPresenter::Term()
{
    m_state = RendererPresenterState{};
}

void RendererPresenter::FlushBatch()
{
    auto &s = m_state;
    if (s.batchVertCount == 0)
        return;
    ApplyBlend(s.batchBlend);
    const float cr = ((s.batchColor >> 16) & 0xFF) / 255.0f;
    const float cg = ((s.batchColor >> 8) & 0xFF) / 255.0f;
    const float cb = (s.batchColor & 0xFF) / 255.0f;
    const float ca = ((s.batchColor >> 24) & 0xFF) / 255.0f;
    const float kr = ((s.batchKey >> 16) & 0xFF) / 255.0f;
    const float kg = ((s.batchKey >> 8) & 0xFF) / 255.0f;
    const float kb = (s.batchKey & 0xFF) / 255.0f;
    GLTrackedNamedBufferSubData(Core().ScreenQuadVbo(), 0,
                                static_cast<GLsizeiptr>(sizeof(RendererPresenterVertex) * s.batchVertCount), s.batchVerts.data(), GLUploadCategory::Renderer);
    auto *shader = TwoD().BlitShader();
    if (!shader)
    {
        s.batchVertCount = 0;
        return;
    }
    shader->Use();
    GLUniform1i(TwoD().BlitTexUniform(), 0);
    GLUniform4f(TwoD().BlitColorUniform(), cr, cg, cb, ca);
    GLUniform1f(TwoD().BlitAlphaUniform(), std::clamp(s.batchAlpha, 0.0f, 1.0f));
    GLUniform1i(TwoD().BlitUseKeyUniform(), s.batchUseKey ? 1 : 0);
    GLUniform3f(TwoD().BlitKeyUniform(), kr, kg, kb);
    GLUniform1i(TwoD().BlitUseTexAlphaUniform(), s.batchUseTexAlpha ? 1 : 0);
    GLStateBindTextureUnit(0, s.batchTexture);
    GLStateBindVertexArray(Core().ScreenQuadVao());
    glf.DrawArrays(GL_TRIANGLES_, 0, static_cast<GLsizei>(s.batchVertCount));
    ++s.frameDrawCalls;
    s.frameHasPresentableContent = true;
    s.batchVertCount = 0;
}

bool RendererPresenter::IsFullScreenRect(const LTRect *rect) const
{
    return rect == nullptr ||
           (rect->m_nLeft <= 0 && rect->m_nTop <= 0 &&
            rect->m_nRight >= Core().Width() && rect->m_nBottom >= Core().Height());
}

void RendererPresenter::InvalidateScreenRect(const LTRect *rect)
{
    m_state.dirtyAny = true;
    const bool full = IsFullScreenRect(rect);
    if (full)
    {
        m_state.dirtyFull = true;
        m_state.dirtyRectCount = 1;
        return;
    }
    if (!m_state.dirtyFull)
    {
        if (m_state.dirtyRectCount < 100)
            ++m_state.dirtyRectCount;
        else
        {
            m_state.dirtyFull = true;
            m_state.dirtyRectCount = 1;
        }
    }
}

void RendererPresenter::ClearInvalidScreenRects()
{
    m_state.dirtyAny = false;
    m_state.dirtyFull = false;
    m_state.dirtyRectCount = 0;
}

void RendererPresenter::ConfigureSwapModel(bool windowed)
{
    m_state.emulateDiscardSwap = !windowed;
}

void RendererPresenter::ResetScreenStorage(int width, int height)
{
    m_state.screenVisibleBytes = static_cast<size_t>(std::max(0, width)) * static_cast<size_t>(std::max(0, height)) * 4u;
    m_state.screenBackingBytes = m_state.screenVisibleBytes + SCREEN_LOCK_GUARD_BYTES;
    m_state.screenPixels.resize(m_state.screenBackingBytes);
    if (m_state.screenBackingBytes >= m_state.screenVisibleBytes)
        std::fill(m_state.screenPixels.begin() + m_state.screenVisibleBytes, m_state.screenPixels.end(), SCREEN_LOCK_CANARY);
    m_state.screenShadowValid = false;
    m_state.screenLocked = false;
    m_state.screenShadowReuseCount = 0;
    m_state.screenShadowReadbackCount = 0;
}

void RendererPresenter::MarkFrameContent()
{
    PState().frameHasPresentableContent = true;
    // A RenderScene can touch arbitrary screen pixels.  Stock scene rendering
    // is normally preceded by a full clear, but full invalidation here keeps
    // FLIPSCREEN_DIRTY correct even for unusual object-list frames.
    Presenter().InvalidateScreenRect(nullptr);
}

void RendererPresenter::PresentSurface(GLSurface *s, const LTRect *srcRect, const LTRect *dstRect,
                                       float alpha, bool useColorKey, uint32 colorKey, bool useTextureAlpha)
{
    PState().screenShadowValid = false;

    if (!s || !TwoD().BlitShader())
        return;

    Renderer2D::Instance().EnsureTexture(s);
    ++PState().frameBlits;

    LTRect src{0, 0, s->width, s->height};
    LTRect dst{0, 0, Core().Width(), Core().Height()};
    if (srcRect)
        src = *srcRect;
    if (dstRect)
    {
        dst = *dstRect;
        const LTRect rawDst = dst;

        // Full-screen pre-3D images (the intro splash is submitted this way)
        // are authored at a fixed aspect ratio.  Talon supplies a stretched
        // destination rectangle, so contain-fit the source into the actual
        // backbuffer and preserve its aspect ratio.  This is intentionally
        // limited to full-screen pre-3D blits; ordinary 2D coordinates remain
        // exactly as submitted by Talon.
        const bool fullSource =
            src.m_nLeft == 0 && src.m_nTop == 0 &&
            src.m_nRight == s->width && src.m_nBottom == s->height;
        const int rawW = rawDst.m_nRight - rawDst.m_nLeft;
        const int rawH = rawDst.m_nBottom - rawDst.m_nTop;
        const bool canonicalFullscreen =
            rawDst.m_nLeft == 0 && rawDst.m_nTop == 0 &&
            ((rawW == 640 && rawH == 480) ||
             (rawW == Core().Width() && rawH == Core().Height()));
        const bool preserveFullscreenAspect =
            !Core().IsIn3D() && fullSource && canonicalFullscreen &&
            s->width >= 320 && s->height >= 200;

        if (preserveFullscreenAspect)
        {
            const int windowW = std::max(1, Core().Width());
            const int windowH = std::max(1, Core().Height());
            const float srcAspect = static_cast<float>(s->width) / static_cast<float>(std::max(1, s->height));
            const float windowAspect = static_cast<float>(windowW) / static_cast<float>(windowH);

            dst = LTRect{0, 0, windowW, windowH};
            if (windowAspect > srcAspect)
            {
                const int targetW = std::max(1, static_cast<int>(static_cast<float>(windowH) * srcAspect + 0.5f));
                dst.m_nLeft = (windowW - targetW) / 2;
                dst.m_nRight = dst.m_nLeft + targetW;
            }
            else if (windowAspect < srcAspect)
            {
                const int targetH = std::max(1, static_cast<int>(static_cast<float>(windowW) / srcAspect + 0.5f));
                dst.m_nTop = (windowH - targetH) / 2;
                dst.m_nBottom = dst.m_nTop + targetH;
            }

            if (LogIsSessionEnabled())
            {
                static int fullscreenAspectBudget = 32;
                if (LogIsSessionEnabled() && ((fullscreenAspectBudget > 0 && fullscreenAspectBudget--)))
                    LOG_SESSION("2D-FULLSCREEN-ASPECT surf=%p size=%dx%d raw=(%d,%d)-(%d,%d) out=(%d,%d)-(%d,%d)",
                                s, s->width, s->height,
                                rawDst.m_nLeft, rawDst.m_nTop, rawDst.m_nRight, rawDst.m_nBottom,
                                dst.m_nLeft, dst.m_nTop, dst.m_nRight, dst.m_nBottom);
            }
        }
    }

    const float u0 = static_cast<float>(src.m_nLeft) / s->width;
    const float v0 = static_cast<float>(src.m_nTop) / s->height;
    const float u1 = static_cast<float>(src.m_nRight) / s->width;
    const float v1 = static_cast<float>(src.m_nBottom) / s->height;

    const float x0 = ToNdcX(static_cast<float>(dst.m_nLeft));
    const float y0 = ToNdcY(static_cast<float>(dst.m_nTop));
    const float x1 = ToNdcX(static_cast<float>(dst.m_nRight));
    const float y1 = ToNdcY(static_cast<float>(dst.m_nBottom));

    const float clampedAlpha = std::clamp(alpha, 0.0f, 1.0f);

    if (PState().batchVertCount > 0 &&
        !BatchStateMatches(s->texture, clampedAlpha, useColorKey, colorKey, useTextureAlpha))
    {
        Presenter().FlushBatch();
    }

    if (PState().batchVertCount == 0)
        BeginBatchState(s->texture, clampedAlpha, useColorKey, colorKey, useTextureAlpha);

    if (PState().batchVertCount + 6 > RendererPresenterState::kMaxBatchVerts)
    {
        Presenter().FlushBatch();
        BeginBatchState(s->texture, clampedAlpha, useColorKey, colorKey, useTextureAlpha);
    }

    RendererPresenterVertex *v = PState().batchVerts.data() + PState().batchVertCount;
    v[0] = {x0, y0, u0, v0};
    v[1] = {x1, y0, u1, v0};
    v[2] = {x1, y1, u1, v1};
    v[3] = {x0, y0, u0, v0};
    v[4] = {x1, y1, u1, v1};
    v[5] = {x0, y1, u0, v1};

    PState().batchVertCount += 6;

    // Both the optimized textured path and the stock direct blit path
    // invalidate their destination rectangles before a dirty flip.
    Presenter().InvalidateScreenRect(&dst);
}

bool RendererPresenter::LockScreen(int left, int top, int right, int bottom, void **data, int *pitch)
{
    Presenter().FlushBatch();

    if (!data || PState().screenLocked)
        return false;

    LTRect requested{
        std::clamp(left, 0, Core().Width()),
        std::clamp(top, 0, Core().Height()),
        std::clamp(right, 0, Core().Width()),
        std::clamp(bottom, 0, Core().Height())};
    if (requested.m_nRight < requested.m_nLeft)
        std::swap(requested.m_nRight, requested.m_nLeft);
    if (requested.m_nBottom < requested.m_nTop)
        std::swap(requested.m_nBottom, requested.m_nTop);
    if (requested.m_nRight == requested.m_nLeft || requested.m_nBottom == requested.m_nTop)
        return false;
    PState().screenLockRect = requested;

    const int rowBytes = Core().Width() * 4;
    PState().screenVisibleBytes = static_cast<size_t>(rowBytes) * Core().Height();
    PState().screenBackingBytes = PState().screenVisibleBytes + SCREEN_LOCK_GUARD_BYTES;

    if (PState().screenPixels.size() != PState().screenBackingBytes)
        PState().screenPixels.resize(PState().screenBackingBytes);

    // Stock d3d_LockScreen maps the current D3D backbuffer directly.  Our
    // logical FBO cannot be CPU-mapped, so keep a top-down shadow and only
    // recapture it after GL rendering invalidates the shadow.  Consecutive
    // Lock/Unlock operations therefore see the previous unlock exactly like
    // locking the same D3D backbuffer again, without a fake fullscreen draw.
    bool didReadback = false;
    if (!PState().screenShadowValid)
    {
        if (PState().screenReadbackScratch.size() != PState().screenVisibleBytes)
            PState().screenReadbackScratch.resize(PState().screenVisibleBytes);

        if (FB().Ready())
        {
            FB().Bind(GL_READ_FRAMEBUFFER, FB().Logical());
            glReadBuffer(GL_COLOR_ATTACHMENT0);
        }
        glReadPixels(0, 0, Core().Width(), Core().Height(), GL_BGRA_, GL_UNSIGNED_BYTE,
                     PState().screenReadbackScratch.data());
        FB().BindLogical();

        for (int y = 0; y < Core().Height(); ++y)
        {
            const uint8_t *src = PState().screenReadbackScratch.data() +
                                 static_cast<size_t>(Core().Height() - 1 - y) * rowBytes;
            uint8_t *dst = PState().screenPixels.data() + static_cast<size_t>(y) * rowBytes;
            std::memcpy(dst, src, rowBytes);
        }
        ++PState().screenShadowReadbackCount;
        PState().screenShadowValid = true;
        didReadback = true;
    }
    else
    {
        ++PState().screenShadowReuseCount;
    }

    // Keep the known AVP2 transition-time overrun harmless and measurable.
    std::fill(PState().screenPixels.begin() + PState().screenVisibleBytes,
              PState().screenPixels.end(), SCREEN_LOCK_CANARY);

    // D3D LockRect(rect) returns pBits at the requested rectangle origin while
    // retaining the actual backbuffer pitch.
    const size_t byteOffset = static_cast<size_t>(requested.m_nTop) * rowBytes +
                              static_cast<size_t>(requested.m_nLeft) * 4;
    *data = PState().screenPixels.data() + byteOffset;
    if (pitch)
        *pitch = rowBytes;

    PState().screenLocked = true;
    static uint32_t s_lockDetailBudget = 96;
    if (LogIsSessionEnabled() && (s_lockDetailBudget))
    {
        --s_lockDetailBudget;
        LOG_SESSION("LockScreen rect=(%d,%d)-(%d,%d) source=%s shadow=%s data=%p pitch=%d visible=%zu backing=%zu guard=%zu",
                    requested.m_nLeft, requested.m_nTop,
                    requested.m_nRight, requested.m_nBottom,
                    FB().Ready() ? "logicalFBO" : "defaultFB",
                    didReadback ? "readback" : "reuse",
                    *data, rowBytes, PState().screenVisibleBytes, PState().screenBackingBytes,
                    SCREEN_LOCK_GUARD_BYTES);
    }
    return true;
}

void RendererPresenter::UnlockScreen()
{
    if (!PState().screenLocked)
        return;

    if (LogIsSessionEnabled())
    {
        size_t firstTouched = SIZE_MAX;
        size_t lastTouched = 0;
        size_t touched = 0;
        for (size_t i = PState().screenVisibleBytes; i < PState().screenBackingBytes; ++i)
        {
            if (PState().screenPixels[i] != SCREEN_LOCK_CANARY)
            {
                if (firstTouched == SIZE_MAX)
                    firstTouched = i;
                lastTouched = i;
                ++touched;
            }
        }
        if (firstTouched != SIZE_MAX)
        {
            LOG_SESSION("LOCKSCREEN OVERRUN: touched=%zu first=+0x%zX last=+0x%zX beyondVisible=%zu bytes",
                        touched, firstTouched, lastTouched,
                        lastTouched + 1 - PState().screenVisibleBytes);
        }
    }

    // Stock d3d_UnlockScreen simply unlocks the already-mapped backbuffer and
    // invalidates that lock rectangle.  Do the equivalent direct texture
    // update here; do NOT route it through PresentSurface/blending and do NOT
    // expose it until the engine's later FlipScreen call.
    const LTRect dirty = PState().screenLockRect;
    const int w = dirty.m_nRight - dirty.m_nLeft;
    const int h = dirty.m_nBottom - dirty.m_nTop;
    const size_t packedRowBytes = static_cast<size_t>(w) * 4;
    const size_t packedBytes = packedRowBytes * static_cast<size_t>(h);
    if (PState().screenUploadScratch.size() < packedBytes)
        PState().screenUploadScratch.resize(packedBytes);

    const int fullPitch = Core().Width() * 4;
    for (int row = 0; row < h; ++row)
    {
        // OpenGL upload row zero is the bottom of the texture.  The CPU shadow
        // is top-down, so pack bottom screen row first.
        const int srcY = dirty.m_nBottom - 1 - row;
        const uint8_t *src = PState().screenPixels.data() +
                             static_cast<size_t>(srcY) * fullPitch +
                             static_cast<size_t>(dirty.m_nLeft) * 4;
        uint8_t *dst = PState().screenUploadScratch.data() +
                       static_cast<size_t>(row) * packedRowBytes;
        std::memcpy(dst, src, packedRowBytes);
    }

    if (w > 0 && h > 0 && FB().ColorTexture() && glf.TextureSubImage2D)
    {
        glf.TextureSubImage2D(
            FB().ColorTexture(), 0,
            dirty.m_nLeft, Core().Height() - dirty.m_nBottom,
            w, h, GL_BGRA_, GL_UNSIGNED_BYTE,
            PState().screenUploadScratch.data());
        ++PState().frameTextureUploads;
    }

    // The CPU shadow now exactly matches the logical D3D-style backbuffer.
    PState().screenShadowValid = true;
    Presenter().InvalidateScreenRect(&dirty);
    PState().screenLocked = false;

    static uint32_t s_unlockDetailBudget = 96;
    if (LogIsSessionEnabled() && (s_unlockDetailBudget))
    {
        --s_unlockDetailBudget;
        LOG_SESSION("UnlockScreen -> direct logical backbuffer update rect=(%d,%d)-(%d,%d) deferredPresent=1",
                    dirty.m_nLeft, dirty.m_nTop, dirty.m_nRight, dirty.m_nBottom);
    }
}

void RendererPresenter::BlitToScreen(BlitRequest *request)
{
    if (!request || !request->m_hBuffer)
        return;

    auto *s = reinterpret_cast<GLSurface *>(request->m_hBuffer);

    const bool requestUsesKey = (request->m_dwBlitOptions & BLIT_TRANSPARENT) != 0;
    const uint32 requestKey = request->m_dwTransparentColor.dwVal;

    // d3d.ren has two distinct paths here:
    //
    //  * optimized surface + StartOptimized2D + Start3D -> textured/blended
    //  * everything else -> ReallyBlitToScreen, a direct backbuffer copy
    //
    // The old OpenGL compatibility path blended every blit.  That is not D3D
    // behavior and is especially visible on loading-screen counters/bars.
    if (TwoD().IsOptimized() && Core().IsIn3D())
    {
        ++PState().frameOptimizedBlits;
        static uint32_t s_optBlitLogBudget = 48;
        if (LogIsSessionEnabled() && (s_optBlitLogBudget))
        {
            --s_optBlitLogBudget;
            LOG_SESSION("BLIT PATH optimized surf=%p blend=%d alpha=%.3f requestKey=%d optimized=%d",
                        s, static_cast<int>(CurrentBlend()), request->m_fAlpha,
                        requestUsesKey ? 1 : 0, s->optimized ? 1 : 0);
        }

        if (!s->optimized)
        {
            // Stock auto-optimizes on first optimized-2D use, baking the
            // transparent color selected by that request into the surface.
            s->optimized = true;
            s->transparentColor = requestUsesKey ? requestKey : 0xFFFFFFFFu;
            s->dirty = true;
            Renderer2D::Instance().EnsureTexture(s);
        }

        // Once a surface is optimized, stock D3D draws the alpha-baked tiles;
        // it does not re-run the request's color key in the pixel stage.
        // The optimized texture alpha was generated by EnsureTexture above.
        Presenter().PresentSurface(s, request->m_pSrcRect, request->m_pDestRect,
                                   request->m_fAlpha, false, 0, true);

        static uint32_t s_loadingBlitBudget = 160;
        if (LogIsSessionEnabled() && (GetCurrentThreadId() != Core().InitThread() && s_loadingBlitBudget))
        {
            --s_loadingBlitBudget;
            LTRect sr{0, 0, s->width, s->height};
            LTRect dr{0, 0, Core().Width(), Core().Height()};
            if (request->m_pSrcRect)
                sr = *request->m_pSrcRect;
            if (request->m_pDestRect)
                dr = *request->m_pDestRect;
            LOG_SESSION("LOAD-BLIT tid=%lu surf=%p size=%dx%d src=(%d,%d)-(%d,%d) dst=(%d,%d)-(%d,%d) alpha=%.3f blend=%d optKey=%08X reqKey=%d:%08X",
                        static_cast<unsigned long>(GetCurrentThreadId()), s, s->width, s->height,
                        sr.m_nLeft, sr.m_nTop, sr.m_nRight, sr.m_nBottom,
                        dr.m_nLeft, dr.m_nTop, dr.m_nRight, dr.m_nBottom,
                        request->m_fAlpha, static_cast<int>(CurrentBlend()), s->transparentColor,
                        requestUsesKey ? 1 : 0, requestKey);
        }
        return;
    }

    // ReallyBlitToScreen does not consume optimized-2D color, blend mode, or
    // per-blit alpha.  It overwrites destination pixels, with color keying as
    // the only optional transparency operation.  Emulate that on the logical
    // FBO using the same textured quad shader but force ONE/ZERO + opaque white
    // and flush immediately so the temporary state cannot leak into a later
    // optimized batch.
    ++PState().frameDirectBlits;
    static uint32_t s_directBlitLogBudget = 48;
    if (LogIsSessionEnabled() && (s_directBlitLogBudget))
    {
        --s_directBlitLogBudget;
        LOG_SESSION("BLIT PATH direct-copy surf=%p in3D=%d inOpt2D=%d alphaIgnored=%.3f requestKey=%d",
                    s, Core().IsIn3D() ? 1 : 0, TwoD().IsOptimized() ? 1 : 0,
                    request->m_fAlpha, requestUsesKey ? 1 : 0);
    }
    Presenter().FlushBatch();
    const auto oldBlend = CurrentBlend();
    const auto oldColor = CurrentColor();
    const auto savedGL = avp2::render::GLStateCache::Instance().Capture();

    // Direct surface copies ignore the 3D depth buffer even when called while
    // a D3D scene is active (stock temporarily EndScene/Blt/BeginScene).
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);
    TwoD().SetBlend(LTSURFACEBLEND_SOLID);
    TwoD().SetColor(0xFFFFFFFFu);

    Presenter().PresentSurface(s, request->m_pSrcRect, request->m_pDestRect,
                               1.0f, requestUsesKey, requestKey, false);
    Presenter().FlushBatch();

    avp2::render::GLStateCache::Instance().Restore(savedGL);
    TwoD().SetBlend(oldBlend);
    TwoD().SetColor(oldColor);
}

bool RendererPresenter::PresentWarp(GLSurface *s, const BlitRequest *request)
{
    PState().screenShadowValid = false;

    if (!s || !request || request->m_nWarpPts != 4 || !request->m_pWarpPts)
        return false;

    Presenter().FlushBatch();

    Renderer2D::Instance().EnsureTexture(s);

    RendererPresenterVertex verts[6];
    auto makeVertex = [&](int i) -> RendererPresenterVertex
    {
        const auto &p = request->m_pWarpPts[i];
        return {
            ToNdcX(p.m_fDestX),
            ToNdcY(p.m_fDestY),
            p.m_fSourceX / static_cast<float>(s->width),
            p.m_fSourceY / static_cast<float>(s->height)};
    };

    // Preserve caller order: 0-1-2, 0-2-3.
    verts[0] = makeVertex(0);
    verts[1] = makeVertex(1);
    verts[2] = makeVertex(2);
    verts[3] = makeVertex(0);
    verts[4] = makeVertex(2);
    verts[5] = makeVertex(3);

    GLTrackedNamedBufferSubData(Core().ScreenQuadVbo(), 0, sizeof(verts), verts, GLUploadCategory::Renderer);
    ApplyBlend(CurrentBlend());

    const float cr = ((CurrentColor() >> 16) & 0xFF) / 255.0f;
    const float cg = ((CurrentColor() >> 8) & 0xFF) / 255.0f;
    const float cb = (CurrentColor() & 0xFF) / 255.0f;
    const float ca = ((CurrentColor() >> 24) & 0xFF) / 255.0f;

    const uint32 keyColor = request->m_dwTransparentColor.dwVal;
    const bool useColorKey = (request->m_dwBlitOptions & BLIT_TRANSPARENT) != 0;
    const float kr = ((keyColor >> 16) & 0xFF) / 255.0f;
    const float kg = ((keyColor >> 8) & 0xFF) / 255.0f;
    const float kb = (keyColor & 0xFF) / 255.0f;

    TwoD().BlitShader()->Use();
    GLUniform1i(TwoD().BlitTexUniform(), 0);
    GLUniform4f(TwoD().BlitColorUniform(), cr, cg, cb, ca);
    GLUniform1f(TwoD().BlitAlphaUniform(), std::clamp(request->m_fAlpha, 0.0f, 1.0f));
    GLUniform1i(TwoD().BlitUseKeyUniform(), useColorKey ? 1 : 0);
    GLUniform3f(TwoD().BlitKeyUniform(), kr, kg, kb);
    GLUniform1i(TwoD().BlitUseTexAlphaUniform(), 0);

    GLStateBindTextureUnit(0, s->texture);
    GLStateBindVertexArray(Core().ScreenQuadVao());
    glf.DrawArrays(GL_TRIANGLES_, 0, 6);
    ++PState().frameDrawCalls;
    PState().frameHasPresentableContent = true;
    Presenter().InvalidateScreenRect(nullptr);
    return true;
}

bool RendererPresenter::WarpToScreen(BlitRequest *request)
{
    if (!request || !request->m_hBuffer || request->m_nWarpPts != 4 || !request->m_pWarpPts)
        return false;

    auto *s = reinterpret_cast<GLSurface *>(request->m_hBuffer);
    return Presenter().PresentWarp(s, request);
}

void RendererPresenter::BlitFromScreen(BlitRequest *request)
{
    Presenter().FlushBatch();
    if (!request || !request->m_hBuffer)
        return;

    auto *s = reinterpret_cast<GLSurface *>(request->m_hBuffer);

    // Milestone 1 supports full-surface readback. glReadPixels is bottom-up,
    // so flip rows into Talon's top-down CPU surface.
    std::vector<uint8_t> temp(static_cast<size_t>(s->width) * s->height * 4);
    glReadPixels(0, 0, s->width, s->height, GL_BGRA_, GL_UNSIGNED_BYTE, temp.data());

    for (int y = 0; y < s->height; ++y)
    {
        const uint8_t *src = temp.data() + static_cast<size_t>(s->height - 1 - y) * s->pitch;
        uint8_t *dst = s->pixels.data() + static_cast<size_t>(y) * s->pitch;
        std::memcpy(dst, src, s->pitch);
    }

    s->dirty = true;
    LOG_SESSION("BlitFromScreen -> surface=%p", s);
}

static void DiscardLogicalColorAfterPresent()
{
    if (!PState().emulateDiscardSwap || !FB().Ready())
        return;

    // D3DSWAPEFFECT_DISCARD explicitly makes the presented backbuffer contents
    // undefined.  A persistent FBO has the opposite semantics.  Clear it to a
    // deterministic black replacement *without* registering an engine dirty
    // rectangle; this is the new discarded backbuffer, not an application draw.
    FB().BindLogical();

    GLboolean oldColorMask[4] = {GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE};
    const auto savedGL = avp2::render::GLStateCache::Instance().Capture();
    GLint oldScissorBox[4] = {0, 0, Core().Width(), Core().Height()};
    glGetBooleanv(GL_COLOR_WRITEMASK, oldColorMask);
    glGetIntegerv(GL_SCISSOR_BOX, oldScissorBox);

    GLStateDisable(GL_SCISSOR_TEST);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColorMask(oldColorMask[0], oldColorMask[1], oldColorMask[2], oldColorMask[3]);
    glScissor(oldScissorBox[0], oldScissorBox[1], oldScissorBox[2], oldScissorBox[3]);
    avp2::render::GLStateCache::Instance().SetEnabled(GL_SCISSOR_TEST, savedGL.scissor);

    PState().screenShadowValid = false;
    ++PState().discardColorResets;
}

void RendererPresenter::SwapBuffers(uint32 flags)
{
    Presenter().FlushBatch();
    Core().DrawPerfOverlay();
    GUIQuality::Instance().DrawTuningMenu();

    constexpr uint32_t FLIPSCREEN_DIRTY_COMPAT = (1u << 2);
    const bool dirtyFlip = (flags & FLIPSCREEN_DIRTY_COMPAT) != 0;

    // Stock d3d_SwapBuffers chooses DirtyRectSwap for FLIPSCREEN_DIRTY and a
    // normal Present otherwise, then clears the invalid-rectangle list.  In
    // fullscreen stock D3D the presented backbuffer is DISCARD, not persistent.
    // We present our logical FBO first, then explicitly discard its color image
    // so the next additive/object-list frame cannot inherit the previous one.
    // IMPORTANT: FLIPSCREEN_DIRTY is invalidation-driven in stock d3d.ren.
    // DirtyRectSwap() does NOT inspect whether the renderer thinks useful draw
    // content was produced. If Clear/UnlockScreen/Blit invalidated any region,
    // Present is issued for that region. In particular, d3d_Clear(NULL/whole
    // screen) invalidates the full screen and FlipScreen(0x04) must present it.
    //
    // Keep the old clear-only HOLD protection only for ordinary/non-dirty flips.
    // Applying it to FLIPSCREEN_DIRTY was a direct D3D semantic mismatch and
    // suppressed the loading screen's full-screen invalidated frames.
    const bool shouldPresent = dirtyFlip ? PState().dirtyAny : PState().frameHasPresentableContent;

    if (Core().DeviceContext() && FB().Ready() && shouldPresent)
    {
        FB().Bind(GL_READ_FRAMEBUFFER, FB().Logical());
        FB().Bind(GL_DRAW_FRAMEBUFFER, 0);
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glDrawBuffer(GL_BACK);
        int presentW = Core().Width(), presentH = Core().Height();
        GetPresentClientSize(presentW, presentH);

        // Borderless fullscreen/window resizing preserves the game's logical
        // aspect ratio. Clear the physical backbuffer first so unused regions
        // are black, then scale the logical image into the largest centered
        // destination rectangle that fits the current client area.
        const bool presentScissorWasEnabled = avp2::render::GLStateCache::Instance().Capture().scissor;
        GLboolean presentColorMask[4] = {GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE};
        GLfloat presentClearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        glGetBooleanv(GL_COLOR_WRITEMASK, presentColorMask);
        glGetFloatv(GL_COLOR_CLEAR_VALUE, presentClearColor);

        GLStateDisable(GL_SCISSOR_TEST);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        RECT presentClientRc{};
        ComputePresentClientRect(presentW, presentH, presentClientRc);
        const int dstX0 = presentClientRc.left;
        const int dstX1 = presentClientRc.right;
        // Convert the Win32 top-left-origin rectangle back to GL bottom-left origin.
        const int dstY0 = presentH - presentClientRc.bottom;
        const int dstY1 = presentH - presentClientRc.top;

        FB().Blit(
            0, 0, Core().Width(), Core().Height(),
            dstX0, dstY0, dstX1, dstY1,
            GL_COLOR_BUFFER_BIT, GL_LINEAR);
        const BOOL swapped = ::SwapBuffers(Core().DeviceContext());
        FB().BindLogical();

        glColorMask(presentColorMask[0], presentColorMask[1], presentColorMask[2], presentColorMask[3]);
        glClearColor(presentClearColor[0], presentClearColor[1], presentClearColor[2], presentClearColor[3]);
        if (presentScissorWasEnabled)
            GLStateEnable(GL_SCISSOR_TEST);
        else
            GLStateDisable(GL_SCISSOR_TEST);

        if (swapped)
            DiscardLogicalColorAfterPresent();
        else
            LOG_SESSION("SwapBuffers WGL FAILED err=%lu", static_cast<unsigned long>(GetLastError()));

        static uint32_t s_presentDetailBudget = 160;
        if (LogIsSessionEnabled() && (s_presentDetailBudget))
        {
            --s_presentDetailBudget;
            LOG_SESSION("SwapBuffers PRESENT flags=%08X mode=%s dirtyAny=%d dirtyFull=%d dirtyRects=%u postPresent=%s logical=%dx%d client=%dx%d dst=(%d,%d)-(%d,%d)",
                        flags, dirtyFlip ? "DIRTY" : "FULL",
                        PState().dirtyAny ? 1 : 0, PState().dirtyFull ? 1 : 0, PState().dirtyRectCount,
                        PState().emulateDiscardSwap ? "DISCARD" : "COPY",
                        Core().Width(), Core().Height(), presentW, presentH, dstX0, dstY0, dstX1, dstY1);
        }
    }
    else if (Core().DeviceContext() && FB().Ready())
    {
        if (dirtyFlip)
        {
            // Exact dirty-rect semantics: no invalid rectangles means
            // DirtyRectSwap() returns without presenting. This is a no-op, not
            // the clear-only transition HOLD heuristic.
            static uint32_t s_dirtyNoopBudget = 32;
            if (LogIsSessionEnabled() && (s_dirtyNoopBudget))
            {
                --s_dirtyNoopBudget;
                LOG_SESSION("SwapBuffers DIRTY-NOOP flags=%08X dirtyAny=0 dirtyFull=0 dirtyRects=0", flags);
            }
        }
        else
        {
            ++PState().skippedEmptyPresents;
            static uint32_t emptyBudget = 64;
            if (LogIsSessionEnabled() && (emptyBudget))
            {
                --emptyBudget;
                LOG_SESSION("SwapBuffers HOLD flags=%08X content=%d dirtyAny=%d dirtyFull=%d dirtyRects=%u skipped=%llu",
                            flags, PState().frameHasPresentableContent ? 1 : 0,
                            PState().dirtyAny ? 1 : 0, PState().dirtyFull ? 1 : 0, PState().dirtyRectCount,
                            static_cast<unsigned long long>(PState().skippedEmptyPresents));
            }
        }
    }

    // Stock ClearDirtyRects() is called after every SwapBuffers invocation,
    // including a dirty flip with no invalid rectangles.
    Presenter().ClearInvalidScreenRects();
    PState().frameHasPresentableContent = false;

    const ULONGLONG now = GetTickCount64();
    if (PState().lastPerfLog == 0 || now - PState().lastPerfLog >= 1000)
    {
        LOG_SESSION("PERF[1s] blits=%llu optBlits=%llu directBlits=%llu drawCalls=%llu textureUploads=%llu lockShadowReuse=%llu lockReadback=%llu emptyPresentHolds=%llu discardResets=%llu clearScreen=%llu clearRenderOnly=%llu clearBoth=%llu glCtxBind=%llu glCtxCallerSwitch=%llu logicalFBO=%d swapModel=%s",
                    static_cast<unsigned long long>(PState().frameBlits),
                    static_cast<unsigned long long>(PState().frameOptimizedBlits),
                    static_cast<unsigned long long>(PState().frameDirectBlits),
                    static_cast<unsigned long long>(PState().frameDrawCalls),
                    static_cast<unsigned long long>(PState().frameTextureUploads),
                    static_cast<unsigned long long>(PState().screenShadowReuseCount),
                    static_cast<unsigned long long>(PState().screenShadowReadbackCount),
                    static_cast<unsigned long long>(PState().skippedEmptyPresents),
                    static_cast<unsigned long long>(PState().discardColorResets),
                    static_cast<unsigned long long>(PState().clearScreenCount),
                    static_cast<unsigned long long>(PState().clearRenderOnlyCount),
                    static_cast<unsigned long long>(PState().clearScreenRenderCount),
                    static_cast<unsigned long long>(Core().GLContextBindCount()),
                    static_cast<unsigned long long>(Core().GLContextThreadChangeCount()),
                    FB().Ready() ? 1 : 0,
                    PState().emulateDiscardSwap ? "DISCARD" : "COPY");
        PState().frameBlits = 0;
        PState().frameOptimizedBlits = 0;
        PState().frameDirectBlits = 0;
        PState().frameDrawCalls = 0;
        PState().frameTextureUploads = 0;
        PState().screenShadowReuseCount = 0;
        PState().screenShadowReadbackCount = 0;
        PState().skippedEmptyPresents = 0;
        PState().discardColorResets = 0;
        PState().clearScreenCount = 0;
        PState().clearRenderOnlyCount = 0;
        PState().clearScreenRenderCount = 0;
        PState().lastPerfLog = now;
    }
}
