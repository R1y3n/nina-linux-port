/* lithtech.exe decompilation - module GameClientShell */
#include "ghidra_types.h"

/* 00410190 size=186 */

/* repo: NOLF/ClientShellDLL/GameClientShell.cpp, runtime/client/src/clientmgr.cpp */

void __cdecl GameClientShell_410190(char *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  pcVar6 = param_1;
  for (iVar2 = 0x85; iVar2 != 0; iVar2 = iVar2 + -1) {
    pcVar6[0] = '\0';
    pcVar6[1] = '\0';
    pcVar6[2] = '\0';
    pcVar6[3] = '\0';
    pcVar6 = pcVar6 + 4;
  }
  *(undefined4 *)(param_1 + 0x204) = DAT_004d82d8;
  *(undefined4 *)(param_1 + 0x208) = DAT_004d82dc;
  *(undefined4 *)(param_1 + 0x20c) = DAT_004d82d4;
  iVar2 = FUN_00420880(0x4e9500,s_renderdll_004d65b4);
  if (iVar2 == 0) {
    uVar3 = 0xffffffff;
    pcVar6 = &DAT_004d65ac;
    do {
      pcVar5 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar5 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar5;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar5 + -uVar3;
    pcVar6 = param_1;
    for (uVar4 = uVar3 >> 2; pcVar6 = pcVar6 + 4, uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar6 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  else {
    _strncpy(param_1 + 4,*(char **)(iVar2 + 0x14),0xff);
  }
  iVar2 = FUN_00420880(0x4e9500,s_carddesc_004d65a0);
  if ((iVar2 != 0) && (*(char **)(iVar2 + 0x14) != (char *)0x0)) {
    _strncpy(param_1 + 0x104,*(char **)(iVar2 + 0x14),0x7f);
  }
  return;
}


/* 0049d7f0 size=1867 */

/* repo: FEAR/ClientShellDLL/GameClientShell.cpp, FEAR/ClientShellDLL/ClientConnectionMgr.cpp,
   runtime/kernel/net/src/sys/win/udpdriver.h */

undefined4 __thiscall GameClientShell_49d7f0(void *this,undefined4 *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  byte bVar3;
  undefined2 extraout_var;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  int *piVar7;
  DWORD DVar8;
  undefined2 extraout_var_00;
  int unaff_EBX;
  int *piVar9;
  byte abStack_e0 [2];
  undefined1 uStack_de;
  undefined1 uStack_dd;
  undefined1 local_dc;
  undefined1 uStack_db;
  undefined1 uStack_da;
  undefined1 uStack_d9;
  undefined1 local_d8;
  undefined1 uStack_d7;
  undefined1 uStack_d6;
  undefined1 uStack_d5;
  int *local_d4;
  int *local_d0;
  undefined4 uStack_cc;
  undefined4 local_c8;
  undefined2 uStack_c4;
  undefined2 uStack_c2;
  undefined1 uStack_c0;
  undefined1 uStack_bf;
  undefined1 uStack_be;
  undefined1 uStack_bd;
  undefined1 uStack_bc;
  undefined1 uStack_bb;
  undefined1 uStack_ba;
  undefined1 uStack_b9;
  undefined4 uStack_b8;
  DWORD DStack_b4;
  int *piStack_b0;
  int *piStack_ac;
  undefined4 uStack_a8;
  undefined1 auStack_a4 [2];
  undefined2 uStack_a2;
  byte bStack_a0;
  undefined1 uStack_9f;
  undefined1 auStack_92 [14];
  undefined1 auStack_84 [132];
  
  uVar1 = *param_1;
  local_dc = (undefined1)uVar1;
  uStack_db = (undefined1)((uint)uVar1 >> 8);
  uStack_da = (undefined1)((uint)uVar1 >> 0x10);
  uStack_d9 = (undefined1)((uint)uVar1 >> 0x18);
  uVar1 = param_1[1];
  local_d8 = (undefined1)uVar1;
  uStack_d7 = (undefined1)((uint)uVar1 >> 8);
  uStack_d6 = (undefined1)((uint)uVar1 >> 0x10);
  uStack_d5 = (undefined1)((uint)uVar1 >> 0x18);
  local_d4 = (int *)param_1[2];
  local_d0 = (int *)param_1[3];
  FUN_0049bc70(this,0);
  iVar4 = FUN_0049c2a0((undefined4 *)(auStack_92 + 2),CONCAT22(extraout_var,DAT_004e988c));
  if (iVar4 == 0) {
    return 1;
  }
  iVar4 = udpdriver_49c2f0();
  (*(uint16_t*)((char*)&local_c8+0)) = (undefined2)iVar4;
  (*(uint16_t*)((char*)&local_c8+2)) = (undefined2)((uint)iVar4 >> 0x10);
  Ordinal_15(CONCAT22(extraout_var_00,*(undefined2 *)((int)param_1 + 2)));
  FUN_004b9f62(auStack_84,(byte *)s__d__d__d__d__d_004ddde0,(uint)*(byte *)(param_1 + 1));
  if (iVar4 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_TCPDriver__JoinSession_004dddc8);
    }
    return 0x50;
  }
  if (DAT_004e9898 != 0) {
    uVar5 = Ordinal_15((*(uint32_t*)((char*)&auStack_92+0)));
    FUN_00436670((byte *)s_Joining_on_port__d_004dddb4,uVar5 & 0xffff);
  }
  puVar6 = FUN_0046b170(&piStack_b0,0x44c,0x44c);
  piVar9 = (int *)*puVar6;
  local_d0 = piVar9;
  if (piVar9 != (int *)0x0) {
    (**(code **)(*piVar9 + 4))();
  }
  if (piStack_b0 != (int *)0x0) {
    (**(code **)(*piStack_b0 + 8))();
  }
  *(undefined1 *)piVar9[0x15] = 0;
  FUN_004183a0(piVar9,3);
  FUN_004183a0(piVar9,0);
  FUN_0046b480(piVar9,(undefined4 *)(*(int *)((int)this + 0x48) + 0xf0),0x10);
  piVar7 = FUN_0046b170(&piStack_ac,0x44c,0x44c);
  piVar7 = (int *)*piVar7;
  if (piVar7 != (int *)0x0) {
    (**(code **)(*piVar7 + 4))();
  }
  if (piStack_ac != (int *)0x0) {
    (**(code **)(*piStack_ac + 8))();
  }
  DStack_b4 = timeGetTime();
  local_c8 = DStack_b4 - 300;
  do {
    DVar8 = timeGetTime();
    if (299 < DVar8 - local_c8) {
      if (DAT_004e9898 != 0) {
        Ordinal_15(CONCAT13(uStack_db,CONCAT12(local_dc,CONCAT11(uStack_dd,uStack_de))));
        FUN_00436670((byte *)s_IP__Sending_conn_request_to__d___004ddd88,
                     CONCAT12(uStack_da,CONCAT11(uStack_db,local_dc)) & 0xff);
      }
      FUN_0049bd70(uStack_cc,piVar9[0x15],(uint)*(ushort *)(piVar9 + 0xd),abStack_e0);
      local_c8 = DVar8;
    }
    iVar4 = udpdriver_49ba30(this,uStack_cc,piVar7[0x15],piVar7[0x16],&uStack_c4);
    if ((iVar4 != -1) && (iVar4 != 0)) {
      if (DAT_004e9898 != 0) {
        FUN_00436670((byte *)s_IP__Got_PacketID__d__len__d__whi_004ddd58,(uint)*(byte *)piVar7[0x15]
                    );
      }
      *(ushort *)(piVar7 + 0xd) = (ushort)iVar4;
      *(undefined2 *)(piVar7 + 0xe) = 1;
      if (*(char *)piVar7[0x15] == '\0') {
        if (((uint)piVar7[0x16] < 3) || ((ushort)iVar4 < 2)) {
          piVar7[0x10] = piVar7[0x10] | 2;
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
          }
          bVar3 = (byte)((uint)unaff_EBX >> 0x18);
        }
        else {
          bVar3 = ((char *)piVar7[0x15])[1];
          *(undefined2 *)(piVar7 + 0xe) = 2;
          unaff_EBX = (uint)bVar3 << 0x18;
        }
        if ((*(byte *)(piVar7 + 0x10) & 2) == 0) {
          if (bVar3 == 5) {
            if (DAT_004e9898 != 0) {
              Ordinal_15(CONCAT13(uStack_db,CONCAT12(local_dc,CONCAT11(uStack_dd,uStack_de))));
              FUN_00436670((byte *)s_IP__Connection_to__d__d__d__d__d_004ddd2c,
                           CONCAT12(uStack_de,(ushort)abStack_e0[0]) & 0xff);
              Ordinal_15(CONCAT22(uStack_c4,(*(uint16_t*)((char*)&local_c8+2))));
              FUN_00436670((byte *)s_recvfrom_addr___d__d__d__d__d_004ddd0c,
                           CONCAT12(uStack_be,CONCAT11(uStack_bf,uStack_c0)) & 0xff);
            }
            if ((*(byte *)(piVar7 + 0x10) & 2) == 0) {
              puVar6 = (undefined4 *)FUN_00430de0(0xe0);
              if (puVar6 != (undefined4 *)0x0) {
                FUN_00464580(puVar6);
                puVar6[0x36] = 0;
                puVar6[0x2f] = CONCAT22(uStack_c2,uStack_c4);
                puVar6[0x30] = CONCAT13(uStack_bd,CONCAT12(uStack_be,CONCAT11(uStack_bf,uStack_c0)))
                ;
                puVar6[0x31] = CONCAT13(uStack_b9,CONCAT12(uStack_ba,CONCAT11(uStack_bb,uStack_bc)))
                ;
                puVar6[0x37] = 1;
                puVar6[0xc] = this;
                puVar6[0x32] = uStack_b8;
                iVar4 = netmgr_465e20(*(void **)((int)this + 0x48),(int)puVar6);
                if (iVar4 != 0) {
                  piVar2 = *(int **)((int)this + 0xa0);
                  piVar9 = puVar6 + 0x33;
                  if (piVar2 == (int *)0x0) {
                    puVar6[0x34] = piVar9;
                    *piVar9 = (int)piVar9;
                    puVar6[0x35] = puVar6;
                    *(int **)((int)this + 0xa0) = piVar9;
                    *(int *)((int)this + 0x9c) = *(int *)((int)this + 0x9c) + 1;
                  }
                  else {
                    *(int **)(*piVar2 + 4) = piVar9;
                    *piVar9 = *piVar2;
                    puVar6[0x34] = piVar2;
                    *piVar2 = (int)piVar9;
                    puVar6[0x35] = puVar6;
                    *(int *)((int)this + 0x9c) = *(int *)((int)this + 0x9c) + 1;
                    if (puVar6[0x34] == *(int *)((int)this + 0xa0)) {
                      *(int **)((int)this + 0xa0) = piVar9;
                    }
                  }
                  *(undefined4 *)((int)this + 0x90) = uStack_cc;
                  if (DAT_004e9898 != 0) {
                    uStack_a8 = 0x10;
                    iVar4 = Ordinal_6(uStack_cc,auStack_a4,&uStack_a8);
                    if (iVar4 == 0) {
                      Ordinal_15(CONCAT13(uStack_9f,CONCAT12(bStack_a0,uStack_a2)));
                      FUN_00436670((byte *)s_getsockname___returned__d__d__d__004ddce4,
                                   (uint)bStack_a0);
                    }
                    else {
                      FUN_00436670((byte *)s_getsockname___returned_error__d_004ddcc4,iVar4);
                    }
                  }
                  if (piVar7 != (int *)0x0) {
                    (**(code **)(*piVar7 + 8))();
                  }
                  if (local_d0 != (int *)0x0) {
                    (**(code **)(*local_d0 + 8))();
                  }
                  return 0;
                }
                if (puVar6[0x36] != 0) {
                  Ordinal_3(puVar6[0x36]);
                }
                FUN_004645f0((int)puVar6);
                FUN_00430df0((undefined *)puVar6);
              }
            }
          }
          else {
            if (bVar3 == 6) {
              if (DAT_004e9898 != 0) {
                Ordinal_15(CONCAT13(uStack_db,CONCAT12(local_dc,CONCAT11(uStack_dd,uStack_de))));
                FUN_00436670((byte *)s_IP__Connection_to__d__d__d__d__d_004ddc98,
                             CONCAT12(uStack_da,CONCAT11(uStack_db,local_dc)) & 0xff);
              }
              Ordinal_3(uStack_cc);
              FUN_004356e0();
              if (1 < DAT_004e4420) {
                FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                             s_TCPDriver__JoinSession_004dddc8);
              }
              if (piVar7 != (int *)0x0) {
                (**(code **)(*piVar7 + 8))();
              }
              if (local_d4 != (int *)0x0) {
                (**(code **)(*local_d4 + 8))();
              }
              return 0x51;
            }
            if (bVar3 == 7) {
              if (DAT_004e9898 != 0) {
                Ordinal_15(CONCAT13(uStack_db,CONCAT12(local_dc,CONCAT11(uStack_dd,uStack_de))));
                FUN_00436670((byte *)s_IP___d__d__d__d__d_not_using_sam_004ddc5c,
                             CONCAT12(uStack_da,CONCAT11(uStack_db,local_dc)) & 0xff);
              }
              Ordinal_3(uStack_cc);
              FUN_004356e0();
              if (1 < DAT_004e4420) {
                FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                             s_TCPDriver__JoinSession_004dddc8);
              }
              if (piVar7 != (int *)0x0) {
                (**(code **)(*piVar7 + 8))();
              }
              if (local_d4 != (int *)0x0) {
                (**(code **)(*local_d4 + 8))();
              }
              return 0x52;
            }
          }
        }
      }
    }
    if (9999 < DVar8 - DStack_b4) {
      FUN_004356e0();
      if (1 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_TCPDriver__JoinSession_004dddc8)
        ;
      }
      if (piVar7 != (int *)0x0) {
        (**(code **)(*piVar7 + 8))();
      }
      if (local_d0 != (int *)0x0) {
        (**(code **)(*local_d0 + 8))();
      }
      return 0x4f;
    }
    piVar9 = local_d0;
  } while( true );
}


