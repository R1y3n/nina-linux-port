/* lithtech.exe decompilation - module Cothineal */
#include "ghidra_types.h"

/* 00402a60 size=248 */

/* repo: Shogo/ObjectDLL/Cothineal.cpp, Blood2/ObjectDLL/GameWeapons.cpp,
   Shogo/ObjectDLL/PVWeaponModel.cpp */

int __cdecl Cothineal_402a60(int *param_1)

{
  int iVar1;
  
  iVar1 = dsys_interface_4359d0(param_1);
  if (iVar1 == 0) {
    FUN_00402b60(param_1);
    iVar1 = FUN_00402890(*(int *)(param_1[0xb] + 0xa1c),(byte *)s_BaseClass_004d567c);
    param_1[6] = iVar1;
    if (iVar1 == 0) {
      FUN_00489880(param_1[0xb],0x34,'x');
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadServerBinaries_004d5654);
      }
      return 0x34;
    }
    FUN_00402d20(param_1);
    iVar1 = (*(code *)param_1[3])(*(undefined4 *)(param_1[0xb] + 0xb38));
    param_1[5] = iVar1;
    if (iVar1 == 0) {
      FUN_00489880(param_1[0xb],0x35,'$');
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadServerBinaries_004d5654);
      }
      return 1;
    }
    iVar1 = FUN_00402da0((int)param_1);
  }
  return iVar1;
}


