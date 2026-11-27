#include "high_refresh_timing.h"
#include "utils/log.h"
#include "../memory/memory_utils.h"
#include "../memory/hook_manager.h"

#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <unordered_map>

namespace
{
    constexpr uintptr_t kClientMgrRva = 0x0DEFACu;
    constexpr uintptr_t kServerMgrRva = 0x0E5DC8u;
    constexpr uintptr_t kClientSleepRva = 0x035070u;
    constexpr uintptr_t kClientSleepCallRva = 0x010E06u;
    constexpr uintptr_t kPdUpdateRva = 0x06E250u;
    constexpr uintptr_t kPdUpdateCallRva = 0x015374u;
    constexpr uintptr_t kUpdateSoundsRva = 0x083370u;
    constexpr uintptr_t kUpdateSoundsCallRva = 0x0836D7u;
    constexpr uintptr_t kServerMgrUpdateRva = 0x083520u;
    constexpr uintptr_t kServerMgrUpdateCallRva = 0x0151DCu;
    constexpr uintptr_t kServerObjectUpdateRva = 0x082E50u;
    constexpr uintptr_t kServerObjectUpdateCallRva = 0x083713u;
    constexpr uintptr_t kClientObjectUpdateRva = 0x017DE0u;
    constexpr uintptr_t kClientObjectUpdateCall1Rva = 0x010FD8u;
    constexpr uintptr_t kClientObjectUpdateCall2Rva = 0x015446u;
    constexpr uintptr_t kClientModelUpdateRva = 0x017F60u;
    constexpr uintptr_t kClientModelUpdateCallRva = 0x017E14u;
    constexpr uintptr_t kClientParticleUpdateRva = 0x017E50u;
    constexpr uintptr_t kClientParticleUpdateCallRva = 0x017E1Au;
    constexpr uintptr_t kClientSpriteUpdateRva = 0x018120u;
    constexpr uintptr_t kClientSpriteUpdateCallRva = 0x017E20u;
    constexpr uintptr_t kClientVisual4UpdateRva = 0x0181F0u;
    constexpr uintptr_t kClientVisual4UpdateCallRva = 0x017E2Cu;

    // Layout offsets are the exact AVP2 structures used by d3d7fix_avp2.
    constexpr uintptr_t kClientMgrFrameTimeOffset = 4968u;
    constexpr uintptr_t kClientMgrCurShellOffset = 5660u;
    constexpr uintptr_t kClientShellGameFrameOffset = 28u;
    constexpr uintptr_t kServerMgrFrameTimeOffset = 2748u;
    constexpr uintptr_t kServerMgrTrueFrameOffset = 2784u;
    constexpr uintptr_t kServerMgrRawDeltaOffset = 0x0AE0u;

    // The CServerMgr* is stored at RVA 0x0E5DC8 and its ILTServer* member
    // is at +0x0D38.  This is the same pointer passed as arg2 to
    // ObjectDLLSetup and stored by Object.lto as g_pLTServer.
    constexpr uintptr_t kServerMgrLTServerOffset = 0x0D38u;

    using ClientSleepFn = void(__cdecl *)(DWORD);
    using PdUpdateFn = void(__cdecl *)(void *);
    using UpdateSoundsFn = void(__fastcall *)(void *, float);
    using ServerMgrUpdateFn = int(__thiscall *)(void *, uint32_t, float);
    using ServerObjectUpdateFn = void(__fastcall *)(void *, void *);
    using ClientObjectUpdateFn = void(__thiscall *)(void *);
    using ClientVisualSubpassFn = void(__cdecl *)(void *);

    static HMODULE g_lithtech = nullptr;
    static ClientSleepFn g_clientSleep = nullptr;
    static PdUpdateFn g_pdUpdate = nullptr;
    static UpdateSoundsFn g_updateSounds = nullptr;
    static ServerMgrUpdateFn g_serverMgrUpdate = nullptr;
    static ServerObjectUpdateFn g_serverObjectUpdate = nullptr;
    static ClientVisualSubpassFn g_clientModelUpdate = nullptr;
    static ClientVisualSubpassFn g_clientParticleUpdate = nullptr;
    static ClientVisualSubpassFn g_clientSpriteUpdate = nullptr;
    static ClientVisualSubpassFn g_clientVisual4Update = nullptr;
    struct ClientVisualSubpassClock
    {
        uint64_t lastMasterFrame = UINT64_MAX;
        double accumulator = 0.0;
        uint64_t calls = 0;
        uint64_t executions = 0;
        uint64_t duplicateCalls = 0;
        uint64_t subMsSkips = 0;
    };

    static ClientVisualSubpassClock g_clientModelClock{};
    static ClientVisualSubpassClock g_clientParticleClock{};
    static ClientVisualSubpassClock g_clientSpriteClock{};
    static ClientVisualSubpassClock g_clientVisual4Clock{};
    static uint64_t g_masterClockFrames = 0;
    static double g_serverObjectAccumulator = 0.0;
    static bool g_installed = false;

    // Runtime counters retained for F10 timing diagnostics and interpolation serials.
    static uint64_t g_playerFixedTicks = 0;
    static uint64_t g_playerSimulationSerial = 0;
    static uint64_t g_serverFixedTicks = 0;
    static uint64_t g_serverSkippedFrames = 0;

    struct ObjectInterpState
    {
        uint64_t serial = 0;
        unsigned objectId = 0;
        unsigned objectType = 0;
        float prevPos[3]{};
        float currPos[3]{};
        float prevQuat[4]{0, 0, 0, 1};
        float currQuat[4]{0, 0, 0, 1};
        bool valid = false;
    };

    static std::unordered_map<const void *, ObjectInterpState> g_objectInterp;

    static void NormalizeQuat(float q[4])
    {
        const float l2 = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
        if (l2 <= 1e-12f || !std::isfinite(l2))
        {
            q[0] = q[1] = q[2] = 0.0f;
            q[3] = 1.0f;
            return;
        }
        const float inv = 1.0f / std::sqrt(l2);
        for (int i = 0; i < 4; ++i)
            q[i] *= inv;
    }

    static unsigned char *GetClientMgr();
    static unsigned char *GetServerMgr();

    struct TimingHistogram
    {
        static constexpr int kBins = 101; // 0..99 ms, 100 = >=100 ms / invalid positive
        uint64_t bins[kBins]{};
        uint64_t count = 0;
        double sumMs = 0.0;
        float minMs = 1.0e30f;
        float maxMs = 0.0f;

        void Add(float seconds)
        {
            if (!std::isfinite(seconds) || seconds < 0.0f)
                return;
            const float ms = seconds * 1000.0f;
            int bin = static_cast<int>(std::floor(ms + 0.5f));
            if (bin < 0)
                bin = 0;
            if (bin >= kBins)
                bin = kBins - 1;
            ++bins[bin];
            ++count;
            sumMs += ms;
            minMs = std::min(minMs, ms);
            maxMs = std::max(maxMs, ms);
        }

        void Reset()
        {
            std::memset(bins, 0, sizeof(bins));
            count = 0;
            sumMs = 0.0;
            minMs = 1.0e30f;
            maxMs = 0.0f;
        }
    };

    static TimingHistogram g_diagClientFrame;
    static TimingHistogram g_diagGameFrame;
    static TimingHistogram g_diagServerFrame;
    static TimingHistogram g_diagServerTrueFrame;
    static LARGE_INTEGER g_diagFreq{};
    static LARGE_INTEGER g_diagWindowStart{};
    static bool g_diagClockReady = false;

    static void ResetTimingDiagnostics()
    {
        g_diagClientFrame.Reset();
        g_diagGameFrame.Reset();
        g_diagServerFrame.Reset();
        g_diagServerTrueFrame.Reset();
        if (!g_diagClockReady)
        {
            QueryPerformanceFrequency(&g_diagFreq);
            g_diagClockReady = g_diagFreq.QuadPart != 0;
        }
        if (g_diagClockReady)
            QueryPerformanceCounter(&g_diagWindowStart);
    }

    static void FormatTopBins(const TimingHistogram &h, char *out, size_t outSize)
    {
        if (!out || outSize == 0)
            return;
        out[0] = '\0';
        struct Pair
        {
            int bin;
            uint64_t count;
        } top[4]{};
        for (int bin = 0; bin < TimingHistogram::kBins; ++bin)
        {
            const uint64_t c = h.bins[bin];
            if (!c)
                continue;
            for (int i = 0; i < 4; ++i)
            {
                if (c > top[i].count)
                {
                    for (int j = 3; j > i; --j)
                        top[j] = top[j - 1];
                    top[i] = {bin, c};
                    break;
                }
            }
        }

        size_t used = 0;
        for (int i = 0; i < 4 && top[i].count; ++i)
        {
            const double pct = h.count ? (100.0 * static_cast<double>(top[i].count) / static_cast<double>(h.count)) : 0.0;
            char part[64]{};
            if (top[i].bin == TimingHistogram::kBins - 1)
                std::snprintf(part, sizeof(part), "%s100+ms:%llu(%.0f%%)", i ? "," : "", static_cast<unsigned long long>(top[i].count), pct);
            else
                std::snprintf(part, sizeof(part), "%s%dms:%llu(%.0f%%)", i ? "," : "", top[i].bin, static_cast<unsigned long long>(top[i].count), pct);
            const size_t len = std::strlen(part);
            if (used + len + 1 >= outSize)
                break;
            std::memcpy(out + used, part, len + 1);
            used += len;
        }
    }

    static void MaybeLogTimingDiagnostics()
    {
        if (!LogIsSessionEnabled())
            return;
        if (!g_diagClockReady)
            ResetTimingDiagnostics();
        if (!g_diagClockReady)
            return;

        LARGE_INTEGER now{};
        QueryPerformanceCounter(&now);
        const double elapsed = static_cast<double>(now.QuadPart - g_diagWindowStart.QuadPart) / static_cast<double>(g_diagFreq.QuadPart);
        if (elapsed < 5.0)
            return;

        char clientTop[192]{}, gameTop[192]{}, serverTop[192]{}, trueTop[192]{};
        FormatTopBins(g_diagClientFrame, clientTop, sizeof(clientTop));
        FormatTopBins(g_diagGameFrame, gameTop, sizeof(gameTop));
        FormatTopBins(g_diagServerFrame, serverTop, sizeof(serverTop));
        FormatTopBins(g_diagServerTrueFrame, trueTop, sizeof(trueTop));

        auto avg = [](const TimingHistogram &h) -> double
        { return h.count ? h.sumMs / static_cast<double>(h.count) : 0.0; };
        LOG_SESSION("TIMING DIAG %.1fs RAW | client n=%llu avg=%.3f min=%.3f max=%.3f top=[%s] | game n=%llu avg=%.3f min=%.3f max=%.3f top=[%s] | server n=%llu avg=%.3f min=%.3f max=%.3f top=[%s] | rawMgr n=%llu avg=%.3f min=%.3f max=%.3f top=[%s] | clientUpdates=%llu serverUpdates=%llu serverSkip=%llu",
                    elapsed,
                    static_cast<unsigned long long>(g_diagClientFrame.count), avg(g_diagClientFrame), g_diagClientFrame.count ? g_diagClientFrame.minMs : 0.0f, g_diagClientFrame.maxMs, clientTop,
                    static_cast<unsigned long long>(g_diagGameFrame.count), avg(g_diagGameFrame), g_diagGameFrame.count ? g_diagGameFrame.minMs : 0.0f, g_diagGameFrame.maxMs, gameTop,
                    static_cast<unsigned long long>(g_diagServerFrame.count), avg(g_diagServerFrame), g_diagServerFrame.count ? g_diagServerFrame.minMs : 0.0f, g_diagServerFrame.maxMs, serverTop,
                    static_cast<unsigned long long>(g_diagServerTrueFrame.count), avg(g_diagServerTrueFrame), g_diagServerTrueFrame.count ? g_diagServerTrueFrame.minMs : 0.0f, g_diagServerTrueFrame.maxMs, trueTop,
                    static_cast<unsigned long long>(g_playerFixedTicks),
                    static_cast<unsigned long long>(g_serverFixedTicks), static_cast<unsigned long long>(g_serverSkippedFrames));

        LOG_SESSION("CLIENT VISUAL DIAG | model c=%llu e=%llu skip=%llu acc=%.3fms | particle c=%llu e=%llu skip=%llu acc=%.3fms | sprite c=%llu e=%llu skip=%llu acc=%.3fms | visual4 c=%llu e=%llu skip=%llu acc=%.3fms | masterFrames=%llu",
                    static_cast<unsigned long long>(g_clientModelClock.calls),
                    static_cast<unsigned long long>(g_clientModelClock.executions),
                    static_cast<unsigned long long>(g_clientModelClock.subMsSkips), g_clientModelClock.accumulator * 1000.0,
                    static_cast<unsigned long long>(g_clientParticleClock.calls),
                    static_cast<unsigned long long>(g_clientParticleClock.executions),
                    static_cast<unsigned long long>(g_clientParticleClock.subMsSkips), g_clientParticleClock.accumulator * 1000.0,
                    static_cast<unsigned long long>(g_clientSpriteClock.calls),
                    static_cast<unsigned long long>(g_clientSpriteClock.executions),
                    static_cast<unsigned long long>(g_clientSpriteClock.subMsSkips), g_clientSpriteClock.accumulator * 1000.0,
                    static_cast<unsigned long long>(g_clientVisual4Clock.calls),
                    static_cast<unsigned long long>(g_clientVisual4Clock.executions),
                    static_cast<unsigned long long>(g_clientVisual4Clock.subMsSkips), g_clientVisual4Clock.accumulator * 1000.0,
                    static_cast<unsigned long long>(g_masterClockFrames));

        g_clientModelClock.calls = g_clientModelClock.executions = g_clientModelClock.duplicateCalls = g_clientModelClock.subMsSkips = 0;
        g_clientParticleClock.calls = g_clientParticleClock.executions = g_clientParticleClock.duplicateCalls = g_clientParticleClock.subMsSkips = 0;
        g_clientSpriteClock.calls = g_clientSpriteClock.executions = g_clientSpriteClock.duplicateCalls = g_clientSpriteClock.subMsSkips = 0;
        g_clientVisual4Clock.calls = g_clientVisual4Clock.executions = g_clientVisual4Clock.duplicateCalls = g_clientVisual4Clock.subMsSkips = 0;
        g_playerFixedTicks = g_serverFixedTicks = 0;
        g_serverSkippedFrames = 0;
        ResetTimingDiagnostics();
    }

    static void SampleClientTimingRaw()
    {
        if (!LogIsSessionEnabled())
            return;
        unsigned char *mgr = GetClientMgr();
        if (!mgr)
            return;
        g_diagClientFrame.Add(*reinterpret_cast<float *>(mgr + kClientMgrFrameTimeOffset));
        MaybeLogTimingDiagnostics();
    }

    static void SampleGameTimingRaw()
    {
        if (!LogIsSessionEnabled())
            return;
        unsigned char *mgr = GetClientMgr();
        if (!mgr)
            return;
        unsigned char *shell = *reinterpret_cast<unsigned char **>(mgr + kClientMgrCurShellOffset);
        if (!shell)
            return;
        g_diagGameFrame.Add(*reinterpret_cast<float *>(shell + kClientShellGameFrameOffset));
        MaybeLogTimingDiagnostics();
    }

    static void SampleServerTimingRaw()
    {
        if (!LogIsSessionEnabled())
            return;
        unsigned char *mgr = GetServerMgr();
        if (!mgr)
            return;
        g_diagServerFrame.Add(*reinterpret_cast<float *>(mgr + kServerMgrFrameTimeOffset));
        // +0xADC is a cumulative server-step counter, not a target-step count.
        // The "true" histogram is populated from CServerMgr::Update's raw
        // timeElapsed argument in HighRefresh_ServerMgrUpdate instead.
        MaybeLogTimingDiagnostics();
    }

    static HMODULE g_cshellModule = nullptr;
    static unsigned char *g_cshellLimiterBranch = nullptr;
    static bool g_cshellLimiterDisabled = false;

    // Keep Talon's internal stock 10 ms scheduled-object scheduler intact,
    // but give every Object.lto consumer of ILTServer::GetTime/GetFrameTime one
    // coherent real-time clock.  This is deliberately global at the ILTServer API
    // boundary rather than a Door-specific code patch.
    static void *g_ltServerInterface = nullptr;
    static uintptr_t *g_ltServerGetTimeSlot = nullptr;
    static uintptr_t *g_ltServerGetFrameTimeSlot = nullptr;
    using LTServerGetTimeFn = float(__thiscall *)(void *);
    using LTServerGetFrameTimeFn = float(__thiscall *)(void *);
    static LTServerGetTimeFn g_originalLTServerGetTime = nullptr;
    static LTServerGetFrameTimeFn g_originalLTServerGetFrameTime = nullptr;
    static bool g_ltServerClockHooked = false;

    static LARGE_INTEGER g_masterClockFreq{};
    static LARGE_INTEGER g_masterClockLast{};
    static bool g_masterClockReady = false;
    static float g_masterFrameDelta = 0.010f;
    static double g_masterElapsed = 0.0;
    static float g_masterBaseServerTime = 0.0f;
    static thread_local bool g_inFixedServerTick = false;

    static void InitMasterClock()
    {
        if (g_masterClockReady)
            return;
        QueryPerformanceFrequency(&g_masterClockFreq);
        QueryPerformanceCounter(&g_masterClockLast);
        g_masterClockReady = g_masterClockFreq.QuadPart != 0;
        g_masterFrameDelta = 0.010f;
        g_masterElapsed = 0.0;
        g_masterClockFrames = 0;
    }

    static void AdvanceMasterClock()
    {
        InitMasterClock();
        if (!g_masterClockReady)
            return;

        LARGE_INTEGER now{};
        QueryPerformanceCounter(&now);
        double dt = static_cast<double>(now.QuadPart - g_masterClockLast.QuadPart) /
                    static_cast<double>(g_masterClockFreq.QuadPart);
        g_masterClockLast = now;

        // Do not let debugger/alt-tab stalls inject a huge one-frame simulation
        // step.  Normal AVP2 high-refresh deltas are far below this cap.
        if (!std::isfinite(dt) || dt <= 0.0)
            return;
        dt = std::min(dt, 0.100);
        g_masterFrameDelta = static_cast<float>(dt);
        g_masterElapsed += dt;
        ++g_masterClockFrames;
    }

    static float __fastcall HighRefresh_LTServerGetTime(void *, void *)
    {
        return g_masterBaseServerTime + static_cast<float>(g_masterElapsed);
    }

    static float __fastcall HighRefresh_LTServerGetFrameTime(void *, void *)
    {
        // Object.lto/server simulation consumes the fixed 10 ms server-step
        // delta only while the real 100 Hz server tick is executing.  Other
        // consumers continue to see the real outer-frame delta.
        return g_inFixedServerTick ? 0.010f : g_masterFrameDelta;
    }

    static bool IsLithtechProcess()
    {
        char path[MAX_PATH]{};
        const DWORD len = GetModuleFileNameA(nullptr, path, static_cast<DWORD>(sizeof(path)));
        if (!len || len >= sizeof(path))
            return false;
        const char *base = wp_strrchr_sep(path);
        base = base ? base + 1 : path;
        return _stricmp(base, "lithtech.exe") == 0;
    }

    static bool IsExecutableAddress(uintptr_t address)
    {
        return MemoryUtils::IsExecutable(address);
    }

    static void RestoreLTServerClockHooks()
    {
        if (g_ltServerClockHooked)
        {
            if (g_ltServerGetTimeSlot && *g_ltServerGetTimeSlot == reinterpret_cast<uintptr_t>(&HighRefresh_LTServerGetTime))
            {
                HookManager::Uninstall("timing.ltserver.get_time");
            }
            if (g_ltServerGetFrameTimeSlot && *g_ltServerGetFrameTimeSlot == reinterpret_cast<uintptr_t>(&HighRefresh_LTServerGetFrameTime))
            {
                HookManager::Uninstall("timing.ltserver.get_frame_time");
            }
        }

        g_ltServerInterface = nullptr;
        g_ltServerGetTimeSlot = nullptr;
        g_ltServerGetFrameTimeSlot = nullptr;
        g_originalLTServerGetTime = nullptr;
        g_originalLTServerGetFrameTime = nullptr;
        g_ltServerClockHooked = false;
        g_masterClockReady = false;
        g_masterFrameDelta = 0.010f;
        g_masterElapsed = 0.0;
        g_masterBaseServerTime = 0.0f;
        g_masterClockFrames = 0;
    }

    static void TryInstallLTServerClockHooks()
    {
        if (!g_installed || g_ltServerClockHooked || !g_lithtech)
            return;

        // Try to resolve the exact interface directly from lithtech.exe instead of
        // reverse-discovering Object.lto's module-local g_pLTServer copy.
        unsigned char *mgr = GetServerMgr();
        if (!mgr)
            return;

        void *server = *reinterpret_cast<void **>(mgr + kServerMgrLTServerOffset);
        if (!server)
            return;
        if (!MemoryUtils::IsReadable(reinterpret_cast<uintptr_t>(server)))
        {
            static bool loggedBadServer = false;
            if (LogIsSessionEnabled() && (!loggedBadServer))
            {
                LOG_SESSION("HighRefresh timing: lithtech CServerMgr+0x%X ILTServer pointer is not readable; global clock hook skipped",
                            static_cast<unsigned>(kServerMgrLTServerOffset));
                loggedBadServer = true;
            }
            return;
        }

        auto *vtable = *reinterpret_cast<uintptr_t **>(server);
        if (!vtable)
            return;

        constexpr size_t kGetTimeIndex = 53u;
        constexpr size_t kGetFrameTimeIndex = 54u;
        uintptr_t *timeSlot = vtable + kGetTimeIndex;
        uintptr_t *frameSlot = vtable + kGetFrameTimeIndex;
        const uintptr_t timeFn = *timeSlot;
        const uintptr_t frameFn = *frameSlot;
        if (!IsExecutableAddress(timeFn) || !IsExecutableAddress(frameFn))
        {
            static bool loggedBadSlots = false;
            if (LogIsSessionEnabled() && (!loggedBadSlots))
            {
                LOG_SESSION("HighRefresh timing: direct lithtech ILTServer slots 53/54 are not executable; hook skipped server=%p vtable=%p",
                            server, vtable);
                loggedBadSlots = true;
            }
            return;
        }

        g_ltServerInterface = server;
        g_originalLTServerGetTime = reinterpret_cast<LTServerGetTimeFn>(timeFn);
        g_originalLTServerGetFrameTime = reinterpret_cast<LTServerGetFrameTimeFn>(frameFn);

        // Preserve the engine's absolute time origin while replacing only the
        // rate source with one monotonic QPC domain.
        g_masterBaseServerTime = g_originalLTServerGetTime(server);
        InitMasterClock();

        void *originalTime = nullptr;
        void *originalFrame = nullptr;
        if (!HookManager::InstallPointerRaw("timing.ltserver.get_time", reinterpret_cast<void **>(timeSlot),
                                            reinterpret_cast<void *>(&HighRefresh_LTServerGetTime), &originalTime) ||
            !HookManager::InstallPointerRaw("timing.ltserver.get_frame_time", reinterpret_cast<void **>(frameSlot),
                                            reinterpret_cast<void *>(&HighRefresh_LTServerGetFrameTime), &originalFrame))
        {
            HookManager::Uninstall("timing.ltserver.get_frame_time");
            HookManager::Uninstall("timing.ltserver.get_time");
            g_ltServerInterface = nullptr;
            g_originalLTServerGetTime = nullptr;
            g_originalLTServerGetFrameTime = nullptr;
            LOG_SESSION("HighRefresh timing: failed to install direct lithtech ILTServer clock hooks");
            return;
        }

        g_ltServerGetTimeSlot = timeSlot;
        g_ltServerGetFrameTimeSlot = frameSlot;
        g_ltServerClockHooked = true;
        LOG_SESSION("HighRefresh timing: GLOBAL ILTServer clock installed DIRECT from lithtech.exe serverMgr=%p server=%p member=+0x%X GetTime=%p GetFrameTime=%p base=%.6f",
                    mgr, server, static_cast<unsigned>(kServerMgrLTServerOffset),
                    reinterpret_cast<void *>(timeFn), reinterpret_cast<void *>(frameFn), g_masterBaseServerTime);
    }

    static void ResetFixedSimulationAccumulators()
    {
        g_playerFixedTicks = 0;
        g_serverFixedTicks = 0;
        g_serverSkippedFrames = 0;
        g_clientModelClock = ClientVisualSubpassClock{};
        g_clientParticleClock = ClientVisualSubpassClock{};
        g_clientSpriteClock = ClientVisualSubpassClock{};
        g_clientVisual4Clock = ClientVisualSubpassClock{};
    }

    static unsigned char *GetClientMgr()
    {
        if (!g_lithtech)
            return nullptr;
        auto **base = reinterpret_cast<unsigned char **>(reinterpret_cast<unsigned char *>(g_lithtech) + kClientMgrRva);
        return base ? *base : nullptr;
    }

    static unsigned char *GetServerMgr()
    {
        if (!g_lithtech)
            return nullptr;
        auto **base = reinterpret_cast<unsigned char **>(reinterpret_cast<unsigned char *>(g_lithtech) + kServerMgrRva);
        return base ? *base : nullptr;
    }

    static void __cdecl HighRefresh_ClientSleep(DWORD milliseconds)
    {
        AdvanceMasterClock();
        SampleClientTimingRaw();
        // Leave CClientMgr::m_FrameTime completely untouched.  Talon's
        // model-animation and particle-system update passes consume +0x1368
        // directly.  The old d3d7fix millisecond quantizer was the last renderer
        // modification on that value and introduces frame-rate-dependent error at
        // unlocked refresh rates.
        if (g_clientSleep)
            g_clientSleep(milliseconds);
    }

    static void __cdecl HighRefresh_PdUpdate(void *shell)
    {
        // Leave CSHELL's private game-frame field alone.
        SampleGameTimingRaw();
        if (!g_pdUpdate)
            return;

        g_pdUpdate(shell);
        ++g_playerFixedTicks;
        ++g_playerSimulationSerial;
    }

    static bool PrepareClientVisualSubpassDt(void *clientMgr, ClientVisualSubpassClock &clock, float &outDt)
    {
        ++clock.calls;
        outDt = 0.0f;

        const uint64_t masterFrame = g_masterClockFrames;
        if (clock.lastMasterFrame == masterFrame)
        {
            ++clock.duplicateCalls;
            return false;
        }
        clock.lastMasterFrame = masterFrame;

        float realDt = g_masterFrameDelta;
        if (!std::isfinite(realDt) || realDt <= 0.0f)
            realDt = *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(clientMgr) + kClientMgrFrameTimeOffset);
        if (!std::isfinite(realDt) || realDt <= 0.0f)
            return false;

        realDt = std::min(realDt, 0.100f);
        clock.accumulator += static_cast<double>(realDt);

        // The retail model/particle/sprite integrators convert seconds to integer
        // milliseconds before doing any work.  Never feed them 0 ms: when the
        // render loop is faster than 1000 Hz, keep accumulating and simply defer
        // ONLY this time-integrating subpass.  The outer UpdateObjects bookkeeping
        // still runs on every render frame.
        const uint32_t wholeMs = static_cast<uint32_t>(
            std::floor(clock.accumulator * 1000.0 + 1.0e-9));
        if (wholeMs == 0)
        {
            ++clock.subMsSkips;
            return false;
        }

        outDt = static_cast<float>(wholeMs) * 0.001f;
        clock.accumulator -= static_cast<double>(wholeMs) * 0.001;
        if (clock.accumulator < 0.0)
            clock.accumulator = 0.0;
        return true;
    }

    static void RunClientVisualSubpass(void *clientMgr, ClientVisualSubpassFn fn,
                                       ClientVisualSubpassClock &clock)
    {
        if (!clientMgr || !fn)
            return;

        float passDt = 0.0f;
        if (!PrepareClientVisualSubpassDt(clientMgr, clock, passDt))
            return;

        float *frameTime = reinterpret_cast<float *>(
            reinterpret_cast<unsigned char *>(clientMgr) + kClientMgrFrameTimeOffset);
        const float saved = *frameTime;
        *frameTime = passDt;
        fn(clientMgr);
        *frameTime = saved;
        ++clock.executions;
    }

    static void __cdecl HighRefresh_ClientModelUpdate(void *clientMgr)
    {
        RunClientVisualSubpass(clientMgr, g_clientModelUpdate, g_clientModelClock);
    }

    static void __cdecl HighRefresh_ClientParticleUpdate(void *clientMgr)
    {
        RunClientVisualSubpass(clientMgr, g_clientParticleUpdate, g_clientParticleClock);
    }

    static void __cdecl HighRefresh_ClientSpriteUpdate(void *clientMgr)
    {
        RunClientVisualSubpass(clientMgr, g_clientSpriteUpdate, g_clientSpriteClock);
    }

    static void __cdecl HighRefresh_ClientVisual4Update(void *clientMgr)
    {
        RunClientVisualSubpass(clientMgr, g_clientVisual4Update, g_clientVisual4Clock);
    }

    static int __fastcall HighRefresh_ServerMgrUpdate(void *serverMgr, void *, uint32_t flags, float currentTime)
    {
        if (!g_serverMgrUpdate)
            return 0;

        ++g_serverFixedTicks; // diagnostic: real CServerMgr::Update calls
        SampleServerTimingRaw();
        return g_serverMgrUpdate(serverMgr, flags, currentTime);
    }

    static void __fastcall HighRefresh_ServerObjectUpdate(void *serverMgr, void *)
    {
        // IMPORTANT: the true raw dt is CServerMgr+0xAE0 here.  CServerMgr::Update
        // computes it near RVA 0x08355B, later clamps m_FrameTime (+0xABC) to a
        // minimum 10 ms, calls this object pass at RVA 0x083713, then clears +0xAE0
        // at RVA 0x08371E.  Reading +0xAE0 here therefore gives the exact unclamped
        // outer/server elapsed time we need.
        if (!g_serverObjectUpdate || !serverMgr)
            return;

        float raw = *reinterpret_cast<float *>(
            reinterpret_cast<unsigned char *>(serverMgr) + kServerMgrRawDeltaOffset);

        if (LogIsSessionEnabled())
            g_diagServerTrueFrame.Add(raw);

        // Invalid/paused/slow-frame path: preserve stock behavior.  At <=100 FPS
        // Talon's 10 ms minimum no longer causes over-advancement, so no gating is
        // needed.  IMPORTANT: this is *not* a synthetic 10 ms tick.  Retail/base
        // AVP2 commonly reaches this path at ~60 Hz (raw ~= 16.7 ms), and Object.lto
        // consumers such as Door ask ILTServer::GetFrameTime() for that real outer
        // delta.  Marking the stock pass as g_inFixedServerTick forced those objects
        // to see 10 ms and therefore run at roughly 60% speed.
        if (!std::isfinite(raw) || raw <= 0.0f || raw >= 0.0095f)
        {
            g_serverObjectAccumulator = 0.0;
            g_inFixedServerTick = false;
            g_serverObjectUpdate(serverMgr, nullptr);
            return;
        }

        g_serverObjectAccumulator += static_cast<double>(raw);
        if (g_serverObjectAccumulator + 1.0e-9 < 0.010)
        {
            ++g_serverSkippedFrames;
            return;
        }

        // Consume one 10 ms server-object step.  Do not burst multiple object
        // updates in one render frame; retain a small bounded remainder only.
        g_serverObjectAccumulator -= 0.010;
        if (g_serverObjectAccumulator > 0.040)
            g_serverObjectAccumulator = 0.040;

        g_inFixedServerTick = true;
        g_serverObjectUpdate(serverMgr, nullptr);
        g_inFixedServerTick = false;
    }

    static void __fastcall HighRefresh_UpdateSounds(void *serverMgr, float deltaTime)
    {
        // CServerMgr::Update clamps m_FrameTime (+0xABC) to a minimum
        // 10 ms before calling UpdateSounds.
        // Keep UpdateSounds full-rate (important for streaming/mixing/service),
        // but feed it the live unclamped delta from +0xAE0.  This is the same raw
        // value used by the object-pass accumulator and is still valid at
        // the 0x0836D7 call site.
        float soundDt = deltaTime;
        if (serverMgr)
        {
            const float raw = *reinterpret_cast<float *>(
                reinterpret_cast<unsigned char *>(serverMgr) + kServerMgrRawDeltaOffset);
            if (std::isfinite(raw) && raw >= 0.0f && raw <= 0.200f)
                soundDt = raw;
        }

        if (g_updateSounds)
            g_updateSounds(serverMgr, soundDt);
    }

    static bool FindCommunityLimiterBranch(HMODULE module, unsigned char *&branchOut, bool &alreadyDisabled)
    {
        branchOut = nullptr;
        alreadyDisabled = false;
        if (!module)
            return false;

        auto *base = reinterpret_cast<unsigned char *>(module);
        auto *dos = reinterpret_cast<IMAGE_DOS_HEADER *>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE)
            return false;
        auto *nt = reinterpret_cast<IMAGE_NT_HEADERS *>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return false;

        // Supplied community CSHELL limiter, immediately before its Sleep(0) loop:
        //   fld  qword ptr [esp+20h]
        //   fcomp qword ptr [esp+28h]
        //   fnstsw ax
        //   test ah,1
        //   je   limiter_done       ; 74 70
        // Changing this to EB 70 removes only the 60 FPS wait loop.
        static const unsigned char prefix[] = {
            0xDD, 0x44, 0x24, 0x20,
            0xDC, 0x5C, 0x24, 0x28,
            0xDF, 0xE0,
            0xF6, 0xC4, 0x01};

        size_t matches = 0;
        unsigned char *found = nullptr;
        auto *section = IMAGE_FIRST_SECTION(nt);
        for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
        {
            if ((section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0)
                continue;
            unsigned char *begin = base + section->VirtualAddress;
            const size_t size = section->Misc.VirtualSize;
            if (size < sizeof(prefix) + 10)
                continue;
            for (size_t j = 0; j + sizeof(prefix) + 10 <= size; ++j)
            {
                unsigned char *p = begin + j;
                if (std::memcmp(p, prefix, sizeof(prefix)) != 0)
                    continue;
                const unsigned char branch = p[sizeof(prefix)];
                if ((branch != 0x74 && branch != 0xEB) || p[sizeof(prefix) + 1] != 0x70)
                    continue;
                if (p[sizeof(prefix) + 2] != 0x8B || p[sizeof(prefix) + 3] != 0x3D)
                    continue;
                if (p[sizeof(prefix) + 8] != 0x6A || p[sizeof(prefix) + 9] != 0x00)
                    continue;
                ++matches;
                found = p + sizeof(prefix);
            }
        }

        if (matches != 1 || !found)
            return false;
        branchOut = found;
        alreadyDisabled = (*found == 0xEB);
        return true;
    }

    static void RestoreCommunityLimiter()
    {
        HookManager::Uninstall("timing.cshell.frame_limiter");
        g_cshellModule = nullptr;
        g_cshellLimiterBranch = nullptr;
        g_cshellLimiterDisabled = false;
    }
}

namespace HighRefreshTimingFix
{
    bool Install()
    {
        if (g_installed)
            return true;
        if (!IsLithtechProcess())
            return false;

        g_lithtech = GetModuleHandleA(nullptr);
        if (!g_lithtech)
            return false;

        auto *exeBase = reinterpret_cast<unsigned char *>(g_lithtech);
        unsigned char *clientSleepCall = exeBase + kClientSleepCallRva;
        unsigned char *pdUpdateCall = exeBase + kPdUpdateCallRva;
        unsigned char *serverMgrUpdateCall = exeBase + kServerMgrUpdateCallRva;
        unsigned char *serverObjectUpdateCall = exeBase + kServerObjectUpdateCallRva;

        if (MemoryUtils::ReadRelativeTarget(clientSleepCall, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kClientSleepRva) ||
            MemoryUtils::ReadRelativeTarget(pdUpdateCall, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kPdUpdateRva) ||
            MemoryUtils::ReadRelativeTarget(exeBase + kUpdateSoundsCallRva, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kUpdateSoundsRva) ||
            MemoryUtils::ReadRelativeTarget(serverMgrUpdateCall, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kServerMgrUpdateRva) ||
            MemoryUtils::ReadRelativeTarget(serverObjectUpdateCall, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kServerObjectUpdateRva) ||
            MemoryUtils::ReadRelativeTarget(exeBase + kClientObjectUpdateCall1Rva, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kClientObjectUpdateRva) ||
            MemoryUtils::ReadRelativeTarget(exeBase + kClientObjectUpdateCall2Rva, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kClientObjectUpdateRva) ||
            MemoryUtils::ReadRelativeTarget(exeBase + kClientModelUpdateCallRva, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kClientModelUpdateRva) ||
            MemoryUtils::ReadRelativeTarget(exeBase + kClientParticleUpdateCallRva, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kClientParticleUpdateRva) ||
            MemoryUtils::ReadRelativeTarget(exeBase + kClientSpriteUpdateCallRva, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kClientSpriteUpdateRva) ||
            MemoryUtils::ReadRelativeTarget(exeBase + kClientVisual4UpdateCallRva, 0xE8u) != reinterpret_cast<uintptr_t>(exeBase + kClientVisual4UpdateRva))
        {
            LOG_SESSION("HighRefresh timing: stock LithTech client call signatures did not match; fix not installed");
            g_lithtech = nullptr;
            return false;
        }

        g_clientSleep = reinterpret_cast<ClientSleepFn>(exeBase + kClientSleepRva);
        g_pdUpdate = reinterpret_cast<PdUpdateFn>(exeBase + kPdUpdateRva);
        g_updateSounds = reinterpret_cast<UpdateSoundsFn>(exeBase + kUpdateSoundsRva);
        g_serverMgrUpdate = reinterpret_cast<ServerMgrUpdateFn>(exeBase + kServerMgrUpdateRva);
        g_serverObjectUpdate = reinterpret_cast<ServerObjectUpdateFn>(exeBase + kServerObjectUpdateRva);
        g_clientModelUpdate = reinterpret_cast<ClientVisualSubpassFn>(exeBase + kClientModelUpdateRva);
        g_clientParticleUpdate = reinterpret_cast<ClientVisualSubpassFn>(exeBase + kClientParticleUpdateRva);
        g_clientSpriteUpdate = reinterpret_cast<ClientVisualSubpassFn>(exeBase + kClientSpriteUpdateRva);
        g_clientVisual4Update = reinterpret_cast<ClientVisualSubpassFn>(exeBase + kClientVisual4UpdateRva);

        if (!HookManager::InstallCall("timing.client_sleep", reinterpret_cast<uintptr_t>(clientSleepCall),
                                      reinterpret_cast<uintptr_t>(g_clientSleep), reinterpret_cast<uintptr_t>(&HighRefresh_ClientSleep)) ||
            !HookManager::InstallCall("timing.pd_update", reinterpret_cast<uintptr_t>(pdUpdateCall),
                                      reinterpret_cast<uintptr_t>(g_pdUpdate), reinterpret_cast<uintptr_t>(&HighRefresh_PdUpdate)) ||
            !HookManager::InstallCall("timing.update_sounds", reinterpret_cast<uintptr_t>(exeBase + kUpdateSoundsCallRva),
                                      reinterpret_cast<uintptr_t>(g_updateSounds), reinterpret_cast<uintptr_t>(&HighRefresh_UpdateSounds)) ||
            !HookManager::InstallCall("timing.client_model", reinterpret_cast<uintptr_t>(exeBase + kClientModelUpdateCallRva),
                                      reinterpret_cast<uintptr_t>(g_clientModelUpdate), reinterpret_cast<uintptr_t>(&HighRefresh_ClientModelUpdate)) ||
            !HookManager::InstallCall("timing.client_particle", reinterpret_cast<uintptr_t>(exeBase + kClientParticleUpdateCallRva),
                                      reinterpret_cast<uintptr_t>(g_clientParticleUpdate), reinterpret_cast<uintptr_t>(&HighRefresh_ClientParticleUpdate)) ||
            !HookManager::InstallCall("timing.client_sprite", reinterpret_cast<uintptr_t>(exeBase + kClientSpriteUpdateCallRva),
                                      reinterpret_cast<uintptr_t>(g_clientSpriteUpdate), reinterpret_cast<uintptr_t>(&HighRefresh_ClientSpriteUpdate)) ||
            !HookManager::InstallCall("timing.client_visual4", reinterpret_cast<uintptr_t>(exeBase + kClientVisual4UpdateCallRva),
                                      reinterpret_cast<uintptr_t>(g_clientVisual4Update), reinterpret_cast<uintptr_t>(&HighRefresh_ClientVisual4Update)) ||
            !HookManager::InstallCall("timing.server_mgr", reinterpret_cast<uintptr_t>(serverMgrUpdateCall),
                                      reinterpret_cast<uintptr_t>(g_serverMgrUpdate), reinterpret_cast<uintptr_t>(&HighRefresh_ServerMgrUpdate)) ||
            !HookManager::InstallCall("timing.server_object", reinterpret_cast<uintptr_t>(serverObjectUpdateCall),
                                      reinterpret_cast<uintptr_t>(g_serverObjectUpdate), reinterpret_cast<uintptr_t>(&HighRefresh_ServerObjectUpdate)))
        {
            HookManager::Uninstall("timing.server_object");
            HookManager::Uninstall("timing.server_mgr");
            HookManager::Uninstall("timing.client_visual4");
            HookManager::Uninstall("timing.client_sprite");
            HookManager::Uninstall("timing.client_particle");
            HookManager::Uninstall("timing.client_model");
            HookManager::Uninstall("timing.update_sounds");
            HookManager::Uninstall("timing.pd_update");
            HookManager::Uninstall("timing.client_sleep");
            g_clientSleep = nullptr;
            g_pdUpdate = nullptr;
            g_updateSounds = nullptr;
            g_serverMgrUpdate = nullptr;
            g_serverObjectUpdate = nullptr;
            g_clientModelUpdate = nullptr;
            g_clientParticleUpdate = nullptr;
            g_clientSpriteUpdate = nullptr;
            g_clientVisual4Update = nullptr;
            g_lithtech = nullptr;
            LOG_SESSION("HighRefresh timing: client-side install failed; all partial patches rolled back");
            return false;
        }

        g_installed = true;
        ResetTimingDiagnostics();
        ResetFixedSimulationAccumulators();
        g_clientModelClock = ClientVisualSubpassClock{};
        g_clientParticleClock = ClientVisualSubpassClock{};
        g_clientSpriteClock = ClientVisualSubpassClock{};
        g_clientVisual4Clock = ClientVisualSubpassClock{};
        LOG_SESSION("HighRefresh timing: CServerMgr::Update full-rate; v368 object-pass 100 Hz timing retained");
        LOG_SESSION("HighRefresh timing: server object pass uses live CServerMgr+0xAE0 raw dt and runs at real 100 Hz above 100 FPS, call RVA 0x%08X -> RVA 0x%08X", static_cast<unsigned>(kServerObjectUpdateCallRva), static_cast<unsigned>(kServerObjectUpdateRva));
        LOG_SESSION("HighRefresh timing: UpdateSounds remains full-rate but receives raw +0xAE0 dt instead of clamped 10 ms; audio lifetime clock corrected");
        LOG_SESSION("HighRefresh timing: outer CClientMgr::UpdateObjects remains completely stock/full-rate at both call sites");
        LOG_SESSION("HighRefresh timing: only model/particle/sprite time-integrating subpasses use whole-ms QPC error diffusion; zero-ms subpass calls are deferred, never injected into Talon trackers");
        LOG_SESSION("HighRefresh timing: raw timing histogram active while F10 logging is enabled; summaries every ~5 seconds");
        TickRuntimePatches();
        return true;
    }

    static void TryDisableCommunityFrameLimiter()
    {
        if (!g_installed || g_cshellLimiterDisabled)
            return;

        HMODULE cshell = GetModuleHandleA("cshell.dll");
        if (!cshell)
            return;

        unsigned char *branch = nullptr;
        bool alreadyDisabled = false;
        if (!FindCommunityLimiterBranch(cshell, branch, alreadyDisabled))
        {
            LOG_SESSION("HighRefresh timing: community CSHELL FrameLimit signature not found/ambiguous; limiter left untouched");
            // Do not scan repeatedly once the module exists but is an unknown build.
            g_cshellLimiterDisabled = true;
            return;
        }

        if (alreadyDisabled)
        {
            g_cshellModule = cshell;
            g_cshellLimiterDisabled = true;
            LOG_SESSION("HighRefresh timing: community CSHELL FrameLimit already disabled");
            return;
        }

        g_cshellModule = cshell;
        g_cshellLimiterBranch = branch;
        const unsigned char jmp = 0xEB;
        if (!HookManager::InstallBytes("timing.cshell.frame_limiter", reinterpret_cast<uintptr_t>(branch), &jmp, 1))
        {
            g_cshellModule = nullptr;
            g_cshellLimiterBranch = nullptr;
            LOG_SESSION("HighRefresh timing: failed to disable community CSHELL FrameLimit");
            return;
        }

        g_cshellLimiterDisabled = true;
        const uintptr_t rva = reinterpret_cast<uintptr_t>(branch) - reinterpret_cast<uintptr_t>(cshell);
        LOG_SESSION("HighRefresh timing: community CSHELL 60 FPS wait loop disabled at RVA 0x%08lX",
                    static_cast<unsigned long>(rva));
    }

    void TickRuntimePatches()
    {
        if (!g_installed)
            return;
        TryDisableCommunityFrameLimiter();
        TryInstallLTServerClockHooks();
    }

    float GetClientInterpolationAlpha()
    {
        return 1.0f;
    }

    unsigned long long GetClientSimulationSerial()
    {
        return static_cast<unsigned long long>(g_playerSimulationSerial);
    }

    bool InterpolateObjectTransform(const void *objectKey, unsigned objectId, unsigned objectType,
                                    const float inPos[3], const float inQuat[4],
                                    float outPos[3], float outQuat[4])
    {
        if (!objectKey || !inPos || !inQuat || !outPos || !outQuat || !g_installed)
            return false;

        const uint64_t serial = g_playerSimulationSerial;
        const float alpha = std::clamp(GetClientInterpolationAlpha(), 0.0f, 1.0f);
        ObjectInterpState &st = g_objectInterp[objectKey];

        auto copyCurrent = [&]()
        {
            for (int i = 0; i < 3; ++i)
                st.prevPos[i] = st.currPos[i] = inPos[i];
            for (int i = 0; i < 4; ++i)
                st.prevQuat[i] = st.currQuat[i] = inQuat[i];
            st.serial = serial;
            st.objectId = objectId;
            st.objectType = objectType;
            st.valid = true;
        };

        if (!st.valid || st.objectId != objectId || st.objectType != objectType || serial == 0)
        {
            copyCurrent();
            for (int i = 0; i < 3; ++i)
                outPos[i] = inPos[i];
            for (int i = 0; i < 4; ++i)
                outQuat[i] = inQuat[i];
            return false;
        }

        if (serial != st.serial)
        {
            if (serial == st.serial + 1)
            {
                for (int i = 0; i < 3; ++i)
                {
                    st.prevPos[i] = st.currPos[i];
                    st.currPos[i] = inPos[i];
                }
                for (int i = 0; i < 4; ++i)
                {
                    st.prevQuat[i] = st.currQuat[i];
                    st.currQuat[i] = inQuat[i];
                }
                st.serial = serial;
            }
            else
            {
                copyCurrent();
            }
        }

        const float dx = st.currPos[0] - st.prevPos[0];
        const float dy = st.currPos[1] - st.prevPos[1];
        const float dz = st.currPos[2] - st.prevPos[2];
        if (dx * dx + dy * dy + dz * dz > 256.0f * 256.0f)
        {
            copyCurrent();
            for (int i = 0; i < 3; ++i)
                outPos[i] = inPos[i];
            for (int i = 0; i < 4; ++i)
                outQuat[i] = inQuat[i];
            return false;
        }

        for (int i = 0; i < 3; ++i)
            outPos[i] = st.prevPos[i] + (st.currPos[i] - st.prevPos[i]) * alpha;

        float bq[4] = {st.currQuat[0], st.currQuat[1], st.currQuat[2], st.currQuat[3]};
        const float dot = st.prevQuat[0] * bq[0] + st.prevQuat[1] * bq[1] + st.prevQuat[2] * bq[2] + st.prevQuat[3] * bq[3];
        if (dot < 0.0f)
            for (float &v : bq)
                v = -v;
        for (int i = 0; i < 4; ++i)
            outQuat[i] = st.prevQuat[i] + (bq[i] - st.prevQuat[i]) * alpha;
        NormalizeQuat(outQuat);
        return true;
    }

    void Remove()
    {
        if (!g_installed)
            return;

        RestoreCommunityLimiter();
        RestoreLTServerClockHooks();
        HookManager::Uninstall("timing.server_object");
        HookManager::Uninstall("timing.server_mgr");
        HookManager::Uninstall("timing.client_visual4");
        HookManager::Uninstall("timing.client_sprite");
        HookManager::Uninstall("timing.client_particle");
        HookManager::Uninstall("timing.client_model");
        HookManager::Uninstall("timing.update_sounds");
        HookManager::Uninstall("timing.pd_update");
        HookManager::Uninstall("timing.client_sleep");

        g_clientSleep = nullptr;
        g_pdUpdate = nullptr;
        g_updateSounds = nullptr;
        g_serverMgrUpdate = nullptr;
        g_serverObjectUpdate = nullptr;
        g_clientModelUpdate = nullptr;
        g_clientParticleUpdate = nullptr;
        g_clientSpriteUpdate = nullptr;
        g_clientVisual4Update = nullptr;
        g_clientModelClock = ClientVisualSubpassClock{};
        g_clientParticleClock = ClientVisualSubpassClock{};
        g_clientSpriteClock = ClientVisualSubpassClock{};
        g_clientVisual4Clock = ClientVisualSubpassClock{};
        g_serverObjectAccumulator = 0.0;
        g_lithtech = nullptr;
        g_cshellLimiterDisabled = false;
        g_cshellModule = nullptr;
        g_cshellLimiterBranch = nullptr;
        ResetFixedSimulationAccumulators();
        g_playerSimulationSerial = 0;
        g_objectInterp.clear();
        g_installed = false;
        LOG_SESSION("HighRefresh timing: engine and CSHELL patches restored");
    }

    bool IsInstalled()
    {
        return g_installed;
    }
}
