/* PE resources + PE loader + import resolution (LoadLibrary/GetProcAddress/FindResource...) */
#include "win.h"
#include <dlfcn.h>
#include <limits.h>
#include "layout.h"
#include <strings.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
struct exp { const char *name; void *fn; }; extern struct exp lt_exports[]; extern int lt_exports_n;
struct ar { const char *name; int n; };     extern struct ar lt_arity[]; extern int lt_arity_n;
#define MAIN_BASE 0x400000u
#define MAIN_RSRC_RVA (LT_RSRC_VA-0x400000)
typedef struct { uint32_t Char,Time; uint16_t Maj,Min,NNamed,NId; } RDIR; typedef struct { uint32_t Name,Off; } RENT; typedef struct { uint32_t Rva,Size,CP,Res; } RDATA;
/* ---------- stubs for unimplemented imports ---------- */
void lt_unimpl(const char *what){ static int n; if(n++<200) lt_log("unimplemented import: %s",what); }
static int arity_of(const char *name){
  char b[256]; snprintf(b,sizeof b,"%s",name); char *at=strrchr(b,'@'); if(at&&isdigit((unsigned char)at[1])){ int n=atoi(at+1); return n; }
  const char *s=b[0]=='_'?b+1:b; int lo=0,hi=lt_arity_n-1; while(lo<=hi){ int m=(lo+hi)/2; int c=strcmp(lt_arity[m].name,s); if(!c) return lt_arity[m].n; if(c<0) lo=m+1; else hi=m-1; }
  return -1; }
static void *make_stub(const char *dll,const char *name){
  static unsigned char *page; static size_t used=4096; if(used+40>4096){ page=mmap(0,4096,7,MAP_PRIVATE|MAP_ANONYMOUS,-1,0); used=0; }
  unsigned char *p=page+used; used+=40; int n=arity_of(name); if(n<0) n=0;
  char *label=malloc(300); snprintf(label,300,"%s!%s",dll,name);
  int hres=!strncasecmp(dll,"dd",2)||!strncasecmp(dll,"d3d",3)||!strncasecmp(dll,"dinput",6)||!strncasecmp(dll,"dsound",6)||!strncasecmp(dll,"dmusic",6)||!strncasecmp(dll,"ole32",5);
  unsigned i=0; p[i++]=0x68; *(uint32_t*)(p+i)=(uint32_t)label; i+=4;                               /* push label   */
  p[i++]=0xE8; *(int32_t*)(p+i)=(int32_t)((unsigned char*)lt_unimpl-(p+i+4)); i+=4;                 /* call lt_unimpl */
  p[i++]=0x83; p[i++]=0xC4; p[i++]=0x04;                                                              /* add esp,4    */
  p[i++]=0xB8; *(uint32_t*)(p+i)=hres?0x80004005u:0; i+=4;                                             /* mov eax, ... */
  p[i++]=0xC2; *(uint16_t*)(p+i)=n; i+=2; return p; }
/* ---------- module list ---------- */
struct mod { void *elf; char name[128]; char wpath[700]; uint8_t *base; uint32_t size; int shim; int refs; uint32_t exp_rva,exp_size,rsrc_rva; };
static struct mod mods[128]; static int nmods; static pthread_mutex_t mmx=PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
static const char *shim_names[]={"kernel32.dll","user32.dll","gdi32.dll","advapi32.dll","winmm.dll","ole32.dll","wsock32.dll","ws2_32.dll","mss32.dll","dinput.dll","ntdll.dll","msvcrt.dll","shell32.dll","comctl32.dll","version.dll","oleaut32.dll","dsound.dll","ddraw.dll","dxguid.dll","d3d9.dll","dplayx.dll","imm32.dll","dwmapi.dll","opengl32.dll","glu32.dll",0};
static void lower_base(const char *p,char *o,size_t n){ const char *b=p; for(const char *q=p;*q;q++) if(*q=='\\'||*q=='/') b=q+1; size_t i=0; for(;*b&&i<n-1;b++) o[i++]=tolower((unsigned char)*b); o[i]=0; }
static int is_shim(const char *low){ for(int i=0;shim_names[i];i++){ if(!strcmp(low,shim_names[i])) return 1; char t[128]; snprintf(t,sizeof t,"%s",shim_names[i]); char *d=strrchr(t,'.'); if(d){ *d=0; if(!strcmp(low,t)) return 1; } } return 0; }
static const char *ord_names_ws[]={0,"accept","bind","closesocket","connect","getpeername","getsockname","getsockopt","htonl","htons","ioctlsocket","inet_addr","inet_ntoa","listen","ntohl","ntohs","recv","recvfrom","select","send","sendto","setsockopt","shutdown","socket"};
static void *export_lookup(const char *name){ for(int i=0;i<lt_exports_n;i++) if(!strcmp(lt_exports[i].name,name)) return lt_exports[i].fn; return NULL; }
static struct mod *find_mod(const char *low){ for(int i=0;i<nmods;i++) if(!strcmp(mods[i].name,low)) return &mods[i]; return NULL; }
static void *pe_export(struct mod *m,const char *name,unsigned ord){
  if(!m->exp_rva) return NULL; uint8_t *b=m->base; uint32_t *d=(uint32_t*)(b+m->exp_rva);
  uint32_t nf=d[5], nn=d[6]; uint32_t *fn=(uint32_t*)(b+d[7]), *nm=(uint32_t*)(b+d[8]); uint16_t *on=(uint16_t*)(b+d[9]); uint32_t obase=d[4];
  uint32_t rva=0;
  if(name){ for(uint32_t i=0;i<nn;i++) if(!strcmp((char*)(b+nm[i]),name)){ rva=fn[on[i]]; break; } }
  else if(ord>=obase&&ord-obase<nf) rva=fn[ord-obase];
  if(!rva) return NULL; if(rva>=m->exp_rva&&rva<m->exp_rva+m->exp_size) return NULL; /* forwarder: unsupported */ return b+rva; }
static struct mod *load_pe(const char *low,const char *unixpath);
static void lt_trace_call(const char *n){ fprintf(stderr,"[call] %s\n",n); }
static void *trace_wrap(const char *name,void *f){
  static int on=-1; if(on<0) on=getenv("LT_TRACE_CALLS")!=NULL; if(!on||!f) return f;
  static unsigned char *page; static size_t used=4096; if(used+24>4096){ page=mmap(0,4096,7,MAP_PRIVATE|MAP_ANONYMOUS,-1,0); used=0; }
  unsigned char *p=page+used; used+=24; unsigned i=0; char *nm=strdup(name);
  p[i++]=0x68; *(uint32_t*)(p+i)=(uint32_t)nm; i+=4; p[i++]=0xE8; *(int32_t*)(p+i)=(int32_t)((unsigned char*)lt_trace_call-(p+i+4)); i+=4; p[i++]=0x83; p[i++]=0xC4; p[i++]=0x04;
  p[i++]=0xE9; *(int32_t*)(p+i)=(int32_t)((unsigned char*)f-(p+i+4)); i+=4; return p; }
static void *resolve_inner(const char *dll,const char *name,unsigned ord);
void *lt_resolve_import(const char *dll,const char *name,unsigned ord){ void *f=resolve_inner(dll,name,ord); return trace_wrap(name?name:"ordinal",f); }
static void *resolve_inner(const char *dll,const char *name,unsigned ord){
  char low[128]; lower_base(dll,low,sizeof low);
  if(!is_shim(low)){ struct mod *m=find_mod(low); if(!m){ char p[1024]; extern HMODULE WINAPI W_LoadLibraryA(LPCSTR); W_LoadLibraryA(dll); m=find_mod(low); } if(m&&!m->shim){ void *f=pe_export(m,name,ord); if(f) return f; } }
  char nb[256];
  if(!name){ if(!strncmp(low,"wsock32",7)&&ord<24&&ord_names_ws[ord]) name=ord_names_ws[ord]; else if(!strncmp(low,"wsock32",7)){ switch(ord){ case 52: name="gethostbyname"; break; case 111: name="WSAGetLastError"; break; case 115: name="WSAStartup"; break; case 116: name="WSACleanup"; break; case 57: name="gethostname"; break; } } }
  if(!name){ snprintf(nb,sizeof nb,"Ordinal_%u",ord); name=nb; }
  const char *s=name; char bare[256]; snprintf(bare,sizeof bare,"%s",s); char *at=strrchr(bare,'@'); if(at&&isdigit((unsigned char)at[1])) *at=0; const char *bn=bare[0]=='_'?bare+1:bare;
  if(!strncasecmp(low,"opengl32",8)&&name[0]=='g'&&name[1]=='l'){ extern void *lt_gl_thunk(const char*); void *t=lt_gl_thunk(name); if(t) return t; }
  void *f=export_lookup(name); if(!f) f=export_lookup(bare); if(!f) f=export_lookup(bn); if(f) return f;
  return make_stub(low,name); }
/* ---------- loader ---------- */
static struct mod *load_pe(const char *low,const char *path){
  int fd=open(path,O_RDONLY); if(fd<0){ if(getenv("LT_TRACE")) lt_log("load_pe: open('%s') failed: %s",path,strerror(errno)); return NULL; } struct stat st; fstat(fd,&st); uint8_t *file=malloc(st.st_size); if(read(fd,file,st.st_size)!=st.st_size){ close(fd); free(file); return NULL; } close(fd);
  if(file[0]!='M'||file[1]!='Z'){ free(file); return NULL; } uint32_t pe=*(uint32_t*)(file+0x3c); uint8_t *nt=file+pe; if(memcmp(nt,"PE\0\0",4)){ free(file); return NULL; }
  uint16_t nsec=*(uint16_t*)(nt+6), optsz=*(uint16_t*)(nt+20); uint8_t *opt=nt+24; uint32_t entry=*(uint32_t*)(opt+16), ibase=*(uint32_t*)(opt+28), isz=*(uint32_t*)(opt+56), hsz=*(uint32_t*)(opt+60);
  uint32_t *dd=(uint32_t*)(opt+96); uint8_t *sec=opt+optsz;
  uint8_t *base=mmap((void*)ibase,isz,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED_NOREPLACE,-1,0);
  if(base==MAP_FAILED) base=mmap(0,isz,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
  if(base==MAP_FAILED){ free(file); return NULL; }
  if(getenv("LT_TRACE")) lt_log("  loaded %s at %p size=0x%x (preferred 0x%x)",low,base,isz,ibase);
  memcpy(base,file,hsz<st.st_size?hsz:st.st_size);
  for(int i=0;i<nsec;i++){ uint8_t *s=sec+i*40; uint32_t va=*(uint32_t*)(s+12), rs=*(uint32_t*)(s+16), ro=*(uint32_t*)(s+20); if(ro&&rs) memcpy(base+va,file+ro,rs); }
  int32_t delta=(int32_t)((uint32_t)base-ibase);
  if(delta&&dd[10]){ uint8_t *r=base+dd[10], *e=r+dd[11]; while(r<e){ uint32_t pg=*(uint32_t*)r, bs=*(uint32_t*)(r+4); for(uint32_t k=8;k<bs;k+=2){ uint16_t w=*(uint16_t*)(r+k); if((w>>12)==3) *(uint32_t*)(base+pg+(w&0xfff))+=delta; } r+=bs; } }
  struct mod *m=&mods[nmods++]; memset(m,0,sizeof *m); snprintf(m->name,sizeof m->name,"%s",low); { char rp[4112]; if(!realpath(path,rp)) snprintf(rp,sizeof rp,"%s",path); snprintf(m->wpath,sizeof m->wpath,"Z:%s",rp); for(char*q=m->wpath;*q;q++) if(*q=='/') *q='\\'; } m->base=base; m->size=isz; m->refs=1; m->exp_rva=dd[0]; m->exp_size=dd[1]; m->rsrc_rva=dd[4];
  if(dd[2]){ uint32_t *imp=(uint32_t*)(base+dd[2]); for(;imp[3];imp+=5){ const char *dn=(char*)(base+imp[3]); uint32_t *ot=(uint32_t*)(base+(imp[0]?imp[0]:imp[4])), *at=(uint32_t*)(base+imp[4]);
      for(;*ot;ot++,at++){ if(*ot&0x80000000u) *at=(uint32_t)lt_resolve_import(dn,NULL,*ot&0xffff); else *at=(uint32_t)lt_resolve_import(dn,(char*)(base+*ot+2),0); } } }
  free(file);
  if(entry){ int ok=((int (WINAPI*)(void*,DWORD,void*))(base+entry))(base,1,NULL); if(!ok){ lt_log("DllMain failed for %s",low); nmods--; munmap(base,isz); return NULL; } }
  return m; }
HMODULE WINAPI W_LoadLibraryA(LPCSTR name){
  if(getenv("LT_TRACE")){ extern unsigned lt_va_of(unsigned); Dl_info di; void *ra=__builtin_return_address(0); int ok=dladdr(ra,&di); lt_log("LoadLibrary(%s) caller_va=%x ra=%p in %s+%#lx sym=%s",name,lt_va_of((unsigned)ra),ra,ok&&di.dli_fname?di.dli_fname:"?",ok?(unsigned long)((char*)ra-(char*)di.dli_fbase):0,ok&&di.dli_sname?di.dli_sname:"?"); }
  if(getenv("LT_TRACE")&&name&&!*name){ const unsigned char *r=(const unsigned char*)name-4; lt_log("  RMode dump: hw=%u dll='%s' internal='%.40s' desc='%.40s' w=%u h=%u bpp=%u next=%x",*(unsigned*)r,name,r+260,r+388,*(unsigned*)(r+516),*(unsigned*)(r+520),*(unsigned*)(r+524),*(unsigned*)(r+528)); { volatile unsigned *sp=(unsigned*)__builtin_frame_address(0); int n=0; char b[400]=""; for(int i=0;i<600&&n<14;i++){ unsigned v=sp[i]; if(v>0x401000&&v<0x4cb000){ const unsigned char *c=(const unsigned char*)v; if(c[-5]==0xE8||c[-6]==0xFF||c[-2]==0xFF||c[-3]==0xFF){ char t[16]; snprintf(t,sizeof t," %x",v); strcat(b,t); n++; } } } lt_log("  stack chain:%s",b); } }
  char low[128]; lower_base(name,low,sizeof low); pthread_mutex_lock(&mmx);
  struct mod *m=find_mod(low);
  if(!m&&is_shim(low)){ m=&mods[nmods++]; memset(m,0,sizeof *m); snprintf(m->name,sizeof m->name,"%s",low); m->shim=1; m->base=(uint8_t*)(0x7c000000u+nmods*0x10000); }
  if(!m){ char p[1024]; win2unix(name,p,sizeof p); if(access(p,R_OK)) { char alt[1024]; win2unix(low,alt,sizeof alt); if(!access(alt,R_OK)) strcpy(p,alt); }
    { FILE *ef=fopen(p,"rb"); unsigned char mg[4]={0}; if(ef){ size_t rd=fread(mg,1,4,ef); (void)rd; fclose(ef); }
      if(!memcmp(mg,"\x7f""ELF",4)){ char rp[PATH_MAX]; if(!realpath(p,rp)) snprintf(rp,sizeof rp,"%s",p); void *h=dlopen(rp,RTLD_NOW|RTLD_LOCAL);
        if(!h){ lt_log("LoadLibrary(%s): dlopen failed: %s",name,dlerror()); set_last_error(126); pthread_mutex_unlock(&mmx); return NULL; }
        m=&mods[nmods++]; memset(m,0,sizeof *m); m->elf=h; snprintf(m->name,sizeof m->name,"%s",low); snprintf(m->wpath,sizeof m->wpath,"%s",rp); m->base=(uint8_t*)(0x7d000000u+nmods*0x10000);
        if(getenv("LT_TRACE")) lt_log("LoadLibrary(%s): native ELF module %s",name,rp); pthread_mutex_unlock(&mmx); return m->base; } }
    m=load_pe(low,p); if(!m){ lt_log("LoadLibrary(%s) failed",name); set_last_error(126); pthread_mutex_unlock(&mmx); return NULL; } }
  else m->refs++;
  pthread_mutex_unlock(&mmx); return m->base; }
HMODULE WINAPI W_GetModuleHandleA(LPCSTR name){ if(!name) return (HMODULE)MAIN_BASE; char low[128]; lower_base(name,low,sizeof low); pthread_mutex_lock(&mmx); struct mod *m=find_mod(low); if(!m&&is_shim(low)){ pthread_mutex_unlock(&mmx); return W_LoadLibraryA(name); } pthread_mutex_unlock(&mmx); if(!m){ set_last_error(126); return NULL; } return m->base; }
BOOL WINAPI W_FreeLibrary(HMODULE h){ return 1; }
static void *elf_sym(HMODULE h,const char *n){ for(int i=0;i<nmods;i++) if(mods[i].base==(uint8_t*)h&&mods[i].elf) return dlsym(mods[i].elf,n); return NULL; }
static int is_elf_mod(HMODULE h){ for(int i=0;i<nmods;i++) if(mods[i].base==(uint8_t*)h&&mods[i].elf) return 1; return 0; }
void *WINAPI W_GetProcAddress(HMODULE h,LPCSTR name){
  if(h&&is_elf_mod(h)&&!MAKEINTRESOURCE_IS_INT(name)) return elf_sym(h,name);
  struct mod *m=NULL; for(int i=0;i<nmods;i++) if(mods[i].base==(uint8_t*)h) m=&mods[i];
  int byord=MAKEINTRESOURCE_IS_INT(name);
  if(m&&!m->shim){ void *f=pe_export(m,byord?NULL:name,(unsigned)(uintptr_t)name); if(!f) set_last_error(127); return f; }
  if(byord) return NULL; void *f=export_lookup(name); if(!f){ char low[128]="?"; if(m) snprintf(low,sizeof low,"%s",m->name); f=make_stub(low,name); } return f; }
const char *lt_module_path(HMODULE h){ for(int i=0;i<nmods;i++) if(mods[i].base==(uint8_t*)h&&mods[i].wpath[0]) return mods[i].wpath; return NULL; }
HMODULE lt_module_of(const void *a){ for(int i=0;i<nmods;i++) if(!mods[i].shim&&(uint8_t*)a>=mods[i].base&&(uint8_t*)a<mods[i].base+mods[i].size) return mods[i].base; return (uint8_t*)a>=(uint8_t*)0x400000&&(uint8_t*)a<(uint8_t*)0x500000?(HMODULE)0x400000:NULL; }
/* ---------- resources ---------- */
static uint8_t *rbase(HMODULE h,uint32_t *rva){ if(!h||h==(HMODULE)MAIN_BASE){ *rva=MAIN_RSRC_RVA; return (uint8_t*)MAIN_BASE; } for(int i=0;i<nmods;i++) if(mods[i].base==(uint8_t*)h&&!mods[i].shim){ *rva=mods[i].rsrc_rva; return mods[i].base; } return NULL; }
static int name_eq(uint8_t *rs,uint32_t off,const char *n){ uint16_t len=*(uint16_t*)(rs+off); WCHAR *w=(WCHAR*)(rs+off+2); if(len!=strlen(n)) return 0; for(int i=0;i<len;i++) if(tolower(w[i])!=tolower((unsigned char)n[i])) return 0; return 1; }
static uint8_t *find_ent(uint8_t *rs,uint32_t dir,const void *id,int *isdir){   /* id: int-resource or string */
  RDIR *d=(RDIR*)(rs+dir); RENT *e=(RENT*)(d+1); int n=d->NNamed+d->NId;
  for(int i=0;i<n;i++){ int hit; if(id==NULL) hit=1; else if(MAKEINTRESOURCE_IS_INT(id)) hit=!(e[i].Name&0x80000000u)&&e[i].Name==(uint32_t)(uintptr_t)id; else { const char *s=id; if(s[0]=='#') hit=!(e[i].Name&0x80000000u)&&e[i].Name==(uint32_t)atoi(s+1); else hit=(e[i].Name&0x80000000u)&&name_eq(rs,e[i].Name&0x7fffffff,s); }
    if(hit){ *isdir=(e[i].Off&0x80000000u)!=0; return (uint8_t*)&e[i]; } }
  return NULL; }
void *WINAPI W_FindResourceA(HMODULE h,LPCSTR name,LPCSTR type){
  uint32_t rva; uint8_t *b=rbase(h,&rva); if(!b){ set_last_error(ERROR_INVALID_PARAMETER); return NULL; } uint8_t *rs=b+rva; int isd; uint32_t dir=0;
  const void *ids[2]={type,name};
  for(int lvl=0;lvl<2;lvl++){ RENT *e=(RENT*)find_ent(rs,dir,ids[lvl],&isd); if(!e||!isd){ set_last_error(1813); return NULL; } dir=e->Off&0x7fffffff; }
  RENT *e=(RENT*)find_ent(rs,dir,NULL,&isd); if(!e){ set_last_error(1813); return NULL; } return rs+e->Off; }
void *WINAPI W_LoadResource(HMODULE h,void *hr){ uint32_t rva; uint8_t *b=rbase(h,&rva); if(!b||!hr) return NULL; return b+((RDATA*)hr)->Rva; }
void *WINAPI W_LockResource(void *h){ return h; }
DWORD WINAPI W_SizeofResource(HMODULE h,void *hr){ return hr?((RDATA*)hr)->Size:0; }
int WINAPI W_LoadStringA(HMODULE h,UINT id,char *buf,int n){
  void *r=W_FindResourceA(h,(LPCSTR)(uintptr_t)((id>>4)+1),(LPCSTR)6); if(getenv("LT_TRACE")) lt_log("LoadString(h=%p,id=%u) -> res=%p",h,id,r); if(!r){ if(n) buf[0]=0; return 0; }
  WCHAR *w=W_LoadResource(h,r); for(UINT i=0;i<(id&15);i++) w+=1+*w; int len=*w++; if(!n) return 0; if(len>=n) len=n-1; for(int i=0;i<len;i++) buf[i]=w[i]<256?w[i]:'?'; buf[len]=0; if(getenv("LT_TRACE")) lt_log("LoadString n=%d len=%d '%s'",n,len,buf); return len; }
