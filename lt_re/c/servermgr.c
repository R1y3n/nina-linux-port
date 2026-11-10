/* lithtech.exe decompilation - module servermgr */
#include "ghidra_types.h"

/* 0047a7f0 size=706 */

/* repo: runtime/server/src/servermgr.cpp, runtime/client/src/clientmgr.cpp */

int __cdecl servermgr_47a7f0(int param_1,char *param_2,int *param_3,undefined4 *param_4)

{
  undefined1 uVar1;
  void *this;
  undefined4 *this_00;
  int iVar2;
  undefined3 extraout_var;
  int iVar3;
  int local_2c;
  char *local_28;
  byte *local_24;
  undefined1 *local_20;
  int *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  int local_4;
  
  local_14 = 0;
  local_24 = (byte *)0x0;
  local_20 = &LAB_0044f5a0;
  local_1c = (int *)0x0;
  local_10 = 1;
  local_c = 1;
  local_8 = 1;
  local_4 = 1;
  local_18 = 0;
  *param_4 = 0;
  this = (void *)FUN_00430de0(0x2c8);
  if (this != (void *)0x0) {
    this_00 = FUN_00450760(this,&DAT_004ecc58,&DAT_004ecc58);
    if (this_00 != (undefined4 *)0x0) {
      FUN_0047a7c0(param_2);
      local_24 = (byte *)FUN_0047b6a0(param_1 + 0xc3c,param_3);
      if (local_24 == (byte *)0x0) {
        (**(code **)*this_00)(1);
        if (0 < DAT_004e4420) {
          FUN_00436670((byte *)s_Couldn_t_open_model_file__s_004dbc84,param_2);
        }
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_se_LoadModelData_004dbca0);
        }
        return 0x16;
      }
      iVar2 = FUN_004590d0(this_00,local_24,&DAT_004ecc58);
      if (iVar2 == 0) {
        local_1c = &local_2c;
        local_2c = param_1;
        local_28 = param_2;
        local_20 = &LAB_0047a4e0;
        local_18 = (**(code **)(**(int **)(param_1 + 0xb38) + 0x18c))();
        if (2 < DAT_004e4420) {
          FUN_00436670((byte *)s_Calling_Model__Load_____s_004dbbc8,param_2);
        }
        uVar1 = KeyPad_4581d0(this_00,(int *)&local_24);
        iVar2 = CONCAT31(extraout_var,uVar1);
      }
      (**(code **)(*(int *)local_24 + 4))();
      if (iVar2 == 0) {
        iVar3 = FUN_00451b00(this_00,param_2);
        if (iVar3 != 0) {
          if (local_c == 0) {
            (**(code **)*this_00)(1);
            if (0 < DAT_004e4420) {
              FUN_00436670((byte *)s_Child_model_trees_invalid_in_mod_004dbc5c,param_2);
            }
            FUN_004356e0();
            if (0 < DAT_004e4420) {
              FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_se_LoadModelData_004dbca0)
              ;
              return 0x18;
            }
          }
          else {
            if (local_4 != 0) {
              this_00[7] = param_3[2];
              *param_4 = this_00;
              return 0;
            }
            (**(code **)*this_00)(1);
            if (0 < DAT_004e4420) {
              FUN_00436670((byte *)s_Missing_one_or_more_child_models_004dbc28,param_2);
            }
            FUN_004356e0();
            if (0 < DAT_004e4420) {
              FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_se_LoadModelData_004dbca0)
              ;
            }
          }
          return 0x18;
        }
      }
      (**(code **)*this_00)(1);
      if (0 < DAT_004e4420) {
        FUN_00436670((byte *)s_Error__d_loading_model__s_004dbc0c,iVar2);
      }
      return iVar2;
    }
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_se_LoadModelData_004dbca0);
  }
  return 0x43;
}


/* 004854c0 size=1046 */

/* repo: runtime/server/src/servermgr.cpp */

undefined4 __fastcall servermgr_4854c0(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  LONG LVar6;
  
  FUN_00486990((int)param_1);
  pvVar1 = (void *)FUN_00430de0(8);
  if (pvVar1 == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_004926f0(pvVar1,param_1);
  }
  param_1[0x285] = uVar2;
  pvVar1 = (void *)FUN_00430de0(0x2c8);
  if (pvVar1 == (void *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    puVar3 = FUN_00450760(pvVar1,&DAT_004ecc58,&DAT_004ecc58);
  }
  param_1[0x34e] = puVar3;
  puVar3 = (undefined4 *)FUN_00430de0(8);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    *puVar3 = &PTR_LAB_004cd630;
    puVar3[1] = param_1;
  }
  param_1[0x22d] = puVar3;
  iVar4 = FUN_0046a550((int)(param_1 + 0xe5),0);
  if ((((iVar4 == 0) && (param_1[0x285] != 0)) && (param_1[0x34e] != 0)) && (param_1[0x22d] != 0)) {
    iVar4 = FUN_00417b40(param_1 + 0x335,param_1);
    if (iVar4 != 0) {
      iVar4 = FUN_0044e3f0(param_1 + 0x335,3);
      if (iVar4 == 0) {
        FUN_004a3d40(param_1 + 0x84,param_1 + 0xe5);
        FUN_00464930(param_1 + 0x23b,s_SERVER_PLAYER_004dc834);
        puVar3 = param_1 + 0x293;
        param_1[0x268] = param_1;
        param_1[0x294] = puVar3;
        *puVar3 = puVar3;
        param_1[0x334] = 0;
        param_1[0x31e] = 0;
        *(undefined1 *)(param_1 + 0x1a) = 0;
        param_1[0x2c7] = 100;
        param_1[0x2cb] = 0;
        param_1[0x2cd] = 0;
        param_1[0x2cc] = 0;
        puVar3 = param_1 + 0x2db;
        for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar3 = 0xffffffff;
          puVar3 = puVar3 + 1;
        }
        param_1[0x2ea] = 0;
        param_1[0x2b2] = 200;
        param_1[0x2b3] = 0;
        param_1[799] = 0;
        param_1[800] = 0;
        param_1[0x66] = 1;
        param_1[0x67] = 0;
        param_1[0x68] = 0;
        DAT_004ebf6c = 0;
        param_1[0x282] = 0;
        param_1[0x281] = 0;
        FUN_004b7be0(param_1 + 0x2eb,8,0x10,4);
        FUN_004b7be0(param_1 + 0x2f2,8,0x80,0x40);
        FUN_004b7be0(param_1 + 0x296,0x14,0x20,0x20);
        FUN_004b7be0(param_1 + 0x2f9,0x164,0x30,0x20);
        FUN_004b7be0(param_1 + 0x29d,0x18,0x20,0x10);
        FUN_004b7be0(param_1 + 3,0x1c,0x10,0x10);
        FUN_004b7be0(param_1 + 10,0x68,0x10,0x10);
        FUN_004b7be0(param_1 + 0x2a4,0xc0,0x10,0x10);
        FUN_004b7be0(param_1 + 0x2ab,10,0x20,0x20);
        puVar3 = param_1 + 0x2b5;
        param_1[0x303] = 0x40;
        param_1[0x2b6] = puVar3;
        *puVar3 = puVar3;
        puVar3 = param_1 + 0x2b8;
        param_1[0x2b9] = puVar3;
        *puVar3 = puVar3;
        puVar3 = param_1 + 700;
        param_1[0x2bd] = puVar3;
        *puVar3 = puVar3;
        puVar3 = param_1 + 0x27e;
        param_1[699] = 0;
        param_1[0x27f] = puVar3;
        *puVar3 = puVar3;
        puVar3 = param_1 + 0x2c0;
        param_1[0x27d] = 0;
        param_1[0x2c1] = puVar3;
        *puVar3 = puVar3;
        puVar3 = param_1 + 0x12;
        param_1[0x2bf] = 0;
        param_1[0x13] = puVar3;
        *puVar3 = puVar3;
        puVar3 = param_1 + 0x16;
        param_1[0x11] = 0;
        param_1[0x17] = puVar3;
        *puVar3 = puVar3;
        param_1[0x15] = 0;
        param_1[0x2cf] = 0xc1200000;
        param_1[0x2d0] = 0xc1200000;
        param_1[0x2d1] = 0xc1200000;
        param_1[0x2d2] = 0x41200000;
        param_1[0x2d3] = 0x41200000;
        param_1[0x2d4] = 0x41200000;
        param_1[0x2d5] = 0;
        param_1[0x2d6] = 0;
        param_1[0x2d7] = 0;
        param_1[0x2d8] = 0;
        param_1[0x2d9] = 0;
        param_1[0x2da] = 0;
        param_1[0x199] = 0;
        param_1[0x19a] = 0;
        *(undefined1 *)(param_1 + 0x19b) = 0;
        param_1[0x21b] = 0;
        param_1[0x21c] = 0;
        param_1[0x286] = 0;
        param_1[0x22f] = 0;
        param_1[0x230] = 0;
        param_1[0x232] = 0;
        param_1[0x233] = 0;
        param_1[0x234] = 0;
        param_1[0x235] = 0;
        param_1[0x236] = 0;
        param_1[0x237] = 0;
        param_1[0x238] = 0;
        param_1[0x239] = 0;
        param_1[0x231] = 0;
        piVar5 = FUN_00434a60(500,1);
        param_1[0x2b4] = piVar5;
        piVar5 = FUN_00434a60(100,1);
        param_1[0x2ca] = piVar5;
        FUN_00475ff0(param_1,param_1 + 0x321);
        FUN_004208c0(param_1 + 0x321,s_s_autoexec_cfg_004dc824);
        puVar3 = FUN_0047bcc0(param_1);
        param_1[0x2ce] = puVar3;
        FUN_0047b480(param_1 + 0x30f,param_1);
        FUN_00402950(param_1 + 0x287,param_1);
        FUN_004b80a0(param_1 + 0x309,300);
        param_1[0x22e] = 0;
        FUN_00478a70();
        puVar3 = DAT_004ebf68;
        if (DAT_004ebf68 != (undefined4 *)0x0) {
          LVar6 = InterlockedDecrement(DAT_004ebf68 + 1);
          if ((LVar6 < 1) && (puVar3 != (undefined4 *)0x0)) {
            (**(code **)*puVar3)(1);
          }
          DAT_004ebf68 = (undefined4 *)0x0;
        }
        return 1;
      }
    }
  }
  return 0;
}


/* 00485be0 size=112 */

/* repo: runtime/server/src/servermgr.cpp */

void __cdecl servermgr_485be0(int param_1,int param_2)

{
  int iVar1;
  
  *(uint *)(param_1 + 0x1a0) = *(uint *)(param_1 + 0x1a0) | 1;
  FUN_0047a020(param_1);
  iVar1 = *(int *)(param_1 + 0xaf4);
  do {
    if (iVar1 == param_1 + 0xaf0) {
      *(uint *)(param_1 + 0x1a0) = *(uint *)(param_1 + 0x1a0) & 0xfffffffe;
      return;
    }
    iVar1 = *(int *)(*(int *)(iVar1 + 8) + 400);
    if (param_2 == 0) {
      if ((*(byte *)(*(int *)(iVar1 + 0x24) + 8) & 4) == 0) {
        iVar1 = *(int *)(iVar1 + 0x20);
        goto LAB_00485c2b;
      }
    }
    else {
      iVar1 = *(int *)(iVar1 + 0x20);
LAB_00485c2b:
      FUN_00487570(param_1,iVar1);
    }
    iVar1 = *(int *)(param_1 + 0xaf4);
  } while( true );
}


/* 00485c70 size=71 */

/* repo: runtime/server/src/servermgr.cpp */

undefined4 __thiscall servermgr_485c70(void *this,byte *param_1)

{
  int *piVar1;
  
  FUN_00486990((int)this);
  piVar1 = udpdriver_465470((void *)((int)this + 0x8ec),param_1);
  if (piVar1 == (int *)0x0) {
    FUN_00489880((int)this,0x38,(char)param_1);
    return 0;
  }
  FUN_00436670((byte *)s_Listening_on_driver___s_004dc860,param_1);
  return 1;
}


/* 00486690 size=761 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/server/src/servermgr.cpp */

undefined4 __thiscall servermgr_486690(void *this,uint param_1,float param_2)

{
  float fVar1;
  bool bVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  int iVar6;
  longlong lVar7;
  undefined8 uVar8;
  
  FUN_00486990((int)this);
  FUN_00486640(this);
  fVar3 = param_2 + *(float *)((int)this + 0x8c4);
  *(float *)((int)this + 0x8e0) = fVar3 - *(float *)((int)this + 0x8e4);
  *(float *)((int)this + 0x8e4) = fVar3;
  netmgr_464bf0((void *)((int)this + 0x8ec),s_Server__004dcaa4,fVar3,1);
  DAT_004ea728 = 0;
  DAT_004ea72c = 0;
  DAT_004e99ac = 0;
  _DAT_004e99a8 = 0;
  _DAT_004e99b8 = 0;
  DAT_004ebf70 = 0;
  DAT_004ebf88 = 0;
  DAT_004ebfa0 = 0;
  DAT_004ebf8c = 0;
  iVar4 = FUN_00478970((int)this);
  if (iVar4 != 0) {
    return 0;
  }
  if (*(int *)((int)this + 0x198) == 0) {
    if (((param_1 & 1) == 0) && ((*(byte *)((int)this + 0x19c) & 1) == 0)) {
      if (DAT_004d8358 != *(float *)((int)this + 0x8c0)) {
        *(undefined4 *)((int)this + 0x8d4) = *(undefined4 *)((int)this + 0x8d8);
        *(undefined4 *)((int)this + 0x8c8) = *(undefined4 *)((int)this + 0x8cc);
        *(undefined4 *)((int)this + 0x8d0) = 0;
        *(undefined4 *)((int)this + 0x8dc) = 0;
      }
      fVar3 = _DAT_004cba94;
      *(float *)((int)this + 0x8c0) = DAT_004d8358;
      fVar3 = fVar3 / DAT_004d8358;
      uVar8 = CONCAT44(unaff_EBX,unaff_EBP);
      *(float *)((int)this + 0x8bc) = _DAT_004d835c * fVar3;
      *(float *)((int)this + 0x8cc) =
           (float)*(uint *)((int)this + 0x8d0) * fVar3 + *(float *)((int)this + 0x8c8);
      lVar7 = __ftol();
      iVar4 = (int)lVar7;
      if (iVar4 < 0) {
        iVar4 = 0;
      }
      fVar1 = *(float *)((int)this + 0x8e0);
      bVar2 = _DAT_004cbec0 <= fVar1;
      *(float *)((int)this + 0x8bc) = fVar1;
      if (bVar2) {
        if (_DAT_004cbef0 < fVar1) {
          fVar1 = _DAT_004cbef0;
        }
      }
      else {
        fVar1 = _DAT_004cbec0;
      }
      *(float *)((int)this + 0x8bc) = fVar1;
      iVar6 = 0;
      *(float *)((int)this + 0x8d8) = fVar1 + *(float *)((int)this + 0x8d8);
      do {
        FUN_004864e0(this,*(float *)((int)this + 0x8e0));
        if (((*(uint *)((int)this + 0x1a0) & 4) != 0) && ((*(uint *)((int)this + 0x1a0) & 8) == 0))
        {
          if (*(int *)((int)this + 0x8e8) == 0) {
            do {
            } while( true );
          }
          *(int *)((int)this + 0x8e8) = *(int *)((int)this + 0x8e8) + -1;
        }
        if (*(int **)((int)this + 0xa30) != (int *)0x0) {
          (**(code **)(**(int **)((int)this + 0xa30) + 0x3c))
                    (*(undefined4 *)((int)this + 0x8bc),uVar8);
        }
        classmgr_485f90((int)this);
        *(undefined4 *)((int)this + 0x8e0) = 0;
        iVar6 = iVar6 + 1;
        *(int *)((int)this + 0x8dc) = *(int *)((int)this + 0x8dc) + 1;
      } while (iVar6 < 1);
      uVar5 = *(int *)((int)this + 0x8d0) + iVar4;
      *(uint *)((int)this + 0x8d0) = uVar5;
      *(float *)((int)this + 0x8cc) = (float)uVar5 * fVar3 + *(float *)((int)this + 0x8c8);
    }
    else {
      *(float *)((int)this + 0x8e4) = fVar3;
      FUN_004863c0(this);
    }
    FUN_00486360(this);
    FUN_00486520((int)this);
  }
  if (DAT_004e9938 != 0) {
    FUN_00436670((byte *)s_Game_time____2f_004dca94,SUB84((double)*(float *)((int)this + 0x8d8),0));
  }
  if (DAT_004e9940 != 0) {
    FUN_00436670((byte *)s_ILTServer__FindObjectsTouchingSp_004dca64,DAT_004ebf70);
    FUN_00436670((byte *)s_ILTServer__FindObjectsTouchingSp_004dca34,DAT_004ebf88);
  }
  if (DAT_004e9944 != 0) {
    FUN_00436670((byte *)s_ILTServer__FindPoliesTouchingBox_004dca08,DAT_004ebfa0);
    FUN_00436670((byte *)s_ILTServer__FindPoliesTouchingBox_004dc9dc,DAT_004ebf8c);
  }
  return 1;
}


/* 00488360 size=226 */

/* repo: runtime/server/src/servermgr.cpp */

void __thiscall servermgr_488360(void *this,int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 unaff_EDI;
  
  iVar5 = *(int *)((int)this + 0x9fc);
  *(undefined4 *)((int)this + 0x664) = 0;
  if (iVar5 != (int)this + 0x9f8) {
    do {
      iVar4 = 2;
      piVar2 = (int *)(*(int *)(iVar5 + 8) + 0x134);
      do {
        iVar3 = 2;
        do {
          iVar1 = *piVar2;
          piVar2 = piVar2 + 3;
          iVar3 = iVar3 + -1;
          *(undefined2 *)(iVar1 + 0x38) = 1;
          *(undefined2 *)(iVar1 + 0x34) = 1;
        } while (iVar3 != 0);
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      iVar5 = *(int *)(iVar5 + 4);
    } while (iVar5 != (int)this + 0x9f8);
  }
  FUN_0047a3e0((int)this);
  FUN_0047a350((int)this);
  for (iVar5 = *(int *)((int)this + 0x9fc); iVar5 != (int)this + 0x9f8; iVar5 = *(int *)(iVar5 + 4))
  {
    FUN_004732c0(this,*(int **)(iVar5 + 8),1);
  }
  FUN_00488450((int)this);
  servermgr_485be0((int)this,0);
  servermgr_489a10((int)this);
  FUN_0042c050((int)this + 0x1a4);
  if (param_1 == 0) {
    FUN_0042be60((int)this + 0x1a4);
  }
  *(undefined4 *)((int)this + 0x198) = 1;
  FUN_00488490(this);
  FUN_00436670((byte *)s_World_ended_004dcbc4,unaff_EDI);
  return;
}


/* 00489a10 size=173 */

/* repo: runtime/server/src/servermgr.cpp */

void __cdecl servermgr_489a10(int param_1)

{
  int *piVar1;
  undefined1 *puVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x5c);
  if (iVar3 != param_1 + 0x58) {
    do {
      piVar1 = *(int **)(iVar3 + 8);
      iVar3 = *(int *)(iVar3 + 4);
      if ((((*(byte *)(piVar1 + 0xd) & 0x10) != 0) && (2 < DAT_004e4420)) &&
         ((int *)piVar1[5] != (int *)0x0)) {
        puVar2 = FUN_0047b9b0(param_1 + 0xc3c,(int *)piVar1[5]);
        FUN_00436670((byte *)s_Unfreed_sound_file__server___s_004dccd0,puVar2);
      }
      *(int *)(*piVar1 + 4) = piVar1[1];
      *(int *)piVar1[1] = *piVar1;
      piVar1[1] = (int)piVar1;
      *piVar1 = (int)piVar1;
      *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + -1;
      if ((int *)piVar1[3] != (int *)0x0) {
        FUN_00485490(DAT_004ebfa4,(int *)piVar1[3]);
      }
      piVar1[6] = 0;
      piVar1[3] = 0;
      if ((piVar1 != (int *)0x0) && (param_1 != -0x28)) {
        *piVar1 = *(int *)(param_1 + 0x40);
        *(int **)(param_1 + 0x40) = piVar1;
      }
    } while (iVar3 != param_1 + 0x58);
  }
  return;
}


