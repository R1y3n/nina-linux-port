/* lithtech.exe decompilation - module ObjectSearchDlg */
#include "ghidra_types.h"

/* 00437760 size=1234 */

/* repo: tools/DEdit/Dlgs/ObjectSearchDlg.cpp, NOLF/ClientShellDLL/NetInfo.cpp,
   Shogo/ClientShellDLL/NetInfo.cpp */

undefined4 __cdecl ObjectSearchDlg_437760(int *param_1,char param_2)

{
  __builtin_trap(); /* STUB: decompiled body did not compile */
}


/* 00437f90 size=250 */

/* repo: tools/DEdit/Dlgs/ObjectSearchDlg.cpp, NOLF/ClientShellDLL/NetInfo.cpp,
   Shogo/ClientShellDLL/NetInfo.cpp */

void __cdecl ObjectSearchDlg_437f90(HANDLE param_1)

{
  FILETIME FVar1;
  DWORD DVar2;
  _FILETIME local_27c;
  _MEMORYSTATUS local_274;
  _SYSTEM_INFO local_254;
  CHAR local_230 [100];
  CHAR local_1cc [260];
  CHAR local_c8 [200];
  
  GetSystemTimeAsFileTime(&local_27c);
  FVar1.dwHighDateTime = local_27c.dwHighDateTime;
  FVar1.dwLowDateTime = local_27c.dwLowDateTime;
  FUN_00437ef0(local_230,FVar1);
  FUN_00437c80(param_1,s_Error_occurred_at__s__004d938c,(char)local_230);
  DVar2 = GetModuleFileNameA((HMODULE)0x0,local_1cc,0x104);
  if (DVar2 == 0) {
    lstrcpyA(local_1cc,s_Unknown_004d9294);
  }
  lstrcpyA(local_c8,s_Unknown_004d9294);
  FUN_00437c80(param_1,s__s__run_by__s__004d9378,(char)local_1cc);
  GetSystemInfo(&local_254);
  FUN_00437c80(param_1,s__d_processor_s___type__d__004d935c,(char)local_254.dwNumberOfProcessors);
  local_274.dwLength = 0x20;
  GlobalMemoryStatus(&local_274);
  FUN_00437c80(param_1,s__d_MBytes_physical_memory__004d933c,
               (char)(local_274.dwTotalPhys + 0xfffff >> 0x14));
  return;
}


