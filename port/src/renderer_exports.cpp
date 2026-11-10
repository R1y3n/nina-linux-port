#include "subsystems/scene/scene_renderer.h"
#include "subsystems/renderer/Console.h"
#include "subsystems/renderer/frame_constants.h"
#include "subsystems/renderer/gl_uniform_stats.h"
#include "subsystems/renderer/renderer_2d.h"
#include "subsystems/renderer/renderer_presenter.h"
#include "subsystems/renderer/gui_quality.h"
#include "subsystems/renderer/opengl_options_menu.h"
#include "subsystems/cshell/cshell_build.h"
#include "subsystems/cshell/msp_compat.h"
#include "subsystems/renderer/stock_render_options.h"
#include "subsystems/timing/high_refresh_timing.h"
#include "subsystems/memory/memory_utils.h"
#include "subsystems/memory/hook_manager.h"
#include "subsystems/world/world_renderer.h"
#include "subsystems/world/world_surface_fx.h"
#include "subsystems/world/world_material_system.h"
#include "lt_renderer_abi.h"
#include "gl_renderer.h"
#include "subsystems/renderer/renderer_core.h"
#include "subsystems/renderer/Framebuffer.h"
#include "subsystems/renderer/gl_state_cache.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "directdraw_compat.h"
#include "gl_loader.h"
#include "utils/log.h"
#include "subsystems/models/abc_model_renderer.h"
#include "subsystems/fx/fx_renderer.h"
#include "subsystems/textures/Texture.h"
#include "subsystems/textures/texture_manager.h"
#include "subsystems/renderer/fog_state.h"

#include <windows.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <tuple>
#include <vector>
#include <string>
#include <cstdint>

extern HMODULE g_hModule;
static RenderStruct *g_rs = nullptr;
static HWND g_rendererHwnd = nullptr;
static bool g_rendererWindowed = true;
static bool g_exclusiveDisplayActive = false;
static char g_exclusiveDisplayDevice[CCHDEVICENAME] = {};
static int g_exclusiveWidth = 0;
static int g_exclusiveHeight = 0;

// AVP2.exe's launcher filters renderer modes to exact 4:3.  Only patch that
// launcher process; never scan/modify lithtech.exe.
// This runs when AVP2.exe loads opengl.ren to query rdll_GetSupportedModes().
static bool g_avp2AspectFilterPatchAttempted = false;
static bool g_avp2AspectFilterPatched = false;
static char g_requestedDisplayDevice[CCHDEVICENAME] = {};

static bool IsDisplayDeviceName(const char *text)
{
    return text && _strnicmp(text, "\\\\.\\DISPLAY", 11) == 0;
}

static bool QueryCurrentDisplayRect(const char *deviceName, RECT &outRect)
{
    if (!deviceName || !deviceName[0])
        return false;

    DEVMODEA dm{};
    dm.dmSize = sizeof(dm);
    if (!EnumDisplaySettingsExA(deviceName, ENUM_CURRENT_SETTINGS, &dm, 0))
        return false;

    LONG left = 0;
    LONG top = 0;
    if ((dm.dmFields & DM_POSITION) != 0)
    {
        left = dm.dmPosition.x;
        top = dm.dmPosition.y;
    }

    outRect.left = left;
    outRect.top = top;
    outRect.right = left + static_cast<LONG>(dm.dmPelsWidth);
    outRect.bottom = top + static_cast<LONG>(dm.dmPelsHeight);
    return true;
}

static bool IsAVP2LauncherProcess()
{
    char path[MAX_PATH] = {};
    const DWORD len = GetModuleFileNameA(nullptr, path, static_cast<DWORD>(sizeof(path)));
    if (len == 0 || len >= sizeof(path))
        return false;

    const char *base = wp_strrchr_sep(path);
    base = base ? (base + 1) : path;
    return _stricmp(base, "AVP2.exe") == 0;
}

static bool PatchAVP2AspectRatioModeFilter()
{
    // Critical safety gate: the renderer is also loaded by lithtech.exe.
    // The 4:3 filter belongs to AVP2.exe's display-settings launcher only.
    if (!IsAVP2LauncherProcess())
        return false;

    if (g_avp2AspectFilterPatchAttempted)
        return g_avp2AspectFilterPatched;
    g_avp2AspectFilterPatchAttempted = true;

    HMODULE exe = GetModuleHandleA(nullptr);
    if (!exe)
        return false;

    auto *base = reinterpret_cast<unsigned char *>(exe);
    auto *dos = reinterpret_cast<IMAGE_DOS_HEADER *>(base);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        return false;
    auto *nt = reinterpret_cast<IMAGE_NT_HEADERS *>(base + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE)
        return false;

    // Runtime AVP2.exe sequence:
    //   lea edx,[eax*4]
    //   mov eax,0AAAAAAABh
    //   mul edx
    //   shr edx,1
    //   cmp edx,ecx
    //   jne reject
    // The final JNE is the exact-4:3 mode gate.
    static const unsigned char pattern[] = {
        0x8D, 0x14, 0x85, 0x00, 0x00, 0x00, 0x00,
        0xB8, 0xAB, 0xAA, 0xAA, 0xAA,
        0xF7, 0xE2,
        0xD1, 0xEA,
        0x3B, 0xD1,
        0x75, 0x34};
    constexpr size_t kBranchOffset = sizeof(pattern) - 2;

    auto findUnique = [&](const unsigned char *needle, size_t needleSize,
                          unsigned char *&matchOut) -> size_t
    {
        matchOut = nullptr;
        size_t matches = 0;
        auto *section = IMAGE_FIRST_SECTION(nt);
        for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
        {
            if ((section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0)
                continue;

            unsigned char *start = base + section->VirtualAddress;
            const size_t size = section->Misc.VirtualSize;
            if (size < needleSize)
                continue;

            for (size_t off = 0; off + needleSize <= size; ++off)
            {
                if (std::memcmp(start + off, needle, needleSize) == 0)
                {
                    matchOut = start + off;
                    ++matches;
                    if (matches > 1)
                        return matches;
                }
            }
        }
        return matches;
    };

    unsigned char *match = nullptr;
    size_t matches = findUnique(pattern, sizeof(pattern), match);

    if (matches != 1 || !match)
    {
        // Renderer reloads are normal in the launcher, so accept the exact
        // same signature with only the JNE already replaced by NOPs.
        unsigned char already[sizeof(pattern)];
        std::memcpy(already, pattern, sizeof(pattern));
        already[kBranchOffset] = 0x90;
        already[kBranchOffset + 1] = 0x90;

        match = nullptr;
        matches = findUnique(already, sizeof(already), match);
        if (matches == 1 && match)
        {
            g_avp2AspectFilterPatched = true;
            LOG_SESSION("AVP2.exe aspect-ratio mode filter already patched at %p", match + kBranchOffset);
            return true;
        }

        LOG_SESSION("AVP2.exe aspect-ratio mode filter patch skipped: signature matches=%zu", matches);
        return false;
    }

    unsigned char *branch = match + kBranchOffset;
    if (!HookManager::InstallNop("launcher.aspect_ratio_filter", reinterpret_cast<uintptr_t>(branch), 2))
    {
        LOG_SESSION("AVP2.exe aspect-ratio mode filter patch failed: reversible NOP install failed");
        return false;
    }

    g_avp2AspectFilterPatched = true;
    LOG_SESSION("AVP2.exe aspect-ratio mode filter disabled at %p (RVA=0x%08X)",
                branch, static_cast<unsigned int>(branch - base));
    return true;
}
// use comctl32 window subclassing instead of replacing GWLP_WNDPROC.
// SetWindowLongPtr cannot be safely unwound if Talon/another component
// subclasses the HWND after us; that can leave a callback into an unloaded
// opengl.ren across a renderer resolution-change reload.
using RendererSubclassProc = LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
using PFN_SetWindowSubclass = BOOL(WINAPI *)(HWND, RendererSubclassProc, UINT_PTR, DWORD_PTR);
using PFN_RemoveWindowSubclass = BOOL(WINAPI *)(HWND, RendererSubclassProc, UINT_PTR);
using PFN_DefSubclassProc = LRESULT(WINAPI *)(HWND, UINT, WPARAM, LPARAM);
static HMODULE g_comctl32Module = nullptr;
static PFN_SetWindowSubclass g_setWindowSubclass = nullptr;
static PFN_RemoveWindowSubclass g_removeWindowSubclass = nullptr;
static PFN_DefSubclassProc g_defSubclassProc = nullptr;
static bool g_rendererMouseSubclassInstalled = false;
static HWND g_rendererMouseSubclassHwnd = nullptr;

// Talon's main loop recenters the OS cursor every frame through its
// USER32!SetCursorPos import (lithtech.exe 0x00403260 in the supplied build).
// Hook only that IAT slot while this renderer is loaded so Insert can release
// the mouse for the renderer-owned ImGui panel without modifying the EXE.
using PFN_SetCursorPos = BOOL(WINAPI *)(int, int);
static PFN_SetCursorPos g_realSetCursorPos = nullptr;
static void **g_setCursorPosIATSlot = nullptr;

static BOOL WINAPI RendererSetCursorPosHook(int x, int y)
{
    if (GUIQuality::Instance().IsTuningMenuOpen())
        return TRUE;
    return g_realSetCursorPos ? g_realSetCursorPos(x, y) : ::SetCursorPos(x, y);
}

static bool InstallSetCursorPosHook()
{
    if (g_setCursorPosIATSlot)
        return true;

    void *original = nullptr;
    void **slot = nullptr;
    if (!HookManager::InstallIAT("renderer.iat.SetCursorPos", GetModuleHandleA(nullptr),
                                 "USER32.dll", "SetCursorPos", reinterpret_cast<void *>(&RendererSetCursorPosHook),
                                 &original, &slot))
    {
        LOG_SESSION("Renderer ImGui cursor hook: USER32!SetCursorPos import not found");
        return false;
    }

    g_realSetCursorPos = reinterpret_cast<PFN_SetCursorPos>(original);
    g_setCursorPosIATSlot = slot;
    LOG_SESSION("Renderer ImGui cursor hook installed IAT=%p original=%p", slot, original);
    return true;
}

static void RemoveSetCursorPosHook()
{
    HookManager::Uninstall("renderer.iat.SetCursorPos");
    g_setCursorPosIATSlot = nullptr;
    g_realSetCursorPos = nullptr;
}

// While the renderer tuning UI is open, AVP2 must not continue receiving
// relative DirectInput mouse deltas/buttons or keyboard state.  WndProc capture
// alone is insufficient because Talon uses legacy DINPUT.dll directly.
using PFN_GetAsyncKeyState = SHORT(WINAPI *)(int);
using PFN_GetKeyboardState = BOOL(WINAPI *)(PBYTE);
static PFN_GetAsyncKeyState g_realExeGetAsyncKeyState = nullptr;
static PFN_GetKeyboardState g_realExeGetKeyboardState = nullptr;
static void **g_getAsyncKeyStateIATSlot = nullptr;
static void **g_getKeyboardStateIATSlot = nullptr;

// Keep the click used to close the panel captured until its physical release.
// These are the renderer's USER32 imports, not the intercepted engine imports.
static bool g_waitForUiMouseRelease = false;
static bool CaptureGameplayInput()
{
    if (GUIQuality::Instance().IsTuningMenuOpen())
    {
        g_waitForUiMouseRelease = true;
        return true;
    }
    if (g_waitForUiMouseRelease)
    {
        for (int key : {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2})
            if ((::GetAsyncKeyState(key) & 0x8000) != 0)
                return true;
        g_waitForUiMouseRelease = false;
    }
    return false;
}

static SHORT WINAPI RendererGetAsyncKeyStateHook(int vk)
{
    if (CaptureGameplayInput())
        return 0;
    return g_realExeGetAsyncKeyState ? g_realExeGetAsyncKeyState(vk) : ::GetAsyncKeyState(vk);
}

static BOOL WINAPI RendererGetKeyboardStateHook(PBYTE state)
{
    if (CaptureGameplayInput())
    {
        if (state)
            std::memset(state, 0, 256);
        return TRUE;
    }
    return g_realExeGetKeyboardState ? g_realExeGetKeyboardState(state) : ::GetKeyboardState(state);
}

// Minimal legacy DirectInput ABI declarations. We patch the COM vtables rather
// than wrapping the interfaces, so no dxguid/dinput import library is required.
using PFN_DirectInputCreateA = HRESULT(WINAPI *)(HINSTANCE, DWORD, void **, void *);
using PFN_DICreateDevice = HRESULT(STDMETHODCALLTYPE *)(void *, REFGUID, void **, void *);
using PFN_DIGetDeviceState = HRESULT(STDMETHODCALLTYPE *)(void *, DWORD, LPVOID);
using PFN_DIGetDeviceData = HRESULT(STDMETHODCALLTYPE *)(void *, DWORD, LPVOID, LPDWORD, DWORD);
static PFN_DirectInputCreateA g_realDirectInputCreateA = nullptr;
static PFN_DICreateDevice g_realDICreateDevice = nullptr;
static void **g_directInputCreateIATSlot = nullptr;
static void **g_diCreateDeviceVtableSlot = nullptr;

struct DIDeviceHookRecord
{
    void **vtable = nullptr;
    PFN_DIGetDeviceState state = nullptr;
    PFN_DIGetDeviceData data = nullptr;
    std::string statePatchName;
    std::string dataPatchName;
};
static std::vector<DIDeviceHookRecord> g_diDeviceHooks;

struct DIInputCaptureState
{
    void *device = nullptr;
    DWORD objectCount = 0; // Talon's custom format uses DWORD-spaced objects.
    DWORD releaseCursor = 0;
    bool captured = false;
};
static std::vector<DIInputCaptureState> g_diInputCaptureStates;
static bool g_talonInputLayoutValid = false;
using PFN_TalonReadInput = void(__cdecl *)(void *, unsigned char *, float *);
static PFN_TalonReadInput g_realTalonReadInput = nullptr;

static void __cdecl RendererTalonReadInputHook(void *manager, unsigned char *commands, float *axes)
{
    const bool capture = CaptureGameplayInput();
    if (capture)
    {
        // Talon retains relative-axis samples for smoothing even when the DI
        // queue is empty. Feed a finite neutral batch on EACH engine input
        // update, not just on panel entry, to retire that history as well.
        for (auto &state : g_diInputCaptureStates)
            state.releaseCursor = 0;
    }
    if (g_realTalonReadInput)
        g_realTalonReadInput(manager, commands, axes);

    // 0x43F490 writes three floats through argument 3. These are the axis
    // offsets returned to the client shell (including mouse yaw/pitch), after
    // binding and smoothing. Capture here also covers retained old samples.
    if (capture && axes)
        std::fill_n(axes, 3, 0.0f);
}

static DIInputCaptureState &DIInputState(void *device)
{
    for (auto &state : g_diInputCaptureStates)
        if (state.device == device)
            return state;
    g_diInputCaptureStates.push_back({device});
    return g_diInputCaptureStates.back();
}

static DIDeviceHookRecord *FindDIHook(void *self)
{
    if (!self)
        return nullptr;

    void **vt = *reinterpret_cast<void ***>(self);
    for (auto &h : g_diDeviceHooks)
    {
        if (h.vtable == vt)
            return &h;
    }
    return nullptr;
}

static HRESULT STDMETHODCALLTYPE RendererDIGetDeviceStateHook(void *self, DWORD bytes, LPVOID data)
{
    auto *h = FindDIHook(self);
    const HRESULT hr = (h && h->state) ? h->state(self, bytes, data) : E_FAIL;
    // Still poll the real device so relative motion is consumed and acquisition
    // failures retain their normal semantics.
    if (CaptureGameplayInput() && SUCCEEDED(hr) && data && bytes)
        std::memset(data, 0, bytes);
    return hr;
}

static HRESULT STDMETHODCALLTYPE RendererDIGetDeviceDataHook(void *self, DWORD objectBytes, LPVOID data, LPDWORD count, DWORD flags)
{
    auto *h = FindDIHook(self);
    if (!h || !h->data)
        return E_FAIL;
    auto &state = DIInputState(self);
    const bool capture = CaptureGameplayInput();
    if (capture || state.captured)
    {
        if (!count)
            return E_POINTER;
        const DWORD capacity = *count;
        if (!state.captured)
            state.releaseCursor = 0;

        // Returning count=0 without reading leaves UI clicks queued for later.
        // Flush even for PEEK callers, including one final flush on returning
        // control to gameplay. Use the caller's legacy (16-byte) event size.
        DWORD discarded = INFINITE;
        const HRESULT hr = h->data(self, objectBytes, nullptr, &discarded, 0);
        *count = 0;
        // Keep the final flush pending across focus loss/reacquisition errors.
        state.captured = true;
        if (FAILED(hr))
            return hr;
        state.captured = capture;

        // Talon caches buffered button states. Supply one neutral event per
        // mapped object on capture entry so held fire/movement can release.
        // A finite batch is essential: Talon can poll until count becomes zero.
        if (capture && data && objectBytes >= 4 * sizeof(DWORD))
        {
            const DWORD available = state.objectCount - std::min(state.releaseCursor, state.objectCount);
            const DWORD emitted = std::min(capacity, available);
            for (DWORD i = 0; i < emitted; ++i)
            {
                auto *event = static_cast<unsigned char *>(data) + size_t(i) * objectBytes;
                std::memset(event, 0, objectBytes);
                const DWORD offset = (state.releaseCursor + i) * sizeof(DWORD);
                std::memcpy(event, &offset, sizeof(offset));
            }
            state.releaseCursor += emitted;
            *count = emitted;
        }
        return S_OK;
    }
    return h->data(self, objectBytes, data, count, flags);
}

static void PatchDirectInputDevice(void *dev)
{
    if (!dev)
        return;

    void **vt = *reinterpret_cast<void ***>(dev);
    if (!vt)
        return;

    for (auto &h : g_diDeviceHooks)
    {
        if (h.vtable == vt)
            return;
    }

    DIDeviceHookRecord rec{};
    rec.vtable = vt;
    rec.state = reinterpret_cast<PFN_DIGetDeviceState>(vt[9]);
    rec.data = reinterpret_cast<PFN_DIGetDeviceData>(vt[10]);

    char patchName[96]{};
    std::snprintf(patchName, sizeof(patchName), "renderer.dinput.device.%p.state", static_cast<void *>(vt));
    rec.statePatchName = patchName;
    std::snprintf(patchName, sizeof(patchName), "renderer.dinput.device.%p.data", static_cast<void *>(vt));
    rec.dataPatchName = patchName;

    void *originalState = nullptr;
    void *originalData = nullptr;
    if (!HookManager::InstallPointerRaw(rec.statePatchName.c_str(), &vt[9],
                                        reinterpret_cast<void *>(&RendererDIGetDeviceStateHook), &originalState) ||
        !HookManager::InstallPointerRaw(rec.dataPatchName.c_str(), &vt[10],
                                        reinterpret_cast<void *>(&RendererDIGetDeviceDataHook), &originalData))
    {
        HookManager::Uninstall(rec.dataPatchName.c_str());
        HookManager::Uninstall(rec.statePatchName.c_str());
        return;
    }
    rec.state = reinterpret_cast<PFN_DIGetDeviceState>(originalState);
    rec.data = reinterpret_cast<PFN_DIGetDeviceData>(originalData);
    g_diDeviceHooks.push_back(rec);
    LOG_SESSION("Renderer ImGui DirectInput device capture installed dev=%p vtable=%p", dev, vt);
}

static HRESULT STDMETHODCALLTYPE RendererDICreateDeviceHook(void *self, REFGUID guid, void **outDev, void *outer)
{
    HRESULT hr = g_realDICreateDevice ? g_realDICreateDevice(self, guid, outDev, outer) : E_FAIL;
    if (SUCCEEDED(hr) && outDev && *outDev)
        PatchDirectInputDevice(*outDev);
    return hr;
}

static void PatchDirectInputInterface(void *di)
{
    if (!di || g_diCreateDeviceVtableSlot)
        return;

    void **vt = *reinterpret_cast<void ***>(di);
    if (!vt)
        return;

    void *original = nullptr;
    if (!HookManager::InstallPointerRaw("renderer.dinput.CreateDevice", &vt[3],
                                        reinterpret_cast<void *>(&RendererDICreateDeviceHook), &original))
        return;

    g_realDICreateDevice = reinterpret_cast<PFN_DICreateDevice>(original);
    g_diCreateDeviceVtableSlot = &vt[3];
    LOG_SESSION("Renderer ImGui DirectInput CreateDevice hook installed interface=%p", di);
}

static HRESULT WINAPI RendererDirectInputCreateAHook(HINSTANCE inst, DWORD version, void **outDI, void *outer)
{
    HRESULT hr = g_realDirectInputCreateA ? g_realDirectInputCreateA(inst, version, outDI, outer) : E_FAIL;
    if (SUCCEEDED(hr) && outDI && *outDI)
        PatchDirectInputInterface(*outDI);
    return hr;
}

static bool ReadInputMemory(uintptr_t address, void *out, size_t bytes)
{
    SIZE_T read = 0;
    return ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<const void *>(address), out, bytes, &read) && read == bytes;
}

static bool ValidateTalonInputLayout()
{
    // Supplied lithtech.exe: DirectInput global +0xE3B18, device list +0xE3B1C.
    // Validate both the creation and list-link instructions before using RVAs.
    const uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
    unsigned char create[] = {0x68, 0, 0, 0, 0, 0x68, 0x00, 0x07, 0x00, 0x00};
    const uintptr_t diGlobal = base + 0xE3B18u;
    std::memcpy(create + 1, &diGlobal, 4);
    unsigned char link[] = {0x8B, 0x0D, 0, 0, 0, 0, 0x89, 0x8E, 0x00, 0x03, 0x00, 0x00,
                           0x89, 0x35, 0, 0, 0, 0};
    const uintptr_t listGlobal = base + 0xE3B1Cu;
    std::memcpy(link + 2, &listGlobal, 4);
    std::memcpy(link + 14, &listGlobal, 4);
    unsigned char actualCreate[sizeof(create)]{}, actualLink[sizeof(link)]{};
    return ReadInputMemory(base + 0x3EE80u, actualCreate, sizeof(actualCreate)) &&
           std::memcmp(create, actualCreate, sizeof(create)) == 0 &&
           ReadInputMemory(base + 0x3EF83u, actualLink, sizeof(actualLink)) &&
           std::memcmp(link, actualLink, sizeof(link)) == 0;
}

static void InstallTalonReadInputHook()
{
    if (!g_talonInputLayoutValid || g_realTalonReadInput)
        return;
    const uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
    // The input-manager function table is initialized at 0x442124; ReadInput
    // is slot 5 at 0x4D3844. Verify the slot and the argument-3 load before use.
    const unsigned char expected[] = {0x55, 0x8B, 0xEC, 0x83, 0xE4, 0xF8,
                                     0x81, 0xEC, 0x6C, 0x05, 0x00, 0x00,
                                     0x8B, 0x45, 0x10};
    unsigned char actual[sizeof(expected)]{};
    uintptr_t original = 0;
    if (!ReadInputMemory(base + 0xD3844u, &original, sizeof(original)) ||
        original != base + 0x3F490u ||
        !ReadInputMemory(original, actual, sizeof(actual)) ||
        std::memcmp(actual, expected, sizeof(expected)) != 0)
        return;
    void *saved = nullptr;
    if (HookManager::InstallPointerRaw("renderer.input.ReadInput",
                                      reinterpret_cast<void **>(base + 0xD3844u),
                                      reinterpret_cast<void *>(&RendererTalonReadInputHook), &saved))
        g_realTalonReadInput = reinterpret_cast<PFN_TalonReadInput>(saved);
}

static void RefreshTalonInputDevices()
{
    if (!g_talonInputLayoutValid)
        return;
    const uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
    void *di = nullptr;
    if (ReadInputMemory(base + 0xE3B18u, &di, sizeof(di)) && di)
        PatchDirectInputInterface(di);

    // Devices may predate Renderer_Init, or be QueryInterface results with a
    // different vtable from CreateDevice's return value (stock 0x43F2BC).
    uintptr_t node = 0;
    if (!ReadInputMemory(base + 0xE3B1Cu, &node, sizeof(node)))
        return;
    for (unsigned visited = 0; node && visited < 128; ++visited)
    {
        void *device = nullptr;
        DWORD objectCount = 0;
        uintptr_t next = 0;
        if (!ReadInputMemory(node, &device, sizeof(device)) ||
            !ReadInputMemory(node + 0x88u, &objectCount, sizeof(objectCount)) ||
            !ReadInputMemory(node + 0x300u, &next, sizeof(next)))
            break;
        if (device && objectCount <= 150) // object pointer table: +0x90..+0x2E7
        {
            void **vt = nullptr;
            void *methods[11]{};
            if (ReadInputMemory(reinterpret_cast<uintptr_t>(device), &vt, sizeof(vt)) &&
                ReadInputMemory(reinterpret_cast<uintptr_t>(vt), methods, sizeof(methods)) &&
                MemoryUtils::IsExecutable(reinterpret_cast<uintptr_t>(methods[9])) &&
                MemoryUtils::IsExecutable(reinterpret_cast<uintptr_t>(methods[10])))
            {
                PatchDirectInputDevice(device);
                DIInputState(device).objectCount = objectCount;
            }
        }
        if (next == node)
            break;
        node = next;
    }
}

static void InstallInputCaptureHooks()
{
    void *original = nullptr;
    if (HookManager::InstallIAT("renderer.iat.GetAsyncKeyState", GetModuleHandleA(nullptr),
                                "USER32.dll", "GetAsyncKeyState", reinterpret_cast<void *>(&RendererGetAsyncKeyStateHook),
                                &original, &g_getAsyncKeyStateIATSlot))
        g_realExeGetAsyncKeyState = reinterpret_cast<PFN_GetAsyncKeyState>(original);

    original = nullptr;
    if (HookManager::InstallIAT("renderer.iat.GetKeyboardState", GetModuleHandleA(nullptr),
                                "USER32.dll", "GetKeyboardState", reinterpret_cast<void *>(&RendererGetKeyboardStateHook),
                                &original, &g_getKeyboardStateIATSlot))
        g_realExeGetKeyboardState = reinterpret_cast<PFN_GetKeyboardState>(original);

    original = nullptr;
    if (HookManager::InstallIAT("renderer.iat.DirectInputCreateA", GetModuleHandleA(nullptr),
                                "DINPUT.dll", "DirectInputCreateA", reinterpret_cast<void *>(&RendererDirectInputCreateAHook),
                                &original, &g_directInputCreateIATSlot))
    {
        g_realDirectInputCreateA = reinterpret_cast<PFN_DirectInputCreateA>(original);
        LOG_SESSION("Renderer ImGui DirectInputCreateA hook installed");
    }
    g_talonInputLayoutValid = ValidateTalonInputLayout();
    InstallTalonReadInputHook();
    RefreshTalonInputDevices();
    LOG_SESSION("Renderer ImGui existing input capture: layout=%d deviceVtables=%zu",
                g_talonInputLayoutValid ? 1 : 0, g_diDeviceHooks.size());
}

static void RemoveInputCaptureHooks()
{
    HookManager::Uninstall("renderer.input.ReadInput");
    g_realTalonReadInput = nullptr;
    for (auto &h : g_diDeviceHooks)
    {
        HookManager::Uninstall(h.dataPatchName.c_str());
        HookManager::Uninstall(h.statePatchName.c_str());
    }
    g_diDeviceHooks.clear();
    g_diInputCaptureStates.clear();
    g_talonInputLayoutValid = false;
    g_waitForUiMouseRelease = false;

    HookManager::Uninstall("renderer.dinput.CreateDevice");
    g_diCreateDeviceVtableSlot = nullptr;
    g_realDICreateDevice = nullptr;

    HookManager::Uninstall("renderer.iat.DirectInputCreateA");
    HookManager::Uninstall("renderer.iat.GetAsyncKeyState");
    HookManager::Uninstall("renderer.iat.GetKeyboardState");
    g_directInputCreateIATSlot = nullptr;
    g_getAsyncKeyStateIATSlot = nullptr;
    g_getKeyboardStateIATSlot = nullptr;
    g_realDirectInputCreateA = nullptr;
    g_realExeGetAsyncKeyState = nullptr;
    g_realExeGetKeyboardState = nullptr;
}
static constexpr UINT_PTR kRendererMouseSubclassId = 0x4F474C4Du; // 'OGLM'
static thread_local uint32_t g_renderer3DContextHolds = 0;
static thread_local uint32_t g_rendererScreenContextHolds = 0;

#define GL_SCOPE_VOID()                                                                  \
    RendererContextScope glScope;                                                        \
    if (!glScope)                                                                        \
    {                                                                                    \
        LOG_SESSION("Renderer callback could not acquire GL context: %s", __FUNCTION__); \
        return;                                                                          \
    }

#define GL_SCOPE_RET(value)                                                              \
    RendererContextScope glScope;                                                        \
    if (!glScope)                                                                        \
    {                                                                                    \
        LOG_SESSION("Renderer callback could not acquire GL context: %s", __FUNCTION__); \
        return (value);                                                                  \
    }

static bool IsClientMouseMessage(UINT msg)
{
    switch (msg)
    {
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDBLCLK:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_XBUTTONDBLCLK:
        return true;
    default:
        return false;
    }
}

static LPARAM RemapFullscreenMouseLParam(LPARAM lp)
{
    // True exclusive fullscreen runs the monitor at Talon's logical
    // framebuffer resolution.  The host client therefore already uses the
    // exact coordinate system expected by AVP2.  Do not alter mouse LPARAMs.
    return lp;
}

static LRESULT CALLBACK RendererHostSubclassProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp,
                                                 UINT_PTR, DWORD_PTR)
{
    LRESULT imguiResult = 0;
    if (GUIQuality::Instance().HandleImGuiWndProc(hwnd, msg, wp, lp, &imguiResult))
        return imguiResult;

    if (IsClientMouseMessage(msg))
        lp = RemapFullscreenMouseLParam(lp);

    return g_defSubclassProc ? g_defSubclassProc(hwnd, msg, wp, lp)
                             : DefWindowProc(hwnd, msg, wp, lp);
}

template <typename T>
static T ResolveWin32Proc(HMODULE module, const char *name)
{
    FARPROC raw = GetProcAddress(module, name);
    T typed = nullptr;
    static_assert(sizeof(typed) == sizeof(raw), "Win32 function pointer size mismatch");
    std::memcpy(&typed, &raw, sizeof(typed));
    return typed;
}

static bool ResolveWindowSubclassApi()
{
    if (g_setWindowSubclass && g_removeWindowSubclass && g_defSubclassProc)
        return true;

    // Comctl32 owns the implementation behind SetWindowSubclass /
    // DefSubclassProc.  A failed map load can make Talon tear the renderer down
    // while USER32 is still unwinding/dispatching through the subclass chain.
    // Unloading a renderer-owned LoadLibrary reference here used to leave an
    // executable callback address inside the now-unmapped comctl32 image.
    //
    // Keep common-controls resident for the lifetime of the process.  It is a
    // system DLL and this is the same effective lifetime it has in applications
    // that link against comctl32 normally.  Pinning also makes renderer unload /
    // reload cycles safe: no later FreeLibrary in another component can remove
    // the subclass implementation while the host HWND still exists.
    if (!g_comctl32Module)
    {
        HMODULE module = GetModuleHandleA("comctl32.dll");
        if (!module)
            module = LoadLibraryA("comctl32.dll");
        if (!module)
            return false;

        HMODULE pinned = nullptr;
        if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_PIN, "comctl32.dll", &pinned) && pinned)
        {
            g_comctl32Module = pinned;
            LOG_SESSION("Renderer window subclass: comctl32 pinned for process lifetime module=%p", pinned);
        }
        else
        {
            // Very old/odd platforms may reject PIN.  Still keep the reference
            // rather than unloading it during renderer teardown; one resident
            // system module is vastly safer than a dangling subclass thunk.
            g_comctl32Module = module;
            LOG_SESSION("Renderer window subclass: comctl32 pin unavailable err=%lu; keeping module resident=%p",
                        static_cast<unsigned long>(GetLastError()), module);
        }
    }

    g_setWindowSubclass = ResolveWin32Proc<PFN_SetWindowSubclass>(
        g_comctl32Module, "SetWindowSubclass");
    g_removeWindowSubclass = ResolveWin32Proc<PFN_RemoveWindowSubclass>(
        g_comctl32Module, "RemoveWindowSubclass");
    g_defSubclassProc = ResolveWin32Proc<PFN_DefSubclassProc>(
        g_comctl32Module, "DefSubclassProc");
    return g_setWindowSubclass && g_removeWindowSubclass && g_defSubclassProc;
}

static void InstallRendererMouseMapping(HWND hwnd)
{
    if (!hwnd)
        return;

    // This subclass is only needed while the renderer-owned ImGui tuning
    // UI is open.  Do NOT leave a renderer callback in the host HWND during
    // splash/loading/normal gameplay.  Talon can unload/reload the renderer
    // re-entrantly from a focus/activation message; an in-flight subclass proc
    // would otherwise return into unmapped opengl.ren code.
    if (g_rendererMouseSubclassInstalled)
    {
        if (g_rendererMouseSubclassHwnd == hwnd)
            return;

        // A renderer/window transition changed HWNDs.  Remove from the exact
        // HWND that we actually subclassed before installing on the new one.
        if (g_rendererMouseSubclassHwnd && g_removeWindowSubclass)
        {
            const BOOL removed = g_removeWindowSubclass(g_rendererMouseSubclassHwnd,
                                                        &RendererHostSubclassProc,
                                                        kRendererMouseSubclassId);
            LOG_SESSION("Renderer UI subclass migrate remove hwnd=%p removed=%d err=%lu",
                        g_rendererMouseSubclassHwnd, removed ? 1 : 0,
                        removed ? 0ul : static_cast<unsigned long>(GetLastError()));
        }
        g_rendererMouseSubclassInstalled = false;
        g_rendererMouseSubclassHwnd = nullptr;
    }

    if (!ResolveWindowSubclassApi())
    {
        LOG_SESSION("Renderer UI subclass install FAILED: comctl32 subclass API unavailable hwnd=%p", hwnd);
        return;
    }

    if (g_setWindowSubclass(hwnd, &RendererHostSubclassProc, kRendererMouseSubclassId, 0))
    {
        g_rendererMouseSubclassInstalled = true;
        g_rendererMouseSubclassHwnd = hwnd;
        LOG_SESSION("Renderer UI subclass installed hwnd=%p logical=%dx%d id=%llu",
                    hwnd, RendererCore::Instance().Width(), RendererCore::Instance().Height(),
                    static_cast<unsigned long long>(kRendererMouseSubclassId));
    }
    else
    {
        LOG_SESSION("Renderer UI subclass install FAILED hwnd=%p err=%lu",
                    hwnd, static_cast<unsigned long>(GetLastError()));
    }
}

static void RemoveRendererMouseMapping()
{
    // Always detach from the exact HWND used by SetWindowSubclass.  The host
    // HWND stored by the renderer can change during splash/mode transitions.
    HWND hwnd = g_rendererMouseSubclassHwnd;
    if (hwnd && g_rendererMouseSubclassInstalled && g_removeWindowSubclass)
    {
        const BOOL removed = g_removeWindowSubclass(hwnd, &RendererHostSubclassProc,
                                                    kRendererMouseSubclassId);
        LOG_SESSION("Renderer UI subclass remove hwnd=%p removed=%d err=%lu",
                    hwnd, removed ? 1 : 0,
                    removed ? 0ul : static_cast<unsigned long>(GetLastError()));
    }

    g_rendererMouseSubclassInstalled = false;
    g_rendererMouseSubclassHwnd = nullptr;
}

static void SyncRendererUiSubclass()
{
    const bool needSubclass = GUIQuality::Instance().IsTuningMenuOpen();
    if (needSubclass)
        InstallRendererMouseMapping(g_rendererHwnd);
    else
        RemoveRendererMouseMapping();
}

static void ReleaseWindowSubclassApi()
{
    // Never FreeLibrary(comctl32.dll) here.
    g_setWindowSubclass = nullptr;
    g_removeWindowSubclass = nullptr;
    g_defSubclassProc = nullptr;
    g_comctl32Module = nullptr;
}

static void RestoreExclusiveDisplayMode()
{
    if (!g_exclusiveDisplayActive)
        return;

    const char *device = g_exclusiveDisplayDevice[0] ? g_exclusiveDisplayDevice : nullptr;
    const LONG result = ChangeDisplaySettingsExA(device, nullptr, nullptr, 0, nullptr);
    LOG_SESSION("Renderer exclusive restore device='%s' result=%ld",
                device ? device : "<default>", static_cast<long>(result));

    g_exclusiveDisplayActive = false;
    g_exclusiveDisplayDevice[0] = '\0';
    g_exclusiveWidth = 0;
    g_exclusiveHeight = 0;
}

static bool EnterExclusiveDisplayMode(HWND hwnd, int width, int height)
{
    if (!hwnd || width <= 0 || height <= 0)
        return false;

    HMONITOR mon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEXA mi{};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoA(mon, &mi))
    {
        LOG_SESSION("Renderer exclusive: GetMonitorInfoA failed err=%lu", static_cast<unsigned long>(GetLastError()));
        return false;
    }

    char targetDevice[CCHDEVICENAME] = {};
    bool requestedDisplay = false;
    if (IsDisplayDeviceName(g_requestedDisplayDevice))
    {
        strncpy_s(targetDevice, g_requestedDisplayDevice, _TRUNCATE);
        requestedDisplay = true;
    }
    else
    {
        strncpy_s(targetDevice, mi.szDevice, _TRUNCATE);
    }

    // A renderer reload may enter here after a previous exclusive mode.  Avoid
    // stacking display-mode changes and make the transition deterministic.
    if (g_exclusiveDisplayActive)
        RestoreExclusiveDisplayMode();

    auto tryChange = [&](const char *deviceName) -> LONG
    {
        DEVMODEA dm{};
        dm.dmSize = sizeof(dm);
        dm.dmPelsWidth = static_cast<DWORD>(width);
        dm.dmPelsHeight = static_cast<DWORD>(height);
        dm.dmBitsPerPel = 32;
        dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

        LONG result = ChangeDisplaySettingsExA(deviceName, &dm, nullptr, CDS_FULLSCREEN, nullptr);
        if (result != DISP_CHANGE_SUCCESSFUL)
        {
            // Some drivers reject an explicit BPP field even though the requested
            // resolution is valid. Retry with width/height only.
            dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
            result = ChangeDisplaySettingsExA(deviceName, &dm, nullptr, CDS_FULLSCREEN, nullptr);
        }
        return result;
    };

    LONG result = tryChange(targetDevice);
    if (result != DISP_CHANGE_SUCCESSFUL && requestedDisplay && _stricmp(targetDevice, mi.szDevice) != 0)
    {
        LOG_SESSION("Renderer exclusive requested display '%s' failed result=%ld; falling back to nearest monitor '%s'",
                    targetDevice, static_cast<long>(result), mi.szDevice);
        strncpy_s(targetDevice, mi.szDevice, _TRUNCATE);
        requestedDisplay = false;
        result = tryChange(targetDevice);
    }

    if (result != DISP_CHANGE_SUCCESSFUL)
    {
        LOG_SESSION("Renderer exclusive FAILED device='%s' mode=%dx%d result=%ld",
                    targetDevice[0] ? targetDevice : "<default>", width, height, static_cast<long>(result));
        return false;
    }

    strncpy_s(g_exclusiveDisplayDevice, targetDevice, _TRUNCATE);
    g_exclusiveDisplayActive = true;
    g_exclusiveWidth = width;
    g_exclusiveHeight = height;

    const LONG_PTR wantStyle = WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    LONG_PTR ex = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
    const LONG_PTR wantEx = (ex & ~(WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME)) | WS_EX_APPWINDOW;
    SetWindowLongPtr(hwnd, GWL_STYLE, wantStyle);
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, wantEx);

    // After ChangeDisplaySettingsEx the display rectangle reflects the new
    // exclusive mode. Prefer the requested Win32 display identity when one was
    // chosen by AVP2.exe's launcher; otherwise fall back to the HWND monitor.
    RECT target{0, 0, width, height};
    if (!QueryCurrentDisplayRect(g_exclusiveDisplayDevice, target))
    {
        MONITORINFOEXA post{};
        post.cbSize = sizeof(post);
        if (GetMonitorInfoA(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST), &post))
            target = post.rcMonitor;
    }

    SetWindowPos(hwnd, HWND_TOPMOST,
                 target.left, target.top,
                 target.right - target.left, target.bottom - target.top,
                 SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOOWNERZORDER);

    LOG_SESSION("Renderer exclusive ENTER device='%s' requested=%dx%d monitor=(%ld,%ld)-(%ld,%ld) launcherRequested=%d",
                g_exclusiveDisplayDevice, width, height,
                target.left, target.top, target.right, target.bottom,
                requestedDisplay ? 1 : 0);
    return true;
}

static bool EnsureRendererWindowMode(HWND hwnd, bool windowed, bool force = false)
{
    if (!hwnd || windowed)
        return false;

    // Fullscreen is a real exclusive display mode. Keep the HWND exactly
    // on the monitor that owns that mode; do not stretch a logical FBO inside
    // a desktop-sized borderless window.
    HMONITOR mon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfo(mon, &mi))
        return false;

    const LONG_PTR wantStyle = WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
    LONG_PTR ex = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
    const LONG_PTR wantEx = (ex & ~(WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME)) | WS_EX_APPWINDOW;

    RECT wr{};
    GetWindowRect(hwnd, &wr);
    const int wantW = mi.rcMonitor.right - mi.rcMonitor.left;
    const int wantH = mi.rcMonitor.bottom - mi.rcMonitor.top;
    const bool rectWrong = wr.left != mi.rcMonitor.left || wr.top != mi.rcMonitor.top ||
                           (wr.right - wr.left) != wantW || (wr.bottom - wr.top) != wantH;
    const bool styleWrong = style != wantStyle;
    const bool exWrong = wantEx != ex;

    if (!force && !rectWrong && !styleWrong && !exWrong)
        return false;

    if (styleWrong || force)
        SetWindowLongPtr(hwnd, GWL_STYLE, wantStyle);
    if (exWrong || force)
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, wantEx);

    SetWindowPos(hwnd, HWND_TOPMOST, mi.rcMonitor.left, mi.rcMonitor.top, wantW, wantH,
                 SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOOWNERZORDER);

    LOG_SESSION("Renderer exclusive window enforce: force=%d rectWrong=%d styleWrong=%d exWrong=%d monitor=(%ld,%ld)-(%ld,%ld) oldWindow=(%ld,%ld)-(%ld,%ld)",
                force ? 1 : 0, rectWrong ? 1 : 0, styleWrong ? 1 : 0, exWrong ? 1 : 0,
                mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom,
                wr.left, wr.top, wr.right, wr.bottom);
    return true;
}

static bool EnsureWindowedClientSize(HWND hwnd, int clientWidth, int clientHeight)
{
    if (!hwnd || clientWidth <= 0 || clientHeight <= 0)
        return false;

    RECT client{};
    if (!GetClientRect(hwnd, &client))
        return false;

    const int currentW = client.right - client.left;
    const int currentH = client.bottom - client.top;
    if (currentW == clientWidth && currentH == clientHeight)
        return false;

    // The engine initially creates a small bootstrap HWND.  MSP resizes that
    // window after renderer init, while the original AVP2 CShell leaves it at
    // the bootstrap dimensions.  Size the host window to the render mode's
    // requested *client* area here so renderer behavior does not depend on a
    // particular CShell doing a later Win32 resize.
    const DWORD style = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_STYLE));
    const DWORD exStyle = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_EXSTYLE));
    RECT outer{0, 0, clientWidth, clientHeight};
    if (!AdjustWindowRectEx(&outer, style, FALSE, exStyle))
    {
        LOG_SESSION("Renderer windowed resize: AdjustWindowRectEx failed requestedClient=%dx%d err=%lu",
                    clientWidth, clientHeight, static_cast<unsigned long>(GetLastError()));
        return false;
    }

    RECT wr{};
    if (!GetWindowRect(hwnd, &wr))
        return false;

    const int outerW = outer.right - outer.left;
    const int outerH = outer.bottom - outer.top;
    const BOOL ok = SetWindowPos(hwnd, nullptr, wr.left, wr.top, outerW, outerH,
                                 SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

    if (LogIsSessionEnabled())
    {
        RECT after{};
        GetClientRect(hwnd, &after);
        LOG_SESSION("Renderer windowed resize: bootstrapClient=%dx%d requestedClient=%dx%d outer=%dx%d result=%d finalClient=%ldx%ld",
                    currentW, currentH, clientWidth, clientHeight, outerW, outerH, ok ? 1 : 0,
                    after.right - after.left, after.bottom - after.top);
    }

    return ok != FALSE;
}

static bool ClientRectToScreen(HWND hwnd, const RECT &clientRc, RECT &screenRc)
{
    if (!hwnd || clientRc.right <= clientRc.left || clientRc.bottom <= clientRc.top)
        return false;

    POINT pts[2] = {{clientRc.left, clientRc.top}, {clientRc.right, clientRc.bottom}};
    MapWindowPoints(hwnd, nullptr, pts, 2);
    screenRc = RECT{pts[0].x, pts[0].y, pts[1].x, pts[1].y};
    return screenRc.right > screenRc.left && screenRc.bottom > screenRc.top;
}

static bool GetClientScreenRect(HWND hwnd, RECT &screenRc)
{
    RECT rc{};
    if (!hwnd || !GetClientRect(hwnd, &rc))
        return false;
    return ClientRectToScreen(hwnd, rc, screenRc);
}

static RECT GetVirtualDesktopRect()
{
    RECT rc{};
    rc.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
    rc.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
    rc.right = rc.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
    rc.bottom = rc.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);
    return rc;
}

static bool RectEqualExact(const RECT &a, const RECT &b)
{
    return a.left == b.left && a.top == b.top &&
           a.right == b.right && a.bottom == b.bottom;
}

static void RefreshCursorClipForWindow(HWND hwnd, bool forceInitial = false)
{
    if (!hwnd)
        return;

    RECT current{};
    if (!GetClipCursor(&current))
        return;

    // AVP2 uses ClipCursor(NULL) to release confinement in menus. Windows then
    // reports the virtual desktop as the clip rectangle. Do not re-confine in
    // that state; only resize an already-active confinement rectangle.
    const RECT desktop = GetVirtualDesktopRect();
    if (!forceInitial && RectEqualExact(current, desktop))
        return;

    if (!forceInitial && GetForegroundWindow() != hwnd)
        return;

    RECT desired{};
    // Fullscreen confinement must match the actual presented image, not
    // the entire borderless client.  The latter includes letterbox/pillarbox
    // pixels which have no corresponding logical framebuffer coordinate and
    // were the source of edge-offset menu hit testing.
    const bool haveDesired = GetClientScreenRect(hwnd, desired);
    if (!haveDesired)
        return;

    if (!RectEqualExact(current, desired))
    {
        ClipCursor(&desired);
        LOG_SESSION("Renderer cursor clip refresh=(%ld,%ld)-(%ld,%ld) old=(%ld,%ld)-(%ld,%ld) initial=%d fullscreenViewport=%d",
                    desired.left, desired.top, desired.right, desired.bottom,
                    current.left, current.top, current.right, current.bottom,
                    forceInitial ? 1 : 0, g_rendererWindowed ? 0 : 1);
    }
}

static int Renderer_Init(RenderStructInit *init)
{
    CallbackTrace trace("Init");
    if (!init || !init->m_hWnd)
        return RENDER_ERROR;

    init->m_nRendererVersion = LTRENDER_VERSION;
    g_rendererHwnd = init->m_hWnd;

    // MSP changes the incoming RMode to 32bpp and forces 32BitTextures=1
    // before SetRenderMode. Original AVP2 does not. Mirror that verified MSP
    // behavior before we consume any of the mode/texture state.
    CShell::Detect();
    MSPCompatibility::PrepareRenderMode(init->m_Mode.m_dwBitDepth);

    LOG_SESSION("Renderer_Init requested: %ux%u %ubpp hwnd=%p internal='%s' desc='%s'",
                init->m_Mode.m_dwWidth, init->m_Mode.m_dwHeight,
                init->m_Mode.m_dwBitDepth, init->m_hWnd,
                init->m_Mode.m_szInternalName, init->m_Mode.m_szDescription);

    if (IsDisplayDeviceName(init->m_Mode.m_szInternalName))
    {
        strncpy_s(g_requestedDisplayDevice, init->m_Mode.m_szInternalName, _TRUNCATE);
        LOG_SESSION("Renderer_Init launcher-selected display='%s'", g_requestedDisplayDevice);
    }
    else
    {
        g_requestedDisplayDevice[0] = '\0';
    }

    const int width = static_cast<int>(init->m_Mode.m_dwWidth ? init->m_Mode.m_dwWidth : 640);
    const int height = static_cast<int>(init->m_Mode.m_dwHeight ? init->m_Mode.m_dwHeight : 480);

    // Match stock d3d_device.cpp presentation selection.  LithTech uses
    // D3DSWAPEFFECT_COPY only in windowed mode; fullscreen defaults to
    // D3DSWAPEFFECT_DISCARD with two backbuffers.
    const bool windowed = Console::Instance().GetBool("windowed", false);
    LOG_SESSION("Renderer_Init presentation mode: windowed=%d stockSwap=%s",
                windowed ? 1 : 0, windowed ? "COPY" : "DISCARD");

    g_rendererWindowed = windowed;

    if (windowed)
    {
        // Do not rely on a particular CShell build to promote Talon's tiny
        // bootstrap HWND to the selected render mode.  Original AVP2 does not
        // follow the same post-init resize path as MSP.
        EnsureWindowedClientSize(init->m_hWnd, width, height);
    }
    else
    {
        if (!EnterExclusiveDisplayMode(init->m_hWnd, width, height))
        {
            LOG_SESSION("Renderer_Init failed: could not enter exclusive fullscreen %dx%d", width, height);
            g_rendererWindowed = true;
            return RENDER_ERROR;
        }
    }

    // Mode changes can occur while a world is resident and Talon still has
    // synchronous renderer calls arriving from loading/render worker threads.
    // Serialize the entire cold-init against the same lock used by GL_SCOPE.
    // No normal renderer entrypoint can observe a partially-created context or
    // a mixture of old/new resolution resources.
    RendererCore::Instance().AcquireLifecycleExclusive();
    const bool rendererInitOk = RendererCore::Instance().Init(init->m_hWnd, width, height, windowed);
    if (!rendererInitOk)
    {
        LOG_SESSION("Renderer_Init failed; rolling back partial renderer state.");
        // Init may have created a WGL context/FBO/shaders before a later stage
        // failed.  Tear that partial state down while we still own the lifecycle
        // lock instead of returning it to Talon in an indeterminate state.
        RendererCore::Instance().Term();
        RendererCore::Instance().ReleaseLifecycleExclusive();
        if (!windowed)
            RestoreExclusiveDisplayMode();
        return RENDER_ERROR;
    }
    RendererCore::Instance().ReleaseLifecycleExclusive();

    // Install the remainder of the verified base-game MSP compatibility layer.
    MSPCompatibility::Install(init->m_hWnd, windowed, width, height);

    // Remove the avp2msp 2.4 CSHELL's presentation-side 60 FPS limiter and
    // replace it with d3d7fix_avp2-style millisecond time calibration in the
    // LithTech client/game/server timing paths.  The timing subsystem validates
    // every engine patch site and rolls back atomically on mismatch.
    HighRefreshTimingFix::Install();

    // Window subclassing is deferred until Insert tuning UI is actually open.
    InstallSetCursorPosHook();
    InstallInputCaptureHooks();
    OpenGLOptionsMenu::Instance().InstallCShellHooks();

    strncpy_s(init->m_Mode.m_szRenderDLL, "opengl.ren", _TRUNCATE);
    strncpy_s(init->m_Mode.m_szInternalName, "OpenGL46", _TRUNCATE);
    strncpy_s(init->m_Mode.m_szDescription, "AVP2 OpenGL 4.6 Core", _TRUNCATE);
    init->m_Mode.m_bHardware = LTTRUE;
    init->m_Mode.m_dwBitDepth = 32;

    if (g_rs)
    {
        g_rs->m_dwWidth = width;
        g_rs->m_dwHeight = height;
        g_rs->m_bInitted = LTTRUE;
    }

    // Do not force a cursor clip here. At this point Talon may still have the
    // bootstrap window active and will resize/reposition it after Init. The
    // live clip rectangle is synchronized from SwapBuffers once confinement is
    // actually active.

    LOG_SESSION("Renderer_Init OK version=%d", init->m_nRendererVersion);
    return RENDER_OK;
}

static void Renderer_Term()
{
    // Engine callsites point into opengl.ren while timing/MSP compatibility is
    // installed, so restore them before renderer teardown/unload.
    HighRefreshTimingFix::Remove();
    MSPCompatibility::Remove();
    OpenGLOptionsMenu::Instance().RemoveCShellHooks();
    CallbackTrace trace("Term");
    LOG_SESSION("Renderer_Term");

    // The HWND callback must be detached BEFORE anything that can fail
    // or early-return during GL teardown. Talon unloads opengl.ren on a mode
    // change; leaving any subclass callback pointing into this DLL would make
    // the next window message execute unloaded code.
    RemoveInputCaptureHooks();
    RemoveSetCursorPosHook();
    HookManager::UninstallAll(); // safety net: restore any remaining registered edits before renderer unload.
    RemoveRendererMouseMapping();

    // Teardown must be atomic with respect to all GL_SCOPE entrypoints.  A
    // loaded map can still have renderer calls in flight while Talon changes
    // mode; wait for them to finish, then keep them blocked until every
    // context-owned object has been destroyed and the HGLRC is gone.
    RendererCore::Instance().AcquireLifecycleExclusive();
    RendererCore::Instance().Term();
    RendererCore::Instance().ReleaseLifecycleExclusive();

    RestoreExclusiveDisplayMode();

    ReleaseWindowSubclassApi();
    g_rendererHwnd = nullptr;
    g_rendererWindowed = true;
    if (g_rs)
        g_rs->m_bInitted = LTFALSE;
}

static void Renderer_BindTexture(SharedTexture *texture, LTBOOL changed)
{
    GL_SCOPE_VOID();
    TextureManager::Instance().Ensure(texture, changed != 0);
}

static void Renderer_UnbindTexture(SharedTexture *texture)
{
    GL_SCOPE_VOID();
    TextureManager::Instance().Unbind(texture);
}
static void Renderer_RebindLightmaps(RenderContext *) {}

static RenderContext *Renderer_CreateContext(RenderContextInit *init)
{
    CallbackTrace trace("CreateContext");
    auto *ctx = new RenderContext{};
    ctx->m_pMainWorld = init ? init->m_pMainWorld : nullptr;
    ctx->m_wCurFrameCode = 0;
    LOG_SESSION("CreateContext -> %p mainWorld=%p (dummy context for 2D milestone)", ctx, ctx->m_pMainWorld);
    return ctx;
}

static void Renderer_DeleteContext(RenderContext *ctx)
{
    CallbackTrace trace("DeleteContext");
    LOG_SESSION("DeleteContext %p", ctx);
    delete ctx;
}

static void Renderer_Clear(LTRect *rect, uint32 flags, LTVector *color)
{
    LogHotEvent(HotEvent::Clear);
    // Match d3d_Clear's per-call load/render critical section
    GL_SCOPE_VOID();
    RendererCore::Instance().Clear(rect, flags, color);
}

static LTBOOL Renderer_Start3D()
{
    RendererCore::Instance().PerfMarkFrameStart();
    CallbackTrace trace("Start3D", false);
    // CSHELL and the in-process server shell can finish loading after renderer
    // init. This keeps the limiter and fixed-simulation hooks attached.
    HighRefreshTimingFix::TickRuntimePatches();
    // Keep one recursive ownership level until End3D.  All renderer callbacks
    // inside the frame then reuse the already-current context instead of doing
    // a WGL handoff for every blit/draw.
    if (!RendererCore::Instance().AcquireThreadContext())
        return LTFALSE;
    const bool ok = RendererCore::Instance().Start3D();
    if (!ok)
        RendererCore::Instance().ReleaseThreadContext();
    else
        ++g_renderer3DContextHolds;
    return ok ? LTTRUE : LTFALSE;
}

static LTBOOL Renderer_End3D()
{
    CallbackTrace trace("End3D", false);
    const bool matchingStart = g_renderer3DContextHolds > 0;
    bool temporaryOwnership = false;
    if (!matchingStart)
    {
        // Be tolerant of an unmatched End3D, but still make its GL operations
        // safe without consuming ownership held by another mapped resource.
        if (!RendererCore::Instance().AcquireThreadContext())
            return LTFALSE;
        temporaryOwnership = true;
    }

    const bool ok = RendererCore::Instance().End3D();
    if (matchingStart)
    {
        --g_renderer3DContextHolds;
        RendererCore::Instance().ReleaseThreadContext();
    }
    else if (temporaryOwnership)
    {
        RendererCore::Instance().ReleaseThreadContext();
    }
    return ok ? LTTRUE : LTFALSE;
}
static LTBOOL Renderer_IsIn3D()
{
    GL_SCOPE_RET(LTFALSE);
    return RendererCore::Instance().IsIn3D() ? LTTRUE : LTFALSE;
}

static LTBOOL Renderer_StartOptimized2D()
{
    GL_SCOPE_RET(LTFALSE);
    LogHotEvent(HotEvent::StartOptimized2D);
    return Renderer2D::Instance().StartOptimized() ? LTTRUE : LTFALSE;
}

static void Renderer_EndOptimized2D()
{
    GL_SCOPE_VOID();
    LogHotEvent(HotEvent::EndOptimized2D);
    Renderer2D::Instance().EndOptimized();
}

static LTBOOL Renderer_IsInOptimized2D()
{
    GL_SCOPE_RET(LTFALSE);
    return Renderer2D::Instance().IsOptimized() ? LTTRUE : LTFALSE;
}

static LTBOOL Renderer_SetOptimized2DBlend(LTSurfaceBlend blend)
{
    GL_SCOPE_RET(LTFALSE);
    return Renderer2D::Instance().SetBlend(blend) ? LTTRUE : LTFALSE;
}

static LTBOOL Renderer_GetOptimized2DBlend(LTSurfaceBlend &blend)
{
    GL_SCOPE_RET(LTFALSE);
    return Renderer2D::Instance().GetBlend(blend) ? LTTRUE : LTFALSE;
}

static LTBOOL Renderer_SetOptimized2DColor(HLTCOLOR color)
{
    GL_SCOPE_RET(LTFALSE);
    return Renderer2D::Instance().SetColor(color) ? LTTRUE : LTFALSE;
}

static LTBOOL Renderer_GetOptimized2DColor(HLTCOLOR &color)
{
    GL_SCOPE_RET(LTFALSE);
    return Renderer2D::Instance().GetColor(color) ? LTTRUE : LTFALSE;
}

namespace
{
    struct FixedCameraInterpolationState
    {
        bool valid = false;
        unsigned long long serial = 0;
        LTVector previousPos{};
        LTVector currentPos{};
        LTRotation previousRot{};
        LTRotation currentRot{};
    };

    static FixedCameraInterpolationState g_fixedCameraInterp{};

    static float CameraPosDistanceSq(const LTVector &a, const LTVector &b)
    {
        const float x = a.x - b.x, y = a.y - b.y, z = a.z - b.z;
        return x * x + y * y + z * z;
    }

    static LTRotation NlerpRotation(const LTRotation &a, const LTRotation &b, float t)
    {
        const float dot = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        const float sign = (dot < 0.0f) ? -1.0f : 1.0f;
        const float x = a.x + ((b.x * sign) - a.x) * t;
        const float y = a.y + ((b.y * sign) - a.y) * t;
        const float z = a.z + ((b.z * sign) - a.z) * t;
        const float w = a.w + ((b.w * sign) - a.w) * t;
        const float lenSq = x * x + y * y + z * z + w * w;

        if (lenSq > 1.0e-12f)
        {
            const float invLen = 1.0f / std::sqrt(lenSq);
            return LTRotation(x * invLen, y * invLen, z * invLen, w * invLen);
        }

        return b;
    }

    static void ApplyFixedCameraInterpolation(SceneDesc *scene)
    {
        // Draw mode 1 is the normal world scene. Object-list/menu scenes retain
        // their authored camera behavior and are deliberately not interpolated.
        if (!scene || scene->m_nDrawMode != 1 || !HighRefreshTimingFix::IsInstalled())
        {
            g_fixedCameraInterp.valid = false;
            return;
        }

        const unsigned long long serial = HighRefreshTimingFix::GetClientSimulationSerial();
        const LTVector authoritativePos = scene->m_vPos;
        const LTRotation authoritativeRot = scene->m_rRotation;

        if (!g_fixedCameraInterp.valid)
        {
            g_fixedCameraInterp.valid = true;
            g_fixedCameraInterp.serial = serial;
            g_fixedCameraInterp.previousPos = authoritativePos;
            g_fixedCameraInterp.currentPos = authoritativePos;
            g_fixedCameraInterp.previousRot = authoritativeRot;
            g_fixedCameraInterp.currentRot = authoritativeRot;
            return;
        }

        if (serial != g_fixedCameraInterp.serial)
        {
            // Teleports/map transitions must snap instead of blending across the
            // world. 256 units is comfortably above ordinary one-tick player motion.
            const bool teleport = CameraPosDistanceSq(g_fixedCameraInterp.currentPos, authoritativePos) > (256.0f * 256.0f);
            if (teleport)
            {
                g_fixedCameraInterp.previousPos = authoritativePos;
                g_fixedCameraInterp.previousRot = authoritativeRot;
            }
            else
            {
                g_fixedCameraInterp.previousPos = g_fixedCameraInterp.currentPos;
                g_fixedCameraInterp.previousRot = g_fixedCameraInterp.currentRot;
            }
            g_fixedCameraInterp.currentPos = authoritativePos;
            g_fixedCameraInterp.currentRot = authoritativeRot;
            g_fixedCameraInterp.serial = serial;
        }

        const float alpha = std::clamp(HighRefreshTimingFix::GetClientInterpolationAlpha(), 0.0f, 1.0f);
        scene->m_vPos.x = g_fixedCameraInterp.previousPos.x + (g_fixedCameraInterp.currentPos.x - g_fixedCameraInterp.previousPos.x) * alpha;
        scene->m_vPos.y = g_fixedCameraInterp.previousPos.y + (g_fixedCameraInterp.currentPos.y - g_fixedCameraInterp.previousPos.y) * alpha;
        scene->m_vPos.z = g_fixedCameraInterp.previousPos.z + (g_fixedCameraInterp.currentPos.z - g_fixedCameraInterp.previousPos.z) * alpha;
        scene->m_rRotation = NlerpRotation(g_fixedCameraInterp.previousRot, g_fixedCameraInterp.currentRot, alpha);

        if (LogIsSessionEnabled())
        {
            // This used to emit once per simulation serial.  With global
            // quantization disabled that is effectively once per rendered frame
            // (300-500 formatted file writes/sec), contaminating HOST profiling.
            // A 1 Hz sample is sufficient to verify interpolation state.
            static ULONGLONG lastInterpLogMs = 0;
            const ULONGLONG nowMs = GetTickCount64();
            if (lastInterpLogMs == 0 || nowMs - lastInterpLogMs >= 1000)
            {
                LOG_SESSION("INTERP camera serial=%llu alpha=%.4f auth=(%.3f %.3f %.3f) render=(%.3f %.3f %.3f)",
                            serial, alpha, authoritativePos.x, authoritativePos.y, authoritativePos.z,
                            scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z);
                lastInterpLogMs = nowMs;
            }
        }
    }
}

// Lock menus to 60fps
static bool g_SawNormalWorldScene = false;
static bool g_SawMenuObjectScene = false;
static LARGE_INTEGER g_MenuLimiterFreq{};
static LARGE_INTEGER g_MenuLastPresent{};
static bool g_MenuLimiterReady = false;

static void LimitMenuPresent60Hz()
{
    if (!g_MenuLimiterReady)
    {
        if (!QueryPerformanceFrequency(&g_MenuLimiterFreq) || g_MenuLimiterFreq.QuadPart <= 0)
            return;
        QueryPerformanceCounter(&g_MenuLastPresent);
        g_MenuLimiterReady = true;
        return;
    }

    const LONGLONG interval = g_MenuLimiterFreq.QuadPart / 60;
    if (interval <= 0)
        return;

    LARGE_INTEGER now{};
    QueryPerformanceCounter(&now);
    const LONGLONG target = g_MenuLastPresent.QuadPart + interval;

    while (now.QuadPart < target)
    {
        const LONGLONG remain = target - now.QuadPart;
        const double remainMs = (1000.0 * static_cast<double>(remain)) /
                                static_cast<double>(g_MenuLimiterFreq.QuadPart);
        if (remainMs > 2.0)
            Sleep(1);
        else
            SwitchToThread();
        QueryPerformanceCounter(&now);
    }

    // Advance from the actual present time instead of repeatedly adding the
    // ideal interval.  This prevents long stalls/menu transitions from causing
    // catch-up bursts.
    g_MenuLastPresent = now;
}

static int Renderer_RenderScene(SceneDesc *scene)
{
    GL_SCOPE_RET(RENDER_ERROR);
    if (scene)
    {
        if (scene->m_nDrawMode == 1)
            g_SawNormalWorldScene = true;
        else if (scene->m_nDrawMode == 2)
            g_SawMenuObjectScene = true;
    }
    OpenGLOptionsMenu::Instance().Tick();
    RefreshFogStateFromConsole();
    StockRenderOptions::Instance().Refresh();

    // Authoritative gameplay/physics advances at the fixed slider rate,
    // while this presentation-only SceneDesc copy is interpolated every render
    // frame. This keeps collision/state fixed-step without camera staircase.
    ApplyFixedCameraInterpolation(scene);

    static bool f11WasDown = false;
    static bool wireframeToggle = false;
    const bool f11Down = (GetAsyncKeyState(VK_F11) & 0x8000) != 0;
    if (f11Down && !f11WasDown)
    {
        wireframeToggle = !wireframeToggle;
        Console::Instance().SetBool("wireframe", wireframeToggle);
        LOG_SESSION("Renderer F11 wireframe -> %d", wireframeToggle ? 1 : 0);
    }
    f11WasDown = f11Down;

    const bool wireframe = Console::Instance().GetFloat("Wireframe", wireframeToggle ? 1.0f : 0.0f) != 0.0f;
    wireframeToggle = wireframe;
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);

    const int64_t qualityBegin = RendererCore::Instance().PerfTimingBegin();
    GUIQuality::Instance().BeginScene(scene);
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Quality, qualityBegin);

    const int result = SceneRenderer::Instance().RenderScene(scene);
    if (scene)
    {
        // AVP2 d3d.ren RenderScene calls 0x10015240 with
        // SceneDesc+0x50 after the scene object/world flush.  InvertHack
        // changes that pass to INVDESTCOLOR/ZERO: this is the Alien-vision
        // framebuffer inversion and, critically, it occurs before the game
        // draws its later 2D vision overlay.
        const bool invertHack = Console::Instance().GetFloat("InvertHack", 0.0f) != 0.0f;
        const int64_t qualityPost = RendererCore::Instance().PerfTimingBegin();
        GUIQuality::Instance().ApplyGlobalLightScale(scene->m_vGlobalLightScale, invertHack);
        // d3d.ren 0x10014CCD..0x10014CD1 always follows the
        // GlobalLightScale/InvertHack pass with SceneDesc+0x74 GlobalLightAdd.
        GUIQuality::Instance().ApplyGlobalLightAdd(scene->m_vGlobalLightAdd);
        RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Quality, qualityPost);
    }
    const int64_t qualityEnd = RendererCore::Instance().PerfTimingBegin();
    GUIQuality::Instance().EndScene(scene);
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Quality, qualityEnd);
    // A real renderer scene (normal world or explicit object-list scene) is a
    // meaningful frame even if a particular visibility phase happened to draw
    // zero primitives.  This distinguishes it from AVP2's transition-time
    // Start3D/Clear/End3D/Swap housekeeping frames.
    if (scene)
        RendererPresenter::Instance().MarkFrameContent();
    return result;
}

// ---------------------------------------------------------------------------
// LithTech console RenderCommand "rcom" handling.
//
// The LithTech engine forwards RenderCommands or RComs entered via the LT
// console to RenderStruct::RenderCommand. Each renderer can define its own set
// of commands. RCom and RenderCommand are both aliases for the same engine
// handler.
//
// The stock renderer (d3d.ren) implements listdevices, listtextureformats,
// listdevicecaps, freetextures, loadgamma <file>, and a stubbed command
// named portalfile <file>.
//
// This is called from LithTech's console, outside of a frame, with no
// guaranteed current GL context.
// ---------------------------------------------------------------------------

struct RenderCommandEntry
{
    const char *name;
    void (*handler)(int argc, char **argv);
};

// argv[0] is RCom sub-command e.g. 'ListDevices' in 'RCom ListDevices'
// argv[1..argc-1] are arguments to that subcommand.
static void RCom_ListDevices(int argc, char **argv);
static void RCom_ListTexFormats(int argc, char **argv);
static void RCom_ListDeviceCaps(int argc, char **argv);
static void RCom_FreeTextures(int argc, char **argv);
static void RCom_LoadGamma(int argc, char **argv);
static void RCom_PortalFile(int argc, char **argv);

static const RenderCommandEntry kRenderCommands[] = {
    {"LISTDEVICES", RCom_ListDevices},
    {"LISTTEXTUREFORMATS", RCom_ListTexFormats},
    {"LISTDEVICECAPS", RCom_ListDeviceCaps},
    {"FREETEXTURES", RCom_FreeTextures},
    {"LOADGAMMA", RCom_LoadGamma},
    {"PortalFile", RCom_PortalFile}
};

static void RCom_ListDevices(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // Stock d3d renderer enumerates DirectDraw devices with
    // DirectDrawEnumerateExA(DDENUM_ATTACHEDSECONDARYDEVICES)
    // and prints each device as "Device: %s".
    // This uses the Win32 API call instead of DirectDraw.
    // It produces identical output to the DDRAW call.
    Console::Instance().Print("Device: %s", "display");

    for (DWORD adapterIndex = 0;; ++adapterIndex)
    {
        DISPLAY_DEVICEA dd{};
        dd.cb = sizeof(dd);
        if (!EnumDisplayDevicesA(nullptr, adapterIndex, &dd, 0))
            break;

        if ((dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) == 0)
            continue;
        if ((dd.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) != 0)
            continue;
        if (!dd.DeviceName[0])
            continue;

        Console::Instance().Print("Device: %s", dd.DeviceName);
    }
}

// A texture format described the way stock d3d.ren prints a DDPIXELFORMAT:
// the type name, bits per pixel, and the R, G, B, A channel masks.
struct RComPixelFormat
{
    const char *name;
    uint32 bitCount;
    uint32 masks[4];
};

// The GL internal formats opengl.ren creates textures with (Texture.cpp
// InternalFormatFor, plus GL_RGBA4 for the 4444 class).  RGBA8 and RGBA4
// match the stock A8R8G8B8 and A4R4G4B4 lines.  The trailing space in
// "DDPF_ALPHAPIXELS " is part of the stock output.
// TODO: Get this info from texture manager so changes automatically
// show up here.
static const RComPixelFormat kRComFormatRGBA8 = {"DDPF_ALPHAPIXELS ", 32, {0x00FF0000u, 0x0000FF00u, 0x000000FFu, 0xFF000000u}};
static const RComPixelFormat kRComFormatRGBA4 = {"DDPF_ALPHAPIXELS ", 16, {0x0F00u, 0x00F0u, 0x000Fu, 0xF000u}};
static const RComPixelFormat kRComFormatDXT1 = {"FOURCC( DXT1 )", 0, {0u, 0u, 0u, 0u}};
static const RComPixelFormat kRComFormatDXT3 = {"FOURCC( DXT3 )", 0, {0u, 0u, 0u, 0u}};
static const RComPixelFormat kRComFormatDXT5 = {"FOURCC( DXT5 )", 0, {0u, 0u, 0u, 0u}};

// Stock d3d.ren prints "%s%s - %d bits (%d %d %d %d) (%x %x %x %x)"
// with a prefix, the type name, the bit count, the bits set in each mask,
// and the masks themselves.
static void RCom_PrintPixelFormat(const char *prefix, const RComPixelFormat &format)
{
    uint32 bits[4] = {};
    for (int i = 0; i < 4; ++i)
    {
        for (uint32 mask = format.masks[i]; mask; mask &= mask - 1)
            ++bits[i];
    }

    Console::Instance().Print("%s%s - %u bits (%u %u %u %u) (%x %x %x %x)",
                              prefix, format.name, format.bitCount,
                              bits[0], bits[1], bits[2], bits[3],
                              format.masks[0], format.masks[1], format.masks[2], format.masks[3]);
}

static void RCom_ListTexFormats(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // Stock d3d.ren prints every texture format the D3D7 device
    // enumerated, then the format it picked for each texture category. GL
    // has no format enumeration, so list the formats opengl.ren actually
    // creates, then what each category really gets here.
    RCom_PrintPixelFormat("", kRComFormatRGBA8);
    RCom_PrintPixelFormat("", kRComFormatRGBA4);
    RCom_PrintPixelFormat("", kRComFormatDXT1);
    RCom_PrintPixelFormat("", kRComFormatDXT3);
    RCom_PrintPixelFormat("", kRComFormatDXT5);

    RCom_PrintPixelFormat("[FULLBRITE] - ", kRComFormatRGBA8);
    RCom_PrintPixelFormat("[4444] - ", kRComFormatRGBA4);
    RCom_PrintPixelFormat("[NORMAL] - ", kRComFormatRGBA8);
    RCom_PrintPixelFormat("[INTERFACE] - ", kRComFormatRGBA8);
    RCom_PrintPixelFormat("[LIGHTMAP] - ", kRComFormatRGBA8);
}

// GL enums LISTDEVICECAPS needs that the Windows SDK's GL 1.1 gl.h lacks.
static constexpr GLenum GL_NUM_EXTENSIONS_ = 0x821D;
static constexpr GLenum GL_RENDERBUFFER_DEPTH_SIZE_ = 0x8D54;
static constexpr GLenum GL_RENDERBUFFER_STENCIL_SIZE_ = 0x8D55;
static constexpr GLenum GL_MAX_FRAMEBUFFER_WIDTH_ = 0x9315;
static constexpr GLenum GL_MAX_FRAMEBUFFER_HEIGHT_ = 0x9316;
static constexpr GLenum GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX_ = 0x9047;
static constexpr GLenum GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX_ = 0x9048;

// Reads the hex number after a tag in a hardware ID such as
// "PCI\VEN_xxxx&DEV_xxxx&SUBSYS_xxxxxxxx&REV_xx".  USB display adapters use
// VID_/PID_ in place of VEN_/DEV_, so a second tag can be given.
static uint32 RCom_HardwareIdField(const char *deviceId, const char *tag, const char *altTag)
{
    const char *field = std::strstr(deviceId, tag);
    if (!field && altTag)
    {
        field = std::strstr(deviceId, altTag);
        tag = altTag;
    }
    if (!field)
        return 0;
    return static_cast<uint32>(std::strtoul(field + std::strlen(tag), nullptr, 16));
}

// PCI vendor ID of the GPU behind the GL context, from GL_VENDOR.
// 0 when the vendor can't be mapped, e.g. MSFT's s/w GDI renderer.
static uint32 RCom_GLVendorId(const char *glVendor)
{
    static const struct
    {
        const char *prefix;
        uint32 vendorId;
    } kVendors[] = {
        {"Intel", 0x8086u},
        {"NVIDIA", 0x10DEu},
        {"ATI", 0x1002u},
        {"AMD", 0x1002u},
        {"Advanced Micro Devices", 0x1002u},
    };

    if (!glVendor)
        return 0;
    for (const auto &vendor : kVendors)
    {
        if (_strnicmp(glVendor, vendor.prefix, std::strlen(vendor.prefix)) == 0)
            return vendor.vendorId;
    }
    return 0;
}

// The display adapter of the GPU that GL renders on.
// Prefers the adapter showing the game window, but when that
// adapter is from another vendor, e.g. a USB display hub
// that only receives frames the GPU already rendered, or the integrated GPU
// on a laptop rendering with its discrete one, takes the first adapter from
// GL's vendor instead. Falls back to the primary adapter.
static bool RCom_FindAdapter(DISPLAY_DEVICEA &adapter, uint32 glVendorId)
{
    char monitorDevice[CCHDEVICENAME] = {};
    if (g_rendererHwnd)
    {
        MONITORINFOEXA info{};
        info.cbSize = sizeof(info);
        HMONITOR monitor = MonitorFromWindow(g_rendererHwnd, MONITOR_DEFAULTTOPRIMARY);
        if (monitor && GetMonitorInfoA(monitor, &info))
            std::snprintf(monitorDevice, sizeof(monitorDevice), "%s", info.szDevice);
    }

    bool foundWindow = false;
    bool foundVendor = false;
    bool foundPrimary = false;
    DISPLAY_DEVICEA windowAdapter{};
    DISPLAY_DEVICEA vendorAdapter{};
    DISPLAY_DEVICEA primary{};
    for (DWORD adapterIndex = 0;; ++adapterIndex)
    {
        DISPLAY_DEVICEA dd{};
        dd.cb = sizeof(dd);
        if (!EnumDisplayDevicesA(nullptr, adapterIndex, &dd, 0))
            break;

        if (!foundWindow && monitorDevice[0] && _stricmp(dd.DeviceName, monitorDevice) == 0)
        {
            windowAdapter = dd;
            foundWindow = true;
        }
        if (!foundVendor && glVendorId && RCom_HardwareIdField(dd.DeviceID, "VEN_", nullptr) == glVendorId)
        {
            vendorAdapter = dd;
            foundVendor = true;
        }
        if (!foundPrimary && (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0)
        {
            primary = dd;
            foundPrimary = true;
        }
    }

    if (foundWindow &&
        (!foundVendor || RCom_HardwareIdField(windowAdapter.DeviceID, "VEN_", nullptr) == glVendorId))
        adapter = windowAdapter;
    else if (foundVendor)
        adapter = vendorAdapter;
    else if (foundPrimary)
        adapter = primary;
    else
        return false;
    return true;
}

// DISPLAY_DEVICE.DeviceKey names the adapter's driver key as
// "\Registry\Machine\System\...", so open the rest under HKEY_LOCAL_MACHINE.
static HKEY RCom_OpenAdapterKey(const DISPLAY_DEVICEA &adapter)
{
    static const char kMachinePrefix[] = "\\Registry\\Machine\\";
    const size_t prefixLength = sizeof(kMachinePrefix) - 1;
    if (_strnicmp(adapter.DeviceKey, kMachinePrefix, prefixLength) != 0)
        return nullptr;

    HKEY key = nullptr;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, adapter.DeviceKey + prefixLength, 0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS)
        return nullptr;
    return key;
}

// Reads a REG_SZ, or the first string of a REG_MULTI_SZ.
static bool RCom_ReadRegString(HKEY key, const char *name, std::string &out)
{
    DWORD type = 0;
    DWORD size = 0;
    if (RegQueryValueExA(key, name, nullptr, &type, nullptr, &size) != ERROR_SUCCESS ||
        (type != REG_SZ && type != REG_MULTI_SZ) || size == 0)
        return false;

    std::vector<char> data(size + 2, '\0');
    if (RegQueryValueExA(key, name, nullptr, &type, reinterpret_cast<BYTE *>(data.data()), &size) != ERROR_SUCCESS)
        return false;

    out = data.data();
    return !out.empty();
}

// The adapter memory size the display driver reports to Windows.  Newer
// drivers write a 64-bit qwMemorySize; older ones only a 32-bit MemorySize,
// stored as REG_DWORD or as 4 bytes of REG_BINARY.
static uint64_t RCom_ReadAdapterMemory(HKEY key)
{
    uint64_t qwMemory = 0;
    DWORD size = sizeof(qwMemory);
    if (RegQueryValueExA(key, "HardwareInformation.qwMemorySize", nullptr, nullptr,
                         reinterpret_cast<BYTE *>(&qwMemory), &size) == ERROR_SUCCESS &&
        size == sizeof(qwMemory))
        return qwMemory;

    uint32_t memory = 0;
    size = sizeof(memory);
    if (RegQueryValueExA(key, "HardwareInformation.MemorySize", nullptr, nullptr,
                         reinterpret_cast<BYTE *>(&memory), &size) == ERROR_SUCCESS &&
        size == sizeof(memory))
        return memory;

    return 0;
}

// Needs a current GL context.
static bool RCom_HasGLExtension(const char *name)
{
    GLint count = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS_, &count);
    for (GLint i = 0; i < count; ++i)
    {
        const char *extension = reinterpret_cast<const char *>(glf.GetStringi(GL_EXTENSIONS, static_cast<GLuint>(i)));
        if (extension && std::strcmp(extension, name) == 0)
            return true;
    }
    return false;
}

static void RCom_ListDeviceCaps(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // Stock d3d.ren prints the DirectDraw device identifier, then
    // D3D7 caps that it collected at init.
    // opengl.ren keeps mostly the same lines in the same order, but answers each one
    // for this renderer: from GL where it knows, otherwise from the Windows
    // display adapter and its driver's registry key.
    // 2 stock bugs are not reproduced: its depth lines compare a bitmask
    // w/ '==' thus printing -1, and its memory sizes are 32 bit values
    // printed with %d.
    // Also product, version, subversion, and build are displayed in decimal
    // to match how Windows displays the driver version.
    const unsigned width = g_rs ? g_rs->m_dwWidth : 0u;
    const unsigned height = g_rs ? g_rs->m_dwHeight : 0u;

    // The console runs outside a frame, so borrow the renderer's GL context.
    // The scope also holds the renderer lock, which keeps the window DC and
    // framebuffer alive while they are read.
    RendererContextScope glScope;

    const char *glVendor = nullptr;
    const char *glRenderer = nullptr;
    const char *glVersion = nullptr;
    PIXELFORMATDESCRIPTOR pfd{};
    int colorBits = 0;
    if (glScope)
    {
        glVendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
        glRenderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
        glVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));

        HDC hdc = RendererCore::Instance().DeviceContext();
        const int pixelFormat = hdc ? GetPixelFormat(hdc) : 0;
        if (pixelFormat && DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd))
            colorBits = pfd.cRedBits + pfd.cGreenBits + pfd.cBlueBits + pfd.cAlphaBits;
    }

    DISPLAY_DEVICEA adapter{};
    adapter.cb = sizeof(adapter);
    const bool haveAdapter = RCom_FindAdapter(adapter, RCom_GLVendorId(glVendor));

    std::string driver;
    unsigned driverVersion[4] = {};
    uint64_t adapterMemory = 0;
    if (haveAdapter)
    {
        HKEY key = RCom_OpenAdapterKey(adapter);
        if (key)
        {
            // opengl.ren is 32-bit, so on 64-bit Windows the OpenGL driver
            // (ICD) it loads is the one listed under the Wow value.
            BOOL wow64 = FALSE;
            IsWow64Process(GetCurrentProcess(), &wow64);
            if (RCom_ReadRegString(key, wow64 ? "OpenGLDriverNameWow" : "OpenGLDriverName", driver))
            {
                const size_t slash = driver.find_last_of("\\/");
                if (slash != std::string::npos)
                    driver.erase(0, slash + 1);
            }

            // DriverVersion is formatted like this: "a.b.c.d".
            std::string version;
            if (RCom_ReadRegString(key, "DriverVersion", version))
            {
                const char *part = version.c_str();
                for (unsigned &value : driverVersion)
                {
                    char *end = nullptr;
                    value = static_cast<unsigned>(std::strtoul(part, &end, 10));
                    if (*end != '.')
                        break;
                    part = end + 1;
                }
            }

            adapterMemory = RCom_ReadAdapterMemory(key);
            RegCloseKey(key);
        }
    }

    const char *description = (glRenderer && *glRenderer) ? glRenderer : adapter.DeviceString;

    Console::Instance().Print("---------------------------------------------------------------");
    Console::Instance().Print("Driver: %s", driver.empty() ? "unknown" : driver.c_str());
    Console::Instance().Print("Description: %s", description);
    Console::Instance().Print("OpenGL: %s", glVersion ? glVersion : "unavailable");
    Console::Instance().Print("Product: %u, Version: %u, SubVersion: %u, Build: %u",
                              driverVersion[0], driverVersion[1], driverVersion[2], driverVersion[3]);
    Console::Instance().Print("VendorID: 0x%x, DeviceID: 0x%x, SubSysID: 0x%x, Revision: 0x%x",
                              RCom_HardwareIdField(adapter.DeviceID, "VEN_", "VID_"),
                              RCom_HardwareIdField(adapter.DeviceID, "DEV_", "PID_"),
                              RCom_HardwareIdField(adapter.DeviceID, "SUBSYS_", nullptr),
                              RCom_HardwareIdField(adapter.DeviceID, "REV_", nullptr));
    Console::Instance().Print("Width: %u, Height: %u, BitDepth: %d", width, height, colorBits);
    Console::Instance().Print("---------------------------------------------------------------");

    if (!glScope)
    {
        Console::Instance().Print("opengl.ren: GL caps unavailable (no GL context)");
        return;
    }

    // Depth and stencil of the buffer the scene is rendered into
    // (Framebuffer.cpp), or of the window if that isn't created yet.
    GLint depthBits = pfd.cDepthBits;
    GLint stencilBits = pfd.cStencilBits;
    const GLuint depthStencil = Framebuffer::Instance().DepthStencil();
    if (depthStencil)
    {
        glf.GetNamedRenderbufferParameteriv(depthStencil, GL_RENDERBUFFER_DEPTH_SIZE_, &depthBits);
        glf.GetNamedRenderbufferParameteriv(depthStencil, GL_RENDERBUFFER_STENCIL_SIZE_, &stencilBits);
    }

    GLint maxTextureSize = 0;
    GLint maxFramebufferWidth = 0;
    GLint maxFramebufferHeight = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH_, &maxFramebufferWidth);
    glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT_, &maxFramebufferHeight);

    // GL has no portable memory query.  NVIDIA drivers report it through
    // GL_NVX_gpu_memory_info (in KB); otherwise use the adapter's registry size.
    uint64_t textureMemory = adapterMemory;
    uint64_t videoMemory = adapterMemory;
    if (RCom_HasGLExtension("GL_NVX_gpu_memory_info"))
    {
        GLint totalKb = 0;
        GLint dedicatedKb = 0;
        glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX_, &totalKb);
        glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX_, &dedicatedKb);
        textureMemory = static_cast<uint64_t>(totalKb) * 1024u;
        videoMemory = static_cast<uint64_t>(dedicatedKb) * 1024u;
    }

    // You'll see hardcoded answers, that is because simply by the fact that
    // this OpenGL renderer is running, we know the listed capability is supported.
    // There is nothing to check. If there is a GL context, then we know that the
    // GL driver supports the capability.
    // This is due to some of these capabilities being core GL and implemented in
    // GL in versions older than the version of GL required by this renderer.
    // A lot of these capabilities were optional on GPU hardware during the
    // timeframe of 1999 - 2001, which is why the stock renderer checked for
    // them specifically using the DX7 API.
    // Another reason some answers are hardcoded besides being available in GL
    // is that this renderer implements them in its own code e.g. Fullbrites
    // and lightmaps.

    // Stock: the z-buffer has stencil bits.
    Console::Instance().Print("Portals: %s", stencilBits > 0 ? "Yes" : "No");
    // Models honor MMD_FULL_BRITE (abc_model_renderer.cpp); world and sky
    // surfaces use the DTX_FULLBRITE alpha mask (world.frag.glsl).
    Console::Instance().Print("Model fullbrites: %s, Gouraud fullbrites: %s", "Yes", "Yes");
    // Lightmapped surfaces sample the lightmap atlas
    // (world_lightmap_system.cpp); additive blending is core GL.
    Console::Instance().Print("Lightmap capable: %s, Light add poly: %s", "Yes", "Yes");
    // Pre-transformed (screen-space) vertices are drawn by renderer_2d.cpp.
    Console::Instance().Print("DrawPrim: %s, Dither: %s", "Yes", glIsEnabled(GL_DITHER) ? "Yes" : "No");
    // Blend factors are core GL; texture combining is done in shaders.
    Console::Instance().Print("Src blend SRCCOLOR: %s, Dest blend SRCALPHA: %s", "Yes", "Yes");
    Console::Instance().Print("TBlend Add: %s, TBlend Modulate (gouraud): %s", "Yes", "Yes");
    // GL_LINEAR_MIPMAP_NEAREST is core GL supported.
    Console::Instance().Print("LINEARMIPNEAREST supported: %s", "Yes");
    // Non-power-of-two textures are core GL. The driver places textures in
    // device memory.
    Console::Instance().Print("Square textures only: %s, Vid mem textures: %s", "No", "Yes");
    // System memory textures (D3DDEVCAPS_TEXTURESYSTEMMEMORY) are typically
    // used in software renderers. This is not a software renderer. 'AGP' is a
    // little misleading historical artifact from the stock renderer. What the
    // flag really means is can the GPU store textures in non-local video memory
    // such as locked system RAM? GL cannot query this, but every GPU with a
    // 4.5 driver is PCIe or integrated and Windows allows them all to
    // texture from locked system RAM.
    Console::Instance().Print("System mem textures: %s, AGP mem textures: %s", "No", "Yes");
    Console::Instance().Print("Texture Memory: %llu, Video Memory: %llu",
                              static_cast<unsigned long long>(textureMemory),
                              static_cast<unsigned long long>(videoMemory));
    Console::Instance().Print("ZBuffer Depth: %d, Device Depth: %d", depthBits, colorBits);
    // Z-test is implemented in core GL.
    // Fog is computed per pixel (world.frag.glsl); there is no paletted
    // texture path, every texture is RGBA or DXT.
    // Paletted alpha is an old texture compression technique. OpenGL 4.6 core
    // has no paletted texture format.
    Console::Instance().Print("Z-test: %s, Table fog: %s, Palette alpha: %s", "Yes", "Yes", "No");
    Console::Instance().Print("Max texture size: (%d x %d)", maxTextureSize, maxTextureSize);
    Console::Instance().Print("Surfaces larger than screen: %s",
                              (maxFramebufferWidth > static_cast<GLint>(width) &&
                               maxFramebufferHeight > static_cast<GLint>(height))
                                  ? "Yes"
                                  : "No");
}

static void RCom_FreeTextures(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // The stock d3d renderer frees every uploaded texture: meaning it clears
    // each SharedTexture::m_pRenderData so LithTech re-uploads on next usage.
    // The renderer also lowers RenderStruct::m_dwRendererTextureMem, and
    // releases the surface. It ignores any arguments and prints nothing.
    // In opengl.ren, TextureManager::Term() frees GL textures, but
    // MaterialAuthoringSystem caches texture names borrowed from the
    // TextureManager. So a real port of this command needs that cache
    // and the GUI material previews reset as well.
    // Stubbed until we decide how to handle this.

    // The stock D3D7 renderer does these steps when this is called.
    // The opengl renderer handles all but the first step for the most part in
    // its Term() function.
    // 1. Skips textures with a certain flag set, unless it is forced to,
    // then it frees any dependent textures.
    // 2. Sets LT's SharedTexture::m_pRenderData to NULL. This is the engine's
    // pointer to the renderer's copy of the texture. This sets the stage for
    // the engine to re-upload the texture when it is next drawn.
    // 3. It subtracts the texture's size from the memory counter:
    // RenderStruct::m_dwRendererTextureMem
    // 4. It clears the currently bound texture cache for its 2 texture stages.
    // 5. It releases the D3D surface, which is actual GPU memory.
}

static void RCom_LoadGamma(int argc, char **argv)
{
    if (argc != 2 || !argv || !argv[1] || !*argv[1])
    {
        Console::Instance().Print("Usage: loadgamma <filename>");
        return;
    }

    // Stock renderer reads exactly sizeof(DDGAMMARAMP) (1536 bytes
    // or 256 WORDs each of red, green, blue) from any supplied file in
    // text mode, and hands it to the primary surface's DirectDraw gamma control.
    // It prints nothing regardless of success or failure.
    // opengl.ren has no DirectDraw, so this is stubbed until how to handle this in
    // opengl is decided.
    // For reference, the d3d renderer does this:
    //   pPrimary->QueryInterface(IID_IDirectDrawGammaControl, (void **)&pGammaControl);
    //   pGammaControl->SetGammaRamp(0, &ramp);
    //
    // Likely, the files loaded by this rendercommand were called .gam files.
    // The stock d3d renderer actually loads a hardcoded lithtech.gam file
    // whenever the renderer initializes e.g. game startup, resolution resize,
    // renderer restart. This lithtech.gam file did not ship with the game.
    // That said, this command in the stock renderer will load any file in text mode
    // regardless of a .gam extension or not.
}

static void RCom_PortalFile(int argc, char **argv)
{
    // This shipped as a stub in the stock d3d renderer
    (void)argc;
    (void)argv;
}

static void Renderer_RenderCommand(int argc, char **argv)
{
    if (LogIsSessionEnabled())
    {
        Log("RenderCommand argc=%d", argc);

        for (int i = 0; i < argc; ++i)
            Log("RenderCommand argv[%d]=%s", i, (argv && argv[i]) ? argv[i] : "(null)");
    }

    // lithtech.exe's console dispatcher calls fn(argc-1, argv+1),
    // so the "rendercommand"/"rcom" token is already stripped
    // and argv[0] is always the sub-command. Stock d3d.ren RenderCommand
    // indexes argv the same way, and compares case-insensitively.
    if (argc <= 0 || !argv || !argv[0] || !*argv[0])
        return;

    for (const RenderCommandEntry &entry : kRenderCommands)
    {
        if (_stricmp(argv[0], entry.name) == 0)
        {
            entry.handler(argc, argv);
            return;
        }
    }
}

static void *Renderer_GetDirectDrawInterface(const char *query)
{
    return DirectDrawCompat::Instance().GetInterface(query);
}

static void Renderer_SwapBuffers(uint32 flags)
{
    static bool f10WasDown = false;
    static bool f12WasDown = false;
    static bool ctrl1WasDown = false;
    static bool ctrl2WasDown = false;
    static bool ctrl3WasDown = false;
    static bool ctrl4WasDown = false;
    static bool insertWasDown = false;
    const bool f10Down = (GetAsyncKeyState(VK_F10) & 0x8000) != 0;
    const bool f12Down = (GetAsyncKeyState(VK_F12) & 0x8000) != 0;
    const bool ctrlDown = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
    const bool oneDown = ((GetAsyncKeyState('1') & 0x8000) != 0) ||
                         ((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) != 0);
    const bool twoDown = ((GetAsyncKeyState('2') & 0x8000) != 0) || ((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) != 0);
    const bool threeDown = ((GetAsyncKeyState('3') & 0x8000) != 0) || ((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) != 0);
    const bool fourDown = ((GetAsyncKeyState('4') & 0x8000) != 0) || ((GetAsyncKeyState(VK_NUMPAD4) & 0x8000) != 0);
    const bool ctrl1Down = ctrlDown && oneDown;
    const bool ctrl2Down = ctrlDown && twoDown;
    const bool ctrl3Down = ctrlDown && threeDown;
    const bool ctrl4Down = ctrlDown && fourDown;
    const bool insertDown = (GetAsyncKeyState(VK_INSERT) & 0x8000) != 0;

    if (f10Down && !f10WasDown)
        LogSetSessionEnabled(!LogIsSessionEnabled());
    if (f12Down && !f12WasDown)
    {
        const bool enabled = !RendererCore::Instance().IsPerfOverlayEnabled();
        RendererCore::Instance().SetPerfOverlayEnabled(enabled);
        LOG_SESSION("Renderer F12 perf overlay -> %d", enabled ? 1 : 0);
    }
    if (ctrl1Down && !ctrl1WasDown)
    {
        const bool enabled = !RendererCore::Instance().IsVSyncEnabled();
        RendererCore::Instance().SetVSyncEnabled(enabled);
        LOG_SESSION("Renderer Ctrl+1 VSync toggle -> %d", enabled ? 1 : 0);
    }
    if (ctrl2Down && !ctrl2WasDown)
        GUIQuality::Instance().SetMSAA4xEnabled(!GUIQuality::Instance().IsMSAA4xEnabled());
    if (ctrl3Down && !ctrl3WasDown)
        GUIQuality::Instance().SetSSAOEnabled(!GUIQuality::Instance().IsSSAOEnabled());
    if (ctrl4Down && !ctrl4WasDown)
        GUIQuality::Instance().SetSSREnabled(!GUIQuality::Instance().IsSSREnabled());
    if (insertDown && !insertWasDown)
    {
        GUIQuality::Instance().SetTuningMenuOpen(!GUIQuality::Instance().IsTuningMenuOpen());
        SyncRendererUiSubclass();
    }
    f10WasDown = f10Down;
    f12WasDown = f12Down;
    ctrl1WasDown = ctrl1Down;
    ctrl2WasDown = ctrl2Down;
    ctrl3WasDown = ctrl3Down;
    ctrl4WasDown = ctrl4Down;
    insertWasDown = insertDown;

    // Keep the renderer-owned HWND callback absent unless the tuning UI needs it.
    SyncRendererUiSubclass();
    // Revisit actual engine interfaces after late device setup/QueryInterface,
    // before the next host input poll. Also arm capture on the opening frame.
    if (CaptureGameplayInput())
        RefreshTalonInputDevices();

    LogHotEvent(HotEvent::SwapBuffers);
    LogHotSummaryIfDue();

    // Talon may perform another placement pass after renderer init. In true
    // exclusive fullscreen, keep the host locked to the exclusive monitor.
    if (g_rendererHwnd && !g_rendererWindowed)
        EnsureRendererWindowMode(g_rendererHwnd, false);

    // The game starts with a small bootstrap client and resizes it later. If
    // AVP2 currently has the cursor confined, keep that confinement synced to
    // the live client rectangle. If the game released confinement via
    // ClipCursor(NULL), RefreshCursorClipForWindow intentionally does nothing.
    if (g_rendererHwnd)
        RefreshCursorClipForWindow(g_rendererHwnd);

    GL_SCOPE_VOID();

    // Lock only menu/object-list-only frames to 60 Hzs.  Gameplay frames include a
    // normal world scene and therefore bypass this completely.
    const bool menuOnlyFrame = g_SawMenuObjectScene && !g_SawNormalWorldScene;
    if (menuOnlyFrame)
        LimitMenuPresent60Hz();
    else
    {
        // Re-anchor when leaving a menu so returning later never inherits an
        // old deadline.
        g_MenuLimiterReady = false;
    }

    // Reset classification for the next present.
    g_SawNormalWorldScene = false;
    g_SawMenuObjectScene = false;

    // Fence the FX persistent-stream segment only after all frame draws have
    // been submitted, but before the platform swap. Three segments keep normal
    // frames non-blocking while protecting data still consumed by the GPU.
    const int64_t streamStart = RendererCore::Instance().PerfTimingBegin();
    FXRenderer::Instance().AdvanceStreamFrame();
    ABCModelRenderer::Instance().AdvanceStreamFrame();
    WorldRenderer::Instance().WorldModels().AdvanceStreamFrame();
    WorldRenderer::Instance().Sky().AdvanceStreamFrame();
    WorldSurfaceFxSystem::Instance().AdvanceStreamFrame();
    WorldMaterialSystem::Instance().AdvanceStreamFrame();
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Streaming, streamStart);

    const int64_t presentStart = RendererCore::Instance().PerfTimingBegin();
    RendererPresenter::Instance().SwapBuffers(flags);
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Present, presentStart);
    RendererCore::Instance().PerfFrameComplete();

    avp2::render::GLStateCache::Instance().ResetStats();
    GLUploadStats::Instance().Reset();
    GLUniformStats::Instance().Reset();
    FrameConstants::Instance().ResetStats();
}

static int Renderer_GetInfoFlags() { return 0; }

static void Renderer_GetScreenFormat(PFormat *format)
{
    CallbackTrace trace("GetScreenFormat");
    RendererCore::Instance().GetScreenFormat(format);
    if (format)
        LOG_SESSION("GetScreenFormat type=%d masks A=%08X R=%08X G=%08X B=%08X",
                    static_cast<int>(format->m_eType),
                    format->m_adwMasks[CP_ALPHA], format->m_adwMasks[CP_RED],
                    format->m_adwMasks[CP_GREEN], format->m_adwMasks[CP_BLUE]);
}

static HLTBUFFER Renderer_CreateSurface(int width, int height)
{
    CallbackTrace trace("CreateSurface");
    return reinterpret_cast<HLTBUFFER>(Renderer2D::Instance().CreateSurface(width, height));
}

static void Renderer_DeleteSurface(HLTBUFFER handle)
{
    CallbackTrace trace("DeleteSurface");
    GL_SCOPE_VOID();
    Renderer2D::Instance().DeleteSurface(reinterpret_cast<GLSurface *>(handle));
}

static void Renderer_GetSurfaceInfo(HLTBUFFER handle, uint32 *width, uint32 *height, int *pitch)
{
    auto *s = reinterpret_cast<GLSurface *>(handle);
    if (!s)
        return;
    if (width)
        *width = static_cast<uint32>(s->width);
    if (height)
        *height = static_cast<uint32>(s->height);
    if (pitch)
        *pitch = s->pitch;
}

static void *Renderer_LockSurface(HLTBUFFER handle)
{
    LogHotEvent(HotEvent::LockSurface);
    auto *s = reinterpret_cast<GLSurface *>(handle);
    if (!s || s->locked)
        return nullptr;

    // Surface CPU mappings may be updated concurrently with the threaded
    // loading-screen renderer.  Keep the same renderer ownership lock until
    // UnlockSurface so EnsureTexture can never read pixels mid-write.
    if (!RendererCore::Instance().AcquireThreadContext())
        return nullptr;
    s->locked = true;
    return s->pixels.data();
}

static void Renderer_UnlockSurface(HLTBUFFER handle)
{
    LogHotEvent(HotEvent::UnlockSurface);
    auto *s = reinterpret_cast<GLSurface *>(handle);
    if (!s || !s->locked)
        return;
    s->locked = false;
    s->dirty = true;
    RendererCore::Instance().ReleaseThreadContext();
}

static LTBOOL Renderer_OptimizeSurface(HLTBUFFER handle, GenericColor transparent)
{
    GL_SCOPE_RET(LTFALSE);
    auto *s = reinterpret_cast<GLSurface *>(handle);
    if (!s)
        return LTFALSE;

    // AVP2 can call OptimizeSurface repeatedly for an already-optimized
    // surface without changing either its pixels or transparent color.
    // The old OpenGL path forced s->dirty=true on every call, which caused
    // EnsureTexture() to rebuild the alpha-keyed CPU copy and issue a full
    // TextureSubImage2D even though the resulting texture was identical.
    //
    // Preserve stock semantics when anything materially changed:
    //   * first optimization
    //   * transparent-key change
    //   * CPU pixel update (UnlockSurface already leaves s->dirty=true)
    // Otherwise this is a true no-op.
    const uint32 nextTransparent = transparent.dwVal;
    const bool optimizationChanged = !s->optimized || s->transparentColor != nextTransparent;

    s->optimized = true;
    s->transparentColor = nextTransparent;
    if (optimizationChanged)
        s->dirty = true;

    // EnsureTexture still handles a genuinely dirty surface, so callers that
    // changed pixels immediately before OptimizeSurface retain the same result.
    Renderer2D::Instance().EnsureTexture(s);

    if (optimizationChanged && LogIsSessionEnabled())
        LOG_SESSION("OptimizeSurface changed surf=%p transparent=%08X", s, nextTransparent);
    return LTTRUE;
}

static void Renderer_UnoptimizeSurface(HLTBUFFER handle)
{
    auto *s = reinterpret_cast<GLSurface *>(handle);
    if (!s)
        return;
    s->optimized = false;
    s->transparentColor = 0xFFFFFFFFu;
    LOG_SESSION("UnoptimizeSurface %p", s);
}

static LTBOOL Renderer_LockScreen(int l, int t, int r, int b, void **data, int *pitch)
{
    // Like Start3D, keep ownership until the matching UnlockScreen.  The stock
    // D3D renderer maps the actual backbuffer for this interval, so allowing a
    // second thread to render into it while the CPU pointer is live would be a
    // semantic and data race.
    if (!RendererCore::Instance().AcquireThreadContext())
        return LTFALSE;
    const bool ok = RendererPresenter::Instance().LockScreen(l, t, r, b, data, pitch);
    if (!ok)
        RendererCore::Instance().ReleaseThreadContext();
    else
        ++g_rendererScreenContextHolds;
    return ok ? LTTRUE : LTFALSE;
}

static void Renderer_UnlockScreen()
{
    const bool matchingLock = g_rendererScreenContextHolds > 0;
    bool temporaryOwnership = false;
    if (!matchingLock)
    {
        if (!RendererCore::Instance().AcquireThreadContext())
            return;
        temporaryOwnership = true;
    }
    RendererPresenter::Instance().UnlockScreen();
    if (matchingLock)
    {
        --g_rendererScreenContextHolds;
        RendererCore::Instance().ReleaseThreadContext();
    }
    else if (temporaryOwnership)
    {
        RendererCore::Instance().ReleaseThreadContext();
    }
}

static void Renderer_BlitToScreen(BlitRequest *request)
{
    GL_SCOPE_VOID();
    LogHotEvent(HotEvent::BlitToScreen);
    RendererPresenter::Instance().BlitToScreen(request);
}

static LTBOOL Renderer_WarpToScreen(BlitRequest *request)
{
    GL_SCOPE_RET(LTFALSE);
    return RendererPresenter::Instance().WarpToScreen(request) ? LTTRUE : LTFALSE;
}

static void Renderer_MakeScreenShot(const char *filename)
{
    LOG_SESSION("MakeScreenShot not implemented yet: %s", filename ? filename : "<null>");
}

static void Renderer_ReadConsoleVariables()
{
    RefreshFogStateFromConsole();
    FXRenderer::Instance().ReadConsoleVariables();
}

static void Renderer_BlitFromScreen(BlitRequest *request)
{
    GL_SCOPE_VOID();
    RendererPresenter::Instance().BlitFromScreen(request);
}

extern "C" RMode *rdll_GetSupportedModes()
{
    LOG_SESSION("GetSupportedModes");

    const bool launcherProcess = IsAVP2LauncherProcess();

    // AVP2.exe is the display-settings launcher.  Remove its exact-4:3 mode
    // filter before returning our full Windows mode list.  In lithtech.exe
    // this is a no-op by process-name guard.
    PatchAVP2AspectRatioModeFilter();

    if (launcherProcess)
    {
        struct DisplayTarget
        {
            std::string deviceName;
            std::string description;
            bool primary = false;
        };

        std::vector<DisplayTarget> displays;
        for (DWORD adapterIndex = 0;; ++adapterIndex)
        {
            DISPLAY_DEVICEA dd{};
            dd.cb = sizeof(dd);
            if (!EnumDisplayDevicesA(nullptr, adapterIndex, &dd, 0))
                break;

            if ((dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) == 0)
                continue;
            if ((dd.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) != 0)
                continue;
            if (!dd.DeviceName[0])
                continue;

            DisplayTarget d{};
            d.deviceName = dd.DeviceName;
            d.primary = (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0;
            d.description = dd.DeviceString[0] ? dd.DeviceString : "Display Adapter";
            displays.push_back(std::move(d));

            LOG_SESSION("Launcher display[%lu] device='%s' gpu='%s' primary=%d flags=0x%08lX",
                        static_cast<unsigned long>(adapterIndex), dd.DeviceName, d.description.c_str(),
                        d.primary ? 1 : 0, static_cast<unsigned long>(dd.StateFlags));
        }

        std::stable_sort(displays.begin(), displays.end(), [](const DisplayTarget &a, const DisplayTarget &b)
                         {
            if (a.primary != b.primary)
                return a.primary && !b.primary;
            return a.deviceName < b.deviceName; });

        std::set<std::tuple<std::string, DWORD, DWORD, DWORD>> unique;
        RMode *head = nullptr;
        RMode *tail = nullptr;
        size_t modeCount = 0;

        auto appendMode = [&](const char *deviceName, const char *description,
                              DWORD width, DWORD height, DWORD bpp)
        {
            const std::string dev = deviceName ? deviceName : "display";
            auto key = std::make_tuple(dev, width, height, 32u);
            if (!unique.insert(key).second)
                return;

            auto *mode = new RMode{};
            mode->m_bHardware = LTTRUE;
            strncpy_s(mode->m_szRenderDLL, "opengl.ren", _TRUNCATE);
            // Important: the launcher uses internalName to group/select each
            // display, but lithtech.exe must not see this ABI.  We therefore
            // expose per-display internal names only in AVP2.exe.
            strncpy_s(mode->m_szInternalName, dev.c_str(), _TRUNCATE);
            strncpy_s(mode->m_szDescription,
                      (description && description[0]) ? description : "Primary Display Driver", _TRUNCATE);
            mode->m_dwWidth = width;
            mode->m_dwHeight = height;
            mode->m_dwBitDepth = 32;
            mode->m_pNext = nullptr;

            if (!head)
                head = mode;
            else
                tail->m_pNext = mode;
            tail = mode;
            ++modeCount;
        };

        for (const DisplayTarget &display : displays)
        {
            DEVMODEA dm{};
            dm.dmSize = sizeof(dm);
            size_t displayModeCount = 0;

            for (DWORD modeIndex = 0;
                 EnumDisplaySettingsExA(display.deviceName.c_str(), modeIndex, &dm, 0);
                 ++modeIndex)
            {
                if (dm.dmBitsPerPel < 32 || dm.dmPelsWidth < 640 || dm.dmPelsHeight < 480)
                {
                    dm = DEVMODEA{};
                    dm.dmSize = sizeof(dm);
                    continue;
                }

                const size_t before = modeCount;
                appendMode(display.deviceName.c_str(), display.description.c_str(),
                           dm.dmPelsWidth, dm.dmPelsHeight, 32);
                if (modeCount != before)
                    ++displayModeCount;

                dm = DEVMODEA{};
                dm.dmSize = sizeof(dm);
            }

            LOG_SESSION("Launcher display modes device='%s' -> %zu unique 32bpp modes",
                        display.deviceName.c_str(), displayModeCount);
        }

        if (!head)
        {
            DEVMODEA dm{};
            dm.dmSize = sizeof(dm);
            for (DWORD i = 0; EnumDisplaySettingsA(nullptr, i, &dm); ++i)
            {
                if (dm.dmBitsPerPel >= 32 && dm.dmPelsWidth >= 640 && dm.dmPelsHeight >= 480)
                    appendMode("display", "Primary Display Driver", dm.dmPelsWidth, dm.dmPelsHeight, 32);
                dm = DEVMODEA{};
                dm.dmSize = sizeof(dm);
            }
        }

        if (!head)
        {
            appendMode("display", "Primary Display Driver", 640, 480, 32);
            appendMode("display", "Primary Display Driver", 800, 600, 32);
            appendMode("display", "Primary Display Driver", 1024, 768, 32);
        }

        LOG_SESSION("GetSupportedModes -> %zu modes across %zu launcher displays", modeCount, displays.size());
        return head;
    }

    std::set<std::tuple<DWORD, DWORD, DWORD>> unique;
    std::vector<std::tuple<DWORD, DWORD, DWORD>> modes;

    DEVMODEA dm{};
    dm.dmSize = sizeof(dm);

    for (DWORD i = 0; EnumDisplaySettingsA(nullptr, i, &dm); ++i)
    {
        if (dm.dmBitsPerPel < 32 || dm.dmPelsWidth < 640 || dm.dmPelsHeight < 480)
            continue;

        auto key = std::make_tuple(dm.dmPelsWidth, dm.dmPelsHeight, 32u);
        if (unique.insert(key).second)
            modes.push_back(key);
    }

    if (modes.empty())
    {
        modes.emplace_back(640, 480, 32);
        modes.emplace_back(800, 600, 32);
        modes.emplace_back(1024, 768, 32);
    }

    RMode *head = nullptr;
    RMode *tail = nullptr;

    for (const auto &m : modes)
    {
        auto *mode = new RMode{};
        mode->m_bHardware = LTTRUE;
        strncpy_s(mode->m_szRenderDLL, "opengl.ren", _TRUNCATE);
        strncpy_s(mode->m_szInternalName, "OpenGL46", _TRUNCATE);
        strncpy_s(mode->m_szDescription, "AVP2 OpenGL 4.6 Core", _TRUNCATE);
        mode->m_dwWidth = std::get<0>(m);
        mode->m_dwHeight = std::get<1>(m);
        mode->m_dwBitDepth = 32;
        mode->m_pNext = nullptr;

        if (!head)
            head = mode;
        else
            tail->m_pNext = mode;
        tail = mode;
    }

    LOG_SESSION("GetSupportedModes -> %zu stable game modes", modes.size());
    return head;
}

extern "C" void rdll_FreeModeList(RMode *modes)
{
    LOG_SESSION("FreeModeList");
    while (modes)
    {
        RMode *next = modes->m_pNext;
        delete modes;
        modes = next;
    }
}

extern "C" void rdll_RenderDLLSetup(RenderStruct *rs)
{
    CallbackTrace trace("RenderDLLSetup");
    g_rs = rs;
    Console::Instance().SetRenderStruct(rs);
    TextureManager::Instance().SetRenderStruct(rs);
    SceneRenderer::Instance().SetRenderStruct(rs);
    FXRenderer::Instance().SetRenderStruct(rs);
    WorldRenderer::Instance().SetRenderStruct(rs);
    LOG_SESSION("RenderDLLSetup RenderStruct=%p", rs);

    if (!rs)
        return;

    rs->Init = Renderer_Init;
    rs->Term = Renderer_Term;

    rs->BindTexture = Renderer_BindTexture;
    rs->UnbindTexture = Renderer_UnbindTexture;
    rs->RebindLightmaps = Renderer_RebindLightmaps;

    rs->CreateContext = Renderer_CreateContext;
    rs->DeleteContext = Renderer_DeleteContext;

    rs->Clear = Renderer_Clear;

    rs->Start3D = Renderer_Start3D;
    rs->End3D = Renderer_End3D;
    rs->IsIn3D = Renderer_IsIn3D;

    rs->StartOptimized2D = Renderer_StartOptimized2D;
    rs->EndOptimized2D = Renderer_EndOptimized2D;
    rs->IsInOptimized2D = Renderer_IsInOptimized2D;

    rs->SetOptimized2DBlend = Renderer_SetOptimized2DBlend;
    rs->GetOptimized2DBlend = Renderer_GetOptimized2DBlend;
    rs->SetOptimized2DColor = Renderer_SetOptimized2DColor;
    rs->GetOptimized2DColor = Renderer_GetOptimized2DColor;

    rs->RenderScene = Renderer_RenderScene;
    rs->RenderCommand = Renderer_RenderCommand;
    rs->GetDirectDrawInterface = Renderer_GetDirectDrawInterface;

    rs->SwapBuffers = Renderer_SwapBuffers;
    rs->GetInfoFlags = Renderer_GetInfoFlags;
    rs->GetScreenFormat = Renderer_GetScreenFormat;

    rs->CreateSurface = Renderer_CreateSurface;
    rs->DeleteSurface = Renderer_DeleteSurface;
    rs->GetSurfaceInfo = Renderer_GetSurfaceInfo;
    rs->LockSurface = Renderer_LockSurface;
    rs->UnlockSurface = Renderer_UnlockSurface;
    rs->OptimizeSurface = Renderer_OptimizeSurface;
    rs->UnoptimizeSurface = Renderer_UnoptimizeSurface;

    rs->LockScreen = Renderer_LockScreen;
    rs->UnlockScreen = Renderer_UnlockScreen;
    rs->BlitToScreen = Renderer_BlitToScreen;
    rs->WarpToScreen = Renderer_WarpToScreen;
    rs->MakeScreenShot = Renderer_MakeScreenShot;
    rs->ReadConsoleVariables = Renderer_ReadConsoleVariables;
    rs->BlitFromScreen = Renderer_BlitFromScreen;
}
