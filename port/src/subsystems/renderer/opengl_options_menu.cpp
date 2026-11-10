#include "opengl_options_menu.h"
#include "../memory/hook_manager.h"
#include "../cshell/cshell_build.h"
#include "gui_quality.h"
#include "renderer_core.h"
#include "../textures/texture_manager.h"
#include "../world/world_renderer.h"
#include "utils/log.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <new>

namespace
{
    constexpr uint32_t kCmdOpenGLOptions = 0x42u;
    constexpr uint32_t kCmdGeneral = 0x70u;
    constexpr uint32_t kCmdGraphics = 0x71u;

    constexpr uint32_t kHelpGeneral = 0x7F10u;
    constexpr uint32_t kHelpGraphics = 0x7F11u;
    constexpr uint32_t kHelpMSAA = 0x7F12u;
    constexpr uint32_t kHelpSSAO = 0x7F13u;
    constexpr uint32_t kHelpSSR = 0x7F14u;
    constexpr uint32_t kHelpVSync = 0x7F15u;
    constexpr uint32_t kHelpDebugOverlay = 0x7F16u;
    constexpr uint32_t kHelpBloom = 0x7F17u;
    constexpr uint32_t kHelpDynamicExposure = 0x7F18u;
    constexpr uint32_t kHelpAnisotropic = 0x7F19u;
    constexpr uint32_t kHelpHighQualityLightGrid = 0x7F1Au;

    constexpr int kIdsOn = 24;
    constexpr int kIdsOff = 25;
    constexpr int kIdsPerformGeneral = 89;
    constexpr int kIdsGraphics = 18;
    constexpr int kSyntheticFolderId = 0x0Au;
    constexpr size_t kVtableEntries = 41u;

    struct LTPointCompat
    {
        int x;
        int y;
    };
    struct LTRectCompat
    {
        int left;
        int top;
        int right;
        int bottom;
    };

    using FolderBuildFn = int(__thiscall *)(void *self);
    using FolderOnCommandFn = int(__thiscall *)(void *self, uint32_t command, uint32_t param1, uint32_t param2);
    using FolderInitFn = void(__thiscall *)(void *self, int folderId);
    using FolderTermFn = void(__thiscall *)(void *self);
    using FolderFocusFn = void(__thiscall *)(void *self, int focus);
    using FolderCtorFn = void *(__thiscall *)(void *self);
    using GetMenuFontFn = void *(__cdecl *)();
    using AddTextLiteralFn = void *(__thiscall *)(void *self, const char *text, uint32_t command, uint32_t helpId, int fixed, void *font, int extra);
    using AddControlFn = int(__thiscall *)(void *self, void *ctrl, int group, int x, int y, int selectable);
    using FolderMgrSetFn = void(__thiscall *)(void *mgr, void *folder, int back);
    using FolderMgrShowFn = int(__thiscall *)(void *mgr, int folderId);
    using SetTitleHStringFn = int(__thiscall *)(void *self, void *hString);
    // Exact retail CreateToggle(HSTRING, helpId, rightColumnOffset, value, fixed, font).
    // Important: CSHELL+0x6A50 is NOT AddToggle -- it is a seven-argument control
    // helper (slider/cycle family).  The real six-argument toggle path used by
    // CFolderPerformance is +0x6A10 for resource IDs, which routes into the
    // HSTRING CreateToggle implementation at +0x4480.  We call +0x4480 directly
    // for our literal labels, then register the result with AddFreeControl.
    using CreateToggleHStringFn = void *(__thiscall *)(void *self, void *hString, int helpId, int rightColumnOffset, int *value, int fixed, void *font);
    using AddFreeControlFn = void(__thiscall *)(void *self, void *ctrl);
    using AddTabFn = void *(__thiscall *)(void *self, int stringId, uint32_t commandId, int helpId);
    using RemoveFreeFn = void(__thiscall *)(void *self);
    using GetHelpStringFn = void *(__thiscall *)(void *self, uint32_t helpId, int controlIndex);
    using LayoutGetRectFn = LTRectCompat *(__thiscall *)(void *self, LTRectCompat *out, int folderId, const char *key);
    using LayoutGetIntFn = int(__thiscall *)(void *self, int folderId, const char *key);
    using LayoutGetPointFn = LTPointCompat *(__thiscall *)(void *self, LTPointCompat *out, int folderId, const char *key);
    using ToggleSetStringIdFn = void(__thiscall *)(void *self, int stringId);
    using FolderNavFn = int(__thiscall *)(void *self);
    using FolderMouseFn = int(__thiscall *)(void *self, int x, int y);
    using FolderUpdateDataFn = void(__thiscall *)(void *self, int saveAndValidate);

    static FolderBuildFn g_originalDisplayBuild = nullptr;
    static FolderOnCommandFn g_originalDisplayCommand = nullptr;
    static GetMenuFontFn g_getMenuFont = nullptr;
    static AddTextLiteralFn g_addTextLiteral = nullptr;
    static AddControlFn g_addControl = nullptr;
    static FolderBuildFn g_baseBuild = nullptr;
    static FolderOnCommandFn g_baseCommand = nullptr;
    static FolderTermFn g_baseTerm = nullptr;
    static FolderFocusFn g_baseOnFocus = nullptr;
    static FolderMgrSetFn g_mgrSetCurrent = nullptr;
    static FolderMgrShowFn g_mgrShowFolder = nullptr;
    static FolderCtorFn g_perfCtor = nullptr;
    static SetTitleHStringFn g_setTitleHString = nullptr;
    static CreateToggleHStringFn g_createToggleHString = nullptr;
    static AddFreeControlFn g_addFreeControl = nullptr;
    static AddTabFn g_addTab = nullptr;
    static RemoveFreeFn g_removeFree = nullptr;
    static GetHelpStringFn g_baseGetHelpString = nullptr;
    static LayoutGetRectFn g_layoutGetRect = nullptr;
    static LayoutGetIntFn g_layoutGetInt = nullptr;
    static LayoutGetPointFn g_layoutGetPoint = nullptr;
    static ToggleSetStringIdFn g_toggleSetOnStringId = nullptr;
    static ToggleSetStringIdFn g_toggleSetOffStringId = nullptr;
    static FolderNavFn g_baseOnLeft = nullptr;
    static FolderNavFn g_baseOnRight = nullptr;
    static FolderMouseFn g_baseOnLButtonUp = nullptr;
    static FolderMouseFn g_baseOnRButtonUp = nullptr;
    static FolderUpdateDataFn g_updateData = nullptr;
    using CShellNewFn = void *(__cdecl *)(size_t);
    static CShellNewFn g_cshellNew = nullptr;
    static std::array<void *, kVtableEntries> g_nativeVtable{};

    static void *GetLTClient()
    {
        if (!OpenGLOptionsMenu::Instance().IsOpen())
        { /* no-op: allows use during Build */
        }
        const auto *profile = CShell::CurrentProfile();
        HMODULE cshell = CShell::Module();
        if (!profile || !cshell)
            return nullptr;
        return *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(cshell) + profile->ltClientGlobalRva);
    }

    static void *CreateLiteralHString(const char *text)
    {
        void *ltClient = GetLTClient();
        if (!ltClient || !text)
            return nullptr;
        void **vt = *reinterpret_cast<void ***>(ltClient);
        using Fn = void *(__thiscall *)(void *, const char *);
        auto fn = reinterpret_cast<Fn>(vt[0xB8u / 4u]);
        return fn ? fn(ltClient, text) : nullptr;
    }

    static void FreeHString(void *hs)
    {
        void *ltClient = GetLTClient();
        if (!ltClient || !hs)
            return;
        void **vt = *reinterpret_cast<void ***>(ltClient);
        using Fn = void(__thiscall *)(void *, void *);
        auto fn = reinterpret_cast<Fn>(vt[0xBCu / 4u]);
        if (fn)
            fn(ltClient, hs);
    }

    static void SetCtrlEnabled(void *ctrl, bool enabled)
    {
        if (!ctrl)
            return;
        void **vt = *reinterpret_cast<void ***>(ctrl);
        using Fn = void(__thiscall *)(void *, int);
        auto fn = reinterpret_cast<Fn>(vt[0x5Cu / 4u]);
        if (fn)
            fn(ctrl, enabled ? 1 : 0);
    }

    // Exact source semantics of CBaseFolder::SetTab(int n):
    //     if (n >= 0 && n < m_nNumTabs) m_nCurTab = n;
    // It is inline in BaseFolder.h, therefore retail CSHELL has no SetTab symbol
    // to call.  CFolderPerformance::OnCommand performs the same +0xDC/+0xE0
    // accesses directly (e.g. 0x12024941..0x12024952 for tab 0).
    static bool SetFolderTab(void *folder, int n)
    {
        const auto *profile = CShell::CurrentProfile();
        if (!folder || !profile || n < 0)
            return false;
        auto *fb = reinterpret_cast<unsigned char *>(folder);
        const int numTabs = *reinterpret_cast<const int *>(fb + profile->baseFolderNumTabsOffset);
        if (n >= numTabs)
            return false;
        *reinterpret_cast<int *>(fb + profile->baseFolderCurTabOffset) = n;
        return true;
    }

    static int GetFolderTab(void *folder)
    {
        const auto *profile = CShell::CurrentProfile();
        if (!folder || !profile)
            return -1;
        return *reinterpret_cast<const int *>(reinterpret_cast<unsigned char *>(folder) + profile->baseFolderCurTabOffset);
    }

    static void SetToggleOnOff(void *ctrl)
    {
        if (!ctrl)
            return;
        if (g_toggleSetOnStringId)
            g_toggleSetOnStringId(ctrl, kIdsOn);
        if (g_toggleSetOffStringId)
            g_toggleSetOffStringId(ctrl, kIdsOff);
    }

    static void SetPerformancePageRect(void *folder)
    {
        if (!folder || !g_layoutGetRect)
            return;
        const auto *profile = CShell::CurrentProfile();
        HMODULE cshell = CShell::Module();
        if (!profile || !cshell)
            return;
        auto *base = reinterpret_cast<unsigned char *>(cshell);
        void *layout = *reinterpret_cast<void **>(base + profile->layoutMgrGlobalRva);
        if (!layout)
            return;
        LTRectCompat rc{};
        if (g_layoutGetRect(layout, &rc, kSyntheticFolderId, "GeneralRect"))
            *reinterpret_cast<LTRectCompat *>(reinterpret_cast<unsigned char *>(folder) + profile->baseFolderPageRectOffset) = rc;
    }

    static int GetPerformanceCustomInt(const char *key, int fallback)
    {
        if (!g_layoutGetInt)
            return fallback;
        const auto *profile = CShell::CurrentProfile();
        HMODULE cshell = CShell::Module();
        if (!profile || !cshell)
            return fallback;
        auto *base = reinterpret_cast<unsigned char *>(cshell);
        void *layout = *reinterpret_cast<void **>(base + profile->layoutMgrGlobalRva);
        return layout ? g_layoutGetInt(layout, kSyntheticFolderId, key) : fallback;
    }

    static bool GetPerformanceCustomPoint(const char *key, LTPointCompat &out)
    {
        if (!g_layoutGetPoint)
            return false;
        const auto *profile = CShell::CurrentProfile();
        HMODULE cshell = CShell::Module();
        if (!profile || !cshell)
            return false;
        auto *base = reinterpret_cast<unsigned char *>(cshell);
        void *layout = *reinterpret_cast<void **>(base + profile->layoutMgrGlobalRva);
        return layout && g_layoutGetPoint(layout, &out, kSyntheticFolderId, key);
    }

    static int __fastcall NativeFolderOnLeftHook(void *self, void *)
    {
        const int r = g_baseOnLeft ? g_baseOnLeft(self) : 0;
        if (r && g_updateData)
            g_updateData(self, 1);
        return r;
    }

    static int __fastcall NativeFolderOnRightHook(void *self, void *)
    {
        const int r = g_baseOnRight ? g_baseOnRight(self) : 0;
        if (r && g_updateData)
            g_updateData(self, 1);
        return r;
    }

    static int __fastcall NativeFolderLButtonUpHook(void *self, void *, int x, int y)
    {
        const int r = g_baseOnLButtonUp ? g_baseOnLButtonUp(self, x, y) : 0;
        if (r && g_updateData)
            g_updateData(self, 1);
        return r;
    }

    static int __fastcall NativeFolderRButtonUpHook(void *self, void *, int x, int y)
    {
        const int r = g_baseOnRButtonUp ? g_baseOnRButtonUp(self, x, y) : 0;
        if (r && g_updateData)
            g_updateData(self, 1);
        return r;
    }

    static int __fastcall NativeFolderBuildHook(void *self, void *)
    {
        return OpenGLOptionsMenu::Instance().BuildNativeFolder(self) ? 1 : 0;
    }

    static int __fastcall NativeFolderCommandHook(void *self, void *, uint32_t command, uint32_t p1, uint32_t p2)
    {
        return OpenGLOptionsMenu::Instance().HandleNativeCommand(self, command, p1, p2);
    }

    static void __fastcall NativeFolderFocusHook(void *self, void *, int focus)
    {
        OpenGLOptionsMenu::Instance().HandleNativeFocus(self, focus);
    }

    static void *__fastcall NativeFolderGetHelpStringHook(void *self, void *, uint32_t helpId, int controlIndex)
    {
        if (void *hs = OpenGLOptionsMenu::Instance().GetNativeHelpString(helpId, controlIndex))
            return hs;
        return g_baseGetHelpString ? g_baseGetHelpString(self, helpId, controlIndex) : nullptr;
    }

    static int __fastcall FolderDisplayBuildHook(void *self, void *)
    {
        const int ok = g_originalDisplayBuild ? g_originalDisplayBuild(self) : 0;
        if (!ok || !self || !g_getMenuFont || !g_addTextLiteral || !g_addControl)
            return ok;

        // Locate the Custom Performance row by its stock layout position rather
        // than assuming it is at a fixed vector index.  CFolderDisplay owns extra
        // decorative/base controls, so end[-N] is not stable.
        auto *fb = reinterpret_cast<unsigned char *>(self);
        void **begin = *reinterpret_cast<void ***>(fb + 0x38);
        void **end = *reinterpret_cast<void ***>(fb + 0x3c);
        if (!begin || !end || begin >= end)
            return ok;
        void *custom = nullptr;
        int customX = 135;
        int customY = 252;
        int bestScore = 0x7fffffff;
        for (void **it = begin; it < end; ++it)
        {
            if (!*it)
                continue;
            auto *cb = reinterpret_cast<unsigned char *>(*it);
            const int x = *reinterpret_cast<int *>(cb + 0x18);
            const int y = *reinterpret_cast<int *>(cb + 0x1c);
            // Stock 640x480 CFolderDisplay puts CUSTOM PERFORMANCE in the lower
            // content area around (135,252); BACK is much lower (~360).
            if (y < 210 || y > 310)
                continue;
            const int score = std::abs(x - 135) + std::abs(y - 252) * 2;
            if (score < bestScore)
            {
                bestScore = score;
                custom = *it;
                customX = x;
                customY = y + 10;
            }
        }
        if (!custom)
            return ok;

        void *font = g_getMenuFont();
        void *ctrl = g_addTextLiteral(self, "OPENGL OPTIONS", kCmdOpenGLOptions, 0x57u, 0, font, 0);
        if (ctrl)
        {
            // Match the native row spacing used by this screen.  The coordinates
            // are logical folder coordinates and are scaled by Talon's UI code.
            const int index = g_addControl(self, ctrl, 3, customX, customY + 28, 1);
            LOG_SESSION("OpenGL Options: native Graphics entry ctrl=%p index=%d custom=(%d,%d) new=(%d,%d)",
                        ctrl, index, customX, customY, customX, customY + 28);
        }

        // Create the reconstructed submenu lazily on activation.  Graphics-folder
        // construction must remain independent from the synthetic folder.
        return ok;
    }

    static int __fastcall FolderDisplayOnCommandHook(void *self, void *, uint32_t command, uint32_t p1, uint32_t p2)
    {
        if (command == kCmdOpenGLOptions)
        {
            if (OpenGLOptionsMenu::Instance().EnsureNativeFolder(self))
            {
                OpenGLOptionsMenu::Instance().Open();
                return 1;
            }
        }
        return g_originalDisplayCommand ? g_originalDisplayCommand(self, command, p1, p2) : 0;
    }
}

OpenGLOptionsMenu &OpenGLOptionsMenu::Instance()
{
    static OpenGLOptionsMenu s;
    return s;
}

bool OpenGLOptionsMenu::InstallCShellHooks()
{
    if (m_displayVtable)
        return true;
    if (!CShell::Detect())
        return false;
    if (!CShell::IsSupported())
    {
        LOG_SESSION("OpenGL Options: recognized %s, but its CSHELL RVA profile is not mapped yet", CShell::BuildName());
        return false;
    }
    HMODULE cshell = CShell::Module();
    const auto *profile = CShell::CurrentProfile();
    if (!cshell || !profile)
        return false;

    auto *base = reinterpret_cast<unsigned char *>(cshell);
    void **vt = reinterpret_cast<void **>(base + profile->folderDisplayVtableRva);
    if (vt[4] != (base + profile->folderDisplayBuildRva) ||
        vt[1] != (base + profile->folderDisplayOnCommandRva))
    {
        LOG_SESSION("OpenGL Options: CSHELL profile validation failed for %s", profile->name);
        return false;
    }

    g_getMenuFont = reinterpret_cast<GetMenuFontFn>(base + profile->baseFolderGetMenuFontRva);
    g_setTitleHString = reinterpret_cast<SetTitleHStringFn>(base + profile->baseFolderSetTitleHStringRva);
    g_createToggleHString = reinterpret_cast<CreateToggleHStringFn>(base + profile->baseFolderCreateToggleHStringRva);
    g_addFreeControl = reinterpret_cast<AddFreeControlFn>(base + profile->baseFolderAddFreeControlRva);
    g_addTab = reinterpret_cast<AddTabFn>(base + profile->baseFolderAddTabRva);
    g_removeFree = reinterpret_cast<RemoveFreeFn>(base + profile->baseFolderRemoveFreeRva);
    g_baseGetHelpString = reinterpret_cast<GetHelpStringFn>(base + profile->baseFolderGetHelpStringRva);
    g_updateData = reinterpret_cast<FolderUpdateDataFn>(base + profile->baseFolderUpdateDataRva);
    g_layoutGetRect = reinterpret_cast<LayoutGetRectFn>(base + profile->layoutGetCustomRectRva);
    g_layoutGetInt = reinterpret_cast<LayoutGetIntFn>(base + profile->layoutGetCustomIntRva);
    g_layoutGetPoint = reinterpret_cast<LayoutGetPointFn>(base + profile->layoutGetCustomPointRva);
    g_toggleSetOnStringId = reinterpret_cast<ToggleSetStringIdFn>(base + profile->toggleSetOnStringIdRva);
    g_toggleSetOffStringId = reinterpret_cast<ToggleSetStringIdFn>(base + profile->toggleSetOffStringIdRva);
    g_addTextLiteral = reinterpret_cast<AddTextLiteralFn>(base + profile->baseFolderAddTextLiteralRva);
    g_addControl = reinterpret_cast<AddControlFn>(base + profile->baseFolderAddControlRva);
    g_baseBuild = reinterpret_cast<FolderBuildFn>(base + profile->baseFolderBuildRva);
    g_baseCommand = reinterpret_cast<FolderOnCommandFn>(base + profile->baseFolderOnCommandRva);
    g_baseTerm = reinterpret_cast<FolderTermFn>(base + profile->baseFolderTermRva);
    g_baseOnFocus = reinterpret_cast<FolderFocusFn>(base + profile->baseFolderOnFocusRva);
    g_mgrSetCurrent = reinterpret_cast<FolderMgrSetFn>(base + profile->folderMgrSetCurrentRva);
    g_mgrShowFolder = reinterpret_cast<FolderMgrShowFn>(base + profile->folderMgrShowFolderRva);
    g_perfCtor = reinterpret_cast<FolderCtorFn>(base + profile->folderPerformanceCtorRva);
    g_cshellNew = reinterpret_cast<CShellNewFn>(base + profile->operatorNewRva);

    void *oldBuild = nullptr;
    void *oldCommand = nullptr;
    if (!HookManager::InstallPointerRaw("options_menu.display.build", &vt[4],
                                        reinterpret_cast<void *>(&FolderDisplayBuildHook), &oldBuild))
        return false;
    if (!HookManager::InstallPointerRaw("options_menu.display.command", &vt[1],
                                        reinterpret_cast<void *>(&FolderDisplayOnCommandHook), &oldCommand))
    {
        HookManager::Uninstall("options_menu.display.build");
        return false;
    }

    m_cshell = cshell;
    m_displayVtable = vt;
    m_originalBuild = oldBuild;
    m_originalOnCommand = oldCommand;
    g_originalDisplayBuild = reinterpret_cast<FolderBuildFn>(oldBuild);
    g_originalDisplayCommand = reinterpret_cast<FolderOnCommandFn>(oldCommand);
    LOG_SESSION("OpenGL Options: CBaseFolder::SetTab parity hooks installed");
    return true;
}

bool OpenGLOptionsMenu::EnsureNativeFolder(void *displayFolder)
{
    if (m_nativeFolder)
        return true;
    const auto *profile = CShell::CurrentProfile();
    if (!displayFolder || !m_cshell || !profile || !g_perfCtor || !g_cshellNew)
        return false;

    m_folderMgr = *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(displayFolder) + 0x10);
    m_parentFolderId = *reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(displayFolder) + 0x14);
    if (!m_folderMgr)
        return false;

    // Allocate from CSHELL's own operator new so the stock deleting
    // destructor uses the matching heap on renderer shutdown.
    void *mem = g_cshellNew(profile->folderPerformanceSize);
    if (!mem)
        return false;
    std::memset(mem, 0, profile->folderPerformanceSize);
    void *obj = g_perfCtor(mem);
    if (!obj)
        return false;

    auto *base = reinterpret_cast<unsigned char *>(m_cshell);
    void **stockPerfVt = reinterpret_cast<void **>(base + profile->folderPerformanceVtableRva);
    void **baseFolderVt = reinterpret_cast<void **>(base + profile->baseFolderVtableRva);
    for (size_t i = 0; i < kVtableEntries; ++i)
        g_nativeVtable[i] = stockPerfVt[i];
    g_nativeVtable[1] = reinterpret_cast<void *>(&NativeFolderCommandHook);
    g_nativeVtable[4] = reinterpret_cast<void *>(&NativeFolderBuildHook);
    g_nativeVtable[9] = reinterpret_cast<void *>(&NativeFolderFocusHook);
    g_nativeVtable[30] = reinterpret_cast<void *>(&NativeFolderGetHelpStringHook);

    // Critical: never let our synthetic page run CFolderPerformance's input
    // overrides.  Those call SetPerformanceValues(), which is why changing an
    // OpenGL toggle was pushing AVP2's Performance preset to Extra Low.
    g_baseOnLButtonUp = reinterpret_cast<FolderMouseFn>(baseFolderVt[18]);
    g_baseOnRButtonUp = reinterpret_cast<FolderMouseFn>(baseFolderVt[21]);
    g_baseOnLeft = reinterpret_cast<FolderNavFn>(baseFolderVt[33]);
    g_baseOnRight = reinterpret_cast<FolderNavFn>(baseFolderVt[34]);
    g_nativeVtable[18] = reinterpret_cast<void *>(&NativeFolderLButtonUpHook);
    g_nativeVtable[21] = reinterpret_cast<void *>(&NativeFolderRButtonUpHook);
    g_nativeVtable[33] = reinterpret_cast<void *>(&NativeFolderOnLeftHook);
    g_nativeVtable[34] = reinterpret_cast<void *>(&NativeFolderOnRightHook);
    *reinterpret_cast<void ***>(obj) = g_nativeVtable.data();

    // Run CBaseFolder::Init through the stock virtual slot using the existing
    // Custom Performance folder ID (10).  This deliberately reuses its
    // FolderPerformance layout/background/font definitions while remaining a
    // distinct object reached directly through FolderMgr::SetCurrentFolder.
    auto init = reinterpret_cast<FolderInitFn>(stockPerfVt[2]);
    if (!init)
        return false;
    init(obj, kSyntheticFolderId);

    m_nativeFolder = obj;
    LOG_SESSION("OpenGL Options: native CBaseFolder object created obj=%p parentId=%d mgr=%p", obj, m_parentFolderId, m_folderMgr);
    return true;
}

bool OpenGLOptionsMenu::BuildNativeFolder(void *folder)
{
    if (!folder || !g_addTextLiteral || !g_addControl || !g_baseBuild ||
        !g_setTitleHString || !g_createToggleHString || !g_addFreeControl || !g_addTab || !m_cshell)
        return false;

    const auto *profile = CShell::CurrentProfile();
    if (!profile)
        return false;

    GUIQuality &q = GUIQuality::Instance();
    m_ssaoValue = q.IsSSAOEnabled() ? 1 : 0;
    m_ssrValue = q.IsSSREnabled() ? 1 : 0;
    m_msaaValue = q.IsMSAA4xEnabled() ? 1 : 0;
    m_lastSSAO = m_ssaoValue;
    m_lastSSR = m_ssrValue;
    m_lastMSAA = m_msaaValue;
    m_bloomValue = q.IsBloomEnabled() ? 1 : 0;
    m_dynamicExposureValue = q.IsDynamicExposureEnabled() ? 1 : 0;
    m_lastBloom = m_bloomValue;
    m_lastDynamicExposure = m_dynamicExposureValue;
    m_anisotropicValue = TextureManager::Instance().IsAnisotropic16xEnabled() ? 1 : 0;
    m_lastAnisotropic = m_anisotropicValue;
    m_highQualityLightGridValue = WorldRenderer::Instance().Lighting().IsHighQualityLightGridEnabled() ? 1 : 0;
    m_lastHighQualityLightGrid = m_highQualityLightGridValue;
    m_debugOverlayValue = RendererCore::Instance().IsPerfOverlayEnabled() ? 1 : 0;
    m_lastDebugOverlay = m_debugOverlayValue;
    m_currentTab = 0;

    if (void *hs = CreateLiteralHString("OpenGL Options"))
    {
        g_setTitleHString(folder, hs);
        FreeHString(hs);
    }

    // Use the exact stock AddTab path for BOTH tabs.  AVP2 already has the
    // string resource IDS_DISPLAY (18) = "Graphics", so there is no reason to
    // synthesize a literal text control.  This makes General and Graphics use
    // the identical small font, color/fade behavior, tab group and spacing.
    m_generalTab = g_addTab(folder, kIdsPerformGeneral, kCmdGeneral, kHelpGeneral);
    m_graphicsTab = g_addTab(folder, kIdsGraphics, kCmdGraphics, kHelpGraphics);

    // Match the lower Custom Performance summary band so this page occupies
    // exactly the same visual structure as the stock folder.
    LTPointCompat performPos{};
    if (GetPerformanceCustomPoint("PerformPos", performPos))
    {
        const int column = GetPerformanceCustomInt("ColumnWidth", 180);
        void *largeFont = nullptr;
        if (m_cshell)
        {
            using GetFontFn = void *(__cdecl *)();
            auto fn = reinterpret_cast<GetFontFn>(reinterpret_cast<unsigned char *>(m_cshell) + profile->baseFolderGetLargeFontRva); // GetLargeFont
            if (fn)
                largeFont = fn();
        }
        void *left = g_addTextLiteral(folder, "OpenGL Renderer", 0, 0, 0, largeFont, 0);
        void *right = g_addTextLiteral(folder, "Renderer graphics options", 0, 0, 0, largeFont, 0);
        if (left)
            g_addControl(folder, left, -1, performPos.x, performPos.y, 0);
        if (right)
            g_addControl(folder, right, -1, performPos.x + column, performPos.y, 0);
    }

    LTPointCompat additionalPos{};
    if (GetPerformanceCustomPoint("AdditionalPos", additionalPos))
    {
        void *helpFont = nullptr;
        if (m_cshell)
        {
            using GetFontFn = void *(__cdecl *)();
            auto fn = reinterpret_cast<GetFontFn>(reinterpret_cast<unsigned char *>(m_cshell) + profile->baseFolderGetHelpFontRva); // GetHelpFont
            if (fn)
                helpFont = fn();
        }
        void *info = g_addTextLiteral(folder, "OpenGL renderer options. Changes apply immediately.", 0, 0, 0, helpFont, 0);
        if (info)
            g_addControl(folder, info, -1, additionalPos.x, additionalPos.y, 0);
    }

    const int ok = g_baseBuild(folder);
    LOG_SESSION("OpenGL Options: Custom Performance shell Build -> %d", ok);
    return ok != 0;
}

void OpenGLOptionsMenu::BuildCurrentTabControls()
{
    if (!m_nativeFolder || !g_removeFree)
        return;
    g_removeFree(m_nativeFolder);
    m_ssaoCtrl = m_ssrCtrl = m_msaaCtrl = nullptr;
    m_bloomCtrl = m_dynamicExposureCtrl = m_anisotropicCtrl = m_highQualityLightGridCtrl = nullptr;
    m_vsyncCtrl = m_debugOverlayCtrl = nullptr;

    SetPerformancePageRect(m_nativeFolder);

    // m_nCurTab is authoritative, just as in stock BuildControlList().
    m_currentTab = GetFolderTab(m_nativeFolder);

    if (m_currentTab == 0)
    {
        m_debugOverlayValue = RendererCore::Instance().IsPerfOverlayEnabled() ? 1 : 0;
        m_lastDebugOverlay = m_debugOverlayValue;
    }
    else if (m_currentTab == 1)
    {
        m_vsyncValue = RendererCore::Instance().IsVSyncEnabled() ? 1 : 0;
        m_lastVSync = m_vsyncValue;
        GUIQuality &q = GUIQuality::Instance();
        m_msaaValue = q.IsMSAA4xEnabled() ? 1 : 0;
        m_ssaoValue = q.IsSSAOEnabled() ? 1 : 0;
        m_ssrValue = q.IsSSREnabled() ? 1 : 0;
        m_lastMSAA = m_msaaValue;
        m_lastSSAO = m_ssaoValue;
        m_lastSSR = m_ssrValue;
        m_bloomValue = q.IsBloomEnabled() ? 1 : 0;
        m_dynamicExposureValue = q.IsDynamicExposureEnabled() ? 1 : 0;
        m_lastBloom = m_bloomValue;
        m_lastDynamicExposure = m_dynamicExposureValue;
        m_anisotropicValue = TextureManager::Instance().IsAnisotropic16xEnabled() ? 1 : 0;
        m_lastAnisotropic = m_anisotropicValue;
        m_highQualityLightGridValue = WorldRenderer::Instance().Lighting().IsHighQualityLightGridEnabled() ? 1 : 0;
        m_lastHighQualityLightGrid = m_highQualityLightGridValue;
    }
    else
    {
        return;
    }

    const int rightColumn = GetPerformanceCustomInt("GeneralWidth", 160);
    auto addToggle = [&](const char *label, uint32_t helpId, int *value) -> void *
    {
        void *hs = CreateLiteralHString(label);
        if (!hs)
            return nullptr;
        void *ctrl = g_createToggleHString(m_nativeFolder, hs, (int)helpId, rightColumn, value, 0, nullptr);
        FreeHString(hs);
        if (ctrl)
        {
            // This is exactly what CBaseFolder::AddToggle does after CreateToggle.
            g_addFreeControl(m_nativeFolder, ctrl);
            SetToggleOnOff(ctrl);
        }
        return ctrl;
    };

    if (m_currentTab == 0)
    {
        // General tab: renderer-wide debug switches.
        m_debugOverlayCtrl = addToggle("Debug Overlay", kHelpDebugOverlay, &m_debugOverlayValue);
    }
    else
    {
        // Graphics tab: presentation/quality options using the exact stock on/off control style.
        m_vsyncCtrl = addToggle("VSync", kHelpVSync, &m_vsyncValue);
        m_msaaCtrl = addToggle("4x MSAA", kHelpMSAA, &m_msaaValue);
        m_anisotropicCtrl = addToggle("16x Anisotropic Filtering", kHelpAnisotropic, &m_anisotropicValue);
        m_highQualityLightGridCtrl = addToggle("Higher Quality Light-Grid Interpolation", kHelpHighQualityLightGrid, &m_highQualityLightGridValue);
        m_ssaoCtrl = addToggle("Ambient Occlusion", kHelpSSAO, &m_ssaoValue);
        m_ssrCtrl = addToggle("Surface Reflections", kHelpSSR, &m_ssrValue);
        m_bloomCtrl = addToggle("Bloom", kHelpBloom, &m_bloomValue);
        m_dynamicExposureCtrl = addToggle("Dynamic Exposure", kHelpDynamicExposure, &m_dynamicExposureValue);
    }
}

void OpenGLOptionsMenu::SwitchTab(int tab)
{
    if (!m_nativeFolder)
        return;
    const int wanted = (tab == 1) ? 1 : 0;

    // Mirror CFolderPerformance::OnCommand exactly (source order):
    //   SetTab(n);
    //   m_PageRect = ...;
    //   enable/disable tab labels;
    //   UpdateData(LTTRUE);
    //   BuildControlList();
    //   UpdateData(LTFALSE).
    //
    // UpdateData(TRUE) must run BEFORE BuildCurrentTabControls(), because that
    // routine begins with RemoveFree() and destroys the old tab's controls.
    if (!SetFolderTab(m_nativeFolder, wanted))
    {
        LOG_SESSION("OpenGL Options: SetTab(%d) rejected (numTabs=%d)", wanted,
                    *reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(m_nativeFolder) + CShell::CurrentProfile()->baseFolderNumTabsOffset));
        return;
    }
    m_currentTab = GetFolderTab(m_nativeFolder);

    // Both of our tabs use the Performance GeneralRect, matching General/SFX
    // in the stock menu.  BuildCurrentTabControls also reapplies it before
    // constructing the free-control list.
    SetPerformancePageRect(m_nativeFolder);

    // Stock convention: the active tab is disabled (grey/non-clickable),
    // all other tabs remain enabled.
    SetCtrlEnabled(m_generalTab, m_currentTab != 0);
    SetCtrlEnabled(m_graphicsTab, m_currentTab != 1);

    // CBaseFolder::UpdateData(LTTRUE): call UpdateData(TRUE) on every fixed
    // and free control so the currently displayed tab writes its UI state
    // back to the bound variables before BuildControlList removes it.
    if (g_updateData)
        g_updateData(m_nativeFolder, 1);

    // Equivalent to CFolderPerformance::BuildControlList() for our page.
    BuildCurrentTabControls();

    // CBaseFolder::UpdateData(LTFALSE): load bound values into all newly
    // created controls so their displayed On/Off state is correct immediately.
    if (g_updateData)
        g_updateData(m_nativeFolder, 0);

    LOG_SESSION("OpenGL Options: SetTab(%d) -> curTab=%d (%s)", wanted, m_currentTab,
                m_currentTab == 1 ? "Graphics" : "General");
}

void OpenGLOptionsMenu::SetTab(int tab)
{
    SwitchTab(tab);
}

int OpenGLOptionsMenu::HandleNativeCommand(void *folder, unsigned command, unsigned p1, unsigned p2)
{
    switch (command)
    {
    case kCmdGeneral:
        SwitchTab(0);
        return 1;
    case kCmdGraphics:
        SwitchTab(1);
        return 1;
    default:
        break;
    }
    // CBaseFolder only. Never CFolderPerformance::OnCommand/OnLeft/OnRight:
    // those update g_pPerformanceMgr and were causing the Extra Low preset.
    return g_baseCommand ? g_baseCommand(folder, command, p1, p2) : 0;
}

void OpenGLOptionsMenu::HandleNativeFocus(void *folder, int focus)
{
    if (focus)
    {
        SwitchTab(0);
    }
    else if (g_removeFree)
    {
        // Same rule as a tab transition: save the live controls before they
        // are removed from the folder.
        if (g_updateData)
            g_updateData(folder, 1);
        g_removeFree(folder);
        m_ssaoCtrl = m_ssrCtrl = m_msaaCtrl = nullptr;
        m_bloomCtrl = m_dynamicExposureCtrl = m_anisotropicCtrl = m_highQualityLightGridCtrl = nullptr;
        m_vsyncCtrl = m_debugOverlayCtrl = nullptr;
    }
    if (g_baseOnFocus)
        g_baseOnFocus(folder, focus);
}

void *OpenGLOptionsMenu::GetNativeHelpString(unsigned helpId, int)
{
    const char *text = nullptr;
    switch (helpId)
    {
    case kHelpGeneral:
        text = "General OpenGL renderer options.";
        break;
    case kHelpGraphics:
        text = "Graphics features provided by the OpenGL renderer.";
        break;
    case kHelpMSAA:
        text = "Enable 4x multisample anti-aliasing for smoother geometry edges.";
        break;
    case kHelpAnisotropic:
        text = "Enable up to 16x anisotropic texture filtering for sharper textures viewed at steep angles.";
        break;
    case kHelpHighQualityLightGrid:
        text = "Use tricubic 4x4x4 interpolation for smoother Talon light-grid lighting. More GPU/CPU work than standard trilinear filtering.";
        break;
    case kHelpSSAO:
        text = "Enable screen-space ambient occlusion for additional contact and crevice shading.";
        break;
    case kHelpSSR:
        text = "Enable screen-space reflections on supported visible surfaces.";
        break;
    case kHelpVSync:
        text = "Synchronize presentation to the display refresh rate to prevent tearing.";
        break;
    case kHelpDebugOverlay:
        text = "Show the renderer performance/debug overlay (the same overlay toggled by F12).";
        break;
    case kHelpBloom:
        text = "Enable a soft bloom glow around bright scene pixels.";
        break;
    case kHelpDynamicExposure:
        text = "Brighten dark scenes with color-neutral dynamic exposure while leaving normal/bright scenes at baseline.";
        break;
    default:
        return nullptr;
    }
    return CreateLiteralHString(text);
}

void OpenGLOptionsMenu::Open()
{
    if (!m_nativeFolder || !m_folderMgr || !g_mgrSetCurrent)
        return;
    m_open = true;
    g_mgrSetCurrent(m_folderMgr, m_nativeFolder, 0);
    LOG_SESSION("OpenGL Options: entered native CSHELL folder");
}

void OpenGLOptionsMenu::Close()
{
    if (!m_open)
        return;
    m_open = false;
    if (m_folderMgr && g_mgrShowFolder && m_parentFolderId)
        g_mgrShowFolder(m_folderMgr, m_parentFolderId);
    LOG_SESSION("OpenGL Options: returned to Graphics folder id=%d", m_parentFolderId);
}

void OpenGLOptionsMenu::Tick()
{
    if (!m_open)
        return;

    // Native LTGUI controls mutate only our bound integers. Mirror them
    // directly into renderer-owned state; never route through PerformanceMgr.
    if (m_currentTab == 0)
    {
        if (m_debugOverlayValue != m_lastDebugOverlay)
        {
            m_lastDebugOverlay = m_debugOverlayValue;
            RendererCore::Instance().SetPerfOverlayEnabled(m_debugOverlayValue != 0);
            m_debugOverlayValue = RendererCore::Instance().IsPerfOverlayEnabled() ? 1 : 0;
            m_lastDebugOverlay = m_debugOverlayValue;
            LOG_SESSION("OpenGL Options: Debug Overlay -> %d", m_debugOverlayValue);
        }
        return;
    }

    if (m_currentTab == 1)
    {
        if (m_vsyncValue != m_lastVSync)
        {
            m_lastVSync = m_vsyncValue;
            RendererCore::Instance().SetVSyncEnabled(m_vsyncValue != 0);
            m_vsyncValue = RendererCore::Instance().IsVSyncEnabled() ? 1 : 0;
            m_lastVSync = m_vsyncValue;
            LOG_SESSION("OpenGL Options: VSync -> %d", m_vsyncValue);
        }
        GUIQuality &q = GUIQuality::Instance();
        if (m_msaaValue != m_lastMSAA)
        {
            m_lastMSAA = m_msaaValue;
            q.SetMSAA4xEnabled(m_msaaValue != 0);
            m_msaaValue = q.IsMSAA4xEnabled() ? 1 : 0;
            m_lastMSAA = m_msaaValue;
        }
        if (m_anisotropicValue != m_lastAnisotropic)
        {
            m_lastAnisotropic = m_anisotropicValue;
            TextureManager::Instance().SetAnisotropic16xEnabled(m_anisotropicValue != 0);
            m_anisotropicValue = TextureManager::Instance().IsAnisotropic16xEnabled() ? 1 : 0;
            m_lastAnisotropic = m_anisotropicValue;
        }
        if (m_highQualityLightGridValue != m_lastHighQualityLightGrid)
        {
            m_lastHighQualityLightGrid = m_highQualityLightGridValue;
            WorldRenderer::Instance().Lighting().SetHighQualityLightGridEnabled(m_highQualityLightGridValue != 0);
            m_highQualityLightGridValue = WorldRenderer::Instance().Lighting().IsHighQualityLightGridEnabled() ? 1 : 0;
            m_lastHighQualityLightGrid = m_highQualityLightGridValue;
        }
        if (m_ssaoValue != m_lastSSAO)
        {
            m_lastSSAO = m_ssaoValue;
            q.SetSSAOEnabled(m_ssaoValue != 0);
            m_ssaoValue = q.IsSSAOEnabled() ? 1 : 0;
            m_lastSSAO = m_ssaoValue;
        }
        if (m_ssrValue != m_lastSSR)
        {
            m_lastSSR = m_ssrValue;
            q.SetSSREnabled(m_ssrValue != 0);
            m_ssrValue = q.IsSSREnabled() ? 1 : 0;
            m_lastSSR = m_ssrValue;
        }
        if (m_bloomValue != m_lastBloom)
        {
            m_lastBloom = m_bloomValue;
            q.SetBloomEnabled(m_bloomValue != 0);
            m_bloomValue = q.IsBloomEnabled() ? 1 : 0;
            m_lastBloom = m_bloomValue;
        }
        if (m_dynamicExposureValue != m_lastDynamicExposure)
        {
            m_lastDynamicExposure = m_dynamicExposureValue;
            q.SetDynamicExposureEnabled(m_dynamicExposureValue != 0);
            m_dynamicExposureValue = q.IsDynamicExposureEnabled() ? 1 : 0;
            m_lastDynamicExposure = m_dynamicExposureValue;
        }
    }
}

void OpenGLOptionsMenu::RemoveCShellHooks()
{
    // The synthetic folder is allocated from CSHELL, but FolderMgr may retain
    // its pointer in current/history/navigation state even after we return to
    // the parent folder.  Deleting it here creates a use-after-free when Talon
    // aborts a failed world load and immediately reconstructs the main menu.
    //
    // Make the object self-contained and safe to outlive opengl.ren instead:
    //  * leave the current page while all renderer callbacks still exist,
    //  * remove free controls whose UpdateData bindings point into this DLL,
    //  * replace the renderer-owned synthetic vtable with CSHELL's CBaseFolder
    //    vtable,
    //  * do NOT delete the CSHELL allocation.
    //
    // This intentionally trades a tiny allocation for lifetime correctness on
    // renderer unload/reload paths.  CSHELL can safely retain or later dispose
    // of the object without ever dispatching into unloaded renderer code.
    if (m_open)
        Close();

    if (m_nativeFolder)
    {
        if (g_updateData)
            g_updateData(m_nativeFolder, 1);
        if (g_removeFree)
            g_removeFree(m_nativeFolder);

        const auto *profile = CShell::CurrentProfile();
        void **baseFolderVt = (m_cshell && profile)
                                  ? reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(m_cshell) + profile->baseFolderVtableRva)
                                  : nullptr;
        if (baseFolderVt)
        {
            *reinterpret_cast<void ***>(m_nativeFolder) = baseFolderVt;
            LOG_SESSION("OpenGL Options: quarantined native folder obj=%p with stock CBaseFolder vtable for renderer unload", m_nativeFolder);
        }
    }

    if (m_displayVtable)
    {
        HookManager::Uninstall("options_menu.display.command");
        HookManager::Uninstall("options_menu.display.build");
    }

    m_nativeFolder = nullptr;
    m_folderMgr = nullptr;
    m_displayVtable = nullptr;
    m_originalBuild = nullptr;
    m_originalOnCommand = nullptr;
    m_cshell = nullptr;
    m_open = false;
    m_currentTab = 0;
    m_generalTab = nullptr;
    m_graphicsTab = nullptr;
    m_ssaoCtrl = nullptr;
    m_ssrCtrl = nullptr;
    m_msaaCtrl = nullptr;
    m_vsyncCtrl = nullptr;
    m_debugOverlayCtrl = nullptr;
    g_originalDisplayBuild = nullptr;
    g_originalDisplayCommand = nullptr;
    g_getMenuFont = nullptr;
    g_setTitleHString = nullptr;
    g_createToggleHString = nullptr;
    g_addFreeControl = nullptr;
    g_addTab = nullptr;
    g_removeFree = nullptr;
    g_baseGetHelpString = nullptr;
    g_layoutGetRect = nullptr;
    g_layoutGetInt = nullptr;
    g_layoutGetPoint = nullptr;
    g_toggleSetOnStringId = nullptr;
    g_toggleSetOffStringId = nullptr;
    g_baseOnLeft = nullptr;
    g_baseOnRight = nullptr;
    g_baseOnLButtonUp = nullptr;
    g_baseOnRButtonUp = nullptr;
    g_updateData = nullptr;
    g_addTextLiteral = nullptr;
    g_addControl = nullptr;
    g_baseBuild = nullptr;
    g_baseCommand = nullptr;
    g_baseTerm = nullptr;
    g_baseOnFocus = nullptr;
    g_mgrSetCurrent = nullptr;
    g_mgrShowFolder = nullptr;
    g_perfCtor = nullptr;
    g_cshellNew = nullptr;
    CShell::Reset();
}
