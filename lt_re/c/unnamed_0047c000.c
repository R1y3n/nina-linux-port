/* lithtech.exe decompilation - unnamed_0047c000 */
#include "ghidra_types.h"

/* 0047c060 size=118 */

undefined4 __thiscall FUN_0047c060(void *this,int param_1,float *param_2)

{
  if (param_1 != 0) {
    FUN_00492ed0(*(int *)((int)this + 0xc),param_1,param_2);
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTPhysics__MoveObject_004dbe8c);
  }
  return 0x3c;
}


/* 0047ea90 size=297 */

void FUN_0047ea90(int param_1,uint param_2)

{
  byte *pbVar1;
  char *pcVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0xbc) == '\x01') {
    if (param_2 != *(ushort *)(param_1 + 0x208)) {
      FUN_00401200(param_1 + 0x1d0,param_2,*(uint *)(param_1 + 0x88) >> 7 & 1);
      iVar3 = DAT_004ebfa4;
      if (((*(uint *)(param_1 + 0x124) & 4) == 0) || ((*(uint *)(param_1 + 0x124) & 1) != 0)) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c)
          ;
        }
      }
      else {
        pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(param_1 + 0xb8) * 8);
        if ((*pcVar2 == '\x01') && (*(int *)(pcVar2 + 4) != 0)) {
          if ((*(short *)(*(int *)(param_1 + 400) + 0x58) == 0) &&
             (*(int *)(DAT_004ebfa4 + 0x664) != 0)) {
            *(undefined4 *)(*(int *)(param_1 + 400) + 0x50) = *(undefined4 *)(DAT_004ebfa4 + 0xb20);
            *(int *)(iVar3 + 0xb20) = param_1;
          }
          pbVar1 = (byte *)(*(int *)(param_1 + 400) + 0x58);
          *pbVar1 = *pbVar1 | 0x20;
          return;
        }
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c)
          ;
          return;
        }
      }
    }
  }
  return;
}


/* 0047ebf0 size=305 */

void FUN_0047ebf0(int param_1,int param_2)

{
  byte *pbVar1;
  char *pcVar2;
  int iVar3;
  ushort uVar4;
  
  if (*(char *)(param_1 + 0xbc) == '\x01') {
    uVar4 = *(ushort *)(param_1 + 0x1e8);
    if ((uVar4 >> 1 & 1) != (ushort)(param_2 != 0)) {
      if (param_2 == 0) {
        uVar4 = uVar4 & 0xfffd;
      }
      else {
        uVar4 = uVar4 | 2;
      }
      *(ushort *)(param_1 + 0x1e8) = uVar4;
      iVar3 = DAT_004ebfa4;
      if (((*(uint *)(param_1 + 0x124) & 4) == 0) || ((*(uint *)(param_1 + 0x124) & 1) != 0)) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c)
          ;
        }
      }
      else {
        pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(param_1 + 0xb8) * 8);
        if ((*pcVar2 == '\x01') && (*(int *)(pcVar2 + 4) != 0)) {
          if ((*(short *)(*(int *)(param_1 + 400) + 0x58) == 0) &&
             (*(int *)(DAT_004ebfa4 + 0x664) != 0)) {
            *(undefined4 *)(*(int *)(param_1 + 400) + 0x50) = *(undefined4 *)(DAT_004ebfa4 + 0xb20);
            *(int *)(iVar3 + 0xb20) = param_1;
          }
          pbVar1 = (byte *)(*(int *)(param_1 + 400) + 0x58);
          *pbVar1 = *pbVar1 | 0x20;
          return;
        }
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c)
          ;
          return;
        }
      }
    }
  }
  return;
}


/* 0047f8e0 size=131 */

int * __thiscall FUN_0047f8e0(void *this,int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  if (param_2 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_ILTPhysics__StartMessageToObject_004dc334);
    }
    return (int *)0x0;
  }
  piVar2 = FUN_0048a310(*(int **)((int)this + 0x244));
  piVar2[5] = 0;
  if (param_1 == 0) {
    piVar2[8] = param_2;
    piVar2[7] = 0;
    piVar2[9] = param_3;
    return piVar2 + 2;
  }
  iVar1 = *(int *)(param_1 + 8);
  piVar2[8] = param_2;
  piVar2[7] = iVar1;
  piVar2[9] = param_3;
  return piVar2 + 2;
}


/* 0047fa20 size=108 */

int * __thiscall FUN_0047fa20(void *this,int *param_1)

{
  int *piVar1;
  
  if (param_1 != (int *)0x0) {
    piVar1 = FUN_0048a310(*(int **)((int)this + 0x244));
    piVar1[5] = 3;
    piVar1[10] = *param_1;
    piVar1[0xb] = param_1[1];
    piVar1[0xc] = param_1[2];
    return piVar1 + 2;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_ILTPhysics__StartInstantSpecialE_004dc380);
  }
  return (int *)0x0;
}


/* 0047fa90 size=94 */

int * __thiscall FUN_0047fa90(void *this,int param_1)

{
  int *piVar1;
  
  if (param_1 != 0) {
    piVar1 = FUN_0048a310(*(int **)((int)this + 0x244));
    piVar1[5] = 2;
    piVar1[8] = *(int *)(param_1 + 8);
    return piVar1 + 2;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_ILTPhysics__StartSpecialEffectMe_004dc3b0);
  }
  return (int *)0x0;
}


/* 0047fb80 size=356 */

undefined4 __thiscall FUN_0047fb80(void *this,int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 == (int *)0x0) || (iVar1 = (**(code **)(*param_1 + 0x90))(), iVar1 != 0)) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_CLTServer_EndMessage2_004dc3f0
                  );
    }
    return 0x3c;
  }
  switch(param_1[3]) {
  case 0:
    uVar2 = (**(code **)(*(int *)this + 0x16c))(param_1,param_1[7],param_1[5],param_1[6],param_2);
    (**(code **)*param_1)();
    return uVar2;
  case 1:
    uVar2 = (**(code **)(*(int *)this + 0x174))(param_1,(char)param_1[7],param_1[4],param_2);
    (**(code **)*param_1)();
    return uVar2;
  case 2:
    uVar2 = (**(code **)(*(int *)this + 0x168))(param_1[6],param_1);
    (**(code **)*param_1)();
    return uVar2;
  case 3:
    (**(code **)(*(int *)this + 0x178))(param_1,param_1 + 8,param_2);
    (**(code **)*param_1)();
    return 0;
  case 4:
    (**(code **)(*(int *)this + 0x170))(param_1,param_1[7],param_1[5],param_2);
    (**(code **)*param_1)();
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_EndMessage_004dc3f4);
  }
  return 1;
}


