/* lithtech.exe decompilation - unnamed_0040c000 */
#include "ghidra_types.h"

/* 0040c140 size=110 */

undefined4 __cdecl FUN_0040c140(int *param_1)

{
  if ((param_1 != (int *)0x0) && ((char)param_1[0x2f] == '\x06')) {
    FUN_0046c0d0((int)param_1);
    FUN_00427310(DAT_004e516c,param_1,(float *)(param_1 + 0x65),1);
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CLTClient__OptimizeParticles_004d618c);
  }
  return 0x3c;
}


/* 0040c870 size=127 */

undefined4 __thiscall FUN_0040c870(void *this,int param_1,int *param_2)

{
  int iVar1;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = (**(code **)(*param_2 + 4))(param_1 + *(int *)((int)this + 0x10));
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      *(int *)((int)this + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 0040c920 size=19 */

int __cdecl FUN_0040c920(int *param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)(*param_1 + 4))(param_3);
  return;
}


/* 0040c950 size=23 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040c950(void)

{
  _DAT_004e5118 = &PTR_LAB_004cbb1c;
  DAT_004e511c = 0;
  DAT_004e5120 = 0;
  return;
}


/* 0040c970 size=12 */

void FUN_0040c970(void)

{
  FUN_004b9cf5(&LAB_0040c980);
  return;
}


/* 0040c9e0 size=11 */

int FUN_0040c9e0(void)

{
  return DAT_004e516c + 0x1728;
}


/* 0040c9f0 size=301 */

int * __cdecl FUN_0040c9f0(uint param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iStack_4;
  
  if (((((param_1 == 0) || (param_2 == 0)) || (5000 < param_1)) ||
      ((5000 < param_2 || (DAT_004e5124 == 0)))) ||
     (iVar2 = (**(code **)(DAT_004e5124 + 0xd0))(param_1,param_2), iVar2 == 0)) {
    return (int *)0x0;
  }
  (**(code **)(DAT_004e5124 + 0xd8))(iVar2,&param_1,&param_2,&iStack_4);
  if ((DAT_004e4f98 != (int *)0x0) ||
     (FUN_004b7c60(0x4e4f80,DAT_004e4f88), piVar3 = DAT_004e4f98, DAT_004e4f98 != (int *)0x0)) {
    piVar3 = DAT_004e4f98;
    DAT_004e4f98 = (int *)*DAT_004e4f98;
  }
  piVar3[3] = iVar2;
  piVar3[2] = 0;
  piVar3[4] = param_1;
  piVar3[5] = param_2;
  piVar3[6] = iStack_4;
  piVar3[7] = 0;
  piVar3[9] = 0;
  piVar3[10] = 0x3f800000;
  piVar1 = DAT_004e5120;
  if (DAT_004e5120 == (int *)0x0) {
    piVar3[1] = (int)piVar3;
    *piVar3 = (int)piVar3;
    DAT_004e5120 = piVar3;
    DAT_004e511c = DAT_004e511c + 1;
    return piVar3;
  }
  *(int **)(*DAT_004e5120 + 4) = piVar3;
  *piVar3 = *piVar1;
  piVar3[1] = (int)piVar1;
  *piVar1 = (int)piVar3;
  DAT_004e511c = DAT_004e511c + 1;
  if ((int *)piVar3[1] == DAT_004e5120) {
    DAT_004e5120 = piVar3;
    return piVar3;
  }
  return piVar3;
}


/* 0040cb20 size=58 */

int * __cdecl FUN_0040cb20(int param_1)

{
  int *piVar1;
  
  piVar1 = FUN_0040c9f0(*(uint *)(param_1 + 0x438),*(uint *)(param_1 + 0x43c));
  if (piVar1 == (int *)0x0) {
    return (int *)0x0;
  }
  FUN_0040cb60((undefined *)piVar1,param_1,(int *)0x0,0,0);
  return piVar1;
}


/* 0040cb60 size=516 */

void __cdecl FUN_0040cb60(undefined *param_1,int param_2,int *param_3,int param_4,int param_5)

{
  int iVar1;
  void *this;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  uint local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  undefined *local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  undefined4 local_74;
  
  local_bc = 0;
  local_b8 = 0;
  local_b4 = 0;
  local_b0 = 0;
  local_ac = 0;
  local_a8 = 0;
  local_a4 = 0;
  local_a0 = 0;
  FUN_0046e390(&local_98);
  if (param_3 == (int *)0x0) {
    iVar3 = *(int *)(param_2 + 0x43c);
    iVar2 = *(int *)(param_2 + 0x438);
    iVar1 = *(int *)(param_1 + 0x14);
    iVar8 = *(int *)(param_1 + 0x10);
    iVar5 = 0;
    iVar4 = 0;
    iVar6 = iVar2;
    iVar7 = iVar3;
  }
  else {
    iVar1 = *(int *)(param_1 + 0x14);
    iVar8 = *(int *)(param_1 + 0x10);
    iVar5 = param_3[1];
    iVar4 = *param_3;
    iVar3 = *(int *)(param_2 + 0x43c);
    iVar2 = *(int *)(param_2 + 0x438);
    iVar6 = param_3[2];
    iVar7 = param_3[3];
  }
  FUN_00443ae0(iVar2,iVar3,iVar4,iVar5,iVar6,iVar7,iVar8,iVar1,param_4,param_5,&local_bc,&local_ac);
  if (DAT_004e5124 == 0) {
    local_9c = 0;
  }
  else {
    local_80 = 0;
    if (param_1 == &DAT_004e4fa0) {
      iVar1 = (**(code **)(DAT_004e5124 + 0xec))(0,0,DAT_004e4fb0,DAT_004e4fb4,&local_9c,&local_80);
      local_9c = -(uint)(iVar1 != 0) & local_9c;
    }
    else {
      local_80 = *(int *)(param_1 + 0x18);
      local_9c = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_1 + 0xc));
      if ((local_9c != 0) && (param_1 != (undefined *)0x0)) {
        *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 4;
      }
    }
  }
  if (local_9c != 0) {
    local_84 = DAT_004e5114 * local_ac + local_9c + local_80 * local_a8;
    local_90 = *(int *)(param_2 + 0x440);
    local_7c = local_b4 - local_bc;
    local_94 = local_90 * local_b8 + *(int *)(param_2 + 0x448) + local_bc;
    local_98 = param_2;
    piVar9 = &local_98;
    local_8c = param_2 + 0x38;
    local_78 = local_b0 - local_b8;
    local_88 = &DAT_004e50d8;
    local_74 = 0;
    this = (void *)FUN_0040c9e0();
    FUN_0046e520(this,piVar9);
    if (param_1 == &DAT_004e4fa0) {
      (**(code **)(DAT_004e5124 + 0xf0))();
      return;
    }
    (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_1 + 0xc));
  }
  return;
}


/* 0040ce60 size=36 */

void __cdecl FUN_0040ce60(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    (**(code **)(DAT_004e5124 + 0xd4))(*(int *)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return;
}


/* 0040ce90 size=30 */

void __cdecl FUN_0040ce90(int param_1)

{
  if (*(undefined **)(param_1 + 8) != (undefined *)0x0) {
    FUN_00430fe0(*(undefined **)(param_1 + 8));
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}


/* 0040d0c0 size=417 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0040d0c0(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  *(code **)(param_1 + 0x150) = FUN_0040d270;
  *(code **)(param_1 + 0x154) = FUN_00436e70;
  *(undefined1 **)(param_1 + 0x158) = &LAB_0040d2d0;
  *(undefined1 **)(param_1 + 0x15c) = &LAB_0040d2f0;
  *(code **)(param_1 + 0x160) = FUN_0040d310;
  *(code **)(param_1 + 0x164) = FUN_0040d600;
  *(undefined1 **)(param_1 + 0x168) = &LAB_0040d6b0;
  *(undefined1 **)(param_1 + 0x16c) = &LAB_0040d720;
  *(undefined1 **)(param_1 + 0x170) = &LAB_0040d730;
  *(undefined1 **)(param_1 + 0x178) = &LAB_0040d850;
  *(code **)(param_1 + 0x17c) = winclientde_impl_40cd70;
  *(undefined1 **)(param_1 + 0x180) = &LAB_0040d870;
  *(undefined1 **)(param_1 + 0x184) = &LAB_0040d880;
  *(undefined1 **)(param_1 + 0x188) = &LAB_0040ceb0;
  *(undefined1 **)(param_1 + 0x18c) = &LAB_0040cfb0;
  *(undefined1 **)(param_1 + 0x198) = &LAB_0040d890;
  *(undefined1 **)(param_1 + 0x19c) = &LAB_0040d8d0;
  *(undefined1 **)(param_1 + 0x1a4) = &LAB_0040d9e0;
  *(undefined1 **)(param_1 + 0x1a0) = &LAB_0040e0d0;
  *(undefined1 **)(param_1 + 0x1a8) = &LAB_0040e410;
  *(undefined1 **)(param_1 + 0x1ac) = &LAB_0040e480;
  *(undefined1 **)(param_1 + 0x1b0) = &LAB_0040e510;
  *(undefined1 **)(param_1 + 0x1b4) = &LAB_0040e880;
  *(undefined1 **)(param_1 + 0x1b8) = &LAB_0040e900;
  *(code **)(param_1 + 0x1bc) = FUN_0040e970;
  *(code **)(param_1 + 0x1c0) = FUN_0040ebf0;
  *(code **)(param_1 + 0x1c4) = FUN_0040ec70;
  *(undefined1 **)(param_1 + 0x1c8) = &LAB_0040ed10;
  *(undefined1 **)(param_1 + 0x1cc) = &LAB_0040f250;
  *(undefined1 **)(param_1 + 0x1d0) = &LAB_0040f2f0;
  *(code **)(param_1 + 0x340) = FUN_0040f610;
  *(undefined1 **)(param_1 + 0x1d4) = &LAB_0040f530;
  *(undefined1 **)(param_1 + 0x1d8) = &LAB_0040f580;
  _DAT_004e4fbc = 1;
  FUN_004b7b90((uint *)&DAT_004e4f80,0x2c,10);
  puVar4 = &DAT_004e4fcc;
  for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined1 *)puVar4 = 0;
  uVar3 = 0;
  do {
    bVar1 = (byte)uVar3;
    uVar3 = uVar3 + 1;
    *(char *)((int)&DAT_004e4fcc + (1 << (bVar1 & 0x1f))) = ('\x01' << (bVar1 & 0x1f)) + -1;
  } while (uVar3 < 8);
  FUN_0049f800(param_1);
  return;
}


/* 0040d270 size=83 */

uint FUN_0040d270(void)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  int in_stack_00000010;
  
  if (in_stack_00000010 == 0) {
    lVar2 = __ftol();
    uVar1 = (uint)lVar2;
  }
  else {
    lVar2 = __ftol();
    uVar1 = (uint)lVar2 | 0xffff8000;
  }
  lVar2 = __ftol();
  lVar3 = __ftol();
  return (uint)lVar3 | (uVar1 << 8 | (uint)lVar2) << 8;
}


/* 0040d310 size=546 */

undefined4 __cdecl FUN_0040d310(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  void *this;
  int iVar5;
  undefined *puVar6;
  undefined4 uVar7;
  int *piVar8;
  
  piVar3 = param_3;
  iVar2 = param_1;
  if (((param_1 == 0) || (param_3 == (int *)0x0)) || (*(int *)(param_1 + 0xc) == 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_GetBorderSize_004d6344);
    }
    return 0x3c;
  }
  if (DAT_004e5124 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_GetBorderSize_004d6344);
    }
    return 0x49;
  }
  iVar4 = (**(code **)(DAT_004e5124 + 0xdc))(*(int *)(param_1 + 0xc));
  if (iVar4 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_GetBorderSize_004d6344);
    }
    return 1;
  }
  piVar8 = &param_1;
  puVar6 = &DAT_004e50d8;
  piVar3[3] = 0;
  piVar3[2] = 0;
  piVar3[1] = 0;
  *piVar3 = 0;
  uVar7 = param_2;
  this = (void *)FUN_0040c9e0();
  FUN_0046e730(this,(int)puVar6,(char)uVar7,piVar8);
  if (*piVar3 < *(int *)(iVar2 + 0x10)) {
    do {
      iVar5 = FUN_0040d540((int *)(*piVar3 + iVar4),param_1,*(int *)(iVar2 + 0x14),
                           *(int *)(iVar2 + 0x18));
      if (iVar5 == 0) break;
      iVar5 = *piVar3;
      *piVar3 = iVar5 + 1;
    } while (iVar5 + 1 < *(int *)(iVar2 + 0x10));
  }
  iVar5 = *(int *)(iVar2 + 0x10);
  if (piVar3[2] < iVar5) {
    do {
      iVar5 = FUN_0040d540((int *)((iVar5 - piVar3[2]) + -1 + iVar4),param_1,*(int *)(iVar2 + 0x14),
                           *(int *)(iVar2 + 0x18));
      if (iVar5 == 0) break;
      iVar1 = piVar3[2];
      piVar3[2] = iVar1 + 1;
      iVar5 = *(int *)(iVar2 + 0x10);
    } while (iVar1 + 1 < iVar5);
  }
  if (piVar3[1] < *(int *)(iVar2 + 0x14)) {
    do {
      iVar5 = FUN_0040d5a0((int *)(*(int *)(iVar2 + 0x18) * piVar3[1] + iVar4),param_1,
                           *(int *)(iVar2 + 0x10));
      if (iVar5 == 0) break;
      iVar5 = piVar3[1];
      piVar3[1] = iVar5 + 1;
    } while (iVar5 + 1 < *(int *)(iVar2 + 0x14));
  }
  iVar5 = *(int *)(iVar2 + 0x14);
  if (piVar3[3] < iVar5) {
    do {
      iVar5 = FUN_0040d5a0((int *)(((iVar5 - piVar3[3]) + -1) * *(int *)(iVar2 + 0x18) + iVar4),
                           param_1,*(int *)(iVar2 + 0x10));
      if (iVar5 == 0) break;
      iVar1 = piVar3[3];
      piVar3[3] = iVar1 + 1;
      iVar5 = *(int *)(iVar2 + 0x14);
    } while (iVar1 + 1 < iVar5);
  }
  (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(iVar2 + 0xc));
  return 0;
}


/* 0040d540 size=93 */

undefined4 __cdecl FUN_0040d540(int *param_1,int param_2,int param_3,int param_4)

{
  if (DAT_004e50dc == 2) {
    if (param_3 != 0) {
      do {
        if ((short)*param_1 != (short)param_2) {
          return 0;
        }
        param_1 = (int *)((int)param_1 + param_4);
        param_3 = param_3 + -1;
      } while (param_3 != 0);
    }
  }
  else if ((DAT_004e50dc == 3) && (param_3 != 0)) {
    do {
      if (*param_1 != param_2) {
        return 0;
      }
      param_1 = (int *)((int)param_1 + param_4);
      param_3 = param_3 + -1;
    } while (param_3 != 0);
    return 1;
  }
  return 1;
}


/* 0040d5a0 size=87 */

undefined4 __cdecl FUN_0040d5a0(int *param_1,int param_2,int param_3)

{
  if (DAT_004e50dc == 2) {
    if (param_3 != 0) {
      do {
        if ((short)*param_1 != (short)param_2) {
          return 0;
        }
        param_3 = param_3 + -1;
        param_1 = (int *)((int)param_1 + 2);
      } while (param_3 != 0);
    }
  }
  else if ((DAT_004e50dc == 3) && (param_3 != 0)) {
    do {
      if (*param_1 != param_2) {
        return 0;
      }
      param_3 = param_3 + -1;
      param_1 = param_1 + 1;
    } while (param_3 != 0);
    return 1;
  }
  return 1;
}


/* 0040d600 size=161 */

undefined4 __cdecl FUN_0040d600(int param_1,uint param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_OptimizeSurface_004d6354);
    }
    return 0x3c;
  }
  *(uint *)(param_1 + 0x20) = param_2;
  if ((param_2 & 0x80000000) == 0) {
    *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
  }
  else {
    *(uint *)(param_1 + 0x20) = param_2 & 0x7fffffff;
  }
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 2;
  if ((DAT_004e5124 != 0) && (*(int *)(DAT_004e5124 + 0x44) != 0)) {
    iVar1 = (**(code **)(DAT_004e5124 + 0xe4))
                      (*(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 0x20));
    if (iVar1 == 0) {
      return 1;
    }
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xfffffffb;
  }
  return 0;
}


/* 0040d7f0 size=96 */

undefined4 __cdecl FUN_0040d7f0(undefined4 param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int local_c;
  undefined4 local_8;
  undefined2 local_4;
  
  local_4 = 0;
  local_c = 1;
  local_8 = param_1;
  piVar1 = FUN_004049e0(*(int *)(DAT_004e516c + 0x1644),&local_c);
  if (piVar1 == (int *)0x0) {
    return 0;
  }
  uVar2 = FUN_00447a10(piVar1,param_2);
  (**(code **)(*piVar1 + 4))();
  return uVar2;
}


/* 0040db50 size=963 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0040db50: lifted from original x86 -> lt_lifted.c */


/* 0040df20 size=162 */

undefined4 __cdecl
FUN_0040df20(int param_1,int param_2,undefined4 *param_3,int param_4,int param_5,int *param_6,
            int *param_7)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  piVar1 = param_6 + 1;
  iVar3 = *param_6;
  piVar2 = param_6 + 2;
  param_6 = (int *)(param_6[3] - *piVar1);
  uVar5 = (*piVar2 - iVar3) * DAT_004e5114;
  puVar6 = (undefined4 *)(*piVar1 * param_4 + param_2 + iVar3 * DAT_004e5114);
  param_3 = (undefined4 *)((int)param_3 + param_7[1] * param_5 + *param_7 * DAT_004e5114);
  if (param_6 != (int *)0x0) {
    do {
      if (param_1 == 0) {
        puVar7 = puVar6;
        puVar8 = param_3;
        for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
        for (uVar4 = uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
          puVar7 = (undefined4 *)((int)puVar7 + 1);
          puVar8 = (undefined4 *)((int)puVar8 + 1);
        }
      }
      else {
        FUN_004bab10(param_3,puVar6,uVar5);
      }
      puVar6 = (undefined4 *)((int)puVar6 + param_4);
      param_3 = (undefined4 *)((int)param_3 + param_5);
      param_6 = (int *)((int)param_6 + -1);
    } while (param_6 != (int *)0x0);
  }
  return 0;
}


/* 0040e090 size=53 */

void __cdecl FUN_0040e090(int param_1)

{
  if (((param_1 != 0) && ((*(uint *)(param_1 + 0x1c) & 2) != 0)) &&
     ((*(uint *)(param_1 + 0x1c) & 4) != 0)) {
    (**(code **)(DAT_004e5124 + 0xe4))
              (*(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 0x20));
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xfffffffb;
  }
  return;
}


/* 0040e580 size=764 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0040e580: lifted from original x86 -> lt_lifted.c */


/* 0040e970 size=98 */

undefined4 __cdecl FUN_0040e970(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  undefined4 uVar1;
  undefined1 unaff_retaddr;
  
  if (DAT_004e5124 != 0) {
    uVar1 = winclientde_impl_40e9e0(param_1,param_2,param_3,param_4,&LAB_00444260,unaff_retaddr);
    return uVar1;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_WarpSurfaceToSurface_004d6444);
  }
  return 0x49;
}


/* 0040ebf0 size=125 */

undefined4 __cdecl
FUN_0040ebf0(undefined4 param_1,uint param_2,uint param_3,uint param_4,undefined1 param_5)

{
  void *this;
  undefined4 uVar1;
  undefined1 unaff_retaddr;
  undefined *puVar2;
  undefined2 *puVar3;
  
  if (DAT_004e5124 != 0) {
    puVar3 = &DAT_004e4f9c;
    puVar2 = &DAT_004e50d8;
    this = (void *)FUN_0040c9e0();
    FUN_0046e730(this,(int)puVar2,param_5,puVar3);
    uVar1 = winclientde_impl_40e9e0(param_1,param_2,param_3,param_4,&LAB_00444580,unaff_retaddr);
    return uVar1;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_WarpSurfaceToSurfaceTransparent_004d6488);
  }
  return 0x49;
}


/* 0040ec70 size=152 */

undefined4 __cdecl
FUN_0040ec70(undefined4 param_1,uint param_2,uint param_3,uint param_4,undefined1 param_5,
            undefined1 param_6)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined1 unaff_retaddr;
  undefined *puVar3;
  undefined2 *puVar4;
  undefined4 *puVar5;
  
  if (DAT_004e5124 != 0) {
    puVar4 = &DAT_004e4f9c;
    puVar3 = &DAT_004e50d8;
    pvVar1 = (void *)FUN_0040c9e0();
    FUN_0046e730(pvVar1,(int)puVar3,param_5,puVar4);
    puVar5 = &DAT_004e50d0;
    puVar3 = &DAT_004e50d8;
    pvVar1 = (void *)FUN_0040c9e0();
    FUN_0046e730(pvVar1,(int)puVar3,param_6,puVar5);
    uVar2 = winclientde_impl_40e9e0(param_1,param_2,param_3,param_4,&LAB_00444830,unaff_retaddr);
    return uVar2;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_WarpSurfaceToSurfaceSolidColor_004d64a8);
  }
  return 0x49;
}


/* 0040f610 size=136 */

undefined4 __thiscall FUN_0040f610(void *this,byte *param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  void *this_00;
  void *this_01;
  
  uVar1 = FUN_004c4c00(this,param_1,&DAT_004d655c);
  if (uVar1 == 0) {
    *param_2 = DAT_004e446c;
    return 0;
  }
  uVar1 = FUN_004c4c00(this_00,param_1,(byte *)s_cres_hinstance_004d654c);
  if (uVar1 == 0) {
    uVar2 = FUN_00401850(*(undefined4 **)(DAT_004e447c + 0x614),param_2);
    return uVar2;
  }
  uVar1 = FUN_004c4c00(this_01,param_1,(byte *)s_cresl_hinstance_004d653c);
  if (uVar1 == 0) {
    uVar2 = FUN_00401850(*(undefined4 **)(DAT_004e447c + 0x618),param_2);
    return uVar2;
  }
  return 1;
}


/* 0040f6a0 size=34 */

void FUN_0040f6a0(void)

{
  FUN_0040f6d0();
  FUN_004b7c50(0x4e4f80);
  FUN_004a0390();
  DAT_004e5124 = 0;
  return;
}


/* 0040f6d0 size=113 */

void FUN_0040f6d0(void)

{
  uint *puVar1;
  uint *puVar2;
  
  puVar1 = DAT_004e5120;
  if (DAT_004e5120 == (uint *)0x0) {
    DAT_004e5120 = (uint *)0x0;
    DAT_004e511c = 0;
    return;
  }
  do {
    puVar2 = (uint *)(puVar1[1] & -(uint)((uint *)puVar1[1] != DAT_004e5120));
    FUN_0040ce90((int)puVar1);
    FUN_0040ce60((int)puVar1);
    if (puVar1 != (uint *)0x0) {
      *puVar1 = (uint)DAT_004e4f98;
      DAT_004e4f98 = puVar1;
    }
    puVar1 = puVar2;
  } while (puVar2 != (uint *)0x0);
  DAT_004e5120 = (uint *)0x0;
  DAT_004e511c = 0;
  return;
}


/* 0040f750 size=121 */

undefined4 __cdecl FUN_0040f750(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  DAT_004e5124 = param_1;
  DAT_004e4fb0 = *(undefined4 *)(param_1 + 0x3c);
  DAT_004e4fb4 = *(undefined4 *)(param_1 + 0x40);
  (**(code **)(param_1 + 0xcc))(&DAT_004e50d8);
  DAT_004e5114 = FUN_0046e380(0x4e50d8);
  uVar2 = DAT_004e5120;
  do {
    if (uVar2 == 0) {
      return 1;
    }
    uVar1 = *(uint *)(uVar2 + 4);
    bVar4 = uVar1 != DAT_004e5120;
    iVar3 = FUN_0040f7d0(uVar2);
    uVar2 = uVar1 & -(uint)bVar4;
  } while (iVar3 != 0);
  return 0;
}


/* 0040f7d0 size=293 */

undefined4 __cdecl FUN_0040f7d0(int param_1)

{
  int iVar1;
  void *this;
  undefined **ppuVar2;
  undefined1 auStack_a0 [4];
  undefined1 auStack_9c [4];
  undefined *local_98;
  undefined4 uStack_94;
  int iStack_90;
  undefined *puStack_88;
  int iStack_84;
  undefined4 uStack_80;
  int iStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  
  FUN_0046e390((int *)&local_98);
  iVar1 = (**(code **)(DAT_004e5124 + 0xd0))
                    (*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14));
  *(int *)(param_1 + 0xc) = iVar1;
  if (iVar1 == 0) {
    return 0;
  }
  (**(code **)(DAT_004e5124 + 0xd8))(iVar1,auStack_a0,auStack_9c,(undefined4 *)(param_1 + 0x18));
  puStack_88 = &DAT_004e50d8;
  iStack_84 = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_1 + 0xc));
  if (iStack_84 == 0) {
    return 0;
  }
  uStack_80 = *(undefined4 *)(param_1 + 0x18);
  uStack_94 = *(undefined4 *)(param_1 + 8);
  iStack_7c = *(int *)(param_1 + 0x10);
  iStack_90 = iStack_7c * DAT_004e5110;
  uStack_78 = *(undefined4 *)(param_1 + 0x14);
  ppuVar2 = &local_98;
  local_98 = &DAT_004e4f40;
  uStack_74 = 0;
  this = (void *)FUN_0040c9e0();
  iVar1 = FUN_0046e520(this,(int *)ppuVar2);
  (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_1 + 0xc));
  if (iVar1 != 0) {
    return 0;
  }
  FUN_0040ce90(param_1);
  if ((*(byte *)(param_1 + 0x1c) & 2) != 0) {
    (**(code **)(DAT_004e5124 + 0xe4))
              (*(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 0x20));
  }
  return 1;
}


/* 0040f900 size=174 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0040f900(void)

{
  _DAT_004e4f44 = DAT_004e50dc;
  _DAT_004e4f48 = DAT_004e50e0;
  _DAT_004e4f4c = DAT_004e50e4;
  _DAT_004e4f50 = DAT_004e50e8;
  _DAT_004e4f54 = DAT_004e50ec;
  _DAT_004e4f58 = DAT_004e50f0;
  _DAT_004e4f5c = DAT_004e50f4;
  _DAT_004e4f60 = DAT_004e50f8;
  _DAT_004e4f64 = DAT_004e50fc;
  _DAT_004e4f68 = DAT_004e5100;
  _DAT_004e4f6c = DAT_004e5104;
  _DAT_004e4f70 = DAT_004e5108;
  _DAT_004e4f74 = DAT_004e510c;
  DAT_004e5110 = DAT_004e5114;
  FUN_0040f9b0();
  DAT_004e5124 = 0;
  return;
}


/* 0040f9b0 size=60 */

undefined4 FUN_0040f9b0(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  uVar2 = DAT_004e5120;
  do {
    if (uVar2 == 0) {
      return 1;
    }
    uVar1 = *(uint *)(uVar2 + 4);
    bVar4 = uVar1 != DAT_004e5120;
    iVar3 = FUN_0040f9f0(uVar2);
    uVar2 = uVar1 & -(uint)bVar4;
  } while (iVar3 != 0);
  return 0;
}


/* 0040f9f0 size=148 */

undefined4 __cdecl FUN_0040f9f0(int param_1)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  pvVar1 = FUN_00430f00(*(int *)(param_1 + 0x10) * DAT_004e5114 * *(int *)(param_1 + 0x14));
  *(void **)(param_1 + 8) = pvVar1;
  iVar2 = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_1 + 0xc));
  if (iVar2 == 0) {
    return 0;
  }
  uVar5 = 0;
  if (*(int *)(param_1 + 0x14) != 0) {
    do {
      uVar3 = *(int *)(param_1 + 0x10) * DAT_004e5114;
      puVar6 = (undefined4 *)(*(int *)(param_1 + 0x18) * uVar5 + iVar2);
      puVar7 = (undefined4 *)(uVar3 * uVar5 + *(int *)(param_1 + 8));
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      uVar5 = uVar5 + 1;
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
        puVar7 = (undefined4 *)((int)puVar7 + 1);
      }
    } while (uVar5 < *(uint *)(param_1 + 0x14));
  }
  (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_1 + 0xc));
  FUN_0040ce60(param_1);
  return 1;
}


/* 0040fac0 size=248 */

/* WARNING: Removing unreachable block (ram,0x0040fb83) */

undefined4 __thiscall FUN_0040fac0(void *this,undefined1 *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 *unaff_retaddr;
  
  uVar1 = *(uint *)((int)this + 8);
  if (*(int *)((int)this + 0xc) != 0) {
    *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
    *(undefined1 *)(*(int *)((int)this + 4) + uVar1) = *param_1;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    return 1;
  }
  iVar3 = (**(code **)(DAT_004ecc58 + 4))(uVar1 + 1 + *(int *)((int)this + 0x10));
  if (iVar3 == 0) {
    return 0;
  }
  uVar4 = 0;
  if (uVar1 != 0) {
    do {
      uVar4 = uVar4 + 1;
      *(undefined1 *)(iVar3 + -1 + uVar4) = *(undefined1 *)(*(int *)((int)this + 4) + -1 + uVar4);
    } while (uVar4 < uVar1);
  }
  uVar4 = uVar1;
  if (uVar1 < *(uint *)((int)this + 8)) {
    do {
      uVar4 = uVar4 + 1;
      *(undefined1 *)(iVar3 + uVar4) = *(undefined1 *)(*(int *)((int)this + 4) + -1 + uVar4);
    } while (uVar4 < *(uint *)((int)this + 8));
  }
  *(undefined1 *)(iVar3 + uVar1) = *unaff_retaddr;
  iVar2 = *(int *)((int)this + 4);
  if (iVar2 != 0) {
    if (iVar2 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar2);
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  *(int *)((int)this + 4) = iVar3;
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
  return 1;
}


/* 0040fef0 size=260 */

undefined4 __thiscall FUN_0040fef0(void *this,uint param_1,int *param_2,int *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *unaff_EBX;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  uVar5 = *(uint *)((int)this + 8);
  if (param_1 < uVar5) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = *(int *)((int)this + 0xc) + (uVar5 - param_1);
    return 1;
  }
  if ((uVar5 < param_1) && (uVar4 = *(int *)((int)this + 0xc) + uVar5, param_1 <= uVar4)) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = uVar4 - param_1;
    return 1;
  }
  if (param_1 == uVar5) {
    return 1;
  }
  puVar2 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 + *(int *)((int)this + 0x10));
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  uVar5 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar5 = param_1;
  }
  if (param_1 == 0) {
    uVar4 = 0;
    param_2 = param_3;
    if (uVar5 != 0) {
      do {
        uVar3 = uVar4 + 1;
        *(undefined1 *)((int)puVar2 + uVar4) = *(undefined1 *)(*(int *)((int)this + 4) + -1 + uVar3)
        ;
        uVar4 = uVar3;
      } while (uVar3 < uVar5);
    }
  }
  else {
    puVar6 = *(undefined4 **)((int)this + 4);
    puVar7 = puVar2;
    for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
  }
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*param_2 + 8))(iVar1);
      puVar2 = unaff_EBX;
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 **)((int)this + 4) = puVar2;
  *(uint *)((int)this + 8) = param_1;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  return 1;
}


