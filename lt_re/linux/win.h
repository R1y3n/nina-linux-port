/* Minimal Win32 types/macros for the native-Linux shim (i386, stdcall). */
#ifndef WIN_H
#define WIN_H
#define _GNU_SOURCE
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
typedef uint32_t DWORD,ULONG,UINT,BOOL,WORD_,HRESULT; typedef uint16_t WORD,WCHAR; typedef uint8_t BYTE;
typedef int32_t LONG; typedef void *HANDLE,*LPVOID,*HWND,*HDC,*HMODULE,*HINSTANCE,*HGDIOBJ,*HICON,*HCURSOR; typedef const char *LPCSTR; typedef char *LPSTR;
typedef uint32_t SIZE_T_; typedef int64_t LONGLONG; typedef uint64_t ULONGLONG;
#define WINAPI __attribute__((stdcall,force_align_arg_pointer))
#define W(name) WINAPI W_##name
#define TRUE 1
#define FALSE 0
#define INVALID_HANDLE_VALUE ((HANDLE)(intptr_t)-1)
#define MAKEINTRESOURCE_IS_INT(p) (((uintptr_t)(p))>>16==0)
/* error codes */
#define ERROR_SUCCESS 0
#define ERROR_FILE_NOT_FOUND 2
#define ERROR_PATH_NOT_FOUND 3
#define ERROR_ACCESS_DENIED 5
#define ERROR_INVALID_HANDLE 6
#define ERROR_NOT_ENOUGH_MEMORY 8
#define ERROR_INVALID_PARAMETER 87
#define ERROR_ALREADY_EXISTS 183
#define ERROR_NO_MORE_FILES 18
#define ERROR_INSUFFICIENT_BUFFER 122
#define ERROR_CALL_NOT_IMPLEMENTED 120
#define WAIT_OBJECT_0 0
#define WAIT_TIMEOUT 258
#define WAIT_FAILED 0xFFFFFFFFu
#define INFINITE 0xFFFFFFFFu
typedef struct { DWORD lo,hi; } FILETIME;
typedef struct { WORD y,mo,dow,d,h,mi,s,ms; } SYSTEMTIME;
/* TEB: fs:[0]=SEH chain, fs:[0x18]=self, fs:[0x30]=PEB, fs:[0x34]=LastError, TLS slots at 0xE10 */
#define TEB_SIZE 0x1000
#define TEB_EXC 0x00
#define TEB_STACKBASE 0x04
#define TEB_STACKLIMIT 0x08
#define TEB_SELF 0x18
#define TEB_PEB 0x30
#define TEB_LASTERR 0x34
#define TEB_TLS 0xE10
#define TLS_SLOTS 64
extern __thread void *lt_teb;           /* this thread's TEB (linux TLS, via gs) */
void lt_thread_init(void *stackbase);   /* allocate TEB + load fs */
static inline void set_last_error(DWORD e){ *(DWORD*)((char*)lt_teb+TEB_LASTERR)=e; }
static inline DWORD get_last_error(void){ return *(DWORD*)((char*)lt_teb+TEB_LASTERR); }
void lt_log(const char *fmt,...);
char *win2unix(const char *w, char *out, size_t n);  /* \ -> /, drop drive, case-insensitive fix-up */
/* handle table */
enum { H_NONE, H_FILE, H_EVENT, H_THREAD, H_FIND, H_HEAP, H_STD, H_MUTEX };
struct obj { int type; int fd; pthread_t th; int started; DWORD exit; int signaled, manual, suspended; void *dir; char pat[260]; char dirpath[512]; void *start; void *param; };
HANDLE obj_new(int type, struct obj **out);
struct obj *obj_get(HANDLE h);
void obj_free(HANDLE h);
extern pthread_mutex_t lt_wait_mx; extern pthread_cond_t lt_wait_cv;
#endif
