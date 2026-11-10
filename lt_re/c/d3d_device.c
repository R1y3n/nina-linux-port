/* lithtech.exe decompilation - module d3d_device */
#include "ghidra_types.h"

/* 0049bb80 size=94 */

/* repo: runtime/render_a/src/sys/d3d/d3d_device.cpp, NOLF2/ClientShellDLL/TRON/ScreenJoin.cpp,
   runtime/kernel/net/src/sys/win/udpdriver.cpp */

void __fastcall d3d_device_49bb80(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cd9f0;
  FUN_0049bd30(param_1);
  param_1[0x2a] = &PTR_LAB_004cc3d0;
  param_1[0x28] = 0;
  param_1[0x27] = 0;
  param_1[0x14] = &PTR_LAB_004cda5c;
  if (param_1[0x15] != 0) {
    FUN_0049efc0(&DAT_004ecc58,param_1[0x15],param_1[0x16] + param_1[0x17]);
    param_1[0x15] = 0;
    param_1[0x17] = 0;
  }
  param_1[0x16] = 0;
  *param_1 = &PTR_LAB_004cc364;
  return;
}


