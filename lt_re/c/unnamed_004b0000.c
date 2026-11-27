/* lithtech.exe decompilation - unnamed_004b0000 */
#include "ghidra_types.h"

/* 004b0040 size=17 */

int __thiscall FUN_004b0040(void *this,int param_1)

{
  FUN_004ae2c0((int)this,param_1);
  return;
}


/* 004b0060 size=25 */

void * __thiscall FUN_004b0060(void *this,short param_1)

{
  FUN_004ae450(this,(int)this,(int)param_1);
  return this;
}


/* 004b0080 size=18 */

bool __thiscall FUN_004b0080(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004b0040(this,param_1);
  return (bool)('\x01' - (iVar1 != 0));
}


/* 004b00a0 size=117 */

void * __thiscall FUN_004b00a0(void *this,void *param_1,int *param_2)

{
  int iVar1;
  int local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca2f8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  iVar1 = FUN_004af200(local_2c,(int)this);
  *param_2 = iVar1;
  FUN_004afb50(param_1,local_2c);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return param_1;
}


/* 004b0120 size=133 */

void * __thiscall
FUN_004b0120(void *this,void *param_1,void *param_2,void *param_3,void *param_4,short param_5)

{
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca318;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  BigInteger_4af410(local_2c,this,param_2,param_3,param_4,param_5,(uint *)0x0);
  FUN_004afb50(param_1,local_2c);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return param_1;
}


/* 004b01b0 size=156 */

int __fastcall FUN_004b01b0(int param_1)

{
  undefined1 *puVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004ca364;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)(param_1 + 0x1048) = 0;
  *(undefined4 *)(param_1 + 0x104c) = 0;
  *(undefined4 *)(param_1 + 0x1050) = 0;
  local_4 = 1;
  FUN_004a9380((undefined4 *)(param_1 + 0x1048),8);
  **(undefined1 **)(param_1 + 0x104c) = 0;
  *(undefined4 *)(param_1 + 0x1054) = 0;
  *(undefined4 *)(param_1 + 0x1058) = 0;
  *(undefined4 *)(param_1 + 0x105c) = 0;
  local_4 = 4;
  puVar1 = (undefined1 *)FUN_004aa520(8);
  *(undefined4 *)(param_1 + 0x1054) = puVar1;
  *(undefined1 **)(param_1 + 0x1058) = puVar1;
  *(undefined1 **)(param_1 + 0x105c) = puVar1 + 8;
  *puVar1 = 0;
  *(undefined1 *)(param_1 + 0x10a8) = 0;
  ExceptionList = local_c;
  return param_1;
}


/* 004b0250 size=705 */

/* FUN_004b0250: lifted from original x86 -> lt_lifted.c */


/* 004b0520 size=223 */

void __thiscall FUN_004b0520(void *this,uint param_1,uint param_2,int param_3,int param_4)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = (uint *)(param_1 + param_2 * 4);
  param_1 = *(uint *)(param_1 + 4 + param_2 * 4);
  param_2 = *puVar1 ^ *(uint *)((int)this + 0x1000);
  iVar2 = 0;
  puVar1 = (uint *)((int)this + 0x1000);
  do {
    param_1 = param_1 ^ (*(int *)((int)this + (param_2 >> 0x10 & 0xff) * 4 + 0x400) +
                         *(int *)((int)this + (param_2 >> 0x18) * 4) ^
                        *(uint *)((int)this + (param_2 >> 8 & 0xff) * 4 + 0x800)) +
                        *(int *)((int)this + (param_2 & 0xff) * 4 + 0xc00) ^ puVar1[1];
    iVar2 = iVar2 + 2;
    param_2 = param_2 ^ (*(int *)((int)this + (param_1 >> 0x10 & 0xff) * 4 + 0x400) +
                         *(int *)((int)this + (param_1 >> 0x18) * 4) ^
                        *(uint *)((int)this + (param_1 >> 8 & 0xff) * 4 + 0x800)) +
                        *(int *)((int)this + (param_1 & 0xff) * 4 + 0xc00) ^ puVar1[2];
    puVar1 = puVar1 + 2;
  } while (iVar2 < 0x10);
  *(uint *)(param_3 + param_4 * 4) = *(uint *)((int)this + 0x1044) ^ param_1;
  *(uint *)(param_3 + 4 + param_4 * 4) = param_2;
  return;
}


/* 004b0600 size=407 */

undefined1 __thiscall FUN_004b0600(void *this,int param_1)

{
  undefined4 uVar1;
  undefined1 local_ee;
  undefined1 local_ed;
  undefined4 *local_ec;
  undefined1 *local_e8;
  int local_e4;
  undefined4 **local_e0;
  undefined4 *local_dc [2];
  int local_d4;
  undefined4 *local_cc [2];
  int local_c4;
  undefined4 *local_24 [2];
  int local_1c;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca3ef;
  local_c = ExceptionList;
  if ((param_1 < 5) || (0x38 < param_1)) {
    local_ee = 0;
  }
  else {
    ExceptionList = &local_c;
    FUN_004b3220(local_dc);
    local_4 = 1;
    local_ee = 0;
    local_ec = (undefined4 *)0x0;
    local_e8 = (undefined1 *)0x0;
    FUN_004a93e0(&local_e4,&local_ed,0);
    (*(uint8_t*)((char*)&local_4+0)) = 2;
    FUN_004a9380(&local_ec,param_1 + 1);
    (*(uint8_t*)((char*)&local_4+0)) = 3;
    local_e8 = FUN_004b3b10((undefined1 *)local_ec,param_1,&local_ee);
    *local_e8 = 0;
    (*(uint8_t*)((char*)&local_4+0)) = 5;
    FUN_004b3450(local_dc,(int *)&local_ec);
    uVar1 = FUN_004b0250(this,local_ec,(int)local_e8 - (int)local_ec);
    local_ee = (undefined1)uVar1;
    local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),6);
    if (local_ec != (undefined4 *)0x0) {
      FUN_004aa6f0(local_ec,local_e4 - (int)local_ec);
    }
    local_e0 = local_24;
    local_4 = 9;
    FUN_004a9430(local_24[0],local_1c - (int)local_24[0]);
    local_e0 = local_cc;
    local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),10);
    FUN_004a9430(local_cc[0],local_c4 - (int)local_cc[0]);
    local_4 = 0xb;
    FUN_004a9430(local_dc[0],local_d4 - (int)local_dc[0]);
  }
  ExceptionList = local_c;
  return local_ee;
}


/* 004b07a0 size=163 */

undefined4 * __fastcall FUN_004b07a0(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca45c;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004b3220(param_1);
  local_4 = 0;
  FUN_004afb30(param_1 + 0x34);
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004afb30(param_1 + 0x3c);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004afb30(param_1 + 0x44);
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  FUN_004afb30(param_1 + 0x4c);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004afb30(param_1 + 0x54);
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  FUN_004afb30(param_1 + 0x5c);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),6);
  FUN_004b0930((int)param_1);
  ExceptionList = local_c;
  return param_1;
}


/* 004b0850 size=220 */

undefined4 * __thiscall FUN_004b0850(void *this,undefined4 *param_1,uint param_2,char param_3)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca4cc;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004b3220(this);
  local_4 = 0;
  FUN_004afb30((undefined4 *)((int)this + 0xd0));
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004afb30((undefined4 *)((int)this + 0xf0));
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004afb30((undefined4 *)((int)this + 0x110));
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  FUN_004afb30((undefined4 *)((int)this + 0x130));
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004afb30((undefined4 *)((int)this + 0x150));
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  FUN_004afb30((undefined4 *)((int)this + 0x170));
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),6);
  if (param_3 == '\0') {
    FUN_004b0b80(this,param_1,param_2);
    ExceptionList = local_c;
    return this;
  }
  FUN_004b0960(this,param_1,param_2);
  ExceptionList = local_c;
  return this;
}


/* 004b0930 size=15 */

void __fastcall FUN_004b0930(int param_1)

{
  *(undefined1 *)(param_1 + 0x198) = 0;
  *(undefined1 *)(param_1 + 0x199) = 0;
  return;
}


/* 004b0940 size=7 */

undefined1 __fastcall FUN_004b0940(int param_1)

{
  return *(undefined1 *)(param_1 + 0x198);
}


/* 004b0950 size=7 */

undefined1 __fastcall FUN_004b0950(int param_1)

{
  return *(undefined1 *)(param_1 + 0x199);
}


/* 004b0960 size=388 */

/* FUN_004b0960: lifted from original x86 -> lt_lifted.c */


/* 004b0af0 size=136 */

void __fastcall FUN_004b0af0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004ca51b;
  local_c = ExceptionList;
  puVar1 = (undefined4 *)*param_1;
  iVar2 = param_1[2];
  local_4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    if (0x80 < (uint)(iVar2 - (int)puVar1)) {
      ExceptionList = &local_c;
      FUN_00430df0((undefined *)puVar1);
      ExceptionList = local_c;
      return;
    }
    ExceptionList = &local_c;
    FUN_004a94b0(&DAT_004ed050);
    *puVar1 = *(undefined4 *)(&DAT_004ec644 + ((iVar2 - (int)puVar1) - 1U >> 3) * 4);
    *(undefined4 **)(&DAT_004ec644 + ((iVar2 - (int)puVar1) - 1U >> 3) * 4) = puVar1;
    DAT_004ed050 = 0;
  }
  ExceptionList = local_c;
  return;
}


/* 004b0b80 size=361 */

/* FUN_004b0b80: lifted from original x86 -> lt_lifted.c */


/* 004b0cf0 size=1154 */

/* WARNING: Variable defined which should be unmapped: param_2 */

undefined4 * __thiscall FUN_004b0cf0(void *param_1,undefined4 *param_2,int param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  undefined1 *puVar7;
  int iVar8;
  undefined1 local_b9;
  int local_b8;
  undefined1 local_b3;
  undefined1 local_b2;
  undefined1 local_b1;
  int local_b0;
  int local_ac;
  undefined4 *local_a8;
  undefined1 *local_a4;
  int local_a0;
  undefined4 local_9c;
  undefined4 *local_98;
  undefined1 *local_94;
  int local_90;
  undefined4 *local_8c;
  undefined1 *local_88;
  int local_84;
  undefined4 local_80 [5];
  undefined1 local_6c [32];
  undefined1 local_4c [32];
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca616;
  local_c = ExceptionList;
  local_9c = 0;
  ExceptionList = &local_c;
  cVar1 = FUN_004b0950((int)param_1);
  if (cVar1 == '\0') {
    *param_2 = 0;
  }
  else {
    iVar8 = *(int *)((int)param_1 + 0x194) + -3;
    iVar2 = param_4 / iVar8;
    if (param_4 % iVar8 != 0) {
      iVar2 = iVar2 + 1;
    }
    local_ac = iVar8;
    FUN_004ad1e0(local_80,0,1);
    (*(uint8_t*)((char*)&local_4+0)) = 1;
    (*(uint32_t*)((char*)&local_4+1)) = 0;
    FUN_004ad280(local_80,iVar2 * *(int *)((int)param_1 + 0x194) * 2 + 4);
    local_b8 = 0;
    FUN_004ad350(local_80,iVar2);
    if (0 < param_4) {
      do {
        local_b0 = iVar8;
        if (param_4 - local_b8 < local_ac) {
          local_b0 = param_4 - local_b8;
        }
        iVar8 = local_b0;
        uVar6 = *(uint *)((int)param_1 + 0x194);
        (*(uint8_t*)((char*)&local_4+0)) = 2;
        local_b9 = 0;
        FUN_004a89f0(&local_a8,&local_b2,uVar6);
        (*(uint8_t*)((char*)&local_4+0)) = 3;
        local_a4 = FUN_004b3b10((undefined1 *)local_a8,uVar6 - 1,&local_b9);
        *local_a4 = 0;
        (*(uint8_t*)((char*)&local_4+0)) = 5;
        iVar2 = (*(int *)((int)param_1 + 0x194) - iVar8) + -2;
        if (iVar2 < *(int *)((int)param_1 + 0x194) + -2) {
          puVar7 = (undefined1 *)(local_b8 + param_3);
          do {
            *(undefined1 *)(iVar2 + (int)local_a8) = *puVar7;
            iVar2 = iVar2 + 1;
            puVar7 = puVar7 + 1;
          } while (iVar2 < *(int *)((int)param_1 + 0x194) + -2);
        }
        *(char *)((int)local_a8 + *(int *)((int)param_1 + 0x194) + -2) = (char)iVar8;
        FUN_004bd127(local_6c,0x20,2,FUN_004afb30);
        (*(uint8_t*)((char*)&local_4+0)) = 6;
        puVar3 = FUN_004afbd0(local_2c,(int *)&local_a8);
        (*(uint8_t*)((char*)&local_4+0)) = 7;
        uVar4 = FUN_004b1ae0(param_1,puVar3,local_6c);
        FUN_004ad860(local_2c);
        if ((char)uVar4 == '\0') {
          *param_2 = 0;
          local_9c = 1;
          (*(uint8_t*)((char*)&local_4+0)) = 5;
          FUN_004bd049(local_6c,0x20,2,FUN_004ad860);
          (*(uint8_t*)((char*)&local_4+0)) = 8;
          FUN_004a93c0(&local_a8);
          goto LAB_004b1105;
        }
        (*(uint8_t*)((char*)&local_4+0)) = 9;
        FUN_004a89f0(&local_98,&local_b3,8);
        *local_94 = 0;
        (*(uint8_t*)((char*)&local_4+0)) = 0xb;
        FUN_004a89f0(&local_8c,&local_b1,8);
        *local_88 = 0;
        local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0xc);
        FUN_004ad910(local_6c,(int *)&local_98);
        FUN_004ad910(local_4c,(int *)&local_8c);
        uVar6 = *(uint *)((int)param_1 + 0x194);
        uVar5 = (int)local_94 - (int)local_98;
        if (uVar5 == uVar6) {
LAB_004b0f61:
          puVar3 = local_98;
          uVar6 = uVar5;
        }
        else {
          if (uVar5 <= uVar6) {
            if ((int)uVar5 < (int)uVar6) {
              do {
                FUN_004ad330(local_80,0);
                uVar5 = uVar5 + 1;
              } while ((int)uVar5 < *(int *)((int)param_1 + 0x194));
            }
            uVar5 = (int)local_94 - (int)local_98;
            goto LAB_004b0f61;
          }
          puVar3 = (undefined4 *)(local_94 + -uVar6);
        }
        FUN_004ad2f0(local_80,puVar3,uVar6);
        uVar6 = *(uint *)((int)param_1 + 0x194);
        uVar5 = (int)local_88 - (int)local_8c;
        if (uVar5 == uVar6) {
LAB_004b0fb2:
          puVar3 = local_8c;
          uVar6 = uVar5;
        }
        else {
          if (uVar5 <= uVar6) {
            if ((int)uVar5 < (int)uVar6) {
              do {
                FUN_004ad330(local_80,0);
                uVar5 = uVar5 + 1;
              } while ((int)uVar5 < *(int *)((int)param_1 + 0x194));
            }
            uVar5 = (int)local_88 - (int)local_8c;
            goto LAB_004b0fb2;
          }
          puVar3 = (undefined4 *)(local_88 + -uVar6);
        }
        FUN_004ad2f0(local_80,puVar3,uVar6);
        puVar3 = local_8c;
        local_b8 = local_b8 + local_b0;
        uVar6 = local_84 - (int)local_8c;
        (*(uint8_t*)((char*)&local_4+0)) = 0xd;
        if (local_8c != (undefined4 *)0x0) {
          if (uVar6 < 0x81) {
            FUN_004a94b0(&DAT_004ed050);
            *puVar3 = *(undefined4 *)(&DAT_004ec644 + (uVar6 - 1 >> 3) * 4);
            *(undefined4 **)(&DAT_004ec644 + (uVar6 - 1 >> 3) * 4) = puVar3;
            DAT_004ed050 = 0;
          }
          else {
            FUN_00430df0((undefined *)local_8c);
          }
        }
        puVar3 = local_98;
        uVar6 = local_90 - (int)local_98;
        (*(uint8_t*)((char*)&local_4+0)) = 0xe;
        if (local_98 != (undefined4 *)0x0) {
          if (uVar6 < 0x81) {
            FUN_004a94b0(&DAT_004ed050);
            *puVar3 = *(undefined4 *)(&DAT_004ec644 + (uVar6 - 1 >> 3) * 4);
            *(undefined4 **)(&DAT_004ec644 + (uVar6 - 1 >> 3) * 4) = puVar3;
            DAT_004ed050 = 0;
          }
          else {
            FUN_00430df0((undefined *)local_98);
          }
        }
        (*(uint8_t*)((char*)&local_4+0)) = 5;
        FUN_004bd049(local_6c,0x20,2,FUN_004ad860);
        puVar3 = local_a8;
        uVar6 = local_a0 - (int)local_a8;
        (*(uint8_t*)((char*)&local_4+0)) = 0xf;
        if (local_a8 != (undefined4 *)0x0) {
          if (uVar6 < 0x81) {
            FUN_004a94b0(&DAT_004ed050);
            *puVar3 = *(undefined4 *)(&DAT_004ec644 + (uVar6 - 1 >> 3) * 4);
            *(undefined4 **)(&DAT_004ec644 + (uVar6 - 1 >> 3) * 4) = puVar3;
            DAT_004ed050 = 0;
          }
          else {
            FUN_00430df0((undefined *)local_a8);
          }
        }
        (*(uint8_t*)((char*)&local_4+0)) = 1;
        if (param_4 <= local_b8) break;
        iVar8 = local_ac;
      } while( true );
    }
    FUN_004ad420(local_80,param_2,'\x01');
    local_9c = 1;
LAB_004b1105:
    local_4 = (uint)(*(uint32_t*)((char*)&local_4+1)) << 8;
    FUN_004ad230(local_80);
  }
  ExceptionList = local_c;
  return param_2;
}


/* 004b1180 size=1231 */

/* WARNING: Variable defined which should be unmapped: param_2 */

undefined4 * __thiscall
FUN_004b1180(void *param_1,undefined4 *param_2,undefined4 *param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  undefined1 local_ae;
  undefined1 local_ad;
  undefined4 local_ac;
  int local_a8;
  undefined4 *local_a4;
  undefined1 *local_a0;
  int local_9c;
  undefined4 *local_98;
  undefined1 *local_94;
  int local_90;
  undefined4 *local_8c;
  undefined4 *local_88;
  int local_84;
  undefined4 local_80 [5];
  undefined4 local_6c [8];
  undefined4 local_4c [8];
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca72b;
  local_c = ExceptionList;
  local_ac = 0;
  ExceptionList = &local_c;
  cVar3 = FUN_004b0940((int)param_1);
  if (cVar3 == '\0') {
    *param_2 = 0;
  }
  else {
    iVar7 = 4;
    if (param_4 < 4) {
      *param_2 = 0;
    }
    else {
      iVar4 = FUN_004aa830(*param_3);
      iVar2 = *(int *)((int)param_1 + 0x194);
      if (param_4 + -4 < iVar2 * iVar4 * 2 + -4) {
        *param_2 = 0;
      }
      else {
        local_4 = 1;
        local_ae = 0;
        FUN_004a89f0(&local_a4,&local_ad,iVar2 + 1);
        (*(uint8_t*)((char*)&local_4+0)) = 2;
        local_a0 = FUN_004b3b10((undefined1 *)local_a4,iVar2,&local_ae);
        *local_a0 = 0;
        iVar2 = *(int *)((int)param_1 + 0x194);
        (*(uint8_t*)((char*)&local_4+0)) = 5;
        local_ae = 0;
        FUN_004a89f0(&local_98,&local_ad,iVar2 + 1);
        (*(uint8_t*)((char*)&local_4+0)) = 6;
        local_94 = FUN_004b3b10((undefined1 *)local_98,iVar2,&local_ae);
        *local_94 = 0;
        (*(uint8_t*)((char*)&local_4+0)) = 8;
        FUN_004ad1e0(local_80,0,1);
        (*(uint8_t*)((char*)&local_4+0)) = 9;
        FUN_004afb30(local_2c);
        (*(uint8_t*)((char*)&local_4+0)) = 10;
        FUN_004afb30(local_6c);
        (*(uint8_t*)((char*)&local_4+0)) = 0xb;
        FUN_004afb30(local_4c);
        local_a8 = 0;
        if (0 < iVar4) {
          do {
            (*(uint8_t*)((char*)&local_4+0)) = 0xc;
            FUN_004ab7f0(&local_a4,(undefined4 *)(iVar7 + (int)param_3),
                         (undefined4 *)(*(int *)((int)param_1 + 0x194) + iVar7 + (int)param_3));
            iVar7 = iVar7 + *(int *)((int)param_1 + 0x194);
            puVar1 = (undefined4 *)(iVar7 + (int)param_3);
            FUN_004ab7f0(&local_98,puVar1,
                         (undefined4 *)(*(int *)((int)param_1 + 0x194) + (int)puVar1));
            iVar7 = iVar7 + *(int *)((int)param_1 + 0x194);
            FUN_004ada70(local_2c,(int *)&local_a4);
            FUN_004ada70(local_6c,(int *)&local_98);
            uVar5 = FUN_004b1cb0(param_1,local_2c,local_6c,local_4c);
            if ((char)uVar5 == '\0') {
              local_ac = 1;
              *param_2 = 0;
              FUN_004ad860(local_4c);
              FUN_004ad860(local_6c);
              FUN_004ad860(local_2c);
              (*(uint8_t*)((char*)&local_4+0)) = 8;
              FUN_004ad230(local_80);
              local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0xd);
              FUN_004a93c0(&local_98);
              local_4 = 0xe;
              FUN_004a93c0(&local_a4);
              ExceptionList = local_c;
              return param_2;
            }
            (*(uint8_t*)((char*)&local_4+0)) = 0xf;
            FUN_004a89f0(&local_8c,&local_ae,8);
            *(undefined1 *)local_88 = 0;
            (*(uint8_t*)((char*)&local_4+0)) = 0x10;
            FUN_004ad910(local_4c,(int *)&local_8c);
            if (local_88 == local_8c) {
              local_ac = 1;
              *param_2 = 0;
              (*(uint8_t*)((char*)&local_4+0)) = 0x11;
              FUN_004a93c0(&local_8c);
              FUN_004ad860(local_4c);
              FUN_004ad860(local_6c);
              FUN_004ad860(local_2c);
              (*(uint8_t*)((char*)&local_4+0)) = 8;
              FUN_004ad230(local_80);
              local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0x12);
              FUN_004a93c0(&local_98);
              local_4 = 0x13;
              FUN_004a93c0(&local_a4);
              ExceptionList = local_c;
              return param_2;
            }
            uVar6 = (uint)*(byte *)((int)local_88 + -1);
            if (*(int *)((int)param_1 + 0x194) + -3 < (int)uVar6) {
              local_ac = 1;
              *param_2 = 0;
              (*(uint8_t*)((char*)&local_4+0)) = 0x14;
              FUN_004a93c0(&local_8c);
              FUN_004ad860(local_4c);
              FUN_004ad860(local_6c);
              FUN_004ad860(local_2c);
              (*(uint8_t*)((char*)&local_4+0)) = 8;
              FUN_004ad230(local_80);
              local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0x15);
              FUN_004a93c0(&local_98);
              local_4 = 0x16;
              FUN_004a93c0(&local_a4);
              ExceptionList = local_c;
              return param_2;
            }
            FUN_004ad2f0(local_80,(undefined4 *)((int)local_88 + (-1 - uVar6)),uVar6);
            (*(uint8_t*)((char*)&local_4+0)) = 0x17;
            FUN_004a9430(local_8c,local_84 - (int)local_8c);
            local_a8 = local_a8 + 1;
          } while (local_a8 < iVar4);
        }
        (*(uint8_t*)((char*)&local_4+0)) = 0xc;
        FUN_004ad420(local_80,param_2,'\x01');
        local_ac = 1;
        FUN_004ad860(local_4c);
        FUN_004ad860(local_6c);
        FUN_004ad860(local_2c);
        (*(uint8_t*)((char*)&local_4+0)) = 8;
        FUN_004ad230(local_80);
        local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0x18);
        FUN_004a9430(local_98,local_90 - (int)local_98);
        local_4 = 0x19;
        FUN_004a9430(local_a4,local_9c - (int)local_a4);
      }
    }
  }
  ExceptionList = local_c;
  return param_2;
}


/* 004b1650 size=385 */

/* FUN_004b1650: lifted from original x86 -> lt_lifted.c */


/* 004b17e0 size=756 */

undefined1 __thiscall
FUN_004b17e0(void *this,undefined4 *param_1,int param_2,undefined4 *param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined1 uVar7;
  undefined4 *puVar8;
  undefined1 local_13e;
  undefined1 local_13d;
  undefined4 *local_13c;
  undefined4 *local_138;
  int local_134;
  undefined4 *local_130;
  undefined1 *local_12c;
  int local_128;
  undefined4 *local_120 [2];
  int local_118;
  undefined4 local_114 [8];
  undefined4 local_f4 [8];
  undefined4 local_d4 [8];
  undefined4 local_b4 [42];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca815;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  cVar1 = FUN_004b0950((int)this);
  uVar7 = 0;
  if (cVar1 != '\0') {
    iVar4 = (int)this + 0xf0;
    iVar2 = FUN_004ad560(iVar4);
    if (param_4 == iVar2 * 2) {
      FUN_004b22f0(local_b4);
      local_4 = 0;
      FUN_004b2760(local_b4,param_1,param_2);
      FUN_004b23a0(local_b4,local_120);
      (*(uint8_t*)((char*)&local_4+0)) = 1;
      FUN_004afb30(local_114);
      (*(uint8_t*)((char*)&local_4+0)) = 2;
      uVar3 = FUN_004b1650(this,(int *)local_120,local_114);
      if ((char)uVar3 == '\0') {
        FUN_004ad860(local_114);
        local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),3);
        FUN_004a93c0(local_120);
        local_4 = 0xffffffff;
        FUN_004a8b90(local_b4);
        uVar7 = 0;
      }
      else {
        (*(uint8_t*)((char*)&local_4+0)) = 4;
        local_13e = 0;
        iVar2 = FUN_004ad560(iVar4);
        FUN_004a89f0(&local_130,&local_13d,iVar2 + 1);
        (*(uint8_t*)((char*)&local_4+0)) = 5;
        local_12c = FUN_004b3b10((undefined1 *)local_130,iVar2,&local_13e);
        *local_12c = 0;
        (*(uint8_t*)((char*)&local_4+0)) = 8;
        local_13e = 0;
        iVar4 = FUN_004ad560(iVar4);
        FUN_004a89f0(&local_13c,&local_13d,iVar4 + 1);
        (*(uint8_t*)((char*)&local_4+0)) = 9;
        local_138 = (undefined4 *)FUN_004b3b10((undefined1 *)local_13c,iVar4,&local_13e);
        *(undefined1 *)local_138 = 0;
        local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0xb);
        FUN_004ab7f0(&local_130,param_3,
                     (undefined4 *)(((int)local_12c - (int)local_130) + (int)param_3));
        puVar5 = (undefined4 *)(((int)local_12c - (int)local_130) + (int)param_3);
        puVar6 = (undefined4 *)(((int)local_138 - (int)local_13c) + (int)puVar5);
        puVar8 = local_13c;
        for (; puVar5 != puVar6; puVar5 = (undefined4 *)((int)puVar5 + 1)) {
          if (puVar8 == local_138) {
            if (puVar5 != puVar6) {
              FUN_004ab7d0(&local_13c,puVar5,puVar6);
              goto LAB_004b19e7;
            }
            break;
          }
          *(undefined1 *)puVar8 = *(undefined1 *)puVar5;
          puVar8 = (undefined4 *)((int)puVar8 + 1);
        }
        FUN_004a89b0(&local_13c,puVar8,local_138);
LAB_004b19e7:
        FUN_004afbd0(local_f4,(int *)&local_130);
        (*(uint8_t*)((char*)&local_4+0)) = 0xc;
        FUN_004afbd0(local_d4,(int *)&local_13c);
        (*(uint8_t*)((char*)&local_4+0)) = 0xd;
        uVar3 = FUN_004b1d90(this,local_114,local_f4,(int)local_d4);
        FUN_004ad860(local_d4);
        FUN_004ad860(local_f4);
        (*(uint8_t*)((char*)&local_4+0)) = 0xe;
        FUN_004a9430(local_13c,local_134 - (int)local_13c);
        (*(uint8_t*)((char*)&local_4+0)) = 0xf;
        FUN_004a9430(local_130,local_128 - (int)local_130);
        FUN_004ad860(local_114);
        local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0x10);
        FUN_004a9430(local_120[0],local_118 - (int)local_120[0]);
        local_4 = 0xffffffff;
        FUN_004a8b90(local_b4);
        uVar7 = (undefined1)uVar3;
      }
    }
    else {
      uVar7 = 0;
    }
  }
  ExceptionList = local_c;
  return uVar7;
}


/* 004b1ae0 size=427 */

/* FUN_004b1ae0: lifted from original x86 -> lt_lifted.c */


/* 004b1cb0 size=184 */

/* FUN_004b1cb0: lifted from original x86 -> lt_lifted.c */


/* 004b1d90 size=413 */

/* FUN_004b1d90: lifted from original x86 -> lt_lifted.c */


/* 004b1f40 size=207 */

int * __thiscall
FUN_004b1f40(void *this,undefined4 *param_1,uint param_2,undefined4 param_3,char param_4)

{
  uint uVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004ca908;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  local_4 = 1;
  uVar1 = param_2 + 1;
  if (uVar1 == 0) {
    FUN_004a5b30(s_basic_string_004de5c8);
  }
  else {
    iVar4 = FUN_004aa520(uVar1);
    *(int *)this = iVar4;
    *(int *)((int)this + 4) = iVar4;
    *(uint *)((int)this + 8) = iVar4 + uVar1;
  }
  puVar3 = *(undefined4 **)this;
  FUN_004bab10(puVar3,param_1,param_2);
  puVar2 = (undefined1 *)((int)puVar3 + (param_2 - (int)param_1));
  *(undefined1 **)((int)this + 4) = puVar2;
  *puVar2 = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined1 *)((int)this + 0x10) = 1;
  if ((param_4 != '\0') && (iVar4 = FUN_004b2010(this), (char)iVar4 == '0')) {
    FUN_004b2060(this);
  }
  ExceptionList = puStack_8;
  return this;
}


/* 004b2010 size=34 */

/* FUN_004b2010: lifted from original x86 -> lt_lifted.c */


/* 004b2040 size=27 */

/* FUN_004b2040: lifted from original x86 -> lt_lifted.c */


/* 004b2060 size=91 */

undefined1 __fastcall FUN_004b2060(int *param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = FUN_004b2010(param_1);
  if ((uVar2 & 0x80) == 0) {
LAB_004b20b0:
    return (char)param_1[4];
  }
  uVar2 = uVar2 & 0x7f;
  if (uVar2 <= (uint)((param_1[1] - param_1[3]) - *param_1)) {
    iVar3 = FUN_004b2010(param_1);
    cVar1 = (char)iVar3;
    for (; (cVar1 == '\0' && (1 < (int)uVar2)); uVar2 = uVar2 - 1) {
      iVar3 = FUN_004b2010(param_1);
      cVar1 = (char)iVar3;
    }
    if (uVar2 != 0) {
      if (uVar2 != 1) {
        if (uVar2 != 2) {
          return 0;
        }
        FUN_004b2010(param_1);
      }
      goto LAB_004b20b0;
    }
  }
  return 0;
}


/* 004b20c0 size=89 */

/* FUN_004b20c0: lifted from original x86 -> lt_lifted.c */


/* 004b2119 size=287 */

/* FUN_004b2119: lifted from original x86 -> lt_lifted.c */


/* 004b2240 size=161 */

uint __fastcall FUN_004b2240(int *param_1)

{
  uint in_EAX;
  uint uVar1;
  uint uVar2;
  
  if ((char)param_1[4] == '\0') {
    return in_EAX & 0xffffff00;
  }
  uVar1 = FUN_004b2010(param_1);
  if ((char)uVar1 != '\x02') {
    return uVar1 & 0xffffff00;
  }
  uVar1 = FUN_004b2040(param_1);
  if ((uVar1 & 0x80) == 0) {
    uVar1 = FUN_004b2010(param_1);
    uVar1 = FUN_004b20c0(param_1,uVar1 & 0xff);
    return uVar1;
  }
  uVar1 = FUN_004b2010(param_1);
  if (2 < (uVar1 & 0x7f)) {
    return 0;
  }
  uVar2 = FUN_004b2010(param_1);
  uVar2 = uVar2 & 0xff;
  if (1 < (uVar1 & 0x7f)) {
    uVar1 = FUN_004b2010(param_1);
    uVar2 = uVar2 << 8 | uVar1 & 0xff;
  }
  uVar1 = FUN_004b20c0(param_1,uVar2);
  return uVar1;
}


/* 004b22f0 size=119 */

undefined4 * __fastcall FUN_004b22f0(undefined4 *param_1)

{
  undefined1 *puVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004ca96b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_4 = 1;
  puVar1 = (undefined1 *)FUN_004aa520(8);
  *param_1 = puVar1;
  param_1[1] = puVar1;
  param_1[2] = puVar1 + 8;
  *puVar1 = 0;
  local_4 = 4;
  FUN_004b2370((int)param_1);
  ExceptionList = local_c;
  return param_1;
}


/* 004b2370 size=43 */

void __fastcall FUN_004b2370(int param_1)

{
  *(undefined4 *)(param_1 + 0x4c) = 0x67452301;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0xefcdab89;
  *(undefined4 *)(param_1 + 0x54) = 0x98badcfe;
  *(undefined4 *)(param_1 + 0x58) = 0x10325476;
  return;
}


/* 004b23a0 size=310 */

undefined4 * __thiscall FUN_004b23a0(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined1 local_25;
  int local_24 [3];
  undefined4 *local_18;
  int local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca9b7;
  local_c = ExceptionList;
  local_24[2] = 0;
  ExceptionList = &local_c;
  uVar2 = FUN_004a8710(&local_25);
  local_4 = 1;
  local_18 = (undefined4 *)0x0;
  local_14 = 0;
  FUN_004a93e0(&local_10,uVar2,0);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),3);
  FUN_004ab770(&local_18,*(undefined1 **)this,*(int *)((int)this + 4));
  puVar1 = *(undefined4 **)this;
  local_4 = 4;
  local_24[0] = *(int *)((int)this + 4) - (int)puVar1;
  local_24[1] = 0xffffffff;
  piVar4 = local_24;
  if (local_24[0] == -1) {
    piVar4 = local_24 + 1;
  }
  puVar5 = (undefined4 *)(*piVar4 + (int)puVar1);
  if (puVar1 != puVar5) {
    FUN_004bab10(puVar1,puVar5,(*(int *)((int)this + 4) - (int)puVar5) + 1);
    *(int *)((int)this + 4) = (*(int *)((int)this + 4) - (int)puVar5) + (int)puVar1;
  }
  FUN_004b2510(this,param_1,&local_18,local_14 - (int)local_18);
  puVar1 = local_18;
  local_24[2] = 1;
  uVar3 = local_10 - (int)local_18;
  local_4 = 5;
  if (local_18 != (undefined4 *)0x0) {
    if (uVar3 < 0x81) {
      FUN_004a94b0(&DAT_004ed050);
      *puVar1 = *(undefined4 *)(&DAT_004ec644 + (uVar3 - 1 >> 3) * 4);
      *(undefined4 **)(&DAT_004ec644 + (uVar3 - 1 >> 3) * 4) = puVar1;
      DAT_004ed050 = 0;
    }
    else {
      FUN_00430df0((undefined *)local_18);
    }
  }
  ExceptionList = local_c;
  return param_1;
}


/* 004b24e0 size=43 */

undefined4 * __thiscall FUN_004b24e0(void *this,undefined4 *param_1,undefined4 *param_2)

{
  FUN_004b2740(this,param_2);
  FUN_004b23a0(this,param_1);
  return param_1;
}


/* 004b2510 size=548 */

undefined4 * __thiscall
FUN_004b2510(void *this,undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  undefined4 *local_18;
  undefined1 *local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004caa17;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  if (param_3 != 0) {
    puVar6 = (undefined4 *)*param_2;
    puVar7 = (undefined4 *)((int)this + 0x5c);
    ExceptionList = &local_c;
    for (uVar5 = param_3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (uVar5 = param_3 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
  }
  *(undefined1 *)(param_3 + 0x5c + (int)this) = 0x80;
  iVar2 = param_3 + 1;
  if (iVar2 < 0x39) {
    if (0x37 < iVar2) goto LAB_004b25bd;
  }
  else {
    if (iVar2 < 0x40) {
      puVar6 = (undefined4 *)(param_3 + 0x5d + (int)this);
      for (uVar5 = 0x40U - iVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      }
      for (uVar5 = 0x40U - iVar2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined1 *)puVar6 = 0;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      }
    }
    FUN_004b31c0((int)this + 0x5c,0,(int)this + 0xc,0,0x10);
    FUN_004b2980(this,(int *)((int)this + 0xc));
    iVar2 = 0;
  }
  puVar6 = (undefined4 *)(iVar2 + 0x5c + (int)this);
  for (uVar5 = 0x38U - iVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  for (uVar5 = 0x38U - iVar2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined1 *)puVar6 = 0;
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
LAB_004b25bd:
  FUN_004b31c0((int)this + 0x5c,0,(int)this + 0xc,0,0xe);
  *(undefined4 *)((int)this + 0x44) = *(undefined4 *)((int)this + 0xa0);
  uVar8 = __allshr(0x20,*(int *)((int)this + 0xa4));
  *(int *)((int)this + 0x48) = (int)uVar8;
  FUN_004b2980(this,(int *)((int)this + 0xc));
  local_4 = 1;
  param_3 = param_3 & 0xffffff00;
  local_18 = (undefined4 *)0x0;
  local_14 = (undefined1 *)0x0;
  FUN_004a93e0(&local_10,&param_2,0);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004a9380(&local_18,0x11);
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  local_14 = FUN_004b3b10((undefined1 *)local_18,0x10,(undefined1 *)&param_3);
  *local_14 = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  iVar2 = 0;
  puVar6 = (undefined4 *)((int)this + 0x4c);
  param_3 = 4;
  do {
    uVar1 = *puVar6;
    puVar6 = puVar6 + 1;
    *(char *)(iVar2 + (int)local_18) = (char)uVar1;
    *(char *)(iVar2 + 1 + (int)local_18) = (char)((uint)uVar1 >> 8);
    iVar3 = iVar2 + 3;
    *(char *)(iVar2 + 2 + (int)local_18) = (char)((uint)uVar1 >> 0x10);
    iVar2 = iVar2 + 4;
    *(char *)(iVar3 + (int)local_18) = (char)((uint)uVar1 >> 0x18);
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  FUN_004b2370((int)this);
  FUN_004a8710(&param_3);
  puVar4 = local_14;
  puVar6 = local_18;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),6);
  FUN_004a9380(param_1,(uint)(local_14 + (1 - (int)local_18)));
  puVar4 = (undefined1 *)FUN_004aca30((int)puVar6,(int)puVar4,(undefined1 *)*param_1);
  param_1[1] = puVar4;
  *puVar4 = 0;
  local_4 = 7;
  if (local_18 != (undefined4 *)0x0) {
    FUN_004aa6f0(local_18,local_10 - (int)local_18);
  }
  ExceptionList = local_c;
  return param_1;
}


/* 004b2740 size=21 */

void __thiscall FUN_004b2740(void *this,undefined4 *param_1)

{
  FUN_004b2760(this,(undefined4 *)*param_1,param_1[1] - (int)*param_1);
  return;
}


/* 004b2760 size=254 */

void __thiscall FUN_004b2760(void *this,undefined4 *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  ulonglong uVar5;
  
  iVar2 = 0;
  uVar3 = param_2 * 8;
  uVar1 = *(uint *)((int)this + 0xa0);
  *(uint *)((int)this + 0xa0) = uVar3 + uVar1;
  *(uint *)((int)this + 0xa4) =
       ((int)uVar3 >> 0x1f) + *(int *)((int)this + 0xa4) + (uint)CARRY4(uVar3,uVar1);
  uVar5 = __allshr(3,0);
  uVar3 = (uint)uVar5 & 0x3f;
  if ((uVar5 & 0x3f) != 0) {
    if ((int)(uVar3 + param_2) < 0x40) {
      FUN_004ac050(this,param_1,(undefined4 *)((int)param_1 + param_2));
      return;
    }
    FUN_004ac050(this,param_1,(undefined4 *)((int)param_1 + (0x40 - uVar3)));
    FUN_004b2960(this);
    iVar2 = 0x40 - uVar3;
    param_2 = uVar3 + param_2 + -0x40;
  }
  if (0x3f < param_2) {
    puVar4 = (undefined4 *)(iVar2 + (int)param_1);
    do {
      FUN_004ac050(this,puVar4,puVar4 + 0x10);
      FUN_004b2960(this);
      param_2 = param_2 + -0x40;
      iVar2 = iVar2 + 0x40;
      puVar4 = puVar4 + 0x10;
    } while (0x3f < param_2);
  }
  FUN_004ac050(this,(undefined4 *)(iVar2 + (int)param_1),
               (undefined4 *)(iVar2 + (int)param_1 + param_2));
  return;
}


/* 004b2860 size=61 */

int __cdecl
FUN_004b2860(int param_1,uint param_2,uint param_3,uint param_4,int param_5,byte param_6,int param_7
            )

{
  uint uVar1;
  
  uVar1 = param_1 + ((param_3 ^ param_4) & param_2 ^ param_4) + param_5 + param_7;
  return (uVar1 >> (-param_6 & 0x1f) | uVar1 << (param_6 & 0x1f)) + param_2;
}


/* 004b28a0 size=63 */

int __cdecl
FUN_004b28a0(int param_1,uint param_2,uint param_3,uint param_4,int param_5,byte param_6,int param_7
            )

{
  uint uVar1;
  
  uVar1 = param_1 + ((param_2 ^ param_3) & param_4 ^ param_3) + param_5 + param_7;
  return (uVar1 >> (-param_6 & 0x1f) | uVar1 << (param_6 & 0x1f)) + param_2;
}


/* 004b28e0 size=61 */

int __cdecl
FUN_004b28e0(int param_1,uint param_2,uint param_3,uint param_4,int param_5,byte param_6,int param_7
            )

{
  uint uVar1;
  
  uVar1 = param_1 + (param_2 ^ param_3 ^ param_4) + param_5 + param_7;
  return (uVar1 >> (-param_6 & 0x1f) | uVar1 << (param_6 & 0x1f)) + param_2;
}


/* 004b2920 size=61 */

int __cdecl
FUN_004b2920(int param_1,uint param_2,uint param_3,uint param_4,int param_5,byte param_6,int param_7
            )

{
  uint uVar1;
  
  uVar1 = param_1 + ((~param_4 | param_2) ^ param_3) + param_5 + param_7;
  return (uVar1 >> (-param_6 & 0x1f) | uVar1 << (param_6 & 0x1f)) + param_2;
}


/* 004b2960 size=21 */

void __fastcall FUN_004b2960(int *param_1)

{
  FUN_004b3150(param_1);
  FUN_004b2980(param_1,param_1 + 3);
  return;
}


/* 004b2980 size=1987 */

void __thiscall FUN_004b2980(void *this,int *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar2 = *(uint *)((int)this + 0x58);
  uVar3 = *(uint *)((int)this + 0x54);
  uVar4 = *(uint *)((int)this + 0x50);
  uVar1 = FUN_004b2860(*(int *)((int)this + 0x4c),uVar4,uVar3,uVar2,*param_1,7,-0x28955b88);
  uVar2 = FUN_004b2860(uVar2,uVar1,uVar4,uVar3,param_1[1],0xc,-0x173848aa);
  uVar3 = FUN_004b2860(uVar3,uVar2,uVar1,uVar4,param_1[2],0x11,0x242070db);
  uVar4 = FUN_004b2860(uVar4,uVar3,uVar2,uVar1,param_1[3],0x16,-0x3e423112);
  uVar1 = FUN_004b2860(uVar1,uVar4,uVar3,uVar2,param_1[4],7,-0xa83f051);
  uVar2 = FUN_004b2860(uVar2,uVar1,uVar4,uVar3,param_1[5],0xc,0x4787c62a);
  uVar3 = FUN_004b2860(uVar3,uVar2,uVar1,uVar4,param_1[6],0x11,-0x57cfb9ed);
  uVar4 = FUN_004b2860(uVar4,uVar3,uVar2,uVar1,param_1[7],0x16,-0x2b96aff);
  uVar1 = FUN_004b2860(uVar1,uVar4,uVar3,uVar2,param_1[8],7,0x698098d8);
  uVar2 = FUN_004b2860(uVar2,uVar1,uVar4,uVar3,param_1[9],0xc,-0x74bb0851);
  uVar3 = FUN_004b2860(uVar3,uVar2,uVar1,uVar4,param_1[10],0x11,-0xa44f);
  uVar4 = FUN_004b2860(uVar4,uVar3,uVar2,uVar1,param_1[0xb],0x16,-0x76a32842);
  uVar1 = FUN_004b2860(uVar1,uVar4,uVar3,uVar2,param_1[0xc],7,0x6b901122);
  uVar2 = FUN_004b2860(uVar2,uVar1,uVar4,uVar3,param_1[0xd],0xc,-0x2678e6d);
  uVar3 = FUN_004b2860(uVar3,uVar2,uVar1,uVar4,param_1[0xe],0x11,-0x5986bc72);
  uVar4 = FUN_004b2860(uVar4,uVar3,uVar2,uVar1,param_1[0xf],0x16,0x49b40821);
  uVar1 = FUN_004b28a0(uVar1,uVar4,uVar3,uVar2,param_1[1],5,-0x9e1da9e);
  uVar2 = FUN_004b28a0(uVar2,uVar1,uVar4,uVar3,param_1[6],9,-0x3fbf4cc0);
  uVar3 = FUN_004b28a0(uVar3,uVar2,uVar1,uVar4,param_1[0xb],0xe,0x265e5a51);
  uVar4 = FUN_004b28a0(uVar4,uVar3,uVar2,uVar1,*param_1,0x14,-0x16493856);
  uVar1 = FUN_004b28a0(uVar1,uVar4,uVar3,uVar2,param_1[5],5,-0x29d0efa3);
  uVar2 = FUN_004b28a0(uVar2,uVar1,uVar4,uVar3,param_1[10],9,0x2441453);
  uVar3 = FUN_004b28a0(uVar3,uVar2,uVar1,uVar4,param_1[0xf],0xe,-0x275e197f);
  uVar4 = FUN_004b28a0(uVar4,uVar3,uVar2,uVar1,param_1[4],0x14,-0x182c0438);
  uVar1 = FUN_004b28a0(uVar1,uVar4,uVar3,uVar2,param_1[9],5,0x21e1cde6);
  uVar2 = FUN_004b28a0(uVar2,uVar1,uVar4,uVar3,param_1[0xe],9,-0x3cc8f82a);
  uVar3 = FUN_004b28a0(uVar3,uVar2,uVar1,uVar4,param_1[3],0xe,-0xb2af279);
  uVar4 = FUN_004b28a0(uVar4,uVar3,uVar2,uVar1,param_1[8],0x14,0x455a14ed);
  uVar1 = FUN_004b28a0(uVar1,uVar4,uVar3,uVar2,param_1[0xd],5,-0x561c16fb);
  uVar2 = FUN_004b28a0(uVar2,uVar1,uVar4,uVar3,param_1[2],9,-0x3105c08);
  uVar3 = FUN_004b28a0(uVar3,uVar2,uVar1,uVar4,param_1[7],0xe,0x676f02d9);
  uVar4 = FUN_004b28a0(uVar4,uVar3,uVar2,uVar1,param_1[0xc],0x14,-0x72d5b376);
  uVar1 = FUN_004b28e0(uVar1,uVar4,uVar3,uVar2,param_1[5],4,-0x5c6be);
  uVar2 = FUN_004b28e0(uVar2,uVar1,uVar4,uVar3,param_1[8],0xb,-0x788e097f);
  uVar3 = FUN_004b28e0(uVar3,uVar2,uVar1,uVar4,param_1[0xb],0x10,0x6d9d6122);
  uVar4 = FUN_004b28e0(uVar4,uVar3,uVar2,uVar1,param_1[0xe],0x17,-0x21ac7f4);
  uVar1 = FUN_004b28e0(uVar1,uVar4,uVar3,uVar2,param_1[1],4,-0x5b4115bc);
  uVar2 = FUN_004b28e0(uVar2,uVar1,uVar4,uVar3,param_1[4],0xb,0x4bdecfa9);
  uVar3 = FUN_004b28e0(uVar3,uVar2,uVar1,uVar4,param_1[7],0x10,-0x944b4a0);
  uVar4 = FUN_004b28e0(uVar4,uVar3,uVar2,uVar1,param_1[10],0x17,-0x41404390);
  uVar1 = FUN_004b28e0(uVar1,uVar4,uVar3,uVar2,param_1[0xd],4,0x289b7ec6);
  uVar2 = FUN_004b28e0(uVar2,uVar1,uVar4,uVar3,*param_1,0xb,-0x155ed806);
  uVar3 = FUN_004b28e0(uVar3,uVar2,uVar1,uVar4,param_1[3],0x10,-0x2b10cf7b);
  uVar4 = FUN_004b28e0(uVar4,uVar3,uVar2,uVar1,param_1[6],0x17,0x4881d05);
  uVar1 = FUN_004b28e0(uVar1,uVar4,uVar3,uVar2,param_1[9],4,-0x262b2fc7);
  uVar2 = FUN_004b28e0(uVar2,uVar1,uVar4,uVar3,param_1[0xc],0xb,-0x1924661b);
  uVar3 = FUN_004b28e0(uVar3,uVar2,uVar1,uVar4,param_1[0xf],0x10,0x1fa27cf8);
  uVar4 = FUN_004b28e0(uVar4,uVar3,uVar2,uVar1,param_1[2],0x17,-0x3b53a99b);
  uVar1 = FUN_004b2920(uVar1,uVar4,uVar3,uVar2,*param_1,6,-0xbd6ddbc);
  uVar2 = FUN_004b2920(uVar2,uVar1,uVar4,uVar3,param_1[7],10,0x432aff97);
  uVar3 = FUN_004b2920(uVar3,uVar2,uVar1,uVar4,param_1[0xe],0xf,-0x546bdc59);
  uVar4 = FUN_004b2920(uVar4,uVar3,uVar2,uVar1,param_1[5],0x15,-0x36c5fc7);
  uVar1 = FUN_004b2920(uVar1,uVar4,uVar3,uVar2,param_1[0xc],6,0x655b59c3);
  uVar2 = FUN_004b2920(uVar2,uVar1,uVar4,uVar3,param_1[3],10,-0x70f3336e);
  uVar3 = FUN_004b2920(uVar3,uVar2,uVar1,uVar4,param_1[10],0xf,-0x100b83);
  uVar4 = FUN_004b2920(uVar4,uVar3,uVar2,uVar1,param_1[1],0x15,-0x7a7ba22f);
  uVar1 = FUN_004b2920(uVar1,uVar4,uVar3,uVar2,param_1[8],6,0x6fa87e4f);
  uVar2 = FUN_004b2920(uVar2,uVar1,uVar4,uVar3,param_1[0xf],10,-0x1d31920);
  uVar3 = FUN_004b2920(uVar3,uVar2,uVar1,uVar4,param_1[6],0xf,-0x5cfebcec);
  uVar4 = FUN_004b2920(uVar4,uVar3,uVar2,uVar1,param_1[0xd],0x15,0x4e0811a1);
  uVar1 = FUN_004b2920(uVar1,uVar4,uVar3,uVar2,param_1[4],6,-0x8ac817e);
  uVar2 = FUN_004b2920(uVar2,uVar1,uVar4,uVar3,param_1[0xb],10,-0x42c50dcb);
  uVar3 = FUN_004b2920(uVar3,uVar2,uVar1,uVar4,param_1[2],0xf,0x2ad7d2bb);
  iVar5 = FUN_004b2920(uVar4,uVar3,uVar2,uVar1,param_1[9],0x15,-0x14792c6f);
  *(int *)((int)this + 0x50) = *(int *)((int)this + 0x50) + iVar5;
  *(uint *)((int)this + 0x4c) = *(int *)((int)this + 0x4c) + uVar1;
  *(uint *)((int)this + 0x54) = *(int *)((int)this + 0x54) + uVar3;
  *(uint *)((int)this + 0x58) = *(int *)((int)this + 0x58) + uVar2;
  return;
}


/* 004b3150 size=102 */

void __fastcall FUN_004b3150(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  int local_8 [2];
  
  FUN_004b31c0(*param_1,0,(int)(param_1 + 3),0,0x10);
  puVar1 = (undefined4 *)*param_1;
  local_8[0] = param_1[1] - (int)puVar1;
  local_8[1] = 0xffffffff;
  piVar2 = local_8;
  if (local_8[0] == -1) {
    piVar2 = local_8 + 1;
  }
  puVar3 = (undefined4 *)(*piVar2 + (int)puVar1);
  if (puVar1 != puVar3) {
    FUN_004bab10(puVar1,puVar3,(param_1[1] - (int)puVar3) + 1);
    param_1[1] = (int)puVar1 + (param_1[1] - (int)puVar3);
  }
  return;
}


/* 004b31c0 size=93 */

void __cdecl FUN_004b31c0(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  byte *pbVar1;
  byte *pbVar2;
  uint *puVar3;
  uint uVar4;
  
  if (0 < param_5) {
    pbVar1 = (byte *)(param_1 + param_2);
    puVar3 = (uint *)(param_3 + param_4 * 4);
    do {
      *puVar3 = (uint)*pbVar1;
      uVar4 = *puVar3 | (uint)pbVar1[1] << 8;
      *puVar3 = uVar4;
      uVar4 = uVar4 | (uint)pbVar1[2] << 0x10;
      pbVar2 = pbVar1 + 3;
      *puVar3 = uVar4;
      pbVar1 = pbVar1 + 4;
      *puVar3 = uVar4 | (uint)*pbVar2 << 0x18;
      param_5 = param_5 + -1;
      puVar3 = puVar3 + 1;
    } while (param_5 != 0);
  }
  return;
}


/* 004b3220 size=267 */

undefined4 * __fastcall FUN_004b3220(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *local_18 [2];
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004caa87;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_4 = 1;
  FUN_004a9380(param_1,8);
  *(undefined1 *)param_1[1] = 0;
  local_4 = 2;
  FUN_004b22f0(param_1 + 4);
  param_1[0x2e] = 0;
  param_1[0x2f] = 0;
  param_1[0x30] = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  FUN_004a9380(param_1 + 0x2e,8);
  *(undefined1 *)param_1[0x2f] = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 6;
  puVar1 = FUN_004b35f0(local_18);
  (*(uint8_t*)((char*)&local_4+0)) = 7;
  FUN_004b3330(param_1,puVar1);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),8);
  if (local_18[0] != (undefined4 *)0x0) {
    if ((uint)(local_10 - (int)local_18[0]) < 0x81) {
      FUN_004a94b0(&DAT_004ed050);
      *local_18[0] = *(undefined4 *)(&DAT_004ec644 + ((local_10 - (int)local_18[0]) - 1U >> 3) * 4);
      *(undefined4 **)(&DAT_004ec644 + ((local_10 - (int)local_18[0]) - 1U >> 3) * 4) = local_18[0];
      DAT_004ed050 = 0;
      ExceptionList = local_c;
      return param_1;
    }
    FUN_00430df0((undefined *)local_18[0]);
  }
  ExceptionList = local_c;
  return param_1;
}


/* 004b3330 size=278 */

void __thiscall FUN_004b3330(void *this,undefined4 *param_1)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  undefined4 *local_18 [2];
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004caab0;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  if (*(int *)((int)this + 4) != *(int *)this) {
    ExceptionList = &local_c;
    FUN_004b2740((void *)((int)this + 0x10),this);
  }
  puVar2 = FUN_004b24e0((void *)((int)this + 0x10),local_18,param_1);
  local_4 = 0;
  if (puVar2 != this) {
    puVar1 = (undefined1 *)puVar2[1];
    puVar4 = *(undefined4 **)this;
    for (puVar3 = (undefined1 *)*puVar2; puVar3 != puVar1; puVar3 = puVar3 + 1) {
      if (puVar4 == *(undefined4 **)((int)this + 4)) {
        if (puVar3 != puVar1) {
          FUN_004ac5c0(this,puVar3,puVar1);
          goto LAB_004b33ce;
        }
        break;
      }
      *(undefined1 *)puVar4 = *puVar3;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    puVar2 = *(undefined4 **)((int)this + 4);
    if (puVar4 != puVar2) {
      FUN_004bab10(puVar4,puVar2,1);
      *(int *)((int)this + 4) = (int)puVar4 + (*(int *)((int)this + 4) - (int)puVar2);
    }
  }
LAB_004b33ce:
  local_4 = 1;
  if (local_18[0] != (undefined4 *)0x0) {
    if (0x80 < (uint)(local_10 - (int)local_18[0])) {
      FUN_00430df0((undefined *)local_18[0]);
      ExceptionList = local_c;
      return;
    }
    FUN_004a94b0(&DAT_004ed050);
    *local_18[0] = *(undefined4 *)(&DAT_004ec644 + ((local_10 - (int)local_18[0]) - 1U >> 3) * 4);
    *(undefined4 **)(&DAT_004ec644 + ((local_10 - (int)local_18[0]) - 1U >> 3) * 4) = local_18[0];
    DAT_004ed050 = 0;
  }
  ExceptionList = local_c;
  return;
}


/* 004b3450 size=403 */

void __thiscall FUN_004b3450(void *this,int *param_1)

{
  int *this_00;
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined8 uVar7;
  undefined4 *puVar8;
  int *piVar9;
  undefined1 *puVar10;
  int iVar11;
  int local_30;
  undefined4 *local_24 [2];
  int local_1c;
  undefined4 *local_18 [2];
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004caae0;
  local_c = ExceptionList;
  iVar2 = param_1[1];
  iVar3 = *param_1;
  local_30 = 0;
  if (0 < iVar2 - iVar3) {
    this_00 = (int *)((int)this + 0xb8);
    ExceptionList = &local_c;
    do {
      local_4 = 0xffffffff;
      if ((*(int *)((int)this + 0xbc) == *this_00) ||
         (*(int *)((int)this + 0xc4) == *(int *)((int)this + 0xbc) - *this_00)) {
        FUN_004b2740((void *)((int)this + 0x10),this);
        uVar4 = *(uint *)((int)this + 200);
        uVar7 = *(undefined8 *)((int)this + 200);
        *(uint *)((int)this + 200) = uVar4 + 1;
        *(uint *)((int)this + 0xcc) = *(int *)((int)this + 0xcc) + (uint)(0xfffffffe < uVar4);
        puVar8 = FUN_004b37e0(local_18,uVar7);
        local_4 = 0;
        piVar9 = FUN_004b24e0((void *)((int)this + 0x10),local_24,puVar8);
        (*(uint8_t*)((char*)&local_4+0)) = 1;
        if (piVar9 != this_00) {
          puVar5 = (undefined1 *)piVar9[1];
          puVar10 = (undefined1 *)*piVar9;
          puVar8 = (undefined4 *)*this_00;
          if (puVar10 == puVar5) {
LAB_004b3532:
            FUN_004a89b0(this_00,puVar8,*(undefined4 **)((int)this + 0xbc));
          }
          else {
            do {
              if (puVar8 == *(undefined4 **)((int)this + 0xbc)) {
                if (puVar10 == puVar5) goto LAB_004b3532;
                FUN_004ac5c0(this_00,puVar10,puVar5);
                goto LAB_004b354e;
              }
              uVar1 = *puVar10;
              puVar10 = puVar10 + 1;
              *(undefined1 *)puVar8 = uVar1;
              puVar8 = (undefined4 *)((int)puVar8 + 1);
            } while (puVar10 != puVar5);
            FUN_004a89b0(this_00,puVar8,*(undefined4 **)((int)this + 0xbc));
          }
        }
LAB_004b354e:
        local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
        FUN_004a9430(local_24[0],local_1c - (int)local_24[0]);
        local_4 = 3;
        FUN_004a9430(local_18[0],local_10 - (int)local_18[0]);
        *(undefined4 *)((int)this + 0xc4) = 0;
      }
      iVar6 = *(int *)((int)this + 0xc4);
      iVar11 = local_30 + 1;
      *(int *)((int)this + 0xc4) = iVar6 + 1;
      *(undefined1 *)(local_30 + *param_1) = *(undefined1 *)(*this_00 + iVar6);
      local_30 = iVar11;
    } while (iVar11 < iVar2 - iVar3);
  }
  ExceptionList = local_c;
  return;
}


/* 004b35f0 size=483 */

/* FUN_004b35f0: lifted from original x86 -> lt_lifted.c */


/* 004b37e0 size=278 */

undefined4 * FUN_004b37e0(undefined4 *param_1,undefined8 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined8 uVar5;
  undefined1 local_1d;
  undefined4 local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004cab8f;
  local_c = ExceptionList;
  local_1c = 0;
  local_4 = 1;
  local_18 = (undefined4 *)0x0;
  local_14 = (undefined4 *)0x0;
  ExceptionList = &local_c;
  FUN_004a93e0(&local_10,&local_1d,0);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004a9380(&local_18,9);
  *local_18 = 0;
  local_18[1] = 0;
  local_14 = local_18 + 2;
  *(undefined1 *)local_14 = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  iVar4 = 0;
  uVar5 = param_2;
  do {
    *(char *)(iVar4 + (int)local_18) = (char)uVar5;
    uVar5 = __allshr(8,(int)((ulonglong)uVar5 >> 0x20));
    iVar4 = iVar4 + 1;
  } while (iVar4 < 8);
  FUN_004a8710(&param_2);
  puVar2 = local_14;
  puVar1 = local_18;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),5);
  FUN_004a9380(param_1,(uint)((int)local_14 + (1 - (int)local_18)));
  puVar3 = (undefined1 *)FUN_004aca30((int)puVar1,(int)puVar2,(undefined1 *)*param_1);
  param_1[1] = puVar3;
  *puVar3 = 0;
  local_1c = 1;
  local_4 = 6;
  if (local_18 != (undefined4 *)0x0) {
    FUN_004aa6f0(local_18,local_10 - (int)local_18);
  }
  ExceptionList = local_c;
  return param_1;
}


/* 004b3900 size=14 */

void __fastcall FUN_004b3900(int *param_1)

{
  if ((int *)*param_1 != (int *)0x0) {
    (**(code **)(*(int *)*param_1 + 8))(1);
  }
  return;
}


/* 004b3910 size=90 */

void __thiscall FUN_004b3910(void *this,undefined1 param_1)

{
  int *piVar1;
  int local_8;
  int local_4;
  
  piVar1 = &local_8;
  if (*(int *)((int)this + 4) + 1 == *(int *)((int)this + 8)) {
    local_8 = 1;
    local_4 = *(int *)((int)this + 4) - *(int *)this;
    if (local_4 != 0) {
      piVar1 = &local_4;
    }
    FUN_004b3970(this,(undefined4 *)(*piVar1 + local_4));
  }
  *(undefined1 *)(*(int *)((int)this + 4) + 1) = 0;
  **(undefined1 **)((int)this + 4) = param_1;
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  return;
}


/* 004b3970 size=407 */

void __thiscall FUN_004b3970(void *this,undefined4 *param_1)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 **ppuVar4;
  int iVar5;
  uint uVar6;
  undefined1 *puVar7;
  uint uVar8;
  undefined4 *local_134 [2];
  uint local_12c;
  undefined1 local_128 [12];
  undefined1 local_11c [272];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004cabc1;
  local_c = ExceptionList;
  if (param_1 == (undefined4 *)0xffffffff) {
    local_4 = 0;
    ExceptionList = &local_c;
    puVar3 = FUN_004a95a0(local_128,s_basic_string_004de5c8);
    local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
    FUN_004a7ed0(local_11c,puVar3);
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_11c,&DAT_004d0380);
  }
  local_134[0] = (undefined4 *)(*(int *)((int)this + 4) - *(int *)this);
  ppuVar4 = local_134;
  if (local_134[0] <= param_1) {
    ppuVar4 = &param_1;
  }
  puVar3 = *ppuVar4;
  uVar8 = (int)puVar3 + 1;
  local_12c = uVar8;
  if (uVar8 == 0) {
    local_134[0] = (undefined4 *)0x0;
    ExceptionList = &local_c;
  }
  else if (uVar8 < 0x81) {
    ExceptionList = &local_c;
    FUN_004a94b0(&DAT_004ed050);
    local_4 = 2;
    puVar2 = *(undefined4 **)(&DAT_004ec644 + ((uint)puVar3 >> 3) * 4);
    if (puVar2 == (undefined4 *)0x0) {
      local_134[0] = (undefined4 *)FUN_004ab930(uVar8);
      DAT_004ed050 = 0;
    }
    else {
      *(undefined4 *)(&DAT_004ec644 + ((uint)puVar3 >> 3) * 4) = *puVar2;
      DAT_004ed050 = 0;
      local_134[0] = puVar2;
    }
  }
  else {
    ExceptionList = &local_c;
    local_134[0] = (undefined4 *)FUN_00430de0(uVar8);
  }
  puVar7 = *(undefined1 **)this;
  iVar5 = *(int *)((int)this + 4) - (int)puVar7;
  puVar3 = local_134[0];
  if (0 < iVar5) {
    do {
      uVar1 = *puVar7;
      puVar7 = puVar7 + 1;
      *(undefined1 *)puVar3 = uVar1;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  *(undefined1 *)puVar3 = 0;
  puVar2 = *(undefined4 **)this;
  uVar6 = *(int *)((int)this + 8) - (int)puVar2;
  if (puVar2 != (undefined4 *)0x0) {
    if (uVar6 < 0x81) {
      FUN_004a94b0(&DAT_004ed050);
      *puVar2 = *(undefined4 *)(&DAT_004ec644 + (uVar6 - 1 >> 3) * 4);
      *(undefined4 **)(&DAT_004ec644 + (uVar6 - 1 >> 3) * 4) = puVar2;
      DAT_004ed050 = 0;
      uVar8 = local_12c;
    }
    else {
      FUN_00430df0((undefined *)puVar2);
    }
  }
  *(undefined4 **)this = local_134[0];
  *(undefined4 **)((int)this + 4) = puVar3;
  *(undefined1 **)((int)this + 8) = (undefined1 *)((int)local_134[0] + uVar8);
  ExceptionList = local_c;
  return;
}


/* 004b3b10 size=32 */

undefined1 * __cdecl FUN_004b3b10(undefined1 *param_1,int param_2,undefined1 *param_3)

{
  if (param_2 == 0) {
    return param_1;
  }
  do {
    *param_1 = *param_3;
    param_1 = param_1 + 1;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return param_1;
}


/* 004b3b40 size=12 */

void FUN_004b3b40(void)

{
  InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_004ec700);
  return;
}


/* 004b3b50 size=12 */

void FUN_004b3b50(void)

{
  FUN_004b9cf5(&LAB_004b3b60);
  return;
}


