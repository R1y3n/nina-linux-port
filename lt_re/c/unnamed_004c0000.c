/* lithtech.exe decompilation - unnamed_004c0000 */
#include "ghidra_types.h"

/* 004c006f size=53 */

void __cdecl FUN_004c006f(uint param_1,int *param_2,int *param_3)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = param_2 + 1;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    uVar2 = FUN_004bf816(param_1,param_2);
  }
  else {
    *(undefined1 *)*param_2 = (undefined1)param_1;
    *param_2 = *param_2 + 1;
    uVar2 = param_1 & 0xff;
  }
  if (uVar2 == 0xffffffff) {
    *param_3 = -1;
    return;
  }
  *param_3 = *param_3 + 1;
  return;
}


/* 004c00a4 size=49 */

void __cdecl FUN_004c00a4(uint param_1,int param_2,int *param_3,int *param_4)

{
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    FUN_004c006f(param_1,param_3,param_4);
  } while (*param_4 != -1);
  return;
}


/* 004c00d5 size=56 */

void __cdecl FUN_004c00d5(char *param_1,int param_2,int *param_3,int *param_4)

{
  char cVar1;
  
  if (0 < param_2) {
    do {
      param_2 = param_2 + -1;
      cVar1 = *param_1;
      param_1 = param_1 + 1;
      FUN_004c006f((int)cVar1,param_3,param_4);
      if (*param_4 == -1) {
        return;
      }
    } while (0 < param_2);
  }
  return;
}


/* 004c010d size=13 */

undefined4 __cdecl FUN_004c010d(int *param_1)

{
  *param_1 = *param_1 + 4;
  return *(undefined4 *)(*param_1 + -4);
}


/* 004c011a size=16 */

undefined8 __cdecl FUN_004c011a(int *param_1)

{
  *param_1 = *param_1 + 8;
  return *(undefined8 *)(*param_1 + -8);
}


/* 004c012a size=14 */

undefined4 __cdecl FUN_004c012a(int *param_1)

{
  *param_1 = *param_1 + 4;
  return CONCAT22((short)((uint)*param_1 >> 0x10),*(undefined2 *)(*param_1 + -4));
}


/* 004c0138 size=93 */

undefined4 __cdecl FUN_004c0138(uint param_1)

{
  undefined4 uVar1;
  DWORD *pDVar2;
  
  if ((param_1 < DAT_004ed3a0) &&
     ((*(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
    FUN_004c6435(param_1);
    uVar1 = FUN_004c0195(param_1);
    FUN_004c6494(param_1);
    return uVar1;
  }
  pDVar2 = FUN_004c09cc();
  *pDVar2 = 9;
  pDVar2 = FUN_004c09d5();
  *pDVar2 = 0;
  return 0xffffffff;
}


/* 004c0195 size=131 */

undefined4 __cdecl FUN_004c0195(uint param_1)

{
  int iVar1;
  int iVar2;
  HANDLE hObject;
  BOOL BVar3;
  DWORD DVar4;
  undefined4 uVar5;
  
  iVar1 = FUN_004c63f3(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = FUN_004c63f3(2);
      iVar2 = FUN_004c63f3(1);
      if (iVar2 == iVar1) goto LAB_004c01e3;
    }
    hObject = (HANDLE)FUN_004c63f3(param_1);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      DVar4 = GetLastError();
      goto LAB_004c01e5;
    }
  }
LAB_004c01e3:
  DVar4 = 0;
LAB_004c01e5:
  FUN_004c6374(param_1);
  *(undefined1 *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) = 0;
  if (DVar4 == 0) {
    uVar5 = 0;
  }
  else {
    FUN_004c0959(DVar4);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}


/* 004c0243 size=368 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __cdecl FUN_004c0243(LPCSTR param_1,char *param_2,uint param_3,undefined4 *param_4)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  uint uVar5;
  uint uVar6;
  
  bVar4 = false;
  bVar3 = false;
  cVar1 = *param_2;
  if (cVar1 == 'a') {
    uVar5 = 0x109;
  }
  else {
    if (cVar1 == 'r') {
      uVar5 = 0;
      uVar6 = DAT_004eceac | 1;
      goto LAB_004c0284;
    }
    if (cVar1 != 'w') {
      return (undefined4 *)0x0;
    }
    uVar5 = 0x301;
  }
  uVar6 = DAT_004eceac | 2;
LAB_004c0284:
  bVar2 = true;
LAB_004c0287:
  cVar1 = param_2[1];
  param_2 = param_2 + 1;
  if ((cVar1 == '\0') || (!bVar2)) {
    uVar5 = FUN_004c64b6(param_1,uVar5,param_3,0x1a4);
    if ((int)uVar5 < 0) {
      return (undefined4 *)0x0;
    }
    _DAT_004eccf0 = _DAT_004eccf0 + 1;
    param_4[3] = uVar6;
    param_4[1] = 0;
    *param_4 = 0;
    param_4[2] = 0;
    param_4[7] = 0;
    param_4[4] = uVar5;
    return param_4;
  }
  if (cVar1 < 'U') {
    if (cVar1 == 'T') {
      if ((uVar5 & 0x1000) == 0) {
        uVar5 = uVar5 | 0x1000;
        goto LAB_004c0287;
      }
    }
    else if (cVar1 == '+') {
      if ((uVar5 & 2) == 0) {
        uVar5 = uVar5 & 0xfffffffe | 2;
        uVar6 = uVar6 & 0xfffffffc | 0x80;
        goto LAB_004c0287;
      }
    }
    else if (cVar1 == 'D') {
      if ((uVar5 & 0x40) == 0) {
        uVar5 = uVar5 | 0x40;
        goto LAB_004c0287;
      }
    }
    else if (cVar1 == 'R') {
      if (!bVar3) {
        bVar3 = true;
        uVar5 = uVar5 | 0x10;
        goto LAB_004c0287;
      }
    }
    else if ((cVar1 == 'S') && (!bVar3)) {
      bVar3 = true;
      uVar5 = uVar5 | 0x20;
      goto LAB_004c0287;
    }
  }
  else {
    if (cVar1 == 'b') {
      if ((uVar5 & 0xc000) != 0) goto LAB_004c0367;
      uVar5 = uVar5 | 0x8000;
      goto LAB_004c0287;
    }
    if (cVar1 == 'c') {
      if (!bVar4) {
        bVar4 = true;
        uVar6 = uVar6 | 0x4000;
        goto LAB_004c0287;
      }
    }
    else {
      if (cVar1 != 'n') {
        if ((cVar1 != 't') || ((uVar5 & 0xc000) != 0)) goto LAB_004c0367;
        uVar5 = uVar5 | 0x4000;
        goto LAB_004c0287;
      }
      if (!bVar4) {
        bVar4 = true;
        uVar6 = uVar6 & 0xffffbfff;
        goto LAB_004c0287;
      }
    }
  }
LAB_004c0367:
  bVar2 = false;
  goto LAB_004c0287;
}


/* 004c03b3 size=200 */

undefined4 * FUN_004c03b3(void)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = (undefined4 *)0x0;
  FUN_004bf7a0(2);
  iVar3 = 0;
  if (0 < DAT_004ee3e0) {
    do {
      iVar1 = *(int *)(DAT_004ed3c8 + iVar3 * 4);
      if (iVar1 == 0) {
        iVar3 = iVar3 * 4;
        pvVar2 = _malloc(0x38);
        *(void **)(iVar3 + DAT_004ed3c8) = pvVar2;
        if (*(int *)(iVar3 + DAT_004ed3c8) != 0) {
          InitializeCriticalSection((LPCRITICAL_SECTION)(*(int *)(iVar3 + DAT_004ed3c8) + 0x20));
          EnterCriticalSection((LPCRITICAL_SECTION)(*(int *)(iVar3 + DAT_004ed3c8) + 0x20));
          puVar4 = *(undefined4 **)(iVar3 + DAT_004ed3c8);
LAB_004c0457:
          if (puVar4 != (undefined4 *)0x0) {
            puVar4[4] = 0xffffffff;
            puVar4[1] = 0;
            puVar4[3] = 0;
            puVar4[2] = 0;
            *puVar4 = 0;
            puVar4[7] = 0;
          }
        }
        break;
      }
      if ((*(byte *)(iVar1 + 0xc) & 0x83) == 0) {
        FUN_004bcfd4(iVar3,iVar1);
        iVar1 = *(int *)(DAT_004ed3c8 + iVar3 * 4);
        if ((*(byte *)(iVar1 + 0xc) & 0x83) == 0) {
          puVar4 = *(undefined4 **)(DAT_004ed3c8 + iVar3 * 4);
          goto LAB_004c0457;
        }
        FUN_004bd026(iVar3,iVar1);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < DAT_004ee3e0);
  }
  FUN_004bf801(2);
  return puVar4;
}


/* 004c047b size=84 */

undefined4 FUN_004c047b(void)

{
  DWORD *lpTlsValue;
  BOOL BVar1;
  DWORD DVar2;
  
  FUN_004bf777();
  DAT_004e3220 = TlsAlloc();
  if (DAT_004e3220 != 0xffffffff) {
    lpTlsValue = (DWORD *)FUN_004c34bf(1,0x74);
    if (lpTlsValue != (DWORD *)0x0) {
      BVar1 = TlsSetValue(DAT_004e3220,lpTlsValue);
      if (BVar1 != 0) {
        FUN_004c04cf((int)lpTlsValue);
        DVar2 = GetCurrentThreadId();
        lpTlsValue[1] = 0xffffffff;
        *lpTlsValue = DVar2;
        return 1;
      }
    }
  }
  return 0;
}


/* 004c04cf size=19 */

void __cdecl FUN_004c04cf(int param_1)

{
  *(undefined **)(param_1 + 0x50) = &DAT_004e3840;
  *(undefined4 *)(param_1 + 0x14) = 1;
  return;
}


/* 004c04e2 size=103 */

DWORD * FUN_004c04e2(void)

{
  DWORD dwErrCode;
  DWORD *lpTlsValue;
  BOOL BVar1;
  DWORD DVar2;
  
  dwErrCode = GetLastError();
  lpTlsValue = TlsGetValue(DAT_004e3220);
  if (lpTlsValue == (DWORD *)0x0) {
    lpTlsValue = (DWORD *)FUN_004c34bf(1,0x74);
    if (lpTlsValue != (DWORD *)0x0) {
      BVar1 = TlsSetValue(DAT_004e3220,lpTlsValue);
      if (BVar1 != 0) {
        FUN_004c04cf((int)lpTlsValue);
        DVar2 = GetCurrentThreadId();
        lpTlsValue[1] = 0xffffffff;
        *lpTlsValue = DVar2;
        goto LAB_004c053d;
      }
    }
    __amsg_exit(0x10);
  }
LAB_004c053d:
  SetLastError(dwErrCode);
  return lpTlsValue;
}


/* 004c0549 size=160 */

void __cdecl FUN_004c0549(undefined *param_1)

{
  if (DAT_004e3220 == 0xffffffff) {
    return;
  }
  if ((param_1 != (undefined *)0x0) ||
     (param_1 = TlsGetValue(DAT_004e3220), param_1 != (undefined *)0x0)) {
    if (*(undefined **)(param_1 + 0x24) != (undefined *)0x0) {
      FUN_004b9d3f(*(undefined **)(param_1 + 0x24));
    }
    if (*(undefined **)(param_1 + 0x28) != (undefined *)0x0) {
      FUN_004b9d3f(*(undefined **)(param_1 + 0x28));
    }
    if (*(undefined **)(param_1 + 0x30) != (undefined *)0x0) {
      FUN_004b9d3f(*(undefined **)(param_1 + 0x30));
    }
    if (*(undefined **)(param_1 + 0x38) != (undefined *)0x0) {
      FUN_004b9d3f(*(undefined **)(param_1 + 0x38));
    }
    if (*(undefined **)(param_1 + 0x40) != (undefined *)0x0) {
      FUN_004b9d3f(*(undefined **)(param_1 + 0x40));
    }
    if (*(undefined **)(param_1 + 0x44) != (undefined *)0x0) {
      FUN_004b9d3f(*(undefined **)(param_1 + 0x44));
    }
    if (*(undefined **)(param_1 + 0x50) != &DAT_004e3840) {
      FUN_004b9d3f(*(undefined **)(param_1 + 0x50));
    }
    FUN_004b9d3f(param_1);
  }
  TlsSetValue(DAT_004e3220,(LPVOID)0x0);
  return;
}


/* 004c05e9 size=220 */

uint __cdecl FUN_004c05e9(undefined4 *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  
  uVar2 = param_1[3];
  if (((uVar2 & 0x83) != 0) && ((uVar2 & 0x40) == 0)) {
    if ((uVar2 & 2) == 0) {
      param_1[3] = uVar2 | 1;
      if ((uVar2 & 0x10c) == 0) {
        FUN_004c602d(param_1);
      }
      else {
        *param_1 = param_1[2];
      }
      iVar3 = FUN_004c19a2(param_1[4],(char *)param_1[2],(char *)param_1[6]);
      param_1[1] = iVar3;
      if ((iVar3 != 0) && (iVar3 != -1)) {
        if ((param_1[3] & 0x82) == 0) {
          uVar2 = param_1[4];
          if (uVar2 == 0xffffffff) {
            puVar4 = &DAT_004e3228;
          }
          else {
            puVar4 = (undefined *)((&DAT_004ed2a0)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 0x24);
          }
          if ((puVar4[4] & 0x82) == 0x82) {
            param_1[3] = param_1[3] | 0x2000;
          }
        }
        if (((param_1[6] == 0x200) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
          param_1[6] = 0x1000;
        }
        param_1[1] = iVar3 + -1;
        bVar1 = *(byte *)*param_1;
        *param_1 = (byte *)*param_1 + 1;
        return (uint)bVar1;
      }
      param_1[3] = param_1[3] | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
      param_1[1] = 0;
    }
    else {
      param_1[3] = uVar2 | 0x20;
    }
  }
  return 0xffffffff;
}


/* 004c06c5 size=101 */

DWORD __cdecl FUN_004c06c5(uint param_1,LONG param_2,DWORD param_3)

{
  DWORD DVar1;
  DWORD *pDVar2;
  
  if ((param_1 < DAT_004ed3a0) &&
     ((*(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
    FUN_004c6435(param_1);
    DVar1 = FUN_004c072a(param_1,param_2,param_3);
    FUN_004c6494(param_1);
    return DVar1;
  }
  pDVar2 = FUN_004c09cc();
  *pDVar2 = 9;
  pDVar2 = FUN_004c09d5();
  *pDVar2 = 0;
  return 0xffffffff;
}


/* 004c072a size=115 */

DWORD __cdecl FUN_004c072a(uint param_1,LONG param_2,DWORD param_3)

{
  byte *pbVar1;
  HANDLE hFile;
  DWORD *pDVar2;
  DWORD DVar3;
  uint uVar4;
  
  hFile = (HANDLE)FUN_004c63f3(param_1);
  if (hFile == (HANDLE)0xffffffff) {
    pDVar2 = FUN_004c09cc();
    *pDVar2 = 9;
  }
  else {
    DVar3 = SetFilePointer(hFile,param_2,(PLONG)0x0,param_3);
    if (DVar3 == 0xffffffff) {
      uVar4 = GetLastError();
    }
    else {
      uVar4 = 0;
    }
    if (uVar4 == 0) {
      pbVar1 = (byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24);
      *pbVar1 = *pbVar1 & 0xfd;
      return DVar3;
    }
    FUN_004c0959(uVar4);
  }
  return 0xffffffff;
}


/* 004c079d size=444 */

/* FUN_004c079d: lifted from original x86 -> lt_lifted.c */


/* 004c0959 size=115 */

void __cdecl FUN_004c0959(uint param_1)

{
  DWORD *pDVar1;
  uint *puVar2;
  int iVar3;
  
  pDVar1 = FUN_004c09d5();
  iVar3 = 0;
  *pDVar1 = param_1;
  puVar2 = &DAT_004e3250;
  do {
    if (param_1 == *puVar2) {
      pDVar1 = FUN_004c09cc();
      *pDVar1 = *(DWORD *)(iVar3 * 8 + 0x4e3254);
      return;
    }
    puVar2 = puVar2 + 2;
    iVar3 = iVar3 + 1;
  } while ((int)puVar2 < 0x4e33b8);
  if ((0x12 < param_1) && (param_1 < 0x25)) {
    pDVar1 = FUN_004c09cc();
    *pDVar1 = 0xd;
    return;
  }
  if ((param_1 < 0xbc) || (0xca < param_1)) {
    pDVar1 = FUN_004c09cc();
    *pDVar1 = 0x16;
    return;
  }
  pDVar1 = FUN_004c09cc();
  *pDVar1 = 8;
  return;
}


/* 004c09cc size=9 */

DWORD * FUN_004c09cc(void)

{
  DWORD *pDVar1;
  
  pDVar1 = FUN_004c04e2();
  return pDVar1 + 2;
}


/* 004c09d5 size=9 */

DWORD * FUN_004c09d5(void)

{
  DWORD *pDVar1;
  
  pDVar1 = FUN_004c04e2();
  return pDVar1 + 3;
}


/* 004c09de size=84 */

float10 __cdecl FUN_004c09de(int param_1,double param_2)

{
  DWORD *pDVar1;
  float10 fVar2;
  
  if (DAT_004e3bf0 == 0) {
    fVar2 = FUN_004c0f94(1,param_1);
    return fVar2;
  }
  pDVar1 = FUN_004c09cc();
  *pDVar1 = 0x21;
  FUN_004c1209();
  return (float10)param_2;
}


/* 004c0a32 size=152 */

float10 __cdecl
FUN_004c0a32(uint param_1,uint param_2,undefined8 param_3,double param_4,uint param_5)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  float10 fVar3;
  uint local_5c [14];
  uint local_24;
  
  bVar1 = FUN_004c0d7d(param_1,&param_4,param_5);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    local_24 = local_24 & 0xfffffffe;
    FUN_004c0aca(local_5c,&param_5,param_1,param_2,&param_3,&param_4);
  }
  iVar2 = FUN_004c1069((byte)param_1);
  if ((DAT_004e3bf0 == 0) && (iVar2 != 0)) {
    fVar3 = FUN_004c0f94(iVar2,param_2);
    return fVar3;
  }
  FUN_004c101c(iVar2);
  FUN_004c1209();
  return (float10)param_4;
}


/* 004c0aca size=691 */

void __cdecl
FUN_004c0aca(uint *param_1,uint *param_2,uint param_3,uint param_4,undefined8 *param_5,
            undefined8 *param_6)

{
  uint *puVar1;
  undefined8 *puVar2;
  uint uVar3;
  
  uVar3 = param_3;
  puVar1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  if ((param_3 & 0x10) != 0) {
    param_3 = 0xc000008f;
    param_1[1] = param_1[1] | 1;
  }
  if ((uVar3 & 2) != 0) {
    param_3 = 0xc0000093;
    param_1[1] = param_1[1] | 2;
  }
  if ((uVar3 & 1) != 0) {
    param_3 = 0xc0000091;
    param_1[1] = param_1[1] | 4;
  }
  if ((uVar3 & 4) != 0) {
    param_3 = 0xc000008e;
    param_1[1] = param_1[1] | 8;
  }
  if ((uVar3 & 8) != 0) {
    param_3 = 0xc0000090;
    param_1[1] = param_1[1] | 0x10;
  }
  param_1[2] = (~*param_2 & 1) << 4 | param_1[2] & 0xffffffef;
  param_1[2] = (~*param_2 & 4) << 1 | param_1[2] & 0xfffffff7;
  param_1[2] = ~*param_2 >> 1 & 4 | param_1[2] & 0xfffffffb;
  param_1[2] = ~*param_2 >> 3 & 2 | param_1[2] & 0xfffffffd;
  param_1[2] = ~*param_2 >> 5 & 1 | param_1[2] & 0xfffffffe;
  uVar3 = FUN_004c11ec();
  puVar2 = param_6;
  if ((uVar3 & 1) != 0) {
    param_1[3] = param_1[3] | 0x10;
  }
  if ((uVar3 & 4) != 0) {
    param_1[3] = param_1[3] | 8;
  }
  if ((uVar3 & 8) != 0) {
    param_1[3] = param_1[3] | 4;
  }
  if ((uVar3 & 0x10) != 0) {
    param_1[3] = param_1[3] | 2;
  }
  if ((uVar3 & 0x20) != 0) {
    param_1[3] = param_1[3] | 1;
  }
  uVar3 = *puVar1 & 0xc00;
  if (uVar3 == 0) {
    *param_1 = *param_1 & 0xfffffffc;
  }
  else {
    if (uVar3 == 0x400) {
      uVar3 = *param_1 & 0xfffffffd | 1;
    }
    else {
      if (uVar3 != 0x800) {
        if (uVar3 == 0xc00) {
          *param_1 = *param_1 | 3;
        }
        goto LAB_004c0c3f;
      }
      uVar3 = *param_1 & 0xfffffffe | 2;
    }
    *param_1 = uVar3;
  }
LAB_004c0c3f:
  uVar3 = *puVar1 & 0x300;
  if (uVar3 == 0) {
    uVar3 = *param_1 & 0xffffffeb | 8;
LAB_004c0c75:
    *param_1 = uVar3;
  }
  else {
    if (uVar3 == 0x200) {
      uVar3 = *param_1 & 0xffffffe7 | 4;
      goto LAB_004c0c75;
    }
    if (uVar3 == 0x300) {
      *param_1 = *param_1 & 0xffffffe3;
    }
  }
  *param_1 = (param_4 & 0xfff) << 5 | *param_1 & 0xfffe001f;
  param_1[8] = param_1[8] | 1;
  param_1[8] = param_1[8] & 0xffffffe3 | 2;
  *(undefined8 *)(param_1 + 4) = *param_5;
  param_1[0x14] = param_1[0x14] | 1;
  param_1[0x14] = param_1[0x14] & 0xffffffe3 | 2;
  *(undefined8 *)(param_1 + 0x10) = *param_6;
  FUN_004c11fa();
  RaiseException(param_3,0,1,(ULONG_PTR *)&param_1);
  if ((param_1[2] & 0x10) != 0) {
    *puVar1 = *puVar1 & 0xfffffffe;
  }
  if ((param_1[2] & 8) != 0) {
    *puVar1 = *puVar1 & 0xfffffffb;
  }
  if ((param_1[2] & 4) != 0) {
    *puVar1 = *puVar1 & 0xfffffff7;
  }
  if ((param_1[2] & 2) != 0) {
    *puVar1 = *puVar1 & 0xffffffef;
  }
  if ((param_1[2] & 1) != 0) {
    *puVar1 = *puVar1 & 0xffffffdf;
  }
  uVar3 = *param_1 & 3;
  if (uVar3 == 0) {
    *puVar1 = *puVar1 & 0xfffff3ff;
  }
  else {
    if (uVar3 == 1) {
      uVar3 = *puVar1 & 0xfffff7ff | 0x400;
    }
    else {
      if (uVar3 != 2) {
        if (uVar3 == 3) {
          *(byte *)((int)puVar1 + 1) = *(byte *)((int)puVar1 + 1) | 0xc;
        }
        goto LAB_004c0d4a;
      }
      uVar3 = *puVar1 & 0xfffffbff | 0x800;
    }
    *puVar1 = uVar3;
  }
LAB_004c0d4a:
  uVar3 = *param_1 >> 2 & 7;
  if (uVar3 == 0) {
    uVar3 = *puVar1 & 0xfffff3ff | 0x300;
  }
  else {
    if (uVar3 != 1) {
      if (uVar3 == 2) {
        *puVar1 = *puVar1 & 0xfffff3ff;
      }
      goto LAB_004c0d73;
    }
    uVar3 = *puVar1 & 0xfffff3ff | 0x200;
  }
  *puVar1 = uVar3;
LAB_004c0d73:
  *puVar2 = *(undefined8 *)(param_1 + 0x10);
  return;
}


/* 004c0d7d size=535 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004c0d7d: lifted from original x86 -> lt_lifted.c */


/* 004c0f94 size=136 */

float10 __cdecl FUN_004c0f94(int param_1,int param_2)

{
  int iVar1;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000020;
  
  iVar1 = FUN_004c1044(param_2);
  if (iVar1 == 0) {
    FUN_004c1209();
    FUN_004c101c(param_1);
    return (float10)(double)CONCAT44(in_stack_00000020,in_stack_0000001c);
  }
  FUN_004c1209();
  iVar1 = FUN_004c6785();
  if (iVar1 == 0) {
    FUN_004c101c(param_1);
  }
  return (float10)(double)CONCAT44(in_stack_00000020,in_stack_0000001c);
}


/* 004c101c size=40 */

void __cdecl FUN_004c101c(int param_1)

{
  DWORD *pDVar1;
  
  if (param_1 == 1) {
    pDVar1 = FUN_004c09cc();
    *pDVar1 = 0x21;
  }
  else if ((1 < param_1) && (param_1 < 4)) {
    pDVar1 = FUN_004c09cc();
    *pDVar1 = 0x22;
    return;
  }
  return;
}


/* 004c1044 size=37 */

undefined4 __cdecl FUN_004c1044(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &DAT_004e33b8;
  do {
    if (*piVar1 == param_1) {
      return *(undefined4 *)(iVar2 * 8 + 0x4e33bc);
    }
    piVar1 = piVar1 + 2;
    iVar2 = iVar2 + 1;
  } while ((int)piVar1 < 0x4e3490);
  return 0;
}


/* 004c1069 size=45 */

int __cdecl FUN_004c1069(byte param_1)

{
  int iStack_4;
  
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 8) == 0) {
      if ((param_1 & 4) == 0) {
        if ((param_1 & 1) == 0) {
          return (param_1 & 2) << 1;
        }
        iStack_4 = 3;
      }
      else {
        iStack_4 = 2;
      }
    }
    else {
      iStack_4 = 1;
    }
  }
  else {
    iStack_4 = 5;
  }
  return iStack_4;
}


/* 004c10a8 size=41 */

/* FUN_004c10a8: lifted from original x86 -> lt_lifted.c */


/* 004c10d1 size=90 */

undefined4 __cdecl FUN_004c10d1(int param_1,uint param_2)

{
  undefined4 uStack_8;
  
  if (param_2 == 0x7ff00000) {
    if (param_1 == 0) {
      return 1;
    }
  }
  else if ((param_2 == 0xfff00000) && (param_1 == 0)) {
    return 2;
  }
  if (((*(uint16_t*)((char*)&param_2+2)) & 0x7ff8) == 0x7ff8) {
    uStack_8 = 3;
  }
  else {
    if ((((*(uint16_t*)((char*)&param_2+2)) & 0x7ff8) != 0x7ff0) || (((param_2 & 0x7ffff) == 0 && (param_1 == 0)))) {
      return 0;
    }
    uStack_8 = 4;
  }
  return uStack_8;
}


/* 004c112b size=193 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_004c112b(uint param_1,uint param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  float10 fVar5;
  double local_c;
  
  if ((double)CONCAT17((*(uint8_t*)((char*)&param_2+3)),CONCAT16((*(uint8_t*)((char*)&param_2+2)),CONCAT24((ushort)param_2,param_1))) ==
      _DAT_004cbeb0) {
    iVar4 = 0;
    local_c = 0.0;
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    iVar4 = -0x3fd;
    if (_DAT_004cbeb0 <=
        (double)CONCAT17((*(uint8_t*)((char*)&param_2+3)),CONCAT16((*(uint8_t*)((char*)&param_2+2)),CONCAT24((ushort)param_2,param_1)))) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    while (((*(uint8_t*)((char*)&param_2+2)) & 0x10) == 0) {
      iVar2 = CONCAT13((*(uint8_t*)((char*)&param_2+3)),CONCAT12((*(uint8_t*)((char*)&param_2+2)),(ushort)param_2)) << 1;
      (*(uint16_t*)((char*)&param_2+0)) = (ushort)iVar2;
      (*(uint8_t*)((char*)&param_2+2)) = (byte)((uint)iVar2 >> 0x10);
      (*(uint8_t*)((char*)&param_2+3)) = (byte)((uint)iVar2 >> 0x18);
      if ((param_1 & 0x80000000) != 0) {
        (*(uint16_t*)((char*)&param_2+0)) = (ushort)param_2 | 1;
      }
      param_1 = param_1 << 1;
      iVar4 = iVar4 + -1;
    }
    uVar1 = CONCAT11((*(uint8_t*)((char*)&param_2+3)),(*(uint8_t*)((char*)&param_2+2))) & 0xffef;
    (*(uint8_t*)((char*)&param_2+2)) = (byte)uVar1;
    (*(uint8_t*)((char*)&param_2+3)) = (byte)(uVar1 >> 8);
    if (bVar3) {
      (*(uint8_t*)((char*)&param_2+3)) = (*(uint8_t*)((char*)&param_2+3)) | 0x80;
    }
    fVar5 = FUN_004c10a8(CONCAT17((*(uint8_t*)((char*)&param_2+3)),
                                  CONCAT16((*(uint8_t*)((char*)&param_2+2)),CONCAT24((ushort)param_2,param_1))),0);
    local_c = (double)fVar5;
  }
  else {
    fVar5 = FUN_004c10a8(CONCAT17((*(uint8_t*)((char*)&param_2+3)),
                                  CONCAT16((*(uint8_t*)((char*)&param_2+2)),CONCAT24((ushort)param_2,param_1))),0);
    local_c = (double)fVar5;
    iVar4 = (short)((ushort)(param_2 >> 0x14) & 0x7ff) + -0x3fe;
  }
  *param_3 = iVar4;
  return (float10)local_c;
}


/* 004c11ec size=14 */

int FUN_004c11ec(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}


/* 004c11fa size=15 */

int FUN_004c11fa(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}


/* 004c1209 size=35 */

int FUN_004c1209(void)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}


/* 004c122c size=86 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004c122c(void)

{
  return;
}


/* 004c1282 size=127 */

int __thiscall FUN_004c1282(void *this,uint *param_1,byte *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ushort local_1c [6];
  uint local_10;
  undefined4 uStack_c;
  int local_8;
  
  uVar3 = 0;
  uVar1 = FUN_004c6788(this,local_1c,&local_8,param_2,0,0,0,0);
  if ((uVar1 & 4) == 0) {
    iVar2 = FUN_004c5ba1(local_1c,&local_10);
    if (((uVar1 & 2) != 0) || (iVar2 == 1)) {
      uVar3 = 0x80;
    }
    if (((uVar1 & 1) != 0) || (iVar2 == 2)) {
      uVar3 = uVar3 | 0x100;
    }
  }
  else {
    uVar3 = 0x200;
    local_10 = 0;
    uStack_c = 0;
  }
  *param_1 = uVar3;
  *(ulonglong *)(param_1 + 4) = CONCAT44(uStack_c,local_10);
  param_1[1] = local_8 - (int)param_2;
  return;
}


/* 004c1301 size=117 */

/* FUN_004c1301: lifted from original x86 -> lt_lifted.c */


/* 004c1376 size=141 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_004c1376(undefined4 *param_1)

{
  undefined4 uVar1;
  byte bVar2;
  undefined3 extraout_var;
  int iVar3;
  void *pvVar4;
  
  bVar2 = FUN_004c6071(param_1[4]);
  if (CONCAT31(extraout_var,bVar2) == 0) {
    return 0;
  }
  if (param_1 == (undefined4 *)&DAT_004e0ea8) {
    iVar3 = 0;
  }
  else {
    if (param_1 != (undefined4 *)&DAT_004e0ec8) {
      return 0;
    }
    iVar3 = 1;
  }
  _DAT_004eccf0 = _DAT_004eccf0 + 1;
  if ((*(ushort *)(param_1 + 3) & 0x10c) != 0) {
    return 0;
  }
  if ((&DAT_004ecd5c)[iVar3] == 0) {
    pvVar4 = _malloc(0x1000);
    (&DAT_004ecd5c)[iVar3] = pvVar4;
    if (pvVar4 == (void *)0x0) {
      param_1[2] = param_1 + 5;
      *param_1 = param_1 + 5;
      param_1[6] = 2;
      param_1[1] = 2;
      goto LAB_004c13f2;
    }
  }
  uVar1 = (&DAT_004ecd5c)[iVar3];
  param_1[6] = 0x1000;
  param_1[2] = uVar1;
  *param_1 = uVar1;
  param_1[1] = 0x1000;
LAB_004c13f2:
  *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) | 0x1102;
  return 1;
}


/* 004c1403 size=42 */

void __cdecl FUN_004c1403(int param_1,int *param_2)

{
  if ((param_1 != 0) && ((*(byte *)((int)param_2 + 0xd) & 0x10) != 0)) {
    FUN_004bbef2(param_2);
    *(byte *)((int)param_2 + 0xd) = *(byte *)((int)param_2 + 0xd) & 0xee;
    param_2[6] = 0;
    *param_2 = 0;
    param_2[2] = 0;
  }
  return;
}


/* 004c1600 size=23 */

float10 __fastcall
FUN_004c1600(undefined4 param_1,uint param_2,undefined2 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float10 in_ST0;
  int local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined4 local_10;
  double dStack_c;
  
  local_14 = param_7;
  local_10 = param_8;
  dStack_c = (double)in_ST0;
  uStack_1c = param_5;
  uStack_18 = param_6;
  uStack_20 = param_1;
  FUN_004c6da2(param_2,&local_24,&param_3);
  return (float10)dStack_c;
}


/* 004c1675 size=23 */

int FUN_004c1675(void)

{
  return;
}


/* 004c168c size=25 */

undefined4 FUN_004c168c(void)

{
  uint in_EAX;
  
  if ((in_EAX & 0x80000) == 0) {
    return 1;
  }
  return 7;
}


/* 004c16e8 size=22 */

uint __cdecl FUN_004c16e8(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7ff00000) == 0x7ff00000) {
    return param_2;
  }
  return param_2 & 0x7ff00000;
}


/* 004c17f0 size=7 */

uint * __cdecl FUN_004c17f0(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = param_1;
  while (((uint)param_2 & 3) != 0) {
    bVar1 = (byte)*param_2;
    uVar3 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_004c18d8;
    *(byte *)puVar4 = bVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
  }
  do {
    uVar2 = *param_2;
    uVar3 = *param_2;
    param_2 = param_2 + 1;
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar3 == '\0') {
LAB_004c18d8:
        *(byte *)puVar4 = (byte)uVar3;
        return param_1;
      }
      if ((char)(uVar3 >> 8) == '\0') {
        *(short *)puVar4 = (short)uVar3;
        return param_1;
      }
      if ((uVar3 & 0xff0000) == 0) {
        *(short *)puVar4 = (short)uVar3;
        *(byte *)((int)puVar4 + 2) = 0;
        return param_1;
      }
      if ((uVar3 & 0xff000000) == 0) {
        *puVar4 = uVar3;
        return param_1;
      }
    }
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
  } while( true );
}


/* 004c1800 size=224 */

uint * __cdecl FUN_004c1800(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar3 = param_1;
  do {
    if (((uint)puVar3 & 3) == 0) goto LAB_004c181c;
    uVar4 = *puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_004c184f;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar5 = (uint *)((int)puVar5 + 2);
      goto joined_r0x004c186b;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_004c181c:
    do {
      puVar5 = puVar3;
      puVar3 = puVar5 + 1;
    } while (((*puVar5 ^ 0xffffffff ^ *puVar5 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar5;
    if ((char)uVar4 == '\0') goto joined_r0x004c186b;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar5 = (uint *)((int)puVar5 + 1);
      goto joined_r0x004c186b;
    }
  }
LAB_004c184f:
  puVar5 = (uint *)((int)puVar3 + -1);
joined_r0x004c186b:
  do {
    if (((uint)param_2 & 3) == 0) {
      do {
        uVar2 = *param_2;
        uVar4 = *param_2;
        param_2 = param_2 + 1;
        if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
          if ((char)uVar4 == '\0') {
LAB_004c18d8:
            *(byte *)puVar5 = (byte)uVar4;
            return param_1;
          }
          if ((char)(uVar4 >> 8) == '\0') {
            *(short *)puVar5 = (short)uVar4;
            return param_1;
          }
          if ((uVar4 & 0xff0000) == 0) {
            *(short *)puVar5 = (short)uVar4;
            *(byte *)((int)puVar5 + 2) = 0;
            return param_1;
          }
          if ((uVar4 & 0xff000000) == 0) {
            *puVar5 = uVar4;
            return param_1;
          }
        }
        *puVar5 = uVar4;
        puVar5 = puVar5 + 1;
      } while( true );
    }
    bVar1 = (byte)*param_2;
    uVar4 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_004c18d8;
    *(byte *)puVar5 = bVar1;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while( true );
}


/* 004c18e0 size=194 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl
FUN_004c18e0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  int iVar4;
  int local_28 [2];
  int local_20;
  int local_18;
  uint local_14;
  int local_c;
  
  uVar3 = param_1 - 0x76c;
  if (((int)uVar3 < 0x46) || (0x8a < (int)uVar3)) {
    return -1;
  }
  iVar4 = *(int *)(&DAT_004e3cd4 + param_2 * 4) + param_3;
  if (((uVar3 & 3) == 0) && (2 < param_2)) {
    iVar4 = iVar4 + 1;
  }
  FUN_004c6e72();
  local_20 = param_4;
  local_18 = param_2 + -1;
  iVar2 = ((param_4 + (uVar3 * 0x16d + iVar4 + (param_1 + -0x76d >> 2)) * 0x18) * 0x3c + param_5) *
          0x3c + DAT_004e3bf4 + 0x7c558180 + param_6;
  if ((param_7 == 1) ||
     (((param_7 == -1 && (DAT_004e3bf8 != 0)) &&
      (local_14 = uVar3, local_c = iVar4, bVar1 = FUN_004c7127(local_28),
      CONCAT31(extraout_var,bVar1) != 0)))) {
    iVar2 = iVar2 + _DAT_004e3bfc;
  }
  return iVar2;
}


/* 004c19a2 size=101 */

int __cdecl FUN_004c19a2(uint param_1,char *param_2,char *param_3)

{
  int iVar1;
  DWORD *pDVar2;
  
  if ((param_1 < DAT_004ed3a0) &&
     ((*(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
    FUN_004c6435(param_1);
    iVar1 = FUN_004c1a07(param_1,param_2,param_3);
    FUN_004c6494(param_1);
    return iVar1;
  }
  pDVar2 = FUN_004c09cc();
  *pDVar2 = 9;
  pDVar2 = FUN_004c09d5();
  *pDVar2 = 0;
  return -1;
}


/* 004c1a07 size=473 */

int __cdecl FUN_004c1a07(uint param_1,char *param_2,char *param_3)

{
  int *piVar1;
  byte *pbVar2;
  char cVar3;
  byte bVar4;
  BOOL BVar5;
  DWORD DVar6;
  DWORD *pDVar7;
  char *pcVar8;
  int iVar9;
  DWORD local_10;
  char *local_c;
  char local_5;
  
  local_c = (char *)0x0;
  if (param_3 != (char *)0x0) {
    piVar1 = &DAT_004ed2a0 + ((int)param_1 >> 5);
    iVar9 = (param_1 & 0x1f) * 0x24;
    bVar4 = *(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + iVar9 + 4);
    if ((bVar4 & 2) == 0) {
      pcVar8 = param_2;
      if (((bVar4 & 0x48) != 0) &&
         (cVar3 = *(char *)((&DAT_004ed2a0)[(int)param_1 >> 5] + iVar9 + 5), cVar3 != '\n')) {
        param_3 = param_3 + -1;
        *param_2 = cVar3;
        pcVar8 = param_2 + 1;
        local_c = (char *)0x1;
        *(undefined1 *)(*piVar1 + 5 + iVar9) = 10;
      }
      BVar5 = ReadFile(*(HANDLE *)(*piVar1 + iVar9),pcVar8,(DWORD)param_3,&local_10,
                       (LPOVERLAPPED)0x0);
      if (BVar5 == 0) {
        DVar6 = GetLastError();
        if (DVar6 == 5) {
          pDVar7 = FUN_004c09cc();
          *pDVar7 = 9;
          pDVar7 = FUN_004c09d5();
          *pDVar7 = 5;
        }
        else {
          if (DVar6 == 0x6d) {
            return 0;
          }
          FUN_004c0959(DVar6);
        }
        return -1;
      }
      local_c = (char *)((int)local_c + local_10);
      bVar4 = *(byte *)(*piVar1 + 4 + iVar9);
      if ((bVar4 & 0x80) != 0) {
        if ((local_10 == 0) || (*param_2 != '\n')) {
          bVar4 = bVar4 & 0xfb;
        }
        else {
          bVar4 = bVar4 | 4;
        }
        *(byte *)(*piVar1 + 4 + iVar9) = bVar4;
        param_3 = param_2;
        local_c = param_2 + (int)local_c;
        pcVar8 = param_2;
        if (param_2 < local_c) {
          do {
            cVar3 = *param_3;
            if (cVar3 == '\x1a') {
              pbVar2 = (byte *)(*piVar1 + 4 + iVar9);
              bVar4 = *pbVar2;
              if ((bVar4 & 0x40) == 0) {
                *pbVar2 = bVar4 | 2;
              }
              break;
            }
            if (cVar3 == '\r') {
              if (param_3 < local_c + -1) {
                if (param_3[1] == '\n') {
                  param_3 = param_3 + 2;
                  goto LAB_004c1b92;
                }
                *pcVar8 = '\r';
                pcVar8 = pcVar8 + 1;
                param_3 = param_3 + 1;
              }
              else {
                param_3 = param_3 + 1;
                BVar5 = ReadFile(*(HANDLE *)(*piVar1 + iVar9),&local_5,1,&local_10,(LPOVERLAPPED)0x0
                                );
                if (((BVar5 == 0) && (DVar6 = GetLastError(), DVar6 != 0)) || (local_10 == 0)) {
LAB_004c1bac:
                  *pcVar8 = '\r';
LAB_004c1baf:
                  pcVar8 = pcVar8 + 1;
                }
                else if ((*(byte *)(*piVar1 + 4 + iVar9) & 0x48) == 0) {
                  if ((pcVar8 == param_2) && (local_5 == '\n')) {
LAB_004c1b92:
                    *pcVar8 = '\n';
                    goto LAB_004c1baf;
                  }
                  FUN_004c072a(param_1,-1,1);
                  if (local_5 != '\n') goto LAB_004c1bac;
                }
                else {
                  if (local_5 == '\n') goto LAB_004c1b92;
                  *pcVar8 = '\r';
                  pcVar8 = pcVar8 + 1;
                  *(char *)(*piVar1 + 5 + iVar9) = local_5;
                }
              }
            }
            else {
              *pcVar8 = cVar3;
              pcVar8 = pcVar8 + 1;
              param_3 = param_3 + 1;
            }
          } while (param_3 < local_c);
        }
        local_c = (char *)((int)pcVar8 - (int)param_2);
      }
      return (int)local_c;
    }
  }
  return 0;
}


/* 004c1be0 size=101 */

int __cdecl FUN_004c1be0(uint param_1,char *param_2,DWORD param_3)

{
  int iVar1;
  DWORD *pDVar2;
  
  if ((param_1 < DAT_004ed3a0) &&
     ((*(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
    FUN_004c6435(param_1);
    iVar1 = FUN_004c1c45(param_1,param_2,param_3);
    FUN_004c6494(param_1);
    return iVar1;
  }
  pDVar2 = FUN_004c09cc();
  *pDVar2 = 9;
  pDVar2 = FUN_004c09d5();
  *pDVar2 = 0;
  return -1;
}


/* 004c1c45 size=395 */

int __cdecl FUN_004c1c45(DWORD param_1,char *param_2,DWORD param_3)

{
  int *piVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  BOOL BVar6;
  DWORD *pDVar7;
  char local_418 [1028];
  int local_14;
  DWORD local_10;
  DWORD local_c;
  char *local_8;
  
  local_c = 0;
  local_14 = 0;
  if (param_3 == 0) {
LAB_004c1c5e:
    iVar4 = 0;
  }
  else {
    piVar1 = &DAT_004ed2a0 + ((int)param_1 >> 5);
    iVar4 = (param_1 & 0x1f) * 0x24;
    if ((*(byte *)(*piVar1 + 4 + iVar4) & 0x20) != 0) {
      FUN_004c072a(param_1,0,2);
    }
    if ((*(byte *)((undefined4 *)(*piVar1 + iVar4) + 1) & 0x80) == 0) {
      BVar6 = WriteFile(*(HANDLE *)(*piVar1 + iVar4),param_2,param_3,&local_10,(LPOVERLAPPED)0x0);
      if (BVar6 == 0) {
        param_1 = GetLastError();
      }
      else {
        param_1 = 0;
        local_c = local_10;
      }
LAB_004c1d2d:
      if (local_c != 0) {
        return local_c - local_14;
      }
      if (param_1 == 0) goto LAB_004c1d9f;
      if (param_1 == 5) {
        pDVar7 = FUN_004c09cc();
        *pDVar7 = 9;
        pDVar7 = FUN_004c09d5();
        *pDVar7 = 5;
      }
      else {
        FUN_004c0959(param_1);
      }
    }
    else {
      local_8 = param_2;
      param_1 = 0;
      if (param_3 != 0) {
        do {
          pcVar5 = local_418;
          do {
            if (param_3 <= (uint)((int)local_8 - (int)param_2)) break;
            pcVar2 = local_8 + 1;
            cVar3 = *local_8;
            local_8 = pcVar2;
            if (cVar3 == '\n') {
              local_14 = local_14 + 1;
              *pcVar5 = '\r';
              pcVar5 = pcVar5 + 1;
            }
            *pcVar5 = cVar3;
            pcVar5 = pcVar5 + 1;
          } while ((int)pcVar5 - (int)local_418 < 0x400);
          BVar6 = WriteFile(*(HANDLE *)(*piVar1 + iVar4),local_418,(int)pcVar5 - (int)local_418,
                            &local_10,(LPOVERLAPPED)0x0);
          if (BVar6 == 0) {
            param_1 = GetLastError();
            goto LAB_004c1d2d;
          }
          local_c = local_c + local_10;
          if (((int)local_10 < (int)pcVar5 - (int)local_418) ||
             (param_3 <= (uint)((int)local_8 - (int)param_2))) goto LAB_004c1d2d;
        } while( true );
      }
LAB_004c1d9f:
      if (((*(byte *)(*piVar1 + 4 + iVar4) & 0x40) != 0) && (*param_2 == '\x1a')) goto LAB_004c1c5e;
      pDVar7 = FUN_004c09cc();
      *pDVar7 = 0x1c;
      pDVar7 = FUN_004c09d5();
      *pDVar7 = 0;
    }
    iVar4 = -1;
  }
  return iVar4;
}


/* 004c1dd0 size=2597 */

/* FUN_004c1dd0: lifted from original x86 -> lt_lifted.c */


/* 004c27f5 size=55 */

/* FUN_004c27f5: lifted from original x86 -> lt_lifted.c */


/* 004c282c size=26 */

uint __cdecl FUN_004c282c(undefined4 *param_1)

{
  int *piVar1;
  byte bVar2;
  uint uVar3;
  
  piVar1 = param_1 + 1;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    uVar3 = FUN_004c05e9(param_1);
    return uVar3;
  }
  bVar2 = *(byte *)*param_1;
  *param_1 = (byte *)*param_1 + 1;
  return (uint)bVar2;
}


/* 004c2846 size=23 */

void __cdecl FUN_004c2846(uint param_1,int *param_2)

{
  if (param_1 != 0xffffffff) {
    FUN_004c757f(param_1,param_2);
  }
  return;
}


/* 004c285d size=36 */

uint __cdecl FUN_004c285d(int *param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  void *this;
  
  do {
    *param_1 = *param_1 + 1;
    uVar1 = FUN_004c282c(param_2);
    uVar2 = FUN_004baf4f(this,uVar1);
  } while (uVar2 != 0);
  return uVar1;
}


/* 004c2881 size=155 */

undefined4 __cdecl
FUN_004c2881(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,undefined4 param_4,int *param_5,
            int param_6,PVOID param_7,char param_8)

{
  code *pcVar1;
  undefined4 uVar2;
  
  if (*param_5 != 0x19930520) {
    FUN_004c314d();
  }
  if ((param_1->ExceptionFlags & 0x66) == 0) {
    if (param_5[3] != 0) {
      if (((param_1->ExceptionCode == 0xe06d7363) && (0x19930520 < param_1->ExceptionInformation[0])
          ) && (pcVar1 = *(code **)(param_1->ExceptionInformation[2] + 8), pcVar1 != (code *)0x0)) {
        uVar2 = (*pcVar1)(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        return uVar2;
      }
      FUN_004c291c(param_1,param_2,param_3,param_4,(uint)param_5,param_8,param_6,param_7);
    }
  }
  else if ((param_5[1] != 0) && (param_6 == 0)) {
    FUN_004c2bd6((int)param_2,param_4,(int)param_5,-1);
  }
  return 1;
}


/* 004c291c size=435 */

void __cdecl
FUN_004c291c(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,undefined4 param_4,uint param_5,
            char param_6,int param_7,PVOID param_8)

{
  byte *pbVar1;
  bool bVar2;
  DWORD *pDVar3;
  undefined3 extraout_var;
  int *piVar4;
  int iVar5;
  int *piVar6;
  uint local_1c;
  uint local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_18 = local_18 & 0xffffff00;
  local_14 = *(int *)((int)param_2 + 8);
  if ((local_14 < -1) || (*(int *)(param_5 + 4) <= local_14)) {
    FUN_004c314d();
  }
  if (param_1->ExceptionCode == 0xe06d7363) {
    if (((param_1->NumberParameters == 3) && (param_1->ExceptionInformation[0] == 0x19930520)) &&
       (param_1->ExceptionInformation[2] == 0)) {
      pDVar3 = FUN_004c04e2();
      if (pDVar3[0x1b] == 0) {
        return;
      }
      pDVar3 = FUN_004c04e2();
      param_1 = (PEXCEPTION_RECORD)pDVar3[0x1b];
      pDVar3 = FUN_004c04e2();
      param_3 = pDVar3[0x1c];
      local_18 = CONCAT31((*(uint32_t*)((char*)&local_18+1)),1);
      bVar2 = FUN_004c75ed(param_1,1);
      if (CONCAT31(extraout_var,bVar2) == 0) {
        FUN_004c314d();
      }
      if (param_1->ExceptionCode != 0xe06d7363) goto LAB_004c2aa4;
      if (((param_1->NumberParameters == 3) && (param_1->ExceptionInformation[0] == 0x19930520)) &&
         (param_1->ExceptionInformation[2] == 0)) {
        FUN_004c314d();
      }
    }
    iVar5 = local_14;
    if (((param_1->ExceptionCode == 0xe06d7363) && (param_1->NumberParameters == 3)) &&
       (param_1->ExceptionInformation[0] == 0x19930520)) {
      piVar4 = (int *)FUN_004bbba7(param_5,param_7,local_14,&local_8,&local_1c);
      do {
        if (local_1c <= local_8) {
          if (param_6 == '\0') {
            return;
          }
          FUN_004c300e((int)param_1);
          return;
        }
        if ((*piVar4 <= iVar5) && (iVar5 <= piVar4[1])) {
          pbVar1 = (byte *)piVar4[4];
          for (local_10 = piVar4[3]; 0 < local_10; local_10 = local_10 + -1) {
            piVar6 = *(int **)(param_1->ExceptionInformation[2] + 0xc);
            for (local_c = *piVar6; 0 < local_c; local_c = local_c + -1) {
              piVar6 = piVar6 + 1;
              iVar5 = FUN_004c2b79(pbVar1,(byte *)*piVar6,(uint *)param_1->ExceptionInformation[2]);
              if (iVar5 != 0) {
                FUN_004c2c8a(param_1,param_2,param_3,param_4,param_5,pbVar1,(byte *)*piVar6,piVar4,
                             param_7,param_8);
                goto LAB_004c2a81;
              }
            }
            pbVar1 = pbVar1 + 0x10;
          }
LAB_004c2a81:
          iVar5 = local_14;
        }
        local_8 = local_8 + 1;
        piVar4 = piVar4 + 5;
      } while( true );
    }
  }
LAB_004c2aa4:
  if (param_6 == '\0') {
    FUN_004c2acf(param_1,param_2,param_3,param_4,param_5,local_14,param_7,param_8);
    return;
  }
  FUN_004c30ec();
  return;
}


/* 004c2acf size=170 */

void __cdecl
FUN_004c2acf(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,undefined4 param_4,uint param_5,
            int param_6,int param_7,PVOID param_8)

{
  DWORD *pDVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint local_c;
  uint local_8;
  
  pDVar1 = FUN_004c04e2();
  if ((pDVar1[0x1a] != 0) &&
     (iVar2 = FUN_004bba7c(&param_1->ExceptionCode,param_2,param_3,param_4,param_5,param_7,param_8),
     iVar2 != 0)) {
    return;
  }
  piVar3 = (int *)FUN_004bbba7(param_5,param_7,param_6,&local_8,&local_c);
  for (; local_8 < local_c; local_8 = local_8 + 1) {
    if ((*piVar3 <= param_6) && (param_6 <= piVar3[1])) {
      iVar4 = piVar3[3] * 0x10 + piVar3[4];
      iVar2 = *(int *)(iVar4 + -0xc);
      if ((iVar2 == 0) || (*(char *)(iVar2 + 8) == '\0')) {
        FUN_004c2c8a(param_1,param_2,param_3,param_4,param_5,(byte *)(iVar4 + -0x10),(byte *)0x0,
                     piVar3,param_7,param_8);
      }
    }
    piVar3 = piVar3 + 5;
  }
  return;
}


/* 004c2b79 size=93 */

undefined4 __cdecl FUN_004c2b79(byte *param_1,byte *param_2,uint *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 4);
  if ((iVar1 == 0) || (*(char *)(iVar1 + 8) == '\0')) {
LAB_004c2bd0:
    uVar2 = 1;
  }
  else {
    if (iVar1 == *(int *)(param_2 + 4)) {
LAB_004c2baa:
      if (((((*param_2 & 2) == 0) || ((*param_1 & 8) != 0)) &&
          (((*param_3 & 1) == 0 || ((*param_1 & 1) != 0)))) &&
         (((*param_3 & 2) == 0 || ((*param_1 & 2) != 0)))) goto LAB_004c2bd0;
    }
    else {
      iVar1 = _strcmp((char *)(iVar1 + 8),(char *)(*(int *)(param_2 + 4) + 8));
      if (iVar1 == 0) goto LAB_004c2baa;
    }
    uVar2 = 0;
  }
  return uVar2;
}


/* 004c2bd6 size=132 */

void __cdecl FUN_004c2bd6(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004cf318;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  for (iVar2 = *(int *)(param_1 + 8); local_8 = 0xffffffff, iVar2 != param_4;
      iVar2 = *(int *)(*(int *)(param_3 + 8) + iVar2 * 8)) {
    if ((iVar2 < 0) || (*(int *)(param_3 + 4) <= iVar2)) {
      FUN_004c314d();
    }
    local_8 = 0;
    iVar1 = *(int *)(*(int *)(param_3 + 8) + 4 + iVar2 * 8);
    if (iVar1 != 0) {
      __CallSettingFrame_12(iVar1,param_1,0x103);
    }
  }
  *(int *)(param_1 + 8) = iVar2;
  ExceptionList = local_14;
  return;
}


/* 004c2c8a size=123 */

void __cdecl
FUN_004c2c8a(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,undefined4 param_4,int param_5,
            byte *param_6,byte *param_7,int *param_8,int param_9,PVOID param_10)

{
  undefined *UNRECOVERED_JUMPTABLE;
  
  if (param_7 != (byte *)0x0) {
    FUN_004c2e4a((int)param_1,(int)param_2,param_6,param_7);
  }
  if (param_10 == (PVOID)0x0) {
    param_10 = param_2;
  }
  else {
  }
  FUN_004bb97e(param_10,param_1);
  FUN_004c2bd6((int)param_2,param_4,param_5,*param_8);
  *(int *)((int)param_2 + 8) = param_8[1] + 1;
  UNRECOVERED_JUMPTABLE =
       (undefined *)
       FUN_004c2d05((DWORD)param_1,param_2,param_3,param_5,*(undefined4 *)(param_6 + 0xc),param_9,
                    0x100);
  if (UNRECOVERED_JUMPTABLE != (undefined *)0x0) {
    FUN_004bb93c(UNRECOVERED_JUMPTABLE);
  }
  return;
}


/* 004c2d05 size=165 */

undefined4 __cdecl
FUN_004c2d05(DWORD param_1,undefined4 param_2,DWORD param_3,undefined4 param_4,undefined4 param_5,
            int param_6,int param_7)

{
  DWORD *pDVar1;
  undefined4 uVar2;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf328;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  FUN_004c04e2();
  FUN_004c04e2();
  pDVar1 = FUN_004c04e2();
  pDVar1[0x1b] = param_1;
  pDVar1 = FUN_004c04e2();
  pDVar1[0x1c] = param_3;
  local_8 = 1;
  uVar2 = FUN_004bba03(param_2,param_4,param_5,param_6,param_7);
  local_8 = 0xffffffff;
  FUN_004c2dd2();
  ExceptionList = local_14;
  return uVar2;
}


/* 004c2dd2 size=78 */

void FUN_004c2dd2(void)

{
  DWORD *pDVar1;
  int unaff_EBP;
  int unaff_ESI;
  int *unaff_EDI;
  
  *(undefined4 *)(unaff_ESI + -4) = *(undefined4 *)(unaff_EBP + -0x28);
  pDVar1 = FUN_004c04e2();
  pDVar1[0x1b] = *(DWORD *)(unaff_EBP + -0x1c);
  pDVar1 = FUN_004c04e2();
  pDVar1[0x1c] = *(DWORD *)(unaff_EBP + -0x20);
  if ((((*unaff_EDI == -0x1f928c9d) && (unaff_EDI[4] == 3)) && (unaff_EDI[5] == 0x19930520)) &&
     ((*(int *)(unaff_EBP + -0x24) == 0 && (*(int *)(unaff_EBP + -0x2c) != 0)))) {
    __abnormal_termination();
    FUN_004c300e((int)unaff_EDI);
  }
  return;
}


/* 004c2e4a size=440 */

void __cdecl FUN_004c2e4a(int param_1,int param_2,byte *param_3,byte *param_4)

{
  int *piVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar3;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined4 *puVar4;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  uint uVar5;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004cf340;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  if (*(int *)(param_3 + 4) == 0) {
    return;
  }
  if (*(char *)(*(int *)(param_3 + 4) + 8) == '\0') {
    return;
  }
  if (*(int *)(param_3 + 8) == 0) {
    return;
  }
  piVar1 = (int *)(*(int *)(param_3 + 8) + 0xc + param_2);
  local_8 = 0;
  if ((*param_3 & 8) == 0) {
    if ((*param_4 & 1) == 0) {
      if (*(int *)(param_4 + 0x18) == 0) {
        ExceptionList = &local_14;
        bVar2 = FUN_004c75ed(*(void **)(param_1 + 0x18),1);
        if ((CONCAT31(extraout_var_03,bVar2) != 0) &&
           (bVar2 = FUN_004c7609(piVar1,1), CONCAT31(extraout_var_04,bVar2) != 0)) {
          uVar5 = *(uint *)(param_4 + 0x14);
          puVar4 = (undefined4 *)FUN_004c3075(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
          FUN_004bab10(piVar1,puVar4,uVar5);
          ExceptionList = local_14;
          return;
        }
      }
      else {
        ExceptionList = &local_14;
        bVar2 = FUN_004c75ed(*(void **)(param_1 + 0x18),1);
        if (((CONCAT31(extraout_var_05,bVar2) != 0) &&
            (bVar2 = FUN_004c7609(piVar1,1), CONCAT31(extraout_var_06,bVar2) != 0)) &&
           (bVar2 = FUN_004c7625(*(FARPROC *)(param_4 + 0x18)), CONCAT31(extraout_var_07,bVar2) != 0
           )) {
          if ((*param_4 & 4) == 0) {
            FUN_004c3075(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
            FUN_004bb970(piVar1,*(undefined **)(param_4 + 0x18));
            ExceptionList = local_14;
            return;
          }
          FUN_004c3075(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
          FUN_004bb977(piVar1,*(undefined **)(param_4 + 0x18));
          ExceptionList = local_14;
          return;
        }
      }
    }
    else {
      ExceptionList = &local_14;
      bVar2 = FUN_004c75ed(*(void **)(param_1 + 0x18),1);
      if ((CONCAT31(extraout_var_01,bVar2) != 0) &&
         (bVar2 = FUN_004c7609(piVar1,1), CONCAT31(extraout_var_02,bVar2) != 0)) {
        FUN_004bab10(piVar1,*(undefined4 **)(param_1 + 0x18),*(uint *)(param_4 + 0x14));
        if (*(int *)(param_4 + 0x14) != 4) {
          ExceptionList = local_14;
          return;
        }
        iVar3 = *piVar1;
        if (iVar3 == 0) {
          ExceptionList = local_14;
          return;
        }
        goto LAB_004c2ed8;
      }
    }
  }
  else {
    ExceptionList = &local_14;
    bVar2 = FUN_004c75ed(*(void **)(param_1 + 0x18),1);
    if ((CONCAT31(extraout_var,bVar2) != 0) &&
       (bVar2 = FUN_004c7609(piVar1,1), CONCAT31(extraout_var_00,bVar2) != 0)) {
      iVar3 = *(int *)(param_1 + 0x18);
      *piVar1 = iVar3;
LAB_004c2ed8:
      iVar3 = FUN_004c3075(iVar3,(int *)(param_4 + 8));
      *piVar1 = iVar3;
      ExceptionList = local_14;
      return;
    }
  }
  FUN_004c314d();
  ExceptionList = local_14;
  return;
}


/* 004c300e size=86 */

void __cdecl FUN_004c300e(int param_1)

{
  undefined *UNRECOVERED_JUMPTABLE;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004cf350;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  if ((param_1 != 0) &&
     (UNRECOVERED_JUMPTABLE = *(undefined **)(*(int *)(param_1 + 0x1c) + 4),
     UNRECOVERED_JUMPTABLE != (undefined *)0x0)) {
    local_8 = 0;
    ExceptionList = &local_14;
    FUN_004bb970(*(undefined4 *)(param_1 + 0x18),UNRECOVERED_JUMPTABLE);
  }
  ExceptionList = local_14;
  return;
}


/* 004c3075 size=35 */

int __cdecl FUN_004c3075(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_2[1];
  iVar2 = *param_2 + param_1;
  if (-1 < iVar1) {
    iVar2 = iVar2 + *(int *)(*(int *)(iVar1 + param_1) + param_2[2]) + iVar1;
  }
  return iVar2;
}


/* 004c30ec size=86 */

int FUN_004c30ec(void)

{
  DWORD *pDVar1;
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004cf360;
  puStack_10 = &LAB_004ba918;
  pvStack_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &pvStack_14;
  pDVar1 = FUN_004c04e2();
  if (pDVar1[0x18] != 0) {
    local_8 = 1;
    pDVar1 = FUN_004c04e2();
    (*(code *)pDVar1[0x18])();
  }
  local_8 = 0xffffffff;
  FUN_004c763d();
  return;
}


/* 004c314d size=79 */

void FUN_004c314d(void)

{
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004cf378;
  puStack_10 = &LAB_004ba918;
  pvStack_14 = ExceptionList;
  ExceptionList = &pvStack_14;
  if (PTR_FUN_004e3730 != (undefined *)0x0) {
    local_8 = 1;
    ExceptionList = &pvStack_14;
    (*(code *)PTR_FUN_004e3730)();
  }
  local_8 = 0xffffffff;
  FUN_004c30ec();
  return;
}


/* 004c31a3 size=76 */

int FUN_004c31a3(void)

{
  return;
}


/* 004c3208 size=511 */

int __cdecl
FUN_004c3208(LCID param_1,DWORD param_2,char *param_3,int param_4,LPWSTR param_5,int param_6,
            UINT param_7,int param_8)

{
  int iVar1;
  int iVar2;
  undefined1 unaff_DI;
  undefined1 uStack00000000;
  WCHAR aWStack_2e [13];
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf3a8;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  if (DAT_004ecd90 == 0) {
    ExceptionList = &local_14;
    iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,"",1,(LPSTR)0x0,0);
      if (iVar1 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      DAT_004ecd90 = 2;
    }
    else {
      DAT_004ecd90 = 1;
    }
  }
  if (0 < param_4) {
    param_4 = FUN_004c879c(param_3,param_4);
  }
  if (DAT_004ecd90 == 2) {
    iVar1 = LCMapStringA(param_1,param_2,param_3,param_4,(LPSTR)param_5,param_6);
    ExceptionList = local_14;
    return iVar1;
  }
  if (DAT_004ecd90 == 1) {
    if (param_7 == 0) {
      param_7 = DAT_004ecd88;
    }
    iVar1 = MultiByteToWideChar(param_7,(-(uint)(param_8 != 0) & 8) + 1,param_3,param_4,(LPWSTR)0x0,
                                0);
    if (iVar1 == 0) {
      ExceptionList = local_14;
      return 0;
    }
    local_8 = 0;
    FUN_004ba7f0(unaff_DI);
    local_8 = 0xffffffff;
    if (&uStack00000000 == (undefined1 *)0x3c) {
      ExceptionList = local_14;
      return 0;
    }
    iVar2 = MultiByteToWideChar(param_7,1,param_3,param_4,aWStack_2e + -7,iVar1);
    if (iVar2 == 0) {
      ExceptionList = local_14;
      return 0;
    }
    iVar2 = LCMapStringW(param_1,param_2,aWStack_2e + -7,iVar1,(LPWSTR)0x0,0);
    if (iVar2 == 0) {
      ExceptionList = local_14;
      return 0;
    }
    if ((param_2 & 0x400) == 0) {
      local_8 = 1;
      FUN_004ba7f0(unaff_DI);
      local_8 = 0xffffffff;
      if (&uStack00000000 == (undefined1 *)0x3c) {
        ExceptionList = local_14;
        return 0;
      }
      iVar1 = LCMapStringW(param_1,param_2,aWStack_2e + -7,iVar1,aWStack_2e + -7,iVar2);
      if (iVar1 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      if (param_6 == 0) {
        param_6 = 0;
        param_5 = (LPWSTR)0x0;
      }
      iVar2 = WideCharToMultiByte(param_7,0x220,aWStack_2e + -7,iVar2,(LPSTR)param_5,param_6,
                                  (LPCSTR)0x0,(LPBOOL)0x0);
      iVar1 = iVar2;
    }
    else {
      if (param_6 == 0) {
        ExceptionList = local_14;
        return iVar2;
      }
      if (param_6 < iVar2) {
        ExceptionList = local_14;
        return 0;
      }
      iVar1 = LCMapStringW(param_1,param_2,aWStack_2e + -7,iVar1,param_5,param_6);
    }
    if (iVar1 != 0) {
      ExceptionList = local_14;
      return iVar2;
    }
  }
  ExceptionList = local_14;
  return 0;
}


/* 004c342c size=147 */

undefined4 __cdecl FUN_004c342c(uint param_1)

{
  HANDLE hFile;
  BOOL BVar1;
  DWORD DVar2;
  DWORD *pDVar3;
  int iVar4;
  undefined4 uVar5;
  
  if (DAT_004ed3a0 <= param_1) {
LAB_004c34ad:
    pDVar3 = FUN_004c09cc();
    *pDVar3 = 9;
    return 0xffffffff;
  }
  iVar4 = (param_1 & 0x1f) * 0x24;
  if ((*(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + iVar4) & 1) == 0) goto LAB_004c34ad;
  FUN_004c6435(param_1);
  if ((*(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + iVar4) & 1) != 0) {
    hFile = (HANDLE)FUN_004c63f3(param_1);
    BVar1 = FlushFileBuffers(hFile);
    if (BVar1 == 0) {
      DVar2 = GetLastError();
    }
    else {
      DVar2 = 0;
    }
    uVar5 = 0;
    if (DVar2 == 0) goto LAB_004c34a2;
    pDVar3 = FUN_004c09d5();
    *pDVar3 = DVar2;
  }
  pDVar3 = FUN_004c09cc();
  *pDVar3 = 9;
  uVar5 = 0xffffffff;
LAB_004c34a2:
  FUN_004c6494(param_1);
  return uVar5;
}


/* 004c34bf size=289 */

int * __cdecl FUN_004c34bf(int param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  uint *_Size;
  int *local_24;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf3c0;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  puVar2 = (uint *)(param_1 * param_2);
  puVar3 = puVar2;
  ExceptionList = &local_14;
  if (puVar2 < (uint *)0xffffffe1) {
    if (puVar2 == (uint *)0x0) {
      puVar3 = (uint *)0x1;
    }
    puVar3 = (uint *)((int)puVar3 + 0xfU & 0xfffffff0);
    ExceptionList = &local_14;
  }
  do {
    local_24 = (int *)0x0;
    if (puVar3 < (uint *)0xffffffe1) {
      if (DAT_004ed3c4 == 3) {
        if (puVar2 <= DAT_004ed3bc) {
          FUN_004bf7a0(9);
          local_8 = 0;
          local_24 = FUN_004be8ff(puVar2);
          local_8 = 0xffffffff;
          FUN_004c3558();
          if (local_24 == (int *)0x0) goto LAB_004c35ac;
          _Size = puVar2;
LAB_004c359b:
          _memset(local_24,0,(size_t)_Size);
        }
LAB_004c35a7:
        if (local_24 != (int *)0x0) {
          ExceptionList = local_14;
          return local_24;
        }
      }
      else {
        if ((DAT_004ed3c4 != 2) || (DAT_004e3154 < puVar3)) goto LAB_004c35a7;
        FUN_004bf7a0(9);
        local_8 = 1;
        local_24 = FUN_004bf3a2((uint)puVar3 >> 4);
        local_8 = 0xffffffff;
        FUN_004c35e1();
        if (local_24 != (int *)0x0) {
          _Size = puVar3;
          goto LAB_004c359b;
        }
      }
LAB_004c35ac:
      local_24 = HeapAlloc(DAT_004ed3c0,8,(SIZE_T)puVar3);
    }
    if ((local_24 != (int *)0x0) || (DAT_004ecd58 == 0)) {
      ExceptionList = local_14;
      return local_24;
    }
    iVar1 = FUN_004bbc46(puVar3);
    if (iVar1 == 0) {
      ExceptionList = local_14;
      return (int *)0x0;
    }
  } while( true );
}


/* 004c3558 size=9 */

void FUN_004c3558(void)

{
  FUN_004bf801(9);
  return;
}


/* 004c35e1 size=9 */

void FUN_004c35e1(void)

{
  FUN_004bf801(9);
  return;
}


/* 004c35fc size=318 */

LONG __cdecl FUN_004c35fc(int param_1,_EXCEPTION_POINTERS *param_2)

{
  code *pcVar1;
  DWORD DVar2;
  DWORD DVar3;
  DWORD *pDVar4;
  int *piVar5;
  LONG LVar6;
  int iVar7;
  int iVar8;
  
  pDVar4 = FUN_004c04e2();
  piVar5 = FUN_004c373a(param_1,(int *)pDVar4[0x14]);
  if ((piVar5 == (int *)0x0) || (pcVar1 = (code *)piVar5[2], pcVar1 == (code *)0x0)) {
    LVar6 = UnhandledExceptionFilter(param_2);
  }
  else if (pcVar1 == (code *)0x5) {
    piVar5[2] = 0;
    LVar6 = 1;
  }
  else {
    if (pcVar1 != (code *)0x1) {
      DVar2 = pDVar4[0x15];
      pDVar4[0x15] = (DWORD)param_2;
      if (piVar5[1] == 8) {
        if (DAT_004e38b8 < DAT_004e38bc + DAT_004e38b8) {
          iVar7 = DAT_004e38b8 * 0xc;
          iVar8 = DAT_004e38b8;
          do {
            *(undefined4 *)(iVar7 + 8 + pDVar4[0x14]) = 0;
            iVar8 = iVar8 + 1;
            iVar7 = iVar7 + 0xc;
          } while (iVar8 < DAT_004e38bc + DAT_004e38b8);
        }
        iVar7 = *piVar5;
        DVar3 = pDVar4[0x16];
        if (iVar7 == -0x3fffff72) {
          pDVar4[0x16] = 0x83;
        }
        else if (iVar7 == -0x3fffff70) {
          pDVar4[0x16] = 0x81;
        }
        else if (iVar7 == -0x3fffff6f) {
          pDVar4[0x16] = 0x84;
        }
        else if (iVar7 == -0x3fffff6d) {
          pDVar4[0x16] = 0x85;
        }
        else if (iVar7 == -0x3fffff73) {
          pDVar4[0x16] = 0x82;
        }
        else if (iVar7 == -0x3fffff71) {
          pDVar4[0x16] = 0x86;
        }
        else if (iVar7 == -0x3fffff6e) {
          pDVar4[0x16] = 0x8a;
        }
        (*pcVar1)(8,pDVar4[0x16]);
        pDVar4[0x16] = DVar3;
      }
      else {
        piVar5[2] = 0;
        (*pcVar1)(piVar5[1]);
      }
      pDVar4[0x15] = DVar2;
    }
    LVar6 = -1;
  }
  return LVar6;
}


/* 004c373a size=58 */

int * __cdecl FUN_004c373a(int param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = param_2;
  if (*param_2 != param_1) {
    do {
      piVar1 = piVar1 + 3;
      if (param_2 + DAT_004e38c4 * 3 <= piVar1) break;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + DAT_004e38c4 * 3 <= piVar1) || (*piVar1 != param_1)) {
    piVar1 = (int *)0x0;
  }
  return piVar1;
}


/* 004c3843 size=7 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004c3843(void)

{
  char cVar1;
  ushort uVar2;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  *(byte *)(unaff_EBP + -0x2c8) = *(byte *)(unaff_EBP + -0x2c8) & 0xfe;
  if (DAT_004ecc7c != 0) {
    return;
  }
  *(double *)(unaff_EBP + -0x2d0) = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if ((cVar1 != -1) && (cVar1 != -2)) {
      if (cVar1 == '\0') {
        return;
      }
      *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
      goto LAB_004c3919;
    }
    uVar2 = *(ushort *)(unaff_EBP + -0x2ca) & 0x7ff0;
    if (uVar2 == 0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 4;
      in_ST0 = (float10)fscale(in_ST0,(float10)_DAT_004cf3f8);
      if (ABS(in_ST0) < (float10)_DAT_004cf3e8) {
        in_ST0 = in_ST0 * (float10)_DAT_004cf408;
      }
      goto LAB_004c3919;
    }
    if (uVar2 == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)_DAT_004cf3f0);
      if ((float10)_DAT_004cf3e0 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)_DAT_004cf400;
      }
      goto LAB_004c3919;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_004c3919:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if ((*(byte *)(unaff_EBP + -0x2c8) & 1) == 0) {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_004c6da2((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),(int *)(unaff_EBP + -0x8e),
               (ushort *)(unaff_EBP + -0xa4));
  return;
}


/* 004c384a size=305 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004c384a(void)

{
  char cVar1;
  ushort uVar2;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  if (DAT_004ecc7c != 0) {
    return;
  }
  *(double *)(unaff_EBP + -0x2d0) = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if ((cVar1 != -1) && (cVar1 != -2)) {
      if (cVar1 == '\0') {
        return;
      }
      *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
      goto LAB_004c3919;
    }
    uVar2 = *(ushort *)(unaff_EBP + -0x2ca) & 0x7ff0;
    if (uVar2 == 0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 4;
      in_ST0 = (float10)fscale(in_ST0,(float10)_DAT_004cf3f8);
      if (ABS(in_ST0) < (float10)_DAT_004cf3e8) {
        in_ST0 = in_ST0 * (float10)_DAT_004cf408;
      }
      goto LAB_004c3919;
    }
    if (uVar2 == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)_DAT_004cf3f0);
      if ((float10)_DAT_004cf3e0 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)_DAT_004cf400;
      }
      goto LAB_004c3919;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_004c3919:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if ((*(byte *)(unaff_EBP + -0x2c8) & 1) == 0) {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_004c6da2((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),(int *)(unaff_EBP + -0x8e),
               (ushort *)(unaff_EBP + -0xa4));
  return;
}


