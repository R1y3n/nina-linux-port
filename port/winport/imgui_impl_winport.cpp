#include "backends/imgui_impl_win32.h"
#include <time.h>
static HWND g_hwnd; static double g_last;
static double NowSec() { timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec + t.tv_nsec * 1e-9; }
struct KeyMap { int vk; ImGuiKey key; };
static const KeyMap kKeys[] = {
    {VK_TAB, ImGuiKey_Tab}, {VK_LEFT, ImGuiKey_LeftArrow}, {VK_RIGHT, ImGuiKey_RightArrow}, {VK_UP, ImGuiKey_UpArrow}, {VK_DOWN, ImGuiKey_DownArrow},
    {VK_PRIOR, ImGuiKey_PageUp}, {VK_NEXT, ImGuiKey_PageDown}, {VK_HOME, ImGuiKey_Home}, {VK_END, ImGuiKey_End}, {VK_INSERT, ImGuiKey_Insert},
    {VK_DELETE, ImGuiKey_Delete}, {VK_BACK, ImGuiKey_Backspace}, {VK_SPACE, ImGuiKey_Space}, {VK_RETURN, ImGuiKey_Enter}, {VK_ESCAPE, ImGuiKey_Escape},
    {VK_F1, ImGuiKey_F1}, {VK_F2, ImGuiKey_F2}, {VK_F3, ImGuiKey_F3}, {VK_F4, ImGuiKey_F4}, {VK_F5, ImGuiKey_F5}, {VK_F6, ImGuiKey_F6},
    {VK_F7, ImGuiKey_F7}, {VK_F8, ImGuiKey_F8}, {VK_F9, ImGuiKey_F9}, {VK_F10, ImGuiKey_F10}, {VK_F11, ImGuiKey_F11}, {VK_F12, ImGuiKey_F12},
    {'A', ImGuiKey_A}, {'C', ImGuiKey_C}, {'V', ImGuiKey_V}, {'X', ImGuiKey_X}, {'Y', ImGuiKey_Y}, {'Z', ImGuiKey_Z}};
bool ImGui_ImplWin32_Init(void *hwnd)
{
    g_hwnd = (HWND)hwnd; g_last = NowSec();
    ImGuiIO &io = ImGui::GetIO(); io.BackendPlatformName = "imgui_impl_winport (native linux)"; io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    return g_hwnd != nullptr;
}
void ImGui_ImplWin32_Shutdown() { g_hwnd = nullptr; }
void ImGui_ImplWin32_NewFrame()
{
    ImGuiIO &io = ImGui::GetIO(); RECT rc{}; GetClientRect(g_hwnd, &rc);
    io.DisplaySize = ImVec2((float)(rc.right - rc.left), (float)(rc.bottom - rc.top));
    const double now = NowSec(); io.DeltaTime = (float)(now - g_last > 0 ? now - g_last : 1.0 / 60.0); g_last = now;
    POINT p{}; if (GetCursorPos(&p) && ScreenToClient(g_hwnd, &p)) io.AddMousePosEvent((float)p.x, (float)p.y);
    io.AddMouseButtonEvent(0, (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0); io.AddMouseButtonEvent(1, (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0);
    io.AddMouseButtonEvent(2, (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0);
    for (const KeyMap &k : kKeys) io.AddKeyEvent(k.key, (GetAsyncKeyState(k.vk) & 0x8000) != 0);
    io.AddKeyEvent(ImGuiMod_Ctrl, (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0); io.AddKeyEvent(ImGuiMod_Shift, (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0);
    io.AddKeyEvent(ImGuiMod_Alt, (GetAsyncKeyState(VK_MENU) & 0x8000) != 0);
}
LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT msg, WPARAM wp, LPARAM)
{
    if (!ImGui::GetCurrentContext()) return 0; ImGuiIO &io = ImGui::GetIO();
    if (msg == WM_CHAR) { if (wp > 0 && wp < 0x10000) io.AddInputCharacter((unsigned)wp); }
    else if (msg == WM_MOUSEWHEEL) io.AddMouseWheelEvent(0.0f, (float)GET_WHEEL_DELTA_WPARAM(wp) / 120.0f);
    else if (msg == WM_MOUSEHWHEEL) io.AddMouseWheelEvent((float)GET_WHEEL_DELTA_WPARAM(wp) / 120.0f, 0.0f);
    return 0;
}
