/* lithtech.exe decompilation - module LayoutDB */
#include "ghidra_types.h"

/* 00459060 size=97 */

/* repo: FEAR/ClientShellDLL/LayoutDB.cpp */

bool __thiscall LayoutDB_459060(void *this,byte *param_1)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  void *unaff_retaddr;
  
  iVar2 = FUN_004570e0(param_1);
  if (iVar2 == 0) {
    return false;
  }
  (**(code **)(*(int *)param_1 + 8))((int *)((int)this + 0x208),4);
  iVar2 = *(int *)((int)this + 0x208);
  if ((((iVar2 == 9) || (iVar2 == 10)) || (iVar2 == 0xb)) || (iVar2 == 0xc)) {
    bVar1 = FUN_0045a9b0(unaff_retaddr,(int *)param_1);
    return CONCAT31(extraout_var,bVar1) != 0;
  }
  return false;
}


