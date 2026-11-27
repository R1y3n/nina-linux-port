/* lithtech.exe decompilation - module setupobject */
#include "ghidra_types.h"

/* 0048d2d0 size=404 */

/* repo: runtime/client/src/setupobject.cpp */

undefined4 __cdecl setupobject_48d2d0(int param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  char cVar6;
  
  *param_3 = 0;
  puVar2 = FUN_004046f0(*(int *)(param_1 + 0x1644),param_2);
  piVar3 = FUN_004047a0(*(int *)(param_1 + 0x1644),param_2,'\x02');
  cVar6 = (char)puVar2;
  if (piVar3 == (int *)0x0) {
    FUN_004267b0(param_1,0x2d,cVar6);
    FUN_004356e0();
  }
  else {
    if (*piVar3 != 0) {
      *param_3 = *piVar3;
      return 0;
    }
    piVar4 = FUN_004049e0(*(int *)(param_1 + 0x1644),param_2);
    if (piVar4 != (int *)0x0) {
      if (1 < DAT_004e4420) {
        puVar2 = FUN_004046f0(*(int *)(param_1 + 0x1644),param_2);
        FUN_00436670((byte *)s_Loading_sprite___s_004dcdbc,puVar2);
      }
      piVar5 = sprite_49a890(param_1,piVar4);
      if (piVar5 != (int *)0x0) {
        *piVar3 = (int)piVar5;
        piVar5[2] = (int)piVar5;
        *piVar5 = param_1 + 0x1214;
        puVar1 = *(undefined4 **)(param_1 + 0x1218);
        piVar5[1] = (int)puVar1;
        *puVar1 = piVar5;
        *(int **)(*piVar5 + 4) = piVar5;
        *(int *)(param_1 + 0x1210) = *(int *)(param_1 + 0x1210) + 1;
        (**(code **)(*piVar4 + 4))();
        *param_3 = (int)piVar5;
        return 0;
      }
      FUN_004267b0(param_1,0x2e,cVar6);
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadSprite_004dcd98);
      }
      return 0x2e;
    }
    FUN_004267b0(param_1,0x2d,cVar6);
    FUN_004356e0();
  }
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadSprite_004dcd98);
  }
  return 0x2d;
}


