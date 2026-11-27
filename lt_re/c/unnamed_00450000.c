/* lithtech.exe decompilation - unnamed_00450000 */
#include "ghidra_types.h"

/* 00450020 size=21 */

undefined4 __fastcall FUN_00450020(int param_1)

{
  if (*(int *)(param_1 + 0x10) == 0) {
    return 0;
  }
  return *(undefined4 *)(*(int *)(param_1 + 0xc) + -0x14 + *(int *)(param_1 + 0x10) * 0x14);
}


/* 00450040 size=37 */

void __fastcall FUN_00450040(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0x43000000;
  param_1[3] = 0x41800000;
  param_1[4] = 0x41800000;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


/* 00450070 size=49 */

undefined4 * __fastcall FUN_00450070(undefined4 *param_1)

{
  param_1[6] = &PTR_LAB_004cc8fc;
  param_1[7] = 0;
  param_1[8] = 0;
  *param_1 = &PTR_FUN_004cc8ec;
  FUN_004501d0((int)param_1);
  param_1[0x2b] = 0;
  return param_1;
}


/* 004500c0 size=30 */

undefined4 * __thiscall FUN_004500c0(void *this,byte param_1)

{
  FUN_00450110(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004500e0 size=45 */

undefined4 * __thiscall FUN_004500e0(void *this,undefined4 param_1)

{
  *(undefined ***)((int)this + 0x18) = &PTR_LAB_004cc8fc;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined ***)this = &PTR_FUN_004cc8ec;
  FUN_004501d0((int)this);
  *(undefined4 *)((int)this + 0xac) = param_1;
  return this;
}


/* 00450110 size=68 */

void __fastcall FUN_00450110(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cc8ec;
  FUN_00450160((int)param_1);
  param_1[6] = &PTR_LAB_004cc8fc;
  if (param_1[7] != 0) {
    (**(code **)(DAT_004ecc58 + 8))(param_1[7]);
    param_1[7] = 0;
  }
  param_1[8] = 0;
  return;
}


/* 00450160 size=107 */

void __fastcall FUN_00450160(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  uVar3 = 0;
  piVar1 = *(int **)(*(int *)(param_1 + 0xac) + 0x174);
  if (*(int *)(param_1 + 0x20) != 0) {
    do {
      puVar2 = *(undefined4 **)(*(int *)(param_1 + 0x1c) + uVar3 * 4);
      if (puVar2 != (undefined4 *)0x0) {
        (**(code **)*puVar2)(0);
        (**(code **)(*piVar1 + 8))(puVar2);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_1 + 0x20));
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    (**(code **)(*piVar1 + 8))(*(int *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  FUN_004501d0(param_1);
  return;
}


/* 004501d0 size=163 */

void __fastcall FUN_004501d0(int param_1)

{
  *(undefined1 **)(param_1 + 0xb0) = &DAT_004e4424;
  *(undefined2 *)(param_1 + 0x10) = 0;
  *(undefined1 *)(param_1 + 0x12) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x6c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)(param_1 + 0x94) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0x3f800000;
  return;
}


/* 004502b0 size=70 */

void __thiscall FUN_004502b0(void *this,void *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  *(void **)((int)this + 0xac) = param_1;
  uVar1 = FUN_004511d0(param_1,*(byte **)((int)this + 0xb0));
  *(undefined4 *)((int)this + 0xb0) = uVar1;
  uVar2 = 0;
  if (*(int *)((int)this + 0x20) != 0) {
    do {
      (**(code **)(**(int **)(*(int *)((int)this + 0x1c) + uVar2 * 4) + 0xc))(param_1);
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)((int)this + 0x20));
  }
  return;
}


/* 00450300 size=46 */

int __fastcall FUN_00450300(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  iVar2 = 1;
  if (*(int *)(param_1 + 0x20) != 0) {
    do {
      iVar1 = FUN_00450300(*(int *)(*(int *)(param_1 + 0x1c) + uVar3 * 4));
      iVar2 = iVar2 + iVar1;
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_1 + 0x20));
  }
  return iVar2;
}


/* 00450330 size=94 */

undefined4 __thiscall FUN_00450330(void *this,uint *param_1)

{
  int iVar1;
  uint uVar2;
  
  if (*(uint *)(*(int *)((int)this + 0xac) + 0x2c) <= *param_1) {
    return 0;
  }
  uVar2 = 0;
  *(short *)((int)this + 0x10) = (short)*param_1;
  *(void **)(*(int *)(*(int *)((int)this + 0xac) + 0x28) + *param_1 * 4) = this;
  *param_1 = *param_1 + 1;
  if (*(int *)((int)this + 0x20) != 0) {
    do {
      iVar1 = FUN_00450330(*(void **)(*(int *)((int)this + 0x1c) + uVar2 * 4),param_1);
      if (iVar1 == 0) {
        return 0;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)((int)this + 0x20));
  }
  return 1;
}


/* 00450390 size=51 */

void __thiscall FUN_00450390(void *this,undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  *(undefined4 *)((int)this + 0x28) = param_1;
  if (*(int *)((int)this + 0x20) != 0) {
    do {
      FUN_00450390(*(void **)(*(int *)((int)this + 0x1c) + uVar1 * 4),
                   (uint)*(ushort *)((int)this + 0x10));
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)((int)this + 0x20));
  }
  return;
}


/* 004503d0 size=90 */

undefined4 * __thiscall FUN_004503d0(void *this,undefined4 param_1)

{
  *(undefined ***)this = &PTR_LAB_004cc95c;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  FUN_00455de0(this,0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0x10) = &PTR_LAB_004cc92c;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  FUN_00455f60((undefined4 *)((int)this + 0x10),0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  FUN_00450490(this,param_1);
  return this;
}


/* 00450430 size=84 */

undefined4 * __fastcall FUN_00450430(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cc95c;
  param_1[1] = 0;
  param_1[2] = 0;
  FUN_00455de0(param_1,0,&DAT_004ecc58);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[4] = &PTR_LAB_004cc92c;
  param_1[5] = 0;
  param_1[6] = 0;
  FUN_00455f60(param_1 + 4,0,&DAT_004ecc58);
  param_1[5] = 0;
  param_1[6] = 0;
  FUN_00450490(param_1,0);
  return param_1;
}


/* 00450490 size=10 */

void __thiscall FUN_00450490(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 0x20) = param_1;
  return;
}


/* 004504a0 size=155 */

void __fastcall FUN_004504a0(undefined4 *param_1)

{
  if (param_1[5] != 0) {
    FUN_00456ac0(param_1 + 4,*(int **)(param_1[8] + 0x174));
  }
  param_1[6] = 0;
  if (param_1[1] != 0) {
    FUN_00456e60(*(int **)(param_1[8] + 0x174),param_1[1]);
    param_1[1] = 0;
  }
  param_1[2] = 0;
  param_1[4] = &PTR_LAB_004cc92c;
  if (param_1[5] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[5]);
    param_1[5] = 0;
  }
  param_1[6] = 0;
  *param_1 = &PTR_LAB_004cc95c;
  if (param_1[1] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[1]);
    param_1[1] = 0;
  }
  param_1[2] = 0;
  return;
}


/* 00450540 size=63 */

void * __thiscall FUN_00450540(void *this,undefined4 param_1)

{
  FUN_004503d0(this,param_1);
  *(undefined ***)((int)this + 0x34) = &PTR_LAB_004cc98c;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x3c) = 0;
  *(undefined1 *)((int)this + 0x48) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x68) = param_1;
  *(undefined4 *)((int)this + 0x30) = 0x3f800000;
  *(undefined4 *)((int)this + 0x44) = 0x3f800000;
  *(undefined4 *)((int)this + 0x2c) = 0x40a00000;
  return this;
}


/* 00450580 size=91 */

void __fastcall FUN_00450580(undefined4 *param_1)

{
  void *pvVar1;
  int iVar2;
  void *this;
  
  FUN_004505e0((int)param_1);
  pvVar1 = (void *)param_1[0xe];
  param_1[0xd] = &PTR_LAB_004cc98c;
  if (pvVar1 != (void *)0x0) {
    iVar2 = param_1[0xf];
    if (iVar2 != 0) {
      this = pvVar1;
      do {
        FUN_004570c0(this,0);
        this = (void *)((int)this + 0x24);
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    (**(code **)(DAT_004ecc58 + 8))(pvVar1);
    param_1[0xe] = 0;
  }
  param_1[0xf] = 0;
  FUN_004504a0(param_1);
  return;
}


/* 004505e0 size=88 */

void __fastcall FUN_004505e0(int param_1)

{
  void *pvVar1;
  int *piVar2;
  int iVar3;
  void *this;
  
  pvVar1 = *(void **)(param_1 + 0x38);
  piVar2 = *(int **)(*(int *)(param_1 + 0x68) + 0x174);
  if (pvVar1 == (void *)0x0) {
    *(undefined4 *)(param_1 + 0x3c) = 0;
    return;
  }
  iVar3 = *(int *)(param_1 + 0x3c);
  if (iVar3 != 0) {
    this = pvVar1;
    do {
      FUN_004570c0(this,0);
      this = (void *)((int)this + 0x24);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  (**(code **)(*piVar2 + 8))(pvVar1);
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  return;
}


/* 00450640 size=123 */

undefined1 * __thiscall FUN_00450640(void *this,undefined4 param_1)

{
  *(undefined ***)((int)this + 0x10) = &PTR_LAB_004cc9bc;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  if (*(int *)((int)this + 0x14) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x14));
    *(undefined4 *)((int)this + 0x14) = 0;
    *(undefined4 *)((int)this + 0x1c) = 0;
  }
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  if (*(int *)((int)this + 0x14) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x14));
    *(undefined4 *)((int)this + 0x14) = 0;
    *(undefined4 *)((int)this + 0x1c) = 0;
  }
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x24) = param_1;
  *(undefined1 *)this = 0;
  return this;
}


/* 004506c0 size=107 */

void __fastcall FUN_004506c0(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x14) != 0) {
    FUN_00456e60(*(int **)(*(int *)(param_1 + 0x24) + 0x174),*(int *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  *(undefined4 *)(param_1 + 0x18) = 0;
  iVar1 = *(int *)(param_1 + 0x14);
  *(undefined ***)(param_1 + 0x10) = &PTR_LAB_004cc9bc;
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  *(undefined4 *)(param_1 + 0x18) = 0;
  return;
}


/* 00450730 size=38 */

void __fastcall FUN_00450730(undefined4 *param_1)

{
  *(undefined1 *)(param_1 + 7) = 0;
  param_1[0xb] = 0;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0x3f800000;
  param_1[0xc] = 0;
  return;
}


/* 00450760 size=738 */

undefined4 * __thiscall FUN_00450760(void *this,undefined4 param_1,undefined4 param_2)

{
  undefined4 *this_00;
  undefined4 *this_01;
  int iVar1;
  undefined **local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_00468450((void *)((int)this + 0x14));
  this_00 = (undefined4 *)((int)this + 0x24);
  *this_00 = &PTR_LAB_004cc8fc;
  *(undefined4 *)((int)this + 0x28) = 0;
  *(undefined4 *)((int)this + 0x2c) = 0;
  FUN_00456830(this_00,0);
  *(undefined4 *)((int)this + 0x34) = &PTR_LAB_004ccb10;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x3c) = 0;
  FUN_00456830((undefined4 *)((int)this + 0x34),0);
  *(undefined4 *)((int)this + 0x44) = &PTR_LAB_004ccae0;
  *(undefined4 *)((int)this + 0x48) = 0;
  *(undefined4 *)((int)this + 0x4c) = 0;
  FUN_00456830((undefined4 *)((int)this + 0x44),0);
  *(undefined4 *)((int)this + 0x54) = &PTR_LAB_004ccab0;
  *(undefined4 *)((int)this + 0x58) = 0;
  *(undefined4 *)((int)this + 0x5c) = 0;
  FUN_00456250((undefined4 *)((int)this + 0x54),0);
  this_01 = (undefined4 *)((int)this + 0x70);
  *this_01 = &PTR_LAB_004cca80;
  *(undefined4 *)((int)this + 0x74) = 0;
  *(undefined4 *)((int)this + 0x78) = 0;
  FUN_00456430(this_01,0);
  FUN_0044f610((void *)((int)this + 0x84),param_1);
  *(undefined4 *)((int)this + 0x8c) = &PTR_LAB_004cca50;
  *(undefined4 *)((int)this + 0x90) = 0;
  *(undefined4 *)((int)this + 0x94) = 0;
  *(undefined4 *)((int)this + 0x98) = 0;
  *(undefined4 *)((int)this + 0x9c) = 0;
  FUN_004565d0((undefined4 *)((int)this + 0x8c),0,0);
  *(undefined4 *)((int)this + 0xa0) = 0;
  *(undefined4 *)((int)this + 0x154) = &PTR_LAB_004cca20;
  *(undefined4 *)((int)this + 0x158) = 0;
  *(undefined4 *)((int)this + 0x15c) = 0;
  FUN_00456830((undefined4 *)((int)this + 0x154),0);
  *(undefined4 *)((int)this + 0x164) = &PTR_LAB_004cc9f0;
  *(undefined4 *)((int)this + 0x168) = 0;
  *(undefined4 *)((int)this + 0x16c) = 0;
  FUN_004568a0((undefined4 *)((int)this + 0x164),0);
  FUN_004b8750((undefined4 *)((int)this + 0x17c));
  FUN_0044f820((undefined4 *)((int)this + 0x1d8));
  FUN_00450070((undefined4 *)((int)this + 0x210));
  *(undefined ***)this = &PTR_FUN_004cc9ec;
  *(undefined4 *)((int)this + 0x174) = param_1;
  *(undefined4 *)((int)this + 0x178) = param_2;
  *(undefined4 *)((int)this + 0xa4) = 0x42c00000;
  *(void **)((int)this + 0x10) = this;
  *(undefined **)((int)this + 4) = PTR_DAT_004da97c;
  *(undefined4 *)((int)this + 100) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x20c) = 0;
  local_10 = &PTR_LAB_004cc8fc;
  local_c = 0;
  local_8 = 0;
  FUN_00456830(&local_10,0);
  FUN_00456be0(this_00,(int)&local_10,&DAT_004ecc58);
  local_10 = &PTR_LAB_004cc8fc;
  FUN_00455a50(&local_10,0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0x6c) = 0;
  *(undefined4 *)((int)this + 0xa8) = 0x42480000;
  *(undefined4 *)((int)this + 0xac) = 0;
  FUN_00451ac0(this,20000.0,20000.0);
  *(undefined4 *)((int)this + 0xe0) = 0x42480000;
  *(undefined4 *)((int)this + 200) = 0x42c80000;
  *(undefined4 *)((int)this + 0xc4) = 0x42c80000;
  *(undefined4 *)((int)this + 0xe4) = 0x42480000;
  *(undefined4 *)((int)this + 0xd8) = 0x43480000;
  *(undefined4 *)((int)this + 0xdc) = 0x43480000;
  *(undefined4 *)((int)this + 0xc0) = 0;
  *(undefined4 *)((int)this + 0xcc) = 0x3e800000;
  *(undefined4 *)((int)this + 0xd0) = 0x3f400000;
  *(undefined4 *)((int)this + 0x140) = 0;
  *(undefined4 *)((int)this + 0x14c) = 0;
  *(undefined4 *)((int)this + 0xd4) = 0;
  *(undefined4 *)((int)this + 0xe8) = 0;
  *(undefined4 *)((int)this + 0xec) = 0;
  *(undefined4 *)((int)this + 0xf0) = 0;
  *(undefined4 *)((int)this + 0x150) = 0;
  *(undefined4 *)((int)this + 0xf4) = 0xffffffff;
  *(undefined4 *)((int)this + 0xf8) = 0xffffffff;
  *(undefined4 *)((int)this + 0x13c) = 0;
  local_10 = &PTR_LAB_004cca80;
  local_c = 0;
  local_8 = 0;
  FUN_00456430(&local_10,0);
  FUN_00456f70(this_01,(int)&local_10,&DAT_004ecc58);
  local_10 = &PTR_LAB_004cca80;
  FUN_00456490(&local_10,0,&DAT_004ecc58);
  *(undefined1 **)((int)this + 0x80) = &DAT_004e4424;
  *(int **)((int)this + 0x2c4) = (int *)((int)this + 0x210);
  (**(code **)(*(int *)((int)this + 0x210) + 0xc))(this);
  *(undefined4 *)((int)this + 0x1d4) = 1;
  *(int *)((int)this + 0x194) = (int)this + 0x1d8;
  *(void **)((int)this + 0x1fc) = this;
  *(void **)(*(int *)((int)this + 0x194) + 0x28) = this;
  iVar1 = _rand();
  *(int *)((int)this + 0x1f8) = iVar1;
  *(undefined4 *)((int)this + 400) = 0;
  DAT_004ea6e4 = DAT_004ea6e4 + 0x2c8;
  return this;
}


/* 00450a50 size=30 */

undefined4 * __thiscall FUN_00450a50(void *this,byte param_1)

{
  FUN_00450a70(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00450a70 size=351 */

void __fastcall FUN_00450a70(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cc9ec;
  FUN_00450bd0(param_1,1);
  DAT_004ea6e4 = (DAT_004ea6e4 + -0x2c8) - param_1[99];
  FUN_00450110(param_1 + 0x84);
  FUN_0044f8b0(param_1 + 0x76);
  FUN_004b87c0(param_1 + 0x5f);
  param_1[0x59] = &PTR_LAB_004cc9f0;
  FUN_00456900(param_1 + 0x59,0,&DAT_004ecc58);
  param_1[0x55] = &PTR_LAB_004cca20;
  FUN_00455a50(param_1 + 0x55,0,&DAT_004ecc58);
  param_1[0x23] = &PTR_LAB_004cca50;
  FUN_00456680(param_1 + 0x23,0,&DAT_004ecc58);
  thunk_FUN_0044f640(param_1 + 0x21);
  param_1[0x1c] = &PTR_LAB_004cca80;
  if (param_1[0x1d] != 0) {
    FUN_00456ac0(param_1 + 0x1c,&DAT_004ecc58);
  }
  param_1[0x1e] = 0;
  param_1[0x15] = &PTR_LAB_004ccab0;
  if (param_1[0x16] != 0) {
    FUN_00456ac0(param_1 + 0x15,&DAT_004ecc58);
  }
  param_1[0x17] = 0;
  param_1[0x11] = &PTR_LAB_004ccae0;
  if (param_1[0x12] != 0) {
    FUN_00456ac0(param_1 + 0x11,&DAT_004ecc58);
  }
  param_1[0x13] = 0;
  param_1[0xd] = &PTR_LAB_004ccb10;
  if (param_1[0xe] != 0) {
    FUN_00456ac0(param_1 + 0xd,&DAT_004ecc58);
  }
  param_1[0xf] = 0;
  param_1[9] = &PTR_LAB_004cc8fc;
  if (param_1[10] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[10]);
    param_1[10] = 0;
  }
  param_1[0xb] = 0;
  thunk_FUN_00468490(param_1 + 5);
  return;
}


/* 00450bd0 size=418 */

void __thiscall FUN_00450bd0(void *this,int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  
  FUN_00468490((void *)((int)this + 0x14));
  puVar2 = *(undefined4 **)((int)this + 0x2c4);
  puVar1 = (undefined4 *)((int)this + 0x210);
  if ((puVar2 != puVar1) && (piVar3 = *(int **)((int)this + 0x174), puVar2 != (undefined4 *)0x0)) {
    (**(code **)*puVar2)(0);
    (**(code **)(*piVar3 + 8))(puVar2);
  }
  FUN_00450160((int)puVar1);
  piVar3 = *(int **)((int)this + 0x174);
  *(undefined4 **)((int)this + 0x2c4) = puVar1;
  uVar5 = 0;
  if (*(int *)((int)this + 0x3c) != 0) {
    do {
      puVar1 = *(undefined4 **)(*(int *)((int)this + 0x38) + uVar5 * 4);
      if (puVar1 != (undefined4 *)0x0) {
        FUN_00456ae0(piVar3,puVar1,1);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)((int)this + 0x3c));
  }
  FUN_00455a50((void *)((int)this + 0x34),0,piVar3);
  FUN_00450d80((int)this);
  FUN_00450e10(this,param_1);
  piVar3 = *(int **)((int)this + 0x174);
  uVar5 = 0;
  if (*(int *)((int)this + 0x15c) != 0) {
    do {
      iVar4 = *(int *)(*(int *)((int)this + 0x158) + uVar5 * 4);
      if (iVar4 != 0) {
        (**(code **)(*piVar3 + 8))(iVar4);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)((int)this + 0x15c));
  }
  FUN_00455a50((void *)((int)this + 0x154),0,piVar3);
  piVar3 = *(int **)((int)this + 0x174);
  uVar5 = 0;
  if (*(int *)((int)this + 0x4c) != 0) {
    do {
      iVar4 = *(int *)(*(int *)((int)this + 0x48) + uVar5 * 4);
      if (iVar4 != 0) {
        FUN_00456b10(piVar3,iVar4,1);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)((int)this + 0x4c));
  }
  FUN_00455a50((void *)((int)this + 0x44),0,piVar3);
  FUN_00456490((void *)((int)this + 0x70),0,*(int **)((int)this + 0x174));
  FUN_004562b0((void *)((int)this + 0x54),0,*(int **)((int)this + 0x174));
  if (*(int *)((int)this + 0x28) != 0) {
    FUN_00456ac0((void *)((int)this + 0x24),*(int **)((int)this + 0x174));
  }
  *(undefined4 *)((int)this + 0x2c) = 0;
  FUN_0044f640((int *)((int)this + 0x84));
  FUN_00451b60((int)this);
  if (*(int *)((int)this + 0x90) != 0) {
    FUN_00456e60(*(int **)((int)this + 0x174),*(int *)((int)this + 0x90));
    *(undefined4 *)((int)this + 0x90) = 0;
    *(undefined4 *)((int)this + 0x98) = 0;
  }
  *(undefined4 *)((int)this + 0x94) = 0;
  *(undefined4 *)((int)this + 100) = 0;
  return;
}


/* 00450d80 size=135 */

void __fastcall FUN_00450d80(int param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  uint local_4;
  
  iVar3 = 0;
  local_4 = 0;
  if (*(int *)(param_1 + 0x16c) != 0) {
    do {
      puVar1 = *(undefined4 **)(*(int *)(param_1 + 0x168) + iVar3);
      if ((puVar1[8] == param_1) &&
         (piVar2 = *(int **)(param_1 + 0x174), puVar1 != (undefined4 *)0x0)) {
        (**(code **)*puVar1)(0);
        (**(code **)(*piVar2 + 8))(puVar1);
      }
      local_4 = local_4 + 1;
      iVar3 = iVar3 + 0x20;
    } while (local_4 < *(uint *)(param_1 + 0x16c));
  }
  if (*(int *)(param_1 + 0x168) != 0) {
    (**(code **)(**(int **)(param_1 + 0x178) + 8))(*(int *)(param_1 + 0x168));
    *(undefined4 *)(param_1 + 0x168) = 0;
  }
  *(undefined4 *)(param_1 + 0x16c) = 0;
  return;
}


/* 00450e10 size=211 */

void __thiscall FUN_00450e10(void *this,int param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 *puVar5;
  uint local_4;
  
  local_4 = 0;
  if (*(int *)((int)this + 0x1d4) != 0) {
    puVar5 = (undefined4 *)((int)this + 0x194);
    do {
      puVar1 = (undefined4 *)*puVar5;
      if (puVar1 != (undefined4 *)0x0) {
        if (((puVar1 != *(undefined4 **)((int)this + 0x194)) &&
            (pvVar2 = (void *)puVar1[10], pvVar2 != (void *)0x0)) && (pvVar2 != this)) {
          if (*(int *)((int)pvVar2 + 0x20c) != 0) {
            *(int *)((int)pvVar2 + 0x20c) = *(int *)((int)pvVar2 + 0x20c) + -1;
          }
          if (((param_1 != 0) && (puVar3 = (undefined4 *)puVar1[10], puVar3[0x83] == 0)) &&
             (puVar3 != (undefined4 *)0x0)) {
            (**(code **)*puVar3)(1);
          }
        }
        FUN_0044f900((int)puVar1);
        if ((puVar1 != *(undefined4 **)((int)this + 0x194)) &&
           (puVar1 != (undefined4 *)((int)this + 0x1d8))) {
          piVar4 = *(int **)((int)this + 0x174);
          FUN_0044f8b0(puVar1);
          (**(code **)(*piVar4 + 8))(puVar1);
        }
      }
      local_4 = local_4 + 1;
      puVar5 = puVar5 + 1;
    } while (local_4 < *(uint *)((int)this + 0x1d4));
  }
  *(undefined4 *)((int)this + 0x1d4) = 1;
  *(int *)((int)this + 0x194) = (int)this + 0x1d8;
  return;
}


/* 00450ef0 size=170 */

undefined4 __thiscall FUN_00450ef0(void *this,uint param_1)

{
  void *this_00;
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = FUN_00450fa0(this,param_1);
  if ((iVar1 == 0) || (iVar1 = FUN_00451050(this,param_1), iVar1 == 0)) {
    return 0;
  }
  iVar1 = 0;
  uVar2 = 0;
  if (*(int *)((int)this + 0x3c) != 0) {
    iVar3 = *(int *)((int)this + 0x38);
    do {
      *(int *)(*(int *)(iVar3 + uVar2 * 4) + 0x28) = iVar1;
      iVar3 = *(int *)((int)this + 0x38);
      iVar1 = iVar1 + *(int *)(*(int *)(iVar3 + uVar2 * 4) + 8);
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)((int)this + 0x3c));
  }
  uVar2 = 0;
  if (*(int *)((int)this + 0x16c) != 0) {
    iVar1 = 0;
    do {
      this_00 = *(void **)(iVar1 + *(int *)((int)this + 0x168));
      if ((*(void **)((int)this_00 + 0x20) == this) &&
         (iVar3 = FUN_0044ff90(this_00,param_1), iVar3 == 0)) {
        return 0;
      }
      uVar2 = uVar2 + 1;
      iVar1 = iVar1 + 0x20;
    } while (uVar2 < *(uint *)((int)this + 0x16c));
  }
  iVar1 = FUN_00451520((int)this);
  *(int *)((int)this + 100) = iVar1;
  iVar1 = FUN_004514d0(this,0);
  *(int *)((int)this + 0x68) = iVar1;
  return 1;
}


/* 00450fa0 size=166 */

undefined4 __thiscall FUN_00450fa0(void *this,int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if ((param_1 == 0) &&
     (iVar3 = *(int *)((int)this + 0x78), iVar2 = FUN_00450300(*(int *)((int)this + 0x2c4)),
     iVar3 == iVar2)) {
    return 1;
  }
  if (*(int *)((int)this + 0x74) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x74));
    *(undefined4 *)((int)this + 0x74) = 0;
  }
  *(undefined4 *)((int)this + 0x78) = 0;
  iVar3 = FUN_00450300(*(int *)((int)this + 0x2c4));
  piVar1 = *(int **)((int)this + 0x174);
  if ((iVar3 != *(int *)((int)this + 0x78)) || (iVar3 == 0)) {
    if (*(int *)((int)this + 0x74) != 0) {
      (**(code **)(*piVar1 + 8))(*(int *)((int)this + 0x74));
      *(undefined4 *)((int)this + 0x74) = 0;
    }
    *(int *)((int)this + 0x78) = iVar3;
    if (iVar3 != 0) {
      iVar3 = (**(code **)(*piVar1 + 4))(iVar3 << 6);
      *(int *)((int)this + 0x74) = iVar3;
      if (iVar3 == 0) {
        *(undefined4 *)((int)this + 0x78) = 0;
        return 0;
      }
    }
  }
  return 1;
}


/* 00451050 size=224 */

undefined4 __thiscall FUN_00451050(void *this,uint param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  
  if ((param_1 != 0) || (*(int *)((int)this + 0x2c) != *(int *)((int)this + 0x78))) {
    FUN_00455a50((void *)((int)this + 0x24),0,*(int **)((int)this + 0x174));
    uVar1 = *(uint *)((int)this + 0x78);
    piVar2 = *(int **)((int)this + 0x174);
    if ((uVar1 != *(uint *)((int)this + 0x2c)) || (uVar1 == 0)) {
      if (*(int *)((int)this + 0x28) != 0) {
        FUN_00456ac0((void *)((int)this + 0x24),piVar2);
      }
      *(uint *)((int)this + 0x2c) = uVar1;
      if (uVar1 != 0) {
        iVar3 = FUN_00456f10(piVar2,0,uVar1);
        *(int *)((int)this + 0x28) = iVar3;
        if (iVar3 == 0) {
          *(undefined4 *)((int)this + 0x2c) = 0;
          return 0;
        }
      }
    }
    uVar4 = 0;
    if (*(int *)((int)this + 0x2c) != 0) {
      do {
        uVar4 = uVar4 + 1;
        *(undefined4 *)(*(int *)((int)this + 0x28) + -4 + uVar4 * 4) = 0;
      } while (uVar4 < *(uint *)((int)this + 0x2c));
    }
    param_1 = 0;
    iVar3 = FUN_00450330(*(void **)((int)this + 0x2c4),&param_1);
    if (iVar3 == 0) {
      return 0;
    }
    *(uint *)((int)this + 0x6c) = uVar1 >> 2;
    if ((uVar1 & 3) != 0) {
      *(uint *)((int)this + 0x6c) = (uVar1 >> 2) + 1;
    }
    FUN_00450390(*(void **)((int)this + 0x2c4),0xffffffff);
  }
  return 1;
}


/* 00451130 size=78 */

int __thiscall FUN_00451130(void *this,byte *param_1,uint *param_2)

{
  void *this_00;
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (*(int *)((int)this + 0x3c) != 0) {
    do {
      iVar1 = *(int *)(*(int *)((int)this + 0x38) + uVar3 * 4);
      this_00 = (void *)(iVar1 + 0x48);
      uVar2 = FUN_004c4c00(this_00,param_1,this_00);
      if (uVar2 == 0) {
        if (param_2 != (uint *)0x0) {
          *param_2 = uVar3;
        }
        return iVar1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)((int)this + 0x3c));
  }
  return 0;
}


/* 00451180 size=75 */

byte * __thiscall FUN_00451180(void *this,byte *param_1,uint *param_2)

{
  byte *pbVar1;
  uint uVar2;
  void *this_00;
  void *extraout_ECX;
  uint uVar3;
  
  uVar3 = 0;
  this_00 = this;
  if (*(int *)((int)this + 0x4c) != 0) {
    do {
      pbVar1 = *(byte **)(*(int *)((int)this + 0x48) + uVar3 * 4);
      uVar2 = FUN_004c4c00(this_00,param_1,pbVar1);
      if (uVar2 == 0) {
        if (param_2 != (uint *)0x0) {
          *param_2 = uVar3;
        }
        return pbVar1;
      }
      uVar3 = uVar3 + 1;
      this_00 = extraout_ECX;
    } while (uVar3 < *(uint *)((int)this + 0x4c));
  }
  return (byte *)0x0;
}


/* 004511d0 size=19 */

int __thiscall FUN_004511d0(void *this,byte *param_1)

{
  FUN_0044f670((void *)((int)this + 0x84),param_1);
  return;
}


/* 004511f0 size=82 */

undefined4 __thiscall FUN_004511f0(void *this,byte *param_1,uint *param_2)

{
  void *this_00;
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (*(int *)((int)this + 0x78) != 0) {
    do {
      this_00 = *(void **)(*(int *)((int)this + 0x28) + uVar2 * 4);
      uVar1 = FUN_004c4c00(this_00,*(byte **)((int)this_00 + 0xb0),param_1);
      if (uVar1 == 0) {
        if (param_2 != (uint *)0x0) {
          *param_2 = uVar2;
        }
        return *(undefined4 *)(*(int *)((int)this + 0x28) + uVar2 * 4);
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)((int)this + 0x78));
  }
  return 0;
}


/* 00451250 size=113 */

int __thiscall FUN_00451250(void *this,void *param_1,uint *param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = 0;
  if (*(int *)((int)this + 0x16c) != 0) {
    iVar3 = 0;
    do {
      iVar1 = *(int *)(iVar3 + *(int *)((int)this + 0x168));
      uVar2 = FUN_004c4c00(param_1,*(byte **)(iVar1 + 0x24),param_1);
      if (uVar2 == 0) {
        if (param_2 != (uint *)0x0) {
          *param_2 = uVar4;
        }
        if (param_3 != (int *)0x0) {
          *param_3 = uVar4 * 0x20 + *(int *)((int)this + 0x168);
        }
        return iVar1;
      }
      uVar4 = uVar4 + 1;
      iVar3 = iVar3 + 0x20;
    } while (uVar4 < *(uint *)((int)this + 0x16c));
  }
  return 0;
}


/* 004512d0 size=104 */

int * __thiscall FUN_004512d0(void *this,byte *param_1,void *param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  
  uVar4 = 0;
  if (*(int *)((int)this + 0x16c) != 0) {
    iVar3 = 0;
    do {
      piVar5 = (int *)(iVar3 + *(int *)((int)this + 0x168));
      iVar1 = *piVar5;
      if (*(void **)(iVar1 + 0x20) == param_2) {
        uVar2 = FUN_004c4c00(param_2,*(byte **)(iVar1 + 0x24),param_1);
        if (uVar2 == 0) {
          if (param_3 != (uint *)0x0) {
            *param_3 = uVar4;
          }
          return piVar5;
        }
      }
      uVar4 = uVar4 + 1;
      iVar3 = iVar3 + 0x20;
    } while (uVar4 < *(uint *)((int)this + 0x16c));
  }
  return (int *)0x0;
}


/* 00451340 size=157 */

void __fastcall FUN_00451340(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  float *pfVar5;
  float *pfVar6;
  float local_c0 [3];
  undefined4 local_b4;
  undefined4 local_a4;
  undefined4 local_94;
  float local_80 [16];
  float local_40 [16];
  
  uVar4 = 0;
  uVar3 = *(uint *)(param_1 + 0x78);
  if (uVar3 != 0) {
    do {
      iVar1 = *(int *)(*(int *)(param_1 + 0x28) + uVar4 * 4);
      if (*(uint *)(iVar1 + 0x28) < uVar3) {
        FUN_004513e0((float *)(*(int *)(*(int *)(param_1 + 0x28) + *(uint *)(iVar1 + 0x28) * 4) +
                              0x2c),local_80);
        pfVar5 = local_80;
        pfVar6 = local_40;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pfVar6 = *pfVar5;
          pfVar5 = pfVar5 + 1;
          pfVar6 = pfVar6 + 1;
        }
        FUN_0043d430(local_c0,local_40,(float *)(iVar1 + 0x2c));
        *(undefined4 *)(iVar1 + 4) = local_b4;
        *(undefined4 *)(iVar1 + 8) = local_a4;
        *(undefined4 *)(iVar1 + 0xc) = local_94;
      }
      else {
        *(undefined4 *)(iVar1 + 4) = 0;
        *(undefined4 *)(iVar1 + 8) = 0;
        *(undefined4 *)(iVar1 + 0xc) = 0;
      }
      uVar3 = *(uint *)(param_1 + 0x78);
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar3);
  }
  return;
}


/* 004513e0 size=182 */

void __cdecl FUN_004513e0(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = param_1[3];
  fVar2 = param_1[7];
  fVar3 = param_1[0xb];
  *param_2 = *param_1;
  param_2[1] = param_1[4];
  param_2[2] = param_1[8];
  param_2[4] = param_1[1];
  param_2[5] = param_1[5];
  param_2[6] = param_1[9];
  param_2[8] = param_1[2];
  param_2[9] = param_1[6];
  fVar4 = param_1[10];
  param_2[0xf] = 1.0;
  param_2[10] = fVar4;
  param_2[0xe] = 0.0;
  param_2[0xd] = 0.0;
  param_2[0xc] = 0.0;
  param_2[3] = -(fVar1 * *param_2 + fVar2 * param_2[1] + fVar3 * param_2[2]);
  param_2[7] = -(fVar2 * param_2[5] + fVar3 * param_2[6] + fVar1 * param_2[4]);
  param_2[0xb] = -(fVar4 * fVar3 + fVar1 * param_2[8] + fVar2 * param_2[9]);
  return;
}


/* 004514a0 size=44 */

void __fastcall FUN_004514a0(undefined4 *param_1)

{
  param_1[3] = 0xffffffff;
  param_1[6] = 0xffffffff;
  param_1[8] = 0;
  *param_1 = 0;
  *(undefined2 *)(param_1 + 1) = 0;
  *(undefined2 *)((int)param_1 + 6) = 0;
  param_1[2] = 0;
  *(undefined2 *)(param_1 + 4) = 0;
  *(undefined2 *)((int)param_1 + 0x12) = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  return;
}


/* 004514d0 size=67 */

int __thiscall FUN_004514d0(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  iVar3 = *(int *)((int)this + 0x3c);
  iVar1 = 0;
  if (iVar3 != 0) {
    piVar4 = *(int **)((int)this + 0x38);
    do {
      iVar2 = *piVar4;
      if (param_1 == 0) {
LAB_004514ff:
        if (iVar2 != 0) {
          iVar1 = iVar1 + *(int *)(iVar2 + 0x18);
        }
      }
      else if (param_1 - 1U < *(uint *)(iVar2 + 0x3c)) {
        iVar2 = *(int *)(iVar2 + 0x38) + (param_1 - 1U) * 0x24;
        goto LAB_004514ff;
      }
      piVar4 = piVar4 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return iVar1;
}


/* 00451520 size=30 */

int __fastcall FUN_00451520(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x3c);
  iVar2 = 0;
  if (iVar4 != 0) {
    piVar3 = *(int **)(param_1 + 0x38);
    do {
      iVar1 = *piVar3;
      piVar3 = piVar3 + 1;
      iVar2 = iVar2 + *(int *)(iVar1 + 8);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  return iVar2;
}


/* 00451540 size=66 */

int __thiscall FUN_00451540(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  iVar3 = *(int *)((int)this + 0x1d4);
  iVar2 = 0;
  if (iVar3 != 0) {
    piVar4 = (int *)((int)this + 0x194);
    do {
      iVar1 = *(int *)(*piVar4 + 0x28);
      if ((iVar1 != 0) && ((*piVar4 != *(int *)((int)this + 0x194) || (param_1 != 0)))) {
        iVar2 = iVar2 + *(int *)(iVar1 + 0x16c);
      }
      piVar4 = piVar4 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return iVar2;
}


/* 00451590 size=37 */

int __fastcall FUN_00451590(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x16c);
  iVar1 = 0;
  if (iVar3 != 0) {
    piVar2 = *(int **)(param_1 + 0x168);
    do {
      if (*(int *)(*piVar2 + 0x20) == param_1) {
        iVar1 = iVar1 + 1;
      }
      piVar2 = piVar2 + 8;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return iVar1;
}


/* 00451a80 size=60 */

void __thiscall
FUN_00451a80(void *this,undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
            undefined2 param_5,undefined4 param_6)

{
  *(undefined4 *)this = param_1;
  *(undefined2 *)((int)this + 4) = param_2;
  *(undefined2 *)((int)this + 6) = param_3;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined2 *)((int)this + 0x10) = param_4;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined2 *)((int)this + 0x12) = param_5;
  *(undefined4 *)((int)this + 0x1c) = param_6;
  return;
}


/* 00451ac0 size=51 */

void __thiscall FUN_00451ac0(void *this,float param_1,float param_2)

{
  *(float *)((int)this + 0xb0) = param_1;
  *(float *)((int)this + 0xb8) = param_2;
  *(float *)((int)this + 0xb4) = param_1 * param_1;
  *(float *)((int)this + 0xbc) = param_2 * param_2;
  return;
}


/* 00451b00 size=91 */

undefined4 __thiscall FUN_00451b00(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  FUN_00451b60((int)this);
  uVar3 = 0xffffffff;
  pcVar2 = param_1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = (char *)FUN_00430de0(~uVar3);
  if (pcVar2 == (char *)0x0) {
    return 0;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = param_1;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  pcVar6 = pcVar2;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  *(char **)((int)this + 4) = pcVar2;
  return 1;
}


/* 00451b60 size=40 */

void __fastcall FUN_00451b60(int param_1)

{
  if (*(undefined **)(param_1 + 4) == PTR_DAT_004da97c) {
    *(undefined **)(param_1 + 4) = PTR_DAT_004da97c;
    return;
  }
  FUN_00430df0(*(undefined **)(param_1 + 4));
  *(undefined **)(param_1 + 4) = PTR_DAT_004da97c;
  return;
}


/* 00451b90 size=34 */

int __thiscall FUN_00451b90(void *this,int param_1,int *param_2)

{
  FUN_0044f5b0(*(int *)((int)this + 0x2c4),*(int *)(param_1 + 0x2c4),param_2);
  return;
}


/* 00451bc0 size=114 */

void __thiscall
FUN_00451bc0(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  *(undefined4 *)this = param_1;
  *(undefined4 *)((int)this + 4) = param_2;
  *(undefined4 *)((int)this + 8) = param_3;
  *(undefined4 *)((int)this + 0xc) = param_4;
  *(undefined4 *)((int)this + 0x10) = param_5;
  *(undefined4 *)((int)this + 0x14) = param_6;
  *(undefined4 *)((int)this + 0x18) = param_7;
  *(undefined4 *)((int)this + 0x1c) = param_8;
  *(undefined4 *)((int)this + 0x20) = param_9;
  *(undefined4 *)((int)this + 0x24) = param_10;
  *(undefined4 *)((int)this + 0x28) = param_11;
  *(undefined4 *)((int)this + 0x2c) = param_12;
  *(undefined4 *)((int)this + 0x30) = param_13;
  *(undefined4 *)((int)this + 0x34) = param_14;
  *(undefined4 *)((int)this + 0x38) = param_15;
  *(undefined4 *)((int)this + 0x3c) = param_16;
  return;
}


/* 00451c40 size=83 */

undefined4 __thiscall
FUN_00451c40(void *this,uint param_1,int param_2,int param_3,undefined4 param_4)

{
  if (0xf < param_1) {
    return 0;
  }
  *(undefined4 *)(param_2 + 0x1c) = param_4;
  *(void **)(param_2 + 0x24) = this;
  *(int *)(param_2 + 0x28) = param_3;
  *(undefined4 *)(param_2 + 0x18) = 0;
  if ((param_3 != 0) && ((void *)param_3 != this)) {
    *(int *)(param_3 + 0x20c) = *(int *)(param_3 + 0x20c) + 1;
  }
  *(int *)((int)this + param_1 * 4 + 0x194) = param_2;
  return 1;
}


/* 00451ca0 size=87 */

int __thiscall FUN_00451ca0(void *this,byte *param_1,uint *param_2)

{
  void *this_00;
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (*(int *)((int)this + 0x15c) != 0) {
    do {
      iVar1 = *(int *)(*(int *)((int)this + 0x158) + uVar3 * 4);
      this_00 = (void *)(iVar1 + 0x1c);
      uVar2 = FUN_004c4c00(this_00,this_00,param_1);
      if (uVar2 == 0) {
        if (param_2 != (uint *)0x0) {
          *param_2 = uVar3;
        }
        return iVar1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)((int)this + 0x15c));
  }
  return 0;
}


/* 00451f00 size=31 */

void __thiscall FUN_00451f00(void *this,undefined4 *param_1)

{
  *(undefined4 *)this = *param_1;
  *(undefined4 *)((int)this + 4) = param_1[1];
  *(undefined4 *)((int)this + 8) = param_1[2];
  *(undefined4 *)((int)this + 0xc) = param_1[3];
  return;
}


/* 00453e40 size=51 */

void __thiscall FUN_00453e40(void *this,int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1 - (int)this;
  iVar4 = 3;
  puVar1 = (undefined4 *)((int)this + 8);
  do {
    puVar2 = puVar1 + 2;
    *(undefined2 *)this = *(undefined2 *)(iVar3 + (int)this);
    *puVar1 = *(undefined4 *)(iVar3 + -8 + (int)puVar2);
    puVar1[1] = *(undefined4 *)(iVar3 + -4 + (int)puVar2);
    this = (void *)((int)this + 2);
    iVar4 = iVar4 + -1;
    puVar1 = puVar2;
  } while (iVar4 != 0);
  return;
}


