/* DirectInput (v3..v7/v8) compatibility layer for LithTech engine native Linux port */
#include "win.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#ifndef STDCALL
  #if defined(__i386__) || defined(_M_IX86)
    #define STDCALL __attribute__((stdcall))
  #else
    #define STDCALL
  #endif
#endif

/* Set LT_INPUT_DEBUG=1 to trace the DirectInput layer on stderr. */
static int g_dbg = -1;
#define DBG(...) do { if (g_dbg < 0) g_dbg = getenv("LT_INPUT_DEBUG") != NULL; \
                      if (g_dbg) { fprintf(stderr, "[dinput] " __VA_ARGS__); fputc('\n', stderr); } } while (0)

#define DI_OK 0
#define DIENUM_STOP 0
#define DIENUM_CONTINUE 1

#define DIERR_NOTFOUND 0x80070002u
#define DIERR_DEVICENOTREG 0x80040154u
#define DIERR_NOTACQUIRED 0x8007001Eu

#define DIDFT_RELAXIS   0x00000001
#define DIDFT_BUTTON    0x0000000C
#ifndef DIDFT_PSHBUTTON
#define DIDFT_PSHBUTTON 0x00000004
#endif
#define DIDFT_MAKEINSTANCE(n) ((WORD)(n) << 8)

#define DIPH_DEVICE 0
#define DIPH_BYOFFSET 1
#define DIPH_BYID 2
#define DIGDD_PEEK 0x00000001

/* DirectInput 5 structure sizes prevent stack/heap memory overruns in LithTech */
#define DI5_DEVINSTANCE_SIZE   560  /* 0x230 */
#define DI5_OBJINSTANCE_SIZE   316  /* 0x13C: DX5+ DIDEVICEOBJECTINSTANCE; the engine copies 0x4F dwords of it */

typedef int (STDCALL *DIENUMDEVICEOBJECTSCALLBACKA)(void *inst, void *ref);
typedef int (STDCALL *DIENUMDEVICESCALLBACKA)(void *inst, void *ref);

struct com { void **vtbl; int ref; int kind; int acquired; };

static const uint8_t GUID_SysMouse[16]    = {0x60,0x2b,0x1d,0x6f,0xa0,0xd5,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00};
static const uint8_t GUID_SysKeyboard[16] = {0x61,0x2b,0x1d,0x6f,0xa0,0xd5,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00};

/* MUST be the real DirectInput GUID_Key {55728220-D33C-11CF-BFC7-444553540000}: the engine classifies an
   object as CONTROLTYPE_KEY by comparing its guidType with this value (table at 0x4cedcc in lithtech.exe). */
static const uint8_t GUID_Key[16]    = {0x20,0x82,0x72,0x55,0x3c,0xd3,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00};
static const uint8_t GUID_XAxis[16]  = {0xe0,0x02,0x6d,0xa3,0xf3,0xc9,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00};
static const uint8_t GUID_YAxis[16]  = {0xe1,0x02,0x6d,0xa3,0xf3,0xc9,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00};
static const uint8_t GUID_ZAxis[16]  = {0xe2,0x02,0x6d,0xa3,0xf3,0xc9,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00};
static const uint8_t GUID_Button[16] = {0xf0,0x02,0x6d,0xa3,0xf3,0xc9,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00};

static void *di_vtbl[10], *dev_vtbl[27];
static struct com *mk(void **v,int k){ struct com *c=calloc(1,sizeof *c); c->vtbl=v; c->ref=1; c->kind=k; c->acquired=1; return c; }

extern void pump_sdl_input_events(void);

typedef struct {
    DWORD dwOfs;        /* LOGICAL id (DIK for keyboard, 0..6 for mouse); translated to the app's offset on read */
    DWORD dwData;
    DWORD dwTimeStamp;
    DWORD dwSequence;
} DIDEVICEOBJECTDATA_COMPAT;

#define OFS_NONE 0xFFFFFFFFu
#define QUEUE_SIZE 256

typedef struct {
    DIDEVICEOBJECTDATA_COMPAT items[QUEUE_SIZE];
    int head;
    int tail;
    int count;
} EventQueue;

static EventQueue q_keyboard;
static EventQueue q_mouse;
static uint32_t g_sequence = 0;
static uint8_t g_dik_state[256] = {0};

/* Logical mouse ids: 0=X 1=Y 2=Z(wheel) 3..6=buttons 0..3 */
#define MID_X    0
#define MID_Y    1
#define MID_Z    2
#define MID_BTN0 3
#define MOUSE_IDS 7

/* Offsets the APPLICATION asked for through SetDataFormat.
   LithTech builds its own format: object i (in its internal list) sits at offset 4*i and the update code does
   object = table[dwOfs >> 2].  Returning the raw DIK / native offset therefore hits the wrong object
   (Q,W,E,R = 0x10..0x13 all collapse onto index 4). */
static DWORD kb_ofs[256];
static DWORD ms_ofs[MOUSE_IDS];

/* DEFAULT offsets (used whenever no real object format is active).  LithTech indexes its object table with
   dwOfs >> 2, where object i is the i-th object returned by EnumObjects.  We enumerate DIK 1..255 contiguously
   (object index = DIK-1) and the mouse as X,Y,Z,B0..B3 (index 0..6), so the matching offset is 4*index.
   Returning the raw DIK (the old default) picked object DIK>>2: Z->"4", S->"7", F1->"Tab" ... */
static void kb_format_default(void) {
    for (int i = 0; i < 256; i++) kb_ofs[i] = i ? (DWORD)(4 * (i - 1)) : OFS_NONE;
}
static void ms_format_default(void) {
    for (int i = 0; i < MOUSE_IDS; i++) ms_ofs[i] = (DWORD)(4 * i);
}
static void formats_default(void) { kb_format_default(); ms_format_default(); }

static void q_flush(EventQueue *q) {
    if (q) { q->head = 0; q->tail = 0; q->count = 0; }
}

static void q_push(EventQueue *q, DWORD id, DWORD data, DWORD timestamp) {
    if (!q) return;
    if (q->count >= QUEUE_SIZE) {
        q->head = (q->head + 1) % QUEUE_SIZE;
        q->count--;
    }
    q->items[q->tail].dwOfs = id;
    q->items[q->tail].dwData = data;
    q->items[q->tail].dwTimeStamp = timestamp;
    q->items[q->tail].dwSequence = g_sequence++;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    q->count++;
}

uint8_t sdl_scancode_to_dik(SDL_Scancode sc) {
    if (sc >= SDL_SCANCODE_A && sc <= SDL_SCANCODE_Z) {
        static const uint8_t alpha_dik[] = {
            0x1E, 0x30, 0x2E, 0x20, 0x12, 0x21, 0x22, 0x23, 0x17, 0x24,
            0x25, 0x26, 0x32, 0x31, 0x18, 0x19, 0x10, 0x13, 0x1F, 0x14,
            0x16, 0x2F, 0x11, 0x2D, 0x15, 0x2C
        };
        return alpha_dik[sc - SDL_SCANCODE_A];
    }
    if (sc >= SDL_SCANCODE_1 && sc <= SDL_SCANCODE_9) return 0x02 + (sc - SDL_SCANCODE_1);
    if (sc == SDL_SCANCODE_0) return 0x0B;

    switch (sc) {
        case SDL_SCANCODE_ESCAPE:       return 0x01;
        case SDL_SCANCODE_MINUS:        return 0x0C;
        case SDL_SCANCODE_EQUALS:       return 0x0D;
        case SDL_SCANCODE_BACKSPACE:    return 0x0E;
        case SDL_SCANCODE_TAB:          return 0x0F;
        case SDL_SCANCODE_LEFTBRACKET:  return 0x1A;
        case SDL_SCANCODE_RIGHTBRACKET: return 0x1B;
        case SDL_SCANCODE_RETURN:       return 0x1C;
        case SDL_SCANCODE_LCTRL:        return 0x1D;
        case SDL_SCANCODE_SEMICOLON:    return 0x27;
        case SDL_SCANCODE_APOSTROPHE:   return 0x28;
        case SDL_SCANCODE_GRAVE:        return 0x29;
        case SDL_SCANCODE_LSHIFT:       return 0x2A;
        case SDL_SCANCODE_BACKSLASH:    return 0x2B;
        case SDL_SCANCODE_COMMA:        return 0x33;
        case SDL_SCANCODE_PERIOD:       return 0x34;
        case SDL_SCANCODE_SLASH:        return 0x35;
        case SDL_SCANCODE_RSHIFT:       return 0x36;
        case SDL_SCANCODE_KP_MULTIPLY:  return 0x37;
        case SDL_SCANCODE_LALT:         return 0x38;
        case SDL_SCANCODE_SPACE:        return 0x39;
        case SDL_SCANCODE_CAPSLOCK:     return 0x3A;
        case SDL_SCANCODE_F1:           return 0x3B;
        case SDL_SCANCODE_F2:           return 0x3C;
        case SDL_SCANCODE_F3:           return 0x3D;
        case SDL_SCANCODE_F4:           return 0x3E;
        case SDL_SCANCODE_F5:           return 0x3F;
        case SDL_SCANCODE_F6:           return 0x40;
        case SDL_SCANCODE_F7:           return 0x41;
        case SDL_SCANCODE_F8:           return 0x42;
        case SDL_SCANCODE_F9:           return 0x43;
        case SDL_SCANCODE_F10:          return 0x44;
        case SDL_SCANCODE_NUMLOCKCLEAR: return 0x45;
        case SDL_SCANCODE_SCROLLLOCK:   return 0x46;
        case SDL_SCANCODE_KP_7:         return 0x47;
        case SDL_SCANCODE_KP_8:         return 0x48;
        case SDL_SCANCODE_KP_9:         return 0x49;
        case SDL_SCANCODE_KP_MINUS:     return 0x4A;
        case SDL_SCANCODE_KP_4:         return 0x4B;
        case SDL_SCANCODE_KP_5:         return 0x4C;
        case SDL_SCANCODE_KP_6:         return 0x4D;
        case SDL_SCANCODE_KP_PLUS:      return 0x4E;
        case SDL_SCANCODE_KP_1:         return 0x4F;
        case SDL_SCANCODE_KP_2:         return 0x50;
        case SDL_SCANCODE_KP_3:         return 0x51;
        case SDL_SCANCODE_KP_0:         return 0x52;
        case SDL_SCANCODE_KP_PERIOD:    return 0x53;
        case SDL_SCANCODE_NONUSBACKSLASH: return 0x56;
        case SDL_SCANCODE_F11:          return 0x57;
        case SDL_SCANCODE_F12:          return 0x58;
        case SDL_SCANCODE_F13:          return 0x64;
        case SDL_SCANCODE_F14:          return 0x65;
        case SDL_SCANCODE_F15:          return 0x66;
        case SDL_SCANCODE_KP_ENTER:     return 0x9C;
        case SDL_SCANCODE_RCTRL:        return 0x9D;
        case SDL_SCANCODE_KP_DIVIDE:    return 0xB5;
        case SDL_SCANCODE_PRINTSCREEN:  return 0xB7;
        case SDL_SCANCODE_RALT:         return 0xB8;
        case SDL_SCANCODE_PAUSE:        return 0xC5;
        case SDL_SCANCODE_HOME:         return 0xC7;
        case SDL_SCANCODE_UP:           return 0xC8;
        case SDL_SCANCODE_PAGEUP:       return 0xC9;
        case SDL_SCANCODE_LEFT:         return 0xCB;
        case SDL_SCANCODE_RIGHT:        return 0xCD;
        case SDL_SCANCODE_END:          return 0xCF;
        case SDL_SCANCODE_DOWN:         return 0xD0;
        case SDL_SCANCODE_PAGEDOWN:     return 0xD1;
        case SDL_SCANCODE_INSERT:       return 0xD2;
        case SDL_SCANCODE_DELETE:       return 0xD3;
        case SDL_SCANCODE_LGUI:         return 0xDB;
        case SDL_SCANCODE_RGUI:         return 0xDC;
        case SDL_SCANCODE_APPLICATION:  return 0xDD;
        default:                        return 0;
    }
}

void process_sdl_event_for_dinput(const SDL_Event *e) {
    if (!e) return;

    if (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP) {
        uint8_t dik = sdl_scancode_to_dik(e->key.keysym.scancode);
        if (!dik) return;

        DWORD is_down = (e->type == SDL_KEYDOWN) ? 0x80 : 0x00;
        g_dik_state[dik] = (uint8_t)is_down;

        if (e->type == SDL_KEYUP || !e->key.repeat)
            q_push(&q_keyboard, dik, is_down, e->key.timestamp);   /* logical id; mapped to the app's offset on read */
    } else if (e->type == SDL_MOUSEMOTION) {
        if (e->motion.xrel != 0) q_push(&q_mouse, MID_X, (DWORD)e->motion.xrel, e->motion.timestamp);
        if (e->motion.yrel != 0) q_push(&q_mouse, MID_Y, (DWORD)e->motion.yrel, e->motion.timestamp);
    } else if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int btn_idx = -1;
        if (e->button.button == SDL_BUTTON_LEFT) btn_idx = 0;
        else if (e->button.button == SDL_BUTTON_RIGHT) btn_idx = 1;
        else if (e->button.button == SDL_BUTTON_MIDDLE) btn_idx = 2;
        else if (e->button.button == SDL_BUTTON_X1) btn_idx = 3;

        if (btn_idx >= 0) {
            DWORD is_down = (e->type == SDL_MOUSEBUTTONDOWN) ? 0x80 : 0x00;
            q_push(&q_mouse, MID_BTN0 + btn_idx, is_down, e->button.timestamp);
        }
    } else if (e->type == SDL_MOUSEWHEEL) {
        if (e->wheel.y != 0) q_push(&q_mouse, MID_Z, (DWORD)(e->wheel.y * 120), e->wheel.timestamp);
    }
}

/* ---- IDirectInput Methods ---- */
static int WINAPI di_QI(struct com *t,const void *iid,void **o){ t->ref++; *o=t; return DI_OK; }
static int WINAPI di_AddRef(struct com *t){ return ++t->ref; }
static int WINAPI di_Release(struct com *t){ return --t->ref; }

static int WINAPI di_EnumDevices(struct com *t, DWORD type, void *cb_ptr, void *ref, DWORD flags) {
    if (!cb_ptr) return DI_OK;
    DIENUMDEVICESCALLBACKA cb = (DIENUMDEVICESCALLBACKA)cb_ptr;

    static const struct { DWORD lt_type; const uint8_t *guid; const char *name; } d[] = {
        {3, GUID_SysKeyboard, "Keyboard"},
        {2, GUID_SysMouse,    "Mouse"}
    };

    uint8_t inst[DI5_DEVINSTANCE_SIZE];

    for (int i = 0; i < 2; i++) {
        if (type && type != d[i].lt_type) continue;

        memset(inst, 0, sizeof(inst));
        *(DWORD*)(inst + 0) = DI5_DEVINSTANCE_SIZE;
        memcpy(inst + 4, d[i].guid, 16);
        memcpy(inst + 20, d[i].guid, 16);
        *(DWORD*)(inst + 36) = d[i].lt_type | (1 << 8);
        snprintf((char*)(inst + 40), 260, "%s", d[i].name);
        snprintf((char*)(inst + 300), 260, "%s", d[i].name);

        int res = cb(inst, ref);
        if (!res) break;
    }
    return DI_OK;
}

static int WINAPI di_GetDeviceStatus(struct com *t,const void *g){ return DI_OK; }
static int WINAPI di_RunControlPanel(struct com *t,HWND h,DWORD f){ return DI_OK; }
static int WINAPI di_Initialize(struct com *t,HINSTANCE h,DWORD v){ return DI_OK; }
static int WINAPI di_CreateDeviceEx(struct com *t,const uint8_t *guid,const void *iid,void **out,void *outer);

static int WINAPI di_CreateDevice(struct com *t,const uint8_t *guid,void **out,void *outer){
  int kind=!memcmp(guid,GUID_SysKeyboard,16)?1:!memcmp(guid,GUID_SysMouse,16)?2:0;
  if(!kind){ *out=NULL; return DIERR_DEVICENOTREG; } *out=mk(dev_vtbl,kind); DBG("CreateDevice kind=%d", kind); return DI_OK;
}

static int WINAPI di_CreateDeviceEx(struct com *t,const uint8_t *guid,const void *iid,void **out,void *outer){ return di_CreateDevice(t,guid,out,outer); }

/* ---- IDirectInputDevice Methods ---- */
static int WINAPI dev_QI(struct com *t,const void *iid,void **o){ t->ref++; *o=t; return DI_OK; }
static int WINAPI dev_AddRef(struct com *t){ return ++t->ref; }
static int WINAPI dev_Release(struct com *t){ DBG("Release kind=%d ref->%d", t->kind, t->ref - 1); return --t->ref; }

static int WINAPI dev_GetCapabilities(struct com *t,DWORD *caps){
  DWORD sz=caps[0]; memset(caps,0,sz); caps[0]=sz; caps[1]=1; caps[2]=t->kind==1?3:2; caps[3]=t->kind==1?101:(t->kind==2?4:0); caps[4]=t->kind==1?0:3; caps[5]=t->kind==1?0:0;
  return DI_OK;
}

/* Real DirectInput-style key names (single characters for letters/digits/punctuation: the cshell special-cases
   1-char names). Only DIKs listed here exist on the "keyboard"; a real 101/104 key board enumerates ~100 objects,
   not 255 (the engine caps its per-device object table at 150 entries). */
static const char *table_key_name(unsigned dik) {
    static const char *n[256] = {
        [0x01]="Escape",[0x02]="1",[0x03]="2",[0x04]="3",[0x05]="4",[0x06]="5",[0x07]="6",[0x08]="7",[0x09]="8",[0x0A]="9",
        [0x0B]="0",[0x0C]="-",[0x0D]="=",[0x0E]="Backspace",[0x0F]="Tab",
        [0x10]="Q",[0x11]="W",[0x12]="E",[0x13]="R",[0x14]="T",[0x15]="Y",[0x16]="U",[0x17]="I",[0x18]="O",[0x19]="P",
        [0x1A]="[",[0x1B]="]",[0x1C]="Enter",[0x1D]="Left Control",
        [0x1E]="A",[0x1F]="S",[0x20]="D",[0x21]="F",[0x22]="G",[0x23]="H",[0x24]="J",[0x25]="K",[0x26]="L",
        [0x27]=";",[0x28]="'",[0x29]="`",[0x2A]="Left Shift",[0x2B]="\\",
        [0x2C]="Z",[0x2D]="X",[0x2E]="C",[0x2F]="V",[0x30]="B",[0x31]="N",[0x32]="M",[0x33]=",",[0x34]=".",[0x35]="/",
        [0x36]="Right Shift",[0x37]="Numpad *",[0x38]="Left Alt",[0x39]="Space",[0x3A]="Caps Lock",
        [0x3B]="F1",[0x3C]="F2",[0x3D]="F3",[0x3E]="F4",[0x3F]="F5",[0x40]="F6",[0x41]="F7",[0x42]="F8",[0x43]="F9",[0x44]="F10",
        [0x45]="Num Lock",[0x46]="Scroll Lock",
        [0x47]="Numpad 7",[0x48]="Numpad 8",[0x49]="Numpad 9",[0x4A]="Numpad -",
        [0x4B]="Numpad 4",[0x4C]="Numpad 5",[0x4D]="Numpad 6",[0x4E]="Numpad +",
        [0x4F]="Numpad 1",[0x50]="Numpad 2",[0x51]="Numpad 3",[0x52]="Numpad 0",[0x53]="Numpad .",
        [0x56]="OEM 102",[0x57]="F11",[0x58]="F12",[0x64]="F13",[0x65]="F14",[0x66]="F15",
        [0x9C]="Numpad Enter",[0x9D]="Right Control",[0xB5]="Numpad /",[0xB7]="Sys Rq",[0xB8]="Right Alt",
        [0xC5]="Pause",[0xC7]="Home",[0xC8]="Up Arrow",[0xC9]="Page Up",[0xCB]="Left Arrow",[0xCD]="Right Arrow",
        [0xCF]="End",[0xD0]="Down Arrow",[0xD1]="Page Down",[0xD2]="Insert",[0xD3]="Delete",
        [0xDB]="Left Windows",[0xDC]="Right Windows",[0xDD]="Apps"
    };
    return dik < 256 ? n[dik] : NULL;
}

/* Key names follow the ACTIVE keyboard layout, like real DirectInput (GetKeyNameText): on AZERTY the key at the
   QWERTY-Q position (DIK 0x10) is called "A".  SDL reports physical positions, so we ask SDL which character that
   position produces.  Names are computed once and then frozen for the whole run: the engine copies a name into a
   binding when it is created and later looks it up by that name, so it must never change. */
static char g_kn[256][24];
static int  g_kn_ready;

static void build_key_names(void) {
    if (g_kn_ready) return;
    g_kn_ready = 1;

    int have_layout = 1;
    if (!SDL_WasInit(SDL_INIT_VIDEO) && SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) have_layout = 0;  /* ref-counted */

    SDL_Scancode rev[256]; memset(rev, 0, sizeof rev);
    for (int sc = 1; sc < SDL_NUM_SCANCODES; sc++) {
        uint8_t d = sdl_scancode_to_dik((SDL_Scancode)sc);
        if (d && !rev[d]) rev[d] = (SDL_Scancode)sc;
    }

    for (unsigned d = 1; d < 256; d++) {
        const char *base = table_key_name(d);
        char tmp[24];
        if (!base) { snprintf(tmp, sizeof tmp, "Key %u", d); base = tmp; }   /* keeps index == DIK-1 */
        g_kn[d][0] = 0;
        snprintf(g_kn[d], sizeof g_kn[d], "%s", base);
        if (have_layout && rev[d] && table_key_name(d)) {
            SDL_Keycode kc = SDL_GetKeyFromScancode(rev[d]);
            if (kc >= 0x21 && kc <= 0x7E) { g_kn[d][0] = (char)toupper((int)kc); g_kn[d][1] = 0; }
        }
    }

    /* names must be unique */
    for (unsigned i = 1; i < 256; i++) {
        if (!g_kn[i][0]) continue;
        for (unsigned j = 1; j < i; j++) {
            if (g_kn[j][0] && !strcmp(g_kn[i], g_kn[j])) {
                const char *tb = table_key_name(i) ? table_key_name(i) : "Key";
                snprintf(g_kn[i], sizeof g_kn[i], "%s", tb);
                if (!strcmp(g_kn[i], g_kn[j])) snprintf(g_kn[i], sizeof g_kn[i], "%s #%02X", tb, i);
                break;
            }
        }
    }
    DBG("key names built (layout=%d): DIK 0x10='%s' 0x11='%s' 0x1E='%s' 0x2C='%s'",
        have_layout, g_kn[0x10], g_kn[0x11], g_kn[0x1E], g_kn[0x2C]);
}

static const char *get_key_name(unsigned dik) {
    build_key_names();
    return (dik < 256 && g_kn[dik][0]) ? g_kn[dik] : NULL;
}

static const char *const g_mouse_names[MOUSE_IDS] = { "X-axis","Y-axis","Z-axis","Button 0","Button 1","Button 2","Button 3" };

static void fill_key_instance(uint8_t *inst, unsigned k) {
    memset(inst, 0, DI5_OBJINSTANCE_SIZE);
    *(DWORD*)(inst + 0)  = DI5_OBJINSTANCE_SIZE;
    memcpy(inst + 4, GUID_Key, 16);
    *(DWORD*)(inst + 20) = k;                                   /* dwOfs: native keyboard offset == DIK */
    *(DWORD*)(inst + 24) = DIDFT_PSHBUTTON | DIDFT_MAKEINSTANCE(k); /* instance == DIK ("##<DIK>" bindings) */
    snprintf((char*)(inst + 32), 260, "%s", get_key_name(k));
}

static void fill_mouse_instance(uint8_t *inst, int i) {
    static const int ofs_map[MOUSE_IDS] = { 0, 4, 8, 12, 13, 14, 15 };
    const uint8_t *guids[MOUSE_IDS] = { GUID_XAxis, GUID_YAxis, GUID_ZAxis, GUID_Button, GUID_Button, GUID_Button, GUID_Button };
    memset(inst, 0, DI5_OBJINSTANCE_SIZE);
    *(DWORD*)(inst + 0)  = DI5_OBJINSTANCE_SIZE;
    memcpy(inst + 4, guids[i], 16);
    *(DWORD*)(inst + 20) = (DWORD)ofs_map[i];
    *(DWORD*)(inst + 24) = (i < 3 ? DIDFT_RELAXIS : DIDFT_PSHBUTTON) | DIDFT_MAKEINSTANCE(i);
    snprintf((char*)(inst + 32), 260, "%s", g_mouse_names[i]);
}

static int WINAPI dev_EnumObjects(struct com *t, void *cb_ptr, void *ref, DWORD flags) {
    if (!cb_ptr) return DI_OK;
    DIENUMDEVICEOBJECTSCALLBACKA cb = (DIENUMDEVICEOBJECTSCALLBACKA)cb_ptr;
    uint8_t inst[DI5_OBJINSTANCE_SIZE];

    if (t->kind == 1) {
        for (unsigned k = 1; k < 256; ++k) {
            fill_key_instance(inst, k);
            if (!cb(inst, ref)) break;
        }
    } else if (t->kind == 2) {
        for (int i = 0; i < MOUSE_IDS; ++i) {
            fill_mouse_instance(inst, i);
            if (!cb(inst, ref)) break;
        }
    }
    return DI_OK;
}

/* Device properties.  rguidProp is MAKEDIPROP(n): a small integer cast to a pointer.
   DIPROPHEADER = {dwSize, dwHeaderSize, dwObj, dwHow}; DIPROPDWORD adds dwData at +16, DIPROPRANGE adds lMin/lMax.
   LithTech's format rebuild (run on EVERY "bind") does:
       SetProperty(DIPROP_BUFFERSIZE, 0x40);  GetProperty(DIPROP_BUFFERSIZE);  if (dwData == 0) -> FAIL
   The old GetProperty always returned dwData = 0, so every bind failed with "Error binding device" and no binding
   was ever created: leaving Options always came back unassigned and nothing reached Player_0.txt. */
#define DIPROP_BUFFERSIZE_ID 1
#define DIPROP_RANGE_ID      4
static DWORD g_prop_buffersize[3];          /* per device kind (1=keyboard, 2=mouse) */

static int WINAPI dev_GetProperty(struct com *t, const void *g, DWORD *h) {
    uintptr_t id = (uintptr_t)g;
    if (!h || h[0] < 20) return DI_OK;
    if (id == DIPROP_BUFFERSIZE_ID) {
        h[4] = (t->kind >= 0 && t->kind < 3) ? g_prop_buffersize[t->kind] : 0;
        DBG("GetProperty(BUFFERSIZE) kind=%d -> %u", t->kind, h[4]);
    } else if (id == DIPROP_RANGE_ID && h[0] >= 24) {
        h[4] = 0;          /* lMin */
        h[5] = 65535;      /* lMax */
    } else {
        h[4] = 0;
    }
    return DI_OK;
}

static int WINAPI dev_SetProperty(struct com *t, const void *g, const void *hdr) {
    uintptr_t id = (uintptr_t)g;
    const DWORD *h = (const DWORD*)hdr;
    if (id == DIPROP_BUFFERSIZE_ID && h && h[0] >= 20 && t->kind >= 0 && t->kind < 3) {
        g_prop_buffersize[t->kind] = h[4];
        DBG("SetProperty(BUFFERSIZE) kind=%d = %u", t->kind, h[4]);
    }
    return DI_OK;
}

static int WINAPI dev_Acquire(struct com *t) {
    DBG("Acquire kind=%d", t->kind);
    t->acquired = 1;
    if (t->kind == 1) {
        q_flush(&q_keyboard);
    } else if (t->kind == 2) {
        q_flush(&q_mouse);
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    return DI_OK;
}

static int WINAPI dev_Unacquire(struct com *t) {
    DBG("Unacquire kind=%d", t->kind);
    t->acquired = 0;
    if (t->kind == 1) {
        memset(g_dik_state, 0, sizeof g_dik_state);
        q_flush(&q_keyboard);
    } else if (t->kind == 2) {
        q_flush(&q_mouse);
    }
    return DI_OK;
}

static int WINAPI dev_GetDeviceState(struct com *t, DWORD cb, void *data) {
    if (!data || cb == 0) return DI_OK;
    memset(data, 0, cb);

    pump_sdl_input_events();

    if (t->kind == 1) {
        for (int dik = 1; dik < 256; dik++) {
            DWORD o = kb_ofs[dik];
            if (g_dik_state[dik] && o != OFS_NONE && o < cb) ((uint8_t*)data)[o] = 0x80;
        }
    } else if (t->kind == 2) {
        int x = 0, y = 0;
        uint32_t bstate = SDL_GetRelativeMouseState(&x, &y);
        if (ms_ofs[MID_X] != OFS_NONE && ms_ofs[MID_X] + 4 <= cb) *(int32_t*)((char*)data + ms_ofs[MID_X]) = x;
        if (ms_ofs[MID_Y] != OFS_NONE && ms_ofs[MID_Y] + 4 <= cb) *(int32_t*)((char*)data + ms_ofs[MID_Y]) = y;
        static const uint32_t sdlbtn[4] = { SDL_BUTTON_LMASK, SDL_BUTTON_RMASK, SDL_BUTTON_MMASK, SDL_BUTTON_X1MASK };
        for (int b = 0; b < 4; b++) {
            DWORD o = ms_ofs[MID_BTN0 + b];
            if (o != OFS_NONE && o < cb && (bstate & sdlbtn[b])) ((uint8_t*)data)[o] = 0x80;
        }
    }
    return DI_OK;
}

static DWORD translate_id(const struct com *t, DWORD id) {
    if (t->kind == 1) return id < 256 ? kb_ofs[id] : OFS_NONE;
    return id < MOUSE_IDS ? ms_ofs[id] : OFS_NONE;
}

static int WINAPI dev_GetDeviceData(struct com *t, DWORD cbObjectBuffer, void *data, DWORD *n, DWORD f) {
    DWORD requested = n ? *n : 0;
    EventQueue *q = (t->kind == 1) ? &q_keyboard : ((t->kind == 2) ? &q_mouse : NULL);
    int peek = (f & DIGDD_PEEK) != 0;

    pump_sdl_input_events();

    if (!q) { if (n) *n = 0; return DI_OK; }

    /* Documented DirectInput semantics: rgdod == NULL means "discard up to *pdwInOut events"
       (0xFFFFFFFF = all) and report how many were discarded.  The engine uses this to flush stale events when it
       starts tracking; leaving them queued makes the Enter key-up / click that opened the dialog get bound. */
    if (!data) {
        DWORD take = requested < (DWORD)q->count ? requested : (DWORD)q->count;
        if (!peek) { q->head = (q->head + take) % QUEUE_SIZE; q->count -= take; }
        if (n) *n = take;
        return DI_OK;
    }

    if (requested == 0) return DI_OK;

    DWORD copied = 0;
    int examined = 0;
    char *out_ptr = (char*)data;
    DWORD stride = (cbObjectBuffer >= 16) ? cbObjectBuffer : 16;

    while (copied < requested && examined < q->count) {
        DIDEVICEOBJECTDATA_COMPAT *item = &q->items[(q->head + examined) % QUEUE_SIZE];
        examined++;

        DWORD ofs = translate_id(t, item->dwOfs);
        if (ofs == OFS_NONE) continue;           /* object not part of the app's data format: drop it */

        memset(out_ptr, 0, stride);
        *(DWORD*)(out_ptr + 0)  = ofs;
        *(DWORD*)(out_ptr + 4)  = item->dwData;
        *(DWORD*)(out_ptr + 8)  = item->dwTimeStamp;
        *(DWORD*)(out_ptr + 12) = item->dwSequence;
        DBG("event kind=%d id=%u -> ofs=%u (idx %u) data=0x%02X", t->kind, item->dwOfs, ofs, ofs >> 2, item->dwData);
        out_ptr += stride;
        copied++;
    }

    if (!peek) { q->head = (q->head + examined) % QUEUE_SIZE; q->count -= examined; }
    if (n) *n = copied;
    return DI_OK;
}

/* DIDATAFORMAT: {dwSize, dwObjSize, dwFlags, dwDataSize, dwNumObjs, rgodf*}   DIOBJECTDATAFORMAT: {pguid, dwOfs, dwType, dwFlags}
   LithTech passes entries with dwOfs = 4*index and dwType = the object's real type (instance in bits 8..23). */
static int WINAPI dev_SetDataFormat(struct com *t, const void *fmt) {
    if (!fmt) return DI_OK;

    uint32_t dwNumObjs = *(uint32_t*)((char*)fmt + 16);
    uint32_t rgodf_ptr = *(uint32_t*)((char*)fmt + 20);
    const char *rgodf = (const char*)(uintptr_t)rgodf_ptr;

    if (t->kind == 1) q_flush(&q_keyboard); else if (t->kind == 2) q_flush(&q_mouse);

    if (dwNumObjs == 0 || !rgodf) {                 /* placeholder format (engine sends one right after CreateDevice) */
        /* Reset ONLY this device. StartDeviceTrack opens the keyboard, sets its real format, then opens the
           mouse: resetting both tables here wiped the keyboard mapping back to identity (wrong keys). */
        if (t->kind == 1) kb_format_default(); else if (t->kind == 2) ms_format_default();
        DBG("SetDataFormat kind=%d placeholder (defaults)", t->kind);
        return DI_OK;
    }

    DBG("SetDataFormat kind=%d objs=%u", t->kind, dwNumObjs);
    if (t->kind == 1) {
        for (int i = 0; i < 256; i++) kb_ofs[i] = OFS_NONE;
        for (uint32_t i = 0; i < dwNumObjs; i++) {
            const char *obj = rgodf + i * 16;
            uint32_t ofs  = *(const uint32_t*)(obj + 4);
            uint32_t type = *(const uint32_t*)(obj + 8);
            uint32_t inst = (type >> 8) & 0xFFFF;
            uint32_t dik  = (inst == 0xFFFF) ? ofs : inst;   /* DIDFT_ANYINSTANCE (c_dfDIKeyboard): native ofs == DIK */
            if (dik < 256) kb_ofs[dik] = ofs;
        }
    } else if (t->kind == 2) {
        for (int i = 0; i < MOUSE_IDS; i++) ms_ofs[i] = OFS_NONE;
        for (uint32_t i = 0; i < dwNumObjs; i++) {
            const char *obj = rgodf + i * 16;
            uint32_t ofs  = *(const uint32_t*)(obj + 4);
            uint32_t type = *(const uint32_t*)(obj + 8);
            uint32_t inst = (type >> 8) & 0xFFFF;
            int id;
            if (inst == 0xFFFF) id = (ofs < 12) ? (int)(ofs / 4) : (int)(MID_BTN0 + (ofs - 12));  /* c_dfDIMouse */
            else id = (int)inst;
            if (id >= 0 && id < MOUSE_IDS) ms_ofs[id] = ofs;
        }
    }
    return DI_OK;
}

static int WINAPI dev_SetEventNotification(struct com *t,HANDLE h){ return DI_OK; }
static int WINAPI dev_SetCooperativeLevel(struct com *t, void *hwnd, DWORD flags) { return DI_OK; }

static int WINAPI dev_GetObjectInfo(struct com *t, DWORD *info, DWORD a, DWORD b) {
    if (!info) return DI_OK;
    uint8_t inst[DI5_OBJINSTANCE_SIZE];
    DWORD sz = info[0];
    if (sz == 0 || sz > DI5_OBJINSTANCE_SIZE) sz = DI5_OBJINSTANCE_SIZE;

    if (t->kind == 1) {
        unsigned dik = (b == DIPH_BYID) ? ((a >> 8) & 0xFFFF) : a;
        if (dik >= 256 || !get_key_name(dik)) return DIERR_NOTFOUND;
        fill_key_instance(inst, dik);
    } else {
        int id = -1;
        if (b == DIPH_BYID) id = (int)((a >> 8) & 0xFFFF);
        else if (a < 12)    id = (int)(a / 4);
        else                id = (int)(MID_BTN0 + (a - 12));
        if (id < 0 || id >= MOUSE_IDS) return DIERR_NOTFOUND;
        fill_mouse_instance(inst, id);
    }
    *(DWORD*)(inst + 0) = sz;
    memcpy(info, inst, sz);
    return DI_OK;
}

static int WINAPI dev_GetDeviceInfo(struct com *t, DWORD *i) {
    DWORD sz = i[0];
    memset(i, 0, sz);
    i[0] = sz;
    memcpy((char*)i + 4, t->kind == 1 ? GUID_SysKeyboard : GUID_SysMouse, 16);
    i[9] = (t->kind == 1 ? 3 : 2) | (1 << 8);
    snprintf((char*)i + 40, 260, "%s", t->kind == 1 ? "Keyboard" : "Mouse");
    snprintf((char*)i + 300, 260, "%s", t->kind == 1 ? "Keyboard" : "Mouse");
    return DI_OK;
}

static int WINAPI dev_RunControlPanel(struct com *t,HWND h,DWORD f){ return DI_OK; }
static int WINAPI dev_Initialize(struct com *t,HINSTANCE h,DWORD v,const void *g){ return DI_OK; }
static int WINAPI dev_unsup1(struct com *t,uint32_t a){ return 0x80004001; }
static int WINAPI dev_unsup2(struct com *t,uint32_t a,uint32_t b){ return 0x80004001; }
static int WINAPI dev_unsup3(struct com *t,uint32_t a,uint32_t b,uint32_t c){ return 0x80004001; }
static int WINAPI dev_unsup4(struct com *t,uint32_t a,uint32_t b,uint32_t c,uint32_t d){ return 0x80004001; }
static int WINAPI dev_Poll(struct com *t){ return DI_OK; }

static void init_tables(void){
  formats_default();
  void *d[]={di_QI,di_AddRef,di_Release,di_CreateDevice,di_EnumDevices,di_GetDeviceStatus,di_RunControlPanel,di_Initialize,di_CreateDeviceEx}; 
  memcpy(di_vtbl,d,sizeof d);
  void *v[]={dev_QI,dev_AddRef,dev_Release,dev_GetCapabilities,dev_EnumObjects,dev_GetProperty,dev_SetProperty,dev_Acquire,dev_Unacquire,dev_GetDeviceState,dev_GetDeviceData,dev_SetDataFormat,dev_SetEventNotification,dev_SetCooperativeLevel,dev_GetObjectInfo,dev_GetDeviceInfo,dev_RunControlPanel,dev_Initialize,
    dev_unsup4,dev_unsup3,dev_unsup2,dev_unsup1,dev_unsup1,dev_unsup3,dev_unsup1,dev_Poll,dev_unsup4}; 
  memcpy(dev_vtbl,v,sizeof v);
}

extern void lt_log(const char *fmt, ...);
HRESULT WINAPI W_DirectInputCreateA(HINSTANCE h,DWORD ver,void **out,void *outer){
  static int inited; if(!inited){ init_tables(); inited=1; lt_log("dinput.c build v4: + GetProperty(BUFFERSIZE) read-back (fixes failing 'bind')"); }
  *out=mk(di_vtbl,0); return DI_OK;
}
HRESULT WINAPI W_DirectInputCreateW(HINSTANCE h,DWORD ver,void **out,void *outer){ return W_DirectInputCreateA(h,ver,out,outer); }
HRESULT WINAPI W_DirectInputCreateEx(HINSTANCE h,DWORD ver,const void *iid,void **out,void *outer){ return W_DirectInputCreateA(h,ver,out,outer); }
HRESULT WINAPI W_DirectInput8Create(HINSTANCE h,DWORD ver,const void *riid,void **out,void *outer){ return W_DirectInputCreateA(h,ver,out,outer); }
