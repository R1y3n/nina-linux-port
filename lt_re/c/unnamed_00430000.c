/* lithtech.exe decompilation - unnamed_00430000 */
#include "ghidra_types.h"

/* 00430006 size=142 */

void FUN_00430006(void)

{
  char *pcVar1;
  char cVar2;
  undefined1 *puVar3;
  uint uVar4;
  uint uVar5;
  int unaff_EBX;
  int unaff_EBP;
  uint unaff_ESI;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  uVar5 = *(uint *)(unaff_EBX + 8);
  if (uVar5 != 0) {
    if (unaff_ESI < uVar5) {
      uVar5 = unaff_ESI;
    }
    puVar6 = *(undefined4 **)(unaff_EBX + 4);
    puVar7 = (undefined4 *)(*(int *)(unaff_EBP + -0x18) + 1);
    for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    unaff_ESI = *(uint *)(unaff_EBP + -0x1c);
  }
  uVar5 = *(uint *)(unaff_EBX + 8);
  if (*(int *)(unaff_EBX + 4) != 0) {
    pcVar1 = (char *)(*(int *)(unaff_EBX + 4) + -1);
    cVar2 = *pcVar1;
    if ((cVar2 == '\0') || (cVar2 == -1)) {
      FUN_00430df0(pcVar1);
    }
    else {
      *pcVar1 = cVar2 + -1;
    }
  }
  *(undefined4 *)(unaff_EBX + 8) = 0;
  puVar3 = *(undefined1 **)(unaff_EBP + -0x18);
  *(undefined1 **)(unaff_EBX + 4) = puVar3 + 1;
  *puVar3 = 0;
  *(uint *)(unaff_EBX + 0xc) = unaff_ESI;
  if (uVar5 <= unaff_ESI) {
    unaff_ESI = uVar5;
  }
  *(uint *)(unaff_EBX + 8) = unaff_ESI;
  *(undefined1 *)(*(int *)(unaff_EBX + 4) + unaff_ESI) = 0;
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}


/* 004300a0 size=201 */

void __fastcall FUN_004300a0(void *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  pcVar5 = *(char **)((int)param_1 + 4);
  if (pcVar5 == (char *)0x0) {
    return;
  }
  cVar1 = pcVar5[-1];
  if (cVar1 == '\0') {
    return;
  }
  if (cVar1 == -1) {
    return;
  }
  pcVar5[-1] = cVar1 + -1;
  uVar3 = 0xffffffff;
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)((int)param_1 + 8) = 0;
  *(undefined4 *)((int)param_1 + 0xc) = 0;
  pcVar6 = pcVar5;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3 - 1;
  if (0xfffffffd < uVar3) {
    FUN_004b97f0();
  }
  iVar2 = *(int *)((int)param_1 + 4);
  if (((iVar2 == 0) || (cVar1 = *(char *)(iVar2 + -1), cVar1 == '\0')) || (cVar1 == -1)) {
    if (uVar3 == 0) {
      FUN_00414100(param_1,'\x01');
      return;
    }
    if ((*(uint *)((int)param_1 + 0xc) < 0x20) && (uVar3 <= *(uint *)((int)param_1 + 0xc)))
    goto LAB_00430147;
    FUN_00414100(param_1,'\x01');
  }
  else if (uVar3 == 0) {
    *(char *)(iVar2 + -1) = cVar1 + -1;
    FUN_00414100(param_1,'\0');
    return;
  }
  FUN_0042ff80(uVar3);
LAB_00430147:
  pcVar6 = *(char **)((int)param_1 + 4);
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  *(uint *)((int)param_1 + 8) = uVar3;
  *(undefined1 *)(uVar3 + *(int *)((int)param_1 + 4)) = 0;
  return;
}


/* 00430170 size=176 */

undefined4 __thiscall FUN_00430170(void *this,int param_1,undefined4 param_2)

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
      iVar1 = (**(code **)(DAT_004ecc58 + 4))(*(int *)((int)this + 0x10) + param_1);
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


/* 00430220 size=183 */

undefined4 __thiscall FUN_00430220(void *this,int param_1,undefined4 param_2)

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
      iVar1 = (**(code **)(DAT_004ecc58 + 4))((*(int *)((int)this + 0x10) + param_1) * 4);
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


/* 004302e0 size=192 */

undefined4 __thiscall FUN_004302e0(void *this,int param_1,int *param_2)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    iVar2 = *(int *)((int)this + 4);
    if (iVar2 != 0) {
      if (iVar2 != 0) {
        (**(code **)(*param_2 + 8))(iVar2);
      }
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    *(int *)((int)this + 8) = param_1;
    if (param_1 != 0) {
      iVar4 = param_1 + *(int *)((int)this + 0x10);
      iVar2 = (**(code **)(*param_2 + 4))(iVar4 * 0x18);
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else if (iVar4 != 0) {
        puVar3 = (undefined1 *)(iVar2 + 0x16);
        do {
          if (puVar3 != (undefined1 *)0x16) {
            puVar1 = puVar3 + -10;
            *puVar3 = 0;
            *(undefined4 *)(puVar3 + -0x16) = 0;
            puVar3[1] = 0;
            *(undefined2 *)(puVar3 + -2) = 0xffff;
            *(undefined4 *)(puVar3 + -0xe) = 0;
            *(undefined4 *)(puVar3 + -0x12) = 0;
            *(undefined1 **)(puVar3 + -6) = puVar1;
            *(undefined1 **)puVar1 = puVar1;
          }
          puVar3 = puVar3 + 0x18;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      *(int *)((int)this + 4) = iVar2;
      if (iVar2 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 004303a0 size=317 */

undefined4 __thiscall FUN_004303a0(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 unaff_retaddr;
  
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
  if (param_1 != uVar5) {
    iVar7 = param_1 + *(int *)((int)this + 0x10);
    puVar2 = (undefined4 *)(**(code **)(*param_3 + 4))(iVar7 * 0x18);
    if (puVar2 == (undefined4 *)0x0) {
      return 0;
    }
    if (iVar7 != 0) {
      puVar3 = (undefined1 *)((int)puVar2 + 0x16);
      do {
        if (puVar3 != (undefined1 *)0x16) {
          puVar1 = puVar3 + -10;
          *puVar3 = 0;
          *(undefined4 *)(puVar3 + -0x16) = 0;
          puVar3[1] = 0;
          *(undefined2 *)(puVar3 + -2) = 0xffff;
          *(undefined4 *)(puVar3 + -0xe) = 0;
          *(undefined4 *)(puVar3 + -0x12) = 0;
          *(undefined1 **)(puVar3 + -6) = puVar1;
          *(undefined1 **)puVar1 = puVar1;
        }
        puVar3 = puVar3 + 0x18;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    uVar5 = *(uint *)((int)this + 8);
    if (param_1 < *(uint *)((int)this + 8)) {
      uVar5 = param_1;
    }
    if (param_1 == 0) {
      uVar10 = 0;
      if (uVar5 != 0) {
        iVar7 = 0;
        do {
          puVar8 = (undefined4 *)(iVar7 + (int)puVar2);
          puVar9 = (undefined4 *)(*(int *)((int)this + 4) + iVar7);
          iVar7 = iVar7 + 0x18;
          uVar5 = uVar5 - 1;
          for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar8 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar8 = puVar8 + 1;
          }
        } while (uVar5 != 0);
        uVar10 = unaff_retaddr;
      }
    }
    else {
      puVar8 = *(undefined4 **)((int)this + 4);
      puVar9 = puVar2;
      for (uVar5 = uVar5 * 0x18 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
        *(undefined1 *)puVar9 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar9 = (undefined4 *)((int)puVar9 + 1);
      }
      uVar10 = unaff_retaddr;
    }
    iVar7 = *(int *)((int)this + 4);
    if (iVar7 != 0) {
      if (iVar7 != 0) {
        (**(code **)(*param_2 + 8))(iVar7);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 **)((int)this + 4) = puVar2;
    *(undefined4 *)((int)this + 8) = uVar10;
    *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  }
  return 1;
}


/* 004304e0 size=229 */

undefined4 __thiscall FUN_004304e0(void *this,int param_1,int *param_2)

{
  void *pvVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  void *this_00;
  int iVar4;
  
  iVar4 = param_1;
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    pvVar1 = *(void **)((int)this + 4);
    if (pvVar1 != (void *)0x0) {
      param_1 = *(int *)((int)this + 0xc) + *(int *)((int)this + 8);
      if (pvVar1 == (void *)0x0) {
        *(undefined4 *)((int)this + 4) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
      }
      else {
        if (param_1 != 0) {
          this_00 = pvVar1;
          do {
            FUN_00430dc0(this_00,0);
            this_00 = (void *)((int)this_00 + 0xc0);
            param_1 = param_1 + -1;
          } while (param_1 != 0);
        }
        (**(code **)(*param_2 + 8))(pvVar1);
        *(undefined4 *)((int)this + 4) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
      }
    }
    *(int *)((int)this + 8) = iVar4;
    if (iVar4 != 0) {
      iVar4 = iVar4 + *(int *)((int)this + 0x10);
      puVar3 = (undefined4 *)(**(code **)(*param_2 + 4))(iVar4 * 0xc0);
      puVar2 = puVar3;
      if (puVar3 != (undefined4 *)0x0) {
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          if (puVar2 != (undefined4 *)0x0) {
            FUN_0042d030(puVar2);
          }
          puVar2 = puVar2 + 0x30;
        }
      }
      *(undefined4 **)((int)this + 4) = puVar3;
      if (puVar3 == (undefined4 *)0x0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 004305d0 size=553 */

undefined4 __thiscall FUN_004305d0(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *unaff_EBP;
  int iVar7;
  undefined4 *puVar8;
  uint unaff_retaddr;
  uint uStack_c;
  void *pvStack_8;
  
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
  iVar7 = param_1 + *(int *)((int)this + 0x10);
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(iVar7 * 0xc0);
  puVar6 = puVar1;
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  for (; iVar7 != 0; iVar7 = iVar7 + -1) {
    if (puVar6 != (undefined4 *)0x0) {
      FUN_0042d030(puVar6);
    }
    puVar6 = puVar6 + 0x30;
  }
  uStack_c = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uStack_c = param_1;
  }
  if (param_1 == 0) {
    if (uStack_c != 0) {
      param_1 = 0;
      puVar6 = puVar1;
      do {
        puVar2 = puVar6 + 1;
        iVar7 = param_1 + *(int *)((int)pvStack_8 + 4);
        do {
          *(undefined1 *)puVar2 = *(undefined1 *)((iVar7 - (int)puVar6) + (int)puVar2);
          puVar2 = (undefined4 *)((int)puVar2 + 1);
        } while ((undefined1 *)((-4 - (int)puVar6) + (int)puVar2) < (undefined1 *)0x41);
        puVar6[0x12] = *(undefined4 *)(iVar7 + 0x48);
        puVar6[0x13] = *(undefined4 *)(iVar7 + 0x4c);
        FUN_00430a90(puVar6 + 0x14,iVar7 + 0x50,&DAT_004ecc58);
        puVar6[0x19] = *(undefined4 *)(iVar7 + 100);
        FUN_00430bd0(puVar6 + 0x1a,iVar7 + 0x68,&DAT_004ecc58);
        puVar6[0x1f] = *(undefined4 *)(iVar7 + 0x7c);
        puVar2 = (undefined4 *)(iVar7 + 0x80);
        puVar8 = puVar6 + 0x20;
        for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar8 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar8 = puVar8 + 1;
        }
        puVar6[0x2c] = *(undefined4 *)(iVar7 + 0xb0);
        puVar6[0x2d] = *(undefined4 *)(iVar7 + 0xb4);
        puVar6[0x2e] = *(undefined4 *)(iVar7 + 0xb8);
        puVar6[0x2f] = *(undefined4 *)(iVar7 + 0xbc);
        param_1 = param_1 + 0xc0;
        uStack_c = uStack_c - 1;
        puVar6 = puVar6 + 0x30;
      } while (uStack_c != 0);
      param_1 = unaff_retaddr;
      this = pvStack_8;
    }
  }
  else {
    puVar6 = *(undefined4 **)((int)this + 4);
    puVar2 = puVar1;
    for (uVar4 = uStack_c * 0xc0 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar2 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar2 = puVar2 + 1;
    }
    for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
      *(undefined1 *)puVar2 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar2 = (undefined4 *)((int)puVar2 + 1);
    }
  }
  puVar6 = *(undefined4 **)((int)this + 4);
  if (puVar6 != (undefined4 *)0x0) {
    iVar7 = *(int *)((int)this + 0xc) + *(int *)((int)this + 8);
    if (puVar6 != (undefined4 *)0x0) {
      if (iVar7 != 0) {
        puVar1 = puVar6;
        do {
          FUN_0042d120(puVar1);
          puVar1 = puVar1 + 0x30;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      (**(code **)(*param_2 + 8))(puVar6);
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


/* 00430800 size=170 */

undefined4 __thiscall FUN_00430800(void *this,int param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  
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
      puVar1 = FUN_00414d50(&DAT_004ecc58,0,*(int *)((int)this + 0x10) + param_1);
      *(undefined1 **)((int)this + 4) = puVar1;
      if (puVar1 == (undefined1 *)0x0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 004308b0 size=182 */

undefined4 __thiscall FUN_004308b0(void *this,int param_1,undefined4 param_2)

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
      iVar1 = (**(code **)(DAT_004ecc58 + 4))((*(int *)((int)this + 0x10) + param_1) * 0x18);
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


/* 00430970 size=283 */

void __cdecl FUN_00430970(undefined1 *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  if (param_1 != (undefined1 *)0x0) {
    uVar1 = *param_2;
    *(undefined4 *)(param_1 + 4) = 0;
    *param_1 = uVar1;
    *(undefined4 *)(param_1 + 8) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    uVar7 = DAT_004cc284;
    uVar3 = *(uint *)(param_2 + 8);
    uVar6 = uVar3;
    if (DAT_004cc284 < uVar3) {
      uVar6 = DAT_004cc284;
    }
    if (param_1 == param_2) {
      if (uVar6 != 0) {
        FUN_004b9a1c();
      }
      FUN_004300a0(param_1);
      uVar3 = *(int *)(param_1 + 8) - uVar6;
      if (uVar3 < uVar7) {
        uVar7 = uVar3;
      }
      if (uVar7 != 0) {
        FUN_004bab10((undefined4 *)(uVar6 + *(int *)(param_1 + 4)),
                     (undefined4 *)((int)(uVar6 + *(int *)(param_1 + 4)) + uVar7),uVar3 - uVar7);
        iVar2 = *(int *)(param_1 + 8);
        uVar4 = FUN_0042fe50(param_1,iVar2 - uVar7,'\0');
        if ((char)uVar4 != '\0') {
          FUN_0042fe30(param_1,iVar2 - uVar7);
        }
      }
      FUN_004300a0(param_1);
      return;
    }
    if ((uVar6 != 0) && (uVar6 == uVar3)) {
      puVar5 = *(undefined1 **)(param_2 + 4);
      if (puVar5 == (undefined1 *)0x0) {
        puVar5 = &DAT_004cc108;
      }
      if ((byte)puVar5[-1] < 0xfe) {
        FUN_00414100(param_1,'\x01');
        puVar5 = *(undefined1 **)(param_2 + 4);
        if (puVar5 == (undefined1 *)0x0) {
          puVar5 = &DAT_004cc108;
        }
        *(undefined1 **)(param_1 + 4) = puVar5;
        *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
        *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
        puVar5[-1] = puVar5[-1] + '\x01';
        return;
      }
    }
    uVar4 = FUN_0042fe50(param_1,uVar6,'\x01');
    if ((char)uVar4 != '\0') {
      puVar8 = *(undefined4 **)(param_2 + 4);
      if (puVar8 == (undefined4 *)0x0) {
        puVar8 = (undefined4 *)&DAT_004cc108;
      }
      puVar9 = *(undefined4 **)(param_1 + 4);
      for (uVar3 = uVar6 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      for (uVar3 = uVar6 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar9 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar9 = (undefined4 *)((int)puVar9 + 1);
      }
      *(uint *)(param_1 + 8) = uVar6;
      *(undefined1 *)(*(int *)(param_1 + 4) + uVar6) = 0;
    }
  }
  return;
}


/* 00430a90 size=184 */

undefined4 __thiscall FUN_00430a90(void *this,int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  
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
    iVar1 = (**(code **)(*param_2 + 4))(iVar1 * 4);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    *(int *)((int)this + 4) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)((int)this + 8) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
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


/* 00430b50 size=66 */

void __thiscall FUN_00430b50(void *this,int *param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = *(undefined4 **)((int)this + 4);
  puVar2 = puVar1;
  if (puVar1 != (undefined4 *)0x0) {
    for (; param_2 != 0; param_2 = param_2 + -1) {
      FUN_0042d120(puVar2);
      puVar2 = puVar2 + 0x30;
    }
    (**(code **)(*param_1 + 8))(puVar1);
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  return;
}


/* 00430bd0 size=263 */

undefined4 __thiscall FUN_00430bd0(void *this,int param_1,int *param_2)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int unaff_retaddr;
  
  iVar3 = *(int *)((int)this + 4);
  if (iVar3 != 0) {
    if (iVar3 != 0) {
      (**(code **)(*param_2 + 8))(iVar3);
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)((int)this + 0x10) = *(undefined4 *)(param_1 + 0x10);
  iVar3 = *(int *)((int)this + 8) + *(int *)((int)this + 0xc);
  if (iVar3 == 0) {
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    iVar2 = (**(code **)(*param_2 + 4))(iVar3 * 0x18);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else if (iVar3 != 0) {
      puVar4 = (undefined1 *)(iVar2 + 0x16);
      do {
        if (puVar4 != (undefined1 *)0x16) {
          puVar1 = puVar4 + -10;
          *puVar4 = 0;
          *(undefined4 *)(puVar4 + -0x16) = 0;
          puVar4[1] = 0;
          *(undefined2 *)(puVar4 + -2) = 0xffff;
          *(undefined4 *)(puVar4 + -0xe) = 0;
          *(undefined4 *)(puVar4 + -0x12) = 0;
          *(undefined1 **)(puVar4 + -6) = puVar1;
          *(undefined1 **)puVar1 = puVar1;
        }
        puVar4 = puVar4 + 0x18;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    *(int *)((int)this + 4) = iVar2;
    if (iVar2 == 0) {
      *(undefined4 *)((int)this + 8) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
      return 0;
    }
    uVar5 = 0;
    if (*(int *)((int)this + 8) != 0) {
      iVar3 = 0;
      do {
        uVar5 = uVar5 + 1;
        puVar6 = (undefined4 *)(iVar3 + *(int *)(unaff_retaddr + 4));
        puVar7 = (undefined4 *)(iVar3 + *(int *)((int)this + 4));
        for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar7 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar7 = puVar7 + 1;
        }
        iVar3 = iVar3 + 0x18;
      } while (uVar5 < *(uint *)((int)this + 8));
      return 1;
    }
  }
  return 1;
}


/* 00430ce0 size=84 */

int __cdecl FUN_00430ce0(int *param_1,undefined4 param_2,int param_3)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  
  iVar2 = (**(code **)(*param_1 + 4))(param_3 * 0x18);
  if (iVar2 == 0) {
    return 0;
  }
  if (param_3 != 0) {
    puVar3 = (undefined1 *)(iVar2 + 0x16);
    do {
      if (puVar3 != (undefined1 *)0x16) {
        puVar1 = puVar3 + -10;
        *puVar3 = 0;
        *(undefined4 *)(puVar3 + -0x16) = 0;
        puVar3[1] = 0;
        *(undefined2 *)(puVar3 + -2) = 0xffff;
        *(undefined4 *)(puVar3 + -0xe) = 0;
        *(undefined4 *)(puVar3 + -0x12) = 0;
        *(undefined1 **)(puVar3 + -6) = puVar1;
        *(undefined1 **)puVar1 = puVar1;
      }
      puVar3 = puVar3 + 0x18;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return iVar2;
}


/* 00430d40 size=51 */

void __cdecl FUN_00430d40(int *param_1,undefined4 *param_2,int param_3)

{
  undefined4 *puVar1;
  
  puVar1 = param_2;
  if (param_2 != (undefined4 *)0x0) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      FUN_0042d120(puVar1);
      puVar1 = puVar1 + 0x30;
    }
    (**(code **)(*param_1 + 8))(param_2);
  }
  return;
}


/* 00430d80 size=64 */

undefined4 * __cdecl FUN_00430d80(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(**(code **)(*param_1 + 4))(param_3 * 0xc0);
  puVar1 = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    if (puVar1 != (undefined4 *)0x0) {
      FUN_0042d030(puVar1);
    }
    puVar1 = puVar1 + 0x30;
  }
  return puVar2;
}


/* 00430dc0 size=30 */

undefined4 * __thiscall FUN_00430dc0(void *this,byte param_1)

{
  FUN_0042d120(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00430de0 size=14 */

int __cdecl FUN_00430de0(size_t param_1)

{
  FUN_00430f00(param_1);
  return;
}


/* 00430df0 size=12 */

int __cdecl FUN_00430df0(undefined *param_1)

{
  FUN_00430fe0(param_1);
  return;
}


/* 00430e20 size=73 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00430e20(void)

{
  if (DAT_004e9604 == 0) {
    DAT_004e95f8 = 0;
    DAT_004e95f0 = FUN_004bbc22(&LAB_00430e70);
    _DAT_004e95ec = 0;
    DAT_004e9600 = 0;
    DAT_004e95f4 = 0;
    DAT_004e95fc = 0;
  }
  DAT_004e9604 = DAT_004e9604 + 1;
  return;
}


/* 00430e80 size=77 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00430e80(void)

{
  undefined *puVar1;
  undefined *puVar2;
  
  DAT_004e9604 = DAT_004e9604 + -1;
  puVar2 = DAT_004e95f8;
  if (DAT_004e9604 == 0) {
    while (puVar2 != (undefined *)0x0) {
      puVar1 = *(undefined **)(puVar2 + 8);
      FUN_004b9d3f(puVar2);
      puVar2 = puVar1;
    }
    FUN_004bbc22(DAT_004e95f0);
    _DAT_004e95ec = 0;
    DAT_004e9600 = 0;
  }
  return;
}


/* 00430ed0 size=42 */

void __cdecl FUN_00430ed0(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = _malloc(0xc);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
    puVar1[1] = param_2;
    puVar1[2] = DAT_004e95f8;
    DAT_004e95f8 = puVar1;
  }
  return;
}


/* 00430f00 size=141 */

void * __cdecl FUN_00430f00(size_t param_1)

{
  void *pvVar1;
  undefined8 uVar2;
  LARGE_INTEGER local_c;
  int *local_4;
  
  if (param_1 == 0) {
    return (void *)0x0;
  }
  FUN_00424310(&local_c,0);
  local_4 = &DAT_004e9608;
  FUN_00424400(&local_c);
  pvVar1 = _malloc(param_1);
  uVar2 = FUN_00424410((uint *)&local_c);
  *local_4 = *local_4 + (int)uVar2;
  if (pvVar1 == (void *)0x0) {
    FUN_00430f90();
    pvVar1 = _malloc(param_1);
    if (pvVar1 == (void *)0x0) {
      FUN_004364e0();
    }
  }
  DAT_004e95fc = DAT_004e95fc + 1;
  DAT_004e9600 = DAT_004e9600 + 1;
  return pvVar1;
}


/* 00430f90 size=29 */

void FUN_00430f90(void)

{
  undefined4 *puVar1;
  
  for (puVar1 = DAT_004e95f8; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)puVar1[2]) {
    (*(code *)*puVar1)(puVar1[1]);
  }
  return;
}


/* 00430fb0 size=48 */

undefined4 * __cdecl FUN_00430fb0(uint param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  puVar1 = FUN_00430f00(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  puVar3 = puVar1;
  for (uVar2 = param_1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  for (uVar2 = param_1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)puVar3 = 0;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  return puVar1;
}


/* 00430fe0 size=95 */

void __cdecl FUN_00430fe0(undefined *param_1)

{
  undefined8 uVar1;
  LARGE_INTEGER local_c;
  int *local_4;
  
  if (param_1 != (undefined *)0x0) {
    DAT_004e9600 = DAT_004e9600 + -1;
    DAT_004e95f4 = DAT_004e95f4 + 1;
    FUN_00424310(&local_c,0);
    local_4 = &DAT_004e960c;
    FUN_00424400(&local_c);
    FUN_004b9d3f(param_1);
    uVar1 = FUN_00424410((uint *)&local_c);
    *local_4 = *local_4 + (int)uVar1;
  }
  return;
}


/* 00431110 size=33 */

void FUN_00431110(void)

{
  if (DAT_004e966c == 0) {
    FUN_004b7b90((uint *)&DAT_004e9650,0x20,0x20);
  }
  DAT_004e966c = DAT_004e966c + 1;
  return;
}


/* 00431140 size=25 */

void FUN_00431140(void)

{
  DAT_004e966c = DAT_004e966c + -1;
  if (DAT_004e966c == 0) {
    FUN_004b7c50(0x4e9650);
  }
  return;
}


/* 00431160 size=156 */

int * __cdecl FUN_00431160(int *param_1,float *param_2,float param_3)

{
  int iVar1;
  float fVar2;
  float *pfVar3;
  
  while( true ) {
    while( true ) {
      iVar1 = *param_1;
      if ((iVar1 == 0) || (*(int *)(iVar1 + 0x2c) == 0)) {
        pfVar3 = (float *)0x0;
      }
      else {
        pfVar3 = *(float **)(iVar1 + 0x28);
      }
      fVar2 = (*param_2 * *pfVar3 + param_2[1] * pfVar3[1] + param_2[2] * pfVar3[2]) - pfVar3[3];
      if (fVar2 <= param_3) break;
      if ((int *)param_1[2] == (int *)PTR_DAT_004d7c44) {
        return param_1;
      }
      param_1 = (int *)param_1[2];
    }
    if (-param_3 <= fVar2) break;
    param_1 = (int *)param_1[1];
    if (param_1 == (int *)PTR_DAT_004d7c48) {
      return (int *)0x0;
    }
  }
  return param_1;
}


/* 00431200 size=514 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_00431200(int param_1,int *param_2,float *param_3,int param_4,int param_5,int param_6)

{
  float *pfVar1;
  undefined4 *puVar2;
  int *piVar3;
  float *pfVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  
  if ((*(byte *)((int)param_2 + 0x16) & 3) == 0) {
    while ((short)param_2[5] == -1) {
      iVar7 = *param_2;
      if ((iVar7 == 0) || (*(int *)(iVar7 + 0x2c) == 0)) {
        pfVar4 = (float *)0x0;
      }
      else {
        pfVar4 = *(float **)(iVar7 + 0x28);
      }
      uVar6 = (uint)(_DAT_004cb524 <
                    (*param_3 * *pfVar4 + param_3[1] * pfVar4[1] + param_3[2] * pfVar4[2]) -
                    pfVar4[3]);
      _DAT_004e9644 = 1;
      if (1 < param_4) {
        do {
          iVar7 = *param_2;
          if ((iVar7 == 0) || (*(int *)(iVar7 + 0x2c) == 0)) {
            pfVar4 = (float *)0x0;
          }
          else {
            pfVar4 = *(float **)(iVar7 + 0x28);
          }
          pfVar1 = param_3 + _DAT_004e9644 * 3;
          _DAT_004e9640 =
               (uint)(_DAT_004cb524 <
                     (*pfVar1 * *pfVar4 + pfVar1[1] * pfVar4[1] + pfVar1[2] * pfVar4[2]) - pfVar4[3]
                     );
          if (_DAT_004e9640 != uVar6) goto LAB_00431315;
          _DAT_004e9644 = _DAT_004e9644 + 1;
        } while (_DAT_004e9644 < param_4);
      }
      if (uVar6 == 2) {
LAB_00431315:
        FUN_00431200(param_1,(int *)param_2[1],param_3,param_4,param_5,param_6);
        param_2 = (int *)param_2[2];
      }
      else {
        param_2 = (int *)param_2[uVar6 + 1];
      }
      if ((*(byte *)((int)param_2 + 0x16) & 3) != 0) {
        return;
      }
    }
    if ((uint)*(ushort *)(param_2 + 5) < *(uint *)(param_1 + 0x8c)) {
      iVar7 = (uint)*(ushort *)(param_2 + 5) * 0x30 + *(int *)(param_1 + 0x88);
    }
    else {
      iVar7 = 0;
    }
    if ((DAT_004e9668 != (int *)0x0) ||
       (FUN_004b7c60(0x4e9650,DAT_004e9658), DAT_004e9648 = DAT_004e9668, DAT_004e9668 != (int *)0x0
       )) {
      DAT_004e9648 = DAT_004e9668;
      DAT_004e9668 = (int *)*DAT_004e9668;
    }
    if (DAT_004e9648 != (int *)0x0) {
      DAT_004e9648[5] = (int)DAT_004e9648;
      DAT_004e9648[2] = (int)DAT_004e9648;
      DAT_004e9648[6] = param_5;
      DAT_004e9648[7] = iVar7;
      piVar3 = DAT_004e9648;
      *DAT_004e9648 = iVar7 + 0x14;
      puVar2 = *(undefined4 **)(iVar7 + 0x18);
      piVar3[1] = (int)puVar2;
      *puVar2 = piVar3;
      *(int **)(*piVar3 + 4) = piVar3;
      piVar3 = DAT_004e9648;
      piVar5 = DAT_004e9648 + 3;
      *piVar5 = param_6;
      puVar2 = *(undefined4 **)(param_6 + 4);
      piVar3[4] = (int)puVar2;
      *puVar2 = piVar5;
      *(int **)(*piVar5 + 4) = piVar5;
    }
  }
  return;
}


/* 00431410 size=507 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00431410: lifted from original x86 -> lt_lifted.c */


/* 00431610 size=108 */

void __cdecl FUN_00431610(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x1f0);
  while (iVar4 != param_1 + 0x1ec) {
    iVar2 = *(int *)(iVar4 + 4);
    piVar3 = *(int **)(iVar4 + 8);
    *(int *)(*piVar3 + 4) = piVar3[1];
    *(int *)piVar3[1] = *piVar3;
    piVar1 = piVar3 + 3;
    piVar3[1] = (int)piVar3;
    *piVar3 = (int)piVar3;
    *(int *)(*piVar1 + 4) = piVar3[4];
    *(int *)piVar3[4] = *piVar1;
    piVar3[4] = (int)piVar1;
    *piVar1 = (int)piVar1;
    iVar4 = iVar2;
    if (piVar3 != (int *)0x0) {
      *piVar3 = (int)DAT_004e9668;
      DAT_004e9668 = piVar3;
    }
  }
  return;
}


/* 00431680 size=145 */

int * __cdecl FUN_00431680(int param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  FUN_00431720((int)param_2);
  piVar4 = FUN_00431160(*(int **)(param_1 + 0x9c),(float *)(param_2 + 0x65),(float)param_2[0x6b]);
  if (piVar4 != (int *)0x0) {
    piVar1 = param_2 + 0x1b;
    if (param_2[100] != 0) {
      *piVar1 = (int)(piVar4 + 3);
      piVar2 = (int *)piVar4[4];
      param_2[0x1c] = (int)piVar2;
      *piVar2 = (int)piVar1;
      *(int **)(*piVar1 + 4) = piVar1;
      param_2[0x1e] = (int)piVar4;
      return piVar4;
    }
    iVar3 = piVar4[3];
    *piVar1 = iVar3;
    piVar2 = *(int **)(iVar3 + 4);
    param_2[0x1c] = (int)piVar2;
    *piVar2 = (int)piVar1;
    *(int **)(*piVar1 + 4) = piVar1;
    if ((char)param_2[0x2f] == '\a') {
      FUN_00431410(param_1,param_2);
    }
    param_2[0x1e] = (int)piVar4;
  }
  return piVar4;
}


/* 00431720 size=61 */

void __cdecl FUN_00431720(int param_1)

{
  undefined4 *puVar1;
  
  if (*(int *)(param_1 + 0x78) != 0) {
    puVar1 = (undefined4 *)(param_1 + 0x6c);
    *(undefined4 *)(*(int *)(param_1 + 0x6c) + 4) = *(undefined4 *)(param_1 + 0x70);
    **(undefined4 **)(param_1 + 0x70) = *puVar1;
    *(undefined4 **)(param_1 + 0x70) = puVar1;
    *puVar1 = puVar1;
    *(undefined4 *)(param_1 + 0x78) = 0;
  }
  if (*(char *)(param_1 + 0xbc) == '\a') {
    FUN_00431610(param_1);
  }
  return;
}


/* 00431760 size=70 */

void __cdecl FUN_00431760(int param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)**(undefined4 **)(param_1 + 0x1b0))();
  if (iVar1 == 0) {
    FUN_0043d160((float *)(*(int *)(param_1 + 0x1b0) + 0xe8),(float *)(param_1 + 0x194),
                 (float *)(param_1 + 0x9c),(float *)(param_1 + 0x1f8),(float *)(param_1 + 0x238));
  }
  return;
}


/* 004317e0 size=62 */

/* FUN_004317e0: lifted from original x86 -> lt_lifted.c */


/* 00431830 size=43 */

undefined4 __fastcall FUN_00431830(int *param_1)

{
  if ((*param_1 != 0) && (param_1[1] != 0)) {
    (**(code **)(*param_1 + 0x17c))(param_1[1]);
  }
  param_1[1] = 0;
  *param_1 = 0;
  return 0;
}


/* 00431860 size=280 */

int __thiscall FUN_00431860(void *this,int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  int local_4;
  
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  iVar2 = FUN_00431ca0(this);
  if (iVar2 != 0) {
    return 0x49;
  }
  iVar2 = *(int *)((int)this + 0x1c) - *(int *)((int)this + 0x14);
  local_20 = iVar2 + -2;
  local_18 = iVar2 + -1;
  if (param_2 == 0) {
    local_4 = (*(int *)((int)this + 0x20) - *(int *)((int)this + 0x18)) + -1;
    local_10 = 2;
    local_c = 1;
    local_8 = iVar2;
    iVar2 = (**(code **)(*(int *)this + 0x1a8))
                      (*(undefined4 *)((int)this + 4),*(undefined4 *)((int)this + 4),&local_10,1,1);
    if (iVar2 != 0) {
      return iVar2;
    }
    local_14 = (*(int *)((int)this + 0x20) - *(int *)((int)this + 0x18)) + -1;
    local_1c = 1;
    iVar2 = (**(code **)(*(int *)this + 0x1d0))(*(undefined4 *)((int)this + 4),&local_20,0);
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  iVar2 = *(int *)((int)this + 0x20);
  iVar1 = *(int *)((int)this + 0x18);
  lVar3 = __ftol();
  local_1c = ((iVar2 - (int)lVar3) - iVar1) + -2;
  local_14 = (iVar2 - iVar1) + -1;
  iVar2 = (**(code **)(*(int *)this + 0x1d0))
                    (*(undefined4 *)((int)this + 4),&local_20,*(undefined4 *)(param_1 + 4));
  return iVar2;
}


/* 00431980 size=152 */

int __fastcall FUN_00431980(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iStack_8;
  undefined1 auStack_4 [4];
  
  iVar1 = FUN_00431ca0(param_1);
  if (iVar1 != 0) {
    return 0x49;
  }
  iVar1 = *param_1;
  uVar2 = (**(code **)(iVar1 + 0x16c))(param_1[1],0,param_1[5],param_1[6],0x80000000);
  iVar1 = (**(code **)(iVar1 + 0x1ac))(uVar2);
  if (iVar1 == 0) {
    if (param_1[2] != 0) {
      (**(code **)(*param_1 + 0x198))(param_1[2],auStack_4,&iStack_8);
      iVar1 = *param_1;
      uVar2 = (**(code **)(iVar1 + 0x16c))(param_1[2],0,param_1[5],param_1[6] - iStack_8,0x80000000)
      ;
      iVar1 = (**(code **)(iVar1 + 0x1ac))(uVar2);
      if (iVar1 != 0) {
        return iVar1;
      }
    }
    iVar1 = 0;
  }
  return iVar1;
}


/* 00431a20 size=85 */

undefined4 __thiscall FUN_00431a20(void *this,int *param_1)

{
  if (((param_1 == (int *)0x0) || (param_1[3] <= param_1[1] + *(int *)((int)this + 0x10))) ||
     (param_1[2] <= *param_1)) {
    return 1;
  }
  *(int *)((int)this + 0x14) = *param_1;
  *(int *)((int)this + 0x18) = param_1[1];
  *(int *)((int)this + 0x1c) = param_1[2];
  *(int *)((int)this + 0x20) = param_1[3];
  *(int *)((int)this + 0x18) = *(int *)((int)this + 0x18) + *(int *)((int)this + 0x10);
  return 0;
}


/* 00431a80 size=191 */

undefined4 * __fastcall FUN_00431a80(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + 1;
  *puVar1 = &PTR_LAB_004cc2b8;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[5] = 0;
  param_1[4] = 0;
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  puVar1 = param_1 + 6;
  *puVar1 = &PTR_LAB_004cc288;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  FUN_004331a0(puVar1,0,&DAT_004ecc58);
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[10] = 0;
  param_1[9] = 0;
  if (param_1[7] != 0) {
    FUN_00433910(puVar1,&DAT_004ecc58,param_1[8]);
  }
  param_1[8] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  *param_1 = 0;
  param_1[0x12] = 0x9e;
  param_1[0x13] = 0x4e;
  param_1[0x14] = 2;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  return param_1;
}


/* 00431b40 size=115 */

void __fastcall FUN_00431b40(int *param_1)

{
  int iVar1;
  
  FUN_00431cb0(param_1);
  param_1[6] = (int)&PTR_LAB_004cc288;
  if (param_1[7] != 0) {
    FUN_00433ac0(&DAT_004ecc58,param_1[7],param_1[8] + param_1[9]);
    param_1[7] = 0;
    param_1[9] = 0;
  }
  param_1[8] = 0;
  iVar1 = param_1[2];
  param_1[1] = (int)&PTR_LAB_004cc2b8;
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    param_1[2] = 0;
    param_1[4] = 0;
  }
  param_1[3] = 0;
  return;
}


/* 00431bc0 size=215 */

int __thiscall FUN_00431bc0(void *this,int param_1,undefined4 *param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    return 1;
  }
  iVar1 = FUN_00432110(this,param_2);
  if (iVar1 == 0) {
    iVar1 = FUN_00431ca0(this);
    if (iVar1 != 0) {
      FUN_00431cb0(this);
    }
    FUN_00468190((void *)((int)this + 4),0,&DAT_004ecc58);
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 *)((int)this + 0x14) = 0;
    *(undefined4 *)((int)this + 0x10) = 0;
    if (*(int *)((int)this + 8) != 0) {
      FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 8));
      *(undefined4 *)((int)this + 8) = 0;
      *(undefined4 *)((int)this + 0x10) = 0;
    }
    *(undefined4 *)((int)this + 0xc) = 0;
    if (*(int *)((int)this + 0x1c) != 0) {
      FUN_00433910((void *)((int)this + 0x18),&DAT_004ecc58,
                   *(int *)((int)this + 0x24) + *(int *)((int)this + 0x20));
    }
    *(undefined4 *)((int)this + 0x1c) = 0;
    *(undefined4 *)((int)this + 0x20) = 0;
    *(undefined4 *)((int)this + 0x28) = 0;
    *(undefined4 *)((int)this + 0x24) = 0;
    if (*(int *)((int)this + 0x1c) != 0) {
      FUN_00433ac0(&DAT_004ecc58,*(int *)((int)this + 0x1c),*(int *)((int)this + 0x20));
      *(undefined4 *)((int)this + 0x1c) = 0;
      *(undefined4 *)((int)this + 0x24) = 0;
    }
    *(undefined4 *)((int)this + 0x20) = 0;
    *(int *)this = param_1;
    iVar1 = 0;
  }
  return iVar1;
}


/* 00431ca0 size=12 */

int __fastcall FUN_00431ca0(int *param_1)

{
  return (-(uint)(*param_1 != 0) & 0xffffffb7) + 0x49;
}


/* 00431cb0 size=142 */

undefined4 __fastcall FUN_00431cb0(int *param_1)

{
  void *pvVar1;
  int iVar2;
  void *this;
  
  iVar2 = FUN_00431ca0(param_1);
  if (iVar2 == 0) {
    return 0;
  }
  FUN_00431e10(param_1);
  if (param_1[2] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[2]);
    param_1[2] = 0;
    param_1[4] = 0;
  }
  param_1[3] = 0;
  pvVar1 = (void *)param_1[7];
  if (pvVar1 != (void *)0x0) {
    iVar2 = param_1[8] + param_1[9];
    if (pvVar1 != (void *)0x0) {
      if (iVar2 != 0) {
        this = pvVar1;
        do {
          dsys_interface_433c20(this,0);
          this = (void *)((int)this + 0x1c);
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      (**(code **)(DAT_004ecc58 + 8))(pvVar1);
    }
    param_1[7] = 0;
    param_1[9] = 0;
  }
  param_1[8] = 0;
  *param_1 = 0;
  return 0;
}


/* 00431d40 size=12 */

void __fastcall FUN_00431d40(int param_1)

{
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  return;
}


/* 00431d50 size=192 */

void __thiscall FUN_00431d50(void *this,uint param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int local_10 [4];
  
  FUN_00433590((void *)((int)this + 4),param_1,&DAT_004ecc58);
  iVar3 = param_1 * 0x1c;
  piVar1 = *(int **)(*(int *)((int)this + 0x1c) + 4 + iVar3);
  if (piVar1 != (int *)0x0) {
    thunk_FUN_00431830(piVar1);
    FUN_00430df0((undefined *)piVar1);
  }
  FUN_004336a0((void *)((int)this + 0x18),param_1,&DAT_004ecc58);
  if (param_1 <= *(uint *)((int)this + 0x34)) {
    FUN_00431d40((int)this);
  }
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_10[3] = 0;
  if (param_1 < *(uint *)((int)this + 0x20)) {
    while (iVar2 = FUN_00431fe0(this,local_10,param_1), iVar2 != 0) {
      iVar2 = FUN_00431a20(*(void **)(*(int *)((int)this + 0x1c) + 4 + iVar3),local_10);
      if (iVar2 == 0) {
        FUN_00431d50(this,param_1);
        return;
      }
      param_1 = param_1 + 1;
      iVar3 = iVar3 + 0x1c;
      if (*(uint *)((int)this + 0x20) <= param_1) {
        return;
      }
    }
  }
  return;
}


/* 00431e10 size=81 */

void __fastcall FUN_00431e10(void *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)((int)param_1 + 0x20);
  while (iVar1 != 0) {
    FUN_00431d50(param_1,iVar1 - 1);
    iVar1 = *(int *)((int)param_1 + 0x20);
  }
  iVar1 = *(int *)((int)param_1 + 8);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    *(undefined4 *)((int)param_1 + 8) = 0;
    *(undefined4 *)((int)param_1 + 0x10) = 0;
  }
  *(undefined4 *)((int)param_1 + 0xc) = 0;
  return;
}


/* 00431e70 size=365 */

/* WARNING: Removing unreachable block (ram,0x00431f09) */
/* WARNING: Removing unreachable block (ram,0x00431f28) */
/* WARNING: Removing unreachable block (ram,0x00431f2c) */
/* WARNING: Removing unreachable block (ram,0x00431f30) */
/* WARNING: Removing unreachable block (ram,0x00431f39) */
/* WARNING: Removing unreachable block (ram,0x00431f3f) */
/* WARNING: Removing unreachable block (ram,0x00431f46) */
/* WARNING: Removing unreachable block (ram,0x00431f48) */
/* WARNING: Removing unreachable block (ram,0x00431f4e) */
/* WARNING: Removing unreachable block (ram,0x00431f6d) */
/* WARNING: Removing unreachable block (ram,0x00431f6f) */
/* WARNING: Removing unreachable block (ram,0x00431f76) */
/* WARNING: Removing unreachable block (ram,0x00431f86) */
/* WARNING: Removing unreachable block (ram,0x00431f95) */
/* WARNING: Removing unreachable block (ram,0x00431f98) */
/* WARNING: Removing unreachable block (ram,0x00431fa7) */

int __fastcall FUN_00431e70(int param_1)

{
  int *this;
  int iVar1;
  int iVar2;
  uint uVar3;
  int local_14;
  uint local_c;
  
  if (*(int *)(param_1 + 0x20) == 0) {
    return 0;
  }
  iVar2 = 0;
  local_c = 0;
  if (*(int *)(param_1 + 0x20) != 0) {
    local_14 = 0;
    do {
      if (iVar2 != 0) {
        return iVar2;
      }
      iVar2 = *(int *)(param_1 + 0x1c) + local_14;
      this = *(int **)(iVar2 + 4);
      if (*(int *)(iVar2 + 0x10) != 0) {
        uVar3 = 0;
        if (*(int *)(iVar2 + 0x10) != 0) {
          do {
            FUN_00431860(this,*(int *)(iVar2 + 0xc) + uVar3 * 8,(uint)(uVar3 != 0));
            uVar3 = uVar3 + 1;
          } while (uVar3 < *(uint *)(iVar2 + 0x10));
        }
        iVar1 = *(int *)(iVar2 + 0x10);
        if (iVar1 != 0) {
          *(undefined4 *)(iVar2 + 0x10) = 0;
          *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + iVar1;
        }
      }
      iVar2 = FUN_00431980(this);
      local_c = local_c + 1;
      local_14 = local_14 + 0x1c;
    } while (local_c < *(uint *)(param_1 + 0x20));
  }
  return iVar2;
}


/* 00431fe0 size=117 */

undefined4 __thiscall FUN_00431fe0(void *this,int *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = *(uint *)((int)this + 0x54);
  uVar2 = *(uint *)((int)this + 0x58);
  if (param_2 < uVar1 * uVar2) {
    iVar3 = ((uVar1 - param_2 / uVar1) + -1) *
            (*(int *)((int)this + 0x48) + *(int *)((int)this + 0x50)) + *(int *)((int)this + 0x5c) +
            *(int *)((int)this + 0x50);
    *param_1 = iVar3;
    param_1[1] = (*(int *)((int)this + 0x4c) + *(int *)((int)this + 0x50)) * (param_2 % uVar2);
    param_1[2] = *(int *)((int)this + 0x48) + iVar3;
    param_1[3] = param_1[1] + *(int *)((int)this + 0x4c);
    return 1;
  }
  return 0;
}


/* 00432060 size=175 */

undefined4 __thiscall FUN_00432060(void *this,uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  if ((((param_1 < 0x20) || (param_2 < 0x10)) ||
      ((uint)(*(int *)((int)this + 0x40) - *(int *)((int)this + 0x38)) <
       *(int *)((int)this + 0x50) + param_1)) ||
     ((uint)(*(int *)((int)this + 0x44) - *(int *)((int)this + 0x3c)) <
      *(int *)((int)this + 0x50) + param_2)) {
    return 1;
  }
  FUN_00431e10(this);
  *(uint *)((int)this + 0x48) = param_1;
  uVar1 = (uint)(*(int *)((int)this + 0x40) - *(int *)((int)this + 0x38)) /
          (param_1 + *(int *)((int)this + 0x50));
  *(uint *)((int)this + 0x4c) = param_2;
  uVar2 = (uint)(*(int *)((int)this + 0x44) - *(int *)((int)this + 0x3c)) /
          (*(int *)((int)this + 0x50) + param_2);
  *(uint *)((int)this + 0x54) = uVar1;
  *(uint *)((int)this + 0x5c) =
       (*(int *)((int)this + 0x40) - uVar1 * param_1) - *(int *)((int)this + 0x38);
  *(uint *)((int)this + 0x58) = uVar2;
  *(uint *)((int)this + 0x60) =
       (*(int *)((int)this + 0x44) - uVar2 * param_2) - *(int *)((int)this + 0x3c);
  return 0;
}


/* 00432110 size=83 */

int __thiscall FUN_00432110(void *this,undefined4 *param_1)

{
  int iVar1;
  
  if (param_1 == (undefined4 *)0x0) {
    return 1;
  }
  *(undefined4 *)((int)this + 0x38) = *param_1;
  *(undefined4 *)((int)this + 0x3c) = param_1[1];
  *(undefined4 *)((int)this + 0x40) = param_1[2];
  *(undefined4 *)((int)this + 0x44) = param_1[3];
  iVar1 = FUN_00432060(this,*(uint *)((int)this + 0x48),*(uint *)((int)this + 0x4c));
  if (iVar1 != 0) {
    *(undefined4 *)((int)this + 0x54) = 0;
    *(undefined4 *)((int)this + 0x58) = 0;
  }
  return iVar1;
}


/* 00432170 size=298 */

/* WARNING: Removing unreachable block (ram,0x00432255) */

undefined4 __thiscall FUN_00432170(void *this,undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  uVar1 = *(uint *)((int)this + 8);
  if (*(int *)((int)this + 0xc) != 0) {
    iVar2 = *(int *)((int)this + 4);
    *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
    *(undefined4 *)(iVar2 + uVar1 * 8) = *param_1;
    *(undefined4 *)(iVar2 + 4 + uVar1 * 8) = param_1[1];
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    return 1;
  }
  puVar3 = FUN_00433a80(&DAT_004ecc58,0,*(int *)((int)this + 0x10) + 1 + uVar1);
  if (puVar3 == (undefined4 *)0x0) {
    return 0;
  }
  uVar4 = 0;
  if (uVar1 != 0) {
    do {
      puVar6 = (undefined4 *)(uVar4 * 8 + *(int *)((int)this + 4));
      uVar5 = uVar4 + 1;
      puVar3[uVar4 * 2] = *puVar6;
      puVar3[uVar4 * 2 + 1] = puVar6[1];
      uVar4 = uVar5;
    } while (uVar5 < uVar1);
  }
  if (uVar1 < *(uint *)((int)this + 8)) {
    uVar4 = uVar1;
    puVar6 = puVar3 + uVar1 * 2 + 2;
    do {
      iVar2 = *(int *)((int)this + 4);
      uVar4 = uVar4 + 1;
      *puVar6 = *(undefined4 *)(iVar2 + -8 + uVar4 * 8);
      puVar6[1] = *(undefined4 *)(iVar2 + -4 + uVar4 * 8);
      puVar6 = puVar6 + 2;
    } while (uVar4 < *(uint *)((int)this + 8));
  }
  puVar3[uVar1 * 2] = *param_1;
  puVar3[uVar1 * 2 + 1] = param_1[1];
  iVar2 = *(int *)((int)this + 4);
  if (iVar2 != 0) {
    if (iVar2 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar2);
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(undefined4 **)((int)this + 4) = puVar3;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
  return 1;
}


/* 004322a0 size=271 */

void __thiscall FUN_004322a0(void *this,uint param_1)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if ((uint)(*(int *)((int)this + 0x10) * 2) <= *(uint *)((int)this + 0xc)) {
    iVar1 = *(int *)((int)this + 0x10) + -1 + *(int *)((int)this + 8);
    puVar2 = FUN_00433a80(&DAT_004ecc58,0,iVar1);
    if ((puVar2 != (undefined4 *)0x0) || (iVar1 == 0)) {
      uVar3 = 0;
      if (param_1 != 0) {
        do {
          iVar1 = *(int *)((int)this + 4);
          uVar3 = uVar3 + 1;
          puVar2[uVar3 * 2 + -2] = *(undefined4 *)(iVar1 + -8 + uVar3 * 8);
          puVar2[uVar3 * 2 + -1] = *(undefined4 *)(iVar1 + -4 + uVar3 * 8);
        } while (uVar3 < param_1);
      }
      if (param_1 < *(int *)((int)this + 8) - 1U) {
        puVar4 = puVar2 + param_1 * 2;
        do {
          puVar5 = (undefined4 *)((int)puVar4 + *(int *)((int)this + 4) + (8 - (int)puVar2));
          param_1 = param_1 + 1;
          *puVar4 = *puVar5;
          puVar4[1] = puVar5[1];
          puVar4 = puVar4 + 2;
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
      *(undefined4 **)((int)this + 4) = puVar2;
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
      *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
      return;
    }
  }
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if (param_1 < *(int *)((int)this + 8) - 1U) {
    do {
      iVar1 = *(int *)((int)this + 4);
      param_1 = param_1 + 1;
      *(undefined4 *)(iVar1 + -8 + param_1 * 8) = *(undefined4 *)(iVar1 + param_1 * 8);
      *(undefined4 *)(iVar1 + -4 + param_1 * 8) = *(undefined4 *)(iVar1 + 4 + param_1 * 8);
    } while (param_1 < *(int *)((int)this + 8) - 1U);
  }
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
  return;
}


/* 00432f20 size=170 */

undefined4 __thiscall FUN_00432f20(void *this,int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
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
      puVar1 = FUN_00433a80(&DAT_004ecc58,0,*(int *)((int)this + 0x10) + param_1);
      *(undefined4 **)((int)this + 4) = puVar1;
      if (puVar1 == (undefined4 *)0x0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 00432fd0 size=161 */

undefined4 __thiscall FUN_00432fd0(void *this,int param_1,int *param_2)

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
      puVar2 = (undefined4 *)(**(code **)(*param_2 + 4))(iVar3 * 8);
      puVar1 = puVar2;
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        for (; iVar3 != 0; iVar3 = iVar3 + -1) {
          if (puVar1 != (undefined4 *)0x0) {
            *puVar1 = 0x3f800000;
            puVar1[1] = 0;
          }
          puVar1 = puVar1 + 2;
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


/* 00433080 size=285 */

undefined4 __thiscall FUN_00433080(void *this,uint param_1,int *param_2,int *param_3)

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
  if (param_1 != uVar3) {
    iVar4 = param_1 + *(int *)((int)this + 0x10);
    puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(iVar4 * 8);
    puVar5 = puVar1;
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      if (puVar5 != (undefined4 *)0x0) {
        *puVar5 = 0x3f800000;
        puVar5[1] = 0;
      }
      puVar5 = puVar5 + 2;
    }
    uVar3 = *(uint *)((int)this + 8);
    if (param_1 < *(uint *)((int)this + 8)) {
      uVar3 = param_1;
    }
    if (param_1 == 0) {
      uVar2 = 0;
      unaff_retaddr = 0;
      if (uVar3 != 0) {
        do {
          iVar4 = *(int *)((int)this + 4);
          uVar2 = uVar2 + 1;
          puVar1[uVar2 * 2 + -2] = *(undefined4 *)(iVar4 + -8 + uVar2 * 8);
          puVar1[uVar2 * 2 + -1] = *(undefined4 *)(iVar4 + -4 + uVar2 * 8);
        } while (uVar2 < uVar3);
      }
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
    iVar4 = *(int *)((int)this + 4);
    if (iVar4 != 0) {
      if (iVar4 != 0) {
        (**(code **)(*param_2 + 8))(iVar4);
      }
      *(undefined4 *)((int)this + 4) = 0;
    }
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 **)((int)this + 4) = puVar1;
    *(undefined4 *)((int)this + 8) = unaff_retaddr;
    *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  }
  return 1;
}


/* 004331a0 size=259 */

undefined4 __thiscall FUN_004331a0(void *this,int param_1,int *param_2)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  void *this_00;
  undefined4 *this_01;
  
  iVar3 = param_1;
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    pvVar1 = *(void **)((int)this + 4);
    if (pvVar1 != (void *)0x0) {
      param_1 = *(int *)((int)this + 0xc) + *(int *)((int)this + 8);
      if (pvVar1 == (void *)0x0) {
        *(undefined4 *)((int)this + 4) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
      }
      else {
        if (param_1 != 0) {
          this_00 = pvVar1;
          do {
            dsys_interface_433c20(this_00,0);
            this_00 = (void *)((int)this_00 + 0x1c);
            param_1 = param_1 + -1;
          } while (param_1 != 0);
        }
        (**(code **)(*param_2 + 8))(pvVar1);
        *(undefined4 *)((int)this + 4) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
      }
    }
    *(int *)((int)this + 8) = iVar3;
    if (iVar3 != 0) {
      iVar3 = iVar3 + *(int *)((int)this + 0x10);
      iVar2 = (**(code **)(*param_2 + 4))(iVar3 * 0x1c);
      if ((iVar2 != 0) && (iVar3 != 0)) {
        this_01 = (undefined4 *)(iVar2 + 8);
        do {
          if (this_01 != (undefined4 *)0x8) {
            this_01[-2] = 0;
            this_01[-1] = 0;
            FUN_004332b0(this_01);
            FUN_00432f20(this_01,0,0x400);
          }
          this_01 = this_01 + 7;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      *(int *)((int)this + 4) = iVar2;
      if (iVar2 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 004332b0 size=111 */

undefined4 * __fastcall FUN_004332b0(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cc2e8;
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


/* 00433320 size=399 */

undefined4 __thiscall FUN_00433320(void *this,uint param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *unaff_EBP;
  int iVar6;
  undefined4 *puVar7;
  uint unaff_retaddr;
  
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
  iVar6 = param_1 + *(int *)((int)this + 0x10);
  puVar1 = (undefined4 *)(**(code **)(*param_3 + 4))(iVar6 * 0x1c);
  puVar7 = puVar1;
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  for (; iVar6 != 0; iVar6 = iVar6 + -1) {
    if (puVar7 != (undefined4 *)0x0) {
      FUN_004334b0(puVar7,0,0);
    }
    puVar7 = puVar7 + 7;
  }
  uVar5 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar5 = param_1;
  }
  if (param_1 == 0) {
    if (uVar5 != 0) {
      puVar7 = puVar1 + 2;
      do {
        puVar2 = (undefined4 *)((int)puVar7 + *(int *)((int)this + 4) + (-8 - (int)puVar1));
        puVar7[-2] = *puVar2;
        puVar7[-1] = puVar2[1];
        FUN_00433980(puVar7,(int)(puVar2 + 2),&DAT_004ecc58);
        puVar7 = puVar7 + 7;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
      param_1 = unaff_retaddr;
    }
  }
  else {
    puVar7 = *(undefined4 **)((int)this + 4);
    puVar2 = puVar1;
    for (uVar5 = uVar5 * 0x1c >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar2 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar2 = puVar2 + 1;
    }
    for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
      *(undefined1 *)puVar2 = *(undefined1 *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + 1);
      puVar2 = (undefined4 *)((int)puVar2 + 1);
    }
  }
  iVar6 = *(int *)((int)this + 4);
  if (iVar6 != 0) {
    iVar3 = *(int *)((int)this + 0xc) + *(int *)((int)this + 8);
    if (iVar6 != 0) {
      if (iVar3 != 0) {
        puVar7 = (undefined4 *)(iVar6 + 8);
        do {
          *puVar7 = &PTR_LAB_004cc2e8;
          FUN_00432fd0(puVar7,0,&DAT_004ecc58);
          puVar7 = puVar7 + 7;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      (**(code **)(*param_2 + 8))(iVar6);
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


/* 004334b0 size=171 */

undefined4 * __thiscall FUN_004334b0(void *this,undefined4 param_1,undefined4 param_2)

{
  undefined4 *this_00;
  
  this_00 = (undefined4 *)((int)this + 8);
  *(undefined4 *)this = param_1;
  *(undefined4 *)((int)this + 4) = param_2;
  *this_00 = &PTR_LAB_004cc2e8;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  FUN_00432fd0(this_00,0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  if (*(int *)((int)this + 0xc) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0xc));
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 *)((int)this + 0x14) = 0;
  }
  *(undefined4 *)((int)this + 0x10) = 0;
  FUN_00432fd0(this_00,0,&DAT_004ecc58);
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x18) = 0x400;
  *(undefined4 *)((int)this + 0x14) = 0;
  if (*(int *)((int)this + 0xc) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0xc));
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 *)((int)this + 0x14) = 0;
  }
  *(undefined4 *)((int)this + 0x10) = 0;
  return this;
}


/* 00433560 size=38 */

void __thiscall FUN_00433560(void *this,int *param_1)

{
  if (*(int *)((int)this + 4) != 0) {
    (**(code **)(*param_1 + 8))(*(int *)((int)this + 4));
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  return;
}


/* 00433590 size=268 */

void __thiscall FUN_00433590(void *this,uint param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if ((uint)(*(int *)((int)this + 0x10) * 2) <= *(uint *)((int)this + 0xc)) {
    iVar1 = *(int *)((int)this + 0x10) + -1 + *(int *)((int)this + 8);
    iVar2 = (**(code **)(*param_2 + 4))(iVar1 * 4);
    if ((iVar2 != 0) || (iVar2 = 0, iVar1 == 0)) {
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
          (**(code **)(*param_2 + 8))(iVar1);
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


/* 004336a0 size=614 */

void __thiscall FUN_004336a0(void *this,uint param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int unaff_EBX;
  uint uVar6;
  int iVar7;
  void *pvVar8;
  void *this_00;
  
  if ((uint)(*(int *)((int)this + 0x10) * 2) <= *(uint *)((int)this + 0xc)) {
    iVar5 = *(int *)((int)this + 0x10) + -1 + *(int *)((int)this + 8);
    iVar2 = FUN_00433b30(param_2,0,iVar5);
    if ((iVar2 != 0) || (iVar5 == 0)) {
      if (param_1 != 0) {
        pvVar8 = (void *)(iVar2 + 8);
        uVar6 = param_1;
        do {
          puVar3 = (undefined4 *)((int)pvVar8 + *(int *)((int)this + 4) + (-8 - iVar2));
          *(undefined4 *)((int)pvVar8 + -8) = *puVar3;
          *(undefined4 *)((int)pvVar8 + -4) = puVar3[1];
          FUN_00433980(pvVar8,(int)(puVar3 + 2),&DAT_004ecc58);
          pvVar8 = (void *)((int)pvVar8 + 0x1c);
          uVar6 = uVar6 - 1;
        } while (uVar6 != 0);
      }
      if (param_1 < *(int *)((int)this + 8) - 1U) {
        pvVar8 = (void *)(iVar2 + 8 + param_1 * 0x1c);
        do {
          puVar3 = (undefined4 *)((int)pvVar8 + *(int *)((int)this + 4) + (0x14 - iVar2));
          *(undefined4 *)((int)pvVar8 + -8) = *puVar3;
          *(undefined4 *)((int)pvVar8 + -4) = puVar3[1];
          FUN_00433980(pvVar8,(int)(puVar3 + 2),&DAT_004ecc58);
          param_1 = param_1 + 1;
          pvVar8 = (void *)((int)pvVar8 + 0x1c);
        } while (param_1 < *(int *)((int)this + 8) - 1U);
      }
      pvVar8 = *(void **)((int)this + 4);
      if (pvVar8 != (void *)0x0) {
        iVar5 = *(int *)((int)this + 0xc) + *(int *)((int)this + 8);
        if (pvVar8 != (void *)0x0) {
          if (iVar5 != 0) {
            this_00 = pvVar8;
            do {
              dsys_interface_433c20(this_00,0);
              this_00 = (void *)((int)this_00 + 0x1c);
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
          }
          (**(code **)(*param_2 + 8))(pvVar8);
          iVar2 = unaff_EBX;
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
    iVar5 = param_1 * 0x1c;
    do {
      iVar1 = *(int *)((int)this + 4);
      iVar2 = iVar5 + 8 + iVar1;
      *(undefined4 *)(iVar5 + iVar1) = *(undefined4 *)(iVar5 + 0x1c + iVar1);
      *(undefined4 *)(iVar5 + 4 + iVar1) = *(undefined4 *)(iVar5 + 0x20 + iVar1);
      iVar1 = iVar5 + 0x24 + iVar1;
      if (*(int *)(iVar2 + 4) != 0) {
        FUN_00456e60(&DAT_004ecc58,*(int *)(iVar2 + 4));
        *(undefined4 *)(iVar2 + 4) = 0;
        *(undefined4 *)(iVar2 + 0xc) = 0;
      }
      *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(iVar1 + 8);
      *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)(iVar1 + 0xc);
      *(undefined4 *)(iVar2 + 0x10) = *(undefined4 *)(iVar1 + 0x10);
      iVar7 = *(int *)(iVar2 + 0xc) + *(int *)(iVar2 + 8);
      if (iVar7 == 0) {
        *(undefined4 *)(iVar2 + 8) = 0;
        *(undefined4 *)(iVar2 + 0xc) = 0;
        *(undefined4 *)(iVar2 + 4) = 0;
      }
      else {
        puVar4 = (undefined4 *)(**(code **)(DAT_004ecc58 + 4))(iVar7 * 8);
        puVar3 = puVar4;
        if (puVar4 == (undefined4 *)0x0) {
          puVar4 = (undefined4 *)0x0;
        }
        else {
          for (; iVar7 != 0; iVar7 = iVar7 + -1) {
            if (puVar3 != (undefined4 *)0x0) {
              *puVar3 = 0x3f800000;
              puVar3[1] = 0;
            }
            puVar3 = puVar3 + 2;
          }
        }
        *(undefined4 **)(iVar2 + 4) = puVar4;
        if (puVar4 == (undefined4 *)0x0) {
          *(undefined4 *)(iVar2 + 8) = 0;
          *(undefined4 *)(iVar2 + 0xc) = 0;
        }
        else {
          uVar6 = 0;
          if (*(int *)(iVar2 + 8) != 0) {
            do {
              puVar4 = (undefined4 *)(uVar6 * 8 + *(int *)(iVar1 + 4));
              puVar3 = (undefined4 *)(uVar6 * 8 + *(int *)(iVar2 + 4));
              uVar6 = uVar6 + 1;
              *puVar3 = *puVar4;
              puVar3[1] = puVar4[1];
            } while (uVar6 < *(uint *)(iVar2 + 8));
          }
        }
      }
      param_1 = param_1 + 1;
      iVar5 = iVar5 + 0x1c;
    } while (param_1 < *(int *)((int)this + 8) - 1U);
  }
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
  return;
}


/* 00433910 size=109 */

void __thiscall FUN_00433910(void *this,int *param_1,int param_2)

{
  int iVar1;
  void *unaff_EBP;
  int *piVar2;
  
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    if (param_2 != 0) {
      piVar2 = (int *)(iVar1 + 0xc);
      do {
        piVar2[-1] = (int)&PTR_LAB_004cc2e8;
        if (*piVar2 != 0) {
          FUN_00456e60(&DAT_004ecc58,*piVar2);
          *piVar2 = 0;
          piVar2[2] = 0;
        }
        piVar2[1] = 0;
        piVar2 = piVar2 + 7;
        param_2 = param_2 + -1;
      } while (param_2 != 0);
    }
    (**(code **)(*param_1 + 8))(iVar1);
    *(undefined4 *)((int)unaff_EBP + 4) = 0;
    this = unaff_EBP;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  return;
}


/* 00433980 size=241 */

undefined4 __thiscall FUN_00433980(void *this,int param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
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
    *(undefined4 *)((int)this + 0xc) = 0;
  }
  *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)((int)this + 0x10) = *(undefined4 *)(param_1 + 0x10);
  iVar4 = *(int *)((int)this + 8) + *(int *)((int)this + 0xc);
  if (iVar4 == 0) {
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    puVar2 = (undefined4 *)(**(code **)(*param_2 + 4))(iVar4 * 8);
    puVar5 = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = (undefined4 *)0x0;
    }
    else {
      for (; iVar4 != 0; iVar4 = iVar4 + -1) {
        if (puVar5 != (undefined4 *)0x0) {
          *puVar5 = 0x3f800000;
          puVar5[1] = 0;
        }
        puVar5 = puVar5 + 2;
      }
    }
    *(undefined4 **)((int)this + 4) = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      *(undefined4 *)((int)this + 8) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
      return 0;
    }
    uVar3 = 0;
    if (*(int *)((int)this + 8) != 0) {
      do {
        iVar4 = uVar3 * 8;
        iVar1 = *(int *)(unaff_retaddr + 4);
        puVar5 = (undefined4 *)(iVar4 + *(int *)((int)this + 4));
        uVar3 = uVar3 + 1;
        *puVar5 = *(undefined4 *)(iVar1 + iVar4);
        puVar5[1] = *(undefined4 *)(iVar1 + 4 + iVar4);
      } while (uVar3 < *(uint *)((int)this + 8));
      return 1;
    }
  }
  return 1;
}


/* 00433a80 size=59 */

undefined4 * __cdecl FUN_00433a80(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(**(code **)(*param_1 + 4))(param_3 * 8);
  puVar1 = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = 0x3f800000;
      puVar1[1] = 0;
    }
    puVar1 = puVar1 + 2;
  }
  return puVar2;
}


/* 00433ac0 size=102 */

void __cdecl FUN_00433ac0(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  if (param_2 != 0) {
    if (param_3 != 0) {
      piVar2 = (int *)(param_2 + 0xc);
      do {
        iVar1 = *piVar2;
        piVar2[-1] = (int)&PTR_LAB_004cc2e8;
        if (iVar1 != 0) {
          if (iVar1 != 0) {
            (**(code **)(DAT_004ecc58 + 8))(iVar1);
          }
          *piVar2 = 0;
          piVar2[2] = 0;
        }
        piVar2[1] = 0;
        piVar2 = piVar2 + 7;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
    }
    (**(code **)(*param_1 + 8))(param_2);
  }
  return;
}


/* 00433b30 size=238 */

int __cdecl FUN_00433b30(int *param_1,undefined4 param_2,int param_3)

{
  int *this;
  int iVar1;
  int *piVar2;
  
  iVar1 = (**(code **)(*param_1 + 4))(param_3 * 0x1c);
  if (iVar1 == 0) {
    return 0;
  }
  if (param_3 != 0) {
    piVar2 = (int *)(iVar1 + 0xc);
    do {
      if (piVar2 != (int *)&DAT_0000000c) {
        this = piVar2 + -1;
        piVar2[-3] = 0;
        piVar2[-2] = 0;
        *this = (int)&PTR_LAB_004cc2e8;
        *piVar2 = 0;
        piVar2[1] = 0;
        piVar2[2] = 0;
        piVar2[3] = 0;
        FUN_00432fd0(this,0,&DAT_004ecc58);
        *piVar2 = 0;
        piVar2[1] = 0;
        piVar2[3] = 0;
        piVar2[2] = 0;
        if (*piVar2 != 0) {
          FUN_00456e60(&DAT_004ecc58,*piVar2);
          *piVar2 = 0;
          piVar2[2] = 0;
        }
        piVar2[1] = 0;
        FUN_00432fd0(this,0,&DAT_004ecc58);
        *piVar2 = 0;
        piVar2[1] = 0;
        piVar2[3] = 0x400;
        piVar2[2] = 0;
        if (*piVar2 != 0) {
          FUN_00456e60(&DAT_004ecc58,*piVar2);
          *piVar2 = 0;
          piVar2[2] = 0;
        }
        piVar2[1] = 0;
      }
      piVar2 = piVar2 + 7;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return iVar1;
}


/* 00433eb0 size=20 */

void __fastcall FUN_00433eb0(int param_1)

{
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  return;
}


/* 00433ee0 size=21 */

undefined4 __fastcall FUN_00433ee0(int param_1)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 0x18) == 1) || (*(int *)(param_1 + 0x18) == 2)) {
    return 0;
  }
  uVar1 = FUN_004365f0();
  return uVar1;
}


/* 00433f00 size=39 */

void __fastcall FUN_00433f00(int param_1)

{
  int *piVar1;
  
  FUN_004bbc61(0x7b);
  if ((*(int *)(param_1 + 0xc) == 0) ||
     (piVar1 = *(int **)(*(int *)(param_1 + 0xc) + 0x620), piVar1 == (int *)0x0)) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00433f23. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*piVar1 + 0x5c))();
  return;
}


/* 00433f30 size=37 */

void __thiscall FUN_00433f30(void *this,undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  
  if ((*(int *)((int)this + 0xc) != 0) &&
     (piVar1 = *(int **)(*(int *)((int)this + 0xc) + 0x620), piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x60))(param_1,param_2);
  }
  return;
}


/* 00433f60 size=214 */

undefined4 __thiscall FUN_00433f60(void *this,undefined4 param_1,LPCSTR param_2)

{
  int *piVar1;
  undefined4 unaff_EBX;
  int iVar2;
  undefined1 uStack00000000;
  
  FUN_004341b0(this);
  piVar1 = FUN_0049ade0(param_2,&DAT_004d7acc);
  *(int **)((int)this + 0x10) = piVar1;
  if (piVar1 == (int *)0x0) {
    return 1;
  }
  param_2 = (LPCSTR)0xf0f0aabc;
  (**(code **)(*piVar1 + 0x24))(&param_2,4);
  iVar2 = 0x10;
  do {
    (**(code **)(**(int **)((int)this + 0x10) + 0x24))(&uStack00000000,4);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  (**(code **)(**(int **)((int)this + 0x10) + 0x28))(unaff_EBX);
  *(undefined4 *)(*(int *)((int)this + 0xc) + 0x1364) =
       *(undefined4 *)(*(int *)((int)this + 0xc) + 0x136c);
  (**(code **)(**(int **)((int)this + 0x10) + 0x24))(*(int *)((int)this + 0xc) + 0x136c,4);
  (**(code **)(**(int **)((int)this + 0x10) + 0x24))(*(int *)((int)this + 0xc) + 0x1364,4);
  *(undefined4 *)(*(int *)((int)this + 0xc) + 0x1368) = 0;
  *(undefined4 *)(*(int *)((int)this + 0xc) + 0x1604) = 0;
  *(undefined4 *)((int)this + 0x18) = 1;
  FUN_00433f30(this,*(undefined4 *)((int)this + 0x10),0);
  FUN_00433f00((int)this);
  return 0;
}


