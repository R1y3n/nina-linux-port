/* lithtech.exe decompilation - module RiotClientShell */
#include "ghidra_types.h"

/* 00487d10 size=719 */

/* repo: Shogo/ClientShellDLL/RiotClientShell.cpp, runtime/server/src/servermgr.cpp,
   NOLF/ClientShellDLL/GameClientShell.cpp */

int __thiscall RiotClientShell_487d10(void *this,uint param_1)

{
  char *_Source;
  uint *puVar1;
  uint uVar2;
  int *piVar3;
  void *this_00;
  int iVar4;
  int unaff_EBP;
  undefined4 *puVar5;
  bool bVar6;
  longlong lVar7;
  byte *unaff_retaddr;
  size_t _Count;
  undefined4 uVar8;
  char acStack_108 [2];
  char acStack_106 [2];
  uint auStack_104 [65];
  
  FUN_00487fe0();
  FUN_004a0540();
  lVar7 = __ftol();
  FUN_004bbc61((DWORD)lVar7);
  (**(code **)(**(int **)((int)this + 0xa30) + 0x48))((DWORD)lVar7);
  uVar8 = 0;
  if (((param_1 & 4) != 0) && (*(int **)((int)this + 0x668) != (int *)0x0)) {
    _Count = 0xff;
    _Source = FUN_0047b9b0((int)this + 0xc3c,*(int **)((int)this + 0x668));
    _strncpy((char *)auStack_104,_Source,_Count);
    FUN_004c8d30(auStack_104);
    puVar1 = FUN_004bae50(auStack_104,&DAT_004dcb74);
    if (puVar1 != (uint *)0x0) {
      *(undefined1 *)puVar1 = 0;
    }
    uVar2 = FUN_004c4c00(this_00,unaff_retaddr,(byte *)auStack_104);
    if (uVar2 == 0) {
      uVar8 = 1;
    }
  }
  bVar6 = *(int *)((int)this + 0x198) == 0;
  (**(code **)(**(int **)((int)this + 0xa30) + 0x1c))(bVar6);
  if (bVar6) {
    servermgr_488360(this,unaff_EBP);
  }
  puVar5 = (undefined4 *)((int)this + 0xb6c);
  for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0xffffffff;
    puVar5 = puVar5 + 1;
  }
  iVar4 = (int)this + 0xa4c;
  *(undefined4 *)((int)this + 0x8d8) = 0;
  *(undefined4 *)((int)this + 0xb20) = 0;
  *(undefined4 *)((int)this + 0xb24) = 0;
  *(int *)((int)this + 0xa50) = iVar4;
  *(int *)iVar4 = iVar4;
  FUN_004b9f62(acStack_108,(byte *)s__s_dat_004d6ec8,unaff_retaddr);
  piVar3 = (int *)FUN_0047b5e0((int)this + 0xc3c,acStack_108);
  if ((piVar3 == (int *)0x0) ||
     (iVar4 = FUN_0047b810((int)this + 0xc3c,acStack_108,1,(undefined4 *)(acStack_108 + -4)),
     iVar4 == 0)) {
    FUN_00489880((int)this,0x29,(char)unaff_retaddr);
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CServerMgr__DoStartWorld_004dcb44)
      ;
    }
    return 0x29;
  }
  FUN_00416b80(unaff_retaddr);
  FUN_00487b90(*(int **)((int)this + 0xb38),(char *)unaff_retaddr);
  if ((unaff_EBP == 0) || (*(int *)((int)this + 0x668) == 0)) {
    iVar4 = FUN_00486aa0(this,piVar3);
    if (iVar4 != 0) {
      (**(code **)(*piVar3 + 4))();
      return iVar4;
    }
  }
  else {
    *(undefined4 *)((int)this + 0x664) = 1;
  }
  *(undefined4 *)((int)this + 0x668) = uVar8;
  FUN_00487730((int)this,1);
  FUN_00488a20(this);
  iVar4 = FUN_004799f0(this,piVar3);
  if (iVar4 != 0) {
    FUN_00436670((byte *)s_FAILED_to_load_world___s_004dcb28,unaff_retaddr);
    return iVar4;
  }
  *(int **)((int)this + 0x328) = piVar3;
  *(uint *)((int)this + 0x324) = *(uint *)((int)this + 0x324) | 1;
  FUN_00436670((byte *)s_Loaded_world___s_004dcb14,unaff_retaddr);
  *(undefined4 *)((int)this + 0x8d0) = 0;
  *(uint *)((int)this + 0x8e4) = param_1;
  *(uint *)((int)this + 0x8c8) = param_1;
  *(undefined4 *)((int)this + 0x8cc) = 0;
  *(undefined4 *)((int)this + 0x8dc) = 0;
  *(undefined4 *)((int)this + 0x8d4) = 0;
  *(undefined4 *)((int)this + 0x8d8) = 0;
  *(undefined4 *)((int)this + 0x8c4) = 0;
  *(undefined4 *)((int)this + 0x8bc) = 0;
  if (((uint)unaff_retaddr & 2) != 0) {
    FUN_004882d0(this);
  }
  return 0;
}


