/* lithtech.exe decompilation - module render */
#include "ghidra_types.h"

/* 00470c90 size=607 */

/* repo: runtime/kernel/src/sys/win/render.cpp */

int render_470c90(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined1 local_res0;
  undefined4 uStack00000004;
  undefined2 uStack00000008;
  int iStack0000000c;
  undefined1 uStack00000010;
  undefined1 uStack00000030;
  undefined4 in_stack_00000034;
  int iStack00000134;
  void *in_stack_0000153c;
  int *in_stack_00001540;
  int in_stack_00001544;
  
  FUN_004ba7f0(local_res0);
  FUN_0044df70((int)&uStack00000010);
  *in_stack_00001540 = 0;
  iStack00000134 = 0;
  uStack00000004 = 0;
  uStack00000008 = 0;
  if (*(int *)((int)in_stack_0000153c + 0x24) == 0) {
    return 0x49;
  }
  iStack0000000c = DAT_004e447c;
  piVar1 = FUN_004049b0(*(int *)(DAT_004e447c + 0x1644),*(int *)((int)in_stack_0000153c + 0x24));
  if (piVar1 == (int *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s__r_LoadSystemTexture_004db737 + 1)
      ;
    }
    return 0x16;
  }
  iVar2 = FUN_00436a60(piVar1,(int)in_stack_00001540);
  (**(code **)(*piVar1 + 4))();
  if (iVar2 != 0) {
    return iVar2;
  }
  iVar2 = *in_stack_00001540;
  *(undefined **)(iVar2 + 0xac) = &DAT_004ea834;
  *(int *)(iVar2 + 0xb4) = iVar2;
  piVar1 = (int *)(iVar2 + 0xac);
  *(int **)(iVar2 + 0xb0) = DAT_004ea838;
  *DAT_004ea838 = (int)piVar1;
  *(int **)(*piVar1 + 4) = piVar1;
  DAT_004ea830 = DAT_004ea830 + 1;
  DAT_004ea82c = DAT_004ea82c + *(int *)(*in_stack_00001540 + 0xb8);
  *(int *)((int)in_stack_0000153c + 8) = *in_stack_00001540;
  FUN_0042e180(in_stack_0000153c,(char *)(*in_stack_00001540 + 0x2c));
  *(uint *)((int)in_stack_0000153c + 0x3c) = (uint)*(byte *)(*in_stack_00001540 + 0x24);
  *(void **)(*in_stack_00001540 + 0xc0) = in_stack_0000153c;
  if (in_stack_00001544 != 0) {
    FUN_00471750(in_stack_0000153c,0);
  }
  iStack00000134 = *in_stack_00001540 + 0x2c;
  iVar2 = FUN_00420a70(&uStack00000030,(byte *)s_DetailTex_004db758,0,1);
  if (iVar2 != 0) {
    uStack00000004 = in_stack_00000034;
    uVar3 = FUN_00426ae0(iStack0000000c,(int *)&local_res0);
    *(uint *)((int)in_stack_0000153c + 0x28) = uVar3;
    *(undefined4 *)((int)in_stack_0000153c + 0x2c) = 0;
    return 0;
  }
  iStack00000134 = *in_stack_00001540 + 0x2c;
  iVar2 = FUN_00420a70(&uStack00000030,(byte *)s_EnvMap_004d6d68,0,1);
  if (iVar2 != 0) {
    uStack00000004 = in_stack_00000034;
    uVar3 = FUN_00426ae0(iStack0000000c,(int *)&local_res0);
    *(uint *)((int)in_stack_0000153c + 0x28) = uVar3;
    *(undefined4 *)((int)in_stack_0000153c + 0x2c) = 1;
  }
  iStack00000134 = *in_stack_00001540 + 0x2c;
  iVar2 = FUN_00420a70(&uStack00000030,(byte *)s_EnvMapAlpha_004db74c,0,1);
  if (iVar2 != 0) {
    uStack00000004 = in_stack_00000034;
    uVar3 = FUN_00426ae0(iStack0000000c,(int *)&local_res0);
    *(uint *)((int)in_stack_0000153c + 0x28) = uVar3;
    *(undefined4 *)((int)in_stack_0000153c + 0x2c) = 2;
  }
  return 0;
}


/* 00471240 size=986 */

/* repo: runtime/kernel/src/sys/win/render.cpp, runtime/shared/src/sys/win/renderstruct.h */

/* render_471240: lifted from original x86 -> lt_lifted.c */


