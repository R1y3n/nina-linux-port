/* lithtech.exe decompilation - unnamed_0044c000 */
#include "ghidra_types.h"

/* 0044c000 size=54 */

undefined4 FUN_0044c000(undefined4 param_1)

{
  switch(param_1) {
  case 1:
    return 0x4000;
  default:
    return 0;
  case 3:
    return 0x1000;
  case 4:
  case 6:
    return 0x2000;
  case 5:
    return 0x800;
  }
}


/* 0044c050 size=160 */

undefined4 __fastcall FUN_0044c050(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined1 **ppuVar3;
  undefined *puStack_28;
  undefined1 *apuStack_24 [4];
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined1 auStack_8 [8];
  
  piVar1 = *(int **)(param_1 + 0x18);
  apuStack_24[0] = (undefined1 *)(apuStack_24 + 1);
  if (piVar1 != (int *)0x0) {
    puStack_28 = &DAT_004cec6c;
    iVar2 = (**(code **)*piVar1)();
    if (-1 < iVar2) {
      ppuVar3 = apuStack_24;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *ppuVar3 = (undefined1 *)0x0;
        ppuVar3 = ppuVar3 + 1;
      }
      apuStack_24[2] = (undefined1 *)DAT_004ced74;
      apuStack_24[0] = DAT_004ced6c;
      apuStack_24[3] = (undefined1 *)DAT_004ced78;
      ppuVar3 = apuStack_24;
      apuStack_24[1] = (undefined1 *)DAT_004ced70;
      uStack_14 = 0;
      uStack_10 = 2;
      (**(code **)(*piVar1 + 0xc))(piVar1,ppuVar3,0x18,auStack_8,0x10,&puStack_28);
      (**(code **)(*ppuVar3 + 8))(ppuVar3);
      return 1;
    }
  }
  return 0;
}


/* 0044c0f0 size=172 */

undefined4 __fastcall FUN_0044c0f0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 *puStack_30;
  int *piStack_2c;
  undefined4 *puStack_28;
  undefined4 local_24 [4];
  undefined4 uStack_14;
  undefined4 uStack_10;
  
  puStack_30 = *(undefined4 **)(param_1 + 0x18);
  if (puStack_30 != (undefined4 *)0x0) {
    puStack_28 = local_24 + 1;
    local_24[0] = 0;
    piStack_2c = (int *)&DAT_004cec6c;
    iVar1 = (**(code **)*puStack_30)();
    if (-1 < iVar1) {
      puStack_30 = (undefined4 *)0x1;
      puVar2 = local_24;
      for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      local_24[2] = DAT_004ced64;
      local_24[0] = DAT_004ced5c;
      local_24[3] = DAT_004ced68;
      local_24[1] = DAT_004ced60;
      uStack_14 = 0;
      uStack_10 = 2;
      piVar3 = (int *)0x18;
      (**(code **)(*piStack_2c + 0xc))(piStack_2c,local_24,0x18,&puStack_30,4,&puStack_28);
      (**(code **)(*piVar3 + 8))(piVar3);
      return 1;
    }
  }
  return 0;
}


/* 0044c1a0 size=275 */

undefined4 __fastcall FUN_0044c1a0(int param_1)

{
  int iVar1;
  undefined4 ***pppuVar2;
  int *piVar3;
  undefined4 ***pppuStack_48;
  int *piStack_44;
  undefined1 *puStack_40;
  undefined4 ***apppuStack_3c [2];
  undefined4 *puStack_30;
  int *piStack_2c;
  undefined4 ***pppuStack_28;
  undefined4 **local_24 [4];
  undefined4 uStack_14;
  undefined4 uStack_10;
  
  puStack_30 = *(undefined4 **)(param_1 + 0x18);
  if (puStack_30 != (undefined4 *)0x0) {
    pppuStack_28 = local_24 + 1;
    local_24[0] = (undefined4 **)0x0;
    piStack_2c = (int *)&DAT_004cec6c;
    iVar1 = (**(code **)*puStack_30)();
    if (-1 < iVar1) {
      pppuVar2 = local_24;
      for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pppuVar2 = (undefined4 **)0x0;
        pppuVar2 = pppuVar2 + 1;
      }
      local_24[2] = (undefined4 **)DAT_004ced64;
      apppuStack_3c[1] = &pppuStack_28;
      local_24[0] = DAT_004ced5c;
      local_24[3] = (undefined4 **)DAT_004ced68;
      apppuStack_3c[0] = (undefined4 ***)0x4;
      pppuStack_48 = local_24;
      local_24[1] = (undefined4 **)DAT_004ced60;
      uStack_14 = 0;
      uStack_10 = 1;
      piStack_44 = (int *)0x18;
      puStack_40 = (undefined1 *)&puStack_30;
      (**(code **)(*piStack_2c + 0xc))(piStack_2c);
      pppuVar2 = apppuStack_3c;
      for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pppuVar2 = (undefined4 **)0x0;
        pppuVar2 = pppuVar2 + 1;
      }
      apppuStack_3c[0] = (undefined4 ***)DAT_004ced5c;
      puStack_30 = (undefined4 *)DAT_004ced68;
      pppuStack_48 = (undefined4 ***)((uint)pppuStack_48 & 0xfffffffe);
      apppuStack_3c[1] = (undefined4 ***)DAT_004ced60;
      piStack_2c = (int *)0x0;
      pppuStack_28 = (undefined4 ***)0x2;
      piVar3 = (int *)0x18;
      (**(code **)(*piStack_44 + 0xc))(piStack_44,apppuStack_3c,0x18,&pppuStack_48,4,&puStack_40);
      (**(code **)(*piVar3 + 8))(piVar3);
      return 1;
    }
  }
  return 0;
}


/* 0044c4a0 size=361 */

int __thiscall FUN_0044c4a0(void *this,byte *param_1)

{
  uint uVar1;
  void *this_00;
  void *this_01;
  void *this_02;
  void *this_03;
  void *this_04;
  void *this_05;
  void *this_06;
  void *this_07;
  void *this_08;
  void *this_09;
  void *this_10;
  void *this_11;
  
  if (param_1 == (byte *)0x0) {
    return 0;
  }
  uVar1 = FUN_004c4c00(this,param_1,(byte *)s_Invalid_004da888);
  if (uVar1 == 0) {
    return 0;
  }
  uVar1 = FUN_004c4c00(this_00,param_1,(byte *)s_Default_004da880);
  if (uVar1 == 0) {
    return 1;
  }
  uVar1 = FUN_004c4c00(this_01,param_1,(byte *)s_Immediatly_004da8cc);
  if (uVar1 == 0) {
    return 2;
  }
  uVar1 = FUN_004c4c00(this_02,param_1,(byte *)s_Immediately_004da8c0);
  if (uVar1 == 0) {
    return 2;
  }
  uVar1 = FUN_004c4c00(this_03,param_1,(byte *)s_Immediate_004da874);
  if (uVar1 == 0) {
    return 2;
  }
  uVar1 = FUN_004c4c00(this_04,param_1,(byte *)s_NextBeat_004da8b4);
  if (uVar1 == 0) {
    return 3;
  }
  uVar1 = FUN_004c4c00(this_05,param_1,(byte *)s_NextMeasure_004da8a8);
  if (uVar1 == 0) {
    return 4;
  }
  uVar1 = FUN_004c4c00(this_06,param_1,(byte *)s_NextGrid_004da89c);
  if (uVar1 == 0) {
    return 5;
  }
  uVar1 = FUN_004c4c00(this_07,param_1,(byte *)s_NextSegment_004da890);
  if (uVar1 == 0) {
    return 6;
  }
  uVar1 = FUN_004c4c00(this_08,param_1,&DAT_004da86c);
  if (uVar1 == 0) {
    return 3;
  }
  uVar1 = FUN_004c4c00(this_09,param_1,(byte *)s_Measure_004da864);
  if (uVar1 == 0) {
    return 4;
  }
  uVar1 = FUN_004c4c00(this_10,param_1,&DAT_004da85c);
  if (uVar1 == 0) {
    return 5;
  }
  uVar1 = FUN_004c4c00(this_11,param_1,(byte *)s_Segment_004da854);
  return (-(uint)(uVar1 != 0) & 0xfffffffa) + 6;
}


/* 0044c660 size=13 */

int __fastcall FUN_0044c660(int param_1)

{
  if (*(undefined4 **)(param_1 + 0x10) != (undefined4 *)0x0) {
    *(undefined4 *)(param_1 + 0x10) = **(undefined4 **)(param_1 + 0x10);
  }
  return;
}


/* 0044c670 size=159 */

undefined4 __fastcall FUN_0044c670(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  
  puVar2 = (undefined4 *)FUN_00430de0(0xc);
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  iVar6 = *(int *)(param_1 + 4);
  puVar3 = (undefined4 *)FUN_00430de0(iVar6 * 0x14);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else if (-1 < iVar6 + -1) {
    puVar4 = puVar3 + 2;
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 5;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  puVar2[2] = puVar3;
  if (puVar3 == (undefined4 *)0x0) {
    return 0;
  }
  uVar5 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    do {
      *puVar3 = *(undefined4 *)(param_1 + 0x10);
      *(undefined4 **)(param_1 + 0x10) = puVar3;
      puVar3 = puVar3 + 5;
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(param_1 + 4));
  }
  uVar1 = *(undefined4 *)(param_1 + 8);
  puVar2[1] = 0;
  *puVar2 = uVar1;
  if (*(int *)(param_1 + 8) == 0) {
    *(undefined4 **)(param_1 + 0xc) = puVar2;
    *(undefined4 **)(param_1 + 8) = puVar2;
    return 1;
  }
  *(undefined4 **)(*(int *)(param_1 + 8) + 4) = puVar2;
  *(undefined4 **)(param_1 + 8) = puVar2;
  return 1;
}


/* 0044c710 size=197 */

undefined4 __fastcall FUN_0044c710(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  
  puVar2 = (undefined4 *)FUN_00430de0(0xc);
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  iVar5 = *(int *)(param_1 + 4);
  piVar3 = (int *)FUN_00430de0(iVar5 * 0x54 + 4);
  if (piVar3 == (int *)0x0) {
    piVar4 = (int *)0x0;
  }
  else {
    *piVar3 = iVar5;
    piVar4 = piVar3 + 1;
    if (-1 < iVar5 + -1) {
      piVar3 = piVar3 + 4;
      do {
        piVar3[-1] = 0;
        *(undefined1 *)piVar3 = 0;
        piVar3[0x10] = 0;
        piVar3[0x11] = 4;
        piVar3 = piVar3 + 0x15;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  puVar2[2] = piVar4;
  if (piVar4 == (int *)0x0) {
    return 0;
  }
  uVar6 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    do {
      *piVar4 = *(int *)(param_1 + 0x10);
      *(int **)(param_1 + 0x10) = piVar4;
      piVar4 = piVar4 + 0x15;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(param_1 + 4));
  }
  uVar1 = *(undefined4 *)(param_1 + 8);
  puVar2[1] = 0;
  *puVar2 = uVar1;
  if (*(int *)(param_1 + 8) == 0) {
    *(undefined4 **)(param_1 + 0xc) = puVar2;
    *(undefined4 **)(param_1 + 8) = puVar2;
    return 1;
  }
  *(undefined4 **)(*(int *)(param_1 + 8) + 4) = puVar2;
  *(undefined4 **)(param_1 + 8) = puVar2;
  return 1;
}


/* 0044c7e0 size=175 */

undefined4 __fastcall FUN_0044c7e0(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  
  puVar2 = (undefined4 *)FUN_00430de0(0xc);
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  iVar5 = *(int *)(param_1 + 4);
  piVar3 = (int *)FUN_00430de0(iVar5 * 0x10 + 4);
  if (piVar3 == (int *)0x0) {
    piVar4 = (int *)0x0;
  }
  else {
    *piVar3 = iVar5;
    piVar4 = piVar3 + 1;
    if (-1 < iVar5 + -1) {
      do {
        piVar3[3] = 0;
        piVar3[4] = 0;
        iVar5 = iVar5 + -1;
        piVar3 = piVar3 + 4;
      } while (iVar5 != 0);
    }
  }
  puVar2[2] = piVar4;
  if (piVar4 == (int *)0x0) {
    return 0;
  }
  uVar6 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    do {
      *piVar4 = *(int *)(param_1 + 0x10);
      *(int **)(param_1 + 0x10) = piVar4;
      piVar4 = piVar4 + 4;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(param_1 + 4));
  }
  uVar1 = *(undefined4 *)(param_1 + 8);
  puVar2[1] = 0;
  *puVar2 = uVar1;
  if (*(int *)(param_1 + 8) == 0) {
    *(undefined4 **)(param_1 + 0xc) = puVar2;
    *(undefined4 **)(param_1 + 8) = puVar2;
    return 1;
  }
  *(undefined4 **)(*(int *)(param_1 + 8) + 4) = puVar2;
  *(undefined4 **)(param_1 + 8) = puVar2;
  return 1;
}


/* 0044c890 size=123 */

undefined4 __fastcall FUN_0044c890(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  puVar2 = (undefined4 *)FUN_00430de0(0xc);
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  puVar3 = (undefined4 *)FUN_00430de0(*(int *)(param_1 + 4) << 4);
  puVar2[2] = puVar3;
  if (puVar3 == (undefined4 *)0x0) {
    return 0;
  }
  uVar4 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    do {
      *puVar3 = *(undefined4 *)(param_1 + 0x10);
      *(undefined4 **)(param_1 + 0x10) = puVar3;
      puVar3 = puVar3 + 4;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(param_1 + 4));
  }
  uVar1 = *(undefined4 *)(param_1 + 8);
  puVar2[1] = 0;
  *puVar2 = uVar1;
  if (*(int *)(param_1 + 8) == 0) {
    *(undefined4 **)(param_1 + 0xc) = puVar2;
    *(undefined4 **)(param_1 + 8) = puVar2;
    return 1;
  }
  *(undefined4 **)(*(int *)(param_1 + 8) + 4) = puVar2;
  *(undefined4 **)(param_1 + 8) = puVar2;
  return 1;
}


/* 0044c910 size=179 */

undefined4 __fastcall FUN_0044c910(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  
  puVar2 = (undefined4 *)FUN_00430de0(0xc);
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  iVar5 = *(int *)(param_1 + 4);
  piVar3 = (int *)FUN_00430de0(iVar5 * 0x50 + 4);
  if (piVar3 == (int *)0x0) {
    piVar4 = (int *)0x0;
  }
  else {
    *piVar3 = iVar5;
    piVar4 = piVar3 + 1;
    if (-1 < iVar5 + -1) {
      piVar3 = piVar3 + 4;
      do {
        piVar3[-1] = 0;
        *(undefined1 *)piVar3 = 0;
        piVar3[0x10] = 0;
        piVar3 = piVar3 + 0x14;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  puVar2[2] = piVar4;
  if (piVar4 == (int *)0x0) {
    return 0;
  }
  uVar6 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    do {
      *piVar4 = *(int *)(param_1 + 0x10);
      *(int **)(param_1 + 0x10) = piVar4;
      piVar4 = piVar4 + 0x14;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(param_1 + 4));
  }
  uVar1 = *(undefined4 *)(param_1 + 8);
  puVar2[1] = 0;
  *puVar2 = uVar1;
  if (*(int *)(param_1 + 8) == 0) {
    *(undefined4 **)(param_1 + 0xc) = puVar2;
    *(undefined4 **)(param_1 + 8) = puVar2;
    return 1;
  }
  *(undefined4 **)(*(int *)(param_1 + 8) + 4) = puVar2;
  *(undefined4 **)(param_1 + 8) = puVar2;
  return 1;
}


/* 0044ca00 size=47 */

void __thiscall FUN_0044ca00(void *this,int *param_1)

{
  if ((int *)param_1[1] == (int *)0x0) {
    *(int *)this = *param_1;
  }
  else {
    *(int *)param_1[1] = *param_1;
  }
  if (*param_1 == 0) {
    *(int *)((int)this + 4) = param_1[1];
    return;
  }
  *(int *)(*param_1 + 4) = param_1[1];
  return;
}


/* 0044ca30 size=37 */

void __thiscall FUN_0044ca30(void *this,int *param_1)

{
  *param_1 = *(int *)this;
  param_1[1] = 0;
  if (*(int *)this == 0) {
    *(int **)((int)this + 4) = param_1;
    *(int **)this = param_1;
    return;
  }
  *(int **)(*(int *)this + 4) = param_1;
  *(int **)this = param_1;
  return;
}


/* 0044cbd0 size=41 */

int __fastcall FUN_0044cbd0(int *param_1)

{
  char cVar1;
  int iVar2;
  
  if (param_1[0xb] == 0) {
    return 0;
  }
  iVar2 = (**(code **)(*param_1 + 0xc))();
  if (iVar2 == 0) {
    cVar1 = *(char *)param_1[0xc];
    param_1[0xc] = (int)((char *)param_1[0xc] + 1);
    return (int)cVar1;
  }
  return 0;
}


/* 0044cc60 size=38 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044cc60(void)

{
  _DAT_004ea648 = 0;
  _DAT_004ea64c = 0;
  _DAT_004ea650 = 0;
  _DAT_004ea654 = 0;
  _DAT_004ea658 = 0;
  _DAT_004ea65c = 0;
  DAT_004ea664 = 0;
  return;
}


/* 0044cc90 size=12 */

void FUN_0044cc90(void)

{
  FUN_004b9cf5(&LAB_0044cca0);
  return;
}


/* 0044ccc0 size=180 */

undefined4 * __thiscall FUN_0044ccc0(void *this,int *param_1,int param_2)

{
  LPCRITICAL_SECTION lpCriticalSection;
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  bool bVar5;
  
  lpCriticalSection = (LPCRITICAL_SECTION)((int)this + 8);
  EnterCriticalSection(lpCriticalSection);
  for (puVar1 = *(undefined4 **)this; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    iVar2 = 4;
    bVar5 = true;
    piVar3 = puVar1 + 2;
    piVar4 = param_1;
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar5 = *piVar3 == *piVar4;
      piVar3 = piVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (bVar5);
    if (bVar5) {
      LeaveCriticalSection(lpCriticalSection);
      return puVar1;
    }
  }
  iVar2 = 4;
  bVar5 = true;
  piVar3 = &DAT_004ced0c;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *param_1 == *piVar3;
    param_1 = param_1 + 1;
    piVar3 = piVar3 + 1;
  } while (bVar5);
  if (bVar5) {
    LeaveCriticalSection(lpCriticalSection);
    return (undefined4 *)0x0;
  }
  if (param_2 == 0) {
    LeaveCriticalSection(lpCriticalSection);
    return (undefined4 *)0x0;
  }
  puVar1 = FUN_0044ccc0(this,&DAT_004ced0c,1);
  LeaveCriticalSection(lpCriticalSection);
  return puVar1;
}


/* 0044cd80 size=169 */

void __thiscall FUN_0044cd80(void *this,int *param_1,short *param_2)

{
  LPCRITICAL_SECTION lpCriticalSection;
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  lpCriticalSection = (LPCRITICAL_SECTION)((int)this + 8);
  EnterCriticalSection(lpCriticalSection);
  piVar1 = (int *)FUN_00430de0(0x220);
  if (piVar1 == (int *)0x0) {
    LeaveCriticalSection(lpCriticalSection);
    return;
  }
  piVar1[2] = DAT_004cee70;
  piVar1[3] = DAT_004cee74;
  piVar1[4] = DAT_004cee78;
  piVar1[5] = DAT_004cee7c;
  piVar1[2] = *param_1;
  piVar1[3] = param_1[1];
  piVar1[4] = param_1[2];
  piVar1[5] = param_1[3];
  piVar3 = piVar1 + 6;
  for (iVar2 = 0x82; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  FUN_004bc308((short *)(piVar1 + 6),param_2,0x103);
  FUN_004b4f00(this,piVar1);
  LeaveCriticalSection(lpCriticalSection);
  return;
}


/* 0044ce30 size=49 */

void __thiscall FUN_0044ce30(void *this,int *param_1)

{
  EnterCriticalSection((LPCRITICAL_SECTION)((int)this + 8));
  FUN_004b4f60(this,param_1);
  FUN_00430df0((undefined *)param_1);
  LeaveCriticalSection((LPCRITICAL_SECTION)((int)this + 8));
  return;
}


/* 0044ce70 size=44 */

void __fastcall FUN_0044ce70(undefined4 *param_1)

{
  int *piVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 2));
  piVar1 = (int *)*param_1;
  while (piVar1 != (int *)0x0) {
    FUN_0044ce30(param_1,piVar1);
    piVar1 = (int *)*param_1;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 2));
  return;
}


/* 0044cea0 size=55 */

void __thiscall FUN_0044cea0(void *this,int param_1)

{
  int *piVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)((int)this + 8));
  piVar1 = (int *)FUN_00430de0(0xc);
  if (piVar1 != (int *)0x0) {
    piVar1[2] = param_1;
    FUN_004b4f00(this,piVar1);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)((int)this + 8));
  return;
}


/* 0044cee0 size=83 */

void __thiscall FUN_0044cee0(void *this,int param_1)

{
  LPCRITICAL_SECTION lpCriticalSection;
  int *piVar1;
  
  lpCriticalSection = (LPCRITICAL_SECTION)((int)this + 8);
  EnterCriticalSection(lpCriticalSection);
  piVar1 = *(int **)this;
  if (piVar1 != (int *)0x0) {
    while (piVar1[2] != param_1) {
      piVar1 = (int *)*piVar1;
      if (piVar1 == (int *)0x0) {
        LeaveCriticalSection(lpCriticalSection);
        return;
      }
    }
    if (piVar1 != (int *)0x0) {
      FUN_004b4f60(this,piVar1);
      FUN_00430df0((undefined *)piVar1);
    }
  }
  LeaveCriticalSection(lpCriticalSection);
  return;
}


/* 0044cf40 size=61 */

void __fastcall FUN_0044cf40(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 2));
  iVar1 = *param_1;
  while (iVar1 != 0) {
    puVar2 = *(undefined4 **)(iVar1 + 8);
    if (puVar2 != (undefined4 *)0x0) {
      FUN_0044d010(puVar2);
      FUN_00430df0((undefined *)puVar2);
    }
    iVar1 = *param_1;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 2));
  return;
}


/* 0044cf80 size=50 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044cf80(void)

{
  _OSVERSIONINFOA local_94;
  
  local_94.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_94);
  _DAT_004ea668 = (uint)(local_94.dwPlatformId != 1);
  return;
}


/* 0044cfc0 size=72 */

undefined4 * __thiscall FUN_0044cfc0(void *this,int param_1)

{
  *(undefined ***)((int)this + 4) = &PTR_LAB_004cc730;
  *(undefined ***)this = &PTR_FUN_004cc6f8;
  *(undefined ***)((int)this + 4) = &PTR_LAB_004cc6e8;
  *(undefined4 *)((int)this + 8) = 1;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(int *)((int)this + 0x10) = param_1;
  if (param_1 != 0) {
    FUN_0044d880(param_1);
    FUN_0044cea0(*(void **)(param_1 + 0x2c),(int)this);
  }
  return this;
}


/* 0044d010 size=49 */

void __fastcall FUN_0044d010(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cc6f8;
  param_1[1] = &PTR_LAB_004cc6e8;
  if (param_1[4] != 0) {
    FUN_0044cee0(*(void **)(param_1[4] + 0x2c),(int)param_1);
    FUN_0044d8f0((undefined *)param_1[4]);
  }
  FUN_0044d120((int)param_1);
  return;
}


/* 0044d120 size=40 */

undefined4 __fastcall FUN_0044d120(int param_1)

{
  if (*(int **)(param_1 + 0xc) != (int *)0x0) {
    FUN_00435220(*(int **)(param_1 + 0xc));
    FUN_00435560(&DAT_004ea630,*(int **)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return 0;
}


/* 0044d180 size=17 */

void FUN_0044d180(int param_1)

{
  InterlockedIncrement((LONG *)(param_1 + 8));
  return;
}


/* 0044d1a0 size=54 */

LONG FUN_0044d1a0(undefined4 *param_1)

{
  LONG LVar1;
  
  LVar1 = InterlockedDecrement(param_1 + 2);
  if (LVar1 != 0) {
    return param_1[2];
  }
  if (param_1 != (undefined4 *)0x0) {
    FUN_0044d010(param_1);
    FUN_00430df0((undefined *)param_1);
  }
  return 0;
}


/* 0044d390 size=69 */

undefined4 * __thiscall FUN_0044d390(void *this,int param_1)

{
  *(undefined ***)((int)this + 4) = &PTR_LAB_004cc730;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined ***)this = &PTR_FUN_004cc750;
  *(undefined ***)((int)this + 4) = &PTR_LAB_004cc740;
  *(undefined4 *)((int)this + 8) = 1;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(int *)((int)this + 0x20) = param_1;
  if (param_1 != 0) {
    FUN_0044d880(param_1);
  }
  return this;
}


/* 0044d3e0 size=37 */

void __fastcall FUN_0044d3e0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cc750;
  param_1[1] = &PTR_LAB_004cc740;
  if ((undefined *)param_1[8] != (undefined *)0x0) {
    FUN_0044d8f0((undefined *)param_1[8]);
  }
  FUN_0044d470((int)param_1);
  return;
}


/* 0044d410 size=88 */

undefined4 __thiscall FUN_0044d410(void *this,void *param_1,UINT_PTR param_2,int param_3)

{
  BOOL BVar1;
  
  FUN_0044d470((int)this);
  *(UINT_PTR *)((int)this + 0x10) = param_2;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(void **)((int)this + 0xc) = param_1;
  *(int *)((int)this + 0x14) = param_3;
  *(undefined4 *)((int)this + 0x1c) = 0;
  if ((param_1 != (void *)0x0) && (param_2 != 0 || param_3 != 0)) {
    BVar1 = IsBadReadPtr(param_1,param_2);
    if (BVar1 == 0) {
      return 0;
    }
    *(undefined4 *)((int)this + 0x10) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 *)((int)this + 0x14) = 0;
  }
  return 0x88781182;
}


/* 0044d470 size=12 */

void __fastcall FUN_0044d470(int param_1)

{
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  return;
}


/* 0044d480 size=154 */

/* FUN_0044d480: lifted from original x86 -> lt_lifted.c */


/* 0044d550 size=54 */

LONG FUN_0044d550(undefined4 *param_1)

{
  LONG LVar1;
  
  LVar1 = InterlockedDecrement(param_1 + 2);
  if (LVar1 != 0) {
    return param_1[2];
  }
  if (param_1 != (undefined4 *)0x0) {
    FUN_0044d3e0(param_1);
    FUN_00430df0((undefined *)param_1);
  }
  return 0;
}


/* 0044d6a0 size=174 */

undefined4 * __fastcall FUN_0044d6a0(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  *param_1 = &PTR_LAB_004cc788;
  InitializeCriticalSection((LPCRITICAL_SECTION)(param_1 + 3));
  param_1[1] = 1;
  param_1[2] = 0;
  param_1[9] = 0;
  MultiByteToWideChar(0,1,&DAT_004da92c,-1,(LPWSTR)(param_1 + 0xc),0x104);
  MultiByteToWideChar(0,1,&DAT_004da0d8,-1,(LPWSTR)(param_1 + 0xd),0x104);
  puVar1 = (undefined4 *)FUN_00430de0(0x20);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = 0;
    puVar1[1] = 0;
    InitializeCriticalSection((LPCRITICAL_SECTION)(puVar1 + 2));
  }
  param_1[10] = puVar1;
  puVar1 = (undefined4 *)FUN_00430de0(0x20);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = 0;
    puVar1[1] = 0;
    InitializeCriticalSection((LPCRITICAL_SECTION)(puVar1 + 2));
  }
  param_1[0xb] = puVar1;
  FUN_00435470(&DAT_004ea630,(PRTL_CRITICAL_SECTION_DEBUG)0x5);
  return param_1;
}


/* 0044d750 size=154 */

void __fastcall FUN_0044d750(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  puVar1 = (undefined4 *)param_1[9];
  *param_1 = &PTR_LAB_004cc788;
  while (puVar1 != (undefined4 *)0x0) {
    param_1[9] = *puVar1;
    piVar2 = (int *)puVar1[5];
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2);
    }
    FUN_00430df0((undefined *)puVar1);
    puVar1 = (undefined4 *)param_1[9];
  }
  puVar1 = (undefined4 *)param_1[10];
  if (puVar1 != (undefined4 *)0x0) {
    if (puVar1 != (undefined4 *)0x0) {
      FUN_0044ce70(puVar1);
      DeleteCriticalSection((LPCRITICAL_SECTION)(puVar1 + 2));
      FUN_00430df0((undefined *)puVar1);
    }
    param_1[10] = 0;
  }
  piVar2 = (int *)param_1[0xb];
  if (piVar2 != (int *)0x0) {
    FUN_0044cf40(piVar2);
    DeleteCriticalSection((LPCRITICAL_SECTION)(piVar2 + 2));
    FUN_00430df0((undefined *)piVar2);
    param_1[0xb] = 0;
  }
  FUN_00435490((LPCRITICAL_SECTION)&DAT_004ea630);
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 3));
  return;
}


/* 0044d7f0 size=8 */

undefined4 FUN_0044d7f0(void)

{
  FUN_0044cf80();
  return 0;
}


/* 0044d880 size=11 */

void __fastcall FUN_0044d880(int param_1)

{
  InterlockedIncrement((LONG *)(param_1 + 8));
  return;
}


/* 0044d8f0 size=55 */

LONG __fastcall FUN_0044d8f0(undefined *param_1)

{
  LONG LVar1;
  
  LVar1 = InterlockedDecrement((LONG *)(param_1 + 8));
  if ((LVar1 != 0) || (*(int *)(param_1 + 4) != 0)) {
    return *(LONG *)(param_1 + 8);
  }
  if (param_1 != (undefined *)0x0) {
    FUN_0044d750((undefined4 *)param_1);
    FUN_00430df0(param_1);
  }
  return 0;
}


/* 0044dac0 size=364 */

int __thiscall FUN_0044dac0(void *this,int param_1,LPVOID *param_2)

{
  HRESULT HVar1;
  void *this_00;
  int *this_01;
  undefined4 *puVar2;
  int iVar3;
  int *unaff_EBP;
  WCHAR *pWVar4;
  int *local_20c;
  WCHAR local_208 [260];
  
  HVar1 = CoCreateInstance((IID *)(param_1 + 0x18),(LPUNKNOWN)0x0,1,(IID *)&DAT_004cecac,param_2);
  if (HVar1 < 0) {
    return HVar1;
  }
  pWVar4 = local_208;
  for (iVar3 = 0x82; iVar3 != 0; iVar3 = iVar3 + -1) {
    pWVar4[0] = L'\0';
    pWVar4[1] = L'\0';
    pWVar4 = pWVar4 + 2;
  }
  this_00 = (void *)FUN_00430de0(0x14);
  if ((this_00 == (void *)0x0) || (this_01 = FUN_0044cfc0(this_00,(int)this), this_01 == (int *)0x0)
     ) {
    iVar3 = -0x7ff8fff2;
  }
  else {
    if ((*(byte *)(param_1 + 4) & 0x20) == 0) {
      puVar2 = FUN_0044ccc0(*(void **)((int)this + 0x28),(int *)(param_1 + 0x18),1);
      if (puVar2 != (undefined4 *)0x0) {
        FUN_004bc2e3(local_208,(short *)(puVar2 + 6));
      }
      iVar3 = FUN_004bc580(local_208);
      if ((local_208[iVar3 + -1] != *(WCHAR *)((int)this + 0x34)) &&
         (iVar3 = FUN_004bc580(local_208), local_208[iVar3 + -1] != *(WCHAR *)((int)this + 0x30))) {
        FUN_004bc2b9(local_208,(WCHAR *)((int)this + 0x34));
      }
      FUN_004bc2b9(local_208,(short *)(param_1 + 0x138));
    }
    else {
      FUN_004bc2e3(local_208,(short *)(param_1 + 0x138));
    }
    iVar3 = ltdirectmusicloader_44d050(this_01,local_208);
    if ((-1 < iVar3) &&
       (iVar3 = (*(code *)**(undefined4 **)*param_2)(*param_2,&DAT_004ceea0,&local_20c), -1 < iVar3)
       ) {
      iVar3 = (**(code **)(*local_20c + 0x14))(local_20c,this_01);
      (**(code **)(*unaff_EBP + 8))(unaff_EBP);
    }
    (**(code **)(*this_01 + 8))(this_01);
    if (-1 < iVar3) {
      return iVar3;
    }
  }
  (**(code **)(*(int *)*param_2 + 8))(*param_2);
  return iVar3;
}


/* 0044dc30 size=196 */

HRESULT __thiscall FUN_0044dc30(void *this,int param_1,LPVOID *param_2)

{
  LPVOID *ppvVar1;
  HRESULT HVar2;
  void *this_00;
  int *this_01;
  int iVar3;
  int *unaff_retaddr;
  
  ppvVar1 = param_2;
  HVar2 = CoCreateInstance((IID *)(param_1 + 0x18),(LPUNKNOWN)0x0,1,(IID *)&DAT_004cecac,param_2);
  if (HVar2 < 0) {
    return HVar2;
  }
  this_00 = (void *)FUN_00430de0(0x28);
  if ((this_00 == (void *)0x0) || (this_01 = FUN_0044d390(this_00,(int)this), this_01 == (int *)0x0)
     ) {
    (**(code **)(*(int *)*ppvVar1 + 8))(*ppvVar1);
    return -0x7ff8fff2;
  }
  iVar3 = FUN_0044d410(this_01,*(void **)(param_1 + 0x348),*(UINT_PTR *)(param_1 + 0x340),
                       *(int *)(param_1 + 0x344));
  if ((-1 < iVar3) &&
     (iVar3 = (*(code *)**(undefined4 **)*ppvVar1)(*ppvVar1,&DAT_004ceea0,&param_2), -1 < iVar3)) {
    iVar3 = (**(code **)((int)*param_2 + 0x14))(param_2,this_01);
    (**(code **)(*unaff_retaddr + 8))(unaff_retaddr);
  }
  (**(code **)(*this_01 + 8))(this_01);
  if (iVar3 < 0) {
    (**(code **)(*(int *)*ppvVar1 + 8))(*ppvVar1);
  }
  return iVar3;
}


/* 0044dd90 size=112 */

undefined4 FUN_0044dd90(int *param_1,undefined4 param_2,LPCSTR param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  LPCSTR pCVar4;
  WCHAR local_208 [260];
  
  uVar3 = 0xffffffff;
  pCVar4 = param_3;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pCVar4;
    pCVar4 = pCVar4 + 1;
  } while (cVar1 != '\0');
  if (~uVar3 - 1 < 0x104) {
    MultiByteToWideChar(0,1,param_3,-1,local_208,0x104);
    uVar2 = (**(code **)(*param_1 + 0x14))(param_1,param_2,local_208,param_4);
    return uVar2;
  }
  return 0x80004005;
}


/* 0044de80 size=28 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044de80(void)

{
  _DAT_004ea688 = &PTR_FUN_004cc7b8;
  FUN_004b7b90((uint *)&DAT_004ea68c,0x20,0x20);
  return;
}


/* 0044dea0 size=12 */

void FUN_0044dea0(void)

{
  FUN_004b9cf5(&LAB_0044deb0);
  return;
}


/* 0044def0 size=10 */

void FUN_0044def0(void)

{
  FUN_0044df20((LPCRITICAL_SECTION)&DAT_004ea670);
  return;
}


/* 0044df00 size=12 */

void FUN_0044df00(void)

{
  FUN_004b9cf5(&LAB_0044df10);
  return;
}


/* 0044df20 size=27 */

LPCRITICAL_SECTION __fastcall FUN_0044df20(LPCRITICAL_SECTION param_1)

{
  int iVar1;
  LPCRITICAL_SECTION p_Var2;
  
  p_Var2 = param_1;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    p_Var2->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)0x0;
    p_Var2 = (LPCRITICAL_SECTION)&p_Var2->LockCount;
  }
  InitializeCriticalSection(param_1);
  return param_1;
}


/* 0044df40 size=8 */

void __fastcall FUN_0044df40(LPCRITICAL_SECTION param_1)

{
  DeleteCriticalSection(param_1);
  return;
}


/* 0044df50 size=8 */

void __fastcall FUN_0044df50(LPCRITICAL_SECTION param_1)

{
  EnterCriticalSection(param_1);
  return;
}


/* 0044df60 size=8 */

void __fastcall FUN_0044df60(LPCRITICAL_SECTION param_1)

{
  LeaveCriticalSection(param_1);
  return;
}


/* 0044df70 size=11 */

void __fastcall FUN_0044df70(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}


/* 0044df80 size=41 */

LPCRITICAL_SECTION __fastcall FUN_0044df80(LPCRITICAL_SECTION param_1)

{
  HANDLE pvVar1;
  
  FUN_0044df20(param_1);
  param_1[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)&PTR_LAB_004cc7c8;
  param_1[1].LockCount = 0;
  param_1[1].RecursionCount = 0;
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCSTR)0x0);
  param_1[1].OwningThread = pvVar1;
  return param_1;
}


/* 0044dfb0 size=42 */

void __fastcall FUN_0044dfb0(LPCRITICAL_SECTION param_1)

{
  FUN_0044e040((int)param_1);
  CloseHandle(param_1[1].OwningThread);
  param_1[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)&PTR_LAB_004cc7c8;
  param_1[1].RecursionCount = 0;
  param_1[1].LockCount = 0;
  FUN_0044df40(param_1);
  return;
}


/* 0044dfe0 size=95 */

undefined4 __fastcall FUN_0044dfe0(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004b7770();
  if (iVar1 != 0) {
    iVar1 = FUN_004b7770();
    if (iVar1 != 0) {
      FUN_0044e040(param_1);
      return 0;
    }
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LThreadQueue__Init_004da930);
  }
  return 0x49;
}


/* 0044e040 size=89 */

void __fastcall FUN_0044e040(int param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  if (*(int **)(param_1 + 0x20) != (int *)0x0) {
    piVar1 = *(int **)(param_1 + 0x20);
    piVar3 = DAT_004ea6a4;
    do {
      piVar2 = (int *)(piVar1[1] & -(uint)(piVar1[1] != *(uint *)(param_1 + 0x20)));
      if (piVar1 != (int *)0x0) {
        *piVar1 = (int)piVar3;
        piVar3 = piVar1;
        DAT_004ea6a4 = piVar1;
      }
      piVar1 = piVar2;
    } while (piVar2 != (int *)0x0);
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  PulseEvent(*(HANDLE *)(param_1 + 0x24));
  return;
}


/* 0044e0a0 size=308 */

undefined4 __thiscall FUN_0044e0a0(void *this,int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  iVar1 = FUN_004b7770();
  if (iVar1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LThreadQueue__PostMessage_004da944
                  );
    }
    return 0x49;
  }
  FUN_0044df50(this);
  FUN_0044df50((LPCRITICAL_SECTION)&DAT_004ea670);
  piVar2 = DAT_004ea6a4;
  if (DAT_004ea6a4 == (int *)0x0) {
    FUN_004b7c60(0x4ea68c,DAT_004ea694);
    piVar2 = DAT_004ea6a4;
    if (DAT_004ea6a4 == (int *)0x0) goto LAB_0044e17d;
  }
  DAT_004ea6a4 = (int *)*piVar2;
  if (piVar2 != (int *)0x0) {
    FUN_0044df70((int)piVar2);
    piVar3 = piVar2;
    for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = *param_1;
      param_1 = param_1 + 1;
      piVar3 = piVar3 + 1;
    }
    if (*(int **)((int)this + 0x20) == (int *)0x0) {
      piVar2[1] = (int)piVar2;
      *piVar2 = (int)piVar2;
      *(int **)((int)this + 0x20) = piVar2;
    }
    else {
      iVar1 = **(int **)((int)this + 0x20);
      **(undefined4 **)(iVar1 + 4) = piVar2;
      piVar2[1] = *(int *)(iVar1 + 4);
      *piVar2 = iVar1;
      *(int **)(iVar1 + 4) = piVar2;
    }
    *(int *)((int)this + 0x1c) = *(int *)((int)this + 0x1c) + 1;
    SetEvent(*(HANDLE *)((int)this + 0x24));
  }
LAB_0044e17d:
  FUN_0044df60((LPCRITICAL_SECTION)&DAT_004ea670);
  FUN_0044df60(this);
  if (piVar2 != (int *)0x0) {
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LThreadQueue__PostMessage_004da944);
  }
  return 0x43;
}


/* 0044e1e0 size=63 */

int __thiscall FUN_0044e1e0(void *this,int *param_1,int param_2)

{
  DWORD DVar1;
  int iVar2;
  
  DVar1 = WaitForSingleObject(*(HANDLE *)((int)this + 0x24),-(uint)(param_2 != 0));
  if (DVar1 == 0x102) {
    return 0x3d;
  }
  iVar2 = FUN_0044e280(this,param_1);
  return (-(uint)(iVar2 != 0) & 0xffffffc3) + 0x3d;
}


/* 0044e220 size=91 */

undefined4 __thiscall FUN_0044e220(void *this,undefined4 *param_1)

{
  DWORD DVar1;
  int iVar2;
  undefined4 *puVar3;
  
  DVar1 = WaitForSingleObject(*(HANDLE *)((int)this + 0x24),0);
  if (DVar1 == 0x102) {
    return 0x3d;
  }
  FUN_0044df50(this);
  if (*(undefined4 **)((int)this + 0x20) == (undefined4 *)0x0) {
    FUN_0044df60(this);
    return 0x3d;
  }
  puVar3 = *(undefined4 **)((int)this + 0x20);
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *puVar3;
    puVar3 = puVar3 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0044df60(this);
  return 0;
}


/* 0044e280 size=214 */

undefined4 __thiscall FUN_0044e280(void *this,int *param_1)

{
  int *piVar1;
  DWORD DVar2;
  int iVar3;
  int *piVar4;
  
  DVar2 = WaitForSingleObject(*(HANDLE *)((int)this + 0x24),0);
  if (DVar2 == 0x102) {
    return 0;
  }
  FUN_0044df50(this);
  piVar1 = *(int **)((int)this + 0x20);
  if (piVar1 == (int *)0x0) {
    ResetEvent(*(HANDLE *)((int)this + 0x24));
    FUN_0044df60(this);
    return 0;
  }
  if (param_1 != (int *)0x0) {
    piVar4 = piVar1;
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *param_1 = *piVar4;
      piVar4 = piVar4 + 1;
      param_1 = param_1 + 1;
    }
  }
  *(int *)(*piVar1 + 4) = piVar1[1];
  *(int *)piVar1[1] = *piVar1;
  if (piVar1 == *(int **)((int)this + 0x20)) {
    *(int *)((int)this + 0x20) = (*(int **)((int)this + 0x20))[1];
  }
  iVar3 = *(int *)((int)this + 0x1c) + -1;
  *(int *)((int)this + 0x1c) = iVar3;
  if (iVar3 == 0) {
    *(undefined4 *)((int)this + 0x20) = 0;
  }
  FUN_0044df50((LPCRITICAL_SECTION)&DAT_004ea670);
  if (piVar1 != (int *)0x0) {
    *piVar1 = (int)DAT_004ea6a4;
    DAT_004ea6a4 = piVar1;
  }
  FUN_0044df60((LPCRITICAL_SECTION)&DAT_004ea670);
  if (*(int *)((int)this + 0x20) == 0) {
    ResetEvent(*(HANDLE *)((int)this + 0x24));
  }
  FUN_0044df60(this);
  return 1;
}


/* 0044e360 size=37 */

undefined4 * __fastcall FUN_0044e360(undefined4 *param_1)

{
  FUN_0044df80((LPCRITICAL_SECTION)(param_1 + 1));
  FUN_0044df80((LPCRITICAL_SECTION)(param_1 + 0xb));
  *param_1 = &PTR_FUN_004cc7f8;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  return param_1;
}


/* 0044e390 size=30 */

undefined4 * __thiscall FUN_0044e390(void *this,byte param_1)

{
  FUN_0044e3b0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0044e3b0 size=27 */

void __fastcall FUN_0044e3b0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cc7f8;
  FUN_0044dfb0((LPCRITICAL_SECTION)(param_1 + 0xb));
  FUN_0044dfb0((LPCRITICAL_SECTION)(param_1 + 1));
  return;
}


/* 0044e3d0 size=21 */

void __fastcall FUN_0044e3d0(int param_1)

{
  FUN_0044e040(param_1 + 4);
  FUN_0044e040(param_1 + 0x2c);
  return;
}


/* 0044e3f0 size=207 */

undefined4 __thiscall FUN_0044e3f0(void *this,int param_1)

{
  int iVar1;
  HANDLE pvVar2;
  
  iVar1 = FUN_0044dfe0((int)this + 4);
  if ((iVar1 != 0) || (iVar1 = FUN_0044dfe0((int)this + 0x2c), iVar1 != 0)) {
    FUN_0044e040((int)this + 4);
    FUN_0044e040((int)this + 0x2c);
    return 1;
  }
  pvVar2 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCSTR)0x0);
  *(HANDLE *)((int)this + 0x5c) = pvVar2;
  pvVar2 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_0044e4c0,this,4,(LPDWORD)((int)this + 0x58)
                       );
  *(HANDLE *)((int)this + 0x54) = pvVar2;
  if (pvVar2 != (HANDLE)0x0) {
    iVar1 = FUN_0044e4e0(param_1);
    SetThreadPriority(*(HANDLE *)((int)this + 0x54),iVar1);
    ResumeThread(*(HANDLE *)((int)this + 0x54));
    return 0;
  }
  FUN_004356e0();
  if (DAT_004e4420 < 1) {
    return 1;
  }
  FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LThread__Start_004da960);
  return 1;
}


/* 0044e4c0 size=25 */

undefined4 FUN_0044e4c0(int *param_1)

{
  (**(code **)(*param_1 + 8))();
  (**(code **)(*param_1 + 4))();
  return 0;
}


/* 0044e4e0 size=54 */

int __cdecl FUN_0044e4e0(int param_1)

{
  if (param_1 == 0) {
    return -0xf;
  }
  if (param_1 == 1) {
    return -2;
  }
  if (param_1 == 2) {
    return -1;
  }
  if (param_1 == 3) {
    return 0;
  }
  return (param_1 != 4) + 1;
}


/* 0044e520 size=78 */

undefined4 __fastcall FUN_0044e520(int param_1)

{
  if (*(int *)(param_1 + 0x54) == 0) {
    return 0;
  }
  SetEvent(*(HANDLE *)(param_1 + 0x5c));
  WaitForSingleObject(*(HANDLE *)(param_1 + 0x54),0xffffffff);
  CloseHandle(*(HANDLE *)(param_1 + 0x54));
  CloseHandle(*(HANDLE *)(param_1 + 0x5c));
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  return 0;
}


/* 0044e6e0 size=52 */

undefined4 * __thiscall FUN_0044e6e0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cc7b8;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0044e720 size=411 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0044e720(float *param_1,float *param_2)

{
  float fVar1;
  
  _DAT_004ea6dc =
       _DAT_004cbb00 /
       (param_1[3] * param_1[3] +
       param_1[2] * param_1[2] + param_1[1] * param_1[1] + *param_1 * *param_1);
  _DAT_004ea6c4 = _DAT_004ea6dc * *param_1;
  _DAT_004ea6c8 = _DAT_004ea6dc * param_1[1];
  _DAT_004ea6bc = _DAT_004ea6dc * param_1[2];
  _DAT_004ea6b4 = _DAT_004ea6c4 * param_1[3];
  _DAT_004ea6c0 = _DAT_004ea6c8 * param_1[3];
  _DAT_004ea6d4 = _DAT_004ea6bc * param_1[3];
  _DAT_004ea6d8 = _DAT_004ea6c4 * *param_1;
  _DAT_004ea6ac = _DAT_004ea6c8 * *param_1;
  _DAT_004ea6d0 = _DAT_004ea6bc * *param_1;
  _DAT_004ea6b0 = _DAT_004ea6c8 * param_1[1];
  _DAT_004ea6cc = _DAT_004ea6bc * param_1[1];
  _DAT_004ea6b8 = _DAT_004ea6bc * param_1[2];
  *param_2 = _DAT_004cba94 - (_DAT_004ea6b8 + _DAT_004ea6b0);
  param_2[1] = _DAT_004ea6ac - _DAT_004ea6d4;
  fVar1 = _DAT_004ea6d0 + _DAT_004ea6c0;
  param_2[3] = 0.0;
  param_2[2] = fVar1;
  param_2[4] = _DAT_004ea6ac + _DAT_004ea6d4;
  param_2[5] = _DAT_004cba94 - (_DAT_004ea6b8 + _DAT_004ea6d8);
  fVar1 = _DAT_004ea6cc - _DAT_004ea6b4;
  param_2[7] = 0.0;
  param_2[6] = fVar1;
  param_2[8] = _DAT_004ea6d0 - _DAT_004ea6c0;
  param_2[9] = _DAT_004ea6cc + _DAT_004ea6b4;
  fVar1 = _DAT_004ea6b0 + _DAT_004ea6d8;
  param_2[0xb] = 0.0;
  param_2[0xc] = 0.0;
  param_2[0xd] = 0.0;
  param_2[0xe] = 0.0;
  fVar1 = _DAT_004cba94 - fVar1;
  param_2[0xf] = 1.0;
  param_2[10] = fVar1;
  return;
}


/* 0044e8c0 size=258 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0044e8c0: lifted from original x86 -> lt_lifted.c */


/* 0044e9d0 size=94 */

void __cdecl FUN_0044e9d0(float *param_1,float *param_2,undefined4 *param_3,undefined4 *param_4)

{
  float local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  FUN_0044e720(param_1,&local_40);
  *param_2 = local_40;
  param_2[1] = local_30;
  param_2[2] = local_20;
  *param_3 = local_3c;
  param_3[1] = local_2c;
  param_3[2] = local_1c;
  *param_4 = local_38;
  param_4[1] = local_28;
  param_4[2] = local_18;
  return;
}


/* 0044ea30 size=298 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0044ea30: lifted from original x86 -> lt_lifted.c */


/* 0044eb60 size=28 */

void * __fastcall FUN_0044eb60(void *param_1)

{
  FUN_00424310(param_1,0);
  *(undefined4 *)((int)param_1 + 8) = 0;
  *(undefined4 *)((int)param_1 + 0xc) = 0;
  return param_1;
}


/* 0044eb80 size=22 */

void __thiscall FUN_0044eb80(void *this,DWORD param_1)

{
  *(undefined4 *)((int)this + 0xc) = 0;
  *(DWORD *)((int)this + 8) = param_1;
  FUN_00424340(this);
  return;
}


/* 0044eba0 size=4 */

float10 __fastcall FUN_0044eba0(int param_1)

{
  return (float10)*(float *)(param_1 + 8);
}


/* 0044ebb0 size=120 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0044ebb0(LARGE_INTEGER *param_1)

{
  float fVar1;
  undefined4 extraout_ECX;
  float10 fVar2;
  ulonglong uVar3;
  
  if ((float)param_1[1].s.LowPart != _DAT_004cb524) {
    fVar1 = _DAT_004cba94 / (float)param_1[1].s.LowPart;
    uVar3 = thunk_FUN_00424350((uint *)param_1);
    if (fVar1 < (float)(uVar3 & 0xffffffff) * _DAT_004cb4e4 + *(float *)((int)param_1 + 0xc)) {
      fVar2 = (float10)FUN_004bc5aa(extraout_ECX);
      *(float *)((int)param_1 + 0xc) = (float)fVar2;
      FUN_00424340(param_1);
      return 1;
    }
  }
  return 0;
}


/* 0044ec30 size=33 */

undefined4 FUN_0044ec30(float *param_1,float *param_2,undefined4 *param_3,undefined4 *param_4)

{
  FUN_0043ce60(param_1,param_2,param_3,param_4);
  return 0;
}


/* 0044ee70 size=187 */

undefined4 FUN_0044ee70(float *param_1,float *param_2,float *param_3)

{
  float local_64;
  undefined4 local_60;
  undefined4 local_5c;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_0043cb90(param_2,param_3,&local_64,&local_58,&local_4c);
  local_40 = local_64;
  local_3c = local_58;
  local_38 = local_4c;
  local_30 = local_60;
  local_2c = local_54;
  local_28 = local_48;
  local_20 = local_5c;
  local_1c = local_50;
  local_18 = local_44;
  local_34 = 0;
  local_24 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0x3f800000;
  FUN_0043ce40(&local_40,param_1);
  return 0;
}


/* 0044eff0 size=145 */

undefined4 FUN_0044eff0(float *param_1,float *param_2,float param_3)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  float local_c0 [16];
  float local_80 [16];
  float local_40 [16];
  
  FUN_0043ce20(param_1,local_c0);
  FUN_0043d070(local_80,*param_2,param_2[1],param_2[2],param_3);
  FUN_0043d430(local_40,local_80,local_c0);
  pfVar2 = local_40;
  pfVar3 = local_c0;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar3 = pfVar3 + 1;
  }
  FUN_0043ce40(local_c0,param_1);
  return 0;
}


/* 0044f590 size=11 */

void FUN_0044f590(void)

{
  DAT_004ea6e0 = 0;
  return;
}


/* 0044f5b0 size=90 */

undefined4 __cdecl FUN_0044f5b0(int param_1,int param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  
  if (*(int *)(param_1 + 0x20) != *(int *)(param_2 + 0x20)) {
    *param_3 = param_1;
    return 0;
  }
  uVar2 = 0;
  if (*(int *)(param_1 + 0x20) != 0) {
    do {
      iVar1 = FUN_0044f5b0(*(int *)(*(int *)(param_1 + 0x1c) + uVar2 * 4),
                           *(int *)(*(int *)(param_2 + 0x1c) + uVar2 * 4),param_3);
      if (iVar1 == 0) {
        return 0;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_1 + 0x20));
  }
  return 1;
}


/* 0044f610 size=18 */

void __thiscall FUN_0044f610(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 4) = param_1;
  *(undefined4 *)this = 0;
  return;
}


/* 0044f640 size=45 */

void __fastcall FUN_0044f640(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *param_1;
  if (iVar2 == 0) {
    *param_1 = 0;
    return;
  }
  do {
    iVar1 = *(int *)(iVar2 + 4);
    if (iVar2 != 0) {
      (**(code **)(*(int *)param_1[1] + 8))(iVar2);
    }
    iVar2 = iVar1;
  } while (iVar1 != 0);
  *param_1 = 0;
  return;
}


/* 0044f670 size=195 */

byte * __thiscall FUN_0044f670(void *this,byte *param_1)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  bool bVar9;
  
  if ((param_1 != (byte *)0x0) && (*param_1 != 0)) {
    for (iVar2 = *(int *)this; iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
      pbVar3 = (byte *)(iVar2 + 8);
      pbVar8 = param_1;
      do {
        bVar1 = *pbVar3;
        bVar9 = bVar1 < *pbVar8;
        if (bVar1 != *pbVar8) {
LAB_0044f6bb:
          iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_0044f6c0;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar9 = bVar1 < pbVar8[1];
        if (bVar1 != pbVar8[1]) goto LAB_0044f6bb;
        pbVar3 = pbVar3 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_0044f6c0:
      if (iVar4 == 0) {
        return (byte *)(iVar2 + 8);
      }
    }
    uVar6 = 0xffffffff;
    pbVar3 = param_1;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      bVar1 = *pbVar3;
      pbVar3 = pbVar3 + 1;
    } while (bVar1 != 0);
    piVar5 = (int *)(**(code **)(**(int **)((int)this + 4) + 4))(~uVar6 + 0xb);
    if (piVar5 != (int *)0x0) {
      *piVar5 = ~uVar6 + 0xb;
      piVar5[1] = *(int *)this;
      *(int **)this = piVar5;
      uVar6 = 0xffffffff;
      do {
        pbVar3 = param_1;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pbVar3 = param_1 + 1;
        bVar1 = *param_1;
        param_1 = pbVar3;
      } while (bVar1 != 0);
      uVar6 = ~uVar6;
      pbVar3 = pbVar3 + -uVar6;
      pbVar8 = (byte *)(piVar5 + 2);
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar8 = *(undefined4 *)pbVar3;
        pbVar3 = pbVar3 + 4;
        pbVar8 = pbVar8 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar8 = *pbVar3;
        pbVar3 = pbVar3 + 1;
        pbVar8 = pbVar8 + 1;
      }
      return (byte *)(piVar5 + 2);
    }
  }
  return &DAT_004e4424;
}


/* 0044f740 size=25 */

undefined4 __thiscall FUN_0044f740(void *this,int param_1)

{
  if (*(int *)this == 0) {
    *(int *)((int)this + 4) = param_1;
    return 1;
  }
  return 0;
}


/* 0044f760 size=123 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0044f760(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    if (((uint)*(ushort *)(param_1 + 1) < *(uint *)(iVar1 + 0x16c)) &&
       ((uint)*(ushort *)(param_1 + 4) < *(uint *)(iVar1 + 0x16c))) {
      if (((uint)*(ushort *)((int)param_1 + 6) <
           *(uint *)(*(int *)((uint)*(ushort *)(param_1 + 1) * 0x20 + *(int *)(iVar1 + 0x168)) +
                    0x10)) &&
         ((((uint)*(ushort *)((int)param_1 + 0x12) <
            *(uint *)(*(int *)((uint)*(ushort *)(param_1 + 4) * 0x20 + *(int *)(iVar1 + 0x168)) +
                     0x10) && (_DAT_004cb524 <= (float)param_1[7])) &&
          ((float)param_1[7] <= _DAT_004cba94)))) {
        return 1;
      }
    }
  }
  return 0;
}


/* 0044f7e0 size=19 */

void __fastcall FUN_0044f7e0(undefined4 *param_1)

{
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  param_1[4] = 0;
  return;
}


/* 0044f800 size=29 */

void __fastcall FUN_0044f800(undefined4 *param_1)

{
  *param_1 = 0;
  *(undefined2 *)(param_1 + 1) = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


/* 0044f820 size=137 */

undefined4 * __fastcall FUN_0044f820(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cc810;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  if (param_1[1] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[1]);
    param_1[1] = 0;
    param_1[3] = 0;
  }
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  if (param_1[1] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[1]);
    param_1[1] = 0;
    param_1[3] = 0;
  }
  param_1[2] = 0;
  param_1[6] = 0;
  param_1[10] = 0;
  param_1[9] = 0;
  param_1[5] = 0;
  param_1[7] = &DAT_004e4424;
  param_1[0xb] = 1;
  return param_1;
}


/* 0044f8b0 size=69 */

void __fastcall FUN_0044f8b0(undefined4 *param_1)

{
  int iVar1;
  
  FUN_0044f900((int)param_1);
  iVar1 = param_1[1];
  *param_1 = &PTR_LAB_004cc810;
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    param_1[1] = 0;
    param_1[3] = 0;
  }
  param_1[2] = 0;
  return;
}


/* 0044f900 size=70 */

void __fastcall FUN_0044f900(int param_1)

{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined1 **)(param_1 + 0x1c) = &DAT_004e4424;
  iVar1 = *(int *)(param_1 + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(**(int **)(*(int *)(param_1 + 0x24) + 0x174) + 8))(iVar1);
    }
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}


/* 0044f950 size=23 */

void __fastcall FUN_0044f950(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = &DAT_004e4424;
  *(undefined1 *)(param_1 + 2) = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  return;
}


/* 0044f970 size=94 */

undefined4 * __fastcall FUN_0044f970(undefined4 *param_1)

{
  param_1[2] = &PTR_LAB_004cc880;
  param_1[3] = 0;
  param_1[4] = 0;
  FUN_004558b0(param_1 + 2,0,&DAT_004ecc58);
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[7] = &PTR_LAB_004cc850;
  param_1[8] = 0;
  param_1[9] = 0;
  FUN_00455a50(param_1 + 7,0,&DAT_004ecc58);
  param_1[8] = 0;
  param_1[9] = 0;
  *param_1 = &PTR_FUN_004cc840;
  FUN_0044fae0((int)param_1);
  return param_1;
}


/* 0044f9e0 size=30 */

undefined4 * __thiscall FUN_0044f9e0(void *this,byte param_1)

{
  FUN_0044fa70(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0044fa00 size=110 */

undefined4 * __thiscall FUN_0044fa00(void *this,undefined4 param_1,undefined4 param_2)

{
  *(undefined4 *)((int)this + 8) = &PTR_LAB_004cc880;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  FUN_004558b0((undefined4 *)((int)this + 8),0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x1c) = &PTR_LAB_004cc850;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  FUN_00455a50((undefined4 *)((int)this + 0x1c),0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined ***)this = &PTR_FUN_004cc840;
  FUN_0044fae0((int)this);
  *(undefined4 *)((int)this + 0x2c) = param_1;
  *(undefined4 *)((int)this + 0x18) = param_2;
  return this;
}


/* 0044fa70 size=101 */

void __fastcall FUN_0044fa70(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cc840;
  FUN_0044fc10((int)param_1);
  param_1[7] = &PTR_LAB_004cc850;
  if (param_1[8] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[8]);
    param_1[8] = 0;
  }
  param_1[9] = 0;
  param_1[2] = &PTR_LAB_004cc880;
  if (param_1[3] != 0) {
    (**(code **)(DAT_004ecc58 + 8))(param_1[3]);
    param_1[3] = 0;
  }
  param_1[4] = 0;
  return;
}


/* 0044fae0 size=231 */

void __fastcall FUN_0044fae0(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined **local_10;
  int local_c;
  int local_8;
  
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  local_10 = &PTR_LAB_004cc880;
  local_c = 0;
  local_8 = 0;
  FUN_004558b0(&local_10,0,&DAT_004ecc58);
  local_c = 0;
  local_8 = 0;
  FUN_004558b0(&local_10,0,&DAT_004ecc58);
  if (*(int *)(param_1 + 0xc) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  *(int *)(param_1 + 0x10) = local_8;
  if (local_8 == 0) {
    *(undefined4 *)(param_1 + 0x10) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  else {
    iVar1 = FUN_00456b70(&DAT_004ecc58,0,local_8);
    *(int *)(param_1 + 0xc) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x10) = 0;
    }
    else {
      uVar2 = 0;
      if (*(int *)(param_1 + 0x10) != 0) {
        iVar1 = 0;
        do {
          FUN_0044fbd0((void *)(*(int *)(param_1 + 0xc) + iVar1),(undefined4 *)(iVar1 + local_c));
          uVar2 = uVar2 + 1;
          iVar1 = iVar1 + 0x1c;
        } while (uVar2 < *(uint *)(param_1 + 0x10));
      }
    }
  }
  local_10 = &PTR_LAB_004cc880;
  if (local_c != 0) {
    FUN_00456e60(&DAT_004ecc58,local_c);
  }
  return;
}


/* 0044fbd0 size=55 */

void __thiscall FUN_0044fbd0(void *this,undefined4 *param_1)

{
  *(undefined4 *)this = *param_1;
  *(undefined4 *)((int)this + 4) = param_1[1];
  *(undefined4 *)((int)this + 8) = param_1[2];
  *(undefined4 *)((int)this + 0xc) = param_1[3];
  *(undefined4 *)((int)this + 0x10) = param_1[4];
  *(undefined4 *)((int)this + 0x14) = param_1[5];
  *(undefined4 *)((int)this + 0x18) = param_1[6];
  return;
}


/* 0044fc10 size=135 */

void __fastcall FUN_0044fc10(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = FUN_0044fda0(param_1);
  uVar4 = 0;
  if (*(int *)(param_1 + 0xc) != 0) {
    FUN_00456e60(*(int **)(iVar3 + 0x174),*(int *)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  *(undefined4 *)(param_1 + 0x10) = 0;
  iVar3 = FUN_0044fda0(param_1);
  piVar1 = *(int **)(iVar3 + 0x174);
  if (*(int *)(param_1 + 0x24) != 0) {
    do {
      puVar2 = *(undefined4 **)(*(int *)(param_1 + 0x20) + uVar4 * 4);
      if (puVar2 != (undefined4 *)0x0) {
        (**(code **)*puVar2)(0);
        (**(code **)(*piVar1 + 8))(puVar2);
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(param_1 + 0x24));
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    FUN_00456e60(piVar1,*(int *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  *(undefined4 *)(param_1 + 0x24) = 0;
  return;
}


/* 0044fce0 size=101 */

undefined4 __thiscall FUN_0044fce0(void *this,uint *param_1)

{
  int iVar1;
  uint uVar2;
  
  if (*(int *)(*(int *)((int)this + 0x2c) + 4) != 0) {
    iVar1 = FUN_0044fda0((int)this);
    if (*param_1 < *(uint *)(iVar1 + 0x78)) {
      uVar2 = 0;
      *(void **)(*(int *)(*(int *)((int)this + 0x2c) + 4) + *param_1 * 4) = this;
      *param_1 = *param_1 + 1;
      if (*(int *)((int)this + 0x24) != 0) {
        do {
          iVar1 = FUN_0044fce0(*(void **)(*(int *)((int)this + 0x20) + uVar2 * 4),param_1);
          if (iVar1 == 0) {
            return 0;
          }
          uVar2 = uVar2 + 1;
        } while (uVar2 < *(uint *)((int)this + 0x24));
      }
      return 1;
    }
  }
  return 0;
}


/* 0044fd50 size=70 */

undefined4 __thiscall FUN_0044fd50(void *this,int param_1)

{
  uint uVar1;
  
  *(int *)((int)this + 4) = param_1;
  if (*(int *)((int)this + 0x24) != *(int *)(param_1 + 0x20)) {
    return 0;
  }
  uVar1 = 0;
  if (*(int *)((int)this + 0x24) != 0) {
    do {
      FUN_0044fd50(*(void **)(*(int *)((int)this + 0x20) + uVar1 * 4),
                   *(int *)(*(int *)(param_1 + 0x1c) + uVar1 * 4));
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)((int)this + 0x24));
  }
  return 1;
}


/* 0044fda0 size=7 */

undefined4 __fastcall FUN_0044fda0(int param_1)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x2c) + 0x20);
}


/* 0044fdb0 size=94 */

undefined4 * __thiscall FUN_0044fdb0(void *this,undefined4 param_1)

{
  int *piVar1;
  
  piVar1 = (int *)((int)this + 0x28);
  *(undefined ***)((int)this + 8) = &PTR_LAB_004cc8bc;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  FUN_0044f970(piVar1);
  *(undefined ***)this = &PTR_FUN_004cc8b0;
  *(undefined4 *)((int)this + 0x20) = param_1;
  *(undefined1 **)((int)this + 0x24) = &DAT_004e4424;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 0x18) = 0xffffffff;
  *(undefined4 *)((int)this + 0x1c) = 200;
  *(int **)((int)this + 0x58) = piVar1;
  (**(code **)(*piVar1 + 8))(this);
  return this;
}


/* 0044fe10 size=30 */

undefined4 * __thiscall FUN_0044fe10(void *this,byte param_1)

{
  FUN_0044fe30(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0044fe30 size=76 */

void __fastcall FUN_0044fe30(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cc8b0;
  FUN_0044fe80((int)param_1);
  FUN_0044fa70(param_1 + 10);
  param_1[2] = &PTR_LAB_004cc8bc;
  if (param_1[3] != 0) {
    (**(code **)(DAT_004ecc58 + 8))(param_1[3]);
    param_1[3] = 0;
  }
  param_1[4] = 0;
  return;
}


/* 0044fe80 size=101 */

void __fastcall FUN_0044fe80(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)(**(int **)(*(int *)(param_1 + 0x20) + 0x174) + 8))(*(int *)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    (**(code **)(**(int **)(*(int *)(param_1 + 0x20) + 0x174) + 8))(*(int *)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  *(undefined4 *)(param_1 + 0x10) = 0;
  FUN_0044fc10(param_1 + 0x28);
  FUN_0044ff50(param_1);
  return;
}


/* 0044fef0 size=45 */

void __thiscall FUN_0044fef0(void *this,void *param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_004511d0(param_1,*(byte **)((int)this + 0x24));
  *(undefined4 *)((int)this + 0x24) = uVar1;
  *(void **)((int)this + 0x20) = param_1;
  FUN_0044fd50(*(void **)((int)this + 0x58),*(int *)((int)param_1 + 0x2c4));
  return;
}


/* 0044ff50 size=51 */

void __fastcall FUN_0044ff50(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0x58);
  if (puVar1 == (undefined4 *)0x0) {
    *(int *)(param_1 + 0x58) = param_1 + 0x28;
    return;
  }
  if (puVar1 != (undefined4 *)(param_1 + 0x28)) {
    if (puVar1 == (undefined4 *)0x0) {
      *(int *)(param_1 + 0x58) = param_1 + 0x28;
      return;
    }
    (**(code **)*puVar1)(1);
  }
  *(int *)(param_1 + 0x58) = param_1 + 0x28;
  return;
}


/* 0044ff90 size=13 */

int __thiscall FUN_0044ff90(void *this,int param_1)

{
  FUN_0044ffa0(this,param_1);
  return;
}


/* 0044ffa0 size=117 */

undefined4 __thiscall FUN_0044ffa0(void *this,int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uStack00000000;
  
  if ((param_1 == 0) && (*(int *)((int)this + 4) != 0)) {
    return 1;
  }
  if (*(int *)((int)this + 4) != 0) {
    (**(code **)(**(int **)(*(int *)((int)this + 0x20) + 0x174) + 8))(*(int *)((int)this + 4));
  }
  iVar1 = (**(code **)(**(int **)(*(int *)((int)this + 0x20) + 0x174) + 4))
                    (*(int *)(*(int *)((int)this + 0x20) + 0x78) << 2);
  *(int *)((int)this + 4) = iVar1;
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = FUN_0044fce0(*(void **)((int)this + 0x58),(uint *)&uStack00000000);
  return uVar2;
}


