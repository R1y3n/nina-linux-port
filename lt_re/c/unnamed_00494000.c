/* lithtech.exe decompilation - unnamed_00494000 */
#include "ghidra_types.h"

/* 00494090 size=204 */

void __fastcall FUN_00494090(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  (**(code **)(*param_1 + 0x18))(0);
  FUN_00494160((int)param_1);
  if (param_1[0x15] != 0) {
    _AIL_lock_0();
    _AIL_close_stream_4(param_1[0x15]);
    _AIL_unlock_0();
    param_1[0x15] = 0;
  }
  if ((HANDLE)param_1[0x16] != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)param_1[0x16]);
    param_1[0x16] = -1;
  }
  param_1[0x12] = 0;
  if ((void *)param_1[2] != (void *)0x0) {
    FUN_00493b10((void *)param_1[2],(int)param_1);
    if (((param_1[4] & 0x1000U) != 0) && (((int *)param_1[2])[0x22] == 0)) {
      (**(code **)(*(int *)param_1[2] + 0x10))();
    }
    param_1[2] = 0;
  }
  piVar1 = param_1 + 0x19;
  iVar2 = 7;
  param_1[0x1a] = (int)piVar1;
  *piVar1 = (int)piVar1;
  param_1[3] = 0;
  param_1[4] = 0;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined1 *)(param_1 + 6) = 0;
  *(undefined1 *)(param_1 + 8) = 100;
  param_1[0xd] = 0x3f800000;
  param_1[10] = 0;
  *(undefined2 *)(param_1 + 0x17) = 0;
  param_1[0x11] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[7] = 0;
  param_1[0x18] = 0;
  param_1[0x21] = -1;
  piVar1 = param_1 + 0x29;
  do {
    piVar1[-7] = -1;
    *piVar1 = 0;
    piVar1 = piVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


/* 00494160 size=47 */

undefined4 __fastcall FUN_00494160(int param_1)

{
  undefined4 in_EAX;
  
  if ((*(short *)(param_1 + 0x14) != -1) && ((*(uint *)(param_1 + 0x10) & 0x200) == 0)) {
    FUN_00427060(DAT_004e516c,CONCAT22((short)((uint)in_EAX >> 0x10),*(short *)(param_1 + 0x14)));
    *(undefined4 *)(param_1 + 0x14) = 0xffff;
  }
  return 0;
}


/* 004941b0 size=268 */

undefined4 __thiscall FUN_004941b0(void *this,int param_1)

{
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  
  *(uint *)((int)this + 0x48) = *(uint *)((int)this + 0x48) & 0xfffffffd;
  if (*(int *)((int)this + 0x4c) == 0) {
    if (*(int *)((int)this + 0x50) == 0) {
      if (*(int *)((int)this + 0x54) != 0) {
        _AIL_lock_0();
        _AIL_close_stream_4(*(undefined4 *)((int)this + 0x54));
        *(undefined4 *)((int)this + 0x54) = 0;
        _AIL_unlock_0();
      }
      goto LAB_004942a0;
    }
    _AIL_lock_0();
    if (param_1 == 0) {
      iVar1 = _AIL_3D_sample_status_4(*(undefined4 *)((int)this + 0x50));
      if (iVar1 == 4) goto LAB_00494241;
    }
    else {
LAB_00494241:
      _AIL_stop_3D_sample_4(*(undefined4 *)((int)this + 0x50));
    }
    _AIL_unlock_0();
    iVar1 = *(int *)((int)this + 0x50);
    uVar3 = 0;
    FUN_00410170();
    FUN_00498730(iVar1,uVar3);
    uVar3 = *(undefined4 *)((int)this + 0x50);
    pvVar2 = (void *)FUN_00410170();
    FUN_004989c0(pvVar2,uVar3);
    *(undefined4 *)((int)this + 0x50) = 0;
    goto LAB_004942a0;
  }
  if (DAT_004d8284 == 0) {
    iVar1 = (**(code **)(*(int *)this + 0x50))();
    if (iVar1 == 0) goto LAB_004941e5;
    _AIL_set_sample_volume_8(*(undefined4 *)((int)this + 0x4c),0);
  }
  else {
LAB_004941e5:
    _AIL_stop_sample_4(*(undefined4 *)((int)this + 0x4c));
  }
  iVar1 = *(int *)((int)this + 0x4c);
  uVar3 = 0;
  FUN_00410170();
  FUN_004986c0(iVar1,uVar3);
  uVar3 = *(undefined4 *)((int)this + 0x4c);
  pvVar2 = (void *)FUN_00410170();
  FUN_00498970(pvVar2,uVar3);
  *(undefined4 *)((int)this + 0x4c) = 0;
LAB_004942a0:
  if (*(HANDLE *)((int)this + 0x58) != (HANDLE)0xffffffff) {
    CloseHandle(*(HANDLE *)((int)this + 0x58));
    *(undefined4 *)((int)this + 0x58) = 0xffffffff;
  }
  return 0;
}


/* 004942c0 size=46 */

undefined4 __fastcall FUN_004942c0(int *param_1)

{
  if ((*(byte *)(param_1 + 0x12) & 2) != 0) {
    (**(code **)(*param_1 + 0x1c))(1);
  }
  if (param_1[0x10] == 0) {
    param_1[0x12] = param_1[0x12] | 0x20;
    param_1[0x11] = param_1[9];
  }
  param_1[0x10] = param_1[0x10] + 1;
  return 0;
}


/* 00494330 size=394 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00494330(void *this,uint param_1)

{
  uint uVar1;
  uint uVar2;
  float fVar3;
  int iVar4;
  longlong lVar5;
  
  uVar1 = *(uint *)((int)this + 0x48);
  if ((uVar1 & 0x20) == 0) {
    if ((uVar1 & 1) == 0) {
      if ((uVar1 & 2) != 0) {
        _AIL_lock_0();
        iVar4 = _AIL_ms_count_0();
        _AIL_unlock_0();
        param_1 = iVar4 - *(int *)((int)this + 0x30);
        *(int *)((int)this + 0x30) = iVar4;
      }
      if (*(int *)((int)this + 8) == 0) {
        *(undefined4 *)((int)this + 0x24) = 0;
        return 0;
      }
      uVar1 = *(uint *)((int)this + 0x2c);
      uVar2 = *(uint *)((int)this + 0x24);
      if ((uVar1 < uVar2) && (uVar2 - uVar1 < param_1)) {
        *(uint *)((int)this + 0x24) = uVar1;
      }
      else if (((*(byte *)((int)this + 0x10) & 4) == 0) ||
              ((*(byte *)((int)this + 0x48) & 0x40) != 0)) {
        if (param_1 < uVar2) {
          if (*(short *)((int)this + 0x5c) != 1) {
            *(uint *)((int)this + 0x24) = uVar2 - param_1;
          }
        }
        else {
          *(undefined4 *)((int)this + 0x24) = 0;
        }
      }
      else {
        lVar5 = __ftol();
        iVar4 = (int)lVar5;
        lVar5 = __ftol();
        if (param_1 < (int)lVar5 - (uVar1 - uVar2)) {
          if (*(short *)((int)this + 0x5c) != 1) {
            *(uint *)((int)this + 0x24) = uVar2 - param_1;
          }
        }
        else {
          *(uint *)((int)this + 0x24) =
               (uVar1 - (((uVar1 - uVar2) - iVar4) + param_1) % (uint)((int)lVar5 - iVar4)) - iVar4;
        }
      }
      if (((*(uint *)((int)this + 0x48) & 0x80) != 0) &&
         (fVar3 = *(float *)((int)this + 0x3c) - (float)param_1 / (float)*(int *)((int)this + 0x38),
         *(float *)((int)this + 0x3c) = fVar3, fVar3 <= _DAT_004cb524)) {
        *(undefined4 *)((int)this + 0x3c) = 0;
        *(undefined4 *)((int)this + 0x24) = 0;
        return 0;
      }
      if ((*(int *)((int)this + 0x24) == 0) &&
         (((*(byte *)((int)this + 0x10) & 4) == 0 || ((*(uint *)((int)this + 0x48) & 0x40) != 0))))
      {
        return 0;
      }
    }
    else {
      *(uint *)((int)this + 0x48) = uVar1 & 0xfffffffe;
    }
  }
  return 1;
}


/* 004944c0 size=381 */

/* WARNING: Removing unreachable block (ram,0x00494580) */

undefined4 __fastcall FUN_004944c0(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  void *this;
  undefined4 uVar3;
  longlong lVar4;
  int *piVar5;
  
  if (param_1[0x13] == 0) {
    iVar1 = FUN_00410170();
    iVar1 = FUN_004987e0(iVar1);
    param_1[0x13] = iVar1;
    if (iVar1 == 0) {
      return 1;
    }
  }
  _AIL_lock_0();
  _AIL_init_sample_4(param_1[0x13]);
  iVar1 = *(int *)(param_1[2] + 0x50);
  if (iVar1 == 0) {
    uVar2 = *(undefined4 *)(param_1[2] + 0x60);
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0x60);
  }
  _AIL_set_sample_type_12(param_1[0x13],uVar2,0);
  iVar1 = FUN_00410170();
  if ((*(int *)(iVar1 + 0x7e8) == 0) || ((param_1[4] & 0x100U) == 0)) {
    _AIL_set_sample_reverb_16(param_1[0x13],0,0,0);
  }
  _AIL_set_sample_volume_8(param_1[0x13],((uint)*(byte *)(param_1 + 8) * 0x7f) / 100);
  iVar1 = param_1[2];
  if (((*(short *)(iVar1 + 8) == 0x11) || (*(short *)(iVar1 + 8) == 0x55)) &&
     (*(int *)(iVar1 + 0x50) == 0)) {
    iVar1 = _AIL_set_sample_file_12(param_1[0x13],*(undefined4 *)(iVar1 + 0x44),0);
    if (iVar1 == 0) {
      iVar1 = param_1[0x13];
      this = (void *)FUN_00410170();
      FUN_00498970(this,iVar1);
      param_1[0x13] = 0;
      return 1;
    }
  }
  else {
    if (*(int *)(iVar1 + 0x50) == 0) {
      uVar2 = *(undefined4 *)(iVar1 + 0x20);
    }
    else {
      uVar2 = *(undefined4 *)(*(int *)(iVar1 + 0x50) + 0x20);
    }
    if (*(int *)(iVar1 + 0x50) == 0) {
      uVar3 = *(undefined4 *)(iVar1 + 0x4c);
    }
    else {
      uVar3 = *(undefined4 *)(*(int *)(iVar1 + 0x50) + 0x4c);
    }
    _AIL_set_sample_address_12(param_1[0x13],uVar3,uVar2);
  }
  lVar4 = __ftol();
  _AIL_set_sample_playback_rate_8(param_1[0x13],(int)lVar4);
  _AIL_set_sample_pan_8(param_1[0x13],0x40);
  iVar1 = param_1[0x13];
  piVar5 = param_1;
  FUN_00410170();
  FUN_004986c0(iVar1,piVar5);
  _AIL_unlock_0();
  (**(code **)(*param_1 + 0x58))();
  return 0;
}


/* 00494880 size=468 */

undefined4 __fastcall FUN_00494880(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  HANDLE hFile;
  DWORD DVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  int local_130;
  int local_12c;
  undefined1 local_128 [32];
  char local_108 [264];
  
  if (*(int *)(param_1 + 8) == 0) {
    return 1;
  }
  if (*(int *)(param_1 + 0x54) == 0) {
    if (*(HANDLE *)(param_1 + 0x58) != (HANDLE)0xffffffff) {
      CloseHandle(*(HANDLE *)(param_1 + 0x58));
      *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
    }
    iVar3 = *(int *)(*(int *)(param_1 + 8) + 4);
    bVar1 = linuxfile_4283c0(*(int **)(iVar3 + 0x10),*(char **)(iVar3 + 0x1c),local_108,0x104,
                             &local_130,&local_12c);
    if (CONCAT31(extraout_var,bVar1) == 0) {
      return 1;
    }
    hFile = CreateFileA(local_108,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
    *(HANDLE *)(param_1 + 0x58) = hFile;
    if (hFile == (HANDLE)0xffffffff) {
      return 1;
    }
    if ((local_130 != 0) &&
       (DVar2 = SetFilePointer(hFile,local_130,(PLONG)0x0,0), DVar2 == 0xffffffff)) {
      CloseHandle(*(HANDLE *)(param_1 + 0x58));
      *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
      return 1;
    }
    FUN_004b9f62(local_128,(byte *)s______d_004dd0f8,*(undefined4 *)(param_1 + 0x58));
    _AIL_lock_0();
    iVar3 = FUN_00410170();
    uVar4 = _AIL_open_stream_12(*(undefined4 *)(iVar3 + 0x130),local_128,0);
    *(undefined4 *)(param_1 + 0x54) = uVar4;
    _AIL_unlock_0();
    if (*(int *)(param_1 + 0x54) == 0) {
      CloseHandle(*(HANDLE *)(param_1 + 0x58));
      *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
      return 1;
    }
  }
  _AIL_lock_0();
  lVar5 = __ftol();
  _AIL_set_stream_playback_rate_8(*(undefined4 *)(param_1 + 0x54),(int)lVar5);
  _AIL_set_stream_pan_8(*(undefined4 *)(param_1 + 0x54),0x40);
  _AIL_set_stream_volume_8
            (*(undefined4 *)(param_1 + 0x54),((uint)*(byte *)(param_1 + 0x20) * 0x7f) / 100);
  iVar3 = *(int *)(param_1 + 0x54);
  FUN_00410170();
  FUN_004987a0(iVar3,param_1);
  _AIL_unlock_0();
  return 0;
}


/* 00494df0 size=152 */

undefined4 __fastcall FUN_00494df0(int param_1)

{
  if ((*(byte *)(param_1 + 0x10) & 4) == 0) {
    return 1;
  }
  _AIL_lock_0();
  if (*(int *)(param_1 + 0x4c) != 0) {
    _AIL_set_sample_loop_block_12(*(int *)(param_1 + 0x4c),0,0xffffffff);
    _AIL_set_sample_loop_count_8(*(undefined4 *)(param_1 + 0x4c),1);
    _AIL_unlock_0();
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x40;
    return 0;
  }
  if (*(int *)(param_1 + 0x50) != 0) {
    _AIL_set_3D_sample_loop_block_12(*(int *)(param_1 + 0x50),0,0xffffffff);
    _AIL_set_3D_sample_loop_count_8(*(undefined4 *)(param_1 + 0x50),1);
    _AIL_unlock_0();
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x40;
    return 0;
  }
  if (*(int *)(param_1 + 0x54) != 0) {
    _AIL_set_stream_loop_count_8(*(int *)(param_1 + 0x54),1);
  }
  _AIL_unlock_0();
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x40;
  return 0;
}


/* 00494e90 size=48 */

ulonglong __fastcall FUN_00494e90(int param_1)

{
  ulonglong uVar1;
  
  uVar1 = __ftol();
  *(int *)(param_1 + 0x38) = (int)uVar1;
  *(undefined4 *)(param_1 + 0x3c) = 0x3f800000;
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x80;
  return uVar1 & 0xffffffff00000000;
}


/* 00494ec0 size=42 */

undefined4 __fastcall FUN_00494ec0(int *param_1)

{
  int *piVar1;
  
  (**(code **)(*param_1 + 0x1c))(1);
  if ((void *)param_1[2] != (void *)0x0) {
    FUN_00493b10((void *)param_1[2],(int)param_1);
    param_1[2] = 0;
  }
  piVar1 = param_1 + 0x19;
  param_1[0x1a] = (int)piVar1;
  *piVar1 = (int)piVar1;
  return 0;
}


/* 00494ef0 size=47 */

bool __fastcall FUN_00494ef0(int *param_1)

{
  void *this;
  int iVar1;
  
  FUN_00494ec0(param_1);
  if (((undefined4 *)param_1[3] == (undefined4 *)0x0) ||
     (this = *(void **)param_1[3], this == (void *)0x0)) {
    return true;
  }
  param_1[2] = (int)this;
  iVar1 = FUN_00493a80(this,(int)param_1);
  return iVar1 != 0;
}


/* 004955d0 size=45 */

undefined4 * __fastcall FUN_004955d0(undefined4 *param_1)

{
  FUN_00493da0(param_1);
  *param_1 = &PTR_FUN_004cd708;
  param_1[1] = 1;
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  return param_1;
}


/* 00495a90 size=81 */

undefined4 * __fastcall FUN_00495a90(undefined4 *param_1)

{
  FUN_00493da0(param_1);
  *param_1 = &PTR_FUN_004cd768;
  param_1[1] = 2;
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  param_1[0x31] = 0;
  param_1[0x32] = 0;
  param_1[0x33] = 0;
  param_1[0x34] = 0;
  param_1[0x35] = 0;
  param_1[0x36] = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  return param_1;
}


/* 00495ba0 size=102 */

undefined4 __thiscall FUN_00495ba0(void *this,float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  
  iVar5 = FUN_00410170();
  fVar3 = *(float *)(iVar5 + 0x730);
  fVar1 = *(float *)((int)this + 0x74);
  fVar4 = *(float *)(iVar5 + 0x734);
  fVar2 = *(float *)((int)this + 0x78);
  *param_1 = *(float *)((int)this + 0x70) - *(float *)(iVar5 + 0x72c);
  param_1[1] = fVar1 - fVar3;
  param_1[2] = fVar2 - fVar4;
  return 0;
}


/* 00496330 size=36 */

undefined4 __thiscall FUN_00496330(void *this,undefined4 param_1)

{
  _AIL_lock_0();
  _AIL_set_3D_sample_obstruction_8(*(undefined4 *)((int)this + 0x50),param_1);
  _AIL_unlock_0();
  return 0;
}


/* 00496360 size=36 */

undefined4 __thiscall FUN_00496360(void *this,undefined4 param_1)

{
  _AIL_lock_0();
  _AIL_set_3D_sample_occlusion_8(*(undefined4 *)((int)this + 0x50),param_1);
  _AIL_unlock_0();
  return 0;
}


/* 00496390 size=37 */

undefined4 __thiscall FUN_00496390(void *this,float *param_1)

{
  float10 fVar1;
  
  _AIL_lock_0();
  fVar1 = (float10)_AIL_3D_sample_obstruction_4(*(undefined4 *)((int)this + 0x50));
  *param_1 = (float)fVar1;
  _AIL_unlock_0();
  return 0;
}


/* 004963f0 size=713 */

undefined4 * __fastcall FUN_004963f0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1 + 0x98;
  *param_1 = &PTR_LAB_004cd88c;
  param_1[0x99] = puVar2;
  *puVar2 = puVar2;
  puVar2 = param_1 + 0x9e;
  param_1[0x97] = 0;
  param_1[0x9f] = puVar2;
  *puVar2 = puVar2;
  param_1[0x9d] = 0;
  param_1[0xa1] = &PTR_FUN_004cd87c;
  FUN_004b7b90(param_1 + 0xa2,0xa4,0x20);
  puVar2 = param_1 + 0xab;
  param_1[0xac] = puVar2;
  *puVar2 = puVar2;
  param_1[0xaa] = 0;
  param_1[0xae] = &PTR_FUN_004cd86c;
  FUN_004b7b90(param_1 + 0xaf,0xc4,0x20);
  param_1[0xb7] = &PTR_FUN_004cd85c;
  FUN_004b7b90(param_1 + 0xb8,0xc4,0x20);
  param_1[0xc0] = &PTR_FUN_004cd84c;
  FUN_004b7b90(param_1 + 0xc1,0xdc,0x20);
  puVar2 = param_1 + 0x1e0;
  *puVar2 = &PTR_LAB_004ccd18;
  param_1[0x1e1] = 0;
  param_1[0x1e2] = &PTR_LAB_004ccd3c;
  FUN_0049a1a0(param_1 + 500);
  *puVar2 = &PTR_FUN_004ccd2c;
  *(undefined2 *)((int)param_1 + 0x7ba) = 1;
  param_1[0x1f0] = 0;
  FUN_00467c90(puVar2,0x44c,0x44c);
  puVar2 = param_1 + 0x204;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0x64646464;
    puVar2 = puVar2 + 1;
  }
  *param_1 = &PTR_LAB_004cd7cc;
  param_1[1] = 0;
  param_1[0x4c] = 0;
  puVar2 = param_1 + 2;
  for (iVar1 = 0x47; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x4b] = 0;
  puVar2 = param_1 + 0x4f;
  for (iVar1 = 0x46; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_1 + 0x98;
  *(undefined1 *)(param_1 + 0x95) = 0;
  *(undefined1 *)((int)param_1 + 0x255) = 0;
  param_1[0x96] = 0;
  param_1[0x99] = puVar2;
  *puVar2 = puVar2;
  param_1[0x97] = 0;
  *(undefined1 *)(param_1 + 0x9b) = 0;
  puVar2 = param_1 + 0x9e;
  *(undefined1 *)((int)param_1 + 0x26d) = 0;
  param_1[0x9c] = 0;
  param_1[0x9f] = puVar2;
  *puVar2 = puVar2;
  puVar2 = param_1 + 0xab;
  param_1[0x9d] = 0;
  param_1[0xac] = puVar2;
  *puVar2 = puVar2;
  param_1[0xaa] = 0;
  (**(code **)(param_1[0xa1] + 0xc))();
  (**(code **)(param_1[0xae] + 0xc))();
  (**(code **)(param_1[0xb7] + 0xc))();
  (**(code **)(param_1[0xc0] + 0xc))();
  param_1[0x1ca] = 0;
  param_1[0x1cb] = 0;
  param_1[0x1cc] = 0;
  param_1[0x1cd] = 0;
  param_1[0x1ce] = 0;
  param_1[0x1cf] = 0;
  param_1[0x1d0] = 0;
  param_1[0x1d1] = 0;
  param_1[0x1d2] = 0;
  param_1[0x1d3] = 0;
  param_1[0x1d4] = 0;
  param_1[0x1d5] = 0;
  param_1[0x1d6] = 0x3f800000;
  param_1[0x1d7] = 0x3f800000;
  param_1[0x1d8] = 0;
  param_1[0x1d9] = 0;
  param_1[0x1da] = 0;
  param_1[0x1db] = 0x3f800000;
  param_1[0x1dc] = 0;
  param_1[0x1dd] = 1;
  *(undefined1 *)(param_1 + 0x1df) = 0;
  puVar2 = param_1 + 0xc9;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x1c9] = 0;
  param_1[0x1f9] = 0;
  param_1[0x1de] = 0x3f800000;
  param_1[0x1fa] = 0;
  param_1[0x1fb] = 0;
  param_1[0x1fe] = 0;
  param_1[0x1fc] = 0;
  param_1[0x1fd] = 0;
  param_1[0x1ff] = 0x3dcccccd;
  param_1[0x200] = 0x3f800000;
  param_1[0x4d] = 0;
  param_1[0x4e] = 0;
  param_1[0x201] = 0;
  param_1[0x202] = 0;
  param_1[0x203] = 0;
  param_1[0x49] = 0;
  param_1[0x4a] = 0;
  return param_1;
}


/* 004966c0 size=206 */

void __fastcall FUN_004966c0(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cd7cc;
  soundmgr_496e50(param_1,1);
  FUN_00496fe0((undefined *)param_1[0x4b]);
  param_1[0x4b] = 0;
  param_1[500] = &PTR_LAB_004cbb50;
  FUN_0040c870(param_1 + 500,0,&DAT_004ecc58);
  param_1[0x1e0] = &PTR_LAB_004ccd18;
  param_1[0xc0] = &PTR_FUN_004cd84c;
  FUN_004b7c10((int)(param_1 + 0xc1));
  param_1[0xc0] = &PTR_LAB_004cb514;
  param_1[0xb7] = &PTR_FUN_004cd85c;
  FUN_004b7c10((int)(param_1 + 0xb8));
  param_1[0xb7] = &PTR_LAB_004cb514;
  param_1[0xae] = &PTR_FUN_004cd86c;
  FUN_004b7c10((int)(param_1 + 0xaf));
  param_1[0xae] = &PTR_LAB_004cb514;
  param_1[0xa1] = &PTR_FUN_004cd87c;
  FUN_004b7c10((int)(param_1 + 0xa2));
  param_1[0xa1] = &PTR_LAB_004cb514;
  return;
}


/* 00496790 size=48 */

void FUN_00496790(void)

{
  _AIL_lock_0();
  _AIL_set_preference_8(0x1b,1);
  _AIL_set_preference_8(0xf,0);
  _AIL_set_preference_8(0x28,0x40000);
  _AIL_set_preference_8(0x12,0);
  _AIL_unlock_0();
  return;
}


/* 004967c0 size=1678 */

/* WARNING: Removing unreachable block (ram,0x004968cb) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004967c0(void *this,byte *param_1)

{
  int *piVar1;
  byte bVar2;
  bool bVar3;
  ushort uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined3 extraout_var;
  int iVar8;
  byte *pbVar9;
  undefined4 *puVar10;
  uint uVar11;
  uint local_38;
  uint local_34;
  int *local_30;
  undefined4 local_2c;
  uint local_28;
  int local_24;
  undefined2 local_20;
  ushort uStack_1e;
  undefined2 local_1c;
  undefined2 uStack_1a;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  if (DAT_004e986c == 0) {
    pbVar9 = param_1;
    puVar10 = (undefined4 *)((int)this + 8);
    for (iVar8 = 0x47; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar10 = *(undefined4 *)pbVar9;
      pbVar9 = pbVar9 + 4;
      puVar10 = puVar10 + 1;
    }
    uVar11 = *(uint *)(param_1 + 0x10c);
    param_1[0x110] = 0;
    param_1[0x111] = 0;
    param_1[0x112] = 0;
    param_1[0x113] = 0;
    local_34 = ~uVar11 >> 1 & 1;
    if (*(int *)((int)this + 0x724) == 0) {
      local_34 = 1;
    }
    else if (local_34 == 0) {
      uVar11 = 0;
      if (*(int *)((int)this + 0x724) != 0) {
        puVar10 = (undefined4 *)((int)this + 0x324);
        do {
          local_30 = (int *)*puVar10;
          if ((local_30 != (int *)0x0) && (iVar8 = FUN_00494ec0(local_30), iVar8 != 0)) {
            FUN_00497990(this,local_30);
            uVar11 = uVar11 - 1;
            puVar10 = puVar10 + -1;
          }
          uVar11 = uVar11 + 1;
          puVar10 = puVar10 + 1;
        } while (uVar11 < *(uint *)((int)this + 0x724));
      }
      iVar8 = *(int *)((int)this + 0x2b0);
      if (iVar8 != (int)this + 0x2ac) {
        do {
          piVar1 = *(int **)(iVar8 + 8);
          iVar8 = *(int *)(iVar8 + 4);
          if ((piVar1 != (int *)0x0) && (iVar7 = (**(code **)(*piVar1 + 0x10))(), iVar7 != 0)) {
            FUN_004978e0(this,piVar1);
          }
        } while (iVar8 != (int)this + 0x2ac);
      }
    }
    soundmgr_496e50(this,local_34);
    *(undefined4 *)((int)this + 0x124) = 1;
    *(undefined4 *)((int)this + 0x128) = 1;
    FUN_004b4ed0();
    _AIL_startup_0();
    FUN_00496790();
    param_1[0x105] = param_1[0x105];
    _AIL_lock_0();
    _AIL_set_preference_8(1,param_1[0x105]);
    _AIL_unlock_0();
    uStack_1e = *(ushort *)(param_1 + 0x10a);
    local_28 = (uint)*(ushort *)(param_1 + 0x108);
    local_1c = 0;
    local_24 = (int)((uint)uStack_1e << 1) >> 3;
    local_20 = (undefined2)local_24;
    local_2c = 0x20001;
    local_24 = local_24 * local_28;
    *(uint *)((int)this + 0x7e4) = *(uint *)(param_1 + 0x10c) & 1;
    _AIL_lock_0();
    iVar8 = _AIL_waveOutOpen_16((int)this + 0x130,0,0xffffffff,&local_2c);
    if (iVar8 != 0) {
      _AIL_unlock_0();
      soundmgr_496e50(this,1);
      return 0x23;
    }
    _AIL_unlock_0();
    *(undefined4 *)((int)this + 0x134) = 0;
    *(undefined4 *)((int)this + 0x138) = 0;
    soundmgr_497010(this,(undefined4 *)((int)this + 300),0);
    if ((*param_1 != 0) && (iVar8 = FUN_00497310(this,param_1), iVar8 != 0)) {
      soundmgr_496e50(this,1);
      return 0x55;
    }
    if (*(int *)((int)this + 0x13c) != 0) {
      _AIL_lock_0();
      _AIL_3D_provider_attribute_12
                (*(undefined4 *)((int)this + 0x13c),s_Maximum_supported_samples_004dd100,&local_38);
      _AIL_unlock_0();
      if (0xfe < local_38) {
        local_38 = 0xff;
      }
      bVar2 = (byte)local_38;
      if (0xff < (local_38 & 0xff)) {
        bVar2 = 0;
      }
      *(byte *)((int)this + 0x255) = bVar2;
      if (param_1[0x106] <= bVar2) {
        bVar2 = param_1[0x106];
      }
      *(byte *)((int)this + 0x255) = bVar2;
    }
    _AIL_lock_0();
    local_38 = _AIL_get_preference_4(1);
    _AIL_unlock_0();
    if (4 < local_38) {
      local_38 = local_38 - 4;
    }
    uVar11 = (uint)param_1[0x105];
    if (local_38 <= param_1[0x105]) {
      uVar11 = local_38;
    }
    *(char *)((int)this + 0x26d) = (char)uVar11;
    uVar5 = 0x100 - *(byte *)((int)this + 0x255);
    if ((int)(uVar11 & 0xff) < (int)uVar5) {
      uVar5 = uVar11 & 0xff;
    }
    *(char *)((int)this + 0x26d) = (char)uVar5;
    FUN_004973e0((int)this);
    FUN_004975f0((int)this);
    if (*(int *)((int)this + 0x13c) != 0) {
      _AIL_lock_0();
      uVar6 = _AIL_open_3D_listener_4(*(undefined4 *)((int)this + 0x13c));
      *(undefined4 *)((int)this + 0x728) = uVar6;
      _AIL_unlock_0();
      if (*(int *)((int)this + 0x728) == 0) {
        soundmgr_496e50(this,1);
        return 0x55;
      }
      _AIL_lock_0();
      _AIL_set_3D_position_16(*(undefined4 *)((int)this + 0x728),0,0,0);
      _AIL_set_3D_velocity_vector_16(*(undefined4 *)((int)this + 0x728),0,0,0);
      _AIL_set_3D_orientation_28
                (*(undefined4 *)((int)this + 0x728),*(undefined4 *)((int)this + 0x750),
                 *(undefined4 *)((int)this + 0x754),*(undefined4 *)((int)this + 0x758),
                 *(undefined4 *)((int)this + 0x768),*(undefined4 *)((int)this + 0x76c),
                 *(undefined4 *)((int)this + 0x770));
      _AIL_unlock_0();
      _AIL_lock_0();
      iVar8 = _AIL_3D_room_type_4(*(undefined4 *)((int)this + 0x13c));
      _AIL_unlock_0();
      if (iVar8 != -1) {
        *(uint *)(param_1 + 0x110) = *(uint *)(param_1 + 0x110) | 1;
        *(undefined4 *)((int)this + 0x7ec) = 1;
      }
    }
    if (local_34 == 0) {
      iVar8 = *(int *)((int)this + 0x2b0);
      if (iVar8 != (int)this + 0x2ac) {
        do {
          piVar1 = *(int **)(iVar8 + 8);
          iVar8 = *(int *)(iVar8 + 4);
          if ((piVar1 != (int *)0x0) && (iVar7 = (**(code **)(*piVar1 + 0x14))(), iVar7 != 0)) {
            FUN_004978e0(this,piVar1);
          }
        } while (iVar8 != (int)this + 0x2ac);
      }
      uVar11 = 0;
      if (*(int *)((int)this + 0x724) != 0) {
        puVar10 = (undefined4 *)((int)this + 0x324);
        do {
          piVar1 = (int *)*puVar10;
          if ((piVar1 != (int *)0x0) &&
             (bVar3 = FUN_00494ef0(piVar1), CONCAT31(extraout_var,bVar3) != 0)) {
            FUN_00497990(this,piVar1);
            uVar11 = uVar11 - 1;
            puVar10 = puVar10 + -1;
          }
          uVar11 = uVar11 + 1;
          puVar10 = puVar10 + 1;
        } while (uVar11 < *(uint *)((int)this + 0x724));
      }
    }
    else {
      FUN_004b7c10((int)this + 0x288);
      FUN_004b7be0((uint *)((int)this + 0x288),0xa4,0x20,0x20);
      iVar8 = (int)this + 0x2ac;
      *(int *)((int)this + 0x2b0) = iVar8;
      *(int *)iVar8 = iVar8;
      *(undefined4 *)((int)this + 0x2a8) = 0;
      FUN_004b7c10((int)this + 700);
      FUN_004b7be0((uint *)((int)this + 700),0xc4,0x10,0x10);
      FUN_004b7c10((int)this + 0x2e0);
      FUN_004b7be0((uint *)((int)this + 0x2e0),0xc4,0x10,0x10);
      FUN_004b7c10((int)this + 0x304);
      FUN_004b7be0((uint *)((int)this + 0x304),0xdc,0x20,0x20);
      puVar10 = (undefined4 *)((int)this + 0x324);
      for (iVar8 = 0x100; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar10 = 0;
        puVar10 = puVar10 + 1;
      }
      *(undefined4 *)((int)this + 0x724) = 0;
    }
    *(undefined1 *)((int)this + 0x77c) = 0;
    if (_DAT_004cb524 < *(float *)(param_1 + 0x118)) {
      *(undefined4 *)((int)this + 0x778) = *(undefined4 *)(param_1 + 0x118);
    }
    uVar4 = *(ushort *)(param_1 + 0x114);
    if (99 < uVar4) {
      uVar4 = 100;
    }
    *(ushort *)(param_1 + 0x114) = uVar4;
    (**(code **)(*(int *)this + 0x28))(uVar4 & 0xff);
    if ((*(int *)((int)this + 0x7e8) != 0) || (*(int *)((int)this + 0x7ec) != 0)) {
      local_1c = 0x1f;
      uStack_1a = 0;
      uStack_18 = 0;
      uStack_14 = 0;
      uStack_10 = 0;
      uStack_c = 0x3dcccccd;
      uStack_8 = 0x3f7d70a4;
      (**(code **)(*(int *)this + 0x34))(&local_1c);
    }
    *(undefined2 *)((int)this + 0x7b4) = 1;
    *(undefined2 *)((int)this + 0x7b6) = 0x44c;
    *(undefined2 *)((int)this + 0x7b8) = 1;
    *(undefined2 *)((int)this + 0x7ba) = 1;
    *(undefined4 *)((int)this + 0x7c0) = 0;
    *(int *)((int)this + 0x790) = (int)this + 0x780;
    if (*(uint *)((int)this + 0x7d8) < 0x44c) {
      if (*(int *)((int)this + 0x7d4) != 0) {
        FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x7d4));
        *(undefined4 *)((int)this + 0x7d4) = 0;
        *(undefined4 *)((int)this + 0x7dc) = 0;
      }
      *(undefined4 *)((int)this + 0x7d8) = 0;
      FUN_0040c870((void *)((int)this + 2000),0,&DAT_004ecc58);
      *(undefined4 *)((int)this + 0x7d4) = 0;
      *(undefined4 *)((int)this + 0x7d8) = 0;
      *(undefined4 *)((int)this + 0x7e0) = 0x44c;
      *(undefined4 *)((int)this + 0x7dc) = 0;
      if (*(int *)((int)this + 0x7d8) != 0x44c) {
        if (*(int *)((int)this + 0x7d4) != 0) {
          FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x7d4));
          *(undefined4 *)((int)this + 0x7d4) = 0;
          *(undefined4 *)((int)this + 0x7dc) = 0;
        }
        *(undefined4 *)((int)this + 0x7d8) = 0x44c;
        iVar8 = FUN_0040c920(&DAT_004ecc58,0,*(int *)((int)this + 0x7e0) + 0x44c);
        *(int *)((int)this + 0x7d4) = iVar8;
        if (iVar8 == 0) {
          *(undefined4 *)((int)this + 0x7d8) = 0;
          *(undefined4 *)((int)this + 0x7dc) = 0;
        }
        else {
          *(undefined4 *)((int)this + 0x7dc) = *(undefined4 *)((int)this + 0x7e0);
        }
      }
    }
    else {
      *(undefined4 *)((int)this + 0x7e0) = 0x44c;
    }
    *(undefined1 *)((int)this + 0x810) = 100;
    _AIL_lock_0();
    uVar6 = _AIL_ms_count_0();
    *(undefined4 *)((int)this + 0x804) = uVar6;
    _AIL_unlock_0();
    *(undefined4 *)((int)this + 0x808) = 0;
    *(undefined4 *)((int)this + 0x80c) = 0;
  }
  return 0;
}


/* 00496fe0 size=34 */

void FUN_00496fe0(undefined *param_1)

{
  undefined *puVar1;
  
  while (param_1 != (undefined *)0x0) {
    puVar1 = *(undefined **)(param_1 + 0x114);
    FUN_00430df0(param_1);
    param_1 = puVar1;
  }
  return;
}


/* 00497310 size=194 */

undefined4 __thiscall FUN_00497310(void *this,byte *param_1)

{
  int *piVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  int *piVar5;
  byte *pbVar6;
  int *piVar7;
  bool bVar8;
  
  if (*(int *)((int)this + 0x124) == 0) {
    return 1;
  }
  piVar5 = *(int **)((int)this + 300);
  piVar1 = (int *)((int)this + 0x13c);
  *piVar1 = 0;
  do {
    if (piVar5 == (int *)0x0) goto LAB_00497389;
    pbVar3 = (byte *)(piVar5 + 2);
    pbVar6 = param_1;
    do {
      bVar2 = *pbVar3;
      bVar8 = bVar2 < *pbVar6;
      if (bVar2 != *pbVar6) {
LAB_0049736b:
        iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
        goto LAB_00497370;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar3[1];
      bVar8 = bVar2 < pbVar6[1];
      if (bVar2 != pbVar6[1]) goto LAB_0049736b;
      pbVar3 = pbVar3 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar2 != 0);
    iVar4 = 0;
LAB_00497370:
    if (iVar4 == 0) {
      piVar7 = piVar1;
      for (iVar4 = 0x46; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar7 = *piVar5;
        piVar5 = piVar5 + 1;
        piVar7 = piVar7 + 1;
      }
LAB_00497389:
      if (*piVar1 == 0) {
        return 1;
      }
      _AIL_lock_0();
      iVar4 = _AIL_open_3D_provider_4(*piVar1);
      if (iVar4 == 0) {
        _AIL_unlock_0();
        return 0;
      }
      _AIL_unlock_0();
      *piVar1 = 0;
      return 1;
    }
    piVar5 = (int *)piVar5[0x45];
  } while( true );
}


/* 004973e0 size=329 */

undefined4 __fastcall FUN_004973e0(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  byte bVar6;
  uint local_4;
  
  if (*(int *)(param_1 + 0x124) == 0) {
    return 1;
  }
  iVar4 = param_1 + 0x260;
  *(int *)(param_1 + 0x264) = iVar4;
  *(int *)iVar4 = iVar4;
  *(undefined4 *)(param_1 + 0x25c) = 0;
  if (*(int *)(param_1 + 0x13c) == 0) {
    return 1;
  }
  if (*(int *)(param_1 + 600) != 0) {
    FUN_00497530(param_1);
    *(undefined4 *)(param_1 + 600) = 0;
  }
  if (*(byte *)(param_1 + 0x255) != 0) {
    iVar4 = FUN_00430de0((uint)*(byte *)(param_1 + 0x255) << 4);
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    *(int *)(param_1 + 600) = iVar4;
    _AIL_lock_0();
    bVar6 = 0;
    local_4 = 0;
    if (*(char *)(param_1 + 0x255) != '\0') {
      do {
        iVar4 = local_4 * 0x10;
        uVar5 = _AIL_allocate_3D_sample_handle_4(*(undefined4 *)(param_1 + 0x13c));
        *(undefined4 *)(*(int *)(param_1 + 600) + iVar4) = uVar5;
        iVar2 = *(int *)(*(int *)(param_1 + 600) + iVar4);
        if (iVar2 == 0) break;
        _AIL_set_3D_user_data_12(iVar2,1,1);
        _AIL_set_3D_user_data_12
                  (*(undefined4 *)(*(int *)(param_1 + 600) + iVar4),2,
                   *(int *)(param_1 + 600) + iVar4);
        iVar4 = *(int *)(param_1 + 600) + iVar4;
        *(int *)(iVar4 + 0xc) = iVar4;
        piVar1 = (int *)(iVar4 + 4);
        *piVar1 = param_1 + 0x260;
        piVar3 = *(int **)(param_1 + 0x264);
        *(int **)(iVar4 + 8) = piVar3;
        *piVar3 = (int)piVar1;
        *(int **)(*piVar1 + 4) = piVar1;
        bVar6 = bVar6 + 1;
        *(int *)(param_1 + 0x25c) = *(int *)(param_1 + 0x25c) + 1;
        local_4 = (uint)bVar6;
      } while (bVar6 < *(byte *)(param_1 + 0x255));
    }
    _AIL_unlock_0();
    *(byte *)(param_1 + 0x254) = bVar6;
  }
  return 0;
}


/* 00497530 size=190 */

undefined4 __fastcall FUN_00497530(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0x13c) == 0) {
    return 1;
  }
  if ((*(int *)(param_1 + 600) != 0) && (cVar1 = *(char *)(param_1 + 0x254), cVar1 != '\0')) {
    if (cVar1 != '\0') {
      iVar4 = (uint)(byte)(cVar1 - 1) << 4;
      iVar3 = (byte)(cVar1 - 1) + 1;
      do {
        piVar2 = (int *)FUN_00498770(*(int *)(iVar4 + *(int *)(param_1 + 600)));
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 0x1c))(1);
        }
        _AIL_lock_0();
        _AIL_release_3D_sample_handle_4(*(undefined4 *)(iVar4 + *(int *)(param_1 + 600)));
        _AIL_unlock_0();
        iVar3 = iVar3 + -1;
        iVar4 = iVar4 + -0x10;
      } while (iVar3 != 0);
    }
    FUN_00430df0(*(undefined **)(param_1 + 600));
    *(undefined4 *)(param_1 + 600) = 0;
    *(undefined1 *)(param_1 + 0x254) = 0;
  }
  return 0;
}


/* 004975f0 size=329 */

undefined4 __fastcall FUN_004975f0(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  byte bVar6;
  uint local_4;
  
  if (*(int *)(param_1 + 0x124) == 0) {
    return 1;
  }
  iVar4 = param_1 + 0x278;
  *(int *)(param_1 + 0x27c) = iVar4;
  *(int *)iVar4 = iVar4;
  *(undefined4 *)(param_1 + 0x274) = 0;
  if (*(int *)(param_1 + 0x130) == 0) {
    return 1;
  }
  if (*(int *)(param_1 + 0x270) != 0) {
    FUN_00497740(param_1);
    *(undefined4 *)(param_1 + 0x270) = 0;
  }
  if (*(byte *)(param_1 + 0x26d) != 0) {
    iVar4 = FUN_00430de0((uint)*(byte *)(param_1 + 0x26d) << 4);
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    *(int *)(param_1 + 0x270) = iVar4;
    _AIL_lock_0();
    bVar6 = 0;
    local_4 = 0;
    if (*(char *)(param_1 + 0x26d) != '\0') {
      do {
        iVar4 = local_4 * 0x10;
        uVar5 = _AIL_allocate_sample_handle_4(*(undefined4 *)(param_1 + 0x130));
        *(undefined4 *)(*(int *)(param_1 + 0x270) + iVar4) = uVar5;
        iVar2 = *(int *)(*(int *)(param_1 + 0x270) + iVar4);
        if (iVar2 == 0) break;
        _AIL_set_sample_user_data_12(iVar2,1,0);
        _AIL_set_sample_user_data_12
                  (*(undefined4 *)(*(int *)(param_1 + 0x270) + iVar4),2,
                   *(int *)(param_1 + 0x270) + iVar4);
        iVar4 = *(int *)(param_1 + 0x270) + iVar4;
        *(int *)(iVar4 + 0xc) = iVar4;
        piVar1 = (int *)(iVar4 + 4);
        *piVar1 = param_1 + 0x278;
        piVar3 = *(int **)(param_1 + 0x27c);
        *(int **)(iVar4 + 8) = piVar3;
        *piVar3 = (int)piVar1;
        *(int **)(*piVar1 + 4) = piVar1;
        bVar6 = bVar6 + 1;
        *(int *)(param_1 + 0x274) = *(int *)(param_1 + 0x274) + 1;
        local_4 = (uint)bVar6;
      } while (bVar6 < *(byte *)(param_1 + 0x26d));
    }
    _AIL_unlock_0();
    *(byte *)(param_1 + 0x26c) = bVar6;
  }
  return 0;
}


/* 00497740 size=190 */

undefined4 __fastcall FUN_00497740(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0x130) == 0) {
    return 1;
  }
  if ((*(int *)(param_1 + 0x270) != 0) && (cVar1 = *(char *)(param_1 + 0x26c), cVar1 != '\0')) {
    if (cVar1 != '\0') {
      iVar4 = (uint)(byte)(cVar1 - 1) << 4;
      iVar3 = (byte)(cVar1 - 1) + 1;
      do {
        piVar2 = (int *)FUN_00498700(*(int *)(iVar4 + *(int *)(param_1 + 0x270)));
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 0x1c))(1);
        }
        _AIL_lock_0();
        _AIL_release_sample_handle_4(*(undefined4 *)(iVar4 + *(int *)(param_1 + 0x270)));
        _AIL_unlock_0();
        iVar3 = iVar3 + -1;
        iVar4 = iVar4 + -0x10;
      } while (iVar3 != 0);
    }
    FUN_00430df0(*(undefined **)(param_1 + 0x270));
    *(undefined4 *)(param_1 + 0x270) = 0;
    *(undefined1 *)(param_1 + 0x26c) = 0;
  }
  return 0;
}


/* 00497800 size=217 */

int * __thiscall FUN_00497800(void *this,int *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  if (*(int *)((int)this + 0x124) == 0) {
    return (int *)0x0;
  }
  piVar4 = (int *)*param_1;
  if (piVar4 != (int *)0x0) {
    if (((char)param_1[6] == '\x04') || ((char)param_1[6] == -1)) {
      piVar4[0x10] = 1;
      return piVar4;
    }
    return (int *)0x0;
  }
  piVar4 = *(int **)((int)this + 0x2a0);
  if (piVar4 == (int *)0x0) {
    FUN_004b7c60((int)this + 0x288,*(int *)((int)this + 0x290));
    piVar4 = *(int **)((int)this + 0x2a0);
    if (piVar4 == (int *)0x0) {
      return (int *)0x0;
    }
  }
  *(int *)((int)this + 0x2a0) = *piVar4;
  if (piVar4 != (int *)0x0) {
    FUN_00493020(piVar4);
    iVar3 = (**(code **)(*piVar4 + 4))(param_1);
    if (iVar3 == 0) {
      iVar3 = *(int *)((int)this + 0x2ac);
      piVar1 = piVar4 + 0x26;
      piVar4[0x28] = (int)piVar4;
      *piVar1 = iVar3;
      piVar2 = *(int **)(iVar3 + 4);
      piVar4[0x27] = (int)piVar2;
      *piVar2 = (int)piVar1;
      *(int **)(*piVar1 + 4) = piVar1;
      *(int *)((int)this + 0x2a8) = *(int *)((int)this + 0x2a8) + 1;
      return piVar4;
    }
    (**(code **)*piVar4)(0);
    if ((int)this + 0x288 != 0) {
      *piVar4 = *(int *)((int)this + 0x2a0);
      *(int **)((int)this + 0x2a0) = piVar4;
    }
  }
  return (int *)0x0;
}


/* 004978e0 size=170 */

undefined4 __thiscall FUN_004978e0(void *this,undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar2 = param_1 + 0x26;
  *(undefined4 *)(param_1[0x26] + 4) = param_1[0x27];
  *(undefined4 *)param_1[0x27] = *puVar2;
  param_1[0x27] = puVar2;
  *puVar2 = puVar2;
  *(int *)((int)this + 0x2a8) = *(int *)((int)this + 0x2a8) + -1;
  if (((*(byte *)(param_1 + 10) & 1) == 0) &&
     (iVar3 = *(int *)((int)this + 0x264), iVar3 != (int)this + 0x260)) {
    do {
      piVar1 = *(int **)(iVar3 + 8);
      iVar3 = *(int *)(iVar3 + 4);
      if ((piVar1 != (int *)0x0) &&
         ((*piVar1 != 0 &&
          (puVar2 = (undefined4 *)_AIL_3D_user_data_8(*piVar1,3), puVar2 == param_1)))) {
        _AIL_set_3D_user_data_12(*piVar1,3,0);
      }
    } while (iVar3 != (int)this + 0x260);
  }
  (**(code **)*param_1)(0);
  if ((param_1 != (undefined4 *)0x0) && (this != (void *)0xfffffd78)) {
    *param_1 = *(undefined4 *)((int)this + 0x2a0);
    *(undefined4 **)((int)this + 0x2a0) = param_1;
  }
  return 0;
}


/* 00497990 size=196 */

undefined4 __thiscall FUN_00497990(void *this,int *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = param_1[1];
  uVar1 = param_1[0x18];
  uVar2 = *(uint *)((int)this + 0x724);
  if ((1 < uVar2) && (uVar1 < uVar2 - 1)) {
    iVar3 = *(int *)((int)this + uVar2 * 4 + 800);
    *(int *)((int)this + uVar1 * 4 + 0x324) = iVar3;
    *(uint *)(iVar3 + 0x60) = uVar1;
  }
  if (*(int *)((int)this + 0x724) != 0) {
    *(undefined4 *)((int)this + *(int *)((int)this + 0x724) * 4 + 800) = 0;
    *(int *)((int)this + 0x724) = *(int *)((int)this + 0x724) + -1;
  }
  (**(code **)(*param_1 + 8))();
  if (iVar4 == 0) {
    (**(code **)*param_1)(0);
    iVar4 = (int)this + 700;
  }
  else {
    if (iVar4 != 1) {
      if (iVar4 != 2) {
        return 0;
      }
      (**(code **)*param_1)(0);
      if (param_1 == (int *)0x0) {
        return 0;
      }
      if (this == (void *)0xfffffcfc) {
        return 0;
      }
      *param_1 = *(int *)((int)this + 0x31c);
      *(int **)((int)this + 0x31c) = param_1;
      return 0;
    }
    (**(code **)*param_1)(0);
    iVar4 = (int)this + 0x2e0;
  }
  if ((param_1 == (int *)0x0) || (iVar4 == 0)) {
    return 0;
  }
  *param_1 = *(int *)(iVar4 + 0x18);
  *(int **)(iVar4 + 0x18) = param_1;
  return 0;
}


/* 00497a60 size=61 */

undefined4 __fastcall FUN_00497a60(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 0x724) == 0) {
    return 0;
  }
  piVar1 = (int *)(param_1 + 0x324);
  do {
    if ((int *)*piVar1 != (int *)0x0) {
      (**(code **)(*(int *)*piVar1 + 0x18))(1);
    }
    uVar2 = uVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (uVar2 < *(uint *)(param_1 + 0x724));
  return 0;
}


/* 00497aa0 size=96 */

int __thiscall FUN_00497aa0(void *this,int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  if (param_2 == 0) {
    if (param_1 != 0xffff) {
      uVar3 = 0;
      if (*(uint *)((int)this + 0x724) != 0) {
        piVar2 = (int *)((int)this + 0x324);
        do {
          iVar1 = *piVar2;
          if (((iVar1 != 0) && (*(int *)(iVar1 + 0x14) == param_1)) &&
             ((*(uint *)(iVar1 + 0x10) & 0x200) == 0)) {
            return iVar1;
          }
          uVar3 = uVar3 + 1;
          piVar2 = piVar2 + 1;
        } while (uVar3 < *(uint *)((int)this + 0x724));
      }
    }
  }
  else if ((param_1 != 0) && ((*(uint *)(param_1 + 0x10) & 0x200) != 0)) {
    return param_1;
  }
  return 0;
}


/* 00497b00 size=1931 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00497b00(int *param_1)

{
  float *pfVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  float10 fVar9;
  undefined1 uStack_41;
  uint uStack_40;
  int *piStack_3c;
  int *local_38;
  undefined4 uStack_34;
  float local_30;
  uint local_2c;
  uint local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  uVar6 = 0;
  if ((param_1[0x49] == 0) || (param_1[0x4a] == 0)) {
    return 1;
  }
  if ((param_1[0x4d] != 0) && (param_1[0x4e] != 0)) {
    clientmgr_498ca0(param_1);
  }
  *(undefined2 *)(param_1 + 0x1ee) = 1;
  *(undefined2 *)(param_1 + 0x1ed) = 1;
  _AIL_lock_0();
  uVar3 = _AIL_ms_count_0();
  local_28 = uVar3;
  _AIL_unlock_0();
  uVar7 = uVar3 - param_1[0x201];
  if ((uint)param_1[0x202] < uVar3) {
    param_1[0x203] = 1;
    param_1[0x202] = uVar3 + 100;
  }
  local_2c = uVar7;
  if (param_1[0x1dd] != 0) {
    if ((*(int *)(DAT_004e516c + 0x161c) == 0) ||
       (iVar4 = *(int *)(*(int *)(DAT_004e516c + 0x161c) + 0x88), iVar4 == 0)) {
      param_1[0x1cb] = 0;
      param_1[0x1cc] = 0;
      param_1[0x1cd] = 0;
      param_1[0x1d7] = 0x3f800000;
      param_1[0x1d8] = 0;
      param_1[0x1d9] = 0;
      param_1[0x1da] = 0;
      param_1[0x1db] = 0x3f800000;
      param_1[0x1dc] = 0;
      param_1[0x1d4] = 0;
      param_1[0x1d5] = 0;
      param_1[0x1d6] = 0x3f800000;
    }
    else {
      param_1[0x1cb] = *(int *)(iVar4 + 0x194);
      param_1[0x1cc] = *(int *)(iVar4 + 0x198);
      param_1[0x1cd] = *(int *)(iVar4 + 0x19c);
      FUN_0044e9d0((float *)(iVar4 + 0x9c),(float *)(param_1 + 0x1d7),param_1 + 0x1da,
                   param_1 + 0x1d4);
    }
  }
  if (uVar7 == 0) {
    param_1[0x1d1] = 0;
    param_1[0x1d2] = 0;
    param_1[0x1d3] = 0;
  }
  else {
    local_24 = (float)param_1[0x1cb] - (float)param_1[0x1ce];
    local_20 = (float)param_1[0x1cc] - (float)param_1[0x1cf];
    local_30 = (float)param_1[0x1d0];
    uStack_34 = 0;
    local_1c = (float)param_1[0x1cd] - local_30;
    pfVar1 = (float *)(param_1 + 0x1d1);
    *pfVar1 = local_24;
    fVar2 = (float)param_1[0x1de] / (float)uVar7;
    param_1[0x1d2] = (int)local_20;
    param_1[0x1d3] = (int)local_1c;
    *pfVar1 = fVar2 * *pfVar1;
    param_1[0x1d2] = (int)(fVar2 * (float)param_1[0x1d2]);
    param_1[0x1d3] = (int)(fVar2 * (float)param_1[0x1d3]);
    local_38 = (int *)uVar7;
  }
  param_1[0x1ce] = param_1[0x1cb];
  param_1[0x1cf] = param_1[0x1cc];
  param_1[0x1d0] = param_1[0x1cd];
  if ((param_1[0x1ca] == 0) || (param_1[0x203] == 0)) goto LAB_00497e43;
  _AIL_lock_0();
  _AIL_3D_orientation_28(param_1[0x1ca],&local_18,&local_14,&local_10,&local_c,&local_8,&local_4);
  local_24 = (float)param_1[0x1d4];
  local_20 = (float)param_1[0x1d5];
  local_1c = (float)param_1[0x1d6];
  FUN_00413050(&local_24,local_18 - local_24,local_14 - local_20,local_10 - local_1c);
  fVar9 = FUN_0043a41f(&local_24);
  if ((float10)_DAT_004cbaec < fVar9) {
LAB_00497e0a:
    _AIL_set_3D_orientation_28
              (param_1[0x1ca],param_1[0x1d4],param_1[0x1d5],param_1[0x1d6],param_1[0x1da],
               param_1[0x1db],param_1[0x1dc]);
  }
  else {
    local_24 = (float)param_1[0x1da];
    local_20 = (float)param_1[0x1db];
    local_1c = (float)param_1[0x1dc];
    FUN_00413050(&local_24,local_c - local_24,local_8 - local_20,local_4 - local_1c);
    fVar9 = FUN_0043a41f(&local_24);
    if ((float10)_DAT_004cbaec < fVar9) goto LAB_00497e0a;
  }
  _AIL_unlock_0();
LAB_00497e43:
  *(undefined1 *)(param_1 + 0x1df) = 0;
  if (param_1[0x1c9] == 0) {
    return 0;
  }
  piVar5 = param_1 + 0xc9;
  do {
    piVar8 = (int *)*piVar5;
    if (((piVar8 != (int *)0x0) && ((*(byte *)(piVar8 + 0x12) & 4) == 0)) &&
       ((**(code **)(*piVar8 + 0x14))(param_1 + 0x1cb), (*(byte *)(piVar8 + 0x12) & 0x10) == 0)) {
      (**(code **)(*piVar8 + 0x1c))(0);
    }
    uVar6 = uVar6 + 1;
    piVar5 = piVar5 + 1;
  } while (uVar6 < (uint)param_1[0x1c9]);
  if ((undefined4 *)0x1 < (undefined4 *)param_1[0x1c9]) {
    piVar5 = param_1 + 0xc9;
    FUN_004bc5d2(piVar5,(undefined4 *)param_1[0x1c9],4,&LAB_00498290);
    uVar6 = 0;
    if (param_1[0x1c9] != 0) {
      do {
        if (*piVar5 == 0) {
          param_1[0x1c9] = uVar6;
          break;
        }
        *(uint *)(*piVar5 + 0x60) = uVar6;
        uVar6 = uVar6 + 1;
        piVar5 = piVar5 + 1;
      } while (uVar6 < (uint)param_1[0x1c9]);
    }
  }
  uStack_40 = 0;
  if (param_1[0x1c9] != 0) {
    local_38 = param_1 + 0xc9;
    do {
      uVar6 = uStack_40;
      piVar5 = (int *)*local_38;
      if ((((((piVar5[0x12] & 4U) == 0) && ((piVar5[0x12] & 0x10U) != 0)) &&
           ((piVar5[0x13] == 0 && ((piVar5[0x14] == 0 && (piVar5[0x15] == 0)))))) &&
          ((void *)piVar5[2] != (void *)0x0)) &&
         (((uint)piVar5[9] <= (uint)piVar5[0xb] &&
          (iVar4 = FUN_00493bd0((void *)piVar5[2],(int)piVar5), iVar4 != 0)))) {
        if ((*(byte *)(piVar5[2] + 0x28) & 1) == 0) {
          if ((*(char *)((int)param_1 + 0x255) == '\0') ||
             (((piVar5[1] != 2 && ((param_1[0x1fb] == 0 || ((piVar5[4] & 0x100U) == 0)))) ||
              (iVar4 = (**(code **)(*piVar5 + 0x50))(), iVar4 != 0)))) {
            iVar4 = FUN_004944c0(piVar5);
          }
          else {
            iVar4 = (**(code **)(*piVar5 + 0xc))();
          }
          if (iVar4 != 0) {
            uVar3 = param_1[0x1c9] - 1;
            if (uVar6 < uVar3) {
              piStack_3c = param_1 + param_1[0x1c9] + 200;
              do {
                piVar8 = (int *)*piStack_3c;
                if (((*(char *)((int)param_1 + 0x255) == '\0') ||
                    ((piVar5[1] != 2 && ((param_1[0x1fb] == 0 || ((piVar5[4] & 0x100U) == 0)))))) ||
                   (iVar4 = (**(code **)(*piVar5 + 0x50))(), iVar4 != 0)) {
                  if (piVar8[0x13] != 0) {
                    (**(code **)(*piVar8 + 0x1c))(0);
                    FUN_004944c0(piVar5);
                    break;
                  }
                }
                else if (((piVar8[0x14] != 0) && (piVar5[1] == 2)) &&
                        ((*(byte *)(piVar5[2] + 0x28) & 1) == 0)) {
                  (**(code **)(*piVar8 + 0x1c))(0);
                  (**(code **)(*piVar5 + 0xc))();
                  break;
                }
                uVar3 = uVar3 - 1;
                piStack_3c = piStack_3c + -1;
              } while (uStack_40 < uVar3);
            }
          }
        }
        else {
          FUN_00494880((int)piVar5);
        }
      }
      uStack_40 = uStack_40 + 1;
      local_38 = local_38 + 1;
    } while (uStack_40 < (uint)param_1[0x1c9]);
  }
  uStack_40 = 0;
  if (param_1[0x1c9] != 0) {
    local_38 = param_1 + 0xc9;
    do {
      piVar8 = local_38;
      piVar5 = (int *)*local_38;
      if (((piVar5[0x14] != 0) || (piVar5[0x13] != 0)) || (piVar5[0x15] != 0)) {
        *(char *)(param_1 + 0x1df) = (char)param_1[0x1df] + '\x01';
        (**(code **)(*piVar5 + 0x10))(local_2c);
      }
      iVar4 = FUN_00494330(piVar5,local_2c);
      if (iVar4 == 0) {
        (**(code **)(*piVar5 + 0x18))(0);
        if (((*(byte *)(piVar5 + 0x12) & 0xc0) == 0) && (uVar6 = piVar5[4], (uVar6 & 0x438) != 0)) {
          if (((uVar6 & 0x200) == 0) &&
             ((((uVar6 & 0x428) != 0 && ((uVar6 & 4) == 0)) && (iVar4 = piVar5[5], iVar4 != 0xffff))
             )) {
            if (*(ushort *)(param_1 + 0x1ee) + 2 < (uint)*(ushort *)((int)param_1 + 0x7b6)) {
              if ((uint)param_1[0x1f6] <= *(ushort *)(param_1 + 0x1ed) + 2) {
                do {
                  uStack_41 = 0;
                  FUN_00414b10(param_1 + 500,(undefined1 *)param_1[0x1f6],&uStack_41,&DAT_004ecc58);
                } while ((uint)param_1[0x1f6] <= *(ushort *)(param_1 + 0x1ed) + 2);
                piVar8 = local_38;
              }
              *(short *)(param_1[0x1f5] + (uint)*(ushort *)(param_1 + 0x1ee)) = (short)iVar4;
              *(short *)(param_1 + 0x1ee) = (short)param_1[0x1ee] + 2;
              *(short *)(param_1 + 0x1ed) = (short)param_1[0x1ed] + 2;
              piVar5[4] = piVar5[4] & 0xfffffbd7;
            }
            else {
              FUN_004356e0();
              if (0 < DAT_004e4420) {
                FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                             s_CPacket__WriteType_004d5cf0);
              }
              param_1[0x1f0] = param_1[0x1f0] | 4;
              piVar5[4] = piVar5[4] & 0xfffffbd7;
            }
          }
        }
        else {
          FUN_00497990(param_1,piVar5);
          uStack_40 = uStack_40 - 1;
          piVar8 = piVar8 + -1;
        }
      }
      uStack_40 = uStack_40 + 1;
      local_38 = piVar8 + 1;
    } while (uStack_40 < (uint)param_1[0x1c9]);
  }
  param_1[0x203] = 0;
  param_1[0x201] = local_28;
  return 0;
}


