/* lithtech.exe decompilation - unnamed_00404000 */
#include "ghidra_types.h"

/* 004040b0 size=60 */

void __cdecl FUN_004040b0(char *param_1,uint *param_2,size_t param_3)

{
  char *pcVar1;
  char cVar2;
  
  _strncpy((char *)param_2,param_1,param_3);
  *(undefined1 *)((int)param_2 + (param_3 - 1)) = 0;
  FUN_004c8d30(param_2);
  cVar2 = (char)*param_2;
  while (cVar2 != '\0') {
    if (cVar2 == '/') {
      *(undefined1 *)param_2 = 0x5c;
    }
    pcVar1 = (char *)((int)param_2 + 1);
    param_2 = (uint *)((int)param_2 + 1);
    cVar2 = *pcVar1;
  }
  return;
}


/* 004040f0 size=261 */

int __cdecl FUN_004040f0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_00430de0(0xe88);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    FUN_004b7fa0((undefined4 *)(iVar1 + 0xc));
    *(undefined ***)(iVar1 + 0x24) = &PTR_FUN_004cb504;
    FUN_004b7b90((uint *)(iVar1 + 0x28),0x20,0x20);
    *(undefined ***)(iVar1 + 0x48) = &PTR_FUN_004cb4f4;
    FUN_004b7b90((uint *)(iVar1 + 0x4c),0x28,0x20);
    FUN_00401000(iVar1 + 0x70,0xc,100,FUN_004798d0);
    FUN_00401000(iVar1 + 0x520,0xc,200,FUN_004798d0);
  }
  *(undefined4 *)(iVar1 + 0x6c) = 0;
  *(undefined4 *)(iVar1 + 0xe80) = 0;
  FUN_004b80a0((void *)(iVar1 + 0xc),0x1000);
  FUN_004b7c10(iVar1 + 0x28);
  FUN_004b7be0((uint *)(iVar1 + 0x28),0x20,0x40,0x400);
  FUN_004b7c10(iVar1 + 0x4c);
  FUN_004b7be0((uint *)(iVar1 + 0x4c),0x28,0x80,0x400);
  iVar2 = iVar1 + 0x70;
  iVar3 = 100;
  do {
    *(int *)(iVar2 + 4) = iVar2;
    *(int *)iVar2 = iVar2;
    iVar2 = iVar2 + 0xc;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *(int *)(iVar1 + 4) = iVar1;
  *(undefined4 *)(iVar1 + 0xe84) = param_1;
  *(int *)iVar1 = iVar1;
  iVar2 = iVar1 + 0x520;
  iVar3 = 200;
  do {
    *(int *)(iVar2 + 4) = iVar2;
    *(int *)iVar2 = iVar2;
    iVar2 = iVar2 + 0xc;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return iVar1;
}


/* 00404200 size=192 */

void __cdecl FUN_00404200(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  
  if (param_1 != (int *)0x0) {
    FUN_00404580(param_1);
    piVar4 = (int *)param_1[1];
    while (piVar4 != param_1) {
      piVar1 = (int *)piVar4[1];
      FUN_004278e0(*(undefined **)(piVar4[2] + 0xc));
      FUN_00430fe0((undefined *)piVar4[2]);
      piVar4 = piVar1;
    }
    piVar4 = param_1 + 0x148;
    iVar5 = 200;
    do {
      piVar1 = (int *)piVar4[1];
      while (piVar1 != piVar4) {
        piVar2 = (int *)piVar1[1];
        piVar3 = (int *)piVar1[2];
        piVar1 = piVar2;
        if ((piVar3 != (int *)0x0) && (param_1 != (int *)0xffffffd8)) {
          *piVar3 = param_1[0x10];
          param_1[0x10] = (int)piVar3;
        }
      }
      piVar4 = piVar4 + 3;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    param_1[0x12] = (int)&PTR_FUN_004cb4f4;
    FUN_004b7c10((int)(param_1 + 0x13));
    param_1[0x12] = (int)&PTR_LAB_004cb514;
    param_1[9] = (int)&PTR_FUN_004cb504;
    FUN_004b7c10((int)(param_1 + 10));
    param_1[9] = (int)&PTR_LAB_004cb514;
    FUN_004b8020(param_1 + 3);
    FUN_00430df0((undefined *)param_1);
  }
  return;
}


/* 004042e0 size=29 */

void __cdecl FUN_004042e0(int param_1,int param_2)

{
  if (param_1 != 0) {
    FUN_00438340(*(uint *)(param_1 + 0xe80),param_2);
  }
  return;
}


/* 004044c0 size=89 */

int __cdecl FUN_004044c0(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_110 [68];
  
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
  return iVar2;
}


/* 00404520 size=65 */

int __cdecl FUN_00404520(int param_1,ushort param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x74 + ((uint)param_2 % 100) * 0xc);
  while( true ) {
    if (iVar1 == param_1 + 0x70 + ((uint)param_2 % 100) * 0xc) {
      return 0;
    }
    if (*(ushort *)(*(int *)(iVar1 + 8) + 0x10) == param_2) break;
    iVar1 = *(int *)(iVar1 + 4);
  }
  return *(int *)(iVar1 + 8);
}


/* 00404580 size=192 */

void __cdecl FUN_00404580(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int local_4;
  
  piVar5 = param_1;
  if (param_1 != (int *)0x0) {
    if ((undefined *)param_1[0x1b] != (undefined *)0x0) {
      FUN_004278e0((undefined *)param_1[0x1b]);
      param_1[0x1b] = 0;
    }
    param_1 = param_1 + 0x1c;
    local_4 = 100;
    do {
      piVar4 = (int *)param_1[1];
      while (piVar4 != param_1) {
        piVar1 = (int *)piVar4[2];
        piVar2 = (int *)piVar4[1];
        piVar3 = (int *)piVar1[5];
        if ((piVar3 != (int *)0x0) && (piVar5 != (int *)0xffffffd8)) {
          *piVar3 = piVar5[0x10];
          piVar5[0x10] = (int)piVar3;
        }
        *(int *)(*piVar4 + 4) = piVar4[1];
        *(int *)piVar4[1] = *piVar4;
        piVar4[1] = (int)piVar4;
        *piVar4 = (int)piVar4;
        piVar4 = piVar2;
        if ((piVar1 != (int *)0x0) && (piVar5 != (int *)0xffffffb4)) {
          *piVar1 = piVar5[0x19];
          piVar5[0x19] = (int)piVar1;
        }
      }
      param_1 = param_1 + 3;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
    if ((int *)piVar5[0x3a0] != (int *)0x0) {
      FUN_004382e0((int *)piVar5[0x3a0]);
      piVar5[0x3a0] = 0;
    }
  }
  return;
}


/* 00404640 size=172 */

void __cdecl
FUN_00404640(undefined4 *param_1,undefined4 *param_2,int param_3,undefined4 *param_4,int *param_5)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int local_4;
  
  puVar3 = param_4;
  puVar2 = param_1;
  if (param_1 != (undefined4 *)0x0) {
    local_4 = 0;
    if (0 < param_3) {
      puVar6 = param_2;
      puVar7 = param_4;
      do {
        FUN_00427780((byte *)*puVar6,&param_1);
        if (param_1 != (undefined4 *)0x0) {
          piVar4 = FUN_00430f00(0x10);
          piVar4[2] = (int)piVar4;
          piVar4[3] = (int)param_1;
          *piVar4 = (int)puVar2;
          puVar1 = (undefined4 *)puVar2[1];
          piVar4[1] = (int)puVar1;
          *puVar1 = piVar4;
          *(int **)(*piVar4 + 4) = piVar4;
          if (puVar3 != (undefined4 *)0x0) {
            uVar5 = FUN_00427940(param_1);
            *puVar7 = uVar5;
          }
          local_4 = local_4 + 1;
          puVar7 = puVar7 + 1;
        }
        puVar6 = puVar6 + 1;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
    }
    if (param_5 != (int *)0x0) {
      *param_5 = local_4;
    }
  }
  return;
}


/* 004046f0 size=49 */

undefined1 * __cdecl FUN_004046f0(int param_1,int *param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    if (*param_2 != 2) {
      return (undefined1 *)param_2[1];
    }
    iVar1 = FUN_00404520(param_1,*(ushort *)(param_2 + 2));
    if (iVar1 != 0) {
      return *(undefined1 **)(iVar1 + 0x1c);
    }
  }
  return &DAT_004e4424;
}


/* 00404730 size=98 */

int * __cdecl FUN_00404730(int param_1,char *param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_a0 [40];
  
  if (param_1 == 0) {
    return (int *)0x0;
  }
  iVar1 = *(int *)(param_1 + 4);
  iVar3 = 0;
  if (iVar1 != param_1) {
    puVar4 = local_a0;
    do {
      iVar3 = iVar3 + 1;
      *puVar4 = *(undefined4 *)(*(int *)(iVar1 + 8) + 0xc);
      if (0x27 < iVar3) break;
      iVar1 = *(int *)(iVar1 + 4);
      puVar4 = puVar4 + 1;
    } while (iVar1 != param_1);
  }
  piVar2 = FUN_0043ff50(local_a0,iVar3,param_2);
  return piVar2;
}


/* 004047a0 size=526 */

undefined4 * __cdecl FUN_004047a0(int param_1,int *param_2,char param_3)

{
  int *piVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  byte *pbVar8;
  int iVar9;
  short sVar10;
  char *pcVar11;
  byte *pbVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  bool bVar15;
  undefined4 local_100;
  
  if (param_1 == 0) {
    return (undefined4 *)0x0;
  }
  if (*param_2 == 2) {
    iVar3 = FUN_00404520(param_1,*(ushort *)(param_2 + 2));
    if (iVar3 == 0) {
      return (undefined4 *)0x0;
    }
    if (*(int *)(iVar3 + 0xc) == *(int *)(param_1 + 0x6c)) {
      puVar13 = *(undefined4 **)(iVar3 + 0x14);
      if (puVar13 != (undefined4 *)0x0) {
        if (param_3 == -1) {
          return puVar13;
        }
        if (*(char *)(puVar13 + 6) == -1) {
          return puVar13;
        }
        if (*(char *)(puVar13 + 6) == param_3) {
          return puVar13;
        }
      }
      goto LAB_00404820;
    }
    pcVar11 = *(char **)(iVar3 + 0x1c);
  }
  else {
LAB_00404820:
    pcVar11 = (char *)param_2[1];
  }
  if (pcVar11 == (char *)0x0) {
    return (undefined4 *)0x0;
  }
  FUN_004040b0(pcVar11,&local_100,0x100);
  sVar10 = 0;
  uVar4 = 0;
  pcVar11 = (char *)&local_100;
  uVar7 = 0;
  do {
    if (*pcVar11 == '\0') break;
    uVar4 = uVar4 + (int)*pcVar11 * uVar7;
    pcVar11 = pcVar11 + 1;
    sVar10 = sVar10 + 1;
    uVar7 = uVar7 + 1;
  } while (uVar7 < 32000);
  iVar3 = param_1 + 0x520 + (uVar4 % 200) * 0xc;
  for (iVar5 = *(int *)(param_1 + 0x524 + (uVar4 % 200) * 0xc); iVar5 != iVar3;
      iVar5 = *(int *)(iVar5 + 4)) {
    puVar13 = *(undefined4 **)(iVar5 + 8);
    if (*(short *)((int)puVar13 + 0x16) == sVar10) {
      pbVar8 = (byte *)puVar13[7];
      pbVar12 = (byte *)&local_100;
      do {
        bVar2 = *pbVar8;
        bVar15 = bVar2 < *pbVar12;
        if (bVar2 != *pbVar12) {
LAB_004048cc:
          iVar9 = (1 - (uint)bVar15) - (uint)(bVar15 != 0);
          goto LAB_004048d1;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar8[1];
        bVar15 = bVar2 < pbVar12[1];
        if (bVar2 != pbVar12[1]) goto LAB_004048cc;
        pbVar8 = pbVar8 + 2;
        pbVar12 = pbVar12 + 2;
      } while (bVar2 != 0);
      iVar9 = 0;
LAB_004048d1:
      if ((iVar9 == 0) &&
         (((*(char *)(puVar13 + 6) == param_3 || (param_3 == -1)) || (*(char *)(puVar13 + 6) == -1))
         )) {
        return puVar13;
      }
    }
  }
  iVar5 = FUN_004044c0(param_1,(char *)&local_100);
  if (iVar5 == 0) {
    return (undefined4 *)0x0;
  }
  puVar13 = *(undefined4 **)(param_1 + 0x40);
  if (puVar13 == (undefined4 *)0x0) {
    FUN_004b7c60(param_1 + 0x28,*(int *)(param_1 + 0x30));
    puVar13 = *(undefined4 **)(param_1 + 0x40);
    if (puVar13 == (undefined4 *)0x0) goto LAB_00404949;
  }
  *(undefined4 *)(param_1 + 0x40) = *puVar13;
LAB_00404949:
  puVar14 = puVar13;
  for (iVar9 = 8; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  puVar13[4] = *(undefined4 *)(iVar5 + 0xc);
  *(short *)((int)puVar13 + 0x16) = sVar10;
  *(undefined2 *)(puVar13 + 5) = 0xffff;
  puVar13[3] = puVar13;
  *(char *)(puVar13 + 6) = param_3;
  uVar6 = FUN_004b80b0((void *)(param_1 + 0xc),(byte *)&local_100,1);
  puVar13[7] = uVar6;
  piVar1 = puVar13 + 1;
  *piVar1 = iVar3;
  puVar14 = *(undefined4 **)(iVar3 + 4);
  puVar13[2] = puVar14;
  *puVar14 = piVar1;
  *(int **)(*piVar1 + 4) = piVar1;
  return puVar13;
}


/* 004049b0 size=34 */

int * __cdecl FUN_004049b0(int param_1,int param_2)

{
  int *piVar1;
  
  if (param_1 == 0) {
    return (int *)0x0;
  }
  piVar1 = de_file_427ad0(*(int **)(param_2 + 0x10),*(char **)(param_2 + 0x1c));
  return piVar1;
}


/* 004049e0 size=132 */

int * __cdecl FUN_004049e0(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_1 != 0) {
    if (*param_2 == 2) {
      iVar1 = FUN_00404520(param_1,*(ushort *)(param_2 + 2));
      if (iVar1 != 0) {
        piVar2 = de_file_427ad0(*(int **)(iVar1 + 0xc),*(char **)(iVar1 + 0x1c));
        return piVar2;
      }
    }
    else {
      for (iVar1 = *(int *)(param_1 + 4); iVar1 != param_1; iVar1 = *(int *)(iVar1 + 4)) {
        piVar2 = de_file_427ad0(*(int **)(*(int *)(iVar1 + 8) + 0xc),(char *)param_2[1]);
        if (piVar2 != (int *)0x0) {
          return piVar2;
        }
      }
      if ((*param_2 == 0) &&
         (piVar2 = de_file_427ad0(*(int **)(param_1 + 0x6c),(char *)param_2[1]),
         piVar2 != (int *)0x0)) {
        return piVar2;
      }
    }
  }
  return (int *)0x0;
}


/* 00404a70 size=109 */

bool __cdecl FUN_00404a70(int param_1,char *param_2,LPCSTR param_3)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  undefined3 extraout_var;
  
  if (param_1 == 0) {
    return true;
  }
  iVar1 = *(int *)(param_1 + 4);
  while( true ) {
    if (iVar1 == param_1) {
      return true;
    }
    piVar3 = de_file_427ad0(*(int **)(*(int *)(iVar1 + 8) + 0xc),param_2);
    if (piVar3 != (int *)0x0) break;
    iVar1 = *(int *)(iVar1 + 4);
  }
  bVar2 = FUN_004282e0(piVar3,param_3);
  (**(code **)(*piVar3 + 4))();
  return CONCAT31(extraout_var,bVar2) == 0;
}


/* 00404b50 size=52 */

undefined4 * __thiscall FUN_00404b50(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cb504;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00404b90 size=52 */

undefined4 * __thiscall FUN_00404b90(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cb4f4;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00404c00 size=47 */

undefined4 __cdecl FUN_00404c00(float *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if ((DAT_004e516c == 0) || (*(int *)(DAT_004e516c + 0x161c) == 0)) {
    return 0;
  }
  uVar1 = FUN_0043913d(param_1,param_2,(int *)(DAT_004e516c + 0x6c));
  return uVar1;
}


/* 00404cc0 size=151 */

undefined4 __cdecl FUN_00404cc0(void *param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  int iVar4;
  
  iVar1 = param_3;
  if (*(uint *)((int)param_1 + 0xc) <= param_2) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   PTR_s_ClientLightAnimLT_SetLightAnimI_004d5950);
    }
    return 0x3c;
  }
  iVar3 = param_2 * 0x60 + *(int *)((int)param_1 + 8);
  if (param_4 == 0) {
    bVar2 = FUN_0043eda0(iVar3,param_3,&param_2);
    iVar4 = CONCAT31(extraout_var,bVar2);
  }
  else {
    iVar4 = 1;
  }
  FUN_0043ecc0(iVar3,iVar1);
  if (iVar4 != 0) {
    FUN_0042c990(param_1,iVar3);
  }
  return 0;
}


/* 00404d60 size=349 */

undefined4 * __cdecl FUN_00404d60(int param_1)

{
  undefined4 *this;
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00430de0(0x3d8);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  this = puVar1 + 0xe0;
  puVar1[1] = &PTR_FUN_004cba48;
  *puVar1 = &PTR_LAB_004cb890;
  FUN_0043d650(this);
  *this = &PTR_LAB_004cb83c;
  puVar1[0xe4] = param_1;
  puVar1[0xe7] = 0xbf800000;
  puVar1[0xe5] = &PTR_LAB_004cb7e4;
  puVar1[0xe8] = param_1;
  puVar1[0xe6] = 0;
  puVar1[0xe9] = &PTR_LAB_004cb7cc;
  puVar1[0xea] = param_1;
  puVar1[0xeb] = &PTR_LAB_004cb738;
  puVar1[0xec] = param_1;
  puVar1[0xed] = &PTR_LAB_004cb714;
  puVar1[0xee] = &PTR_LAB_004cb704;
  puVar1[0xef] = param_1;
  FUN_0049f0b0(puVar1 + 0xf0,param_1);
  puVar1[0xf2] = &PTR_LAB_004cb6e4;
  puVar1[0xf3] = param_1;
  puVar1[0xe1] = puVar1 + 0xed;
  puVar1[0xe2] = puVar1 + 0xeb;
  *puVar1 = &PTR_LAB_004cb52c;
  shared_iltcommon_43d680(this,puVar1 + 1);
  puVar1[2] = this;
  puVar1[3] = puVar1 + 0xe5;
  puVar1[0xdc] = puVar1 + 0xe9;
  puVar1[0xdf] = *(undefined4 *)(param_1 + 0x22c0);
  puVar1[4] = puVar1 + 0xeb;
  puVar1[5] = puVar1 + 0xed;
  puVar1[6] = puVar1 + 0xee;
  puVar1[0xdd] = puVar1 + 0xf0;
  puVar1[7] = param_1 + 0x784;
  puVar1[0xde] = puVar1 + 0xf2;
  puVar1[0xf5] = 0;
  FUN_00408a30((int)puVar1);
  puVar1[0xf4] = param_1;
  return puVar1;
}


/* 00405c20 size=1510 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00405c20(int param_1,float *param_2,undefined1 *param_3)

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
  int iVar10;
  int iVar11;
  longlong lVar12;
  int local_8c;
  
  fVar7 = *(float *)(param_1 + 0x3c);
  fVar8 = *(float *)(param_1 + 0x40);
  fVar9 = *(float *)(param_1 + 0x44);
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar3 = param_2[2];
  fVar4 = *(float *)(param_1 + 0x30);
  fVar5 = *(float *)(param_1 + 0x34);
  fVar6 = *(float *)(param_1 + 0x38);
  lVar12 = __ftol();
  iVar10 = (int)lVar12;
  lVar12 = __ftol();
  local_8c = (int)lVar12;
  lVar12 = __ftol();
  iVar11 = (int)lVar12;
  if (iVar10 < 0) {
    iVar10 = 0;
  }
  else if (*(int *)(param_1 + 0x14) < iVar10) {
    iVar10 = *(int *)(param_1 + 0x14);
  }
  if (local_8c < 0) {
    local_8c = 0;
  }
  else if (*(int *)(param_1 + 0x18) < local_8c) {
    local_8c = *(int *)(param_1 + 0x18);
  }
  if (iVar11 < 0) {
    iVar11 = 0;
  }
  else if (*(int *)(param_1 + 0x1c) < iVar11) {
    iVar11 = *(int *)(param_1 + 0x1c);
  }
  if (iVar10 != *(int *)(param_1 + 0x14)) {
    FUN_004ba9f0((double)((fVar1 - fVar7) * fVar4));
  }
  if (local_8c != *(int *)(param_1 + 0x18)) {
    FUN_004ba9f0((double)((fVar2 - fVar8) * fVar5));
  }
  if (iVar11 != *(int *)(param_1 + 0x1c)) {
    FUN_004ba9f0((double)((fVar3 - fVar9) * fVar6));
  }
  lVar12 = __ftol();
  param_3[2] = (char)lVar12;
  lVar12 = __ftol();
  param_3[1] = (char)lVar12;
  lVar12 = __ftol();
  *param_3 = (char)lVar12;
  return;
}


/* 00406cd0 size=385 */

undefined4 *
FUN_00406cd0(int param_1,float *param_2,undefined4 *param_3,undefined4 *param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  if ((param_1 == 0) || (*(char *)(param_1 + 0xbc) != '\x06')) {
    return (undefined4 *)0x0;
  }
  iVar1 = *(int *)(param_1 + 0x1ec);
  puVar3 = *(undefined4 **)(iVar1 + 0x18);
  if (puVar3 == (undefined4 *)0x0) {
    FUN_004b7c60(iVar1,*(int *)(iVar1 + 8));
    puVar3 = *(undefined4 **)(iVar1 + 0x18);
    if (puVar3 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
  }
  *(undefined4 *)(iVar1 + 0x18) = *puVar3;
  if (puVar3 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  if (*param_2 < *(float *)(param_1 + 0x238)) {
    *(float *)(param_1 + 0x238) = *param_2;
  }
  if (param_2[1] < *(float *)(param_1 + 0x23c)) {
    *(float *)(param_1 + 0x23c) = param_2[1];
  }
  if (param_2[2] < *(float *)(param_1 + 0x240)) {
    *(float *)(param_1 + 0x240) = param_2[2];
  }
  if (*(float *)(param_1 + 0x244) < *param_2) {
    *(float *)(param_1 + 0x244) = *param_2;
  }
  if (*(float *)(param_1 + 0x248) < param_2[1]) {
    *(float *)(param_1 + 0x248) = param_2[1];
  }
  if (*(float *)(param_1 + 0x24c) < param_2[2]) {
    *(float *)(param_1 + 0x24c) = param_2[2];
  }
  puVar3[9] = *param_2;
  puVar3[10] = param_2[1];
  puVar3[0xb] = param_2[2];
  puVar3[3] = *param_4;
  puVar3[4] = param_4[1];
  puVar3[5] = param_4[2];
  *puVar3 = *param_3;
  puVar3[1] = param_3[1];
  uVar2 = param_3[2];
  puVar3[6] = 0x3f800000;
  puVar3[2] = uVar2;
  puVar3[0xc] = param_5;
  puVar3[0xd] = param_5;
  puVar3[7] = *(undefined4 *)(param_1 + 0x254);
  puVar3[0xe] = *(undefined4 *)(param_1 + 0x1e8);
  puVar3[8] = param_1 + 0x1b0;
  *(undefined4 **)(param_1 + 0x1e8) = puVar3;
  *(undefined4 **)(puVar3[0xe] + 0x20) = puVar3;
  *(int *)(param_1 + 0x230) = *(int *)(param_1 + 0x230) + 1;
  *(int *)(param_1 + 0x234) = *(int *)(param_1 + 0x234) + 1;
  return puVar3;
}


/* 00406fc0 size=172 */

undefined4 __thiscall FUN_00406fc0(void *this,char *param_1,undefined4 *param_2)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_CLTClient__GetSConValueFloat_004d5c94);
    }
    return 0x3c;
  }
  *param_2 = 0;
  iVar1 = FUN_00420880(*(int *)((int)this + 0x3d0) + 0x1378,param_1);
  if (iVar1 != 0) {
    *param_2 = *(undefined4 *)(iVar1 + 0x18);
    return 0;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CLTClient__GetSConValueFloat_004d5c94);
  }
  return 0x3d;
}


/* 00407070 size=198 */

undefined4 __thiscall FUN_00407070(void *this,char *param_1,char *param_2,int param_3)

{
  int iVar1;
  
  if ((param_1 == (char *)0x0) || (param_3 == 0)) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_CLTClient__GetSConValueString_004d5cb4);
    }
    return 0x3c;
  }
  *param_2 = '\0';
  iVar1 = FUN_00420880(*(int *)((int)this + 0x3d0) + 0x1378,param_1);
  if (iVar1 != 0) {
    _strncpy(param_2,*(char **)(iVar1 + 0x14),param_3 - 1);
    param_2[param_3 + -1] = '\0';
    return 0;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CLTClient__GetSConValueString_004d5cb4);
  }
  return 0x3d;
}


/* 004073f0 size=102 */

undefined4 FUN_004073f0(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_CLTClient__ProcessAttachments_004d5d24);
    }
    return 0x3c;
  }
  for (iVar1 = *(int *)(param_1 + 0x98); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x24)) {
    FUN_00470ef0(param_1,iVar1);
  }
  return 0;
}


/* 004078b0 size=112 */

undefined4 __thiscall
FUN_004078b0(void *this,undefined4 param_1,int param_2,undefined4 param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  
  if (((param_2 != 0) && (param_4 != 0)) && (param_5 != 0)) {
    uVar1 = (**(code **)(**(int **)((int)this + 8) + 0x14))(param_1,param_2,param_3,param_4,param_5)
    ;
    return uVar1;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 PTR_s_CLTClient_GetAttachments_004d5df8);
  }
  return 0x3c;
}


/* 00407920 size=129 */

undefined4 __thiscall FUN_00407920(void *this,int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CLTClient__StartVideo_004d5dfc);
    }
    return 0x3c;
  }
  if (*(int *)((int)this + 0x3d4) != 0) {
    (**(code **)(**(int **)((int)this + 0x370) + 0x10))(*(int *)((int)this + 0x3d4));
    *(undefined4 *)((int)this + 0x3d4) = 0;
  }
  uVar1 = (**(code **)**(undefined4 **)((int)this + 0x370))
                    (param_1,param_2,(undefined4 *)((int)this + 0x3d4));
  return uVar1;
}


/* 004079b0 size=33 */

void __fastcall FUN_004079b0(int param_1)

{
  (**(code **)(**(int **)(param_1 + 0x370) + 0x10))(*(undefined4 *)(param_1 + 0x3d4));
  *(undefined4 *)(param_1 + 0x3d4) = 0;
  return;
}


/* 00407a00 size=49 */

undefined4 __fastcall FUN_00407a00(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*(int *)param_1[0xdc] + 0xc))(param_1[0xf5]);
  if (iVar1 == 0) {
    return 0xc;
  }
  (**(code **)(*param_1 + 0x154))();
  return 0xd;
}


/* 00407aa0 size=120 */

undefined4 __thiscall FUN_00407aa0(void *this,int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 != (int *)0x0) {
    iVar1 = (**(code **)(*param_1 + 0x90))();
    if (iVar1 == 0) {
      uVar2 = (**(code **)(*(int *)this + 0x16c))(param_1,(char)param_1[7],param_2);
      (**(code **)*param_1)();
      return uVar2;
    }
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CLTClient__EndMessage2_004d5e14);
  }
  return 0x3c;
}


/* 00407bd0 size=64 */

undefined1 * __thiscall FUN_00407bd0(void *this,undefined4 param_1)

{
  int *piVar1;
  void *local_4;
  
  piVar1 = *(int **)((int)this + 0x10);
  local_4 = this;
  local_4 = (void *)(**(code **)(*piVar1 + 0x2c))(param_1);
  if (local_4 == (void *)0x0) {
    (**(code **)(*piVar1 + 0x48))(&local_4,&local_4);
    return (undefined1 *)&local_4;
  }
  return (undefined1 *)0xffffffff;
}


/* 00407c70 size=63 */

undefined1 * __thiscall FUN_00407c70(void *this,undefined4 param_1)

{
  int *piVar1;
  void *local_4;
  
  piVar1 = *(int **)((int)this + 0x10);
  local_4 = this;
  local_4 = (void *)(**(code **)(*piVar1 + 0x2c))(param_1);
  if (local_4 == (void *)0x0) {
    (**(code **)(*piVar1 + 0x34))(&local_4,&local_4);
    return (undefined1 *)&local_4;
  }
  return (undefined1 *)0x0;
}


