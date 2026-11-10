/* lithtech.exe decompilation - unnamed_0043c000 */
#include "ghidra_types.h"

/* 0043c210 size=252 */

undefined4 __cdecl FUN_0043c210(ushort param_1,int param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  undefined4 unaff_EBX;
  uint unaff_EBP;
  ushort uVar3;
  int unaff_retaddr;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_24;
  undefined1 auStack_20 [8];
  undefined4 auStack_18 [5];
  int iStack_4;
  
  piVar1 = param_3;
  uStack_3c = &param_3;
  uStack_38 = 2;
  (**(code **)(*param_3 + 8))();
  piVar2 = param_3;
  uVar3 = 0;
  if (param_1 != 0) {
    do {
      (**(code **)(*piVar1 + 8))(&uStack_24);
      (**(code **)(*piVar1 + 8))(auStack_20,0x10);
      (**(code **)(*piVar1 + 8))(&uStack_3c,2);
      (**(code **)(*piVar1 + 8))(auStack_20 + -0x20,4);
      if ((int)piVar2 <= (int)(unaff_EBP & 0xffff)) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_RestoreAttachments_004d973c);
        }
        return 1;
      }
      FUN_0046a860(iStack_4 + 0x394,unaff_retaddr,
                   *(undefined2 *)(*(int *)(param_2 + (unaff_EBP & 0xffff) * 4) + 0xb8),unaff_EBX,
                   &uStack_24,auStack_18,(undefined4 *)0x0);
      uVar3 = uVar3 + 1;
    } while (uVar3 < param_1);
  }
  return 0;
}


/* 0043c310 size=198 */

undefined4 __cdecl FUN_0043c310(ushort param_1,int param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  uint unaff_EBX;
  uint unaff_EBP;
  ushort uVar3;
  int unaff_retaddr;
  undefined1 auStack_6 [2];
  int iStack_4;
  
  piVar1 = param_3;
  (**(code **)(*param_3 + 8))(&param_3,2);
  piVar2 = param_3;
  uVar3 = 0;
  if (param_1 != 0) {
    do {
      (**(code **)(*piVar1 + 8))(auStack_6 + -6,1);
      (**(code **)(*piVar1 + 8))(auStack_6 + -0x12,2);
      if ((int)piVar2 <= (int)(unaff_EBP & 0xffff)) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_RestoreInterlinks_004d9750);
        }
        return 1;
      }
      FUN_004457d0(iStack_4,unaff_retaddr,*(int *)(param_2 + (unaff_EBP & 0xffff) * 4),
                   unaff_EBX & 0xff);
      uVar3 = uVar3 + 1;
    } while (uVar3 < param_1);
  }
  return 0;
}


/* 0043c3e0 size=21 */

void __thiscall FUN_0043c3e0(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0x10) = param_1;
  *(undefined4 *)((int)this + 0xc) = 0;
  return;
}


/* 0043c440 size=10 */

void FUN_0043c440(void)

{
  FUN_0043c470(&DAT_004e99cc);
  return;
}


/* 0043c450 size=12 */

void FUN_0043c450(void)

{
  FUN_004b9cf5(&LAB_0043c460);
  return;
}


/* 0043c470 size=59 */

undefined4 __fastcall FUN_0043c470(undefined4 param_1)

{
  DAT_004e99d7 = 0;
  DAT_004e99d6 = 1;
  DAT_004e99d2 = 2;
  DAT_004e99d3 = 3;
  DAT_004e99d1 = 4;
  DAT_004e99d0 = 5;
  DAT_004e99d4 = 6;
  DAT_004e99d5 = 7;
  return param_1;
}


/* 0043c4b0 size=1 */

void FUN_0043c4b0(void)

{
  return;
}


/* 0043c4c0 size=64 */

void __cdecl FUN_0043c4c0(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[0x47] = 0;
  param_1[0x48] = 0;
  param_1[0x49] = 0;
  param_1[0x4a] = 0x3f800000;
  *(undefined1 *)(param_1 + 6) = 0;
  param_1[0x4b] = 0;
  param_1[0x4c] = 0;
  param_1[0x4d] = 0;
  return;
}


/* 0043c580 size=65 */

void __cdecl FUN_0043c580(int param_1,float param_2)

{
  longlong lVar1;
  
  FUN_004b9f62((undefined1 *)(param_1 + 0x18),&DAT_004d9780,SUB84((double)param_2,0));
  *(float *)(param_1 + 0x130) = param_2;
  lVar1 = __ftol();
  *(int *)(param_1 + 300) = (int)lVar1;
  *(int *)(param_1 + 0x134) = (int)lVar1;
  return;
}


/* 0043c640 size=27 */

void __cdecl FUN_0043c640(undefined4 *param_1,float param_2)

{
  FUN_0043c4c0(param_1);
  FUN_0043c580((int)param_1,param_2);
  return;
}


/* 0043c660 size=61 */

void __cdecl FUN_0043c660(float *param_1,float *param_2)

{
  FUN_0043c4c0(param_1);
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  FUN_0043ced0(*param_1,param_1[1],param_1[2],param_1 + 0x47);
  return;
}


/* 0043c790 size=63 */

void __thiscall FUN_0043c790(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  undefined2 unaff_BX;
  
  pcVar2 = param_1;
  uVar3 = 0xffffffff;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *param_1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  param_1 = (char *)(~uVar3 - 1);
  (**(code **)(*(int *)this + 0x24))(&param_1,2);
  (**(code **)(*(int *)this + 0x24))(pcVar2,unaff_BX);
  return;
}


/* 0043c890 size=753 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0043c890: lifted from original x86 -> lt_lifted.c */


/* 0043cb90 size=351 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0043cb90: lifted from original x86 -> lt_lifted.c */


/* 0043ccf0 size=210 */

void __cdecl FUN_0043ccf0(float param_1,float param_2,float param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  
  fVar4 = (float10)fcos((float10)param_2);
  param_4[3] = 0.0;
  param_4[7] = 0.0;
  param_4[0xb] = 0.0;
  param_4[0xe] = 0.0;
  param_4[0xd] = 0.0;
  param_4[0xc] = 0.0;
  param_4[0xf] = 1.0;
  fVar5 = (float10)fsin((float10)param_2);
  fVar6 = (float10)fcos((float10)param_1);
  fVar1 = (float)fVar6;
  fVar6 = (float10)fsin((float10)param_1);
  fVar7 = (float10)fcos((float10)param_3);
  fVar2 = (float)fVar7;
  fVar7 = (float10)fsin((float10)param_3);
  fVar3 = (float)fVar7;
  *param_4 = (float)((float10)fVar2 * fVar4 + fVar7 * fVar6 * fVar5);
  param_4[1] = (float)((float10)fVar2 * fVar6 * fVar5 - (float10)fVar3 * fVar4);
  param_4[2] = (float)((float10)fVar1 * fVar5);
  param_4[4] = fVar3 * fVar1;
  param_4[5] = fVar2 * fVar1;
  param_4[6] = (float)-fVar6;
  param_4[8] = (float)((float10)(float)(fVar7 * fVar6) * fVar4 - (float10)fVar2 * fVar5);
  param_4[9] = (float)((float10)fVar3 * fVar5 + (float10)(float)((float10)fVar2 * fVar6) * fVar4);
  param_4[10] = (float)((float10)fVar1 * fVar4);
  return;
}


/* 0043cdd0 size=66 */

void __cdecl FUN_0043cdd0(float *param_1,float param_2,float param_3,float param_4)

{
  FUN_0043ccf0(param_2,param_3,param_4,param_1);
  return;
}


/* 0043ce20 size=19 */

void __cdecl FUN_0043ce20(float *param_1,float *param_2)

{
  FUN_0044e720(param_1,param_2);
  return;
}


/* 0043ce40 size=19 */

void __cdecl FUN_0043ce40(float *param_1,float *param_2)

{
  FUN_0044e8c0(param_2,param_1);
  return;
}


/* 0043ce60 size=29 */

void __cdecl FUN_0043ce60(float *param_1,float *param_2,undefined4 *param_3,undefined4 *param_4)

{
  FUN_0044e9d0(param_1,param_2,param_3,param_4);
  return;
}


/* 0043ce80 size=29 */

void __cdecl FUN_0043ce80(float *param_1,float *param_2,float *param_3,float param_4)

{
  FUN_0044ea30(param_1,param_2,param_3,param_4);
  return;
}


/* 0043cea0 size=47 */

void __cdecl FUN_0043cea0(float param_1,float param_2,float param_3,float *param_4)

{
  float local_40 [16];
  
  FUN_0043cdd0(local_40,param_1,param_2,param_3);
  FUN_0043ce40(local_40,param_4);
  return;
}


/* 0043ced0 size=66 */

void __cdecl FUN_0043ced0(float param_1,float param_2,float param_3,float *param_4)

{
  FUN_0043cea0(param_1,param_2,param_3,param_4);
  return;
}


/* 0043cf20 size=114 */

void __cdecl
FUN_0043cf20(float param_1,float param_2,float param_3,float *param_4,undefined4 *param_5,
            undefined4 *param_6)

{
  float local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  FUN_0043ccf0(param_1,param_2,param_3,&local_40);
  *param_4 = local_40;
  param_4[1] = local_30;
  param_4[2] = local_20;
  *param_5 = local_3c;
  param_5[1] = local_2c;
  param_5[2] = local_1c;
  *param_6 = local_38;
  param_6[1] = local_28;
  param_6[2] = local_18;
  return;
}


/* 0043cfa0 size=196 */

void __cdecl FUN_0043cfa0(float *param_1,float *param_2,float *param_3,float *param_4)

{
  if (param_2 == (float *)0x0) {
    *param_4 = 1.0;
    param_4[1] = 0.0;
    param_4[2] = 0.0;
    param_4[3] = 0.0;
    param_4[4] = 0.0;
    param_4[5] = 1.0;
    param_4[6] = 0.0;
    param_4[7] = 0.0;
    param_4[8] = 0.0;
    param_4[9] = 0.0;
    param_4[10] = 1.0;
    param_4[0xb] = 0.0;
    param_4[0xc] = 0.0;
    param_4[0xd] = 0.0;
    param_4[0xe] = 0.0;
    param_4[0xf] = 1.0;
  }
  else {
    FUN_0044e720(param_2,param_4);
  }
  if (param_3 != (float *)0x0) {
    *param_4 = *param_3 * *param_4;
    param_4[4] = *param_3 * param_4[4];
    param_4[8] = *param_3 * param_4[8];
    param_4[1] = param_4[1] * param_3[1];
    param_4[5] = param_4[5] * param_3[1];
    param_4[9] = param_4[9] * param_3[1];
    param_4[2] = param_3[2] * param_4[2];
    param_4[6] = param_3[2] * param_4[6];
    param_4[10] = param_3[2] * param_4[10];
  }
  if (param_1 != (float *)0x0) {
    param_4[3] = *param_1;
    param_4[7] = param_1[1];
    param_4[0xb] = param_1[2];
  }
  return;
}


/* 0043d070 size=236 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0043d070(float *param_1,float param_2,float param_3,float param_4,float param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float10 fVar5;
  float10 fVar6;
  
  fVar5 = (float10)fsin((float10)param_5);
  param_1[0xc] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[3] = 0.0;
  param_1[7] = 0.0;
  param_1[0xb] = 0.0;
  param_1[0xf] = 1.0;
  fVar6 = (float10)fcos((float10)param_5);
  fVar1 = (float)fVar6;
  fVar3 = _DAT_004cba94 - fVar1;
  fVar4 = fVar3 * param_2;
  *param_1 = fVar4 * param_2 + fVar1;
  param_1[4] = (float)((float10)fVar4 * (float10)param_3 + fVar5 * (float10)param_4);
  param_1[8] = param_4 * fVar4 - (float)(fVar5 * (float10)param_3);
  param_1[1] = (float)((float10)fVar4 * (float10)param_3 - fVar5 * (float10)param_4);
  param_1[5] = fVar3 * param_3 * param_3 + fVar1;
  fVar2 = param_4 * fVar3 * param_3;
  param_1[9] = fVar2 + (float)(fVar5 * (float10)param_2);
  param_1[2] = param_4 * fVar4 + (float)(fVar5 * (float10)param_3);
  param_1[6] = fVar2 - (float)(fVar5 * (float10)param_2);
  param_1[10] = param_4 * fVar3 * param_4 + fVar1;
  return;
}


/* 0043d160 size=718 */

void __cdecl
FUN_0043d160(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180 [4];
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  float local_140 [4];
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  float local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  float local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  float local_100 [4];
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  float local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  float local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  float local_c0 [16];
  float local_80 [16];
  float local_40 [16];
  
  local_100[0] = 1.0;
  local_100[1] = 0.0;
  local_198 = *param_1;
  local_100[2] = 0.0;
  local_f0 = 0;
  local_194 = param_1[1];
  local_ec = 0x3f800000;
  local_190 = param_1[2];
  local_e8 = 0;
  local_e0 = 0;
  local_188 = param_2[1] - local_194;
  local_dc = 0;
  local_d8 = 0x3f800000;
  local_d0 = 0;
  local_cc = 0;
  local_184 = param_2[2] - local_190;
  local_c8 = 0;
  local_c4 = 0x3f800000;
  local_140[0] = 1.0;
  local_140[1] = 0.0;
  local_100[3] = -*param_1;
  local_e4 = -param_1[1];
  local_d4 = -param_1[2];
  local_140[2] = 0.0;
  local_130 = 0;
  local_140[3] = (*param_2 - local_198) + *param_1;
  local_12c = 0x3f800000;
  local_128 = 0;
  local_120 = 0;
  local_11c = 0;
  local_124 = local_188 + param_1[1];
  local_118 = 0x3f800000;
  local_110 = 0;
  local_10c = 0;
  local_108 = 0;
  local_114 = local_184 + param_1[2];
  local_104 = 0x3f800000;
  FUN_0043ce20(param_3,local_c0);
  FUN_0043d430(local_180,local_140,local_c0);
  pfVar2 = local_180;
  pfVar3 = local_80;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar3 = pfVar3 + 1;
  }
  FUN_0043d430(local_40,local_80,local_100);
  pfVar2 = local_40;
  pfVar3 = param_4;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar3 = pfVar3 + 1;
  }
  local_18c = param_4[3];
  local_188 = param_4[7];
  local_184 = param_4[0xb];
  local_180[0] = *param_4;
  local_180[1] = param_4[4];
  local_180[2] = param_4[8];
  local_170 = param_4[1];
  local_16c = param_4[5];
  local_168 = param_4[9];
  local_160 = param_4[2];
  local_15c = param_4[6];
  local_158 = param_4[10];
  FUN_0043a341(&local_198,local_180,&local_18c);
  local_180[3] = -local_198;
  local_164 = -local_194;
  local_154 = -local_190;
  local_148 = 0;
  local_14c = 0;
  local_150 = 0;
  local_144 = 0x3f800000;
  pfVar2 = local_180;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_5 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_5 = param_5 + 1;
  }
  return;
}


/* 0043d430 size=532 */

void __cdecl FUN_0043d430(float *param_1,float *param_2,float *param_3)

{
  *param_1 = param_2[3] * param_3[0xc] +
             *param_2 * *param_3 + param_2[1] * param_3[4] + param_3[8] * param_2[2];
  param_1[4] = *param_3 * param_2[4] +
               param_2[7] * param_3[0xc] + param_2[5] * param_3[4] + param_3[8] * param_2[6];
  param_1[8] = param_2[9] * param_3[4] +
               param_2[10] * param_3[8] + param_2[8] * *param_3 + param_2[0xb] * param_3[0xc];
  param_1[0xc] = param_2[0xf] * param_3[0xc] +
                 param_2[0xd] * param_3[4] + param_2[0xc] * *param_3 + param_3[8] * param_2[0xe];
  param_1[1] = param_3[1] * *param_2 +
               param_3[9] * param_2[2] + param_2[1] * param_3[5] + param_3[0xd] * param_2[3];
  param_1[5] = param_2[6] * param_3[9] +
               param_2[7] * param_3[0xd] + param_3[1] * param_2[4] + param_2[5] * param_3[5];
  param_1[9] = param_3[1] * param_2[8] +
               param_2[10] * param_3[9] + param_2[0xb] * param_3[0xd] + param_3[5] * param_2[9];
  param_1[0xd] = param_3[5] * param_2[0xd] +
                 param_3[9] * param_2[0xe] + param_3[0xd] * param_2[0xf] + param_3[1] * param_2[0xc]
  ;
  param_1[2] = param_3[2] * *param_2 +
               param_3[10] * param_2[2] + param_2[1] * param_3[6] + param_3[0xe] * param_2[3];
  param_1[6] = param_2[6] * param_3[10] +
               param_2[7] * param_3[0xe] + param_3[2] * param_2[4] + param_2[5] * param_3[6];
  param_1[10] = param_3[2] * param_2[8] +
                param_2[10] * param_3[10] + param_2[0xb] * param_3[0xe] + param_3[6] * param_2[9];
  param_1[0xe] = param_3[6] * param_2[0xd] +
                 param_3[10] * param_2[0xe] +
                 param_3[0xe] * param_2[0xf] + param_3[2] * param_2[0xc];
  param_1[3] = param_3[3] * *param_2 +
               param_3[0xb] * param_2[2] + param_2[1] * param_3[7] + param_3[0xf] * param_2[3];
  param_1[7] = param_2[6] * param_3[0xb] +
               param_2[7] * param_3[0xf] + param_3[3] * param_2[4] + param_2[5] * param_3[7];
  param_1[0xb] = param_3[3] * param_2[8] +
                 param_2[10] * param_3[0xb] + param_2[0xb] * param_3[0xf] + param_3[7] * param_2[9];
  param_1[0xf] = param_3[7] * param_2[0xd] +
                 param_3[0xb] * param_2[0xe] +
                 param_3[0xf] * param_2[0xf] + param_3[3] * param_2[0xc];
  return;
}


/* 0043d650 size=16 */

void __fastcall FUN_0043d650(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cc4cc;
  param_1[3] = 0;
  return;
}


/* 0043e5f0 size=136 */

int __thiscall FUN_0043e5f0(void *this,undefined4 param_1)

{
  int *piVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 *puStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined1 *puStack_54;
  undefined4 *puStack_50;
  undefined1 local_3c [2];
  undefined1 auStack_3a [18];
  undefined1 auStack_28 [12];
  undefined4 uStack_1c;
  undefined4 uStack_14;
  undefined4 uStack_10;
  int iStack_8;
  
  uVar3 = param_1;
  puStack_54 = local_3c;
  puStack_50 = &param_1;
  piVar1 = *(int **)((int)this + 8);
  piVar2 = *(int **)((int)this + 4);
  uStack_58 = param_1;
  uStack_5c = 0x43e615;
  iVar4 = (**(code **)(*(int *)this + 0x10))();
  if (iVar4 == 0) {
    puStack_60 = auStack_28;
    uStack_5c = 1;
    iVar4 = (**(code **)(*(int *)this + 0x18))(uVar3);
    if (iVar4 == 0) {
      if (iStack_8 == 0) {
        iVar4 = (**(code **)(*piVar1 + 0x20))(uStack_14,uStack_10,&puStack_50,0);
      }
      else {
        iVar4 = (**(code **)(*piVar1 + 0x1c))();
      }
      if (iVar4 == 0) {
        (**(code **)(*piVar2 + 0x1c))(uStack_1c,local_3c + -8,&puStack_60);
        iVar4 = 0;
      }
    }
  }
  return iVar4;
}


/* 0043eb80 size=66 */

undefined4 FUN_0043eb80(int param_1)

{
  uint uVar1;
  
  if ((param_1 == 0) || (*(char *)(param_1 + 0xbc) != '\x02')) {
    return 0x57;
  }
  uVar1 = (**(code **)(**(int **)(param_1 + 0x1b0) + 0x20))();
  if (((uVar1 & 4) == 0) &&
     (uVar1 = (**(code **)(**(int **)(param_1 + 0x1b0) + 0x20))(), (uVar1 & 8) == 0)) {
    return 0x57;
  }
  return 0x56;
}


/* 0043ec40 size=121 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0043ec40(int param_1,undefined4 *param_2)

{
  *param_2 = *(undefined4 *)(param_1 + 0x20);
  param_2[1] = *(undefined4 *)(param_1 + 0x34);
  param_2[2] = *(undefined4 *)(param_1 + 0x38);
  param_2[3] = (float)*(uint *)(param_1 + 0x3c) * _DAT_004cbaf0;
  param_2[4] = *(undefined4 *)(param_1 + 0x40);
  param_2[5] = *(undefined4 *)(param_1 + 0x44);
  param_2[6] = *(undefined4 *)(param_1 + 0x48);
  param_2[7] = *(undefined4 *)(param_1 + 0x4c);
  param_2[8] = *(undefined4 *)(param_1 + 0x50);
  param_2[9] = *(undefined4 *)(param_1 + 0x54);
  param_2[10] = *(undefined4 *)(param_1 + 0x58);
  param_2[0xb] = *(undefined4 *)(param_1 + 0x5c);
  return;
}


/* 0043ecc0 size=99 */

void __cdecl FUN_0043ecc0(int param_1,int param_2)

{
  longlong lVar1;
  
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_2 + 4);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_2 + 8);
  lVar1 = __ftol();
  *(int *)(param_1 + 0x3c) = (int)lVar1;
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_2 + 0x14);
  *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_2 + 0x1c);
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_2 + 0x2c);
  return;
}


/* 0043ed30 size=110 */

longlong FUN_0043ed30(void)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  
  lVar2 = __ftol();
  lVar3 = __ftol();
  uVar1 = (uint)((ulonglong)lVar3 >> 0x20);
  if ((int)lVar2 == (int)lVar3) {
    lVar2 = __ftol();
    lVar3 = __ftol();
    uVar1 = (uint)((ulonglong)lVar3 >> 0x20);
    if ((int)lVar2 == (int)lVar3) {
      lVar2 = __ftol();
      lVar3 = __ftol();
      uVar1 = (uint)((ulonglong)lVar3 >> 0x20);
      if ((int)lVar2 == (int)lVar3) {
        return (ulonglong)uVar1 << 0x20;
      }
    }
  }
  return CONCAT44(uVar1,1);
}


/* 0043eda0 size=231 */

bool __cdecl FUN_0043eda0(int param_1,int param_2,uint *param_3)

{
  longlong lVar1;
  longlong lVar2;
  
  *param_3 = 0;
  if ((*(int *)(param_1 + 0x34) != *(int *)(param_2 + 4)) ||
     (*(int *)(param_1 + 0x38) != *(int *)(param_2 + 8))) {
    *param_3 = 1;
  }
  lVar1 = __ftol();
  if (*(uint *)(param_1 + 0x3c) >> 3 != (uint)lVar1) {
    *param_3 = *param_3 | 2;
  }
  lVar1 = __ftol();
  lVar2 = __ftol();
  if ((int)lVar1 != (int)lVar2) {
    *param_3 = *param_3 | 4;
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    lVar1 = FUN_0043ed30();
    if ((int)lVar1 != 0) {
      *param_3 = *param_3 | 8;
    }
    lVar1 = FUN_0043ed30();
    if ((int)lVar1 != 0) {
      *param_3 = *param_3 | 0x10;
    }
    lVar1 = __ftol();
    lVar2 = __ftol();
    if ((int)lVar1 != (int)lVar2) {
      *param_3 = *param_3 | 0x20;
    }
  }
  return *param_3 != 0;
}


/* 0043ee90 size=168 */

byte __cdecl FUN_0043ee90(int *param_1,float *param_2,float param_3)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  float fVar4;
  float *pfVar5;
  
  piVar2 = (int *)*param_1;
  bVar1 = *(byte *)((int)piVar2 + 0x16);
  do {
    if ((bVar1 & 3) != 0) {
      return *(byte *)(*param_1 + 0x16) & 1;
    }
    iVar3 = *piVar2;
    if ((iVar3 == 0) || (*(int *)(iVar3 + 0x2c) == 0)) {
      pfVar5 = (float *)0x0;
    }
    else {
      pfVar5 = *(float **)(iVar3 + 0x28);
    }
    fVar4 = (*param_2 * *pfVar5 + param_2[1] * pfVar5[1] + param_2[2] * pfVar5[2]) - pfVar5[3];
    if (fVar4 <= param_3) {
      if (-param_3 <= fVar4) {
        return 2;
      }
      *param_1 = piVar2[1];
    }
    else {
      *param_1 = piVar2[2];
    }
    piVar2 = (int *)*param_1;
    bVar1 = *(byte *)((int)piVar2 + 0x16);
  } while( true );
}


/* 0043ef40 size=145 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0043ef40(int *param_1,float *param_2)

{
  byte bVar1;
  int iVar2;
  float *pfVar3;
  
  bVar1 = *(byte *)((int)param_1 + 0x16);
  while( true ) {
    if ((bVar1 & 2) != 0) {
      return 0;
    }
    if ((bVar1 & 1) != 0) break;
    iVar2 = *param_1;
    if ((iVar2 == 0) || (*(int *)(iVar2 + 0x2c) == 0)) {
      pfVar3 = (float *)0x0;
    }
    else {
      pfVar3 = *(float **)(iVar2 + 0x28);
    }
    param_1 = (int *)param_1[(_DAT_004cbea0 <
                             (*param_2 * *pfVar3 + param_2[1] * pfVar3[1] + param_2[2] * pfVar3[2])
                             - pfVar3[3]) + 1];
    bVar1 = *(byte *)((int)param_1 + 0x16);
  }
  return 1;
}


/* 0043f0e0 size=69 */

undefined4 __cdecl FUN_0043f0e0(int *param_1,undefined4 *param_2)

{
  undefined4 unaff_ESI;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_10 = *param_2;
  local_c = param_2[1];
  local_4 = 1;
  local_8 = param_2[2];
  (**(code **)(*param_1 + 0xc))(param_2,&LAB_0043efe0,&local_10,0);
  return unaff_ESI;
}


/* 0043f150 size=368 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0043f150: lifted from original x86 -> lt_lifted.c */


/* 0043f2c0 size=133 */

void __cdecl FUN_0043f2c0(undefined2 *param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  
  lVar1 = __ftol();
  lVar2 = __ftol();
  lVar3 = __ftol();
  param_1[1] = (short)lVar2;
  param_1[2] = (short)lVar3;
  *param_1 = (short)lVar1;
  *(byte *)(param_1 + 3) =
       (byte)((ulonglong)lVar3 >> 0x10) | (byte)((ulonglong)lVar2 >> 0x10) |
       (byte)((ulonglong)lVar1 >> 0x10);
  return;
}


/* 0043f350 size=48 */

void __cdecl FUN_0043f350(int *param_1,undefined2 *param_2)

{
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  
  (**(code **)(*param_1 + 0x48))(*param_2);
  (**(code **)(*param_1 + 0x48))(CONCAT22(extraout_var,param_2[1]));
  (**(code **)(*param_1 + 0x48))(CONCAT22(extraout_var_00,param_2[2]));
  return;
}


/* 0043f380 size=42 */

void __cdecl FUN_0043f380(int *param_1)

{
  undefined2 local_8 [4];
  
  FUN_0043f2c0(local_8);
  FUN_0043f350(param_1,local_8);
  return;
}


/* 0043f3b0 size=261 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0043f3b0(int *param_1,undefined4 *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ushort unaff_retaddr;
  float *pfStack_4;
  
  iVar4 = param_3;
  piVar3 = param_1;
  if (param_3 == 0) {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = 0;
      param_2[1] = 0;
      param_2[2] = 0;
      return;
    }
  }
  else {
    (**(code **)(*param_1 + 0xc))(&param_3);
    uVar5 = (uint)param_2 & 0xffff;
    (**(code **)(*piVar3 + 0xc))(&param_2);
    uVar6 = (uint)param_1 & 0xffff;
    (**(code **)(*piVar3 + 0xc))(&param_1);
    fVar1 = (float)uVar6 * _DAT_004cc534;
    fVar2 = (float)unaff_retaddr * _DAT_004cc534;
    *pfStack_4 = (*(float *)(iVar4 + 0x150) - *(float *)(iVar4 + 0x144)) *
                 (float)uVar5 * _DAT_004cc534 + *(float *)(iVar4 + 0x144);
    pfStack_4[1] = (*(float *)(iVar4 + 0x154) - *(float *)(iVar4 + 0x148)) * fVar1 +
                   *(float *)(iVar4 + 0x148);
    pfStack_4[2] = (*(float *)(iVar4 + 0x158) - *(float *)(iVar4 + 0x14c)) * fVar2 +
                   *(float *)(iVar4 + 0x14c);
  }
  return;
}


/* 0043f4c0 size=590 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0043f4c0(float *param_1,char *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  char cVar6;
  longlong lVar7;
  longlong lVar8;
  float local_40;
  float local_3c;
  float local_2c;
  float local_1c;
  
  FUN_0044e720(param_1,&local_40);
  lVar7 = __ftol();
  cVar5 = (char)lVar7;
  *param_2 = cVar5;
  lVar7 = __ftol();
  cVar6 = (char)lVar7;
  param_2[1] = cVar6;
  lVar7 = __ftol();
  param_2[2] = (char)lVar7;
  lVar8 = __ftol();
  param_2[3] = (char)lVar8;
  lVar8 = __ftol();
  param_2[4] = (char)lVar8;
  lVar8 = __ftol();
  fVar2 = (float)(int)cVar6 * _DAT_004cc544;
  param_2[5] = (char)lVar8;
  fVar2 = fVar2 - _DAT_004cba94;
  fVar1 = (float)(int)cVar5 * _DAT_004cc544 - _DAT_004cba94;
  fVar4 = (float)(int)(char)lVar7 * _DAT_004cbb18;
  fVar3 = -((fVar1 * (fVar1 + _DAT_004cc540) + fVar2 * fVar2 + fVar4 * fVar4) /
           (fVar1 * fVar1 + fVar2 * fVar2 + fVar4 * fVar4));
  fVar2 = fVar2 * fVar3 + fVar2;
  fVar1 = fVar3 * fVar1 + fVar1 + _DAT_004cc540;
  fVar4 = fVar4 * fVar3 + fVar4;
  fVar3 = fVar2 * fVar2 + fVar1 * fVar1 + fVar4 * fVar4;
  if (fVar3 <= _DAT_004cbeec) {
    return;
  }
  fVar3 = _DAT_004cba94 / SQRT(fVar3);
  fVar1 = fVar3 * fVar2 * local_3c + fVar3 * fVar1 * local_2c + fVar3 * fVar4 * local_1c;
  if (fVar1 <= _DAT_004cc53c) {
    if (_DAT_004cc538 <= fVar1) {
      return;
    }
    if (cVar6 == '\0') {
      param_2[1] = -1;
    }
    else {
      param_2[1] = -cVar6;
    }
  }
  if (cVar5 == '\0') {
    *param_2 = -1;
    return;
  }
  *param_2 = -cVar5;
  return;
}


/* 0043f710 size=83 */

void __cdecl FUN_0043f710(int *param_1,char *param_2)

{
  (**(code **)(*param_1 + 0x44))(*param_2);
  (**(code **)(*param_1 + 0x44))(param_2[1]);
  (**(code **)(*param_1 + 0x44))(param_2[2]);
  if (-1 < *param_2) {
    (**(code **)(*param_1 + 0x44))(param_2[3]);
    (**(code **)(*param_1 + 0x44))(param_2[4]);
    (**(code **)(*param_1 + 0x44))(param_2[5]);
  }
  return;
}


/* 0043f770 size=37 */

void __cdecl FUN_0043f770(int *param_1,float *param_2)

{
  char local_8 [8];
  
  FUN_0043f4c0(param_2,local_8);
  FUN_0043f710(param_1,local_8);
  return;
}


/* 0043f7a0 size=1016 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0043f7a0(int *param_1)

{
  char cVar1;
  float fVar2;
  float *pfVar3;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  bool bVar4;
  float10 fVar5;
  float10 fVar6;
  undefined4 uStack_84;
  char cVar7;
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float afStack_4c [18];
  float *pfStack_4;
  
  uStack_84 = (int)&uStack_74 + 1;
  (**(code **)(*param_1 + 8))();
  (**(code **)(*param_1 + 8))((int)afStack_4c + -0x2d);
  cVar1 = (char)((uint)unaff_ESI >> 0x18);
  (*(uint16_t*)((char*)&uStack_78+0)) = CONCAT11(cVar1,(undefined1)uStack_78);
  (**(code **)(*param_1 + 8))(afStack_4c + -0xc);
  cVar7 = (char)((uint)unaff_ESI >> 8);
  if (cVar7 < '\0') {
    bVar4 = -1 < uStack_84;
    if (bVar4) {
      cVar1 = (char)((uint)unaff_EBX >> 8);
    }
    else {
      cVar1 = -(*(uint8_t*)((char*)&uStack_84+3));
    }
    fStack_70 = (float)(int)cVar1 * _DAT_004cc544 - _DAT_004cba94;
    fStack_60 = (float)(int)-cVar7 * _DAT_004cc544 - _DAT_004cba94;
    fStack_68 = (float)(int)(char)unaff_ESI * _DAT_004cbb18;
    fStack_6c = fStack_60 + _DAT_004cc540;
    fStack_64 = fStack_70;
    fStack_5c = fStack_68;
    fVar5 = FUN_0041feb0(&fStack_64,fStack_70,fStack_6c,fStack_68);
    fVar6 = FUN_0043a41f(&fStack_64);
    fVar2 = (float)-((float10)(float)fVar5 / fVar6);
    pfVar3 = (float *)FUN_0041ff50(&fStack_64,afStack_4c + -0xc,fVar2);
    FUN_0041ff80(&fStack_70,*pfVar3,pfVar3[1],pfVar3[2]);
    fVar5 = FUN_0041fe80(&fStack_70);
    if (fVar5 != (float10)_DAT_004cb524) {
      fVar5 = (float10)_DAT_004cba94 / fVar5;
      fStack_70 = (float)(fVar5 * (float10)fStack_70);
      fStack_6c = (float)(fVar5 * (float10)fStack_6c);
      fStack_68 = (float)(fVar5 * (float10)fStack_68);
    }
    fVar5 = FUN_0041fe80(&fStack_64);
    if (fVar5 != (float10)_DAT_004cb524) {
      fVar5 = (float10)_DAT_004cba94 / fVar5;
      fStack_64 = (float)(fVar5 * (float10)fStack_64);
      fStack_60 = (float)(fVar5 * (float10)fStack_60);
      fStack_5c = (float)(fVar5 * (float10)fStack_5c);
    }
    if (!bVar4) {
      FUN_00413050(afStack_4c + -0xc,-fStack_70,-fStack_6c,-fStack_68);
      fStack_6c = uStack_78;
      fStack_68 = uStack_74;
      fStack_70 = fVar2;
    }
  }
  else {
    (**(code **)(*param_1 + 8))((int)afStack_4c + -0x33);
    (**(code **)(*param_1 + 8))((int)&uStack_84 + 2);
    (**(code **)(*param_1 + 8))((int)afStack_4c + -0x39);
    fStack_60 = (float)(int)cVar7 * _DAT_004cc544 - _DAT_004cba94;
    fVar2 = (float)(int)cVar1;
    fStack_64 = (float)(int)(*(uint8_t*)((char*)&uStack_84+3)) * _DAT_004cc544 - _DAT_004cba94;
    fStack_5c = (float)(int)(char)unaff_ESI * _DAT_004cbb18;
    fStack_6c = (float)(int)(char)((uint)unaff_ESI >> 0x10) * _DAT_004cbb18;
    fStack_68 = (float)(int)fVar2 * _DAT_004cbb18;
    fStack_70 = (float)(int)cVar7 * _DAT_004cbb18;
  }
  FUN_00413050(afStack_4c + -0xc,fStack_6c * fStack_5c - fStack_68 * fStack_60,
               fStack_68 * fStack_64 - fStack_70 * fStack_5c,
               fStack_70 * fStack_60 - fStack_6c * fStack_64);
  fStack_54 = uStack_78;
  fStack_50 = uStack_74;
  fStack_58 = fVar2;
  pfVar3 = (float *)FUN_00440190(&fStack_70,afStack_4c + -0xc,fVar2,uStack_78,uStack_74);
  fStack_64 = *pfVar3;
  fStack_60 = pfVar3[1];
  fStack_5c = pfVar3[2];
  fVar5 = FUN_0041fe80(&fStack_58);
  if (fVar5 != (float10)_DAT_004cb524) {
    fVar5 = (float10)_DAT_004cba94 / fVar5;
    fStack_58 = (float)((float10)fStack_58 * fVar5);
    fStack_54 = (float)((float10)fStack_54 * fVar5);
    fStack_50 = (float)((float10)fStack_50 * fVar5);
  }
  FUN_00420000(&fStack_64,1.0);
  pfVar3 = (float *)FUN_00440190(&fStack_58,afStack_4c + -0xc,fStack_64,fStack_60,fStack_5c);
  fStack_70 = *pfVar3;
  fStack_6c = pfVar3[1];
  fStack_68 = pfVar3[2];
  FUN_0043fba0(afStack_4c,&fStack_58,&fStack_70,&fStack_64);
  FUN_0044e8c0(pfStack_4,afStack_4c);
  return;
}


/* 0043fba0 size=100 */

void __thiscall FUN_0043fba0(void *this,undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  uVar1 = param_3[2];
  uVar2 = param_2[2];
  uVar3 = param_1[2];
  uVar4 = param_3[1];
  uVar5 = param_2[1];
  uVar6 = param_1[1];
  uVar7 = *param_3;
  uVar8 = *param_1;
  uVar9 = *param_2;
  *(undefined4 *)((int)this + 0x3c) = 0x3f800000;
  *(undefined4 *)this = uVar8;
  *(undefined4 *)((int)this + 8) = uVar7;
  *(undefined4 *)((int)this + 4) = uVar9;
  *(undefined4 *)((int)this + 0x10) = uVar6;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x14) = uVar5;
  *(undefined4 *)((int)this + 0x2c) = 0;
  *(undefined4 *)((int)this + 0x30) = 0;
  *(undefined4 *)((int)this + 0x18) = uVar4;
  *(undefined4 *)((int)this + 0x34) = 0;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x20) = uVar3;
  *(undefined4 *)((int)this + 0x24) = uVar2;
  *(undefined4 *)((int)this + 0x28) = uVar1;
  return;
}


/* 0043fc10 size=219 */

void __cdecl FUN_0043fc10(int param_1,float *param_2)

{
  longlong lVar1;
  float local_40 [2];
  float local_38;
  float local_18;
  
  FUN_0044e720(param_2,local_40);
  fpatan((float10)local_38,(float10)local_18);
  lVar1 = __ftol();
  if ((uint)*(ushort *)(param_1 + 0x36) <= *(ushort *)(param_1 + 0x38) + 1) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | 4;
    return;
  }
  if (*(uint *)(param_1 + 0x58) <= *(ushort *)(param_1 + 0x34) + 1) {
    do {
      param_2 = (float *)((uint)param_2 & 0xffffff00);
      FUN_00414b10((void *)(param_1 + 0x50),*(undefined1 **)(param_1 + 0x58),(undefined1 *)&param_2,
                   &DAT_004ecc58);
    } while (*(uint *)(param_1 + 0x58) <= *(ushort *)(param_1 + 0x34) + 1);
  }
  *(char *)(*(int *)(param_1 + 0x54) + (uint)*(ushort *)(param_1 + 0x38)) = (char)lVar1;
  *(short *)(param_1 + 0x38) = *(short *)(param_1 + 0x38) + 1;
  *(short *)(param_1 + 0x34) = *(short *)(param_1 + 0x34) + 1;
  return;
}


/* 0043fcf0 size=163 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0043fcf0(uint param_1,float *param_2)

{
  uint uVar1;
  byte bVar2;
  ushort uVar3;
  
  uVar3 = *(ushort *)(param_1 + 0x38);
  uVar1 = uVar3 + 1;
  if ((uVar1 < *(uint *)(param_1 + 0x58)) && (uVar1 <= *(ushort *)(param_1 + 0x34))) {
    bVar2 = *(byte *)(*(int *)(param_1 + 0x54) + (uint)uVar3);
    *(ushort *)(param_1 + 0x38) = uVar3 + 1;
    param_1 = (uint)bVar2;
  }
  else {
    *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | 2;
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
    }
  }
  FUN_0043ced0(0.0,(float)(int)(char)param_1 * _DAT_004cbb18 * _DAT_004cc4c4,0.0,param_2);
  return;
}


/* 0043fec0 size=53 */

uint __cdecl FUN_0043fec0(uint param_1,void *param_2)

{
  int iVar1;
  
  if ((param_1 != 0) && (*(char *)(param_1 + 0xbc) == '\x01')) {
    iVar1 = FUN_00451250(*(void **)(param_1 + 0x1f8),param_2,&param_1,(int *)0x0);
    if (iVar1 != 0) {
      return param_1;
    }
  }
  return 0xffffffff;
}


/* 0043ff40 size=16 */

void __cdecl FUN_0043ff40(int *param_1)

{
  if (param_1 != (int *)0x0) {
    FUN_0049b820(param_1);
  }
  return;
}


/* 0043ff50 size=423 */

int * __cdecl FUN_0043ff50(undefined4 *param_1,int param_2,char *param_3)

{
  byte bVar1;
  void *this;
  int iVar2;
  int *piVar3;
  void *extraout_ECX;
  uint uVar4;
  uint uVar5;
  void *extraout_ECX_00;
  int *piVar6;
  byte *pbVar7;
  byte *pbVar8;
  int local_218;
  uint local_210;
  byte local_20c [264];
  undefined4 local_104;
  byte local_100 [256];
  
  piVar6 = (int *)0x0;
  if (param_2 < 1) {
    return (int *)0x0;
  }
  local_218 = param_2;
  do {
    local_104 = 0;
    iVar2 = de_file_427f40((int *)*param_1,param_3,&local_210);
    this = extraout_ECX;
    while (iVar2 != 0) {
      iVar2 = FUN_00440100(this,(int)piVar6,local_20c);
      piVar3 = piVar6;
      if (iVar2 == 0) {
        if (*param_3 == '\0') {
          uVar4 = 0xffffffff;
          pbVar7 = local_20c;
          do {
            pbVar8 = pbVar7;
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            pbVar8 = pbVar7 + 1;
            bVar1 = *pbVar7;
            pbVar7 = pbVar8;
          } while (bVar1 != 0);
          uVar4 = ~uVar4;
          pbVar7 = pbVar8 + -uVar4;
          pbVar8 = local_100;
          for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined4 *)pbVar8 = *(undefined4 *)pbVar7;
            pbVar7 = pbVar7 + 4;
            pbVar8 = pbVar8 + 4;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *pbVar8 = *pbVar7;
            pbVar7 = pbVar7 + 1;
            pbVar8 = pbVar8 + 1;
          }
        }
        else {
          FUN_004b9f62(local_100,(byte *)s__s__s_004d7a34,param_3);
        }
        uVar4 = 0xffffffff;
        pbVar7 = local_100;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          bVar1 = *pbVar7;
          pbVar7 = pbVar7 + 1;
        } while (bVar1 != 0);
        uVar5 = 0xffffffff;
        pbVar7 = local_20c;
        do {
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          bVar1 = *pbVar7;
          pbVar7 = pbVar7 + 1;
        } while (bVar1 != 0);
        piVar3 = FUN_00430f00(~uVar4 + ~uVar5 + 0x13);
        uVar4 = 0xffffffff;
        piVar3[1] = (int)(piVar3 + 4);
        pbVar7 = local_20c;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          bVar1 = *pbVar7;
          pbVar7 = pbVar7 + 1;
        } while (bVar1 != 0);
        uVar5 = 0xffffffff;
        piVar3[2] = ~uVar4 + 0x10 + (int)piVar3;
        pbVar7 = local_20c;
        do {
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          bVar1 = *pbVar7;
          pbVar7 = pbVar7 + 1;
        } while (bVar1 != 0);
        pbVar7 = local_20c;
        pbVar8 = (byte *)(piVar3 + 4);
        for (uVar4 = ~uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(int *)pbVar8 = *(int *)pbVar7;
          pbVar7 = pbVar7 + 4;
          pbVar8 = pbVar8 + 4;
        }
        for (uVar4 = ~uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pbVar8 = *pbVar7;
          pbVar7 = pbVar7 + 1;
          pbVar8 = pbVar8 + 1;
        }
        uVar4 = 0xffffffff;
        pbVar7 = local_100;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          bVar1 = *pbVar7;
          pbVar7 = pbVar7 + 1;
        } while (bVar1 != 0);
        pbVar7 = local_100;
        pbVar8 = (byte *)piVar3[2];
        for (uVar5 = ~uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pbVar8 = *(undefined4 *)pbVar7;
          pbVar7 = pbVar7 + 4;
          pbVar8 = pbVar8 + 4;
        }
        for (uVar4 = ~uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pbVar8 = *pbVar7;
          pbVar7 = pbVar7 + 1;
          pbVar8 = pbVar8 + 1;
        }
        piVar3[3] = (int)piVar6;
        *piVar3 = 2 - (uint)(local_210 != 0);
      }
      iVar2 = de_file_427f40((int *)*param_1,param_3,&local_210);
      this = extraout_ECX_00;
      piVar6 = piVar3;
    }
    param_1 = param_1 + 1;
    local_218 = local_218 + -1;
    if (local_218 == 0) {
      return piVar6;
    }
  } while( true );
}


