/* lithtech.exe decompilation - module netmgr */
#include "ghidra_types.h"

/* 00464bf0 size=1065 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/kernel/net/src/netmgr.cpp */

/* netmgr_464bf0: lifted from original x86 -> lt_lifted.c */


/* 00465780 size=57 */

/* repo: runtime/kernel/net/src/netmgr.cpp */

void __thiscall netmgr_465780(void *this,int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    FUN_00466dd0(this,param_1);
    netmgr_467b80(this,param_1,1,(byte *)s_CNetMgr__Disconnect_called___rea_004db06c,param_2);
    (**(code **)(**(int **)(param_1 + 0x30) + 0x5c))(param_1,param_2);
  }
  return;
}


/* 00465e20 size=481 */

/* repo: runtime/kernel/net/src/netmgr.cpp */

undefined4 __thiscall netmgr_465e20(void *this,int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  
  FUN_004317e0();
  iVar5 = 0;
  if (*(int *)((int)this + 0xb4) != 0) {
    *(undefined4 *)(param_1 + 0x80) = 0;
    *(undefined4 *)(param_1 + 0x7c) = 0;
    *(undefined4 *)(param_1 + 0x74) = 0;
    *(undefined4 *)(param_1 + 0x88) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0;
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0xb4) = 0;
    *(undefined4 *)(param_1 + 0x9c) = 0;
    uVar6 = 0xa0;
    do {
      uVar1 = uVar6 + 4;
      *(undefined4 *)(uVar6 + param_1) = 0;
      uVar6 = uVar1;
    } while (uVar1 < 0xac);
    *(undefined4 *)(param_1 + 0x98) = 0;
    *(undefined4 *)(param_1 + 0x94) = 0;
    *(undefined4 *)(param_1 + 0x78) = 0;
    FUN_00468340((void *)((int)this + 0x28),*(undefined4 **)((int)this + 0x30),&param_1,
                 &DAT_004ecc58);
    iVar2 = (**(code **)(**(int **)((int)this + 0xb4) + 4))(param_1,*(uint *)(param_1 + 0x70) & 1);
    if (iVar2 != 0) {
      return 1;
    }
    uVar6 = *(int *)((int)this + 0x30) - 1;
    if ((uint)(*(int *)((int)this + 0x38) * 2) <= *(uint *)((int)this + 0x34)) {
      iVar2 = *(int *)((int)this + 0x30) + -1 + *(int *)((int)this + 0x38);
      iVar3 = (**(code **)(DAT_004ecc58 + 4))(iVar2 * 4);
      if (iVar3 != 0) {
        iVar5 = iVar3;
LAB_00465f3f:
        uVar1 = 0;
        if (uVar6 != 0) {
          do {
            uVar1 = uVar1 + 1;
            *(undefined4 *)(iVar5 + -4 + uVar1 * 4) =
                 *(undefined4 *)(*(int *)((int)this + 0x2c) + -4 + uVar1 * 4);
          } while (uVar1 < uVar6);
        }
        if (uVar6 < *(int *)((int)this + 0x30) - 1U) {
          puVar4 = (undefined4 *)(iVar5 + uVar6 * 4);
          do {
            uVar6 = uVar6 + 1;
            *puVar4 = *(undefined4 *)((int)puVar4 + *(int *)((int)this + 0x2c) + (4 - iVar5));
            puVar4 = puVar4 + 1;
          } while (uVar6 < *(int *)((int)this + 0x30) - 1U);
        }
        iVar2 = *(int *)((int)this + 0x2c);
        if (iVar2 != 0) {
          if (iVar2 != 0) {
            (**(code **)(DAT_004ecc58 + 8))(iVar2);
          }
          *(undefined4 *)((int)this + 0x2c) = 0;
        }
        *(undefined4 *)((int)this + 0x34) = 0;
        *(int *)((int)this + 0x2c) = iVar5;
        *(undefined4 *)((int)this + 0x34) = *(undefined4 *)((int)this + 0x38);
        *(int *)((int)this + 0x30) = *(int *)((int)this + 0x30) + -1;
        return 0;
      }
      if (iVar2 == 0) goto LAB_00465f3f;
    }
    *(int *)((int)this + 0x34) = *(int *)((int)this + 0x34) + 1;
    if (uVar6 < *(int *)((int)this + 0x30) - 1U) {
      do {
        uVar6 = uVar6 + 1;
        *(undefined4 *)(*(int *)((int)this + 0x2c) + -4 + uVar6 * 4) =
             *(undefined4 *)(*(int *)((int)this + 0x2c) + uVar6 * 4);
      } while (uVar6 < *(int *)((int)this + 0x30) - 1U);
    }
    *(int *)((int)this + 0x30) = *(int *)((int)this + 0x30) + -1;
  }
  return 0;
}


/* 00466010 size=321 */

/* repo: runtime/kernel/net/src/netmgr.cpp */

void __thiscall netmgr_466010(void *this,int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint uVar6;
  
  uVar6 = 0xffffffff;
  uVar2 = 0;
  if (*(uint *)((int)this + 0x30) != 0) {
    piVar5 = *(int **)((int)this + 0x2c);
    do {
      if (*piVar5 == param_1) {
        uVar6 = uVar2;
        break;
      }
      uVar2 = uVar2 + 1;
      piVar5 = piVar5 + 1;
    } while (uVar2 < *(uint *)((int)this + 0x30));
  }
  FUN_004317e0();
  if (uVar6 != 0xffffffff) {
    if (*(int **)((int)this + 0xb4) != (int *)0x0) {
      (**(code **)(**(int **)((int)this + 0xb4) + 8))(param_1);
    }
    if ((uint)(*(int *)((int)this + 0x38) * 2) <= *(uint *)((int)this + 0x34)) {
      iVar1 = *(int *)((int)this + 0x30) + -1 + *(int *)((int)this + 0x38);
      iVar3 = FUN_00456f10(&DAT_004ecc58,0,iVar1);
      if ((iVar3 != 0) || (iVar1 == 0)) {
        uVar2 = 0;
        if (uVar6 != 0) {
          do {
            uVar2 = uVar2 + 1;
            *(undefined4 *)(iVar3 + -4 + uVar2 * 4) =
                 *(undefined4 *)(*(int *)((int)this + 0x2c) + -4 + uVar2 * 4);
          } while (uVar2 < uVar6);
        }
        if (uVar6 < *(int *)((int)this + 0x30) - 1U) {
          puVar4 = (undefined4 *)(iVar3 + uVar6 * 4);
          do {
            uVar6 = uVar6 + 1;
            *puVar4 = *(undefined4 *)((*(int *)((int)this + 0x2c) - iVar3) + (int)(puVar4 + 1));
            puVar4 = puVar4 + 1;
          } while (uVar6 < *(int *)((int)this + 0x30) - 1U);
        }
        iVar1 = *(int *)((int)this + 0x2c);
        if (iVar1 != 0) {
          if (iVar1 != 0) {
            (**(code **)(DAT_004ecc58 + 8))(iVar1);
          }
          *(undefined4 *)((int)this + 0x2c) = 0;
        }
        *(undefined4 *)((int)this + 0x34) = 0;
        *(int *)((int)this + 0x2c) = iVar3;
        *(undefined4 *)((int)this + 0x34) = *(undefined4 *)((int)this + 0x38);
        *(int *)((int)this + 0x30) = *(int *)((int)this + 0x30) + -1;
        return;
      }
    }
    *(int *)((int)this + 0x34) = *(int *)((int)this + 0x34) + 1;
    if (uVar6 < *(int *)((int)this + 0x30) - 1U) {
      do {
        uVar6 = uVar6 + 1;
        *(undefined4 *)(*(int *)((int)this + 0x2c) + -4 + uVar6 * 4) =
             *(undefined4 *)(*(int *)((int)this + 0x2c) + uVar6 * 4);
      } while (uVar6 < *(int *)((int)this + 0x30) - 1U);
    }
    *(int *)((int)this + 0x30) = *(int *)((int)this + 0x30) + -1;
  }
  return;
}


/* 004666e0 size=976 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/kernel/net/src/netmgr.cpp */

/* netmgr_4666e0: lifted from original x86 -> lt_lifted.c */


/* 00467b10 size=104 */

/* repo: runtime/kernel/net/src/netmgr.cpp */

void __cdecl netmgr_467b10(undefined4 param_1,int param_2,byte *param_3,undefined4 param_4)

{
  undefined8 uVar1;
  undefined1 local_1f4 [500];
  
  if (param_2 <= DAT_004e98f0) {
    FUN_004baabf(local_1f4,499,param_3,&param_4);
    uVar1 = thunk_FUN_00424350((uint *)&DAT_004ea780);
    FUN_00436670((byte *)s___d___s_s_004db50c,(int)uVar1);
  }
  return;
}


/* 00467b80 size=126 */

/* repo: runtime/kernel/net/src/netmgr.cpp */

void __cdecl
netmgr_467b80(undefined4 param_1,int param_2,int param_3,byte *param_4,undefined4 param_5)

{
  undefined8 uVar1;
  undefined1 local_1f4 [500];
  
  if ((param_3 <= DAT_004e98f0) && ((DAT_004e98e4 != 0 || ((*(byte *)(param_2 + 0x70) & 1) == 0))))
  {
    FUN_004baabf(local_1f4,499,param_4,&param_5);
    uVar1 = thunk_FUN_00424350((uint *)&DAT_004ea780);
    FUN_00436670((byte *)s___d___s_s_004db50c,(int)uVar1);
  }
  return;
}


