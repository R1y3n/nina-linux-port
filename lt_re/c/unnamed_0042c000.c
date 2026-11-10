/* lithtech.exe decompilation - unnamed_0042c000 */
#include "ghidra_types.h"

/* 0042c050 size=30 */

void __fastcall FUN_0042c050(int param_1)

{
  if (*(int **)(param_1 + 0x184) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x184) + 4))();
    *(undefined4 *)(param_1 + 0x184) = 0;
  }
  return;
}


/* 0042c070 size=275 */

undefined4 __fastcall FUN_0042c070(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  iVar5 = 0;
  iVar7 = *(int *)(param_1 + 400);
  if (iVar7 != 0) {
    piVar3 = *(int **)(param_1 + 0x18c);
    do {
      iVar2 = *(int *)(*(int *)(*piVar3 + 4) + 0xa4);
      if (iVar2 != 0) {
        piVar1 = *(int **)(*(int *)(*piVar3 + 4) + 0xa0);
        do {
          if ((*(byte *)(*(int *)(*piVar1 + 0x2c) + 0x30) & 0x10) != 0) {
            iVar5 = iVar5 + 1;
          }
          piVar1 = piVar1 + 1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      piVar3 = piVar3 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  if ((iVar5 != *(int *)(param_1 + 0x1a4)) || (iVar5 == 0)) {
    if (*(int *)(param_1 + 0x1a0) != 0) {
      FUN_00433560((void *)(param_1 + 0x19c),&DAT_004ecc58);
    }
    *(int *)(param_1 + 0x1a4) = iVar5;
    if (iVar5 != 0) {
      iVar7 = FUN_00456f10(&DAT_004ecc58,0,*(int *)(param_1 + 0x1ac) + iVar5);
      *(int *)(param_1 + 0x1a0) = iVar7;
      if (iVar7 == 0) {
        *(undefined4 *)(param_1 + 0x1a4) = 0;
        *(undefined4 *)(param_1 + 0x1a8) = 0;
        return 0;
      }
      *(undefined4 *)(param_1 + 0x1a8) = *(undefined4 *)(param_1 + 0x1ac);
    }
  }
  uVar8 = 0;
  uVar6 = 0;
  if (*(int *)(param_1 + 400) != 0) {
    do {
      uVar4 = 0;
      iVar7 = *(int *)(*(int *)(*(int *)(param_1 + 0x18c) + uVar6 * 4) + 4);
      if (*(int *)(iVar7 + 0xa4) != 0) {
        do {
          iVar5 = *(int *)(*(int *)(iVar7 + 0xa0) + uVar4 * 4);
          if (((*(byte *)(*(int *)(iVar5 + 0x2c) + 0x30) & 0x10) != 0) &&
             (uVar8 < *(uint *)(param_1 + 0x1a4))) {
            uVar8 = uVar8 + 1;
            *(int *)(*(int *)(param_1 + 0x1a0) + -4 + uVar8 * 4) = iVar5;
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(uint *)(iVar7 + 0xa4));
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(param_1 + 400));
  }
  return 1;
}


/* 0042c190 size=43 */

void __thiscall FUN_0042c190(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4);
  if (iVar1 != param_1) {
    do {
      FUN_004a3df0((void *)((int)this + 0x6c),*(int **)(iVar1 + 8));
      iVar1 = *(int *)(iVar1 + 4);
    } while (iVar1 != param_1);
  }
  return;
}


/* 0042c1c0 size=439 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0042c1c0: lifted from original x86 -> lt_lifted.c */


/* 0042c880 size=186 */

void __fastcall FUN_0042c880(int param_1)

{
  if (*(int *)(param_1 + 8) != 0) {
    FUN_00433560((void *)(param_1 + 4),&DAT_004ecc58);
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  if (*(int *)(param_1 + 0x1c) != 0) {
    FUN_00433560((void *)(param_1 + 0x18),&DAT_004ecc58);
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  if (*(int *)(param_1 + 0x30) != 0) {
    FUN_00433560((void *)(param_1 + 0x2c),&DAT_004ecc58);
  }
  *(undefined4 *)(param_1 + 0x34) = 0;
  if (*(int *)(param_1 + 0x44) != 0) {
    FUN_00433560((void *)(param_1 + 0x40),&DAT_004ecc58);
  }
  *(undefined4 *)(param_1 + 0x48) = 0;
  if (*(int *)(param_1 + 0x58) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)(param_1 + 0x58));
    *(undefined4 *)(param_1 + 0x58) = 0;
    *(undefined4 *)(param_1 + 0x60) = 0;
  }
  *(undefined4 *)(param_1 + 0x5c) = 0;
  return;
}


/* 0042c940 size=79 */

byte * __thiscall FUN_0042c940(void *this,byte *param_1,uint *param_2)

{
  uint uVar1;
  void *this_00;
  void *extraout_ECX;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  
  uVar3 = 0;
  if (*(int *)((int)this + 0xc) != 0) {
    iVar2 = 0;
    this_00 = this;
    do {
      pbVar4 = (byte *)(*(int *)((int)this + 8) + iVar2);
      uVar1 = FUN_004c4c00(this_00,pbVar4,param_1);
      if (uVar1 == 0) {
        if (param_2 != (uint *)0x0) {
          *param_2 = uVar3;
        }
        return pbVar4;
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 0x60;
      this_00 = extraout_ECX;
    } while (uVar3 < *(uint *)((int)this + 0xc));
  }
  return (byte *)0x0;
}


/* 0042c990 size=70 */

void __thiscall FUN_0042c990(void *this,int param_1)

{
  byte *pbVar1;
  ushort *puVar2;
  ushort *puVar3;
  
  puVar3 = *(ushort **)(param_1 + 0x2c);
  puVar2 = puVar3 + (uint)*(ushort *)(param_1 + 0x30) * 2;
  for (; puVar3 != puVar2; puVar3 = puVar3 + 2) {
    pbVar1 = (byte *)(*(int *)(*(int *)(*(int *)(*(int *)(*(int *)((int)this + 0x18c) +
                                                         (uint)*puVar3 * 4) + 4) + 0xa0) +
                              (uint)puVar3[1] * 4) + 0x15);
    *pbVar1 = *pbVar1 | 0xc0;
  }
  return;
}


/* 0042c9e0 size=179 */

undefined4 __fastcall FUN_0042c9e0(int *param_1)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iStack_8;
  uint uStack_4;
  
  iVar3 = (**(code **)(*param_1 + 4))();
  if (iVar3 == 0) {
    return 0;
  }
  uStack_4 = 0;
  if (*(int *)(iVar3 + 0x8c) != 0) {
    iStack_8 = 0;
    do {
      iVar4 = *(int *)(iVar3 + 0x88) + iStack_8;
      uVar5 = 0;
      if (*(int *)(iVar4 + 0x24) != 0) {
        do {
          puVar1 = (ushort *)(*(int *)(iVar4 + 0x20) + uVar5 * 4);
          if ((uint)param_1[100] <= (uint)*puVar1) {
            return 0;
          }
          iVar2 = *(int *)(*(int *)(param_1[99] + (uint)*puVar1 * 4) + 4);
          if (*(uint *)(iVar2 + 0xa4) <= (uint)puVar1[1]) {
            return 0;
          }
          uVar5 = uVar5 + 1;
          *(undefined4 *)puVar1 = *(undefined4 *)(*(int *)(iVar2 + 0xa0) + (uint)puVar1[1] * 4);
        } while (uVar5 < *(uint *)(iVar4 + 0x24));
      }
      uStack_4 = uStack_4 + 1;
      iStack_8 = iStack_8 + 0x30;
    } while (uStack_4 < *(uint *)(iVar3 + 0x8c));
  }
  return 1;
}


/* 0042cb00 size=73 */

void __fastcall FUN_0042cb00(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (*(int *)(param_1 + 400) != 0) {
    do {
      iVar1 = *(int *)(*(int *)(param_1 + 0x18c) + uVar3 * 4);
      iVar2 = *(int *)(iVar1 + 4);
      if (iVar2 != 0) {
        FUN_0042cb50(iVar2);
      }
      iVar1 = *(int *)(iVar1 + 8);
      if (iVar1 != 0) {
        FUN_0042cb50(iVar1);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_1 + 400));
  }
  return;
}


/* 0042cb50 size=749 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0042cb50: lifted from original x86 -> lt_lifted.c */


/* 0042ce40 size=51 */

void __fastcall FUN_0042ce40(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    do {
      FUN_00430fe0(*(undefined **)(*(int *)(param_1 + 0x2c) + uVar1 * 8));
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x28));
  }
  FUN_00430fe0(*(undefined **)(param_1 + 0x2c));
  return;
}


/* 0042ce80 size=250 */

undefined4 __thiscall FUN_0042ce80(void *this,int *param_1)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  void *pvVar5;
  uint uVar6;
  
  FUN_0042ce40((int)this);
  (**(code **)(*param_1 + 8))((int *)((int)this + 0x18),0xc);
  iVar2 = *(int *)((int)this + 0x18);
  iVar3 = *(int *)((int)this + 0x20) * iVar2 * *(int *)((int)this + 0x1c);
  *(int *)((int)this + 0x24) = iVar2 * *(int *)((int)this + 0x1c);
  *(int *)((int)this + 0x28) = iVar3;
  if (iVar3 != 0) {
    puVar4 = FUN_00430fb0(iVar3 * 8);
    *(undefined4 **)((int)this + 0x2c) = puVar4;
    if (puVar4 == (undefined4 *)0x0) {
LAB_0042cecc:
      FUN_0042ce40((int)this);
      return 0;
    }
  }
  (**(code **)(*param_1 + 8))(this,0xc);
  (**(code **)(*param_1 + 8))((int)this + 0xc,0xc);
  uVar6 = 0;
  if (*(int *)((int)this + 0x28) != 0) {
    do {
      puVar4 = (undefined4 *)(*(int *)((int)this + 0x2c) + uVar6 * 8);
      puVar1 = (ushort *)(puVar4 + 1);
      (**(code **)(*param_1 + 8))(puVar1,2);
      (**(code **)(*param_1 + 8))((int)puVar4 + 6,2);
      if (*puVar1 != 0) {
        pvVar5 = FUN_00430f00((uint)*puVar1 * 6);
        *puVar4 = pvVar5;
        if (pvVar5 == (void *)0x0) goto LAB_0042cecc;
      }
      (**(code **)(*param_1 + 8))(*puVar4,(uint)*puVar1 * 6);
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)((int)this + 0x28));
  }
  return 1;
}


/* 0042cf80 size=173 */

ulonglong __fastcall FUN_0042cf80(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  ulonglong uVar6;
  
  lVar5 = __ftol();
  iVar1 = (int)lVar5;
  lVar5 = __ftol();
  iVar2 = (int)lVar5;
  uVar6 = __ftol();
  iVar4 = (int)uVar6;
  if (iVar1 < 0) {
    iVar1 = 0;
  }
  else {
    iVar3 = *(int *)(param_1 + 0x18) + -1;
    if (iVar3 < iVar1) {
      iVar1 = iVar3;
    }
  }
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  else {
    iVar3 = *(int *)(param_1 + 0x1c) + -1;
    if (iVar3 < iVar2) {
      iVar2 = iVar3;
    }
  }
  if (iVar4 < 0) {
    iVar4 = 0;
  }
  else {
    iVar3 = *(int *)(param_1 + 0x20) + -1;
    if (iVar3 < iVar4) {
      iVar4 = iVar3;
    }
  }
  if (((iVar1 < 0) || (iVar2 < 0)) || (iVar4 < 0)) {
    return uVar6 & 0xffffffff00000000;
  }
  iVar4 = *(int *)(param_1 + 0x18) * iVar2 + iVar1 + *(int *)(param_1 + 0x24) * iVar4;
  return CONCAT44(iVar4,*(int *)(param_1 + 0x2c) + iVar4 * 8);
}


/* 0042d030 size=225 */

undefined4 * __fastcall FUN_0042d030(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  FUN_0042d640(param_1);
  puVar1 = param_1 + 0x14;
  *puVar1 = &PTR_LAB_004cbcc4;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x18] = 0;
  param_1[0x17] = 0;
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  puVar1 = param_1 + 0x1a;
  *puVar1 = &PTR_LAB_004cc138;
  param_1[0x1b] = 0;
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  FUN_004302e0(puVar1,0,&DAT_004ecc58);
  param_1[0x1b] = 0;
  param_1[0x1c] = 0;
  param_1[0x1e] = 0;
  param_1[0x1d] = 0;
  FUN_004302e0(puVar1,0,&DAT_004ecc58);
  param_1[0x20] = 0;
  param_1[0x21] = 0;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  param_1[0x24] = 0;
  param_1[0x25] = 0;
  param_1[0x28] = 0;
  param_1[0x27] = 0;
  param_1[0x26] = 0;
  param_1[0x29] = 0;
  param_1[0x2a] = 0;
  param_1[0x2b] = 0;
  *param_1 = &DAT_004cc10c;
  param_1[0x19] = PTR_DAT_004d7c48;
  param_1[0x1f] = 0;
  return param_1;
}


/* 0042d120 size=121 */

void __fastcall FUN_0042d120(undefined4 *param_1)

{
  int iVar1;
  
  *param_1 = &DAT_004cc10c;
  FUN_0042d1a0((int)param_1);
  param_1[0x1a] = &PTR_LAB_004cc138;
  if (param_1[0x1b] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[0x1b]);
    param_1[0x1b] = 0;
    param_1[0x1d] = 0;
  }
  param_1[0x1c] = 0;
  iVar1 = param_1[0x15];
  param_1[0x14] = &PTR_LAB_004cbcc4;
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    param_1[0x15] = 0;
    param_1[0x17] = 0;
  }
  param_1[0x16] = 0;
  return;
}


/* 0042d1a0 size=120 */

void __fastcall FUN_0042d1a0(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x54) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)(param_1 + 0x54));
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(undefined4 *)(param_1 + 0x5c) = 0;
  }
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined **)(param_1 + 100) = PTR_DAT_004d7c48;
  iVar1 = *(int *)(param_1 + 0x6c);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x74) = 0;
  }
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  FUN_0042ce40(param_1 + 0x80);
  return;
}


/* 0042d220 size=670 */

undefined4 __thiscall FUN_0042d220(void *this,int param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  uint unaff_EBX;
  uint uVar4;
  uint unaff_EBP;
  undefined4 *puVar5;
  int unaff_EDI;
  uint uVar6;
  undefined4 uStack_c;
  undefined1 local_8 [4];
  int iStack_4;
  
  iVar3 = param_1;
  FUN_0042d1a0((int)this);
  *(int *)((int)this + 0x7c) = param_1;
  iVar1 = FUN_00428d70((char *)(param_1 + 4),param_3,(undefined1 *)((int)this + 4),0x41);
  if (iVar1 == 0) {
    FUN_00436670((byte *)s____Terrain__s_s_name_is_too_long_004d7c04,unaff_EDI);
    return 0;
  }
  (**(code **)(*param_2 + 8))(local_8,4);
  iVar1 = FUN_004302e0((void *)((int)this + 0x68),unaff_EBX,&DAT_004ecc58);
  if (iVar1 == 0) {
    return 0;
  }
  uVar6 = 0;
  if (unaff_EBX != 0) {
    param_1 = 0;
    iVar1 = param_1;
    do {
      param_1 = iVar1;
      puVar5 = (undefined4 *)(*(int *)((int)this + 0x6c) + param_1);
      *(undefined1 *)((int)puVar5 + 0x16) = 8;
      (**(code **)(*param_2 + 8))(local_8 + -0xc,4);
      if (*(uint *)(iVar3 + 0xa4) <= unaff_EBP) goto LAB_0042d418;
      uVar4 = 0;
      *puVar5 = *(undefined4 *)(*(int *)(iVar3 + 0xa0) + unaff_EBP * 4);
      do {
        puVar5 = puVar5 + 1;
        (**(code **)(*param_2 + 8))(local_8 + -0xc,4);
        puVar2 = FUN_0042a880(*(int *)((int)this + 0x6c),*(int *)((int)this + 0x70),unaff_EBP);
        *puVar5 = puVar2;
        if (puVar2 == (undefined *)0x0) goto LAB_0042d418;
        uVar4 = uVar4 + 1;
      } while (uVar4 < 2);
      uVar6 = uVar6 + 1;
      iVar1 = param_1 + 0x18;
      param_1 = iStack_4;
      iVar3 = iStack_4;
    } while (uVar6 < unaff_EBX);
  }
  (**(code **)(*param_2 + 8))(local_8 + -0xc,4);
  puVar2 = FUN_0042a880(*(int *)((int)this + 0x6c),*(int *)((int)this + 0x70),unaff_EDI);
  *(undefined **)((int)this + 100) = puVar2;
  if (puVar2 == (undefined *)0x0) {
    FUN_0042d1a0((int)this);
    return 0;
  }
  (**(code **)(*param_2 + 8))(local_8 + -0xc,4);
  iVar3 = FUN_00468190((void *)((int)this + 0x50),uStack_c,&DAT_004ecc58);
  if (iVar3 != 0) {
    uVar6 = 0;
    if (*(int *)((int)this + 0x58) != 0) {
      do {
        uVar6 = uVar6 + 1;
        *(undefined4 *)(*(int *)((int)this + 0x54) + -4 + uVar6 * 4) = 0;
      } while (uVar6 < *(uint *)((int)this + 0x58));
    }
    uVar6 = 0;
    if (uStack_c != 0) {
      do {
        (**(code **)(*param_2 + 8))(local_8 + -0xc,4);
        if (*(uint *)(param_1 + 0xa4) <= unaff_EBP) goto LAB_0042d418;
        uVar6 = uVar6 + 1;
        *(undefined4 *)(*(int *)((int)this + 0x54) + -4 + uVar6 * 4) =
             *(undefined4 *)(*(int *)(param_1 + 0xa0) + unaff_EBP * 4);
      } while (uVar6 < uStack_c);
    }
    iVar3 = FUN_0042ce80((void *)((int)this + 0x80),param_2);
    if (iVar3 != 0) {
      (**(code **)(*param_2 + 8))((int)this + 0x48,1);
      (**(code **)(*param_2 + 8))((int)this + 0x49,1);
      (**(code **)(*param_2 + 8))((int)this + 0x4a,1);
      (**(code **)(*param_2 + 8))((int)this + 0x4b,1);
      (**(code **)(*param_2 + 8))((int)this + 0x4c,4);
      (**(code **)(*param_2 + 8))((int)this + 0xb0,4);
      (**(code **)(*param_2 + 8))((int)this + 0xb4,4);
      (**(code **)(*param_2 + 8))((int)this + 0xb8,4);
      FUN_0042a940(*(int **)((int)this + 0x6c),*(int *)((int)this + 0x70),1);
      FUN_0042d4c0((int)this);
      return 1;
    }
  }
LAB_0042d418:
  FUN_0042d1a0((int)this);
  return 0;
}


/* 0042d4c0 size=34 */

void __fastcall FUN_0042d4c0(int param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_0042d4f0(*(int **)(param_1 + 0x54),*(int *)(param_1 + 0x58),
                                (float *)(param_1 + 0xb0));
  *(float *)(param_1 + 0xbc) = (float)fVar1;
  return;
}


/* 0042d4f0 size=157 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl FUN_0042d4f0(int *param_1,int param_2,float *param_3)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int *piVar4;
  uint uVar5;
  
  if (param_2 != 0) {
    fVar2 = _DAT_004cb524;
    do {
      uVar5 = (uint)*(ushort *)(*param_1 + 0x54);
      if (uVar5 != 0) {
        piVar4 = (int *)(*param_1 + 0x58);
        do {
          pfVar1 = (float *)*piVar4;
          fVar3 = SQRT((param_3[1] - pfVar1[1]) * (param_3[1] - pfVar1[1]) +
                       (*param_3 - *pfVar1) * (*param_3 - *pfVar1) +
                       (param_3[2] - pfVar1[2]) * (param_3[2] - pfVar1[2]));
          if (fVar2 < fVar3) {
            fVar2 = fVar3;
          }
          piVar4 = piVar4 + 6;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}


/* 0042d640 size=13 */

void __fastcall FUN_0042d640(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cc168;
  *(undefined1 *)(param_1 + 1) = 0;
  return;
}


/* 0042d650 size=241 */

undefined4 * __fastcall FUN_0042d650(undefined4 *param_1)

{
  undefined4 *this;
  
  FUN_0042d640(param_1);
  this = param_1 + 0x15;
  *this = &PTR_LAB_004cc1f4;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  FUN_00468190(this,0,&DAT_004ecc58);
  FUN_0043c3e0(this,0);
  FUN_00468190(this,0,&DAT_004ecc58);
  param_1[0x42] = 0;
  param_1[0x43] = 0;
  param_1[0x44] = 0;
  param_1[0x45] = 0;
  param_1[0x46] = 0;
  param_1[0x47] = 0;
  param_1[0x4a] = 0;
  param_1[0x49] = 0;
  param_1[0x48] = 0;
  param_1[0x4b] = 0;
  param_1[0x4c] = 0;
  param_1[0x4d] = 0;
  param_1[0x4e] = &PTR_LAB_004cc1c4;
  param_1[0x4f] = 0;
  param_1[0x50] = 0;
  param_1[0x51] = 0;
  param_1[0x52] = 0;
  FUN_004304e0(param_1 + 0x4e,0,&DAT_004ecc58);
  param_1[0x4f] = 0;
  param_1[0x50] = 0;
  param_1[0x52] = 0;
  param_1[0x51] = 0;
  if ((undefined4 *)param_1[0x4f] != (undefined4 *)0x0) {
    FUN_00430d40(&DAT_004ecc58,(undefined4 *)param_1[0x4f],param_1[0x50]);
    param_1[0x4f] = 0;
    param_1[0x51] = 0;
  }
  param_1[0x50] = 0;
  *param_1 = &PTR_LAB_004cc194;
  FUN_0042d7e0((int)param_1);
  return param_1;
}


/* 0042d750 size=142 */

void __fastcall FUN_0042d750(undefined4 *param_1)

{
  int iVar1;
  
  *param_1 = &PTR_LAB_004cc194;
  FUN_0042d8e0((int)param_1);
  param_1[0x4e] = &PTR_LAB_004cc1c4;
  if ((undefined4 *)param_1[0x4f] != (undefined4 *)0x0) {
    FUN_00430d40(&DAT_004ecc58,(undefined4 *)param_1[0x4f],param_1[0x50] + param_1[0x51]);
    param_1[0x4f] = 0;
    param_1[0x51] = 0;
  }
  param_1[0x50] = 0;
  iVar1 = param_1[0x16];
  param_1[0x15] = &PTR_LAB_004cc1f4;
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    param_1[0x16] = 0;
    param_1[0x18] = 0;
  }
  param_1[0x17] = 0;
  return;
}


/* 0042d7e0 size=245 */

void __fastcall FUN_0042d7e0(int param_1)

{
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)(param_1 + 0x94) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0xac) = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  *(undefined4 *)(param_1 + 0xb4) = 0;
  *(undefined4 *)(param_1 + 0xb8) = 0;
  *(undefined4 *)(param_1 + 0xbc) = 0;
  *(undefined4 *)(param_1 + 0xc0) = 0;
  *(undefined4 *)(param_1 + 0xc4) = 0;
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  *(undefined4 *)(param_1 + 0xd8) = 0;
  *(undefined4 *)(param_1 + 0xdc) = 0;
  *(undefined4 *)(param_1 + 0xe0) = 0;
  *(undefined4 *)(param_1 + 0xe4) = 0;
  *(undefined4 *)(param_1 + 0xe8) = 0;
  *(undefined4 *)(param_1 + 0xec) = 0;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  *(undefined4 *)(param_1 + 0xf4) = 0;
  *(undefined2 *)(param_1 + 0xf8) = 0;
  *(undefined4 *)(param_1 + 0xfc) = 0;
  *(undefined4 *)(param_1 + 0x100) = 0;
  *(undefined4 *)(param_1 + 0x104) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x150) = 0xffffffff;
  return;
}


/* 0042d8e0 size=450 */

void __fastcall FUN_0042d8e0(int param_1)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  
  if ((*(byte *)(param_1 + 0x4c) & 1) == 0) {
    if (*(undefined4 **)(param_1 + 0x13c) != (undefined4 *)0x0) {
      FUN_00430d40(&DAT_004ecc58,*(undefined4 **)(param_1 + 0x13c),
                   *(int *)(param_1 + 0x140) + *(int *)(param_1 + 0x144));
      *(undefined4 *)(param_1 + 0x13c) = 0;
      *(undefined4 *)(param_1 + 0x144) = 0;
    }
    *(undefined4 *)(param_1 + 0x140) = 0;
    FUN_0042ce40(param_1 + 0x108);
    uVar2 = 0;
    if (*(int *)(param_1 + 0xb4) != 0) {
      iVar4 = 0;
      do {
        puVar1 = *(undefined **)(*(int *)(param_1 + 0xb0) + iVar4);
        if (puVar1 != (undefined *)0x0) {
          FUN_00430fe0(puVar1);
        }
        uVar2 = uVar2 + 1;
        iVar4 = iVar4 + 0x24;
      } while (uVar2 < *(uint *)(param_1 + 0xb4));
    }
    if (*(undefined **)(param_1 + 0xb0) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0xb0));
    }
    if (*(undefined **)(param_1 + 0x80) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0x80));
    }
    if (*(undefined **)(param_1 + 0xfc) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0xfc));
    }
    if (*(undefined **)(param_1 + 0x104) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0x104));
    }
    if (*(undefined **)(param_1 + 0x88) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0x88));
    }
    if (*(undefined **)(param_1 + 0x90) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0x90));
    }
    if (*(undefined **)(param_1 + 0xa0) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0xa0));
    }
    if (*(undefined **)(param_1 + 0xa8) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0xa8));
    }
    if (*(undefined **)(param_1 + 0x68) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0x68));
    }
    iVar4 = *(int *)(param_1 + 0x78);
    if (iVar4 != 0) {
      iVar3 = *(int *)(iVar4 + -4);
      if (-1 < iVar3 + -1) {
        pvVar5 = (void *)(iVar3 * 0x40 + iVar4 + 0x24);
        do {
          pvVar5 = (void *)((int)pvVar5 + -0x40);
          thunk_FUN_00468490(pvVar5);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      FUN_00430df0((undefined *)(iVar4 + -4));
    }
    if (*(undefined **)(param_1 + 0xbc) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0xbc));
    }
    if (*(undefined **)(param_1 + 0xb8) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0xb8));
    }
    if (*(undefined **)(param_1 + 0xf4) != (undefined *)0x0) {
      FUN_00430fe0(*(undefined **)(param_1 + 0xf4));
    }
    DAT_004e95e8 = DAT_004e95e8 - *(int *)(param_1 + 0x50);
  }
  FUN_0042dab0(param_1);
  FUN_0042d7e0(param_1);
  return;
}


/* 0042dab0 size=28 */

void __fastcall FUN_0042dab0(int param_1)

{
  if (*(undefined **)(param_1 + 0x70) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)(param_1 + 0x70));
    *(undefined4 *)(param_1 + 0x70) = 0;
  }
  return;
}


/* 0042dad0 size=1197 */

undefined4 __thiscall FUN_0042dad0(void *this,int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined *puVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  int iVar8;
  int iVar9;
  int local_10;
  uint local_c;
  
  iVar2 = param_1;
  FUN_0042d8e0((int)this);
  iVar9 = *(int *)(param_1 + 0x74);
  iVar3 = FUN_00430de0(iVar9 * 0x18);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else if (-1 < iVar9 + -1) {
    puVar7 = (undefined1 *)(iVar3 + 0x16);
    do {
      puVar1 = puVar7 + -10;
      *puVar7 = 0;
      *(undefined4 *)(puVar7 + -0x16) = 0;
      puVar7[1] = 0;
      *(undefined2 *)(puVar7 + -2) = 0xffff;
      *(undefined4 *)(puVar7 + -0xe) = 0;
      *(undefined4 *)(puVar7 + -0x12) = 0;
      *(undefined1 **)(puVar7 + -6) = puVar1;
      puVar7 = puVar7 + 0x18;
      iVar9 = iVar9 + -1;
      *(undefined1 **)puVar1 = puVar1;
    } while (iVar9 != 0);
  }
  *(int *)((int)this + 0x70) = iVar3;
  if (iVar3 == 0) {
    return 0;
  }
  local_c = 0;
  if (*(int *)(param_1 + 0x74) != 0) {
    param_1 = 0;
    do {
      puVar4 = (undefined4 *)(param_1 + *(int *)((int)this + 0x70));
      iVar9 = param_1 + *(int *)(iVar2 + 0x70);
      local_10 = 2;
      iVar3 = iVar9 - (int)puVar4;
      *(undefined2 *)(puVar4 + 5) = *(undefined2 *)(iVar9 + 0x14);
      puVar6 = puVar4 + 3;
      puVar4[4] = puVar6;
      *puVar6 = puVar6;
      do {
        puVar4 = puVar4 + 1;
        puVar5 = FUN_0042e0d0(this,iVar2,*(undefined **)(iVar3 + (int)puVar4));
        *puVar4 = puVar5;
        local_10 = local_10 + -1;
      } while (local_10 != 0);
      local_c = local_c + 1;
      param_1 = param_1 + 0x18;
    } while (local_c < *(uint *)(iVar2 + 0x74));
  }
  *(undefined4 *)((int)this + 0x74) = *(undefined4 *)(iVar2 + 0x74);
  puVar5 = FUN_0042e0d0(this,iVar2,*(undefined **)(iVar2 + 0x9c));
  *(undefined **)((int)this + 0x9c) = puVar5;
  if (*(undefined4 **)((int)this + 0x13c) != (undefined4 *)0x0) {
    FUN_00430d40(&DAT_004ecc58,*(undefined4 **)((int)this + 0x13c),
                 *(int *)((int)this + 0x140) + *(int *)((int)this + 0x144));
    *(undefined4 *)((int)this + 0x13c) = 0;
    *(undefined4 *)((int)this + 0x144) = 0;
  }
  *(undefined4 *)((int)this + 0x140) = *(undefined4 *)(iVar2 + 0x140);
  *(undefined4 *)((int)this + 0x144) = *(undefined4 *)(iVar2 + 0x144);
  *(undefined4 *)((int)this + 0x148) = *(undefined4 *)(iVar2 + 0x148);
  iVar9 = *(int *)((int)this + 0x140) + *(int *)((int)this + 0x144);
  if (iVar9 == 0) {
    *(undefined4 *)((int)this + 0x140) = 0;
    *(undefined4 *)((int)this + 0x144) = 0;
    *(undefined4 *)((int)this + 0x13c) = 0;
  }
  else {
    puVar6 = FUN_00430d80(&DAT_004ecc58,0,iVar9);
    *(undefined4 **)((int)this + 0x13c) = puVar6;
    if (puVar6 == (undefined4 *)0x0) {
      *(undefined4 *)((int)this + 0x140) = 0;
      *(undefined4 *)((int)this + 0x144) = 0;
      return 0;
    }
    local_c = 0;
    if (*(int *)((int)this + 0x140) != 0) {
      param_1 = 0;
      do {
        iVar9 = *(int *)(iVar2 + 0x13c) + param_1;
        iVar3 = *(int *)((int)this + 0x13c) + param_1;
        puVar7 = (undefined1 *)(iVar3 + 4);
        do {
          *puVar7 = puVar7[iVar9 - iVar3];
          puVar7 = puVar7 + 1;
        } while (puVar7 + (-4 - iVar3) < (undefined1 *)0x41);
        *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(iVar9 + 0x48);
        *(undefined4 *)(iVar3 + 0x4c) = *(undefined4 *)(iVar9 + 0x4c);
        FUN_00430a90((void *)(iVar3 + 0x50),iVar9 + 0x50,&DAT_004ecc58);
        *(undefined4 *)(iVar3 + 100) = *(undefined4 *)(iVar9 + 100);
        FUN_00430bd0((void *)(iVar3 + 0x68),iVar9 + 0x68,&DAT_004ecc58);
        *(undefined4 *)(iVar3 + 0x7c) = *(undefined4 *)(iVar9 + 0x7c);
        puVar6 = (undefined4 *)(iVar9 + 0x80);
        puVar4 = (undefined4 *)(iVar3 + 0x80);
        for (iVar8 = 0xc; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar4 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar4 = puVar4 + 1;
        }
        *(undefined4 *)(iVar3 + 0xb0) = *(undefined4 *)(iVar9 + 0xb0);
        *(undefined4 *)(iVar3 + 0xb4) = *(undefined4 *)(iVar9 + 0xb4);
        *(undefined4 *)(iVar3 + 0xb8) = *(undefined4 *)(iVar9 + 0xb8);
        *(undefined4 *)(iVar3 + 0xbc) = *(undefined4 *)(iVar9 + 0xbc);
        local_c = local_c + 1;
        param_1 = param_1 + 0xc0;
      } while (local_c < *(uint *)((int)this + 0x140));
    }
  }
  *(undefined4 *)((int)this + 0x68) = *(undefined4 *)(iVar2 + 0x68);
  *(undefined4 *)((int)this + 0x6c) = *(undefined4 *)(iVar2 + 0x6c);
  *(undefined4 *)((int)this + 0x78) = *(undefined4 *)(iVar2 + 0x78);
  *(undefined4 *)((int)this + 0x7c) = *(undefined4 *)(iVar2 + 0x7c);
  *(undefined4 *)((int)this + 0x80) = *(undefined4 *)(iVar2 + 0x80);
  *(undefined4 *)((int)this + 0x84) = *(undefined4 *)(iVar2 + 0x84);
  *(undefined4 *)((int)this + 0x88) = *(undefined4 *)(iVar2 + 0x88);
  *(undefined4 *)((int)this + 0x8c) = *(undefined4 *)(iVar2 + 0x8c);
  *(undefined4 *)((int)this + 0x90) = *(undefined4 *)(iVar2 + 0x90);
  *(undefined4 *)((int)this + 0x94) = *(undefined4 *)(iVar2 + 0x94);
  *(undefined4 *)((int)this + 0x98) = *(undefined4 *)(iVar2 + 0x98);
  *(undefined4 *)((int)this + 0x9c) = *(undefined4 *)(iVar2 + 0x9c);
  *(undefined4 *)((int)this + 0xa0) = *(undefined4 *)(iVar2 + 0xa0);
  *(undefined4 *)((int)this + 0xa4) = *(undefined4 *)(iVar2 + 0xa4);
  *(undefined4 *)((int)this + 0x100) = *(undefined4 *)(iVar2 + 0x100);
  *(undefined4 *)((int)this + 0xa8) = *(undefined4 *)(iVar2 + 0xa8);
  *(undefined4 *)((int)this + 0xac) = *(undefined4 *)(iVar2 + 0xac);
  *(undefined4 *)((int)this + 0xb0) = *(undefined4 *)(iVar2 + 0xb0);
  *(undefined4 *)((int)this + 0xb4) = *(undefined4 *)(iVar2 + 0xb4);
  *(undefined4 *)((int)this + 0xb8) = *(undefined4 *)(iVar2 + 0xb8);
  *(undefined4 *)((int)this + 0xbc) = *(undefined4 *)(iVar2 + 0xbc);
  *(undefined4 *)((int)this + 0xc0) = *(undefined4 *)(iVar2 + 0xc0);
  _strncpy((char *)((int)this + 4),(char *)(iVar2 + 4),0x40);
  *(undefined1 *)((int)this + 0x44) = 0;
  *(undefined4 *)((int)this + 0xc4) = *(undefined4 *)(iVar2 + 0xc4);
  *(undefined4 *)((int)this + 200) = *(undefined4 *)(iVar2 + 200);
  *(undefined4 *)((int)this + 0xcc) = *(undefined4 *)(iVar2 + 0xcc);
  *(undefined4 *)((int)this + 0xd0) = *(undefined4 *)(iVar2 + 0xd0);
  *(undefined4 *)((int)this + 0xd4) = *(undefined4 *)(iVar2 + 0xd4);
  *(undefined4 *)((int)this + 0xd8) = *(undefined4 *)(iVar2 + 0xd8);
  *(undefined4 *)((int)this + 0xdc) = *(undefined4 *)(iVar2 + 0xdc);
  *(undefined4 *)((int)this + 0xe0) = *(undefined4 *)(iVar2 + 0xe0);
  *(undefined4 *)((int)this + 0xe4) = *(undefined4 *)(iVar2 + 0xe4);
  *(undefined4 *)((int)this + 0xe8) = *(undefined4 *)(iVar2 + 0xe8);
  *(undefined4 *)((int)this + 0xec) = *(undefined4 *)(iVar2 + 0xec);
  *(undefined4 *)((int)this + 0xf0) = *(undefined4 *)(iVar2 + 0xf0);
  *(undefined4 *)((int)this + 0xf4) = *(undefined4 *)(iVar2 + 0xf4);
  *(undefined2 *)((int)this + 0xf8) = *(undefined2 *)(iVar2 + 0xf8);
  *(undefined4 *)((int)this + 0xfc) = *(undefined4 *)(iVar2 + 0xfc);
  *(undefined4 *)((int)this + 0x104) = *(undefined4 *)(iVar2 + 0x104);
  puVar6 = (undefined4 *)(iVar2 + 0x108);
  puVar4 = (undefined4 *)((int)this + 0x108);
  for (iVar9 = 0xc; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar4 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)((int)this + 0x48) = *(undefined4 *)(iVar2 + 0x48);
  *(undefined4 *)((int)this + 0x14c) = *(undefined4 *)(iVar2 + 0x14c);
  *(uint *)((int)this + 0x4c) = *(uint *)((int)this + 0x4c) | 1;
  return 1;
}


/* 0042df80 size=40 */

void __fastcall FUN_0042df80(int param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_0042d4f0(*(int **)(param_1 + 0xa0),*(int *)(param_1 + 0xa4),
                                (float *)(param_1 + 0xe8));
  *(float *)(param_1 + 0x14c) = (float)fVar1;
  return;
}


/* 0042e0d0 size=71 */

undefined * __thiscall FUN_0042e0d0(void *this,int param_1,undefined *param_2)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_004d7c44;
  if ((param_2 != PTR_DAT_004d7c44) && (puVar1 = PTR_DAT_004d7c48, param_2 != PTR_DAT_004d7c48)) {
    if (param_2 != (undefined *)0x0) {
      return (undefined *)
             (*(int *)((int)this + 0x70) + (((int)param_2 - *(int *)(param_1 + 0x70)) / 0x18) * 0x18
             );
    }
    puVar1 = (undefined *)0x0;
  }
  return puVar1;
}


/* 0042e120 size=62 */

void * __fastcall FUN_0042e120(void *param_1)

{
  FUN_00468450(param_1);
  *(undefined4 *)((int)param_1 + 8) = 0;
  *(undefined4 *)((int)param_1 + 0xc) = 0;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  *(undefined4 *)((int)param_1 + 0x28) = 0;
  *(undefined4 *)((int)param_1 + 0x2c) = 0;
  *(undefined2 *)((int)param_1 + 0x30) = 0;
  *(undefined2 *)((int)param_1 + 0x32) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  *(undefined4 *)((int)param_1 + 0x38) = 0;
  *(void **)((int)param_1 + 0x18) = param_1;
  *(undefined4 *)((int)param_1 + 0x1c) = 0;
  *(undefined4 *)((int)param_1 + 0x20) = 0;
  FUN_00468470(param_1,param_1);
  return param_1;
}


/* 0042e160 size=24 */

void __fastcall FUN_0042e160(void *param_1)

{
  FUN_00430df0(*(undefined **)((int)param_1 + 0x38));
  thunk_FUN_00468490(param_1);
  return;
}


/* 0042e180 size=100 */

void __thiscall FUN_0042e180(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  
  uVar3 = 0xffffffff;
  pcVar2 = param_1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  if (~uVar3 != 1) {
    if (*(undefined **)((int)this + 0x38) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)((int)this + 0x38));
      *(undefined4 *)((int)this + 0x38) = 0;
    }
    pcVar2 = (char *)FUN_00430de0(~uVar3);
    uVar3 = 0xffffffff;
    *(char **)((int)this + 0x38) = pcVar2;
    do {
      pcVar5 = param_1;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar5 = param_1 + 1;
      cVar1 = *param_1;
      param_1 = pcVar5;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar5 + -uVar3;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar2 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar2 = pcVar2 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar2 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar2 = pcVar2 + 1;
    }
  }
  return;
}


/* 0042e8a0 size=216 */

void __thiscall FUN_0042e8a0(void *this,undefined4 *param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = 0x10;
  puVar2 = (undefined4 *)(*param_2 * 0xc0 + *(int *)((int)this + 4));
  *param_2 = *param_2 + 1;
  puVar3 = puVar2;
  puVar4 = param_1;
  while( true ) {
    puVar4 = puVar4 + 1;
    puVar3 = puVar3 + 1;
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    *puVar4 = *puVar3;
  }
  *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
  *param_1 = &PTR_LAB_004cc168;
  param_1[0x12] = puVar2[0x12];
  param_1[0x13] = puVar2[0x13];
  param_1[0x14] = &PTR_LAB_004cc254;
  param_1[0x15] = puVar2[0x15];
  param_1[0x16] = puVar2[0x16];
  param_1[0x17] = puVar2[0x17];
  param_1[0x18] = puVar2[0x18];
  param_1[0x14] = &PTR_LAB_004cbcc4;
  param_1[0x19] = puVar2[0x19];
  param_1[0x1a] = &PTR_LAB_004cc224;
  param_1[0x1b] = puVar2[0x1b];
  param_1[0x1c] = puVar2[0x1c];
  param_1[0x1d] = puVar2[0x1d];
  param_1[0x1e] = puVar2[0x1e];
  param_1[0x1a] = &PTR_LAB_004cc138;
  param_1[0x1f] = puVar2[0x1f];
  puVar3 = puVar2 + 0x20;
  puVar4 = param_1 + 0x20;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  param_1[0x2c] = puVar2[0x2c];
  param_1[0x2d] = puVar2[0x2d];
  param_1[0x2e] = puVar2[0x2e];
  param_1[0x2f] = puVar2[0x2f];
  *param_1 = &DAT_004cc10c;
  return;
}


/* 0042f600 size=418 */

int __thiscall FUN_0042f600(void *this,int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  puVar1 = (undefined1 *)((int)this + 4);
  do {
    *puVar1 = puVar1[param_1 - (int)this];
    puVar1 = puVar1 + 1;
  } while (puVar1 + (-4 - (int)this) < (undefined1 *)0x41);
  *(undefined4 *)((int)this + 0x48) = *(undefined4 *)(param_1 + 0x48);
  *(undefined4 *)((int)this + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  if (*(int *)((int)this + 0x54) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x54));
    *(undefined4 *)((int)this + 0x54) = 0;
    *(undefined4 *)((int)this + 0x5c) = 0;
  }
  *(undefined4 *)((int)this + 0x58) = *(undefined4 *)(param_1 + 0x58);
  *(undefined4 *)((int)this + 0x5c) = *(undefined4 *)(param_1 + 0x5c);
  *(undefined4 *)((int)this + 0x60) = *(undefined4 *)(param_1 + 0x60);
  iVar2 = *(int *)((int)this + 0x5c) + *(int *)((int)this + 0x58);
  if (iVar2 == 0) {
    *(undefined4 *)((int)this + 0x58) = 0;
    *(undefined4 *)((int)this + 0x5c) = 0;
    *(undefined4 *)((int)this + 0x54) = 0;
  }
  else {
    iVar2 = FUN_00456f10(&DAT_004ecc58,0,iVar2);
    *(int *)((int)this + 0x54) = iVar2;
    if (iVar2 == 0) {
      *(undefined4 *)((int)this + 0x58) = 0;
      *(undefined4 *)((int)this + 0x5c) = 0;
    }
    else {
      uVar4 = 0;
      if (*(int *)((int)this + 0x58) != 0) {
        do {
          *(undefined4 *)(*(int *)((int)this + 0x54) + uVar4 * 4) =
               *(undefined4 *)(*(int *)(param_1 + 0x54) + uVar4 * 4);
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(uint *)((int)this + 0x58));
      }
    }
  }
  *(undefined4 *)((int)this + 100) = *(undefined4 *)(param_1 + 100);
  if (*(int *)((int)this + 0x6c) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x6c));
    *(undefined4 *)((int)this + 0x6c) = 0;
    *(undefined4 *)((int)this + 0x74) = 0;
  }
  *(undefined4 *)((int)this + 0x70) = *(undefined4 *)(param_1 + 0x70);
  *(undefined4 *)((int)this + 0x74) = *(undefined4 *)(param_1 + 0x74);
  *(undefined4 *)((int)this + 0x78) = *(undefined4 *)(param_1 + 0x78);
  iVar2 = *(int *)((int)this + 0x74) + *(int *)((int)this + 0x70);
  if (iVar2 == 0) {
    *(undefined4 *)((int)this + 0x70) = 0;
    *(undefined4 *)((int)this + 0x74) = 0;
    *(undefined4 *)((int)this + 0x6c) = 0;
  }
  else {
    iVar2 = FUN_00430ce0(&DAT_004ecc58,0,iVar2);
    *(int *)((int)this + 0x6c) = iVar2;
    if (iVar2 == 0) {
      *(undefined4 *)((int)this + 0x70) = 0;
      *(undefined4 *)((int)this + 0x74) = 0;
    }
    else {
      uVar4 = 0;
      if (*(int *)((int)this + 0x70) != 0) {
        iVar2 = 0;
        do {
          puVar5 = (undefined4 *)(iVar2 + *(int *)(param_1 + 0x6c));
          puVar6 = (undefined4 *)(iVar2 + *(int *)((int)this + 0x6c));
          for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar6 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar6 = puVar6 + 1;
          }
          uVar4 = uVar4 + 1;
          iVar2 = iVar2 + 0x18;
        } while (uVar4 < *(uint *)((int)this + 0x70));
      }
    }
  }
  *(undefined4 *)((int)this + 0x7c) = *(undefined4 *)(param_1 + 0x7c);
  puVar5 = (undefined4 *)(param_1 + 0x80);
  puVar6 = (undefined4 *)((int)this + 0x80);
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  *(undefined4 *)((int)this + 0xb0) = *(undefined4 *)(param_1 + 0xb0);
  *(undefined4 *)((int)this + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)((int)this + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
  *(undefined4 *)((int)this + 0xbc) = *(undefined4 *)(param_1 + 0xbc);
  return (int)this;
}


/* 0042f7b0 size=39 */

void __thiscall FUN_0042f7b0(void *this,int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)((int)this + 4);
  do {
    *puVar1 = puVar1[param_1 - (int)this];
    puVar1 = puVar1 + 1;
  } while (puVar1 + (-4 - (int)this) < (undefined1 *)0x41);
  return;
}


/* 0042f7e0 size=15 */

void __fastcall FUN_0042f7e0(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}


/* 0042f7f0 size=156 */

void * __thiscall FUN_0042f7f0(void *this,undefined4 *param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if (0xfffffffd < param_2) {
    FUN_004b97f0();
  }
  iVar2 = *(int *)((int)this + 4);
  if (((iVar2 == 0) || (cVar1 = *(char *)(iVar2 + -1), cVar1 == '\0')) || (cVar1 == -1)) {
    if (param_2 == 0) {
      FUN_00414100(this,'\x01');
      return this;
    }
    if ((*(uint *)((int)this + 0xc) < 0x20) && (param_2 <= *(uint *)((int)this + 0xc)))
    goto LAB_0042f860;
    FUN_00414100(this,'\x01');
  }
  else if (param_2 == 0) {
    *(char *)(iVar2 + -1) = cVar1 + -1;
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 0xc) = 0;
    return this;
  }
  FUN_0042ff80(param_2);
LAB_0042f860:
  puVar4 = *(undefined4 **)((int)this + 4);
  for (uVar3 = param_2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar4 = *param_1;
    param_1 = param_1 + 1;
    puVar4 = puVar4 + 1;
  }
  for (uVar3 = param_2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)puVar4 = *(undefined1 *)param_1;
    param_1 = (undefined4 *)((int)param_1 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  *(uint *)((int)this + 8) = param_2;
  *(undefined1 *)(param_2 + *(int *)((int)this + 4)) = 0;
  return this;
}


/* 0042f890 size=633 */

void __thiscall FUN_0042f890(void *this,undefined1 *param_1,uint param_2,undefined1 *param_3)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined1 *puVar6;
  void *pvVar7;
  undefined1 *puVar8;
  void *pvVar9;
  undefined1 *puVar10;
  
  puVar6 = *(undefined1 **)((int)this + 8);
  if (param_2 <= (uint)(*(int *)((int)this + 0xc) - (int)puVar6 >> 4)) {
    if ((uint)((int)puVar6 - (int)param_1 >> 4) < param_2) {
      puVar8 = param_1 + param_2 * 0x10;
      if (param_1 != puVar6) {
        puVar10 = puVar8 + param_2 * -0x10;
        do {
          if (puVar8 != (undefined1 *)0x0) {
            FUN_0042fb10(puVar8,puVar10);
          }
          puVar10 = puVar10 + 0x10;
          puVar8 = puVar8 + 0x10;
        } while (puVar10 != puVar6);
      }
      pvVar9 = *(void **)((int)this + 8);
      iVar5 = param_2 - ((int)pvVar9 - (int)param_1 >> 4);
      if (iVar5 != 0) {
        do {
          if (pvVar9 != (void *)0x0) {
            FUN_0042fb10(pvVar9,param_3);
          }
          pvVar9 = (void *)((int)pvVar9 + 0x10);
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      puVar6 = *(undefined1 **)((int)this + 8);
      for (; param_1 != puVar6; param_1 = param_1 + 0x10) {
        FUN_0042fc30(param_1,param_3,0,0xffffffff);
      }
    }
    else {
      if (param_2 == 0) {
        return;
      }
      puVar8 = puVar6;
      for (puVar10 = puVar6 + param_2 * -0x10; puVar10 != puVar6; puVar10 = puVar10 + 0x10) {
        FUN_00430970(puVar8,puVar10);
        puVar8 = puVar8 + 0x10;
      }
      pvVar9 = *(void **)((int)this + 8);
      puVar6 = (undefined1 *)((int)pvVar9 + param_2 * -0x10);
      while (param_1 != puVar6) {
        puVar6 = puVar6 + -0x10;
        pvVar9 = (void *)((int)pvVar9 + -0x10);
        FUN_0042fc30(pvVar9,puVar6,0,0xffffffff);
      }
      puVar6 = param_1 + param_2 * 0x10;
      for (; param_1 != puVar6; param_1 = param_1 + 0x10) {
        FUN_0042fc30(param_1,param_3,0,0xffffffff);
      }
    }
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + param_2 * 0x10;
    return;
  }
  iVar5 = *(int *)((int)this + 4);
  uVar4 = param_2;
  if (iVar5 != 0) {
    uVar3 = (int)puVar6 - iVar5 >> 4;
    if (param_2 < uVar3) {
      uVar4 = uVar3;
    }
    if (iVar5 != 0) {
      iVar5 = (int)puVar6 - iVar5 >> 4;
      goto LAB_0042f8d3;
    }
  }
  iVar5 = 0;
LAB_0042f8d3:
  iVar5 = uVar4 + iVar5;
  iVar1 = iVar5;
  if (iVar5 < 0) {
    iVar1 = 0;
  }
  pvVar2 = (void *)FUN_00430de0(iVar1 << 4);
  pvVar9 = pvVar2;
  for (puVar6 = *(undefined1 **)((int)this + 4); puVar6 != param_1; puVar6 = puVar6 + 0x10) {
    if (pvVar9 != (void *)0x0) {
      FUN_0042fb10(pvVar9,puVar6);
    }
    pvVar9 = (void *)((int)pvVar9 + 0x10);
  }
  if (param_2 != 0) {
    uVar4 = param_2;
    pvVar7 = pvVar9;
    do {
      if (pvVar7 != (void *)0x0) {
        FUN_0042fb10(pvVar7,param_3);
      }
      pvVar7 = (void *)((int)pvVar7 + 0x10);
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  puVar6 = *(undefined1 **)((int)this + 8);
  pvVar7 = (void *)(param_2 * 0x10 + (int)pvVar9);
  if (param_1 != puVar6) {
    puVar8 = param_1 + (int)pvVar7 + (param_2 * -0x10 - (int)pvVar9);
    do {
      if (pvVar7 != (void *)0x0) {
        FUN_0042fb10(pvVar7,puVar8);
      }
      puVar8 = puVar8 + 0x10;
      pvVar7 = (void *)((int)pvVar7 + 0x10);
    } while (puVar8 != puVar6);
  }
  pvVar9 = *(void **)((int)this + 8);
  for (pvVar7 = *(void **)((int)this + 4); pvVar7 != pvVar9; pvVar7 = (void *)((int)pvVar7 + 0x10))
  {
    FUN_00414100(pvVar7,'\x01');
  }
  FUN_00430df0(*(undefined **)((int)this + 4));
  *(void **)((int)this + 0xc) = (void *)(iVar5 * 0x10 + (int)pvVar2);
  if (*(int *)((int)this + 4) == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = *(int *)((int)this + 8) - *(int *)((int)this + 4) >> 4;
  }
  *(void **)((int)this + 4) = pvVar2;
  *(void **)((int)this + 8) = (void *)((iVar5 + param_2) * 0x10 + (int)pvVar2);
  return;
}


/* 0042fb10 size=282 */

undefined1 * __thiscall FUN_0042fb10(void *this,undefined1 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  *(undefined1 *)this = *param_1;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  uVar6 = DAT_004cc284;
  uVar1 = *(uint *)(param_1 + 8);
  uVar5 = uVar1;
  if (DAT_004cc284 < uVar1) {
    uVar5 = DAT_004cc284;
  }
  if (this == param_1) {
    if (uVar5 != 0) {
      FUN_004b9a1c();
    }
    FUN_004300a0(this);
    uVar1 = *(int *)((int)this + 8) - uVar5;
    if (uVar1 < uVar6) {
      uVar6 = uVar1;
    }
    if (uVar6 != 0) {
      puVar4 = (undefined4 *)(*(int *)((int)this + 4) + uVar5);
      FUN_004bab10(puVar4,(undefined4 *)((int)puVar4 + uVar6),uVar1 - uVar6);
      uVar6 = *(int *)((int)this + 8) - uVar6;
      uVar2 = FUN_0042fe50(this,uVar6,'\0');
      if ((char)uVar2 != '\0') {
        FUN_0042fe30(this,uVar6);
      }
    }
    FUN_004300a0(this);
    return this;
  }
  if ((uVar5 != 0) && (uVar5 == uVar1)) {
    puVar3 = *(undefined1 **)(param_1 + 4);
    if (puVar3 == (undefined1 *)0x0) {
      puVar3 = &DAT_004cc108;
    }
    if ((byte)puVar3[-1] < 0xfe) {
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 8) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
      puVar3 = *(undefined1 **)(param_1 + 4);
      if (puVar3 == (undefined1 *)0x0) {
        puVar3 = &DAT_004cc108;
      }
      *(undefined1 **)((int)this + 4) = puVar3;
      *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 8);
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
      puVar3[-1] = puVar3[-1] + '\x01';
      return this;
    }
  }
  uVar2 = FUN_0042fe50(this,uVar5,'\x01');
  if ((char)uVar2 != '\0') {
    puVar4 = *(undefined4 **)(param_1 + 4);
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)&DAT_004cc108;
    }
    puVar7 = *(undefined4 **)((int)this + 4);
    for (uVar1 = uVar5 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *puVar7 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar7 = puVar7 + 1;
    }
    for (uVar1 = uVar5 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    FUN_0042fe30(this,uVar5);
  }
  return this;
}


/* 0042fc30 size=512 */

void * __thiscall FUN_0042fc30(void *this,void *param_1,uint param_2,uint param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  
  if (*(uint *)((int)param_1 + 8) < param_2) {
    FUN_004b9a1c();
  }
  uVar8 = DAT_004cc284;
  uVar7 = *(uint *)((int)param_1 + 8) - param_2;
  if (param_3 < uVar7) {
    uVar7 = param_3;
  }
  if (this == param_1) {
    uVar7 = uVar7 + param_2;
    if (*(uint *)((int)this + 8) < uVar7) {
      FUN_004b9a1c();
    }
    FUN_004300a0(this);
    uVar3 = *(int *)((int)this + 8) - uVar7;
    if (uVar3 < uVar8) {
      uVar8 = uVar3;
    }
    if (uVar8 != 0) {
      puVar6 = (undefined4 *)(*(int *)((int)this + 4) + uVar7);
      FUN_004bab10(puVar6,(undefined4 *)((int)puVar6 + uVar8),uVar3 - uVar8);
      uVar8 = *(int *)((int)this + 8) - uVar8;
      uVar4 = FUN_0042fe50(this,uVar8,'\0');
      if ((char)uVar4 != '\0') {
        *(uint *)((int)this + 8) = uVar8;
        *(undefined1 *)(uVar8 + *(int *)((int)this + 4)) = 0;
      }
    }
    FUN_004300a0(this);
    uVar8 = *(uint *)((int)this + 8);
    if (uVar8 < param_2) {
      param_2 = uVar8;
    }
    if (param_2 == 0) {
      return this;
    }
    FUN_004bab10(*(undefined4 **)((int)this + 4),
                 (undefined4 *)((int)*(undefined4 **)((int)this + 4) + param_2),uVar8 - param_2);
    uVar8 = *(int *)((int)this + 8) - param_2;
    uVar4 = FUN_0042fe50(this,uVar8,'\0');
    if ((char)uVar4 == '\0') {
      return this;
    }
    FUN_0042fe30(this,uVar8);
    return this;
  }
  if ((uVar7 != 0) && (uVar7 == *(uint *)((int)param_1 + 8))) {
    puVar5 = *(undefined1 **)((int)param_1 + 4);
    if (puVar5 == (undefined1 *)0x0) {
      puVar5 = &DAT_004cc108;
    }
    if ((byte)puVar5[-1] < 0xfe) {
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
      puVar5 = *(undefined1 **)((int)param_1 + 4);
      if (puVar5 == (undefined1 *)0x0) {
        puVar5 = &DAT_004cc108;
      }
      *(undefined1 **)((int)this + 4) = puVar5;
      *(undefined4 *)((int)this + 8) = *(undefined4 *)((int)param_1 + 8);
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)param_1 + 0xc);
      puVar5[-1] = puVar5[-1] + '\x01';
      return this;
    }
  }
  uVar8 = FUN_0042ff70();
  if (uVar8 < uVar7) {
    FUN_004b97f0();
  }
  iVar2 = *(int *)((int)this + 4);
  if (((iVar2 == 0) || (cVar1 = *(char *)(iVar2 + -1), cVar1 == '\0')) || (cVar1 == -1)) {
    if (uVar7 == 0) {
      FUN_00414100(this,'\x01');
      return this;
    }
    if ((*(uint *)((int)this + 0xc) < 0x20) && (uVar7 <= *(uint *)((int)this + 0xc)))
    goto LAB_0042fdfc;
    FUN_00414100(this,'\x01');
  }
  else if (uVar7 == 0) {
    *(char *)(iVar2 + -1) = cVar1 + -1;
    FUN_00414100(this,'\0');
    return this;
  }
  FUN_0042ff80(uVar7);
LAB_0042fdfc:
  puVar5 = *(undefined1 **)((int)param_1 + 4);
  if (puVar5 == (undefined1 *)0x0) {
    puVar5 = &DAT_004cc108;
  }
  puVar6 = (undefined4 *)(puVar5 + param_2);
  puVar9 = *(undefined4 **)((int)this + 4);
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *puVar9 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar9 = puVar9 + 1;
  }
  for (uVar8 = uVar7 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined1 *)puVar9 = *(undefined1 *)puVar6;
    puVar6 = (undefined4 *)((int)puVar6 + 1);
    puVar9 = (undefined4 *)((int)puVar9 + 1);
  }
  *(uint *)((int)this + 8) = uVar7;
  *(undefined1 *)(uVar7 + *(int *)((int)this + 4)) = 0;
  return this;
}


/* 0042fe30 size=17 */

void __thiscall FUN_0042fe30(void *this,int param_1)

{
  *(int *)((int)this + 8) = param_1;
  *(undefined1 *)(*(int *)((int)this + 4) + param_1) = 0;
  return;
}


/* 0042fe50 size=282 */

/* FUN_0042fe50: lifted from original x86 -> lt_lifted.c */


/* 0042ff70 size=6 */

undefined4 FUN_0042ff70(void)

{
  return 0xfffffffd;
}


/* 0042ff80 size=95 */

int FUN_0042ff80(uint param_1)

{
  size_t sVar1;
  uint uVar2;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004c8fd0;
  pvStack_10 = ExceptionList;
  uVar2 = param_1 | 0x1f;
  if (0xfffffffd < (param_1 | 0x1f)) {
    uVar2 = param_1;
  }
  local_8 = 0;
  sVar1 = uVar2 + 2;
  if ((int)sVar1 < 0) {
    sVar1 = 0;
  }
  ExceptionList = &pvStack_10;
  FUN_00430de0(sVar1);
  FUN_00430006();
  return;
}


