/* DirectInput (v3..v7, ANSI) compatibility layer: keyboard + mouse devices that currently report no input.
   Hook an SDL2/evdev backend into dev_GetDeviceState / dev_GetDeviceData. */
#include "win.h"
struct com { void **vtbl; int ref; int kind; };
static const uint8_t GUID_SysMouse[16]={0x60,0x2b,0x1d,0x6f,0xa0,0xd5,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00};
static const uint8_t GUID_SysKeyboard[16]={0x61,0x2b,0x1d,0x6f,0xa0,0xd5,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00};
#define DI_OK 0
#define DIERR_NOTFOUND 0x80070002u
#define DIERR_DEVICENOTREG 0x80040154u
static void *di_vtbl[10], *dev_vtbl[27];
static struct com *mk(void **v,int k){ struct com *c=calloc(1,sizeof *c); c->vtbl=v; c->ref=1; c->kind=k; return c; }
/* ---- IDirectInput ---- */
static int WINAPI di_QI(struct com *t,const void *iid,void **o){ t->ref++; *o=t; return DI_OK; }
static int WINAPI di_AddRef(struct com *t){ return ++t->ref; }
static int WINAPI di_Release(struct com *t){ return --t->ref; }
static int WINAPI di_CreateDevice(struct com *t,const uint8_t *guid,void **out,void *outer){
  int kind=!memcmp(guid,GUID_SysKeyboard,16)?1:!memcmp(guid,GUID_SysMouse,16)?2:0;
  if(!kind){ *out=NULL; return DIERR_DEVICENOTREG; } *out=mk(dev_vtbl,kind); return DI_OK; }
static int WINAPI di_EnumDevices(struct com *t,DWORD type,int (WINAPI *cb)(void *inst,void *ref),void *ref,DWORD flags){
  static const struct { DWORD type; const uint8_t *guid; const char *name; } d[]={{3,GUID_SysKeyboard,"Keyboard"},{2,GUID_SysMouse,"Mouse"}};
  for(int i=0;i<2;i++){ if(type&&type!=d[i].type&&type!=0) continue; uint8_t inst[0x244]; memset(inst,0,sizeof inst); *(DWORD*)inst=0x244; memcpy(inst+4,d[i].guid,16); memcpy(inst+20,d[i].guid,16); *(DWORD*)(inst+36)=d[i].type|(1<<8); snprintf((char*)inst+40,260,"%s",d[i].name); snprintf((char*)inst+300,260,"%s",d[i].name); if(!cb(inst,ref)) break; }
  return DI_OK; }
static int WINAPI di_GetDeviceStatus(struct com *t,const void *g){ return DI_OK; }
static int WINAPI di_RunControlPanel(struct com *t,HWND h,DWORD f){ return DI_OK; }
static int WINAPI di_Initialize(struct com *t,HINSTANCE h,DWORD v){ return DI_OK; }
static int WINAPI di_CreateDeviceEx(struct com *t,const uint8_t *guid,const void *iid,void **out,void *outer){ return di_CreateDevice(t,guid,out,outer); }
/* ---- IDirectInputDevice(2) ---- */
static int WINAPI dev_QI(struct com *t,const void *iid,void **o){ t->ref++; *o=t; return DI_OK; }
static int WINAPI dev_AddRef(struct com *t){ return ++t->ref; }
static int WINAPI dev_Release(struct com *t){ return --t->ref; }
static int WINAPI dev_GetCapabilities(struct com *t,DWORD *caps){ DWORD sz=caps[0]; memset(caps,0,sz); caps[0]=sz; caps[1]=1; caps[2]=t->kind==1?3:2; caps[3]=t->kind==1?101:(t->kind==2?3:0); caps[4]=t->kind==1?0:3; caps[5]=t->kind==1?0:0; return DI_OK; }
static int WINAPI dev_EnumObjects(struct com *t,void *cb,void *ref,DWORD f){ return DI_OK; }
static int WINAPI dev_GetProperty(struct com *t,const void *g,DWORD *h){ if(h&&h[0]>=20) h[4]=0; return DI_OK; }
static int WINAPI dev_SetProperty(struct com *t,const void *g,const void *h){ return DI_OK; }
static int WINAPI dev_Acquire(struct com *t){ return DI_OK; }
static int WINAPI dev_Unacquire(struct com *t){ return DI_OK; }
static int WINAPI dev_GetDeviceState(struct com *t,DWORD cb,void *data){ memset(data,0,cb); return DI_OK; }
static int WINAPI dev_GetDeviceData(struct com *t,DWORD cb,void *data,DWORD *n,DWORD f){ if(n)*n=0; return DI_OK; }
static int WINAPI dev_SetDataFormat(struct com *t,const void *fmt){ return DI_OK; }
static int WINAPI dev_SetEventNotification(struct com *t,HANDLE h){ return DI_OK; }
static int WINAPI dev_SetCooperativeLevel(struct com *t,HWND h,DWORD f){ return DI_OK; }
static int WINAPI dev_GetObjectInfo(struct com *t,void *o,DWORD a,DWORD b){ return DIERR_NOTFOUND; }
static int WINAPI dev_GetDeviceInfo(struct com *t,DWORD *i){ DWORD sz=i[0]; memset(i,0,sz); i[0]=sz; memcpy((char*)i+4,t->kind==1?GUID_SysKeyboard:GUID_SysMouse,16); i[9]=(t->kind==1?3:2)|(1<<8); return DI_OK; }
static int WINAPI dev_RunControlPanel(struct com *t,HWND h,DWORD f){ return DI_OK; }
static int WINAPI dev_Initialize(struct com *t,HINSTANCE h,DWORD v,const void *g){ return DI_OK; }
static int WINAPI dev_unsup1(struct com *t,uint32_t a){ return 0x80004001; }
static int WINAPI dev_unsup2(struct com *t,uint32_t a,uint32_t b){ return 0x80004001; }
static int WINAPI dev_unsup3(struct com *t,uint32_t a,uint32_t b,uint32_t c){ return 0x80004001; }
static int WINAPI dev_unsup4(struct com *t,uint32_t a,uint32_t b,uint32_t c,uint32_t d){ return 0x80004001; }
static int WINAPI dev_Poll(struct com *t){ return DI_OK; }
static void init_tables(void){
  void *d[]={di_QI,di_AddRef,di_Release,di_CreateDevice,di_EnumDevices,di_GetDeviceStatus,di_RunControlPanel,di_Initialize,di_CreateDeviceEx}; memcpy(di_vtbl,d,sizeof d);
  void *v[]={dev_QI,dev_AddRef,dev_Release,dev_GetCapabilities,dev_EnumObjects,dev_GetProperty,dev_SetProperty,dev_Acquire,dev_Unacquire,dev_GetDeviceState,dev_GetDeviceData,dev_SetDataFormat,dev_SetEventNotification,dev_SetCooperativeLevel,dev_GetObjectInfo,dev_GetDeviceInfo,dev_RunControlPanel,dev_Initialize,
    /*CreateEffect*/dev_unsup4,/*EnumEffects*/dev_unsup3,/*GetEffectInfo*/dev_unsup2,/*GetForceFeedbackState*/dev_unsup1,/*SendForceFeedbackCommand*/dev_unsup1,/*EnumCreatedEffectObjects*/dev_unsup3,/*Escape*/dev_unsup1,/*Poll*/dev_Poll,/*SendDeviceData*/dev_unsup4}; memcpy(dev_vtbl,v,sizeof v); }
HRESULT WINAPI W_DirectInputCreateA(HINSTANCE h,DWORD ver,void **out,void *outer){ static int inited; if(!inited){ init_tables(); inited=1; } *out=mk(di_vtbl,0); return DI_OK; }
HRESULT WINAPI W_DirectInputCreateEx(HINSTANCE h,DWORD ver,const void *iid,void **out,void *outer){ return W_DirectInputCreateA(h,ver,out,outer); }
