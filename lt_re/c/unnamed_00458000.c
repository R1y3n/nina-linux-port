/* lithtech.exe decompilation - unnamed_00458000 */
#include "ghidra_types.h"

/* 00458070 size=339 */

undefined4 __thiscall FUN_00458070(void *this,int *param_1)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  int unaff_EBX;
  uint uVar4;
  int *piStack_4;
  
  uVar4 = 0;
  piVar1 = *(int **)((int)this + 0x174);
  if (*(int *)((int)this + 0x4c) != 0) {
    do {
      pvVar3 = *(void **)(*(int *)((int)this + 0x48) + uVar4 * 4);
      if (pvVar3 != (void *)0x0) {
        FUN_0045a810(pvVar3,0);
        (**(code **)(*piVar1 + 8))(pvVar3);
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)((int)this + 0x4c));
  }
  FUN_00455a50((void *)((int)this + 0x44),0,piVar1);
  (**(code **)(*param_1 + 8))(&piStack_4,4);
  iVar2 = FUN_00455a50((void *)((int)this + 0x44),unaff_EBX,*(int **)((int)this + 0x174));
  if (iVar2 == 0) {
    return 0;
  }
  uVar4 = 0;
  if (*(int *)((int)this + 0x4c) != 0) {
    do {
      uVar4 = uVar4 + 1;
      *(undefined4 *)(*(int *)((int)this + 0x48) + -4 + uVar4 * 4) = 0;
    } while (uVar4 < *(uint *)((int)this + 0x4c));
  }
  uVar4 = 0;
  if (*(int *)((int)this + 0x4c) != 0) {
    do {
      pvVar3 = (void *)(**(code **)(**(int **)((int)this + 0x174) + 4))(0x28);
      if (pvVar3 != (void *)0x0) {
        FUN_00450640(pvVar3,this);
      }
      *(void **)(*(int *)((int)this + 0x48) + uVar4 * 4) = pvVar3;
      if ((pvVar3 == (void *)0x0) || (iVar2 = FUN_00457c80(pvVar3,piStack_4), iVar2 == 0)) {
        piVar1 = *(int **)((int)this + 0x174);
        uVar4 = 0;
        if (*(int *)((int)this + 0x4c) != 0) {
          do {
            iVar2 = *(int *)(*(int *)((int)this + 0x48) + uVar4 * 4);
            if (iVar2 != 0) {
              FUN_004506c0(iVar2);
              (**(code **)(*piVar1 + 8))(iVar2);
            }
            uVar4 = uVar4 + 1;
          } while (uVar4 < *(uint *)((int)this + 0x4c));
        }
        if (*(int *)((int)this + 0x48) != 0) {
          FUN_00456e60(piVar1,*(int *)((int)this + 0x48));
          *(undefined4 *)((int)this + 0x48) = 0;
        }
        *(undefined4 *)((int)this + 0x4c) = 0;
        return 0;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)((int)this + 0x4c));
  }
  return 1;
}


/* 004590d0 size=154 */

undefined4 __thiscall FUN_004590d0(void *this,byte *param_1,int *param_2)

{
  void *this_00;
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  int local_38;
  undefined4 local_34 [13];
  
  FUN_0045a970(local_34);
  bVar1 = LayoutDB_459060(this,param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    return 0x4d;
  }
  iVar2 = FUN_0045aa70(local_34,&local_38);
  if (iVar2 != 0) {
    this_00 = (void *)((int)this + 0x17c);
    iVar2 = FUN_004b8810(this_00,param_2,local_38);
    if (iVar2 == 0) {
      return 0x43;
    }
    *(void **)((int)this + 0x174) = this_00;
    FUN_0044f740((void *)((int)this + 0x84),(int)this_00);
    DAT_004ea6e4 = DAT_004ea6e4 + *(int *)((int)this + 0x18c);
  }
  return 0;
}


/* 00459170 size=34 */

void __fastcall FUN_00459170(int param_1)

{
  FUN_00430df0(*(undefined **)(param_1 + 4));
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}


/* 004591a0 size=296 */

void __fastcall FUN_004591a0(int param_1)

{
  void *this;
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined *puVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  undefined4 *local_10;
  int local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar2 = *(undefined4 **)(param_1 + 0x14);
  this = (void *)(param_1 + 0x10);
  local_10 = (undefined4 *)*puVar2;
  if (((*(int *)(param_1 + 0x1c) == 0) ||
      (piVar5 = (int *)FUN_004599d0(this,&local_c), local_10 != (undefined4 *)*piVar5)) ||
     (puVar2 != *(undefined4 **)(param_1 + 0x14))) {
    while (local_10 != puVar2) {
      puVar6 = (undefined4 *)FUN_004592d0(&local_10,&local_c);
      FUN_00459e20(this,&local_4,(int *)*puVar6);
    }
  }
  else {
    FUN_0045a340((int *)(*(undefined4 **)(param_1 + 0x14))[1]);
    *(undefined **)(*(int *)(param_1 + 0x14) + 4) = DAT_004ea6ec;
    *(undefined4 *)(param_1 + 0x1c) = 0;
    *(undefined4 *)*(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x14);
    *(int *)(*(int *)(param_1 + 0x14) + 8) = *(int *)(param_1 + 0x14);
    FUN_004599d0(this,&local_8);
  }
  FUN_00430df0(*(undefined **)(param_1 + 0x14));
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  FUN_004b9b4f(&local_10);
  puVar4 = DAT_004ea6ec;
  DAT_004ea6e8 = DAT_004ea6e8 + -1;
  puVar7 = (undefined *)0x0;
  if (DAT_004ea6e8 == 0) {
    DAT_004ea6ec = (undefined *)0x0;
    puVar7 = puVar4;
  }
  FUN_004b9beb();
  if (puVar7 != (undefined *)0x0) {
    FUN_00430df0(puVar7);
  }
  iVar3 = *(int *)(param_1 + 4);
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 != '\0') && (cVar1 != -1)) {
      *(char *)(iVar3 + -1) = cVar1 + -1;
      *(undefined4 *)(param_1 + 4) = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined4 *)(param_1 + 0xc) = 0;
      return;
    }
    FUN_00430df0((char *)(iVar3 + -1));
  }
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}


/* 004592d0 size=86 */

int __thiscall FUN_004592d0(void *this,int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar1 = *(int *)this;
  puVar2 = *(undefined4 **)(iVar1 + 8);
  if (puVar2 != DAT_004ea6ec) {
    for (puVar3 = (undefined4 *)*puVar2; puVar3 != DAT_004ea6ec; puVar3 = (undefined4 *)*puVar3) {
      puVar2 = puVar3;
    }
    *(undefined4 **)this = puVar2;
    *param_1 = iVar1;
    return;
  }
  iVar4 = *(int *)(iVar1 + 4);
  if (*(int *)this == *(int *)(iVar4 + 8)) {
    do {
      *(int *)this = iVar4;
      iVar4 = *(int *)(iVar4 + 4);
    } while (*(int *)this == *(int *)(iVar4 + 8));
  }
  if (*(int *)(*(int *)this + 8) != iVar4) {
    *(int *)this = iVar4;
  }
  *param_1 = iVar1;
  return;
}


/* 00459330 size=412 */

undefined4 * __thiscall FUN_00459330(void *this,undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  
  puVar5 = *(undefined4 **)((int)this + 8);
  iVar1 = *(int *)((int)this + 4);
  iVar6 = (int)param_1 - iVar1 >> 2;
  if (*(int *)((int)this + 0xc) - (int)puVar5 >> 2 != 0) {
    if ((int)puVar5 - (int)param_1 >> 2 == 0) {
      FUN_00459b50(param_1,puVar5,param_1 + 1);
      FUN_00459b80(*(undefined4 **)((int)this + 8),
                   1 - ((int)*(undefined4 **)((int)this + 8) - (int)param_1 >> 2),param_2);
      puVar5 = *(undefined4 **)((int)this + 8);
      for (; param_1 != puVar5; param_1 = param_1 + 1) {
        *param_1 = *param_2;
      }
    }
    else {
      FUN_00459b50(puVar5 + -1,puVar5,puVar5);
      puVar5 = *(undefined4 **)((int)this + 8);
      puVar7 = puVar5;
      while (param_1 != puVar7 + -1) {
        puVar5 = puVar5 + -1;
        *puVar5 = puVar7[-2];
        puVar7 = puVar7 + -1;
      }
      puVar5 = param_1 + 1;
      for (; param_1 != puVar5; param_1 = param_1 + 1) {
        *param_1 = *param_2;
      }
    }
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 4;
    return (undefined4 *)(*(int *)((int)this + 4) + iVar6 * 4);
  }
  if ((iVar1 == 0) || (uVar4 = (int)puVar5 - iVar1 >> 2, uVar4 < 2)) {
    uVar4 = 1;
  }
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = (int)puVar5 - iVar1 >> 2;
  }
  iVar1 = iVar1 + uVar4;
  iVar2 = iVar1;
  if (iVar1 < 0) {
    iVar2 = 0;
  }
  puVar3 = (undefined4 *)FUN_00430de0(iVar2 * 4);
  puVar7 = puVar3;
  for (puVar5 = *(undefined4 **)((int)this + 4); puVar5 != param_1; puVar5 = puVar5 + 1) {
    FUN_0048ce90(puVar7,puVar5);
    puVar7 = puVar7 + 1;
  }
  FUN_0048ce90(puVar7,param_2);
  FUN_00459b50(param_1,*(undefined4 **)((int)this + 8),puVar7 + 1);
  FUN_004594f0();
  FUN_00430df0(*(undefined **)((int)this + 4));
  *(undefined4 **)((int)this + 0xc) = puVar3 + iVar1;
  iVar1 = FUN_004594d0((int)this);
  *(undefined4 **)((int)this + 4) = puVar3;
  *(undefined4 **)((int)this + 8) = puVar3 + iVar1 + 1;
  return puVar3 + iVar6;
}


/* 004594d0 size=19 */

int __fastcall FUN_004594d0(int param_1)

{
  if (*(int *)(param_1 + 4) == 0) {
    return 0;
  }
  return *(int *)(param_1 + 8) - *(int *)(param_1 + 4) >> 2;
}


/* 004594f0 size=3 */

void FUN_004594f0(void)

{
  return;
}


/* 00459500 size=245 */

/* FUN_00459500: lifted from original x86 -> lt_lifted.c */


/* 00459600 size=176 */

void __thiscall FUN_00459600(void *this,undefined4 *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  byte *pbVar9;
  bool bVar10;
  bool bVar11;
  
  puVar8 = *(undefined4 **)((int)this + 4);
  puVar5 = (undefined4 *)puVar8[1];
  if ((undefined4 *)puVar8[1] != DAT_004ea6f0) {
    do {
      uVar2 = FUN_0045a710(puVar5 + 3,param_2);
      if ((int)uVar2 < 0) {
        puVar6 = (undefined4 *)puVar5[2];
      }
      else {
        puVar6 = (undefined4 *)*puVar5;
        puVar8 = puVar5;
      }
      puVar5 = puVar6;
    } while (puVar6 != DAT_004ea6f0);
  }
  if (puVar8 != *(undefined4 **)((int)this + 4)) {
    uVar2 = puVar8[5];
    pbVar9 = (byte *)puVar8[4];
    if (pbVar9 == (byte *)0x0) {
      pbVar9 = &DAT_004cc108;
    }
    uVar1 = *(uint *)(param_2 + 8);
    uVar4 = uVar1;
    if (uVar2 <= uVar1) {
      uVar4 = uVar2;
    }
    bVar10 = false;
    iVar3 = 0;
    bVar11 = true;
    pbVar7 = *(byte **)(param_2 + 4);
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      bVar10 = *pbVar7 < *pbVar9;
      bVar11 = *pbVar7 == *pbVar9;
      pbVar7 = pbVar7 + 1;
      pbVar9 = pbVar9 + 1;
    } while (bVar11);
    if (!bVar11) {
      iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
    }
    if (((iVar3 != 0) || (uVar2 <= uVar1)) && (-1 < iVar3)) {
      *param_1 = puVar8;
      return;
    }
  }
  *param_1 = *(undefined4 **)((int)this + 4);
  return;
}


/* 004596b0 size=376 */

/* FUN_004596b0: lifted from original x86 -> lt_lifted.c */


/* 00459830 size=168 */

/* FUN_00459830: lifted from original x86 -> lt_lifted.c */


/* 004598e0 size=231 */

void __fastcall FUN_004598e0(void *param_1)

{
  int *piVar1;
  int *piVar2;
  int *local_8;
  undefined4 local_4;
  
  piVar1 = *(int **)((int)param_1 + 4);
  local_8 = (int *)*piVar1;
  piVar2 = local_8;
  if (*(int *)((int)param_1 + 0xc) == 0) {
    while (local_8 = piVar2, piVar2 != piVar1) {
      FUN_00459b00((int *)&local_8);
      FUN_00459e20(param_1,&local_4,piVar2);
      piVar2 = local_8;
    }
  }
  else {
    piVar2 = (int *)piVar1[1];
    if ((int *)piVar1[1] != DAT_004ea6ec) {
      do {
        FUN_0045a340((int *)piVar2[2]);
        piVar1 = (int *)*piVar2;
        FUN_0045a6b0(piVar2 + 3,0);
        FUN_00430df0((undefined *)piVar2);
        piVar2 = piVar1;
      } while (piVar1 != DAT_004ea6ec);
    }
    *(int **)(*(int *)((int)param_1 + 4) + 4) = DAT_004ea6ec;
    *(undefined4 *)((int)param_1 + 0xc) = 0;
    *(undefined4 *)*(undefined4 *)((int)param_1 + 4) = *(undefined4 *)((int)param_1 + 4);
    *(int *)(*(int *)((int)param_1 + 4) + 8) = *(int *)((int)param_1 + 4);
  }
  FUN_00430df0(*(undefined **)((int)param_1 + 4));
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)((int)param_1 + 0xc) = 0;
  FUN_004b9b4f(&local_8);
  piVar1 = DAT_004ea6ec;
  DAT_004ea6e8 = DAT_004ea6e8 + -1;
  piVar2 = (int *)0x0;
  if (DAT_004ea6e8 == 0) {
    DAT_004ea6ec = (int *)0x0;
    piVar2 = piVar1;
  }
  FUN_004b9beb();
  if (piVar2 != (int *)0x0) {
    FUN_00430df0((undefined *)piVar2);
  }
  return;
}


/* 004599d0 size=14 */

int __thiscall FUN_004599d0(void *this,undefined4 *param_1)

{
  *param_1 = **(undefined4 **)((int)this + 4);
  return;
}


/* 004599e0 size=279 */

void * __thiscall FUN_004599e0(void *this,uint param_1,uint param_2)

{
  char cVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  char *pcVar7;
  char *pcVar8;
  
  if (*(uint *)((int)this + 8) < param_1) {
    FUN_004b9a1c();
  }
  pcVar7 = *(char **)((int)this + 4);
  if (((pcVar7 != (char *)0x0) && (cVar1 = pcVar7[-1], cVar1 != '\0')) && (cVar1 != -1)) {
    pcVar7[-1] = cVar1 + -1;
    uVar4 = 0xffffffff;
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
    pcVar8 = pcVar7;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4 - 1;
    uVar3 = FUN_0042fe50(this,uVar4,'\x01');
    if ((char)uVar3 != '\0') {
      pcVar8 = *(char **)((int)this + 4);
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar5 = uVar4 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar8 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar8 = pcVar8 + 1;
      }
      FUN_0042fe30(this,uVar4);
    }
  }
  uVar4 = *(int *)((int)this + 8) - param_1;
  if (uVar4 < param_2) {
    param_2 = uVar4;
  }
  if (param_2 == 0) {
    return this;
  }
  puVar6 = (undefined4 *)(*(int *)((int)this + 4) + param_1);
  FUN_004bab10(puVar6,(undefined4 *)((int)puVar6 + param_2),uVar4 - param_2);
  uVar4 = *(int *)((int)this + 8) - param_2;
  if (0xfffffffd < uVar4) {
    FUN_004b97f0();
  }
  puVar2 = *(undefined1 **)((int)this + 4);
  if (((puVar2 == (undefined1 *)0x0) || (cVar1 = puVar2[-1], cVar1 == '\0')) || (cVar1 == -1)) {
    if (uVar4 == 0) {
      if (puVar2 == (undefined1 *)0x0) {
        return this;
      }
      *(undefined4 *)((int)this + 8) = 0;
      *puVar2 = 0;
      return this;
    }
    if (uVar4 <= *(uint *)((int)this + 0xc)) goto LAB_00459ae4;
  }
  else if (uVar4 == 0) {
    puVar2[-1] = cVar1 + -1;
    FUN_00414100(this,'\0');
    return this;
  }
  FUN_0042ff80(uVar4);
LAB_00459ae4:
  *(uint *)((int)this + 8) = uVar4;
  *(undefined1 *)(uVar4 + *(int *)((int)this + 4)) = 0;
  return this;
}


/* 00459b00 size=67 */

void __fastcall FUN_00459b00(int *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = *(undefined4 **)(*param_1 + 8);
  if (puVar1 != DAT_004ea6ec) {
    for (puVar2 = (undefined4 *)*puVar1; puVar2 != DAT_004ea6ec; puVar2 = (undefined4 *)*puVar2) {
      puVar1 = puVar2;
    }
    *param_1 = (int)puVar1;
    return;
  }
  iVar3 = *(int *)(*param_1 + 4);
  if (*param_1 == *(int *)(iVar3 + 8)) {
    do {
      *param_1 = iVar3;
      iVar3 = *(int *)(iVar3 + 4);
    } while (*param_1 == *(int *)(iVar3 + 8));
  }
  if (*(int *)(*param_1 + 8) != iVar3) {
    *param_1 = iVar3;
  }
  return;
}


/* 00459b50 size=46 */

undefined4 * FUN_00459b50(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_1 == param_2) {
    return param_3;
  }
  do {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *param_1;
    }
    param_1 = param_1 + 1;
    param_3 = param_3 + 1;
  } while (param_1 != param_2);
  return param_3;
}


/* 00459b80 size=37 */

void FUN_00459b80(undefined4 *param_1,int param_2,undefined4 *param_3)

{
  if (param_2 != 0) {
    do {
      if (param_1 != (undefined4 *)0x0) {
        *param_1 = *param_3;
      }
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}


/* 00459bb0 size=619 */

void __thiscall
FUN_00459bb0(void *this,undefined4 *param_1,int param_2,int *param_3,undefined1 *param_4)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  
  piVar3 = (int *)FUN_00430de0(0x30);
  piVar3[1] = (int)param_3;
  piVar3[0xb] = 0;
  *piVar3 = DAT_004ea6f0;
  piVar3[2] = DAT_004ea6f0;
  FUN_0045a570(piVar3 + 3,param_4);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if ((param_3 != *(int **)((int)this + 4)) && (param_2 == DAT_004ea6f0)) {
    uVar4 = FUN_0045a710(param_4,(int)(param_3 + 3));
    if (-1 < (int)uVar4) {
      param_3[2] = (int)piVar3;
      if (param_3 == *(int **)(*(int *)((int)this + 4) + 8)) {
        *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
      }
      goto LAB_00459c44;
    }
  }
  *param_3 = (int)piVar3;
  piVar5 = *(int **)((int)this + 4);
  if (param_3 == piVar5) {
    piVar5[1] = (int)piVar3;
    *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
  }
  else if (param_3 == (int *)*piVar5) {
    *piVar5 = (int)piVar3;
  }
LAB_00459c44:
  piVar5 = piVar3;
  if (piVar3 != *(int **)(*(int *)((int)this + 4) + 4)) {
    do {
      piVar6 = (int *)piVar5[1];
      if (piVar6[0xb] != 0) break;
      piVar7 = *(int **)piVar6[1];
      if (piVar6 == piVar7) {
        iVar1 = ((undefined4 *)piVar6[1])[2];
        if (*(int *)(iVar1 + 0x2c) == 0) {
          piVar6[0xb] = 1;
          *(undefined4 *)(iVar1 + 0x2c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
          piVar5 = *(int **)(piVar5[1] + 4);
        }
        else {
          if (piVar5 == (int *)piVar6[2]) {
            piVar5 = (int *)piVar6[2];
            piVar6[2] = *piVar5;
            if (*piVar5 != DAT_004ea6f0) {
              *(int **)(*piVar5 + 4) = piVar6;
            }
            piVar5[1] = piVar6[1];
            if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int **)(*(int *)((int)this + 4) + 4) = piVar5;
            }
            else {
              piVar7 = (int *)piVar6[1];
              if (piVar6 == (int *)*piVar7) {
                *piVar7 = (int)piVar5;
              }
              else {
                piVar7[2] = (int)piVar5;
              }
            }
            *piVar5 = (int)piVar6;
            piVar6[1] = (int)piVar5;
            piVar5 = piVar6;
          }
          *(undefined4 *)(piVar5[1] + 0x2c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
          piVar6 = *(int **)(piVar5[1] + 4);
          piVar7 = (int *)*piVar6;
          *piVar6 = piVar7[2];
          if (piVar7[2] != DAT_004ea6f0) {
            *(int **)(piVar7[2] + 4) = piVar6;
          }
          piVar7[1] = piVar6[1];
          if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
            *(int **)(*(int *)((int)this + 4) + 4) = piVar7;
            piVar7[2] = (int)piVar6;
          }
          else {
            piVar2 = (int *)piVar6[1];
            if (piVar6 == (int *)piVar2[2]) {
              piVar2[2] = (int)piVar7;
              piVar7[2] = (int)piVar6;
            }
            else {
              *piVar2 = (int)piVar7;
              piVar7[2] = (int)piVar6;
            }
          }
LAB_00459df2:
          piVar6[1] = (int)piVar7;
        }
      }
      else {
        if (piVar7[0xb] != 0) {
          if (piVar5 == (int *)*piVar6) {
            iVar1 = *piVar6;
            *piVar6 = *(int *)(iVar1 + 8);
            if (*(int *)(iVar1 + 8) != DAT_004ea6f0) {
              *(int **)(*(int *)(iVar1 + 8) + 4) = piVar6;
            }
            *(int *)(iVar1 + 4) = piVar6[1];
            if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int *)(*(int *)((int)this + 4) + 4) = iVar1;
            }
            else {
              piVar5 = (int *)piVar6[1];
              if (piVar6 == (int *)piVar5[2]) {
                piVar5[2] = iVar1;
              }
              else {
                *piVar5 = iVar1;
              }
            }
            *(int **)(iVar1 + 8) = piVar6;
            piVar6[1] = iVar1;
            piVar5 = piVar6;
          }
          *(undefined4 *)(piVar5[1] + 0x2c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
          piVar6 = *(int **)(piVar5[1] + 4);
          piVar7 = (int *)piVar6[2];
          piVar6[2] = *piVar7;
          if (*piVar7 != DAT_004ea6f0) {
            *(int **)(*piVar7 + 4) = piVar6;
          }
          piVar7[1] = piVar6[1];
          if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
            *(int **)(*(int *)((int)this + 4) + 4) = piVar7;
          }
          else {
            piVar2 = (int *)piVar6[1];
            if (piVar6 == (int *)*piVar2) {
              *piVar2 = (int)piVar7;
            }
            else {
              piVar2[2] = (int)piVar7;
            }
          }
          *piVar7 = (int)piVar6;
          goto LAB_00459df2;
        }
        piVar6[0xb] = 1;
        piVar7[0xb] = 1;
        *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
        piVar5 = *(int **)(piVar5[1] + 4);
      }
    } while (piVar5 != *(int **)(*(int *)((int)this + 4) + 4));
  }
  *(undefined4 *)(*(int *)(*(int *)((int)this + 4) + 4) + 0x2c) = 1;
  *param_1 = piVar3;
  return;
}


/* 00459e20 size=1066 */

void __thiscall FUN_00459e20(void *this,undefined4 *param_1,int *param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int *piVar9;
  int *piVar10;
  int *local_c;
  undefined1 local_4 [4];
  
  piVar4 = param_2;
  FUN_00459b00((int *)&param_2);
  piVar10 = (int *)*piVar4;
  piVar6 = piVar4 + 2;
  local_c = piVar4;
  piVar9 = piVar6;
  if (piVar10 == DAT_004ea6ec) {
    piVar10 = (int *)*piVar6;
  }
  else {
    piVar2 = (int *)*piVar6;
    if (piVar2 != DAT_004ea6ec) {
      local_c = piVar2;
      for (piVar9 = (int *)*piVar2; piVar9 != DAT_004ea6ec; piVar9 = (int *)*piVar9) {
        local_c = piVar9;
      }
      piVar10 = (int *)local_c[2];
      piVar9 = local_c + 2;
    }
  }
  piVar2 = local_c;
  FUN_004b9b4f(local_4);
  if (local_c == piVar4) {
    piVar10[1] = local_c[1];
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar4) {
      *(int **)(*(int *)((int)this + 4) + 4) = piVar10;
    }
    else {
      piVar9 = (int *)piVar4[1];
      if ((int *)*piVar9 == piVar4) {
        *piVar9 = (int)piVar10;
      }
      else {
        piVar9[2] = (int)piVar10;
      }
    }
    piVar9 = *(int **)((int)this + 4);
    if ((int *)*piVar9 == piVar4) {
      if ((int *)*piVar6 == DAT_004ea6ec) {
        *piVar9 = piVar4[1];
      }
      else {
        piVar6 = piVar10;
        if ((int *)*piVar10 != DAT_004ea6ec) {
          piVar2 = (int *)*piVar10;
          do {
            piVar6 = piVar2;
            piVar2 = (int *)*piVar6;
          } while ((int *)*piVar6 != DAT_004ea6ec);
        }
        *piVar9 = (int)piVar6;
      }
    }
    if (*(int **)(*(int *)((int)this + 4) + 8) == piVar4) {
      if ((int *)*piVar4 == DAT_004ea6ec) {
        piVar6 = (int *)piVar4[1];
      }
      else {
        piVar9 = (int *)piVar10[2];
        piVar6 = piVar10;
        while (piVar4 = piVar9, piVar4 != DAT_004ea6ec) {
          piVar6 = piVar4;
          piVar9 = (int *)piVar4[2];
        }
      }
      *(int **)(*(int *)((int)this + 4) + 8) = piVar6;
    }
  }
  else {
    *(int **)(*piVar4 + 4) = local_c;
    *local_c = *piVar4;
    if (local_c == (int *)*piVar6) {
      piVar10[1] = (int)local_c;
    }
    else {
      piVar10[1] = local_c[1];
      *(int **)local_c[1] = piVar10;
      *piVar9 = *piVar6;
      *(int **)(*piVar6 + 4) = local_c;
    }
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar4) {
      *(int **)(*(int *)((int)this + 4) + 4) = local_c;
    }
    else {
      piVar6 = (int *)piVar4[1];
      if ((int *)*piVar6 == piVar4) {
        *piVar6 = (int)local_c;
      }
      else {
        piVar6[2] = (int)local_c;
      }
    }
    local_c = piVar4;
    piVar2[1] = piVar4[1];
    iVar3 = piVar2[7];
    piVar2[7] = piVar4[7];
    piVar4[7] = iVar3;
  }
  if (local_c[7] == 1) {
    if (piVar10 != *(int **)(*(int *)((int)this + 4) + 4)) {
      do {
        if (piVar10[7] != 1) break;
        piVar6 = *(int **)piVar10[1];
        if (piVar10 == piVar6) {
          piVar6 = (int *)((undefined4 *)piVar10[1])[2];
          if (piVar6[7] == 0) {
            piVar6[7] = 1;
            *(undefined4 *)(piVar10[1] + 0x1c) = 0;
            iVar3 = piVar10[1];
            piVar6 = *(int **)(iVar3 + 8);
            *(int *)(iVar3 + 8) = *piVar6;
            if ((int *)*piVar6 != DAT_004ea6ec) {
              ((int *)*piVar6)[1] = iVar3;
            }
            piVar6[1] = *(int *)(iVar3 + 4);
            if (iVar3 == *(int *)(*(int *)((int)this + 4) + 4)) {
              *(int **)(*(int *)((int)this + 4) + 4) = piVar6;
            }
            else {
              piVar9 = *(int **)(iVar3 + 4);
              if (iVar3 == *piVar9) {
                *piVar9 = (int)piVar6;
              }
              else {
                piVar9[2] = (int)piVar6;
              }
            }
            *piVar6 = iVar3;
            *(int **)(iVar3 + 4) = piVar6;
            piVar6 = *(int **)(piVar10[1] + 8);
          }
          if ((*(int *)(*piVar6 + 0x1c) != 1) || (*(int *)(piVar6[2] + 0x1c) != 1)) {
            if (*(int *)(piVar6[2] + 0x1c) == 1) {
              *(undefined4 *)(*piVar6 + 0x1c) = 1;
              iVar3 = *piVar6;
              piVar6[7] = 0;
              *piVar6 = *(int *)(iVar3 + 8);
              if (*(int **)(iVar3 + 8) != DAT_004ea6ec) {
                (*(int **)(iVar3 + 8))[1] = (int)piVar6;
              }
              *(int *)(iVar3 + 4) = piVar6[1];
              if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int *)(*(int *)((int)this + 4) + 4) = iVar3;
              }
              else {
                piVar9 = (int *)piVar6[1];
                if (piVar6 == (int *)piVar9[2]) {
                  piVar9[2] = iVar3;
                }
                else {
                  *piVar9 = iVar3;
                }
              }
              *(int **)(iVar3 + 8) = piVar6;
              piVar6[1] = iVar3;
              piVar6 = *(int **)(piVar10[1] + 8);
            }
            piVar6[7] = *(int *)(piVar10[1] + 0x1c);
            *(undefined4 *)(piVar10[1] + 0x1c) = 1;
            *(undefined4 *)(piVar6[2] + 0x1c) = 1;
            puVar7 = (undefined4 *)piVar10[1];
            puVar8 = (undefined4 *)puVar7[2];
            puVar7[2] = *puVar8;
            if ((int *)*puVar8 != DAT_004ea6ec) {
              ((int *)*puVar8)[1] = (int)puVar7;
            }
            puVar8[1] = puVar7[1];
            if (puVar7 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar8;
              *puVar8 = puVar7;
            }
            else {
              piVar6 = (int *)puVar7[1];
              if (puVar7 == (undefined4 *)*piVar6) {
                *piVar6 = (int)puVar8;
                *puVar8 = puVar7;
              }
              else {
                piVar6[2] = (int)puVar8;
                *puVar8 = puVar7;
              }
            }
            goto LAB_0045a1e6;
          }
        }
        else {
          if (piVar6[7] == 0) {
            piVar6[7] = 1;
            *(undefined4 *)(piVar10[1] + 0x1c) = 0;
            piVar6 = (int *)piVar10[1];
            iVar3 = *piVar6;
            *piVar6 = *(int *)(iVar3 + 8);
            if (*(int **)(iVar3 + 8) != DAT_004ea6ec) {
              (*(int **)(iVar3 + 8))[1] = (int)piVar6;
            }
            *(int *)(iVar3 + 4) = piVar6[1];
            if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int *)(*(int *)((int)this + 4) + 4) = iVar3;
            }
            else {
              piVar9 = (int *)piVar6[1];
              if (piVar6 == (int *)piVar9[2]) {
                piVar9[2] = iVar3;
              }
              else {
                *piVar9 = iVar3;
              }
            }
            *(int **)(iVar3 + 8) = piVar6;
            piVar6[1] = iVar3;
            piVar6 = *(int **)piVar10[1];
          }
          if ((*(int *)(piVar6[2] + 0x1c) != 1) || (*(int *)(*piVar6 + 0x1c) != 1)) {
            if (*(int *)(*piVar6 + 0x1c) == 1) {
              *(undefined4 *)(piVar6[2] + 0x1c) = 1;
              piVar9 = (int *)piVar6[2];
              piVar6[7] = 0;
              piVar6[2] = *piVar9;
              if ((int *)*piVar9 != DAT_004ea6ec) {
                ((int *)*piVar9)[1] = (int)piVar6;
              }
              piVar9[1] = piVar6[1];
              if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int **)(*(int *)((int)this + 4) + 4) = piVar9;
              }
              else {
                piVar4 = (int *)piVar6[1];
                if (piVar6 == (int *)*piVar4) {
                  *piVar4 = (int)piVar9;
                }
                else {
                  piVar4[2] = (int)piVar9;
                }
              }
              *piVar9 = (int)piVar6;
              piVar6[1] = (int)piVar9;
              piVar6 = *(int **)piVar10[1];
            }
            piVar6[7] = *(int *)(piVar10[1] + 0x1c);
            *(undefined4 *)(piVar10[1] + 0x1c) = 1;
            *(undefined4 *)(*piVar6 + 0x1c) = 1;
            puVar7 = (undefined4 *)piVar10[1];
            puVar8 = (undefined4 *)*puVar7;
            *puVar7 = puVar8[2];
            if ((int *)puVar8[2] != DAT_004ea6ec) {
              ((int *)puVar8[2])[1] = (int)puVar7;
            }
            puVar8[1] = puVar7[1];
            if (puVar7 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar8;
            }
            else {
              puVar5 = (undefined4 *)puVar7[1];
              if (puVar7 == (undefined4 *)puVar5[2]) {
                puVar5[2] = puVar8;
              }
              else {
                *puVar5 = puVar8;
              }
            }
            puVar8[2] = puVar7;
LAB_0045a1e6:
            puVar7[1] = puVar8;
            break;
          }
        }
        piVar6[7] = 0;
        piVar10 = (int *)piVar10[1];
      } while (piVar10 != *(int **)(*(int *)((int)this + 4) + 4));
    }
    piVar10[7] = 1;
  }
  FUN_004b9beb();
  iVar3 = local_c[4];
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar3 + -1));
    }
    else {
      *(char *)(iVar3 + -1) = cVar1 + -1;
    }
  }
  local_c[4] = 0;
  local_c[5] = 0;
  local_c[6] = 0;
  FUN_00430df0((undefined *)local_c);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
  *param_1 = param_2;
  return;
}


/* 0045a250 size=235 */

void __thiscall FUN_0045a250(void *this,int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int *local_8;
  
  piVar3 = *(int **)((int)this + 4);
  piVar6 = *(int **)(*(int *)(param_1 + 4) + 4);
  piVar5 = piVar3;
  local_8 = piVar6;
  if (piVar6 != DAT_004ea6ec) {
    do {
      iVar1 = piVar6[7];
      piVar3 = (int *)FUN_00430de0(0x20);
      piVar3[7] = iVar1;
      piVar3[1] = (int)piVar5;
      if (local_8 == piVar6) {
        local_8 = piVar3;
      }
      piVar4 = FUN_0045a3b0((int *)piVar6[2],piVar3);
      piVar3[2] = (int)piVar4;
      FUN_00430970((undefined1 *)(piVar3 + 3),(undefined1 *)(piVar6 + 3));
      *piVar5 = (int)piVar3;
      piVar6 = (int *)*piVar6;
      piVar5 = piVar3;
    } while (piVar6 != DAT_004ea6ec);
  }
  *piVar3 = (int)DAT_004ea6ec;
  *(int **)(*(int *)((int)this + 4) + 4) = local_8;
  puVar2 = *(undefined4 **)((int)this + 4);
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
  piVar3 = (int *)puVar2[1];
  if (piVar3 == DAT_004ea6ec) {
    *puVar2 = puVar2;
    *(int *)(*(int *)((int)this + 4) + 8) = *(int *)((int)this + 4);
    return;
  }
  for (piVar6 = (int *)*piVar3; piVar6 != DAT_004ea6ec; piVar6 = (int *)*piVar6) {
    piVar3 = piVar6;
  }
  *puVar2 = piVar3;
  piVar3 = *(int **)(*(int *)((int)this + 4) + 4);
  for (piVar6 = (int *)piVar3[2]; piVar6 != DAT_004ea6ec; piVar6 = (int *)piVar6[2]) {
    piVar3 = piVar6;
  }
  *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
  return;
}


/* 0045a340 size=108 */

void FUN_0045a340(int *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  
  if (param_1 != DAT_004ea6ec) {
    do {
      FUN_0045a340((int *)param_1[2]);
      iVar2 = param_1[4];
      piVar3 = (int *)*param_1;
      if (iVar2 != 0) {
        cVar1 = *(char *)(iVar2 + -1);
        if ((cVar1 == '\0') || (cVar1 == -1)) {
          FUN_00430df0((char *)(iVar2 + -1));
        }
        else {
          *(char *)(iVar2 + -1) = cVar1 + -1;
        }
      }
      param_1[4] = 0;
      param_1[5] = 0;
      param_1[6] = 0;
      FUN_00430df0((undefined *)param_1);
      param_1 = piVar3;
    } while (piVar3 != DAT_004ea6ec);
  }
  return;
}


/* 0045a3b0 size=164 */

int * FUN_0045a3b0(int *param_1,int *param_2)

{
  int *this;
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  
  if (param_1 == DAT_004ea6ec) {
    *param_2 = (int)DAT_004ea6ec;
    return param_1;
  }
  piVar4 = param_1;
  do {
    iVar1 = piVar4[7];
    piVar2 = (int *)FUN_00430de0(0x20);
    piVar2[1] = (int)param_2;
    piVar2[7] = iVar1;
    if (param_1 == piVar4) {
      param_1 = piVar2;
    }
    piVar3 = FUN_0045a3b0((int *)piVar4[2],piVar2);
    this = piVar2 + 3;
    piVar2[2] = (int)piVar3;
    if (this != (int *)0x0) {
      iVar1 = piVar4[3];
      piVar2[4] = 0;
      *(char *)this = (char)iVar1;
      piVar2[5] = 0;
      piVar2[6] = 0;
      FUN_0042fc30(this,piVar4 + 3,0,DAT_004cc284);
    }
    *param_2 = (int)piVar2;
    piVar4 = (int *)*piVar4;
    param_2 = piVar2;
  } while (piVar4 != DAT_004ea6ec);
  *piVar2 = (int)DAT_004ea6ec;
  return param_1;
}


/* 0045a460 size=27 */

int FUN_0045a460(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_00430de0(0x20);
  *(undefined4 *)(iVar1 + 4) = param_1;
  *(undefined4 *)(iVar1 + 0x1c) = param_2;
  return;
}


/* 0045a480 size=81 */

void __fastcall FUN_0045a480(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)*param_1;
  if ((piVar3[0xb] == 0) && (*(int **)(piVar3[1] + 4) == piVar3)) {
    *param_1 = piVar3[2];
    return;
  }
  iVar1 = *piVar3;
  if (iVar1 != DAT_004ea6f0) {
    for (iVar2 = *(int *)(iVar1 + 8); iVar2 != DAT_004ea6f0; iVar2 = *(int *)(iVar2 + 8)) {
      iVar1 = iVar2;
    }
    *param_1 = iVar1;
    return;
  }
  piVar3 = (int *)piVar3[1];
  if (*param_1 == *piVar3) {
    do {
      *param_1 = (int)piVar3;
      piVar3 = (int *)piVar3[1];
    } while (*param_1 == *piVar3);
  }
  *param_1 = (int)piVar3;
  return;
}


/* 0045a4e0 size=73 */

void * __cdecl FUN_0045a4e0(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  void *this;
  void *pvVar2;
  
  pvVar2 = (void *)(**(code **)(*param_1 + 4))(param_3 * 0x5c);
  iVar1 = param_3;
  this = pvVar2;
  if (pvVar2 == (void *)0x0) {
    return (void *)0x0;
  }
  for (; iVar1 != 0; iVar1 = iVar1 + -1) {
    if (this != (void *)0x0) {
      FUN_0044fdb0(this,param_3);
    }
    this = (void *)((int)this + 0x5c);
  }
  return pvVar2;
}


/* 0045a530 size=49 */

void __cdecl FUN_0045a530(int *param_1,undefined4 *param_2,int param_3)

{
  undefined4 *puVar1;
  
  puVar1 = param_2;
  if (param_2 != (undefined4 *)0x0) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      (**(code **)*puVar1)(0);
      puVar1 = puVar1 + 0x17;
    }
    (**(code **)(*param_1 + 8))(param_2);
  }
  return;
}


/* 0045a570 size=317 */

/* FUN_0045a570: lifted from original x86 -> lt_lifted.c */


/* 0045a6b0 size=83 */

undefined * __thiscall FUN_0045a6b0(void *this,byte param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)((int)this + 4);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar2 + -1));
    }
    else {
      *(char *)(iVar2 + -1) = cVar1 + -1;
    }
  }
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0045a710 size=80 */

uint __thiscall FUN_0045a710(void *this,int param_1)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  bool bVar7;
  bool bVar8;
  
  uVar1 = *(uint *)(param_1 + 8);
  pbVar3 = *(byte **)(param_1 + 4);
  if (pbVar3 == (byte *)0x0) {
    pbVar3 = &DAT_004cc108;
  }
  uVar2 = *(uint *)((int)this + 8);
  uVar5 = uVar2;
  if (uVar1 <= uVar2) {
    uVar5 = uVar1;
  }
  bVar7 = false;
  uVar4 = 0;
  bVar8 = true;
  pbVar6 = *(byte **)((int)this + 4);
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    bVar7 = *pbVar6 < *pbVar3;
    bVar8 = *pbVar6 == *pbVar3;
    pbVar6 = pbVar6 + 1;
    pbVar3 = pbVar3 + 1;
  } while (bVar8);
  if (!bVar8) {
    uVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
  }
  if (uVar4 == 0) {
    if (uVar2 < uVar1) {
      return 0xffffffff;
    }
    uVar4 = (uint)(uVar2 != uVar1);
  }
  return uVar4;
}


/* 0045a760 size=124 */

undefined4 __thiscall FUN_0045a760(void *this,int param_1,undefined4 *param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    if (*(int *)((int)this + 4) != 0) {
      FUN_00456e60(param_3,*(int *)((int)this + 4));
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = FUN_00456f10(param_3,0,param_1);
      *(int *)((int)this + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  uVar2 = 0;
  if (*(int *)((int)this + 8) != 0) {
    do {
      *(undefined4 *)(*(int *)((int)this + 4) + uVar2 * 4) = *param_2;
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)((int)this + 8));
  }
  return 1;
}


/* 0045a810 size=30 */

undefined * __thiscall FUN_0045a810(void *this,byte param_1)

{
  FUN_004506c0((int)this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0045a830 size=264 */

undefined4 __thiscall FUN_0045a830(void *this,uint param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint unaff_retaddr;
  
  uVar4 = param_1;
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*param_2 + 8))(iVar1);
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)((int)this + 0x10) = *(undefined4 *)(param_1 + 0x10);
  iVar1 = *(int *)((int)this + 8) + *(int *)((int)this + 0xc);
  if (iVar1 == 0) {
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    iVar1 = (**(code **)(*param_2 + 4))(iVar1 * 0x1c);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    *(int *)((int)this + 4) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)((int)this + 8) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
      return 0;
    }
    param_1 = 0;
    if (*(int *)((int)this + 8) != 0) {
      iVar1 = 0;
      while( true ) {
        puVar2 = (undefined4 *)(iVar1 + *(int *)(uVar4 + 4));
        puVar3 = (undefined4 *)(iVar1 + *(int *)((int)this + 4));
        iVar1 = iVar1 + 0x1c;
        *puVar3 = *puVar2;
        puVar3[1] = puVar2[1];
        puVar3[2] = puVar2[2];
        puVar3[3] = puVar2[3];
        puVar3[4] = puVar2[4];
        puVar3[5] = puVar2[5];
        puVar3[6] = puVar2[6];
        param_1 = param_1 + 1;
        if (*(uint *)((int)this + 8) <= param_1) break;
        uVar4 = unaff_retaddr;
      }
      return 1;
    }
  }
  return 1;
}


/* 0045a970 size=12 */

undefined4 * __fastcall FUN_0045a970(undefined4 *param_1)

{
  FUN_0045a980(param_1);
  return param_1;
}


/* 0045a980 size=41 */

void __fastcall FUN_0045a980(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  return;
}


/* 0045a9b0 size=191 */

bool __thiscall FUN_0045a9b0(void *this,int *param_1)

{
  int iVar1;
  
  (**(code **)(*param_1 + 8))(this,4);
  (**(code **)(*param_1 + 8))((int)this + 4,4);
  (**(code **)(*param_1 + 8))((int)this + 8,4);
  (**(code **)(*param_1 + 8))((int)this + 0xc,4);
  (**(code **)(*param_1 + 8))((int)this + 0x10,4);
  (**(code **)(*param_1 + 8))((int)this + 0x14,4);
  (**(code **)(*param_1 + 8))((int)this + 0x18,4);
  (**(code **)(*param_1 + 8))((int)this + 0x1c,4);
  (**(code **)(*param_1 + 8))((int)this + 0x20,4);
  (**(code **)(*param_1 + 8))((int)this + 0x24,4);
  (**(code **)(*param_1 + 8))((int)this + 0x28,4);
  (**(code **)(*param_1 + 8))((int)this + 0x2c,4);
  (**(code **)(*param_1 + 8))((int)this + 0x30,4);
  iVar1 = (**(code **)(*param_1 + 0x10))();
  return (bool)('\x01' - (iVar1 != 0));
}


/* 0045aa70 size=355 */

undefined4 __thiscall FUN_0045aa70(void *this,int *param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)((int)this + 0x20) == 0) {
    return 0;
  }
  *param_1 = 0;
  iVar1 = *(int *)((int)this + 8) + -1;
  iVar2 = *(int *)((int)this + 0x2c) * 0xc;
  *param_1 = iVar2;
  iVar2 = ((*(int *)((int)this + 0x2c) + 1) * 3 + *(int *)((int)this + 0x30) & 0xfffffffcU) + 1000 +
          iVar2;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 8) * *(int *)this * 0x1c;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 4) * iVar1 * 4;
  *param_1 = iVar2;
  iVar2 = *(int *)((int)this + 4) * iVar1 * 0x30 + iVar2;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)this * 0x14;
  *param_1 = iVar2;
  iVar2 = iVar2 + (*(int *)((int)this + 8) * *(int *)((int)this + 4) + iVar1 * 0x2e) * 4;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0x10) * *(int *)((int)this + 8) * 0x1c;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0x14) * 0x20;
  *param_1 = iVar2;
  iVar2 = *(int *)((int)this + 0x18) * 0x20 + iVar2;
  *param_1 = iVar2;
  iVar2 = iVar2 + (*(int *)((int)this + 0x20) + -1) * *(int *)((int)this + 0xc) * 0x24;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0xc) * 4;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0xc) * 0x6c;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0x28) * *(int *)((int)this + 8) * 4;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0x28) * 4;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0x28) * 0x28;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0x24) * 4;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0x24) * 0x34;
  *param_1 = iVar2;
  iVar2 = iVar2 + -4 + *(int *)((int)this + 0x20) * 4;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 0x1c) * 0x14;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 8) * 0x40;
  *param_1 = iVar2;
  iVar2 = iVar2 + *(int *)((int)this + 8) * 4;
  *param_1 = iVar2;
  iVar2 = *(int *)((int)this + 0x10) * 0x30 + -0x30 + iVar2;
  *param_1 = iVar2;
  *param_1 = iVar2 + *(int *)((int)this + 4) * 0x5c;
  return 1;
}


/* 0045b0f0 size=168 */

undefined4 FUN_0045b0f0(int param_1,byte param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  
  if ((param_1 == 0) || (*(char *)(param_1 + 0xbc) != '\x01')) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   PTR_s_ServerModelLT_SetPieceHideStatu_004daad8);
    }
    return 0x3c;
  }
  uVar2 = 1 << (param_2 & 0x1f);
  uVar1 = *(uint *)(param_1 + 0x24c);
  if ((param_3 != 0) == ((uVar1 & uVar2) != 0)) {
    return 0x46;
  }
  if (param_3 != 0) {
    *(uint *)(param_1 + 0x24c) = uVar1 | uVar2;
    return 0;
  }
  *(uint *)(param_1 + 0x24c) = ~uVar2 & uVar1;
  return 0;
}


/* 0045b760 size=65 */

void __thiscall FUN_0045b760(void *this,undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  *(undefined4 *)this = *param_1;
  *(undefined4 *)((int)this + 0x10) = param_1[1];
  *(undefined4 *)((int)this + 0x20) = param_1[2];
  *(undefined4 *)((int)this + 4) = *param_2;
  *(undefined4 *)((int)this + 0x14) = param_2[1];
  *(undefined4 *)((int)this + 0x24) = param_2[2];
  *(undefined4 *)((int)this + 8) = *param_3;
  *(undefined4 *)((int)this + 0x18) = param_3[1];
  *(undefined4 *)((int)this + 0x28) = param_3[2];
  return;
}


/* 0045b8d0 size=103 */

undefined4 FUN_0045b8d0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_ILTModel_SetWeightSet_004daaf0
                  );
    }
    return 0x3c;
  }
  if (*(int *)(param_1 + 0x24) == 0) {
    *(undefined4 *)(param_1 + 0x34) = param_2;
    *(undefined4 *)(param_1 + 0x40) = param_2;
    return 0;
  }
  uVar1 = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(param_1 + 0x40) = param_2;
  *(undefined4 *)(param_1 + 0x34) = uVar1;
  return 0;
}


/* 0045b9a0 size=97 */

undefined4 FUN_0045b9a0(int param_1,int param_2)

{
  if (param_1 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   PTR_s_ILTModel_SetAllowTransition_004daaf8);
    }
    return 0x3c;
  }
  *(int *)(param_1 + 0x24) = param_2;
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x40);
    *(undefined2 *)(param_1 + 0x2c) = *(undefined2 *)(param_1 + 0x38);
  }
  return 0;
}


/* 0045ba90 size=178 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0045ba90(int param_1,float param_2)

{
  longlong lVar1;
  
  if (param_1 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   PTR_s_ILTModel_SetAllowTransition_004dab00);
    }
    return 0x3c;
  }
  if (param_2 < _DAT_004cba94) {
    lVar1 = __ftol();
    *(int *)(param_1 + 0x20) = (int)lVar1;
    *(undefined4 *)(param_1 + 0x1c) = 100000;
    return 0;
  }
  if (_DAT_004cba94 < param_2) {
    *(undefined4 *)(param_1 + 0x20) = 100000;
    lVar1 = __ftol();
    *(int *)(param_1 + 0x1c) = (int)lVar1;
    return 0;
  }
  *(undefined4 *)(param_1 + 0x1c) = 1;
  *(undefined4 *)(param_1 + 0x20) = 1;
  return 0;
}


/* 0045bb50 size=206 */

undefined4 FUN_0045bb50(int param_1,uint *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  *param_2 = 0;
  if (param_1 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   PTR_s_ILTModel_GetCurAnimLength_004dab04);
    }
    return 0x3c;
  }
  iVar1 = *(int *)((uint)*(ushort *)(param_1 + 0x38) * 0x20 +
                  *(int *)(*(int *)(param_1 + 0x28) + 0x168));
  if (iVar1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   PTR_s_ILTModel_GetCurAnimLength_004dab04);
    }
    return 0x49;
  }
  uVar2 = FUN_00450020(iVar1);
  *param_2 = uVar2;
  if (param_3 != 0) {
    uVar2 = *(int *)(param_1 + 0x20) * uVar2;
    *param_2 = uVar2;
    *param_2 = uVar2 / *(uint *)(param_1 + 0x1c);
  }
  return 0;
}


/* 0045bca0 size=116 */

undefined4 FUN_0045bca0(uint param_1,uint param_2,int param_3)

{
  if (param_1 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   PTR_s_ILTModel_SetCurAnimTime_004dab0c);
    }
    return 0x3c;
  }
  if (param_3 != 0) {
    param_2 = (*(int *)(param_1 + 0x20) * param_2) / *(uint *)(param_1 + 0x1c);
  }
  FUN_004011a0(param_1,param_2,*(byte *)(param_1 + 0x18) & 1);
  return 0;
}


/* 0045bd20 size=243 */

undefined4 FUN_0045bd20(int *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_2;
  piVar2 = param_1;
  if (((param_1 == (int *)0x0) || ((char)param_1[0x2f] != '\x01')) || (param_2 == 0)) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_ILTModel_AddTracker_004dab10);
    }
    return 0x3c;
  }
  iVar4 = (**(code **)(*param_1 + 0x40))(param_2,&param_1);
  if (iVar4 != 0) {
    FUN_004356e0();
    if (2 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_ILTModel_AddTracker_004dab10);
    }
    return 0x3e;
  }
  piVar1 = piVar2 + 0x88;
  for (iVar4 = piVar2[0x88]; iVar4 != 0; iVar4 = *(int *)(iVar4 + 4)) {
    piVar1 = (int *)(iVar4 + 4);
  }
  FUN_00401050(iVar3,piVar2[0x7e],0);
  *(int **)(iVar3 + 8) = piVar2;
  *(undefined4 *)(iVar3 + 4) = 0;
  *piVar1 = iVar3;
  return 0;
}


/* 0045be20 size=221 */

undefined4 FUN_0045be20(int *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *unaff_ESI;
  
  piVar1 = param_2;
  if (((param_1 == (int *)0x0) || ((char)param_1[0x2f] != '\x01')) || (param_2 == (int *)0x0)) {
    FUN_004356e0();
  }
  else {
    if (param_2 != param_1 + 0x74) {
      iVar2 = (**(code **)(*param_1 + 0x40))(param_2,&param_1);
      if (iVar2 != 0) {
        *unaff_ESI = piVar1[1];
        return 0;
      }
      FUN_004356e0();
      if (2 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     PTR_s_ILTModel_RemoveTracker_004dab14);
      }
      return 0x3d;
    }
    FUN_004356e0();
  }
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_ILTModel_RemoveTracker_004dab14)
    ;
  }
  return 0x3c;
}


