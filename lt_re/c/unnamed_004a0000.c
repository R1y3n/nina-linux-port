/* lithtech.exe decompilation - unnamed_004a0000 */
#include "ghidra_types.h"

/* 004a0390 size=107 */

void FUN_004a0390(void)

{
  FUN_004a0400();
  if (DAT_004ec3fc != (HDC)0x0) {
    SelectObject(DAT_004ec3fc,DAT_004ec408);
    SelectObject(DAT_004ec3fc,DAT_004ec404);
    DeleteDC(DAT_004ec3fc);
  }
  if (DAT_004ec400 != (HGDIOBJ)0x0) {
    DeleteObject(DAT_004ec400);
  }
  DAT_004ec404 = (HGDIOBJ)0x0;
  DAT_004ec400 = (HGDIOBJ)0x0;
  DAT_004ec3fc = (HDC)0x0;
  return;
}


/* 004a0400 size=47 */

void FUN_004a0400(void)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  
  piVar2 = DAT_004ec3f8;
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[1];
    bVar3 = piVar1 != DAT_004ec3f8;
    FUN_0049f9a0(piVar2);
    piVar2 = (int *)((uint)piVar1 & -(uint)bVar3);
  }
  return;
}


/* 004a0540 size=43 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_004a0540(void)

{
  DWORD DVar1;
  
  DVar1 = timeGetTime();
  return (float10)(DVar1 - DAT_004ec420) * (float10)_DAT_004cbaec;
}


/* 004a09d0 size=91 */

undefined4 __fastcall FUN_004a09d0(int *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  
  uVar1 = param_1[0x48];
  if ((uVar1 == 0) || (8 < uVar1)) {
    return 0;
  }
  iVar2 = *param_1;
  uVar4 = 0;
  if (uVar1 != 0) {
    piVar5 = param_1;
    do {
      iVar3 = FUN_0044f760(piVar5);
      if (iVar3 == 0) {
        return 0;
      }
      if (*piVar5 != iVar2) {
        return 0;
      }
      if ((uVar4 != 0) && (*(uint *)(iVar2 + 0x4c) <= (uint)piVar5[6])) {
        return 0;
      }
      uVar4 = uVar4 + 1;
      piVar5 = piVar5 + 9;
    } while (uVar4 < (uint)param_1[0x48]);
  }
  return 1;
}


/* 004a0a30 size=54 */

undefined4 __fastcall FUN_004a0a30(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_004a0a70(param_1);
  if (iVar1 == 0) {
    return 0;
  }
  FUN_004a1190(param_1,(float)(uint)*(ushort *)(*(int *)(param_1[0x79] + 0x2c4) + 0x10),
               (float *)param_1[0x49]);
  return 1;
}


/* 004a0a70 size=319 */

undefined4 __fastcall FUN_004a0a70(int *param_1)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  uint uVar4;
  
  iVar1 = FUN_004a09d0(param_1);
  if (iVar1 == 0) {
    return 0;
  }
  param_1[0x79] = *param_1;
  uVar4 = 0;
  param_1[0x4e] = 0;
  if (param_1[0x48] != 0) {
    piVar2 = param_1 + 0x92;
    puVar3 = (uint *)(param_1 + 6);
    do {
      if (puVar3[-3] < *(uint *)(param_1[0x79] + 0x4c)) {
        iVar1 = *(int *)(*(int *)(param_1[0x79] + 0x48) + puVar3[-3] * 4);
      }
      else {
        iVar1 = 0;
      }
      piVar2[-8] = iVar1;
      if (*puVar3 < *(uint *)(param_1[0x79] + 0x4c)) {
        iVar1 = *(int *)(*(int *)(param_1[0x79] + 0x48) + *puVar3 * 4);
      }
      else {
        iVar1 = 0;
      }
      *piVar2 = iVar1;
      piVar2[8] = *(int *)((uint)(ushort)puVar3[-5] * 0x20 + *(int *)(param_1[0x79] + 0x168));
      uVar4 = uVar4 + 1;
      piVar2[0x10] = *(int *)((uint)(ushort)puVar3[-2] * 0x20 + *(int *)(param_1[0x79] + 0x168));
      piVar2 = piVar2 + 1;
      puVar3 = puVar3 + 9;
    } while (uVar4 < (uint)param_1[0x48]);
  }
  if (param_1[0x49] == 0) {
    param_1[0x7a] = 0x3f800000;
    param_1[0x7b] = 0;
    param_1[0x7c] = 0;
    param_1[0x7d] = 0;
    param_1[0x7e] = 0;
    param_1[0x7f] = 0x3f800000;
    param_1[0x80] = 0;
    param_1[0x81] = 0;
    param_1[0x82] = 0;
    param_1[0x83] = 0;
    param_1[0x84] = 0x3f800000;
    param_1[0x85] = 0;
    param_1[0x86] = 0;
    param_1[0x87] = 0;
    param_1[0x88] = 0;
    param_1[0x89] = 0x3f800000;
    param_1[0x49] = (int)(param_1 + 0x7a);
  }
  if (param_1[0x4a] == 0) {
    param_1[0x4a] = *(int *)(param_1[0x79] + 0x74);
  }
  param_1[0x61] =
       *(int *)((uint)*(ushort *)(param_1 + 1) * 0x20 + 4 + *(int *)(param_1[0x79] + 0x168));
  return 1;
}


/* 004a0bb0 size=454 */

void __thiscall FUN_004a0bb0(void *this,int param_1,int param_2,float *param_3,float *param_4)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  int iVar12;
  
  pfVar1 = (float *)(*(int *)(*(int *)(*(int *)(*(int *)((int)this + param_1 * 4 + 0x268) + 4) +
                                      param_2 * 4) + 0xc) +
                    (uint)*(ushort *)((int)this + param_1 * 0x24 + 6) * 0x1c);
  pfVar2 = (float *)(*(int *)(*(int *)(*(int *)(*(int *)((int)this + param_1 * 4 + 0x288) + 4) +
                                      param_2 * 4) + 0xc) +
                    (uint)*(ushort *)((int)this + param_1 * 0x24 + 0x12) * 0x1c);
  FUN_0044ea30(param_3,pfVar1 + 3,pfVar2 + 3,*(float *)((int)this + param_1 * 0x24 + 0x1c));
  fVar8 = *(float *)((int)this + param_1 * 0x24 + 0x1c);
  fVar9 = pfVar1[1];
  fVar4 = pfVar2[1];
  fVar10 = pfVar1[2];
  fVar5 = pfVar2[2];
  fVar6 = pfVar1[1];
  fVar7 = pfVar1[2];
  *param_4 = (*pfVar2 - *pfVar1) * fVar8 + *pfVar1;
  param_4[1] = (fVar4 - fVar9) * fVar8 + fVar6;
  param_4[2] = (fVar5 - fVar10) * fVar8 + fVar7;
  if (param_2 == 0) {
    iVar11 = *(int *)(*(int *)((int)this + 0x1e4) + 0x168);
    iVar12 = (uint)*(ushort *)((int)this + param_1 * 0x24 + 0x10) * 0x20;
    pfVar1 = (float *)((uint)*(ushort *)((int)this + param_1 * 0x24 + 4) * 0x20 + 0x14 + iVar11);
    iVar3 = iVar12 + 0x14 + iVar11;
    fVar8 = pfVar1[1];
    fVar4 = *(float *)(iVar3 + 4);
    fVar9 = pfVar1[2];
    fVar5 = *(float *)(iVar3 + 8);
    fVar10 = *(float *)((int)this + param_1 * 0x24 + 0x1c);
    fVar6 = pfVar1[1];
    fVar7 = pfVar1[2];
    *param_4 = (*(float *)(iVar12 + 0x14 + iVar11) - *pfVar1) * fVar10 + *pfVar1 + *param_4;
    param_4[1] = (fVar4 - fVar8) * fVar10 + fVar6 + param_4[1];
    param_4[2] = (fVar5 - fVar9) * fVar10 + fVar7 + param_4[2];
  }
  return;
}


/* 004a0d80 size=423 */

void __thiscall FUN_004a0d80(void *this,int param_1,int param_2,float *param_3,float *param_4)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  pfVar3 = *(float **)
            (*(int *)(*(int *)(*(int *)((int)this + param_1 * 4 + 0x268) + 4) + param_2 * 4) + 0xc);
  pfVar1 = pfVar3 + (uint)*(ushort *)((int)this + param_1 * 0x24 + 6) * 7;
  pfVar2 = (float *)(*(int *)(*(int *)(*(int *)(*(int *)((int)this + param_1 * 4 + 0x288) + 4) +
                                      param_2 * 4) + 0xc) +
                    (uint)*(ushort *)((int)this + param_1 * 0x24 + 0x12) * 0x1c);
  FUN_0044ea30(param_3,pfVar1 + 3,pfVar2 + 3,*(float *)((int)this + param_1 * 0x24 + 0x1c));
  fVar4 = *(float *)((int)this + param_1 * 0x24 + 0x1c);
  local_20 = (*pfVar2 - *pfVar1) * fVar4 + *pfVar1;
  local_1c = (pfVar2[1] - pfVar1[1]) * fVar4 + pfVar1[1];
  local_18 = (pfVar2[2] - pfVar1[2]) * fVar4 + pfVar1[2];
  *param_4 = local_20;
  param_4[1] = local_1c;
  param_4[2] = local_18;
  local_10 = -pfVar3[3];
  local_c = -pfVar3[4];
  local_8 = -pfVar3[5];
  local_4 = pfVar3[6];
  FUN_00418000(&local_20,&local_10,param_3);
  *param_3 = local_20;
  param_3[1] = local_1c;
  param_3[2] = local_18;
  param_3[3] = local_14;
  fVar4 = pfVar3[1];
  fVar5 = pfVar3[2];
  *param_4 = *param_4 - *pfVar3;
  param_4[1] = param_4[1] - fVar4;
  param_4[2] = param_4[2] - fVar5;
  return;
}


/* 004a0f30 size=603 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __thiscall FUN_004a0f30(void *param_1,int param_2,int param_3,float param_4,int param_5)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  float10 fVar4;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_10 [4];
  
  if (param_4 <= _DAT_004cba94) {
  }
  else {
    param_4 = _DAT_004cba94;
  }
  if (param_5 == 0) {
    iVar2 = *(int *)((int)param_1 + param_2 * 4 + 0x228);
    if (iVar2 == 0) {
      param_4 = 0.0;
    }
    else {
      param_4 = *(float *)(*(int *)(iVar2 + 0x14) + param_3 * 4);
    }
    iVar2 = *(int *)((int)param_1 + param_2 * 4 + 0x248);
    if (iVar2 == 0) {
      fVar3 = _DAT_004cb524;
    }
    else {
      fVar3 = *(float *)(*(int *)(iVar2 + 0x14) + param_3 * 4);
    }
    if (param_4 != _DAT_004cbb00) {
      if (fVar3 == _DAT_004cbb00) goto LAB_004a1015;
      fVar3 = (fVar3 - param_4) * *(float *)((int)param_1 + param_2 * 0x24 + 0x1c) + param_4;
    }
    param_4 = fVar3;
  }
  else {
    param_4 = _DAT_004cba94 - param_4;
  }
  if (param_4 == _DAT_004cb524) {
    return (float10)_DAT_004cb524;
  }
  if (param_4 != _DAT_004cbb00) {
    FUN_004a0bb0(param_1,param_2,param_3,local_10,&local_3c);
    local_30 = *(float *)((int)param_1 + 0x1c8);
    local_2c = *(undefined4 *)((int)param_1 + 0x1cc);
    local_28 = *(undefined4 *)((int)param_1 + 0x1d0);
    local_24 = *(undefined4 *)((int)param_1 + 0x1d4);
    FUN_0044ea30((float *)((int)param_1 + 0x1c8),&local_30,local_10,param_4);
    pfVar1 = (float *)((int)param_1 + 0x1d8);
    *pfVar1 = (local_3c - *pfVar1) * param_4 + *pfVar1;
    *(float *)((int)param_1 + 0x1dc) =
         (local_38 - *(float *)((int)param_1 + 0x1dc)) * param_4 + *(float *)((int)param_1 + 0x1dc);
    *(float *)((int)param_1 + 0x1e0) =
         (local_34 - *(float *)((int)param_1 + 0x1e0)) * param_4 + *(float *)((int)param_1 + 0x1e0);
    return (float10)param_4;
  }
LAB_004a1015:
  FUN_004a0d80(param_1,param_2,param_3,local_10,&local_3c);
  FUN_00418000(&local_20,(float *)((int)param_1 + 0x1c8),local_10);
  *(float *)((int)param_1 + 0x1c8) = local_20;
  *(undefined4 *)((int)param_1 + 0x1cc) = local_1c;
  *(undefined4 *)((int)param_1 + 0x1d4) = local_14;
  *(undefined4 *)((int)param_1 + 0x1d0) = local_18;
  *(float *)((int)param_1 + 0x1d8) = local_3c + *(float *)((int)param_1 + 0x1d8);
  *(float *)((int)param_1 + 0x1dc) = local_38 + *(float *)((int)param_1 + 0x1dc);
  fVar4 = (float10)_DAT_004cb524;
  *(float *)((int)param_1 + 0x1e0) = local_34 + *(float *)((int)param_1 + 0x1e0);
  return fVar4;
}


/* 004a1190 size=567 */

void __thiscall FUN_004a1190(void *this,float param_1,float *param_2)

{
  undefined4 *puVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  float *pfVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  uint uVar9;
  float fVar10;
  float10 fVar11;
  
  fVar10 = param_1;
  while( true ) {
    while( true ) {
      pfVar5 = (float *)((int)fVar10 * 0x40 + *(int *)((int)this + 0x128));
      FUN_004a0bb0(this,0,(int)fVar10,(float *)((int)this + 0x1c8),(float *)((int)this + 0x1d8));
      if (((*(int *)((int)this + 0x228) == 0) || (*(int *)((int)this + 0x248) == 0)) ||
         (*(int *)((int)this + 0x1c) == 0x40000000)) {
        param_1 = 0.0;
      }
      else {
        fVar2 = *(float *)(*(int *)(*(int *)((int)this + 0x228) + 0x14) + (int)fVar10 * 4);
        param_1 = (*(float *)(*(int *)(*(int *)((int)this + 0x248) + 0x14) + (int)fVar10 * 4) -
                  fVar2) * *(float *)((int)this + 0x1c) + fVar2;
      }
      uVar7 = 1;
      if (1 < *(uint *)((int)this + 0x120)) {
        piVar8 = (int *)((int)this + 0x44);
        do {
          fVar11 = FUN_004a0f30(this,uVar7,(int)fVar10,param_1,*piVar8);
          uVar7 = uVar7 + 1;
          piVar8 = piVar8 + 9;
          param_1 = (float)(fVar11 + (float10)param_1);
        } while (uVar7 < *(uint *)((int)this + 0x120));
      }
      iVar6 = *(int *)(*(int *)(*(int *)((int)this + 0x1e4) + 0x28) + (int)fVar10 * 4);
      FUN_0044e720((float *)((int)this + 0x1c8),(float *)((int)this + 0x188));
      if ((*(byte *)(iVar6 + 0x12) & 2) == 0) {
        *(undefined4 *)((int)this + 0x194) = *(undefined4 *)((int)this + 0x1d8);
        *(undefined4 *)((int)this + 0x1a4) = *(undefined4 *)((int)this + 0x1dc);
        *(undefined4 *)((int)this + 0x1b4) = *(undefined4 *)((int)this + 0x1e0);
      }
      else {
        uVar3 = *(undefined4 *)(iVar6 + 8);
        uVar4 = *(undefined4 *)(iVar6 + 0xc);
        *(undefined4 *)((int)this + 0x194) = *(undefined4 *)(iVar6 + 4);
        *(undefined4 *)((int)this + 0x1a4) = uVar3;
        *(undefined4 *)((int)this + 0x1b4) = uVar4;
      }
      FUN_0043d430((float *)&DAT_004ec428,param_2,(float *)((int)this + 0x188));
      puVar1 = (undefined4 *)(*(int *)(*(int *)((int)this + 0x184) + 4) + (int)fVar10 * 0x1c);
      *(undefined4 **)((int)this + 0x140) = puVar1;
      FUN_0044e720((float *)(puVar1 + 3),(float *)((int)this + 0x144));
      uVar3 = puVar1[1];
      uVar4 = puVar1[2];
      *(undefined4 *)((int)this + 0x150) = *puVar1;
      *(undefined4 *)((int)this + 0x160) = uVar3;
      *(undefined4 *)((int)this + 0x170) = uVar4;
      FUN_0043d430(pfVar5,(float *)&DAT_004ec428,(float *)((int)this + 0x144));
      if (*(code **)((int)this + 300) != (code *)0x0) {
        (**(code **)((int)this + 300))
                  (*(undefined4 *)((int)this + 0x134),fVar10,pfVar5,
                   *(undefined4 *)((int)this + 0x130));
      }
      param_2 = pfVar5;
      if (*(int *)((int)this + 0x138) != 0) break;
      if (*(int *)(iVar6 + 0x20) == 0) {
        return;
      }
      uVar7 = *(int *)(iVar6 + 0x20) - 1;
      uVar9 = 0;
      if (uVar7 != 0) {
        do {
          FUN_004a1190(this,(float)(uint)*(ushort *)
                                          (*(int *)(*(int *)(iVar6 + 0x1c) + uVar9 * 4) + 0x10),
                       pfVar5);
          uVar9 = uVar9 + 1;
        } while (uVar9 < uVar7);
      }
      *(undefined4 *)((int)this + 0x13c) = 1;
      fVar10 = (float)(uint)*(ushort *)(*(int *)(*(int *)(iVar6 + 0x1c) + uVar7 * 4) + 0x10);
    }
    if (*(int *)((int)this + 0x13c) == 0) break;
    iVar6 = *(int *)((int)this + 0x13c) + -1;
    *(int *)((int)this + 0x13c) = iVar6;
    fVar10 = *(float *)(*(int *)((int)this + 0x138) + iVar6 * 4);
  }
  return;
}


/* 004a1490 size=121 */

undefined4 __cdecl FUN_004a1490(HMODULE param_1,undefined4 *param_2)

{
  HRSRC hResInfo;
  HGLOBAL hResData;
  DWORD DVar1;
  undefined4 *puVar2;
  
  hResInfo = FindResourceA(param_1,(LPCSTR)0x303a,(LPCSTR)0xa);
  if (hResInfo == (HRSRC)0x0) {
    return 1;
  }
  hResData = LoadResource(param_1,hResInfo);
  if (hResData == (HGLOBAL)0x0) {
    return 1;
  }
  DVar1 = SizeofResource(param_1,hResInfo);
  if (DVar1 != 8) {
    return 1;
  }
  puVar2 = LockResource(hResData);
  if (puVar2 == (undefined4 *)0x0) {
    return 1;
  }
  *param_2 = *puVar2;
  param_2[1] = puVar2[1];
  return 0;
}


/* 004a1570 size=42 */

int __thiscall FUN_004a1570(void *this,undefined4 param_1)

{
  *(undefined ***)((int)this + 4) = &PTR_LAB_004ddec0;
  *(undefined4 *)((int)this + 8) = param_1;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined ***)((int)this + 0x14) = &PTR_LAB_004ddec8;
  *(undefined4 *)((int)this + 0x18) = param_1;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  return;
}


/* 004a15a0 size=32 */

void __fastcall FUN_004a15a0(int *param_1)

{
  if (*param_1 != 0) {
    FUN_00468500((void *)(*param_1 + 0x24),(int)(param_1 + 1));
  }
  videomgr_4a1600(param_1,(int *)0x0);
  return;
}


/* 004a15c0 size=51 */

void __thiscall FUN_004a15c0(void *this,int param_1)

{
  if (*(int *)this != 0) {
    FUN_00468500((void *)(*(int *)this + 0x24),(int)this + 4);
  }
  *(int *)this = param_1;
  if (param_1 != 0) {
    FUN_00446060((int *)(param_1 + 0x24),(int)this + 4);
  }
  return;
}


/* 004a1690 size=42 */

void __fastcall FUN_004a1690(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(param_1 + 8);
  while (uVar3 != 0) {
    uVar1 = *(uint *)(uVar3 + 4);
    uVar2 = *(uint *)(param_1 + 8);
    (**(code **)(**(int **)(uVar3 + 8) + 8))();
    uVar3 = uVar1 & -(uint)(uVar1 != uVar2);
  }
  return;
}


/* 004a16c0 size=42 */

void __fastcall FUN_004a16c0(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(param_1 + 8);
  while (uVar3 != 0) {
    uVar1 = *(uint *)(uVar3 + 4);
    uVar2 = *(uint *)(param_1 + 8);
    (**(code **)(**(int **)(uVar3 + 8) + 0xc))();
    uVar3 = uVar1 & -(uint)(uVar1 != uVar2);
  }
  return;
}


/* 004a16f0 size=248 */

undefined4 * __thiscall FUN_004a16f0(void *this,undefined4 param_1,byte *param_2)

{
  uint uVar1;
  void *pvVar2;
  undefined4 *puVar3;
  int iVar4;
  void *this_00;
  
  uVar1 = FUN_004c4c00(this,param_2,&DAT_004d65c0);
  if (uVar1 == 0) {
    pvVar2 = (void *)FUN_00430de0(0x54);
    if (pvVar2 != (void *)0x0) {
      puVar3 = (undefined4 *)FUN_004018f0(pvVar2,param_1);
      if (puVar3 != (undefined4 *)0x0) {
        iVar4 = binkvideomgrimpl_401960((int)puVar3);
        if (iVar4 == 0) {
          return puVar3;
        }
        FUN_00401930(puVar3);
        FUN_00430df0((undefined *)puVar3);
        return (undefined4 *)0x0;
      }
    }
  }
  else {
    uVar1 = FUN_004c4c00(this_00,param_2,(byte *)s_SMACKER_004ddee8);
    if (uVar1 == 0) {
      pvVar2 = (void *)FUN_00430de0(0x54);
      if (pvVar2 != (void *)0x0) {
        puVar3 = (undefined4 *)FUN_004018f0(pvVar2,param_1);
        if (puVar3 != (undefined4 *)0x0) {
          iVar4 = binkvideomgrimpl_401960((int)puVar3);
          if (iVar4 == 0) {
            return puVar3;
          }
          FUN_00401930(puVar3);
          FUN_00430df0((undefined *)puVar3);
        }
      }
      pvVar2 = (void *)FUN_00430de0(0x34);
      if (pvVar2 != (void *)0x0) {
        puVar3 = (undefined4 *)FUN_004a1820(pvVar2,param_1);
        if (puVar3 != (undefined4 *)0x0) {
          iVar4 = FUN_004a1890((int)puVar3);
          if (iVar4 == 0) {
            return puVar3;
          }
          FUN_004a1860(puVar3);
          FUN_00430df0((undefined *)puVar3);
        }
      }
    }
  }
  return (undefined4 *)0x0;
}


/* 004a1820 size=50 */

int __thiscall FUN_004a1820(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = param_1;
  *(undefined ***)this = &PTR_LAB_004cdadc;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x28) = 0;
  *(undefined4 *)((int)this + 0x2c) = 0;
  *(undefined4 *)((int)this + 0x30) = 0;
  return;
}


/* 004a1860 size=46 */

void __fastcall FUN_004a1860(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cdadc;
  if ((HMODULE)param_1[0xc] != (HMODULE)0x0) {
    FreeLibrary((HMODULE)param_1[0xc]);
    param_1[0xc] = 0;
  }
  param_1[2] = 0;
  param_1[1] = 0;
  return;
}


/* 004a1890 size=367 */

undefined4 __fastcall FUN_004a1890(int param_1)

{
  HMODULE hModule;
  FARPROC pFVar1;
  int iVar2;
  undefined4 unaff_ESI;
  
  hModule = LoadLibraryA(s_smackw32_dll_004ddfe8);
  *(HMODULE *)(param_1 + 0x30) = hModule;
  if (hModule == (HMODULE)0x0) {
    FUN_00436670((byte *)s_Unable_to_find_smackw32_dll__vid_004ddfb0,unaff_ESI);
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SmackVideoMgr__Init_004ddf9c);
    }
    return 0x16;
  }
  pFVar1 = GetProcAddress(hModule,s__SmackSoundUseMSS_4_004ddf88);
  *(FARPROC *)(param_1 + 0x14) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x30),s__SmackOpen_12_004ddf78);
  *(FARPROC *)(param_1 + 0x18) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x30),s__SmackClose_4_004ddf68);
  *(FARPROC *)(param_1 + 0x1c) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x30),s__SmackWait_4_004ddf58);
  *(FARPROC *)(param_1 + 0x20) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x30),s__SmackToBuffer_28_004ddf44);
  *(FARPROC *)(param_1 + 0x24) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x30),s__SmackDoFrame_4_004ddf34);
  *(FARPROC *)(param_1 + 0x28) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x30),s__SmackNextFrame_4_004ddf20);
  *(FARPROC *)(param_1 + 0x2c) = pFVar1;
  if ((((*(int *)(param_1 + 0x14) != 0) && (*(int *)(param_1 + 0x18) != 0)) &&
      (*(int *)(param_1 + 0x1c) != 0)) &&
     (((*(int *)(param_1 + 0x20) != 0 && (*(int *)(param_1 + 0x24) != 0)) &&
      ((*(int *)(param_1 + 0x28) != 0 && (pFVar1 != (FARPROC)0x0)))))) {
    iVar2 = FUN_00410170();
    if (*(int *)(iVar2 + 0x124) == 0) {
      (**(code **)(param_1 + 0x14))(0);
      return 0;
    }
    iVar2 = FUN_00410170();
    (**(code **)(param_1 + 0x14))(*(undefined4 *)(iVar2 + 0x130));
    return 0;
  }
  FUN_00436670((byte *)s_Invalid_smackw32_dll__video_play_004ddef0,unaff_ESI);
  FreeLibrary(*(HMODULE *)(param_1 + 0x30));
  *(undefined4 *)(param_1 + 0x30) = 0;
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SmackVideoMgr__Init_004ddf9c);
  }
  return 0x49;
}


/* 004a1a00 size=259 */

int __thiscall
FUN_004a1a00(void *this,undefined4 param_1,uint param_2,undefined4 *param_3,int param_4)

{
  int *piVar1;
  void *this_00;
  int *this_01;
  int iVar2;
  
  *param_3 = 0;
  this_00 = (void *)FUN_00430de0(0xb0);
  if (this_00 != (void *)0x0) {
    this_01 = FUN_004a1b50(this_00,this);
    if (this_01 != (int *)0x0) {
      iVar2 = FUN_004a1c90(this_01,param_1,param_2,param_4);
      if (iVar2 != 0) {
        (**(code **)(*this_01 + 4))();
        return iVar2;
      }
      if (param_4 == 0) {
        iVar2 = FUN_004a1d20(this_01);
      }
      else {
        iVar2 = FUN_004a1f80(this_01);
      }
      if (iVar2 != 0) {
        (**(code **)(*this_01 + 4))();
        return iVar2;
      }
      piVar1 = this_01 + 1;
      if (*(int **)((int)this + 8) == (int *)0x0) {
        this_01[2] = (int)piVar1;
        *piVar1 = (int)piVar1;
        this_01[3] = (int)this_01;
        *(int **)((int)this + 8) = piVar1;
      }
      else {
        iVar2 = **(int **)((int)this + 8);
        **(int **)(iVar2 + 4) = (int)piVar1;
        this_01[2] = *(int *)(iVar2 + 4);
        *piVar1 = iVar2;
        *(int **)(iVar2 + 4) = piVar1;
        this_01[3] = (int)this_01;
      }
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
      *param_3 = this_01;
      return 0;
    }
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SmackVideoMgr_004ddff8);
  }
  return 0x43;
}


/* 004a1b50 size=68 */

undefined4 * __thiscall FUN_004a1b50(void *this,undefined4 param_1)

{
  *(undefined ***)this = &PTR_LAB_004cb4bc;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined ***)((int)this + 0x2c) = &PTR_FUN_004cbb4c;
  FUN_0042e120((void *)((int)this + 0x68));
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = param_1;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 100) = 0;
  *(undefined4 *)((int)this + 0x28) = 0;
  *(undefined ***)this = &PTR_FUN_004cdaf0;
  return this;
}


/* 004a1ba0 size=30 */

int * __thiscall FUN_004a1ba0(void *this,byte param_1)

{
  FUN_004a1bc0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004a1bc0 size=38 */

void __fastcall FUN_004a1bc0(int *param_1)

{
  *param_1 = (int)&PTR_FUN_004cdaf0;
  FUN_004a1bf0(param_1);
  FUN_0042e160(param_1 + 0x1a);
  param_1[5] = 0;
  param_1[4] = 0;
  *param_1 = (int)&PTR_LAB_004cb4bc;
  return;
}


/* 004a1bf0 size=152 */

void __fastcall FUN_004a1bf0(int *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  
  (**(code **)(*param_1 + 0xc))();
  if (param_1[6] != 0) {
    (**(code **)(param_1[7] + 0x1c))(param_1[6]);
    param_1[6] = 0;
  }
  if ((undefined4 *)param_1[0x19] != (undefined4 *)0x0) {
    FUN_00436de0((undefined4 *)param_1[0x19]);
    param_1[0x19] = 0;
  }
  uVar3 = param_1[5];
  while (uVar3 != 0) {
    piVar1 = (int *)(uVar3 + 8);
    uVar3 = *(uint *)(uVar3 + 4) & -(uint)(*(uint *)(uVar3 + 4) != param_1[5]);
    iVar2 = *(int *)*piVar1;
    if (iVar2 != 0) {
      *(int *)(iVar2 + 0x2c) = ((int *)*piVar1)[4];
    }
  }
  uVar3 = param_1[5];
  while (uVar3 != 0) {
    piVar1 = *(int **)(uVar3 + 8);
    uVar3 = *(uint *)(uVar3 + 4) & -(uint)(*(uint *)(uVar3 + 4) != param_1[5]);
    if (piVar1 != (int *)0x0) {
      FUN_004a15a0(piVar1);
      FUN_00430df0((undefined *)piVar1);
    }
  }
  param_1[5] = 0;
  param_1[4] = 0;
  return;
}


/* 004a1c90 size=140 */

undefined4 __thiscall FUN_004a1c90(void *this,undefined4 param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (-(uint)(param_3 != 0) & 0xfff02000) + 0xfe000;
  if ((param_2 & 2) != 0) {
    uVar1 = uVar1 | 0x100000;
  }
  iVar2 = (**(code **)(*(int *)((int)this + 0x1c) + 0x18))(param_1,uVar1,0xffffffff);
  *(int *)((int)this + 0x18) = iVar2;
  if (iVar2 != 0) {
    *(int *)((int)this + 0xac) = param_3;
    *(uint *)((int)this + 0xa8) = param_2;
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SmackVideoInst__Init_004de008);
  }
  return 0x16;
}


/* 004a1d20 size=606 */

/* FUN_004a1d20: lifted from original x86 -> lt_lifted.c */


/* 004a1f80 size=286 */

undefined4 __fastcall FUN_004a1f80(int *param_1)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined1 auStack_3ff [1023];
  
  (**(code **)(*param_1 + 0xc))();
  iVar4 = param_1[6];
  if (iVar4 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_SmackVideoInst__InitTexture_004de050);
    }
    return 0x49;
  }
  puVar1 = FUN_00436890(3,*(uint *)(iVar4 + 4),*(uint *)(iVar4 + 8),1,(undefined4 *)0x0,
                        (size_t *)0x0,0);
  param_1[0x19] = (int)puVar1;
  if (puVar1 == (undefined4 *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_SmackVideoInst__InitTexture_004de050);
    }
    return 0x43;
  }
  puVar3 = auStack_3ff + 1;
  iVar4 = 0x100;
  puVar2 = (undefined1 *)(param_1[6] + 0x6d);
  do {
    puVar3[-1] = puVar2[-1];
    *puVar3 = *puVar2;
    puVar3[1] = puVar2[1];
    puVar3 = puVar3 + 4;
    iVar4 = iVar4 + -1;
    puVar2 = puVar2 + 3;
  } while (iVar4 != 0);
  puVar1[0x31] = puVar1[0x31] | 2;
  *(uint *)(param_1[0x19] + 0x18) = *(uint *)(param_1[0x19] + 0x18) | 0x40;
  param_1[0x1c] = param_1[0x19];
  FUN_00471750(param_1 + 0x1a,1);
  return 0;
}


/* 004a20a0 size=49 */

void __fastcall FUN_004a20a0(int *param_1)

{
  int iVar1;
  
  if (param_1[0x2b] == 0) {
    iVar1 = FUN_004a1d20(param_1);
    if (iVar1 != 0) {
      FUN_004a1bf0(param_1);
      return;
    }
  }
  else {
    iVar1 = FUN_004a1f80(param_1);
    if (iVar1 != 0) {
      FUN_004a1bf0(param_1);
    }
  }
  return;
}


/* 004a20e0 size=73 */

void __fastcall FUN_004a20e0(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x20);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  piVar1 = *(int **)(param_1 + 0x28);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  if (*(int *)(param_1 + 100) != 0) {
    FUN_00471770(param_1 + 0x68);
    *(undefined4 *)(param_1 + 0x70) = 0;
    FUN_00436de0(*(undefined4 **)(param_1 + 100));
    *(undefined4 *)(param_1 + 100) = 0;
  }
  return;
}


/* 004a21b0 size=59 */

void __thiscall FUN_004a21b0(void *this,int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  
  uVar2 = *(uint *)((int)this + 0x14);
  while (uVar2 != 0) {
    puVar1 = (undefined4 *)(uVar2 + 8);
    uVar2 = *(uint *)(uVar2 + 4) & -(uint)(*(uint *)(uVar2 + 4) != *(uint *)((int)this + 0x14));
    if (*(int *)((int)*puVar1 + 0x10) == param_1) {
      videomgr_4a1600((void *)*puVar1,(int *)0x0);
    }
  }
  return;
}


/* 004a2250 size=192 */

undefined4 __thiscall FUN_004a2250(void *this,int param_1)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  
  pvVar3 = (void *)FUN_00430de0(0x2c);
  if (pvVar3 != (void *)0x0) {
    pvVar3 = (void *)FUN_004a1570(pvVar3,this);
    if (pvVar3 != (void *)0x0) {
      FUN_004a15c0(pvVar3,param_1);
      videomgr_4a1600(pvVar3,*(int **)(param_1 + 0x2c));
      piVar1 = (int *)((int)pvVar3 + 0x20);
      *(int *)(param_1 + 0x2c) = (int)this + 0x68;
      if (*(int **)((int)this + 0x14) == (int *)0x0) {
        *(int **)((int)pvVar3 + 0x24) = piVar1;
        *piVar1 = (int)piVar1;
        *(void **)((int)pvVar3 + 0x28) = pvVar3;
        *(int **)((int)this + 0x14) = piVar1;
        *(int *)((int)this + 0x10) = *(int *)((int)this + 0x10) + 1;
        return 0;
      }
      iVar2 = **(int **)((int)this + 0x14);
      **(int **)(iVar2 + 4) = (int)piVar1;
      *(undefined4 *)((int)pvVar3 + 0x24) = *(undefined4 *)(iVar2 + 4);
      *piVar1 = iVar2;
      *(int **)(iVar2 + 4) = piVar1;
      *(void **)((int)pvVar3 + 0x28) = pvVar3;
      *(int *)((int)this + 0x10) = *(int *)((int)this + 0x10) + 1;
      return 0;
    }
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_SmackVideoInst__BindToSurface_004de06c);
  }
  return 0x43;
}


/* 004a2390 size=35 */

bool __fastcall FUN_004a2390(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (iVar1 == 0) {
    return true;
  }
  return *(int *)(iVar1 + 0x374) == *(int *)(iVar1 + 0xc) + -1;
}


/* 004a27a0 size=188 */

undefined4 __fastcall FUN_004a27a0(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  undefined3 extraout_var_00;
  
  if ((*(int *)(param_1 + 0x18) == 0) || (*(int *)(param_1 + 100) == 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_SmackVideoInst__UpdateTextureVid_004de160);
    }
    return 2;
  }
  bVar1 = FUN_004a2390(param_1);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    return 0;
  }
  iVar2 = (**(code **)(*(int *)(param_1 + 0x1c) + 0x20))(*(undefined4 *)(param_1 + 0x18));
  if (iVar2 == 0) {
    (**(code **)(*(int *)(param_1 + 0x1c) + 0x24))
              (*(int *)(param_1 + 0x18),0,0,*(undefined4 *)(*(int *)(param_1 + 100) + 0xd8),
               *(undefined4 *)(*(int *)(param_1 + 0x18) + 8),
               *(undefined4 *)(*(int *)(param_1 + 100) + 0xd4),0);
    (**(code **)(*(int *)(param_1 + 0x1c) + 0x28))(*(undefined4 *)(param_1 + 0x18));
    FUN_00471750(param_1 + 0x68,1);
    bVar1 = FUN_004a2390(param_1);
    if (CONCAT31(extraout_var_00,bVar1) == 0) {
      (**(code **)(*(int *)(param_1 + 0x1c) + 0x2c))(*(undefined4 *)(param_1 + 0x18));
    }
  }
  return 0;
}


/* 004a2890 size=861 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004a2890: lifted from original x86 -> lt_lifted.c */


/* 004a2bf0 size=76 */

void __cdecl FUN_004a2bf0(undefined4 *param_1,uint *param_2,int *param_3)

{
  undefined4 *puVar1;
  
  for (puVar1 = (undefined4 *)*param_1; puVar1 != param_1; puVar1 = (undefined4 *)*puVar1) {
    if ((*param_2 < DAT_004ec474) && (*(int *)(puVar1[2] + 0x58) != *(int *)(DAT_004ec468 + 0x1c)))
    {
      *(undefined4 *)(*param_2 + *param_3 * 4) = puVar1[2];
      *param_3 = *param_3 + 1;
    }
  }
  return;
}


/* 004a2c40 size=43 */

byte FUN_004a2c40(void)

{
  byte bVar1;
  uint uVar2;
  
  bVar1 = (byte)DAT_004ec46c;
  uVar2 = DAT_004ec46c >> 3;
  DAT_004ec46c = DAT_004ec46c + 1;
  return '\x01' << (bVar1 & 7) & *(byte *)(uVar2 + DAT_004ec470);
}


/* 004a2c70 size=203 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __cdecl FUN_004a2c70(float *param_1,int *param_2,int param_3,int *param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = param_2;
  piVar2 = param_2;
  if (param_5 != 0) {
    piVar2 = param_2 + param_3;
  }
  *param_4 = 0;
  if ((piVar2 + param_3 < DAT_004ec474) && (param_3 != 0)) {
    param_2 = (int *)param_3;
    do {
      iVar1 = *piVar3;
      if ((*(int *)(iVar1 + 0x58) != *(int *)(DAT_004ec468 + 0x1c)) &&
         ((*(float *)(iVar1 + 0x194) * *param_1 +
          *(float *)(iVar1 + 0x198) * param_1[1] + *(float *)(iVar1 + 0x19c) * param_1[2]) -
          param_1[3] < *(float *)(iVar1 + 0x1ac) + _DAT_004cbeec)) {
        piVar2[*param_4] = iVar1;
        *param_4 = *param_4 + 1;
      }
      piVar3 = piVar3 + 1;
      param_2 = (int *)((int)param_2 + -1);
    } while (param_2 != (int *)0x0);
  }
  return piVar2;
}


/* 004a2d40 size=199 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __cdecl FUN_004a2d40(float *param_1,int *param_2,int param_3,int *param_4)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = param_2;
  *param_4 = 0;
  if (DAT_004ec474 <= param_2 + param_3) {
    return param_2;
  }
  if (param_3 != 0) {
    param_2 = (int *)param_3;
    piVar3 = piVar2;
    do {
      iVar1 = *piVar3;
      if ((*(int *)(iVar1 + 0x58) != *(int *)(DAT_004ec468 + 0x1c)) &&
         (-(*(float *)(iVar1 + 0x1ac) + _DAT_004cbeec) <
          (*(float *)(iVar1 + 0x194) * *param_1 +
          *(float *)(iVar1 + 0x198) * param_1[1] + *(float *)(iVar1 + 0x19c) * param_1[2]) -
          param_1[3])) {
        piVar2[*param_4] = iVar1;
        *param_4 = *param_4 + 1;
      }
      piVar3 = piVar3 + 1;
      param_2 = (int *)((int)param_2 + -1);
    } while (param_2 != (int *)0x0);
  }
  return piVar2;
}


/* 004a2e10 size=884 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004a2e10: lifted from original x86 -> lt_lifted.c */


/* 004a31c0 size=206 */

/* FUN_004a31c0: lifted from original x86 -> lt_lifted.c */


/* 004a3290 size=713 */

/* FUN_004a3290: lifted from original x86 -> lt_lifted.c */


/* 004a3560 size=410 */

void __cdecl FUN_004a3560(int param_1,int *param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  iVar3 = (*(code *)param_2[10])(param_1);
  if (iVar3 != 0) {
    iVar3 = *(int *)(param_1 + 0x14);
    if (iVar3 != param_1 + 0x10) {
      do {
        piVar1 = *(int **)(iVar3 + 8);
        iVar3 = *(int *)(iVar3 + 4);
        if (piVar1[0x16] != *(int *)(param_2[0x11] + 8)) {
          piVar1[0x16] = *(int *)(param_2[0x11] + 8);
          (**(code **)(*piVar1 + 0x1c))(param_2);
        }
      } while (iVar3 != param_1 + 0x10);
      return;
    }
    iVar3 = *param_2;
    iVar2 = *(int *)(param_1 + 4 + iVar3 * 8);
    while (iVar2 != param_1 + iVar3 * 8) {
      piVar1 = *(int **)(iVar2 + 8);
      iVar2 = *(int *)(iVar2 + 4);
      if (piVar1[0x16] != *(int *)(param_2[0x11] + 8)) {
        piVar1[0x16] = *(int *)(param_2[0x11] + 8);
        (**(code **)(*piVar1 + 0xc))(&fStack_18,&fStack_c);
        if ((((fStack_18 <= (float)param_2[0xe]) && (fStack_14 <= (float)param_2[0xf])) &&
            (fStack_10 <= (float)param_2[0x10])) &&
           ((((float)param_2[0xb] <= fStack_c && ((float)param_2[0xc] <= fStack_8)) &&
            ((float)param_2[0xd] <= fStack_4)))) {
          (*(code *)param_2[5])(piVar1,param_2[7]);
        }
      }
    }
    if (*(int *)(param_1 + 0x4c) != 0) {
      if ((float)param_2[0xb] < *(float *)(param_1 + 0x30)) {
        if ((float)param_2[0xd] < *(float *)(param_1 + 0x38)) {
          FUN_004a3560(*(int *)(param_1 + 0x4c),param_2,param_3 + 1);
        }
        if (*(float *)(param_1 + 0x38) < (float)param_2[0x10]) {
          FUN_004a3560(*(int *)(param_1 + 0x50),param_2,param_3 + 1);
        }
      }
      if (*(float *)(param_1 + 0x30) < (float)param_2[0xe]) {
        if ((float)param_2[0xd] < *(float *)(param_1 + 0x38)) {
          FUN_004a3560(*(int *)(param_1 + 0x54),param_2,param_3 + 1);
        }
        if (*(float *)(param_1 + 0x38) < (float)param_2[0x10]) {
          FUN_004a3560(*(int *)(param_1 + 0x58),param_2,param_3 + 1);
        }
      }
    }
  }
  return;
}


/* 004a3700 size=54 */

void __thiscall FUN_004a3700(void *this,undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 5;
  *(undefined ***)this = &PTR_FUN_004cdb24;
  iVar2 = (int)this + 4;
  do {
    *(int *)(iVar2 + 4) = iVar2;
    *(int *)iVar2 = iVar2;
    *(void **)(iVar2 + 8) = this;
    *(undefined4 *)(iVar2 + 0xc) = 0;
    iVar2 = iVar2 + 0x10;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *(undefined4 *)((int)this + 0x58) = 0xffffffff;
  *(undefined4 *)((int)this + 0x54) = param_1;
  return;
}


/* 004a3740 size=11 */

void __fastcall FUN_004a3740(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cdb24;
  FUN_004a3750((int)param_1);
  return;
}


/* 004a3750 size=74 */

void __fastcall FUN_004a3750(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
  piVar2 = (int *)(param_1 + 4);
  iVar3 = 5;
  do {
    *(int *)(*piVar2 + 4) = piVar2[1];
    *(int *)piVar2[1] = *piVar2;
    iVar1 = piVar2[3];
    piVar2[1] = (int)piVar2;
    *piVar2 = (int)piVar2;
    while (iVar1 != 0) {
      *(int *)(piVar2[3] + 0x44) = *(int *)(piVar2[3] + 0x44) + -1;
      iVar1 = *(int *)(piVar2[3] + 0x48);
      piVar2[3] = iVar1;
    }
    piVar2 = piVar2 + 4;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


/* 004a37a0 size=12 */

int __fastcall FUN_004a37a0(int param_1)

{
  FUN_004a37c0(param_1);
  return param_1;
}


/* 004a37c0 size=76 */

void __fastcall FUN_004a37c0(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  iVar2 = 3;
  iVar1 = param_1;
  do {
    *(int *)(iVar1 + 4) = iVar1;
    *(int *)iVar1 = iVar1;
    iVar1 = iVar1 + 8;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  return;
}


/* 004a3810 size=51 */

void __thiscall FUN_004a3810(void *this,undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *(undefined4 *)((int)this + 0x18);
  param_1[1] = *(undefined4 *)((int)this + 0x1c);
  param_1[2] = *(undefined4 *)((int)this + 0x20);
  *param_2 = *(undefined4 *)((int)this + 0x24);
  param_2[1] = *(undefined4 *)((int)this + 0x28);
  param_2[2] = *(undefined4 *)((int)this + 0x2c);
  return;
}


/* 004a3850 size=251 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004a3850: lifted from original x86 -> lt_lifted.c */


/* 004a3950 size=62 */

void __fastcall FUN_004a3950(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  FUN_004a3990(param_1);
  iVar3 = 3;
  iVar4 = param_1;
  do {
    iVar2 = *(int *)(iVar4 + 4);
    while (iVar2 != iVar4) {
      iVar1 = *(int *)(iVar2 + 4);
      (**(code **)(**(int **)(iVar2 + 8) + 8))();
      iVar2 = iVar1;
    }
    iVar4 = iVar4 + 8;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  FUN_004a37c0(param_1);
  return;
}


/* 004a3990 size=49 */

void __fastcall FUN_004a3990(int param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(param_1 + 0x4c);
  iVar2 = 4;
  do {
    puVar1 = (undefined *)*puVar3;
    if (puVar1 != (undefined *)0x0) {
      thunk_FUN_004a3950((int)puVar1);
      FUN_00430df0(puVar1);
      *puVar3 = 0;
    }
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


/* 004a39d0 size=155 */

undefined4 __thiscall FUN_004a39d0(void *this,int *param_1,byte *param_2,byte *param_3)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  FUN_004a3990((int)this);
  if (*param_3 == 8) {
    (**(code **)(*param_1 + 8))(param_2,1);
    *param_3 = 0;
  }
  bVar1 = *param_3;
  bVar2 = *param_2;
  *param_3 = bVar1 + 1;
  if (((byte)(1 << (bVar1 & 0x1f)) & bVar2) != 0) {
    iVar3 = FUN_004a3a70((int)this);
    if (iVar3 == 0) {
      return 0;
    }
    uVar4 = 0;
    puVar5 = (undefined4 *)((int)this + 0x4c);
    do {
      iVar3 = FUN_004a39d0((void *)*puVar5,param_1,param_2,param_3);
      if (iVar3 == 0) {
        FUN_004a3990((int)this);
        return 0;
      }
      uVar4 = uVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (uVar4 < 4);
  }
  return 1;
}


/* 004a3a70 size=590 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004a3a70: lifted from original x86 -> lt_lifted.c */


/* 004a3cc0 size=52 */

void __thiscall FUN_004a3cc0(void *this,int *param_1,int param_2)

{
  void *pvVar1;
  undefined4 *puVar2;
  
  pvVar1 = (void *)((int)this + param_2 * 8);
  *param_1 = (int)pvVar1;
  puVar2 = *(undefined4 **)((int)pvVar1 + 4);
  param_1[1] = (int)puVar2;
  *puVar2 = param_1;
  *(int **)(*param_1 + 4) = param_1;
  param_1[3] = (int)this;
  for (; this != (void *)0x0; this = *(void **)((int)this + 0x48)) {
    *(int *)((int)this + 0x44) = *(int *)((int)this + 0x44) + 1;
  }
  return;
}


/* 004a3d00 size=43 */

undefined4 * __fastcall FUN_004a3d00(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  FUN_004a37a0((int)(param_1 + 3));
  *param_1 = &PTR_FUN_004cdb44;
  param_1[1] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[0x1c] = 0;
  puVar1 = param_1 + 0x1d;
  param_1[0x1e] = puVar1;
  *puVar1 = puVar1;
  return param_1;
}


/* 004a3d30 size=8 */

void __fastcall FUN_004a3d30(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x004a3d35. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)(param_1 + 4) + 4))();
  return;
}


/* 004a3d40 size=18 */

void __thiscall FUN_004a3d40(void *this,undefined4 param_1)

{
  int iVar1;
  
  *(undefined4 *)((int)this + 4) = param_1;
  iVar1 = (int)this + 0x74;
  *(int *)((int)this + 0x78) = iVar1;
  *(int *)iVar1 = iVar1;
  return;
}


/* 004a3d60 size=45 */

void __fastcall FUN_004a3d60(int param_1)

{
  undefined4 *puVar1;
  
  FUN_004a3950(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  puVar1 = (undefined4 *)(param_1 + 0x74);
  *(undefined4 *)(*(int *)(param_1 + 0x74) + 4) = *(undefined4 *)(param_1 + 0x78);
  **(undefined4 **)(param_1 + 0x78) = *puVar1;
  *(undefined4 **)(param_1 + 0x78) = puVar1;
  *puVar1 = puVar1;
  return;
}


/* 004a3d90 size=87 */

int __thiscall FUN_004a3d90(void *this,int param_1)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  iVar3 = (int)this + 0xc;
  iVar5 = 0;
  iVar4 = 0;
  uVar6 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    while (*(int *)(iVar3 + 0x4c) != 0) {
      bVar2 = (byte)iVar4;
      pbVar1 = (byte *)(uVar6 + param_1);
      iVar4 = iVar4 + 2;
      if (iVar4 == 8) {
        uVar6 = uVar6 + 1;
        iVar4 = 0;
        if (3 < uVar6) break;
      }
      iVar3 = *(int *)(iVar3 + 0x4c + (*pbVar1 >> (bVar2 & 0x1f) & 3) * 4);
      iVar5 = iVar5 + 1;
      if (iVar5 == *(int *)(param_1 + 4)) {
        return iVar3;
      }
    }
    iVar3 = 0;
  }
  return iVar3;
}


/* 004a3df0 size=59 */

void __thiscall FUN_004a3df0(void *this,int *param_1)

{
  undefined4 unaff_retaddr;
  undefined1 local_18 [4];
  float afStack_14 [2];
  undefined1 local_c [12];
  
  (**(code **)(*param_1 + 0xc))(local_c,local_18);
  FUN_004a3e30(this,param_1,afStack_14,(float *)(local_18 + -8),unaff_retaddr);
  return;
}


/* 004a3e30 size=189 */

void __thiscall
FUN_004a3e30(void *this,int *param_1,float *param_2,float *param_3,undefined4 param_4)

{
  int iVar1;
  float fStack_2c;
  int *piStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  (**(code **)(*param_1 + 8))();
  piStack_28 = param_1;
  fStack_8 = *param_3 - *param_2;
  fStack_2c = param_3[2] - param_2[2];
  uStack_24 = param_4;
  fStack_20 = *param_2;
  fStack_1c = param_2[1];
  fStack_18 = param_2[2];
  fStack_14 = *param_3;
  fStack_10 = param_3[1];
  fStack_c = param_3[2];
  if (fStack_8 <= fStack_2c) {
    fStack_8 = fStack_2c;
  }
  uStack_4 = 0;
  iVar1 = (**(code **)(*param_1 + 4))(this);
  if (iVar1 == 0) {
    FUN_004a3ef0((void *)((int)this + 0xc),(int *)&fStack_2c);
  }
  return;
}


/* 004a3ef0 size=258 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004a3ef0: lifted from original x86 -> lt_lifted.c */


