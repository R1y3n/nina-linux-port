/* lithtech.exe decompilation - module WorldProperties */
#include "ghidra_types.h"

/* 0046b5f0 size=296 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: FEAR/ObjectDLL/WorldProperties.cpp, tools/shared/model/model.cpp,
   tools/shared/engine/parse_world_info.cpp */

undefined4 __cdecl WorldProperties_46b5f0(undefined *param_1,byte *param_2,byte *param_3)

{
  float fVar1;
  int iVar2;
  undefined *extraout_ECX;
  undefined *extraout_ECX_00;
  float10 fVar3;
  undefined1 local_res0;
  float *in_stack_00001510;
  
  FUN_004ba7f0(local_res0);
  *in_stack_00001510 = 0.0;
  in_stack_00001510[1] = 0.0;
  in_stack_00001510[2] = 0.0;
  iVar2 = FUN_00420a70(&local_res0,(byte *)s_AmbientLight_004daa5c,0,4);
  if (iVar2 == 0) {
    return 0;
  }
  fVar3 = FUN_004baed0(param_1,param_1);
  *in_stack_00001510 = (float)fVar3;
  fVar3 = FUN_004baed0(extraout_ECX,param_2);
  in_stack_00001510[1] = (float)fVar3;
  fVar3 = FUN_004baed0(extraout_ECX_00,param_3);
  in_stack_00001510[2] = (float)fVar3;
  if (_DAT_004cb524 <= *in_stack_00001510) {
    if (*in_stack_00001510 <= _DAT_004cbaf4) {
      fVar1 = *in_stack_00001510;
    }
    else {
      fVar1 = _DAT_004cbaf4;
    }
  }
  else {
    fVar1 = _DAT_004cb524;
  }
  *in_stack_00001510 = fVar1;
  if (_DAT_004cb524 <= in_stack_00001510[1]) {
    if (in_stack_00001510[1] <= _DAT_004cbaf4) {
      fVar1 = in_stack_00001510[1];
    }
    else {
      fVar1 = _DAT_004cbaf4;
    }
  }
  else {
    fVar1 = _DAT_004cb524;
  }
  in_stack_00001510[1] = fVar1;
  if (fVar3 < (float10)_DAT_004cb524) {
    in_stack_00001510[2] = _DAT_004cb524;
    return 1;
  }
  if ((float10)_DAT_004cbaf4 < fVar3) {
    fVar3 = (float10)_DAT_004cbaf4;
  }
  in_stack_00001510[2] = (float)fVar3;
  return 1;
}


