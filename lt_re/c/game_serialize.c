/* lithtech.exe decompilation - module game_serialize */
#include "ghidra_types.h"

/* 0043c020 size=486 */

/* repo: runtime/server/src/game_serialize.cpp */

undefined4 __cdecl game_serialize_43c020(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int unaff_ESI;
  char *pcVar3;
  undefined1 *puVar4;
  float fVar5;
  undefined1 *puStack_148;
  undefined1 *puStack_144;
  int iStack_140;
  undefined1 *puStack_13c;
  undefined4 uStack_138;
  undefined1 *puStack_134;
  undefined4 uStack_130;
  undefined1 local_120 [2];
  undefined1 auStack_11e [14];
  undefined1 auStack_110 [4];
  undefined **local_10c;
  undefined4 local_108;
  int *local_104;
  int iStack_10;
  uint uStack_c;
  
  local_108 = *(undefined4 *)(param_1 + 0xa14);
  puStack_134 = local_120;
  uStack_130 = 4;
  local_10c = &PTR_LAB_004cc430;
  local_104 = param_2;
  uStack_138 = 0x43c05b;
  (**(code **)(*param_2 + 8))();
  if (unaff_ESI == -1) {
    return 2;
  }
  puStack_13c = local_120 + -4;
  uStack_138 = 4;
  iStack_140 = 0x43c07f;
  (**(code **)(*param_2 + 8))();
  puStack_144 = auStack_110;
  iStack_140 = 0x100;
  puStack_148 = (undefined1 *)0x43c090;
  (**(code **)(*param_2 + 0xc))();
  puStack_148 = puStack_134;
  (**(code **)(*param_2 + 0x14))();
  if (*(char *)(iStack_10 + 0xbc) == '\x01') {
    (**(code **)(*param_2 + 8))(iStack_10 + 0x24c,4);
    piVar1 = *(int **)(*(int *)(param_1 + 0xb38) + 0x10);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x40))(iStack_10 + 0x1d0,local_120 + -8);
    }
  }
  puStack_134 = (undefined1 *)uStack_c;
  uStack_130 = 0;
  puVar4 = local_120 + -8;
  fVar5 = (float)uStack_c;
  (**(code **)(**(int **)(*(int *)(iStack_10 + 400) + 0x20) + 4))();
  (**(code **)(*param_2 + 8))(&uStack_138,4);
  if (iStack_140 == -0x54321051) {
    FUN_004898b0(param_1);
    (**(code **)(*param_2 + 0x14))(puVar4);
    return 0;
  }
  (**(code **)(*param_2 + 0x18))(&puStack_148);
  FUN_00436670((byte *)s_LOAD_ERROR__Couldn_t_restore_obj_004d9704,DAT_004e99c4);
  FUN_00436670((byte *)s_Object_saved__d_bytes_004d96ec,7 - (int)puVar4);
  FUN_00436670((byte *)s_Object_tried_to_load__d_bytes__004d96c8,(int)fVar5 - (int)puVar4);
  if ((uint)fVar5 < 7) {
    iVar2 = 7 - (int)fVar5;
    pcVar3 = s_Restore_UNDER_wrote__d_bytes__004d96a8;
  }
  else {
    iVar2 = (int)fVar5 + -7;
    pcVar3 = s_Restore_OVER_wrote__d_bytes__004d9688;
  }
  FUN_00436670((byte *)pcVar3,iVar2);
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_RestoreNextObject_004d9670);
  }
  return 0x4d;
}


