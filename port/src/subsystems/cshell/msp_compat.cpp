#include "msp_compat.h"
#include "cshell_build.h"

#include "../memory/hook_manager.h"
#include "../memory/memory_utils.h"
#include "../renderer/Console.h"
#include "utils/log.h"

#include <windows.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cstdarg>
#include <cstdio>

namespace
{
    // Matching LithTech.exe supplied with AVP2/MSP.
    constexpr uintptr_t kEngineTimerCallRva = 0x033186u;
    constexpr uintptr_t kEngineStockTimerRva = 0x09C130u;
    constexpr uintptr_t kEngineFontQualityByteRva = 0x09B5B5u;

    // MSP also writes lithtech+0xE370C and installs several debug/network/message
    // hooks.  Those are intentionally NOT reproduced here yet: their full
    // behavior is unrelated to renderer compatibility or has not been mapped
    // sufficiently to duplicate safely without MSP CSHELL being present.

    bool g_installed = false;
    bool g_timerInstalled = false;
    bool g_fontPatchInstalled = false;

    LARGE_INTEGER g_qpcFrequency{};
    LARGE_INTEGER g_qpcLast{};
    double g_qpcAccumulatedSeconds = 0.0;
    bool g_qpcReady = false;

    void CompatLog(const char *fmt, ...)
    {
        char message[2048]{};
        va_list args;
        va_start(args, fmt);
        _vsnprintf_s(message, sizeof(message), _TRUNCATE, fmt, args);
        va_end(args);

        char debugLine[2140]{};
        _snprintf_s(debugLine, sizeof(debugLine), _TRUNCATE, "AVP2 OpenGL: %s\n", message);
        OutputDebugStringA(debugLine);
        if (LogIsSessionEnabled())
            Log("%s", message);
    }

    bool IsLithTechProcess()
    {
        char path[MAX_PATH]{};
        const DWORD n = GetModuleFileNameA(nullptr, path, MAX_PATH);
        if (!n || n >= MAX_PATH)
            return false;
        const char *base = wp_strrchr_sep(path);
        base = base ? base + 1 : path;
        return _stricmp(base, "lithtech.exe") == 0;
    }

    bool ValidateExeImage(HMODULE exe)
    {
        if (!exe)
            return false;
        auto *base = reinterpret_cast<unsigned char *>(exe);
        const auto *dos = reinterpret_cast<const IMAGE_DOS_HEADER *>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew <= 0)
            return false;
        const auto *nt = reinterpret_cast<const IMAGE_NT_HEADERS *>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return false;
        return nt->OptionalHeader.SizeOfImage > 0x0E370Du;
    }

    float __cdecl MSPCompatHighResolutionTime()
    {
        LARGE_INTEGER now{};
        if (!g_qpcReady)
        {
            if (!QueryPerformanceFrequency(&g_qpcFrequency) || g_qpcFrequency.QuadPart <= 0 ||
                !QueryPerformanceCounter(&g_qpcLast))
                return 0.0f;
            g_qpcAccumulatedSeconds = 0.0;
            g_qpcReady = true;
            return 0.0f;
        }

        if (!QueryPerformanceCounter(&now))
            return static_cast<float>(g_qpcAccumulatedSeconds);

        LONGLONG ticks = now.QuadPart - g_qpcLast.QuadPart;
        g_qpcLast = now;
        if (ticks < 0)
            ticks = 0;

        double dt = static_cast<double>(ticks) / static_cast<double>(g_qpcFrequency.QuadPart);
        // QPC should be monotonic, but don't allow a debugger/suspend hiccup to
        // poison the accumulated engine time with an absurd single step.
        if (!std::isfinite(dt) || dt < 0.0)
            dt = 0.0;
        g_qpcAccumulatedSeconds += dt;
        return static_cast<float>(g_qpcAccumulatedSeconds);
    }

    bool InstallEngineTimer(HMODULE exe)
    {
        const uintptr_t base = reinterpret_cast<uintptr_t>(exe);
        const uintptr_t site = base + kEngineTimerCallRva;
        const uintptr_t stockTarget = base + kEngineStockTimerRva;

        if (HookManager::IsInstalled("mspcompat.engine_qpc_timer"))
            return true;

        // Exact supplied LithTech build contains:
        //   00433186 E8 A5 8F 06 00    call 0049C130
        // Refuse to touch any other executable revision.
        const unsigned char expected[5] = {0xE8, 0xA5, 0x8F, 0x06, 0x00};
        unsigned char current[5]{};
        if (!MemoryUtils::ReadBytes(reinterpret_cast<const void *>(site), current, sizeof(current)) ||
            std::memcmp(current, expected, sizeof(expected)) != 0)
        {
            CompatLog("MSP compat: QPC timer patch skipped: lithtech+0x%X signature mismatch", static_cast<unsigned>(kEngineTimerCallRva));
            return false;
        }

        g_qpcReady = false;
        g_qpcAccumulatedSeconds = 0.0;
        if (!HookManager::InstallCall("mspcompat.engine_qpc_timer", site, stockTarget,
                                      reinterpret_cast<uintptr_t>(&MSPCompatHighResolutionTime)))
        {
            CompatLog("MSP compat: failed to install engine QPC timer replacement");
            return false;
        }

        CompatLog("MSP compat: installed MSP-equivalent QPC engine timer at lithtech+0x%X", static_cast<unsigned>(kEngineTimerCallRva));
        return true;
    }

    bool InstallFontQualityPatch(HMODULE exe)
    {
        if (HookManager::IsInstalled("mspcompat.font_quality"))
            return true;

        const uintptr_t address = reinterpret_cast<uintptr_t>(exe) + kEngineFontQualityByteRva;
        unsigned char original = 0xFF;
        if (!MemoryUtils::ReadBytes(reinterpret_cast<const void *>(address), &original, 1) || original != 0x00)
        {
            CompatLog("MSP compat: font-quality patch skipped: lithtech+0x%X byte=%02X expected=00",
                        static_cast<unsigned>(kEngineFontQualityByteRva), static_cast<unsigned>(original));
            return false;
        }

        const unsigned char nonAntialiasedQuality = 0x03;
        if (!HookManager::InstallBytes("mspcompat.font_quality", address, &nonAntialiasedQuality, 1))
            return false;

        CompatLog("MSP compat: installed MSP font-quality patch at lithtech+0x%X (DEFAULT_QUALITY -> NONANTIALIASED_QUALITY)",
                    static_cast<unsigned>(kEngineFontQualityByteRva));
        return true;
    }

    bool EnsureBorderlessCvar()
    {
        auto &console = Console::Instance();
        if (console.GetParameter("Borderless"))
            return true;

        // Talon's console creates unknown variables on assignment.  MSP adds
        // and consumes this same cvar.  Default remains off so original AVP2
        // behavior is unchanged unless the user/config enables it.
        console.Run("Borderless 0");
        return console.GetParameter("Borderless") != nullptr;
    }

    void ApplyWindowPolicy(HWND hwnd, bool windowed, int clientWidth, int clientHeight)
    {
        if (!hwnd || !IsWindow(hwnd) || !windowed)
            return;

        EnsureBorderlessCvar();
        const bool borderless = Console::Instance().GetBool("Borderless", false);
        if (!borderless)
            return;

        LONG style = GetWindowLongA(hwnd, GWL_STYLE);
        LONG exStyle = GetWindowLongA(hwnd, GWL_EXSTYLE);

        // MSP masks the existing style with 0xDE33FFFF.  Express the intent
        // explicitly: remove title/caption sizing chrome and system controls,
        // while preserving the rest of Talon's style bits.
        constexpr LONG kMspStyleMask = static_cast<LONG>(0xDE33FFFFu);
        const LONG newStyle = style & kMspStyleMask;
        if (newStyle != style)
            SetWindowLongA(hwnd, GWL_STYLE, newStyle);

        RECT target{};
        HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
        MONITORINFO mi{};
        mi.cbSize = sizeof(mi);
        if (monitor && GetMonitorInfoA(monitor, &mi))
            target = mi.rcMonitor;
        else
        {
            target.left = 0;
            target.top = 0;
            target.right = GetSystemMetrics(SM_CXSCREEN);
            target.bottom = GetSystemMetrics(SM_CYSCREEN);
        }

        // MSP centers the selected client size rather than unconditionally
        // stretching a windowed render mode to desktop dimensions.
        const int width = std::max(1, clientWidth);
        const int height = std::max(1, clientHeight);
        const int monitorW = target.right - target.left;
        const int monitorH = target.bottom - target.top;
        const int x = target.left + std::max(0, (monitorW - width) / 2);
        const int y = target.top + std::max(0, (monitorH - height) / 2);

        SetWindowPos(hwnd, HWND_TOP, x, y, width, height,
                     SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOACTIVATE);

        (void)exStyle;
        CompatLog("MSP compat: Borderless=1 applied hwnd=%p client=%dx%d pos=%d,%d style=%08X->%08X",
                    hwnd, width, height, x, y,
                    static_cast<unsigned>(style), static_cast<unsigned>(newStyle));
    }
}

namespace MSPCompatibility
{
    void PrepareRenderMode(uint32_t &bitDepth)
    {
        if (!CShell::Detect() || CShell::CurrentBuild() != CShell::Build::AVP2Original)
            return;

        const uint32_t incomingBitDepth = bitDepth;

        // Exact MSP OnEngineInitialized delta immediately before SetRenderMode:
        //   mov [pMode+0x20C], 0x20
        //   WriteConsoleInt("32BitTextures", 1)  -> "+32BitTextures 1"
        // Original AVP2 does neither here. Do it before RendererCore/texture
        // initialization so Talon and opengl.ren see the MSP policy from the
        // first renderer callback onward.
        bitDepth = 32u;
        Console::Instance().Run("+32BitTextures 1");

        CompatLog("MSP compat: pre-render mode policy bitDepth=%u->32 32BitTextures=%.0f",
                  static_cast<unsigned>(incomingBitDepth),
                  static_cast<double>(Console::Instance().GetFloat("32BitTextures", -1.0f)));
    }

    bool Install(HWND hwnd, bool windowed, int clientWidth, int clientHeight)
    {
        if (!CShell::Detect() || CShell::CurrentBuild() != CShell::Build::AVP2Original)
        {
            // MSP already contains these fixes; Coop will get its own profile
            // once its behavior is mapped.
            return false;
        }

        if (!IsLithTechProcess())
            return false;

        HMODULE exe = GetModuleHandleA(nullptr);
        if (!ValidateExeImage(exe))
        {
            CompatLog("MSP compat: unsupported/invalid lithtech.exe image; no engine patches installed");
            return false;
        }

        g_timerInstalled = InstallEngineTimer(exe);
        g_fontPatchInstalled = InstallFontQualityPatch(exe);
        ApplyWindowPolicy(hwnd, windowed, clientWidth, clientHeight);

        g_installed = g_timerInstalled || g_fontPatchInstalled;
        CompatLog("MSP compat: original AVP2 compatibility layer active timer=%d font=%d borderless=%d",
                    g_timerInstalled ? 1 : 0,
                    g_fontPatchInstalled ? 1 : 0,
                    (windowed && Console::Instance().GetBool("Borderless", false)) ? 1 : 0);
        return g_installed;
    }

    void RefreshWindow(HWND hwnd, bool windowed, int clientWidth, int clientHeight)
    {
        if (CShell::CurrentBuild() != CShell::Build::AVP2Original)
            return;
        ApplyWindowPolicy(hwnd, windowed, clientWidth, clientHeight);
    }

    void Remove()
    {
        HookManager::Uninstall("mspcompat.engine_qpc_timer");
        HookManager::Uninstall("mspcompat.font_quality");
        g_timerInstalled = false;
        g_fontPatchInstalled = false;
        g_installed = false;
        g_qpcReady = false;
        g_qpcAccumulatedSeconds = 0.0;
    }

    bool IsInstalled()
    {
        return g_installed;
    }
}
