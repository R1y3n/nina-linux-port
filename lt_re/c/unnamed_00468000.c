/* lithtech.exe decompilation - unnamed_00468000 */
#include "ghidra_types.h"

/* 004680f0 size=119 */

undefined1 __fastcall FUN_004680f0(int param_1)

{
  uint uVar1;
  undefined1 uVar2;
  ushort uVar3;
  undefined1 local_1;
  
  uVar3 = *(ushort *)(param_1 + 0x38);
  uVar1 = uVar3 + 1;
  if ((uVar1 < *(uint *)(param_1 + 0x58)) && (uVar1 <= *(ushort *)(param_1 + 0x34))) {
    uVar2 = *(undefined1 *)(*(int *)(param_1 + 0x54) + (uint)uVar3);
    *(ushort *)(param_1 + 0x38) = uVar3 + 1;
    return uVar2;
  }
  *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | 2;
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
  }
  local_1 = (undefined1)((uint)param_1 >> 0x18);
  return local_1;
}


/* 00468190 size=134 */

undefined4 __thiscall FUN_00468190(void *this,int param_1,int *param_2)

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
      iVar1 = (**(code **)(*param_2 + 4))((param_1 + *(int *)((int)this + 0x10)) * 4);
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


/* 00468220 size=52 */

undefined4 * __thiscall FUN_00468220(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004ccd04;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00468260 size=91 */

undefined * __thiscall FUN_00468260(void *this,byte param_1)

{
  *(undefined ***)((int)this + 0x5c) = &PTR_LAB_004cbb50;
  if (*(int *)((int)this + 0x60) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x60));
    *(undefined4 *)((int)this + 0x60) = 0;
    *(undefined4 *)((int)this + 0x68) = 0;
  }
  *(undefined4 *)((int)this + 100) = 0;
  *(undefined ***)((int)this + 0xc) = &PTR_LAB_004ccd18;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004682c0 size=36 */

void __thiscall FUN_004682c0(void *this,int param_1,int *param_2)

{
  **(undefined4 **)(param_1 + 4) = param_2;
  param_2[1] = *(int *)(param_1 + 4);
  *param_2 = param_1;
  *(int **)(param_1 + 4) = param_2;
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  return;
}


/* 004682f0 size=72 */

void __thiscall FUN_004682f0(void *this,int *param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)((int)this + 8);
  if (piVar1 == (int *)0x0) {
    param_1[1] = (int)param_1;
    *param_1 = (int)param_1;
    *(int **)((int)this + 8) = param_1;
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  }
  else {
    *(int **)(*piVar1 + 4) = param_1;
    *param_1 = *piVar1;
    param_1[1] = (int)piVar1;
    *piVar1 = (int)param_1;
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
    if (param_1[1] == *(int *)((int)this + 8)) {
      *(int **)((int)this + 8) = param_1;
      return;
    }
  }
  return;
}


/* 00468340 size=265 */

undefined4 __thiscall FUN_00468340(void *this,undefined4 *param_1,undefined4 *param_2,int *param_3)

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
      *(undefined4 *)(*(int *)((int)this + 4) + (int)puVar3 * 4) =
           *(undefined4 *)(*(int *)((int)this + 4) + -4 + (int)puVar3 * 4);
    }
    *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
    *(undefined4 *)(*(int *)((int)this + 4) + (int)param_1 * 4) = *param_2;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    return 1;
  }
  iVar2 = (**(code **)(*param_3 + 4))(((int)puVar3 + *(int *)((int)this + 0x10) + 1) * 4);
  if (iVar2 == 0) {
    return 0;
  }
  puVar3 = (undefined4 *)0x0;
  if (param_1 != (undefined4 *)0x0) {
    do {
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      *(undefined4 *)(iVar2 + -4 + (int)puVar3 * 4) =
           *(undefined4 *)(*(int *)((int)this + 4) + -4 + (int)puVar3 * 4);
    } while (puVar3 < param_1);
  }
  if (param_1 < *(undefined4 **)((int)this + 8)) {
    puVar3 = param_1;
    puVar4 = (undefined4 *)(iVar2 + 4 + (int)param_1 * 4);
    do {
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      *puVar4 = *(undefined4 *)(*(int *)((int)this + 4) + -4 + (int)puVar3 * 4);
      puVar4 = puVar4 + 1;
    } while (puVar3 < *(undefined4 **)((int)this + 8));
  }
  *(undefined4 *)(iVar2 + (int)param_1 * 4) = *param_1;
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


/* 00468450 size=14 */

void * __fastcall FUN_00468450(void *param_1)

{
  FUN_00468470(param_1,0);
  return param_1;
}


/* 00468470 size=21 */

undefined4 __thiscall FUN_00468470(void *this,undefined4 param_1)

{
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = param_1;
  return 1;
}


/* 00468490 size=23 */

void __fastcall FUN_00468490(void *param_1)

{
  undefined4 local_4;
  
  local_4 = 1;
  FUN_004684b0(param_1,0,&local_4);
  return;
}


/* 004684b0 size=73 */

undefined4 __thiscall FUN_004684b0(void *this,undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)this;
  if (puVar3 == (undefined4 *)0x0) {
    return 0;
  }
  do {
    puVar2 = (undefined4 *)puVar3[2];
    for (puVar1 = (undefined4 *)*puVar3; puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)puVar1[1]) {
      (*(code *)*puVar1)(this,puVar3,param_1,param_2);
    }
    puVar3 = puVar2;
  } while (puVar2 != (undefined4 *)0x0);
  return 0;
}


/* 00468500 size=35 */

void __thiscall FUN_00468500(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)this;
  if (iVar1 != 0) {
    while (iVar1 != param_1) {
      this = (void *)(iVar1 + 8);
      iVar1 = *(int *)(iVar1 + 8);
      if (iVar1 == 0) {
        return;
      }
    }
    *(undefined4 *)this = *(undefined4 *)(iVar1 + 8);
  }
  return;
}


/* 00468530 size=26 */

int * __thiscall FUN_00468530(void *this,int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)this;
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    if (*piVar1 == param_1) break;
    piVar1 = (int *)piVar1[2];
  }
  return piVar1;
}


/* 00468570 size=418 */

undefined4 * __fastcall FUN_00468570(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  *param_1 = &PTR_LAB_004ccdd8;
  param_1[0x1a] = &PTR_FUN_004cbda4;
  FUN_004b7be0(param_1 + 0x1b,0x1b0,0x20,0x20);
  param_1[0x23] = &PTR_FUN_004cbcf4;
  FUN_004b7be0(param_1 + 0x24,0x2cc,0x20,0x100);
  param_1[0x2c] = &PTR_FUN_004cbd04;
  FUN_004b7be0(param_1 + 0x2d,0x278,0x20,0x20);
  param_1[0x35] = &PTR_FUN_004cbd14;
  FUN_004b7be0(param_1 + 0x36,0x1d0,0x20,0x80);
  param_1[0x3e] = &PTR_FUN_004cbd24;
  FUN_004b7be0(param_1 + 0x3f,0x1b4,0x20,0x20);
  param_1[0x47] = &PTR_FUN_004cbd34;
  FUN_004b7be0(param_1 + 0x48,0x1d8,0x20,0x20);
  param_1[0x50] = &PTR_FUN_004cbd44;
  FUN_004b7be0(param_1 + 0x51,0x264,0x20,0x20);
  param_1[0x59] = &PTR_FUN_004cbd54;
  FUN_004b7be0(param_1 + 0x5a,0x1200,0x20,0x20);
  param_1[0x62] = &PTR_FUN_004cbd64;
  FUN_004b7be0(param_1 + 99,0x224,0x20,0x20);
  param_1[0x6b] = &PTR_FUN_004cbd74;
  FUN_004b7be0(param_1 + 0x6c,0x27c,0x20,0x20);
  param_1[0x74] = &PTR_FUN_004cbd84;
  FUN_004b7be0(param_1 + 0x75,0x1bc,0x20,0x20);
  puVar2 = param_1 + 0x88;
  iVar3 = 0xb;
  puVar1 = param_1 + 0x89;
  do {
    puVar1[1] = puVar1;
    *puVar1 = puVar1;
    *puVar2 = 0;
    puVar2 = puVar2 + 4;
    puVar1 = puVar1 + 4;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  puVar1 = param_1 + 2;
  *param_1 = &PTR_LAB_004ccdd0;
  param_1[1] = 0;
  param_1[3] = puVar1;
  *puVar1 = puVar1;
  return param_1;
}


/* 00468720 size=4 */

undefined4 __fastcall FUN_00468720(int param_1)

{
  return *(undefined4 *)(param_1 + 4);
}


/* 00468780 size=34 */

undefined4 * __fastcall FUN_00468780(undefined4 *param_1)

{
  FUN_004a3700(param_1,0);
  *param_1 = &PTR_FUN_004ccde0;
  FUN_00468970((int)param_1);
  *(undefined1 *)(param_1 + 0x2f) = 0;
  return param_1;
}


/* 004687e0 size=30 */

undefined4 * __thiscall FUN_004687e0(void *this,byte param_1)

{
  FUN_00468830(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00468800 size=39 */

undefined4 * __thiscall FUN_00468800(void *this,undefined1 param_1)

{
  FUN_004a3700(this,0);
  *(undefined ***)this = &PTR_FUN_004ccde0;
  FUN_00468970((int)this);
  *(undefined1 *)((int)this + 0xbc) = param_1;
  return this;
}


/* 00468830 size=167 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00468830(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  iVar1 = param_1[0x17];
  *param_1 = &PTR_FUN_004ccde0;
  if (iVar1 != 0) {
    puVar2 = (undefined4 *)param_1[0x26];
    while (puVar3 = puVar2, puVar3 != (undefined4 *)0x0) {
      puVar2 = (undefined4 *)puVar3[9];
      if ((puVar3 != (undefined4 *)0x0) && (iVar1 != -0x4c)) {
        *puVar3 = *(undefined4 *)(iVar1 + 100);
        *(undefined4 **)(iVar1 + 100) = puVar3;
      }
    }
    param_1[0x26] = 0;
  }
  puVar2 = param_1 + 0x55;
  *(undefined4 *)(param_1[0x55] + 4) = param_1[0x56];
  *(undefined4 *)param_1[0x56] = *puVar2;
  param_1[0x56] = puVar2;
  *puVar2 = puVar2;
  if ((float)param_1[0x58] != _DAT_004cb524) {
    puVar2 = param_1 + 0x5e;
    *(undefined4 *)(param_1[0x5e] + 4) = param_1[0x5f];
    *(undefined4 *)param_1[0x5f] = *puVar2;
    param_1[0x5f] = puVar2;
    *puVar2 = puVar2;
  }
  FUN_00468bf0((int)param_1);
  FUN_004a3740(param_1);
  return;
}


/* 004688e0 size=140 */

void __thiscall FUN_004688e0(void *this,undefined4 param_1,undefined1 *param_2)

{
  *(undefined4 *)((int)this + 0x88) = *(undefined4 *)(param_2 + 8);
  *(undefined4 *)((int)this + 0x8c) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)((int)this + 0x90) = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)((int)this + 0x194) = *(undefined4 *)(param_2 + 0x14);
  *(undefined4 *)((int)this + 0x198) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)((int)this + 0x19c) = *(undefined4 *)(param_2 + 0x1c);
  *(undefined4 *)((int)this + 0x9c) = *(undefined4 *)(param_2 + 0x2c);
  *(undefined4 *)((int)this + 0xa0) = *(undefined4 *)(param_2 + 0x30);
  *(undefined4 *)((int)this + 0xa4) = *(undefined4 *)(param_2 + 0x34);
  *(undefined4 *)((int)this + 0xa8) = *(undefined4 *)(param_2 + 0x38);
  *(undefined4 *)((int)this + 0xac) = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)((int)this + 0xb0) = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)((int)this + 0xb4) = *(undefined4 *)(param_2 + 0x28);
  *(undefined1 *)((int)this + 0xbc) = *param_2;
  *(undefined4 *)((int)this + 0x5c) = param_1;
  return;
}


/* 00468970 size=523 */

void __fastcall FUN_00468970(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 + 0x60;
  iVar2 = param_1 + 0x6c;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(int *)(param_1 + 100) = iVar1;
  *(int *)iVar1 = iVar1;
  *(int *)(param_1 + 0x70) = iVar2;
  *(int *)iVar2 = iVar2;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(int *)(param_1 + 0x74) = param_1;
  *(int *)(param_1 + 100) = iVar1;
  *(int *)iVar1 = iVar1;
  iVar1 = param_1 + 0x7c;
  *(int *)(param_1 + 0x80) = iVar1;
  *(int *)iVar1 = iVar1;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined1 *)(param_1 + 0x96) = 0xff;
  *(undefined1 *)(param_1 + 0x95) = 0xff;
  *(undefined1 *)(param_1 + 0x94) = 0xff;
  *(undefined1 *)(param_1 + 0x97) = 0xff;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0x3f800000;
  *(undefined4 *)(param_1 + 0xac) = 0x3f800000;
  *(undefined4 *)(param_1 + 0xb0) = 0x3f800000;
  *(undefined4 *)(param_1 + 0xb4) = 0x3f800000;
  *(undefined2 *)(param_1 + 0xb8) = 0xffff;
  *(undefined2 *)(param_1 + 0xba) = 0xffff;
  *(undefined1 *)(param_1 + 0xbc) = 0;
  *(undefined1 *)(param_1 + 0xbd) = 0;
  *(undefined4 *)(param_1 + 0xc0) = 0;
  *(undefined4 *)(param_1 + 0xc4) = 0;
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  *(undefined4 *)(param_1 + 0xd8) = 0;
  *(undefined1 *)(param_1 + 0xdc) = 5;
  *(undefined4 *)(param_1 + 0xe0) = 0x40a00000;
  *(undefined4 *)(param_1 + 0xe4) = 0x41f00000;
  *(undefined4 *)(param_1 + 0xe8) = 0x49742400;
  *(undefined4 *)(param_1 + 0xec) = 0;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  iVar1 = param_1 + 0x10c;
  *(undefined4 *)(param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0xf8) = 0;
  *(undefined4 *)(param_1 + 0xfc) = 0;
  *(undefined4 *)(param_1 + 0x100) = 0;
  *(undefined4 *)(param_1 + 0x104) = 0;
  *(undefined4 *)(param_1 + 0x108) = 0;
  *(int *)(param_1 + 0x110) = iVar1;
  *(int *)iVar1 = iVar1;
  iVar1 = param_1 + 0x118;
  *(int *)(param_1 + 0x120) = param_1;
  *(int *)(param_1 + 0x11c) = iVar1;
  *(int *)iVar1 = iVar1;
  *(undefined4 *)(param_1 + 0x124) = 0;
  *(undefined2 *)(param_1 + 0x188) = 0;
  *(undefined4 *)(param_1 + 0x128) = 0;
  *(undefined4 *)(param_1 + 300) = 0;
  *(undefined4 *)(param_1 + 0x130) = 0;
  *(undefined4 *)(param_1 + 0x134) = 0;
  *(undefined4 *)(param_1 + 0x138) = 0;
  *(undefined4 *)(param_1 + 0x13c) = 0;
  *(undefined4 *)(param_1 + 0x140) = 0;
  *(undefined4 *)(param_1 + 0x144) = 0;
  iVar1 = param_1 + 0x154;
  *(undefined4 *)(param_1 + 0x148) = 0;
  *(undefined4 *)(param_1 + 0x14c) = 0;
  *(undefined4 *)(param_1 + 0x150) = 0;
  *(int *)(param_1 + 0x15c) = param_1;
  *(int *)(param_1 + 0x158) = iVar1;
  *(int *)iVar1 = iVar1;
  *(undefined4 *)(param_1 + 0x160) = 0;
  *(undefined4 *)(param_1 + 0x164) = 0;
  iVar1 = param_1 + 0x178;
  *(undefined4 *)(param_1 + 0x168) = 0;
  *(undefined4 *)(param_1 + 0x16c) = 0;
  *(undefined4 *)(param_1 + 0x170) = 0;
  *(undefined4 *)(param_1 + 0x174) = 0x3f800000;
  *(int *)(param_1 + 0x180) = param_1;
  *(int *)(param_1 + 0x17c) = iVar1;
  *(int *)iVar1 = iVar1;
  *(undefined4 *)(param_1 + 400) = 0;
  *(undefined4 *)(param_1 + 0x194) = 0;
  *(undefined4 *)(param_1 + 0x198) = 0;
  *(undefined4 *)(param_1 + 0x19c) = 0;
  *(undefined4 *)(param_1 + 0x1a0) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1a4) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1a8) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1ac) = 0;
  return;
}


/* 00468bf0 size=30 */

void __fastcall FUN_00468bf0(int param_1)

{
  if ((*(byte *)(param_1 + 0x88) & 0x40) == 0) {
    FUN_00431720(param_1);
  }
  FUN_004a3750(param_1);
  return;
}


/* 00468c10 size=255 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00468c10(void *this,float param_1,undefined4 param_2,undefined4 param_3)

{
  float *pfVar1;
  float *pfVar2;
  
  pfVar1 = (float *)((int)this + 0x194);
  *pfVar1 = param_1;
  *(undefined4 *)((int)this + 0x198) = param_2;
  *(undefined4 *)((int)this + 0x19c) = param_3;
  pfVar2 = (float *)((int)this + 0x1a0);
  *(float *)((int)this + 0xf4) = *pfVar1 - *pfVar2;
  *(float *)((int)this + 0xf8) = *(float *)((int)this + 0x198) - *(float *)((int)this + 0x1a4);
  *(float *)((int)this + 0xfc) = *(float *)((int)this + 0x19c) - *(float *)((int)this + 0x1a8);
  *(float *)((int)this + 0x100) = *pfVar2 + *pfVar1;
  *(float *)((int)this + 0x104) = *(float *)((int)this + 0x1a4) + *(float *)((int)this + 0x198);
  *(float *)((int)this + 0x108) = *(float *)((int)this + 0x1a8) + *(float *)((int)this + 0x19c);
  *(float *)((int)this + 0x1ac) =
       SQRT(*(float *)((int)this + 0x1a8) * *(float *)((int)this + 0x1a8) +
            *(float *)((int)this + 0x1a4) * *(float *)((int)this + 0x1a4) + *pfVar2 * *pfVar2) +
       _DAT_004cbeec;
  return;
}


/* 00468d10 size=219 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00468d10(void *this,float param_1,float param_2,float param_3)

{
  float fVar1;
  
  *(float *)((int)this + 0x1a0) = param_1;
  *(float *)((int)this + 0x1a4) = param_2;
  *(float *)((int)this + 0x1a8) = param_3;
  *(float *)((int)this + 0xf4) = *(float *)((int)this + 0x194) - param_1;
  *(float *)((int)this + 0xf8) = *(float *)((int)this + 0x198) - param_2;
  *(float *)((int)this + 0xfc) = *(float *)((int)this + 0x19c) - param_3;
  *(float *)((int)this + 0x100) = param_1 + *(float *)((int)this + 0x194);
  *(float *)((int)this + 0x104) = param_2 + *(float *)((int)this + 0x198);
  *(float *)((int)this + 0x108) = param_3 + *(float *)((int)this + 0x19c);
  fVar1 = *(float *)((int)this + 0x1a0);
  *(float *)((int)this + 0x1ac) =
       SQRT(*(float *)((int)this + 0x1a8) * *(float *)((int)this + 0x1a8) +
            *(float *)((int)this + 0x1a4) * *(float *)((int)this + 0x1a4) + fVar1 * fVar1) +
       _DAT_004cbeec;
  return;
}


/* 00468e10 size=27 */

undefined4 * __fastcall FUN_00468e10(undefined4 *param_1)

{
  FUN_00468800(param_1,2);
  *param_1 = &PTR_FUN_004cce18;
  FUN_00468eb0((int)param_1);
  return param_1;
}


/* 00468e30 size=30 */

undefined4 * __thiscall FUN_00468e30(void *this,byte param_1)

{
  FUN_00468e70(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00468e50 size=32 */

undefined4 * __thiscall FUN_00468e50(void *this,undefined1 param_1)

{
  FUN_00468800(this,param_1);
  *(undefined ***)this = &PTR_FUN_004cce18;
  FUN_00468eb0((int)this);
  return this;
}


/* 00468e70 size=23 */

void __fastcall FUN_00468e70(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cce18;
  FUN_00469150((int)param_1);
  FUN_00468830(param_1);
  return;
}


/* 00468e90 size=18 */

void __thiscall FUN_00468e90(void *this,undefined4 param_1,undefined1 *param_2)

{
  FUN_004688e0(this,param_1,param_2);
  return;
}


/* 00468eb0 size=263 */

void __fastcall FUN_00468eb0(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x96) = 0xff;
  *(undefined1 *)(param_1 + 0x95) = 0xff;
  *(undefined1 *)(param_1 + 0x94) = 0xff;
  *(undefined4 *)(param_1 + 0x1b0) = 0;
  *(undefined4 *)(param_1 + 0x1b4) = 0;
  *(undefined4 *)(param_1 + 0x1b8) = 0;
  *(undefined4 *)(param_1 + 0x1f8) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1fc) = 0;
  *(undefined4 *)(param_1 + 0x200) = 0;
  *(undefined4 *)(param_1 + 0x204) = 0;
  *(undefined4 *)(param_1 + 0x208) = 0;
  *(undefined4 *)(param_1 + 0x20c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x210) = 0;
  *(undefined4 *)(param_1 + 0x214) = 0;
  *(undefined4 *)(param_1 + 0x218) = 0;
  *(undefined4 *)(param_1 + 0x21c) = 0;
  *(undefined4 *)(param_1 + 0x220) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x224) = 0;
  *(undefined4 *)(param_1 + 0x228) = 0;
  *(undefined4 *)(param_1 + 0x22c) = 0;
  *(undefined4 *)(param_1 + 0x230) = 0;
  *(undefined4 *)(param_1 + 0x234) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x238) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x23c) = 0;
  *(undefined4 *)(param_1 + 0x240) = 0;
  *(undefined4 *)(param_1 + 0x244) = 0;
  *(undefined4 *)(param_1 + 0x248) = 0;
  *(undefined4 *)(param_1 + 0x24c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x250) = 0;
  *(undefined4 *)(param_1 + 0x254) = 0;
  *(undefined4 *)(param_1 + 600) = 0;
  *(undefined4 *)(param_1 + 0x25c) = 0;
  *(undefined4 *)(param_1 + 0x260) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x264) = 0;
  *(undefined4 *)(param_1 + 0x268) = 0;
  *(undefined4 *)(param_1 + 0x26c) = 0;
  *(undefined4 *)(param_1 + 0x270) = 0;
  *(undefined4 *)(param_1 + 0x274) = 0x3f800000;
  iVar1 = param_1 + 0x1bc;
  iVar2 = 5;
  do {
    *(int *)(iVar1 + 4) = iVar1;
    *(int *)iVar1 = iVar1;
    *(int *)(iVar1 + 8) = param_1;
    iVar1 = iVar1 + 0xc;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


/* 00469150 size=47 */

void __fastcall FUN_00469150(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + 0x1bc);
  iVar2 = 5;
  do {
    *(int *)(*piVar1 + 4) = piVar1[1];
    *(int *)piVar1[1] = *piVar1;
    piVar1[1] = (int)piVar1;
    *piVar1 = (int)piVar1;
    piVar1 = piVar1 + 3;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  FUN_00468bf0(param_1);
  return;
}


/* 00469180 size=212 */

undefined4 __thiscall FUN_00469180(void *this,undefined4 *param_1)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  int iVar3;
  void *this_00;
  char *pcVar4;
  
  if (*(int **)((int)this + 0x1b0) != (int *)0x0) {
    uVar2 = (**(code **)(**(int **)((int)this + 0x1b0) + 0x20))();
    if ((uVar2 & 0x10) != 0) {
      FUN_004a3cc0(param_1 + 3,(int *)((int)this + 4),0);
      return 1;
    }
    uVar2 = (**(code **)(**(int **)((int)this + 0x1b0) + 0x20))();
    if ((uVar2 & 0x20) != 0) {
      FUN_004a3cc0(param_1 + 3,(int *)((int)this + 4),2);
      return 1;
    }
    bVar1 = FUN_004692e0((int)this);
    if (CONCAT31(extraout_var,bVar1) != 0) {
      iVar3 = (**(code **)**(undefined4 **)((int)this + 0x1b0))();
      if (iVar3 == 1) {
        this_00 = (void *)(**(code **)*param_1)(*(int *)((int)this + 0x1b0) + 0x48);
        if (this_00 != (void *)0x0) {
          FUN_004a3cc0(this_00,(int *)((int)this + 4),0);
          return 1;
        }
        pcVar4 = (char *)(*(int *)((int)this + 0x1b0) + 4);
        if (*(int *)((int)this + 0x1b0) == 0) {
          pcVar4 = s____NONAME____004db550;
        }
        FUN_00436670((byte *)s_ERROR___Terrain_section___s__has_004db518,pcVar4);
        return 1;
      }
    }
  }
  return 0;
}


/* 00469280 size=42 */

void __thiscall FUN_00469280(void *this,undefined4 param_1,int param_2)

{
  *(undefined4 *)((int)this + 0x1b0) = param_1;
  *(int *)((int)this + 0x1b4) = param_2;
  if (param_2 == 0) {
    *(undefined4 *)((int)this + 0x1b8) = param_1;
    return;
  }
  *(int *)((int)this + 0x1b8) = param_2;
  return;
}


/* 004692b0 size=46 */

void __thiscall FUN_004692b0(void *this,undefined4 param_1)

{
  int iVar1;
  
  if ((*(int **)((int)this + 0x1b4) == (int *)0x0) ||
     (iVar1 = (**(code **)(**(int **)((int)this + 0x1b4) + 8))(param_1), iVar1 == -1)) {
    (**(code **)(**(int **)((int)this + 0x1b0) + 8))(param_1);
    return;
  }
  return;
}


/* 004692e0 size=24 */

bool __fastcall FUN_004692e0(int param_1)

{
  int iVar1;
  
  if (*(undefined4 **)(param_1 + 0x1b0) == (undefined4 *)0x0) {
    return false;
  }
  iVar1 = (**(code **)**(undefined4 **)(param_1 + 0x1b0))();
  return (bool)('\x01' - (iVar1 != 1));
}


/* 00469310 size=236 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00469310(void *this,float *param_1)

{
  float fVar1;
  undefined4 uVar2;
  
  if (*(int **)((int)this + 0x1b8) == (int *)0x0) {
    return 0;
  }
  fVar1 = _DAT_004cba94 /
          (*(float *)((int)this + 0x270) * param_1[2] +
           *(float *)((int)this + 0x268) * *param_1 + *(float *)((int)this + 0x26c) * param_1[1] +
          *(float *)((int)this + 0x274));
  uVar2 = (**(code **)(**(int **)((int)this + 0x1b8) + 0x10))
                    ((*(float *)((int)this + 0x238) * *param_1 +
                      *(float *)((int)this + 0x240) * param_1[2] +
                      *(float *)((int)this + 0x23c) * param_1[1] + *(float *)((int)this + 0x244)) *
                     fVar1,(*(float *)((int)this + 0x250) * param_1[2] +
                            *(float *)((int)this + 0x248) * *param_1 +
                            *(float *)((int)this + 0x24c) * param_1[1] +
                           *(float *)((int)this + 0x254)) * fVar1,
                     (*(float *)((int)this + 0x260) * param_1[2] +
                      *(float *)((int)this + 600) * *param_1 +
                      *(float *)((int)this + 0x25c) * param_1[1] + *(float *)((int)this + 0x264)) *
                     fVar1);
  return uVar2;
}


/* 00469400 size=420 */

undefined4 * __fastcall FUN_00469400(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  FUN_00468800(param_1,1);
  param_1[0x81] = 0xffffffff;
  param_1[0x84] = 0xffffffff;
  param_1[0x86] = 0;
  FUN_00451a80(param_1 + 0x7e,0,0,0,0,0,0);
  puVar1 = param_1 + 0x89;
  *puVar1 = &PTR_LAB_004ccea8;
  param_1[0x8a] = 0;
  param_1[0x8b] = 0;
  FUN_0046af00(puVar1,0,&DAT_004ecc58);
  FUN_0046b060((int)puVar1);
  FUN_0046af00(puVar1,0,&DAT_004ecc58);
  puVar1 = param_1 + 0x8d;
  *puVar1 = &PTR_LAB_004cca80;
  param_1[0x8e] = 0;
  param_1[0x8f] = 0;
  FUN_00456490(puVar1,0,&DAT_004ecc58);
  FUN_0046b060((int)puVar1);
  FUN_00456490(puVar1,0,&DAT_004ecc58);
  *param_1 = &PTR_FUN_004cce54;
  param_1[0x6d] = 0;
  param_1[0x6e] = 0;
  param_1[0x70] = 0;
  param_1[0x6f] = 0;
  param_1[0x70] = 0;
  param_1[0x71] = 0;
  param_1[0x72] = 0;
  param_1[0x73] = 0;
  FUN_00401050((int)(param_1 + 0x74),0,0);
  param_1[0x88] = param_1 + 0x74;
  param_1[0x75] = 0;
  param_1[0x76] = param_1;
  param_1[0x91] = 0;
  param_1[0x92] = 0;
  param_1[0x93] = 0;
  puVar1 = param_1 + 0x99;
  puVar2 = param_1 + 0x94;
  iVar3 = 4;
  do {
    *puVar2 = 0;
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar2 = puVar2 + 1;
    puVar1 = puVar1 + 5;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  param_1[0xac] = 0;
  param_1[0xad] = 0;
  param_1[0xaf] = 0xbf800000;
  param_1[0xae] = 0;
  param_1[0xb0] = 0xbf800000;
  param_1[0xb1] = 0xbf800000;
  param_1[0xb2] = 0xbf800000;
  return param_1;
}


/* 00469650 size=30 */

undefined4 * __thiscall FUN_00469650(void *this,byte param_1)

{
  FUN_00469670(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00469670 size=133 */

void __fastcall FUN_00469670(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cce54;
  param_1[0x8d] = &PTR_LAB_004cca80;
  if (param_1[0x8e] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[0x8e]);
    param_1[0x8e] = 0;
  }
  param_1[0x8f] = 0;
  param_1[0x89] = &PTR_LAB_004ccea8;
  if (param_1[0x8a] != 0) {
    (**(code **)(DAT_004ecc58 + 8))(param_1[0x8a]);
    param_1[0x8a] = 0;
  }
  param_1[0x8b] = 0;
  FUN_00468830(param_1);
  return;
}


/* 00469800 size=21 */

int __fastcall FUN_00469800(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  for (iVar1 = *(int *)(param_1 + 0x220); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}


/* 00469820 size=27 */

int __fastcall FUN_00469820(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x50))();
  if (iVar1 == 0) {
    FUN_00469ac0(param_1);
  }
  return param_1[0x8e];
}


/* 00469840 size=217 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __thiscall FUN_00469840(void *this,uint param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*(int *)this + 0x50))();
  if (iVar1 == 0) {
    FUN_00469ac0(this);
  }
  if (param_1 < *(uint *)((int)this + 0x23c)) {
    return (undefined *)(*(int *)((int)this + 0x238) + param_1 * 0x40);
  }
  _DAT_004ea798 = 0x3f800000;
  _DAT_004ea79c = 0;
  _DAT_004ea7a0 = 0;
  _DAT_004ea7a4 = 0;
  _DAT_004ea7a8 = 0;
  _DAT_004ea7ac = 0x3f800000;
  _DAT_004ea7b0 = 0;
  _DAT_004ea7b4 = 0;
  _DAT_004ea7b8 = 0;
  _DAT_004ea7bc = 0;
  _DAT_004ea7c0 = 0x3f800000;
  _DAT_004ea7c4 = 0;
  _DAT_004ea7c8 = 0;
  _DAT_004ea7cc = 0;
  _DAT_004ea7d0 = 0;
  _DAT_004ea7d4 = 0x3f800000;
  return &DAT_004ea798;
}


/* 00469a80 size=57 */

undefined4 __cdecl FUN_00469a80(short *param_1,short *param_2)

{
  if ((((*param_1 == *param_2) && (param_1[1] == param_2[1])) &&
      (*(int *)(param_1 + 2) == *(int *)(param_2 + 2))) &&
     (*(int *)(param_1 + 4) == *(int *)(param_2 + 4))) {
    return 0;
  }
  return 1;
}


/* 00469ac0 size=831 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00469ac0: lifted from original x86 -> lt_lifted.c */


/* 00469e00 size=21 */

undefined1 * __fastcall FUN_00469e00(int param_1)

{
  undefined1 *puVar1;
  
  if (*(int *)(param_1 + 0x1f8) == 0) {
    return &DAT_004e4424;
  }
  puVar1 = (undefined1 *)FUN_00468720(*(int *)(param_1 + 0x1f8));
  return puVar1;
}


/* 00469e20 size=98 */

undefined4 * __fastcall FUN_00469e20(undefined4 *param_1)

{
  FUN_00468800(param_1,3);
  param_1[0x72] = &PTR_LAB_004ccf14;
  *(undefined1 *)((int)param_1 + 0x96) = 0xff;
  *(undefined1 *)((int)param_1 + 0x95) = 0xff;
  *(undefined1 *)(param_1 + 0x25) = 0xff;
  param_1[0x6c] = 0;
  param_1[0x6d] = 0;
  param_1[0x6e] = 0;
  param_1[0x6f] = 0;
  param_1[0x70] = 0;
  *param_1 = &PTR_FUN_004cced8;
  param_1[0x71] = 0xffffffff;
  param_1[0x73] = param_1;
  return param_1;
}


/* 00469ec0 size=30 */

undefined4 * __thiscall FUN_00469ec0(void *this,byte param_1)

{
  FUN_00469ee0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00469ee0 size=11 */

void __fastcall FUN_00469ee0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cced8;
  FUN_00468830(param_1);
  return;
}


/* 00469ef0 size=30 */

undefined4 * __fastcall FUN_00469ef0(undefined4 *param_1)

{
  FUN_00468800(param_1,4);
  *param_1 = &PTR_FUN_004ccf30;
  param_1[0x6c] = 0x42c80000;
  return param_1;
}


/* 00469f20 size=30 */

undefined4 * __thiscall FUN_00469f20(void *this,byte param_1)

{
  FUN_00469f40(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00469f40 size=11 */

void __fastcall FUN_00469f40(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004ccf30;
  FUN_00468830(param_1);
  return;
}


/* 00469f50 size=91 */

undefined4 * __fastcall FUN_00469f50(undefined4 *param_1)

{
  FUN_00468800(param_1,5);
  *param_1 = &PTR_FUN_004ccf6c;
  param_1[0x6c] = 0;
  param_1[0x6d] = 0;
  param_1[0x6e] = 0;
  param_1[0x6f] = 0;
  param_1[0x72] = 1;
  param_1[0x71] = 0x3fc90fdb;
  param_1[0x70] = 0x3fc90fdb;
  param_1[0x73] = 0;
  param_1[0x74] = 0;
  param_1[0x75] = 0;
  return param_1;
}


/* 00469fb0 size=30 */

undefined4 * __thiscall FUN_00469fb0(void *this,byte param_1)

{
  FUN_00469fd0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00469fd0 size=11 */

void __fastcall FUN_00469fd0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004ccf6c;
  FUN_00468830(param_1);
  return;
}


/* 00469fe0 size=274 */

undefined4 * __fastcall FUN_00469fe0(undefined4 *param_1)

{
  FUN_00468800(param_1,6);
  *param_1 = &PTR_FUN_004ccfa4;
  param_1[0x7a] = param_1 + 0x6c;
  param_1[0x74] = param_1 + 0x6c;
  param_1[0x7b] = 0;
  param_1[0x7c] = 0;
  *(undefined1 *)((int)param_1 + 0x1f6) = 0xff;
  *(undefined1 *)((int)param_1 + 0x1f5) = 0xff;
  *(undefined1 *)(param_1 + 0x7d) = 0xff;
  *(undefined1 *)((int)param_1 + 0x96) = 0xff;
  *(undefined1 *)((int)param_1 + 0x95) = 0xff;
  *(undefined1 *)(param_1 + 0x25) = 0xff;
  *(undefined1 *)((int)param_1 + 0x1f7) = 0;
  param_1[0x87] = 0x3f800000;
  param_1[0x8b] = 0x3f800000;
  param_1[0x7e] = 0;
  param_1[0x7f] = 0;
  param_1[0x80] = 0;
  param_1[0x81] = 0;
  param_1[0x82] = 0;
  param_1[0x83] = 0;
  param_1[0x86] = 0;
  param_1[0x85] = 0;
  param_1[0x84] = 0;
  param_1[0x8a] = 0;
  param_1[0x89] = 0;
  param_1[0x88] = 0;
  param_1[0x8c] = 0;
  param_1[0x8d] = 0;
  param_1[0x90] = 0;
  param_1[0x8f] = 0;
  param_1[0x8e] = 0;
  param_1[0x93] = 0;
  param_1[0x92] = 0;
  param_1[0x91] = 0;
  param_1[0x98] = 0;
  param_1[0x94] = 0xc3fa0000;
  param_1[0x95] = 0x43960000;
  param_1[0x97] = 0xffffffff;
  param_1[0x96] = 0xffffffff;
  return param_1;
}


/* 0046a100 size=30 */

undefined4 * __thiscall FUN_0046a100(void *this,byte param_1)

{
  FUN_0046a120(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0046a120 size=156 */

void __fastcall FUN_0046a120(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  *param_1 = &PTR_FUN_004ccfa4;
  param_1[0x8e] = 0x7cf0bdc2;
  param_1[0x8f] = 0x7cf0bdc2;
  param_1[0x90] = 0x7cf0bdc2;
  param_1[0x91] = 0xfcf0bdc2;
  param_1[0x92] = 0xfcf0bdc2;
  param_1[0x93] = 0xfcf0bdc2;
  param_1[0x7c] = 0;
  if (param_1[0x17] != 0) {
    puVar2 = (undefined4 *)param_1[0x74];
    while (puVar3 = puVar2, puVar3 != param_1 + 0x6c) {
      iVar1 = param_1[0x17];
      puVar2 = (undefined4 *)puVar3[8];
      if ((puVar3 != (undefined4 *)0x0) && (iVar1 != -0x14)) {
        *puVar3 = *(undefined4 *)(iVar1 + 0x2c);
        *(undefined4 **)(iVar1 + 0x2c) = puVar3;
      }
    }
  }
  param_1[0x8c] = 0;
  param_1[0x7a] = param_1 + 0x6c;
  param_1[0x74] = param_1 + 0x6c;
  FUN_00468830(param_1);
  return;
}


/* 0046a1f0 size=155 */

undefined4 * __fastcall FUN_0046a1f0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_00468800(param_1,7);
  param_1[0x78] = 0x3f800000;
  param_1[0x77] = 0x3f800000;
  puVar2 = param_1 + 0x7b;
  *param_1 = &PTR_FUN_004ccfdc;
  param_1[0x6c] = 0;
  param_1[0x6d] = 0;
  param_1[0x6e] = 0;
  param_1[0x6f] = 0;
  param_1[0x70] = 0;
  param_1[0x71] = 0;
  param_1[0x72] = 0;
  param_1[0x73] = 0;
  param_1[0x74] = 0;
  param_1[0x76] = 0;
  param_1[0x75] = 0;
  param_1[0x79] = 0;
  param_1[0x7a] = 0;
  param_1[0x7c] = puVar2;
  *puVar2 = puVar2;
  param_1[0x7f] = 0;
  param_1[0x7e] = 0;
  puVar2 = param_1 + 0x80;
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return param_1;
}


/* 0046a300 size=30 */

undefined4 * __thiscall FUN_0046a300(void *this,byte param_1)

{
  FUN_0046a320(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0046a320 size=76 */

void __fastcall FUN_0046a320(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004ccfdc;
  if ((undefined *)param_1[0x6c] != (undefined *)0x0) {
    FUN_00430fe0((undefined *)param_1[0x6c]);
    param_1[0x6c] = 0;
  }
  if ((undefined *)param_1[0x6d] != (undefined *)0x0) {
    FUN_00430fe0((undefined *)param_1[0x6d]);
    param_1[0x6d] = 0;
  }
  FUN_00468830(param_1);
  return;
}


/* 0046a370 size=112 */

undefined4 * __fastcall FUN_0046a370(undefined4 *param_1)

{
  FUN_00468800(param_1,8);
  *param_1 = &PTR_FUN_004cd01c;
  param_1[0x6c] = 0;
  param_1[0x6d] = 0;
  param_1[0x7d] = param_1 + 0x6e;
  param_1[0x7e] = param_1 + 0x6e;
  param_1[0x7f] = 0;
  param_1[0x80] = 0;
  param_1[0x81] = 0;
  param_1[0x82] = 0;
  param_1[0x83] = 0;
  param_1[0x84] = 0;
  param_1[0x85] = 0;
  param_1[0x86] = 0;
  param_1[0x87] = 0;
  param_1[0x88] = 0;
  return param_1;
}


/* 0046a3e0 size=30 */

undefined4 * __thiscall FUN_0046a3e0(void *this,byte param_1)

{
  FUN_0046a400(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0046a400 size=87 */

void __fastcall FUN_0046a400(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar1 = param_1 + 0x6e;
  *param_1 = &PTR_FUN_004cd01c;
  puVar2 = (undefined4 *)param_1[0x7e];
  while (puVar4 = puVar2, puVar4 != puVar1) {
    puVar2 = (undefined4 *)puVar4[0x10];
    iVar3 = param_1[0x6c];
    if ((puVar4 != (undefined4 *)0x0) && (iVar3 != 0)) {
      *puVar4 = *(undefined4 *)(iVar3 + 0x18);
      *(undefined4 **)(iVar3 + 0x18) = puVar4;
    }
  }
  param_1[0x7d] = puVar1;
  param_1[0x7e] = puVar1;
  param_1[0x6c] = 0;
  FUN_00468830(param_1);
  return;
}


/* 0046a490 size=29 */

undefined4 * __fastcall FUN_0046a490(undefined4 *param_1)

{
  FUN_00468e50(param_1,9);
  *param_1 = &PTR_FUN_004cd054;
  *(undefined2 *)(param_1 + 0x9e) = 0xffff;
  return param_1;
}


/* 0046a4b0 size=30 */

undefined4 * __thiscall FUN_0046a4b0(void *this,byte param_1)

{
  FUN_0046a4d0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0046a4d0 size=11 */

void __fastcall FUN_0046a4d0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cd054;
  FUN_00468e70(param_1);
  return;
}


/* 0046a510 size=44 */

undefined4 * __fastcall FUN_0046a510(undefined4 *param_1)

{
  FUN_00468800(param_1,10);
  *param_1 = &PTR_FUN_004cd090;
  param_1[0x6c] = 0;
  param_1[0x6d] = 0;
  param_1[0x6e] = 0x3f800000;
  return param_1;
}


/* 0046a550 size=306 */

undefined4 __cdecl FUN_0046a550(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = (int *)(param_1 + 500);
  for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = 0;
    piVar4 = piVar4 + 1;
  }
  *(int *)(param_1 + 500) = param_1 + 0x68;
  *(int *)(param_1 + 0x200) = param_1 + 0xd4;
  *(int *)(param_1 + 0x1f8) = param_1 + 0x8c;
  *(int *)(param_1 + 0x20c) = param_1 + 0x140;
  *(int *)(param_1 + 0x1fc) = param_1 + 0xb0;
  *(int *)(param_1 + 0x204) = param_1 + 0xf8;
  *(int *)(param_1 + 0x218) = param_1 + 0x1ac;
  *(int *)(param_1 + 0x208) = param_1 + 0x11c;
  *(int *)(param_1 + 0x210) = param_1 + 0x164;
  *(int *)(param_1 + 0x214) = param_1 + 0x188;
  *(int *)(param_1 + 0x21c) = param_1 + 0x1d0;
  if (param_2 == 0) {
    FUN_004b7b90((uint *)(param_1 + 0x14),0x3c,0x40);
    FUN_004b7b90((uint *)(param_1 + 0x30),0x44,0x40);
  }
  else {
    FUN_004b7be0((uint *)(param_1 + 0x14),0x3c,0x400,0x400);
    FUN_004b7be0((uint *)(param_1 + 0x30),0x44,0x40,0x40);
  }
  FUN_004b7be0((uint *)(param_1 + 0x4c),0x28,0x10,0x20);
  iVar2 = param_1 + 0x224;
  iVar3 = 0xb;
  do {
    *(int *)(iVar2 + 4) = iVar2;
    *(int *)iVar2 = iVar2;
    *(undefined4 *)(iVar2 + -4) = 0;
    iVar2 = iVar2 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  piVar4 = (int *)(param_1 + 8);
  *(int *)(param_1 + 0x10) = param_1;
  *piVar4 = (int)&DAT_004ea788;
  puVar1 = DAT_004ea78c;
  *(undefined4 **)(param_1 + 0xc) = DAT_004ea78c;
  *puVar1 = piVar4;
  *(int **)(*piVar4 + 4) = piVar4;
  return 0;
}


/* 0046a690 size=120 */

undefined4 __cdecl FUN_0046a690(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar2 = (undefined4 *)(param_1 + 500);
  iVar3 = 0xb;
  do {
    (**(code **)(*(int *)*puVar2 + 0xc))();
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  FUN_004b7c50(param_1 + 0x14);
  FUN_004b7c50(param_1 + 0x30);
  FUN_004b7c50(param_1 + 0x4c);
  piVar1 = DAT_004ea78c;
  if (DAT_004ea78c != (int *)&DAT_004ea788) {
    while (piVar1[2] != param_1) {
      piVar1 = (int *)piVar1[1];
      if (piVar1 == (int *)&DAT_004ea788) {
        return 0;
      }
    }
    *(int *)(*piVar1 + 4) = piVar1[1];
    *(int *)piVar1[1] = *piVar1;
    piVar1[1] = (int)piVar1;
    *piVar1 = (int)piVar1;
  }
  return 0;
}


/* 0046a710 size=238 */

undefined4 __cdecl FUN_0046a710(undefined4 *param_1,ushort *param_2,undefined4 *param_3)

{
  int *piVar1;
  ushort uVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  *param_3 = 0;
  uVar2 = *param_2;
  if (10 < uVar2) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_om_CreateObject_004db570);
    }
    return 0x3c;
  }
  piVar4 = (int *)(**(code **)(*(int *)param_1[uVar2 + 0x7d] + 4))();
  if (piVar4 != (int *)0x0) {
    (**(code **)(*piVar4 + 0x20))(param_1,param_2);
    piVar1 = piVar4 + 0x1f;
    piVar5 = param_1 + (uVar2 + 0x22) * 4;
    piVar4[0x21] = (int)piVar4;
    *piVar1 = (int)(piVar5 + 1);
    piVar3 = (int *)piVar5[2];
    piVar4[0x20] = (int)piVar3;
    *piVar3 = (int)piVar1;
    *(int **)(*piVar1 + 4) = piVar1;
    *piVar5 = *piVar5 + 1;
    *param_1 = piVar4;
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_om_CreateObject_004db570);
  }
  return 0x43;
}


/* 0046a800 size=89 */

undefined4 __cdecl FUN_0046a800(int param_1,int param_2)

{
  int *piVar1;
  char cVar2;
  int *piVar3;
  
  cVar2 = *(char *)(param_2 + 0xbc);
  piVar1 = (int *)(param_2 + 0x7c);
  *(undefined4 *)(*piVar1 + 4) = *(undefined4 *)(param_2 + 0x80);
  piVar3 = (int *)((cVar2 + 0x22) * 0x10 + param_1);
  **(int **)(param_2 + 0x80) = *piVar1;
  *(int **)(param_2 + 0x80) = piVar1;
  *piVar1 = (int)piVar1;
  *piVar3 = *piVar3 + -1;
  if (*(char *)(param_2 + 0xbc) < '\v') {
    (**(code **)(**(int **)(param_1 + 500 + *(char *)(param_2 + 0xbc) * 4) + 8))(param_2);
  }
  return 0;
}


/* 0046a860 size=198 */

undefined4 __cdecl
FUN_0046a860(int param_1,int param_2,undefined2 param_3,undefined4 param_4,undefined4 *param_5,
            undefined4 *param_6,undefined4 *param_7)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 100);
  if (puVar1 == (undefined4 *)0x0) {
    FUN_004b7c60(param_1 + 0x4c,*(int *)(param_1 + 0x54));
    puVar1 = *(undefined4 **)(param_1 + 100);
    if (puVar1 == (undefined4 *)0x0) {
      return 1;
    }
  }
  *(undefined4 *)(param_1 + 100) = *puVar1;
  if (puVar1 == (undefined4 *)0x0) {
    return 1;
  }
  puVar1[9] = *(undefined4 *)(param_2 + 0x98);
  *(undefined4 **)(param_2 + 0x98) = puVar1;
  *(undefined2 *)(puVar1 + 7) = *(undefined2 *)(param_2 + 0xb8);
  puVar1[8] = param_4;
  *(undefined2 *)((int)puVar1 + 0x1e) = param_3;
  if (param_5 != (undefined4 *)0x0) {
    *puVar1 = *param_5;
    puVar1[1] = param_5[1];
    puVar1[2] = param_5[2];
  }
  if (param_6 == (undefined4 *)0x0) {
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0x3f800000;
  }
  else {
    puVar1[3] = *param_6;
    puVar1[4] = param_6[1];
    puVar1[5] = param_6[2];
    puVar1[6] = param_6[3];
  }
  if (param_7 != (undefined4 *)0x0) {
    *param_7 = puVar1;
  }
  return 0;
}


/* 0046a930 size=125 */

undefined4 __cdecl FUN_0046a930(int param_1,int param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined4 *)(param_2 + 0x98);
  puVar2 = *(undefined4 **)(param_2 + 0x98);
  while( true ) {
    if (puVar2 == (undefined4 *)0x0) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     s_ILTServer__RemoveAttachment_004db580);
      }
      return 1;
    }
    if (puVar2 == param_3) break;
    puVar1 = puVar2 + 9;
    puVar2 = (undefined4 *)puVar2[9];
  }
  *puVar1 = puVar2[9];
  if ((param_3 != (undefined4 *)0x0) && (param_1 != -0x4c)) {
    *param_3 = *(undefined4 *)(param_1 + 100);
    *(undefined4 **)(param_1 + 100) = param_3;
  }
  return 0;
}


/* 0046a9b0 size=55 */

void __cdecl FUN_0046a9b0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0xb;
  iVar2 = param_1 + 0x224;
  do {
    for (iVar1 = *(int *)(iVar2 + 4); iVar1 != iVar2; iVar1 = *(int *)(iVar1 + 4)) {
      *(undefined2 *)(*(int *)(iVar1 + 8) + 0xba) = 0xffff;
    }
    iVar2 = iVar2 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


/* 0046af00 size=102 */

undefined4 __thiscall FUN_0046af00(void *this,int param_1,int *param_2)

{
  int iVar1;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = (**(code **)(*param_2 + 4))(param_1 * 0xc);
      *(int *)((int)this + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  return 1;
}


/* 0046af70 size=230 */

undefined4 __thiscall FUN_0046af70(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *unaff_EBX;
  undefined4 *puVar5;
  int *piVar6;
  
  uVar2 = *(uint *)((int)this + 8);
  if (uVar2 <= param_1) {
    if (uVar2 < param_1) {
      if (param_1 <= uVar2) {
        *(uint *)((int)this + 8) = param_1;
        return 1;
      }
    }
    else if (param_1 == uVar2) {
      return 1;
    }
    puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 * 0xc);
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    uVar2 = *(uint *)((int)this + 8);
    if (param_1 < *(uint *)((int)this + 8)) {
      uVar2 = param_1;
    }
    if (param_1 == 0) {
      piVar6 = param_3;
      if (uVar2 != 0) {
        iVar3 = 0;
        do {
          puVar4 = (undefined4 *)((int)puVar1 + iVar3);
          puVar5 = (undefined4 *)(*(int *)((int)this + 4) + iVar3);
          iVar3 = iVar3 + 0xc;
          uVar2 = uVar2 - 1;
          *puVar4 = *puVar5;
          puVar4[1] = puVar5[1];
          puVar4[2] = puVar5[2];
        } while (uVar2 != 0);
        piVar6 = param_2;
      }
    }
    else {
      puVar4 = *(undefined4 **)((int)this + 4);
      puVar5 = puVar1;
      for (uVar2 = uVar2 * 0xc >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
      piVar6 = param_2;
    }
    if (*(int *)((int)this + 4) != 0) {
      (**(code **)(*piVar6 + 8))(*(int *)((int)this + 4));
      *(undefined4 *)((int)this + 4) = 0;
      puVar1 = unaff_EBX;
    }
    *(undefined4 **)((int)this + 4) = puVar1;
  }
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 0046b060 size=11 */

void __fastcall FUN_0046b060(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}


/* 0046b0a0 size=25 */

int __cdecl FUN_0046b0a0(int *param_1,undefined4 param_2,int param_3)

{
  (**(code **)(*param_1 + 4))(param_3 * 0xc);
  return;
}


/* 0046b0d0 size=13 */

void FUN_0046b0d0(void)

{
  DAT_004ea7d8 = 0;
  DAT_004ea7dc = 0;
  return;
}


/* 0046b0e0 size=12 */

void FUN_0046b0e0(void)

{
  FUN_004b9cf5(&LAB_0046b0f0);
  return;
}


/* 0046b100 size=7 */

void FUN_0046b100(void)

{
  DAT_004ea7e0 = DAT_004ea7e0 + 1;
  return;
}


/* 0046b110 size=96 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0046b110(void)

{
  int *piVar1;
  uint uVar2;
  
  if ((0 < DAT_004ea7e0) &&
     (DAT_004ea7e0 = DAT_004ea7e0 + -1, uVar2 = DAT_004ea7dc, DAT_004ea7e0 == 0)) {
    while (uVar2 != 0) {
      piVar1 = (int *)(uVar2 + 8);
      uVar2 = *(uint *)(uVar2 + 4) & -(uint)(*(uint *)(uVar2 + 4) != DAT_004ea7dc);
      if ((undefined4 *)*piVar1 != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)*piVar1)(1);
      }
    }
    DAT_004ea7dc = 0;
    DAT_004ea7d8 = 0;
    _DAT_004ea7e4 = 0;
  }
  return;
}


/* 0046b170 size=336 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0046b170: lifted from original x86 -> lt_lifted.c */


/* 0046b320 size=75 */

undefined4 __thiscall FUN_0046b320(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = ((uint)*(ushort *)((int)this + 0x36) - (uint)*(ushort *)((int)this + 0x38)) + -7;
  if (iVar1 < 0) {
    iVar1 = 0;
  }
  if (iVar1 < (int)(*(ushort *)(param_1 + 0x34) - 1)) {
    return 0;
  }
  FUN_0046b480(this,(undefined4 *)(*(int *)(param_1 + 0x54) + 1),*(ushort *)(param_1 + 0x34) - 1);
  return 1;
}


/* 0046b370 size=76 */

int __fastcall FUN_0046b370(int param_1)

{
  ushort uVar1;
  uint uVar2;
  
  uVar1 = *(ushort *)(param_1 + 0x38);
  uVar2 = (uint)uVar1;
  while (uVar1 < *(ushort *)(param_1 + 0x36)) {
    uVar1 = *(ushort *)(param_1 + 0x38);
    if ((*(uint *)(param_1 + 0x58) <= (uint)uVar1) ||
       (*(char *)((uint)uVar1 + *(int *)(param_1 + 0x54)) == '\0')) break;
    uVar1 = uVar1 + 1;
    *(ushort *)(param_1 + 0x38) = uVar1;
  }
  *(short *)(param_1 + 0x38) = *(short *)(param_1 + 0x38) + 1;
  return uVar2 + *(int *)(param_1 + 0x54);
}


/* 0046b3c0 size=123 */

void __thiscall FUN_0046b3c0(void *this,undefined4 *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  uVar2 = (uint)*(ushort *)((int)this + 0x38);
  if ((uint)*(ushort *)((int)this + 0x36) <= (param_2 & 0xffff) + uVar2) {
    param_2 = *(ushort *)((int)this + 0x36) - uVar2;
  }
  if ((*(uint *)((int)this + 0x58) & 0xffff) <= (param_2 & 0xffff) + uVar2) {
    param_2 = *(uint *)((int)this + 0x58) - uVar2;
  }
  puVar3 = (undefined4 *)(*(int *)((int)this + 0x54) + uVar2);
  for (uVar1 = (param_2 & 0xffff) >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *param_1 = *puVar3;
    puVar3 = puVar3 + 1;
    param_1 = param_1 + 1;
  }
  for (uVar2 = param_2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)param_1 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + (short)param_2;
  return;
}


/* 0046b440 size=60 */

void __thiscall FUN_0046b440(void *this,char *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  if (param_1 == (char *)0x0) {
    param_1 = (char *)0x0;
    FUN_0046b480(this,&param_1,1);
    return;
  }
  uVar2 = 0xffffffff;
  pcVar3 = param_1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  FUN_0046b480(this,(undefined4 *)param_1,~uVar2);
  return;
}


/* 0046b480 size=363 */

/* WARNING: Removing unreachable block (ram,0x0046b57a) */

void __thiscall FUN_0046b480(void *this,undefined4 *param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  uVar1 = *(ushort *)((int)this + 0x38);
  if ((uint)*(ushort *)((int)this + 0x36) <= (param_2 & 0xffff) + (uint)uVar1) {
    param_2 = (uint)*(ushort *)((int)this + 0x36) - (uint)uVar1;
  }
  uVar3 = param_2 & 0xffff;
  if ((*(uint *)((int)this + 0x58) & 0xffff) <= uVar1 + uVar3) {
    do {
      uVar2 = *(uint *)((int)this + 0x58);
      if (*(int *)((int)this + 0x5c) == 0) {
        iVar4 = FUN_0040c920(&DAT_004ecc58,0,*(int *)((int)this + 0x60) + uVar2 + 1);
        if (iVar4 != 0) {
          uVar6 = 0;
          if (uVar2 != 0) {
            do {
              uVar5 = uVar6 + 1;
              *(undefined1 *)(uVar6 + iVar4) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar5);
              uVar6 = uVar5;
            } while (uVar5 < uVar2);
          }
          uVar6 = uVar2;
          if (uVar2 < *(uint *)((int)this + 0x58)) {
            do {
              uVar6 = uVar6 + 1;
              *(undefined1 *)(iVar4 + uVar6) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar6);
            } while (uVar6 < *(uint *)((int)this + 0x58));
          }
          *(undefined1 *)(iVar4 + uVar2) = 0;
          if (*(int *)((int)this + 0x54) != 0) {
            FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x54));
            *(undefined4 *)((int)this + 0x54) = 0;
            *(undefined4 *)((int)this + 0x5c) = 0;
          }
          *(int *)((int)this + 0x54) = iVar4;
          *(undefined4 *)((int)this + 0x5c) = *(undefined4 *)((int)this + 0x60);
          goto LAB_0046b596;
        }
      }
      else {
        *(int *)((int)this + 0x5c) = *(int *)((int)this + 0x5c) + -1;
        *(undefined1 *)(*(int *)((int)this + 0x54) + uVar2) = 0;
LAB_0046b596:
        *(int *)((int)this + 0x58) = *(int *)((int)this + 0x58) + 1;
      }
    } while ((*(uint *)((int)this + 0x58) & 0xffff) <= *(ushort *)((int)this + 0x38) + uVar3);
  }
  puVar7 = (undefined4 *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38));
  for (uVar3 = uVar3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar7 = *param_1;
    param_1 = param_1 + 1;
    puVar7 = puVar7 + 1;
  }
  for (uVar3 = param_2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)param_1;
    param_1 = (undefined4 *)((int)param_1 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + (short)param_2;
  *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + (short)param_2;
  return;
}


/* 0046b770 size=252 */

int __cdecl FUN_0046b770(uint param_1,int param_2,char *param_3)

{
  int *piVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  int local_c;
  char *local_8;
  undefined2 local_4;
  
  uVar3 = param_1;
  piVar1 = (int *)(param_1 + 0x1f8);
  uVar5 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1f0) = 0;
  *piVar1 = 0;
  local_4 = 0;
  pcVar6 = param_3;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  local_c = 1;
  local_8 = param_3;
  if (3 < (int)(uVar5 - 1)) {
    param_1 = (uint)CONCAT12(param_3[uVar5 - 2],CONCAT11(param_3[uVar5 - 3],param_3[uVar5 - 4]));
    iVar4 = FUN_00436e20((char *)&param_1,&DAT_004db5b0);
    if (iVar4 != 0) {
      uVar5 = FUN_00426ae0(param_2,&local_c);
      *(uint *)(uVar3 + 0x1f0) = uVar5;
      return 0;
    }
    iVar4 = FUN_00436e20((char *)&param_1,&DAT_004db5ac);
    if (iVar4 != 0) {
      iVar4 = setupobject_48d2d0(param_2,&local_c,piVar1);
      if (iVar4 != 0) {
        return iVar4;
      }
      FUN_0049aaf0((int *)(uVar3 + 0x1fc),*piVar1);
      if (*(undefined4 **)(uVar3 + 0x204) != (undefined4 *)0x0) {
        *(undefined4 *)(uVar3 + 0x1f0) = **(undefined4 **)(uVar3 + 0x204);
      }
    }
  }
  return 0;
}


/* 0046b870 size=750 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_0046b870(int param_1,int param_2,float *param_3,float *param_4,float *param_5,float *param_6,
            float *param_7,float *param_8,float param_9,float param_10)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float *pfVar27;
  int iVar28;
  float *pfVar29;
  
  pfVar27 = param_5;
  if (param_2 != 0) {
    param_5 = (float *)param_2;
    do {
      iVar28 = _rand();
      fVar23 = (float)iVar28 * _DAT_004cc554;
      iVar28 = _rand();
      fVar1 = (float)iVar28 * _DAT_004cc554;
      iVar28 = _rand();
      fVar2 = (float)iVar28 * _DAT_004cc554;
      iVar28 = _rand();
      fVar24 = (float)iVar28 * _DAT_004cc554;
      iVar28 = _rand();
      fVar25 = (float)iVar28 * _DAT_004cc554;
      iVar28 = _rand();
      fVar26 = (float)iVar28 * _DAT_004cc554;
      fVar19 = (*param_4 - *param_3) * fVar23 + *param_3;
      fVar20 = (param_4[1] - param_3[1]) * fVar1 + param_3[1];
      fVar21 = (param_4[2] - param_3[2]) * fVar2 + param_3[2];
      fVar1 = *param_6;
      fVar2 = *pfVar27;
      fVar3 = *pfVar27;
      fVar4 = param_6[1];
      fVar5 = pfVar27[1];
      fVar6 = pfVar27[1];
      fVar7 = param_6[2];
      fVar8 = pfVar27[2];
      fVar9 = pfVar27[2];
      fVar10 = *param_8;
      fVar11 = *param_7;
      fVar12 = *param_7;
      fVar13 = param_8[1];
      fVar14 = param_7[1];
      fVar15 = param_7[1];
      fVar16 = param_8[2];
      fVar17 = param_7[2];
      iVar28 = *(int *)(param_1 + 0x1ec);
      pfVar29 = *(float **)(iVar28 + 0x18);
      fVar18 = param_7[2];
      fVar22 = (param_10 - param_9) * fVar24 + param_9;
      if (pfVar29 == (float *)0x0) {
        FUN_004b7c60(iVar28,*(int *)(iVar28 + 8));
        pfVar29 = *(float **)(iVar28 + 0x18);
        if (pfVar29 != (float *)0x0) goto LAB_0046ba02;
      }
      else {
LAB_0046ba02:
        *(float *)(iVar28 + 0x18) = *pfVar29;
        if (pfVar29 != (float *)0x0) {
          if (fVar19 < *(float *)(param_1 + 0x238)) {
            *(float *)(param_1 + 0x238) = fVar19;
          }
          if (fVar20 < *(float *)(param_1 + 0x23c)) {
            *(float *)(param_1 + 0x23c) = fVar20;
          }
          if (fVar21 < *(float *)(param_1 + 0x240)) {
            *(float *)(param_1 + 0x240) = fVar21;
          }
          if (*(float *)(param_1 + 0x244) < fVar19) {
            *(float *)(param_1 + 0x244) = fVar19;
          }
          if (*(float *)(param_1 + 0x248) < fVar20) {
            *(float *)(param_1 + 0x248) = fVar20;
          }
          if (*(float *)(param_1 + 0x24c) < fVar21) {
            *(float *)(param_1 + 0x24c) = fVar21;
          }
          pfVar29[6] = 1.0;
          pfVar29[9] = fVar19;
          pfVar29[10] = fVar20;
          pfVar29[0xb] = fVar21;
          pfVar29[3] = (fVar10 - fVar11) * fVar23 + fVar12;
          pfVar29[4] = (fVar13 - fVar14) * fVar26 + fVar15;
          pfVar29[5] = (fVar16 - fVar17) * fVar24 + fVar18;
          *pfVar29 = (fVar1 - fVar2) * fVar24 + fVar3;
          pfVar29[1] = (fVar4 - fVar5) * fVar25 + fVar6;
          pfVar29[2] = (fVar7 - fVar8) * fVar26 + fVar9;
          pfVar29[0xc] = fVar22;
          pfVar29[0xd] = fVar22;
          pfVar29[7] = *(float *)(param_1 + 0x254);
          pfVar29[0xe] = *(float *)(param_1 + 0x1e8);
          pfVar29[8] = (float)(param_1 + 0x1b0);
          *(float **)(param_1 + 0x1e8) = pfVar29;
          *(float **)((int)pfVar29[0xe] + 0x20) = pfVar29;
          *(int *)(param_1 + 0x230) = *(int *)(param_1 + 0x230) + 1;
          *(int *)(param_1 + 0x234) = *(int *)(param_1 + 0x234) + 1;
        }
      }
      param_5 = (float *)((int)param_5 + -1);
    } while (param_5 != (float *)0x0);
  }
  return;
}


/* 0046bb60 size=920 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0046bb60: lifted from original x86 -> lt_lifted.c */


/* 0046bf00 size=289 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0046bf00: lifted from original x86 -> lt_lifted.c */


