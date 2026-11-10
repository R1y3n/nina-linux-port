/* lithtech.exe decompilation - module s_concommand */
#include "ghidra_types.h"

/* 004757a0 size=356 */

/* WARNING: Removing unreachable block (ram,0x00475870) */
/* repo: runtime/server/src/s_concommand.cpp */

void __thiscall s_concommand_4757a0(void *this,undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if ((uint)*(ushort *)((int)this + 0x36) <= *(ushort *)((int)this + 0x38) + 4) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
    return;
  }
  if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4) {
    do {
      uVar1 = *(uint *)((int)this + 0x58);
      if (*(int *)((int)this + 0x5c) == 0) {
        iVar2 = FUN_0040c920(&DAT_004ecc58,0,*(int *)((int)this + 0x60) + uVar1 + 1);
        if (iVar2 != 0) {
          uVar4 = 0;
          if (uVar1 != 0) {
            do {
              uVar3 = uVar4 + 1;
              *(undefined1 *)(uVar4 + iVar2) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar3);
              uVar4 = uVar3;
            } while (uVar3 < uVar1);
          }
          uVar4 = uVar1;
          if (uVar1 < *(uint *)((int)this + 0x58)) {
            do {
              uVar4 = uVar4 + 1;
              *(undefined1 *)(uVar4 + iVar2) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar4);
            } while (uVar4 < *(uint *)((int)this + 0x58));
          }
          *(undefined1 *)(uVar1 + iVar2) = 0;
          if (*(int *)((int)this + 0x54) != 0) {
            FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x54));
            *(undefined4 *)((int)this + 0x54) = 0;
            *(undefined4 *)((int)this + 0x5c) = 0;
          }
          *(int *)((int)this + 0x54) = iVar2;
          *(undefined4 *)((int)this + 0x5c) = *(undefined4 *)((int)this + 0x60);
          goto LAB_0047588c;
        }
      }
      else {
        *(int *)((int)this + 0x5c) = *(int *)((int)this + 0x5c) + -1;
        *(undefined1 *)(*(int *)((int)this + 0x54) + uVar1) = 0;
LAB_0047588c:
        *(int *)((int)this + 0x58) = *(int *)((int)this + 0x58) + 1;
      }
    } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4);
  }
  *(undefined4 *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = param_1;
  *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 4;
  *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 4;
  return;
}


/* 00475bf0 size=1 */

/* repo: runtime/server/src/s_concommand.cpp */

undefined4 s_concommand_475bf0(byte *param_1,byte *param_2,int param_3,int *param_4)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  iVar4 = 0;
  if (0 < param_3) {
    do {
      pbVar2 = param_1;
      pbVar5 = param_2;
      do {
        bVar1 = *pbVar2;
        bVar6 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
code_r0x00475c2c:
          iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto code_r0x00475c31;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto code_r0x00475c2c;
        pbVar2 = pbVar2 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
code_r0x00475c31:
      if (iVar3 == 0) {
        *param_4 = iVar4;
        return 1;
      }
      iVar4 = iVar4 + 1;
      param_2 = param_2 + 0x32;
    } while (iVar4 < param_3);
  }
  return 0;
}


/* 00475f10 size=177 */

/* repo: runtime/server/src/s_concommand.cpp */

void __cdecl s_concommand_475f10(int *param_1,int param_2)

{
  int *this;
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  piVar1 = param_1;
  if (param_1[0xe] != 0) {
    puVar3 = FUN_0046b170(&param_1,0x44c,0x44c);
    this = (int *)*puVar3;
    if (this != (int *)0x0) {
      (**(code **)(*this + 4))();
    }
    if (param_1 != (int *)0x0) {
      (**(code **)(*param_1 + 8))();
    }
    iVar2 = param_2;
    uVar4 = FUN_004c4c00(*(void **)(param_2 + 0x10),*(void **)(param_2 + 0x10),
                         (byte *)s_AutoDeactivate_004d8d08);
    if (uVar4 == 0) {
      FUN_00489b30(DAT_004ebfa4);
    }
    *(undefined2 *)(this + 0xe) = 1;
    *(undefined2 *)(this + 0xd) = 1;
    FUN_0046b440(this,*(char **)(iVar2 + 0x10));
    FUN_0046b440(this,*(char **)(iVar2 + 0x14));
    FUN_004777e0(piVar1[0xe],0x10,this,0x80);
    if (this != (int *)0x0) {
      (**(code **)(*this + 8))();
    }
  }
  return;
}


