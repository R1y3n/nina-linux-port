/* lithtech.exe decompilation - unnamed_00454000 */
#include "ghidra_types.h"

/* 00454ef0 size=256 */

/* WARNING: Removing unreachable block (ram,0x00454fbb) */

undefined4 __thiscall FUN_00454ef0(void *this,undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  uVar1 = *(uint *)((int)this + 8);
  if (*(int *)((int)this + 0xc) != 0) {
    *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
    *(undefined4 *)(*(int *)((int)this + 4) + uVar1 * 4) = *param_1;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    return 1;
  }
  iVar3 = FUN_00457040(&DAT_004ecc58,0,*(int *)((int)this + 0x10) + 1 + uVar1);
  if (iVar3 == 0) {
    return 0;
  }
  uVar4 = 0;
  if (uVar1 != 0) {
    do {
      uVar4 = uVar4 + 1;
      *(undefined4 *)(iVar3 + -4 + uVar4 * 4) =
           *(undefined4 *)(*(int *)((int)this + 4) + -4 + uVar4 * 4);
    } while (uVar4 < uVar1);
  }
  if (uVar1 < *(uint *)((int)this + 8)) {
    uVar4 = uVar1;
    puVar5 = (undefined4 *)(iVar3 + 4 + uVar1 * 4);
    do {
      uVar4 = uVar4 + 1;
      *puVar5 = *(undefined4 *)(*(int *)((int)this + 4) + -4 + uVar4 * 4);
      puVar5 = puVar5 + 1;
    } while (uVar4 < *(uint *)((int)this + 8));
  }
  *(undefined4 *)(iVar3 + uVar1 * 4) = *param_1;
  iVar2 = *(int *)((int)this + 4);
  if (iVar2 != 0) {
    if (iVar2 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar2);
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  *(int *)((int)this + 4) = iVar3;
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
  return 1;
}


/* 00454ff0 size=248 */

void __thiscall FUN_00454ff0(void *this,uint param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if ((uint)(*(int *)((int)this + 0x10) * 2) <= *(uint *)((int)this + 0xc)) {
    iVar1 = *(int *)((int)this + 0x10) + -1 + *(int *)((int)this + 8);
    iVar2 = FUN_00457040(&DAT_004ecc58,0,iVar1);
    if ((iVar2 != 0) || (iVar1 == 0)) {
      uVar3 = 0;
      if (param_1 != 0) {
        do {
          uVar3 = uVar3 + 1;
          *(undefined4 *)(iVar2 + -4 + uVar3 * 4) =
               *(undefined4 *)(*(int *)((int)this + 4) + -4 + uVar3 * 4);
        } while (uVar3 < param_1);
      }
      if (param_1 < *(int *)((int)this + 8) - 1U) {
        puVar4 = (undefined4 *)(iVar2 + param_1 * 4);
        do {
          param_1 = param_1 + 1;
          *puVar4 = *(undefined4 *)((int)puVar4 + *(int *)((int)this + 4) + (4 - iVar2));
          puVar4 = puVar4 + 1;
        } while (param_1 < *(int *)((int)this + 8) - 1U);
      }
      iVar1 = *(int *)((int)this + 4);
      if (iVar1 != 0) {
        if (iVar1 != 0) {
          (**(code **)(DAT_004ecc58 + 8))(iVar1);
        }
        *(undefined4 *)((int)this + 4) = 0;
      }
      *(undefined4 *)((int)this + 0xc) = 0;
      *(int *)((int)this + 4) = iVar2;
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
      *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
      return;
    }
  }
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if (param_1 < *(int *)((int)this + 8) - 1U) {
    do {
      param_1 = param_1 + 1;
      *(undefined4 *)(*(int *)((int)this + 4) + -4 + param_1 * 4) =
           *(undefined4 *)(*(int *)((int)this + 4) + param_1 * 4);
    } while (param_1 < *(int *)((int)this + 8) - 1U);
  }
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
  return;
}


/* 00455300 size=215 */

void __fastcall FUN_00455300(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint unaff_retaddr;
  
  iVar4 = *(int *)(param_1 + 8) + -1;
  iVar1 = (**(code **)(DAT_004ecc58 + 4))(iVar4 * 4);
  if ((iVar1 == 0) && (iVar1 = 0, iVar4 != 0)) {
    if (unaff_retaddr < *(int *)(param_1 + 8) - 1U) {
      do {
        unaff_retaddr = unaff_retaddr + 1;
        *(undefined4 *)(*(int *)(param_1 + 4) + -4 + unaff_retaddr * 4) =
             *(undefined4 *)(*(int *)(param_1 + 4) + unaff_retaddr * 4);
      } while (unaff_retaddr < *(int *)(param_1 + 8) - 1U);
    }
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
    return;
  }
  uVar2 = 0;
  if (unaff_retaddr != 0) {
    do {
      uVar2 = uVar2 + 1;
      *(undefined4 *)(iVar1 + -4 + uVar2 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 4) + -4 + uVar2 * 4);
    } while (uVar2 < unaff_retaddr);
  }
  if (unaff_retaddr < *(int *)(param_1 + 8) - 1U) {
    puVar3 = (undefined4 *)(iVar1 + unaff_retaddr * 4);
    do {
      unaff_retaddr = unaff_retaddr + 1;
      *puVar3 = *(undefined4 *)((int)puVar3 + *(int *)(param_1 + 4) + (4 - iVar1));
      puVar3 = puVar3 + 1;
    } while (unaff_retaddr < *(int *)(param_1 + 8) - 1U);
  }
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)(DAT_004ecc58 + 8))(*(int *)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
  }
  *(int *)(param_1 + 4) = iVar1;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  return;
}


/* 00455870 size=57 */

void __thiscall FUN_00455870(void *this,undefined4 *param_1)

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


/* 004558b0 size=108 */

undefined4 __thiscall FUN_004558b0(void *this,int param_1,int *param_2)

{
  int iVar1;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = (**(code **)(*param_2 + 4))(param_1 * 0x1c);
      *(int *)((int)this + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  return 1;
}


/* 00455920 size=290 */

undefined4 __thiscall FUN_00455920(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *unaff_EBP;
  int *piVar6;
  uint unaff_retaddr;
  
  uVar3 = *(uint *)((int)this + 8);
  if (uVar3 <= param_1) {
    if (uVar3 < param_1) {
      if (param_1 <= uVar3) {
        *(uint *)((int)this + 8) = param_1;
        return 1;
      }
    }
    else if (param_1 == uVar3) {
      return 1;
    }
    puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 * 0x1c);
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    uVar3 = *(uint *)((int)this + 8);
    if (param_1 < *(uint *)((int)this + 8)) {
      uVar3 = param_1;
    }
    if (param_1 == 0) {
      piVar6 = param_3;
      if (uVar3 != 0) {
        puVar5 = puVar1 + 5;
        param_1 = uVar3;
        do {
          puVar2 = (undefined4 *)(*(int *)((int)this + 4) + (-0x14 - (int)puVar1) + (int)puVar5);
          puVar5[-5] = *puVar2;
          puVar5[-4] = puVar2[1];
          puVar5[-3] = puVar2[2];
          puVar5[-2] = puVar2[3];
          puVar5[-1] = puVar2[4];
          *puVar5 = puVar2[5];
          puVar5[1] = puVar2[6];
          param_1 = param_1 - 1;
          puVar5 = puVar5 + 7;
        } while (param_1 != 0);
        param_1 = unaff_retaddr;
        piVar6 = param_2;
      }
    }
    else {
      puVar5 = *(undefined4 **)((int)this + 4);
      puVar2 = puVar1;
      for (uVar3 = uVar3 * 0x1c >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar2 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar2 = puVar2 + 1;
      }
      for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
        *(undefined1 *)puVar2 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        puVar2 = (undefined4 *)((int)puVar2 + 1);
      }
      piVar6 = param_2;
    }
    if (*(int *)((int)this + 4) != 0) {
      (**(code **)(*piVar6 + 8))(*(int *)((int)this + 4));
      *(undefined4 *)((int)this + 4) = 0;
      puVar1 = unaff_EBP;
    }
    *(undefined4 **)((int)this + 4) = puVar1;
  }
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 00455a50 size=103 */

undefined4 __thiscall FUN_00455a50(void *this,int param_1,int *param_2)

{
  int iVar1;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = (**(code **)(*param_2 + 4))(param_1 * 4);
      *(int *)((int)this + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  return 1;
}


/* 00455ac0 size=237 */

undefined4 __thiscall FUN_00455ac0(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  
  uVar6 = *(uint *)((int)this + 8);
  if (uVar6 <= param_1) {
    if (uVar6 < param_1) {
      if (param_1 <= uVar6) {
        *(uint *)((int)this + 8) = param_1;
        return 1;
      }
    }
    else if (param_1 == uVar6) {
      return 1;
    }
    puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 * 0x14);
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    if (param_1 != 0) {
      puVar4 = puVar1;
      uVar6 = param_1;
      do {
        if (puVar4 != (undefined4 *)0x0) {
          FUN_0044f950(puVar4);
        }
        puVar4 = puVar4 + 5;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
    uVar6 = *(uint *)((int)this + 8);
    if (param_1 < *(uint *)((int)this + 8)) {
      uVar6 = param_1;
    }
    if (param_1 == 0) {
      if (uVar6 != 0) {
        iVar2 = 0;
        do {
          puVar5 = (undefined4 *)(*(int *)((int)this + 4) + iVar2);
          puVar4 = (undefined4 *)(iVar2 + (int)puVar1);
          iVar2 = iVar2 + 0x14;
          uVar6 = uVar6 - 1;
          for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar4 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar4 = puVar4 + 1;
          }
        } while (uVar6 != 0);
      }
    }
    else {
      puVar4 = *(undefined4 **)((int)this + 4);
      puVar5 = puVar1;
      for (uVar6 = uVar6 * 0x14 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
    }
    if (*(int *)((int)this + 4) != 0) {
      (**(code **)(*param_2 + 8))(*(int *)((int)this + 4));
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(undefined4 **)((int)this + 4) = puVar1;
  }
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 00455bb0 size=360 */

undefined4 __thiscall FUN_00455bb0(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *unaff_EBP;
  int *piVar7;
  uint unaff_retaddr;
  
  uVar4 = *(uint *)((int)this + 8);
  if (param_1 < uVar4) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = *(int *)((int)this + 0xc) + (uVar4 - param_1);
    return 1;
  }
  if ((uVar4 < param_1) && (uVar3 = *(int *)((int)this + 0xc) + uVar4, param_1 <= uVar3)) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = uVar3 - param_1;
    return 1;
  }
  if (param_1 == uVar4) {
    return 1;
  }
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))((param_1 + *(int *)((int)this + 0x10)) * 0x1c);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  uVar4 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar4 = param_1;
  }
  if (param_1 == 0) {
    piVar7 = param_3;
    if (uVar4 != 0) {
      puVar6 = puVar1 + 5;
      param_1 = uVar4;
      do {
        puVar2 = (undefined4 *)(*(int *)((int)this + 4) + (-0x14 - (int)puVar1) + (int)puVar6);
        puVar6[-5] = *puVar2;
        puVar6[-4] = puVar2[1];
        puVar6[-3] = puVar2[2];
        puVar6[-2] = puVar2[3];
        puVar6[-1] = puVar2[4];
        *puVar6 = puVar2[5];
        puVar6[1] = puVar2[6];
        param_1 = param_1 - 1;
        puVar6 = puVar6 + 7;
      } while (param_1 != 0);
      param_1 = unaff_retaddr;
      piVar7 = param_2;
    }
  }
  else {
    puVar6 = *(undefined4 **)((int)this + 4);
    puVar2 = puVar1;
    for (uVar4 = uVar4 * 0x1c >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar2 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar2 = puVar2 + 1;
    }
    for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar2 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar2 = (undefined4 *)((int)puVar2 + 1);
    }
    piVar7 = param_2;
  }
  iVar5 = *(int *)((int)this + 4);
  if (iVar5 != 0) {
    if (iVar5 != 0) {
      (**(code **)(*piVar7 + 8))(iVar5);
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


/* 00455d20 size=179 */

undefined4 __thiscall FUN_00455d20(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint unaff_retaddr;
  
  uVar4 = *(uint *)((int)this + 8);
  if (uVar4 <= param_1) {
    if (uVar4 < param_1) {
      if (param_1 <= uVar4) {
        *(uint *)((int)this + 8) = param_1;
        return 1;
      }
    }
    else if (param_1 == uVar4) {
      return 1;
    }
    puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 * 4);
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    uVar4 = *(uint *)((int)this + 8);
    if (param_1 < *(uint *)((int)this + 8)) {
      uVar4 = param_1;
    }
    if (param_1 == 0) {
      uVar2 = 0;
      unaff_retaddr = param_1;
      param_2 = param_3;
      if (uVar4 != 0) {
        do {
          uVar3 = uVar2 + 1;
          puVar1[uVar2] = *(undefined4 *)(*(int *)((int)this + 4) + -4 + uVar3 * 4);
          uVar2 = uVar3;
        } while (uVar3 < uVar4);
      }
    }
    else {
      puVar5 = *(undefined4 **)((int)this + 4);
      puVar6 = puVar1;
      for (; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
    }
    if (*(int *)((int)this + 4) != 0) {
      (**(code **)(*param_2 + 8))(*(int *)((int)this + 4));
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(undefined4 **)((int)this + 4) = puVar1;
    param_1 = unaff_retaddr;
  }
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 00455de0 size=130 */

undefined4 __thiscall FUN_00455de0(void *this,int param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      puVar2 = (undefined4 *)(**(code **)(*param_2 + 4))(param_1 << 5);
      if (puVar2 != (undefined4 *)0x0) {
        puVar3 = puVar2;
        do {
          if (puVar3 != (undefined4 *)0x0) {
            FUN_0044f800(puVar3);
          }
          puVar3 = puVar3 + 8;
          param_1 = param_1 + -1;
        } while (param_1 != 0);
      }
      *(undefined4 **)((int)this + 4) = puVar2;
      if (puVar2 == (undefined4 *)0x0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  return 1;
}


/* 00455e70 size=238 */

undefined4 __thiscall FUN_00455e70(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint unaff_retaddr;
  
  uVar2 = *(uint *)((int)this + 8);
  if (param_1 < uVar2) goto LAB_00455f4f;
  if (uVar2 < param_1) {
    if (param_1 <= uVar2) {
      *(uint *)((int)this + 8) = param_1;
      return 1;
    }
  }
  else if (param_1 == uVar2) {
    return 1;
  }
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 << 5);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  if (param_1 != 0) {
    puVar5 = puVar1;
    uVar2 = param_1;
    do {
      if (puVar5 != (undefined4 *)0x0) {
        FUN_0044f800(puVar5);
      }
      puVar5 = puVar5 + 8;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  uVar2 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar2 = param_1;
  }
  if (param_1 == 0) {
    if (uVar2 != 0) {
      iVar3 = 0;
      do {
        puVar5 = (undefined4 *)(iVar3 + (int)puVar1);
        puVar6 = (undefined4 *)(*(int *)((int)this + 4) + iVar3);
        iVar3 = iVar3 + 0x20;
        uVar2 = uVar2 - 1;
        for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar5 = puVar5 + 1;
        }
      } while (uVar2 != 0);
      goto LAB_00455f28;
    }
  }
  else {
    puVar5 = *(undefined4 **)((int)this + 4);
    puVar6 = puVar1;
    for (iVar3 = (uVar2 & 0x7ffffff) << 3; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
LAB_00455f28:
    param_1 = unaff_retaddr;
  }
  if (*(int *)((int)this + 4) != 0) {
    (**(code **)(*param_2 + 8))(*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 **)((int)this + 4) = puVar1;
LAB_00455f4f:
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 00455f60 size=99 */

undefined4 __thiscall FUN_00455f60(void *this,int param_1,int *param_2)

{
  int iVar1;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = (**(code **)(*param_2 + 4))(param_1 << 5);
      *(int *)((int)this + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  return 1;
}


/* 00455fd0 size=288 */

undefined4 __thiscall FUN_00455fd0(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *unaff_EBX;
  undefined4 *puVar7;
  int iVar8;
  uint unaff_retaddr;
  
  uVar4 = *(uint *)((int)this + 8);
  if (param_1 < uVar4) goto LAB_004560df;
  if (uVar4 < param_1) {
    if (param_1 <= uVar4) {
      *(uint *)((int)this + 8) = param_1;
      return 1;
    }
  }
  else if (param_1 == uVar4) {
    return 1;
  }
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 << 5);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  uVar4 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar4 = param_1;
  }
  if (param_1 == 0) {
    if (uVar4 != 0) {
      param_1 = 0;
      puVar7 = puVar1;
      do {
        iVar5 = (*(int *)((int)this + 4) + param_1) - (int)puVar7;
        iVar8 = 3;
        puVar2 = puVar7 + 2;
        puVar6 = puVar7;
        do {
          puVar3 = puVar2 + 2;
          *(undefined2 *)puVar6 = *(undefined2 *)(iVar5 + (int)puVar6);
          *puVar2 = *(undefined4 *)(iVar5 + -8 + (int)puVar3);
          puVar2[1] = *(undefined4 *)(iVar5 + -4 + (int)puVar3);
          puVar6 = (undefined4 *)((int)puVar6 + 2);
          iVar8 = iVar8 + -1;
          puVar2 = puVar3;
        } while (iVar8 != 0);
        param_1 = param_1 + 0x20;
        puVar7 = puVar7 + 8;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
      unaff_EBX = (undefined4 *)0x0;
      goto LAB_004560b6;
    }
  }
  else {
    puVar7 = *(undefined4 **)((int)this + 4);
    puVar2 = puVar1;
    for (iVar5 = (uVar4 & 0x7ffffff) << 3; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar2 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar2 = puVar2 + 1;
    }
    for (iVar5 = 0; unaff_retaddr = param_1, iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar2 = *(undefined1 *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + 1);
      puVar2 = (undefined4 *)((int)puVar2 + 1);
    }
LAB_004560b6:
    param_1 = unaff_retaddr;
    param_3 = param_2;
  }
  if (*(int *)((int)this + 4) != 0) {
    (**(code **)(*param_3 + 8))(*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
    puVar1 = unaff_EBX;
  }
  *(undefined4 **)((int)this + 4) = puVar1;
LAB_004560df:
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 004560f0 size=346 */

undefined4 __thiscall FUN_004560f0(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *unaff_EBX;
  undefined4 *puVar3;
  undefined1 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint unaff_retaddr;
  
  uVar5 = *(uint *)((int)this + 8);
  if (param_1 < uVar5) {
    *(uint *)((int)this + 8) = param_1;
    return 1;
  }
  if (uVar5 < param_1) {
    if (param_1 <= uVar5) {
      *(uint *)((int)this + 8) = param_1;
      return 1;
    }
  }
  else if (param_1 == uVar5) {
    return 1;
  }
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 * 0x24);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  if (param_1 != 0) {
    puVar3 = puVar1;
    uVar5 = param_1;
    do {
      if (puVar3 != (undefined4 *)0x0) {
        FUN_00450430(puVar3);
      }
      puVar3 = puVar3 + 9;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
  uVar5 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar5 = param_1;
  }
  if (param_1 == 0) {
    if (uVar5 != 0) {
      puVar3 = puVar1 + 8;
      do {
        puVar4 = (undefined1 *)(unaff_EBX[1] + (-0x20 - (int)puVar1) + (int)puVar3);
        FUN_00456c80(puVar3 + -8,(int)puVar4,&DAT_004ecc58);
        FUN_00456d80(puVar3 + -4,(uint)(puVar4 + 0x10),&DAT_004ecc58);
        *puVar3 = *(undefined4 *)(puVar4 + 0x20);
        puVar3 = puVar3 + 9;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
      param_1 = unaff_retaddr;
      this = unaff_EBX;
    }
  }
  else {
    puVar3 = *(undefined4 **)((int)this + 4);
    puVar6 = puVar1;
    for (uVar5 = uVar5 * 0x24 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
    }
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar3;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
  }
  puVar3 = *(undefined4 **)((int)this + 4);
  if (puVar3 != (undefined4 *)0x0) {
    iVar2 = *(int *)((int)this + 8);
    if (iVar2 != 0) {
      puVar1 = puVar3;
      do {
        FUN_004504a0(puVar1);
        puVar1 = puVar1 + 9;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      this = unaff_EBX;
    }
    (**(code **)(*param_2 + 8))(puVar3);
    *(undefined4 *)((int)this + 4) = 0;
    puVar1 = unaff_EBX;
  }
  *(undefined4 **)((int)this + 4) = puVar1;
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 00456250 size=92 */

undefined4 __thiscall FUN_00456250(void *this,int param_1)

{
  undefined4 *puVar1;
  
  if (*(int *)((int)this + 4) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 4) = 0;
  *(int *)((int)this + 8) = param_1;
  if (param_1 != 0) {
    puVar1 = FUN_00456f30(&DAT_004ecc58,0,param_1);
    *(undefined4 **)((int)this + 4) = puVar1;
    if (puVar1 == (undefined4 *)0x0) {
      *(undefined4 *)((int)this + 8) = 0;
      return 0;
    }
  }
  return 1;
}


/* 004562b0 size=131 */

undefined4 __thiscall FUN_004562b0(void *this,int param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      puVar2 = (undefined4 *)(**(code **)(*param_2 + 4))(param_1 * 0x14);
      if (puVar2 != (undefined4 *)0x0) {
        puVar3 = puVar2;
        do {
          if (puVar3 != (undefined4 *)0x0) {
            FUN_0044f7e0(puVar3);
          }
          puVar3 = puVar3 + 5;
          param_1 = param_1 + -1;
        } while (param_1 != 0);
      }
      *(undefined4 **)((int)this + 4) = puVar2;
      if (puVar2 == (undefined4 *)0x0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  return 1;
}


/* 00456340 size=237 */

undefined4 __thiscall FUN_00456340(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  
  uVar6 = *(uint *)((int)this + 8);
  if (uVar6 <= param_1) {
    if (uVar6 < param_1) {
      if (param_1 <= uVar6) {
        *(uint *)((int)this + 8) = param_1;
        return 1;
      }
    }
    else if (param_1 == uVar6) {
      return 1;
    }
    puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 * 0x14);
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    if (param_1 != 0) {
      puVar4 = puVar1;
      uVar6 = param_1;
      do {
        if (puVar4 != (undefined4 *)0x0) {
          FUN_0044f7e0(puVar4);
        }
        puVar4 = puVar4 + 5;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
    uVar6 = *(uint *)((int)this + 8);
    if (param_1 < *(uint *)((int)this + 8)) {
      uVar6 = param_1;
    }
    if (param_1 == 0) {
      if (uVar6 != 0) {
        iVar2 = 0;
        do {
          puVar5 = (undefined4 *)(*(int *)((int)this + 4) + iVar2);
          puVar4 = (undefined4 *)(iVar2 + (int)puVar1);
          iVar2 = iVar2 + 0x14;
          uVar6 = uVar6 - 1;
          for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar4 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar4 = puVar4 + 1;
          }
        } while (uVar6 != 0);
      }
    }
    else {
      puVar4 = *(undefined4 **)((int)this + 4);
      puVar5 = puVar1;
      for (uVar6 = uVar6 * 0x14 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
    }
    if (*(int *)((int)this + 4) != 0) {
      (**(code **)(*param_2 + 8))(*(int *)((int)this + 4));
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(undefined4 **)((int)this + 4) = puVar1;
  }
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 00456430 size=94 */

undefined4 __thiscall FUN_00456430(void *this,int param_1)

{
  int iVar1;
  
  if (*(int *)((int)this + 4) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 4) = 0;
  *(int *)((int)this + 8) = param_1;
  if (param_1 != 0) {
    iVar1 = (**(code **)(DAT_004ecc58 + 4))(param_1 << 6);
    *(int *)((int)this + 4) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)((int)this + 8) = 0;
      return 0;
    }
  }
  return 1;
}


/* 00456490 size=99 */

undefined4 __thiscall FUN_00456490(void *this,int param_1,int *param_2)

{
  int iVar1;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = (**(code **)(*param_2 + 4))(param_1 << 6);
      *(int *)((int)this + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  return 1;
}


/* 00456500 size=203 */

undefined4 __thiscall FUN_00456500(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint unaff_retaddr;
  
  uVar4 = *(uint *)((int)this + 8);
  if (param_1 < uVar4) goto LAB_004565bc;
  if (uVar4 < param_1) {
    if (param_1 <= uVar4) {
      *(uint *)((int)this + 8) = param_1;
      return 1;
    }
  }
  else if (param_1 == uVar4) {
    return 1;
  }
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 << 6);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  uVar4 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar4 = param_1;
  }
  if (param_1 == 0) {
    if (uVar4 != 0) {
      iVar2 = 0;
      do {
        puVar5 = (undefined4 *)(iVar2 + (int)puVar1);
        puVar6 = (undefined4 *)(*(int *)((int)this + 4) + iVar2);
        iVar2 = iVar2 + 0x40;
        uVar4 = uVar4 - 1;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar5 = puVar5 + 1;
        }
      } while (uVar4 != 0);
      goto LAB_00456594;
    }
  }
  else {
    puVar5 = *(undefined4 **)((int)this + 4);
    puVar6 = puVar1;
    for (iVar2 = (uVar4 & 0x3ffffff) << 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
LAB_00456594:
    param_1 = unaff_retaddr;
    param_3 = param_2;
  }
  if (*(int *)((int)this + 4) != 0) {
    (**(code **)(*param_3 + 8))(*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 **)((int)this + 4) = puVar1;
LAB_004565bc:
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 004565d0 size=170 */

undefined4 __thiscall FUN_004565d0(void *this,int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (*(int *)((int)this + 4) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0x10) = param_2;
  *(undefined4 *)((int)this + 0xc) = 0;
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    if (*(int *)((int)this + 4) != 0) {
      (**(code **)(DAT_004ecc58 + 8))(*(int *)((int)this + 4));
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar1 = FUN_00457040(&DAT_004ecc58,0,*(int *)((int)this + 0x10) + param_1);
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


/* 00456680 size=154 */

undefined4 __thiscall FUN_00456680(void *this,int param_1,int *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
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
      puVar2 = (undefined4 *)(**(code **)(*param_2 + 4))(iVar3 * 4);
      puVar1 = puVar2;
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        for (; iVar3 != 0; iVar3 = iVar3 + -1) {
          if (puVar1 != (undefined4 *)0x0) {
            *puVar1 = 0;
          }
          puVar1 = puVar1 + 1;
        }
      }
      *(undefined4 **)((int)this + 4) = puVar2;
      if (puVar2 == (undefined4 *)0x0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 00456720 size=271 */

undefined4 __thiscall FUN_00456720(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *unaff_EBX;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  uVar4 = *(uint *)((int)this + 8);
  if (param_1 < uVar4) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = *(int *)((int)this + 0xc) + (uVar4 - param_1);
    return 1;
  }
  if ((uVar4 < param_1) && (uVar3 = *(int *)((int)this + 0xc) + uVar4, param_1 <= uVar3)) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = uVar3 - param_1;
    return 1;
  }
  if (param_1 != uVar4) {
    iVar5 = param_1 + *(int *)((int)this + 0x10);
    puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(iVar5 * 4);
    puVar6 = puVar1;
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    for (; iVar5 != 0; iVar5 = iVar5 + -1) {
      if (puVar6 != (undefined4 *)0x0) {
        *puVar6 = 0;
      }
      puVar6 = puVar6 + 1;
    }
    uVar4 = *(uint *)((int)this + 8);
    if (param_1 < *(uint *)((int)this + 8)) {
      uVar4 = param_1;
    }
    if (param_1 == 0) {
      uVar3 = 0;
      param_2 = param_3;
      if (uVar4 != 0) {
        do {
          uVar2 = uVar3 + 1;
          puVar1[uVar3] = *(undefined4 *)(*(int *)((int)this + 4) + -4 + uVar2 * 4);
          uVar3 = uVar2;
        } while (uVar2 < uVar4);
      }
    }
    else {
      puVar6 = *(undefined4 **)((int)this + 4);
      puVar7 = puVar1;
      for (; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
    }
    iVar5 = *(int *)((int)this + 4);
    if (iVar5 != 0) {
      if (iVar5 != 0) {
        (**(code **)(*param_2 + 8))(iVar5);
        puVar1 = unaff_EBX;
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 **)((int)this + 4) = puVar1;
    *(uint *)((int)this + 8) = param_1;
    *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  }
  return 1;
}


/* 00456830 size=97 */

undefined4 __thiscall FUN_00456830(void *this,int param_1)

{
  int iVar1;
  
  if (*(int *)((int)this + 4) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 4) = 0;
  *(int *)((int)this + 8) = param_1;
  if (param_1 != 0) {
    iVar1 = (**(code **)(DAT_004ecc58 + 4))(param_1 * 4);
    *(int *)((int)this + 4) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)((int)this + 8) = 0;
      return 0;
    }
  }
  return 1;
}


/* 004568a0 size=92 */

undefined4 __thiscall FUN_004568a0(void *this,int param_1)

{
  undefined4 *puVar1;
  
  if (*(int *)((int)this + 4) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 4) = 0;
  *(int *)((int)this + 8) = param_1;
  if (param_1 != 0) {
    puVar1 = FUN_00457080(&DAT_004ecc58,0,param_1);
    *(undefined4 **)((int)this + 4) = puVar1;
    if (puVar1 == (undefined4 *)0x0) {
      *(undefined4 *)((int)this + 8) = 0;
      return 0;
    }
  }
  return 1;
}


/* 00456900 size=130 */

undefined4 __thiscall FUN_00456900(void *this,int param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar1 = *(int *)((int)this + 4);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*param_2 + 8))(iVar1);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      puVar2 = (undefined4 *)(**(code **)(*param_2 + 4))(param_1 << 5);
      if (puVar2 != (undefined4 *)0x0) {
        puVar3 = puVar2;
        do {
          if (puVar3 != (undefined4 *)0x0) {
            FUN_00450040(puVar3);
          }
          puVar3 = puVar3 + 8;
          param_1 = param_1 + -1;
        } while (param_1 != 0);
      }
      *(undefined4 **)((int)this + 4) = puVar2;
      if (puVar2 == (undefined4 *)0x0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  return 1;
}


/* 00456990 size=238 */

undefined4 __thiscall FUN_00456990(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint unaff_retaddr;
  
  uVar2 = *(uint *)((int)this + 8);
  if (param_1 < uVar2) goto LAB_00456a6f;
  if (uVar2 < param_1) {
    if (param_1 <= uVar2) {
      *(uint *)((int)this + 8) = param_1;
      return 1;
    }
  }
  else if (param_1 == uVar2) {
    return 1;
  }
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(param_1 << 5);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  if (param_1 != 0) {
    puVar5 = puVar1;
    uVar2 = param_1;
    do {
      if (puVar5 != (undefined4 *)0x0) {
        FUN_00450040(puVar5);
      }
      puVar5 = puVar5 + 8;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  uVar2 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar2 = param_1;
  }
  if (param_1 == 0) {
    if (uVar2 != 0) {
      iVar3 = 0;
      do {
        puVar5 = (undefined4 *)(iVar3 + (int)puVar1);
        puVar6 = (undefined4 *)(*(int *)((int)this + 4) + iVar3);
        iVar3 = iVar3 + 0x20;
        uVar2 = uVar2 - 1;
        for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar5 = puVar5 + 1;
        }
      } while (uVar2 != 0);
      goto LAB_00456a48;
    }
  }
  else {
    puVar5 = *(undefined4 **)((int)this + 4);
    puVar6 = puVar1;
    for (iVar3 = (uVar2 & 0x7ffffff) << 3; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
LAB_00456a48:
    param_1 = unaff_retaddr;
  }
  if (*(int *)((int)this + 4) != 0) {
    (**(code **)(*param_2 + 8))(*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 **)((int)this + 4) = puVar1;
LAB_00456a6f:
  *(uint *)((int)this + 8) = param_1;
  return 1;
}


/* 00456a80 size=60 */

void __thiscall FUN_00456a80(void *this,int *param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = *(undefined4 **)((int)this + 4);
  puVar2 = puVar1;
  if (puVar1 != (undefined4 *)0x0) {
    for (; param_2 != 0; param_2 = param_2 + -1) {
      FUN_004504a0(puVar2);
      puVar2 = puVar2 + 9;
    }
    (**(code **)(*param_1 + 8))(puVar1);
    *(undefined4 *)((int)this + 4) = 0;
  }
  return;
}


/* 00456ac0 size=31 */

void __thiscall FUN_00456ac0(void *this,int *param_1)

{
  if (*(int *)((int)this + 4) != 0) {
    (**(code **)(*param_1 + 8))(*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
  }
  return;
}


/* 00456ae0 size=48 */

void __cdecl FUN_00456ae0(int *param_1,undefined4 *param_2,int param_3)

{
  undefined4 *puVar1;
  
  puVar1 = param_2;
  if (param_2 != (undefined4 *)0x0) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      FUN_00450580(puVar1);
      puVar1 = puVar1 + 0x1b;
    }
    (**(code **)(*param_1 + 8))(param_2);
  }
  return;
}


/* 00456b10 size=48 */

void __cdecl FUN_00456b10(int *param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = param_2;
  if (param_2 != 0) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      FUN_004506c0(iVar1);
      iVar1 = iVar1 + 0x28;
    }
    (**(code **)(*param_1 + 8))(param_2);
  }
  return;
}


/* 00456b70 size=33 */

int __cdecl FUN_00456b70(int *param_1,undefined4 param_2,int param_3)

{
  (**(code **)(*param_1 + 4))(param_3 * 0x1c);
  return;
}


/* 00456ba0 size=61 */

undefined4 * __cdecl FUN_00456ba0(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(**(code **)(*param_1 + 4))(param_3 * 0x14);
  puVar1 = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    if (puVar1 != (undefined4 *)0x0) {
      FUN_0044f950(puVar1);
    }
    puVar1 = puVar1 + 5;
  }
  return puVar2;
}


/* 00456be0 size=150 */

undefined4 __thiscall FUN_00456be0(void *this,int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*param_2 + 8))(iVar1);
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  iVar1 = *(int *)(param_1 + 8);
  *(int *)((int)this + 8) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    iVar1 = (**(code **)(*param_2 + 4))(iVar1 << 2);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    *(int *)((int)this + 4) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)((int)this + 8) = 0;
      return 0;
    }
    uVar2 = 0;
    if (*(int *)((int)this + 8) != 0) {
      do {
        *(undefined4 *)(*(int *)((int)this + 4) + uVar2 * 4) =
             *(undefined4 *)(*(int *)(param_1 + 4) + uVar2 * 4);
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)((int)this + 8));
      return 1;
    }
  }
  return 1;
}


/* 00456c80 size=191 */

undefined4 __thiscall FUN_00456c80(void *this,int param_1,int *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  int unaff_retaddr;
  
  iVar4 = *(int *)((int)this + 4);
  if (iVar4 != 0) {
    if (iVar4 != 0) {
      (**(code **)(*param_2 + 8))(iVar4);
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  iVar4 = *(int *)(param_1 + 8);
  *(int *)((int)this + 8) = iVar4;
  if (iVar4 == 0) {
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    puVar1 = (undefined4 *)(**(code **)(*param_2 + 4))(iVar4 << 5);
    puVar5 = puVar1;
    if (puVar1 != (undefined4 *)0x0) {
      for (; iVar4 != 0; iVar4 = iVar4 + -1) {
        if (puVar5 != (undefined4 *)0x0) {
          FUN_0044f800(puVar5);
        }
        puVar5 = puVar5 + 8;
      }
    }
    uVar3 = 0;
    *(undefined4 **)((int)this + 4) = puVar1;
    if (puVar1 == (undefined4 *)0x0) {
      *(undefined4 *)((int)this + 8) = 0;
      return 0;
    }
    if (*(int *)((int)this + 8) != 0) {
      iVar4 = 0;
      do {
        puVar5 = (undefined4 *)(*(int *)(unaff_retaddr + 4) + iVar4);
        puVar1 = (undefined4 *)(iVar4 + *(int *)((int)this + 4));
        for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar1 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar1 = puVar1 + 1;
        }
        uVar3 = uVar3 + 1;
        iVar4 = iVar4 + 0x20;
      } while (uVar3 < *(uint *)((int)this + 8));
      return 1;
    }
  }
  return 1;
}


/* 00456d40 size=60 */

undefined4 * __cdecl FUN_00456d40(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(**(code **)(*param_1 + 4))(param_3 << 5);
  puVar1 = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    if (puVar1 != (undefined4 *)0x0) {
      FUN_0044f800(puVar1);
    }
    puVar1 = puVar1 + 8;
  }
  return puVar2;
}


/* 00456d80 size=211 */

undefined4 __thiscall FUN_00456d80(void *this,uint param_1,int *param_2)

{
  int iVar1;
  undefined2 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int unaff_retaddr;
  
  iVar5 = 0;
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*param_2 + 8))(iVar1);
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  iVar1 = *(int *)(param_1 + 8);
  *(int *)((int)this + 8) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    iVar1 = (**(code **)(*param_2 + 4))(iVar1 << 5);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    *(int *)((int)this + 4) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)((int)this + 8) = 0;
      return 0;
    }
    param_1 = 0;
    if (*(int *)((int)this + 8) != 0) {
      do {
        iVar6 = 3;
        puVar2 = (undefined2 *)(iVar5 + *(int *)((int)this + 4));
        iVar1 = (iVar5 + *(int *)(unaff_retaddr + 4)) - (int)puVar2;
        puVar3 = (undefined4 *)(puVar2 + 4);
        do {
          puVar4 = puVar3 + 2;
          *puVar2 = *(undefined2 *)(iVar1 + (int)puVar2);
          *puVar3 = *(undefined4 *)(iVar1 + -8 + (int)puVar4);
          puVar3[1] = *(undefined4 *)(iVar1 + -4 + (int)puVar4);
          puVar2 = puVar2 + 1;
          iVar6 = iVar6 + -1;
          puVar3 = puVar4;
        } while (iVar6 != 0);
        param_1 = param_1 + 1;
        iVar5 = iVar5 + 0x20;
      } while (param_1 < *(uint *)((int)this + 8));
      return 1;
    }
  }
  return 1;
}


/* 00456e60 size=19 */

void __cdecl FUN_00456e60(int *param_1,int param_2)

{
  if (param_2 != 0) {
    (**(code **)(*param_1 + 8))(param_2);
  }
  return;
}


/* 00456e80 size=22 */

int __cdecl FUN_00456e80(int *param_1,undefined4 param_2,int param_3)

{
  (**(code **)(*param_1 + 4))(param_3 << 5);
  return;
}


/* 00456ea0 size=48 */

void __cdecl FUN_00456ea0(int *param_1,undefined4 *param_2,int param_3)

{
  undefined4 *puVar1;
  
  puVar1 = param_2;
  if (param_2 != (undefined4 *)0x0) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      FUN_004504a0(puVar1);
      puVar1 = puVar1 + 9;
    }
    (**(code **)(*param_1 + 8))(param_2);
  }
  return;
}


/* 00456ed0 size=61 */

undefined4 * __cdecl FUN_00456ed0(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(**(code **)(*param_1 + 4))(param_3 * 0x24);
  puVar1 = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    if (puVar1 != (undefined4 *)0x0) {
      FUN_00450430(puVar1);
    }
    puVar1 = puVar1 + 9;
  }
  return puVar2;
}


/* 00456f10 size=22 */

int __cdecl FUN_00456f10(int *param_1,undefined4 param_2,int param_3)

{
  (**(code **)(*param_1 + 4))(param_3 << 2);
  return;
}


/* 00456f30 size=61 */

undefined4 * __cdecl FUN_00456f30(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(**(code **)(*param_1 + 4))(param_3 * 0x14);
  puVar1 = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    if (puVar1 != (undefined4 *)0x0) {
      FUN_0044f7e0(puVar1);
    }
    puVar1 = puVar1 + 5;
  }
  return puVar2;
}


/* 00456f70 size=164 */

undefined4 __thiscall FUN_00456f70(void *this,int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*param_2 + 8))(iVar1);
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  iVar1 = *(int *)(param_1 + 8);
  *(int *)((int)this + 8) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    iVar1 = (**(code **)(*param_2 + 4))(iVar1 << 6);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    *(int *)((int)this + 4) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)((int)this + 8) = 0;
      return 0;
    }
    uVar3 = 0;
    if (*(int *)((int)this + 8) != 0) {
      iVar1 = 0;
      do {
        puVar4 = (undefined4 *)(iVar1 + *(int *)(param_1 + 4));
        puVar5 = (undefined4 *)(iVar1 + *(int *)((int)this + 4));
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
        uVar3 = uVar3 + 1;
        iVar1 = iVar1 + 0x40;
      } while (uVar3 < *(uint *)((int)this + 8));
      return 1;
    }
  }
  return 1;
}


/* 00457020 size=22 */

void __cdecl FUN_00457020(int *param_1,undefined4 param_2,int param_3)

{
  (**(code **)(*param_1 + 4))(param_3 << 6);
  return;
}


/* 00457040 size=52 */

int __cdecl FUN_00457040(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(**(code **)(*param_1 + 4))(param_3 * 4);
  if (puVar1 == (undefined4 *)0x0) {
    return;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = 0;
    }
    puVar1 = puVar1 + 1;
  }
  return;
}


/* 00457080 size=60 */

undefined4 * __cdecl FUN_00457080(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(**(code **)(*param_1 + 4))(param_3 << 5);
  puVar1 = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    if (puVar1 != (undefined4 *)0x0) {
      FUN_00450040(puVar1);
    }
    puVar1 = puVar1 + 8;
  }
  return puVar2;
}


/* 004570c0 size=30 */

undefined4 * __thiscall FUN_004570c0(void *this,byte param_1)

{
  FUN_004504a0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004570e0 size=172 */

undefined4 __cdecl FUN_004570e0(byte *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  bool bVar6;
  byte abStack_118 [4];
  undefined1 auStack_104 [260];
  
  (**(code **)(*(int *)param_1 + 0x14))();
  uVar4 = 0;
  do {
    (**(code **)(*(int *)param_1 + 0xc))(auStack_104,0x100);
    (**(code **)(*(int *)param_1 + 8))(abStack_118 + 8,4);
    pbVar5 = abStack_118 + 4;
    pbVar2 = param_1;
    do {
      bVar1 = *pbVar2;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_0045714c:
        iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_00457151;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_0045714c;
      pbVar2 = pbVar2 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00457151:
    if (iVar3 == 0) {
      return 1;
    }
    (**(code **)(*(int *)param_1 + 0x14))(0);
    uVar4 = uVar4 + 1;
    if (0x1ff < uVar4) {
      return 0;
    }
  } while( true );
}


/* 00457190 size=455 */

undefined4 __thiscall FUN_00457190(void *this,int *param_1)

{
  int *piVar1;
  void *this_00;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 uStack_8;
  void *pvStack_4;
  
  iVar2 = FUN_0044fda0((int)this);
  piVar1 = *(int **)(iVar2 + 0x174);
  iVar2 = *(int *)(*(int *)((int)this + 0x2c) + 0x10);
  if ((iVar2 != *(int *)((int)this + 0x10)) || (iVar2 == 0)) {
    if (*(int *)((int)this + 0xc) != 0) {
      FUN_00456ac0((void *)((int)this + 8),piVar1);
    }
    *(int *)((int)this + 0x10) = iVar2;
    if (iVar2 != 0) {
      iVar2 = FUN_00456b70(piVar1,0,iVar2);
      *(int *)((int)this + 0xc) = iVar2;
      if (iVar2 == 0) {
        *(undefined4 *)((int)this + 0x10) = 0;
        return 0;
      }
    }
  }
  uVar5 = 0;
  if (*(int *)(*(int *)((int)this + 0x2c) + 0x10) != 0) {
    iVar2 = 0;
    do {
      (**(code **)(*param_1 + 8))(*(int *)((int)this + 0xc) + iVar2,0x1c);
      uVar5 = uVar5 + 1;
      iVar2 = iVar2 + 0x1c;
    } while (uVar5 < *(uint *)(*(int *)((int)this + 0x2c) + 0x10));
  }
  iVar2 = FUN_0044fda0((int)this);
  uVar5 = 0;
  pvStack_4 = (void *)((int)this + 0x1c);
  uStack_8 = 0;
  iVar2 = FUN_0045a760(pvStack_4,*(int *)(*(int *)((int)this + 4) + 0x20),&uStack_8,
                       *(int **)(iVar2 + 0x174));
  if (iVar2 == 0) {
    return 0;
  }
  if (*(int *)(*(int *)((int)this + 4) + 0x20) != 0) {
    do {
      iVar2 = FUN_0044fda0((int)this);
      piVar1 = *(int **)(iVar2 + 0x174);
      uVar3 = (**(code **)(*(int *)this + 4))();
      puVar4 = (undefined4 *)(**(code **)(*piVar1 + 4))(0x30);
      if (puVar4 == (undefined4 *)0x0) {
        return 0;
      }
      FUN_0044fa00(puVar4,uVar3,this);
      puVar4[1] = *(undefined4 *)(*(int *)(*(int *)((int)this + 4) + 0x1c) + uVar5 * 4);
      iVar2 = FUN_00457190(puVar4,param_1);
      if (iVar2 == 0) {
        iVar2 = FUN_0044fda0((int)this);
        piVar1 = *(int **)(iVar2 + 0x174);
        if (puVar4 != (undefined4 *)0x0) {
          (**(code **)*puVar4)(0);
          (**(code **)(*piVar1 + 8))(puVar4);
        }
        iVar2 = FUN_0044fda0((int)this);
        this_00 = pvStack_4;
        piVar1 = *(int **)(iVar2 + 0x174);
        uVar5 = 0;
        if (*(int *)((int)pvStack_4 + 8) != 0) {
          do {
            puVar4 = *(undefined4 **)(*(int *)((int)this_00 + 4) + uVar5 * 4);
            if (puVar4 != (undefined4 *)0x0) {
              (**(code **)*puVar4)(0);
              (**(code **)(*piVar1 + 8))(puVar4);
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < *(uint *)((int)this_00 + 8));
        }
        if (*(int *)((int)this_00 + 4) != 0) {
          FUN_00456ac0(this_00,piVar1);
        }
        *(undefined4 *)((int)this_00 + 8) = 0;
        return 0;
      }
      uVar5 = uVar5 + 1;
      *(undefined4 **)(*(int *)((int)this + 0x20) + -4 + uVar5 * 4) = puVar4;
    } while (uVar5 < *(uint *)(*(int *)((int)this + 4) + 0x20));
  }
  return 1;
}


/* 00457360 size=306 */

undefined4 __thiscall FUN_00457360(void *this,int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  void *unaff_EBP;
  void *pvStack_4;
  
  pvStack_4 = this;
  FUN_0044fe80((int)this);
  iVar2 = FUN_00457d50();
  if (iVar2 != 0) {
    if (10 < *(uint *)(*(int *)((int)this + 0x20) + 0x208)) {
      (**(code **)(*param_1 + 8))((int)this + 0x18,4);
    }
    if (0xb < *(uint *)(*(int *)((int)this + 0x20) + 0x208)) {
      (**(code **)(*param_1 + 8))((int)this + 0x1c,4);
    }
    (**(code **)(*param_1 + 8))(&pvStack_4,4);
    piVar1 = *(int **)(*(int *)((int)this + 0x20) + 0x174);
    if ((unaff_EBP != *(void **)((int)this + 0x10)) || (unaff_EBP == (void *)0x0)) {
      if (*(int *)((int)this + 0xc) != 0) {
        FUN_00456e60(piVar1,*(int *)((int)this + 0xc));
        *(undefined4 *)((int)this + 0xc) = 0;
      }
      *(void **)((int)this + 0x10) = unaff_EBP;
      if (unaff_EBP != (void *)0x0) {
        puVar3 = FUN_00456ba0(piVar1,0,(int)unaff_EBP);
        *(undefined4 **)((int)this + 0xc) = puVar3;
        if (puVar3 == (undefined4 *)0x0) {
          *(undefined4 *)((int)this + 0x10) = 0;
          return 0;
        }
      }
    }
    iVar2 = 0;
    pvStack_4 = (void *)0x0;
    if (unaff_EBP != (void *)0x0) {
      do {
        (**(code **)(*param_1 + 8))(*(int *)((int)this + 0xc) + iVar2,4);
        iVar4 = FUN_00457d50();
        if (iVar4 == 0) {
          return 0;
        }
        pvStack_4 = (void *)((int)pvStack_4 + 1);
        iVar2 = iVar2 + 0x14;
      } while (pvStack_4 < unaff_EBP);
    }
    *(undefined4 *)(*(int *)((int)this + 0x58) + 4) =
         *(undefined4 *)(*(int *)((int)this + 0x20) + 0x2c4);
    iVar2 = FUN_00457190(*(void **)((int)this + 0x58),param_1);
    if (iVar2 != 0) {
      uVar5 = FUN_0044ff90(this,1);
      return uVar5;
    }
  }
  return 0;
}


/* 004574a0 size=526 */

undefined4 __thiscall FUN_004574a0(void *this,int *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  float *pfVar6;
  int iVar7;
  undefined4 *puVar8;
  float *pfVar9;
  undefined1 auStack_e0 [4];
  undefined1 auStack_ca [2];
  float afStack_c8 [14];
  float afStack_90 [16];
  float afStack_50 [20];
  
  iVar2 = FUN_00457d50();
  if (iVar2 == 0) {
    return 0;
  }
  (**(code **)(*param_1 + 8))((int)this + 0x10);
  (**(code **)(*param_1 + 8))((int)this + 0x12,1);
  puVar5 = auStack_ca + -6;
  iVar2 = 4;
  do {
    iVar7 = 4;
    do {
      (**(code **)(*param_1 + 8))(puVar5,4);
      puVar5 = puVar5 + 4;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  pfVar6 = (float *)(auStack_ca + -6);
  pfVar9 = afStack_90;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar9 = *pfVar6;
    pfVar6 = pfVar6 + 1;
    pfVar9 = pfVar9 + 1;
  }
  puVar4 = (undefined4 *)(auStack_ca + -6);
  puVar8 = (undefined4 *)((int)this + 0x2c);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar8 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar8 = puVar8 + 1;
  }
  FUN_004513e0(afStack_90,afStack_50);
  pfVar6 = afStack_50;
  pfVar9 = (float *)((int)this + 0x6c);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar9 = *pfVar6;
    pfVar6 = pfVar6 + 1;
    pfVar9 = pfVar9 + 1;
  }
  (**(code **)(*param_1 + 8))(auStack_e0 + 8,4);
  iVar2 = FUN_00455a50((void *)((int)this + 0x18),2,*(int **)(*(int *)((int)this + 0xac) + 0x174));
  if (iVar2 != 0) {
    uVar3 = 0;
    if (*(int *)((int)this + 0x20) != 0) {
      do {
        uVar3 = uVar3 + 1;
        *(undefined4 *)(*(int *)((int)this + 0x1c) + -4 + uVar3 * 4) = 0;
      } while (uVar3 < *(uint *)((int)this + 0x20));
    }
    uVar3 = 0;
    while( true ) {
      iVar2 = *(int *)((int)this + 0xac);
      puVar4 = (undefined4 *)(**(code **)(**(int **)(iVar2 + 0x174) + 4))(0xb4);
      if (puVar4 == (undefined4 *)0x0) break;
      FUN_004500e0(puVar4,iVar2);
      iVar2 = FUN_004574a0(puVar4,param_1);
      if (iVar2 == 0) {
        piVar1 = *(int **)(*(int *)((int)this + 0xac) + 0x174);
        if (puVar4 != (undefined4 *)0x0) {
          (**(code **)*puVar4)(0);
          (**(code **)(*piVar1 + 8))(puVar4);
        }
        uVar3 = 0;
        piVar1 = *(int **)(*(int *)((int)this + 0xac) + 0x174);
        if (*(int *)((int)this + 0x20) != 0) {
          do {
            puVar4 = *(undefined4 **)(*(int *)((int)this + 0x1c) + uVar3 * 4);
            if (puVar4 != (undefined4 *)0x0) {
              (**(code **)*puVar4)(0);
              (**(code **)(*piVar1 + 8))(puVar4);
            }
            uVar3 = uVar3 + 1;
          } while (uVar3 < *(uint *)((int)this + 0x20));
        }
        if (*(int *)((int)this + 0x1c) != 0) {
          FUN_00456ac0((void *)((int)this + 0x18),piVar1);
        }
        *(undefined4 *)((int)this + 0x20) = 0;
        return 0;
      }
      *(undefined4 **)(*(int *)((int)this + 0x1c) + uVar3 * 4) = puVar4;
      uVar3 = uVar3 + 1;
      if (1 < uVar3) {
        return 1;
      }
    }
  }
  return 0;
}


/* 004576b0 size=71 */

undefined4 __thiscall FUN_004576b0(void *this,int *param_1)

{
  undefined4 uVar1;
  
  (**(code **)(*param_1 + 8))((int)this + 8,4);
  (**(code **)(*param_1 + 8))((int)this + 0xc,4);
  (**(code **)(*param_1 + 8))((int)this + 0x10,4);
  if (*(void **)this == (void *)0x0) {
    return 0;
  }
  uVar1 = FUN_00457360(*(void **)this,param_1);
  return uVar1;
}


/* 00457700 size=255 */

undefined4 __thiscall FUN_00457700(void *this,int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if (*(int *)((int)this + 0x24) == 0) {
    return 0;
  }
  (**(code **)(*param_1 + 8))((int)this + 0x20,4);
  piVar1 = *(int **)(*(int *)((int)this + 0x24) + 0x174);
  iVar2 = *(int *)(*(int *)((int)this + 0x24) + 0x78);
  if ((iVar2 != *(int *)((int)this + 8)) || (iVar2 == 0)) {
    if (*(int *)((int)this + 4) != 0) {
      FUN_00456e60(piVar1,*(int *)((int)this + 4));
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    *(int *)((int)this + 8) = iVar2;
    if (iVar2 != 0) {
      iVar2 = FUN_00456b70(piVar1,0,*(int *)((int)this + 0x10) + iVar2);
      *(int *)((int)this + 4) = iVar2;
      if (iVar2 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  iVar2 = 0;
  uVar4 = 0;
  if (*(int *)(*(int *)((int)this + 0x24) + 0x78) != 0) {
    do {
      iVar3 = iVar2 + *(int *)((int)this + 4);
      (**(code **)(*param_1 + 8))(iVar3,4);
      (**(code **)(*param_1 + 8))(iVar3 + 4,4);
      (**(code **)(*param_1 + 8))(iVar3 + 8,4);
      FUN_00470b30(param_1,*(int *)((int)this + 4) + 0xc + iVar2);
      uVar4 = uVar4 + 1;
      iVar2 = iVar2 + 0x1c;
    } while (uVar4 < *(uint *)(*(int *)((int)this + 0x24) + 0x78));
  }
  return 1;
}


/* 00457800 size=749 */

undefined4 __thiscall FUN_00457800(void *this,int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  uint unaff_EBX;
  int iVar3;
  int unaff_ESI;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int *piStack_18;
  int local_14;
  int iStack_10;
  int *apiStack_c [3];
  
  (**(code **)(*param_1 + 8))(&local_14,4);
  apiStack_c[0] = *(int **)(*(int *)((int)this + 0x20) + 0x174);
  if ((unaff_EBX != *(uint *)((int)this + 0x18)) || (unaff_EBX == 0)) {
    if (*(int *)((int)this + 0x14) != 0) {
      FUN_00456ac0((void *)((int)this + 0x10),apiStack_c[0]);
    }
    *(uint *)((int)this + 0x18) = unaff_EBX;
    if (unaff_EBX != 0) {
      iVar1 = FUN_00456e80(apiStack_c[0],0,unaff_EBX);
      *(int *)((int)this + 0x14) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)((int)this + 0x18) = 0;
        return 0;
      }
    }
  }
  uVar7 = 0;
  if (unaff_EBX != 0) {
    iStack_10 = 0;
    do {
      apiStack_c[0] = (int *)0x3;
      iVar1 = iStack_10;
      local_14 = iStack_10;
      do {
        (**(code **)(*param_1 + 8))(iVar1 + 8 + *(int *)((int)this + 0x14),4);
        (**(code **)(*param_1 + 8))(iVar1 + 0xc + *(int *)((int)this + 0x14),4);
        (**(code **)(*param_1 + 8))(unaff_ESI + *(int *)((int)this + 0x14),2);
        local_14 = local_14 + 2;
        apiStack_c[0] = (int *)((int)apiStack_c[0] + -1);
        iVar1 = iVar1 + 8;
      } while (apiStack_c[0] != (int *)0x0);
      uVar7 = uVar7 + 1;
      iStack_10 = iStack_10 + 0x20;
      apiStack_c[0] = (int *)0x0;
    } while (uVar7 < unaff_EBX);
  }
  (**(code **)(*param_1 + 8))(&piStack_18,4);
  piVar4 = *(int **)(*(int *)((int)this + 0x20) + 0x174);
  if ((uVar7 != *(uint *)((int)this + 8)) || (uVar7 == 0)) {
    if (*(int *)((int)this + 4) != 0) {
      FUN_00456ac0(this,piVar4);
    }
    *(uint *)((int)this + 8) = uVar7;
    if (uVar7 != 0) {
      puVar2 = FUN_00456d40(piVar4,0,uVar7);
      *(undefined4 **)((int)this + 4) = puVar2;
      if (puVar2 == (undefined4 *)0x0) {
        *(undefined4 *)((int)this + 8) = 0;
        return 0;
      }
    }
  }
  uVar5 = 0;
  if (uVar7 != 0) {
    iVar1 = 0;
    do {
      piVar4 = (int *)(*(int *)((int)this + 4) + iVar1);
      (**(code **)(*param_1 + 8))(apiStack_c,2);
      *(undefined2 *)(piVar4 + 1) = (undefined2)local_14;
      (**(code **)(*param_1 + 8))(&local_14,2);
      *(short *)((int)piVar4 + 6) = (short)iVar1;
      if (*(uint *)(*(int *)((int)this + 0x20) + 0x5c) < *piStack_18 + (uint)*(ushort *)(piVar4 + 1)
         ) {
        return 0;
      }
      if ((short)piVar4[1] != 0) {
        *piVar4 = *(int *)(*(int *)((int)this + 0x20) + 0x58) + *piStack_18 * 0x14;
        *piStack_18 = *piStack_18 + (uint)*(ushort *)(piVar4 + 1);
        uVar6 = 0;
        if ((short)piVar4[1] != 0) {
          uVar5 = 0;
          do {
            iVar3 = uVar5 + *piVar4;
            (**(code **)(*param_1 + 8))(iVar3 + 0x10,4);
            (**(code **)(*param_1 + 8))(iVar3,4);
            (**(code **)(*param_1 + 8))(iVar3 + 4,4);
            (**(code **)(*param_1 + 8))(iVar3 + 8,4);
            (**(code **)(*param_1 + 8))(iVar3 + 0xc,4);
            uVar6 = uVar6 + 1;
            uVar5 = uVar5 + 0x14;
          } while (uVar6 < *(ushort *)(piVar4 + 1));
        }
      }
      (**(code **)(*param_1 + 8))(piVar4 + 2,4);
      (**(code **)(*param_1 + 8))(piVar4 + 3,4);
      (**(code **)(*param_1 + 8))(piVar4 + 4,4);
      (**(code **)(*param_1 + 8))(piVar4 + 5,4);
      (**(code **)(*param_1 + 8))(piVar4 + 6,4);
      (**(code **)(*param_1 + 8))(piVar4 + 7,4);
      uVar5 = uVar5 + 1;
      iVar1 = iVar1 + 0x20;
    } while (uVar5 < uVar7);
  }
  return 1;
}


/* 00457af0 size=390 */

undefined4 __thiscall FUN_00457af0(void *this,int *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  uint unaff_EBX;
  uint uVar5;
  int iVar6;
  ushort unaff_DI;
  undefined1 *puStack_24;
  undefined4 uStack_20;
  undefined1 auStack_a [2];
  undefined1 local_8 [8];
  
  puStack_24 = local_8;
  uStack_20 = 2;
  (**(code **)(*param_1 + 8))();
  *(uint *)((int)this + 0x24) = unaff_EBX & 0xffff;
  (**(code **)(*param_1 + 8))((int)this + 0x2c,4);
  (**(code **)(*param_1 + 8))((int)this + 0x30,4);
  if (9 < *(uint *)(*(int *)((int)this + 0x68) + 0x208)) {
    (**(code **)(*param_1 + 8))((int)this + 0x44,4);
  }
  (**(code **)(*param_1 + 8))(auStack_a + -10,2);
  uVar5 = 0;
  if (unaff_DI != 0) {
    do {
      (**(code **)(*param_1 + 8))(&puStack_24,4);
      uVar5 = uVar5 + 1;
    } while (uVar5 < unaff_DI);
  }
  uVar5 = *(uint *)(*(int *)((int)this + 0x68) + 0x94);
  piVar1 = *(int **)(*(int *)((int)this + 0x68) + 0x174);
  if ((uVar5 != *(uint *)((int)this + 0x3c)) || (uVar5 == 0)) {
    if (*(undefined4 **)((int)this + 0x38) != (undefined4 *)0x0) {
      FUN_00456ea0(piVar1,*(undefined4 **)((int)this + 0x38),*(uint *)((int)this + 0x3c));
      *(undefined4 *)((int)this + 0x38) = 0;
    }
    *(uint *)((int)this + 0x3c) = uVar5;
    if (uVar5 == 0) goto LAB_00457bff;
    puVar2 = FUN_00456ed0(piVar1,0,uVar5);
    *(undefined4 **)((int)this + 0x38) = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      *(undefined4 *)((int)this + 0x3c) = 0;
      return 0;
    }
  }
  if (uVar5 != 0) {
    iVar6 = 0;
    uVar3 = uVar5;
    do {
      FUN_00450490((void *)(*(int *)((int)this + 0x38) + iVar6),*(undefined4 *)((int)this + 0x68));
      iVar6 = iVar6 + 0x24;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
LAB_00457bff:
  iVar6 = (**(code **)(*param_1 + 0xc))((int)this + 0x48,0x20);
  if (iVar6 != 0) {
    return 0;
  }
  iVar6 = FUN_00457800(this,param_1);
  if (iVar6 == 0) {
    return 0;
  }
  iVar6 = 0;
  uVar3 = 0;
  if (uVar5 != 0) {
    do {
      iVar4 = FUN_00457800((void *)(*(int *)((int)this + 0x38) + iVar6),param_1);
      if (iVar4 == 0) {
        return 0;
      }
      iVar6 = iVar6 + 0x24;
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar5);
  }
  return 1;
}


/* 00457c80 size=208 */

undefined4 __thiscall FUN_00457c80(void *this,int *param_1)

{
  int *piVar1;
  int iVar2;
  uint unaff_ESI;
  uint uVar3;
  undefined1 auStackY_ac [128];
  
  iVar2 = (**(code **)(*param_1 + 0xc))(this,0x10);
  if (iVar2 != 0) {
    return 0;
  }
  (**(code **)(*param_1 + 8))(auStackY_ac + 0xa8,4);
  piVar1 = *(int **)(*(int *)((int)this + 0x24) + 0x174);
  if ((unaff_ESI != *(uint *)((int)this + 0x18)) || (unaff_ESI == 0)) {
    if (*(int *)((int)this + 0x14) != 0) {
      FUN_00456e60(piVar1,*(int *)((int)this + 0x14));
      *(undefined4 *)((int)this + 0x14) = 0;
      *(undefined4 *)((int)this + 0x1c) = 0;
    }
    *(uint *)((int)this + 0x18) = unaff_ESI;
    if (unaff_ESI != 0) {
      iVar2 = FUN_00456f10(piVar1,0,*(int *)((int)this + 0x20) + unaff_ESI);
      *(int *)((int)this + 0x14) = iVar2;
      if (iVar2 == 0) {
        *(undefined4 *)((int)this + 0x18) = 0;
        *(undefined4 *)((int)this + 0x1c) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0x1c) = *(undefined4 *)((int)this + 0x20);
    }
  }
  uVar3 = 0;
  if (unaff_ESI != 0) {
    do {
      (**(code **)(*param_1 + 8))(*(int *)((int)this + 0x14) + uVar3 * 4,4);
      uVar3 = uVar3 + 1;
    } while (uVar3 < unaff_ESI);
  }
  return 1;
}


/* 00457d50 size=87 */

undefined4 FUN_00457d50(void)

{
  int iVar1;
  undefined4 uVar2;
  void *this;
  undefined1 local_res0;
  undefined4 *in_stack_00001000;
  int *in_stack_00001004;
  byte abStack_8 [4];
  
  FUN_004ba7f0(local_res0);
  abStack_8[0] = 0;
  abStack_8[1] = 0x10;
  abStack_8[2] = 0;
  abStack_8[3] = 0;
  iVar1 = (**(code **)(*in_stack_00001004 + 0xc))(&local_res0);
  if (iVar1 == 0) {
    uVar2 = FUN_004511d0(this,abStack_8);
    *in_stack_00001000 = uVar2;
    return 1;
  }
  return 0;
}


/* 00457db0 size=386 */

undefined4 __thiscall FUN_00457db0(void *this,int param_1,byte *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int *local_128;
  uint local_124;
  uint local_120;
  int iStack_11c;
  int iStack_118;
  int iStack_114;
  uint auStack_110 [4];
  byte abStack_100 [256];
  
  iVar1 = FUN_004570e0(param_2);
  if (iVar1 == 0) {
    return 0;
  }
  local_120 = 0;
  if (*(int *)((int)this + 0x1d4) != 0) {
    local_128 = (int *)((int)this + 0x194);
    do {
      iVar1 = *local_128;
      (**(code **)(*(int *)param_2 + 8))();
      uVar5 = 0;
      if ((*(int *)(iVar1 + 0x28) != 0) &&
         ((uVar2 = FUN_00451590(*(int *)(iVar1 + 0x28)), local_124 != uVar2 ||
          (*(int *)(iVar1 + 0x20) != *(int *)(*(int *)(iVar1 + 0x28) + 0x1f8))))) {
        *(undefined4 *)(param_1 + 0x1c) = 0;
      }
      if (local_124 != 0) {
        do {
          iVar3 = (**(code **)(*(int *)param_2 + 0xc))();
          if (iVar3 != 0) {
            return 0;
          }
          (**(code **)(*(int *)param_2 + 8))(&iStack_114);
          (**(code **)(*(int *)param_2 + 8))(&iStack_118,4);
          (**(code **)(*(int *)param_2 + 8))(&iStack_11c,4);
          (**(code **)(*(int *)param_2 + 8))(auStack_110 + -0xb,4);
          (**(code **)(*(int *)param_2 + 8))(auStack_110 + -0xc,4);
          (**(code **)(*(int *)param_2 + 8))(auStack_110 + -0xd,4);
          if ((*(void **)(iVar1 + 0x28) != (void *)0x0) &&
             (piVar4 = FUN_004512d0(this,abStack_100,*(void **)(iVar1 + 0x28),auStack_110),
             piVar4 != (int *)0x0)) {
            piVar4[5] = iStack_11c;
            piVar4[6] = iStack_118;
            piVar4[7] = iStack_114;
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < local_124);
      }
      local_120 = local_120 + 1;
      local_128 = local_128 + 1;
    } while (local_120 < *(uint *)((int)this + 0x1d4));
  }
  return 1;
}


