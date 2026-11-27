/* user32 / gdi32 / ole32 / dinput / winsock shims with active SDL2 input event processing & window activation. */
#include "win.h"
#include <SDL2/SDL.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

static DWORD g_text_color = 0x00FFFFFF;
static DWORD g_bk_color   = 0x00000000;
static int   g_bk_mode    = 1;


//DWORD WINAPI W_SetTextColor(HDC d, DWORD c) { DWORD old = g_text_color; g_text_color = c; return old; }
//DWORD WINAPI W_SetBkColor(HDC d, DWORD c)   { DWORD old = g_bk_color;   g_bk_color   = c; return old; }
//int   WINAPI W_SetBkMode(HDC d, int m)      { int old   = g_bk_mode;    g_bk_mode    = m; return old; }

/* DirectInput Scancode converter for MapVirtualKeyA */
UINT WINAPI W_MapVirtualKeyA(UINT uCode, UINT uMapType) {
    if (uMapType == 0) { /* MAPVK_VK_TO_VSC */
        if (uCode >= 'A' && uCode <= 'Z') {
            static const uint8_t vk_alpha_dik[] = {
                0x1E, 0x30, 0x2E, 0x20, 0x12, 0x21, 0x22, 0x23, 0x17, 0x24, /* A-J */
                0x25, 0x26, 0x32, 0x31, 0x18, 0x19, 0x10, 0x13, 0x1F, 0x14, /* K-T */
                0x16, 0x2F, 0x11, 0x2D, 0x15, 0x2C                          /* U-Z */
            };
            return vk_alpha_dik[uCode - 'A'];
        }
        if (uCode >= '1' && uCode <= '9') return 0x02 + (uCode - '1');
        if (uCode == '0') return 0x0B;

        switch (uCode) {
            case 0x0D: return 0x1C; /* VK_RETURN -> DIK_RETURN (0x1C, NOT 0x0D!) */
            case 0x1B: return 0x01; /* VK_ESCAPE -> DIK_ESCAPE */
            case 0x08: return 0x0E; /* VK_BACK -> DIK_BACKSPACE */
            case 0x09: return 0x0F; /* VK_TAB -> DIK_TAB */
            case 0x20: return 0x39; /* VK_SPACE -> DIK_SPACE */
            case 0x10: return 0x2A; /* VK_SHIFT -> DIK_LSHIFT */
            case 0x11: return 0x1D; /* VK_CONTROL -> DIK_LCTRL */
            case 0x12: return 0x38; /* VK_MENU -> DIK_LALT */
            case 0x25: return 0xCB; /* VK_LEFT -> DIK_LEFT */
            case 0x26: return 0xC8; /* VK_UP -> DIK_UP */
            case 0x27: return 0xCD; /* VK_RIGHT -> DIK_RIGHT */
            case 0x28: return 0xD0; /* VK_DOWN -> DIK_DOWN */
            default:   return 0;
        }
    }
    return 0;
}

UINT WINAPI W_MapVirtualKeyW(UINT uCode, UINT uMapType) {
    return W_MapVirtualKeyA(uCode, uMapType);
}

BOOL WINAPI W_HeapValidate(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem) {
    return TRUE;
}

HWND WINAPI W_GetLastActivePopup(HWND hWnd) {
    return hWnd;
}


/* ---- user32 ---- */
struct wcls { char name[64]; void *proc; }; static struct wcls cls[64]; static int ncls;
int lt_win_w,lt_win_h;
struct win { int used; void *proc; int x,y,w,h,visible; }; static struct win wins[256];
static int quit_pending, quit_code;
static HWND g_main_hwnd = NULL;
typedef int (WINAPI *WNDPROC)(HWND,UINT,uintptr_t,intptr_t);

uint32_t WINAPI W_RegisterClassA(const uint32_t *wc){ if(ncls>=64) return 0; snprintf(cls[ncls].name,64,"%s",MAKEINTRESOURCE_IS_INT((void*)wc[9])?"":(const char*)wc[9]); cls[ncls].proc=(void*)wc[1]; return 0xC000+ncls++; }
HWND WINAPI W_CreateWindowExA(DWORD ex,LPCSTR cn,LPCSTR title,DWORD style,int x,int y,int w,int h,HWND parent,HANDLE menu,HINSTANCE inst,void *param){
  void *proc=NULL; if(!MAKEINTRESOURCE_IS_INT(cn)) for(int i=0;i<ncls;i++) if(!strcasecmp(cls[i].name,cn)) proc=cls[i].proc;
  for(int i=1;i<256;i++) if(!wins[i].used){ wins[i]=(struct win){1,proc,x==(int)0x80000000?0:x,y==(int)0x80000000?0:y,w?w:640,h?h:480,0};
    HWND hw=(HWND)(uintptr_t)(0x10000+i*4); lt_win_w=wins[i].w; lt_win_h=wins[i].h; g_main_hwnd = hw;
    if(proc){ uint32_t cs[12]={(uint32_t)param,(uint32_t)inst,(uint32_t)menu,(uint32_t)parent,h,w,y,x,style,(uint32_t)title,(uint32_t)cn,ex};
      ((WNDPROC)proc)(hw,0x81,0,(intptr_t)cs); if(((WNDPROC)proc)(hw,1,0,(intptr_t)cs)==-1){ wins[i].used=0; return NULL; }
      /* Force window activation so LithTech's m_bAppActive flag stays TRUE */
      ((WNDPROC)proc)(hw, 0x0018, 1, 0); // WM_SHOWWINDOW
      ((WNDPROC)proc)(hw, 0x001C, 1, 0); // WM_ACTIVATEAPP
      ((WNDPROC)proc)(hw, 0x0006, 1, 0); // WM_ACTIVATE (WA_ACTIVE)
      ((WNDPROC)proc)(hw, 0x0007, 0, 0); // WM_SETFOCUS
    }
    return hw; }
  return NULL; }

static struct win *getwin(HWND h){ uintptr_t v=(uintptr_t)h; if(v<0x10000||(v-0x10000)%4) return NULL; v=(v-0x10000)/4; return v<256&&wins[v].used?&wins[v]:NULL; }
BOOL WINAPI W_DestroyWindow(HWND h){ struct win *w=getwin(h); if(!w) return 0; if(w->proc) ((WNDPROC)w->proc)(h,2,0,0); w->used=0; return 1; }
BOOL WINAPI W_ShowWindow(HWND h,int c){
    struct win *w=getwin(h);
    if(w) {
        w->visible=c!=0;
        if (w->proc) {
            ((WNDPROC)w->proc)(h, 0x001C, 1, 0); // WM_ACTIVATEAPP
            ((WNDPROC)w->proc)(h, 0x0006, 1, 0); // WM_ACTIVATE (WA_ACTIVE)
            ((WNDPROC)w->proc)(h, 0x0007, 0, 0); // WM_SETFOCUS
        }
    }
    return 1;
}
BOOL WINAPI W_UpdateWindow(HWND h){ return 1; }

intptr_t WINAPI W_CallWindowProcA(void *proc, HWND h, UINT m, uintptr_t w, intptr_t l) {
    if (proc) return ((WNDPROC)proc)(h, m, w, l);
    return 0;
}

intptr_t WINAPI W_SendMessageA(HWND h, UINT m, uintptr_t w, intptr_t l) {
    struct win *win = getwin(h);
    return (win && win->proc) ? ((WNDPROC)win->proc)(h, m, w, l) : 0;
}

intptr_t WINAPI W_DefWindowProcA(HWND h,UINT m,uintptr_t w,intptr_t l){ if(m==0x10) W_DestroyWindow(h); return 0; }
BOOL WINAPI W_GetWindowRect(HWND h,int *r){ struct win *w=getwin(h); r[0]=w?w->x:0; r[1]=w?w->y:0; r[2]=r[0]+(w?w->w:640); r[3]=r[1]+(w?w->h:480); return 1; }
HWND WINAPI W_GetDesktopWindow(void){ return g_main_hwnd ? g_main_hwnd : (HWND)0x10004; }
void WINAPI W_PostQuitMessage(int c){ quit_pending=1; quit_code=c; }

/* ---- Input Event Queue & Key State ---- */
typedef struct {
    uint32_t hwnd;
    uint32_t message;
    uint32_t wParam;
    uint32_t lParam;
    uint32_t time;
    int32_t  pt_x;
    int32_t  pt_y;
} WIN32_MSG32;

static WIN32_MSG32 msg_queue[64];
static int msg_head = 0, msg_tail = 0;
static uint8_t g_vk_state[256] = {0};
static int g_mouse_x = 320, g_mouse_y = 240;

static void push_msg(uint32_t message, uint32_t wParam, uint32_t lParam) {
    int next = (msg_head + 1) % 64;
    if (next == msg_tail) return;
    msg_queue[msg_head].hwnd = (uint32_t)(uintptr_t)W_GetDesktopWindow();
    msg_queue[msg_head].message = message;
    msg_queue[msg_head].wParam = wParam;
    msg_queue[msg_head].lParam = lParam;
    msg_queue[msg_head].time = SDL_GetTicks();
    msg_queue[msg_head].pt_x = g_mouse_x;
    msg_queue[msg_head].pt_y = g_mouse_y;
    msg_head = next;
}






extern void process_sdl_event_for_dinput(const SDL_Event *event);

extern uint8_t sdl_scancode_to_dik(SDL_Scancode sc);

static uint32_t sdl_key_to_vk(SDL_Keycode sym) {
    if (sym >= 'a' && sym <= 'z') return sym - 'a' + 'A';
    if (sym >= '0' && sym <= '9') return sym;
    switch (sym) {
        case SDLK_BACKSPACE: return 0x08;
        case SDLK_TAB:       return 0x09;
        case SDLK_RETURN:    return 0x0D; /* VK_RETURN */
        case SDLK_ESCAPE:    return 0x1B; /* VK_ESCAPE */
        case SDLK_SPACE:     return 0x20;
        case SDLK_LEFT:      return 0x25;
        case SDLK_UP:        return 0x26;
        case SDLK_RIGHT:     return 0x27;
        case SDLK_DOWN:      return 0x28;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:    return 0x10; /* VK_SHIFT */
        case SDLK_LCTRL:
        case SDLK_RCTRL:     return 0x11; /* VK_CONTROL */
        case SDLK_LALT:
        case SDLK_RALT:      return 0x12; /* VK_MENU */
        default:             return (sym >= 32 && sym <= 126) ? (uint32_t)sym : 0;
    }
}

void pump_sdl_input_events(void) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        process_sdl_event_for_dinput(&e);

        switch (e.type) {
            case SDL_QUIT:
                quit_pending = 1;
                quit_code = 0;
                push_msg(0x0012, 0, 0);
                break;

            case SDL_KEYDOWN: {
                uint32_t vk = sdl_key_to_vk(e.key.keysym.sym);
                uint32_t dik = W_MapVirtualKeyA(vk, 0);
                if (!dik) dik = sdl_scancode_to_dik(e.key.keysym.scancode);

                if (vk < 256) g_vk_state[vk] = 0x80;

                /* Bit 16-23 of lParam must contain the DirectInput hardware scancode */
                uint32_t lp = ((dik & 0xFF) << 16) | 1;
                if (e.key.repeat) lp |= (1U << 30);

                if (vk) push_msg(0x0100, vk, lp);
		
                /*if (e.key.keysym.sym >= 32 && e.key.keysym.sym <= 126) {
                    push_msg(0x0102, e.key.keysym.sym, lp);
                }*/
                break;
            }

            case SDL_KEYUP: {
                uint32_t vk = sdl_key_to_vk(e.key.keysym.sym);
                uint32_t dik = W_MapVirtualKeyA(vk, 0);
                if (!dik) dik = sdl_scancode_to_dik(e.key.keysym.scancode);

                if (vk < 256) g_vk_state[vk] = 0x00;

                uint32_t lp = ((dik & 0xFF) << 16) | 1 | (1U << 30) | (1U << 31);
                if (vk) push_msg(0x0101, vk, lp);
                break;
            }

            case SDL_MOUSEMOTION: {
                g_mouse_x = e.motion.x;
                g_mouse_y = e.motion.y;
                uint32_t lp = ((uint32_t)(uint16_t)e.motion.y << 16) | (uint16_t)e.motion.x;
                push_msg(0x0200, 0, lp);
                break;
            }

            case SDL_MOUSEBUTTONDOWN: {
                g_mouse_x = e.button.x;
                g_mouse_y = e.button.y;
                uint32_t lp = ((uint32_t)(uint16_t)e.button.y << 16) | (uint16_t)e.button.x;
                uint32_t msg = (e.button.button == SDL_BUTTON_LEFT) ? 0x0201 : 0x0204;
                push_msg(msg, 0, lp);
                break;
            }

            case SDL_MOUSEBUTTONUP: {
                g_mouse_x = e.button.x;
                g_mouse_y = e.button.y;
                uint32_t lp = ((uint32_t)(uint16_t)e.button.y << 16) | (uint16_t)e.button.x;
                uint32_t msg = (e.button.button == SDL_BUTTON_LEFT) ? 0x0202 : 0x0205;
                push_msg(msg, 0, lp);
                break;
            }
        }
    }
}




/*
void pump_sdl_input_events(void) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                quit_pending = 1;
                quit_code = 0;
                push_msg(0x0012, 0, 0);
                break;

            case SDL_KEYDOWN: {
                uint32_t vk = sdl_key_to_vk(e.key.keysym.sym);
                if (vk < 256) g_vk_state[vk] = 0x80;
                if (vk) push_msg(0x0100, vk, 0);
                if (e.key.keysym.sym >= 32 && e.key.keysym.sym <= 126) {
                    push_msg(0x0102, e.key.keysym.sym, 0);
                }
                break;
            }

            case SDL_KEYUP: {
                uint32_t vk = sdl_key_to_vk(e.key.keysym.sym);
                if (vk < 256) g_vk_state[vk] = 0x00;
                if (vk) push_msg(0x0101, vk, 0);
                break;
            }

            case SDL_MOUSEMOTION: {
                g_mouse_x = e.motion.x;
                g_mouse_y = e.motion.y;
                uint32_t lp = ((uint32_t)(uint16_t)e.motion.y << 16) | (uint16_t)e.motion.x;
                push_msg(0x0200, 0, lp);
                break;
            }

            case SDL_MOUSEBUTTONDOWN: {
                g_mouse_x = e.button.x;
                g_mouse_y = e.button.y;
                uint32_t lp = ((uint32_t)(uint16_t)e.button.y << 16) | (uint16_t)e.button.x;
                uint32_t msg = (e.button.button == SDL_BUTTON_LEFT) ? 0x0201 : 0x0204;
                push_msg(msg, 0, lp);
                break;
            }

            case SDL_MOUSEBUTTONUP: {
                g_mouse_x = e.button.x;
                g_mouse_y = e.button.y;
                uint32_t lp = ((uint32_t)(uint16_t)e.button.y << 16) | (uint16_t)e.button.x;
                uint32_t msg = (e.button.button == SDL_BUTTON_LEFT) ? 0x0202 : 0x0205;
                push_msg(msg, 0, lp);
                break;
            }
        }
    }
}*/

BOOL WINAPI W_PeekMessageA(uint32_t *msg, HWND h, UINT lo, UINT hi, UINT rm) {
    pump_sdl_input_events();

    if (quit_pending && msg_tail == msg_head) {
        if (msg) {
            memset(msg, 0, 28);
            msg[1] = 0x12;
            msg[2] = quit_code;
        }
        if (rm & 1) quit_pending = 0;
        return 1;
    }

    if (msg_tail != msg_head) {
        if (msg) {
            WIN32_MSG32 *m = (WIN32_MSG32*)msg;
            *m = msg_queue[msg_tail];
        }
        if (rm & 1) {
            msg_tail = (msg_tail + 1) % 64;
        }
        return 1;
    }
    return 0;
}

BOOL WINAPI W_TranslateMessage(const void *m){ return 0; }
intptr_t WINAPI W_DispatchMessageA(const uint32_t *m){ struct win *w=getwin((HWND)m[0]); return w&&w->proc?((WNDPROC)w->proc)((HWND)m[0],m[1],m[2],m[3]):0; }
HDC WINAPI W_GetDC(HWND h){ return (HDC)0x20004; } int WINAPI W_ReleaseDC(HWND h,HDC d){ return 1; }
HDC WINAPI W_BeginPaint(HWND h,void *ps){ memset(ps,0,64); return (HDC)0x20004; } BOOL WINAPI W_EndPaint(HWND h,const void *ps){ return 1; }
BOOL WINAPI W_IsIconic(HWND h){ return 0; } HWND WINAPI W_SetFocus(HWND h){ return g_main_hwnd ? g_main_hwnd : (HWND)0x10004; }
HCURSOR WINAPI W_SetCursor(HCURSOR c){ return NULL; }

int WINAPI W_ShowCursor(BOOL s){
    if (s) {
        SDL_ShowCursor(SDL_ENABLE);
        SDL_SetRelativeMouseMode(SDL_FALSE);
    } else {
        SDL_ShowCursor(SDL_DISABLE);
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    return s ? 1 : -1;
}

BOOL WINAPI W_ClipCursor(const void *r){ return 1; } BOOL WINAPI W_SetCursorPos(int x,int y){ return 1; }
short WINAPI W_GetAsyncKeyState(int k){ return (k>=0 && k<256 && g_vk_state[k]) ? (short)0x8000 : 0; }
BOOL WINAPI W_GetKeyboardState(BYTE *s){ if(s) memcpy(s,g_vk_state,256); return 1; }
int WINAPI W_ToAscii(UINT vk,UINT sc,const BYTE *ks,WORD *out,UINT fl){ return 0; }
HICON WINAPI W_LoadIconA(HINSTANCE i,LPCSTR n){ return (HICON)1; } HCURSOR WINAPI W_LoadCursorA(HINSTANCE i,LPCSTR n){ return (HCURSOR)1; } HANDLE WINAPI W_LoadImageA(HINSTANCE i,LPCSTR n,UINT t,int x,int y,UINT f){ return (HANDLE)1; }
DWORD WINAPI W_GetClassLongA(HWND h,int i){ return 0; }
int WINAPI W_MessageBoxA(HWND h,LPCSTR text,LPCSTR cap,UINT type){ fprintf(stderr,"[MessageBox] %s: %s",cap?cap:"",text?text:""); fflush(stderr); UINT k=type&0xf; return (k==4||k==3)?6:1; }
int W_wsprintfA(char *buf,const char *fmt,...){ va_list a; va_start(a,fmt); int n=vsprintf(buf,fmt,a); va_end(a); return n; }
int WINAPI W_wvsprintfA(char *buf,const char *fmt,va_list a){ return vsprintf(buf,fmt,a); }

/* ---- gdi32 ---- */
//HANDLE WINAPI W_CreateDIBSection(HDC dc,const uint32_t *bi,UINT use,void **bits,HANDLE sec,DWORD off){ int w=(int)bi[1],h=(int)bi[2]; if(h<0)h=-h; int bpp=((WORD*)bi)[7]; size_t sz=(size_t)h*(((w*bpp+31)/32)*4); void *p=calloc(1,sz?sz:4); if(bits)*bits=p; return p; }
BOOL WINAPI W_Rectangle(HDC d,int a,int b,int c,int e){ return 1; } //BOOL WINAPI W_TextOutA(HDC d,int x,int y,LPCSTR s,int n){ return 1; }
//BOOL WINAPI W_GetTextExtentPoint32A(HDC d,LPCSTR s,int n,int *sz){ sz[0]=n*8; sz[1]=16; return 1; }
int WINAPI W_GetTextCharacterExtra(HDC d){ return 0; } int WINAPI W_SetTextCharacterExtra(HDC d,int e){ return 0; }
//BOOL WINAPI W_DeleteObject(HGDIOBJ o){ return 1; } HANDLE WINAPI W_CreateFontA(int a,int b,int c,int d,int e,DWORD f,DWORD g,DWORD h,DWORD i,DWORD j,DWORD k,DWORD l,DWORD m,LPCSTR n){ return (HANDLE)1; }
//HDC WINAPI W_CreateCompatibleDC(HDC d){ return (HDC)0x20008; } HGDIOBJ WINAPI W_SelectObject(HDC d,HGDIOBJ o){ return (HGDIOBJ)1; }
//DWORD WINAPI W_SetTextColor(HDC d,DWORD c){ return 0; } int WINAPI W_SetBkMode(HDC d,int m){ return 1; } DWORD WINAPI W_SetBkColor(HDC d,DWORD c){ return 0; }
//HGDIOBJ WINAPI W_GetStockObject(int i){ return (HGDIOBJ)1; } BOOL WINAPI W_DeleteDC(HDC d){ return 1; }

/* custom added */

/* ---- Built-in 8x16 ASCII Font Rasterizer for GDI TextOutA ---- *//*
static const uint8_t font8x16_basic[128][16] = {
    ['A'] = {0x00,0x00,0x10,0x28,0x44,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x00,0x00,0x00,0x00},
    ['B'] = {0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x42,0x42,0x42,0xFC,0x00,0x00,0x00,0x00,0x00},
    ['C'] = {0x00,0x00,0x3C,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['D'] = {0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00,0x00,0x00,0x00},
    ['E'] = {0x00,0x00,0xFE,0x40,0x40,0x40,0x7C,0x40,0x40,0x40,0xFE,0x00,0x00,0x00,0x00,0x00},
    ['F'] = {0x00,0x00,0xFE,0x40,0x40,0x40,0x7C,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00},
    ['G'] = {0x00,0x00,0x3C,0x42,0x80,0x80,0x8E,0x82,0x82,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['H'] = {0x00,0x00,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['I'] = {0x00,0x00,0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,0x00,0x00},
    ['J'] = {0x00,0x00,0x1C,0x08,0x08,0x08,0x08,0x08,0x88,0x88,0x70,0x00,0x00,0x00,0x00,0x00},
    ['K'] = {0x00,0x00,0x84,0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88,0x84,0x00,0x00,0x00,0x00,0x00},
    ['L'] = {0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7E,0x00,0x00,0x00,0x00,0x00},
    ['M'] = {0x00,0x00,0x82,0xC6,0xAA,0x92,0x82,0x82,0x82,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['N'] = {0x00,0x00,0x82,0xC2,0xA2,0x92,0x8A,0x86,0x82,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['O'] = {0x00,0x00,0x3C,0x42,0x81,0x81,0x81,0x81,0x81,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['P'] = {0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00},
    ['Q'] = {0x00,0x00,0x3C,0x42,0x81,0x81,0x81,0x89,0x85,0x42,0x3D,0x00,0x00,0x00,0x00,0x00},
    ['R'] = {0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x48,0x44,0x42,0x41,0x00,0x00,0x00,0x00,0x00},
    ['S'] = {0x00,0x00,0x3C,0x42,0x40,0x30,0x0C,0x02,0x42,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['T'] = {0x00,0x00,0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00},
    ['U'] = {0x00,0x00,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['V'] = {0x00,0x00,0x82,0x82,0x82,0x82,0x44,0x44,0x28,0x28,0x10,0x00,0x00,0x00,0x00,0x00},
    ['W'] = {0x00,0x00,0x82,0x82,0x82,0x82,0x92,0xAA,0xC6,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['X'] = {0x00,0x00,0x82,0x44,0x28,0x10,0x10,0x28,0x44,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['Y'] = {0x00,0x00,0x82,0x44,0x28,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00},
    ['Z'] = {0x00,0x00,0xFE,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xFE,0x00,0x00,0x00,0x00,0x00},
    ['0'] = {0x00,0x00,0x3C,0x42,0x46,0x4A,0x52,0x62,0x42,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['1'] = {0x00,0x00,0x10,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,0x00,0x00},
    ['2'] = {0x00,0x00,0x3C,0x42,0x02,0x04,0x08,0x10,0x20,0x40,0xFE,0x00,0x00,0x00,0x00,0x00},
    ['3'] = {0x00,0x00,0x3C,0x42,0x02,0x04,0x18,0x02,0x02,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['4'] = {0x00,0x00,0x08,0x18,0x28,0x48,0x88,0xFE,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00},
    ['5'] = {0x00,0x00,0xFE,0x40,0x40,0x7C,0x02,0x02,0x02,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['6'] = {0x00,0x00,0x3C,0x40,0x80,0xFC,0x82,0x82,0x82,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['7'] = {0x00,0x00,0xFE,0x02,0x04,0x08,0x10,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00},
    ['8'] = {0x00,0x00,0x3C,0x42,0x42,0x42,0x3C,0x42,0x42,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['9'] = {0x00,0x00,0x3C,0x42,0x82,0x82,0x7E,0x02,0x02,0x04,0x38,0x00,0x00,0x00,0x00,0x00},
    [':'] = {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['x'] = {0x00,0x00,0x00,0x00,0x00,0x82,0x44,0x28,0x10,0x28,0x44,0x82,0x00,0x00,0x00,0x00},
    [' '] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

typedef struct {
    HDC hdc;
    void *bits;
    int w;
    int h;
    int bpp;
    size_t sz;
} DIB_MAP;
static DIB_MAP g_dibs[64];
static int g_ndibs = 0;

HANDLE WINAPI W_CreateDIBSection(HDC dc, const uint32_t *bi, UINT use, void **bits, HANDLE sec, DWORD off) {
    if (!bi) return NULL;
    int w = (int)bi[1];
    int h = (int)bi[2];
    if (h < 0) h = -h;
    if (w <= 0 || h <= 0) return NULL;
    
    int bpp = ((WORD*)bi)[7];
    if (bpp == 0) bpp = 32;

    size_t pitch = ((w * bpp + 31) / 32) * 4;
    size_t sz = (size_t)h * pitch;
    void *p = calloc(1, sz ? sz : 16);
    if (bits) *bits = p;

    if (g_ndibs < 64) {
        g_dibs[g_ndibs].hdc = dc ? dc : (HDC)0x20004;
        g_dibs[g_ndibs].bits = p;
        g_dibs[g_ndibs].w = w;
        g_dibs[g_ndibs].h = h;
        g_dibs[g_ndibs].bpp = bpp;
        g_dibs[g_ndibs].sz = sz;
        g_ndibs++;
    }
    return p;
}

BOOL WINAPI W_TextOutA(HDC d, int x, int y, LPCSTR s, int n) {
    if (!s || n <= 0) return 1;

    DIB_MAP *dib = NULL;
    for (int i = g_ndibs - 1; i >= 0; i--) {
        if (g_dibs[i].hdc == d || d == (HDC)0x20004 || d == (HDC)0x20008) {
            if (g_dibs[i].bits) { dib = &g_dibs[i]; break; }
        }
    }
    if (!dib && g_ndibs > 0) dib = &g_dibs[g_ndibs - 1];
    if (!dib || !dib->bits || dib->w <= 0 || dib->h <= 0) return 1;

    uint8_t *raw_bits = (uint8_t*)dib->bits;
    int bytes_per_pixel = dib->bpp / 8;
    if (bytes_per_pixel <= 0) bytes_per_pixel = 4;
    int pitch = ((dib->w * dib->bpp + 31) / 32) * 4;

    for (int c = 0; c < n; c++) {
        unsigned char ch = (unsigned char)s[c];
        if (ch >= 128) ch = '?';

        int char_x = x + (c * 8);
        for (int row = 0; row < 16; row++) {
            int py = y + row;
            if (py < 0 || py >= dib->h) continue;

            uint8_t bits = font8x16_basic[ch][row];
            for (int col = 0; col < 8; col++) {
                int px = char_x + col;
                if (px < 0 || px >= dib->w) continue;

                if (bits & (0x80 >> col)) {
                    size_t offset = (size_t)py * pitch + (size_t)px * bytes_per_pixel;
                    if (offset + bytes_per_pixel <= dib->sz) {
                        memset(raw_bits + offset, 0xFF, bytes_per_pixel);
                    }
                }
            }
        }
    }
    return 1;
}

BOOL WINAPI W_GetTextExtentPoint32A(HDC d, LPCSTR s, int n, int *sz) {
    if (sz) {
        sz[0] = n * 8;
        sz[1] = 16;
    }
    return 1;
}*/



/* ---- Dynamic GDI & DIB Section Subsystem ---- */
HANDLE WINAPI W_CreateFontA(int a, int b, int c, int d, int e, DWORD f, DWORD g, DWORD h, DWORD i, DWORD j, DWORD k, DWORD l, DWORD m, LPCSTR n) {
    return (HANDLE)1;
}

HGDIOBJ WINAPI W_GetStockObject(int i) {
    return (HGDIOBJ)1;
}

typedef struct {
    uint32_t magic; // 'BMP ' (0x42494D50)
    int w, h, bpp;
    size_t pitch, sz;
    void *bits;
} GDI_BITMAP;

typedef struct {
    uint32_t magic; // 'DC00' (0x44433030)
    GDI_BITMAP *selected_bmp;
    DWORD text_color;
    DWORD bk_color;
    int bk_mode;
} GDI_DC;

static GDI_DC g_default_dc = { .magic = 0x44433030, .selected_bmp = NULL, .text_color = 0x00FFFFFF, .bk_color = 0, .bk_mode = 1 };

static GDI_DC* get_gdi_dc(HDC hdc) {
    uintptr_t v = (uintptr_t)hdc;
    if (!hdc || v < 0x10000) return &g_default_dc; /* Safe guard against fake handles like 0x20004 */
    GDI_DC *d = (GDI_DC*)(uintptr_t)hdc;
    if (d->magic == 0x44433030) return d;
    return &g_default_dc;
}

static GDI_BITMAP* get_gdi_bmp(HANDLE hbmp) {
    uintptr_t v = (uintptr_t)hbmp;
    if (!hbmp || v < 0x10000) return NULL; /* Safe guard against fake handles like (HANDLE)1 */
    GDI_BITMAP *b = (GDI_BITMAP*)(uintptr_t)hbmp;
    if (b->magic == 0x42494D50) return b;
    return NULL;
}

/* Full Printable ASCII 8x16 Font Bitmap Table */
static const uint8_t font8x16_full[128][16] = {
    ['A'] = {0x00,0x00,0x10,0x28,0x44,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x00,0x00,0x00,0x00},
    ['B'] = {0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x42,0x42,0x42,0xFC,0x00,0x00,0x00,0x00,0x00},
    ['C'] = {0x00,0x00,0x3C,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['D'] = {0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00,0x00,0x00,0x00},
    ['E'] = {0x00,0x00,0xFE,0x40,0x40,0x40,0x7C,0x40,0x40,0x40,0xFE,0x00,0x00,0x00,0x00,0x00},
    ['F'] = {0x00,0x00,0xFE,0x40,0x40,0x40,0x7C,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00},
    ['G'] = {0x00,0x00,0x3C,0x42,0x80,0x80,0x8E,0x82,0x82,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['H'] = {0x00,0x00,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['I'] = {0x00,0x00,0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,0x00,0x00},
    ['J'] = {0x00,0x00,0x1C,0x08,0x08,0x08,0x08,0x08,0x88,0x88,0x70,0x00,0x00,0x00,0x00,0x00},
    ['K'] = {0x00,0x00,0x84,0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88,0x84,0x00,0x00,0x00,0x00,0x00},
    ['L'] = {0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7E,0x00,0x00,0x00,0x00,0x00},
    ['M'] = {0x00,0x00,0x82,0xC6,0xAA,0x92,0x82,0x82,0x82,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['N'] = {0x00,0x00,0x82,0xC2,0xA2,0x92,0x8A,0x86,0x82,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['O'] = {0x00,0x00,0x3C,0x42,0x81,0x81,0x81,0x81,0x81,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['P'] = {0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00},
    ['Q'] = {0x00,0x00,0x3C,0x42,0x81,0x81,0x81,0x89,0x85,0x42,0x3D,0x00,0x00,0x00,0x00,0x00},
    ['R'] = {0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x48,0x44,0x42,0x41,0x00,0x00,0x00,0x00,0x00},
    ['S'] = {0x00,0x00,0x3C,0x42,0x40,0x30,0x0C,0x02,0x42,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['T'] = {0x00,0x00,0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00},
    ['U'] = {0x00,0x00,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['V'] = {0x00,0x00,0x82,0x82,0x82,0x82,0x44,0x44,0x28,0x28,0x10,0x00,0x00,0x00,0x00,0x00},
    ['W'] = {0x00,0x00,0x82,0x82,0x82,0x82,0x92,0xAA,0xC6,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['X'] = {0x00,0x00,0x82,0x44,0x28,0x10,0x10,0x28,0x44,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['Y'] = {0x00,0x00,0x82,0x44,0x28,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00},
    ['Z'] = {0x00,0x00,0xFE,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xFE,0x00,0x00,0x00,0x00,0x00},

    ['a'] = {0x00,0x00,0x00,0x00,0x00,0x3C,0x02,0x3E,0x42,0x46,0x3A,0x00,0x00,0x00,0x00,0x00},
    ['b'] = {0x00,0x00,0x80,0x80,0x80,0xBC,0x82,0x82,0x82,0x82,0xBC,0x00,0x00,0x00,0x00,0x00},
    ['c'] = {0x00,0x00,0x00,0x00,0x00,0x3E,0x40,0x40,0x40,0x40,0x3E,0x00,0x00,0x00,0x00,0x00},
    ['d'] = {0x00,0x00,0x02,0x02,0x02,0x3E,0x42,0x42,0x42,0x42,0x3E,0x00,0x00,0x00,0x00,0x00},
    ['e'] = {0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x40,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['f'] = {0x00,0x00,0x0C,0x12,0x10,0x7C,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00},
    ['g'] = {0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x42,0x3E,0x02,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['h'] = {0x00,0x00,0x80,0x80,0x80,0xBC,0x82,0x82,0x82,0x82,0x82,0x00,0x00,0x00,0x00,0x00},
    ['i'] = {0x00,0x00,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,0x00,0x00},
    ['j'] = {0x00,0x00,0x08,0x00,0x00,0x18,0x08,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x00,0x00},
    ['k'] = {0x00,0x00,0x80,0x80,0x80,0x84,0x88,0xF0,0x88,0x84,0x82,0x00,0x00,0x00,0x00,0x00},
    ['l'] = {0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,0x00,0x00},
    ['m'] = {0x00,0x00,0x00,0x00,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0x00,0x00,0x00,0x00,0x00},
    ['n'] = {0x00,0x00,0x00,0x00,0x00,0xDC,0x62,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x00,0x00},
    ['o'] = {0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['p'] = {0x00,0x00,0x00,0x00,0x00,0xBC,0x82,0x82,0x82,0xBE,0x80,0x80,0x00,0x00,0x00,0x00},
    ['q'] = {0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x42,0x42,0x3E,0x02,0x02,0x00,0x00,0x00,0x00},
    ['r'] = {0x00,0x00,0x00,0x00,0x00,0x5C,0x62,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00},
    ['s'] = {0x00,0x00,0x00,0x00,0x00,0x3E,0x40,0x3C,0x02,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['t'] = {0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x12,0x0C,0x00,0x00,0x00,0x00,0x00},
    ['u'] = {0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,0x00,0x00},
    ['v'] = {0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x24,0x24,0x18,0x18,0x00,0x00,0x00,0x00,0x00},
    ['w'] = {0x00,0x00,0x00,0x00,0x00,0x82,0x82,0x92,0xAA,0x44,0x44,0x00,0x00,0x00,0x00,0x00},
    ['x'] = {0x00,0x00,0x00,0x00,0x00,0x82,0x44,0x28,0x10,0x28,0x44,0x82,0x00,0x00,0x00,0x00},
    ['y'] = {0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x3E,0x02,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['z'] = {0x00,0x00,0x00,0x00,0x00,0x7E,0x04,0x08,0x10,0x20,0x7E,0x00,0x00,0x00,0x00,0x00},

    ['0'] = {0x00,0x00,0x3C,0x42,0x46,0x4A,0x52,0x62,0x42,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['1'] = {0x00,0x00,0x10,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,0x00,0x00},
    ['2'] = {0x00,0x00,0x3C,0x42,0x02,0x04,0x08,0x10,0x20,0x40,0xFE,0x00,0x00,0x00,0x00,0x00},
    ['3'] = {0x00,0x00,0x3C,0x42,0x02,0x04,0x18,0x02,0x02,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['4'] = {0x00,0x00,0x08,0x18,0x28,0x48,0x88,0xFE,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00},
    ['5'] = {0x00,0x00,0xFE,0x40,0x40,0x7C,0x02,0x02,0x02,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['6'] = {0x00,0x00,0x3C,0x40,0x80,0xFC,0x82,0x82,0x82,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['7'] = {0x00,0x00,0xFE,0x02,0x04,0x08,0x10,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00},
    ['8'] = {0x00,0x00,0x3C,0x42,0x42,0x42,0x3C,0x42,0x42,0x42,0x3C,0x00,0x00,0x00,0x00,0x00},
    ['9'] = {0x00,0x00,0x3C,0x42,0x82,0x82,0x7E,0x02,0x02,0x04,0x38,0x00,0x00,0x00,0x00,0x00},

    ['-'] = {0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['_'] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00},
    ['['] = {0x00,0x00,0x3C,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3C,0x00,0x00,0x00,0x00,0x00},
    [']'] = {0x00,0x00,0x3C,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x3C,0x00,0x00,0x00,0x00,0x00},
    [':'] = {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['.'] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00},
    ['/'] = {0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['#'] = {0x00,0x00,0x24,0x24,0x7E,0x24,0x24,0x7E,0x24,0x24,0x00,0x00,0x00,0x00,0x00,0x00},
    ['%'] = {0x00,0x00,0x62,0x64,0x08,0x10,0x20,0x4C,0x8C,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['<'] = {0x00,0x00,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['>'] = {0x00,0x00,0x20,0x10,0x08,0x04,0x08,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['='] = {0x00,0x00,0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['\'']= {0x00,0x00,0x10,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['?'] = {0x00,0x00,0x3C,0x42,0x02,0x04,0x08,0x10,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x00},
    [' '] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

HDC WINAPI W_CreateCompatibleDC(HDC d) {
    GDI_DC *dc = calloc(1, sizeof(GDI_DC));
    dc->magic = 0x44433030;
    dc->text_color = 0x00FFFFFF;
    dc->bk_color = 0x00000000;
    dc->bk_mode = 1;
    return (HDC)(uintptr_t)dc;
}

BOOL WINAPI W_DeleteDC(HDC d) {
    GDI_DC *dc = (GDI_DC*)(uintptr_t)d;
    if (dc && dc->magic == 0x44433030) free(dc);
    return 1;
}

HANDLE WINAPI W_CreateDIBSection(HDC dc, const uint32_t *bi, UINT use, void **bits, HANDLE sec, DWORD off) {
    if (!bi) return NULL;
    int w = (int)bi[1];
    int h = (int)bi[2];
    if (h < 0) h = -h;
    if (w <= 0 || h <= 0) return NULL;

    int bpp = ((WORD*)bi)[7];
    if (bpp == 0) bpp = 32;

    size_t pitch = ((w * bpp + 31) / 32) * 4;
    size_t sz = (size_t)h * pitch;
    void *p = calloc(1, sz ? sz : 16);
    if (bits) *bits = p;

    GDI_BITMAP *bmp = calloc(1, sizeof(GDI_BITMAP));
    bmp->magic = 0x42494D50;
    bmp->w = w;
    bmp->h = h;
    bmp->bpp = bpp;
    bmp->pitch = pitch;
    bmp->sz = sz;
    bmp->bits = p;

    GDI_DC *gdc = get_gdi_dc(dc);
    if (gdc != &g_default_dc) gdc->selected_bmp = bmp;

    return (HANDLE)(uintptr_t)bmp;
}

HGDIOBJ WINAPI W_SelectObject(HDC d, HGDIOBJ o) {
    GDI_DC *dc = get_gdi_dc(d);
    GDI_BITMAP *bmp = get_gdi_bmp((HANDLE)o);
    if (bmp) {
        HGDIOBJ old = (HGDIOBJ)(uintptr_t)dc->selected_bmp;
        dc->selected_bmp = bmp;
        return old;
    }
    return (HGDIOBJ)1;
}

BOOL WINAPI W_DeleteObject(HGDIOBJ o) {
    GDI_BITMAP *bmp = get_gdi_bmp((HANDLE)o);
    if (bmp) {
        if (bmp->bits) free(bmp->bits);
        free(bmp);
        return 1;
    }
    return 1;
}

DWORD WINAPI W_SetTextColor(HDC d, DWORD c) {
    GDI_DC *dc = get_gdi_dc(d);
    DWORD old = dc->text_color;
    dc->text_color = c;
    return old;
}

DWORD WINAPI W_SetBkColor(HDC d, DWORD c) {
    GDI_DC *dc = get_gdi_dc(d);
    DWORD old = dc->bk_color;
    dc->bk_color = c;
    return old;
}

int WINAPI W_SetBkMode(HDC d, int m) {
    GDI_DC *dc = get_gdi_dc(d);
    int old = dc->bk_mode;
    dc->bk_mode = m;
    return old;
}

BOOL WINAPI W_TextOutA(HDC d, int x, int y, LPCSTR s, int n) {
    if (!s || n <= 0) return 1;

    GDI_DC *dc = get_gdi_dc(d);
    GDI_BITMAP *dib = dc->selected_bmp;

    if (!dib || !dib->bits || dib->w <= 0 || dib->h <= 0) return 1;

    uint8_t *raw_bits = (uint8_t*)dib->bits;
    int bytes_per_pixel = dib->bpp / 8;
    if (bytes_per_pixel <= 0) bytes_per_pixel = 4;
    size_t pitch = dib->pitch;

    for (int c = 0; c < n; c++) {
        unsigned char ch = (unsigned char)s[c];
        if (ch >= 128) ch = '?';

        int char_x = x + (c * 8);
        for (int row = 0; row < 16; row++) {
            int py = y + row;
            if (py < 0 || py >= dib->h) continue;

            uint8_t bits = font8x16_full[ch][row];
            for (int col = 0; col < 8; col++) {
                int px = char_x + col;
                if (px < 0 || px >= dib->w) continue;

                size_t offset = (size_t)py * pitch + (size_t)px * bytes_per_pixel;
                if (offset + bytes_per_pixel <= dib->sz) {
                    if (bits & (0x80 >> col)) {
                        memset(raw_bits + offset, 0xFF, bytes_per_pixel);
                    } else if (dc->bk_mode != 1) {
                        memset(raw_bits + offset, 0x00, bytes_per_pixel);
                    }
                }
            }
        }
    }
    return 1;
}

BOOL WINAPI W_GetTextExtentPoint32A(HDC d, LPCSTR s, int n, int *sz) {
    if (sz) {
        sz[0] = n * 8;
        sz[1] = 16;
    }
    return 1;
}

/* ---- ole32 ---- */
HRESULT WINAPI W_CoInitialize(void *r){ return 0; } void WINAPI W_CoUninitialize(void){}
HRESULT WINAPI W_CoCreateInstance(const void *clsid,void *outer,DWORD ctx,const void *iid,void **out){ if(out)*out=NULL; return 0x80040154; }

/* ---- winsock ---- */
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
BOOL WINAPI W_GetCursorPos(int *p){ if(p){ p[0]=g_mouse_x; p[1]=g_mouse_y; } return 1; }
HWND WINAPI W_GetActiveWindow(void){ return g_main_hwnd ? g_main_hwnd : (HWND)0x10004; }
HWND WINAPI W_GetFocus(void){ return g_main_hwnd ? g_main_hwnd : (HWND)0x10004; }
HWND WINAPI W_GetForegroundWindow(void){ return g_main_hwnd ? g_main_hwnd : (HWND)0x10004; }
BOOL WINAPI W_PostMessageA(HWND h,UINT m,uintptr_t w,intptr_t l){ return 1; }
BOOL WINAPI W_SetWindowTextA(HWND h,LPCSTR t){ return 1; }
BOOL WINAPI W_ClientToScreen(HWND h,int *p){ return 1; } BOOL WINAPI W_ScreenToClient(HWND h,int *p){ return 1; }
BOOL WINAPI W_SystemParametersInfoA(UINT a,UINT b,void *c,UINT d){ return 1; }
HRESULT WINAPI W_DirectSoundCreate(const void *g,void **out,void *outer){ if(out)*out=NULL; return 0x88780078; }
