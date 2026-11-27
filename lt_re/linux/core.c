/* Core: handle table, TEB/fs setup (set_thread_area), logging, SEH dispatch (RaiseException/RtlUnwind), signal->SEH. */
#include "win.h"
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <asm/ldt.h>
#include <ucontext.h>
__thread void *lt_teb;
pthread_mutex_t lt_wait_mx=PTHREAD_MUTEX_INITIALIZER; pthread_cond_t lt_wait_cv=PTHREAD_COND_INITIALIZER;
static char fake_peb[0x1000] __attribute__((aligned(16)));
void lt_log(const char *fmt,...){ va_list a; va_start(a,fmt); fputs("[lt] ",stderr); vfprintf(stderr,fmt,a); fputc('\n',stderr); va_end(a);}
void lt_thread_init(void *stackbase){
  char *t=calloc(1,TEB_SIZE+16); t=(char*)(((uintptr_t)t+15)&~15u);
  *(void**)(t+TEB_SELF)=t; *(void**)(t+TEB_PEB)=fake_peb; *(void**)(t+TEB_EXC)=(void*)-1;
  *(void**)(t+TEB_STACKBASE)=stackbase; *(void**)(t+TEB_STACKLIMIT)=(char*)stackbase-0x100000;
  *(uint32_t*)(fake_peb+8)=0x400000;           /* PEB.ImageBaseAddress */
  struct user_desc d; memset(&d,0,sizeof d); d.entry_number=-1; d.base_addr=(unsigned)t; d.limit=0xfff; d.seg_32bit=1; d.useable=1;
  if(syscall(SYS_set_thread_area,&d)<0){ perror("set_thread_area"); exit(1);} 
  uint16_t sel=(d.entry_number<<3)|3; __asm__ volatile("movw %0,%%fs"::"r"(sel));
  lt_teb=t;
}
/* ---- handle table ---- */
#define MAXH 8192
static struct obj *tab[MAXH]; static pthread_mutex_t hmx=PTHREAD_MUTEX_INITIALIZER;
HANDLE obj_new(int type,struct obj **out){
  pthread_mutex_lock(&hmx);
  for(int i=1;i<MAXH;i++) if(!tab[i]){ tab[i]=calloc(1,sizeof(struct obj)); tab[i]->type=type; tab[i]->fd=-1; pthread_mutex_unlock(&hmx); if(out)*out=tab[i]; return (HANDLE)(uintptr_t)(i*4); }
  pthread_mutex_unlock(&hmx); return NULL; }
struct obj *obj_get(HANDLE h){ uintptr_t v=(uintptr_t)h; if(v==0||v%4||v/4>=MAXH) return NULL; return tab[v/4]; }
void obj_free(HANDLE h){ uintptr_t v=(uintptr_t)h; if(v&&v%4==0&&v/4<MAXH){ pthread_mutex_lock(&hmx); free(tab[v/4]); tab[v/4]=NULL; pthread_mutex_unlock(&hmx);} }
/* ---- SEH: Windows-style frame chain at fs:[0] ---- */
typedef struct { DWORD code, flags; void *rec; void *addr; DWORD nparams; DWORD info[15]; } EXC_REC;
typedef struct { DWORD flags; DWORD dr[6]; char fp[112]; DWORD seg_gs,seg_fs,seg_es,seg_ds,edi,esi,ebx,edx,ecx,eax,ebp,eip,seg_cs,eflags,esp,seg_ss; char ext[512]; } CONTEXT;
typedef struct EXC_FRAME { struct EXC_FRAME *next; void *handler; } EXC_FRAME;
typedef int (WINAPI *EXC_HANDLER)(EXC_REC*,EXC_FRAME*,CONTEXT*,void*);
#define EXCEPTION_NONCONTINUABLE 1
#define EXCEPTION_UNWINDING 2
#define EXCEPTION_NESTED_CALL 0x10
static EXC_FRAME *head(void){ return *(EXC_FRAME**)((char*)lt_teb+TEB_EXC);} 
static void sethead(EXC_FRAME*f){ *(EXC_FRAME**)((char*)lt_teb+TEB_EXC)=f; }
static int dispatch(EXC_REC *r,CONTEXT *c){
  for(EXC_FRAME *f=head(); f && f!=(EXC_FRAME*)-1; f=f->next){
    void *disp[2]={0,0};
    int res=((EXC_HANDLER)f->handler)(r,f,c,disp);
    if(res==0) return 1;            /* ExceptionContinueExecution */
    /* 1 = ContinueSearch, others treated as search */
  }
  return 0;
}
static void *g_unhandled;
void *lt_set_unhandled(void *f){ void *o=g_unhandled; g_unhandled=f; return o; }
void WINAPI W_RaiseException(DWORD code,DWORD flags,DWORD n,const DWORD *args){
  EXC_REC r; memset(&r,0,sizeof r); r.code=code; r.flags=flags; r.nparams=n>15?15:n; for(DWORD i=0;i<r.nparams;i++) r.info[i]=args[i];
  r.addr=__builtin_return_address(0);
  CONTEXT c; memset(&c,0,sizeof c); c.eip=(DWORD)r.addr;
  if(dispatch(&r,&c)) return;
  lt_log("unhandled exception 0x%08x at %p",code,r.addr); fflush(stderr); _exit(3);
}
void WINAPI W_RtlUnwind(EXC_FRAME *target,void *targetIp,EXC_REC *rec,DWORD retval){
  EXC_REC local; if(!rec){ memset(&local,0,sizeof local); local.code=0xC0000027; rec=&local; }
  rec->flags|=EXCEPTION_UNWINDING; if(!target) rec->flags|=0x4; /* EXIT_UNWIND */
  CONTEXT c; memset(&c,0,sizeof c); c.eax=retval;
  EXC_FRAME *f=head();
  while(f && f!=(EXC_FRAME*)-1 && f!=target){
    void *disp[2]={0,0}; EXC_FRAME *next=f->next;
    ((EXC_HANDLER)f->handler)(rec,f,&c,disp);
    sethead(next); f=next;
  }
  rec->flags&=~(EXCEPTION_UNWINDING|4);
}
struct ltm { unsigned addr, va; }; extern struct ltm lt_map_start[], lt_map_end[];
unsigned lt_va_of(unsigned a){ struct ltm *lo=lt_map_start,*hi=lt_map_end; if(hi<=lo||a<lo->addr||a>=(hi-1)->addr+16) return 0; unsigned n=hi-lo,l=0,h=n; while(l+1<h){ unsigned m=(l+h)/2; if(lo[m].addr<=a) l=m; else h=m; } return lo[l].va; }
static void dump_chain(unsigned esp){ unsigned *p=(unsigned*)esp; fprintf(stderr,"[lt]   call chain (original exe addresses):"); int n=0; for(int i=0;i<2048&&n<14;i++){ unsigned va=lt_va_of(p[i]); if(va){ fprintf(stderr," %08x",va); n++; } } fprintf(stderr,"\n"); }
static void segv(int sig,siginfo_t *si,void *uc_){
  ucontext_t *uc=uc_; gregset_t *g=&uc->uc_mcontext.gregs;
  EXC_REC r; memset(&r,0,sizeof r);
  r.code = sig==SIGSEGV||sig==SIGBUS ? 0xC0000005 : sig==SIGFPE ? (si->si_code==FPE_INTDIV?0xC0000094:0xC000008E) : sig==SIGILL ? 0xC000001D : 0x80000003;
  r.addr=(void*)(*g)[REG_EIP]; if(r.code==0xC0000005){ r.nparams=2; r.info[0]=0; r.info[1]=(DWORD)si->si_addr; }
  CONTEXT c; memset(&c,0,sizeof c);
  c.eax=(*g)[REG_EAX]; c.ebx=(*g)[REG_EBX]; c.ecx=(*g)[REG_ECX]; c.edx=(*g)[REG_EDX]; c.esi=(*g)[REG_ESI]; c.edi=(*g)[REG_EDI]; c.ebp=(*g)[REG_EBP]; c.esp=(*g)[REG_ESP]; c.eip=(*g)[REG_EIP]; c.eflags=(*g)[REG_EFL];
  if(getenv("LT_TRACE")) { lt_log("exception code=%08x eip=%p (original VA 0x%08x) addr=%p",r.code,r.addr,lt_va_of((unsigned)r.addr),si->si_addr); dump_chain(c.esp); }
  if(dispatch(&r,&c)){ (*g)[REG_EAX]=c.eax;(*g)[REG_EBX]=c.ebx;(*g)[REG_ECX]=c.ecx;(*g)[REG_EDX]=c.edx;(*g)[REG_ESI]=c.esi;(*g)[REG_EDI]=c.edi;(*g)[REG_EBP]=c.ebp;(*g)[REG_ESP]=c.esp;(*g)[REG_EIP]=c.eip; return; }
  lt_log("fatal %s at eip=%p (original exe VA 0x%08x) addr=%p",sig==SIGSEGV?"access violation":sig==SIGFPE?"arithmetic fault":"signal",r.addr,lt_va_of((unsigned)r.addr),si->si_addr); dump_chain(c.esp); fflush(stderr); _exit(139);
}
void lt_install_signals(void){
  struct sigaction sa; memset(&sa,0,sizeof sa); sa.sa_sigaction=segv; sa.sa_flags=SA_SIGINFO|SA_NODEFER; sigemptyset(&sa.sa_mask);
  sigaction(SIGSEGV,&sa,0); sigaction(SIGFPE,&sa,0); sigaction(SIGILL,&sa,0); sigaction(SIGBUS,&sa,0);
}
