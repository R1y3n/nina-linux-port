/* lithtech.exe decompilation - unnamed_00478000 */
#include "ghidra_types.h"

/* 00478310 size=113 */

void __cdecl FUN_00478310(byte *param_1,int param_2)

{
  if (((*param_1 & 1) != 0) || (*(short *)(param_1 + 2) != *(short *)(param_2 + 2))) {
    *param_1 = *param_1 | 1;
    *(undefined2 *)(param_1 + 2) = *(undefined2 *)(param_2 + 2);
  }
  if (((*param_1 & 2) != 0) || (param_1[4] != *(byte *)(param_2 + 4))) {
    *param_1 = *param_1 | 2;
    param_1[4] = *(byte *)(param_2 + 4);
  }
  if ((((*param_1 & 4) != 0) || (*(short *)(param_1 + 6) != *(short *)(param_2 + 6))) ||
     (param_1[8] != *(byte *)(param_2 + 8))) {
    *param_1 = *param_1 | 4;
    *(undefined2 *)(param_1 + 6) = *(undefined2 *)(param_2 + 6);
    param_1[8] = *(byte *)(param_2 + 8);
  }
  return;
}


/* 00478390 size=29 */

void __cdecl FUN_00478390(undefined4 param_1,int *param_2,int param_3,void *param_4)

{
  if (*param_2 == 0) {
    FUN_004783b0((uint)param_2,param_3,param_4);
  }
  return;
}


/* 004783b0 size=1472 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004783b0: lifted from original x86 -> lt_lifted.c */


/* 00478970 size=244 */

/* FUN_00478970: lifted from original x86 -> lt_lifted.c */


/* 00478a70 size=97 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00478a70(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_004eabc4;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _DAT_004eabdc = &LAB_00478e90;
  _DAT_004eabe0 = &LAB_00478c00;
  _DAT_004eabe4 = FUN_00478ae0;
  _DAT_004eabec = &LAB_00478eb0;
  _DAT_004eabf0 = FUN_00478f10;
  _DAT_004eabe8 = &LAB_00478f90;
  _DAT_004eabd8 = FUN_00479030;
  _DAT_004eabf8 = &LAB_00478ee0;
  return;
}


/* 00478ae0 size=275 */

undefined4 __cdecl FUN_00478ae0(int param_1,int param_2,uint param_3)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  uint uVar5;
  ushort uVar6;
  uint uVar7;
  
  if (param_3 == 0) {
    return 0;
  }
  uVar6 = *(ushort *)(param_2 + 0x38);
  uVar3 = (uint)*(ushort *)(param_2 + 0x34);
  uVar5 = (uint)uVar6;
  if (uVar3 != uVar5) {
    uVar7 = param_3;
    do {
      if ((uVar5 + 2 < *(uint *)(param_2 + 0x58)) && (uVar5 + 2 <= uVar3)) {
        uVar7 = CONCAT22((short)(uVar7 >> 0x10),*(undefined2 *)(*(int *)(param_2 + 0x54) + uVar5));
        *(ushort *)(param_2 + 0x38) = uVar6 + 2;
      }
      else {
        *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      pcVar4 = (char *)FUN_0047a0c0(param_1,uVar7);
      if ((((pcVar4 != (char *)0x0) && (*pcVar4 == '\x02')) &&
          (iVar2 = *(int *)(pcVar4 + 4), iVar2 != 0)) &&
         (((pbVar1 = (byte *)(*(int *)(param_3 + 400) + 2 + (uVar7 & 0xffff) * 4),
           (*pbVar1 & 1) == 0 && ((*(uint *)(iVar2 + 0x34) & 0x428) != 0)) &&
          ((*(uint *)(iVar2 + 0x34) & 4) == 0)))) {
        *pbVar1 = *pbVar1 | 1;
        if (*(int *)(iVar2 + 0x28) != 0) {
          *(int *)(iVar2 + 0x28) = *(int *)(iVar2 + 0x28) + -1;
        }
        if (*(int *)(iVar2 + 0x28) == 0) {
          *(undefined4 *)(iVar2 + 0x20) = 0;
        }
      }
      uVar6 = *(ushort *)(param_2 + 0x38);
      uVar3 = (uint)*(ushort *)(param_2 + 0x34);
      uVar5 = (uint)uVar6;
    } while (uVar3 != uVar5);
  }
  return 0;
}


/* 00478f10 size=120 */

undefined4 __cdecl FUN_00478f10(void *param_1,int param_2,int param_3)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  
  iVar3 = param_3;
  if ((param_3 == 0) || (*(int *)((int)param_1 + 0xa30) == 0)) {
    return 0;
  }
  FUN_0048a370(param_1,param_2);
  uVar2 = *(ushort *)(param_2 + 0x34);
  if ((uint)uVar2 == (uint)*(ushort *)(param_2 + 0x38)) {
    param_3 = 0;
  }
  else {
    bVar1 = *(byte *)(*(int *)(param_2 + 0x54) + -1 + (uint)uVar2);
    *(ushort *)(param_2 + 0x34) = uVar2 - 1;
    param_3 = (int)bVar1;
  }
  (**(code **)(**(int **)((int)param_1 + 0xa30) + 0x2c))(iVar3,param_3,param_2 + 8);
  return 0;
}


/* 00479030 size=189 */

undefined4 __cdecl FUN_00479030(undefined4 param_1,void *param_2,int param_3)

{
  ushort uVar1;
  ushort uVar2;
  void *this;
  uint uVar3;
  undefined4 *puVar4;
  undefined2 extraout_var;
  
  this = param_2;
  uVar1 = *(ushort *)((int)param_2 + 0x38);
  uVar3 = uVar1 + 2;
  if ((uVar3 < *(uint *)((int)param_2 + 0x58)) && (uVar3 <= *(ushort *)((int)param_2 + 0x34))) {
    uVar2 = *(ushort *)(*(int *)((int)param_2 + 0x54) + (uint)uVar1);
    *(ushort *)((int)param_2 + 0x38) = uVar1 + 2;
    param_2 = (void *)(uint)uVar2;
  }
  else {
    *(uint *)((int)param_2 + 0x40) = *(uint *)((int)param_2 + 0x40) | 2;
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
    }
  }
  uVar3 = (uint)param_2 & 0xffff;
  *(uint *)(param_3 + 0x114) = uVar3;
  if (uVar3 != 0) {
    puVar4 = (undefined4 *)FUN_00430de0(uVar3);
    *(undefined4 **)(param_3 + 0x110) = puVar4;
    FUN_0046b3c0(this,puVar4,CONCAT22(extraout_var,*(undefined2 *)(param_3 + 0x114)));
  }
  *(uint *)(param_3 + 0x3c0) = *(uint *)(param_3 + 0x3c0) | 0x100;
  return 0;
}


/* 00479120 size=72 */

undefined4 __cdecl FUN_00479120(int param_1,int *param_2)

{
  if ((*(int *)(param_2[100] + 0x2c) == 0) &&
     (((param_2[0x22] & 0x21213001U) == 0 || ((param_2[0x22] & 0x10000000U) != 0)))) {
    (**(code **)(*param_2 + 8))();
  }
  else if (param_2[0x16] == -1) {
    FUN_004a3df0((void *)(param_1 + 0x210),param_2);
    return 0;
  }
  return 0;
}


/* 00479170 size=284 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl FUN_00479170(undefined4 param_1,int param_2)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  
  uVar3 = 0x201;
  if ((((*(float *)(param_2 + 0x9c) != _DAT_004cb524) ||
       (*(float *)(param_2 + 0xa0) != _DAT_004cb524)) ||
      (*(float *)(param_2 + 0xa4) != _DAT_004cb524)) || (*(int *)(param_2 + 0xa8) != 0x3f800000)) {
    uVar3 = 0x601;
  }
  if (((*(uint *)(param_2 + 0x88) & 0x4ffff) != 0) || (*(int *)(param_2 + 0x90) != 0)) {
    uVar3 = uVar3 | 8;
  }
  if (((*(int *)(param_2 + 0xac) != 0x3f800000) || (*(int *)(param_2 + 0xb0) != 0x3f800000)) ||
     (*(int *)(param_2 + 0xb4) != 0x3f800000)) {
    uVar3 = uVar3 | 0x10;
  }
  cVar1 = *(char *)(param_2 + 0xbc);
  if (cVar1 == '\x03') {
    if (((*(char *)(param_2 + 0x94) == -1) && (*(char *)(param_2 + 0x95) == -1)) &&
       (*(char *)(param_2 + 0x96) == -1)) {
      cVar2 = *(char *)(param_2 + 0x97);
joined_r0x00479250:
      if (cVar2 == -1) goto LAB_00479255;
    }
  }
  else if (((*(char *)(param_2 + 0x94) == '\0') && (*(char *)(param_2 + 0x95) == '\0')) &&
          (*(char *)(param_2 + 0x96) == '\0')) {
    cVar2 = *(char *)(param_2 + 0x97);
    goto joined_r0x00479250;
  }
  uVar3 = uVar3 | 0x40;
LAB_00479255:
  if (cVar1 == '\x01') {
    uVar3 = uVar3 | 0x20;
  }
  if (((*(int *)(param_2 + 0x98) != 0) || ((cVar1 == '\x01' && (*(int *)(param_2 + 0x24c) != 0))))
     || ((*(uint *)(param_2 + 0x124) & 0x400) != 0)) {
    uVar3 = uVar3 | 0x100;
  }
  return uVar3;
}


/* 00479290 size=300 */

void __cdecl FUN_00479290(int param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = param_1;
  param_1 = FUN_00434ff0(*(int *)(param_1 + 0xb28));
  while (param_1 != 0) {
    iVar1 = FUN_00435040(&param_1);
    iVar1 = FUN_00434fd0(iVar1);
    *(int *)(iVar1 + 0x20c) = *(int *)(iVar1 + 0x20c) + 1;
  }
  param_1 = FUN_00434ff0(*(int *)(iVar5 + 0xb28));
  while (param_1 != 0) {
    piVar2 = (int *)FUN_00435040(&param_1);
    puVar3 = (undefined4 *)FUN_00434fd0((int)piVar2);
    if (puVar3[0x83] != 0) {
      puVar3[0x83] = puVar3[0x83] + -1;
    }
    if (puVar3[0x83] == 0) {
      if (2 < DAT_004e4420) {
        uVar4 = FUN_00468720((int)puVar3);
        FUN_00436670((byte *)s_Removing_model_from_resource_lis_004dbb14,uVar4);
      }
      FUN_00434e60(*(int **)(iVar5 + 0xb28),piVar2);
      if (puVar3 != (undefined4 *)0x0) {
        (**(code **)*puVar3)(1);
      }
    }
  }
  param_1 = FUN_00434ff0(*(int *)(iVar5 + 0xb28));
  while (param_1 != 0) {
    iVar5 = FUN_00435040(&param_1);
    iVar5 = FUN_00434fd0(iVar5);
    if (2 < DAT_004e4420) {
      uVar4 = FUN_00468720(iVar5);
      FUN_00436670((byte *)s_Warning__Server_unable_to_unload_004dbad0,uVar4);
    }
  }
  return;
}


/* 004793c0 size=1032 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_004793c0(int param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  int iVar11;
  float10 fVar12;
  longlong lVar13;
  int local_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float afStack_2c [3];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint uStack_8;
  int iStack_4;
  
  if (*(char *)(param_2 + 0xbc) == '\x01') {
    lVar13 = __ftol();
    if ((int)lVar13 != 0) {
      for (uVar4 = *(uint *)(param_2 + 0x220); uVar4 != 0; uVar4 = *(uint *)(uVar4 + 4)) {
        *(undefined1 **)(uVar4 + 0xc) = &LAB_004798e0;
        FUN_004010f0(uVar4,(int)lVar13);
      }
    }
  }
  iVar5 = *(int *)(param_2 + 400);
  if ((_DAT_004cb524 < *(float *)(iVar5 + 0x10)) &&
     (*(float *)(iVar5 + 0x10) = *(float *)(iVar5 + 0x10) - *(float *)(param_1 + 0x8bc),
     *(float *)(*(int *)(param_2 + 400) + 0x10) <= _DAT_004cb524)) {
    *(undefined4 *)(param_2 + 0xd0) = 0;
    *(undefined4 *)(param_2 + 0xd4) = 0;
    *(undefined4 *)(param_2 + 0xd8) = 0;
    (**(code **)(**(int **)(*(int *)(param_2 + 400) + 0x20) + 4))(2,0,0);
    if ((*(byte *)(param_2 + 0x124) & 4) == 0) {
      return;
    }
  }
  puVar2 = (undefined4 *)(param_2 + 0xd0);
  local_38 = *(undefined4 *)(param_2 + 0x194);
  local_34 = *(undefined4 *)(param_2 + 0x198);
  local_50 = *puVar2;
  local_30 = *(undefined4 *)(param_2 + 0x19c);
  uVar6 = *(undefined4 *)(param_1 + 0x8bc);
  local_4c = *(undefined4 *)(param_2 + 0xd4);
  uStack_48 = *(undefined4 *)(param_2 + 0xd8);
  FUN_004798d0(&uStack_20);
  if ((*(byte *)(param_2 + 0x124) & 0x40) != 0) {
    piVar3 = (int *)(param_1 + 0x874);
    *(undefined4 *)(param_1 + 0x878) = uVar6;
    *piVar3 = param_2;
    if (((*(uint *)(param_2 + 0x88) & 0x20000000) == 0) &&
       (iVar5 = *(int *)(param_2 + 400), *(int *)(iVar5 + 4) != iVar5)) {
      uStack_20 = *puVar2;
      uStack_1c = *(undefined4 *)(param_2 + 0xd4);
      uStack_18 = *(undefined4 *)(param_2 + 0xd8);
      uStack_14 = *(undefined4 *)(param_2 + 0xc4);
      uStack_10 = *(undefined4 *)(param_2 + 200);
      iVar11 = 0;
      uStack_c = *(undefined4 *)(param_2 + 0xcc);
      iVar7 = *(int *)(iVar5 + 4);
      uStack_8 = *(uint *)(param_2 + 0x88);
      iStack_4 = param_2;
      while (iVar7 != iVar5) {
        piVar1 = (int *)(iVar7 + 8);
        iVar7 = *(int *)(iVar7 + 4);
        if ((*(int *)*piVar1 == 1) &&
           (iVar8 = ((int *)*piVar1)[1], (*(uint *)(iVar8 + 0x88) & 0x20000000) != 0)) {
          (**(code **)(**(int **)(*(int *)(iVar8 + 400) + 0x20) + 4))(9,&uStack_20,0);
          iVar11 = iVar11 + 1;
        }
      }
      *(undefined4 **)(param_1 + 0x880) = &uStack_14;
      *(undefined4 **)(param_1 + 0x884) = &uStack_20;
      *(uint *)(param_1 + 0x87c) = uStack_8;
      local_60 = FUN_0045df70(piVar3);
      (**(code **)(**(int **)(*(int *)(param_2 + 400) + 0x20) + 4))(9,(float *)(param_1 + 0x8a8),0);
      fStack_5c = *(float *)(param_1 + 0x8a8);
      fStack_58 = *(float *)(param_1 + 0x8ac);
      fStack_54 = *(float *)(param_1 + 0x8b0);
      if (iVar11 != 0) {
        *(uint *)(param_2 + 0x124) = *(uint *)(param_2 + 0x124) | 0x40;
      }
    }
    else {
      *(undefined4 **)(param_1 + 0x884) = puVar2;
      *(int *)(param_1 + 0x880) = param_2 + 0xc4;
      *(undefined4 *)(param_1 + 0x87c) = *(undefined4 *)(param_2 + 0x88);
      local_60 = FUN_0045df70(piVar3);
      if ((*(uint *)(param_2 + 0x88) & 0x20000000) == 0) {
        (**(code **)(**(int **)(*(int *)(param_2 + 400) + 0x20) + 4))(9,param_1 + 0x8a8,0);
      }
      fStack_5c = *(float *)(param_1 + 0x8a8);
      fStack_58 = *(float *)(param_1 + 0x8ac);
      fStack_54 = *(float *)(param_1 + 0x8b0);
    }
    if (local_60 != 0) {
      fVar12 = FUN_0043a41f(&fStack_5c);
      if ((float10)_DAT_004cbaec < fVar12) {
        pfVar10 = (float *)(param_2 + 0x194);
        pfVar9 = (float *)FUN_0041fef0(pfVar10,afStack_2c,fStack_5c,fStack_58,fStack_54);
        fStack_44 = *pfVar9;
        fStack_40 = pfVar9[1];
        fStack_3c = pfVar9[2];
        FUN_00492ed0(param_1,param_2,&fStack_44);
        if ((((*(uint *)(param_2 + 0x88) & 0x8000000) != 0) && (*(int *)(param_1 + 0x370) != 0)) &&
           (((*pfVar10 < *(float *)(param_1 + 0x30c) ||
             (((*(float *)(param_2 + 0x198) < *(float *)(param_1 + 0x310) ||
               (*(float *)(param_2 + 0x19c) < *(float *)(param_1 + 0x314))) ||
              (*(float *)(param_1 + 0x318) < *pfVar10)))) ||
            ((*(float *)(param_1 + 0x31c) < *(float *)(param_2 + 0x198) ||
             (*(float *)(param_1 + 800) < *(float *)(param_2 + 0x19c))))))) {
          FUN_00479f80(param_1,param_2);
          return;
        }
        if ((*(byte *)(param_2 + 0x124) & 4) != 0) {
          pfVar10 = (float *)FUN_0041ff20(&local_38,afStack_2c,*pfVar10,*(float *)(param_2 + 0x198),
                                          *(float *)(param_2 + 0x19c));
          fVar12 = FUN_0043a41f(pfVar10);
          if ((float10)_DAT_004cbaec < fVar12) {
            FUN_004797d0(param_1,param_2,2);
          }
        }
      }
      *puVar2 = local_50;
      *(undefined4 *)(param_2 + 0xd4) = local_4c;
      *(undefined4 *)(param_2 + 0xd8) = uStack_48;
    }
  }
  return;
}


/* 004797d0 size=246 */

undefined4 __cdecl FUN_004797d0(int param_1,int param_2,ushort param_3)

{
  ushort *puVar1;
  char *pcVar2;
  
  if (((*(uint *)(param_2 + 0x124) & 4) == 0) || ((*(uint *)(param_2 + 0x124) & 1) != 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
    }
    return 0x19;
  }
  pcVar2 = (char *)(*(int *)(param_1 + 0xb10) + (uint)*(ushort *)(param_2 + 0xb8) * 8);
  if ((*pcVar2 != '\x01') || (*(int *)(pcVar2 + 4) == 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
    }
    return 1;
  }
  if ((*(short *)(*(int *)(param_2 + 400) + 0x58) == 0) && (*(int *)(param_1 + 0x664) != 0)) {
    *(undefined4 *)(*(int *)(param_2 + 400) + 0x50) = *(undefined4 *)(param_1 + 0xb20);
    *(int *)(param_1 + 0xb20) = param_2;
  }
  puVar1 = (ushort *)(*(int *)(param_2 + 400) + 0x58);
  *puVar1 = *puVar1 | param_3;
  return 0;
}


/* 004798d0 size=3 */

undefined4 __fastcall FUN_004798d0(undefined4 param_1)

{
  return param_1;
}


/* 004799f0 size=1418 */

undefined4 __cdecl FUN_004799f0(undefined4 param_1,int *param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  int iVar8;
  uint unaff_ESI;
  uint unaff_EDI;
  int *piVar9;
  uint uVar10;
  char cVar11;
  undefined1 auStack_846 [10];
  undefined4 uStack_83c;
  int *piVar12;
  undefined4 *puVar13;
  uint uVar14;
  uint uVar15;
  undefined2 uStack_816;
  undefined4 uStack_814;
  undefined4 uStack_810;
  undefined4 uStack_80c;
  undefined4 uStack_808;
  undefined4 uStack_804;
  undefined4 uStack_800;
  undefined4 uStack_7fc;
  undefined4 uStack_7f8;
  undefined4 uStack_7f4;
  undefined4 uStack_7f0;
  undefined4 uStack_7ec;
  undefined4 uStack_7e8;
  undefined4 local_7e4;
  undefined4 local_7e0;
  undefined4 local_7dc;
  uint local_7d8;
  undefined4 local_7d4;
  undefined1 local_7d0 [12];
  char local_7c4 [12];
  undefined1 local_7b8 [16];
  undefined4 local_7a8;
  undefined1 local_7a4;
  undefined1 uStack_798;
  undefined1 uStack_785;
  undefined1 local_764;
  undefined1 auStack_718 [52];
  undefined1 local_6e4 [460];
  undefined1 uStack_518;
  undefined1 local_4e4;
  undefined4 uStack_498;
  undefined4 uStack_494;
  undefined4 uStack_490;
  byte abStack_48c [8];
  undefined1 auStack_484 [12];
  char acStack_478 [20];
  undefined4 local_464;
  undefined4 local_460;
  undefined4 local_45c;
  char acStack_398 [32];
  undefined1 auStack_378 [224];
  undefined1 auStack_298 [32];
  char acStack_278 [584];
  int iStack_30;
  undefined4 uStack_28;
  int iStack_24;
  int *piStack_1c;
  undefined4 uStack_14;
  
  local_7e4 = 0;
  local_7e0 = 1;
  local_7dc = 0;
  local_7d8 = 0;
  local_7d4 = 0;
  FUN_0041fe60(local_7d0,0,0,0);
  FUN_0041fe60(local_7c4,0x3f800000,0x3f800000,0x3f800000);
  uStack_83c = (undefined4 *)0x479a53;
  FUN_00402fd0(local_7b8,0,0,0,0x3f800000);
  local_7a8 = 0;
  local_7a4 = 0;
  local_764 = 0;
  puVar4 = local_6e4;
  iVar8 = 4;
  do {
    *puVar4 = 0;
    puVar4 = puVar4 + 0x80;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  local_45c = 1;
  local_4e4 = 0;
  local_464 = 0;
  local_460 = 0;
  (**(code **)(*param_2 + 0x14))();
  puVar13 = &uStack_7f0;
  (**(code **)(*param_2 + 8))();
  uStack_83c = &uStack_808;
  piVar12 = (int *)0x4;
  (**(code **)(*param_2 + 8))();
  (**(code **)(*param_2 + 0x14))();
  (**(code **)(*param_2 + 8))();
  uVar15 = 0;
  if (unaff_ESI != 0) {
    do {
      (**(code **)(*param_2 + 8))(&uStack_816);
      (**(code **)(*param_2 + 0x18))(&uStack_810);
      (**(code **)(*param_2 + 0xc))(auStack_484,0x100);
      iVar5 = (**(code **)(*param_2 + 0x10))();
      iVar8 = iStack_30;
      if (iVar5 != 0) {
        FUN_00489880(iStack_30,0x2a,(char)uStack_28);
        FUN_004356e0();
        if (DAT_004e4420 < 1) {
          return 0x2a;
        }
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadObjects_004dbb3c);
        return 0x2a;
      }
      iVar5 = FUN_00402890(*(int *)(iStack_30 + 0xa1c),abStack_48c);
      if (iVar5 == 0) {
        FUN_00436670((byte *)s_Server_is_missing_class__s_004dbb48,abStack_48c);
LAB_00479b8b:
        piVar9 = (int *)0x0;
      }
      else {
        if (((*(byte *)(iVar5 + 8) & 2) != 0) ||
           ((iStack_24 == 0 &&
            (iVar6 = FUN_00402900(*(undefined4 *)(iVar8 + 0xa1c),iVar5,8), iVar6 == 0)))) {
          iVar5 = 0;
          goto LAB_00479b8b;
        }
        iVar8 = *(int *)(iVar5 + 0x24 + *(int *)(iVar8 + 0xa44) * 4);
        piVar9 = *(int **)(iVar8 + 0x20);
        if (piVar9 == (int *)0x0) {
          FUN_004b7c60(iVar8 + 8,*(int *)(iVar8 + 0x10));
          piVar9 = *(int **)(iVar8 + 0x20);
          if (piVar9 != (int *)0x0) goto LAB_00479d71;
          piVar9 = (int *)0x0;
        }
        else {
LAB_00479d71:
          *(int *)(iVar8 + 0x20) = *piVar9;
        }
        piVar9[2] = 0;
        piVar9[1] = 0;
        (**(code **)(iVar5 + 0xc))(piVar9);
      }
      uStack_816 = 0;
      uStack_814 = 1;
      uStack_80c = 0;
      uStack_808 = 0;
      uStack_7f8 = 0x3f800000;
      uStack_7f4 = 0x3f800000;
      uStack_7f0 = 0x3f800000;
      uStack_7ec = 0;
      uStack_7e8 = 0;
      local_7e4 = 0;
      local_7e0 = 0x3f800000;
      local_7dc = 0;
      local_7d8 = local_7d8 & 0xffffff00;
      puVar4 = auStack_718;
      iVar8 = 4;
      do {
        *puVar4 = 0;
        puVar4 = puVar4 + 0x80;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      uStack_490 = 1;
      uStack_518 = 0;
      uStack_498 = 0;
      uStack_494 = 0;
      uStack_810 = 0;
      uStack_798 = 0;
      auStack_718[0] = 0;
      uStack_804 = 0;
      uStack_800 = 0;
      uStack_7fc = 0;
      (**(code **)(*param_2 + 8))(&uStack_83c,4);
      uVar14 = 0;
      if (unaff_EDI != 0) {
        do {
          piVar9 = piVar12;
          puVar4 = auStack_378;
          (**(code **)(*param_2 + 0xc))();
          uVar10 = 1;
          (**(code **)(*param_2 + 8))(auStack_846 + 0xe);
          (**(code **)(*param_2 + 8))(auStack_846 + 0x26,4);
          (**(code **)(*param_2 + 8))(auStack_846 + -6,2);
          puVar7 = FUN_00430f00((uVar10 & 0xffff) + 0x5b);
          cVar11 = (char)puVar4;
          *puVar7 = (uint)puVar4 & 0xff;
          _strncpy((char *)(puVar7 + 1),acStack_398,0x4f);
          if (cVar11 == '\0') {
            (**(code **)(*param_2 + 0xc))(auStack_298,600);
            _strncpy((char *)(puVar7 + 0x16),acStack_278,((uint)puVar13 & 0xffff) - 1);
          }
          else {
            (**(code **)(*param_2 + 8))(puVar7 + 0x16,uVar10 & 0xffff);
          }
          puVar7[0x15] = *(uint *)(DAT_004ebfa4 + 0xc78);
          *(uint **)(DAT_004ebfa4 + 0xc78) = puVar7;
          uVar14 = uVar14 + 1;
          piVar12 = piVar9;
        } while (uVar14 < unaff_EDI);
      }
      if ((iVar5 != 0) && (piVar9 != (int *)0x0)) {
        _strncpy(local_7c4,acStack_478,0x3f);
        uStack_785 = 0;
        (**(code **)(*piVar9 + 4))(0,&uStack_804);
        piVar3 = piStack_1c;
        iVar8 = FUN_00487270(piStack_1c,piVar9,iVar5,(ushort *)&uStack_804,0xffff,0x3f800000,
                             &uStack_814);
        if (iVar8 != 0) {
          iVar8 = *(int *)(iVar5 + 0x24 + piVar3[0x291] * 4);
          (**(code **)(iVar5 + 0x10))();
          if (iVar8 != -8) {
            *piVar12 = *(int *)(iVar8 + 0x20);
            *(int **)(iVar8 + 0x20) = piVar12;
          }
        }
      }
      puVar2 = *(undefined **)(DAT_004ebfa4 + 0xc78);
      while (puVar2 != (undefined *)0x0) {
        puVar1 = *(undefined **)(puVar2 + 0x54);
        FUN_00430fe0(puVar2);
        puVar2 = puVar1;
      }
      uVar15 = uVar15 + 1;
      *(undefined4 *)(DAT_004ebfa4 + 0xc78) = 0;
    } while (uVar15 < unaff_ESI);
  }
  iVar8 = (**(code **)(*param_2 + 0x10))();
  if (iVar8 == 0) {
    return 0;
  }
  FUN_00489880((int)piStack_1c,0x2a,(char)uStack_14);
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadObjects_004dbb3c);
  }
  return 0x2a;
}


/* 00479f80 size=146 */

void __cdecl FUN_00479f80(int param_1,int param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  
  if ((~*(uint *)(param_1 + 0x1a0) & 1) == 0) {
    return;
  }
  if ((~*(uint *)(param_2 + 0x124) & 1) == 0) {
    return;
  }
  if ((DAT_004e514c != (int *)0x0) ||
     (FUN_004b7c60(0x4e5134,DAT_004e513c), piVar2 = DAT_004e514c, DAT_004e514c != (int *)0x0)) {
    piVar2 = DAT_004e514c;
    DAT_004e514c = (int *)*DAT_004e514c;
  }
  piVar2[2] = param_2;
  *piVar2 = param_1 + 0xa4c;
  puVar1 = *(undefined4 **)(param_1 + 0xa50);
  piVar2[1] = (int)puVar1;
  *puVar1 = piVar2;
  *(int **)(*piVar2 + 4) = piVar2;
  *(uint *)(param_2 + 0x124) = *(uint *)(param_2 + 0x124) | 1;
  FUN_00431720(param_2);
  *(uint *)(param_2 + 0x124) = *(uint *)(param_2 + 0x124) & 0xfffffffb;
  return;
}


/* 0047a020 size=102 */

void __cdecl FUN_0047a020(int param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = *(int **)(param_1 + 0xa50);
  while (piVar2 = piVar1, piVar2 != (int *)(param_1 + 0xa4c)) {
    FUN_00487570(param_1,*(int *)(*(int *)(piVar2[2] + 400) + 0x20));
    piVar1 = (int *)piVar2[1];
    *(int **)(*piVar2 + 4) = piVar1;
    *(int *)piVar2[1] = *piVar2;
    piVar2[1] = (int)piVar2;
    *piVar2 = (int)piVar2;
    if (piVar2 != (int *)0x0) {
      *piVar2 = (int)DAT_004e514c;
      DAT_004e514c = piVar2;
    }
  }
  return;
}


/* 0047a090 size=42 */

undefined4 __cdecl FUN_0047a090(int param_1,uint param_2)

{
  char *pcVar1;
  
  if (((param_2 & 0xffff) < *(uint *)(param_1 + 0xb14)) &&
     (pcVar1 = (char *)(*(int *)(param_1 + 0xb10) + (param_2 & 0xffff) * 8), *pcVar1 == '\x01')) {
    return *(undefined4 *)(pcVar1 + 4);
  }
  return 0;
}


/* 0047a0c0 size=34 */

int __cdecl FUN_0047a0c0(int param_1,uint param_2)

{
  if ((param_2 & 0xffff) < *(uint *)(param_1 + 0xb14)) {
    return *(int *)(param_1 + 0xb10) + (param_2 & 0xffff) * 8;
  }
  return 0;
}


/* 0047a0f0 size=55 */

int __cdecl FUN_0047a0f0(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xad8);
  if (iVar1 != param_1 + 0xad4) {
    do {
      if ((*(uint *)(iVar1 + 8) & 0xbfffffff) == (param_2 & 0xffff)) {
        return iVar1;
      }
      iVar1 = *(int *)(iVar1 + 4);
    } while (iVar1 != param_1 + 0xad4);
  }
  return 0;
}


/* 0047a130 size=293 */

void __cdecl FUN_0047a130(int param_1,int *param_2,int param_3)

{
  void *this;
  ushort uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  piVar4 = param_2;
  if (*(int *)(param_2[100] + 0x2c) == 0) {
    piVar6 = FUN_0046b170(&param_2,0x44c,0x44c);
    iVar2 = piVar4[100];
    piVar3 = *(int **)(iVar2 + 0x2c);
    if (piVar3 != (int *)0x0) {
      (**(code **)(*piVar3 + 8))();
    }
    piVar6 = (int *)*piVar6;
    *(int **)(iVar2 + 0x2c) = piVar6;
    if (piVar6 != (int *)0x0) {
      (**(code **)(*piVar6 + 4))();
    }
    if (param_2 != (int *)0x0) {
      (**(code **)(*param_2 + 8))();
    }
  }
  iVar5 = param_3;
  iVar2 = *(int *)(piVar4[100] + 0x2c);
  uVar1 = *(ushort *)(param_3 + 0x34);
  *(undefined2 *)(iVar2 + 0x34) = 1;
  *(ushort *)(iVar2 + 0x36) = uVar1;
  *(undefined2 *)(iVar2 + 0x38) = 1;
  *(undefined2 *)(iVar2 + 0x3a) = 1;
  *(undefined4 *)(iVar2 + 0x40) = 0;
  *(int *)(iVar2 + 0x10) = iVar2;
  if (*(uint *)(iVar2 + 0x58) < (uint)uVar1) {
    this = (void *)(iVar2 + 0x50);
    FUN_0040c870(this,0,&DAT_004ecc58);
    FUN_0040c870(this,0,&DAT_004ecc58);
    FUN_0043c3e0(this,0x44c);
    FUN_0040c870(this,(uint)uVar1,&DAT_004ecc58);
  }
  else {
    *(undefined4 *)(iVar2 + 0x60) = 0x44c;
  }
  uVar7 = *(ushort *)(iVar5 + 0x34) - 1;
  puVar9 = (undefined4 *)(*(int *)(iVar5 + 0x54) + 1);
  puVar10 = *(undefined4 **)(*(int *)(piVar4[100] + 0x2c) + 0x54);
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined1 *)puVar10 = *(undefined1 *)puVar9;
    puVar9 = (undefined4 *)((int)puVar9 + 1);
    puVar10 = (undefined4 *)((int)puVar10 + 1);
  }
  *(short *)(*(int *)(piVar4[100] + 0x2c) + 0x34) = *(short *)(iVar5 + 0x34) + -1;
  FUN_00479120(param_1,piVar4);
  return;
}


/* 0047a260 size=225 */

void __cdecl FUN_0047a260(undefined4 param_1,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int *piVar5;
  
  if (param_3 != (*(uint *)(param_2 + 0x124) & 0x38)) {
    *(uint *)(param_2 + 0x124) = *(uint *)(param_2 + 0x124) & 0xffffffc7 | param_3;
    iVar1 = *(int *)(param_2 + 400);
    piVar4 = (int *)(iVar1 + 0x44);
    piVar5 = (int *)(DAT_004ebfa4 + 0xaec);
    *(undefined4 *)(*piVar4 + 4) = *(undefined4 *)(iVar1 + 0x48);
    **(int **)(iVar1 + 0x48) = *piVar4;
    *(int **)(iVar1 + 0x48) = piVar4;
    *piVar4 = (int)piVar4;
    *piVar5 = *piVar5 + -1;
    iVar2 = DAT_004ebfa4;
    iVar1 = *(int *)(param_2 + 400);
    if (param_3 != 0) {
      piVar4 = (int *)(iVar1 + 0x44);
      piVar5 = (int *)(DAT_004ebfa4 + 0xaec);
      iVar2 = *(int *)(DAT_004ebfa4 + 0xaf0);
      *(int *)(iVar1 + 0x4c) = param_2;
      *piVar4 = iVar2;
      puVar3 = *(undefined4 **)(iVar2 + 4);
      *(undefined4 **)(iVar1 + 0x48) = puVar3;
      *puVar3 = piVar4;
      *(int **)(*piVar4 + 4) = piVar4;
      *piVar5 = *piVar5 + 1;
      (**(code **)(**(int **)(*(int *)(param_2 + 400) + 0x20) + 4))(0xd,0,0);
      return;
    }
    piVar4 = (int *)(iVar1 + 0x44);
    piVar5 = (int *)(DAT_004ebfa4 + 0xaec);
    *(int *)(iVar1 + 0x4c) = param_2;
    *piVar4 = iVar2 + 0xaf0;
    puVar3 = *(undefined4 **)(iVar2 + 0xaf4);
    *(undefined4 **)(iVar1 + 0x48) = puVar3;
    *puVar3 = piVar4;
    *(int **)(*piVar4 + 4) = piVar4;
    *piVar5 = *piVar5 + 1;
    (**(code **)(**(int **)(*(int *)(param_2 + 400) + 0x20) + 4))(0xc,0,0);
  }
  return;
}


/* 0047a350 size=69 */

void __cdecl FUN_0047a350(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0xb04);
  while (iVar1 != param_1 + 0xb00) {
    iVar2 = *(int *)(iVar1 + 4);
    FUN_00430fe0(*(undefined **)(iVar1 + 8));
    iVar1 = iVar2;
  }
  iVar1 = param_1 + 0xb00;
  *(int *)(param_1 + 0xb04) = iVar1;
  *(int *)iVar1 = iVar1;
  *(undefined4 *)(param_1 + 0xafc) = 0;
  return;
}


/* 0047a3a0 size=52 */

int __cdecl FUN_0047a3a0(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xb04);
  if (iVar1 != param_1 + 0xb00) {
    do {
      if (*(short *)(*(int *)(iVar1 + 8) + 0x10) == *(short *)(param_2 + 0xb8)) {
        return *(int *)(iVar1 + 8);
      }
      iVar1 = *(int *)(iVar1 + 4);
    } while (iVar1 != param_1 + 0xb00);
  }
  return 0;
}


/* 0047a3e0 size=67 */

void __cdecl FUN_0047a3e0(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xaf4);
  while (iVar3 != param_1 + 0xaf0) {
    iVar2 = *(int *)(iVar3 + 4);
    piVar1 = (int *)(iVar3 + 8);
    iVar3 = iVar2;
    if ((*(byte *)(*piVar1 + 0x124) & 0x80) != 0) {
      FUN_00487570(param_1,*(int *)(*(int *)(*piVar1 + 400) + 0x20));
    }
  }
  return;
}


/* 0047a7c0 size=36 */

char * __cdecl FUN_0047a7c0(char *param_1)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  
  if (param_1 == (char *)0x0) {
    return (char *)0x0;
  }
  pcVar3 = param_1;
  cVar2 = *param_1;
  while (cVar2 != '\0') {
    if (cVar2 == '/') {
      *param_1 = '\\';
    }
    pcVar1 = param_1 + 1;
    param_1 = param_1 + 1;
    cVar2 = *pcVar1;
  }
  return pcVar3;
}


/* 0047aac0 size=312 */

bool __cdecl FUN_0047aac0(int param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined4 *puVar7;
  int *piVar8;
  int *piVar9;
  uint uVar10;
  
  if (1 < DAT_004e4420) {
    uVar5 = FUN_00468720(param_2);
    FUN_00436670((byte *)s__Server__loaded_model___s_004dbcd8,uVar5);
  }
  if (2 < DAT_004e4420) {
    uVar5 = FUN_00468720(param_2);
    FUN_00436670((byte *)s_Adding_model_to_resource_list____004dbcb4,uVar5);
  }
  pcVar6 = (char *)FUN_00468720(param_2);
  uVar10 = 0xffffffff;
  do {
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  uVar10 = ~uVar10 - 1;
  puVar7 = (undefined4 *)FUN_00468720(param_2);
  piVar8 = FUN_00434d70(*(int **)(param_1 + 0xb28),puVar7,uVar10);
  FUN_00434fe0((int)piVar8,param_2);
  if ((param_4 != 0) && ((*(byte *)(param_3 + 0xc) & 1) != 0)) {
    for (iVar2 = *(int *)(param_1 + 0x5cc); iVar2 != param_1 + 0x5c8; iVar2 = *(int *)(iVar2 + 4)) {
      iVar3 = *(int *)(iVar2 + 8);
      if (*(int *)(*(int *)(iVar3 + 400) + 0x30) == param_3) {
        iVar4 = *(int *)(*(int *)(iVar3 + 0x1f8) + 0x20c);
        if (iVar4 != 0) {
          *(int *)(*(int *)(iVar3 + 0x1f8) + 0x20c) = iVar4 + -1;
        }
        *(int *)(iVar3 + 0x1f8) = param_2;
        *(int *)(param_2 + 0x20c) = *(int *)(param_2 + 0x20c) + 1;
        *(ushort *)(iVar3 + 0x1e8) = *(ushort *)(iVar3 + 0x1e8) & 0xfff7;
      }
    }
    *(byte *)(param_3 + 0xc) = *(byte *)(param_3 + 0xc) & 0xfe;
  }
  piVar9 = (int *)FUN_00430de0(8);
  if (piVar9 == (int *)0x0) {
    piVar9 = (int *)0x0;
  }
  else {
    *piVar9 = param_1;
    piVar9[1] = param_2;
  }
  puVar7 = FUN_00445fe0(&PTR_LAB_004dbb68,piVar9);
  FUN_00446060((int *)(param_2 + 0x14),(int)puVar7);
  FUN_00416be0(param_2);
  return piVar8 == (int *)0x0;
}


/* 0047ac00 size=341 */

int __cdecl
FUN_0047ac00(int param_1,char *param_2,int *param_3,int *param_4,int param_5,int param_6)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int local_20 [2];
  undefined4 local_18;
  undefined4 local_10;
  int local_c;
  
  *param_3 = 0;
  *param_4 = 0;
  FUN_0047a7c0(param_2);
  uVar3 = 0xffffffff;
  pcVar4 = param_2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar2 = FUN_00434ec0(*(int **)(param_1 + 0xb28),param_2,~uVar3 - 1);
  if (iVar2 != 0) {
    iVar2 = FUN_00434fd0(iVar2);
    *param_3 = iVar2;
    return 0;
  }
  iVar2 = FUN_0047b810(param_1 + 0xc3c,param_2,0,param_4);
  if (iVar2 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_se_LoadModel_004dbcf4);
    }
    return 0x16;
  }
  if (param_5 == 0) {
    return 0x54;
  }
  if (param_6 == 0) {
    iVar2 = FUN_00417b50((void *)(param_1 + 0xcd4),*param_4);
    if (iVar2 == 0) {
      FUN_0044df70((int)local_20);
      local_c = *param_4;
      local_18 = 0;
      local_10 = 0;
      FUN_0044e0a0((void *)(param_1 + 0xcd8),local_20);
      return 0x54;
    }
    return 0x54;
  }
  iVar2 = servermgr_47a7f0(param_1,param_2,(int *)*param_4,param_3);
  if (iVar2 == 0) {
    FUN_0047aac0(param_1,*param_3,*param_4,1);
  }
  return iVar2;
}


/* 0047b2f0 size=42 */

undefined4 __cdecl FUN_0047b2f0(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (*(code **)(&DAT_004dbb70 + *(char *)(param_2 + 0xbc) * 8) == (code *)0x0) {
    return 0;
  }
  uVar1 = (**(code **)(&DAT_004dbb70 + *(char *)(param_2 + 0xbc) * 8))(param_1,param_2,param_3);
  return uVar1;
}


/* 0047b320 size=37 */

undefined4 __cdecl FUN_0047b320(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(code **)(&DAT_004dbb74 + *(char *)(param_2 + 0xbc) * 8) == (code *)0x0) {
    return 0;
  }
  uVar1 = (**(code **)(&DAT_004dbb74 + *(char *)(param_2 + 0xbc) * 8))(param_1,param_2);
  return uVar1;
}


/* 0047b350 size=127 */

undefined4 __cdecl FUN_0047b350(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 400) == 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_BackupExtraData_004dbe34);
    }
    return 0x3c;
  }
  param_2[0x14] = *(undefined4 *)(*(int *)(param_1 + 400) + 0x30);
  param_2[0x15] = *(undefined4 *)(*(int *)(param_1 + 400) + 0x34);
  if (*(char *)(param_1 + 0xbc) == '\x01') {
    puVar2 = (undefined4 *)(param_1 + 0x1d0);
    for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_2 = *puVar2;
      puVar2 = puVar2 + 1;
      param_2 = param_2 + 1;
    }
  }
  return 0;
}


/* 0047b3d0 size=126 */

undefined4 __cdecl FUN_0047b3d0(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 400) == 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_RestoreExtraData_004dbe44);
    }
    return 0x3c;
  }
  *(undefined4 *)(*(int *)(param_1 + 400) + 0x30) = param_2[0x14];
  *(undefined4 *)(*(int *)(param_1 + 400) + 0x34) = param_2[0x15];
  if (*(char *)(param_1 + 0xbc) == '\x01') {
    puVar2 = (undefined4 *)(param_1 + 0x1d0);
    for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_2;
      param_2 = param_2 + 1;
      puVar2 = puVar2 + 1;
    }
  }
  return 0;
}


/* 0047b480 size=76 */

void __cdecl FUN_0047b480(undefined4 *param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = param_1;
  for (iVar2 = 0xf; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  piVar1 = FUN_00434a60(500,3);
  param_1[4] = piVar1;
  param_1[1] = param_1;
  *param_1 = param_1;
  param_1[5] = param_2;
  FUN_004b7c10((int)(param_1 + 7));
  FUN_004b7be0(param_1 + 7,0x14,0x40,0x200);
  return;
}


/* 0047b4d0 size=92 */

void __cdecl FUN_0047b4d0(int param_1)

{
  undefined *puVar1;
  int iVar2;
  
  FUN_0047b940(param_1);
  if (*(int **)(param_1 + 0x10) != (int *)0x0) {
    FUN_00434d00(*(int **)(param_1 + 0x10));
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  iVar2 = *(int *)(param_1 + 4);
  if (iVar2 == param_1) {
    *(int *)(param_1 + 4) = param_1;
    *(int *)param_1 = param_1;
    return;
  }
  do {
    puVar1 = *(undefined **)(iVar2 + 8);
    iVar2 = *(int *)(iVar2 + 4);
    FUN_004278e0(*(undefined **)(puVar1 + 0xc));
    FUN_00430fe0(puVar1);
  } while (iVar2 != param_1);
  *(int *)(param_1 + 4) = param_1;
  *(int *)param_1 = param_1;
  return;
}


/* 0047b530 size=166 */

void __cdecl
FUN_0047b530(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,int *param_5)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int local_4;
  
  puVar2 = param_4;
  local_4 = 0;
  if ((int)param_3 < 1) {
    *param_5 = 0;
    return;
  }
  param_4 = param_3;
  puVar6 = puVar2;
  do {
    iVar3 = FUN_00427780((byte *)*param_2,&param_3);
    if (iVar3 == 0) {
      piVar4 = FUN_00430f00(0x10);
      piVar4[2] = (int)piVar4;
      piVar4[3] = (int)param_3;
      *piVar4 = param_1;
      puVar1 = *(undefined4 **)(param_1 + 4);
      piVar4[1] = (int)puVar1;
      *puVar1 = piVar4;
      *(int **)(*piVar4 + 4) = piVar4;
      if (puVar2 != (undefined4 *)0x0) {
        uVar5 = FUN_00427940(param_3);
        *puVar6 = uVar5;
      }
      local_4 = local_4 + 1;
      puVar6 = puVar6 + 1;
    }
    param_2 = param_2 + 1;
    param_4 = (undefined4 *)((int)param_4 + -1);
  } while (param_4 != (undefined4 *)0x0);
  *param_5 = local_4;
  return;
}


/* 0047b5e0 size=23 */

int __cdecl FUN_0047b5e0(int param_1,char *param_2)

{
  FUN_0047b600(param_1,param_2,0,0);
  return;
}


/* 0047b600 size=154 */

int * __cdecl FUN_0047b600(int param_1,char *param_2,int param_3,undefined2 param_4)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  char *pcVar5;
  
  uVar4 = 0xffffffff;
  pcVar5 = param_2;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  iVar2 = FUN_00434ec0(*(int **)(param_1 + 0x10),param_2,~uVar4);
  if ((iVar2 != 0) && (iVar2 = FUN_00434fd0(iVar2), iVar2 != 0)) {
    piVar3 = de_file_427ad0(*(int **)(*(int *)(iVar2 + 0x10) + 0xc),param_2);
    return piVar3;
  }
  iVar2 = *(int *)(param_1 + 4);
  while( true ) {
    if (iVar2 == param_1) {
      return (int *)0x0;
    }
    piVar3 = de_file_427ad0(*(int **)(*(int *)(iVar2 + 8) + 0xc),param_2);
    if (piVar3 != (int *)0x0) break;
    iVar2 = *(int *)(iVar2 + 4);
  }
  if (param_3 != 0) {
    FUN_0047b810(param_1,param_2,param_4,(undefined4 *)0x0);
  }
  return piVar3;
}


/* 0047b6a0 size=36 */

int __cdecl FUN_0047b6a0(undefined4 param_1,int *param_2)

{
  char *pcVar1;
  
  pcVar1 = FUN_0047b9b0(param_1,param_2);
  de_file_427ad0(*(int **)(param_2[4] + 0xc),pcVar1);
  return;
}


/* 0047b6d0 size=95 */

undefined1 __cdecl FUN_0047b6d0(int param_1,char *param_2,LPCSTR param_3)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  undefined3 extraout_var;
  
  iVar1 = *(int *)(param_1 + 4);
  while( true ) {
    if (iVar1 == param_1) {
      return 0x3d;
    }
    piVar3 = de_file_427ad0(*(int **)(*(int *)(iVar1 + 8) + 0xc),param_2);
    if (piVar3 != (int *)0x0) break;
    iVar1 = *(int *)(iVar1 + 4);
  }
  bVar2 = FUN_004282e0(piVar3,param_3);
  (**(code **)(*piVar3 + 4))();
  return CONCAT31(extraout_var,bVar2) == 0;
}


/* 0047b730 size=125 */

undefined4 __cdecl FUN_0047b730(int param_1,char *param_2,int *param_3,undefined4 *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_110 [66];
  undefined4 local_8;
  
  iVar1 = *(int *)(param_1 + 4);
  while( true ) {
    if (iVar1 == param_1) {
      return 0;
    }
    iVar2 = *(int *)(iVar1 + 8);
    iVar3 = FUN_00427960(*(int **)(iVar2 + 0xc),param_2,local_110);
    if (iVar3 != 0) break;
    iVar1 = *(int *)(iVar1 + 4);
  }
  if (param_3 != (int *)0x0) {
    *param_3 = iVar2;
  }
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = local_8;
  }
  return 1;
}


/* 0047b7b0 size=89 */

int * __cdecl FUN_0047b7b0(int param_1,char *param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_78 [30];
  
  if (param_1 == 0) {
    return (int *)0x0;
  }
  iVar1 = *(int *)(param_1 + 4);
  iVar3 = 0;
  if (iVar1 != param_1) {
    puVar4 = local_78;
    do {
      iVar3 = iVar3 + 1;
      *puVar4 = *(undefined4 *)(*(int *)(iVar1 + 8) + 0xc);
      if (0x1d < iVar3) break;
      iVar1 = *(int *)(iVar1 + 4);
      puVar4 = puVar4 + 1;
    } while (iVar1 != param_1);
  }
  piVar2 = FUN_0043ff50(local_78,iVar3,param_2);
  return piVar2;
}


/* 0047b810 size=303 */

undefined4 __cdecl FUN_0047b810(int param_1,char *param_2,undefined2 param_3,undefined4 *param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 uVar7;
  int *piVar8;
  int iVar9;
  uint uVar10;
  undefined2 extraout_var;
  int *piVar11;
  char *pcVar12;
  
  puVar5 = param_4;
  pcVar4 = param_2;
  iVar2 = param_1;
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = 0;
  }
  uVar10 = 0xffffffff;
  pcVar12 = param_2;
  do {
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    cVar1 = *pcVar12;
    pcVar12 = pcVar12 + 1;
  } while (cVar1 != '\0');
  iVar6 = FUN_00434ec0(*(int **)(param_1 + 0x10),param_2,~uVar10);
  if (iVar6 != 0) {
    uVar7 = FUN_00434fd0(iVar6);
    if (puVar5 != (undefined4 *)0x0) {
      *puVar5 = uVar7;
    }
    return 1;
  }
  iVar6 = FUN_0047b730(iVar2,pcVar4,(int *)&param_2,&param_1);
  if (iVar6 == 0) {
    return 0;
  }
  piVar11 = *(int **)(iVar2 + 0x34);
  if (piVar11 == (int *)0x0) {
    FUN_004b7c60(iVar2 + 0x1c,*(int *)(iVar2 + 0x24));
    piVar11 = *(int **)(iVar2 + 0x34);
    if (piVar11 == (int *)0x0) goto LAB_0047b8a2;
  }
  *(int *)(iVar2 + 0x34) = *piVar11;
LAB_0047b8a2:
  uVar10 = 0xffffffff;
  pcVar12 = pcVar4;
  do {
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    cVar1 = *pcVar12;
    pcVar12 = pcVar12 + 1;
  } while (cVar1 != '\0');
  piVar8 = FUN_00434d70(*(int **)(iVar2 + 0x10),(undefined4 *)pcVar4,~uVar10);
  *(undefined2 *)(piVar11 + 3) = param_3;
  piVar11[4] = (int)param_2;
  piVar11[1] = param_1;
  piVar11[2] = *(int *)(iVar2 + 0xc);
  *(int *)(iVar2 + 0xc) = *(int *)(iVar2 + 0xc) + 1;
  FUN_00434fe0((int)piVar8,piVar11);
  *piVar11 = (int)piVar8;
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = piVar11;
  }
  iVar2 = *(int *)(iVar2 + 0x14);
  for (iVar6 = *(int *)(iVar2 + 0x9fc); iVar6 != iVar2 + 0x9f8; iVar6 = *(int *)(iVar6 + 4)) {
    iVar3 = *(int *)(iVar6 + 8);
    iVar9 = FUN_00434fb0(*piVar11,(uint *)0x0);
    FUN_00438870(*(int *)(iVar3 + 0x18c),iVar9,piVar11[1],piVar11[2],
                 (int *)CONCAT22(extraout_var,(short)piVar11[3]));
  }
  return 2;
}


/* 0047b940 size=108 */

void __cdecl FUN_0047b940(int param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  iVar1 = param_1;
  param_1 = FUN_00434ff0(*(int *)(param_1 + 0x10));
  if (param_1 == 0) {
    *(undefined4 *)(iVar1 + 0xc) = 0;
    return;
  }
  do {
    piVar2 = (int *)FUN_00435040(&param_1);
    puVar3 = (undefined4 *)FUN_00434fd0((int)piVar2);
    if ((puVar3 != (undefined4 *)0x0) && (iVar1 != -0x1c)) {
      *puVar3 = *(undefined4 *)(iVar1 + 0x34);
      *(undefined4 **)(iVar1 + 0x34) = puVar3;
    }
    FUN_00434e60(*(int **)(iVar1 + 0x10),piVar2);
  } while (param_1 != 0);
  *(undefined4 *)(iVar1 + 0xc) = 0;
  return;
}


/* 0047b9b0 size=28 */

undefined1 * __cdecl FUN_0047b9b0(undefined4 param_1,int *param_2)

{
  undefined1 *puVar1;
  
  if (param_2 == (int *)0x0) {
    return &DAT_004e4424;
  }
  puVar1 = (undefined1 *)FUN_00434fb0(*param_2,(uint *)0x0);
  return puVar1;
}


/* 0047ba00 size=689 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0047ba00: lifted from original x86 -> lt_lifted.c */


/* 0047bcc0 size=440 */

/* FUN_0047bcc0: lifted from original x86 -> lt_lifted.c */


/* 0047bea0 size=226 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0047bea0(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  if ((param_1 != 0) && (param_2 != (float *)0x0)) {
    fVar1 = *(float *)(param_1 + 0xc4) - *param_2;
    fVar2 = *(float *)(param_1 + 200) - param_2[1];
    fVar3 = *(float *)(param_1 + 0xcc) - param_2[2];
    if (fVar2 * fVar2 + fVar3 * fVar3 + fVar1 * fVar1 < _DAT_004cbaec) {
      return 0;
    }
    *(uint *)(param_1 + 0x124) = *(uint *)(param_1 + 0x124) | 0x40;
    *(float *)(param_1 + 0xc4) = *param_2;
    *(float *)(param_1 + 200) = param_2[1];
    *(float *)(param_1 + 0xcc) = param_2[2];
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTPhysics__SetVelocity_004dbe58);
  }
  return 0x3c;
}


