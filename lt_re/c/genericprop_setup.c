/* lithtech.exe decompilation - module genericprop_setup */
#include "ghidra_types.h"

/* 0043c500 size=124 */

/* repo: runtime/shared/src/genericprop_setup.cpp, sdk/inc/ltproperty.h,
   Shogo/ObjectDLL/RiotServerShell.cpp */

void __cdecl genericprop_setup_43c500(undefined4 *param_1,byte *param_2)

{
  uint uVar1;
  void *this;
  void *this_00;
  undefined *extraout_ECX;
  float10 fVar2;
  float fVar3;
  
  FUN_0043c4c0(param_1);
  FUN_004bb908((char *)param_2,(byte *)s__f__f__f_004d9774,param_1);
  uVar1 = FUN_004c4c00(this,param_2,&DAT_004d976c);
  if (uVar1 == 0) {
    fVar3 = 1.0;
  }
  else {
    uVar1 = FUN_004c4c00(this_00,param_2,(byte *)s_false_004d9764);
    if (uVar1 == 0) {
      fVar3 = 0.0;
    }
    else {
      fVar2 = FUN_004baed0(extraout_ECX,param_2);
      fVar3 = (float)fVar2;
    }
  }
  FUN_0043c580((int)param_1,fVar3);
  _strncpy((char *)(param_1 + 6),(char *)param_2,0x100);
  return;
}


/* 0043c5d0 size=100 */

/* repo: runtime/shared/src/genericprop_setup.cpp, sdk/inc/ltproperty.h,
   Shogo/ObjectDLL/RiotServerShell.cpp */

void __cdecl genericprop_setup_43c5d0(float *param_1,float *param_2)

{
  FUN_0043c4c0(param_1);
  FUN_004b9f62((undefined1 *)(param_1 + 6),(byte *)s__f__f__f_004d9774,SUB84((double)*param_2,0));
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = *param_2;
  param_1[4] = param_2[1];
  param_1[5] = param_2[2];
  return;
}


