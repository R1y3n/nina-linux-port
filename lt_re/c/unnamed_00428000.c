/* lithtech.exe decompilation - unnamed_00428000 */
#include "ghidra_types.h"

/* 004282e0 size=218 */

/* FUN_004282e0: lifted from original x86 -> lt_lifted.c */


/* 00428530 size=116 */

undefined4 * __fastcall FUN_00428530(int param_1)

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
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = 0;
    puVar2[8] = 0;
    *puVar2 = &PTR_FUN_004cc020;
  }
  FUN_0044df60(p_Var1);
  return puVar2;
}


/* 004285b0 size=59 */

void __thiscall FUN_004285b0(void *this,undefined4 *param_1)

{
  FUN_0044df50((LPCRITICAL_SECTION)((int)this + 0x20));
  (**(code **)*param_1)(0);
  if ((param_1 != (undefined4 *)0x0) && (this != (void *)0xfffffffc)) {
    *param_1 = *(undefined4 *)((int)this + 0x1c);
    *(undefined4 **)((int)this + 0x1c) = param_1;
  }
  FUN_0044df60((LPCRITICAL_SECTION)((int)this + 0x20));
  return;
}


/* 004285f0 size=116 */

undefined4 * __fastcall FUN_004285f0(int param_1)

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
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = 0;
    puVar2[8] = 0;
    *puVar2 = &PTR_FUN_004cbff4;
  }
  FUN_0044df60(p_Var1);
  return puVar2;
}


/* 00428670 size=48 */

void __fastcall FUN_00428670(int param_1)

{
  FUN_0044df50((LPCRITICAL_SECTION)(param_1 + 0x20));
  FUN_004b7c10(param_1 + 4);
  FUN_004b7b90((uint *)(param_1 + 4),0x24,0x20);
  FUN_0044df60((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}


/* 004286a0 size=60 */

undefined4 * __thiscall FUN_004286a0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbfd4;
  FUN_004b7c10((int)this + 4);
  FUN_0044df40((LPCRITICAL_SECTION)((int)this + 0x20));
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004286e0 size=60 */

undefined4 * __thiscall FUN_004286e0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cbfe4;
  FUN_004b7c10((int)this + 4);
  FUN_0044df40((LPCRITICAL_SECTION)((int)this + 0x20));
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00428720 size=94 */

undefined4 * __thiscall FUN_00428720(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cc0a4;
  if (1 < DAT_004e98ac) {
    FUN_00436670((byte *)s_close_stream__p_num_reads____u_b_004d7ad0,this);
  }
  if ((**(int **)((int)this + 0x10) == 1) && (*(FILE **)((int)this + 0xc) != (FILE *)0x0)) {
    FUN_004ba14f(*(FILE **)((int)this + 0xc));
  }
  *(undefined ***)this = &PTR_LAB_004cc078;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00428780 size=178 */

undefined4 __cdecl FUN_00428780(int *param_1,int *param_2)

{
  undefined4 uStack_4c;
  undefined4 *puStack_48;
  undefined4 uStack_44;
  undefined4 *puStack_40;
  undefined4 uStack_3c;
  undefined4 *puStack_38;
  undefined4 uStack_34;
  undefined4 *puStack_30;
  undefined4 uStack_2c;
  undefined4 *puStack_28;
  undefined4 auStack_24 [2];
  undefined4 uStack_1c;
  int *piStack_18;
  undefined4 uStack_14;
  int *piStack_10;
  undefined4 uStack_c;
  
  uStack_c = 4;
  piStack_10 = param_2;
  uStack_14 = 0x428794;
  (**(code **)(*param_1 + 8))();
  if (*param_2 == 0x46) {
    uStack_14 = 4;
    piStack_18 = param_1;
    uStack_1c = 0x4287ac;
    (**(code **)(*param_1 + 8))();
    uStack_1c = 4;
    auStack_24[0] = 0x4287ba;
    (**(code **)(*param_1 + 8))();
    puStack_28 = &uStack_14;
    auStack_24[0] = 4;
    uStack_2c = 0x4287c8;
    (**(code **)(*param_1 + 8))();
    puStack_30 = &uStack_1c;
    uStack_2c = 4;
    uStack_34 = 0x4287d6;
    (**(code **)(*param_1 + 8))();
    puStack_38 = auStack_24;
    uStack_34 = 4;
    uStack_3c = 0x4287e4;
    (**(code **)(*param_1 + 8))();
    puStack_40 = &uStack_2c;
    uStack_3c = 4;
    uStack_44 = 0x4287f2;
    (**(code **)(*param_1 + 8))();
    puStack_48 = &uStack_34;
    uStack_44 = 4;
    uStack_4c = 0x428800;
    (**(code **)(*param_1 + 8))();
    uStack_4c = 4;
    (**(code **)(*param_1 + 8))(&uStack_3c);
    (**(code **)(*param_1 + 8))(&uStack_44,4);
    (**(code **)(*param_1 + 8))(&uStack_4c,4);
    return 1;
  }
  return 0;
}


/* 00428840 size=138 */

undefined4 __cdecl FUN_00428840(int *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  undefined1 *unaff_retaddr;
  int local_4;
  
  piVar1 = param_1;
  iVar2 = FUN_00428780(param_1,&local_4);
  if (iVar2 == 0) {
    return 0x2a;
  }
  (**(code **)(*piVar1 + 8))(&param_1,4);
  if (param_1 == (int *)0x0) {
    *unaff_retaddr = 0;
  }
  else {
    if (param_1 < (int *)(local_4 + 1U)) {
      local_4 = (int)param_1 + -1;
    }
    (**(code **)(*piVar1 + 8))(unaff_retaddr,local_4);
    unaff_retaddr[local_4] = 0;
  }
  if (param_2 != (int *)0x0) {
    *param_2 = local_4;
  }
  return 0;
}


/* 004288d0 size=68 */

void __cdecl FUN_004288d0(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar2 = *(undefined **)(param_1 + 0xf4);
  if (puVar2 == (undefined *)0x0) {
    *(undefined4 *)(param_1 + 0xf4) = 0;
    return;
  }
  do {
    puVar1 = *(undefined **)(puVar2 + 0x10);
    (**(code **)(*(int *)(puVar2 + 0xc) + 8))(*(undefined4 *)(puVar2 + 8));
    FUN_00430fe0(puVar2);
    puVar2 = puVar1;
  } while (puVar1 != (undefined *)0x0);
  *(undefined4 *)(param_1 + 0xf4) = 0;
  return;
}


/* 00428920 size=78 */

int __cdecl FUN_00428920(int param_1,byte *param_2)

{
  int iVar1;
  uint uVar2;
  void *this;
  uint uVar3;
  
  uVar3 = 0;
  if (*(int *)(param_1 + 400) != 0) {
    do {
      iVar1 = *(int *)(*(int *)(param_1 + 0x18c) + uVar3 * 4);
      this = (void *)(*(int *)(iVar1 + 4) + 4);
      uVar2 = FUN_004c4c00(this,this,param_2);
      if (uVar2 == 0) {
        return iVar1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_1 + 400));
  }
  return 0;
}


/* 00428970 size=586 */

void __cdecl FUN_00428970(uint param_1,float *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  uint uVar7;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  iVar3 = (**(code **)**(undefined4 **)(param_1 + 0x1b0))();
  if (iVar3 == 0) {
    iVar3 = *(int *)(param_1 + 0x1b0);
    iVar1 = *(int *)(param_1 + 0x1b4);
    if (((iVar3 != 0) && (iVar1 != 0)) && (param_3 == 0)) {
      uVar7 = 0;
      if (*(int *)(iVar1 + 0xac) != 0) {
        iVar6 = 0;
        do {
          pfVar4 = (float *)(iVar6 + *(int *)(iVar3 + 0xa8));
          pfVar5 = (float *)(*(int *)(iVar1 + 0xa8) + iVar6);
          uVar7 = uVar7 + 1;
          iVar6 = iVar6 + 0xc;
          *pfVar5 = param_2[1] * pfVar4[1] + pfVar4[2] * param_2[2] + *pfVar4 * *param_2 +
                    param_2[3];
          pfVar5[1] = pfVar4[1] * param_2[5] + param_2[4] * *pfVar4 + pfVar4[2] * param_2[6] +
                      param_2[7];
          pfVar5[2] = pfVar4[1] * param_2[9] + param_2[8] * *pfVar4 + pfVar4[2] * param_2[10] +
                      param_2[0xb];
        } while (uVar7 < *(uint *)(iVar1 + 0xac));
      }
      iVar6 = 0;
      param_1 = 0;
      if (*(int *)(iVar1 + 0x6c) != 0) {
        do {
          fStack_1c = *(float *)(*(int *)(iVar3 + 0x68) + 0xc + iVar6);
          pfVar4 = (float *)(*(int *)(iVar3 + 0x68) + iVar6);
          fStack_24 = fStack_1c * *pfVar4;
          fStack_20 = fStack_1c * pfVar4[1];
          fStack_1c = fStack_1c * pfVar4[2];
          fStack_18 = fStack_24;
          fStack_14 = fStack_20;
          fStack_10 = fStack_1c;
          FUN_00428bc0(&fStack_c,param_2,&fStack_24);
          pfVar4 = (float *)(*(int *)(iVar3 + 0x68) + iVar6);
          pfVar5 = (float *)(iVar6 + *(int *)(iVar1 + 0x68));
          *pfVar5 = *pfVar4 * *param_2 + pfVar4[2] * param_2[2] + param_2[1] * pfVar4[1];
          pfVar5[1] = pfVar4[1] * param_2[5] + pfVar4[2] * param_2[6] + *pfVar4 * param_2[4];
          pfVar5[2] = pfVar4[1] * param_2[9] + pfVar4[2] * param_2[10] + *pfVar4 * param_2[8];
          iVar2 = *(int *)(iVar1 + 0x68);
          ((float *)(iVar6 + iVar2))[3] =
               fStack_c * *(float *)(iVar6 + iVar2) +
               fStack_4 * *(float *)(iVar6 + 8 + iVar2) + fStack_8 * *(float *)(iVar6 + 4 + iVar2);
          param_1 = param_1 + 1;
          iVar6 = iVar6 + 0x10;
        } while (param_1 < *(uint *)(iVar1 + 0x6c));
      }
      uVar7 = 0;
      if (*(int *)(iVar1 + 0xa4) != 0) {
        do {
          iVar6 = *(int *)(*(int *)(iVar3 + 0xa0) + uVar7 * 4);
          iVar2 = *(int *)(*(int *)(iVar1 + 0xa0) + uVar7 * 4);
          pfVar4 = (float *)(iVar6 + 0x18);
          uVar7 = uVar7 + 1;
          *(float *)(iVar2 + 0x18) =
               *(float *)(iVar6 + 0x20) * param_2[2] +
               *pfVar4 * *param_2 + param_2[1] * *(float *)(iVar6 + 0x1c) + param_2[3];
          *(float *)(iVar2 + 0x1c) =
               param_2[5] * *(float *)(iVar6 + 0x1c) +
               param_2[6] * *(float *)(iVar6 + 0x20) + *pfVar4 * param_2[4] + param_2[7];
          *(float *)(iVar2 + 0x20) =
               param_2[9] * *(float *)(iVar6 + 0x1c) +
               param_2[10] * *(float *)(iVar6 + 0x20) + *pfVar4 * param_2[8] + param_2[0xb];
        } while (uVar7 < *(uint *)(iVar1 + 0xa4));
      }
    }
  }
  return;
}


/* 00428bc0 size=92 */

void __cdecl FUN_00428bc0(float *param_1,float *param_2,float *param_3)

{
  *param_1 = *param_2 * *param_3 + param_2[1] * param_3[1] + param_2[2] * param_3[2] + param_2[3];
  param_1[1] = param_2[5] * param_3[1] + param_2[4] * *param_3 + param_2[6] * param_3[2] +
               param_2[7];
  param_1[2] = param_2[9] * param_3[1] + param_2[8] * *param_3 + param_2[10] * param_3[2] +
               param_2[0xb];
  return;
}


/* 00428c20 size=124 */

int __cdecl FUN_00428c20(int param_1,byte *param_2,uint *param_3)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  uint uVar6;
  bool bVar7;
  
  uVar6 = 0;
  if (*(uint *)(param_1 + 0xb4) != 0) {
    puVar4 = *(undefined4 **)(param_1 + 0xb0);
    do {
      pbVar2 = (byte *)*puVar4;
      pbVar5 = param_2;
      do {
        bVar1 = *pbVar2;
        bVar7 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00428c65:
          iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_00428c6a;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar7 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00428c65;
        pbVar2 = pbVar2 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00428c6a:
      if (iVar3 == 0) {
        if (param_3 != (uint *)0x0) {
          *param_3 = uVar6;
        }
        return *(int *)(param_1 + 0xb0) + uVar6 * 0x24;
      }
      uVar6 = uVar6 + 1;
      puVar4 = puVar4 + 9;
    } while (uVar6 < *(uint *)(param_1 + 0xb4));
  }
  return 0;
}


/* 00428ca0 size=88 */

int __cdecl FUN_00428ca0(int param_1,byte *param_2,uint *param_3,uint *param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 400) != 0) {
    do {
      iVar1 = FUN_00428c20(*(int *)(*(int *)(*(int *)(param_1 + 0x18c) + uVar2 * 4) + 4),param_2,
                           param_4);
      if (iVar1 != 0) {
        if (param_3 == (uint *)0x0) {
          return iVar1;
        }
        *param_3 = uVar2;
        return iVar1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_1 + 400));
  }
  return 0;
}


/* 00428d00 size=104 */

int __thiscall FUN_00428d00(void *this,int param_1,byte *param_2,uint *param_3)

{
  uint uVar1;
  void *extraout_ECX;
  uint uVar2;
  int iVar3;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 0x1b4) != 0) {
    iVar3 = 0;
    do {
      uVar1 = FUN_004c4c00(this,(byte *)(iVar3 + *(int *)(param_1 + 0x1b0)),param_2);
      if (uVar1 == 0) {
        if (param_3 != (uint *)0x0) {
          *param_3 = uVar2;
        }
        return *(int *)(param_1 + 0x1b0) + uVar2 * 0x38;
      }
      uVar2 = uVar2 + 1;
      iVar3 = iVar3 + 0x38;
      this = extraout_ECX;
    } while (uVar2 < *(uint *)(param_1 + 0x1b4));
  }
  return 0;
}


/* 00428d70 size=77 */

undefined4 __cdecl FUN_00428d70(char *param_1,undefined4 param_2,undefined1 *param_3,uint param_4)

{
  char cVar1;
  uint uVar2;
  
  if (param_4 < 8) {
    return 0;
  }
  uVar2 = 0xffffffff;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *param_1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  if (param_4 - 8 < ~uVar2 - 1) {
    return 0;
  }
  FUN_004b9f62(param_3,(byte *)s__s_d__s_004d7b00,&DAT_004d7b08);
  return 1;
}


/* 00428dc0 size=63 */

void __fastcall FUN_00428dc0(undefined1 *param_1)

{
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *param_1 = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  param_1[0x28] = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined2 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x34) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0x3f800000;
  return;
}


/* 00428e00 size=12 */

undefined4 * __fastcall FUN_00428e00(undefined4 *param_1)

{
  FUN_00428e20(param_1);
  return param_1;
}


/* 00428e20 size=14 */

void __fastcall FUN_00428e20(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  return;
}


/* 00428e30 size=70 */

void __fastcall FUN_00428e30(byte *param_1)

{
  undefined4 *puVar1;
  
  if (((*param_1 & 1) != 0) && (puVar1 = *(undefined4 **)(param_1 + 4), puVar1 != (undefined4 *)0x0)
     ) {
    FUN_0042d750(puVar1);
    FUN_00430df0((undefined *)puVar1);
  }
  if (((*param_1 & 2) != 0) && (puVar1 = *(undefined4 **)(param_1 + 8), puVar1 != (undefined4 *)0x0)
     ) {
    FUN_0042d750(puVar1);
    FUN_00430df0((undefined *)puVar1);
  }
  FUN_00428e20((undefined4 *)param_1);
  return;
}


/* 00428e80 size=260 */

undefined4 * __fastcall FUN_00428e80(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  param_1[1] = &PTR_LAB_004cbbd4;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  FUN_00430800(param_1 + 1,0,0);
  puVar1 = param_1 + 6;
  *puVar1 = &PTR_LAB_004cbc04;
  FUN_0042f7e0((int)puVar1);
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  FUN_0043c3e0(puVar1,0);
  FUN_00468190(puVar1,0,&DAT_004ecc58);
  puVar1 = param_1 + 0xb;
  *puVar1 = &PTR_LAB_004cbc34;
  FUN_0042f7e0((int)puVar1);
  FUN_00430220(puVar1,0,0);
  puVar1 = param_1 + 0x10;
  *puVar1 = &PTR_LAB_004cbb50;
  FUN_0042f7e0((int)puVar1);
  FUN_00430170(puVar1,0,0);
  puVar1 = param_1 + 0x15;
  *puVar1 = &PTR_LAB_004cbc64;
  FUN_0042f7e0((int)puVar1);
  FUN_004308b0(puVar1,0,0);
  FUN_004a3d00(param_1 + 0x1b);
  FUN_004461c0(param_1 + 0x3f);
  param_1[0x62] = &PTR_LAB_004cbc94;
  param_1[99] = 0;
  param_1[100] = 0;
  param_1[0x65] = 0;
  param_1[0x66] = 0;
  FUN_00430220(param_1 + 0x62,0,0);
  param_1[0x67] = &PTR_LAB_004cbcc4;
  param_1[0x68] = 0;
  param_1[0x69] = 0;
  param_1[0x6a] = 0;
  param_1[0x6b] = 0;
  FUN_00430220(param_1 + 0x67,0,0);
  *param_1 = &PTR_FUN_004cc0d0;
  FUN_00428f90((int)param_1);
  return param_1;
}


/* 00428f90 size=207 */

void __fastcall FUN_00428f90(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + 0xe8;
  *(undefined4 *)(param_1 + 0x168) = 0;
  *(undefined4 *)(param_1 + 0x16c) = 0;
  *(undefined4 *)(param_1 + 0x170) = 0;
  *(undefined4 *)(param_1 + 0x174) = 0;
  *(undefined4 *)(param_1 + 0x178) = 0;
  *(undefined4 *)(param_1 + 0x17c) = 0;
  *(int *)(param_1 + 0xec) = iVar1;
  *(int *)iVar1 = iVar1;
  *(undefined4 *)(param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0xf8) = 0;
  *(undefined4 *)(param_1 + 0x144) = 0;
  *(undefined4 *)(param_1 + 0x148) = 0;
  *(undefined4 *)(param_1 + 0x14c) = 0;
  *(undefined4 *)(param_1 + 0x150) = 0;
  *(undefined4 *)(param_1 + 0x154) = 0;
  *(undefined4 *)(param_1 + 0x158) = 0;
  iVar1 = param_1 + 0x1bc;
  *(undefined4 *)(param_1 + 0x15c) = 0;
  *(undefined4 *)(param_1 + 0x160) = 0;
  *(undefined4 *)(param_1 + 0x164) = 0;
  *(undefined4 *)(param_1 + 0x180) = 0;
  *(undefined4 *)(param_1 + 0x184) = 0;
  *(undefined4 *)(param_1 + 0x1b0) = 0;
  *(undefined4 *)(param_1 + 0x1b4) = 0;
  *(undefined4 *)(param_1 + 0x1b8) = 0;
  *(int *)(param_1 + 0x1c0) = iVar1;
  *(int *)iVar1 = iVar1;
  iVar1 = param_1 + 0x1d0;
  *(undefined4 *)(param_1 + 0x1c8) = 0;
  *(undefined4 *)(param_1 + 0x1cc) = 0;
  *(int *)(param_1 + 0x1d4) = iVar1;
  *(int *)iVar1 = iVar1;
  iVar1 = param_1 + 0x1dc;
  *(int *)(param_1 + 0x1e0) = iVar1;
  *(int *)iVar1 = iVar1;
  *(undefined4 *)(param_1 + 0x1e8) = 0;
  FUN_004462d0((undefined4 *)(param_1 + 0xfc));
  return;
}


/* 00429060 size=1278 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_00429060(void *this,int *param_1)

{
  uint *puVar1;
  float *pfVar2;
  float *pfVar3;
  int *piVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  void *pvVar9;
  int iVar10;
  uint uVar11;
  undefined4 *puVar12;
  uint *puVar13;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  char cVar14;
  float **ppfVar15;
  byte *pbVar16;
  float *pfStack_8c;
  float *pfStack_88;
  undefined4 uStack_84;
  int iStack_80;
  undefined4 uStack_7c;
  int iStack_78;
  undefined4 uStack_74;
  float *pfStack_70;
  undefined4 uStack_6c;
  int iStack_68;
  undefined4 uStack_64;
  byte abStack_56 [6];
  int local_28 [10];
  
  if (*param_1 == 0) {
    return 3;
  }
  FUN_0042be60((int)this);
  piVar4 = (int *)*param_1;
  if (param_1[2] == 0) {
    param_1[2] = (int)FUN_00436e70;
  }
  uStack_64 = 0x4290af;
  iVar8 = FUN_00428780(piVar4,local_28);
  if (iVar8 == 0) {
    return 1;
  }
  *(int *)((int)this + 0x1ec) = local_28[0];
  (**(code **)(*piVar4 + 8))();
  pvVar9 = FUN_00430f00(unaff_EBP + 1);
  *(void **)((int)this + 0x1b8) = pvVar9;
  if (pvVar9 == (void *)0x0) {
    FUN_0042be60((int)this);
    return 4;
  }
  uStack_64 = 0x429120;
  (**(code **)(*piVar4 + 8))();
  uStack_64 = 4;
  *(undefined1 *)(*(int *)((int)this + 0x1b8) + unaff_EDI) = 0;
  iStack_68 = (int)this + 0xf8;
  uStack_6c = 0x42913e;
  (**(code **)(*piVar4 + 8))();
  pfVar2 = (float *)((int)this + 0x144);
  uStack_6c = 4;
  uStack_74 = 0x42914e;
  pfStack_70 = pfVar2;
  (**(code **)(*piVar4 + 8))();
  iStack_78 = (int)this + 0x148;
  uStack_74 = 4;
  uStack_7c = 0x42915b;
  (**(code **)(*piVar4 + 8))();
  iStack_80 = (int)this + 0x14c;
  uStack_7c = 4;
  uStack_84 = 0x429168;
  (**(code **)(*piVar4 + 8))();
  pfVar3 = (float *)((int)this + 0x150);
  uStack_84 = 4;
  pfStack_8c = (float *)0x429178;
  pfStack_88 = pfVar3;
  (**(code **)(*piVar4 + 8))();
  pfStack_8c = (float *)0x4;
  (**(code **)(*piVar4 + 8))((int)this + 0x154);
  iVar8 = (int)this + 0x158;
  (**(code **)(*piVar4 + 8))(iVar8,4);
  fVar5 = *(float *)((int)this + 0x148) - _DAT_004cb528;
  fVar6 = *(float *)((int)this + 0x14c) - _DAT_004cb528;
  *(float *)((int)this + 0x168) = *pfVar2 - _DAT_004cb528;
  *(float *)((int)this + 0x16c) = fVar5;
  *(float *)((int)this + 0x170) = fVar6;
  fVar5 = *(float *)((int)this + 0x154) + _DAT_004cb528;
  fVar6 = *(float *)((int)this + 0x158) + _DAT_004cb528;
  fVar7 = _DAT_004cba94 / (*pfVar3 - *pfVar2);
  *(float *)((int)this + 0x174) = *pfVar3 + _DAT_004cb528;
  *(float *)((int)this + 0x178) = fVar5;
  *(float *)((int)this + 0x17c) = fVar6;
  *(float *)((int)this + 0x15c) = fVar7;
  *(float *)((int)this + 0x160) =
       _DAT_004cba94 / (*(float *)((int)this + 0x154) - *(float *)((int)this + 0x148));
  *(float *)((int)this + 0x164) =
       _DAT_004cba94 / (*(float *)((int)this + 0x158) - *(float *)((int)this + 0x14c));
  iVar10 = FUN_004a48c0((void *)((int)this + 0x6c),piVar4);
  if (iVar10 == 0) {
    FUN_0042be60((int)this);
    return 4;
  }
  pbVar16 = (byte *)&iStack_80;
  (**(code **)(*piVar4 + 8))(pbVar16,4);
  pfVar2 = pfStack_88;
  if ((pfStack_88 != *(float **)((int)this + 400)) || (pfStack_88 == (float *)0x0)) {
    if (*(int *)((int)this + 0x18c) != 0) {
      FUN_00433560((void *)((int)this + 0x188),&DAT_004ecc58);
    }
    *(float **)((int)this + 400) = pfVar2;
    if (pfVar2 != (float *)0x0) {
      iVar10 = FUN_00456f10(&DAT_004ecc58,0,*(int *)((int)this + 0x198) + (int)pfVar2);
      *(int *)((int)this + 0x18c) = iVar10;
      if (iVar10 == 0) {
        *(undefined4 *)((int)this + 400) = 0;
        *(undefined4 *)((int)this + 0x194) = 0;
        FUN_0042be60((int)this);
        return 4;
      }
      *(undefined4 *)((int)this + 0x194) = *(undefined4 *)((int)this + 0x198);
    }
  }
  uVar11 = 0;
  if (*(int *)((int)this + 400) != 0) {
    do {
      uVar11 = uVar11 + 1;
      *(undefined4 *)(*(int *)((int)this + 0x18c) + -4 + uVar11 * 4) = 0;
    } while (uVar11 < *(uint *)((int)this + 400));
  }
  pfStack_8c = (float *)0x0;
  if (pfStack_88 != (float *)0x0) {
    do {
      puVar12 = (undefined4 *)FUN_00430de0(0x10);
      if (puVar12 == (undefined4 *)0x0) {
        puVar13 = (uint *)0x0;
        iVar10 = iVar8;
      }
      else {
        puVar13 = FUN_00428e00(puVar12);
        iVar10 = iVar8;
      }
      *(uint **)(*(int *)((int)this + 0x18c) + (int)pfStack_8c * 4) = puVar13;
      if (puVar13 == (uint *)0x0) goto LAB_004294b1;
      ppfVar15 = &pfStack_70;
      (**(code **)(*piVar4 + 8))(ppfVar15,4);
      cVar14 = (char)ppfVar15;
      puVar12 = &uStack_7c;
      (**(code **)(*piVar4 + 0x18))();
      puVar1 = puVar13 + 1;
      iVar8 = FUN_00429560(SUB41(fVar6,0),this,0,puVar1,(char)&pfStack_88,&pfStack_8c,1,puVar12,
                           cVar14);
      if (iVar8 != 0) {
LAB_0042948c:
        FUN_0042be60((int)this);
        return iVar8;
      }
      if ((*(byte *)(*puVar1 + 0x48) & 2) != 0) {
        (**(code **)(*piVar4 + 0x14))(iStack_80);
        iVar8 = FUN_00429560(SUB41(fVar6,0),this,0,puVar13 + 2,(char)&pfStack_88,&pfStack_8c,0,
                             puVar12,cVar14);
        if (iVar8 != 0) goto LAB_0042948c;
      }
      iVar8 = (**(code **)(*(int *)*puVar1 + 0x24))();
      if (iVar8 != 0) {
        *(uint *)((int)this + 0x180) = *(uint *)((int)this + 0x180) | 2;
      }
      uVar11 = puVar13[2];
      *puVar13 = *puVar13 | 3;
      if (uVar11 == 0) {
        uVar11 = *puVar1;
      }
      puVar13[3] = uVar11;
      *(short *)(*puVar1 + 0xf8) = (short)iVar10;
      if (puVar13[2] != 0) {
        *(short *)(puVar13[2] + 0xf8) = (short)iVar10;
      }
      iVar8 = iVar10;
      (**(code **)((int)fVar6 + 8))(*(undefined4 *)((int)fVar6 + 0xc));
      (**(code **)(*piVar4 + 0x14))(uStack_7c);
      pfStack_8c = (float *)(iVar10 + 1);
    } while (pfStack_8c < pfStack_88);
  }
  WorldProperties_46b5f0(*(undefined **)((int)this + 0x1b8),abStack_56 + -6,pbVar16);
  iVar8 = FUN_0042c9e0(this);
  if (iVar8 == 0) {
    FUN_0042be60((int)this);
    return 2;
  }
  FUN_0042cb00((int)this);
  iVar8 = FUN_0042c070((int)this);
  if (iVar8 != 0) {
    FUN_0042aa70((int *)((int)this + 0xfc),*(undefined **)((int)this + 0x1b8),
                 (undefined4 *)((int)this + 0x144),(int)this + 0x150,abStack_56 + -6);
    LightMapMaker_42ab00(piVar4);
    if (1 < DAT_004e4420) {
      FUN_00436670((byte *)s_World_load___d_ticks__precalcula_004d7b0c,uStack_7c);
    }
    (**(code **)(unaff_ESI + 8))(*(undefined4 *)(unaff_ESI + 0xc));
    iVar8 = (**(code **)(*piVar4 + 0x10))();
    if (iVar8 == 0) {
      *(undefined4 *)((int)this + 0x1cc) = 1;
      return 0;
    }
    FUN_0042be60((int)this);
    return 2;
  }
LAB_004294b1:
  FUN_0042be60((int)this);
  return 4;
}


/* 00429560 size=4891 */

/* WARNING: Removing unreachable block (ram,0x00429884) */
/* WARNING: Removing unreachable block (ram,0x00429be3) */

/* FUN_00429560: lifted from original x86 -> lt_lifted.c */


/* 0042a880 size=46 */

undefined * __cdecl FUN_0042a880(int param_1,int param_2,int param_3)

{
  if (param_3 == -1) {
    return PTR_DAT_004d7c44;
  }
  if (param_3 == -2) {
    return PTR_DAT_004d7c48;
  }
  if (param_3 < param_2) {
    return (undefined *)(param_1 + param_3 * 0x18);
  }
  return (undefined *)0x0;
}


/* 0042a8b0 size=95 */

void __cdecl FUN_0042a8b0(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 0x7c) != 0) {
    iVar3 = 0;
    do {
      uVar2 = uVar2 + 1;
      *(undefined2 *)(iVar3 + 0x38 + *(int *)(param_1 + 0x78)) = 0xffff;
      iVar3 = iVar3 + 0x40;
    } while (uVar2 < *(uint *)(param_1 + 0x7c));
  }
  uVar2 = 0;
  if (*(int *)(param_1 + 0xa4) != 0) {
    do {
      iVar3 = *(int *)(*(int *)(param_1 + 0xa0) + uVar2 * 4);
      iVar1 = *(int *)(iVar3 + 0x2c);
      if (iVar1 != 0) {
        *(undefined2 *)(iVar3 + 0x44) = *(undefined2 *)(iVar1 + 0x38);
        *(short *)(iVar1 + 0x38) = (short)uVar2;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_1 + 0xa4));
  }
  return;
}


/* 0042a910 size=48 */

int __cdecl FUN_0042a910(int param_1,char *param_2)

{
  int iVar1;
  
  while( true ) {
    if (param_1 == 0) {
      return 0;
    }
    iVar1 = FUN_00436e20((char *)(param_1 + 0x10),param_2);
    if (iVar1 != 0) break;
    param_1 = *(int *)(param_1 + 0xc);
  }
  return param_1;
}


/* 0042a940 size=293 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0042a940(int *param_1,int param_2,int param_3)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 != 0) {
    do {
      *(undefined1 *)((int)param_1 + 0x17) = 6;
      if (param_3 != 0) {
        iVar3 = *param_1;
        if ((iVar3 == 0) || (*(int *)(iVar3 + 0x2c) == 0)) {
          pfVar1 = (float *)0x0;
        }
        else {
          pfVar1 = *(float **)(iVar3 + 0x28);
        }
        if (*pfVar1 <= _DAT_004cc0e0) {
          if ((iVar3 == 0) || (*(int *)(iVar3 + 0x2c) == 0)) {
            pfVar1 = (float *)0x0;
          }
          else {
            pfVar1 = *(float **)(iVar3 + 0x28);
          }
          if (_DAT_004cc0dc <= *pfVar1) {
            if ((iVar3 == 0) || (*(int *)(iVar3 + 0x2c) == 0)) {
              iVar2 = 0;
            }
            else {
              iVar2 = *(int *)(iVar3 + 0x28);
            }
            if (*(float *)(iVar2 + 4) <= _DAT_004cc0e0) {
              if ((iVar3 == 0) || (*(int *)(iVar3 + 0x2c) == 0)) {
                iVar2 = 0;
              }
              else {
                iVar2 = *(int *)(iVar3 + 0x28);
              }
              if (_DAT_004cc0dc <= *(float *)(iVar2 + 4)) {
                if ((iVar3 == 0) || (*(int *)(iVar3 + 0x2c) == 0)) {
                  iVar2 = 0;
                }
                else {
                  iVar2 = *(int *)(iVar3 + 0x28);
                }
                if (*(float *)(iVar2 + 8) <= _DAT_004cc0e0) {
                  if ((iVar3 == 0) || (*(int *)(iVar3 + 0x2c) == 0)) {
                    iVar3 = 0;
                  }
                  else {
                    iVar3 = *(int *)(iVar3 + 0x28);
                  }
                  if (*(float *)(iVar3 + 8) < _DAT_004cc0dc) {
                    *(undefined1 *)((int)param_1 + 0x17) = 5;
                  }
                }
                else {
                  *(undefined1 *)((int)param_1 + 0x17) = 4;
                }
              }
              else {
                *(undefined1 *)((int)param_1 + 0x17) = 3;
              }
            }
            else {
              *(undefined1 *)((int)param_1 + 0x17) = 2;
            }
          }
          else {
            *(undefined1 *)((int)param_1 + 0x17) = 1;
          }
        }
        else {
          *(undefined1 *)((int)param_1 + 0x17) = 0;
        }
      }
      param_1 = param_1 + 6;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}


/* 0042aa70 size=141 */

void __cdecl
FUN_0042aa70(int *param_1,undefined *param_2,undefined4 *param_3,undefined4 param_4,
            undefined4 param_5)

{
  void *pvVar1;
  uint uVar2;
  float10 fVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  
  lVar4 = __ftol();
  lVar5 = __ftol();
  lVar6 = __ftol();
  param_5 = CONCAT31(CONCAT21(CONCAT11((*(uint8_t*)((char*)&param_5+3)),(char)lVar4),(char)lVar5),(char)lVar6);
  fVar3 = parse_world_info_46b720(param_2);
  FUN_004461e0(param_1,param_3,param_4,(float)fVar3);
  pvVar1 = FUN_00430f00(param_1[1] << 2);
  *param_1 = (int)pvVar1;
  if (pvVar1 != (void *)0x0) {
    uVar2 = 0;
    if (param_1[1] != 0) {
      do {
        uVar2 = uVar2 + 1;
        *(undefined4 *)(*param_1 + -4 + uVar2 * 4) = param_5;
      } while (uVar2 < (uint)param_1[1]);
    }
    DAT_004e95e8 = DAT_004e95e8 + param_1[1];
  }
  return;
}


/* 0042b7f0 size=30 */

undefined4 * __thiscall FUN_0042b7f0(void *this,byte param_1)

{
  FUN_004a3740(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0042b810 size=818 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0042b810(float *param_1,float *param_2,float param_3,int *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  longlong lVar15;
  longlong lVar16;
  longlong lVar17;
  undefined1 uStack_4d;
  int local_18 [5];
  int local_4;
  
  lVar15 = __ftol();
  local_18[0] = (int)lVar15;
  lVar15 = __ftol();
  local_18[1] = (int)lVar15;
  lVar15 = __ftol();
  local_18[2] = (int)lVar15;
  lVar15 = __ftol();
  local_18[3] = (int)lVar15;
  lVar15 = __ftol();
  local_18[4] = (int)lVar15;
  lVar15 = __ftol();
  local_4 = (int)lVar15;
  piVar9 = local_18;
  piVar14 = param_4 + 5;
  iVar12 = 3;
  do {
    iVar10 = *piVar9;
    if (iVar10 < 0) {
      iVar10 = 0;
    }
    else if (*piVar14 < iVar10) {
      iVar10 = *piVar14;
    }
    *piVar9 = iVar10;
    iVar10 = piVar9[1];
    if (iVar10 < 0) {
      iVar10 = 0;
    }
    else if (*piVar14 < iVar10) {
      iVar10 = *piVar14;
    }
    piVar9[1] = iVar10;
    if (iVar10 < *piVar9) {
      *piVar9 = iVar10;
    }
    piVar14 = piVar14 + 1;
    piVar9 = piVar9 + 2;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  iVar12 = local_18[0];
  if (local_18[0] <= local_18[1]) {
    do {
      fVar1 = (float)param_4[9];
      fVar2 = (float)param_4[0xf];
      iVar10 = local_18[2];
      if (local_18[2] <= local_18[3]) {
        do {
          fVar3 = (float)param_4[10];
          fVar4 = (float)param_4[0x10];
          iVar13 = local_18[4];
          if (local_18[4] <= local_4) {
            do {
              fVar6 = ((float)iVar13 * (float)param_4[0xb] + (float)param_4[0x11]) - param_1[2];
              fVar8 = ((float)iVar10 * fVar3 + fVar4) - param_1[1];
              fVar7 = ((float)iVar12 * fVar1 + fVar2) - *param_1;
              if (fVar6 * fVar6 + fVar8 * fVar8 + fVar7 * fVar7 < param_3 * param_3) {
                iVar5 = *param_4;
                iVar11 = param_4[2] * iVar10 + iVar12 + param_4[8] * iVar13;
                uStack_4d = (undefined1)((uint)*(undefined4 *)(iVar5 + iVar11 * 4) >> 0x18);
                lVar15 = __ftol();
                lVar16 = __ftol();
                lVar17 = __ftol();
                *(uint *)(iVar5 + iVar11 * 4) =
                     CONCAT13(uStack_4d,CONCAT12((char)lVar15,CONCAT11((char)lVar16,(char)lVar17)));
              }
              iVar13 = iVar13 + 1;
            } while (iVar13 <= local_4);
          }
          iVar10 = iVar10 + 1;
        } while (iVar10 <= local_18[3]);
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 <= local_18[1]);
  }
  return;
}


/* 0042bb50 size=769 */

undefined4 __thiscall FUN_0042bb50(void *this,uint param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint *puVar7;
  int iVar8;
  undefined4 *puVar9;
  
  uVar3 = param_1;
  FUN_0042be60((int)this);
  *(undefined4 *)((int)this + 0x1e8) = 1;
  iVar4 = FUN_004a4850((void *)((int)this + 0x6c),param_1 + 0x6c);
  if (iVar4 != 0) {
    iVar4 = FUN_00468190((void *)((int)this + 0x188),*(int *)(param_1 + 400),&DAT_004ecc58);
    if (iVar4 != 0) {
      uVar5 = 0;
      if (*(int *)((int)this + 400) != 0) {
        do {
          uVar5 = uVar5 + 1;
          *(undefined4 *)(*(int *)((int)this + 0x18c) + -4 + uVar5 * 4) = 0;
        } while (uVar5 < *(uint *)((int)this + 400));
      }
      iVar4 = FUN_00430a90((void *)((int)this + 0x19c),param_1 + 0x19c,&DAT_004ecc58);
      if (iVar4 != 0) {
        if (*(int *)((int)this + 8) != 0) {
          FUN_00433560((void *)((int)this + 4),&DAT_004ecc58);
        }
        *(undefined4 *)((int)this + 0xc) = 0;
        *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 8);
        *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
        *(undefined4 *)((int)this + 0x10) = *(undefined4 *)(param_1 + 0x10);
        *(undefined4 *)((int)this + 0x14) = *(undefined4 *)(param_1 + 0x14);
        param_1 = 0;
        if (*(int *)((int)this + 400) != 0) {
          do {
            iVar4 = *(int *)(*(int *)(uVar3 + 0x18c) + param_1 * 4);
            puVar6 = (undefined4 *)FUN_00430de0(0x10);
            if (puVar6 == (undefined4 *)0x0) goto LAB_0042be41;
            puVar7 = FUN_00428e00(puVar6);
            if (puVar7 == (uint *)0x0) goto LAB_0042be41;
            *(uint **)(*(int *)((int)this + 0x18c) + param_1 * 4) = puVar7;
            puVar7[1] = *(uint *)(iVar4 + 4);
            puVar7[2] = *(uint *)(iVar4 + 8);
            *puVar7 = *puVar7 & 0xfffffffc;
            iVar8 = (**(code **)(**(int **)(iVar4 + 4) + 0x24))();
            if (iVar8 != 0) {
              *puVar7 = *puVar7 | 1;
              puVar6 = (undefined4 *)FUN_00430de0(0x154);
              if (puVar6 == (undefined4 *)0x0) {
                puVar6 = (undefined4 *)0x0;
              }
              else {
                puVar6 = FUN_0042d650(puVar6);
              }
              puVar7[1] = (uint)puVar6;
              if (puVar6 == (undefined4 *)0x0) goto LAB_0042be41;
              iVar4 = FUN_0042dad0(puVar6,*(int *)(iVar4 + 4));
              if (iVar4 == 0) goto LAB_0042be41;
            }
            uVar5 = puVar7[2];
            if (uVar5 == 0) {
              uVar5 = puVar7[1];
            }
            puVar7[3] = uVar5;
            param_1 = param_1 + 1;
          } while (param_1 < *(uint *)((int)this + 400));
        }
        *(undefined4 *)((int)this + 0x68) = *(undefined4 *)(uVar3 + 0x68);
        *(undefined4 *)((int)this + 0x168) = *(undefined4 *)(uVar3 + 0x168);
        *(undefined4 *)((int)this + 0x16c) = *(undefined4 *)(uVar3 + 0x16c);
        *(undefined4 *)((int)this + 0x170) = *(undefined4 *)(uVar3 + 0x170);
        *(undefined4 *)((int)this + 0x174) = *(undefined4 *)(uVar3 + 0x174);
        *(undefined4 *)((int)this + 0x178) = *(undefined4 *)(uVar3 + 0x178);
        *(undefined4 *)((int)this + 0x17c) = *(undefined4 *)(uVar3 + 0x17c);
        *(undefined4 *)((int)this + 0xe8) = *(undefined4 *)(uVar3 + 0xe8);
        *(undefined4 *)((int)this + 0xec) = *(undefined4 *)(uVar3 + 0xec);
        *(undefined4 *)((int)this + 0xf0) = *(undefined4 *)(uVar3 + 0xf0);
        *(undefined4 *)((int)this + 0xf4) = *(undefined4 *)(uVar3 + 0xf4);
        *(undefined4 *)((int)this + 0xf8) = *(undefined4 *)(uVar3 + 0xf8);
        puVar6 = (undefined4 *)(uVar3 + 0xfc);
        puVar9 = (undefined4 *)((int)this + 0xfc);
        for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar9 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar9 = puVar9 + 1;
        }
        *(undefined4 *)((int)this + 0x144) = *(undefined4 *)(uVar3 + 0x144);
        *(undefined4 *)((int)this + 0x148) = *(undefined4 *)(uVar3 + 0x148);
        *(undefined4 *)((int)this + 0x14c) = *(undefined4 *)(uVar3 + 0x14c);
        *(undefined4 *)((int)this + 0x150) = *(undefined4 *)(uVar3 + 0x150);
        *(undefined4 *)((int)this + 0x154) = *(undefined4 *)(uVar3 + 0x154);
        *(undefined4 *)((int)this + 0x158) = *(undefined4 *)(uVar3 + 0x158);
        *(undefined4 *)((int)this + 0x15c) = *(undefined4 *)(uVar3 + 0x15c);
        *(undefined4 *)((int)this + 0x160) = *(undefined4 *)(uVar3 + 0x160);
        *(undefined4 *)((int)this + 0x164) = *(undefined4 *)(uVar3 + 0x164);
        *(undefined4 *)((int)this + 0x180) = *(undefined4 *)(uVar3 + 0x180);
        *(undefined4 *)((int)this + 0x1b0) = *(undefined4 *)(uVar3 + 0x1b0);
        *(undefined4 *)((int)this + 0x1b4) = *(undefined4 *)(uVar3 + 0x1b4);
        *(undefined4 *)((int)this + 0x1b8) = *(undefined4 *)(uVar3 + 0x1b8);
        *(undefined4 *)((int)this + 0x184) = *(undefined4 *)(uVar3 + 0x184);
        *(undefined4 *)((int)this + 0x1ec) = *(undefined4 *)(uVar3 + 0x1ec);
        FUN_0042c190(this,(int)(uVar3 + 0xe8));
        piVar1 = (int *)((int)this + 0x1dc);
        *piVar1 = uVar3 + 0x1d0;
        piVar2 = *(int **)(uVar3 + 0x1d4);
        *(int **)((int)this + 0x1e0) = piVar2;
        *piVar2 = (int)piVar1;
        *(int **)(*piVar1 + 4) = piVar1;
        *(undefined4 *)((int)this + 0x1cc) = 1;
        return 1;
      }
    }
  }
LAB_0042be41:
  FUN_0042be60((int)this);
  return 0;
}


/* 0042be60 size=487 */

void __fastcall FUN_0042be60(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  
  FUN_004a3d60(param_1 + 0x6c);
  iVar3 = *(int *)(param_1 + 0x1d4);
  while (iVar3 != param_1 + 0x1d0) {
    piVar1 = (int *)(iVar3 + 8);
    iVar3 = *(int *)(iVar3 + 4);
    FUN_0042be60(*piVar1);
  }
  puVar2 = (undefined4 *)(param_1 + 0x1dc);
  *(undefined4 *)(*(int *)(param_1 + 0x1dc) + 4) = *(undefined4 *)(param_1 + 0x1e0);
  **(undefined4 **)(param_1 + 0x1e0) = *puVar2;
  *(undefined4 **)(param_1 + 0x1e0) = puVar2;
  *puVar2 = puVar2;
  if (*(int *)(param_1 + 0x1e8) == 0) {
    if (*(int *)(param_1 + 8) != 0) {
      FUN_00456e60(&DAT_004ecc58,*(int *)(param_1 + 8));
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined4 *)(param_1 + 0x10) = 0;
    }
    *(undefined4 *)(param_1 + 0xc) = 0;
    FUN_0042c050(param_1);
    iVar3 = *(int *)(param_1 + 0xec);
    while (iVar3 != param_1 + 0xe8) {
      iVar5 = *(int *)(iVar3 + 4);
      piVar1 = (int *)(iVar3 + 8);
      iVar3 = iVar5;
      if ((undefined4 *)*piVar1 != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)*piVar1)(1);
      }
    }
    uVar6 = 0;
    FUN_00430fe0(*(undefined **)(param_1 + 0x1b8));
    FUN_004288d0(param_1);
    FUN_00446310((undefined4 *)(param_1 + 0xfc));
    if (*(undefined **)(param_1 + 0x1b0) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)(param_1 + 0x1b0));
    }
    if (*(int *)(param_1 + 400) != 0) {
      do {
        pbVar4 = *(byte **)(*(int *)(param_1 + 0x18c) + uVar6 * 4);
        if (pbVar4 != (byte *)0x0) {
          thunk_FUN_00428e30(pbVar4);
          (**(code **)(DAT_004ecc58 + 8))(pbVar4);
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < *(uint *)(param_1 + 400));
    }
    if (*(int *)(param_1 + 0x18c) != 0) {
      FUN_00433560((void *)(param_1 + 0x188),&DAT_004ecc58);
    }
    *(undefined4 *)(param_1 + 400) = 0;
    FUN_00428f90(param_1);
    return;
  }
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  uVar6 = 0;
  if (*(int *)(param_1 + 400) != 0) {
    do {
      pbVar4 = *(byte **)(*(int *)(param_1 + 0x18c) + uVar6 * 4);
      if (pbVar4 != (byte *)0x0) {
        if ((*pbVar4 & 1) != 0) {
          FUN_0042dab0(*(int *)(pbVar4 + 4));
        }
        FUN_00428e20((undefined4 *)pbVar4);
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(param_1 + 400));
  }
  uVar6 = 0;
  if (*(int *)(param_1 + 400) != 0) {
    do {
      pbVar4 = *(byte **)(*(int *)(param_1 + 0x18c) + uVar6 * 4);
      if (pbVar4 != (byte *)0x0) {
        thunk_FUN_00428e30(pbVar4);
        (**(code **)(DAT_004ecc58 + 8))(pbVar4);
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(param_1 + 400));
  }
  FUN_00468190((void *)(param_1 + 0x188),0,&DAT_004ecc58);
  FUN_00428f90(param_1);
  return;
}


