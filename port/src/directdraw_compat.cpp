#include "subsystems/renderer/renderer_core.h"
#include "subsystems/renderer/renderer_2d.h"
#include "subsystems/renderer/renderer_presenter.h"
#include "directdraw_compat.h"
#include "utils/log.h"
#include <algorithm>
#include <cstring>

static HRESULT NotImpl(const char *fn)
{
    LOG_SESSION("DirectDraw unimplemented call: %s", fn);
    return E_NOTIMPL;
}

class DD7Base : public IDirectDraw7
{
public:
    ULONG refs = 1;

    HRESULT __stdcall QueryInterface(REFIID, LPVOID *) noexcept override { return E_NOINTERFACE; }
    ULONG __stdcall AddRef() noexcept override { return ++refs; }
    ULONG __stdcall Release() noexcept override
    {
        if (refs > 1)
            --refs;
        return refs;
    }

    HRESULT __stdcall Compact() noexcept override { return NotImpl("IDirectDraw7::Compact"); }
    HRESULT __stdcall CreateClipper(DWORD, LPDIRECTDRAWCLIPPER *, IUnknown *) noexcept override { return NotImpl("CreateClipper"); }
    HRESULT __stdcall CreatePalette(DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE *, IUnknown *) noexcept override { return NotImpl("CreatePalette"); }
    HRESULT __stdcall CreateSurface(LPDDSURFACEDESC2, LPDIRECTDRAWSURFACE7 *, IUnknown *) noexcept override;
    HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE7, LPDIRECTDRAWSURFACE7 *) noexcept override { return NotImpl("DuplicateSurface"); }
    HRESULT __stdcall EnumDisplayModes(DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMMODESCALLBACK2) noexcept override { return NotImpl("EnumDisplayModes"); }
    HRESULT __stdcall EnumSurfaces(DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMSURFACESCALLBACK7) noexcept override { return NotImpl("EnumSurfaces"); }
    HRESULT __stdcall FlipToGDISurface() noexcept override { return NotImpl("FlipToGDISurface"); }
    HRESULT __stdcall GetCaps(LPDDCAPS, LPDDCAPS) noexcept override { return NotImpl("GetCaps"); }
    HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC2) noexcept override;
    HRESULT __stdcall GetFourCCCodes(LPDWORD, LPDWORD) noexcept override { return NotImpl("GetFourCCCodes"); }
    HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE7 *) noexcept override { return NotImpl("GetGDISurface"); }
    HRESULT __stdcall GetMonitorFrequency(LPDWORD) noexcept override { return NotImpl("GetMonitorFrequency"); }
    HRESULT __stdcall GetScanLine(LPDWORD) noexcept override { return NotImpl("GetScanLine"); }
    HRESULT __stdcall GetVerticalBlankStatus(LPBOOL) noexcept override { return NotImpl("GetVerticalBlankStatus"); }
    HRESULT __stdcall Initialize(GUID *) noexcept override { return DD_OK; }
    HRESULT __stdcall RestoreDisplayMode() noexcept override { return DD_OK; }
    HRESULT __stdcall SetCooperativeLevel(HWND, DWORD) noexcept override { return DD_OK; }
    HRESULT __stdcall SetDisplayMode(DWORD, DWORD, DWORD, DWORD, DWORD) noexcept override { return DD_OK; }
    HRESULT __stdcall WaitForVerticalBlank(DWORD, HANDLE) noexcept override { return DD_OK; }
    HRESULT __stdcall GetAvailableVidMem(LPDDSCAPS2, LPDWORD total, LPDWORD freeMem) noexcept override
    {
        if (total)
            *total = 256u * 1024u * 1024u;
        if (freeMem)
            *freeMem = 256u * 1024u * 1024u;
        return DD_OK;
    }
    HRESULT __stdcall GetSurfaceFromDC(HDC, LPDIRECTDRAWSURFACE7 *) noexcept override { return NotImpl("GetSurfaceFromDC"); }
    HRESULT __stdcall RestoreAllSurfaces() noexcept override { return DD_OK; }
    HRESULT __stdcall TestCooperativeLevel() noexcept override { return DD_OK; }
    HRESULT __stdcall GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2, DWORD) noexcept override { return NotImpl("GetDeviceIdentifier"); }
    HRESULT __stdcall StartModeTest(LPSIZE, DWORD, DWORD) noexcept override { return NotImpl("StartModeTest"); }
    HRESULT __stdcall EvaluateMode(DWORD, DWORD *) noexcept override { return NotImpl("EvaluateMode"); }
};

class DDSurfaceBase : public IDirectDrawSurface7
{
public:
    ULONG refs = 1;

    HRESULT __stdcall QueryInterface(REFIID, LPVOID *) noexcept override { return E_NOINTERFACE; }
    ULONG __stdcall AddRef() noexcept override { return ++refs; }
    ULONG __stdcall Release() noexcept override
    {
        if (refs > 1)
            --refs;
        return refs;
    }

    HRESULT __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE7) noexcept override { return NotImpl("AddAttachedSurface"); }
    HRESULT __stdcall AddOverlayDirtyRect(LPRECT) noexcept override { return NotImpl("AddOverlayDirtyRect"); }
    HRESULT __stdcall Blt(LPRECT, LPDIRECTDRAWSURFACE7, LPRECT, DWORD, LPDDBLTFX) noexcept override { return NotImpl("DDSurface::Blt"); }
    HRESULT __stdcall BltBatch(LPDDBLTBATCH, DWORD, DWORD) noexcept override { return NotImpl("BltBatch"); }
    HRESULT __stdcall BltFast(DWORD, DWORD, LPDIRECTDRAWSURFACE7, LPRECT, DWORD) noexcept override { return NotImpl("BltFast"); }
    HRESULT __stdcall DeleteAttachedSurface(DWORD, LPDIRECTDRAWSURFACE7) noexcept override { return NotImpl("DeleteAttachedSurface"); }
    HRESULT __stdcall EnumAttachedSurfaces(LPVOID, LPDDENUMSURFACESCALLBACK7) noexcept override { return NotImpl("EnumAttachedSurfaces"); }
    HRESULT __stdcall EnumOverlayZOrders(DWORD, LPVOID, LPDDENUMSURFACESCALLBACK7) noexcept override { return NotImpl("EnumOverlayZOrders"); }
    HRESULT __stdcall Flip(LPDIRECTDRAWSURFACE7, DWORD) noexcept override { return NotImpl("Flip"); }
    HRESULT __stdcall GetAttachedSurface(LPDDSCAPS2, LPDIRECTDRAWSURFACE7 *) noexcept override { return NotImpl("GetAttachedSurface"); }
    HRESULT __stdcall GetBltStatus(DWORD) noexcept override { return DD_OK; }
    HRESULT __stdcall GetCaps(LPDDSCAPS2) noexcept override { return NotImpl("Surface::GetCaps"); }
    HRESULT __stdcall GetClipper(LPDIRECTDRAWCLIPPER *) noexcept override { return NotImpl("GetClipper"); }
    HRESULT __stdcall GetColorKey(DWORD, LPDDCOLORKEY) noexcept override { return NotImpl("GetColorKey"); }
    HRESULT __stdcall GetDC(HDC *) noexcept override { return NotImpl("GetDC"); }
    HRESULT __stdcall GetFlipStatus(DWORD) noexcept override { return DD_OK; }
    HRESULT __stdcall GetOverlayPosition(LPLONG, LPLONG) noexcept override { return NotImpl("GetOverlayPosition"); }
    HRESULT __stdcall GetPalette(LPDIRECTDRAWPALETTE *) noexcept override { return NotImpl("GetPalette"); }
    HRESULT __stdcall GetPixelFormat(LPDDPIXELFORMAT) noexcept override { return NotImpl("GetPixelFormat"); }
    HRESULT __stdcall GetSurfaceDesc(LPDDSURFACEDESC2) noexcept override { return NotImpl("GetSurfaceDesc"); }
    HRESULT __stdcall Initialize(LPDIRECTDRAW, LPDDSURFACEDESC2) noexcept override { return DD_OK; }
    HRESULT __stdcall IsLost() noexcept override { return DD_OK; }
    HRESULT __stdcall Lock(LPRECT, LPDDSURFACEDESC2, DWORD, HANDLE) noexcept override { return NotImpl("Surface::Lock"); }
    HRESULT __stdcall ReleaseDC(HDC) noexcept override { return NotImpl("ReleaseDC"); }
    HRESULT __stdcall Restore() noexcept override { return DD_OK; }
    HRESULT __stdcall SetClipper(LPDIRECTDRAWCLIPPER) noexcept override { return DD_OK; }
    HRESULT __stdcall SetColorKey(DWORD, LPDDCOLORKEY) noexcept override { return DD_OK; }
    HRESULT __stdcall SetOverlayPosition(LONG, LONG) noexcept override { return DD_OK; }
    HRESULT __stdcall SetPalette(LPDIRECTDRAWPALETTE) noexcept override { return DD_OK; }
    HRESULT __stdcall Unlock(LPRECT) noexcept override { return NotImpl("Surface::Unlock"); }
    HRESULT __stdcall UpdateOverlay(LPRECT, LPDIRECTDRAWSURFACE7, LPRECT, DWORD, LPDDOVERLAYFX) noexcept override { return NotImpl("UpdateOverlay"); }
    HRESULT __stdcall UpdateOverlayDisplay(DWORD) noexcept override { return NotImpl("UpdateOverlayDisplay"); }
    HRESULT __stdcall UpdateOverlayZOrder(DWORD, LPDIRECTDRAWSURFACE7) noexcept override { return NotImpl("UpdateOverlayZOrder"); }
    HRESULT __stdcall GetDDInterface(LPVOID *) noexcept override { return NotImpl("GetDDInterface"); }
    HRESULT __stdcall PageLock(DWORD) noexcept override { return DD_OK; }
    HRESULT __stdcall PageUnlock(DWORD) noexcept override { return DD_OK; }
    HRESULT __stdcall SetSurfaceDesc(LPDDSURFACEDESC2, DWORD) noexcept override { return NotImpl("SetSurfaceDesc"); }
    HRESULT __stdcall SetPrivateData(REFGUID, LPVOID, DWORD, DWORD) noexcept override { return NotImpl("SetPrivateData"); }
    HRESULT __stdcall GetPrivateData(REFGUID, LPVOID, LPDWORD) noexcept override { return NotImpl("GetPrivateData"); }
    HRESULT __stdcall FreePrivateData(REFGUID) noexcept override { return NotImpl("FreePrivateData"); }
    HRESULT __stdcall GetUniquenessValue(LPDWORD) noexcept override { return NotImpl("GetUniquenessValue"); }
    HRESULT __stdcall ChangeUniquenessValue() noexcept override { return DD_OK; }
    HRESULT __stdcall SetPriority(DWORD) noexcept override { return DD_OK; }
    HRESULT __stdcall GetPriority(LPDWORD p) noexcept override
    {
        if (p)
            *p = 0;
        return DD_OK;
    }
    HRESULT __stdcall SetLOD(DWORD) noexcept override { return DD_OK; }
    HRESULT __stdcall GetLOD(LPDWORD p) noexcept override
    {
        if (p)
            *p = 0;
        return DD_OK;
    }
};

class BinkVideoSurface final : public DDSurfaceBase
{
public:
    explicit BinkVideoSurface(DWORD w, DWORD h)
        : surface(Renderer2D::Instance().CreateSurface(static_cast<int>(w), static_cast<int>(h))) {}

    ~BinkVideoSurface()
    {
        RendererContextScope glScope;
        if (glScope)
            Renderer2D::Instance().DeleteSurface(surface);
        else
        {
            // Renderer may already be terminated.  The GL context teardown has
            // reclaimed GPU objects in that case; still release the CPU object.
            LOG_SESSION("BinkVideoSurface destruction after GL context teardown; freeing CPU surface only");
            if (surface)
            {
                surface->texture = 0;
                surface->textureAllocated = false;
                delete surface;
            }
        }
    }

    ULONG __stdcall Release() noexcept override
    {
        if (--refs == 0)
        {
            delete this;
            return 0;
        }
        return refs;
    }

    HRESULT __stdcall Blt(LPRECT dest, LPDIRECTDRAWSURFACE7 src, LPRECT srcRect,
                          DWORD flags, LPDDBLTFX fx) noexcept override
    {
        (void)flags;
        if (dest || src || srcRect || !fx || !surface)
            return DDERR_INVALIDPARAMS;

        RendererContextScope glScope;
        if (!glScope)
            return DDERR_GENERIC;

        const uint32 fill = fx->dwFillColor;
        uint32 *p = reinterpret_cast<uint32 *>(surface->pixels.data());
        const size_t count = static_cast<size_t>(surface->width) * surface->height;
        std::fill(p, p + count, fill);
        surface->dirty = true;
        return DD_OK;
    }

    HRESULT __stdcall Lock(LPRECT rect, LPDDSURFACEDESC2 desc, DWORD, HANDLE) noexcept override
    {
        if (rect || !desc || !surface || surface->locked)
            return DDERR_INVALIDPARAMS;

        if (!RendererCore::Instance().AcquireThreadContext())
            return DDERR_CANTLOCKSURFACE;

        surface->locked = true;
        std::memset(desc, 0, sizeof(*desc));
        desc->dwSize = sizeof(*desc);
        desc->dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PITCH | DDSD_PIXELFORMAT;
        desc->dwWidth = surface->width;
        desc->dwHeight = surface->height;
        desc->lpSurface = surface->pixels.data();
        desc->lPitch = surface->pitch;
        desc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
        desc->ddpfPixelFormat.dwFlags = DDPF_RGB;
        desc->ddpfPixelFormat.dwRGBBitCount = 32;
        desc->ddpfPixelFormat.dwRBitMask = 0x00FF0000;
        desc->ddpfPixelFormat.dwGBitMask = 0x0000FF00;
        desc->ddpfPixelFormat.dwBBitMask = 0x000000FF;
        desc->ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_LOCALVIDMEM | DDSCAPS_VIDEOMEMORY;
        LOG_SESSION("Bink surface Lock %p %dx%d", surface, surface->width, surface->height);
        return DD_OK;
    }

    HRESULT __stdcall Unlock(LPRECT rect) noexcept override
    {
        if (rect || !surface || !surface->locked)
            return DDERR_INVALIDPARAMS;
        surface->locked = false;
        surface->dirty = true;
        LOG_SESSION("Bink surface Unlock %p", surface);
        RendererCore::Instance().ReleaseThreadContext();
        return DD_OK;
    }

    GLSurface *surface = nullptr;
};

class BackBufferSurface final : public DDSurfaceBase
{
public:
    bool mapped = false;

    HRESULT __stdcall Blt(LPRECT dest, LPDIRECTDRAWSURFACE7 src, LPRECT srcRect,
                          DWORD, LPDDBLTFX fx) noexcept override
    {
        RendererContextScope glScope;
        if (!glScope)
            return DDERR_GENERIC;

        if (!dest || !src || !srcRect || fx)
            return DDERR_INVALIDPARAMS;

        auto *movie = dynamic_cast<BinkVideoSurface *>(src);
        if (!movie || !movie->surface)
            return DDERR_INVALIDPARAMS;

        LTRect s{srcRect->left, srcRect->top, srcRect->right, srcRect->bottom};

        // Bink asks DirectDraw to stretch the decoded frame to a destination
        // rectangle.  On widescreen this distorts the movie because the stock
        // coordinates are normally 4:3.  Present against the actual renderer
        // backbuffer instead and use a centered contain fit so the decoded
        // movie aspect ratio is never changed.
        const int windowW = std::max(1, RendererCore::Instance().Width());
        const int windowH = std::max(1, RendererCore::Instance().Height());
        LTRect d{0, 0, windowW, windowH};

        const float srcW = static_cast<float>(std::max(1L, srcRect->right - srcRect->left));
        const float srcH = static_cast<float>(std::max(1L, srcRect->bottom - srcRect->top));
        const float srcAspect = srcW / srcH;
        const float windowAspect = static_cast<float>(windowW) / static_cast<float>(windowH);

        if (windowAspect > srcAspect)
        {
            const int targetW = std::max(1, static_cast<int>(static_cast<float>(windowH) * srcAspect + 0.5f));
            d.m_nLeft = (windowW - targetW) / 2;
            d.m_nRight = d.m_nLeft + targetW;
        }
        else if (windowAspect < srcAspect)
        {
            const int targetH = std::max(1, static_cast<int>(static_cast<float>(windowW) / srcAspect + 0.5f));
            d.m_nTop = (windowH - targetH) / 2;
            d.m_nBottom = d.m_nTop + targetH;
        }

        LOG_SESSION("BACKBUFFER::Blt movie %dx%d src=(%ld,%ld)-(%ld,%ld) requestedDst=(%ld,%ld)-(%ld,%ld) actualDst=(%d,%d)-(%d,%d)",
                    movie->surface->width, movie->surface->height,
                    srcRect->left, srcRect->top, srcRect->right, srcRect->bottom,
                    dest->left, dest->top, dest->right, dest->bottom,
                    d.m_nLeft, d.m_nTop, d.m_nRight, d.m_nBottom);

        RendererPresenter::Instance().PresentSurface(movie->surface, &s, &d, 1.0f, false, 0, false);
        return DD_OK;
    }

    HRESULT __stdcall Lock(LPRECT rect, LPDDSURFACEDESC2 desc, DWORD, HANDLE) noexcept override
    {
        if (rect || !desc)
            return DDERR_INVALIDPARAMS;

        // Keep renderer ownership for the lifetime of the mapped backbuffer,
        // matching the renderer ABI LockScreen/UnlockScreen pair.
        if (!RendererCore::Instance().AcquireThreadContext())
            return DDERR_CANTLOCKSURFACE;

        void *data = nullptr;
        int pitch = 0;
        if (!RendererPresenter::Instance().LockScreen(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), &data, &pitch))
        {
            RendererCore::Instance().ReleaseThreadContext();
            return DDERR_CANTLOCKSURFACE;
        }
        mapped = true;

        std::memset(desc, 0, sizeof(*desc));
        desc->dwSize = sizeof(*desc);
        desc->dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PITCH | DDSD_PIXELFORMAT;
        desc->dwWidth = RendererCore::Instance().Width();
        desc->dwHeight = RendererCore::Instance().Height();
        desc->lpSurface = data;
        desc->lPitch = pitch;
        desc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
        desc->ddpfPixelFormat.dwFlags = DDPF_RGB;
        desc->ddpfPixelFormat.dwRGBBitCount = 32;
        desc->ddpfPixelFormat.dwRBitMask = 0x00FF0000;
        desc->ddpfPixelFormat.dwGBitMask = 0x0000FF00;
        desc->ddpfPixelFormat.dwBBitMask = 0x000000FF;
        desc->ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;
        return DD_OK;
    }

    HRESULT __stdcall Unlock(LPRECT) noexcept override
    {
        if (!mapped)
            return DDERR_INVALIDPARAMS;

        RendererPresenter::Instance().UnlockScreen();
        mapped = false;
        RendererCore::Instance().ReleaseThreadContext();
        return DD_OK;
    }
};

HRESULT __stdcall DD7Base::CreateSurface(LPDDSURFACEDESC2 desc, LPDIRECTDRAWSURFACE7 *out, IUnknown *) noexcept
{
    LOG_SESSION("IDirectDraw7::CreateSurface desc=%p out=%p", desc, out);
    if (desc)
        LOG_SESSION("  flags=0x%08X caps=0x%08X width=%u height=%u", desc->dwFlags, desc->ddsCaps.dwCaps, desc->dwWidth, desc->dwHeight);

    if (!desc || !out || desc->dwWidth == 0 || desc->dwHeight == 0)
        return DDERR_INVALIDPARAMS;

    auto *s = new BinkVideoSurface(desc->dwWidth, desc->dwHeight);
    if (!s->surface)
    {
        delete s;
        return DDERR_OUTOFMEMORY;
    }

    *out = s;
    LOG_SESSION("IDirectDraw7::CreateSurface -> BinkVideoSurface %ux%u", desc->dwWidth, desc->dwHeight);
    return DD_OK;
}

HRESULT __stdcall DD7Base::GetDisplayMode(LPDDSURFACEDESC2 desc) noexcept
{
    if (!desc)
        return DDERR_INVALIDPARAMS;

    std::memset(desc, 0, sizeof(*desc));
    desc->dwSize = sizeof(*desc);
    desc->dwFlags = DDSD_REFRESHRATE | DDSD_PIXELFORMAT | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PITCH;
    desc->dwWidth = RendererCore::Instance().Width();
    desc->dwHeight = RendererCore::Instance().Height();
    desc->lPitch = RendererCore::Instance().Width() * 4;
    desc->dwRefreshRate = 60;
    desc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
    desc->ddpfPixelFormat.dwFlags = DDPF_RGB;
    desc->ddpfPixelFormat.dwRGBBitCount = 32;
    desc->ddpfPixelFormat.dwRBitMask = 0x00FF0000;
    desc->ddpfPixelFormat.dwGBitMask = 0x0000FF00;
    desc->ddpfPixelFormat.dwBBitMask = 0x000000FF;
    return DD_OK;
}

static DD7Base g_fakeDirectDraw;
static BackBufferSurface g_fakeBackBuffer;

DirectDrawCompat &DirectDrawCompat::Instance()
{
    static DirectDrawCompat instance;
    return instance;
}

void *DirectDrawCompat::GetInterface(const char *query)
{
    LOG_SESSION("GetDirectDrawInterface query=%s", query ? query : "<null>");
    if (!query)
        return nullptr;

    if (std::strcmp(query, "LPDIRECTDRAW") == 0)
        return &g_fakeDirectDraw;

    if (std::strcmp(query, "BACKBUFFER") == 0)
        return &g_fakeBackBuffer;

    return nullptr;
}
