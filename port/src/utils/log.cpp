#include "log.h"
#include <cstdio>
#include <cstdarg>
#include <mutex>
#include <string>
#include <array>
#include <atomic>

static HMODULE g_module = nullptr;
static std::mutex g_logMutex;
static FILE *g_logFile = nullptr;
static std::atomic_bool g_logEnabled{false};
static thread_local int g_callbackDepth = 0;

static std::array<uint64_t, static_cast<size_t>(HotEvent::Count)> g_hotCounts{};
static ULONGLONG g_lastSummaryMs = 0;

void LogSetModule(HMODULE module)
{
    g_module = module;
}

static std::string GetLogDirectory()
{
    char path[MAX_PATH] = {};
    if (g_module && GetModuleFileNameA(g_module, path, MAX_PATH))
    {
        char *slash = wp_strrchr_sep(path);
        if (slash)
        {
            slash[1] = '\0';
            return std::string(path);
        }
    }
    return std::string();
}

static std::string GetLogPath()
{
    SYSTEMTIME st{};
    GetLocalTime(&st);
    char name[96]{};
    std::snprintf(name, sizeof(name), "opengl_renderer_%04u%02u%02u-%02u%02u%02u.log",
                  st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    return GetLogDirectory() + name;
}

static void EnsureLogOpen()
{
    if (!g_logEnabled.load(std::memory_order_relaxed))
        return;
    if (g_logFile)
        return;

#if defined(_MSC_VER)
    fopen_s(&g_logFile, GetLogPath().c_str(), "a");
#else
    g_logFile = std::fopen(GetLogPath().c_str(), "a");
#endif
    if (g_logFile)
    {
        static char s_buffer[64 * 1024];
        setvbuf(g_logFile, s_buffer, _IOFBF, sizeof(s_buffer));
    }
}

void LogSetSessionEnabled(bool enabled)
{
    std::lock_guard<std::mutex> guard(g_logMutex);
    if (enabled == g_logEnabled.load(std::memory_order_relaxed))
        return;

    if (!enabled)
    {
        if (g_logFile)
        {
            SYSTEMTIME st{};
            GetLocalTime(&st);
            std::fprintf(g_logFile, "[%02u:%02u:%02u.%03u] ==== F10 SESSION LOGGING DISABLED ====\n",
                         st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
            std::fflush(g_logFile);
            std::fclose(g_logFile);
            g_logFile = nullptr;
        }
        g_logEnabled.store(false, std::memory_order_release);
        return;
    }

    g_logEnabled.store(true, std::memory_order_release);
    EnsureLogOpen();
    if (g_logFile)
    {
        SYSTEMTIME st{};
        GetLocalTime(&st);
        std::fprintf(g_logFile, "[%02u:%02u:%02u.%03u] ==== F10 SESSION LOGGING ENABLED ====\n",
                     st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        std::fflush(g_logFile);
    }
}

bool LogIsSessionEnabled()
{
    return g_logEnabled.load(std::memory_order_acquire);
}

void Log(const char *fmt, ...)
{
    // Fast reject before the mutex and before touching the filesystem.
    if (!g_logEnabled.load(std::memory_order_acquire))
        return;

    std::lock_guard<std::mutex> guard(g_logMutex);
    if (!g_logEnabled.load(std::memory_order_relaxed))
        return;
    EnsureLogOpen();
    if (!g_logFile)
        return;

    SYSTEMTIME st{};
    GetLocalTime(&st);
    std::fprintf(g_logFile, "[%02u:%02u:%02u.%03u] ",
                 st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

    for (int i = 0; i < g_callbackDepth; ++i)
        std::fputs("  ", g_logFile);

    va_list args;
    va_start(args, fmt);
    std::vfprintf(g_logFile, fmt, args);
    va_end(args);

    std::fputc('\n', g_logFile);
}

void LogFlush()
{
    std::lock_guard<std::mutex> guard(g_logMutex);
    if (g_logFile)
        std::fflush(g_logFile);
}

void LogFlushMarker(const char *marker)
{
    if (!LogIsSessionEnabled())
        return;
    Log("==== %s ====", marker ? marker : "<null>");
    LogFlush();
}

void LogHotEvent(HotEvent event)
{
    if (!g_logEnabled.load(std::memory_order_relaxed))
        return;
    const size_t i = static_cast<size_t>(event);
    if (i < g_hotCounts.size())
        ++g_hotCounts[i];
}

void LogHotSummaryIfDue()
{
    if (!g_logEnabled.load(std::memory_order_relaxed))
        return;
    const ULONGLONG now = GetTickCount64();
    if (g_lastSummaryMs != 0 && now - g_lastSummaryMs < 1000)
        return;

    g_lastSummaryMs = now;

    const auto blit = g_hotCounts[static_cast<size_t>(HotEvent::BlitToScreen)];
    const auto lock = g_hotCounts[static_cast<size_t>(HotEvent::LockSurface)];
    const auto unlock = g_hotCounts[static_cast<size_t>(HotEvent::UnlockSurface)];
    const auto start2d = g_hotCounts[static_cast<size_t>(HotEvent::StartOptimized2D)];
    const auto end2d = g_hotCounts[static_cast<size_t>(HotEvent::EndOptimized2D)];
    const auto clear = g_hotCounts[static_cast<size_t>(HotEvent::Clear)];
    const auto swap = g_hotCounts[static_cast<size_t>(HotEvent::SwapBuffers)];

    if (blit || lock || unlock || start2d || end2d || clear || swap)
    {
        Log("HOT[1s] blit=%llu lockSurf=%llu unlockSurf=%llu start2D=%llu end2D=%llu clear=%llu swap=%llu",
            static_cast<unsigned long long>(blit),
            static_cast<unsigned long long>(lock),
            static_cast<unsigned long long>(unlock),
            static_cast<unsigned long long>(start2d),
            static_cast<unsigned long long>(end2d),
            static_cast<unsigned long long>(clear),
            static_cast<unsigned long long>(swap));

        g_hotCounts.fill(0);
    }
}

CallbackTrace::CallbackTrace(const char *name, bool enabled)
    : m_name(name), m_enabled(enabled && LogIsSessionEnabled())
{
    if (!m_enabled)
        return;

    Log(">> %s", m_name);
    ++g_callbackDepth;
}

CallbackTrace::~CallbackTrace()
{
    if (!m_enabled)
        return;

    --g_callbackDepth;
    Log("<< %s", m_name);
}
