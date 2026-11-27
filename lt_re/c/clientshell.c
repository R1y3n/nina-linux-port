/* lithtech.exe decompilation - module clientshell */
#include "ghidra_types.h"

/* 00415000 size=332 */

/* repo: runtime/client/src/clientshell.cpp, runtime/client/src/clientmgr.cpp */

int __thiscall clientshell_415000(void *this,int param_1,undefined4 param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  int *piVar3;
  char local_100 [256];
  
  iVar2 = FUN_00415150((int)this);
  if (iVar2 != 0) {
    return iVar2;
  }
  if ((*(undefined4 **)(param_1 + 0x11e8) != (undefined4 *)0x0) &&
     (*(uint *)(param_1 + 0x11ec) != 0)) {
    FUN_00485ed0(*(void **)((int)this + 0x40),*(undefined4 **)(param_1 + 0x11e8),
                 *(uint *)(param_1 + 0x11ec));
  }
  iVar2 = FUN_00485e20(*(void **)((int)this + 0x40),
                       (undefined4 *)(*(int *)((int)this + 0x78) + 0x1648),
                       *(undefined4 **)(*(int *)((int)this + 0x78) + 0x1698));
  if (((iVar2 == 0) ||
      (bVar1 = FUN_00485eb0(*(int *)((int)this + 0x40)), CONCAT31(extraout_var,bVar1) == 0)) ||
     (iVar2 = servermgr_485c70(*(void **)((int)this + 0x40),(byte *)s_local_004d674c), iVar2 == 0))
  {
    FUN_004869b0(*(void **)((int)this + 0x40),local_100,0x100);
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_CClientShell__StartupLocal_004d6730);
    }
    return 0x31;
  }
  *(undefined4 *)((int)this + 0x3c) = 1;
  if (param_3 != 0) {
    FUN_00485cc0(*(void **)((int)this + 0x40),param_3);
  }
  FUN_00420e60(DAT_004e5178,1,(uint *)s_Connecting_locally_004d671c);
  piVar3 = udpdriver_465470((void *)(*(int *)((int)this + 0x78) + 0x510),(byte *)s_local_004d674c);
  *(int **)((int)this + 0x30) = piVar3;
  iVar2 = clientmgr_488d30(*(int *)((int)this + 0x40));
  (**(code **)(**(int **)((int)this + 0x30) + 0x10))(iVar2);
  netmgr_464bf0((void *)(*(int *)((int)this + 0x78) + 0x510),s_Client__004d6710,
                *(float *)(*(int *)((int)this + 0x78) + 0x136c),1);
  return 0;
}


/* 00415560 size=1031 */

/* repo: runtime/client/src/clientshell.cpp, runtime/client/src/clientmgr.cpp */

uint __fastcall clientshell_415560(int param_1)

{
  float fVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  LARGE_INTEGER local_118;
  int *local_110;
  LARGE_INTEGER local_10c;
  int *local_104;
  char local_100 [256];
  
  piVar2 = *(int **)(*(int *)(param_1 + 0x78) + 0x620);
  FUN_00424310(&local_118,0);
  local_110 = &DAT_004e517c;
  FUN_00424400(&local_118);
  netmgr_464bf0((void *)(*(int *)(param_1 + 0x78) + 0x510),s_Client__004d6710,
                *(float *)(*(int *)(param_1 + 0x78) + 0x136c),1);
  uVar5 = FUN_00424410((uint *)&local_118);
  *local_110 = *local_110 + (int)uVar5;
  FUN_00424310(&local_118,0);
  local_110 = &DAT_004e4e90;
  FUN_00424400(&local_118);
  FUN_00424310(&local_10c,0);
  local_104 = &DAT_004e5180;
  FUN_00424400(&local_10c);
  if ((*(int *)(param_1 + 0x40) != 0) && (DAT_004d82cc != 0)) {
    uVar4 = 0;
    iVar3 = FUN_00436610();
    if (iVar3 == 0) {
      iVar3 = FUN_00420880(0x4e9500,s_alwaysfocused_004d67c0);
      if ((iVar3 == 0) || (*(int *)(iVar3 + 0x18) != 0x3f800000)) {
        uVar4 = 1;
      }
    }
    iVar3 = servermgr_486690(*(void **)(param_1 + 0x40),uVar4,
                             *(float *)(*(int *)(param_1 + 0x78) + 0x136c));
    if (iVar3 == 0) {
      FUN_004869b0(*(void **)(param_1 + 0x40),local_100,0x100);
      FUN_004267b0(*(int *)(param_1 + 0x78),0x31,'\0');
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientShell__Update_004d6788);
      }
      uVar5 = FUN_00424410((uint *)&local_10c);
      *local_104 = *local_104 + (int)uVar5;
      uVar5 = FUN_00424410((uint *)&local_118);
      *local_110 = *local_110 + (int)uVar5;
      return 0x2000031;
    }
  }
  uVar5 = FUN_00424410((uint *)&local_10c);
  *local_104 = *local_104 + (int)uVar5;
  uVar5 = FUN_00424410((uint *)&local_118);
  *local_110 = *local_110 + (int)uVar5;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  FUN_00424310(&local_10c,0);
  local_104 = &DAT_004e4d64;
  FUN_00424400(&local_10c);
  FUN_00424310(&local_118,0);
  local_110 = &DAT_004e5184;
  FUN_00424400(&local_118);
  uVar4 = FUN_00492420(param_1);
  if (uVar4 != 0) {
    uVar5 = FUN_00424410((uint *)&local_118);
    *local_110 = *local_110 + (int)uVar5;
    uVar5 = FUN_00424410((uint *)&local_10c);
    *local_104 = *local_104 + (int)uVar5;
    return uVar4 | 0x2000000;
  }
  uVar5 = FUN_00424410((uint *)&local_118);
  *local_110 = *local_110 + (int)uVar5;
  uVar5 = FUN_00424410((uint *)&local_10c);
  *local_104 = *local_104 + (int)uVar5;
  fVar1 = *(float *)(param_1 + 0x14);
  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x18);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x18) - fVar1;
  iVar3 = FUN_00436610();
  if (iVar3 != 0) {
    FUN_004702e0(param_1);
  }
  FUN_00424310(&local_10c,0);
  local_104 = (int *)&DAT_004e4efc;
  FUN_00424400(&local_10c);
  FUN_00424310(&local_118,0);
  local_110 = (int *)&DAT_004e5188;
  FUN_00424400(&local_118);
  (**(code **)(*piVar2 + 0x38))();
  (**(code **)(*piVar2 + 0x3c))();
  if ((param_1 != *(int *)(DAT_004e516c + 0x161c)) && (param_1 != *(int *)(DAT_004e516c + 0x620))) {
    uVar5 = FUN_00424410((uint *)&local_118);
    *local_110 = *local_110 + (int)uVar5;
    uVar5 = FUN_00424410((uint *)&local_10c);
    *local_104 = *local_104 + (int)uVar5;
    return 0;
  }
  uVar5 = FUN_00424410((uint *)&local_118);
  *local_110 = *local_110 + (int)uVar5;
  uVar5 = FUN_00424410((uint *)&local_10c);
  *local_104 = *local_104 + (int)uVar5;
  iVar3 = FUN_00436610();
  if (iVar3 != 0) {
    FUN_00418590(*(int *)(param_1 + 0x78));
    FUN_00415970(param_1);
  }
  FUN_00424310(&local_10c,0);
  local_104 = (int *)&DAT_004e4efc;
  FUN_00424400(&local_10c);
  FUN_00424310(&local_118,0);
  local_110 = (int *)&DAT_004e5188;
  FUN_00424400(&local_118);
  (**(code **)(*piVar2 + 0x40))();
  uVar5 = FUN_00424410((uint *)&local_118);
  *local_110 = *local_110 + (int)uVar5;
  uVar5 = FUN_00424410((uint *)&local_10c);
  *local_104 = *local_104 + (int)uVar5;
  iVar3 = FUN_004926a0(param_1);
  if ((iVar3 != 0) && (*(int *)(param_1 + 0x88) != iVar3)) {
    *(int *)(param_1 + 0x88) = iVar3;
  }
  return 0;
}


/* 00415c40 size=2041 */

/* repo: runtime/client/src/clientshell.cpp */

undefined4 __thiscall clientshell_415c40(void *this,int param_1)

{
  uint uVar1;
  int iVar2;
  ushort uVar3;
  undefined2 uVar4;
  undefined4 *puVar5;
  void *this_00;
  char *pcVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  int iVar9;
  int *piVar10;
  undefined4 uVar11;
  undefined4 *local_28;
  int local_24;
  undefined4 local_20;
  int local_1c [2];
  undefined2 local_14;
  int *local_10;
  undefined4 local_c;
  undefined1 *local_8;
  undefined4 *local_4;
  
  local_1c[0] = 0;
  local_1c[1] = 0;
  local_14 = 0;
  local_10 = (int *)0x0;
  local_c = 0;
  local_8 = (undefined1 *)0x0;
  local_4 = (undefined4 *)0x0;
  FUN_004165f0((int)this);
  iVar9 = param_1;
  uVar3 = *(ushort *)(param_1 + 0x38);
  uVar1 = uVar3 + 4;
  if ((uVar1 < *(uint *)(param_1 + 0x58)) && (uVar1 <= *(ushort *)(param_1 + 0x34))) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x54) + (uint)uVar3);
    *(ushort *)(param_1 + 0x38) = uVar3 + 4;
  }
  else {
    *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | 2;
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
    }
    iVar2 = param_1;
  }
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(int *)((int)this + 0x14) = iVar2;
  *(int *)((int)this + 0x18) = iVar2;
  uVar11 = *(undefined4 *)(*(int *)((int)this + 0x78) + 0x136c);
  *(undefined4 *)((int)this + 0x24) = 0x3d088889;
  *(undefined4 *)((int)this + 0x20) = uVar11;
  uVar3 = *(ushort *)(iVar9 + 0x38);
  local_1c[0] = 2;
  uVar1 = uVar3 + 2;
  if ((uVar1 < *(uint *)(iVar9 + 0x58)) && (uVar1 <= *(ushort *)(iVar9 + 0x34))) {
    uVar4 = *(undefined2 *)(*(int *)(iVar9 + 0x54) + (uint)uVar3);
    *(ushort *)(iVar9 + 0x38) = uVar3 + 2;
    param_1 = CONCAT22((*(uint16_t*)((char*)&param_1+2)),uVar4);
  }
  else {
    *(uint *)(iVar9 + 0x40) = *(uint *)(iVar9 + 0x40) | 2;
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
    }
  }
  local_14 = (undefined2)param_1;
  pcVar6 = FUN_004046f0(*(int *)(*(int *)((int)this + 0x78) + 0x1644),local_1c);
  puVar7 = FUN_004047a0(*(int *)(*(int *)((int)this + 0x78) + 0x1644),local_1c,'\0');
  uVar3 = *(ushort *)(iVar9 + 0x38);
  uVar1 = uVar3 + 4;
  if ((uVar1 < *(uint *)(iVar9 + 0x58)) && (uVar1 <= *(ushort *)(iVar9 + 0x34))) {
    param_1 = *(int *)(*(int *)(iVar9 + 0x54) + (uint)uVar3);
    *(ushort *)(iVar9 + 0x38) = uVar3 + 4;
  }
  else {
    *(uint *)(iVar9 + 0x40) = *(uint *)(iVar9 + 0x40) | 2;
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
    }
  }
  local_24 = FUN_0046b370(iVar9);
  uVar3 = *(ushort *)(iVar9 + 0x38);
  uVar1 = uVar3 + 4;
  if ((uVar1 < *(uint *)(iVar9 + 0x58)) && (uVar1 <= *(ushort *)(iVar9 + 0x34))) {
    local_20 = *(undefined4 *)(*(int *)(iVar9 + 0x54) + (uint)uVar3);
    *(ushort *)(iVar9 + 0x38) = uVar3 + 4;
  }
  else {
    *(uint *)(iVar9 + 0x40) = *(uint *)(iVar9 + 0x40) | 2;
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
    }
  }
  uVar3 = *(ushort *)(iVar9 + 0x38);
  uVar1 = uVar3 + 4;
  if ((uVar1 < *(uint *)(iVar9 + 0x58)) && (uVar1 <= *(ushort *)(iVar9 + 0x34))) {
    local_28 = *(undefined4 **)(*(int *)(iVar9 + 0x54) + (uint)uVar3);
    *(ushort *)(iVar9 + 0x38) = uVar3 + 4;
  }
  else {
    *(uint *)(iVar9 + 0x40) = *(uint *)(iVar9 + 0x40) | 2;
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
    }
  }
  uVar1 = DAT_004e5170;
  if (param_1 == 0) {
    puVar5 = *(undefined4 **)((int)this + 0x70);
    FUN_0046ff00((int)this,*(undefined4 *)((int)this + 0x18));
    this_00 = *(void **)((int)this + 0x78);
    if (*(int *)((int)this + 0x3c) == 0) {
      if (*(int **)((int)this_00 + 0x620) != (int *)0x0) {
        (**(code **)(**(int **)((int)this_00 + 0x620) + 0x24))(pcVar6);
      }
      piVar10 = FUN_004049e0(*(int *)(*(int *)((int)this + 0x78) + 0x1644),local_1c);
      iVar9 = *(int *)((int)this + 0x78);
      if (piVar10 == (int *)0x0) {
        if (*(int **)(iVar9 + 0x620) != (int *)0x0) {
          iVar2 = **(int **)(iVar9 + 0x620);
          puVar8 = FUN_004046f0(*(int *)(iVar9 + 0x1644),local_1c);
          (**(code **)(iVar2 + 0x68))(1,puVar8);
        }
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_CClientShell__DoLoadWorld_004d6858);
        }
        return 0x29;
      }
      (**(code **)(**(int **)(*(int *)(iVar9 + 0x4c4) + 8) + 0x3c))(piVar10,&param_1);
      if (local_4 != puVar7) {
        piVar10 = *(int **)(*(int *)((int)this + 0x78) + 0x620);
        if (piVar10 != (int *)0x0) {
          iVar9 = *piVar10;
          puVar8 = FUN_004046f0(*(int *)(*(int *)((int)this + 0x78) + 0x1644),&local_24);
          (**(code **)(iVar9 + 0x68))(6,puVar8);
        }
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_CClientShell__DoLoadWorld_004d6858);
        }
        return 0x59;
      }
      FUN_00412440(*(void **)((int)this + 0x78),pcVar6,&local_4);
      if (local_4 != local_28) {
        piVar10 = *(int **)(*(int *)((int)this + 0x78) + 0x620);
        if (piVar10 != (int *)0x0) {
          iVar9 = *piVar10;
          puVar8 = FUN_004046f0(*(int *)(*(int *)((int)this + 0x78) + 0x1644),&local_24);
          (**(code **)(iVar9 + 0x68))(7,puVar8);
        }
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_CClientShell__DoLoadWorld_004d6858);
        }
        return 0x5a;
      }
      puVar8 = FUN_004046f0(*(int *)(*(int *)((int)this + 0x78) + 0x1644),&local_24);
      FUN_00420e80(0x6464fa,1,(byte *)s_Entering_world__s_004d680c,puVar8);
      (**(code **)(*piVar10 + 0x14))(0);
      local_4 = *(undefined4 **)((int)this + 0x78);
      local_c = local_4[0x4ba];
      local_8 = &LAB_00415c30;
      local_10 = piVar10;
      iVar9 = FUN_00429060(this_00,(int *)&local_10);
      if (iVar9 != 0) {
        FUN_004267b0(*(int *)((int)this + 0x78),0x2a,(char)pcVar6);
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_CClientShell__DoLoadWorld_004d6858);
        }
        return 0x2a;
      }
      *(int **)((int)this_00 + 0x184) = piVar10;
      LightMapMaker_42c380(this_00,piVar10);
    }
    else {
      if (uVar1 == 0) {
        FUN_004356e0();
        if (DAT_004e4420 < 1) {
          return 1;
        }
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     s_ClientShell__DoLoadWorld_004d683c);
        return 1;
      }
      iVar9 = FUN_0042bb50(this_00,uVar1);
      if (iVar9 == 0) {
        FUN_004356e0();
        if (DAT_004e4420 < 1) {
          return 1;
        }
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     s_ClientShell__DoLoadWorld_004d683c);
        return 1;
      }
    }
    iVar9 = FUN_00416b10((int)this);
    if (iVar9 == 0) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     s_CClientShell__DoLoadWorld_004d6858);
      }
      return 0x2b;
    }
    if (puVar7 != puVar5) {
      FUN_00426e20(*(int *)((int)this + 0x78));
    }
    FUN_00416440(*(int *)((int)this + 0x78),(int)this_00);
    FUN_00426e50(*(int *)((int)this + 0x78));
    iVar9 = FUN_00416730((int)this);
    if (iVar9 == 0) {
      FUN_00416630((int)this);
      FUN_004356e0();
      if (DAT_004e4420 < 1) {
        return 1;
      }
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientShell__DoLoadWorld_004d6858
                  );
      return 1;
    }
    iVar9 = 0x410;
    do {
      FUN_004165b0((int)this,iVar9 + *(int *)((int)this + 0x78));
      iVar9 = iVar9 + 0x10;
    } while (iVar9 < 0x4c0);
    *(undefined4 **)((int)this + 0x70) = puVar7;
    FUN_00410ae0(*(int *)((int)this + 0x78));
    *(undefined4 *)((int)this + 0x7c) = 1;
    return 0;
  }
  if (param_1 == 1) {
    piVar10 = *(int **)(*(int *)((int)this + 0x78) + 0x620);
    if (piVar10 == (int *)0x0) goto LAB_00415f77;
    iVar9 = *piVar10;
    puVar8 = FUN_004046f0(*(int *)(*(int *)((int)this + 0x78) + 0x1644),local_1c);
    uVar11 = 8;
  }
  else {
    if (param_1 != 0x51) goto LAB_00415f77;
    piVar10 = *(int **)(*(int *)((int)this + 0x78) + 0x620);
    if (piVar10 == (int *)0x0) goto LAB_00415f77;
    iVar9 = *piVar10;
    puVar8 = FUN_004046f0(*(int *)(*(int *)((int)this + 0x78) + 0x1644),local_1c);
    uVar11 = 0x10000;
  }
  (**(code **)(iVar9 + 0x68))(uVar11,puVar8);
LAB_00415f77:
  FUN_004356e0();
  if (DAT_004e4420 < 1) {
    return 1;
  }
  FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientShell__DoLoadWorld_004d6858);
  return 1;
}


/* 00416480 size=301 */

/* repo: runtime/client/src/clientshell.cpp */

void __cdecl clientshell_416480(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  uint local_14;
  int local_10;
  int local_c;
  char *local_8;
  undefined2 local_4;
  
  iVar1 = param_2;
  local_4 = 0;
  local_14 = 0;
  if (*(int *)(param_2 + 0x7c) != 0) {
    local_10 = 0;
    do {
      iVar5 = local_10 + *(int *)(iVar1 + 0x78);
      local_c = 0;
      local_8 = *(char **)(*(int *)(iVar1 + 0xbc) + (uint)*(ushort *)(iVar5 + 0x36) * 4);
      if ((*(uint *)(iVar5 + 0x30) & 0x4000) == 0) {
        uVar4 = FUN_00426ae0(param_1,&local_c);
        *(uint *)(iVar5 + 0x2c) = uVar4;
        if ((uVar4 == 0) && (0 < DAT_004e4420)) {
          FUN_00436670((byte *)s_Unable_to_find_world_texture__s_004d68c4,local_8);
        }
        if (*(int *)(iVar5 + 0x2c) == 0) {
          local_c = 1;
          local_8 = s_textures_default_texture_dtx_004d68a4;
          uVar4 = FUN_00426ae0(param_1,&local_c);
          *(uint *)(iVar5 + 0x2c) = uVar4;
        }
      }
      else {
        iVar2 = setupobject_48d2d0(param_1,&local_c,&param_2);
        if (iVar2 == 0) {
          piVar3 = FUN_00430fb0(0x20);
          piVar3[1] = *(int *)(param_1 + 0x1374);
          *(int **)(param_1 + 0x1374) = piVar3;
          *piVar3 = iVar5;
          piVar3[2] = param_2;
          FUN_0049aaf0(piVar3 + 3,param_2);
          if ((undefined4 *)piVar3[5] != (undefined4 *)0x0) {
            *(undefined4 *)(iVar5 + 0x2c) = *(undefined4 *)piVar3[5];
          }
        }
      }
      local_14 = local_14 + 1;
      local_10 = local_10 + 0x40;
    } while (local_14 < *(uint *)(iVar1 + 0x7c));
  }
  return;
}


