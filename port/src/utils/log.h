#pragma once
#include <windows.h>
#include <cstdint>

void LogSetModule(HMODULE module);
void LogSetSessionEnabled(bool enabled);
bool LogIsSessionEnabled();
void Log(const char *fmt, ...);

// Lazy session logger: the session flag is tested before C++ evaluates any
// format arguments. Guard any diagnostic preparation outside the macro with
// LogIsSessionEnabled() BEFORE scans, formatting, lookups, or budget updates.
// Keep rendering work and performance-overlay statistics outside those guards.
#define LOG_SESSION(...)           \
    do                             \
    {                              \
        if (LogIsSessionEnabled()) \
            Log(__VA_ARGS__);      \
    } while (0)
void LogFlushMarker(const char *marker);
void LogFlush();

enum class HotEvent : uint32_t
{
    BlitToScreen = 0,
    LockSurface,
    UnlockSurface,
    StartOptimized2D,
    EndOptimized2D,
    Clear,
    SwapBuffers,
    Count
};

void LogHotEvent(HotEvent event);
void LogHotSummaryIfDue();

class CallbackTrace
{
public:
    explicit CallbackTrace(const char *name, bool enabled = true);
    ~CallbackTrace();

private:
    const char *m_name;
    bool m_enabled;
};
