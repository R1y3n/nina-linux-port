/* lithtech.exe decompilation - unnamed_00490000 */
#include "ghidra_types.h"

/* 004903b0 size=498 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_004903b0(void *param_1,int param_2,uint param_3,uint param_4)

{
  uint uVar1;
  ushort uVar2;
  char *pcVar3;
  void *this;
  int iVar4;
  int *piVar5;
  int *piVar6;
  char local_154;
  float local_150;
  uint local_14c;
  int local_148 [2];
  undefined2 local_140;
  uint local_13c [68];
  uint local_2c;
  undefined4 local_14 [5];
  
  piVar5 = (int *)0x0;
  local_14c = param_4 & 1;
  local_148[0] = 0;
  local_148[1] = 0;
  local_140 = 0;
  if ((short)local_14c == 0) {
    pcVar3 = (char *)FUN_004270c0(*(int *)((int)param_1 + 0x78),param_3);
    if (((pcVar3 != (char *)0x0) && (*(int **)(pcVar3 + 4) != (int *)0x0)) && (*pcVar3 == '\x02')) {
      piVar5 = *(int **)(pcVar3 + 4);
    }
  }
  else {
    if ((short)param_3 != -1) {
      pcVar3 = (char *)FUN_004270c0(*(int *)((int)param_1 + 0x78),param_3);
      if ((pcVar3 != (char *)0x0) && (piVar6 = *(int **)(pcVar3 + 4), piVar6 != (int *)0x0)) {
        if (*pcVar3 == '\x01') {
          FUN_00412f00(*(int *)((int)param_1 + 0x78),(int)piVar6);
        }
        else {
          this = (void *)FUN_00410170();
          FUN_00497990(this,piVar6);
        }
      }
    }
    FUN_004905b0(param_1,param_2,local_13c,local_148,&local_150);
    local_2c = param_3 & 0xffff;
  }
  if ((param_4 & 2) != 0) {
    iVar4 = FUN_00416dd0((int)param_1);
    FUN_0043f3b0((int *)(param_2 + 8),local_14,iVar4);
    if (piVar5 != (int *)0x0) {
      (**(code **)(*piVar5 + 0x38))(local_14,0);
    }
  }
  if ((param_4 & 0x20) != 0) {
    uVar2 = *(ushort *)(param_2 + 0x38);
    uVar1 = uVar2 + 1;
    if ((uVar1 < *(uint *)(param_2 + 0x58)) && (uVar1 <= *(ushort *)(param_2 + 0x34))) {
      local_154 = *(char *)(*(int *)(param_2 + 0x54) + (uint)uVar2);
      *(ushort *)(param_2 + 0x38) = uVar2 + 1;
    }
    else {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
    }
    if (piVar5 != (int *)0x0) {
      if (local_154 == '\0') {
        FUN_00494df0((int)piVar5);
      }
      else {
        FUN_00494e90((int)piVar5);
      }
    }
  }
  if ((short)local_14c != 0) {
    clientmgr_411810(DAT_004e516c,local_13c,local_148);
  }
  return 0;
}


/* 004905b0 size=1019 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004905b0: lifted from original x86 -> lt_lifted.c */


/* 00490d70 size=96 */

undefined4 __cdecl FUN_00490d70(int param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  
  iVar3 = param_2;
  uVar2 = *(ushort *)(param_2 + 0x34);
  if ((uint)uVar2 == (uint)*(ushort *)(param_2 + 0x38)) {
    param_2 = 0;
  }
  else {
    bVar1 = *(byte *)(*(int *)(param_2 + 0x54) + -1 + (uint)uVar2);
    *(ushort *)(param_2 + 0x34) = uVar2 - 1;
    param_2 = (int)bVar1;
  }
  FUN_00412310(*(void **)(param_1 + 0x78),iVar3);
  (**(code **)(**(int **)(*(int *)(param_1 + 0x78) + 0x620) + 0x1c))(param_2,iVar3 + 8);
  return 0;
}


/* 004910b0 size=51 */

undefined4 __cdecl FUN_004910b0(int param_1,int param_2)

{
  char *pcVar1;
  byte *pbVar2;
  
  pcVar1 = (char *)FUN_0046b370(param_2);
  pbVar2 = (byte *)FUN_0046b370(param_2);
  FUN_00420590(*(int *)(param_1 + 0x78) + 0x1378,pcVar1,pbVar2);
  return 0;
}


/* 004910f0 size=403 */

undefined4 __cdecl FUN_004910f0(uint param_1,void *param_2)

{
  uint uVar1;
  ushort uVar2;
  ushort uVar3;
  void *pvVar4;
  int iVar5;
  uint uVar6;
  char unaff_DI;
  undefined4 *puVar7;
  
  pvVar4 = param_2;
  FUN_0046b3c0(param_2,(undefined4 *)(*(int *)(param_1 + 0x78) + 0x12b0),0x30);
  uVar2 = *(ushort *)((int)param_2 + 0x38);
  uVar6 = uVar2 + 2;
  if ((uVar6 < *(uint *)((int)param_2 + 0x58)) && (uVar6 <= *(ushort *)((int)param_2 + 0x34))) {
    uVar3 = *(ushort *)(*(int *)((int)param_2 + 0x54) + (uint)uVar2);
    *(ushort *)((int)param_2 + 0x38) = uVar2 + 2;
    uVar6 = (uint)uVar3;
  }
  else {
    *(uint *)((int)param_2 + 0x40) = *(uint *)((int)param_2 + 0x40) | 2;
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
    }
    uVar6 = param_1;
  }
  if (0x1e < (ushort)uVar6) {
    FUN_004267b0(*(int *)(param_1 + 0x78),0x2c,unaff_DI);
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_OnSkyDef_004dcff8);
    }
    return 1;
  }
  puVar7 = (undefined4 *)(*(int *)(param_1 + 0x78) + 0x1270);
  for (iVar5 = 0xf; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = 0xffffffff;
    puVar7 = puVar7 + 1;
  }
  if ((ushort)uVar6 != 0) {
    param_2 = (void *)(uVar6 & 0xffff);
    uVar6 = param_1;
    iVar5 = 0x1270;
    do {
      uVar2 = *(ushort *)((int)pvVar4 + 0x38);
      uVar1 = uVar2 + 2;
      if ((uVar1 < *(uint *)((int)pvVar4 + 0x58)) && (uVar1 <= *(ushort *)((int)pvVar4 + 0x34))) {
        uVar6 = (uint)*(ushort *)(*(int *)((int)pvVar4 + 0x54) + (uint)uVar2);
        *(ushort *)((int)pvVar4 + 0x38) = uVar2 + 2;
      }
      else {
        *(uint *)((int)pvVar4 + 0x40) = *(uint *)((int)pvVar4 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      param_2 = (void *)((int)param_2 + -1);
      *(short *)(iVar5 + *(int *)(param_1 + 0x78)) = (short)uVar6;
      iVar5 = iVar5 + 2;
    } while (param_2 != (void *)0x0);
  }
  return 0;
}


/* 00492420 size=246 */

/* FUN_00492420: lifted from original x86 -> lt_lifted.c */


/* 00492520 size=106 */

void __fastcall FUN_00492520(int *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int *local_4;
  
  local_4 = param_1;
  puVar2 = FUN_0046b170(&local_4,0x44c,0x44c);
  piVar1 = (int *)*puVar2;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))();
  }
  if (local_4 != (int *)0x0) {
    (**(code **)(*local_4 + 8))();
  }
  if (param_1[0xd] != 0) {
    *(undefined1 *)piVar1[0x15] = 6;
    FUN_004657c0((void *)(param_1[0x1e] + 0x510),piVar1,(float *)param_1[0xd],0x80);
  }
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))();
  }
  return;
}


/* 00492590 size=37 */

int __thiscall FUN_00492590(void *this,int *param_1)

{
  int *piVar1;
  
  if (*(int **)this != (int *)0x0) {
    (**(code **)(**(int **)this + 8))();
  }
  piVar1 = (int *)*param_1;
  *(int **)this = piVar1;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))();
  }
  return *(int *)this;
}


/* 004925c0 size=121 */

float10 __fastcall FUN_004925c0(float param_1)

{
  uint uVar1;
  float fVar2;
  ushort uVar3;
  
  uVar3 = *(ushort *)((int)param_1 + 0x38);
  uVar1 = uVar3 + 4;
  if ((uVar1 < *(uint *)((int)param_1 + 0x58)) && (uVar1 <= *(ushort *)((int)param_1 + 0x34))) {
    fVar2 = *(float *)(*(int *)((int)param_1 + 0x54) + (uint)uVar3);
    *(ushort *)((int)param_1 + 0x38) = uVar3 + 4;
    return (float10)fVar2;
  }
  *(uint *)((int)param_1 + 0x40) = *(uint *)((int)param_1 + 0x40) | 2;
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
  }
  return (float10)param_1;
}


/* 004926a0 size=27 */

undefined4 __fastcall FUN_004926a0(int param_1)

{
  undefined4 in_EAX;
  undefined4 uVar1;
  
  if (*(short *)(param_1 + 0x6c) == -1) {
    return 0;
  }
  uVar1 = FUN_00427090(*(int *)(param_1 + 0x78),
                       CONCAT22((short)((uint)in_EAX >> 0x10),*(short *)(param_1 + 0x6c)));
  return uVar1;
}


/* 004926f0 size=18 */

int __thiscall FUN_004926f0(void *this,undefined4 param_1)

{
  *(undefined ***)this = &PTR_FUN_004cd670;
  *(undefined4 *)((int)this + 4) = param_1;
  return;
}


/* 00492710 size=176 */

undefined4 __thiscall FUN_00492710(void *this,int *param_1,int *param_2)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  short sVar6;
  
  piVar3 = param_2;
  *param_2 = 0;
  (**(code **)(*param_1 + 0xc))(&param_2);
  iVar4 = (**(code **)(*param_1 + 0x90))();
  sVar6 = (short)param_1;
  if (iVar4 == 1) {
    if (sVar6 != -1) {
      uVar5 = 0;
      iVar4 = DAT_004ebfa4 + 0x5b8;
      do {
        for (iVar2 = *(int *)(iVar4 + 4); iVar2 != iVar4; iVar2 = *(int *)(iVar2 + 4)) {
          if (*(short *)(*(int *)(iVar2 + 8) + 0xba) == sVar6) {
            *piVar3 = *(int *)(iVar2 + 8);
            return 0;
          }
        }
        uVar5 = uVar5 + 1;
        iVar4 = iVar4 + 0x10;
      } while (uVar5 < 0xb);
      return 0;
    }
  }
  else if (sVar6 != -1) {
    if ((((uint)param_1 & 0xffff) < *(uint *)(*(int *)((int)this + 4) + 0xb14)) &&
       (pcVar1 = (char *)(*(int *)(*(int *)((int)this + 4) + 0xb10) + ((uint)param_1 & 0xffff) * 8),
       *pcVar1 == '\x01')) {
      *piVar3 = *(int *)(pcVar1 + 4);
    }
  }
  return 0;
}


/* 004927c0 size=90 */

undefined4 FUN_004927c0(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x90))();
  if (iVar1 == 1) {
    iVar1 = *param_1;
    if (param_2 != 0) {
      (**(code **)(iVar1 + 0x48))(*(undefined2 *)(param_2 + 0xba));
      return 0;
    }
  }
  else {
    iVar1 = *param_1;
    if (param_2 != 0) {
      (**(code **)(iVar1 + 0x48))(*(undefined2 *)(param_2 + 0xb8));
      return 0;
    }
  }
  (**(code **)(iVar1 + 0x48))(0xffff);
  return 0;
}


/* 00492ed0 size=197 */

void __cdecl FUN_00492ed0(int param_1,int param_2,float *param_3)

{
  undefined8 uVar1;
  LARGE_INTEGER local_78;
  int *local_70;
  float local_6c;
  undefined4 local_68;
  int local_64;
  uint local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004ea72c = DAT_004ea72c + 1;
  FUN_00424310(&local_78,0);
  local_70 = &DAT_004ea728;
  FUN_00424400(&local_78);
  local_8 = 0;
  local_4 = 0;
  local_68 = *(undefined4 *)(param_1 + 0x8b4);
  local_6c = (float)(param_1 + 0x210);
  local_60 = (uint)*(byte *)(param_2 + 0xbd);
  local_64 = param_2;
  local_5c = 0;
  local_58 = 0;
  FUN_0045ef30(&local_6c,*param_3,param_3[1],param_3[2]);
  uVar1 = FUN_00424410((uint *)&local_78);
  *local_70 = *local_70 + (int)uVar1;
  return;
}


/* 00493020 size=86 */

undefined4 * __fastcall FUN_00493020(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = param_1 + 0x23;
  puVar1 = param_1 + 0x23;
  param_1[0x24] = puVar3;
  *puVar3 = puVar3;
  param_1[0x22] = 0;
  *param_1 = &PTR_FUN_004cd690;
  param_1[1] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x18] = 0;
  param_1[0x24] = puVar1;
  *puVar1 = puVar1;
  param_1[0x22] = 0;
  param_1[0x10] = 0;
  param_1[0x17] = 0;
  param_1[0x16] = 0;
  puVar3 = param_1 + 0x19;
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  return param_1;
}


/* 00493080 size=30 */

undefined4 * __thiscall FUN_00493080(void *this,byte param_1)

{
  soundbuffer_4930a0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004930b0 size=74 */

undefined4 __thiscall FUN_004930b0(void *this,int param_1)

{
  int iVar1;
  
  (**(code **)(*(int *)this + 0xc))();
  *(int *)((int)this + 4) = param_1;
  *(undefined4 *)((int)this + 0x40) = 1;
  iVar1 = (**(code **)(*(int *)this + 0x18))();
  if (iVar1 == 0) {
    iVar1 = (int)this + 0x8c;
    *(int *)((int)this + 0x90) = iVar1;
    *(int *)iVar1 = iVar1;
    *(undefined4 *)((int)this + 0x88) = 0;
    **(undefined4 **)((int)this + 4) = this;
    return 0;
  }
  return 1;
}


/* 00493100 size=178 */

undefined4 __thiscall FUN_00493100(void *this,int param_1)

{
  int iVar1;
  
  (**(code **)(*(int *)this + 0xc))();
  *(undefined4 *)((int)this + 0x40) = 1;
  if (*(short *)(param_1 + 8) == 0x11) {
    iVar1 = _AIL_decompress_ADPCM_12(param_1 + 100,(int)this + 0x44,(int)this + 0x48);
  }
  else {
    if (*(short *)(param_1 + 8) != 0x55) {
      return 1;
    }
    iVar1 = _AIL_decompress_ASI_24
                      (*(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x20),&DAT_004dd0a8
                       ,(int)this + 0x44,(int)this + 0x48,0);
  }
  if (iVar1 == 0) {
    _AIL_unlock_0();
    return 1;
  }
  iVar1 = FUN_004937a0((int)this);
  if (iVar1 == 0) {
    DAT_004ea6e0 = DAT_004ea6e0 + *(int *)((int)this + 0x48);
    return 0;
  }
  _AIL_lock_0();
  _AIL_mem_free_lock_4(*(undefined4 *)((int)this + 0x44));
  _AIL_unlock_0();
  *(undefined4 *)((int)this + 0x44) = 0;
  return 1;
}


/* 004931c0 size=247 */

void __fastcall FUN_004931c0(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (*(undefined4 **)(param_1 + 4) != (undefined4 *)0x0) {
    **(undefined4 **)(param_1 + 4) = 0;
  }
  *(undefined4 *)(param_1 + 4) = 0;
  piVar2 = *(int **)(param_1 + 0x90);
  while (piVar2 != (int *)(param_1 + 0x8c)) {
    piVar1 = (int *)piVar2[1];
    (**(code **)(*(int *)piVar2[2] + 8))();
    *(int *)(*piVar2 + 4) = piVar2[1];
    *(int *)piVar2[1] = *piVar2;
    piVar2[1] = (int)piVar2;
    *piVar2 = (int)piVar2;
    *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + -1;
    piVar2[1] = (int)piVar2;
    *piVar2 = (int)piVar2;
    piVar2 = piVar1;
  }
  iVar3 = param_1 + 0x8c;
  *(int *)(param_1 + 0x90) = iVar3;
  *(int *)iVar3 = iVar3;
  *(undefined4 *)(param_1 + 0x88) = 0;
  puVar4 = (undefined4 *)(param_1 + 8);
  for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)(param_1 + 0x40) = 0;
  if (*(int *)(param_1 + 0x50) != 0) {
    iVar3 = FUN_00410170();
    puVar4 = *(undefined4 **)(param_1 + 0x50);
    (**(code **)*puVar4)(0);
    if ((puVar4 != (undefined4 *)0x0) && (iVar3 != -0x288)) {
      *puVar4 = *(undefined4 *)(iVar3 + 0x2a0);
      *(undefined4 **)(iVar3 + 0x2a0) = puVar4;
    }
    *(undefined4 *)(param_1 + 0x50) = 0;
  }
  if (*(int *)(param_1 + 0x44) != 0) {
    _AIL_lock_0();
    _AIL_mem_free_lock_4(*(undefined4 *)(param_1 + 0x44));
    _AIL_unlock_0();
    *(undefined4 *)(param_1 + 0x44) = 0;
    DAT_004ea6e0 = DAT_004ea6e0 - *(int *)(param_1 + 0x48);
    *(undefined4 *)(param_1 + 0x4c) = 0;
  }
  return;
}


/* 004937a0 size=303 */

undefined4 __fastcall FUN_004937a0(int param_1)

{
  int *piVar1;
  int iVar2;
  longlong lVar3;
  
  if (*(int *)(param_1 + 0x44) == 0) {
    return 1;
  }
  piVar1 = FUN_0049b410(*(int *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x48));
  if (piVar1 == (int *)0x0) {
    return 1;
  }
  iVar2 = FUN_004a31c0(piVar1);
  if (iVar2 == 0) {
    return 1;
  }
  (**(code **)(*piVar1 + 4))();
  iVar2 = *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 0x44);
  *(uint *)(param_1 + 100) = (uint)*(ushort *)(param_1 + 8);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_1 + 0x20);
  *(uint *)(param_1 + 0x78) = (uint)*(ushort *)(param_1 + 10);
  *(uint *)(param_1 + 0x74) = (uint)*(ushort *)(param_1 + 0x16);
  *(int *)(param_1 + 0x4c) = iVar2;
  *(int *)(param_1 + 0x68) = iVar2;
  *(int *)(param_1 + 0x84) = iVar2;
  *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_1 + 0x24);
  *(uint *)(param_1 + 0x80) = (uint)*(ushort *)(param_1 + 0x14);
  iVar2 = (int)((*(ushort *)(param_1 + 10) + 1) * (uint)*(ushort *)(param_1 + 0x16)) >> 3;
  if (iVar2 == 3) {
    *(undefined4 *)(param_1 + 0x60) = 2;
  }
  else if (iVar2 == 4) {
    *(undefined4 *)(param_1 + 0x60) = 1;
  }
  else if (iVar2 == 6) {
    *(undefined4 *)(param_1 + 0x60) = 3;
  }
  else {
    *(undefined4 *)(param_1 + 0x60) = 0;
  }
  lVar3 = __ftol();
  *(int *)(param_1 + 0x54) = (int)lVar3;
  return 0;
}


/* 004938d0 size=167 */

undefined4 __fastcall FUN_004938d0(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  
  if (*(int *)(param_1 + 0x50) != 0) {
    return 0;
  }
  iVar2 = FUN_00410170();
  piVar3 = *(int **)(iVar2 + 0x2a0);
  if (piVar3 == (int *)0x0) {
    FUN_004b7c60(iVar2 + 0x288,*(int *)(iVar2 + 0x290));
    piVar3 = *(int **)(iVar2 + 0x2a0);
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
      goto LAB_0049391b;
    }
  }
  *(int *)(iVar2 + 0x2a0) = *piVar3;
  if (piVar3 != (int *)0x0) {
    FUN_00493020(piVar3);
  }
LAB_0049391b:
  *(int **)(param_1 + 0x50) = piVar3;
  if (piVar3 == (int *)0x0) {
    return 1;
  }
  iVar2 = (**(code **)(*piVar3 + 8))(param_1);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_00410170();
  puVar1 = *(undefined4 **)(param_1 + 0x50);
  (**(code **)*puVar1)(0);
  if ((puVar1 != (undefined4 *)0x0) && (iVar2 != -0x288)) {
    *puVar1 = *(undefined4 *)(iVar2 + 0x2a0);
    *(undefined4 **)(iVar2 + 0x2a0) = puVar1;
  }
  *(undefined4 *)(param_1 + 0x50) = 0;
  return 1;
}


/* 00493980 size=194 */

undefined4 __fastcall FUN_00493980(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  
  piVar3 = *(int **)(param_1 + 0x90);
  while (piVar3 != (int *)(param_1 + 0x8c)) {
    piVar1 = (int *)piVar3[1];
    *(int **)(*piVar3 + 4) = piVar1;
    *(int *)piVar3[1] = *piVar3;
    piVar3[1] = (int)piVar3;
    *piVar3 = (int)piVar3;
    *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + -1;
    piVar3[1] = (int)piVar3;
    *piVar3 = (int)piVar3;
    piVar3 = piVar1;
  }
  iVar4 = param_1 + 0x8c;
  *(int *)(param_1 + 0x90) = iVar4;
  *(int *)iVar4 = iVar4;
  *(undefined4 *)(param_1 + 0x88) = 0;
  if (*(int *)(param_1 + 0x50) != 0) {
    iVar4 = FUN_00410170();
    puVar2 = *(undefined4 **)(param_1 + 0x50);
    (**(code **)*puVar2)(0);
    if ((puVar2 != (undefined4 *)0x0) && (iVar4 != -0x288)) {
      *puVar2 = *(undefined4 *)(iVar4 + 0x2a0);
      *(undefined4 **)(iVar4 + 0x2a0) = puVar2;
    }
    *(undefined4 *)(param_1 + 0x50) = 0;
  }
  if (*(int *)(param_1 + 0x44) != 0) {
    _AIL_lock_0();
    _AIL_mem_free_lock_4(*(undefined4 *)(param_1 + 0x44));
    _AIL_unlock_0();
    *(undefined4 *)(param_1 + 0x44) = 0;
    DAT_004ea6e0 = DAT_004ea6e0 - *(int *)(param_1 + 0x48);
    *(undefined4 *)(param_1 + 0x4c) = 0;
  }
  return 0;
}


/* 00493a50 size=37 */

bool __fastcall FUN_00493a50(int *param_1)

{
  int iVar1;
  
  (**(code **)(*param_1 + 0x10))();
  if (param_1[1] == 0) {
    return true;
  }
  iVar1 = (**(code **)(*param_1 + 0x18))();
  return iVar1 != 0;
}


/* 00493a80 size=139 */

undefined4 __thiscall FUN_00493a80(void *this,int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  if ((*(int *)((int)this + 0x44) == 0) && (*(int *)((int)this + 4) != 0)) {
    iVar3 = (**(code **)(*(int *)this + 0x14))();
    if (iVar3 != 0) {
      return 1;
    }
  }
  if ((((*(short *)((int)this + 8) == 0x11) || (*(short *)((int)this + 8) == 0x55)) &&
      ((*(uint *)((int)this + 0x28) & 1) == 0)) &&
     (((*(uint *)((int)this + 0x28) & 4) != 0 && (*(int *)((int)this + 0x50) == 0)))) {
    iVar3 = FUN_004938d0((int)this);
    if (iVar3 != 0) {
      return 1;
    }
  }
  iVar3 = *(int *)((int)this + 0x8c);
  *(int *)(param_1 + 0x6c) = param_1;
  piVar1 = (int *)(param_1 + 100);
  *piVar1 = iVar3;
  piVar2 = *(int **)(iVar3 + 4);
  *(int **)(param_1 + 0x68) = piVar2;
  *piVar2 = (int)piVar1;
  *(int **)(*piVar1 + 4) = piVar1;
  *(int *)((int)this + 0x88) = *(int *)((int)this + 0x88) + 1;
  return 0;
}


/* 00493b10 size=128 */

undefined4 __thiscall FUN_00493b10(void *this,int param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)(param_1 + 100);
  *(undefined4 *)(*piVar2 + 4) = *(undefined4 *)(param_1 + 0x68);
  **(int **)(param_1 + 0x68) = *piVar2;
  *(int **)(param_1 + 0x68) = piVar2;
  *piVar2 = (int)piVar2;
  iVar3 = *(int *)((int)this + 0x88) + -1;
  *(int *)((int)this + 0x88) = iVar3;
  if (((*(int *)((int)this + 0x50) == 0) || ((*(byte *)((int)this + 0x28) & 4) == 0)) ||
     (iVar3 != 0)) {
    return 0;
  }
  iVar3 = FUN_00410170();
  puVar1 = *(undefined4 **)((int)this + 0x50);
  (**(code **)*puVar1)(0);
  if ((puVar1 != (undefined4 *)0x0) && (iVar3 != -0x288)) {
    *puVar1 = *(undefined4 *)(iVar3 + 0x2a0);
    *(undefined4 **)(iVar3 + 0x2a0) = puVar1;
  }
  *(undefined4 *)((int)this + 0x50) = 0;
  return 0;
}


/* 00493b90 size=64 */

int __fastcall FUN_00493b90(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x88) == 0) {
    return 0;
  }
  iVar2 = *(int *)(*(int *)(param_1 + 0x90) + 4);
  iVar3 = *(int *)(*(int *)(param_1 + 0x90) + 8);
  while (iVar2 != param_1 + 0x8c) {
    piVar1 = (int *)(iVar2 + 8);
    iVar2 = *(int *)(iVar2 + 4);
    if (*(uint *)(*piVar1 + 0x24) < *(uint *)(iVar3 + 0x24)) {
      iVar3 = *piVar1;
    }
  }
  return iVar3;
}


/* 00493bd0 size=145 */

undefined4 __thiscall FUN_00493bd0(void *this,int param_1)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  if ((*(byte *)(param_1 + 0x48) & 0x20) != 0) {
    return 0;
  }
  if (1 < *(uint *)((int)this + 0x88)) {
    iVar5 = *(int *)((int)this + 0x90);
    bVar2 = false;
    if (iVar5 != (int)this + 0x8c) {
      do {
        if (bVar2) break;
        iVar1 = *(int *)(iVar5 + 8);
        iVar5 = *(int *)(iVar5 + 4);
        if ((((iVar1 != 0) && (iVar1 != param_1)) &&
            ((*(int *)(iVar1 + 0x4c) != 0 || (*(int *)(iVar1 + 0x50) != 0)))) &&
           ((uVar3 = *(int *)(iVar1 + 0x24) - *(int *)(param_1 + 0x24), uVar4 = (int)uVar3 >> 0x1f,
            (int)((uVar3 ^ uVar4) - uVar4) < 5 &&
            (*(uint *)(param_1 + 0x60) < *(uint *)(iVar1 + 0x60))))) {
          bVar2 = true;
        }
      } while (iVar5 != (int)this + 0x8c);
      if (bVar2) {
        *(short *)(param_1 + 0x5c) = *(short *)(param_1 + 0x5c) + 1;
        return 0;
      }
    }
  }
  return 1;
}


/* 00493c70 size=48 */

undefined4 FUN_00493c70(undefined1 *param_1,ushort *param_2,int param_3)

{
  undefined1 *puVar1;
  ushort uVar2;
  
  puVar1 = param_1 + param_3;
  for (; param_1 < puVar1; param_1 = param_1 + 1) {
    uVar2 = *param_2;
    param_2 = param_2 + 1;
    *param_1 = (char)(uVar2 + 0x8000 >> 8);
  }
  return 0;
}


/* 00493cd0 size=133 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00493cd0(void *this,int param_1,int *param_2,int param_3)

{
  int iVar1;
  int local_30;
  uint local_20;
  
  if (((param_1 != 0) && (param_2 != (int *)0x0)) && (param_3 != 0)) {
    FUN_00493d60((int)this);
    *(int *)((int)this + 0xc) = param_1;
    iVar1 = FUN_004a31c0(param_2);
    if (iVar1 != 0) {
      *(undefined4 *)((int)this + 0x18) = 0;
      *(undefined4 *)((int)this + 0x14) = 0;
      *(float *)((int)this + 0x10) = (float)local_20 / (float)local_30 + _DAT_004cbeec;
      return 1;
    }
  }
  return 0;
}


/* 00493d60 size=9 */

void __fastcall FUN_00493d60(int param_1)

{
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  return;
}


/* 00493da0 size=137 */

void __fastcall FUN_00493da0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  param_1[0xd] = 0x3f800000;
  param_1[0xf] = 0x3f800000;
  puVar1 = param_1 + 0x19;
  *param_1 = &PTR_FUN_004cd6ac;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[4] = 0;
  param_1[0x12] = 0;
  *(undefined1 *)(param_1 + 6) = 0;
  *(undefined1 *)(param_1 + 8) = 100;
  param_1[10] = 0;
  param_1[9] = 0;
  param_1[0xe] = 0;
  param_1[0xc] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[5] = 0xffff;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0xffffffff;
  *(undefined2 *)(param_1 + 0x17) = 0;
  param_1[7] = 0;
  param_1[0x18] = 0;
  param_1[0x1a] = puVar1;
  *puVar1 = puVar1;
  param_1[0x21] = 0xffffffff;
  *(undefined1 *)(param_1 + 0x30) = 0;
  puVar1 = param_1 + 0x29;
  iVar2 = 7;
  do {
    puVar1[-7] = 0xffffffff;
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


/* 00493e80 size=11 */

void __fastcall FUN_00493e80(int *param_1)

{
  *param_1 = (int)&PTR_FUN_004cd6ac;
  FUN_00494090(param_1);
  return;
}


/* 00493e90 size=497 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00493e90: lifted from original x86 -> lt_lifted.c */


