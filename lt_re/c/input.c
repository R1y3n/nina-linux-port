/* lithtech.exe decompilation - module input */
#include "ghidra_types.h"

/* 00440640 size=14 */

/* repo: runtime/kernel/src/sys/win/input.cpp */

bool input_440640(void)

{
  return DAT_004e9cb8 != 0;
}


/* 00440730 size=274 */

/* repo: runtime/kernel/src/sys/win/input.cpp, FEAR/ClientShellDLL/ScreenConfigure.cpp,
   Blood2/ClientShellDLL/MenuControls.cpp */

char * __cdecl input_440730(int param_1)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  bool bVar6;
  
  piVar1 = (int *)(param_1 + 4);
  iVar3 = 4;
  bVar6 = true;
  piVar4 = piVar1;
  piVar5 = &DAT_004cee4c;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar4 == *piVar5;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return s_X_axis_004d9ad4;
  }
  iVar3 = 4;
  bVar6 = true;
  piVar4 = piVar1;
  piVar5 = &DAT_004cee3c;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar4 == *piVar5;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return s_Y_axis_004d9acc;
  }
  iVar3 = 4;
  bVar6 = true;
  piVar4 = piVar1;
  piVar5 = &DAT_004cee2c;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar4 == *piVar5;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return s_Z_axis_004d9ac4;
  }
  iVar3 = 4;
  bVar6 = true;
  piVar4 = piVar1;
  piVar5 = &DAT_004cee1c;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar4 == *piVar5;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return s_X_axis_rotation_004d9ab4;
  }
  iVar3 = 4;
  bVar6 = true;
  piVar4 = piVar1;
  piVar5 = &DAT_004cee0c;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar4 == *piVar5;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return s_Y_axis_rotation_004d9aa4;
  }
  iVar3 = 4;
  bVar6 = true;
  piVar4 = piVar1;
  piVar5 = &DAT_004cedfc;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar4 == *piVar5;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return s_Z_axis_rotation_004d9a94;
  }
  iVar3 = 4;
  bVar6 = true;
  piVar4 = piVar1;
  piVar5 = &DAT_004cedec;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar4 == *piVar5;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return s_slider_004d9a8c;
  }
  iVar3 = 4;
  bVar6 = true;
  piVar4 = piVar1;
  piVar5 = &DAT_004ceddc;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar4 == *piVar5;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return s_button_004d9a84;
  }
  iVar3 = 4;
  bVar6 = true;
  piVar4 = piVar1;
  piVar5 = &DAT_004cedcc;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar4 == *piVar5;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return &DAT_004d9a80;
  }
  iVar3 = 4;
  bVar6 = true;
  piVar4 = &DAT_004cedbc;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *piVar1 == *piVar4;
    piVar1 = piVar1 + 1;
    piVar4 = piVar4 + 1;
  } while (bVar6);
  pcVar2 = s_POV_hat_004d9a78;
  if (!bVar6) {
    pcVar2 = s_unknown_004d9a70;
  }
  return pcVar2;
}


/* 00440850 size=443 */

/* repo: runtime/kernel/src/sys/win/input.cpp, NOLF/ClientShellDLL/FolderCustomControls.cpp */

undefined4 __cdecl input_440850(undefined4 param_1,byte *param_2)

{
  int *piVar1;
  bool bVar2;
  undefined3 extraout_var;
  int *piVar3;
  uint uVar4;
  int iVar5;
  void *this;
  void *this_00;
  int **ppiVar6;
  undefined4 uVar7;
  int *apiStack_40 [2];
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int *piStack_18;
  undefined4 *puStack_c;
  
  bVar2 = input_440640();
  if ((CONCAT31(extraout_var,bVar2) != 0) &&
     (piVar3 = (int *)input_440a10(this,param_2), piVar3 != (int *)0x0)) {
    if (*piVar3 != 0) {
      return 1;
    }
    local_28 = piVar3[0x1c];
    local_24 = piVar3[0x1d];
    local_20 = piVar3[0x1e];
    local_1c = piVar3[0x1f];
    piVar3[0xbf] = 0;
    apiStack_40[1] = (int *)0x4408bd;
    uVar4 = FUN_004c4c00(piVar3 + 0x1c,param_2,(byte *)s___mouse_004d9ae8);
    if (uVar4 == 0) {
      piVar3[0xbf] = 1;
      local_28 = DAT_004ced9c;
      local_24 = DAT_004ceda0;
      local_20 = DAT_004ceda4;
      local_1c = DAT_004ceda8;
    }
    else {
      apiStack_40[1] = (int *)0x440902;
      uVar4 = FUN_004c4c00(this_00,param_2,(byte *)s___keyboard_004d9adc);
      if (uVar4 == 0) {
        local_28 = DAT_004ced8c;
        local_24 = DAT_004ced90;
        local_20 = DAT_004ced94;
        local_1c = DAT_004ced98;
      }
    }
    apiStack_40[1] = &local_28;
    apiStack_40[0] = DAT_004e9cb8;
    iVar5 = (**(code **)(*DAT_004e9cb8 + 0xc))();
    if (iVar5 == 0) {
      iVar5 = (**(code **)*puStack_c)(puStack_c,&DAT_004cee5c,piVar3);
      if (iVar5 != 0) {
        (**(code **)(*piStack_18 + 8))(piStack_18);
        return 0;
      }
      if ((char)piVar3[0x20] == '\x04') {
        uVar7 = 5;
      }
      else {
        uVar7 = 6;
      }
      iVar5 = (**(code **)(*(int *)*piVar3 + 0x34))((int *)*piVar3,DAT_004e9cb4,uVar7);
      if (iVar5 == 0) {
        ppiVar6 = apiStack_40;
        for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
          *ppiVar6 = (int *)0x0;
          ppiVar6 = ppiVar6 + 1;
        }
        apiStack_40[0] = (int *)0x18;
        apiStack_40[1] = (int *)0x10;
        piVar1 = (int *)*piVar3;
        if ((char)piVar3[0x20] == '\x04') {
          iVar5 = (**(code **)(*piVar1 + 0x2c))(piVar1,&DAT_004cec54);
        }
        else {
          iVar5 = (**(code **)(*piVar1 + 0x2c))(piVar1,apiStack_40);
        }
        if (iVar5 == 0) {
          (**(code **)(*(int *)*piVar3 + 0x1c))((int *)*piVar3);
          return 1;
        }
      }
      (**(code **)(*(int *)*piVar3 + 8))((int *)*piVar3);
      *piVar3 = 0;
    }
  }
  return 0;
}


/* 00440a10 size=181 */

/* repo: runtime/kernel/src/sys/win/input.cpp, NOLF/ClientShellDLL/FolderCustomControls.cpp,
   Blood2/ClientShellDLL/MenuJoystickAxis.cpp */

int __thiscall input_440a10(void *this,byte *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  void *extraout_ECX;
  void *this_00;
  
  for (iVar3 = DAT_004e9cbc; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x300)) {
    iVar1 = FUN_004b7d10(param_1,iVar3 + 0xc);
    if (iVar1 != 0) {
      return iVar3;
    }
    this = extraout_ECX;
  }
  uVar2 = FUN_004c4c00(this,param_1,(byte *)s___mouse_004d9ae8);
  if (uVar2 == 0) {
    iVar3 = FUN_00440ad0(2);
    if (iVar3 != 0) {
      *(char **)(iVar3 + 4) = s___mouse_004d9ae8;
      return iVar3;
    }
  }
  else {
    uVar2 = FUN_004c4c00(this_00,param_1,(byte *)s___keyboard_004d9adc);
    if (uVar2 == 0) {
      iVar3 = FUN_00440ad0(3);
      if (iVar3 != 0) {
        *(char **)(iVar3 + 4) = s___keyboard_004d9adc;
        return iVar3;
      }
    }
    else {
      iVar3 = FUN_004c8310(param_1,s_Joystick_1_004d9af0,(void *)0x8);
      if ((iVar3 == 0) && (iVar3 = FUN_00440ad0(4), iVar3 != 0)) {
        *(char **)(iVar3 + 4) = s_Joystick_1_004d9af0;
        return iVar3;
      }
    }
  }
  return 0;
}


/* 00440b30 size=2376 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/kernel/src/sys/win/input.cpp */

/* input_440b30: lifted from original x86 -> lt_lifted.c */


/* 00441880 size=58 */

/* repo: runtime/kernel/src/sys/win/input.cpp */

undefined * __cdecl input_441880(byte *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined *puVar3;
  
  puVar3 = DAT_004e9b58;
  if (DAT_004e9b58 != &DAT_004e9b30) {
    do {
      iVar2 = FUN_004b7d10(param_1,(int)(puVar3 + 4));
      if (iVar2 != 0) {
        return puVar3;
      }
      puVar1 = (undefined4 *)(puVar3 + 0x28);
      puVar3 = (undefined *)*puVar1;
    } while ((undefined *)*puVar1 != &DAT_004e9b30);
  }
  return (undefined *)0x0;
}


/* 00441a00 size=95 */

/* repo: runtime/kernel/src/sys/win/input.cpp, Blood2/ClientShellDLL/MenuJoystickAxis.cpp,
   NOLF/ClientShellDLL/JoystickAxis.cpp */

uint __cdecl input_441a00(int param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  void *this;
  
  uVar1 = *(uint *)(param_1 + 0x8c);
  do {
    uVar3 = uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    uVar1 = *(uint *)(param_1 + 0x8c);
    uVar2 = *(uint *)(uVar3 + 4);
    uVar4 = FUN_004c4c00((void *)(uVar3 + 8),(void *)(uVar3 + 8),param_2);
  } while ((uVar4 != 0) &&
          (uVar4 = FUN_004c4c00(this,(byte *)(uVar3 + 0x6c),param_2),
          uVar1 = uVar2 & -(uint)(uVar2 != uVar1), uVar4 != 0));
  return uVar3;
}


/* 00441d30 size=1689 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/kernel/src/sys/win/input.cpp, runtime/kernel/src/sys/win/InputSim.cpp,
   sdk/inc/ltbasedefs.h */

/* input_441d30: lifted from original x86 -> lt_lifted.c */


/* 00442680 size=719 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/kernel/src/sys/win/input.cpp */

/* input_442680: lifted from original x86 -> lt_lifted.c */


/* 00442950 size=62 */

/* repo: runtime/kernel/src/sys/win/input.cpp */

void __cdecl input_442950(undefined *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  while (param_1 != (undefined *)0x0) {
    puVar2 = *(undefined **)(param_1 + 0x13c);
    while (puVar2 != (undefined *)0x0) {
      puVar1 = *(undefined **)(puVar2 + 0x2c);
      FUN_00430df0(puVar2);
      puVar2 = puVar1;
    }
    puVar2 = *(undefined **)(param_1 + 0x140);
    FUN_00430df0(param_1);
    param_1 = puVar2;
  }
  return;
}


/* 004434a0 size=49 */

/* repo: runtime/kernel/src/sys/win/input.cpp */

int __cdecl input_4434a0(uint param_1,int param_2)

{
  int iVar1;
  
  if (DAT_004e9cbc != 0) {
    iVar1 = DAT_004e9cbc;
    do {
      if (*(byte *)(iVar1 + 0x80) == param_1) {
        if (param_2 < 1) {
          return iVar1;
        }
        param_2 = param_2 + -1;
      }
      iVar1 = *(int *)(iVar1 + 0x300);
    } while (iVar1 != 0);
  }
  return 0;
}


