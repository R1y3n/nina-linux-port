/* lithtech.exe decompilation - unnamed_004b4000 */
#include "ghidra_types.h"

/* 004b4ed0 size=16 */

undefined4 FUN_004b4ed0(void)

{
  FUN_004b9cf5(&LAB_004b4ee0);
  return 0;
}


/* 004b4f00 size=37 */

void __thiscall FUN_004b4f00(void *this,int *param_1)

{
  *param_1 = *(int *)this;
  param_1[1] = 0;
  if (*(int *)this == 0) {
    *(int **)((int)this + 4) = param_1;
    *(int **)this = param_1;
    return;
  }
  *(int **)(*(int *)this + 4) = param_1;
  *(int **)this = param_1;
  return;
}


/* 004b4f30 size=39 */

void __thiscall FUN_004b4f30(void *this,undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = *(undefined4 *)((int)this + 4);
  if (*(undefined4 **)((int)this + 4) == (undefined4 *)0x0) {
    *(undefined4 **)this = param_1;
    *(undefined4 **)((int)this + 4) = param_1;
    return;
  }
  **(undefined4 **)((int)this + 4) = param_1;
  *(undefined4 **)((int)this + 4) = param_1;
  return;
}


/* 004b4f60 size=47 */

void __thiscall FUN_004b4f60(void *this,int *param_1)

{
  if ((int *)param_1[1] == (int *)0x0) {
    *(int *)this = *param_1;
  }
  else {
    *(int *)param_1[1] = *param_1;
  }
  if (*param_1 == 0) {
    *(int *)((int)this + 4) = param_1[1];
    return;
  }
  *(int *)(*param_1 + 4) = param_1[1];
  return;
}


/* 004b4f90 size=26 */

void __fastcall FUN_004b4f90(undefined4 *param_1)

{
  param_1[7] = &PTR_LAB_004ceeb0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[4] = 0;
  *param_1 = 0;
  param_1[0xc] = param_1;
  return;
}


/* 004b4fb0 size=141 */

void __thiscall
FUN_004b4fb0(void *this,undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  
  *(undefined4 *)((int)this + 0x34) = param_11;
  *(undefined4 *)((int)this + 0x10) = param_1;
  if (param_2 == (char *)0x0) {
    *(undefined4 *)this = 0;
  }
  else {
    uVar3 = 0xffffffff;
    pcVar2 = param_2;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    pcVar2 = (char *)FUN_00430de0(~uVar3);
    *(char **)this = pcVar2;
    if (pcVar2 != (char *)0x0) {
      uVar3 = 0xffffffff;
      do {
        pcVar5 = param_2;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar5 = param_2 + 1;
        cVar1 = *param_2;
        param_2 = pcVar5;
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
  }
  *(undefined4 *)((int)this + 4) = param_4;
  *(undefined4 *)((int)this + 0xc) = param_6;
  *(undefined4 *)((int)this + 0x14) = param_7;
  *(undefined4 *)((int)this + 8) = param_8;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(void **)((int)this + 0x30) = this;
  return;
}


/* 004b5040 size=87 */

void __fastcall FUN_004b5040(undefined4 *param_1)

{
  undefined *puVar1;
  
  if ((undefined *)*param_1 != (undefined *)0x0) {
    FUN_00430df0((undefined *)*param_1);
  }
  if (param_1[4] == 0) {
    puVar1 = (undefined *)param_1[0xe];
  }
  else {
    if (*(int *)(param_1[4] + 0x48) != 0) goto LAB_004b507a;
    puVar1 = (undefined *)param_1[0xe];
  }
  if (puVar1 != (undefined *)0x0) {
    FUN_00430df0(puVar1);
  }
LAB_004b507a:
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[0xe] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[0xc] = 0;
  return;
}


/* 004b50a0 size=6 */

undefined4 __fastcall FUN_004b50a0(int param_1)

{
  return **(undefined4 **)(param_1 + 4);
}


/* 004b50b0 size=15 */

undefined4 __thiscall FUN_004b50b0(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 0x18) = param_1;
  return 1;
}


/* 004b50c0 size=211 */

uint __thiscall FUN_004b50c0(void *this,undefined4 *param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if (param_3 != -1) {
    FUN_004b50b0(this,param_3);
  }
  uVar3 = *(uint *)((int)this + 0x18);
  uVar2 = *(uint *)((int)this + 0xc);
  if (uVar3 <= uVar2) {
    if (uVar2 < uVar3 + param_2) {
      param_2 = uVar2 - uVar3;
    }
    if (param_2 != 0) {
      iVar1 = *(int *)(*(int *)((int)this + 0x10) + 0x48);
      if (iVar1 != 0) {
        puVar4 = (undefined4 *)
                 ((*(int *)((int)this + 0x14) - *(int *)(*(int *)((int)this + 0x10) + 0xc)) + iVar1
                 + uVar3);
        for (uVar2 = param_2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *param_1 = *puVar4;
          puVar4 = puVar4 + 1;
          param_1 = param_1 + 1;
        }
        for (uVar3 = param_2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined1 *)param_1 = *(undefined1 *)puVar4;
          puVar4 = (undefined4 *)((int)puVar4 + 1);
          param_1 = (undefined4 *)((int)param_1 + 1);
        }
        *(uint *)((int)this + 0x18) = *(int *)((int)this + 0x18) + param_2;
        return param_2;
      }
      if (*(int *)((int)this + 0x38) != 0) {
        puVar4 = (undefined4 *)(*(int *)((int)this + 0x38) + uVar3);
        for (uVar2 = param_2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *param_1 = *puVar4;
          puVar4 = puVar4 + 1;
          param_1 = param_1 + 1;
        }
        for (uVar3 = param_2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined1 *)param_1 = *(undefined1 *)puVar4;
          puVar4 = (undefined4 *)((int)puVar4 + 1);
          param_1 = (undefined4 *)((int)param_1 + 1);
        }
        *(uint *)((int)this + 0x18) = *(int *)((int)this + 0x18) + param_2;
        return param_2;
      }
      uVar3 = (**(code **)(**(int **)((int)this + 0x34) + 8))
                        (*(undefined4 *)((int)this + 0x14),uVar3,param_2,param_1);
      if (uVar3 == param_2) {
        *(uint *)((int)this + 0x18) = *(int *)((int)this + 0x18) + param_2;
        return param_2;
      }
    }
  }
  return 0;
}


/* 004b51a0 size=113 */

undefined4 * __thiscall
FUN_004b51a0(void *this,undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004cabdb;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined ***)((int)this + 4) = &PTR_LAB_004ceeb4;
  *(undefined4 *)((int)this + 0x18) = 0;
  FUN_004c8b40((void *)((int)this + 0x1c),param_3);
  local_4 = 0;
  FUN_004c8b40((void *)((int)this + 0x24),param_4);
  *(undefined4 *)this = param_1;
  *(void **)((int)this + 0x18) = this;
  *(undefined4 *)((int)this + 0x2c) = param_2;
  ExceptionList = local_c;
  return this;
}


/* 004b5220 size=108 */

undefined4 * __thiscall FUN_004b5220(void *this,undefined4 param_1,undefined4 param_2,int param_3)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004cabfb;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined ***)((int)this + 4) = &PTR_LAB_004ceeb4;
  *(undefined4 *)((int)this + 0x18) = 0;
  FUN_004c8b30((undefined4 *)((int)this + 0x1c));
  local_4 = 0;
  FUN_004c8b40((void *)((int)this + 0x24),param_3);
  *(undefined4 *)this = param_1;
  *(void **)((int)this + 0x18) = this;
  *(undefined4 *)((int)this + 0x2c) = param_2;
  ExceptionList = local_c;
  return this;
}


/* 004b5290 size=215 */

void __fastcall FUN_004b5290(undefined4 *param_1)

{
  uint *this;
  int iVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  puStack_8 = &LAB_004cac26;
  local_c = ExceptionList;
  local_4 = 1;
  ExceptionList = &local_c;
  if (*(int *)(*(int *)(param_1[0xb] + 0x18) + 0x6c) != 0) {
    ExceptionList = &local_c;
    iVar1 = FUN_004c8c70(param_1 + 7);
    while (iVar1 != 0) {
      iVar2 = FUN_004c8ae0(iVar1);
      FUN_004c8c40(param_1 + 7,iVar1);
      iVar1 = iVar2;
    }
  }
  this = param_1 + 9;
  iVar1 = FUN_004c8c70(this);
  while (iVar1 != 0) {
    iVar2 = FUN_004c8ae0(iVar1);
    FUN_004c8c40(this,iVar1);
    FUN_004b5040(*(undefined4 **)(iVar1 + 0x14));
    FUN_004b7060(*(void **)(param_1[0xb] + 0x18),*(int *)(iVar1 + 0x14));
    iVar1 = iVar2;
  }
  *param_1 = 0;
  param_1[6] = 0;
  local_4 = local_4 & 0xffffff00;
  FUN_004c8bd0((int)this);
  local_4 = 0xffffffff;
  FUN_004c8bd0((int)(param_1 + 7));
  ExceptionList = local_c;
  return;
}


/* 004b5370 size=212 */

undefined4 * __thiscall
FUN_004b5370(void *this,undefined4 param_1,undefined4 param_2,char *param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,int param_7,int param_8)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004cac46;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined ***)((int)this + 0x20) = &PTR_LAB_004ceeb8;
  *(undefined4 *)((int)this + 0x34) = 0;
  FUN_004c8b40((void *)((int)this + 0x38),param_7);
  local_4 = 0;
  FUN_004c8b40((void *)((int)this + 0x40),param_8);
  uVar3 = 0xffffffff;
  pcVar2 = param_3;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
  pcVar2 = (char *)FUN_00430de0(~uVar3);
  *(char **)this = pcVar2;
  if (pcVar2 != (char *)0x0) {
    uVar3 = 0xffffffff;
    do {
      pcVar5 = param_3;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar5 = param_3 + 1;
      cVar1 = *param_3;
      param_3 = pcVar5;
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
  *(undefined4 *)((int)this + 0x14) = param_6;
  *(undefined4 *)((int)this + 8) = param_5;
  *(undefined4 *)((int)this + 0x18) = param_1;
  *(undefined4 *)((int)this + 4) = param_4;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x48) = 0;
  *(undefined4 *)((int)this + 0x1c) = param_2;
  *(void **)((int)this + 0x34) = this;
  ExceptionList = local_c;
  return this;
}


/* 004b5460 size=289 */

void __fastcall FUN_004b5460(undefined4 *param_1)

{
  uint *this;
  uint *this_00;
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  void *local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  puStack_8 = &LAB_004cac66;
  local_c = ExceptionList;
  this = param_1 + 0x10;
  local_4 = 1;
  ExceptionList = &local_c;
  iVar2 = FUN_004c8c70(this);
  while (iVar2 != 0) {
    iVar3 = FUN_004c8ae0(iVar2);
    FUN_004c8c40(this,iVar2);
    puVar1 = *(undefined4 **)(iVar2 + 0x14);
    iVar2 = iVar3;
    if (puVar1 != (undefined4 *)0x0) {
      FUN_004b5290(puVar1);
      FUN_00430df0((undefined *)puVar1);
    }
  }
  this_00 = param_1 + 0xe;
  iVar2 = FUN_004c8c70(this_00);
  while (iVar2 != 0) {
    iVar3 = FUN_004c8ae0(iVar2);
    FUN_004c8c40(this_00,iVar2);
    puVar1 = *(undefined4 **)(iVar2 + 0x14);
    iVar2 = iVar3;
    if (puVar1 != (undefined4 *)0x0) {
      FUN_004b5460(puVar1);
      FUN_00430df0((undefined *)puVar1);
    }
  }
  if ((undefined *)*param_1 != (undefined *)0x0) {
    FUN_00430df0((undefined *)*param_1);
  }
  if ((undefined *)param_1[0x12] != (undefined *)0x0) {
    FUN_00430df0((undefined *)param_1[0x12]);
  }
  *param_1 = 0;
  param_1[5] = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[0x12] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[0xd] = 0;
  local_4 = local_4 & 0xffffff00;
  FUN_004c8bd0((int)this);
  local_4 = 0xffffffff;
  FUN_004c8bd0((int)this_00);
  ExceptionList = local_c;
  return;
}


/* 004b5590 size=55 */

int __thiscall FUN_004b5590(void *this,byte *param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = FUN_004b70c0((void *)((int)this + 0x40),param_2);
  if (iVar1 == 0) {
    return;
  }
  FUN_004b7140((void *)(iVar1 + 0x24),param_1,
               (uint)(*(int *)(*(int *)((int)this + 0x18) + 0x68) == 0));
  return;
}


/* 004b55d0 size=218 */

int __thiscall FUN_004b55d0(void *this,byte *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  byte *pbVar6;
  byte *pbVar7;
  uint *puVar8;
  uint local_418 [2];
  byte local_410 [4];
  byte local_40c [260];
  byte local_308 [256];
  undefined1 local_208;
  byte local_104 [260];
  
  FUN_004bd1d1(param_1,local_410,local_104,local_308,local_40c);
  uVar2 = 0xffffffff;
  pbVar6 = local_40c;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    bVar1 = *pbVar6;
    pbVar6 = pbVar6 + 1;
  } while (bVar1 != 0);
  if (~uVar2 - 1 < 6) {
    iVar3 = -1;
    pbVar6 = local_40c;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar1 = *pbVar6;
      pbVar6 = pbVar6 + 1;
    } while (bVar1 != 0);
    if (iVar3 == -2) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffffff;
      pbVar6 = local_40c + 1;
      do {
        pbVar7 = pbVar6;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pbVar7 = pbVar6 + 1;
        bVar1 = *pbVar6;
        pbVar6 = pbVar7;
      } while (bVar1 != 0);
      uVar2 = ~uVar2;
      puVar5 = (uint *)(pbVar7 + -uVar2);
      puVar8 = local_418;
      for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar8 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(byte *)puVar8 = (byte)*puVar5;
        puVar5 = (uint *)((int)puVar5 + 1);
        puVar8 = (uint *)((int)puVar8 + 1);
      }
      FUN_004c8d30(local_418);
      uVar2 = FUN_004b6a40((char *)local_418);
    }
  }
  else {
    _strncat((char *)local_308,(char *)local_40c,0x201);
    uVar2 = 0;
    local_208 = 0;
  }
  FUN_004b5590(this,local_308,uVar2);
  return;
}


/* 004b56b0 size=42 */

undefined4 __thiscall FUN_004b56b0(void *this,byte *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (byte *)0x0) {
    return 0;
  }
  uVar1 = FUN_004b7140((void *)((int)this + 0x38),param_1,
                       (uint)(*(int *)(*(int *)((int)this + 0x18) + 0x68) == 0));
  return uVar1;
}


/* 004b56e0 size=17 */

undefined4 __fastcall FUN_004b56e0(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004c8c70((uint *)(param_1 + 0x38));
  if (iVar1 == 0) {
    return 0;
  }
  return *(undefined4 *)(iVar1 + 0x14);
}


/* 004b5700 size=25 */

undefined4 FUN_004b5700(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004c8ae0(param_1 + 0x20);
  if (iVar1 == 0) {
    return 0;
  }
  return *(undefined4 *)(iVar1 + 0x14);
}


/* 004b5720 size=17 */

undefined4 __fastcall FUN_004b5720(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004c8c70((uint *)(param_1 + 0x40));
  if (iVar1 == 0) {
    return 0;
  }
  return *(undefined4 *)(iVar1 + 0x14);
}


/* 004b5740 size=25 */

undefined4 FUN_004b5740(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004c8ae0(param_1 + 4);
  if (iVar1 == 0) {
    return 0;
  }
  return *(undefined4 *)(iVar1 + 0x14);
}


/* 004b5760 size=25 */

undefined4 FUN_004b5760(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004c8c70((uint *)(param_1 + 0x24));
  if (iVar1 == 0) {
    return 0;
  }
  return *(undefined4 *)(iVar1 + 0x14);
}


/* 004b5780 size=25 */

undefined4 FUN_004b5780(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004c8ae0(param_1 + 0x1c);
  if (iVar1 == 0) {
    return 0;
  }
  return *(undefined4 *)(iVar1 + 0x14);
}


/* 004b57a0 size=206 */

undefined4 * __thiscall FUN_004b57a0(void *this,byte *param_1)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  void *this_00;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004cac7b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar2 = FUN_004b7140((void *)((int)this + 0x38),param_1,
                       (uint)(*(int *)(*(int *)((int)this + 0x18) + 0x68) == 0));
  if (iVar2 == 0) {
    this_00 = (void *)FUN_00430de0(0x4c);
    local_4 = 0;
    if (this_00 == (void *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      iVar2 = *(int *)(*(int *)((int)this + 0x18) + 0x7c);
      iVar6 = *(int *)(*(int *)((int)this + 0x18) + 0x78);
      uVar4 = FUN_004b6b10();
      puVar3 = FUN_004b5370(this_00,*(undefined4 *)((int)this + 0x18),this,(char *)param_1,0,0,uVar4
                            ,iVar6,iVar2);
    }
    local_4 = 0xffffffff;
    if (puVar3 == (undefined4 *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      FUN_004c8c00((void *)((int)this + 0x38),puVar3 + 8);
      uVar5 = 0xffffffff;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        bVar1 = *param_1;
        param_1 = param_1 + 1;
      } while (bVar1 != 0);
      if (*(uint *)(*(int *)((int)this + 0x18) + 0x58) <= ~uVar5 - 1) {
        *(uint *)(*(int *)((int)this + 0x18) + 0x58) = ~uVar5;
      }
    }
  }
  else {
    puVar3 = (undefined4 *)0x0;
  }
  ExceptionList = local_c;
  return puVar3;
}


/* 004b5870 size=117 */

void * __thiscall
FUN_004b5870(void *this,undefined4 param_1,char *param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  void *this_00;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  this_00 = (void *)FUN_004b6f50(*(int *)((int)this + 0x18));
  if (this_00 == (void *)0x0) {
    return (void *)0x0;
  }
  uVar5 = 0;
  uVar4 = 0;
  uVar2 = FUN_004b6b10();
  FUN_004b4fb0(this_00,this,param_2,param_1,param_3,0,0,0,uVar2,uVar4,uVar5,param_4);
  FUN_004c8c00((void *)(param_3 + 0x24),(undefined4 *)((int)this_00 + 0x1c));
  uVar3 = 0xffffffff;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *param_2;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  if (*(uint *)(*(int *)((int)this + 0x18) + 0x5c) <= ~uVar3 - 1) {
    *(uint *)(*(int *)((int)this + 0x18) + 0x5c) = ~uVar3;
  }
  return this_00;
}


/* 004b58f0 size=71 */

undefined4 __thiscall FUN_004b58f0(void *this,int param_1,undefined4 *param_2)

{
  *(int *)((int)this + 0x10) = *(int *)((int)this + 0x10) - param_2[3];
  FUN_004c8c40((void *)(param_1 + 0x24),(int)(param_2 + 7));
  FUN_004b5040(param_2);
  FUN_004b7060(*(void **)((int)this + 0x18),(int)param_2);
  *(undefined4 *)(*(int *)((int)this + 0x18) + 8) = 0;
  return 1;
}


/* 004b5940 size=178 */

undefined4 __thiscall
FUN_004b5940(void *this,int *param_1,undefined4 param_2,int *param_3,int param_4)

{
  void *this_00;
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_4;
  
  local_4 = 1;
  uVar3 = 1;
  if (param_3 != (int *)0x0) {
    for (iVar1 = FUN_004c8c70((uint *)((int)this + 0x38)); iVar1 != 0; iVar1 = FUN_004c8ae0(iVar1))
    {
      *(undefined4 *)(*(int *)(iVar1 + 0x14) + 4) = 0;
    }
    iVar1 = FUN_004b5a00(this,param_1,param_2,param_3,param_4);
    if (iVar1 == 0) {
      local_4 = 0;
    }
    else {
      iVar1 = FUN_004c8c70((uint *)((int)this + 0x38));
      if (iVar1 != 0) {
        do {
          this_00 = *(void **)(iVar1 + 0x14);
          if ((*(int *)((int)this_00 + 4) != 0) &&
             (iVar2 = FUN_004b5940(this_00,param_1,*(int *)((int)this_00 + 4),
                                   *(int **)((int)this_00 + 8),param_4), iVar2 == 0)) {
            local_4 = 0;
          }
          iVar1 = FUN_004c8ae0(iVar1);
        } while (iVar1 != 0);
        return local_4;
      }
    }
    uVar3 = local_4;
  }
  return uVar3;
}


/* 004b5a00 size=759 */

undefined4 __thiscall
FUN_004b5a00(void *this,int *param_1,undefined4 param_2,int *param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  int *piVar9;
  undefined4 uVar10;
  int *piVar11;
  int iVar12;
  void *pvVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  int *piVar16;
  uint uVar17;
  int iVar18;
  byte *pbVar19;
  int *piVar20;
  byte *pbVar21;
  char *pcVar22;
  char *pcStack_34;
  uint local_2c;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_004cac9b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0xc) = 0xffffffff;
  local_2c = 0;
  piVar9 = (int *)FUN_00430de0((size_t)param_3);
  if (piVar9 == (int *)0x0) {
    uVar10 = 0;
  }
  else {
    piVar11 = (int *)(**(code **)(*param_1 + 8))(param_2,0,param_3,piVar9);
    if (piVar11 == param_3) {
      piVar11 = (int *)((int)piVar9 + (int)param_3);
      piVar20 = piVar9;
      while (piVar20 < piVar11) {
        if (*piVar20 == 1) {
          iVar3 = piVar20[1];
          iVar4 = piVar20[2];
          iVar5 = piVar20[3];
          pbVar19 = (byte *)(piVar20 + 4);
          uVar17 = 0xffffffff;
          pbVar21 = pbVar19;
          do {
            if (uVar17 == 0) break;
            uVar17 = uVar17 - 1;
            bVar1 = *pbVar21;
            pbVar21 = pbVar21 + 1;
          } while (bVar1 != 0);
          piVar20 = (int *)((int)piVar20 + ~uVar17 + 0x10);
          iVar12 = FUN_004b7140((void *)((int)this + 0x38),pbVar19,
                                (uint)(*(int *)(*(int *)((int)this + 0x18) + 0x68) == 0));
          if (iVar12 == 0) {
            pvVar13 = (void *)FUN_00430de0(0x4c);
            uStack_4 = 0;
            if (pvVar13 == (void *)0x0) {
              puVar14 = (undefined4 *)0x0;
            }
            else {
              iVar12 = *(int *)((int)this + 0x18);
              puVar14 = FUN_004b5370(pvVar13,iVar12,this,(char *)pbVar19,iVar3,iVar4,iVar5,
                                     *(int *)(iVar12 + 0x78),*(int *)(iVar12 + 0x7c));
            }
            uStack_4 = 0xffffffff;
            FUN_004c8c00((void *)((int)this + 0x38),puVar14 + 8);
          }
          else {
            *(int *)(iVar12 + 4) = iVar3;
            *(int *)(iVar12 + 8) = iVar4;
            *(int *)(iVar12 + 0x14) = iVar5;
          }
        }
        else {
          iVar3 = piVar20[1];
          iVar4 = piVar20[2];
          iVar5 = piVar20[3];
          iVar12 = piVar20[4];
          iVar6 = piVar20[6];
          pbVar19 = (byte *)(piVar20 + 7);
          uVar17 = 0xffffffff;
          pbVar21 = pbVar19;
          do {
            if (uVar17 == 0) break;
            uVar17 = uVar17 - 1;
            bVar1 = *pbVar21;
            pbVar21 = pbVar21 + 1;
          } while (bVar1 != 0);
          pcStack_34 = (char *)((int)piVar20 + ~uVar17 + 0x1c);
          puVar14 = FUN_004b5d00(this,piVar20[5]);
          bVar8 = false;
          puVar15 = (undefined4 *)FUN_004b7140(puVar14 + 9,pbVar19,1);
          if (puVar15 != (undefined4 *)0x0) {
            if (param_4 == 0) {
              bVar8 = true;
            }
            else {
              FUN_004b58f0(this,(int)puVar14,puVar15);
            }
          }
          uVar17 = 0xffffffff;
          pcVar22 = pcStack_34;
          do {
            if (uVar17 == 0) break;
            uVar17 = uVar17 - 1;
            cVar2 = *pcVar22;
            pcVar22 = pcVar22 + 1;
          } while (cVar2 != '\0');
          piVar20 = (int *)(pcStack_34 + ~uVar17);
          if (*pcStack_34 == '\0') {
            pcStack_34 = (char *)0x0;
          }
          if (iVar6 == 0) {
            param_3 = (int *)0x0;
          }
          else {
            param_3 = (int *)FUN_00430de0(iVar6 * 4);
            if (iVar6 != 0) {
              piVar16 = param_3;
              iVar18 = iVar6;
              do {
                iVar7 = *piVar20;
                piVar20 = piVar20 + 1;
                *piVar16 = iVar7;
                piVar16 = piVar16 + 1;
                iVar18 = iVar18 + -1;
              } while (iVar18 != 0);
            }
          }
          if (!bVar8) {
            pvVar13 = (void *)FUN_004b6f50(*(int *)((int)this + 0x18));
            FUN_004b4fb0(pvVar13,this,(char *)pbVar19,iVar12,puVar14,pcStack_34,iVar4,iVar3,iVar5,
                         iVar6,param_3,param_1);
            FUN_004c8c00(puVar14 + 9,(undefined4 *)((int)pvVar13 + 0x1c));
            *(int *)((int)this + 0x10) = *(int *)((int)this + 0x10) + *(int *)((int)pvVar13 + 0xc);
            if (*(uint *)((int)pvVar13 + 0x14) < *(uint *)((int)this + 0xc)) {
              *(uint *)((int)this + 0xc) = *(uint *)((int)pvVar13 + 0x14);
            }
            if (local_2c < *(uint *)((int)pvVar13 + 0x14)) {
              local_2c = *(uint *)((int)pvVar13 + 0x14);
            }
          }
          if (param_3 != (int *)0x0) {
            FUN_00430df0((undefined *)param_3);
          }
        }
      }
      FUN_00430df0((undefined *)piVar9);
      uVar10 = 1;
    }
    else {
      FUN_00430df0((undefined *)piVar9);
      uVar10 = 0;
    }
  }
  ExceptionList = local_c;
  return uVar10;
}


/* 004b5d00 size=194 */

undefined4 * __thiscall FUN_004b5d00(void *this,uint param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 *local_4;
  
  local_4 = (undefined4 *)0xffffffff;
  puStack_8 = &LAB_004cacc6;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  puVar1 = (undefined4 *)FUN_004b70c0((void *)((int)this + 0x40),param_1);
  if (puVar1 != (undefined4 *)0x0) {
    ExceptionList = local_c;
    return puVar1;
  }
  if (*(int *)(*(int *)((int)this + 0x18) + 0x6c) == 0) {
    pvVar2 = (void *)FUN_00430de0(0x30);
    local_4 = (undefined4 *)0x1;
    if (pvVar2 != (void *)0x0) {
      puVar1 = FUN_004b5220(pvVar2,param_1,this,*(int *)(*(int *)((int)this + 0x18) + 0x70));
      goto LAB_004b5d92;
    }
  }
  else {
    pvVar2 = (void *)FUN_00430de0(0x30);
    if (pvVar2 != (void *)0x0) {
      local_4 = puVar1;
      puVar1 = FUN_004b51a0(pvVar2,param_1,this,*(int *)(*(int *)((int)this + 0x18) + 0x74),
                            *(int *)(*(int *)((int)this + 0x18) + 0x70));
      goto LAB_004b5d92;
    }
  }
  puVar1 = (undefined4 *)0x0;
LAB_004b5d92:
  local_4 = (undefined4 *)0xffffffff;
  if (puVar1 == (undefined4 *)0x0) {
    ExceptionList = local_c;
    return (undefined4 *)0x0;
  }
  FUN_004c8c00((void *)((int)this + 0x40),puVar1 + 1);
  ExceptionList = local_c;
  return puVar1;
}


/* 004b5dd0 size=226 */

undefined4 * __fastcall FUN_004b5dd0(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004cacdb;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[4] = &PTR_FUN_004ceec8;
  local_4 = 0;
  FUN_004c8b40(param_1 + 0x20,1);
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  param_1[0x1c] = 0x13;
  param_1[0x1d] = 0x13;
  *param_1 = &PTR_ClientUtilities_4486e0_004ceebc;
  param_1[3] = 0;
  param_1[9] = 1;
  param_1[10] = 2000000000;
  param_1[8] = 0;
  param_1[7] = 0;
  param_1[0xc] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 1;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[2] = 1;
  param_1[0x19] = 0;
  param_1[0xb] = 3;
  param_1[1] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[0x1e] = 5;
  param_1[0x1f] = 9;
  param_1[0x24] = 100;
  *(undefined1 *)(param_1 + 0x25) = 0;
  ExceptionList = local_c;
  return param_1;
}


/* 004b5ec0 size=319 */

void __fastcall FUN_004b5ec0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  void *pvStack_c;
  undefined1 *puStack_8;
  uint local_4;
  
  puStack_8 = &LAB_004cad17;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  *param_1 = &PTR_ClientUtilities_4486e0_004ceebc;
  local_4 = 2;
  if (param_1[3] != 0) {
    FUN_004b6980((int)param_1);
  }
  piVar2 = (int *)param_1[5];
  if (piVar2 != (int *)0x0) {
    do {
      FUN_004c8cf0(param_1 + 4,(int)piVar2);
      param_1[7] = param_1[7] + -1;
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 4))(1);
      }
      piVar2 = (int *)param_1[5];
    } while (piVar2 != (int *)0x0);
  }
  puVar1 = (undefined4 *)param_1[0x11];
  if (puVar1 != (undefined4 *)0x0) {
    FUN_004b5460(puVar1);
    FUN_00430df0((undefined *)puVar1);
    param_1[0x11] = 0;
  }
  if ((undefined *)param_1[0x19] != (undefined *)0x0) {
    FUN_00430df0((undefined *)param_1[0x19]);
    param_1[0x19] = 0;
  }
  if ((undefined *)param_1[1] != (undefined *)0x0) {
    FUN_00430df0((undefined *)param_1[1]);
    param_1[1] = 0;
  }
  piVar2 = (int *)param_1[0x22];
  param_1[3] = 0;
  param_1[8] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 1;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 1;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[2] = 1;
  param_1[0x19] = 0;
  while (piVar2 != (int *)0x0) {
    FUN_00430df0((undefined *)piVar2[2]);
    FUN_004b4f60(param_1 + 0x22,piVar2);
    FUN_00430df0((undefined *)piVar2);
    piVar2 = (int *)param_1[0x22];
  }
  local_4 = local_4 & 0xffffff00;
  FUN_004c8bd0((int)(param_1 + 0x20));
  param_1[4] = &PTR_LAB_004ceecc;
  ExceptionList = pvStack_c;
  return;
}


/* 004b6000 size=1018 */

undefined4 __thiscall FUN_004b6000(void *this,byte *param_1,int param_2,int param_3)

{
  byte bVar1;
  bool bVar2;
  byte *pbVar3;
  undefined3 extraout_var;
  undefined4 uVar4;
  void *pvVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  char *pcVar9;
  uint uVar10;
  uint uVar11;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  byte *pbVar12;
  uint unaff_EDI;
  byte *pbVar13;
  undefined4 *puVar14;
  int iVar15;
  void *pvVar16;
  byte in_stack_ffffff48;
  undefined1 auStack_b5 [60];
  char cStack_79;
  undefined4 auStack_78 [15];
  char cStack_3a;
  undefined4 uStack_39;
  undefined4 uStack_35;
  undefined4 uStack_31;
  undefined4 uStack_2d;
  undefined4 uStack_29;
  undefined4 uStack_25;
  undefined4 uStack_21;
  undefined4 uStack_1d;
  undefined4 uStack_19;
  undefined4 uStack_15;
  uint uStack_11;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004cad76;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(int *)((int)this + 0x40) = param_2;
  uVar4 = 0;
  if (param_2 != 0) {
    if (*(undefined **)((int)this + 100) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)((int)this + 100));
    }
    uVar10 = 0xffffffff;
    pbVar3 = param_1;
    do {
      if (uVar10 == 0) break;
      uVar10 = uVar10 - 1;
      bVar1 = *pbVar3;
      pbVar3 = pbVar3 + 1;
    } while (bVar1 != 0);
    pbVar3 = (byte *)FUN_00430de0(~uVar10);
    uVar10 = 0xffffffff;
    *(byte **)((int)this + 100) = pbVar3;
    pbVar12 = param_1;
    do {
      pbVar13 = pbVar12;
      if (uVar10 == 0) break;
      uVar10 = uVar10 - 1;
      pbVar13 = pbVar12 + 1;
      bVar1 = *pbVar12;
      pbVar12 = pbVar13;
    } while (bVar1 != 0);
    uVar10 = ~uVar10;
    pbVar12 = pbVar13 + -uVar10;
    for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
      *(undefined4 *)pbVar3 = *(undefined4 *)pbVar12;
      pbVar12 = pbVar12 + 4;
      pbVar3 = pbVar3 + 4;
    }
    for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
      *pbVar3 = *pbVar12;
      pbVar12 = pbVar12 + 1;
      pbVar3 = pbVar3 + 1;
    }
    bVar2 = FUN_004b6f10(param_1);
    if (CONCAT31(extraout_var,bVar2) == 0) {
      pvVar5 = (void *)FUN_00430de0(0x24);
      local_4 = 2;
      if (pvVar5 == (void *)0x0) {
        piVar6 = (int *)0x0;
      }
      else {
        piVar6 = FUN_004b7250(pvVar5,this);
      }
      local_4 = 0xffffffff;
      if (piVar6 == (int *)0x0) {
        FUN_00430df0(*(undefined **)((int)this + 100));
        *(undefined4 *)((int)this + 100) = 0;
        uVar4 = 0;
      }
      else {
        *(int **)((int)this + 0x20) = piVar6;
        FUN_004c8cc0((void *)((int)this + 0x10),(int)piVar6);
        *(int *)((int)this + 0x1c) = *(int *)((int)this + 0x1c) + 1;
        iVar7 = (**(code **)(*piVar6 + 0x10))(param_1,param_2,param_3);
        uVar4 = 0;
        if (iVar7 != 0) {
          *(undefined4 *)((int)this + 0xc) = 1;
          if (param_3 == 0) {
            (**(code **)(*piVar6 + 8))(0,0,0xa8,auStack_b5 + -3);
            *(undefined4 *)((int)this + 0x3c) = uStack_29;
            *(undefined4 *)((int)this + 0x30) = uStack_35;
            *(undefined4 *)((int)this + 0x38) = uStack_2d;
            *(undefined4 *)((int)this + 0x48) = uStack_25;
            *(undefined4 *)((int)this + 0x54) = uStack_21;
            *(undefined4 *)((int)this + 0x34) = uStack_31;
            *(undefined4 *)((int)this + 0x60) = uStack_15;
            *(undefined4 *)((int)this + 0x58) = uStack_1d;
            *(undefined4 *)((int)this + 0x50) = uStack_39;
            puVar8 = auStack_78;
            puVar14 = (undefined4 *)((int)this + 0x94);
            for (iVar7 = 0xf; iVar7 != 0; iVar7 = iVar7 + -1) {
              *puVar14 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar14 = puVar14 + 1;
            }
            *(undefined4 *)((int)this + 0x5c) = uStack_19;
            *(uint *)((int)this + 8) = uStack_11 & 0xff;
            *(undefined1 *)((int)this + 0xd0) = 0;
            pcVar9 = (char *)((int)this + 0xcf);
            do {
              if (*pcVar9 != ' ') break;
              *pcVar9 = '\0';
              pcVar9 = pcVar9 + -1;
            } while (-1 < (int)(pcVar9 + (-0x94 - (int)this)));
            if (in_stack_ffffff48 != 0xd) {
              ExceptionList = local_c;
              return 0;
            }
            if (cStack_79 != '\n') {
              ExceptionList = local_c;
              return 0;
            }
            if (cStack_3a != '\x1a') {
              ExceptionList = local_c;
              return 0;
            }
            if (*(int *)((int)this + 0x50) != 1) {
              ExceptionList = local_c;
              return 0;
            }
            pvVar5 = (void *)FUN_00430de0(0x4c);
            local_4 = 4;
            if (pvVar5 == (void *)0x0) {
              puVar8 = (undefined4 *)0x0;
            }
            else {
              puVar8 = FUN_004b5370(pvVar5,this,0,&DAT_004e4424,*(undefined4 *)((int)this + 0x30),
                                    *(undefined4 *)((int)this + 0x34),
                                    *(undefined4 *)((int)this + 0x38),*(int *)((int)this + 0x78),
                                    *(int *)((int)this + 0x7c));
            }
            local_4 = 0xffffffff;
            *(undefined4 **)((int)this + 0x44) = puVar8;
            FUN_004b5940(puVar8,piVar6,*(undefined4 *)((int)this + 0x30),*(int **)((int)this + 0x34)
                         ,0);
          }
          else {
            *(undefined4 *)((int)this + 0x3c) = 0xa8;
            *(undefined4 *)((int)this + 0x4c) = 1;
            pvVar5 = (void *)FUN_00430de0(0x4c);
            local_4 = 3;
            if (pvVar5 == (void *)0x0) {
              *(undefined4 *)((int)this + 0x44) = 0;
            }
            else {
              iVar7 = *(int *)((int)this + 0x7c);
              iVar15 = *(int *)((int)this + 0x78);
              uVar4 = FUN_004b6b10();
              puVar8 = FUN_004b5370(pvVar5,this,0,&DAT_004e4424,0,0,uVar4,iVar15,iVar7);
              *(undefined4 **)((int)this + 0x44) = puVar8;
            }
          }
          uVar4 = 1;
        }
      }
    }
    else if (*(int *)((int)this + 0x40) == 0) {
      uVar4 = 0;
    }
    else {
      pvVar5 = (void *)FUN_00430de0(0x38);
      local_4 = 0;
      if (pvVar5 == (void *)0x0) {
        piVar6 = (int *)0x0;
      }
      else {
        piVar6 = FUN_004b7620(pvVar5,this,*(undefined4 *)((int)this + 0x2c));
      }
      local_4 = 0xffffffff;
      if (piVar6 == (int *)0x0) {
        FUN_00430df0(*(undefined **)((int)this + 100));
        *(undefined4 *)((int)this + 100) = 0;
        uVar4 = 0;
      }
      else {
        *(int **)((int)this + 0x20) = piVar6;
        FUN_004c8cc0((void *)((int)this + 0x10),(int)piVar6);
        *(int *)((int)this + 0x1c) = *(int *)((int)this + 0x1c) + 1;
        iVar7 = (**(code **)(*piVar6 + 0x10))(param_1,param_2,param_3);
        uVar4 = 0;
        if (iVar7 != 0) {
          *(undefined4 *)((int)this + 0xc) = 1;
          pvVar5 = (void *)FUN_00430de0(0x4c);
          local_4 = 1;
          if (pvVar5 == (void *)0x0) {
            puVar8 = (undefined4 *)0x0;
          }
          else {
            iVar7 = *(int *)((int)this + 0x7c);
            iVar15 = *(int *)((int)this + 0x78);
            pvVar16 = pvVar5;
            uVar4 = FUN_004b6b10();
            puVar8 = FUN_004b5370(pvVar5,this,0,&DAT_004e4424,0,0,uVar4,iVar15,iVar7);
            pvVar5 = pvVar16;
          }
          local_4 = 0xffffffff;
          *(undefined4 **)((int)this + 0x44) = puVar8;
          FUN_004b6400(piVar6,(byte)puVar8,(char)*(undefined4 *)((int)this + 100),0,unaff_EDI,
                       unaff_ESI,unaff_EBP,unaff_EBX,pvVar5,in_stack_ffffff48);
          uVar4 = 1;
        }
      }
    }
  }
  ExceptionList = local_c;
  return uVar4;
}


/* 004b6400 size=1400 */

/* FUN_004b6400: lifted from original x86 -> lt_lifted.c */


/* 004b6980 size=168 */

undefined4 __fastcall FUN_004b6980(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  uVar3 = (**(code **)(**(int **)(param_1 + 0x20) + 0x14))();
  FUN_004c8cf0((void *)(param_1 + 0x10),*(int *)(param_1 + 0x20));
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + -1;
  if (*(int **)(param_1 + 0x20) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x20) + 4))(1);
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  piVar1 = *(int **)(param_1 + 0x14);
  while (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x14))();
    FUN_004c8cf0((void *)(param_1 + 0x10),(int)piVar1);
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + -1;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 4))(1);
    }
    piVar1 = *(int **)(param_1 + 0x14);
  }
  puVar2 = *(undefined4 **)(param_1 + 0x44);
  if (puVar2 != (undefined4 *)0x0) {
    FUN_004b5460(puVar2);
    FUN_00430df0((undefined *)puVar2);
    *(undefined4 *)(param_1 + 0x44) = 0;
  }
  if (*(undefined **)(param_1 + 100) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)(param_1 + 100));
    *(undefined4 *)(param_1 + 100) = 0;
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  return uVar3;
}


/* 004b6a30 size=4 */

undefined4 __fastcall FUN_004b6a30(int param_1)

{
  return *(undefined4 *)(param_1 + 0x44);
}


/* 004b6a40 size=88 */

/* FUN_004b6a40: lifted from original x86 -> lt_lifted.c */


/* 004b6aa0 size=110 */

/* FUN_004b6aa0: lifted from original x86 -> lt_lifted.c */


/* 004b6b10 size=15 */

int FUN_004b6b10(void)

{
  int local_4;
  
  FUN_004bcb91(&local_4);
  return;
}


/* 004b6b20 size=87 */

void __thiscall FUN_004b6b20(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  
  if (*(undefined **)((int)this + 4) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)((int)this + 4));
  }
  uVar3 = 0xffffffff;
  pcVar2 = param_1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = (char *)FUN_00430de0(~uVar3);
  uVar3 = 0xffffffff;
  *(char **)((int)this + 4) = pcVar2;
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
  return;
}


/* 004b6b80 size=458 */

void * __thiscall FUN_004b6b80(void *this,char *param_1)

{
  char cVar1;
  uint *puVar2;
  void *pvVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  byte local_400 [1024];
  
  uVar4 = 0xffffffff;
  pcVar6 = param_1;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  iVar5 = ~uVar4 - 1;
  if (1 < iVar5) {
    cVar1 = *param_1;
    puVar2 = *(uint **)(*(int *)((int)this + 0x18) + 4);
    if (puVar2 == (uint *)0x0) {
      if ((((('\x1f' < cVar1) && (cVar1 < '/')) || (('/' < cVar1 && (cVar1 < ':')))) ||
          (('@' < cVar1 && (cVar1 < '[')))) || (('`' < cVar1 && (cVar1 < '{')))) goto LAB_004b6bdc;
    }
    else {
      puVar2 = FUN_004bb020(puVar2,cVar1);
      if (puVar2 == (uint *)0x0) goto LAB_004b6bdc;
    }
    param_1 = param_1 + 1;
    iVar5 = ~uVar4 - 2;
  }
LAB_004b6bdc:
  iVar7 = 0;
  pcVar6 = param_1;
  do {
    cVar1 = *pcVar6;
    puVar2 = *(uint **)(*(int *)((int)this + 0x18) + 4);
    if (puVar2 == (uint *)0x0) {
      if ((((cVar1 < ' ') || ('.' < cVar1)) && ((cVar1 < '0' || ('9' < cVar1)))) &&
         (((cVar1 < 'A' || ('Z' < cVar1)) && ((cVar1 < 'a' || ('z' < cVar1)))))) break;
    }
    else {
      puVar2 = FUN_004bb020(puVar2,cVar1);
      if (puVar2 != (uint *)0x0) break;
    }
    iVar7 = iVar7 + 1;
    pcVar6[(int)(local_400 + -(int)param_1)] = *pcVar6;
    pcVar6 = pcVar6 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar7 < 0x3ff);
  local_400[iVar7] = 0;
  if (((2 < iVar5) && (param_1[iVar7 + 1] == '.')) && (param_1[iVar7 + 2] == '.')) {
    return this;
  }
  pvVar3 = (void *)FUN_004b56b0(this,local_400);
  if (pvVar3 == (void *)0x0) {
    return (void *)0x0;
  }
  cVar1 = param_1[iVar7];
  if (cVar1 == '\0') {
    return pvVar3;
  }
  do {
    puVar2 = *(uint **)(*(int *)((int)this + 0x18) + 4);
    if (puVar2 == (uint *)0x0) {
      if (((('\x1f' < cVar1) && (cVar1 < '/')) || (('/' < cVar1 && (cVar1 < ':')))) ||
         ((('@' < cVar1 && (cVar1 < '[')) || (('`' < cVar1 && (cVar1 < '{')))))) goto LAB_004b6d33;
    }
    else {
      puVar2 = FUN_004bb020(puVar2,cVar1);
      if (puVar2 == (uint *)0x0) {
LAB_004b6d33:
        pvVar3 = FUN_004b6b80(pvVar3,param_1 + iVar7);
        return pvVar3;
      }
    }
    cVar1 = param_1[iVar7 + 1];
    iVar7 = iVar7 + 1;
    if (cVar1 == '\0') {
      return pvVar3;
    }
  } while( true );
}


/* 004b6d50 size=370 */

undefined4 __thiscall FUN_004b6d50(void *this,char *param_1)

{
  char cVar1;
  uint *puVar2;
  undefined4 uVar3;
  void *this_00;
  uint uVar4;
  size_t sVar5;
  size_t _Count;
  char *pcVar6;
  byte local_800 [1023];
  undefined1 local_401;
  char local_400 [1024];
  
  uVar4 = 0xffffffff;
  pcVar6 = param_1;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  sVar5 = ~uVar4 - 1;
  if (0x3fe < (int)sVar5) {
    return 0;
  }
  if (1 < (int)sVar5) {
    cVar1 = *param_1;
    puVar2 = *(uint **)(*(int *)((int)this + 0x18) + 4);
    if (puVar2 == (uint *)0x0) {
      if ((((('\x1f' < cVar1) && (cVar1 < '/')) || (('/' < cVar1 && (cVar1 < ':')))) ||
          (('@' < cVar1 && (cVar1 < '[')))) || (('`' < cVar1 && (cVar1 < '{')))) goto LAB_004b6db0;
    }
    else {
      puVar2 = FUN_004bb020(puVar2,cVar1);
      if (puVar2 == (uint *)0x0) goto LAB_004b6db0;
    }
    param_1 = param_1 + 1;
    sVar5 = ~uVar4 - 2;
  }
LAB_004b6db0:
  _Count = sVar5 - 1;
  do {
    cVar1 = param_1[_Count];
    puVar2 = *(uint **)(*(int *)((int)this + 0x18) + 4);
    if (puVar2 == (uint *)0x0) {
      if ((((cVar1 < ' ') || ('.' < cVar1)) && ((cVar1 < '0' || ('9' < cVar1)))) &&
         (((cVar1 < 'A' || ('Z' < cVar1)) && ((cVar1 < 'a' || ('z' < cVar1)))))) break;
    }
    else {
      puVar2 = FUN_004bb020(puVar2,cVar1);
      if (puVar2 != (uint *)0x0) break;
    }
    _Count = _Count - 1;
  } while (-1 < (int)_Count);
  if (_Count == sVar5) {
    return 0;
  }
  _strncpy((char *)local_800,param_1 + _Count + 1,0x3ff);
  local_401 = 0;
  if ((int)_Count < 2) {
    uVar3 = FUN_004b55d0(this,local_800);
    return uVar3;
  }
  _strncpy(local_400,param_1,_Count);
  local_400[_Count] = '\0';
  this_00 = FUN_004b6b80(this,local_400);
  if (this_00 == (void *)0x0) {
    return 0;
  }
  uVar3 = FUN_004b55d0(this_00,local_800);
  return uVar3;
}


/* 004b6ed0 size=20 */

int __thiscall FUN_004b6ed0(void *this,char *param_1)

{
  void *this_00;
  
  this_00 = (void *)FUN_004b6a30((int)this);
  FUN_004b6d50(this_00,param_1);
  return;
}


/* 004b6ef0 size=20 */

int __thiscall FUN_004b6ef0(void *this,char *param_1)

{
  void *this_00;
  
  this_00 = (void *)FUN_004b6a30((int)this);
  FUN_004b6b80(this_00,param_1);
  return;
}


/* 004b6f10 size=60 */

bool FUN_004b6f10(byte *param_1)

{
  int iVar1;
  int local_24;
  uint local_1e;
  
  iVar1 = FUN_004bd3d0(param_1,&local_24);
  if (iVar1 == 0) {
    return (local_1e & 0x4000) == 0x4000;
  }
  return false;
}


/* 004b6f50 size=259 */

int __fastcall FUN_004b6f50(int param_1)

{
  uint *this;
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  
  this = (uint *)(param_1 + 0x80);
  iVar1 = FUN_004c8c70(this);
  if ((iVar1 == 0) || (iVar1 = *(int *)(iVar1 + 0x14), iVar1 == 0)) {
    piVar2 = (int *)FUN_00430de0(0xc);
    if (piVar2 == (int *)0x0) {
      return 0;
    }
    iVar1 = *(int *)(param_1 + 0x90);
    puVar3 = (undefined4 *)FUN_00430de0(iVar1 * 0x3c);
    if (puVar3 == (undefined4 *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else if (-1 < iVar1 + -1) {
      puVar4 = puVar3;
      do {
        FUN_004b4f90(puVar4);
        puVar4 = puVar4 + 0xf;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    piVar2[2] = (int)puVar3;
    if (puVar3 == (undefined4 *)0x0) {
      FUN_00430df0((undefined *)piVar2);
      return 0;
    }
    uVar5 = 0;
    if (*(int *)(param_1 + 0x90) != 0) {
      iVar1 = 0;
      do {
        *(int *)(iVar1 + piVar2[2] + 0x30) = iVar1 + piVar2[2];
        FUN_004c8c00(this,(undefined4 *)(iVar1 + 0x1c + piVar2[2]));
        uVar5 = uVar5 + 1;
        iVar1 = iVar1 + 0x3c;
      } while (uVar5 < *(uint *)(param_1 + 0x90));
    }
    FUN_004b4f00((void *)(param_1 + 0x88),piVar2);
    iVar1 = FUN_004c8c70(this);
    iVar1 = *(int *)(iVar1 + 0x14);
    if (iVar1 == 0) {
      return 0;
    }
  }
  FUN_004c8c40(this,iVar1 + 0x1c);
  return iVar1;
}


/* 004b7060 size=26 */

void __thiscall FUN_004b7060(void *this,int param_1)

{
  if (param_1 != 0) {
    FUN_004c8c00((void *)((int)this + 0x80),(undefined4 *)(param_1 + 0x1c));
  }
  return;
}


/* 004b70b0 size=13 */

uint __thiscall FUN_004b70b0(void *this,uint param_1)

{
  return param_1 % *(uint *)this;
}


/* 004b70c0 size=62 */

undefined4 __thiscall FUN_004b70c0(void *this,uint param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_004b70b0(this,param_1);
  iVar2 = FUN_004c8ca0(this,uVar1);
  while( true ) {
    if (iVar2 == 0) {
      return 0;
    }
    if (**(uint **)(iVar2 + 0x14) == param_1) break;
    if (*(int *)(iVar2 + 4) == 0) {
      return 0;
    }
    iVar2 = *(int *)(iVar2 + 4) + -4;
  }
  return *(undefined4 *)(iVar2 + 0x14);
}


/* 004b7110 size=41 */

uint __thiscall FUN_004b7110(void *this,char *param_1)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  uVar3 = 0;
  cVar2 = *param_1;
  while (cVar2 != '\0') {
    pcVar1 = param_1 + 1;
    uVar3 = uVar3 + 1;
    param_1 = param_1 + 1;
    cVar2 = *pcVar1;
  }
  return uVar3 % *(uint *)this;
}


/* 004b7140 size=177 */

undefined4 __thiscall FUN_004b7140(void *this,byte *param_1,int param_2)

{
  byte bVar1;
  void *this_00;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  void *extraout_ECX;
  void *extraout_ECX_00;
  byte *pbVar6;
  bool bVar7;
  
  if (param_1 != (byte *)0x0) {
    uVar2 = FUN_004b7110(this,(char *)param_1);
    iVar3 = FUN_004c8ca0(this,uVar2);
    this_00 = extraout_ECX;
    if (param_2 == 0) {
      if (iVar3 != 0) {
        do {
          pbVar4 = (byte *)**(undefined4 **)(iVar3 + 0x14);
          pbVar6 = param_1;
          do {
            bVar1 = *pbVar4;
            bVar7 = bVar1 < *pbVar6;
            if (bVar1 != *pbVar6) {
LAB_004b71c7:
              iVar5 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
              goto LAB_004b71cc;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar4[1];
            bVar7 = bVar1 < pbVar6[1];
            if (bVar1 != pbVar6[1]) goto LAB_004b71c7;
            pbVar4 = pbVar4 + 2;
            pbVar6 = pbVar6 + 2;
          } while (bVar1 != 0);
          iVar5 = 0;
LAB_004b71cc:
          if (iVar5 == 0) goto LAB_004b71e7;
          if (*(int *)(iVar3 + 4) == 0) {
            return 0;
          }
          iVar3 = *(int *)(iVar3 + 4) + -4;
          if (iVar3 == 0) {
            return 0;
          }
        } while( true );
      }
    }
    else {
      for (; iVar3 != 0; iVar3 = *(int *)(iVar3 + 4) + -4) {
        uVar2 = FUN_004c4c00(this_00,(byte *)**(undefined4 **)(iVar3 + 0x14),param_1);
        if (uVar2 == 0) {
LAB_004b71e7:
          return *(undefined4 *)(iVar3 + 0x14);
        }
        if (*(int *)(iVar3 + 4) == 0) {
          return 0;
        }
        this_00 = extraout_ECX_00;
      }
    }
  }
  return 0;
}


/* 004b7200 size=18 */

void __thiscall FUN_004b7200(void *this,undefined4 param_1)

{
  *(undefined ***)this = &PTR_FUN_004ceed0;
  *(undefined4 *)((int)this + 0xc) = param_1;
  return;
}


/* 004b7220 size=30 */

undefined4 * __thiscall FUN_004b7220(void *this,byte param_1)

{
  FUN_004b7240(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004b7240 size=14 */

void __fastcall FUN_004b7240(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004ceed0;
  param_1[3] = 0;
  return;
}


/* 004b7250 size=40 */

undefined4 * __thiscall FUN_004b7250(void *this,undefined4 param_1)

{
  FUN_004b7200(this,param_1);
  *(undefined ***)this = &PTR_FUN_004ceef4;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x20) = 0xffffffff;
  return this;
}


/* 004b7280 size=30 */

undefined4 * __thiscall FUN_004b7280(void *this,byte param_1)

{
  FUN_004b72a0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004b72a0 size=94 */

void __fastcall FUN_004b72a0(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004cada8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_004ceef4;
  local_4 = 0;
  if (param_1[4] != 0) {
    FUN_004b7520((int)param_1);
  }
  if ((undefined *)param_1[5] != (undefined *)0x0) {
    FUN_00430df0((undefined *)param_1[5]);
  }
  FUN_004b7240(param_1);
  ExceptionList = local_c;
  return;
}


/* 004b7300 size=176 */

uint __thiscall FUN_004b7300(void *this,int param_1,int param_2,uint param_3,char *param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if (param_3 == 0) {
    return 0;
  }
  iVar1 = param_1 + param_2;
  if (*(int *)((int)this + 0x20) != iVar1) {
    iVar2 = FUN_004ba72b(*(int **)((int)this + 0x10),iVar1,0);
    while (iVar2 != 0) {
      iVar2 = (**(code **)(**(int **)((int)this + 0xc) + 8))();
      if (iVar2 == 0) goto LAB_004b73a0;
      iVar2 = FUN_004ba72b(*(int **)((int)this + 0x10),iVar1,0);
    }
  }
  uVar3 = FUN_004bb674(param_4,1,param_3,*(int **)((int)this + 0x10));
  while( true ) {
    if (uVar3 == param_3) {
      *(uint *)((int)this + 0x20) = uVar3 + iVar1;
      return uVar3;
    }
    iVar2 = (**(code **)(**(int **)((int)this + 0xc) + 8))();
    if (iVar2 == 0) break;
    uVar3 = FUN_004bb674(param_4,1,param_3,*(int **)((int)this + 0x10));
  }
LAB_004b73a0:
  *(undefined4 *)((int)this + 0x20) = 0xffffffff;
  return 0;
}


/* 004b73b0 size=151 */

uint __thiscall FUN_004b73b0(void *this,int param_1,int param_2,uint param_3,char *param_4)

{
  int iVar1;
  uint uVar2;
  
  *(undefined4 *)((int)this + 0x20) = 0xffffffff;
  if (param_3 != 0) {
    iVar1 = FUN_004ba72b(*(int **)((int)this + 0x10),param_1 + param_2,0);
    while (iVar1 != 0) {
      iVar1 = (**(code **)(**(int **)((int)this + 0xc) + 8))();
      if (iVar1 == 0) {
        return 0;
      }
      iVar1 = FUN_004ba72b(*(int **)((int)this + 0x10),param_1 + param_2,0);
    }
    uVar2 = FUN_004bb78b(param_4,1,param_3,*(int **)((int)this + 0x10));
    if (uVar2 == param_3) {
      return uVar2;
    }
    while (iVar1 = (**(code **)(**(int **)((int)this + 0xc) + 8))(), iVar1 != 0) {
      uVar2 = FUN_004bb78b(param_4,1,param_3,*(int **)((int)this + 0x10));
      if (uVar2 == param_3) {
        return uVar2;
      }
    }
  }
  return 0;
}


/* 004b7520 size=86 */

undefined4 __fastcall FUN_004b7520(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    iVar1 = FUN_004ba14f(*(FILE **)(param_1 + 0x10));
    if (iVar1 == 0) break;
    iVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 8))();
  }
  *(undefined4 *)(param_1 + 0x10) = 0;
  if (*(undefined **)(param_1 + 0x14) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)(param_1 + 0x14));
  }
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
  return 1;
}


/* 004b7580 size=56 */

undefined4 __fastcall FUN_004b7580(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    iVar1 = FUN_004bbe95(*(int **)(param_1 + 0x10));
    if (iVar1 == 0) break;
    iVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 8))();
  }
  return 1;
}


/* 004b75c0 size=65 */

bool __fastcall FUN_004b75c0(int *param_1)

{
  int iVar1;
  
  param_1[8] = -1;
  if ((char *)param_1[4] == (char *)0x0) {
    return false;
  }
  iVar1 = FUN_004ba5a8((char *)param_1[4]);
  if (iVar1 == -1) {
    iVar1 = (**(code **)(*param_1 + 0x10))(param_1[5],param_1[6],0);
    return iVar1 != 0;
  }
  return true;
}


/* 004b7620 size=70 */

undefined4 * __thiscall FUN_004b7620(void *this,undefined4 param_1,undefined4 param_2)

{
  FUN_004b7200(this,param_1);
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined ***)((int)this + 0x10) = &PTR_FUN_004cef3c;
  *(undefined ***)((int)this + 0x1c) = &PTR_FUN_004cef3c;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x28) = 0;
  *(undefined4 *)((int)this + 0x34) = 0;
  *(undefined ***)this = &PTR_FUN_004cef18;
  *(undefined4 *)((int)this + 0x2c) = param_2;
  *(undefined4 *)((int)this + 0x30) = 1;
  return this;
}


/* 004b7670 size=30 */

undefined4 * __thiscall FUN_004b7670(void *this,byte param_1)

{
  FUN_004b7690(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004b7690 size=119 */

void __fastcall FUN_004b7690(undefined4 *param_1)

{
  int *piVar1;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  pvStack_c = ExceptionList;
  puStack_8 = &LAB_004cadde;
  ExceptionList = &pvStack_c;
  *param_1 = &PTR_FUN_004cef18;
  piVar1 = (int *)param_1[5];
  local_4 = 2;
  while (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))(1);
    piVar1 = (int *)param_1[5];
  }
  piVar1 = (int *)param_1[8];
  while (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))(1);
    piVar1 = (int *)param_1[8];
  }
  param_1[7] = &PTR_LAB_004ceecc;
  param_1[4] = &PTR_LAB_004ceecc;
  FUN_004b7240(param_1);
  ExceptionList = pvStack_c;
  return;
}


/* 004b7710 size=7 */

void __fastcall FUN_004b7710(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004ceecc;
  return;
}


/* 004b7750 size=29 */

undefined4 __fastcall FUN_004b7750(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x14);
  while (iVar1 != 0) {
    FUN_004b7b00(iVar1);
    iVar1 = *(int *)(param_1 + 0x14);
  }
  return 1;
}


/* 004b7770 size=6 */

undefined4 FUN_004b7770(void)

{
  return 1;
}


/* 004b7780 size=155 */

undefined4 * __thiscall FUN_004b7780(void *this,undefined4 param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004cadf8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004b7200(this,param_1);
  *(undefined4 *)((int)this + 0x18) = param_3;
  uVar3 = 0xffffffff;
  *(undefined ***)this = &PTR_FUN_004cef40;
  *(undefined4 *)((int)this + 0x14) = 0;
  pcVar2 = param_2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  local_4 = 0;
  pcVar2 = (char *)FUN_00430de0(~uVar3);
  uVar3 = 0xffffffff;
  *(char **)((int)this + 0x10) = pcVar2;
  do {
    pcVar5 = param_2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = param_2 + 1;
    cVar1 = *param_2;
    param_2 = pcVar5;
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
  FUN_004c8cc0((void *)(*(int *)((int)this + 0x18) + 0x1c),(int)this);
  ExceptionList = local_c;
  return this;
}


/* 004b7820 size=30 */

undefined4 * __thiscall FUN_004b7820(void *this,byte param_1)

{
  FUN_004b7840(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004b7840 size=106 */

void __fastcall FUN_004b7840(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004cae18;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_004cef40;
  local_4 = 0;
  if (param_1[5] != 0) {
    FUN_004b7b00((int)param_1);
  }
  if ((undefined *)param_1[4] != (undefined *)0x0) {
    FUN_00430df0((undefined *)param_1[4]);
  }
  FUN_004c8cf0((void *)(param_1[6] + 0x1c),(int)param_1);
  FUN_004b7240(param_1);
  ExceptionList = local_c;
  return;
}


/* 004b78b0 size=159 */

uint __thiscall FUN_004b78b0(void *this,undefined4 param_1,int param_2,uint param_3,char *param_4)

{
  int iVar1;
  uint uVar2;
  
  if (param_3 != 0) {
    if (*(int *)((int)this + 0x14) == 0) {
      FUN_004b7a50((int)this);
    }
    iVar1 = FUN_004ba72b(*(int **)((int)this + 0x14),param_2,0);
    while (iVar1 != 0) {
      iVar1 = (**(code **)(**(int **)(*(int *)((int)this + 0x18) + 0xc) + 8))();
      if (iVar1 == 0) {
        return 0;
      }
      iVar1 = FUN_004ba72b(*(int **)((int)this + 0x14),param_2,0);
    }
    uVar2 = FUN_004bb674(param_4,1,param_3,*(int **)((int)this + 0x14));
    if (uVar2 == param_3) {
      return uVar2;
    }
    while (iVar1 = (**(code **)(**(int **)(*(int *)((int)this + 0x18) + 0xc) + 8))(), iVar1 != 0) {
      uVar2 = FUN_004bb674(param_4,1,param_3,*(int **)((int)this + 0x14));
      if (uVar2 == param_3) {
        return uVar2;
      }
    }
  }
  return 0;
}


/* 004b7950 size=159 */

uint __thiscall FUN_004b7950(void *this,undefined4 param_1,int param_2,uint param_3,char *param_4)

{
  int iVar1;
  uint uVar2;
  
  if (param_3 != 0) {
    if (*(int *)((int)this + 0x14) == 0) {
      FUN_004b7a50((int)this);
    }
    iVar1 = FUN_004ba72b(*(int **)((int)this + 0x14),param_2,0);
    while (iVar1 != 0) {
      iVar1 = (**(code **)(**(int **)(*(int *)((int)this + 0x18) + 0xc) + 8))();
      if (iVar1 == 0) {
        return 0;
      }
      iVar1 = FUN_004ba72b(*(int **)((int)this + 0x14),param_2,0);
    }
    uVar2 = FUN_004bb78b(param_4,1,param_3,*(int **)((int)this + 0x14));
    if (uVar2 == param_3) {
      return uVar2;
    }
    while (iVar1 = (**(code **)(**(int **)(*(int *)((int)this + 0x18) + 0xc) + 8))(), iVar1 != 0) {
      uVar2 = FUN_004bb78b(param_4,1,param_3,*(int **)((int)this + 0x14));
      if (uVar2 == param_3) {
        return uVar2;
      }
    }
  }
  return 0;
}


/* 004b7a00 size=73 */

bool __fastcall FUN_004b7a00(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(int **)(param_1 + 0x14) == (int *)0x0) {
    bVar2 = true;
  }
  else {
    iVar1 = FUN_004bbe95(*(int **)(param_1 + 0x14));
    bVar2 = iVar1 == 0;
    if (!bVar2) {
      do {
        iVar1 = (**(code **)(**(int **)(*(int *)(param_1 + 0x18) + 0xc) + 8))();
        if (iVar1 == 0) {
          return false;
        }
        iVar1 = FUN_004bbe95(*(int **)(param_1 + 0x14));
      } while (iVar1 != 0);
      return iVar1 == 0;
    }
  }
  return bVar2;
}


/* 004b7a50 size=173 */

undefined4 __fastcall FUN_004b7a50(int param_1)

{
  int *piVar1;
  int iVar2;
  LPCSTR pCVar3;
  char *pcVar4;
  
  if (*(int *)(param_1 + 0x14) == 0) {
    iVar2 = *(int *)(param_1 + 0x18);
    if ((*(int *)(iVar2 + 0x2c) < *(int *)(iVar2 + 0x28)) && (*(int *)(iVar2 + 0x18) != 0)) {
      FUN_004b7b00(*(int *)(iVar2 + 0x18));
    }
    do {
      iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0x30);
      if (*(int *)(*(int *)(param_1 + 0x18) + 0x34) == 0) {
        if (iVar2 == 0) {
          pCVar3 = *(LPCSTR *)(param_1 + 0x10);
          pcVar4 = &DAT_004e0d28;
        }
        else {
          pCVar3 = *(LPCSTR *)(param_1 + 0x10);
          pcVar4 = &DAT_004d57f4;
        }
      }
      else {
        if (iVar2 != 0) {
          return 0;
        }
        pCVar3 = *(LPCSTR *)(param_1 + 0x10);
        pcVar4 = &DAT_004e0d2c;
      }
      iVar2 = FUN_004ba1fd(pCVar3,pcVar4);
      *(int *)(param_1 + 0x14) = iVar2;
      if (iVar2 != 0) break;
      iVar2 = (**(code **)(**(int **)(*(int *)(param_1 + 0x18) + 0xc) + 8))();
      if (iVar2 == 0) {
        return 0;
      }
    } while (*(int *)(param_1 + 0x14) == 0);
    FUN_004c8cf0((void *)(*(int *)(param_1 + 0x18) + 0x1c),param_1);
    FUN_004c8cc0((void *)(*(int *)(param_1 + 0x18) + 0x10),param_1);
    piVar1 = (int *)(*(int *)(param_1 + 0x18) + 0x28);
    *piVar1 = *piVar1 + 1;
  }
  return 1;
}


/* 004b7b00 size=124 */

undefined1 __fastcall FUN_004b7b00(int param_1)

{
  int iVar1;
  
  if (*(FILE **)(param_1 + 0x14) == (FILE *)0x0) {
    return 1;
  }
  iVar1 = FUN_004ba14f(*(FILE **)(param_1 + 0x14));
  while( true ) {
    if (iVar1 == 0) {
      *(int *)(*(int *)(param_1 + 0x18) + 0x28) = *(int *)(*(int *)(param_1 + 0x18) + 0x28) + -1;
      FUN_004c8cf0((void *)(*(int *)(param_1 + 0x18) + 0x10),param_1);
      FUN_004c8cc0((void *)(*(int *)(param_1 + 0x18) + 0x1c),param_1);
      *(undefined4 *)(param_1 + 0x14) = 0;
      return 1;
    }
    iVar1 = (**(code **)(**(int **)(*(int *)(param_1 + 0x18) + 0xc) + 8))();
    if (iVar1 == 0) break;
    iVar1 = FUN_004ba14f(*(FILE **)(param_1 + 0x14));
  }
  return 0;
}


/* 004b7b90 size=65 */

void __cdecl FUN_004b7b90(uint *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  *param_1 = param_2;
  param_1[1] = param_2;
  if (param_2 < 4) {
    param_1[1] = 4;
  }
  uVar1 = param_1[1] & 3;
  if (uVar1 != 0) {
    param_1[1] = (param_1[1] - uVar1) + 4;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[2] = param_3;
  param_1[5] = 0;
  param_1[6] = 0;
  return;
}


/* 004b7be0 size=37 */

void __cdecl FUN_004b7be0(uint *param_1,uint param_2,uint param_3,int param_4)

{
  FUN_004b7b90(param_1,param_2,param_3);
  FUN_004b7c60((int)param_1,param_4);
  return;
}


/* 004b7c10 size=49 */

void __cdecl FUN_004b7c10(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 0x14);
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar2;
    FUN_00430df0((undefined *)puVar2);
    puVar2 = puVar1;
  }
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}


/* 004b7c50 size=16 */

void __cdecl FUN_004b7c50(int param_1)

{
  FUN_004b7c10(param_1);
  return;
}


/* 004b7c60 size=94 */

undefined4 __cdecl FUN_004b7c60(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (param_2 != 0) {
    puVar2 = (undefined4 *)FUN_00430de0(*(int *)(param_1 + 4) * param_2 + 8);
    if (puVar2 == (undefined4 *)0x0) {
      return 0;
    }
    uVar1 = *(undefined4 *)(param_1 + 0x14);
    puVar2[1] = param_2;
    *puVar2 = uVar1;
    *(undefined4 **)(param_1 + 0x14) = puVar2;
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + param_2;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
    puVar2 = puVar2 + 2;
    do {
      *puVar2 = *(undefined4 *)(param_1 + 0x18);
      *(undefined4 **)(param_1 + 0x18) = puVar2;
      puVar2 = (undefined4 *)((int)puVar2 + *(int *)(param_1 + 4));
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return 1;
}


/* 004b7ce0 size=37 */

undefined4 __fastcall FUN_004b7ce0(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = 0;
  iVar3 = 0x100;
  do {
    uVar1 = FUN_004bbd5a(uVar2);
    (&DAT_004ecb58)[uVar2] = (char)uVar1;
    uVar2 = uVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return param_1;
}


/* 004b7d10 size=64 */

undefined4 __cdecl FUN_004b7d10(byte *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_2 - (int)param_1;
  while( true ) {
    if ((&DAT_004ecb58)[*param_1] != (&DAT_004ecb58)[param_1[iVar1]]) {
      return 0;
    }
    if (*param_1 == 0) break;
    param_1 = param_1 + 1;
  }
  return 1;
}


/* 004b7d50 size=188 */

undefined4 __cdecl FUN_004b7d50(char *param_1,char *param_2,char *param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  *param_3 = '\0';
  uVar2 = 0xffffffff;
  *param_2 = '\0';
  pcVar6 = param_1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  iVar3 = ~uVar2 - 1;
  uVar2 = 0xffffffff;
  uVar5 = 0;
  if (0 < iVar3) {
    do {
      if ((param_1[uVar5] == '\\') || (param_1[uVar5] == '/')) {
        uVar2 = uVar5;
      }
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < iVar3);
    if (uVar2 != 0xffffffff) {
      pcVar6 = param_1;
      pcVar7 = param_2;
      for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar7 = pcVar7 + 4;
      }
      uVar4 = iVar3 - uVar2;
      for (uVar5 = uVar2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar7 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      }
      param_2[uVar2] = '\0';
      pcVar6 = param_1 + uVar2 + 1;
      pcVar7 = param_3;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar2 = uVar4 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar7 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      }
      param_3[uVar4] = '\0';
      return 1;
    }
  }
  uVar2 = 0xffffffff;
  *param_2 = '\0';
  do {
    pcVar6 = param_1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar6 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar6;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar6 = pcVar6 + -uVar2;
  for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)param_3 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    param_3 = param_3 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_3 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    param_3 = param_3 + 1;
  }
  return 1;
}


/* 004b7e10 size=115 */

undefined4 __cdecl FUN_004b7e10(char *param_1,char *param_2,char *param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  uVar2 = 0xffffffff;
  pcVar5 = param_1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  uVar3 = ~uVar2 - 1;
  uVar4 = 0;
  uVar2 = uVar3;
  if (0 < (int)uVar3) {
    do {
      if (param_1[uVar4] == '.') {
        uVar2 = uVar4;
      }
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < (int)uVar3);
  }
  pcVar5 = param_1;
  pcVar6 = param_2;
  for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  uVar3 = uVar3 - uVar2;
  for (uVar4 = uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  param_2[uVar2] = '\0';
  pcVar5 = param_1 + uVar2 + 1;
  pcVar6 = param_3;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar2 = uVar3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  param_3[uVar3] = '\0';
  return 1;
}


/* 004b7e90 size=259 */

undefined4 __cdecl
FUN_004b7e90(char *param_1,char *param_2,char *param_3,char *param_4,char *param_5)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  char local_400 [256];
  char local_300 [256];
  char local_200 [256];
  char local_100 [256];
  
  FUN_004b7d50(param_1,local_300,local_400);
  FUN_004b7e10(local_400,local_200,local_100);
  if (param_2 != (char *)0x0) {
    uVar2 = 0xffffffff;
    pcVar4 = local_300;
    do {
      pcVar5 = pcVar4;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar5 = pcVar4 + 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar5;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    pcVar4 = pcVar5 + -uVar2;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)param_2 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      param_2 = param_2 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_2 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      param_2 = param_2 + 1;
    }
  }
  if (param_3 != (char *)0x0) {
    uVar2 = 0xffffffff;
    pcVar4 = local_400;
    do {
      pcVar5 = pcVar4;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar5 = pcVar4 + 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar5;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    pcVar4 = pcVar5 + -uVar2;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)param_3 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      param_3 = param_3 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_3 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      param_3 = param_3 + 1;
    }
  }
  if (param_4 != (char *)0x0) {
    uVar2 = 0xffffffff;
    pcVar4 = local_200;
    do {
      pcVar5 = pcVar4;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar5 = pcVar4 + 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar5;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    pcVar4 = pcVar5 + -uVar2;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)param_4 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      param_4 = param_4 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_4 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      param_4 = param_4 + 1;
    }
  }
  if (param_5 != (char *)0x0) {
    uVar2 = 0xffffffff;
    pcVar4 = local_100;
    do {
      pcVar5 = pcVar4;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar5 = pcVar4 + 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar5;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    pcVar4 = pcVar5 + -uVar2;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)param_5 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      param_5 = param_5 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_5 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      param_5 = param_5 + 1;
    }
  }
  return 1;
}


/* 004b7fa0 size=117 */

undefined4 * __fastcall FUN_004b7fa0(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cef64;
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
  *(undefined2 *)(param_1 + 5) = 0x96;
  return param_1;
}


