/* lithtech.exe decompilation - unnamed_004a4000 */
#include "ghidra_types.h"

/* 004a4080 size=36 */

void __thiscall FUN_004a4080(void *this,int *param_1)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)**(undefined4 **)((int)this + 4))();
  *(undefined4 *)((int)this + 8) = uVar1;
  *param_1 = (int)this;
  FUN_004a40b0((int)this + 0xc,param_1);
  return;
}


/* 004a40b0 size=342 */

void __cdecl FUN_004a40b0(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  float local_18;
  float fStack_14;
  float fStack_10;
  float local_c;
  float fStack_8;
  float fStack_4;
  
  iVar1 = *(int *)(*param_2 + 8);
  if (*(int *)(param_1 + 0x44) != 0) {
    iVar2 = param_2[1];
    iVar3 = *(int *)(param_1 + 4 + iVar2 * 8);
    while (iVar3 != param_1 + iVar2 * 8) {
      piVar4 = *(int **)(iVar3 + 8);
      iVar3 = *(int *)(iVar3 + 4);
      if (piVar4[0x16] != iVar1) {
        piVar4[0x16] = iVar1;
        (**(code **)(*piVar4 + 0xc))(&local_18,&local_c);
        if ((((local_18 <= (float)param_2[5]) && (fStack_14 <= (float)param_2[6])) &&
            (fStack_10 <= (float)param_2[7])) &&
           ((((float)param_2[2] <= local_c && ((float)param_2[3] <= fStack_8)) &&
            ((float)param_2[4] <= fStack_4)))) {
          (*(code *)param_2[0xb])(piVar4,param_2[0xc]);
        }
      }
    }
    if (*(int *)(param_1 + 0x4c) != 0) {
      if ((float)param_2[2] < *(float *)(param_1 + 0x30)) {
        if ((float)param_2[4] < *(float *)(param_1 + 0x38)) {
          FUN_004a40b0(*(int *)(param_1 + 0x4c),param_2);
        }
        if (*(float *)(param_1 + 0x38) < (float)param_2[7]) {
          FUN_004a40b0(*(int *)(param_1 + 0x50),param_2);
        }
      }
      if (*(float *)(param_1 + 0x30) < (float)param_2[5]) {
        if ((float)param_2[4] < *(float *)(param_1 + 0x38)) {
          FUN_004a40b0(*(int *)(param_1 + 0x54),param_2);
        }
        if (*(float *)(param_1 + 0x38) < (float)param_2[7]) {
          FUN_004a40b0(*(int *)(param_1 + 0x58),param_2);
        }
      }
    }
  }
  return;
}


/* 004a42b0 size=259 */

uint __cdecl FUN_004a42b0(int param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint local_4;
  
  piVar1 = param_2;
  local_4 = 0;
  iVar3 = param_2[1];
  iVar4 = *(int *)(param_1 + 4 + iVar3 * 8);
  while (iVar4 != param_1 + iVar3 * 8) {
    iVar5 = *(int *)(iVar4 + 8);
    iVar4 = *(int *)(iVar4 + 4);
    if (*(int *)(iVar5 + 0x58) != *(int *)(*param_2 + 8)) {
      *(int *)(iVar5 + 0x58) = *(int *)(*param_2 + 8);
      uVar2 = (*(code *)param_2[8])(iVar5,param_2[9]);
      local_4 = local_4 | uVar2;
    }
  }
  if (*(int *)(param_1 + 0x4c) != 0) {
    param_2 = (int *)(uint)(*(float *)(param_1 + 0x30) < (float)param_2[2]);
    uVar2 = (uint)(*(float *)(param_1 + 0x38) < (float)piVar1[4]);
    iVar3 = FUN_004a43c0(*(int *)(param_1 + 0x4c + (uVar2 + (int)param_2 * 2) * 4),(int)piVar1);
    iVar4 = (uint)(param_2 == (int *)0x0) * 2;
    iVar5 = FUN_004a43c0(*(int *)(param_1 + 0x4c + (iVar4 + uVar2) * 4),(int)piVar1);
    iVar6 = FUN_004a43c0(*(int *)(param_1 + 0x4c + ((uint)(uVar2 == 0) + (int)param_2 * 2) * 4),
                         (int)piVar1);
    iVar4 = FUN_004a43c0(*(int *)(param_1 + 0x4c + ((uint)(uVar2 == 0) + iVar4) * 4),(int)piVar1);
    if (iVar4 != 0 || ((iVar3 != 0 || iVar5 != 0) || iVar6 != 0)) {
      return 1;
    }
  }
  return local_4;
}


/* 004a43c0 size=732 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_004a43c0(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  
  if (((((*(float *)(param_1 + 0x18) <= *(float *)(param_2 + 8)) &&
        (*(float *)(param_1 + 0x20) <= *(float *)(param_2 + 0x10))) &&
       (*(float *)(param_2 + 8) <= *(float *)(param_1 + 0x24))) &&
      (*(float *)(param_2 + 0x10) <= *(float *)(param_1 + 0x2c))) ||
     (((*(float *)(param_1 + 0x18) <= *(float *)(param_2 + 0x14) &&
       (*(float *)(param_1 + 0x20) <= *(float *)(param_2 + 0x1c))) &&
      ((*(float *)(param_2 + 0x14) <= *(float *)(param_1 + 0x24) &&
       (*(float *)(param_2 + 0x1c) <= *(float *)(param_1 + 0x2c))))))) goto LAB_004a468c;
  if ((*(float *)(param_1 + 0x18) <= *(float *)(param_2 + 8)) ||
     (*(float *)(param_1 + 0x18) <= *(float *)(param_2 + 0x14))) {
    if ((*(float *)(param_1 + 0x24) < *(float *)(param_2 + 8)) &&
       (*(float *)(param_1 + 0x24) < *(float *)(param_2 + 0x14))) {
      iVar7 = 1;
      goto LAB_004a448c;
    }
  }
  else {
    iVar7 = 0;
LAB_004a448c:
    if ((*(float *)(param_1 + 0x20) <= *(float *)(param_2 + 0x10)) ||
       (*(float *)(param_1 + 0x20) <= *(float *)(param_2 + 0x1c))) {
      if ((*(float *)(param_2 + 0x10) <= *(float *)(param_1 + 0x2c)) ||
         (*(float *)(param_2 + 0x1c) <= *(float *)(param_1 + 0x2c))) {
        iVar5 = 2;
      }
      else {
        iVar5 = 1;
      }
    }
    else {
      iVar5 = 0;
    }
    if (iVar7 == iVar5) {
      return 0;
    }
  }
  fVar1 = *(float *)(param_2 + 0x10);
  fVar2 = *(float *)(param_2 + 8);
  fVar3 = *(float *)(param_1 + 0x18);
  if (fVar2 < fVar3 != *(float *)(param_2 + 0x14) <= fVar3) {
    fVar4 = *(float *)(param_2 + 0x14) - fVar2;
    if ((float)_DAT_004ccc08 <= ABS(fVar4)) {
      fVar1 = ((*(float *)(param_2 + 0x1c) - fVar1) * (fVar3 - fVar2)) / fVar4 + fVar1;
    }
    if ((*(float *)(param_1 + 0x20) <= fVar1) && (fVar1 <= *(float *)(param_1 + 0x2c)))
    goto LAB_004a468c;
  }
  fVar1 = *(float *)(param_2 + 0x10);
  fVar2 = *(float *)(param_2 + 8);
  fVar3 = *(float *)(param_1 + 0x24);
  if (fVar2 < fVar3 != *(float *)(param_2 + 0x14) <= fVar3) {
    fVar4 = *(float *)(param_2 + 0x14) - fVar2;
    if ((float)_DAT_004ccc08 <= ABS(fVar4)) {
      fVar1 = ((*(float *)(param_2 + 0x1c) - fVar1) * (fVar3 - fVar2)) / fVar4 + fVar1;
    }
    if ((*(float *)(param_1 + 0x20) <= fVar1) && (fVar1 <= *(float *)(param_1 + 0x2c)))
    goto LAB_004a468c;
  }
  iVar7 = FUN_004a46a0(*(float *)(param_2 + 0x10),*(float *)(param_2 + 0x1c),
                       *(float *)(param_1 + 0x20),*(float *)(param_1 + 0x18),
                       *(float *)(param_1 + 0x24),*(float *)(param_2 + 8),*(float *)(param_2 + 0x14)
                      );
  if ((iVar7 == 0) &&
     (iVar7 = FUN_004a46a0(*(float *)(param_2 + 0x10),*(float *)(param_2 + 0x1c),
                           *(float *)(param_1 + 0x2c),*(float *)(param_1 + 0x18),
                           *(float *)(param_1 + 0x24),*(float *)(param_2 + 8),
                           *(float *)(param_2 + 0x14)), iVar7 == 0)) {
    return 0;
  }
LAB_004a468c:
  uVar6 = FUN_004a42b0(param_1,(int *)param_2);
  return uVar6;
}


/* 004a46a0 size=142 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_004a46a0(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
            float param_7)

{
  if (param_1 < param_3 != param_2 <= param_3) {
    if ((float)_DAT_004ccc08 <= ABS(param_2 - param_1)) {
      param_6 = ((param_7 - param_6) * (param_3 - param_1)) / (param_2 - param_1) + param_6;
    }
    if ((param_4 <= param_6) && (param_6 <= param_5)) {
      return 1;
    }
  }
  return 0;
}


/* 004a4810 size=59 */

void __cdecl FUN_004a4810(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 4);
  while (iVar1 != param_1) {
    iVar2 = *(int *)(iVar1 + 8);
    iVar1 = *(int *)(iVar1 + 4);
    iVar3 = *(int *)(*(int *)(param_2 + 0x44) + 8);
    if (*(int *)(iVar2 + 0x58) != iVar3) {
      *(int *)(iVar2 + 0x58) = iVar3;
      (**(code **)(param_2 + 0x14))(iVar2,*(undefined4 *)(param_2 + 0x1c));
    }
  }
  return;
}


/* 004a4850 size=109 */

int __thiscall FUN_004a4850(void *this,int param_1)

{
  FUN_004a3d60((int)this);
  *(undefined4 *)((int)this + 0x70) = *(undefined4 *)(param_1 + 0x70);
  *(undefined4 *)((int)this + 0x6c) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)((int)this + 0x68) = *(undefined4 *)(param_1 + 0x68);
  FUN_004a3850((void *)((int)this + 0xc),*(float *)(param_1 + 0x24),*(float *)(param_1 + 0x28),
               *(float *)(param_1 + 0x2c),*(float *)(param_1 + 0x30),*(float *)(param_1 + 0x34),
               *(float *)(param_1 + 0x38));
  FUN_004a49c0((int)this + 0xc,param_1 + 0xc);
  return;
}


/* 004a48c0 size=248 */

/* FUN_004a48c0: lifted from original x86 -> lt_lifted.c */


/* 004a49c0 size=94 */

undefined4 FUN_004a49c0(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  if (*(int *)(param_2 + 0x4c) != 0) {
    iVar1 = FUN_004a3a70(param_1);
    if (iVar1 == 0) {
      return 0;
    }
    uVar3 = 0;
    piVar2 = (int *)(param_1 + 0x4c);
    do {
      iVar1 = FUN_004a49c0(*piVar2,*(int *)((param_2 - param_1) + (int)piVar2));
      if (iVar1 == 0) {
        return 0;
      }
      uVar3 = uVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (uVar3 < 4);
  }
  return 1;
}


/* 004a4a20 size=35 */

void __thiscall FUN_004a4a20(void *this,int param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 0x44);
  *piVar2 = (int)this + 0x74;
  puVar1 = *(undefined4 **)((int)this + 0x78);
  *(undefined4 **)(param_1 + 0x48) = puVar1;
  *puVar1 = piVar2;
  *(int **)(*piVar2 + 4) = piVar2;
  *(undefined4 *)(param_1 + 0x50) = 0;
  return;
}


/* 004a4a50 size=199 */

undefined4 * __thiscall FUN_004a4a50(void *this,undefined4 *param_1,uint param_2)

{
  undefined4 *puVar1;
  void *this_00;
  undefined4 *puVar2;
  LONG LVar3;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c8ffe;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  local_4 = 1;
  *(undefined ***)this = &PTR_FUN_004cdb64;
  *(undefined1 *)((int)this + 0x18) = 0;
  if ((param_1 != (undefined4 *)0x0) && (param_2 != 0)) {
    this_00 = (void *)FUN_00430de0(0x10);
    (*(uint8_t*)((char*)&local_4+0)) = 2;
    if (this_00 == (void *)0x0) {
      puVar2 = (undefined4 *)0x0;
    }
    else {
      puVar2 = FUN_004acb10(this_00,param_1,param_2,'\0');
    }
    puVar1 = *(undefined4 **)((int)this + 8);
    local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
    if (puVar1 != puVar2) {
      if (puVar1 != (undefined4 *)0x0) {
        LVar3 = InterlockedDecrement(puVar1 + 1);
        if ((LVar3 < 1) && (puVar1 != (undefined4 *)0x0)) {
          (**(code **)*puVar1)(1);
        }
      }
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        InterlockedIncrement(puVar2 + 1);
      }
      *(undefined4 **)((int)this + 8) = puVar2;
    }
  }
  ExceptionList = local_c;
  return this;
}


/* 004a4b20 size=7 */

void __fastcall FUN_004a4b20(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cdb70;
  return;
}


/* 004a4b50 size=30 */

undefined4 * __thiscall FUN_004a4b50(void *this,byte param_1)

{
  FUN_004a4b70(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004a4b70 size=100 */

void __fastcall FUN_004a4b70(undefined4 *param_1)

{
  undefined4 *puVar1;
  LONG LVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9018;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_004cdb64;
  puVar1 = (undefined4 *)param_1[2];
  local_4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    LVar2 = InterlockedDecrement(puVar1 + 1);
    if ((LVar2 < 1) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
  }
  *param_1 = &PTR_LAB_004cdb70;
  ExceptionList = local_c;
  return;
}


/* 004a4be0 size=132 */

void __fastcall FUN_004a4be0(int *param_1)

{
  int iVar1;
  char cVar2;
  undefined1 auStackY_bc [128];
  uint local_28 [2];
  uint local_20;
  int *local_1c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004c9030;
  local_10 = ExceptionList;
  local_14 = auStackY_bc + 0x88;
  cVar2 = '\0';
  iVar1 = param_1[2];
  local_15 = 0;
  if (iVar1 != 0) {
    local_8 = 0;
    ExceptionList = &local_10;
    local_1c = param_1;
    FUN_004acbe0(local_28,*(undefined4 *)(iVar1 + 8),*(undefined4 *)(iVar1 + 0xc));
    cVar2 = (**(code **)(*param_1 + 4))(local_28);
    if ((cVar2 != '\0') &&
       (*(short *)(param_1 + 3) = (short)local_28[0], local_20 <= (local_28[0] & 0xffff))) {
      cVar2 = '\0';
    }
  }
  *(char *)(param_1 + 6) = cVar2;
  ExceptionList = local_10;
  return;
}


/* 004a4c70 size=102 */

int __thiscall FUN_004a4c70(void *this,void *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)((int)this + 8);
  if (iVar1 == 0) {
    FUN_004b17e0(param_1,(undefined4 *)0x0,0,(undefined4 *)0x0,0);
    return;
  }
  FUN_004b17e0(param_1,*(undefined4 **)(iVar1 + 8),(uint)*(ushort *)((int)this + 0xc),
               (undefined4 *)((uint)*(ushort *)((int)this + 0xc) + *(int *)(iVar1 + 8)),
               *(int *)(iVar1 + 0xc) - (uint)*(ushort *)((int)this + 0xc));
  return;
}


/* 004a4ce0 size=48 */

bool __thiscall FUN_004a4ce0(void *this,int param_1)

{
  int iVar1;
  
  if (*(char *)((int)this + 0x18) == '\0') {
    return true;
  }
  iVar1 = FUN_004bcb91((int *)0x0);
  return *(int *)((int)this + 0x14) <= iVar1 + param_1;
}


/* 004a4d10 size=46 */

/* FUN_004a4d10: lifted from original x86 -> lt_lifted.c */


/* 004a4d40 size=279 */

void __fastcall FUN_004a4d40(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c90ca;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_004cdb78;
  local_4 = 6;
  FUN_004ad860(param_1 + 100);
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  FUN_004ad860(param_1 + 0x5c);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004ad860(param_1 + 0x54);
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  FUN_004ad860(param_1 + 0x4c);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004ad860(param_1 + 0x44);
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004ad860(param_1 + 0x3c);
  (*(uint8_t*)((char*)&local_4+0)) = 9;
  FUN_004a9430((undefined4 *)param_1[0x36],param_1[0x38] - (int)param_1[0x36]);
  puVar2 = (undefined4 *)param_1[0xc];
  (*(uint8_t*)((char*)&local_4+0)) = 10;
  uVar1 = param_1[0xe] - (int)puVar2;
  FUN_004aa830(param_1 + 0xe);
  FUN_004a9430(puVar2,uVar1);
  puVar2 = (undefined4 *)param_1[8];
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0xb);
  if (puVar2 != (undefined4 *)0x0) {
    FUN_004aa6f0(puVar2,param_1[10] - (int)puVar2);
  }
  local_4 = 0xffffffff;
  FUN_004a4b70(param_1);
  ExceptionList = local_c;
  return;
}


/* 004a4e70 size=30 */

undefined4 * __thiscall FUN_004a4e70(void *this,byte param_1)

{
  FUN_004a4e90(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004a4e90 size=266 */

void __fastcall FUN_004a4e90(undefined4 *param_1)

{
  undefined4 *puVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c916a;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_004cdb78;
  local_4 = 6;
  FUN_004ad860(param_1 + 100);
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  FUN_004ad860(param_1 + 0x5c);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004ad860(param_1 + 0x54);
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  FUN_004ad860(param_1 + 0x4c);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004ad860(param_1 + 0x44);
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004ad860(param_1 + 0x3c);
  (*(uint8_t*)((char*)&local_4+0)) = 9;
  FUN_004a9430((undefined4 *)param_1[0x36],param_1[0x38] - (int)param_1[0x36]);
  (*(uint8_t*)((char*)&local_4+0)) = 10;
  FUN_004a9430((undefined4 *)param_1[0xc],param_1[0xe] - (int)param_1[0xc]);
  puVar1 = (undefined4 *)param_1[8];
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0xb);
  if (puVar1 != (undefined4 *)0x0) {
    FUN_004aa6f0(puVar1,param_1[10] - (int)puVar1);
  }
  local_4 = 0xffffffff;
  FUN_004a4b70(param_1);
  ExceptionList = local_c;
  return;
}


/* 004a4fa0 size=219 */

void __fastcall FUN_004a4fa0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c91b4;
  local_c = ExceptionList;
  puVar1 = (undefined4 *)param_1[0x2e];
  local_4 = 2;
  ExceptionList = &local_c;
  if (puVar1 != (undefined4 *)0x0) {
    ExceptionList = &local_c;
    FUN_004aa6f0(puVar1,param_1[0x30] - (int)puVar1);
  }
  puVar1 = (undefined4 *)param_1[4];
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),3);
  if (puVar1 != (undefined4 *)0x0) {
    FUN_004aa6f0(puVar1,param_1[6] - (int)puVar1);
  }
  puVar1 = (undefined4 *)*param_1;
  iVar2 = param_1[2];
  local_4 = 4;
  if (puVar1 != (undefined4 *)0x0) {
    if (0x80 < (uint)(iVar2 - (int)puVar1)) {
      FUN_00430df0((undefined *)puVar1);
      ExceptionList = local_c;
      return;
    }
    FUN_004a94b0(&DAT_004ed050);
    *puVar1 = *(undefined4 *)(&DAT_004ec644 + ((iVar2 - (int)puVar1) - 1U >> 3) * 4);
    *(undefined4 **)(&DAT_004ec644 + ((iVar2 - (int)puVar1) - 1U >> 3) * 4) = puVar1;
    DAT_004ed050 = 0;
  }
  ExceptionList = local_c;
  return;
}


/* 004a5080 size=136 */

void __fastcall FUN_004a5080(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c91cb;
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


/* 004a5110 size=100 */

/* FUN_004a5110: lifted from original x86 -> lt_lifted.c */


/* 004a51c0 size=500 */

void __fastcall FUN_004a51c0(undefined4 *param_1)

{
  int *piVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c92a1;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_004cdb88;
  piVar1 = param_1 + 0x7c;
  local_4 = 5;
  if (param_1[0x7d] != 0) {
    FUN_004aa020(*(undefined4 **)(*piVar1 + 4));
    *(int *)(*piVar1 + 8) = *piVar1;
    *(undefined4 *)(*piVar1 + 4) = 0;
    *(int *)(*piVar1 + 0xc) = *piVar1;
    param_1[0x7d] = 0;
  }
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004a91b0(piVar1);
  piVar1 = param_1 + 0x79;
  (*(uint8_t*)((char*)&local_4+0)) = 6;
  if (param_1[0x7a] != 0) {
    FUN_004a9d40(*(undefined4 **)(*piVar1 + 4));
    *(int *)(*piVar1 + 8) = *piVar1;
    *(undefined4 *)(*piVar1 + 4) = 0;
    *(int *)(*piVar1 + 0xc) = *piVar1;
    param_1[0x7a] = 0;
  }
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  FUN_004a9120(piVar1);
  piVar1 = param_1 + 0x76;
  (*(uint8_t*)((char*)&local_4+0)) = 7;
  if (param_1[0x77] != 0) {
    FUN_004a9a20(*(undefined4 **)(*piVar1 + 4));
    *(int *)(*piVar1 + 8) = *piVar1;
    *(undefined4 *)(*piVar1 + 4) = 0;
    *(int *)(*piVar1 + 0xc) = *piVar1;
    param_1[0x77] = 0;
  }
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004a9090(piVar1);
  piVar1 = param_1 + 0x73;
  (*(uint8_t*)((char*)&local_4+0)) = 8;
  if (param_1[0x74] != 0) {
    FUN_004a96e0(*(undefined4 **)(*piVar1 + 4));
    *(int *)(*piVar1 + 8) = *piVar1;
    *(undefined4 *)(*piVar1 + 4) = 0;
    *(int *)(*piVar1 + 0xc) = *piVar1;
    param_1[0x74] = 0;
  }
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004a8f60(piVar1);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),9);
  FUN_004a9490((undefined4 *)param_1[0x70],param_1[0x72] - (int)param_1[0x70] >> 1);
  *param_1 = &PTR_FUN_004cdb78;
  local_4 = 0x10;
  FUN_004ad860(param_1 + 100);
  (*(uint8_t*)((char*)&local_4+0)) = 0xf;
  FUN_004ad860(param_1 + 0x5c);
  (*(uint8_t*)((char*)&local_4+0)) = 0xe;
  FUN_004ad860(param_1 + 0x54);
  (*(uint8_t*)((char*)&local_4+0)) = 0xd;
  FUN_004ad860(param_1 + 0x4c);
  (*(uint8_t*)((char*)&local_4+0)) = 0xc;
  FUN_004ad860(param_1 + 0x44);
  (*(uint8_t*)((char*)&local_4+0)) = 0xb;
  FUN_004ad860(param_1 + 0x3c);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),10);
  FUN_004a4fa0(param_1 + 8);
  local_4 = 0xffffffff;
  FUN_004a4b70(param_1);
  ExceptionList = local_c;
  return;
}


/* 004a53c0 size=30 */

undefined4 * __thiscall FUN_004a53c0(void *this,byte param_1)

{
  FUN_004a51c0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004a53e0 size=167 */

void __fastcall FUN_004a53e0(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  void **ppvVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c92c0;
  local_c = ExceptionList;
  local_4 = 0;
  ppvVar4 = &local_c;
  if (param_1[1] != 0) {
    puVar3 = *(undefined4 **)(*param_1 + 4);
    ExceptionList = &local_c;
    while (puVar3 != (undefined4 *)0x0) {
      FUN_004a96e0((undefined4 *)puVar3[3]);
      puVar1 = (undefined4 *)puVar3[2];
      FUN_004a9450(puVar3,1);
      puVar3 = puVar1;
    }
    *(int *)(*param_1 + 8) = *param_1;
    *(undefined4 *)(*param_1 + 4) = 0;
    *(int *)(*param_1 + 0xc) = *param_1;
    param_1[1] = 0;
    ppvVar4 = ExceptionList;
  }
  ExceptionList = ppvVar4;
  piVar2 = (int *)*param_1;
  local_4 = 1;
  if (piVar2 != (int *)0x0) {
    FUN_004a94b0(&DAT_004ed050);
    *piVar2 = (int)DAT_004ec64c;
    DAT_004ed050 = 0;
    DAT_004ec64c = piVar2;
  }
  ExceptionList = local_c;
  return;
}


/* 004a5490 size=176 */

void __fastcall FUN_004a5490(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  void **ppvVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c92e0;
  local_c = ExceptionList;
  local_4 = 0;
  ppvVar4 = &local_c;
  if (param_1[1] != 0) {
    puVar3 = *(undefined4 **)(*param_1 + 4);
    ExceptionList = &local_c;
    while (puVar3 != (undefined4 *)0x0) {
      FUN_004a9a20((undefined4 *)puVar3[3]);
      puVar1 = (undefined4 *)puVar3[2];
      FUN_004aba90(puVar3 + 4,0);
      FUN_004a9470(puVar3,1);
      puVar3 = puVar1;
    }
    *(int *)(*param_1 + 8) = *param_1;
    *(undefined4 *)(*param_1 + 4) = 0;
    *(int *)(*param_1 + 0xc) = *param_1;
    param_1[1] = 0;
    ppvVar4 = ExceptionList;
  }
  ExceptionList = ppvVar4;
  piVar2 = (int *)*param_1;
  local_4 = 1;
  if (piVar2 != (int *)0x0) {
    FUN_004a94b0(&DAT_004ed050);
    *piVar2 = (int)DAT_004ec654;
    DAT_004ed050 = 0;
    DAT_004ec654 = piVar2;
  }
  ExceptionList = local_c;
  return;
}


/* 004a5540 size=176 */

void __fastcall FUN_004a5540(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  void **ppvVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9300;
  local_c = ExceptionList;
  local_4 = 0;
  ppvVar4 = &local_c;
  if (param_1[1] != 0) {
    puVar3 = *(undefined4 **)(*param_1 + 4);
    ExceptionList = &local_c;
    while (puVar3 != (undefined4 *)0x0) {
      FUN_004a9d40((undefined4 *)puVar3[3]);
      puVar1 = (undefined4 *)puVar3[2];
      FUN_004abab0(puVar3 + 4,0);
      FUN_004a9450(puVar3,1);
      puVar3 = puVar1;
    }
    *(int *)(*param_1 + 8) = *param_1;
    *(undefined4 *)(*param_1 + 4) = 0;
    *(int *)(*param_1 + 0xc) = *param_1;
    param_1[1] = 0;
    ppvVar4 = ExceptionList;
  }
  ExceptionList = ppvVar4;
  piVar2 = (int *)*param_1;
  local_4 = 1;
  if (piVar2 != (int *)0x0) {
    FUN_004a94b0(&DAT_004ed050);
    *piVar2 = (int)DAT_004ec64c;
    DAT_004ed050 = 0;
    DAT_004ec64c = piVar2;
  }
  ExceptionList = local_c;
  return;
}


/* 004a55f0 size=1143 */

/* FUN_004a55f0: lifted from original x86 -> lt_lifted.c */


/* 004a5b30 size=208 */

void FUN_004a5b30(char *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  undefined1 local_125;
  char *local_124;
  undefined1 *local_120;
  undefined1 local_11c [4];
  undefined **local_118 [3];
  char local_10c [255];
  undefined1 local_d;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9391;
  pvStack_c = ExceptionList;
  local_4 = 0;
  local_124 = (char *)0x0;
  local_120 = (undefined1 *)0x0;
  ExceptionList = &pvStack_c;
  FUN_004a93e0(local_11c,&local_125,0);
  uVar2 = 0xffffffff;
  pcVar3 = param_1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004a9380(&local_124,(uint)(param_1 + (~uVar2 - 1) + (1 - (int)param_1)));
  local_120 = (undefined1 *)
              FUN_004a5c10((undefined4 *)param_1,(int)(param_1 + (~uVar2 - 1)),
                           (undefined4 *)local_124);
  *local_120 = 0;
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
  FUN_004bcc6d(local_118);
  local_118[0] = &PTR_FUN_004cdba4;
  _strncpy(local_10c,local_124,0x100);
  local_d = 0;
  local_118[0] = &PTR_FUN_004cdb98;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_118,&DAT_004d0380);
}


/* 004a5c10 size=33 */

int __cdecl FUN_004a5c10(undefined4 *param_1,int param_2,undefined4 *param_3)

{
  FUN_004bab10(param_3,param_1,param_2 - (int)param_1);
  return (param_2 - (int)param_1) + (int)param_3;
}


/* 004a5cb0 size=30 */

exception * __thiscall FUN_004a5cb0(void *this,byte param_1)

{
  exception__dtor_exception(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004a5d20 size=23 */

void FUN_004a5d20(void)

{
  FUN_004b0850(&DAT_004ec480,(undefined4 *)&DAT_004de18c,0x331,'\0');
  return;
}


/* 004a5d40 size=12 */

void FUN_004a5d40(void)

{
  FUN_004b9cf5(&LAB_004a5d50);
  return;
}


/* 004a5d70 size=252 */

void __fastcall FUN_004a5d70(undefined4 *param_1)

{
  undefined4 *puVar1;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_004c9422;
  local_c = ExceptionList;
  local_4 = 5;
  ExceptionList = &local_c;
  FUN_004ad860(param_1 + 0x5c);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004ad860(param_1 + 0x54);
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  FUN_004ad860(param_1 + 0x4c);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004ad860(param_1 + 0x44);
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004ad860(param_1 + 0x3c);
  local_4 = (uint)(*(uint32_t*)((char*)&local_4+1)) << 8;
  FUN_004ad860(param_1 + 0x34);
  puVar1 = (undefined4 *)param_1[0x2e];
  local_4 = 8;
  if (puVar1 != (undefined4 *)0x0) {
    FUN_004aa6f0(puVar1,param_1[0x30] - (int)puVar1);
  }
  puVar1 = (undefined4 *)param_1[4];
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),9);
  if (puVar1 != (undefined4 *)0x0) {
    FUN_004aa6f0(puVar1,param_1[6] - (int)puVar1);
  }
  puVar1 = (undefined4 *)*param_1;
  local_4 = 10;
  if (puVar1 != (undefined4 *)0x0) {
    FUN_004aa6f0(puVar1,param_1[2] - (int)puVar1);
  }
  ExceptionList = local_c;
  return;
}


/* 004a5e70 size=80 */

int * __thiscall FUN_004a5e70(void *this,int *param_1)

{
  int iVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)((int)this + 8));
  iVar2 = *(int *)((int)this + 0x4c);
  iVar1 = 1;
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    InterlockedIncrement((LONG *)(iVar2 + 4));
  }
  *param_1 = iVar2;
  do {
    LeaveCriticalSection((LPCRITICAL_SECTION)((int)this + 8));
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return param_1;
}


/* 004a5ec0 size=30 */

undefined4 * __thiscall FUN_004a5ec0(void *this,byte param_1)

{
  FUN_004a4d40(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004a5ee0 size=167 */

void __fastcall FUN_004a5ee0(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  void **ppvVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9440;
  local_c = ExceptionList;
  local_4 = 0;
  ppvVar4 = &local_c;
  if (param_1[1] != 0) {
    puVar3 = *(undefined4 **)(*param_1 + 4);
    ExceptionList = &local_c;
    while (puVar3 != (undefined4 *)0x0) {
      FUN_004aa020((undefined4 *)puVar3[3]);
      puVar1 = (undefined4 *)puVar3[2];
      FUN_004a9450(puVar3,1);
      puVar3 = puVar1;
    }
    *(int *)(*param_1 + 8) = *param_1;
    *(undefined4 *)(*param_1 + 4) = 0;
    *(int *)(*param_1 + 0xc) = *param_1;
    param_1[1] = 0;
    ppvVar4 = ExceptionList;
  }
  ExceptionList = ppvVar4;
  piVar2 = (int *)*param_1;
  local_4 = 1;
  if (piVar2 != (int *)0x0) {
    FUN_004a94b0(&DAT_004ed050);
    *piVar2 = (int)DAT_004ec64c;
    DAT_004ed050 = 0;
    DAT_004ec64c = piVar2;
  }
  ExceptionList = local_c;
  return;
}


/* 004a5f90 size=16 */

int __thiscall FUN_004a5f90(void *this,void *param_1)

{
  FUN_004a5fa0(*(void **)((int)this + 0x10),param_1);
  return;
}


/* 004a5fa0 size=72 */

/* FUN_004a5fa0: lifted from original x86 -> lt_lifted.c */


/* 004a5ff0 size=717 */

/* FUN_004a5ff0: lifted from original x86 -> lt_lifted.c */


/* 004a62c0 size=30 */

undefined4 * __thiscall FUN_004a62c0(void *this,byte param_1)

{
  FUN_004a62e0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004a62e0 size=139 */

void __fastcall FUN_004a62e0(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c94fc;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_004cdbcc;
  local_4 = 2;
  FUN_004a9430((undefined4 *)param_1[0x41a],param_1[0x41c] - (int)param_1[0x41a]);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),3);
  FUN_004a9430((undefined4 *)param_1[0x417],param_1[0x419] - (int)param_1[0x417]);
  *param_1 = &PTR_LAB_004cdb70;
  ExceptionList = local_c;
  return;
}


/* 004a63a0 size=239 */

void __fastcall FUN_004a63a0(LONG *param_1)

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


/* 004a6490 size=7 */

int __fastcall FUN_004a6490(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}


/* 004a64a0 size=89 */

undefined4 * __thiscall FUN_004a64a0(void *this,undefined4 *param_1,uint param_2)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9518;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004a4a50(this,param_1,param_2);
  local_4 = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  FUN_004b07a0((undefined4 *)((int)this + 0x20));
  *(undefined ***)this = &PTR_FUN_004cdb78;
  ExceptionList = local_c;
  return this;
}


/* 004a6500 size=124 */

undefined4 * __fastcall FUN_004a6500(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c956d;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  local_4 = 0;
  FUN_004b01b0((int)(param_1 + 2));
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004b01b0((int)(param_1 + 0x42d));
  param_1[0x859] = 0;
  param_1[0x85a] = 0;
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),4);
  FUN_004a6580((int)param_1);
  *(undefined1 *)((int)param_1 + 0x2161) = 1;
  ExceptionList = local_c;
  return param_1;
}


/* 004a6580 size=11 */

void __fastcall FUN_004a6580(int param_1)

{
  *(undefined4 *)(param_1 + 0x216c) = 0;
  return;
}


/* 004a6590 size=732 */

undefined4 __thiscall FUN_004a6590(void *this,undefined4 *param_1,int *param_2)

{
  void *pvVar1;
  char cVar2;
  ushort uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 uVar6;
  LONG LVar7;
  int *this_00;
  undefined4 *puVar8;
  uint uVar9;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puVar8 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c95f4;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  uVar3 = FUN_004acf30(param_1);
  uVar9 = (uint)uVar3;
  iVar5 = *(int *)this;
  puVar4 = (undefined4 *)ReadBuffer_4acc20(puVar8,uVar9);
  FUN_004b1180((void *)(iVar5 + 0x18),&param_1,puVar4,uVar9);
  local_4 = 0;
  if (param_1 == (undefined4 *)0x0) {
    ExceptionList = local_c;
    return 0x186b7;
  }
  uVar9 = (uint)(byte)((char *)param_1[2])[1] << 8 | (uint)(ushort)(short)*(char *)param_1[2];
  if (param_1[3] - 2 < uVar9) {
    local_4 = 0xffffffff;
    FUN_0048a6a0(param_1);
    ExceptionList = local_c;
    return 0x186b8;
  }
  FUN_004b0600((void *)((int)this + 8),8);
  if (param_1 == (undefined4 *)0x0) {
    iVar5 = 0;
  }
  else {
    iVar5 = param_1[2];
  }
  uVar6 = FUN_004b0250((void *)((int)this + 0x10b4),(undefined4 *)(iVar5 + 2),uVar9);
  puVar4 = param_1;
  if ((char)uVar6 == '\0') {
    local_4 = 0xffffffff;
    if (((param_1 != (undefined4 *)0x0) && (LVar7 = InterlockedDecrement(param_1 + 1), LVar7 < 1))
       && (puVar4 != (undefined4 *)0x0)) {
      (**(code **)*puVar4)(1);
    }
    ExceptionList = local_c;
    return 0x186b9;
  }
  uVar3 = FUN_004acf30(puVar8);
  uVar9 = (uint)uVar3;
  if (*(char *)((int)this + 0x2161) == '\0') {
    this_00 = (int *)FUN_00430de0(0x1c8);
    (*(uint8_t*)((char*)&local_4+0)) = 8;
    if (this_00 != (int *)0x0) {
      puVar8 = (undefined4 *)ReadBuffer_4acc20(puVar8,uVar9);
      FUN_004a64a0(this_00,puVar8,uVar9);
      (*(uint8_t*)((char*)&local_4+0)) = 9;
      this_00[0x70] = 0;
      *(undefined2 *)(this_00 + 0x71) = 0;
      *this_00 = (int)&PTR_FUN_004cdbbc;
      FUN_004a4be0(this_00);
      goto LAB_004a6792;
    }
  }
  else {
    this_00 = (int *)FUN_00430de0(0x200);
    (*(uint8_t*)((char*)&local_4+0)) = 1;
    if (this_00 != (int *)0x0) {
      puVar8 = (undefined4 *)ReadBuffer_4acc20(puVar8,uVar9);
      FUN_004a64a0(this_00,puVar8,uVar9);
      (*(uint8_t*)((char*)&local_4+0)) = 2;
      FUN_004a80d0(this_00 + 0x70);
      (*(uint8_t*)((char*)&local_4+0)) = 3;
      FUN_004a8300(this_00 + 0x73);
      (*(uint8_t*)((char*)&local_4+0)) = 4;
      FUN_004a83a0(this_00 + 0x76);
      (*(uint8_t*)((char*)&local_4+0)) = 5;
      FUN_004a8440(this_00 + 0x79);
      (*(uint8_t*)((char*)&local_4+0)) = 6;
      FUN_004a84e0(this_00 + 0x7c);
      (*(uint8_t*)((char*)&local_4+0)) = 7;
      *this_00 = (int)&PTR_FUN_004cdb88;
      FUN_004a4be0(this_00);
      goto LAB_004a6792;
    }
  }
  this_00 = (int *)0x0;
LAB_004a6792:
  local_4 = (uint)(*(uint32_t*)((char*)&local_4+1)) << 8;
  FUN_00414150((undefined4 *)((int)this + 0x2164),this_00);
  puVar8 = param_1;
  pvVar1 = *(void **)((int)this + 0x2164);
  if (*(char *)((int)pvVar1 + 0x18) == '\0') {
    local_4 = 0xffffffff;
    if (((param_1 != (undefined4 *)0x0) && (LVar7 = InterlockedDecrement(param_1 + 1), LVar7 < 1))
       && (puVar8 != (undefined4 *)0x0)) {
      (**(code **)*puVar8)(1);
    }
    uVar6 = 0x186ba;
  }
  else {
    cVar2 = FUN_004a5f90(*(void **)this,pvVar1);
    puVar8 = param_1;
    if (cVar2 == '\0') {
      local_4 = 0xffffffff;
      if (((param_1 != (undefined4 *)0x0) && (LVar7 = InterlockedDecrement(param_1 + 1), LVar7 < 1))
         && (puVar8 != (undefined4 *)0x0)) {
        (**(code **)*puVar8)(1);
      }
      uVar6 = 0x186bb;
    }
    else {
      uVar6 = FUN_004a6870(this,param_2);
      puVar8 = param_1;
      local_4 = 0xffffffff;
      if (((param_1 != (undefined4 *)0x0) && (LVar7 = InterlockedDecrement(param_1 + 1), LVar7 < 1))
         && (puVar8 != (undefined4 *)0x0)) {
        (**(code **)*puVar8)(1);
      }
    }
  }
  ExceptionList = local_c;
  return uVar6;
}


/* 004a6870 size=538 */

undefined4 __thiscall FUN_004a6870(void *this,int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  LONG LVar3;
  undefined2 extraout_var;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *local_3c;
  undefined4 *local_38;
  undefined4 local_34 [3];
  int local_28;
  int local_24;
  undefined4 local_20 [5];
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9620;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)((int)this + 0x216c) = 2;
  FUN_004ad1e0(local_20,*(undefined1 *)((int)this + 0x2160),1);
  local_4 = 0;
  FUN_004ad350(local_20,0xcb);
  FUN_004ad350(local_20,0x34);
  FUN_004ad1e0(local_34,0,1);
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004ad340(local_34,CONCAT22(extraout_var,
                                 *(short *)((int)this + 0x210c) - *(short *)((int)this + 0x2108)));
  FUN_004ad2f0(local_34,*(undefined4 **)((int)this + 0x2108),
               *(int *)((int)this + 0x210c) - (int)*(undefined4 **)((int)this + 0x2108));
  FUN_004ad2f0(local_34,*(undefined4 **)((int)this + 0x105c),
               *(int *)((int)this + 0x1060) - (int)*(undefined4 **)((int)this + 0x105c));
  FUN_004b0cf0((void *)(*(int *)((int)this + 0x2164) + 0x20),&local_3c,local_24,local_28);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  if (local_3c == (undefined4 *)0x0) {
    local_4 = (uint)(*(uint32_t*)((char*)&local_4+1)) << 8;
    FUN_004ad230(local_34);
    local_4 = 0xffffffff;
    FUN_004ad230(local_20);
    ExceptionList = local_c;
    return 0x186bc;
  }
  FUN_004ad340(local_20,local_3c[3]);
  if (local_3c == (undefined4 *)0x0) {
    uVar4 = 0;
    puVar5 = (undefined4 *)0x0;
  }
  else {
    uVar4 = local_3c[3];
    puVar5 = (undefined4 *)local_3c[2];
  }
  FUN_004ad2f0(local_20,puVar5,uVar4);
  piVar2 = (int *)FUN_004ad420(local_20,&local_38,'\x01');
  puVar5 = (undefined4 *)*piVar2;
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  puVar1 = (undefined4 *)*param_1;
  if (puVar1 != puVar5) {
    if (puVar1 != (undefined4 *)0x0) {
      LVar3 = InterlockedDecrement(puVar1 + 1);
      if ((LVar3 < 1) && (puVar1 != (undefined4 *)0x0)) {
        (**(code **)*puVar1)(1);
      }
    }
    if (puVar5 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      InterlockedIncrement(puVar5 + 1);
    }
    *param_1 = (int)puVar5;
  }
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  if (local_38 != (undefined4 *)0x0) {
    LVar3 = InterlockedDecrement(local_38 + 1);
    if ((LVar3 < 1) && (local_38 != (undefined4 *)0x0)) {
      (**(code **)*local_38)(1);
    }
  }
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  if (local_3c != (undefined4 *)0x0) {
    LVar3 = InterlockedDecrement(local_3c + 1);
    if ((LVar3 < 1) && (local_3c != (undefined4 *)0x0)) {
      (**(code **)*local_3c)(1);
    }
  }
  local_4 = (uint)(*(uint32_t*)((char*)&local_4+1)) << 8;
  FUN_004ad230(local_34);
  local_4 = 0xffffffff;
  FUN_004ad230(local_20);
  ExceptionList = local_c;
  return 0;
}


/* 004a6a90 size=612 */

/* FUN_004a6a90: lifted from original x86 -> lt_lifted.c */


/* 004a6d00 size=598 */

undefined4 * __thiscall FUN_004a6d00(void *this,undefined4 *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 local_1c;
  int local_18;
  void *local_14;
  int *local_10;
  undefined4 *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puVar3 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c967e;
  local_c = ExceptionList;
  puVar7 = param_1;
  puVar8 = this;
  ExceptionList = &local_c;
  for (iVar6 = 0x100; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar7 = param_1 + 0x100;
  puVar8 = (undefined4 *)((int)this + 0x400);
  for (iVar6 = 0x100; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar7 = param_1 + 0x200;
  puVar8 = (undefined4 *)((int)this + 0x800);
  for (iVar6 = 0x100; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar7 = param_1 + 0x300;
  puVar8 = (undefined4 *)((int)this + 0xc00);
  for (iVar6 = 0x100; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar7 = param_1 + 0x400;
  puVar8 = (undefined4 *)((int)this + 0x1000);
  for (iVar6 = 0x12; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  piVar1 = param_1 + 0x412;
  piVar2 = (int *)((int)this + 0x1048);
  local_14 = this;
  local_10 = piVar2;
  FUN_004a8710(&param_1);
  *piVar2 = 0;
  *(undefined4 *)((int)this + 0x104c) = 0;
  *(undefined4 *)((int)this + 0x1050) = 0;
  local_18 = puVar3[0x413];
  iVar6 = *piVar1;
  local_1c = (local_18 - iVar6) + 1;
  local_4 = 0;
  if (local_1c == 0) {
    FUN_004a5b30(s_basic_string_004de5c8);
  }
  else {
    iVar4 = FUN_004aa520(local_1c);
    *piVar2 = iVar4;
    *(int *)((int)this + 0x104c) = iVar4;
    *(uint *)((int)this + 0x1050) = iVar4 + local_1c;
  }
  puVar5 = (undefined1 *)FUN_004aca30(iVar6,(int)local_14,(undefined1 *)*piVar2);
  *(undefined1 **)((int)this + 0x104c) = puVar5;
  *puVar5 = 0;
  puVar7 = (undefined4 *)((int)this + 0x1054);
  local_c = puVar7;
  FUN_004a8710((int)&local_1c + 3);
  *puVar7 = 0;
  *(undefined4 *)((int)this + 0x1058) = 0;
  *(undefined4 *)((int)this + 0x105c) = 0;
  param_2 = puVar3[0x416];
  iVar6 = puVar3[0x415];
  FUN_004a9380(puVar7,(param_2 - iVar6) + 1);
  puVar5 = (undefined1 *)FUN_004aca30(iVar6,param_2,(undefined1 *)*puVar7);
  *(undefined1 **)((int)this + 0x1058) = puVar5;
  *puVar5 = 0;
  *(undefined4 *)((int)this + 0x1060) = puVar3[0x418];
  *(undefined4 *)((int)this + 0x1064) = puVar3[0x419];
  *(undefined4 *)((int)this + 0x1068) = puVar3[0x41a];
  *(undefined4 *)((int)this + 0x106c) = puVar3[0x41b];
  *(undefined4 *)((int)this + 0x1070) = puVar3[0x41c];
  *(undefined4 *)((int)this + 0x1074) = puVar3[0x41d];
  *(undefined4 *)((int)this + 0x1078) = puVar3[0x41e];
  *(undefined4 *)((int)this + 0x107c) = puVar3[0x41f];
  *(undefined4 *)((int)this + 0x1080) = puVar3[0x420];
  *(undefined4 *)((int)this + 0x1084) = puVar3[0x421];
  *(undefined4 *)((int)this + 0x1088) = puVar3[0x422];
  *(undefined4 *)((int)this + 0x108c) = puVar3[0x423];
  *(undefined4 *)((int)this + 0x1090) = puVar3[0x424];
  *(undefined4 *)((int)this + 0x1094) = puVar3[0x425];
  *(undefined4 *)((int)this + 0x1098) = puVar3[0x426];
  *(undefined4 *)((int)this + 0x109c) = puVar3[0x427];
  *(undefined4 *)((int)this + 0x10a0) = puVar3[0x428];
  *(undefined4 *)((int)this + 0x10a4) = puVar3[0x429];
  *(undefined1 *)((int)this + 0x10a8) = *(undefined1 *)(puVar3 + 0x42a);
  ExceptionList = puStack_8;
  return this;
}


/* 004a6f60 size=389 */

/* FUN_004a6f60: lifted from original x86 -> lt_lifted.c */


/* 004a70f0 size=277 */

int __thiscall FUN_004a70f0(void *this,undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  LONG LVar3;
  int iVar4;
  int iVar5;
  undefined1 auStackY_b4 [128];
  undefined4 local_20 [3];
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004c96c0;
  local_10 = ExceptionList;
  local_14 = auStackY_b4 + 0x88;
  puVar1 = (undefined4 *)*param_3;
  ExceptionList = &local_10;
  puVar2 = auStackY_b4 + 0x88;
  if (puVar1 != (undefined4 *)0x0) {
    ExceptionList = &local_10;
    LVar3 = InterlockedDecrement(puVar1 + 1);
    if ((LVar3 < 1) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
    *param_3 = 0;
    puVar2 = local_14;
  }
  local_14 = puVar2;
  local_8 = 0;
  FUN_004acbe0(local_20,param_1,param_2);
  iVar4 = FUN_004acf40(local_20);
  iVar5 = FUN_004acf40(local_20);
  if (iVar4 != 0xcb) {
    ExceptionList = local_10;
    return 0x186c0;
  }
  if (iVar5 == 0x35) {
    iVar4 = FUN_004a6a90(this,local_20);
    ExceptionList = local_10;
    return iVar4;
  }
  if (iVar5 != 0x33) {
    ExceptionList = local_10;
    return 0x186c2;
  }
  if (*(int *)((int)this + 0x216c) == 1) {
    iVar4 = FUN_004a6590(this,local_20,param_3);
    ExceptionList = local_10;
    return iVar4;
  }
  ExceptionList = local_10;
  return 0x186c1;
}


/* 004a7230 size=106 */

undefined4 * __fastcall FUN_004a7230(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c96e3;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  local_4 = 0;
  FUN_004b01b0((int)(param_1 + 2));
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
  FUN_004b01b0((int)(param_1 + 0x42d));
  param_1[0x859] = 0;
  param_1[0x85a] = 0;
  param_1[0x85c] = 0;
  *(undefined1 *)(param_1 + 0x85b) = 1;
  ExceptionList = local_c;
  return param_1;
}


/* 004a72a0 size=145 */

void __thiscall FUN_004a72a0(void *this,undefined4 *param_1,undefined1 param_2)

{
  undefined4 *puVar1;
  LONG LVar2;
  
  puVar1 = *(undefined4 **)this;
  if (puVar1 == param_1) {
    *(undefined4 *)((int)this + 0x2170) = 1;
    *(undefined1 *)((int)this + 0x2160) = param_2;
    return;
  }
  if (puVar1 != (undefined4 *)0x0) {
    LVar2 = InterlockedDecrement(puVar1 + 1);
    if ((LVar2 < 1) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
  }
  if (param_1 == (undefined4 *)0x0) {
    *(undefined4 *)this = 0;
    *(undefined1 *)((int)this + 0x2160) = param_2;
    *(undefined4 *)((int)this + 0x2170) = 1;
    return;
  }
  InterlockedIncrement(param_1 + 1);
  *(undefined4 **)this = param_1;
  *(undefined1 *)((int)this + 0x2160) = param_2;
  *(undefined4 *)((int)this + 0x2170) = 1;
  return;
}


/* 004a7340 size=658 */

undefined4 __thiscall FUN_004a7340(void *this,int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  LONG LVar4;
  undefined2 extraout_var;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *local_3c;
  undefined4 *local_38;
  undefined4 local_34 [5];
  undefined4 local_20 [3];
  int local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9720;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004ad1e0(local_34,*(undefined1 *)((int)this + 0x2160),1);
  local_4 = 0;
  FUN_004ad350(local_34,0xcb);
  FUN_004ad350(local_34,0x33);
  FUN_004b0600((void *)((int)this + 0x10b4),8);
  FUN_004ad1e0(local_20,0,1);
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004ad340(local_20,CONCAT22(extraout_var,
                                 *(short *)((int)this + 0x210c) - *(short *)((int)this + 0x2108)));
  FUN_004ad2f0(local_20,*(undefined4 **)((int)this + 0x2108),
               *(int *)((int)this + 0x210c) - (int)*(undefined4 **)((int)this + 0x2108));
  FUN_004b0cf0((void *)(*(int *)((int)this + 0x2164) + 0x20),&local_3c,local_10,local_14);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  if (local_3c == (undefined4 *)0x0) {
    local_4 = (uint)(*(uint32_t*)((char*)&local_4+1)) << 8;
    FUN_004ad230(local_20);
    local_4 = 0xffffffff;
    FUN_004ad230(local_34);
    ExceptionList = local_c;
    return 0x186cf;
  }
  FUN_004ad340(local_34,local_3c[3]);
  if (local_3c == (undefined4 *)0x0) {
    uVar5 = 0;
    puVar6 = (undefined4 *)0x0;
  }
  else {
    uVar5 = local_3c[3];
    puVar6 = (undefined4 *)local_3c[2];
  }
  FUN_004ad2f0(local_34,puVar6,uVar5);
  if (*(char *)((int)this + 0x216c) == '\0') {
    piVar2 = (int *)FUN_004a75e0(*(void **)(*(int *)this + 8),(int *)&local_38);
    (*(uint8_t*)((char*)&local_4+0)) = 4;
    FUN_004ad3e0(local_34,*piVar2,'\x02');
    puVar6 = local_38;
    (*(uint8_t*)((char*)&local_4+0)) = 2;
    if (local_38 == (undefined4 *)0x0) goto LAB_004a7504;
    iVar3 = InterlockedDecrement(local_38 + 1);
  }
  else {
    piVar2 = (int *)FUN_004a75e0(*(void **)(*(int *)this + 0xc),(int *)&local_38);
    (*(uint8_t*)((char*)&local_4+0)) = 3;
    FUN_004ad3e0(local_34,*piVar2,'\x02');
    puVar6 = local_38;
    (*(uint8_t*)((char*)&local_4+0)) = 2;
    if (local_38 == (undefined4 *)0x0) goto LAB_004a7504;
    iVar3 = InterlockedDecrement(local_38 + 1);
  }
  if ((iVar3 < 1) && (puVar6 != (undefined4 *)0x0)) {
    (**(code **)*puVar6)(1);
  }
LAB_004a7504:
  piVar2 = (int *)FUN_004ad420(local_34,&local_38,'\x01');
  puVar6 = (undefined4 *)*piVar2;
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  puVar1 = (undefined4 *)*param_1;
  if (puVar1 != puVar6) {
    if (((puVar1 != (undefined4 *)0x0) && (LVar4 = InterlockedDecrement(puVar1 + 1), LVar4 < 1)) &&
       (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
    if (puVar6 == (undefined4 *)0x0) {
      puVar6 = (undefined4 *)0x0;
    }
    else {
      InterlockedIncrement(puVar6 + 1);
    }
    *param_1 = (int)puVar6;
  }
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  if (((local_38 != (undefined4 *)0x0) && (LVar4 = InterlockedDecrement(local_38 + 1), LVar4 < 1))
     && (local_38 != (undefined4 *)0x0)) {
    (**(code **)*local_38)(1);
  }
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  if (((local_3c != (undefined4 *)0x0) && (LVar4 = InterlockedDecrement(local_3c + 1), LVar4 < 1))
     && (local_3c != (undefined4 *)0x0)) {
    (**(code **)*local_3c)(1);
  }
  local_4 = (uint)(*(uint32_t*)((char*)&local_4+1)) << 8;
  FUN_004ad230(local_20);
  local_4 = 0xffffffff;
  FUN_004ad230(local_34);
  ExceptionList = local_c;
  return 0;
}


/* 004a75e0 size=51 */

int __thiscall FUN_004a75e0(void *this,int *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)((int)this + 8);
  if (iVar1 == 0) {
    *param_1 = 0;
    return;
  }
  InterlockedIncrement((LONG *)(iVar1 + 4));
  *param_1 = iVar1;
  return;
}


/* 004a7620 size=598 */

undefined4 __thiscall FUN_004a7620(void *this,void *param_1,int *param_2)

{
  char cVar1;
  undefined1 uVar2;
  bool bVar3;
  ushort uVar4;
  uint uVar5;
  int *this_00;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 uStack_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c97a4;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  uStack_10 = this;
  cVar1 = FUN_004acf20(param_1);
  uVar2 = FUN_004acf20(param_1);
  (*(uint16_t*)((char*)&uStack_10+0)) = CONCAT11(uVar2,(undefined1)uStack_10);
  FUN_004acf30(param_1);
  if (cVar1 != '\x01') {
    ExceptionList = local_c;
    return 0x186ca;
  }
  if (((*(uint8_t*)((char*)&uStack_10+1)) != '\0') && ((*(uint8_t*)((char*)&uStack_10+1)) != '\x01')) {
    ExceptionList = local_c;
    return 0x186cb;
  }
  *(uint *)((int)this + 4) = 3 - (uint)((*(uint8_t*)((char*)&uStack_10+1)) == '\x01');
  uVar4 = FUN_004acf30(param_1);
  uVar5 = (uint)uVar4;
  if (*(char *)((int)this + 0x216c) == '\0') {
    this_00 = (int *)FUN_00430de0(0x1c8);
    local_4 = 8;
    if (this_00 != (int *)0x0) {
      puVar6 = (undefined4 *)ReadBuffer_4acc20(param_1,uVar5);
      FUN_004a64a0(this_00,puVar6,uVar5);
      local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),9);
      this_00[0x70] = 0;
      *(undefined2 *)(this_00 + 0x71) = 0;
      *this_00 = (int)&PTR_FUN_004cdbbc;
      FUN_004a4be0(this_00);
      goto LAB_004a77cb;
    }
  }
  else {
    this_00 = (int *)FUN_00430de0(0x200);
    local_4 = 0;
    if (this_00 != (int *)0x0) {
      puVar6 = (undefined4 *)ReadBuffer_4acc20(param_1,uVar5);
      FUN_004a64a0(this_00,puVar6,uVar5);
      (*(uint8_t*)((char*)&local_4+0)) = 1;
      FUN_004a80d0(this_00 + 0x70);
      (*(uint8_t*)((char*)&local_4+0)) = 3;
      FUN_004a8e80(this_00 + 0x73,(undefined1 *)((int)&uStack_10 + 3));
      (*(uint8_t*)((char*)&local_4+0)) = 4;
      FUN_004a83a0(this_00 + 0x76);
      (*(uint8_t*)((char*)&local_4+0)) = 5;
      FUN_004a8440(this_00 + 0x79);
      (*(uint8_t*)((char*)&local_4+0)) = 6;
      FUN_004a84e0(this_00 + 0x7c);
      local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),7);
      *this_00 = (int)&PTR_FUN_004cdb88;
      FUN_004a4be0(this_00);
      goto LAB_004a77cb;
    }
  }
  this_00 = (int *)0x0;
LAB_004a77cb:
  puVar6 = (undefined4 *)((int)this + 0x2164);
  local_4 = 0xffffffff;
  FUN_00414150(puVar6,this_00);
  if (*(char *)((int)*puVar6 + 0x18) == '\0') {
    ExceptionList = local_c;
    return 0x186cc;
  }
  bVar3 = FUN_004a4ce0((void *)*puVar6,*(int *)(*(int *)this + 0x1b8));
  if (bVar3) {
    ExceptionList = local_c;
    return 0x186cd;
  }
  cVar1 = FUN_004a5f90(*(void **)this,(void *)*puVar6);
  if (cVar1 == '\0') {
    ExceptionList = local_c;
    return 0x186ce;
  }
  uVar7 = FUN_004a7340(this,param_2);
  ExceptionList = local_c;
  return uVar7;
}


/* 004a7880 size=804 */

/* FUN_004a7880: lifted from original x86 -> lt_lifted.c */


/* 004a7bb0 size=390 */

undefined4 __thiscall FUN_004a7bb0(void *this,undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  ushort uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  char *pcVar5;
  LONG LVar6;
  uint uVar7;
  char *pcVar8;
  bool bVar9;
  int local_18;
  int local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puVar3 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9818;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  uVar2 = FUN_004acf30(param_1);
  uVar7 = (uint)uVar2;
  iVar1 = *(int *)this;
  puVar3 = (undefined4 *)ReadBuffer_4acc20(puVar3,uVar7);
  FUN_004b1180((void *)(iVar1 + 0x18),&param_1,puVar3,uVar7);
  local_4 = 0;
  if (param_1 == (undefined4 *)0x0) {
    uVar4 = 0x186d0;
  }
  else {
    FUN_004acbe0(&local_18,param_1[2],param_1[3]);
    uVar2 = FUN_004acf30(&local_18);
    uVar7 = (uint)uVar2;
    pcVar8 = *(char **)((int)this + 0x2108);
    if (uVar7 == *(int *)((int)this + 0x210c) - (int)pcVar8) {
      pcVar5 = (char *)ReadBuffer_4acc20(&local_18,uVar7);
      bVar9 = true;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        bVar9 = *pcVar8 == *pcVar5;
        pcVar8 = pcVar8 + 1;
        pcVar5 = pcVar5 + 1;
      } while (bVar9);
      if (bVar9) {
        uVar4 = FUN_004b0250((void *)((int)this + 8),(undefined4 *)(local_14 + local_18),
                             local_10 - local_18);
        puVar3 = param_1;
        if ((char)uVar4 == '\0') {
          local_4 = 0xffffffff;
          if (((param_1 != (undefined4 *)0x0) &&
              (LVar6 = InterlockedDecrement(param_1 + 1), LVar6 < 1)) &&
             (puVar3 != (undefined4 *)0x0)) {
            (**(code **)*puVar3)(1);
          }
          ExceptionList = local_c;
          return 0x186d1;
        }
        uVar4 = FUN_004a7880(this,0);
        puVar3 = param_1;
        local_4 = 0xffffffff;
        if (((param_1 != (undefined4 *)0x0) &&
            (LVar6 = InterlockedDecrement(param_1 + 1), LVar6 < 1)) && (puVar3 != (undefined4 *)0x0)
           ) {
          (**(code **)*puVar3)(1);
        }
        ExceptionList = local_c;
        return uVar4;
      }
    }
    puVar3 = param_1;
    local_4 = 0xffffffff;
    if (((param_1 != (undefined4 *)0x0) && (LVar6 = InterlockedDecrement(param_1 + 1), LVar6 < 1))
       && (puVar3 != (undefined4 *)0x0)) {
      (**(code **)*puVar3)(1);
    }
    uVar4 = 0x186d2;
  }
  ExceptionList = local_c;
  return uVar4;
}


/* 004a7d40 size=328 */

undefined4 __thiscall FUN_004a7d40(void *this,undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  LONG LVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 auStackY_b8 [128];
  undefined4 local_24 [3];
  void *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004c9830;
  local_10 = ExceptionList;
  local_14 = auStackY_b8 + 0x88;
  puVar1 = (undefined4 *)*param_3;
  ExceptionList = &local_10;
  local_18 = this;
  puVar2 = auStackY_b8 + 0x88;
  if (puVar1 != (undefined4 *)0x0) {
    ExceptionList = &local_10;
    LVar3 = InterlockedDecrement(puVar1 + 1);
    if ((LVar3 < 1) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
    *param_3 = 0;
    puVar2 = local_14;
  }
  local_14 = puVar2;
  if (*(int *)((int)this + 0x2170) == 0) {
    ExceptionList = local_10;
    return 0x186c4;
  }
  local_8 = 0;
  FUN_004acbe0(local_24,param_1,param_2);
  iVar4 = FUN_004acf40(local_24);
  iVar5 = FUN_004acf40(local_24);
  if (iVar4 != 0xcb) {
    ExceptionList = local_10;
    return 0x186c5;
  }
  if (iVar5 == 0x32) {
    if (*(int *)((int)this + 0x2170) == 1) {
      FUN_004a7620(this,local_24,param_3);
      *(undefined4 *)((int)this + 0x2170) = 2;
      uVar6 = FUN_004a7e9e();
      return uVar6;
    }
    ExceptionList = local_10;
    return 0x186c6;
  }
  if (iVar5 != 0x34) {
    ExceptionList = local_10;
    return 0x186c8;
  }
  if (*(int *)((int)this + 0x2170) == 2) {
    FUN_004a7bb0(this,local_24,param_3);
    uVar6 = FUN_004a7e9e();
    return uVar6;
  }
  ExceptionList = local_10;
  return 0x186c7;
}


/* 004a7e9e size=41 */

int FUN_004a7e9e(void)

{
  int unaff_EBP;
  int unaff_ESI;
  void *unaff_EDI;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (unaff_ESI != 0) {
    FUN_004a7880(unaff_EDI,unaff_ESI);
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}


/* 004a7ed0 size=57 */

undefined4 * __thiscall FUN_004a7ed0(void *this,undefined4 *param_1)

{
  FUN_004bcc6d(this);
  *(undefined ***)this = &PTR_FUN_004cdba4;
  _strncpy((char *)((int)this + 0xc),(char *)*param_1,0x100);
  *(undefined1 *)((int)this + 0x10b) = 0;
  *(undefined ***)this = &PTR_FUN_004cdb98;
  return this;
}


/* 004a7f10 size=136 */

void __fastcall FUN_004a7f10(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c984b;
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


/* 004a7fa0 size=108 */

undefined4 * __thiscall FUN_004a7fa0(void *this,undefined4 *param_1)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  
  if (param_1 != this) {
    puVar1 = (undefined1 *)param_1[1];
    puVar4 = *(undefined4 **)this;
    for (puVar3 = (undefined1 *)*param_1; puVar3 != puVar1; puVar3 = puVar3 + 1) {
      if (puVar4 == *(undefined4 **)((int)this + 4)) {
        if (puVar3 != puVar1) {
          FUN_004ac460(this,puVar3,puVar1);
          return this;
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
      return this;
    }
  }
  return this;
}


