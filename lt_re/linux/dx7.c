/* DirectDraw 7 / Direct3D 7 compatibility layer (milestone 1: driver + display-mode enumeration + caps; everything else logs and fails safely). */
#include "win.h"
#include <stdarg.h>
extern void *dd_vtbl[],*sf_vtbl[],*d3_vtbl[],*dv_vtbl[];
void lt_dx_unimpl(const char *what){ static int n; if(n++<300) lt_log("DX unimplemented: %s",what); }
struct com { void **vtbl; int ref; int kind; };
static const uint8_t IID_DD1[16]={0x80,0xdb,0x14,0x6c,0x33,0xa7,0xce,0x11,0xa5,0x21,0x00,0x20,0xaf,0x0b,0xe5,0x60};
static const uint8_t IID_DD2[16]={0xe0,0xf3,0xa6,0xb3,0x43,0x2b,0xcf,0x11,0xa2,0xde,0x00,0xaa,0x00,0xb9,0x33,0x56};
static const uint8_t IID_DD4[16]={0x9a,0x50,0x59,0x9c,0xbd,0x39,0xd1,0x11,0x8c,0x4a,0x00,0xc0,0x4f,0xd9,0x30,0xc5};
static const uint8_t IID_DD7[16]={0xc0,0x5e,0xe6,0x15,0x9c,0x3b,0xd2,0x11,0xb9,0x2f,0x00,0x60,0x97,0x97,0xea,0x5b};
static const uint8_t IID_D3D7[16]={0x77,0x9e,0x04,0xf5,0x61,0x48,0xd2,0x11,0xa4,0x07,0x00,0xa0,0xc9,0x06,0x29,0xa8};
static const uint8_t IID_UNK[16]={0,0,0,0,0,0,0,0,0xc0,0,0,0,0,0,0,0x46};
static struct com *mk(void **v,int kind){ struct com *c=calloc(1,sizeof *c); c->vtbl=v; c->ref=1; c->kind=kind; return c; }
#define DDOK 0
#define E_NOINTERFACE_ 0x80004002u
/* ---- IDirectDraw family ---- */
int WINAPI dd_QueryInterface(struct com *t,const uint8_t *iid,void **out){
  if(!memcmp(iid,IID_DD1,16)||!memcmp(iid,IID_DD2,16)||!memcmp(iid,IID_DD4,16)||!memcmp(iid,IID_DD7,16)||!memcmp(iid,IID_UNK,16)){ t->ref++; *out=t; return DDOK; }
  if(!memcmp(iid,IID_D3D7,16)){ *out=mk(d3_vtbl,2); return DDOK; }
  *out=NULL; lt_log("DD QueryInterface: unsupported IID %02x%02x%02x%02x",iid[3],iid[2],iid[1],iid[0]); return E_NOINTERFACE_; }
int WINAPI dd_AddRef(struct com *t){ return ++t->ref; }
int WINAPI dd_Release(struct com *t){ return --t->ref; }
static const struct { int w,h; } modes[]={{640,480},{800,600},{1024,768},{1280,720},{1280,1024},{1600,1200}};
int WINAPI dd_EnumDisplayModes(struct com *t,DWORD flags,void *desc,void *ctx,int (WINAPI *cb)(uint32_t*,void*)){
  for(int bpp=16;bpp<=32;bpp+=16) for(unsigned i=0;i<sizeof modes/sizeof *modes;i++){
    uint32_t d[31]; memset(d,0,sizeof d); d[0]=124; d[1]=0x2|0x4|0x8|0x1000|0x40000; d[2]=modes[i].h; d[3]=modes[i].w; d[4]=modes[i].w*bpp/8; d[6]=60;
    d[18]=32; d[19]=0x40; d[21]=bpp; if(bpp==16){ d[22]=0xF800; d[23]=0x07E0; d[24]=0x001F; } else { d[22]=0xFF0000; d[23]=0xFF00; d[24]=0xFF; }
    if(!cb(d,ctx)) return DDOK; }
  return DDOK; }
int WINAPI dd_GetCaps(struct com *t,uint32_t *drv,uint32_t *hel){ uint32_t sz=drv?drv[0]:0; if(drv){ memset(drv,0,sz?sz:380); drv[0]=sz?sz:380; drv[1]=0x1|0x40|0x400000|0x2000000; drv[16]=64u<<20; drv[17]=48u<<20; } if(hel){ uint32_t s=hel[0]; memset(hel,0,s?s:380); hel[0]=s?s:380; } return DDOK; }
int WINAPI dd_SetCooperativeLevel(struct com *t,HWND h,DWORD f){ return DDOK; }
int WINAPI dd_RestoreDisplayMode(struct com *t){ return DDOK; }
int WINAPI dd_TestCooperativeLevel(struct com *t){ return DDOK; }
int WINAPI dd_GetDisplayMode(struct com *t,uint32_t *d){ memset(d,0,124); d[0]=124; d[2]=480; d[3]=640; d[18]=32; d[19]=0x40; d[21]=32; d[22]=0xFF0000; d[23]=0xFF00; d[24]=0xFF; return DDOK; }
int WINAPI dd_GetAvailableVidMem(struct com *t,uint32_t *caps,uint32_t *tot,uint32_t *fr){ if(tot)*tot=64u<<20; if(fr)*fr=48u<<20; return DDOK; }
/* ---- entry points exported by ddraw.dll ---- */
typedef int (WINAPI *ENUMCB)(void *guid,char *desc,char *name,void *ctx);
int WINAPI W_DirectDrawEnumerateA(ENUMCB cb,void *ctx){ if(cb) cb(NULL,"Primary Display Driver","display",ctx); return DDOK; }
int WINAPI W_DirectDrawCreate(void *guid,void **out,void *outer){ *out=mk(dd_vtbl,1); return DDOK; }
int WINAPI W_DirectDrawCreateEx(void *guid,void **out,const uint8_t *iid,void *outer){ *out=mk(dd_vtbl,1); return DDOK; }
typedef int (WINAPI *ENUMCBEX)(void *guid,char *desc,char *name,void *ctx,void *hmon);
int WINAPI W_DirectDrawEnumerateExA(ENUMCBEX cb,void *ctx,DWORD flags){ if(cb) cb(NULL,"Primary Display Driver","display",ctx,NULL); return DDOK; }

/* ======================= surfaces ======================= */
struct surf { void **vtbl; int ref; int kind;           /* kind 10 = surface */
  uint32_t desc[31]; uint32_t w,h,bpp,pitch; uint8_t *pix; int primary,back,zbuf,freed; struct surf *attached_back,*attached_z; struct com *dd; };
static int cur_w=640,cur_h=480,cur_bpp=32;
static struct surf *new_surf(struct com *dd,uint32_t w,uint32_t h,uint32_t bpp,const uint32_t *pf,uint32_t caps){
  struct surf *s=calloc(1,sizeof *s); s->vtbl=sf_vtbl; s->ref=1; s->kind=10; s->dd=dd; s->w=w; s->h=h; s->bpp=bpp?bpp:16; s->pitch=(w*s->bpp/8+3)&~3u;
  s->pix=calloc(1,(size_t)s->pitch*(h?h:1)+16);
  s->desc[0]=124; s->desc[1]=0x1|0x2|0x4|0x8|0x1000; s->desc[2]=h; s->desc[3]=w; s->desc[4]=s->pitch; s->desc[26]=caps;
  if(pf) memcpy(&s->desc[18],pf,32); else { s->desc[18]=32; s->desc[19]=0x40; s->desc[21]=s->bpp; if(s->bpp==16){ s->desc[22]=0xF800; s->desc[23]=0x07E0; s->desc[24]=0x001F; } else { s->desc[22]=0xFF0000; s->desc[23]=0xFF00; s->desc[24]=0xFF; } }
  return s; }
#define DDERR_NOTFOUND_ 0x887600FFu
int WINAPI dd_CreateSurface(struct com *dd,const uint32_t *d,struct surf **out,void *outer){
  uint32_t fl=d[1], caps=(fl&1)?d[26]:0; uint32_t w=(fl&4)?d[3]:cur_w, h=(fl&2)?d[2]:cur_h; const uint32_t *pf=(fl&0x1000)?&d[18]:NULL; uint32_t bpp=pf?pf[3]:cur_bpp;
  if(caps&0x200){ /* primary (+ optional complex flip chain) */
    struct surf *p=new_surf(dd,cur_w,cur_h,cur_bpp,NULL,caps); p->primary=1;
    if((fl&0x20)&&d[5]>0){ struct surf *prev=p; for(uint32_t k=0;k<d[5];k++){ struct surf *b=new_surf(dd,cur_w,cur_h,cur_bpp,NULL,0x4|0x8|0x10|0x2000); b->back=1; prev->attached_back=b; prev=b; } }
    lt_log("DD CreateSurface primary %ux%ux%u backbuffers=%u",cur_w,cur_h,cur_bpp,(fl&0x20)?d[5]:0); *out=p; return DDOK; }
  if(caps&0x20000){ /* z-buffer */ uint32_t zb=pf?pf[3]:16; struct surf *z=new_surf(dd,w,h,zb,pf,caps); z->zbuf=1; lt_log("DD CreateSurface zbuffer %ux%ux%u",w,h,zb); *out=z; return DDOK; }
  *out=new_surf(dd,w,h,bpp,pf,caps); if(!(caps&0x1000)||getenv("LT_TRACE")) lt_log("DD CreateSurface %ux%ux%u caps=%08x",w,h,bpp,caps); return DDOK; }
int WINAPI sf_QueryInterface(struct surf *t,const uint8_t *iid,void **o){ t->ref++; *o=t; return DDOK; }
int WINAPI sf_AddRef(struct surf *t){ return ++t->ref; }
static void surf_free_pix(struct surf *t){ if(t->pix){ free(t->pix); t->pix=NULL; } t->freed=1; }
int WINAPI sf_Release(struct surf *t){ if(t->freed) return 0; if(--t->ref>0) return t->ref; if(t->primary) for(struct surf *b=t->attached_back;b;b=b->attached_back) surf_free_pix(b); surf_free_pix(t); return 0; }
int WINAPI sf_GetAttachedSurface(struct surf *t,const uint32_t *caps,struct surf **o){ if((caps[0]&0x4)&&t->attached_back){ *o=t->attached_back; (*o)->ref++; return DDOK; } if((caps[0]&0x20000)&&t->attached_z){ *o=t->attached_z; (*o)->ref++; return DDOK; } *o=NULL; return DDERR_NOTFOUND_; }
int WINAPI sf_AddAttachedSurface(struct surf *t,struct surf *z){ if(z->zbuf) t->attached_z=z; return DDOK; }
int WINAPI sf_DeleteAttachedSurface(struct surf *t,DWORD f,struct surf *z){ if(t->attached_z==z) t->attached_z=NULL; return DDOK; }
int WINAPI sf_Lock(struct surf *t,const int32_t *rect,uint32_t *d,DWORD flags,HANDLE ev){ uint32_t sz=d[0]; memset(d,0,sz?sz:124); d[0]=124; d[1]=0x1|0x2|0x4|0x8|0x1000|0x400; d[2]=t->h; d[3]=t->w; d[4]=t->pitch; d[9]=(uint32_t)t->pix; memcpy(&d[18],&t->desc[18],32); if(rect) d[9]=(uint32_t)(t->pix+rect[1]*t->pitch+rect[0]*t->bpp/8); return DDOK; }
int WINAPI sf_Unlock(struct surf *t,const void *r){ return DDOK; }
int WINAPI sf_GetSurfaceDesc(struct surf *t,uint32_t *d){ memcpy(d,t->desc,124); d[9]=(uint32_t)t->pix; return DDOK; }
int WINAPI sf_GetPixelFormat(struct surf *t,uint32_t *pf){ memcpy(pf,&t->desc[18],32); return DDOK; }
int WINAPI sf_GetCaps(struct surf *t,uint32_t *caps){ caps[0]=t->desc[26]; caps[1]=caps[2]=caps[3]=0; return DDOK; }
int WINAPI sf_IsLost(struct surf *t){ return DDOK; }
int WINAPI sf_Restore(struct surf *t){ return DDOK; }
int WINAPI sf_SetColorKey(struct surf *t,DWORD f,void *k){ return DDOK; }
int WINAPI sf_GetBltStatus(struct surf *t,DWORD f){ return DDOK; }
int WINAPI sf_GetFlipStatus(struct surf *t,DWORD f){ return DDOK; }
int WINAPI sf_SetPalette(struct surf *t,void *p){ return DDOK; }
int WINAPI sf_Flip(struct surf *t,struct surf *o,DWORD f){ return DDOK; }
int WINAPI sf_SetClipper(struct surf *t,void *c){ return DDOK; }
int WINAPI sf_GetDDInterface(struct surf *t,void **o){ *o=t->dd; t->dd->ref++; return DDOK; }
static void rect_of(const int32_t *r,uint32_t w,uint32_t h,int *x0,int *y0,int *x1,int *y1){ if(r){ *x0=r[0]; *y0=r[1]; *x1=r[2]; *y1=r[3]; } else { *x0=0; *y0=0; *x1=w; *y1=h; } }
int WINAPI sf_Blt(struct surf *d,const int32_t *dr,struct surf *s,const int32_t *sr,DWORD flags,const uint32_t *fx){
  int dx0,dy0,dx1,dy1; rect_of(dr,d->w,d->h,&dx0,&dy0,&dx1,&dy1); if(dx0<0)dx0=0; if(dy0<0)dy0=0; if((uint32_t)dx1>d->w)dx1=d->w; if((uint32_t)dy1>d->h)dy1=d->h; uint32_t Bpp=d->bpp/8; if(!Bpp) return DDOK;
  if(flags&0x400){ uint32_t c=fx?fx[20]:0; for(int y=dy0;y<dy1;y++) for(int x=dx0;x<dx1;x++) memcpy(d->pix+y*d->pitch+x*Bpp,&c,Bpp>4?4:Bpp); return DDOK; }
  if(!s||s->bpp!=d->bpp) return DDOK; int sx0,sy0,sx1,sy1; rect_of(sr,s->w,s->h,&sx0,&sy0,&sx1,&sy1); int w=dx1-dx0<sx1-sx0?dx1-dx0:sx1-sx0, h=dy1-dy0<sy1-sy0?dy1-dy0:sy1-sy0;
  for(int y=0;y<h;y++) memcpy(d->pix+(dy0+y)*d->pitch+dx0*Bpp,s->pix+(sy0+y)*s->pitch+sx0*Bpp,(size_t)w*Bpp); return DDOK; }
int WINAPI sf_BltFast(struct surf *d,DWORD x,DWORD y,struct surf *s,const int32_t *sr,DWORD f){ int32_t dr[4]={x,y,x+(sr?sr[2]-sr[0]:s->w),y+(sr?sr[3]-sr[1]:s->h)}; return sf_Blt(d,dr,s,sr,0,NULL); }
/* ======================= DirectDraw display state ======================= */
int WINAPI dd_SetDisplayMode(struct com *t,DWORD w,DWORD h,DWORD bpp,DWORD rr,DWORD fl){ cur_w=w; cur_h=h; cur_bpp=bpp; lt_log("DD SetDisplayMode %ux%ux%u",w,h,bpp); return DDOK; }
/* ======================= Direct3D 7 ======================= */
static void fill_prim(uint32_t *p){ p[0]=56; p[1]=0x2|0x4|0x8; p[2]=0xFFFFFFFFu&~0x80000000u; p[3]=0xFF; p[4]=0x1FFF; p[5]=0x1FFF; p[6]=0xFF; p[7]=0x7; p[8]=0x7FFF; p[9]=0x3F0000|0x3F; p[10]=0x1FFF; p[11]=0x1F; }
static void fill_devdesc(uint32_t *d){ memset(d,0,256); d[0]=0x1|0x10|0x20|0x40|0x400|0x800|0x1000|0x2000|0x8000|0x10000; fill_prim(&d[1]); fill_prim(&d[15]);
  d[29]=0x1F; d[30]=0x1F00; d[31]=1; d[32]=1; d[33]=4096; d[34]=4096; d[35]=0x8000; d[36]=0x8000; d[37]=16;
  d[44]=0x1F; d[45]=0x7; d[46]=0x1|0x2|0x4|0x8|0x10|0x20|0x40|0x80|0x100|0x200|0x400|0x800|0x1000|0x2000|0x4000|0x8000|0x10000|0x20000|0x40000|0x80000; ((uint16_t*)d)[47*2]=8; ((uint16_t*)d)[47*2+1]=8; d[48]=8; ((float*)d)[49]=1e10f;
  static const uint8_t HAL[16]={0xe0,0x3d,0xe6,0x84,0xaa,0x46,0xcf,0x11,0x81,0x6f,0x00,0x00,0xc0,0x20,0x15,0x6e}; memcpy(&d[50],HAL,16); d[54]=0x1F; }
int WINAPI d3_EnumDevices(struct com *t,int (WINAPI *cb)(char *desc,char *name,uint32_t *d7,void *ctx),void *ctx){ uint32_t d[64]; fill_devdesc(d); cb("Direct3D HAL","Direct3D HAL",d,ctx); return DDOK; }
int WINAPI d3_CreateDevice(struct com *t,const uint8_t *iid,struct surf *rt,void **out){ struct com *c=calloc(1,sizeof *c); c->vtbl=dv_vtbl; c->ref=1; c->kind=3; *out=c; lt_log("D3D CreateDevice"); return DDOK; }
int WINAPI d3_QueryInterface(struct com *t,const uint8_t *iid,void **o){ t->ref++; *o=t; return DDOK; }
int WINAPI d3_AddRef(struct com *t){ return ++t->ref; } int WINAPI d3_Release(struct com *t){ return --t->ref; }
int WINAPI d3_EnumZBufferFormats(struct com *t,const uint8_t *iid,int (WINAPI *cb)(uint32_t *pf,void *ctx),void *ctx){ uint32_t pf[8]; memset(pf,0,32); pf[0]=32; pf[1]=0x400; pf[3]=16; pf[5]=0xFFFF; if(!cb(pf,ctx)) return DDOK; pf[3]=24; pf[5]=0xFFFFFF; if(!cb(pf,ctx)) return DDOK; pf[3]=32; pf[5]=0xFFFFFF; pf[1]=0x400|0x4000; pf[6]=0xFF000000u; cb(pf,ctx); return DDOK; }
int WINAPI d3_EvictManagedTextures(struct com *t){ return DDOK; }
int WINAPI dv_QueryInterface(struct com *t,const uint8_t *iid,void **o){ t->ref++; *o=t; return DDOK; }
int WINAPI dv_AddRef(struct com *t){ return ++t->ref; } int WINAPI dv_Release(struct com *t){ return --t->ref; }
int WINAPI dv_GetCaps(struct com *t,uint32_t *d){ fill_devdesc(d); return DDOK; }
int WINAPI dv_EnumTextureFormats(struct com *t,int (WINAPI *cb)(uint32_t *pf,void *ctx),void *ctx){
  uint32_t f[4][8]={{32,0x40,0,16,0xF800,0x07E0,0x001F,0},{32,0x41,0,16,0x0F00,0x00F0,0x000F,0xF000},{32,0x41,0,16,0x7C00,0x03E0,0x001F,0x8000},{32,0x41,0,32,0xFF0000,0xFF00,0xFF,0xFF000000u}};
  for(int i=0;i<4;i++) if(!cb(f[i],ctx)) break; return DDOK; }
int WINAPI dv_BeginScene(struct com *t){ return DDOK; } int WINAPI dv_EndScene(struct com *t){ return DDOK; }
int WINAPI dv_GetDirect3D(struct com *t,void **o){ *o=t; return DDOK; }
int WINAPI dv_SetRenderTarget(struct com *t,void *s,DWORD f){ return DDOK; }
int WINAPI dv_Clear(struct com *t,DWORD n,void *r,DWORD fl,DWORD c,float z,DWORD st){ return DDOK; }
int WINAPI dv_SetTransform(struct com *t,DWORD s,const void *m){ return DDOK; }
int WINAPI dv_SetViewport(struct com *t,const void *vp){ return DDOK; }
int WINAPI dv_SetMaterial(struct com *t,const void *m){ return DDOK; }
int WINAPI dv_SetLight(struct com *t,DWORD i,const void *l){ return DDOK; }
int WINAPI dv_LightEnable(struct com *t,DWORD i,BOOL e){ return DDOK; }
int WINAPI dv_SetRenderState(struct com *t,DWORD s,DWORD v){ return DDOK; }
int WINAPI dv_GetRenderState(struct com *t,DWORD s,DWORD *v){ *v=0; return DDOK; }
int WINAPI dv_SetTexture(struct com *t,DWORD stage,void *tex){ return DDOK; }
int WINAPI dv_SetTextureStageState(struct com *t,DWORD stage,DWORD type,DWORD v){ return DDOK; }
int WINAPI dv_GetTextureStageState(struct com *t,DWORD stage,DWORD type,DWORD *v){ *v=0; return DDOK; }
int WINAPI dv_ValidateDevice(struct com *t,DWORD *passes){ if(passes)*passes=1; return DDOK; }
int WINAPI dv_DrawPrimitive(struct com *t,DWORD type,DWORD fvf,void *v,DWORD n,DWORD f){ return DDOK; }
int WINAPI dv_DrawIndexedPrimitive(struct com *t,DWORD type,DWORD fvf,void *v,DWORD n,uint16_t *idx,DWORD ni,DWORD f){ return DDOK; }
int WINAPI dv_PreLoad(struct com *t,void *tex){ return DDOK; }
int WINAPI dv_SetClipStatus(struct com *t,const void *s){ return DDOK; }
int WINAPI dv_MultiplyTransform(struct com *t,DWORD s,const void *m){ return DDOK; }
int WINAPI dv_GetViewport(struct com *t,void *vp){ return DDOK; }
int WINAPI dv_GetRenderTarget(struct com *t,void **s){ *s=NULL; return 0x80004005; }
int WINAPI sf_EnumAttachedSurfaces(struct surf *t,void *ctx,int (WINAPI *cb)(struct surf *s,uint32_t *desc,void *ctx)){
  if(t->attached_back){ t->attached_back->ref++; uint32_t d[31]; memcpy(d,t->attached_back->desc,124); d[9]=(uint32_t)t->attached_back->pix; if(!cb(t->attached_back,d,ctx)) return DDOK; }
  if(t->attached_z){ t->attached_z->ref++; uint32_t d[31]; memcpy(d,t->attached_z->desc,124); d[9]=(uint32_t)t->attached_z->pix; cb(t->attached_z,d,ctx); }
  return DDOK; }
/* ======================= vertex buffers ======================= */
struct vb { void **vtbl; int ref; int kind; uint32_t fvf,count,stride; uint8_t *data; };
static void *vb_vtbl[9];
static uint32_t fvf_stride(uint32_t f){ uint32_t s=0; if(f&0x2) s+=12; if(f&0x4) s+=16; uint32_t nb=(f>>1)&7; (void)nb; if((f&0xE)==0x6||(f&0xE)==0x8||(f&0xE)==0xA||(f&0xE)==0xC||(f&0xE)==0xE) s+=12+4*(((f&0xE)-4)/2); if(f&0x10) s+=12; if(f&0x20) s+=4; if(f&0x40) s+=4; if(f&0x80) s+=4; s+=8*((f>>8)&0xF); return s?s:32; }
int WINAPI vb_QI(struct vb *t,const void *iid,void **o){ t->ref++; *o=t; return DDOK; }
int WINAPI vb_AddRef(struct vb *t){ return ++t->ref; } int WINAPI vb_Release(struct vb *t){ if(t->ref<=0) return 0; if(--t->ref==0){ free(t->data); t->data=NULL; } return t->ref; }
int WINAPI vb_Lock(struct vb *t,DWORD fl,void **d,DWORD *sz){ *d=t->data; if(sz)*sz=t->count*t->stride; return DDOK; }
int WINAPI vb_Unlock(struct vb *t){ return DDOK; }
int WINAPI vb_ProcessVertices(struct vb *t,DWORD op,DWORD di,DWORD n,void *src,DWORD si,void *dev,DWORD fl){ return DDOK; }
int WINAPI vb_GetVertexBufferDesc(struct vb *t,uint32_t *d){ d[0]=16; d[1]=0; d[2]=t->fvf; d[3]=t->count; return DDOK; }
int WINAPI vb_Optimize(struct vb *t,void *dev,DWORD fl){ return DDOK; }
int WINAPI d3_CreateVertexBuffer(struct com *t,const uint32_t *d,void **out,DWORD fl){
  struct vb *v=calloc(1,sizeof *v); void *tab[]={vb_QI,vb_AddRef,vb_Release,vb_Lock,vb_Unlock,vb_ProcessVertices,vb_GetVertexBufferDesc,vb_Optimize,vb_ProcessVertices}; memcpy(vb_vtbl,tab,sizeof tab);
  v->vtbl=vb_vtbl; v->ref=1; v->kind=4; v->fvf=d[2]; v->count=d[3]; v->stride=fvf_stride(d[2]); v->data=calloc(1,(size_t)v->count*v->stride+16); *out=v; return DDOK; }
int WINAPI dv_DrawPrimitiveVB(struct com *t,DWORD type,void *vb,DWORD start,DWORD n,DWORD f){ return DDOK; }
int WINAPI dv_DrawIndexedPrimitiveVB(struct com *t,DWORD type,void *vb,DWORD start,DWORD n,uint16_t *idx,DWORD ni,DWORD f){ return DDOK; }
int WINAPI sf_SetPriority(struct surf *t,DWORD p){ return DDOK; }
int WINAPI sf_GetPriority(struct surf *t,DWORD *p){ if(p)*p=0; return DDOK; }
