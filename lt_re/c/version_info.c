/* lithtech.exe decompilation - module version_info */
#include "ghidra_types.h"

/* 004a1430 size=85 */

/* repo: tools/shared/engine/version_info.cpp, runtime/shared/src/version_info.cpp,
   tools/utils/SetVersionCode/SetVersionCode.cpp */

void __thiscall version_info_4a1430(void *this,char *param_1,int param_2)

{
  char local_200 [512];
  
  FUN_004b9f62(local_200,(byte *)s__lu__lu_004ddeb4,*(undefined4 *)this);
  if (param_2 != 0) {
    _strncpy(param_1,local_200,param_2 - 1);
    param_1[param_2 + -1] = '\0';
  }
  return;
}


