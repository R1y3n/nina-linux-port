/* lithtech.exe decompilation - module clientde_impl */
#include "ghidra_types.h"

/* 0040b640 size=95 */

/* repo: runtime/client/src/clientde_impl.cpp */

void __cdecl clientde_impl_40b640(int param_1)

{
  longlong lVar1;
  
  if (param_1 != 0) {
    lVar1 = __ftol();
    *(char *)(param_1 + 0x94) = (char)lVar1;
    lVar1 = __ftol();
    *(char *)(param_1 + 0x95) = (char)lVar1;
    lVar1 = __ftol();
    *(char *)(param_1 + 0x96) = (char)lVar1;
    lVar1 = __ftol();
    *(char *)(param_1 + 0x97) = (char)lVar1;
  }
  return;
}


