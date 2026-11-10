/* lithtech.exe decompilation - unnamed_00448000 */
#include "ghidra_types.h"

/* 00448030 size=62 */

undefined4 __fastcall FUN_00448030(char *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar2 = 0xffffffff;
  pcVar4 = s_local_004d674c;
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  for (uVar3 = uVar2 >> 2; param_1 = param_1 + 4, uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)param_1 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    param_1 = param_1 + 1;
  }
  return 1;
}


/* 00448070 size=336 */

void __fastcall FUN_00448070(int param_1)

{
  undefined *puVar1;
  int *piVar2;
  undefined *local_8;
  
  puVar1 = *(undefined **)(param_1 + 0x74);
  while (local_8 = puVar1, local_8 != (undefined *)(param_1 + 0x5c)) {
    puVar1 = *(undefined **)(local_8 + 0x18);
    *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0x94) - *(int *)(local_8 + 4);
    if (local_8 != (undefined *)0x0) {
      FUN_00447e70((int)local_8);
      FUN_00430df0(local_8);
    }
  }
  *(int *)(param_1 + 0x74) = param_1 + 0x5c;
  *(int *)(param_1 + 0x8c) = param_1 + 0x78;
  *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  if (*(int *)(param_1 + 0x54) != 0) {
    piVar2 = *(int **)(param_1 + 0x54);
    *(undefined4 *)(param_1 + 0x54) = 0;
    (**(code **)(*piVar2 + 0x70))();
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    puVar1 = *(undefined **)(param_1 + 0x58);
    if (puVar1 != (undefined *)0x0) {
      FUN_004645f0((int)puVar1);
      FUN_00430df0(puVar1);
    }
    *(undefined4 *)(param_1 + 0x58) = 0;
  }
  return;
}


/* 004481c0 size=170 */

void __fastcall FUN_004481c0(int param_1)

{
  undefined *puVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x50) != 0) {
    *(undefined4 *)(param_1 + 0x50) = 0;
    if (DAT_004e98c8 == 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x70) = 1;
    }
    iVar2 = netmgr_465e20(*(void **)(param_1 + 0x48),*(int *)(param_1 + 0x58));
    if (iVar2 == 0) {
      puVar1 = *(undefined **)(param_1 + 0x58);
      if (puVar1 != (undefined *)0x0) {
        FUN_004645f0((int)puVar1);
        FUN_00430df0(puVar1);
      }
      *(undefined4 *)(param_1 + 0x58) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
  }
  return;
}


/* 00448270 size=51 */

void __thiscall FUN_00448270(void *this,int *param_1)

{
  (**(code **)(*param_1 + 0x6c))(this);
  (**(code **)(*(int *)this + 0x74))(param_1);
  return;
}


/* 004482f0 size=56 */

bool __thiscall FUN_004482f0(void *this,undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = *(int *)((int)this + 0x54) != 0;
  if (bVar1) {
    (**(code **)(**(int **)((int)this + 0x54) + 0x78))(param_1,param_2);
  }
  return bVar1;
}


/* 00448330 size=200 */

undefined4 __thiscall FUN_00448330(void *this,int param_1)

{
  uint *puVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  puVar1 = *(uint **)((int)this + 0x8c);
  if (((*(int *)((int)this + 0x58) == 0) || (puVar1 == (uint *)((int)this + 0x78))) ||
     (*(int *)((int)this + 0x50) != 0)) {
    uVar2 = 0;
  }
  else {
    uVar4 = puVar1[2];
    puVar5 = (undefined4 *)puVar1[3];
    puVar6 = *(undefined4 **)(param_1 + 0x54);
    for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    *(short *)(param_1 + 0x34) = (short)puVar1[2];
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)((int)this + 0x58);
    *(uint *)(puVar1[4] + 0x14) = puVar1[5];
    *(uint *)(puVar1[5] + 0x10) = puVar1[4];
    *puVar1 = *puVar1 & 0xfffffffe;
    *(int *)((int)this + 0x98) = *(int *)((int)this + 0x98) + -1;
    uVar2 = 1;
  }
  return uVar2;
}


/* 00448400 size=28 */

void __thiscall FUN_00448400(void *this,undefined4 param_1)

{
  (**(code **)(*(int *)this + 0x74))(param_1);
  return;
}


/* 00448420 size=40 */

void __fastcall FUN_00448420(int *param_1)

{
  if (param_1[0x16] != 0) {
    (**(code **)(*param_1 + 0x5c))(param_1[0x16],1);
  }
  return;
}


/* 00448450 size=106 */

void __thiscall FUN_00448450(void *this,undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *local_10;
  
  if (*(int *)((int)this + 0x54) == 0) {
    puVar1 = (undefined4 *)FUN_00430de0(0xbc);
    if (puVar1 == (undefined4 *)0x0) {
      local_10 = (undefined4 *)0x0;
    }
    else {
      local_10 = FUN_00464580(puVar1);
    }
    *(undefined4 **)((int)this + 0x58) = local_10;
    *(void **)(*(int *)((int)this + 0x58) + 0x30) = this;
    *(undefined4 *)((int)this + 0x54) = param_1;
    *(undefined4 *)((int)this + 0x50) = 1;
  }
  return;
}


/* 004484c0 size=424 */

void __thiscall FUN_004484c0(void *this,undefined4 *param_1,size_t param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  uint *local_20;
  uint *local_c;
  uint *local_8;
  
  local_c = *(uint **)((int)this + 0x74);
  local_8 = (uint *)0x0;
  do {
    if (local_c == (uint *)((int)this + 0x5c)) {
LAB_00448510:
      if (local_8 == (uint *)0x0) {
        puVar1 = (undefined4 *)FUN_00430de0(0x1c);
        if (puVar1 == (undefined4 *)0x0) {
          local_20 = (uint *)0x0;
        }
        else {
          local_20 = FUN_00447e40(puVar1);
        }
        local_8 = local_20;
        puVar4 = local_20;
        for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        local_20[1] = param_2;
        uVar2 = FUN_00430de0(param_2);
        local_20[3] = uVar2;
        *(int *)((int)this + 0x9c) = *(int *)((int)this + 0x9c) + 1;
        *(size_t *)((int)this + 0x94) = *(int *)((int)this + 0x94) + param_2;
        for (local_c = (uint *)((int)this + 0x5c);
            (*(int *)(*(int *)((int)local_c + 0x18) + 4) < (int)param_2 &&
            (*(int *)((int)local_c + 0x18) != (int)this + 0x5c));
            local_c = *(uint **)((int)local_c + 0x18)) {
        }
        local_20[6] = *(uint *)((int)local_c + 0x18);
        *(uint **)((int)local_c + 0x18) = local_20;
      }
      puVar1 = (undefined4 *)local_8[3];
      for (uVar2 = param_2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar1 = *param_1;
        param_1 = param_1 + 1;
        puVar1 = puVar1 + 1;
      }
      for (uVar2 = param_2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar1 = *(undefined1 *)param_1;
        param_1 = (undefined4 *)((int)param_1 + 1);
        puVar1 = (undefined4 *)((int)puVar1 + 1);
      }
      local_8[2] = param_2;
      uVar2 = *(uint *)((int)this + 0x88);
      local_8[5] = *(uint *)(uVar2 + 0x14);
      local_8[4] = uVar2;
      *(uint **)(uVar2 + 0x14) = local_8;
      *(uint **)(local_8[5] + 0x10) = local_8;
      *local_8 = *local_8 | 1;
      *(int *)((int)this + 0x98) = *(int *)((int)this + 0x98) + 1;
      return;
    }
    if (((*local_c & 3) == 0) && ((int)param_2 <= (int)local_c[1])) {
      local_8 = local_c;
      goto LAB_00448510;
    }
    local_c = (uint *)local_c[6];
  } while( true );
}


/* 00448670 size=39 */

undefined4 * __cdecl FUN_00448670(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00430de0(0x10);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  *puVar1 = &PTR_FUN_004cc644;
  puVar1[3] = param_1;
  puVar1[2] = 0;
  puVar1[1] = 0;
  return puVar1;
}


/* 004486a0 size=53 */

undefined4 FUN_004486a0(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    do {
      iVar1 = ShowCursor(0);
    } while (-1 < iVar1);
  }
  else if (param_1 == 1) {
    do {
      iVar1 = ShowCursor(1);
    } while (iVar1 < 0);
    return 0;
  }
  return 0;
}


/* 004486f0 size=62 */

undefined4 __thiscall FUN_004486f0(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*(int *)this + 8))(param_1);
  if (iVar1 == 0) {
    return 0x53;
  }
  if (param_1 != *(int *)((int)this + 4)) {
    FUN_004486a0(param_1);
    *(int *)((int)this + 4) = param_1;
    ClientUtilities_4486e0();
  }
  return 0;
}


/* 00448740 size=44 */

undefined4 FUN_00448740(int *param_1)

{
  int iVar1;
  HCURSOR hCursor;
  
  iVar1 = (**(code **)*param_1)();
  if (iVar1 == 0) {
    return 0x3c;
  }
  hCursor = (HCURSOR)(**(code **)(*param_1 + 8))();
  SetCursor(hCursor);
  return 0;
}


/* 00448850 size=10 */

void __thiscall FUN_00448850(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 4) = param_1;
  return;
}


/* 004488d0 size=155 */

/* FUN_004488d0: lifted from original x86 -> lt_lifted.c */


/* 00448970 size=155 */

/* FUN_00448970: lifted from original x86 -> lt_lifted.c */


/* 00448a10 size=159 */

/* FUN_00448a10: lifted from original x86 -> lt_lifted.c */


/* 00448ae0 size=18 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00448ae0(void)

{
  DAT_004ea618 = 0;
  _DAT_004ea61c = 0;
  DAT_004ea610 = 0;
  return;
}


/* 00448b00 size=12 */

void FUN_00448b00(void)

{
  FUN_004b9cf5(&LAB_00448b10);
  return;
}


/* 00448bb0 size=18 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00448bb0(void)

{
  DAT_004ea5a0 = 0;
  _DAT_004ea5a4 = 0;
  DAT_004ea598 = 0;
  return;
}


/* 00448bd0 size=12 */

void FUN_00448bd0(void)

{
  FUN_004b9cf5(&LAB_00448be0);
  return;
}


/* 00448cc0 size=18 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00448cc0(void)

{
  DAT_004ea5e8 = 0;
  _DAT_004ea5ec = 0;
  DAT_004ea5e0 = 0;
  return;
}


/* 00448ce0 size=12 */

void FUN_00448ce0(void)

{
  FUN_004b9cf5(&LAB_00448cf0);
  return;
}


/* 00448da0 size=18 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00448da0(void)

{
  DAT_004ea600 = 0;
  _DAT_004ea604 = 0;
  DAT_004ea5f8 = 0;
  return;
}


/* 00448dc0 size=12 */

void FUN_00448dc0(void)

{
  FUN_004b9cf5(&LAB_00448dd0);
  return;
}


/* 00448e70 size=18 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00448e70(void)

{
  DAT_004ea5b8 = 0;
  _DAT_004ea5bc = 0;
  DAT_004ea5b0 = 0;
  return;
}


/* 00448e90 size=12 */

void FUN_00448e90(void)

{
  FUN_004b9cf5(&LAB_00448ea0);
  return;
}


/* 00448f60 size=15 */

void __fastcall FUN_00448f60(int param_1)

{
  if (*(undefined **)(param_1 + 0x4c) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)(param_1 + 0x4c));
  }
  return;
}


/* 00448f80 size=18 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00448f80(void)

{
  DAT_004ea5d0 = 0;
  _DAT_004ea5d4 = 0;
  DAT_004ea5c8 = 0;
  return;
}


/* 00448fa0 size=12 */

void FUN_00448fa0(void)

{
  FUN_004b9cf5(&LAB_00448fb0);
  return;
}


/* 0044a770 size=289 */

undefined4 __thiscall FUN_0044a770(void *this,byte *param_1,int param_2)

{
  LPCRITICAL_SECTION lpCriticalSection;
  void *this_00;
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  FUN_00448a10(4,(byte *)s_CLTDirectMusicMgr__StopSecondary_004da57c,param_1);
  if (*(int *)((int)this + 4) == 0) {
    ltdirectmusic_impl_448ab0(s_CLTDirectMusicMgr__StopSecondary_004da558);
    return 1;
  }
  if (*(int *)((int)this + 8) == 0) {
    ltdirectmusic_impl_448ab0(s_CLTDirectMusicMgr__StopSecondary_004da558);
    return 1;
  }
  lpCriticalSection = (LPCRITICAL_SECTION)((int)this + 0x94);
  EnterCriticalSection(lpCriticalSection);
  if (param_1 == (byte *)0x0) {
    piVar2 = *(int **)((int)this + 0x84);
    iVar3 = param_2;
    if (piVar2 != (int *)0x0) {
      do {
        piVar1 = (int *)*piVar2;
        if (piVar2[2] != 0) {
          if (param_2 == 1) {
            iVar3 = *(int *)(piVar2[3] + 0x50);
          }
          if (iVar3 != 6) {
            FUN_0044bf80((void *)((int)this + 0x84),(int)this,piVar2);
          }
          piVar2 = piVar1;
        }
      } while (piVar2 != (int *)0x0);
      LeaveCriticalSection(lpCriticalSection);
      return 0;
    }
  }
  else {
    this_00 = (void *)((int)this + 0x84);
    piVar2 = FUN_0044bcb0(this_00,param_1);
    iVar3 = param_2;
    while (piVar2 != (int *)0x0) {
      if (param_2 == 1) {
        iVar3 = *(int *)(piVar2[3] + 0x50);
      }
      if ((*(int *)(piVar2[3] + 8) != 0) && (iVar3 != 6)) {
        FUN_0044bf80(this_00,(int)this,piVar2);
      }
      piVar2 = FUN_0044bcb0(this_00,param_1);
    }
  }
  LeaveCriticalSection(lpCriticalSection);
  return 0;
}


/* 0044aa20 size=289 */

undefined4 __thiscall FUN_0044aa20(void *this,byte *param_1,int param_2)

{
  LPCRITICAL_SECTION lpCriticalSection;
  void *this_00;
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  FUN_00448a10(4,(byte *)s_CLTDirectMusicMgr__StopMotif_sMo_004da638,param_1);
  if (*(int *)((int)this + 4) == 0) {
    ltdirectmusic_impl_448ab0(s_CLTDirectMusicMgr__StopMotif_004da618);
    return 1;
  }
  if (*(int *)((int)this + 8) == 0) {
    ltdirectmusic_impl_448ab0(s_CLTDirectMusicMgr__StopMotif_004da618);
    return 1;
  }
  lpCriticalSection = (LPCRITICAL_SECTION)((int)this + 0x94);
  EnterCriticalSection(lpCriticalSection);
  if (param_1 == (byte *)0x0) {
    piVar2 = *(int **)((int)this + 0x8c);
    iVar3 = param_2;
    if (piVar2 != (int *)0x0) {
      do {
        piVar1 = (int *)*piVar2;
        if (piVar2[2] != 0) {
          if (param_2 == 1) {
            iVar3 = *(int *)(piVar2[3] + 0x50);
          }
          if (iVar3 != 6) {
            FUN_0044bf80((void *)((int)this + 0x8c),(int)this,piVar2);
          }
          piVar2 = piVar1;
        }
      } while (piVar2 != (int *)0x0);
      LeaveCriticalSection(lpCriticalSection);
      return 0;
    }
  }
  else {
    this_00 = (void *)((int)this + 0x8c);
    piVar2 = FUN_0044bcb0(this_00,param_1);
    iVar3 = param_2;
    while (piVar2 != (int *)0x0) {
      if (param_2 == 1) {
        iVar3 = *(int *)(piVar2[3] + 0x50);
      }
      if ((*(int *)(piVar2[3] + 8) != 0) && (iVar3 != 6)) {
        FUN_0044bf80(this_00,(int)this,piVar2);
      }
      piVar2 = FUN_0044bcb0(this_00,param_1);
    }
  }
  LeaveCriticalSection(lpCriticalSection);
  return 0;
}


/* 0044ab70 size=226 */

undefined4 __fastcall FUN_0044ab70(int param_1)

{
  LPVOID *ppv;
  int *piVar1;
  bool bVar2;
  HRESULT HVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined3 extraout_var;
  int *piVar6;
  
  ppv = (LPVOID *)(param_1 + 0x14);
  HVar3 = CoCreateInstance((IID *)&DAT_004ced4c,(LPUNKNOWN)0x0,3,(IID *)&DAT_004cec7c,ppv);
  if (-1 < HVar3) {
    puVar4 = (undefined4 *)FUN_00430de0(0x38);
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)0x0;
    }
    else {
      puVar4 = FUN_0044d6a0(puVar4);
    }
    *(undefined4 **)(param_1 + 0x10) = puVar4;
    if (puVar4 == (undefined4 *)0x0) {
      *(undefined4 *)(param_1 + 0x10) = 0;
      piVar6 = *ppv;
    }
    else {
      FUN_0044d7f0();
      piVar6 = (int *)(param_1 + 0xc);
      *piVar6 = 0;
      iVar5 = (**(code **)(*(int *)*ppv + 0xc))(*ppv,piVar6,0,0);
      if (iVar5 < 0) {
        (**(code **)(**(int **)(param_1 + 0x10) + 8))(*(int **)(param_1 + 0x10));
        piVar6 = *ppv;
        *(undefined4 *)(param_1 + 0x10) = 0;
      }
      else {
        bVar2 = FUN_0044ac60(param_1);
        if (CONCAT31(extraout_var,bVar2) != 0) {
          return 1;
        }
        piVar1 = (int *)*piVar6;
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 0x2c))(piVar1,0,0);
          *piVar6 = 0;
        }
        piVar6 = *(int **)(param_1 + 0x10);
        if (piVar6 != (int *)0x0) {
          (**(code **)(*piVar6 + 8))(piVar6);
          *(undefined4 *)(param_1 + 0x10) = 0;
        }
        piVar6 = *ppv;
        if (piVar6 == (int *)0x0) {
          return 0;
        }
      }
    }
    (**(code **)(*piVar6 + 0x98))(piVar6);
    (**(code **)(*(int *)*ppv + 8))(*ppv);
  }
  *ppv = (LPVOID)0x0;
  return 0;
}


/* 0044ac60 size=211 */

bool __fastcall FUN_0044ac60(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  puVar1 = (undefined4 *)(param_1 + 0x18);
  if (*(int *)(param_1 + 0x18) != 0) {
    FUN_0044ad40(param_1);
  }
  puVar2 = (undefined4 *)(param_1 + 0x1c);
  puVar7 = puVar2;
  for (iVar6 = 9; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0xc4);
  *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0xc0);
  iVar6 = *(int *)(param_1 + 0xc0) + -1;
  *puVar2 = 0x24;
  *(int *)(param_1 + 0x28) = ((int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4) + 1;
  *(undefined4 *)(param_1 + 0x20) = 0xf;
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 200);
  iVar6 = (**(code **)(**(int **)(param_1 + 0xc) + 0x14))
                    (*(int **)(param_1 + 0xc),&DAT_004cee70,puVar2,puVar1,0);
  if (-1 < iVar6) {
    iVar6 = (**(code **)(*(int *)*puVar1 + 0x3c))((int *)*puVar1,1);
    if (-1 < iVar6) {
      iVar6 = (**(code **)(**(int **)(param_1 + 0x14) + 0x60))(*(int **)(param_1 + 0x14),*puVar1);
      if ((-1 < iVar6) && (uVar4 = 0, *(int *)(param_1 + 0x28) != 0)) {
        do {
          uVar3 = uVar4 + 1;
          iVar5 = (**(code **)(**(int **)(param_1 + 0x14) + 0x68))
                            (*(int **)(param_1 + 0x14),uVar4,*puVar1,uVar4 + 1);
          uVar4 = uVar3;
          if (iVar5 < 0) break;
        } while (uVar4 < *(uint *)(param_1 + 0x28));
      }
    }
  }
  return -1 < iVar6;
}


/* 0044ad40 size=58 */

undefined4 __fastcall FUN_0044ad40(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x18);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x3c))(piVar1,0);
    piVar1 = *(int **)(param_1 + 0x14);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 100))(piVar1,*(undefined4 *)(param_1 + 0x18));
    }
    (**(code **)(**(int **)(param_1 + 0x18) + 8))(*(int **)(param_1 + 0x18));
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return 1;
}


/* 0044ad80 size=121 */

void __fastcall FUN_0044ad80(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  
  piVar1 = *(int **)(param_1 + 0x14);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x14))(piVar1,0,0,0,0);
  }
  FUN_0044ad40(param_1);
  piVar1 = *(int **)(param_1 + 0xc);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x2c))(piVar1,0,0);
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  piVar1 = *(int **)(param_1 + 0x14);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x98))(piVar1);
    (**(code **)(**(int **)(param_1 + 0x14) + 8))(*(int **)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  puVar2 = *(undefined4 **)(param_1 + 0x10);
  if (puVar2 != (undefined4 *)0x0) {
    FUN_0044d750(puVar2);
    FUN_00430df0((undefined *)puVar2);
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  return;
}


/* 0044ae00 size=490 */

void __thiscall FUN_0044ae00(void *this,LPCSTR param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  int *piVar7;
  LPCSTR pCVar8;
  int *piVar9;
  bool bVar10;
  int local_10 [4];
  
  if (param_2 == 1) {
    if (*(undefined **)((int)this + 0xd8) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)((int)this + 0xd8));
      *(undefined4 *)((int)this + 0xd8) = 0;
    }
    if (param_1 != (LPCSTR)0x0) {
      uVar3 = 0xffffffff;
      pCVar8 = param_1;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        cVar1 = *pCVar8;
        pCVar8 = pCVar8 + 1;
      } while (cVar1 != '\0');
      pcVar2 = (char *)FUN_00430de0(~uVar3);
      *(char **)((int)this + 0xd8) = pcVar2;
LAB_0044ae97:
      uVar3 = 0xffffffff;
      pCVar8 = param_1;
      do {
        pcVar6 = pCVar8;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar6 = pCVar8 + 1;
        cVar1 = *pCVar8;
        pCVar8 = pcVar6;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      pcVar6 = pcVar6 + -uVar3;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar2 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar2 = pcVar2 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar2 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar2 = pcVar2 + 1;
      }
    }
  }
  else if (param_2 == 2) {
    if (*(undefined **)((int)this + 0xdc) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)((int)this + 0xdc));
      *(undefined4 *)((int)this + 0xdc) = 0;
    }
    if (param_1 != (LPCSTR)0x0) {
      uVar3 = 0xffffffff;
      pCVar8 = param_1;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        cVar1 = *pCVar8;
        pCVar8 = pCVar8 + 1;
      } while (cVar1 != '\0');
      pcVar2 = (char *)FUN_00430de0(~uVar3);
      *(char **)((int)this + 0xdc) = pcVar2;
      goto LAB_0044ae97;
    }
  }
  local_10[1] = DAT_004cee74;
  local_10[2] = DAT_004cee78;
  local_10[0] = DAT_004cee70;
  local_10[3] = DAT_004cee7c;
  switch(param_2) {
  case 1:
    local_10[0] = DAT_004ced0c;
    local_10[1] = DAT_004ced10;
    local_10[2] = DAT_004ced14;
    local_10[3] = DAT_004ced18;
    break;
  case 3:
    local_10[0] = DAT_004ced7c;
    local_10[1] = DAT_004ced80;
    local_10[2] = DAT_004ced84;
    local_10[3] = DAT_004ced88;
    goto LAB_0044afb8;
  case 4:
    local_10[0] = DAT_004ced2c;
    local_10[1] = DAT_004ced30;
    local_10[2] = DAT_004ced34;
    local_10[3] = DAT_004ced38;
    break;
  case 5:
    local_10[0] = DAT_004ced3c;
    local_10[1] = DAT_004ced40;
    local_10[2] = DAT_004ced44;
    local_10[3] = DAT_004ced48;
    break;
  case 6:
    local_10[0] = DAT_004ced1c;
    local_10[1] = DAT_004ced20;
    local_10[2] = DAT_004ced24;
    local_10[3] = DAT_004ced28;
LAB_0044afb8:
  }
  iVar5 = 4;
  bVar10 = true;
  piVar7 = local_10;
  piVar9 = &DAT_004cee70;
  do {
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    bVar10 = *piVar7 == *piVar9;
    piVar7 = piVar7 + 1;
    piVar9 = piVar9 + 1;
  } while (bVar10);
  if (!bVar10) {
    FUN_0044dd90(*(int **)((int)this + 0x10),local_10,param_1,0);
  }
  return;
}


/* 0044b190 size=239 */

undefined4 __thiscall FUN_0044b190(void *this,LPCSTR param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  WCHAR local_208 [260];
  
  MultiByteToWideChar(0,1,param_1,-1,local_208,0x104);
  iVar1 = FUN_004bc284((ushort *)local_208,(ushort *)&DAT_004ea62c);
  if (iVar1 != 0) {
    piVar2 = DAT_004ea5d8;
    if (DAT_004ea5d8 == (int *)0x0) {
      piVar2 = (int *)FUN_00430de0(0xc);
      if (piVar2 == (int *)0x0) {
        return 0;
      }
      piVar3 = (int *)FUN_00430de0(DAT_004ea5cc * 0xc);
      piVar2[2] = (int)piVar3;
      if (piVar3 == (int *)0x0) {
        return 0;
      }
      uVar4 = 0;
      if (DAT_004ea5cc != 0) {
        piVar5 = DAT_004ea5d8;
        do {
          DAT_004ea5d8 = piVar3;
          *DAT_004ea5d8 = (int)piVar5;
          uVar4 = uVar4 + 1;
          piVar3 = DAT_004ea5d8 + 3;
          piVar5 = DAT_004ea5d8;
        } while (uVar4 < DAT_004ea5cc);
      }
      FUN_0044ca30(&DAT_004ea5d0,piVar2);
      piVar2 = DAT_004ea5d8;
      if (DAT_004ea5d8 == (int *)0x0) {
        return 0;
      }
    }
    DAT_004ea5d8 = (int *)*piVar2;
    if (piVar2 == (int *)0x0) {
      return 0;
    }
    piVar2[2] = 0;
    FUN_004b4f00((void *)((int)this + 0x60),piVar2);
  }
  return 1;
}


/* 0044b620 size=76 */

undefined4 __thiscall FUN_0044b620(void *this,void *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  for (puVar1 = FUN_004b8dd0(param_1,(byte *)0x0,(byte *)s_STYLE_004da7b8);
      puVar1 != (undefined4 *)0x0; puVar1 = FUN_004b8a30(puVar1)) {
    iVar2 = FUN_004b8a20((int)puVar1);
    if (iVar2 != 0) {
      ltdirectmusic_impl_44b280(this,*(byte **)(iVar2 + 8));
    }
  }
  return 1;
}


/* 0044b880 size=346 */

undefined4 __thiscall FUN_0044b880(void *this,void *param_1)

{
  LPCSTR lpMultiByteStr;
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int *this_00;
  undefined4 *local_214;
  int local_20c;
  WCHAR local_208 [260];
  
  local_214 = FUN_004b8dd0(param_1,(byte *)0x0,(byte *)s_MOTIF_004da7e0);
  if (local_214 == (undefined4 *)0x0) {
    return 1;
  }
  do {
    piVar1 = (int *)FUN_004b8a20((int)local_214);
    if (piVar1 != (int *)0x0) {
      puVar2 = FUN_0044bc60((void *)((int)this + 0x58),(byte *)piVar1[2]);
      piVar1 = (int *)*piVar1;
      if (((piVar1 != (int *)0x0) &&
          (lpMultiByteStr = (LPCSTR)piVar1[2], puVar2 != (undefined4 *)0x0)) &&
         (lpMultiByteStr != (LPCSTR)0x0)) {
        MultiByteToWideChar(0,1,lpMultiByteStr,-1,local_208,0x104);
        iVar3 = (**(code **)(*(int *)puVar2[2] + 0x1c))((int *)puVar2[2],local_208,&local_20c);
        if ((iVar3 == 0) && (local_20c != 0)) {
          if (DAT_004ea5a8 == (int *)0x0) {
            iVar3 = FUN_0044c710(0x4ea598);
            if (iVar3 == 0) goto LAB_0044b9a5;
            this_00 = (int *)FUN_0044c660(0x4ea598);
          }
          else {
            this_00 = DAT_004ea5a8;
            DAT_004ea5a8 = (int *)*DAT_004ea5a8;
          }
          if (this_00 != (int *)0x0) {
            *(undefined1 *)(this_00 + 3) = 0;
            this_00[2] = 0;
            this_00[0x13] = 0;
            this_00[0x14] = 4;
            this_00[2] = local_20c;
            FUN_0044bb90(this_00,lpMultiByteStr);
            if (*piVar1 != 0) {
              iVar3 = (**(code **)(*(int *)this + 0x3c))(*(undefined4 *)(*piVar1 + 8));
              this_00[0x14] = iVar3;
            }
            FUN_004b4f00((void *)((int)this + 0x48),this_00);
          }
        }
      }
    }
LAB_0044b9a5:
    local_214 = FUN_004b8a30(local_214);
    if (local_214 == (undefined4 *)0x0) {
      return 1;
    }
  } while( true );
}


/* 0044bb90 size=184 */

undefined4 __thiscall FUN_0044bb90(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  
  if (*(undefined **)((int)this + 0x4c) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)((int)this + 0x4c));
    *(undefined4 *)((int)this + 0x4c) = 0;
  }
  if (param_1 == (char *)0x0) {
    *(undefined1 *)((int)this + 0xc) = 0;
    return 1;
  }
  uVar3 = 0xffffffff;
  pcVar2 = param_1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  if ((int)(~uVar3 - 1) < 0x40) {
    uVar3 = 0xffffffff;
    do {
      pcVar2 = param_1;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar2 = param_1 + 1;
      cVar1 = *param_1;
      param_1 = pcVar2;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar2 = pcVar2 + -uVar3;
    pcVar5 = (char *)((int)this + 0xc);
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar5 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar5 = pcVar5 + 1;
    }
    return 1;
  }
  pcVar2 = (char *)FUN_00430de0(~uVar3);
  *(char **)((int)this + 0x4c) = pcVar2;
  if (pcVar2 == (char *)0x0) {
    return 0;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = param_1;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar2 = pcVar2 + 1;
  }
  *(undefined1 *)((int)this + 0xc) = 0;
  return 1;
}


/* 0044bc50 size=11 */

int __fastcall FUN_0044bc50(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x4c);
  if (iVar1 == 0) {
    iVar1 = param_1 + 0xc;
  }
  return iVar1;
}


/* 0044bc60 size=68 */

undefined4 * __thiscall FUN_0044bc60(void *this,byte *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  void *this_00;
  byte *pbVar5;
  
  if (param_1 != (byte *)0x0) {
    for (puVar1 = *(undefined4 **)this; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1)
    {
      iVar2 = FUN_0044bc50((int)puVar1);
      if (iVar2 != 0) {
        pbVar5 = param_1;
        pbVar3 = (byte *)FUN_0044bc50((int)puVar1);
        uVar4 = FUN_004c4c00(this_00,pbVar3,pbVar5);
        if (uVar4 == 0) {
          return puVar1;
        }
      }
    }
  }
  return (undefined4 *)0x0;
}


/* 0044bcb0 size=78 */

undefined4 * __thiscall FUN_0044bcb0(void *this,byte *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  void *this_00;
  byte *pbVar6;
  
  if (param_1 != (byte *)0x0) {
    for (puVar1 = *(undefined4 **)this; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1)
    {
      iVar2 = puVar1[3];
      if ((iVar2 != 0) && (iVar3 = FUN_0044bc50(iVar2), iVar3 != 0)) {
        pbVar6 = param_1;
        pbVar4 = (byte *)FUN_0044bc50(iVar2);
        uVar5 = FUN_004c4c00(this_00,pbVar4,pbVar6);
        if (uVar5 == 0) {
          return puVar1;
        }
      }
    }
  }
  return (undefined4 *)0x0;
}


/* 0044bd00 size=26 */

undefined4 * __thiscall FUN_0044bd00(void *this,int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)this;
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if (param_1 == puVar1[2]) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}


/* 0044bd20 size=71 */

void __fastcall FUN_0044bd20(int param_1)

{
  int *this;
  
  this = *(int **)(param_1 + 8);
  while (this != (int *)0x0) {
    FUN_0044bb90(this,(char *)0x0);
    FUN_004b4f60((undefined4 *)(param_1 + 8),this);
    if (this != (int *)0x0) {
      if ((undefined *)this[0x13] != (undefined *)0x0) {
        FUN_00430df0((undefined *)this[0x13]);
      }
      *this = (int)DAT_004ea5a8;
      DAT_004ea5a8 = this;
    }
    this = *(int **)(param_1 + 8);
  }
  return;
}


/* 0044bd70 size=92 */

void __fastcall FUN_0044bd70(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x68);
  while (piVar1 != (int *)0x0) {
    FUN_004b4f60((undefined4 *)(param_1 + 0x68),piVar1);
    if (piVar1 != (int *)0x0) {
      *piVar1 = (int)DAT_004ea620;
      DAT_004ea620 = piVar1;
    }
    piVar1 = *(int **)(param_1 + 0x68);
  }
  piVar1 = *(int **)(param_1 + 0x70);
  while (piVar1 != (int *)0x0) {
    FUN_004b4f60((undefined4 *)(param_1 + 0x70),piVar1);
    if (piVar1 != (int *)0x0) {
      *piVar1 = (int)DAT_004ea620;
      DAT_004ea620 = piVar1;
    }
    piVar1 = *(int **)(param_1 + 0x70);
  }
  return;
}


/* 0044bdd0 size=71 */

int __thiscall FUN_0044bdd0(void *this,int param_1,int param_2)

{
  if ((((*(int *)((int)this + 0xd0) < param_1) || (param_1 < 1)) ||
      (*(int *)((int)this + 0xd0) < param_2)) || (param_2 < 1)) {
    return *(int *)((int)this + 0xd4);
  }
  return *(int *)((int)this + 0xd4) +
         ((*(int *)((int)this + 0xb0) + 1) * param_2 + 1 + param_1) * 0xc;
}


/* 0044be20 size=47 */

void __thiscall FUN_0044be20(void *this,int param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = *(int **)this;
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)*piVar2;
    FUN_0044be50(this,param_1,piVar2);
    piVar2 = piVar1;
  }
  return;
}


/* 0044be50 size=137 */

void __thiscall FUN_0044be50(void *this,int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  
  if (((param_1 != 0) && (param_2 != (int *)0x0)) && (param_2[2] != 0)) {
    iVar2 = (**(code **)(**(int **)(param_1 + 0x14) + 0x38))(*(int **)(param_1 + 0x14),param_2[2],0)
    ;
    if ((iVar2 == 0) || (param_1 == 0)) {
      (**(code **)(**(int **)(param_1 + 0x14) + 0x14))(*(int **)(param_1 + 0x14),param_2[2],0,0,0);
      piVar1 = (int *)param_2[2];
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
      }
      FUN_0044bb90(param_2,(char *)0x0);
      FUN_004b4f60(this,param_2);
      if ((undefined *)param_2[0x13] != (undefined *)0x0) {
        FUN_00430df0((undefined *)param_2[0x13]);
      }
      *param_2 = (int)DAT_004ea5a8;
      DAT_004ea5a8 = param_2;
    }
  }
  return;
}


/* 0044bee0 size=103 */

void __thiscall FUN_0044bee0(void *this,int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_1 != 0) {
    if (DAT_004ea5f0 == (int *)0x0) {
      iVar1 = FUN_0044c7e0(0x4ea5e0);
      if (iVar1 == 0) {
        return;
      }
      if (DAT_004ea5f0 == (int *)0x0) {
        return;
      }
      piVar2 = DAT_004ea5f0;
      DAT_004ea5f0 = (int *)*DAT_004ea5f0;
    }
    else {
      piVar2 = DAT_004ea5f0;
      DAT_004ea5f0 = (int *)*DAT_004ea5f0;
    }
    if (piVar2 != (int *)0x0) {
      piVar2[2] = 0;
      piVar2[3] = 0;
      piVar2[3] = param_2;
      piVar2[2] = param_1;
      FUN_004b4f00(this,piVar2);
    }
  }
  return;
}


/* 0044bf50 size=47 */

void __thiscall FUN_0044bf50(void *this,int param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = *(int **)this;
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)*piVar2;
    FUN_0044bf80(this,param_1,piVar2);
    piVar2 = piVar1;
  }
  return;
}


/* 0044bf80 size=120 */

void __thiscall FUN_0044bf80(void *this,int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int unaff_retaddr;
  
  if (((param_1 != 0) && (param_2 != (int *)0x0)) && (param_2[2] != 0)) {
    iVar2 = (**(code **)(**(int **)(param_1 + 0x14) + 0x38))(*(int **)(param_1 + 0x14),0,param_2[2])
    ;
    if ((iVar2 == 0) || (param_1 == 0)) {
      if (unaff_retaddr != 0) {
        (**(code **)(**(int **)(param_1 + 0x14) + 0x14))(*(int **)(param_1 + 0x14),0,param_2[2],0,0)
        ;
      }
      piVar1 = (int *)param_2[2];
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
      }
      FUN_004b4f60(this,param_2);
      *param_2 = (int)DAT_004ea5f0;
      DAT_004ea5f0 = param_2;
    }
  }
  return;
}


