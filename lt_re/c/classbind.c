/* lithtech.exe decompilation - module classbind */
#include "ghidra_types.h"

/* 00402730 size=172 */

/* repo: runtime/shared/src/classbind.cpp, tools/shared/engine/classbind.cpp */

undefined4 __cdecl
classbind_402730(LPCSTR param_1,undefined4 param_2,undefined4 *param_3,int *param_4)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  undefined *puVar4;
  undefined4 uVar5;
  
  iVar2 = FUN_00401790(param_1,&param_1);
  if (iVar2 == 0) {
    return 0;
  }
  pcVar3 = (code *)FUN_004018a0((undefined4 *)param_1,s_ObjectDLLSetup_004d5640);
  if (pcVar3 == (code *)0x0) {
    FUN_004017d0((undefined4 *)param_1);
    return 1;
  }
  puVar4 = _malloc(0x14);
  piVar1 = param_4;
  *(LPCSTR *)(puVar4 + 8) = param_1;
  uVar5 = (*pcVar3)(puVar4 + 0x10,param_2,param_4);
  *(undefined4 *)(puVar4 + 0xc) = uVar5;
  if (*piVar1 == 1) {
    FUN_004027e0((int)puVar4);
    FUN_00436e70();
    *param_3 = puVar4;
    return 0xffffffff;
  }
  FUN_004b9d3f(puVar4);
  FUN_004017d0((undefined4 *)param_1);
  return 2;
}


