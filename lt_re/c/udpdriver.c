/* lithtech.exe decompilation - module udpdriver */
#include "ghidra_types.h"

/* 00465470 size=454 */

/* WARNING: Removing unreachable block (ram,0x004655fb) */
/* repo: runtime/kernel/net/src/sys/win/udpdriver.cpp, runtime/client/src/clientde_impl.cpp,
   runtime/client/src/clientmgr.cpp */

int * __thiscall udpdriver_465470(void *this,byte *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  char *pcVar8;
  bool bVar9;
  int *local_4;
  
  pcVar8 = s_local_004d674c;
  pbVar4 = param_1;
  do {
    bVar1 = *pbVar4;
    bVar9 = bVar1 < (byte)*pcVar8;
    if (bVar1 != *pcVar8) {
LAB_004654ad:
      iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
      goto LAB_004654b2;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar4[1];
    bVar9 = bVar1 < (byte)pcVar8[1];
    if (bVar1 != pcVar8[1]) goto LAB_004654ad;
    pbVar4 = pbVar4 + 2;
    pcVar8 = pcVar8 + 2;
  } while (bVar1 != 0);
  iVar5 = 0;
LAB_004654b2:
  if (iVar5 == 0) {
    local_4 = FUN_00447e00();
  }
  else {
    pcVar8 = s_internet_004d5ec0;
    do {
      bVar1 = *param_1;
      bVar9 = bVar1 < (byte)*pcVar8;
      if (bVar1 != *pcVar8) {
LAB_004654ee:
        iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
        goto LAB_004654f3;
      }
      if (bVar1 == 0) break;
      bVar1 = param_1[1];
      bVar9 = bVar1 < (byte)pcVar8[1];
      if (bVar1 != pcVar8[1]) goto LAB_004654ee;
      param_1 = param_1 + 2;
      pcVar8 = pcVar8 + 2;
    } while (bVar1 != 0);
    iVar5 = 0;
LAB_004654f3:
    if (iVar5 != 0) {
      return (int *)0x0;
    }
    local_4 = FUN_0049e030();
  }
  if (local_4 == (int *)0x0) {
    return (int *)0x0;
  }
  local_4[0x12] = (int)this;
  iVar5 = (**(code **)(*local_4 + 4))();
  if (iVar5 == 0) {
    (**(code **)*local_4)(1);
    return (int *)0x0;
  }
  uVar2 = *(uint *)((int)this + 0x44);
  if (*(int *)((int)this + 0x48) != 0) {
    *(int *)((int)this + 0x48) = *(int *)((int)this + 0x48) + -1;
    *(int **)(*(int *)((int)this + 0x40) + uVar2 * 4) = local_4;
    *(int *)((int)this + 0x44) = *(int *)((int)this + 0x44) + 1;
    return local_4;
  }
  iVar5 = (**(code **)(DAT_004ecc58 + 4))((uVar2 + 1 + *(int *)((int)this + 0x4c)) * 4);
  if (iVar5 == 0) {
    return local_4;
  }
  uVar6 = 0;
  if (uVar2 != 0) {
    do {
      uVar6 = uVar6 + 1;
      *(undefined4 *)(iVar5 + -4 + uVar6 * 4) =
           *(undefined4 *)(*(int *)((int)this + 0x40) + -4 + uVar6 * 4);
    } while (uVar6 < uVar2);
  }
  if (uVar2 < *(uint *)((int)this + 0x44)) {
    uVar6 = uVar2;
    puVar7 = (undefined4 *)(iVar5 + 4 + uVar2 * 4);
    do {
      uVar6 = uVar6 + 1;
      *puVar7 = *(undefined4 *)(*(int *)((int)this + 0x40) + -4 + uVar6 * 4);
      puVar7 = puVar7 + 1;
    } while (uVar6 < *(uint *)((int)this + 0x44));
  }
  *(int **)(iVar5 + uVar2 * 4) = local_4;
  iVar3 = *(int *)((int)this + 0x40);
  if (iVar3 != 0) {
    if (iVar3 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar3);
    }
    *(undefined4 *)((int)this + 0x40) = 0;
    *(undefined4 *)((int)this + 0x48) = 0;
  }
  *(int *)((int)this + 0x40) = iVar5;
  *(undefined4 *)((int)this + 0x48) = *(undefined4 *)((int)this + 0x4c);
  *(int *)((int)this + 0x44) = *(int *)((int)this + 0x44) + 1;
  return local_4;
}


/* 0049ba30 size=103 */

/* repo: runtime/kernel/net/src/sys/win/udpdriver.cpp, runtime/client/src/clientde_impl.cpp,
   runtime/client/src/clientmgr.cpp */

int __cdecl
udpdriver_49ba30(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  int iVar1;
  int iVar2;
  undefined4 local_4;
  
  local_4 = 0x10;
  iVar1 = Ordinal_17(param_2,param_3,param_4,0,param_5,&local_4);
  if ((iVar1 != 0) && (iVar1 != -1)) {
    return iVar1;
  }
  if (1 < DAT_004e9898) {
    iVar2 = Ordinal_111();
    if (iVar2 != 0x2733) {
      FUN_00436670((byte *)s_recvfrom_returned_error__d__max_p_004dd94c,iVar1);
    }
  }
  return -1;
}


/* 0049bde0 size=75 */

/* repo: runtime/kernel/net/src/sys/win/udpdriver.cpp */

int __thiscall udpdriver_49bde0(void *this,int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = *(uint *)((int)this + 0xa0);
  if (uVar1 != 0) {
    uVar3 = uVar1;
    do {
      iVar2 = *(int *)(uVar3 + 8);
      uVar3 = *(uint *)(uVar3 + 4) & -(uint)(*(uint *)(uVar3 + 4) != uVar1);
      if ((*(short *)(iVar2 + 0xbe) == *(short *)(param_1 + 2)) &&
         (*(int *)(iVar2 + 0xc0) == *(int *)(param_1 + 4))) {
        return iVar2;
      }
    } while (uVar3 != 0);
  }
  return 0;
}


/* 0049c2f0 size=201 */

/* repo: runtime/kernel/net/src/sys/win/udpdriver.cpp */

int udpdriver_49c2f0(void)

{
  int iVar1;
  int iVar2;
  undefined4 unaff_EDI;
  int iStack_28;
  char *pcStack_24;
  char *pcStack_20;
  undefined4 uStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  
  uStack_14 = 0x11;
  iStack_18 = 2;
  uStack_1c = 2;
  pcStack_20 = (char *)0x49c301;
  iVar1 = Ordinal_23();
  if (iVar1 == -1) {
    pcStack_20 = (char *)0x49c30d;
    pcStack_20 = udpdriver_49c3c0();
    pcStack_24 = s_socket___returned_SOCKET_ERROR__L_004dda5c;
    iStack_28 = 0x49c318;
    FUN_004317e0();
    return 0;
  }
  pcStack_20 = (char *)&uStack_14;
  uStack_14 = 1;
  pcStack_24 = (char *)0x8004667e;
  iStack_28 = iVar1;
  iVar2 = Ordinal_12();
  if (iVar2 != 0) {
    FUN_00436670((byte *)s_ioctlsocket_FIONBIO__nonblocking_004dda2c,iVar2);
    Ordinal_3(iVar1);
    return 0;
  }
  iVar2 = Ordinal_2(iVar1,unaff_EDI,0x10);
  if (iVar2 != 0) {
    udpdriver_49c3c0();
    FUN_004317e0();
    Ordinal_3(iVar1);
    return 0;
  }
  if (iStack_18 != 0) {
    iStack_28 = 0x10;
    Ordinal_6(iVar1,iStack_18,&iStack_28);
  }
  return iVar1;
}


/* 0049c3c0 size=43 */

/* repo: runtime/kernel/net/src/sys/win/udpdriver.cpp, FEAR/Shared/AnimationContext.cpp,
   NOLF/Shared/DebugMgr.cpp */

/* udpdriver_49c3c0: lifted from original x86 -> lt_lifted.c */


/* 0049d440 size=75 */

/* repo: runtime/kernel/net/src/sys/win/udpdriver.cpp, runtime/server/src/serverde_impl.cpp,
   runtime/client/src/clientde_impl.cpp */

int __cdecl udpdriver_49d440(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_1 + 0xa0);
  if (uVar1 != 0) {
    uVar3 = uVar1;
    do {
      iVar2 = *(int *)(uVar3 + 8);
      uVar3 = *(uint *)(uVar3 + 4) & -(uint)(*(uint *)(uVar3 + 4) != uVar1);
      if ((*(int *)(iVar2 + 0xc0) == *(int *)(param_2 + 4)) &&
         (*(short *)(iVar2 + 0xbe) == *(short *)(param_2 + 2))) {
        return iVar2;
      }
    } while (uVar3 != 0);
  }
  return 0;
}


