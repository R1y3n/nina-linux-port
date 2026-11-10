/* lithtech.exe decompilation - module shellnet */
#include "ghidra_types.h"

/* 0048e3e0 size=7 */

/* repo: runtime/client/src/shellnet.cpp */

undefined4 __cdecl shellnet_48e3e0(undefined4 *param_1)

{
  return *param_1;
}


/* 0048e480 size=217 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/client/src/shellnet.cpp */

void shellnet_48e480(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_004ebfc4;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _DAT_004ebff4 = &LAB_0048e560;
  _DAT_004ebfdc = FUN_0048e6a0;
  _DAT_004ebfd8 = &LAB_0048e7d0;
  _DAT_004ec030 = &LAB_0048e680;
  _DAT_004ebfe4 = &LAB_0048e9e0;
  _DAT_004ebfec = &LAB_00490ad0;
  _DAT_004ebff8 = FUN_00490d70;
  _DAT_004ebffc = shellnet_48e7f0;
  _DAT_004ec000 = &LAB_00490dd0;
  _DAT_004ec004 = FUN_004910b0;
  _DAT_004ec008 = FUN_004910f0;
  _DAT_004ec02c = &LAB_00491290;
  _DAT_004ec00c = &LAB_00491560;
  _DAT_004ebfe0 = &LAB_004915a0;
  _DAT_004ec010 = &LAB_00491640;
  _DAT_004ec018 = &LAB_00491840;
  _DAT_004ebfd4 = &LAB_00491c00;
  _DAT_004ec020 = &LAB_00491cd0;
  _DAT_004ec024 = &LAB_00491e70;
  _DAT_004ec028 = &LAB_00492050;
  return;
}


/* 0048e7f0 size=491 */

/* repo: runtime/client/src/shellnet.cpp */

/* shellnet_48e7f0: lifted from original x86 -> lt_lifted.c */


/* 0048f790 size=291 */

/* repo: runtime/client/src/shellnet.cpp */

void __cdecl shellnet_48f790(int param_1,uint param_2)

{
  undefined4 unaff_EBX;
  
  if (DAT_004e9908 == 2) {
    FUN_00420ea0(&DAT_004e4424,unaff_EBX);
    FUN_00420ea0((byte *)s_ObjectID___d__type__d__flags__d_004dcfc8,
                 (uint)*(ushort *)(param_1 + 0xb8));
    if ((param_2 & 1) != 0) {
      FUN_00420ea0((byte *)s_CF_NEWOBJECT_004dcfb8,unaff_EBX);
    }
    if ((param_2 & 2) != 0) {
      FUN_00420ea0((byte *)s_CF_POSITION_004dcfac,unaff_EBX);
    }
    if ((param_2 & 4) != 0) {
      FUN_00420ea0((byte *)s_CF_ROTATION_004dcfa0,unaff_EBX);
    }
    if ((param_2 & 8) != 0) {
      FUN_00420ea0((byte *)s_CF_FLAGS_004dcf94,unaff_EBX);
    }
    if ((param_2 & 0x10) != 0) {
      FUN_00420ea0((byte *)s_CF_SCALE_004dcf88,unaff_EBX);
    }
    if ((param_2 & 0x20) != 0) {
      FUN_00420ea0((byte *)s_CF_MODELINFO_004dcf78,unaff_EBX);
    }
    if ((param_2 & 0x40) != 0) {
      FUN_00420ea0((byte *)s_CF_COLORINFO_004dcf68,unaff_EBX);
    }
    if ((param_2 & 0x100) != 0) {
      FUN_00420ea0((byte *)s_CF_ATTACHMENTS_004dcf58,unaff_EBX);
      return;
    }
  }
  else if ((DAT_004e9908 == 1) && ((param_2 & 1) != 0)) {
    FUN_00420ea0(&DAT_004e4424,unaff_EBX);
    FUN_00420ea0((byte *)s_ObjectID___d__type___d__flags__d_004dcf34,
                 (uint)*(ushort *)(param_1 + 0xb8));
    FUN_00420ea0((byte *)s_CF_NEWOBJECT_004dcfb8,unaff_EBX);
  }
  return;
}


/* 004909b0 size=274 */

/* repo: runtime/client/src/shellnet.cpp */

undefined4 __cdecl shellnet_4909b0(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  void *this;
  uint uVar4;
  ushort uVar5;
  int *piVar6;
  
  iVar1 = *(int *)(param_1 + 0x78);
  uVar5 = *(ushort *)(param_2 + 0x38);
  uVar2 = (uint)*(ushort *)(param_2 + 0x34);
  uVar4 = (uint)uVar5;
  if ((int)(uVar2 - uVar4) < 1) {
    return 0;
  }
  do {
    if ((uVar4 + 2 < *(uint *)(param_2 + 0x58)) && (uVar4 + 2 <= uVar2)) {
      param_1 = CONCAT22((short)(param_1 >> 0x10),*(undefined2 *)(*(int *)(param_2 + 0x54) + uVar4))
      ;
      *(ushort *)(param_2 + 0x38) = uVar5 + 2;
    }
    else {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
    }
    if (DAT_004e9908 == 1) {
      FUN_00420ea0((byte *)s_Remove_id__d_004dcfe8,param_1 & 0xffff);
    }
    pcVar3 = (char *)FUN_004270c0(iVar1,param_1);
    if ((pcVar3 != (char *)0x0) && (piVar6 = *(int **)(pcVar3 + 4), piVar6 != (int *)0x0)) {
      if (*pcVar3 == '\x01') {
        FUN_00412f00(iVar1,(int)piVar6);
      }
      else if ((*(byte *)(piVar6 + 0x12) & 0xc0) == 0) {
        this = (void *)FUN_00410170();
        FUN_00497990(this,piVar6);
      }
      else {
        FUN_00494160((int)piVar6);
      }
    }
    uVar5 = *(ushort *)(param_2 + 0x38);
    uVar2 = (uint)*(ushort *)(param_2 + 0x34);
    uVar4 = (uint)uVar5;
  } while (0 < (int)(uVar2 - uVar4));
  return 0;
}


/* 00490cc0 size=173 */

/* repo: runtime/client/src/shellnet.cpp */

undefined4 __cdecl shellnet_490cc0(int param_1,float param_2)

{
  uint uVar1;
  float fVar2;
  ushort uVar3;
  float local_4;
  
  local_4 = 0.0;
  uVar3 = *(ushort *)((int)param_2 + 0x38);
  uVar1 = uVar3 + 4;
  if ((uVar1 < *(uint *)((int)param_2 + 0x58)) && (uVar1 <= *(ushort *)((int)param_2 + 0x34))) {
    fVar2 = *(float *)(*(int *)((int)param_2 + 0x54) + (uint)uVar3);
    *(ushort *)((int)param_2 + 0x38) = uVar3 + 4;
    param_2 = fVar2;
  }
  else {
    *(uint *)((int)param_2 + 0x40) = *(uint *)((int)param_2 + 0x40) | 2;
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
    }
  }
  if (*(float *)(param_1 + 0x18) < param_2) {
    local_4 = param_2 - *(float *)(param_1 + 0x18);
    *(float *)(param_1 + 0x18) = param_2;
  }
  *(float *)(param_1 + 0x24) = local_4;
  return 0;
}


