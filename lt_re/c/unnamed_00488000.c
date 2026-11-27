/* lithtech.exe decompilation - unnamed_00488000 */
#include "ghidra_types.h"

/* 004882d0 size=143 */

undefined4 __fastcall FUN_004882d0(int *param_1)

{
  undefined4 unaff_ESI;
  
  if (param_1[0xdc] != 0) {
    FUN_004877f0(param_1);
    FUN_004877b0((int)param_1);
    param_1[0x66] = 0;
    param_1[0x230] = DAT_004d8358;
    (**(code **)(*(int *)param_1[0x28c] + 0x20))();
    FUN_00486360((undefined2 *)param_1);
    FUN_00436670((byte *)s_Running_world_004dcb9c,unaff_ESI);
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CServerMgr__DoRunWorld_004dcbac);
  }
  return 0x15;
}


/* 00488450 size=62 */

void __cdecl FUN_00488450(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  for (iVar1 = *(int *)(param_1 + 0x9fc); iVar1 != param_1 + 0x9f8; iVar1 = *(int *)(iVar1 + 4)) {
    iVar2 = *(int *)(iVar1 + 8);
    iVar3 = *(int *)(iVar2 + 0x3ac);
    if (iVar3 != 0) {
      *(undefined4 *)(*(int *)(iVar3 + 400) + 0x1c) = 0;
      *(undefined4 *)(iVar2 + 0x3ac) = 0;
    }
  }
  return;
}


/* 00488490 size=416 */

void __cdecl FUN_00488490(int *param_1)

{
  int *piVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  int local_28;
  uint local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18 [2];
  undefined1 local_10;
  undefined1 local_f;
  int *local_c;
  undefined1 local_8;
  int local_4;
  
  local_f = (*(uint8_t*)((char*)&param_1+0));
  local_10 = (*(uint8_t*)((char*)&param_1+0));
  local_8 = 0;
  FUN_0048bcf0((int)&local_10);
  piVar1 = param_1;
  local_28 = FUN_00434ff0(param_1[0x2ca]);
  while (local_28 != 0) {
    iVar2 = FUN_00435040(&local_28);
    local_24 = FUN_00434fd0(iVar2);
    if (*(int *)(local_24 + 400) != 0) {
      FUN_0048af00(&local_10,local_18,&local_24);
    }
  }
  piVar6 = (int *)*local_c;
  local_28 = 0;
  if (piVar6 != local_c) {
    do {
      pcVar3 = (char *)FUN_00468720(piVar6[3]);
      FUN_00488630((int)piVar1,pcVar3);
      if ((undefined4 *)piVar6[2] == DAT_004ebfb8) {
        piVar4 = (int *)piVar6[1];
        if (piVar6 == (int *)piVar4[2]) {
          do {
            piVar6 = piVar4;
            piVar4 = (int *)piVar6[1];
          } while (piVar6 == (int *)piVar4[2]);
        }
        if ((int *)piVar6[2] != piVar4) goto LAB_00488555;
      }
      else {
        piVar4 = (int *)FUN_0048cb80((undefined4 *)piVar6[2]);
LAB_00488555:
        piVar6 = piVar4;
      }
    } while (piVar6 != local_c);
  }
  piVar1 = local_c;
  param_1 = (int *)*local_c;
  if (local_4 == 0) {
    if (param_1 != local_c) {
      do {
        puVar5 = (undefined4 *)FUN_0048a740(&param_1,&local_1c);
        FUN_0048b8b0(&local_10,local_18,(int *)*puVar5);
      } while (param_1 != piVar1);
    }
  }
  else {
    FUN_0048bcb0((int *)local_c[1]);
    local_c[1] = (int)DAT_004ebfb8;
    local_4 = 0;
    *local_c = (int)local_c;
    local_c[2] = (int)local_c;
    FUN_004599d0(&local_10,&local_20);
  }
  FUN_00430df0((undefined *)local_c);
  local_c = (int *)0x0;
  local_4 = 0;
  FUN_004b9b4f(&param_1);
  puVar5 = DAT_004ebfb8;
  DAT_004ebfb4 = DAT_004ebfb4 + -1;
  puVar7 = (undefined4 *)0x0;
  if (DAT_004ebfb4 == 0) {
    DAT_004ebfb8 = (undefined4 *)0x0;
    puVar7 = puVar5;
  }
  FUN_004b9beb();
  if (puVar7 != (undefined4 *)0x0) {
    FUN_00430df0((undefined *)puVar7);
  }
  return;
}


/* 00488630 size=137 */

int __cdecl FUN_00488630(int param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = param_2;
  iVar2 = FUN_0047b810(param_1 + 0xc3c,param_2,0,&param_2);
  if (iVar2 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ThreadLoadTexture_004dc23c);
    }
    return 0x16;
  }
  iVar2 = server_extradata_47ad60(param_1,pcVar1,(int)param_2);
  if (iVar2 == 0) {
    FUN_004886c0(param_1,0,0x18,*(undefined2 *)(param_2 + 8),0);
    iVar2 = 0;
  }
  return iVar2;
}


/* 004886c0 size=531 */

void __cdecl
FUN_004886c0(int param_1,undefined1 param_2,undefined1 param_3,undefined2 param_4,int param_5)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined1 uStack_d;
  int local_c;
  int *local_8;
  int local_4;
  
  piVar2 = (int *)0x0;
  local_c = *(int *)(param_1 + 0x9fc);
  if (local_c != param_1 + 0x9f8) {
    do {
      local_4 = *(int *)(local_c + 8);
      if ((param_5 != 0) || ((*(byte *)(local_4 + 0x3c0) & 2) == 0)) {
        puVar1 = FUN_0046b170(&local_8,0x44c,0x44c);
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 8))();
        }
        piVar2 = (int *)*puVar1;
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 4))();
        }
        if (local_8 != (int *)0x0) {
          (**(code **)(*local_8 + 8))();
        }
        if (*(ushort *)(piVar2 + 0xe) + 1 < (uint)*(ushort *)((int)piVar2 + 0x36)) {
          if ((uint)piVar2[0x16] <= *(ushort *)(piVar2 + 0xd) + 1) {
            do {
              uStack_d = 0;
              FUN_00414b10(piVar2 + 0x14,(undefined1 *)piVar2[0x16],&uStack_d,&DAT_004ecc58);
            } while ((uint)piVar2[0x16] <= *(ushort *)(piVar2 + 0xd) + 1);
          }
          *(undefined1 *)(piVar2[0x15] + (uint)*(ushort *)(piVar2 + 0xe)) = param_2;
          *(short *)(piVar2 + 0xe) = (short)piVar2[0xe] + 1;
          *(short *)(piVar2 + 0xd) = (short)piVar2[0xd] + 1;
        }
        else {
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0)
            ;
          }
          piVar2[0x10] = piVar2[0x10] | 4;
        }
        if (*(ushort *)(piVar2 + 0xe) + 2 < (uint)*(ushort *)((int)piVar2 + 0x36)) {
          if ((uint)piVar2[0x16] <= *(ushort *)(piVar2 + 0xd) + 2) {
            do {
              uStack_d = 0;
              FUN_00414b10(piVar2 + 0x14,(undefined1 *)piVar2[0x16],&uStack_d,&DAT_004ecc58);
            } while ((uint)piVar2[0x16] <= *(ushort *)(piVar2 + 0xd) + 2);
          }
          *(undefined2 *)(piVar2[0x15] + (uint)*(ushort *)(piVar2 + 0xe)) = param_4;
          *(short *)(piVar2 + 0xe) = (short)piVar2[0xe] + 2;
          *(short *)(piVar2 + 0xd) = (short)piVar2[0xd] + 2;
        }
        else {
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0)
            ;
          }
          piVar2[0x10] = piVar2[0x10] | 4;
        }
        FUN_00477830(param_1,local_4,param_3,piVar2,0,0x80);
      }
      local_c = *(int *)(local_c + 4);
    } while (local_c != param_1 + 0x9f8);
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))();
    }
  }
  return;
}


/* 004888e0 size=315 */

undefined4 __fastcall FUN_004888e0(int param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int local_4;
  
  for (iVar3 = *(int *)(param_1 + 0x5cc); iVar3 != param_1 + 0x5c8; iVar3 = *(int *)(iVar3 + 4)) {
    iVar2 = *(int *)(*(int *)(iVar3 + 8) + 0x1f8);
    if (iVar2 != 0) {
      puVar1 = (uint *)(iVar2 + 0x20);
      *puVar1 = *puVar1 | 1;
    }
  }
  local_4 = param_1;
  FUN_00416cc0();
  local_4 = FUN_00434ff0(*(int *)(param_1 + 0xb28));
  while (local_4 != 0) {
    iVar3 = FUN_00435040(&local_4);
    iVar3 = FUN_00434fd0(iVar3);
    *(int *)(iVar3 + 0x20c) = *(int *)(iVar3 + 0x20c) + 1;
  }
  local_4 = FUN_00434ff0(*(int *)(param_1 + 0xb28));
  if (local_4 == 0) {
    return 0;
  }
  do {
    piVar4 = (int *)FUN_00435040(&local_4);
    puVar5 = (undefined4 *)FUN_00434fd0((int)piVar4);
    if (puVar5[0x83] != 0) {
      puVar5[0x83] = puVar5[0x83] + -1;
    }
    if ((puVar5[0x83] == 0) && ((*(byte *)(puVar5 + 8) & 1) == 0)) {
      if (1 < DAT_004e4420) {
        uVar6 = FUN_00468720((int)puVar5);
        FUN_00436670((byte *)s_Debug__Server_caching_out_model___004dcbd0,uVar6);
      }
      if (2 < DAT_004e4420) {
        uVar6 = FUN_00468720((int)puVar5);
        FUN_00436670((byte *)s_Removing_model_from_resource_lis_004dbd04,uVar6);
      }
      FUN_00434e60(*(int **)(param_1 + 0xb28),piVar4);
      if (puVar5 != (undefined4 *)0x0) {
        (**(code **)*puVar5)(1);
      }
    }
  } while (local_4 != 0);
  return 0;
}


/* 00488a20 size=686 */

undefined4 __fastcall FUN_00488a20(void *param_1)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint local_390;
  ushort local_38c [32];
  undefined1 local_34c;
  char local_30c [127];
  undefined1 local_28d;
  undefined1 local_28c [512];
  undefined1 local_8c;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_00416a80(local_38c);
  iVar2 = FUN_00402a20((void *)((int)param_1 + 0xa1c),s_VisContainer_004dcbf4);
  if (iVar2 == 0) {
    return 0;
  }
  local_390 = 0;
  if (*(int *)((int)param_1 + 0x334) != 0) {
    do {
      iVar1 = *(int *)(*(int *)((int)param_1 + 0x330) + local_390 * 4);
      uVar6 = *(uint *)(*(int *)(iVar1 + 4) + 0x48);
      if ((uVar6 & 8) == 0) {
        if ((uVar6 & 0x30) != 0) {
          local_38c[1] = 0;
          local_38c[2] = 1;
          local_38c[3] = 0;
          local_38c[6] = 0;
          local_38c[7] = 0;
          local_38c[8] = 0;
          local_38c[9] = 0;
          local_38c[10] = 0;
          local_38c[0xb] = 0;
          local_38c[0xc] = 0;
          local_38c[0xd] = 0;
          local_38c[0xe] = 0;
          local_38c[0xf] = 0;
          local_38c[0x10] = 0;
          local_38c[0x11] = 0x3f80;
          local_38c[0x12] = 0;
          local_38c[0x13] = 0x3f80;
          local_38c[0x14] = 0;
          local_38c[0x15] = 0x3f80;
          local_38c[0x16] = 0;
          local_38c[0x17] = 0;
          local_38c[0x18] = 0;
          local_38c[0x19] = 0;
          local_38c[0x1a] = 0;
          local_38c[0x1b] = 0;
          local_38c[0x1c] = 0;
          local_38c[0x1d] = 0x3f80;
          local_38c[0x1e] = 0;
          local_38c[0x1f] = 0;
          local_34c = 0;
          local_30c[0] = '\0';
          puVar3 = local_28c;
          iVar5 = 4;
          do {
            *puVar3 = 0;
            puVar3 = puVar3 + 0x80;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          local_8c = 0;
          local_c = 0;
          local_8 = 0;
          local_4 = 1;
          local_38c[0] = 2;
          local_38c[4] = 0x3000;
          local_38c[5] = 0;
          _strncpy(local_30c,(char *)(*(int *)(iVar1 + 0xc) + 4),0x7f);
          local_28d = 0;
          piVar4 = FUN_004869d0(param_1,iVar2,local_38c);
          if (piVar4 == (int *)0x0) {
            return 0;
          }
        }
      }
      else {
        uVar6 = 0;
        if (*(int *)(*(int *)(iVar1 + 4) + 0x140) != 0) {
          do {
            local_38c[1] = 0;
            local_38c[2] = 1;
            local_38c[3] = 0;
            local_38c[6] = 0;
            local_38c[7] = 0;
            local_38c[8] = 0;
            local_38c[9] = 0;
            local_38c[10] = 0;
            local_38c[0xb] = 0;
            local_38c[0xc] = 0;
            local_38c[0xd] = 0;
            local_38c[0xe] = 0;
            local_38c[0xf] = 0;
            local_38c[0x10] = 0;
            local_38c[0x11] = 0x3f80;
            local_38c[0x12] = 0;
            local_38c[0x13] = 0x3f80;
            local_38c[0x14] = 0;
            local_38c[0x15] = 0x3f80;
            local_38c[0x16] = 0;
            local_38c[0x17] = 0;
            local_38c[0x18] = 0;
            local_38c[0x19] = 0;
            local_38c[0x1a] = 0;
            local_38c[0x1b] = 0;
            local_38c[0x1c] = 0;
            local_38c[0x1d] = 0x3f80;
            local_38c[0x1e] = 0;
            local_38c[0x1f] = 0;
            local_34c = 0;
            local_30c[0] = '\0';
            puVar3 = local_28c;
            iVar5 = 4;
            do {
              *puVar3 = 0;
              puVar3 = puVar3 + 0x80;
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
            local_8c = 0;
            local_c = 0;
            local_8 = 0;
            local_4 = 1;
            local_38c[0] = 2;
            local_38c[4] = 0x3000;
            local_38c[5] = 0;
            iVar5 = FUN_00428d70((char *)(*(int *)(iVar1 + 4) + 4),uVar6,local_30c,0x80);
            if (iVar5 == 0) {
              return 0;
            }
            piVar4 = FUN_004869d0(param_1,iVar2,local_38c);
            if (piVar4 == (int *)0x0) {
              return 0;
            }
            uVar6 = uVar6 + 1;
          } while (uVar6 < *(uint *)(*(int *)(iVar1 + 4) + 0x140));
        }
      }
      local_390 = local_390 + 1;
    } while (local_390 < *(uint *)((int)param_1 + 0x334));
  }
  return 1;
}


/* 00488cd0 size=89 */

void __thiscall FUN_00488cd0(void *this,int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < param_3) {
    do {
      if (*(char *)(*(int *)(param_1 + 0x3a8) * 0xff + (uint)*(byte *)(iVar1 + param_2) + 0x1a8 +
                   param_1) == '\0') {
        (**(code **)(**(int **)((int)this + 0xa30) + 0x38))
                  (param_1,(uint)*(byte *)(iVar1 + param_2));
      }
      else {
        (**(code **)(**(int **)((int)this + 0xa30) + 0x34))();
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_3);
  }
  return;
}


/* 004891f0 size=279 */

undefined4 __thiscall FUN_004891f0(void *this,int param_1)

{
  char *pcVar1;
  
  if (param_1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CServerMgr__KillSoundLoop_004dcc70
                  );
    }
    return 0x3c;
  }
  if (((byte)*(undefined4 *)(param_1 + 0x34) & 0x14) != 0x14) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CServerMgr__KillSoundLoop_004dcc70
                  );
    }
    return 1;
  }
  pcVar1 = (char *)(*(int *)((int)this + 0xb0c) + *(int *)(*(int *)(param_1 + 0xc) + 8) * 8);
  if ((*pcVar1 == '\x02') && (*(int *)(pcVar1 + 4) != 0)) {
    if (*(short *)(param_1 + 0x2c) == 0) {
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)((int)this + 0xb20);
      *(int *)((int)this + 0xb20) = param_1;
    }
    *(byte *)(param_1 + 0x2c) = *(byte *)(param_1 + 0x2c) | 0x20;
    *(undefined4 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x10) = 1;
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetSoundTrackChangeFlags_004dcc54);
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x10) = 1;
  return 0;
}


/* 00489310 size=264 */

undefined4 __thiscall FUN_00489310(void *this,int param_1,undefined4 param_2)

{
  char *pcVar1;
  
  if (param_1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CServerMgr__KillSoundFade_004dcc8c
                  );
    }
    return 0x3c;
  }
  if ((*(byte *)(param_1 + 0x34) & 0x10) == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CServerMgr__KillSoundFade_004dcc8c
                  );
    }
    return 1;
  }
  pcVar1 = (char *)(*(int *)((int)this + 0xb0c) + *(int *)(*(int *)(param_1 + 0xc) + 8) * 8);
  if ((*pcVar1 == '\x02') && (*(int *)(pcVar1 + 4) != 0)) {
    if (*(short *)(param_1 + 0x2c) == 0) {
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)((int)this + 0xb20);
      *(int *)((int)this + 0xb20) = param_1;
    }
    *(byte *)(param_1 + 0x2c) = *(byte *)(param_1 + 0x2c) | 0x20;
  }
  else {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetSoundTrackChangeFlags_004dcc54)
      ;
    }
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x10) = 1;
  *(undefined4 *)(param_1 + 0x5c) = param_2;
  return 0;
}


/* 00489420 size=36 */

int __thiscall FUN_00489420(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)((int)this + 0x4c);
  while( true ) {
    if (iVar1 == (int)this + 0x48) {
      return 0;
    }
    if (*(int *)(*(int *)(iVar1 + 8) + 0xc) == param_1) break;
    iVar1 = *(int *)(iVar1 + 4);
  }
  return *(int *)(iVar1 + 8);
}


/* 00489450 size=200 */

int * __thiscall FUN_00489450(void *this,int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  char *pcVar3;
  int iVar4;
  int *this_00;
  
  piVar2 = (int *)FUN_00489420(this,(int)param_1);
  if (piVar2 != (int *)0x0) {
    return piVar2;
  }
  pcVar3 = FUN_0047b9b0((int)this + 0xc3c,param_1);
  if (param_1 == (int *)0x0) {
    return (int *)0x0;
  }
  piVar2 = (int *)FUN_0047b5e0((int)this + 0xc3c,pcVar3);
  if (piVar2 == (int *)0x0) {
    return (int *)0x0;
  }
  this_00 = *(int **)((int)this + 0x24);
  if (this_00 == (int *)0x0) {
    FUN_004b7c60((int)this + 0xc,*(int *)((int)this + 0x14));
    this_00 = *(int **)((int)this + 0x24);
    if (this_00 == (int *)0x0) goto LAB_004894b5;
  }
  *(int *)((int)this + 0x24) = *this_00;
LAB_004894b5:
  iVar4 = FUN_00493cd0(this_00,(int)param_1,piVar2,param_1[1]);
  (**(code **)(*piVar2 + 4))();
  if (iVar4 != 0) {
    this_00[2] = (int)this_00;
    *this_00 = (int)this + 0x48;
    puVar1 = *(undefined4 **)((int)this + 0x4c);
    this_00[1] = (int)puVar1;
    *puVar1 = this_00;
    *(int **)(*this_00 + 4) = this_00;
    *(int *)((int)this + 0x44) = *(int *)((int)this + 0x44) + 1;
    return this_00;
  }
  if ((this_00 != (int *)0x0) && ((int)this + 0xc != 0)) {
    *this_00 = *(int *)((int)this + 0x24);
    *(int **)((int)this + 0x24) = this_00;
  }
  return (int *)0x0;
}


/* 00489520 size=310 */

void __cdecl FUN_00489520(byte *param_1,undefined4 param_2)

{
  int *this;
  undefined4 *puVar1;
  undefined1 uStack_1f9;
  int *local_1f8;
  char local_1f4 [500];
  
  if (DAT_004ebfa4 != 0) {
    FUN_004baabf(local_1f4,499,param_1,&param_2);
    puVar1 = FUN_0046b170(&local_1f8,0x44c,0x44c);
    this = (int *)*puVar1;
    if (this != (int *)0x0) {
      (**(code **)(*this + 4))();
    }
    if (local_1f8 != (int *)0x0) {
      (**(code **)(*local_1f8 + 8))();
    }
    if (*(ushort *)(this + 0xe) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
      if ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 1) {
        do {
          uStack_1f9 = 0;
          FUN_00414b10(this + 0x14,(undefined1 *)this[0x16],&uStack_1f9,&DAT_004ecc58);
        } while ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 1);
      }
      *(undefined1 *)(this[0x15] + (uint)*(ushort *)(this + 0xe)) = 0;
      *(short *)(this + 0xe) = (short)this[0xe] + 1;
      *(short *)(this + 0xd) = (short)this[0xd] + 1;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      this[0x10] = this[0x10] | 4;
    }
    FUN_0046b440(this,local_1f4);
    FUN_004777e0(DAT_004ebfa4,0xd,this,0x80);
    if (this != (int *)0x0) {
      (**(code **)(*this + 8))();
    }
  }
  return;
}


/* 00489660 size=531 */

/* WARNING: Removing unreachable block (ram,0x00489821) */

undefined4 __cdecl FUN_00489660(int param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int *piVar6;
  uint local_8;
  
  if (0xffe < *(int *)(param_1 + 0xacc) + 1U) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_CreateNewID_004dcca8);
    }
    return 1;
  }
  *param_2 = 0;
  if ((DAT_004e514c != (int *)0x0) ||
     (FUN_004b7c60(0x4e5134,DAT_004e513c), piVar6 = DAT_004e514c, DAT_004e514c != (int *)0x0)) {
    piVar6 = DAT_004e514c;
    DAT_004e514c = (int *)*DAT_004e514c;
  }
  piVar6[2] = *(int *)(param_1 + 0xacc);
  *(int *)(param_1 + 0xacc) = *(int *)(param_1 + 0xacc) + 1;
  *piVar6 = param_1 + 0xad4;
  puVar5 = *(undefined4 **)(param_1 + 0xad8);
  local_8 = local_8 & 0xffffff00;
  piVar6[1] = (int)puVar5;
  *puVar5 = piVar6;
  *(int **)(*piVar6 + 4) = piVar6;
  uVar2 = *(uint *)(param_1 + 0xb14);
  if (*(int *)(param_1 + 0xb18) == 0) {
    iVar3 = FUN_00417590(&DAT_004ecc58,0,*(int *)(param_1 + 0xb1c) + 1 + uVar2);
    if (iVar3 == 0) goto LAB_00489863;
    uVar4 = 0;
    if (uVar2 != 0) {
      do {
        iVar1 = uVar4 * 8;
        puVar5 = (undefined4 *)(iVar1 + *(int *)(param_1 + 0xb10));
        uVar4 = uVar4 + 1;
        *(undefined4 *)(iVar1 + iVar3) = *puVar5;
        *(undefined4 *)(iVar1 + 4 + iVar3) = puVar5[1];
      } while (uVar4 < uVar2);
    }
    if (uVar2 < *(uint *)(param_1 + 0xb14)) {
      uVar4 = uVar2;
      puVar5 = (undefined4 *)(iVar3 + 8 + uVar2 * 8);
      do {
        iVar1 = *(int *)(param_1 + 0xb10);
        uVar4 = uVar4 + 1;
        *puVar5 = *(undefined4 *)(iVar1 + -8 + uVar4 * 8);
        puVar5[1] = *(undefined4 *)(iVar1 + -4 + uVar4 * 8);
        puVar5 = puVar5 + 2;
      } while (uVar4 < *(uint *)(param_1 + 0xb14));
    }
    *(uint *)(iVar3 + uVar2 * 8) = local_8;
    *(undefined4 *)(iVar3 + 4 + uVar2 * 8) = 0;
    iVar1 = *(int *)(param_1 + 0xb10);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(DAT_004ecc58 + 8))(iVar1);
      }
      *(undefined4 *)(param_1 + 0xb10) = 0;
      *(undefined4 *)(param_1 + 0xb18) = 0;
    }
    *(int *)(param_1 + 0xb10) = iVar3;
    *(undefined4 *)(param_1 + 0xb18) = *(undefined4 *)(param_1 + 0xb1c);
  }
  else {
    iVar3 = *(int *)(param_1 + 0xb10);
    *(int *)(param_1 + 0xb18) = *(int *)(param_1 + 0xb18) + -1;
    *(uint *)(iVar3 + uVar2 * 8) = local_8;
    *(undefined4 *)(iVar3 + 4 + uVar2 * 8) = 0;
  }
  *(int *)(param_1 + 0xb14) = *(int *)(param_1 + 0xb14) + 1;
LAB_00489863:
  *param_2 = piVar6;
  return 0;
}


/* 00489880 size=41 */

void __cdecl FUN_00489880(int param_1,uint param_2,char param_3)

{
  dsys_interface_4356f0((LPSTR)(param_1 + 0x68),300,param_2,&param_3);
  *(uint *)(param_1 + 100) = param_2;
  return;
}


/* 004898b0 size=138 */

undefined4 __cdecl FUN_004898b0(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_1 + 0xaf4);
  if (iVar1 != param_1 + 0xaf0) {
    do {
      uVar2 = (uint)*(ushort *)(*(int *)(iVar1 + 8) + 0xb8);
      if ((*(char *)(*(int *)(param_1 + 0xb10) + uVar2 * 8) != '\x01') ||
         (*(int *)(*(int *)(param_1 + 0xb10) + uVar2 * 8 + 4) == 0)) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_sm_CheckObjectIntegrity_004dccb8);
        }
        return 1;
      }
      iVar1 = *(int *)(iVar1 + 4);
    } while (iVar1 != param_1 + 0xaf0);
  }
  return 0;
}


/* 00489940 size=30 */

void __fastcall FUN_00489940(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x4c);
  while (iVar2 != param_1 + 0x48) {
    iVar1 = *(int *)(iVar2 + 4);
    *(undefined4 *)(*(int *)(iVar2 + 8) + 0x18) = 0;
    iVar2 = iVar1;
  }
  return;
}


/* 00489960 size=76 */

void __cdecl FUN_00489960(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  FUN_00489ac0(param_1);
  iVar1 = *(int *)(param_1 + 0x4c);
  while (iVar1 != param_1 + 0x48) {
    iVar2 = *(int *)(iVar1 + 4);
    puVar3 = *(undefined4 **)(iVar1 + 8);
    iVar1 = iVar2;
    if ((puVar3 != (undefined4 *)0x0) && (param_1 != -0xc)) {
      *puVar3 = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 **)(param_1 + 0x24) = puVar3;
    }
  }
  iVar1 = param_1 + 0x48;
  *(int *)(param_1 + 0x4c) = iVar1;
  *(int *)iVar1 = iVar1;
  *(undefined4 *)(param_1 + 0x44) = 0;
  return;
}


/* 004899b0 size=93 */

void __cdecl FUN_004899b0(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)(param_1 + 0x4c);
  while (iVar1 != param_1 + 0x48) {
    piVar2 = *(int **)(iVar1 + 8);
    iVar1 = *(int *)(iVar1 + 4);
    if (piVar2[6] == 0) {
      *(int *)(*piVar2 + 4) = piVar2[1];
      *(int *)piVar2[1] = *piVar2;
      piVar2[1] = (int)piVar2;
      *piVar2 = (int)piVar2;
      *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + -1;
      FUN_00493d60((int)piVar2);
      if ((piVar2 != (int *)0x0) && (param_1 != -0xc)) {
        *piVar2 = *(int *)(param_1 + 0x24);
        *(int **)(param_1 + 0x24) = piVar2;
      }
    }
  }
  return;
}


/* 00489ac0 size=102 */

void __cdecl FUN_00489ac0(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x5c);
  if (iVar2 != param_1 + 0x58) {
    do {
      puVar1 = *(undefined4 **)(iVar2 + 8);
      iVar2 = *(int *)(iVar2 + 4);
      if ((int *)puVar1[3] != (int *)0x0) {
        FUN_00485490(DAT_004ebfa4,(int *)puVar1[3]);
      }
      puVar1[6] = 0;
      puVar1[3] = 0;
      if ((puVar1 != (undefined4 *)0x0) && (param_1 != -0x28)) {
        *puVar1 = *(undefined4 *)(param_1 + 0x40);
        *(undefined4 **)(param_1 + 0x40) = puVar1;
      }
    } while (iVar2 != param_1 + 0x58);
  }
  iVar2 = param_1 + 0x58;
  *(int *)(param_1 + 0x5c) = iVar2;
  *(int *)iVar2 = iVar2;
  *(undefined4 *)(param_1 + 0x54) = 0;
  return;
}


/* 00489b30 size=112 */

void __cdecl FUN_00489b30(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0xaf4);
  while (iVar1 != param_1 + 0xaf0) {
    piVar2 = *(int **)(iVar1 + 8);
    iVar1 = *(int *)(iVar1 + 4);
    iVar3 = piVar2[100];
    if (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 0x18) = *(undefined4 *)(iVar3 + 0x14);
      if ((piVar2[0x49] & 0x20U) != 0) {
        FUN_0047a260(param_1,(int)piVar2,piVar2[0x49] & 0x18);
      }
      if ((DAT_004e9930 != 0) && ((int *)piVar2[0x19] == piVar2 + 0x18)) {
        FUN_004a3df0((void *)(param_1 + 0x210),piVar2);
      }
    }
  }
  return;
}


/* 00489ba0 size=82 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00489ba0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 400);
  if (*(float *)(iVar1 + 0x14) <= _DAT_004cb524) {
    *(undefined4 *)(iVar1 + 0x18) = *(undefined4 *)(iVar1 + 0x14);
  }
  else {
    *(float *)(iVar1 + 0x18) = *(float *)(DAT_004ebfa4 + 0x8bc) + *(float *)(iVar1 + 0x14);
  }
  if ((*(uint *)(param_1 + 0x124) & 0x20) != 0) {
    FUN_0047a260(DAT_004ebfa4,param_1,*(uint *)(param_1 + 0x124) & 0x18);
  }
  return;
}


/* 00489c00 size=170 */

void __cdecl FUN_00489c00(int param_1,int param_2)

{
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 *local_34;
  undefined4 local_30;
  undefined4 local_2c;
  code *local_28;
  undefined1 *local_24;
  undefined4 local_20;
  
  local_30 = 0;
  local_28 = FUN_004a82f0;
  local_48 = 0;
  local_24 = &LAB_004687d0;
  local_20 = 0;
  if ((DAT_004e9930 != 0) && (*(int *)(param_1 + 0x370) != 0)) {
    local_2c = 0;
    local_38 = 0x461c4000;
    local_44 = *(undefined4 *)(param_2 + 0x194);
    local_34 = &LAB_00489cb0;
    local_40 = *(undefined4 *)(param_2 + 0x198);
    local_3c = *(undefined4 *)(param_2 + 0x19c);
    (**(code **)(*(int *)(param_1 + 0x210) + 0x14))(&local_48);
  }
  return;
}


/* 00489cd0 size=396 */

undefined4 __cdecl FUN_00489cd0(int *param_1,byte *param_2,uint param_3)

{
  int iVar1;
  undefined4 *puVar2;
  short sVar3;
  uint uVar4;
  int *this;
  undefined2 local_8 [2];
  undefined2 local_4 [2];
  
  this = (int *)0x0;
  iVar1 = FUN_00428ca0((int)(param_1 + 0x69),param_2,(uint *)local_8,(uint *)local_4);
  if (iVar1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTServer__SetPortalFlags_004dccf0
                  );
    }
    return 0x3d;
  }
  uVar4 = param_3 & 1;
  sVar3 = (short)uVar4;
  if (sVar3 != *(short *)(iVar1 + 6)) {
    puVar2 = FUN_0046b170(&param_1,0x44c,0x44c);
    this = (int *)*puVar2;
    if (this != (int *)0x0) {
      (**(code **)(*this + 4))();
    }
    if (param_1 != (int *)0x0) {
      (**(code **)(*param_1 + 8))();
    }
    FUN_004385b0(this,local_8[0]);
    FUN_004385b0(this,local_4[0]);
    if (*(ushort *)(this + 0xe) + 1 < (uint)*(ushort *)((int)this + 0x36)) {
      if ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 1) {
        do {
          param_2 = (byte *)((uint)param_2 & 0xffffff00);
          FUN_00414b10(this + 0x14,(undefined1 *)this[0x16],(undefined1 *)&param_2,&DAT_004ecc58);
        } while ((uint)this[0x16] <= *(ushort *)(this + 0xd) + 1);
      }
      *(char *)(this[0x15] + (uint)*(ushort *)(this + 0xe)) = (char)uVar4;
      *(short *)(this + 0xe) = (short)this[0xe] + 1;
      *(short *)(this + 0xd) = (short)this[0xd] + 1;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      this[0x10] = this[0x10] | 4;
    }
    FUN_00477a90(DAT_004ebfa4,0x13,this);
  }
  *(short *)(iVar1 + 6) = sVar3;
  if (this != (int *)0x0) {
    (**(code **)(*this + 8))();
  }
  return 0;
}


/* 00489e60 size=263 */

undefined4 __cdecl
FUN_00489e60(int param_1,uint param_2,int *param_3,undefined4 param_4,undefined4 *param_5,
            uint param_6)

{
  int iVar1;
  int local_5c;
  int *local_58;
  undefined4 local_54;
  undefined1 local_50;
  uint local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  code *local_34;
  code *local_30;
  undefined1 *local_2c;
  code *local_28;
  undefined1 *local_24;
  undefined4 local_20;
  
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = FUN_004a82f0;
  local_30 = (code *)0x0;
  local_2c = (undefined1 *)0x0;
  local_28 = FUN_004a82f0;
  local_48 = 0;
  local_24 = &LAB_004687d0;
  local_20 = 0;
  if (*(int *)(param_1 + 0x9f4) != 0) {
    if ((*(int *)(param_1 + 0x9f4) == 1) &&
       (iVar1 = *(int *)(*(int *)(param_1 + 0x9fc) + 8), (*(byte *)(iVar1 + 0x3c0) & 2) != 0)) {
      FUN_004778c0(param_1,iVar1,param_2,param_3,param_6);
      return 0;
    }
    local_58 = param_3;
    local_54 = param_4;
    local_50 = (undefined1)param_2;
    local_4c = param_6;
    local_5c = param_1;
    local_44 = *param_5;
    local_38 = 0x461c4000;
    local_34 = (code *)&LAB_00489fc0;
    local_40 = param_5[1];
    local_30 = FUN_00489f70;
    local_3c = param_5[2];
    local_2c = (undefined1 *)&local_5c;
    (**(code **)(*(int *)(param_1 + 0x210) + 0x14))(&local_48);
  }
  return 0;
}


/* 00489f70 size=68 */

void __cdecl FUN_00489f70(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 4);
  while( true ) {
    if (iVar1 == param_1) {
      return;
    }
    iVar2 = *(int *)(*(int *)(iVar1 + 8) + 400);
    if (iVar2 == 0) break;
    if (*(int *)(iVar2 + 0x1c) != 0) {
      *(int *)(*param_2 + *param_3 * 4) = *(int *)(iVar1 + 8);
      *param_3 = *param_3 + 1;
    }
    iVar1 = *(int *)(iVar1 + 4);
  }
  return;
}


/* 0048a000 size=494 */

undefined4 __cdecl FUN_0048a000(int *param_1,undefined4 param_2,char *param_3)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  
  uVar1 = param_2;
  piVar3 = param_1;
  if (DAT_004d8290 == 0) {
switchD_0048a05f_default:
    return 0;
  }
  if (param_3 == (char *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTServer__CacheFile_004dcd0c);
    }
    return 1;
  }
  switch(param_2) {
  case 0:
    iVar2 = FUN_0047ac00((int)param_1,param_3,(int *)&param_3,(int *)&param_1,1,1);
    if (iVar2 == 0) {
      if ((*(byte *)(piVar3 + 0x68) & 0x10) != 0) {
        *(uint *)(param_3 + 0x20) = *(uint *)(param_3 + 0x20) | 1;
        FUN_00416ca0();
        return 0;
      }
      if (param_1 == (int *)0x0) {
        return 0;
      }
      FUN_0048a200((int)piVar3,0,(short)param_1[2]);
      return 0;
    }
    FUN_004356e0();
    break;
  case 1:
  case 2:
    iVar2 = FUN_0047b810((int)(param_1 + 0x30f),param_3,0,&param_1);
    if (iVar2 != 0) {
      if (param_1 == (int *)0x0) {
        return 0;
      }
      FUN_0048a200((int)piVar3,(short)uVar1,(short)param_1[2]);
      return 0;
    }
    FUN_004356e0();
    break;
  case 3:
    iVar2 = FUN_0047b810((int)(param_1 + 0x30f),param_3,0,&param_1);
    if (iVar2 == 0) {
      FUN_004356e0();
      if (DAT_004e4420 < 1) {
        return 0x3d;
      }
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTServer__CacheFile_004dcd0c);
      return 0x3d;
    }
    if ((*(byte *)(piVar3 + 0x68) & 0x10) == 0) {
      if (param_1 == (int *)0x0) {
        return 0;
      }
      FUN_0048a200((int)piVar3,3,(short)param_1[2]);
      return 0;
    }
    piVar3 = FUN_00489450(piVar3,param_1);
    if (piVar3 == (int *)0x0) {
      return 0;
    }
    piVar3[6] = 1;
    return 0;
  default:
    goto switchD_0048a05f_default;
  }
  if (DAT_004e4420 < 1) {
    return 0x3d;
  }
  FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTServer__CacheFile_004dcd0c);
  return 0x3d;
}


/* 0048a200 size=258 */

void __cdecl FUN_0048a200(int param_1,undefined2 param_2,short param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  short *psVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  uVar1 = 0;
  uVar4 = *(uint *)(param_1 + 0xb30);
  if (uVar4 != 0) {
    psVar3 = (short *)(*(int *)(param_1 + 0xb2c) + 2);
    do {
      if (*psVar3 == param_3) {
        return;
      }
      uVar1 = uVar1 + 1;
      psVar3 = psVar3 + 2;
    } while (uVar1 < uVar4);
  }
  if (uVar4 == *(uint *)(param_1 + 0xb34)) {
    iVar6 = *(uint *)(param_1 + 0xb34) + 0x14;
    puVar2 = FUN_00430f00(iVar6 * 4);
    puVar7 = *(undefined4 **)(param_1 + 0xb2c);
    puVar8 = puVar2;
    for (uVar4 = *(uint *)(param_1 + 0xb34) & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + 1);
      puVar8 = (undefined4 *)((int)puVar8 + 1);
    }
    FUN_00430fe0(*(undefined **)(param_1 + 0xb2c));
    *(undefined4 **)(param_1 + 0xb2c) = puVar2;
    *(int *)(param_1 + 0xb34) = iVar6;
  }
  *(short *)(*(int *)(param_1 + 0xb2c) + 2 + *(int *)(param_1 + 0xb30) * 4) = param_3;
  *(undefined2 *)(*(int *)(param_1 + 0xb2c) + *(int *)(param_1 + 0xb30) * 4) = param_2;
  *(int *)(param_1 + 0xb30) = *(int *)(param_1 + 0xb30) + 1;
  if ((*(byte *)(param_1 + 0x1a0) & 0x10) == 0) {
    for (iVar6 = *(int *)(param_1 + 0x9fc); iVar6 != param_1 + 0x9f8; iVar6 = *(int *)(iVar6 + 4)) {
      FUN_004717e0(param_1,*(int *)(iVar6 + 8),*(int *)(param_1 + 0xb30) - 1);
    }
  }
  return;
}


/* 0048a310 size=96 */

int * __fastcall FUN_0048a310(int *param_1)

{
  int *piVar1;
  int *local_4;
  
  local_4 = param_1;
  piVar1 = FUN_0046b170(&local_4,0x44c,0x44c);
  piVar1 = (int *)*piVar1;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))();
  }
  if (local_4 != (int *)0x0) {
    (**(code **)(*local_4 + 8))();
  }
  piVar1[3] = param_1[0x285];
  (**(code **)(*piVar1 + 4))();
  piVar1[0x10] = piVar1[0x10] | 1;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))();
  }
  return piVar1;
}


/* 0048a370 size=16 */

void __thiscall FUN_0048a370(void *this,int param_1)

{
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)((int)this + 0xa14);
  return;
}


/* 0048a380 size=59 */

void __thiscall FUN_0048a380(void *this,undefined4 param_1)

{
  int iVar1;
  
  *(undefined4 *)((int)this + 0xba8) = param_1;
  for (iVar1 = *(int *)((int)this + 0x9fc); iVar1 != (int)this + 0x9f8; iVar1 = *(int *)(iVar1 + 4))
  {
    *(uint *)(*(int *)(iVar1 + 8) + 0x3c0) = *(uint *)(*(int *)(iVar1 + 8) + 0x3c0) | 0x400;
  }
  return;
}


/* 0048a3c0 size=730 */

/* FUN_0048a3c0: lifted from original x86 -> lt_lifted.c */


/* 0048a6a0 size=31 */

void __fastcall FUN_0048a6a0(undefined4 *param_1)

{
  LONG LVar1;
  
  LVar1 = InterlockedDecrement(param_1 + 1);
  if ((LVar1 < 1) && (param_1 != (undefined4 *)0x0)) {
    (**(code **)*param_1)(1);
  }
  return;
}


/* 0048a6c0 size=123 */

void __fastcall FUN_0048a6c0(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x105c);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar2 + -1));
    }
    else {
      *(char *)(iVar2 + -1) = cVar1 + -1;
    }
  }
  *(undefined4 *)(param_1 + 0x105c) = 0;
  *(undefined4 *)(param_1 + 0x1060) = 0;
  *(undefined4 *)(param_1 + 0x1064) = 0;
  iVar2 = *(int *)(param_1 + 0x104c);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar2 + -1));
    }
    else {
      *(char *)(iVar2 + -1) = cVar1 + -1;
    }
  }
  *(undefined4 *)(param_1 + 0x104c) = 0;
  *(undefined4 *)(param_1 + 0x1050) = 0;
  *(undefined4 *)(param_1 + 0x1054) = 0;
  return;
}


/* 0048a740 size=86 */

int __thiscall FUN_0048a740(void *this,int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar1 = *(int *)this;
  puVar2 = *(undefined4 **)(iVar1 + 8);
  if (puVar2 != DAT_004ebfb8) {
    for (puVar3 = (undefined4 *)*puVar2; puVar3 != DAT_004ebfb8; puVar3 = (undefined4 *)*puVar3) {
      puVar2 = puVar3;
    }
    *(undefined4 **)this = puVar2;
    *param_1 = iVar1;
    return;
  }
  iVar4 = *(int *)(iVar1 + 4);
  if (*(int *)this == *(int *)(iVar4 + 8)) {
    do {
      *(int *)this = iVar4;
      iVar4 = *(int *)(iVar4 + 4);
    } while (*(int *)this == *(int *)(iVar4 + 8));
  }
  if (*(int *)(*(int *)this + 8) != iVar4) {
    *(int *)this = iVar4;
  }
  *param_1 = iVar1;
  return;
}


/* 0048a7a0 size=296 */

void __fastcall FUN_0048a7a0(int param_1)

{
  void *this;
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined *puVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  undefined4 *local_10;
  int local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar2 = *(undefined4 **)(param_1 + 0x14);
  this = (void *)(param_1 + 0x10);
  local_10 = (undefined4 *)*puVar2;
  if (((*(int *)(param_1 + 0x1c) == 0) ||
      (piVar5 = (int *)FUN_004599d0(this,&local_c), local_10 != (undefined4 *)*piVar5)) ||
     (puVar2 != *(undefined4 **)(param_1 + 0x14))) {
    while (local_10 != puVar2) {
      puVar6 = (undefined4 *)FUN_0048a8d0(&local_10,&local_c);
      FUN_0048c2c0(this,&local_4,(int *)*puVar6);
    }
  }
  else {
    FUN_0048c810((int *)(*(undefined4 **)(param_1 + 0x14))[1]);
    *(undefined **)(*(int *)(param_1 + 0x14) + 4) = DAT_004ebfc0;
    *(undefined4 *)(param_1 + 0x1c) = 0;
    *(undefined4 *)*(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x14);
    *(int *)(*(int *)(param_1 + 0x14) + 8) = *(int *)(param_1 + 0x14);
    FUN_004599d0(this,&local_8);
  }
  FUN_00430df0(*(undefined **)(param_1 + 0x14));
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  FUN_004b9b4f(&local_10);
  puVar4 = DAT_004ebfc0;
  DAT_004ebfbc = DAT_004ebfbc + -1;
  puVar7 = (undefined *)0x0;
  if (DAT_004ebfbc == 0) {
    DAT_004ebfc0 = (undefined *)0x0;
    puVar7 = puVar4;
  }
  FUN_004b9beb();
  if (puVar7 != (undefined *)0x0) {
    FUN_00430df0(puVar7);
  }
  iVar3 = *(int *)(param_1 + 4);
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 != '\0') && (cVar1 != -1)) {
      *(char *)(iVar3 + -1) = cVar1 + -1;
      *(undefined4 *)(param_1 + 4) = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined4 *)(param_1 + 0xc) = 0;
      return;
    }
    FUN_00430df0((char *)(iVar3 + -1));
  }
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}


/* 0048a8d0 size=86 */

int __thiscall FUN_0048a8d0(void *this,int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar1 = *(int *)this;
  puVar2 = *(undefined4 **)(iVar1 + 8);
  if (puVar2 != DAT_004ebfc0) {
    for (puVar3 = (undefined4 *)*puVar2; puVar3 != DAT_004ebfc0; puVar3 = (undefined4 *)*puVar3) {
      puVar2 = puVar3;
    }
    *(undefined4 **)this = puVar2;
    *param_1 = iVar1;
    return;
  }
  iVar4 = *(int *)(iVar1 + 4);
  if (*(int *)this == *(int *)(iVar4 + 8)) {
    do {
      *(int *)this = iVar4;
      iVar4 = *(int *)(iVar4 + 4);
    } while (*(int *)this == *(int *)(iVar4 + 8));
  }
  if (*(int *)(*(int *)this + 8) != iVar4) {
    *(int *)this = iVar4;
  }
  *param_1 = iVar1;
  return;
}


/* 0048a930 size=109 */

void __fastcall FUN_0048a930(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x14);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar2 + -1));
    }
    else {
      *(char *)(iVar2 + -1) = cVar1 + -1;
    }
  }
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  iVar2 = *(int *)(param_1 + 4);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 != '\0') && (cVar1 != -1)) {
      *(char *)(iVar2 + -1) = cVar1 + -1;
      *(undefined4 *)(param_1 + 4) = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined4 *)(param_1 + 0xc) = 0;
      return;
    }
    FUN_00430df0((char *)(iVar2 + -1));
  }
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}


/* 0048a9a0 size=245 */

/* FUN_0048a9a0: lifted from original x86 -> lt_lifted.c */


/* 0048aaa0 size=376 */

/* FUN_0048aaa0: lifted from original x86 -> lt_lifted.c */


/* 0048ac20 size=245 */

/* FUN_0048ac20: lifted from original x86 -> lt_lifted.c */


/* 0048ad20 size=231 */

void __fastcall FUN_0048ad20(void *param_1)

{
  int *piVar1;
  int *piVar2;
  int *local_8;
  undefined4 local_4;
  
  piVar1 = *(int **)((int)param_1 + 4);
  local_8 = (int *)*piVar1;
  piVar2 = local_8;
  if (*(int *)((int)param_1 + 0xc) == 0) {
    while (local_8 = piVar2, piVar2 != piVar1) {
      FUN_0048b860((int *)&local_8);
      FUN_0048c2c0(param_1,&local_4,piVar2);
      piVar2 = local_8;
    }
  }
  else {
    piVar2 = (int *)piVar1[1];
    if ((int *)piVar1[1] != DAT_004ebfc0) {
      do {
        FUN_0048c810((int *)piVar2[2]);
        piVar1 = (int *)*piVar2;
        FUN_0048d220(piVar2 + 3,0);
        FUN_00430df0((undefined *)piVar2);
        piVar2 = piVar1;
      } while (piVar1 != DAT_004ebfc0);
    }
    *(int **)(*(int *)((int)param_1 + 4) + 4) = DAT_004ebfc0;
    *(undefined4 *)((int)param_1 + 0xc) = 0;
    *(undefined4 *)*(undefined4 *)((int)param_1 + 4) = *(undefined4 *)((int)param_1 + 4);
    *(int *)(*(int *)((int)param_1 + 4) + 8) = *(int *)((int)param_1 + 4);
  }
  FUN_00430df0(*(undefined **)((int)param_1 + 4));
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)((int)param_1 + 0xc) = 0;
  FUN_004b9b4f(&local_8);
  piVar1 = DAT_004ebfc0;
  DAT_004ebfbc = DAT_004ebfbc + -1;
  piVar2 = (int *)0x0;
  if (DAT_004ebfbc == 0) {
    DAT_004ebfc0 = (int *)0x0;
    piVar2 = piVar1;
  }
  FUN_004b9beb();
  if (piVar2 != (int *)0x0) {
    FUN_00430df0((undefined *)piVar2);
  }
  return;
}


/* 0048ae10 size=234 */

undefined1 * __thiscall FUN_0048ae10(void *this,undefined1 *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  *(undefined1 *)this = *param_1;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  uVar4 = *(uint *)(param_1 + 8);
  uVar5 = uVar4;
  if (DAT_004cc284 < uVar4) {
    uVar5 = DAT_004cc284;
  }
  if (this == param_1) {
    FUN_004599e0(this,uVar5,DAT_004cc284);
    FUN_004599e0(this,0,0);
  }
  else {
    if ((uVar5 != 0) && (uVar5 == uVar4)) {
      puVar2 = *(undefined1 **)(param_1 + 4);
      if (puVar2 == (undefined1 *)0x0) {
        puVar2 = &DAT_004cc108;
      }
      if ((byte)puVar2[-1] < 0xfe) {
        FUN_00414100(this,'\x01');
        puVar2 = *(undefined1 **)(param_1 + 4);
        if (puVar2 == (undefined1 *)0x0) {
          puVar2 = &DAT_004cc108;
        }
        *(undefined1 **)((int)this + 4) = puVar2;
        *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 8);
        *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
        puVar2[-1] = puVar2[-1] + '\x01';
        goto LAB_0048aed0;
      }
    }
    uVar3 = FUN_0042fe50(this,uVar5,'\x01');
    if ((char)uVar3 != '\0') {
      puVar6 = *(undefined4 **)(param_1 + 4);
      if (puVar6 == (undefined4 *)0x0) {
        puVar6 = (undefined4 *)&DAT_004cc108;
      }
      puVar7 = *(undefined4 **)((int)this + 4);
      for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      for (uVar4 = uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
        puVar7 = (undefined4 *)((int)puVar7 + 1);
      }
      FUN_0042fe30(this,uVar5);
    }
  }
LAB_0048aed0:
  uVar1 = *param_2;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined1 *)((int)this + 0x10) = uVar1;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  FUN_0042fc30((undefined1 *)((int)this + 0x10),param_2,0,DAT_004cc284);
  return this;
}


/* 0048af00 size=574 */

void __thiscall FUN_0048af00(void *this,undefined4 *param_1,uint *param_2)

{
  int *piVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  uint *puVar7;
  undefined4 *puVar8;
  uint *puVar9;
  bool bVar10;
  int *local_4;
  
  puVar9 = param_2;
  bVar10 = true;
  piVar1 = *(int **)((int)this + 4);
  piVar5 = piVar1;
  piVar6 = (int *)piVar1[1];
  while (piVar6 != DAT_004ebfb8) {
    bVar10 = *param_2 < (uint)piVar6[3];
    piVar5 = piVar6;
    if (bVar10) {
      piVar6 = (int *)*piVar6;
    }
    else {
      piVar6 = (int *)piVar6[2];
    }
  }
  if (*(char *)((int)this + 8) == '\0') {
    local_4 = piVar5;
    if (bVar10) {
      if (piVar5 == (int *)*piVar1) {
        puVar8 = (undefined4 *)FUN_0048bd90(this,&param_2,(int)piVar6,piVar5,param_2);
        *param_1 = *puVar8;
        *(undefined1 *)(param_1 + 1) = 1;
        return;
      }
      FUN_0048cc20((int *)&local_4);
    }
    if ((uint)local_4[3] < *puVar9) {
      puVar8 = (undefined4 *)FUN_0048bd90(this,&param_2,(int)piVar6,piVar5,puVar9);
      *param_1 = *puVar8;
      *(undefined1 *)(param_1 + 1) = 1;
      return;
    }
    *param_1 = local_4;
    *(undefined1 *)(param_1 + 1) = 0;
    return;
  }
  local_4 = this;
  param_2 = (uint *)FUN_0048cc00(piVar5,0);
  *param_2 = (uint)DAT_004ebfb8;
  param_2[2] = (uint)DAT_004ebfb8;
  FUN_0048ce90(param_2 + 3,puVar9);
  puVar7 = param_2;
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if (((piVar5 == *(int **)((int)this + 4)) || (piVar6 != DAT_004ebfb8)) ||
     (*puVar9 < (uint)piVar5[3])) {
    *piVar5 = (int)param_2;
    piVar1 = *(int **)((int)this + 4);
    if (piVar5 == piVar1) {
      piVar1[1] = (int)param_2;
      *(uint **)(*(int *)((int)this + 4) + 8) = param_2;
    }
    else if (piVar5 == (int *)*piVar1) {
      *piVar1 = (int)param_2;
    }
  }
  else {
    piVar5[2] = (int)param_2;
    if (piVar5 == *(int **)(*(int *)((int)this + 4) + 8)) {
      *(uint **)(*(int *)((int)this + 4) + 8) = param_2;
    }
  }
  puVar9 = param_2;
  if (param_2 != *(uint **)(*(int *)((int)this + 4) + 4)) {
    do {
      puVar2 = (uint *)puVar9[1];
      if (puVar2[4] != 0) break;
      puVar3 = *(uint **)puVar2[1];
      if (puVar2 == puVar3) {
        iVar4 = ((undefined4 *)puVar2[1])[2];
        if (*(int *)(iVar4 + 0x10) == 0) {
          puVar2[4] = 1;
          *(undefined4 *)(iVar4 + 0x10) = 1;
          *(undefined4 *)(*(int *)(puVar9[1] + 4) + 0x10) = 0;
          puVar9 = *(uint **)(puVar9[1] + 4);
        }
        else {
          if (puVar9 == (uint *)puVar2[2]) {
            FUN_0048cb20(this,(int)puVar2);
            puVar9 = puVar2;
          }
          *(undefined4 *)(puVar9[1] + 0x10) = 1;
          *(undefined4 *)(*(int *)(puVar9[1] + 4) + 0x10) = 0;
          FUN_0048cba0(this,*(int **)(puVar9[1] + 4));
        }
      }
      else if (puVar3[4] == 0) {
        puVar2[4] = 1;
        puVar3[4] = 1;
        *(undefined4 *)(*(int *)(puVar9[1] + 4) + 0x10) = 0;
        puVar9 = *(uint **)(puVar9[1] + 4);
      }
      else {
        if (puVar9 == (uint *)*puVar2) {
          FUN_0048cba0(this,(int *)puVar2);
          puVar9 = puVar2;
        }
        *(undefined4 *)(puVar9[1] + 0x10) = 1;
        *(undefined4 *)(*(int *)(puVar9[1] + 4) + 0x10) = 0;
        FUN_0048cb20(this,*(int *)(puVar9[1] + 4));
      }
    } while (puVar9 != *(uint **)(*(int *)((int)this + 4) + 4));
  }
  *(undefined4 *)(*(int *)(*(int *)((int)this + 4) + 4) + 0x10) = 1;
  *param_1 = puVar7;
  *(undefined1 *)(param_1 + 1) = 1;
  return;
}


/* 0048b140 size=1204 */

void __thiscall FUN_0048b140(void *this,undefined4 *param_1,int *param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int *piVar10;
  int *piVar11;
  undefined *puVar12;
  int *local_c;
  int *local_8;
  int *local_4;
  
  piVar4 = param_2;
  FUN_0048ce40((int *)&param_2);
  piVar11 = (int *)*piVar4;
  piVar7 = piVar4 + 2;
  local_c = piVar4;
  piVar10 = piVar7;
  if (piVar11 == DAT_004ebfb0) {
    piVar11 = (int *)*piVar7;
  }
  else {
    piVar2 = (int *)*piVar7;
    if (piVar2 != DAT_004ebfb0) {
      local_c = piVar2;
      for (piVar10 = (int *)*piVar2; piVar10 != DAT_004ebfb0; piVar10 = (int *)*piVar10) {
        local_c = piVar10;
      }
      piVar11 = (int *)local_c[2];
      piVar10 = local_c + 2;
    }
  }
  FUN_004b9b4f(&local_4);
  piVar2 = local_c;
  if (local_c == piVar4) {
    piVar11[1] = local_c[1];
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar4) {
      *(int **)(*(int *)((int)this + 4) + 4) = piVar11;
    }
    else {
      piVar10 = (int *)piVar4[1];
      if ((int *)*piVar10 == piVar4) {
        *piVar10 = (int)piVar11;
      }
      else {
        piVar10[2] = (int)piVar11;
      }
    }
    local_8 = *(int **)((int)this + 4);
    if ((int *)*local_8 == piVar4) {
      if ((int *)*piVar7 == DAT_004ebfb0) {
        *local_8 = piVar4[1];
      }
      else {
        piVar7 = piVar11;
        if ((int *)*piVar11 != DAT_004ebfb0) {
          piVar10 = (int *)*piVar11;
          do {
            piVar7 = piVar10;
            piVar10 = (int *)*piVar7;
          } while ((int *)*piVar7 != DAT_004ebfb0);
        }
        *local_8 = (int)piVar7;
      }
    }
    if (*(int **)(*(int *)((int)this + 4) + 8) == piVar4) {
      if ((int *)*piVar4 == DAT_004ebfb0) {
        piVar7 = (int *)piVar4[1];
      }
      else {
        piVar10 = (int *)piVar11[2];
        piVar7 = piVar11;
        while (piVar4 = piVar10, piVar4 != DAT_004ebfb0) {
          piVar7 = piVar4;
          piVar10 = (int *)piVar4[2];
        }
      }
      *(int **)(*(int *)((int)this + 4) + 8) = piVar7;
    }
  }
  else {
    *(int **)(*piVar4 + 4) = local_c;
    *local_c = *piVar4;
    if (local_c == (int *)*piVar7) {
      piVar11[1] = (int)local_c;
    }
    else {
      piVar11[1] = local_c[1];
      *(int **)local_c[1] = piVar11;
      *piVar10 = *piVar7;
      *(int **)(*piVar7 + 4) = local_c;
    }
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar4) {
      *(int **)(*(int *)((int)this + 4) + 4) = local_c;
    }
    else {
      piVar7 = (int *)piVar4[1];
      if ((int *)*piVar7 == piVar4) {
        *piVar7 = (int)local_c;
      }
      else {
        piVar7[2] = (int)local_c;
      }
    }
    local_c = piVar4;
    piVar2[1] = piVar4[1];
    iVar3 = piVar2[0xb];
    piVar2[0xb] = piVar4[0xb];
    piVar4[0xb] = iVar3;
  }
  if (local_c[0xb] == 1) {
    if (piVar11 != *(int **)(*(int *)((int)this + 4) + 4)) {
      do {
        if (piVar11[0xb] != 1) break;
        piVar7 = *(int **)piVar11[1];
        if (piVar11 == piVar7) {
          piVar7 = (int *)((undefined4 *)piVar11[1])[2];
          if (piVar7[0xb] == 0) {
            piVar7[0xb] = 1;
            *(undefined4 *)(piVar11[1] + 0x2c) = 0;
            iVar3 = piVar11[1];
            piVar7 = *(int **)(iVar3 + 8);
            *(int *)(iVar3 + 8) = *piVar7;
            if ((int *)*piVar7 != DAT_004ebfb0) {
              ((int *)*piVar7)[1] = iVar3;
            }
            piVar7[1] = *(int *)(iVar3 + 4);
            if (iVar3 == *(int *)(*(int *)((int)this + 4) + 4)) {
              *(int **)(*(int *)((int)this + 4) + 4) = piVar7;
            }
            else {
              piVar10 = *(int **)(iVar3 + 4);
              if (iVar3 == *piVar10) {
                *piVar10 = (int)piVar7;
              }
              else {
                piVar10[2] = (int)piVar7;
              }
            }
            *piVar7 = iVar3;
            *(int **)(iVar3 + 4) = piVar7;
            piVar7 = *(int **)(piVar11[1] + 8);
          }
          if ((*(int *)(*piVar7 + 0x2c) != 1) || (*(int *)(piVar7[2] + 0x2c) != 1)) {
            if (*(int *)(piVar7[2] + 0x2c) == 1) {
              *(undefined4 *)(*piVar7 + 0x2c) = 1;
              iVar3 = *piVar7;
              piVar7[0xb] = 0;
              *piVar7 = *(int *)(iVar3 + 8);
              if (*(int **)(iVar3 + 8) != DAT_004ebfb0) {
                (*(int **)(iVar3 + 8))[1] = (int)piVar7;
              }
              *(int *)(iVar3 + 4) = piVar7[1];
              if (piVar7 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int *)(*(int *)((int)this + 4) + 4) = iVar3;
              }
              else {
                piVar10 = (int *)piVar7[1];
                if (piVar7 == (int *)piVar10[2]) {
                  piVar10[2] = iVar3;
                }
                else {
                  *piVar10 = iVar3;
                }
              }
              *(int **)(iVar3 + 8) = piVar7;
              piVar7[1] = iVar3;
              piVar7 = *(int **)(piVar11[1] + 8);
            }
            piVar7[0xb] = *(int *)(piVar11[1] + 0x2c);
            *(undefined4 *)(piVar11[1] + 0x2c) = 1;
            *(undefined4 *)(piVar7[2] + 0x2c) = 1;
            puVar8 = (undefined4 *)piVar11[1];
            puVar9 = (undefined4 *)puVar8[2];
            puVar8[2] = *puVar9;
            if ((int *)*puVar9 != DAT_004ebfb0) {
              ((int *)*puVar9)[1] = (int)puVar8;
            }
            puVar9[1] = puVar8[1];
            if (puVar8 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar9;
              *puVar9 = puVar8;
            }
            else {
              piVar7 = (int *)puVar8[1];
              if (puVar8 == (undefined4 *)*piVar7) {
                *piVar7 = (int)puVar9;
                *puVar9 = puVar8;
              }
              else {
                piVar7[2] = (int)puVar9;
                *puVar9 = puVar8;
              }
            }
            goto LAB_0048b506;
          }
        }
        else {
          if (piVar7[0xb] == 0) {
            piVar7[0xb] = 1;
            *(undefined4 *)(piVar11[1] + 0x2c) = 0;
            piVar7 = (int *)piVar11[1];
            iVar3 = *piVar7;
            *piVar7 = *(int *)(iVar3 + 8);
            if (*(int **)(iVar3 + 8) != DAT_004ebfb0) {
              (*(int **)(iVar3 + 8))[1] = (int)piVar7;
            }
            *(int *)(iVar3 + 4) = piVar7[1];
            if (piVar7 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int *)(*(int *)((int)this + 4) + 4) = iVar3;
            }
            else {
              piVar10 = (int *)piVar7[1];
              if (piVar7 == (int *)piVar10[2]) {
                piVar10[2] = iVar3;
              }
              else {
                *piVar10 = iVar3;
              }
            }
            *(int **)(iVar3 + 8) = piVar7;
            piVar7[1] = iVar3;
            piVar7 = *(int **)piVar11[1];
          }
          if ((*(int *)(piVar7[2] + 0x2c) != 1) || (*(int *)(*piVar7 + 0x2c) != 1)) {
            if (*(int *)(*piVar7 + 0x2c) == 1) {
              *(undefined4 *)(piVar7[2] + 0x2c) = 1;
              piVar10 = (int *)piVar7[2];
              piVar7[0xb] = 0;
              piVar7[2] = *piVar10;
              if ((int *)*piVar10 != DAT_004ebfb0) {
                ((int *)*piVar10)[1] = (int)piVar7;
              }
              piVar10[1] = piVar7[1];
              if (piVar7 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int **)(*(int *)((int)this + 4) + 4) = piVar10;
              }
              else {
                piVar4 = (int *)piVar7[1];
                if (piVar7 == (int *)*piVar4) {
                  *piVar4 = (int)piVar10;
                }
                else {
                  piVar4[2] = (int)piVar10;
                }
              }
              *piVar10 = (int)piVar7;
              piVar7[1] = (int)piVar10;
              piVar7 = *(int **)piVar11[1];
            }
            piVar7[0xb] = *(int *)(piVar11[1] + 0x2c);
            *(undefined4 *)(piVar11[1] + 0x2c) = 1;
            *(undefined4 *)(*piVar7 + 0x2c) = 1;
            puVar8 = (undefined4 *)piVar11[1];
            puVar9 = (undefined4 *)*puVar8;
            *puVar8 = puVar9[2];
            if ((int *)puVar9[2] != DAT_004ebfb0) {
              ((int *)puVar9[2])[1] = (int)puVar8;
            }
            puVar9[1] = puVar8[1];
            if (puVar8 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar9;
            }
            else {
              puVar5 = (undefined4 *)puVar8[1];
              if (puVar8 == (undefined4 *)puVar5[2]) {
                puVar5[2] = puVar9;
              }
              else {
                *puVar5 = puVar9;
              }
            }
            puVar9[2] = puVar8;
LAB_0048b506:
            puVar8[1] = puVar9;
            break;
          }
        }
        piVar7[0xb] = 0;
        piVar11 = (int *)piVar11[1];
      } while (piVar11 != *(int **)(*(int *)((int)this + 4) + 4));
    }
    piVar11[0xb] = 1;
  }
  FUN_004b9beb();
  piVar10 = local_c;
  piVar7 = local_c + 7;
  FUN_004850c0(&local_4,local_c[8]);
  puVar8 = (undefined4 *)FUN_004aa830(piVar10[8]);
  FUN_004850c0(&local_8,*puVar8);
  FUN_0048b7b0(piVar7,&local_c,local_8,local_4);
  FUN_00430df0((undefined *)piVar10[8]);
  piVar10[8] = 0;
  piVar10[10] = 0;
  FUN_004b9b4f(&local_4);
  puVar6 = DAT_004ebfc0;
  DAT_004ebfbc = DAT_004ebfbc + -1;
  puVar12 = (undefined *)0x0;
  if (DAT_004ebfbc == 0) {
    DAT_004ebfc0 = (undefined *)0x0;
    puVar12 = puVar6;
  }
  FUN_004b9beb();
  if (puVar12 != (undefined *)0x0) {
    FUN_00430df0(puVar12);
  }
  iVar3 = piVar10[4];
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar3 + -1));
    }
    else {
      *(char *)(iVar3 + -1) = cVar1 + -1;
    }
  }
  piVar10[4] = 0;
  piVar10[5] = 0;
  piVar10[6] = 0;
  FUN_00430df0((undefined *)piVar10);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
  *param_1 = param_2;
  return;
}


/* 0048b600 size=251 */

void FUN_0048b600(int *param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  int *piVar7;
  int *piVar8;
  undefined1 local_c [4];
  undefined4 local_8;
  undefined4 local_4;
  
  piVar7 = param_1;
  if (param_1 != DAT_004ebfb0) {
    do {
      FUN_0048b600((int *)piVar7[2]);
      piVar2 = (int *)*piVar7;
      FUN_004850c0(&param_1,piVar7[8]);
      piVar8 = param_1;
      puVar5 = (undefined4 *)FUN_004599d0(piVar7 + 7,&local_8);
      FUN_0048b7b0(piVar7 + 7,&local_4,(int *)*puVar5,piVar8);
      FUN_00430df0((undefined *)piVar7[8]);
      piVar7[8] = 0;
      piVar7[10] = 0;
      FUN_004b9b4f(local_c);
      puVar4 = DAT_004ebfc0;
      DAT_004ebfbc = DAT_004ebfbc + -1;
      puVar6 = (undefined *)0x0;
      if (DAT_004ebfbc == 0) {
        DAT_004ebfc0 = (undefined *)0x0;
        puVar6 = puVar4;
      }
      FUN_004b9beb();
      if (puVar6 != (undefined *)0x0) {
        FUN_00430df0(puVar6);
      }
      iVar3 = piVar7[4];
      if (iVar3 != 0) {
        cVar1 = *(char *)(iVar3 + -1);
        if ((cVar1 == '\0') || (cVar1 == -1)) {
          FUN_00430df0((char *)(iVar3 + -1));
        }
        else {
          *(char *)(iVar3 + -1) = cVar1 + -1;
        }
      }
      piVar7[4] = 0;
      piVar7[5] = 0;
      piVar7[6] = 0;
      FUN_00430df0((undefined *)piVar7);
      piVar7 = piVar2;
    } while (piVar2 != DAT_004ebfb0);
  }
  return;
}


/* 0048b700 size=172 */

/* FUN_0048b700: lifted from original x86 -> lt_lifted.c */


/* 0048b7b0 size=175 */

void __thiscall FUN_0048b7b0(void *this,undefined4 *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = param_3;
  piVar3 = param_2;
  if (((*(int *)((int)this + 0xc) == 0) ||
      (piVar1 = *(int **)((int)this + 4), param_2 != (int *)*piVar1)) || (param_3 != piVar1)) {
    while (piVar3 != piVar2) {
      param_2 = piVar3;
      FUN_0048b860((int *)&param_2);
      FUN_0048c2c0(this,&param_3,piVar3);
      piVar3 = param_2;
    }
    *param_1 = piVar3;
    return;
  }
  piVar3 = (int *)piVar1[1];
  if ((int *)piVar1[1] != DAT_004ebfc0) {
    do {
      FUN_0048c810((int *)piVar3[2]);
      piVar2 = (int *)*piVar3;
      FUN_0048a930((int)(piVar3 + 3));
      FUN_00430df0((undefined *)piVar3);
      piVar3 = piVar2;
    } while (piVar2 != DAT_004ebfc0);
  }
  *(int **)(*(int *)((int)this + 4) + 4) = DAT_004ebfc0;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)*(undefined4 *)((int)this + 4) = *(undefined4 *)((int)this + 4);
  *(int *)(*(int *)((int)this + 4) + 8) = *(int *)((int)this + 4);
  *param_1 = **(undefined4 **)((int)this + 4);
  return;
}


/* 0048b860 size=67 */

void __fastcall FUN_0048b860(int *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = *(undefined4 **)(*param_1 + 8);
  if (puVar1 != DAT_004ebfc0) {
    for (puVar2 = (undefined4 *)*puVar1; puVar2 != DAT_004ebfc0; puVar2 = (undefined4 *)*puVar2) {
      puVar1 = puVar2;
    }
    *param_1 = (int)puVar1;
    return;
  }
  iVar3 = *(int *)(*param_1 + 4);
  if (*param_1 == *(int *)(iVar3 + 8)) {
    do {
      *param_1 = iVar3;
      iVar3 = *(int *)(iVar3 + 4);
    } while (*param_1 == *(int *)(iVar3 + 8));
  }
  if (*(int *)(*param_1 + 8) != iVar3) {
    *param_1 = iVar3;
  }
  return;
}


/* 0048b8b0 size=1021 */

void __thiscall FUN_0048b8b0(void *this,undefined4 *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int *piVar8;
  int *piVar9;
  int *local_c;
  undefined1 local_4 [4];
  
  piVar3 = param_2;
  FUN_0048c000((int *)&param_2);
  piVar9 = (int *)*piVar3;
  piVar5 = piVar3 + 2;
  local_c = piVar3;
  piVar8 = piVar5;
  if (piVar9 == DAT_004ebfb8) {
    piVar9 = (int *)*piVar5;
  }
  else {
    piVar1 = (int *)*piVar5;
    if (piVar1 != DAT_004ebfb8) {
      local_c = piVar1;
      for (piVar8 = (int *)*piVar1; piVar8 != DAT_004ebfb8; piVar8 = (int *)*piVar8) {
        local_c = piVar8;
      }
      piVar9 = (int *)local_c[2];
      piVar8 = local_c + 2;
    }
  }
  piVar1 = local_c;
  FUN_004b9b4f(local_4);
  if (local_c == piVar3) {
    piVar9[1] = local_c[1];
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar3) {
      *(int **)(*(int *)((int)this + 4) + 4) = piVar9;
    }
    else {
      piVar8 = (int *)piVar3[1];
      if ((int *)*piVar8 == piVar3) {
        *piVar8 = (int)piVar9;
      }
      else {
        piVar8[2] = (int)piVar9;
      }
    }
    piVar8 = *(int **)((int)this + 4);
    if ((int *)*piVar8 == piVar3) {
      if ((int *)*piVar5 == DAT_004ebfb8) {
        *piVar8 = piVar3[1];
      }
      else {
        piVar5 = piVar9;
        if ((int *)*piVar9 != DAT_004ebfb8) {
          piVar1 = (int *)*piVar9;
          do {
            piVar5 = piVar1;
            piVar1 = (int *)*piVar5;
          } while ((int *)*piVar5 != DAT_004ebfb8);
        }
        *piVar8 = (int)piVar5;
      }
    }
    if (*(int **)(*(int *)((int)this + 4) + 8) == piVar3) {
      if ((int *)*piVar3 == DAT_004ebfb8) {
        piVar5 = (int *)piVar3[1];
      }
      else {
        piVar8 = (int *)piVar9[2];
        piVar5 = piVar9;
        while (piVar3 = piVar8, piVar3 != DAT_004ebfb8) {
          piVar5 = piVar3;
          piVar8 = (int *)piVar3[2];
        }
      }
      *(int **)(*(int *)((int)this + 4) + 8) = piVar5;
    }
  }
  else {
    *(int **)(*piVar3 + 4) = local_c;
    *local_c = *piVar3;
    if (local_c == (int *)*piVar5) {
      piVar9[1] = (int)local_c;
    }
    else {
      piVar9[1] = local_c[1];
      *(int **)local_c[1] = piVar9;
      *piVar8 = *piVar5;
      *(int **)(*piVar5 + 4) = local_c;
    }
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar3) {
      *(int **)(*(int *)((int)this + 4) + 4) = local_c;
    }
    else {
      piVar5 = (int *)piVar3[1];
      if ((int *)*piVar5 == piVar3) {
        *piVar5 = (int)local_c;
      }
      else {
        piVar5[2] = (int)local_c;
      }
    }
    local_c = piVar3;
    piVar1[1] = piVar3[1];
    iVar2 = piVar1[4];
    piVar1[4] = piVar3[4];
    piVar3[4] = iVar2;
  }
  if (local_c[4] == 1) {
    if (piVar9 != *(int **)(*(int *)((int)this + 4) + 4)) {
      do {
        if (piVar9[4] != 1) break;
        piVar5 = *(int **)piVar9[1];
        if (piVar9 == piVar5) {
          piVar5 = (int *)((undefined4 *)piVar9[1])[2];
          if (piVar5[4] == 0) {
            piVar5[4] = 1;
            *(undefined4 *)(piVar9[1] + 0x10) = 0;
            iVar2 = piVar9[1];
            piVar5 = *(int **)(iVar2 + 8);
            *(int *)(iVar2 + 8) = *piVar5;
            if ((int *)*piVar5 != DAT_004ebfb8) {
              ((int *)*piVar5)[1] = iVar2;
            }
            piVar5[1] = *(int *)(iVar2 + 4);
            if (iVar2 == *(int *)(*(int *)((int)this + 4) + 4)) {
              *(int **)(*(int *)((int)this + 4) + 4) = piVar5;
            }
            else {
              piVar8 = *(int **)(iVar2 + 4);
              if (iVar2 == *piVar8) {
                *piVar8 = (int)piVar5;
              }
              else {
                piVar8[2] = (int)piVar5;
              }
            }
            *piVar5 = iVar2;
            *(int **)(iVar2 + 4) = piVar5;
            piVar5 = *(int **)(piVar9[1] + 8);
          }
          if ((*(int *)(*piVar5 + 0x10) != 1) || (*(int *)(piVar5[2] + 0x10) != 1)) {
            if (*(int *)(piVar5[2] + 0x10) == 1) {
              *(undefined4 *)(*piVar5 + 0x10) = 1;
              iVar2 = *piVar5;
              piVar5[4] = 0;
              *piVar5 = *(int *)(iVar2 + 8);
              if (*(int **)(iVar2 + 8) != DAT_004ebfb8) {
                (*(int **)(iVar2 + 8))[1] = (int)piVar5;
              }
              *(int *)(iVar2 + 4) = piVar5[1];
              if (piVar5 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int *)(*(int *)((int)this + 4) + 4) = iVar2;
              }
              else {
                piVar8 = (int *)piVar5[1];
                if (piVar5 == (int *)piVar8[2]) {
                  piVar8[2] = iVar2;
                }
                else {
                  *piVar8 = iVar2;
                }
              }
              *(int **)(iVar2 + 8) = piVar5;
              piVar5[1] = iVar2;
              piVar5 = *(int **)(piVar9[1] + 8);
            }
            piVar5[4] = *(int *)(piVar9[1] + 0x10);
            *(undefined4 *)(piVar9[1] + 0x10) = 1;
            *(undefined4 *)(piVar5[2] + 0x10) = 1;
            puVar6 = (undefined4 *)piVar9[1];
            puVar7 = (undefined4 *)puVar6[2];
            puVar6[2] = *puVar7;
            if ((int *)*puVar7 != DAT_004ebfb8) {
              ((int *)*puVar7)[1] = (int)puVar6;
            }
            puVar7[1] = puVar6[1];
            if (puVar6 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar7;
              *puVar7 = puVar6;
            }
            else {
              piVar5 = (int *)puVar6[1];
              if (puVar6 == (undefined4 *)*piVar5) {
                *piVar5 = (int)puVar7;
                *puVar7 = puVar6;
              }
              else {
                piVar5[2] = (int)puVar7;
                *puVar7 = puVar6;
              }
            }
            goto LAB_0048bc76;
          }
        }
        else {
          if (piVar5[4] == 0) {
            piVar5[4] = 1;
            *(undefined4 *)(piVar9[1] + 0x10) = 0;
            piVar5 = (int *)piVar9[1];
            iVar2 = *piVar5;
            *piVar5 = *(int *)(iVar2 + 8);
            if (*(int **)(iVar2 + 8) != DAT_004ebfb8) {
              (*(int **)(iVar2 + 8))[1] = (int)piVar5;
            }
            *(int *)(iVar2 + 4) = piVar5[1];
            if (piVar5 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int *)(*(int *)((int)this + 4) + 4) = iVar2;
            }
            else {
              piVar8 = (int *)piVar5[1];
              if (piVar5 == (int *)piVar8[2]) {
                piVar8[2] = iVar2;
              }
              else {
                *piVar8 = iVar2;
              }
            }
            *(int **)(iVar2 + 8) = piVar5;
            piVar5[1] = iVar2;
            piVar5 = *(int **)piVar9[1];
          }
          if ((*(int *)(piVar5[2] + 0x10) != 1) || (*(int *)(*piVar5 + 0x10) != 1)) {
            if (*(int *)(*piVar5 + 0x10) == 1) {
              *(undefined4 *)(piVar5[2] + 0x10) = 1;
              piVar8 = (int *)piVar5[2];
              piVar5[4] = 0;
              piVar5[2] = *piVar8;
              if ((int *)*piVar8 != DAT_004ebfb8) {
                ((int *)*piVar8)[1] = (int)piVar5;
              }
              piVar8[1] = piVar5[1];
              if (piVar5 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int **)(*(int *)((int)this + 4) + 4) = piVar8;
              }
              else {
                piVar3 = (int *)piVar5[1];
                if (piVar5 == (int *)*piVar3) {
                  *piVar3 = (int)piVar8;
                }
                else {
                  piVar3[2] = (int)piVar8;
                }
              }
              *piVar8 = (int)piVar5;
              piVar5[1] = (int)piVar8;
              piVar5 = *(int **)piVar9[1];
            }
            piVar5[4] = *(int *)(piVar9[1] + 0x10);
            *(undefined4 *)(piVar9[1] + 0x10) = 1;
            *(undefined4 *)(*piVar5 + 0x10) = 1;
            puVar6 = (undefined4 *)piVar9[1];
            puVar7 = (undefined4 *)*puVar6;
            *puVar6 = puVar7[2];
            if ((int *)puVar7[2] != DAT_004ebfb8) {
              ((int *)puVar7[2])[1] = (int)puVar6;
            }
            puVar7[1] = puVar6[1];
            if (puVar6 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar7;
            }
            else {
              puVar4 = (undefined4 *)puVar6[1];
              if (puVar6 == (undefined4 *)puVar4[2]) {
                puVar4[2] = puVar7;
              }
              else {
                *puVar4 = puVar7;
              }
            }
            puVar7[2] = puVar6;
LAB_0048bc76:
            puVar6[1] = puVar7;
            break;
          }
        }
        piVar5[4] = 0;
        piVar9 = (int *)piVar9[1];
      } while (piVar9 != *(int **)(*(int *)((int)this + 4) + 4));
    }
    piVar9[4] = 1;
  }
  FUN_004b9beb();
  FUN_00430df0((undefined *)local_c);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
  *param_1 = param_2;
  return;
}


/* 0048bcb0 size=59 */

void FUN_0048bcb0(int *param_1)

{
  int *piVar1;
  
  if (param_1 != DAT_004ebfb8) {
    do {
      FUN_0048bcb0((int *)param_1[2]);
      piVar1 = (int *)*param_1;
      FUN_00430df0((undefined *)param_1);
      param_1 = piVar1;
    } while (piVar1 != DAT_004ebfb8);
  }
  return;
}


/* 0048bcf0 size=145 */

/* FUN_0048bcf0: lifted from original x86 -> lt_lifted.c */


/* 0048bd90 size=613 */

int __thiscall FUN_0048bd90(void *this,undefined4 *param_1,int param_2,int *param_3,uint *param_4)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  
  piVar3 = (int *)FUN_00430de0(0x14);
  piVar3[1] = (int)param_3;
  piVar3[4] = 0;
  *piVar3 = DAT_004ebfb8;
  piVar3[2] = DAT_004ebfb8;
  FUN_0048ce90(piVar3 + 3,param_4);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if (((param_3 == *(int **)((int)this + 4)) || (param_2 != DAT_004ebfb8)) ||
     (*param_4 < (uint)param_3[3])) {
    *param_3 = (int)piVar3;
    piVar4 = *(int **)((int)this + 4);
    if (param_3 == piVar4) {
      piVar4[1] = (int)piVar3;
      *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
    }
    else if (param_3 == (int *)*piVar4) {
      *piVar4 = (int)piVar3;
    }
  }
  else {
    param_3[2] = (int)piVar3;
    if (param_3 == *(int **)(*(int *)((int)this + 4) + 8)) {
      *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
    }
  }
  piVar4 = piVar3;
  if (piVar3 != *(int **)(*(int *)((int)this + 4) + 4)) {
    do {
      piVar5 = (int *)piVar4[1];
      if (piVar5[4] != 0) break;
      piVar6 = *(int **)piVar5[1];
      if (piVar5 == piVar6) {
        iVar1 = ((undefined4 *)piVar5[1])[2];
        if (*(int *)(iVar1 + 0x10) == 0) {
          piVar5[4] = 1;
          *(undefined4 *)(iVar1 + 0x10) = 1;
          *(undefined4 *)(*(int *)(piVar4[1] + 4) + 0x10) = 0;
          piVar4 = *(int **)(piVar4[1] + 4);
        }
        else {
          if (piVar4 == (int *)piVar5[2]) {
            piVar4 = (int *)piVar5[2];
            piVar5[2] = *piVar4;
            if (*piVar4 != DAT_004ebfb8) {
              *(int **)(*piVar4 + 4) = piVar5;
            }
            piVar4[1] = piVar5[1];
            if (piVar5 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int **)(*(int *)((int)this + 4) + 4) = piVar4;
            }
            else {
              piVar6 = (int *)piVar5[1];
              if (piVar5 == (int *)*piVar6) {
                *piVar6 = (int)piVar4;
              }
              else {
                piVar6[2] = (int)piVar4;
              }
            }
            *piVar4 = (int)piVar5;
            piVar5[1] = (int)piVar4;
            piVar4 = piVar5;
          }
          *(undefined4 *)(piVar4[1] + 0x10) = 1;
          *(undefined4 *)(*(int *)(piVar4[1] + 4) + 0x10) = 0;
          piVar5 = *(int **)(piVar4[1] + 4);
          piVar6 = (int *)*piVar5;
          *piVar5 = piVar6[2];
          if (piVar6[2] != DAT_004ebfb8) {
            *(int **)(piVar6[2] + 4) = piVar5;
          }
          piVar6[1] = piVar5[1];
          if (piVar5 == *(int **)(*(int *)((int)this + 4) + 4)) {
            *(int **)(*(int *)((int)this + 4) + 4) = piVar6;
            piVar6[2] = (int)piVar5;
          }
          else {
            piVar2 = (int *)piVar5[1];
            if (piVar5 == (int *)piVar2[2]) {
              piVar2[2] = (int)piVar6;
              piVar6[2] = (int)piVar5;
            }
            else {
              *piVar2 = (int)piVar6;
              piVar6[2] = (int)piVar5;
            }
          }
LAB_0048bfcc:
          piVar5[1] = (int)piVar6;
        }
      }
      else {
        if (piVar6[4] != 0) {
          if (piVar4 == (int *)*piVar5) {
            iVar1 = *piVar5;
            *piVar5 = *(int *)(iVar1 + 8);
            if (*(int *)(iVar1 + 8) != DAT_004ebfb8) {
              *(int **)(*(int *)(iVar1 + 8) + 4) = piVar5;
            }
            *(int *)(iVar1 + 4) = piVar5[1];
            if (piVar5 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int *)(*(int *)((int)this + 4) + 4) = iVar1;
            }
            else {
              piVar4 = (int *)piVar5[1];
              if (piVar5 == (int *)piVar4[2]) {
                piVar4[2] = iVar1;
              }
              else {
                *piVar4 = iVar1;
              }
            }
            *(int **)(iVar1 + 8) = piVar5;
            piVar5[1] = iVar1;
            piVar4 = piVar5;
          }
          *(undefined4 *)(piVar4[1] + 0x10) = 1;
          *(undefined4 *)(*(int *)(piVar4[1] + 4) + 0x10) = 0;
          piVar5 = *(int **)(piVar4[1] + 4);
          piVar6 = (int *)piVar5[2];
          piVar5[2] = *piVar6;
          if (*piVar6 != DAT_004ebfb8) {
            *(int **)(*piVar6 + 4) = piVar5;
          }
          piVar6[1] = piVar5[1];
          if (piVar5 == *(int **)(*(int *)((int)this + 4) + 4)) {
            *(int **)(*(int *)((int)this + 4) + 4) = piVar6;
          }
          else {
            piVar2 = (int *)piVar5[1];
            if (piVar5 == (int *)*piVar2) {
              *piVar2 = (int)piVar6;
            }
            else {
              piVar2[2] = (int)piVar6;
            }
          }
          *piVar6 = (int)piVar5;
          goto LAB_0048bfcc;
        }
        piVar5[4] = 1;
        piVar6[4] = 1;
        *(undefined4 *)(*(int *)(piVar4[1] + 4) + 0x10) = 0;
        piVar4 = *(int **)(piVar4[1] + 4);
      }
    } while (piVar4 != *(int **)(*(int *)((int)this + 4) + 4));
  }
  *(undefined4 *)(*(int *)(*(int *)((int)this + 4) + 4) + 0x10) = 1;
  *param_1 = piVar3;
  return;
}


