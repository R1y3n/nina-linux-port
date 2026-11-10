#pragma once
/* winport: the Win32 surface used by the AVP2 OpenGL renderer, for a native i386 Linux build (.ren as ELF shared object).
 * Window / GL context / input / cursor / display / memory APIs resolve to the host's W_* exports (lithtech_linux, SDL2-backed);
 * pure-libc ones (timing, SRW locks, snprintf variants, resources) are implemented in winport.cpp. */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>
#ifdef __cplusplus
#define WP_C extern "C"
#else
#define WP_C extern
#endif
#define WINAPI __attribute__((stdcall))
#define CALLBACK __attribute__((stdcall))
#define APIENTRY
#ifndef __stdcall
#define __stdcall __attribute__((stdcall))
#endif
#ifndef __cdecl
#define __cdecl __attribute__((cdecl))
#endif
#ifndef __thiscall
#define __thiscall __attribute__((thiscall))
#endif
#ifndef __fastcall
#define __fastcall __attribute__((fastcall))
#endif
#define __declspec(x)
#define __forceinline inline __attribute__((always_inline))
#define __int64 long long
#define _stricmp strcasecmp
#define _strnicmp strncasecmp
#define _TRUNCATE ((size_t)-1)
typedef unsigned char BYTE; typedef unsigned short WORD; typedef unsigned long DWORD; typedef int BOOL; typedef long LONG; typedef unsigned long ULONG;
typedef unsigned int UINT; typedef int INT; typedef short SHORT; typedef unsigned short USHORT; typedef char CHAR; typedef wchar_t WCHAR;
typedef float FLOAT; typedef unsigned char BOOLEAN; typedef void VOID; typedef long long LONGLONG; typedef unsigned long long ULONGLONG;
typedef void *HANDLE; typedef HANDLE HMODULE, HINSTANCE, HWND, HDC, HGLRC, HMONITOR, HICON, HCURSOR, HBRUSH, HMENU, HKEY, HGDIOBJ, HRSRC, HGLOBAL, HPALETTE, HRGN, HBITMAP;
typedef void *LPVOID, *PVOID; typedef const void *LPCVOID; typedef const char *LPCSTR; typedef char *LPSTR; typedef const wchar_t *LPCWSTR; typedef wchar_t *LPWSTR;
typedef uintptr_t WPARAM, UINT_PTR, ULONG_PTR, DWORD_PTR, SIZE_T_; typedef intptr_t LPARAM, LRESULT, LONG_PTR, INT_PTR; typedef size_t SIZE_T;
typedef int (WINAPI *FARPROC)(void); typedef DWORD *LPDWORD, *PDWORD; typedef BYTE *LPBYTE; typedef long HRESULT; typedef WORD ATOM; typedef DWORD COLORREF;
typedef BOOL *LPBOOL; typedef LONG *LPLONG, *PLONG; typedef UINT *PUINT; typedef HANDLE *PHANDLE; typedef const DWORD *LPCDWORD; typedef WORD *LPWORD; typedef const WCHAR *PCWSTR;
typedef ULONG_PTR *PULONG_PTR;
#define TRUE 1
#define FALSE 0
#define MAX_PATH 260
#define INVALID_HANDLE_VALUE ((HANDLE)(intptr_t)-1)
#define LOWORD(l) ((WORD)((DWORD_PTR)(l)&0xffff))
#define HIWORD(l) ((WORD)(((DWORD_PTR)(l)>>16)&0xffff))
#define MAKELONG(a,b) ((LONG)(((WORD)((DWORD_PTR)(a)&0xffff))|((DWORD)((WORD)((DWORD_PTR)(b)&0xffff)))<<16))
#define MAKEINTRESOURCEW(i) ((LPWSTR)((ULONG_PTR)((WORD)(i))))
#define MAKEINTRESOURCEA(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))
#define MAKEINTRESOURCE MAKEINTRESOURCEA
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#define GET_WHEEL_DELTA_WPARAM(wp) ((short)HIWORD(wp))
#define GET_XBUTTON_WPARAM(wp) (HIWORD(wp))
#define S_OK ((HRESULT)0)
#define S_FALSE ((HRESULT)1)
#define E_NOTIMPL ((HRESULT)0x80004001L)
#define E_NOINTERFACE ((HRESULT)0x80004002L)
#define E_POINTER ((HRESULT)0x80004003L)
#define E_FAIL ((HRESULT)0x80004005L)
#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#define E_INVALIDARG ((HRESULT)0x80070057L)
#define SUCCEEDED(h) ((HRESULT)(h)>=0)
#define FAILED(h) ((HRESULT)(h)<0)
#define ERROR_ALREADY_EXISTS 183
#define DLL_PROCESS_ATTACH 1
#define DLL_PROCESS_DETACH 0
#define DLL_THREAD_ATTACH 2
#define DLL_THREAD_DETACH 3
typedef struct { LONG x, y; } POINT, *LPPOINT;
typedef struct { LONG left, top, right, bottom; } RECT, *LPRECT; typedef const RECT *LPCRECT;
typedef struct { LONG cx, cy; } SIZE;
typedef struct { DWORD cbSize; RECT rcMonitor, rcWork; DWORD dwFlags; } MONITORINFO, *LPMONITORINFO;
typedef struct { WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds; } SYSTEMTIME;
typedef union _LARGE_INTEGER { struct { DWORD LowPart; LONG HighPart; }; struct { DWORD LowPart; LONG HighPart; } u; LONGLONG QuadPart; } LARGE_INTEGER;
typedef union _ULARGE_INTEGER { struct { DWORD LowPart; DWORD HighPart; }; ULONGLONG QuadPart; } ULARGE_INTEGER;
typedef int WINBOOL;
#define DECL_WINELIB_TYPE_AW(x)
typedef struct { PVOID Ptr; } SRWLOCK, *PSRWLOCK;
#define SRWLOCK_INIT {0}
typedef struct { PVOID BaseAddress, AllocationBase; DWORD AllocationProtect; SIZE_T RegionSize; DWORD State, Protect, Type; } MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;
typedef struct { WORD nSize, nVersion; DWORD dwFlags; BYTE iPixelType, cColorBits, cRedBits, cRedShift, cGreenBits, cGreenShift, cBlueBits, cBlueShift, cAlphaBits, cAlphaShift, cAccumBits, cAccumRedBits, cAccumGreenBits, cAccumBlueBits, cAccumAlphaBits, cDepthBits, cStencilBits, cAuxBuffers, iLayerType, bReserved; DWORD dwLayerMask, dwVisibleMask, dwDamageMask; } PIXELFORMATDESCRIPTOR;
typedef struct { BYTE dmDeviceName[32]; WORD dmSpecVersion, dmDriverVersion, dmSize, dmDriverExtra; DWORD dmFields; LONG dmPositionX, dmPositionY; DWORD dmDisplayOrientation, dmDisplayFixedOutput; short dmColor, dmDuplex, dmYResolution, dmTTOption, dmCollate; BYTE dmFormName[32]; WORD dmLogPixels; DWORD dmBitsPerPel, dmPelsWidth, dmPelsHeight, dmDisplayFlags, dmDisplayFrequency, dmICMMethod, dmICMIntent, dmMediaType, dmDitherType, dmReserved1, dmReserved2, dmPanningWidth, dmPanningHeight; } DEVMODEA_RAW;
typedef struct { char dmDeviceName[32]; WORD dmSpecVersion, dmDriverVersion, dmSize, dmDriverExtra; DWORD dmFields; POINT dmPosition; DWORD dmDisplayOrientation, dmDisplayFixedOutput; short dmColor, dmDuplex, dmYResolution, dmTTOption, dmCollate; char dmFormName[32]; WORD dmLogPixels; DWORD dmBitsPerPel, dmPelsWidth, dmPelsHeight, dmDisplayFlags, dmDisplayFrequency, dmICMMethod, dmICMIntent, dmMediaType, dmDitherType, dmReserved1, dmReserved2, dmPanningWidth, dmPanningHeight; } DEVMODEA, DEVMODE;
typedef struct { DWORD cb; char DeviceName[32]; char DeviceString[128]; DWORD StateFlags; char DeviceID[128]; char DeviceKey[128]; } DISPLAY_DEVICEA, DISPLAY_DEVICE;
typedef struct { DWORD nLength; LPVOID lpSecurityDescriptor; BOOL bInheritHandle; } SECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;
typedef struct { DWORD ExceptionCode, ExceptionFlags; void *ExceptionRecord, *ExceptionAddress; DWORD NumberParameters; ULONG_PTR ExceptionInformation[15]; } EXCEPTION_RECORD;
typedef struct { EXCEPTION_RECORD *ExceptionRecord; void *ContextRecord; } EXCEPTION_POINTERS;
typedef LONG (WINAPI *LPTOP_LEVEL_EXCEPTION_FILTER)(EXCEPTION_POINTERS *);
/* constants */
#define MEM_COMMIT 0x1000
#define MEM_RESERVE 0x2000
#define MEM_RELEASE 0x8000
#define PAGE_NOACCESS 0x01
#define PAGE_READONLY 0x02
#define PAGE_READWRITE 0x04
#define PAGE_WRITECOPY 0x08
#define PAGE_EXECUTE 0x10
#define PAGE_EXECUTE_READ 0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD 0x100
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define SWP_NOSIZE 1
#define SWP_NOMOVE 2
#define SWP_NOZORDER 4
#define SWP_NOACTIVATE 0x10
#define SWP_FRAMECHANGED 0x20
#define SWP_SHOWWINDOW 0x40
#define HWND_TOP ((HWND)0)
#define HWND_BOTTOM ((HWND)1)
#define HWND_TOPMOST ((HWND)-1)
#define HWND_NOTOPMOST ((HWND)-2)
#define GWL_STYLE (-16)
#define GWL_EXSTYLE (-20)
#define GWL_WNDPROC (-4)
#define GWLP_WNDPROC (-4)
#define MONITOR_DEFAULTTONULL 0
#define MONITOR_DEFAULTTOPRIMARY 1
#define MONITOR_DEFAULTTONEAREST 2
#define PFD_TYPE_RGBA 0
#define PFD_MAIN_PLANE 0
#define PFD_DOUBLEBUFFER 1
#define PFD_DRAW_TO_WINDOW 4
#define PFD_SUPPORT_OPENGL 0x20
#define PFD_SWAP_COPY 0x400
#define PFD_SWAP_EXCHANGE 0x200
#define WM_KEYDOWN 0x100
#define WM_KEYUP 0x101
#define WM_CHAR 0x102
#define WM_SYSKEYDOWN 0x104
#define WM_SYSKEYUP 0x105
#define WM_MOUSEMOVE 0x200
#define WM_LBUTTONDOWN 0x201
#define WM_LBUTTONUP 0x202
#define WM_LBUTTONDBLCLK 0x203
#define WM_RBUTTONDOWN 0x204
#define WM_RBUTTONUP 0x205
#define WM_RBUTTONDBLCLK 0x206
#define WM_MBUTTONDOWN 0x207
#define WM_MBUTTONUP 0x208
#define WM_MBUTTONDBLCLK 0x209
#define WM_MOUSEWHEEL 0x20A
#define WM_XBUTTONDOWN 0x20B
#define WM_XBUTTONUP 0x20C
#define WM_XBUTTONDBLCLK 0x20D
#define WM_MOUSEHWHEEL 0x20E
#define WM_INPUT 0x00FF
#define RIM_INPUT 0
#define GET_RAWINPUT_CODE_WPARAM(wp) ((wp)&0xff)
#define VK_LBUTTON 1
#define VK_RBUTTON 2
#define VK_MBUTTON 4
#define VK_XBUTTON1 5
#define VK_XBUTTON2 6
#define VK_BACK 8
#define VK_TAB 9
#define VK_RETURN 13
#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_ESCAPE 0x1B
#define VK_SPACE 0x20
#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B
#define CDS_FULLSCREEN 4
#define CDS_TEST 2
#define DISP_CHANGE_SUCCESSFUL 0
#define ENUM_CURRENT_SETTINGS ((DWORD)-1)
#define ENUM_REGISTRY_SETTINGS ((DWORD)-2)
#define DM_PELSWIDTH 0x80000
#define DM_PELSHEIGHT 0x100000
#define DM_BITSPERPEL 0x40000
#define DM_DISPLAYFREQUENCY 0x400000
#define DISPLAY_DEVICE_ATTACHED_TO_DESKTOP 1
#define DISPLAY_DEVICE_PRIMARY_DEVICE 4
#define GET_MODULE_HANDLE_EX_FLAG_PIN 1
#define PROV_RSA_AES 24
#define CRYPT_VERIFYCONTEXT 0xF0000000
#define CALG_SHA_256 0x800C
#define HP_HASHVAL 2
#define IMAGE_DOS_SIGNATURE 0x5A4D
#define IMAGE_NT_SIGNATURE 0x00004550
#define IMAGE_DIRECTORY_ENTRY_IMPORT 1
#define IMAGE_SCN_MEM_EXECUTE 0x20000000
#define IMAGE_ORDINAL_FLAG32 0x80000000
#define IMAGE_SNAP_BY_ORDINAL(o) (((o)&IMAGE_ORDINAL_FLAG32)!=0)
#define EXCEPTION_ACCESS_VIOLATION 0xC0000005
#define EXCEPTION_CONTINUE_SEARCH 0
typedef struct { WORD e_magic, e_cblp, e_cp, e_crlc, e_cparhdr, e_minalloc, e_maxalloc, e_ss, e_sp, e_csum, e_ip, e_cs, e_lfarlc, e_ovno, e_res[4], e_oemid, e_oeminfo, e_res2[10]; LONG e_lfanew; } IMAGE_DOS_HEADER;
typedef struct { WORD Machine, NumberOfSections; DWORD TimeDateStamp, PointerToSymbolTable, NumberOfSymbols; WORD SizeOfOptionalHeader, Characteristics; } IMAGE_FILE_HEADER;
typedef struct { DWORD VirtualAddress, Size; } IMAGE_DATA_DIRECTORY;
typedef struct { WORD Magic; BYTE MajorLinkerVersion, MinorLinkerVersion; DWORD SizeOfCode, SizeOfInitializedData, SizeOfUninitializedData, AddressOfEntryPoint, BaseOfCode, BaseOfData, ImageBase, SectionAlignment, FileAlignment; WORD MajorOperatingSystemVersion, MinorOperatingSystemVersion, MajorImageVersion, MinorImageVersion, MajorSubsystemVersion, MinorSubsystemVersion; DWORD Win32VersionValue, SizeOfImage, SizeOfHeaders, CheckSum; WORD Subsystem, DllCharacteristics; DWORD SizeOfStackReserve, SizeOfStackCommit, SizeOfHeapReserve, SizeOfHeapCommit, LoaderFlags, NumberOfRvaAndSizes; IMAGE_DATA_DIRECTORY DataDirectory[16]; } IMAGE_OPTIONAL_HEADER32, IMAGE_OPTIONAL_HEADER;
typedef struct { DWORD Signature; IMAGE_FILE_HEADER FileHeader; IMAGE_OPTIONAL_HEADER32 OptionalHeader; } IMAGE_NT_HEADERS32, IMAGE_NT_HEADERS;
typedef struct { BYTE Name[8]; union { DWORD PhysicalAddress, VirtualSize; } Misc; DWORD VirtualAddress, SizeOfRawData, PointerToRawData, PointerToRelocations, PointerToLinenumbers; WORD NumberOfRelocations, NumberOfLinenumbers; DWORD Characteristics; } IMAGE_SECTION_HEADER;
#define IMAGE_FIRST_SECTION(nt) ((IMAGE_SECTION_HEADER*)((ULONG_PTR)(nt)+offsetof(IMAGE_NT_HEADERS32,OptionalHeader)+((IMAGE_NT_HEADERS32*)(nt))->FileHeader.SizeOfOptionalHeader))
typedef struct { union { DWORD Characteristics, OriginalFirstThunk; }; DWORD TimeDateStamp, ForwarderChain, Name, FirstThunk; } IMAGE_IMPORT_DESCRIPTOR;
typedef struct { union { DWORD ForwarderString, Function, Ordinal, AddressOfData; } u1; } IMAGE_THUNK_DATA32, IMAGE_THUNK_DATA;
typedef struct { WORD Hint; BYTE Name[1]; } IMAGE_IMPORT_BY_NAME;
/* ---- host-provided (resolved against lithtech_linux's W_* exports; SDL2-backed) ---- */
#define WP_HOST(ret, name, args) WP_C ret WINAPI name args __asm__("W_" #name)
WP_HOST(HDC, GetDC, (HWND)); WP_HOST(int, ReleaseDC, (HWND, HDC)); WP_HOST(BOOL, GetClientRect, (HWND, RECT *)); WP_HOST(BOOL, GetWindowRect, (HWND, RECT *));
WP_HOST(BOOL, ClientToScreen, (HWND, POINT *)); WP_HOST(BOOL, ScreenToClient, (HWND, POINT *)); WP_HOST(BOOL, IsWindow, (HWND));
WP_HOST(BOOL, SetWindowPos, (HWND, HWND, int, int, int, int, UINT)); WP_HOST(LONG, GetWindowLongA, (HWND, int)); WP_HOST(LONG, SetWindowLongA, (HWND, int, LONG));
#define GetWindowLongPtrA GetWindowLongA
#define SetWindowLongPtrA SetWindowLongA
#define GetWindowLongPtr GetWindowLongA
#define SetWindowLongPtr SetWindowLongA
WP_HOST(LRESULT, DefWindowProcA, (HWND, UINT, WPARAM, LPARAM)); WP_HOST(HWND, GetForegroundWindow, (void));
WP_HOST(int, GetSystemMetrics, (int)); WP_HOST(HMONITOR, MonitorFromWindow, (HWND, DWORD)); WP_HOST(BOOL, GetMonitorInfoA, (HMONITOR, MONITORINFO *));
#define DefWindowProc DefWindowProcA
WP_HOST(BOOL, GetCursorPos, (POINT *)); WP_HOST(BOOL, SetCursorPos, (int, int)); WP_HOST(BOOL, ClipCursor, (const RECT *)); WP_HOST(int, ShowCursor, (BOOL)); WP_HOST(HCURSOR, SetCursor, (HCURSOR));
WP_HOST(SHORT, GetAsyncKeyState, (int)); WP_HOST(SHORT, GetKeyState, (int));
WP_HOST(int, ChoosePixelFormat, (HDC, const PIXELFORMATDESCRIPTOR *)); WP_HOST(BOOL, SetPixelFormat, (HDC, int, const PIXELFORMATDESCRIPTOR *));
WP_HOST(int, GetPixelFormat, (HDC)); WP_HOST(int, DescribePixelFormat, (HDC, int, UINT, PIXELFORMATDESCRIPTOR *)); WP_HOST(BOOL, SwapBuffers, (HDC));
WP_HOST(HGLRC, wglCreateContext, (HDC)); WP_HOST(BOOL, wglDeleteContext, (HGLRC)); WP_HOST(BOOL, wglMakeCurrent, (HDC, HGLRC)); WP_HOST(HGLRC, wglGetCurrentContext, (void)); WP_HOST(HDC, wglGetCurrentDC, (void));
WP_HOST(void *, wglGetProcAddress, (LPCSTR));
WP_HOST(LONG, ChangeDisplaySettingsExA, (LPCSTR, DEVMODEA *, HWND, DWORD, LPVOID)); WP_HOST(BOOL, EnumDisplaySettingsA, (LPCSTR, DWORD, DEVMODEA *)); WP_HOST(BOOL, EnumDisplayDevicesA, (LPCSTR, DWORD, DISPLAY_DEVICEA *, DWORD));
WP_HOST(BOOL, EnumDisplaySettingsExA, (LPCSTR, DWORD, DEVMODEA *, DWORD));
#define ChangeDisplaySettingsEx ChangeDisplaySettingsExA
#define EnumDisplaySettings EnumDisplaySettingsA
#define EnumDisplayDevices EnumDisplayDevicesA
WP_HOST(DWORD, GetLastError, (void)); WP_HOST(void, SetLastError, (DWORD));
WP_HOST(HMODULE, GetModuleHandleA, (LPCSTR)); WP_HOST(BOOL, GetModuleHandleExA, (DWORD, LPCSTR, HMODULE *)); WP_HOST(DWORD, GetModuleFileNameA, (HMODULE, LPSTR, DWORD));
WP_HOST(HMODULE, LoadLibraryA, (LPCSTR)); WP_HOST(FARPROC, GetProcAddress, (HMODULE, LPCSTR)); WP_HOST(HANDLE, GetCurrentProcess, (void));
WP_HOST(BOOL, FlushInstructionCache, (HANDLE, LPCVOID, SIZE_T)); WP_HOST(SIZE_T, VirtualQuery, (LPCVOID, MEMORY_BASIC_INFORMATION *, SIZE_T));
WP_HOST(BOOL, VirtualProtect, (LPVOID, SIZE_T, DWORD, DWORD *)); WP_HOST(LPVOID, VirtualAlloc, (LPVOID, SIZE_T, DWORD, DWORD)); WP_HOST(BOOL, VirtualFree, (LPVOID, SIZE_T, DWORD));
WP_HOST(LPTOP_LEVEL_EXCEPTION_FILTER, SetUnhandledExceptionFilter, (LPTOP_LEVEL_EXCEPTION_FILTER));
WP_HOST(BOOL, CryptAcquireContextA, (HANDLE *, LPCSTR, LPCSTR, DWORD, DWORD)); WP_HOST(BOOL, CryptCreateHash, (HANDLE, DWORD, HANDLE, DWORD, HANDLE *));
WP_HOST(BOOL, CryptHashData, (HANDLE, const BYTE *, DWORD, DWORD)); WP_HOST(BOOL, CryptGetHashParam, (HANDLE, DWORD, BYTE *, DWORD *, DWORD)); WP_HOST(BOOL, CryptDestroyHash, (HANDLE)); WP_HOST(BOOL, CryptReleaseContext, (HANDLE, DWORD));
typedef HANDLE HCRYPTPROV, HCRYPTHASH;
/* ---- implemented natively in winport.cpp ---- */
WP_C BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *); WP_C BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *);
WP_C ULONGLONG WINAPI GetTickCount64(void); WP_C DWORD WINAPI GetTickCount(void); WP_C DWORD WINAPI GetCurrentThreadId(void); WP_C void WINAPI Sleep(DWORD);
WP_C void WINAPI OutputDebugStringA(LPCSTR); WP_C void WINAPI GetLocalTime(SYSTEMTIME *); WP_C DWORD WINAPI GetEnvironmentVariableA(LPCSTR, LPSTR, DWORD);
WP_C BOOL WINAPI CreateDirectoryA(LPCSTR, void *); WP_C BOOL WINAPI DisableThreadLibraryCalls(HMODULE);
WP_C void WINAPI AcquireSRWLockExclusive(SRWLOCK *); WP_C void WINAPI ReleaseSRWLockExclusive(SRWLOCK *);
WP_C HRSRC WINAPI FindResourceW(HMODULE, LPCWSTR, LPCWSTR); WP_C DWORD WINAPI SizeofResource(HMODULE, HRSRC); WP_C HGLOBAL WINAPI LoadResource(HMODULE, HRSRC); WP_C LPVOID WINAPI LockResource(HGLOBAL);
WP_C int WINAPI LoadStringA(HINSTANCE, UINT, LPSTR, int);
WP_C int _snprintf_s(char *, size_t, size_t, const char *, ...); WP_C int _vsnprintf_s(char *, size_t, size_t, const char *, va_list);

/* COM basics (enough for ddraw.h) */
typedef struct _GUID { uint32_t Data1; uint16_t Data2, Data3; uint8_t Data4[8]; } GUID, IID, CLSID; typedef const GUID &REFGUID; typedef const GUID &REFIID; typedef const GUID &REFCLSID;
typedef GUID *LPGUID; typedef const GUID *LPCGUID;
inline bool operator==(const GUID &a, const GUID &b) { return !memcmp(&a, &b, sizeof(GUID)); }
typedef struct { BYTE peRed, peGreen, peBlue, peFlags; } PALETTEENTRY, *LPPALETTEENTRY;
typedef struct { DWORD dwSize, dwFlags; } RGNDATAHEADER_; typedef struct { BYTE b[1]; } RGNDATA, *LPRGNDATA;
typedef struct { BYTE rgbBlue, rgbGreen, rgbRed, rgbReserved; } RGBQUAD; typedef struct { DWORD biSize; LONG biWidth, biHeight; WORD biPlanes, biBitCount; DWORD biCompression, biSizeImage; LONG biXPelsPerMeter, biYPelsPerMeter; DWORD biClrUsed, biClrImportant; } BITMAPINFOHEADER;
#define interface struct
#define STDMETHODCALLTYPE __attribute__((stdcall))
#define STDMETHOD(m) virtual HRESULT STDMETHODCALLTYPE m
#define STDMETHOD_(t,m) virtual t STDMETHODCALLTYPE m
#define PURE = 0
#define THIS_
#define THIS void
#define DECLARE_INTERFACE(i) interface i
#define DECLARE_INTERFACE_(i,b) interface i : public b
#define EXTERN_C extern "C"
#ifdef INITGUID
#define DEFINE_GUID(n,a,b,c,d,e,f,g,h,i,j,k) extern "C" const GUID n = {a,b,c,{d,e,f,g,h,i,j,k}}
#else
#define DEFINE_GUID(n,a,b,c,d,e,f,g,h,i,j,k) extern "C" const GUID n
#endif
#define __GNU_EXTENSION __extension__
#define DUMMYUNIONNAME
#define DUMMYUNIONNAME1
#define DUMMYUNIONNAME2
#define DUMMYUNIONNAME3
#define DUMMYUNIONNAME4
#define DUMMYUNIONNAME5
#define DUMMYSTRUCTNAME
#define DUMMYSTRUCTNAME1
#define DUMMYSTRUCTNAME2
#define DECLSPEC_UUID(x)
interface IUnknown { virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, void **) = 0; virtual ULONG STDMETHODCALLTYPE AddRef() = 0; virtual ULONG STDMETHODCALLTYPE Release() = 0; };
typedef IUnknown *LPUNKNOWN;

#define MAKE_HRESULT(sev,fac,code) ((HRESULT)(((unsigned long)(sev)<<31)|((unsigned long)(fac)<<16)|((unsigned long)(code))))
typedef SIZE *LPSIZE; typedef BYTE *PBYTE; typedef DWORD LCID;
#define CCHDEVICENAME 32
struct MONITORINFOEXA : MONITORINFO { char szDevice[CCHDEVICENAME]; };
typedef MONITORINFOEXA MONITORINFOEX;
#define DM_POSITION 0x20
#define INFINITE 0xFFFFFFFF
#define WS_POPUP 0x80000000u
#define WS_VISIBLE 0x10000000
#define WS_CLIPSIBLINGS 0x04000000
#define WS_CLIPCHILDREN 0x02000000
#define WS_CAPTION 0x00C00000
#define WS_BORDER 0x00800000
#define WS_SYSMENU 0x00080000
#define WS_THICKFRAME 0x00040000
#define WS_MINIMIZEBOX 0x00020000
#define WS_MAXIMIZEBOX 0x00010000
#define WS_OVERLAPPED 0
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)
#define WS_EX_DLGMODALFRAME 1
#define WS_EX_TOPMOST 8
#define WS_EX_WINDOWEDGE 0x100
#define WS_EX_CLIENTEDGE 0x200
#define WS_EX_APPWINDOW 0x40000
WP_C int strncpy_s(char *, size_t, const char *, size_t);
template <size_t N> inline int strncpy_s(char (&d)[N], const char *s, size_t n) { return strncpy_s(d, N, s, n); }
template <size_t N> inline int strcpy_s(char (&d)[N], const char *s) { return strcpy_s(d, N, s); }
template <size_t N> inline int strcat_s(char (&d)[N], const char *s) { return strcat_s(d, N, s); }
template <size_t N> inline int sprintf_s(char (&d)[N], const char *f, ...) { va_list a; va_start(a, f); int r = vsnprintf(d, N, f, a); va_end(a); return r; } WP_C int strcpy_s(char *, size_t, const char *); WP_C int strcat_s(char *, size_t, const char *);
WP_HOST(BOOL, ReadProcessMemory, (HANDLE, LPCVOID, LPVOID, SIZE_T, SIZE_T *));
WP_HOST(BOOL, GetKeyboardState, (PBYTE));

#define HMONITOR_DECLARED 1
#define WINVER 0x0600
#define SWP_NOOWNERZORDER 0x200
#define GetMonitorInfo GetMonitorInfoA
#define SM_XVIRTUALSCREEN 76
#define SM_YVIRTUALSCREEN 77
#define SM_CXVIRTUALSCREEN 78
#define SM_CYVIRTUALSCREEN 79
#define DISPLAY_DEVICE_MIRRORING_DRIVER 8
#define ERROR_SUCCESS 0
#define ERROR_FILE_NOT_FOUND 2
#define HKEY_LOCAL_MACHINE ((HKEY)(ULONG_PTR)0x80000002u)
#define KEY_QUERY_VALUE 1
#define REG_SZ 1
#define REG_MULTI_SZ 7
#define REG_DWORD 4
WP_HOST(BOOL, GetClipCursor, (RECT *));
WP_C BOOL WINAPI AdjustWindowRectEx(RECT *, DWORD, BOOL, DWORD); WP_C int WINAPI MapWindowPoints(HWND, HWND, POINT *, UINT); WP_C BOOL WINAPI SwitchToThread(void);
WP_C LONG WINAPI RegOpenKeyExA(HKEY, LPCSTR, DWORD, DWORD, HKEY *); WP_C LONG WINAPI RegQueryValueExA(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD); WP_C LONG WINAPI RegCloseKey(HKEY);
WP_C BOOL WINAPI IsWow64Process(HANDLE, BOOL *);

#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69
#define VK_INSERT 0x2D
#define VK_DELETE 0x2E
#define VK_HOME 0x24
#define VK_END 0x23
#define VK_PRIOR 0x21
#define VK_NEXT 0x22
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
#define VK_LSHIFT 0xA0
#define VK_RSHIFT 0xA1
#define VK_LCONTROL 0xA2
#define VK_RCONTROL 0xA3
#define VK_LMENU 0xA4
#define VK_RMENU 0xA5
#define GENERIC_READ 0x80000000u
#define GENERIC_WRITE 0x40000000u
#define FILE_SHARE_READ 1
#define FILE_SHARE_WRITE 2
#define FILE_SHARE_DELETE 4
#define OPEN_EXISTING 3
#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000
#define FILE_ATTRIBUTE_NORMAL 0x80
WP_HOST(HANDLE, CreateFileA, (LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE));
WP_HOST(BOOL, ReadFile, (HANDLE, LPVOID, DWORD, LPDWORD, LPVOID)); WP_HOST(BOOL, CloseHandle, (HANDLE));
template <class T> inline T *wp_strrchr_sep(T *p) { T *a = strrchr(p, '\\'); T *b = strrchr(p, '/'); return a > b ? a : b; }
