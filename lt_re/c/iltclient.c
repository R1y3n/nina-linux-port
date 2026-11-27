/* lithtech.exe decompilation - module iltclient */
#include "ghidra_types.h"

/* 00408350 size=340 */

/* repo: sdk/inc/iltclient.h, runtime/kernel/net/src/sys/win/udpdriver.cpp,
   runtime/client/src/clientde_impl.cpp */

undefined4 __cdecl iltclient_408350(int param_1,float *param_2,float *param_3)

{
  float fVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  ushort uVar6;
  
  if ((((*(int *)(DAT_004e516c + 0x161c) == 0) || (*(int *)(DAT_004e516c + 0x1cc) == 0)) ||
      (param_1 == 0)) || ((param_2 == (float *)0x0 || (param_3 == (float *)0x0)))) {
    return 0;
  }
  iVar3 = *(int *)(param_1 + 0x2c);
  iVar4 = *(int *)(param_1 + 0x28);
  *param_2 = 100000.0;
  param_2[1] = 100000.0;
  param_2[2] = 100000.0;
  *param_3 = -100000.0;
  param_3[1] = -100000.0;
  param_3[2] = -100000.0;
  uVar2 = *(ushort *)(iVar3 + 0x38);
  while (uVar2 != 0xffff) {
    uVar6 = 0;
    iVar3 = *(int *)(*(int *)(iVar4 + 0xa0) + (uint)uVar2 * 4);
    if (*(short *)(iVar3 + 0x54) != 0) {
      do {
        pfVar5 = *(float **)(iVar3 + 0x58 + (uint)uVar6 * 0x18);
        if (*pfVar5 <= *param_2) {
          fVar1 = *pfVar5;
        }
        else {
          fVar1 = *param_2;
        }
        *param_2 = fVar1;
        if (pfVar5[1] <= param_2[1]) {
          fVar1 = pfVar5[1];
        }
        else {
          fVar1 = param_2[1];
        }
        param_2[1] = fVar1;
        if (pfVar5[2] <= param_2[2]) {
          fVar1 = pfVar5[2];
        }
        else {
          fVar1 = param_2[2];
        }
        param_2[2] = fVar1;
        if (*param_3 <= *pfVar5) {
          fVar1 = *pfVar5;
        }
        else {
          fVar1 = *param_3;
        }
        *param_3 = fVar1;
        if (param_3[1] <= pfVar5[1]) {
          fVar1 = pfVar5[1];
        }
        else {
          fVar1 = param_3[1];
        }
        param_3[1] = fVar1;
        if (param_3[2] <= pfVar5[2]) {
          fVar1 = pfVar5[2];
        }
        else {
          fVar1 = param_3[2];
        }
        param_3[2] = fVar1;
        uVar6 = uVar6 + 1;
      } while (uVar6 < *(ushort *)(iVar3 + 0x54));
    }
    uVar2 = *(ushort *)(iVar3 + 0x44);
  }
  return 1;
}


/* 004649d0 size=36 */

/* repo: sdk/inc/iltclient.h, Shogo/ClientShellDLL/NetStart.cpp,
   Blood2/ClientShellDLL/BloodClientShell.cpp */

undefined4 __fastcall iltclient_4649d0(void *param_1)

{
  FUN_00464a00(param_1);
  udpdriver_465470(param_1,(byte *)s_dplay2_004d5f04);
  udpdriver_465470(param_1,(byte *)s_internet_004d5ec0);
  return 0;
}


