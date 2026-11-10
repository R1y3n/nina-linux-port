/* user32/gdi32 additions for modern DLLs (display enumeration, monitors, clipboard/capture stubs) */
#include "win.h"
BOOL WINAPI W_AdjustWindowRectEx(int *r,DWORD s,BOOL m,DWORD e){ return 1; }
int WINAPI W_ChangeDisplaySettingsExA(LPCSTR n,void *dm,HWND h,DWORD f,void *p){ return 0; }
BOOL WINAPI W_CloseClipboard(void){ return 1; } BOOL WINAPI W_EmptyClipboard(void){ return 1; } BOOL WINAPI W_OpenClipboard(HWND h){ return 0; }
HANDLE WINAPI W_GetClipboardData(UINT f){ return NULL; } HANDLE WINAPI W_SetClipboardData(UINT f,HANDLE h){ return NULL; }
BOOL WINAPI W_EnumDisplayDevicesA(LPCSTR dev,DWORD i,uint8_t *dd,DWORD fl){ if(i>0) return 0; memset(dd+4,0,420); snprintf((char*)dd+4,32,"\\\\.\\DISPLAY1"); snprintf((char*)dd+36,128,"Linux Display"); *(DWORD*)(dd+164)=1|4; return 1; }
static const int modes[][2]={{640,480},{800,600},{1024,768},{1280,720},{1280,1024},{1600,1200},{1920,1080}};
static void fillmode(uint8_t *dm,int w,int h){ DWORD sz=*(uint16_t*)(dm+36); memset(dm+40,0,(sz>40?sz:156)-40); *(DWORD*)(dm+40)=0x1C0000|0x20000|0x400000|0x40000; *(DWORD*)(dm+104)=32; *(DWORD*)(dm+108)=w; *(DWORD*)(dm+112)=h; *(DWORD*)(dm+120)=60; }
BOOL WINAPI W_EnumDisplaySettingsA(LPCSTR dev,DWORD i,uint8_t *dm){ if(i==(DWORD)-1||i==(DWORD)-2){ fillmode(dm,1920,1080); return 1; } if(i>=sizeof modes/sizeof *modes) return 0; fillmode(dm,modes[i][0],modes[i][1]); return 1; }
BOOL WINAPI W_EnumDisplaySettingsExA(LPCSTR dev,DWORD i,uint8_t *dm,DWORD f){ return W_EnumDisplaySettingsA(dev,i,dm); }
HANDLE WINAPI W_GetCapture(void){ return NULL; } HANDLE WINAPI W_SetCapture(HWND h){ return NULL; } BOOL WINAPI W_ReleaseCapture(void){ return 1; }
BOOL WINAPI W_GetClipCursor(int *r){ r[0]=0; r[1]=0; r[2]=1920; r[3]=1080; return 1; }
short WINAPI W_GetKeyState(int k){ return 0; } HANDLE WINAPI W_GetKeyboardLayout(DWORD t){ return (HANDLE)0x04090409; } intptr_t WINAPI W_GetMessageExtraInfo(void){ return 0; }
BOOL WINAPI W_GetMonitorInfoA(HANDLE m,DWORD *mi){ mi[1]=0; mi[2]=0; mi[3]=1920; mi[4]=1080; mi[5]=0; mi[6]=0; mi[7]=1920; mi[8]=1080; mi[9]=1; return 1; }
HANDLE WINAPI W_MonitorFromWindow(HWND h,DWORD f){ return (HANDLE)1; }
BOOL WINAPI W_IsWindow(HWND h){ return (uintptr_t)h>=0x10000; } BOOL WINAPI W_IsWindowUnicode(HWND h){ return 0; }
int WINAPI W_MapWindowPoints(HWND a,HWND b,void *p,UINT n){ return 0; } BOOL WINAPI W_SetProcessDPIAware(void){ return 1; } BOOL WINAPI W_TrackMouseEvent(void *e){ return 1; }
HANDLE WINAPI W_CreateRectRgn(int a,int b,int c,int d){ return (HANDLE)1; }
int WINAPI W_GetDeviceCaps(HDC dc,int i){ switch(i){ case 8: return 1920; case 10: return 1080; case 12: return 32; case 14: return 1; case 24: return 1920; case 88: case 90: return 96; case 116: return 60; } return 0; }
