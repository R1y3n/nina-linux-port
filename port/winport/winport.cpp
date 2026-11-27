/* winport.cpp - native implementations of the Win32 calls the renderer needs that have no host equivalent. */
#define INITGUID
#include <windows.h>
#include <ddraw.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <dlfcn.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <string>
extern "C" DWORD WINAPI host_GetModuleFileNameA(HMODULE, LPSTR, DWORD) __asm__("W_GetModuleFileNameA");
/* ---- timing / threads ---- */
extern "C" BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *v) { timespec t; clock_gettime(CLOCK_MONOTONIC, &t); v->QuadPart = (LONGLONG)t.tv_sec * 1000000000LL + t.tv_nsec; return TRUE; }
extern "C" BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *v) { v->QuadPart = 1000000000LL; return TRUE; }
extern "C" ULONGLONG WINAPI GetTickCount64(void) { timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return (ULONGLONG)t.tv_sec * 1000ULL + t.tv_nsec / 1000000; }
extern "C" DWORD WINAPI GetTickCount(void) { return (DWORD)GetTickCount64(); }
extern "C" DWORD WINAPI GetCurrentThreadId(void) { return (DWORD)syscall(SYS_gettid); }
extern "C" void WINAPI Sleep(DWORD ms) { if (!ms) sched_yield(); else { timespec r{(time_t)(ms / 1000), (long)(ms % 1000) * 1000000L}; while (nanosleep(&r, &r) && errno == EINTR) {} } }
extern "C" BOOL WINAPI SwitchToThread(void) { return sched_yield() == 0; }
extern "C" void WINAPI AcquireSRWLockExclusive(SRWLOCK *l) { while (__sync_lock_test_and_set((volatile int *)&l->Ptr, 1)) sched_yield(); }
extern "C" void WINAPI ReleaseSRWLockExclusive(SRWLOCK *l) { __sync_lock_release((volatile int *)&l->Ptr); }
extern "C" void WINAPI OutputDebugStringA(LPCSTR s) { if (getenv("LT_TRACE")) fputs(s, stderr); }
extern "C" void WINAPI GetLocalTime(SYSTEMTIME *st) { timespec t; clock_gettime(CLOCK_REALTIME, &t); tm lt; localtime_r(&t.tv_sec, &lt); st->wYear = lt.tm_year + 1900; st->wMonth = lt.tm_mon + 1; st->wDayOfWeek = lt.tm_wday; st->wDay = lt.tm_mday; st->wHour = lt.tm_hour; st->wMinute = lt.tm_min; st->wSecond = lt.tm_sec; st->wMilliseconds = t.tv_nsec / 1000000; }
extern "C" DWORD WINAPI GetEnvironmentVariableA(LPCSTR n, LPSTR b, DWORD sz) { const char *v = getenv(n); if (!v) return 0; DWORD l = (DWORD)strlen(v); if (l + 1 > sz) return l + 1; memcpy(b, v, l + 1); return l; }
extern "C" BOOL WINAPI DisableThreadLibraryCalls(HMODULE) { return TRUE; }
extern "C" BOOL WINAPI SetLastErrorProxy(DWORD);
extern "C" void WINAPI host_SetLastError(DWORD) __asm__("W_SetLastError");
extern "C" BOOL WINAPI CreateDirectoryA(LPCSTR p, void *) { std::string s(p); for (char &c : s) if (c == '\\') c = '/'; if (!mkdir(s.c_str(), 0755)) return TRUE; if (errno == EEXIST) host_SetLastError(ERROR_ALREADY_EXISTS); return FALSE; }
/* ---- module identity: this shared object is the 'renderer module' ---- */
extern "C" DWORD WINAPI GetModuleFileNameA(HMODULE h, LPSTR buf, DWORD sz)
{
    extern HMODULE g_hModule;
    if (h && h == g_hModule) { Dl_info di; if (dladdr((void *)&GetModuleFileNameA, &di) && di.dli_fname) { DWORD l = (DWORD)strlen(di.dli_fname); if (l >= sz) l = sz - 1; memcpy(buf, di.dli_fname, l); buf[l] = 0; return l; } return 0; }
    return host_GetModuleFileNameA(h, buf, sz);
}
/* ---- resources (embedded shaders + name string) ---- */
struct WpRes { int id; const unsigned char *data; unsigned size; };
extern const WpRes g_wp_resources[]; extern const unsigned g_wp_resource_count;
extern "C" HRSRC WINAPI FindResourceW(HMODULE, LPCWSTR name, LPCWSTR type) { if ((uintptr_t)type != 10) return nullptr; for (unsigned i = 0; i < g_wp_resource_count; i++) if ((uintptr_t)name == (uintptr_t)g_wp_resources[i].id) return (HRSRC)&g_wp_resources[i]; host_SetLastError(1814); return nullptr; }
extern "C" DWORD WINAPI SizeofResource(HMODULE, HRSRC r) { return r ? ((const WpRes *)r)->size : 0; }
extern "C" HGLOBAL WINAPI LoadResource(HMODULE, HRSRC r) { return (HGLOBAL)r; }
extern "C" LPVOID WINAPI LockResource(HGLOBAL g) { return g ? (LPVOID)((const WpRes *)g)->data : nullptr; }
extern "C" int WINAPI LoadStringA(HINSTANCE, UINT id, LPSTR buf, int n) { if (id != 5 || n <= 0) return 0; const char s[] = "LithFAQ OpenGL Renderer"; int l = (int)sizeof(s) - 1; if (l >= n) l = n - 1; memcpy(buf, s, l); buf[l] = 0; return l; }
/* ---- registry: none on Linux (callers fall back to GL strings) ---- */
extern "C" LONG WINAPI RegOpenKeyExA(HKEY, LPCSTR, DWORD, DWORD, HKEY *) { return ERROR_FILE_NOT_FOUND; }
extern "C" LONG WINAPI RegQueryValueExA(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD) { return ERROR_FILE_NOT_FOUND; }
extern "C" LONG WINAPI RegCloseKey(HKEY) { return ERROR_SUCCESS; }
extern "C" BOOL WINAPI IsWow64Process(HANDLE, BOOL *w) { if (w) *w = FALSE; return TRUE; }
/* ---- window geometry helpers: the host's SDL window has no non-client area ---- */
extern "C" BOOL WINAPI AdjustWindowRectEx(RECT *, DWORD, BOOL, DWORD) { return TRUE; }
extern "C" int WINAPI MapWindowPoints(HWND from, HWND to, POINT *pts, UINT n)
{
    for (UINT i = 0; i < n; i++) { if (from) ClientToScreen(from, &pts[i]); if (to) ScreenToClient(to, &pts[i]); }
    return 0;
}
/* ---- secure CRT string functions ---- */
extern "C" int strncpy_s(char *d, size_t dsz, const char *s, size_t cnt)
{
    if (!d || !dsz) return 22; if (!s) { d[0] = 0; return 22; }
    size_t n = strnlen(s, cnt == _TRUNCATE ? dsz : cnt);
    if (n >= dsz) { if (cnt != _TRUNCATE) { d[0] = 0; return 34; } n = dsz - 1; }
    memcpy(d, s, n); d[n] = 0; return (cnt == _TRUNCATE && strnlen(s, dsz) >= dsz) ? 80 : 0;
}
extern "C" int strcpy_s(char *d, size_t dsz, const char *s) { if (!d || !s || strlen(s) >= dsz) { if (d && dsz) d[0] = 0; return 34; } strcpy(d, s); return 0; }
extern "C" int strcat_s(char *d, size_t dsz, const char *s) { size_t dl = strnlen(d, dsz); if (dl + strlen(s) >= dsz) { d[0] = 0; return 34; } strcat(d, s); return 0; }
extern "C" int _vsnprintf_s(char *b, size_t sz, size_t cnt, const char *f, va_list a)
{
    if (!b || !sz) return -1; size_t lim = cnt == _TRUNCATE ? sz - 1 : (cnt < sz - 1 ? cnt : sz - 1);
    int r = vsnprintf(b, lim + 1, f, a); b[lim] = 0; if (r < 0 || (size_t)r > lim) return -1; return r;
}
extern "C" int _snprintf_s(char *b, size_t sz, size_t cnt, const char *f, ...) { va_list a; va_start(a, f); int r = _vsnprintf_s(b, sz, cnt, f, a); va_end(a); return r; }
