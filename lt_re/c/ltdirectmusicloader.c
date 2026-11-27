/* lithtech.exe decompilation - module ltdirectmusicloader */
#include "ghidra_types.h"

/* 0044d050 size=195 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusicloader.cpp, tools/ltdmtest/ltdirectmusicloader.cpp
    */

undefined4 __thiscall ltdirectmusicloader_44d050(void *this,LPCWSTR param_1)

{
  int *this_00;
  int iVar1;
  CHAR local_104 [260];
  
  FUN_0044d120((int)this);
  if (param_1 == (LPCWSTR)0x0) {
    return 0x80004005;
  }
  FUN_004bc345(local_104,param_1,0x104);
  this_00 = FUN_004354b0(&DAT_004ea630,local_104);
  *(int **)((int)this + 0xc) = this_00;
  if (this_00 == (int *)0x0) {
    return 0x80004005;
  }
  iVar1 = FUN_00435160(this_00,(char *)0x0);
  if (iVar1 == 0) {
    FUN_00448a10(5,(byte *)s_CLTDMFileStream__Open_FileName___004da8d8,local_104);
    return 0;
  }
  FUN_00448970((byte *)s_LTDirectMusic_loader_failed_to_o_004da8fc,local_104);
  FUN_00435560(&DAT_004ea630,*(int **)((int)this + 0xc));
  *(undefined4 *)((int)this + 0xc) = 0;
  return 0x80004005;
}


