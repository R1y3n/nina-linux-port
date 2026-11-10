/* lithtech.exe decompilation - module ModelsDB */
#include "ghidra_types.h"

/* 00457f40 size=299 */

/* repo: FEAR/Shared/ModelsDB.cpp */

undefined4 __thiscall ModelsDB_457f40(void *this,byte *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  int unaff_EBX;
  void *unaff_EBP;
  void *local_4;
  
  local_4 = this;
  iVar1 = FUN_004570e0(param_1);
  if (iVar1 != 0) {
    (**(code **)(*(int *)param_1 + 8))(&local_4,4);
    iVar1 = FUN_00455a50((void *)((int)this + 0x154),(int)unaff_EBP,*(int **)((int)this + 0x174));
    if (iVar1 != 0) {
      uVar2 = 0;
      if (*(int *)((int)this + 0x15c) != 0) {
        do {
          uVar2 = uVar2 + 1;
          *(undefined4 *)(*(int *)((int)this + 0x158) + -4 + uVar2 * 4) = 0;
        } while (uVar2 < *(uint *)((int)this + 0x15c));
      }
      local_4 = (void *)0x0;
      if (unaff_EBP != (void *)0x0) {
        do {
          puVar3 = (undefined4 *)(**(code **)(**(int **)((int)this + 0x174) + 4))(0x34);
          if (puVar3 == (undefined4 *)0x0) {
            return 0;
          }
          FUN_00450730(puVar3);
          *(undefined4 **)(*(int *)((int)this + 0x158) + unaff_EBX * 4) = puVar3;
          (**(code **)(*(int *)param_1 + 8))(puVar3 + 0xb,4);
          if (*(uint *)((int)this + 0x78) <= (uint)puVar3[0xb]) {
            return 0;
          }
          iVar1 = (**(code **)(*(int *)param_1 + 0xc))(puVar3 + 7,0x10);
          if (iVar1 != 0) {
            return 0;
          }
          FUN_00470b30((int *)param_1,(int)(puVar3 + 3));
          (**(code **)(*(int *)param_1 + 8))(puVar3,4);
          (**(code **)(*(int *)param_1 + 8))(puVar3 + 1,4);
          (**(code **)(*(int *)param_1 + 8))(puVar3 + 2,4);
          local_4 = (void *)((int)local_4 + 1);
        } while (local_4 < unaff_EBP);
      }
      return 1;
    }
  }
  return 0;
}


