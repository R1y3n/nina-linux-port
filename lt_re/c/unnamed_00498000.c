/* lithtech.exe decompilation - unnamed_00498000 */
#include "ghidra_types.h"

/* 004984a0 size=544 */

int __thiscall FUN_004984a0(void *this,uint *param_1,int *param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int unaff_EBP;
  int *piVar5;
  
  if ((*param_1 & 0x200) != 0) {
    param_1[0x44] = 0;
  }
  if (*(int *)((int)this + 0x124) == 0) {
    return 1;
  }
  if (*(int *)((int)this + 0x128) == 0) {
    return 0;
  }
  piVar3 = FUN_00497800(this,param_2);
  if (piVar3 == (int *)0x0) {
    return 1;
  }
  uVar1 = *param_1;
  if ((((uVar1 & 0x800) == 0) || (*(int *)((int)this + 0x774) == 0)) &&
     (((uVar1 & 1) != 0 || ((uVar1 & 2) != 0)))) {
    if ((uVar1 & 1) == 0) {
      piVar5 = *(int **)((int)this + 0x31c);
      if (piVar5 == (int *)0x0) {
        FUN_004b7c60((int)this + 0x304,*(int *)((int)this + 0x30c));
        piVar5 = *(int **)((int)this + 0x31c);
        if (piVar5 == (int *)0x0) {
          piVar5 = (int *)0x0;
          goto LAB_004985d3;
        }
      }
      *(int *)((int)this + 0x31c) = *piVar5;
      if (piVar5 != (int *)0x0) {
        FUN_00495a90(piVar5);
      }
    }
    else {
      piVar5 = *(int **)((int)this + 0x2f8);
      if (piVar5 == (int *)0x0) {
        FUN_004b7c60((int)this + 0x2e0,*(int *)((int)this + 0x2e8));
        piVar5 = *(int **)((int)this + 0x2f8);
        if (piVar5 == (int *)0x0) {
          piVar5 = (int *)0x0;
          goto LAB_004985d3;
        }
      }
      *(int *)((int)this + 0x2f8) = *piVar5;
      if (piVar5 != (int *)0x0) {
        FUN_004955d0(piVar5);
      }
    }
  }
  else {
    piVar5 = *(int **)((int)this + 0x2d4);
    if (piVar5 == (int *)0x0) {
      FUN_004b7c60((int)this + 700,*(int *)((int)this + 0x2c4));
      piVar5 = *(int **)((int)this + 0x2d4);
      if (piVar5 == (int *)0x0) {
        piVar5 = (int *)0x0;
        goto LAB_004985d3;
      }
    }
    *(int *)((int)this + 0x2d4) = *piVar5;
    if (piVar5 != (int *)0x0) {
      FUN_0049a3f0(piVar5);
    }
  }
LAB_004985d3:
  if (piVar5 == (int *)0x0) {
    return 1;
  }
  iVar4 = (**(code **)(*piVar5 + 4))(piVar3,param_1,param_3);
  if (iVar4 == 0) {
    if (*(uint *)((int)this + 0x724) < 0x100) {
      *(int **)((int)this + *(uint *)((int)this + 0x724) * 4 + 0x324) = piVar5;
      piVar5[0x18] = *(int *)((int)this + 0x724);
      *(int *)((int)this + 0x724) = *(int *)((int)this + 0x724) + 1;
      if ((DAT_004d8288 < (uint)piVar3[0x22]) &&
         (piVar3 = (int *)FUN_00493b90((int)piVar3), piVar3 != (int *)0x0)) {
        FUN_00497990(this,piVar3);
      }
      return 0;
    }
    iVar4 = 1;
  }
  iVar2 = piVar5[1];
  (**(code **)(*piVar5 + 8))();
  if (iVar2 == 0) {
    (**(code **)*piVar5)(0);
    iVar2 = (int)this + 700;
  }
  else if (iVar2 == 1) {
    (**(code **)*piVar5)(0);
    iVar2 = (int)this + 0x2e0;
  }
  else {
    if (iVar2 != 2) goto LAB_004986a9;
    (**(code **)*piVar5)(0);
    iVar2 = (int)this + 0x304;
  }
  if (iVar2 != 0) {
    *piVar5 = *(int *)(iVar2 + 0x18);
    *(int **)(iVar2 + 0x18) = piVar5;
  }
LAB_004986a9:
  *(undefined4 *)(unaff_EBP + 0x110) = 0;
  return iVar4;
}


/* 004986c0 size=50 */

undefined4 FUN_004986c0(int param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    return 1;
  }
  _AIL_lock_0();
  _AIL_set_sample_user_data_12(param_1,0,param_2);
  _AIL_unlock_0();
  return 0;
}


/* 00498700 size=44 */

undefined4 FUN_00498700(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  _AIL_lock_0();
  uVar1 = _AIL_sample_user_data_8(param_1,0);
  _AIL_unlock_0();
  return uVar1;
}


/* 00498730 size=50 */

undefined4 FUN_00498730(int param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    return 1;
  }
  _AIL_lock_0();
  _AIL_set_3D_user_data_12(param_1,0,param_2);
  _AIL_unlock_0();
  return 0;
}


/* 00498770 size=44 */

undefined4 FUN_00498770(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  _AIL_lock_0();
  uVar1 = _AIL_3D_user_data_8(param_1,0);
  _AIL_unlock_0();
  return uVar1;
}


/* 004987a0 size=50 */

undefined4 FUN_004987a0(int param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    return 1;
  }
  _AIL_lock_0();
  _AIL_set_stream_user_data_12(param_1,0,param_2);
  _AIL_unlock_0();
  return 0;
}


/* 004987e0 size=65 */

undefined4 __fastcall FUN_004987e0(int param_1)

{
  int *piVar1;
  
  if (*(int *)(param_1 + 0x274) == 0) {
    return 0;
  }
  piVar1 = *(int **)(param_1 + 0x27c);
  *(int *)(*piVar1 + 4) = piVar1[1];
  *(int *)piVar1[1] = *piVar1;
  piVar1[1] = (int)piVar1;
  *piVar1 = (int)piVar1;
  *(int *)(param_1 + 0x274) = *(int *)(param_1 + 0x274) + -1;
  piVar1[1] = (int)piVar1;
  *piVar1 = (int)piVar1;
  return *(undefined4 *)piVar1[2];
}


/* 00498830 size=312 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00498830(void *this,int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float local_c;
  float fStack_8;
  float fStack_4;
  
  puVar3 = (undefined4 *)0x0;
  uVar4 = 0;
  if (*(int *)((int)this + 0x25c) == 0) goto LAB_00498938;
  (**(code **)(*param_1 + 0x40))(&local_c);
  piVar5 = *(int **)((int)this + 0x260);
  if (piVar5 == (int *)((int)this + 0x260)) {
LAB_004988f5:
    uVar4 = 0;
    if ((*(int *)((int)this + 0x264) == 0) ||
       (puVar3 = *(undefined4 **)(*(int *)((int)this + 0x264) + 8), puVar3 == (undefined4 *)0x0))
    goto LAB_00498938;
  }
  else {
    do {
      puVar1 = (undefined4 *)piVar5[2];
      if (((puVar1 != (undefined4 *)0x0) &&
          (iVar2 = _AIL_3D_user_data_8(*puVar1,3), iVar2 == param_1[2])) &&
         (_AIL_3D_position_16(*puVar1,&fStack_18,&fStack_14,&fStack_10), puVar3 = puVar1,
         (fStack_8 - fStack_14) * (fStack_8 - fStack_14) +
         (local_c - fStack_18) * (local_c - fStack_18) +
         (fStack_4 - fStack_10) * (fStack_4 - fStack_10) < _DAT_004cbaec)) break;
      piVar5 = (int *)*piVar5;
    } while (piVar5 != (int *)((int)this + 0x260));
    if (puVar3 == (undefined4 *)0x0) goto LAB_004988f5;
  }
  puVar1 = puVar3 + 1;
  *(undefined4 *)(puVar3[1] + 4) = puVar3[2];
  *(undefined4 *)puVar3[2] = *puVar1;
  puVar3[2] = puVar1;
  *puVar1 = puVar1;
  *(int *)((int)this + 0x25c) = *(int *)((int)this + 0x25c) + -1;
  puVar3[2] = puVar1;
  *puVar1 = puVar1;
  uVar4 = *puVar3;
LAB_00498938:
  if (((*(int *)((int)this + 0x25c) == 1) && (*(int *)((int)this + 0x264) != 0)) &&
     (puVar3 = *(undefined4 **)(*(int *)((int)this + 0x264) + 8), puVar3 != (undefined4 *)0x0)) {
    _AIL_end_3D_sample_4(*puVar3);
  }
  return uVar4;
}


/* 00498970 size=80 */

void __thiscall FUN_00498970(void *this,undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  _AIL_lock_0();
  iVar4 = _AIL_sample_user_data_8(param_1,2);
  _AIL_unlock_0();
  if (iVar4 != 0) {
    iVar2 = *(int *)((int)this + 0x278);
    piVar1 = (int *)(iVar4 + 4);
    *(int *)(iVar4 + 0xc) = iVar4;
    *piVar1 = iVar2;
    piVar3 = *(int **)(iVar2 + 4);
    *(int **)(iVar4 + 8) = piVar3;
    *piVar3 = (int)piVar1;
    *(int **)(*piVar1 + 4) = piVar1;
    *(int *)((int)this + 0x274) = *(int *)((int)this + 0x274) + 1;
  }
  return;
}


/* 004989c0 size=80 */

void __thiscall FUN_004989c0(void *this,undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  _AIL_lock_0();
  iVar4 = _AIL_3D_user_data_8(param_1,2);
  _AIL_unlock_0();
  if (iVar4 != 0) {
    iVar2 = *(int *)((int)this + 0x260);
    piVar1 = (int *)(iVar4 + 4);
    *(int *)(iVar4 + 0xc) = iVar4;
    *piVar1 = iVar2;
    piVar3 = *(int **)(iVar2 + 4);
    *(int **)(iVar4 + 8) = piVar3;
    *piVar3 = (int)piVar1;
    *(int **)(*piVar1 + 4) = piVar1;
    *(int *)((int)this + 0x25c) = *(int *)((int)this + 0x25c) + 1;
  }
  return;
}


/* 00498a10 size=54 */

undefined4 __fastcall FUN_00498a10(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x124) == 0) {
    return 1;
  }
  iVar2 = *(int *)(param_1 + 0x2b0);
  while (iVar2 != param_1 + 0x2ac) {
    iVar1 = *(int *)(iVar2 + 4);
    *(undefined4 *)(*(int *)(iVar2 + 8) + 0x40) = 0;
    iVar2 = iVar1;
  }
  return 0;
}


/* 00498a50 size=139 */

undefined4 __fastcall FUN_00498a50(void *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (*(int *)((int)param_1 + 0x124) == 0) {
    return 1;
  }
  iVar3 = 0;
  if (0 < *(int *)((int)param_1 + 0x724)) {
    puVar2 = (undefined4 *)((int)param_1 + 0x324);
    do {
      piVar1 = (int *)*puVar2;
      if ((piVar1 != (int *)0x0) && ((*(byte *)(piVar1 + 4) & 0x10) == 0)) {
        FUN_00497990(param_1,piVar1);
        iVar3 = iVar3 + -1;
        puVar2 = puVar2 + -1;
      }
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar3 < *(int *)((int)param_1 + 0x724));
  }
  iVar3 = *(int *)((int)param_1 + 0x2b0);
  while (iVar3 != (int)param_1 + 0x2ac) {
    puVar2 = *(undefined4 **)(iVar3 + 8);
    iVar3 = *(int *)(iVar3 + 4);
    if (((puVar2 != (undefined4 *)0x0) && (puVar2[0x10] == 0)) && (puVar2[0x22] == 0)) {
      FUN_004978e0(param_1,puVar2);
    }
  }
  return 0;
}


/* 00498ae0 size=316 */

undefined4 __thiscall
FUN_00498ae0(void *this,int param_1,undefined4 *param_2,float *param_3,float *param_4,int param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  *(int *)((int)this + 0x774) = param_1;
  if ((*(int *)((int)this + 0x124) == 0) || (*(int *)((int)this + 0x128) == 0)) {
    return 1;
  }
  if (param_1 == 0) {
    if (param_2 != (undefined4 *)0x0) {
      *(undefined4 *)((int)this + 0x72c) = *param_2;
      *(undefined4 *)((int)this + 0x730) = param_2[1];
      *(undefined4 *)((int)this + 0x734) = param_2[2];
      if (param_5 != 0) {
        *(undefined4 *)((int)this + 0x738) = *param_2;
        *(undefined4 *)((int)this + 0x73c) = param_2[1];
        *(undefined4 *)((int)this + 0x740) = param_2[2];
      }
    }
    if (param_3 != (float *)0x0) {
      *(float *)((int)this + 0x750) = *param_3;
      *(float *)((int)this + 0x754) = param_3[1];
      *(float *)((int)this + 0x758) = param_3[2];
    }
    if (param_4 != (float *)0x0) {
      *(float *)((int)this + 0x75c) = *param_4;
      *(float *)((int)this + 0x760) = param_4[1];
      *(float *)((int)this + 0x764) = param_4[2];
    }
    if ((param_3 != (float *)0x0) && (param_4 != (float *)0x0)) {
      fVar5 = *param_4;
      fVar6 = param_4[1];
      fVar7 = param_4[2];
      fVar1 = *param_3;
      fVar2 = param_3[2];
      fVar3 = param_3[1];
      fVar4 = *param_3;
      *(float *)((int)this + 0x768) = fVar6 * param_3[2] - fVar7 * param_3[1];
      *(float *)((int)this + 0x76c) = fVar7 * fVar1 - fVar5 * fVar2;
      *(float *)((int)this + 0x770) = fVar5 * fVar3 - fVar6 * fVar4;
    }
  }
  return 0;
}


/* 00498c20 size=117 */

undefined4 __fastcall FUN_00498c20(int *param_1)

{
  int iVar1;
  
  if (param_1[0x4c] == 0) {
    return 1;
  }
  if (param_1[0x4f] == 0) {
    if (param_1[0x4d] == 0) {
      _AIL_lock_0();
      iVar1 = _AIL_digital_handle_release_4(param_1[0x4c]);
      if (iVar1 == 0) {
        _AIL_unlock_0();
        return 1;
      }
      _AIL_unlock_0();
      param_1[0x4d] = 1;
      param_1[0x4e] = 0;
      return 0;
    }
  }
  else {
    (**(code **)(*param_1 + 0x68))();
  }
  return 0;
}


/* 00498dc0 size=534 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00498dc0(void *this,byte *param_1)

{
  float fVar1;
  bool bVar2;
  
  if (param_1 == (byte *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_CSoundMgr__SetReverbProperties_004dd260);
    }
    return 0x3c;
  }
  if ((*(int *)((int)this + 0x124) == 0) ||
     ((*(int *)((int)this + 0x7e8) == 0 && (*(int *)((int)this + 0x7ec) == 0)))) {
    return 1;
  }
  bVar2 = false;
  if ((*param_1 & 2) != 0) {
    if (0x19 < *(uint *)(param_1 + 8)) {
      param_1[8] = 0;
      param_1[9] = 0;
      param_1[10] = 0;
      param_1[0xb] = 0;
    }
    if (*(int *)((int)this + 0x7f0) != *(int *)(param_1 + 8)) {
      bVar2 = true;
      *(int *)((int)this + 0x7f0) = *(int *)(param_1 + 8);
    }
  }
  if ((*param_1 & 1) != 0) {
    if (_DAT_004cb524 <= *(float *)(param_1 + 4)) {
      if (*(float *)(param_1 + 4) <= _DAT_004cba94) {
        fVar1 = *(float *)(param_1 + 4);
      }
      else {
        fVar1 = _DAT_004cba94;
      }
    }
    else {
      fVar1 = _DAT_004cb524;
    }
    *(float *)(param_1 + 4) = fVar1;
    if (fVar1 != *(float *)((int)this + 0x7f8)) {
      *(float *)((int)this + 0x7f8) = fVar1;
      bVar2 = true;
    }
  }
  if ((*param_1 & 4) != 0) {
    if (_DAT_004cb524 <= *(float *)(param_1 + 0xc)) {
      if (*(float *)(param_1 + 0xc) <= _DAT_004cbee8) {
        fVar1 = *(float *)(param_1 + 0xc);
      }
      else {
        fVar1 = _DAT_004cbee8;
      }
    }
    else {
      fVar1 = _DAT_004cb524;
    }
    *(float *)((int)this + 0x7f4) = fVar1;
  }
  if ((*param_1 & 8) != 0) {
    if (_DAT_004cbaec <= *(float *)(param_1 + 0x10)) {
      if (*(float *)(param_1 + 0x10) <= _DAT_004cd90c) {
        fVar1 = *(float *)(param_1 + 0x10);
      }
      else {
        fVar1 = _DAT_004cd90c;
      }
    }
    else {
      fVar1 = _DAT_004cbaec;
    }
    *(float *)(param_1 + 0x10) = fVar1;
    if (fVar1 != *(float *)((int)this + 0x7fc)) {
      *(float *)((int)this + 0x7fc) = fVar1;
      bVar2 = true;
    }
  }
  if ((*param_1 & 0x10) != 0) {
    if (_DAT_004cb524 <= *(float *)(param_1 + 0x14)) {
      if (*(float *)(param_1 + 0x14) <= _DAT_004cbb00) {
        fVar1 = *(float *)(param_1 + 0x14);
      }
      else {
        fVar1 = _DAT_004cbb00;
      }
    }
    else {
      fVar1 = _DAT_004cb524;
    }
    *(float *)(param_1 + 0x14) = fVar1;
    if (fVar1 != *(float *)((int)this + 0x800)) {
      *(float *)((int)this + 0x800) = fVar1;
      bVar2 = true;
    }
  }
  if ((*(int *)((int)this + 0x7ec) != 0) && (bVar2)) {
    _AIL_lock_0();
    _AIL_set_3D_room_type_8(*(undefined4 *)((int)this + 0x13c),*(undefined4 *)((int)this + 0x7f0));
    _AIL_unlock_0();
  }
  return 0;
}


/* 00499a10 size=321 */

undefined4 __thiscall FUN_00499a10(void *this,int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  
  if (param_2 == 0) {
    FUN_004356e0();
    if (DAT_004e4420 < 1) {
      return 0x3c;
    }
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CSoundMgr__SetSoundFilterParam_004dd3a8);
    return 0x3c;
  }
  if (param_1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_CSoundMgr__SetSoundFilterParam_004dd3a8);
    }
    return 1;
  }
  piVar1 = (int *)FUN_00497aa0(this,param_1,0);
  if ((piVar1 == (int *)0x0) && (piVar1 = (int *)FUN_00497aa0(this,param_1,1), piVar1 == (int *)0x0)
     ) {
    FUN_004356e0();
    if (DAT_004e4420 < 1) {
      return 0x3c;
    }
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CSoundMgr__SetSoundFilterParam_004dd3a8);
    return 0x3c;
  }
  iVar2 = (**(code **)(*piVar1 + 0x48))(param_2,param_3);
  if (iVar2 != 0) {
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CSoundMgr__SetSoundFilterParam_004dd3a8);
  }
  return 0x3d;
}


/* 00499b60 size=342 */

undefined4 __thiscall FUN_00499b60(void *this,int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  if ((param_2 == 0) || (param_3 == 0)) {
    FUN_004356e0();
  }
  else {
    if (param_1 == 0) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     s_CSoundMgr__GetSoundFilterParam_004dd3c8);
      }
      return 1;
    }
    piVar1 = (int *)FUN_00497aa0(this,param_1,1);
    if (piVar1 != (int *)0x0) {
      if (piVar1[0x13] != 0) {
        iVar2 = (**(code **)(*piVar1 + 0x4c))(param_2,param_3);
        if (iVar2 != 0) {
          return 0;
        }
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_CSoundMgr__GetSoundFilterParam_004dd3c8);
        }
        return 0x3d;
      }
      FUN_004356e0();
      if (DAT_004e4420 < 1) {
        return 0x3c;
      }
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_CSoundMgr__GetSoundFilterParam_004dd3c8);
      return 0x3c;
    }
    FUN_004356e0();
  }
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CSoundMgr__GetSoundFilterParam_004dd3c8);
  }
  return 0x3c;
}


/* 0049a1a0 size=111 */

undefined4 * __fastcall FUN_0049a1a0(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cbb50;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  if (param_1[1] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[1]);
    param_1[1] = 0;
    param_1[3] = 0;
  }
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  if (param_1[1] != 0) {
    FUN_00456e60(&DAT_004ecc58,param_1[1]);
    param_1[1] = 0;
    param_1[3] = 0;
  }
  param_1[2] = 0;
  return param_1;
}


/* 0049a310 size=30 */

void __fastcall FUN_0049a310(int param_1)

{
  FUN_004b7c10(param_1 + 4);
  FUN_004b7b90((uint *)(param_1 + 4),0xa4,0x20);
  return;
}


/* 0049a330 size=30 */

void __fastcall FUN_0049a330(int param_1)

{
  FUN_004b7c10(param_1 + 4);
  FUN_004b7b90((uint *)(param_1 + 4),0xc4,0x20);
  return;
}


/* 0049a350 size=30 */

void __fastcall FUN_0049a350(int param_1)

{
  FUN_004b7c10(param_1 + 4);
  FUN_004b7b90((uint *)(param_1 + 4),0xdc,0x20);
  return;
}


/* 0049a370 size=52 */

undefined4 * __thiscall FUN_0049a370(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cd87c;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0049a3b0 size=52 */

undefined4 * __thiscall FUN_0049a3b0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cd86c;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0049a3f0 size=18 */

undefined4 * __fastcall FUN_0049a3f0(undefined4 *param_1)

{
  FUN_00493da0(param_1);
  *param_1 = &PTR_FUN_004cd910;
  return param_1;
}


/* 0049a410 size=52 */

undefined4 * __thiscall FUN_0049a410(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cd85c;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0049a450 size=52 */

undefined4 * __thiscall FUN_0049a450(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cd84c;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0049a490 size=30 */

int * __thiscall FUN_0049a490(void *this,byte param_1)

{
  FUN_00493e80(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0049a4e0 size=532 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_0049a4e0: lifted from original x86 -> lt_lifted.c */


/* 0049a700 size=344 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0049a700(void *this,float param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (*(float *)((int)this + 0x20) <= param_1) {
    *(undefined4 *)((int)this + 0x20) = 0;
  }
  else {
    *(float *)((int)this + 0x20) = *(float *)((int)this + 0x20) - param_1;
  }
  if (*(int *)((int)this + 0x10) == 0) {
    uVar1 = *(uint *)((int)this + 0x34);
    if (((((uVar1 & 0x10) == 0) && ((uVar1 & 4) == 0)) &&
        (*(float *)((int)this + 0x20) <= _DAT_004cb524)) && (*(int *)((int)this + 0x28) == 0)) {
      *(undefined4 *)((int)this + 0x10) = 1;
      return;
    }
    if (((uVar1 & 8) != 0) && ((uVar1 & 3) != 0)) {
      if ((*(int *)((int)this + 0x38) == 0) ||
         (iVar2 = *(int *)(*(int *)((int)this + 0x38) + 4), iVar2 == 0)) {
        if ((uVar1 & 0x10) == 0) {
          *(undefined4 *)((int)this + 0x20) = 0;
          *(undefined4 *)((int)this + 0x10) = 1;
          return;
        }
      }
      else if (((*(float *)(iVar2 + 0x194) != *(float *)((int)this + 0x50)) ||
               (*(float *)(iVar2 + 0x198) != *(float *)((int)this + 0x54))) ||
              (*(float *)(iVar2 + 0x19c) != *(float *)((int)this + 0x58))) {
        *(undefined4 *)((int)this + 0x50) = *(undefined4 *)(iVar2 + 0x194);
        *(undefined4 *)((int)this + 0x54) = *(undefined4 *)(iVar2 + 0x198);
        *(undefined4 *)((int)this + 0x58) = *(undefined4 *)(iVar2 + 0x19c);
        iVar3 = DAT_004ebfa4;
        iVar2 = *(int *)(*(int *)((int)this + 0xc) + 8);
        if ((*(char *)(*(int *)(DAT_004ebfa4 + 0xb10) + iVar2 * 8) == '\x02') &&
           (*(int *)(*(int *)(DAT_004ebfa4 + 0xb10) + iVar2 * 8 + 4) != 0)) {
          if (*(short *)((int)this + 0x2c) == 0) {
            *(undefined4 *)((int)this + 0x30) = *(undefined4 *)(DAT_004ebfa4 + 0xb24);
            *(void **)(iVar3 + 0xb24) = this;
          }
          *(byte *)((int)this + 0x2c) = *(byte *)((int)this + 0x2c) | 2;
          return;
        }
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_SetSoundTrackChangeFlags_004dcc54);
        }
      }
    }
  }
  return;
}


/* 0049aa90 size=81 */

void __cdecl FUN_0049aa90(undefined *param_1)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0xc) != 0) {
    uVar2 = 0;
    if (*(int *)(param_1 + 0x10) != 0) {
      iVar3 = 0;
      do {
        puVar1 = *(undefined **)(iVar3 + 0x20 + *(int *)(param_1 + 0xc));
        if (puVar1 != (undefined *)0x0) {
          FUN_00430fe0(puVar1);
        }
        uVar2 = uVar2 + 1;
        iVar3 = iVar3 + 0x3c;
      } while (uVar2 < *(uint *)(param_1 + 0x10));
    }
    FUN_00430fe0(*(undefined **)(param_1 + 0xc));
  }
  FUN_00430fe0(param_1);
  return;
}


/* 0049aaf0 size=58 */

void __cdecl FUN_0049aaf0(int *param_1,int param_2)

{
  int iVar1;
  
  *param_1 = param_2;
  iVar1 = *(int *)(param_2 + 0xc);
  param_1[1] = iVar1;
  if (*(int *)(iVar1 + 0x24) == 0) {
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 3;
    return;
  }
  iVar1 = *(int *)(iVar1 + 0x20);
  param_1[3] = 0;
  param_1[2] = iVar1;
  param_1[4] = 3;
  return;
}


/* 0049ab30 size=113 */

void __cdecl FUN_0049ab30(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_1 + 4);
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0x28) != 0) {
      if ((*(uint *)(param_1 + 0x10) & 1) != 0) {
        *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + param_2;
      }
      uVar2 = *(uint *)(iVar1 + 0x28);
      if ((*(uint *)(param_1 + 0xc) < uVar2) || ((*(uint *)(param_1 + 0x10) & 2) != 0)) {
        *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) % uVar2;
      }
      else {
        *(uint *)(param_1 + 0xc) = uVar2 - 1;
      }
      *(int *)(param_1 + 8) =
           *(int *)(iVar1 + 0x20) +
           (int)(((ulonglong)*(uint *)(param_1 + 0xc) / (1000 / (ulonglong)*(uint *)(iVar1 + 0x2c)))
                % (ulonglong)*(uint *)(iVar1 + 0x24)) * 4;
      return;
    }
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}


/* 0049acc0 size=161 */

undefined4 __thiscall FUN_0049acc0(void *this,uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)((int)this + 4) + 0x1b0);
  if (param_1 < *(uint *)(iVar1 + 0x10)) {
    iVar1 = *(int *)(iVar1 + 0xc) + param_1 * 0x3c;
    if (param_2 < *(uint *)(iVar1 + 0x24)) {
      *(int *)(*(int *)((int)this + 4) + 0x1b4) = iVar1;
      *(uint *)(*(int *)((int)this + 4) + 0x1b8) =
           *(int *)(*(int *)(*(int *)((int)this + 4) + 0x1b4) + 0x20) + param_2 * 4;
      *(uint *)(*(int *)((int)this + 4) + 0x1bc) = (param_2 * 1000) / *(uint *)(iVar1 + 0x2c);
      return 0;
    }
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SpriteControl__SetCurPos_004dd488);
  }
  return 0x3c;
}


/* 0049ade0 size=68 */

undefined4 * __cdecl FUN_0049ade0(LPCSTR param_1,char *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = FUN_004ba1fd(param_1,param_2);
  if (iVar1 != 0) {
    puVar2 = (undefined4 *)FUN_00430de0(0xc);
    if (puVar2 != (undefined4 *)0x0) {
      *puVar2 = &PTR_FUN_004cd96c;
      puVar2[2] = 0;
      puVar2[1] = 0;
      puVar2[1] = iVar1;
      return puVar2;
    }
  }
  return (undefined4 *)0x0;
}


/* 0049ae90 size=71 */

undefined4 __thiscall FUN_0049ae90(void *this,char *param_1,uint param_2)

{
  uint uVar1;
  
  if (*(int **)((int)this + 4) != (int *)0x0) {
    if (param_2 == 0) {
      return 0;
    }
    uVar1 = FUN_004bb78b(param_1,1,param_2,*(int **)((int)this + 4));
    if (uVar1 == param_2) {
      return 0;
    }
    *(undefined4 *)((int)this + 8) = 1;
  }
  return 1;
}


/* 0049af60 size=88 */

undefined4 __thiscall FUN_0049af60(void *this,int *param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(char **)((int)this + 4) == (char *)0x0) {
    *param_1 = 0;
    return 1;
  }
  iVar1 = FUN_004ba5a8(*(char **)((int)this + 4));
  FUN_004ba72b(*(int **)((int)this + 4),0,2);
  iVar2 = FUN_004ba5a8(*(char **)((int)this + 4));
  *param_1 = iVar2;
  FUN_004ba72b(*(int **)((int)this + 4),iVar1,0);
  return 0;
}


/* 0049afc0 size=54 */

undefined4 * __thiscall FUN_0049afc0(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cd96c;
  if (*(FILE **)((int)this + 4) != (FILE *)0x0) {
    FUN_004ba14f(*(FILE **)((int)this + 4));
  }
  *(undefined ***)this = &PTR_LAB_004cc078;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0049b000 size=129 */

undefined4 * __cdecl FUN_0049b000(undefined4 param_1)

{
  undefined4 *this;
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00430de0(0x20);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  this = puVar1 + 1;
  *puVar1 = &PTR_LAB_004cc04c;
  *this = &PTR_LAB_004cbb50;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[5] = 0;
  FUN_0040c870(this,0,&DAT_004ecc58);
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[5] = 0;
  puVar1[4] = 0;
  if (puVar1[2] != 0) {
    FUN_00433560(this,&DAT_004ecc58);
  }
  puVar1[3] = 0;
  *puVar1 = &PTR_FUN_004cd998;
  puVar1[5] = param_1;
  puVar1[6] = 0;
  puVar1[7] = 0;
  return puVar1;
}


/* 0049b110 size=276 */

undefined1 __thiscall FUN_0049b110(void *this,undefined4 *param_1,uint param_2)

{
  bool bVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  if (param_2 != 0) {
    uVar4 = *(uint *)((int)this + 0xc);
    uVar5 = *(int *)((int)this + 0x18) + param_2;
    if (uVar4 < uVar5) {
      if (uVar5 < uVar4) {
        *(uint *)((int)this + 0xc) = uVar5;
        *(uint *)((int)this + 0x10) = *(int *)((int)this + 0x10) + (uVar4 - uVar5);
        bVar1 = true;
      }
      else if ((uVar4 < uVar5) && (uVar3 = *(int *)((int)this + 0x10) + uVar4, uVar5 <= uVar3)) {
        *(uint *)((int)this + 0xc) = uVar5;
        *(uint *)((int)this + 0x10) = uVar3 - uVar5;
        bVar1 = true;
      }
      else if (uVar5 == uVar4) {
        bVar1 = true;
      }
      else {
        puVar2 = (undefined4 *)FUN_0040c920(&DAT_004ecc58,0,*(int *)((int)this + 0x14) + uVar5);
        bVar1 = false;
        if (puVar2 != (undefined4 *)0x0) {
          uVar4 = *(uint *)((int)this + 0xc);
          if (uVar5 < *(uint *)((int)this + 0xc)) {
            uVar4 = uVar5;
          }
          puVar6 = *(undefined4 **)((int)this + 8);
          puVar7 = puVar2;
          for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
            *puVar7 = *puVar6;
            puVar6 = puVar6 + 1;
            puVar7 = puVar7 + 1;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
            puVar6 = (undefined4 *)((int)puVar6 + 1);
            puVar7 = (undefined4 *)((int)puVar7 + 1);
          }
          if (*(int *)((int)this + 8) != 0) {
            FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 8));
            *(undefined4 *)((int)this + 8) = 0;
          }
          *(undefined4 *)((int)this + 0x10) = 0;
          *(undefined4 **)((int)this + 8) = puVar2;
          *(uint *)((int)this + 0xc) = uVar5;
          *(undefined4 *)((int)this + 0x10) = *(undefined4 *)((int)this + 0x14);
          bVar1 = true;
        }
      }
      if (!bVar1) {
        return 1;
      }
    }
    puVar2 = (undefined4 *)(*(int *)((int)this + 8) + *(int *)((int)this + 0x18));
    for (uVar4 = param_2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar2 = *param_1;
      param_1 = param_1 + 1;
      puVar2 = puVar2 + 1;
    }
    for (uVar4 = param_2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar2 = *(undefined1 *)param_1;
      param_1 = (undefined4 *)((int)param_1 + 1);
      puVar2 = (undefined4 *)((int)puVar2 + 1);
    }
    *(int *)((int)this + 0x18) = *(int *)((int)this + 0x18) + param_2;
  }
  return 0;
}


/* 0049b270 size=90 */

undefined4 * __thiscall FUN_0049b270(void *this,byte param_1)

{
  *(undefined ***)((int)this + 4) = &PTR_LAB_004cbb50;
  if (*(int *)((int)this + 8) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 8));
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 0x10) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined ***)this = &PTR_LAB_004cc078;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0049b2d0 size=310 */

undefined4 * __cdecl FUN_0049b2d0(LPCSTR param_1)

{
  FILE *pFVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  
  pFVar1 = (FILE *)FUN_004ba1fd(param_1,&DAT_004d57f4);
  if (pFVar1 == (FILE *)0x0) {
    return (undefined4 *)0x0;
  }
  FUN_004ba72b((int *)pFVar1,0,2);
  uVar2 = FUN_004ba5a8((char *)pFVar1);
  FUN_004ba72b((int *)pFVar1,0,0);
  puVar3 = (undefined4 *)FUN_00430de0(0x20);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    *puVar3 = &PTR_LAB_004cc04c;
    puVar3[1] = &PTR_LAB_004cbb50;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    FUN_00430170(puVar3 + 1,0,0);
    *puVar3 = &PTR_FUN_004cd998;
    puVar3[5] = 0x100;
    puVar3[6] = 0;
    puVar3[7] = 0;
  }
  if ((uVar2 == puVar3[3]) && (uVar2 != 0)) {
LAB_0049b3ce:
    uVar5 = FUN_004bb674((char *)puVar3[2],1,uVar2,(int *)pFVar1);
    if (uVar5 == uVar2) goto LAB_0049b3b8;
    if (puVar3 != (undefined4 *)0x0) {
      (**(code **)*puVar3)(1);
      FUN_004ba14f(pFVar1);
      return (undefined4 *)0x0;
    }
  }
  else {
    if (puVar3[2] != 0) {
      FUN_00456e60(&DAT_004ecc58,puVar3[2]);
      puVar3[2] = 0;
      puVar3[4] = 0;
    }
    puVar3[3] = uVar2;
    if (uVar2 == 0) goto LAB_0049b3ce;
    iVar4 = FUN_0040c920(&DAT_004ecc58,0,puVar3[5] + uVar2);
    puVar3[2] = iVar4;
    if (iVar4 != 0) {
      puVar3[4] = puVar3[5];
      goto LAB_0049b3ce;
    }
    puVar3[3] = 0;
    puVar3[4] = 0;
    if (puVar3 != (undefined4 *)0x0) {
      (**(code **)*puVar3)(1);
    }
  }
  puVar3 = (undefined4 *)0x0;
LAB_0049b3b8:
  FUN_004ba14f(pFVar1);
  return puVar3;
}


/* 0049b410 size=46 */

undefined4 * __cdecl FUN_0049b410(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00430de0(0x14);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  *puVar1 = &PTR_LAB_004cd9c4;
  puVar1[1] = param_1;
  puVar1[3] = param_2;
  puVar1[2] = 0;
  puVar1[4] = 0;
  return puVar1;
}


/* 0049b560 size=31 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0049b560(void)

{
  if (DAT_004ec3d4 == 0) {
    _DAT_004ec3cc = &DAT_004ec3c8;
    DAT_004ec3c8 = &DAT_004ec3c8;
  }
  DAT_004ec3d4 = DAT_004ec3d4 + 1;
  return;
}


/* 0049b580 size=72 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0049b580(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  DAT_004ec3d4 = DAT_004ec3d4 + -1;
  if (DAT_004ec3d4 == 0) {
    puVar2 = DAT_004ec3c8;
    if ((undefined4 **)DAT_004ec3c8 != &DAT_004ec3c8) {
      do {
        puVar1 = (undefined4 *)*puVar2;
        FUN_00430fe0((undefined *)puVar2[2]);
        puVar2 = puVar1;
      } while ((undefined4 **)puVar1 != &DAT_004ec3c8);
    }
    _DAT_004ec3cc = &DAT_004ec3c8;
    DAT_004ec3c8 = &DAT_004ec3c8;
  }
  return;
}


/* 0049b5d0 size=52 */

void __cdecl FUN_0049b5d0(undefined *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_004ec3c8;
  if ((undefined4 **)DAT_004ec3c8 != &DAT_004ec3c8) {
    do {
      (*(code *)param_1)(puVar1[2] + 0x14,param_2);
      puVar1 = (undefined4 *)*puVar1;
    } while ((undefined4 **)puVar1 != &DAT_004ec3c8);
  }
  return;
}


/* 0049b6d0 size=16 */

void __cdecl FUN_0049b6d0(HLOCAL param_1)

{
  if (param_1 != (HLOCAL)0x0) {
    LocalFree(param_1);
  }
  return;
}


/* 0049b6e0 size=134 */

int * __cdecl FUN_0049b6e0(byte *param_1)

{
  byte *pbVar1;
  byte *pbVar2;
  int *piVar3;
  uint uVar4;
  short sVar5;
  
  if (param_1 == (byte *)0x0) {
    return (int *)0x0;
  }
  if (*param_1 == 0) {
    return (int *)&DAT_004ec3d8;
  }
  sVar5 = 0;
  pbVar1 = param_1;
  do {
    sVar5 = sVar5 + 1;
    pbVar1 = FUN_004bc7a0(pbVar1);
  } while (*pbVar1 != 0);
  pbVar2 = pbVar1 + (1 - (int)param_1);
  piVar3 = FUN_00430f00((size_t)(pbVar1 + (0x18 - (int)param_1)));
  *(short *)((int)piVar3 + 0x12) = (short)pbVar2;
  piVar3[3] = 1;
  *(short *)(piVar3 + 4) = sVar5;
  pbVar1 = (byte *)(piVar3 + 5);
  for (uVar4 = (uint)pbVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(int *)pbVar1 = *(int *)param_1;
    param_1 = param_1 + 4;
    pbVar1 = pbVar1 + 4;
  }
  for (uVar4 = (uint)pbVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pbVar1 = *param_1;
    param_1 = param_1 + 1;
    pbVar1 = pbVar1 + 1;
  }
  piVar3[2] = (int)piVar3;
  piVar3[1] = (int)&DAT_004ec3c8;
  *piVar3 = DAT_004ec3c8;
  *(int **)(DAT_004ec3c8 + 4) = piVar3;
  *(int **)piVar3[1] = piVar3;
  return piVar3;
}


/* 0049b770 size=146 */

int * __cdecl FUN_0049b770(char *param_1)

{
  char cVar1;
  short sVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  char *pcVar7;
  int *piVar8;
  
  if (param_1 == (char *)0x0) {
    return (int *)0x0;
  }
  if (*param_1 == '\0') {
    return (int *)&DAT_004ec3d8;
  }
  uVar4 = 0xffffffff;
  pcVar7 = param_1;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  sVar2 = (short)~uVar4;
  piVar3 = FUN_00430f00(~uVar4 + 0x17);
  uVar4 = 0xffffffff;
  *(short *)((int)piVar3 + 0x12) = sVar2;
  piVar3[3] = 1;
  *(short *)(piVar3 + 4) = sVar2 + -1;
  do {
    pcVar7 = param_1;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  piVar6 = (int *)(pcVar7 + -uVar4);
  piVar8 = piVar3 + 5;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *piVar8 = *piVar6;
    piVar6 = piVar6 + 1;
    piVar8 = piVar8 + 1;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)piVar8 = (char)*piVar6;
    piVar6 = (int *)((int)piVar6 + 1);
    piVar8 = (int *)((int)piVar8 + 1);
  }
  piVar3[2] = (int)piVar3;
  piVar3[1] = (int)&DAT_004ec3c8;
  *piVar3 = DAT_004ec3c8;
  *(int **)(DAT_004ec3c8 + 4) = piVar3;
  *(int **)piVar3[1] = piVar3;
  return piVar3;
}


/* 0049b810 size=13 */

void __cdecl FUN_0049b810(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  return;
}


/* 0049b820 size=47 */

void __cdecl FUN_0049b820(int *param_1)

{
  int iVar1;
  
  if (((param_1 != (int *)&DAT_004ec3d8) && (param_1 != (int *)0x0)) &&
     (iVar1 = param_1[3], param_1[3] = iVar1 + -1, iVar1 + -1 == 0)) {
    *(int *)param_1[1] = *param_1;
    *(int *)(*param_1 + 4) = param_1[1];
    FUN_00430fe0((undefined *)param_1);
  }
  return;
}


/* 0049b850 size=41 */

bool __cdecl FUN_0049b850(int param_1,int param_2)

{
  int iVar1;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    return false;
  }
  iVar1 = FUN_004bc7b7((byte *)(param_1 + 0x14),(byte *)(param_2 + 0x14));
  return (bool)('\x01' - (iVar1 != 0));
}


/* 0049b880 size=41 */

bool __cdecl FUN_0049b880(int param_1,int param_2)

{
  uint uVar1;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    return false;
  }
  uVar1 = FUN_004bc866((void *)(param_1 + 0x14),(void *)(param_1 + 0x14),(byte *)(param_2 + 0x14));
  return (bool)('\x01' - (uVar1 != 0));
}


/* 0049b8b0 size=13 */

int __cdecl FUN_0049b8b0(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return param_1 + 0x14;
}


/* 0049b8c0 size=18 */

undefined2 __cdecl FUN_0049b8c0(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined2 *)(param_1 + 0x10);
}


/* 0049b8e0 size=41 */

int __cdecl FUN_0049b8e0(int param_1,uint *param_2)

{
  if (param_1 == 0) {
    if (param_2 != (uint *)0x0) {
      *param_2 = 0;
    }
    return 0;
  }
  if (param_2 != (uint *)0x0) {
    *param_2 = (uint)*(ushort *)(param_1 + 0x12);
  }
  return param_1 + 0x14;
}


/* 0049b910 size=282 */

undefined4 __cdecl FUN_0049b910(uint *param_1)

{
  char cVar1;
  undefined2 uVar2;
  uint *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint *puVar10;
  undefined4 *unaff_retaddr;
  uint local_100 [63];
  undefined1 local_1;
  
  puVar3 = FUN_004bb020(param_1,':');
  if (puVar3 == (uint *)0x0) {
    uVar4 = 0x6cf0;
    _strncpy((char *)local_100,(char *)param_1,0xff);
    local_1 = 0;
  }
  else {
    uVar8 = (int)puVar3 - (int)param_1;
    puVar10 = local_100;
    for (uVar7 = uVar8 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar10 = *param_1;
      param_1 = param_1 + 1;
      puVar10 = puVar10 + 1;
    }
    for (uVar7 = uVar8 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(char *)puVar10 = (char)*param_1;
      param_1 = (uint *)((int)param_1 + 1);
      puVar10 = (uint *)((int)puVar10 + 1);
    }
    *(undefined1 *)((int)local_100 + uVar8) = 0;
    uVar4 = FUN_004bb167((void *)0x0,(byte *)((int)puVar3 + 1));
  }
  if (((char)local_100[0] < '0') || ('9' < (char)local_100[0])) {
    iVar6 = Ordinal_52(local_100);
    if (iVar6 == 0) {
      FUN_004317e0();
      return 0;
    }
    iVar9 = 0;
    uVar7 = 0;
    uVar8 = 0;
    do {
      cVar1 = (char)uVar8;
      uVar8 = uVar8 + 8;
      uVar7 = uVar7 | (uint)*(byte *)(iVar9 + **(int **)(iVar6 + 0xc)) << (0x18U - cVar1 & 0x1f);
      iVar9 = iVar9 + 1;
    } while (uVar8 < 0x20);
  }
  else {
    uVar5 = Ordinal_10(local_100);
    uVar7 = Ordinal_14(uVar5);
  }
  *unaff_retaddr = 0;
  unaff_retaddr[1] = 0;
  unaff_retaddr[2] = 0;
  unaff_retaddr[3] = 0;
  *(undefined2 *)unaff_retaddr = 2;
  uVar5 = Ordinal_8(uVar7);
  unaff_retaddr[1] = uVar5;
  uVar2 = Ordinal_9(uVar4);
  *(undefined2 *)((int)unaff_retaddr + 2) = uVar2;
  return 1;
}


/* 0049baa0 size=175 */

undefined4 * __fastcall FUN_0049baa0(undefined4 *param_1)

{
  undefined4 *this;
  
  this = param_1 + 0x14;
  *param_1 = &PTR_LAB_004cc364;
  param_1[0x13] = 0x42f00000;
  param_1[0x11] = 0;
  *this = &PTR_LAB_004cda5c;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  FUN_0049e910(this,0,&DAT_004ecc58);
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x18] = 0;
  param_1[0x17] = 0;
  FUN_0049e910(this,0,&DAT_004ecc58);
  param_1[0x27] = 0;
  param_1[0x28] = 0;
  param_1[0x2a] = &PTR_LAB_004cc3d0;
  *param_1 = &PTR_FUN_004cd9f0;
  param_1[0x1f] = 0;
  param_1[0x29] = 0;
  param_1[0x24] = 0;
  param_1[0x26] = 0;
  param_1[0x25] = 0;
  param_1[0x19] = 0;
  _strncpy((char *)(param_1 + 1),s_internet_004d5ec0,0x3f);
  *(undefined1 *)((int)param_1 + 0x43) = 0;
  param_1[0x11] = 1;
  return param_1;
}


/* 0049bb60 size=30 */

undefined4 * __thiscall FUN_0049bb60(void *this,byte param_1)

{
  d3d_device_49bb80(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0049bc70 size=181 */

void __thiscall FUN_0049bc70(void *this,int param_1)

{
  undefined *puVar1;
  uint uVar2;
  
  uVar2 = *(uint *)((int)this + 0xa0);
  while (uVar2 != 0) {
    puVar1 = *(undefined **)(uVar2 + 8);
    uVar2 = *(uint *)(uVar2 + 4) & -(uint)(*(uint *)(uVar2 + 4) != *(uint *)((int)this + 0xa0));
    if (puVar1 != (undefined *)0x0) {
      if (*(int *)(puVar1 + 0xd8) != 0) {
        Ordinal_3(*(int *)(puVar1 + 0xd8));
      }
      FUN_004645f0((int)puVar1);
      FUN_00430df0(puVar1);
    }
  }
  *(undefined4 *)((int)this + 0xa0) = 0;
  *(undefined4 *)((int)this + 0x9c) = 0;
  if (*(int *)((int)this + 0x90) != 0) {
    Ordinal_3(*(int *)((int)this + 0x90));
    *(undefined4 *)((int)this + 0x90) = 0;
  }
  (**(code **)(*(int *)this + 0x2c))();
  if (*(undefined **)((int)this + 0x98) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)((int)this + 0x98));
    *(undefined4 *)((int)this + 0x98) = 0;
  }
  if ((param_1 != 0) && (*(int *)((int)this + 0xa4) != 0)) {
    Ordinal_116();
    *(undefined4 *)((int)this + 0xa4) = 0;
  }
  return;
}


/* 0049bd30 size=60 */

void __fastcall FUN_0049bd30(void *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = *(uint *)((int)param_1 + 0xa0);
  while (uVar3 != 0) {
    uVar1 = *(uint *)(uVar3 + 4);
    uVar2 = *(uint *)((int)param_1 + 0xa0);
    FUN_0049bda0(param_1,*(int *)(uVar3 + 8));
    uVar3 = uVar1 & -(uint)(uVar1 != uVar2);
  }
  FUN_0049bc70(param_1,1);
  return;
}


/* 0049bd70 size=44 */

bool FUN_0049bd70(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = Ordinal_20(param_1,param_2,param_3,0,param_4,0x10);
  return iVar1 == param_3;
}


/* 0049bda0 size=63 */

void __thiscall FUN_0049bda0(void *this,int param_1)

{
  int iVar1;
  uint local_4;
  
  local_4 = (uint)this & 0xffff0000;
  iVar1 = 4;
  do {
    FUN_0049bd70(*(undefined4 *)((int)this + 0x90),&local_4,3,param_1 + 0xbc);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


/* 0049be30 size=114 */

undefined4 __thiscall FUN_0049be30(void *this,int *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00430de0(0x9c);
  if (piVar1 == (int *)0x0) {
    return 1;
  }
  *(void **)((int)this + 0xac) = this;
  *piVar1 = (int)this + 0xa8;
  piVar1[1] = 1;
  piVar1[2] = 0;
  piVar1[3] = 0;
  piVar1[4] = 0;
  piVar1[5] = 0;
  _strncpy((char *)(piVar1 + 6),s_Internet_TCP_IP_004dd9c8,0x7f);
  *(undefined1 *)((int)piVar1 + 0x97) = 0;
  piVar1[0x26] = *param_1;
  *param_1 = (int)piVar1;
  return 0;
}


