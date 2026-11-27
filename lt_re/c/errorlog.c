/* lithtech.exe decompilation - module errorlog */
#include "ghidra_types.h"

/* 004376e0 size=70 */

/* repo: runtime/client/src/errorlog.cpp */

void errorlog_4376e0(void)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = FUN_00420880(0x4e9500,s_errorlogfile_004d90a8);
  pcVar2 = s_error_log_004d909c;
  if (iVar1 != 0) {
    pcVar2 = *(char **)(iVar1 + 0x14);
  }
  if (DAT_004e9918 != 0) {
    DAT_004e9948 = FUN_004ba1fd(pcVar2,&DAT_004d9098);
  }
  FUN_00420e50(&LAB_004376a0);
  return;
}


