/* kernel32: memory, heaps, threads, sync, TLS, process/env, locale */
#include "win.h"
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <malloc.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <setjmp.h>
extern char **environ;
void *lt_set_unhandled(void *f);
/* ---- heaps ---- */
static HANDLE proc_heap;
HANDLE WINAPI W_GetProcessHeap(void){ if(!proc_heap) proc_heap=obj_new(H_HEAP,NULL); return proc_heap; }
HANDLE WINAPI W_HeapCreate(DWORD f,DWORD i,DWORD m){ return obj_new(H_HEAP,NULL); }
BOOL WINAPI W_HeapDestroy(HANDLE h){ if(h!=proc_heap) obj_free(h); return 1; }
void *WINAPI W_HeapAlloc(HANDLE h,DWORD f,DWORD n){ void *p=(f&8)?calloc(1,n?n:1):malloc(n?n:1); if(!p){ set_last_error(ERROR_NOT_ENOUGH_MEMORY); { lt_log("HeapAlloc(%u) FAILED errno=%d flags=%x heap=%p",n,errno,f,h); FILE *st=fopen("/proc/self/status","r"); char l[200]; while(st&&fgets(l,sizeof l,st)) if(!strncmp(l,"VmSize",6)||!strncmp(l,"VmData",6)||!strncmp(l,"VmRSS",5)) fputs(l,stderr); if(st) fclose(st); } } return p; }
void *WINAPI W_HeapReAlloc(HANDLE h,DWORD f,void *p,DWORD n){ if(!p) return W_HeapAlloc(h,f,n); size_t o=malloc_usable_size(p); void *q=realloc(p,n?n:1); if(q&&(f&8)&&n>o) memset((char*)q+o,0,n-o); return q; }
BOOL WINAPI W_HeapFree(HANDLE h,DWORD f,void *p){ free(p); return 1; }
DWORD WINAPI W_HeapSize(HANDLE h,DWORD f,void *p){ return p?malloc_usable_size(p):(DWORD)-1; }
DWORD WINAPI W_HeapCompact(HANDLE h,DWORD f){ return 0; }
/* ---- virtual memory ---- */
static int prot_of(DWORD p){ switch(p&0xff){ case 1: return PROT_NONE; case 2: return PROT_READ; case 4: case 8: return PROT_READ|PROT_WRITE; case 0x10: return PROT_EXEC; case 0x20: return PROT_READ|PROT_EXEC; case 0x40: case 0x80: return PROT_READ|PROT_WRITE|PROT_EXEC; } return PROT_READ|PROT_WRITE; }
static struct { void *a; size_t n; } vm[1024]; static pthread_mutex_t vmx=PTHREAD_MUTEX_INITIALIZER;
void *WINAPI W_VirtualAlloc(void *addr,DWORD size,DWORD type,DWORD prot){
  size=(size+4095)&~4095u; void *r;
  if(addr){ void *base=(void*)((uintptr_t)addr&~4095u);
    r=mmap(base,size,prot_of(prot),MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED_NOREPLACE,-1,0);
    if(r==MAP_FAILED){ if(mprotect(base,size,prot_of(prot))==0) return addr; set_last_error(ERROR_NOT_ENOUGH_MEMORY); return NULL; }
  } else { r=mmap(NULL,size,prot_of(prot),MAP_PRIVATE|MAP_ANONYMOUS,-1,0); if(r==MAP_FAILED){ set_last_error(ERROR_NOT_ENOUGH_MEMORY); return NULL; } }
  pthread_mutex_lock(&vmx); for(int i=0;i<1024;i++) if(!vm[i].a){ vm[i].a=r; vm[i].n=size; break; } pthread_mutex_unlock(&vmx); return r; }
BOOL WINAPI W_VirtualFree(void *a,DWORD size,DWORD type){
  if(type&0x8000){ pthread_mutex_lock(&vmx); for(int i=0;i<1024;i++) if(vm[i].a==a){ munmap(a,vm[i].n); vm[i].a=0; break; } pthread_mutex_unlock(&vmx); return 1; }
  if(type&0x4000){ madvise(a,(size+4095)&~4095u,MADV_DONTNEED); return 1; } return 0; }
typedef struct { void *base,*allocbase; DWORD allocprot,size,state,prot,type; } MBI;
DWORD WINAPI W_VirtualQuery(const void *p,MBI *m,DWORD len){
  uintptr_t a=(uintptr_t)p; FILE *f=fopen("/proc/self/maps","r"); char line[512]; uintptr_t last_end=0;
  memset(m,0,sizeof *m);
  while(f&&fgets(line,sizeof line,f)){ unsigned long s,e; char pr[8]; if(sscanf(line,"%lx-%lx %7s",&s,&e,pr)!=3) continue;
    if(a>=s&&a<e){ m->base=(void*)(a&~4095u); m->allocbase=(void*)s; m->size=e-(a&~4095u); m->state=0x1000; m->type=0x20000;
      m->prot=(pr[0]=='r'&&pr[1]=='w'&&pr[2]=='x')?0x40:(pr[0]=='r'&&pr[1]=='w')?4:(pr[0]=='r'&&pr[2]=='x')?0x20:pr[0]=='r'?2:pr[2]=='x'?0x10:1; m->allocprot=m->prot; fclose(f); return sizeof *m; }
    if(s>a){ m->base=(void*)(a&~4095u); m->size=s-(a&~4095u); m->state=0x10000; m->prot=1; fclose(f); return sizeof *m; } last_end=e; }
  if(f) fclose(f); m->base=(void*)(a&~4095u); m->state=0x10000; m->size=0x1000; m->prot=1; (void)last_end; return sizeof *m; }
static BOOL bad(const void *p,DWORD n){ if(!p) return 1; if(!n) return 0; uintptr_t a=(uintptr_t)p&~4095u, e=((uintptr_t)p+n+4095)&~4095u; unsigned char v; for(;a<e;a+=4096) if(mincore((void*)a,1,&v)) return 1; return 0; }
BOOL WINAPI W_IsBadReadPtr(const void *p,DWORD n){ return bad(p,n); }
BOOL WINAPI W_IsBadWritePtr(void *p,DWORD n){ return bad(p,n); }
BOOL WINAPI W_IsBadCodePtr(const void *p){ return bad(p,1); }
void WINAPI W_GlobalMemoryStatus(DWORD *m){ struct sysinfo s; sysinfo(&s); uint64_t tot=(uint64_t)s.totalram*s.mem_unit, fr=(uint64_t)s.freeram*s.mem_unit; if(tot>0x7fffffffu) tot=0x7fffffffu; if(fr>tot) fr=tot; m[0]=32; m[1]=(DWORD)(100-fr*100/(tot?tot:1)); m[2]=tot; m[3]=fr; m[4]=tot; m[5]=fr; m[6]=0x7fff0000; m[7]=0x7ff00000; }
void WINAPI W_GetSystemInfo(DWORD *s){ memset(s,0,36); s[1]=4096; s[2]=0x10000; s[3]=0x7ffeffff; s[5]=sysconf(_SC_NPROCESSORS_ONLN); s[4]=(1u<<s[5])-1; s[6]=586; s[7]=65536; ((WORD*)s)[16]=6; }
/* ---- sync / threads ---- */
static __thread struct obj *cur_thread; static __thread jmp_buf exit_jb; static __thread DWORD exit_code_tl;
static struct obj *waitable(HANDLE h){ return obj_get(h); }
static int is_signaled(struct obj *o){ switch(o->type){ case H_EVENT: return o->signaled; case H_THREAD: return o->signaled; default: return 1; } }
static void consume(struct obj *o){ if(o->type==H_EVENT&&!o->manual) o->signaled=0; }
static DWORD wait_many(DWORD n,const HANDLE *hs,BOOL all,DWORD ms){
  struct timespec dl; if(ms!=INFINITE){ clock_gettime(CLOCK_REALTIME,&dl); dl.tv_sec+=ms/1000; dl.tv_nsec+=(ms%1000)*1000000L; if(dl.tv_nsec>=1000000000L){dl.tv_sec++; dl.tv_nsec-=1000000000L;} }
  pthread_mutex_lock(&lt_wait_mx);
  for(;;){
    int cnt=0; DWORD first=WAIT_FAILED;
    for(DWORD i=0;i<n;i++){ struct obj *o=waitable(hs[i]); if(!o){ pthread_mutex_unlock(&lt_wait_mx); set_last_error(ERROR_INVALID_HANDLE); return WAIT_FAILED; } if(is_signaled(o)){ cnt++; if(first==WAIT_FAILED) first=i; } }
    if((all&&cnt==(int)n)||(!all&&cnt)){ if(all) for(DWORD i=0;i<n;i++) consume(waitable(hs[i])); else consume(waitable(hs[first])); pthread_mutex_unlock(&lt_wait_mx); return WAIT_OBJECT_0+(all?0:first); }
    if(ms==0){ pthread_mutex_unlock(&lt_wait_mx); return WAIT_TIMEOUT; }
    if(ms==INFINITE) pthread_cond_wait(&lt_wait_cv,&lt_wait_mx);
    else if(pthread_cond_timedwait(&lt_wait_cv,&lt_wait_mx,&dl)==ETIMEDOUT){ pthread_mutex_unlock(&lt_wait_mx); return WAIT_TIMEOUT; }
  } }
DWORD WINAPI W_WaitForSingleObject(HANDLE h,DWORD ms){ return wait_many(1,&h,0,ms); }
DWORD WINAPI W_WaitForMultipleObjects(DWORD n,const HANDLE *h,BOOL all,DWORD ms){ return wait_many(n,h,all,ms); }
HANDLE WINAPI W_CreateEventA(void *sa,BOOL manual,BOOL init,LPCSTR name){ struct obj *o; HANDLE h=obj_new(H_EVENT,&o); if(h){ o->manual=manual; o->signaled=init; } return h; }
BOOL WINAPI W_SetEvent(HANDLE h){ struct obj *o=obj_get(h); if(!o) return 0; pthread_mutex_lock(&lt_wait_mx); o->signaled=1; pthread_cond_broadcast(&lt_wait_cv); pthread_mutex_unlock(&lt_wait_mx); return 1; }
BOOL WINAPI W_ResetEvent(HANDLE h){ struct obj *o=obj_get(h); if(!o) return 0; pthread_mutex_lock(&lt_wait_mx); o->signaled=0; pthread_mutex_unlock(&lt_wait_mx); return 1; }
BOOL WINAPI W_PulseEvent(HANDLE h){ struct obj *o=obj_get(h); if(!o) return 0; pthread_mutex_lock(&lt_wait_mx); o->signaled=1; pthread_cond_broadcast(&lt_wait_cv); pthread_mutex_unlock(&lt_wait_mx); sched_yield(); pthread_mutex_lock(&lt_wait_mx); o->signaled=0; pthread_mutex_unlock(&lt_wait_mx); return 1; }
static void *thread_main(void *arg){
  struct obj *o=arg; int dummy; lt_thread_init(&dummy+0x1000/4); cur_thread=o;
  DWORD r; if(setjmp(exit_jb)==0) r=((DWORD (WINAPI*)(void*))o->start)(o->param); else r=exit_code_tl;
  pthread_mutex_lock(&lt_wait_mx); o->exit=r; o->signaled=1; pthread_cond_broadcast(&lt_wait_cv); pthread_mutex_unlock(&lt_wait_mx); return NULL; }
static int start_thread(struct obj *o){ pthread_attr_t a; pthread_attr_init(&a); pthread_attr_setstacksize(&a,8<<20); o->started=1; o->suspended=0; return pthread_create(&o->th,&a,thread_main,o); }
HANDLE WINAPI W_CreateThread(void *sa,DWORD stack,void *start,void *param,DWORD flags,DWORD *tid){
  struct obj *o; HANDLE h=obj_new(H_THREAD,&o); if(!h) return NULL; o->start=start; o->param=param;
  if(flags&4) o->suspended=1; else if(start_thread(o)){ lt_log("CreateThread FAILED (errno %d)",errno); obj_free(h); set_last_error(ERROR_NOT_ENOUGH_MEMORY); return NULL; }
  if(tid) *tid=(DWORD)h; return h; }
DWORD WINAPI W_ResumeThread(HANDLE h){ struct obj *o=obj_get(h); if(!o||o->type!=H_THREAD) return (DWORD)-1; if(o->suspended){ start_thread(o); return 1; } return 0; }
BOOL WINAPI W_SetThreadPriority(HANDLE h,int p){ return 1; }
void WINAPI W_ExitThread(DWORD code){ if(!cur_thread){ fflush(NULL); exit(code); } exit_code_tl=code; longjmp(exit_jb,1); }
DWORD WINAPI W_GetCurrentThreadId(void){ return syscall(SYS_gettid); }
HANDLE WINAPI W_GetCurrentProcess(void){ return (HANDLE)-1; }
BOOL WINAPI W_SetPriorityClass(HANDLE h,DWORD c){ return 1; }
void WINAPI W_InitializeCriticalSection(void *cs){ pthread_mutexattr_t a; pthread_mutexattr_init(&a); pthread_mutexattr_settype(&a,PTHREAD_MUTEX_RECURSIVE); pthread_mutex_init((pthread_mutex_t*)cs,&a); }
void WINAPI W_EnterCriticalSection(void *cs){ pthread_mutex_lock((pthread_mutex_t*)cs); }
void WINAPI W_LeaveCriticalSection(void *cs){ pthread_mutex_unlock((pthread_mutex_t*)cs); }
void WINAPI W_DeleteCriticalSection(void *cs){ pthread_mutex_destroy((pthread_mutex_t*)cs); }
LONG WINAPI W_InterlockedIncrement(volatile LONG *p){ return __sync_add_and_fetch(p,1); }
LONG WINAPI W_InterlockedDecrement(volatile LONG *p){ return __sync_sub_and_fetch(p,1); }
LONG WINAPI W_InterlockedExchange(volatile LONG *p,LONG v){ return __sync_lock_test_and_set(p,v); }
/* ---- TLS / errors ---- */
static int tls_next; static pthread_mutex_t tlsmx=PTHREAD_MUTEX_INITIALIZER;
DWORD WINAPI W_TlsAlloc(void){ pthread_mutex_lock(&tlsmx); DWORD i=tls_next<TLS_SLOTS?tls_next++:(DWORD)-1; pthread_mutex_unlock(&tlsmx); return i; }
BOOL WINAPI W_TlsSetValue(DWORD i,void *v){ if(i>=TLS_SLOTS) return 0; ((void**)((char*)lt_teb+TEB_TLS))[i]=v; return 1; }
void *WINAPI W_TlsGetValue(DWORD i){ if(i>=TLS_SLOTS) return NULL; set_last_error(0); return ((void**)((char*)lt_teb+TEB_TLS))[i]; }
DWORD WINAPI W_GetLastError(void){ return get_last_error(); }
void WINAPI W_SetLastError(DWORD e){ set_last_error(e); }
/* ---- process / env ---- */
char lt_cmdline[2048]="lithtech.exe";
void WINAPI W_ExitProcess(DWORD c){ fflush(NULL); exit(c); }
BOOL WINAPI W_TerminateProcess(HANDLE h,DWORD c){ fflush(NULL); _exit(c); }
void WINAPI W_GetStartupInfoA(DWORD *si){ memset(si,0,68); si[0]=68; }
LPCSTR WINAPI W_GetCommandLineA(void){ return lt_cmdline; }
DWORD WINAPI W_GetVersion(void){ return 0x0A280105; }
BOOL WINAPI W_GetVersionExA(DWORD *v){ DWORD sz=v[0]; memset(v,0,sz); v[0]=sz; v[1]=5; v[2]=1; v[3]=2600; v[4]=2; return 1; }
void *WINAPI W_GetEnvironmentStringsA(void){ size_t n=1; for(char **e=environ;*e;e++) n+=strlen(*e)+1; char *b=malloc(n),*p=b; for(char **e=environ;*e;e++){ size_t l=strlen(*e)+1; memcpy(p,*e,l); p+=l; } *p=0; return b; }
void *WINAPI W_GetEnvironmentStrings(void){ return W_GetEnvironmentStringsA(); }
void *WINAPI W_GetEnvironmentStringsW(void){ size_t n=1; for(char **e=environ;*e;e++) n+=strlen(*e)+1; WCHAR *b=malloc(n*2),*p=b; for(char **e=environ;*e;e++) for(const char *c=*e;;c++){ *p++=(unsigned char)*c; if(!*c) break; } *p=0; return b; }
BOOL WINAPI W_FreeEnvironmentStringsA(void *p){ free(p); return 1; }
BOOL WINAPI W_FreeEnvironmentStringsW(void *p){ free(p); return 1; }
DWORD WINAPI W_GetEnvironmentVariableA(LPCSTR n,char *b,DWORD sz){ const char *v=getenv(n); if(!v){ set_last_error(203); return 0; } if(strlen(v)>=sz) return strlen(v)+1; strcpy(b,v); return strlen(v); }
BOOL WINAPI W_SetEnvironmentVariableA(LPCSTR n,LPCSTR v){ return (v?setenv(n,v,1):unsetenv(n))==0; }
void *WINAPI W_SetUnhandledExceptionFilter(void *f){ return lt_set_unhandled(f); }
LONG WINAPI W_UnhandledExceptionFilter(void *p){ return 1; }
void WINAPI W_DebugBreak(void){ raise(SIGTRAP); }
/* ---- locale ---- */
DWORD WINAPI W_GetACP(void){ return 1252; } DWORD WINAPI W_GetOEMCP(void){ return 437; }
BOOL WINAPI W_GetCPInfo(DWORD cp,BYTE *i){ memset(i,0,20); *(DWORD*)i=1; i[4]='?'; return 1; }
static int u8dec(const unsigned char *s,int n,unsigned *cp){ unsigned c=s[0]; if(c<0x80){*cp=c;return 1;} if((c>>5)==6&&n>1){*cp=((c&31)<<6)|(s[1]&63);return 2;} if((c>>4)==14&&n>2){*cp=((c&15)<<12)|((s[1]&63)<<6)|(s[2]&63);return 3;} *cp=c; return 1; }
int WINAPI W_MultiByteToWideChar(DWORD cp,DWORD fl,const char *s,int n,WCHAR *d,int dn){
  if(n<0) n=strlen(s)+1; int o=0;
  for(int i=0;i<n;){ unsigned c; int k=cp==65001?u8dec((const unsigned char*)s+i,n-i,&c):(c=(unsigned char)s[i],1); if(d){ if(o>=dn){ set_last_error(ERROR_INSUFFICIENT_BUFFER); return 0; } d[o]=c; } o++; i+=k; }
  return o; }
int WINAPI W_WideCharToMultiByte(DWORD cp,DWORD fl,const WCHAR *s,int n,char *d,int dn,const char *def,BOOL *used){
  if(n<0){ n=0; while(s[n]) n++; n++; } int o=0; if(used)*used=0;
  for(int i=0;i<n;i++){ unsigned c=s[i]; char t[4]; int k;
    if(cp==65001){ if(c<0x80){t[0]=c;k=1;} else if(c<0x800){t[0]=0xC0|(c>>6);t[1]=0x80|(c&63);k=2;} else {t[0]=0xE0|(c>>12);t[1]=0x80|((c>>6)&63);t[2]=0x80|(c&63);k=3;} }
    else { t[0]=c<256?c:'?'; if(c>=256&&used)*used=1; k=1; }
    if(d){ if(o+k>dn){ set_last_error(ERROR_INSUFFICIENT_BUFFER); return 0; } memcpy(d+o,t,k); } o+=k; }
  return o; }
static int cmpstr(const WCHAR *a,int an,const WCHAR *b,int bn,DWORD fl){ int i=0; for(;;i++){ int ea=an>=0?i>=an:!a[i], eb=bn>=0?i>=bn:!b[i]; if(ea&&eb) return 2; if(ea) return 1; if(eb) return 3; unsigned x=a[i],y=b[i]; if(fl&1){ if(x<128) x=tolower(x); if(y<128) y=tolower(y); } if(x!=y) return x<y?1:3; } }
int WINAPI W_CompareStringA(DWORD l,DWORD f,const char *a,int an,const char *b,int bn){ int n=an<0?(int)strlen(a):an,m=bn<0?(int)strlen(b):bn; WCHAR *x=malloc(2*(n+1)),*y=malloc(2*(m+1)); for(int i=0;i<n;i++) x[i]=(unsigned char)a[i]; for(int i=0;i<m;i++) y[i]=(unsigned char)b[i]; int r=cmpstr(x,n,y,m,f); free(x); free(y); return r; }
int WINAPI W_CompareStringW(DWORD l,DWORD f,const WCHAR *a,int an,const WCHAR *b,int bn){ return cmpstr(a,an,b,bn,f); }
static WORD ctype1(unsigned c){ WORD r=0; if(c>255) return r; if(isupper(c)) r|=1|0x100; if(islower(c)) r|=2|0x100; if(isdigit(c)) r|=4; if(isspace(c)) r|=8; if(ispunct(c)) r|=0x10; if(iscntrl(c)) r|=0x20; if(c==' '||c=='\t') r|=0x40; if(isxdigit(c)) r|=0x80; if(isalpha(c)) r|=0x100; return r; }
BOOL WINAPI W_GetStringTypeA(DWORD l,DWORD t,const char *s,int n,WORD *o){ if(n<0) n=strlen(s)+1; for(int i=0;i<n;i++) o[i]=ctype1((unsigned char)s[i]); return 1; }
BOOL WINAPI W_GetStringTypeW(DWORD t,const WCHAR *s,int n,WORD *o){ if(n<0){ n=0; while(s[n]) n++; n++; } for(int i=0;i<n;i++) o[i]=ctype1(s[i]); return 1; }
int WINAPI W_LCMapStringA(DWORD l,DWORD f,const char *s,int n,char *d,int dn){ if(n<0) n=strlen(s)+1; if(!dn) return n; if(n>dn) return 0; for(int i=0;i<n;i++){ unsigned char c=s[i]; d[i]=(f&0x100)?tolower(c):(f&0x200)?toupper(c):c; } return n; }
int WINAPI W_LCMapStringW(DWORD l,DWORD f,const WCHAR *s,int n,WCHAR *d,int dn){ if(n<0){ n=0; while(s[n]) n++; n++; } if(!dn) return n; if(n>dn) return 0; for(int i=0;i<n;i++){ unsigned c=s[i]; d[i]=c<128?((f&0x100)?tolower(c):(f&0x200)?toupper(c):c):c; } return n; }

BOOL WINAPI W_IsProcessorFeaturePresent(DWORD f){ return 0; }
UINT WINAPI W_SetErrorMode(UINT m){ return 0; }
DWORD WINAPI W_WaitForSingleObjectEx(HANDLE h,DWORD ms,BOOL alertable){ return wait_many(1,&h,0,ms); }
DWORD WINAPI W_SleepEx(DWORD ms,BOOL a){ W_Sleep(ms); return 0; }
