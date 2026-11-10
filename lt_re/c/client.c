/* lithtech.exe decompilation - module client */
#include "ghidra_types.h"

/* 004030f0 size=918 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/kernel/src/sys/win/client.cpp, runtime/kernel/src/sys/win/dsys_interface.cpp,
   tools/shared/engine/dsys_interface.cpp */

WPARAM __cdecl client_4030f0(undefined4 param_1,int *param_2)

{
  undefined *puVar1;
  undefined1 *puVar2;
  LPCSTR lpPathName;
  undefined4 *puVar3;
  HANDLE hProcess;
  DWORD DVar4;
  HWND pHVar5;
  int iVar6;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  void *unaff_EDI;
  undefined4 *puVar7;
  char *pcVar8;
  tagRECT *lpRect;
  ulonglong uVar9;
  WNDCLASSA local_7c;
  tagMSG local_54;
  tagRECT local_38;
  tagRECT local_28;
  uint local_18;
  undefined4 uStack_14;
  undefined4 *local_10;
  WPARAM local_c;
  int local_8;
  
  local_10 = &DAT_004e4428;
  puVar7 = &DAT_004e4428;
  for (iVar6 = 0x249; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  local_c = 0;
  puVar2 = FUN_00403020(0x4d5778,param_2[1],(undefined4 *)*param_2);
  if (puVar2 != (undefined1 *)0x0) {
    _DAT_004ecb50 = 1;
  }
  local_8 = 0;
  iVar6 = __setjmp3(&DAT_004e442c,0,unaff_EDI,unaff_ESI,unaff_EBX);
  puVar7 = local_10;
  if (iVar6 == 0) {
    lpPathName = FUN_00403020(0x4d576c,param_2[1],(undefined4 *)*param_2);
    if (lpPathName != (LPCSTR)0x0) {
      SetCurrentDirectoryA(lpPathName);
    }
    puVar7[0x1cb] = 1;
    iVar6 = FUN_004357f0();
    if (iVar6 != 0) {
      if (iVar6 == 1) {
        pcVar8 = s_Unable_to_load_ltmsg_dll__004d5748;
      }
      else {
        pcVar8 = s_Unknown_error_initializing_engin_004d5724;
      }
      MessageBoxA((HWND)0x0,pcVar8,s_Error_004d5764,0);
      FUN_00435860();
      return 0xffffffff;
    }
    puVar7[0x12] = param_1;
    puVar7[0x13] = s_LithTech_004d5718;
    puVar3 = clientmgr_411920();
    puVar7[0x15] = puVar3;
    puVar7[0x18] = 1;
    puVar2 = FUN_00403020(0x4d570c,param_2[1],(undefined4 *)*param_2);
    puVar7[0x14] = puVar2;
    if (puVar2 == (undefined1 *)0x0) {
      puVar7[0x14] = s_LithTech_004d5718;
    }
    puVar2 = FUN_00403020(0x4d56fc,param_2[1],(undefined4 *)*param_2);
    puVar7[0x17] = (uint)(puVar2 != (undefined1 *)0x0);
    local_7c.style = 0xb;
    local_7c.lpfnWndProc = (WNDPROC)&LAB_00403610;
    local_7c.cbClsExtra = 0;
    local_7c.cbWndExtra = 0;
    local_7c.hInstance = (HINSTANCE)puVar7[0x12];
    local_7c.hIcon = LoadIconA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    local_7c.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    local_7c.hbrBackground = GetStockObject(4);
    local_7c.lpszMenuName = (LPCSTR)0x0;
    local_7c.lpszClassName = (LPCSTR)puVar7[0x13];
    RegisterClassA(&local_7c);
    lpRect = &local_28;
    pHVar5 = GetDesktopWindow();
    GetWindowRect(pHVar5,lpRect);
    pHVar5 = CreateWindowExA(0,(LPCSTR)puVar7[0x13],(LPCSTR)puVar7[0x14],0x10810000,
                             ((local_28.right - local_28.left) + -0x140) / 2,
                             ((local_28.bottom - local_28.top) + -200) / 2,0x140,200,(HWND)0x0,
                             (HMENU)0x0,(HINSTANCE)puVar7[0x12],(LPVOID)0x0);
    puVar7[0x11] = pHVar5;
    iVar6 = client_403490((int)puVar7,param_2);
    if (iVar6 != 0) {
      *puVar7 = 1;
      ShowWindow((HWND)puVar7[0x11],1);
      UpdateWindow((HWND)puVar7[0x11]);
      iVar6 = FUN_00411410((void *)puVar7[0x15]);
      while (iVar6 == 0) {
        if (DAT_004e98d4 != 0) {
          FUN_00436670((byte *)s_Setting_process_to_high_priority_004d56d8,unaff_EDI);
          DVar4 = 0x80;
          hProcess = GetCurrentProcess();
          SetPriorityClass(hProcess,DVar4);
        }
        if (DAT_004e98cc != 0) {
          DVar4 = timeGetTime();
          uStack_14 = 0;
          local_18 = DVar4 - DAT_004e4d4c;
          FUN_00436670((byte *)s_Running_for___1f_seconds_004d56bc,
                       SUB84((double)((float)local_18 * _DAT_004cb4e4),0));
        }
        if ((DAT_004d828c != 0) && (DAT_004e448c == 0)) {
          GetWindowRect((HWND)puVar7[0x11],&local_38);
          SetCursorPos((local_28.right - local_28.left) / 2,(local_28.bottom - local_28.top) / 2);
        }
        iVar6 = PeekMessageA(&local_54,(HWND)0x0,0,0,1);
        while (iVar6 != 0) {
          if (local_54.message == 0x12) {
            local_c = local_54.wParam;
            goto LAB_004033f6;
          }
          TranslateMessage(&local_54);
          DispatchMessageA(&local_54);
          iVar6 = PeekMessageA(&local_54,(HWND)0x0,0,0,1);
        }
        iVar6 = FUN_00411410((void *)puVar7[0x15]);
      }
    }
  }
  else {
    local_8 = 1;
  }
LAB_004033f6:
  if (*(char *)(puVar7 + 0x1cc) != '\0') {
    FUN_00471640(puVar7[0x15],2);
    FUN_00436710((LPCSTR)(puVar7 + 0x1cc),(LPCSTR)puVar7[0x14]);
  }
  *puVar7 = 0;
  puVar1 = (undefined *)puVar7[0x15];
  if (puVar1 != (undefined *)0x0) {
    clientmgr_411d80(puVar1);
    FUN_00430df0(puVar1);
  }
  puVar7[0x15] = 0;
  DestroyWindow((HWND)puVar7[0x11]);
  FUN_00435860();
  if (local_8 != 0) {
    ShowWindow((HWND)puVar7[0x11],0);
    uVar9 = (ulonglong)(uint)puVar7[0x14];
    pcVar8 = s_Out_of_memory_004d56ac;
    pHVar5 = GetDesktopWindow();
    MessageBoxA(pHVar5,pcVar8,(LPCSTR)uVar9,(UINT)(uVar9 >> 0x20));
  }
  return local_c;
}


/* 00403490 size=375 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/kernel/src/sys/win/client.cpp, NOLF2/ClientShellDLL/TRON/ScreenControls.cpp,
   NOLF/ClientShellDLL/FolderDisplay.cpp */

undefined4 __cdecl client_403490(int param_1,int *param_2)

{
  void *this;
  int *piVar1;
  undefined1 *puVar2;
  uint uVar3;
  LPCSTR lpPathName;
  char *pcVar4;
  DWORD DVar5;
  DWORD DVar6;
  uint uVar7;
  int iVar8;
  ushort in_FPUControlWord;
  int local_80 [20];
  char local_30 [32];
  int local_10;
  undefined4 uStack_c;
  ushort local_6;
  
  piVar1 = param_2;
  local_6 = in_FPUControlWord & 0xfcff;
  puVar2 = FUN_00403020(0x4d57ec,param_2[1],(undefined4 *)*param_2);
  *(uint *)(param_1 + 0x74) = (uint)(puVar2 != (undefined1 *)0x0);
  puVar2 = FUN_00403020(0x4d57e4,param_2[1],(undefined4 *)*param_2);
  *(undefined1 **)(param_1 + 0x7c) = puVar2;
  uVar7 = 0;
  iVar8 = 0;
  if (0 < param_2[1] + -1) {
    param_2 = local_80;
    do {
      this = *(void **)(*piVar1 + iVar8 * 4);
      uVar3 = FUN_004c4c00(this,this,&DAT_004d57dc);
      if (uVar3 == 0) {
        uVar7 = uVar7 + 1;
        *param_2 = *(int *)(*piVar1 + 4 + iVar8 * 4);
        param_2 = param_2 + 1;
        if (0x13 < uVar7) break;
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < piVar1[1] + -1);
  }
  puVar2 = FUN_00403020(0x4d57d4,piVar1[1],(undefined4 *)*piVar1);
  if (puVar2 != (undefined1 *)0x0) {
    *(undefined4 *)(param_1 + 0x72c) = 0;
  }
  lpPathName = FUN_00403020(0x4d576c,piVar1[1],(undefined4 *)*piVar1);
  if (lpPathName != (LPCSTR)0x0) {
    SetCurrentDirectoryA(lpPathName);
  }
  pcVar4 = FUN_00403020(0x4d57cc,piVar1[1],(undefined4 *)*piVar1);
  if (pcVar4 == (LPCSTR)0x0) {
    pcVar4 = s_autoexec_cfg_004d57bc;
  }
  DVar5 = timeGetTime();
  uVar7 = clientmgr_410250(*(void **)(param_1 + 0x54),local_80,uVar7,pcVar4,piVar1);
  if (uVar7 == 0) {
    version_info_4a1430((void *)(*(int *)(param_1 + 0x54) + 0x12e0),local_30,0x20);
    DVar6 = timeGetTime();
    uStack_c = 0;
    local_10 = DVar6 - DVar5;
    FUN_004317e0();
    return 1;
  }
  return 0;
}


/* 00403b50 size=938 */

/* repo: runtime/kernel/src/sys/win/client.cpp, NOLF2/Shared/AssertMgr.cpp,
   runtime/kernel/src/sys/win/dsys_interface.cpp */

/* client_403b50: lifted from original x86 -> lt_lifted.c */


