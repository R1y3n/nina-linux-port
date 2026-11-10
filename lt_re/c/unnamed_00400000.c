/* lithtech.exe decompilation - unnamed_00400000 */
#include "ghidra_types.h"

/* 00401000 size=42 */

void FUN_00401000(undefined4 param_1,undefined4 param_2,int param_3,undefined *param_4)

{
  if (-1 < param_3 + -1) {
    do {
      (*(code *)param_4)();
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}


/* 00401030 size=21 */

void __thiscall FUN_00401030(void *this,undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)((int)this + 0x28);
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


/* 00401050 size=157 */

void __cdecl FUN_00401050(int param_1,int param_2,uint param_3)

{
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(int *)(param_1 + 0x28) = param_2;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined2 *)(param_1 + 0x18) = 0;
  *(undefined2 *)(param_1 + 0x1a) = 0;
  *(undefined4 *)(param_1 + 0x20) = 1;
  *(undefined4 *)(param_1 + 0x1c) = 1;
  *(undefined4 *)(param_1 + 0x24) = 1;
  *(undefined2 *)(param_1 + 0x2c) = 0;
  *(undefined2 *)(param_1 + 0x2e) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined2 *)(param_1 + 0x38) = 0;
  *(undefined2 *)(param_1 + 0x3a) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  if (param_2 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 2;
    return;
  }
  if (((*(ushort *)(param_1 + 0x18) & 8) == 0) && (*(uint *)(param_2 + 0x16c) <= param_3)) {
    param_3 = 0;
  }
  *(short *)(param_1 + 0x38) = (short)param_3;
  *(ushort *)(param_1 + 0x18) = *(ushort *)(param_1 + 0x18) | 1;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 2;
  *(short *)(param_1 + 0x2c) = (short)param_3;
  *(undefined2 *)(param_1 + 0x3a) = 0;
  *(undefined2 *)(param_1 + 0x2e) = 0;
  *(undefined2 *)(param_1 + 0x1a) = 0xffff;
  return;
}


/* 004010f0 size=51 */

void __cdecl FUN_004010f0(uint param_1,int param_2)

{
  if ((*(byte *)(param_1 + 0x18) & 1) != 0) {
    if (*(int *)(param_1 + 0x1c) == 0) {
      *(undefined4 *)(param_1 + 0x1c) = 1;
    }
    FUN_00401400(param_1,(uint)(*(int *)(param_1 + 0x20) * param_2) / *(uint *)(param_1 + 0x1c),1);
  }
  return;
}


/* 00401130 size=104 */

undefined4 __cdecl FUN_00401130(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_1 + 0x28);
  if (iVar1 != 0) {
    if ((((uint)*(ushort *)(param_1 + 0x38) < *(uint *)(iVar1 + 0x16c)) &&
        ((uint)*(ushort *)(param_1 + 0x2c) < *(uint *)(iVar1 + 0x16c))) &&
       (iVar1 = *(int *)(*(int *)(iVar1 + 0x168) + (uint)*(ushort *)(param_1 + 0x38) * 0x20),
       (*(byte *)(param_1 + 0x18) & 2) == 0)) {
      uVar2 = *(uint *)(iVar1 + 0x10);
      if (uVar2 < 2) {
        return 1;
      }
      if (*(int *)(param_1 + 0x3c) == *(int *)(*(int *)(iVar1 + 0xc) + -0x14 + uVar2 * 0x14) + 1) {
        return 1;
      }
    }
  }
  return 0;
}


/* 004011a0 size=90 */

void __cdecl FUN_004011a0(uint param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  if ((((*(int *)(param_1 + 0x28) == 0) ||
       (uVar1 = *(uint *)(*(int *)(param_1 + 0x28) + 0x16c), uVar1 <= *(ushort *)(param_1 + 0x38)))
      || (uVar1 <= *(ushort *)(param_1 + 0x2c))) || (param_3 == 0)) {
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
    *(undefined2 *)(param_1 + 0x3a) = 0;
    *(undefined2 *)(param_1 + 0x2e) = 0;
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined2 *)(param_1 + 0x3a) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  FUN_00401400(param_1,param_2,0);
  return;
}


/* 00401200 size=223 */

undefined4 __cdecl FUN_00401200(int param_1,uint param_2,uint param_3)

{
  undefined4 *puVar1;
  ushort *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  if (((*(byte *)(param_1 + 0x18) & 8) == 0) &&
     (*(uint *)(*(int *)(param_1 + 0x28) + 0x16c) <= param_2)) {
    return 0;
  }
  uVar3 = *(undefined4 *)(param_1 + 0x34);
  puVar1 = (undefined4 *)(param_1 + 0x38);
  puVar2 = (ushort *)(param_1 + 0x2c);
  *(undefined4 *)puVar2 = *puVar1;
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x3c);
  *(short *)puVar1 = (short)param_2;
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(param_1 + 0x34) = uVar3;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined2 *)(param_1 + 0x3a) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  if (param_3 != 0) {
    iVar4 = *(int *)(param_1 + 0x28);
    iVar5 = *(int *)(param_2 * 0x20 + *(int *)(iVar4 + 0x168));
    if (iVar5 != 0) {
      param_3 = (uint)(*(int *)(iVar5 + 0x1c) != 0);
    }
    if ((((param_3 != 0) && (iVar4 != 0)) && ((param_2 & 0xffff) < *(uint *)(iVar4 + 0x16c))) &&
       (((uint)*puVar2 < *(uint *)(iVar4 + 0x16c) && (*(int *)(param_1 + 0x24) != 0)))) {
      *(undefined2 *)(param_1 + 0x1a) = 0;
      return 1;
    }
  }
  *(undefined2 *)(param_1 + 0x1a) = 0xffff;
  *(undefined4 *)puVar2 = *puVar1;
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x40);
  return 1;
}


/* 004012e0 size=41 */

void __cdecl FUN_004012e0(int param_1)

{
  *(undefined2 *)(param_1 + 0x2c) = *(undefined2 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined2 *)(param_1 + 0x3a) = 0;
  *(undefined2 *)(param_1 + 0x2e) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  return;
}


/* 00401310 size=234 */

void __cdecl FUN_00401310(int param_1,uint param_2)

{
  short sVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  FUN_004012e0(param_1);
  iVar2 = *(int *)((uint)*(ushort *)(param_1 + 0x38) * 0x20 +
                  *(int *)(*(int *)(param_1 + 0x28) + 0x168));
  if (1 < *(uint *)(iVar2 + 0x10)) {
    uVar7 = *(uint *)(iVar2 + 0x10) - 1;
    uVar6 = *(uint *)(*(int *)(iVar2 + 0xc) + uVar7 * 0x14);
    if (uVar6 < param_2) {
      param_2 = uVar6;
    }
    if ((*(byte *)(param_1 + 0x18) & 2) == 0) {
      uVar4 = uVar6 + 1;
      if (*(uint *)(param_1 + 0x3c) < uVar6 + 1) {
        uVar4 = *(uint *)(param_1 + 0x3c);
      }
      *(uint *)(param_1 + 0x3c) = uVar4;
    }
    uVar6 = 0;
    if (*(uint *)(param_1 + 0x14) <= uVar7) {
      while( true ) {
        uVar4 = *(uint *)(*(int *)(iVar2 + 0xc) + *(int *)(param_1 + 0x14) * 0x14);
        if (param_2 <= uVar4) break;
        uVar5 = *(int *)(param_1 + 0x14) + 1;
        *(uint *)(param_1 + 0x14) = uVar5;
        uVar6 = uVar4;
        if (uVar7 < uVar5) {
          return;
        }
      }
      sVar1 = *(short *)(param_1 + 0x14);
      if (sVar1 == 0) {
        sVar3 = 0;
      }
      else {
        sVar3 = sVar1 + -1;
      }
      *(short *)(param_1 + 0x2e) = sVar3;
      *(short *)(param_1 + 0x3a) = sVar1;
      if (uVar4 - uVar6 == 0) {
        *(undefined4 *)(param_1 + 0x44) = 0;
        return;
      }
      *(uint *)(param_1 + 0x3c) = param_2;
      *(uint *)(param_1 + 0x30) = uVar6;
      *(float *)(param_1 + 0x44) = (float)(param_2 - uVar6) / (float)(int)(uVar4 - uVar6);
    }
  }
  return;
}


/* 00401400 size=511 */

uint __cdecl FUN_00401400(uint param_1,uint param_2,int param_3)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  iVar2 = *(int *)(param_1 + 0x28);
  if (iVar2 == 0) {
LAB_0040142e:
    *(uint *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + param_2;
    return param_2;
  }
  if ((*(uint *)(iVar2 + 0x16c) <= (uint)*(ushort *)(param_1 + 0x38)) ||
     (*(uint *)(iVar2 + 0x16c) <= (uint)*(ushort *)(param_1 + 0x2c))) goto LAB_0040142e;
  iVar5 = (uint)*(ushort *)(param_1 + 0x38) * 0x20;
  iVar2 = *(int *)(*(int *)(iVar2 + 0x168) + iVar5);
  uVar6 = CONCAT22((short)((uint)iVar5 >> 0x10),*(short *)(param_1 + 0x1a));
  if (*(short *)(param_1 + 0x1a) != -1) {
    *(short *)(param_1 + 0x1a) = (short)(uVar6 + param_2);
    uVar3 = *(uint *)(iVar2 + 0x1c);
    uVar6 = uVar6 + param_2 & 0xffff;
    if (uVar6 <= uVar3) {
      if (uVar3 != 0) {
        *(float *)(param_1 + 0x44) = (float)uVar6 / (float)(int)uVar3;
        return uVar6;
      }
      goto LAB_004015f4;
    }
    FUN_004012e0(param_1);
    uVar6 = *(uint *)(iVar2 + 0x1c);
    param_2 = *(ushort *)(param_1 + 0x1a) - uVar6;
    *(undefined2 *)(param_1 + 0x1a) = 0xffff;
  }
  uVar3 = *(uint *)(iVar2 + 0x10);
  if (uVar3 < 2) {
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x44) = 0;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    return uVar6;
  }
  uVar4 = *(uint *)(*(int *)(iVar2 + 0xc) + (uVar3 - 1) * 0x14);
  *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x3c);
  uVar6 = *(int *)(param_1 + 0x3c) + param_2;
  *(uint *)(param_1 + 0x3c) = uVar6;
  if ((*(byte *)(param_1 + 0x18) & 2) == 0) {
    if (uVar4 + 1 <= uVar6) {
      uVar6 = uVar4 + 1;
    }
    *(uint *)(param_1 + 0x3c) = uVar6;
  }
  uVar6 = *(uint *)(param_1 + 0x14);
  while ((uVar6 <= uVar3 - 1 &&
         (*(uint *)(*(int *)(iVar2 + 0xc) + *(int *)(param_1 + 0x14) * 0x14) <
          *(uint *)(param_1 + 0x3c)))) {
    if (param_3 != 0) {
      FUN_00401600(param_1,iVar2,*(int *)(param_1 + 0x14));
    }
    uVar6 = *(int *)(param_1 + 0x14) + 1;
    *(uint *)(param_1 + 0x14) = uVar6;
  }
  uVar6 = *(uint *)(param_1 + 0x14);
  if ((uVar6 == uVar3) && ((*(byte *)(param_1 + 0x18) & 2) != 0)) {
    uVar6 = *(uint *)(param_1 + 0x3c) / uVar4;
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) % uVar4;
  }
  if (param_3 == 0) {
    uVar1 = *(undefined2 *)(param_1 + 0x14);
    uVar6 = CONCAT22((short)(uVar6 >> 0x10),uVar1);
    *(undefined2 *)(param_1 + 0x3a) = uVar1;
    *(undefined2 *)(param_1 + 0x2e) = uVar1;
  }
  if ((*(ushort *)(param_1 + 0x2e) != *(ushort *)(param_1 + 0x3a)) &&
     (iVar2 = *(int *)(param_1 + 0x28), iVar2 != 0)) {
    uVar6 = (uint)*(ushort *)(param_1 + 0x38);
    if ((uVar6 < *(uint *)(iVar2 + 0x16c)) &&
       ((uint)*(ushort *)(param_1 + 0x2c) < *(uint *)(iVar2 + 0x16c))) {
      iVar5 = *(int *)(*(int *)(*(int *)((uint)*(ushort *)(param_1 + 0x2c) * 0x20 +
                                        *(int *)(iVar2 + 0x168)) + 0xc) +
                      (uint)*(ushort *)(param_1 + 0x2e) * 0x14);
      uVar6 = *(int *)(*(int *)(*(int *)(uVar6 * 0x20 + *(int *)(iVar2 + 0x168)) + 0xc) +
                      (uint)*(ushort *)(param_1 + 0x3a) * 0x14) - iVar5;
      *(float *)(param_1 + 0x44) =
           (float)(uint)(*(int *)(param_1 + 0x3c) - iVar5) / (float)(int)uVar6;
      return uVar6;
    }
  }
LAB_004015f4:
  *(undefined4 *)(param_1 + 0x44) = 0;
  return uVar6;
}


/* 00401600 size=256 */

/* FUN_00401600: lifted from original x86 -> lt_lifted.c */


/* 00401700 size=87 */

int __cdecl FUN_00401700(int param_1,uint param_2,uint *param_3)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = *(int *)((uint)*(ushort *)(param_1 + 0x38) * 0x20 +
                  *(int *)(*(int *)(param_1 + 0x28) + 0x168));
  if (iVar1 != 0) {
    if (param_2 < *(uint *)(iVar1 + 0x10)) {
      pcVar2 = (char *)(*(int *)(iVar1 + 0xc) + 8 + param_2 * 0x14);
      do {
        if (*pcVar2 == '\0') {
          *param_3 = param_2;
          return *(int *)(iVar1 + 0xc) + param_2 * 0x14;
        }
        param_2 = param_2 + 1;
        pcVar2 = pcVar2 + 0x14;
      } while (param_2 < *(uint *)(iVar1 + 0x10));
    }
  }
  return 0;
}


/* 00401790 size=50 */

undefined4 __cdecl FUN_00401790(LPCSTR param_1,undefined4 *param_2)

{
  HMODULE pHVar1;
  undefined4 *puVar2;
  
  pHVar1 = LoadLibraryA(param_1);
  if (pHVar1 == (HMODULE)0x0) {
    return 0;
  }
  puVar2 = FUN_00430f00(0xc);
  *puVar2 = pHVar1;
  puVar2[1] = 1;
  *param_2 = puVar2;
  return 0xffffffff;
}


/* 004017d0 size=31 */

void __cdecl FUN_004017d0(undefined4 *param_1)

{
  if (param_1[1] == 1) {
    FreeLibrary((HMODULE)*param_1);
  }
  FUN_00430fe0((undefined *)param_1);
  return;
}


/* 00401850 size=74 */

undefined4 __cdecl FUN_00401850(undefined4 *param_1,undefined4 *param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_2 = *param_1;
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_bm_SetInstanceHandle_004d5304);
  }
  return 0x3c;
}


/* 004018a0 size=19 */

int __cdecl FUN_004018a0(undefined4 *param_1,LPCSTR param_2)

{
  GetProcAddress((HMODULE)*param_1,param_2);
  return;
}


/* 004018f0 size=59 */

int __thiscall FUN_004018f0(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = param_1;
  *(undefined ***)this = &PTR_LAB_004cb480;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x28) = 0;
  *(undefined4 *)((int)this + 0x2c) = 0;
  *(undefined4 *)((int)this + 0x30) = 0;
  *(undefined4 *)((int)this + 0x34) = 0;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x48) = 0;
  return;
}


/* 00401930 size=46 */

void __fastcall FUN_00401930(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cb480;
  if ((HMODULE)param_1[0x12] != (HMODULE)0x0) {
    FreeLibrary((HMODULE)param_1[0x12]);
    param_1[0x12] = 0;
  }
  param_1[2] = 0;
  param_1[1] = 0;
  return;
}


/* 00401b60 size=256 */

int __thiscall
FUN_00401b60(void *this,undefined4 param_1,uint param_2,undefined4 *param_3,int param_4)

{
  int *piVar1;
  void *this_00;
  int *this_01;
  int iVar2;
  
  *param_3 = 0;
  this_00 = (void *)FUN_00430de0(0x74);
  if (this_00 != (void *)0x0) {
    this_01 = FUN_00401ca0(this_00,this);
    if (this_01 != (int *)0x0) {
      iVar2 = binkvideomgrimpl_401e10(this_01,param_1,param_2,param_4);
      if (iVar2 != 0) {
        (**(code **)(*this_01 + 4))();
        return iVar2;
      }
      if (param_4 == 0) {
        iVar2 = FUN_00401eb0(this_01);
      }
      else {
        iVar2 = FUN_00402120(this_01);
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
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_BinkVideoMgr_004d54b8);
  }
  return 0x43;
}


/* 00401ca0 size=58 */

undefined4 * __thiscall FUN_00401ca0(void *this,undefined4 param_1)

{
  *(undefined ***)this = &PTR_LAB_004cb4bc;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  FUN_0042e120((void *)((int)this + 0x28));
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = param_1;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x70) = 0;
  *(undefined ***)this = &PTR_FUN_004cb494;
  return this;
}


/* 00401d00 size=30 */

int * __thiscall FUN_00401d00(void *this,byte param_1)

{
  FUN_00401d20(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00401d20 size=38 */

void __fastcall FUN_00401d20(int *param_1)

{
  *param_1 = (int)&PTR_FUN_004cb494;
  FUN_00401d50(param_1);
  FUN_0042e160(param_1 + 10);
  param_1[5] = 0;
  param_1[4] = 0;
  *param_1 = (int)&PTR_LAB_004cb4bc;
  return;
}


/* 00401d50 size=182 */

void __fastcall FUN_00401d50(int *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  
  if (param_1[6] != 0) {
    iVar2 = (**(code **)(param_1[7] + 0x2c))(param_1[6]);
    while (iVar2 != 0) {
      iVar2 = (**(code **)(param_1[7] + 0x2c))(param_1[6]);
    }
    (**(code **)(param_1[7] + 0x28))(param_1[6]);
    param_1[6] = 0;
  }
  (**(code **)(*param_1 + 0xc))();
  if ((undefined4 *)param_1[9] != (undefined4 *)0x0) {
    FUN_00436de0((undefined4 *)param_1[9]);
    param_1[9] = 0;
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


/* 00401eb0 size=611 */

/* FUN_00401eb0: lifted from original x86 -> lt_lifted.c */


/* 00402120 size=212 */

undefined4 __fastcall FUN_00402120(int *param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  
  (**(code **)(*param_1 + 0xc))();
  puVar1 = (uint *)param_1[6];
  if (puVar1 == (uint *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_BinkVideoInst__InitTexture_004d558c);
    }
    return 0x49;
  }
  puVar2 = FUN_00436890(3,*puVar1,puVar1[1],1,(undefined4 *)0x0,(size_t *)0x0,0);
  param_1[9] = (int)puVar2;
  if (puVar2 != (undefined4 *)0x0) {
    puVar2[0x31] = puVar2[0x31] | 4;
    *(uint *)(param_1[9] + 0x18) = *(uint *)(param_1[9] + 0x18) | 0x40;
    param_1[0xc] = param_1[9];
    FUN_00471750(param_1 + 10,1);
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_BinkVideoInst__InitTexture_004d558c)
    ;
  }
  return 0x43;
}


/* 00402200 size=46 */

void __fastcall FUN_00402200(int *param_1)

{
  int iVar1;
  
  if (param_1[0x1b] == 0) {
    iVar1 = FUN_00401eb0(param_1);
    if (iVar1 != 0) {
      FUN_00401d50(param_1);
      return;
    }
  }
  else {
    iVar1 = FUN_00402120(param_1);
    if (iVar1 != 0) {
      FUN_00401d50(param_1);
    }
  }
  return;
}


/* 00402230 size=67 */

void __fastcall FUN_00402230(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x20);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    FUN_00471770(param_1 + 0x28);
    *(undefined4 *)(param_1 + 0x30) = 0;
    FUN_00436de0(*(undefined4 **)(param_1 + 0x24));
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  return;
}


/* 004022e0 size=192 */

undefined4 __thiscall FUN_004022e0(void *this,int param_1)

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
      *(int *)(param_1 + 0x2c) = (int)this + 0x28;
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
                 s_BinkVideoInst__BindToSurface_004d55a8);
  }
  return 0x43;
}


/* 004023a0 size=32 */

bool __fastcall FUN_004023a0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (iVar1 == 0) {
    return true;
  }
  return *(int *)(iVar1 + 0xc) == *(int *)(iVar1 + 8) + -1;
}


/* 00402620 size=218 */

undefined4 __fastcall FUN_00402620(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  undefined3 extraout_var_00;
  
  if ((*(int *)(param_1 + 0x18) == 0) || (*(int *)(param_1 + 0x24) == 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_BinkVideoInst__UpdateTextureVide_004d5618);
    }
    return 2;
  }
  bVar1 = FUN_004023a0(param_1);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    return 0;
  }
  iVar2 = (**(code **)(*(int *)(param_1 + 0x1c) + 0x2c))(*(undefined4 *)(param_1 + 0x18));
  if (iVar2 == 0) {
    (**(code **)(*(int *)(param_1 + 0x1c) + 0x30))
              (*(int *)(param_1 + 0x18),*(undefined4 *)(*(int *)(param_1 + 0x24) + 0xd4),
               *(undefined4 *)(*(int *)(param_1 + 0x24) + 0xd8),
               *(undefined4 *)(*(int *)(param_1 + 0x18) + 4),0,0,10);
    (**(code **)(*(int *)(param_1 + 0x1c) + 0x34))(*(undefined4 *)(param_1 + 0x18));
    FUN_00471750(param_1 + 0x28,1);
    bVar1 = FUN_004023a0(param_1);
    if (CONCAT31(extraout_var_00,bVar1) == 0) {
      (**(code **)(*(int *)(param_1 + 0x1c) + 0x38))(*(undefined4 *)(param_1 + 0x18));
    }
    else {
      iVar2 = *(int *)(param_1 + 0x1c);
      if (*(int *)(iVar2 + 0x50) != 0) {
        (**(code **)(iVar2 + 0x44))(*(undefined4 *)(iVar2 + 0x4c));
        return 0;
      }
    }
  }
  return 0;
}


/* 004027e0 size=100 */

void __cdecl FUN_004027e0(int param_1)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  if (0 < *(int *)(param_1 + 0x10)) {
    do {
      iVar5 = 0;
      piVar2 = (int *)(*(int *)(param_1 + 0xc) + iVar6 * 4);
      if (0 < *(short *)(*(int *)(*(int *)(param_1 + 0xc) + iVar6 * 4) + 0x18)) {
        iVar4 = 0;
        do {
          iVar3 = *(int *)(*piVar2 + 0x1c) + iVar4;
          sVar1 = *(short *)(iVar3 + 4);
          if ((7 < sVar1) || (sVar1 < 0)) {
            *(undefined2 *)(iVar3 + 4) = 8;
          }
          iVar5 = iVar5 + 1;
          iVar4 = iVar4 + 0x2c;
          piVar2 = (int *)(*(int *)(param_1 + 0xc) + iVar6 * 4);
        } while (iVar5 < *(short *)(*(int *)(*(int *)(param_1 + 0xc) + iVar6 * 4) + 0x18));
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < *(int *)(param_1 + 0x10));
  }
  return;
}


/* 00402850 size=25 */

void __cdecl FUN_00402850(undefined *param_1)

{
  FUN_004017d0(*(undefined4 **)(param_1 + 8));
  FUN_004b9d3f(param_1);
  return;
}


/* 00402870 size=8 */

undefined4 __cdecl FUN_00402870(int param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}


/* 00402880 size=8 */

undefined4 __cdecl FUN_00402880(int param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}


/* 00402890 size=106 */

undefined4 __cdecl FUN_00402890(int param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  bool bVar7;
  
  iVar4 = 0;
  if (0 < *(int *)(param_1 + 0x10)) {
    puVar6 = *(undefined4 **)(param_1 + 0xc);
    do {
      pbVar2 = *(byte **)*puVar6;
      pbVar5 = param_2;
      do {
        bVar1 = *pbVar2;
        bVar7 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_004028d6:
          iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_004028db;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar7 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_004028d6;
        pbVar2 = pbVar2 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_004028db:
      if (iVar3 == 0) {
        return (*(undefined4 **)(param_1 + 0xc))[iVar4];
      }
      iVar4 = iVar4 + 1;
      puVar6 = puVar6 + 1;
    } while (iVar4 < *(int *)(param_1 + 0x10));
  }
  return 0;
}


/* 00402900 size=27 */

int __cdecl FUN_00402900(undefined4 param_1,int param_2,uint param_3)

{
  while( true ) {
    if (param_2 == 0) {
      return 0;
    }
    if ((*(uint *)(param_2 + 8) & param_3) != 0) break;
    param_2 = *(int *)(param_2 + 4);
  }
  return param_2;
}


/* 00402920 size=18 */

undefined4 * __fastcall FUN_00402920(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return param_1;
}


/* 00402950 size=30 */

undefined4 __thiscall FUN_00402950(void *this,undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = this;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)((int)this + 0x2c) = param_1;
  return 1;
}


/* 00402970 size=176 */

void __fastcall FUN_00402970(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((int *)param_1[9] != (int *)0x0) {
    FUN_00434d00((int *)param_1[9]);
    param_1[9] = 0;
  }
  if (param_1[7] != 0) {
    iVar2 = 0;
    if (0 < (int)param_1[8]) {
      iVar3 = 0;
      do {
        FUN_004b7c50(iVar3 + 8 + param_1[7]);
        iVar2 = iVar2 + 1;
        iVar1 = iVar3 + 0x24;
        iVar3 = iVar3 + 0x4c;
        *(undefined4 *)(*(int *)(iVar1 + param_1[7]) + 0x24 + param_1[10] * 4) = 0;
      } while (iVar2 < (int)param_1[8]);
    }
    FUN_00430df0((undefined *)param_1[7]);
    param_1[7] = 0;
  }
  if (param_1[5] != 0) {
    (*(code *)param_1[4])(param_1[5]);
  }
  if ((undefined4 *)param_1[2] != (undefined4 *)0x0) {
    FUN_0048e3a0((undefined4 *)param_1[2]);
  }
  if ((undefined *)*param_1 != (undefined *)0x0) {
    FUN_00402850((undefined *)*param_1);
  }
  if ((undefined4 *)param_1[1] != (undefined4 *)0x0) {
    FUN_004017d0((undefined4 *)param_1[1]);
    param_1[1] = 0;
  }
  param_1[2] = 0;
  *param_1 = 0;
  param_1[5] = 0;
  return;
}


/* 00402a20 size=57 */

undefined4 __thiscall FUN_00402a20(void *this,char *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  char *pcVar5;
  
  uVar4 = 0xffffffff;
  pcVar5 = param_1;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  iVar2 = FUN_00434ec0(*(int **)((int)this + 0x24),param_1,~uVar4 - 1);
  if (iVar2 == 0) {
    return 0;
  }
  uVar3 = FUN_00434fd0(iVar2);
  return uVar3;
}


/* 00402b60 size=444 */

undefined4 __cdecl FUN_00402b60(int *param_1)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  int local_8;
  
  piVar2 = param_1;
  piVar3 = (int *)FUN_00402880(*param_1);
  iVar4 = FUN_00402870(*param_1);
  iVar10 = 0;
  if (0 < iVar4) {
    if (*(int *)(*piVar3 + 0x24) == 0) {
      param_1[10] = 0;
    }
    else {
      if (*(int *)(*piVar3 + 0x28) != 0) {
        FUN_004356e0();
joined_r0x00402bb2:
        if (DAT_004e4420 < 1) {
          return 1;
        }
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_InitExtraClassData_004d5688);
        return 1;
      }
      param_1[10] = 1;
    }
    piVar5 = FUN_00434a60(0x32,2);
    param_1[9] = (int)piVar5;
    puVar6 = (undefined4 *)FUN_00430de0(iVar4 * 0x4c);
    if (puVar6 == (undefined4 *)0x0) {
      puVar6 = (undefined4 *)0x0;
    }
    else if (-1 < iVar4 + -1) {
      puVar7 = puVar6 + 0xc;
      iVar9 = iVar4;
      do {
        puVar7[-1] = 0;
        *puVar7 = 0;
        puVar7[1] = 0;
        puVar7[2] = 0;
        puVar7[3] = 0;
        puVar7[4] = 0;
        puVar7[5] = 0;
        puVar7 = puVar7 + 0x13;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
    }
    param_1[7] = (int)puVar6;
    param_1[8] = iVar4;
    for (uVar8 = (uint)(iVar4 * 0x4c) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
      *(undefined1 *)puVar6 = 0;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    if (0 < iVar4) {
      local_8 = 0;
      param_1 = piVar3;
      do {
        puVar6 = (undefined4 *)*param_1;
        iVar9 = piVar2[7] + local_8;
        FUN_004b7be0((uint *)(iVar9 + 8),puVar6[8],0x20,8);
        *(short *)(iVar9 + 0x28) = (short)iVar10;
        *(undefined4 **)(iVar9 + 0x24) = puVar6;
        puVar6[piVar2[10] + 9] = iVar9;
        uVar8 = 0xffffffff;
        pcVar11 = (char *)*puVar6;
        do {
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar11 + 1;
        } while (cVar1 != '\0');
        piVar3 = FUN_00434d70((int *)piVar2[9],(undefined4 *)*puVar6,~uVar8 - 1);
        if (piVar3 == (int *)0x0) {
          FUN_004356e0();
          goto joined_r0x00402bb2;
        }
        FUN_00434fe0((int)piVar3,iVar9);
        iVar10 = iVar10 + 1;
        param_1 = param_1 + 1;
        local_8 = local_8 + 0x4c;
        if (iVar4 <= iVar10) {
          return 1;
        }
      } while( true );
    }
  }
  return 1;
}


/* 00402d20 size=65 */

void __cdecl FUN_00402d20(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)FUN_00402880(*param_1);
  iVar3 = FUN_00402870(*param_1);
  if (0 < iVar3) {
    do {
      iVar1 = *piVar2;
      FUN_00402d70(iVar1,0xc);
      FUN_00402d70(iVar1,0x10);
      piVar2 = piVar2 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}


/* 00402d70 size=45 */

void __cdecl FUN_00402d70(int param_1,int param_2)

{
  if ((*(int *)(param_1 + param_2) == 0) && (*(int *)(param_1 + 4) != 0)) {
    FUN_00402d70(*(int *)(param_1 + 4),param_2);
    *(undefined4 *)(param_1 + param_2) = *(undefined4 *)(param_2 + *(int *)(param_1 + 4));
  }
  return;
}


/* 00402da0 size=553 */

undefined4 __cdecl FUN_00402da0(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int *piVar4;
  int local_394;
  int local_390;
  ushort local_38c [22];
  undefined4 local_360;
  undefined4 local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined1 local_34c;
  undefined1 local_30c;
  undefined1 local_28c [512];
  undefined1 local_8c;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_38c[0] = 0;
  local_38c[1] = 0;
  local_38c[2] = 1;
  local_38c[3] = 0;
  local_38c[4] = 0;
  local_38c[5] = 0;
  local_38c[6] = 0;
  local_38c[7] = 0;
  local_38c[8] = 0;
  local_38c[9] = 0;
  local_38c[10] = 0;
  local_38c[0xb] = 0;
  local_38c[0xc] = 0;
  local_38c[0xd] = 0;
  local_38c[0xe] = 0;
  local_38c[0xf] = 0;
  local_38c[0x10] = 0;
  local_38c[0x11] = 0x3f80;
  local_38c[0x12] = 0;
  local_38c[0x13] = 0x3f80;
  local_38c[0x14] = 0;
  local_38c[0x15] = 0x3f80;
  FUN_00402fd0(&local_360,0,0,0,0x3f800000);
  puVar2 = local_28c;
  iVar3 = 4;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 0x80;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  local_390 = 0;
  if (*(int *)(param_1 + 0x20) < 1) {
    return 0;
  }
  local_394 = 0;
  do {
    local_38c[0] = 0;
    local_38c[1] = 0;
    local_38c[2] = 1;
    local_38c[3] = 0;
    local_38c[4] = 0;
    local_38c[5] = 0;
    local_38c[6] = 0;
    local_38c[7] = 0;
    local_38c[8] = 0;
    local_38c[9] = 0;
    local_38c[10] = 0;
    local_38c[0xb] = 0;
    local_38c[0xc] = 0;
    local_38c[0xd] = 0;
    local_38c[0xe] = 0;
    local_38c[0xf] = 0;
    local_38c[0x10] = 0;
    local_38c[0x11] = 0x3f80;
    local_38c[0x12] = 0;
    local_38c[0x13] = 0x3f80;
    local_38c[0x14] = 0;
    local_38c[0x15] = 0x3f80;
    local_360 = 0;
    local_35c = 0;
    local_358 = 0;
    local_354 = 0x3f800000;
    local_350 = 0;
    local_34c = 0;
    local_30c = 0;
    puVar2 = local_28c;
    iVar3 = 4;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 0x80;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    local_8c = 0;
    local_c = 0;
    local_8 = 0;
    local_4 = 1;
    iVar3 = *(int *)(*(int *)(param_1 + 0x1c) + 0x24 + local_394);
    if ((*(byte *)(iVar3 + 8) & 4) != 0) {
      iVar1 = *(int *)(iVar3 + 0x24 + *(int *)(*(int *)(param_1 + 0x2c) + 0xa44) * 4);
      piVar4 = *(int **)(iVar1 + 0x20);
      if (piVar4 == (int *)0x0) {
        FUN_004b7c60(iVar1 + 8,*(int *)(iVar1 + 0x10));
        piVar4 = *(int **)(iVar1 + 0x20);
        if (piVar4 != (int *)0x0) goto LAB_00402f56;
        piVar4 = (int *)0x0;
      }
      else {
LAB_00402f56:
        *(int *)(iVar1 + 0x20) = *piVar4;
      }
      piVar4[2] = 0;
      piVar4[1] = 0;
      (**(code **)(iVar3 + 0xc))(piVar4);
      FUN_00487270(*(int **)(param_1 + 0x2c),piVar4,iVar3,local_38c,0xffff,0,
                   (undefined4 *)(*(int *)(param_1 + 0x1c) + 0x48 + local_394));
    }
    local_390 = local_390 + 1;
    local_394 = local_394 + 0x4c;
    if (*(int *)(param_1 + 0x20) <= local_390) {
      return 0;
    }
  } while( true );
}


/* 00402fd0 size=30 */

void __thiscall
FUN_00402fd0(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)this = param_1;
  *(undefined4 *)((int)this + 4) = param_2;
  *(undefined4 *)((int)this + 8) = param_3;
  *(undefined4 *)((int)this + 0xc) = param_4;
  return;
}


/* 00403020 size=161 */

undefined1 * __cdecl FUN_00403020(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_100 [256];
  
  FUN_004b9f62(local_100,&DAT_004d56a0,&DAT_004d56a8);
  iVar2 = 0;
  if (0 < param_2) {
    puVar3 = param_3;
    do {
      iVar1 = FUN_004b7d10((byte *)*puVar3,param_1);
      if (iVar1 != 0) {
LAB_00403096:
        if (iVar2 < param_2 + -1) {
          return (undefined1 *)param_3[iVar2 + 1];
        }
        return &DAT_004e4424;
      }
      iVar1 = FUN_004b7d10((byte *)*puVar3,(int)local_100);
      if (iVar1 != 0) goto LAB_00403096;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar2 < param_2);
  }
  return (undefined1 *)0x0;
}


/* 004030d0 size=27 */

int __cdecl FUN_004030d0(int param_1)

{
  FUN_00403020(param_1,DAT_004ecc98,DAT_004ecc9c);
  return;
}


/* 00403f00 size=235 */

/* WARNING: Removing unreachable block (ram,0x00403fc7) */
/* WARNING: Removing unreachable block (ram,0x00403fd8) */
/* WARNING: Removing unreachable block (ram,0x00403f3f) */
/* WARNING: Removing unreachable block (ram,0x00403f50) */

WPARAM FUN_00403f00(undefined4 param_1)

{
  int iVar1;
  WPARAM WVar2;
  int local_8 [2];
  
  DAT_004e4d4c = timeGetTime();
  iVar1 = client_403b50((int)(local_8 + -1),'\0');
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  WVar2 = client_4030f0(param_1,local_8 + -1);
  if ((1 < (int)DAT_004e9864) && (DAT_004e4d50 = DAT_004e4d50 + 1, DAT_004e4d50 < DAT_004e9864)) {
    do {
      DAT_004e4d50 = DAT_004e4d50 + 1;
      WVar2 = client_4030f0(param_1,local_8 + -1);
    } while (DAT_004e4d50 < DAT_004e9864);
  }
  return WVar2;
}


/* 00403ff0 size=102 */

WPARAM FUN_00403ff0(undefined4 param_1)

{
  WPARAM WVar1;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004cb4e8;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  WVar1 = FUN_00403f00(param_1);
  ExceptionList = local_14;
  return WVar1;
}


