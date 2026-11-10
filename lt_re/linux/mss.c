/* Miles Sound System (mss32) compatibility layer: memory/lock/startup are real, audio output is a null device for now.
   Everything not defined here falls back to an auto-stub that logs and returns 0. Hook an audio backend (SDL2/OpenAL) into AIL_open_digital_driver etc. */
#include "win.h"
void *WINAPI W_AIL_mem_alloc_lock(DWORD n){ return malloc(n?n:1); }
void WINAPI W_AIL_mem_free_lock(void *p){ free(p); }
void WINAPI W_AIL_lock(void){} void WINAPI W_AIL_unlock(void){}
int WINAPI W_AIL_startup(void){ return 1; }
void WINAPI W_AIL_shutdown(void){}
int WINAPI W_AIL_set_preference(DWORD idx,int val){ return 0; }
const char *WINAPI W_AIL_last_error(void){ return "No audio device"; }
int WINAPI W_AIL_get_preference(DWORD idx){ return 0; }
DWORD WINAPI W_AIL_ms_count(void){ extern DWORD WINAPI W_GetTickCount(void); return W_GetTickCount(); }
int WINAPI W_AIL_waveOutOpen(void *drv,void *a,DWORD b,void *fmt){ return 1; }
