/* lithtech.exe decompilation - module localdriver */
#include "ghidra_types.h"

/* 004482b0 size=52 */

/* repo: runtime/kernel/net/src/localdriver.cpp */

void __thiscall localdriver_4482b0(void *this,int param_1)

{
  FUN_004317e0();
  netmgr_466010(*(void **)((int)this + 0x48),param_1);
  (**(code **)(*(int *)this + 8))();
  return;
}


