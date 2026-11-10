/* lithtech.exe decompilation - unnamed_00460000 */
#include "ghidra_types.h"

/* 004602e0 size=38 */

undefined4 __cdecl FUN_004602e0(int param_1)

{
  if (((*(char *)(param_1 + 0xbc) == '\x02') || (*(char *)(param_1 + 0xbc) == '\t')) &&
     ((*(uint *)(param_1 + 0x88) & 0x4000) == 0)) {
    return 1;
  }
  return 0;
}


/* 00460310 size=192 */

bool __cdecl
FUN_00460310(int param_1,int param_2,float *param_3,float *param_4,float *param_5,float *param_6,
            float param_7,undefined4 *param_8)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = FUN_0045f6e0(param_3,param_4,param_5,param_6,param_7);
  if (iVar1 == 0) {
    return false;
  }
  if (((*(char *)(param_1 + 0xbc) != '\x02') && (*(char *)(param_1 + 0xbc) != '\t')) ||
     ((*(uint *)(param_1 + 0x88) & 0x4000) != 0)) {
    if (((*(char *)(param_2 + 0xbc) != '\x02') && (*(char *)(param_2 + 0xbc) != '\t')) ||
       ((*(uint *)(param_2 + 0x88) & 0x4000) != 0)) goto LAB_004603b8;
    param_1 = param_2;
    param_5 = param_3;
    param_6 = param_4;
  }
  if (param_1 != 0) {
    if (param_8 != (undefined4 *)0x0) {
      *param_8 = 1;
    }
    puVar2 = (uint *)(**(code **)(**(int **)(param_1 + 0x1b8) + 4))();
    iVar1 = FUN_0041b6c0(puVar2,param_5,param_6);
    return iVar1 != 0;
  }
LAB_004603b8:
  if (param_8 != (undefined4 *)0x0) {
    *param_8 = 0;
  }
  return true;
}


/* 004603d0 size=160 */

void __cdecl FUN_004603d0(int *param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  puVar1 = (undefined4 *)(**(code **)(*param_1 + 4))();
  puVar1 = (undefined4 *)*puVar1;
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[5] = 0;
  uStack_c = 0;
  uStack_8 = 0;
  uStack_4 = 0;
  if ((*(uint *)(param_2 + 0x88) & 0x10000) != 0) {
    (**(code **)(*param_1 + 8))(param_2,param_3,&uStack_c,0);
  }
  if ((*(uint *)(param_3 + 0x88) & 0x10000) != 0) {
    (**(code **)(*param_1 + 8))(param_3,param_2,&uStack_c,0);
  }
  if ((*(uint *)(param_2 + 0x88) & 0x20000000) != 0) {
    (**(code **)(*param_1 + 0xc))(param_3,param_2);
  }
  if ((*(uint *)(param_3 + 0x88) & 0x20000000) != 0) {
    (**(code **)(*param_1 + 0xc))(param_2,param_3);
  }
  return;
}


/* 00460470 size=1718 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00460470: lifted from original x86 -> lt_lifted.c */


/* 00460b30 size=38 */

void __thiscall
FUN_00460b30(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)this = param_1;
  *(undefined4 *)((int)this + 4) = param_2;
  *(undefined4 *)((int)this + 8) = param_3;
  *(undefined4 *)((int)this + 0xc) = param_4;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  return;
}


/* 00460b60 size=649 */

bool __cdecl
FUN_00460b60(int param_1,undefined4 param_2,int *param_3,void *param_4,undefined4 *param_5,
            float *param_6,undefined4 param_7,int param_8)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  undefined4 *puVar4;
  int iVar5;
  int *piVar6;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  int iStack_78;
  int iStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  undefined4 uStack_54;
  undefined4 uStack_50;
  int *local_4c;
  undefined4 uStack_48;
  undefined4 local_44;
  undefined4 uStack_40;
  int *piStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  uint uStack_14;
  void *pvStack_10;
  undefined4 uStack_c;
  undefined4 local_8;
  int local_4;
  
  local_8 = 0;
  local_4 = 0;
  if ((*(uint *)((int)param_4 + 0x88) & 0x200000) != 0) {
    return false;
  }
  local_4c = *(int **)(param_1 + 4);
  local_44 = *(undefined4 *)(param_1 + 0x18);
  puVar4 = (undefined4 *)(**(code **)(*local_4c + 4))();
  uStack_48 = *puVar4;
  uStack_38 = *param_5;
  uStack_40 = param_2;
  uStack_34 = param_5[1];
  uStack_30 = param_5[2];
  fStack_2c = *param_6;
  fStack_28 = param_6[1];
  piStack_3c = param_3;
  fStack_24 = param_6[2];
  uStack_20 = *(undefined4 *)((int)param_4 + 0x1a0);
  uStack_1c = *(undefined4 *)((int)param_4 + 0x1a4);
  uStack_18 = *(undefined4 *)((int)param_4 + 0x1a8);
  uStack_c = param_7;
  local_8 = *(undefined4 *)(param_1 + 100);
  uStack_14 = *(uint *)((int)param_4 + 0x88) >> 0x12 & 1;
  local_4 = param_1 + 0x68;
  pvStack_10 = param_4;
  collision_41c5f0((float *)&local_4c,&fStack_84);
  *param_6 = fStack_84;
  param_6[1] = fStack_80;
  param_6[2] = fStack_7c;
  if (param_8 != 0) {
    iVar5 = FUN_0045ea50(param_3);
    if ((iVar5 == 0) && ((*(uint *)((int)param_4 + 0x88) & 0x2000) == 0)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
      if (iStack_74 != 0) {
        FUN_0045eb10((int)param_4,(int)param_3,iStack_74);
      }
    }
    if (iStack_78 != 0) {
      if ((*(char *)((int)param_4 + 0xbc) == '\x02') || (*(char *)((int)param_4 + 0xbc) == '\t')) {
        FUN_0045eb60((uint)param_4);
      }
      fVar2 = fStack_70 * fStack_70 + fStack_68 * fStack_68 + fStack_6c * fStack_6c;
      if (*(float *)((int)param_4 + 0xe8) <= fVar2) {
        fVar1 = *(float *)((int)param_4 + 0x194);
        uStack_54 = *(undefined4 *)((int)param_4 + 0x198);
        uStack_50 = *(undefined4 *)((int)param_4 + 0x19c);
        FUN_00468c10(param_4,*param_6,param_6[1],param_6[2]);
        iVar5 = **(int **)(param_1 + 4);
        piVar6 = (int *)(**(code **)(iVar5 + 4))(&fStack_64,SQRT(fVar2));
        (**(code **)(iVar5 + 8))(param_4,*(undefined4 *)(*piVar6 + 0x10));
        FUN_00468c10(param_4,fVar1,uStack_54,uStack_50);
      }
      if (bVar3) {
        *(float *)((int)param_4 + 0xc4) = fStack_64 + *(float *)((int)param_4 + 0xc4);
        *(float *)((int)param_4 + 200) = fStack_60 + *(float *)((int)param_4 + 200);
        *(float *)((int)param_4 + 0xcc) = fStack_5c + *(float *)((int)param_4 + 0xcc);
      }
    }
  }
  return iStack_78 != 0;
}


/* 00460df0 size=1364 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00460df0: lifted from original x86 -> lt_lifted.c */


/* 00461350 size=40 */

void __thiscall FUN_00461350(void *this,undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = param_1[3];
  uVar2 = *param_1;
  *(undefined4 *)((int)this + 4) = param_1[1];
  *(undefined4 *)this = uVar2;
  *(undefined4 *)((int)this + 8) = param_2;
  *(undefined4 *)((int)this + 0xc) = uVar1;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  return;
}


/* 00461380 size=325 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_00461380(int param_1,int param_2,int param_3,int param_4,int param_5,float *param_6,
            undefined4 *param_7,int *param_8,int param_9)

{
  float *pfVar1;
  float fVar2;
  bool bVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int local_8;
  
  iVar9 = param_3 - (int)param_6;
  iVar10 = param_1 - (int)param_6;
  iVar11 = param_4 - (int)param_6;
  iVar6 = 0;
  iVar8 = 0;
  iVar13 = 0;
  iVar12 = param_5 - (int)param_6;
  iVar7 = param_2 - (int)param_6;
  local_8 = 0;
  fVar4 = _DAT_004ccc10;
  do {
    pfVar1 = (float *)(iVar9 + (int)param_6);
    fVar2 = *(float *)((int)pfVar1 + (param_9 - param_3));
    if (((fVar2 <= _DAT_004cbf0c) && (_DAT_004cbf04 <= *pfVar1 - *param_6)) &&
       (fVar5 = *param_6 - *(float *)(iVar10 + (int)param_6), ABS(fVar5) < ABS(fVar4))) {
      iVar8 = iVar6;
      local_8 = iVar13;
      fVar4 = fVar5;
    }
    if (((_DAT_004cbf04 <= fVar2) &&
        (_DAT_004cbf04 <= *(float *)(iVar12 + (int)param_6) - *(float *)(iVar11 + (int)param_6))) &&
       (fVar2 = *(float *)(iVar12 + (int)param_6) - *(float *)(iVar7 + (int)param_6),
       ABS(fVar2) < ABS(fVar4))) {
      iVar8 = iVar6;
      local_8 = iVar13 + 1;
      fVar4 = fVar2;
    }
    iVar13 = iVar13 + 2;
    iVar6 = iVar6 + 1;
    param_6 = param_6 + 1;
  } while (iVar6 < 3);
  bVar3 = fVar4 == _DAT_004ccc10;
  *param_7 = 0;
  param_7[1] = 0;
  param_7[2] = 0;
  if (bVar3) {
    fVar4 = _DAT_004cb524;
  }
  param_7[iVar8] = fVar4;
  *param_8 = local_8;
  return;
}


/* 004614d0 size=957 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_004614d0(float *param_1,int param_2,int param_3,float *param_4,float *param_5,uint *param_6,
            float *param_7)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  float fVar5;
  int iVar6;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_48 = *param_5 - *param_4;
  local_44 = param_5[1] - param_4[1];
  pfVar1 = (float *)(param_2 + 0x1a0);
  local_40 = param_5[2] - param_4[2];
  local_24 = *param_4 - *pfVar1;
  local_20 = param_4[1] - *(float *)(param_2 + 0x1a4);
  local_1c = param_4[2] - *(float *)(param_2 + 0x1a8);
  local_30 = *pfVar1 + *param_4;
  local_2c = *(float *)(param_2 + 0x1a4) + param_4[1];
  local_28 = *(float *)(param_2 + 0x1a8) + param_4[2];
  local_18 = *param_5 - *pfVar1;
  local_14 = param_5[1] - *(float *)(param_2 + 0x1a4);
  local_10 = param_5[2] - *(float *)(param_2 + 0x1a8);
  local_3c = *pfVar1 + *param_5;
  local_38 = *(float *)(param_2 + 0x1a4) + param_5[1];
  local_34 = *(float *)(param_2 + 0x1a8) + param_5[2];
  if (local_1c < local_10) {
    local_10 = local_1c;
  }
  if (local_20 < local_14) {
    local_14 = local_20;
  }
  if (local_24 < local_18) {
    local_18 = local_24;
  }
  if (local_28 <= local_34) {
    local_4 = local_34;
  }
  else {
    local_4 = local_28;
  }
  if (local_2c <= local_38) {
    local_8 = local_38;
  }
  else {
    local_8 = local_2c;
  }
  if (local_30 <= local_3c) {
    local_c = local_3c;
  }
  else {
    local_c = local_30;
  }
  FUN_00461380((int)&local_18,(int)&local_c,(int)&local_24,(int)&local_30,param_3 + 0xf4,
               (float *)(param_3 + 0x100),&local_3c,(int *)param_6,(int)&local_48);
  uVar4 = *param_6;
  if ((uVar4 & 1) == 0) {
    *param_7 = *(float *)(param_3 + 0x100 + ((int)uVar4 >> 1) * 4);
  }
  else {
    *param_7 = -*(float *)(param_3 + 0xf4 + ((int)(uVar4 - 1) >> 1) * 4);
  }
  if ((*param_6 == 2) || (*param_6 == 3)) {
    if (param_4[1] <= *(float *)(param_3 + 0x198)) {
      if (local_44 <= _DAT_004cb524) goto LAB_0046174d;
      iVar6 = param_3;
      param_3 = param_2;
    }
    else {
      if (_DAT_004cb524 <= local_44) goto LAB_0046174d;
      iVar6 = param_2;
    }
    FUN_0045eb10(iVar6,param_3,0);
  }
LAB_0046174d:
  if ((*(uint *)(param_2 + 0x88) & 0x2000000) == 0) {
    fVar2 = param_5[1];
    fVar3 = param_5[2];
    *param_1 = local_3c + *param_5;
    param_1[1] = local_38 + fVar2;
    param_1[2] = local_34 + fVar3;
    return;
  }
  fVar5 = -SQRT(local_3c * local_3c + local_34 * local_34 + local_38 * local_38);
  fVar2 = -fVar5;
  fVar5 = fVar5 / ((fVar5 - ((local_3c / fVar2) * local_48 +
                            (local_38 / fVar2) * local_44 + (local_34 / fVar2) * local_40)) - fVar5)
  ;
  fVar2 = param_5[1];
  fVar3 = param_5[2];
  *param_1 = fVar5 * local_48 + *param_5;
  param_1[1] = fVar5 * local_44 + fVar2;
  param_1[2] = local_40 * fVar5 + fVar3;
  return;
}


/* 00461890 size=210 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_00461890(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  *param_1 = *param_4;
  param_1[1] = param_4[1];
  param_1[2] = param_4[2];
  *param_2 = *param_5;
  param_2[1] = param_5[1];
  param_2[2] = param_5[2];
  if (*param_3 <= _DAT_004cb524) {
    if (*param_3 < _DAT_004cb524) {
      *param_2 = *param_2 - *param_3;
    }
  }
  else {
    *param_1 = *param_1 - *param_3;
  }
  if (param_3[1] <= _DAT_004cb524) {
    if (param_3[1] < _DAT_004cb524) {
      param_2[1] = param_2[1] - param_3[1];
    }
  }
  else {
    param_1[1] = param_1[1] - param_3[1];
  }
  if (_DAT_004cb524 < param_3[2]) {
    param_1[2] = param_1[2] - param_3[2];
    return;
  }
  if (param_3[2] < _DAT_004cb524) {
    param_2[2] = param_2[2] - param_3[2];
  }
  return;
}


/* 00461970 size=4059 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00461970: lifted from original x86 -> lt_lifted.c */


/* 00462950 size=19 */

void __fastcall FUN_00462950(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  return;
}


/* 00462970 size=1265 */

/* FUN_00462970: lifted from original x86 -> lt_lifted.c */


/* 004630e0 size=55 */

undefined4 __cdecl FUN_004630e0(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0xbc) != '\x02') {
    return 0;
  }
  uVar1 = (**(code **)(**(int **)(param_1 + 0x1b0) + 0x20))();
  if (((uVar1 & 4) == 0) &&
     (uVar1 = (**(code **)(**(int **)(param_1 + 0x1b0) + 0x20))(), (uVar1 & 8) == 0)) {
    return 0;
  }
  return 1;
}


/* 00463150 size=607 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __cdecl FUN_00463150(undefined4 *param_1,float *param_2,int param_3,int param_4)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int *this;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  float fStack_18;
  
  puVar7 = param_1;
  uVar8 = (**(code **)(*(int *)param_1[1] + 0x24))();
  this = (int *)param_1[2];
  param_1[6] = uVar8;
  pfVar1 = (float *)(this + 0x68);
  if ((param_4 != 0) &&
     (((float)this[0x68] - *param_2) * ((float)this[0x68] - *param_2) +
      ((float)this[0x69] - param_2[1]) * ((float)this[0x69] - param_2[1]) +
      ((float)this[0x6a] - param_2[2]) * ((float)this[0x6a] - param_2[2]) < _DAT_004cbf0c)) {
    return true;
  }
  if ((param_3 == 0) || ((this[0x22] & 0x20012000U) == 0)) {
    FUN_00468d10(this,*param_2,param_2[1],param_2[2]);
    (*(uint8_t*)((char*)&param_1+0)) = true;
  }
  else {
    fVar4 = *param_2;
    fVar5 = param_2[1];
    fVar6 = param_2[2];
    if (*pfVar1 <= *param_2) {
      fStack_18 = *pfVar1;
    }
    else {
      fStack_18 = *param_2;
    }
    if ((float)this[0x69] <= param_2[1]) {
      fVar2 = (float)this[0x69];
    }
    else {
      fVar2 = param_2[1];
    }
    if ((float)this[0x6a] <= param_2[2]) {
      fVar3 = (float)this[0x6a];
    }
    else {
      fVar3 = param_2[2];
    }
    FUN_00468d10(this,fStack_18,fVar2,fVar3);
    if ((float)this[0x69] < param_2[1]) {
      FUN_004633b0(param_1,1,param_2 + 1);
    }
    if (*pfVar1 < *param_2) {
      FUN_004633b0(param_1,0,param_2);
    }
    if ((float)this[0x6a] < param_2[2]) {
      FUN_004633b0(param_1,2,param_2 + 2);
    }
    (*(uint8_t*)((char*)&param_1+0)) =
         (fVar4 - *pfVar1) * (fVar4 - *pfVar1) +
         (fVar5 - (float)this[0x69]) * (fVar5 - (float)this[0x69]) +
         (fVar6 - (float)this[0x6a]) * (fVar6 - (float)this[0x6a]) < _DAT_004cbaec;
    *param_2 = *pfVar1;
    param_2[1] = (float)this[0x69];
    param_2[2] = (float)this[0x6a];
  }
  FUN_0045ea90((int)this);
  if (((char)this[0x2f] == '\x02') || ((char)this[0x2f] == '\t')) {
    FUN_0045eb60((uint)this);
  }
  FUN_004a3df0((void *)*puVar7,this);
  return (*(uint8_t*)((char*)&param_1+0));
}


/* 004633b0 size=749 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004633b0: lifted from original x86 -> lt_lifted.c */


/* 004636a0 size=1432 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004636a0: lifted from original x86 -> lt_lifted.c */


/* 00463c40 size=99 */

undefined4 __thiscall FUN_00463c40(void *this,float *param_1,float param_2)

{
  if ((((ABS(*(float *)this - *param_1) <= param_2) &&
       (ABS(*(float *)((int)this + 4) - param_1[1]) <= param_2)) &&
      (ABS(*(float *)((int)this + 8) - param_1[2]) <= param_2)) &&
     (ABS(*(float *)((int)this + 0xc) - param_1[3]) <= param_2)) {
    return 1;
  }
  return 0;
}


/* 00463cb0 size=1253 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00463cb0(undefined4 *param_1,void *param_2)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  undefined3 extraout_var;
  float10 fVar7;
  float *pfVar8;
  float *pfVar9;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  int local_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float local_6c [3];
  uint uStack_60;
  undefined4 local_8;
  undefined4 local_4;
  
  local_6c[0] = 0.0;
  local_6c[1] = 0.0;
  local_6c[2] = 0.0;
  local_8 = 0;
  local_4 = 0;
  if (((*(char *)((int)param_2 + 0xbc) != '\x02') && (*(char *)((int)param_2 + 0xbc) != '\t')) ||
     ((*(uint *)((int)param_2 + 0x88) & 0x4000) != 0)) {
    pfVar9 = (float *)((int)param_2 + 0x100);
    pfVar8 = (float *)((int)param_2 + 0xf4);
    local_a0 = param_1[2];
    iVar4 = FUN_0045f6e0((float *)(local_a0 + 0xf4),(float *)(local_a0 + 0x100),pfVar8,pfVar9,-0.001
                        );
    if (iVar4 != 0) {
      puVar5 = (uint *)(**(code **)(**(int **)(param_1[2] + 0x1b8) + 4))();
      iVar4 = FUN_0041b6c0(puVar5,pfVar8,pfVar9);
      if (iVar4 != 0) {
        iVar4 = param_1[2];
        if (((*(uint *)(iVar4 + 0x88) & 0x2000) == 0) ||
           ((*(uint *)((int)param_2 + 0x88) & 0x2000) == 0)) {
          FUN_004603d0((int *)param_1[1],iVar4,(int)param_2);
        }
        else {
          pfVar9 = (float *)((int)param_2 + 0x194);
          fStack_c4 = *pfVar9;
          fStack_c0 = *(float *)((int)param_2 + 0x198);
          fStack_bc = *(float *)((int)param_2 + 0x19c);
          pfVar8 = (float *)param_1[0x18];
          fStack_c8 = _DAT_004cba94 /
                      (fStack_c4 * pfVar8[0xc] + fStack_c0 * pfVar8[0xd] + fStack_bc * pfVar8[0xe] +
                      pfVar8[0xf]);
          fStack_d0 = (fStack_c4 * *pfVar8 + fStack_c0 * pfVar8[1] + fStack_bc * pfVar8[2] +
                      pfVar8[3]) * fStack_c8;
          fStack_cc = (fStack_c4 * pfVar8[4] + fStack_c0 * pfVar8[5] + fStack_bc * pfVar8[6] +
                      pfVar8[7]) * fStack_c8;
          fStack_c8 = (fStack_c4 * pfVar8[8] + fStack_c0 * pfVar8[9] + fStack_bc * pfVar8[10] +
                      pfVar8[0xb]) * fStack_c8;
          fVar1 = fStack_cc - *(float *)((int)param_2 + 0x198);
          fVar2 = fStack_c8 - *(float *)((int)param_2 + 0x19c);
          if (_DAT_004cbaec <=
              (fStack_d0 - *pfVar9) * (fStack_d0 - *pfVar9) + fVar1 * fVar1 + fVar2 * fVar2) {
            fStack_b8 = *(float *)(iVar4 + 0x194);
            fStack_ac = *pfVar9 - fStack_b8;
            fStack_b4 = *(float *)(iVar4 + 0x198);
            fStack_a8 = *(float *)((int)param_2 + 0x198) - fStack_b4;
            fStack_b0 = *(float *)(iVar4 + 0x19c);
            fStack_a4 = *(float *)((int)param_2 + 0x19c) - fStack_b0;
            fVar7 = FUN_0041fe80(&fStack_ac);
            if (fVar7 != (float10)_DAT_004cb524) {
              fVar7 = (float10)_DAT_004cba94 / fVar7;
              fStack_ac = (float)(fVar7 * (float10)fStack_ac);
              fStack_a8 = (float)((float10)fStack_a8 * fVar7);
              fStack_a4 = (float)((float10)fStack_a4 * fVar7);
            }
            iVar4 = 199;
            do {
              fStack_b8 = *(float *)((int)param_2 + 0x1a0);
              fStack_78 = fStack_d0 - fStack_b8;
              fStack_b4 = *(float *)((int)param_2 + 0x1a4);
              fStack_74 = fStack_cc - fStack_b4;
              fStack_b0 = *(float *)((int)param_2 + 0x1a8);
              fStack_70 = fStack_c8 - fStack_b0;
              fStack_90 = *(float *)((int)param_2 + 0x1a0);
              fStack_9c = fStack_90 + fStack_d0;
              fStack_8c = *(float *)((int)param_2 + 0x1a4);
              fStack_98 = fStack_cc + fStack_8c;
              fStack_88 = *(float *)((int)param_2 + 0x1a8);
              fStack_94 = fStack_c8 + fStack_88;
              pfVar9 = &fStack_84;
              pfVar8 = &fStack_78;
              fStack_84 = fStack_9c;
              fStack_80 = fStack_98;
              fStack_7c = fStack_94;
              puVar5 = (uint *)(**(code **)(**(int **)(local_a0 + 0x1b8) + 4))();
              iVar6 = FUN_0041b6c0(puVar5,pfVar8,pfVar9);
              if (iVar6 == 0) break;
              fStack_d0 = fStack_d0 + fStack_ac;
              fStack_cc = fStack_a8 + fStack_cc;
              fStack_c8 = fStack_a4 + fStack_c8;
              bVar3 = 0 < iVar4;
              iVar4 = iVar4 + -1;
            } while (bVar3);
            pfVar9 = (float *)((int)param_2 + 0xc4);
            fVar1 = *pfVar9;
            fStack_8c = *(float *)((int)param_2 + 200);
            fStack_88 = *(float *)((int)param_2 + 0xcc);
            FUN_00413050(&fStack_9c,fStack_c4 - fStack_d0,fStack_c0 - fStack_cc,
                         fStack_bc - fStack_c8);
            *pfVar9 = fStack_9c;
            *(float *)((int)param_2 + 200) = fStack_98;
            *(float *)((int)param_2 + 0xcc) = fStack_94;
            bVar3 = FUN_00460b60((int)param_1,*(undefined4 *)(local_a0 + 0x1b8),(int *)param_1[2],
                                 param_2,&fStack_d0,&fStack_c4,
                                 ~*(uint *)((int)param_2 + 0x88) >> 0x19 & 1,1);
            *pfVar9 = fVar1;
            *(float *)((int)param_2 + 200) = fStack_8c;
            *(float *)((int)param_2 + 0xcc) = fStack_88;
            if (CONCAT31(extraout_var,bVar3) != 0) {
              FUN_00460b30(local_6c,*param_1,param_1[1],param_2,param_1[3]);
              uStack_60 = (uint)*(byte *)((int)param_2 + 0xbd);
              FUN_0045ef30(local_6c,fStack_c4,fStack_c0,fStack_bc);
              pfVar9 = (float *)((int)param_2 + 0x100);
              pfVar8 = (float *)((int)param_2 + 0xf4);
              puVar5 = (uint *)(**(code **)(**(int **)(local_a0 + 0x1b8) + 4))();
              iVar4 = FUN_0041b6c0(puVar5,pfVar8,pfVar9);
              if (iVar4 != 0) {
                (**(code **)(*(int *)param_1[1] + 0x1c))(param_2,param_1[2]);
                return;
              }
            }
          }
        }
      }
    }
  }
  return;
}


