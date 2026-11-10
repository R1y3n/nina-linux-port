#pragma once

#include <windows.h>

class OpenGLOptionsMenu final
{
public:
    static OpenGLOptionsMenu &Instance();

    bool InstallCShellHooks();
    void RemoveCShellHooks();

    // Opens the real CSHELL-backed folder object.
    void Open();
    void Close();
    bool IsOpen() const { return m_open; }

    // Deferred native control rebuild after a toggle so we never destroy the
    // currently-dispatching LTGUI control from inside OnCommand.
    void Tick();

    // Internal CSHELL callbacks used by the reconstructed folder vtable.
    bool EnsureNativeFolder(void *displayFolder);
    bool BuildNativeFolder(void *folder);
    int HandleNativeCommand(void *folder, unsigned command, unsigned param1, unsigned param2);
    void HandleNativeFocus(void *folder, int focus);
    void *GetNativeHelpString(unsigned helpId, int controlIndex);

    // Source-parity CBaseFolder::SetTab(int): selects an existing native tab
    // and rebuilds that tab's free controls using the stock folder workflow.
    void SetTab(int tab);

private:
    OpenGLOptionsMenu() = default;
    void SwitchTab(int tab);
    void BuildCurrentTabControls();

    bool m_open = false;
    int m_currentTab = 0;
    int m_parentFolderId = 0;
    HMODULE m_cshell = nullptr;
    void **m_displayVtable = nullptr;
    void *m_originalBuild = nullptr;
    void *m_originalOnCommand = nullptr;
    void *m_nativeFolder = nullptr;
    void *m_folderMgr = nullptr;

    // Bound directly to the stock LTGUI toggle controls.
    int m_ssaoValue = 0;
    int m_ssrValue = 0;
    int m_msaaValue = 0;
    int m_lastSSAO = 0;
    int m_lastSSR = 0;
    int m_lastMSAA = 0;
    int m_bloomValue = 0;
    int m_dynamicExposureValue = 0;
    int m_anisotropicValue = 0;
    int m_highQualityLightGridValue = 0;
    int m_lastBloom = 0;
    int m_lastDynamicExposure = 0;
    int m_lastAnisotropic = 0;
    int m_lastHighQualityLightGrid = 0;
    int m_vsyncValue = 0;
    int m_lastVSync = 0;
    int m_debugOverlayValue = 0;
    int m_lastDebugOverlay = 0;
    void *m_generalTab = nullptr;
    void *m_graphicsTab = nullptr;
    void *m_ssaoCtrl = nullptr;
    void *m_ssrCtrl = nullptr;
    void *m_msaaCtrl = nullptr;
    void *m_bloomCtrl = nullptr;
    void *m_dynamicExposureCtrl = nullptr;
    void *m_anisotropicCtrl = nullptr;
    void *m_highQualityLightGridCtrl = nullptr;
    void *m_vsyncCtrl = nullptr;
    void *m_debugOverlayCtrl = nullptr;
};
