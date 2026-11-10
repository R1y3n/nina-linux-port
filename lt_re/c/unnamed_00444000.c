/* lithtech.exe decompilation - unnamed_00444000 */
#include "ghidra_types.h"

/* 004441a0 size=81 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004441a0(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  
  fVar1 = (_DAT_004ea454 - param_1[2]) / (param_2[2] - param_1[2]);
  param_3[2] = _DAT_004ea454;
  param_3[3] = (param_2[3] - param_1[3]) * fVar1 + param_1[3];
  *param_3 = (*param_2 - *param_1) * fVar1 + *param_1;
  param_3[1] = (param_2[1] - param_1[1]) * fVar1 + param_1[1];
  return;
}


/* 00444200 size=81 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00444200(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  
  fVar1 = (_DAT_004e9cc8 - param_1[3]) / (param_2[3] - param_1[3]);
  param_3[3] = _DAT_004e9cc8;
  param_3[2] = (param_2[2] - param_1[2]) * fVar1 + param_1[2];
  *param_3 = (*param_2 - *param_1) * fVar1 + *param_1;
  param_3[1] = (param_2[1] - param_1[1]) * fVar1 + param_1[1];
  return;
}


/* 004444f0 size=131 */

uint __cdecl FUN_004444f0(undefined *param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_004e5124 == 0) {
    return 0;
  }
  *param_2 = 0;
  if (param_1 == &DAT_004e4fa0) {
    iVar1 = (**(code **)(DAT_004e5124 + 0xec))(0,0,DAT_004e4fb0,DAT_004e4fb4,&param_2,param_2);
    return -(uint)(iVar1 != 0) & (uint)param_2;
  }
  *param_2 = *(undefined4 *)(param_1 + 0x18);
  uVar2 = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_1 + 0xc));
  if (((param_3 != 0) && (uVar2 != 0)) && (param_1 != (undefined *)0x0)) {
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 4;
  }
  return uVar2;
}


/* 00444800 size=40 */

void __cdecl FUN_00444800(undefined *param_1)

{
  if (param_1 == &DAT_004e4fa0) {
                    /* WARNING: Could not recover jumptable at 0x00444810. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(DAT_004e5124 + 0xf0))();
    return;
  }
  (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_1 + 0xc));
  return;
}


/* 00444ab0 size=401 */

undefined4 __cdecl FUN_00444ab0(undefined4 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  float fVar1;
  uint uVar2;
  float *pfVar3;
  uint *puVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int local_d4;
  uint local_c8 [50];
  
  iVar9 = *param_4;
  iVar11 = 0;
  if (0 < iVar9) {
    puVar4 = local_c8;
    pfVar7 = (float *)(*param_3 + 0xc);
    do {
      fVar1 = *pfVar7;
      *puVar4 = (uint)(fVar1 < DAT_004ea45c);
      iVar11 = iVar11 + (uint)(fVar1 < DAT_004ea45c);
      pfVar7 = pfVar7 + 4;
      puVar4 = puVar4 + 1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    if (iVar11 != 0) {
      if (iVar11 != *param_4) {
        pfVar5 = (float *)(&DAT_004e9cd0 + DAT_004ea458 * 0xf0);
        DAT_004ea458 = (uint)(DAT_004ea458 == 0);
        iVar9 = *param_4 + -1;
        pfVar7 = pfVar5;
        if (0 < *param_4) {
          local_d4 = 0;
          pfVar3 = (float *)(iVar9 * 0x10 + *param_3);
          iVar11 = 0;
          do {
            iVar10 = iVar11;
            uVar2 = local_c8[iVar9];
            pfVar8 = (float *)(local_d4 + *param_3);
            pfVar6 = pfVar7;
            if (uVar2 != 0) {
              pfVar6 = pfVar7 + 4;
              *pfVar7 = *pfVar3;
              pfVar7[1] = pfVar3[1];
              pfVar7[2] = pfVar3[2];
              pfVar7[3] = pfVar3[3];
            }
            pfVar7 = pfVar6;
            if (uVar2 != local_c8[iVar10]) {
              fVar1 = (DAT_004ea45c - pfVar3[3]) / (pfVar8[3] - pfVar3[3]);
              pfVar6[3] = DAT_004ea45c;
              pfVar7 = pfVar6 + 4;
              pfVar6[2] = (pfVar8[2] - pfVar3[2]) * fVar1 + pfVar3[2];
              *pfVar6 = (*pfVar8 - *pfVar3) * fVar1 + *pfVar3;
              pfVar6[1] = (pfVar8[1] - pfVar3[1]) * fVar1 + pfVar3[1];
            }
            local_d4 = local_d4 + 0x10;
            pfVar3 = pfVar8;
            iVar11 = iVar10 + 1;
            iVar9 = iVar10;
          } while (iVar10 + 1 < *param_4);
        }
        *param_4 = (int)pfVar7 - (int)pfVar5 >> 4;
        *param_3 = (int)pfVar5;
      }
      return 1;
    }
  }
  return 0;
}


/* 00444c50 size=655 */

undefined4 __cdecl
FUN_00444c50(undefined *param_1,undefined *param_2,short *param_3,int param_4,short *param_5,
            uint param_6)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  int iVar9;
  uint local_20;
  int iStack_1c;
  int local_18;
  short *psStack_14;
  int iStack_10;
  int local_c;
  int iStack_8;
  uint uStack_4;
  
  local_c = 1;
  if (DAT_004e5124 == 0) goto LAB_00444e9a;
  local_20 = 0;
  if (param_2 == &DAT_004e4fa0) {
    iVar2 = (**(code **)(DAT_004e5124 + 0xec))(0,0,DAT_004e4fb0,DAT_004e4fb4,&local_18,&local_20);
    if (iVar2 == 0) goto LAB_00444e9a;
  }
  else {
    local_20 = *(uint *)(param_2 + 0x18);
    local_18 = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_2 + 0xc));
  }
  if (local_18 == 0) goto LAB_00444e9a;
  if (DAT_004e5124 != 0) {
    iStack_1c = 0;
    if (param_1 == &DAT_004e4fa0) {
      iVar2 = (**(code **)(DAT_004e5124 + 0xec))(0,0,DAT_004e4fb0,DAT_004e4fb4,&iStack_8,&iStack_1c)
      ;
      if (iVar2 == 0) goto LAB_00444e74;
    }
    else {
      iStack_1c = *(int *)(param_1 + 0x18);
      iStack_8 = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_1 + 0xc));
      if ((iStack_8 != 0) && (param_1 != (undefined *)0x0)) {
        *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 4;
      }
    }
    iStack_10 = iStack_8;
    if (iStack_8 != 0) {
      uStack_4 = local_20 / DAT_004e5114;
      local_c = 0;
      psStack_14 = param_5;
      psVar5 = param_3 + (int)param_5 * 6;
      if (param_5 < param_6) {
        param_3 = (short *)((int)psVar5 + (param_4 - (int)param_3));
        param_5 = psVar5;
        do {
          if (*param_3 != *param_5) {
            iVar2 = (int)*param_3 - (int)*param_5;
            if (iVar2 < 1) {
              iVar2 = -iVar2;
              psVar5 = param_3;
              psVar8 = param_5;
            }
            else {
              psVar5 = param_5;
              psVar8 = param_3;
            }
            iVar9 = *(int *)(psVar5 + 2);
            iVar7 = *(int *)(psVar5 + 4);
            iVar3 = (*(int *)(psVar8 + 2) - iVar9) / iVar2;
            iVar4 = (*(int *)(psVar8 + 4) - iVar7) / iVar2;
            puVar1 = (undefined4 *)
                     ((int)psStack_14 * iStack_1c + iStack_8 + (int)*psVar5 * DAT_004e5114);
            for (; iVar2 != 0; iVar2 = iVar2 + -1) {
              iVar6 = iVar7 >> 0x10;
              iVar7 = iVar7 + iVar4;
              *puVar1 = *(undefined4 *)(local_18 + (iVar6 * uStack_4 + (iVar9 >> 0x10)) * 4);
              iVar9 = iVar9 + iVar3;
              puVar1 = puVar1 + 1;
            }
          }
          param_5 = param_5 + 6;
          param_3 = param_3 + 6;
          psStack_14 = (short *)((int)psStack_14 + 1);
        } while (psStack_14 < param_6);
      }
      if (param_1 == &DAT_004e4fa0) {
        (**(code **)(DAT_004e5124 + 0xf0))();
      }
      else {
        (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_1 + 0xc));
      }
    }
  }
LAB_00444e74:
  if (param_2 == &DAT_004e4fa0) {
    (**(code **)(DAT_004e5124 + 0xf0))();
  }
  else {
    (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_2 + 0xc));
  }
  if (local_c == 0) {
    return 0;
  }
LAB_00444e9a:
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_cis_DrawWarp_004d9d08);
  }
  return 1;
}


/* 00444ee0 size=664 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_00444ee0(undefined *param_1,undefined *param_2,short *param_3,short *param_4,uint param_5,
            uint param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  int *piVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  uint local_20;
  int iStack_1c;
  int local_18;
  int iStack_14;
  int local_10;
  int iStack_c;
  uint uStack_8;
  int iStack_4;
  
  local_10 = 1;
  if (DAT_004e5124 == 0) goto LAB_00445133;
  local_20 = 0;
  if (param_2 == &DAT_004e4fa0) {
    iVar2 = (**(code **)(DAT_004e5124 + 0xec))(0,0,DAT_004e4fb0,DAT_004e4fb4,&local_18,&local_20);
    if (iVar2 == 0) goto LAB_00445133;
  }
  else {
    local_20 = *(uint *)(param_2 + 0x18);
    local_18 = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_2 + 0xc));
  }
  if (local_18 == 0) goto LAB_00445133;
  if (DAT_004e5124 != 0) {
    iStack_1c = 0;
    if (param_1 == &DAT_004e4fa0) {
      iVar2 = (**(code **)(DAT_004e5124 + 0xec))(0,0,DAT_004e4fb0,DAT_004e4fb4,&iStack_c,&iStack_1c)
      ;
      if (iVar2 == 0) goto LAB_0044510d;
    }
    else {
      iStack_1c = *(int *)(param_1 + 0x18);
      iStack_c = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_1 + 0xc));
      if ((iStack_c != 0) && (param_1 != (undefined *)0x0)) {
        *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 4;
      }
    }
    iStack_14 = iStack_c;
    if (iStack_c != 0) {
      uStack_8 = local_20 / DAT_004e5114;
      local_10 = 0;
      if (param_5 < param_6) {
        param_4 = (short *)(((int)(param_3 + param_5 * 6) - (int)param_3) + (int)param_4);
        param_3 = param_3 + param_5 * 6;
        do {
          if (*param_4 != *param_3) {
            iVar2 = (int)*param_4 - (int)*param_3;
            if (iVar2 < 1) {
              iVar2 = -iVar2;
              psVar4 = param_4;
              psVar7 = param_3;
            }
            else {
              psVar4 = param_3;
              psVar7 = param_4;
            }
            iVar8 = *(int *)(psVar4 + 2);
            iVar6 = *(int *)(psVar4 + 4);
            iStack_4 = (*(int *)(psVar7 + 2) - iVar8) / iVar2;
            iVar3 = (*(int *)(psVar7 + 4) - iVar6) / iVar2;
            piVar5 = (int *)(param_5 * iStack_1c + iStack_c + (int)*psVar4 * DAT_004e5114);
            for (; iVar2 != 0; iVar2 = iVar2 + -1) {
              iVar1 = *(int *)(local_18 + ((iVar6 >> 0x10) * uStack_8 + (iVar8 >> 0x10)) * 4);
              if (iVar1 != _DAT_004e4f9c) {
                *piVar5 = iVar1;
              }
              piVar5 = piVar5 + 1;
              iVar8 = iVar8 + iStack_4;
              iVar6 = iVar6 + iVar3;
            }
          }
          param_3 = param_3 + 6;
          param_4 = param_4 + 6;
          param_5 = param_5 + 1;
        } while (param_5 < param_6);
      }
      if (param_1 == &DAT_004e4fa0) {
        (**(code **)(DAT_004e5124 + 0xf0))();
      }
      else {
        (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_1 + 0xc));
      }
    }
  }
LAB_0044510d:
  if (param_2 == &DAT_004e4fa0) {
    (**(code **)(DAT_004e5124 + 0xf0))();
  }
  else {
    (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_2 + 0xc));
  }
  if (local_10 == 0) {
    return 0;
  }
LAB_00445133:
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_cis_DrawWarp_004d9d08);
  }
  return 1;
}


/* 00445180 size=670 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_00445180(undefined *param_1,undefined *param_2,short *param_3,short *param_4,uint param_5,
            uint param_6)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  undefined4 *puVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  uint local_20;
  int iStack_1c;
  int local_18;
  int iStack_14;
  int local_10;
  int iStack_c;
  uint uStack_8;
  int iStack_4;
  
  local_10 = 1;
  if (DAT_004e5124 == 0) goto LAB_004453d9;
  local_20 = 0;
  if (param_2 == &DAT_004e4fa0) {
    iVar1 = (**(code **)(DAT_004e5124 + 0xec))(0,0,DAT_004e4fb0,DAT_004e4fb4,&local_18,&local_20);
    if (iVar1 == 0) goto LAB_004453d9;
  }
  else {
    local_20 = *(uint *)(param_2 + 0x18);
    local_18 = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_2 + 0xc));
  }
  if (local_18 == 0) goto LAB_004453d9;
  if (DAT_004e5124 != 0) {
    iStack_1c = 0;
    if (param_1 == &DAT_004e4fa0) {
      iVar1 = (**(code **)(DAT_004e5124 + 0xec))(0,0,DAT_004e4fb0,DAT_004e4fb4,&iStack_c,&iStack_1c)
      ;
      if (iVar1 == 0) goto LAB_004453b3;
    }
    else {
      iStack_1c = *(int *)(param_1 + 0x18);
      iStack_c = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_1 + 0xc));
      if ((iStack_c != 0) && (param_1 != (undefined *)0x0)) {
        *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 4;
      }
    }
    iStack_14 = iStack_c;
    if (iStack_c != 0) {
      uStack_8 = local_20 / DAT_004e5114;
      local_10 = 0;
      if (param_5 < param_6) {
        param_4 = (short *)(((int)(param_3 + param_5 * 6) - (int)param_3) + (int)param_4);
        param_3 = param_3 + param_5 * 6;
        do {
          if (*param_4 != *param_3) {
            iVar1 = (int)*param_4 - (int)*param_3;
            if (iVar1 < 1) {
              iVar1 = -iVar1;
              psVar3 = param_4;
              psVar6 = param_3;
            }
            else {
              psVar3 = param_3;
              psVar6 = param_4;
            }
            iVar7 = *(int *)(psVar3 + 2);
            iVar5 = *(int *)(psVar3 + 4);
            iStack_4 = (*(int *)(psVar6 + 2) - iVar7) / iVar1;
            iVar2 = (*(int *)(psVar6 + 4) - iVar5) / iVar1;
            puVar4 = (undefined4 *)(param_5 * iStack_1c + iStack_c + (int)*psVar3 * DAT_004e5114);
            for (; iVar1 != 0; iVar1 = iVar1 + -1) {
              if (*(int *)(local_18 + ((iVar5 >> 0x10) * uStack_8 + (iVar7 >> 0x10)) * 4) !=
                  _DAT_004e4f9c) {
                *puVar4 = DAT_004e50d0;
              }
              puVar4 = puVar4 + 1;
              iVar7 = iVar7 + iStack_4;
              iVar5 = iVar5 + iVar2;
            }
          }
          param_3 = param_3 + 6;
          param_4 = param_4 + 6;
          param_5 = param_5 + 1;
        } while (param_5 < param_6);
      }
      if (param_1 == &DAT_004e4fa0) {
        (**(code **)(DAT_004e5124 + 0xf0))();
      }
      else {
        (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_1 + 0xc));
      }
    }
  }
LAB_004453b3:
  if (param_2 == &DAT_004e4fa0) {
    (**(code **)(DAT_004e5124 + 0xf0))();
  }
  else {
    (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_2 + 0xc));
  }
  if (local_10 == 0) {
    return 0;
  }
LAB_004453d9:
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_cis_DrawWarp_004d9d08);
  }
  return 1;
}


/* 00445430 size=41 */

void __fastcall FUN_00445430(undefined4 param_1)

{
  undefined1 local_1;
  
  local_1 = (undefined1)((uint)param_1 >> 0x18);
  DAT_004ea460 = local_1;
  DAT_004ea464 = FUN_00430de0(0x14);
  *(int *)DAT_004ea464 = DAT_004ea464;
  *(int *)(DAT_004ea464 + 4) = DAT_004ea464;
  DAT_004ea468 = 0;
  return;
}


/* 00445460 size=12 */

void FUN_00445460(void)

{
  FUN_004b9cf5(&LAB_00445470);
  return;
}


/* 004454d0 size=135 */

int * __cdecl FUN_004454d0(int param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  
  piVar1 = DAT_004ea464;
  piVar2 = (int *)*DAT_004ea464;
  if (piVar2 != DAT_004ea464) {
    do {
      if (piVar2[3] == param_1) break;
      piVar2 = (int *)*piVar2;
    } while (piVar2 != DAT_004ea464);
    if (piVar2 != DAT_004ea464) {
      return piVar2 + 2;
    }
  }
  piVar2 = (int *)DAT_004ea464[1];
  piVar3 = (int *)FUN_00430de0(0x14);
  piVar4 = piVar1;
  if (piVar1 == (int *)0x0) {
    piVar4 = piVar3;
  }
  *piVar3 = (int)piVar4;
  if (piVar2 == (int *)0x0) {
    piVar2 = piVar3;
  }
  piVar3[1] = (int)piVar2;
  piVar1[1] = (int)piVar3;
  *(int **)piVar3[1] = piVar3;
  if (piVar3 + 2 != (int *)0x0) {
    piVar3[2] = 0;
    piVar3[3] = param_1;
    piVar3[4] = 0;
  }
  DAT_004ea468 = DAT_004ea468 + 1;
  return (int *)(DAT_004ea464[1] + 8);
}


/* 00445560 size=85 */

void __cdecl FUN_00445560(int *param_1)

{
  int *piVar1;
  
  for (piVar1 = (int *)*DAT_004ea464; (piVar1 != DAT_004ea464 && (piVar1 + 2 != param_1));
      piVar1 = (int *)*piVar1) {
  }
  if (((piVar1 != DAT_004ea464) && (piVar1[2] < 1)) && (piVar1[3] == 0)) {
    *(int *)piVar1[1] = *piVar1;
    *(int *)(*piVar1 + 4) = piVar1[1];
    FUN_00430df0((undefined *)piVar1);
    DAT_004ea468 = DAT_004ea468 + -1;
  }
  return;
}


/* 004455c0 size=240 */

void __cdecl FUN_004455c0(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  
  iVar1 = *(int *)(param_2 + 400);
  iVar2 = *(int *)(iVar1 + 4);
  do {
    do {
      if (iVar2 == iVar1) {
        return;
      }
      piVar3 = *(int **)(iVar2 + 8);
      iVar2 = *(int *)(iVar2 + 4);
      iVar4 = *piVar3;
    } while ((((iVar4 != 0) && (iVar4 != 2)) || (piVar3[1] != param_2)) || (piVar3[2] != param_3));
    if (iVar4 == 2) {
      *(undefined4 *)(piVar3[2] + 0x38) = 0;
    }
    else {
      piVar5 = (int *)piVar3[4];
      *(int *)(*piVar5 + 4) = piVar5[1];
      *(int *)piVar5[1] = *piVar5;
      piVar5[1] = (int)piVar5;
      *piVar5 = (int)piVar5;
      piVar5 = (int *)piVar3[4];
      if (piVar5 != (int *)0x0) {
        *piVar5 = (int)DAT_004e514c;
        DAT_004e514c = piVar5;
      }
    }
    piVar5 = (int *)piVar3[3];
    *(int *)(*piVar5 + 4) = piVar5[1];
    *(int *)piVar5[1] = *piVar5;
    piVar5[1] = (int)piVar5;
    *piVar5 = (int)piVar5;
    piVar5 = (int *)piVar3[3];
    if (piVar5 != (int *)0x0) {
      *piVar5 = (int)DAT_004e514c;
      DAT_004e514c = piVar5;
    }
    if ((piVar3 != (int *)0x0) && (param_1 != -0xa58)) {
      *piVar3 = *(int *)(param_1 + 0xa70);
      *(int **)(param_1 + 0xa70) = piVar3;
    }
  } while (param_4 != 0);
  return;
}


/* 004456b0 size=288 */

void __cdecl FUN_004456b0(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  
  iVar1 = *(int *)(param_2 + 400);
  iVar2 = *(int *)(iVar1 + 4);
  while (iVar2 != iVar1) {
    piVar3 = *(int **)(iVar2 + 8);
    iVar2 = *(int *)(iVar2 + 4);
    iVar4 = *piVar3;
    if (iVar4 == param_3) {
      if (iVar4 == 2) {
        iVar4 = piVar3[2];
        if ((*(byte *)(iVar4 + 0x34) & 0x10) == 0) {
          *(undefined4 *)(iVar4 + 0x20) = 0;
          *(undefined4 *)(iVar4 + 0x10) = 1;
        }
        *(undefined4 *)(iVar4 + 0x38) = 0;
      }
      else if (iVar4 == 3) {
        piVar5 = (int *)piVar3[2];
        if (piVar5 != (int *)0x0) {
          piVar5[1] = 0;
          FUN_00445560(piVar5);
        }
      }
      else {
        if ((param_4 != 0) &&
           (piVar5 = *(int **)(*(int *)(piVar3[1] + 400) + 0x20), piVar5 != (int *)0x0)) {
          (**(code **)(*piVar5 + 4))(4,piVar3[2],0);
        }
        piVar5 = (int *)piVar3[4];
        *(int *)(*piVar5 + 4) = piVar5[1];
        *(int *)piVar5[1] = *piVar5;
        piVar5[1] = (int)piVar5;
        *piVar5 = (int)piVar5;
        piVar5 = (int *)piVar3[4];
        if (piVar5 != (int *)0x0) {
          *piVar5 = (int)DAT_004e514c;
          DAT_004e514c = piVar5;
        }
      }
      piVar5 = (int *)piVar3[3];
      *(int *)(*piVar5 + 4) = piVar5[1];
      *(int *)piVar5[1] = *piVar5;
      piVar5[1] = (int)piVar5;
      *piVar5 = (int)piVar5;
      piVar5 = (int *)piVar3[3];
      if (piVar5 != (int *)0x0) {
        *piVar5 = (int)DAT_004e514c;
        DAT_004e514c = piVar5;
      }
      if ((piVar3 != (int *)0x0) && (param_1 != -0xa58)) {
        *piVar3 = *(int *)(param_1 + 0xa70);
        *(int **)(param_1 + 0xa70) = piVar3;
      }
    }
  }
  return;
}


/* 004457d0 size=294 */

undefined4 __cdecl FUN_004457d0(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  if (((param_4 == 3) || (param_4 == 1)) &&
     (iVar2 = FUN_00445900(param_2,param_3,param_4), iVar2 != 0)) {
    return 0;
  }
  if (param_2 == param_3) {
    return 1;
  }
  piVar4 = *(int **)(param_1 + 0xa70);
  if (piVar4 == (int *)0x0) {
    FUN_004b7c60(param_1 + 0xa58,*(int *)(param_1 + 0xa60));
    piVar4 = *(int **)(param_1 + 0xa70);
    if (piVar4 == (int *)0x0) goto LAB_00445839;
  }
  *(int *)(param_1 + 0xa70) = *piVar4;
LAB_00445839:
  *piVar4 = param_4;
  piVar4[1] = param_2;
  piVar4[2] = param_3;
  if ((DAT_004e514c != (int *)0x0) ||
     (FUN_004b7c60(0x4e5134,DAT_004e513c), piVar3 = DAT_004e514c, DAT_004e514c != (int *)0x0)) {
    piVar3 = DAT_004e514c;
    DAT_004e514c = (int *)*DAT_004e514c;
  }
  piVar3[2] = (int)piVar4;
  piVar4[3] = (int)piVar3;
  iVar2 = *(int *)(param_2 + 400);
  *piVar3 = iVar2;
  puVar1 = *(undefined4 **)(iVar2 + 4);
  piVar3[1] = (int)puVar1;
  *puVar1 = piVar3;
  *(int **)(*piVar3 + 4) = piVar3;
  if (param_4 == 2) {
    *(int **)(param_3 + 0x38) = piVar4;
    return 0;
  }
  if ((param_4 != 0) && (param_4 != 1)) {
    return 0;
  }
  if ((DAT_004e514c != (int *)0x0) ||
     (FUN_004b7c60(0x4e5134,DAT_004e513c), piVar3 = DAT_004e514c, DAT_004e514c != (int *)0x0)) {
    piVar3 = DAT_004e514c;
    DAT_004e514c = (int *)*DAT_004e514c;
  }
  piVar3[2] = (int)piVar4;
  piVar4[4] = (int)piVar3;
  iVar2 = *(int *)(param_3 + 400);
  *piVar3 = iVar2;
  puVar1 = *(undefined4 **)(iVar2 + 4);
  piVar3[1] = (int)puVar1;
  *puVar1 = piVar3;
  *(int **)(*piVar3 + 4) = piVar3;
  return 0;
}


/* 00445900 size=67 */

undefined4 __cdecl FUN_00445900(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)(*(int *)(param_1 + 400) + 4);
  while( true ) {
    if (iVar1 == *(int *)(param_1 + 400)) {
      return 0;
    }
    piVar2 = *(int **)(iVar1 + 8);
    if (((*piVar2 == param_3) && (piVar2[1] == param_1)) && (piVar2[2] == param_2)) break;
    iVar1 = *(int *)(iVar1 + 4);
  }
  return 1;
}


/* 00445980 size=1119 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_00445980(int *param_1,int param_2,float *param_3,float *param_4)

{
  int *piVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  undefined4 uVar11;
  float *pfVar12;
  int iVar13;
  float10 fVar14;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_58 = *param_3;
  local_54 = param_3[1];
  local_50 = param_3[2];
  if ((*(byte *)((int)param_1 + 0x16) & 3) != 0) {
    return 0;
  }
  do {
    iVar13 = *param_1;
    if ((iVar13 == 0) || (*(int *)(iVar13 + 0x2c) == 0)) {
      pfVar12 = (float *)0x0;
    }
    else {
      pfVar12 = *(float **)(iVar13 + 0x28);
    }
    fVar4 = (local_58 * *pfVar12 + local_54 * pfVar12[1] + local_50 * pfVar12[2]) - pfVar12[3];
    if ((iVar13 == 0) || (*(int *)(iVar13 + 0x2c) == 0)) {
      pfVar12 = (float *)0x0;
    }
    else {
      pfVar12 = *(float **)(iVar13 + 0x28);
    }
    local_40 = *param_4;
    local_3c = param_4[1];
    local_38 = param_4[2];
    fVar5 = (local_40 * *pfVar12 + local_3c * pfVar12[1] + local_38 * pfVar12[2]) - pfVar12[3];
    if ((fVar4 <= _DAT_004cbec0) || (fVar5 <= _DAT_004cbec0)) {
      if (_DAT_004cbeb8 <= fVar4) {
        if (_DAT_004cbec0 < fVar4) goto LAB_00445ab3;
        if (_DAT_004cb524 <= fVar5) goto LAB_00445acb;
        iVar13 = 1;
      }
      else {
        if (fVar5 < _DAT_004cbeb8) {
          param_1 = (int *)param_1[1];
          goto LAB_00445d7f;
        }
LAB_00445ab3:
        if (fVar4 < _DAT_004cb524) {
LAB_00445acb:
          iVar13 = 0;
        }
        else {
          iVar13 = 1;
        }
      }
      if ((fVar5 - fVar4 != _DAT_004cb524) && ((fVar4 < _DAT_004cbeb8 || (_DAT_004cbec0 < fVar4))))
      {
        fVar4 = -(fVar4 / (fVar5 - fVar4));
        local_4c = (*param_4 - local_58) * fVar4 + local_58;
        local_48 = (param_4[1] - local_54) * fVar4 + local_54;
        local_44 = (param_4[2] - local_50) * fVar4 + local_50;
        iVar10 = FUN_00445980((int *)param_1[iVar13 + 1],param_2,&local_58,&local_4c);
        if (iVar10 != 0) {
          return 1;
        }
        if ((iVar13 == 1) && (iVar10 = *param_1, iVar10 != 0)) {
          if (((*(byte *)(*(int *)(iVar10 + 0x2c) + 0x30) & 1) != 0) &&
             (fVar4 = *(float *)(iVar10 + 0x18) - local_4c,
             fVar6 = *(float *)(iVar10 + 0x1c) - local_48,
             fVar5 = *(float *)(iVar10 + 0x20) - local_44,
             fVar4 * fVar4 + fVar6 * fVar6 + fVar5 * fVar5 <=
             *(float *)(iVar10 + 0x24) * *(float *)(iVar10 + 0x24))) {
            pfVar12 = *(float **)(iVar10 + 0x28);
            piVar1 = (int *)(iVar10 + 0x58 + (uint)*(ushort *)(iVar10 + 0x54) * 0x18);
            piVar9 = (int *)(iVar10 + 0x58);
            piVar8 = piVar1 + -6;
            while (piVar7 = piVar9, piVar7 != piVar1) {
              pfVar2 = (float *)*piVar7;
              pfVar3 = (float *)*piVar8;
              local_34 = *pfVar2;
              local_30 = pfVar2[1];
              local_2c = pfVar2[2];
              local_24 = pfVar3[1] - local_30;
              local_20 = pfVar3[2] - local_2c;
              FUN_00413050(&local_1c,local_24 * pfVar12[2] - local_20 * pfVar12[1],
                           local_20 * *pfVar12 - (*pfVar3 - local_34) * pfVar12[2],
                           (*pfVar3 - local_34) * pfVar12[1] - local_24 * *pfVar12);
              local_8 = local_14;
              local_10 = local_1c;
              local_c = local_18;
              fVar14 = FUN_0041fe80(&local_10);
              if (fVar14 != (float10)_DAT_004cb524) {
                fVar14 = (float10)_DAT_004cba94 / fVar14;
                local_10 = (float)((float10)local_10 * fVar14);
                local_c = (float)((float10)local_c * fVar14);
                local_8 = (float)((float10)local_8 * fVar14);
              }
              pfVar2 = (float *)*piVar7;
              fVar14 = FUN_0041feb0(&local_10,*pfVar2,pfVar2[1],pfVar2[2]);
              local_4 = (float)fVar14;
              fVar14 = FUN_0041feb0(&local_10,local_4c,local_48,local_44);
              if (fVar14 - (float10)local_4 < (float10)_DAT_004cbeb8) goto LAB_00445d58;
              piVar8 = piVar7;
              piVar9 = piVar7 + 6;
            }
            iVar10 = *(int *)(param_2 + 0xc);
            if (((iVar10 == 0) || (*(int *)(iVar10 + 0x2c) == 0)) ||
               (*(int **)(param_2 + 0x10) == (int *)0x0)) {
LAB_00445daa:
              pfVar12 = *(float **)(param_2 + 8);
              *(int **)(param_2 + 0x14) = param_1;
              *pfVar12 = local_4c;
              pfVar12[1] = local_48;
              pfVar12[2] = local_44;
              return 1;
            }
            uVar11 = (**(code **)(**(int **)(param_2 + 0x10) + 8))
                               (param_1,*(undefined4 *)(iVar10 + 0x30));
            iVar10 = (**(code **)(iVar10 + 0x2c))(uVar11);
            if (iVar10 != 0) goto LAB_00445daa;
          }
        }
        else if (_DAT_004cbee0 < fVar4) {
          return 0;
        }
LAB_00445d58:
        local_58 = local_4c;
        local_54 = local_48;
        local_50 = local_44;
      }
      param_1 = (int *)param_1[(iVar13 == 0) + 1];
    }
    else {
      param_1 = (int *)param_1[2];
    }
LAB_00445d7f:
    if ((*(byte *)((int)param_1 + 0x16) & 3) != 0) {
      return 0;
    }
  } while( true );
}


/* 00445de0 size=26 */

int __cdecl FUN_00445de0(int *param_1,undefined4 *param_2)

{
  FUN_00445980(param_1,(int)param_2,(float *)*param_2,(float *)param_2[1]);
  return;
}


/* 00445e00 size=124 */

int * __cdecl
FUN_00445e00(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  int *local_4;
  
  local_18 = param_2;
  local_14 = param_3;
  local_4 = (int *)0x0;
  local_c = 0;
  local_8 = 0;
  local_10 = param_4;
  iVar1 = FUN_00445de0(param_1,&local_18);
  if (iVar1 == 0) {
    return (int *)0x0;
  }
  iVar1 = *local_4;
  if ((iVar1 == 0) || (*(int *)(iVar1 + 0x2c) == 0)) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    puVar2 = *(undefined4 **)(iVar1 + 0x28);
  }
  *param_5 = *puVar2;
  param_5[1] = puVar2[1];
  param_5[2] = puVar2[2];
  param_5[3] = puVar2[3];
  return local_4;
}


/* 00445ec0 size=50 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00445ec0(void)

{
  _DAT_004ea470 = &PTR_LAB_004cb514;
  FUN_0044df20((LPCRITICAL_SECTION)&DAT_004ea490);
  _DAT_004ea470 = &PTR_FUN_004cc5b4;
  FUN_004b7be0((uint *)&DAT_004ea474,0xc,0x20,0x20);
  return;
}


/* 00445f00 size=12 */

void FUN_00445f00(void)

{
  FUN_004b9cf5(&LAB_00445f10);
  return;
}


/* 00445f50 size=10 */

void FUN_00445f50(void)

{
  FUN_0044df20((LPCRITICAL_SECTION)&DAT_004ea4a8);
  return;
}


/* 00445f60 size=12 */

void FUN_00445f60(void)

{
  FUN_004b9cf5(&LAB_00445f70);
  return;
}


/* 00445fe0 size=117 */

undefined4 * __cdecl FUN_00445fe0(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  FUN_0044df50((LPCRITICAL_SECTION)&DAT_004ea490);
  puVar1 = DAT_004ea48c;
  if (DAT_004ea48c == (undefined4 *)0x0) {
    FUN_004b7c60(0x4ea474,DAT_004ea47c);
    puVar1 = DAT_004ea48c;
    if (DAT_004ea48c == (undefined4 *)0x0) {
      puVar1 = (undefined4 *)0x0;
      goto LAB_00446036;
    }
  }
  DAT_004ea48c = (undefined4 *)*puVar1;
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
  }
LAB_00446036:
  FUN_0044df60((LPCRITICAL_SECTION)&DAT_004ea490);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
    puVar1[1] = param_2;
  }
  return puVar1;
}


/* 00446060 size=51 */

undefined4 __cdecl FUN_00446060(int *param_1,int param_2)

{
  if (param_2 == 0) {
    return 1;
  }
  FUN_0044df50((LPCRITICAL_SECTION)&DAT_004ea4a8);
  *(int *)(param_2 + 8) = *param_1;
  *param_1 = param_2;
  FUN_0044df60((LPCRITICAL_SECTION)&DAT_004ea4a8);
  return 0;
}


/* 004460a0 size=101 */

undefined4 * __fastcall FUN_004460a0(int param_1)

{
  LPCRITICAL_SECTION p_Var1;
  undefined4 *puVar2;
  
  p_Var1 = (LPCRITICAL_SECTION)(param_1 + 0x20);
  FUN_0044df50(p_Var1);
  puVar2 = *(undefined4 **)(param_1 + 0x1c);
  if (puVar2 == (undefined4 *)0x0) {
    FUN_004b7c60(param_1 + 4,*(int *)(param_1 + 0xc));
    puVar2 = *(undefined4 **)(param_1 + 0x1c);
    if (puVar2 == (undefined4 *)0x0) {
      FUN_0044df60(p_Var1);
      return (undefined4 *)0x0;
    }
  }
  *(undefined4 *)(param_1 + 0x1c) = *puVar2;
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2[2] = 0;
  }
  FUN_0044df60(p_Var1);
  return puVar2;
}


/* 00446110 size=49 */

void __thiscall FUN_00446110(void *this,undefined4 *param_1)

{
  FUN_0044df50((LPCRITICAL_SECTION)((int)this + 0x20));
  if ((param_1 != (undefined4 *)0x0) && (this != (void *)0xfffffffc)) {
    *param_1 = *(undefined4 *)((int)this + 0x1c);
    *(undefined4 **)((int)this + 0x1c) = param_1;
  }
  FUN_0044df60((LPCRITICAL_SECTION)((int)this + 0x20));
  return;
}


/* 00446150 size=48 */

void __fastcall FUN_00446150(int param_1)

{
  FUN_0044df50((LPCRITICAL_SECTION)(param_1 + 0x20));
  FUN_004b7c10(param_1 + 4);
  FUN_004b7b90((uint *)(param_1 + 4),0xc,0x20);
  FUN_0044df60((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}


/* 00446180 size=60 */

undefined4 * __thiscall FUN_00446180(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cc5b4;
  FUN_004b7c10((int)this + 4);
  FUN_0044df40((LPCRITICAL_SECTION)((int)this + 0x20));
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004461c0 size=12 */

undefined4 * __fastcall FUN_004461c0(undefined4 *param_1)

{
  FUN_004462d0(param_1);
  return param_1;
}


/* 004461e0 size=235 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004461e0(void *this,undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  float fVar3;
  longlong lVar4;
  
  fVar3 = _DAT_004cba94;
  *(undefined4 *)((int)this + 0x24) = param_3;
  *(undefined4 *)((int)this + 0x28) = param_3;
  *(undefined4 *)((int)this + 0x2c) = param_3;
  *(float *)((int)this + 0x30) = fVar3 / *(float *)((int)this + 0x24);
  *(float *)((int)this + 0x34) = _DAT_004cba94 / *(float *)((int)this + 0x28);
  *(float *)((int)this + 0x38) = _DAT_004cba94 / *(float *)((int)this + 0x2c);
  lVar4 = __ftol();
  *(int *)((int)this + 8) = (int)lVar4 + 1;
  lVar4 = __ftol();
  *(int *)((int)this + 0xc) = (int)lVar4 + 1;
  lVar4 = __ftol();
  *(int *)((int)this + 0x10) = (int)lVar4 + 1;
  if (*(int *)((int)this + 8) == 0) {
    *(undefined4 *)((int)this + 8) = 1;
  }
  if (*(int *)((int)this + 0xc) == 0) {
    *(undefined4 *)((int)this + 0xc) = 1;
  }
  if (*(int *)((int)this + 0x10) == 0) {
    *(undefined4 *)((int)this + 0x10) = 1;
  }
  iVar1 = *(int *)((int)this + 8);
  iVar2 = *(int *)((int)this + 0xc);
  *(int *)((int)this + 0x14) = iVar1 + -1;
  *(int *)((int)this + 0x18) = iVar2 + -1;
  *(int *)((int)this + 0x1c) = *(int *)((int)this + 0x10) + -1;
  *(int *)((int)this + 0x20) = iVar2 * iVar1;
  *(int *)((int)this + 4) = *(int *)((int)this + 0x10) * iVar2 * iVar1;
  *(undefined4 *)((int)this + 0x3c) = *param_1;
  *(undefined4 *)((int)this + 0x40) = param_1[1];
  *(undefined4 *)((int)this + 0x44) = param_1[2];
  return;
}


/* 004462d0 size=53 */

void __fastcall FUN_004462d0(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[7] = 0;
  param_1[6] = 0;
  param_1[5] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  return;
}


/* 00446310 size=23 */

void __fastcall FUN_00446310(undefined4 *param_1)

{
  FUN_00430fe0((undefined *)*param_1);
  FUN_004462d0(param_1);
  return;
}


/* 00446730 size=73 */

void __thiscall
FUN_00446730(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9)

{
  *(undefined4 *)this = param_1;
  *(undefined4 *)((int)this + 4) = param_2;
  *(undefined4 *)((int)this + 8) = param_3;
  *(undefined4 *)((int)this + 0xc) = param_4;
  *(undefined4 *)((int)this + 0x10) = param_5;
  *(undefined4 *)((int)this + 0x14) = param_6;
  *(undefined4 *)((int)this + 0x18) = param_7;
  *(undefined4 *)((int)this + 0x1c) = param_8;
  *(undefined4 *)((int)this + 0x20) = param_9;
  return;
}


/* 00446780 size=81 */

int __cdecl FUN_00446780(float param_1,float param_2,float param_3)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float local_4;
  
  iVar4 = 0;
  local_4 = -2.0;
  iVar3 = 0;
  pfVar2 = (float *)&DAT_004ea4dc;
  do {
    fVar1 = param_2 * *pfVar2 + param_3 * pfVar2[1] + param_1 * pfVar2[-1];
    if (local_4 < fVar1) {
      iVar4 = iVar3;
      local_4 = fVar1;
    }
    pfVar2 = pfVar2 + 9;
    iVar3 = iVar3 + 1;
  } while (pfVar2 < &DAT_004ea5b4);
  return iVar4;
}


/* 00446f90 size=174 */

undefined4 __thiscall FUN_00446f90(void *this,int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined1 uStack00000000;
  
  uVar2 = param_2;
  iVar1 = param_1;
  if ((param_1 == 0) || (param_2 == 0)) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   PTR_s_LMessageImpl_ReadStringFL_004d9d20);
    }
    return 0x3c;
  }
  uVar3 = 0;
  if (param_2 != 0) {
    do {
      (**(code **)(*(int *)this + 8))(&param_1);
      *(char *)(uVar3 + iVar1) = (char)param_1;
      if ((char)param_1 == '\0') {
        return 0;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar2);
  }
  *(undefined1 *)(iVar1 + -1 + uVar2) = 0;
  (**(code **)(*(int *)this + 8))(&param_1);
  while (uStack00000000 != '\0') {
    (**(code **)(*(int *)this + 8))(&uStack00000000);
  }
  return 0;
}


/* 00447500 size=50 */

undefined4 __thiscall FUN_00447500(void *this,char *param_1)

{
  char *pcVar1;
  char cVar2;
  
  if (param_1 != (char *)0x0) {
    cVar2 = *param_1;
    while (cVar2 != '\0') {
      (**(code **)(*(int *)this + 0x44))(cVar2);
      pcVar1 = param_1 + 1;
      param_1 = param_1 + 1;
      cVar2 = *pcVar1;
    }
  }
  (**(code **)(*(int *)this + 0x44))(0);
  return 0;
}


/* 00447640 size=171 */

undefined4 __thiscall FUN_00447640(void *this,int *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != (int *)0x0) {
    iVar1 = (**(code **)(*param_1 + 0x90))();
    if (iVar1 != 0) {
      (**(code **)(*(int *)this + 0x48))(0xffff);
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     PTR_s_LMessageImpl_WriteMessage_004d9d28);
      }
      return 0x49;
    }
  }
  (**(code **)(*(int *)this + 0x48))(*(short *)(param_1[2] + 0x34) + -1);
  iVar1 = param_1[2];
  iVar2 = 0;
  if (0 < (int)(*(ushort *)(iVar1 + 0x34) - 1)) {
    do {
      (**(code **)(*(int *)this + 0x44))(*(undefined1 *)(*(int *)(iVar1 + 0x54) + 1 + iVar2));
      iVar1 = param_1[2];
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)(*(ushort *)(iVar1 + 0x34) - 1));
  }
  return 0;
}


/* 00447740 size=30 */

void __cdecl FUN_00447740(int *param_1,undefined4 param_2,undefined1 param_3)

{
  undefined1 *local_4;
  
  local_4 = &param_3;
  (**(code **)(*param_1 + 0x7c))(param_2,&local_4);
  return;
}


/* 00447760 size=26 */

void __thiscall FUN_00447760(void *this,undefined4 param_1,undefined4 param_2)

{
  (**(code **)(**(int **)((int)this + 4) + 8))(this,param_1,param_2);
  return;
}


/* 004478c0 size=52 */

void __fastcall FUN_004478c0(int param_1)

{
  int iVar1;
  
  FUN_0046b370(*(int *)(param_1 + 8));
  iVar1 = *(int *)(param_1 + 8);
  if (((int)((uint)*(ushort *)(iVar1 + 0x34) - (uint)*(ushort *)(iVar1 + 0x38)) < 1) &&
     ((*(byte *)(iVar1 + 0x40) & 1) != 0)) {
    *(undefined2 *)(iVar1 + 0x38) = 1;
  }
  return;
}


/* 00447930 size=182 */

undefined4 * __fastcall FUN_00447930(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbb4c;
  param_1[0x111] = &PTR_LAB_004cbb50;
  param_1[0x112] = 0;
  param_1[0x113] = 0;
  param_1[0x114] = 0;
  param_1[0x115] = 0;
  if (param_1[0x112] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[0x112]);
    param_1[0x112] = 0;
    param_1[0x114] = 0;
  }
  param_1[0x112] = 0;
  param_1[0x113] = 0;
  param_1[0x115] = 0;
  param_1[0x114] = 0;
  if (param_1[0x112] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[0x112]);
    param_1[0x112] = 0;
    param_1[0x114] = 0;
  }
  param_1[0x113] = 0;
  FUN_004479f0((int)param_1);
  return param_1;
}


/* 004479f0 size=21 */

void __fastcall FUN_004479f0(int param_1)

{
  *(undefined4 *)(param_1 + 0x438) = 0;
  *(undefined4 *)(param_1 + 0x43c) = 0;
  *(undefined4 *)(param_1 + 0x440) = 0;
  return;
}


/* 00447a10 size=1006 */

/* FUN_00447a10: lifted from original x86 -> lt_lifted.c */


/* 00447e00 size=55 */

undefined4 * FUN_00447e00(void)

{
  undefined4 *puVar1;
  undefined4 *local_c;
  
  puVar1 = (undefined4 *)FUN_00430de0(0xa0);
  if (puVar1 == (undefined4 *)0x0) {
    local_c = (undefined4 *)0x0;
  }
  else {
    local_c = FUN_00447eb0(puVar1);
  }
  return local_c;
}


/* 00447e40 size=43 */

undefined4 * __fastcall FUN_00447e40(undefined4 *param_1)

{
  param_1[6] = 0;
  *param_1 = 0;
  param_1[3] = 0;
  return param_1;
}


/* 00447e70 size=53 */

void __fastcall FUN_00447e70(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    FUN_00430df0(*(undefined **)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return;
}


/* 00447eb0 size=245 */

undefined4 * __fastcall FUN_00447eb0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  *param_1 = &PTR_LAB_004cc364;
  param_1[0x13] = 0x42f00000;
  param_1[0x11] = 0;
  FUN_00447e40(param_1 + 0x17);
  FUN_00447e40(param_1 + 0x1e);
  *param_1 = &PTR_FUN_004cc5c8;
  param_1[0x23] = param_1 + 0x1e;
  param_1[0x22] = param_1[0x23];
  puVar2 = param_1 + 0x17;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x1d] = param_1 + 0x17;
  param_1[0x19] = 0xffffffff;
  param_1[0x18] = 0xffffffff;
  param_1[0x17] = 2;
  param_1[0x27] = 0;
  param_1[0x26] = 0;
  param_1[0x25] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x13] = 0x49742400;
  param_1[0x14] = 0;
  return param_1;
}


/* 00447fb0 size=13 */

undefined4 FUN_00447fb0(void)

{
  return 0;
}


/* 00447fc0 size=46 */

undefined4 * __thiscall FUN_00447fc0(void *this,uint param_1)

{
  FUN_00447ff0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00447ff0 size=59 */

void __fastcall FUN_00447ff0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cc5c8;
  FUN_00448070((int)param_1);
  FUN_00447e70((int)(param_1 + 0x1e));
  FUN_00447e70((int)(param_1 + 0x17));
  *param_1 = &PTR_LAB_004cc364;
  return;
}


