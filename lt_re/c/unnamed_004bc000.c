/* lithtech.exe decompilation - unnamed_004bc000 */
#include "ghidra_types.h"

/* 004bc030 size=20 */

void FUN_004bc030(void)

{
  float10 in_ST0;
  double dVar1;
  
  dVar1 = (double)in_ST0;
  FUN_004c16e8(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  FUN_004bc04d(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  return;
}


/* 004bc04d size=170 */

/* FUN_004bc04d: lifted from original x86 -> lt_lifted.c */


/* 004bc0ea size=81 */

int __cdecl FUN_004bc0ea(undefined1 *param_1,int param_2,byte *param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  local_1c = param_1;
  local_24 = param_1;
  local_18 = 0x42;
  local_20 = param_2;
  iVar1 = FUN_004bf92e((int *)&local_24,param_3,&param_4);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_004bf816(0,(int *)&local_24);
  }
  else {
    *local_24 = 0;
  }
  return iVar1;
}


/* 004bc13b size=119 */

HANDLE __cdecl FUN_004bc13b(int param_1,SIZE_T param_2,int param_3)

{
  int *lpThreadId;
  HANDLE hThread;
  DWORD DVar1;
  
  DVar1 = 0;
  lpThreadId = FUN_004c34bf(1,0x74);
  if (lpThreadId != (int *)0x0) {
    FUN_004c04cf((int)lpThreadId);
    lpThreadId[0x12] = param_1;
    lpThreadId[0x13] = param_3;
    hThread = CreateThread((LPSECURITY_ATTRIBUTES)0x0,param_2,FUN_004bc1b2,lpThreadId,4,
                           (LPDWORD)lpThreadId);
    lpThreadId[1] = (int)hThread;
    if ((hThread != (HANDLE)0x0) && (DVar1 = ResumeThread(hThread), DVar1 != 0xffffffff)) {
      return hThread;
    }
    DVar1 = GetLastError();
  }
  FUN_004b9d3f((undefined *)lpThreadId);
  if (DVar1 != 0) {
    FUN_004c0959(DVar1);
  }
  return (HANDLE)0xffffffff;
}


/* 004bc1b2 size=116 */

undefined4 FUN_004bc1b2(LPVOID param_1)

{
  BOOL BVar1;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf048;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  BVar1 = TlsSetValue(DAT_004e3220,param_1);
  if (BVar1 == 0) {
    __amsg_exit(0x10);
  }
  if (PTR_FUN_004e0dc4 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004e0dc4)();
  }
  local_8 = 0;
  (**(code **)((int)param_1 + 0x48))(*(undefined4 *)((int)param_1 + 0x4c));
  FUN_004bc245();
  ExceptionList = local_14;
  return 0;
}


/* 004bc245 size=61 */

void FUN_004bc245(void)

{
  DWORD *pDVar1;
  
  if (PTR_FUN_004e0dc8 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004e0dc8)();
  }
  pDVar1 = FUN_004c04e2();
  if (pDVar1 == (DWORD *)0x0) {
    __amsg_exit(0x10);
  }
  if ((HANDLE)pDVar1[1] != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)pDVar1[1]);
  }
  FUN_004c0549((undefined *)pDVar1);
                    /* WARNING: Subroutine does not return */
  ExitThread(0);
}


/* 004bc284 size=53 */

int __cdecl FUN_004bc284(ushort *param_1,ushort *param_2)

{
  int iVar1;
  ushort uVar2;
  
  uVar2 = *param_2;
  while ((iVar1 = (uint)*param_1 - (uint)uVar2, iVar1 == 0 && (uVar2 != 0))) {
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    uVar2 = *param_2;
  }
  if (iVar1 < 0) {
    return -1;
  }
  if (0 < iVar1) {
    iVar1 = 1;
  }
  return iVar1;
}


/* 004bc2b9 size=42 */

void __cdecl FUN_004bc2b9(short *param_1,short *param_2)

{
  short sVar1;
  
  sVar1 = *param_1;
  while (sVar1 != 0) {
    param_1 = param_1 + 1;
    sVar1 = *param_1;
  }
  do {
    sVar1 = *param_2;
    *param_1 = sVar1;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  } while (sVar1 != 0);
  return;
}


/* 004bc2e3 size=37 */

void __cdecl FUN_004bc2e3(short *param_1,short *param_2)

{
  short sVar1;
  
  sVar1 = *param_2;
  *param_1 = sVar1;
  while( true ) {
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    if (sVar1 == 0) break;
    sVar1 = *param_2;
    *param_1 = sVar1;
  }
  return;
}


/* 004bc308 size=61 */

short * __cdecl FUN_004bc308(short *param_1,short *param_2,int param_3)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  short *psVar4;
  
  if (param_3 != 0) {
    psVar4 = param_1;
    do {
      sVar1 = *param_2;
      *psVar4 = sVar1;
      psVar4 = psVar4 + 1;
      param_2 = param_2 + 1;
      if (sVar1 == 0) break;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
    if ((param_3 != 0) && (uVar2 = param_3 - 1, uVar2 != 0)) {
      for (uVar3 = uVar2 >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
        psVar4[0] = 0;
        psVar4[1] = 0;
        psVar4 = psVar4 + 2;
      }
      for (uVar2 = (uint)((uVar2 & 1) != 0); uVar2 != 0; uVar2 = uVar2 - 1) {
        *psVar4 = 0;
        psVar4 = psVar4 + 1;
      }
    }
  }
  return param_1;
}


/* 004bc345 size=93 */

uint __cdecl FUN_004bc345(LPSTR param_1,LPCWSTR param_2,uint param_3)

{
  uint uVar1;
  bool bVar2;
  
  InterlockedIncrement((LONG *)&DAT_004ed28c);
  bVar2 = DAT_004ed288 != 0;
  if (bVar2) {
    InterlockedDecrement((LONG *)&DAT_004ed28c);
    FUN_004bf7a0(0x13);
  }
  uVar1 = FUN_004bc3a2(param_1,param_2,param_3);
  if (bVar2) {
    FUN_004bf801(0x13);
  }
  else {
    InterlockedDecrement((LONG *)&DAT_004ed28c);
  }
  return uVar1;
}


/* 004bc3a2 size=431 */

uint __cdecl FUN_004bc3a2(LPSTR param_1,LPCWSTR param_2,uint param_3)

{
  char cVar1;
  WCHAR WVar2;
  int iVar3;
  DWORD DVar4;
  DWORD *pDVar5;
  int iVar6;
  uint uVar7;
  BOOL local_c;
  CHAR local_6 [2];
  
  uVar7 = 0;
  local_c = 0;
  if (param_1 == (LPSTR)0x0) {
    if (DAT_004ecd78 == 0) {
      uVar7 = FUN_004bc580(param_2);
      return uVar7;
    }
    uVar7 = WideCharToMultiByte(DAT_004ecd88,0x220,param_2,-1,(LPSTR)0x0,0,(LPCSTR)0x0,&local_c);
    if ((uVar7 != 0) && (local_c == 0)) {
LAB_004bc53b:
      return uVar7 - 1;
    }
  }
  else {
    if (param_3 == 0) {
      return 0;
    }
    if (DAT_004ecd78 == 0) {
      if (param_3 != 0) {
        do {
          if (0xff < (ushort)*param_2) goto LAB_004bc53e;
          param_1[uVar7] = (CHAR)*param_2;
          WVar2 = *param_2;
          param_2 = param_2 + 1;
        } while ((WVar2 != L'\0') && (uVar7 = uVar7 + 1, uVar7 < param_3));
      }
      return uVar7;
    }
    if (DAT_004e36dc == 1) {
      iVar3 = 0;
      if (param_3 != 0) {
        iVar3 = FUN_004bc551(param_2,param_3);
      }
      uVar7 = WideCharToMultiByte(DAT_004ecd88,0x220,param_2,iVar3,param_1,iVar3,(LPCSTR)0x0,
                                  &local_c);
      if ((uVar7 != 0) && (local_c == 0)) {
        if (param_1[uVar7 - 1] != '\0') {
          return uVar7;
        }
        goto LAB_004bc53b;
      }
    }
    else {
      iVar3 = WideCharToMultiByte(DAT_004ecd88,0x220,param_2,-1,param_1,param_3,(LPCSTR)0x0,&local_c
                                 );
      if (iVar3 == 0) {
        if (local_c == 0) {
          DVar4 = GetLastError();
          uVar7 = 0;
          if (DVar4 == 0x7a) {
            while( true ) {
              if (param_3 <= uVar7) {
                return uVar7;
              }
              iVar3 = WideCharToMultiByte(DAT_004ecd88,0,param_2,1,local_6,DAT_004e36dc,(LPCSTR)0x0,
                                          &local_c);
              if ((iVar3 == 0) || (local_c != 0)) break;
              if (param_3 < iVar3 + uVar7) {
                return uVar7;
              }
              iVar6 = 0;
              if (0 < iVar3) {
                do {
                  cVar1 = local_6[iVar6];
                  param_1[uVar7] = cVar1;
                  if (cVar1 == '\0') {
                    return uVar7;
                  }
                  iVar6 = iVar6 + 1;
                  uVar7 = uVar7 + 1;
                } while (iVar6 < iVar3);
              }
              param_2 = param_2 + 1;
            }
          }
        }
      }
      else if (local_c == 0) {
        return iVar3 - 1;
      }
    }
  }
LAB_004bc53e:
  pDVar5 = FUN_004c09cc();
  *pDVar5 = 0x2a;
  return 0xffffffff;
}


/* 004bc551 size=47 */

int __cdecl FUN_004bc551(short *param_1,int param_2)

{
  short *psVar1;
  int iVar2;
  
  psVar1 = param_1;
  iVar2 = param_2;
  if (param_2 != 0) {
    do {
      if (*psVar1 == 0) break;
      psVar1 = psVar1 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if ((iVar2 != 0) && (*psVar1 == 0)) {
      return ((int)psVar1 - (int)param_1 >> 1) + 1;
    }
  }
  return param_2;
}


/* 004bc580 size=29 */

int __cdecl FUN_004bc580(short *param_1)

{
  short sVar1;
  short *psVar2;
  
  sVar1 = *param_1;
  psVar2 = param_1;
  while (psVar2 = psVar2 + 1, sVar1 != 0) {
    sVar1 = *psVar2;
  }
  return ((int)psVar2 - (int)param_1 >> 1) + -1;
}


/* 004bc5aa size=10 */

int __fastcall FUN_004bc5aa(undefined4 param_1)

{
  __cintrindisp2(param_1,0x4e0e10);
  return;
}


/* 004bc5d2 size=340 */

void __cdecl FUN_004bc5d2(int *param_1,undefined4 *param_2,uint param_3,undefined *param_4)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  undefined4 local_fc [30];
  int local_84 [30];
  int *local_c;
  int local_8;
  
  if ((param_2 < (undefined4 *)0x2) || (param_3 == 0)) {
    return;
  }
  local_8 = 0;
  iVar4 = (int)param_2 + -1;
  param_2 = local_fc;
  piVar5 = (int *)(iVar4 * param_3 + (int)param_1);
  piVar3 = param_1;
  param_1 = local_84;
LAB_004bc611:
  uVar2 = (uint)((int)piVar5 - (int)piVar3) / param_3 + 1;
  if (8 < uVar2) {
    FUN_004bc774((undefined1 *)((uVar2 >> 1) * param_3 + (int)piVar3),(undefined1 *)piVar3,param_3);
    piVar6 = (int *)(param_3 + (int)piVar5);
    local_c = piVar3;
LAB_004bc668:
    local_c = (int *)((int)local_c + param_3);
    if (local_c <= piVar5) goto code_r0x004bc675;
    goto LAB_004bc680;
  }
  FUN_004bc726((undefined1 *)piVar3,(undefined1 *)piVar5,param_3,param_4);
  goto LAB_004bc630;
code_r0x004bc675:
  iVar4 = (*(code *)param_4)(local_c,piVar3);
  if (iVar4 < 1) goto LAB_004bc668;
LAB_004bc680:
  do {
    piVar6 = (int *)((int)piVar6 - param_3);
    if (piVar6 <= piVar3) break;
    iVar4 = (*(code *)param_4)(piVar6,piVar3);
  } while (-1 < iVar4);
  if (local_c <= piVar6) {
    FUN_004bc774((undefined1 *)local_c,(undefined1 *)piVar6,param_3);
    goto LAB_004bc668;
  }
  FUN_004bc774((undefined1 *)piVar3,(undefined1 *)piVar6,param_3);
  piVar1 = local_c;
  if ((int)((int)piVar6 + (-1 - (int)piVar3)) < (int)piVar5 - (int)local_c) {
    if (local_c < piVar5) {
      local_8 = local_8 + 1;
      *param_2 = local_c;
      *param_1 = (int)piVar5;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
    if ((int *)(param_3 + (int)piVar3) < piVar6) {
      piVar5 = (int *)((int)piVar6 - param_3);
      goto LAB_004bc611;
    }
  }
  else {
    if ((int *)((int)piVar3 + param_3) < piVar6) {
      local_8 = local_8 + 1;
      *param_2 = piVar3;
      *param_1 = (int)piVar6 - param_3;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
    if (piVar1 < piVar5) {
      piVar3 = piVar1;
      goto LAB_004bc611;
    }
  }
LAB_004bc630:
  local_8 = local_8 + -1;
  param_2 = param_2 + -1;
  param_1 = param_1 + -1;
  if (local_8 < 0) {
    return;
  }
  piVar5 = (int *)*param_1;
  piVar3 = (int *)*param_2;
  goto LAB_004bc611;
}


/* 004bc726 size=78 */

void __cdecl FUN_004bc726(undefined1 *param_1,undefined1 *param_2,int param_3,undefined *param_4)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  
  for (; param_1 < param_2; param_2 = param_2 + -param_3) {
    puVar2 = param_1;
    puVar3 = param_1;
    while (puVar3 = puVar3 + param_3, puVar3 <= param_2) {
      iVar1 = (*(code *)param_4)(puVar3,puVar2);
      if (0 < iVar1) {
        puVar2 = puVar3;
      }
    }
    FUN_004bc774(puVar2,param_2,param_3);
  }
  return;
}


/* 004bc774 size=44 */

void __cdecl FUN_004bc774(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  undefined1 uVar1;
  
  if ((param_1 != param_2) && (param_3 != 0)) {
    do {
      uVar1 = *param_1;
      *param_1 = *param_2;
      param_1 = param_1 + 1;
      *param_2 = uVar1;
      param_2 = param_2 + 1;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}


/* 004bc7a0 size=23 */

byte * __cdecl FUN_004bc7a0(byte *param_1)

{
  byte *pbVar1;
  
  pbVar1 = param_1 + 1;
  if ((*(byte *)((int)&DAT_004ed180 + *param_1 + 1) & 4) != 0) {
    pbVar1 = param_1 + 2;
  }
  return pbVar1;
}


/* 004bc7b7 size=175 */

int __cdecl FUN_004bc7b7(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  ushort uVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  
  if (DAT_004ed06c == 0) {
    iVar3 = _strcmp((char *)param_1,(char *)param_2);
  }
  else {
    FUN_004bf7a0(0x19);
    pbVar5 = param_2;
    do {
      (*(uint16_t*)((char*)&param_2+0)) = (ushort)*param_1;
      pbVar7 = param_1 + 1;
      if ((*(byte *)((int)&DAT_004ed180 + (ushort)param_2 + 1) & 4) != 0) {
        bVar1 = *pbVar7;
        if (bVar1 == 0) {
          (*(uint16_t*)((char*)&param_2+0)) = 0;
        }
        else {
          pbVar7 = param_1 + 2;
          (*(uint16_t*)((char*)&param_2+0)) = CONCAT11(*param_1,bVar1);
        }
      }
      bVar1 = *pbVar5;
      uVar4 = (ushort)bVar1;
      pbVar6 = pbVar5 + 1;
      if ((*(byte *)((int)&DAT_004ed180 + bVar1 + 1) & 4) != 0) {
        bVar2 = *pbVar6;
        if (bVar2 == 0) {
          uVar4 = 0;
        }
        else {
          pbVar6 = pbVar5 + 2;
          uVar4 = CONCAT11(bVar1,bVar2);
        }
      }
      if ((ushort)param_2 != uVar4) {
        FUN_004bf801(0x19);
        return (-(uint)(uVar4 < (ushort)param_2) & 2) - 1;
      }
      pbVar5 = pbVar6;
      param_1 = pbVar7;
    } while ((ushort)param_2 != 0);
    FUN_004bf801(0x19);
    iVar3 = 0;
  }
  return iVar3;
}


/* 004bc866 size=405 */

uint __thiscall FUN_004bc866(void *this,byte *param_1,byte *param_2)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  ushort uVar6;
  ushort uVar7;
  byte *local_10;
  byte *local_c;
  byte local_8;
  undefined1 local_7;
  
  if (DAT_004ed06c == 0) {
    uVar2 = FUN_004c4c00(this,param_1,param_2);
    return uVar2;
  }
  FUN_004bf7a0(0x19);
  local_10 = param_2 + -1;
  local_c = param_1 + -1;
  do {
    uVar2 = (uint)*param_1;
    pbVar5 = param_1 + 1;
    pbVar1 = local_c + 1;
    if ((*(byte *)((int)&DAT_004ed180 + uVar2 + 1) & 4) == 0) {
      if ((*(byte *)((int)&DAT_004ed180 + uVar2 + 1) & 0x10) == 0x10) {
        uVar2 = (uint)(byte)(&DAT_004ed080)[uVar2];
        param_1 = pbVar5;
        local_c = pbVar1;
      }
      else {
        param_1 = pbVar5;
        local_c = pbVar1;
      }
    }
    else if (*pbVar5 == 0) {
      uVar2 = 0;
      param_1 = pbVar5;
      local_c = pbVar1;
    }
    else {
      iVar4 = FUN_004c3208(DAT_004ed284,0x200,(char *)pbVar1,2,(LPWSTR)&local_8,2,DAT_004ed058,1);
      if (iVar4 == 1) {
        uVar2 = (uint)local_8;
      }
      else {
        if (iVar4 != 2) goto LAB_004bc9ca;
        uVar2 = (uint)CONCAT11(local_8,local_7);
      }
      param_1 = param_1 + 2;
      local_c = local_c + 2;
    }
    uVar3 = (uint)*param_2;
    uVar6 = (ushort)*param_2;
    pbVar5 = param_2 + 1;
    pbVar1 = local_10 + 1;
    if ((*(byte *)((int)&DAT_004ed180 + uVar3 + 1) & 4) == 0) {
      param_2 = pbVar5;
      local_10 = pbVar1;
      if ((*(byte *)((int)&DAT_004ed180 + uVar3 + 1) & 0x10) == 0x10) {
        uVar6 = (ushort)(byte)(&DAT_004ed080)[uVar3];
      }
    }
    else if (*pbVar5 == 0) {
      uVar6 = 0;
      param_2 = pbVar5;
      local_10 = pbVar1;
    }
    else {
      iVar4 = FUN_004c3208(DAT_004ed284,0x200,(char *)pbVar1,2,(LPWSTR)&local_8,2,DAT_004ed058,1);
      if (iVar4 == 1) {
        uVar6 = (ushort)local_8;
      }
      else {
        if (iVar4 != 2) {
LAB_004bc9ca:
          FUN_004bf801(0x19);
          return 0x7fffffff;
        }
        uVar6 = CONCAT11(local_8,local_7);
      }
      param_2 = param_2 + 2;
      local_10 = local_10 + 2;
    }
    uVar7 = (ushort)uVar2;
    if (uVar7 != uVar6) {
      FUN_004bf801(0x19);
      return (-(uint)(uVar6 < uVar7) & 2) - 1;
    }
    if (uVar7 == 0) {
      FUN_004bf801(0x19);
      return 0;
    }
  } while( true );
}


/* 004bcb28 size=35 */

void __cdecl FUN_004bcb28(DWORD param_1)

{
  if (DAT_004eccd4 == 1) {
    FUN_004c5160();
  }
  FUN_004c5199(param_1);
                    /* WARNING: Subroutine does not return */
  ExitProcess(0xff);
}


/* 004bcb4c size=41 */

/* FUN_004bcb4c: lifted from original x86 -> lt_lifted.c */


/* 004bcb75 size=28 */

undefined4 * __thiscall FUN_004bcb75(void *this,byte param_1)

{
  FUN_004bcb4c(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004bcb91 size=220 */

int __cdecl FUN_004bcb91(int *param_1)

{
  DWORD DVar1;
  int iVar2;
  _TIME_ZONE_INFORMATION local_d0;
  _SYSTEMTIME local_24;
  _SYSTEMTIME local_14;
  
  GetLocalTime(&local_14);
  GetSystemTime(&local_24);
  if (local_24.wMinute == (*(uint16_t*)((char*)&DAT_004ecce8+2))) {
    if (local_24.wHour == (WORD)DAT_004ecce8) {
      if (local_24.wDay == (*(uint16_t*)((char*)&DAT_004ecce4+2))) {
        if (local_24.wMonth == (*(uint16_t*)((char*)&DAT_004ecce0+2))) {
          if (local_24.wYear == (WORD)DAT_004ecce0) goto LAB_004bcc3b;
        }
      }
    }
  }
  DVar1 = GetTimeZoneInformation(&local_d0);
  if (DVar1 == 0xffffffff) {
    DAT_004eccd8 = -1;
  }
  else if (((DVar1 == 2) && (local_d0.DaylightDate.wMonth != 0)) && (local_d0.DaylightBias != 0)) {
    DAT_004eccd8 = 1;
  }
  else {
    DAT_004eccd8 = 0;
  }
  (*(uint16_t*)((char*)&DAT_004ecce0+0)) = local_24.wYear;
  (*(uint16_t*)((char*)&DAT_004ecce0+2)) = local_24.wMonth;
  (*(uint16_t*)((char*)&DAT_004ecce4+0)) = local_24.wDayOfWeek;
  (*(uint16_t*)((char*)&DAT_004ecce4+2)) = local_24.wDay;
  (*(uint16_t*)((char*)&DAT_004ecce8+0)) = local_24.wHour;
  (*(uint16_t*)((char*)&DAT_004ecce8+2)) = local_24.wMinute;
  (*(uint16_t*)((char*)&DAT_004eccec+0)) = local_24.wSecond;
  (*(uint16_t*)((char*)&DAT_004eccec+2)) = local_24.wMilliseconds;
LAB_004bcc3b:
  iVar2 = FUN_004c18e0((uint)local_14.wYear,(uint)local_14.wMonth,(uint)local_14.wDay,
                       (uint)local_14.wHour,(uint)local_14.wMinute,(uint)local_14.wSecond,
                       DAT_004eccd8);
  if (param_1 != (int *)0x0) {
    *param_1 = iVar2;
  }
  return;
}


/* 004bcc6d size=17 */

void __fastcall FUN_004bcc6d(undefined4 *param_1)

{
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = &PTR_FUN_004cf070;
  return;
}


/* 004bcc7e size=28 */

exception * __thiscall FUN_004bcc7e(void *this,byte param_1)

{
  exception__dtor_exception(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004bcc9a size=61 */

undefined4 * __thiscall FUN_004bcc9a(void *this,undefined4 *param_1)

{
  size_t sVar1;
  uint *puVar2;
  
  *(undefined ***)this = &PTR_FUN_004cf070;
  sVar1 = _strlen((char *)*param_1);
  puVar2 = (uint *)FUN_00430de0(sVar1 + 1);
  *(uint **)((int)this + 4) = puVar2;
  if (puVar2 != (uint *)0x0) {
    FUN_004c17f0(puVar2,(uint *)*param_1);
  }
  *(undefined4 *)((int)this + 8) = 1;
  return this;
}


/* 004bccd7 size=74 */

undefined4 * __thiscall FUN_004bccd7(void *this,int param_1)

{
  int iVar1;
  size_t sVar2;
  uint *puVar3;
  
  *(undefined ***)this = &PTR_FUN_004cf070;
  iVar1 = *(int *)(param_1 + 8);
  *(int *)((int)this + 8) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)((int)this + 4) = *(undefined4 *)(param_1 + 4);
  }
  else {
    sVar2 = _strlen(*(char **)(param_1 + 4));
    puVar3 = (uint *)FUN_00430de0(sVar2 + 1);
    *(uint **)((int)this + 4) = puVar3;
    if (puVar3 != (uint *)0x0) {
      FUN_004c17f0(puVar3,*(uint **)(param_1 + 4));
    }
  }
  return this;
}


/* 004bcd7e size=49 */

uint __cdecl FUN_004bcd7e(undefined4 *param_1)

{
  int *piVar1;
  uint uVar2;
  
  FUN_004bcfa5((uint)param_1);
  piVar1 = param_1 + 1;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    uVar2 = FUN_004c05e9(param_1);
  }
  else {
    uVar2 = (uint)*(byte *)*param_1;
    *param_1 = (byte *)*param_1 + 1;
  }
  FUN_004bcff7((uint)param_1);
  return uVar2;
}


/* 004bcdaf size=111 */

uint __cdecl FUN_004bcdaf(uint param_1)

{
  void *extraout_ECX;
  bool bVar1;
  void *this;
  
  if (DAT_004ecd78 == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    InterlockedIncrement((LONG *)&DAT_004ed28c);
    bVar1 = DAT_004ed288 != 0;
    this = extraout_ECX;
    if (bVar1) {
      InterlockedDecrement((LONG *)&DAT_004ed28c);
      this = (void *)0x13;
      FUN_004bf7a0(0x13);
    }
    param_1 = FUN_004bce1e(this,param_1);
    if (bVar1) {
      FUN_004bf801(0x13);
    }
    else {
      InterlockedDecrement((LONG *)&DAT_004ed28c);
    }
  }
  return param_1;
}


/* 004bce1e size=203 */

/* FUN_004bce1e: lifted from original x86 -> lt_lifted.c */


/* 004bcfa5 size=47 */

void __cdecl FUN_004bcfa5(uint param_1)

{
  if ((param_1 < 0x4e0e88) || (0x4e10e8 < param_1)) {
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
    return;
  }
  FUN_004bf7a0(((int)(param_1 - 0x4e0e88) >> 5) + 0x1c);
  return;
}


/* 004bcfd4 size=35 */

void __cdecl FUN_004bcfd4(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    FUN_004bf7a0(param_1 + 0x1c);
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)(param_2 + 0x20));
  return;
}


/* 004bcff7 size=47 */

void __cdecl FUN_004bcff7(uint param_1)

{
  if ((param_1 < 0x4e0e88) || (0x4e10e8 < param_1)) {
    LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
    return;
  }
  FUN_004bf801(((int)(param_1 - 0x4e0e88) >> 5) + 0x1c);
  return;
}


/* 004bd026 size=35 */

void __cdecl FUN_004bd026(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    FUN_004bf801(param_1 + 0x1c);
    return;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_2 + 0x20));
  return;
}


/* 004bd049 size=104 */

void FUN_004bd049(undefined4 param_1,undefined4 param_2,int param_3,undefined *param_4)

{
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004cf0b0;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  while( true ) {
    param_3 = param_3 + -1;
    if (param_3 < 0) break;
    (*(code *)param_4)();
  }
  local_8 = 0xffffffff;
  FUN_004bd0b1();
  ExceptionList = local_14;
  return;
}


/* 004bd0b1 size=24 */

void FUN_004bd0b1(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x1c) == 0) {
    FUN_004bd0c9(*(undefined4 *)(unaff_EBP + 8),*(undefined4 *)(unaff_EBP + 0xc),
                 *(int *)(unaff_EBP + 0x10),*(undefined **)(unaff_EBP + 0x14));
  }
  return;
}


/* 004bd0c9 size=81 */

void FUN_004bd0c9(undefined4 param_1,undefined4 param_2,int param_3,undefined *param_4)

{
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004cf0c0;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  while( true ) {
    param_3 = param_3 + -1;
    if (param_3 < 0) break;
    (*(code *)param_4)();
  }
  ExceptionList = local_14;
  return;
}


/* 004bd127 size=106 */

void FUN_004bd127(undefined4 param_1,undefined4 param_2,int param_3,undefined *param_4)

{
  int local_20;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004cf0d0;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  for (local_20 = 0; local_20 < param_3; local_20 = local_20 + 1) {
    (*(code *)param_4)();
  }
  local_8 = 0xffffffff;
  FUN_004bd191();
  ExceptionList = local_14;
  return;
}


/* 004bd191 size=24 */

void FUN_004bd191(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x20) == 0) {
    FUN_004bd0c9(*(undefined4 *)(unaff_EBP + 8),*(undefined4 *)(unaff_EBP + 0xc),
                 *(int *)(unaff_EBP + -0x1c),*(undefined **)(unaff_EBP + 0x18));
  }
  return;
}


/* 004bd1d1 size=327 */

void __cdecl FUN_004bd1d1(byte *param_1,byte *param_2,byte *param_3,byte *param_4,byte *param_5)

{
  byte bVar1;
  size_t sVar2;
  byte *pbVar3;
  byte *local_8;
  
  local_8 = (byte *)0x0;
  sVar2 = _strlen((char *)param_1);
  if ((sVar2 == 0) || (param_1[1] != 0x3a)) {
    pbVar3 = param_1;
    if (param_2 != (byte *)0x0) {
      *param_2 = 0;
    }
  }
  else {
    if (param_2 != (byte *)0x0) {
      FUN_004c53d1(param_2,param_1,2);
      param_2[2] = 0;
    }
    pbVar3 = param_1 + 2;
  }
  param_2 = (byte *)0x0;
  param_1 = pbVar3;
  if (*pbVar3 != 0) {
    do {
      bVar1 = *param_1;
      if ((*(byte *)((int)&DAT_004ed180 + bVar1 + 1) & 4) == 0) {
        if ((bVar1 == 0x2f) || (bVar1 == 0x5c)) {
          param_2 = param_1 + 1;
        }
        else if (bVar1 == 0x2e) {
          local_8 = param_1;
        }
      }
      else {
        param_1 = param_1 + 1;
      }
      param_1 = param_1 + 1;
    } while (*param_1 != 0);
    if (param_2 != (byte *)0x0) {
      if (param_3 != (byte *)0x0) {
        sVar2 = (int)param_2 - (int)pbVar3;
        if (0xfe < sVar2) {
          sVar2 = 0xff;
        }
        FUN_004c53d1(param_3,pbVar3,sVar2);
        param_3[sVar2] = 0;
      }
      pbVar3 = param_2;
      goto LAB_004bd298;
    }
  }
  if (param_3 != (byte *)0x0) {
    *param_3 = 0;
  }
LAB_004bd298:
  if ((local_8 == (byte *)0x0) || (local_8 < pbVar3)) {
    if (param_4 != (byte *)0x0) {
      sVar2 = 0xff;
      if ((uint)((int)param_1 - (int)pbVar3) < 0xff) {
        sVar2 = (int)param_1 - (int)pbVar3;
      }
      FUN_004c53d1(param_4,pbVar3,sVar2);
      param_4[sVar2] = 0;
    }
    if (param_5 != (byte *)0x0) {
      *param_5 = 0;
    }
  }
  else {
    if (param_4 != (byte *)0x0) {
      sVar2 = (int)local_8 - (int)pbVar3;
      if (0xfe < sVar2) {
        sVar2 = 0xff;
      }
      FUN_004c53d1(param_4,pbVar3,sVar2);
      param_4[sVar2] = 0;
    }
    if (param_5 != (byte *)0x0) {
      sVar2 = 0xff;
      if ((uint)((int)param_1 - (int)local_8) < 0xff) {
        sVar2 = (int)param_1 - (int)local_8;
      }
      FUN_004c53d1(param_5,local_8,sVar2);
      param_5[sVar2] = 0;
    }
  }
  return;
}


/* 004bd318 size=184 */

uint __cdecl FUN_004bd318(byte param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  void *this;
  undefined *puVar5;
  undefined *this_00;
  
  pbVar2 = param_2;
  if (param_2[1] == 0x3a) {
    pbVar2 = param_2 + 2;
  }
  bVar1 = *pbVar2;
  if ((((bVar1 == 0x5c) || (bVar1 == 0x2f)) && (pbVar2[1] == 0)) ||
     (((param_1 & 0x10) != 0 || (uVar4 = 0x8000, bVar1 == 0)))) {
    uVar4 = 0x4040;
  }
  this = (void *)0x2e;
  uVar4 = uVar4 | (uint)(~param_1 & 1 | 2) << 7;
  pbVar2 = FUN_004c546b(param_2,0x2e);
  if (pbVar2 != (byte *)0x0) {
    puVar5 = &DAT_004cf0f4;
    uVar3 = FUN_004bc866(this,pbVar2,&DAT_004cf0f4);
    if (uVar3 != 0) {
      this_00 = &DAT_004cf0ec;
      uVar3 = FUN_004bc866(puVar5,pbVar2,&DAT_004cf0ec);
      if (uVar3 != 0) {
        puVar5 = &DAT_004cf0e4;
        uVar3 = FUN_004bc866(this_00,pbVar2,&DAT_004cf0e4);
        if (uVar3 != 0) {
          uVar3 = FUN_004bc866(puVar5,pbVar2,&DAT_004cf0dc);
          if (uVar3 != 0) goto LAB_004bd3b9;
        }
      }
    }
    uVar4 = uVar4 | 0x40;
  }
LAB_004bd3b9:
  return uVar4 >> 6 & 7 | uVar4 | uVar4 >> 3 & 0x38;
}


/* 004bd3d0 size=699 */

undefined4 __cdecl FUN_004bd3d0(byte *param_1,int *param_2)

{
  byte *pbVar1;
  DWORD *pDVar2;
  uint uVar3;
  uint *_Str;
  size_t sVar4;
  int iVar5;
  UINT UVar6;
  BOOL BVar7;
  DWORD DVar8;
  uint local_268 [65];
  _WIN32_FIND_DATAA local_164;
  int local_24;
  _FILETIME local_20;
  HANDLE local_18;
  _SYSTEMTIME local_14;
  
  pbVar1 = FUN_004c5640(param_1,&DAT_004cf100);
  if (pbVar1 != (byte *)0x0) {
LAB_004bd403:
    pDVar2 = FUN_004c09cc();
    *pDVar2 = 2;
    pDVar2 = FUN_004c09d5();
    *pDVar2 = 2;
    return 0xffffffff;
  }
  if (param_1[1] == 0x3a) {
    if ((*param_1 != 0) && (param_1[2] == 0)) goto LAB_004bd403;
    uVar3 = FUN_004c55c5((int)(char)*param_1);
    local_24 = uVar3 - 0x60;
  }
  else {
    local_24 = FUN_004c5582();
  }
  local_18 = FindFirstFileA((LPCSTR)param_1,&local_164);
  if (local_18 == (HANDLE)0xffffffff) {
    pbVar1 = FUN_004c5640(param_1,&DAT_004cf0fc);
    if ((((pbVar1 == (byte *)0x0) ||
         (_Str = FUN_004c54dd(local_268,(LPCSTR)param_1,0x104), _Str == (uint *)0x0)) ||
        ((sVar4 = _strlen((char *)_Str), sVar4 != 3 &&
         (iVar5 = FUN_004bd68b((char *)_Str), iVar5 == 0)))) ||
       (UVar6 = GetDriveTypeA((LPCSTR)_Str), UVar6 < 2)) {
      pDVar2 = FUN_004c09cc();
      *pDVar2 = 2;
      pDVar2 = FUN_004c09d5();
      *pDVar2 = 2;
      return 0xffffffff;
    }
    local_164.dwFileAttributes = 0x10;
    local_164.nFileSizeHigh = 0;
    local_164.nFileSizeLow = 0;
    local_164.cFileName[0] = '\0';
    iVar5 = FUN_004c18e0(0x7bc,1,1,0,0,0,-1);
    param_2[7] = iVar5;
    param_2[6] = iVar5;
    param_2[8] = iVar5;
  }
  else {
    BVar7 = FileTimeToLocalFileTime(&local_164.ftLastWriteTime,&local_20);
    if ((BVar7 == 0) || (BVar7 = FileTimeToSystemTime(&local_20,&local_14), BVar7 == 0)) {
LAB_004bd66e:
      DVar8 = GetLastError();
      FUN_004c0959(DVar8);
      FindClose(local_18);
      return 0xffffffff;
    }
    iVar5 = FUN_004c18e0((uint)local_14.wYear,(uint)local_14.wMonth,(uint)local_14.wDay,
                         (uint)local_14.wHour,(uint)local_14.wMinute,(uint)local_14.wSecond,-1);
    param_2[7] = iVar5;
    if ((local_164.ftLastAccessTime.dwLowDateTime != 0) ||
       (local_164.ftLastAccessTime.dwHighDateTime != 0)) {
      BVar7 = FileTimeToLocalFileTime(&local_164.ftLastAccessTime,&local_20);
      if ((BVar7 == 0) || (BVar7 = FileTimeToSystemTime(&local_20,&local_14), BVar7 == 0))
      goto LAB_004bd66e;
      iVar5 = FUN_004c18e0((uint)local_14.wYear,(uint)local_14.wMonth,(uint)local_14.wDay,
                           (uint)local_14.wHour,(uint)local_14.wMinute,(uint)local_14.wSecond,-1);
    }
    param_2[6] = iVar5;
    if ((local_164.ftCreationTime.dwLowDateTime == 0) &&
       (local_164.ftCreationTime.dwHighDateTime == 0)) {
      iVar5 = param_2[7];
    }
    else {
      BVar7 = FileTimeToLocalFileTime(&local_164.ftCreationTime,&local_20);
      if ((BVar7 == 0) || (BVar7 = FileTimeToSystemTime(&local_20,&local_14), BVar7 == 0))
      goto LAB_004bd66e;
      iVar5 = FUN_004c18e0((uint)local_14.wYear,(uint)local_14.wMonth,(uint)local_14.wDay,
                           (uint)local_14.wHour,(uint)local_14.wMinute,(uint)local_14.wSecond,-1);
    }
    param_2[8] = iVar5;
    FindClose(local_18);
  }
  uVar3 = FUN_004bd318((byte)local_164.dwFileAttributes,param_1);
  *(short *)((int)param_2 + 6) = (short)uVar3;
  param_2[5] = local_164.nFileSizeLow;
  *param_2 = local_24 + -1;
  param_2[4] = local_24 + -1;
  *(undefined2 *)(param_2 + 2) = 1;
  *(undefined2 *)(param_2 + 1) = 0;
  *(undefined2 *)(param_2 + 3) = 0;
  *(undefined2 *)((int)param_2 + 10) = 0;
  return 0;
}


/* 004bd68b size=112 */

undefined4 __cdecl FUN_004bd68b(char *param_1)

{
  char *pcVar1;
  size_t sVar2;
  char *pcVar3;
  char cVar4;
  
  sVar2 = _strlen(param_1);
  if (((4 < sVar2) && ((*param_1 == '\\' || (*param_1 == '/')))) &&
     ((param_1[1] == '\\' || (param_1[1] == '/')))) {
    pcVar3 = param_1 + 3;
    cVar4 = param_1[3];
    while (((cVar4 != '\0' && (cVar4 != '\\')) && (cVar4 != '/'))) {
      pcVar1 = pcVar3 + 1;
      pcVar3 = pcVar3 + 1;
      cVar4 = *pcVar1;
    }
    if ((*pcVar3 != '\0') && (pcVar3 = pcVar3 + 1, *pcVar3 != '\0')) {
      for (; (cVar4 = *pcVar3, cVar4 != '\0' && ((cVar4 != '\\' && (cVar4 != '/'))));
          pcVar3 = pcVar3 + 1) {
      }
      if ((*pcVar3 == '\0') || (pcVar3[1] == '\0')) {
        return 1;
      }
    }
  }
  return 0;
}


/* 004bd77c size=31 */

void FUN_004bd77c(void)

{
  undefined1 auStack_c [12];
  
  ExceptionList = auStack_c;
  return;
}


/* 004bd7a0 size=664 */

undefined4 * __cdecl FUN_004bd7a0(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    puVar3 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar4 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = param_3 >> 2;
      uVar2 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return param_1;
        case 2:
          goto switchD_004bd957_caseD_2;
        case 3:
          goto switchD_004bd957_caseD_3;
        }
        goto switchD_004bd957_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_004bd957_caseD_0;
      case 1:
        goto switchD_004bd957_caseD_1;
      case 2:
        goto switchD_004bd957_caseD_2;
      case 3:
        goto switchD_004bd957_caseD_3;
      default:
        uVar1 = param_3 - ((uint)puVar4 & 3);
        switch((uint)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          puVar3 = (undefined4 *)((int)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (undefined4 *)((int)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_004bd957_caseD_2;
            case 3:
              goto switchD_004bd957_caseD_3;
            }
            goto switchD_004bd957_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          puVar3 = (undefined4 *)((int)puVar3 + -2);
          puVar4 = (undefined4 *)((int)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_004bd957_caseD_2;
            case 3:
              goto switchD_004bd957_caseD_3;
            }
            goto switchD_004bd957_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + -3);
          puVar4 = (undefined4 *)((int)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_004bd957_caseD_2;
            case 3:
              goto switchD_004bd957_caseD_3;
            }
            goto switchD_004bd957_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_004bd957_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return param_1;
    case 2:
switchD_004bd957_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return param_1;
    case 3:
switchD_004bd957_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return param_1;
    }
switchD_004bd957_caseD_0:
    return param_1;
  }
  puVar3 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    uVar2 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *param_2;
        param_2 = param_2 + 1;
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return param_1;
      case 2:
        goto switchD_004bd7d5_caseD_2;
      case 3:
        goto switchD_004bd7d5_caseD_3;
      }
      goto switchD_004bd7d5_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_004bd7d5_caseD_0;
    case 1:
      goto switchD_004bd7d5_caseD_1;
    case 2:
      goto switchD_004bd7d5_caseD_2;
    case 3:
      goto switchD_004bd7d5_caseD_3;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar3 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_004bd7d5_caseD_2;
          case 3:
            goto switchD_004bd7d5_caseD_3;
          }
          goto switchD_004bd7d5_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar3 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_004bd7d5_caseD_2;
          case 3:
            goto switchD_004bd7d5_caseD_3;
          }
          goto switchD_004bd7d5_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_004bd7d5_caseD_2;
          case 3:
            goto switchD_004bd7d5_caseD_3;
          }
          goto switchD_004bd7d5_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar3[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar3[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar3[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar3[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar3[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar3[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_004bd7d5_caseD_1:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    return param_1;
  case 2:
switchD_004bd7d5_caseD_2:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
switchD_004bd7d5_caseD_3:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
switchD_004bd7d5_caseD_0:
  return param_1;
}


/* 004bdad5 size=18 */

void __fastcall FUN_004bdad5(void *param_1)

{
  FUN_004c570a(param_1,0x10000,0x30000);
  return;
}


/* 004bdae7 size=62 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004bdae7(void)

{
  if (_DAT_004cc808 < _DAT_004cf108 - (_DAT_004cf108 / _DAT_004cf110) * _DAT_004cf110) {
    return 1;
  }
  return 0;
}


/* 004bdb25 size=41 */

/* FUN_004bdb25: lifted from original x86 -> lt_lifted.c */


/* 004bdb4e size=90 */

/* FUN_004bdb4e: lifted from original x86 -> lt_lifted.c */


/* 004bdc4c size=97 */

undefined1 * __cdecl FUN_004bdc4c(undefined8 *param_1,undefined1 *param_2,int param_3,int param_4)

{
  uint local_2c [6];
  int local_14 [4];
  
  FUN_004c5c9e((uint)*param_1,(int)((ulonglong)*param_1 >> 0x20),local_14,local_2c);
  FUN_004c5c27(param_2 + (uint)(0 < param_3) + (uint)(local_14[0] == 0x2d),param_3 + 1,(int)local_14
              );
  FUN_004bdcad(param_2,param_3,param_4,local_14,'\0');
  return param_2;
}


/* 004bdcad size=194 */

undefined1 * __cdecl
FUN_004bdcad(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  uint *puVar3;
  int iVar4;
  
  if (param_5 != '\0') {
    FUN_004bdf4f(param_1 + (*param_4 == 0x2d),(uint)(0 < param_2));
  }
  puVar1 = param_1;
  if (*param_4 == 0x2d) {
    *param_1 = 0x2d;
    puVar1 = param_1 + 1;
  }
  puVar2 = puVar1;
  if (0 < param_2) {
    puVar2 = puVar1 + 1;
    *puVar1 = puVar1[1];
    *puVar2 = DAT_004e36e0;
  }
  puVar3 = FUN_004c17f0((uint *)(puVar2 + param_2 + (uint)(param_5 == '\0')),(uint *)"e+000");
  if (param_3 != 0) {
    *(undefined1 *)puVar3 = 0x45;
  }
  if (*(char *)param_4[3] != '0') {
    iVar4 = param_4[1] + -1;
    if (iVar4 < 0) {
      iVar4 = -iVar4;
      *(undefined1 *)((int)puVar3 + 1) = 0x2d;
    }
    if (99 < iVar4) {
      *(char *)((int)puVar3 + 2) = *(char *)((int)puVar3 + 2) + (char)(iVar4 / 100);
      iVar4 = iVar4 % 100;
    }
    if (9 < iVar4) {
      *(char *)((int)puVar3 + 3) = *(char *)((int)puVar3 + 3) + (char)(iVar4 / 10);
      iVar4 = iVar4 % 10;
    }
    *(char *)(puVar3 + 1) = (char)puVar3[1] + (char)iVar4;
  }
  return param_1;
}


/* 004bdd6f size=85 */

char * __cdecl FUN_004bdd6f(undefined8 *param_1,char *param_2,size_t param_3)

{
  uint local_2c [6];
  int local_14;
  int local_10;
  
  FUN_004c5c9e((uint)*param_1,(int)((ulonglong)*param_1 >> 0x20),&local_14,local_2c);
  FUN_004c5c27(param_2 + (local_14 == 0x2d),local_10 + param_3,(int)&local_14);
  FUN_004bddc4(param_2,param_3,&local_14,'\0');
  return param_2;
}


/* 004bddc4 size=167 */

char * __cdecl FUN_004bddc4(char *param_1,size_t param_2,int *param_3,char param_4)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = param_3[1];
  if ((param_4 != '\0') && (iVar1 - 1U == param_2)) {
    iVar2 = *param_3;
    param_1[(uint)(iVar2 == 0x2d) + (iVar1 - 1U)] = '0';
    (param_1 + (uint)(iVar2 == 0x2d) + (iVar1 - 1U))[1] = '\0';
  }
  pcVar3 = param_1;
  if (*param_3 == 0x2d) {
    *param_1 = '-';
    pcVar3 = param_1 + 1;
  }
  if (param_3[1] < 1) {
    FUN_004bdf4f(pcVar3,1);
    *pcVar3 = '0';
    pcVar3 = pcVar3 + 1;
  }
  else {
    pcVar3 = pcVar3 + param_3[1];
  }
  if (0 < (int)param_2) {
    FUN_004bdf4f(pcVar3,1);
    *pcVar3 = DAT_004e36e0;
    iVar1 = param_3[1];
    if (iVar1 < 0) {
      if ((param_4 != '\0') || (-iVar1 <= (int)param_2)) {
        param_2 = -iVar1;
      }
      FUN_004bdf4f(pcVar3 + 1,param_2);
      _memset(pcVar3 + 1,0x30,param_2);
    }
  }
  return param_1;
}


/* 004bde6b size=147 */

int __cdecl FUN_004bde6b(undefined8 *param_1,char *param_2,size_t param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  uint local_2c [6];
  int local_14;
  int local_10;
  
  FUN_004c5c9e((uint)*param_1,(int)((ulonglong)*param_1 >> 0x20),&local_14,local_2c);
  iVar1 = local_10 + -1;
  FUN_004c5c27(param_2 + (local_14 == 0x2d),param_3,(int)&local_14);
  local_10 = local_10 + -1;
  if ((local_10 < -4) || ((int)param_3 <= local_10)) {
    FUN_004bdcad(param_2,param_3,param_4,&local_14,'\x01');
  }
  else {
    pcVar2 = param_2 + (local_14 == 0x2d);
    if (iVar1 < local_10) {
      do {
        pcVar3 = pcVar2;
        pcVar2 = pcVar3 + 1;
      } while (*pcVar3 != '\0');
      pcVar3[-1] = '\0';
    }
    FUN_004bddc4(param_2,param_3,&local_14,'\x01');
  }
  return;
}


/* 004bdf4f size=37 */

void __cdecl FUN_004bdf4f(char *param_1,int param_2)

{
  size_t sVar1;
  
  if (param_2 != 0) {
    sVar1 = _strlen(param_1);
    FUN_004bab10((undefined4 *)(param_1 + param_2),(undefined4 *)param_1,sVar1 + 1);
  }
  return;
}


/* 004bdf74 size=781 */

byte * __cdecl FUN_004bdf74(byte *param_1,uint *param_2)

{
  int iVar1;
  uint *puVar2;
  byte *pbVar3;
  int local_3c;
  uint *local_38;
  byte *local_34;
  int *local_30;
  uint *local_2c;
  byte *local_28;
  uint *local_24;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf148;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  pbVar3 = (byte *)0x0;
  if (param_1 == (byte *)0x0) {
    ExceptionList = &local_14;
    pbVar3 = _malloc((size_t)param_2);
  }
  else {
    if (param_2 == (uint *)0x0) {
      ExceptionList = &local_14;
      FUN_004b9d3f(param_1);
    }
    else {
      ExceptionList = &local_14;
      if (DAT_004ed3c4 == 3) {
        do {
          local_28 = (byte *)0x0;
          if (param_2 < (uint *)0xffffffe1) {
            FUN_004bf7a0(9);
            local_8 = 0;
            local_2c = (uint *)FUN_004be5ab((int)param_1);
            if (local_2c != (uint *)0x0) {
              if (param_2 <= DAT_004ed3bc) {
                iVar1 = FUN_004bedb4(local_2c,(int)param_1,(int)param_2);
                if (iVar1 == 0) {
                  local_28 = (byte *)FUN_004be8ff(param_2);
                  if (local_28 != (byte *)0x0) {
                    local_24 = (uint *)(*(int *)(param_1 + -4) - 1);
                    puVar2 = local_24;
                    if (param_2 <= local_24) {
                      puVar2 = param_2;
                    }
                    FUN_004bd7a0((undefined4 *)local_28,(undefined4 *)param_1,(uint)puVar2);
                    local_2c = (uint *)FUN_004be5ab((int)param_1);
                    FUN_004be5d6(local_2c,(int)param_1);
                  }
                }
                else {
                  local_28 = param_1;
                }
              }
              if (local_28 == (byte *)0x0) {
                if (param_2 == (uint *)0x0) {
                  param_2 = (uint *)0x1;
                }
                param_2 = (uint *)((int)param_2 + 0xfU & 0xfffffff0);
                local_28 = HeapAlloc(DAT_004ed3c0,0,(SIZE_T)param_2);
                if (local_28 != (byte *)0x0) {
                  local_24 = (uint *)(*(int *)(param_1 + -4) - 1);
                  puVar2 = local_24;
                  if (param_2 <= local_24) {
                    puVar2 = param_2;
                  }
                  FUN_004bd7a0((undefined4 *)local_28,(undefined4 *)param_1,(uint)puVar2);
                  FUN_004be5d6(local_2c,(int)param_1);
                }
              }
            }
            local_8 = 0xffffffff;
            FUN_004be0ff();
            if (local_2c == (uint *)0x0) {
              if (param_2 == (uint *)0x0) {
                param_2 = (uint *)0x1;
              }
              param_2 = (uint *)((int)param_2 + 0xfU & 0xfffffff0);
              local_28 = HeapReAlloc(DAT_004ed3c0,0,param_1,(SIZE_T)param_2);
            }
          }
          if (local_28 != (byte *)0x0) {
            ExceptionList = local_14;
            return local_28;
          }
          if (DAT_004ecd58 == (byte *)0x0) {
            ExceptionList = local_14;
            return (byte *)0x0;
          }
          iVar1 = FUN_004bbc46(param_2);
        } while (iVar1 != 0);
      }
      else {
        ExceptionList = &local_14;
        if (DAT_004ed3c4 == 2) {
          ExceptionList = &local_14;
          if (param_2 < (uint *)0xffffffe1) {
            if (param_2 == (uint *)0x0) {
              param_2 = (uint *)0x10;
              ExceptionList = &local_14;
            }
            else {
              param_2 = (uint *)((int)param_2 + 0xfU & 0xfffffff0);
              ExceptionList = &local_14;
            }
          }
          do {
            local_28 = pbVar3;
            if (param_2 < (uint *)0xffffffe1) {
              FUN_004bf7a0(9);
              local_8 = 1;
              pbVar3 = (byte *)FUN_004bf306(param_1,&local_3c,(uint *)&local_30);
              local_34 = pbVar3;
              if (pbVar3 == (byte *)0x0) {
                local_28 = HeapReAlloc(DAT_004ed3c0,0,param_1,(SIZE_T)param_2);
              }
              else {
                if (param_2 < DAT_004e3154) {
                  iVar1 = FUN_004bf6ce(local_3c,local_30,pbVar3,(uint)param_2 >> 4);
                  if (iVar1 == 0) {
                    local_28 = (byte *)FUN_004bf3a2((uint)param_2 >> 4);
                    if (local_28 != (byte *)0x0) {
                      local_38 = (uint *)((uint)*pbVar3 << 4);
                      puVar2 = local_38;
                      if (param_2 <= local_38) {
                        puVar2 = param_2;
                      }
                      FUN_004bd7a0((undefined4 *)local_28,(undefined4 *)param_1,(uint)puVar2);
                      FUN_004bf35d(local_3c,(int)local_30,pbVar3);
                    }
                  }
                  else {
                    local_28 = param_1;
                  }
                }
                if ((local_28 == (byte *)0x0) &&
                   (local_28 = HeapAlloc(DAT_004ed3c0,0,(SIZE_T)param_2), local_28 != (byte *)0x0))
                {
                  local_38 = (uint *)((uint)*pbVar3 << 4);
                  puVar2 = local_38;
                  if (param_2 <= local_38) {
                    puVar2 = param_2;
                  }
                  FUN_004bd7a0((undefined4 *)local_28,(undefined4 *)param_1,(uint)puVar2);
                  FUN_004bf35d(local_3c,(int)local_30,pbVar3);
                }
              }
              local_8 = 0xffffffff;
              FUN_004be24d();
            }
            if (local_28 != pbVar3) {
              ExceptionList = local_14;
              return local_28;
            }
            if (DAT_004ecd58 == pbVar3) {
              ExceptionList = local_14;
              return local_28;
            }
            iVar1 = FUN_004bbc46(param_2);
          } while (iVar1 != 0);
        }
        else {
          do {
            pbVar3 = (byte *)0x0;
            if (param_2 < (uint *)0xffffffe1) {
              if (param_2 == (uint *)0x0) {
                param_2 = (uint *)0x1;
              }
              param_2 = (uint *)((int)param_2 + 0xfU & 0xfffffff0);
              pbVar3 = HeapReAlloc(DAT_004ed3c0,0,param_1,(SIZE_T)param_2);
            }
            if (pbVar3 != (byte *)0x0) {
              ExceptionList = local_14;
              return pbVar3;
            }
            if (DAT_004ecd58 == (byte *)0x0) {
              ExceptionList = local_14;
              return (byte *)0x0;
            }
            iVar1 = FUN_004bbc46(param_2);
          } while (iVar1 != 0);
        }
      }
    }
    pbVar3 = (byte *)0x0;
  }
  ExceptionList = local_14;
  return pbVar3;
}


/* 004be0ff size=9 */

void FUN_004be0ff(void)

{
  FUN_004bf801(9);
  return;
}


/* 004be24d size=11 */

void FUN_004be24d(void)

{
  FUN_004bf801(9);
  return;
}


/* 004be2a3 size=214 */

SIZE_T __cdecl FUN_004be2a3(undefined *param_1)

{
  byte *pbVar1;
  SIZE_T SVar2;
  undefined4 local_30;
  byte *local_2c;
  uint local_28;
  SIZE_T local_24;
  byte *local_20;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf160;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  if (DAT_004ed3c4 == 3) {
    ExceptionList = &local_14;
    FUN_004bf7a0(9);
    local_8 = 0;
    local_20 = (byte *)FUN_004be5ab((int)param_1);
    if (local_20 != (byte *)0x0) {
      local_24 = *(int *)(param_1 + -4) - 9;
    }
    SVar2 = local_24;
    local_8 = 0xffffffff;
    FUN_004be30d();
    pbVar1 = local_20;
  }
  else {
    ExceptionList = &local_14;
    if (DAT_004ed3c4 != 2) goto LAB_004be361;
    ExceptionList = &local_14;
    FUN_004bf7a0(9);
    local_8 = 1;
    local_2c = (byte *)FUN_004bf306(param_1,&local_30,&local_28);
    if (local_2c != (byte *)0x0) {
      local_24 = (uint)*local_2c << 4;
    }
    SVar2 = local_24;
    local_8 = 0xffffffff;
    FUN_004be388();
    pbVar1 = local_2c;
  }
  if (pbVar1 != (byte *)0x0) {
    ExceptionList = local_14;
    return SVar2;
  }
LAB_004be361:
  SVar2 = HeapSize(DAT_004ed3c0,0,param_1);
  ExceptionList = local_14;
  return SVar2;
}


/* 004be30d size=9 */

void FUN_004be30d(void)

{
  FUN_004bf801(9);
  return;
}


/* 004be388 size=9 */

void FUN_004be388(void)

{
  FUN_004bf801(9);
  return;
}


/* 004be391 size=45 */

void __cdecl FUN_004be391(undefined4 *param_1)

{
  int iVar1;
  HMODULE pHVar2;
  
  *param_1 = 0;
  pHVar2 = GetModuleHandleA((LPCSTR)0x0);
  if (((short)pHVar2->unused == 0x5a4d) && (iVar1 = pHVar2[0xf].unused, iVar1 != 0)) {
    *(undefined1 *)param_1 = *(undefined1 *)((int)&pHVar2[6].unused + iVar1 + 2);
    *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)&pHVar2[6].unused + iVar1 + 3);
  }
  return;
}


/* 004be3be size=328 */

int FUN_004be3be(void)

{
  char cVar1;
  byte bVar2;
  BOOL BVar3;
  DWORD DVar4;
  int iVar5;
  uint *puVar6;
  byte *pbVar7;
  char *pcVar8;
  byte *this;
  undefined4 unaff_EBX;
  undefined1 unaff_BP;
  undefined4 local_1230;
  char local_1a0 [260];
  DWORD local_9c;
  uint local_98;
  DWORD local_8c;
  CHAR aCStackY_18 [4];
  byte bVar9;
  
  FUN_004ba7f0(unaff_BP);
  local_9c = 0x94;
  BVar3 = GetVersionExA((LPOSVERSIONINFOA)&local_9c);
  if (((BVar3 == 0) || (local_8c != 2)) || (local_98 < 5)) {
    aCStackY_18[0] = '\x18';
    aCStackY_18[1] = -0x1c;
    aCStackY_18[2] = 'K';
    aCStackY_18[3] = '\0';
    DVar4 = GetEnvironmentVariableA("__MSVCRT_HEAP_SELECT",(LPSTR)&local_1230,0x1090);
    bVar9 = (byte)unaff_EBX;
    if (DVar4 != 0) {
      pcVar8 = (char *)&local_1230;
      while ((char)local_1230 != '\0') {
        cVar1 = *pcVar8;
        if (('`' < cVar1) && (cVar1 < '{')) {
          *pcVar8 = cVar1 + -0x20;
        }
        pcVar8 = pcVar8 + 1;
        (*(uint8_t*)((char*)&local_1230+0)) = *pcVar8;
      }
      aCStackY_18[0] = 'V';
      aCStackY_18[1] = -0x1c;
      aCStackY_18[2] = 'K';
      aCStackY_18[3] = '\0';
      iVar5 = _strncmp("__GLOBAL_HEAP_SELECTED",(char *)&local_1230,0x16);
      bVar9 = (byte)unaff_EBX;
      if (iVar5 == 0) {
        puVar6 = &local_1230;
      }
      else {
        aCStackY_18[0] = 'x';
        aCStackY_18[1] = -0x1c;
        aCStackY_18[2] = 'K';
        aCStackY_18[3] = '\0';
        GetModuleFileNameA((HMODULE)0x0,local_1a0,0x104);
        bVar9 = (byte)unaff_EBX;
        pcVar8 = local_1a0;
        while (local_1a0[0] != '\0') {
          cVar1 = *pcVar8;
          if (('`' < cVar1) && (cVar1 < '{')) {
            *pcVar8 = cVar1 + -0x20;
          }
          bVar9 = (byte)unaff_EBX;
          pcVar8 = pcVar8 + 1;
          local_1a0[0] = *pcVar8;
        }
        puVar6 = FUN_004bae50(&local_1230,local_1a0);
      }
      if ((puVar6 != (uint *)0x0) && (puVar6 = FUN_004bb020(puVar6,','), puVar6 != (uint *)0x0)) {
        pbVar7 = (byte *)((int)puVar6 + 1);
        bVar2 = *pbVar7;
        this = pbVar7;
        while (bVar2 != 0) {
          if (*this == 0x3b) {
            *this = 0;
          }
          else {
            this = this + 1;
          }
          bVar2 = *this;
        }
        aCStackY_18[0] = -0x22;
        aCStackY_18[1] = -0x1c;
        aCStackY_18[2] = 'K';
        aCStackY_18[3] = '\0';
        iVar5 = FUN_004c5e11(this,pbVar7,(int *)0x0,(void *)0xa);
        if (iVar5 == 2) {
          return 2;
        }
        if (iVar5 == 3) {
          return 3;
        }
        if (iVar5 == 1) {
          return 1;
        }
      }
    }
    FUN_004be391((undefined4 *)(aCStackY_18 + 0x10));
    iVar5 = 3 - (uint)(bVar9 < 6);
  }
  else {
    iVar5 = 1;
  }
  return iVar5;
}


/* 004be506 size=93 */

undefined4 __cdecl FUN_004be506(int param_1)

{
  undefined **ppuVar1;
  
  DAT_004ed3c0 = HeapCreate((uint)(param_1 == 0),0x1000,0);
  if (DAT_004ed3c0 != (HANDLE)0x0) {
    DAT_004ed3c4 = FUN_004be3be();
    if (DAT_004ed3c4 == 3) {
      ppuVar1 = (undefined **)FUN_004be563(0x3f8);
    }
    else {
      if (DAT_004ed3c4 != 2) {
        return 1;
      }
      ppuVar1 = FUN_004bf0aa();
    }
    if (ppuVar1 != (undefined **)0x0) {
      return 1;
    }
    HeapDestroy(DAT_004ed3c0);
  }
  return 0;
}


/* 004be563 size=72 */

undefined4 __cdecl FUN_004be563(undefined4 param_1)

{
  DAT_004ed3b8 = HeapAlloc(DAT_004ed3c0,0,0x140);
  if (DAT_004ed3b8 == (LPVOID)0x0) {
    return 0;
  }
  DAT_004ed3b0 = 0;
  DAT_004ed3b4 = 0;
  DAT_004ed3ac = DAT_004ed3b8;
  DAT_004ed3bc = param_1;
  DAT_004ed3a4 = 0x10;
  return 1;
}


/* 004be5ab size=43 */

uint __cdecl FUN_004be5ab(int param_1)

{
  uint uVar1;
  
  uVar1 = DAT_004ed3b8;
  while( true ) {
    if (DAT_004ed3b8 + DAT_004ed3b4 * 0x14 <= uVar1) {
      return 0;
    }
    if ((uint)(param_1 - *(int *)(uVar1 + 0xc)) < 0x100000) break;
    uVar1 = uVar1 + 0x14;
  }
  return uVar1;
}


/* 004be5d6 size=809 */

/* FUN_004be5d6: lifted from original x86 -> lt_lifted.c */


/* 004be8ff size=777 */

int * __cdecl FUN_004be8ff(uint *param_1)

{
  uint *puVar1;
  char *pcVar2;
  int *piVar3;
  char cVar4;
  int *piVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint *puVar10;
  int iVar11;
  int *piVar12;
  uint uVar13;
  uint local_10;
  uint local_c;
  int local_8;
  
  puVar10 = DAT_004ed3b8 + DAT_004ed3b4 * 5;
  uVar7 = (int)param_1 + 0x17U & 0xfffffff0;
  iVar8 = (int)((int)param_1 + 0x17U) >> 4;
  iVar9 = iVar8 + -1;
  if (iVar9 < 0x20) {
    local_10 = 0xffffffff >> ((byte)iVar9 & 0x1f);
    local_c = 0xffffffff;
  }
  else {
    local_c = 0xffffffff >> ((char)iVar8 - 0x21U & 0x1f);
    local_10 = 0;
  }
  for (param_1 = DAT_004ed3ac;
      (param_1 < puVar10 && ((param_1[1] & local_c) == 0 && (*param_1 & local_10) == 0));
      param_1 = param_1 + 5) {
  }
  if (param_1 == puVar10) {
    for (param_1 = DAT_004ed3b8;
        (param_1 < DAT_004ed3ac && ((param_1[1] & local_c) == 0 && (*param_1 & local_10) == 0));
        param_1 = param_1 + 5) {
    }
    if (param_1 == DAT_004ed3ac) {
      for (; (param_1 < puVar10 && (param_1[2] == 0)); param_1 = param_1 + 5) {
      }
      if (param_1 == puVar10) {
        for (param_1 = DAT_004ed3b8; (param_1 < DAT_004ed3ac && (param_1[2] == 0));
            param_1 = param_1 + 5) {
        }
        if ((param_1 == DAT_004ed3ac) && (param_1 = FUN_004bec08(), param_1 == (uint *)0x0)) {
          return (int *)0x0;
        }
      }
      iVar8 = FUN_004becb9((int)param_1);
      *(int *)param_1[4] = iVar8;
      if (*(int *)param_1[4] == -1) {
        return (int *)0x0;
      }
    }
  }
  piVar5 = (int *)param_1[4];
  local_8 = *piVar5;
  if ((local_8 == -1) ||
     ((piVar5[local_8 + 0x31] & local_c) == 0 && (piVar5[local_8 + 0x11] & local_10) == 0)) {
    local_8 = 0;
    puVar10 = (uint *)(piVar5 + 0x11);
    if ((piVar5[0x31] & local_c) == 0 && (piVar5[0x11] & local_10) == 0) {
      do {
        puVar1 = puVar10 + 0x21;
        local_8 = local_8 + 1;
        puVar10 = puVar10 + 1;
      } while ((*puVar1 & local_c) == 0 && (local_10 & *puVar10) == 0);
    }
  }
  iVar8 = 0;
  piVar3 = piVar5 + local_8 * 0x81 + 0x51;
  local_10 = piVar5[local_8 + 0x11] & local_10;
  if (local_10 == 0) {
    local_10 = piVar5[local_8 + 0x31] & local_c;
    iVar8 = 0x20;
  }
  for (; -1 < (int)local_10; local_10 = local_10 << 1) {
    iVar8 = iVar8 + 1;
  }
  piVar12 = (int *)piVar3[iVar8 * 2 + 1];
  iVar11 = *piVar12 - uVar7;
  iVar9 = (iVar11 >> 4) + -1;
  if (0x3f < iVar9) {
    iVar9 = 0x3f;
  }
  DAT_004ed3ac = param_1;
  if (iVar9 != iVar8) {
    if (piVar12[1] == piVar12[2]) {
      if (iVar8 < 0x20) {
        pcVar2 = (char *)((int)piVar5 + iVar8 + 4);
        uVar13 = ~(0x80000000U >> ((byte)iVar8 & 0x1f));
        piVar5[local_8 + 0x11] = uVar13 & piVar5[local_8 + 0x11];
        *pcVar2 = *pcVar2 + -1;
        if (*pcVar2 == '\0') {
          *param_1 = *param_1 & uVar13;
        }
      }
      else {
        pcVar2 = (char *)((int)piVar5 + iVar8 + 4);
        uVar13 = ~(0x80000000U >> ((byte)iVar8 - 0x20 & 0x1f));
        piVar5[local_8 + 0x31] = piVar5[local_8 + 0x31] & uVar13;
        *pcVar2 = *pcVar2 + -1;
        if (*pcVar2 == '\0') {
          param_1[1] = param_1[1] & uVar13;
        }
      }
    }
    *(int *)(piVar12[2] + 4) = piVar12[1];
    *(int *)(piVar12[1] + 8) = piVar12[2];
    if (iVar11 == 0) goto LAB_004bebc5;
    piVar12[1] = piVar3[iVar9 * 2 + 1];
    piVar12[2] = (int)(piVar3 + iVar9 * 2);
    (piVar3 + iVar9 * 2)[1] = (int)piVar12;
    *(int **)(piVar12[1] + 8) = piVar12;
    if (piVar12[1] == piVar12[2]) {
      cVar4 = *(char *)(iVar9 + 4 + (int)piVar5);
      bVar6 = (byte)iVar9;
      if (iVar9 < 0x20) {
        *(char *)(iVar9 + 4 + (int)piVar5) = cVar4 + '\x01';
        if (cVar4 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> (bVar6 & 0x1f);
        }
        piVar5[local_8 + 0x11] = piVar5[local_8 + 0x11] | 0x80000000U >> (bVar6 & 0x1f);
      }
      else {
        *(char *)(iVar9 + 4 + (int)piVar5) = cVar4 + '\x01';
        if (cVar4 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> (bVar6 - 0x20 & 0x1f);
        }
        piVar5[local_8 + 0x31] = piVar5[local_8 + 0x31] | 0x80000000U >> (bVar6 - 0x20 & 0x1f);
      }
    }
  }
  if (iVar11 != 0) {
    *piVar12 = iVar11;
    *(int *)(iVar11 + -4 + (int)piVar12) = iVar11;
  }
LAB_004bebc5:
  piVar12 = (int *)((int)piVar12 + iVar11);
  *piVar12 = uVar7 + 1;
  *(uint *)((int)piVar12 + (uVar7 - 4)) = uVar7 + 1;
  iVar8 = *piVar3;
  *piVar3 = iVar8 + 1;
  if (((iVar8 == 0) && (param_1 == DAT_004ed3b0)) && (local_8 == DAT_004ed3a8)) {
    DAT_004ed3b0 = (uint *)0x0;
  }
  *piVar5 = local_8;
  return piVar12 + 1;
}


/* 004bec08 size=177 */

undefined4 * FUN_004bec08(void)

{
  undefined4 *puVar1;
  LPVOID pvVar2;
  
  if (DAT_004ed3b4 == DAT_004ed3a4) {
    pvVar2 = HeapReAlloc(DAT_004ed3c0,0,DAT_004ed3b8,(DAT_004ed3a4 * 5 + 0x50) * 4);
    if (pvVar2 == (LPVOID)0x0) {
      return (undefined4 *)0x0;
    }
    DAT_004ed3a4 = DAT_004ed3a4 + 0x10;
    DAT_004ed3b8 = pvVar2;
  }
  puVar1 = (undefined4 *)((int)DAT_004ed3b8 + DAT_004ed3b4 * 0x14);
  pvVar2 = HeapAlloc(DAT_004ed3c0,8,0x41c4);
  puVar1[4] = pvVar2;
  if (pvVar2 != (LPVOID)0x0) {
    pvVar2 = VirtualAlloc((LPVOID)0x0,0x100000,0x2000,4);
    puVar1[3] = pvVar2;
    if (pvVar2 != (LPVOID)0x0) {
      puVar1[2] = 0xffffffff;
      *puVar1 = 0;
      puVar1[1] = 0;
      DAT_004ed3b4 = DAT_004ed3b4 + 1;
      *(undefined4 *)puVar1[4] = 0xffffffff;
      return puVar1;
    }
    HeapFree(DAT_004ed3c0,0,(LPVOID)puVar1[4]);
  }
  return (undefined4 *)0x0;
}


/* 004becb9 size=251 */

int __cdecl FUN_004becb9(int param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  LPVOID pvVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int *lpAddress;
  
  iVar3 = *(int *)(param_1 + 0x10);
  iVar9 = 0;
  for (iVar4 = *(int *)(param_1 + 8); -1 < iVar4; iVar4 = iVar4 << 1) {
    iVar9 = iVar9 + 1;
  }
  iVar8 = 0x3f;
  iVar4 = iVar9 * 0x204 + 0x144 + iVar3;
  iVar5 = iVar4;
  do {
    *(int *)(iVar5 + 8) = iVar5;
    *(int *)(iVar5 + 4) = iVar5;
    iVar5 = iVar5 + 8;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  lpAddress = (int *)(iVar9 * 0x8000 + *(int *)(param_1 + 0xc));
  pvVar6 = VirtualAlloc(lpAddress,0x8000,0x1000,4);
  if (pvVar6 == (LPVOID)0x0) {
    iVar9 = -1;
  }
  else {
    if (lpAddress <= lpAddress + 0x1c00) {
      piVar7 = lpAddress + 4;
      do {
        piVar7[-2] = -1;
        piVar7[0x3fb] = -1;
        piVar7[-1] = 0xff0;
        *piVar7 = (int)(piVar7 + 0x3ff);
        piVar7[1] = (int)(piVar7 + -0x401);
        piVar7[0x3fa] = 0xff0;
        piVar1 = piVar7 + 0x3fc;
        piVar7 = piVar7 + 0x400;
      } while (piVar1 <= lpAddress + 0x1c00);
    }
    *(int **)(iVar4 + 0x1fc) = lpAddress + 3;
    lpAddress[5] = iVar4 + 0x1f8;
    *(int **)(iVar4 + 0x200) = lpAddress + 0x1c03;
    lpAddress[0x1c04] = iVar4 + 0x1f8;
    *(undefined4 *)(iVar3 + 0x44 + iVar9 * 4) = 0;
    *(undefined4 *)(iVar3 + 0xc4 + iVar9 * 4) = 1;
    cVar2 = *(char *)(iVar3 + 0x43);
    *(char *)(iVar3 + 0x43) = cVar2 + '\x01';
    if (cVar2 == '\0') {
      *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 1;
    }
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~(0x80000000U >> ((byte)iVar9 & 0x1f));
  }
  return iVar9;
}


/* 004bedb4 size=758 */

undefined4 __cdecl FUN_004bedb4(uint *param_1,int param_2,int param_3)

{
  char *pcVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint local_c;
  
  uVar5 = param_1[4];
  uVar11 = param_3 + 0x17U & 0xfffffff0;
  uVar9 = param_2 - param_1[3] >> 0xf;
  iVar3 = uVar9 * 0x204 + 0x144 + uVar5;
  iVar6 = *(int *)(param_2 + -4);
  iVar8 = iVar6 + -1;
  uVar12 = *(uint *)(iVar6 + -5 + param_2);
  iVar6 = iVar6 + -5 + param_2;
  if (iVar8 < (int)uVar11) {
    if (((uVar12 & 1) != 0) || ((int)(uVar12 + iVar8) < (int)uVar11)) {
      return 0;
    }
    local_c = ((int)uVar12 >> 4) - 1;
    if (0x3f < local_c) {
      local_c = 0x3f;
    }
    if (*(int *)(iVar6 + 4) == *(int *)(iVar6 + 8)) {
      if (local_c < 0x20) {
        pcVar1 = (char *)(local_c + 4 + uVar5);
        uVar10 = ~(0x80000000U >> ((byte)local_c & 0x1f));
        puVar7 = (uint *)(uVar5 + 0x44 + uVar9 * 4);
        *puVar7 = *puVar7 & uVar10;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          *param_1 = *param_1 & uVar10;
        }
      }
      else {
        pcVar1 = (char *)(local_c + 4 + uVar5);
        uVar10 = ~(0x80000000U >> ((byte)local_c - 0x20 & 0x1f));
        puVar7 = (uint *)(uVar5 + 0xc4 + uVar9 * 4);
        *puVar7 = *puVar7 & uVar10;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          param_1[1] = param_1[1] & uVar10;
        }
      }
    }
    *(undefined4 *)(*(int *)(iVar6 + 8) + 4) = *(undefined4 *)(iVar6 + 4);
    *(undefined4 *)(*(int *)(iVar6 + 4) + 8) = *(undefined4 *)(iVar6 + 8);
    iVar6 = uVar12 + (iVar8 - uVar11);
    if (0 < iVar6) {
      uVar12 = (iVar6 >> 4) - 1;
      iVar8 = param_2 + -4 + uVar11;
      if (0x3f < uVar12) {
        uVar12 = 0x3f;
      }
      iVar3 = iVar3 + uVar12 * 8;
      *(undefined4 *)(iVar8 + 4) = *(undefined4 *)(iVar3 + 4);
      *(int *)(iVar8 + 8) = iVar3;
      *(int *)(iVar3 + 4) = iVar8;
      *(int *)(*(int *)(iVar8 + 4) + 8) = iVar8;
      if (*(int *)(iVar8 + 4) == *(int *)(iVar8 + 8)) {
        cVar4 = *(char *)(uVar12 + 4 + uVar5);
        *(char *)(uVar12 + 4 + uVar5) = cVar4 + '\x01';
        if (uVar12 < 0x20) {
          if (cVar4 == '\0') {
            *param_1 = *param_1 | 0x80000000U >> ((byte)uVar12 & 0x1f);
          }
          puVar7 = (uint *)(uVar5 + 0x44 + uVar9 * 4);
        }
        else {
          if (cVar4 == '\0') {
            param_1[1] = param_1[1] | 0x80000000U >> ((byte)uVar12 - 0x20 & 0x1f);
          }
          puVar7 = (uint *)(uVar5 + 0xc4 + uVar9 * 4);
          uVar12 = uVar12 - 0x20;
        }
        *puVar7 = *puVar7 | 0x80000000U >> ((byte)uVar12 & 0x1f);
      }
      piVar2 = (int *)(param_2 + -4 + uVar11);
      *piVar2 = iVar6;
      *(int *)(iVar6 + -4 + (int)piVar2) = iVar6;
    }
    *(uint *)(param_2 + -4) = uVar11 + 1;
    *(uint *)(param_2 + -8 + uVar11) = uVar11 + 1;
  }
  else if ((int)uVar11 < iVar8) {
    param_3 = iVar8 - uVar11;
    *(uint *)(param_2 + -4) = uVar11 + 1;
    piVar2 = (int *)(param_2 + -4 + uVar11);
    uVar10 = (param_3 >> 4) - 1;
    piVar2[-1] = uVar11 + 1;
    if (0x3f < uVar10) {
      uVar10 = 0x3f;
    }
    if ((uVar12 & 1) == 0) {
      uVar11 = ((int)uVar12 >> 4) - 1;
      if (0x3f < uVar11) {
        uVar11 = 0x3f;
      }
      if (*(int *)(iVar6 + 4) == *(int *)(iVar6 + 8)) {
        if (uVar11 < 0x20) {
          pcVar1 = (char *)(uVar11 + 4 + uVar5);
          uVar11 = ~(0x80000000U >> ((byte)uVar11 & 0x1f));
          puVar7 = (uint *)(uVar5 + 0x44 + uVar9 * 4);
          *puVar7 = *puVar7 & uVar11;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            *param_1 = *param_1 & uVar11;
          }
        }
        else {
          pcVar1 = (char *)(uVar11 + 4 + uVar5);
          uVar11 = ~(0x80000000U >> ((byte)uVar11 - 0x20 & 0x1f));
          puVar7 = (uint *)(uVar5 + 0xc4 + uVar9 * 4);
          *puVar7 = *puVar7 & uVar11;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            param_1[1] = param_1[1] & uVar11;
          }
        }
      }
      *(undefined4 *)(*(int *)(iVar6 + 8) + 4) = *(undefined4 *)(iVar6 + 4);
      *(undefined4 *)(*(int *)(iVar6 + 4) + 8) = *(undefined4 *)(iVar6 + 8);
      param_3 = param_3 + uVar12;
      uVar10 = (param_3 >> 4) - 1;
      if (0x3f < uVar10) {
        uVar10 = 0x3f;
      }
    }
    iVar6 = iVar3 + uVar10 * 8;
    piVar2[1] = *(int *)(iVar3 + 4 + uVar10 * 8);
    piVar2[2] = iVar6;
    *(int **)(iVar6 + 4) = piVar2;
    *(int **)(piVar2[1] + 8) = piVar2;
    if (piVar2[1] == piVar2[2]) {
      cVar4 = *(char *)(uVar10 + 4 + uVar5);
      *(char *)(uVar10 + 4 + uVar5) = cVar4 + '\x01';
      if (uVar10 < 0x20) {
        if (cVar4 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> ((byte)uVar10 & 0x1f);
        }
        puVar7 = (uint *)(uVar5 + 0x44 + uVar9 * 4);
      }
      else {
        if (cVar4 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> ((byte)uVar10 - 0x20 & 0x1f);
        }
        puVar7 = (uint *)(uVar5 + 0xc4 + uVar9 * 4);
        uVar10 = uVar10 - 0x20;
      }
      *puVar7 = *puVar7 | 0x80000000U >> ((byte)uVar10 & 0x1f);
    }
    *piVar2 = param_3;
    *(int *)(param_3 + -4 + (int)piVar2) = param_3;
  }
  return 1;
}


/* 004bf0aa size=324 */

undefined ** FUN_004bf0aa(void)

{
  bool bVar1;
  int *lpAddress;
  LPVOID pvVar2;
  undefined **ppuVar3;
  int iVar4;
  undefined **lpMem;
  
  if (DAT_004e1140 == -1) {
    lpMem = &PTR_LOOP_004e1130;
  }
  else {
    lpMem = HeapAlloc(DAT_004ed3c0,0,0x2020);
    if (lpMem == (undefined **)0x0) {
      return (undefined **)0x0;
    }
  }
  lpAddress = VirtualAlloc((LPVOID)0x0,0x400000,0x2000,4);
  if (lpAddress != (int *)0x0) {
    pvVar2 = VirtualAlloc(lpAddress,0x10000,0x1000,4);
    if (pvVar2 != (LPVOID)0x0) {
      if (lpMem == &PTR_LOOP_004e1130) {
        if (PTR_LOOP_004e1130 == (undefined *)0x0) {
          PTR_LOOP_004e1130 = (undefined *)&PTR_LOOP_004e1130;
        }
        if (PTR_LOOP_004e1134 == (undefined *)0x0) {
          PTR_LOOP_004e1134 = (undefined *)&PTR_LOOP_004e1130;
        }
      }
      else {
        *lpMem = (undefined *)&PTR_LOOP_004e1130;
        lpMem[1] = PTR_LOOP_004e1134;
        PTR_LOOP_004e1134 = (undefined *)lpMem;
        *(undefined ***)lpMem[1] = lpMem;
      }
      lpMem[5] = (undefined *)(lpAddress + 0x100000);
      ppuVar3 = lpMem + 6;
      lpMem[3] = (undefined *)(lpMem + 0x26);
      lpMem[4] = (undefined *)lpAddress;
      lpMem[2] = (undefined *)ppuVar3;
      iVar4 = 0;
      do {
        bVar1 = 0xf < iVar4;
        iVar4 = iVar4 + 1;
        *ppuVar3 = (undefined *)((bVar1 - 1 & 0xf1) - 1);
        ppuVar3[1] = (undefined *)0xf1;
        ppuVar3 = ppuVar3 + 2;
      } while (iVar4 < 0x400);
      _memset(lpAddress,0,0x10000);
      for (; lpAddress < lpMem[4] + 0x10000; lpAddress = lpAddress + 0x400) {
        *(undefined1 *)(lpAddress + 0x3e) = 0xff;
        *lpAddress = (int)(lpAddress + 2);
        lpAddress[1] = 0xf0;
      }
      return lpMem;
    }
    VirtualFree(lpAddress,0,0x8000);
  }
  if (lpMem != &PTR_LOOP_004e1130) {
    HeapFree(DAT_004ed3c0,0,lpMem);
  }
  return (undefined **)0x0;
}


/* 004bf1ee size=86 */

void __cdecl FUN_004bf1ee(undefined **param_1)

{
  VirtualFree(param_1[4],0,0x8000);
  if ((undefined **)PTR_LOOP_004e3150 == param_1) {
    PTR_LOOP_004e3150 = param_1[1];
  }
  if (param_1 == &PTR_LOOP_004e1130) {
    DAT_004e1140 = 0xffffffff;
    return;
  }
  *(undefined **)param_1[1] = *param_1;
  *(undefined **)(*param_1 + 4) = param_1[1];
  HeapFree(DAT_004ed3c0,0,param_1);
  return;
}


/* 004bf244 size=194 */

void __cdecl FUN_004bf244(int param_1)

{
  BOOL BVar1;
  undefined **ppuVar2;
  int iVar3;
  undefined **ppuVar4;
  undefined **ppuVar5;
  int local_8;
  
  ppuVar4 = (undefined **)PTR_LOOP_004e1134;
  do {
    ppuVar5 = ppuVar4;
    if (ppuVar4[4] != (undefined *)0xffffffff) {
      local_8 = 0;
      ppuVar5 = ppuVar4 + 0x804;
      iVar3 = 0x3ff000;
      do {
        if (*ppuVar5 == (undefined *)0xf0) {
          BVar1 = VirtualFree(ppuVar4[4] + iVar3,0x1000,0x4000);
          if (BVar1 != 0) {
            *ppuVar5 = (undefined *)0xffffffff;
            DAT_004eccf4 = DAT_004eccf4 + -1;
            if (((undefined **)ppuVar4[3] == (undefined **)0x0) || (ppuVar5 < ppuVar4[3])) {
              ppuVar4[3] = (undefined *)ppuVar5;
            }
            local_8 = local_8 + 1;
            param_1 = param_1 + -1;
            if (param_1 == 0) break;
          }
        }
        iVar3 = iVar3 + -0x1000;
        ppuVar5 = ppuVar5 + -2;
      } while (-1 < iVar3);
      ppuVar5 = (undefined **)ppuVar4[1];
      if ((local_8 != 0) && (ppuVar4[6] == (undefined *)0xffffffff)) {
        ppuVar2 = ppuVar4 + 8;
        iVar3 = 1;
        do {
          if (*ppuVar2 != (undefined *)0xffffffff) break;
          iVar3 = iVar3 + 1;
          ppuVar2 = ppuVar2 + 2;
        } while (iVar3 < 0x400);
        if (iVar3 == 0x400) {
          FUN_004bf1ee(ppuVar4);
        }
      }
    }
    if ((ppuVar5 == (undefined **)PTR_LOOP_004e1134) || (ppuVar4 = ppuVar5, param_1 < 1)) {
      return;
    }
  } while( true );
}


/* 004bf306 size=87 */

int __cdecl FUN_004bf306(undefined *param_1,undefined4 *param_2,uint *param_3)

{
  undefined **ppuVar1;
  uint uVar2;
  
  ppuVar1 = &PTR_LOOP_004e1130;
  while ((param_1 <= ppuVar1[4] || (ppuVar1[5] <= param_1))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_004e1130) {
      return 0;
    }
  }
  if (((uint)param_1 & 0xf) != 0) {
    return 0;
  }
  if (((uint)param_1 & 0xfff) < 0x100) {
    return 0;
  }
  *param_2 = ppuVar1;
  uVar2 = (uint)param_1 & 0xfffff000;
  *param_3 = uVar2;
  return ((int)(param_1 + (-0x100 - uVar2)) >> 4) + 8 + uVar2;
}


/* 004bf35d size=69 */

void __cdecl FUN_004bf35d(int param_1,int param_2,byte *param_3)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x18 + (param_2 - *(int *)(param_1 + 0x10) >> 0xc) * 8);
  *piVar1 = *piVar1 + (uint)*param_3;
  *param_3 = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_004eccf4 = DAT_004eccf4 + 1, DAT_004eccf4 == 0x20)) {
    FUN_004bf244(0x10);
  }
  return;
}


/* 004bf3a2 size=520 */

/* WARNING: Type propagation algorithm not settling */

int * __cdecl FUN_004bf3a2(uint param_1)

{
  uint *puVar1;
  int *piVar2;
  undefined **ppuVar3;
  undefined *puVar4;
  int *piVar5;
  undefined **ppuVar6;
  int *piVar7;
  uint *puVar8;
  undefined **ppuVar9;
  int *local_8;
  
  piVar7 = (int *)PTR_LOOP_004e3150;
  do {
    if (piVar7[4] != -1) {
      puVar8 = (uint *)piVar7[2];
      local_8 = (int *)(((int)puVar8 + (-0x18 - (int)piVar7) >> 3) * 0x1000 + piVar7[4]);
      if (puVar8 < piVar7 + 0x806) {
        do {
          if (((int)param_1 <= (int)*puVar8) && (param_1 < puVar8[1])) {
            piVar5 = (int *)FUN_004bf5aa(local_8,*puVar8,param_1);
            if (piVar5 != (int *)0x0) goto LAB_004bf46d;
            puVar8[1] = param_1;
          }
          puVar8 = puVar8 + 2;
          local_8 = local_8 + 0x400;
        } while (puVar8 < piVar7 + 0x806);
      }
      puVar1 = (uint *)piVar7[2];
      piVar2 = (int *)piVar7[4];
      for (puVar8 = (uint *)(piVar7 + 6); puVar8 < puVar1; puVar8 = puVar8 + 2) {
        if (((int)param_1 <= (int)*puVar8) && (param_1 < puVar8[1])) {
          piVar5 = (int *)FUN_004bf5aa(piVar2,*puVar8,param_1);
          if (piVar5 != (int *)0x0) {
LAB_004bf46d:
            PTR_LOOP_004e3150 = (undefined *)piVar7;
            *puVar8 = *puVar8 - param_1;
            piVar7[2] = (int)puVar8;
            return piVar5;
          }
          puVar8[1] = param_1;
        }
        piVar2 = piVar2 + 0x400;
      }
    }
    piVar7 = (int *)*piVar7;
    if (piVar7 == (int *)PTR_LOOP_004e3150) {
      ppuVar9 = &PTR_LOOP_004e1130;
      while ((ppuVar9[4] == (undefined *)0xffffffff || (ppuVar9[3] == (undefined *)0x0))) {
        ppuVar9 = (undefined **)*ppuVar9;
        if (ppuVar9 == &PTR_LOOP_004e1130) {
          ppuVar9 = FUN_004bf0aa();
          if (ppuVar9 == (undefined **)0x0) {
            return (int *)0x0;
          }
          piVar7 = (int *)ppuVar9[4];
          *(char *)(piVar7 + 2) = (char)param_1;
          PTR_LOOP_004e3150 = (undefined *)ppuVar9;
          *piVar7 = (int)piVar7 + param_1 + 8;
          piVar7[1] = 0xf0 - param_1;
          ppuVar9[6] = ppuVar9[6] + -(param_1 & 0xff);
          return piVar7 + 0x40;
        }
      }
      ppuVar3 = (undefined **)ppuVar9[3];
      local_8 = (int *)0x0;
      piVar7 = (int *)(ppuVar9[4] + ((int)ppuVar3 + (-0x18 - (int)ppuVar9) >> 3) * 0x1000);
      puVar4 = *ppuVar3;
      ppuVar6 = ppuVar3;
      for (; (puVar4 == (undefined *)0xffffffff && ((int)local_8 < 0x10));
          local_8 = (int *)((int)local_8 + 1)) {
        ppuVar6 = ppuVar6 + 2;
        puVar4 = *ppuVar6;
      }
      piVar5 = VirtualAlloc(piVar7,(int)local_8 << 0xc,0x1000,4);
      if (piVar5 != piVar7) {
        return (int *)0x0;
      }
      _memset(piVar7,(int)local_8 << 0xc,0);
      ppuVar6 = ppuVar3;
      if (0 < (int)local_8) {
        piVar5 = piVar7 + 1;
        do {
          *(undefined1 *)(piVar5 + 0x3d) = 0xff;
          piVar5[-1] = (int)(piVar5 + 1);
          *piVar5 = 0xf0;
          *ppuVar6 = (undefined *)0xf0;
          ppuVar6[1] = (undefined *)0xf1;
          piVar5 = piVar5 + 0x400;
          ppuVar6 = ppuVar6 + 2;
          local_8 = (int *)((int)local_8 + -1);
        } while (local_8 != (int *)0x0);
      }
      for (; (ppuVar6 < ppuVar9 + 0x806 && (*ppuVar6 != (undefined *)0xffffffff));
          ppuVar6 = ppuVar6 + 2) {
      }
      PTR_LOOP_004e3150 = (undefined *)ppuVar9;
      ppuVar9[3] = (undefined *)(-(uint)(ppuVar6 < ppuVar9 + 0x806) & (uint)ppuVar6);
      *(char *)(piVar7 + 2) = (char)param_1;
      ppuVar9[2] = (undefined *)ppuVar3;
      *ppuVar3 = *ppuVar3 + -param_1;
      piVar7[1] = piVar7[1] - param_1;
      *piVar7 = (int)piVar7 + param_1 + 8;
      return piVar7 + 0x40;
    }
  } while( true );
}


/* 004bf5aa size=292 */

int __cdecl FUN_004bf5aa(int *param_1,uint param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  byte bVar4;
  byte *pbVar5;
  uint uVar6;
  byte *pbVar7;
  
  pbVar2 = (byte *)*param_1;
  pbVar1 = (byte *)(param_1 + 0x3e);
  bVar4 = (byte)param_3;
  if ((uint)param_1[1] < param_3) {
    pbVar7 = pbVar2;
    if (pbVar2[param_1[1]] != 0) {
      pbVar7 = pbVar2 + param_1[1];
    }
    do {
      while( true ) {
        while( true ) {
          if (pbVar1 <= pbVar7 + param_3) {
            pbVar7 = (byte *)(param_1 + 2);
            goto LAB_004bf645;
          }
          if (*pbVar7 == 0) break;
          pbVar7 = pbVar7 + *pbVar7;
        }
        uVar6 = 1;
        pbVar5 = pbVar7;
        while (pbVar5 = pbVar5 + 1, *pbVar5 == 0) {
          uVar6 = uVar6 + 1;
        }
        if (param_3 <= uVar6) {
          if (pbVar7 + param_3 < pbVar1) {
            *param_1 = (int)(pbVar7 + param_3);
            param_1[1] = uVar6 - param_3;
          }
          else {
            param_1[1] = 0;
            *param_1 = (int)(param_1 + 2);
          }
          *pbVar7 = bVar4;
          pbVar2 = pbVar7 + 8;
          goto LAB_004bf6bd;
        }
        if (pbVar7 != pbVar2) break;
        param_1[1] = uVar6;
        pbVar7 = pbVar5;
      }
      param_2 = param_2 - uVar6;
      pbVar7 = pbVar5;
    } while (param_3 <= param_2);
LAB_004bf6c7:
    iVar3 = 0;
  }
  else {
    *pbVar2 = bVar4;
    if (pbVar2 + param_3 < pbVar1) {
      *param_1 = *param_1 + param_3;
      param_1[1] = param_1[1] - param_3;
    }
    else {
      param_1[1] = 0;
      *param_1 = (int)(param_1 + 2);
    }
    pbVar2 = pbVar2 + 8;
LAB_004bf6bd:
    iVar3 = (int)pbVar2 * 0x10 + (int)param_1 * -0xf;
  }
  return iVar3;
LAB_004bf645:
  if ((pbVar2 <= pbVar7) || (pbVar1 <= pbVar7 + param_3)) goto LAB_004bf6c7;
  if (*pbVar7 == 0) {
    uVar6 = 1;
    pbVar5 = pbVar7;
    while (pbVar5 = pbVar5 + 1, *pbVar5 == 0) {
      uVar6 = uVar6 + 1;
    }
    if (param_3 <= uVar6) {
      if (pbVar7 + param_3 < pbVar1) {
        *param_1 = (int)(pbVar7 + param_3);
        param_1[1] = uVar6 - param_3;
      }
      else {
        param_1[1] = 0;
        *param_1 = (int)(param_1 + 2);
      }
      *pbVar7 = bVar4;
      pbVar2 = pbVar7 + 8;
      goto LAB_004bf6bd;
    }
    param_2 = param_2 - uVar6;
    if (param_2 < param_3) goto LAB_004bf6c7;
    pbVar7 = pbVar5;
  }
  else {
    pbVar7 = pbVar7 + *pbVar7;
  }
  goto LAB_004bf645;
}


/* 004bf6ce size=169 */

undefined4 __cdecl FUN_004bf6ce(int param_1,int *param_2,byte *param_3,uint param_4)

{
  byte *pbVar1;
  int *piVar2;
  byte bVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  
  uVar6 = (uint)*param_3;
  piVar2 = (int *)(param_1 + 0x18 + ((int)param_2 - *(int *)(param_1 + 0x10) >> 0xc) * 8);
  if (param_4 < uVar6) {
    *param_3 = (byte)param_4;
    *piVar2 = *piVar2 + (uVar6 - param_4);
    piVar2[1] = 0xf1;
  }
  else {
    if (param_4 <= uVar6) {
      return 0;
    }
    pbVar1 = param_3 + param_4;
    if (param_2 + 0x3e < pbVar1) {
      return 0;
    }
    for (pbVar4 = param_3 + uVar6; (pbVar4 < pbVar1 && (*pbVar4 == 0)); pbVar4 = pbVar4 + 1) {
    }
    if (pbVar4 != pbVar1) {
      return 0;
    }
    *param_3 = (byte)param_4;
    if ((param_3 <= (byte *)*param_2) && ((byte *)*param_2 < pbVar1)) {
      if (pbVar1 < param_2 + 0x3e) {
        iVar5 = 0;
        *param_2 = (int)pbVar1;
        bVar3 = *pbVar1;
        while (bVar3 == 0) {
          iVar5 = iVar5 + 1;
          bVar3 = pbVar1[iVar5];
        }
        param_2[1] = iVar5;
      }
      else {
        param_2[1] = 0;
        *param_2 = (int)(param_2 + 2);
      }
    }
    *piVar2 = *piVar2 + (uVar6 - param_4);
  }
  return 1;
}


/* 004bf777 size=41 */

void FUN_004bf777(void)

{
  InitializeCriticalSection((LPCRITICAL_SECTION)PTR_DAT_004e319c);
  InitializeCriticalSection((LPCRITICAL_SECTION)PTR_DAT_004e318c);
  InitializeCriticalSection((LPCRITICAL_SECTION)PTR_DAT_004e317c);
  InitializeCriticalSection((LPCRITICAL_SECTION)PTR_DAT_004e315c);
  return;
}


/* 004bf7a0 size=97 */

void __cdecl FUN_004bf7a0(int param_1)

{
  int *piVar1;
  LPCRITICAL_SECTION lpCriticalSection;
  
  piVar1 = (int *)(&DAT_004e3158 + param_1 * 4);
  if (*(int *)(&DAT_004e3158 + param_1 * 4) == 0) {
    lpCriticalSection = _malloc(0x18);
    if (lpCriticalSection == (LPCRITICAL_SECTION)0x0) {
      __amsg_exit(0x11);
    }
    FUN_004bf7a0(0x11);
    if (*piVar1 == 0) {
      InitializeCriticalSection(lpCriticalSection);
      *piVar1 = (int)lpCriticalSection;
    }
    else {
      FUN_004b9d3f((undefined *)lpCriticalSection);
    }
    FUN_004bf801(0x11);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)*piVar1);
  return;
}


/* 004bf801 size=21 */

void __cdecl FUN_004bf801(int param_1)

{
  LeaveCriticalSection(*(LPCRITICAL_SECTION *)(&DAT_004e3158 + param_1 * 4));
  return;
}


/* 004bf816 size=280 */

uint __cdecl FUN_004bf816(uint param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  char *pcVar3;
  int *piVar4;
  byte bVar5;
  undefined3 extraout_var;
  undefined *puVar6;
  int *piVar7;
  
  piVar4 = param_2;
  uVar1 = param_2[3];
  uVar2 = param_2[4];
  if (((uVar1 & 0x82) == 0) || ((uVar1 & 0x40) != 0)) {
LAB_004bf922:
    param_2[3] = uVar1 | 0x20;
  }
  else {
    if ((uVar1 & 1) != 0) {
      param_2[1] = 0;
      if ((uVar1 & 0x10) == 0) goto LAB_004bf922;
      *param_2 = param_2[2];
      param_2[3] = uVar1 & 0xfffffffe;
    }
    uVar1 = param_2[3];
    param_2[1] = 0;
    param_2 = (int *)0x0;
    piVar4[3] = uVar1 & 0xffffffef | 2;
    if (((uVar1 & 0x10c) == 0) &&
       (((piVar4 != (int *)&DAT_004e0ea8 && (piVar4 != (int *)&DAT_004e0ec8)) ||
        (bVar5 = FUN_004c6071(uVar2), CONCAT31(extraout_var,bVar5) == 0)))) {
      FUN_004c602d(piVar4);
    }
    if ((*(ushort *)(piVar4 + 3) & 0x108) == 0) {
      piVar7 = (int *)0x1;
      param_2 = (int *)FUN_004c1be0(uVar2,(char *)&param_1,1);
    }
    else {
      pcVar3 = (char *)piVar4[2];
      piVar7 = (int *)(*piVar4 - (int)pcVar3);
      *piVar4 = (int)(pcVar3 + 1);
      piVar4[1] = piVar4[6] + -1;
      if ((int)piVar7 < 1) {
        if (uVar2 == 0xffffffff) {
          puVar6 = &DAT_004e3228;
        }
        else {
          puVar6 = (undefined *)((&DAT_004ed2a0)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 0x24);
        }
        if ((puVar6[4] & 0x20) != 0) {
          FUN_004c06c5(uVar2,0,2);
        }
      }
      else {
        param_2 = (int *)FUN_004c1be0(uVar2,pcVar3,(DWORD)piVar7);
      }
      *(undefined1 *)piVar4[2] = (undefined1)param_1;
    }
    if (param_2 == piVar7) {
      return param_1 & 0xff;
    }
    piVar4[3] = piVar4[3] | 0x20;
  }
  return 0xffffffff;
}


/* 004bf92e size=1825 */

/* FUN_004bf92e: lifted from original x86 -> lt_lifted.c */


