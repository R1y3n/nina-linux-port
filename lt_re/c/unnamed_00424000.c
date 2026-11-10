/* lithtech.exe decompilation - unnamed_00424000 */
#include "ghidra_types.h"

/* 00424080 size=12 */

void FUN_00424080(void)

{
  FUN_004206a0(&DAT_004e9500);
  return;
}


/* 00424090 size=19 */

void __cdecl FUN_00424090(byte param_1)

{
  FUN_00420080(&DAT_004e9500,param_1);
  return;
}


/* 004240b0 size=26 */

void __fastcall FUN_004240b0(undefined4 *param_1)

{
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *param_1 = &PTR_LAB_004cbfa4;
  return;
}


/* 004240d0 size=30 */

undefined4 * __thiscall FUN_004240d0(void *this,byte param_1)

{
  FUN_004240f0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004240f0 size=7 */

void __fastcall FUN_004240f0(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cbf20;
  return;
}


/* 00424110 size=227 */

bool __fastcall FUN_00424110(int *param_1)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  
  bVar3 = false;
  iVar2 = param_1[1];
  if (iVar2 == 0) {
    iVar2 = param_1[2];
    param_1[2] = iVar2 + 1;
    if (DAT_004e9514 <= iVar2 + 1) {
      param_1[1] = 1;
      param_1[3] = 0;
      iVar2 = (**(code **)(*param_1 + 8))();
      bVar3 = iVar2 == 0;
    }
  }
  else if (iVar2 == 1) {
    piVar1 = param_1 + 3;
    if (param_1[3] == 0) {
      iVar2 = FUN_00434ff0(DAT_004e953c);
      *piVar1 = iVar2;
      param_1[4] = 0;
    }
    do {
      iVar2 = FUN_00435040(piVar1);
      param_1[4] = iVar2;
      if (*piVar1 == 0) break;
    } while (iVar2 == 0);
    if (*piVar1 == 0) {
      param_1[1] = 2;
      param_1[5] = -1;
      iVar2 = (**(code **)(*param_1 + 8))();
      return iVar2 != 0;
    }
  }
  else if (iVar2 == 2) {
    iVar2 = FUN_00437690();
    if (param_1[2] < iVar2) {
      param_1[5] = param_1[5] + 1;
      return true;
    }
    return false;
  }
  return !bVar3;
}


/* 00424200 size=99 */

undefined * __fastcall FUN_00424200(int param_1)

{
  int iVar1;
  undefined **ppuVar2;
  
  iVar1 = *(int *)(param_1 + 4);
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 8) < DAT_004e9514) {
      return *(undefined **)(DAT_004e9510 + *(int *)(param_1 + 8) * 0xc);
    }
  }
  else if (iVar1 == 1) {
    if (*(int *)(param_1 + 0x10) != 0) {
      iVar1 = FUN_00434fd0(*(int *)(param_1 + 0x10));
      return *(undefined **)(iVar1 + 0x10);
    }
  }
  else if (iVar1 == 2) {
    iVar1 = FUN_00437690();
    if (*(int *)(param_1 + 0x14) < iVar1) {
      ppuVar2 = FUN_00437680();
      return ppuVar2[*(int *)(param_1 + 0x14) * 5];
    }
  }
  return (undefined *)0x0;
}


/* 004242e0 size=47 */

undefined8 FUN_004242e0(void)

{
  undefined8 uVar1;
  LARGE_INTEGER local_8;
  
  QueryPerformanceFrequency(&local_8);
  uVar1 = __aulldiv(local_8.s.LowPart,local_8.s.HighPart,DAT_004d73a0,DAT_004d73a4);
  return uVar1;
}


/* 00424310 size=41 */

LARGE_INTEGER * __thiscall FUN_00424310(void *this,int param_1)

{
  if (param_1 == 2) {
    FUN_00424340(this);
    return this;
  }
  if (param_1 == 1) {
    FUN_00424340(this);
  }
  return this;
}


/* 00424340 size=8 */

void __fastcall FUN_00424340(LARGE_INTEGER *param_1)

{
  QueryPerformanceCounter(param_1);
  return;
}


/* 00424350 size=81 */

undefined8 __fastcall FUN_00424350(uint *param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  LARGE_INTEGER local_10;
  LARGE_INTEGER local_8;
  
  QueryPerformanceCounter(&local_10);
  QueryPerformanceFrequency(&local_8);
  lVar1 = __allmul(local_10.s.LowPart - *param_1,
                   (local_10.s.HighPart - param_1[1]) - (uint)(local_10.s.LowPart < *param_1),1000,0
                  );
  uVar2 = __alldiv((uint)lVar1,(uint)((ulonglong)lVar1 >> 0x20),local_8.s.LowPart,local_8.s.HighPart
                  );
  return uVar2;
}


/* 004243c0 size=58 */

undefined8 __fastcall FUN_004243c0(uint *param_1)

{
  undefined8 uVar1;
  LARGE_INTEGER local_8;
  
  QueryPerformanceCounter(&local_8);
  uVar1 = __aulldiv(local_8.s.LowPart - *param_1,
                    (local_8.s.HighPart - param_1[1]) - (uint)(local_8.s.LowPart < *param_1),
                    DAT_004d73a0,DAT_004d73a4);
  return uVar1;
}


/* 00424400 size=9 */

void __cdecl FUN_00424400(LARGE_INTEGER *param_1)

{
  FUN_00424340(param_1);
  return;
}


/* 00424410 size=9 */

undefined8 __cdecl FUN_00424410(uint *param_1)

{
  undefined8 uVar1;
  
  uVar1 = FUN_004243c0(param_1);
  return uVar1;
}


/* 004250e0 size=108 */

undefined4 __thiscall
FUN_004250e0(void *this,int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (((param_1 != 0) && (param_2 != 0)) && (param_3 != 0)) {
    uVar1 = (**(code **)(*(int *)((int)this + 4) + 4))(param_1,param_2,param_3,param_4);
    return uVar1;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_ILTCSBase__InterpolateRotation_004d787c);
  }
  return 0x3c;
}


/* 00425150 size=95 */

void __thiscall FUN_00425150(void *this,int param_1,int param_2,int param_3)

{
  if (((param_1 != 0) && (param_2 != 0)) && (param_3 != 0)) {
    (**(code **)(*(int *)((int)this + 4) + 0x18))(param_1,param_2,param_3);
    return;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_ILTCSBase__SetupTransformationMa_004d789c);
  }
  return;
}


/* 00425330 size=95 */

void __thiscall FUN_00425330(void *this,int param_1,int param_2,int param_3)

{
  if (((param_1 != 0) && (param_2 != 0)) && (param_3 != 0)) {
    (**(code **)(*(int *)((int)this + 4) + 0x2c))(param_1,param_2,param_3);
    return;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_ILTCSBase__SetupRotationAroundPo_004d7954);
  }
  return;
}


/* 004253c0 size=1633 */

/* WARNING: Removing unreachable block (ram,0x0042589f) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004253c0: lifted from original x86 -> lt_lifted.c */


/* 00425a30 size=914 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_00425a30(float *param_1,float *param_2,float param_3,float *param_4,float *param_5,
            float *param_6,undefined4 *param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  undefined4 *puVar9;
  float10 fVar10;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c [3];
  
  local_24 = *param_4;
  local_3c = *param_2 - *param_1;
  local_38 = param_2[1] - param_1[1];
  local_34 = param_2[2] - param_1[2];
  local_20 = param_4[1];
  fVar1 = *param_5 - local_24;
  local_1c = param_4[2];
  fVar4 = param_5[1] - local_20;
  fVar3 = param_5[2] - local_1c;
  fVar2 = SQRT(fVar1 * fVar1 + fVar4 * fVar4 + fVar3 * fVar3);
  fVar5 = _DAT_004cba94 / fVar2;
  FUN_00413050(&local_24,fVar1 * fVar5,fVar4 * fVar5,fVar3 * fVar5);
  local_10 = param_4[2];
  local_14 = param_4[1];
  local_18 = *param_4;
  FUN_00413050(&local_30,*param_1 - local_18,param_1[1] - local_14,param_1[2] - local_10);
  fVar1 = local_24 * local_3c + local_20 * local_38 + local_1c * local_34;
  fVar3 = local_24 * local_30 + local_1c * local_28 + local_20 * local_2c;
  fVar5 = (local_3c * local_3c + local_38 * local_38 + local_34 * local_34) - fVar1 * fVar1;
  fVar4 = (local_30 * local_3c + local_2c * local_38 + local_28 * local_34) - fVar3 * fVar1;
  fVar4 = fVar4 + fVar4;
  if (fVar5 != _DAT_004cb524) {
    fVar6 = fVar4 * fVar4 -
            (((local_30 * local_30 + local_28 * local_28 + local_2c * local_2c) - fVar3 * fVar3) -
            param_3 * param_3) * fVar5 * _DAT_004cbfcc;
    fVar5 = _DAT_004cba94 / (fVar5 + fVar5);
    if ((fVar6 != _DAT_004cb524) && (_DAT_004cb524 < fVar6)) {
      fVar7 = (SQRT(fVar6) - fVar4) * fVar5;
      fVar5 = (-fVar4 - SQRT(fVar6)) * fVar5;
      if (fVar7 != fVar5) {
        if (fVar7 < fVar5) {
          fVar5 = fVar7;
        }
        *param_6 = fVar5;
        if ((((_DAT_004cb524 <= fVar5) && (fVar5 <= _DAT_004cba94)) &&
            (fVar3 = fVar5 * fVar1 + fVar3, _DAT_004cb524 <= fVar3)) && (fVar3 <= fVar2)) {
          FUN_00413050(&local_18,fVar5 * local_3c,local_38 * fVar5,local_34 * fVar5);
          FUN_00413050(&local_3c,local_18 + local_30,local_14 + local_2c,local_10 + local_28);
          fVar10 = FUN_0041feb0(&local_3c,local_24,local_20,local_1c);
          pfVar8 = (float *)FUN_0041ff50(&local_24,&local_18,(float)fVar10);
          puVar9 = (undefined4 *)FUN_0041ff20(&local_3c,local_c,*pfVar8,pfVar8[1],pfVar8[2]);
          *param_7 = *puVar9;
          param_7[1] = puVar9[1];
          param_7[2] = puVar9[2];
          FUN_00420000(param_7,1.0);
          return 1;
        }
      }
    }
  }
  return 0;
}


/* 00425dd0 size=607 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_00425dd0(float *param_1,float *param_2,float param_3,float *param_4,float *param_5,
            float *param_6)

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
  
  fVar1 = *param_2 - *param_1;
  fVar2 = param_2[1] - param_1[1];
  fVar3 = param_2[2] - param_1[2];
  fVar4 = *param_1 - *param_4;
  fVar5 = param_1[1] - param_4[1];
  fVar6 = param_1[2] - param_4[2];
  fVar8 = fVar1 * fVar1 + fVar2 * fVar2 + fVar3 * fVar3;
  fVar7 = fVar4 * fVar1 + fVar5 * fVar2 + fVar6 * fVar3;
  fVar7 = fVar7 + fVar7;
  if (fVar8 != _DAT_004cb524) {
    fVar9 = fVar7 * fVar7 -
            ((fVar4 * fVar4 + fVar5 * fVar5 + fVar6 * fVar6) - param_3 * param_3) * fVar8 *
            _DAT_004cbfcc;
    fVar8 = _DAT_004cba94 / (fVar8 + fVar8);
    if ((fVar9 != _DAT_004cb524) && (_DAT_004cb524 < fVar9)) {
      fVar10 = (SQRT(fVar9) - fVar7) * fVar8;
      fVar8 = (-fVar7 - SQRT(fVar9)) * fVar8;
      if (fVar10 != fVar8) {
        if (fVar10 < fVar8) {
          fVar8 = fVar10;
        }
        *param_5 = fVar8;
        if ((_DAT_004cb524 <= fVar8) && (fVar8 <= _DAT_004cba94)) {
          *param_6 = fVar8 * fVar1 + fVar4;
          param_6[1] = fVar2 * fVar8 + fVar5;
          param_6[2] = fVar8 * fVar3 + fVar6;
          fVar1 = SQRT(param_6[2] * param_6[2] + param_6[1] * param_6[1] + *param_6 * *param_6);
          if (fVar1 == _DAT_004cb524) {
            return 1;
          }
          fVar1 = _DAT_004cba94 / fVar1;
          *param_6 = fVar1 * *param_6;
          param_6[1] = fVar1 * param_6[1];
          param_6[2] = fVar1 * param_6[2];
          return 1;
        }
      }
    }
  }
  return 0;
}


/* 00426030 size=650 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

short __cdecl FUN_00426030(float *param_1,float param_2,int *param_3,int param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  float fVar6;
  short sVar7;
  float *pfVar8;
  uint uVar9;
  uint uVar10;
  int *local_74;
  int local_70;
  
  sVar7 = 10;
LAB_00426046:
  if ((sVar7 == 0) || (local_70 = 0, param_4 < 1)) {
    return sVar7;
  }
  local_74 = param_3;
  do {
    iVar3 = *local_74;
    if ((*(byte *)(*(int *)(iVar3 + 0x2c) + 0x30) & 1) != 0) {
      pfVar4 = *(float **)(iVar3 + 0x28);
      fVar1 = (*param_1 * *pfVar4 + param_1[1] * pfVar4[1] + param_1[2] * pfVar4[2]) - pfVar4[3];
      if (fVar1 < param_2 + _DAT_004cbeec) {
        uVar9 = 0;
        uVar10 = (uint)*(ushort *)(iVar3 + 0x54);
        if (uVar10 == 0) break;
        while( true ) {
          if (uVar9 == 0) {
            pfVar8 = *(float **)(iVar3 + 0x40 + uVar10 * 0x18);
          }
          else {
            pfVar8 = *(float **)(iVar3 + 0x40 + uVar9 * 0x18);
          }
          pfVar5 = *(float **)(iVar3 + 0x58 + uVar9 * 0x18);
          if (((pfVar5[2] - pfVar8[2]) * pfVar4[1] - (pfVar5[1] - pfVar8[1]) * pfVar4[2]) *
              ((*param_1 - fVar1 * *pfVar4) - *pfVar8) +
              (pfVar4[2] * (*pfVar5 - *pfVar8) - (pfVar5[2] - pfVar8[2]) * *pfVar4) *
              ((param_1[1] - fVar1 * pfVar4[1]) - pfVar8[1]) +
              ((pfVar5[1] - pfVar8[1]) * *pfVar4 - pfVar4[1] * (*pfVar5 - *pfVar8)) *
              ((param_1[2] - fVar1 * pfVar4[2]) - pfVar8[2]) < _DAT_004cbea0) break;
          uVar9 = uVar9 + 1;
          if (uVar10 <= uVar9) goto LAB_0042624b;
        }
      }
    }
    local_70 = local_70 + 1;
    local_74 = local_74 + 1;
    if (param_4 <= local_70) {
      return sVar7;
    }
  } while( true );
LAB_0042624b:
  pfVar4 = *(float **)(iVar3 + 0x28);
  sVar7 = sVar7 + -1;
  fVar6 = (param_2 - fVar1) + _DAT_004cbef0;
  fVar1 = pfVar4[1];
  fVar2 = pfVar4[2];
  *param_1 = fVar6 * *pfVar4 + *param_1;
  param_1[1] = fVar6 * fVar1 + param_1[1];
  param_1[2] = fVar6 * fVar2 + param_1[2];
  goto LAB_00426046;
}


/* 004262c0 size=250 */

/* FUN_004262c0: lifted from original x86 -> lt_lifted.c */


/* 004263c0 size=829 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_004263c0(float *param_1,int param_2)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  float10 fVar6;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  double local_78;
  float local_70;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c [3];
  float local_40 [4];
  float local_30 [4];
  float local_20 [3];
  undefined4 local_14 [4];
  
  pfVar1 = (float *)(param_2 + 0x9c);
  FUN_0044ec30(pfVar1,local_20,&local_84,local_14);
  local_9c = local_7c * -param_1[1] - local_80 * -param_1[2];
  local_98 = -param_1[2] * local_84 - local_7c * -*param_1;
  local_94 = local_80 * -*param_1 - -param_1[1] * local_84;
  fVar2 = SQRT(local_94 * local_94 + local_98 * local_98 + local_9c * local_9c);
  if (fVar2 != _DAT_004cb524) {
    fVar2 = _DAT_004cba94 / fVar2;
    local_9c = fVar2 * local_9c;
    local_98 = fVar2 * local_98;
    local_94 = fVar2 * local_94;
  }
  local_78 = *(double *)param_1;
  local_70 = param_1[2];
  fVar6 = (float10)FUN_004bb390();
  fVar2 = (float)fVar6;
  local_78 = (double)fVar6;
  iVar4 = FUN_004bb354((*(uint32_t*)((char*)&local_78+0)),(uint)((ulonglong)local_78 >> 0x20));
  if (iVar4 != 0) {
    return 0;
  }
  pfVar5 = (float *)(param_2 + 0xc4);
  FUN_0044ee70(local_30,pfVar5,&local_84);
  FUN_0044eff0(local_30,&local_9c,fVar2);
  fVar3 = SQRT(*(float *)(param_2 + 0xcc) * *(float *)(param_2 + 0xcc) +
               *(float *)(param_2 + 200) * *(float *)(param_2 + 200) + *pfVar5 * *pfVar5);
  FUN_0044ec30(local_30,local_4c,&local_58,&local_64);
  local_90 = local_64 * fVar3;
  local_8c = local_60 * fVar3;
  *pfVar5 = local_90;
  local_88 = local_5c * fVar3;
  *(float *)(param_2 + 200) = local_8c;
  *(float *)(param_2 + 0xcc) = local_88;
  pfVar5 = (float *)(param_2 + 0xd0);
  FUN_0044ee70(local_40,pfVar5,&local_84);
  FUN_0044eff0(local_40,&local_9c,fVar2);
  fVar3 = SQRT(*(float *)(param_2 + 0xd8) * *(float *)(param_2 + 0xd8) +
               *(float *)(param_2 + 0xd4) * *(float *)(param_2 + 0xd4) + *pfVar5 * *pfVar5);
  FUN_0044ec30(local_40,local_4c,&local_58,&local_64);
  local_90 = local_64 * fVar3;
  local_8c = local_60 * fVar3;
  *pfVar5 = local_90;
  local_88 = local_5c * fVar3;
  *(float *)(param_2 + 0xd4) = local_8c;
  *(float *)(param_2 + 0xd8) = local_88;
  FUN_0044eff0(pfVar1,&local_9c,fVar2);
  FUN_0044ec30(pfVar1,local_4c,&local_58,&local_64);
  iVar4 = FUN_004bb354(SUB84((double)local_58,0),(uint)((ulonglong)(double)local_58 >> 0x20));
  if (((iVar4 != 0) ||
      (iVar4 = FUN_004bb354(SUB84((double)local_54,0),(uint)((ulonglong)(double)local_54 >> 0x20)),
      iVar4 != 0)) ||
     (iVar4 = FUN_004bb354(SUB84((double)local_50,0),(uint)((ulonglong)(double)local_50 >> 0x20)),
     iVar4 != 0)) {
    FUN_00436670((byte *)s_SweptSphereOrient_Rotation_Inval_004d797c,SUB84((double)local_9c,0));
  }
  return 1;
}


/* 00426730 size=117 */

undefined4 __cdecl FUN_00426730(int param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  uVar3 = 0xffffffff;
  pcVar5 = (char *)*param_2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  puVar2 = FUN_00430f00(~uVar3 + 0x13);
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  *puVar2 = param_2[1];
  puVar2[1] = param_2[2];
  puVar2[2] = param_2[3];
  uVar3 = 0xffffffff;
  pcVar5 = (char *)*param_2;
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = (char *)(puVar2 + 4);
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
  puVar2[3] = *(undefined4 *)(param_1 + 0x12e8);
  *(undefined4 **)(param_1 + 0x12e8) = puVar2;
  return 0;
}


/* 004267b0 size=35 */

void __cdecl FUN_004267b0(int param_1,uint param_2,char param_3)

{
  dsys_interface_4356f0((LPSTR)(param_1 + 0x624),300,param_2,&param_3);
  return;
}


/* 004267e0 size=148 */

undefined4 __cdecl FUN_004267e0(int param_1,uint param_2)

{
  if ((param_2 & 0x2000000) == 0) {
    if ((param_2 & 0x4000000) != 0) {
      if (*(int **)(param_1 + 0x620) != (int *)0x0) {
        (**(code **)(**(int **)(param_1 + 0x620) + 0x54))(1,param_2 & 0xf9ffffff);
      }
      FUN_00471640(param_1,2);
      FUN_00436620((char *)(param_1 + 0x624));
      return 1;
    }
  }
  else {
    if (*(int **)(param_1 + 0x620) != (int *)0x0) {
      (**(code **)(**(int **)(param_1 + 0x620) + 0x54))(1,param_2 & 0xf9ffffff);
    }
    if (*(undefined4 **)(param_1 + 0x161c) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x161c))(1);
      *(undefined4 *)(param_1 + 0x161c) = 0;
    }
    FUN_004366d0((uint *)(param_1 + 0x624));
  }
  return 0;
}


/* 00426880 size=151 */

void __fastcall FUN_00426880(int param_1)

{
  int iVar1;
  short sVar2;
  ushort uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  
  if (*(int *)(param_1 + 0x620) != 0) {
    iVar6 = 0;
    sVar2 = FUN_00436510();
    if (sVar2 != 0) {
      do {
        iVar1 = **(int **)(param_1 + 0x620);
        uVar4 = FUN_00436540(iVar6);
        uVar5 = FUN_00436530(iVar6);
        (**(code **)(iVar1 + 0x10))(uVar5,uVar4);
        iVar6 = iVar6 + 1;
        uVar3 = FUN_00436510();
      } while (iVar6 < (int)(uint)uVar3);
    }
    iVar6 = 0;
    sVar2 = FUN_00436520();
    if (sVar2 != 0) {
      do {
        iVar1 = **(int **)(param_1 + 0x620);
        uVar4 = FUN_00436550(iVar6);
        (**(code **)(iVar1 + 0x14))(uVar4);
        iVar6 = iVar6 + 1;
        uVar3 = FUN_00436520();
      } while (iVar6 < (int)(uint)uVar3);
    }
    FUN_00436560();
    FUN_00436570();
  }
  return;
}


/* 00426920 size=86 */

void __thiscall FUN_00426920(void *this,int *param_1,int param_2)

{
  if ((*(int *)((int)this + 0x620) != 0) && (0 < param_2)) {
    do {
      if (*(char *)(*(int *)((int)this + 0x15bc) * 0xff + *param_1 + 0x13bc + (int)this) == '\0') {
        (**(code **)(**(int **)((int)this + 0x620) + 0xc))(*param_1);
      }
      else {
        (**(code **)(**(int **)((int)this + 0x620) + 8))();
      }
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}


/* 00426980 size=35 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00426980(int param_1)

{
  *(float *)(param_1 + 0x12f4) = *(float *)(param_1 + 0x12f4) + _DAT_004cba94;
  FUN_00470b90((float *)(param_1 + 0x12f4),*(float *)(param_1 + 0x1368));
  return;
}


/* 004269b0 size=225 */

undefined4 __cdecl FUN_004269b0(int param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  int iVar4;
  undefined4 *puVar5;
  
  bVar3 = true;
  *param_3 = 0;
  if (*param_2 != 0) {
    *param_3 = *param_2;
    bVar3 = false;
    goto LAB_00426a57;
  }
  puVar5 = *(undefined4 **)(param_1 + 0x1268);
  if (puVar5 == (undefined4 *)0x0) {
    FUN_004b7c60(param_1 + 0x1250,*(int *)(param_1 + 0x1258));
    puVar5 = *(undefined4 **)(param_1 + 0x1268);
    if (puVar5 != (undefined4 *)0x0) goto LAB_00426a03;
    puVar5 = (undefined4 *)0x0;
  }
  else {
LAB_00426a03:
    *(undefined4 *)(param_1 + 0x1268) = *puVar5;
    if (puVar5 != (undefined4 *)0x0) {
      FUN_0042e120(puVar5);
    }
  }
  *param_3 = (int)puVar5;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  iVar4 = *param_3;
  *(int *)(iVar4 + 0x10) = param_1 + 0x1224;
  *(int *)(iVar4 + 0x18) = iVar4;
  piVar2 = *(int **)(param_1 + 0x1228);
  piVar1 = (int *)(iVar4 + 0x10);
  *(int **)(iVar4 + 0x14) = piVar2;
  *piVar2 = (int)piVar1;
  *(int **)(*piVar1 + 4) = piVar1;
  *(int *)(param_1 + 0x1220) = *(int *)(param_1 + 0x1220) + 1;
  *(int **)(*param_3 + 0x24) = param_2;
  *param_2 = *param_3;
LAB_00426a57:
  if (*(int *)(*param_3 + 0xc) == 0) {
    FUN_00471750(*param_3,0);
    FUN_0043c4b0();
  }
  if (bVar3) {
    (**(code **)(**(int **)(param_1 + 0x620) + 0x6c))
              (*param_3 + 0x34,*(undefined4 *)(*param_3 + 0x38));
  }
  return 0;
}


/* 00426aa0 size=64 */

undefined4 __cdecl FUN_00426aa0(int param_1,int *param_2,int *param_3)

{
  int *piVar1;
  undefined4 uVar2;
  
  *param_3 = 0;
  piVar1 = FUN_004047a0(*(int *)(param_1 + 0x1644),param_2,'\x03');
  if (piVar1 == (int *)0x0) {
    return 0x16;
  }
  uVar2 = FUN_004269b0(param_1,piVar1,param_3);
  return uVar2;
}


/* 00426ae0 size=36 */

uint __cdecl FUN_00426ae0(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = FUN_00426aa0(param_1,param_2,(int *)&param_2);
  return ~-(uint)(iVar1 != 0) & (uint)param_2;
}


/* 00426b10 size=101 */

void __cdecl FUN_00426b10(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_2 + 4;
  *(undefined4 *)(param_2[4] + 4) = param_2[5];
  *(undefined4 *)param_2[5] = *puVar1;
  param_2[5] = puVar1;
  *puVar1 = puVar1;
  *(int *)(param_1 + 0x1220) = *(int *)(param_1 + 0x1220) + -1;
  if ((undefined4 *)param_2[9] != (undefined4 *)0x0) {
    *(undefined4 *)param_2[9] = 0;
  }
  FUN_00471770((int)param_2);
  FUN_0042e160(param_2);
  if ((param_2 != (undefined4 *)0x0) && (param_1 != -0x1250)) {
    *param_2 = *(undefined4 *)(param_1 + 0x1268);
    *(undefined4 **)(param_1 + 0x1268) = param_2;
  }
  return;
}


/* 00426b80 size=49 */

void __cdecl FUN_00426b80(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x1228);
  while (iVar2 != param_1 + 0x1224) {
    iVar1 = *(int *)(iVar2 + 4);
    FUN_00426b10(param_1,*(undefined4 **)(iVar2 + 8));
    iVar2 = iVar1;
  }
  return;
}


/* 00426bc0 size=13 */

void __cdecl FUN_00426bc0(int param_1)

{
  if (param_1 != 0) {
    *(byte *)(param_1 + 0x33) = *(byte *)(param_1 + 0x33) | 0x80;
  }
  return;
}


/* 00426bd0 size=75 */

void __cdecl FUN_00426bd0(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    iVar4 = 0;
    do {
      uVar3 = 0;
      iVar1 = *(int *)(param_1 + 0xc) + iVar4;
      if (*(int *)(iVar1 + 0x24) != 0) {
        do {
          FUN_00426bc0(*(int *)(*(int *)(iVar1 + 0x20) + uVar3 * 4));
          iVar1 = *(int *)(param_1 + 0xc) + iVar4;
          uVar3 = uVar3 + 1;
        } while (uVar3 < *(uint *)(iVar1 + 0x24));
      }
      uVar2 = uVar2 + 1;
      iVar4 = iVar4 + 0x3c;
    } while (uVar2 < *(uint *)(param_1 + 0x10));
  }
  return;
}


/* 00426c20 size=37 */

void __cdecl FUN_00426c20(int param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)(param_1 + 0x1228); iVar1 != param_1 + 0x1224; iVar1 = *(int *)(iVar1 + 4)) {
    *(undefined2 *)(*(int *)(iVar1 + 8) + 0x32) = 0;
  }
  return;
}


/* 00426c50 size=390 */

void __cdecl FUN_00426c50(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  for (iVar1 = *(int *)(param_1 + 0x1228); iVar1 != param_1 + 0x1224; iVar1 = *(int *)(iVar1 + 4)) {
    if ((*(ushort *)(*(int *)(iVar1 + 8) + 0x32) & 0x7fff) != 0) {
      FUN_00426bc0(*(int *)(iVar1 + 8));
    }
  }
  for (iVar1 = *(int *)(param_1 + 0x1208); iVar1 != param_1 + 0x1204; iVar1 = *(int *)(iVar1 + 4)) {
    FUN_00426bc0(*(int *)(*(int *)(iVar1 + 8) + 0xc0));
  }
  for (iVar1 = *(int *)(param_1 + 0x1228); iVar1 != param_1 + 0x1224; iVar1 = *(int *)(iVar1 + 4)) {
    FUN_00426bc0(*(int *)(*(int *)(iVar1 + 8) + 0x28));
  }
  if (((*(int *)(param_1 + 0x161c) != 0) && (param_1 != 0)) &&
     (uVar3 = 0, *(int *)(param_1 + 400) != 0)) {
    do {
      iVar1 = *(int *)(*(int *)(param_1 + 0x18c) + uVar3 * 4);
      FUN_00426de0(*(int *)(iVar1 + 4));
      iVar1 = *(int *)(iVar1 + 8);
      if (iVar1 != 0) {
        FUN_00426de0(iVar1);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_1 + 400));
  }
  iVar1 = *(int *)(param_1 + 0x428);
  if (iVar1 != param_1 + 0x424) {
    do {
      iVar4 = 4;
      piVar2 = (int *)(*(int *)(iVar1 + 8) + 0x1c0);
      do {
        FUN_00426bc0(*piVar2);
        piVar2 = piVar2 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      iVar1 = *(int *)(iVar1 + 4);
    } while (iVar1 != param_1 + 0x424);
  }
  for (iVar1 = *(int *)(param_1 + 0x1218); iVar1 != param_1 + 0x1214; iVar1 = *(int *)(iVar1 + 4)) {
    FUN_00426bd0(*(int *)(iVar1 + 8));
  }
  for (iVar1 = *(int *)(param_1 + 0x478); iVar1 != param_1 + 0x474; iVar1 = *(int *)(iVar1 + 4)) {
    FUN_00426bc0(*(int *)(*(int *)(iVar1 + 8) + 0x1f0));
  }
  if (DAT_004eaa9c != 0) {
    FUN_00426bc0(DAT_004eab64);
    piVar2 = &DAT_004eab68;
    do {
      FUN_00426bc0(*piVar2);
      piVar2 = piVar2 + 5;
    } while (piVar2 < &DAT_004eab90);
  }
  return;
}


/* 00426de0 size=49 */

void __cdecl FUN_00426de0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0x7c) != 0) {
    iVar2 = 0;
    do {
      FUN_00426bc0(*(int *)(iVar2 + 0x2c + *(int *)(param_1 + 0x78)));
      uVar1 = uVar1 + 1;
      iVar2 = iVar2 + 0x40;
    } while (uVar1 < *(uint *)(param_1 + 0x7c));
  }
  return;
}


/* 00426e20 size=38 */

void __cdecl FUN_00426e20(int param_1)

{
  int iVar1;
  
  iVar1 = 2;
  do {
    FUN_00426c20(param_1);
    FUN_00426c50(param_1);
    FUN_00426f90(param_1);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


/* 00426e50 size=61 */

void __cdecl FUN_00426e50(int param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)(param_1 + 0x1228); iVar1 != param_1 + 0x1224; iVar1 = *(int *)(iVar1 + 4)) {
    if (*(int *)(*(int *)(iVar1 + 8) + 0xc) == 0) {
      FUN_00471750(*(int *)(iVar1 + 8),0);
      FUN_0043c4b0();
    }
  }
  return;
}


/* 00426e90 size=249 */

void __cdecl FUN_00426e90(int param_1,int param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  
  piVar5 = (int *)(param_2 + 0x1c0);
  piVar3 = piVar5;
  uVar6 = 1;
  do {
    if (uVar6 < 4) {
      iVar4 = 4 - uVar6;
      piVar2 = piVar3;
      do {
        piVar2 = piVar2 + 1;
        if ((*piVar3 == *piVar2) && (*piVar3 != 0)) {
          *piVar2 = 0;
        }
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    piVar3 = piVar3 + 1;
    bVar8 = uVar6 < 4;
    uVar6 = uVar6 + 1;
  } while (bVar8);
  piVar3 = (int *)(param_2 + 0x250);
  iVar4 = 4;
  do {
    iVar7 = piVar3[-0x24];
    if (iVar7 != 0) {
      if (*piVar3 == 0) {
        if ((*(ushort *)(iVar7 + 0x32) & 0x7fff) == 0) {
          *(undefined2 *)(iVar7 + 0x32) = 0;
        }
      }
      else {
        *(byte *)(iVar7 + 0x33) = *(byte *)(iVar7 + 0x33) | 0x80;
      }
    }
    piVar3 = piVar3 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  for (iVar4 = *(int *)(param_1 + 0x428); iVar4 != param_1 + 0x424; iVar4 = *(int *)(iVar4 + 4)) {
    if (*(int *)(iVar4 + 8) != param_2) {
      piVar3 = (int *)(*(int *)(iVar4 + 8) + 0x1c0);
      iVar7 = 4;
      do {
        FUN_00426bc0(*piVar3);
        piVar3 = piVar3 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
  }
  iVar4 = 4;
  do {
    puVar1 = (undefined4 *)*piVar5;
    if ((puVar1 != (undefined4 *)0x0) && ((*(byte *)((int)puVar1 + 0x33) & 0x80) == 0)) {
      FUN_00426b10(param_1,puVar1);
      *piVar5 = 0;
    }
    piVar5 = piVar5 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}


/* 00426f90 size=55 */

void __cdecl FUN_00426f90(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x1228);
  while (iVar3 != param_1 + 0x1224) {
    iVar2 = *(int *)(iVar3 + 4);
    puVar1 = (undefined4 *)(iVar3 + 8);
    iVar3 = iVar2;
    if ((*(byte *)((int)*puVar1 + 0x33) & 0x80) == 0) {
      FUN_00426b10(param_1,(undefined4 *)*puVar1);
    }
  }
  return;
}


/* 00426fd0 size=134 */

void __cdecl FUN_00426fd0(int param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (*(uint *)(param_1 + 0x12f0) <= (param_2 & 0xffff)) {
    iVar1 = (param_2 & 0xffff) + 100;
    puVar2 = FUN_00430f00(iVar1 * 8);
    puVar4 = puVar2;
    for (iVar3 = iVar1 * 2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar4 = 0;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    puVar4 = *(undefined4 **)(param_1 + 0x12ec);
    puVar5 = puVar2;
    for (iVar3 = (*(uint *)(param_1 + 0x12f0) & 0x1fffffff) << 1; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    FUN_00430fe0(*(undefined **)(param_1 + 0x12ec));
    *(undefined4 **)(param_1 + 0x12ec) = puVar2;
    *(int *)(param_1 + 0x12f0) = iVar1;
  }
  return;
}


/* 00427060 size=46 */

void __cdecl FUN_00427060(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = param_2 & 0xffff;
  if (uVar1 < *(uint *)(param_1 + 0x12f0)) {
    *(undefined1 *)(*(int *)(param_1 + 0x12ec) + uVar1 * 8) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x12ec) + 4 + uVar1 * 8) = 0;
  }
  return;
}


/* 00427090 size=42 */

undefined4 __cdecl FUN_00427090(int param_1,uint param_2)

{
  char *pcVar1;
  
  if (((param_2 & 0xffff) < *(uint *)(param_1 + 0x12f0)) &&
     (pcVar1 = (char *)(*(int *)(param_1 + 0x12ec) + (param_2 & 0xffff) * 8), *pcVar1 == '\x01')) {
    return *(undefined4 *)(pcVar1 + 4);
  }
  return 0;
}


/* 004270c0 size=34 */

int __cdecl FUN_004270c0(int param_1,uint param_2)

{
  if ((param_2 & 0xffff) < *(uint *)(param_1 + 0x12f0)) {
    return *(int *)(param_1 + 0x12ec) + (param_2 & 0xffff) * 8;
  }
  return 0;
}


/* 004270f0 size=135 */

void __cdecl FUN_004270f0(int param_1,int *param_2,float *param_3)

{
  bool bVar1;
  
  if (((*param_3 == (float)param_2[0x2b]) && (param_3[1] == (float)param_2[0x2c])) &&
     (param_3[2] == (float)param_2[0x2d])) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  param_2[0x2b] = (int)*param_3;
  param_2[0x2c] = (int)param_3[1];
  param_2[0x2d] = (int)param_3[2];
  FUN_004a3df0((void *)(param_1 + 0x6c),param_2);
  if ((bVar1) && ((char)param_2[0x2f] == '\x01')) {
    FUN_00427200(param_1,(int)param_2);
  }
  return;
}


/* 00427180 size=91 */

void __cdecl FUN_00427180(int param_1)

{
  undefined4 uVar1;
  
  if (0 < DAT_004e4420) {
    if ((*(char *)(param_1 + 0xbc) == '\x01') && (*(int *)(param_1 + 0x1f8) != 0)) {
      uVar1 = FUN_00468720(*(int *)(param_1 + 0x1f8));
      FUN_00436670((byte *)s_Model__s_has_suspiciously_large_i_004d79fc,uVar1);
      return;
    }
    FUN_00436670((byte *)s_An_object__type__d__has_suspicio_004d79bc,(int)*(char *)(param_1 + 0xbc))
    ;
  }
  return;
}


/* 004271e0 size=28 */

void __cdecl FUN_004271e0(int param_1,int *param_2)

{
  FUN_00427310(param_1,param_2,(float *)(param_2 + 0x65),1);
  return;
}


/* 00427200 size=271 */

void __cdecl FUN_00427200(int param_1,int param_2)

{
  int iVar1;
  float local_78;
  float local_74;
  float local_70;
  int local_6c;
  undefined4 local_68;
  int local_64;
  uint local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_8;
  undefined4 local_4;
  
  local_8 = 0;
  local_4 = 0;
  if (((*(byte *)(param_2 + 0x188) & 4) == 0) && (iVar1 = *(int *)(param_2 + 0x1f8), iVar1 != 0)) {
    if (((uint)*(ushort *)(param_2 + 0x208) < *(uint *)(iVar1 + 0x16c)) &&
       (((uint)*(ushort *)(param_2 + 0x1fc) < *(uint *)(iVar1 + 0x16c) &&
        (*(int *)(param_1 + 0x161c) != 0)))) {
      local_64 = param_2;
      iVar1 = *(int *)(iVar1 + 0x168) + (uint)*(ushort *)(param_2 + 0x208) * 0x20;
      local_6c = param_1 + 0x6c;
      local_68 = *(undefined4 *)(param_1 + 0x50c);
      local_60 = (uint)*(byte *)(param_2 + 0xbd);
      local_5c = 0;
      local_58 = 0;
      local_78 = *(float *)(iVar1 + 8) * *(float *)(param_2 + 0xac);
      local_74 = *(float *)(iVar1 + 0xc) * *(float *)(param_2 + 0xb0);
      local_70 = *(float *)(iVar1 + 0x10) * *(float *)(param_2 + 0xb4);
      FUN_00463150(&local_6c,&local_78,0,1);
    }
  }
  return;
}


/* 00427310 size=222 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00427310(int param_1,int *param_2,float *param_3,int param_4)

{
  if ((param_4 == 0) &&
     (((float)param_2[0x65] - *param_3) * ((float)param_2[0x65] - *param_3) +
      ((float)param_2[0x66] - param_3[1]) * ((float)param_2[0x66] - param_3[1]) +
      ((float)param_2[0x67] - param_3[2]) * ((float)param_2[0x67] - param_3[2]) < _DAT_004cbaec)) {
    return;
  }
  FUN_00468c10(param_2,*param_3,param_3[1],param_3[2]);
  if (_DAT_004cbfd0 < (float)param_2[0x6b]) {
    FUN_00427180((int)param_2);
  }
  if (param_1 != 0) {
    if (((char)param_2[0x2f] == '\x02') || ((char)param_2[0x2f] == '\t')) {
      FUN_0045eb60((uint)param_2);
    }
    FUN_004a3df0((void *)(param_1 + 0x6c),param_2);
  }
  return;
}


/* 004273f0 size=252 */

void __cdecl FUN_004273f0(int param_1,int *param_2,float *param_3)

{
  float local_6c;
  undefined4 local_68;
  int *local_64;
  uint local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_8;
  undefined4 local_4;
  
  local_6c = 0.0;
  local_68 = 0;
  local_64 = (int *)0x0;
  local_8 = 0;
  local_4 = 0;
  if (param_1 == 0) {
    param_2[0x27] = (int)*param_3;
    param_2[0x28] = (int)param_3[1];
    param_2[0x29] = (int)param_3[2];
    param_2[0x2a] = (int)param_3[3];
    return;
  }
  if (((char)param_2[0x2f] == '\x02') || ((char)param_2[0x2f] == '\t')) {
    local_68 = *(undefined4 *)(param_1 + 0x50c);
    local_6c = (float)(param_1 + 0x6c);
    local_60 = (uint)*(byte *)((int)param_2 + 0xbd);
    local_64 = param_2;
    local_5c = 0;
    local_58 = 0;
    FUN_004636a0(&local_6c,param_3,0);
    FUN_004a3df0((void *)(param_1 + 0x6c),param_2);
    return;
  }
  param_2[0x27] = (int)*param_3;
  param_2[0x28] = (int)param_3[1];
  param_2[0x29] = (int)param_3[2];
  param_2[0x2a] = (int)param_3[3];
  FUN_004a3df0((void *)(param_1 + 0x6c),param_2);
  return;
}


/* 004274f0 size=122 */

void __cdecl FUN_004274f0(int param_1,int *param_2,float *param_3,int *param_4)

{
  FUN_00468c10(param_2,*param_3,param_3[1],param_3[2]);
  param_2[0x27] = *param_4;
  param_2[0x28] = param_4[1];
  param_2[0x29] = param_4[2];
  param_2[0x2a] = param_4[3];
  if (param_1 != 0) {
    if (((char)param_2[0x2f] == '\x02') || ((char)param_2[0x2f] == '\t')) {
      FUN_0045eb60((uint)param_2);
    }
    FUN_004a3df0((void *)(param_1 + 0x6c),param_2);
  }
  return;
}


/* 004275a0 size=48 */

void __cdecl FUN_004275a0(int param_1,undefined4 *param_2)

{
  (**(code **)*param_2)
            ((*(int *)(param_1 + 0xc) != 0x10) + '\x02',*(undefined4 *)(param_1 + 0x1c),
             *(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14),
             *(undefined4 *)(param_1 + 0x18));
  return;
}


/* 004275e0 size=50 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004275e0(void)

{
  _DAT_004e9570 = &PTR_LAB_004cb514;
  FUN_0044df20((LPCRITICAL_SECTION)&DAT_004e9590);
  _DAT_004e9570 = &PTR_FUN_004cbfd4;
  FUN_004b7be0((uint *)&DAT_004e9574,0x24,8,8);
  return;
}


/* 00427620 size=12 */

void FUN_00427620(void)

{
  FUN_004b9cf5(&LAB_00427630);
  return;
}


/* 00427670 size=50 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00427670(void)

{
  _DAT_004e95a8 = &PTR_LAB_004cb514;
  FUN_0044df20((LPCRITICAL_SECTION)&DAT_004e95c8);
  _DAT_004e95a8 = &PTR_FUN_004cbfe4;
  FUN_004b7be0((uint *)&DAT_004e95ac,0x24,8,8);
  return;
}


/* 004276b0 size=12 */

void FUN_004276b0(void)

{
  FUN_004b9cf5(&LAB_004276c0);
  return;
}


/* 004276f0 size=60 */

void __fastcall FUN_004276f0(undefined4 *param_1)

{
  FUN_0044df50((LPCRITICAL_SECTION)&DAT_004e9590);
  (**(code **)*param_1)(0);
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = DAT_004e958c;
    DAT_004e958c = param_1;
  }
  FUN_0044df60((LPCRITICAL_SECTION)&DAT_004e9590);
  return;
}


/* 00427730 size=60 */

void __fastcall FUN_00427730(undefined4 *param_1)

{
  FUN_0044df50((LPCRITICAL_SECTION)&DAT_004e95c8);
  (**(code **)*param_1)(0);
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = DAT_004e95c4;
    DAT_004e95c4 = param_1;
  }
  FUN_0044df60((LPCRITICAL_SECTION)&DAT_004e95c8);
  return;
}


/* 00427770 size=13 */

void FUN_00427770(void)

{
  DAT_004e95e0 = 0;
  DAT_004e9568 = 0;
  return;
}


/* 00427780 size=341 */

undefined4 __cdecl FUN_00427780(byte *param_1,undefined4 *param_2)

{
  byte bVar1;
  HANDLE pvVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte local_118 [280];
  
  *param_2 = 0;
  pvVar2 = FUN_004bb45b((LPCSTR)param_1,(uint *)local_118);
  if (pvVar2 == (HANDLE)0xffffffff) {
    return 0xffffffff;
  }
  FUN_004bb5f0(pvVar2);
  uVar6 = 0xffffffff;
  pbVar8 = param_1;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    bVar1 = *pbVar8;
    pbVar8 = pbVar8 + 1;
  } while (bVar1 != 0);
  if ((local_118[0] & 0x10) == 0) {
    puVar3 = FUN_00430fb0(~uVar6 + 0x23);
    *puVar3 = 0;
    puVar4 = (undefined4 *)FUN_00430de0(0xd4);
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)0x0;
    }
    else {
      puVar4 = FUN_004b5dd0(puVar4);
    }
    puVar3[1] = puVar4;
    if (puVar4 == (undefined4 *)0x0) {
      return 0xfffffffe;
    }
    iVar5 = FUN_004b6000(puVar4,param_1,1,0);
    if (iVar5 == 0) {
      puVar4 = (undefined4 *)puVar3[1];
      if (puVar4 != (undefined4 *)0x0) {
        FUN_004b5ec0(puVar4);
        FUN_00430df0((undefined *)puVar4);
      }
      FUN_00430fe0((undefined *)puVar3);
      return 0xfffffffe;
    }
    FUN_004b6b20((void *)puVar3[1],&DAT_004d7a30);
    DAT_004e95e0 = 0;
    DAT_004e9568 = 0;
    InitializeCriticalSection((LPCRITICAL_SECTION)(puVar3 + 2));
  }
  else {
    puVar3 = FUN_00430fb0(~uVar6 + 0x23);
    *puVar3 = 1;
    puVar3[1] = 0;
  }
  uVar6 = 0xffffffff;
  do {
    pbVar8 = param_1;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pbVar8 = param_1 + 1;
    bVar1 = *param_1;
    param_1 = pbVar8;
  } while (bVar1 != 0);
  uVar6 = ~uVar6;
  pbVar8 = pbVar8 + -uVar6;
  pbVar9 = (byte *)(puVar3 + 8);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pbVar9 = *(undefined4 *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar9 = pbVar9 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pbVar9 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar9 = pbVar9 + 1;
  }
  *param_2 = puVar3;
  return 0;
}


/* 004278e0 size=82 */

void __cdecl FUN_004278e0(undefined *param_1)

{
  undefined4 *puVar1;
  
  if (param_1 != (undefined *)0x0) {
    puVar1 = *(undefined4 **)(param_1 + 4);
    if (puVar1 != (undefined4 *)0x0) {
      FUN_004b5ec0(puVar1);
      FUN_00430df0((undefined *)puVar1);
      *(undefined4 *)(param_1 + 4) = 0;
      DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 8));
    }
    DAT_004e95e0 = 0;
    DAT_004e9568 = 0;
    FUN_00430fe0(param_1);
  }
  return;
}


/* 00427940 size=17 */

undefined4 __cdecl FUN_00427940(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return 1;
  }
  return *param_1;
}


/* 00427960 size=300 */

undefined4 __cdecl FUN_00427960(int *param_1,char *param_2,undefined4 *param_3)

{
  HANDLE pvVar1;
  HANDLE pvVar2;
  undefined4 *puVar3;
  byte local_30c [12];
  undefined4 local_300;
  undefined4 local_2fc;
  char local_2f8 [260];
  CHAR local_1f4 [500];
  
  if (param_1 != (int *)0x0) {
    if (*param_1 == 1) {
      FUN_004b9f62(local_1f4,(byte *)s__s__s_004d7a34,param_1 + 8);
      pvVar1 = FUN_004bb45b(local_1f4,(uint *)local_30c);
      pvVar2 = pvVar1;
      while( true ) {
        if (pvVar2 == (HANDLE)0xffffffff) {
          FUN_004bb5f0(pvVar1);
          return 0;
        }
        if ((local_30c[0] & 0x10) == 0) break;
        pvVar2 = (HANDLE)FUN_004bb528(pvVar1,(uint *)local_30c);
      }
      _strncpy((char *)(param_3 + 1),local_2f8,0xff);
      *param_3 = 1;
      param_3[0x42] = local_2fc;
      param_3[0x41] = local_300;
      FUN_004bb5f0(pvVar1);
      return 1;
    }
    puVar3 = (undefined4 *)FUN_004b6ed0((void *)param_1[1],param_2);
    if (puVar3 != (undefined4 *)0x0) {
      _strncpy((char *)(param_3 + 1),(char *)*puVar3,0xff);
      *param_3 = 1;
      param_3[0x42] = puVar3[3];
      param_3[0x41] = puVar3[2];
      return 1;
    }
  }
  return 0;
}


/* 00427a90 size=50 */

undefined4 __cdecl FUN_00427a90(int *param_1,undefined4 param_2,undefined1 *param_3)

{
  if (param_1 == (int *)0x0) {
    return 0;
  }
  if (*param_1 == 1) {
    FUN_004b9f62(param_3,(byte *)s__s__s_004d7a34,param_1 + 8);
    return 1;
  }
  return 0;
}


/* 00427d50 size=32 */

undefined4 __thiscall FUN_00427d50(void *this,int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_004ba5a8(*(char **)((int)this + 0xc));
  *param_1 = iVar1 - *(int *)((int)this + 8);
  return 0;
}


