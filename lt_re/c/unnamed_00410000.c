/* lithtech.exe decompilation - unnamed_00410000 */
#include "ghidra_types.h"

/* 00410040 size=11 */

void FUN_00410040(void)

{
  DAT_004e5128 = 0;
  return;
}


/* 00410050 size=12 */

void FUN_00410050(void)

{
  FUN_004b9cf5(&LAB_00410060);
  return;
}


/* 004100a0 size=11 */

void FUN_004100a0(void)

{
  DAT_004e512c = 0;
  return;
}


/* 004100b0 size=12 */

void FUN_004100b0(void)

{
  FUN_004b9cf5(&LAB_004100c0);
  return;
}


/* 00410100 size=33 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00410100(void)

{
  _DAT_004e5130 = &PTR_FUN_004cbb80;
  FUN_004b7be0((uint *)&DAT_004e5134,0xc,0x40,0x400);
  return;
}


/* 00410130 size=12 */

void FUN_00410130(void)

{
  FUN_004b9cf5(&LAB_00410140);
  return;
}


/* 00410170 size=11 */

int FUN_00410170(void)

{
  return DAT_004e516c + 0x784;
}


/* 00410180 size=11 */

int FUN_00410180(void)

{
  return DAT_004e516c + 0x1094;
}


/* 00410630 size=355 */

void __fastcall FUN_00410630(int param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  LONG LVar3;
  uint uVar4;
  int *piStack_10;
  undefined4 *puStack_c;
  undefined4 *puStack_8;
  undefined4 *puStack_4;
  
  puVar1 = (undefined4 *)(**(code **)(**(int **)(param_1 + 0x620) + 4))();
  FUN_00414150(&DAT_004e5128,puVar1);
  if (DAT_004e5128 != (void *)0x0) {
    puVar1 = (undefined4 *)FUN_00430de0(0x2180);
    if (puVar1 == (undefined4 *)0x0) {
      DAT_004e5154 = (undefined4 *)0x0;
    }
    else {
      DAT_004e5154 = FUN_004a6500(puVar1);
    }
    puStack_c = (undefined4 *)0x0;
    *(undefined1 *)((int)DAT_004e5154 + 0x2171) = 1;
    piVar2 = FUN_004a5e70(DAT_004e5128,(int *)&puStack_4);
    puVar1 = FUN_004a6f60(DAT_004e5154,&puStack_8,(undefined4 *)*piVar2,2,4);
    FUN_00414150(&puStack_c,(undefined4 *)*puVar1);
    if (puStack_8 != (undefined4 *)0x0) {
      LVar3 = InterlockedDecrement(puStack_8 + 1);
      if ((LVar3 < 1) && (puStack_8 != (undefined4 *)0x0)) {
        (**(code **)*puStack_8)(1);
      }
    }
    if (puStack_4 != (undefined4 *)0x0) {
      LVar3 = InterlockedDecrement(puStack_4 + 1);
      if ((LVar3 < 1) && (puStack_4 != (undefined4 *)0x0)) {
        (**(code **)*puStack_4)(1);
      }
    }
    FUN_0046b170(&piStack_10,0x44c,0x44c);
    *(undefined1 *)piStack_10[0x15] = 0xd;
    if (puStack_c == (undefined4 *)0x0) {
      uVar4 = 0;
      puVar1 = (undefined4 *)0x0;
    }
    else {
      uVar4 = puStack_c[3];
      puVar1 = (undefined4 *)puStack_c[2];
    }
    FUN_0046b480(piStack_10,puVar1,uVar4);
    FUN_004657c0((void *)(param_1 + 0x510),piStack_10,*(float **)(*(int *)(param_1 + 0x161c) + 0x34)
                 ,0x80);
    if (piStack_10 != (int *)0x0) {
      (**(code **)(*piStack_10 + 8))();
    }
    puVar1 = puStack_c;
    if (puStack_c != (undefined4 *)0x0) {
      LVar3 = InterlockedDecrement(puStack_c + 1);
      if ((LVar3 < 1) && (puVar1 != (undefined4 *)0x0)) {
        (**(code **)*puVar1)(1);
      }
    }
  }
  return;
}


/* 004107a0 size=324 */

void __thiscall FUN_004107a0(void *this,void *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  LONG LVar3;
  int iVar4;
  uint uVar5;
  undefined4 *local_208;
  int *local_204;
  undefined4 local_200;
  undefined1 local_1fc [508];
  
  puVar2 = &local_200;
  for (iVar4 = 0x80; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  uVar5 = (uint)*(ushort *)((int)param_1 + 0x34) - (uint)*(ushort *)((int)param_1 + 0x38);
  FUN_0046b3c0(param_1,&local_200,uVar5);
  local_208 = (undefined4 *)0x0;
  FUN_004a70f0(DAT_004e5154,local_1fc,uVar5 - 4,(int *)&local_208);
  piVar1 = DAT_004e5154;
  if (DAT_004e5154 != (int *)0x0) {
    FUN_004108f0(DAT_004e5154);
    FUN_00430df0((undefined *)piVar1);
  }
  puVar2 = DAT_004e5128;
  if ((local_208 == (undefined4 *)0x0) || (local_208[3] == 0)) {
    if (DAT_004e5128 != (undefined4 *)0x0) {
      LVar3 = InterlockedDecrement(DAT_004e5128 + 1);
      if ((LVar3 < 1) && (puVar2 != (undefined4 *)0x0)) {
        (**(code **)*puVar2)(1);
      }
      DAT_004e5128 = (undefined4 *)0x0;
    }
  }
  else {
    FUN_0046b170(&local_204,0x44c,0x44c);
    *(undefined1 *)local_204[0x15] = 0xd;
    if (local_208 == (undefined4 *)0x0) {
      uVar5 = 0;
      puVar2 = (undefined4 *)0x0;
    }
    else {
      uVar5 = local_208[3];
      puVar2 = (undefined4 *)local_208[2];
    }
    FUN_0046b480(local_204,puVar2,uVar5);
    FUN_004657c0((void *)((int)this + 0x510),local_204,
                 *(float **)(*(int *)((int)this + 0x161c) + 0x34),0x80);
    if (local_204 != (int *)0x0) {
      (**(code **)(*local_204 + 8))();
    }
  }
  puVar2 = local_208;
  if (((local_208 != (undefined4 *)0x0) && (LVar3 = InterlockedDecrement(local_208 + 1), LVar3 < 1))
     && (puVar2 != (undefined4 *)0x0)) {
    (**(code **)*puVar2)(1);
  }
  return;
}


/* 004108f0 size=251 */

void __fastcall FUN_004108f0(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  LONG LVar4;
  
  puVar2 = (undefined4 *)param_1[0x85e];
  if (puVar2 != (undefined4 *)0x0) {
    LVar4 = InterlockedDecrement(puVar2 + 1);
    if ((LVar4 < 1) && (puVar2 != (undefined4 *)0x0)) {
      (**(code **)*puVar2)(1);
    }
  }
  puVar2 = (undefined4 *)param_1[0x85d];
  if (puVar2 != (undefined4 *)0x0) {
    LVar4 = InterlockedDecrement(puVar2 + 1);
    if ((LVar4 < 1) && (puVar2 != (undefined4 *)0x0)) {
      (**(code **)*puVar2)(1);
    }
  }
  FUN_00414100(param_1 + 0x845,'\x01');
  iVar3 = param_1[0x842];
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar3 + -1));
    }
    else {
      *(char *)(iVar3 + -1) = cVar1 + -1;
    }
  }
  param_1[0x842] = 0;
  param_1[0x843] = 0;
  param_1[0x844] = 0;
  FUN_00414100(param_1 + 0x418,'\x01');
  iVar3 = param_1[0x415];
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar3 + -1));
    }
    else {
      *(char *)(iVar3 + -1) = cVar1 + -1;
    }
  }
  param_1[0x415] = 0;
  param_1[0x416] = 0;
  param_1[0x417] = 0;
  puVar2 = (undefined4 *)*param_1;
  if (puVar2 != (undefined4 *)0x0) {
    LVar4 = InterlockedDecrement(puVar2 + 1);
    if ((LVar4 < 1) && (puVar2 != (undefined4 *)0x0)) {
      (**(code **)*puVar2)(1);
    }
  }
  return;
}


/* 004109f0 size=234 */

void __fastcall FUN_004109f0(int param_1)

{
  int *piVar1;
  undefined *puVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  LONG LVar6;
  code *pcStack_8;
  undefined4 uStack_4;
  
  puVar5 = DAT_004e5128;
  if (DAT_004e5128 != (undefined4 *)0x0) {
    LVar6 = InterlockedDecrement(DAT_004e5128 + 1);
    if ((LVar6 < 1) && (puVar5 != (undefined4 *)0x0)) {
      (**(code **)*puVar5)(1);
    }
    DAT_004e5128 = (undefined4 *)0x0;
  }
  *(undefined4 *)(param_1 + 0x1634) = 0;
  puVar4 = DAT_004e951c;
  while ((puVar4 != (undefined *)0x0 && (puVar4 != &DAT_004e9518))) {
    puVar2 = *(undefined **)(puVar4 + 4);
    piVar1 = (int *)(puVar4 + 8);
    puVar4 = puVar2;
    if ((*(byte *)(*piVar1 + 0x14) & 1) != 0) {
      FUN_004207e0(0x4e9500,*piVar1);
    }
  }
  iVar3 = *(int *)(param_1 + 0x620);
  if (iVar3 != 0) {
    *(undefined4 *)(param_1 + 0x620) = 0;
    FUN_0048e3c0(*(int *)(param_1 + 0x61c),&uStack_4,&pcStack_8);
    (*pcStack_8)(iVar3);
  }
  if (*(undefined4 **)(param_1 + 0x61c) != (undefined4 *)0x0) {
    FUN_0048e3a0(*(undefined4 **)(param_1 + 0x61c));
    *(undefined4 *)(param_1 + 0x61c) = 0;
  }
  if (*(undefined4 **)(param_1 + 0x614) != (undefined4 *)0x0) {
    FUN_004017d0(*(undefined4 **)(param_1 + 0x614));
    *(undefined4 *)(param_1 + 0x614) = 0;
  }
  if (*(undefined4 **)(param_1 + 0x618) != (undefined4 *)0x0) {
    FUN_004017d0(*(undefined4 **)(param_1 + 0x618));
    *(undefined4 *)(param_1 + 0x618) = 0;
  }
  return;
}


/* 00410ae0 size=18 */

void __fastcall FUN_00410ae0(int param_1)

{
  if (*(int **)(param_1 + 0x620) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x620) + 0x28))();
  }
  return;
}


/* 00410b00 size=18 */

void __fastcall FUN_00410b00(int param_1)

{
  if (*(int **)(param_1 + 0x620) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x620) + 0x2c))();
  }
  return;
}


/* 004110a0 size=42 */

void __fastcall FUN_004110a0(int param_1)

{
  FUN_004341b0((void *)(param_1 + 0x169c));
  if (*(undefined4 **)(param_1 + 0x161c) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x161c))(1);
    *(undefined4 *)(param_1 + 0x161c) = 0;
  }
  return;
}


/* 00411260 size=21 */

undefined4 __fastcall FUN_00411260(int param_1)

{
  if (*(int *)(param_1 + 0x161c) != 0) {
    FUN_00416b10(*(int *)(param_1 + 0x161c));
  }
  return 1;
}


/* 00411280 size=16 */

void __fastcall FUN_00411280(int param_1)

{
  if (*(int *)(param_1 + 0x161c) == 0) {
    return;
  }
  FUN_00416b50(*(int *)(param_1 + 0x161c));
  return;
}


/* 00411290 size=72 */

/* FUN_00411290: lifted from original x86 -> lt_lifted.c */


/* 004112e0 size=40 */

void __fastcall FUN_004112e0(int param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)(param_1 + 0x1228); iVar1 != param_1 + 0x1224; iVar1 = *(int *)(iVar1 + 4)) {
    FUN_00471770(*(int *)(iVar1 + 8));
  }
  return;
}


/* 00411310 size=65 */

void FUN_00411310(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  uint local_4;
  
  local_8 = DAT_004eaa94;
  local_4 = DAT_004eaa98 >> 1;
  local_10 = 0;
  local_c = 0;
  FUN_00420e00(0);
  FUN_00420e30(&local_10,FUN_00424090,&DAT_004eaa58);
  return;
}


/* 00411360 size=9 */

void FUN_00411360(void)

{
  FUN_00420e00(0);
  return;
}


/* 00411370 size=23 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00411370(int param_1)

{
  *(undefined4 *)(param_1 + 0x1720) = 0;
  DAT_004e516c = param_1;
  _DAT_004e9560 = param_1;
  return;
}


/* 00411390 size=40 */

void __thiscall FUN_00411390(void *this,int param_1)

{
  if ((*(int *)(param_1 + 8) == 0) && (*(int *)(param_1 + 0x10) == 0)) {
    FUN_0048db40(this,*(undefined4 *)(param_1 + 0x18),(char)*(undefined4 *)(param_1 + 0x14),1);
  }
  return;
}


/* 004113c0 size=76 */

void __fastcall FUN_004113c0(void *param_1)

{
  int iVar1;
  int local_20 [8];
  
  FUN_0044df70((int)local_20);
  iVar1 = FUN_0044e1e0((void *)((int)param_1 + 0x16e4),local_20,0);
  while (iVar1 == 0) {
    FUN_00411390(param_1,(int)local_20);
    iVar1 = FUN_0044e1e0((void *)((int)param_1 + 0x16e4),local_20,0);
  }
  return;
}


/* 00411410 size=764 */

undefined4 __fastcall FUN_00411410(void *param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  UINT UVar6;
  ushort uVar7;
  undefined8 uVar8;
  LARGE_INTEGER LStack_18;
  int *piStack_10;
  LARGE_INTEGER LStack_c;
  int *piStack_4;
  
  FUN_004113c0(param_1);
  if (*(int **)((int)param_1 + 0x1720) != (int *)0x0) {
    (**(code **)(**(int **)((int)param_1 + 0x1720) + 8))();
  }
  if (DAT_004e98b4 != 0) {
    *(undefined4 *)((int)param_1 + 0x76c) = 0x3f800000;
    *(undefined4 *)((int)param_1 + 0x770) = 0x3f800000;
    *(undefined4 *)((int)param_1 + 0x774) = 0x3f800000;
  }
  iVar3 = FUN_00436610();
  if (iVar3 != 0) {
    FUN_00434500((void *)((int)param_1 + 0x169c));
  }
  FUN_004364f0(DAT_004e98f8);
  if (*(int *)((int)param_1 + 0x10f0) != 0) {
    FUN_00424310(&LStack_18,0);
    piStack_10 = (int *)&DAT_004e5158;
    FUN_00424400(&LStack_18);
    if (DAT_004d834c != *(int *)((int)param_1 + 0x10f4)) {
      *(int *)((int)param_1 + 0x10f4) = DAT_004d834c;
      if (DAT_004d834c == 0) {
        (**(code **)((int)param_1 + 0x10dc))(0);
      }
      else {
        (**(code **)((int)param_1 + 0x10e0))();
      }
    }
    uVar8 = FUN_00424410((uint *)&LStack_18);
    *piStack_10 = *piStack_10 + (int)uVar8;
  }
  if (*(int *)((int)param_1 + 0x8a8) != 0) {
    FUN_00424310(&LStack_18,0);
    piStack_10 = &DAT_004e515c;
    FUN_00424400(&LStack_18);
    if (DAT_004d8350 != *(int *)((int)param_1 + 0x8ac)) {
      *(int *)((int)param_1 + 0x8ac) = DAT_004d8350;
      if (DAT_004d8350 == 0) {
        (**(code **)(*(int *)((int)param_1 + 0x784) + 0x68))();
      }
      else {
        (**(code **)(*(int *)((int)param_1 + 0x784) + 0x6c))();
      }
    }
    uVar8 = FUN_00424410((uint *)&LStack_18);
    *piStack_10 = *piStack_10 + (int)uVar8;
  }
  iVar3 = FUN_00433ee0((int)param_1 + 0x169c);
  if (iVar3 == 0) {
    FUN_00426880((int)param_1);
  }
  iVar3 = FUN_00436610();
  if (iVar3 != 0) {
    FUN_00424310(&LStack_18,0);
    piStack_10 = &DAT_004e5160;
    FUN_00424400(&LStack_18);
    FUN_00411710(param_1,0);
    uVar8 = FUN_00424410((uint *)&LStack_18);
    *piStack_10 = *piStack_10 + (int)uVar8;
  }
  if (*(int *)((int)param_1 + 0x161c) == 0) {
    if (*(int **)((int)param_1 + 0x620) != (int *)0x0) {
      (**(code **)(**(int **)((int)param_1 + 0x620) + 0x38))();
      (**(code **)(**(int **)((int)param_1 + 0x620) + 0x3c))();
      FUN_00418590((int)param_1);
      (**(code **)(**(int **)((int)param_1 + 0x620) + 0x40))();
    }
  }
  else {
    FUN_00424310(&LStack_18,0);
    piStack_10 = &DAT_004e5164;
    FUN_00424400(&LStack_18);
    uVar4 = clientshell_415560(*(int *)((int)param_1 + 0x161c));
    if (uVar4 != 0) {
      uVar5 = FUN_004267e0((int)param_1,uVar4);
      uVar8 = FUN_00424410((uint *)&LStack_18);
      *piStack_10 = *piStack_10 + (int)uVar8;
      return uVar5;
    }
    uVar8 = FUN_00424410((uint *)&LStack_18);
    *piStack_10 = *piStack_10 + (int)uVar8;
  }
  FUN_00424310(&LStack_c,0);
  piStack_4 = &DAT_004e515c;
  FUN_00424400(&LStack_c);
  FUN_00424310(&LStack_18,0);
  piStack_10 = &DAT_004e4e30;
  FUN_00424400(&LStack_18);
  clientmgr_4118c0((int)param_1);
  uVar8 = FUN_00424410((uint *)&LStack_18);
  *piStack_10 = *piStack_10 + (int)uVar8;
  uVar8 = FUN_00424410((uint *)&LStack_c);
  *piStack_4 = *piStack_4 + (int)uVar8;
  iVar3 = FUN_00433ee0((int)param_1 + 0x169c);
  if (iVar3 != 0) {
    uVar7 = 0;
    sVar1 = FUN_00436510();
    if (sVar1 != 0) {
      do {
        UVar6 = FUN_00436530((uint)uVar7);
        FUN_00420ec0(UVar6);
        uVar7 = uVar7 + 1;
        uVar2 = FUN_00436510();
      } while (uVar7 < uVar2);
    }
    FUN_00436560();
    FUN_00436570();
  }
  return 0;
}


/* 00411710 size=147 */

void __thiscall FUN_00411710(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  uint local_800;
  uint local_7fc;
  int local_7f8 [255];
  char local_3fc [1020];
  
  if (param_1 == 0) {
    iVar1 = FUN_00433ee0((int)this + 0x169c);
    iVar2 = 0;
    if (iVar1 == 0) goto LAB_00411735;
  }
  iVar2 = 1;
LAB_00411735:
  FUN_00434220((void *)((int)this + 0x169c),(int)local_7f8,&local_7fc,(int)local_3fc,
               (int *)&local_800,iVar2);
  FUN_00426920(this,local_7f8,local_7fc);
  iVar2 = *(int *)((int)this + 0x161c);
  if ((iVar2 != 0) && (*(int *)(iVar2 + 0x7c) != 0)) {
    FUN_004181c0(this,(void *)((int)this + 0x510),*(float **)(iVar2 + 0x34),local_3fc,local_800);
  }
  return;
}


/* 004117b0 size=48 */

undefined4 __fastcall FUN_004117b0(void *param_1)

{
  if (*(int *)((int)param_1 + 0x16b4) == 0) {
    FUN_00411710(param_1,1);
    FUN_00436560();
    FUN_00436570();
    FUN_00436580();
    (**(code **)(*(int *)((int)param_1 + 0x1618) + 0x1c))();
  }
  return 0;
}


/* 004117e0 size=35 */

/* FUN_004117e0: lifted from original x86 -> lt_lifted.c */


/* 00411cc0 size=17 */

void __fastcall FUN_00411cc0(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + 1;
  param_1[2] = puVar1;
  *puVar1 = puVar1;
  *param_1 = 0;
  return;
}


/* 00411ce0 size=144 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00411ce0(void *this,float *param_1)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  
  pfVar1 = (float *)((int)this + 0x14);
  *pfVar1 = *param_1;
  *(float *)((int)this + 0x18) = param_1[1];
  *(float *)((int)this + 0x1c) = param_1[2];
  fVar3 = SQRT(*(float *)((int)this + 0x1c) * *(float *)((int)this + 0x1c) +
               *(float *)((int)this + 0x18) * *(float *)((int)this + 0x18) + *pfVar1 * *pfVar1);
  *(float *)((int)this + 0x2c) = fVar3;
  if (_DAT_004cba90 < fVar3) {
    pfVar2 = (float *)((int)this + 0x20);
    fVar3 = *(float *)((int)this + 0x2c);
    *pfVar2 = *pfVar1;
    *(undefined4 *)((int)this + 0x24) = *(undefined4 *)((int)this + 0x18);
    *(undefined4 *)((int)this + 0x28) = *(undefined4 *)((int)this + 0x1c);
    *pfVar2 = *pfVar2 / fVar3;
    *(float *)((int)this + 0x24) = *(float *)((int)this + 0x24) / fVar3;
    *(float *)((int)this + 0x28) = *(float *)((int)this + 0x28) / fVar3;
    return;
  }
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x28) = 0;
  return;
}


/* 00412200 size=102 */

void __cdecl FUN_00412200(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = *(int *)(param_1 + 4);
  while (iVar2 != param_1) {
    iVar1 = *(int *)(iVar2 + 4);
    *(int *)(*(int *)(iVar2 + 8) + 0x20c) = *(int *)(*(int *)(iVar2 + 8) + 0x20c) + 1;
    iVar2 = iVar1;
  }
  iVar2 = *(int *)(param_1 + 4);
  while (iVar2 != param_1) {
    puVar3 = *(undefined4 **)(iVar2 + 8);
    iVar2 = *(int *)(iVar2 + 4);
    if (puVar3[0x83] != 0) {
      puVar3[0x83] = puVar3[0x83] + -1;
    }
    if ((puVar3[0x83] == 0) && (puVar3 != (undefined4 *)0x0)) {
      (**(code **)*puVar3)(1);
    }
  }
  *(int *)(param_1 + 4) = param_1;
  *(int *)param_1 = param_1;
  return;
}


/* 00412270 size=53 */

void __cdecl FUN_00412270(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar1 = param_1 + 1;
  puVar3 = (undefined4 *)param_1[2];
  while (puVar3 != puVar1) {
    puVar2 = (undefined4 *)puVar3[1];
    FUN_0049aa90((undefined *)puVar3[2]);
    puVar3 = puVar2;
  }
  param_1[2] = puVar1;
  *puVar1 = puVar1;
  *param_1 = 0;
  return;
}


/* 004122b0 size=96 */

int * __fastcall FUN_004122b0(int *param_1)

{
  int *piVar1;
  int *local_4;
  
  local_4 = param_1;
  piVar1 = FUN_0046b170(&local_4,0x44c,0x44c);
  piVar1 = (int *)*piVar1;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))();
  }
  if (local_4 != (int *)0x0) {
    (**(code **)(*local_4 + 8))();
  }
  (**(code **)(*piVar1 + 4))();
  piVar1[3] = param_1[0x130];
  piVar1[0x10] = piVar1[0x10] | 1;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))();
  }
  return piVar1;
}


/* 00412310 size=16 */

void __thiscall FUN_00412310(void *this,int param_1)

{
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)((int)this + 0x4c0);
  return;
}


/* 00412320 size=77 */

undefined4 __fastcall FUN_00412320(int param_1)

{
  undefined4 in_EAX;
  int iVar1;
  
  if (*(short *)(param_1 + 0x22bc) == -1) {
    *(undefined2 *)(param_1 + 0x22bc) = 1;
    iVar1 = *(int *)(param_1 + 0x1228);
    if (iVar1 != param_1 + 0x1224) {
      do {
        *(undefined2 *)(*(int *)(iVar1 + 8) + 0x30) = 0;
        iVar1 = *(int *)(iVar1 + 4);
      } while (iVar1 != param_1 + 0x1224);
      return CONCAT22((short)((uint)iVar1 >> 0x10),*(undefined2 *)(param_1 + 0x22bc));
    }
  }
  else {
    iVar1 = CONCAT22((short)((uint)in_EAX >> 0x10),*(short *)(param_1 + 0x22bc)) + 1;
    *(short *)(param_1 + 0x22bc) = (short)iVar1;
  }
  return CONCAT22((short)((uint)iVar1 >> 0x10),*(undefined2 *)(param_1 + 0x22bc));
}


/* 00412370 size=201 */

undefined4 __fastcall FUN_00412370(int param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  for (iVar3 = *(int *)(param_1 + 0x1208); iVar3 != param_1 + 0x1204; iVar3 = *(int *)(iVar3 + 4)) {
    iVar4 = *(int *)(iVar3 + 8);
    *(int *)(iVar4 + 0x20c) = *(int *)(iVar4 + 0x20c) + 1;
    *(uint *)(iVar4 + 0x20) = *(uint *)(iVar4 + 0x20) & 0xfffffffe;
  }
  for (iVar3 = *(int *)(param_1 + 0x428); iVar3 != param_1 + 0x424; iVar3 = *(int *)(iVar3 + 4)) {
    if (*(short *)(*(int *)(iVar3 + 8) + 0xb8) == -1) {
      puVar1 = (uint *)(*(int *)(*(int *)(iVar3 + 8) + 0x1f8) + 0x20);
      *puVar1 = *puVar1 | 1;
    }
  }
  iVar3 = *(int *)(param_1 + 0x1208);
  while (iVar3 != param_1 + 0x1204) {
    puVar5 = *(undefined4 **)(iVar3 + 8);
    iVar3 = *(int *)(iVar3 + 4);
    if (puVar5[0x83] != 0) {
      puVar5[0x83] = puVar5[0x83] + -1;
    }
    if ((puVar5[0x83] == 0) && ((*(byte *)(puVar5 + 8) & 1) == 0)) {
      puVar2 = puVar5 + 2;
      *(undefined4 *)(puVar5[2] + 4) = puVar5[3];
      *(undefined4 *)puVar5[3] = *puVar2;
      puVar5[3] = puVar2;
      *puVar2 = puVar2;
      if (puVar5 != (undefined4 *)0x0) {
        (**(code **)*puVar5)(1);
      }
    }
  }
  return 0;
}


/* 00412440 size=741 */

undefined4 __thiscall FUN_00412440(void *this,char *param_1,undefined4 *param_2)

{
  char cVar1;
  void *pvVar2;
  uint *_Source;
  uint *puVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  char *pcVar10;
  byte *pbVar11;
  char *pcVar12;
  undefined1 local_3a8 [4];
  int *local_3a4;
  void *local_3a0;
  void *local_39c;
  int local_398;
  uint *local_394;
  undefined2 local_390;
  int local_38c;
  int local_388;
  undefined2 local_384;
  char local_380 [127];
  char cStack_301;
  undefined4 local_300 [32];
  char local_280 [128];
  byte local_200 [512];
  
  if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    return 0;
  }
  uVar7 = 0xffffffff;
  do {
    pcVar10 = param_1;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar10 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar10;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pbVar9 = (byte *)(pcVar10 + -uVar7);
  pbVar11 = local_200;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pbVar11 = *(undefined4 *)pbVar9;
    pbVar9 = pbVar9 + 4;
    pbVar11 = pbVar11 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pbVar11 = *pbVar9;
    pbVar9 = pbVar9 + 1;
    pbVar11 = pbVar11 + 1;
  }
  _Source = (uint *)FUN_004ba43e(local_200,(byte *)s___004d66fc);
  do {
    if (_Source == (uint *)0x0) {
      *param_2 = 1;
      return 0;
    }
    puVar3 = FUN_004bae50(_Source,&DAT_004d66f8);
    if (puVar3 == (uint *)0x0) {
      local_390 = 0;
      local_398 = 1;
      local_394 = _Source;
      piVar4 = FUN_004049e0(*(int *)((int)this + 0x1644),&local_398);
      if (piVar4 != (int *)0x0) {
        (**(code **)(**(int **)(*(int *)((int)this + 0x4c4) + 8) + 0x3c))(piVar4,local_3a8);
        (**(code **)(*piVar4 + 4))();
      }
    }
    else {
      _strncpy(local_380,(char *)_Source,(int)puVar3 - (int)_Source);
      uVar7 = 0xffffffff;
      pcVar10 = (char *)((int)puVar3 + 1);
      do {
        pcVar12 = pcVar10;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar12 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar12;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar10 = pcVar12 + -uVar7;
      pcVar12 = local_280;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar12 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar12 = pcVar12 + 1;
      }
      uVar7 = 0xffffffff;
      local_380[(int)puVar3 - (int)_Source] = '\0';
      pcVar10 = local_380;
      do {
        pcVar12 = pcVar10;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar12 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar12;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar10 = pcVar12 + -uVar7;
      pcVar12 = (char *)local_300;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar12 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar12 = pcVar12 + 1;
      }
      uVar7 = 0xffffffff;
      pcVar10 = (char *)local_300;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      for (uVar7 = ~uVar7; (0 < (int)(uVar7 - 1) && (local_380[uVar7 + 0x7f] != '\\'));
          uVar7 = uVar7 - 1) {
        local_380[uVar7 + 0x7f] = '\0';
      }
      piVar4 = FUN_00404730(*(int *)((int)this + 0x1644),(char *)local_300);
      uVar7 = 0xffffffff;
      pcVar10 = local_380;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      local_3a0 = (void *)(~uVar7 - 1);
      uVar7 = 0xffffffff;
      pcVar10 = local_280;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      local_39c = (void *)(~uVar7 - 1);
      local_3a4 = piVar4;
      if (piVar4 != (int *)0x0) {
        do {
          pvVar2 = local_39c;
          if ((*piVar4 == 1) &&
             (iVar5 = FUN_004c8310((byte *)piVar4[2],local_380,local_3a0), iVar5 == 0)) {
            uVar7 = 0xffffffff;
            pcVar10 = (char *)piVar4[2];
            do {
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              cVar1 = *pcVar10;
              pcVar10 = pcVar10 + 1;
            } while (cVar1 != '\0');
            iVar5 = FUN_004c8310((byte *)((char *)piVar4[2] + ((~uVar7 - 1) - (int)pvVar2)),
                                 local_280,pvVar2);
            if (iVar5 == 0) {
              local_388 = piVar4[2];
              local_384 = 0;
              local_38c = 1;
              piVar6 = FUN_004049e0(*(int *)((int)this + 0x1644),&local_38c);
              if (piVar6 != (int *)0x0) {
                (**(code **)(**(int **)(*(int *)((int)this + 0x4c4) + 8) + 0x3c))(piVar6,local_3a8);
                (**(code **)(*piVar6 + 4))();
              }
            }
          }
          piVar4 = (int *)piVar4[3];
        } while (piVar4 != (int *)0x0);
      }
      FUN_00440140((undefined *)local_3a4);
    }
    _Source = (uint *)FUN_004ba43e((byte *)0x0,(byte *)s___004d66fc);
  } while( true );
}


/* 00412730 size=87 */

void __cdecl FUN_00412730(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  client_filemgr_404300
            (*(int *)(param_1 + 0x1644),*(undefined4 *)(*(int *)(param_1 + 0x161c) + 0x34));
  puVar2 = (undefined4 *)(param_1 + 0x1378);
  for (iVar1 = 0x11; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(code **)(param_1 + 0x13a0) = FUN_00430f00;
  *(code **)(param_1 + 0x13a4) = FUN_00430fe0;
  FUN_00420630(param_1 + 0x1378);
  *(undefined4 *)(param_1 + 0x1600) = 0;
  return;
}


/* 00412790 size=64 */

void __cdecl FUN_00412790(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_2 == *(int *)(param_1 + 0x161c)) {
    puVar2 = (undefined4 *)(param_1 + 0x1270);
    for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0xffffffff;
      puVar2 = puVar2 + 1;
    }
    FUN_00404580(*(int **)(param_1 + 0x1644));
    FUN_004206a0((undefined4 *)(param_1 + 0x1378));
  }
  return;
}


/* 004128b0 size=35 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_004128b0(undefined4 param_1,LPCSTR param_2)

{
  _DAT_004e9560 = param_1;
  FUN_004208c0(&DAT_004e9500,param_2);
  return;
}


/* 004128e0 size=33 */

void __cdecl FUN_004128e0(int param_1,LPCSTR param_2)

{
  if (*(int *)(param_1 + 0x1628) != 0) {
    FUN_00420960(&DAT_004e9500,param_2);
  }
  return;
}


/* 00412940 size=1020 */

/* FUN_00412940: lifted from original x86 -> lt_lifted.c */


/* 00412d60 size=21 */

void __cdecl FUN_00412d60(int param_1)

{
  FUN_004112e0(param_1);
  FUN_00411290(param_1);
  return;
}


/* 00412d80 size=373 */

int __cdecl
FUN_00412d80(int param_1,undefined2 param_2,int *param_3,undefined4 *param_4,int param_5,int param_6
            )

{
  int *piVar1;
  int iVar2;
  undefined2 extraout_var;
  
  piVar1 = param_3;
  *param_4 = 0;
  iVar2 = FUN_0046a710((undefined4 *)(param_1 + 0x1f0),(ushort *)param_3[0xf],&param_3);
  if (iVar2 == 0) {
    iVar2 = FUN_0048e1e0(param_1,(int)param_3,piVar1,0);
    if (iVar2 != 0) {
      FUN_0046a800(param_1 + 0x1f0,(int)param_3);
      return iVar2;
    }
    *(undefined2 *)(param_3 + 0x2e) = param_2;
    if ((short)param_3[0x2e] != -1) {
      FUN_00426fd0(param_1,CONCAT22(extraout_var,(short)param_3[0x2e]));
      *(undefined1 *)(*(int *)(param_1 + 0x12ec) + (uint)*(ushort *)(param_3 + 0x2e) * 8) = 1;
      *(int **)(*(int *)(param_1 + 0x12ec) + 4 + (uint)*(ushort *)(param_3 + 0x2e) * 8) = param_3;
    }
    if (param_5 == 0) {
      if (param_6 != 0) {
        FUN_004273f0(param_1,param_3,(float *)(piVar1[0xf] + 0x2c));
      }
    }
    else if (param_6 == 0) {
      FUN_00427310(param_1,param_3,(float *)(piVar1[0xf] + 0x14),1);
    }
    else {
      FUN_004274f0(param_1,param_3,(float *)(piVar1[0xf] + 0x14),(int *)(piVar1[0xf] + 0x2c));
    }
    iVar2 = piVar1[0xf];
    if (((*(int *)(iVar2 + 0x20) != 0x3f800000) || (*(int *)(iVar2 + 0x24) != 0x3f800000)) ||
       (*(int *)(iVar2 + 0x28) != 0x3f800000)) {
      FUN_004270f0(param_1,param_3,(float *)(iVar2 + 0x20));
    }
    if (((char)param_3[0x2f] == '\x02') || ((char)param_3[0x2f] == '\t')) {
      FUN_0045eef0(param_3);
    }
    *param_4 = param_3;
    DAT_004eabac = DAT_004eabac | 1;
    iVar2 = 0;
  }
  return iVar2;
}


/* 00412f00 size=142 */

undefined4 __cdecl FUN_00412f00(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_0045ea90(param_2);
  FUN_0045ead0(param_2);
  FUN_00431720(param_2);
  if (((*(byte *)(param_2 + 0x188) & 1) != 0) && (*(int **)(param_1 + 0x620) != (int *)0x0)) {
    (**(code **)(**(int **)(param_1 + 0x620) + 0x34))(param_2);
  }
  uVar1 = FUN_0048e210(param_1,param_2);
  if (*(short *)(param_2 + 0xb8) != -1) {
    FUN_00427060(param_1,CONCAT22((short)((uint)uVar1 >> 0x10),*(short *)(param_2 + 0xb8)));
  }
  if (*(char *)(param_2 + 0xbc) == '\x01') {
    FUN_00426e90(param_1,param_2);
  }
  FUN_0046a800(param_1 + 0x1f0,param_2);
  DAT_004eabac = DAT_004eabac | 2;
  return 0;
}


/* 00412f90 size=68 */

void __cdecl FUN_00412f90(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_2 + 8);
  while (iVar3 != param_2 + 4) {
    iVar2 = *(int *)(iVar3 + 4);
    piVar1 = (int *)(iVar3 + 8);
    iVar3 = iVar2;
    if ((param_3 == 0) || (*(short *)(*piVar1 + 0xb8) != -1)) {
      FUN_00412f00(param_1,*piVar1);
    }
  }
  return;
}


/* 00412fe0 size=55 */

void __cdecl FUN_00412fe0(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar2 = *(undefined **)(param_1 + 0x1374);
  if (puVar2 == (undefined *)0x0) {
    *(undefined4 *)(param_1 + 0x1374) = 0;
    return;
  }
  do {
    puVar1 = *(undefined **)(puVar2 + 4);
    FUN_00430fe0(puVar2);
    puVar2 = puVar1;
  } while (puVar1 != (undefined *)0x0);
  *(undefined4 *)(param_1 + 0x1374) = 0;
  return;
}


/* 00413050 size=25 */

void __thiscall FUN_00413050(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)this = param_1;
  *(undefined4 *)((int)this + 4) = param_2;
  *(undefined4 *)((int)this + 8) = param_3;
  return;
}


/* 00413390 size=40 */

void __thiscall FUN_00413390(void *this,undefined4 *param_1)

{
  (**(code **)*param_1)(0);
  if ((param_1 != (undefined4 *)0x0) && (this != (void *)0xfffffffc)) {
    *param_1 = *(undefined4 *)((int)this + 0x1c);
    *(undefined4 **)((int)this + 0x1c) = param_1;
  }
  return;
}


