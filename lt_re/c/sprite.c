/* lithtech.exe decompilation - module sprite */
#include "ghidra_types.h"

/* 0049a890 size=507 */

/* repo: runtime/client/src/sprite.cpp */

undefined4 * __cdecl sprite_49a890(int param_1,int *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  void *pvVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *_Dest;
  undefined4 local_42c;
  uint local_428;
  uint local_424;
  uint uStack_420;
  uint uStack_41c;
  uint uStack_418;
  undefined4 uStack_414;
  int local_410;
  undefined1 *local_40c;
  undefined2 local_408 [2];
  uint uStack_404;
  undefined1 auStack_400 [1024];
  
  local_410 = 0;
  local_40c = (undefined1 *)0x0;
  local_408[0] = 0;
  puVar1 = FUN_00430f00(0x14);
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[2] = puVar1;
  puVar1[4] = 1;
  puVar2 = FUN_00430f00(0x3c);
  puVar1[3] = puVar2;
  local_424 = 0;
  for (uVar5 = puVar1[4] * 0xf & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
    *(undefined1 *)puVar2 = 0;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  if (puVar1[4] != 0) {
    local_428 = 0;
    do {
      uVar5 = 0;
      _Dest = (char *)(puVar1[3] + local_428);
      (**(code **)(*param_2 + 8))(&local_42c,4);
      (**(code **)(*param_2 + 8))(&local_424,4);
      (**(code **)(*param_2 + 8))(&uStack_414,4);
      (**(code **)(*param_2 + 8))(local_408 + -0x14,4);
      (**(code **)(*param_2 + 8))(local_408 + -0x16,4);
      pvVar3 = FUN_00430f00(local_42c * 4);
      *(void **)(_Dest + 0x20) = pvVar3;
      _strncpy(_Dest,s_Untitled_004dd460,0x1f);
      *(uint *)(_Dest + 0x24) = local_42c;
      *(uint *)(_Dest + 0x2c) = uStack_41c;
      *(uint *)(_Dest + 0x28) = (int)(1000 / (ulonglong)uStack_41c) * local_42c;
      *(uint *)(_Dest + 0x30) = uStack_404 & 0xff;
      *(uint *)(_Dest + 0x38) = uStack_418 & 0xff;
      *(undefined4 *)(_Dest + 0x34) = uStack_414;
      if (local_42c != 0) {
        do {
          (**(code **)(*param_2 + 8))(&uStack_420,2);
          if (1000 < (ushort)local_428) goto LAB_0049aa68;
          (**(code **)(*param_2 + 8))(local_408,local_428 & 0xffff);
          local_40c = auStack_400;
          local_410 = 1;
          auStack_400[uStack_420 & 0xffff] = 0;
          uVar4 = FUN_00426ae0(param_1,&local_410);
          *(uint *)(*(int *)(_Dest + 0x20) + uVar5 * 4) = uVar4;
          uVar5 = uVar5 + 1;
        } while (uVar5 < local_42c);
      }
      local_424 = local_424 + 1;
      local_428 = local_428 + 0x3c;
    } while (local_424 < (uint)puVar1[4]);
  }
  iVar6 = (**(code **)(*param_2 + 0x10))();
  if (iVar6 == 0) {
    return puVar1;
  }
LAB_0049aa68:
  FUN_0049aa90((undefined *)puVar1);
  return (undefined4 *)0x0;
}


