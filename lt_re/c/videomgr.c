/* lithtech.exe decompilation - module videomgr */
#include "ghidra_types.h"

/* 004a1600 size=47 */

/* repo: runtime/kernel/src/sys/win/videomgr.cpp */

void __thiscall videomgr_4a1600(void *this,int *param_1)

{
  if (*(void **)((int)this + 0x10) != (void *)0x0) {
    FUN_00468500(*(void **)((int)this + 0x10),(int)this + 0x14);
  }
  *(int **)((int)this + 0x10) = param_1;
  if (param_1 != (int *)0x0) {
    FUN_00446060(param_1,(int)this + 0x14);
  }
  return;
}


