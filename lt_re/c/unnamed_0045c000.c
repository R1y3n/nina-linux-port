/* lithtech.exe decompilation - unnamed_0045c000 */
#include "ghidra_types.h"

/* 0045c020 size=166 */

undefined4 FUN_0045c020(int param_1,int *param_2)

{
  undefined2 extraout_var;
  
  if ((param_2 != (int *)0x0) && (param_1 != 0)) {
    (**(code **)(*param_2 + 0x48))(*(undefined2 *)(param_1 + 0x38));
    (**(code **)(*param_2 + 0x4c))(*(undefined4 *)(param_1 + 0x3c));
    (**(code **)(*param_2 + 0x4c))(*(undefined4 *)(param_1 + 0x40));
    (**(code **)(*param_2 + 0x4c))(*(undefined4 *)(param_1 + 0x20));
    (**(code **)(*param_2 + 0x4c))(*(undefined4 *)(param_1 + 0x1c));
    (**(code **)(*param_2 + 0x44))(*(undefined1 *)(param_1 + 0x24));
    (**(code **)(*param_2 + 0x48))(CONCAT22(extraout_var,*(undefined2 *)(param_1 + 0x18)));
    return 0;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_ILTModel_WriteTracker_004dab1c);
  }
  return 0x3c;
}


/* 0045c130 size=95 */

undefined4 FUN_0045c130(int param_1,int param_2)

{
  if (param_1 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_ILTModel_SetLooping_004dab24);
    }
    return 0x3c;
  }
  if (param_2 == 0) {
    *(ushort *)(param_1 + 0x18) = *(ushort *)(param_1 + 0x18) & 0xfffd;
    return 0;
  }
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 2;
  return 0;
}


/* 0045c1f0 size=95 */

undefined4 FUN_0045c1f0(int param_1,int param_2)

{
  if (param_1 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_ILTModel_SetPlaying_004dab2c);
    }
    return 0x3c;
  }
  if (param_2 == 0) {
    *(ushort *)(param_1 + 0x18) = *(ushort *)(param_1 + 0x18) & 0xfffe;
    return 0;
  }
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 1;
  return 0;
}


/* 0045c2b0 size=106 */

undefined4 FUN_0045c2b0(int param_1,uint param_2)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 8) != 0)) {
    FUN_00401200(param_1,param_2,*(uint *)(*(int *)(param_1 + 8) + 0x88) >> 7 & 1);
    return 0;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_ILTModel_SetCurAnim_004dab34);
  }
  return 0x3c;
}


/* 0045c320 size=81 */

undefined4 FUN_0045c320(int param_1)

{
  if (param_1 != 0) {
    FUN_004012e0(param_1);
    return 0;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_ILTModel_ResetAnim_004dab38);
  }
  return 0x3c;
}


/* 0045c650 size=33 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0045c650(void)

{
  _DAT_004ea710 = &PTR_LAB_004ccba4;
  DAT_004ea714 = 0;
  DAT_004ea720 = 0;
  DAT_004ea71c = 0;
  DAT_004ea718 = 0;
  return;
}


/* 0045c680 size=12 */

void FUN_0045c680(void)

{
  FUN_004b9cf5(&LAB_0045c690);
  return;
}


/* 0045c710 size=33 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0045c710(void)

{
  _DAT_004ea6f8 = &PTR_LAB_004ccbd4;
  DAT_004ea6fc = 0;
  DAT_004ea708 = 0;
  DAT_004ea704 = 0;
  DAT_004ea700 = 0;
  return;
}


/* 0045c740 size=12 */

void FUN_0045c740(void)

{
  FUN_004b9cf5(&LAB_0045c750);
  return;
}


/* 0045c7c0 size=48 */

undefined4 __thiscall FUN_0045c7c0(void *this,int param_1,float *param_2,int param_3)

{
  uint uVar1;
  
  *(int *)((int)this + 4) = param_1;
  *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 0x1f8);
  uVar1 = FUN_0045c7f0(this,param_2,param_3);
  *(uint *)((int)this + 0xc) = uVar1;
  return 1;
}


/* 0045c7f0 size=327 */

/* FUN_0045c7f0: lifted from original x86 -> lt_lifted.c */


/* 0045c940 size=200 */

undefined4 __fastcall FUN_0045c940(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_2e8 [2];
  undefined1 auStack_2e6 [54];
  int iStack_2b0;
  undefined1 auStack_2ac [24];
  undefined4 auStack_294 [66];
  undefined4 uStack_18c;
  undefined1 *puStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  int *piStack_178;
  
  (**(code **)(**(int **)(param_1 + 4) + 0x28))(local_2e8);
  puVar1 = auStack_294;
  iVar3 = 8;
  do {
    puVar1[-3] = 0xffffffff;
    *puVar1 = 0xffffffff;
    puVar1[2] = 0;
    puVar1[-6] = 0;
    *(undefined2 *)(puVar1 + -5) = 0;
    *(undefined2 *)((int)puVar1 + -0x12) = 0;
    puVar1[-4] = 0;
    *(undefined2 *)(puVar1 + -2) = 0;
    *(undefined2 *)((int)puVar1 + -6) = 0;
    puVar1[-1] = 0;
    puVar1[1] = 0;
    puVar1 = puVar1 + 9;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uStack_180 = 0;
  uStack_17c = 0;
  uStack_18c = 0;
  puStack_188 = local_2e8 + -4;
  uStack_184 = 0;
  piStack_178 = *(int **)(param_1 + 4);
  (**(code **)(*piStack_178 + 0x38))(auStack_2ac);
  iVar3 = FUN_004a0a30(&iStack_2b0);
  if (iVar3 == 0) {
    uVar2 = FUN_00468720(*(int *)(param_1 + 8));
    FUN_00436670((byte *)s_Model__SetupTransforms_failed_fo_004daea0,uVar2);
    return 0;
  }
  return 1;
}


/* 0045ca10 size=263 */

undefined4 __thiscall FUN_0045ca10(void *this,uint *param_1,uint param_2,float *param_3,int param_4)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint *local_4;
  
  uVar5 = 0;
  if ((param_1 == (uint *)0x0) || (param_2 == 0)) {
    param_1 = (uint *)0x0;
    param_2 = *(uint *)(*(int *)((int)this + 8) + 0x3c);
  }
  if (param_4 != 0) {
    pfVar1 = param_3 + 7;
    iVar4 = param_4;
    do {
      pfVar1[1] = 0.0;
      pfVar1[5] = *pfVar1;
      pfVar1 = pfVar1 + 0xe;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (param_2 != 0) {
    local_4 = param_1;
    do {
      if (param_1 == (uint *)0x0) {
        uVar2 = uVar5;
      }
      else {
        uVar2 = *local_4;
      }
      *(uint *)((int)this + 0x10) = uVar2;
      iVar4 = *(int *)(*(int *)(*(int *)((int)this + 8) + 0x38) + uVar2 * 4);
      if ((*(uint *)(*(int *)((int)this + 4) + 0x24c) & 1 << ((byte)uVar2 & 0x1f)) == 0) {
        if (*(int *)((int)this + 0xc) != 0) {
          uVar2 = *(int *)((int)this + 0xc) - 1;
          if (uVar2 < *(uint *)(iVar4 + 0x3c)) {
            iVar4 = *(int *)(iVar4 + 0x38) + uVar2 * 0x24;
          }
          else {
            iVar4 = 0;
          }
        }
        iVar3 = FUN_0045cb20(iVar4);
        if (iVar3 == 0) {
          return 0;
        }
        FUN_0045cc80(this,iVar4);
        FUN_0045cdc0(this,iVar4);
        if (param_4 != 0) {
          iVar4 = param_4;
          pfVar1 = param_3;
          do {
            FUN_0045cf10(this,pfVar1);
            pfVar1 = pfVar1 + 0xe;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
      }
      uVar5 = uVar5 + 1;
      local_4 = local_4 + 1;
    } while (uVar5 < param_2);
  }
  return 1;
}


/* 0045cb20 size=346 */

undefined4 FUN_0045cb20(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((DAT_004ea718 < *(uint *)(param_1 + 8)) &&
     ((uVar1 = *(uint *)(param_1 + 8) + 0x20, uVar1 != DAT_004ea718 || (uVar1 == 0)))) {
    if (DAT_004ea714 != 0) {
      FUN_00433560(&DAT_004ea710,&DAT_004ecc58);
    }
    DAT_004ea718 = uVar1;
    if (uVar1 != 0) {
      DAT_004ea714 = FUN_0046b0a0(&DAT_004ecc58,0,DAT_004ea720 + uVar1);
      if (DAT_004ea714 == 0) {
        DAT_004ea718 = 0;
        DAT_004ea71c = 0;
        return 0;
      }
      DAT_004ea71c = DAT_004ea720;
    }
  }
  if ((DAT_004ea700 < *(uint *)(param_1 + 0x18)) &&
     ((uVar1 = *(uint *)(param_1 + 0x18) + 0x20, uVar1 != DAT_004ea700 || (uVar1 == 0)))) {
    if (DAT_004ea6fc != 0) {
      if (DAT_004ea6fc != 0) {
        (**(code **)(DAT_004ecc58 + 8))(DAT_004ea6fc);
      }
      DAT_004ea6fc = 0;
      DAT_004ea704 = 0;
    }
    DAT_004ea700 = uVar1;
    if (uVar1 != 0) {
      iVar4 = uVar1 + DAT_004ea708;
      iVar3 = (**(code **)(DAT_004ecc58 + 4))(iVar4 * 0x24);
      iVar2 = iVar3;
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          if (iVar2 != 0) {
            FUN_004798d0(iVar2);
          }
          iVar2 = iVar2 + 0x24;
        }
      }
      DAT_004ea6fc = iVar3;
      if (iVar3 == 0) {
        DAT_004ea700 = 0;
        DAT_004ea704 = 0;
        return 0;
      }
      DAT_004ea704 = DAT_004ea708;
    }
  }
  return 1;
}


/* 0045cc80 size=312 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0045cc80(void *this,int param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 *puVar6;
  float *pfVar7;
  float *pfVar8;
  uint uVar9;
  uint uVar10;
  float *pfVar11;
  int iVar12;
  
  iVar1 = *(int *)(*(int *)((int)this + 8) + 0x74);
  uVar10 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    iVar12 = 0;
    pfVar11 = (float *)(DAT_004ea714 + 8);
    do {
      puVar6 = (undefined4 *)(iVar12 + *(int *)(param_1 + 4));
      uVar9 = (uint)*(ushort *)(puVar6 + 1);
      fVar2 = _DAT_004cb524;
      fVar3 = _DAT_004cb524;
      fVar4 = _DAT_004cb524;
      if (uVar9 == 0) {
        fVar5 = 0.0;
      }
      else {
        fVar5 = 0.0;
        pfVar8 = (float *)*puVar6;
        do {
          pfVar7 = (float *)((int)pfVar8[4] * 0x40 + iVar1);
          uVar9 = uVar9 - 1;
          fVar4 = *pfVar8 * *pfVar7 +
                  pfVar7[1] * pfVar8[1] + pfVar7[3] * pfVar8[3] + pfVar7[2] * pfVar8[2] + fVar4;
          fVar3 = pfVar7[5] * pfVar8[1] +
                  pfVar7[7] * pfVar8[3] + pfVar7[4] * *pfVar8 + pfVar7[6] * pfVar8[2] + fVar3;
          fVar2 = pfVar7[9] * pfVar8[1] +
                  pfVar7[0xb] * pfVar8[3] + pfVar7[8] * *pfVar8 + pfVar7[10] * pfVar8[2] + fVar2;
          fVar5 = pfVar7[0xd] * pfVar8[1] +
                  pfVar7[0xf] * pfVar8[3] + pfVar7[0xc] * *pfVar8 + pfVar7[0xe] * pfVar8[2] + fVar5;
          pfVar8 = pfVar8 + 5;
        } while (uVar9 != 0);
      }
      fVar5 = _DAT_004cba94 / fVar5;
      uVar10 = uVar10 + 1;
      iVar12 = iVar12 + 0x20;
      pfVar11[-2] = fVar4 * fVar5;
      pfVar11[-1] = fVar3 * fVar5;
      *pfVar11 = fVar2 * fVar5;
      pfVar11 = pfVar11 + 3;
    } while (uVar10 < *(uint *)(param_1 + 8));
  }
  return;
}


/* 0045cdc0 size=333 */

void __thiscall FUN_0045cdc0(void *this,int param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  ushort *puVar8;
  float *pfVar9;
  int local_40;
  uint local_3c;
  int local_38;
  
  iVar7 = DAT_004ea714;
  iVar4 = *(int *)(param_1 + 0x18);
  *(int *)this = iVar4;
  local_3c = 0;
  if (iVar4 != 0) {
    local_40 = 0;
    local_38 = 0;
    do {
      pfVar9 = (float *)(local_38 + DAT_004ea6fc);
      puVar8 = (ushort *)(*(int *)(param_1 + 0x14) + local_40);
      pfVar1 = (float *)(iVar7 + (uint)*puVar8 * 0xc);
      *pfVar9 = *pfVar1;
      pfVar9[1] = pfVar1[1];
      pfVar9[2] = pfVar1[2];
      fVar5 = pfVar1[1];
      fVar6 = pfVar1[2];
      iVar4 = iVar7 + (uint)puVar8[1] * 0xc;
      fVar2 = *(float *)(iVar4 + 4);
      fVar3 = *(float *)(iVar4 + 8);
      pfVar9[3] = *(float *)(iVar7 + (uint)puVar8[1] * 0xc) - *pfVar1;
      pfVar9[4] = fVar2 - fVar5;
      pfVar9[5] = fVar3 - fVar6;
      iVar4 = iVar7 + (uint)puVar8[2] * 0xc;
      fVar2 = *(float *)(iVar4 + 4);
      fVar3 = *(float *)(iVar4 + 8);
      pfVar9[6] = *(float *)(iVar7 + (uint)puVar8[2] * 0xc) - *pfVar9;
      pfVar9[7] = fVar2 - pfVar9[1];
      local_3c = local_3c + 1;
      pfVar9[8] = fVar3 - pfVar9[2];
      local_38 = local_38 + 0x24;
      local_40 = local_40 + 0x20;
    } while (local_3c < *(uint *)this);
  }
  return;
}


/* 0045cf10 size=737 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0045cf10(void *this,float *param_1)

{
  float *pfVar1;
  float *this_00;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float10 fVar6;
  int local_60;
  uint local_5c;
  float local_54;
  float local_50;
  float local_4c;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_5c = 0;
  if (*(int *)this != 0) {
    local_60 = 0;
    do {
      pfVar2 = (float *)(local_60 + DAT_004ea6fc);
      pfVar1 = pfVar2 + 6;
      FUN_00413050(&local_30,param_1[4] * pfVar2[8] - param_1[5] * pfVar2[7],
                   param_1[5] * *pfVar1 - param_1[3] * pfVar2[8],
                   param_1[3] * pfVar2[7] - param_1[4] * *pfVar1);
      this_00 = pfVar2 + 3;
      local_4 = pfVar2[2];
      local_8 = pfVar2[1];
      local_c = *pfVar2;
      fVar3 = _DAT_004cba94 / (local_30 * *this_00 + local_28 * pfVar2[5] + local_2c * pfVar2[4]);
      FUN_00413050(&local_24,*param_1 - local_c,param_1[1] - local_8,param_1[2] - local_4);
      fVar4 = (local_30 * local_24 + local_1c * local_28 + local_20 * local_2c) * fVar3;
      if ((_DAT_004cb524 <= fVar4) && (fVar4 <= _DAT_004cba94)) {
        FUN_00440190(this_00,&local_18,local_24,local_20,local_1c);
        fVar5 = (local_18 * param_1[3] + local_10 * param_1[5] + local_14 * param_1[4]) * fVar3;
        if ((_DAT_004cb524 <= fVar5) && (fVar5 + fVar4 <= _DAT_004cba94)) {
          fVar6 = FUN_0041feb0(pfVar1,local_18,local_14,local_10);
          fVar6 = fVar6 * (float10)fVar3;
          if ((fVar6 < (float10)param_1[0xc]) && ((float10)param_1[6] < fVar6)) {
            param_1[0xc] = (float)fVar6;
            param_1[8] = 1.4013e-45;
            local_54 = pfVar2[4] * pfVar2[8] - pfVar2[5] * pfVar2[7];
            local_50 = pfVar2[5] * *pfVar1 - *this_00 * pfVar2[8];
            local_4c = *this_00 * pfVar2[7] - pfVar2[4] * *pfVar1;
            fVar3 = SQRT(local_50 * local_50 + local_4c * local_4c + local_54 * local_54);
            if (fVar3 != _DAT_004cb524) {
              fVar3 = _DAT_004cba94 / fVar3;
              local_54 = fVar3 * local_54;
              local_50 = fVar3 * local_50;
              local_4c = fVar3 * local_4c;
            }
            param_1[9] = local_54;
            param_1[10] = local_50;
            param_1[0xb] = local_4c;
            param_1[0xd] = *(float *)((int)this + 0x10);
          }
        }
      }
      local_5c = local_5c + 1;
      local_60 = local_60 + 0x24;
    } while (local_5c < *(uint *)this);
  }
  return;
}


/* 0045dcc0 size=279 */

undefined4 __thiscall FUN_0045dcc0(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined4 unaff_retaddr;
  
  uVar3 = *(uint *)((int)this + 8);
  if (param_1 < uVar3) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = *(int *)((int)this + 0xc) + (uVar3 - param_1);
    return 1;
  }
  if ((uVar3 < param_1) && (uVar2 = *(int *)((int)this + 0xc) + uVar3, param_1 <= uVar2)) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = uVar2 - param_1;
    return 1;
  }
  if (param_1 == uVar3) {
    return 1;
  }
  iVar5 = param_1 + *(int *)((int)this + 0x10);
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(iVar5 * 0x24);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  for (; iVar5 != 0; iVar5 = iVar5 + -1) {
  }
  uVar3 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar3 = param_1;
  }
  if (param_1 == 0) {
    uVar8 = 0;
    if (uVar3 == 0) goto LAB_0045dd90;
    iVar5 = 0;
    do {
      puVar7 = (undefined4 *)(iVar5 + *(int *)((int)this + 4));
      puVar6 = (undefined4 *)(iVar5 + (int)puVar1);
      iVar5 = iVar5 + 0x24;
      uVar3 = uVar3 - 1;
      for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar6 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar6 = puVar6 + 1;
      }
    } while (uVar3 != 0);
  }
  else {
    puVar6 = *(undefined4 **)((int)this + 4);
    puVar7 = puVar1;
    for (uVar3 = uVar3 * 0x24 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
  }
  uVar8 = unaff_retaddr;
LAB_0045dd90:
  iVar5 = *(int *)((int)this + 4);
  if (iVar5 != 0) {
    if (iVar5 != 0) {
      (**(code **)(*param_2 + 8))(iVar5);
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 **)((int)this + 4) = puVar1;
  *(undefined4 *)((int)this + 8) = uVar8;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  return 1;
}


/* 0045dde0 size=302 */

undefined4 __thiscall FUN_0045dde0(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *unaff_EBP;
  undefined4 *puVar6;
  
  uVar3 = *(uint *)((int)this + 8);
  if (param_1 < uVar3) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = *(int *)((int)this + 0xc) + (uVar3 - param_1);
    return 1;
  }
  if ((uVar3 < param_1) && (uVar2 = *(int *)((int)this + 0xc) + uVar3, param_1 <= uVar2)) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = uVar2 - param_1;
    return 1;
  }
  if (param_1 == uVar3) {
    return 1;
  }
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))((param_1 + *(int *)((int)this + 0x10)) * 0xc);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  uVar3 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar3 = param_1;
  }
  if (param_1 == 0) {
    if (uVar3 == 0) goto LAB_0045dec4;
    iVar4 = 0;
    do {
      puVar6 = (undefined4 *)(iVar4 + (int)puVar1);
      puVar5 = (undefined4 *)(*(int *)((int)this + 4) + iVar4);
      iVar4 = iVar4 + 0xc;
      *puVar6 = *puVar5;
      puVar6[1] = puVar5[1];
      puVar6[2] = puVar5[2];
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
  else {
    puVar6 = *(undefined4 **)((int)this + 4);
    puVar5 = puVar1;
    for (uVar3 = uVar3 * 0xc >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar5 = puVar5 + 1;
    }
    for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
  }
  param_3 = param_2;
LAB_0045dec4:
  iVar4 = *(int *)((int)this + 4);
  if (iVar4 != 0) {
    if (iVar4 != 0) {
      (**(code **)(*param_3 + 8))(iVar4);
      puVar1 = unaff_EBP;
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 **)((int)this + 4) = puVar1;
  *(uint *)((int)this + 8) = param_1;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  return 1;
}


/* 0045df40 size=41 */

void __cdecl FUN_0045df40(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 4))(param_3 * 0x24);
  if (iVar1 == 0) {
    return;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
  }
  return;
}


/* 0045df70 size=2518 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0045df70: lifted from original x86 -> lt_lifted.c */


/* 0045ea50 size=52 */

undefined4 __cdecl FUN_0045ea50(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x34))();
  if ((iVar1 == 0) &&
     (((param_1[0x22] & 0x2000U) == 0 ||
      (((char)param_1[0x2f] != '\x02' && ((char)param_1[0x2f] != '\t')))))) {
    return 0;
  }
  return 1;
}


/* 0045ea90 size=64 */

void __cdecl FUN_0045ea90(int param_1)

{
  int *piVar1;
  
  if (*(int *)(param_1 + 0xec) == 0) {
    *(undefined4 *)(param_1 + 0xf0) = 0;
    return;
  }
  piVar1 = (int *)(param_1 + 0x118);
  *(undefined4 *)(*piVar1 + 4) = *(undefined4 *)(param_1 + 0x11c);
  **(int **)(param_1 + 0x11c) = *piVar1;
  *(int **)(param_1 + 0x11c) = piVar1;
  *piVar1 = (int)piVar1;
  *(undefined4 *)(param_1 + 0xec) = 0;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  return;
}


/* 0045ead0 size=63 */

void __cdecl FUN_0045ead0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x110);
  while (iVar1 != param_1 + 0x10c) {
    iVar2 = *(int *)(iVar1 + 8);
    iVar1 = *(int *)(iVar1 + 4);
    FUN_0045ea90(iVar2);
    *(uint *)(iVar2 + 0x124) = *(uint *)(iVar2 + 0x124) | 0x40;
  }
  return;
}


/* 0045eb10 size=76 */

void __cdecl FUN_0045eb10(int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  
  FUN_0045ea90(param_1);
  if (param_2 != 0) {
    if ((*(byte *)(param_2 + 0x8c) & 0x40) != 0) {
      return;
    }
    piVar1 = (int *)(param_1 + 0x118);
    *piVar1 = param_2 + 0x10c;
    piVar2 = *(int **)(param_2 + 0x110);
    *(int **)(param_1 + 0x11c) = piVar2;
    *piVar2 = (int)piVar1;
    *(int **)(*piVar1 + 4) = piVar1;
  }
  *(int *)(param_1 + 0xec) = param_2;
  *(undefined4 *)(param_1 + 0xf0) = param_3;
  return;
}


/* 0045eb60 size=42 */

void __cdecl FUN_0045eb60(uint param_1)

{
  FUN_00431760(param_1);
  FUN_00428970(param_1,(float *)(param_1 + 0x1f8),*(uint *)(param_1 + 0x88) >> 0xe & 1);
  return;
}


/* 0045eb90 size=856 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0045eb90: lifted from original x86 -> lt_lifted.c */


/* 0045eef0 size=51 */

void __cdecl FUN_0045eef0(void *param_1)

{
  FUN_00431760((int)param_1);
  FUN_0045eb90(param_1,(float *)((int)param_1 + 0x1f8));
  FUN_00428970((uint)param_1,(float *)((int)param_1 + 0x1f8),
               *(uint *)((int)param_1 + 0x88) >> 0xe & 1);
  return;
}


/* 0045ef30 size=1953 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0045ef30: lifted from original x86 -> lt_lifted.c */


/* 0045f6e0 size=142 */

undefined4 __cdecl
FUN_0045f6e0(float *param_1,float *param_2,float *param_3,float *param_4,float param_5)

{
  float fVar1;
  
  fVar1 = -param_5;
  if (*param_1 - *param_4 < fVar1) {
    if ((((param_5 < *param_2 - *param_3) && (param_1[1] - param_4[1] < fVar1)) &&
        (param_5 < param_2[1] - param_3[1])) &&
       ((param_1[2] - param_4[2] < fVar1 && (param_5 < param_2[2] - param_3[2])))) {
      return 1;
    }
  }
  return 0;
}


/* 0045f770 size=2915 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0045f770: lifted from original x86 -> lt_lifted.c */


