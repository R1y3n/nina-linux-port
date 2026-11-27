/* lithtech.exe decompilation - unnamed_00440000 */
#include "ghidra_types.h"

/* 00440100 size=51 */

undefined4 __thiscall FUN_00440100(void *this,int param_1,byte *param_2)

{
  uint uVar1;
  void *extraout_ECX;
  
  while( true ) {
    if (param_1 == 0) {
      return 0;
    }
    uVar1 = FUN_004c4c00(this,*(byte **)(param_1 + 4),param_2);
    if (uVar1 == 0) break;
    param_1 = *(int *)(param_1 + 0xc);
    this = extraout_ECX;
  }
  return 1;
}


/* 00440140 size=29 */

void __cdecl FUN_00440140(undefined *param_1)

{
  undefined *puVar1;
  
  while (param_1 != (undefined *)0x0) {
    puVar1 = *(undefined **)(param_1 + 0xc);
    FUN_00430fe0(param_1);
    param_1 = puVar1;
  }
  return;
}


/* 00440190 size=61 */

int __thiscall FUN_00440190(void *this,float *param_1,float param_2,float param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = *(float *)((int)this + 4);
  fVar2 = *(float *)this;
  fVar3 = *(float *)this;
  fVar4 = *(float *)((int)this + 8);
  *param_1 = param_3 * *(float *)((int)this + 8) - param_4 * *(float *)((int)this + 4);
  param_1[1] = param_4 * fVar3 - param_2 * fVar4;
  param_1[2] = param_2 * fVar1 - param_3 * fVar2;
  return;
}


/* 00440230 size=68 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00440230(void)

{
  _DAT_004e9ac4 = 0;
  _DAT_004e9ac8 = 0;
  _DAT_004e9acc = 0;
  _DAT_004e9adc = 1;
  _DAT_004e9ad0 = 0;
  _DAT_004e9ad4 = 0;
  _DAT_004e9ad8 = 0;
  _DAT_004e9ae0 = 0x3f800000;
  return;
}


/* 00440280 size=12 */

void FUN_00440280(void)

{
  FUN_004b9cf5(&LAB_00440290);
  return;
}


/* 004404b0 size=82 */

undefined4 * __thiscall FUN_004404b0(void *this,byte param_1)

{
  void *pvVar1;
  void *pvVar2;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  pvVar2 = DAT_004e9cb0;
  if (DAT_004e9cb0 == this) {
    DAT_004e9cb0 = *(void **)((int)this + 8);
  }
  else {
    do {
      pvVar1 = pvVar2;
      if (pvVar1 == (void *)0x0) goto LAB_004404ec;
      pvVar2 = *(void **)((int)pvVar1 + 8);
    } while (*(void **)((int)pvVar1 + 8) != this);
    *(undefined4 *)((int)pvVar1 + 8) = *(undefined4 *)((int)this + 8);
  }
LAB_004404ec:
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00440700 size=41 */

undefined4 FUN_00440700(int param_1)

{
  input_440730(param_1);
  FUN_00436670((byte *)s___Object__s__type___s__004d9a54,param_1 + 0x20);
  return 1;
}


/* 00440ad0 size=94 */

int __cdecl FUN_00440ad0(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_004e9cbc;
  while( true ) {
    iVar2 = DAT_004e9cbc;
    if (iVar1 == 0) {
      while( true ) {
        if (iVar2 == 0) {
          return 0;
        }
        if ((*(byte *)(iVar2 + 0x80) == param_1) && ((*(uint *)(iVar2 + 0x80) & 0x10000) != 0))
        break;
        iVar2 = *(int *)(iVar2 + 0x300);
      }
      return iVar2;
    }
    if ((*(byte *)(iVar1 + 0x80) == param_1) && ((*(uint *)(iVar1 + 0x80) & 0x10000) == 0)) break;
    iVar1 = *(int *)(iVar1 + 0x300);
  }
  return iVar1;
}


/* 00441500 size=784 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00441500: lifted from original x86 -> lt_lifted.c */


/* 00441810 size=111 */

void __cdecl FUN_00441810(undefined4 param_1,byte *param_2,int param_3)

{
  int *piVar1;
  
  if (param_3 < 0x100) {
    piVar1 = (int *)input_441880(param_2);
    if (piVar1 != (int *)0x0) {
      *piVar1 = param_3;
      return;
    }
    piVar1 = (int *)FUN_00430de0(0x2c);
    if (piVar1 == (int *)0x0) {
      piVar1 = (int *)0x0;
    }
    else {
      piVar1[10] = (int)piVar1;
      piVar1[9] = (int)piVar1;
    }
    piVar1[10] = (int)&DAT_004e9b30;
    piVar1[9] = (int)DAT_004e9b54;
    DAT_004e9b54 = piVar1;
    *(int **)(piVar1[9] + 0x28) = piVar1;
    _strncpy((char *)(piVar1 + 1),(char *)param_2,0x1e);
    *piVar1 = param_3;
  }
  return;
}


/* 004418c0 size=309 */

bool __thiscall FUN_004418c0(void *this,undefined4 param_1,byte *param_2,byte *param_3)

{
  int iVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  bool bVar7;
  int *piVar8;
  int *piVar9;
  
  piVar8 = (int *)input_440a10(this,param_2);
  if (piVar8 == (int *)0x0) {
    return false;
  }
  if (*piVar8 == 0) {
    return false;
  }
  piVar9 = (int *)input_441a00((int)piVar8,param_3);
  if (piVar9 == (int *)0x0) {
    return false;
  }
  *(int *)(*piVar9 + 4) = piVar9[1];
  *(int *)piVar9[1] = *piVar9;
  if (piVar9 == (int *)piVar8[0x23]) {
    piVar8[0x23] = ((int *)piVar8[0x23])[1];
  }
  iVar1 = piVar8[0x22];
  piVar8[0x22] = iVar1 + -1;
  if (iVar1 + -1 == 0) {
    piVar8[0x23] = 0;
  }
  puVar2 = (undefined *)piVar9[0x4e];
  do {
    do {
      puVar4 = puVar2;
      if (puVar4 == (undefined *)0x0) {
        FUN_00430df0((undefined *)piVar9);
        if (10 < DAT_004e4420) {
          FUN_00436670((byte *)s_Cleared_bindings_for__s__on__s__004d9b90,param_3);
        }
        bVar7 = FUN_00441500(piVar8);
        return bVar7;
      }
      puVar2 = *(undefined **)(puVar4 + 0x10);
    } while (puVar4 == (undefined *)0x0);
    if (*(undefined **)(puVar4 + 8) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)(puVar4 + 8));
    }
    puVar3 = *(undefined4 **)(puVar4 + 0x14);
    if (puVar3 != (undefined4 *)0x0) {
      *puVar3 = 0;
      puVar3[1] = 0;
      puVar6 = DAT_004e9cb0;
      if (DAT_004e9cb0 == puVar3) {
        DAT_004e9cb0 = (undefined4 *)puVar3[2];
      }
      else {
        do {
          puVar5 = puVar6;
          if (puVar5 == (undefined4 *)0x0) goto LAB_0044199d;
          puVar6 = (undefined4 *)puVar5[2];
        } while ((undefined4 *)puVar5[2] != puVar3);
        puVar5[2] = puVar3[2];
      }
LAB_0044199d:
      FUN_00430df0((undefined *)puVar3);
      *(undefined4 *)(puVar4 + 0x14) = 0;
    }
    FUN_00430df0(puVar4);
  } while( true );
}


/* 00443730 size=90 */

undefined4 __cdecl FUN_00443730(uint param_1,char *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  if (param_1 == 1) {
    uVar2 = 3;
  }
  else if ((param_1 & 2) == 0) {
    if ((param_1 & 4) == 0) {
      if ((param_1 & 8) == 0) {
        return 0;
      }
      uVar2 = 1;
    }
    else {
      uVar2 = 4;
    }
  }
  else {
    uVar2 = 2;
  }
  iVar1 = FUN_00440ad0(uVar2);
  if (iVar1 == 0) {
    return 0;
  }
  _strncpy(param_2,(char *)(iVar1 + 0xc),param_3 - 1);
  return 1;
}


/* 004437b0 size=192 */

undefined4 __thiscall FUN_004437b0(void *this,byte *param_1)

{
  undefined *puVar1;
  int *piVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined *puVar5;
  undefined4 local_4;
  
  local_4 = 0;
  if (param_1 == (byte *)0x0) {
    return 0;
  }
  piVar2 = (int *)input_440a10(this,param_1);
  if (piVar2 == (int *)0x0) {
    return 0;
  }
  if (*piVar2 == 0) {
    return 0;
  }
  param_1 = (byte *)&local_4;
  puVar4 = &LAB_004434e0;
  DAT_004e9cc4 = piVar2;
  iVar3 = (**(code **)(*(int *)*piVar2 + 0x10))((int *)*piVar2,&LAB_004434e0,&param_1,0);
  if (iVar3 != 0) {
    return 0;
  }
  DAT_004e9cc4 = (int *)0x0;
  if (puVar4 != (undefined1 *)0x0) {
    puVar5 = puVar4;
    do {
      FUN_00436670((byte *)s_Device____s_Control____s_Type_____004d9cd8,piVar2 + 3);
      puVar4 = *(undefined1 **)(puVar4 + 0xd0);
    } while (puVar4 != (undefined1 *)0x0);
    while (puVar5 != (undefined *)0x0) {
      puVar1 = *(undefined **)(puVar5 + 0xd0);
      FUN_00430df0(puVar5);
      puVar5 = puVar1;
    }
  }
  return 1;
}


/* 004438a0 size=13 */

undefined4 __cdecl FUN_004438a0(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004d9988;
  return 0;
}


/* 004438b0 size=100 */

bool __cdecl FUN_004438b0(int *param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *param_2;
  if (*param_2 <= *param_3) {
    iVar3 = *param_3;
  }
  *param_1 = iVar3;
  iVar2 = param_2[1];
  if (param_2[1] <= param_3[1]) {
    iVar2 = param_3[1];
  }
  param_1[1] = iVar2;
  iVar4 = param_2[2];
  if (param_3[2] <= param_2[2]) {
    iVar4 = param_3[2];
  }
  param_1[2] = iVar4;
  iVar1 = param_2[3];
  if (param_3[3] <= param_2[3]) {
    iVar1 = param_3[3];
  }
  param_1[3] = iVar1;
  if (iVar3 < iVar4) {
    return iVar2 < iVar1;
  }
  return false;
}


/* 00443920 size=439 */

bool __cdecl
FUN_00443920(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9,int param_10,int param_11,int param_12,int *param_13,
            int *param_14)

{
  longlong lVar1;
  
  if (param_3 < 0) {
    param_3 = 0;
  }
  if (param_1 < param_5) {
    param_5 = param_1;
  }
  if (param_4 < 0) {
    param_4 = 0;
  }
  if (param_2 < param_6) {
    param_6 = param_2;
  }
  if (param_5 < param_3) {
    return false;
  }
  if (param_6 < param_4) {
    return false;
  }
  if (param_9 < 0) {
    lVar1 = __ftol();
    param_3 = param_3 - (int)lVar1;
    param_9 = 0;
  }
  if (param_10 < 0) {
    lVar1 = __ftol();
    param_10 = 0;
    param_4 = param_4 - (int)lVar1;
  }
  if (0 < param_11 - param_7) {
    lVar1 = __ftol();
    param_5 = param_5 - (int)lVar1;
    param_11 = param_7;
  }
  if (0 < param_12 - param_8) {
    lVar1 = __ftol();
    param_6 = param_6 - (int)lVar1;
    param_12 = param_8;
  }
  if (param_1 < param_5) {
    param_5 = param_1;
  }
  if (param_2 < param_6) {
    param_6 = param_2;
  }
  if (param_5 <= param_3) {
    return false;
  }
  if (param_6 <= param_4) {
    return false;
  }
  if (param_7 <= param_9) {
    return false;
  }
  if (param_8 <= param_10) {
    return false;
  }
  *param_13 = param_3;
  param_13[1] = param_4;
  param_13[2] = param_5;
  param_13[3] = param_6;
  param_14[1] = param_10;
  *param_14 = param_9;
  param_14[2] = param_11;
  param_14[3] = param_12;
  if (param_11 < 0) {
    return false;
  }
  return -1 < param_12;
}


/* 00443ae0 size=239 */

bool __cdecl
FUN_00443ae0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9,int param_10,int *param_11,int *param_12)

{
  int iVar1;
  int iVar2;
  
  if (param_3 < 0) {
    param_9 = param_9 - param_3;
    param_3 = 0;
  }
  if (param_4 < 0) {
    param_10 = param_10 - param_4;
    param_4 = 0;
  }
  if (param_9 < 0) {
    param_3 = param_3 - param_9;
    param_9 = 0;
  }
  if (param_10 < 0) {
    param_4 = param_4 - param_10;
    param_10 = 0;
  }
  iVar1 = ((param_5 - param_3) - param_7) + param_9;
  if (0 < iVar1) {
    param_5 = param_5 - iVar1;
  }
  iVar1 = ((param_6 - param_4) - param_8) + param_10;
  if (0 < iVar1) {
    param_6 = param_6 - iVar1;
  }
  if (param_1 < param_5) {
    param_5 = param_1;
  }
  if (param_2 < param_6) {
    param_6 = param_2;
  }
  if (param_5 <= param_3) {
    return false;
  }
  if (param_6 <= param_4) {
    return false;
  }
  if (param_7 <= param_9) {
    return false;
  }
  if (param_8 <= param_10) {
    return false;
  }
  param_11[2] = param_5;
  param_11[3] = param_6;
  *param_11 = param_3;
  param_11[1] = param_4;
  iVar2 = (param_5 - param_3) + param_9;
  iVar1 = (param_6 - param_4) + param_10;
  *param_12 = param_9;
  param_12[1] = param_10;
  param_12[2] = iVar2;
  param_12[3] = iVar1;
  if (iVar2 < 0) {
    return false;
  }
  return -1 < iVar1;
}


/* 00443bd0 size=340 */

void __cdecl
FUN_00443bd0(int param_1,int param_2,undefined4 param_3,int param_4,uint *param_5,uint *param_6)

{
  undefined2 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined2 *puVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  int local_10;
  
  *param_5 = 5000;
  *param_6 = 0;
  if (0 < param_4) {
    local_10 = param_4;
    do {
      lVar8 = __ftol();
      uVar2 = (uint)lVar8;
      lVar8 = __ftol();
      uVar3 = (uint)lVar8;
      if (uVar2 < uVar3) {
        uVar5 = uVar2;
        uVar2 = uVar3;
        iVar6 = param_2;
      }
      else {
        uVar5 = uVar3;
        iVar6 = param_1;
      }
      puVar7 = (undefined2 *)(iVar6 + uVar5 * 0xc);
      if (uVar5 < *param_5) {
        *param_5 = uVar5;
      }
      if (*param_6 < uVar2) {
        *param_6 = uVar2;
      }
      if (uVar2 - uVar5 != 0) {
        lVar8 = __ftol();
        iVar6 = (int)lVar8;
        lVar8 = __ftol();
        iVar4 = (int)lVar8;
        lVar8 = __ftol();
        lVar9 = __ftol();
        puVar1 = puVar7 + (uVar2 - uVar5) * 6;
        for (; puVar7 < puVar1; puVar7 = puVar7 + 6) {
          lVar10 = __ftol();
          *puVar7 = (short)lVar10;
          *(int *)(puVar7 + 2) = iVar6;
          *(int *)(puVar7 + 4) = iVar4;
          iVar6 = iVar6 + (int)lVar8;
          iVar4 = iVar4 + (int)lVar9;
        }
      }
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  return;
}


/* 00443d30 size=1130 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __cdecl
FUN_00443d30(int *param_1,int *param_2,float param_3,float param_4,float param_5,undefined4 param_6)

{
  float fVar1;
  uint uVar2;
  float *pfVar3;
  float *pfVar4;
  uint *puVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  int local_dc;
  float *local_d0;
  uint local_c8 [50];
  
  DAT_004ea450 = param_3;
  _DAT_004e9cc8 = param_4;
  iVar9 = 0;
  _DAT_004ea454 = param_5;
  DAT_004ea45c = param_6;
  DAT_004ea458 = 0;
  iVar7 = *param_2;
  if (0 < iVar7) {
    puVar5 = local_c8;
    pfVar6 = (float *)(*param_1 + 8);
    do {
      fVar1 = *pfVar6;
      *puVar5 = (uint)(param_3 <= fVar1);
      iVar9 = iVar9 + (uint)(param_3 <= fVar1);
      pfVar6 = pfVar6 + 4;
      puVar5 = puVar5 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    if (iVar9 != 0) {
      if (iVar9 != *param_2) {
        DAT_004ea458 = 1;
        pfVar6 = (float *)&DAT_004e9cd0;
        iVar7 = *param_2 + -1;
        if (0 < *param_2) {
          local_dc = 0;
          pfVar3 = (float *)(iVar7 * 0x10 + *param_1);
          iVar9 = 0;
          do {
            iVar8 = iVar9;
            uVar2 = local_c8[iVar7];
            pfVar4 = (float *)(*param_1 + local_dc);
            pfVar10 = pfVar6;
            if (uVar2 != 0) {
              pfVar10 = pfVar6 + 4;
              *pfVar6 = *pfVar3;
              pfVar6[1] = pfVar3[1];
              pfVar6[2] = pfVar3[2];
              pfVar6[3] = pfVar3[3];
            }
            pfVar6 = pfVar10;
            if (uVar2 != local_c8[iVar8]) {
              fVar1 = (DAT_004ea450 - pfVar3[2]) / (pfVar4[2] - pfVar3[2]);
              pfVar10[2] = DAT_004ea450;
              pfVar6 = pfVar10 + 4;
              pfVar10[3] = (pfVar4[3] - pfVar3[3]) * fVar1 + pfVar3[3];
              *pfVar10 = (*pfVar4 - *pfVar3) * fVar1 + *pfVar3;
              pfVar10[1] = (pfVar4[1] - pfVar3[1]) * fVar1 + pfVar3[1];
            }
            local_dc = local_dc + 0x10;
            pfVar3 = pfVar4;
            iVar9 = iVar8 + 1;
            iVar7 = iVar8;
          } while (iVar8 + 1 < *param_2);
        }
        *param_2 = (int)(pfVar6 + -0x13a734) >> 4;
        *param_1 = (int)&DAT_004e9cd0;
      }
      iVar9 = 0;
      iVar7 = *param_2;
      if (0 < iVar7) {
        puVar5 = local_c8;
        pfVar6 = (float *)(*param_1 + 0xc);
        do {
          fVar1 = *pfVar6;
          *puVar5 = (uint)(_DAT_004e9cc8 <= fVar1);
          iVar9 = iVar9 + (uint)(_DAT_004e9cc8 <= fVar1);
          pfVar6 = pfVar6 + 4;
          puVar5 = puVar5 + 1;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
        if (iVar9 != 0) {
          if (iVar9 != *param_2) {
            local_d0 = (float *)(&DAT_004e9cd0 + DAT_004ea458 * 0xf0);
            DAT_004ea458 = (uint)(DAT_004ea458 == 0);
            iVar7 = *param_2 + -1;
            pfVar6 = local_d0;
            if (0 < *param_2) {
              local_dc = 0;
              pfVar3 = (float *)(iVar7 * 0x10 + *param_1);
              iVar9 = 0;
              do {
                iVar8 = iVar9;
                uVar2 = local_c8[iVar7];
                pfVar10 = (float *)(local_dc + *param_1);
                if (uVar2 != 0) {
                  *pfVar6 = *pfVar3;
                  pfVar6[1] = pfVar3[1];
                  pfVar6[2] = pfVar3[2];
                  pfVar6[3] = pfVar3[3];
                  pfVar6 = pfVar6 + 4;
                }
                if (uVar2 != local_c8[iVar8]) {
                  FUN_00444200(pfVar3,pfVar10,pfVar6);
                  pfVar6 = pfVar6 + 4;
                }
                local_dc = local_dc + 0x10;
                pfVar3 = pfVar10;
                iVar9 = iVar8 + 1;
                iVar7 = iVar8;
              } while (iVar8 + 1 < *param_2);
            }
            *param_2 = (int)pfVar6 - (int)local_d0 >> 4;
            *param_1 = (int)local_d0;
          }
          iVar9 = 0;
          iVar7 = *param_2;
          if (0 < iVar7) {
            puVar5 = local_c8;
            pfVar6 = (float *)(*param_1 + 8);
            do {
              fVar1 = *pfVar6;
              *puVar5 = (uint)(fVar1 < _DAT_004ea454);
              iVar9 = iVar9 + (uint)(fVar1 < _DAT_004ea454);
              pfVar6 = pfVar6 + 4;
              puVar5 = puVar5 + 1;
              iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
            if (iVar9 != 0) {
              if (iVar9 != *param_2) {
                pfVar3 = (float *)(&DAT_004e9cd0 + DAT_004ea458 * 0xf0);
                DAT_004ea458 = (uint)(DAT_004ea458 == 0);
                iVar7 = *param_2 + -1;
                pfVar6 = pfVar3;
                if (0 < *param_2) {
                  local_dc = 0;
                  pfVar10 = (float *)(iVar7 * 0x10 + *param_1);
                  iVar9 = 0;
                  do {
                    iVar8 = iVar9;
                    local_d0 = (float *)local_c8[iVar7];
                    pfVar4 = (float *)(local_dc + *param_1);
                    if (local_d0 != (float *)0x0) {
                      *pfVar6 = *pfVar10;
                      pfVar6[1] = pfVar10[1];
                      pfVar6[2] = pfVar10[2];
                      pfVar6[3] = pfVar10[3];
                      pfVar6 = pfVar6 + 4;
                    }
                    if (local_d0 != (float *)local_c8[iVar8]) {
                      FUN_004441a0(pfVar10,pfVar4,pfVar6);
                      pfVar6 = pfVar6 + 4;
                    }
                    local_dc = local_dc + 0x10;
                    pfVar10 = pfVar4;
                    iVar9 = iVar8 + 1;
                    iVar7 = iVar8;
                  } while (iVar8 + 1 < *param_2);
                }
                *param_2 = (int)pfVar6 - (int)pfVar3 >> 4;
                *param_1 = (int)pfVar3;
              }
              iVar7 = FUN_00444ab0(local_d0,local_d0,param_1,param_2);
              return iVar7 != 0;
            }
          }
        }
      }
    }
  }
  return false;
}


