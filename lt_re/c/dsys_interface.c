/* lithtech.exe decompilation - module dsys_interface */
#include "ghidra_types.h"

/* 00433c20 size=94 */

/* repo: tools/shared/engine/dsys_interface.cpp, libs/ltmem/ltmemtrack.cpp */

undefined * __thiscall dsys_interface_433c20(void *this,byte param_1)

{
  int iVar1;
  
  iVar1 = *(int *)((int)this + 0xc);
  *(undefined ***)((int)this + 8) = &PTR_LAB_004cc2e8;
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar1);
    }
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 *)((int)this + 0x14) = 0;
  }
  *(undefined4 *)((int)this + 0x10) = 0;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004356f0 size=242 */

/* repo: tools/shared/engine/dsys_interface.cpp, runtime/kernel/src/sys/win/dsys_interface.cpp */

/* dsys_interface_4356f0: lifted from original x86 -> lt_lifted.c */


/* 00435840 size=26 */

/* repo: tools/shared/engine/dsys_interface.cpp, runtime/kernel/src/sys/win/dsys_interface.cpp */

bool dsys_interface_435840(void)

{
  DAT_004e9824 = LoadLibraryA(s_ltmsg_dll_004d8058);
  return DAT_004e9824 != (HMODULE)0x0;
}


/* 004359d0 size=942 */

/* repo: tools/shared/engine/dsys_interface.cpp, libs/rezmgr/rezutils.cpp,
   runtime/kernel/src/sys/win/dsys_interface.cpp */

undefined4 __cdecl dsys_interface_4359d0(undefined4 *param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  DWORD DVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  int local_1cc;
  CHAR local_1c8 [256];
  CHAR local_c8 [200];
  
  iVar3 = param_1[0xb];
  DVar4 = GetTempPathA(200,local_c8);
  if (DVar4 == 0) {
    uVar6 = 0xffffffff;
    pcVar8 = &DAT_004d813c;
    do {
      pcVar9 = pcVar8;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar9 = pcVar8 + 1;
      cVar2 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar8 = pcVar9 + -uVar6;
    pcVar9 = local_c8;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar9 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  iVar5 = FUN_004358c0(iVar3,local_c8,s_object_lto_004d8130,local_1c8,0x100);
  if (iVar5 == 0) {
    iVar5 = classbind_402730(local_1c8,*(undefined4 *)(iVar3 + 0xb38),param_1,&local_1cc);
    if (iVar5 != -1) {
      if (iVar5 == 0) {
        FUN_00489880(iVar3,0x36,'0');
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_LoadObjectsInDirectory_004d8080);
        }
      }
      else {
        if (iVar5 != 1) {
          FUN_00489880(iVar3,0x37,'0');
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                         s_LoadObjectsInDirectory_004d8080);
          }
          return 0x37;
        }
        FUN_00489880(iVar3,0x36,'0');
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_LoadObjectsInDirectory_004d8080);
          return 0x36;
        }
      }
      return 0x36;
    }
    piVar1 = param_1 + 2;
    iVar5 = FUN_0048e270(local_1c8,s_ServerShell_004d8124,piVar1,2,&local_1cc);
    if (iVar5 == 0) {
      FUN_00489880(iVar3,0x1d,(char)local_1c8);
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadServerObjects_004d80fc);
      }
      return 0x1d;
    }
    if (iVar5 == 1) {
      FUN_00489880(iVar3,0x1e,(char)local_1c8);
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadServerObjects_004d80fc);
      }
      return 0x1e;
    }
    if (iVar5 == 2) {
      FUN_00489880(iVar3,0x1f,(char)local_1c8);
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadServerObjects_004d80fc);
      }
      return 0x1f;
    }
    FUN_0048e3c0(*piVar1,param_1 + 3,param_1 + 4);
    iVar5 = FUN_004358c0(iVar3,local_c8,s_sres_dll_004d80c0,local_1c8,0x100);
    if ((iVar5 == 0) && (iVar5 = FUN_00401790(local_1c8,param_1 + 1), iVar5 == -1)) {
      return 0;
    }
    FUN_0048e3a0((undefined4 *)*piVar1);
    *piVar1 = 0;
    FUN_00489880(iVar3,0x4c,-0x40);
    FUN_004356e0();
  }
  else {
    FUN_00489880(iVar3,0x4c,'0');
    FUN_004356e0();
  }
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadServerObjects_004d80fc);
  }
  return 0x4c;
}


/* 00435de0 size=184 */

/* repo: tools/shared/engine/dsys_interface.cpp */

/* dsys_interface_435de0: lifted from original x86 -> lt_lifted.c */


/* 004361b0 size=816 */

/* repo: tools/shared/engine/dsys_interface.cpp, libs/rezmgr/rezutils.cpp,
   runtime/kernel/src/sys/win/dsys_interface.cpp */

undefined4 __cdecl dsys_interface_4361b0(int param_1)

{
  int *piVar1;
  char cVar2;
  DWORD DVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  code *local_1d4;
  int local_1d0;
  undefined4 local_1cc;
  CHAR local_1c8 [200];
  CHAR local_100 [256];
  
  piVar1 = (int *)(param_1 + 0x61c);
  *(undefined4 *)(param_1 + 0x614) = 0;
  *(undefined4 *)(param_1 + 0x618) = 0;
  *piVar1 = 0;
  DVar3 = GetTempPathA(200,local_1c8);
  if (DVar3 == 0) {
    uVar5 = 0xffffffff;
    pcVar7 = &DAT_004d813c;
    do {
      pcVar8 = pcVar7;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar8 = pcVar7 + 1;
      cVar2 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar2 != '\0');
    uVar5 = ~uVar5;
    pcVar7 = pcVar8 + -uVar5;
    pcVar8 = local_1c8;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  iVar4 = FUN_00436090(param_1,local_1c8,s_cshell_dll_004d81c0,local_100,0x100);
  if (iVar4 == 0) {
    iVar4 = FUN_0048e270(local_100,s_ClientShell_004d7d04,piVar1,2,&local_1d0);
    if (iVar4 != -1) {
      if (iVar4 == 0) {
        FUN_004267b0(param_1,0x1d,-0x40);
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_InitClientShellDE_004d81ac);
        }
        return 0x1d;
      }
      if (iVar4 == 1) {
        FUN_004267b0(param_1,0x1e,-0x40);
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_InitClientShellDE_004d81ac);
        }
        return 0x1e;
      }
      FUN_004267b0(param_1,0x1f,-0x40);
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_InitClientShellDE_004d81ac);
      }
      return 0x1f;
    }
    iVar4 = FUN_00436090(param_1,local_1c8,s_cres_dll_004d81a0,local_100,0x100);
    if ((iVar4 == 0) &&
       (iVar4 = FUN_00401790(local_100,(undefined4 *)(param_1 + 0x614)), iVar4 == -1)) {
      FUN_00436090(param_1,local_1c8,s_cresl_dll_004d8194,local_100,0x100);
      FUN_00401790(local_100,(undefined4 *)(param_1 + 0x618));
      FUN_0048e3c0(*piVar1,&local_1d4,&local_1cc);
      iVar4 = (*local_1d4)(*(undefined4 *)(param_1 + 0x4c4));
      *(int *)(param_1 + 0x620) = iVar4;
      if (iVar4 != 0) {
        RenderPassDlg_437560(param_1);
        return 0;
      }
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_InitClientShellDE_004d81ac);
      }
      return 0x20;
    }
    FUN_0048e3a0((undefined4 *)*piVar1);
    *piVar1 = 0;
    FUN_004267b0(param_1,0x4c,-0x60);
    FUN_004356e0();
  }
  else {
    FUN_004267b0(param_1,0x4c,-0x40);
    FUN_004356e0();
  }
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_InitClientShellDE_004d81ac);
  }
  return 0x4c;
}


