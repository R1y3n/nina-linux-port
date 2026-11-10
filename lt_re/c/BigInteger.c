/* lithtech.exe decompilation - module BigInteger */
#include "ghidra_types.h"

/* 004ae660 size=425 */

/* repo: libs/WONAPI/WONCrypt/BigInteger.cpp */

void __cdecl BigInteger_4ae660(void *param_1,void *param_2,void *param_3)

{
  char cVar1;
  void *pvVar2;
  void *pvVar3;
  void *pvVar4;
  undefined2 uVar5;
  uint uVar6;
  char *pcVar7;
  undefined4 *local_30;
  undefined1 *local_2c;
  undefined1 local_28 [4];
  undefined **local_24 [3];
  undefined1 local_18 [4];
  undefined1 *local_14;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  pvVar4 = param_3;
  pvVar3 = param_2;
  pvVar2 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9ef0;
  local_c = ExceptionList;
  if ((param_1 != param_2) && (param_1 != param_3)) {
    if ((*(short *)((int)param_2 + 0x1a) == 0) || (*(short *)((int)param_3 + 0x1a) == 0)) {
      ExceptionList = &local_c;
      FUN_004adb50((int)param_1);
      ExceptionList = local_c;
      return;
    }
    ExceptionList = &local_c;
    *(byte *)((int)param_1 + 0x1c) = *(byte *)((int)param_2 + 0x1c) ^ *(byte *)((int)param_3 + 0x1c)
    ;
    FUN_004ad8d0(param_1,(uint)*(ushort *)((int)param_2 + 0x1a) +
                         (uint)*(ushort *)((int)param_3 + 0x1a),'\0');
    *(short *)((int)pvVar2 + 0x1a) = *(short *)((int)pvVar3 + 0x1a) + *(short *)((int)pvVar4 + 0x1a)
    ;
    FUN_004add00(*(uint **)((int)pvVar2 + 0x14),*(int *)((int)pvVar3 + 0x14),
                 *(uint **)((int)pvVar4 + 0x14),(uint)*(ushort *)((int)pvVar3 + 0x1a),
                 (uint)*(ushort *)((int)pvVar4 + 0x1a));
    uVar5 = FUN_004ae150(*(int *)((int)pvVar2 + 0x14),(uint)*(ushort *)((int)pvVar2 + 0x1a));
    *(undefined2 *)((int)pvVar2 + 0x1a) = uVar5;
    ExceptionList = local_c;
    return;
  }
  local_4 = 0;
  local_30 = (undefined4 *)0x0;
  local_2c = (undefined1 *)0x0;
  ExceptionList = &local_c;
  FUN_004a93e0(local_28,&param_1,0);
  uVar6 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  pcVar7 = s_Result_must_not_be_either_Parame_004de964;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  FUN_004a9380(&local_30,~uVar6);
  local_2c = (undefined1 *)
             FUN_004a5c10((undefined4 *)s_Result_must_not_be_either_Parame_004de964,
                          (int)(s___AVArithmeticException_WONAPI___004de940 + ~uVar6 + 0x23),
                          local_30);
  *local_2c = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004bcc6d(local_24);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004a8740(local_18,&param_2,8);
  *local_14 = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  local_24[0] = &PTR_FUN_004cec4c;
  FUN_004ab700(local_18,(undefined1 *)local_30,local_2c);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_24,&DAT_004d13b0);
}


/* 004aea00 size=516 */

/* repo: libs/WONAPI/WONCrypt/BigInteger.cpp */

void __cdecl BigInteger_4aea00(void *param_1,void *param_2,void *param_3,uint *param_4)

{
  char cVar1;
  void *pvVar2;
  void *pvVar3;
  undefined2 uVar4;
  uint uVar5;
  void *pvVar6;
  void *pvVar7;
  char *pcVar8;
  uint *local_34;
  undefined4 *local_30;
  undefined1 *local_2c;
  undefined1 local_28 [4];
  undefined **local_24 [3];
  undefined1 local_18 [4];
  undefined1 *local_14;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  pvVar2 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9fa0;
  local_c = ExceptionList;
  local_34 = param_4;
  if (param_1 != param_2) {
    pvVar3 = param_3;
    pvVar7 = param_2;
    do {
      pvVar6 = pvVar3;
      if (param_1 == pvVar6) break;
      if ((*(ushort *)((int)pvVar7 + 0x1a) == 0) || (*(ushort *)((int)pvVar6 + 0x1a) == 0)) {
        ExceptionList = &local_c;
        BigInteger_4ae660(param_1,pvVar7,pvVar6);
        ExceptionList = local_c;
        return;
      }
      if (*(ushort *)((int)pvVar6 + 0x1a) <= *(ushort *)((int)pvVar7 + 0x1a)) {
        ExceptionList = &local_c;
        *(byte *)((int)param_1 + 0x1c) =
             *(byte *)((int)pvVar7 + 0x1c) ^ *(byte *)((int)pvVar6 + 0x1c);
        uVar5 = (uint)*(ushort *)((int)pvVar7 + 0x1a);
        if (param_4 == (uint *)0x0) {
          local_34 = (uint *)FUN_00430de0(uVar5 * 0xc);
        }
        FUN_004ad8d0(pvVar7,uVar5,'\x01');
        FUN_004ad8d0(pvVar6,uVar5,'\x01');
        FUN_004ad8d0(pvVar2,uVar5 * 2,'\0');
        *(short *)((int)pvVar2 + 0x1a) =
             *(short *)((int)pvVar7 + 0x1a) + *(short *)((int)pvVar6 + 0x1a);
        FUN_004aded0(*(uint **)((int)pvVar2 + 0x14),local_34,*(uint **)((int)pvVar7 + 0x14),
                     *(uint **)((int)pvVar6 + 0x14),(uint)*(ushort *)((int)pvVar7 + 0x1a),
                     (uint)*(ushort *)((int)pvVar7 + 0x1a),(uint)*(ushort *)((int)pvVar6 + 0x1a));
        uVar4 = FUN_004ae150(*(int *)((int)pvVar2 + 0x14),(uint)*(ushort *)((int)pvVar2 + 0x1a));
        *(undefined2 *)((int)pvVar2 + 0x1a) = uVar4;
        if (param_4 == (uint *)0x0) {
          FUN_00430df0((undefined *)local_34);
        }
        ExceptionList = local_c;
        return;
      }
      pvVar3 = pvVar7;
      pvVar7 = pvVar6;
    } while (param_1 != pvVar6);
  }
  local_4 = 0;
  local_30 = (undefined4 *)0x0;
  local_2c = (undefined1 *)0x0;
  ExceptionList = &local_c;
  FUN_004a93e0(local_28,&param_4,0);
  uVar5 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  pcVar8 = s_Result_must_not_be_either_Parame_004de964;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  FUN_004a9380(&local_30,~uVar5);
  local_2c = (undefined1 *)
             FUN_004a5c10((undefined4 *)s_Result_must_not_be_either_Parame_004de964,
                          (int)(s___AVArithmeticException_WONAPI___004de940 + ~uVar5 + 0x23),
                          local_30);
  *local_2c = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004bcc6d(local_24);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004a8740(local_18,&param_1,8);
  *local_14 = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  local_24[0] = &PTR_FUN_004cec4c;
  FUN_004ab700(local_18,(undefined1 *)local_30,local_2c);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_24,&DAT_004d13b0);
}


/* 004aec10 size=480 */

/* repo: libs/WONAPI/WONCrypt/BigInteger.cpp */

void __cdecl BigInteger_4aec10(void *param_1,void *param_2,void *param_3)

{
  char cVar1;
  void *pvVar2;
  void *pvVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  undefined4 *local_50;
  undefined1 *local_4c;
  undefined1 local_48 [4];
  undefined **local_44 [3];
  undefined1 local_38 [4];
  undefined1 *local_34;
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  pvVar3 = param_2;
  pvVar2 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9fe8;
  local_c = ExceptionList;
  if (param_1 != param_2) {
    ExceptionList = &local_c;
    FUN_004ad8a0(param_1,param_2);
    pvVar4 = param_3;
    iVar5 = FUN_004ae310((int)pvVar3,(int)param_3);
    if (iVar5 < 0) {
      if (*(char *)((int)pvVar3 + 0x1c) != '\0') {
        *(undefined1 *)((int)pvVar2 + 0x1c) = 1;
        FUN_004ae170(pvVar2,pvVar4,pvVar2);
        ExceptionList = local_c;
        return;
      }
    }
    else {
      *(undefined1 *)((int)pvVar2 + 0x1c) = 0;
      iVar5 = FUN_004ad580((int)pvVar3);
      iVar6 = FUN_004ad580((int)pvVar4);
      uVar7 = iVar5 - iVar6;
      FUN_004afb30(local_2c);
      local_4 = 7;
      FUN_004ae340(local_2c,(int)pvVar4,uVar7);
      if (-1 < (int)uVar7) {
        iVar5 = uVar7 + 1;
        do {
          iVar6 = FUN_004ae2c0((int)pvVar2,(int)local_2c);
          if (-1 < iVar6) {
            FUN_004ae200(pvVar2,pvVar2,local_2c);
          }
          FUN_004ae450(local_2c,(int)local_2c,1);
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      if (*(char *)((int)pvVar3 + 0x1c) != '\0') {
        *(undefined1 *)((int)pvVar2 + 0x1c) = 1;
        FUN_004ae170(pvVar2,pvVar4,pvVar2);
      }
      FUN_004ad860(local_2c);
    }
    ExceptionList = local_c;
    return;
  }
  local_4 = 0;
  local_50 = (undefined4 *)0x0;
  local_4c = (undefined1 *)0x0;
  ExceptionList = &local_c;
  FUN_004a93e0(local_48,&param_1,0);
  uVar7 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  pcVar8 = s_Result_must_not_be_the_same_obje_004de994;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  FUN_004a9380(&local_50,~uVar7);
  local_4c = (undefined1 *)
             FUN_004a5c10((undefined4 *)s_Result_must_not_be_the_same_obje_004de994,
                          (int)(s_Result_must_not_be_either_Parame_004de964 + ~uVar7 + 0x2f),
                          local_50);
  *local_4c = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004bcc6d(local_44);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004a8740(local_38,&param_2,8);
  *local_34 = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  local_44[0] = &PTR_FUN_004cec4c;
  FUN_004ab700(local_38,(undefined1 *)local_50,local_4c);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_44,&DAT_004d13b0);
}


/* 004aedf0 size=721 */

/* repo: libs/WONAPI/WONCrypt/BigInteger.cpp */

void __cdecl BigInteger_4aedf0(int *param_1,int *param_2,void *param_3,int param_4)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  int unaff_EDI;
  char *pcVar10;
  bool bVar11;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 local_48 [4];
  undefined **local_44 [3];
  undefined1 local_38 [4];
  undefined1 *local_34;
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  pvVar2 = param_3;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca05e;
  local_c = ExceptionList;
  if (*(short *)(param_4 + 0x1a) != 0) {
    ExceptionList = &local_c;
    iVar3 = FUN_004ae2c0((int)param_3,param_4);
    piVar6 = param_2;
    if (iVar3 < 0) {
      if (param_2 != (int *)0x0) {
        FUN_004ad8a0(param_2,pvVar2);
      }
      if (param_1 != (int *)0x0) {
        FUN_004adb50((int)param_1);
        ExceptionList = local_c;
        return;
      }
    }
    else {
      piVar5 = param_1;
      if (param_1 == (int *)0x0) {
        puVar4 = (undefined4 *)FUN_00430de0(0x20);
        local_4 = 7;
        if (puVar4 == (undefined4 *)0x0) {
          piVar5 = (int *)0x0;
        }
        else {
          piVar5 = FUN_004afb30(puVar4);
        }
        local_4 = 0xffffffff;
      }
      if (piVar6 == (int *)0x0) {
        puVar4 = (undefined4 *)FUN_00430de0(0x20);
        local_4 = 8;
        if (puVar4 == (undefined4 *)0x0) {
          piVar6 = (int *)0x0;
        }
        else {
          piVar6 = FUN_004afb30(puVar4);
        }
      }
      bVar11 = param_1 != (int *)0x0;
      local_4 = 10;
      param_1 = piVar5;
      if (bVar11) {
        param_1 = (int *)0x0;
      }
      piVar9 = piVar6;
      if (param_2 != (int *)0x0) {
        piVar9 = (int *)0x0;
      }
      FUN_004afb30(local_2c);
      pvVar2 = param_3;
      local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0xb);
      FUN_004ad8a0(piVar6,param_3);
      FUN_004adb50((int)piVar5);
      iVar3 = FUN_004ad580((int)pvVar2);
      iVar7 = FUN_004ad580(param_4);
      uVar8 = iVar3 - iVar7;
      FUN_004ae340(local_2c,param_4,uVar8);
      if (-1 < (int)uVar8) {
        iVar3 = uVar8 + 1;
        do {
          if (*(short *)((int)piVar5 + 0x1a) == 0) {
            iVar7 = FUN_004ae2c0((int)piVar6,(int)local_2c);
            if (-1 < iVar7) {
              FUN_004adb70((int)piVar5);
              FUN_004ae200(piVar6,piVar6,local_2c);
            }
          }
          else {
            FUN_004ae340(piVar5,(int)piVar5,1);
            iVar7 = FUN_004ae2c0((int)piVar6,(int)local_2c);
            if (-1 < iVar7) {
              *(uint *)piVar5[5] = *(uint *)piVar5[5] | 1;
              FUN_004ae200(piVar6,piVar6,local_2c);
            }
          }
          FUN_004ae450(local_2c,(int)local_2c,1);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      *(byte *)(piVar5 + 7) = *(byte *)((int)param_3 + 0x1c) ^ *(byte *)(param_4 + 0x1c);
      FUN_004ad860(local_2c);
      local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),9);
      if (piVar9 != (int *)0x0) {
        (**(code **)(*piVar9 + 8))(1);
      }
      local_4 = 0xffffffff;
      if (param_1 != (int *)0x0) {
        (**(code **)(*param_1 + 8))(1);
      }
    }
    ExceptionList = local_c;
    return;
  }
  local_4 = 0;
  local_50 = 0;
  local_4c = 0;
  ExceptionList = &local_c;
  FUN_004a93e0(local_48,&param_4,0);
  uVar8 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 1;
  pcVar10 = s_div__Divide_by_zero_004de9bc;
  do {
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar1 != '\0');
  FUN_004aa340(&local_50,(undefined4 *)s_div__Divide_by_zero_004de9bc,
               (int)(s_Result_must_not_be_the_same_obje_004de994 + ~uVar8 + 0x27),unaff_EDI);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004bcc6d(local_44);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  FUN_004a8740(local_38,&param_2,8);
  *local_34 = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  local_44[0] = &PTR_FUN_004cec4c;
  FUN_004a7fa0(local_38,&local_50);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_44,&DAT_004d13b0);
}


/* 004af410 size=593 */

/* repo: libs/WONAPI/WONCrypt/BigInteger.cpp */

/* BigInteger_4af410: lifted from original x86 -> lt_lifted.c */


/* 004af670 size=1043 */

/* repo: libs/WONAPI/WONCrypt/BigInteger.cpp */

void __cdecl BigInteger_4af670(void *param_1,void *param_2,void *param_3)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  uint uVar13;
  char *pcVar14;
  undefined1 local_195;
  undefined4 *local_194;
  undefined4 *local_190;
  undefined1 *local_18c;
  undefined4 local_188;
  undefined **local_184 [3];
  undefined4 local_178;
  undefined1 *local_174;
  undefined1 local_170 [4];
  int local_16c [6];
  short local_152;
  int local_14c [8];
  int local_12c [8];
  undefined4 local_10c [8];
  undefined4 local_ec [8];
  undefined4 local_cc [8];
  undefined4 local_ac [8];
  undefined4 local_8c [8];
  int local_6c [8];
  undefined4 local_4c [8];
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca200;
  local_c = ExceptionList;
  if ((*(char *)((int)param_2 + 0x1c) == '\0') && (*(char *)((int)param_3 + 0x1c) == '\0')) {
    ExceptionList = &local_c;
    FUN_004afb30(local_ec);
    local_4 = 8;
    FUN_004afb30(local_10c);
    (*(uint8_t*)((char*)&local_4+0)) = 9;
    FUN_004afb30(local_12c);
    (*(uint8_t*)((char*)&local_4+0)) = 10;
    FUN_004ad8a0(local_12c,param_2);
    FUN_004afb30(local_cc);
    (*(uint8_t*)((char*)&local_4+0)) = 0xb;
    FUN_004afb30(local_ac);
    (*(uint8_t*)((char*)&local_4+0)) = 0xc;
    FUN_004afb30(local_16c);
    (*(uint8_t*)((char*)&local_4+0)) = 0xd;
    FUN_004ad8a0(local_16c,param_3);
    local_194 = local_cc;
    FUN_004adb70((int)local_ec);
    FUN_004adb70((int)local_ac);
    FUN_004adb50((int)local_10c);
    FUN_004adb50((int)local_cc);
    FUN_004afb30(local_2c);
    (*(uint8_t*)((char*)&local_4+0)) = 0xe;
    FUN_004afb30(local_4c);
    (*(uint8_t*)((char*)&local_4+0)) = 0xf;
    FUN_004afb30(local_6c);
    (*(uint8_t*)((char*)&local_4+0)) = 0x10;
    FUN_004afb30(local_14c);
    (*(uint8_t*)((char*)&local_4+0)) = 0x11;
    FUN_004afb30(local_8c);
    local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),0x12);
    piVar8 = local_12c;
    puVar9 = local_ac;
    puVar10 = local_ec;
    puVar11 = local_10c;
    piVar4 = local_16c;
    puVar5 = local_4c;
    piVar6 = local_6c;
    puVar12 = local_2c;
    while (puVar7 = puVar12, puVar3 = puVar11, puVar12 = puVar10, puVar11 = puVar9, piVar2 = piVar8,
          local_152 != 0) {
      BigInteger_4aedf0(local_14c,piVar6,piVar2,(int)piVar4);
      BigInteger_4ae660(puVar7,local_14c,puVar11);
      FUN_004ae200(puVar5,puVar3,puVar7);
      BigInteger_4ae660(local_8c,local_14c,local_194);
      FUN_004ae200(puVar7,puVar12,local_8c);
      local_152 = *(short *)((int)piVar6 + 0x1a);
      piVar8 = piVar4;
      puVar9 = puVar5;
      puVar10 = local_194;
      piVar4 = piVar6;
      puVar5 = puVar3;
      piVar6 = piVar2;
      local_194 = puVar7;
    }
    if (*(char *)(puVar12 + 7) != '\0') {
      FUN_004ae170(puVar12,puVar12,param_3);
    }
    FUN_004ad8a0(param_1,puVar12);
    FUN_004ad860(local_8c);
    FUN_004ad860(local_14c);
    FUN_004ad860(local_6c);
    FUN_004ad860(local_4c);
    FUN_004ad860(local_2c);
    FUN_004ad860(local_16c);
    FUN_004ad860(local_ac);
    FUN_004ad860(local_cc);
    FUN_004ad860(local_12c);
    FUN_004ad860(local_10c);
    FUN_004ad860(local_ec);
    ExceptionList = local_c;
    return;
  }
  local_190 = (undefined4 *)0x0;
  local_18c = (undefined1 *)0x0;
  local_188 = 0;
  uVar13 = 0xffffffff;
  local_4 = 1;
  pcVar14 = s_inverseModN_004de9dc;
  do {
    if (uVar13 == 0) break;
    uVar13 = uVar13 - 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar14 + 1;
  } while (cVar1 != '\0');
  ExceptionList = &local_c;
  FUN_004a9380(&local_190,~uVar13);
  local_18c = (undefined1 *)
              FUN_004a5c10((undefined4 *)s_inverseModN_004de9dc,
                           (int)(s_modMulRecip_004de9d0 + ~uVar13 + 0xb),local_190);
  *local_18c = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004bcc6d(local_184);
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  local_178 = 0;
  local_174 = (undefined1 *)0x0;
  FUN_004a93e0(local_170,&local_195,0);
  (*(uint8_t*)((char*)&local_4+0)) = 5;
  FUN_004a9380(&local_178,8);
  *local_174 = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 6;
  local_184[0] = &PTR_FUN_004cec4c;
  FUN_004ab700(&local_178,(undefined1 *)local_190,local_18c);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),2);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_184,&DAT_004d13b0);
}


