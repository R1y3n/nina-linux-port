/* lithtech.exe decompilation - unnamed_00474000 */
#include "ghidra_types.h"

/* 00474150 size=550 */

/* WARNING: Removing unreachable block (ram,0x004742c4) */

void __cdecl FUN_00474150(int param_1,undefined4 *param_2,int param_3)

{
  void *this;
  int *piVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *extraout_EDX;
  undefined4 *extraout_EDX_00;
  int iVar8;
  int local_8;
  
  piVar3 = (int *)(param_3 + 0x134);
  param_2 = param_2 + 4;
  local_8 = 2;
  do {
    iVar8 = 2;
    this = (void *)*param_2;
    puVar7 = param_2;
    do {
      piVar1 = (int *)*piVar3;
      puVar7 = (undefined4 *)CONCAT22((short)((uint)puVar7 >> 0x10),*(ushort *)(piVar1 + 0xd));
      if (0 < (int)(*(ushort *)(piVar1 + 0xd) - 1)) {
        iVar6 = ((uint)*(ushort *)((int)this + 0x36) - (uint)*(ushort *)((int)this + 0x38)) + -7;
        if (iVar6 < 0) {
          iVar6 = 0;
        }
        if ((int)(*(ushort *)(piVar1 + 0xd) - 1) < iVar6) {
          FUN_0046b480(this,(undefined4 *)(piVar1[0x15] + 1),(int)puVar7 - 1);
          puVar7 = extraout_EDX;
        }
        else {
          FUN_00477830(param_1,param_3,0xe,piVar1,1,(byte)piVar3[2]);
          puVar7 = extraout_EDX_00;
        }
        iVar6 = *piVar3;
        *(undefined2 *)(iVar6 + 0x38) = 1;
        *(undefined2 *)(iVar6 + 0x34) = 1;
      }
      piVar3 = piVar3 + 3;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    if (*(ushort *)((int)this + 0x38) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
      if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1) {
        do {
          uVar2 = *(uint *)((int)this + 0x58);
          if (*(int *)((int)this + 0x5c) == 0) {
            iVar8 = FUN_0040c920(&DAT_004ecc58,0,*(int *)((int)this + 0x60) + uVar2 + 1);
            if (iVar8 != 0) {
              uVar5 = 0;
              if (uVar2 != 0) {
                do {
                  uVar4 = uVar5 + 1;
                  *(undefined1 *)(uVar5 + iVar8) =
                       *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar4);
                  uVar5 = uVar4;
                } while (uVar4 < uVar2);
              }
              uVar5 = uVar2;
              if (uVar2 < *(uint *)((int)this + 0x58)) {
                do {
                  uVar5 = uVar5 + 1;
                  *(undefined1 *)(iVar8 + uVar5) =
                       *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar5);
                } while (uVar5 < *(uint *)((int)this + 0x58));
              }
              *(undefined1 *)(iVar8 + uVar2) = 0;
              if (*(int *)((int)this + 0x54) != 0) {
                FUN_00433560((void *)((int)this + 0x50),&DAT_004ecc58);
              }
              *(int *)((int)this + 0x54) = iVar8;
              *(undefined4 *)((int)this + 0x5c) = *(undefined4 *)((int)this + 0x60);
              *(int *)((int)this + 0x58) = *(int *)((int)this + 0x58) + 1;
            }
          }
          else {
            *(int *)((int)this + 0x5c) = *(int *)((int)this + 0x5c) + -1;
            *(undefined1 *)(*(int *)((int)this + 0x54) + uVar2) = 0;
            *(int *)((int)this + 0x58) = *(int *)((int)this + 0x58) + 1;
          }
        } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1);
      }
      *(undefined1 *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = 0;
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
    param_2 = param_2 + 1;
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  return;
}


/* 00474380 size=670 */

void __cdecl FUN_00474380(int *param_1,ushort *param_2)

{
  byte *pbVar1;
  ushort uVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  uint extraout_EDX;
  uint extraout_EDX_00;
  int local_8;
  ushort *local_4;
  
  piVar3 = param_1;
  local_8 = 0;
  param_1 = (int *)(uint)*param_2;
  local_4 = *(ushort **)(param_2 + 2);
  if (param_1 != (int *)0x0) {
    do {
      if ((*(byte *)(*(int *)(piVar3[1] + 400) + 1 + (uint)*local_4 * 4) & 0x10) == 0) {
        iVar4 = FUN_004738c0(piVar3,(int *)piVar3[2],'\b',0x10);
        if (iVar4 == 0) {
          if (local_8 == 0) goto LAB_004743f7;
        }
        else {
          local_8 = 0;
LAB_004743f7:
          FUN_004183a0((void *)piVar3[2],0);
          iVar4 = piVar3[2];
          if (*(ushort *)(iVar4 + 0x38) + 1 < (uint)*(ushort *)(iVar4 + 0x36)) {
            if (*(uint *)(iVar4 + 0x58) <= *(ushort *)(iVar4 + 0x34) + 1) {
              do {
                param_2 = (ushort *)((uint)param_2 & 0xffffff00);
                FUN_00414b10((void *)(iVar4 + 0x50),*(undefined1 **)(iVar4 + 0x58),
                             (undefined1 *)&param_2,&DAT_004ecc58);
              } while (*(uint *)(iVar4 + 0x58) <= *(ushort *)(iVar4 + 0x34) + 1);
            }
            *(undefined1 *)(*(int *)(iVar4 + 0x54) + (uint)*(ushort *)(iVar4 + 0x38)) = 3;
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
        iVar4 = piVar3[2];
        uVar2 = *local_4;
        if (*(ushort *)(iVar4 + 0x38) + 2 < (uint)*(ushort *)(iVar4 + 0x36)) {
          if (*(uint *)(iVar4 + 0x58) <= *(ushort *)(iVar4 + 0x34) + 2) {
            do {
              param_2 = (ushort *)((uint)param_2 & 0xffffff00);
              FUN_00414b10((void *)(iVar4 + 0x50),*(undefined1 **)(iVar4 + 0x58),
                           (undefined1 *)&param_2,&DAT_004ecc58);
            } while (*(uint *)(iVar4 + 0x58) <= *(ushort *)(iVar4 + 0x34) + 2);
          }
          uVar6 = (uint)*(ushort *)(iVar4 + 0x38);
          *(ushort *)(*(int *)(iVar4 + 0x54) + uVar6) = uVar2;
          *(short *)(iVar4 + 0x38) = *(short *)(iVar4 + 0x38) + 2;
          *(short *)(iVar4 + 0x34) = *(short *)(iVar4 + 0x34) + 2;
        }
        else {
          FUN_004356e0();
          uVar6 = extraout_EDX;
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0)
            ;
            uVar6 = extraout_EDX_00;
          }
          *(uint *)(iVar4 + 0x40) = *(uint *)(iVar4 + 0x40) | 4;
        }
        local_8 = local_8 + 1;
        pcVar5 = (char *)FUN_0047a0c0(*piVar3,CONCAT22((short)(uVar6 >> 0x10),*local_4));
        if ((pcVar5 != (char *)0x0) && (iVar4 = *(int *)(pcVar5 + 4), iVar4 != 0)) {
          if (*pcVar5 == '\x01') {
            uVar6 = FUN_00479170(*piVar3,iVar4);
            *(short *)(*(int *)(piVar3[1] + 400) + (uint)*local_4 * 4) = (short)uVar6;
          }
          else {
            pbVar1 = (byte *)(*(int *)(piVar3[1] + 400) + 2 + (uint)*local_4 * 4);
            if ((((*pbVar1 & 1) == 0) && ((*(uint *)(iVar4 + 0x34) & 0x428) != 0)) &&
               ((*(uint *)(iVar4 + 0x34) & 4) == 0)) {
              *pbVar1 = *pbVar1 | 1;
              if (*(int *)(iVar4 + 0x28) != 0) {
                *(int *)(iVar4 + 0x28) = *(int *)(iVar4 + 0x28) + -1;
              }
              if (*(int *)(iVar4 + 0x28) == 0) {
                *(undefined4 *)(iVar4 + 0x20) = 0;
              }
            }
            *(undefined2 *)(*(int *)(piVar3[1] + 400) + (uint)*local_4 * 4) = 3;
          }
        }
      }
      local_4 = local_4 + 1;
      param_1 = (int *)((int)param_1 + -1);
    } while (param_1 != (int *)0x0);
  }
  return;
}


/* 00474620 size=112 */

void __cdecl FUN_00474620(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = param_2 + 0x224;
  param_2 = 0xb;
  do {
    for (iVar1 = *(int *)(iVar4 + 4); iVar1 != iVar4; iVar1 = *(int *)(iVar1 + 4)) {
      piVar2 = *(int **)(iVar1 + 8);
      uVar3 = piVar2[0x49];
      if ((uVar3 & 0x200) != 0) {
        piVar2[0x49] = uVar3 & 0xfffffdff;
        FUN_0047a260(param_1,(int)piVar2,(uint)((byte)uVar3 & 0x18 | 0x20));
      }
      FUN_00473a90(piVar2,param_3);
    }
    iVar4 = iVar4 + 0x10;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return;
}


/* 00474690 size=2053 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00474690: lifted from original x86 -> lt_lifted.c */


/* 00474f40 size=552 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00474f40(int *param_1,int *param_2)

{
  ushort *puVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined4 *puVar9;
  uint uVar10;
  int iVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  int local_20;
  
  local_20 = *(int *)(*param_1 + 0x5c);
  if (local_20 != *param_1 + 0x58) {
    do {
      uVar3 = *(uint *)(local_20 + 8);
      iVar11 = param_1[1];
      if ((*(byte *)(*(int *)(iVar11 + 400) + *(int *)(*(int *)(uVar3 + 0xc) + 8) * 4) & 0x20) == 0)
      {
        if ((*(int *)(uVar3 + 0x10) == 0) &&
           ((*(int *)(uVar3 + 0x18) == 0 || (_DAT_004cb524 < *(float *)(uVar3 + 0x20))))) {
          if ((*(byte *)(uVar3 + 0x34) & 3) != 0) {
            iVar4 = *(int *)(iVar11 + 0x3ac);
            fVar5 = *(float *)(uVar3 + 0x40) * *(float *)(uVar3 + 0x40) * _DAT_004cbfcc;
            fVar8 = *(float *)(uVar3 + 0x50) - *(float *)(iVar4 + 0x194);
            fVar7 = *(float *)(uVar3 + 0x54) - *(float *)(iVar4 + 0x198);
            fVar6 = *(float *)(uVar3 + 0x58) - *(float *)(iVar4 + 0x19c);
            if ((fVar5 <= fVar8 * fVar8 + fVar7 * fVar7 + fVar6 * fVar6) &&
               (fVar8 = *(float *)(uVar3 + 0x50) - *(float *)(iVar11 + 0x174),
               fVar7 = *(float *)(uVar3 + 0x54) - *(float *)(iVar11 + 0x178),
               fVar6 = *(float *)(uVar3 + 0x58) - *(float *)(iVar11 + 0x17c),
               fVar5 <= fVar8 * fVar8 + fVar7 * fVar7 + fVar6 * fVar6)) goto LAB_0047514c;
          }
          goto LAB_0047506a;
        }
      }
      else {
LAB_0047506a:
        FUN_004738c0(param_1,param_2,'\b',0x2d);
        puVar1 = (ushort *)(*(int *)(param_1[1] + 400) + *(int *)(*(int *)(uVar3 + 0xc) + 8) * 4);
        if (DAT_004eabbc[1] <= *DAT_004eabbc) {
          puVar9 = FUN_00430f00((uint)DAT_004eabbc[1] * 2 + 400);
          uVar2 = *DAT_004eabbc;
          puVar12 = *(undefined4 **)(DAT_004eabbc + 2);
          puVar13 = puVar9;
          for (uVar10 = (uint)(uVar2 >> 1); uVar10 != 0; uVar10 = uVar10 - 1) {
            *puVar13 = *puVar12;
            puVar12 = puVar12 + 1;
            puVar13 = puVar13 + 1;
          }
          for (iVar11 = (uVar2 & 1) << 1; iVar11 != 0; iVar11 = iVar11 + -1) {
            *(undefined1 *)puVar13 = *(undefined1 *)puVar12;
            puVar12 = (undefined4 *)((int)puVar12 + 1);
            puVar13 = (undefined4 *)((int)puVar13 + 1);
          }
          FUN_00430fe0(*(undefined **)(DAT_004eabbc + 2));
          *(undefined4 **)(DAT_004eabbc + 2) = puVar9;
          DAT_004eabbc[1] = DAT_004eabbc[1] + 200;
        }
        *(short *)(*(int *)(DAT_004eabbc + 2) + (uint)*DAT_004eabbc * 2) =
             (short)*(undefined4 *)(*(int *)(uVar3 + 0xc) + 8);
        *DAT_004eabbc = *DAT_004eabbc + 1;
        if ((*puVar1 != 0) && ((puVar1[1] & 1) == 0)) {
          FUN_00477c20(*param_1,uVar3,puVar1,param_1[1],param_2);
        }
        *puVar1 = 0x1000;
      }
LAB_0047514c:
      local_20 = *(int *)(local_20 + 4);
    } while (local_20 != *param_1 + 0x58);
  }
  return;
}


/* 00475170 size=47 */

int __cdecl FUN_00475170(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x9fc);
  while( true ) {
    if (iVar1 == param_1 + 0x9f8) {
      return 0;
    }
    if (*(int *)(*(int *)(iVar1 + 8) + 0x3c8) == param_2) break;
    iVar1 = *(int *)(iVar1 + 4);
  }
  return *(int *)(iVar1 + 8);
}


/* 004751a0 size=48 */

void __cdecl FUN_004751a0(int param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)(param_1 + 0x9fc); iVar1 != param_1 + 0x9f8; iVar1 = *(int *)(iVar1 + 4)) {
    *(uint *)(*(int *)(iVar1 + 8) + 0x3c0) = *(uint *)(*(int *)(iVar1 + 8) + 0x3c0) | 0x20;
  }
  return;
}


/* 004751d0 size=486 */

void __cdecl FUN_004751d0(int param_1,int param_2)

{
  undefined2 uVar1;
  int *this;
  undefined4 *puVar2;
  undefined2 *puVar3;
  undefined1 uStack_9;
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
  FUN_0046b480(this,(undefined4 *)(param_1 + 0xb3c),0x30);
  if (*(ushort *)(this + 0xe) + 2 < (uint)*(ushort *)((int)this + 0x36)) {
    if ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 2) {
      do {
        uStack_9 = 0;
        FUN_00414b10(this + 0x14,(undefined1 *)this[0x16],&uStack_9,&DAT_004ecc58);
      } while ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 2);
    }
    *(undefined2 *)(this[0x15] + (uint)*(ushort *)(this + 0xe)) = 0x1e;
    *(short *)(this + 0xe) = (short)this[0xe] + 2;
    *(short *)(this + 0xd) = (short)this[0xd] + 2;
  }
  else {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    this[0x10] = this[0x10] | 4;
  }
  puVar3 = (undefined2 *)(param_1 + 0xb6c);
  iStack_8 = 0x1e;
  do {
    uVar1 = *puVar3;
    if (*(ushort *)(this + 0xe) + 2 < (uint)*(ushort *)((int)this + 0x36)) {
      if ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 2) {
        do {
          uStack_9 = 0;
          FUN_00414b10(this + 0x14,(undefined1 *)this[0x16],&uStack_9,&DAT_004ecc58);
        } while ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 2);
      }
      *(undefined2 *)(this[0x15] + (uint)*(ushort *)(this + 0xe)) = uVar1;
      *(short *)(this + 0xe) = (short)this[0xe] + 2;
      *(short *)(this + 0xd) = (short)this[0xd] + 2;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      this[0x10] = this[0x10] | 4;
    }
    puVar3 = puVar3 + 1;
    iStack_8 = iStack_8 + -1;
  } while (iStack_8 != 0);
  FUN_00477830(param_1,param_2,0x11,this,0,0x80);
  if (this != (int *)0x0) {
    (**(code **)(*this + 8))();
  }
  return;
}


/* 004753c0 size=441 */

void __cdecl FUN_004753c0(uint param_1,int param_2)

{
  int *this;
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  int *local_64;
  undefined4 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float afStack_50 [4];
  float afStack_40 [2];
  undefined4 uStack_38;
  undefined4 uStack_28;
  undefined4 uStack_18;
  
  puVar2 = FUN_0046b170(&local_64,0x44c,0x44c);
  this = (int *)*puVar2;
  if (this != (int *)0x0) {
    (**(code **)(*this + 4))();
  }
  if (local_64 != (int *)0x0) {
    (**(code **)(*local_64 + 8))();
  }
  uVar1 = param_1;
  iVar3 = (**(code **)(*(int *)(param_1 + 0xb38) + 0x13c))(*(undefined4 *)(param_1 + 0xba8));
  (**(code **)(*(int *)(uVar1 + 0xb38) + 0x1b8))(*(undefined4 *)(uVar1 + 0xba8),afStack_50);
  FUN_0044e720(afStack_50,afStack_40);
  uStack_58 = uStack_28;
  uStack_54 = uStack_18;
  s_concommand_4757a0(this,uStack_38);
  s_concommand_4757a0(this,uStack_58);
  s_concommand_4757a0(this,uStack_54);
  s_concommand_4757a0(this,*(undefined4 *)(iVar3 + 0x14));
  s_concommand_4757a0(this,*(undefined4 *)(iVar3 + 0x18));
  s_concommand_4757a0(this,*(undefined4 *)(iVar3 + 0x1c));
  uStack_60 = *(undefined4 *)(iVar3 + 0x2c);
  if (*(ushort *)(this + 0xe) + 4 < (uint)*(ushort *)((int)this + 0x36)) {
    if ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 4) {
      do {
        param_1 = param_1 & 0xffffff00;
        FUN_00414b10(this + 0x14,(undefined1 *)this[0x16],(undefined1 *)&param_1,&DAT_004ecc58);
      } while ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 4);
    }
    *(undefined4 *)(this[0x15] + (uint)*(ushort *)(this + 0xe)) = uStack_60;
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
  FUN_00477830(uVar1,param_2,0x1a,this,0,0x80);
  if (this != (int *)0x0) {
    (**(code **)(*this + 8))();
  }
  return;
}


/* 00475580 size=112 */

undefined4 __cdecl FUN_00475580(int param_1,int param_2)

{
  uint uVar1;
  short *psVar2;
  
  if ((~*(uint *)(param_2 + 0x124) & 0x100) == 0) {
    *(uint *)(param_2 + 0x124) = *(uint *)(param_2 + 0x124) & 0xfffffeff;
    FUN_004751a0(param_1);
    uVar1 = 0;
    psVar2 = (short *)(DAT_004ebfa4 + 0xb6c);
    while (*psVar2 != *(short *)(param_2 + 0xb8)) {
      uVar1 = uVar1 + 1;
      psVar2 = psVar2 + 1;
      if (0x1d < uVar1) {
        return 0;
      }
    }
    *(undefined2 *)(param_1 + 0xb6c + uVar1 * 2) = 0xffff;
    FUN_004751a0(DAT_004ebfa4);
  }
  return 0;
}


/* 004755f0 size=186 */

undefined4 * __cdecl FUN_004755f0(int param_1,undefined4 param_2)

{
  uint *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  iVar2 = FUN_00434ec0(*(int **)(param_1 + 0x3dc),&param_2,2);
  if ((iVar2 != 0) && (puVar3 = (undefined4 *)FUN_00434fd0(iVar2), puVar3 != (undefined4 *)0x0)) {
    return puVar3;
  }
  iVar2 = DAT_004ebfa4;
  puVar3 = *(undefined4 **)(DAT_004ebfa4 + 0xac4);
  puVar1 = (uint *)(DAT_004ebfa4 + 0xaac);
  if (puVar3 == (undefined4 *)0x0) {
    FUN_004b7c60((int)puVar1,*(int *)(DAT_004ebfa4 + 0xab4));
    puVar3 = *(undefined4 **)(iVar2 + 0xac4);
    if (puVar3 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
  }
  *(undefined4 *)(iVar2 + 0xac4) = *puVar3;
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
  *(undefined1 *)puVar3 = 7;
  piVar4 = FUN_00434d70(*(int **)(param_1 + 0x3dc),&param_2,2);
  if (piVar4 == (int *)0x0) {
    FUN_00430fe0((undefined *)puVar3);
    return (undefined4 *)0x0;
  }
  FUN_00434fe0((int)piVar4,puVar3);
  return puVar3;
}


/* 004756b0 size=54 */

undefined4 __cdecl FUN_004756b0(int param_1,short param_2,uint *param_3)

{
  uint uVar1;
  short *psVar2;
  
  uVar1 = 0;
  if (*(uint *)(param_1 + 0x10c) != 0) {
    psVar2 = (short *)(param_1 + 0xc);
    do {
      if (*psVar2 == param_2) {
        *param_3 = uVar1;
        return 1;
      }
      uVar1 = uVar1 + 1;
      psVar2 = psVar2 + 2;
    } while (uVar1 < *(uint *)(param_1 + 0x10c));
  }
  return 0;
}


/* 004756f0 size=156 */

void __cdecl FUN_004756f0(uint param_1,uint param_2,undefined4 param_3)

{
  ushort *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  uVar4 = param_3;
  uVar3 = param_2;
  if ((param_2 < *(uint *)(param_1 + 0x1b0)) &&
     (iVar6 = *(int *)(param_1 + 0x9fc), iVar6 != param_1 + 0x9f8)) {
    do {
      iVar2 = *(int *)(iVar6 + 8);
      iVar5 = FUN_004756b0(iVar2,(short)uVar3,&param_2);
      if (iVar5 == 0) {
        if (0x3f < *(uint *)(iVar2 + 0x10c)) {
          FUN_00471e70(param_1,iVar2);
        }
        *(short *)(iVar2 + 0xc + *(int *)(iVar2 + 0x10c) * 4) = (short)uVar3;
        *(ushort *)(iVar2 + 0xe + *(int *)(iVar2 + 0x10c) * 4) = (ushort)uVar4;
        *(int *)(iVar2 + 0x10c) = *(int *)(iVar2 + 0x10c) + 1;
      }
      else {
        puVar1 = (ushort *)(iVar2 + 0xe + param_2 * 4);
        *puVar1 = *puVar1 | (ushort)uVar4;
      }
      iVar6 = *(int *)(iVar6 + 4);
    } while (iVar6 != param_1 + 0x9f8);
  }
  return;
}


/* 00475790 size=12 */

void __fastcall FUN_00475790(int *param_1)

{
  if ((int *)*param_1 == (int *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00475798. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)*param_1 + 8))();
  return;
}


/* 00475ff0 size=106 */

void __cdecl FUN_00475ff0(undefined4 param_1,undefined4 *param_2)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = param_2;
  for (iVar3 = 0x11; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *param_2 = 0;
  param_2[1] = 0;
  ppuVar1 = FUN_00437680();
  param_2[2] = ppuVar1;
  uVar2 = FUN_00437690();
  param_2[3] = uVar2;
  param_2[4] = &PTR_s_Portal_004db8e0;
  param_2[5] = 8;
  param_2[9] = FUN_00436670;
  param_2[10] = FUN_00430de0;
  param_2[0xb] = FUN_00430df0;
  param_2[0xc] = s_concommand_475f10;
  param_2[0xd] = &LAB_00475fd0;
  param_2[0xe] = param_1;
  FUN_00420630((int)param_2);
  return;
}


/* 00476060 size=12 */

void __cdecl FUN_00476060(undefined4 *param_1)

{
  FUN_004206a0(param_1);
  return;
}


/* 00476070 size=34 */

undefined4 __cdecl FUN_00476070(undefined4 param_1,byte param_2)

{
  DAT_004eabc0 = 0;
  FUN_00420080(param_1,param_2);
  return DAT_004eabc0;
}


/* 004760d0 size=37 */

void __cdecl FUN_004760d0(float *param_1,undefined4 *param_2)

{
  if (DAT_004ebfa4 == 0) {
    return;
  }
  FUN_0043913d(param_1,param_2,(int *)(DAT_004ebfa4 + 0x210));
  return;
}


/* 00476130 size=36 */

undefined4 __thiscall FUN_00476130(void *this,int param_1,int param_2)

{
  FUN_00486990((int)this);
  s_client_4725f0(this,param_1,param_2);
  return 1;
}


/* 00476160 size=26 */

void __thiscall FUN_00476160(void *this,int param_1)

{
  FUN_00486990((int)this);
  FUN_00472d40(this,param_1);
  return;
}


/* 00476180 size=81 */

void __thiscall FUN_00476180(void *this,int param_1,undefined4 param_2,undefined4 param_3)

{
  if (*(int **)((int)this + 0xcd0) != (int *)0x0) {
    (**(code **)(**(int **)((int)this + 0xcd0) + 0xc))
              (*(undefined4 *)(param_1 + 0x54),*(undefined2 *)(param_1 + 0x34),param_2,param_3);
  }
  if (*(int **)((int)this + 0xa30) != (int *)0x0) {
    (**(code **)(**(int **)((int)this + 0xa30) + 0x50))
              (*(undefined4 *)(param_1 + 0x54),*(undefined2 *)(param_1 + 0x34),param_2,param_3);
  }
  return;
}


/* 004761e0 size=458 */

void __cdecl FUN_004761e0(int param_1,uint param_2,int *param_3)

{
  void *this;
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined2 uVar4;
  int *piVar5;
  int local_4;
  
  uVar2 = param_2;
  if (param_2 != 0) {
    uVar4 = *(undefined2 *)(*(int *)(*(int *)(param_1 + 400) + 0x30) + 8);
    if (*(ushort *)(param_2 + 0x38) + 2 < (uint)*(ushort *)(param_2 + 0x36)) {
      if (*(uint *)(param_2 + 0x58) <= *(ushort *)(param_2 + 0x34) + 2) {
        this = (void *)(param_2 + 0x50);
        do {
          param_2 = param_2 & 0xffffff00;
          FUN_00414b10(this,*(undefined1 **)(uVar2 + 0x58),(undefined1 *)&param_2,&DAT_004ecc58);
        } while (*(uint *)(uVar2 + 0x58) <= *(ushort *)(uVar2 + 0x34) + 2);
      }
      *(undefined2 *)(*(int *)(uVar2 + 0x54) + (uint)*(ushort *)(uVar2 + 0x38)) = uVar4;
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
  }
  if (param_3 != (int *)0x0) {
    *param_3 = *param_3 + 2;
  }
  iVar3 = 0x34;
  local_4 = 4;
  piVar5 = param_3;
  do {
    if (uVar2 != 0) {
      iVar1 = *(int *)(*(int *)(param_1 + 400) + iVar3);
      if (iVar1 == 0) {
        uVar4 = 0xffff;
      }
      else {
        uVar4 = *(undefined2 *)(iVar1 + 8);
      }
      if (*(ushort *)(uVar2 + 0x38) + 2 < (uint)*(ushort *)(uVar2 + 0x36)) {
        if (*(uint *)(uVar2 + 0x58) <= *(ushort *)(uVar2 + 0x34) + 2) {
          do {
            param_2 = param_2 & 0xffffff00;
            FUN_00414b10((void *)(uVar2 + 0x50),*(undefined1 **)(uVar2 + 0x58),
                         (undefined1 *)&param_2,&DAT_004ecc58);
          } while (*(uint *)(uVar2 + 0x58) <= *(ushort *)(uVar2 + 0x34) + 2);
          piVar5 = param_3;
        }
        *(undefined2 *)(*(int *)(uVar2 + 0x54) + (uint)*(ushort *)(uVar2 + 0x38)) = uVar4;
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
    }
    if (piVar5 != (int *)0x0) {
      *piVar5 = *piVar5 + 2;
    }
    iVar3 = iVar3 + 4;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  return;
}


/* 004763b0 size=1087 */

/* FUN_004763b0: lifted from original x86 -> lt_lifted.c */


/* 004767f0 size=4073 */

/* WARNING: Removing unreachable block (ram,0x004775ad) */
/* WARNING: Removing unreachable block (ram,0x00477734) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004767f0: lifted from original x86 -> lt_lifted.c */


/* 004777e0 size=77 */

void __cdecl FUN_004777e0(int param_1,undefined1 param_2,int *param_3,byte param_4)

{
  int iVar1;
  float *pfVar2;
  
  *(undefined1 *)param_3[0x15] = param_2;
  for (iVar1 = *(int *)(param_1 + 0x9fc); iVar1 != param_1 + 0x9f8; iVar1 = *(int *)(iVar1 + 4)) {
    pfVar2 = *(float **)(*(int *)(iVar1 + 8) + 0x3c8);
    if (pfVar2 != (float *)0x0) {
      FUN_004657c0((void *)(param_1 + 0x8ec),param_3,pfVar2,param_4);
    }
  }
  return;
}


/* 00477830 size=136 */

void __cdecl
FUN_00477830(int param_1,int param_2,undefined1 param_3,int *param_4,int param_5,byte param_6)

{
  float *pfVar1;
  int iVar2;
  
  *(undefined1 *)param_4[0x15] = param_3;
  if (*(float **)(param_2 + 0x3c8) != (float *)0x0) {
    iVar2 = FUN_004657c0((void *)(param_1 + 0x8ec),param_4,*(float **)(param_2 + 0x3c8),param_6);
    if (iVar2 == 0) {
      *(int *)(param_1 + 0xa10) = *(int *)(param_1 + 0xa10) + 1;
    }
    *(int *)(param_1 + 0xa0c) = *(int *)(param_1 + 0xa0c) + 1;
  }
  if (param_5 != 0) {
    for (iVar2 = *(int *)(param_2 + 0x184); iVar2 != param_2 + 0x180; iVar2 = *(int *)(iVar2 + 4)) {
      pfVar1 = *(float **)(*(int *)(iVar2 + 8) + 0x3c8);
      if (pfVar1 != (float *)0x0) {
        FUN_004657c0((void *)(param_1 + 0x8ec),param_4,pfVar1,param_6);
      }
    }
  }
  return;
}


/* 004778c0 size=459 */

undefined4 __cdecl
FUN_004778c0(undefined4 param_1,int param_2,uint param_3,int *param_4,uint param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint extraout_EDX;
  uint extraout_EDX_00;
  int *piVar5;
  byte bVar6;
  
  bVar6 = (byte)param_5;
  if ((((*(byte *)(param_2 + 0x3c0) & 2) != 0) || ((param_5 & 3) == 0)) ||
     (0xff < *(ushort *)(param_4 + 0xd))) {
    FUN_00477830(DAT_004ebfa4,param_2,(char)param_3,param_4,1,bVar6);
    return 0;
  }
  iVar3 = (param_5 >> 1 & 1) + (param_5 >> 7 & 1) * 2;
  piVar1 = (int *)(param_2 + 0x134 + iVar3 * 0xc);
  piVar5 = *(int **)(param_2 + 0x134 + iVar3 * 0xc);
  iVar3 = ((uint)*(ushort *)((int)piVar5 + 0x36) - (uint)*(ushort *)(piVar5 + 0xe)) + -7;
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  if (iVar3 < (int)(*(ushort *)(param_4 + 0xd) + 1)) {
    FUN_00477830(DAT_004ebfa4,param_2,0xe,piVar5,1,(byte)piVar1[2]);
    iVar3 = *piVar1;
    *(undefined2 *)(iVar3 + 0x38) = 1;
    *(undefined2 *)(iVar3 + 0x34) = 1;
  }
  piVar5 = param_4;
  iVar3 = ((uint)*(ushort *)(*piVar1 + 0x36) - (uint)*(ushort *)(*piVar1 + 0x38)) + -7;
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  if (iVar3 < (int)(*(ushort *)(param_4 + 0xd) + 1)) {
    FUN_00477830(DAT_004ebfa4,param_2,0xe,param_4,1,bVar6);
    return 0;
  }
  *(undefined1 *)param_4[0x15] = (undefined1)param_3;
  iVar3 = *piVar1;
  iVar2 = param_4[0xd];
  if (*(ushort *)(iVar3 + 0x38) + 1 < (uint)*(ushort *)(iVar3 + 0x36)) {
    if (*(uint *)(iVar3 + 0x58) <= *(ushort *)(iVar3 + 0x34) + 1) {
      do {
        param_3 = param_3 & 0xffffff00;
        FUN_00414b10((void *)(iVar3 + 0x50),*(undefined1 **)(iVar3 + 0x58),(undefined1 *)&param_3,
                     &DAT_004ecc58);
      } while (*(uint *)(iVar3 + 0x58) <= *(ushort *)(iVar3 + 0x34) + 1);
    }
    uVar4 = (uint)*(ushort *)(iVar3 + 0x38);
    *(char *)(*(int *)(iVar3 + 0x54) + uVar4) = (char)iVar2;
    *(short *)(iVar3 + 0x38) = *(short *)(iVar3 + 0x38) + 1;
    *(short *)(iVar3 + 0x34) = *(short *)(iVar3 + 0x34) + 1;
    piVar5 = param_4;
  }
  else {
    FUN_004356e0();
    uVar4 = extraout_EDX;
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      uVar4 = extraout_EDX_00;
    }
    *(uint *)(iVar3 + 0x40) = *(uint *)(iVar3 + 0x40) | 4;
  }
  FUN_0046b480((void *)*piVar1,(undefined4 *)piVar5[0x15],
               CONCAT22((short)(uVar4 >> 0x10),(short)piVar5[0xd]));
  return 0;
}


/* 00477a90 size=86 */

void __cdecl FUN_00477a90(int param_1,undefined1 param_2,int *param_3)

{
  int iVar1;
  float *pfVar2;
  
  *(undefined1 *)param_3[0x15] = param_2;
  for (iVar1 = *(int *)(param_1 + 0x9fc); iVar1 != param_1 + 0x9f8; iVar1 = *(int *)(iVar1 + 4)) {
    pfVar2 = *(float **)(*(int *)(iVar1 + 8) + 0x3c8);
    if ((pfVar2 != (float *)0x0) && (*(int *)(*(int *)(iVar1 + 8) + 0x3b8) == 3)) {
      FUN_004657c0((void *)(param_1 + 0x8ec),param_3,pfVar2,0x80);
    }
  }
  return;
}


/* 00477af0 size=292 */

undefined4 * __cdecl FUN_00477af0(int param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  puVar5 = *(undefined4 **)(param_1 + 0xbfc);
  if (puVar5 == (undefined4 *)0x0) {
    FUN_004b7c60(param_1 + 0xbe4,*(int *)(param_1 + 0xbec));
    puVar5 = *(undefined4 **)(param_1 + 0xbfc);
    if (puVar5 == (undefined4 *)0x0) goto LAB_00477b21;
  }
  *(undefined4 *)(param_1 + 0xbfc) = *puVar5;
LAB_00477b21:
  puVar6 = puVar5;
  for (iVar4 = 0x59; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  puVar6 = puVar5 + 0x52;
  puVar5[0x53] = puVar6;
  *puVar6 = puVar6;
  puVar5[0x51] = 0;
  iVar4 = *(int *)(param_1 + 0x9fc);
  if (iVar4 == param_1 + 0x9f8) {
    *puVar5 = param_2;
    return puVar5;
  }
  do {
    iVar2 = *(int *)(iVar4 + 8);
    if (*(int *)(iVar2 + 0x3b8) == 3) {
      piVar3 = *(int **)(param_1 + 0xa8c);
      if (piVar3 == (int *)0x0) {
        FUN_004b7c60(param_1 + 0xa74,*(int *)(param_1 + 0xa7c));
        piVar3 = *(int **)(param_1 + 0xa8c);
        if (piVar3 != (int *)0x0) goto LAB_00477b86;
      }
      else {
LAB_00477b86:
        *(int *)(param_1 + 0xa8c) = *piVar3;
      }
      piVar1 = piVar3 + 3;
      piVar3[5] = (int)piVar3;
      *piVar1 = (int)(puVar5 + 0x52);
      puVar6 = (undefined4 *)puVar5[0x53];
      piVar3[4] = (int)puVar6;
      *puVar6 = piVar1;
      *(int **)(*piVar1 + 4) = piVar1;
      puVar5[0x51] = puVar5[0x51] + 1;
      piVar3[2] = (int)puVar5;
      *piVar3 = iVar2 + 0x3d0;
      puVar6 = *(undefined4 **)(iVar2 + 0x3d4);
      piVar3[1] = (int)puVar6;
      *puVar6 = piVar3;
      *(int **)(*piVar3 + 4) = piVar3;
      *(int *)(iVar2 + 0x3cc) = *(int *)(iVar2 + 0x3cc) + 1;
      puVar5[0x55] = puVar5[0x55] + 1;
    }
    iVar4 = *(int *)(iVar4 + 4);
    if (iVar4 == param_1 + 0x9f8) {
      *puVar5 = param_2;
      return puVar5;
    }
  } while( true );
}


/* 00477c20 size=1770 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_00477c20(undefined4 param_1,uint param_2,ushort *param_3,uint param_4,void *param_5)

{
  undefined1 uVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  ushort *puVar6;
  void *this;
  char cVar7;
  undefined4 in_EAX;
  int iVar8;
  byte *pbVar9;
  longlong lVar10;
  longlong lVar11;
  byte local_c [2];
  undefined2 local_a;
  undefined1 local_8;
  undefined2 local_6;
  char local_4;
  
  this = param_5;
  puVar6 = param_3;
  uVar5 = param_2;
  if (param_5 == (void *)0x0) {
    return;
  }
  uVar2 = *(ushort *)(param_2 + 0x34);
  param_5 = (void *)CONCAT22((short)((uint)in_EAX >> 0x10),uVar2);
  if ((uVar2 & 0x808) == 0) goto LAB_00477ce0;
  uVar3 = *(uint *)(param_2 + 0x34);
  if ((uVar3 & 8) == 0) {
    if ((uVar3 & 0x800) == 0) goto LAB_00477c6e;
    iVar8 = *(int *)(param_2 + 0x38);
  }
  else if (*(int *)(param_2 + 0x38) == 0) {
LAB_00477c6e:
    iVar8 = 0;
  }
  else {
    iVar8 = *(int *)(*(int *)(param_2 + 0x38) + 4);
  }
  if (iVar8 == *(int *)(param_4 + 0x3ac)) {
    param_5 = (void *)((uint)param_5 | 0x800);
    *param_3 = *param_3 & 0xfffd;
    goto LAB_00477ce0;
  }
  if ((uVar2 & 0x800) != 0) {
    if ((uVar3 & 8) == 0) {
      if ((uVar3 & 0x800) == 0) goto LAB_00477cb5;
      iVar8 = *(int *)(param_2 + 0x38);
    }
    else if (*(int *)(param_2 + 0x38) == 0) {
LAB_00477cb5:
      iVar8 = 0;
    }
    else {
      iVar8 = *(int *)(*(int *)(param_2 + 0x38) + 4);
    }
    *(undefined4 *)(param_2 + 0x50) = *(undefined4 *)(iVar8 + 0x194);
    *(undefined4 *)(param_2 + 0x54) = *(undefined4 *)(iVar8 + 0x198);
    *(undefined4 *)(param_2 + 0x58) = *(undefined4 *)(iVar8 + 0x19c);
    *(byte *)param_3 = (byte)*param_3 | 2;
  }
  param_5 = (void *)(uVar2 & 0xf7ff | 2);
LAB_00477ce0:
  FUN_004183a0(this,0);
  FUN_004183a0(this,1);
  FUN_004183a0(this,(char)*puVar6);
  FUN_004385b0(this,(short)*(undefined4 *)(*(int *)(uVar5 + 0xc) + 8));
  if ((*puVar6 & 1) != 0) {
    if (((*(uint *)(param_2 + 0x34) & 0x428) != 0) && ((*(uint *)(param_2 + 0x34) & 4) == 0)) {
      *(int *)(param_2 + 0x28) = *(int *)(param_2 + 0x28) + 1;
    }
    FUN_004385b0(this,*(undefined2 *)(*(int *)(param_2 + 0x14) + 8));
    lVar10 = __ftol();
    lVar11 = __ftol();
    cVar7 = (char)lVar11;
    if (cVar7 == -1) {
      cVar7 = -1;
    }
    pbVar9 = (byte *)FUN_004755f0(param_4,CONCAT22((short)((ulonglong)lVar11 >> 0x10),
                                                   *(undefined2 *)(*(int *)(param_2 + 0x14) + 8)));
    if (pbVar9 == (byte *)0x0) {
      local_c[0] = 7;
      pbVar9 = local_c;
    }
    else {
      local_a = (*(uint16_t*)((char*)&param_5+0));
      local_8 = *(undefined1 *)(param_2 + 0x3c);
      local_6 = (short)lVar10;
      local_4 = cVar7;
      FUN_00478310(pbVar9,(int)local_c);
    }
    FUN_004183a0(this,*pbVar9);
    if ((*pbVar9 & 1) != 0) {
      *pbVar9 = *pbVar9 & 0xfe;
      FUN_004385b0(this,(short)param_5);
    }
    if ((*pbVar9 & 2) != 0) {
      *pbVar9 = *pbVar9 & 0xfd;
      FUN_004183a0(this,*(undefined1 *)(param_2 + 0x3c));
    }
    if ((((uint)param_5 & 3) != 0) && ((*pbVar9 & 4) != 0)) {
      *pbVar9 = *pbVar9 & 0xfb;
      FUN_004385b0(this,(short)lVar10);
      FUN_004183a0(this,cVar7);
    }
    if (((uint)param_5 & 0x40) != 0) {
      FUN_004183a0(this,*(undefined1 *)(param_2 + 0x48));
    }
    if (((uint)param_5 & 0x80) != 0) {
      s_concommand_4757a0(this,*(undefined4 *)(param_2 + 0x4c));
    }
    if (((uint)param_5 & 0x400) != 0) {
      lVar10 = __ftol();
      if ((ushort)lVar10 < 0xff) {
        if (*(ushort *)((int)this + 0x38) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
          if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1) {
            do {
              param_4 = param_4 & 0xffffff00;
              FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                           (undefined1 *)&param_4,&DAT_004ecc58);
            } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1);
          }
          *(char *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = (char)lVar10
          ;
          *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 1;
          *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 1;
        }
        else {
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0)
            ;
          }
          *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
        }
      }
      else {
        if (*(ushort *)((int)this + 0x38) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
          if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1) {
            do {
              param_4 = param_4 & 0xffffff00;
              FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                           (undefined1 *)&param_4,&DAT_004ecc58);
            } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1);
          }
          *(undefined1 *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = 0xff;
          *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 1;
          *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 1;
        }
        else {
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0)
            ;
          }
          *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
        }
        if (*(ushort *)((int)this + 0x38) + 4 < (uint)*(ushort *)((int)this + 0x36)) {
          if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4) {
            do {
              param_4 = param_4 & 0xffffff00;
              FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                           (undefined1 *)&param_4,&DAT_004ecc58);
            } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4);
          }
          *(uint *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) =
               (uint)lVar10 & 0xffff;
          *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 4;
          *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 4;
        }
        else {
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0)
            ;
          }
          *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
        }
      }
    }
    if (((uint)param_5 & 0x2000) != 0) {
      uVar1 = *(undefined1 *)(param_2 + 0x60);
      if (*(ushort *)((int)this + 0x38) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
        if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1) {
          do {
            param_4 = param_4 & 0xffffff00;
            FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                         (undefined1 *)&param_4,&DAT_004ecc58);
          } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1);
        }
        *(undefined1 *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = uVar1;
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
    }
    if (((uint)param_5 & 0x4000) != 0) {
      uVar4 = *(undefined4 *)(param_2 + 100);
      if (*(ushort *)((int)this + 0x38) + 4 < (uint)*(ushort *)((int)this + 0x36)) {
        if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4) {
          do {
            param_4 = param_4 & 0xffffff00;
            FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                         (undefined1 *)&param_4,&DAT_004ecc58);
          } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4);
        }
        *(undefined4 *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = uVar4;
        *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 4;
        *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 4;
      }
      else {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
        }
        *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
      }
    }
  }
  puVar6 = param_3;
  if ((*param_3 & 2) != 0) {
    FUN_0043f380((int *)((int)this + 8));
  }
  if ((*puVar6 & 0x20) != 0) {
    lVar10 = __ftol();
    if (*(ushort *)((int)this + 0x38) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
      if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1) {
        do {
          param_2 = param_2 & 0xffffff00;
          FUN_00414b10((void *)((int)this + 0x50),*(undefined1 **)((int)this + 0x58),
                       (undefined1 *)&param_2,&DAT_004ecc58);
        } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 1);
      }
      *(char *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = (char)lVar10;
      *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 1;
      *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 1;
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


