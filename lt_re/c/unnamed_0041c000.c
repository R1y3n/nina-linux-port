/* lithtech.exe decompilation - unnamed_0041c000 */
#include "ghidra_types.h"

/* 0041c130 size=626 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0041c130: lifted from original x86 -> lt_lifted.c */


/* 0041c3b0 size=562 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0041c3b0(undefined4 *param_1,float *param_2)

{
  DAT_004e8e48 = *param_1;
  DAT_004e8e4c = param_2[1];
  DAT_004e8e50 = param_1[2];
  DAT_004e8e54 = *param_1;
  DAT_004e8e58 = param_2[1];
  DAT_004e8e5c = param_2[2];
  DAT_004e8e60 = *param_2;
  DAT_004e8e64 = param_2[1];
  DAT_004e8e68 = param_2[2];
  DAT_004e8e78 = *param_1;
  DAT_004e8e7c = param_2[1];
  DAT_004e8e80 = param_1[2];
  DAT_004e8e84 = *param_1;
  DAT_004e8e88 = param_2[1];
  DAT_004e8e8c = param_2[2];
  DAT_004e8e90 = *param_2;
  DAT_004e8e94 = param_2[1];
  DAT_004e8e6c = *param_2;
  DAT_004e8e98 = param_2[2];
  DAT_004e8e70 = param_2[1];
  DAT_004e8e9c = *param_2;
  DAT_004e8e74 = param_1[2];
  DAT_004e8ea0 = param_2[1];
  DAT_004e8ea4 = param_1[2];
  DAT_004e8ea8 = *param_1;
  DAT_004e8eac = param_1[1];
  DAT_004e8eb0 = param_1[2];
  DAT_004e8eb4 = *param_1;
  DAT_004e8eb8 = param_1[1];
  DAT_004e8ebc = param_2[2];
  DAT_004e8ec0 = *param_2;
  DAT_004e8ec4 = param_1[1];
  DAT_004e8ec8 = param_2[2];
  DAT_004e8ecc = *param_2;
  DAT_004e8ed0 = param_1[1];
  _DAT_004e8ed8 = *param_1;
  _DAT_004e8edc = param_1[1];
  _DAT_004e8ee0 = param_1[2];
  _DAT_004e8ee4 = *param_1;
  _DAT_004e8ee8 = param_1[1];
  _DAT_004e8eec = param_2[2];
  _DAT_004e8ef0 = *param_2;
  _DAT_004e8ef4 = param_1[1];
  DAT_004e8ed4 = param_1[2];
  _DAT_004e8ef8 = param_2[2];
  _DAT_004e8efc = *param_2;
  _DAT_004e8f00 = param_1[1];
  _DAT_004e8f04 = param_1[2];
  DAT_004e90a4 = *param_1;
  DAT_004e90b4 = -*param_2;
  _DAT_004e90c4 = param_1[1];
  _DAT_004e90d4 = -param_2[1];
  _DAT_004e90e4 = param_1[2];
  _DAT_004e90f4 = -param_2[2];
  return;
}


/* 0041cc70 size=95 */

undefined4 __cdecl FUN_0041cc70(ushort param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_4;
  
  local_4 = 0;
  iVar1 = FUN_0041ccd0(param_1,param_2,0,&local_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_4 == 0) {
    return 1;
  }
  iVar1 = FUN_00419020();
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = FUN_0041ccd0(param_1,param_2,1,&local_4);
  return uVar2;
}


/* 0041ccd0 size=4465 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0041ccd0: lifted from original x86 -> lt_lifted.c */


/* 0041de50 size=20 */

undefined4 __fastcall FUN_0041de50(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if ((iVar1 == 0) || (*(int *)(iVar1 + 0x2c) == 0)) {
    return 0;
  }
  return *(undefined4 *)(iVar1 + 0x28);
}


/* 0041de70 size=293 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_0041de70(float *param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
            float param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  *param_1 = param_2;
  fVar4 = SQRT(param_5 * param_5 + param_7 * param_7 + param_6 * param_6);
  param_1[1] = param_3;
  param_1[2] = param_4;
  if (_DAT_004cbf00 <= fVar4) {
    fVar1 = *param_1;
    *param_1 = param_5 + fVar1;
    fVar2 = param_1[1];
    param_1[1] = param_6 + fVar2;
    fVar3 = param_1[2];
    param_1[2] = param_7 + fVar3;
    if (((param_5 + fVar1 == param_2) && (param_6 + fVar2 == param_3)) &&
       (param_7 + fVar3 == param_4)) {
      fVar4 = (SQRT(param_2 * param_2 + param_4 * param_4 + param_3 * param_3) * _DAT_004cbf00) /
              fVar4;
      *param_1 = param_2 + param_5 * fVar4;
      param_1[1] = param_6 * fVar4 + param_3;
      param_1[2] = fVar4 * param_7 + param_4;
    }
  }
  return;
}


/* 0041dfa0 size=176 */

void __cdecl FUN_0041dfa0(undefined4 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined8 uVar5;
  LARGE_INTEGER local_c;
  int *local_4;
  
  FUN_00424310(&local_c,0);
  local_4 = &DAT_004e6e1c;
  FUN_00424400(&local_c);
  iVar1 = DAT_004e7630;
  if (DAT_004e7630 < 0x14) {
    if ((param_2 != 0) && (iVar3 = 0, 0 < DAT_004e7630)) {
      piVar4 = &DAT_004e8f18;
      do {
        if (*piVar4 == param_2) goto LAB_0041e031;
        iVar3 = iVar3 + 1;
        piVar4 = piVar4 + 5;
      } while (iVar3 < DAT_004e7630);
    }
    iVar2 = DAT_004e7630 + 1;
    (&DAT_004e8f08)[DAT_004e7630 * 5] = *param_1;
    (&DAT_004e8f0c)[DAT_004e7630 * 5] = param_1[1];
    (&DAT_004e8f10)[DAT_004e7630 * 5] = param_1[2];
    iVar3 = DAT_004e7630 * 5;
    DAT_004e7630 = iVar2;
    (&DAT_004e8f14)[iVar3] = param_1[3];
    (&DAT_004e8f18)[iVar1 * 5] = param_2;
    if (1 < iVar2) {
      FUN_0041e050();
    }
  }
LAB_0041e031:
  uVar5 = FUN_00424410((uint *)&local_c);
  *local_4 = *local_4 + (int)uVar5;
  return;
}


/* 0041e050 size=559 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0041e050: lifted from original x86 -> lt_lifted.c */


/* 0041e280 size=2022 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0041e280: lifted from original x86 -> lt_lifted.c */


/* 0041ea70 size=2841 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0041ea70: lifted from original x86 -> lt_lifted.c */


/* 0041f590 size=1541 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0041f590: lifted from original x86 -> lt_lifted.c */


/* 0041fba0 size=689 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0041fba0(int *param_1,int param_2,int param_3,float *param_4,float param_5)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int *piVar8;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  piVar8 = (int *)(**(code **)(*param_1 + 4))();
  pfVar2 = (float *)*piVar8;
  fVar4 = *(float *)(param_2 + 0xc4) * *param_4 +
          *(float *)(param_2 + 0xcc) * param_4[2] + *(float *)(param_2 + 200) * param_4[1];
  fStack_10 = -fVar4;
  fStack_18 = fStack_10 * *param_4;
  fStack_14 = fStack_10 * param_4[1];
  fStack_10 = fStack_10 * param_4[2];
  pfVar1 = (float *)(param_3 + 0xc4);
  fVar5 = -*param_4 * *pfVar1 +
          -param_4[1] * *(float *)(param_3 + 200) + -param_4[2] * *(float *)(param_3 + 0xcc);
  fStack_4 = -fVar5;
  fStack_c = fStack_4 * -*param_4;
  fStack_8 = -param_4[1] * fStack_4;
  fStack_4 = -param_4[2] * fStack_4;
  *pfVar2 = *param_4;
  pfVar2[1] = param_4[1];
  fVar3 = param_4[2];
  pfVar2[5] = 0.0;
  pfVar2[2] = fVar3;
  pfVar2[3] = param_5;
  fVar6 = (*(float *)(param_2 + 0xe4) + *(float *)(param_3 + 0xe4)) * _DAT_004cbec0;
  fVar3 = (fStack_18 - fStack_c) * fVar6;
  fVar7 = (fStack_14 - fStack_8) * fVar6;
  fVar6 = (fStack_10 - fStack_4) * fVar6;
  fVar3 = fVar3 * fVar3 + fVar7 * fVar7 + fVar6 * fVar6;
  if (((*(uint *)(param_2 + 0x88) & 0x10000) != 0) && (*(float *)(param_2 + 0xe8) <= fVar3)) {
    (**(code **)(*param_1 + 8))(param_2,param_3,&fStack_18,SQRT(fVar3));
  }
  if (((*(uint *)(param_3 + 0x88) & 0x10000) != 0) && (*(float *)(param_3 + 0xe8) <= fVar3)) {
    (**(code **)(*param_1 + 8))(param_3,param_2,&fStack_c,-SQRT(fVar3));
  }
  if ((fVar4 < _DAT_004cb524) && (*(byte *)(param_2 + 0xbd) <= *(byte *)(param_3 + 0xbd))) {
    *(uint *)(param_2 + 0x124) = *(uint *)(param_2 + 0x124) | 0x40;
    *(float *)(param_2 + 0xc4) = fStack_18 + *(float *)(param_2 + 0xc4);
    *(float *)(param_2 + 200) = fStack_14 + *(float *)(param_2 + 200);
    *(float *)(param_2 + 0xcc) = fStack_10 + *(float *)(param_2 + 0xcc);
  }
  if ((fVar5 < _DAT_004cb524) && (*(byte *)(param_3 + 0xbd) <= *(byte *)(param_2 + 0xbd))) {
    *(uint *)(param_3 + 0x124) = *(uint *)(param_3 + 0x124) | 0x40;
    *pfVar1 = fStack_c + *pfVar1;
    *(float *)(param_3 + 200) = fStack_8 + *(float *)(param_3 + 200);
    *(float *)(param_3 + 0xcc) = fStack_4 + *(float *)(param_3 + 0xcc);
  }
  return;
}


/* 0041fe60 size=23 */

void __thiscall FUN_0041fe60(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)this = param_1;
  *(undefined4 *)((int)this + 4) = param_2;
  *(undefined4 *)((int)this + 8) = param_3;
  return;
}


/* 0041fe80 size=33 */

float10 __fastcall FUN_0041fe80(float *param_1)

{
  return SQRT((float10)param_1[2] * (float10)param_1[2] +
              (float10)param_1[1] * (float10)param_1[1] + (float10)*param_1 * (float10)*param_1);
}


/* 0041feb0 size=27 */

float10 __thiscall FUN_0041feb0(float *param_1,float param_2,float param_3,float param_4)

{
  return (float10)param_2 * (float10)*param_1 +
         (float10)param_3 * (float10)param_1[1] + (float10)param_4 * (float10)param_1[2];
}


/* 0041fed0 size=29 */

int __thiscall FUN_0041fed0(void *this,float *param_1)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)((int)this + 8);
  fVar2 = *(float *)((int)this + 4);
  *param_1 = -*(float *)this;
  param_1[1] = -fVar2;
  param_1[2] = -fVar1;
  return;
}


/* 0041fef0 size=35 */

int __thiscall FUN_0041fef0(void *this,float *param_1,float param_2,float param_3,float param_4)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)((int)this + 8);
  fVar2 = *(float *)((int)this + 4);
  *param_1 = param_2 + *(float *)this;
  param_1[1] = param_3 + fVar2;
  param_1[2] = param_4 + fVar1;
  return;
}


/* 0041ff20 size=35 */

int __thiscall FUN_0041ff20(void *this,float *param_1,float param_2,float param_3,float param_4)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)((int)this + 8);
  fVar2 = *(float *)((int)this + 4);
  *param_1 = *(float *)this - param_2;
  param_1[1] = fVar2 - param_3;
  param_1[2] = fVar1 - param_4;
  return;
}


/* 0041ff50 size=35 */

int __thiscall FUN_0041ff50(void *this,float *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)((int)this + 8);
  fVar2 = *(float *)((int)this + 4);
  *param_1 = param_2 * *(float *)this;
  param_1[1] = param_2 * fVar2;
  param_1[2] = param_2 * fVar1;
  return;
}


/* 0041ff80 size=31 */

void __thiscall FUN_0041ff80(void *this,float param_1,float param_2,float param_3)

{
  *(float *)this = param_1 + *(float *)this;
  *(float *)((int)this + 4) = param_2 + *(float *)((int)this + 4);
  *(float *)((int)this + 8) = param_3 + *(float *)((int)this + 8);
  return;
}


/* 0041ffa0 size=31 */

void __thiscall FUN_0041ffa0(void *this,float param_1)

{
  *(float *)this = param_1 * *(float *)this;
  *(float *)((int)this + 4) = param_1 * *(float *)((int)this + 4);
  *(float *)((int)this + 8) = param_1 * *(float *)((int)this + 8);
  return;
}


/* 0041ffc0 size=54 */

undefined4 __thiscall FUN_0041ffc0(void *this,float *param_1)

{
  if (((*(float *)this == *param_1) && (*(float *)((int)this + 4) == param_1[1])) &&
     (*(float *)((int)this + 8) == param_1[2])) {
    return 0;
  }
  return 1;
}


