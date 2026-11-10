/* lithtech.exe decompilation - module parse_world_info */
#include "ghidra_types.h"

/* 0046b720 size=79 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: tools/shared/engine/parse_world_info.cpp */

float10 __cdecl parse_world_info_46b720(undefined *param_1)

{
  int iVar1;
  float10 fVar2;
  undefined1 local_res0;
  
  FUN_004ba7f0(local_res0);
  iVar1 = FUN_00420a70(&local_res0,(byte *)s_LightTableRes_004db59c,0,2);
  if (iVar1 == 0) {
    return (float10)_DAT_004cbfa0;
  }
  fVar2 = FUN_004baed0(param_1,param_1);
  return fVar2;
}


