/* lithtech.exe decompilation - module binkvideomgrimpl */
#include "ghidra_types.h"

/* 00401960 size=500 */

/* repo: runtime/kernel/src/sys/win/binkvideomgrimpl.cpp */

undefined4 __fastcall binkvideomgrimpl_401960(int param_1)

{
  HMODULE hModule;
  FARPROC pFVar1;
  int iVar2;
  undefined4 unaff_ESI;
  
  hModule = LoadLibraryA(s_Binkw32_dll_004d54ac);
  *(HMODULE *)(param_1 + 0x48) = hModule;
  if (hModule == (HMODULE)0x0) {
    FUN_00436670((byte *)s_Unable_to_find_Binkw32_dll__vide_004d5474,unaff_ESI);
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_BinkVideoMgr__Init_004d545c);
    }
    return 0x16;
  }
  pFVar1 = GetProcAddress(hModule,s__BinkSetSoundSystem_8_004d5444);
  *(FARPROC *)(param_1 + 0x14) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkOpenMiles_4_004d5430);
  *(FARPROC *)(param_1 + 0x18) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkOpenDirectSound_4_004d5418);
  *(FARPROC *)(param_1 + 0x1c) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkSetSoundTrack_4_004d5400);
  *(FARPROC *)(param_1 + 0x20) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkOpen_8_004d53f4);
  *(FARPROC *)(param_1 + 0x24) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkClose_4_004d53e4);
  *(FARPROC *)(param_1 + 0x28) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkWait_4_004d53d8);
  *(FARPROC *)(param_1 + 0x2c) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkCopyToBuffer_28_004d53c0);
  *(FARPROC *)(param_1 + 0x30) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkDoFrame_4_004d53b0);
  *(FARPROC *)(param_1 + 0x34) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkNextFrame_4_004d539c);
  *(FARPROC *)(param_1 + 0x38) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkIsSoftwareCursor_8_004d5384);
  *(FARPROC *)(param_1 + 0x3c) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkCheckCursor_20_004d5370);
  *(FARPROC *)(param_1 + 0x40) = pFVar1;
  pFVar1 = GetProcAddress(*(HMODULE *)(param_1 + 0x48),s__BinkRestoreCursor_4_004d5358);
  *(FARPROC *)(param_1 + 0x44) = pFVar1;
  if (((((*(int *)(param_1 + 0x14) != 0) && (*(int *)(param_1 + 0x24) != 0)) &&
       (*(int *)(param_1 + 0x28) != 0)) &&
      ((((*(int *)(param_1 + 0x2c) != 0 && (*(int *)(param_1 + 0x30) != 0)) &&
        ((*(int *)(param_1 + 0x34) != 0 &&
         ((*(int *)(param_1 + 0x38) != 0 && (*(int *)(param_1 + 0x18) != 0)))))) &&
       (*(int *)(param_1 + 0x1c) != 0)))) &&
     (((*(int *)(param_1 + 0x20) != 0 && (*(int *)(param_1 + 0x3c) != 0)) &&
      (*(int *)(param_1 + 0x40) != 0)))) {
    iVar2 = FUN_00410170();
    if (*(int *)(iVar2 + 0x124) == 0) {
      (**(code **)(param_1 + 0x14))(*(undefined4 *)(param_1 + 0x1c),0);
      return 0;
    }
    iVar2 = FUN_00410170();
    (**(code **)(param_1 + 0x14))(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(iVar2 + 0x130));
    return 0;
  }
  FUN_00436670((byte *)s_Invalid_Binkw32_dll__video_playb_004d5328,unaff_ESI);
  FreeLibrary(*(HMODULE *)(param_1 + 0x48));
  *(undefined4 *)(param_1 + 0x48) = 0;
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_BinkVideoMgr__Init_004d545c);
  }
  return 0x49;
}


/* 00401e10 size=156 */

/* repo: runtime/kernel/src/sys/win/binkvideomgrimpl.cpp */

undefined4 __thiscall
binkvideomgrimpl_401e10(void *this,undefined4 param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0;
  if (param_3 == 1) {
    (**(code **)(*(int *)((int)this + 0x1c) + 0x20))(0xffffffff);
    uVar1 = 0x4000;
  }
  if ((param_2 & 2) != 0) {
    uVar1 = uVar1 | 0x20000000;
  }
  if ((param_2 & 4) != 0) {
    uVar1 = uVar1 | 0x800000;
  }
  if ((param_2 & 8) != 0) {
    uVar1 = uVar1 | 0x4000000;
  }
  iVar2 = (**(code **)(*(int *)((int)this + 0x1c) + 0x24))(param_1,uVar1);
  *(int *)((int)this + 0x18) = iVar2;
  if (iVar2 != 0) {
    *(int *)((int)this + 0x6c) = param_3;
    *(uint *)((int)this + 0x68) = param_2;
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_BinkVideoInst__Init_004d54cc);
  }
  return 0x16;
}


