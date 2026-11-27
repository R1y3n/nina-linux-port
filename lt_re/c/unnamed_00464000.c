/* lithtech.exe decompilation - unnamed_00464000 */
#include "ghidra_types.h"

/* 004641c0 size=377 */

void __cdecl FUN_004641c0(int param_1,float *param_2,float *param_3,float *param_4)

{
  float *pfVar1;
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
  float local_40;
  float local_3c;
  float local_38;
  float local_30;
  float local_2c;
  float local_28;
  float local_20;
  float local_1c;
  float local_18;
  
  *param_3 = *param_2;
  pfVar1 = (float *)(param_1 + 0x9c);
  param_3[1] = param_2[1];
  param_3[2] = param_2[2];
  FUN_0044e720(pfVar1,&local_40);
  fVar2 = *param_3;
  fVar3 = param_3[1];
  fVar4 = *param_3;
  *param_3 = local_38 * param_3[2] + local_40 * *param_3 + local_3c * param_3[1];
  param_3[1] = local_28 * param_3[2] + local_30 * fVar2 + local_2c * param_3[1];
  param_3[2] = local_18 * param_3[2] + local_20 * fVar4 + local_1c * fVar3;
  fVar2 = *(float *)(param_1 + 0x198);
  fVar3 = *(float *)(param_1 + 0x19c);
  *param_3 = *(float *)(param_1 + 0x194) + *param_3;
  param_3[1] = fVar2 + param_3[1];
  param_3[2] = fVar3 + param_3[2];
  fVar2 = param_2[6];
  fVar3 = *pfVar1;
  fVar4 = param_2[3];
  fVar5 = *(float *)(param_1 + 0xa8);
  fVar6 = *(float *)(param_1 + 0xa0);
  fVar7 = param_2[5];
  fVar8 = *(float *)(param_1 + 0xa4);
  fVar9 = param_2[4];
  fVar10 = param_2[4];
  fVar11 = *(float *)(param_1 + 0xa8);
  fVar12 = param_2[5];
  fVar13 = *pfVar1;
  fVar14 = param_2[6];
  fVar15 = *(float *)(param_1 + 0xa0);
  fVar16 = *(float *)(param_1 + 0xa4);
  fVar17 = param_2[3];
  fVar18 = param_2[6];
  fVar19 = *(float *)(param_1 + 0xa8);
  fVar20 = param_2[3];
  fVar21 = *pfVar1;
  fVar22 = param_2[4];
  fVar23 = *(float *)(param_1 + 0xa0);
  fVar24 = *(float *)(param_1 + 0xa4);
  fVar25 = param_2[5];
  param_4[2] = param_2[6] * *(float *)(param_1 + 0xa4) +
               ((param_2[5] * *(float *)(param_1 + 0xa8) + param_2[4] * *pfVar1) -
               *(float *)(param_1 + 0xa0) * param_2[3]);
  *param_4 = (fVar6 * fVar7 + fVar4 * fVar5 + fVar2 * fVar3) - fVar8 * fVar9;
  param_4[3] = ((fVar18 * fVar19 - fVar20 * fVar21) - fVar22 * fVar23) - fVar24 * fVar25;
  param_4[1] = fVar16 * fVar17 + fVar14 * fVar15 + (fVar10 * fVar11 - fVar12 * fVar13);
  return;
}


/* 00464340 size=35 */

int __thiscall FUN_00464340(void *this,float *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)((int)this + 8);
  fVar2 = *(float *)((int)this + 4);
  *param_1 = *(float *)this / param_2;
  param_1[1] = fVar2 / param_2;
  param_1[2] = fVar1 / param_2;
  return;
}


/* 00464490 size=61 */

void FUN_00464490(void)

{
  if (DAT_004ea77c != 0) {
    (**(code **)(DAT_004ea77c + 4))();
    *(undefined4 *)(DAT_004ea77c + 0x5c) = 0;
    DAT_004ea77c = 0;
  }
  if (DAT_004ea778 != (HMODULE)0x0) {
    FreeLibrary(DAT_004ea778);
    DAT_004ea778 = (HMODULE)0x0;
  }
  return;
}


/* 004644f0 size=97 */

int __thiscall FUN_004644f0(void *this,char *param_1,int param_2)

{
  int iVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  int unaff_EDI;
  
  iVar1 = 0;
  uVar2 = (ushort)param_2 >> 1;
  iVar4 = CONCAT22((short)((uint)this >> 0x10),uVar2);
  iVar5 = param_2 + iVar4 * -2;
  uVar3 = iVar4 + 0xffff;
  if (uVar2 != 0) {
    iVar4 = (uVar3 & 0xffff) + 1;
    do {
      unaff_EDI = CONCAT22((short)((uint)unaff_EDI >> 0x10),*(undefined2 *)param_1);
      param_1 = param_1 + 2;
      iVar1 = iVar1 + unaff_EDI;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    uVar3 = 0;
  }
  sVar6 = (short)iVar5;
  iVar4 = CONCAT22((short)(uVar3 >> 0x10),sVar6);
  if (sVar6 != 0) {
    iVar5 = (iVar5 + 0xffffU & 0xffff) + 1;
    do {
      iVar4 = CONCAT22((short)((uint)iVar4 >> 0x10),(short)*param_1);
      iVar1 = iVar1 + iVar4;
      param_1 = param_1 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  return iVar1;
}


/* 00464560 size=32 */

undefined4 __cdecl FUN_00464560(int param_1)

{
  if (((**(byte **)(param_1 + 0x54) & 0x3f) == 1) && ((*(byte **)(param_1 + 0x54))[1] == 3)) {
    return 1;
  }
  return 0;
}


/* 00464580 size=106 */

undefined4 * __fastcall FUN_00464580(undefined4 *param_1)

{
  FUN_00470b70(param_1);
  FUN_00470b70(param_1 + 3);
  FUN_00470b70(param_1 + 6);
  FUN_00470b70(param_1 + 9);
  param_1[0xd] = &PTR_LAB_004ccc44;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = &PTR_LAB_004ccc44;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = &PTR_LAB_004ccc14;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = &PTR_LAB_004ccc44;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  FUN_00424310(param_1 + 0x2b,0);
  param_1[0x1a] = 0;
  param_1[0x19] = 0;
  param_1[0x1c] = 0;
  return param_1;
}


/* 004645f0 size=263 */

void __fastcall FUN_004645f0(int param_1)

{
  int iVar1;
  undefined4 *this;
  undefined4 *puVar2;
  
  FUN_00467820(*(void **)(*(int *)(param_1 + 0x30) + 0x48),param_1 + 0x40);
  FUN_00467820(*(void **)(*(int *)(param_1 + 0x30) + 0x48),param_1 + 0x34);
  FUN_00467820(*(void **)(*(int *)(param_1 + 0x30) + 0x48),param_1 + 0x58);
  iVar1 = *(int *)(*(int *)(param_1 + 0x30) + 0x48);
  if (*(undefined4 **)(param_1 + 0x54) != (undefined4 *)0x0) {
    this = *(undefined4 **)(param_1 + 0x54);
    do {
      puVar2 = (undefined4 *)(this[1] & -(uint)(this[1] != *(uint *)(param_1 + 0x54)));
      FUN_00468260(this,0);
      FUN_00464700(iVar1 + 8,this);
      this = puVar2;
    } while (puVar2 != (undefined4 *)0x0);
  }
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  if (0 < DAT_004e98f0) {
    FUN_00436670((byte *)(s__333_Conn__p_closing___total_sen_004daf23 + 5),param_1);
  }
  *(undefined ***)(param_1 + 0x58) = &PTR_LAB_004ccc44;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined ***)(param_1 + 0x4c) = &PTR_LAB_004ccc14;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined ***)(param_1 + 0x40) = &PTR_LAB_004ccc44;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined ***)(param_1 + 0x34) = &PTR_LAB_004ccc44;
  return;
}


/* 00464700 size=25 */

void __cdecl FUN_00464700(int param_1,undefined4 *param_2)

{
  if ((param_2 != (undefined4 *)0x0) && (param_1 != 0)) {
    *param_2 = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 **)(param_1 + 0x18) = param_2;
  }
  return;
}


/* 00464720 size=68 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00464720(int param_1)

{
  if (((*(byte *)(param_1 + 0x70) & 1) == 0) && (_DAT_004d8298 < *(float *)(param_1 + 0x98))) {
    if (0 < DAT_004e98e0) {
      FUN_00436670((byte *)s_Ack_timeout____3f__004daf64,SUB84((double)*(float *)(param_1 + 0x98),0)
                  );
    }
    return 1;
  }
  return 0;
}


/* 00464770 size=242 */

undefined4 * __fastcall FUN_00464770(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  param_1[1] = &PTR_FUN_004ccd04;
  FUN_004b7b90(param_1 + 2,0x70,0x20);
  puVar1 = param_1 + 10;
  *puVar1 = &PTR_LAB_004cccd4;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xe] = 0;
  param_1[0xd] = 0;
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  puVar1 = param_1 + 0xf;
  *puVar1 = &PTR_LAB_004ccca4;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x13] = 0;
  param_1[0x12] = 0;
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  param_1[0x2e] = &PTR_LAB_004ccc44;
  param_1[0x2f] = 0;
  param_1[0x30] = 0;
  param_1[0x31] = &PTR_LAB_004ccc74;
  param_1[0x32] = 0;
  param_1[0x33] = 0;
  FUN_00470b70(param_1 + 0x38);
  param_1[0x40] = 0;
  param_1[0x35] = 0;
  param_1[0x3c] = 0;
  param_1[0x3d] = 0;
  param_1[0x3e] = 0;
  param_1[0x3f] = 0;
  *param_1 = 0;
  return param_1;
}


/* 00464870 size=178 */

void __fastcall FUN_00464870(void *param_1)

{
  FUN_004649a0(param_1);
  *(undefined ***)((int)param_1 + 0xc4) = &PTR_LAB_004ccc74;
  *(undefined4 *)((int)param_1 + 0xcc) = 0;
  *(undefined4 *)((int)param_1 + 200) = 0;
  *(undefined ***)((int)param_1 + 0xb8) = &PTR_LAB_004ccc44;
  *(undefined4 *)((int)param_1 + 0xc0) = 0;
  *(undefined4 *)((int)param_1 + 0xbc) = 0;
  *(undefined ***)((int)param_1 + 0x3c) = &PTR_LAB_004ccca4;
  if (*(int *)((int)param_1 + 0x40) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)param_1 + 0x40));
    *(undefined4 *)((int)param_1 + 0x40) = 0;
    *(undefined4 *)((int)param_1 + 0x48) = 0;
  }
  *(undefined4 *)((int)param_1 + 0x44) = 0;
  *(undefined ***)((int)param_1 + 0x28) = &PTR_LAB_004cccd4;
  if (*(int *)((int)param_1 + 0x2c) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)param_1 + 0x2c));
    *(undefined4 *)((int)param_1 + 0x2c) = 0;
    *(undefined4 *)((int)param_1 + 0x34) = 0;
  }
  *(undefined4 *)((int)param_1 + 0x30) = 0;
  *(undefined ***)((int)param_1 + 4) = &PTR_FUN_004ccd04;
  FUN_004b7c10((int)param_1 + 8);
  *(undefined ***)((int)param_1 + 4) = &PTR_LAB_004cb514;
  return;
}


/* 00464930 size=101 */

undefined4 __thiscall FUN_00464930(void *this,char *param_1)

{
  float10 fVar1;
  
  *(undefined4 *)((int)this + 0xd8) = 0;
  *(char *)((int)this + 0x50) = '\0';
  *(undefined4 *)((int)this + 0x10) = 0x100;
  *(undefined4 *)((int)this + 0xdc) = 0;
  *(undefined1 **)((int)this + 0xd0) = &DAT_004e4424;
  _strncpy((char *)((int)this + 0x50),param_1,100);
  fVar1 = FUN_004a0540();
  *(float *)((int)this + 0xec) = (float)fVar1;
  FUN_00467a80(this,(undefined4 *)0x0);
  *(undefined4 *)((int)this + 0x100) = 0;
  return 1;
}


/* 004649a0 size=48 */

void __fastcall FUN_004649a0(void *param_1)

{
  FUN_00464a00(param_1);
  *(undefined1 *)((int)param_1 + 0x50) = 0;
  *(undefined4 *)((int)param_1 + 0xb4) = 0;
  *(undefined4 *)((int)param_1 + 0xd8) = 0;
  FUN_00467820(param_1,(int)param_1 + 0xb8);
  FUN_00466da0(param_1);
  return;
}


/* 00464a00 size=40 */

void __fastcall FUN_00464a00(void *param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = *(int *)((int)param_1 + 0x44);
  do {
    if (iVar1 == 0) {
      return;
    }
    FUN_00465640(param_1,(undefined4 *)**(undefined4 **)((int)param_1 + 0x40));
    bVar2 = iVar1 != *(int *)((int)param_1 + 0x44);
    iVar1 = *(int *)((int)param_1 + 0x44);
  } while (bVar2);
  return;
}


/* 00464a30 size=52 */

undefined4 __thiscall FUN_00464a30(void *this,undefined4 *param_1)

{
  uint uVar1;
  
  *param_1 = 0;
  uVar1 = 0;
  if (*(int *)((int)this + 0x44) != 0) {
    do {
      (**(code **)(**(int **)(*(int *)((int)this + 0x40) + uVar1 * 4) + 0x14))(param_1);
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)((int)this + 0x44));
  }
  return 0;
}


/* 00464a70 size=39 */

undefined4 FUN_00464a70(undefined *param_1)

{
  undefined *puVar1;
  
  if (param_1 == (undefined *)0x0) {
    return 0;
  }
  do {
    puVar1 = *(undefined **)(param_1 + 0x98);
    FUN_00430df0(param_1);
    param_1 = puVar1;
  } while (puVar1 != (undefined *)0x0);
  return 0;
}


/* 00464aa0 size=99 */

undefined4 __thiscall FUN_00464aa0(void *this,int param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  
  uVar1 = 0;
  if (*(uint *)((int)this + 0x44) != 0) {
    piVar3 = *(int **)((int)this + 0x40);
    while ((int *)*piVar3 != *(int **)(param_1 + 4)) {
      uVar1 = uVar1 + 1;
      piVar3 = piVar3 + 1;
      if (*(uint *)((int)this + 0x44) <= uVar1) {
        return 0x49;
      }
    }
    if (uVar1 != 0xffffffff) {
      iVar2 = (**(code **)(**(int **)(param_1 + 4) + 0x18))(param_1);
      if (iVar2 == 0) {
        *(undefined4 *)((int)this + 0x100) = *(undefined4 *)(param_1 + 4);
        return 0;
      }
      return 1;
    }
  }
  return 0x49;
}


/* 00464b10 size=36 */

undefined4 __thiscall FUN_00464b10(void *this,undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(int **)((int)this + 0x100) == (int *)0x0) {
    return 0x49;
  }
  uVar1 = (**(code **)(**(int **)((int)this + 0x100) + 0x1c))(param_1,param_2);
  return uVar1;
}


/* 00464b40 size=42 */

undefined4 FUN_00464b40(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  if (param_1 == (undefined4 *)0x0) {
    return 0;
  }
  do {
    puVar1 = (undefined4 *)param_1[0x426];
    if (param_1 != (undefined4 *)0x0) {
      (**(code **)*param_1)(1);
    }
    param_1 = puVar1;
  } while (puVar1 != (undefined4 *)0x0);
  return 0;
}


/* 00464b70 size=42 */

undefined4 __thiscall FUN_00464b70(void *this,undefined1 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(int **)((int)this + 0x100) == (int *)0x0) {
    *param_1 = 0;
    return 0x49;
  }
  uVar1 = (**(code **)(**(int **)((int)this + 0x100) + 0x3c))(param_1,param_2);
  return uVar1;
}


/* 00464ba0 size=31 */

undefined4 __thiscall FUN_00464ba0(void *this,undefined4 param_1)

{
  undefined4 uVar1;
  
  if (*(int **)((int)this + 0x100) == (int *)0x0) {
    return 0x49;
  }
  uVar1 = (**(code **)(**(int **)((int)this + 0x100) + 0x38))(param_1);
  return uVar1;
}


/* 00464bc0 size=47 */

undefined4 __thiscall
FUN_00464bc0(void *this,undefined1 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (*(int **)((int)this + 0x100) == (int *)0x0) {
    *param_1 = 0;
    return 0x49;
  }
  uVar1 = (**(code **)(**(int **)((int)this + 0x100) + 0x50))(param_1,param_2,param_3);
  return uVar1;
}


/* 00465020 size=61 */

void __fastcall FUN_00465020(undefined4 *param_1)

{
  param_1[0x14] = &PTR_LAB_004cbb50;
  if (param_1[0x15] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[0x15]);
    param_1[0x15] = 0;
    param_1[0x17] = 0;
  }
  param_1[0x16] = 0;
  *param_1 = &PTR_LAB_004ccd18;
  return;
}


/* 004650b0 size=949 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004650b0(void *this,uint param_1,void *param_2)

{
  undefined4 uVar1;
  void *this_00;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint local_c;
  
  this_00 = param_2;
  *(undefined2 *)((int)param_2 + 0x38) = 1;
  *(undefined2 *)((int)param_2 + 0x34) = 1;
  **(undefined1 **)((int)param_2 + 0x54) = 0x41;
  FUN_004183a0(param_2,0);
  uVar4 = param_1;
  if (_DAT_004cb524 <= *(float *)(param_1 + 0xb4)) {
    FUN_004183a0(this_00,0);
  }
  else {
    *(short *)(param_1 + 0xb8) = *(short *)(param_1 + 0xb8) + 1;
    FUN_00424340((LARGE_INTEGER *)(param_1 + 0xac));
    param_2 = (void *)_rand();
    *(float *)(uVar4 + 0xb4) = (float)(int)param_2 * _DAT_004cc554 * _DAT_004ccd28;
    FUN_004183a0(this_00,1);
    FUN_004385b0(this_00,*(undefined2 *)(uVar4 + 0xb8));
  }
  if (*(int *)(uVar4 + 0x7c) == 0) {
    iVar2 = -1;
  }
  else {
    iVar2 = *(int *)(uVar4 + 0x7c) + -1;
  }
  FUN_00438f40(this_00,iVar2);
  uVar1 = *(undefined4 *)(uVar4 + 0x74);
  if (*(ushort *)((int)this_00 + 0x38) + 4 < (uint)*(ushort *)((int)this_00 + 0x36)) {
    if (*(uint *)((int)this_00 + 0x58) <= *(ushort *)((int)this_00 + 0x34) + 4) {
      do {
        param_2 = (void *)((uint)param_2 & 0xffffff00);
        FUN_00414b10((void *)((int)this_00 + 0x50),*(undefined1 **)((int)this_00 + 0x58),
                     (undefined1 *)&param_2,&DAT_004ecc58);
      } while (*(uint *)((int)this_00 + 0x58) <= *(ushort *)((int)this_00 + 0x34) + 4);
    }
    *(undefined4 *)((uint)*(ushort *)((int)this_00 + 0x38) + *(int *)((int)this_00 + 0x54)) = uVar1;
    *(short *)((int)this_00 + 0x38) = *(short *)((int)this_00 + 0x38) + 4;
    *(short *)((int)this_00 + 0x34) = *(short *)((int)this_00 + 0x34) + 4;
  }
  else {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    *(uint *)((int)this_00 + 0x40) = *(uint *)((int)this_00 + 0x40) | 4;
  }
  uVar3 = *(uint *)(uVar4 + 0x48);
  uVar5 = *(uint *)(uVar4 + 0x7c);
  uVar6 = 0;
  local_c = 0;
  if (uVar3 != 0) {
    do {
      uVar4 = -(uint)(*(uint *)(uVar3 + 4) != *(uint *)(param_1 + 0x48)) & *(uint *)(uVar3 + 4);
      if (uVar3 != 0) {
        if (uVar5 < *(uint *)(uVar3 + 0x18)) {
          do {
            if (7 < uVar6) break;
            if (*(ushort *)((int)this_00 + 0x38) + 4 < (uint)*(ushort *)((int)this_00 + 0x36)) {
              if (*(uint *)((int)this_00 + 0x58) <= *(ushort *)((int)this_00 + 0x34) + 4) {
                do {
                  param_2 = (void *)((uint)param_2 & 0xffffff00);
                  FUN_00414b10((void *)((int)this_00 + 0x50),*(undefined1 **)((int)this_00 + 0x58),
                               (undefined1 *)&param_2,&DAT_004ecc58);
                } while (*(uint *)((int)this_00 + 0x58) <= *(ushort *)((int)this_00 + 0x34) + 4);
              }
              *(uint *)((uint)*(ushort *)((int)this_00 + 0x38) + *(int *)((int)this_00 + 0x54)) =
                   uVar5;
              *(short *)((int)this_00 + 0x38) = *(short *)((int)this_00 + 0x38) + 4;
              *(short *)((int)this_00 + 0x34) = *(short *)((int)this_00 + 0x34) + 4;
            }
            else {
              FUN_004356e0();
              if (0 < DAT_004e4420) {
                FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                             s_CPacket__WriteType_004d5cf0);
              }
              *(uint *)((int)this_00 + 0x40) = *(uint *)((int)this_00 + 0x40) | 4;
            }
            netmgr_467b10(this,1,(byte *)s_NAK_sent_on_packet_frame__d_004db050,uVar5);
            uVar5 = uVar5 + 1;
            uVar6 = local_c + 1;
            local_c = uVar6;
          } while (uVar5 < *(uint *)(uVar3 + 0x18));
        }
        uVar5 = uVar5 + 1;
      }
      if (7 < uVar6) {
        *(undefined4 *)(param_1 + 0x94) = 0;
        return;
      }
      if (uVar4 == 0) goto code_r0x00465331;
      uVar3 = uVar4;
    } while( true );
  }
LAB_0046533e:
  if (uVar5 < *(uint *)(uVar4 + 0x80)) {
    do {
      if (*(ushort *)((int)this_00 + 0x38) + 4 < (uint)*(ushort *)((int)this_00 + 0x36)) {
        if (*(uint *)((int)this_00 + 0x58) <= *(ushort *)((int)this_00 + 0x34) + 4) {
          do {
            param_1 = param_1 & 0xffffff00;
            FUN_00414b10((void *)((int)this_00 + 0x50),*(undefined1 **)((int)this_00 + 0x58),
                         (undefined1 *)&param_1,&DAT_004ecc58);
          } while (*(uint *)((int)this_00 + 0x58) <= *(ushort *)((int)this_00 + 0x34) + 4);
          uVar6 = local_c;
        }
        *(uint *)((uint)*(ushort *)((int)this_00 + 0x38) + *(int *)((int)this_00 + 0x54)) = uVar5;
        *(short *)((int)this_00 + 0x38) = *(short *)((int)this_00 + 0x38) + 4;
        *(short *)((int)this_00 + 0x34) = *(short *)((int)this_00 + 0x34) + 4;
      }
      else {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
        }
        *(uint *)((int)this_00 + 0x40) = *(uint *)((int)this_00 + 0x40) | 4;
      }
      netmgr_467b10(this,1,(byte *)s_NAK_sent_on_packet_frame__d_004db050,uVar5);
      uVar6 = uVar6 + 1;
    } while ((uVar6 < 8) && (uVar5 = uVar5 + 1, local_c = uVar6, uVar5 < *(uint *)(uVar4 + 0x80)));
  }
  *(undefined4 *)(uVar4 + 0x94) = 0;
  return;
code_r0x00465331:
  if (7 < uVar6) {
    *(undefined4 *)(param_1 + 0x94) = 0;
    return;
  }
  uVar4 = param_1;
  goto LAB_0046533e;
}


/* 00465640 size=315 */

void __thiscall FUN_00465640(void *this,undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint uVar6;
  
  uVar6 = 0xffffffff;
  uVar2 = 0;
  if (*(uint *)((int)this + 0x44) != 0) {
    piVar5 = *(int **)((int)this + 0x40);
    do {
      if ((undefined4 *)*piVar5 == param_1) {
        uVar6 = uVar2;
        break;
      }
      uVar2 = uVar2 + 1;
      piVar5 = piVar5 + 1;
    } while (uVar2 < *(uint *)((int)this + 0x44));
  }
  if (param_1 == *(undefined4 **)((int)this + 0x100)) {
    *(undefined4 *)((int)this + 0x100) = 0;
  }
  if (param_1 != (undefined4 *)0x0) {
    (**(code **)*param_1)(1);
  }
  if ((uint)(*(int *)((int)this + 0x4c) * 2) <= *(uint *)((int)this + 0x48)) {
    iVar1 = *(int *)((int)this + 0x44) + -1 + *(int *)((int)this + 0x4c);
    iVar3 = FUN_00456f10(&DAT_004ecc58,0,iVar1);
    if ((iVar3 != 0) || (iVar1 == 0)) {
      uVar2 = 0;
      if (uVar6 != 0) {
        do {
          uVar2 = uVar2 + 1;
          *(undefined4 *)(iVar3 + -4 + uVar2 * 4) =
               *(undefined4 *)(*(int *)((int)this + 0x40) + -4 + uVar2 * 4);
        } while (uVar2 < uVar6);
      }
      if (uVar6 < *(int *)((int)this + 0x44) - 1U) {
        puVar4 = (undefined4 *)(iVar3 + uVar6 * 4);
        do {
          uVar6 = uVar6 + 1;
          *puVar4 = *(undefined4 *)((int)puVar4 + *(int *)((int)this + 0x40) + (4 - iVar3));
          puVar4 = puVar4 + 1;
        } while (uVar6 < *(int *)((int)this + 0x44) - 1U);
      }
      iVar1 = *(int *)((int)this + 0x40);
      if (iVar1 != 0) {
        if (iVar1 != 0) {
          (**(code **)(DAT_004ecc58 + 8))(iVar1);
        }
        *(undefined4 *)((int)this + 0x40) = 0;
      }
      *(undefined4 *)((int)this + 0x48) = 0;
      *(int *)((int)this + 0x40) = iVar3;
      *(undefined4 *)((int)this + 0x48) = *(undefined4 *)((int)this + 0x4c);
      *(int *)((int)this + 0x44) = *(int *)((int)this + 0x44) + -1;
      return;
    }
  }
  *(int *)((int)this + 0x48) = *(int *)((int)this + 0x48) + 1;
  if (uVar6 < *(int *)((int)this + 0x44) - 1U) {
    do {
      uVar6 = uVar6 + 1;
      *(undefined4 *)(*(int *)((int)this + 0x40) + -4 + uVar6 * 4) =
           *(undefined4 *)(*(int *)((int)this + 0x40) + uVar6 * 4);
    } while (uVar6 < *(int *)((int)this + 0x44) - 1U);
  }
  *(int *)((int)this + 0x44) = *(int *)((int)this + 0x44) + -1;
  return;
}


/* 004657c0 size=117 */

int __thiscall FUN_004657c0(void *this,int *param_1,float *param_2,byte param_3)

{
  byte bVar1;
  int iVar2;
  
  if (param_2 == (float *)0x0) {
    return 0;
  }
  if ((((param_3 & 0x80) == 0) && (((uint)param_2[0x1c] & 1) == 0)) &&
     (((uint)DAT_004d82a8 < (uint)param_2[0x11] || ((uint)DAT_004d82a8 < (uint)param_2[0xe])))) {
    return 1;
  }
  param_2[0x22] = 0.0;
  bVar1 = *(byte *)param_1[0x15];
  *(byte *)param_1[0x15] = bVar1 & 0x3f | param_3 & 0xc0;
  iVar2 = FUN_00465a90(this,param_1,param_2,bVar1);
  return iVar2;
}


/* 00465840 size=7 */

void __fastcall FUN_00465840(uint *param_1)

{
  *param_1 = *param_1 | 1;
  return;
}


/* 00465850 size=7 */

void __fastcall FUN_00465850(uint *param_1)

{
  *param_1 = *param_1 & 0xfffffffe;
  return;
}


/* 00465860 size=471 */

/* FUN_00465860: lifted from original x86 -> lt_lifted.c */


/* 00465a40 size=70 */

void __thiscall FUN_00465a40(void *this,int *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_1 != (int *)0x0) {
    uVar3 = param_1[0xf];
    while (uVar3 != 0) {
      uVar1 = param_1[0xf];
      uVar2 = *(uint *)(uVar3 + 4);
      FUN_00466160(this,*(int *)(uVar3 + 8),*(uint *)(uVar3 + 0x10),
                   *(int *)(uVar3 + 0xc) - *(uint *)(uVar3 + 0x10),param_1);
      uVar3 = uVar2 & -(uint)(uVar2 != uVar1);
    }
  }
  return;
}


/* 00465a90 size=385 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00465a90: lifted from original x86 -> lt_lifted.c */


/* 00465c20 size=215 */

undefined4 * __fastcall FUN_00465c20(undefined4 *param_1)

{
  undefined4 *this;
  
  this = param_1 + 0x14;
  *param_1 = &PTR_LAB_004ccd18;
  param_1[1] = 0;
  param_1[2] = &PTR_LAB_004ccd3c;
  *this = &PTR_LAB_004cbb50;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  FUN_0040c870(this,0,&DAT_004ecc58);
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x18] = 0;
  param_1[0x17] = 0;
  if (param_1[0x15] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[0x15]);
    param_1[0x15] = 0;
    param_1[0x17] = 0;
  }
  param_1[0x16] = 0;
  *param_1 = &PTR_FUN_004ccd2c;
  *(undefined2 *)(param_1 + 0xd) = 1;
  *(undefined2 *)((int)param_1 + 0x36) = 0x44c;
  *(undefined2 *)(param_1 + 0xe) = 1;
  *(undefined2 *)((int)param_1 + 0x3a) = 1;
  param_1[0x10] = 0;
  param_1[4] = param_1;
  if ((uint)param_1[0x16] < 0x44c) {
    FUN_0040c870(this,0,&DAT_004ecc58);
    FUN_0040c870(this,0,&DAT_004ecc58);
    param_1[0x15] = 0;
    param_1[0x16] = 0;
    param_1[0x18] = 0x44c;
    param_1[0x17] = 0;
    FUN_0040c870(this,0x44c,&DAT_004ecc58);
    return param_1;
  }
  param_1[0x18] = 0x44c;
  return param_1;
}


/* 00465d00 size=90 */

undefined4 * __thiscall FUN_00465d00(void *this,byte param_1)

{
  *(undefined ***)((int)this + 0x50) = &PTR_LAB_004cbb50;
  if (*(int *)((int)this + 0x54) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x54));
    *(undefined4 *)((int)this + 0x54) = 0;
    *(undefined4 *)((int)this + 0x5c) = 0;
  }
  *(undefined4 *)((int)this + 0x58) = 0;
  *(undefined ***)this = &PTR_LAB_004ccd18;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00465d60 size=55 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00465d60(int param_1,uint param_2)

{
  if (param_1 != 0) {
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + _DAT_004cba94;
    *(float *)(param_1 + 0x18) = (float)param_2 + *(float *)(param_1 + 0x18);
  }
  return;
}


/* 00465da0 size=81 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00465da0(void *this,float *param_1,uint param_2)

{
  if (param_1 != (float *)0x0) {
    param_1[3] = param_1[3] + _DAT_004cba94;
    *param_1 = (float)param_2 + *param_1;
    if (((uint)param_1[0x1c] & 1) == 0) {
      *(float *)((int)this + 0xe0) = (float)param_2 + *(float *)((int)this + 0xe0);
      return;
    }
  }
  return;
}


/* 00465e00 size=29 */

void __thiscall FUN_00465e00(void *this,int param_1)

{
  if (param_1 != 0) {
    FUN_00467480(this,param_1 + 0x40,*(uint *)(param_1 + 0x7c));
    *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 0x7c) + 1;
  }
  return;
}


/* 00466160 size=364 */

undefined4 __thiscall FUN_00466160(void *this,int param_1,uint param_2,uint param_3,int *param_4)

{
  int *piVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 unaff_EDI;
  undefined4 local_10;
  
  piVar1 = param_4;
  if (param_2 < 0x44d) {
    uVar2 = (**(code **)(*(int *)param_4[0xc] + 0x60))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  uVar2 = *(undefined4 *)(param_1 + -4 + param_2);
  uVar5 = param_2 - 4;
  netmgr_467b80(this,(int)param_4,2,(byte *)s_Fragmenting_packet__d_004db108,uVar2);
  FUN_0046b170(&param_4,0x44c,0x44c);
  *(undefined1 *)param_4[0x15] = 1;
  local_10 = 1;
  param_3 = 0;
  uVar7 = 0;
  do {
    uVar3 = (uVar5 >> 2) + 1 + uVar7;
    uVar6 = uVar5;
    if (uVar3 < uVar5) {
      uVar6 = uVar3;
    }
    if (uVar6 == uVar7) {
      netmgr_467b10(this,0,(byte *)s_Unable_to_complete_fragment_uplo_004db0e4,unaff_EDI);
      break;
    }
    *(undefined2 *)(param_4 + 0xe) = 1;
    *(undefined2 *)(param_4 + 0xd) = 1;
    FUN_004183a0(param_4,4);
    FUN_004183a0(param_4,(byte)param_3 | 0x30);
    FUN_00438f40(param_4,uVar2);
    FUN_0046b480(param_4,(undefined4 *)(uVar7 + param_1),uVar6 - uVar7);
    iVar4 = (**(code **)(*(int *)piVar1[0xc] + 0x60))
                      (param_4[0x15],(uint)*(ushort *)(param_4 + 0xd),
                       param_4[0x16] - (uint)*(ushort *)(param_4 + 0xd),piVar1);
    if (iVar4 == 0) {
      local_10 = 0;
      break;
    }
    param_3 = param_3 + 1;
    uVar7 = uVar6;
  } while (param_3 < 4);
  if (param_4 != (int *)0x0) {
    (**(code **)(*param_4 + 8))();
  }
  return local_10;
}


/* 004662d0 size=1026 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004662d0(void *this,int *param_1,int *param_2)

{
  ushort uVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int *piVar7;
  int *unaff_ESI;
  undefined4 *puVar8;
  int *piVar9;
  int *unaff_EDI;
  undefined4 *puVar10;
  char *pcVar11;
  int *local_18;
  int *local_14;
  byte *local_10;
  int *local_c;
  uint local_8;
  uint local_4;
  
  piVar2 = param_2;
  piVar7 = param_1;
  local_18 = (int *)0x0;
  local_14 = (int *)0x0;
  local_8 = 0;
  local_4 = 0;
  local_c = (int *)0x0;
  piVar9 = (int *)0x0;
  local_10 = this;
  if ((*(byte *)param_1[0x15] & 0x80) != 0) {
    local_8 = (uint)*(ushort *)(param_1 + 0xd);
    local_4 = (uint)*(ushort *)(param_1 + 0xe);
    local_c = param_1;
    FUN_00438f40(param_1,param_2[0x1d]);
    piVar9 = piVar7;
  }
  if ((piVar7[0x10] & 6U) != 0) {
    if ((piVar7[0x10] & 2U) == 0) {
      pcVar11 = s_____Packet_write_overflow__disco_004db188;
    }
    else {
      pcVar11 = s_____Packet_read_overflow__discon_004db1b8;
    }
    FUN_00436670((byte *)pcVar11,unaff_EDI);
    piVar2[0x1c] = piVar2[0x1c] | 4;
    piVar7[0x10] = piVar7[0x10] & 0xfffffff9;
    if (piVar9 != (int *)0x0) {
      *(undefined2 *)(piVar9 + 0xd) = (undefined2)local_8;
      *(undefined2 *)(piVar9 + 0xe) = (undefined2)local_4;
    }
    if (local_18 != (int *)0x0) {
      (**(code **)(*local_18 + 8))();
    }
    return 0;
  }
  piVar3 = (int *)0x0;
  if ((*(byte *)piVar7[0x15] & 0x80) != 0) {
    if ((*(byte *)(piVar2 + 0x1c) & 1) == 0) {
      param_1 = FUN_00467760(this,(uint)*(ushort *)(piVar7 + 0xd));
      uVar1 = *(ushort *)(piVar7 + 0xd);
      puVar8 = (undefined4 *)piVar7[0x15];
      puVar10 = (undefined4 *)param_1[2];
      for (uVar6 = (uint)(uVar1 >> 2); uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar10 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar10 = puVar10 + 1;
      }
      for (uVar6 = uVar1 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined1 *)puVar10 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar10 = (undefined4 *)((int)puVar10 + 1);
      }
      param_1[4] = (uint)*(ushort *)(piVar7 + 0xd);
      param_1[6] = piVar2[0x1d];
      if ((int *)piVar2[0xf] == (int *)0x0) {
        FUN_004682f0(piVar2 + 0xd,param_1);
      }
      else {
        FUN_004682c0(piVar2 + 0xd,*(int *)piVar2[0xf],param_1);
      }
      piVar3 = param_1;
      piVar9 = local_c;
      this = local_10;
    }
    piVar2[0x1d] = piVar2[0x1d] + 1;
  }
  if (((*(byte *)(piVar7 + 0x10) & 8) != 0) && (piVar3 != (int *)0x0)) {
    piVar3[7] = 1;
    if (piVar9 != (int *)0x0) {
      *(undefined2 *)(piVar9 + 0xd) = (undefined2)local_8;
      *(undefined2 *)(piVar9 + 0xe) = (undefined2)local_4;
    }
    if (local_18 != (int *)0x0) {
      (**(code **)(*local_18 + 8))();
    }
    return 1;
  }
  netmgr_467b80(this,(int)piVar2,5,(byte *)s_Sent_packet__d_to_connection__p___004db148,piVar2[0x1d]
               );
  if (((*(byte *)(piVar7 + 0x10) & 0x10) != 0) &&
     (piVar3 = (int *)piVar2[0xf], piVar3 != (int *)0x0)) {
    while( true ) {
      param_1 = (int *)(-(uint)(piVar3[1] != piVar2[0xf]) & piVar3[1]);
      if (piVar3[7] != 0) {
        iVar4 = ((uint)*(ushort *)((int)piVar7 + 0x36) - (uint)*(ushort *)(piVar7 + 0xe)) + -7;
        if (iVar4 < 0) {
          iVar4 = 0;
        }
        uVar6 = piVar3[4];
        if ((int)(uVar6 + 4) < iVar4) {
          iVar4 = FUN_00464560((int)piVar7);
          if (iVar4 == 0) {
            FUN_00467890((int *)&local_18);
            FUN_00467990(local_18,(int)piVar7);
            piVar7 = local_18;
          }
          FUN_004679b0(piVar7,(undefined4 *)piVar3[2],piVar3[4]);
        }
        else {
          FUN_00466160(this,piVar3[2],uVar6,piVar3[3] - uVar6,piVar2);
        }
        piVar3[7] = 0;
      }
      if (param_1 == (int *)0x0) break;
      piVar3 = param_1;
    }
    piVar9 = local_c;
  }
  if ((_DAT_004daf18 < (float)piVar2[0x25]) && ((*(byte *)this & 1) == 0)) {
    if ((*(byte *)(piVar2 + 0x1c) & 1) != 0) goto LAB_0046667a;
    iVar4 = ((uint)*(ushort *)((int)piVar7 + 0x36) - (uint)*(ushort *)(piVar7 + 0xe)) + -7;
    if ((-1 < iVar4) && (0x2b < iVar4)) {
      netmgr_467b80(this,(int)piVar2,2,(byte *)s_Piggybacking_ack_local___d__remo_004db120,
                    piVar2[0x1d]);
      local_14 = FUN_0046b170(&param_1,0x44c,0x44c);
      local_14 = (int *)*local_14;
      if (local_14 != (int *)0x0) {
        (**(code **)(*local_14 + 4))();
      }
      if (param_1 != (int *)0x0) {
        (**(code **)(*param_1 + 8))();
      }
      FUN_004650b0(this,(uint)piVar2,local_14);
      iVar4 = FUN_00464560((int)piVar7);
      if (iVar4 == 0) {
        FUN_00467890((int *)&local_18);
        FUN_00467990(local_18,(int)piVar7);
        FUN_00467990(local_18,(int)local_14);
        piVar7 = local_18;
      }
      else {
        FUN_00467990(piVar7,(int)local_14);
      }
    }
  }
  if (((*(byte *)(piVar2 + 0x1c) & 1) == 0) && ((*(byte *)piVar7[0x15] & 0x80) != 0)) {
    uVar5 = FUN_00466160(this,piVar7[0x15],(uint)*(ushort *)(piVar7 + 0xd),
                         piVar7[0x16] - (uint)*(ushort *)(piVar7 + 0xd),piVar2);
    if (piVar9 != (int *)0x0) {
      *(undefined2 *)(piVar9 + 0xd) = (undefined2)local_8;
      *(undefined2 *)(piVar9 + 0xe) = (undefined2)local_4;
    }
    if (local_14 != (int *)0x0) {
      (**(code **)(*local_14 + 8))();
    }
    if (local_18 == (int *)0x0) {
      return uVar5;
    }
    (**(code **)(*local_18 + 8))();
    return uVar5;
  }
LAB_0046667a:
  uVar5 = (**(code **)(*(int *)piVar2[0xc] + 0x60))
                    (piVar7[0x15],(uint)*(ushort *)(piVar7 + 0xd),
                     piVar7[0x16] - (uint)*(ushort *)(piVar7 + 0xd),piVar2);
  if (piVar9 != (int *)0x0) {
    *(undefined2 *)(piVar9 + 0xd) = (*(uint16_t*)((char*)&local_18+0));
    *(undefined2 *)(piVar9 + 0xe) = (*(uint16_t*)((char*)&local_14+0));
  }
  if (unaff_ESI != (int *)0x0) {
    (**(code **)(*unaff_ESI + 8))();
  }
  if (unaff_EDI != (int *)0x0) {
    (**(code **)(*unaff_EDI + 8))();
  }
  return uVar5;
}


/* 00466ab0 size=62 */

uint __thiscall FUN_00466ab0(void *this,int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)((int)this + 0xcc);
  do {
    uVar1 = uVar2;
    if (uVar1 == 0) {
      return 0;
    }
    uVar2 = *(uint *)(uVar1 + 4) & -(uint)(*(uint *)(uVar1 + 4) != *(uint *)((int)this + 0xcc));
  } while ((*(int *)(uVar1 + 0x18) != param_1) || (*(int *)(uVar1 + 0x1c) != param_2));
  return uVar1;
}


/* 00466af0 size=180 */

undefined4 FUN_00466af0(int param_1,int *param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined1 uVar4;
  int *piVar5;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined2 uVar6;
  
  iVar2 = param_3;
  piVar3 = param_2;
  piVar1 = (int *)(param_3 + 8 + ((uint)param_2 & 0xff) * 4);
  if (*(int *)(param_3 + 8 + ((uint)param_2 & 0xff) * 4) != 0) {
    return 0;
  }
  piVar5 = FUN_0046b170(&param_2,0x44c,0x44c);
  uVar6 = extraout_var;
  if ((int *)*piVar1 != (int *)0x0) {
    (**(code **)(*(int *)*piVar1 + 8))();
    uVar6 = extraout_var_00;
  }
  piVar5 = (int *)*piVar5;
  *piVar1 = (int)piVar5;
  if (piVar5 != (int *)0x0) {
    (**(code **)(*piVar5 + 4))();
    uVar6 = extraout_var_01;
  }
  if (param_2 != (int *)0x0) {
    (**(code **)(*param_2 + 8))();
    uVar6 = extraout_var_02;
  }
  if ((char)piVar3 == '\0') {
    iVar2 = *(int *)(iVar2 + 8);
    uVar4 = FUN_004680f0(param_1);
    **(undefined1 **)(iVar2 + 0x54) = uVar4;
    uVar6 = extraout_var_03;
  }
  iVar2 = *piVar1;
  *(undefined2 *)(iVar2 + 0x38) = 1;
  *(undefined2 *)(iVar2 + 0x34) = 1;
  FUN_0046b480((void *)*piVar1,
               (undefined4 *)(*(int *)(param_1 + 0x54) + (uint)*(ushort *)(param_1 + 0x38)),
               CONCAT22(uVar6,*(short *)(param_1 + 0x34) - *(ushort *)(param_1 + 0x38)));
  return 1;
}


/* 00466bb0 size=36 */

undefined4 FUN_00466bb0(int param_1)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = 0;
  piVar2 = (int *)(param_1 + 8);
  do {
    if (*piVar2 == 0) {
      return 0;
    }
    uVar1 = uVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (uVar1 < 4);
  return 1;
}


/* 00466be0 size=335 */

int * __fastcall FUN_00466be0(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  
  uVar5 = 0;
  uVar1 = *(uint *)(param_1 + 0xcc);
  uVar2 = uVar1;
  if (uVar1 != 0) {
    do {
      uVar2 = *(uint *)(uVar2 + 4) & -(uint)(*(uint *)(uVar2 + 4) != uVar1);
      uVar5 = uVar5 + 1;
    } while (uVar2 != 0);
    if (5 < uVar5) {
      piVar4 = (int *)**(int **)(param_1 + 0xcc);
      *(int *)(*piVar4 + 4) = piVar4[1];
      *(int *)piVar4[1] = *piVar4;
      if (piVar4 == *(int **)(param_1 + 0xcc)) {
        *(int *)(param_1 + 0xcc) = (*(int **)(param_1 + 0xcc))[1];
      }
      iVar3 = *(int *)(param_1 + 200) + -1;
      *(int *)(param_1 + 200) = iVar3;
      if (iVar3 == 0) {
        *(undefined4 *)(param_1 + 0xcc) = 0;
      }
      piVar6 = piVar4 + 2;
      iVar3 = 4;
      do {
        if ((int *)*piVar6 != (int *)0x0) {
          (**(code **)(*(int *)*piVar6 + 8))();
        }
        *piVar6 = 0;
        piVar6 = piVar6 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      piVar4[6] = 0;
      piVar4[7] = 0;
      goto LAB_00466cd1;
    }
  }
  piVar4 = (int *)FUN_00430de0(0x20);
  if (piVar4 == (int *)0x0) {
    piVar4 = (int *)0x0;
  }
  else {
    piVar6 = piVar4 + 2;
    iVar3 = 4;
    *piVar6 = 0;
    piVar4[3] = 0;
    piVar4[4] = 0;
    piVar4[5] = 0;
    do {
      if ((int *)*piVar6 != (int *)0x0) {
        (**(code **)(*(int *)*piVar6 + 8))();
      }
      *piVar6 = 0;
      piVar6 = piVar6 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    piVar4[6] = 0;
    piVar4[7] = 0;
  }
LAB_00466cd1:
  piVar6 = *(int **)(param_1 + 0xcc);
  if (piVar6 == (int *)0x0) {
    piVar4[1] = (int)piVar4;
    *piVar4 = (int)piVar4;
    *(int **)(param_1 + 0xcc) = piVar4;
    *(int *)(param_1 + 200) = *(int *)(param_1 + 200) + 1;
  }
  else {
    *(int **)(*piVar6 + 4) = piVar4;
    *piVar4 = *piVar6;
    piVar4[1] = (int)piVar6;
    *piVar6 = (int)piVar4;
    *(int *)(param_1 + 200) = *(int *)(param_1 + 200) + 1;
    if (piVar4[1] == *(int *)(param_1 + 0xcc)) {
      *(int **)(param_1 + 0xcc) = piVar4;
      return piVar4;
    }
  }
  return piVar4;
}


/* 00466d30 size=111 */

void __thiscall FUN_00466d30(void *this,int *param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  if (param_1 != (int *)0x0) {
    *(int *)(*param_1 + 4) = param_1[1];
    *(int *)param_1[1] = *param_1;
    if (param_1 == *(int **)((int)this + 0xcc)) {
      *(int *)((int)this + 0xcc) = (*(int **)((int)this + 0xcc))[1];
    }
    iVar2 = *(int *)((int)this + 200) + -1;
    *(int *)((int)this + 200) = iVar2;
    if (iVar2 == 0) {
      *(undefined4 *)((int)this + 0xcc) = 0;
    }
    piVar3 = param_1 + 6;
    iVar2 = 4;
    do {
      piVar1 = piVar3 + -1;
      piVar3 = piVar3 + -1;
      if ((int *)*piVar1 != (int *)0x0) {
        (**(code **)(*(int *)*piVar1 + 8))();
      }
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    FUN_00430df0((undefined *)param_1);
  }
  return;
}


/* 00466da0 size=33 */

void __fastcall FUN_00466da0(void *param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)((int)param_1 + 0xcc);
  while (piVar1 != (int *)0x0) {
    FUN_00466d30(param_1,piVar1);
    piVar1 = *(int **)((int)param_1 + 0xcc);
  }
  return;
}


/* 00466dd0 size=81 */

void __thiscall FUN_00466dd0(void *this,int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = *(int **)((int)this + 0xcc);
  while (piVar2 = piVar3, piVar2 != (int *)0x0) {
    piVar3 = (int *)(piVar2[1] & -(uint)(piVar2[1] != *(uint *)((int)this + 0xcc)));
    iVar1 = piVar2[7];
    if ((iVar1 != 0) && ((iVar1 == param_1 || ((uint)piVar2[6] < *(uint *)(iVar1 + 0x7c))))) {
      FUN_00466d30(this,piVar2);
    }
  }
  return;
}


/* 00466e30 size=1600 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00466e30: lifted from original x86 -> lt_lifted.c */


/* 00467470 size=5 */

undefined4 FUN_00467470(void)

{
  return 0;
}


/* 00467480 size=116 */

void __thiscall FUN_00467480(void *this,int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  
  piVar3 = *(int **)(param_1 + 8);
  while( true ) {
    if (piVar3 == (int *)0x0) {
      return;
    }
    uVar1 = piVar3[1];
    uVar2 = *(uint *)(param_1 + 8);
    if (param_2 < (uint)piVar3[6]) break;
    *(int *)(*piVar3 + 4) = piVar3[1];
    *(int *)piVar3[1] = *piVar3;
    if (piVar3 == *(int **)(param_1 + 8)) {
      *(int *)(param_1 + 8) = (*(int **)(param_1 + 8))[1];
    }
    iVar4 = *(int *)(param_1 + 4) + -1;
    *(int *)(param_1 + 4) = iVar4;
    if (iVar4 == 0) {
      *(undefined4 *)(param_1 + 8) = 0;
    }
    FUN_00467660(this,piVar3);
    piVar3 = (int *)(-(uint)(uVar1 != uVar2) & uVar1);
  }
  return;
}


/* 00467500 size=116 */

void __thiscall FUN_00467500(void *this,int param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_1 + 8);
  while (piVar1 = piVar3, piVar1 != (int *)0x0) {
    piVar3 = (int *)(-(uint)(piVar1[1] != *(uint *)(param_1 + 8)) & piVar1[1]);
    if (param_2 < (uint)piVar1[6]) {
      *(int *)(*piVar1 + 4) = piVar1[1];
      *(int *)piVar1[1] = *piVar1;
      if (piVar1 == *(int **)(param_1 + 8)) {
        *(int *)(param_1 + 8) = (*(int **)(param_1 + 8))[1];
      }
      iVar2 = *(int *)(param_1 + 4) + -1;
      *(int *)(param_1 + 4) = iVar2;
      if (iVar2 == 0) {
        *(undefined4 *)(param_1 + 8) = 0;
      }
      FUN_00467660(this,piVar1);
    }
  }
  return;
}


/* 00467580 size=219 */

undefined4 __thiscall FUN_00467580(void *this,int param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined4 unaff_EDI;
  
  piVar1 = *(int **)(param_1 + 8);
  iVar4 = 0;
  piVar3 = piVar1;
  while (piVar2 = piVar3, piVar2 != (int *)0x0) {
    if (DAT_004d82c4 <= iVar4) goto LAB_004675c8;
    iVar4 = iVar4 + 1;
    piVar3 = (int *)((uint)piVar2[1] & -(uint)((int *)piVar2[1] != piVar1));
    if ((uint)param_2[6] < (uint)piVar2[6]) {
      *(int **)(*piVar2 + 4) = param_2;
      *param_2 = *piVar2;
      param_2[1] = (int)piVar2;
      *piVar2 = (int)param_2;
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
      if (param_2[1] == *(int *)(param_1 + 8)) {
        *(int **)(param_1 + 8) = param_2;
        return 1;
      }
      return 1;
    }
  }
  if (iVar4 < DAT_004d82c4) {
    if (piVar1 == (int *)0x0) {
      param_2[1] = (int)param_2;
      *param_2 = (int)param_2;
      *(int **)(param_1 + 8) = param_2;
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
      return 1;
    }
    iVar4 = *piVar1;
    **(undefined4 **)(iVar4 + 4) = param_2;
    param_2[1] = *(int *)(iVar4 + 4);
    *param_2 = iVar4;
    *(int **)(iVar4 + 4) = param_2;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
    return 1;
  }
LAB_004675c8:
  netmgr_467b10(this,1,(byte *)s_Dropped_guaranteed_packet_due_to_004db4dc,unaff_EDI);
  return 0;
}


/* 00467660 size=192 */

void __thiscall FUN_00467660(void *this,int *param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  param_1[4] = 0;
  piVar1 = *(int **)((int)this + 0xc0);
  if (piVar1 != (int *)0x0) {
    piVar3 = piVar1;
    do {
      piVar4 = (int *)((uint)piVar3[1] & -(uint)((int *)piVar3[1] != piVar1));
      if (piVar3[3] <= param_1[3]) {
        if (piVar4 != (int *)0x0) {
          *(int **)(*piVar3 + 4) = param_1;
          *param_1 = *piVar3;
          param_1[1] = (int)piVar3;
          *piVar3 = (int)param_1;
          *(int *)((int)this + 0xbc) = *(int *)((int)this + 0xbc) + 1;
          if (param_1[1] == *(int *)((int)this + 0xc0)) {
            *(int **)((int)this + 0xc0) = param_1;
            return;
          }
          return;
        }
        break;
      }
      piVar3 = piVar4;
    } while (piVar4 != (int *)0x0);
  }
  if (*(int **)((int)this + 0xc0) == (int *)0x0) {
    param_1[1] = (int)param_1;
    *param_1 = (int)param_1;
    *(int **)((int)this + 0xc0) = param_1;
    *(int *)((int)this + 0xbc) = *(int *)((int)this + 0xbc) + 1;
    return;
  }
  iVar2 = **(int **)((int)this + 0xc0);
  **(undefined4 **)(iVar2 + 4) = param_1;
  param_1[1] = *(int *)(iVar2 + 4);
  *param_1 = iVar2;
  *(int **)(iVar2 + 4) = param_1;
  *(int *)((int)this + 0xbc) = *(int *)((int)this + 0xbc) + 1;
  return;
}


/* 00467720 size=54 */

uint FUN_00467720(int param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(param_1 + 8);
  while( true ) {
    if (uVar2 == 0) {
      return 0;
    }
    puVar1 = (uint *)(uVar2 + 0x18);
    if (*puVar1 == param_2) break;
    uVar2 = *(uint *)(uVar2 + 4) & -(uint)(*(uint *)(uVar2 + 4) != *(uint *)(param_1 + 8));
    if (param_2 < *puVar1) {
      return 0;
    }
  }
  return uVar2;
}


/* 00467760 size=179 */

int * __thiscall FUN_00467760(void *this,int param_1)

{
  int *piVar1;
  int iVar2;
  size_t sVar3;
  int *piVar4;
  
  sVar3 = param_1 + 2;
  piVar4 = *(int **)((int)this + 0xc0);
  do {
    piVar1 = piVar4;
    if (piVar1 == (int *)0x0) {
      piVar1 = (int *)FUN_00430de0(0x20);
      piVar4 = piVar1;
      for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar4 = 0;
        piVar4 = piVar4 + 1;
      }
      iVar2 = FUN_00430de0(sVar3);
      piVar1[2] = iVar2;
      piVar1[3] = sVar3;
      *(size_t *)((int)this + 0xd8) = *(int *)((int)this + 0xd8) + sVar3;
      return piVar1;
    }
    piVar4 = (int *)((uint)piVar1[1] & -(uint)((int *)piVar1[1] != *(int **)((int)this + 0xc0)));
  } while (piVar1[3] < (int)sVar3);
  *(int *)(*piVar1 + 4) = piVar1[1];
  *(int *)piVar1[1] = *piVar1;
  if (piVar1 == *(int **)((int)this + 0xc0)) {
    *(int *)((int)this + 0xc0) = (*(int **)((int)this + 0xc0))[1];
  }
  iVar2 = *(int *)((int)this + 0xbc) + -1;
  *(int *)((int)this + 0xbc) = iVar2;
  if (iVar2 == 0) {
    *(undefined4 *)((int)this + 0xc0) = 0;
  }
  piVar1[5] = 0;
  piVar1[7] = 0;
  return piVar1;
}


/* 00467820 size=110 */

void __thiscall FUN_00467820(void *this,int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = *(undefined **)(param_1 + 8);
  if (puVar1 == (undefined *)0x0) {
    *(undefined4 *)(param_1 + 8) = 0;
    *(undefined4 *)(param_1 + 4) = 0;
    return;
  }
  do {
    puVar2 = (undefined *)
             (*(uint *)(puVar1 + 4) & -(uint)(*(uint *)(puVar1 + 4) != *(uint *)(param_1 + 8)));
    if (*(undefined **)(puVar1 + 8) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)(puVar1 + 8));
      *(int *)((int)this + 0xd8) = *(int *)((int)this + 0xd8) - *(int *)(puVar1 + 0xc);
    }
    FUN_00430df0(puVar1);
    puVar1 = puVar2;
  } while (puVar2 != (undefined *)0x0);
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}


/* 00467890 size=244 */

void FUN_00467890(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *local_4;
  
  piVar3 = FUN_0046b170(&local_4,0x44c,0x44c);
  piVar2 = param_1;
  if ((int *)*param_1 != (int *)0x0) {
    (**(code **)(*(int *)*param_1 + 8))();
  }
  piVar3 = (int *)*piVar3;
  *piVar2 = (int)piVar3;
  if (piVar3 != (int *)0x0) {
    (**(code **)(*piVar3 + 4))();
  }
  if (local_4 != (int *)0x0) {
    (**(code **)(*local_4 + 8))();
  }
  **(undefined1 **)(*piVar2 + 0x54) = 1;
  iVar1 = *piVar2;
  if ((uint)*(ushort *)(iVar1 + 0x36) <= *(ushort *)(iVar1 + 0x38) + 1) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    *(uint *)(iVar1 + 0x40) = *(uint *)(iVar1 + 0x40) | 4;
    return;
  }
  if (*(uint *)(iVar1 + 0x58) <= *(ushort *)(iVar1 + 0x34) + 1) {
    do {
      param_1 = (int *)((uint)param_1 & 0xffffff00);
      FUN_00414b10((void *)(iVar1 + 0x50),*(undefined1 **)(iVar1 + 0x58),(undefined1 *)&param_1,
                   &DAT_004ecc58);
    } while (*(uint *)(iVar1 + 0x58) <= *(ushort *)(iVar1 + 0x34) + 1);
  }
  *(undefined1 *)(*(int *)(iVar1 + 0x54) + (uint)*(ushort *)(iVar1 + 0x38)) = 3;
  *(short *)(iVar1 + 0x38) = *(short *)(iVar1 + 0x38) + 1;
  *(short *)(iVar1 + 0x34) = *(short *)(iVar1 + 0x34) + 1;
  return;
}


/* 00467990 size=28 */

void FUN_00467990(void *param_1,int param_2)

{
  FUN_004679b0(param_1,*(undefined4 **)(param_2 + 0x54),(uint)*(ushort *)(param_2 + 0x34));
  return;
}


/* 004679b0 size=195 */

void FUN_004679b0(void *param_1,undefined4 *param_2,uint param_3)

{
  void *this;
  void *this_00;
  
  this_00 = param_1;
  if (*(ushort *)((int)param_1 + 0x38) + 2 < (uint)*(ushort *)((int)param_1 + 0x36)) {
    if (*(uint *)((int)param_1 + 0x58) <= *(ushort *)((int)param_1 + 0x34) + 2) {
      this = (void *)((int)param_1 + 0x50);
      do {
        param_1 = (void *)((uint)param_1 & 0xffffff00);
        FUN_00414b10(this,*(undefined1 **)((int)this_00 + 0x58),(undefined1 *)&param_1,&DAT_004ecc58
                    );
      } while (*(uint *)((int)this_00 + 0x58) <= *(ushort *)((int)this_00 + 0x34) + 2);
    }
    *(undefined2 *)(*(int *)((int)this_00 + 0x54) + (uint)*(ushort *)((int)this_00 + 0x38)) =
         (undefined2)param_3;
    *(short *)((int)this_00 + 0x38) = *(short *)((int)this_00 + 0x38) + 2;
    *(short *)((int)this_00 + 0x34) = *(short *)((int)this_00 + 0x34) + 2;
  }
  else {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    *(uint *)((int)this_00 + 0x40) = *(uint *)((int)this_00 + 0x40) | 4;
  }
  FUN_0046b480(this_00,param_2,param_3);
  return;
}


/* 00467a80 size=61 */

void __thiscall FUN_00467a80(void *this,undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    *(undefined4 *)((int)this + 0xf0) = 0;
    *(undefined4 *)((int)this + 0xf4) = 0;
    *(undefined4 *)((int)this + 0xf8) = 0;
    *(undefined4 *)((int)this + 0xfc) = 0;
    return;
  }
  *(undefined4 *)((int)this + 0xf0) = *param_1;
  *(undefined4 *)((int)this + 0xf4) = param_1[1];
  *(undefined4 *)((int)this + 0xf8) = param_1[2];
  *(undefined4 *)((int)this + 0xfc) = param_1[3];
  return;
}


/* 00467ac0 size=72 */

int __thiscall FUN_00467ac0(void *this,byte *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (*(int *)((int)this + 0x44) != 0) {
    do {
      iVar1 = *(int *)(*(int *)((int)this + 0x40) + uVar3 * 4);
      if ((iVar1 != 0) &&
         (uVar2 = FUN_004c4c00((void *)(iVar1 + 4),(void *)(iVar1 + 4),param_1), uVar2 == 0)) {
        return iVar1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)((int)this + 0x44));
  }
  return 0;
}


/* 00467c90 size=246 */

void __thiscall FUN_00467c90(void *this,ushort param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  *(undefined2 *)((int)this + 0x34) = 1;
  *(ushort *)((int)this + 0x36) = param_1;
  *(undefined2 *)((int)this + 0x38) = 1;
  *(undefined2 *)((int)this + 0x3a) = 1;
  *(undefined4 *)((int)this + 0x40) = 0;
  *(void **)((int)this + 0x10) = this;
  uVar1 = (uint)param_1;
  if (*(uint *)((int)this + 0x58) < uVar1) {
    if (*(int *)((int)this + 0x54) != 0) {
      FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x54));
      *(undefined4 *)((int)this + 0x54) = 0;
      *(undefined4 *)((int)this + 0x5c) = 0;
    }
    *(undefined4 *)((int)this + 0x58) = 0;
    FUN_0040c870((void *)((int)this + 0x50),0,&DAT_004ecc58);
    *(undefined4 *)((int)this + 0x54) = 0;
    *(undefined4 *)((int)this + 0x58) = 0;
    *(uint *)((int)this + 0x60) = param_2 & 0xffff;
    *(undefined4 *)((int)this + 0x5c) = 0;
    if ((uVar1 != *(uint *)((int)this + 0x58)) || (param_1 == 0)) {
      if (*(int *)((int)this + 0x54) != 0) {
        FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x54));
        *(undefined4 *)((int)this + 0x54) = 0;
        *(undefined4 *)((int)this + 0x5c) = 0;
      }
      *(uint *)((int)this + 0x58) = uVar1;
      if (param_1 != 0) {
        iVar2 = FUN_0040c920(&DAT_004ecc58,0,*(int *)((int)this + 0x60) + uVar1);
        *(int *)((int)this + 0x54) = iVar2;
        if (iVar2 == 0) {
          *(undefined4 *)((int)this + 0x58) = 0;
          *(undefined4 *)((int)this + 0x5c) = 0;
          return;
        }
        *(undefined4 *)((int)this + 0x5c) = *(undefined4 *)((int)this + 0x60);
        return;
      }
    }
  }
  else {
    *(uint *)((int)this + 0x60) = param_2 & 0xffff;
  }
  return;
}


/* 00467d90 size=60 */

void __thiscall FUN_00467d90(void *this,undefined4 *param_1)

{
  param_1[0x17] = &PTR_LAB_004cbb50;
  FUN_0040c870(param_1 + 0x17,0,&DAT_004ecc58);
  param_1[3] = &PTR_LAB_004ccd18;
  if ((param_1 != (undefined4 *)0x0) && (this != (void *)0xfffffffc)) {
    *param_1 = *(undefined4 *)((int)this + 0x1c);
    *(undefined4 **)((int)this + 0x1c) = param_1;
  }
  return;
}


/* 00467dd0 size=262 */

/* WARNING: Removing unreachable block (ram,0x00467ea1) */

undefined4 __thiscall FUN_00467dd0(void *this,undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *unaff_retaddr;
  
  uVar1 = *(uint *)((int)this + 8);
  if (*(int *)((int)this + 0xc) != 0) {
    *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
    *(undefined4 *)(*(int *)((int)this + 4) + uVar1 * 4) = *param_1;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    return 1;
  }
  iVar3 = (**(code **)(DAT_004ecc58 + 4))((uVar1 + 1 + *(int *)((int)this + 0x10)) * 4);
  if (iVar3 == 0) {
    return 0;
  }
  uVar4 = 0;
  if (uVar1 != 0) {
    do {
      uVar4 = uVar4 + 1;
      *(undefined4 *)(iVar3 + -4 + uVar4 * 4) =
           *(undefined4 *)(*(int *)((int)this + 4) + -4 + uVar4 * 4);
    } while (uVar4 < uVar1);
  }
  if (uVar1 < *(uint *)((int)this + 8)) {
    uVar4 = uVar1;
    puVar5 = (undefined4 *)(iVar3 + 4 + uVar1 * 4);
    do {
      uVar4 = uVar4 + 1;
      *puVar5 = *(undefined4 *)(*(int *)((int)this + 4) + -4 + uVar4 * 4);
      puVar5 = puVar5 + 1;
    } while (uVar4 < *(uint *)((int)this + 8));
  }
  *(undefined4 *)(iVar3 + uVar1 * 4) = *unaff_retaddr;
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


/* 00467ee0 size=269 */

void __thiscall FUN_00467ee0(void *this,uint param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if ((uint)(*(int *)((int)this + 0x10) * 2) <= *(uint *)((int)this + 0xc)) {
    iVar1 = *(int *)((int)this + 0x10) + -1 + *(int *)((int)this + 8);
    iVar2 = (**(code **)(DAT_004ecc58 + 4))(iVar1 * 4);
    if ((iVar2 != 0) || (iVar2 = 0, iVar1 == 0)) {
      uVar3 = 0;
      if (param_1 != 0) {
        do {
          uVar3 = uVar3 + 1;
          *(undefined4 *)(iVar2 + -4 + uVar3 * 4) =
               *(undefined4 *)(*(int *)((int)this + 4) + -4 + uVar3 * 4);
        } while (uVar3 < param_1);
      }
      if (param_1 < *(int *)((int)this + 8) - 1U) {
        puVar4 = (undefined4 *)(iVar2 + param_1 * 4);
        do {
          param_1 = param_1 + 1;
          *puVar4 = *(undefined4 *)((*(int *)((int)this + 4) - iVar2) + (int)(puVar4 + 1));
          puVar4 = puVar4 + 1;
        } while (param_1 < *(int *)((int)this + 8) - 1U);
      }
      iVar1 = *(int *)((int)this + 4);
      if (iVar1 != 0) {
        if (iVar1 != 0) {
          (**(code **)(DAT_004ecc58 + 8))(iVar1);
        }
        *(undefined4 *)((int)this + 4) = 0;
      }
      *(undefined4 *)((int)this + 0xc) = 0;
      *(int *)((int)this + 4) = iVar2;
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
      *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
      return;
    }
  }
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if (param_1 < *(int *)((int)this + 8) - 1U) {
    do {
      param_1 = param_1 + 1;
      *(undefined4 *)(*(int *)((int)this + 4) + -4 + param_1 * 4) =
           *(undefined4 *)(*(int *)((int)this + 4) + param_1 * 4);
    } while (param_1 < *(int *)((int)this + 8) - 1U);
  }
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
  return;
}


