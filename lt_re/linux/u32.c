/* user32 / gdi32 / ole32 / dinput / winsock shims. Windowing is headless: windows are bookkeeping objects (hook your renderer/SDL here). */
#include "win.h"
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
/* ---- user32 ---- */
struct wcls { char name[64]; void *proc; }; static struct wcls cls[64]; static int ncls;
int lt_win_w,lt_win_h;
struct win { int used; void *proc; int x,y,w,h,visible; }; static struct win wins[256];
static int quit_pending, quit_code;
typedef int (WINAPI *WNDPROC)(HWND,UINT,uintptr_t,intptr_t);
uint32_t WINAPI W_RegisterClassA(const uint32_t *wc){ if(ncls>=64) return 0; snprintf(cls[ncls].name,64,"%s",MAKEINTRESOURCE_IS_INT((void*)wc[9])?"":(const char*)wc[9]); cls[ncls].proc=(void*)wc[1]; return 0xC000+ncls++; }
HWND WINAPI W_CreateWindowExA(DWORD ex,LPCSTR cn,LPCSTR title,DWORD style,int x,int y,int w,int h,HWND parent,HANDLE menu,HINSTANCE inst,void *param){
  void *proc=NULL; if(!MAKEINTRESOURCE_IS_INT(cn)) for(int i=0;i<ncls;i++) if(!strcasecmp(cls[i].name,cn)) proc=cls[i].proc;
  for(int i=1;i<256;i++) if(!wins[i].used){ wins[i]=(struct win){1,proc,x==(int)0x80000000?0:x,y==(int)0x80000000?0:y,w?w:640,h?h:480,0};
    HWND hw=(HWND)(uintptr_t)(0x10000+i*4); lt_win_w=wins[i].w; lt_win_h=wins[i].h;
    if(proc){ uint32_t cs[12]={(uint32_t)param,(uint32_t)inst,(uint32_t)menu,(uint32_t)parent,h,w,y,x,style,(uint32_t)title,(uint32_t)cn,ex};
      ((WNDPROC)proc)(hw,0x81,0,(intptr_t)cs); if(((WNDPROC)proc)(hw,1,0,(intptr_t)cs)==-1){ wins[i].used=0; return NULL; } }
    return hw; }
  return NULL; }
static struct win *getwin(HWND h){ uintptr_t v=(uintptr_t)h; if(v<0x10000||(v-0x10000)%4) return NULL; v=(v-0x10000)/4; return v<256&&wins[v].used?&wins[v]:NULL; }
BOOL WINAPI W_DestroyWindow(HWND h){ struct win *w=getwin(h); if(!w) return 0; if(w->proc) ((WNDPROC)w->proc)(h,2,0,0); w->used=0; return 1; }
BOOL WINAPI W_ShowWindow(HWND h,int c){ struct win *w=getwin(h); if(w) w->visible=c!=0; return 1; }
BOOL WINAPI W_UpdateWindow(HWND h){ return 1; }
intptr_t WINAPI W_DefWindowProcA(HWND h,UINT m,uintptr_t w,intptr_t l){ if(m==0x10) W_DestroyWindow(h); return 0; }
BOOL WINAPI W_GetWindowRect(HWND h,int *r){ struct win *w=getwin(h); r[0]=w?w->x:0; r[1]=w?w->y:0; r[2]=r[0]+(w?w->w:640); r[3]=r[1]+(w?w->h:480); return 1; }
HWND WINAPI W_GetDesktopWindow(void){ return (HWND)0x10004; }
void WINAPI W_PostQuitMessage(int c){ quit_pending=1; quit_code=c; }
int lt_pump_events(void);
BOOL WINAPI W_PeekMessageA(uint32_t *msg,HWND h,UINT lo,UINT hi,UINT rm){ if(lt_pump_events()){ quit_pending=1; quit_code=0; } if(quit_pending){ memset(msg,0,28); msg[1]=0x12; msg[2]=quit_code; if(rm&1) quit_pending=0; return 1; } return 0; }
BOOL WINAPI W_TranslateMessage(const void *m){ return 0; }
intptr_t WINAPI W_DispatchMessageA(const uint32_t *m){ struct win *w=getwin((HWND)m[0]); return w&&w->proc?((WNDPROC)w->proc)((HWND)m[0],m[1],m[2],m[3]):0; }
HDC WINAPI W_GetDC(HWND h){ return (HDC)0x20004; } int WINAPI W_ReleaseDC(HWND h,HDC d){ return 1; }
HDC WINAPI W_BeginPaint(HWND h,void *ps){ memset(ps,0,64); return (HDC)0x20004; } BOOL WINAPI W_EndPaint(HWND h,const void *ps){ return 1; }
BOOL WINAPI W_IsIconic(HWND h){ return 0; } HWND WINAPI W_SetFocus(HWND h){ return NULL; }
HCURSOR WINAPI W_SetCursor(HCURSOR c){ return NULL; } int WINAPI W_ShowCursor(BOOL s){ return s?1:-1; } BOOL WINAPI W_ClipCursor(const void *r){ return 1; } BOOL WINAPI W_SetCursorPos(int x,int y){ return 1; }
short WINAPI W_GetAsyncKeyState(int k){ return 0; } BOOL WINAPI W_GetKeyboardState(BYTE *s){ memset(s,0,256); return 1; } int WINAPI W_ToAscii(UINT vk,UINT sc,const BYTE *ks,WORD *out,UINT fl){ return 0; }
HICON WINAPI W_LoadIconA(HINSTANCE i,LPCSTR n){ return (HICON)1; } HCURSOR WINAPI W_LoadCursorA(HINSTANCE i,LPCSTR n){ return (HCURSOR)1; } HANDLE WINAPI W_LoadImageA(HINSTANCE i,LPCSTR n,UINT t,int x,int y,UINT f){ return (HANDLE)1; }
DWORD WINAPI W_GetClassLongA(HWND h,int i){ return 0; }
int WINAPI W_MessageBoxA(HWND h,LPCSTR text,LPCSTR cap,UINT type){ fprintf(stderr,"[MessageBox] %s: %s\n",cap?cap:"",text?text:""); fflush(stderr); UINT k=type&0xf; return (k==4||k==3)?6:1; }
int W_wsprintfA(char *buf,const char *fmt,...){ va_list a; va_start(a,fmt); int n=vsprintf(buf,fmt,a); va_end(a); return n; }   /* cdecl */
int WINAPI W_wvsprintfA(char *buf,const char *fmt,va_list a){ return vsprintf(buf,fmt,a); }
/* ---- gdi32 (no real drawing) ---- */
HANDLE WINAPI W_CreateDIBSection(HDC dc,const uint32_t *bi,UINT use,void **bits,HANDLE sec,DWORD off){ int w=(int)bi[1],h=(int)bi[2]; if(h<0)h=-h; int bpp=((WORD*)bi)[7]; size_t sz=(size_t)h*(((w*bpp+31)/32)*4); void *p=calloc(1,sz?sz:4); if(bits)*bits=p; return p; }
BOOL WINAPI W_Rectangle(HDC d,int a,int b,int c,int e){ return 1; } BOOL WINAPI W_TextOutA(HDC d,int x,int y,LPCSTR s,int n){ return 1; }
BOOL WINAPI W_GetTextExtentPoint32A(HDC d,LPCSTR s,int n,int *sz){ sz[0]=n*8; sz[1]=16; return 1; }
int WINAPI W_GetTextCharacterExtra(HDC d){ return 0; } int WINAPI W_SetTextCharacterExtra(HDC d,int e){ return 0; }
BOOL WINAPI W_DeleteObject(HGDIOBJ o){ return 1; } HANDLE WINAPI W_CreateFontA(int a,int b,int c,int d,int e,DWORD f,DWORD g,DWORD h,DWORD i,DWORD j,DWORD k,DWORD l,DWORD m,LPCSTR n){ return (HANDLE)1; }
HDC WINAPI W_CreateCompatibleDC(HDC d){ return (HDC)0x20008; } HGDIOBJ WINAPI W_SelectObject(HDC d,HGDIOBJ o){ return (HGDIOBJ)1; }
DWORD WINAPI W_SetTextColor(HDC d,DWORD c){ return 0; } int WINAPI W_SetBkMode(HDC d,int m){ return 1; } DWORD WINAPI W_SetBkColor(HDC d,DWORD c){ return 0; }
HGDIOBJ WINAPI W_GetStockObject(int i){ return (HGDIOBJ)1; } BOOL WINAPI W_DeleteDC(HDC d){ return 1; }
/* ---- ole32 / dinput (report "not available"; engine falls back) ---- */
HRESULT WINAPI W_CoInitialize(void *r){ return 0; } void WINAPI W_CoUninitialize(void){}
HRESULT WINAPI W_CoCreateInstance(const void *clsid,void *outer,DWORD ctx,const void *iid,void **out){ if(out)*out=NULL; return 0x80040154; }
/* ---- winsock -> BSD sockets ---- */
static __thread int wsaerr;
static int wsmap(int e){ switch(e){ case EWOULDBLOCK: return 10035; case EINPROGRESS: return 10036; case ECONNRESET: return 10054; case ECONNREFUSED: return 10061; case EADDRINUSE: return 10048; case EADDRNOTAVAIL: return 10049; case EMSGSIZE: return 10040; case ENETUNREACH: return 10051; case EINVAL: return 10022; case EBADF: return 10038; case EAFNOSUPPORT: return 10047; case EACCES: return 10013; case ENOTSOCK: return 10038; } return 10000+e; }
static int chk(int r){ if(r<0){ wsaerr=wsmap(errno); return -1; } return r; }
int WINAPI W_WSAStartup(WORD v,void *d){ memset(d,0,400); ((WORD*)d)[0]=0x0101; ((WORD*)d)[1]=0x0202; strcpy((char*)d+4,"lt shim winsock"); return 0; }
int WINAPI W_WSACleanup(void){ return 0; } int WINAPI W_WSAGetLastError(void){ return wsaerr; }
uint32_t WINAPI W_htonl(uint32_t v){ return htonl(v); } uint32_t WINAPI W_ntohl(uint32_t v){ return ntohl(v); } uint16_t WINAPI W_htons(uint16_t v){ return htons(v); } uint16_t WINAPI W_ntohs(uint16_t v){ return ntohs(v); }
int WINAPI W_socket(int af,int type,int proto){ int s=socket(af,type,proto); if(s<0){ wsaerr=wsmap(errno); return -1; } return s; }
int WINAPI W_closesocket(int s){ return chk(close(s)); }
int WINAPI W_ioctlsocket(int s,uint32_t cmd,uint32_t *arg){ if(cmd==0x8004667E){ int fl=fcntl(s,F_GETFL,0); return chk(fcntl(s,F_SETFL,*arg?fl|O_NONBLOCK:fl&~O_NONBLOCK)); } if(cmd==0x4004667F){ int n=0; int r=chk(ioctl(s,FIONREAD,&n)); *arg=n; return r; } wsaerr=10022; return -1; }
int WINAPI W_bind(int s,const struct sockaddr *a,int l){ return chk(bind(s,a,l)); }
int WINAPI W_getsockname(int s,struct sockaddr *a,int *l){ socklen_t n=*l; int r=chk(getsockname(s,a,&n)); *l=n; return r; }
int WINAPI W_setsockopt(int s,int lvl,int opt,const char *v,int l){ if(lvl==0xffff){ lvl=SOL_SOCKET; switch(opt){ case 0x20: opt=SO_BROADCAST; break; case 4: opt=SO_REUSEADDR; break; case 0x1001: opt=SO_SNDBUF; break; case 0x1002: opt=SO_RCVBUF; break; default: return 0; } } return chk(setsockopt(s,lvl,opt,v,l)); }
int WINAPI W_sendto(int s,const char *b,int n,int fl,const struct sockaddr *to,int tl){ return chk(sendto(s,b,n,fl,to,tl)); }
int WINAPI W_recvfrom(int s,char *b,int n,int fl,struct sockaddr *from,int *fl_){ socklen_t l=fl_?*fl_:0; int r=chk(recvfrom(s,b,n,fl,from,fl_?&l:NULL)); if(fl_)*fl_=l; return r; }
int WINAPI W_gethostname(char *n,int l){ return chk(gethostname(n,l)); }
uint32_t WINAPI W_inet_addr(const char *s){ return inet_addr(s); }
struct whost { char *name; char **aliases; short type; short len; char **addrs; };
void *WINAPI W_gethostbyname(const char *n){ static __thread struct whost h; static __thread char *al[1]; static __thread char *ad[16]; static __thread char name[256]; static __thread uint32_t ips[16];
  struct hostent *he=gethostbyname(n); if(!he){ wsaerr=11001; return NULL; } snprintf(name,sizeof name,"%s",he->h_name); int i=0; for(;he->h_addr_list[i]&&i<15;i++){ memcpy(&ips[i],he->h_addr_list[i],4); ad[i]=(char*)&ips[i]; } ad[i]=NULL; al[0]=NULL;
  h.name=name; h.aliases=al; h.type=2; h.len=4; h.addrs=ad; return &h; }
int WINAPI W_RemoveFontResourceA(LPCSTR n){ return 1; } int WINAPI W_AddFontResourceA(LPCSTR n){ return 1; }
BOOL WINAPI W_SetWindowPos(HWND h,HWND a,int x,int y,int cx,int cy,UINT f){ struct win *w=getwin(h); if(w){ if(!(f&2)){ w->x=x; w->y=y; } if(!(f&1)){ w->w=cx; w->h=cy; lt_win_w=cx; lt_win_h=cy; } } return 1; }
BOOL WINAPI W_MoveWindow(HWND h,int x,int y,int cx,int cy,BOOL r){ return W_SetWindowPos(h,0,x,y,cx,cy,0); }
BOOL WINAPI W_AdjustWindowRect(int *r,DWORD st,BOOL m){ return 1; }
BOOL WINAPI W_GetClientRect(HWND h,int *r){ struct win *w=getwin(h); r[0]=0; r[1]=0; r[2]=w?w->w:640; r[3]=w?w->h:480; return 1; }
int WINAPI W_GetSystemMetrics(int i){ switch(i){ case 0: return 1920; case 1: return 1080; case 4: return 19; case 5: case 6: return 1; case 32: case 33: return 4; case 7: case 8: return 3; } return 0; }
DWORD WINAPI W_GetWindowLongA(HWND h,int i){ struct win *w=getwin(h); if(w&&i==-4) return (DWORD)w->proc; return 0; }
DWORD WINAPI W_SetWindowLongA(HWND h,int i,DWORD v){ struct win *w=getwin(h); if(w&&i==-4){ DWORD o=(DWORD)w->proc; w->proc=(void*)v; return o; } return 0; }
BOOL WINAPI W_SetForegroundWindow(HWND h){ return 1; } BOOL WINAPI W_EnableWindow(HWND h,BOOL e){ return 1; } BOOL WINAPI W_IsWindowVisible(HWND h){ return 1; }
BOOL WINAPI W_GetCursorPos(int *p){ p[0]=320; p[1]=240; return 1; } HWND WINAPI W_GetActiveWindow(void){ return (HWND)0x10004; } HWND WINAPI W_GetFocus(void){ return (HWND)0x10004; } HWND WINAPI W_GetForegroundWindow(void){ return (HWND)0x10004; }
BOOL WINAPI W_PostMessageA(HWND h,UINT m,uintptr_t w,intptr_t l){ return 1; }
BOOL WINAPI W_SetWindowTextA(HWND h,LPCSTR t){ return 1; }
BOOL WINAPI W_ClientToScreen(HWND h,int *p){ return 1; } BOOL WINAPI W_ScreenToClient(HWND h,int *p){ return 1; }
BOOL WINAPI W_SystemParametersInfoA(UINT a,UINT b,void *c,UINT d){ return 1; }
HRESULT WINAPI W_DirectSoundCreate(const void *g,void **out,void *outer){ if(out)*out=NULL; return 0x88780078; }
