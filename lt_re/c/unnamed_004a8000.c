/* lithtech.exe decompilation - unnamed_004a8000 */
#include "ghidra_types.h"

/* 004a8010 size=136 */

void __fastcall FUN_004a8010(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c986b;
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


/* 004a80a0 size=35 */

void __fastcall FUN_004a80a0(int *param_1)

{
  undefined4 *puVar1;
  LONG LVar2;
  
  puVar1 = (undefined4 *)*param_1;
  if (puVar1 != (undefined4 *)0x0) {
    LVar2 = InterlockedDecrement(puVar1 + 1);
    if ((LVar2 < 1) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
  }
  return;
}


/* 004a80d0 size=106 */

undefined4 * __fastcall FUN_004a80d0(undefined4 *param_1)

{
  undefined2 *puVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9893;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_4 = 1;
  puVar1 = (undefined2 *)FUN_004aa520(0x10);
  *param_1 = puVar1;
  param_1[1] = puVar1;
  param_1[2] = puVar1 + 8;
  *puVar1 = 0;
  ExceptionList = local_c;
  return param_1;
}


/* 004a8140 size=279 */

undefined4 * __thiscall FUN_004a8140(void *this,undefined4 *param_1)

{
  char cVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  uint uVar5;
  int unaff_EDI;
  int iVar6;
  char *pcVar7;
  undefined1 local_12a [2];
  void *local_128;
  undefined4 local_124 [3];
  undefined1 local_118 [268];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c98cc;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_128 = this;
  FUN_004a8710(local_12a);
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  puVar4 = (undefined2 *)*param_1;
  local_4 = 0;
  iVar6 = param_1[1] - (int)puVar4 >> 1;
  uVar5 = iVar6 + 1;
  if ((uVar5 < 0x80000000) && (uVar5 != 0)) {
    puVar3 = (undefined2 *)FUN_004aa520(uVar5 * 2);
    *(undefined2 **)this = puVar3;
    *(undefined2 **)((int)this + 4) = puVar3;
    *(undefined2 **)((int)this + 8) = puVar3 + uVar5;
    if (0 < iVar6) {
      do {
        uVar2 = *puVar4;
        puVar4 = puVar4 + 1;
        *puVar3 = uVar2;
        puVar3 = puVar3 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    *(undefined2 **)((int)this + 4) = puVar3;
    *puVar3 = 0;
    ExceptionList = local_c;
    return this;
  }
  local_4 = 1;
  FUN_004a8730(local_124);
  uVar5 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  pcVar7 = s_basic_string_004de5c8;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  FUN_004aa340(local_124,(undefined4 *)s_basic_string_004de5c8,
               (int)(s___AVAuth2Certificate_WONAPI___004de5a8 + ~uVar5 + 0x1f),unaff_EDI);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),3);
  FUN_004a7ed0(local_118,local_124);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_118,&DAT_004d0380);
}


/* 004a8260 size=140 */

void __fastcall FUN_004a8260(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c98eb;
  local_c = ExceptionList;
  puVar1 = (undefined4 *)*param_1;
  local_4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    uVar2 = (param_1[2] - (int)puVar1 >> 1) * 2;
    if (0x80 < uVar2) {
      ExceptionList = &local_c;
      FUN_00430df0((undefined *)puVar1);
      ExceptionList = local_c;
      return;
    }
    ExceptionList = &local_c;
    FUN_004a94b0(&DAT_004ed050);
    *puVar1 = *(undefined4 *)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4);
    *(undefined4 **)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4) = puVar1;
    DAT_004ed050 = 0;
  }
  ExceptionList = local_c;
  return;
}


/* 004a82f0 size=1 */

void FUN_004a82f0(void)

{
  return;
}


/* 004a8300 size=146 */

int * __fastcall FUN_004a8300(int *param_1)

{
  undefined4 *puVar1;
  undefined1 local_11;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9918;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  local_4 = 1;
  FUN_004a94b0(&DAT_004ed050);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
  if (DAT_004ec64c == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)FUN_004ab930(0x18);
  }
  else {
    puVar1 = DAT_004ec64c;
    DAT_004ec64c = (undefined4 *)*DAT_004ec64c;
  }
  DAT_004ed050 = 0;
  *param_1 = (int)puVar1;
  param_1[1] = 0;
  *(undefined1 *)(param_1 + 2) = local_11;
  *(undefined1 *)puVar1 = 0;
  *(undefined4 *)(*param_1 + 4) = 0;
  *(int *)(*param_1 + 8) = *param_1;
  *(int *)(*param_1 + 0xc) = *param_1;
  ExceptionList = local_c;
  return param_1;
}


/* 004a83a0 size=146 */

int * __fastcall FUN_004a83a0(int *param_1)

{
  undefined4 *puVar1;
  undefined1 local_11;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9948;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  local_4 = 1;
  FUN_004a94b0(&DAT_004ed050);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
  if (DAT_004ec654 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)FUN_004ab930(0x28);
  }
  else {
    puVar1 = DAT_004ec654;
    DAT_004ec654 = (undefined4 *)*DAT_004ec654;
  }
  DAT_004ed050 = 0;
  *param_1 = (int)puVar1;
  param_1[1] = 0;
  *(undefined1 *)(param_1 + 2) = local_11;
  *(undefined1 *)puVar1 = 0;
  *(undefined4 *)(*param_1 + 4) = 0;
  *(int *)(*param_1 + 8) = *param_1;
  *(int *)(*param_1 + 0xc) = *param_1;
  ExceptionList = local_c;
  return param_1;
}


/* 004a8440 size=146 */

int * __fastcall FUN_004a8440(int *param_1)

{
  undefined4 *puVar1;
  undefined1 local_11;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9978;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  local_4 = 1;
  FUN_004a94b0(&DAT_004ed050);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
  if (DAT_004ec64c == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)FUN_004ab930(0x18);
  }
  else {
    puVar1 = DAT_004ec64c;
    DAT_004ec64c = (undefined4 *)*DAT_004ec64c;
  }
  DAT_004ed050 = 0;
  *param_1 = (int)puVar1;
  param_1[1] = 0;
  *(undefined1 *)(param_1 + 2) = local_11;
  *(undefined1 *)puVar1 = 0;
  *(undefined4 *)(*param_1 + 4) = 0;
  *(int *)(*param_1 + 8) = *param_1;
  *(int *)(*param_1 + 0xc) = *param_1;
  ExceptionList = local_c;
  return param_1;
}


/* 004a84e0 size=146 */

int * __fastcall FUN_004a84e0(int *param_1)

{
  undefined4 *puVar1;
  undefined1 local_11;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c99a8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  local_4 = 1;
  FUN_004a94b0(&DAT_004ed050);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
  if (DAT_004ec64c == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)FUN_004ab930(0x18);
  }
  else {
    puVar1 = DAT_004ec64c;
    DAT_004ec64c = (undefined4 *)*DAT_004ec64c;
  }
  DAT_004ed050 = 0;
  *param_1 = (int)puVar1;
  param_1[1] = 0;
  *(undefined1 *)(param_1 + 2) = local_11;
  *(undefined1 *)puVar1 = 0;
  *(undefined4 *)(*param_1 + 4) = 0;
  *(int *)(*param_1 + 8) = *param_1;
  *(int *)(*param_1 + 0xc) = *param_1;
  ExceptionList = local_c;
  return param_1;
}


/* 004a8580 size=98 */

uint * __thiscall FUN_004a8580(void *this,uint *param_1)

{
  int *piVar1;
  uint *puVar2;
  undefined1 auStackY_a0 [128];
  uint *puVar3;
  int local_c;
  uint local_8 [2];
  
  puVar3 = param_1;
  FUN_004aa300(this,(int *)&param_1,param_1);
  puVar2 = *(uint **)this;
  if ((param_1 == puVar2) || (puVar2 = (uint *)*puVar3, puVar2 < (uint *)param_1[4])) {
    local_8[0] = *puVar3;
    puVar3 = local_8;
    local_8[1] = 0;
    FUN_004a8fc0(auStackY_a0 + 0x84,&param_1);
    piVar1 = FUN_004a9180(this,&local_c,puVar2,puVar3);
    param_1 = (uint *)*piVar1;
  }
  return param_1 + 5;
}


/* 004a85f0 size=240 */

void __fastcall FUN_004a85f0(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c99de;
  local_c = ExceptionList;
  puVar1 = (undefined4 *)param_1[3];
  local_4 = 1;
  ExceptionList = &local_c;
  if (puVar1 != (undefined4 *)0x0) {
    uVar2 = (param_1[5] - (int)puVar1 >> 1) * 2;
    if (uVar2 < 0x81) {
      ExceptionList = &local_c;
      FUN_004a94b0(&DAT_004ed050);
      *puVar1 = *(undefined4 *)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4);
      *(undefined4 **)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4) = puVar1;
      DAT_004ed050 = 0;
    }
    else {
      ExceptionList = &local_c;
      FUN_00430df0((undefined *)puVar1);
    }
  }
  puVar1 = (undefined4 *)*param_1;
  local_4 = 2;
  if (puVar1 != (undefined4 *)0x0) {
    uVar2 = (param_1[2] - (int)puVar1 >> 1) * 2;
    if (0x80 < uVar2) {
      FUN_00430df0((undefined *)puVar1);
      ExceptionList = local_c;
      return;
    }
    FUN_004a94b0(&DAT_004ed050);
    *puVar1 = *(undefined4 *)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4);
    *(undefined4 **)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4) = puVar1;
    DAT_004ed050 = 0;
  }
  ExceptionList = local_c;
  return;
}


/* 004a86e0 size=36 */

void __fastcall FUN_004a86e0(int param_1)

{
  undefined4 *puVar1;
  LONG LVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 4);
  if (puVar1 != (undefined4 *)0x0) {
    LVar2 = InterlockedDecrement(puVar1 + 1);
    if ((LVar2 < 1) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
  }
  return;
}


/* 004a8710 size=17 */

undefined4 FUN_004a8710(undefined4 param_1)

{
  return param_1;
}


/* 004a8730 size=15 */

void __fastcall FUN_004a8730(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}


/* 004a8740 size=410 */

undefined4 * __thiscall FUN_004a8740(void *this,undefined4 param_1,uint param_2)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int unaff_EDI;
  int iVar6;
  char *pcVar7;
  undefined1 local_12d;
  uint local_12c;
  undefined4 *local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined1 local_11c [4];
  undefined **local_118 [67];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9a27;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  local_4 = 0;
  local_128 = this;
  if (param_2 != 0) {
    if (param_2 < 0x81) {
      FUN_004a94b0(&DAT_004ed050);
      local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
      piVar2 = *(int **)(&DAT_004ec644 + (param_2 - 1 >> 3) * 4);
      if (piVar2 == (int *)0x0) {
        uVar5 = param_2 + 7 & 0xfffffff8;
        local_12c = 0x14;
        piVar2 = FUN_004ac1c0(uVar5,&local_12c);
        if (local_12c != 1) {
          puVar3 = (undefined4 *)((int)piVar2 + uVar5);
          *(undefined4 **)(&DAT_004ec644 + (uVar5 - 1 >> 3) * 4) = puVar3;
          iVar6 = 1;
          puVar4 = puVar3;
          if (local_12c != 2) {
            do {
              puVar3 = (undefined4 *)((int)puVar4 + uVar5);
              *puVar4 = puVar3;
              iVar6 = iVar6 + 1;
              puVar4 = puVar3;
            } while (local_12c - 1 != iVar6);
          }
          *puVar3 = 0;
          this = local_128;
        }
      }
      else {
        *(int *)(&DAT_004ec644 + (param_2 - 1 >> 3) * 4) = *piVar2;
      }
      DAT_004ed050 = 0;
    }
    else {
      piVar2 = (int *)FUN_00430de0(param_2);
    }
    *(int **)this = piVar2;
    *(int **)((int)this + 4) = piVar2;
    *(uint *)((int)this + 8) = (int)piVar2 + param_2;
    ExceptionList = local_c;
    return this;
  }
  local_4 = 2;
  local_124 = 0;
  local_120 = 0;
  FUN_004a93e0(local_11c,&local_12d,0);
  uVar5 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  pcVar7 = s_basic_string_004de5c8;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  FUN_004aa340(&local_124,(undefined4 *)s_basic_string_004de5c8,
               (int)(s___AVAuth2Certificate_WONAPI___004de5a8 + ~uVar5 + 0x1f),unaff_EDI);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),4);
  FUN_004a88e0(local_118,&local_124);
  local_118[0] = &PTR_FUN_004cdb98;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_118,&DAT_004d0380);
}


/* 004a88e0 size=51 */

undefined4 * __thiscall FUN_004a88e0(void *this,undefined4 *param_1)

{
  FUN_004bcc6d(this);
  *(undefined ***)this = &PTR_FUN_004cdba4;
  _strncpy((char *)((int)this + 0xc),(char *)*param_1,0x100);
  *(undefined1 *)((int)this + 0x10b) = 0;
  return this;
}


/* 004a8920 size=136 */

void __fastcall FUN_004a8920(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9a4b;
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


/* 004a89b0 size=54 */

undefined4 * __thiscall FUN_004a89b0(void *this,undefined4 *param_1,undefined4 *param_2)

{
  if (param_1 != param_2) {
    FUN_004bab10(param_1,param_2,(*(int *)((int)this + 4) - (int)param_2) + 1);
    *(int *)((int)this + 4) = (int)param_1 + (*(int *)((int)this + 4) - (int)param_2);
  }
  return param_1;
}


/* 004a89f0 size=410 */

undefined4 * __thiscall FUN_004a89f0(void *this,undefined4 param_1,uint param_2)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int unaff_EDI;
  int iVar6;
  char *pcVar7;
  undefined1 local_12d;
  uint local_12c;
  undefined4 *local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined1 local_11c [4];
  undefined **local_118 [67];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9a97;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  local_4 = 0;
  local_128 = this;
  if (param_2 != 0) {
    if (param_2 < 0x81) {
      FUN_004a94b0(&DAT_004ed050);
      local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
      piVar2 = *(int **)(&DAT_004ec644 + (param_2 - 1 >> 3) * 4);
      if (piVar2 == (int *)0x0) {
        uVar5 = param_2 + 7 & 0xfffffff8;
        local_12c = 0x14;
        piVar2 = FUN_004ac1c0(uVar5,&local_12c);
        if (local_12c != 1) {
          puVar3 = (undefined4 *)((int)piVar2 + uVar5);
          *(undefined4 **)(&DAT_004ec644 + (uVar5 - 1 >> 3) * 4) = puVar3;
          iVar6 = 1;
          puVar4 = puVar3;
          if (local_12c != 2) {
            do {
              puVar3 = (undefined4 *)((int)puVar4 + uVar5);
              *puVar4 = puVar3;
              iVar6 = iVar6 + 1;
              puVar4 = puVar3;
            } while (local_12c - 1 != iVar6);
          }
          *puVar3 = 0;
          this = local_128;
        }
      }
      else {
        *(int *)(&DAT_004ec644 + (param_2 - 1 >> 3) * 4) = *piVar2;
      }
      DAT_004ed050 = 0;
    }
    else {
      piVar2 = (int *)FUN_00430de0(param_2);
    }
    *(int **)this = piVar2;
    *(int **)((int)this + 4) = piVar2;
    *(uint *)((int)this + 8) = (int)piVar2 + param_2;
    ExceptionList = local_c;
    return this;
  }
  local_4 = 2;
  local_124 = 0;
  local_120 = 0;
  FUN_004a93e0(local_11c,&local_12d,0);
  uVar5 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  pcVar7 = s_basic_string_004de5c8;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  FUN_004aa340(&local_124,(undefined4 *)s_basic_string_004de5c8,
               (int)(s___AVAuth2Certificate_WONAPI___004de5a8 + ~uVar5 + 0x1f),unaff_EDI);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),4);
  FUN_004a88e0(local_118,&local_124);
  local_118[0] = &PTR_FUN_004cdb98;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_118,&DAT_004d0380);
}


/* 004a8b90 size=136 */

void __fastcall FUN_004a8b90(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9abb;
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


/* 004a8c20 size=415 */

undefined4 * __thiscall FUN_004a8c20(void *this,undefined4 param_1,uint param_2)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  int unaff_EDI;
  int iVar7;
  char *pcVar8;
  undefined1 local_12d;
  uint local_12c;
  undefined4 *local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined1 local_11c [4];
  undefined **local_118 [67];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9b07;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  local_4 = 0;
  local_128 = this;
  if ((param_2 < 0x80000000) && (param_2 != 0)) {
    uVar4 = param_2 * 2;
    if (uVar4 < 0x81) {
      FUN_004a94b0(&DAT_004ed050);
      local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
      piVar2 = *(int **)(&DAT_004ec644 + (uVar4 - 1 >> 3) * 4);
      if (piVar2 == (int *)0x0) {
        uVar6 = uVar4 + 7 & 0xfffffff8;
        local_12c = 0x14;
        piVar2 = FUN_004ac1c0(uVar6,&local_12c);
        if (local_12c != 1) {
          puVar3 = (undefined4 *)((int)piVar2 + uVar6);
          *(undefined4 **)(&DAT_004ec644 + (uVar6 - 1 >> 3) * 4) = puVar3;
          iVar7 = 1;
          puVar5 = puVar3;
          if (local_12c != 2) {
            do {
              puVar3 = (undefined4 *)((int)puVar5 + uVar6);
              *puVar5 = puVar3;
              iVar7 = iVar7 + 1;
              puVar5 = puVar3;
            } while (local_12c - 1 != iVar7);
          }
          *puVar3 = 0;
          this = local_128;
        }
      }
      else {
        *(int *)(&DAT_004ec644 + (uVar4 - 1 >> 3) * 4) = *piVar2;
      }
      DAT_004ed050 = 0;
    }
    else {
      piVar2 = (int *)FUN_00430de0(uVar4);
    }
    *(int **)this = piVar2;
    *(int **)((int)this + 4) = piVar2;
    *(uint *)((int)this + 8) = uVar4 + (int)piVar2;
    ExceptionList = local_c;
    return this;
  }
  local_4 = 2;
  local_124 = 0;
  local_120 = 0;
  FUN_004a93e0(local_11c,&local_12d,0);
  uVar4 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  pcVar8 = s_basic_string_004de5c8;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  FUN_004aa340(&local_124,(undefined4 *)s_basic_string_004de5c8,
               (int)(s___AVAuth2Certificate_WONAPI___004de5a8 + ~uVar4 + 0x1f),unaff_EDI);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),4);
  FUN_004a88e0(local_118,&local_124);
  local_118[0] = &PTR_FUN_004cdb98;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_118,&DAT_004d0380);
}


/* 004a8dc0 size=140 */

void __fastcall FUN_004a8dc0(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9b2b;
  local_c = ExceptionList;
  puVar1 = (undefined4 *)*param_1;
  local_4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    uVar2 = (param_1[2] - (int)puVar1 >> 1) * 2;
    if (0x80 < uVar2) {
      ExceptionList = &local_c;
      FUN_00430df0((undefined *)puVar1);
      ExceptionList = local_c;
      return;
    }
    ExceptionList = &local_c;
    FUN_004a94b0(&DAT_004ed050);
    *puVar1 = *(undefined4 *)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4);
    *(undefined4 **)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4) = puVar1;
    DAT_004ed050 = 0;
  }
  ExceptionList = local_c;
  return;
}


/* 004a8e50 size=41 */

int * __thiscall FUN_004a8e50(void *this,int *param_1,undefined4 param_2,uint *param_3)

{
  undefined1 auStackY_94 [128];
  void *pvVar1;
  uint *puVar2;
  
  pvVar1 = this;
  puVar2 = param_3;
  FUN_004a8fc0(auStackY_94 + 0x84,&param_2);
  FUN_004a9720(this,param_1,(int)pvVar1,puVar2);
  return param_1;
}


/* 004a8e80 size=214 */

int * __thiscall FUN_004a8e80(void *this,undefined1 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  uint local_14;
  void *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9b50;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)this = 0;
  local_4 = 0;
  local_10 = this;
  FUN_004a94b0(&DAT_004ed050);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
  if (DAT_004ec64c == (undefined4 *)0x0) {
    local_14 = 0x14;
    puVar2 = FUN_004ac1c0(0x18,&local_14);
    if (local_14 != 1) {
      puVar4 = puVar2 + 6;
      iVar5 = 1;
      puVar1 = puVar2 + 0xc;
      puVar3 = puVar4;
      DAT_004ec64c = puVar4;
      if (local_14 != 2) {
        do {
          puVar4 = puVar1;
          *puVar3 = puVar4;
          iVar5 = iVar5 + 1;
          puVar1 = puVar4 + 6;
          puVar3 = puVar4;
        } while (local_14 - 1 != iVar5);
      }
      *puVar4 = 0;
    }
  }
  else {
    puVar2 = DAT_004ec64c;
    DAT_004ec64c = (undefined4 *)*DAT_004ec64c;
  }
  DAT_004ed050 = 0;
  *(undefined4 **)this = puVar2;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined1 *)((int)this + 8) = *param_1;
  *(undefined1 *)puVar2 = 0;
  *(undefined4 *)(*(int *)this + 4) = 0;
  *(int *)(*(int *)this + 8) = *(int *)this;
  *(int *)(*(int *)this + 0xc) = *(int *)this;
  ExceptionList = local_c;
  return this;
}


/* 004a8f60 size=93 */

void __fastcall FUN_004a8f60(undefined4 *param_1)

{
  int *piVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9b68;
  local_c = ExceptionList;
  piVar1 = (int *)*param_1;
  local_4 = 0;
  if (piVar1 != (int *)0x0) {
    ExceptionList = &local_c;
    FUN_004a94b0(&DAT_004ed050);
    *piVar1 = (int)DAT_004ec64c;
    DAT_004ed050 = 0;
    DAT_004ec64c = piVar1;
  }
  ExceptionList = local_c;
  return;
}


/* 004a8fc0 size=13 */

void __thiscall FUN_004a8fc0(void *this,undefined4 *param_1)

{
  *(undefined4 *)this = *param_1;
  return;
}


/* 004a8fd0 size=41 */

int * __thiscall FUN_004a8fd0(void *this,int *param_1,undefined4 param_2,int *param_3)

{
  undefined1 auStackY_94 [128];
  void *pvVar1;
  int *piVar2;
  
  pvVar1 = this;
  piVar2 = param_3;
  FUN_004a8fc0(auStackY_94 + 0x84,&param_2);
  FUN_004a9a60(this,param_1,(int)pvVar1,piVar2);
  return param_1;
}


/* 004a9000 size=143 */

void __thiscall FUN_004a9000(void *this,int *param_1,undefined4 *param_2)

{
  short *psVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 **ppuVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int local_8;
  undefined4 *local_4;
  
  puVar2 = param_2;
  local_8 = *(int *)this;
  iVar5 = *(int *)(local_8 + 4);
  if (iVar5 == 0) {
    *param_1 = local_8;
    return;
  }
  do {
    psVar1 = (short *)*puVar2;
    puVar6 = (undefined4 *)(*(int *)(iVar5 + 0x14) - *(int *)(iVar5 + 0x10) >> 1);
    puVar7 = (undefined4 *)(puVar2[1] - (int)psVar1 >> 1);
    local_4 = puVar6;
    ppuVar4 = &param_2;
    if ((int)puVar6 <= (int)puVar7) {
      ppuVar4 = &local_4;
    }
    param_2 = puVar7;
    iVar3 = FUN_004aa8e0(*(int *)(iVar5 + 0x10),psVar1,(uint)*ppuVar4);
    if (((iVar3 == 0) && ((int)puVar6 < (int)puVar7)) || (iVar3 < 0)) {
      iVar3 = *(int *)(iVar5 + 0xc);
    }
    else {
      iVar3 = *(int *)(iVar5 + 8);
      local_8 = iVar5;
    }
    iVar5 = iVar3;
  } while (iVar3 != 0);
  *param_1 = local_8;
  return;
}


/* 004a9090 size=93 */

void __fastcall FUN_004a9090(undefined4 *param_1)

{
  int *piVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9b88;
  local_c = ExceptionList;
  piVar1 = (int *)*param_1;
  local_4 = 0;
  if (piVar1 != (int *)0x0) {
    ExceptionList = &local_c;
    FUN_004a94b0(&DAT_004ed050);
    *piVar1 = (int)DAT_004ec654;
    DAT_004ed050 = 0;
    DAT_004ec654 = piVar1;
  }
  ExceptionList = local_c;
  return;
}


/* 004a90f0 size=41 */

int * __thiscall FUN_004a90f0(void *this,int *param_1,undefined4 param_2,uint *param_3)

{
  undefined1 auStackY_94 [128];
  void *pvVar1;
  uint *puVar2;
  
  pvVar1 = this;
  puVar2 = param_3;
  FUN_004a8fc0(auStackY_94 + 0x84,&param_2);
  FUN_004a9d80(this,param_1,(int)pvVar1,puVar2);
  return param_1;
}


/* 004a9120 size=93 */

void __fastcall FUN_004a9120(undefined4 *param_1)

{
  int *piVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9ba8;
  local_c = ExceptionList;
  piVar1 = (int *)*param_1;
  local_4 = 0;
  if (piVar1 != (int *)0x0) {
    ExceptionList = &local_c;
    FUN_004a94b0(&DAT_004ed050);
    *piVar1 = (int)DAT_004ec64c;
    DAT_004ed050 = 0;
    DAT_004ec64c = piVar1;
  }
  ExceptionList = local_c;
  return;
}


/* 004a9180 size=41 */

int * __thiscall FUN_004a9180(void *this,int *param_1,undefined4 param_2,uint *param_3)

{
  undefined1 auStackY_94 [128];
  void *pvVar1;
  uint *puVar2;
  
  pvVar1 = this;
  puVar2 = param_3;
  FUN_004a8fc0(auStackY_94 + 0x84,&param_2);
  FUN_004aa060(this,param_1,(int)pvVar1,puVar2);
  return param_1;
}


/* 004a91b0 size=93 */

void __fastcall FUN_004a91b0(undefined4 *param_1)

{
  int *piVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9bc8;
  local_c = ExceptionList;
  piVar1 = (int *)*param_1;
  local_4 = 0;
  if (piVar1 != (int *)0x0) {
    ExceptionList = &local_c;
    FUN_004a94b0(&DAT_004ed050);
    *piVar1 = (int)DAT_004ec64c;
    DAT_004ed050 = 0;
    DAT_004ec64c = piVar1;
  }
  ExceptionList = local_c;
  return;
}


/* 004a9210 size=24 */

int __thiscall FUN_004a9210(void *this,undefined4 *param_1,undefined2 *param_2)

{
  *(undefined4 *)this = *param_1;
  *(undefined2 *)((int)this + 4) = *param_2;
  return;
}


/* 004a9230 size=258 */

int * __thiscall FUN_004a9230(void *this,int *param_1,undefined1 param_2,int *param_3)

{
  undefined4 *this_00;
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined2 *puVar6;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  piVar3 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9bf8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004a8710(&param_1);
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  iVar1 = piVar3[1];
  iVar2 = *piVar3;
  local_4 = 0;
  uVar4 = (iVar1 - iVar2 >> 1) + 1;
  if ((uVar4 < 0x80000000) && (uVar4 != 0)) {
    iVar5 = FUN_004aa520(uVar4 * 2);
    *(int *)this = iVar5;
    *(int *)((int)this + 4) = iVar5;
    *(uint *)((int)this + 8) = uVar4 * 2 + iVar5;
  }
  else {
    FUN_004a5b30(s_basic_string_004de5c8);
  }
  puVar6 = (undefined2 *)FUN_004aca60(iVar2,iVar1,*(undefined2 **)this);
  piVar3 = param_3;
  *(undefined2 **)((int)this + 4) = puVar6;
  *puVar6 = 0;
  this_00 = (undefined4 *)((int)this + 0xc);
  FUN_004a8710(&param_2);
  *this_00 = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  iVar1 = piVar3[1];
  iVar2 = *piVar3;
  FUN_004a93f0(this_00,(iVar1 - iVar2 >> 1) + 1);
  puVar6 = (undefined2 *)FUN_004aca60(iVar2,iVar1,(undefined2 *)*this_00);
  *(undefined2 **)((int)this + 0x10) = puVar6;
  *puVar6 = 0;
  ExceptionList = puStack_8;
  return this;
}


/* 004a9340 size=54 */

undefined4 * __thiscall FUN_004a9340(void *this,undefined4 *param_1,int *param_2)

{
  int iVar1;
  
  *(undefined4 *)this = *param_1;
  iVar1 = *param_2;
  if (iVar1 == 0) {
    *(undefined4 *)((int)this + 4) = 0;
    return this;
  }
  InterlockedIncrement((LONG *)(iVar1 + 4));
  *(int *)((int)this + 4) = iVar1;
  return this;
}


/* 004a9380 size=59 */

void __thiscall FUN_004a9380(void *this,uint param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    FUN_004a5b30(s_basic_string_004de5c8);
    return;
  }
  iVar1 = FUN_004aa520(param_1);
  *(int *)this = iVar1;
  *(int *)((int)this + 4) = iVar1;
  *(uint *)((int)this + 8) = iVar1 + param_1;
  return;
}


/* 004a93c0 size=22 */

void __fastcall FUN_004a93c0(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)*param_1;
  if (puVar1 != (undefined4 *)0x0) {
    FUN_004aa6f0(puVar1,param_1[2] - (int)puVar1);
  }
  return;
}


/* 004a93e0 size=11 */

void __thiscall FUN_004a93e0(void *this,undefined4 param_1,undefined4 param_2)

{
  *(undefined4 *)this = param_2;
  return;
}


/* 004a93f0 size=63 */

void __thiscall FUN_004a93f0(void *this,uint param_1)

{
  int iVar1;
  
  if ((param_1 < 0x80000000) && (param_1 != 0)) {
    iVar1 = FUN_004aa520(param_1 * 2);
    *(uint *)((int)this + 8) = param_1 * 2 + iVar1;
    *(int *)this = iVar1;
    *(int *)((int)this + 4) = iVar1;
    return;
  }
  FUN_004a5b30(s_basic_string_004de5c8);
  return;
}


/* 004a9430 size=25 */

void FUN_004a9430(undefined4 *param_1,uint param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    FUN_004aa6f0(param_1,param_2);
  }
  return;
}


/* 004a9450 size=31 */

void FUN_004a9450(undefined4 *param_1,int param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    FUN_004aa6f0(param_1,param_2 * 0x18);
  }
  return;
}


/* 004a9470 size=31 */

void FUN_004a9470(undefined4 *param_1,int param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    FUN_004aa6f0(param_1,param_2 * 0x28);
  }
  return;
}


/* 004a9490 size=28 */

void FUN_004a9490(undefined4 *param_1,int param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    FUN_004aa6f0(param_1,param_2 * 2);
  }
  return;
}


/* 004a94b0 size=239 */

int __cdecl FUN_004a94b0(LONG *param_1)

{
  uint uVar1;
  LONG LVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  LVar2 = InterlockedExchange(param_1,1);
  uVar1 = DAT_004de6a4;
  if (LVar2 != 0) {
    uVar4 = 0;
    if (DAT_004de6a4 != 0) {
      uVar3 = DAT_004ec684 >> 1;
      do {
        if (((uVar3 <= uVar4) && (*param_1 == 0)) &&
           (LVar2 = InterlockedExchange(param_1,1), LVar2 == 0)) {
          DAT_004de6a4 = 1000;
          DAT_004ec684 = uVar4;
          return;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < uVar1);
    }
    DAT_004de6a4 = 0x1e;
    iVar6 = 6;
    while( true ) {
      iVar5 = iVar6;
      if (0x1b < iVar6) {
        iVar5 = 0x1b;
      }
      LVar2 = InterlockedExchange(param_1,1);
      if (LVar2 == 0) break;
      if (iVar5 < 0x15) {
        Sleep(0);
        iVar6 = iVar6 + 1;
      }
      else {
        Sleep(1 << ((char)iVar5 - 0x14U & 0x1f));
        iVar6 = iVar6 + 1;
      }
    }
  }
  return;
}


/* 004a95a0 size=241 */

undefined4 * __thiscall FUN_004a95a0(void *this,char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  char *pcVar4;
  undefined1 local_124 [12];
  undefined **local_118 [67];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9c31;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  uVar3 = 0xffffffff;
  pcVar4 = param_1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  local_4 = 0;
  if (uVar3 == 0) {
    local_4 = 1;
    puVar2 = FUN_004a95a0(local_124,s_basic_string_004de5c8);
    local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
    FUN_004a96a0(local_118,puVar2);
    local_118[0] = &PTR_FUN_004cdb98;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_118,&DAT_004d0380);
  }
  puVar2 = (undefined4 *)FUN_004aa520(uVar3);
  *(undefined4 **)this = puVar2;
  *(undefined4 **)((int)this + 4) = puVar2;
  *(uint *)((int)this + 8) = (int)puVar2 + uVar3;
  FUN_004bab10(puVar2,(undefined4 *)param_1,uVar3 - 1);
  *(char **)((int)this + 4) = param_1 + (int)puVar2 + ((uVar3 - 1) - (int)param_1);
  param_1[(int)puVar2 + ((uVar3 - 1) - (int)param_1)] = '\0';
  ExceptionList = local_c;
  return this;
}


/* 004a96a0 size=57 */

undefined4 * __thiscall FUN_004a96a0(void *this,undefined4 *param_1)

{
  FUN_004bcc6d(this);
  *(undefined ***)this = &PTR_FUN_004cdba4;
  _strncpy((char *)((int)this + 0xc),(char *)*param_1,0x100);
  *(undefined1 *)((int)this + 0x10b) = 0;
  *(undefined ***)this = &PTR_FUN_004cdbb0;
  return this;
}


/* 004a96e0 size=54 */

void FUN_004a96e0(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  while (puVar1 = param_1, puVar1 != (undefined4 *)0x0) {
    FUN_004a96e0((undefined4 *)puVar1[3]);
    param_1 = (undefined4 *)puVar1[2];
    if (puVar1 != (undefined4 *)0x0) {
      FUN_004aa6f0(puVar1,0x18);
    }
  }
  return;
}


/* 004a9720 size=661 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __thiscall FUN_004a9720(void *this,int *param_1,int param_2,uint *param_3)

{
  uint *puVar1;
  char *pcVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  uint **ppuVar7;
  undefined1 local_19;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8 [2];
  
  puVar1 = param_3;
  iVar5 = param_2;
  iVar4 = *(int *)this;
  if (param_2 != *(int *)(iVar4 + 8)) {
    if (param_2 == iVar4) {
      iVar5 = *(int *)(iVar4 + 0xc);
      if (*(uint *)(iVar5 + 0x10) < *param_3) {
        if ((iVar5 == iVar4) || (*param_3 < *(uint *)(iVar5 + 0x10))) {
          pcVar2 = (char *)FUN_004abad0(param_3);
          *(char **)(iVar5 + 8) = pcVar2;
          iVar4 = *(int *)this;
          if (iVar5 == iVar4) {
            *(char **)(iVar4 + 4) = pcVar2;
            *(char **)(*(int *)this + 0xc) = pcVar2;
          }
          else if (iVar5 == *(int *)(iVar4 + 8)) {
            *(char **)(iVar4 + 8) = pcVar2;
          }
        }
        else {
          pcVar2 = (char *)FUN_004abad0(param_3);
          *(char **)(iVar5 + 0xc) = pcVar2;
          if (iVar5 == *(int *)(*(int *)this + 0xc)) {
            *(char **)(*(int *)this + 0xc) = pcVar2;
          }
        }
        *(int *)(pcVar2 + 4) = iVar5;
        pcVar2[8] = '\0';
        pcVar2[9] = '\0';
        pcVar2[10] = '\0';
        pcVar2[0xb] = '\0';
        pcVar2[0xc] = '\0';
        pcVar2[0xd] = '\0';
        pcVar2[0xe] = '\0';
        pcVar2[0xf] = '\0';
        FUN_004abea0(pcVar2,(int *)(*(int *)this + 4));
        *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
        *param_1 = (int)pcVar2;
        return param_1;
      }
    }
    else {
      FUN_004ab8e0(&param_2);
      if ((*(uint *)(param_2 + 0x10) < *param_3) && (*param_3 < *(uint *)(iVar5 + 0x10))) {
        if (*(int *)(param_2 + 0xc) == 0) {
          FUN_004aa930(this,param_1,0,param_2,param_3);
          return param_1;
        }
        FUN_004aa930(this,param_1,iVar5,iVar5,param_3);
        return param_1;
      }
    }
    piVar3 = (int *)FUN_004aab90(this,local_8,param_3);
    *param_1 = *piVar3;
    return param_1;
  }
  if (*(int *)((int)this + 4) != 0) {
    if (*param_3 < *(uint *)(param_2 + 0x10)) {
      if (((param_2 == iVar4) || (param_2 != 0)) || (*param_3 < *(uint *)(param_2 + 0x10))) {
        pcVar2 = (char *)FUN_004abad0(param_3);
        *(char **)(iVar5 + 8) = pcVar2;
        iVar4 = *(int *)this;
        if (iVar5 == iVar4) {
          *(char **)(iVar4 + 4) = pcVar2;
          *(char **)(*(int *)this + 0xc) = pcVar2;
        }
        else if (iVar5 == *(int *)(iVar4 + 8)) {
          *(char **)(iVar4 + 8) = pcVar2;
        }
      }
      else {
        pcVar2 = (char *)FUN_004abad0(param_3);
        _DAT_0000000c = pcVar2;
        if (*(int *)(*(int *)this + 0xc) == 0) {
          *(char **)(*(int *)this + 0xc) = pcVar2;
        }
      }
      *(int *)(pcVar2 + 4) = iVar5;
      pcVar2[8] = '\0';
      pcVar2[9] = '\0';
      pcVar2[10] = '\0';
      pcVar2[0xb] = '\0';
      pcVar2[0xc] = '\0';
      pcVar2[0xd] = '\0';
      pcVar2[0xe] = '\0';
      pcVar2[0xf] = '\0';
      FUN_004abea0(pcVar2,(int *)(*(int *)this + 4));
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
      *param_1 = (int)pcVar2;
      return param_1;
    }
  }
  bVar6 = true;
  if (*(int *)(iVar4 + 4) != 0) {
    iVar5 = *(int *)(iVar4 + 4);
    do {
      iVar4 = iVar5;
      bVar6 = *param_3 < *(uint *)(iVar4 + 0x10);
      if (bVar6) {
        iVar5 = *(int *)(iVar4 + 8);
      }
      else {
        iVar5 = *(int *)(iVar4 + 0xc);
      }
    } while (iVar5 != 0);
  }
  local_18 = iVar4;
  if (bVar6) {
    piVar3 = (int *)FUN_004abba0(this,&local_14);
    if (local_18 == *piVar3) {
      ppuVar7 = &param_3;
      param_3 = (uint *)CONCAT31((*(uint32_t*)((char*)&param_3+1)),1);
      piVar3 = (int *)FUN_004aa930(this,&local_10,0,iVar4,puVar1);
      goto LAB_004a987c;
    }
    FUN_004ab8e0(&local_18);
  }
  if (*(uint *)(local_18 + 0x10) < *puVar1) {
    ppuVar7 = (uint **)&param_2;
    param_2 = CONCAT31((*(uint32_t*)((char*)&param_2+1)),1);
    piVar3 = (int *)FUN_004aa930(this,&local_c,0,iVar4,puVar1);
  }
  else {
    ppuVar7 = (uint **)&local_19;
    piVar3 = &local_18;
    local_19 = 0;
  }
LAB_004a987c:
  FUN_004844c0(local_8,piVar3,(undefined1 *)ppuVar7);
  *param_1 = local_8[0];
  return param_1;
}


/* 004a99c0 size=96 */

void __thiscall FUN_004a99c0(void *this,int *param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *(int *)this;
  iVar4 = iVar1;
  if (*(int *)(iVar1 + 4) != 0) {
    iVar2 = *(int *)(iVar1 + 4);
    do {
      if (*(uint *)(iVar2 + 0x10) < *param_2) {
        iVar3 = *(int *)(iVar2 + 0xc);
      }
      else {
        iVar3 = *(int *)(iVar2 + 8);
        iVar4 = iVar2;
      }
      iVar2 = iVar3;
    } while (iVar3 != 0);
  }
  if ((iVar4 == iVar1) || (*param_2 < *(uint *)(iVar4 + 0x10))) {
    *param_1 = iVar1;
    return;
  }
  *param_1 = iVar4;
  return;
}


/* 004a9a20 size=62 */

void FUN_004a9a20(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  while (puVar1 = param_1, puVar1 != (undefined4 *)0x0) {
    FUN_004a9a20((undefined4 *)puVar1[3]);
    param_1 = (undefined4 *)puVar1[2];
    FUN_004a85f0(puVar1 + 4);
    if (puVar1 != (undefined4 *)0x0) {
      FUN_004aa6f0(puVar1,0x28);
    }
  }
  return;
}


/* 004a9a60 size=734 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __thiscall FUN_004a9a60(void *this,int *param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  char *pcVar5;
  int *piVar6;
  int *piVar7;
  int **ppiVar8;
  undefined1 local_19;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8 [2];
  
  piVar7 = param_3;
  iVar2 = param_2;
  iVar1 = *(int *)this;
  if (param_2 != *(int *)(iVar1 + 8)) {
    if (param_2 == iVar1) {
      uVar4 = FUN_004aa470((int *)(*(int *)(iVar1 + 0xc) + 0x10),param_3);
      if ((char)uVar4 != '\0') {
        iVar1 = *(int *)(*(int *)this + 0xc);
        if ((iVar1 == *(int *)this) ||
           (uVar4 = FUN_004aa470(piVar7,(undefined4 *)(iVar1 + 0x10)), (char)uVar4 != '\0')) {
          pcVar5 = (char *)FUN_004abbb0(piVar7);
          *(char **)(iVar1 + 8) = pcVar5;
          iVar2 = *(int *)this;
          if (iVar1 == iVar2) {
            *(char **)(iVar2 + 4) = pcVar5;
            *(char **)(*(int *)this + 0xc) = pcVar5;
          }
          else if (iVar1 == *(int *)(iVar2 + 8)) {
            *(char **)(iVar2 + 8) = pcVar5;
          }
        }
        else {
          pcVar5 = (char *)FUN_004abbb0(piVar7);
          *(char **)(iVar1 + 0xc) = pcVar5;
          if (iVar1 == *(int *)(*(int *)this + 0xc)) {
            *(char **)(*(int *)this + 0xc) = pcVar5;
          }
        }
        *(int *)(pcVar5 + 4) = iVar1;
        pcVar5[8] = '\0';
        pcVar5[9] = '\0';
        pcVar5[10] = '\0';
        pcVar5[0xb] = '\0';
        pcVar5[0xc] = '\0';
        pcVar5[0xd] = '\0';
        pcVar5[0xe] = '\0';
        pcVar5[0xf] = '\0';
        FUN_004abea0(pcVar5,(int *)(*(int *)this + 4));
        *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
        *param_1 = (int)pcVar5;
        return param_1;
      }
    }
    else {
      FUN_004ab8e0(&param_2);
      piVar7 = param_3;
      uVar4 = FUN_004aa470((int *)(param_2 + 0x10),param_3);
      if (((char)uVar4 != '\0') &&
         (uVar4 = FUN_004aa470(piVar7,(undefined4 *)(iVar2 + 0x10)), (char)uVar4 != '\0')) {
        if (*(int *)(param_2 + 0xc) == 0) {
          FUN_004aad10(this,param_1,0,param_2,piVar7);
          return param_1;
        }
        FUN_004aad10(this,param_1,iVar2,iVar2,piVar7);
        return param_1;
      }
    }
    piVar7 = (int *)FUN_004aaec0(this,local_8,piVar7);
    *param_1 = *piVar7;
    return param_1;
  }
  if ((*(int *)((int)this + 4) != 0) &&
     (uVar4 = FUN_004aa470(param_3,(undefined4 *)(param_2 + 0x10)), (char)uVar4 != '\0')) {
    if ((iVar2 == *(int *)this) ||
       ((iVar2 != 0 || (uVar4 = FUN_004aa470(piVar7,(undefined4 *)0x10), (char)uVar4 != '\0')))) {
      pcVar5 = (char *)FUN_004abbb0(piVar7);
      *(char **)(iVar2 + 8) = pcVar5;
      iVar1 = *(int *)this;
      if (iVar2 == iVar1) {
        *(char **)(iVar1 + 4) = pcVar5;
        *(char **)(*(int *)this + 0xc) = pcVar5;
      }
      else if (iVar2 == *(int *)(iVar1 + 8)) {
        *(char **)(iVar1 + 8) = pcVar5;
      }
    }
    else {
      pcVar5 = (char *)FUN_004abbb0(piVar7);
      _DAT_0000000c = pcVar5;
      if (*(int *)(*(int *)this + 0xc) == 0) {
        *(char **)(*(int *)this + 0xc) = pcVar5;
      }
    }
    *(int *)(pcVar5 + 4) = iVar2;
    pcVar5[8] = '\0';
    pcVar5[9] = '\0';
    pcVar5[10] = '\0';
    pcVar5[0xb] = '\0';
    pcVar5[0xc] = '\0';
    pcVar5[0xd] = '\0';
    pcVar5[0xe] = '\0';
    pcVar5[0xf] = '\0';
    FUN_004abea0(pcVar5,(int *)(*(int *)this + 4));
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
    *param_1 = (int)pcVar5;
    return param_1;
  }
  cVar3 = '\x01';
  iVar1 = *(int *)this;
  iVar2 = *(int *)(*(int *)this + 4);
  while (iVar2 != 0) {
    uVar4 = FUN_004aa470(piVar7,(undefined4 *)(iVar2 + 0x10));
    cVar3 = (char)uVar4;
    iVar1 = iVar2;
    if (cVar3 == '\0') {
      iVar2 = *(int *)(iVar2 + 0xc);
    }
    else {
      iVar2 = *(int *)(iVar2 + 8);
    }
  }
  local_18 = iVar1;
  if (cVar3 != '\0') {
    piVar6 = (int *)FUN_004abba0(this,&local_14);
    if (local_18 == *piVar6) {
      ppiVar8 = &param_3;
      param_3 = (int *)CONCAT31((*(uint32_t*)((char*)&param_3+1)),1);
      piVar7 = (int *)FUN_004aad10(this,&local_10,0,iVar1,piVar7);
      goto LAB_004a9bd4;
    }
    FUN_004ab8e0(&local_18);
  }
  uVar4 = FUN_004aa470((int *)(local_18 + 0x10),piVar7);
  if ((char)uVar4 == '\0') {
    ppiVar8 = (int **)&local_19;
    local_19 = 0;
    piVar7 = &local_18;
  }
  else {
    ppiVar8 = (int **)&param_2;
    param_2 = CONCAT31((*(uint32_t*)((char*)&param_2+1)),1);
    piVar7 = (int *)FUN_004aad10(this,&local_c,0,iVar1,piVar7);
  }
LAB_004a9bd4:
  FUN_004844c0(local_8,piVar7,(undefined1 *)ppiVar8);
  *param_1 = local_8[0];
  return param_1;
}


/* 004a9d40 size=62 */

void FUN_004a9d40(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  while (puVar1 = param_1, puVar1 != (undefined4 *)0x0) {
    FUN_004a9d40((undefined4 *)puVar1[3]);
    param_1 = (undefined4 *)puVar1[2];
    FUN_004a86e0((int)(puVar1 + 4));
    if (puVar1 != (undefined4 *)0x0) {
      FUN_004aa6f0(puVar1,0x18);
    }
  }
  return;
}


/* 004a9d80 size=661 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __thiscall FUN_004a9d80(void *this,int *param_1,int param_2,uint *param_3)

{
  uint *puVar1;
  char *pcVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  uint **ppuVar7;
  undefined1 local_19;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8 [2];
  
  puVar1 = param_3;
  iVar5 = param_2;
  iVar4 = *(int *)this;
  if (param_2 != *(int *)(iVar4 + 8)) {
    if (param_2 == iVar4) {
      iVar5 = *(int *)(iVar4 + 0xc);
      if (*(uint *)(iVar5 + 0x10) < *param_3) {
        if ((iVar5 == iVar4) || (*param_3 < *(uint *)(iVar5 + 0x10))) {
          pcVar2 = (char *)FUN_004abcf0(param_3);
          *(char **)(iVar5 + 8) = pcVar2;
          iVar4 = *(int *)this;
          if (iVar5 == iVar4) {
            *(char **)(iVar4 + 4) = pcVar2;
            *(char **)(*(int *)this + 0xc) = pcVar2;
          }
          else if (iVar5 == *(int *)(iVar4 + 8)) {
            *(char **)(iVar4 + 8) = pcVar2;
          }
        }
        else {
          pcVar2 = (char *)FUN_004abcf0(param_3);
          *(char **)(iVar5 + 0xc) = pcVar2;
          if (iVar5 == *(int *)(*(int *)this + 0xc)) {
            *(char **)(*(int *)this + 0xc) = pcVar2;
          }
        }
        *(int *)(pcVar2 + 4) = iVar5;
        pcVar2[8] = '\0';
        pcVar2[9] = '\0';
        pcVar2[10] = '\0';
        pcVar2[0xb] = '\0';
        pcVar2[0xc] = '\0';
        pcVar2[0xd] = '\0';
        pcVar2[0xe] = '\0';
        pcVar2[0xf] = '\0';
        FUN_004abea0(pcVar2,(int *)(*(int *)this + 4));
        *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
        *param_1 = (int)pcVar2;
        return param_1;
      }
    }
    else {
      FUN_004ab8e0(&param_2);
      if ((*(uint *)(param_2 + 0x10) < *param_3) && (*param_3 < *(uint *)(iVar5 + 0x10))) {
        if (*(int *)(param_2 + 0xc) == 0) {
          FUN_004ab080(this,param_1,0,param_2,param_3);
          return param_1;
        }
        FUN_004ab080(this,param_1,iVar5,iVar5,param_3);
        return param_1;
      }
    }
    piVar3 = (int *)FUN_004ab240(this,local_8,param_3);
    *param_1 = *piVar3;
    return param_1;
  }
  if (*(int *)((int)this + 4) != 0) {
    if (*param_3 < *(uint *)(param_2 + 0x10)) {
      if (((param_2 == iVar4) || (param_2 != 0)) || (*param_3 < *(uint *)(param_2 + 0x10))) {
        pcVar2 = (char *)FUN_004abcf0(param_3);
        *(char **)(iVar5 + 8) = pcVar2;
        iVar4 = *(int *)this;
        if (iVar5 == iVar4) {
          *(char **)(iVar4 + 4) = pcVar2;
          *(char **)(*(int *)this + 0xc) = pcVar2;
        }
        else if (iVar5 == *(int *)(iVar4 + 8)) {
          *(char **)(iVar4 + 8) = pcVar2;
        }
      }
      else {
        pcVar2 = (char *)FUN_004abcf0(param_3);
        _DAT_0000000c = pcVar2;
        if (*(int *)(*(int *)this + 0xc) == 0) {
          *(char **)(*(int *)this + 0xc) = pcVar2;
        }
      }
      *(int *)(pcVar2 + 4) = iVar5;
      pcVar2[8] = '\0';
      pcVar2[9] = '\0';
      pcVar2[10] = '\0';
      pcVar2[0xb] = '\0';
      pcVar2[0xc] = '\0';
      pcVar2[0xd] = '\0';
      pcVar2[0xe] = '\0';
      pcVar2[0xf] = '\0';
      FUN_004abea0(pcVar2,(int *)(*(int *)this + 4));
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
      *param_1 = (int)pcVar2;
      return param_1;
    }
  }
  bVar6 = true;
  if (*(int *)(iVar4 + 4) != 0) {
    iVar5 = *(int *)(iVar4 + 4);
    do {
      iVar4 = iVar5;
      bVar6 = *param_3 < *(uint *)(iVar4 + 0x10);
      if (bVar6) {
        iVar5 = *(int *)(iVar4 + 8);
      }
      else {
        iVar5 = *(int *)(iVar4 + 0xc);
      }
    } while (iVar5 != 0);
  }
  local_18 = iVar4;
  if (bVar6) {
    piVar3 = (int *)FUN_004abba0(this,&local_14);
    if (local_18 == *piVar3) {
      ppuVar7 = &param_3;
      param_3 = (uint *)CONCAT31((*(uint32_t*)((char*)&param_3+1)),1);
      piVar3 = (int *)FUN_004ab080(this,&local_10,0,iVar4,puVar1);
      goto LAB_004a9edc;
    }
    FUN_004ab8e0(&local_18);
  }
  if (*(uint *)(local_18 + 0x10) < *puVar1) {
    ppuVar7 = (uint **)&param_2;
    param_2 = CONCAT31((*(uint32_t*)((char*)&param_2+1)),1);
    piVar3 = (int *)FUN_004ab080(this,&local_c,0,iVar4,puVar1);
  }
  else {
    ppuVar7 = (uint **)&local_19;
    piVar3 = &local_18;
    local_19 = 0;
  }
LAB_004a9edc:
  FUN_004844c0(local_8,piVar3,(undefined1 *)ppuVar7);
  *param_1 = local_8[0];
  return param_1;
}


/* 004aa020 size=54 */

void FUN_004aa020(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  while (puVar1 = param_1, puVar1 != (undefined4 *)0x0) {
    FUN_004aa020((undefined4 *)puVar1[3]);
    param_1 = (undefined4 *)puVar1[2];
    if (puVar1 != (undefined4 *)0x0) {
      FUN_004aa6f0(puVar1,0x18);
    }
  }
  return;
}


/* 004aa060 size=661 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __thiscall FUN_004aa060(void *this,int *param_1,int param_2,uint *param_3)

{
  uint *puVar1;
  char *pcVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  uint **ppuVar7;
  undefined1 local_19;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8 [2];
  
  puVar1 = param_3;
  iVar5 = param_2;
  iVar4 = *(int *)this;
  if (param_2 != *(int *)(iVar4 + 8)) {
    if (param_2 == iVar4) {
      iVar5 = *(int *)(iVar4 + 0xc);
      if (*(uint *)(iVar5 + 0x10) < *param_3) {
        if ((iVar5 == iVar4) || (*param_3 < *(uint *)(iVar5 + 0x10))) {
          pcVar2 = (char *)FUN_004abdd0(param_3);
          *(char **)(iVar5 + 8) = pcVar2;
          iVar4 = *(int *)this;
          if (iVar5 == iVar4) {
            *(char **)(iVar4 + 4) = pcVar2;
            *(char **)(*(int *)this + 0xc) = pcVar2;
          }
          else if (iVar5 == *(int *)(iVar4 + 8)) {
            *(char **)(iVar4 + 8) = pcVar2;
          }
        }
        else {
          pcVar2 = (char *)FUN_004abdd0(param_3);
          *(char **)(iVar5 + 0xc) = pcVar2;
          if (iVar5 == *(int *)(*(int *)this + 0xc)) {
            *(char **)(*(int *)this + 0xc) = pcVar2;
          }
        }
        *(int *)(pcVar2 + 4) = iVar5;
        pcVar2[8] = '\0';
        pcVar2[9] = '\0';
        pcVar2[10] = '\0';
        pcVar2[0xb] = '\0';
        pcVar2[0xc] = '\0';
        pcVar2[0xd] = '\0';
        pcVar2[0xe] = '\0';
        pcVar2[0xf] = '\0';
        FUN_004abea0(pcVar2,(int *)(*(int *)this + 4));
        *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
        *param_1 = (int)pcVar2;
        return param_1;
      }
    }
    else {
      FUN_004ab8e0(&param_2);
      if ((*(uint *)(param_2 + 0x10) < *param_3) && (*param_3 < *(uint *)(iVar5 + 0x10))) {
        if (*(int *)(param_2 + 0xc) == 0) {
          FUN_004ab3c0(this,param_1,0,param_2,param_3);
          return param_1;
        }
        FUN_004ab3c0(this,param_1,iVar5,iVar5,param_3);
        return param_1;
      }
    }
    piVar3 = (int *)FUN_004ab580(this,local_8,param_3);
    *param_1 = *piVar3;
    return param_1;
  }
  if (*(int *)((int)this + 4) != 0) {
    if (*param_3 < *(uint *)(param_2 + 0x10)) {
      if (((param_2 == iVar4) || (param_2 != 0)) || (*param_3 < *(uint *)(param_2 + 0x10))) {
        pcVar2 = (char *)FUN_004abdd0(param_3);
        *(char **)(iVar5 + 8) = pcVar2;
        iVar4 = *(int *)this;
        if (iVar5 == iVar4) {
          *(char **)(iVar4 + 4) = pcVar2;
          *(char **)(*(int *)this + 0xc) = pcVar2;
        }
        else if (iVar5 == *(int *)(iVar4 + 8)) {
          *(char **)(iVar4 + 8) = pcVar2;
        }
      }
      else {
        pcVar2 = (char *)FUN_004abdd0(param_3);
        _DAT_0000000c = pcVar2;
        if (*(int *)(*(int *)this + 0xc) == 0) {
          *(char **)(*(int *)this + 0xc) = pcVar2;
        }
      }
      *(int *)(pcVar2 + 4) = iVar5;
      pcVar2[8] = '\0';
      pcVar2[9] = '\0';
      pcVar2[10] = '\0';
      pcVar2[0xb] = '\0';
      pcVar2[0xc] = '\0';
      pcVar2[0xd] = '\0';
      pcVar2[0xe] = '\0';
      pcVar2[0xf] = '\0';
      FUN_004abea0(pcVar2,(int *)(*(int *)this + 4));
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
      *param_1 = (int)pcVar2;
      return param_1;
    }
  }
  bVar6 = true;
  if (*(int *)(iVar4 + 4) != 0) {
    iVar5 = *(int *)(iVar4 + 4);
    do {
      iVar4 = iVar5;
      bVar6 = *param_3 < *(uint *)(iVar4 + 0x10);
      if (bVar6) {
        iVar5 = *(int *)(iVar4 + 8);
      }
      else {
        iVar5 = *(int *)(iVar4 + 0xc);
      }
    } while (iVar5 != 0);
  }
  local_18 = iVar4;
  if (bVar6) {
    piVar3 = (int *)FUN_004abba0(this,&local_14);
    if (local_18 == *piVar3) {
      ppuVar7 = &param_3;
      param_3 = (uint *)CONCAT31((*(uint32_t*)((char*)&param_3+1)),1);
      piVar3 = (int *)FUN_004ab3c0(this,&local_10,0,iVar4,puVar1);
      goto LAB_004aa1bc;
    }
    FUN_004ab8e0(&local_18);
  }
  if (*(uint *)(local_18 + 0x10) < *puVar1) {
    ppuVar7 = (uint **)&param_2;
    param_2 = CONCAT31((*(uint32_t*)((char*)&param_2+1)),1);
    piVar3 = (int *)FUN_004ab3c0(this,&local_c,0,iVar4,puVar1);
  }
  else {
    ppuVar7 = (uint **)&local_19;
    piVar3 = &local_18;
    local_19 = 0;
  }
LAB_004aa1bc:
  FUN_004844c0(local_8,piVar3,(undefined1 *)ppuVar7);
  *param_1 = local_8[0];
  return param_1;
}


/* 004aa300 size=52 */

void __thiscall FUN_004aa300(void *this,int *param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)this;
  if (*(int *)(iVar3 + 4) == 0) {
    *param_1 = iVar3;
    return;
  }
  iVar1 = *(int *)(iVar3 + 4);
  do {
    if (*(uint *)(iVar1 + 0x10) < *param_2) {
      iVar2 = *(int *)(iVar1 + 0xc);
    }
    else {
      iVar2 = *(int *)(iVar1 + 8);
      iVar3 = iVar1;
    }
    iVar1 = iVar2;
  } while (iVar2 != 0);
  *param_1 = iVar3;
  return;
}


/* 004aa340 size=96 */

void __thiscall FUN_004aa340(void *this,undefined4 *param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  
  uVar1 = (param_2 - (int)param_1) + 1;
  if (uVar1 == 0) {
    FUN_004a5b30(s_basic_string_004de5c8);
  }
  else {
    iVar3 = FUN_004aa520(uVar1);
    *(int *)this = iVar3;
    *(int *)((int)this + 4) = iVar3;
    *(uint *)((int)this + 8) = iVar3 + uVar1;
  }
  puVar2 = *(undefined4 **)this;
  FUN_004bab10(puVar2,param_1,param_2 - (int)param_1);
  puVar4 = (undefined1 *)((int)puVar2 + (param_3 - (int)param_1));
  *(undefined1 **)((int)this + 4) = puVar4;
  *puVar4 = 0;
  return;
}


/* 004aa3a0 size=92 */

void __thiscall FUN_004aa3a0(void *this,undefined1 *param_1,int param_2)

{
  uint uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  
  iVar5 = param_2 - (int)param_1;
  uVar1 = iVar5 + 1;
  if (uVar1 == 0) {
    FUN_004a5b30(s_basic_string_004de5c8);
  }
  else {
    iVar3 = FUN_004aa520(uVar1);
    *(int *)this = iVar3;
    *(int *)((int)this + 4) = iVar3;
    *(uint *)((int)this + 8) = iVar3 + uVar1;
  }
  puVar4 = *(undefined1 **)this;
  if (0 < iVar5) {
    do {
      uVar2 = *param_1;
      param_1 = param_1 + 1;
      *puVar4 = uVar2;
      puVar4 = puVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  *(undefined1 **)((int)this + 4) = puVar4;
  *puVar4 = 0;
  return;
}


/* 004aa400 size=107 */

void __thiscall FUN_004aa400(void *this,undefined2 *param_1,int param_2)

{
  uint uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  
  iVar5 = param_2 - (int)param_1 >> 1;
  uVar1 = iVar5 + 1;
  if ((uVar1 < 0x80000000) && (uVar1 != 0)) {
    iVar3 = FUN_004aa520(uVar1 * 2);
    *(uint *)((int)this + 8) = uVar1 * 2 + iVar3;
    *(int *)this = iVar3;
    *(int *)((int)this + 4) = iVar3;
  }
  else {
    FUN_004a5b30(s_basic_string_004de5c8);
  }
  puVar4 = *(undefined2 **)this;
  if (0 < iVar5) {
    do {
      uVar2 = *param_1;
      param_1 = param_1 + 1;
      *puVar4 = uVar2;
      puVar4 = puVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  *(undefined2 **)((int)this + 4) = puVar4;
  *puVar4 = 0;
  return;
}


/* 004aa470 size=161 */

/* FUN_004aa470: lifted from original x86 -> lt_lifted.c */


/* 004aa520 size=453 */

int __cdecl FUN_004aa520(uint param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  LONG LVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uVar8 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9c48;
  local_c = ExceptionList;
  if (0x80 < param_1) {
    ExceptionList = &local_c;
    FUN_00430de0(param_1);
    ExceptionList = local_c;
    return;
  }
  uVar1 = param_1 - 1;
  ExceptionList = &local_c;
  LVar4 = InterlockedExchange(&DAT_004ed050,1);
  uVar3 = DAT_004de6a4;
  if (LVar4 != 0) {
    uVar8 = 0;
    if (DAT_004de6a4 != 0) {
      uVar7 = DAT_004ec684 >> 1;
      do {
        if (((uVar7 <= uVar8) && (DAT_004ed050 == 0)) &&
           (LVar4 = InterlockedExchange(&DAT_004ed050,1), LVar4 == 0)) {
          DAT_004de6a4 = 1000;
          DAT_004ec684 = uVar8;
          goto LAB_004aa64d;
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar3);
    }
    DAT_004de6a4 = 0x1e;
    iVar10 = 6;
    while( true ) {
      iVar9 = iVar10;
      if (0x1b < iVar10) {
        iVar9 = 0x1b;
      }
      LVar4 = InterlockedExchange(&DAT_004ed050,1);
      if (LVar4 == 0) break;
      if (iVar9 < 0x15) {
        Sleep(0);
        iVar10 = iVar10 + 1;
      }
      else {
        Sleep(1 << ((char)iVar9 - 0x14U & 0x1f));
        iVar10 = iVar10 + 1;
      }
    }
LAB_004aa64d:
    uVar8 = param_1;
  }
  local_4 = 0;
  piVar2 = *(int **)(&DAT_004ec644 + (uVar1 >> 3) * 4);
  if (piVar2 == (int *)0x0) {
    uVar8 = uVar8 + 7 & 0xfffffff8;
    param_1 = 0x14;
    puVar5 = FUN_004ac1c0(uVar8,&param_1);
    if (param_1 != 1) {
      puVar5 = (undefined4 *)((int)puVar5 + uVar8);
      *(undefined4 **)(&DAT_004ec644 + (uVar8 - 1 >> 3) * 4) = puVar5;
      iVar10 = 1;
      puVar6 = puVar5;
      if (param_1 != 2) {
        do {
          puVar5 = (undefined4 *)((int)puVar6 + uVar8);
          *puVar6 = puVar5;
          iVar10 = iVar10 + 1;
          puVar6 = puVar5;
        } while (param_1 - 1 != iVar10);
      }
      *puVar5 = 0;
    }
  }
  else {
    *(int *)(&DAT_004ec644 + (uVar1 >> 3) * 4) = *piVar2;
  }
  DAT_004ed050 = 0;
  ExceptionList = local_c;
  return;
}


/* 004aa6f0 size=311 */

int __cdecl FUN_004aa6f0(undefined4 *param_1,uint param_2)

{
  uint uVar1;
  LONG LVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  if (0x80 < param_2) {
    FUN_00430df0((undefined *)param_1);
    return;
  }
  LVar2 = InterlockedExchange(&DAT_004ed050,1);
  uVar1 = DAT_004de6a4;
  if (LVar2 != 0) {
    uVar4 = 0;
    if (DAT_004de6a4 != 0) {
      uVar3 = DAT_004ec684 >> 1;
      do {
        if (((uVar3 <= uVar4) && (DAT_004ed050 == 0)) &&
           (LVar2 = InterlockedExchange(&DAT_004ed050,1), LVar2 == 0)) {
          DAT_004de6a4 = 1000;
          DAT_004ec684 = uVar4;
          goto LAB_004aa7f9;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < uVar1);
    }
    DAT_004de6a4 = 0x1e;
    iVar6 = 6;
    while( true ) {
      iVar5 = iVar6;
      if (0x1b < iVar6) {
        iVar5 = 0x1b;
      }
      LVar2 = InterlockedExchange(&DAT_004ed050,1);
      if (LVar2 == 0) break;
      if (iVar5 < 0x15) {
        Sleep(0);
        iVar6 = iVar6 + 1;
      }
      else {
        Sleep(1 << ((char)iVar5 - 0x14U & 0x1f));
        iVar6 = iVar6 + 1;
      }
    }
  }
LAB_004aa7f9:
  *param_1 = *(undefined4 *)(&DAT_004ec644 + (param_2 - 1 >> 3) * 4);
  *(undefined4 **)(&DAT_004ec644 + (param_2 - 1 >> 3) * 4) = param_1;
  DAT_004ed050 = 0;
  return;
}


/* 004aa830 size=5 */

undefined4 __cdecl FUN_004aa830(undefined4 param_1)

{
  return param_1;
}


/* 004aa840 size=131 */

uint __cdecl FUN_004aa840(int param_1,uint param_2,short *param_3,int param_4)

{
  uint uVar1;
  short *psVar2;
  uint *puVar3;
  int iVar4;
  uint local_4;
  
  local_4 = (int)(param_2 - param_1) >> 1;
  iVar4 = param_4 - (int)param_3 >> 1;
  puVar3 = &param_2;
  if ((int)local_4 <= iVar4) {
    puVar3 = &local_4;
  }
  uVar1 = 0;
  if (*puVar3 != 0) {
    psVar2 = param_3;
    do {
      if (*(short *)((param_1 - (int)param_3) + (int)psVar2) != *psVar2) {
        uVar1 = (-(uint)(*(ushort *)(param_1 + uVar1 * 2) < (ushort)param_3[uVar1]) & 0xfffffffe) +
                1;
        if (uVar1 != 0) {
          return uVar1;
        }
        break;
      }
      uVar1 = uVar1 + 1;
      psVar2 = psVar2 + 1;
    } while (uVar1 < *puVar3);
  }
  if ((int)local_4 < iVar4) {
    return 0xffffffff;
  }
  return (uint)(iVar4 < (int)local_4);
}


/* 004aa8d0 size=11 */

void FUN_004aa8d0(void)

{
  DAT_004ed050 = 0;
  return;
}


/* 004aa8e0 size=70 */

int __cdecl FUN_004aa8e0(int param_1,short *param_2,uint param_3)

{
  uint uVar1;
  short *psVar2;
  
  uVar1 = 0;
  if (param_3 != 0) {
    psVar2 = param_2;
    do {
      if (*(short *)((param_1 - (int)param_2) + (int)psVar2) != *psVar2) {
        return (-(uint)(*(ushort *)(param_1 + uVar1 * 2) < (ushort)param_2[uVar1]) & 0xfffffffe) + 1
        ;
      }
      uVar1 = uVar1 + 1;
      psVar2 = psVar2 + 1;
    } while (uVar1 < param_3);
  }
  return 0;
}


/* 004aa930 size=442 */

int __thiscall FUN_004aa930(void *this,undefined4 *param_1,int param_2,int param_3,uint *param_4)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  int *piVar8;
  
  if (((param_3 == *(int *)this) || (param_2 != 0)) || (*param_4 < *(uint *)(param_3 + 0x10))) {
    pcVar5 = (char *)FUN_004abad0(param_4);
    *(char **)(param_3 + 8) = pcVar5;
    iVar1 = *(int *)this;
    if (param_3 == iVar1) {
      *(char **)(iVar1 + 4) = pcVar5;
      *(char **)(*(int *)this + 0xc) = pcVar5;
    }
    else if (param_3 == *(int *)(iVar1 + 8)) {
      *(char **)(iVar1 + 8) = pcVar5;
    }
  }
  else {
    pcVar5 = (char *)FUN_004abad0(param_4);
    *(char **)(param_3 + 0xc) = pcVar5;
    if (param_3 == *(int *)(*(int *)this + 0xc)) {
      *(char **)(*(int *)this + 0xc) = pcVar5;
    }
  }
  *(int *)(pcVar5 + 4) = param_3;
  pcVar5[8] = '\0';
  pcVar5[9] = '\0';
  pcVar5[10] = '\0';
  pcVar5[0xb] = '\0';
  pcVar5[0xc] = '\0';
  pcVar5[0xd] = '\0';
  pcVar5[0xe] = '\0';
  pcVar5[0xf] = '\0';
  iVar1 = *(int *)this;
  *pcVar5 = '\0';
  piVar8 = (int *)(iVar1 + 4);
  pcVar7 = pcVar5;
  if (pcVar5 != (char *)*piVar8) {
    do {
      pcVar2 = *(char **)(pcVar7 + 4);
      if (*pcVar2 != '\0') break;
      pcVar6 = *(char **)(*(int *)(pcVar2 + 4) + 8);
      if (pcVar2 == pcVar6) {
        pcVar6 = *(char **)(*(int *)(pcVar2 + 4) + 0xc);
        if ((pcVar6 == (char *)0x0) || (*pcVar6 != '\0')) {
          if (pcVar7 == *(char **)(pcVar2 + 0xc)) {
            iVar1 = *(int *)(pcVar2 + 0xc);
            *(undefined4 *)(pcVar2 + 0xc) = *(undefined4 *)(iVar1 + 8);
            if (*(int *)(iVar1 + 8) != 0) {
              *(char **)(*(int *)(iVar1 + 8) + 4) = pcVar2;
            }
            *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(pcVar2 + 4);
            if (pcVar2 == (char *)*piVar8) {
              *piVar8 = iVar1;
            }
            else {
              iVar3 = *(int *)(pcVar2 + 4);
              if (pcVar2 == *(char **)(iVar3 + 8)) {
                *(int *)(iVar3 + 8) = iVar1;
              }
              else {
                *(int *)(iVar3 + 0xc) = iVar1;
              }
            }
            *(char **)(iVar1 + 8) = pcVar2;
            *(int *)(pcVar2 + 4) = iVar1;
            pcVar7 = pcVar2;
          }
          **(undefined1 **)(pcVar7 + 4) = 1;
          **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
          iVar1 = *(int *)(*(int *)(pcVar7 + 4) + 4);
          iVar3 = *(int *)(iVar1 + 8);
          *(undefined4 *)(iVar1 + 8) = *(undefined4 *)(iVar3 + 0xc);
          if (*(int *)(iVar3 + 0xc) != 0) {
            *(int *)(*(int *)(iVar3 + 0xc) + 4) = iVar1;
          }
          *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar1 + 4);
          if (iVar1 == *piVar8) {
            *piVar8 = iVar3;
            *(int *)(iVar3 + 0xc) = iVar1;
            *(int *)(iVar1 + 4) = iVar3;
          }
          else {
            iVar4 = *(int *)(iVar1 + 4);
            if (iVar1 == *(int *)(iVar4 + 0xc)) {
              *(int *)(iVar4 + 0xc) = iVar3;
              *(int *)(iVar3 + 0xc) = iVar1;
              *(int *)(iVar1 + 4) = iVar3;
            }
            else {
              *(int *)(iVar4 + 8) = iVar3;
              *(int *)(iVar3 + 0xc) = iVar1;
              *(int *)(iVar1 + 4) = iVar3;
            }
          }
        }
        else {
LAB_004aa9d6:
          *pcVar2 = '\x01';
          *pcVar6 = '\x01';
          **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
          pcVar7 = *(char **)(*(int *)(pcVar7 + 4) + 4);
        }
      }
      else {
        if ((pcVar6 != (char *)0x0) && (*pcVar6 == '\0')) goto LAB_004aa9d6;
        if (pcVar7 == *(char **)(pcVar2 + 8)) {
          FUN_004aab40((int)pcVar2,piVar8);
          pcVar7 = pcVar2;
        }
        **(undefined1 **)(pcVar7 + 4) = 1;
        **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
        FUN_004aaaf0(*(int *)(*(int *)(pcVar7 + 4) + 4),piVar8);
      }
    } while (pcVar7 != (char *)*piVar8);
  }
  *(undefined1 *)*piVar8 = 1;
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  *param_1 = pcVar5;
  return;
}


/* 004aaaf0 size=74 */

void __cdecl FUN_004aaaf0(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar1 + 8);
  if (*(int *)(iVar1 + 8) != 0) {
    *(int *)(*(int *)(iVar1 + 8) + 4) = param_1;
  }
  *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(param_1 + 4);
  if (param_1 == *param_2) {
    *param_2 = iVar1;
    *(int *)(iVar1 + 8) = param_1;
    *(int *)(param_1 + 4) = iVar1;
    return;
  }
  iVar2 = *(int *)(param_1 + 4);
  if (param_1 == *(int *)(iVar2 + 8)) {
    *(int *)(iVar2 + 8) = iVar1;
    *(int *)(iVar1 + 8) = param_1;
    *(int *)(param_1 + 4) = iVar1;
    return;
  }
  *(int *)(iVar2 + 0xc) = iVar1;
  *(int *)(iVar1 + 8) = param_1;
  *(int *)(param_1 + 4) = iVar1;
  return;
}


/* 004aab40 size=74 */

void __cdecl FUN_004aab40(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(iVar1 + 0xc);
  if (*(int *)(iVar1 + 0xc) != 0) {
    *(int *)(*(int *)(iVar1 + 0xc) + 4) = param_1;
  }
  *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(param_1 + 4);
  if (param_1 == *param_2) {
    *param_2 = iVar1;
    *(int *)(iVar1 + 0xc) = param_1;
    *(int *)(param_1 + 4) = iVar1;
    return;
  }
  iVar2 = *(int *)(param_1 + 4);
  if (param_1 == *(int *)(iVar2 + 0xc)) {
    *(int *)(iVar2 + 0xc) = iVar1;
    *(int *)(iVar1 + 0xc) = param_1;
    *(int *)(param_1 + 4) = iVar1;
    return;
  }
  *(int *)(iVar2 + 8) = iVar1;
  *(int *)(iVar1 + 0xc) = param_1;
  *(int *)(param_1 + 4) = iVar1;
  return;
}


/* 004aab90 size=371 */

int __thiscall FUN_004aab90(void *this,int *param_1,uint *param_2)

{
  uint *puVar1;
  uint *puVar2;
  char *pcVar3;
  uint *puVar4;
  uint *puVar5;
  bool bVar6;
  
  puVar2 = param_2;
  puVar1 = *(uint **)this;
  bVar6 = true;
  puVar5 = puVar1;
  if ((uint *)puVar1[1] != (uint *)0x0) {
    puVar4 = (uint *)puVar1[1];
    do {
      puVar5 = puVar4;
      bVar6 = *param_2 < puVar5[4];
      if (bVar6) {
        puVar4 = (uint *)puVar5[2];
      }
      else {
        puVar4 = (uint *)puVar5[3];
      }
    } while (puVar4 != (uint *)0x0);
  }
  puVar4 = puVar5;
  if (bVar6) {
    if (puVar5 == (uint *)puVar1[2]) {
      if ((puVar5 == puVar1) || (*param_2 < puVar5[4])) {
        param_2 = puVar5;
        pcVar3 = (char *)FUN_004abad0(puVar2);
        puVar5[2] = (uint)pcVar3;
        puVar1 = *(uint **)this;
        if (puVar5 == puVar1) {
          puVar1[1] = (uint)pcVar3;
          *(char **)(*(int *)this + 0xc) = pcVar3;
        }
        else if (puVar5 == (uint *)puVar1[2]) {
          puVar1[2] = (uint)pcVar3;
        }
      }
      else {
        param_2 = puVar5;
        pcVar3 = (char *)FUN_004abad0(puVar2);
        puVar5[3] = (uint)pcVar3;
        if (puVar5 == *(uint **)(*(int *)this + 0xc)) {
          *(char **)(*(int *)this + 0xc) = pcVar3;
        }
      }
      *(uint **)(pcVar3 + 4) = puVar5;
      pcVar3[8] = '\0';
      pcVar3[9] = '\0';
      pcVar3[10] = '\0';
      pcVar3[0xb] = '\0';
      pcVar3[0xc] = '\0';
      pcVar3[0xd] = '\0';
      pcVar3[0xe] = '\0';
      pcVar3[0xf] = '\0';
      FUN_004abea0(pcVar3,(int *)(*(int *)this + 4));
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
      *param_1 = (int)pcVar3;
      *(undefined1 *)(param_1 + 1) = 1;
      return;
    }
    param_2 = puVar5;
    FUN_004ab8e0((int *)&param_2);
    puVar4 = param_2;
  }
  param_2 = puVar4;
  if (*puVar2 <= param_2[4]) {
    *param_1 = (int)param_2;
    *(undefined1 *)(param_1 + 1) = 0;
    return;
  }
  if ((puVar5 == *(uint **)this) || (*puVar2 < puVar5[4])) {
    pcVar3 = (char *)FUN_004abad0(puVar2);
    puVar5[2] = (uint)pcVar3;
    puVar1 = *(uint **)this;
    if (puVar5 == puVar1) {
      puVar1[1] = (uint)pcVar3;
      *(char **)(*(int *)this + 0xc) = pcVar3;
    }
    else if (puVar5 == (uint *)puVar1[2]) {
      puVar1[2] = (uint)pcVar3;
    }
  }
  else {
    pcVar3 = (char *)FUN_004abad0(puVar2);
    puVar5[3] = (uint)pcVar3;
    if (puVar5 == *(uint **)(*(int *)this + 0xc)) {
      *(char **)(*(int *)this + 0xc) = pcVar3;
    }
  }
  *(uint **)(pcVar3 + 4) = puVar5;
  pcVar3[8] = '\0';
  pcVar3[9] = '\0';
  pcVar3[10] = '\0';
  pcVar3[0xb] = '\0';
  pcVar3[0xc] = '\0';
  pcVar3[0xd] = '\0';
  pcVar3[0xe] = '\0';
  pcVar3[0xf] = '\0';
  FUN_004abea0(pcVar3,(int *)(*(int *)this + 4));
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  *param_1 = (int)pcVar3;
  *(undefined1 *)(param_1 + 1) = 1;
  return;
}


/* 004aad10 size=417 */

int __thiscall FUN_004aad10(void *this,undefined4 *param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  int *piVar8;
  
  if (((param_3 == *(int *)this) || (param_2 != 0)) ||
     (uVar5 = FUN_004aa840(*param_4,param_4[1],*(short **)(param_3 + 0x10),*(int *)(param_3 + 0x14))
     , (int)uVar5 < 0)) {
    pcVar6 = (char *)FUN_004abbb0(param_4);
    *(char **)(param_3 + 8) = pcVar6;
    iVar1 = *(int *)this;
    if (param_3 == iVar1) {
      *(char **)(iVar1 + 4) = pcVar6;
      *(char **)(*(int *)this + 0xc) = pcVar6;
    }
    else if (param_3 == *(int *)(iVar1 + 8)) {
      *(char **)(iVar1 + 8) = pcVar6;
    }
  }
  else {
    pcVar6 = (char *)FUN_004abbb0(param_4);
    *(char **)(param_3 + 0xc) = pcVar6;
    if (param_3 == *(int *)(*(int *)this + 0xc)) {
      *(char **)(*(int *)this + 0xc) = pcVar6;
    }
  }
  *(int *)(pcVar6 + 4) = param_3;
  pcVar6[8] = '\0';
  pcVar6[9] = '\0';
  pcVar6[10] = '\0';
  pcVar6[0xb] = '\0';
  pcVar6[0xc] = '\0';
  pcVar6[0xd] = '\0';
  pcVar6[0xe] = '\0';
  pcVar6[0xf] = '\0';
  iVar1 = *(int *)this;
  *pcVar6 = '\0';
  piVar8 = (int *)(iVar1 + 4);
  pcVar7 = pcVar6;
  if (pcVar6 != (char *)*piVar8) {
    do {
      pcVar2 = *(char **)(pcVar7 + 4);
      if (*pcVar2 != '\0') break;
      pcVar3 = *(char **)(*(int *)(pcVar2 + 4) + 8);
      if (pcVar2 == pcVar3) {
        pcVar3 = *(char **)(*(int *)(pcVar2 + 4) + 0xc);
        if ((pcVar3 == (char *)0x0) || (*pcVar3 != '\0')) {
          if (pcVar7 == *(char **)(pcVar2 + 0xc)) {
            iVar1 = *(int *)(pcVar2 + 0xc);
            *(undefined4 *)(pcVar2 + 0xc) = *(undefined4 *)(iVar1 + 8);
            if (*(int *)(iVar1 + 8) != 0) {
              *(char **)(*(int *)(iVar1 + 8) + 4) = pcVar2;
            }
            *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(pcVar2 + 4);
            if (pcVar2 == (char *)*piVar8) {
              *piVar8 = iVar1;
            }
            else {
              iVar4 = *(int *)(pcVar2 + 4);
              if (pcVar2 == *(char **)(iVar4 + 8)) {
                *(int *)(iVar4 + 8) = iVar1;
              }
              else {
                *(int *)(iVar4 + 0xc) = iVar1;
              }
            }
            *(char **)(iVar1 + 8) = pcVar2;
            *(int *)(pcVar2 + 4) = iVar1;
            pcVar7 = pcVar2;
          }
          **(undefined1 **)(pcVar7 + 4) = 1;
          **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
          FUN_004aab40(*(int *)(*(int *)(pcVar7 + 4) + 4),piVar8);
        }
        else {
          *pcVar2 = '\x01';
          *pcVar3 = '\x01';
          **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
          pcVar7 = *(char **)(*(int *)(pcVar7 + 4) + 4);
        }
      }
      else if ((pcVar3 == (char *)0x0) || (*pcVar3 != '\0')) {
        if (pcVar7 == *(char **)(pcVar2 + 8)) {
          FUN_004aab40((int)pcVar2,piVar8);
          pcVar7 = pcVar2;
        }
        **(undefined1 **)(pcVar7 + 4) = 1;
        **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
        FUN_004aaaf0(*(int *)(*(int *)(pcVar7 + 4) + 4),piVar8);
      }
      else {
        *pcVar2 = '\x01';
        *pcVar3 = '\x01';
        **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
        pcVar7 = *(char **)(*(int *)(pcVar7 + 4) + 4);
      }
    } while (pcVar7 != (char *)*piVar8);
  }
  *(undefined1 *)*piVar8 = 1;
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  *param_1 = pcVar6;
  return;
}


/* 004aaec0 size=446 */

int __thiscall FUN_004aaec0(void *this,int *param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  undefined4 uVar5;
  char *pcVar6;
  bool bVar7;
  
  piVar3 = param_2;
  bVar7 = true;
  piVar2 = *(int **)this;
  piVar1 = (int *)(*(int **)this)[1];
  while (piVar1 != (int *)0x0) {
    uVar4 = FUN_004aa840(*piVar3,piVar3[1],(short *)piVar1[4],piVar1[5]);
    bVar7 = (int)uVar4 < 0;
    piVar2 = piVar1;
    if (bVar7) {
      piVar1 = (int *)piVar1[2];
    }
    else {
      piVar1 = (int *)piVar1[3];
    }
  }
  param_2 = piVar2;
  if (bVar7) {
    if (piVar2 == (int *)(*(int **)this)[2]) {
      if ((piVar2 == *(int **)this) ||
         (uVar5 = FUN_004aa470(piVar3,piVar2 + 4), (char)uVar5 != '\0')) {
        pcVar6 = (char *)FUN_004abbb0(piVar3);
        piVar2[2] = (int)pcVar6;
        piVar1 = *(int **)this;
        if (piVar2 == piVar1) {
          piVar1[1] = (int)pcVar6;
          *(char **)(*(int *)this + 0xc) = pcVar6;
        }
        else if (piVar2 == (int *)piVar1[2]) {
          piVar1[2] = (int)pcVar6;
        }
      }
      else {
        pcVar6 = (char *)FUN_004abbb0(piVar3);
        piVar2[3] = (int)pcVar6;
        if (piVar2 == *(int **)(*(int *)this + 0xc)) {
          *(char **)(*(int *)this + 0xc) = pcVar6;
        }
      }
      *(int **)(pcVar6 + 4) = piVar2;
      pcVar6[8] = '\0';
      pcVar6[9] = '\0';
      pcVar6[10] = '\0';
      pcVar6[0xb] = '\0';
      pcVar6[0xc] = '\0';
      pcVar6[0xd] = '\0';
      pcVar6[0xe] = '\0';
      pcVar6[0xf] = '\0';
      FUN_004abea0(pcVar6,(int *)(*(int *)this + 4));
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
      *param_1 = (int)pcVar6;
      *(undefined1 *)(param_1 + 1) = 1;
      return;
    }
    FUN_004ab8e0((int *)&param_2);
  }
  uVar4 = FUN_004aa840(param_2[4],param_2[5],(short *)*piVar3,piVar3[1]);
  if (-1 < (int)uVar4) {
    *param_1 = (int)param_2;
    *(undefined1 *)(param_1 + 1) = 0;
    return;
  }
  if ((piVar2 == *(int **)this) || (uVar5 = FUN_004aa470(piVar3,piVar2 + 4), (char)uVar5 != '\0')) {
    pcVar6 = (char *)FUN_004abbb0(piVar3);
    piVar2[2] = (int)pcVar6;
    piVar1 = *(int **)this;
    if (piVar2 == piVar1) {
      piVar1[1] = (int)pcVar6;
      *(char **)(*(int *)this + 0xc) = pcVar6;
    }
    else if (piVar2 == (int *)piVar1[2]) {
      piVar1[2] = (int)pcVar6;
    }
  }
  else {
    pcVar6 = (char *)FUN_004abbb0(piVar3);
    piVar2[3] = (int)pcVar6;
    if (piVar2 == *(int **)(*(int *)this + 0xc)) {
      *(char **)(*(int *)this + 0xc) = pcVar6;
    }
  }
  *(int **)(pcVar6 + 4) = piVar2;
  pcVar6[8] = '\0';
  pcVar6[9] = '\0';
  pcVar6[10] = '\0';
  pcVar6[0xb] = '\0';
  pcVar6[0xc] = '\0';
  pcVar6[0xd] = '\0';
  pcVar6[0xe] = '\0';
  pcVar6[0xf] = '\0';
  FUN_004abea0(pcVar6,(int *)(*(int *)this + 4));
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  *param_1 = (int)pcVar6;
  *(undefined1 *)(param_1 + 1) = 1;
  return;
}


/* 004ab080 size=442 */

int __thiscall FUN_004ab080(void *this,undefined4 *param_1,int param_2,int param_3,uint *param_4)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  int *piVar8;
  
  if (((param_3 == *(int *)this) || (param_2 != 0)) || (*param_4 < *(uint *)(param_3 + 0x10))) {
    pcVar5 = (char *)FUN_004abcf0(param_4);
    *(char **)(param_3 + 8) = pcVar5;
    iVar1 = *(int *)this;
    if (param_3 == iVar1) {
      *(char **)(iVar1 + 4) = pcVar5;
      *(char **)(*(int *)this + 0xc) = pcVar5;
    }
    else if (param_3 == *(int *)(iVar1 + 8)) {
      *(char **)(iVar1 + 8) = pcVar5;
    }
  }
  else {
    pcVar5 = (char *)FUN_004abcf0(param_4);
    *(char **)(param_3 + 0xc) = pcVar5;
    if (param_3 == *(int *)(*(int *)this + 0xc)) {
      *(char **)(*(int *)this + 0xc) = pcVar5;
    }
  }
  *(int *)(pcVar5 + 4) = param_3;
  pcVar5[8] = '\0';
  pcVar5[9] = '\0';
  pcVar5[10] = '\0';
  pcVar5[0xb] = '\0';
  pcVar5[0xc] = '\0';
  pcVar5[0xd] = '\0';
  pcVar5[0xe] = '\0';
  pcVar5[0xf] = '\0';
  iVar1 = *(int *)this;
  *pcVar5 = '\0';
  piVar8 = (int *)(iVar1 + 4);
  pcVar7 = pcVar5;
  if (pcVar5 != (char *)*piVar8) {
    do {
      pcVar2 = *(char **)(pcVar7 + 4);
      if (*pcVar2 != '\0') break;
      pcVar6 = *(char **)(*(int *)(pcVar2 + 4) + 8);
      if (pcVar2 == pcVar6) {
        pcVar6 = *(char **)(*(int *)(pcVar2 + 4) + 0xc);
        if ((pcVar6 == (char *)0x0) || (*pcVar6 != '\0')) {
          if (pcVar7 == *(char **)(pcVar2 + 0xc)) {
            iVar1 = *(int *)(pcVar2 + 0xc);
            *(undefined4 *)(pcVar2 + 0xc) = *(undefined4 *)(iVar1 + 8);
            if (*(int *)(iVar1 + 8) != 0) {
              *(char **)(*(int *)(iVar1 + 8) + 4) = pcVar2;
            }
            *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(pcVar2 + 4);
            if (pcVar2 == (char *)*piVar8) {
              *piVar8 = iVar1;
            }
            else {
              iVar3 = *(int *)(pcVar2 + 4);
              if (pcVar2 == *(char **)(iVar3 + 8)) {
                *(int *)(iVar3 + 8) = iVar1;
              }
              else {
                *(int *)(iVar3 + 0xc) = iVar1;
              }
            }
            *(char **)(iVar1 + 8) = pcVar2;
            *(int *)(pcVar2 + 4) = iVar1;
            pcVar7 = pcVar2;
          }
          **(undefined1 **)(pcVar7 + 4) = 1;
          **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
          iVar1 = *(int *)(*(int *)(pcVar7 + 4) + 4);
          iVar3 = *(int *)(iVar1 + 8);
          *(undefined4 *)(iVar1 + 8) = *(undefined4 *)(iVar3 + 0xc);
          if (*(int *)(iVar3 + 0xc) != 0) {
            *(int *)(*(int *)(iVar3 + 0xc) + 4) = iVar1;
          }
          *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar1 + 4);
          if (iVar1 == *piVar8) {
            *piVar8 = iVar3;
            *(int *)(iVar3 + 0xc) = iVar1;
            *(int *)(iVar1 + 4) = iVar3;
          }
          else {
            iVar4 = *(int *)(iVar1 + 4);
            if (iVar1 == *(int *)(iVar4 + 0xc)) {
              *(int *)(iVar4 + 0xc) = iVar3;
              *(int *)(iVar3 + 0xc) = iVar1;
              *(int *)(iVar1 + 4) = iVar3;
            }
            else {
              *(int *)(iVar4 + 8) = iVar3;
              *(int *)(iVar3 + 0xc) = iVar1;
              *(int *)(iVar1 + 4) = iVar3;
            }
          }
        }
        else {
LAB_004ab126:
          *pcVar2 = '\x01';
          *pcVar6 = '\x01';
          **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
          pcVar7 = *(char **)(*(int *)(pcVar7 + 4) + 4);
        }
      }
      else {
        if ((pcVar6 != (char *)0x0) && (*pcVar6 == '\0')) goto LAB_004ab126;
        if (pcVar7 == *(char **)(pcVar2 + 8)) {
          FUN_004aab40((int)pcVar2,piVar8);
          pcVar7 = pcVar2;
        }
        **(undefined1 **)(pcVar7 + 4) = 1;
        **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
        FUN_004aaaf0(*(int *)(*(int *)(pcVar7 + 4) + 4),piVar8);
      }
    } while (pcVar7 != (char *)*piVar8);
  }
  *(undefined1 *)*piVar8 = 1;
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  *param_1 = pcVar5;
  return;
}


/* 004ab240 size=371 */

int __thiscall FUN_004ab240(void *this,int *param_1,uint *param_2)

{
  uint *puVar1;
  uint *puVar2;
  char *pcVar3;
  uint *puVar4;
  uint *puVar5;
  bool bVar6;
  
  puVar2 = param_2;
  puVar1 = *(uint **)this;
  bVar6 = true;
  puVar5 = puVar1;
  if ((uint *)puVar1[1] != (uint *)0x0) {
    puVar4 = (uint *)puVar1[1];
    do {
      puVar5 = puVar4;
      bVar6 = *param_2 < puVar5[4];
      if (bVar6) {
        puVar4 = (uint *)puVar5[2];
      }
      else {
        puVar4 = (uint *)puVar5[3];
      }
    } while (puVar4 != (uint *)0x0);
  }
  puVar4 = puVar5;
  if (bVar6) {
    if (puVar5 == (uint *)puVar1[2]) {
      if ((puVar5 == puVar1) || (*param_2 < puVar5[4])) {
        param_2 = puVar5;
        pcVar3 = (char *)FUN_004abcf0(puVar2);
        puVar5[2] = (uint)pcVar3;
        puVar1 = *(uint **)this;
        if (puVar5 == puVar1) {
          puVar1[1] = (uint)pcVar3;
          *(char **)(*(int *)this + 0xc) = pcVar3;
        }
        else if (puVar5 == (uint *)puVar1[2]) {
          puVar1[2] = (uint)pcVar3;
        }
      }
      else {
        param_2 = puVar5;
        pcVar3 = (char *)FUN_004abcf0(puVar2);
        puVar5[3] = (uint)pcVar3;
        if (puVar5 == *(uint **)(*(int *)this + 0xc)) {
          *(char **)(*(int *)this + 0xc) = pcVar3;
        }
      }
      *(uint **)(pcVar3 + 4) = puVar5;
      pcVar3[8] = '\0';
      pcVar3[9] = '\0';
      pcVar3[10] = '\0';
      pcVar3[0xb] = '\0';
      pcVar3[0xc] = '\0';
      pcVar3[0xd] = '\0';
      pcVar3[0xe] = '\0';
      pcVar3[0xf] = '\0';
      FUN_004abea0(pcVar3,(int *)(*(int *)this + 4));
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
      *param_1 = (int)pcVar3;
      *(undefined1 *)(param_1 + 1) = 1;
      return;
    }
    param_2 = puVar5;
    FUN_004ab8e0((int *)&param_2);
    puVar4 = param_2;
  }
  param_2 = puVar4;
  if (*puVar2 <= param_2[4]) {
    *param_1 = (int)param_2;
    *(undefined1 *)(param_1 + 1) = 0;
    return;
  }
  if ((puVar5 == *(uint **)this) || (*puVar2 < puVar5[4])) {
    pcVar3 = (char *)FUN_004abcf0(puVar2);
    puVar5[2] = (uint)pcVar3;
    puVar1 = *(uint **)this;
    if (puVar5 == puVar1) {
      puVar1[1] = (uint)pcVar3;
      *(char **)(*(int *)this + 0xc) = pcVar3;
    }
    else if (puVar5 == (uint *)puVar1[2]) {
      puVar1[2] = (uint)pcVar3;
    }
  }
  else {
    pcVar3 = (char *)FUN_004abcf0(puVar2);
    puVar5[3] = (uint)pcVar3;
    if (puVar5 == *(uint **)(*(int *)this + 0xc)) {
      *(char **)(*(int *)this + 0xc) = pcVar3;
    }
  }
  *(uint **)(pcVar3 + 4) = puVar5;
  pcVar3[8] = '\0';
  pcVar3[9] = '\0';
  pcVar3[10] = '\0';
  pcVar3[0xb] = '\0';
  pcVar3[0xc] = '\0';
  pcVar3[0xd] = '\0';
  pcVar3[0xe] = '\0';
  pcVar3[0xf] = '\0';
  FUN_004abea0(pcVar3,(int *)(*(int *)this + 4));
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  *param_1 = (int)pcVar3;
  *(undefined1 *)(param_1 + 1) = 1;
  return;
}


/* 004ab3c0 size=442 */

int __thiscall FUN_004ab3c0(void *this,undefined4 *param_1,int param_2,int param_3,uint *param_4)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  int *piVar8;
  
  if (((param_3 == *(int *)this) || (param_2 != 0)) || (*param_4 < *(uint *)(param_3 + 0x10))) {
    pcVar5 = (char *)FUN_004abdd0(param_4);
    *(char **)(param_3 + 8) = pcVar5;
    iVar1 = *(int *)this;
    if (param_3 == iVar1) {
      *(char **)(iVar1 + 4) = pcVar5;
      *(char **)(*(int *)this + 0xc) = pcVar5;
    }
    else if (param_3 == *(int *)(iVar1 + 8)) {
      *(char **)(iVar1 + 8) = pcVar5;
    }
  }
  else {
    pcVar5 = (char *)FUN_004abdd0(param_4);
    *(char **)(param_3 + 0xc) = pcVar5;
    if (param_3 == *(int *)(*(int *)this + 0xc)) {
      *(char **)(*(int *)this + 0xc) = pcVar5;
    }
  }
  *(int *)(pcVar5 + 4) = param_3;
  pcVar5[8] = '\0';
  pcVar5[9] = '\0';
  pcVar5[10] = '\0';
  pcVar5[0xb] = '\0';
  pcVar5[0xc] = '\0';
  pcVar5[0xd] = '\0';
  pcVar5[0xe] = '\0';
  pcVar5[0xf] = '\0';
  iVar1 = *(int *)this;
  *pcVar5 = '\0';
  piVar8 = (int *)(iVar1 + 4);
  pcVar7 = pcVar5;
  if (pcVar5 != (char *)*piVar8) {
    do {
      pcVar2 = *(char **)(pcVar7 + 4);
      if (*pcVar2 != '\0') break;
      pcVar6 = *(char **)(*(int *)(pcVar2 + 4) + 8);
      if (pcVar2 == pcVar6) {
        pcVar6 = *(char **)(*(int *)(pcVar2 + 4) + 0xc);
        if ((pcVar6 == (char *)0x0) || (*pcVar6 != '\0')) {
          if (pcVar7 == *(char **)(pcVar2 + 0xc)) {
            iVar1 = *(int *)(pcVar2 + 0xc);
            *(undefined4 *)(pcVar2 + 0xc) = *(undefined4 *)(iVar1 + 8);
            if (*(int *)(iVar1 + 8) != 0) {
              *(char **)(*(int *)(iVar1 + 8) + 4) = pcVar2;
            }
            *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(pcVar2 + 4);
            if (pcVar2 == (char *)*piVar8) {
              *piVar8 = iVar1;
            }
            else {
              iVar3 = *(int *)(pcVar2 + 4);
              if (pcVar2 == *(char **)(iVar3 + 8)) {
                *(int *)(iVar3 + 8) = iVar1;
              }
              else {
                *(int *)(iVar3 + 0xc) = iVar1;
              }
            }
            *(char **)(iVar1 + 8) = pcVar2;
            *(int *)(pcVar2 + 4) = iVar1;
            pcVar7 = pcVar2;
          }
          **(undefined1 **)(pcVar7 + 4) = 1;
          **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
          iVar1 = *(int *)(*(int *)(pcVar7 + 4) + 4);
          iVar3 = *(int *)(iVar1 + 8);
          *(undefined4 *)(iVar1 + 8) = *(undefined4 *)(iVar3 + 0xc);
          if (*(int *)(iVar3 + 0xc) != 0) {
            *(int *)(*(int *)(iVar3 + 0xc) + 4) = iVar1;
          }
          *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar1 + 4);
          if (iVar1 == *piVar8) {
            *piVar8 = iVar3;
            *(int *)(iVar3 + 0xc) = iVar1;
            *(int *)(iVar1 + 4) = iVar3;
          }
          else {
            iVar4 = *(int *)(iVar1 + 4);
            if (iVar1 == *(int *)(iVar4 + 0xc)) {
              *(int *)(iVar4 + 0xc) = iVar3;
              *(int *)(iVar3 + 0xc) = iVar1;
              *(int *)(iVar1 + 4) = iVar3;
            }
            else {
              *(int *)(iVar4 + 8) = iVar3;
              *(int *)(iVar3 + 0xc) = iVar1;
              *(int *)(iVar1 + 4) = iVar3;
            }
          }
        }
        else {
LAB_004ab466:
          *pcVar2 = '\x01';
          *pcVar6 = '\x01';
          **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
          pcVar7 = *(char **)(*(int *)(pcVar7 + 4) + 4);
        }
      }
      else {
        if ((pcVar6 != (char *)0x0) && (*pcVar6 == '\0')) goto LAB_004ab466;
        if (pcVar7 == *(char **)(pcVar2 + 8)) {
          FUN_004aab40((int)pcVar2,piVar8);
          pcVar7 = pcVar2;
        }
        **(undefined1 **)(pcVar7 + 4) = 1;
        **(undefined1 **)(*(int *)(pcVar7 + 4) + 4) = 0;
        FUN_004aaaf0(*(int *)(*(int *)(pcVar7 + 4) + 4),piVar8);
      }
    } while (pcVar7 != (char *)*piVar8);
  }
  *(undefined1 *)*piVar8 = 1;
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  *param_1 = pcVar5;
  return;
}


/* 004ab580 size=371 */

int __thiscall FUN_004ab580(void *this,int *param_1,uint *param_2)

{
  uint *puVar1;
  uint *puVar2;
  char *pcVar3;
  uint *puVar4;
  uint *puVar5;
  bool bVar6;
  
  puVar2 = param_2;
  puVar1 = *(uint **)this;
  bVar6 = true;
  puVar5 = puVar1;
  if ((uint *)puVar1[1] != (uint *)0x0) {
    puVar4 = (uint *)puVar1[1];
    do {
      puVar5 = puVar4;
      bVar6 = *param_2 < puVar5[4];
      if (bVar6) {
        puVar4 = (uint *)puVar5[2];
      }
      else {
        puVar4 = (uint *)puVar5[3];
      }
    } while (puVar4 != (uint *)0x0);
  }
  puVar4 = puVar5;
  if (bVar6) {
    if (puVar5 == (uint *)puVar1[2]) {
      if ((puVar5 == puVar1) || (*param_2 < puVar5[4])) {
        param_2 = puVar5;
        pcVar3 = (char *)FUN_004abdd0(puVar2);
        puVar5[2] = (uint)pcVar3;
        puVar1 = *(uint **)this;
        if (puVar5 == puVar1) {
          puVar1[1] = (uint)pcVar3;
          *(char **)(*(int *)this + 0xc) = pcVar3;
        }
        else if (puVar5 == (uint *)puVar1[2]) {
          puVar1[2] = (uint)pcVar3;
        }
      }
      else {
        param_2 = puVar5;
        pcVar3 = (char *)FUN_004abdd0(puVar2);
        puVar5[3] = (uint)pcVar3;
        if (puVar5 == *(uint **)(*(int *)this + 0xc)) {
          *(char **)(*(int *)this + 0xc) = pcVar3;
        }
      }
      *(uint **)(pcVar3 + 4) = puVar5;
      pcVar3[8] = '\0';
      pcVar3[9] = '\0';
      pcVar3[10] = '\0';
      pcVar3[0xb] = '\0';
      pcVar3[0xc] = '\0';
      pcVar3[0xd] = '\0';
      pcVar3[0xe] = '\0';
      pcVar3[0xf] = '\0';
      FUN_004abea0(pcVar3,(int *)(*(int *)this + 4));
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
      *param_1 = (int)pcVar3;
      *(undefined1 *)(param_1 + 1) = 1;
      return;
    }
    param_2 = puVar5;
    FUN_004ab8e0((int *)&param_2);
    puVar4 = param_2;
  }
  param_2 = puVar4;
  if (*puVar2 <= param_2[4]) {
    *param_1 = (int)param_2;
    *(undefined1 *)(param_1 + 1) = 0;
    return;
  }
  if ((puVar5 == *(uint **)this) || (*puVar2 < puVar5[4])) {
    pcVar3 = (char *)FUN_004abdd0(puVar2);
    puVar5[2] = (uint)pcVar3;
    puVar1 = *(uint **)this;
    if (puVar5 == puVar1) {
      puVar1[1] = (uint)pcVar3;
      *(char **)(*(int *)this + 0xc) = pcVar3;
    }
    else if (puVar5 == (uint *)puVar1[2]) {
      puVar1[2] = (uint)pcVar3;
    }
  }
  else {
    pcVar3 = (char *)FUN_004abdd0(puVar2);
    puVar5[3] = (uint)pcVar3;
    if (puVar5 == *(uint **)(*(int *)this + 0xc)) {
      *(char **)(*(int *)this + 0xc) = pcVar3;
    }
  }
  *(uint **)(pcVar3 + 4) = puVar5;
  pcVar3[8] = '\0';
  pcVar3[9] = '\0';
  pcVar3[10] = '\0';
  pcVar3[0xb] = '\0';
  pcVar3[0xc] = '\0';
  pcVar3[0xd] = '\0';
  pcVar3[0xe] = '\0';
  pcVar3[0xf] = '\0';
  FUN_004abea0(pcVar3,(int *)(*(int *)this + 4));
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  *param_1 = (int)pcVar3;
  *(undefined1 *)(param_1 + 1) = 1;
  return;
}


/* 004ab700 size=103 */

undefined4 * __thiscall FUN_004ab700(void *this,undefined1 *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)this;
  do {
    if (param_1 == param_2) {
LAB_004ab728:
      puVar2 = *(undefined4 **)((int)this + 4);
      if (puVar3 == puVar2) {
        return this;
      }
      FUN_004bab10(puVar3,puVar2,1);
      *(int *)((int)this + 4) = (int)puVar3 + (*(int *)((int)this + 4) - (int)puVar2);
      return this;
    }
    if (puVar3 == *(undefined4 **)((int)this + 4)) {
      if (param_1 != param_2) {
        FUN_004ac460(this,param_1,param_2);
        return this;
      }
      goto LAB_004ab728;
    }
    uVar1 = *param_1;
    param_1 = param_1 + 1;
    *(undefined1 *)puVar3 = uVar1;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  } while( true );
}


/* 004ab770 size=92 */

void __thiscall FUN_004ab770(void *this,undefined1 *param_1,int param_2)

{
  uint uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  
  iVar5 = param_2 - (int)param_1;
  uVar1 = iVar5 + 1;
  if (uVar1 == 0) {
    FUN_004a5b30(s_basic_string_004de5c8);
  }
  else {
    iVar3 = FUN_004aa520(uVar1);
    *(int *)this = iVar3;
    *(int *)((int)this + 4) = iVar3;
    *(uint *)((int)this + 8) = iVar3 + uVar1;
  }
  puVar4 = *(undefined1 **)this;
  if (0 < iVar5) {
    do {
      uVar2 = *param_1;
      param_1 = param_1 + 1;
      *puVar4 = uVar2;
      puVar4 = puVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  *(undefined1 **)((int)this + 4) = puVar4;
  *puVar4 = 0;
  return;
}


/* 004ab7d0 size=23 */

void __thiscall FUN_004ab7d0(void *this,undefined4 *param_1,undefined4 *param_2)

{
  FUN_004ac050(this,param_1,param_2);
  return;
}


/* 004ab7f0 size=103 */

undefined4 * __thiscall FUN_004ab7f0(void *this,undefined4 *param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)this;
  do {
    if (param_1 == param_2) {
LAB_004ab818:
      puVar2 = *(undefined4 **)((int)this + 4);
      if (puVar3 == puVar2) {
        return this;
      }
      FUN_004bab10(puVar3,puVar2,1);
      *(int *)((int)this + 4) = (int)puVar3 + (*(int *)((int)this + 4) - (int)puVar2);
      return this;
    }
    if (puVar3 == *(undefined4 **)((int)this + 4)) {
      if (param_1 != param_2) {
        FUN_004ac050(this,param_1,param_2);
        return this;
      }
      goto LAB_004ab818;
    }
    uVar1 = *(undefined1 *)param_1;
    param_1 = (undefined4 *)((int)param_1 + 1);
    *(undefined1 *)puVar3 = uVar1;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  } while( true );
}


/* 004ab860 size=120 */

undefined4 * __thiscall FUN_004ab860(void *this,undefined2 *param_1,undefined2 *param_2)

{
  undefined2 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)this;
  do {
    if (param_1 == param_2) {
LAB_004ab88e:
      puVar2 = *(undefined4 **)((int)this + 4);
      if (puVar3 == puVar2) {
        return this;
      }
      FUN_004bab10(puVar3,puVar2,2);
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + ((int)puVar2 - (int)puVar3 >> 1) * -2;
      return this;
    }
    if (puVar3 == *(undefined4 **)((int)this + 4)) {
      if (param_1 != param_2) {
        FUN_004ac720(this,param_1,param_2);
        return this;
      }
      goto LAB_004ab88e;
    }
    uVar1 = *param_1;
    param_1 = param_1 + 1;
    *(undefined2 *)puVar3 = uVar1;
    puVar3 = (undefined4 *)((int)puVar3 + 2);
  } while( true );
}


/* 004ab8e0 size=76 */

void __cdecl FUN_004ab8e0(int *param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  pcVar1 = (char *)*param_1;
  if ((*pcVar1 == '\0') && (*(char **)(*(int *)(pcVar1 + 4) + 4) == pcVar1)) {
    *param_1 = *(int *)(pcVar1 + 0xc);
    return;
  }
  iVar3 = *(int *)(pcVar1 + 8);
  if (iVar3 != 0) {
    for (iVar2 = *(int *)(iVar3 + 0xc); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0xc)) {
      iVar3 = iVar2;
    }
    *param_1 = iVar3;
    return;
  }
  iVar3 = *(int *)(pcVar1 + 4);
  iVar2 = iVar3;
  if (pcVar1 == *(char **)(iVar3 + 8)) {
    do {
      iVar3 = *(int *)(iVar2 + 4);
      bVar4 = iVar2 == *(int *)(iVar3 + 8);
      iVar2 = iVar3;
    } while (bVar4);
  }
  *param_1 = iVar3;
  return;
}


/* 004ab930 size=350 */

int __cdecl FUN_004ab930(int param_1)

{
  size_t sVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  uint local_4;
  
  uVar5 = param_1 + 7U & 0xfffffff8;
  uVar2 = DAT_004ec68c - (int)DAT_004ec690;
  local_4 = 0x14;
  puVar3 = DAT_004ec690;
  if (uVar2 < uVar5 * 0x14) {
    if (uVar2 < uVar5) {
      sVar1 = ((DAT_004ec688 >> 4) + 7 & 0xfffffff8) + uVar5 * 0x28;
      if (uVar2 != 0) {
        *DAT_004ec690 = *(undefined4 *)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4);
        *(undefined4 **)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4) = DAT_004ec690;
      }
      DAT_004ec690 = (undefined4 *)FUN_00430de0(sVar1);
      uVar2 = uVar5;
      if (DAT_004ec690 == (undefined4 *)0x0) {
        for (; uVar2 < 0x81; uVar2 = uVar2 + 8) {
          puVar3 = *(undefined4 **)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4);
          if (puVar3 != (undefined4 *)0x0) {
            *(undefined4 *)(&DAT_004ec644 + (uVar2 - 1 >> 3) * 4) = *puVar3;
            DAT_004ec68c = (int)puVar3 + uVar2;
            DAT_004ec690 = puVar3;
            goto LAB_004aba2c;
          }
        }
        DAT_004ec68c = 0;
        DAT_004ec690 = (undefined4 *)FUN_00430de0(sVar1);
      }
      DAT_004ec688 = DAT_004ec688 + sVar1;
      DAT_004ec68c = (int)DAT_004ec690 + sVar1;
LAB_004aba2c:
      puVar3 = FUN_004ac1c0(uVar5,&local_4);
    }
    else {
      local_4 = uVar2 / uVar5;
      DAT_004ec690 = (undefined4 *)((int)DAT_004ec690 + local_4 * uVar5);
    }
    if (local_4 == 1) {
      return;
    }
  }
  else {
    DAT_004ec690 = DAT_004ec690 + uVar5 * 5;
  }
  puVar3 = (undefined4 *)((int)puVar3 + uVar5);
  *(undefined4 **)(&DAT_004ec644 + (uVar5 - 1 >> 3) * 4) = puVar3;
  iVar6 = 1;
  puVar4 = puVar3;
  if (local_4 != 2) {
    do {
      puVar3 = (undefined4 *)((int)puVar4 + uVar5);
      *puVar4 = puVar3;
      iVar6 = iVar6 + 1;
      puVar4 = puVar3;
    } while (local_4 - 1 != iVar6);
  }
  *puVar3 = 0;
  return;
}


/* 004aba90 size=30 */

undefined4 * __thiscall FUN_004aba90(void *this,byte param_1)

{
  FUN_004a85f0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004abab0 size=30 */

undefined * __thiscall FUN_004abab0(void *this,byte param_1)

{
  FUN_004a86e0((int)this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004abad0 size=197 */

int FUN_004abad0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  uint local_14 [2];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9c68;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004a94b0(&DAT_004ed050);
  local_4 = 0;
  if (DAT_004ec64c == (undefined4 *)0x0) {
    local_14[0] = 0x14;
    puVar2 = FUN_004ac1c0(0x18,local_14);
    if (local_14[0] != 1) {
      puVar4 = puVar2 + 6;
      iVar5 = 1;
      puVar1 = puVar2 + 0xc;
      puVar3 = puVar4;
      DAT_004ec64c = puVar4;
      if (local_14[0] != 2) {
        do {
          puVar4 = puVar1;
          *puVar3 = puVar4;
          iVar5 = iVar5 + 1;
          puVar1 = puVar4 + 6;
          puVar3 = puVar4;
        } while (local_14[0] - 1 != iVar5);
      }
      *puVar4 = 0;
    }
  }
  else {
    puVar2 = DAT_004ec64c;
    DAT_004ec64c = (undefined4 *)*DAT_004ec64c;
  }
  DAT_004ed050 = 0;
  if (puVar2 + 4 != (undefined4 *)0x0) {
    puVar2[4] = *param_1;
    *(undefined2 *)(puVar2 + 5) = *(undefined2 *)(param_1 + 1);
  }
  ExceptionList = local_c;
  return;
}


/* 004abba0 size=14 */

int __thiscall FUN_004abba0(void *this,undefined4 *param_1)

{
  *param_1 = *(undefined4 *)(*(int *)this + 8);
  return;
}


/* 004abbb0 size=256 */

undefined4 * FUN_004abbb0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined1 auStackY_b4 [128];
  undefined4 *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004c9ca9;
  local_10 = ExceptionList;
  local_14 = auStackY_b4 + 0x88;
  ExceptionList = &local_10;
  FUN_004a94b0(&DAT_004ed050);
  local_8 = 0;
  local_18 = DAT_004ec654;
  if (DAT_004ec654 == (undefined4 *)0x0) {
    local_18 = (undefined4 *)0x14;
    puVar2 = FUN_004ac1c0(0x28,(uint *)&local_18);
    if (local_18 != (undefined4 *)0x1) {
      puVar4 = puVar2 + 10;
      iVar5 = 1;
      puVar1 = puVar2 + 0x14;
      puVar3 = puVar4;
      DAT_004ec654 = puVar4;
      if (local_18 != (undefined4 *)0x2) {
        do {
          puVar4 = puVar1;
          *puVar3 = puVar4;
          iVar5 = iVar5 + 1;
          puVar1 = puVar4 + 10;
          puVar3 = puVar4;
        } while ((int)local_18 + -1 != iVar5);
      }
      *puVar4 = 0;
    }
    local_18 = puVar2;
  }
  else {
    DAT_004ec654 = (undefined4 *)*DAT_004ec654;
  }
  puVar1 = local_18;
  puVar4 = param_1;
  DAT_004ed050 = 0;
  puVar2 = local_18 + 4;
  local_8 = 2;
  if (puVar2 != (undefined4 *)0x0) {
    FUN_004a8710((int)&param_1 + 3);
    FUN_004a8730(puVar2);
    (*(uint8_t*)((char*)&local_8+0)) = 3;
    FUN_004aa400(puVar2,(undefined2 *)*puVar4,puVar4[1]);
    local_8 = CONCAT31((*(uint32_t*)((char*)&local_8+1)),4);
    FUN_004a8140(puVar1 + 7,puVar4 + 3);
  }
  ExceptionList = local_10;
  return puVar1;
}


/* 004abcf0 size=219 */

undefined4 * FUN_004abcf0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  uint local_14 [2];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9cc8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004a94b0(&DAT_004ed050);
  local_4 = 0;
  if (DAT_004ec64c == (undefined4 *)0x0) {
    local_14[0] = 0x14;
    puVar2 = FUN_004ac1c0(0x18,local_14);
    if (local_14[0] != 1) {
      puVar4 = puVar2 + 6;
      iVar5 = 1;
      puVar1 = puVar2 + 0xc;
      puVar3 = puVar4;
      DAT_004ec64c = puVar4;
      if (local_14[0] != 2) {
        do {
          puVar4 = puVar1;
          *puVar3 = puVar4;
          iVar5 = iVar5 + 1;
          puVar1 = puVar4 + 6;
          puVar3 = puVar4;
        } while (local_14[0] - 1 != iVar5);
      }
      *puVar4 = 0;
    }
  }
  else {
    puVar2 = DAT_004ec64c;
    DAT_004ec64c = (undefined4 *)*DAT_004ec64c;
  }
  DAT_004ed050 = 0;
  if (puVar2 + 4 != (undefined4 *)0x0) {
    puVar2[4] = *param_1;
    iVar5 = param_1[1];
    if (iVar5 == 0) {
      iVar5 = 0;
    }
    else {
      InterlockedIncrement((LONG *)(iVar5 + 4));
    }
    puVar2[5] = iVar5;
  }
  ExceptionList = local_c;
  return puVar2;
}


/* 004abdd0 size=195 */

int FUN_004abdd0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  uint local_14 [2];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9ce8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004a94b0(&DAT_004ed050);
  local_4 = 0;
  if (DAT_004ec64c == (undefined4 *)0x0) {
    local_14[0] = 0x14;
    puVar2 = FUN_004ac1c0(0x18,local_14);
    if (local_14[0] != 1) {
      puVar4 = puVar2 + 6;
      iVar5 = 1;
      puVar1 = puVar2 + 0xc;
      puVar3 = puVar4;
      DAT_004ec64c = puVar4;
      if (local_14[0] != 2) {
        do {
          puVar4 = puVar1;
          *puVar3 = puVar4;
          iVar5 = iVar5 + 1;
          puVar1 = puVar4 + 6;
          puVar3 = puVar4;
        } while (local_14[0] - 1 != iVar5);
      }
      *puVar4 = 0;
    }
  }
  else {
    puVar2 = DAT_004ec64c;
    DAT_004ec64c = (undefined4 *)*DAT_004ec64c;
  }
  DAT_004ed050 = 0;
  if (puVar2 + 4 != (undefined4 *)0x0) {
    puVar2[4] = *param_1;
    puVar2[5] = param_1[1];
  }
  ExceptionList = local_c;
  return;
}


/* 004abea0 size=430 */

void __cdecl FUN_004abea0(char *param_1,int *param_2)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  
  *param_1 = '\0';
  if (param_1 == (char *)*param_2) {
    *(undefined1 *)*param_2 = 1;
    return;
  }
  do {
    pcVar1 = *(char **)(param_1 + 4);
    if (*pcVar1 != '\0') {
      *(undefined1 *)*param_2 = 1;
      return;
    }
    pcVar4 = *(char **)(*(int *)(pcVar1 + 4) + 8);
    if (pcVar1 == pcVar4) {
      pcVar4 = *(char **)(*(int *)(pcVar1 + 4) + 0xc);
      if ((pcVar4 != (char *)0x0) && (*pcVar4 == '\0')) goto LAB_004abedb;
      if (param_1 == *(char **)(pcVar1 + 0xc)) {
        iVar3 = *(int *)(pcVar1 + 0xc);
        *(undefined4 *)(pcVar1 + 0xc) = *(undefined4 *)(iVar3 + 8);
        if (*(int *)(iVar3 + 8) != 0) {
          *(char **)(*(int *)(iVar3 + 8) + 4) = pcVar1;
        }
        *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(pcVar1 + 4);
        if (pcVar1 == (char *)*param_2) {
          *param_2 = iVar3;
        }
        else {
          iVar5 = *(int *)(pcVar1 + 4);
          if (pcVar1 == *(char **)(iVar5 + 8)) {
            *(int *)(iVar5 + 8) = iVar3;
          }
          else {
            *(int *)(iVar5 + 0xc) = iVar3;
          }
        }
        *(char **)(iVar3 + 8) = pcVar1;
        *(int *)(pcVar1 + 4) = iVar3;
        param_1 = pcVar1;
      }
      **(undefined1 **)(param_1 + 4) = 1;
      **(undefined1 **)(*(int *)(param_1 + 4) + 4) = 0;
      iVar3 = *(int *)(*(int *)(param_1 + 4) + 4);
      iVar5 = *(int *)(iVar3 + 8);
      *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(iVar5 + 0xc);
      if (*(int *)(iVar5 + 0xc) != 0) {
        *(int *)(*(int *)(iVar5 + 0xc) + 4) = iVar3;
      }
      *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(iVar3 + 4);
      if (iVar3 == *param_2) {
        *param_2 = iVar5;
        *(int *)(iVar5 + 0xc) = iVar3;
      }
      else {
        iVar2 = *(int *)(iVar3 + 4);
        if (iVar3 == *(int *)(iVar2 + 0xc)) {
          *(int *)(iVar2 + 0xc) = iVar5;
          *(int *)(iVar5 + 0xc) = iVar3;
        }
        else {
          *(int *)(iVar2 + 8) = iVar5;
          *(int *)(iVar5 + 0xc) = iVar3;
        }
      }
LAB_004ac029:
      *(int *)(iVar3 + 4) = iVar5;
    }
    else {
      if ((pcVar4 == (char *)0x0) || (*pcVar4 != '\0')) {
        if (param_1 == *(char **)(pcVar1 + 8)) {
          iVar3 = *(int *)(pcVar1 + 8);
          *(undefined4 *)(pcVar1 + 8) = *(undefined4 *)(iVar3 + 0xc);
          if (*(int *)(iVar3 + 0xc) != 0) {
            *(char **)(*(int *)(iVar3 + 0xc) + 4) = pcVar1;
          }
          *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(pcVar1 + 4);
          if (pcVar1 == (char *)*param_2) {
            *param_2 = iVar3;
          }
          else {
            iVar5 = *(int *)(pcVar1 + 4);
            if (pcVar1 == *(char **)(iVar5 + 0xc)) {
              *(int *)(iVar5 + 0xc) = iVar3;
            }
            else {
              *(int *)(iVar5 + 8) = iVar3;
            }
          }
          *(char **)(iVar3 + 0xc) = pcVar1;
          *(int *)(pcVar1 + 4) = iVar3;
          param_1 = pcVar1;
        }
        **(undefined1 **)(param_1 + 4) = 1;
        **(undefined1 **)(*(int *)(param_1 + 4) + 4) = 0;
        iVar3 = *(int *)(*(int *)(param_1 + 4) + 4);
        iVar5 = *(int *)(iVar3 + 0xc);
        *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(iVar5 + 8);
        if (*(int *)(iVar5 + 8) != 0) {
          *(int *)(*(int *)(iVar5 + 8) + 4) = iVar3;
        }
        *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(iVar3 + 4);
        if (iVar3 == *param_2) {
          *param_2 = iVar5;
        }
        else {
          iVar2 = *(int *)(iVar3 + 4);
          if (iVar3 == *(int *)(iVar2 + 8)) {
            *(int *)(iVar2 + 8) = iVar5;
          }
          else {
            *(int *)(iVar2 + 0xc) = iVar5;
          }
        }
        *(int *)(iVar5 + 8) = iVar3;
        goto LAB_004ac029;
      }
LAB_004abedb:
      *pcVar1 = '\x01';
      *pcVar4 = '\x01';
      **(undefined1 **)(*(int *)(param_1 + 4) + 4) = 0;
      param_1 = *(char **)(*(int *)(param_1 + 4) + 4);
    }
    if (param_1 == (char *)*param_2) {
      *(char *)*param_2 = '\x01';
      return;
    }
  } while( true );
}


