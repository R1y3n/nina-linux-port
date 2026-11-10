/* lithtech.exe decompilation - unnamed_00470000 */
#include "ghidra_types.h"

/* 004701b0 size=300 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_004701b0(int param_1,int *param_2,float *param_3,int param_4,int param_5)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  float fVar4;
  undefined4 uVar5;
  
  piVar2 = *(int **)(*(int *)(param_1 + 0x78) + 0x620);
  fVar4 = *(float *)(param_1 + 0x28) - (float)param_2[0x59];
  param_2[0x59] = *(int *)(param_1 + 0x28);
  param_2[0x5a] = (int)*param_3;
  param_2[0x5b] = (int)param_3[1];
  param_2[0x5c] = (int)param_3[2];
  param_2[0x5d] = (int)param_3[3];
  if (DAT_004e98e8 == 0) {
    if ((param_4 == 0) && (param_5 == 0)) {
      uVar5 = 0;
      goto LAB_004702b2;
    }
  }
  else {
    if (((param_4 == 0) && (param_5 == 0)) && (fVar4 != _DAT_004cb524)) {
      piVar2 = param_2 + 0x5e;
      *(int *)(param_2[0x5e] + 4) = param_2[0x5f];
      *(int *)param_2[0x5f] = *piVar2;
      param_2[0x5f] = (int)piVar2;
      *piVar2 = (int)piVar2;
      *piVar2 = param_1 + 0x50;
      puVar3 = *(undefined4 **)(param_1 + 0x54);
      param_2[0x5f] = (int)puVar3;
      *puVar3 = piVar2;
      *(int **)(*piVar2 + 4) = piVar2;
      param_2[0x58] = (int)(fVar4 + fVar4);
      return;
    }
    piVar1 = param_2 + 0x5e;
    *(int *)(param_2[0x5e] + 4) = param_2[0x5f];
    *(int *)param_2[0x5f] = *piVar1;
    param_2[0x5f] = (int)piVar1;
    *piVar1 = (int)piVar1;
    param_2[0x5f] = (int)piVar1;
    *piVar1 = (int)piVar1;
    uVar5 = 0;
    param_2[0x58] = 0;
    if ((param_4 == 0) && (param_5 == 0)) goto LAB_004702b2;
  }
  uVar5 = 1;
LAB_004702b2:
  (**(code **)(*piVar2 + 0x48))(param_2,uVar5,param_3);
  FUN_004273f0(*(int *)(param_1 + 0x78),param_2,param_3);
  return;
}


/* 004702e0 size=1241 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004702e0: lifted from original x86 -> lt_lifted.c */


/* 004707c0 size=827 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004707c0: lifted from original x86 -> lt_lifted.c */


/* 00470b30 size=62 */

void __cdecl FUN_00470b30(int *param_1,int param_2)

{
  (**(code **)(*param_1 + 8))(param_2,4);
  (**(code **)(*param_1 + 8))(param_2 + 4,4);
  (**(code **)(*param_1 + 8))(param_2 + 8,4);
  (**(code **)(*param_1 + 8))(param_2 + 0xc,4);
  return;
}


/* 00470b70 size=23 */

void __fastcall FUN_00470b70(undefined4 *param_1)

{
  param_1[1] = 0x38d1b717;
  param_1[2] = 0x40000000;
  *param_1 = 0;
  return;
}


/* 00470b90 size=49 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00470b90(void *this,float param_1)

{
  float fVar1;
  
  fVar1 = param_1 + *(float *)((int)this + 4);
  *(float *)((int)this + 4) = fVar1;
  if ((*(float *)((int)this + 8) != _DAT_004cb524) && (*(float *)((int)this + 8) < fVar1)) {
    FUN_00470bd0(this);
    return;
  }
  return;
}


/* 00470bd0 size=21 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00470bd0(float *param_1)

{
  float fVar1;
  
  fVar1 = param_1[1];
  param_1[1] = 0.1;
  *param_1 = (*param_1 / fVar1) * _DAT_004cbeec;
  return;
}


/* 00470c20 size=100 */

void __cdecl FUN_00470c20(undefined *param_1)

{
  int *piVar1;
  
  DAT_004ea82c = DAT_004ea82c - *(int *)(param_1 + 0xb8);
  piVar1 = (int *)(param_1 + 0xac);
  *(undefined4 *)(*(int *)(param_1 + 0xc0) + 8) = 0;
  *(undefined4 *)(*piVar1 + 4) = *(undefined4 *)(param_1 + 0xb0);
  **(int **)(param_1 + 0xb0) = *piVar1;
  *(int **)(param_1 + 0xb0) = piVar1;
  *piVar1 = (int)piVar1;
  DAT_004ea830 = DAT_004ea830 + -1;
  FUN_00430fe0(*(undefined **)(param_1 + 200));
  FUN_00430fe0(param_1);
  return;
}


/* 00470ef0 size=112 */

int * __cdecl FUN_00470ef0(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined2 extraout_var;
  float fStack_28;
  float local_1c [7];
  
  iVar1 = DAT_004e447c;
  fStack_28 = 1.4013e-45;
  iVar2 = (**(code **)(**(int **)(*(int *)(DAT_004e447c + 0x4c4) + 8) + 0x18))(param_2,local_1c);
  if (iVar2 != 0) {
    return (int *)0x0;
  }
  piVar3 = (int *)FUN_00427090(iVar1,CONCAT22(extraout_var,*(undefined2 *)(param_2 + 0x1e)));
  if (piVar3 == (int *)0x0) {
    return (int *)0x0;
  }
  FUN_00427310(iVar1,piVar3,&fStack_28,0);
  FUN_004273f0(iVar1,piVar3,local_1c);
  return piVar3;
}


/* 00470f80 size=297 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00470f80(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = 0x56;
  if (param_1 == 0) {
    iVar2 = 0x42;
  }
  fVar1 = (float)_DAT_004cd0d8;
  puVar3 = &DAT_004eaa58;
  for (; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  DAT_004eab90 = 0;
  DAT_004eaa58 = FUN_00470ef0;
  DAT_004eaa5c = &LAB_004710b0;
  _DAT_004eaa60 = &LAB_004710e0;
  _DAT_004eaa64 = &LAB_00471100;
  _DAT_004eaa68 = &LAB_00471120;
  _DAT_004eaa6c = &LAB_00471140;
  _DAT_004eaa70 = &LAB_00471180;
  _DAT_004eaa74 = &LAB_004711a0;
  _DAT_004eaa78 = &LAB_004711c0;
  _DAT_004eaa7c = FUN_00436e70;
  _DAT_004eaa80 = &LAB_004711f0;
  _DAT_004eaa84 = &LAB_004711d0;
  _DAT_004eaa88 = &LAB_00471210;
  _DAT_004eaa8c = &LAB_00471220;
  _DAT_004eaa90 = &LAB_00471230;
  DAT_004eab94 = -2.0;
  DAT_004eab98 = -1.0;
  if (SQRT(fVar1) == _DAT_004cb524) {
    DAT_004eaba8 = 0;
    DAT_004eabac = 0;
    return;
  }
  fVar1 = _DAT_004cba94 / SQRT(fVar1);
  DAT_004eab90 = 0;
  DAT_004eaba8 = 0;
  DAT_004eabac = 0;
  DAT_004eab94 = fVar1 * _DAT_004cbed4;
  DAT_004eab98 = fVar1 * _DAT_004cbf1c;
  return;
}


/* 00471620 size=27 */

void __cdecl FUN_00471620(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + 3;
  param_1[4] = puVar1;
  *puVar1 = puVar1;
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = param_2;
  return;
}


/* 00471640 size=269 */

/* FUN_00471640: lifted from original x86 -> lt_lifted.c */


/* 00471750 size=29 */

/* FUN_00471750: lifted from original x86 -> lt_lifted.c */


/* 00471770 size=55 */

/* FUN_00471770: lifted from original x86 -> lt_lifted.c */


/* 004717e0 size=130 */

undefined4 __cdecl FUN_004717e0(int param_1,int param_2,uint param_3)

{
  int *local_4;
  
  FUN_0046b170(&local_4,0x44c,0x44c);
  FUN_00471870(param_1,param_2,param_3,(int *)&local_4,2,0);
  FUN_00471870(param_1,param_2,param_3,(int *)&local_4,4,1);
  FUN_00471870(param_1,param_2,param_3,(int *)&local_4,3,2);
  FUN_00471870(param_1,param_2,param_3,(int *)&local_4,5,3);
  if (local_4 != (int *)0x0) {
    (**(code **)(*local_4 + 8))();
  }
  return 0;
}


/* 00471870 size=422 */

undefined4 __cdecl
FUN_00471870(int param_1,int param_2,uint param_3,int *param_4,undefined4 param_5,short param_6)

{
  int *piVar1;
  bool bVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  
  piVar3 = param_4;
  bVar2 = true;
  uVar5 = param_3;
  if (param_3 < *(uint *)(param_1 + 0xb30)) {
    do {
      if (*(short *)(*(int *)(param_1 + 0xb2c) + uVar5 * 4) == param_6) {
        if (bVar2) {
          FUN_004183a0((void *)*piVar3,(char)param_5);
          bVar2 = false;
        }
        FUN_004385b0((void *)*piVar3,*(undefined2 *)(*(int *)(param_1 + 0xb2c) + 2 + uVar5 * 4));
        piVar1 = (int *)*piVar3;
        iVar4 = ((uint)*(ushort *)((int)piVar1 + 0x36) - (uint)*(ushort *)(piVar1 + 0xe)) + -7;
        if ((iVar4 < 0) || (iVar4 < 0x32)) {
          FUN_00477830(param_1,param_2,0x15,piVar1,0,0x80);
          iVar4 = *piVar3;
          *(undefined2 *)(iVar4 + 0x38) = 1;
          *(undefined2 *)(iVar4 + 0x34) = 1;
          iVar4 = *piVar3;
          if (*(ushort *)(iVar4 + 0x38) + 1 < (uint)*(ushort *)(iVar4 + 0x36)) {
            if (*(uint *)(iVar4 + 0x58) <= *(ushort *)(iVar4 + 0x34) + 1) {
              do {
                param_3 = param_3 & 0xffffff00;
                FUN_00414b10((void *)(iVar4 + 0x50),*(undefined1 **)(iVar4 + 0x58),
                             (undefined1 *)&param_3,&DAT_004ecc58);
              } while (*(uint *)(iVar4 + 0x58) <= *(ushort *)(iVar4 + 0x34) + 1);
            }
            *(undefined1 *)(*(int *)(iVar4 + 0x54) + (uint)*(ushort *)(iVar4 + 0x38)) =
                 (undefined1)param_5;
            *(short *)(iVar4 + 0x38) = *(short *)(iVar4 + 0x38) + 1;
            *(short *)(iVar4 + 0x34) = *(short *)(iVar4 + 0x34) + 1;
          }
          else {
            FUN_004356e0();
            if (0 < DAT_004e4420) {
              FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                           s_CPacket__WriteType_004d5cf0);
            }
            *(uint *)(iVar4 + 0x40) = *(uint *)(iVar4 + 0x40) | 4;
          }
        }
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(param_1 + 0xb30));
    if (!bVar2) {
      FUN_00477830(param_1,param_2,0x15,(int *)*piVar3,0,0x80);
      iVar4 = *piVar3;
      *(undefined2 *)(iVar4 + 0x38) = 1;
      *(undefined2 *)(iVar4 + 0x34) = 1;
    }
  }
  return 0;
}


/* 00471a20 size=849 */

void __cdecl
FUN_00471a20(undefined4 param_1,uint param_2,undefined4 param_3,void *param_4,uint param_5)

{
  uint uVar1;
  void *this;
  uint uVar2;
  longlong lVar3;
  
  this = param_4;
  uVar1 = param_2;
  if (*(int *)(param_2 + 0x20) == 0) {
    param_5 = param_5 & 0xffffffc7;
  }
  uVar2 = param_5;
  FUN_004385b0(param_4,(short)param_3);
  FUN_004183a0(this,(char)uVar2);
  if ((uVar2 & 1) != 0) {
    FUN_004385b0(this,*(undefined2 *)(uVar1 + 0x34));
    FUN_004385b0(this,*(undefined2 *)(uVar1 + 0x38));
  }
  if ((uVar2 & 2) != 0) {
    FUN_004183a0(this,*(undefined1 *)(uVar1 + 0x3c));
  }
  if ((uVar2 & 4) != 0) {
    lVar3 = __ftol();
    FUN_004183a0(this,(char)lVar3);
  }
  if ((uVar2 & 8) != 0) {
    FUN_0043f380((int *)((int)this + 8));
  }
  if ((uVar2 & 0x10) != 0) {
    lVar3 = __ftol();
    if (*(ushort *)((int)this + 0x38) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
      if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1) {
        do {
          param_2 = param_2 & 0xffffff00;
          FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                       (undefined1 *)&param_2,&DAT_004ecc58);
        } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1);
      }
      *(char *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = (char)lVar3;
      *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 1;
      *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 1;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
    }
    lVar3 = __ftol();
    if (*(ushort *)((int)this + 0x38) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
      if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1) {
        do {
          param_2 = param_2 & 0xffffff00;
          FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                       (undefined1 *)&param_2,&DAT_004ecc58);
        } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1);
      }
      *(char *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = (char)lVar3;
      *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 1;
      *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 1;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
    }
    lVar3 = __ftol();
    if (*(ushort *)((int)this + 0x38) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
      if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1) {
        do {
          param_2 = param_2 & 0xffffff00;
          FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                       (undefined1 *)&param_2,&DAT_004ecc58);
        } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1);
      }
      *(char *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = (char)lVar3;
      *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 1;
      *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 1;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
    }
    uVar2 = param_5;
  }
  if ((uVar2 & 0x20) != 0) {
    param_2 = *(uint *)(uVar1 + 0x5c);
    if (*(ushort *)((int)this + 0x38) + 4 < (uint)*(ushort *)((int)this + 0x36)) {
      if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4) {
        do {
          param_5 = param_5 & 0xffffff00;
          FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                       (undefined1 *)&param_5,&DAT_004ecc58);
        } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4);
      }
      *(uint *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = param_2;
      *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 4;
      *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 4;
      return;
    }
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
  }
  return;
}


/* 00471d80 size=239 */

void __cdecl FUN_00471d80(int param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int *local_4;
  
  puVar2 = FUN_0046b170(&local_4,0x44c,0x44c);
  piVar1 = (int *)*puVar2;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))();
  }
  if (local_4 != (int *)0x0) {
    (**(code **)(*local_4 + 8))();
  }
  uVar4 = 0;
  if (*(int *)(param_1 + 0x1b0) != 0) {
    iVar5 = 0;
    do {
      FUN_00471a20(param_1,iVar5 + *(int *)(param_1 + 0x1ac),uVar4,piVar1,0xff);
      iVar3 = ((uint)*(ushort *)((int)piVar1 + 0x36) - (uint)*(ushort *)(piVar1 + 0xe)) + -7;
      if ((iVar3 < 0) || (iVar3 < 0x17)) {
        FUN_00477830(param_1,param_2,0x19,piVar1,0,0x80);
        *(undefined2 *)(piVar1 + 0xe) = 1;
        *(undefined2 *)(piVar1 + 0xd) = 1;
      }
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0x60;
    } while (uVar4 < *(uint *)(param_1 + 0x1b0));
  }
  if (0 < (int)(*(ushort *)(piVar1 + 0xd) - 1)) {
    FUN_00477830(param_1,param_2,0x19,piVar1,0,0x80);
    *(undefined2 *)(piVar1 + 0xe) = 1;
    *(undefined2 *)(piVar1 + 0xd) = 1;
  }
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))();
  }
  return;
}


/* 00471e70 size=286 */

void __cdecl FUN_00471e70(uint param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  ushort *puVar6;
  int *local_4;
  
  uVar2 = param_1;
  puVar3 = FUN_0046b170(&local_4,0x44c,0x44c);
  piVar1 = (int *)*puVar3;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))();
  }
  if (local_4 != (int *)0x0) {
    (**(code **)(*local_4 + 8))();
  }
  param_1 = 0;
  if (*(int *)(param_2 + 0x10c) != 0) {
    puVar6 = (ushort *)(param_2 + 0xc);
    do {
      uVar4 = (uint)*puVar6;
      if (uVar4 < *(uint *)(uVar2 + 0x1b0)) {
        FUN_00471a20(uVar2,uVar4 * 0x60 + *(int *)(uVar2 + 0x1ac),uVar4,piVar1,(uint)puVar6[1]);
        iVar5 = ((uint)*(ushort *)((int)piVar1 + 0x36) - (uint)*(ushort *)(piVar1 + 0xe)) + -7;
        if ((iVar5 < 0) || (iVar5 < 0x17)) {
          FUN_00477830(uVar2,param_2,0x19,piVar1,0,0x80);
          *(undefined2 *)(piVar1 + 0xe) = 1;
          *(undefined2 *)(piVar1 + 0xd) = 1;
        }
      }
      param_1 = param_1 + 1;
      puVar6 = puVar6 + 2;
    } while (param_1 < *(uint *)(param_2 + 0x10c));
  }
  if (0 < (int)(*(ushort *)(piVar1 + 0xd) - 1)) {
    FUN_00477830(uVar2,param_2,0x19,piVar1,0,0x80);
    *(undefined2 *)(piVar1 + 0xe) = 1;
    *(undefined2 *)(piVar1 + 0xd) = 1;
  }
  *(undefined4 *)(param_2 + 0x10c) = 0;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))();
  }
  return;
}


/* 00472370 size=604 */

undefined4 __cdecl FUN_00472370(int param_1,uint param_2)

{
  int *this;
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  int iStack_8;
  int *local_4;
  
  puVar2 = FUN_0046b170(&local_4,0x44c,0x44c);
  this = (int *)*puVar2;
  if (this != (int *)0x0) {
    (**(code **)(*this + 4))();
  }
  if (local_4 != (int *)0x0) {
    (**(code **)(*local_4 + 8))();
  }
  FUN_004183a0(this,0);
  uVar1 = param_2;
  FUN_00477830(param_1,param_2,0x15,this,0,0x80);
  *(undefined2 *)(this + 0xe) = 1;
  *(undefined2 *)(this + 0xd) = 1;
  FUN_004717e0(param_1,uVar1,0);
  FUN_004183a0(this,2);
  iStack_8 = FUN_00434ff0(*(int *)(param_1 + 0xb28));
  while (iStack_8 != 0) {
    iVar3 = FUN_00435040(&iStack_8);
    iVar3 = FUN_00434fd0(iVar3);
    FUN_004385b0(this,*(undefined2 *)(iVar3 + 0x1c));
    iVar3 = FUN_004725d0((int)this);
    if (iVar3 < 0x32) {
      FUN_00477830(param_1,uVar1,0x15,this,0,0x80);
      *(undefined2 *)(this + 0xe) = 1;
      *(undefined2 *)(this + 0xd) = 1;
      FUN_004183a0(this,2);
    }
  }
  FUN_00477830(param_1,uVar1,0x15,this,0,0x80);
  *(undefined2 *)(this + 0xe) = 1;
  *(undefined2 *)(this + 0xd) = 1;
  FUN_004183a0(this,5);
  uVar4 = *(uint *)(param_1 + 0x4c);
  if (uVar4 != param_1 + 0x48U) {
    while( true ) {
      iVar3 = *(int *)(uVar4 + 8);
      param_2 = *(uint *)(uVar4 + 4);
      if (iVar3 != 0) {
        if ((*(int *)(iVar3 + 0x18) != 0) && (*(int *)(iVar3 + 0xc) != 0)) {
          FUN_004385b0(this,*(undefined2 *)(*(int *)(iVar3 + 0xc) + 8));
        }
        iVar3 = ((uint)*(ushort *)((int)this + 0x36) - (uint)*(ushort *)(this + 0xe)) + -7;
        if ((iVar3 < 0) || (iVar3 < 0x32)) {
          FUN_00477830(param_1,uVar1,0x15,this,0,0x80);
          *(undefined2 *)(this + 0xe) = 1;
          *(undefined2 *)(this + 0xd) = 1;
          FUN_004183a0(this,5);
        }
      }
      if (param_2 == param_1 + 0x48U) break;
      uVar4 = param_2;
    }
  }
  FUN_00477830(param_1,uVar1,0x15,this,0,0x80);
  *(undefined2 *)(this + 0xe) = 1;
  *(undefined2 *)(this + 0xd) = 1;
  if (*(ushort *)((int)this + 0x36) < 3) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    this[0x10] = this[0x10] | 4;
  }
  else {
    if ((uint)this[0x16] < 3) {
      do {
        param_2 = param_2 & 0xffffff00;
        FUN_00414b10(this + 0x14,(undefined1 *)this[0x16],(undefined1 *)&param_2,&DAT_004ecc58);
      } while ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 1);
    }
    *(undefined1 *)(this[0x15] + (uint)*(ushort *)(this + 0xe)) = 1;
    *(short *)(this + 0xe) = (short)this[0xe] + 1;
    *(short *)(this + 0xd) = (short)this[0xd] + 1;
  }
  FUN_00477830(param_1,uVar1,0x15,this,0,0x80);
  if (this != (int *)0x0) {
    (**(code **)(*this + 8))();
  }
  return 0;
}


/* 004725d0 size=24 */

int __fastcall FUN_004725d0(int param_1)

{
  int iVar1;
  
  iVar1 = ((uint)*(ushort *)(param_1 + 0x36) - (uint)*(ushort *)(param_1 + 0x38)) + -7;
  if (iVar1 < 0) {
    iVar1 = 0;
  }
  return iVar1;
}


/* 00472ca0 size=22 */

void __thiscall FUN_00472ca0(void *this,int *param_1)

{
  undefined4 *puVar1;
  
  *param_1 = (int)this;
  puVar1 = *(undefined4 **)((int)this + 4);
  param_1[1] = (int)puVar1;
  *puVar1 = param_1;
  *(int **)(*param_1 + 4) = param_1;
  return;
}


/* 00472cc0 size=36 */

void __fastcall FUN_00472cc0(int *param_1)

{
  if ((int *)*param_1 != (int *)0x0) {
    (**(code **)(*(int *)*param_1 + 8))();
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}


/* 00472cf0 size=9 */

void __fastcall FUN_00472cf0(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}


/* 00472d40 size=35 */

void __cdecl FUN_00472d40(undefined2 *param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00475170((int)param_1,param_2);
  if (piVar1 != (int *)0x0) {
    s_client_4730b0(param_1,piVar1);
  }
  return;
}


/* 00472d70 size=404 */

undefined4 __cdecl FUN_00472d70(int param_1,int *param_2,int *param_3)

{
  int *piVar1;
  undefined2 uVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  undefined4 *puVar7;
  
  piVar6 = param_3;
  piVar5 = param_2;
  if (param_2 == param_3) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_AttachClient_004db858);
    }
    return 0x3c;
  }
  puVar7 = FUN_0046b170(&param_3,0x44c,0x44c);
  piVar3 = (int *)*puVar7;
  if (piVar3 != (int *)0x0) {
    (**(code **)(*piVar3 + 4))();
  }
  if (param_3 != (int *)0x0) {
    (**(code **)(*param_3 + 8))();
  }
  FUN_00472f10(param_1,(uint)piVar6);
  piVar1 = piVar6 + 0x59;
  piVar6[0x5c] = (int)piVar5;
  *piVar1 = (int)(piVar5 + 0x60);
  piVar4 = (int *)piVar5[0x61];
  piVar6[0x5a] = (int)piVar4;
  *piVar4 = (int)piVar1;
  *(int **)(*piVar1 + 4) = piVar1;
  if (piVar5[0xeb] != 0) {
    *(undefined2 *)(piVar3 + 0xe) = 1;
    *(undefined2 *)(piVar3 + 0xd) = 1;
    uVar2 = *(undefined2 *)(piVar5[0xeb] + 0xb8);
    if (*(ushort *)((int)piVar3 + 0x36) < 4) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      piVar3[0x10] = piVar3[0x10] | 4;
    }
    else {
      if ((uint)piVar3[0x16] < 4) {
        do {
          param_2 = (int *)((uint)param_2 & 0xffffff00);
          FUN_00414b10(piVar3 + 0x14,(undefined1 *)piVar3[0x16],(undefined1 *)&param_2,&DAT_004ecc58
                      );
        } while ((uint)piVar3[0x16] <= *(ushort *)(piVar3 + 0xd) + 2);
      }
      *(undefined2 *)(piVar3[0x15] + (uint)*(ushort *)(piVar3 + 0xe)) = uVar2;
      *(short *)(piVar3 + 0xe) = (short)piVar3[0xe] + 2;
      *(short *)(piVar3 + 0xd) = (short)piVar3[0xd] + 2;
    }
    FUN_00477830(param_1,(int)piVar6,7,piVar3,1,0x80);
  }
  if (piVar3 != (int *)0x0) {
    (**(code **)(*piVar3 + 8))();
  }
  return 0;
}


/* 00472f10 size=349 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_00472f10(int param_1,uint param_2)

{
  undefined4 *puVar1;
  undefined2 uVar2;
  uint uVar3;
  
  uVar3 = param_2;
  if (*(int *)(param_2 + 0x170) != 0) {
    puVar1 = (undefined4 *)(param_2 + 0x164);
    *(undefined4 *)(*(int *)(param_2 + 0x164) + 4) = *(undefined4 *)(param_2 + 0x168);
    **(undefined4 **)(param_2 + 0x168) = *puVar1;
    *(undefined4 **)(param_2 + 0x168) = puVar1;
    *puVar1 = puVar1;
    *(undefined4 *)(param_2 + 0x170) = 0;
    if (*(int *)(param_2 + 0x3ac) != 0) {
      uVar2 = *(undefined2 *)(*(int *)(param_2 + 0x3ac) + 0xb8);
      _DAT_00000038 = 1;
      _DAT_00000034 = 1;
      if (_DAT_00000036 < 4) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
        }
        _DAT_00000040 = _DAT_00000040 | 4;
      }
      else {
        if (_DAT_00000058 < (undefined1 *)0x4) {
          do {
            param_2 = param_2 & 0xffffff00;
            FUN_00414b10((void *)0x50,_DAT_00000058,(undefined1 *)&param_2,&DAT_004ecc58);
          } while (_DAT_00000058 <= (undefined1 *)(_DAT_00000034 + 2));
        }
        *(undefined2 *)((uint)_DAT_00000038 + _DAT_00000054) = uVar2;
        _DAT_00000038 = _DAT_00000038 + 2;
        _DAT_00000034 = _DAT_00000034 + 2;
      }
      FUN_00477830(param_1,uVar3,7,(int *)0x0,1,0x80);
      return 0;
    }
  }
  return 0;
}


/* 00473070 size=59 */

undefined4 __cdecl FUN_00473070(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 0x184);
  if (iVar2 == param_2 + 0x180) {
    return 0;
  }
  do {
    iVar1 = *(int *)(iVar2 + 4);
    FUN_00472f10(param_1,*(uint *)(iVar2 + 8));
    iVar2 = iVar1;
  } while (iVar1 != param_2 + 0x180);
  return 0;
}


/* 004731b0 size=261 */

void __cdecl FUN_004731b0(undefined4 param_1,undefined *param_2)

{
  int *piVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined *puVar5;
  
  puVar2 = param_2;
  FUN_004387e0(*(int **)(param_2 + 0x18c));
  puVar5 = *(undefined **)(puVar2 + 0x3d4);
  while (puVar5 != puVar2 + 0x3d0) {
    puVar4 = (undefined4 *)(puVar5 + 8);
    puVar5 = *(undefined **)(puVar5 + 4);
    FUN_00485220((undefined4 *)*puVar4);
  }
  FUN_00430fe0(*(undefined **)(puVar2 + 400));
  FUN_00430fe0(*(undefined **)(puVar2 + 0x198));
  FUN_00430fe0(*(undefined **)(puVar2 + 0x1a0));
  FUN_00430fe0(*(undefined **)(puVar2 + 0x3c4));
  param_2 = (undefined *)FUN_00434ff0(*(int *)(puVar2 + 0x3dc));
  while (param_2 != (undefined *)0x0) {
    iVar3 = FUN_00435040((int *)&param_2);
    if (((iVar3 != 0) &&
        (puVar4 = (undefined4 *)FUN_00434fd0(iVar3), iVar3 = DAT_004ebfa4,
        puVar4 != (undefined4 *)0x0)) && (DAT_004ebfa4 != -0xaac)) {
      *puVar4 = *(undefined4 *)(DAT_004ebfa4 + 0xac4);
      *(undefined4 **)(iVar3 + 0xac4) = puVar4;
    }
  }
  FUN_00434d00(*(int **)(puVar2 + 0x3dc));
  FUN_00430df0(*(undefined **)(puVar2 + 0x110));
  if (puVar2 != (undefined *)0x0) {
    puVar5 = puVar2 + 0x164;
    iVar3 = 4;
    do {
      piVar1 = (int *)(puVar5 + -0xc);
      puVar5 = puVar5 + -0xc;
      if ((int *)*piVar1 != (int *)0x0) {
        (**(code **)(*(int *)*piVar1 + 8))();
      }
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    FUN_00430df0(puVar2);
  }
  return;
}


/* 004732c0 size=99 */

undefined4 __cdecl FUN_004732c0(undefined2 *param_1,int *param_2,int param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  
  if (param_2[0xee] != param_3) {
    if (param_3 == 3) {
      bVar1 = FUN_00473330((int)param_1,(int)param_2);
      if (CONCAT31(extraout_var,bVar1) == 0) {
        return 0;
      }
      FUN_004733b0(param_1,param_2);
      return 1;
    }
    if (param_2[0xee] == 3) {
      FUN_004736c0((int)param_1,(int)param_2);
    }
    param_2[0xee] = param_3;
  }
  return 1;
}


/* 00473330 size=120 */

bool __cdecl FUN_00473330(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x198) == 0) {
    uVar1 = *(uint *)(param_2 + 0x3c0);
    if ((uVar1 & 0x100) == 0) {
      return false;
    }
    if ((uVar1 & 2) != 0) {
      return true;
    }
    if ((uVar1 & 1) == 0) {
      iVar2 = FUN_00438850(*(int *)(param_2 + 0x18c));
      return (bool)('\x01' - (iVar2 != 0));
    }
    iVar2 = FUN_00438850(*(int *)(param_2 + 0x18c));
    if (iVar2 == 0) {
      iVar2 = FUN_00438860(*(int *)(param_2 + 0x18c));
      if (iVar2 == 0) {
        return true;
      }
    }
  }
  return false;
}


/* 004733b0 size=783 */

undefined4 __cdecl FUN_004733b0(undefined2 *param_1,int *param_2)

{
  int *this;
  undefined2 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int iStack_c;
  int *local_8;
  undefined4 uStack_4;
  
  puVar3 = FUN_0046b170(&local_8,0x44c,0x44c);
  this = (int *)*puVar3;
  if (this != (int *)0x0) {
    (**(code **)(*this + 4))();
  }
  if (local_8 != (int *)0x0) {
    (**(code **)(*local_8 + 8))();
  }
  piVar2 = param_2;
  puVar1 = param_1;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(this + 0xe) = 1;
    *(undefined2 *)(this + 0xd) = 1;
    FUN_00477830((int)param_1,(int)param_2,5,this,0,0x80);
    if ((*(byte *)(piVar2 + 0xf0) & 2) != 0) {
      DAT_004e5170 = puVar1 + 0xd2;
    }
    iStack_c = FUN_00434ff0(*(int *)(puVar1 + 0x660));
    while (iStack_c != 0) {
      iVar4 = FUN_00435040(&iStack_c);
      if (iVar4 != 0) {
        iVar4 = FUN_00434fd0(iVar4);
        *(undefined2 *)(this + 0xe) = 1;
        *(undefined2 *)(this + 0xd) = 1;
        FUN_0046b440(this,*(char **)(iVar4 + 0x10));
        FUN_0046b440(this,*(char **)(iVar4 + 0x14));
        FUN_00477830((int)puVar1,(int)piVar2,0x10,this,0,0x80);
      }
    }
    param_2 = (int *)0x0;
    (**(code **)(**(int **)(puVar1 + 0x518) + 0x10))(piVar2,piVar2[0x44],&param_2);
    *(undefined2 *)(this + 0xe) = 1;
    *(undefined2 *)(this + 0xd) = 1;
    s_concommand_4757a0(this,*(undefined4 *)(puVar1 + 0x46c));
    FUN_004385b0(this,*(undefined2 *)(*(int *)(puVar1 + 0x334) + 8));
    FUN_00438f40(this,param_2);
    FUN_0046b440(this,(char *)(puVar1 + 0x336));
    uStack_4 = *(undefined4 *)(puVar1 + 0x436);
    if (*(ushort *)(this + 0xe) + 4 < (uint)*(ushort *)((int)this + 0x36)) {
      if ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 4) {
        do {
          param_1 = (undefined2 *)((uint)param_1 & 0xffffff00);
          FUN_00414b10(this + 0x14,(undefined1 *)this[0x16],(undefined1 *)&param_1,&DAT_004ecc58);
        } while ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 4);
      }
      *(undefined4 *)(this[0x15] + (uint)*(ushort *)(this + 0xe)) = uStack_4;
      *(short *)(this + 0xe) = (short)this[0xe] + 4;
      *(short *)(this + 0xd) = (short)this[0xd] + 4;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      this[0x10] = this[0x10] | 4;
    }
    uStack_4 = *(undefined4 *)(puVar1 + 0x438);
    if (*(ushort *)(this + 0xe) + 4 < (uint)*(ushort *)((int)this + 0x36)) {
      if ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 4) {
        do {
          param_1 = (undefined2 *)((uint)param_1 & 0xffffff00);
          FUN_00414b10(this + 0x14,(undefined1 *)this[0x16],(undefined1 *)&param_1,&DAT_004ecc58);
        } while ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 4);
      }
      *(undefined4 *)(this[0x15] + (uint)*(ushort *)(this + 0xe)) = uStack_4;
      *(short *)(this + 0xe) = (short)this[0xe] + 4;
      *(short *)(this + 0xd) = (short)this[0xd] + 4;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      this[0x10] = this[0x10] | 4;
    }
    FUN_00477830((int)puVar1,(int)piVar2,6,this,0,0x80);
    piVar2[0xee] = 2;
    piVar2[0xef] = 0;
    if ((*(byte *)(piVar2 + 0xf0) & 2) != 0) {
      s_client_471f90(puVar1,piVar2);
    }
  }
  if (this != (int *)0x0) {
    (**(code **)(*this + 8))();
  }
  return 0;
}


/* 004736c0 size=170 */

void __cdecl FUN_004736c0(int param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int *local_4;
  
  puVar2 = FUN_0046b170(&local_4,0x44c,0x44c);
  piVar1 = (int *)*puVar2;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))();
  }
  if (local_4 != (int *)0x0) {
    (**(code **)(*local_4 + 8))();
  }
  (**(code **)(**(int **)(param_1 + 0xa30) + 0x18))(param_2);
  if (*(int *)(param_2 + 0x3ac) != 0) {
    *(undefined4 *)(*(int *)(*(int *)(param_2 + 0x3ac) + 400) + 0x1c) = 0;
  }
  *(undefined4 *)(param_2 + 0x3ac) = 0;
  *(undefined2 *)(piVar1 + 0xe) = 1;
  *(undefined2 *)(piVar1 + 0xd) = 1;
  FUN_00477830(param_1,param_2,5,piVar1,0,0x80);
  if ((*(byte *)(param_2 + 0x3c0) & 2) != 0) {
    FUN_00416bb0();
  }
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))();
  }
  return;
}


/* 00473770 size=74 */

void __cdecl FUN_00473770(undefined2 *param_1,int *param_2)

{
  if (param_2[0xee] == 1) {
    FUN_004732c0(param_1,param_2,3);
    FUN_004737c0((int)param_1,(int)param_2);
    return;
  }
  if (param_2[0xee] == 2) {
    s_client_471f90(param_1,param_2);
  }
  FUN_004737c0((int)param_1,(int)param_2);
  return;
}


/* 004737c0 size=31 */

void __cdecl FUN_004737c0(int param_1,int param_2)

{
  FUN_00438d30(*(int *)(param_2 + 0x18c),*(float *)(param_1 + 0x8e0));
  return;
}


/* 004738c0 size=451 */

/* WARNING: Removing unreachable block (ram,0x004739de) */

undefined4 __cdecl FUN_004738c0(int *param_1,int *param_2,char param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  
  if (param_4 != -1) {
    iVar2 = ((uint)*(ushort *)((int)param_2 + 0x36) - (uint)*(ushort *)(param_2 + 0xe)) + -7;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
    if (param_4 + 4 < iVar2) {
      return 0;
    }
  }
  bVar5 = 0;
  if (param_3 == '\b') {
    bVar5 = 0x80;
  }
  s_client_4737e0(*param_1,(int)param_2);
  FUN_00477830(*param_1,param_1[1],param_3,param_2,0,bVar5);
  *(undefined2 *)(param_2 + 0xe) = 1;
  *(undefined2 *)(param_2 + 0xd) = 1;
  if (*(ushort *)((int)param_2 + 0x36) < 3) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    param_2[0x10] = param_2[0x10] | 4;
    param_1[6] = param_1[6] + 1;
    return 1;
  }
  if ((uint)param_2[0x16] < 3) {
    do {
      uVar1 = param_2[0x16];
      if (param_2[0x17] == 0) {
        iVar2 = FUN_0040c920(&DAT_004ecc58,0,param_2[0x18] + uVar1 + 1);
        if (iVar2 != 0) {
          uVar4 = 0;
          if (uVar1 != 0) {
            do {
              uVar3 = uVar4 + 1;
              *(undefined1 *)(uVar4 + iVar2) = *(undefined1 *)(uVar4 + param_2[0x15]);
              uVar4 = uVar3;
            } while (uVar3 < uVar1);
          }
          uVar4 = uVar1;
          if (uVar1 < (uint)param_2[0x16]) {
            do {
              uVar3 = uVar4 + 1;
              *(undefined1 *)(iVar2 + uVar3) = *(undefined1 *)(uVar4 + param_2[0x15]);
              uVar4 = uVar3;
            } while (uVar3 < (uint)param_2[0x16]);
          }
          *(undefined1 *)(iVar2 + uVar1) = 0;
          if (param_2[0x15] != 0) {
            FUN_00433560(param_2 + 0x14,&DAT_004ecc58);
          }
          param_2[0x15] = iVar2;
          param_2[0x17] = param_2[0x18];
          goto LAB_004739fc;
        }
      }
      else {
        param_2[0x17] = param_2[0x17] + -1;
        *(undefined1 *)(param_2[0x15] + uVar1) = 0;
LAB_004739fc:
        param_2[0x16] = param_2[0x16] + 1;
      }
    } while ((uint)param_2[0x16] <= *(ushort *)(param_2 + 0xd) + 1);
  }
  *(undefined1 *)(param_2[0x15] + (uint)*(ushort *)(param_2 + 0xe)) = 0;
  *(short *)(param_2 + 0xe) = (short)param_2[0xe] + 1;
  *(short *)(param_2 + 0xd) = (short)param_2[0xd] + 1;
  param_1[6] = param_1[6] + 1;
  return 1;
}


/* 00473a90 size=896 */

void __cdecl FUN_00473a90(int *param_1,int *param_2)

{
  ushort *puVar1;
  ushort uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int *piVar8;
  undefined4 *puVar9;
  int *piVar10;
  undefined4 *puVar11;
  int *piVar12;
  
  piVar12 = param_1;
  if ((((((param_1[0x15] == 0) && (iVar4 = (**(code **)(*param_1 + 0x34))(), iVar4 == 0)) &&
        (((char)piVar12[0x2f] != '\x02' ||
         (iVar4 = (*(code *)**(undefined4 **)piVar12[0x6c])(), iVar4 != 1)))) &&
       ((piVar3 = param_2, (piVar12[0x22] & 0x1000000U) != 0 ||
        (((piVar12[0x22] & 0x3001U) != 0 &&
         (((char)piVar12[0x2f] != '\0' || (*(int *)(piVar12[100] + 0x2c) != 0)))))))) &&
      ((*(byte *)(piVar12 + 0x49) & 4) != 0)) &&
     (((char)piVar12[0x2f] != '\x01' || (piVar12[0x7e] != *(int *)(*param_2 + 0xd38))))) {
    iVar4 = *(int *)(param_2[1] + 400);
    puVar1 = (ushort *)(iVar4 + (uint)*(ushort *)(piVar12 + 0x2e) * 4);
    if ((*(byte *)(iVar4 + 1 + (uint)*(ushort *)(piVar12 + 0x2e) * 4) & 0x10) == 0) {
      if (DAT_004eabbc[1] <= *DAT_004eabbc) {
        param_2 = FUN_00430f00((uint)DAT_004eabbc[1] * 2 + 400);
        uVar2 = *DAT_004eabbc;
        piVar8 = *(int **)(DAT_004eabbc + 2);
        piVar10 = param_2;
        for (uVar7 = (uint)(uVar2 >> 1); uVar7 != 0; uVar7 = uVar7 - 1) {
          *piVar10 = *piVar8;
          piVar8 = piVar8 + 1;
          piVar10 = piVar10 + 1;
        }
        for (iVar4 = (uVar2 & 1) << 1; iVar4 != 0; iVar4 = iVar4 + -1) {
          *(char *)piVar10 = (char)*piVar8;
          piVar8 = (int *)((int)piVar8 + 1);
          piVar10 = (int *)((int)piVar10 + 1);
        }
        FUN_00430fe0(*(undefined **)(DAT_004eabbc + 2));
        *(int **)(DAT_004eabbc + 2) = param_2;
        DAT_004eabbc[1] = DAT_004eabbc[1] + 200;
      }
      *(short *)(*(int *)(DAT_004eabbc + 2) + (uint)*DAT_004eabbc * 2) = (short)piVar12[0x2e];
      *DAT_004eabbc = *DAT_004eabbc + 1;
      param_1 = (int *)0x0;
      FUN_004767f0(*piVar3,piVar3[1],(int)piVar12,puVar1,(void *)0x0,(int *)&param_1);
      FUN_004738c0(piVar3,(int *)piVar3[2],'\b',(int)param_1);
      FUN_004767f0(*piVar3,piVar3[1],(int)piVar12,puVar1,(void *)piVar3[2],(int *)0x0);
      FUN_00473e10(piVar3,(int)piVar12);
      *puVar1 = (ushort)((byte)(*puVar1 >> 8) & 0x40 | 0x10) << 8;
      iVar4 = extraout_EDX;
    }
    for (piVar12 = (int *)piVar12[0x26]; piVar12 != (int *)0x0; piVar12 = (int *)piVar12[9]) {
      param_1 = piVar12;
      iVar5 = FUN_0047a090(*piVar3,CONCAT22((short)((uint)iVar4 >> 0x10),
                                            *(undefined2 *)((int)piVar12 + 0x1e)));
      iVar4 = extraout_EDX_00;
      if (((iVar5 != 0) &&
          (((*(uint *)(iVar5 + 0x88) & 0x1000000) != 0 ||
           (((*(uint *)(iVar5 + 0x88) & 0x3001) != 0 &&
            ((*(char *)(iVar5 + 0xbc) != '\0' || (*(int *)(*(int *)(iVar5 + 400) + 0x2c) != 0)))))))
          ) && (((*(byte *)(iVar5 + 0x124) & 4) != 0 &&
                ((*(char *)(iVar5 + 0xbc) != '\x01' ||
                 (iVar4 = *piVar3, *(int *)(iVar5 + 0x1f8) != *(int *)(iVar4 + 0xd38))))))) {
        iVar4 = piVar3[1];
        puVar1 = (ushort *)(*(int *)(iVar4 + 400) + (uint)*(ushort *)(iVar5 + 0xb8) * 4);
        if ((*(byte *)(*(int *)(iVar4 + 400) + 1 + (uint)*(ushort *)(iVar5 + 0xb8) * 4) & 0x10) == 0
           ) {
          if (DAT_004eabbc[1] <= *DAT_004eabbc) {
            puVar6 = FUN_00430f00((uint)DAT_004eabbc[1] * 2 + 400);
            uVar2 = *DAT_004eabbc;
            puVar9 = *(undefined4 **)(DAT_004eabbc + 2);
            puVar11 = puVar6;
            for (uVar7 = (uint)(uVar2 >> 1); uVar7 != 0; uVar7 = uVar7 - 1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
            for (iVar4 = (uVar2 & 1) << 1; iVar4 != 0; iVar4 = iVar4 + -1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
              puVar9 = (undefined4 *)((int)puVar9 + 1);
              puVar11 = (undefined4 *)((int)puVar11 + 1);
            }
            FUN_00430fe0(*(undefined **)(DAT_004eabbc + 2));
            *(undefined4 **)(DAT_004eabbc + 2) = puVar6;
            DAT_004eabbc[1] = DAT_004eabbc[1] + 200;
            piVar12 = param_1;
          }
          *(undefined2 *)(*(int *)(DAT_004eabbc + 2) + (uint)*DAT_004eabbc * 2) =
               *(undefined2 *)(iVar5 + 0xb8);
          *DAT_004eabbc = *DAT_004eabbc + 1;
          param_2 = (int *)0x0;
          FUN_004767f0(*piVar3,piVar3[1],iVar5,puVar1,(void *)0x0,(int *)&param_2);
          FUN_004738c0(piVar3,(int *)piVar3[2],'\b',(int)param_2);
          FUN_004767f0(*piVar3,piVar3[1],iVar5,puVar1,(void *)piVar3[2],(int *)0x0);
          FUN_00473e10(piVar3,iVar5);
          *puVar1 = (ushort)((byte)(*puVar1 >> 8) & 0x40 | 0x10) << 8;
          iVar4 = extraout_EDX_01;
        }
      }
    }
  }
  return;
}


/* 00473e10 size=299 */

void __cdecl FUN_00473e10(int *param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  
  iVar2 = param_2;
  uVar1 = *(ushort *)(*(int *)(param_2 + 400) + 0x5a);
  if ((uVar1 & 7) != 0) {
    uVar3 = 0;
    if ((uVar1 & 2) != 0) {
      uVar3 = 0x4000;
    }
    if ((uVar1 & 4) != 0) {
      if ((*(uint *)(param_2 + 0x88) & 0x800) == 0) {
        uVar3 = uVar3 | 0x2000;
      }
      else {
        uVar3 = uVar3 | 0x8000;
      }
    }
    if ((uVar1 & 1) != 0) {
      uVar3 = uVar3 | 0x1000;
    }
    param_2 = 0x19;
    if (((uVar3 & 0x1000) != 0) && (iVar2 != 0)) {
      FUN_004763b0(iVar2,(void *)0x0,&param_2);
    }
    FUN_004738c0(param_1,(int *)param_1[3],'\n',param_2);
    FUN_004385b0((void *)param_1[3],*(ushort *)(iVar2 + 0xb8) | uVar3);
    if ((uVar3 & 0x4000) != 0) {
      FUN_0043f380((int *)(param_1[3] + 8));
      (**(code **)(*(int *)(param_1[3] + 8) + 0x5c))(iVar2 + 0xc4);
    }
    if ((uVar3 & 0x8000) == 0) {
      if ((uVar3 & 0x2000) != 0) {
        FUN_0043f770((int *)(param_1[3] + 8),(float *)(iVar2 + 0x9c));
      }
    }
    else {
      FUN_0043fc10(param_1[3],(float *)(iVar2 + 0x9c));
    }
    if ((uVar3 & 0x1000) != 0) {
      FUN_004763b0(iVar2,(void *)param_1[3],(int *)0x0);
    }
  }
  return;
}


/* 00473fd0 size=377 */

void __cdecl FUN_00473fd0(int param_1,undefined4 param_2,uint param_3,int *param_4)

{
  void *this;
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = param_3;
  if (param_3 != 0) {
    if (*(ushort *)(param_3 + 0x38) + 2 < (uint)*(ushort *)(param_3 + 0x36)) {
      if (*(uint *)(param_3 + 0x58) <= *(ushort *)(param_3 + 0x34) + 2) {
        this = (void *)(param_3 + 0x50);
        do {
          param_3 = param_3 & 0xffffff00;
          FUN_00414b10(this,*(undefined1 **)(uVar2 + 0x58),(undefined1 *)&param_3,&DAT_004ecc58);
        } while (*(uint *)(uVar2 + 0x58) <= *(ushort *)(uVar2 + 0x34) + 2);
      }
      *(undefined2 *)(*(int *)(uVar2 + 0x54) + (uint)*(ushort *)(uVar2 + 0x38)) = 0xffff;
      *(short *)(uVar2 + 0x38) = *(short *)(uVar2 + 0x38) + 2;
      *(short *)(uVar2 + 0x34) = *(short *)(uVar2 + 0x34) + 2;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      *(uint *)(uVar2 + 0x40) = *(uint *)(uVar2 + 0x40) | 4;
    }
    uVar1 = *(undefined4 *)(param_1 + 0x8d8);
    if (*(ushort *)(uVar2 + 0x38) + 4 < (uint)*(ushort *)(uVar2 + 0x36)) {
      if (*(uint *)(uVar2 + 0x58) <= *(ushort *)(uVar2 + 0x34) + 4) {
        do {
          param_3 = param_3 & 0xffffff00;
          FUN_00414b10((void *)(uVar2 + 0x50),*(undefined1 **)(uVar2 + 0x58),(undefined1 *)&param_3,
                       &DAT_004ecc58);
        } while (*(uint *)(uVar2 + 0x58) <= *(ushort *)(uVar2 + 0x34) + 4);
      }
      *(undefined4 *)(*(int *)(uVar2 + 0x54) + (uint)*(ushort *)(uVar2 + 0x38)) = uVar1;
      *(short *)(uVar2 + 0x38) = *(short *)(uVar2 + 0x38) + 4;
      *(short *)(uVar2 + 0x34) = *(short *)(uVar2 + 0x34) + 4;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      *(uint *)(uVar2 + 0x40) = *(uint *)(uVar2 + 0x40) | 4;
    }
  }
  if (param_4 != (int *)0x0) {
    *param_4 = *param_4 + 6;
  }
  return;
}


