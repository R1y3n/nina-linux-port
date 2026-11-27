#pragma once
/* Native Linux platform backend for Dear ImGui, driven by the same host window/input APIs the renderer uses (winport). */
#include "imgui.h"
#include <windows.h>
IMGUI_IMPL_API bool ImGui_ImplWin32_Init(void *hwnd);
IMGUI_IMPL_API void ImGui_ImplWin32_Shutdown();
IMGUI_IMPL_API void ImGui_ImplWin32_NewFrame();
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
