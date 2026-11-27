/* Native-Linux startup: map the original image regions at their original addresses, set up TEB, imports, code-pointer patches, run original entry. */
#include "win.h"
#include "layout.h"
#include <sys/mman.h>
#include <unistd.h>
extern unsigned char lt_blob_hdr[], lt_blob_hdr_end[], lt_blob_text[], lt_blob_text_end[], lt_blob_data[], lt_blob_data_end[], lt_blob_rsrc[], lt_blob_rsrc_end[];
extern unsigned lt_patch_tab[]; extern void lt_entry(void);
struct iat { unsigned slot; const char *dll; const char *name; unsigned ord; }; extern struct iat lt_iat_tab[]; extern int lt_iat_n;
void *lt_resolve_import(const char *dll,const char *name,unsigned ord);
void lt_install_signals(void); extern char lt_cmdline[2048];
static void map_region(unsigned va,unsigned char *src,unsigned char *end,unsigned size){
  void *p=mmap((void*)va,size,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED_NOREPLACE,-1,0);
  if(p!=(void*)va){ perror("mmap original image region"); fprintf(stderr,"cannot map 0x%x (is the address range free?)\n",va); exit(1); }
  memcpy(p,src,end-src); }
typedef struct RMode { DWORD hw; char dll[256]; char name[128]; char desc[128]; DWORD w,h,bpp; struct RMode *next; } RMode;
void *WINAPI W_GetProcAddress(HMODULE,LPCSTR); HMODULE WINAPI W_LoadLibraryA(LPCSTR);
static int test_ren(const char *path){
  int local; lt_thread_init(&local);
  HMODULE m=W_LoadLibraryA(path); if(!m){ fprintf(stderr,"cannot load %s\n",path); return 1; }
  RMode *(*gsm)(void)=W_GetProcAddress(m,"GetSupportedModes"); void (*fml)(RMode*)=W_GetProcAddress(m,"FreeModeList"); if(!gsm){ fprintf(stderr,"no GetSupportedModes\n"); return 1; }
  RMode *l=gsm(); int n=0; for(RMode *p=l;p;p=p->next,n++) printf("mode %d: %ux%ux%u hw=%u '%s' (%s)\n",n,p->w,p->h,p->bpp,p->hw,p->name,p->desc);
  printf("%d modes\n",n); if(fml) fml(l); return 0; }
int main(int argc,char **argv){
  if(argc>2&&!strcmp(argv[1],"--test-ren")) return test_ren(argv[2]);
  map_region(0x400000,lt_blob_hdr,lt_blob_hdr_end,0x1000);
  map_region(LT_TEXT_VA,lt_blob_text,lt_blob_text_end,LT_TEXT_SZ);
  map_region(LT_DATA_VA,lt_blob_data,lt_blob_data_end,LT_DATA_SZ);
  map_region(LT_RSRC_VA,lt_blob_rsrc,lt_blob_rsrc_end,LT_RSRC_SZ);
  int local; lt_thread_init(&local); lt_install_signals();
  size_t n=snprintf(lt_cmdline,sizeof lt_cmdline,"C:\\lithtech.exe"); for(int i=1;i<argc&&n<sizeof lt_cmdline-4;i++){ int sp=strchr(argv[i],' ')!=NULL; n+=snprintf(lt_cmdline+n,sizeof lt_cmdline-n,sp?" \"%s\"":" %s",argv[i]); }
  for(int i=0;i<lt_iat_n;i++) *(void**)lt_iat_tab[i].slot=lt_resolve_import(lt_iat_tab[i].dll,lt_iat_tab[i].name,lt_iat_tab[i].ord);
  for(unsigned *p=lt_patch_tab;p[0];p+=2) *(unsigned*)p[0]=p[1];snprintf(lt_cmdline + strlen(lt_cmdline), sizeof(lt_cmdline) - strlen(lt_cmdline), " -exec bindings.cfg");
  lt_entry(); return 0; }
