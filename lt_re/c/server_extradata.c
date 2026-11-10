/* lithtech.exe decompilation - module server_extradata */
#include "ghidra_types.h"

/* 0047ad60 size=181 */

/* repo: runtime/server/src/server_extradata.cpp */

undefined4 __cdecl server_extradata_47ad60(int param_1,char *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  
  uVar6 = 0xffffffff;
  pcVar8 = param_2;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  iVar3 = FUN_00434ec0(*(int **)(param_1 + 0xb28),param_2,~uVar6 - 1);
  if (iVar3 == 0) {
    return 0x3d;
  }
  puVar4 = (undefined4 *)FUN_00434fd0(iVar3);
  if (2 < DAT_004e4420) {
    uVar5 = FUN_00468720((int)puVar4);
    FUN_00436670((byte *)s_Removing_model_from_resource_lis_004dbd04,uVar5);
  }
  if (puVar4 != (undefined4 *)0x0) {
    (**(code **)*puVar4)(1);
  }
  iVar3 = *(int *)(param_1 + 0x5cc);
  iVar7 = 0;
  if (iVar3 != param_1 + 0x5c8) {
    do {
      iVar2 = *(int *)(iVar3 + 8);
      if (*(undefined4 **)(iVar2 + 0x1f8) == puVar4) {
        *(undefined4 *)(iVar2 + 0x1f8) = *(undefined4 *)(param_1 + 0xd38);
        *(byte *)(iVar2 + 0x1e8) = *(byte *)(iVar2 + 0x1e8) | 8;
        iVar7 = iVar7 + 1;
      }
      iVar3 = *(int *)(iVar3 + 4);
    } while (iVar3 != param_1 + 0x5c8);
    if (iVar7 != 0) {
      *(byte *)(param_3 + 0xc) = *(byte *)(param_3 + 0xc) | 1;
    }
  }
  return 0;
}


