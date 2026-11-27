/* lithtech.exe decompilation - unnamed_004c8000 */
#include "ghidra_types.h"

/* 004c8210 size=124 */

void __cdecl FUN_004c8210(int *param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined **ppuVar3;
  undefined **ppuVar4;
  undefined2 local_10;
  undefined4 local_e;
  undefined2 uStack_a;
  undefined *puStack_8;
  
  ppuVar3 = &PTR_DAT_004e3db0;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      ppuVar3 = (undefined **)0x4e3f10;
    }
    if (param_3 == 0) {
      *(undefined2 *)param_1 = 0;
    }
    while (param_2 != 0) {
      ppuVar3 = ppuVar3 + 0x15;
      uVar1 = (int)param_2 >> 3;
      uVar2 = param_2 & 7;
      param_2 = uVar1;
      if (uVar2 != 0) {
        ppuVar4 = ppuVar3 + uVar2 * 3;
        if (0x7fff < *(ushort *)(ppuVar3 + uVar2 * 3)) {
          local_10 = SUB42(*ppuVar4,0);
          (*(uint16_t*)((char*)&local_e+0)) = (undefined2)((uint)*ppuVar4 >> 0x10);
          (*(uint16_t*)((char*)&local_e+2)) = SUB42(ppuVar4[1],0);
          uStack_a = (undefined2)((uint)ppuVar4[1] >> 0x10);
          puStack_8 = ppuVar4[2];
          local_e = CONCAT22((*(uint16_t*)((char*)&local_e+2)),(undefined2)local_e) + -1;
          ppuVar4 = (undefined **)&local_10;
        }
        FUN_004c7ff0(param_1,(int *)ppuVar4);
      }
    }
  }
  return;
}


/* 004c828c size=125 */

int __cdecl FUN_004c828c(uchar *param_1)

{
  int iVar1;
  size_t _MaxCount;
  size_t sVar2;
  int *piVar3;
  
  if (((DAT_004ee3e8 != 0) &&
      ((DAT_004ecca4 != (int *)0x0 ||
       (((DAT_004eccac != 0 && (iVar1 = FUN_004c84b1(), iVar1 == 0)) && (DAT_004ecca4 != (int *)0x0)
        ))))) && (piVar3 = DAT_004ecca4, param_1 != (uchar *)0x0)) {
    _MaxCount = _strlen((char *)param_1);
    for (; (char *)*piVar3 != (char *)0x0; piVar3 = piVar3 + 1) {
      sVar2 = _strlen((char *)*piVar3);
      if (((_MaxCount < sVar2) && (((uchar *)*piVar3)[_MaxCount] == '=')) &&
         (iVar1 = __mbsnbicoll((uchar *)*piVar3,param_1,_MaxCount), iVar1 == 0)) {
        return *piVar3 + 1 + _MaxCount;
      }
    }
  }
  return 0;
}


/* 004c8310 size=257 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004c8310: lifted from original x86 -> lt_lifted.c */


/* 004c8411 size=97 */

int __cdecl FUN_004c8411(uint param_1,int param_2)

{
  byte bVar1;
  DWORD *pDVar2;
  byte bVar3;
  
  bVar1 = *(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24);
  if (param_2 == 0x8000) {
    bVar3 = bVar1 & 0x7f;
  }
  else {
    if (param_2 != 0x4000) {
      pDVar2 = FUN_004c09cc();
      *pDVar2 = 0x16;
      return -1;
    }
    bVar3 = bVar1 | 0x80;
  }
  *(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) = bVar3;
  return (-(uint)((bVar1 & 0x80) != 0) & 0xffffc000) + 0x8000;
}


/* 004c84b1 size=110 */

undefined4 FUN_004c84b1(void)

{
  LPCWSTR lpWideCharStr;
  size_t _Size;
  uint *lpMultiByteStr;
  int iVar1;
  undefined4 *puVar2;
  
  lpWideCharStr = (LPCWSTR)*DAT_004eccac;
  puVar2 = DAT_004eccac;
  while( true ) {
    if (lpWideCharStr == (LPCWSTR)0x0) {
      return 0;
    }
    _Size = WideCharToMultiByte(1,0,lpWideCharStr,-1,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
    if (((_Size == 0) || (lpMultiByteStr = _malloc(_Size), lpMultiByteStr == (uint *)0x0)) ||
       (iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*puVar2,-1,(LPSTR)lpMultiByteStr,_Size,(LPCSTR)0x0,
                                    (LPBOOL)0x0), iVar1 == 0)) break;
    FUN_004c87c7(lpMultiByteStr,0);
    lpWideCharStr = (LPCWSTR)puVar2[1];
    puVar2 = puVar2 + 1;
  }
  return 0xffffffff;
}


/* 004c851f size=597 */

int __cdecl
FUN_004c851f(LCID param_1,DWORD param_2,byte *param_3,int param_4,byte *param_5,int param_6,
            UINT param_7)

{
  int iVar1;
  BOOL BVar2;
  BYTE *pBVar3;
  int iVar4;
  undefined1 unaff_DI;
  undefined1 uStack00000000;
  BYTE aBStack_42 [2];
  _cpinfo local_40;
  undefined1 *local_2c;
  PCNZWCH local_28;
  int local_24;
  int local_20;
  undefined1 *local_1c;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf8d0;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  local_1c = (&local_40)[-1].DefaultChar;
  ExceptionList = &local_14;
  pBVar3 = (&local_40)[-1].DefaultChar;
  if (DAT_004ed014 == 0) {
    ExceptionList = &local_14;
    iVar1 = CompareStringW(0,0,L"",1,L"",1);
    if (iVar1 == 0) {
      iVar1 = CompareStringA(0,0,"",1,"",1);
      if (iVar1 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      DAT_004ed014 = 2;
      pBVar3 = local_1c;
    }
    else {
      DAT_004ed014 = 1;
      pBVar3 = local_1c;
    }
  }
  local_1c = pBVar3;
  if (0 < param_4) {
    param_4 = FUN_004c879c((char *)param_3,param_4);
  }
  if (0 < param_6) {
    param_6 = FUN_004c879c((char *)param_5,param_6);
  }
  if (DAT_004ed014 == 2) {
    iVar1 = CompareStringA(param_1,param_2,(PCNZCH)param_3,param_4,(PCNZCH)param_5,param_6);
    ExceptionList = local_14;
    return iVar1;
  }
  if (DAT_004ed014 != 1) {
    ExceptionList = local_14;
    return 0;
  }
  if (param_7 == 0) {
    param_7 = DAT_004ecd88;
  }
  if ((param_4 != 0) && (param_6 != 0)) {
LAB_004c869d:
    local_20 = MultiByteToWideChar(param_7,9,(LPCSTR)param_3,param_4,(LPWSTR)0x0,0);
    if (local_20 != 0) {
      local_8 = 0;
      FUN_004ba7f0(unaff_DI);
      local_8 = 0xffffffff;
      if ((&uStack00000000 != (undefined1 *)0x50) &&
         (local_28 = (PCNZWCH)(&local_40)[-1].DefaultChar, local_1c = (&local_40)[-1].DefaultChar,
         iVar1 = MultiByteToWideChar(param_7,1,(LPCSTR)param_3,param_4,
                                     (LPWSTR)(&local_40)[-1].DefaultChar,local_20), iVar1 != 0)) {
        iVar1 = MultiByteToWideChar(param_7,9,(LPCSTR)param_5,param_6,(LPWSTR)0x0,0);
        if (iVar1 != 0) {
          local_8 = 1;
          local_24 = iVar1;
          FUN_004ba7f0(unaff_DI);
          local_8 = 0xffffffff;
          if ((&uStack00000000 != (undefined1 *)0x50) &&
             (local_2c = (&local_40)[-1].DefaultChar, local_1c = (&local_40)[-1].DefaultChar,
             iVar4 = MultiByteToWideChar(param_7,1,(LPCSTR)param_5,param_6,
                                         (LPWSTR)(&local_40)[-1].DefaultChar,iVar1), iVar4 != 0)) {
            iVar1 = CompareStringW(param_1,param_2,local_28,local_20,
                                   (PCNZWCH)(&local_40)[-1].DefaultChar,iVar1);
            ExceptionList = local_14;
            return iVar1;
          }
        }
      }
    }
    ExceptionList = local_14;
    return 0;
  }
  if (param_4 == param_6) {
    ExceptionList = local_14;
    return 2;
  }
  if (1 < param_6) {
    ExceptionList = local_14;
    return 1;
  }
  if (param_4 < 2) {
    BVar2 = GetCPInfo(param_7,&local_40);
    if (BVar2 == 0) {
      ExceptionList = local_14;
      return 0;
    }
    if (param_4 < 1) {
      if (0 < param_6) {
        if (local_40.MaxCharSize < 2) {
          ExceptionList = local_14;
          return 1;
        }
        pBVar3 = local_40.LeadByte;
        while( true ) {
          if (local_40.LeadByte[0] == 0) {
            ExceptionList = local_14;
            return 1;
          }
          if (pBVar3[1] == 0) break;
          if ((*pBVar3 <= *param_5) && (*param_5 <= pBVar3[1])) {
            ExceptionList = local_14;
            return 2;
          }
          pBVar3 = pBVar3 + 2;
          local_40.LeadByte[0] = *pBVar3;
        }
        ExceptionList = local_14;
        return 1;
      }
      goto LAB_004c869d;
    }
    if (1 < local_40.MaxCharSize) {
      pBVar3 = local_40.LeadByte;
      while ((local_40.LeadByte[0] != 0 && (pBVar3[1] != 0))) {
        if ((*pBVar3 <= *param_3) && (*param_3 <= pBVar3[1])) {
          ExceptionList = local_14;
          return 2;
        }
        pBVar3 = pBVar3 + 2;
        local_40.LeadByte[0] = *pBVar3;
      }
    }
  }
  ExceptionList = local_14;
  return 3;
}


/* 004c879c size=43 */

int __cdecl FUN_004c879c(char *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = param_2;
  for (pcVar1 = param_1; (iVar2 != 0 && (iVar2 = iVar2 + -1, *pcVar1 != '\0')); pcVar1 = pcVar1 + 1)
  {
  }
  if (*pcVar1 == '\0') {
    return (int)pcVar1 - (int)param_1;
  }
  return param_2;
}


/* 004c87c7 size=391 */

undefined4 __cdecl FUN_004c87c7(uint *param_1,int param_2)

{
  byte *pbVar1;
  uint *puVar2;
  int iVar3;
  byte *pbVar4;
  size_t sVar5;
  uint *lpName;
  undefined1 *puVar6;
  byte *pbVar7;
  bool bVar8;
  
  if (param_1 == (uint *)0x0) {
    return 0xffffffff;
  }
  puVar2 = FUN_004c8a0d(param_1,0x3d);
  if (puVar2 == (uint *)0x0) {
    return 0xffffffff;
  }
  if (param_1 == puVar2) {
    return 0xffffffff;
  }
  bVar8 = *(char *)((int)puVar2 + 1) == '\0';
  if (DAT_004ecca4 == DAT_004ecca8) {
    DAT_004ecca4 = (byte *)FUN_004c89a6((int *)DAT_004ecca4);
  }
  if (DAT_004ecca4 == (byte *)0x0) {
    if ((param_2 == 0) || (DAT_004eccac == (undefined4 *)0x0)) {
      if (bVar8) {
        return 0;
      }
      DAT_004ecca4 = _malloc(4);
      if (DAT_004ecca4 == (byte *)0x0) {
        return 0xffffffff;
      }
      pbVar4 = DAT_004ecca4 + 1;
      pbVar7 = DAT_004ecca4 + 2;
      pbVar1 = DAT_004ecca4 + 3;
      DAT_004ecca4[0] = 0;
      *pbVar4 = 0;
      *pbVar7 = 0;
      *pbVar1 = 0;
      if (DAT_004eccac == (undefined4 *)0x0) {
        DAT_004eccac = _malloc(4);
        if (DAT_004eccac == (undefined4 *)0x0) {
          return 0xffffffff;
        }
        *DAT_004eccac = 0;
      }
    }
    else {
      iVar3 = FUN_004c84b1();
      if (iVar3 != 0) {
        return 0xffffffff;
      }
    }
  }
  pbVar4 = DAT_004ecca4;
  iVar3 = FUN_004c894e((uchar *)param_1,(int)puVar2 - (int)param_1);
  if ((iVar3 < 0) || (*(int *)pbVar4 == 0)) {
    if (bVar8) {
      return 0;
    }
    if (iVar3 < 0) {
      iVar3 = -iVar3;
    }
    pbVar4 = FUN_004bdf74(pbVar4,(uint *)(iVar3 * 4 + 8));
    if (pbVar4 == (byte *)0x0) {
      return 0xffffffff;
    }
    *(uint **)(pbVar4 + iVar3 * 4) = param_1;
    pbVar7 = pbVar4 + iVar3 * 4 + 4;
    pbVar7[0] = 0;
    pbVar7[1] = 0;
    pbVar7[2] = 0;
    pbVar7[3] = 0;
  }
  else {
    if (!bVar8) {
      *(uint **)(pbVar4 + iVar3 * 4) = param_1;
      goto LAB_004c88fb;
    }
    pbVar7 = pbVar4 + iVar3 * 4;
    FUN_004b9d3f(*(undefined **)(pbVar4 + iVar3 * 4));
    for (; *(int *)pbVar7 != 0; pbVar7 = pbVar7 + 4) {
      iVar3 = iVar3 + 1;
      *(int *)pbVar7 = *(int *)(pbVar7 + 4);
    }
    pbVar4 = FUN_004bdf74(pbVar4,(uint *)(iVar3 << 2));
    if (pbVar4 == (byte *)0x0) goto LAB_004c88fb;
  }
  DAT_004ecca4 = pbVar4;
LAB_004c88fb:
  if (param_2 != 0) {
    sVar5 = _strlen((char *)param_1);
    lpName = _malloc(sVar5 + 2);
    if (lpName != (uint *)0x0) {
      FUN_004c17f0(lpName,param_1);
      puVar6 = (undefined1 *)(((int)lpName - (int)param_1) + (int)puVar2);
      *puVar6 = 0;
      SetEnvironmentVariableA((LPCSTR)lpName,(LPCSTR)(~-(uint)bVar8 & (uint)(puVar6 + 1)));
      FUN_004b9d3f((undefined *)lpName);
    }
  }
  return 0;
}


/* 004c894e size=88 */

int __cdecl FUN_004c894e(uchar *param_1,size_t param_2)

{
  uchar *_Str2;
  int iVar1;
  int *piVar2;
  
  _Str2 = (uchar *)*DAT_004ecca4;
  piVar2 = DAT_004ecca4;
  while( true ) {
    if (_Str2 == (uchar *)0x0) {
      return -((int)piVar2 - (int)DAT_004ecca4 >> 2);
    }
    iVar1 = __mbsnbicoll(param_1,_Str2,param_2);
    if ((iVar1 == 0) &&
       ((*(char *)(*piVar2 + param_2) == '=' || (*(char *)(*piVar2 + param_2) == '\0')))) break;
    _Str2 = (uchar *)piVar2[1];
    piVar2 = piVar2 + 1;
  }
  return (int)piVar2 - (int)DAT_004ecca4 >> 2;
}


/* 004c89a6 size=103 */

undefined4 * __cdecl FUN_004c89a6(int *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  uint *puVar4;
  int iVar5;
  undefined4 *puVar6;
  
  iVar5 = 0;
  if (param_1 == (int *)0x0) {
    return (undefined4 *)0x0;
  }
  iVar1 = *param_1;
  piVar2 = param_1;
  while (iVar1 != 0) {
    piVar2 = piVar2 + 1;
    iVar5 = iVar5 + 1;
    iVar1 = *piVar2;
  }
  puVar3 = _malloc(iVar5 * 4 + 4);
  if (puVar3 == (undefined4 *)0x0) {
    __amsg_exit(9);
  }
  puVar4 = (uint *)*param_1;
  puVar6 = puVar3;
  while (puVar4 != (uint *)0x0) {
    param_1 = param_1 + 1;
    puVar4 = FUN_004c8aa4(puVar4);
    *puVar6 = puVar4;
    puVar6 = puVar6 + 1;
    puVar4 = (uint *)*param_1;
  }
  *puVar6 = 0;
  return puVar3;
}


/* 004c8a0d size=151 */

uint * __cdecl FUN_004c8a0d(uint *param_1,uint param_2)

{
  byte bVar1;
  uint *puVar2;
  uint uVar3;
  
  if (DAT_004ed06c == 0) {
    puVar2 = FUN_004bb020(param_1,(char)param_2);
  }
  else {
    FUN_004bf7a0(0x19);
    while( true ) {
      bVar1 = (byte)*param_1;
      uVar3 = (uint)bVar1;
      if (bVar1 == 0) break;
      if ((*(byte *)((int)&DAT_004ed180 + uVar3 + 1) & 4) == 0) {
        puVar2 = param_1;
        if (param_2 == uVar3) break;
      }
      else {
        puVar2 = (uint *)((int)param_1 + 1);
        if (*(byte *)((int)param_1 + 1) == 0) {
          FUN_004bf801(0x19);
          return (uint *)0x0;
        }
        if (param_2 == CONCAT11(bVar1,*(byte *)((int)param_1 + 1))) {
          FUN_004bf801(0x19);
          return param_1;
        }
      }
      param_1 = (uint *)((int)puVar2 + 1);
    }
    FUN_004bf801(0x19);
    puVar2 = (uint *)(~-(uint)(param_2 != uVar3) & (uint)param_1);
  }
  return puVar2;
}


/* 004c8aa4 size=43 */

uint * __cdecl FUN_004c8aa4(uint *param_1)

{
  size_t sVar1;
  uint *puVar2;
  
  if (param_1 != (uint *)0x0) {
    sVar1 = _strlen((char *)param_1);
    puVar2 = _malloc(sVar1 + 1);
    if (puVar2 != (uint *)0x0) {
      puVar2 = FUN_004c17f0(puVar2,param_1);
      return puVar2;
    }
  }
  return (uint *)0x0;
}


/* 004c8ae0 size=73 */

int __fastcall FUN_004c8ae0(int param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  if ((*(int *)(param_1 + 4) != 0) && (iVar2 = *(int *)(param_1 + 4) + -4, iVar2 != 0)) {
    return iVar2;
  }
  uVar4 = *(int *)(param_1 + 0x10) + 1;
  uVar1 = **(uint **)(param_1 + 0xc);
  if (uVar4 < uVar1) {
    piVar3 = (int *)((*(uint **)(param_1 + 0xc))[1] + 8 + uVar4 * 0x10);
    do {
      if ((*piVar3 != 0) && (iVar2 = *piVar3 + -4, iVar2 != 0)) {
        return iVar2;
      }
      uVar4 = uVar4 + 1;
      piVar3 = piVar3 + 4;
    } while (uVar4 < uVar1);
  }
  return 0;
}


/* 004c8b30 size=16 */

void __fastcall FUN_004c8b30(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}


/* 004c8b40 size=121 */

int * __thiscall FUN_004c8b40(void *this,int param_1)

{
  int *piVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004caf6b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(int *)this = param_1;
  piVar1 = (int *)FUN_00430de0(param_1 * 0x10 + 4);
  local_4 = 0;
  if (piVar1 == (int *)0x0) {
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    *piVar1 = param_1;
    FUN_004bd127(piVar1 + 1,0x10,param_1,&LAB_004c8bc0);
    *(int **)((int)this + 4) = piVar1 + 1;
  }
  ExceptionList = local_c;
  return this;
}


/* 004c8bd0 size=39 */

void __fastcall FUN_004c8bd0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4);
  if (iVar1 != 0) {
    FUN_004bd049(iVar1,0x10,*(int *)(iVar1 + -4),FUN_004a82f0);
    FUN_00430df0((undefined *)(iVar1 + -4));
  }
  return;
}


/* 004c8c00 size=52 */

void __thiscall FUN_004c8c00(void *this,undefined4 *param_1)

{
  int iVar1;
  int *piVar2;
  
  param_1[3] = this;
  iVar1 = (**(code **)*param_1)();
  param_1[4] = iVar1;
  if (param_1 == (undefined4 *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = param_1 + 1;
  }
  FUN_004b4f00((void *)(iVar1 * 0x10 + 8 + *(int *)((int)this + 4)),piVar2);
  return;
}


/* 004c8c40 size=37 */

void __thiscall FUN_004c8c40(void *this,int param_1)

{
  int *piVar1;
  
  if (param_1 == 0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1 = (int *)(param_1 + 4);
  }
  FUN_004b4f60((void *)(*(int *)(param_1 + 0x10) * 0x10 + 8 + *(int *)((int)this + 4)),piVar1);
  return;
}


/* 004c8c70 size=36 */

int __fastcall FUN_004c8c70(uint *param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = 0;
  piVar2 = (int *)(param_1[1] + 8);
  do {
    if (*piVar2 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *piVar2 + -4;
    }
    uVar3 = uVar3 + 1;
    piVar2 = piVar2 + 4;
  } while ((iVar1 == 0) && (uVar3 < *param_1));
  return;
}


/* 004c8ca0 size=29 */

int __thiscall FUN_004c8ca0(void *this,int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 * 0x10 + 8 + *(int *)((int)this + 4));
  if (iVar1 == 0) {
    return 0;
  }
  return iVar1 + -4;
}


/* 004c8cc0 size=42 */

void __thiscall FUN_004c8cc0(void *this,int param_1)

{
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)((int)this + 4);
  *(undefined4 *)(param_1 + 8) = 0;
  if (*(int *)((int)this + 4) == 0) {
    *(int *)((int)this + 8) = param_1;
    *(int *)((int)this + 4) = param_1;
    return;
  }
  *(int *)(*(int *)((int)this + 4) + 8) = param_1;
  *(int *)((int)this + 4) = param_1;
  return;
}


/* 004c8cf0 size=52 */

void __thiscall FUN_004c8cf0(void *this,int param_1)

{
  if (*(int *)(param_1 + 8) == 0) {
    *(undefined4 *)((int)this + 4) = *(undefined4 *)(param_1 + 4);
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 8) + 4) = *(undefined4 *)(param_1 + 4);
  }
  if (*(int *)(param_1 + 4) == 0) {
    *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 8);
    return;
  }
  *(undefined4 *)(*(int *)(param_1 + 4) + 8) = *(undefined4 *)(param_1 + 8);
  return;
}


/* 004c8d30 size=308 */

/* WARNING: Variable defined which should be unmapped: param_1 */

uint * __cdecl FUN_004c8d30(uint *param_1)

{
  char cVar1;
  size_t _Size;
  int iVar2;
  uint *puVar3;
  bool bVar4;
  LPWSTR local_c;
  
  local_c = (LPWSTR)0x0;
  if (DAT_004ecd78 == 0) {
    cVar1 = (char)*param_1;
    puVar3 = param_1;
    while (cVar1 != '\0') {
      cVar1 = (char)*puVar3;
      if (('`' < cVar1) && (cVar1 < '{')) {
        *(char *)puVar3 = cVar1 + -0x20;
      }
      puVar3 = (uint *)((int)puVar3 + 1);
      cVar1 = *(char *)puVar3;
    }
  }
  else {
    InterlockedIncrement((LONG *)&DAT_004ed28c);
    bVar4 = DAT_004ed288 == 0;
    if (!bVar4) {
      InterlockedDecrement((LONG *)&DAT_004ed28c);
      FUN_004bf7a0(0x13);
    }
    if (DAT_004ecd78 == 0) {
      if (bVar4) {
        InterlockedDecrement((LONG *)&DAT_004ed28c);
      }
      else {
        FUN_004bf801(0x13);
      }
      cVar1 = (char)*param_1;
      puVar3 = param_1;
      while (cVar1 != '\0') {
        cVar1 = (char)*puVar3;
        if (('`' < cVar1) && (cVar1 < '{')) {
          *(char *)puVar3 = cVar1 + -0x20;
        }
        puVar3 = (uint *)((int)puVar3 + 1);
        cVar1 = *(char *)puVar3;
      }
    }
    else {
      _Size = FUN_004c3208(DAT_004ecd78,0x200,(char *)param_1,-1,(LPWSTR)0x0,0,0,1);
      if (((_Size != 0) && (local_c = _malloc(_Size), local_c != (LPWSTR)0x0)) &&
         (iVar2 = FUN_004c3208(DAT_004ecd78,0x200,(char *)param_1,-1,local_c,_Size,0,1), iVar2 != 0)
         ) {
        FUN_004c17f0(param_1,(uint *)local_c);
      }
      if (bVar4) {
        InterlockedDecrement((LONG *)&DAT_004ed28c);
      }
      else {
        FUN_004bf801(0x13);
      }
      FUN_004b9d3f((undefined *)local_c);
    }
  }
  return param_1;
}


/* 004c8e64 size=308 */

/* WARNING: Variable defined which should be unmapped: param_1 */

uint * __cdecl FUN_004c8e64(uint *param_1)

{
  char cVar1;
  size_t _Size;
  int iVar2;
  uint *puVar3;
  bool bVar4;
  LPWSTR local_c;
  
  local_c = (LPWSTR)0x0;
  if (DAT_004ecd78 == 0) {
    cVar1 = (char)*param_1;
    puVar3 = param_1;
    while (cVar1 != '\0') {
      cVar1 = (char)*puVar3;
      if (('@' < cVar1) && (cVar1 < '[')) {
        *(char *)puVar3 = cVar1 + ' ';
      }
      puVar3 = (uint *)((int)puVar3 + 1);
      cVar1 = *(char *)puVar3;
    }
  }
  else {
    InterlockedIncrement((LONG *)&DAT_004ed28c);
    bVar4 = DAT_004ed288 == 0;
    if (!bVar4) {
      InterlockedDecrement((LONG *)&DAT_004ed28c);
      FUN_004bf7a0(0x13);
    }
    if (DAT_004ecd78 == 0) {
      if (bVar4) {
        InterlockedDecrement((LONG *)&DAT_004ed28c);
      }
      else {
        FUN_004bf801(0x13);
      }
      cVar1 = (char)*param_1;
      puVar3 = param_1;
      while (cVar1 != '\0') {
        cVar1 = (char)*puVar3;
        if (('@' < cVar1) && (cVar1 < '[')) {
          *(char *)puVar3 = cVar1 + ' ';
        }
        puVar3 = (uint *)((int)puVar3 + 1);
        cVar1 = *(char *)puVar3;
      }
    }
    else {
      _Size = FUN_004c3208(DAT_004ecd78,0x100,(char *)param_1,-1,(LPWSTR)0x0,0,0,1);
      if (((_Size != 0) && (local_c = _malloc(_Size), local_c != (LPWSTR)0x0)) &&
         (iVar2 = FUN_004c3208(DAT_004ecd78,0x100,(char *)param_1,-1,local_c,_Size,0,1), iVar2 != 0)
         ) {
        FUN_004c17f0(param_1,(uint *)local_c);
      }
      if (bVar4) {
        InterlockedDecrement((LONG *)&DAT_004ed28c);
      }
      else {
        FUN_004bf801(0x13);
      }
      FUN_004b9d3f((undefined *)local_c);
    }
  }
  return param_1;
}


