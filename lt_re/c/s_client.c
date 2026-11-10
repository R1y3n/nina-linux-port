/* lithtech.exe decompilation - module s_client */
#include "ghidra_types.h"

/* 00471f90 size=987 */

/* repo: runtime/server/src/s_client.cpp */

undefined4 __cdecl s_client_471f90(undefined2 *param_1,int *param_2)

{
  undefined2 uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined2 *puVar7;
  uint uVar8;
  undefined2 *puVar9;
  int *this;
  undefined4 unaff_EDI;
  uint uStack_8;
  int *local_4;
  
  piVar4 = param_2;
  this = (int *)0x0;
  if ((param_2[0xef] == 1) || ((*(byte *)(param_2 + 0xf0) & 2) != 0)) {
    puVar5 = FUN_0046b170(&local_4,0x44c,0x44c);
    this = (int *)*puVar5;
    if (this != (int *)0x0) {
      (**(code **)(*this + 4))();
    }
    if (local_4 != (int *)0x0) {
      (**(code **)(*local_4 + 8))();
    }
    uStack_8 = 0;
    if (*(int *)(param_1 + 0x19a) != 0) {
      do {
        uVar8 = 0;
        iVar6 = *(int *)(*(int *)(*(int *)(param_1 + 0x198) + uStack_8 * 4) + 4);
        if (*(int *)(iVar6 + 0xb4) != 0) {
          param_2 = (int *)0x0;
          do {
            if (*(short *)((int)param_2 + *(int *)(iVar6 + 0xb0) + 6) != 0) {
              *(undefined2 *)(this + 0xe) = 1;
              *(undefined2 *)(this + 0xd) = 1;
              FUN_004385b0(this,(short)uStack_8);
              FUN_004385b0(this,(short)uVar8);
              FUN_004183a0(this,*(undefined1 *)((int)param_2 + *(int *)(iVar6 + 0xb0) + 6));
              FUN_00477830((int)param_1,(int)piVar4,0x13,this,0,0x80);
            }
            uVar8 = uVar8 + 1;
            param_2 = param_2 + 9;
          } while (uVar8 < *(uint *)(iVar6 + 0xb4));
        }
        uStack_8 = uStack_8 + 1;
      } while (uStack_8 < *(uint *)(param_1 + 0x19a));
    }
    puVar9 = param_1;
    FUN_00471d80((int)param_1,(int)piVar4);
    piVar4[0x43] = 0;
    FUN_00472370((int)puVar9,(uint)piVar4);
    FUN_004751d0((int)puVar9,(int)piVar4);
    piVar4[0xef] = 2;
  }
  else {
    puVar9 = param_1;
  }
  if ((piVar4[0xef] == 3) || ((*(byte *)(piVar4 + 0xf0) & 2) != 0)) {
    puVar5 = FUN_0046b170(&param_2,0x44c,0x44c);
    if (this != (int *)0x0) {
      (**(code **)(*this + 8))();
    }
    this = (int *)*puVar5;
    if (this != (int *)0x0) {
      (**(code **)(*this + 4))();
    }
    if (param_2 != (int *)0x0) {
      (**(code **)(*param_2 + 8))();
    }
    iVar6 = (**(code **)(**(int **)(puVar9 + 0x518) + 0x14))(piVar4,piVar4[0x44],piVar4[0x45]);
    if (iVar6 == 0) {
      FUN_00436670((byte *)s_Error__ServerShell__OnClientEnte_004db7f8,unaff_EDI);
      if (this != (int *)0x0) {
        (**(code **)(*this + 8))();
      }
      return 1;
    }
    iVar6 = *(int *)(iVar6 + 8);
    piVar4[0xeb] = iVar6;
    *(int **)(*(int *)(iVar6 + 400) + 0x1c) = piVar4;
    puVar7 = *(undefined2 **)(puVar9 + 0x582);
    if (puVar7 != puVar9 + 0x580) {
      do {
        piVar2 = *(int **)(puVar7 + 4);
        if ((short)piVar2[4] == *(short *)(piVar4[0xeb] + 0xb8)) {
          *(uint *)(piVar4[0xeb] + 0x124) = *(uint *)(piVar4[0xeb] + 0x124) & 0xffffff7f;
          *(int *)(*piVar2 + 4) = piVar2[1];
          *(int *)piVar2[1] = *piVar2;
          piVar2[1] = (int)piVar2;
          *piVar2 = (int)piVar2;
          *(int *)(puVar9 + 0x57e) = *(int *)(puVar9 + 0x57e) + -1;
          FUN_00430fe0((undefined *)piVar2);
          break;
        }
        puVar7 = *(undefined2 **)(puVar7 + 2);
      } while (puVar7 != puVar9 + 0x580);
    }
    if (piVar4[0x5c] == 0) {
      *(undefined2 *)(this + 0xe) = 1;
      *(undefined2 *)(this + 0xd) = 1;
      uVar1 = *(undefined2 *)(piVar4[0xeb] + 0xb8);
      if (*(ushort *)((int)this + 0x36) < 4) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
        }
        this[0x10] = this[0x10] | 4;
      }
      else {
        if ((uint)this[0x16] < 4) {
          do {
            param_1 = (undefined2 *)((uint)param_1 & 0xffffff00);
            FUN_00414b10(this + 0x14,(undefined1 *)this[0x16],(undefined1 *)&param_1,&DAT_004ecc58);
          } while ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 2);
        }
        *(undefined2 *)(this[0x15] + (uint)*(ushort *)(this + 0xe)) = uVar1;
        *(short *)(this + 0xe) = (short)this[0xe] + 2;
        *(short *)(this + 0xd) = (short)this[0xd] + 2;
      }
      FUN_00477830((int)puVar9,(int)piVar4,7,this,1,0x80);
    }
    *(undefined2 *)(piVar4 + 0x67) = 0;
    *(undefined2 *)(piVar4 + 0x65) = 0;
    puVar7 = *(undefined2 **)(puVar9 + 0x57a);
    if (puVar7 != puVar9 + 0x578) {
      do {
        param_1 = (undefined2 *)(piVar4[100] + (uint)*(ushort *)(*(int *)(puVar7 + 4) + 0xb8) * 4);
        uVar8 = FUN_00479170(puVar9,*(int *)(puVar7 + 4));
        *param_1 = (short)uVar8;
        puVar7 = *(undefined2 **)(puVar7 + 2);
      } while (puVar7 != puVar9 + 0x578);
    }
    for (puVar7 = *(undefined2 **)(puVar9 + 0x2e); puVar7 != puVar9 + 0x2c;
        puVar7 = *(undefined2 **)(puVar7 + 2)) {
      iVar6 = piVar4[100];
      iVar3 = *(int *)(*(int *)(*(int *)(puVar7 + 4) + 0xc) + 8);
      *(undefined2 *)(iVar6 + iVar3 * 4) = 3;
      *(undefined1 *)(iVar6 + 2 + iVar3 * 4) = 0;
    }
    piVar4[0xee] = 3;
  }
  if (this != (int *)0x0) {
    (**(code **)(*this + 8))();
  }
  return 0;
}


/* 004725f0 size=1697 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/server/src/s_client.cpp */

/* s_client_4725f0: lifted from original x86 -> lt_lifted.c */


/* 004730b0 size=246 */

/* repo: runtime/server/src/s_client.cpp */

void __cdecl s_client_4730b0(undefined2 *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  
  FUN_00436670((byte *)s_Removing_client__id__d__leaving___004db868,
               (uint)*(ushort *)(param_2 + 0xed));
  FUN_00472f10((int)param_1,(uint)param_2);
  FUN_00473070((int)param_1,(int)param_2);
  puVar3 = *(undefined2 **)(param_1 + 0x2e);
  if (puVar3 != param_1 + 0x2c) {
    do {
      iVar2 = *(int *)(puVar3 + 4);
      iVar1 = param_2[100] + *(int *)(*(int *)(iVar2 + 0xc) + 8) * 4;
      if ((((*(byte *)(iVar1 + 2) & 1) == 0) && ((*(uint *)(iVar2 + 0x34) & 0x428) != 0)) &&
         ((*(uint *)(iVar2 + 0x34) & 4) == 0)) {
        *(byte *)(iVar1 + 2) = *(byte *)(iVar1 + 2) | 1;
        if (*(int *)(iVar2 + 0x28) != 0) {
          *(int *)(iVar2 + 0x28) = *(int *)(iVar2 + 0x28) + -1;
        }
        if (*(int *)(iVar2 + 0x28) == 0) {
          *(undefined4 *)(iVar2 + 0x20) = 0;
        }
      }
      puVar3 = *(undefined2 **)(puVar3 + 2);
    } while (puVar3 != param_1 + 0x2c);
  }
  if ((*(byte *)(param_2 + 0xf0) & 2) != 0) {
    *(uint *)(param_1 + 0xd0) = *(uint *)(param_1 + 0xd0) & 0xfffffffd;
  }
  FUN_004732c0(param_1,param_2,0);
  (**(code **)(**(int **)(param_1 + 0x518) + 0xc))(param_2);
  *(int *)(*param_2 + 4) = param_2[1];
  *(int *)param_2[1] = *param_2;
  param_2[1] = (int)param_2;
  *param_2 = (int)param_2;
  *(int *)(param_1 + 0x4fa) = *(int *)(param_1 + 0x4fa) + -1;
  FUN_004731b0(param_1,(undefined *)param_2);
  return;
}


/* 004737e0 size=220 */

/* repo: runtime/server/src/s_client.cpp */

void __cdecl s_client_4737e0(int param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined1 auStack_1e [2];
  undefined1 auStack_16 [2];
  
  if (DAT_004e9878 != 0) {
    if (*(int *)(param_1 + 0xa18) == 0) {
      puVar2 = FUN_0049ade0(s_packet_trc_004db88c,&DAT_004d7acc);
      *(undefined4 **)(param_1 + 0xa18) = puVar2;
      if (puVar2 == (undefined4 *)0x0) {
        return;
      }
    }
    uVar3 = 0;
    if (*(short *)(param_2 + 0x34) != 0) {
      do {
        (**(code **)(**(int **)(param_1 + 0xa18) + 0x24))();
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(ushort *)(param_2 + 0x34));
    }
    if (DAT_004d8294 != 0) {
      piVar1 = *(int **)(param_1 + 0xa18);
      (**(code **)(*piVar1 + 0x24))();
      (**(code **)(*piVar1 + 0x24))();
      (**(code **)(*piVar1 + 0x24))(auStack_16 + 3);
      (**(code **)(*piVar1 + 0x24))(auStack_1e + 4,1);
      (**(code **)(*piVar1 + 0x24))(auStack_1e + -3,1);
    }
  }
  return;
}


