/* lithtech.exe decompilation - unnamed_00418000 */
#include "ghidra_types.h"

/* 00418000 size=136 */

void __cdecl FUN_00418000(float *param_1,float *param_2,float *param_3)

{
  *param_1 = (param_3[3] * *param_2 + param_3[2] * param_2[1] + param_2[3] * *param_3) -
             param_3[1] * param_2[2];
  param_1[1] = param_2[2] * *param_3 +
               param_3[3] * param_2[1] + (param_2[3] * param_3[1] - param_3[2] * *param_2);
  param_1[2] = param_3[3] * param_2[2] +
               ((param_3[1] * *param_2 + param_2[3] * param_3[2]) - *param_3 * param_2[1]);
  param_1[3] = ((param_3[3] * param_2[3] - *param_2 * *param_3) - param_3[1] * param_2[1]) -
               param_2[2] * param_3[2];
  return;
}


/* 004181c0 size=466 */

void __thiscall FUN_004181c0(void *this,void *param_1,float *param_2,char *param_3,uint param_4)

{
  int *this_00;
  byte bVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  uint uStack_10c;
  int *local_108;
  uint uStack_104;
  char acStack_100 [256];
  
  *(float *)((int)this + 0x1604) = *(float *)((int)this + 0x1368) + *(float *)((int)this + 0x1604);
  puVar2 = FUN_0046b170(&local_108,0x44c,0x44c);
  this_00 = (int *)*puVar2;
  if (this_00 != (int *)0x0) {
    (**(code **)(*this_00 + 4))();
  }
  if (local_108 != (int *)0x0) {
    (**(code **)(*local_108 + 8))();
  }
  if (DAT_004d82a0 < 2) {
    bVar1 = 2;
  }
  else {
    bVar1 = 0x3c;
    if (DAT_004d82a0 < 0x3d) {
      bVar1 = DAT_004d82a0;
    }
  }
  FUN_004183a0(this_00,bVar1);
  uStack_104 = (uint)(bVar1 != *(byte *)((int)this + 0x1608));
  *(byte *)((int)this + 0x1608) = bVar1;
  FUN_004183a0(this_00,(char)param_4);
  iVar4 = 0;
  if (0 < (int)param_4) {
    pcVar5 = param_3;
    do {
      FUN_004183a0(this_00,*pcVar5);
      acStack_100[iVar4] = *pcVar5;
      iVar4 = iVar4 + 1;
      pcVar5 = pcVar5 + 4;
    } while (iVar4 < (int)param_4);
  }
  if ((int)param_4 < 0x40) {
    uStack_10c = param_4;
  }
  else {
    uStack_10c = 0x40;
  }
  if ((((uStack_104 == 0) && ((int)param_4 < 0x41)) && (*(uint *)((int)this + 0x1600) == uStack_10c)
      ) && ((int)(*(ushort *)((int)this + 0xf38) - 1) < 1)) {
    bVar7 = true;
    uVar3 = uStack_10c;
    pcVar5 = (char *)((int)this + 0x15c0);
    pcVar6 = param_3;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (bVar7) goto LAB_0041837a;
  }
  *(undefined1 *)this_00[0x15] = 7;
  iVar4 = FUN_0046b320(this_00,(int)this + 0xf04);
  if (iVar4 == 0) {
    **(undefined1 **)((int)this + 0xf58) = 8;
    FUN_004657c0(param_1,(int *)((int)this + 0xf04),param_2,0);
  }
  if (0 < (int)(*(ushort *)((int)this + 0xf38) - 1)) {
    *(undefined2 *)((int)this + 0xf3c) = 1;
    *(undefined2 *)((int)this + 0xf38) = 1;
  }
  FUN_004657c0(param_1,this_00,param_2,0x80);
  pcVar5 = (char *)((int)this + 0x15c0);
  for (uVar3 = uStack_10c >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)param_3;
    param_3 = param_3 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar3 = uStack_10c & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar5 = *param_3;
    param_3 = param_3 + 1;
    pcVar5 = pcVar5 + 1;
  }
  *(uint *)((int)this + 0x1600) = uStack_10c;
  *(undefined4 *)((int)this + 0x1604) = 0;
LAB_0041837a:
  if (this_00 != (int *)0x0) {
    (**(code **)(*this_00 + 8))();
  }
  return;
}


/* 004183a0 size=348 */

/* WARNING: Removing unreachable block (ram,0x0041846c) */

void __thiscall FUN_004183a0(void *this,undefined1 param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if ((uint)*(ushort *)((int)this + 0x36) <= *(ushort *)((int)this + 0x38) + 1) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
    return;
  }
  if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1) {
    do {
      uVar1 = *(uint *)((int)this + 0x58);
      if (*(int *)((int)this + 0x5c) == 0) {
        iVar2 = FUN_0040c920(&DAT_004ecc58,0,*(int *)((int)this + 0x60) + uVar1 + 1);
        if (iVar2 != 0) {
          uVar4 = 0;
          if (uVar1 != 0) {
            do {
              uVar3 = uVar4 + 1;
              *(undefined1 *)(uVar4 + iVar2) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar3);
              uVar4 = uVar3;
            } while (uVar3 < uVar1);
          }
          uVar4 = uVar1;
          if (uVar1 < *(uint *)((int)this + 0x58)) {
            do {
              uVar4 = uVar4 + 1;
              *(undefined1 *)(uVar4 + iVar2) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar4);
            } while (uVar4 < *(uint *)((int)this + 0x58));
          }
          *(undefined1 *)(uVar1 + iVar2) = 0;
          if (*(int *)((int)this + 0x54) != 0) {
            FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x54));
            *(undefined4 *)((int)this + 0x54) = 0;
            *(undefined4 *)((int)this + 0x5c) = 0;
          }
          *(int *)((int)this + 0x54) = iVar2;
          *(undefined4 *)((int)this + 0x5c) = *(undefined4 *)((int)this + 0x60);
          goto LAB_00418488;
        }
      }
      else {
        *(int *)((int)this + 0x5c) = *(int *)((int)this + 0x5c) + -1;
        *(undefined1 *)(*(int *)((int)this + 0x54) + uVar1) = 0;
LAB_00418488:
        *(int *)((int)this + 0x58) = *(int *)((int)this + 0x58) + 1;
      }
    } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1);
  }
  *(undefined1 *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = param_1;
  *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 1;
  *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 1;
  return;
}


/* 00418530 size=83 */

void __cdecl FUN_00418530(int param_1)

{
  int *piVar1;
  longlong lVar2;
  
  if (*(int *)(param_1 + 0x161c) != 0) {
    lVar2 = __ftol();
    if ((int)lVar2 != 0) {
      for (piVar1 = *(int **)(param_1 + 0x1374); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
        FUN_0049ab30((int)(piVar1 + 3),(int)lVar2);
        if ((undefined4 *)piVar1[5] != (undefined4 *)0x0) {
          *(undefined4 *)(*piVar1 + 0x2c) = *(undefined4 *)piVar1[5];
        }
      }
    }
  }
  return;
}


/* 00418590 size=109 */

void __fastcall FUN_00418590(int param_1)

{
  undefined8 uVar1;
  LARGE_INTEGER local_c;
  int *local_4;
  
  DAT_004e6608 = 0;
  FUN_00424310(&local_c,0);
  local_4 = &DAT_004e6608;
  FUN_00424400(&local_c);
  FUN_00418530(param_1);
  FUN_00418710(param_1);
  FUN_00418600(param_1);
  FUN_004188d0(param_1);
  FUN_00418950(param_1);
  FUN_004189a0(param_1);
  uVar1 = FUN_00424410((uint *)&local_c);
  *local_4 = *local_4 + (int)uVar1;
  return;
}


/* 00418600 size=269 */

void __cdecl FUN_00418600(int param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  
  lVar6 = __ftol();
  if ((0 < (int)lVar6) && (iVar5 = *(int *)(param_1 + 0x478), iVar5 != param_1 + 0x474)) {
    do {
      piVar1 = *(int **)(iVar5 + 8);
      uVar2 = piVar1[0x22];
      piVar1[0x22] = uVar2 & 0xbfffffef;
      if (((uVar2 & 8) != 0) || (((uVar2 & 0x40000000) != 0 || (piVar1[0x8d] != 0)))) {
        piVar1[0x22] = uVar2 & 0xbfffffef | 0x10;
        if (piVar1[0x7e] != 0) {
          FUN_0049ab30((int)(piVar1 + 0x7f),(int)lVar6);
          if ((int *)piVar1[0x81] == (int *)0x0) {
            piVar1[0x7c] = 0;
          }
          else {
            piVar1[0x7c] = *(int *)piVar1[0x81];
          }
        }
        iVar3 = piVar1[0x8d];
        FUN_0046c030((int)piVar1);
        FUN_0046bb60((int)piVar1,*(float *)(param_1 + 0x1368));
        iVar4 = FUN_0046c060((int)piVar1);
        if ((0 < iVar3) || (iVar4 != 0)) {
          FUN_00427310(param_1,piVar1,(float *)(piVar1 + 0x65),1);
        }
        piVar1[0x8d] = 0;
      }
      iVar5 = *(int *)(iVar5 + 4);
    } while (iVar5 != param_1 + 0x474);
  }
  return;
}


/* 00418710 size=151 */

void __cdecl FUN_00418710(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  
  lVar4 = __ftol();
  iVar2 = (int)lVar4;
  if (0 < iVar2) {
    iVar3 = *(int *)(param_1 + 0x428);
    if (iVar3 != param_1 + 0x424) {
      do {
        for (uVar1 = *(uint *)(*(int *)(iVar3 + 8) + 0x220); uVar1 != 0;
            uVar1 = *(uint *)(uVar1 + 4)) {
          *(undefined1 **)(uVar1 + 0xc) = &LAB_004187b0;
          FUN_004010f0(uVar1,iVar2);
        }
        iVar3 = *(int *)(iVar3 + 4);
      } while (iVar3 != param_1 + 0x424);
    }
    for (iVar3 = *(int *)(param_1 + 0x448); iVar3 != param_1 + 0x444; iVar3 = *(int *)(iVar3 + 4)) {
      FUN_0049ab30(*(int *)(iVar3 + 8) + 0x1b0,iVar2);
    }
  }
  return;
}


/* 004188d0 size=126 */

void __cdecl FUN_004188d0(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  longlong lVar4;
  
  lVar4 = __ftol();
  if ((int)lVar4 != 0) {
    for (iVar1 = *(int *)(param_1 + 0x488); iVar1 != param_1 + 0x484; iVar1 = *(int *)(iVar1 + 4)) {
      iVar2 = *(int *)(iVar1 + 8);
      uVar3 = *(uint *)(iVar2 + 0x88);
      *(uint *)(iVar2 + 0x88) = uVar3 & 0xbfffffef;
      if ((((uVar3 & 8) != 0) || ((uVar3 & 0x40000000) != 0)) &&
         (*(uint *)(iVar2 + 0x88) = uVar3 & 0xbfffffef | 0x10, *(int *)(iVar2 + 0x1b8) != 0)) {
        FUN_0049ab30(iVar2 + 0x1bc,(int)lVar4);
      }
    }
  }
  return;
}


/* 00418950 size=78 */

void __cdecl FUN_00418950(int param_1)

{
  int iVar1;
  int *piVar2;
  
  for (iVar1 = *(int *)(param_1 + 0x498); iVar1 != param_1 + 0x494; iVar1 = *(int *)(iVar1 + 4)) {
    piVar2 = *(int **)(iVar1 + 8);
    if (piVar2[0x6d] != 0) {
      FUN_00427310(param_1,piVar2,(float *)(piVar2 + 0x65),1);
    }
    piVar2[0x6d] = 0;
  }
  return;
}


/* 004189a0 size=191 */

void __cdecl FUN_004189a0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  longlong lVar5;
  int local_c;
  undefined4 local_8;
  undefined2 local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  lVar5 = __ftol();
  if ((int)lVar5 != 0) {
    for (iVar1 = *(int *)(param_1 + 0x428); iVar1 != param_1 + 0x424; iVar1 = *(int *)(iVar1 + 4)) {
      iVar2 = 4;
      piVar4 = (int *)(*(int *)(iVar1 + 8) + 0x1c0);
      puVar3 = (undefined4 *)(*(int *)(iVar1 + 8) + 0x268);
      do {
        if (piVar4[0x24] != 0) {
          FUN_0049ab30((int)(puVar3 + -2),(int)lVar5);
          local_8 = *(undefined4 *)(*(int *)(*(int *)*puVar3 + 0x24) + 0x1c);
          local_c = 1;
          FUN_00426aa0(DAT_004e516c,&local_c,piVar4);
        }
        piVar4 = piVar4 + 1;
        puVar3 = puVar3 + 5;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}


/* 00418c60 size=211 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_00418c60(undefined4 *param_1)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  
  iVar3 = 0;
  pfVar1 = (float *)*param_1;
  pfVar4 = (float *)param_1[1];
  param_1[3] = 0x7cf0bdc2;
  param_1[4] = 0xfcf0bdc2;
  do {
    fVar2 = (pfVar4[1] * pfVar1[1] + *pfVar4 * *pfVar1 + pfVar4[2] * pfVar1[2]) - pfVar1[3];
    if ((float)param_1[3] <= fVar2) {
      if ((float)param_1[4] <= fVar2) {
        param_1[4] = fVar2;
        param_1[0xd] = iVar3;
      }
    }
    else {
      param_1[3] = fVar2;
      param_1[0xc] = iVar3;
    }
    pfVar4 = pfVar4 + 3;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 8);
  *(undefined4 *)param_1[5] = 1;
  if (((float)param_1[3] < _DAT_004cbea0) && (_DAT_004cbea0 <= (float)param_1[4])) {
    return 2;
  }
  if ((float)param_1[3] <= _DAT_004cbea0) {
    return 0;
  }
  return 1;
}


/* 00419020 size=1197 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00419020: lifted from original x86 -> lt_lifted.c */


/* 004194d0 size=436 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004194d0: lifted from original x86 -> lt_lifted.c */


/* 00419690 size=510 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00419690(void *this,float *param_1,float *param_2,int param_3,int param_4)

{
  float fVar1;
  float fVar2;
  
  fVar1 = (param_2[2] * param_1[2] + param_2[1] * param_1[1] + *param_2 * *param_1) - param_1[3];
  if (param_3 != 0) {
    *(float *)((int)this + 0x78) = fVar1;
  }
  if (param_4 != 0) {
    if (*(float *)((int)this + 0x30) <= fVar1) {
      return 1;
    }
    if (fVar1 <= -*(float *)((int)this + 0x30)) {
      return 0;
    }
    if (param_1[1] == (float)_DAT_004cbeb0) {
      if (*(float *)((int)this + 0x24) <= fVar1) {
        return 1;
      }
      if (-*(float *)((int)this + 0x24) < fVar1) {
        if (param_3 == 0) {
          return 2;
        }
        *(float *)((int)this + 0x7c) = *(float *)((int)this + 0x24) - fVar1;
        return 2;
      }
      return 0;
    }
    if ((*param_1 == (float)_DAT_004cbeb0) && (param_1[2] == (float)_DAT_004cbeb0)) {
      if (*(float *)((int)this + 0x28) <= fVar1) {
        return 1;
      }
      if (-*(float *)((int)this + 0x28) < fVar1) {
        if (param_3 == 0) {
          return 2;
        }
        *(float *)((int)this + 0x7c) = *(float *)((int)this + 0x28) - fVar1;
        return 2;
      }
      return 0;
    }
  }
  fVar2 = SQRT(param_1[2] * param_1[2] + *param_1 * *param_1);
  fVar2 = fVar2 * *(float *)((int)this + 0x24) +
          SQRT(_DAT_004cba94 - fVar2 * fVar2) * *(float *)((int)this + 0x28);
  if (fVar2 <= fVar1) {
    return 1;
  }
  if (-fVar2 < fVar1) {
    if (param_3 != 0) {
      *(float *)((int)this + 0x7c) = fVar2 - fVar1;
    }
    return 2;
  }
  if ((param_4 == 0) && (param_3 != 0)) {
    *(float *)((int)this + 0x7c) = (fVar2 + fVar2) - fVar1;
  }
  return 0;
}


/* 00419890 size=49 */

undefined4 __thiscall FUN_00419890(void *this,float param_1)

{
  if (param_1 < *(float *)((int)this + 0x74)) {
    return 2;
  }
  if (*(float *)((int)this + 0x70) < param_1) {
    return 1;
  }
  return 0;
}


/* 004198d0 size=2199 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004198d0: lifted from original x86 -> lt_lifted.c */


/* 0041a170 size=467 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0041a170(void *this,int *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  undefined4 local_8;
  
  local_1c = -(*(float *)((int)this + 0x98) * _DAT_004cbed8);
  local_24 = local_1c * *(float *)((int)this + 0x8c);
  local_20 = local_1c * *(float *)((int)this + 0x90);
  local_1c = local_1c * *(float *)((int)this + 0x94);
  if (*(float *)((int)this + 0x90) == _DAT_004cb524) {
    local_c = *(float *)((int)this + 0x48) - _DAT_004cb524;
    local_10 = *(float *)((int)this + 0x94);
    fVar1 = _DAT_004cb524 - *(float *)((int)this + 0x40);
    local_8 = 0;
    fVar2 = (*(float *)((int)this + 0x8c) * local_c +
            *(float *)((int)this + 0x90) * 0.0 + fVar1 * local_10) * _DAT_004cbed4;
    local_18 = fVar2 * local_c;
    local_14 = fVar2 * 0.0;
    local_24 = local_18 + local_24;
    local_20 = local_14 + local_20;
    local_1c = fVar1 * fVar2 + local_1c;
  }
  *(float *)((int)this + 0xc) = local_24 + *(float *)((int)this + 0xc);
  *(float *)((int)this + 0x10) = local_20 + *(float *)((int)this + 0x10);
  *(float *)((int)this + 0x14) = local_1c + *(float *)((int)this + 0x14);
  if ((*(int *)((int)this + 0x2c) != 0) && (*(float *)((int)this + 0x90) < _DAT_004cbed0)) {
    *(undefined4 *)(DAT_004e9100 + 0x10) = *(undefined4 *)((int)this + 0x9c);
  }
  if (param_1 != (int *)0x0) {
    local_14 = local_20;
    local_18 = local_24;
    local_10 = local_1c;
    fVar1 = SQRT(local_24 * local_24 + local_20 * local_20 + local_1c * local_1c);
    if (fVar1 != _DAT_004cb524) {
      fVar1 = _DAT_004cba94 / fVar1;
      local_18 = fVar1 * local_24;
      local_14 = local_20 * fVar1;
      local_10 = local_1c * fVar1;
    }
    FUN_0041a350(*(undefined4 **)(DAT_004e9104 + 4),param_2,*(int *)(DAT_004e9104 + 0x3c),
                 *(undefined4 *)(DAT_004e9104 + 0x10),*(int **)(DAT_004e9104 + 0xc),param_1,
                 &local_18);
  }
  FUN_004194d0(this);
  return;
}


/* 0041a350 size=537 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_0041a350(undefined4 *param_1,int param_2,int param_3,undefined4 param_4,int *param_5,
            int *param_6,float *param_7)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  float *pfVar6;
  float local_54;
  float local_50;
  float local_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  float afStack_18 [3];
  float afStack_c [3];
  
  iVar2 = *param_6;
  if ((iVar2 == 0) || (*(int *)(iVar2 + 0x2c) == 0)) {
    puVar4 = (undefined4 *)0x0;
  }
  else {
    puVar4 = *(undefined4 **)(iVar2 + 0x28);
  }
  *param_1 = *puVar4;
  param_1[1] = puVar4[1];
  param_1[2] = puVar4[2];
  param_1[3] = puVar4[3];
  param_1[4] = param_4;
  if (param_5 == (int *)0x0) {
    param_1[5] = 0xffffffff;
  }
  else {
    uVar5 = (**(code **)(*param_5 + 8))(param_6);
    param_1[5] = uVar5;
  }
  pfVar1 = (float *)(param_2 + 0x20);
  local_54 = *pfVar1;
  local_50 = *(float *)(param_2 + 0x24);
  local_4c = *(float *)(param_2 + 0x28);
  fVar3 = (local_54 + *(float *)(param_3 + 0xc4)) * *param_7 +
          (local_4c + *(float *)(param_3 + 0xcc)) * param_7[2] +
          (local_50 + *(float *)(param_3 + 200)) * param_7[1];
  if (fVar3 < _DAT_004cb524) {
    fVar3 = -fVar3;
    FUN_00413050(&local_54,fVar3 * *param_7,fVar3 * param_7[1],fVar3 * param_7[2]);
    fStack_40 = local_4c;
    fStack_48 = local_54;
    fStack_44 = local_50;
    FUN_00413050(&uStack_30,local_54 * _DAT_004cbec0,local_50 * _DAT_004cbec0,
                 local_4c * _DAT_004cbec0);
    uStack_24 = uStack_30;
    uStack_20 = uStack_2c;
    uStack_1c = uStack_28;
    pfVar6 = (float *)FUN_0041ff50(&uStack_24,afStack_18,*(float *)(param_3 + 0xe4));
    fStack_3c = *pfVar6;
    fStack_38 = pfVar6[1];
    fStack_34 = pfVar6[2];
    if (_DAT_004cbedc < param_7[1]) {
      pfVar6 = (float *)FUN_0041ff50(param_7,afStack_c,-0.05);
      FUN_0041ff80(&fStack_48,*pfVar6,pfVar6[1],pfVar6[2]);
    }
    if ((*(uint *)(param_3 + 0x88) & 0x10000) != 0) {
      *(float *)(param_2 + 0x14) = fStack_3c + *(float *)(param_2 + 0x14);
      *(float *)(param_2 + 0x18) = fStack_38 + *(float *)(param_2 + 0x18);
      *(float *)(param_2 + 0x1c) = fStack_34 + *(float *)(param_2 + 0x1c);
    }
    *(uint *)(param_3 + 0x124) = *(uint *)(param_3 + 0x124) | 0x40;
    *pfVar1 = fStack_48 + *pfVar1;
    *(float *)(param_2 + 0x24) = fStack_44 + *(float *)(param_2 + 0x24);
    *(float *)(param_2 + 0x28) = fStack_40 + *(float *)(param_2 + 0x28);
    return;
  }
  return;
}


/* 0041a570 size=1151 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __cdecl FUN_0041a570(int *param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  bool bVar5;
  short sVar6;
  undefined2 extraout_var;
  int iVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  float local_8b8;
  float local_8b4;
  float local_8b0;
  int local_8ac;
  float local_8a8;
  float local_8a4;
  int local_8a0;
  float *local_89c;
  float local_898;
  float local_894;
  float local_890;
  float local_88c;
  float local_888;
  float local_884;
  undefined **local_880;
  float local_87c;
  float local_878;
  float local_874;
  float local_86c;
  float local_868;
  float local_860;
  float local_85c;
  float local_858;
  float local_854;
  float local_850;
  float local_848;
  float local_844;
  int local_840;
  int local_83c;
  int local_838;
  float local_830;
  float local_82c;
  float local_828;
  undefined4 local_824;
  undefined4 local_820;
  undefined4 local_81c;
  undefined4 local_818 [3];
  float local_80c [3];
  float local_800 [512];
  
  local_8b8 = 0.0;
  local_8b4 = 0.0;
  local_8b0 = 0.0;
  param_1[0xb] = 0;
  param_1[10] = 0x3f800000;
  param_1[0xc] = 0;
  *(undefined1 *)(param_1 + 0xe) = 0;
  param_1[0xf] = 0;
  param_1[0x2e] = 0;
  param_1[0xd] = 0;
  iVar7 = *param_1;
  param_1[0x4d] = 0;
  local_880 = &PTR_FUN_004cba48;
  local_828 = *(float *)(iVar7 + 0x9c);
  local_824 = *(undefined4 *)(iVar7 + 0xa0);
  local_820 = *(undefined4 *)(iVar7 + 0xa4);
  local_81c = *(undefined4 *)(iVar7 + 0xa8);
  FUN_0044ec30(&local_828,local_80c,&local_858,local_818);
  pfVar9 = (float *)(param_1 + 3);
  local_8ac = 0;
  local_89c = pfVar9;
  FUN_0041ada0((int)param_1,(int)local_800,&local_8ac,0x200,*pfVar9,(float)param_1[4],
               (float)param_1[5],0);
  sVar6 = FUN_00426030(pfVar9,(float)param_1[9],(int *)local_800,local_8ac);
  if (CONCAT22(extraout_var,sVar6) == 0) {
    param_1[6] = (int)*pfVar9;
    param_1[7] = param_1[4];
    param_1[8] = param_1[5];
    return false;
  }
  pfVar1 = (float *)(param_1 + 6);
  while( true ) {
    FUN_0041a9f0((int)param_1,(int)local_800,&local_8ac,0x200,(float *)0x0,(float *)0x0,0);
    iVar7 = FUN_004262c0(pfVar9,pfVar1,(float)param_1[9],local_800,local_8ac,&local_8b8,&local_840,
                         &local_8a8,&local_8a0);
    if (iVar7 == 0) {
      if ((*(byte *)(*param_1 + 0x8c) & 0x40) != 0) {
        FUN_0041aff0(param_1);
      }
      return (char)param_1[0xe] != '\0';
    }
    if (local_8b8 * local_8b8 + local_8b4 * local_8b4 + local_8b0 * local_8b0 <= _DAT_004cbaec)
    break;
    local_87c = *pfVar9;
    local_878 = pfVar9[1];
    local_874 = pfVar9[2];
    local_830 = (float)param_1[7] - local_878;
    local_82c = (float)param_1[8] - local_874;
    local_8a4 = _DAT_004cba94 - local_8a8;
    fVar2 = (*pfVar1 - local_87c) * local_8a4;
    local_86c = local_830 * local_8a4;
    local_868 = local_82c * local_8a4;
    local_890 = fVar2 * local_8b8 + local_8b4 * local_86c + local_8b0 * local_868;
    local_898 = local_890 * local_8b8;
    local_894 = local_8b4 * local_890;
    local_890 = local_8b0 * local_890;
    if ((local_8a0 != 0) && (local_8a8 <= (float)param_1[10])) {
      param_1[10] = (int)local_8a8;
      param_1[0xb] = local_840;
      param_1[0xc] = local_83c;
      param_1[0xd] = local_838;
    }
    iVar7 = param_1[0xf];
    bVar4 = false;
    iVar8 = 0;
    bVar5 = bVar4;
    if (0 < iVar7) {
      pfVar10 = (float *)(param_1 + 0x10);
      do {
        bVar5 = true;
        if (bVar4) break;
        local_88c = *pfVar10;
        local_888 = pfVar10[1];
        local_884 = pfVar10[2];
        bVar4 = local_88c * local_8b8 + local_8b4 * local_888 + local_8b0 * local_884 <
                _DAT_004cb524;
        iVar8 = iVar8 + 1;
        pfVar10 = pfVar10 + 3;
        pfVar9 = local_89c;
        bVar5 = bVar4;
      } while (iVar8 < iVar7);
    }
    if (iVar7 < 10) {
      pfVar10 = (float *)(param_1 + iVar7 * 3 + 0x10);
      *pfVar10 = local_8b8;
      pfVar10[1] = local_8b4;
      pfVar10[2] = local_8b0;
      param_1[0xf] = param_1[0xf] + 1;
    }
    if (9 < *(byte *)(param_1 + 0xe)) break;
    if (bVar5) {
      local_848 = local_86c * _DAT_004cbee4;
      local_844 = local_868 * _DAT_004cbee4;
      *pfVar1 = *pfVar1 - fVar2 * _DAT_004cbee4;
      param_1[7] = (int)((float)param_1[7] - local_848);
      fVar2 = (float)param_1[8] - local_844;
    }
    else {
      local_860 = local_894 * _DAT_004cbee4;
      local_85c = local_890 * _DAT_004cbee4;
      *pfVar1 = *pfVar1 - local_898 * _DAT_004cbee4;
      param_1[7] = (int)((float)param_1[7] - local_860);
      fVar2 = (float)param_1[8] - local_85c;
    }
    param_1[8] = (int)fVar2;
    if ((local_8a0 != 0) &&
       (local_858 * local_8b8 + local_854 * local_8b4 + local_850 * local_8b0 < _DAT_004cbee0)) {
      iVar7 = param_1[0x2e];
      param_1[iVar7 * 3 + 0x2f] = (int)local_8b8;
      param_1[iVar7 * 3 + 0x30] = (int)local_8b4;
      param_1[iVar7 * 3 + 0x31] = (int)local_8b0;
      param_1[0x4d] = 1;
      param_1[0x2e] = param_1[0x2e] + 1;
    }
    *(char *)(param_1 + 0xe) = (char)param_1[0xe] + '\x01';
  }
  fVar2 = pfVar9[1];
  fVar3 = pfVar9[2];
  *pfVar1 = *pfVar9;
  param_1[7] = (int)fVar2;
  param_1[8] = (int)fVar3;
  return false;
}


/* 0041a9f0 size=934 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0041a9f0: lifted from original x86 -> lt_lifted.c */


/* 0041ada0 size=581 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_0041ada0(int param_1,int param_2,int *param_3,int param_4,float param_5,float param_6,
            float param_7,int param_8)

{
  int iVar1;
  short sVar2;
  void *this;
  int *piVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int *piVar10;
  int iVar11;
  float *pfVar12;
  short *psVar13;
  ushort uVar14;
  undefined4 unaff_EDI;
  char *pcVar15;
  int local_1c;
  int local_c;
  
  if (param_2 != 0) {
    *param_3 = 0;
    fVar9 = *(float *)(param_1 + 0x24) + _DAT_004cbeec;
    local_c = *(int *)(*(int *)(param_1 + 8) + 4);
    if (-1 < local_c + -1) {
      local_1c = local_c * 8;
      do {
        this = *(void **)(local_1c + *(int *)(param_1 + 8));
        if ((*(char *)((int)this + 0xbc) == '\x02') || (*(char *)((int)this + 0xbc) == '\t')) {
          piVar3 = *(int **)((int)this + 0x1b8);
          piVar10 = (int *)FUN_00469310(this,&param_5);
          if (piVar10 != (int *)0x0) {
            uVar14 = *(ushort *)((int)piVar10 + 6);
            psVar13 = (short *)&DAT_004e6e30;
            iVar11 = (**(code **)(*piVar3 + 0x1c))();
            while ((int)(psVar13 + -0x273718) < 0x800) {
              if ((uVar14 == 0xfffe) || (uVar14 == 0xffff)) {
                if (psVar13 == (short *)&DAT_004e6e30) goto LAB_0041afc3;
                uVar14 = psVar13[-1];
                psVar13 = psVar13 + -1;
              }
              iVar1 = *piVar10 + (uint)uVar14 * 6;
              uVar14 = *(ushort *)(*piVar10 + (uint)uVar14 * 6);
              if (uVar14 == 0xffff) {
                uVar14 = *(ushort *)(iVar1 + 4);
              }
              else {
                piVar3 = (int *)(iVar11 + (uint)uVar14 * 0x18);
                iVar4 = *piVar3;
                if ((iVar4 == 0) || (*(int *)(iVar4 + 0x2c) == 0)) {
                  pfVar12 = (float *)0x0;
                }
                else {
                  pfVar12 = *(float **)(iVar4 + 0x28);
                }
                fVar5 = (param_5 * *pfVar12 + param_7 * pfVar12[2] + param_6 * pfVar12[1]) -
                        pfVar12[3];
                if (fVar5 <= fVar9) {
                  if (_DAT_004cbea0 <= fVar5) {
                    if (((*(byte *)(*(int *)(iVar4 + 0x2c) + 0x30) & 1) != 0) &&
                       (fVar5 = *(float *)(iVar4 + 0x18) - param_5,
                       fVar6 = *(float *)(iVar4 + 0x1c) - param_6,
                       fVar7 = *(float *)(iVar4 + 0x20) - param_7,
                       fVar8 = fVar9 + *(float *)(iVar4 + 0x24),
                       fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5 <= fVar8 * fVar8)) {
                      if (param_4 <= *param_3) {
                        pcVar15 = s_GetSpherePosTestPolys___World_ca_004d6a04;
                        goto LAB_0041afbb;
                      }
                      *(int *)(param_2 + *param_3 * 4) = iVar4;
                      if (param_8 != 0) {
                        *(void **)(param_8 + *param_3 * 8) = this;
                        *(int **)(param_8 + 4 + *param_3 * 8) = piVar3;
                      }
                      *param_3 = *param_3 + 1;
                    }
                    sVar2 = *(short *)(iVar1 + 2);
                    if ((sVar2 != -2) && (sVar2 != -1)) {
                      *psVar13 = sVar2;
                      psVar13 = psVar13 + 1;
                    }
                    uVar14 = *(ushort *)(iVar1 + 4);
                  }
                  else {
                    uVar14 = *(ushort *)(iVar1 + 2);
                  }
                }
                else {
                  uVar14 = *(ushort *)(iVar1 + 4);
                }
              }
            }
            pcVar15 = s_GetSpherePosTestPolys___World_ca_004d6a40;
LAB_0041afbb:
            FUN_00436670((byte *)pcVar15,unaff_EDI);
          }
        }
LAB_0041afc3:
        local_1c = local_1c + -8;
        local_c = local_c + -1;
        if (local_c == 0) {
          return;
        }
      } while( true );
    }
  }
  return;
}


/* 0041aff0 size=1743 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0041aff0(int *param_1)

{
  float *this;
  float fVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  float10 extraout_ST0;
  float10 fVar5;
  longlong lVar6;
  int local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  int local_74;
  int local_70;
  float local_6c;
  float local_68;
  float local_64;
  int local_60;
  undefined **local_5c;
  float local_58;
  float local_54;
  int local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_24 [3];
  float local_18 [3];
  undefined4 local_c [3];
  
  local_5c = &PTR_FUN_004cba48;
  iVar2 = *param_1;
  local_4c = *(float *)(iVar2 + 0x9c);
  local_48 = *(undefined4 *)(iVar2 + 0xa0);
  local_44 = *(undefined4 *)(iVar2 + 0xa4);
  local_40 = *(undefined4 *)(iVar2 + 0xa8);
  FUN_0044ec30(&local_4c,local_18,&local_a4,local_c);
  this = (float *)(param_1 + 6);
  local_70 = 0;
  local_74 = 0;
  local_c0 = (float)param_1[3];
  local_bc = (float)param_1[4];
  local_b8 = (float)param_1[5];
  local_94 = (float)param_1[7] - local_bc;
  local_90 = (float)param_1[8] - local_b8;
  lVar6 = __ftol();
  iVar4 = (int)lVar6 + 2;
  iVar2 = (int)lVar6 + 1;
  local_34 = (float)iVar2;
  local_3c = (float)(extraout_ST0 / (float10)iVar2);
  local_38 = local_94 / local_34;
  local_34 = local_90 / local_34;
  local_c4 = 0;
  if (0 < iVar4) {
    do {
      fVar1 = (float)local_c4;
      local_30 = local_3c * fVar1;
      local_2c = local_38 * fVar1;
      local_58 = local_30 + (float)param_1[3];
      local_54 = local_2c + (float)param_1[4];
      local_c0 = local_a4 + local_58;
      local_bc = local_a0 + local_54;
      local_b8 = local_9c + fVar1 * local_34 + (float)param_1[5];
      fVar1 = (float)param_1[9] + (float)param_1[9];
      local_b0 = local_a4 * fVar1;
      local_ac = local_a0 * fVar1;
      local_98 = local_c0 - local_b0;
      local_94 = local_bc - local_ac;
      local_90 = local_b8 - fVar1 * local_9c;
      local_8c = local_98;
      local_88 = local_94;
      local_84 = local_90;
      local_80 = local_c0;
      local_7c = local_bc;
      local_78 = local_b8;
      FUN_0041a9f0((int)param_1,0x4e8648,&local_74,0x200,&local_80,&local_8c,0);
      iVar2 = FUN_004262c0(&local_80,&local_8c,(float)param_1[9],(float *)&DAT_004e8648,local_74,
                           &local_6c,local_24,&local_b4,&local_60);
      if (((iVar2 != 0) && (local_60 != 0)) &&
         (local_6c * local_a4 + local_68 * local_a0 + local_64 * local_9c <= (float)_DAT_004cbef8))
      {
        FUN_004263c0(&local_6c,*param_1);
        iVar2 = *param_1;
        local_4c = *(float *)(iVar2 + 0x9c);
        local_48 = *(undefined4 *)(iVar2 + 0xa0);
        local_44 = *(undefined4 *)(iVar2 + 0xa4);
        local_40 = *(undefined4 *)(iVar2 + 0xa8);
        FUN_0044ec30(&local_4c,local_18,&local_a4,local_c);
        local_b4 = local_b4 - _DAT_004cbeec;
        if (local_b4 < _DAT_004cb524) {
          local_b4 = 0.0;
        }
        local_ac = local_88 - local_7c;
        local_a8 = local_84 - local_78;
        FUN_00413050(&local_b0,(local_8c - local_80) * local_b4 + local_80,
                     local_7c + local_ac * local_b4,local_78 + local_a8 * local_b4);
        local_70 = 1;
        *this = local_b0;
        param_1[7] = (int)local_ac;
        param_1[8] = (int)local_a8;
        break;
      }
      local_c4 = local_c4 + 1;
    } while (local_c4 < iVar4);
  }
  if ((char)param_1[0xe] != '\0') {
    if (param_1[0x4d] != 0) goto LAB_0041b587;
    if (local_70 == 0) {
      if ((float)param_1[10] < _DAT_004cba94) {
        FUN_004263c0((float *)(param_1 + 0xb),*param_1);
        return;
      }
      return;
    }
  }
  if (param_1[0x4d] == 0) {
    fVar1 = (float)param_1[9] * _DAT_004cbef0;
    local_80 = *this;
    local_7c = (float)param_1[7];
    local_78 = (float)param_1[8];
    FUN_00413050(&local_b0,fVar1 * local_a4,local_a0 * fVar1,local_9c * fVar1);
    FUN_00413050(&local_58,*this - local_b0,(float)param_1[7] - local_ac,
                 (float)param_1[8] - local_a8);
    local_8c = local_58;
    local_88 = local_54;
    local_84 = (float)local_50;
    FUN_0041a9f0((int)param_1,0x4e8648,&local_74,0x200,&local_80,&local_8c,0);
    iVar2 = FUN_004262c0(&local_80,&local_8c,(float)param_1[9],(float *)&DAT_004e8648,local_74,
                         &local_6c,local_24,&local_b4,&local_60);
    if (iVar2 == 0) {
      *this = local_8c;
      param_1[7] = (int)local_88;
      param_1[8] = (int)local_84;
      return;
    }
    if (local_b4 < _DAT_004cba94) {
      if (local_6c * local_a4 + local_68 * local_a0 + local_64 * local_9c <= (float)_DAT_004cbef8) {
        FUN_004263c0(local_24,*param_1);
        return;
      }
      return;
    }
    return;
  }
LAB_0041b587:
  local_70 = param_1[0x2e];
  local_bc = _DAT_004cb524;
  local_b8 = _DAT_004cb524;
  local_c0 = _DAT_004cb524;
  if (0 < local_70) {
    pfVar3 = (float *)(param_1 + 0x2f);
    iVar2 = local_70;
    do {
      local_98 = *pfVar3;
      iVar2 = iVar2 + -1;
      local_c0 = local_c0 + local_98;
      local_94 = pfVar3[1];
      local_90 = pfVar3[2];
      local_bc = local_bc + local_94;
      local_b8 = local_b8 + local_90;
      pfVar3 = pfVar3 + 3;
    } while (iVar2 != 0);
  }
  fVar1 = (float)local_70;
  local_c0 = local_c0 / fVar1;
  local_bc = local_bc / fVar1;
  local_b8 = local_b8 / fVar1;
  fVar5 = FUN_0041fe80(&local_c0);
  if (fVar5 != (float10)_DAT_004cb524) {
    fVar5 = (float10)_DAT_004cba94 / fVar5;
    local_c0 = (float)(fVar5 * (float10)local_c0);
    local_bc = (float)((float10)local_bc * fVar5);
    local_b8 = (float)((float10)local_b8 * fVar5);
  }
  FUN_004263c0(&local_c0,*param_1);
  FUN_00413050(&local_b0,local_c0 + local_c0,local_bc + local_bc,local_b8 + local_b8);
  FUN_0041ff80(this,local_b0,local_ac,local_a8);
  return;
}


/* 0041b6c0 size=980 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0041b6c0: lifted from original x86 -> lt_lifted.c */


/* 0041baa0 size=222 */

undefined4 __cdecl FUN_0041baa0(uint *param_1,float *param_2)

{
  uint uVar1;
  float fVar2;
  float *pfVar3;
  int iVar4;
  uint *puVar5;
  
  puVar5 = (uint *)&DAT_004e7634;
  do {
    while( true ) {
      while( true ) {
        if ((*(byte *)((int)param_1 + 0x16) & 3) != 0) {
          if (puVar5 == (uint *)&DAT_004e7634) {
            return 0;
          }
          param_1 = (uint *)puVar5[-1];
          puVar5 = puVar5 + -1;
        }
        uVar1 = *param_1;
        if ((uVar1 == 0) || (*(int *)(uVar1 + 0x2c) == 0)) {
          pfVar3 = (float *)0x0;
        }
        else {
          pfVar3 = *(float **)(uVar1 + 0x28);
        }
        fVar2 = (param_2[1] * *pfVar3 + param_2[2] * pfVar3[1] + param_2[3] * pfVar3[2]) - pfVar3[3]
        ;
        if (fVar2 <= *param_2) break;
        param_1 = (uint *)param_1[2];
      }
      if (-*param_2 <= fVar2) break;
      param_1 = (uint *)param_1[1];
    }
    if (uVar1 != 0) {
      iVar4 = FUN_004175b0(uVar1,(float *)0x0,(float *)0x0);
      if (iVar4 != 0) {
        return 1;
      }
    }
    if ((*(byte *)(param_1[1] + 0x16) & 3) == 0) {
      *puVar5 = param_1[1];
      puVar5 = puVar5 + 1;
    }
    param_1 = (uint *)param_1[2];
  } while( true );
}


/* 0041bb80 size=328 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0041bb80: lifted from original x86 -> lt_lifted.c */


/* 0041bcd0 size=1106 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0041bcd0(int *param_1,int *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  bool bVar5;
  float *pfVar6;
  int iVar7;
  longlong lVar8;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float local_48;
  float fStack_44;
  float fStack_40;
  float local_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  
  FUN_0041c130(&local_48,&local_3c);
  pfVar6 = (float *)(**(code **)(**(int **)(DAT_004e9104 + 0xc) + 0x14))();
  fStack_30 = *pfVar6;
  fStack_2c = pfVar6[1];
  fStack_28 = pfVar6[2];
  pfVar6 = (float *)(**(code **)(**(int **)(DAT_004e9104 + 0xc) + 0x18))();
  fStack_18 = *pfVar6;
  fStack_14 = pfVar6[1];
  fStack_10 = pfVar6[2];
  iVar7 = *(int *)(DAT_004e9104 + 0x10);
  fVar1 = _DAT_004cba94 /
          (local_48 * *(float *)(iVar7 + 0x268) +
           fStack_44 * *(float *)(iVar7 + 0x26c) + fStack_40 * *(float *)(iVar7 + 0x270) +
          *(float *)(iVar7 + 0x274));
  fVar2 = (local_48 * *(float *)(iVar7 + 0x238) +
           fStack_44 * *(float *)(iVar7 + 0x23c) + fStack_40 * *(float *)(iVar7 + 0x240) +
          *(float *)(iVar7 + 0x244)) * fVar1;
  fVar3 = (local_48 * *(float *)(iVar7 + 0x248) +
           fStack_44 * *(float *)(iVar7 + 0x24c) + fStack_40 * *(float *)(iVar7 + 0x250) +
          *(float *)(iVar7 + 0x254)) * fVar1;
  fVar1 = (local_48 * *(float *)(iVar7 + 600) +
           fStack_44 * *(float *)(iVar7 + 0x25c) + fStack_40 * *(float *)(iVar7 + 0x260) +
          *(float *)(iVar7 + 0x264)) * fVar1;
  fStack_1c = _DAT_004cba94 /
              (local_3c * *(float *)(iVar7 + 0x268) +
               fStack_38 * *(float *)(iVar7 + 0x26c) + fStack_34 * *(float *)(iVar7 + 0x270) +
              *(float *)(iVar7 + 0x274));
  fStack_24 = (local_3c * *(float *)(iVar7 + 0x238) +
               fStack_38 * *(float *)(iVar7 + 0x23c) + fStack_34 * *(float *)(iVar7 + 0x240) +
              *(float *)(iVar7 + 0x244)) * fStack_1c;
  fStack_20 = (local_3c * *(float *)(iVar7 + 0x248) +
               fStack_38 * *(float *)(iVar7 + 0x24c) + fStack_34 * *(float *)(iVar7 + 0x250) +
              *(float *)(iVar7 + 0x254)) * fStack_1c;
  fStack_1c = (local_3c * *(float *)(iVar7 + 600) +
               fStack_38 * *(float *)(iVar7 + 0x25c) + fStack_34 * *(float *)(iVar7 + 0x260) +
              *(float *)(iVar7 + 0x264)) * fStack_1c;
  if (fStack_24 <= fVar2) {
    fStack_c = fStack_24;
  }
  else {
    fStack_c = fVar2;
  }
  if (fStack_20 <= fVar3) {
    fStack_8 = fStack_20;
  }
  else {
    fStack_8 = fVar3;
  }
  if (fStack_24 < fVar2) {
    fStack_24 = fVar2;
  }
  if (fStack_20 < fVar3) {
    fStack_20 = fVar3;
  }
  if (fStack_1c < fVar1) {
    fStack_1c = fVar1;
  }
  lVar8 = __ftol();
  fVar1 = (float)(int)lVar8 * fStack_30 + fStack_18;
  lVar8 = __ftol();
  fStack_50 = (float)(int)lVar8 * fStack_2c + fStack_14;
  lVar8 = __ftol();
  bVar4 = false;
  *param_2 = 0;
  bVar5 = false;
  fVar2 = (float)(int)lVar8 * fStack_28 + fStack_10;
  if (fStack_50 <= fStack_20) {
    do {
      if (bVar4) break;
      fStack_54 = fVar1;
      if (fVar1 <= fStack_24) {
        do {
          if (bVar4) break;
          fStack_4c = fVar2;
          if (fVar2 <= fStack_1c) {
            do {
              if (bVar4) break;
              iVar7 = (**(code **)(**(int **)(DAT_004e9104 + 0xc) + 0x10))
                                (fStack_54,fStack_50,fStack_4c);
              *param_1 = iVar7;
              bVar4 = bVar5;
              if (iVar7 != 0) {
                iVar7 = *param_2;
                param_1 = param_1 + 1;
                *param_2 = iVar7 + 1;
                if (param_3 <= iVar7 + 1) {
                  bVar4 = true;
                }
              }
              fStack_4c = fStack_4c + fStack_28;
              bVar5 = bVar4;
            } while (fStack_4c <= fStack_1c);
          }
          fStack_54 = fStack_54 + fStack_30;
        } while (fStack_54 <= fStack_24);
      }
      fStack_50 = fStack_50 + fStack_2c;
    } while (fStack_50 <= fStack_20);
  }
  if (*param_2 == 0) {
    iVar7 = (**(code **)(**(int **)(DAT_004e9104 + 0xc) + 0x10))(fStack_18,fStack_14,fStack_10);
    *param_1 = iVar7;
    if (iVar7 != 0) {
      *param_2 = *param_2 + 1;
    }
  }
  return;
}


