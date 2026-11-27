/* kernel32/advapi32/dwmapi additions needed by modern (MinGW-built) DLLs: wide file APIs, condition variables, SRW locks, global memory, registry, Crypt, DWM. */
#include "win.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <time.h>
static void w2a(const WCHAR *w,char *o,size_t n){ size_t k=0; for(;*w&&k+4<n;w++){ unsigned c=*w; if(c<0x80) o[k++]=c; else if(c<0x800){ o[k++]=0xC0|(c>>6); o[k++]=0x80|(c&63); } else { o[k++]=0xE0|(c>>12); o[k++]=0x80|((c>>6)&63); o[k++]=0x80|(c&63); } } o[k]=0; }
static void a2w(const char *s,WCHAR *o,size_t n){ size_t k=0; while(*s&&k+1<n){ unsigned char c=*s; unsigned cp; int l; if(c<0x80){cp=c;l=1;} else if((c>>5)==6){cp=((c&31)<<6)|(s[1]&63);l=2;} else if((c>>4)==14){cp=((c&15)<<12)|((s[1]&63)<<6)|(s[2]&63);l=3;} else {cp='?';l=4;} s+=l; o[k++]=cp; } o[k]=0; }
HANDLE WINAPI W_CreateFileA(LPCSTR,DWORD,DWORD,void*,DWORD,DWORD,HANDLE); HANDLE WINAPI W_FindFirstFileA(LPCSTR,void*); BOOL WINAPI W_FindNextFileA(HANDLE,void*);
DWORD WINAPI W_GetFileAttributesA(LPCSTR); BOOL WINAPI W_DeleteFileA(LPCSTR); HMODULE WINAPI W_LoadLibraryA(LPCSTR); void *WINAPI W_FindResourceA(HMODULE,LPCSTR,LPCSTR); DWORD WINAPI W_GetTickCount(void);
DWORD WINAPI W_GetFullPathNameA(LPCSTR,DWORD,char*,char**); DWORD WINAPI W_GetTempPathA(DWORD,char*);
HANDLE WINAPI W_CreateFileW(const WCHAR *n,DWORD a,DWORD s,void *sa,DWORD d,DWORD f,HANDLE t){ char u[1024]; w2a(n,u,sizeof u); return W_CreateFileA(u,a,s,sa,d,f,t); }
DWORD WINAPI W_GetFileAttributesW(const WCHAR *n){ char u[1024]; w2a(n,u,sizeof u); return W_GetFileAttributesA(u); }
BOOL WINAPI W_DeleteFileW(const WCHAR *n){ char u[1024]; w2a(n,u,sizeof u); return W_DeleteFileA(u); }
BOOL WINAPI W_RemoveDirectoryW(const WCHAR *n){ char a[1024],u[1024]; w2a(n,a,sizeof a); win2unix(a,u,sizeof u); return rmdir(u)==0; }
BOOL WINAPI W_MoveFileExW(const WCHAR *a,const WCHAR *b,DWORD f){ char x[1024],y[1024],ux[1024],uy[1024]; w2a(a,x,sizeof x); w2a(b,y,sizeof y); win2unix(x,ux,sizeof ux); win2unix(y,uy,sizeof uy); return rename(ux,uy)==0; }
BOOL WINAPI W_CreateHardLinkW(const WCHAR *l,const WCHAR *e,void *sa){ char x[1024],y[1024],ux[1024],uy[1024]; w2a(l,x,sizeof x); w2a(e,y,sizeof y); win2unix(x,ux,sizeof ux); win2unix(y,uy,sizeof uy); return link(uy,ux)==0; }
typedef struct { DWORD attr; FILETIME c,a,m; DWORD szhi,szlo,r0,r1; char name[260]; char alt[14]; } FDA; typedef struct { DWORD attr; FILETIME c,a,m; DWORD szhi,szlo,r0,r1; WCHAR name[260]; WCHAR alt[14]; } FDW;
static void fda2w(const FDA *a,FDW *w){ memset(w,0,sizeof *w); memcpy(w,a,44); a2w(a->name,w->name,260); }
HANDLE WINAPI W_FindFirstFileW(const WCHAR *p,FDW *w){ char u[1024]; w2a(p,u,sizeof u); FDA a; HANDLE h=W_FindFirstFileA(u,&a); if(h!=INVALID_HANDLE_VALUE) fda2w(&a,w); return h; }
BOOL WINAPI W_FindNextFileW(HANDLE h,FDW *w){ FDA a; if(!W_FindNextFileA(h,&a)) return 0; fda2w(&a,w); return 1; }
HANDLE WINAPI W_FindFirstVolumeW(WCHAR *b,DWORD n){ set_last_error(ERROR_NO_MORE_FILES); return INVALID_HANDLE_VALUE; } BOOL WINAPI W_FindNextVolumeW(HANDLE h,WCHAR *b,DWORD n){ set_last_error(ERROR_NO_MORE_FILES); return 0; } BOOL WINAPI W_FindVolumeClose(HANDLE h){ return 1; }
BOOL WINAPI W_GetVolumeInformationW(const WCHAR *r,WCHAR *a,DWORD b,DWORD *c,DWORD *d,DWORD *e,WCHAR *f,DWORD g){ set_last_error(ERROR_CALL_NOT_IMPLEMENTED); return 0; }
BOOL WINAPI W_GetDiskFreeSpaceExW(const WCHAR *r,uint64_t *av,uint64_t *tot,uint64_t *fr){ struct statvfs s; if(statvfs(".",&s)) return 0; if(av)*av=(uint64_t)s.f_bsize*s.f_bavail; if(tot)*tot=(uint64_t)s.f_bsize*s.f_blocks; if(fr)*fr=(uint64_t)s.f_bsize*s.f_bfree; return 1; }
DWORD WINAPI W_GetFullPathNameW(const WCHAR *f,DWORD n,WCHAR *b,WCHAR **part){ char a[1024],o[1100]; w2a(f,a,sizeof a); char *p; DWORD r=W_GetFullPathNameA(a,sizeof o,o,&p); if(r>=n) return r+1; a2w(o,b,n); if(part){ WCHAR *s=b,*l=b; for(;*s;s++) if(*s=='\\') l=s+1; *part=l; } return r; }
DWORD WINAPI W_GetTempPathW(DWORD n,WCHAR *b){ char t[300]; W_GetTempPathA(sizeof t,t); if(strlen(t)>=n) return strlen(t)+1; a2w(t,b,n); return strlen(t); }
HMODULE WINAPI W_LoadLibraryW(const WCHAR *n){ char u[1024]; w2a(n,u,sizeof u); return W_LoadLibraryA(u); }
void *WINAPI W_FindResourceW(HMODULE h,const WCHAR *n,const WCHAR *t){ char a[256],b[256]; const void *pa=n,*pb=t; if(!MAKEINTRESOURCE_IS_INT(n)){ w2a(n,a,sizeof a); pa=a; } if(!MAKEINTRESOURCE_IS_INT(t)){ w2a(t,b,sizeof b); pb=b; } return W_FindResourceA(h,pa,pb); }
BOOL WINAPI W_GetFileInformationByHandle(HANDLE h,DWORD *i){ struct obj *o=obj_get(h); struct stat st; if(!o||fstat(o->fd,&st)) return 0; memset(i,0,52); i[0]=S_ISDIR(st.st_mode)?0x10:0x80; i[8]=(DWORD)((uint64_t)st.st_size>>32); i[9]=(DWORD)st.st_size; i[10]=1; i[11]=(DWORD)(st.st_ino>>32); i[12]=(DWORD)st.st_ino; return 1; }
BOOL WINAPI W_GetFileSizeEx(HANDLE h,int64_t *sz){ struct obj *o=obj_get(h); struct stat st; if(!o||fstat(o->fd,&st)) return 0; *sz=st.st_size; return 1; }
/* ---- global memory ---- */
HANDLE WINAPI W_GlobalAlloc(UINT f,DWORD n){ return (f&0x40)?calloc(1,n?n:1):malloc(n?n:1); } HANDLE WINAPI W_GlobalFree(HANDLE h){ free(h); return NULL; } void *WINAPI W_GlobalLock(HANDLE h){ return h; } BOOL WINAPI W_GlobalUnlock(HANDLE h){ return 1; }
/* ---- misc ---- */
BOOL WINAPI W_DisableThreadLibraryCalls(HMODULE m){ return 1; } BOOL WINAPI W_FlushInstructionCache(HANDLE p,const void *a,DWORD n){ return 1; }
DWORD WINAPI W_GetThreadId(HANDLE h){ return (DWORD)(uintptr_t)h; } ULONGLONG WINAPI W_GetTickCount64(void){ struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts); return (ULONGLONG)ts.tv_sec*1000+ts.tv_nsec/1000000; }
BOOL WINAPI W_IsWow64Process(HANDLE h,BOOL *w){ if(w)*w=0; return 1; } BOOL WINAPI W_IsDBCSLeadByteEx(UINT cp,BYTE c){ return 0; }
BOOL WINAPI W_ReadProcessMemory(HANDLE p,const void *a,void *b,DWORD n,DWORD *r){ memcpy(b,a,n); if(r)*r=n; return 1; }
BOOL WINAPI W_SwitchToThread(void){ sched_yield(); return 1; } BOOL WINAPI W_TlsFree(DWORD i){ return 1; }
BOOL WINAPI W_TryEnterCriticalSection(void *cs){ return pthread_mutex_trylock((pthread_mutex_t*)cs)==0; }
ULONGLONG WINAPI W_VerSetConditionMask(ULONGLONG m,DWORD t,BYTE c){ return m; }
BOOL WINAPI W_VirtualProtect(void *a,DWORD n,DWORD np,DWORD *old){ int pr=(np&0xff)==1?PROT_NONE:(np&0xff)==2?PROT_READ:((np&0xff)==0x20)?PROT_READ|PROT_EXEC:((np&0xff)==0x40||(np&0xff)==0x80)?PROT_READ|PROT_WRITE|PROT_EXEC:PROT_READ|PROT_WRITE; uintptr_t s=(uintptr_t)a&~4095u,e=((uintptr_t)a+n+4095)&~4095u; if(old)*old=4; return mprotect((void*)s,e-s,pr)==0; }
DWORD WINAPI W_GetLocaleInfoA(DWORD l,DWORD t,char *b,int n){ if(b&&n) b[0]=0; return 1; }
BOOL WINAPI W_GetModuleHandleExA(DWORD f,LPCSTR n,HMODULE *m){ HMODULE W_GetModuleHandleA(LPCSTR); if(f&4){ extern HMODULE lt_module_of(const void*); *m=lt_module_of(n); return *m!=NULL; } *m=W_GetModuleHandleA(n); return *m!=NULL; }
BOOL WINAPI W_GetModuleHandleExW(DWORD f,const WCHAR *n,HMODULE *m){ extern HMODULE lt_module_of(const void*); if(f&4){ *m=lt_module_of(n); return *m!=NULL; } char u[260]; w2a(n,u,sizeof u); HMODULE W_GetModuleHandleA(LPCSTR); *m=W_GetModuleHandleA(u); return *m!=NULL; }
/* ---- condition variables / SRW locks (4-byte lazily-allocated objects) ---- */
static pthread_mutex_t lazy_mx=PTHREAD_MUTEX_INITIALIZER;
static void *lazy(volatile void **slot,size_t sz,void (*init)(void*)){ if(!*slot){ pthread_mutex_lock(&lazy_mx); if(!*slot){ void *p=calloc(1,sz); init(p); *slot=p; } pthread_mutex_unlock(&lazy_mx); } return (void*)*slot; }
static void cv_init(void *p){ pthread_cond_init((pthread_cond_t*)p,NULL); } static void mx_init(void *p){ pthread_mutex_init((pthread_mutex_t*)p,NULL); }
void WINAPI W_InitializeConditionVariable(volatile void **cv){ *cv=NULL; }
void WINAPI W_WakeConditionVariable(volatile void **cv){ pthread_cond_signal((pthread_cond_t*)lazy(cv,sizeof(pthread_cond_t),cv_init)); }
void WINAPI W_WakeAllConditionVariable(volatile void **cv){ pthread_cond_broadcast((pthread_cond_t*)lazy(cv,sizeof(pthread_cond_t),cv_init)); }
BOOL WINAPI W_SleepConditionVariableCS(volatile void **cv,void *cs,DWORD ms){ pthread_cond_t *c=lazy(cv,sizeof(pthread_cond_t),cv_init); if(ms==INFINITE){ pthread_cond_wait(c,(pthread_mutex_t*)cs); return 1; } struct timespec dl; clock_gettime(CLOCK_REALTIME,&dl); dl.tv_sec+=ms/1000; dl.tv_nsec+=(ms%1000)*1000000L; if(dl.tv_nsec>=1000000000L){ dl.tv_sec++; dl.tv_nsec-=1000000000L; } if(pthread_cond_timedwait(c,(pthread_mutex_t*)cs,&dl)==ETIMEDOUT){ set_last_error(1460); return 0; } return 1; }
void WINAPI W_AcquireSRWLockExclusive(volatile void **l){ pthread_mutex_lock((pthread_mutex_t*)lazy(l,sizeof(pthread_mutex_t),mx_init)); }
void WINAPI W_ReleaseSRWLockExclusive(volatile void **l){ pthread_mutex_unlock((pthread_mutex_t*)lazy(l,sizeof(pthread_mutex_t),mx_init)); }
/* ---- registry: nothing registered ---- */
DWORD WINAPI W_RegOpenKeyExA(HANDLE k,LPCSTR s,DWORD o,DWORD sam,HANDLE *r){ return 2; } DWORD WINAPI W_RegQueryValueExA(HANDLE k,LPCSTR n,DWORD *r,DWORD *t,BYTE *d,DWORD *sz){ return 2; } DWORD WINAPI W_RegCloseKey(HANDLE k){ return 0; }
/* ---- Crypt: real MD5 / SHA-1 / SHA-256 ---- */
struct hobj { int alg; uint32_t h[8]; uint64_t len; uint8_t buf[64]; int bl; };
#define ROR(x,n) (((x)>>(n))|((x)<<(32-(n)))) 
#define ROL(x,n) (((x)<<(n))|((x)>>(32-(n))))
static const uint32_t K256[64]={0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2};
static const uint32_t MD5K[64]={0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};
static const int MD5S[64]={7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21};
static void block(struct hobj *o,const uint8_t *p){
  if(o->alg==2){ uint32_t w[64],a,b,c,d,e,f,g,h; for(int i=0;i<16;i++) w[i]=p[4*i]<<24|p[4*i+1]<<16|p[4*i+2]<<8|p[4*i+3]; for(int i=16;i<64;i++){ uint32_t s0=ROR(w[i-15],7)^ROR(w[i-15],18)^(w[i-15]>>3), s1=ROR(w[i-2],17)^ROR(w[i-2],19)^(w[i-2]>>10); w[i]=w[i-16]+s0+w[i-7]+s1; }
    a=o->h[0];b=o->h[1];c=o->h[2];d=o->h[3];e=o->h[4];f=o->h[5];g=o->h[6];h=o->h[7];
    for(int i=0;i<64;i++){ uint32_t S1=ROR(e,6)^ROR(e,11)^ROR(e,25),ch=(e&f)^(~e&g),t1=h+S1+ch+K256[i]+w[i],S0=ROR(a,2)^ROR(a,13)^ROR(a,22),mj=(a&b)^(a&c)^(b&c),t2=S0+mj; h=g;g=f;f=e;e=d+t1;d=c;c=b;b=a;a=t1+t2; }
    o->h[0]+=a;o->h[1]+=b;o->h[2]+=c;o->h[3]+=d;o->h[4]+=e;o->h[5]+=f;o->h[6]+=g;o->h[7]+=h; }
  else if(o->alg==1){ uint32_t w[80],a=o->h[0],b=o->h[1],c=o->h[2],d=o->h[3],e=o->h[4]; for(int i=0;i<16;i++) w[i]=p[4*i]<<24|p[4*i+1]<<16|p[4*i+2]<<8|p[4*i+3]; for(int i=16;i<80;i++) w[i]=ROL(w[i-3]^w[i-8]^w[i-14]^w[i-16],1);
    for(int i=0;i<80;i++){ uint32_t f,k; if(i<20){f=(b&c)|(~b&d);k=0x5A827999;} else if(i<40){f=b^c^d;k=0x6ED9EBA1;} else if(i<60){f=(b&c)|(b&d)|(c&d);k=0x8F1BBCDC;} else {f=b^c^d;k=0xCA62C1D6;} uint32_t t=ROL(a,5)+f+e+k+w[i]; e=d;d=c;c=ROL(b,30);b=a;a=t; }
    o->h[0]+=a;o->h[1]+=b;o->h[2]+=c;o->h[3]+=d;o->h[4]+=e; }
  else { uint32_t m[16],a=o->h[0],b=o->h[1],c=o->h[2],d=o->h[3]; for(int i=0;i<16;i++) m[i]=p[4*i]|p[4*i+1]<<8|p[4*i+2]<<16|(uint32_t)p[4*i+3]<<24;
    for(int i=0;i<64;i++){ uint32_t f; int g; if(i<16){f=(b&c)|(~b&d);g=i;} else if(i<32){f=(d&b)|(~d&c);g=(5*i+1)&15;} else if(i<48){f=b^c^d;g=(3*i+5)&15;} else {f=c^(b|~d);g=(7*i)&15;} f=f+a+MD5K[i]+m[g]; a=d;d=c;c=b;b=b+ROL(f,MD5S[i]); }
    o->h[0]+=a;o->h[1]+=b;o->h[2]+=c;o->h[3]+=d; } }
static void hinit(struct hobj *o,int alg){ memset(o,0,sizeof *o); o->alg=alg; if(alg==2){ static const uint32_t i[8]={0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19}; memcpy(o->h,i,32); } else if(alg==1){ static const uint32_t i[5]={0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476,0xC3D2E1F0}; memcpy(o->h,i,20); } else { o->h[0]=0x67452301; o->h[1]=0xefcdab89; o->h[2]=0x98badcfe; o->h[3]=0x10325476; } }
static void hupd(struct hobj *o,const uint8_t *d,DWORD n){ o->len+=n; while(n){ DWORD c=64-o->bl<n?64-o->bl:n; memcpy(o->buf+o->bl,d,c); o->bl+=c; d+=c; n-=c; if(o->bl==64){ block(o,o->buf); o->bl=0; } } }
static int hfinal(struct hobj *src,uint8_t *out){ struct hobj o=*src; uint64_t bits=o.len*8; uint8_t pad=0x80; hupd(&o,&pad,1); uint8_t z=0; while(o.bl!=56) hupd(&o,&z,1); uint8_t lb[8]; for(int i=0;i<8;i++) lb[i]=o.alg==0?(bits>>(8*i)):(bits>>(56-8*i)); hupd(&o,lb,8);
  int words=o.alg==2?8:o.alg==1?5:4; for(int i=0;i<words;i++) for(int k=0;k<4;k++) out[4*i+k]=o.alg==0?(o.h[i]>>(8*k)):(o.h[i]>>(24-8*k)); return words*4; }
BOOL WINAPI W_CryptAcquireContextA(HANDLE *p,LPCSTR c,LPCSTR pr,DWORD t,DWORD f){ *p=(HANDLE)0x1; return 1; } BOOL WINAPI W_CryptReleaseContext(HANDLE p,DWORD f){ return 1; }
BOOL WINAPI W_CryptCreateHash(HANDLE p,DWORD alg,HANDLE key,DWORD f,HANDLE *h){ int a=alg==0x800C?2:alg==0x8004?1:alg==0x8003?0:-1; if(a<0){ set_last_error(0x80090008); return 0; } struct hobj *o=malloc(sizeof *o); hinit(o,a); *h=o; return 1; }
BOOL WINAPI W_CryptHashData(HANDLE h,const BYTE *d,DWORD n,DWORD f){ hupd((struct hobj*)h,d,n); return 1; }
BOOL WINAPI W_CryptGetHashParam(HANDLE h,DWORD p,BYTE *d,DWORD *n,DWORD f){ struct hobj *o=h; int sz=o->alg==2?32:o->alg==1?20:16; if(p==4){ if(d) *(DWORD*)d=sz; if(n)*n=4; return 1; } if(p==2){ if(!d||*n<(DWORD)sz){ *n=sz; if(d) set_last_error(234); return d==NULL; } hfinal(o,d); *n=sz; return 1; } if(p==1){ if(d) *(DWORD*)d=o->alg==2?0x800C:o->alg==1?0x8004:0x8003; if(n)*n=4; return 1; } return 0; }
BOOL WINAPI W_CryptDestroyHash(HANDLE h){ free(h); return 1; }
/* ---- dwmapi ---- */
HRESULT WINAPI W_DwmIsCompositionEnabled(BOOL *e){ *e=0; return 0; } HRESULT WINAPI W_DwmGetColorizationColor(DWORD *c,BOOL *o){ *c=0xFF404040; *o=0; return 0; } HRESULT WINAPI W_DwmEnableBlurBehindWindow(HWND h,const void *b){ return 0; }
