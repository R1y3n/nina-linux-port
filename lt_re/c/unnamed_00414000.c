/* lithtech.exe decompilation - unnamed_00414000 */
#include "ghidra_types.h"

/* 004140d0 size=39 */

void __thiscall FUN_004140d0(void *this,undefined4 *param_1)

{
  FUN_0042e160(param_1);
  if ((param_1 != (undefined4 *)0x0) && (this != (void *)0xfffffffc)) {
    *param_1 = *(undefined4 *)((int)this + 0x1c);
    *(undefined4 **)((int)this + 0x1c) = param_1;
  }
  return;
}


/* 00414100 size=72 */

void __thiscall FUN_00414100(void *this,char param_1)

{
  char cVar1;
  int iVar2;
  
  if ((param_1 != '\0') && (iVar2 = *(int *)((int)this + 4), iVar2 != 0)) {
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
  return;
}


/* 00414150 size=81 */

undefined4 * __thiscall FUN_00414150(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  LONG LVar2;
  
  puVar1 = *(undefined4 **)this;
  if (puVar1 != param_1) {
    if (puVar1 != (undefined4 *)0x0) {
      LVar2 = InterlockedDecrement(puVar1 + 1);
      if ((LVar2 < 1) && (puVar1 != (undefined4 *)0x0)) {
        (**(code **)*puVar1)(1);
      }
    }
    if (param_1 != (undefined4 *)0x0) {
      InterlockedIncrement(param_1 + 1);
      *(undefined4 **)this = param_1;
      return param_1;
    }
    *(undefined4 *)this = 0;
  }
  return param_1;
}


/* 004141b0 size=249 */

undefined4 __thiscall FUN_004141b0(void *this,uint param_1,int *param_2,int *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *unaff_EBX;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  uVar5 = *(uint *)((int)this + 8);
  if (param_1 < uVar5) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = *(int *)((int)this + 0xc) + (uVar5 - param_1);
    return 1;
  }
  if ((uVar5 < param_1) && (uVar4 = *(int *)((int)this + 0xc) + uVar5, param_1 <= uVar4)) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = uVar4 - param_1;
    return 1;
  }
  if (param_1 == uVar5) {
    return 1;
  }
  puVar2 = (undefined4 *)(**(code **)(*param_3 + 4))((param_1 + *(int *)((int)this + 0x10)) * 4);
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  uVar5 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar5 = param_1;
  }
  if (param_1 == 0) {
    uVar4 = 0;
    param_2 = param_3;
    if (uVar5 != 0) {
      do {
        uVar3 = uVar4 + 1;
        puVar2[uVar4] = *(undefined4 *)(*(int *)((int)this + 4) + -4 + uVar3 * 4);
        uVar4 = uVar3;
      } while (uVar3 < uVar5);
    }
  }
  else {
    puVar6 = *(undefined4 **)((int)this + 4);
    puVar7 = puVar2;
    for (; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
  }
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*param_2 + 8))(iVar1);
      puVar2 = unaff_EBX;
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 **)((int)this + 4) = puVar2;
  *(uint *)((int)this + 8) = param_1;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  return 1;
}


/* 004142b0 size=31 */

void __fastcall FUN_004142b0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbda4;
  FUN_004b7c10((int)(param_1 + 1));
  *param_1 = &PTR_LAB_004cb514;
  return;
}


/* 00414470 size=307 */

undefined4 __thiscall FUN_00414470(void *this,uint param_1,int *param_2,int *param_3)

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
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(iVar5 * 0x60);
  puVar6 = puVar1;
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  for (; iVar5 != 0; iVar5 = iVar5 + -1) {
    if (puVar6 != (undefined4 *)0x0) {
      FUN_00428dc0((undefined1 *)puVar6);
    }
    puVar6 = puVar6 + 0x18;
  }
  uVar3 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar3 = param_1;
  }
  if (param_1 == 0) {
    uVar8 = 0;
    if (uVar3 == 0) goto LAB_0041455b;
    iVar5 = 0;
    do {
      puVar7 = (undefined4 *)(iVar5 + *(int *)((int)this + 4));
      puVar6 = (undefined4 *)(iVar5 + (int)puVar1);
      iVar5 = iVar5 + 0x60;
      uVar3 = uVar3 - 1;
      for (iVar4 = 0x18; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar6 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar6 = puVar6 + 1;
      }
    } while (uVar3 != 0);
  }
  else {
    puVar6 = *(undefined4 **)((int)this + 4);
    puVar7 = puVar1;
    for (uVar3 = uVar3 * 0x60 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
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
LAB_0041455b:
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


/* 004145b0 size=133 */

undefined4 __thiscall FUN_004145b0(void *this,int param_1,int *param_2)

{
  int iVar1;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = (**(code **)(*param_2 + 4))((param_1 + *(int *)((int)this + 0x10)) * 0x18);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      *(int *)((int)this + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 00414640 size=293 */

undefined4 __thiscall FUN_00414640(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *unaff_EBP;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
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
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))((param_1 + *(int *)((int)this + 0x10)) * 0x18);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  uVar3 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar3 = param_1;
  }
  if (param_1 == 0) {
    if (uVar3 == 0) goto LAB_0041471b;
    iVar4 = 0;
    do {
      puVar6 = (undefined4 *)(*(int *)((int)this + 4) + iVar4);
      puVar7 = (undefined4 *)(iVar4 + (int)puVar1);
      for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      iVar4 = iVar4 + 0x18;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
  else {
    puVar6 = *(undefined4 **)((int)this + 4);
    puVar7 = puVar1;
    for (uVar3 = uVar3 * 0x18 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
  }
  param_3 = param_2;
LAB_0041471b:
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


/* 00414770 size=29 */

undefined4 * __fastcall FUN_00414770(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbd94;
  FUN_004b7b90(param_1 + 1,0x40,0x20);
  return param_1;
}


/* 004147d0 size=52 */

undefined4 * __thiscall FUN_004147d0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbda4;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414810 size=52 */

undefined4 * __thiscall FUN_00414810(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbcf4;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414850 size=52 */

undefined4 * __thiscall FUN_00414850(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd04;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414890 size=52 */

undefined4 * __thiscall FUN_00414890(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd14;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004148d0 size=52 */

undefined4 * __thiscall FUN_004148d0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd24;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414910 size=52 */

undefined4 * __thiscall FUN_00414910(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd34;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414950 size=52 */

undefined4 * __thiscall FUN_00414950(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd44;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414990 size=52 */

undefined4 * __thiscall FUN_00414990(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd54;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004149d0 size=52 */

undefined4 * __thiscall FUN_004149d0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd64;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414a10 size=52 */

undefined4 * __thiscall FUN_00414a10(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd74;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414a50 size=52 */

undefined4 * __thiscall FUN_00414a50(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd84;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414a90 size=52 */

undefined4 * __thiscall FUN_00414a90(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbd94;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414ad0 size=52 */

undefined4 * __thiscall FUN_00414ad0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbb80;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414b10 size=253 */

undefined4 __thiscall FUN_00414b10(void *this,undefined1 *param_1,undefined1 *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  
  puVar3 = *(undefined1 **)((int)this + 8);
  if (puVar3 < param_1) {
    return 0;
  }
  if (*(int *)((int)this + 0xc) != 0) {
    for (; param_1 < puVar3; puVar3 = puVar3 + -1) {
      puVar3[*(int *)((int)this + 4)] = (puVar3 + *(int *)((int)this + 4))[-1];
    }
    *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
    param_1[*(int *)((int)this + 4)] = *param_2;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    return 1;
  }
  iVar2 = (**(code **)(*param_3 + 4))(puVar3 + *(int *)((int)this + 0x10) + 1);
  if (iVar2 == 0) {
    return 0;
  }
  puVar3 = (undefined1 *)0x0;
  if (param_1 != (undefined1 *)0x0) {
    do {
      puVar3 = puVar3 + 1;
      puVar3[iVar2 + -1] = puVar3[*(int *)((int)this + 4) + -1];
    } while (puVar3 < param_1);
  }
  puVar3 = param_1;
  if (param_1 < *(undefined1 **)((int)this + 8)) {
    do {
      puVar3 = puVar3 + 1;
      puVar3[iVar2] = puVar3[*(int *)((int)this + 4) + -1];
    } while (puVar3 < *(undefined1 **)((int)this + 8));
  }
  param_1[iVar2] = *param_1;
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*param_3 + 8))(iVar1);
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(int *)((int)this + 4) = iVar2;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
  return 1;
}


/* 00414c40 size=136 */

undefined4 * __thiscall FUN_00414c40(void *this,byte param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  if ((param_1 & 2) == 0) {
    if (*(undefined **)((int)this + 0x4c) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)((int)this + 0x4c));
    }
    if (((param_1 & 1) != 0) && (this != (void *)0x0)) {
      *(void **)this = DAT_004ea5a8;
      DAT_004ea5a8 = this;
    }
    return this;
  }
  iVar2 = *(int *)((int)this + -4);
  if (-1 < iVar2 + -1) {
    iVar3 = (int)this + iVar2 * 0x54 + 0x4c;
    do {
      puVar1 = (undefined4 *)(iVar3 + -0x54);
      iVar3 = iVar3 + -0x54;
      if ((undefined *)*puVar1 != (undefined *)0x0) {
        FUN_00430df0((undefined *)*puVar1);
      }
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  if ((param_1 & 1) != 0) {
    FUN_00430df0((undefined *)((int)this + -4));
  }
  return (undefined4 *)((int)this + -4);
}


/* 00414cd0 size=128 */

undefined4 * __thiscall FUN_00414cd0(void *this,byte param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  if ((param_1 & 2) == 0) {
    if (*(undefined **)((int)this + 0x4c) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)((int)this + 0x4c));
    }
    if (((param_1 & 1) != 0) && (this != (void *)0x0)) {
      *(void **)this = DAT_004ea5c0;
      DAT_004ea5c0 = this;
    }
    return this;
  }
  iVar2 = *(int *)((int)this + -4);
  if (-1 < iVar2 + -1) {
    iVar3 = (int)this + iVar2 * 0x50 + 0x4c;
    do {
      puVar1 = (undefined4 *)(iVar3 + -0x50);
      iVar3 = iVar3 + -0x50;
      if ((undefined *)*puVar1 != (undefined *)0x0) {
        FUN_00430df0((undefined *)*puVar1);
      }
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  if ((param_1 & 1) != 0) {
    FUN_00430df0((undefined *)((int)this + -4));
  }
  return (undefined4 *)((int)this + -4);
}


/* 00414d50 size=61 */

undefined1 * __cdecl FUN_00414d50(int *param_1,undefined4 param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)(**(code **)(*param_1 + 4))(param_3 * 0x60);
  puVar1 = puVar2;
  if (puVar2 == (undefined1 *)0x0) {
    return (undefined1 *)0x0;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    if (puVar1 != (undefined1 *)0x0) {
      FUN_00428dc0(puVar1);
    }
    puVar1 = puVar1 + 0x60;
  }
  return puVar2;
}


/* 00414d90 size=25 */

void __cdecl FUN_00414d90(int *param_1,undefined4 param_2,int param_3)

{
  (**(code **)(*param_1 + 4))(param_3 * 0x18);
  return;
}


/* 00414dd0 size=134 */

undefined4 * __fastcall FUN_00414dd0(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined2 *)(param_1 + 0xe) = 0xffff;
  *(undefined2 *)(param_1 + 0x1b) = 0xffff;
  puVar1 = param_1 + 0x11;
  *param_1 = &PTR_FUN_004cbdb8;
  param_1[0x1c] = 0;
  param_1[0x1f] = 0;
  param_1[7] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[0x1d] = 0;
  param_1[0xd] = 0;
  param_1[0xc] = 0;
  param_1[0x20] = 0;
  param_1[0x10] = 0;
  param_1[0x12] = puVar1;
  *puVar1 = puVar1;
  puVar1 = param_1 + 0x14;
  param_1[0x15] = puVar1;
  *puVar1 = puVar1;
  param_1[0x22] = 0;
  do {
    lVar3 = __ftol();
    *(char *)((int)param_1 + uVar2 + 4) = (char)lVar3;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x10);
  return param_1;
}


/* 00414e60 size=30 */

int * __thiscall FUN_00414e60(void *this,byte param_1)

{
  FUN_00414e80(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00414e80 size=22 */

void __fastcall FUN_00414e80(int *param_1)

{
  *param_1 = (int)&PTR_FUN_004cbdb8;
  FUN_00414f00(param_1);
  *param_1 = (int)&PTR_LAB_004cbdcc;
  return;
}


/* 00414ec0 size=57 */

undefined4 __thiscall FUN_00414ec0(void *this,undefined4 param_1)

{
  int *piVar1;
  
  *(undefined4 *)((int)this + 0x78) = param_1;
  shellnet_48e480();
  *(void **)(*(int *)((int)this + 0x78) + 0x5c4) = this;
  DAT_004e5174 = this;
  piVar1 = FUN_00434a60(100,0);
  *(int **)((int)this + 0x8c) = piVar1;
  return 1;
}


/* 00414f00 size=226 */

void __fastcall FUN_00414f00(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piStack_4;
  
  piStack_4 = param_1;
  FUN_00412790(param_1[0x1e],(int)param_1);
  if (*(int *)(param_1[0x1e] + 0x540) != 0) {
    FUN_00492520(param_1);
  }
  netmgr_465780((void *)(param_1[0x1e] + 0x510),param_1[0xd],0);
  param_1[0xd] = 0;
  *(undefined4 *)(param_1[0x1e] + 0x5c4) = 0;
  if ((undefined4 *)param_1[0x10] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)param_1[0x10])(1);
    param_1[0x10] = 0;
  }
  FUN_00415c00((int)param_1);
  FUN_00416610((int)param_1);
  FUN_00416630((int)param_1);
  param_1[0xc] = 0;
  *(undefined2 *)(param_1 + 0x1b) = 0xffff;
  param_1[0x22] = 0;
  piStack_4 = (int *)FUN_00434ff0(param_1[0x23]);
  while (piStack_4 != (int *)0x0) {
    iVar1 = FUN_00435040((int *)&piStack_4);
    if (iVar1 != 0) {
      puVar2 = (undefined4 *)FUN_00434fd0(iVar1);
      iVar1 = param_1[0x1e];
      if ((puVar2 != (undefined4 *)0x0) && (iVar1 != -0x1230)) {
        *puVar2 = *(undefined4 *)(iVar1 + 0x1248);
        *(undefined4 **)(iVar1 + 0x1248) = puVar2;
      }
    }
  }
  FUN_00434d00((int *)param_1[0x23]);
  DAT_004e5174 = 0;
  return;
}


/* 00414ff0 size=12 */

undefined4 __thiscall FUN_00414ff0(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 0x30) = param_1;
  return 0;
}


/* 00415150 size=427 */

undefined4 __fastcall FUN_00415150(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  float local_c [3];
  
  puVar2 = (undefined4 *)FUN_00430de0(0xd3c);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    puVar1 = puVar2 + 0x12;
    *puVar2 = &PTR_LAB_004cbdcc;
    puVar2[1] = &PTR_LAB_004cbe0c;
    puVar2[0x13] = puVar1;
    *puVar1 = puVar1;
    puVar1 = puVar2 + 0x16;
    puVar2[0x11] = 0;
    puVar2[0x17] = puVar1;
    *puVar1 = puVar1;
    puVar2[0x15] = 0;
    FUN_00428e80(puVar2 + 0x69);
    FUN_00468570(puVar2 + 0xe5);
    FUN_00413050(local_c,0,0xc4fa0000,0);
    FUN_00411ce0(puVar2 + 0x21d,local_c);
    puVar2[0x229] = 0xbf350481;
    FUN_00464770(puVar2 + 0x23b);
    puVar1 = puVar2 + 0x27e;
    puVar2[0x27f] = puVar1;
    *puVar1 = puVar1;
    puVar2[0x27d] = 0;
    FUN_00402920(puVar2 + 0x287);
    FUN_00411cc0(puVar2 + 699);
    FUN_00411cc0(puVar2 + 0x2bf);
    FUN_00416de0(puVar2 + 0x2c3);
    FUN_004798d0(puVar2 + 0x2cf);
    FUN_004174a0(puVar2 + 0x300);
    FUN_004b7fa0(puVar2 + 0x309);
    FUN_00415540((int)(puVar2 + 0x30f));
    smoveabstract_4928e0(puVar2 + 0x335);
    *puVar2 = &PTR_FUN_004cbdf8;
    puVar2[1] = &PTR_LAB_004cbde0;
    puVar2[2] = 1;
    puVar2[0x283] = 0;
    puVar2[0x284] = 0;
  }
  *(undefined4 **)(param_1 + 0x40) = puVar2;
  if (puVar2 != (undefined4 *)0x0) {
    iVar3 = servermgr_4854c0(puVar2);
    if (iVar3 != 0) {
      if (*(int *)(param_1 + 0x78) != 0) {
        FUN_00467a80((void *)(*(int *)(param_1 + 0x40) + 0x8ec),
                     (undefined4 *)(*(int *)(param_1 + 0x78) + 0x600));
      }
      return 0;
    }
  }
  if (*(undefined4 **)(param_1 + 0x40) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x40))(1);
  }
  *(undefined4 *)(param_1 + 0x40) = 0;
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CClientShell__CreateServerMgr_004d6768);
  }
  return 0x32;
}


/* 00415300 size=562 */

undefined4 * __thiscall FUN_00415300(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbdf8;
  *(undefined ***)((int)this + 4) = &PTR_LAB_004cbde0;
  FUN_004858f0(this);
  FUN_0044e3b0((undefined4 *)((int)this + 0xcd4));
  *(undefined ***)((int)this + 0xc54) = &PTR_FUN_004cbe64;
  FUN_004b7c10((int)this + 0xc58);
  *(undefined ***)((int)this + 0xc54) = &PTR_LAB_004cb514;
  FUN_004b8020((undefined4 *)((int)this + 0xc24));
  *(undefined ***)((int)this + 0xc00) = &PTR_FUN_004cbe54;
  FUN_004b7c10((int)this + 0xc04);
  *(undefined ***)((int)this + 0xc00) = &PTR_LAB_004cb514;
  *(undefined4 *)((int)this + 0xb0c) = &PTR_LAB_004cbe24;
  FUN_00417300((undefined4 *)((int)this + 0xb0c),0,&DAT_004ecc58);
  thunk_FUN_00402970((undefined4 *)((int)this + 0xa1c));
  FUN_00464870((void *)((int)this + 0x8ec));
  *(undefined ***)((int)this + 0x564) = &PTR_FUN_004cbd84;
  FUN_004b7c10((int)this + 0x568);
  *(undefined ***)((int)this + 0x564) = &PTR_LAB_004cb514;
  *(undefined ***)((int)this + 0x540) = &PTR_FUN_004cbd74;
  FUN_004b7c10((int)this + 0x544);
  *(undefined ***)((int)this + 0x540) = &PTR_LAB_004cb514;
  *(undefined ***)((int)this + 0x51c) = &PTR_FUN_004cbd64;
  FUN_004b7c10((int)this + 0x520);
  *(undefined ***)((int)this + 0x51c) = &PTR_LAB_004cb514;
  FUN_00417220((undefined4 *)((int)this + 0x4f8));
  FUN_00417200((undefined4 *)((int)this + 0x4d4));
  FUN_004171e0((undefined4 *)((int)this + 0x4b0));
  FUN_004171c0((undefined4 *)((int)this + 0x48c));
  FUN_004171a0((undefined4 *)((int)this + 0x468));
  FUN_00417180((undefined4 *)((int)this + 0x444));
  FUN_00417160((undefined4 *)((int)this + 0x420));
  FUN_004142b0((undefined4 *)((int)this + 0x3fc));
  *(undefined4 *)((int)this + 0x340) = &PTR_LAB_004cbcc4;
  FUN_00468190((undefined4 *)((int)this + 0x340),0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0x32c) = &PTR_LAB_004cbc94;
  FUN_00468190((undefined4 *)((int)this + 0x32c),0,&DAT_004ecc58);
  thunk_FUN_00446310((undefined4 *)((int)this + 0x2a0));
  thunk_FUN_004a3950((int)this + 0x21c);
  *(undefined4 *)((int)this + 0x1f8) = &PTR_LAB_004cbc64;
  FUN_004145b0((undefined4 *)((int)this + 0x1f8),0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0x1e4) = &PTR_LAB_004cbb50;
  FUN_0040c870((undefined4 *)((int)this + 0x1e4),0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0x1d0) = &PTR_LAB_004cbc34;
  FUN_00468190((undefined4 *)((int)this + 0x1d0),0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0x1bc) = &PTR_LAB_004cbc04;
  FUN_00468190((undefined4 *)((int)this + 0x1bc),0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0x1a8) = &PTR_LAB_004cbbd4;
  FUN_00417240((undefined4 *)((int)this + 0x1a8),0,&DAT_004ecc58);
  *(undefined ***)this = &PTR_LAB_004cbdcc;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00415540 size=30 */

int __fastcall FUN_00415540(int param_1)

{
  *(undefined ***)(param_1 + 0x18) = &PTR_FUN_004cbe64;
  FUN_004b7b90((uint *)(param_1 + 0x1c),0x14,0x20);
  return param_1;
}


/* 00415970 size=509 */

void __cdecl FUN_00415970(int param_1)

{
  undefined4 *puVar1;
  ushort uVar2;
  int iVar3;
  int *piVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  uint uVar8;
  undefined4 *puVar9;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  int local_c;
  int local_8;
  float *local_4;
  
  iVar3 = *(int *)(param_1 + 0x78);
  for (piVar4 = *(int **)(iVar3 + 0xf4); piVar4 != (int *)0x0; piVar4 = (int *)piVar4[4]) {
    local_4 = (float *)piVar4[1];
    local_8 = *piVar4;
    local_30 = *local_4;
    local_2c = local_4[1];
    local_28 = local_4[2];
    local_24 = local_4[3];
    local_20 = local_4[4];
    local_1c = local_4[5];
    local_18 = local_4[6];
    local_14 = local_4[7];
    local_10 = local_4[8];
    local_c = iVar3;
    (**(code **)(piVar4[3] + 4))(&local_30,piVar4[2]);
    pfVar5 = (float *)piVar4[1];
    *pfVar5 = local_30;
    pfVar5[1] = local_2c;
    pfVar5[2] = local_28;
    pfVar5[3] = local_24;
    pfVar5[4] = local_20;
    pfVar5[5] = local_1c;
    pfVar5[6] = local_18;
    pfVar5[7] = local_14;
    pfVar5[8] = local_10;
    uVar2 = *(ushort *)(pfVar5 + 0xe);
    while (uVar2 != 0xffff) {
      iVar6 = *(int *)(*(int *)(*piVar4 + 0xa0) + (uint)uVar2 * 4);
      puVar9 = (undefined4 *)(iVar6 + 0x58);
      if (*(undefined4 **)(iVar6 + 0x50) == puVar9) {
        uVar8 = (uint)*(ushort *)(iVar6 + 0x54);
      }
      else {
        uVar8 = (uint)*(ushort *)(iVar6 + 0x56) + (uint)*(ushort *)(iVar6 + 0x54);
      }
      puVar1 = puVar9 + uVar8 * 6;
      for (; puVar9 != puVar1; puVar9 = puVar9 + 6) {
        pfVar7 = (float *)*puVar9;
        puVar9[1] = (pfVar5[3] * *pfVar7 + pfVar5[4] * pfVar7[1] + pfVar5[5] * pfVar7[2]) -
                    (local_24 * local_30 + local_1c * local_28 + local_20 * local_2c);
        puVar9[2] = (pfVar5[6] * *pfVar7 + pfVar5[7] * pfVar7[1] + pfVar5[8] * pfVar7[2]) -
                    (local_18 * local_30 + local_10 * local_28 + local_14 * local_2c);
      }
      uVar2 = *(ushort *)(iVar6 + 0x44);
    }
  }
  return;
}


/* 00415c00 size=41 */

void __fastcall FUN_00415c00(int param_1)

{
  int iVar1;
  
  iVar1 = 0x410;
  do {
    FUN_00412f90(*(int *)(param_1 + 0x78),iVar1 + *(int *)(param_1 + 0x78),1);
    iVar1 = iVar1 + 0x10;
  } while (iVar1 < 0x4c0);
  return;
}


/* 00416440 size=60 */

void __cdecl FUN_00416440(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_2 + 400) != 0) {
    do {
      clientshell_416480(param_1,*(int *)(*(int *)(*(int *)(param_2 + 0x18c) + uVar1 * 4) + 4));
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_2 + 400));
  }
  return;
}


/* 004165b0 size=51 */

void __cdecl FUN_004165b0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x78);
  for (iVar1 = *(int *)(param_2 + 8); iVar1 != param_2 + 4; iVar1 = *(int *)(iVar1 + 4)) {
    FUN_004a3df0((void *)(iVar2 + 0x6c),*(int **)(iVar1 + 8));
  }
  return;
}


/* 004165f0 size=28 */

void __cdecl FUN_004165f0(int param_1)

{
  FUN_00416610(param_1);
  FUN_00415c00(param_1);
  FUN_00416630(param_1);
  return;
}


/* 00416610 size=28 */

void __fastcall FUN_00416610(int param_1)

{
  if (*(int *)(param_1 + 0x7c) != 0) {
    FUN_00410b00(*(int *)(param_1 + 0x78));
  }
  *(undefined4 *)(param_1 + 0x7c) = 0;
  return;
}


/* 00416630 size=194 */

void __fastcall FUN_00416630(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_4;
  
  iVar3 = 0x410;
  do {
    FUN_00416700(param_1,*(int *)(param_1 + 0x78) + iVar3);
    iVar3 = iVar3 + 0x10;
  } while (iVar3 < 0x4c0);
  local_4 = 0;
  do {
    iVar3 = *(int *)(param_1 + 0x78);
    for (iVar1 = *(int *)(iVar3 + 0x418 + local_4); iVar1 != iVar3 + 0x414 + local_4;
        iVar1 = *(int *)(iVar1 + 4)) {
      iVar2 = *(int *)(iVar1 + 8);
      FUN_0045ea90(iVar2);
      FUN_0045ead0(iVar2);
    }
    local_4 = local_4 + 0x10;
  } while (local_4 < 0xb0);
  FUN_00412f90(*(int *)(param_1 + 0x78),*(int *)(param_1 + 0x78) + 0x430,0);
  FUN_00412f90(*(int *)(param_1 + 0x78),*(int *)(param_1 + 0x78) + 0x4a0,0);
  FUN_00416b50(param_1);
  FUN_00412fe0(*(int *)(param_1 + 0x78));
  FUN_00497a60(*(int *)(param_1 + 0x78) + 0x784);
  FUN_0042be60(*(int *)(param_1 + 0x78));
  return;
}


/* 00416700 size=34 */

void __cdecl FUN_00416700(undefined4 param_1,int param_2)

{
  int iVar1;
  
  for (iVar1 = *(int *)(param_2 + 8); iVar1 != param_2 + 4; iVar1 = *(int *)(iVar1 + 4)) {
    (**(code **)(**(int **)(iVar1 + 8) + 8))();
  }
  return;
}


/* 00416730 size=842 */

undefined4 __fastcall FUN_00416730(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  uint local_3dc;
  undefined4 local_3d4;
  int local_3d0 [2];
  undefined2 local_3c8;
  undefined4 local_3c4 [12];
  undefined2 *local_394;
  undefined4 local_390;
  undefined2 local_38c;
  undefined2 local_38a;
  undefined4 local_388;
  undefined4 local_384;
  undefined4 local_380;
  undefined4 local_37c;
  undefined4 local_378;
  undefined4 local_374;
  undefined4 local_370;
  undefined4 local_36c;
  undefined4 local_368;
  undefined4 local_364;
  undefined4 local_360;
  undefined4 local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined1 local_34c;
  char local_30c [127];
  undefined1 local_28d;
  undefined1 local_28c [512];
  undefined1 local_8c;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_00416a80(&local_38c);
  puVar4 = local_3c4;
  local_3d0[0] = 0;
  local_3d0[1] = 0;
  local_3c8 = 0;
  iVar5 = 4;
  do {
    FUN_00416b00(puVar4);
    puVar4 = puVar4 + 3;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  local_394 = &local_38c;
  local_390 = 1;
  iVar5 = FUN_00416dd0(param_1);
  local_3dc = 0;
  if (*(int *)(iVar5 + 400) != 0) {
    do {
      iVar2 = *(int *)(*(int *)(iVar5 + 0x18c) + local_3dc * 4);
      uVar6 = *(uint *)(*(int *)(iVar2 + 4) + 0x48);
      if ((uVar6 & 8) == 0) {
        if ((uVar6 & 0x30) != 0) {
          local_38c = 0;
          local_38a = 0;
          local_388 = 1;
          local_384 = 0;
          local_380 = 0;
          local_37c = 0;
          local_378 = 0;
          local_374 = 0;
          local_370 = 0;
          local_36c = 0x3f800000;
          local_368 = 0x3f800000;
          local_364 = 0x3f800000;
          FUN_00402fd0(&local_360,0,0,0,0x3f800000);
          local_350 = 0;
          local_34c = 0;
          local_30c[0] = '\0';
          puVar1 = local_28c;
          iVar3 = 4;
          do {
            *puVar1 = 0;
            puVar1 = puVar1 + 0x80;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          local_8c = 0;
          local_c = 0;
          local_8 = 0;
          local_4 = 1;
          local_38c = 2;
          local_384 = 0x3001;
          _strncpy(local_30c,(char *)(*(int *)(iVar2 + 0xc) + 4),0x7f);
          local_28d = 0;
          iVar2 = *(int *)(iVar2 + 4);
          local_378 = *(undefined4 *)(iVar2 + 0xe8);
          local_374 = *(undefined4 *)(iVar2 + 0xec);
          local_370 = *(undefined4 *)(iVar2 + 0xf0);
          iVar2 = FUN_00412d80(*(int *)(param_1 + 0x78),0xffff,local_3d0,&local_3d4,1,0);
          if (iVar2 != 0) {
            return 0;
          }
        }
      }
      else {
        uVar6 = 0;
        if (*(int *)(*(int *)(iVar2 + 4) + 0x140) != 0) {
          do {
            local_38a = 0;
            local_388 = 1;
            local_380 = 0;
            local_37c = 0;
            local_378 = 0;
            local_374 = 0;
            local_370 = 0;
            local_36c = 0x3f800000;
            local_368 = 0x3f800000;
            local_364 = 0x3f800000;
            local_360 = 0;
            local_35c = 0;
            local_358 = 0;
            local_354 = 0x3f800000;
            local_350 = 0;
            local_34c = 0;
            local_30c[0] = '\0';
            puVar1 = local_28c;
            iVar3 = 4;
            do {
              *puVar1 = 0;
              puVar1 = puVar1 + 0x80;
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            local_8c = 0;
            local_c = 0;
            local_8 = 0;
            local_4 = 1;
            local_38c = 2;
            local_384 = 0x3000;
            iVar3 = FUN_00428d70((char *)(*(int *)(iVar2 + 4) + 4),uVar6,local_30c,0x80);
            if (iVar3 == 0) {
              return 0;
            }
            iVar3 = FUN_00412d80(*(int *)(param_1 + 0x78),0xffff,local_3d0,&local_3d4,0,0);
            if (iVar3 != 0) {
              return 0;
            }
            uVar6 = uVar6 + 1;
          } while (uVar6 < *(uint *)(*(int *)(iVar2 + 4) + 0x140));
        }
      }
      local_3dc = local_3dc + 1;
    } while (local_3dc < *(uint *)(iVar5 + 400));
  }
  return 1;
}


/* 00416a80 size=125 */

void __fastcall FUN_00416a80(undefined2 *param_1)

{
  undefined2 *puVar1;
  int iVar2;
  
  *(undefined4 *)(param_1 + 2) = 1;
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 6) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 10) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0xe) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x12) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x14) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x16) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1a) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1e) = 0;
  *(undefined1 *)(param_1 + 0x20) = 0;
  *(undefined1 *)(param_1 + 0x40) = 0;
  puVar1 = param_1 + 0x80;
  iVar2 = 4;
  do {
    *(undefined1 *)puVar1 = 0;
    puVar1 = puVar1 + 0x40;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  *(undefined1 *)(param_1 + 0x180) = 0;
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  *(undefined4 *)(param_1 + 0x1c2) = 0;
  *(undefined4 *)(param_1 + 0x1c4) = 1;
  return;
}


/* 00416b00 size=14 */

void __fastcall FUN_00416b00(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined2 *)(param_1 + 2) = 0;
  return;
}


/* 00416b10 size=63 */

/* FUN_00416b10: lifted from original x86 -> lt_lifted.c */


/* 00416b50 size=36 */

/* FUN_00416b50: lifted from original x86 -> lt_lifted.c */


/* 00416b80 size=33 */

void __cdecl FUN_00416b80(undefined4 param_1)

{
  int *piVar1;
  
  if ((DAT_004e5174 != 0) &&
     (piVar1 = *(int **)(*(int *)(DAT_004e5174 + 0x78) + 0x620), piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x24))(param_1);
  }
  return;
}


/* 00416bb0 size=28 */

void FUN_00416bb0(void)

{
  if (DAT_004e5174 != 0) {
    *(undefined2 *)(DAT_004e5174 + 0x6c) = 0xffff;
    FUN_004165f0(DAT_004e5174);
  }
  return;
}


/* 00416bd0 size=12 */

undefined4 FUN_00416bd0(void)

{
  return *(undefined4 *)(DAT_004e516c + 0x12e8);
}


/* 00416be0 size=179 */

void __cdecl FUN_00416be0(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  int local_c [2];
  undefined2 local_4;
  
  local_c[1] = 0;
  if (DAT_004e98c8 == 0) {
    local_c[0] = 2;
    local_4 = *(undefined2 *)(param_1 + 0x1c);
    piVar1 = FUN_004047a0(*(int *)(DAT_004e516c + 0x1644),local_c,'\x01');
    if ((piVar1 != (int *)0x0) && (*piVar1 == 0)) {
      *piVar1 = param_1;
      puVar2 = FUN_00445fe0(&PTR_LAB_004d6570,piVar1);
      FUN_00446060((int *)(param_1 + 0x14),(int)puVar2);
      if (0 < DAT_004e4420) {
        puVar3 = FUN_004046f0(*(int *)(DAT_004e516c + 0x1644),local_c);
        FUN_00436670((byte *)s_Client_inherited_model__s_from_s_004d68e4,puVar3);
      }
    }
  }
  return;
}


/* 00416ca0 size=20 */

void FUN_00416ca0(void)

{
  if (DAT_004e5174 != 0) {
    FUN_0043c4b0();
  }
  return;
}


/* 00416cc0 size=68 */

void FUN_00416cc0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (DAT_004e516c != 0) {
    iVar1 = DAT_004e516c + 0x424;
    for (iVar2 = *(int *)(DAT_004e516c + 0x428); iVar2 != iVar1; iVar2 = *(int *)(iVar2 + 4)) {
      iVar3 = *(int *)(*(int *)(iVar2 + 8) + 0x1f8);
      if ((*(int *)(*(int *)(iVar2 + 8) + 400) == 0) && (iVar3 != 0)) {
        *(uint *)(iVar3 + 0x20) = *(uint *)(iVar3 + 0x20) | 1;
      }
    }
  }
  return;
}


/* 00416d10 size=187 */

undefined4 * __thiscall FUN_00416d10(void *this,undefined4 param_1)

{
  uint *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  iVar2 = FUN_00434ec0(*(int **)((int)this + 0x8c),&param_1,2);
  if ((iVar2 != 0) && (puVar3 = (undefined4 *)FUN_00434fd0(iVar2), puVar3 != (undefined4 *)0x0)) {
    return puVar3;
  }
  iVar2 = DAT_004e516c;
  puVar3 = *(undefined4 **)(DAT_004e516c + 0x1248);
  puVar1 = (uint *)(DAT_004e516c + 0x1230);
  if (puVar3 == (undefined4 *)0x0) {
    FUN_004b7c60((int)puVar1,*(int *)(DAT_004e516c + 0x1238));
    puVar3 = *(undefined4 **)(iVar2 + 0x1248);
    if (puVar3 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
  }
  *(undefined4 *)(iVar2 + 0x1248) = *puVar3;
  uVar6 = *puVar1;
  puVar7 = puVar3;
  for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar7 = 0;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  if (puVar3 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  piVar4 = FUN_00434d70(*(int **)((int)this + 0x8c),&param_1,2);
  if (piVar4 == (int *)0x0) {
    FUN_00430fe0((undefined *)puVar3);
    return (undefined4 *)0x0;
  }
  FUN_00434fe0((int)piVar4,puVar3);
  return puVar3;
}


/* 00416dd0 size=4 */

undefined4 __fastcall FUN_00416dd0(int param_1)

{
  return *(undefined4 *)(param_1 + 0x78);
}


/* 00416de0 size=111 */

undefined4 * __fastcall FUN_00416de0(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cbe24;
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
  return param_1;
}


/* 00416e90 size=288 */

void __thiscall FUN_00416e90(void *this,uint param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  
  if ((uint)(*(int *)((int)this + 0x10) * 2) <= *(uint *)((int)this + 0xc)) {
    iVar5 = *(int *)((int)this + 0x10) + -1 + *(int *)((int)this + 8);
    iVar1 = (**(code **)(DAT_004ecc58 + 4))(iVar5 * 8);
    if ((iVar1 != 0) || (iVar1 = 0, iVar5 == 0)) {
      uVar2 = 0;
      if (param_1 != 0) {
        do {
          iVar5 = *(int *)((int)this + 4);
          uVar2 = uVar2 + 1;
          *(undefined4 *)(iVar1 + -8 + uVar2 * 8) = *(undefined4 *)(iVar5 + -8 + uVar2 * 8);
          *(undefined4 *)(iVar1 + -4 + uVar2 * 8) = *(undefined4 *)(iVar5 + -4 + uVar2 * 8);
        } while (uVar2 < param_1);
      }
      if (param_1 < *(int *)((int)this + 8) - 1U) {
        puVar3 = (undefined4 *)(iVar1 + param_1 * 8);
        do {
          puVar4 = puVar3 + 2;
          iVar5 = *(int *)((int)this + 4) + (8 - iVar1);
          param_1 = param_1 + 1;
          *puVar3 = *(undefined4 *)(iVar5 + -8 + (int)puVar4);
          puVar3[1] = *(undefined4 *)(iVar5 + -4 + (int)puVar4);
          puVar3 = puVar4;
        } while (param_1 < *(int *)((int)this + 8) - 1U);
      }
      iVar5 = *(int *)((int)this + 4);
      if (iVar5 != 0) {
        if (iVar5 != 0) {
          (**(code **)(DAT_004ecc58 + 8))(iVar5);
        }
        *(undefined4 *)((int)this + 4) = 0;
      }
      *(undefined4 *)((int)this + 0xc) = 0;
      *(int *)((int)this + 4) = iVar1;
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
      *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
      return;
    }
  }
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if (param_1 < *(int *)((int)this + 8) - 1U) {
    do {
      iVar5 = *(int *)((int)this + 4);
      param_1 = param_1 + 1;
      *(undefined4 *)(iVar5 + -8 + param_1 * 8) = *(undefined4 *)(iVar5 + param_1 * 8);
      *(undefined4 *)(iVar5 + -4 + param_1 * 8) = *(undefined4 *)(iVar5 + 4 + param_1 * 8);
    } while (param_1 < *(int *)((int)this + 8) - 1U);
  }
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
  return;
}


/* 00416fb0 size=297 */

undefined4 __thiscall FUN_00416fb0(void *this,int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 uStack_10;
  undefined1 auStack_8 [8];
  
  iVar2 = (**(code **)(*param_1 + 0x1c))();
  if ((iVar2 != *(int *)((int)this + 8)) || (iVar2 == 0)) {
    if (*(int *)((int)this + 4) != 0) {
      FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 4));
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    *(int *)((int)this + 8) = iVar2;
    if (iVar2 != 0) {
      iVar2 = FUN_00417590(&DAT_004ecc58,0,*(int *)((int)this + 0x10) + iVar2);
      *(int *)((int)this + 4) = iVar2;
      if (iVar2 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  uVar4 = 0;
  iVar2 = (**(code **)*param_1)(auStack_8);
  uStack_10 = *(undefined4 *)(iVar2 + 4);
  iVar2 = (**(code **)(*param_1 + 4))(auStack_8 + -0xc);
  while( true ) {
    if (iVar2 == 0) {
      return 1;
    }
    if (*(uint *)((int)this + 8) <= uVar4) break;
    puVar1 = (undefined4 *)(*(int *)((int)this + 4) + uVar4 * 8);
    puVar3 = (undefined4 *)(**(code **)(*param_1 + 8))(&uStack_10,auStack_8 + -0x10);
    uVar4 = uVar4 + 1;
    *puVar1 = *puVar3;
    puVar1[1] = puVar3[1];
    iVar2 = (**(code **)(*param_1 + 4))(auStack_8 + -0x18);
  }
  if (*(int *)((int)this + 4) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(undefined4 *)((int)this + 8) = 0;
  return 0;
}


/* 00417130 size=44 */

void __thiscall FUN_00417130(void *this,undefined4 *param_1)

{
  if ((int *)param_1[0xb] != (int *)0x0) {
    (**(code **)(*(int *)param_1[0xb] + 8))();
  }
  if ((param_1 != (undefined4 *)0x0) && (this != (void *)0xfffffffc)) {
    *param_1 = *(undefined4 *)((int)this + 0x1c);
    *(undefined4 **)((int)this + 0x1c) = param_1;
  }
  return;
}


/* 00417160 size=31 */

void __fastcall FUN_00417160(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbcf4;
  FUN_004b7c10((int)(param_1 + 1));
  *param_1 = &PTR_LAB_004cb514;
  return;
}


/* 00417180 size=31 */

void __fastcall FUN_00417180(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbd04;
  FUN_004b7c10((int)(param_1 + 1));
  *param_1 = &PTR_LAB_004cb514;
  return;
}


/* 004171a0 size=31 */

void __fastcall FUN_004171a0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbd14;
  FUN_004b7c10((int)(param_1 + 1));
  *param_1 = &PTR_LAB_004cb514;
  return;
}


/* 004171c0 size=31 */

void __fastcall FUN_004171c0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbd24;
  FUN_004b7c10((int)(param_1 + 1));
  *param_1 = &PTR_LAB_004cb514;
  return;
}


/* 004171e0 size=31 */

void __fastcall FUN_004171e0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbd34;
  FUN_004b7c10((int)(param_1 + 1));
  *param_1 = &PTR_LAB_004cb514;
  return;
}


/* 00417200 size=31 */

void __fastcall FUN_00417200(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbd44;
  FUN_004b7c10((int)(param_1 + 1));
  *param_1 = &PTR_LAB_004cb514;
  return;
}


/* 00417220 size=31 */

void __fastcall FUN_00417220(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbd54;
  FUN_004b7c10((int)(param_1 + 1));
  *param_1 = &PTR_LAB_004cb514;
  return;
}


/* 00417240 size=156 */

undefined4 __thiscall FUN_00417240(void *this,int param_1,int *param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar3 = *(int *)((int)this + 4);
    if (iVar3 != 0) {
      if (iVar3 != 0) {
        (**(code **)(*param_2 + 8))(iVar3);
      }
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar3 = param_1 + *(int *)((int)this + 0x10);
      puVar2 = (undefined1 *)(**(code **)(*param_2 + 4))(iVar3 * 0x60);
      puVar1 = puVar2;
      if (puVar2 != (undefined1 *)0x0) {
        for (; iVar3 != 0; iVar3 = iVar3 + -1) {
          if (puVar1 != (undefined1 *)0x0) {
            FUN_00428dc0(puVar1);
          }
          puVar1 = puVar1 + 0x60;
        }
      }
      *(undefined1 **)((int)this + 4) = puVar2;
      if (puVar2 == (undefined1 *)0x0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 00417300 size=134 */

undefined4 __thiscall FUN_00417300(void *this,int param_1,int *param_2)

{
  int iVar1;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = (**(code **)(*param_2 + 4))((param_1 + *(int *)((int)this + 0x10)) * 8);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      *(int *)((int)this + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 00417390 size=264 */

undefined4 __thiscall FUN_00417390(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
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
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))((param_1 + *(int *)((int)this + 0x10)) * 8);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  uVar3 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar3 = param_1;
  }
  if (param_1 == 0) {
    uVar2 = 0;
    unaff_retaddr = 0;
    if (uVar3 == 0) goto LAB_00417453;
    do {
      iVar4 = *(int *)((int)this + 4);
      uVar2 = uVar2 + 1;
      puVar1[uVar2 * 2 + -2] = *(undefined4 *)(iVar4 + -8 + uVar2 * 8);
      puVar1[uVar2 * 2 + -1] = *(undefined4 *)(iVar4 + -4 + uVar2 * 8);
    } while (uVar2 < uVar3);
  }
  else {
    puVar5 = *(undefined4 **)((int)this + 4);
    puVar6 = puVar1;
    for (iVar4 = (uVar3 & 0x1fffffff) << 1; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
  }
  param_3 = param_2;
LAB_00417453:
  iVar4 = *(int *)((int)this + 4);
  if (iVar4 != 0) {
    if (iVar4 != 0) {
      (**(code **)(*param_3 + 8))(iVar4);
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 **)((int)this + 4) = puVar1;
  *(undefined4 *)((int)this + 8) = unaff_retaddr;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  return 1;
}


/* 004174a0 size=29 */

undefined4 * __fastcall FUN_004174a0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbe54;
  FUN_004b7b90(param_1 + 1,0x5c,0x20);
  return param_1;
}


/* 004174e0 size=52 */

undefined4 * __thiscall FUN_004174e0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbe64;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00417520 size=52 */

undefined4 * __thiscall FUN_00417520(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbe54;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00417590 size=22 */

int __cdecl FUN_00417590(int *param_1,undefined4 param_2,int param_3)

{
  (**(code **)(*param_1 + 4))(param_3 << 3);
  return;
}


/* 004175b0 size=1016 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004175b0: lifted from original x86 -> lt_lifted.c */


/* 004179f0 size=18 */

int __thiscall FUN_004179f0(void *this,undefined4 param_1)

{
  *(undefined ***)this = &PTR_LAB_004cbe74;
  *(undefined4 *)((int)this + 4) = param_1;
  return;
}


/* 00417b20 size=25 */

undefined4 * __fastcall FUN_00417b20(undefined4 *param_1)

{
  FUN_0044e360(param_1);
  *param_1 = &PTR_FUN_004cbe84;
  param_1[0x18] = 0;
  return param_1;
}


/* 00417b40 size=15 */

undefined4 __thiscall FUN_00417b40(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 0x60) = param_1;
  return 1;
}


/* 00417b50 size=175 */

undefined4 __thiscall FUN_00417b50(void *this,int param_1)

{
  LPCRITICAL_SECTION p_Var1;
  LPCRITICAL_SECTION p_Var2;
  int *piVar3;
  uint uVar4;
  
  p_Var1 = (LPCRITICAL_SECTION)((int)this + 4);
  FUN_0044df50(p_Var1);
  p_Var2 = (LPCRITICAL_SECTION)((int)this + 0x2c);
  FUN_0044df50(p_Var2);
  if (*(int *)((int)this + 0x60) == 0) {
LAB_00417be7:
    FUN_0044df60(p_Var2);
    FUN_0044df60(p_Var1);
    return 0;
  }
  uVar4 = *(uint *)((int)this + 0x24);
  do {
    if (uVar4 == 0) {
      uVar4 = *(uint *)((int)this + 0x4c);
      goto joined_r0x00417ba8;
    }
    piVar3 = (int *)(uVar4 + 0x14);
    uVar4 = *(uint *)(uVar4 + 4) & -(uint)(*(uint *)(uVar4 + 4) != *(uint *)((int)this + 0x24));
  } while (*piVar3 != param_1);
LAB_00417bce:
  FUN_0044df60(p_Var2);
  FUN_0044df60(p_Var1);
  return 1;
  while (piVar3 = (int *)(uVar4 + 0x14),
        uVar4 = *(uint *)(uVar4 + 4) & -(uint)(*(uint *)(uVar4 + 4) != *(uint *)((int)this + 0x4c)),
        *piVar3 != param_1) {
joined_r0x00417ba8:
    if (uVar4 == 0) goto LAB_00417be7;
  }
  goto LAB_00417bce;
}


/* 00417d00 size=141 */

void __thiscall
FUN_00417d00(void *this,undefined4 param_1,int *param_2,undefined4 *param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)((int)this + 4) + 0x508);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0x18) = *param_3;
    *(undefined4 *)(iVar2 + 0x1c) = param_3[1];
    *(undefined4 *)(iVar2 + 0x20) = param_3[2];
    *(int **)(*(int *)(*(int *)((int)this + 4) + 0x508) + 0x10) = param_2;
    if (param_2 != (int *)0x0) {
      iVar2 = (**(code **)(*param_2 + 0x34))();
      if (((iVar2 == 0) && ((char)param_2[0x2f] != '\x02')) && ((char)param_2[0x2f] != '\t')) {
        *(undefined4 *)(*(int *)(*(int *)((int)this + 4) + 0x508) + 0x14) = 0xffffffff;
      }
    }
    piVar1 = *(int **)(*(int *)((int)this + 4) + 0x620);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x58))
                (param_1,*(undefined4 *)(*(int *)((int)this + 4) + 0x508),param_4);
    }
  }
  return;
}


