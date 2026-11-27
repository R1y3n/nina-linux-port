/* kernel32: files, paths, directory search, time conversion */
#include "win.h"
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <fnmatch.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <time.h>
#include <sys/time.h>
/* ---------- path mapping ---------- */
static int ci_lookup(char *path){   /* fix case of each component in place; returns 1 if found */
  if(access(path,F_OK)==0) return 1;
  char *p=path; char built[1024]; size_t bl=0; built[0]=0;
  if(*p=='/'){ built[0]='/'; built[1]=0; bl=1; p++; }
  while(*p){
    char comp[256]; size_t n=0; while(*p&&*p!='/'&&n<255) comp[n++]=*p++; comp[n]=0; while(*p=='/') p++;
    if(!n) continue;
    char dir[1024]; snprintf(dir,sizeof dir,"%s",built[0]?built:"."); DIR *d=opendir(dir); int ok=0;
    if(d){ struct dirent *e; while((e=readdir(d))){ if(!strcasecmp(e->d_name,comp)){ strcpy(comp,e->d_name); ok=1; break; } } closedir(d);} 
    if(!ok){ /* append rest as is */ size_t k=strlen(built); if(k&&built[k-1]!='/') strcat(built,"/"); strcat(built,comp); if(*p){strcat(built,"/"); strcat(built,p);} strcpy(path,built); return 0; }
    size_t k=strlen(built); if(k&&built[k-1]!='/') strcat(built,"/"); strcat(built,comp);
  }
  strcpy(path,built[0]?built:"."); return 1;
}
char *win2unix(const char *w,char *out,size_t n){
  char tmp[1024]; size_t i=0; const char *s=w;
  if(((s[0]>='A'&&s[0]<='Z')||(s[0]>='a'&&s[0]<='z'))&&s[1]==':') s+=2;
  for(;*s&&i<sizeof tmp-1;s++) tmp[i++]=(*s=='\\')?'/':*s; tmp[i]=0;
  if(!tmp[0]) strcpy(tmp,".");
  ci_lookup(tmp); snprintf(out,n,"%s",tmp); return out;
}
static void unix2win(const char *u,char *out,size_t n){ snprintf(out,n,"Z:%s",u); for(char*p=out;*p;p++) if(*p=='/') *p='\\'; }
/* ---------- time ---------- */
static void unix_to_ft(time_t t,long ns,FILETIME *f){ uint64_t v=((uint64_t)t+11644473600ULL)*10000000ULL+ns/100; f->lo=(DWORD)v; f->hi=(DWORD)(v>>32); }
static time_t ft_to_unix(const FILETIME *f){ uint64_t v=((uint64_t)f->hi<<32)|f->lo; return (time_t)(v/10000000ULL-11644473600ULL); }
void WINAPI W_GetSystemTimeAsFileTime(FILETIME *f){ struct timespec ts; clock_gettime(CLOCK_REALTIME,&ts); unix_to_ft(ts.tv_sec,ts.tv_nsec,f); }
static void tm_to_st(struct tm *t,int ms,SYSTEMTIME *s){ s->y=t->tm_year+1900; s->mo=t->tm_mon+1; s->dow=t->tm_wday; s->d=t->tm_mday; s->h=t->tm_hour; s->mi=t->tm_min; s->s=t->tm_sec; s->ms=ms; }
void WINAPI W_GetSystemTime(SYSTEMTIME *s){ struct timeval tv; gettimeofday(&tv,0); struct tm t; gmtime_r(&tv.tv_sec,&t); tm_to_st(&t,tv.tv_usec/1000,s); }
void WINAPI W_GetLocalTime(SYSTEMTIME *s){ struct timeval tv; gettimeofday(&tv,0); struct tm t; localtime_r(&tv.tv_sec,&t); tm_to_st(&t,tv.tv_usec/1000,s); }
BOOL WINAPI W_FileTimeToSystemTime(const FILETIME *f,SYSTEMTIME *s){ time_t t=ft_to_unix(f); struct tm tm; gmtime_r(&t,&tm); tm_to_st(&tm,((((uint64_t)f->hi<<32)|f->lo)/10000)%1000,s); return 1; }
BOOL WINAPI W_FileTimeToLocalFileTime(const FILETIME *f,FILETIME *o){ time_t t=ft_to_unix(f); struct tm tm; localtime_r(&t,&tm); uint64_t v=(((uint64_t)f->hi<<32)|f->lo)+(uint64_t)tm.tm_gmtoff*10000000ULL; o->lo=(DWORD)v; o->hi=(DWORD)(v>>32); return 1; }
BOOL WINAPI W_FileTimeToDosDateTime(const FILETIME *f,WORD *d,WORD *t){ time_t u=ft_to_unix(f); struct tm tm; gmtime_r(&u,&tm); if(tm.tm_year<80){return 0;} *d=((tm.tm_year-80)<<9)|((tm.tm_mon+1)<<5)|tm.tm_mday; *t=(tm.tm_hour<<11)|(tm.tm_min<<5)|(tm.tm_sec/2); return 1; }
typedef struct { LONG bias; WCHAR sn[32]; SYSTEMTIME sd; LONG sb; WCHAR dn[32]; SYSTEMTIME dd; LONG db; } TZI;
DWORD WINAPI W_GetTimeZoneInformation(TZI *z){ memset(z,0,sizeof *z); return 0; }
DWORD WINAPI W_GetTickCount(void){ struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts); return (DWORD)(ts.tv_sec*1000+ts.tv_nsec/1000000); }
DWORD WINAPI W_timeGetTime(void){ return W_GetTickCount(); }
BOOL WINAPI W_QueryPerformanceCounter(LONGLONG *v){ struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts); *v=(LONGLONG)ts.tv_sec*1000000000LL+ts.tv_nsec; return 1; }
BOOL WINAPI W_QueryPerformanceFrequency(LONGLONG *v){ *v=1000000000LL; return 1; }
void WINAPI W_Sleep(DWORD ms){ struct timespec ts={ms/1000,(ms%1000)*1000000L}; nanosleep(&ts,0); }
/* ---------- files ---------- */
static struct obj *getfile(HANDLE h){ struct obj *o=obj_get(h); return (o&&(o->type==H_FILE||o->type==H_STD))?o:NULL; }
HANDLE WINAPI W_CreateFileA(LPCSTR name,DWORD access,DWORD share,void *sa,DWORD disp,DWORD flags,HANDLE tmpl){
  char p[1024]; win2unix(name,p,sizeof p); if(getenv("LT_TRACE")) lt_log("CreateFile('%s' -> '%s' access=%08x disp=%u)",name,p,access,disp);
  int fl=0; int rd=(access&0x80000000u)!=0, wr=(access&0x40000000u)!=0; fl=(rd&&wr)?O_RDWR:wr?O_WRONLY:O_RDONLY;
  switch(disp){ case 1: fl|=O_CREAT|O_EXCL; break; case 2: fl|=O_CREAT|O_TRUNC; break; case 3: break; case 4: fl|=O_CREAT; break; case 5: fl|=O_TRUNC; break; }
  int fd=open(p,fl,0666);
  if(fd<0){ set_last_error(errno==ENOENT?(access&&disp==3?ERROR_FILE_NOT_FOUND:ERROR_FILE_NOT_FOUND):errno==EEXIST?ERROR_ALREADY_EXISTS:errno==EACCES?ERROR_ACCESS_DENIED:ERROR_PATH_NOT_FOUND); return INVALID_HANDLE_VALUE; }
  struct obj *o; HANDLE h=obj_new(H_FILE,&o); if(!h){ close(fd); return INVALID_HANDLE_VALUE; } o->fd=fd; set_last_error(0); return h; }
BOOL WINAPI W_CloseHandle(HANDLE h){
  struct obj *o=obj_get(h); if(!o){ set_last_error(ERROR_INVALID_HANDLE); return 0; }
  if(o->type==H_FILE&&o->fd>=0) close(o->fd);
  if(o->type==H_THREAD) { /* detach so resources are reclaimed when finished */ if(o->started) pthread_detach(o->th); }
  obj_free(h); return 1; }
BOOL WINAPI W_ReadFile(HANDLE h,void *buf,DWORD n,DWORD *got,void *ov){ struct obj *o=getfile(h); if(!o){ set_last_error(ERROR_INVALID_HANDLE); return 0; } ssize_t r=read(o->fd,buf,n); if(r<0){ set_last_error(ERROR_ACCESS_DENIED); if(got)*got=0; return 0; } if(got)*got=r; return 1; }
BOOL WINAPI W_WriteFile(HANDLE h,const void *buf,DWORD n,DWORD *wr,void *ov){ struct obj *o=getfile(h); if(!o){ set_last_error(ERROR_INVALID_HANDLE); return 0; } ssize_t r=write(o->fd,buf,n); if(r<0){ set_last_error(ERROR_ACCESS_DENIED); if(wr)*wr=0; return 0; } if(wr)*wr=r; return 1; }
DWORD WINAPI W_SetFilePointer(HANDLE h,LONG lo,LONG *hi,DWORD how){ struct obj *o=getfile(h); if(!o) return 0xFFFFFFFFu; off_t off=lo; if(hi) off=((off_t)*hi<<32)|(uint32_t)lo; off_t r=lseek(o->fd,off,how==0?SEEK_SET:how==1?SEEK_CUR:SEEK_END); if(r<0) return 0xFFFFFFFFu; if(hi)*hi=(LONG)(r>>32); return (DWORD)r; }
DWORD WINAPI W_GetFileSize(HANDLE h,DWORD *hi){ struct obj *o=getfile(h); struct stat st; if(!o||fstat(o->fd,&st)) return 0xFFFFFFFFu; if(hi)*hi=(DWORD)((uint64_t)st.st_size>>32); return (DWORD)st.st_size; }
BOOL WINAPI W_GetFileTime(HANDLE h,FILETIME *c,FILETIME *a,FILETIME *m){ struct obj *o=getfile(h); struct stat st; if(!o||fstat(o->fd,&st)) return 0; if(c)unix_to_ft(st.st_ctime,0,c); if(a)unix_to_ft(st.st_atime,0,a); if(m)unix_to_ft(st.st_mtime,0,m); return 1; }
BOOL WINAPI W_SetEndOfFile(HANDLE h){ struct obj *o=getfile(h); if(!o) return 0; off_t p=lseek(o->fd,0,SEEK_CUR); return ftruncate(o->fd,p)==0; }
BOOL WINAPI W_FlushFileBuffers(HANDLE h){ struct obj *o=getfile(h); if(!o) return 0; if(o->type==H_FILE) fsync(o->fd); return 1; }
DWORD WINAPI W_GetFileType(HANDLE h){ struct obj *o=getfile(h); if(!o) return 0; return isatty(o->fd)?2:(lseek(o->fd,0,SEEK_CUR)<0?3:1); }
static HANDLE std_h[3];
HANDLE WINAPI W_GetStdHandle(DWORD n){ int i=n==(DWORD)-10?0:n==(DWORD)-11?1:n==(DWORD)-12?2:-1; if(i<0) return INVALID_HANDLE_VALUE; if(!std_h[i]){ struct obj *o; std_h[i]=obj_new(H_STD,&o); o->fd=i; } return std_h[i]; }
BOOL WINAPI W_SetStdHandle(DWORD n,HANDLE h){ int i=n==(DWORD)-10?0:n==(DWORD)-11?1:n==(DWORD)-12?2:-1; if(i<0) return 0; std_h[i]=h; return 1; }
DWORD WINAPI W_SetHandleCount(DWORD n){ return n; }
/* ---------- directory search ---------- */
typedef struct { DWORD attr; FILETIME c,a,m; DWORD szhi,szlo,r0,r1; char name[260]; char alt[14]; } FINDDATA;
static void fill_find(FINDDATA *fd,const char *dir,const char *name){
  char p[1200]; snprintf(p,sizeof p,"%s/%s",dir,name); struct stat st; memset(fd,0,sizeof *fd);
  if(stat(p,&st)==0){ fd->attr=S_ISDIR(st.st_mode)?0x10:0x80; if(!(st.st_mode&0200)) fd->attr|=1; unix_to_ft(st.st_ctime,0,&fd->c); unix_to_ft(st.st_atime,0,&fd->a); unix_to_ft(st.st_mtime,0,&fd->m); fd->szhi=(DWORD)((uint64_t)st.st_size>>32); fd->szlo=(DWORD)st.st_size; }
  snprintf(fd->name,260,"%s",name); }
static int next_match(struct obj *o,FINDDATA *fd){ struct dirent *e; while((e=readdir(o->dir))){ if(!fnmatch(o->pat,e->d_name,FNM_CASEFOLD)||!strcmp(o->pat,"*.*")){ fill_find(fd,o->dirpath,e->d_name); return 1; } } return 0; }
HANDLE WINAPI W_FindFirstFileA(LPCSTR pat,FINDDATA *fd){
  char p[1024]; win2unix(pat,p,sizeof p); char *sl=strrchr(p,'/'); char dir[1024],mask[260];
  if(sl){ *sl=0; snprintf(dir,sizeof dir,"%s",p[0]?p:"/"); snprintf(mask,sizeof mask,"%s",sl+1); } else { strcpy(dir,"."); snprintf(mask,sizeof mask,"%s",p); }
  if(!strchr(mask,'*')&&!strchr(mask,'?')){ char full[1200]; snprintf(full,sizeof full,"%s/%s",dir,mask); struct stat st; if(stat(full,&st)){ set_last_error(ERROR_FILE_NOT_FOUND); return INVALID_HANDLE_VALUE; } }
  DIR *d=opendir(dir); if(!d){ set_last_error(ERROR_PATH_NOT_FOUND); return INVALID_HANDLE_VALUE; }
  struct obj *o; HANDLE h=obj_new(H_FIND,&o); o->dir=d; snprintf(o->pat,sizeof o->pat,"%s",mask); snprintf(o->dirpath,sizeof o->dirpath,"%s",dir);
  if(!next_match(o,fd)){ closedir(d); obj_free(h); set_last_error(ERROR_FILE_NOT_FOUND); return INVALID_HANDLE_VALUE; }
  return h; }
BOOL WINAPI W_FindNextFileA(HANDLE h,FINDDATA *fd){ struct obj *o=obj_get(h); if(!o||o->type!=H_FIND) return 0; if(!next_match(o,fd)){ set_last_error(ERROR_NO_MORE_FILES); return 0; } return 1; }
BOOL WINAPI W_FindClose(HANDLE h){ struct obj *o=obj_get(h); if(!o||o->type!=H_FIND) return 0; closedir(o->dir); obj_free(h); return 1; }
/* ---------- misc path/system ---------- */
DWORD WINAPI W_GetTempPathA(DWORD n,char *b){ const char *t="Z:\\tmp\\"; if(n>strlen(t)) strcpy(b,t); return strlen(t); }
DWORD WINAPI W_GetTempFileNameA(LPCSTR path,LPCSTR pre,DWORD u,char *out){ if(getenv("LT_TRACE")) lt_log("GetTempFileName(path='%s' prefix='%s' unique=%u)",path,pre,u); static int c; char p[1024]; char base[900]; win2unix(path,base,sizeof base); snprintf(p,sizeof p,"%s/%.3s%04x.tmp",base,pre,(unsigned)(getpid()+ ++c)&0xffff); int fd=open(p,O_CREAT|O_WRONLY,0666); if(fd>=0) close(fd); char w[1100]; unix2win(p,w,sizeof w); strcpy(out,w); return u?u:1; }
DWORD WINAPI W_GetFullPathNameA(LPCSTR f,DWORD n,char *buf,char **part){ char cwd[900],full[1100]; getcwd(cwd,sizeof cwd); const char *s=f; if(((s[0]|32)>='a'&&(s[0]|32)<='z')&&s[1]==':') snprintf(full,sizeof full,"%s",f); else { char u[1100]; unix2win(cwd,u,sizeof u); snprintf(full,sizeof full,"%s\\%s",u,f); } if(strlen(full)>=n) return strlen(full)+1; strcpy(buf,full); if(part){ char *b=strrchr(buf,'\\'); *part=b?b+1:buf; } return strlen(buf); }
DWORD WINAPI W_GetCurrentDirectoryA(DWORD n,char *b){ char cwd[900],w[1000]; getcwd(cwd,sizeof cwd); unix2win(cwd,w,sizeof w); if(strlen(w)>=n) return strlen(w)+1; strcpy(b,w); return strlen(w); }
BOOL WINAPI W_SetCurrentDirectoryA(LPCSTR d){ char p[1024]; win2unix(d,p,sizeof p); return chdir(p)==0; }
BOOL WINAPI W_GetDiskFreeSpaceA(LPCSTR root,DWORD *spc,DWORD *bps,DWORD *free_,DWORD *total){ struct statvfs s; if(statvfs(".",&s)) return 0; if(spc)*spc=8; if(bps)*bps=512; uint64_t b=(uint64_t)s.f_bsize*s.f_bavail/4096, t=(uint64_t)s.f_bsize*s.f_blocks/4096; if(free_)*free_=b>0xffffffffu?0xffffffffu:b; if(total)*total=t>0xffffffffu?0xffffffffu:t; return 1; }
DWORD WINAPI W_GetDriveTypeA(LPCSTR r){ return 3; }
const char *lt_module_path(HMODULE h);
DWORD WINAPI W_GetModuleFileNameA(HMODULE m,char *b,DWORD n){ const char *mp=lt_module_path(m); if(mp){ snprintf(b,n,"%s",mp); return strlen(b); } char p[900],w[1000]; ssize_t k=readlink("/proc/self/exe",p,sizeof p-1); if(k<0) k=0; p[k]=0; unix2win(p,w,sizeof w); snprintf(b,n,"%s",w); return strlen(b); }
char *WINAPI W_lstrcpyA(char *d,const char *s){ return strcpy(d,s); }
int WINAPI W_lstrlenA(const char *s){ return s?(int)strlen(s):0; }
void WINAPI W_OutputDebugStringA(const char *s){ fputs(s,stderr); }
void *WINAPI W_FindResourceA(HMODULE h,LPCSTR name,LPCSTR type); void *WINAPI W_LoadResource(HMODULE h,void *r);
static const char *msg_lookup(HMODULE h,DWORD id,int *uni){
  void *r=W_FindResourceA(h,(LPCSTR)1,(LPCSTR)11); if(!r) return NULL; uint8_t *d=W_LoadResource(h,r); if(!d) return NULL;
  uint32_t nb=*(uint32_t*)d; uint32_t *blk=(uint32_t*)(d+4);
  for(uint32_t b=0;b<nb;b++){ uint32_t lo=blk[b*3],hi=blk[b*3+1],off=blk[b*3+2]; if(id<lo||id>hi) continue; uint8_t *e=d+off; for(uint32_t k=lo;k<id;k++) e+=*(uint16_t*)e; *uni=*(uint16_t*)(e+2)&1; return (const char*)(e+4); }
  return NULL; }
DWORD WINAPI W_FormatMessageA(DWORD fl,const void *src,DWORD id,DWORD lang,char *buf,DWORD n,void *args){
  char text[4096]; int have=0;
  if(fl&0x400){ snprintf(text,sizeof text,"%s",(const char*)src); have=1; }
  if(!have&&(fl&0x800)){ int uni=0; const char *m=msg_lookup((HMODULE)src,id,&uni); if(m){ size_t o=0; if(uni){ const WCHAR *w=(const WCHAR*)m; for(;*w&&o<sizeof text-1;w++) text[o++]=*w<256?*w:'?'; } else for(;*m&&o<sizeof text-1;m++) text[o++]=*m; text[o]=0; have=1; } }
  if(!have){ if(fl&0x1000) snprintf(text,sizeof text,"Error %u",id); else { set_last_error(1814); return 0; } }
  char out[4096]; size_t o=0; const DWORD *av=(const DWORD*)args; int ignore=(fl&0x200)!=0;
  for(const char *p=text;*p&&o<sizeof out-16;){
    if(*p!='%'){ out[o++]=*p++; continue; }
    p++; if(*p=='%'){ out[o++]='%'; p++; continue; } if(*p=='n'){ out[o++]='\r'; out[o++]='\n'; p++; continue; } if(*p=='r'){ out[o++]='\r'; p++; continue; } if(*p=='t'){ out[o++]='\t'; p++; continue; }
    if(*p=='0'){ p++; continue; }
    if(*p>='1'&&*p<='9'){ int k=0; while(*p>='0'&&*p<='9') k=k*10+(*p++-'0'); char f[32]="s"; if(*p=='!'){ p++; int q=0; while(*p&&*p!='!'&&q<30) f[q++]=*p++; f[q]=0; if(*p=='!') p++; }
      if(ignore||!av){ o+=snprintf(out+o,sizeof out-o,"%%%d",k); continue; }
      char fm[40]; snprintf(fm,sizeof fm,"%%%s",f); char *conv=f+strlen(f)-1; if(*conv=='s'||*conv=='S') o+=snprintf(out+o,sizeof out-o,fm,(const char*)av[k-1]); else o+=snprintf(out+o,sizeof out-o,fm,av[k-1]); continue; }
    out[o++]='%'; }
  out[o]=0; size_t len=o;
  if(fl&0x100){ char *r=malloc(len+1); strcpy(r,out); *(char**)buf=r; return len; }
  if(len>=n){ set_last_error(ERROR_INSUFFICIENT_BUFFER); return 0; } strcpy(buf,out); return len; }
HANDLE WINAPI W_LocalFree(HANDLE h){ free(h); return NULL; }
BOOL WINAPI W_CreateDirectoryA(LPCSTR p,void *sa){ char u[1024]; win2unix(p,u,sizeof u); if(mkdir(u,0777)==0) return 1; set_last_error(errno==EEXIST?ERROR_ALREADY_EXISTS:ERROR_PATH_NOT_FOUND); return 0; }
DWORD WINAPI W_GetFileAttributesA(LPCSTR p){ char u[1024]; win2unix(p,u,sizeof u); struct stat st; if(stat(u,&st)){ set_last_error(ERROR_FILE_NOT_FOUND); return 0xFFFFFFFFu; } return S_ISDIR(st.st_mode)?0x10:0x80; }
BOOL WINAPI W_DeleteFileA(LPCSTR p){ char u[1024]; win2unix(p,u,sizeof u); if(unlink(u)==0) return 1; set_last_error(ERROR_FILE_NOT_FOUND); return 0; }
BOOL WINAPI W_CopyFileA(LPCSTR a,LPCSTR b,BOOL failIfExists){ char s[1024],d[1024]; win2unix(a,s,sizeof s); win2unix(b,d,sizeof d); if(failIfExists&&access(d,F_OK)==0){ set_last_error(ERROR_ALREADY_EXISTS); return 0; } int i=open(s,O_RDONLY); if(i<0){ set_last_error(ERROR_FILE_NOT_FOUND); return 0; } int o=open(d,O_WRONLY|O_CREAT|O_TRUNC,0666); if(o<0){ close(i); set_last_error(ERROR_ACCESS_DENIED); return 0; } char buf[65536]; ssize_t n; while((n=read(i,buf,sizeof buf))>0) if(write(o,buf,n)!=n) break; close(i); close(o); return 1; }

DWORD WINAPI W_GetWindowsDirectoryA(char *b,DWORD n){ const char *s="C:\\WINDOWS"; if(n<=strlen(s)) return strlen(s)+1; strcpy(b,s); return strlen(s); }
DWORD WINAPI W_GetSystemDirectoryA(char *b,DWORD n){ const char *s="C:\\WINDOWS\\SYSTEM32"; if(n<=strlen(s)) return strlen(s)+1; strcpy(b,s); return strlen(s); }
/* ini files */
static int ini_find(const char *file,const char *sec,const char *key,char *out,size_t on){
  char p[1024]; win2unix(file,p,sizeof p); FILE *f=fopen(p,"r"); if(!f) return 0; char line[1024]; int in=0,found=0;
  while(fgets(line,sizeof line,f)){ char *s=line; while(*s==' '||*s=='\t') s++; size_t l=strlen(s); while(l&&(s[l-1]=='\n'||s[l-1]=='\r')) s[--l]=0;
    if(*s=='['){ char *e=strchr(s,']'); in=e&&!strncasecmp(s+1,sec,e-s-1)&&strlen(sec)==(size_t)(e-s-1); continue; }
    if(in){ char *eq=strchr(s,'='); if(eq&&!strncasecmp(s,key,eq-s)&&strlen(key)==(size_t)(eq-s)){ snprintf(out,on,"%s",eq+1); found=1; break; } } }
  fclose(f); return found; }
DWORD WINAPI W_GetPrivateProfileStringA(LPCSTR sec,LPCSTR key,LPCSTR def,char *out,DWORD n,LPCSTR file){
  char v[1024]; if(key&&sec&&ini_find(file,sec,key,v,sizeof v)){ snprintf(out,n,"%s",v); return strlen(out); } snprintf(out,n,"%s",def?def:""); return strlen(out); }
UINT WINAPI W_GetPrivateProfileIntA(LPCSTR sec,LPCSTR key,int def,LPCSTR file){ char v[64]; if(ini_find(file,sec,key,v,sizeof v)) return atoi(v); return def; }
BOOL WINAPI W_WritePrivateProfileStringA(LPCSTR sec,LPCSTR key,LPCSTR val,LPCSTR file){ return 1; }
/* OpenFile (legacy): returns a handle usable with ReadFile/CloseHandle */
int WINAPI W_OpenFile(LPCSTR name,uint8_t *of,UINT style){ if(of){ memset(of,0,136); of[0]=136; snprintf((char*)of+8,128,"%s",name); }
  HANDLE h=W_CreateFileA(name,(style&2)?0xC0000000u:((style&1)?0x40000000u:0x80000000u),3,NULL,(style&0x1000)?2:3,0,NULL); if(h==INVALID_HANDLE_VALUE) return -1; return (int)(intptr_t)h; }

DWORD WINAPI W_GetModuleFileNameW(HMODULE m,WCHAR *b,DWORD n){ char a[1100]; DWORD r=W_GetModuleFileNameA(m,a,sizeof a); DWORD i=0; for(;a[i]&&i+1<n;i++) b[i]=(unsigned char)a[i]; if(n) b[i]=0; return i; }
