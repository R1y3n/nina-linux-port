/* lithtech.exe decompilation - unnamed_00438000 */
#include "ghidra_types.h"

/* 00438090 size=487 */

char * __cdecl FUN_00438090(int param_1)

{
  uint uVar1;
  int *piVar2;
  int local_c0;
  char *local_bc [5];
  undefined4 local_a8;
  char *local_a4;
  undefined4 local_a0;
  char *local_9c;
  undefined4 local_98;
  char *local_94;
  undefined4 local_90;
  char *local_8c;
  undefined4 local_88;
  char *local_84;
  undefined4 local_80;
  char *local_7c;
  undefined4 local_78;
  char *local_74;
  undefined4 local_70;
  char *local_6c;
  undefined4 local_68;
  char *local_64;
  undefined4 local_60;
  char *local_5c;
  undefined4 local_58;
  char *local_54;
  undefined4 local_50;
  char *local_4c;
  undefined4 local_48;
  char *local_44;
  undefined4 local_40;
  char *local_3c;
  undefined4 local_38;
  char *local_34;
  undefined4 local_30;
  char *local_2c;
  undefined4 local_28;
  char *local_24;
  undefined4 local_20;
  char *local_1c;
  undefined4 local_18;
  char *local_14;
  undefined4 local_10;
  char *local_c;
  undefined4 local_8;
  char *local_4;
  
  piVar2 = &local_c0;
  local_c0 = 0x40010005;
  local_bc[0] = s_a_Control_C_004d95c8;
  local_bc[1] = (char *)0x40010008;
  local_bc[2] = s_a_Control_Break_004d95b8;
  local_bc[3] = (char *)0x80000002;
  local_bc[4] = s_a_Datatype_Misalignment_004d95a0;
  local_a8 = 0x80000003;
  local_a4 = s_a_Breakpoint_004d9590;
  local_a0 = 0xc0000005;
  local_9c = s_an_Access_Violation_004d957c;
  local_98 = 0xc0000006;
  local_94 = s_an_In_Page_Error_004d9568;
  local_90 = 0xc0000017;
  local_8c = s_a_No_Memory_004d955c;
  local_88 = 0xc000001d;
  local_84 = s_an_Illegal_Instruction_004d9544;
  local_80 = 0xc0000025;
  local_7c = s_a_Noncontinuable_Exception_004d9528;
  local_78 = 0xc0000026;
  local_74 = s_an_Invalid_Disposition_004d9510;
  local_70 = 0xc000008c;
  local_6c = s_a_Array_Bounds_Exceeded_004d94f8;
  local_68 = 0xc000008d;
  local_64 = s_a_Float_Denormal_Operand_004d94dc;
  local_60 = 0xc000008e;
  local_5c = s_a_Float_Divide_by_Zero_004d94c4;
  local_58 = 0xc000008f;
  local_54 = s_a_Float_Inexact_Result_004d94ac;
  local_50 = 0xc0000090;
  local_4c = s_a_Float_Invalid_Operation_004d9490;
  local_48 = 0xc0000091;
  local_44 = s_a_Float_Overflow_004d947c;
  local_40 = 0xc0000092;
  local_3c = s_a_Float_Stack_Check_004d9468;
  local_38 = 0xc0000093;
  local_34 = s_a_Float_Underflow_004d9454;
  local_30 = 0xc0000094;
  local_2c = s_an_Integer_Divide_by_Zero_004d9438;
  local_28 = 0xc0000095;
  local_24 = s_an_Integer_Overflow_004d9424;
  local_20 = 0xc0000096;
  local_1c = s_a_Privileged_Instruction_004d9408;
  local_18 = 0xc00000fd;
  local_14 = s_a_Stack_Overflow_004d93f4;
  local_10 = 0xc0000142;
  local_c = s_a_DLL_Initialization_Failed_004d93d8;
  local_8 = 0xe06d7363;
  local_4 = s_a_Microsoft_C___Exception_004d93bc;
  uVar1 = 0;
  do {
    if (param_1 == *piVar2) {
      return local_bc[uVar1 * 2];
    }
    uVar1 = uVar1 + 1;
    piVar2 = piVar2 + 2;
  } while (uVar1 < 0x18);
  return s_Unknown_exception_type_004d93a4;
}


/* 00438280 size=27 */

char * __cdecl FUN_00438280(char *param_1)

{
  char *pcVar1;
  
  pcVar1 = _strrchr(param_1,0x5c);
  if (pcVar1 == (char *)0x0) {
    return param_1;
  }
  return pcVar1 + 1;
}


/* 004382a0 size=57 */

undefined4 * __cdecl FUN_004382a0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = FUN_00430f00(0x28);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  puVar3 = puVar1;
  for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar3 = puVar1 + 2;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_1;
    param_1 = param_1 + 1;
    puVar3 = puVar3 + 1;
  }
  DAT_004e9950 = puVar1;
  return puVar1;
}


/* 004382e0 size=51 */

void __cdecl FUN_004382e0(int *param_1)

{
  if (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      (*(code *)param_1[6])(param_1,*param_1,(short)param_1[1]);
    }
    FUN_00430fe0((undefined *)param_1);
    DAT_004e9950 = 0;
  }
  return;
}


/* 00438320 size=13 */

undefined4 __cdecl FUN_00438320(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x24);
}


/* 00438330 size=16 */

void __cdecl FUN_00438330(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x24) = param_2;
  }
  return;
}


/* 00438340 size=320 */

void __cdecl FUN_00438340(uint param_1,int param_2)

{
  int *this;
  uint uVar1;
  ushort uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *local_4;
  
  uVar1 = param_1;
  if ((param_1 != 0) && ((**(byte **)(param_2 + 0x54) & 0x3f) == 0x32)) {
    puVar3 = FUN_0046b170(&local_4,0x44c,0x44c);
    this = (int *)*puVar3;
    if (this != (int *)0x0) {
      (**(code **)(*this + 4))();
    }
    if (local_4 != (int *)0x0) {
      (**(code **)(*local_4 + 8))();
    }
    param_1 = 0;
    do {
      if (*(short *)(param_2 + 0x34) == *(short *)(param_2 + 0x38)) break;
      uVar2 = FUN_004384b0(param_2);
      iVar4 = FUN_00438530(param_2);
      iVar5 = FUN_0046b370(param_2);
      iVar4 = (**(code **)(uVar1 + 8))(uVar1,iVar5,iVar4,uVar2);
      if (iVar4 == 0) {
        uVar2 = uVar2 | 0x8000;
      }
      uVar6 = ((uint)*(ushort *)((int)this + 0x36) - (uint)*(ushort *)(this + 0xe)) - 7;
      if (((int)uVar6 < 0) || (uVar6 < 4)) {
        *(undefined1 *)this[0x15] = 0x36;
        FUN_004657c0(*(void **)(uVar1 + 0x1c),this,*(float **)(uVar1 + 0x20),0x80);
        *(undefined2 *)(this + 0xe) = 1;
        *(undefined2 *)(this + 0xd) = 1;
      }
      FUN_004385b0(this,uVar2);
      param_1 = param_1 + 1;
    } while (param_1 < 5000);
    if (0 < (int)(*(ushort *)(this + 0xd) - 1)) {
      *(undefined1 *)this[0x15] = 0x36;
      FUN_004657c0(*(void **)(uVar1 + 0x1c),this,*(float **)(uVar1 + 0x20),0x80);
    }
    if (this != (int *)0x0) {
      (**(code **)(*this + 8))();
    }
  }
  return;
}


/* 00438480 size=38 */

void __cdecl FUN_00438480(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  if (DAT_004e9950 != 0) {
    (**(code **)(DAT_004e9950 + 8))(DAT_004e9950,param_3,param_2,param_1);
  }
  return;
}


/* 004384b0 size=123 */

undefined2 __fastcall FUN_004384b0(int param_1)

{
  uint uVar1;
  ushort uVar2;
  undefined2 uVar3;
  undefined2 local_4;
  
  uVar2 = *(ushort *)(param_1 + 0x38);
  uVar1 = uVar2 + 2;
  if ((uVar1 < *(uint *)(param_1 + 0x58)) && (uVar1 <= *(ushort *)(param_1 + 0x34))) {
    uVar3 = *(undefined2 *)(*(int *)(param_1 + 0x54) + (uint)uVar2);
    *(ushort *)(param_1 + 0x38) = uVar2 + 2;
    return uVar3;
  }
  *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | 2;
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
  }
  local_4 = (undefined2)param_1;
  return local_4;
}


/* 00438530 size=121 */

int __fastcall FUN_00438530(int param_1)

{
  uint uVar1;
  ushort uVar2;
  int iVar3;
  
  uVar2 = *(ushort *)(param_1 + 0x38);
  uVar1 = uVar2 + 4;
  if ((uVar1 < *(uint *)(param_1 + 0x58)) && (uVar1 <= *(ushort *)(param_1 + 0x34))) {
    iVar3 = *(int *)(*(int *)(param_1 + 0x54) + (uint)uVar2);
    *(ushort *)(param_1 + 0x38) = uVar2 + 4;
    return iVar3;
  }
  *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | 2;
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
  }
  return param_1;
}


/* 004385b0 size=358 */

/* WARNING: Removing unreachable block (ram,0x00438680) */

void __thiscall FUN_004385b0(void *this,undefined2 param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if ((uint)*(ushort *)((int)this + 0x36) <= *(ushort *)((int)this + 0x38) + 2) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
    return;
  }
  if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 2) {
    do {
      uVar1 = *(uint *)((int)this + 0x58);
      if (*(int *)((int)this + 0x5c) == 0) {
        iVar2 = FUN_0040c920(&DAT_004ecc58,0,*(int *)((int)this + 0x60) + uVar1 + 1);
        if (iVar2 != 0) {
          uVar4 = 0;
          if (uVar1 != 0) {
            do {
              uVar3 = uVar4 + 1;
              *(undefined1 *)(uVar4 + iVar2) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar3);
              uVar4 = uVar3;
            } while (uVar3 < uVar1);
          }
          uVar4 = uVar1;
          if (uVar1 < *(uint *)((int)this + 0x58)) {
            do {
              uVar4 = uVar4 + 1;
              *(undefined1 *)(uVar4 + iVar2) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar4);
            } while (uVar4 < *(uint *)((int)this + 0x58));
          }
          *(undefined1 *)(uVar1 + iVar2) = 0;
          if (*(int *)((int)this + 0x54) != 0) {
            FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x54));
            *(undefined4 *)((int)this + 0x54) = 0;
            *(undefined4 *)((int)this + 0x5c) = 0;
          }
          *(int *)((int)this + 0x54) = iVar2;
          *(undefined4 *)((int)this + 0x5c) = *(undefined4 *)((int)this + 0x60);
          goto LAB_0043869c;
        }
      }
      else {
        *(int *)((int)this + 0x5c) = *(int *)((int)this + 0x5c) + -1;
        *(undefined1 *)(*(int *)((int)this + 0x54) + uVar1) = 0;
LAB_0043869c:
        *(int *)((int)this + 0x58) = *(int *)((int)this + 0x58) + 1;
      }
    } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 2);
  }
  *(undefined2 *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = param_1;
  *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 2;
  *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 2;
  return;
}


/* 00438720 size=182 */

undefined4 * __cdecl FUN_00438720(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *this;
  int iVar2;
  undefined4 *puVar3;
  
  this = (undefined4 *)FUN_00430de0(0x88);
  if (this == (undefined4 *)0x0) {
    this = (undefined4 *)0x0;
  }
  else {
    FUN_004b7fa0(this);
    this[6] = &PTR_FUN_004cc41c;
    FUN_004b7b90(this + 7,0x1c,0x20);
  }
  this[0x15] = param_2;
  this[0x12] = 0;
  this[0x13] = 0;
  this[0x14] = 0;
  this[0x17] = 0;
  this[0x1d] = 0;
  this[0x1e] = 0;
  this[0x1f] = 0;
  this[0x20] = 0;
  this[0x21] = 0;
  FUN_004b80a0(this,0x1000);
  FUN_004b7c10((int)(this + 7));
  FUN_004b7be0(this + 7,0x1c,0x80,0x80);
  puVar1 = this + 0xf;
  puVar3 = this + 0x18;
  for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_1;
    param_1 = param_1 + 1;
    puVar3 = puVar3 + 1;
  }
  this[0x10] = puVar1;
  *puVar1 = puVar1;
  this[0x14] = 0;
  this[0x16] = 0x47c35000;
  return this;
}


/* 004387e0 size=70 */

void __cdecl FUN_004387e0(int *param_1)

{
  FUN_00438ac0((int)param_1);
  FUN_00438b50(param_1);
  if (param_1 != (int *)0x0) {
    param_1[6] = (int)&PTR_FUN_004cc41c;
    FUN_004b7c10((int)(param_1 + 7));
    param_1[6] = (int)&PTR_LAB_004cb514;
    FUN_004b8020(param_1);
    FUN_00430df0((undefined *)param_1);
  }
  return;
}


/* 00438830 size=15 */

undefined4 __cdecl FUN_00438830(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x74);
}


/* 00438840 size=16 */

void __cdecl FUN_00438840(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x74) = param_2;
  }
  return;
}


/* 00438850 size=15 */

undefined4 __cdecl FUN_00438850(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x48);
}


/* 00438860 size=15 */

undefined4 __cdecl FUN_00438860(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x4c);
}


/* 00438870 size=304 */

undefined4 __cdecl FUN_00438870(int param_1,int param_2,int param_3,int param_4,int *param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int *this;
  int *piVar3;
  
  this = (int *)0x0;
  if (param_1 == 0) {
    return 0;
  }
  piVar3 = *(int **)(param_1 + 0x34);
  if (piVar3 == (int *)0x0) {
    FUN_004b7c60(param_1 + 0x1c,*(int *)(param_1 + 0x24));
    piVar3 = *(int **)(param_1 + 0x34);
    if (piVar3 == (int *)0x0) goto LAB_004388a6;
  }
  *(int *)(param_1 + 0x34) = *piVar3;
LAB_004388a6:
  piVar3[2] = (int)piVar3;
  *(undefined2 *)(piVar3 + 6) = (*(uint16_t*)((char*)&param_5+0));
  piVar3[3] = param_4;
  piVar3[4] = param_3;
  piVar3[5] = param_2;
  if (((uint)param_5 & 1) == 0) {
    iVar1 = *(int *)(param_1 + 0x3c);
    *piVar3 = iVar1;
    puVar2 = *(undefined4 **)(iVar1 + 4);
    piVar3[1] = (int)puVar2;
    *puVar2 = piVar3;
    *(int **)(*piVar3 + 4) = piVar3;
  }
  else {
    *piVar3 = param_1 + 0x3c;
    puVar2 = *(undefined4 **)(param_1 + 0x40);
    piVar3[1] = (int)puVar2;
    *puVar2 = piVar3;
    *(int **)(*piVar3 + 4) = piVar3;
    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
  }
  if (((uint)param_5 & 2) == 0) {
    puVar2 = FUN_0046b170(&param_5,0x44c,0x44c);
    this = (int *)*puVar2;
    if (this != (int *)0x0) {
      (**(code **)(*this + 4))();
    }
    if (param_5 != (int *)0x0) {
      (**(code **)(*param_5 + 8))();
    }
    *(undefined1 *)this[0x15] = 0x32;
    FUN_004385b0(this,(short)piVar3[3]);
    FUN_00438f40(this,piVar3[4]);
    FUN_0046b440(this,(char *)piVar3[5]);
    FUN_004657c0(*(void **)(param_1 + 0x6c),this,*(float **)(param_1 + 0x70),0x80);
  }
  if ((*(byte *)(param_1 + 0x54) & 4) != 0) {
    FUN_00438480((short)param_4,param_3,param_2);
  }
  *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x4c) + 1;
  if (this != (int *)0x0) {
    (**(code **)(*this + 8))();
  }
  return 1;
}


/* 004389a0 size=282 */

void __cdecl FUN_004389a0(int param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  int *this;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  int *local_4;
  
  iVar4 = param_1;
  if (param_1 != 0) {
    puVar5 = FUN_0046b170(&local_4,0x44c,0x44c);
    this = (int *)*puVar5;
    if (this != (int *)0x0) {
      (**(code **)(*this + 4))();
    }
    if (local_4 != (int *)0x0) {
      (**(code **)(*local_4 + 8))();
    }
    piVar1 = (int *)(param_1 + 0x40);
    iVar2 = param_1 + 0x3c;
    param_1 = *piVar1;
    if (*piVar1 != iVar2) {
      do {
        iVar2 = *(int *)(param_1 + 8);
        if ((*(byte *)(iVar2 + 0x18) & 2) != 0) {
          uVar7 = 0xffffffff;
          pcVar8 = *(char **)(iVar2 + 0x14);
          do {
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            cVar3 = *pcVar8;
            pcVar8 = pcVar8 + 1;
          } while (cVar3 != '\0');
          iVar6 = ((uint)*(ushort *)((int)this + 0x36) - (uint)*(ushort *)(this + 0xe)) + -7;
          if (iVar6 < 0) {
            iVar6 = 0;
          }
          if (iVar6 <= (int)(~uVar7 + 5)) {
            FUN_004657c0(*(void **)(iVar4 + 0x6c),this,*(float **)(iVar4 + 0x70),0x80);
            *(undefined2 *)(this + 0xe) = 1;
            *(undefined2 *)(this + 0xd) = 1;
          }
          *(undefined1 *)this[0x15] = 0x32;
          FUN_004385b0(this,*(undefined2 *)(iVar2 + 0xc));
          FUN_00438f40(this,*(undefined4 *)(iVar2 + 0x10));
          FUN_0046b440(this,*(char **)(iVar2 + 0x14));
          *(ushort *)(iVar2 + 0x18) = *(ushort *)(iVar2 + 0x18) & 0xfffd;
        }
        param_1 = *(int *)(param_1 + 4);
      } while (param_1 != iVar4 + 0x3c);
    }
    if (0 < (int)(*(ushort *)(this + 0xd) - 1)) {
      FUN_004657c0(*(void **)(iVar4 + 0x6c),this,*(float **)(iVar4 + 0x70),0x80);
    }
    if (this != (int *)0x0) {
      (**(code **)(*this + 8))();
    }
  }
  return;
}


/* 00438ac0 size=49 */

void __cdecl FUN_00438ac0(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x40);
  while (iVar3 != param_1 + 0x3c) {
    iVar2 = *(int *)(iVar3 + 4);
    puVar1 = (undefined4 *)(iVar3 + 8);
    iVar3 = iVar2;
    if ((*(byte *)((int *)*puVar1 + 6) & 4) == 0) {
      FUN_00438b00(param_1,(int *)*puVar1);
    }
  }
  return;
}


/* 00438b00 size=68 */

void __cdecl FUN_00438b00(int param_1,int *param_2)

{
  *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x4c) + -1;
  if ((*(byte *)(param_2 + 6) & 1) != 0) {
    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + -1;
  }
  *(int *)(*param_2 + 4) = param_2[1];
  *(int *)param_2[1] = *param_2;
  param_2[1] = (int)param_2;
  *param_2 = (int)param_2;
  if ((param_2 != (int *)0x0) && (param_1 != -0x1c)) {
    *param_2 = *(int *)(param_1 + 0x34);
    *(int **)(param_1 + 0x34) = param_2;
  }
  return;
}


/* 00438b50 size=148 */

void __cdecl FUN_00438b50(int *param_1)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = param_1;
  if ((param_1 != (int *)0x0) && (param_1[0x14] == 1)) {
    puVar3 = FUN_0046b170(&param_1,0x44c,0x44c);
    piVar1 = (int *)*puVar3;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 4))();
    }
    if (param_1 != (int *)0x0) {
      (**(code **)(*param_1 + 8))();
    }
    *(undefined1 *)piVar1[0x15] = 0x34;
    FUN_004657c0((void *)piVar2[0x1b],piVar1,(float *)piVar2[0x1c],0x80);
    (*(code *)piVar2[0x19])(piVar2,piVar2[0x1e]);
    *(ushort *)(piVar2[0x1f] + 0x18) = *(ushort *)(piVar2[0x1f] + 0x18) & 0xfffb;
    piVar2[0x1f] = 0;
    piVar2[0x1e] = 0;
    piVar2[0x14] = 0;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))();
    }
  }
  return;
}


/* 00438bf0 size=266 */

undefined4 __cdecl FUN_00438bf0(uint param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  ushort uVar5;
  uint uVar6;
  
  bVar1 = **(byte **)(param_2 + 0x54) & 0x3f;
  if (bVar1 == 0x36) {
    uVar5 = *(ushort *)(param_2 + 0x38);
    uVar2 = (uint)*(ushort *)(param_2 + 0x34);
    uVar4 = (uint)uVar5;
    if (0 < (int)(uVar2 - uVar4)) {
      uVar6 = param_1;
      do {
        if ((uVar4 + 2 < *(uint *)(param_2 + 0x58)) && (uVar4 + 2 <= uVar2)) {
          uVar6 = (uint)*(ushort *)(uVar4 + *(int *)(param_2 + 0x54));
          *(ushort *)(param_2 + 0x38) = uVar5 + 2;
        }
        else {
          *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 2;
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
          }
        }
        piVar3 = (int *)FUN_00438d00(param_1,uVar6 & 0x7fff);
        if (piVar3 != (int *)0x0) {
          if ((uVar6 & 0x8000) == 0) {
            *(byte *)(piVar3 + 6) = *(byte *)(piVar3 + 6) | 2;
          }
          else {
            FUN_00438b00(param_1,piVar3);
          }
        }
        uVar5 = *(ushort *)(param_2 + 0x38);
        uVar2 = (uint)*(ushort *)(param_2 + 0x34);
        uVar4 = (uint)uVar5;
      } while (0 < (int)(uVar2 - uVar4));
    }
    return 1;
  }
  if (bVar1 != 0x38) {
    return 0;
  }
  if (*(int *)(param_1 + 0x50) == 1) {
    *(undefined4 *)(param_1 + 0x80) = 0;
  }
  return 1;
}


/* 00438d00 size=44 */

int __cdecl FUN_00438d00(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x40);
  if (iVar1 != param_1 + 0x3c) {
    do {
      if (*(uint *)(*(int *)(iVar1 + 8) + 0xc) == (param_2 & 0xffff)) {
        return *(int *)(iVar1 + 8);
      }
      iVar1 = *(int *)(iVar1 + 4);
    } while (iVar1 != param_1 + 0x3c);
  }
  return 0;
}


/* 00438d30 size=211 */

void __cdecl FUN_00438d30(int param_1,float param_2)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x50) == 0) {
      piVar1 = (int *)FUN_00438e10(param_1);
      if (piVar1 != (int *)0x0) {
        *(undefined4 *)(param_1 + 0x5c) = 0;
        if (((*(uint *)(param_1 + 0x54) & 2) == 0) &&
           (((*(uint *)(param_1 + 0x54) & 1) == 0 || ((*(byte *)(piVar1 + 6) & 1) != 0)))) {
          iVar2 = (**(code **)(param_1 + 0x60))(param_1,piVar1[5]);
          if (iVar2 != 0) {
            *(byte *)(piVar1 + 6) = *(byte *)(piVar1 + 6) | 4;
            *(int **)(param_1 + 0x7c) = piVar1;
            *(int *)(param_1 + 0x78) = iVar2;
            *(undefined4 *)(param_1 + 0x50) = 1;
            *(undefined4 *)(param_1 + 0x80) = 0;
            *(int *)(param_1 + 0x84) = piVar1[4];
            return;
          }
          iVar2 = (**(code **)(param_1 + 0x68))(param_1,piVar1[5]);
          if (iVar2 == 1) {
            *(int *)(*piVar1 + 4) = piVar1[1];
            *(int *)piVar1[1] = *piVar1;
            piVar1[1] = (int)piVar1;
            *piVar1 = (int)piVar1;
            if (param_1 != -0x1c) {
              *piVar1 = *(int *)(param_1 + 0x34);
              *(int **)(param_1 + 0x34) = piVar1;
              return;
            }
          }
        }
      }
    }
    else if (*(int *)(param_1 + 0x50) == 1) {
      *(float *)(param_1 + 0x5c) = param_2 + *(float *)(param_1 + 0x5c);
      FUN_00438e40(param_1);
    }
  }
  return;
}


/* 00438e10 size=33 */

int __cdecl FUN_00438e10(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x40);
  while( true ) {
    if (iVar1 == param_1 + 0x3c) {
      return 0;
    }
    if ((*(byte *)(*(int *)(iVar1 + 8) + 0x18) & 2) != 0) break;
    iVar1 = *(int *)(iVar1 + 4);
  }
  return *(int *)(iVar1 + 8);
}


/* 00438e40 size=247 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00438e40(int param_1)

{
  int *this;
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  int *local_450;
  undefined4 auStack_44c [275];
  
  if (*(int *)(param_1 + 0x80) != 6) {
    puVar2 = FUN_0046b170(&local_450,0x44c,0x44c);
    this = (int *)*puVar2;
    if (this != (int *)0x0) {
      (**(code **)(*this + 4))();
    }
    if (local_450 != (int *)0x0) {
      (**(code **)(*local_450 + 8))();
    }
    if (_DAT_004cc42c / *(float *)(param_1 + 0x5c) <= *(float *)(param_1 + 0x58)) {
      *(undefined1 *)this[0x15] = 0x35;
      uVar1 = *(uint *)(param_1 + 0x84);
      uVar3 = 0x424;
      if (uVar1 < 0x425) {
        uVar3 = uVar1;
      }
      (**(code **)(**(int **)(param_1 + 0x78) + 8))(auStack_44c,uVar3);
      FUN_0046b480(this,auStack_44c,uVar3);
      FUN_004657c0(*(void **)(param_1 + 0x6c),this,*(float **)(param_1 + 0x70),0x80);
      if (uVar1 < 0x425) {
        FUN_00438b00(param_1,*(int **)(param_1 + 0x7c));
        *(undefined4 *)(param_1 + 0x7c) = 0;
        (**(code **)(param_1 + 100))(param_1,*(undefined4 *)(param_1 + 0x78));
        *(undefined4 *)(param_1 + 0x78) = 0;
      }
      *(undefined4 *)(param_1 + 0x5c) = 0;
      *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + 1;
    }
    if (this != (int *)0x0) {
      (**(code **)(*this + 8))();
    }
  }
  return;
}


/* 00438f40 size=356 */

/* WARNING: Removing unreachable block (ram,0x00439010) */

void __thiscall FUN_00438f40(void *this,undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if ((uint)*(ushort *)((int)this + 0x36) <= *(ushort *)((int)this + 0x38) + 4) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
    }
    *(uint *)((int)this + 0x40) = *(uint *)((int)this + 0x40) | 4;
    return;
  }
  if (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4) {
    do {
      uVar1 = *(uint *)((int)this + 0x58);
      if (*(int *)((int)this + 0x5c) == 0) {
        iVar2 = FUN_0040c920(&DAT_004ecc58,0,*(int *)((int)this + 0x60) + uVar1 + 1);
        if (iVar2 != 0) {
          uVar4 = 0;
          if (uVar1 != 0) {
            do {
              uVar3 = uVar4 + 1;
              *(undefined1 *)(uVar4 + iVar2) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar3);
              uVar4 = uVar3;
            } while (uVar3 < uVar1);
          }
          uVar4 = uVar1;
          if (uVar1 < *(uint *)((int)this + 0x58)) {
            do {
              uVar4 = uVar4 + 1;
              *(undefined1 *)(uVar4 + iVar2) =
                   *(undefined1 *)(*(int *)((int)this + 0x54) + -1 + uVar4);
            } while (uVar4 < *(uint *)((int)this + 0x58));
          }
          *(undefined1 *)(uVar1 + iVar2) = 0;
          if (*(int *)((int)this + 0x54) != 0) {
            FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x54));
            *(undefined4 *)((int)this + 0x54) = 0;
            *(undefined4 *)((int)this + 0x5c) = 0;
          }
          *(int *)((int)this + 0x54) = iVar2;
          *(undefined4 *)((int)this + 0x5c) = *(undefined4 *)((int)this + 0x60);
          goto LAB_0043902c;
        }
      }
      else {
        *(int *)((int)this + 0x5c) = *(int *)((int)this + 0x5c) + -1;
        *(undefined1 *)(*(int *)((int)this + 0x54) + uVar1) = 0;
LAB_0043902c:
        *(int *)((int)this + 0x58) = *(int *)((int)this + 0x58) + 1;
      }
    } while (*(uint *)((int)this + 0x58) <= *(ushort *)((int)this + 0x34) + 4);
  }
  *(undefined4 *)(*(int *)((int)this + 0x54) + (uint)*(ushort *)((int)this + 0x38)) = param_1;
  *(short *)((int)this + 0x38) = *(short *)((int)this + 0x38) + 4;
  *(short *)((int)this + 0x34) = *(short *)((int)this + 0x34) + 4;
  return;
}


/* 004390d0 size=52 */

undefined4 * __thiscall FUN_004390d0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cc41c;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00439110 size=10 */

void FUN_00439110(void)

{
  FUN_0043911a();
  return;
}


/* 0043911a size=5 */

void FUN_0043911a(void)

{
  return;
}


/* 0043911f size=10 */

void FUN_0043911f(void)

{
  FUN_00439129();
  return;
}


/* 00439129 size=5 */

void FUN_00439129(void)

{
  return;
}


/* 0043912e size=10 */

void FUN_0043912e(void)

{
  FUN_00439138();
  return;
}


/* 00439138 size=5 */

void FUN_00439138(void)

{
  return;
}


/* 0043913d size=690 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0043913d: lifted from original x86 -> lt_lifted.c */


/* 004393ef size=135 */

void __cdecl
FUN_004393ef(int *param_1,undefined4 *param_2,float *param_3,float *param_4,undefined4 *param_5,
            undefined4 param_6,undefined4 param_7)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  float10 fVar4;
  undefined4 *puVar5;
  undefined4 local_1c;
  undefined4 local_18;
  float *local_14;
  void *local_10;
  int *local_c;
  undefined4 local_8;
  
  FUN_00439476(&local_1c);
  local_1c = param_6;
  local_18 = param_7;
  local_14 = param_3;
  local_10 = DAT_004e9984;
  local_c = param_1;
  puVar5 = &local_1c;
  piVar1 = (int *)(**(code **)(*param_1 + 4))();
  iVar2 = FUN_00445de0(piVar1,puVar5);
  if (iVar2 == 0) {
    *param_5 = 0xffffffff;
    *param_2 = 0;
  }
  else {
    uVar3 = (**(code **)(*param_1 + 8))(local_8);
    *param_5 = uVar3;
    *param_2 = local_8;
    fVar4 = (float10)FUN_0043a3cb(DAT_004e9984,local_14);
    *param_4 = (float)fVar4;
  }
  return;
}


/* 00439476 size=53 */

undefined4 * __fastcall FUN_00439476(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[5] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  return param_1;
}


/* 004394ab size=76 */

void __cdecl
FUN_004394ab(int *param_1,int *param_2,float *param_3,float *param_4,undefined4 *param_5,
            void *param_6,undefined4 param_7)

{
  int *piVar1;
  float10 fVar2;
  void *pvVar3;
  float *pfVar4;
  undefined4 *puVar5;
  undefined4 local_14 [4];
  
  *param_5 = 0xffffffff;
  puVar5 = local_14;
  pvVar3 = param_6;
  pfVar4 = param_3;
  piVar1 = (int *)(**(code **)(*param_1 + 4))();
  piVar1 = FUN_00445e00(piVar1,pvVar3,param_7,pfVar4,puVar5);
  *param_2 = (int)piVar1;
  if (*param_2 != 0) {
    fVar2 = (float10)FUN_0043a3cb(param_6,param_3);
    *param_4 = (float)fVar2;
  }
  return;
}


/* 004394f7 size=104 */

uint __cdecl FUN_004394f7(int *param_1)

{
  int iVar1;
  uint uVar2;
  
  if (((param_1[0x22] & 0x3000U) == 0) && (DAT_004e9980 == '\0')) {
    uVar2 = 0;
  }
  else {
    if ((DAT_004e99b0 == '\0') && (iVar1 = (**(code **)(*param_1 + 0x34))(), iVar1 == 0)) {
      return 0;
    }
    uVar2 = FUN_0043955f(DAT_004e9984,DAT_004e9984 + 3,(int)param_1);
    uVar2 = uVar2 & 0xff;
  }
  return uVar2;
}


/* 0043955f size=326 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0043955f: lifted from original x86 -> lt_lifted.c */


/* 004396a5 size=1752 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004396a5: lifted from original x86 -> lt_lifted.c */


/* 00439d7d size=389 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort __cdecl FUN_00439d7d(undefined4 param_1,undefined4 param_2,int param_3)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  ushort uVar4;
  float10 fVar5;
  float local_14;
  float fStack_10;
  float fStack_c;
  float local_8;
  
  local_8 = (DAT_004e9970 * *(float *)(param_3 + 0x194) + DAT_004e9974 * *(float *)(param_3 + 0x198)
            + DAT_004e9978 * *(float *)(param_3 + 0x19c)) - _DAT_004e99b4;
  fVar1 = -*(float *)(param_3 + 0x1ac);
  uVar4 = (ushort)(fVar1 < local_8) << 8 | (ushort)(NAN(fVar1) || NAN(local_8)) << 10 |
          (ushort)(fVar1 == local_8) << 0xe;
  if (fVar1 < local_8 || (fVar1 == local_8) != 0) {
    fVar1 = _DAT_004e9994 + *(float *)(param_3 + 0x1ac);
    uVar4 = (ushort)(fVar1 < local_8) << 8 | (ushort)(NAN(fVar1) || NAN(local_8)) << 10 |
            (ushort)(fVar1 == local_8) << 0xe;
    if (fVar1 >= local_8) {
      fStack_c = (DAT_004e9968 * local_8 + DAT_004e9984[2]) - *(float *)(param_3 + 0x19c);
      fStack_10 = (DAT_004e9964 * local_8 + DAT_004e9984[1]) - *(float *)(param_3 + 0x198);
      local_14 = (DAT_004e9960 * local_8 + *DAT_004e9984) - *(float *)(param_3 + 0x194);
      fVar1 = *(float *)(param_3 + 0x1ac);
      fVar2 = *(float *)(param_3 + 0x1ac);
      fVar5 = FUN_0043a41f(&local_14);
      bVar3 = fVar5 < (float10)(fVar1 * fVar2);
      return CONCAT11(bVar3,bVar3);
    }
  }
  return uVar4;
}


/* 00439f02 size=634 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00439f02: lifted from original x86 -> lt_lifted.c */


/* 0043a17c size=223 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_0043a17c(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  
  fVar1 = _DAT_004cba94 /
          (param_2[0xe] * param_3[2] + param_2[0xd] * param_3[1] + param_2[0xc] * *param_3 +
          param_2[0xf]);
  *param_1 = (param_2[2] * param_3[2] + param_2[1] * param_3[1] + *param_2 * *param_3 + param_2[3])
             * fVar1;
  param_1[1] = (param_2[6] * param_3[2] + param_2[5] * param_3[1] + param_2[4] * *param_3 +
               param_2[7]) * fVar1;
  param_1[2] = (param_2[10] * param_3[2] + param_2[9] * param_3[1] + param_2[8] * *param_3 +
               param_2[0xb]) * fVar1;
  return (float10)fVar1;
}


/* 0043a25b size=230 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_0043a25b(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  
  fVar12 = _DAT_004cba94 /
           (param_1[0xe] * param_2[2] + param_1[0xd] * param_2[1] + param_1[0xc] * *param_2 +
           param_1[0xf]);
  fVar1 = param_1[4];
  fVar2 = *param_2;
  fVar3 = param_1[5];
  fVar4 = param_1[6];
  fVar5 = param_1[7];
  fVar6 = param_1[8];
  fVar7 = *param_2;
  fVar8 = param_1[9];
  fVar9 = param_2[1];
  fVar10 = param_1[10];
  fVar11 = param_1[0xb];
  *param_2 = (param_1[2] * param_2[2] + param_1[1] * param_2[1] + *param_1 * *param_2 + param_1[3])
             * fVar12;
  param_2[1] = (fVar4 * param_2[2] + fVar3 * param_2[1] + fVar1 * fVar2 + fVar5) * fVar12;
  param_2[2] = (fVar10 * param_2[2] + fVar8 * fVar9 + fVar6 * fVar7 + fVar11) * fVar12;
  return (float10)fVar12;
}


/* 0043a341 size=138 */

void __cdecl FUN_0043a341(float *param_1,float *param_2,float *param_3)

{
  *param_1 = param_2[2] * param_3[2] + param_2[1] * param_3[1] + *param_2 * *param_3;
  param_1[1] = param_2[6] * param_3[2] + param_2[5] * param_3[1] + param_2[4] * *param_3;
  param_1[2] = param_2[10] * param_3[2] + param_2[9] * param_3[1] + param_2[8] * *param_3;
  return;
}


/* 0043a3cb size=84 */

int __thiscall FUN_0043a3cb(void *this,float *param_1)

{
  float local_10;
  float local_c;
  float local_8;
  
  local_8 = *(float *)((int)this + 8) - param_1[2];
  local_c = *(float *)((int)this + 4) - param_1[1];
  local_10 = *(float *)this - *param_1;
  FUN_0043a41f(&local_10);
  return;
}


/* 0043a41f size=47 */

float10 __fastcall FUN_0043a41f(float *param_1)

{
  return (float10)param_1[2] * (float10)param_1[2] +
         (float10)param_1[1] * (float10)param_1[1] + (float10)*param_1 * (float10)*param_1;
}


/* 0043a44e size=36 */

void FUN_0043a44e(void)

{
  if ((DAT_004ed04c & 1) == 0) {
    DAT_004ed04c = DAT_004ed04c | 1;
  }
  FUN_0043a472();
  return;
}


/* 0043a472 size=16 */

void FUN_0043a472(void)

{
  FUN_004b9cf5(FUN_004a82f0);
  return;
}


/* 0043a490 size=842 */

/* FUN_0043a490: lifted from original x86 -> lt_lifted.c */


/* 0043a7e0 size=1287 */

/* FUN_0043a7e0: lifted from original x86 -> lt_lifted.c */


/* 0043ada0 size=193 */

void __cdecl FUN_0043ada0(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar3;
  int local_4;
  
  local_4 = 0;
  for (iVar1 = *(int *)(param_2 + 0x98); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x24)) {
    in_EAX = FUN_0047a090(param_1,CONCAT22((short)((uint)in_EAX >> 0x10),
                                           *(undefined2 *)(iVar1 + 0x1e)));
    if ((in_EAX != 0) && (*(short *)(in_EAX + 0xba) != -1)) {
      local_4 = local_4 + 1;
    }
  }
  (**(code **)(*param_3 + 0x24))(&local_4,2);
  uVar3 = extraout_ECX;
  for (iVar1 = *(int *)(param_2 + 0x98); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x24)) {
    iVar2 = FUN_0047a090(param_1,CONCAT22((short)((uint)uVar3 >> 0x10),*(undefined2 *)(iVar1 + 0x1e)
                                         ));
    uVar3 = extraout_ECX_00;
    if ((iVar2 != 0) && (*(short *)(iVar2 + 0xba) != -1)) {
      (**(code **)(*param_3 + 0x24))(iVar1,0xc);
      (**(code **)(*param_3 + 0x24))(iVar1 + 0xc,0x10);
      (**(code **)(*param_3 + 0x24))(iVar2 + 0xba,2);
      (**(code **)(*param_3 + 0x24))(iVar1 + 0x20,4);
      uVar3 = extraout_ECX_01;
    }
  }
  return;
}


/* 0043ae70 size=193 */

void __cdecl FUN_0043ae70(undefined4 param_1,int param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined1 uStack00000000;
  int local_4;
  
  local_4 = 0;
  for (iVar3 = *(int *)(*(int *)(param_2 + 400) + 4); iVar3 != *(int *)(param_2 + 400);
      iVar3 = *(int *)(iVar3 + 4)) {
    piVar1 = *(int **)(iVar3 + 8);
    if ((piVar1[1] == param_2) &&
       (((*piVar1 == 0 || (*piVar1 == 1)) && (*(short *)(piVar1[2] + 0xba) != -1)))) {
      local_4 = local_4 + 1;
    }
  }
  (**(code **)(*param_3 + 0x24))(&local_4,2);
  iVar3 = *(int *)(*(int *)(param_2 + 400) + 4);
  if (iVar3 != *(int *)(param_2 + 400)) {
    do {
      piVar1 = *(int **)(iVar3 + 8);
      if (((piVar1[1] == param_2) && ((*piVar1 == 0 || (*piVar1 == 1)))) &&
         (iVar2 = piVar1[2], *(short *)(iVar2 + 0xba) != -1)) {
        (**(code **)(*param_3 + 0x24))(&uStack00000000,1);
        (**(code **)(*param_3 + 0x24))(iVar2 + 0xba,2);
      }
      iVar3 = *(int *)(iVar3 + 4);
    } while (iVar3 != *(int *)(param_2 + 400));
  }
  return;
}


/* 0043af40 size=1342 */

int __cdecl FUN_0043af40(undefined4 param_1,int *param_2)

{
  int iVar1;
  undefined1 **ppuVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  undefined4 unaff_EBP;
  undefined1 *puVar7;
  float10 fVar8;
  byte unaff_retaddr;
  undefined1 auStack_496 [2];
  int *piStack_494;
  char cStack_48d;
  int *piStack_48c;
  undefined4 uStack_488;
  uint uStack_484;
  undefined1 *puStack_480;
  int iStack_47c;
  undefined1 *puStack_478;
  uint uStack_474;
  undefined1 *puStack_470;
  undefined4 uStack_46c;
  undefined1 *puStack_468;
  undefined4 uStack_464;
  undefined1 *puStack_460;
  undefined4 uStack_45c;
  undefined1 *puStack_458;
  undefined4 uStack_454;
  undefined1 *puStack_450;
  undefined4 uStack_44c;
  undefined1 auStack_438 [4];
  undefined1 auStack_434 [12];
  undefined1 auStack_428 [4];
  undefined1 auStack_424 [4];
  undefined1 local_420 [184];
  undefined1 auStack_368 [16];
  undefined1 auStack_358 [240];
  undefined1 auStack_268 [604];
  int iStack_c;
  
  puStack_450 = local_420;
  uStack_44c = 4;
  uStack_454 = 0x43af5f;
  (**(code **)(*param_2 + 8))();
  puStack_458 = auStack_438;
  uStack_454 = 4;
  uStack_45c = 0x43af6d;
  (**(code **)(*param_2 + 8))();
  uStack_45c = 4;
  DAT_004e99c8 = unaff_EBP;
  if ((unaff_retaddr & 1) == 0) {
    puStack_460 = auStack_424;
    uStack_464 = 0x43afff;
    (**(code **)(*param_2 + 8))();
    puStack_468 = auStack_434;
    uStack_464 = 4;
    uStack_46c = 0x43b00d;
    (**(code **)(*param_2 + 8))();
    puStack_470 = auStack_428;
    uStack_46c = 4;
    uStack_474 = 0x43b01b;
    (**(code **)(*param_2 + 8))();
    puStack_478 = auStack_434;
    uStack_474 = 4;
    iStack_47c = 0x43b029;
    (**(code **)(*param_2 + 8))();
    puStack_480 = auStack_434;
    iStack_47c = 4;
    uStack_484 = 0x43b037;
    (**(code **)(*param_2 + 8))();
    uStack_488 = &puStack_450;
    uStack_484 = 4;
    piStack_48c = (int *)0x43b045;
    (**(code **)(*param_2 + 8))();
    iVar5 = *param_2;
    ppuVar2 = &puStack_450;
  }
  else {
    puStack_460 = (undefined1 *)(iStack_c + 0x8d0);
    uStack_464 = 0x43af99;
    (**(code **)(*param_2 + 8))();
    puStack_468 = (undefined1 *)(iStack_c + 0x8c8);
    uStack_464 = 4;
    uStack_46c = 0x43afa9;
    (**(code **)(*param_2 + 8))();
    puStack_470 = (undefined1 *)(iStack_c + 0x8cc);
    uStack_46c = 4;
    uStack_474 = 0x43afb9;
    (**(code **)(*param_2 + 8))();
    puStack_478 = (undefined1 *)(iStack_c + 0x8dc);
    uStack_474 = 4;
    iStack_47c = 0x43afc9;
    (**(code **)(*param_2 + 8))();
    puStack_480 = (undefined1 *)(iStack_c + 0x8d4);
    iStack_47c = 4;
    uStack_484 = 0x43afd9;
    (**(code **)(*param_2 + 8))();
    uStack_488 = (undefined1 **)(iStack_c + 0x8d8);
    uStack_484 = 4;
    piStack_48c = (int *)0x43afe9;
    (**(code **)(*param_2 + 8))();
    iVar5 = *param_2;
    ppuVar2 = (undefined1 **)(iStack_c + 0x8c4);
  }
  piStack_48c = (int *)0x4;
  (**(code **)(iVar5 + 8))();
  (**(code **)(*param_2 + 8))();
  if (uStack_474 != 0xffffffff) {
    if (uStack_474 != *(uint *)(iStack_c + 0x334)) {
      FUN_004356e0();
      if (DAT_004e4420 < 1) {
        return 0x49;
      }
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_RestoreObjects_004d95f4);
      return 0x49;
    }
    uStack_484 = 0;
    if (uStack_474 != 0) {
      do {
        uVar6 = uStack_484;
        (**(code **)(*param_2 + 8))(&puStack_478);
        iStack_47c = *(int *)(*(int *)(*(int *)(iStack_c + 0x330) + uVar6 * 4) + 4);
        if (puStack_478 != *(undefined1 **)(iStack_47c + 0xb4)) {
          FUN_004356e0();
          if (DAT_004e4420 < 1) {
            return 0x49;
          }
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_RestoreObjects_004d95f4);
          return 0x49;
        }
        puVar7 = (undefined1 *)0x0;
        if (puStack_478 != (undefined1 *)0x0) {
          iVar5 = 0;
          do {
            (**(code **)(*param_2 + 8))(iVar5 + 6 + *(int *)(iStack_47c + 0xb0));
            puVar7 = puVar7 + 1;
            iVar5 = iVar5 + 0x24;
          } while (puVar7 < puStack_478);
          uVar6 = uStack_484;
        }
        uStack_484 = uVar6 + 1;
      } while (uStack_484 < uStack_474);
    }
  }
  fVar8 = FUN_004a0540();
  *(float *)(iStack_c + 0x8c4) =
       (float)((float10)*(float *)(iStack_c + 0x8cc) -
              (fVar8 + (float10)*(float *)(iStack_c + 0x8c4)));
  if (puStack_470 != DAT_004d95d4) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_RestoreObjects_004d95f4);
    }
    return 0x45;
  }
  FUN_004898b0(iStack_c);
  (**(code **)(*param_2 + 8))((int)&uStack_488 + 3);
  cStack_48d = (char)((uint)ppuVar2 >> 0x18);
  while (cStack_48d != '\0') {
    (**(code **)(*param_2 + 0xc))(auStack_358,0x100);
    (**(code **)(*param_2 + 0xc))(&puStack_460,0x100);
    iVar5 = (**(code **)(*param_2 + 0x10))();
    if (iVar5 != 0) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_RestoreObjects_004d95d8);
      }
      return 0x4d;
    }
    FUN_004b9f62(auStack_268,(byte *)s__s__s_004d95ec,auStack_368);
    FUN_004200a0(iStack_c + 0xc84,(byte)auStack_268);
    (**(code **)(*param_2 + 8))(auStack_496 + -7,1);
  }
  (**(code **)(*param_2 + 0x18))(&piStack_48c);
  piVar3 = FUN_00430fb0((int)piStack_48c * 4);
  (**(code **)(*param_2 + 0x14))(ppuVar2);
  iVar5 = FUN_0043b480(iStack_c,param_2);
  if (iVar5 == 0) {
    piStack_48c = piVar3 + 1;
    do {
      piStack_48c = piStack_48c + 1;
      iVar5 = FUN_0043b480(iStack_c,param_2);
    } while (iVar5 == 0);
  }
  if (iVar5 == 2) {
    FUN_0046a9b0(iStack_c + 0x394);
    iVar5 = 0;
    if (0 < (int)ppuVar2) {
      piVar4 = piVar3;
      do {
        iVar1 = *piVar4;
        piVar4 = piVar4 + 1;
        *(short *)(iVar1 + 0xba) = (short)iVar5;
        iVar5 = iVar5 + 1;
      } while (iVar5 < (int)ppuVar2);
    }
    FUN_004898b0(iStack_c);
    (**(code **)(*param_2 + 0x14))(4);
    DAT_004e99c4 = 1;
    iVar5 = game_serialize_43c020(iStack_c,param_2);
    while (iVar5 == 0) {
      DAT_004e99c4 = DAT_004e99c4 + 1;
      iVar5 = game_serialize_43c020(iStack_c,param_2);
    }
    if ((iVar5 == 2) && (piStack_48c = (int *)0x0, 0 < (int)ppuVar2)) {
      piStack_494 = piVar3;
      do {
        iVar5 = FUN_0043c210((ushort)iStack_c,*piStack_494,param_2);
        if ((iVar5 != 0) ||
           (iVar5 = FUN_0043c310((ushort)iStack_c,*piStack_494,param_2), iVar5 != 0)) break;
        piStack_494 = piStack_494 + 1;
        piStack_48c = (int *)((int)piStack_48c + 1);
      } while ((int)piStack_48c < (int)ppuVar2);
    }
  }
  FUN_00430fe0((undefined *)piVar3);
  if ((iVar5 == 0) || (iVar5 == 2)) {
    FUN_004898b0(iStack_c);
    return 0;
  }
  return iVar5;
}


/* 0043b480 size=2972 */

/* WARNING: Removing unreachable block (ram,0x0043b508) */
/* WARNING: Removing unreachable block (ram,0x0043b510) */
/* WARNING: Removing unreachable block (ram,0x0043b515) */

/* FUN_0043b480: lifted from original x86 -> lt_lifted.c */


