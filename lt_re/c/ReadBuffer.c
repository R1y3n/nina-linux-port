/* lithtech.exe decompilation - module ReadBuffer */
#include "ghidra_types.h"

/* 004acc20 size=257 */

/* repo: libs/WONAPI/WONCommon/ReadBuffer.cpp */

int __thiscall ReadBuffer_4acc20(void *this,uint param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  undefined1 local_31;
  undefined1 *local_30;
  undefined1 *local_2c;
  undefined1 local_28 [4];
  undefined **local_24 [3];
  undefined1 local_18 [4];
  undefined1 *local_14;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9db0;
  local_c = ExceptionList;
  iVar2 = *(int *)this;
  if (param_1 <= (uint)(*(int *)((int)this + 8) - iVar2)) {
    *(uint *)this = iVar2 + param_1;
    return *(int *)((int)this + 4) + iVar2;
  }
  local_4 = 0;
  local_30 = (undefined1 *)0x0;
  local_2c = (undefined1 *)0x0;
  ExceptionList = &local_c;
  FUN_004a93e0(local_28,&param_1,0);
  uVar3 = 0xffffffff;
  pcVar4 = s_Attempt_to_read_past_end_of_buff_004de8c8;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  FUN_004ad500(&local_30,(undefined4 *)s_Attempt_to_read_past_end_of_buff_004de8c8,
               (int)(s___AVByteBuffer_WONAPI___004de8b0 + ~uVar3 + 0x17),param_1);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004bcc6d(local_24);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004a8740(local_18,&local_31,8);
  *local_14 = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  local_24[0] = &PTR_FUN_004cdbdc;
  FUN_004ab700(local_18,local_30,local_2c);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_24,&DAT_004d11f8);
}


