/* lithtech.exe decompilation - unnamed_004b8000 */
#include "ghidra_types.h"

/* 004b8020 size=119 */

void __fastcall FUN_004b8020(undefined4 *param_1)

{
  int iVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004cae38;
  local_c = ExceptionList;
  local_4 = 0;
  ExceptionList = &local_c;
  FUN_004b82b0((int)param_1);
  iVar1 = param_1[1];
  local_4 = 0xffffffff;
  *param_1 = &PTR_LAB_004cef64;
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    param_1[1] = 0;
    param_1[3] = 0;
  }
  param_1[2] = 0;
  ExceptionList = local_c;
  return;
}


/* 004b80a0 size=12 */

void __thiscall FUN_004b80a0(void *this,undefined2 param_1)

{
  *(undefined2 *)((int)this + 0x14) = param_1;
  return;
}


/* 004b80b0 size=45 */

int __thiscall FUN_004b80b0(void *this,byte *param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  
  uVar2 = 0xffffffff;
  pbVar3 = param_1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
  } while (bVar1 != 0);
  FUN_004b80e0(this,param_1,param_2,~uVar2 - 1 & 0xffff);
  return;
}


/* 004b80e0 size=244 */

void __thiscall FUN_004b80e0(void *this,byte *param_1,int param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  ushort *puVar5;
  byte *pbVar6;
  int local_8;
  undefined2 local_4;
  undefined2 local_2;
  
  if ((param_2 != 0) && (iVar2 = FUN_004b81e0(this,param_1), iVar2 != 0)) {
    return;
  }
  uVar3 = 0;
  if (*(uint *)((int)this + 8) != 0) {
    puVar5 = (ushort *)(*(int *)((int)this + 4) + 4);
    do {
      if (puVar5[1] + 1 + param_3 < (uint)*puVar5) goto LAB_004b819a;
      uVar3 = uVar3 + 1;
      puVar5 = puVar5 + 4;
    } while (uVar3 < *(uint *)((int)this + 8));
  }
  uVar3 = param_3 + 1;
  if ((ushort)(param_3 + 1) < *(ushort *)((int)this + 0x14)) {
    uVar3 = (uint)*(ushort *)((int)this + 0x14);
  }
  local_8 = FUN_00430de0(uVar3 & 0xffff);
  if (local_8 == 0) {
    return;
  }
  local_4 = (undefined2)uVar3;
  local_2 = 0;
  iVar2 = FUN_004b8580(this,*(undefined4 **)((int)this + 8),&local_8,&DAT_004ecc58);
  if (iVar2 == 0) {
    return;
  }
  uVar3 = *(int *)((int)this + 8) - 1U & 0xffff;
LAB_004b819a:
  piVar1 = (int *)(*(int *)((int)this + 4) + uVar3 * 8);
  pbVar4 = (byte *)((uint)*(ushort *)((int)piVar1 + 6) + *piVar1);
  pbVar6 = pbVar4;
  for (uVar3 = param_3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pbVar6 = *(undefined4 *)param_1;
    param_1 = param_1 + 4;
    pbVar6 = pbVar6 + 4;
  }
  for (uVar3 = param_3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pbVar6 = *param_1;
    param_1 = param_1 + 1;
    pbVar6 = pbVar6 + 1;
  }
  pbVar4[param_3] = 0;
  *(short *)((int)piVar1 + 6) = *(short *)((int)piVar1 + 6) + (short)param_3 + 1;
  return;
}


/* 004b81e0 size=197 */

int __thiscall FUN_004b81e0(void *this,byte *param_1)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  bool bVar10;
  uint local_10;
  
  local_10 = 0;
  if (*(uint *)((int)this + 8) != 0) {
    uVar4 = 0;
    do {
      iVar3 = *(int *)(*(int *)((int)this + 4) + uVar4 * 8);
      uVar2 = *(ushort *)(*(int *)((int)this + 4) + 6 + uVar4 * 8);
      uVar4 = 0;
      if (uVar2 != 0) {
        do {
          pbVar9 = (byte *)((uVar4 & 0xffff) + iVar3);
          pbVar5 = param_1;
          pbVar8 = pbVar9;
          do {
            bVar1 = *pbVar5;
            bVar10 = bVar1 < *pbVar8;
            if (bVar1 != *pbVar8) {
LAB_004b824e:
              iVar6 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
              goto LAB_004b8253;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar5[1];
            bVar10 = bVar1 < pbVar8[1];
            if (bVar1 != pbVar8[1]) goto LAB_004b824e;
            pbVar5 = pbVar5 + 2;
            pbVar8 = pbVar8 + 2;
          } while (bVar1 != 0);
          iVar6 = 0;
LAB_004b8253:
          if (iVar6 == 0) {
            return (uVar4 & 0xffff) + iVar3;
          }
          uVar7 = 0xffffffff;
          do {
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            bVar1 = *pbVar9;
            pbVar9 = pbVar9 + 1;
          } while (bVar1 != 0);
          uVar4 = ~uVar7 + uVar4;
        } while ((ushort)uVar4 < uVar2);
      }
      local_10 = local_10 + 1;
      uVar4 = local_10 & 0xffff;
    } while (uVar4 < *(uint *)((int)this + 8));
  }
  return 0;
}


/* 004b82b0 size=89 */

void __fastcall FUN_004b82b0(int param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    do {
      FUN_00430df0(*(undefined **)(*(int *)(param_1 + 4) + uVar2 * 8));
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_1 + 8));
  }
  iVar1 = *(int *)(param_1 + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}


/* 004b8310 size=64 */

void __fastcall FUN_004b8310(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = param_1[1];
  *param_1 = &PTR_LAB_004cef64;
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    param_1[1] = 0;
    param_1[3] = 0;
  }
  param_1[2] = 0;
  return;
}


/* 004b8370 size=304 */

/* WARNING: Removing unreachable block (ram,0x004b845b) */

undefined4 __thiscall FUN_004b8370(void *this,undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *unaff_retaddr;
  
  uVar2 = *(uint *)((int)this + 8);
  if (*(int *)((int)this + 0xc) != 0) {
    iVar3 = *(int *)((int)this + 4);
    *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
    *(undefined4 *)(iVar3 + uVar2 * 8) = *param_1;
    *(undefined4 *)(iVar3 + 4 + uVar2 * 8) = param_1[1];
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    return 1;
  }
  iVar3 = (**(code **)(DAT_004ecc58 + 4))((uVar2 + 1 + *(int *)((int)this + 0x10)) * 8);
  if (iVar3 == 0) {
    return 0;
  }
  uVar4 = 0;
  if (uVar2 != 0) {
    do {
      iVar1 = uVar4 * 8;
      puVar5 = (undefined4 *)(iVar1 + *(int *)((int)this + 4));
      uVar4 = uVar4 + 1;
      *(undefined4 *)(iVar1 + iVar3) = *puVar5;
      *(undefined4 *)(iVar1 + 4 + iVar3) = puVar5[1];
    } while (uVar4 < uVar2);
  }
  if (uVar2 < *(uint *)((int)this + 8)) {
    uVar4 = uVar2;
    puVar5 = (undefined4 *)(iVar3 + 8 + uVar2 * 8);
    do {
      iVar1 = *(int *)((int)this + 4);
      uVar4 = uVar4 + 1;
      *puVar5 = *(undefined4 *)(iVar1 + -8 + uVar4 * 8);
      puVar5[1] = *(undefined4 *)(iVar1 + -4 + uVar4 * 8);
      puVar5 = puVar5 + 2;
    } while (uVar4 < *(uint *)((int)this + 8));
  }
  *(undefined4 *)(iVar3 + uVar2 * 8) = *unaff_retaddr;
  *(undefined4 *)(iVar3 + 4 + uVar2 * 8) = unaff_retaddr[1];
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(int *)((int)this + 4) = iVar3;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
  return 1;
}


/* 004b84a0 size=217 */

undefined4 __thiscall FUN_004b84a0(void *this,int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 uStack_10;
  undefined1 auStack_8 [8];
  
  uVar4 = *(uint *)((int)this + 8);
  iVar2 = (**(code **)(*param_1 + 0x1c))();
  iVar2 = FUN_00417390(this,iVar2 + uVar4,(int *)0x0,&DAT_004ecc58);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = (**(code **)*param_1)(auStack_8);
  uStack_10 = *(undefined4 *)(iVar2 + 4);
  iVar2 = (**(code **)(*param_1 + 4))(auStack_8 + -0xc);
  while( true ) {
    if (iVar2 == 0) {
      return 1;
    }
    if (*(uint *)((int)this + 8) <= uVar4) break;
    puVar1 = (undefined4 *)(*(int *)((int)this + 4) + uVar4 * 8);
    puVar3 = (undefined4 *)(**(code **)(*param_1 + 8))(&uStack_10,auStack_8 + -0x10);
    uVar4 = uVar4 + 1;
    *puVar1 = *puVar3;
    puVar1[1] = puVar3[1];
    iVar2 = (**(code **)(*param_1 + 4))(auStack_8 + -0x18);
  }
  if (*(int *)((int)this + 4) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(undefined4 *)((int)this + 8) = 0;
  return 0;
}


/* 004b8580 size=306 */

undefined4 __thiscall FUN_004b8580(void *this,undefined4 *param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar3 = *(undefined4 **)((int)this + 8);
  if (puVar3 < param_1) {
    return 0;
  }
  if (*(int *)((int)this + 0xc) != 0) {
    for (; param_1 < puVar3; puVar3 = (undefined4 *)((int)puVar3 - 1)) {
      puVar4 = (undefined4 *)(*(int *)((int)this + 4) + (int)puVar3 * 8);
      *puVar4 = *(undefined4 *)(*(int *)((int)this + 4) + -8 + (int)puVar3 * 8);
      puVar4[1] = puVar4[-1];
    }
    iVar2 = *(int *)((int)this + 4);
    *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
    *(int *)(iVar2 + (int)param_1 * 8) = *param_2;
    *(int *)(iVar2 + 4 + (int)param_1 * 8) = param_2[1];
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    return 1;
  }
  iVar2 = (**(code **)(*param_3 + 4))(((int)puVar3 + *(int *)((int)this + 0x10) + 1) * 8);
  if (iVar2 == 0) {
    return 0;
  }
  puVar3 = (undefined4 *)0x0;
  if (param_1 != (undefined4 *)0x0) {
    do {
      iVar1 = *(int *)((int)this + 4);
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      *(undefined4 *)(iVar2 + -8 + (int)puVar3 * 8) = *(undefined4 *)(iVar1 + -8 + (int)puVar3 * 8);
      *(undefined4 *)(iVar2 + -4 + (int)puVar3 * 8) = *(undefined4 *)(iVar1 + -4 + (int)puVar3 * 8);
    } while (puVar3 < param_1);
  }
  if (param_1 < *(undefined4 **)((int)this + 8)) {
    puVar3 = param_1;
    puVar4 = (undefined4 *)(iVar2 + 8 + (int)param_1 * 8);
    do {
      iVar1 = *(int *)((int)this + 4);
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      *puVar4 = *(undefined4 *)(iVar1 + -8 + (int)puVar3 * 8);
      puVar4[1] = *(undefined4 *)(iVar1 + -4 + (int)puVar3 * 8);
      puVar4 = puVar4 + 2;
    } while (puVar3 < *(undefined4 **)((int)this + 8));
    param_3 = param_2;
  }
  *(undefined4 *)(iVar2 + (int)param_1 * 8) = *param_1;
  *(undefined4 *)(iVar2 + 4 + (int)param_1 * 8) = param_1[1];
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*param_3 + 8))(iVar1);
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(int *)((int)this + 4) = iVar2;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
  return 1;
}


/* 004b86d0 size=11 */

void FUN_004b86d0(void)

{
  DAT_004ecc58 = &PTR_LAB_004cef94;
  return;
}


/* 004b86e0 size=12 */

void FUN_004b86e0(void)

{
  FUN_004b9cf5(&LAB_004b86f0);
  return;
}


/* 004b8700 size=7 */

void __fastcall FUN_004b8700(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cef94;
  return;
}


/* 004b8750 size=66 */

undefined4 * __fastcall FUN_004b8750(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004cae58;
  local_c = ExceptionList;
  local_4 = 0;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_004cefa0;
  FUN_004b88d0((int)param_1);
  ExceptionList = local_c;
  return param_1;
}


/* 004b87a0 size=30 */

undefined4 * __thiscall FUN_004b87a0(void *this,byte param_1)

{
  FUN_004b87c0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004b87c0 size=70 */

void __fastcall FUN_004b87c0(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004cae78;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_004cefa0;
  local_4 = 0;
  FUN_004b8860((int)param_1);
  *param_1 = &PTR_LAB_004cef94;
  ExceptionList = local_c;
  return;
}


/* 004b8810 size=71 */

undefined4 __thiscall FUN_004b8810(void *this,int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  FUN_004b8860((int)this);
  uVar2 = param_2 + 3U & 0xfffffffc;
  if (uVar2 != 0) {
    iVar1 = (**(code **)(*param_1 + 4))(uVar2);
    *(int *)((int)this + 8) = iVar1;
    if (iVar1 == 0) {
      return 0;
    }
  }
  *(uint *)((int)this + 0x10) = uVar2;
  *(int **)((int)this + 4) = param_1;
  *(undefined4 *)((int)this + 0xc) = 0;
  return 1;
}


/* 004b8860 size=28 */

void __fastcall FUN_004b8860(int param_1)

{
  if (*(int **)(param_1 + 4) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 4) + 8))(*(undefined4 *)(param_1 + 8));
  }
  FUN_004b88d0(param_1);
  return;
}


/* 004b88d0 size=15 */

void __fastcall FUN_004b88d0(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}


/* 004b88e0 size=55 */

uint __cdecl FUN_004b88e0(char *param_1,undefined4 param_2,uint param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  
  uVar1 = 0;
  pcVar3 = param_1;
  if (param_3 != 0) {
    do {
      bVar6 = true;
      iVar2 = param_4;
      pcVar4 = pcVar3;
      pcVar5 = param_1;
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar6 = *pcVar4 == *pcVar5;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      } while (bVar6);
      if (bVar6) {
        return uVar1;
      }
      uVar1 = uVar1 + 1;
      pcVar3 = pcVar3 + param_4;
    } while (uVar1 < param_3);
  }
  return 0xffffffff;
}


/* 004b8920 size=65 */

char * __cdecl FUN_004b8920(char *param_1,char *param_2,int param_3)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  bool bVar5;
  
  if (param_1 != (char *)0x0) {
    bVar5 = true;
    iVar2 = param_3;
    pcVar1 = param_1;
    pcVar3 = param_2;
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar5 = *pcVar1 == *pcVar3;
      pcVar1 = pcVar1 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar5);
    pcVar1 = param_1;
    if (bVar5) {
      return param_1;
    }
    while( true ) {
      pcVar1 = *(char **)(pcVar1 + 4);
      if (pcVar1 == param_1) break;
      bVar5 = true;
      iVar2 = param_3;
      pcVar3 = pcVar1;
      pcVar4 = param_2;
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar5 = *pcVar3 == *pcVar4;
        pcVar3 = pcVar3 + 1;
        pcVar4 = pcVar4 + 1;
      } while (bVar5);
      if (bVar5) {
        return pcVar1;
      }
    }
  }
  return (char *)0x0;
}


/* 004b8970 size=100 */

undefined4 __thiscall FUN_004b8970(void *this,char *param_1,uint param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  if ((int)param_2 < *(int *)((int)this + 0xc)) {
    pcVar4 = *(char **)((int)this + 8);
    for (uVar2 = param_2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)param_1 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      param_1 = param_1 + 4;
    }
    for (uVar2 = param_2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      param_1 = param_1 + 1;
    }
    *(undefined1 *)((param_2 - 1) + *(int *)((int)this + 8)) = 0;
    return 1;
  }
  uVar2 = 0xffffffff;
  pcVar4 = *(char **)((int)this + 8);
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)param_1 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    param_1 = param_1 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    param_1 = param_1 + 1;
  }
  return 1;
}


/* 004b89e0 size=26 */

undefined4 __thiscall FUN_004b89e0(void *this,undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_004bb167(*(void **)((int)this + 8),*(void **)((int)this + 8));
  *param_1 = uVar1;
  return 1;
}


/* 004b8a00 size=26 */

undefined4 __thiscall FUN_004b8a00(void *this,float *param_1)

{
  float10 fVar1;
  
  fVar1 = FUN_004baed0(*(undefined **)((int)this + 8),*(undefined **)((int)this + 8));
  *param_1 = (float)fVar1;
  return 1;
}


/* 004b8a20 size=4 */

undefined4 __fastcall FUN_004b8a20(int param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}


/* 004b8a30 size=41 */

undefined4 * __fastcall FUN_004b8a30(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = (undefined4 *)*param_1;
  while ((puVar1 != (undefined4 *)0x0 &&
         (uVar2 = FUN_004c4c00((void *)puVar1[2],(void *)puVar1[2],(byte *)param_1[2]), uVar2 != 0))
        ) {
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}


/* 004b8a60 size=26 */

undefined4 * __thiscall FUN_004b8a60(void *this,byte *param_1)

{
  undefined4 *puVar1;
  
  if (param_1 == (byte *)0x0) {
    return *(undefined4 **)((int)this + 0xc);
  }
  puVar1 = FUN_004b8a80((void *)((int)this + 0xc),param_1);
  return puVar1;
}


/* 004b8a80 size=42 */

undefined4 * __thiscall FUN_004b8a80(void *this,byte *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  void *extraout_ECX;
  
  puVar1 = *(undefined4 **)this;
  while ((puVar1 != (undefined4 *)0x0 &&
         (uVar2 = FUN_004c4c00(this,(byte *)puVar1[2],param_1), uVar2 != 0))) {
    puVar1 = (undefined4 *)*puVar1;
    this = extraout_ECX;
  }
  return puVar1;
}


/* 004b8ab0 size=32 */

void __fastcall FUN_004b8ab0(undefined4 *param_1)

{
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  *param_1 = &PTR_LAB_004cefac;
  param_1[10] = 0;
  return;
}


/* 004b8ad0 size=130 */

void __fastcall FUN_004b8ad0(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  puStack_8 = &LAB_004caebc;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_LAB_004cefac;
  local_4 = 3;
  FUN_004b8c90((int)param_1);
  FUN_004b8f50((int)param_1);
  local_4 = local_4 & 0xffffff00;
  if ((undefined *)param_1[3] != (undefined *)0x0) {
    FUN_00430df0((undefined *)param_1[3]);
    param_1[3] = 0;
  }
  local_4 = 0xffffffff;
  if ((undefined *)param_1[2] != (undefined *)0x0) {
    FUN_00430df0((undefined *)param_1[2]);
    param_1[2] = 0;
  }
  ExceptionList = local_c;
  return;
}


/* 004b8b60 size=300 */

undefined4 __thiscall FUN_004b8b60(void *this,char *param_1,char *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte unaff_BL;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  char *pcVar7;
  int unaff_EDI;
  char *pcVar8;
  
  uVar5 = 0xffffffff;
  pcVar7 = param_1;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  if (*(undefined **)((int)this + 8) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)((int)this + 8));
    *(undefined4 *)((int)this + 8) = 0;
  }
  uVar2 = FUN_00430de0(~uVar5);
  *(undefined4 *)((int)this + 8) = uVar2;
  uVar5 = 0xffffffff;
  pcVar7 = param_1;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  pcVar7 = param_1;
  pcVar8 = *(char **)((int)this + 8);
  for (uVar6 = ~uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = ~uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  if (param_2 == (char *)0x0) {
    if (*(undefined **)((int)this + 0xc) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)((int)this + 0xc));
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    puVar3 = (undefined4 *)FUN_00430de0(6);
    *(undefined4 **)((int)this + 0xc) = puVar3;
    *puVar3 = DAT_004e0d30;
    *(undefined2 *)(puVar3 + 1) = DAT_004e0d34;
  }
  else {
    uVar5 = 0xffffffff;
    pcVar7 = param_2;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    if (*(undefined **)((int)this + 0xc) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)((int)this + 0xc));
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    uVar2 = FUN_00430de0(~uVar5 - 1);
    *(undefined4 *)((int)this + 0xc) = uVar2;
    uVar5 = 0xffffffff;
    pcVar7 = param_2;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    pcVar7 = *(char **)((int)this + 0xc);
    for (uVar6 = ~uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)param_2;
      param_2 = param_2 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = ~uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *param_2;
      param_2 = param_2 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  *(undefined1 *)((int)this + 0x10) = 10;
  *(undefined1 *)((int)this + 0x11) = 0x5b;
  *(undefined1 *)((int)this + 0x12) = 0x5d;
  *(undefined1 *)((int)this + 0x13) = 0x3b;
  *(undefined1 *)((int)this + 0x14) = 0x22;
  *(undefined1 *)((int)this + 0x15) = 0x23;
  iVar4 = FUN_004b9000(param_1,unaff_EDI,unaff_ESI,unaff_EBP,unaff_BL);
  *(undefined4 *)((int)this + 0x28) = 1;
  if (iVar4 == 0) {
    FUN_004b8c90((int)this);
    return 0;
  }
  return 1;
}


/* 004b8c90 size=282 */

void __fastcall FUN_004b8c90(int param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  if (*(int *)(param_1 + 0x28) != 0) {
    if (*(undefined **)(param_1 + 8) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)(param_1 + 8));
      *(undefined4 *)(param_1 + 8) = 0;
    }
    if (*(undefined **)(param_1 + 0xc) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)(param_1 + 0xc));
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
    while (piVar1 = *(int **)(param_1 + 0x18), piVar1 != (int *)0x0) {
      while (piVar2 = (int *)piVar1[3], piVar2 != (int *)0x0) {
        while (piVar3 = (int *)piVar2[3], piVar3 != (int *)0x0) {
          if ((int *)piVar3[1] == (int *)0x0) {
            piVar2[3] = *piVar3;
          }
          else {
            *(int *)piVar3[1] = *piVar3;
          }
          if (*piVar3 == 0) {
            piVar2[4] = piVar3[1];
          }
          else {
            *(int *)(*piVar3 + 4) = piVar3[1];
          }
          FUN_004b8fa0((int)piVar3);
          FUN_00430df0((undefined *)piVar3);
        }
        if ((int *)piVar2[1] == (int *)0x0) {
          piVar1[3] = *piVar2;
        }
        else {
          *(int *)piVar2[1] = *piVar2;
        }
        if (*piVar2 == 0) {
          piVar1[4] = piVar2[1];
        }
        else {
          *(int *)(*piVar2 + 4) = piVar2[1];
        }
        FUN_004b8fa0((int)piVar2);
        FUN_00430df0((undefined *)piVar2);
      }
      if ((int *)piVar1[1] == (int *)0x0) {
        *(int *)(param_1 + 0x18) = *piVar1;
      }
      else {
        *(int *)piVar1[1] = *piVar1;
      }
      if (*piVar1 == 0) {
        *(int *)(param_1 + 0x1c) = piVar1[1];
      }
      else {
        *(int *)(*piVar1 + 4) = piVar1[1];
      }
      FUN_004b8fa0((int)piVar1);
      FUN_00430df0((undefined *)piVar1);
    }
    *(undefined4 *)(param_1 + 0x28) = 0;
  }
  return;
}


/* 004b8db0 size=26 */

undefined4 * __thiscall FUN_004b8db0(void *this,byte *param_1)

{
  undefined4 *puVar1;
  
  if (param_1 == (byte *)0x0) {
    return *(undefined4 **)((int)this + 0x18);
  }
  puVar1 = FUN_004b8a80((void *)((int)this + 0x18),param_1);
  return puVar1;
}


/* 004b8dd0 size=34 */

undefined4 * __thiscall FUN_004b8dd0(void *this,byte *param_1,byte *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = FUN_004b8db0(this,param_1);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  puVar1 = FUN_004b8a60(puVar1,param_2);
  return puVar1;
}


/* 004b8e00 size=50 */

undefined4 __thiscall FUN_004b8e00(void *this,byte *param_1,byte *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  void *this_00;
  undefined4 uVar2;
  
  puVar1 = FUN_004b8dd0(this,param_1,param_2);
  if (puVar1 != (undefined4 *)0x0) {
    this_00 = (void *)FUN_004b8a20((int)puVar1);
    if (this_00 != (void *)0x0) {
      uVar2 = FUN_004b89e0(this_00,param_3);
      return uVar2;
    }
  }
  return 0;
}


/* 004b8e40 size=50 */

undefined4 __thiscall FUN_004b8e40(void *this,byte *param_1,byte *param_2,float *param_3)

{
  undefined4 *puVar1;
  void *this_00;
  undefined4 uVar2;
  
  puVar1 = FUN_004b8dd0(this,param_1,param_2);
  if (puVar1 != (undefined4 *)0x0) {
    this_00 = (void *)FUN_004b8a20((int)puVar1);
    if (this_00 != (void *)0x0) {
      uVar2 = FUN_004b8a00(this_00,param_3);
      return uVar2;
    }
  }
  return 0;
}


/* 004b8e80 size=55 */

undefined4 __thiscall
FUN_004b8e80(void *this,byte *param_1,byte *param_2,char *param_3,uint param_4)

{
  undefined4 *puVar1;
  void *this_00;
  undefined4 uVar2;
  
  puVar1 = FUN_004b8dd0(this,param_1,param_2);
  if (puVar1 != (undefined4 *)0x0) {
    this_00 = (void *)FUN_004b8a20((int)puVar1);
    if (this_00 != (void *)0x0) {
      uVar2 = FUN_004b8970(this_00,param_3,param_4);
      return uVar2;
    }
  }
  return 0;
}


/* 004b8ec0 size=134 */

undefined4 FUN_004b8ec0(char *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  uVar4 = 0xffffffff;
  pcVar3 = param_1;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  if (0 < (int)(uVar4 - 1)) {
    iVar2 = FUN_00430de0(0xc);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 8) = 0;
      if (*(undefined **)(iVar2 + 8) != (undefined *)0x0) {
        FUN_00430df0(*(undefined **)(iVar2 + 8));
        *(undefined4 *)(iVar2 + 8) = 0;
      }
      pcVar3 = (char *)FUN_00430de0(uVar4);
      *(char **)(iVar2 + 8) = pcVar3;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)param_1;
        param_1 = param_1 + 4;
        pcVar3 = pcVar3 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar3 = *param_1;
        param_1 = param_1 + 1;
        pcVar3 = pcVar3 + 1;
      }
      return 1;
    }
  }
  return 0;
}


/* 004b8f50 size=70 */

void __fastcall FUN_004b8f50(int param_1)

{
  int *piVar1;
  
  while (piVar1 = *(int **)(param_1 + 0x20), piVar1 != (int *)0x0) {
    if ((int *)piVar1[1] == (int *)0x0) {
      *(int *)(param_1 + 0x20) = *piVar1;
    }
    else {
      *(int *)piVar1[1] = *piVar1;
    }
    if (*piVar1 == 0) {
      *(int *)(param_1 + 0x24) = piVar1[1];
    }
    else {
      *(int *)(*piVar1 + 4) = piVar1[1];
    }
    FUN_004b8fa0((int)piVar1);
    FUN_00430df0((undefined *)piVar1);
  }
  return;
}


/* 004b8fa0 size=28 */

void __fastcall FUN_004b8fa0(int param_1)

{
  if (*(undefined **)(param_1 + 8) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)(param_1 + 8));
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}


/* 004b8fc0 size=62 */

undefined4 __thiscall FUN_004b8fc0(void *this,byte *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  void *extraout_ECX;
  
  if ((param_1 != (byte *)0x0) && (*param_1 != 0)) {
    for (puVar1 = *(undefined4 **)((int)this + 0x20); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      uVar2 = FUN_004c4c00(this,(byte *)puVar1[2],param_1);
      if (uVar2 == 0) {
        return 1;
      }
      this = extraout_ECX;
    }
  }
  return 0;
}


/* 004b9000 size=1898 */

/* FUN_004b9000: lifted from original x86 -> lt_lifted.c */


/* 004b97d0 size=26 */

void __fastcall FUN_004b97d0(undefined4 *param_1)

{
  if ((undefined *)*param_1 != (undefined *)0x0) {
    FUN_00430df0((undefined *)*param_1);
    *param_1 = 0;
  }
  return;
}


/* 004b97f0 size=89 */

void FUN_004b97f0(void)

{
  size_t sVar1;
  int unaff_EBP;
  
  FUN_004bd77c();
  *(undefined1 *)(unaff_EBP + -0x20) = *(undefined1 *)(unaff_EBP + -0xd);
  FUN_00414100((void *)(unaff_EBP + -0x20),'\0');
  sVar1 = _strlen("string too long");
  FUN_0042f7f0((void *)(unaff_EBP + -0x20),(undefined4 *)"string too long",sVar1);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_004b984a();
  *(undefined ***)(unaff_EBP + -0x3c) = &PTR_LAB_004cefc0;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x3c,&DAT_004d2638);
}


/* 004b984a size=100 */

undefined4 * FUN_004b984a(void)

{
  undefined4 *this;
  undefined1 *puVar1;
  undefined4 *this_00;
  int unaff_EBP;
  
  FUN_004bd77c();
  *(undefined4 **)(unaff_EBP + -0x14) = this_00;
  *(undefined1 **)(unaff_EBP + -0x10) = &DAT_004e4424;
  FUN_004bcc9a(this_00,(undefined4 *)(unaff_EBP + -0x10));
  puVar1 = *(undefined1 **)(unaff_EBP + 8);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  this = this_00 + 3;
  *(undefined1 *)this = *puVar1;
  FUN_00414100(this,'\0');
  FUN_0042fc30(this,puVar1,0,DAT_004cc284);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  *this_00 = &PTR_FUN_004cefe0;
  return this_00;
}


/* 004b98bb size=29 */

void FUN_004b98bb(void)

{
  undefined1 local_20 [28];
  
  FUN_004b9931();
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_20,&DAT_004d26a8);
}


/* 004b98d8 size=61 */

void FUN_004b98d8(void)

{
  exception *this;
  int unaff_EBP;
  
  FUN_004bd77c();
  *(exception **)(unaff_EBP + -0x10) = this;
  *(undefined ***)this = &PTR_FUN_004cefe0;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_00414100(this + 0xc,'\x01');
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  exception__dtor_exception(this);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}


/* 004b9915 size=28 */

undefined * __thiscall FUN_004b9915(void *this,byte param_1)

{
  FUN_004b98d8();
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004b9931 size=93 */

undefined4 * FUN_004b9931(void)

{
  undefined4 *this;
  undefined1 uVar1;
  int iVar2;
  undefined4 *this_00;
  int unaff_EBP;
  
  FUN_004bd77c();
  iVar2 = *(int *)(unaff_EBP + 8);
  *(undefined4 **)(unaff_EBP + -0x10) = this_00;
  FUN_004bccd7(this_00,iVar2);
  uVar1 = *(undefined1 *)(iVar2 + 0xc);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  this = this_00 + 3;
  *(undefined1 *)this = uVar1;
  FUN_00414100(this,'\0');
  FUN_0042fc30(this,(void *)(iVar2 + 0xc),0,DAT_004cc284);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  *this_00 = &PTR_FUN_004cefe0;
  return this_00;
}


/* 004b998e size=61 */

void FUN_004b998e(void)

{
  exception *this;
  int unaff_EBP;
  
  FUN_004bd77c();
  *(exception **)(unaff_EBP + -0x10) = this;
  *(undefined ***)this = &PTR_FUN_004cefe0;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_00414100(this + 0xc,'\x01');
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  exception__dtor_exception(this);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}


/* 004b99cb size=29 */

void FUN_004b99cb(void)

{
  undefined4 local_20 [7];
  
  FUN_004b9a04(local_20);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_20,&DAT_004d2638);
}


/* 004b9a04 size=24 */

undefined4 * __fastcall FUN_004b9a04(undefined4 *param_1)

{
  FUN_004b9931();
  *param_1 = &PTR_LAB_004cefc0;
  return param_1;
}


/* 004b9a1c size=89 */

void FUN_004b9a1c(void)

{
  size_t sVar1;
  int unaff_EBP;
  
  FUN_004bd77c();
  *(undefined1 *)(unaff_EBP + -0x20) = *(undefined1 *)(unaff_EBP + -0xd);
  FUN_00414100((void *)(unaff_EBP + -0x20),'\0');
  sVar1 = _strlen("invalid string position");
  FUN_0042f7f0((void *)(unaff_EBP + -0x20),(undefined4 *)"invalid string position",sVar1);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_004b984a();
  *(undefined ***)(unaff_EBP + -0x3c) = &PTR_LAB_004ceff0;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x3c,&DAT_004d2760);
}


/* 004b9a76 size=61 */

void FUN_004b9a76(void)

{
  exception *this;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  
  FUN_004bd77c();
  *(exception **)(unaff_EBP + -0x10) = this;
  *(undefined ***)this = &PTR_FUN_004cefe0;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_00414100(this + 0xc,'\x01');
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  exception__dtor_exception(this);
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0xc);
  return;
}


/* 004b9ab3 size=29 */

void FUN_004b9ab3(void)

{
  undefined4 local_20 [7];
  
  FUN_004b9aec(local_20);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_20,&DAT_004d2760);
}


/* 004b9aec size=24 */

undefined4 * __fastcall FUN_004b9aec(undefined4 *param_1)

{
  FUN_004b9931();
  *param_1 = &PTR_LAB_004ceff0;
  return param_1;
}


/* 004b9b04 size=8 */

void __fastcall FUN_004b9b04(void *param_1)

{
  FUN_00414100(param_1,'\x01');
  return;
}


/* 004b9b36 size=12 */

void FUN_004b9b36(void)

{
  FUN_004b9cf5(FUN_004a82f0);
  return;
}


/* 004b9b42 size=12 */

void FUN_004b9b42(void)

{
  FUN_004b9cf5(&DAT_004b9b4e);
  return;
}


/* 004b9b4f size=126 */

undefined4 __fastcall FUN_004b9b4f(undefined4 param_1)

{
  LONG LVar1;
  
  if (DAT_004ecc78 != 2) {
    if (DAT_004ecc78 == 0) {
      LVar1 = InterlockedExchange(&DAT_004ecc78,1);
      if (LVar1 == 0) {
        InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_004ecc60);
        FUN_004b9cf5(&LAB_004b9bcd);
        DAT_004ecc78 = 2;
        goto LAB_004b9bc1;
      }
      if (LVar1 == 2) {
        DAT_004ecc78 = 2;
      }
    }
    while (DAT_004ecc78 == 1) {
      Sleep(1);
    }
    if (DAT_004ecc78 != 2) {
      return param_1;
    }
  }
LAB_004b9bc1:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004ecc60);
  return param_1;
}


/* 004b9beb size=21 */

void FUN_004b9beb(void)

{
  if (DAT_004ecc78 == 2) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004ecc60);
  }
  return;
}


/* 004b9c00 size=23 */

void FUN_004b9c00(void)

{
  void *extraout_ECX;
  
  FUN_004b9c18();
  DAT_004ecc80 = FUN_004bdb25();
  FUN_004bdad5(extraout_ECX);
  return;
}


/* 004b9c17 size=1 */

void FUN_004b9c17(void)

{
  return;
}


/* 004b9c18 size=56 */

void FUN_004b9c18(void)

{
  PTR_FUN_004e1114 = &LAB_004bdba8;
  PTR_FUN_004e1110 = __cfltcvt;
  PTR_FUN_004e1118 = __fassign;
  PTR_FUN_004e111c = FUN_004bdb4e;
  PTR_FUN_004e1120 = &LAB_004bdbf6;
  PTR_FUN_004e1124 = __cfltcvt;
  return;
}


/* 004b9c77 size=126 */

undefined4 __cdecl FUN_004b9c77(undefined4 param_1)

{
  byte *pbVar1;
  SIZE_T SVar2;
  
  FUN_004ba0a8();
  pbVar1 = (byte *)FUN_004be2a3(DAT_004ee3f4);
  if (pbVar1 < DAT_004ee3f0 + (4 - (int)DAT_004ee3f4)) {
    SVar2 = FUN_004be2a3(DAT_004ee3f4);
    pbVar1 = FUN_004bdf74(DAT_004ee3f4,(uint *)(SVar2 + 0x10));
    if (pbVar1 == (byte *)0x0) {
      param_1 = 0;
      goto LAB_004b9cec;
    }
    DAT_004ee3f0 = pbVar1 + ((int)DAT_004ee3f0 - (int)DAT_004ee3f4 >> 2) * 4;
    DAT_004ee3f4 = pbVar1;
  }
  *(undefined4 *)DAT_004ee3f0 = param_1;
  DAT_004ee3f0 = DAT_004ee3f0 + 4;
LAB_004b9cec:
  FUN_004ba0b1();
  return param_1;
}


/* 004b9cf5 size=18 */

int __cdecl FUN_004b9cf5(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_004b9c77(param_1);
  return (iVar1 != 0) - 1;
}


/* 004b9d3f size=215 */

void __cdecl FUN_004b9d3f(undefined *param_1)

{
  uint *puVar1;
  int local_2c;
  uint *local_28;
  uint local_24;
  uint *local_20;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf018;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  if (param_1 == (undefined *)0x0) {
    return;
  }
  if (DAT_004ed3c4 == 3) {
    ExceptionList = &local_14;
    FUN_004bf7a0(9);
    local_8 = 0;
    local_20 = (uint *)FUN_004be5ab((int)param_1);
    if (local_20 != (uint *)0x0) {
      FUN_004be5d6(local_20,(int)param_1);
    }
    local_8 = 0xffffffff;
    FUN_004b9da9();
    puVar1 = local_20;
  }
  else {
    ExceptionList = &local_14;
    if (DAT_004ed3c4 != 2) goto LAB_004b9e0b;
    ExceptionList = &local_14;
    FUN_004bf7a0(9);
    local_8 = 1;
    local_28 = (uint *)FUN_004bf306(param_1,&local_2c,&local_24);
    if (local_28 != (uint *)0x0) {
      FUN_004bf35d(local_2c,local_24,(byte *)local_28);
    }
    local_8 = 0xffffffff;
    FUN_004b9e01();
    puVar1 = local_28;
  }
  if (puVar1 != (uint *)0x0) {
    ExceptionList = local_14;
    return;
  }
LAB_004b9e0b:
  HeapFree(DAT_004ed3c0,0,param_1);
  ExceptionList = local_14;
  return;
}


/* 004b9da9 size=9 */

void FUN_004b9da9(void)

{
  FUN_004bf801(9);
  return;
}


/* 004b9e01 size=9 */

void FUN_004b9e01(void)

{
  FUN_004bf801(9);
  return;
}


/* 004b9e66 size=231 */

int __cdecl FUN_004b9e66(uint *param_1)

{
  int *piVar1;
  uint dwBytes;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf030;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  if (DAT_004ed3c4 == 3) {
    ExceptionList = &local_14;
    if (param_1 <= DAT_004ed3bc) {
      ExceptionList = &local_14;
      FUN_004bf7a0(9);
      local_8 = 0;
      piVar1 = FUN_004be8ff(param_1);
      local_8 = 0xffffffff;
      FUN_004b9ecd();
      if (piVar1 != (int *)0x0) {
        ExceptionList = local_14;
        return;
      }
    }
  }
  else {
    ExceptionList = &local_14;
    if (DAT_004ed3c4 == 2) {
      if (param_1 == (uint *)0x0) {
        dwBytes = 0x10;
      }
      else {
        dwBytes = (int)param_1 + 0xfU & 0xfffffff0;
      }
      ExceptionList = &local_14;
      if (dwBytes <= DAT_004e3154) {
        ExceptionList = &local_14;
        FUN_004bf7a0(9);
        local_8 = 1;
        piVar1 = FUN_004bf3a2(dwBytes >> 4);
        local_8 = 0xffffffff;
        FUN_004b9f2c();
        if (piVar1 != (int *)0x0) {
          ExceptionList = local_14;
          return;
        }
      }
      goto LAB_004b9f45;
    }
  }
  if (param_1 == (uint *)0x0) {
    param_1 = (uint *)0x1;
  }
  dwBytes = (int)param_1 + 0xfU & 0xfffffff0;
LAB_004b9f45:
  HeapAlloc(DAT_004ed3c0,0,dwBytes);
  ExceptionList = local_14;
  return;
}


/* 004b9ecd size=9 */

void FUN_004b9ecd(void)

{
  FUN_004bf801(9);
  return;
}


/* 004b9f2c size=9 */

void FUN_004b9f2c(void)

{
  FUN_004bf801(9);
  return;
}


/* 004b9f62 size=82 */

int __cdecl FUN_004b9f62(undefined1 *param_1,byte *param_2,undefined4 param_3)

{
  int iVar1;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  local_1c = param_1;
  local_24 = param_1;
  local_18 = 0x42;
  local_20 = 0x7fffffff;
  iVar1 = FUN_004bf92e((int *)&local_24,param_2,&param_3);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_004bf816(0,(int *)&local_24);
  }
  else {
    *local_24 = 0;
  }
  return iVar1;
}


/* 004b9fb4 size=45 */

void FUN_004b9fb4(void)

{
  if (PTR_FUN_004e0dc0 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004e0dc0)();
  }
  FUN_004ba0ba((undefined4 *)&DAT_004d5280,(undefined4 *)&DAT_004d5294);
  FUN_004ba0ba((undefined4 *)&DAT_004d5000,(undefined4 *)&DAT_004d527c);
  return;
}


/* 004b9fe1 size=17 */

void __cdecl FUN_004b9fe1(UINT param_1)

{
  FUN_004ba003(param_1,0,0);
  return;
}


/* 004ba003 size=163 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_004ba003(UINT param_1,int param_2,int param_3)

{
  HANDLE hProcess;
  undefined4 *puVar1;
  UINT uExitCode;
  
  FUN_004ba0a8();
  if (DAT_004eccc4 == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_004eccc0 = 1;
  DAT_004eccbc = (undefined1)param_3;
  if (param_2 == 0) {
    if ((DAT_004ee3f4 != (undefined4 *)0x0) &&
       (puVar1 = (undefined4 *)(DAT_004ee3f0 - 4), DAT_004ee3f4 <= puVar1)) {
      do {
        if ((code *)*puVar1 != (code *)0x0) {
          (*(code *)*puVar1)();
        }
        puVar1 = puVar1 + -1;
      } while (DAT_004ee3f4 <= puVar1);
    }
    FUN_004ba0ba((undefined4 *)&DAT_004d5298,(undefined4 *)&DAT_004d52a4);
  }
  FUN_004ba0ba((undefined4 *)&DAT_004d52a8,(undefined4 *)&DAT_004d52b0);
  if (param_3 == 0) {
    DAT_004eccc4 = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(param_1);
  }
  FUN_004ba0b1();
  return;
}


/* 004ba0a8 size=9 */

void FUN_004ba0a8(void)

{
  FUN_004bf7a0(0xd);
  return;
}


/* 004ba0b1 size=9 */

void FUN_004ba0b1(void)

{
  FUN_004bf801(0xd);
  return;
}


/* 004ba0ba size=26 */

void __cdecl FUN_004ba0ba(undefined4 *param_1,undefined4 *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((code *)*param_1 != (code *)0x0) {
      (*(code *)*param_1)();
    }
  }
  return;
}


/* 004ba14f size=49 */

undefined4 __cdecl FUN_004ba14f(FILE *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffffff;
  if ((param_1->_flag & 0x40) == 0) {
    FUN_004bcfa5((uint)param_1);
    uVar1 = __fclose_lk(param_1);
    FUN_004bcff7((uint)param_1);
  }
  else {
    param_1->_flag = 0;
  }
  return uVar1;
}


/* 004ba1cc size=49 */

undefined4 * __cdecl FUN_004ba1cc(LPCSTR param_1,char *param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = FUN_004c03b3();
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  puVar2 = FUN_004c0243(param_1,param_2,param_3,puVar1);
  FUN_004bcff7((uint)puVar1);
  return puVar2;
}


/* 004ba1fd size=19 */

int __cdecl FUN_004ba1fd(LPCSTR param_1,char *param_2)

{
  FUN_004ba1cc(param_1,param_2,0x40);
  return;
}


/* 004ba43e size=164 */

uint __cdecl FUN_004ba43e(byte *param_1,byte *param_2)

{
  byte bVar1;
  DWORD *pDVar2;
  int iVar3;
  byte *pbVar4;
  byte local_24 [32];
  
  pDVar2 = FUN_004c04e2();
  pbVar4 = local_24;
  for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
    pbVar4[0] = 0;
    pbVar4[1] = 0;
    pbVar4[2] = 0;
    pbVar4[3] = 0;
    pbVar4 = pbVar4 + 4;
  }
  do {
    bVar1 = *param_2;
    local_24[bVar1 >> 3] = local_24[bVar1 >> 3] | '\x01' << (bVar1 & 7);
    param_2 = param_2 + 1;
  } while (bVar1 != 0);
  if (param_1 == (byte *)0x0) {
    param_1 = (byte *)pDVar2[6];
  }
  for (; (bVar1 = *param_1, pbVar4 = param_1, (local_24[bVar1 >> 3] & (byte)(1 << (bVar1 & 7))) != 0
         && (bVar1 != 0)); param_1 = param_1 + 1) {
  }
  do {
    bVar1 = *pbVar4;
    if (bVar1 == 0) {
LAB_004ba4cd:
      pDVar2[6] = (DWORD)pbVar4;
      return -(uint)(param_1 != pbVar4) & (uint)param_1;
    }
    if ((local_24[bVar1 >> 3] & (byte)(1 << (bVar1 & 7))) != 0) {
      *pbVar4 = 0;
      pbVar4 = pbVar4 + 1;
      goto LAB_004ba4cd;
    }
    pbVar4 = pbVar4 + 1;
  } while( true );
}


/* 004ba4e2 size=98 */

char * __cdecl FUN_004ba4e2(char *param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  uint uVar2;
  char *pcVar3;
  
  if (param_2 < 1) {
    param_1 = (char *)0x0;
  }
  else {
    FUN_004bcfa5((uint)param_3);
    pcVar3 = param_1;
    do {
      param_2 = param_2 + -1;
      if (param_2 == 0) break;
      piVar1 = param_3 + 1;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 < 0) {
        uVar2 = FUN_004c05e9(param_3);
      }
      else {
        uVar2 = (uint)*(byte *)*param_3;
        *param_3 = (byte *)*param_3 + 1;
      }
      if (uVar2 == 0xffffffff) {
        if (pcVar3 == param_1) {
          param_1 = (char *)0x0;
          goto LAB_004ba536;
        }
        break;
      }
      *pcVar3 = (char)uVar2;
      pcVar3 = pcVar3 + 1;
    } while ((char)uVar2 != '\n');
    *pcVar3 = '\0';
LAB_004ba536:
    FUN_004bcff7((uint)param_3);
  }
  return param_1;
}


/* 004ba544 size=100 */

void __cdecl FUN_004ba544(int *param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  uVar1 = param_1[4];
  FUN_004bcfa5((uint)param_1);
  FUN_004bbef2(param_1);
  param_1[3] = param_1[3] & 0xffffffcf;
  if (uVar1 == 0xffffffff) {
    puVar2 = &DAT_004e3228;
  }
  else {
    puVar2 = (undefined *)((&DAT_004ed2a0)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 0x24);
  }
  puVar2[4] = puVar2[4] & 0xfd;
  if ((param_1[3] & 0x80U) != 0) {
    param_1[3] = param_1[3] & 0xfffffffc;
  }
  FUN_004c06c5(uVar1,0,0);
  FUN_004bcff7((uint)param_1);
  return;
}


/* 004ba5a8 size=34 */

int __cdecl FUN_004ba5a8(char *param_1)

{
  int iVar1;
  
  FUN_004bcfa5((uint)param_1);
  iVar1 = FUN_004ba5ca(param_1);
  FUN_004bcff7((uint)param_1);
  return iVar1;
}


/* 004ba5ca size=353 */

int __cdecl FUN_004ba5ca(char *param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  DWORD *pDVar4;
  char *pcVar5;
  DWORD DVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  int iVar10;
  int local_c;
  DWORD local_8;
  
  pcVar8 = param_1;
  uVar1 = *(uint *)(param_1 + 0x10);
  if (*(int *)(param_1 + 4) < 0) {
    param_1[4] = '\0';
    param_1[5] = '\0';
    param_1[6] = '\0';
    param_1[7] = '\0';
  }
  local_8 = FUN_004c06c5(uVar1,0,1);
  if ((int)local_8 < 0) {
LAB_004ba658:
    local_c = -1;
  }
  else {
    uVar2 = *(uint *)(param_1 + 0xc);
    if ((uVar2 & 0x108) == 0) {
      return local_8 - *(int *)(param_1 + 4);
    }
    pcVar5 = *(char **)param_1;
    pcVar7 = *(char **)(param_1 + 8);
    local_c = (int)pcVar5 - (int)pcVar7;
    if ((uVar2 & 3) == 0) {
      if ((uVar2 & 0x80) == 0) {
        pDVar4 = FUN_004c09cc();
        *pDVar4 = 0x16;
        goto LAB_004ba658;
      }
    }
    else if ((*(byte *)((&DAT_004ed2a0)[(int)uVar1 >> 5] + 4 + (uVar1 & 0x1f) * 0x24) & 0x80) != 0)
    {
      for (pcVar9 = pcVar7; pcVar9 < pcVar5; pcVar9 = pcVar9 + 1) {
        if (*pcVar9 == '\n') {
          local_c = local_c + 1;
        }
      }
    }
    if (local_8 != 0) {
      if ((param_1[0xc] & 1U) != 0) {
        if (*(int *)(param_1 + 4) == 0) {
          local_c = 0;
        }
        else {
          pcVar5 = pcVar5 + (*(int *)(param_1 + 4) - (int)pcVar7);
          iVar10 = (uVar1 & 0x1f) * 0x24;
          if ((*(byte *)(iVar10 + 4 + (&DAT_004ed2a0)[(int)uVar1 >> 5]) & 0x80) != 0) {
            DVar6 = FUN_004c06c5(uVar1,0,2);
            if (DVar6 == local_8) {
              pcVar7 = *(char **)(param_1 + 8);
              pcVar9 = pcVar5 + (int)pcVar7;
              param_1 = pcVar5;
              for (; pcVar7 < pcVar9; pcVar7 = pcVar7 + 1) {
                if (*pcVar7 == '\n') {
                  param_1 = param_1 + 1;
                }
              }
              bVar3 = pcVar8[0xd] & 0x20;
            }
            else {
              FUN_004c06c5(uVar1,local_8,0);
              pcVar8 = (char *)0x200;
              if ((((char *)0x200 < pcVar5) || ((*(uint *)(param_1 + 0xc) & 8) == 0)) ||
                 ((*(uint *)(param_1 + 0xc) & 0x400) != 0)) {
                pcVar8 = *(char **)(param_1 + 0x18);
              }
              bVar3 = *(byte *)(iVar10 + 4 + (&DAT_004ed2a0)[(int)uVar1 >> 5]) & 4;
              param_1 = pcVar8;
            }
            pcVar5 = param_1;
            if (bVar3 != 0) {
              pcVar5 = param_1 + 1;
            }
          }
          param_1 = pcVar5;
          local_8 = local_8 - (int)param_1;
        }
      }
      local_c = local_c + local_8;
    }
  }
  return local_c;
}


/* 004ba72b size=44 */

int __cdecl FUN_004ba72b(int *param_1,int param_2,DWORD param_3)

{
  int iVar1;
  
  FUN_004bcfa5((uint)param_1);
  iVar1 = FUN_004ba757(param_1,param_2,param_3);
  FUN_004bcff7((uint)param_1);
  return iVar1;
}


/* 004ba757 size=141 */

int __cdecl FUN_004ba757(int *param_1,int param_2,DWORD param_3)

{
  uint uVar1;
  int iVar2;
  DWORD DVar3;
  DWORD *pDVar4;
  
  if (((param_1[3] & 0x83U) == 0) || (((param_3 != 0 && (param_3 != 1)) && (param_3 != 2)))) {
    pDVar4 = FUN_004c09cc();
    *pDVar4 = 0x16;
    iVar2 = -1;
  }
  else {
    param_1[3] = param_1[3] & 0xffffffef;
    if (param_3 == 1) {
      iVar2 = FUN_004ba5ca((char *)param_1);
      param_2 = param_2 + iVar2;
      param_3 = 0;
    }
    FUN_004bbef2(param_1);
    uVar1 = param_1[3];
    if ((uVar1 & 0x80) == 0) {
      if ((((uVar1 & 1) != 0) && ((uVar1 & 8) != 0)) && ((uVar1 & 0x400) == 0)) {
        param_1[6] = 0x200;
      }
    }
    else {
      param_1[3] = uVar1 & 0xfffffffc;
    }
    DVar3 = FUN_004c06c5(param_1[4],param_2,param_3);
    iVar2 = (DVar3 != 0xffffffff) - 1;
  }
  return iVar2;
}


/* 004ba7f0 size=47 */

/* WARNING: Unable to track spacebase fully for stack */

void __cdecl FUN_004ba7f0(undefined1 param_1)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  puVar1 = &param_1;
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}


/* 004ba8f6 size=24 */

void FUN_004ba8f6(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_004e0dd8 = *(undefined4 *)(unaff_EBP + 8);
  DAT_004e0dd4 = in_EAX;
  DAT_004e0ddc = unaff_EBP;
  return;
}


/* 004ba9d5 size=27 */

void FUN_004ba9d5(int param_1)

{
  __local_unwind2(*(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
  return;
}


/* 004ba9f0 size=207 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_004ba9f0(double param_1)

{
  double dVar1;
  uint uVar2;
  int iVar3;
  float10 fVar4;
  uint uVar5;
  
  uVar2 = FUN_004c1209();
  if (((*(uint16_t*)((char*)&param_1+6)) & 0x7ff0) == 0x7ff0) {
    iVar3 = FUN_004c10d1(SUB84(param_1,0),(uint)((ulonglong)param_1 >> 0x20));
    if (0 < iVar3) {
      if (iVar3 < 3) {
        FUN_004c1209();
        return (float10)param_1;
      }
      if (iVar3 == 3) {
        fVar4 = FUN_004c09de(0xb,param_1);
        return fVar4;
      }
    }
    dVar1 = param_1 + _DAT_004cc808;
    uVar5 = 8;
  }
  else {
    fVar4 = __frnd(param_1);
    dVar1 = (double)fVar4;
    if ((dVar1 == param_1) || ((uVar2 & 0x20) != 0)) {
      FUN_004c1209();
      return (float10)dVar1;
    }
    uVar5 = 0x10;
  }
  fVar4 = FUN_004c0a32(uVar5,0xb,param_1,dVar1,uVar2);
  return fVar4;
}


/* 004baabf size=80 */

int __cdecl FUN_004baabf(undefined1 *param_1,int param_2,byte *param_3,undefined4 *param_4)

{
  int iVar1;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  local_1c = param_1;
  local_24 = param_1;
  local_20 = param_2;
  local_18 = 0x42;
  iVar1 = FUN_004bf92e((int *)&local_24,param_3,param_4);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_004bf816(0,(int *)&local_24);
  }
  else {
    *local_24 = 0;
  }
  return iVar1;
}


/* 004bab10 size=664 */

undefined4 * __cdecl FUN_004bab10(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    puVar3 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar4 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = param_3 >> 2;
      uVar2 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return param_1;
        case 2:
          goto switchD_004bacc7_caseD_2;
        case 3:
          goto switchD_004bacc7_caseD_3;
        }
        goto switchD_004bacc7_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_004bacc7_caseD_0;
      case 1:
        goto switchD_004bacc7_caseD_1;
      case 2:
        goto switchD_004bacc7_caseD_2;
      case 3:
        goto switchD_004bacc7_caseD_3;
      default:
        uVar1 = param_3 - ((uint)puVar4 & 3);
        switch((uint)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          puVar3 = (undefined4 *)((int)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (undefined4 *)((int)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_004bacc7_caseD_2;
            case 3:
              goto switchD_004bacc7_caseD_3;
            }
            goto switchD_004bacc7_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          puVar3 = (undefined4 *)((int)puVar3 + -2);
          puVar4 = (undefined4 *)((int)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_004bacc7_caseD_2;
            case 3:
              goto switchD_004bacc7_caseD_3;
            }
            goto switchD_004bacc7_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + -3);
          puVar4 = (undefined4 *)((int)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_004bacc7_caseD_2;
            case 3:
              goto switchD_004bacc7_caseD_3;
            }
            goto switchD_004bacc7_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_004bacc7_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return param_1;
    case 2:
switchD_004bacc7_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return param_1;
    case 3:
switchD_004bacc7_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return param_1;
    }
switchD_004bacc7_caseD_0:
    return param_1;
  }
  puVar3 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    uVar2 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *param_2;
        param_2 = param_2 + 1;
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return param_1;
      case 2:
        goto switchD_004bab45_caseD_2;
      case 3:
        goto switchD_004bab45_caseD_3;
      }
      goto switchD_004bab45_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_004bab45_caseD_0;
    case 1:
      goto switchD_004bab45_caseD_1;
    case 2:
      goto switchD_004bab45_caseD_2;
    case 3:
      goto switchD_004bab45_caseD_3;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar3 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_004bab45_caseD_2;
          case 3:
            goto switchD_004bab45_caseD_3;
          }
          goto switchD_004bab45_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar3 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_004bab45_caseD_2;
          case 3:
            goto switchD_004bab45_caseD_3;
          }
          goto switchD_004bab45_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_004bab45_caseD_2;
          case 3:
            goto switchD_004bab45_caseD_3;
          }
          goto switchD_004bab45_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar3[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar3[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar3[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar3[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar3[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar3[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_004bab45_caseD_1:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    return param_1;
  case 2:
switchD_004bab45_caseD_2:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
switchD_004bab45_caseD_3:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
switchD_004bab45_caseD_0:
  return param_1;
}


/* 004bae50 size=133 */

uint * __cdecl FUN_004bae50(uint *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  uint *puVar4;
  uint uVar5;
  char cVar6;
  uint uVar7;
  char *pcVar8;
  uint uVar9;
  uint *puVar10;
  
  cVar3 = *param_2;
  if (cVar3 == '\0') {
    return param_1;
  }
  if (param_2[1] == '\0') {
    while (((uint)param_1 & 3) != 0) {
      uVar5 = *param_1;
      if ((char)uVar5 == cVar3) {
        return param_1;
      }
      param_1 = (uint *)((int)param_1 + 1);
      if ((char)uVar5 == '\0') {
        return (uint *)0x0;
      }
    }
    while( true ) {
      while( true ) {
        uVar5 = *param_1;
        uVar9 = uVar5 ^ CONCAT22(CONCAT11(cVar3,cVar3),CONCAT11(cVar3,cVar3));
        uVar7 = uVar5 ^ 0xffffffff ^ uVar5 + 0x7efefeff;
        puVar10 = param_1 + 1;
        if (((uVar9 ^ 0xffffffff ^ uVar9 + 0x7efefeff) & 0x81010100) != 0) break;
        param_1 = puVar10;
        if ((uVar7 & 0x81010100) != 0) {
          if ((uVar7 & 0x1010100) != 0) {
            return (uint *)0x0;
          }
          if ((uVar5 + 0x7efefeff & 0x80000000) == 0) {
            return (uint *)0x0;
          }
        }
      }
      uVar5 = *param_1;
      if ((char)uVar5 == cVar3) {
        return param_1;
      }
      if ((char)uVar5 == '\0') {
        return (uint *)0x0;
      }
      cVar6 = (char)(uVar5 >> 8);
      if (cVar6 == cVar3) {
        return (uint *)((int)param_1 + 1);
      }
      if (cVar6 == '\0') {
        return (uint *)0x0;
      }
      cVar6 = (char)(uVar5 >> 0x10);
      if (cVar6 == cVar3) {
        return (uint *)((int)param_1 + 2);
      }
      if (cVar6 == '\0') break;
      cVar6 = (char)(uVar5 >> 0x18);
      if (cVar6 == cVar3) {
        return (uint *)((int)param_1 + 3);
      }
      param_1 = puVar10;
      if (cVar6 == '\0') {
        return (uint *)0x0;
      }
    }
    return (uint *)0x0;
  }
  do {
    cVar6 = (char)*param_1;
    do {
      while (puVar10 = param_1, param_1 = (uint *)((int)puVar10 + 1), cVar6 != cVar3) {
        if (cVar6 == '\0') {
          return (uint *)0x0;
        }
        cVar6 = *(char *)param_1;
      }
      cVar6 = *(char *)param_1;
      pcVar8 = param_2;
      puVar4 = puVar10;
    } while (cVar6 != param_2[1]);
    do {
      if (pcVar8[2] == '\0') {
        return puVar10;
      }
      if (*(char *)((int)puVar4 + 2) != pcVar8[2]) break;
      pcVar1 = pcVar8 + 3;
      if (*pcVar1 == '\0') {
        return puVar10;
      }
      pcVar2 = (char *)((int)puVar4 + 3);
      pcVar8 = pcVar8 + 2;
      puVar4 = (uint *)((int)puVar4 + 2);
    } while (*pcVar1 == *pcVar2);
  } while( true );
}


/* 004baed0 size=87 */

/* FUN_004baed0: lifted from original x86 -> lt_lifted.c */


/* 004baf27 size=40 */

/* FUN_004baf27: lifted from original x86 -> lt_lifted.c */


/* 004baf4f size=40 */

/* FUN_004baf4f: lifted from original x86 -> lt_lifted.c */


/* 004baf77 size=46 */

uint __thiscall FUN_004baf77(void *this,int param_1)

{
  uint uVar1;
  
  if (DAT_004e36dc < 2) {
    return *(ushort *)(PTR_DAT_004e34d0 + param_1 * 2) & 0x107;
  }
  uVar1 = FUN_004c1301(this,param_1,0x107);
  return uVar1;
}


/* 004bafa5 size=40 */

/* FUN_004bafa5: lifted from original x86 -> lt_lifted.c */


/* 004bafcd size=60 */

int __cdecl FUN_004bafcd(int *param_1,byte *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  FUN_004bcfa5((uint)param_1);
  iVar1 = FUN_004c1376(param_1);
  iVar2 = FUN_004bf92e(param_1,param_2,&param_3);
  FUN_004c1403(iVar1,param_1);
  FUN_004bcff7((uint)param_1);
  return iVar2;
}


/* 004bb020 size=188 */

uint * __cdecl FUN_004bb020(uint *param_1,char param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uint)param_1 & 3) != 0) {
    uVar1 = *param_1;
    if ((char)uVar1 == param_2) {
      return param_1;
    }
    param_1 = (uint *)((int)param_1 + 1);
    if ((char)uVar1 == '\0') {
      return (uint *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *param_1;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11(param_2,param_2),CONCAT11(param_2,param_2));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = param_1 + 1;
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      param_1 = puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (uint *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (uint *)0x0;
        }
      }
    }
    uVar1 = *param_1;
    if ((char)uVar1 == param_2) {
      return param_1;
    }
    if ((char)uVar1 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 1);
    }
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 3);
    }
    param_1 = puVar5;
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
  }
  return (uint *)0x0;
}


/* 004bb0dc size=139 */

/* FUN_004bb0dc: lifted from original x86 -> lt_lifted.c */


/* 004bb167 size=11 */

int __thiscall FUN_004bb167(void *this,byte *param_1)

{
  FUN_004bb0dc(this,param_1);
  return;
}


/* 004bb172 size=59 */

uint __cdecl FUN_004bb172(uint param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  
  FUN_004bcfa5((uint)param_2);
  piVar1 = param_2 + 1;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    uVar2 = FUN_004bf816(param_1,param_2);
  }
  else {
    uVar2 = param_1 & 0xff;
    *(undefined1 *)*param_2 = (undefined1)param_1;
    *param_2 = *param_2 + 1;
  }
  FUN_004bcff7((uint)param_2);
  return uVar2;
}


/* 004bb1ad size=78 */

int __cdecl FUN_004bb1ad(char *param_1,int *param_2)

{
  size_t sVar1;
  int iVar2;
  uint uVar3;
  
  sVar1 = _strlen(param_1);
  FUN_004bcfa5((uint)param_2);
  iVar2 = FUN_004c1376(param_2);
  uVar3 = FUN_004bb7ba(param_1,1,sVar1,param_2);
  FUN_004c1403(iVar2,param_2);
  FUN_004bcff7((uint)param_2);
  return (uVar3 == sVar1) - 1;
}


/* 004bb354 size=46 */

undefined4 __cdecl FUN_004bb354(int param_1,uint param_2)

{
  if (((((*(uint16_t*)((char*)&param_2+2)) & 0x7ff8) == 0x7ff0) && (((param_2 & 0x7ffff) != 0 || (param_1 != 0)))) ||
     (((*(uint16_t*)((char*)&param_2+2)) & 0x7ff8) == 0x7ff8)) {
    return 1;
  }
  return 0;
}


/* 004bb390 size=20 */

int FUN_004bb390(void)

{
  float10 in_ST0;
  double dVar1;
  
  dVar1 = (double)in_ST0;
  FUN_004c16e8(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  FUN_004bb3ad(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  return;
}


/* 004bb3ad size=174 */

void __cdecl FUN_004bb3ad(int param_1,uint param_2)

{
  uint in_EAX;
  bool in_ZF;
  ushort in_FPUControlWord;
  float10 in_ST0;
  float10 extraout_ST0;
  undefined4 unaff_retaddr;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) != 0) || (param_1 != 0)) {
      FUN_004c168c();
    }
LAB_004bb43c:
    if (DAT_004ecc7c == 0) {
      __startOneArgErrorHandling(&DAT_004e0df0,0xd,in_FPUControlWord,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      in_EAX = FUN_004c1675();
      in_ST0 = extraout_ST0;
    }
    if (in_EAX < 0x3ff00000) {
      fpatan(SQRT(((float10)1 - in_ST0) * ((float10)1 + in_ST0)),in_ST0);
    }
    else if ((0x3ff00000 < in_EAX) || ((param_2 & 0xfffff) != 0 || param_1 != 0)) goto LAB_004bb43c;
    if (DAT_004ecc7c == 0) {
      __math_exit(&DAT_004e0df0,0xd,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  return;
}


/* 004bb45b size=205 */

HANDLE __cdecl FUN_004bb45b(LPCSTR param_1,uint *param_2)

{
  HANDLE pvVar1;
  DWORD DVar2;
  DWORD *pDVar3;
  uint uVar4;
  _WIN32_FIND_DATAA local_144;
  
  pvVar1 = FindFirstFileA(param_1,&local_144);
  if (pvVar1 != (HANDLE)0xffffffff) {
    *param_2 = -(uint)(local_144.dwFileAttributes != 0x80) & local_144.dwFileAttributes;
    uVar4 = ___timet_from_ft(&local_144.ftCreationTime);
    param_2[1] = uVar4;
    uVar4 = ___timet_from_ft(&local_144.ftLastAccessTime);
    param_2[2] = uVar4;
    uVar4 = ___timet_from_ft(&local_144.ftLastWriteTime);
    param_2[3] = uVar4;
    param_2[4] = local_144.nFileSizeLow;
    FUN_004c17f0(param_2 + 5,(uint *)local_144.cFileName);
    return pvVar1;
  }
  DVar2 = GetLastError();
  if (DVar2 < 2) {
LAB_004bb499:
    pDVar3 = FUN_004c09cc();
    *pDVar3 = 0x16;
  }
  else {
    if (3 < DVar2) {
      if (DVar2 == 8) {
        pDVar3 = FUN_004c09cc();
        *pDVar3 = 0xc;
        return (HANDLE)0xffffffff;
      }
      if (DVar2 != 0x12) goto LAB_004bb499;
    }
    pDVar3 = FUN_004c09cc();
    *pDVar3 = 2;
  }
  return (HANDLE)0xffffffff;
}


/* 004bb528 size=200 */

undefined4 __cdecl FUN_004bb528(HANDLE param_1,uint *param_2)

{
  BOOL BVar1;
  DWORD DVar2;
  DWORD *pDVar3;
  uint uVar4;
  _WIN32_FIND_DATAA local_144;
  
  BVar1 = FindNextFileA(param_1,&local_144);
  if (BVar1 != 0) {
    *param_2 = -(uint)(local_144.dwFileAttributes != 0x80) & local_144.dwFileAttributes;
    uVar4 = ___timet_from_ft(&local_144.ftCreationTime);
    param_2[1] = uVar4;
    uVar4 = ___timet_from_ft(&local_144.ftLastAccessTime);
    param_2[2] = uVar4;
    uVar4 = ___timet_from_ft(&local_144.ftLastWriteTime);
    param_2[3] = uVar4;
    param_2[4] = local_144.nFileSizeLow;
    FUN_004c17f0(param_2 + 5,(uint *)local_144.cFileName);
    return 0;
  }
  DVar2 = GetLastError();
  if (DVar2 < 2) {
LAB_004bb562:
    pDVar3 = FUN_004c09cc();
    *pDVar3 = 0x16;
  }
  else {
    if (3 < DVar2) {
      if (DVar2 == 8) {
        pDVar3 = FUN_004c09cc();
        *pDVar3 = 0xc;
        return 0xffffffff;
      }
      if (DVar2 != 0x12) goto LAB_004bb562;
    }
    pDVar3 = FUN_004c09cc();
    *pDVar3 = 2;
  }
  return 0xffffffff;
}


/* 004bb5f0 size=32 */

undefined4 __cdecl FUN_004bb5f0(HANDLE param_1)

{
  BOOL BVar1;
  DWORD *pDVar2;
  
  BVar1 = FindClose(param_1);
  if (BVar1 == 0) {
    pDVar2 = FUN_004c09cc();
    *pDVar2 = 0x16;
    return 0xffffffff;
  }
  return 0;
}


/* 004bb674 size=47 */

uint __cdecl FUN_004bb674(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  FUN_004bcfa5((uint)param_4);
  uVar1 = FUN_004bb6a3(param_1,param_2,param_3,param_4);
  FUN_004bcff7((uint)param_4);
  return uVar1;
}


/* 004bb6a3 size=232 */

uint __cdecl FUN_004bb6a3(char *param_1,uint param_2,uint param_3,int *param_4)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  
  piVar1 = param_4;
  pcVar6 = (char *)(param_2 * param_3);
  if (pcVar6 == (char *)0x0) {
    return 0;
  }
  pcVar5 = param_1;
  param_1 = pcVar6;
  if ((*(ushort *)(param_4 + 3) & 0x10c) == 0) {
    param_4 = (int *)0x1000;
  }
  else {
    param_4 = (int *)param_4[6];
  }
  do {
    if (((*(ushort *)(piVar1 + 3) & 0x10c) == 0) ||
       (pcVar2 = (char *)piVar1[1], pcVar2 == (char *)0x0)) {
      if (param_1 < param_4) {
        uVar4 = FUN_004c05e9(piVar1);
        if (uVar4 == 0xffffffff) goto LAB_004bb77f;
        *pcVar5 = (char)uVar4;
        param_4 = (int *)piVar1[6];
        pcVar5 = pcVar5 + 1;
        param_1 = param_1 + -1;
      }
      else {
        pcVar2 = param_1;
        if (param_4 != (int *)0x0) {
          pcVar2 = param_1 + -((uint)param_1 % (uint)param_4);
        }
        iVar3 = FUN_004c19a2(piVar1[4],pcVar5,pcVar2);
        if (iVar3 == 0) {
          piVar1[3] = piVar1[3] | 0x10;
LAB_004bb77f:
          return (uint)((int)pcVar6 - (int)param_1) / param_2;
        }
        if (iVar3 == -1) {
          piVar1[3] = piVar1[3] | 0x20;
          goto LAB_004bb77f;
        }
        param_1 = param_1 + -iVar3;
        pcVar5 = pcVar5 + iVar3;
      }
    }
    else {
      pcVar7 = param_1;
      if (pcVar2 <= param_1) {
        pcVar7 = pcVar2;
      }
      FUN_004bd7a0((undefined4 *)pcVar5,(undefined4 *)*piVar1,(uint)pcVar7);
      param_1 = param_1 + -(int)pcVar7;
      piVar1[1] = piVar1[1] - (int)pcVar7;
      *piVar1 = (int)(pcVar7 + *piVar1);
      pcVar5 = pcVar5 + (int)pcVar7;
    }
    if (param_1 == (char *)0x0) {
      return param_3;
    }
  } while( true );
}


/* 004bb78b size=47 */

uint __cdecl FUN_004bb78b(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  FUN_004bcfa5((uint)param_4);
  uVar1 = FUN_004bb7ba(param_1,param_2,param_3,param_4);
  FUN_004bcff7((uint)param_4);
  return uVar1;
}


/* 004bb7ba size=266 */

uint __cdecl FUN_004bb7ba(char *param_1,uint param_2,uint param_3,int *param_4)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  
  piVar1 = param_4;
  piVar6 = (int *)(param_2 * param_3);
  if (piVar6 == (int *)0x0) {
    param_3 = 0;
  }
  else {
    piVar5 = piVar6;
    if ((*(ushort *)(param_4 + 3) & 0x10c) == 0) {
      param_4 = (int *)0x1000;
    }
    else {
      param_4 = (int *)param_4[6];
    }
    do {
      if (((piVar1[3] & 0x108U) == 0) || (piVar7 = (int *)piVar1[1], piVar7 == (int *)0x0)) {
        if (param_4 <= piVar5) {
          if (((piVar1[3] & 0x108U) != 0) && (iVar2 = FUN_004bbef2(piVar1), iVar2 != 0)) {
LAB_004bb8bb:
            return (uint)((int)piVar6 - (int)piVar5) / param_2;
          }
          if (param_4 == (int *)0x0) {
            piVar7 = piVar5;
          }
          else {
            piVar7 = (int *)((int)piVar5 - (uint)piVar5 % (uint)param_4);
          }
          piVar3 = (int *)FUN_004c1be0(piVar1[4],param_1,(DWORD)piVar7);
          if ((piVar3 == (int *)0xffffffff) ||
             (piVar5 = (int *)((int)piVar5 - (int)piVar3), piVar3 < piVar7)) {
            piVar1[3] = piVar1[3] | 0x20;
            goto LAB_004bb8bb;
          }
          goto LAB_004bb872;
        }
        uVar4 = FUN_004bf816((int)*param_1,piVar1);
        if (uVar4 == 0xffffffff) goto LAB_004bb8bb;
        param_1 = param_1 + 1;
        param_4 = (int *)piVar1[6];
        piVar5 = (int *)((int)piVar5 - 1);
        if ((int)param_4 < 1) {
          param_4 = (int *)0x1;
        }
      }
      else {
        piVar3 = piVar5;
        if (piVar7 <= piVar5) {
          piVar3 = piVar7;
        }
        FUN_004bd7a0((undefined4 *)*piVar1,(undefined4 *)param_1,(uint)piVar3);
        piVar1[1] = piVar1[1] - (int)piVar3;
        *piVar1 = *piVar1 + (int)piVar3;
        piVar5 = (int *)((int)piVar5 - (int)piVar3);
LAB_004bb872:
        param_1 = param_1 + (int)piVar3;
      }
    } while (piVar5 != (int *)0x0);
  }
  return param_3;
}


/* 004bb908 size=52 */

void __cdecl FUN_004bb908(char *param_1,byte *param_2,undefined4 param_3)

{
  void *this;
  char *local_24;
  size_t local_20;
  char *local_1c;
  undefined4 local_18;
  
  local_18 = 0x49;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = _strlen(param_1);
  FUN_004c1dd0(this,(int *)&local_24,param_2,&param_3);
  return;
}


/* 004bb93c size=45 */

void FUN_004bb93c(undefined *UNRECOVERED_JUMPTABLE)

{
  ExceptionList = *(void **)ExceptionList;
                    /* WARNING: Could not recover jumptable at 0x004bb967. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)UNRECOVERED_JUMPTABLE)();
  return;
}


/* 004bb970 size=7 */

void FUN_004bb970(undefined4 param_1,undefined *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x004bb975. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)UNRECOVERED_JUMPTABLE)();
  return;
}


/* 004bb977 size=7 */

void FUN_004bb977(undefined4 param_1,undefined *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x004bb97c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)UNRECOVERED_JUMPTABLE)();
  return;
}


/* 004bb97e size=79 */

void FUN_004bb97e(PVOID param_1,PEXCEPTION_RECORD param_2)

{
  void *pvVar1;
  
  pvVar1 = ExceptionList;
  RtlUnwind(param_1,(PVOID)0x4bb9a6,param_2,(PVOID)0x0);
  param_2->ExceptionFlags = param_2->ExceptionFlags & 0xfffffffd;
  *(void **)pvVar1 = ExceptionList;
  ExceptionList = pvVar1;
  return;
}


/* 004bb9cd size=54 */

undefined4 __cdecl
FUN_004bb9cd(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,undefined4 param_4)

{
  int *in_EAX;
  undefined4 uVar1;
  
  uVar1 = FUN_004c2881(param_1,param_2,param_3,param_4,in_EAX,0,(PVOID)0x0,'\0');
  return uVar1;
}


/* 004bba03 size=84 */

undefined4 __cdecl
FUN_004bba03(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  void *local_18;
  code *local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_10 = param_2;
  local_14 = FUN_004bba57;
  local_8 = param_4 + 1;
  local_c = param_1;
  local_18 = ExceptionList;
  ExceptionList = &local_18;
  uVar1 = __CallSettingFrame_12(param_3,param_1,param_5);
  ExceptionList = local_18;
  return uVar1;
}


/* 004bba57 size=37 */

void __cdecl FUN_004bba57(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3)

{
  FUN_004c2881(param_1,*(PVOID *)((int)param_2 + 0xc),param_3,0,*(int **)((int)param_2 + 8),
               *(int *)((int)param_2 + 0x10),param_2,'\0');
  return;
}


/* 004bba7c size=182 */

undefined4 __cdecl
FUN_004bba7c(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  DWORD *pDVar1;
  undefined1 auStackY_cc [128];
  undefined4 uVar2;
  undefined4 **ppuVar3;
  undefined4 *local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  code *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined1 *local_10;
  undefined1 *local_c;
  undefined4 local_8;
  
  local_c = auStackY_cc + 200;
  local_10 = auStackY_cc + 0x88;
  local_28 = FUN_004bbb32;
  local_24 = param_5;
  local_20 = param_2;
  local_1c = param_6;
  local_18 = param_7;
  local_8 = 0;
  local_14 = 0x4bbb04;
  local_2c = ExceptionList;
  ExceptionList = &local_2c;
  local_34 = param_1;
  local_30 = param_3;
  ppuVar3 = &local_34;
  uVar2 = *param_1;
  pDVar1 = FUN_004c04e2();
  (*(code *)pDVar1[0x1a])(uVar2,ppuVar3);
  if (local_8 != 0) {
    *local_2c = *(undefined4 *)ExceptionList;
  }
  ExceptionList = local_2c;
  return 0;
}


/* 004bbb32 size=114 */

undefined4 __cdecl FUN_004bbb32(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3)

{
  undefined4 uVar1;
  
  if ((param_1->ExceptionFlags & 0x66) != 0) {
    *(undefined4 *)((int)param_2 + 0x24) = 1;
    return 1;
  }
  FUN_004c2881(param_1,*(PVOID *)((int)param_2 + 0xc),param_3,0,*(int **)((int)param_2 + 8),
               *(int *)((int)param_2 + 0x10),*(PVOID *)((int)param_2 + 0x14),'\x01');
  if (*(int *)((int)param_2 + 0x24) == 0) {
    FUN_004bb97e(param_2,param_1);
  }
                    /* WARNING: Could not recover jumptable at 0x004bbb9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)((int)param_2 + 0x18))();
  return uVar1;
}


/* 004bbba7 size=123 */

int __cdecl FUN_004bbba7(uint param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint local_8;
  
  uVar2 = param_1;
  local_8 = *(uint *)(param_1 + 0xc);
  iVar1 = *(int *)(param_1 + 0x10);
  uVar3 = local_8;
  param_1 = local_8;
  if (-1 < param_2) {
    do {
      if (uVar3 == 0xffffffff) {
        FUN_004c314d();
      }
      uVar3 = uVar3 - 1;
      if (((*(int *)(iVar1 + 4 + uVar3 * 0x14) < param_3) &&
          (param_3 <= *(int *)(iVar1 + uVar3 * 0x14 + 8))) || (uVar3 == 0xffffffff)) {
        param_2 = param_2 + -1;
        local_8 = param_1;
        param_1 = uVar3;
      }
    } while (-1 < param_2);
  }
  uVar3 = uVar3 + 1;
  *param_4 = uVar3;
  *param_5 = local_8;
  if ((*(uint *)(uVar2 + 0xc) < local_8) || (local_8 < uVar3)) {
    FUN_004c314d();
  }
  return iVar1 + uVar3 * 0x14;
}


/* 004bbc22 size=36 */

undefined4 __cdecl FUN_004bbc22(undefined4 param_1)

{
  undefined4 uVar1;
  
  FUN_004bf7a0(9);
  uVar1 = DAT_004eccc8;
  DAT_004eccc8 = param_1;
  FUN_004bf801(9);
  return uVar1;
}


/* 004bbc46 size=27 */

/* FUN_004bbc46: lifted from original x86 -> lt_lifted.c */


/* 004bbc61 size=13 */

void __cdecl FUN_004bbc61(DWORD param_1)

{
  DWORD *pDVar1;
  
  pDVar1 = FUN_004c04e2();
  pDVar1[5] = param_1;
  return;
}


/* 004bbd09 size=81 */

int __cdecl FUN_004bbd09(undefined1 *param_1,byte *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  local_1c = param_1;
  local_24 = param_1;
  local_18 = 0x42;
  local_20 = 0x7fffffff;
  iVar1 = FUN_004bf92e((int *)&local_24,param_2,param_3);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_004bf816(0,(int *)&local_24);
  }
  else {
    *local_24 = 0;
  }
  return iVar1;
}


/* 004bbd5a size=111 */

uint __cdecl FUN_004bbd5a(uint param_1)

{
  void *extraout_ECX;
  bool bVar1;
  void *this;
  
  if (DAT_004ecd78 == 0) {
    if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
      return param_1 - 0x20;
    }
  }
  else {
    InterlockedIncrement((LONG *)&DAT_004ed28c);
    bVar1 = DAT_004ed288 != 0;
    this = extraout_ECX;
    if (bVar1) {
      InterlockedDecrement((LONG *)&DAT_004ed28c);
      this = (void *)0x13;
      FUN_004bf7a0(0x13);
    }
    param_1 = FUN_004bbdc9(this,param_1);
    if (bVar1) {
      FUN_004bf801(0x13);
    }
    else {
      InterlockedDecrement((LONG *)&DAT_004ed28c);
    }
  }
  return param_1;
}


/* 004bbdc9 size=204 */

/* FUN_004bbdc9: lifted from original x86 -> lt_lifted.c */


/* 004bbe95 size=47 */

int __cdecl FUN_004bbe95(int *param_1)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    iVar1 = FUN_004bbf57(0);
    return iVar1;
  }
  FUN_004bcfa5((uint)param_1);
  iVar1 = FUN_004bbec4(param_1);
  FUN_004bcff7((uint)param_1);
  return iVar1;
}


/* 004bbec4 size=46 */

int __cdecl FUN_004bbec4(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_004bbef2(param_1);
  if (iVar1 != 0) {
    return -1;
  }
  if ((*(byte *)((int)param_1 + 0xd) & 0x40) == 0) {
    return 0;
  }
  iVar1 = FUN_004c342c(param_1[4]);
  return -(uint)(iVar1 != 0);
}


/* 004bbef2 size=92 */

undefined4 __cdecl FUN_004bbef2(int *param_1)

{
  DWORD DVar1;
  undefined4 uVar2;
  DWORD DVar3;
  
  uVar2 = 0;
  if ((((byte)param_1[3] & 3) == 2) && ((param_1[3] & 0x108U) != 0)) {
    DVar3 = *param_1 - param_1[2];
    if (0 < (int)DVar3) {
      DVar1 = FUN_004c1be0(param_1[4],(char *)param_1[2],DVar3);
      if (DVar1 == DVar3) {
        if ((param_1[3] & 0x80U) != 0) {
          param_1[3] = param_1[3] & 0xfffffffd;
        }
      }
      else {
        param_1[3] = param_1[3] | 0x20;
        uVar2 = 0xffffffff;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return uVar2;
}


/* 004bbf57 size=164 */

int __cdecl FUN_004bbf57(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar5 = 0;
  FUN_004bf7a0(2);
  iVar4 = 0;
  if (0 < DAT_004ee3e0) {
    do {
      iVar2 = *(int *)(DAT_004ed3c8 + iVar4 * 4);
      if ((iVar2 != 0) && ((*(byte *)(iVar2 + 0xc) & 0x83) != 0)) {
        FUN_004bcfd4(iVar4,iVar2);
        piVar1 = *(int **)(DAT_004ed3c8 + iVar4 * 4);
        if ((piVar1[3] & 0x83U) != 0) {
          if (param_1 == 1) {
            iVar2 = FUN_004bbec4(piVar1);
            if (iVar2 != -1) {
              iVar3 = iVar3 + 1;
            }
          }
          else if ((param_1 == 0) && ((piVar1[3] & 2U) != 0)) {
            iVar2 = FUN_004bbec4(piVar1);
            if (iVar2 == -1) {
              iVar5 = -1;
            }
          }
        }
        FUN_004bd026(iVar4,*(int *)(DAT_004ed3c8 + iVar4 * 4));
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < DAT_004ee3e0);
  }
  FUN_004bf801(2);
  if (param_1 != 1) {
    iVar3 = iVar5;
  }
  return iVar3;
}


