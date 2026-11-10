#pragma once

#include <windows.h>
#include <cstdint>

namespace MSPCompatibility
{
    // Mirrors MSP's pre-SetRenderMode policy for the canonical original AVP2
    // CSHELL. MSP forcibly selects 32-bit mode and writes +32BitTextures 1
    // before asking LithTech to initialize the renderer. Call this at the very
    // beginning of Renderer_Init, before any GL/texture/world initialization.
    void PrepareRenderMode(uint32_t &bitDepth);

    // Installs the subset of AVP2 MSP engine/window compatibility behavior that
    // has been positively identified and can be reproduced safely when the
    // canonical original AVP2 CSHELL is loaded.
    bool Install(HWND hwnd, bool windowed, int clientWidth, int clientHeight);

    // Re-applies window policy after renderer/window mode changes.  Safe to call
    // repeatedly; engine-code patches remain one-shot/reversible through
    // HookManager.
    void RefreshWindow(HWND hwnd, bool windowed, int clientWidth, int clientHeight);

    void Remove();
    bool IsInstalled();
}
