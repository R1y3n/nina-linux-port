/* lithtech.exe decompilation - module cloaderthread */
#include "ghidra_types.h"

/* 00417c30 size=126 */

/* repo: runtime/client/src/cloaderthread.cpp */

void __thiscall cloaderthread_417c30(void *this,int param_1)

{
  int iVar1;
  int local_24;
  int local_20 [2];
  uint local_18;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  FUN_0044df70((int)local_20);
  if (*(int *)((int)this + 0x60) != 0) {
    if (DAT_004e9874 != 0) {
      FUN_00436670((byte *)s_CLoaderThread__LoadModel__s__004d6924,*(undefined4 *)(param_1 + 0x1c));
    }
    iVar1 = clientmgr_48d890(*(int *)((int)this + 0x60),*(char **)(param_1 + 0x1c),param_1,&local_24
                            );
    local_18 = (uint)(iVar1 != 0);
    local_8 = local_24;
    local_10 = 0;
    local_c = param_1;
    FUN_0044e0a0((void *)((int)this + 0x2c),local_20);
  }
  return;
}


