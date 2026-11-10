/* lithtech.exe decompilation - module soundmgr */
#include "ghidra_types.h"

/* 00496e50 size=398 */

/* repo: runtime/sound/src/soundmgr.cpp */

void __thiscall soundmgr_496e50(void *this,int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  char *pcVar6;
  int *piVar7;
  
  uVar4 = 0;
  if (param_1 != 0) {
    if (*(int *)((int)this + 0x724) != 0) {
      puVar5 = (undefined4 *)((int)this + 0x324);
      do {
        piVar2 = (int *)*puVar5;
        if (piVar2 != (int *)0x0) {
          if (((*(byte *)(piVar2 + 4) & 0x10) != 0) && (1 < DAT_004e4420)) {
            if (piVar2[2] == 0) {
              pcVar6 = s_Unfreed_sound_handle_0x_x_004dd11c;
              piVar7 = piVar2;
            }
            else {
              pcVar6 = s_Unfreed_sound_handle__s_004dd138;
              piVar7 = *(int **)(*(int *)(piVar2[2] + 4) + 0x1c);
            }
            FUN_00436670((byte *)pcVar6,piVar7);
          }
          FUN_00497990(this,piVar2);
          uVar4 = uVar4 - 1;
          puVar5 = puVar5 + -1;
        }
        uVar4 = uVar4 + 1;
        puVar5 = puVar5 + 1;
      } while (uVar4 < *(uint *)((int)this + 0x724));
    }
    *(undefined4 *)((int)this + 0x724) = 0;
    (**(code **)(*(int *)((int)this + 0x2b8) + 0xc))();
    (**(code **)(*(int *)((int)this + 0x2dc) + 0xc))();
    (**(code **)(*(int *)((int)this + 0x300) + 0xc))();
    iVar1 = *(int *)((int)this + 0x2b0);
    while (iVar1 != (int)this + 0x2ac) {
      iVar3 = *(int *)(iVar1 + 4);
      if (*(undefined4 **)(iVar1 + 8) != (undefined4 *)0x0) {
        FUN_004978e0(this,*(undefined4 **)(iVar1 + 8));
        iVar1 = iVar3;
      }
    }
    iVar1 = (int)this + 0x2ac;
    *(int *)((int)this + 0x2b0) = iVar1;
    *(int *)iVar1 = iVar1;
    *(undefined4 *)((int)this + 0x2a8) = 0;
    (**(code **)(*(int *)((int)this + 0x284) + 0xc))();
  }
  FUN_00497530((int)this);
  FUN_00497740((int)this);
  if (*(int *)((int)this + 0x728) != 0) {
    _AIL_lock_0();
    _AIL_close_3D_listener_4(*(undefined4 *)((int)this + 0x728));
    _AIL_unlock_0();
    *(undefined4 *)((int)this + 0x728) = 0;
  }
  if (*(int *)((int)this + 0x13c) != 0) {
    _AIL_lock_0();
    _AIL_close_3D_provider_4(*(undefined4 *)((int)this + 0x13c));
    _AIL_unlock_0();
    *(undefined4 *)((int)this + 0x13c) = 0;
  }
  if (*(int *)((int)this + 0x130) != 0) {
    _AIL_lock_0();
    _AIL_waveOutClose_4(*(undefined4 *)((int)this + 0x130));
    _AIL_unlock_0();
    *(undefined4 *)((int)this + 0x130) = 0;
    *(undefined4 *)((int)this + 0x134) = 0;
    *(undefined4 *)((int)this + 0x138) = 0;
  }
  _AIL_shutdown_0();
  *(undefined4 *)((int)this + 0x124) = 0;
  *(undefined4 *)((int)this + 0x128) = 0;
  return;
}


/* 00497010 size=764 */

/* repo: runtime/sound/src/soundmgr.cpp */

undefined4 __thiscall soundmgr_497010(void *this,undefined4 *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  undefined4 *puVar5;
  char *pcVar6;
  bool bVar7;
  undefined4 local_18;
  byte *local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  undefined4 local_4;
  
  if (*(int *)((int)this + 300) == 0) {
    if (*(int *)((int)this + 0x124) == 0) {
      FUN_004b4ed0();
      _AIL_startup_0();
      FUN_00496790();
      _AIL_lock_0();
      iVar2 = _AIL_waveOutOpen_16(&local_4,0,0xffffffff,0);
      if (iVar2 != 0) {
        _AIL_unlock_0();
        _AIL_shutdown_0();
        return 1;
      }
      _AIL_unlock_0();
    }
    local_c = 0;
    _AIL_lock_0();
    iVar2 = _AIL_enumerate_3D_providers_12(&local_c,&local_18,&local_14);
    while (iVar2 != 0) {
      local_10 = 0;
      pcVar6 = s_Microsoft_DirectSound3D_with_Cre_004dd22c;
      pbVar3 = local_14;
      do {
        bVar1 = *pbVar3;
        bVar7 = bVar1 < (byte)*pcVar6;
        if (bVar1 != *pcVar6) {
LAB_004970d4:
          iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_004970d9;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar7 = bVar1 < (byte)pcVar6[1];
        if (bVar1 != pcVar6[1]) goto LAB_004970d4;
        pbVar3 = pbVar3 + 2;
        pcVar6 = pcVar6 + 2;
      } while (bVar1 != 0);
      iVar2 = 0;
LAB_004970d9:
      if (iVar2 == 0) {
        iVar2 = 2;
      }
      else {
        pcVar6 = s_Aureal_A3D_Interactive_TM__004dd210;
        pbVar3 = local_14;
        do {
          bVar1 = *pbVar3;
          bVar7 = bVar1 < (byte)*pcVar6;
          if (bVar1 != *pcVar6) {
LAB_00497112:
            iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
            goto LAB_00497117;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar7 = bVar1 < (byte)pcVar6[1];
          if (bVar1 != pcVar6[1]) goto LAB_00497112;
          pbVar3 = pbVar3 + 2;
          pcVar6 = pcVar6 + 2;
        } while (bVar1 != 0);
        iVar2 = 0;
LAB_00497117:
        if (iVar2 == 0) {
          iVar2 = 4;
        }
        else {
          pcVar6 = s_Microsoft_DirectSound3D_hardware_004dd1e4;
          pbVar3 = local_14;
          do {
            bVar1 = *pbVar3;
            bVar7 = bVar1 < (byte)*pcVar6;
            if (bVar1 != *pcVar6) {
LAB_00497150:
              iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
              goto LAB_00497155;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar3[1];
            bVar7 = bVar1 < (byte)pcVar6[1];
            if (bVar1 != pcVar6[1]) goto LAB_00497150;
            pbVar3 = pbVar3 + 2;
            pcVar6 = pcVar6 + 2;
          } while (bVar1 != 0);
          iVar2 = 0;
LAB_00497155:
          if (iVar2 == 0) {
            iVar2 = 1;
          }
          else {
            pcVar6 = s_Microsoft_DirectSound3D_software_004dd1b8;
            pbVar3 = local_14;
            do {
              bVar1 = *pbVar3;
              bVar7 = bVar1 < (byte)*pcVar6;
              if (bVar1 != *pcVar6) {
LAB_0049718e:
                iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                goto LAB_00497193;
              }
              if (bVar1 == 0) break;
              bVar1 = pbVar3[1];
              bVar7 = bVar1 < (byte)pcVar6[1];
              if (bVar1 != pcVar6[1]) goto LAB_0049718e;
              pbVar3 = pbVar3 + 2;
              pcVar6 = pcVar6 + 2;
            } while (bVar1 != 0);
            iVar2 = 0;
LAB_00497193:
            if (iVar2 == 0) {
              iVar2 = 3;
            }
            else {
              pcVar6 = s_Intel_Realistic_Sound_Experience_004dd190;
              pbVar3 = local_14;
              do {
                bVar1 = *pbVar3;
                bVar7 = bVar1 < (byte)*pcVar6;
                if (bVar1 != *pcVar6) {
LAB_004971c9:
                  iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                  goto LAB_004971ce;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar3[1];
                bVar7 = bVar1 < (byte)pcVar6[1];
                if (bVar1 != pcVar6[1]) goto LAB_004971c9;
                pbVar3 = pbVar3 + 2;
                pcVar6 = pcVar6 + 2;
              } while (bVar1 != 0);
              iVar2 = 0;
LAB_004971ce:
              if (iVar2 == 0) {
                iVar2 = 5;
              }
              else {
                pcVar6 = s_Miles_2D_Stereo_Positional_Audio_004dd16c;
                pbVar3 = local_14;
                do {
                  bVar1 = *pbVar3;
                  bVar7 = bVar1 < (byte)*pcVar6;
                  if (bVar1 != *pcVar6) {
LAB_00497204:
                    iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                    goto LAB_00497209;
                  }
                  if (bVar1 == 0) break;
                  bVar1 = pbVar3[1];
                  bVar7 = bVar1 < (byte)pcVar6[1];
                  if (bVar1 != pcVar6[1]) goto LAB_00497204;
                  pbVar3 = pbVar3 + 2;
                  pcVar6 = pcVar6 + 2;
                } while (bVar1 != 0);
                iVar2 = 0;
LAB_00497209:
                iVar2 = (iVar2 != 0) + 6;
              }
            }
          }
        }
      }
      if (param_2 == 0) {
LAB_0049725d:
        puVar5 = (undefined4 *)FUN_00430de0(0x118);
        puVar5[0x45] = *(undefined4 *)((int)this + 300);
        *(undefined4 **)((int)this + 300) = puVar5;
        puVar5[0x44] = local_10;
        *(int *)(*(int *)((int)this + 300) + 4) = iVar2;
        *puVar5 = local_18;
        _strncpy((char *)(puVar5 + 2),(char *)local_14,0x104);
        *(undefined1 *)(puVar5 + 0x43) = 0;
      }
      else {
        iVar4 = _AIL_open_3D_provider_4(local_18);
        if (iVar4 == 0) {
          _AIL_3D_provider_attribute_12(local_18,s_EAX_environment_selection_004dd150,&local_8);
          if (local_8 != -1) {
            local_10 = 1;
          }
          _AIL_close_3D_provider_4(local_18);
          goto LAB_0049725d;
        }
      }
      iVar2 = _AIL_enumerate_3D_providers_12(&local_c,&local_18,&local_14);
    }
    _AIL_unlock_0();
    if (*(int *)((int)this + 0x124) == 0) {
      _AIL_lock_0();
      _AIL_waveOutClose_4(local_4);
      _AIL_unlock_0();
      _AIL_shutdown_0();
    }
  }
  *param_1 = *(undefined4 *)((int)this + 300);
  return 0;
}


