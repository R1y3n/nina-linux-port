/* lithtech.exe decompilation - module client_filemgr */
#include "ghidra_types.h"

/* 00404300 size=140 */

/* repo: runtime/client/src/client_filemgr.cpp */

void __cdecl client_filemgr_404300(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *local_1c;
  undefined1 *local_18;
  code *local_14;
  code *local_10;
  code *local_c;
  int local_8;
  undefined4 local_4;
  
  if (param_1 != 0) {
    iVar1 = param_1 + 0x70;
    iVar3 = 100;
    do {
      *(int *)(iVar1 + 4) = iVar1;
      *(int *)iVar1 = iVar1;
      iVar1 = iVar1 + 0xc;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    FUN_00427780((byte *)s_c__de_cache_004d5918,(undefined4 *)(param_1 + 0x6c));
    local_8 = *(int *)(param_1 + 0xe84) + 0x510;
    local_4 = param_2;
    local_1c = &LAB_00404390;
    local_18 = &LAB_00404570;
    local_14 = FUN_00436e70;
    local_10 = FUN_00436e70;
    local_c = FUN_00436e70;
    puVar2 = FUN_004382a0(&local_1c);
    *(undefined4 **)(param_1 + 0xe80) = puVar2;
    FUN_00438330((int)puVar2,param_1);
  }
  return;
}


