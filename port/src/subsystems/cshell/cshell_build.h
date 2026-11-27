#pragma once

#include <windows.h>
#include <cstddef>
#include <cstdint>

namespace CShell
{
    enum class Build
    {
        Unknown = 0,
        AVP2Original,
        AVP2MSP,
        AVP2Coop
    };

    struct Profile
    {
        Build build;
        const char *name;
        const char *sha256;

        uintptr_t folderDisplayVtableRva;
        uintptr_t folderDisplayBuildRva;
        uintptr_t folderDisplayOnCommandRva;
        uintptr_t baseFolderAddTextLiteralRva;
        uintptr_t baseFolderSetTitleHStringRva;
        uintptr_t baseFolderCreateToggleHStringRva;
        uintptr_t baseFolderAddFreeControlRva;
        uintptr_t baseFolderAddTabRva;
        uintptr_t baseFolderRemoveFreeRva;
        uintptr_t baseFolderGetHelpStringRva;
        uintptr_t baseFolderUpdateDataRva;
        uintptr_t baseFolderVtableRva;
        uintptr_t layoutGetCustomRectRva;
        uintptr_t layoutGetCustomIntRva;
        uintptr_t layoutGetCustomPointRva;
        uintptr_t toggleSetOnStringIdRva;
        uintptr_t toggleSetOffStringIdRva;
        uintptr_t baseFolderAddControlRva;
        uintptr_t baseFolderGetMenuFontRva;
        uintptr_t baseFolderGetLargeFontRva;
        uintptr_t baseFolderGetHelpFontRva;
        uintptr_t baseFolderBuildRva;
        uintptr_t baseFolderOnCommandRva;
        uintptr_t baseFolderTermRva;
        uintptr_t baseFolderOnFocusRva;
        uintptr_t folderMgrSetCurrentRva;
        uintptr_t folderMgrShowFolderRva;
        uintptr_t folderPerformanceCtorRva;
        uintptr_t operatorNewRva;
        uintptr_t folderPerformanceVtableRva;
        uintptr_t ltClientGlobalRva;
        uintptr_t layoutMgrGlobalRva;

        std::size_t folderPerformanceSize;
        std::size_t baseFolderNumTabsOffset;
        std::size_t baseFolderCurTabOffset;
        std::size_t baseFolderPageRectOffset;
    };

    // Detects the currently loaded CSHELL.DLL and selects an exact SHA-256 profile.
    // AVP2 MSP and AVP2 Original are identified by exact SHA-256. MSP also has
    // a strict structural fallback for diagnostics if a modified MSP DLL is used.
    // A recognized build may still be feature-disabled until its RVAs are mapped.
    bool Detect();
    void Reset();
    bool IsSupported();
    bool IsHashVerified();
    HMODULE Module();
    uintptr_t Base();
    Build CurrentBuild();
    const Profile *CurrentProfile();
    const char *BuildName();
    const char *SHA256();
}
