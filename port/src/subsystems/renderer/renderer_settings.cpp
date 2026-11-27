#include "renderer_settings.h"

#include "renderer_core.h"
#include "gui_quality.h"
#include "../textures/texture_manager.h"
#include "../world/world_renderer.h"
#include "utils/log.h"

#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

namespace
{
    constexpr std::uint32_t kVSyncDisabled = 1u << 0;
    constexpr std::uint32_t kDebugOverlay = 1u << 1;
    constexpr std::uint32_t kMSAA4x = 1u << 2;
    constexpr std::uint32_t kSSAO = 1u << 3;
    constexpr std::uint32_t kSSR = 1u << 4;
    constexpr std::uint32_t kBloom = 1u << 5;
    constexpr std::uint32_t kDynamicExposure = 1u << 6;
    constexpr std::uint32_t kAnisotropic16x = 1u << 7;
    constexpr std::uint32_t kHighQualityLightGrid = 1u << 8;
    constexpr std::uint32_t kKnownMask = kVSyncDisabled | kDebugOverlay | kMSAA4x | kSSAO | kSSR | kBloom | kDynamicExposure | kAnisotropic16x | kHighQualityLightGrid;
    constexpr std::uint32_t kDefaultMask = kMSAA4x;
}

RendererSettings &RendererSettings::Instance()
{
    static RendererSettings s;
    return s;
}

bool RendererSettings::BuildSettingsPath(char *outPath, unsigned int outPathBytes) const
{
    if (!outPath || outPathBytes == 0)
        return false;

    char appData[MAX_PATH] = {};
    const DWORD appDataLen = GetEnvironmentVariableA("APPDATA", appData, static_cast<DWORD>(sizeof(appData)));
    if (appDataLen == 0 || appDataLen >= sizeof(appData))
        return false;

    char dir[MAX_PATH] = {};
    const int dirLen = std::snprintf(dir, sizeof(dir), "%s\\AVP2_OpenGL_Renderer", appData);
    if (dirLen <= 0 || static_cast<unsigned int>(dirLen) >= sizeof(dir))
        return false;

    if (!CreateDirectoryA(dir, nullptr))
    {
        const DWORD err = GetLastError();
        if (err != ERROR_ALREADY_EXISTS)
        {
            LOG_SESSION("Renderer settings: CreateDirectory failed path='%s' err=%lu", dir,
                        static_cast<unsigned long>(err));
            return false;
        }
    }

    const int fileLen = std::snprintf(outPath, outPathBytes, "%s\\settings.bin", dir);
    return fileLen > 0 && static_cast<unsigned int>(fileLen) < outPathBytes;
}

std::uint32_t RendererSettings::CaptureMask() const
{
    std::uint32_t mask = 0;
    if (!RendererCore::Instance().IsVSyncEnabled())
        mask |= kVSyncDisabled;
    if (RendererCore::Instance().IsPerfOverlayEnabled())
        mask |= kDebugOverlay;
    if (GUIQuality::Instance().IsMSAA4xEnabled())
        mask |= kMSAA4x;
    if (GUIQuality::Instance().IsSSAOEnabled())
        mask |= kSSAO;
    if (GUIQuality::Instance().IsSSREnabled())
        mask |= kSSR;
    if (GUIQuality::Instance().IsBloomEnabled())
        mask |= kBloom;
    if (GUIQuality::Instance().IsDynamicExposureEnabled())
        mask |= kDynamicExposure;
    if (TextureManager::Instance().IsAnisotropic16xEnabled())
        mask |= kAnisotropic16x;
    if (WorldRenderer::Instance().Lighting().IsHighQualityLightGridEnabled())
        mask |= kHighQualityLightGrid;
    return mask;
}

void RendererSettings::ApplyMask(std::uint32_t mask)
{
    mask &= kKnownMask;
    RendererCore::Instance().SetVSyncEnabled((mask & kVSyncDisabled) == 0);
    RendererCore::Instance().SetPerfOverlayEnabled((mask & kDebugOverlay) != 0);
    GUIQuality::Instance().SetMSAA4xEnabled((mask & kMSAA4x) != 0);
    GUIQuality::Instance().SetSSAOEnabled((mask & kSSAO) != 0);
    GUIQuality::Instance().SetSSREnabled((mask & kSSR) != 0);
    GUIQuality::Instance().SetBloomEnabled((mask & kBloom) != 0);
    GUIQuality::Instance().SetDynamicExposureEnabled((mask & kDynamicExposure) != 0);
    TextureManager::Instance().SetAnisotropic16xEnabled((mask & kAnisotropic16x) != 0);
    WorldRenderer::Instance().Lighting().SetHighQualityLightGridEnabled((mask & kHighQualityLightGrid) != 0);
}

void RendererSettings::LoadAndApply()
{
    if (m_initialized)
        return;

    char path[MAX_PATH] = {};
    if (!BuildSettingsPath(path, sizeof(path)))
    {
        LOG_SESSION("Renderer settings: APPDATA path unavailable; persistence disabled for this session");
        return;
    }

    std::uint32_t mask = 0;
    bool loaded = false;
    {
        std::ifstream f(path, std::ios::binary);
        if (f)
        {
            f.read(reinterpret_cast<char *>(&mask), static_cast<std::streamsize>(sizeof(mask)));
            loaded = f.gcount() == static_cast<std::streamsize>(sizeof(mask));
        }
    }

    m_applying = true;
    if (loaded)
    {
        mask &= kKnownMask;
        ApplyMask(mask);
        LOG_SESSION("Renderer settings loaded '%s' mask=0x%08lX", path,
                    static_cast<unsigned long>(mask));
    }
    else
    {
        mask = kDefaultMask;
        ApplyMask(mask);
        LOG_SESSION("Renderer settings: no valid 4-byte settings file; applying defaults mask=0x%08lX",
                    static_cast<unsigned long>(mask));
    }
    m_applying = false;
    m_initialized = true;

    if (!loaded)
        SaveCurrent();
}

void RendererSettings::SaveCurrent()
{
    if (!m_initialized || m_applying)
        return;

    char path[MAX_PATH] = {};
    if (!BuildSettingsPath(path, sizeof(path)))
        return;

    const std::uint32_t mask = CaptureMask() & kKnownMask;
    bool ok = false;
    {
        std::ofstream f(path, std::ios::binary | std::ios::trunc);
        if (!f)
        {
            LOG_SESSION("Renderer settings: failed to open '%s' for write", path);
            return;
        }

        f.write(reinterpret_cast<const char *>(&mask), static_cast<std::streamsize>(sizeof(mask)));
        ok = f.good();
    }
    if (ok)
        LOG_SESSION("Renderer settings saved mask=0x%08lX", static_cast<unsigned long>(mask));
    else
        LOG_SESSION("Renderer settings: failed writing '%s'", path);
}
