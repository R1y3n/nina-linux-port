/* Startup for the statically translated build: fill the import table, patch code pointers stored in data, run the original entry point. */
#include <windows.h>
extern unsigned lt_patch_tab[] __asm__("_lt_patch_tab");
extern void lt_iat_init(void);
extern void lt_entry(void);
void lt_start(void){
  lt_iat_init();
  for(unsigned *p=lt_patch_tab; p[0]; p+=2) *(unsigned*)p[0]=p[1];
  lt_entry();
  ExitProcess(0);
}
