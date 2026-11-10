/* lithtech.exe decompilation - module linuxfile */
#include "ghidra_types.h"

/* 00427d20 size=9 */

/* repo: runtime/kernel/io/src/sys/linux/linuxfile.cpp */

void __fastcall linuxfile_427d20(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cc04c;
  return;
}


/* 004283c0 size=353 */

/* repo: runtime/kernel/io/src/sys/linux/linuxfile.cpp */

bool __cdecl
linuxfile_4283c0(int *param_1,char *param_2,char *param_3,uint param_4,undefined4 *param_5,
                int *param_6)

{
  char cVar1;
  FILE *pFVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  CHAR local_1f4 [500];
  
  if (param_1 == (int *)0x0) {
    return false;
  }
  if (*param_1 != 1) {
    iVar3 = FUN_004b6ed0((void *)param_1[1],param_2);
    if (iVar3 == 0) {
      return false;
    }
    if (*(int **)(iVar3 + 0x34) == (int *)0x0) {
      pcVar4 = (char *)0x0;
    }
    else {
      pcVar4 = (char *)(**(code **)(**(int **)(iVar3 + 0x34) + 0x20))();
    }
    _strncpy(param_3,pcVar4,param_4);
    param_3[param_4 - 1] = '\0';
    if (*(int **)(iVar3 + 0x34) == (int *)0x0) {
      pcVar4 = (char *)0x0;
    }
    else {
      pcVar4 = (char *)(**(code **)(**(int **)(iVar3 + 0x34) + 0x20))();
    }
    uVar5 = 0xffffffff;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    if (~uVar5 - 1 < param_4) {
      *param_5 = *(undefined4 *)(iVar3 + 0x14);
      *param_6 = *(int *)(iVar3 + 0xc);
      return true;
    }
    return false;
  }
  FUN_004b9f62(local_1f4,(byte *)s__s__s_004d7a34,param_1 + 8);
  pFVar2 = (FILE *)FUN_004ba1fd(local_1f4,&DAT_004d57f4);
  if (pFVar2 == (FILE *)0x0) {
    return false;
  }
  FUN_004ba72b((int *)pFVar2,0,2);
  iVar3 = FUN_004ba5a8((char *)pFVar2);
  *param_6 = iVar3;
  *param_5 = 0;
  FUN_004ba14f(pFVar2);
  _strncpy(param_3,local_1f4,param_4);
  param_3[param_4 - 1] = '\0';
  uVar5 = 0xffffffff;
  pcVar4 = local_1f4;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  return ~uVar5 - 1 < param_4;
}


