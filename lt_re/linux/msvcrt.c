/* msvcrt.dll compatibility (cdecl). Windows wchar_t is 16-bit and FILE/_iob differ from glibc, so those are translated. */
#define _GNU_SOURCE
#include "win.h"
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <wctype.h>
#define CD __attribute__((force_align_arg_pointer))
/* ---- stdio: fake Windows _iob (32-byte FILE slots) mapped back to stdin/out/err ---- */
static char fake_iob[3*32] __attribute__((aligned(16)));
CD void *W___p__iob(void){ return fake_iob; }
static FILE *F(void *f){ if((char*)f>=fake_iob&&(char*)f<fake_iob+sizeof fake_iob){ int i=((char*)f-fake_iob)/32; return i==0?stdin:i==1?stdout:stderr; } return (FILE*)f; }
CD void *W_fopen(const char *p,const char *m){ char u[1024]; win2unix(p,u,sizeof u); FILE *f=fopen(u,m); if(!f&&strchr(m,'w')==NULL&&strchr(m,'a')==NULL) return NULL; return f; }
CD int W_fclose(void *f){ return fclose(F(f)); } CD int W_fflush(void *f){ return fflush(f?F(f):NULL); }
CD size_t W_fread(void *b,size_t s,size_t n,void *f){ return fread(b,s,n,F(f)); } CD size_t W_fwrite(const void *b,size_t s,size_t n,void *f){ return fwrite(b,s,n,F(f)); }
CD int W_fseek(void *f,long o,int w){ return fseek(F(f),o,w); } CD long W_ftell(void *f){ return ftell(F(f)); }
CD int W_fputc(int c,void *f){ return fputc(c,F(f)); } CD int W_fputs(const char *s,void *f){ return fputs(s,F(f)); }
CD int W_getc(void *f){ return getc(F(f)); } CD int W_ungetc(int c,void *f){ return ungetc(c,F(f)); }
CD int W_setvbuf(void *f,char *b,int m,size_t n){ return setvbuf(F(f),b,m,n); }
CD int W_fprintf(void *f,const char *fmt,...){ va_list a; va_start(a,fmt); int r=vfprintf(F(f),fmt,a); va_end(a); return r; }
CD int W_vfprintf(void *f,const char *fmt,va_list a){ return vfprintf(F(f),fmt,a); }
CD int W__snprintf_s(char *b,size_t sz,size_t cnt,const char *fmt,...){ va_list a; va_start(a,fmt); int r=vsnprintf(b,cnt<sz?cnt+1:sz,fmt,a); va_end(a); return r; }
CD int W__vsnprintf_s(char *b,size_t sz,size_t cnt,const char *fmt,va_list a){ return vsnprintf(b,cnt<sz?cnt+1:sz,fmt,a); }
/* ---- io.h style fds ---- */
CD int W__close(int fd){ return close(fd); } CD int W__read(int fd,void *b,unsigned n){ return read(fd,b,n); } CD int W__write(int fd,const void *b,unsigned n){ return write(fd,b,n); }
CD long long W__lseeki64(int fd,long long o,int w){ return lseek64(fd,o,w); } CD long long W__telli64(int fd){ return lseek64(fd,0,SEEK_CUR); }
CD int W__fileno(void *f){ return fileno(F(f)); } CD void *W__fdopen(int fd,const char *m){ return fdopen(fd,m); }
CD intptr_t W__get_osfhandle(int fd){ return fd; }
CD int W__fstat(int fd,void *buf){ struct stat st; if(fstat(fd,&st)) return -1; memset(buf,0,64); ((uint32_t*)buf)[0]=st.st_dev; ((uint16_t*)buf)[3]=st.st_mode; ((uint32_t*)buf)[5]=(uint32_t)st.st_size; return 0; }
/* ---- memory / string ---- */
CD void *W_malloc(size_t n){ return malloc(n); } CD void *W_calloc(size_t a,size_t b){ return calloc(a,b); } CD void *W_realloc(void *p,size_t n){ return realloc(p,n); } CD void W_free(void *p){ free(p); }
CD void *W_memchr(const void *p,int c,size_t n){ return memchr(p,c,n); } CD int W_memcmp(const void *a,const void *b,size_t n){ return memcmp(a,b,n); } CD void *W_memcpy(void *d,const void *s,size_t n){ return memcpy(d,s,n); } CD void *W_memmove(void *d,const void *s,size_t n){ return memmove(d,s,n); } CD void *W_memset(void *d,int c,size_t n){ return memset(d,c,n); }
CD char *W_strchr(const char *s,int c){ return strchr(s,c); } CD int W_strcmp(const char *a,const char *b){ return strcmp(a,b); } CD int W_strcoll(const char *a,const char *b){ return strcoll(a,b); } CD char *W_strcpy(char *d,const char *s){ return strcpy(d,s); }
CD size_t W_strlen(const char *s){ return strlen(s); } CD int W_strncmp(const char *a,const char *b,size_t n){ return strncmp(a,b,n); } CD char *W_strncpy(char *d,const char *s,size_t n){ return strncpy(d,s,n); }
CD char *W_strrchr(const char *s,int c){ return strrchr(s,c); } CD char *W_strstr(const char *a,const char *b){ return strstr(a,b); } CD char *W_strerror(int e){ return strerror(e); } CD size_t W_strxfrm(char *d,const char *s,size_t n){ return strxfrm(d,s,n); }
CD long W_strtol(const char *s,char **e,int b){ return strtol(s,e,b); } CD unsigned long W_strtoul(const char *s,char **e,int b){ return strtoul(s,e,b); } CD double W_atof(const char *s){ return atof(s); } CD int W_atoi(const char *s){ return atoi(s); }
CD int W__stricmp(const char *a,const char *b){ return strcasecmp(a,b); } CD int W__strnicmp(const char *a,const char *b,size_t n){ return strncasecmp(a,b,n); }
CD int W_strncpy_s(char *d,size_t dn,const char *s,size_t n){ if(!d||!dn) return 22; size_t l=strnlen(s,n==(size_t)-1?dn:n); if(l>=dn){ d[0]=0; return 34; } memcpy(d,s,l); d[l]=0; return 0; }
CD int W_isdigit(int c){ return isdigit(c); } CD int W_islower(int c){ return islower(c); } CD int W_isspace(int c){ return isspace(c); } CD int W_isupper(int c){ return isupper(c); } CD int W_isxdigit(int c){ return isxdigit(c); } CD int W_tolower(int c){ return tolower(c); }
CD char *W_getenv(const char *n){ return getenv(n); } CD void W_abort(void){ abort(); } CD int *W__errno(void){ return &errno; }
CD void W_qsort(void *b,size_t n,size_t s,int (*c)(const void*,const void*)){ qsort(b,n,s,c); }
CD double W_exp(double x){ return exp(x); } CD double W_tan(double x){ return tan(x); } CD double W_ldexp(double x,int e){ return ldexp(x,e); }
CD char *W_setlocale(int cat,const char *l){ return "C"; }
static struct lconv mslc;
CD void *W_localeconv(void){ static struct { char *dp,*ts,*g,*id,*cs,*mdp,*mts,*mg,*ps,*ns; char idg,fd,pcs,psp,ncs,nsp,pp,np; } lc={".","","","","","","","","","",127,127,127,127,127,127,127,127}; (void)mslc; return &lc; }
CD size_t W_strftime(char *b,size_t n,const char *f,const struct tm *t){ return strftime(b,n,f,t); }
CD int W___p___mb_cur_max_dummy(void){ return 1; } CD int *W___p___mb_cur_max(void){ static int one=1; return &one; }
CD void *W___setusermatherr(void *f){ return NULL; }
CD void W__amsg_exit(int n){ lt_log("_amsg_exit(%d)",n); fflush(NULL); _exit(255); }
CD void W__initterm(void (**s)(void),void (**e)(void)){ for(;s<e;s++) if(*s) (*s)(); }
static pthread_mutex_t crtlocks[64]; static int crtinit;
CD void W__lock(int n){ if(!crtinit){ for(int i=0;i<64;i++){ pthread_mutexattr_t a; pthread_mutexattr_init(&a); pthread_mutexattr_settype(&a,PTHREAD_MUTEX_RECURSIVE); pthread_mutex_init(&crtlocks[i],&a); } crtinit=1; } pthread_mutex_lock(&crtlocks[n&63]); }
CD void W__unlock(int n){ pthread_mutex_unlock(&crtlocks[n&63]); }
CD void W__findclose_dummy(void){} CD int W__findclose(intptr_t h){ return 0; }
/* ---- wide (UTF-16) helpers ---- */
static void w2u(const WCHAR *w,char *o,size_t n){ size_t k=0; for(;*w&&k+4<n;w++){ unsigned c=*w; if(c>=0xD800&&c<0xDC00&&w[1]>=0xDC00&&w[1]<0xE000){ c=0x10000+((c-0xD800)<<10)+(w[1]-0xDC00); w++; } if(c<0x80) o[k++]=c; else if(c<0x800){ o[k++]=0xC0|(c>>6); o[k++]=0x80|(c&63); } else if(c<0x10000){ o[k++]=0xE0|(c>>12); o[k++]=0x80|((c>>6)&63); o[k++]=0x80|(c&63); } else { o[k++]=0xF0|(c>>18); o[k++]=0x80|((c>>12)&63); o[k++]=0x80|((c>>6)&63); o[k++]=0x80|(c&63); } } o[k]=0; }
static void u2w(const char *s,WCHAR *o,size_t n){ size_t k=0; while(*s&&k+2<n){ unsigned char c=*s; unsigned cp; int l; if(c<0x80){cp=c;l=1;} else if((c>>5)==6){cp=((c&31)<<6)|(s[1]&63);l=2;} else if((c>>4)==14){cp=((c&15)<<12)|((s[1]&63)<<6)|(s[2]&63);l=3;} else {cp=((c&7)<<18)|((s[1]&63)<<12)|((s[2]&63)<<6)|(s[3]&63);l=4;} s+=l; if(cp>=0x10000){ cp-=0x10000; o[k++]=0xD800+(cp>>10); o[k++]=0xDC00+(cp&0x3ff);} else o[k++]=cp; } o[k]=0; }
CD size_t W_wcslen(const WCHAR *s){ size_t n=0; while(s[n]) n++; return n; }
CD WCHAR *W_wcscpy(WCHAR *d,const WCHAR *s){ WCHAR *r=d; while((*d++=*s++)); return r; }
CD WCHAR *W_wcscat(WCHAR *d,const WCHAR *s){ WCHAR *r=d; while(*d) d++; while((*d++=*s++)); return r; }
CD int W_wcscmp(const WCHAR *a,const WCHAR *b){ while(*a&&*a==*b){ a++; b++; } return (int)*a-(int)*b; }
CD int W_wcscoll(const WCHAR *a,const WCHAR *b){ return W_wcscmp(a,b); } CD size_t W_wcsxfrm(WCHAR *d,const WCHAR *s,size_t n){ size_t l=W_wcslen(s); if(d&&n){ size_t c=l<n-1?l:n-1; memcpy(d,s,c*2); d[c]=0; } return l; }
CD unsigned W_towlower(unsigned c){ return c<128?tolower(c):c; } CD unsigned W_towupper(unsigned c){ return c<128?toupper(c):c; } CD int W_iswctype(unsigned c,unsigned t){ if(c>255) return 0; int r=0; if((t&1)&&isupper(c)) r=1; if((t&2)&&islower(c)) r=1; if((t&4)&&isdigit(c)) r=1; if((t&8)&&isspace(c)) r=1; if((t&0x10)&&ispunct(c)) r=1; if((t&0x20)&&iscntrl(c)) r=1; if((t&0x80)&&isxdigit(c)) r=1; if((t&0x100)&&isalpha(c)) r=1; return r; }
CD size_t W_wcsftime(WCHAR *b,size_t n,const WCHAR *f,const struct tm *t){ char fm[256],o[512]; w2u(f,fm,sizeof fm); size_t r=strftime(o,sizeof o,fm,t); u2w(o,b,n); return r; }
CD void *W__wfopen(const WCHAR *p,const WCHAR *m){ char a[1024],b[16]; w2u(p,a,sizeof a); w2u(m,b,sizeof b); return W_fopen(a,b); }
CD int W__wopen(const WCHAR *p,int fl,...){ char a[1024]; w2u(p,a,sizeof a); char u[1024]; win2unix(a,u,sizeof u); int f=(fl&3)==0?O_RDONLY:(fl&3)==1?O_WRONLY:O_RDWR; if(fl&0x100) f|=O_CREAT; if(fl&0x200) f|=O_TRUNC; if(fl&0x400) f|=O_EXCL; if(fl&8) f|=O_APPEND; return open(u,f,0666); }
CD int W__wmkdir(const WCHAR *p){ char a[1024],u[1024]; w2u(p,a,sizeof a); win2unix(a,u,sizeof u); return mkdir(u,0777); }
CD int W__wchdir(const WCHAR *p){ char a[1024],u[1024]; w2u(p,a,sizeof a); win2unix(a,u,sizeof u); return chdir(u); }
CD int W__wchmod(const WCHAR *p,int m){ return 0; }
CD WCHAR *W__wgetcwd(WCHAR *b,int n){ char c[1024]; if(!getcwd(c,sizeof c)) return NULL; char w[1100]; snprintf(w,sizeof w,"Z:%s",c); for(char*q=w;*q;q++) if(*q=='/') *q='\\'; if(!b){ b=malloc(2*(strlen(w)+1)); n=strlen(w)+1; } u2w(w,b,n); return b; }
CD WCHAR *W__wfullpath(WCHAR *o,const WCHAR *p,size_t n){ char a[1024],c[1024]; w2u(p,a,sizeof a); getcwd(c,sizeof c); char w[2200]; if(a[1]==':') snprintf(w,sizeof w,"%s",a); else snprintf(w,sizeof w,"Z:%s/%s",c,a); for(char*q=w;*q;q++) if(*q=='/') *q='\\'; if(!o){ o=malloc(2*(strlen(w)+1)); n=strlen(w)+1; } u2w(w,o,n); return o; }
CD int W__wstat(const WCHAR *p,void *buf){ char a[1024],u[1024]; w2u(p,a,sizeof a); win2unix(a,u,sizeof u); struct stat st; if(stat(u,&st)) return -1; memset(buf,0,64); ((uint16_t*)buf)[3]=st.st_mode; ((uint32_t*)buf)[5]=(uint32_t)st.st_size; return 0; }
CD intptr_t W__wfindfirst(const WCHAR *p,void *d){ errno=2; return -1; } CD int W__wfindnext(intptr_t h,void *d){ return -1; }
CD int W__wutime(const WCHAR *p,void *t){ return 0; }
