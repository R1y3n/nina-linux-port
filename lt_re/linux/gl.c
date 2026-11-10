/* OpenGL (opengl32/WGL) -> host OpenGL via SDL2 (loaded at run time). Windows GL is stdcall, host GL is cdecl: every function handed out gets a small adapter thunk. */
#include "win.h"
#include <dlfcn.h>
#include <sys/mman.h>
#include <strings.h>
struct glar { const char *name; int n; }; extern struct glar lt_glarity[]; extern int lt_glarity_n;
extern int lt_win_w,lt_win_h;
static void *sdl;
static int (*SDL_Init)(uint32_t); static void *(*SDL_CreateWindow)(const char*,int,int,int,int,uint32_t); static int (*SDL_GL_SetAttribute)(int,int);
static void *(*SDL_GL_CreateContext)(void*); static int (*SDL_GL_MakeCurrent)(void*,void*); static void *(*SDL_GL_GetProcAddress)(const char*);
static void (*SDL_GL_SwapWindow)(void*); static void (*SDL_GL_DeleteContext)(void*); static int (*SDL_GL_SetSwapInterval)(int); static const char *(*SDL_GetError)(void);
static int (*SDL_PollEvent)(void*); static void (*SDL_SetWindowSize)(void*,int,int); static void (*SDL_ShowWindow)(void*);
static void *win; static void *cur_ctx; static int swap_interval=1;
static int load_sdl(void){
  if(sdl) return 1; sdl=dlopen("libSDL2-2.0.so.0",RTLD_NOW|RTLD_GLOBAL); if(!sdl) sdl=dlopen("libSDL2.so",RTLD_NOW|RTLD_GLOBAL); if(!sdl){ lt_log("SDL2 not found (%s): OpenGL unavailable",dlerror()); return 0; }
#define L(n) *(void**)&n=dlsym(sdl,#n)
  L(SDL_Init); L(SDL_CreateWindow); L(SDL_GL_SetAttribute); L(SDL_GL_CreateContext); L(SDL_GL_MakeCurrent); L(SDL_GL_GetProcAddress); L(SDL_GL_SwapWindow); L(SDL_GL_DeleteContext); L(SDL_GL_SetSwapInterval); L(SDL_GetError); L(SDL_PollEvent); L(SDL_SetWindowSize); L(SDL_ShowWindow);
  if(SDL_Init(0x20)){ lt_log("SDL_Init failed: %s",SDL_GetError()); return 0; } return 1; }
static int ensure_window(void){ if(win) return 1; if(!load_sdl()) return 0; int w=lt_win_w?lt_win_w:640,h=lt_win_h?lt_win_h:480; win=SDL_CreateWindow("AVP2 (lithtech_linux)",0x2FFF0000,0x2FFF0000,w,h,2|4); if(!win){ lt_log("SDL_CreateWindow failed: %s",SDL_GetError()); return 0; } lt_log("SDL window %dx%d created",w,h); return 1; }
/* ---- stdcall -> cdecl thunks ---- */
struct gt { char name[64]; int n; void *slot; unsigned char *code; struct gt *next; }; static struct gt *gts;
static void gl_unresolved(void){ static int c; if(c++<20) lt_log("call to an unresolved GL function"); }
static int arity(const char *name){ int lo=0,hi=lt_glarity_n-1; while(lo<=hi){ int m=(lo+hi)/2; int c=strcmp(lt_glarity[m].name,name); if(!c) return lt_glarity[m].n; if(c<0) lo=m+1; else hi=m-1; } return -1; }
static void resolve_one(struct gt *g){ if(!SDL_GL_GetProcAddress||!cur_ctx) return; void *p=SDL_GL_GetProcAddress(g->name); if(p) g->slot=p; }
static unsigned char *code_alloc(size_t n){ static unsigned char *pg; static size_t used=65536; if(used+n>65536){ pg=mmap(0,65536,7,MAP_PRIVATE|MAP_ANONYMOUS,-1,0); used=0; } unsigned char *p=pg+used; used+=(n+15)&~15u; return p; }
void *lt_gl_thunk(const char *name){
  for(struct gt *g=gts;g;g=g->next) if(!strcmp(g->name,name)) return g->code;
  int n=arity(name); if(n<0){ lt_log("GL: unknown function %s (no arity)",name); return NULL; }
  struct gt *g=calloc(1,sizeof *g); snprintf(g->name,sizeof g->name,"%s",name); g->n=n; g->slot=gl_unresolved; g->code=code_alloc(16+6*(n/4)+16); resolve_one(g);
  unsigned char *p=g->code; unsigned i=0; p[i++]=0x55; p[i++]=0x89; p[i++]=0xE5;
  for(int k=n/4-1;k>=0;k--){ int d=8+4*k; if(d<128){ p[i++]=0xFF; p[i++]=0x75; p[i++]=d; } else { p[i++]=0xFF; p[i++]=0xB5; *(int*)(p+i)=d; i+=4; } }
  p[i++]=0xFF; p[i++]=0x15; *(void***)(p+i)=&g->slot; i+=4;                     /* call [slot] */
  if(n){ p[i++]=0x81; p[i++]=0xC4; *(int*)(p+i)=n; i+=4; }                       /* add esp,n  (cdecl cleanup) */
  p[i++]=0x5D; if(n){ p[i++]=0xC2; *(uint16_t*)(p+i)=n; i+=2; } else p[i++]=0xC3; /* pop ebp; ret n */
  g->next=gts; gts=g; return g->code; }
static void resolve_all(void){ for(struct gt *g=gts;g;g=g->next) resolve_one(g); }
/* ---- WGL ---- */
struct ctx { void *sdl; int major,minor,profile,flags; };
HANDLE WINAPI W_wglCreateContext(HDC dc){ if(!ensure_window()) return NULL; void *c=SDL_GL_CreateContext(win); if(!c){ lt_log("SDL_GL_CreateContext failed: %s",SDL_GetError()); return NULL; } struct ctx *x=calloc(1,sizeof *x); x->sdl=c; return x; }
BOOL WINAPI W_wglDeleteContext(HANDLE c){ struct ctx *x=c; if(!x) return 0; if(cur_ctx==x->sdl) cur_ctx=NULL; SDL_GL_DeleteContext(x->sdl); free(x); return 1; }
BOOL WINAPI W_wglMakeCurrent(HDC dc,HANDLE c){ struct ctx *x=c; if(!x){ if(win) SDL_GL_MakeCurrent(win,NULL); cur_ctx=NULL; return 1; } if(SDL_GL_MakeCurrent(win,x->sdl)){ lt_log("SDL_GL_MakeCurrent failed: %s",SDL_GetError()); return 0; } cur_ctx=x->sdl; static int first=1; if(first){ first=0; SDL_GL_SetSwapInterval(swap_interval); } resolve_all(); return 1; }
HANDLE WINAPI W_wglGetCurrentContext(void){ return cur_ctx?(HANDLE)cur_ctx:NULL; } HDC WINAPI W_wglGetCurrentDC(void){ return cur_ctx?(HDC)0x20004:NULL; }
static HANDLE WINAPI wgl_CreateContextAttribsARB(HDC dc,HANDLE share,const int *a){ int maj=1,min=0,prof=0,fl=0; for(;a&&a[0];a+=2){ if(a[0]==0x2091) maj=a[1]; else if(a[0]==0x2092) min=a[1]; else if(a[0]==0x9126) prof=a[1]; else if(a[0]==0x2094) fl=a[1]; }
  if(!ensure_window()) return NULL; SDL_GL_SetAttribute(17,maj); SDL_GL_SetAttribute(18,min); SDL_GL_SetAttribute(21,prof==1?1:prof==2?2:0); SDL_GL_SetAttribute(20,fl&1?1:0);
  lt_log("wglCreateContextAttribsARB %d.%d profile=%d flags=%d",maj,min,prof,fl); void *c=SDL_GL_CreateContext(win);
  static const int fb[][2]={{4,5},{4,3},{4,1},{3,3},{3,2}};
  for(unsigned k=0;!c&&k<sizeof fb/sizeof *fb;k++){ if(fb[k][0]>maj||(fb[k][0]==maj&&fb[k][1]>=min)) continue; SDL_GL_SetAttribute(17,fb[k][0]); SDL_GL_SetAttribute(18,fb[k][1]); c=SDL_GL_CreateContext(win); if(c) lt_log("  fell back to GL %d.%d (host driver)",fb[k][0],fb[k][1]); }
  if(!c){ lt_log("SDL_GL_CreateContext(attribs) failed: %s",SDL_GetError()); return NULL; } struct ctx *x=calloc(1,sizeof *x); x->sdl=c; x->major=maj; x->minor=min; return x; }
static const char *WINAPI wgl_GetExtensionsStringARB(HDC dc){ return "WGL_ARB_extensions_string WGL_ARB_create_context WGL_ARB_create_context_profile WGL_EXT_swap_control WGL_ARB_pixel_format"; }
static BOOL WINAPI wgl_SwapIntervalEXT(int i){ swap_interval=i; if(SDL_GL_SetSwapInterval) SDL_GL_SetSwapInterval(i); return 1; } static int WINAPI wgl_GetSwapIntervalEXT(void){ return swap_interval; }
static BOOL WINAPI wgl_ChoosePixelFormatARB(HDC dc,const int *ia,const float *fa,UINT n,int *f,UINT *nf){ if(f) f[0]=1; if(nf) *nf=1; return 1; }
static BOOL WINAPI wgl_GetPixelFormatAttribivARB(HDC dc,int pf,int layer,UINT n,const int *attr,int *val){ for(UINT i=0;i<n;i++){ switch(attr[i]){ case 0x2000: val[i]=1; break; case 0x2001: case 0x2003: val[i]=1; break; case 0x2010: case 0x2011: val[i]=1; break; case 0x2013: val[i]=0x202B; break; case 0x2014: val[i]=32; break; case 0x2022: val[i]=24; break; case 0x2023: val[i]=8; break; case 0x2002: val[i]=1; break; default: val[i]=0; } } return 1; }
void *WINAPI W_wglGetProcAddress(LPCSTR name){
  if(!strncmp(name,"wgl",3)){
    if(!strcmp(name,"wglCreateContextAttribsARB")) return wgl_CreateContextAttribsARB; if(!strcmp(name,"wglGetExtensionsStringARB")||!strcmp(name,"wglGetExtensionsStringEXT")) return wgl_GetExtensionsStringARB;
    if(!strcmp(name,"wglSwapIntervalEXT")) return wgl_SwapIntervalEXT; if(!strcmp(name,"wglGetSwapIntervalEXT")) return wgl_GetSwapIntervalEXT;
    if(!strcmp(name,"wglChoosePixelFormatARB")) return wgl_ChoosePixelFormatARB; if(!strcmp(name,"wglGetPixelFormatAttribivARB")) return wgl_GetPixelFormatAttribivARB; return NULL; }
  if(!load_sdl()) return NULL; return lt_gl_thunk(name); }
/* ---- pixel format / swap (gdi32) ---- */
int WINAPI W_ChoosePixelFormat(HDC dc,const void *pfd){ return 1; } BOOL WINAPI W_SetPixelFormat(HDC dc,int f,const void *pfd){ return 1; } int WINAPI W_GetPixelFormat(HDC dc){ return 1; }
int WINAPI W_DescribePixelFormat(HDC dc,int f,UINT sz,uint8_t *pfd){ if(pfd&&sz>=40){ memset(pfd,0,sz); *(uint16_t*)pfd=40; *(uint16_t*)(pfd+2)=1; *(DWORD*)(pfd+4)=0x25|0x4|0x20|0x1; pfd[8]=0; pfd[9]=32; pfd[10]=16; pfd[11]=8; pfd[12]=8; pfd[13]=8; pfd[14]=0; pfd[15]=8; pfd[16]=24; pfd[17]=8; pfd[18]=0; pfd[19]=0; pfd[20]=32; pfd[21]=0; pfd[22]=24; pfd[23]=8; } return 1; }
BOOL WINAPI W_SwapBuffers(HDC dc){ if(win) SDL_GL_SwapWindow(win); return 1; }
/* event pump (called from PeekMessage): returns 1 if the user closed the window */
int lt_pump_events(void){ if(!SDL_PollEvent) return 0; uint8_t ev[64]; int quit=0; while(SDL_PollEvent(ev)){ if(*(uint32_t*)ev==0x100) quit=1; } return quit; }

/* native (cdecl) GL entry points for ELF renderer modules */
void *WINAPI W_lt_GetGLProcNative(LPCSTR n){ if(!SDL_GL_GetProcAddress && !load_sdl()) return NULL; return SDL_GL_GetProcAddress(n); }
