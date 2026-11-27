/* lithtech.exe decompilation - unnamed_004c4000 */
#include "ghidra_types.h"

/* 004c41f6 size=518 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004c41f6: lifted from original x86 -> lt_lifted.c */


/* 004c43fc size=178 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004c43fc: lifted from original x86 -> lt_lifted.c */


/* 004c477b size=429 */

undefined4 __cdecl FUN_004c477b(int param_1)

{
  BYTE *pBVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  UINT CodePage;
  UINT *pUVar5;
  BOOL BVar6;
  uint uVar7;
  uint uVar8;
  BYTE *pBVar9;
  int iVar10;
  byte *pbVar11;
  int iVar12;
  byte *pbVar13;
  undefined4 uVar14;
  undefined4 *puVar15;
  _cpinfo local_1c;
  uint local_8;
  
  FUN_004bf7a0(0x19);
  CodePage = FUN_004c4928(param_1);
  if (CodePage != DAT_004ed058) {
    if (CodePage != 0) {
      iVar12 = 0;
      pUVar5 = &DAT_004e3a38;
LAB_004c47b8:
      if (*pUVar5 != CodePage) goto code_r0x004c47bc;
      local_8 = 0;
      puVar15 = &DAT_004ed180;
      for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar12 = iVar12 * 0x30;
      *(undefined1 *)puVar15 = 0;
      pbVar13 = (byte *)(iVar12 + 0x4e3a48);
      do {
        bVar3 = *pbVar13;
        pbVar11 = pbVar13;
        while ((bVar3 != 0 && (bVar3 = pbVar11[1], bVar3 != 0))) {
          uVar8 = (uint)*pbVar11;
          if (uVar8 <= bVar3) {
            bVar4 = (&DAT_004e3a30)[local_8];
            do {
              pbVar2 = (byte *)((int)&DAT_004ed180 + uVar8 + 1);
              *pbVar2 = *pbVar2 | bVar4;
              uVar8 = uVar8 + 1;
            } while (uVar8 <= bVar3);
          }
          pbVar11 = pbVar11 + 2;
          bVar3 = *pbVar11;
        }
        local_8 = local_8 + 1;
        pbVar13 = pbVar13 + 8;
      } while (local_8 < 4);
      DAT_004ed06c = 1;
      DAT_004ed058 = CodePage;
      DAT_004ed284 = FUN_004c4972(CodePage);
      DAT_004ed060 = *(undefined4 *)(iVar12 + 0x4e3a3c);
      DAT_004ed064 = *(undefined4 *)(iVar12 + 0x4e3a40);
      DAT_004ed068 = *(undefined4 *)(iVar12 + 0x4e3a44);
      goto LAB_004c490c;
    }
    goto LAB_004c4907;
  }
  goto LAB_004c47a2;
code_r0x004c47bc:
  pUVar5 = pUVar5 + 0xc;
  iVar12 = iVar12 + 1;
  if (0x4e3b27 < (int)pUVar5) goto code_r0x004c47c7;
  goto LAB_004c47b8;
code_r0x004c47c7:
  BVar6 = GetCPInfo(CodePage,&local_1c);
  uVar8 = 1;
  if (BVar6 == 1) {
    DAT_004ed284 = 0;
    puVar15 = &DAT_004ed180;
    for (iVar12 = 0x40; iVar12 != 0; iVar12 = iVar12 + -1) {
      *puVar15 = 0;
      puVar15 = puVar15 + 1;
    }
    *(undefined1 *)puVar15 = 0;
    if (local_1c.MaxCharSize < 2) {
      DAT_004ed06c = 0;
      DAT_004ed058 = CodePage;
    }
    else {
      DAT_004ed058 = CodePage;
      if (local_1c.LeadByte[0] != '\0') {
        pBVar9 = local_1c.LeadByte + 1;
        do {
          bVar3 = *pBVar9;
          if (bVar3 == 0) break;
          for (uVar7 = (uint)pBVar9[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
            pbVar13 = (byte *)((int)&DAT_004ed180 + uVar7 + 1);
            *pbVar13 = *pbVar13 | 4;
          }
          pBVar1 = pBVar9 + 1;
          pBVar9 = pBVar9 + 2;
        } while (*pBVar1 != 0);
      }
      do {
        pbVar13 = (byte *)((int)&DAT_004ed180 + uVar8 + 1);
        *pbVar13 = *pbVar13 | 8;
        uVar8 = uVar8 + 1;
      } while (uVar8 < 0xff);
      DAT_004ed284 = FUN_004c4972(CodePage);
      DAT_004ed06c = 1;
    }
    DAT_004ed060 = 0;
    DAT_004ed064 = 0;
    DAT_004ed068 = 0;
  }
  else {
    if (DAT_004ecd94 == 0) {
      uVar14 = 0xffffffff;
      goto LAB_004c4919;
    }
LAB_004c4907:
    FUN_004c49a5();
  }
LAB_004c490c:
  FUN_004c49ce();
LAB_004c47a2:
  uVar14 = 0;
LAB_004c4919:
  FUN_004bf801(0x19);
  return uVar14;
}


/* 004c4928 size=74 */

int __cdecl FUN_004c4928(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_004ecd94 = 1;
                    /* WARNING: Could not recover jumptable at 0x004c4942. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_004ecd94 = 1;
                    /* WARNING: Could not recover jumptable at 0x004c4957. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_004ecd88;
  }
  DAT_004ecd94 = (uint)bVar2;
  return param_1;
}


/* 004c4972 size=51 */

undefined4 __cdecl FUN_004c4972(int param_1)

{
  if (param_1 == 0x3a4) {
    return 0x411;
  }
  if (param_1 == 0x3a8) {
    return 0x804;
  }
  if (param_1 == 0x3b5) {
    return 0x412;
  }
  if (param_1 == 0x3b6) {
    return 0x404;
  }
  return 0;
}


/* 004c49a5 size=41 */

void FUN_004c49a5(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_004ed180;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_004ed058 = 0;
  DAT_004ed06c = 0;
  DAT_004ed284 = 0;
  DAT_004ed060 = 0;
  DAT_004ed064 = 0;
  DAT_004ed068 = 0;
  return;
}


/* 004c49ce size=389 */

void FUN_004c49ce(void)

{
  byte *pbVar1;
  BOOL BVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  undefined1 uVar8;
  BYTE *pBVar9;
  CHAR *pCVar10;
  WORD local_518 [256];
  WCHAR local_318 [128];
  WCHAR local_218 [128];
  CHAR local_118 [256];
  _cpinfo local_18;
  
  BVar2 = GetCPInfo(DAT_004ed058,&local_18);
  if (BVar2 == 1) {
    uVar3 = 0;
    do {
      local_118[uVar3] = (CHAR)uVar3;
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
    local_118[0] = ' ';
    if (local_18.LeadByte[0] != 0) {
      pBVar9 = local_18.LeadByte + 1;
      do {
        uVar3 = (uint)local_18.LeadByte[0];
        if (uVar3 <= *pBVar9) {
          uVar5 = (*pBVar9 - uVar3) + 1;
          uVar6 = uVar5 >> 2;
          pCVar10 = local_118 + uVar3;
          while (uVar6 != 0) {
            uVar6 = uVar6 - 1;
            builtin_memcpy(pCVar10,"    ",4);
            pCVar10 = pCVar10 + 4;
          }
          for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *pCVar10 = ' ';
            pCVar10 = pCVar10 + 1;
          }
        }
        local_18.LeadByte[0] = pBVar9[1];
        pBVar9 = pBVar9 + 2;
      } while (local_18.LeadByte[0] != 0);
    }
    FUN_004c6c59(1,local_118,0x100,local_518,DAT_004ed058,DAT_004ed284,0);
    FUN_004c3208(DAT_004ed284,0x100,local_118,0x100,local_218,0x100,DAT_004ed058,0);
    FUN_004c3208(DAT_004ed284,0x200,local_118,0x100,local_318,0x100,DAT_004ed058,0);
    uVar3 = 0;
    puVar7 = local_518;
    do {
      if ((*puVar7 & 1) == 0) {
        if ((*puVar7 & 2) != 0) {
          pbVar1 = (byte *)((int)&DAT_004ed180 + uVar3 + 1);
          *pbVar1 = *pbVar1 | 0x20;
          uVar8 = *(undefined1 *)((int)local_318 + uVar3);
          goto LAB_004c4ada;
        }
        (&DAT_004ed080)[uVar3] = 0;
      }
      else {
        pbVar1 = (byte *)((int)&DAT_004ed180 + uVar3 + 1);
        *pbVar1 = *pbVar1 | 0x10;
        uVar8 = *(undefined1 *)((int)local_218 + uVar3);
LAB_004c4ada:
        (&DAT_004ed080)[uVar3] = uVar8;
      }
      uVar3 = uVar3 + 1;
      puVar7 = puVar7 + 1;
    } while (uVar3 < 0x100);
  }
  else {
    uVar3 = 0;
    do {
      if ((uVar3 < 0x41) || (0x5a < uVar3)) {
        if ((0x60 < uVar3) && (uVar3 < 0x7b)) {
          pbVar1 = (byte *)((int)&DAT_004ed180 + uVar3 + 1);
          *pbVar1 = *pbVar1 | 0x20;
          cVar4 = (char)uVar3 + -0x20;
          goto LAB_004c4b24;
        }
        (&DAT_004ed080)[uVar3] = 0;
      }
      else {
        pbVar1 = (byte *)((int)&DAT_004ed180 + uVar3 + 1);
        *pbVar1 = *pbVar1 | 0x10;
        cVar4 = (char)uVar3 + ' ';
LAB_004c4b24:
        (&DAT_004ed080)[uVar3] = cVar4;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
  }
  return;
}


/* 004c4b53 size=28 */

void FUN_004c4b53(void)

{
  if (DAT_004ee3ec == 0) {
    FUN_004c477b(-3);
    DAT_004ee3ec = 1;
  }
  return;
}


/* 004c4c00 size=208 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_004c4c00: lifted from original x86 -> lt_lifted.c */


/* 004c4cd0 size=88 */

byte * FUN_004c4cd0(void)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  if (DAT_004ee3ec == 0) {
    FUN_004c4b53();
  }
  bVar1 = *DAT_004ee3e4;
  pbVar4 = DAT_004ee3e4;
  if (bVar1 == 0x22) {
    while( true ) {
      pbVar3 = pbVar4;
      bVar1 = pbVar3[1];
      pbVar4 = pbVar3 + 1;
      if ((bVar1 == 0x22) || (bVar1 == 0)) break;
      iVar2 = FUN_004c76da(bVar1);
      if (iVar2 != 0) {
        pbVar4 = pbVar3 + 2;
      }
    }
    if (*pbVar4 == 0x22) goto LAB_004c4d0d;
  }
  else {
    while (0x20 < bVar1) {
      bVar1 = pbVar4[1];
      pbVar4 = pbVar4 + 1;
    }
  }
  for (; (*pbVar4 != 0 && (*pbVar4 < 0x21)); pbVar4 = pbVar4 + 1) {
LAB_004c4d0d:
  }
  return pbVar4;
}


/* 004c4d28 size=185 */

void FUN_004c4d28(void)

{
  char cVar1;
  size_t sVar2;
  undefined4 *puVar3;
  void *pvVar4;
  int iVar5;
  uint *puVar6;
  
  if (DAT_004ee3ec == 0) {
    FUN_004c4b53();
  }
  iVar5 = 0;
  for (puVar6 = DAT_004ecccc; (char)*puVar6 != '\0'; puVar6 = (uint *)((int)puVar6 + sVar2 + 1)) {
    if ((char)*puVar6 != '=') {
      iVar5 = iVar5 + 1;
    }
    sVar2 = _strlen((char *)puVar6);
  }
  puVar3 = _malloc(iVar5 * 4 + 4);
  DAT_004ecca4 = puVar3;
  if (puVar3 == (undefined4 *)0x0) {
    __amsg_exit(9);
  }
  cVar1 = (char)*DAT_004ecccc;
  puVar6 = DAT_004ecccc;
  while (cVar1 != '\0') {
    sVar2 = _strlen((char *)puVar6);
    if ((char)*puVar6 != '=') {
      pvVar4 = _malloc(sVar2 + 1);
      *puVar3 = pvVar4;
      if (pvVar4 == (void *)0x0) {
        __amsg_exit(9);
      }
      FUN_004c17f0((uint *)*puVar3,puVar6);
      puVar3 = puVar3 + 1;
    }
    puVar6 = (uint *)((int)puVar6 + sVar2 + 1);
    cVar1 = (char)*puVar6;
  }
  FUN_004b9d3f((undefined *)DAT_004ecccc);
  DAT_004ecccc = (uint *)0x0;
  *puVar3 = 0;
  DAT_004ee3e8 = 1;
  return;
}


/* 004c4de1 size=153 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004c4de1(void)

{
  undefined4 *puVar1;
  byte *pbVar2;
  int local_c;
  int local_8;
  
  if (DAT_004ee3ec == 0) {
    FUN_004c4b53();
  }
  GetModuleFileNameA((HMODULE)0x0,&DAT_004ecd98,0x104);
  _DAT_004eccb4 = &DAT_004ecd98;
  pbVar2 = &DAT_004ecd98;
  if (*DAT_004ee3e4 != 0) {
    pbVar2 = DAT_004ee3e4;
  }
  FUN_004c4e7a(pbVar2,(undefined4 *)0x0,(byte *)0x0,&local_8,&local_c);
  puVar1 = _malloc(local_c + local_8 * 4);
  if (puVar1 == (undefined4 *)0x0) {
    __amsg_exit(8);
  }
  FUN_004c4e7a(pbVar2,puVar1,(byte *)(puVar1 + local_8),&local_8,&local_c);
  DAT_004ecc9c = puVar1;
  DAT_004ecc98 = local_8 + -1;
  return;
}


/* 004c4e7a size=436 */

void __cdecl FUN_004c4e7a(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  byte *pbVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  *param_5 = 0;
  *param_4 = 1;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  if (*param_1 == 0x22) {
    while( true ) {
      bVar1 = param_1[1];
      pbVar4 = param_1 + 1;
      if ((bVar1 == 0x22) || (bVar1 == 0)) break;
      if (((*(byte *)((int)&DAT_004ed180 + bVar1 + 1) & 4) != 0) &&
         (*param_5 = *param_5 + 1, param_3 != (byte *)0x0)) {
        *param_3 = *pbVar4;
        param_3 = param_3 + 1;
        pbVar4 = param_1 + 2;
      }
      *param_5 = *param_5 + 1;
      param_1 = pbVar4;
      if (param_3 != (byte *)0x0) {
        *param_3 = *pbVar4;
        param_3 = param_3 + 1;
      }
    }
    *param_5 = *param_5 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    if (*pbVar4 == 0x22) {
      pbVar4 = param_1 + 2;
    }
  }
  else {
    do {
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *param_1;
        param_3 = param_3 + 1;
      }
      bVar1 = *param_1;
      pbVar4 = param_1 + 1;
      if ((*(byte *)((int)&DAT_004ed180 + bVar1 + 1) & 4) != 0) {
        *param_5 = *param_5 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = *pbVar4;
          param_3 = param_3 + 1;
        }
        pbVar4 = param_1 + 2;
      }
      if (bVar1 == 0x20) break;
      if (bVar1 == 0) goto LAB_004c4f25;
      param_1 = pbVar4;
    } while (bVar1 != 9);
    if (bVar1 == 0) {
LAB_004c4f25:
      pbVar4 = pbVar4 + -1;
    }
    else if (param_3 != (byte *)0x0) {
      param_3[-1] = 0;
    }
  }
  bVar2 = false;
  puVar6 = param_2;
  while (*pbVar4 != 0) {
    for (; (*pbVar4 == 0x20 || (*pbVar4 == 9)); pbVar4 = pbVar4 + 1) {
    }
    if (*pbVar4 == 0) break;
    if (puVar6 != (undefined4 *)0x0) {
      *puVar6 = param_3;
      puVar6 = puVar6 + 1;
      param_2 = puVar6;
    }
    *param_4 = *param_4 + 1;
    while( true ) {
      bVar3 = true;
      uVar5 = 0;
      for (; *pbVar4 == 0x5c; pbVar4 = pbVar4 + 1) {
        uVar5 = uVar5 + 1;
      }
      if (*pbVar4 == 0x22) {
        if ((uVar5 & 1) == 0) {
          if ((!bVar2) || (pbVar4[1] != 0x22)) {
            bVar3 = false;
          }
          else {
            pbVar4 = pbVar4 + 1;
          }
          bVar2 = !bVar2;
          puVar6 = param_2;
        }
        uVar5 = uVar5 >> 1;
      }
      if (uVar5 != 0) {
        do {
          if (param_3 != (byte *)0x0) {
            *param_3 = 0x5c;
            param_3 = param_3 + 1;
          }
          *param_5 = *param_5 + 1;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
      bVar1 = *pbVar4;
      if ((bVar1 == 0) || ((!bVar2 && ((bVar1 == 0x20 || (bVar1 == 9)))))) break;
      if (bVar3) {
        if (param_3 == (byte *)0x0) {
          if ((*(byte *)((int)&DAT_004ed180 + bVar1 + 1) & 4) != 0) {
            pbVar4 = pbVar4 + 1;
            *param_5 = *param_5 + 1;
          }
        }
        else {
          if ((*(byte *)((int)&DAT_004ed180 + bVar1 + 1) & 4) != 0) {
            *param_3 = bVar1;
            param_3 = param_3 + 1;
            pbVar4 = pbVar4 + 1;
            *param_5 = *param_5 + 1;
          }
          *param_3 = *pbVar4;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      pbVar4 = pbVar4 + 1;
    }
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    *param_5 = *param_5 + 1;
  }
  if (puVar6 != (undefined4 *)0x0) {
    *puVar6 = 0;
  }
  *param_4 = *param_4 + 1;
  return;
}


/* 004c502e size=306 */

LPSTR FUN_004c502e(void)

{
  char cVar1;
  WCHAR WVar2;
  WCHAR *pWVar3;
  WCHAR *pWVar4;
  int iVar5;
  size_t _Size;
  LPSTR pCVar6;
  char *pcVar8;
  char *pcVar7;
  LPWCH lpWideCharStr;
  LPCH pCVar9;
  LPSTR local_8;
  
  local_8 = (LPSTR)0x0;
  lpWideCharStr = (LPWCH)0x0;
  pCVar9 = (LPCH)0x0;
  if (DAT_004ece9c == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr != (LPWCH)0x0) {
      DAT_004ece9c = 1;
      goto LAB_004c5085;
    }
    pCVar9 = GetEnvironmentStrings();
    if (pCVar9 == (LPCH)0x0) {
      return (LPSTR)0x0;
    }
    DAT_004ece9c = 2;
  }
  else {
    if (DAT_004ece9c == 1) {
LAB_004c5085:
      if ((lpWideCharStr == (LPWCH)0x0) &&
         (lpWideCharStr = GetEnvironmentStringsW(), lpWideCharStr == (LPWCH)0x0)) {
        return (LPSTR)0x0;
      }
      WVar2 = *lpWideCharStr;
      pWVar4 = lpWideCharStr;
      while (WVar2 != L'\0') {
        do {
          pWVar3 = pWVar4;
          pWVar4 = pWVar3 + 1;
        } while (*pWVar4 != L'\0');
        pWVar4 = pWVar3 + 2;
        WVar2 = *pWVar4;
      }
      iVar5 = ((int)pWVar4 - (int)lpWideCharStr >> 1) + 1;
      _Size = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
      if ((_Size != 0) && (pCVar6 = _malloc(_Size), pCVar6 != (LPSTR)0x0)) {
        iVar5 = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,pCVar6,_Size,(LPCSTR)0x0,(LPBOOL)0x0);
        local_8 = pCVar6;
        if (iVar5 == 0) {
          FUN_004b9d3f(pCVar6);
          local_8 = (LPSTR)0x0;
        }
      }
      FreeEnvironmentStringsW(lpWideCharStr);
      return local_8;
    }
    if (DAT_004ece9c != 2) {
      return (LPSTR)0x0;
    }
  }
  if ((pCVar9 == (LPCH)0x0) && (pCVar9 = GetEnvironmentStrings(), pCVar9 == (LPCH)0x0)) {
    return (LPSTR)0x0;
  }
  cVar1 = *pCVar9;
  pcVar7 = pCVar9;
  while (cVar1 != '\0') {
    do {
      pcVar8 = pcVar7;
      pcVar7 = pcVar8 + 1;
    } while (*pcVar7 != '\0');
    pcVar7 = pcVar8 + 2;
    cVar1 = *pcVar7;
  }
  pCVar6 = _malloc((size_t)(pcVar7 + (1 - (int)pCVar9)));
  if (pCVar6 == (LPSTR)0x0) {
    pCVar6 = (LPSTR)0x0;
  }
  else {
    FUN_004bd7a0((undefined4 *)pCVar6,(undefined4 *)pCVar9,(uint)(pcVar7 + (1 - (int)pCVar9)));
  }
  FreeEnvironmentStringsA(pCVar9);
  return pCVar6;
}


/* 004c5160 size=57 */

/* FUN_004c5160: lifted from original x86 -> lt_lifted.c */


/* 004c5199 size=339 */

void __cdecl FUN_004c5199(DWORD param_1)

{
  undefined4 *puVar1;
  DWORD *pDVar2;
  DWORD DVar3;
  size_t sVar4;
  HANDLE hFile;
  int iVar5;
  uint *_Dest;
  undefined1 auStackY_1e3 [7];
  LPCVOID lpBuffer;
  LPOVERLAPPED lpOverlapped;
  uint local_1a8 [65];
  uint local_a4 [40];
  
  iVar5 = 0;
  pDVar2 = &DAT_004e3b30;
  do {
    if (param_1 == *pDVar2) break;
    pDVar2 = pDVar2 + 2;
    iVar5 = iVar5 + 1;
  } while ((int)pDVar2 < 0x4e3bc0);
  if (param_1 == (&DAT_004e3b30)[iVar5 * 2]) {
    if ((DAT_004eccd4 == 1) || ((DAT_004eccd4 == 0 && (DAT_004e0e64 == 1)))) {
      pDVar2 = &param_1;
      puVar1 = (undefined4 *)(iVar5 * 8 + 0x4e3b34);
      lpOverlapped = (LPOVERLAPPED)0x0;
      sVar4 = _strlen((char *)*puVar1);
      lpBuffer = (LPCVOID)*puVar1;
      hFile = GetStdHandle(0xfffffff4);
      WriteFile(hFile,lpBuffer,sVar4,pDVar2,lpOverlapped);
    }
    else if (param_1 != 0xfc) {
      DVar3 = GetModuleFileNameA((HMODULE)0x0,(LPSTR)local_1a8,0x104);
      if (DVar3 == 0) {
        FUN_004c17f0(local_1a8,(uint *)"<program name unknown>");
      }
      _Dest = local_1a8;
      sVar4 = _strlen((char *)local_1a8);
      if (0x3c < sVar4 + 1) {
        sVar4 = _strlen((char *)local_1a8);
        _Dest = (uint *)(auStackY_1e3 + sVar4);
        _strncpy((char *)_Dest,"...",3);
      }
      FUN_004c17f0(local_a4,(uint *)"Runtime Error!\n\nProgram: ");
      FUN_004c1800(local_a4,_Dest);
      FUN_004c1800(local_a4,(uint *)&DAT_004cf6c0);
      FUN_004c1800(local_a4,*(uint **)(iVar5 * 8 + 0x4e3b34));
      (*(uint32_t*)((char*)&auStackY_1e3+3)) = 0x4c52bd;
      FUN_004c771c(local_a4,"Microsoft Visual C++ Runtime Library",0x12010);
    }
  }
  return;
}


/* 004c52ec size=70 */

/* FUN_004c52ec: lifted from original x86 -> lt_lifted.c */


/* 004c53d1 size=154 */

byte * __cdecl FUN_004c53d1(byte *param_1,byte *param_2,size_t param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  if (DAT_004ed06c == 0) {
    param_1 = (byte *)_strncpy((char *)param_1,(char *)param_2,param_3);
  }
  else {
    FUN_004bf7a0(0x19);
    uVar4 = 0;
    pbVar6 = param_1;
    if (param_3 != 0) {
      pbVar5 = param_1;
      do {
        bVar1 = *param_2;
        uVar4 = param_3 - 1;
        bVar2 = *(byte *)((int)&DAT_004ed180 + bVar1 + 1);
        *pbVar5 = bVar1;
        if ((bVar2 & 4) == 0) {
          pbVar6 = pbVar5 + 1;
          param_2 = param_2 + 1;
          if (bVar1 == 0) goto LAB_004c5442;
        }
        else {
          pbVar6 = pbVar5 + 1;
          if (uVar4 == 0) {
            *pbVar5 = 0;
            goto LAB_004c5442;
          }
          bVar1 = param_2[1];
          uVar4 = param_3 - 2;
          *pbVar6 = bVar1;
          pbVar6 = pbVar5 + 2;
          param_2 = param_2 + 2;
          if (bVar1 == 0) {
            *pbVar5 = 0;
            goto LAB_004c5442;
          }
        }
        param_3 = uVar4;
        pbVar5 = pbVar6;
      } while (uVar4 != 0);
      uVar4 = 0;
    }
LAB_004c5442:
    if (uVar4 != 0) {
      for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        pbVar6[0] = 0;
        pbVar6[1] = 0;
        pbVar6[2] = 0;
        pbVar6[3] = 0;
        pbVar6 = pbVar6 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pbVar6 = 0;
        pbVar6 = pbVar6 + 1;
      }
    }
    FUN_004bf801(0x19);
  }
  return param_1;
}


/* 004c546b size=114 */

byte * __cdecl FUN_004c546b(byte *param_1,uint param_2)

{
  byte bVar1;
  ushort uVar2;
  byte *pbVar3;
  byte bVar4;
  byte *pbVar5;
  bool bVar6;
  
  pbVar5 = (byte *)0x0;
  if (DAT_004ed06c == 0) {
    pbVar5 = (byte *)_strrchr((char *)param_1,param_2);
  }
  else {
    FUN_004bf7a0(0x19);
    do {
      bVar4 = *param_1;
      if ((*(byte *)((int)&DAT_004ed180 + bVar4 + 1) & 4) == 0) {
        bVar6 = param_2 == bVar4;
LAB_004c54c6:
        pbVar3 = param_1;
        if (bVar6) {
          pbVar5 = param_1;
        }
      }
      else {
        bVar1 = param_1[1];
        pbVar3 = param_1 + 1;
        if (bVar1 == 0) {
          bVar6 = pbVar5 == (byte *)0x0;
          param_1 = pbVar3;
          bVar4 = bVar1;
          goto LAB_004c54c6;
        }
        uVar2 = CONCAT11(bVar4,bVar1);
        bVar4 = bVar1;
        if (param_2 == uVar2) {
          pbVar5 = param_1;
        }
      }
      param_1 = pbVar3 + 1;
    } while (bVar4 != 0);
    FUN_004bf801(0x19);
  }
  return pbVar5;
}


/* 004c54dd size=165 */

uint * __cdecl FUN_004c54dd(uint *param_1,LPCSTR param_2,size_t param_3)

{
  LPCSTR lpFileName;
  uint *puVar1;
  DWORD *pDVar2;
  DWORD DVar3;
  
  lpFileName = param_2;
  if ((param_2 == (LPCSTR)0x0) || (*param_2 == '\0')) {
    puVar1 = FUN_004c77a5(param_1,param_3);
    return puVar1;
  }
  puVar1 = param_1;
  if (param_1 == (uint *)0x0) {
    puVar1 = _malloc(0x104);
    if (puVar1 == (uint *)0x0) {
      pDVar2 = FUN_004c09cc();
      *pDVar2 = 0xc;
      return (uint *)0x0;
    }
    param_3 = 0x104;
  }
  DVar3 = GetFullPathNameA(lpFileName,param_3,(LPSTR)puVar1,&param_2);
  if (DVar3 < param_3) {
    if (DVar3 != 0) {
      return puVar1;
    }
    if (param_1 == (uint *)0x0) {
      FUN_004b9d3f((undefined *)puVar1);
    }
    DVar3 = GetLastError();
    FUN_004c0959(DVar3);
  }
  else {
    if (param_1 == (uint *)0x0) {
      FUN_004b9d3f((undefined *)puVar1);
    }
    pDVar2 = FUN_004c09cc();
    *pDVar2 = 0x22;
  }
  return (uint *)0x0;
}


/* 004c5582 size=67 */

int FUN_004c5582(void)

{
  DWORD DVar1;
  uint uVar2;
  int iVar3;
  byte local_108;
  char local_107;
  
  iVar3 = 0;
  DVar1 = GetCurrentDirectoryA(0x104,(LPSTR)&local_108);
  if ((DVar1 != 0) && (local_107 == ':')) {
    uVar2 = FUN_004bbd5a((uint)local_108);
    iVar3 = uVar2 - 0x40;
  }
  return iVar3;
}


/* 004c55c5 size=123 */

uint __cdecl FUN_004c55c5(uint param_1)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  undefined1 uVar4;
  undefined2 local_8;
  
  uVar1 = param_1;
  if (param_1 < 0x100) {
    if ((*(byte *)((int)&DAT_004ed180 + param_1 + 1) & 0x10) == 0x10) {
      return (uint)(byte)(&DAT_004ed080)[param_1];
    }
  }
  else {
    uVar4 = (undefined1)param_1;
    bVar2 = (byte)(param_1 >> 8);
    param_1 = CONCAT13(uVar4,CONCAT12(bVar2,(undefined2)param_1));
    if (((*(byte *)((int)&DAT_004ed180 + bVar2 + 1) & 4) != 0) &&
       (iVar3 = FUN_004c3208(DAT_004ed284,0x100,(char *)((int)&param_1 + 2),2,&local_8,2,
                             DAT_004ed058,1), iVar3 != 0)) {
      return (uint)CONCAT11((undefined1)local_8,(*(uint8_t*)((char*)&local_8+1)));
    }
  }
  return uVar1;
}


/* 004c5640 size=149 */

byte * __cdecl FUN_004c5640(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  
  if (DAT_004ed06c == 0) {
    pbVar2 = FUN_004c76a0(param_1,param_2);
    return pbVar2;
  }
  FUN_004bf7a0(0x19);
  if (*param_1 != 0) {
    do {
      bVar1 = *param_2;
      pbVar2 = param_2;
      while (bVar1 != 0) {
        bVar1 = *pbVar2;
        if ((*(byte *)((int)&DAT_004ed180 + bVar1 + 1) & 4) == 0) {
          if (bVar1 == *param_1) break;
        }
        else {
          if (((bVar1 == *param_1) && (pbVar2[1] == param_1[1])) || (pbVar2[1] == 0)) break;
          pbVar2 = pbVar2 + 1;
        }
        pbVar2 = pbVar2 + 1;
        bVar1 = *pbVar2;
      }
    } while (((*pbVar2 == 0) &&
             (((*(byte *)((int)&DAT_004ed180 + *param_1 + 1) & 4) == 0 ||
              (param_1 = param_1 + 1, *param_1 != 0)))) && (param_1 = param_1 + 1, *param_1 != 0));
  }
  FUN_004bf801(0x19);
  return (byte *)(-(uint)(*param_1 != 0) & (uint)param_1);
}


/* 004c56d5 size=53 */

uint __thiscall FUN_004c56d5(void *this,uint param_1,uint param_2)

{
  uint uVar1;
  undefined2 in_FPUControlWord;
  undefined4 local_8;
  
  local_8 = CONCAT22((short)((uint)this >> 0x10),in_FPUControlWord);
  uVar1 = FUN_004c5720(local_8);
  uVar1 = uVar1 & ~param_2 | param_1 & param_2;
  FUN_004c57b2(uVar1);
  return uVar1;
}


/* 004c570a size=22 */

void __thiscall FUN_004c570a(void *this,uint param_1,uint param_2)

{
  FUN_004c56d5(this,param_1,param_2 & 0xfff7ffff);
  return;
}


/* 004c5720 size=146 */

uint __cdecl FUN_004c5720(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((param_1 & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  uVar2 = param_1 & 0xc00;
  if (uVar2 != 0) {
    if (uVar2 == 0x400) {
      uVar1 = uVar1 | 0x100;
    }
    else if (uVar2 == 0x800) {
      uVar1 = uVar1 | 0x200;
    }
    else if (uVar2 == 0xc00) {
      uVar1 = uVar1 | 0x300;
    }
  }
  if ((param_1 & 0x300) == 0) {
    uVar1 = uVar1 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    uVar1 = uVar1 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    uVar1 = uVar1 | 0x40000;
  }
  return uVar1;
}


/* 004c57b2 size=137 */

uint __cdecl FUN_004c57b2(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (uint)((param_1 & 0x10) != 0);
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x10;
  }
  if ((param_1 & 1) != 0) {
    uVar1 = uVar1 | 0x20;
  }
  if ((param_1 & 0x80000) != 0) {
    uVar1 = uVar1 | 2;
  }
  uVar2 = param_1 & 0x300;
  if (uVar2 != 0) {
    if (uVar2 == 0x100) {
      uVar1 = uVar1 | 0x400;
    }
    else if (uVar2 == 0x200) {
      uVar1 = uVar1 | 0x800;
    }
    else if (uVar2 == 0x300) {
      uVar1 = uVar1 | 0xc00;
    }
  }
  if ((param_1 & 0x30000) == 0) {
    uVar1 = uVar1 | 0x300;
  }
  else if ((param_1 & 0x30000) == 0x10000) {
    uVar1 = uVar1 | 0x200;
  }
  if ((param_1 & 0x40000) != 0) {
    uVar1 = uVar1 | 0x1000;
  }
  return uVar1;
}


/* 004c583b size=73 */

undefined4 __cdecl FUN_004c583b(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + (param_2 / 0x20) * 4) & ~(-1 << (0x1fU - (char)(param_2 % 0x20) & 0x1f)))
      != 0) {
    return 0;
  }
  iVar2 = param_2 / 0x20 + 1;
  if (iVar2 < 3) {
    piVar1 = (int *)(param_1 + iVar2 * 4);
    do {
      if (*piVar1 != 0) {
        return 0;
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < 3);
  }
  return 1;
}


/* 004c5884 size=86 */

int __cdecl FUN_004c5884(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  
  puVar3 = (uint *)(param_1 + (param_2 / 0x20) * 4);
  iVar1 = FUN_004c7a97(*puVar3,1 << (0x1fU - (char)(param_2 % 0x20) & 0x1f),puVar3);
  iVar2 = param_2 / 0x20 + -1;
  if (-1 < iVar2) {
    puVar3 = (uint *)(param_1 + iVar2 * 4);
    do {
      if (iVar1 == 0) {
        return;
      }
      iVar1 = FUN_004c7a97(*puVar3,1,puVar3);
      iVar2 = iVar2 + -1;
      puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
  }
  return;
}


/* 004c58da size=140 */

undefined4 __cdecl FUN_004c58da(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 local_8;
  
  local_8 = 0;
  puVar1 = (uint *)(param_1 + (param_2 / 0x20) * 4);
  bVar3 = 0x1f - (char)(param_2 % 0x20);
  if (((*puVar1 & 1 << (bVar3 & 0x1f)) != 0) &&
     (iVar2 = FUN_004c583b(param_1,param_2 + 1), iVar2 == 0)) {
    local_8 = FUN_004c5884(param_1,param_2 + -1);
  }
  *puVar1 = *puVar1 & -1 << (bVar3 & 0x1f);
  iVar2 = param_2 / 0x20 + 1;
  if (iVar2 < 3) {
    puVar5 = (undefined4 *)(param_1 + iVar2 * 4);
    for (iVar4 = 3 - iVar2; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  return local_8;
}


/* 004c5966 size=27 */

void __cdecl FUN_004c5966(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 - (int)param_2;
  iVar2 = 3;
  do {
    *(undefined4 *)(iVar1 + (int)param_2) = *param_2;
    param_2 = param_2 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


/* 004c5981 size=12 */

void __cdecl FUN_004c5981(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}


/* 004c598d size=27 */

undefined4 __cdecl FUN_004c598d(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*param_1 != 0) {
      return 0;
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 1;
  } while (iVar1 < 3);
  return 1;
}


/* 004c59a8 size=141 */

void __cdecl FUN_004c59a8(uint *param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  int local_8;
  
  local_8 = 3;
  iVar2 = (int)param_2 / 0x20;
  iVar5 = (int)param_2 % 0x20;
  param_2 = 0;
  bVar3 = (byte)iVar5;
  puVar6 = param_1;
  do {
    uVar1 = *puVar6;
    *puVar6 = uVar1 >> (bVar3 & 0x1f) | param_2;
    puVar6 = puVar6 + 1;
    param_2 = (uVar1 & ~(-1 << (bVar3 & 0x1f))) << (0x20 - bVar3 & 0x1f);
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  iVar5 = 2;
  iVar4 = 8;
  do {
    if (iVar5 < iVar2) {
      *(undefined4 *)(iVar4 + (int)param_1) = 0;
    }
    else {
      *(undefined4 *)(iVar4 + (int)param_1) = *(undefined4 *)(iVar4 + iVar2 * -4 + (int)param_1);
    }
    iVar5 = iVar5 + -1;
    iVar4 = iVar4 + -4;
  } while (-1 < iVar4);
  return;
}


/* 004c5a35 size=364 */

undefined4 __cdecl FUN_004c5a35(ushort *param_1,uint *param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 local_1c [3];
  uint local_10;
  uint local_c;
  int local_8;
  
  uVar1 = param_1[5];
  local_10 = *(uint *)(param_1 + 3);
  local_c = *(uint *)(param_1 + 1);
  uVar3 = uVar1 & 0x7fff;
  iVar4 = uVar3 - 0x3fff;
  local_8 = (uint)*param_1 << 0x10;
  if (iVar4 == -0x3fff) {
    iVar4 = 0;
    iVar2 = FUN_004c598d((int *)&local_10);
    if (iVar2 != 0) {
LAB_004c5b61:
      uVar5 = 0;
      goto LAB_004c5b63;
    }
    FUN_004c5981(&local_10);
  }
  else {
    FUN_004c5966((int)local_1c,&local_10);
    iVar2 = FUN_004c58da((int)&local_10,param_3[2]);
    if (iVar2 != 0) {
      iVar4 = uVar3 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar4 < iVar2 - param_3[2]) {
      FUN_004c5981(&local_10);
    }
    else {
      if (iVar2 < iVar4) {
        if (*param_3 <= iVar4) {
          FUN_004c5981(&local_10);
          local_10 = local_10 | 0x80000000;
          FUN_004c59a8(&local_10,param_3[3]);
          iVar4 = param_3[5] + *param_3;
          uVar5 = 1;
          goto LAB_004c5b63;
        }
        local_10 = local_10 & 0x7fffffff;
        iVar4 = param_3[5] + iVar4;
        FUN_004c59a8(&local_10,param_3[3]);
        goto LAB_004c5b61;
      }
      FUN_004c5966((int)&local_10,local_1c);
      FUN_004c59a8(&local_10,iVar2 - iVar4);
      FUN_004c58da((int)&local_10,param_3[2]);
      FUN_004c59a8(&local_10,param_3[3] + 1);
    }
  }
  iVar4 = 0;
  uVar5 = 2;
LAB_004c5b63:
  local_10 = iVar4 << (0x1fU - (char)param_3[3] & 0x1f) |
             -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 | local_10;
  if (param_3[4] == 0x40) {
    param_2[1] = local_10;
    *param_2 = local_c;
  }
  else if (param_3[4] == 0x20) {
    *param_2 = local_10;
  }
  return uVar5;
}


/* 004c5ba1 size=22 */

int __cdecl FUN_004c5ba1(ushort *param_1,uint *param_2)

{
  FUN_004c5a35(param_1,param_2,(int *)&DAT_004e3bc0);
  return;
}


/* 004c5bb7 size=22 */

void __cdecl FUN_004c5bb7(ushort *param_1,uint *param_2)

{
  FUN_004c5a35(param_1,param_2,(int *)&DAT_004e3bd8);
  return;
}


/* 004c5bcd size=45 */

void __thiscall FUN_004c5bcd(void *this,uint *param_1,byte *param_2)

{
  ushort local_10 [6];
  
  FUN_004c6788(this,local_10,(int *)&param_2,param_2,0,0,0,0);
  FUN_004c5ba1(local_10,param_1);
  return;
}


/* 004c5bfa size=45 */

void __thiscall FUN_004c5bfa(void *this,uint *param_1,byte *param_2)

{
  ushort local_10 [6];
  
  FUN_004c6788(this,local_10,(int *)&param_2,param_2,0,0,0,0);
  FUN_004c5bb7(local_10,param_1);
  return;
}


/* 004c5c27 size=119 */

void __cdecl FUN_004c5c27(char *param_1,int param_2,int param_3)

{
  char *_Str;
  char *pcVar1;
  char *pcVar2;
  size_t sVar3;
  char *pcVar4;
  char cVar5;
  
  pcVar1 = param_1;
  pcVar4 = *(char **)(param_3 + 0xc);
  _Str = param_1 + 1;
  *param_1 = '0';
  pcVar2 = _Str;
  if (0 < param_2) {
    param_1 = (char *)param_2;
    param_2 = 0;
    do {
      cVar5 = *pcVar4;
      if (cVar5 == '\0') {
        cVar5 = '0';
      }
      else {
        pcVar4 = pcVar4 + 1;
      }
      *pcVar2 = cVar5;
      pcVar2 = pcVar2 + 1;
      param_1 = param_1 + -1;
    } while (param_1 != (char *)0x0);
  }
  *pcVar2 = '\0';
  if ((-1 < param_2) && ('4' < *pcVar4)) {
    while (pcVar2 = pcVar2 + -1, *pcVar2 == '9') {
      *pcVar2 = '0';
    }
    *pcVar2 = *pcVar2 + '\x01';
  }
  if (*pcVar1 == '1') {
    *(int *)(param_3 + 4) = *(int *)(param_3 + 4) + 1;
  }
  else {
    sVar3 = _strlen(_Str);
    FUN_004bab10((undefined4 *)pcVar1,(undefined4 *)_Str,sVar3 + 1);
  }
  return;
}


/* 004c5c9e size=92 */

int * __cdecl FUN_004c5c9e(uint param_1,undefined4 param_2,int *param_3,uint *param_4)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  undefined4 in_stack_ffffffbc;
  undefined2 uVar4;
  short local_2c;
  char local_2a;
  uint local_28 [6];
  uint local_10;
  uint uStack_c;
  undefined2 uStack_8;
  
  uVar4 = (undefined2)((uint)in_stack_ffffffbc >> 0x10);
  FUN_004c5cfa(&local_10,&param_1);
  iVar3 = FUN_004c7c38(local_10,uStack_c,CONCAT22(uVar4,uStack_8),0x11,0,&local_2c);
  puVar2 = param_4;
  piVar1 = param_3;
  param_3[2] = iVar3;
  *param_3 = (int)local_2a;
  param_3[1] = (int)local_2c;
  FUN_004c17f0(param_4,local_28);
  piVar1[3] = (int)puVar2;
  return piVar1;
}


/* 004c5cfa size=182 */

void __cdecl FUN_004c5cfa(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint local_8;
  
  uVar1 = *(ushort *)((int)param_2 + 6);
  uVar3 = (uVar1 & 0x7ff0) >> 4;
  uVar2 = *param_2;
  local_8 = 0x80000000;
  if (uVar3 == 0) {
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    iVar4 = 0x3c01;
    local_8 = 0;
  }
  else if (uVar3 == 0x7ff) {
    iVar4 = 0x7fff;
  }
  else {
    iVar4 = uVar3 + 0x3c00;
  }
  local_8 = uVar2 >> 0x15 | (param_2[1] & 0xfffff) << 0xb | local_8;
  param_1[1] = local_8;
  *param_1 = uVar2 << 0xb;
  while ((local_8 & 0x80000000) == 0) {
    local_8 = *param_1 >> 0x1f | local_8 * 2;
    *param_1 = *param_1 * 2;
    param_1[1] = local_8;
    iVar4 = iVar4 + 0xffff;
  }
  *(ushort *)(param_1 + 2) = uVar1 & 0x8000 | (ushort)iVar4;
  return;
}


/* 004c5e08 size=9 */

void FUN_004c5e08(void)

{
  __amsg_exit(2);
  return;
}


/* 004c5e11 size=23 */

int __thiscall FUN_004c5e11(void *this,byte *param_1,int *param_2,void *param_3)

{
  FUN_004c5e28(this,param_1,param_2,param_3,0);
  return;
}


/* 004c5e28 size=517 */

/* FUN_004c5e28: lifted from original x86 -> lt_lifted.c */


/* 004c602d size=68 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_004c602d(undefined4 *param_1)

{
  void *pvVar1;
  
  _DAT_004eccf0 = _DAT_004eccf0 + 1;
  pvVar1 = _malloc(0x1000);
  param_1[2] = pvVar1;
  if (pvVar1 == (void *)0x0) {
    param_1[3] = param_1[3] | 4;
    param_1[2] = param_1 + 5;
    param_1[6] = 2;
  }
  else {
    param_1[3] = param_1[3] | 8;
    param_1[6] = 0x1000;
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return;
}


/* 004c6071 size=41 */

byte __cdecl FUN_004c6071(uint param_1)

{
  if (param_1 < DAT_004ed3a0) {
    return *(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 0x40;
  }
  return 0;
}


/* 004c609a size=89 */

int __cdecl FUN_004c609a(LPSTR param_1,WCHAR param_2)

{
  int iVar1;
  bool bVar2;
  
  InterlockedIncrement((LONG *)&DAT_004ed28c);
  bVar2 = DAT_004ed288 != 0;
  if (bVar2) {
    InterlockedDecrement((LONG *)&DAT_004ed28c);
    FUN_004bf7a0(0x13);
  }
  iVar1 = FUN_004c60f3(param_1,param_2);
  if (bVar2) {
    FUN_004bf801(0x13);
  }
  else {
    InterlockedDecrement((LONG *)&DAT_004ed28c);
  }
  return iVar1;
}


/* 004c60f3 size=105 */

int __cdecl FUN_004c60f3(LPSTR param_1,WCHAR param_2)

{
  LPSTR lpMultiByteStr;
  int iVar1;
  DWORD *pDVar2;
  
  lpMultiByteStr = param_1;
  if (param_1 == (LPSTR)0x0) {
    return 0;
  }
  if (DAT_004ecd78 == 0) {
    if ((ushort)param_2 < 0x100) {
      *param_1 = (CHAR)param_2;
      return 1;
    }
  }
  else {
    param_1 = (LPSTR)0x0;
    iVar1 = WideCharToMultiByte(DAT_004ecd88,0x220,&param_2,1,lpMultiByteStr,DAT_004e36dc,
                                (LPCSTR)0x0,(LPBOOL)&param_1);
    if ((iVar1 != 0) && (param_1 == (LPSTR)0x0)) {
      return iVar1;
    }
  }
  pDVar2 = FUN_004c09cc();
  *pDVar2 = 0x2a;
  return -1;
}


/* 004c61d5 size=291 */

uint FUN_004c61d5(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  uint uVar4;
  int local_8;
  int local_4;
  
  uVar4 = 0xffffffff;
  FUN_004bf7a0(0x12);
  local_8 = 0;
  local_4 = 0;
  piVar3 = &DAT_004ed2a0;
  while (puVar2 = (undefined4 *)*piVar3, puVar1 = puVar2, puVar2 != (undefined4 *)0x0) {
    for (; puVar2 < puVar1 + 0x120; puVar2 = puVar2 + 9) {
      if ((*(byte *)(puVar2 + 1) & 1) == 0) {
        if (puVar2[2] == 0) {
          FUN_004bf7a0(0x11);
          if (puVar2[2] == 0) {
            InitializeCriticalSection((LPCRITICAL_SECTION)(puVar2 + 3));
            puVar2[2] = puVar2[2] + 1;
          }
          FUN_004bf801(0x11);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)(puVar2 + 3));
        if ((*(byte *)(puVar2 + 1) & 1) == 0) {
          *puVar2 = 0xffffffff;
          uVar4 = ((int)puVar2 - *piVar3) / 0x24 + local_4;
          if (uVar4 != 0xffffffff) goto LAB_004c62e7;
          break;
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)(puVar2 + 3));
      }
      puVar1 = (undefined4 *)*piVar3;
    }
    local_4 = local_4 + 0x20;
    piVar3 = piVar3 + 1;
    local_8 = local_8 + 1;
    if (0x4ed39f < (int)piVar3) goto LAB_004c62e7;
  }
  puVar2 = _malloc(0x480);
  if (puVar2 != (undefined4 *)0x0) {
    DAT_004ed3a0 = DAT_004ed3a0 + 0x20;
    (&DAT_004ed2a0)[local_8] = puVar2;
    puVar1 = puVar2;
    for (; puVar2 < puVar1 + 0x120; puVar2 = puVar2 + 9) {
      *(undefined1 *)(puVar2 + 1) = 0;
      *puVar2 = 0xffffffff;
      puVar2[2] = 0;
      *(undefined1 *)((int)puVar2 + 5) = 10;
      puVar1 = (undefined4 *)(&DAT_004ed2a0)[local_8];
    }
    uVar4 = local_8 << 5;
    FUN_004c6435(uVar4);
  }
LAB_004c62e7:
  FUN_004bf801(0x12);
  return uVar4;
}


/* 004c62f8 size=124 */

undefined4 __cdecl FUN_004c62f8(uint param_1,HANDLE param_2)

{
  DWORD *pDVar1;
  int iVar2;
  DWORD nStdHandle;
  
  if (param_1 < DAT_004ed3a0) {
    iVar2 = (param_1 & 0x1f) * 0x24;
    if (*(int *)((&DAT_004ed2a0)[(int)param_1 >> 5] + iVar2) == -1) {
      if (DAT_004e0e64 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_004c6351;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,param_2);
      }
LAB_004c6351:
      *(HANDLE *)((&DAT_004ed2a0)[(int)param_1 >> 5] + iVar2) = param_2;
      return 0;
    }
  }
  pDVar1 = FUN_004c09cc();
  *pDVar1 = 9;
  pDVar1 = FUN_004c09d5();
  *pDVar1 = 0;
  return 0xffffffff;
}


/* 004c6374 size=127 */

undefined4 __cdecl FUN_004c6374(uint param_1)

{
  int *piVar1;
  DWORD *pDVar2;
  int iVar3;
  DWORD nStdHandle;
  
  if (param_1 < DAT_004ed3a0) {
    iVar3 = (param_1 & 0x1f) * 0x24;
    piVar1 = (int *)((&DAT_004ed2a0)[(int)param_1 >> 5] + iVar3);
    if (((*(byte *)(piVar1 + 1) & 1) != 0) && (*piVar1 != -1)) {
      if (DAT_004e0e64 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_004c63d0;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_004c63d0:
      *(undefined4 *)((&DAT_004ed2a0)[(int)param_1 >> 5] + iVar3) = 0xffffffff;
      return 0;
    }
  }
  pDVar2 = FUN_004c09cc();
  *pDVar2 = 9;
  pDVar2 = FUN_004c09d5();
  *pDVar2 = 0;
  return 0xffffffff;
}


/* 004c63f3 size=66 */

undefined4 __cdecl FUN_004c63f3(uint param_1)

{
  DWORD *pDVar1;
  
  if ((param_1 < DAT_004ed3a0) &&
     ((*(byte *)((&DAT_004ed2a0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
    return *(undefined4 *)((&DAT_004ed2a0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 0x24);
  }
  pDVar1 = FUN_004c09cc();
  *pDVar1 = 9;
  pDVar1 = FUN_004c09d5();
  *pDVar1 = 0;
  return 0xffffffff;
}


/* 004c6435 size=95 */

void __cdecl FUN_004c6435(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (param_1 & 0x1f) * 0x24;
  iVar1 = (&DAT_004ed2a0)[(int)param_1 >> 5] + iVar2;
  if (*(int *)(iVar1 + 8) == 0) {
    FUN_004bf7a0(0x11);
    if (*(int *)(iVar1 + 8) == 0) {
      InitializeCriticalSection((LPCRITICAL_SECTION)(iVar1 + 0xc));
      *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + 1;
    }
    FUN_004bf801(0x11);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)((&DAT_004ed2a0)[(int)param_1 >> 5] + 0xc + iVar2));
  return;
}


/* 004c6494 size=34 */

void __cdecl FUN_004c6494(uint param_1)

{
  LeaveCriticalSection
            ((LPCRITICAL_SECTION)
             ((&DAT_004ed2a0)[(int)param_1 >> 5] + 0xc + (param_1 & 0x1f) * 0x24));
  return;
}


/* 004c64b6 size=719 */

uint __cdecl FUN_004c64b6(LPCSTR param_1,uint param_2,uint param_3,uint param_4)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  DWORD *pDVar4;
  HANDLE hFile;
  DWORD DVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  _SECURITY_ATTRIBUTES local_20;
  DWORD local_14;
  DWORD local_10;
  DWORD local_c;
  byte local_5;
  
  bVar8 = (param_2 & 0x80) == 0;
  local_20.nLength = 0xc;
  local_20.lpSecurityDescriptor = (LPVOID)0x0;
  if (bVar8) {
    local_5 = 0;
  }
  else {
    local_5 = 0x10;
  }
  local_20.bInheritHandle = (BOOL)bVar8;
  if (((param_2 & 0x8000) == 0) && (((param_2 & 0x4000) != 0 || (DAT_004ecffc != 0x8000)))) {
    local_5 = local_5 | 0x80;
  }
  uVar2 = param_2 & 3;
  if (uVar2 == 0) {
    local_10 = 0x80000000;
  }
  else if (uVar2 == 1) {
    local_10 = 0x40000000;
  }
  else {
    if (uVar2 != 2) goto LAB_004c65ba;
    local_10 = 0xc0000000;
  }
  if (param_3 == 0x10) {
    local_14 = 0;
  }
  else if (param_3 == 0x20) {
    local_14 = 1;
  }
  else if (param_3 == 0x30) {
    local_14 = 2;
  }
  else {
    if (param_3 != 0x40) goto LAB_004c65ba;
    local_14 = 3;
  }
  uVar2 = param_2 & 0x700;
  if (uVar2 < 0x401) {
    if ((uVar2 == 0x400) || (uVar2 == 0)) {
      local_c = 3;
    }
    else if (uVar2 == 0x100) {
      local_c = 4;
    }
    else {
      if (uVar2 == 0x200) goto LAB_004c65d4;
      if (uVar2 != 0x300) goto LAB_004c65ba;
      local_c = 2;
    }
  }
  else {
    if (uVar2 != 0x500) {
      if (uVar2 == 0x600) {
LAB_004c65d4:
        local_c = 5;
        goto LAB_004c65e4;
      }
      if (uVar2 != 0x700) {
LAB_004c65ba:
        pDVar4 = FUN_004c09cc();
        *pDVar4 = 0x16;
        pDVar4 = FUN_004c09d5();
        *pDVar4 = 0;
        return 0xffffffff;
      }
    }
    local_c = 1;
  }
LAB_004c65e4:
  uVar2 = 0x80;
  if (((param_2 & 0x100) != 0) && ((~DAT_004ecc84 & param_4 & 0x80) == 0)) {
    uVar2 = 1;
  }
  if ((param_2 & 0x40) != 0) {
    uVar2 = uVar2 | 0x4000000;
    local_10 = CONCAT13((*(uint8_t*)((char*)&local_10+3)),0x10000);
  }
  if ((param_2 & 0x1000) != 0) {
    uVar2 = uVar2 | 0x100;
  }
  if ((param_2 & 0x20) == 0) {
    if ((param_2 & 0x10) != 0) {
      uVar2 = uVar2 | 0x10000000;
    }
  }
  else {
    uVar2 = uVar2 | 0x8000000;
  }
  uVar3 = FUN_004c61d5();
  if (uVar3 == 0xffffffff) {
    pDVar4 = FUN_004c09cc();
    *pDVar4 = 0x18;
    pDVar4 = FUN_004c09d5();
    *pDVar4 = 0;
    return 0xffffffff;
  }
  hFile = CreateFileA(param_1,local_10,local_14,&local_20,local_c,uVar2,(HANDLE)0x0);
  if (hFile != (HANDLE)0xffffffff) {
    DVar5 = GetFileType(hFile);
    if (DVar5 != 0) {
      if (DVar5 == 2) {
        local_5 = local_5 | 0x40;
      }
      else if (DVar5 == 3) {
        local_5 = local_5 | 8;
      }
      FUN_004c62f8(uVar3,hFile);
      iVar7 = (uVar3 & 0x1f) * 0x24;
      (*(uint8_t*)((char*)&param_1+3)) = local_5 & 0x48;
      *(byte *)((&DAT_004ed2a0)[(int)uVar3 >> 5] + 4 + iVar7) = local_5 | 1;
      if ((((local_5 & 0x48) == 0) && ((local_5 & 0x80) != 0)) && ((param_2 & 2) != 0)) {
        local_14 = FUN_004c072a(uVar3,-1,2);
        if (local_14 == 0xffffffff) {
          pDVar4 = FUN_004c09d5();
          if (*pDVar4 == 0x83) goto LAB_004c675e;
        }
        else {
          param_3 = param_3 & 0xffffff;
          iVar6 = FUN_004c1a07(uVar3,(char *)((int)&param_3 + 3),(char *)0x1);
          if ((((iVar6 != 0) || ((*(uint8_t*)((char*)&param_3+3)) != '\x1a')) ||
              (iVar6 = FUN_004c7ecb(uVar3,local_14), iVar6 != -1)) &&
             (DVar5 = FUN_004c072a(uVar3,0,0), DVar5 != 0xffffffff)) goto LAB_004c675e;
        }
        FUN_004c0138(uVar3);
        uVar2 = 0xffffffff;
      }
      else {
LAB_004c675e:
        if (((*(uint8_t*)((char*)&param_1+3)) == 0) && ((param_2 & 8) != 0)) {
          pbVar1 = (byte *)((&DAT_004ed2a0)[(int)uVar3 >> 5] + 4 + iVar7);
          *pbVar1 = *pbVar1 | 0x20;
        }
        uVar2 = uVar3;
      }
      goto LAB_004c6777;
    }
    CloseHandle(hFile);
  }
  DVar5 = GetLastError();
  FUN_004c0959(DVar5);
  uVar2 = 0xffffffff;
LAB_004c6777:
  FUN_004c6494(uVar3);
  return uVar2;
}


/* 004c6785 size=3 */

undefined4 FUN_004c6785(void)

{
  return 0;
}


/* 004c6788 size=1185 */

/* FUN_004c6788: lifted from original x86 -> lt_lifted.c */


/* 004c6c59 size=318 */

BOOL __cdecl
FUN_004c6c59(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6,
            int param_7)

{
  WCHAR *pWVar1;
  BOOL BVar2;
  int iVar3;
  undefined1 unaff_DI;
  undefined1 uStack00000000;
  WCHAR aWStack_2a [5];
  WORD local_20 [2];
  undefined1 *local_1c;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004cf700;
  puStack_10 = &LAB_004ba918;
  local_14 = ExceptionList;
  local_1c = (undefined1 *)(aWStack_2a + -7);
  ExceptionList = &local_14;
  pWVar1 = aWStack_2a + -7;
  if (DAT_004eceb0 == 0) {
    iVar3 = 1;
    ExceptionList = &local_14;
    BVar2 = GetStringTypeW(1,L"",1,local_20);
    if (BVar2 == 0) {
      BVar2 = GetStringTypeA(0,1,"",1,local_20);
      if (BVar2 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      iVar3 = 2;
    }
    DAT_004eceb0 = iVar3;
    pWVar1 = (WCHAR *)local_1c;
  }
  local_1c = (undefined1 *)pWVar1;
  if (DAT_004eceb0 == 2) {
    if (param_6 == 0) {
      param_6 = DAT_004ecd78;
    }
    BVar2 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
    ExceptionList = local_14;
    return BVar2;
  }
  if (DAT_004eceb0 == 1) {
    if (param_5 == 0) {
      param_5 = DAT_004ecd88;
    }
    iVar3 = MultiByteToWideChar(param_5,(-(uint)(param_7 != 0) & 8) + 1,param_2,param_3,(LPWSTR)0x0,
                                0);
    if (iVar3 != 0) {
      local_8 = 0;
      FUN_004ba7f0(unaff_DI);
      local_1c = (undefined1 *)(aWStack_2a + -7);
      _memset(aWStack_2a + -7,0,iVar3 * 2);
      local_8 = 0xffffffff;
      if ((&uStack00000000 != &DAT_00000038) &&
         (iVar3 = MultiByteToWideChar(param_5,1,param_2,param_3,aWStack_2a + -7,iVar3), iVar3 != 0))
      {
        BVar2 = GetStringTypeW(param_1,aWStack_2a + -7,iVar3,param_4);
        ExceptionList = local_14;
        return BVar2;
      }
    }
  }
  ExceptionList = local_14;
  return 0;
}


/* 004c6da2 size=208 */

void __cdecl FUN_004c6da2(uint param_1,int *param_2,ushort *param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  uint local_5c [10];
  undefined8 local_34;
  uint local_24;
  
  param_3 = (ushort *)(uint)*param_3;
  iVar2 = *param_2;
  if (iVar2 == 1) {
LAB_004c6de7:
    uVar3 = 8;
  }
  else if (iVar2 == 2) {
    uVar3 = 4;
  }
  else if (iVar2 == 3) {
    uVar3 = 0x11;
  }
  else if (iVar2 == 4) {
    uVar3 = 0x12;
  }
  else {
    if (iVar2 == 5) goto LAB_004c6de7;
    if (iVar2 == 7) {
      *param_2 = 1;
      goto LAB_004c6e3d;
    }
    if (iVar2 != 8) goto LAB_004c6e3d;
    uVar3 = 0x10;
  }
  bVar1 = FUN_004c0d7d(uVar3,(double *)(param_2 + 6),(uint)param_3);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    if (((param_1 == 0x10) || (param_1 == 0x16)) || (param_1 == 0x1d)) {
      local_34 = *(undefined8 *)(param_2 + 4);
      local_24 = local_24 & 0xffffffe3 | 3;
    }
    else {
      local_24 = local_24 & 0xfffffffe;
    }
    FUN_004c0aca(local_5c,(uint *)&param_3,uVar3,param_1,(undefined8 *)(param_2 + 2),
                 (undefined8 *)(param_2 + 6));
  }
LAB_004c6e3d:
  FUN_004c1209();
  if (((*param_2 == 8) || (DAT_004e3bf0 != 0)) || (iVar2 = FUN_004c6785(), iVar2 == 0)) {
    FUN_004c101c(*param_2);
    return;
  }
  return;
}


/* 004c6e72 size=46 */

void FUN_004c6e72(void)

{
  if (DAT_004ecf70 == 0) {
    FUN_004bf7a0(0xb);
    if (DAT_004ecf70 == 0) {
      FUN_004c6ea0();
      DAT_004ecf70 = DAT_004ecf70 + 1;
    }
    FUN_004bf801(0xb);
  }
  return;
}


/* 004c6ea0 size=647 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004c6ea0(void)

{
  char cVar1;
  char cVar2;
  uint *_Str1;
  DWORD DVar3;
  int iVar4;
  size_t sVar5;
  void *this;
  uint *_Source;
  int local_8;
  
  FUN_004bf7a0(0xc);
  DAT_004e3c98 = 0xffffffff;
  DAT_004e3c88 = 0xffffffff;
  DAT_004eceb8 = 0;
  _Str1 = (uint *)FUN_004c828c("TZ");
  if (_Str1 == (uint *)0x0) {
    FUN_004bf801(0xc);
    DVar3 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&DAT_004ecec0);
    if (DVar3 == 0xffffffff) {
      return;
    }
    DAT_004e3bf4 = (void *)(DAT_004ecec0 * 0x3c);
    DAT_004eceb8 = 1;
    if (DAT_004ecf06 != 0) {
      DAT_004e3bf4 = (void *)((int)DAT_004e3bf4 + DAT_004ecf14 * 0x3c);
    }
    if ((DAT_004ecf5a == 0) || (DAT_004ecf68 == 0)) {
      DAT_004e3bf8 = 0;
      _DAT_004e3bfc = 0;
    }
    else {
      DAT_004e3bf8 = 1;
      _DAT_004e3bfc = (DAT_004ecf68 - DAT_004ecf14) * 0x3c;
    }
    iVar4 = WideCharToMultiByte(DAT_004ecd88,0x220,(LPCWSTR)&DAT_004ecec4,-1,PTR_DAT_004e3c80,0x3f,
                                (LPCSTR)0x0,&local_8);
    if ((iVar4 == 0) || (local_8 != 0)) {
      *PTR_DAT_004e3c80 = 0;
    }
    else {
      PTR_DAT_004e3c80[0x3f] = 0;
    }
    iVar4 = WideCharToMultiByte(DAT_004ecd88,0x220,(LPCWSTR)&DAT_004ecf18,-1,PTR_DAT_004e3c84,0x3f,
                                (LPCSTR)0x0,&local_8);
    if ((iVar4 != 0) && (local_8 == 0)) {
      PTR_DAT_004e3c84[0x3f] = 0;
      return;
    }
LAB_004c7111:
    *PTR_DAT_004e3c84 = 0;
  }
  else {
    if (((char)*_Str1 != '\0') &&
       ((DAT_004ecf6c == (uint *)0x0 ||
        (iVar4 = _strcmp((char *)_Str1,(char *)DAT_004ecf6c), iVar4 != 0)))) {
      FUN_004b9d3f((undefined *)DAT_004ecf6c);
      sVar5 = _strlen((char *)_Str1);
      DAT_004ecf6c = _malloc(sVar5 + 1);
      if (DAT_004ecf6c != (uint *)0x0) {
        FUN_004c17f0(DAT_004ecf6c,_Str1);
        FUN_004bf801(0xc);
        _strncpy(PTR_DAT_004e3c80,(char *)_Str1,3);
        _Source = (uint *)((int)_Str1 + 3);
        PTR_DAT_004e3c80[3] = 0;
        cVar1 = *(char *)_Source;
        if (cVar1 == '-') {
          _Source = _Str1 + 1;
        }
        iVar4 = FUN_004bb0dc(this,(byte *)_Source);
        DAT_004e3bf4 = (void *)(iVar4 * 0xe10);
        for (; (cVar2 = (char)*_Source, cVar2 == '+' || (('/' < cVar2 && (cVar2 < ':'))));
            _Source = (uint *)((int)_Source + 1)) {
        }
        if ((char)*_Source == ':') {
          _Source = (uint *)((int)_Source + 1);
          iVar4 = FUN_004bb0dc(DAT_004e3bf4,(byte *)_Source);
          DAT_004e3bf4 = (void *)((int)DAT_004e3bf4 + iVar4 * 0x3c);
          for (; ('/' < (char)*_Source && ((char)*_Source < ':'));
              _Source = (uint *)((int)_Source + 1)) {
          }
          if ((char)*_Source == ':') {
            _Source = (uint *)((int)_Source + 1);
            iVar4 = FUN_004bb0dc(DAT_004e3bf4,(byte *)_Source);
            DAT_004e3bf4 = (void *)((int)DAT_004e3bf4 + iVar4);
            for (; ('/' < (char)*_Source && ((char)*_Source < ':'));
                _Source = (uint *)((int)_Source + 1)) {
            }
          }
        }
        if (cVar1 == '-') {
          DAT_004e3bf4 = (void *)-(int)DAT_004e3bf4;
        }
        DAT_004e3bf8 = (int)(char)*_Source;
        if (DAT_004e3bf8 != 0) {
          _strncpy(PTR_DAT_004e3c84,(char *)_Source,3);
          PTR_DAT_004e3c84[3] = 0;
          return;
        }
        goto LAB_004c7111;
      }
    }
    FUN_004bf801(0xc);
  }
  return;
}


/* 004c7127 size=33 */

bool __cdecl FUN_004c7127(int *param_1)

{
  bool bVar1;
  
  FUN_004bf7a0(0xb);
  bVar1 = FUN_004c7148(param_1);
  FUN_004bf801(0xb);
  return bVar1;
}


/* 004c7148 size=428 */

bool __cdecl FUN_004c7148(int *param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  if (DAT_004e3bf8 != 0) {
    uVar6 = param_1[5];
    if ((uVar6 != DAT_004e3c88) || (uVar6 != DAT_004e3c98)) {
      if (DAT_004eceb8 == 0) {
        FUN_004c72f4(1,1,uVar6,4,1,0,0,2,0,0,0);
        FUN_004c72f4(0,1,param_1[5],10,5,0,0,2,0,0,0);
      }
      else {
        if (DAT_004ecf58 != 0) {
          uVar7 = (uint)DAT_004ecf5e;
          uVar4 = 0;
          uVar5 = 0;
        }
        else {
          uVar4 = (uint)DAT_004ecf5c;
          uVar7 = 0;
          uVar5 = (uint)DAT_004ecf5e;
        }
        FUN_004c72f4(1,(uint)(DAT_004ecf58 == 0),uVar6,(uint)DAT_004ecf5a,uVar5,uVar4,uVar7,
                     (uint)DAT_004ecf60,(uint)DAT_004ecf62,(uint)DAT_004ecf64,(uint)DAT_004ecf66);
        if (DAT_004ecf04 != 0) {
          uVar7 = (uint)DAT_004ecf0a;
          uVar4 = 0;
          uVar5 = 0;
          uVar6 = param_1[5];
        }
        else {
          uVar4 = (uint)DAT_004ecf08;
          uVar7 = 0;
          uVar5 = (uint)DAT_004ecf0a;
          uVar6 = param_1[5];
        }
        FUN_004c72f4(0,(uint)(DAT_004ecf04 == 0),uVar6,(uint)DAT_004ecf06,uVar5,uVar4,uVar7,
                     (uint)DAT_004ecf0c,(uint)DAT_004ecf0e,(uint)DAT_004ecf10,(uint)DAT_004ecf12);
      }
    }
    iVar1 = param_1[7];
    if (DAT_004e3c8c < DAT_004e3c9c) {
      if ((DAT_004e3c8c <= iVar1) && (iVar1 <= DAT_004e3c9c)) {
        if ((DAT_004e3c8c < iVar1) && (iVar1 < DAT_004e3c9c)) {
          return true;
        }
LAB_004c72c0:
        iVar3 = ((param_1[2] * 0x3c + param_1[1]) * 0x3c + *param_1) * 1000;
        if (iVar1 == DAT_004e3c8c) {
          bVar2 = DAT_004e3c90 <= iVar3;
        }
        else {
          bVar2 = iVar3 < DAT_004e3ca0;
        }
        return bVar2;
      }
    }
    else {
      if (iVar1 < DAT_004e3c9c) {
        return true;
      }
      if (DAT_004e3c8c < iVar1) {
        return true;
      }
      if ((iVar1 <= DAT_004e3c9c) || (DAT_004e3c8c <= iVar1)) goto LAB_004c72c0;
    }
  }
  return false;
}


/* 004c72f4 size=320 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_004c72f4(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 1) {
    if ((param_3 & 3) == 0) {
      iVar1 = (&DAT_004e3ca0)[param_4];
    }
    else {
      iVar1 = *(int *)(&DAT_004e3cd4 + param_4 * 4);
    }
    iVar2 = (int)(param_3 * 0x16d + -0x63db + iVar1 + 1 + ((int)(param_3 - 1) >> 2)) % 7;
    if (param_6 < iVar2) {
      iVar1 = iVar1 + 1 + (param_5 * 7 - iVar2) + param_6;
    }
    else {
      iVar1 = iVar1 + -6 + (param_5 * 7 - iVar2) + param_6;
    }
    if (param_5 == 5) {
      if ((param_3 & 3) == 0) {
        iVar2 = *(int *)(&DAT_004e3ca4 + param_4 * 4);
      }
      else {
        iVar2 = *(int *)(&DAT_004e3cd8 + param_4 * 4);
      }
      if (iVar2 < iVar1) {
        iVar1 = iVar1 + -7;
      }
    }
  }
  else {
    if ((param_3 & 3) == 0) {
      iVar1 = (&DAT_004e3ca0)[param_4];
    }
    else {
      iVar1 = *(int *)(&DAT_004e3cd4 + param_4 * 4);
    }
    iVar1 = iVar1 + param_7;
  }
  if (param_1 == 1) {
    DAT_004e3c88 = param_3;
    DAT_004e3c8c = iVar1;
    DAT_004e3c90 = ((param_8 * 0x3c + param_9) * 0x3c + param_10) * 1000 + param_11;
    return;
  }
  DAT_004e3ca0 = ((param_8 * 0x3c + param_9) * 0x3c + _DAT_004e3bfc + param_10) * 1000 + param_11;
  if (DAT_004e3ca0 < 0) {
    DAT_004e3ca0 = DAT_004e3ca0 + 86400000;
    DAT_004e3c9c = iVar1 + -1;
  }
  else {
    if (DAT_004e3ca0 < 86400000) {
      DAT_004e3c98 = param_3;
      DAT_004e3c9c = iVar1;
      return;
    }
    DAT_004e3ca0 = DAT_004e3ca0 + -86400000;
    DAT_004e3c9c = iVar1 + 1;
  }
  DAT_004e3c98 = param_3;
  return;
}


/* 004c7434 size=93 */

uint __cdecl FUN_004c7434(LPWSTR param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  bool bVar2;
  
  InterlockedIncrement((LONG *)&DAT_004ed28c);
  bVar2 = DAT_004ed288 != 0;
  if (bVar2) {
    InterlockedDecrement((LONG *)&DAT_004ed28c);
    FUN_004bf7a0(0x13);
  }
  uVar1 = FUN_004c7491(param_1,param_2,param_3);
  if (bVar2) {
    FUN_004bf801(0x13);
  }
  else {
    InterlockedDecrement((LONG *)&DAT_004ed28c);
  }
  return uVar1;
}


/* 004c7491 size=201 */

/* FUN_004c7491: lifted from original x86 -> lt_lifted.c */


/* 004c757f size=110 */

uint __cdecl FUN_004c757f(uint param_1,int *param_2)

{
  uint uVar1;
  
  if ((param_1 == 0xffffffff) ||
     ((uVar1 = param_2[3], (uVar1 & 1) == 0 && (((uVar1 & 0x80) == 0 || ((uVar1 & 2) != 0)))))) {
    return 0xffffffff;
  }
  if (param_2[2] == 0) {
    FUN_004c602d(param_2);
  }
  if (*param_2 == param_2[2]) {
    if (param_2[1] != 0) {
      return 0xffffffff;
    }
    *param_2 = *param_2 + 1;
  }
  if ((*(byte *)(param_2 + 3) & 0x40) == 0) {
    *param_2 = *param_2 + -1;
    *(char *)*param_2 = (char)param_1;
  }
  else {
    *param_2 = *param_2 + -1;
    if (*(char *)*param_2 != (char)param_1) {
      *param_2 = (int)((char *)*param_2 + 1);
      return 0xffffffff;
    }
  }
  param_2[1] = param_2[1] + 1;
  param_2[3] = param_2[3] & 0xffffffefU | 1;
  return param_1 & 0xff;
}


/* 004c75ed size=28 */

bool __cdecl FUN_004c75ed(void *param_1,UINT_PTR param_2)

{
  BOOL BVar1;
  
  BVar1 = IsBadReadPtr(param_1,param_2);
  return BVar1 == 0;
}


/* 004c7609 size=28 */

bool __cdecl FUN_004c7609(LPVOID param_1,UINT_PTR param_2)

{
  BOOL BVar1;
  
  BVar1 = IsBadWritePtr(param_1,param_2);
  return BVar1 == 0;
}


/* 004c7625 size=24 */

bool __cdecl FUN_004c7625(FARPROC param_1)

{
  BOOL BVar1;
  
  BVar1 = IsBadCodePtr(param_1);
  return BVar1 == 0;
}


/* 004c763d size=23 */

void FUN_004c763d(void)

{
  FUN_004c5199(10);
  FUN_004c78d8((DWORD *)0x16);
                    /* WARNING: Subroutine does not return */
  __exit(3);
}


/* 004c7660 size=62 */

int __cdecl FUN_004c7660(byte *param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  byte abStack_28 [32];
  
  abStack_28[0x1c] = 0;
  abStack_28[0x1d] = 0;
  abStack_28[0x1e] = 0;
  abStack_28[0x1f] = 0;
  abStack_28[0x18] = 0;
  abStack_28[0x19] = 0;
  abStack_28[0x1a] = 0;
  abStack_28[0x1b] = 0;
  abStack_28[0x14] = 0;
  abStack_28[0x15] = 0;
  abStack_28[0x16] = 0;
  abStack_28[0x17] = 0;
  abStack_28[0x10] = 0;
  abStack_28[0x11] = 0;
  abStack_28[0x12] = 0;
  abStack_28[0x13] = 0;
  abStack_28[0xc] = 0;
  abStack_28[0xd] = 0;
  abStack_28[0xe] = 0;
  abStack_28[0xf] = 0;
  abStack_28[8] = 0;
  abStack_28[9] = 0;
  abStack_28[10] = 0;
  abStack_28[0xb] = 0;
  abStack_28[4] = 0;
  abStack_28[5] = 0;
  abStack_28[6] = 0;
  abStack_28[7] = 0;
  abStack_28[0] = 0;
  abStack_28[1] = 0;
  abStack_28[2] = 0;
  abStack_28[3] = 0;
  while( true ) {
    bVar1 = *param_2;
    if (bVar1 == 0) break;
    param_2 = param_2 + 1;
    abStack_28[(int)(uint)bVar1 >> 3] = abStack_28[(int)(uint)bVar1 >> 3] | '\x01' << (bVar1 & 7);
  }
  iVar2 = -1;
  do {
    iVar2 = iVar2 + 1;
    bVar1 = *param_1;
    if (bVar1 == 0) {
      return iVar2;
    }
    param_1 = param_1 + 1;
  } while ((abStack_28[(int)(uint)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return iVar2;
}


/* 004c76a0 size=58 */

byte * __cdecl FUN_004c76a0(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte abStack_28 [32];
  
  abStack_28[0x1c] = 0;
  abStack_28[0x1d] = 0;
  abStack_28[0x1e] = 0;
  abStack_28[0x1f] = 0;
  abStack_28[0x18] = 0;
  abStack_28[0x19] = 0;
  abStack_28[0x1a] = 0;
  abStack_28[0x1b] = 0;
  abStack_28[0x14] = 0;
  abStack_28[0x15] = 0;
  abStack_28[0x16] = 0;
  abStack_28[0x17] = 0;
  abStack_28[0x10] = 0;
  abStack_28[0x11] = 0;
  abStack_28[0x12] = 0;
  abStack_28[0x13] = 0;
  abStack_28[0xc] = 0;
  abStack_28[0xd] = 0;
  abStack_28[0xe] = 0;
  abStack_28[0xf] = 0;
  abStack_28[8] = 0;
  abStack_28[9] = 0;
  abStack_28[10] = 0;
  abStack_28[0xb] = 0;
  abStack_28[4] = 0;
  abStack_28[5] = 0;
  abStack_28[6] = 0;
  abStack_28[7] = 0;
  abStack_28[0] = 0;
  abStack_28[1] = 0;
  abStack_28[2] = 0;
  abStack_28[3] = 0;
  while( true ) {
    bVar1 = *param_2;
    if (bVar1 == 0) break;
    param_2 = param_2 + 1;
    abStack_28[(int)(uint)bVar1 >> 3] = abStack_28[(int)(uint)bVar1 >> 3] | '\x01' << (bVar1 & 7);
  }
  do {
    pbVar2 = param_1;
    bVar1 = *pbVar2;
    if (bVar1 == 0) {
      return (byte *)0x0;
    }
    param_1 = pbVar2 + 1;
  } while ((abStack_28[(int)(uint)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return pbVar2;
}


/* 004c76da size=17 */

int __cdecl FUN_004c76da(byte param_1)

{
  FUN_004c76eb(param_1,0,4);
  return;
}


/* 004c76eb size=49 */

undefined4 __cdecl FUN_004c76eb(byte param_1,uint param_2,byte param_3)

{
  uint uVar1;
  
  if ((*(byte *)((int)&DAT_004ed180 + param_1 + 1) & param_3) == 0) {
    if (param_2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = *(ushort *)(&DAT_004e34da + (uint)param_1 * 2) & param_2;
    }
    if (uVar1 == 0) {
      return 0;
    }
  }
  return 1;
}


/* 004c771c size=137 */

/* FUN_004c771c: lifted from original x86 -> lt_lifted.c */


/* 004c77a5 size=39 */

uint * __cdecl FUN_004c77a5(uint *param_1,size_t param_2)

{
  uint *puVar1;
  
  FUN_004bf7a0(0xc);
  puVar1 = FUN_004c77cc(0,param_1,param_2);
  FUN_004bf801(0xc);
  return puVar1;
}


/* 004c77cc size=213 */

uint * __cdecl FUN_004c77cc(uint param_1,uint *param_2,size_t param_3)

{
  int iVar1;
  DWORD *pDVar2;
  DWORD DVar3;
  uint uVar4;
  uint *puVar5;
  uint local_10c [65];
  LPSTR local_8;
  
  uVar4 = param_1;
  if (param_1 == 0) {
    DVar3 = GetCurrentDirectoryA(0x104,(LPSTR)local_10c);
  }
  else {
    iVar1 = FUN_004c78a1(param_1);
    if (iVar1 == 0) {
      pDVar2 = FUN_004c09d5();
      *pDVar2 = 0xf;
      pDVar2 = FUN_004c09cc();
      *pDVar2 = 0xd;
      return (uint *)0x0;
    }
    param_1 = (uint)CONCAT12(0x2e,CONCAT11(0x3a,(char)uVar4 + '@'));
    DVar3 = GetFullPathNameA((LPCSTR)&param_1,0x104,(LPSTR)local_10c,&local_8);
  }
  if ((DVar3 != 0) && (uVar4 = DVar3 + 1, uVar4 < 0x105)) {
    if (param_2 == (uint *)0x0) {
      if ((int)uVar4 <= (int)param_3) {
        uVar4 = param_3;
      }
      puVar5 = _malloc(uVar4);
      if (puVar5 != (uint *)0x0) {
LAB_004c788d:
        puVar5 = FUN_004c17f0(puVar5,local_10c);
        return puVar5;
      }
      pDVar2 = FUN_004c09cc();
      *pDVar2 = 0xc;
    }
    else {
      puVar5 = param_2;
      if ((int)uVar4 <= (int)param_3) goto LAB_004c788d;
      pDVar2 = FUN_004c09cc();
      *pDVar2 = 0x22;
    }
  }
  return (uint *)0x0;
}


/* 004c78a1 size=55 */

undefined4 __cdecl FUN_004c78a1(uint param_1)

{
  char cVar1;
  UINT UVar2;
  
  if (param_1 != 0) {
    cVar1 = (char)param_1;
    param_1 = (uint)CONCAT12(0x5c,CONCAT11(0x3a,cVar1 + '@'));
    UVar2 = GetDriveTypeA((LPCSTR)&param_1);
    if ((UVar2 == 0) || (UVar2 == 1)) {
      return 0;
    }
  }
  return 1;
}


/* 004c78d8 size=386 */

undefined4 __cdecl FUN_004c78d8(DWORD *param_1)

{
  bool bVar1;
  DWORD *pDVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  code *pcVar6;
  undefined4 *puVar7;
  DWORD local_10;
  DWORD local_c;
  
  bVar1 = false;
  if (param_1 == (DWORD *)0x2) {
    puVar7 = &DAT_004ecfe8;
    pcVar6 = DAT_004ecfe8;
LAB_004c795e:
    bVar1 = true;
    FUN_004bf7a0(1);
    pDVar2 = param_1;
  }
  else {
    if (((param_1 != (DWORD *)0x4) && (param_1 != (DWORD *)0x8)) && (param_1 != (DWORD *)0xb)) {
      if (param_1 == (DWORD *)0xf) {
        puVar7 = &DAT_004ecff4;
        pcVar6 = DAT_004ecff4;
      }
      else if (param_1 == (DWORD *)0x15) {
        puVar7 = &DAT_004ecfec;
        pcVar6 = DAT_004ecfec;
      }
      else {
        if (param_1 != (DWORD *)0x16) {
          return 0xffffffff;
        }
        puVar7 = &DAT_004ecff0;
        pcVar6 = DAT_004ecff0;
      }
      goto LAB_004c795e;
    }
    pDVar2 = FUN_004c04e2();
    uVar3 = FUN_004c7a5a((int)param_1,pDVar2[0x14]);
    puVar7 = (undefined4 *)(uVar3 + 8);
    pcVar6 = (code *)*puVar7;
  }
  if (pcVar6 == (code *)0x1) {
    if (bVar1) {
      FUN_004bf801(1);
      return 0;
    }
    return 0;
  }
  if (pcVar6 == (code *)0x0) {
    if (bVar1) {
      FUN_004bf801(1);
    }
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  if (((param_1 == (DWORD *)0x8) || (param_1 == (DWORD *)0xb)) || (param_1 == (DWORD *)0x4)) {
    local_c = pDVar2[0x15];
    pDVar2[0x15] = 0;
    if (param_1 == (DWORD *)0x8) {
      local_10 = pDVar2[0x16];
      pDVar2[0x16] = 0x8c;
      goto LAB_004c79d2;
    }
  }
  else {
LAB_004c79d2:
    if (param_1 == (DWORD *)0x8) {
      if (DAT_004e38b8 < DAT_004e38bc + DAT_004e38b8) {
        iVar4 = DAT_004e38b8 * 0xc;
        iVar5 = DAT_004e38b8;
        do {
          iVar4 = iVar4 + 0xc;
          *(undefined4 *)((pDVar2[0x14] - 4) + iVar4) = 0;
          iVar5 = iVar5 + 1;
        } while (iVar5 < DAT_004e38bc + DAT_004e38b8);
      }
      goto LAB_004c7a10;
    }
  }
  *puVar7 = 0;
LAB_004c7a10:
  if (bVar1) {
    FUN_004bf801(1);
  }
  if (param_1 == (DWORD *)0x8) {
    (*pcVar6)(8,pDVar2[0x16]);
  }
  else {
    (*pcVar6)(param_1);
    if ((param_1 != (DWORD *)0xb) && (param_1 != (DWORD *)0x4)) {
      return 0;
    }
  }
  pDVar2[0x15] = local_c;
  if (param_1 == (DWORD *)0x8) {
    pDVar2[0x16] = local_10;
  }
  return 0;
}


/* 004c7a5a size=61 */

uint __cdecl FUN_004c7a5a(int param_1,uint param_2)

{
  int *piVar1;
  uint uVar3;
  uint uVar2;
  
  uVar2 = param_2;
  if (*(int *)(param_2 + 4) != param_1) {
    uVar3 = param_2;
    do {
      uVar2 = uVar3 + 0xc;
      if (param_2 + DAT_004e38c4 * 0xc <= uVar2) break;
      piVar1 = (int *)(uVar3 + 0x10);
      uVar3 = uVar2;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + DAT_004e38c4 * 0xc <= uVar2) || (*(int *)(uVar2 + 4) != param_1)) {
    uVar2 = 0;
  }
  return uVar2;
}


/* 004c7a97 size=33 */

undefined4 __cdecl FUN_004c7a97(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  uVar1 = param_1 + param_2;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    uVar2 = 1;
  }
  *param_3 = uVar1;
  return uVar2;
}


/* 004c7b16 size=46 */

void __cdecl FUN_004c7b16(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = uVar1 * 2;
  param_1[1] = uVar2 * 2 | uVar1 >> 0x1f;
  param_1[2] = param_1[2] << 1 | uVar2 >> 0x1f;
  return;
}


/* 004c7b44 size=45 */

void __cdecl FUN_004c7b44(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}


/* 004c7b71 size=199 */

void __cdecl FUN_004c7b71(char *param_1,int param_2,uint *param_3)

{
  uint *puVar1;
  uint local_14;
  uint local_10;
  uint local_c;
  int local_8;
  
  puVar1 = param_3;
  local_8 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    param_3 = (uint *)param_2;
    do {
      local_14 = *puVar1;
      local_10 = puVar1[1];
      local_c = puVar1[2];
      FUN_004c7b16(puVar1);
      FUN_004c7b16(puVar1);
      ___add_12(puVar1,&local_14);
      FUN_004c7b16(puVar1);
      local_10 = 0;
      local_c = 0;
      local_14 = (uint)*param_1;
      ___add_12(puVar1,&local_14);
      param_1 = param_1 + 1;
      param_3 = (uint *)((int)param_3 + -1);
    } while (param_3 != (uint *)0x0);
  }
  while (puVar1[2] == 0) {
    puVar1[2] = puVar1[1] >> 0x10;
    local_8 = local_8 + 0xfff0;
    puVar1[1] = *puVar1 >> 0x10 | puVar1[1] << 0x10;
    *puVar1 = *puVar1 << 0x10;
  }
  while ((puVar1[2] & 0x8000) == 0) {
    FUN_004c7b16(puVar1);
    local_8 = local_8 + 0xffff;
  }
  *(undefined2 *)((int)puVar1 + 10) = (undefined2)local_8;
  return;
}


/* 004c7c38 size=659 */

undefined4 __cdecl
FUN_004c7c38(uint param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

{
  short *psVar1;
  uint uVar2;
  short *psVar3;
  char cVar4;
  uint uVar5;
  short *psVar6;
  short *psVar7;
  short sVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined2 local_14;
  undefined4 local_12;
  undefined4 local_e;
  undefined1 local_a;
  char cStack_9;
  undefined4 local_8;
  
  psVar3 = param_6;
  uVar5 = param_3 & 0x7fff;
  local_20 = 0xcc;
  local_1f = 0xcc;
  local_1e = 0xcc;
  local_1d = 0xcc;
  local_1c = 0xcc;
  local_1b = 0xcc;
  local_1a = 0xcc;
  local_19 = 0xcc;
  local_18 = 0xcc;
  local_17 = 0xcc;
  local_16 = 0xfb;
  local_15 = 0x3f;
  local_8 = 1;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar5 == 0) && (param_2 == 0)) && (param_1 == 0)) {
LAB_004c7caf:
    *psVar3 = 0;
    *(undefined1 *)(psVar3 + 1) = 0x20;
    *(undefined1 *)((int)psVar3 + 3) = 1;
    *(undefined1 *)(psVar3 + 2) = 0x30;
  }
  else {
    if ((short)uVar5 == 0x7fff) {
      *param_6 = 1;
      if (((param_2 == 0x80000000) && (param_1 == 0)) || ((param_2 & 0x40000000) != 0)) {
        if (((param_3 & 0x8000) == 0) || (param_2 != 0xc0000000)) {
          if ((param_2 != 0x80000000) || (param_1 != 0)) goto LAB_004c7d2d;
          pcVar11 = "1#INF";
        }
        else {
          if (param_1 != 0) {
LAB_004c7d2d:
            pcVar11 = "1#QNAN";
            goto LAB_004c7d32;
          }
          pcVar11 = "1#IND";
        }
        FUN_004c17f0((uint *)(param_6 + 2),(uint *)pcVar11);
        *(undefined1 *)((int)psVar3 + 3) = 5;
      }
      else {
        pcVar11 = "1#SNAN";
LAB_004c7d32:
        FUN_004c17f0((uint *)(param_6 + 2),(uint *)pcVar11);
        *(undefined1 *)((int)psVar3 + 3) = 6;
      }
      local_8 = 0;
      goto LAB_004c7e9e;
    }
    local_14 = 0;
    local_a = (undefined1)uVar5;
    cStack_9 = (char)(uVar5 >> 8);
    sVar8 = (short)(((uVar5 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar5 * 0x4d10 >>
                   0x10);
    local_e = param_2;
    local_12 = param_1;
    FUN_004c8210((int *)&local_14,-(int)sVar8,1);
    if (0x3ffe < CONCAT11(cStack_9,local_a)) {
      sVar8 = sVar8 + 1;
      FUN_004c7ff0((int *)&local_14,(int *)&local_20);
    }
    *psVar3 = sVar8;
    if ((param_5 & 1) == 0) {
      iVar10 = param_4;
    }
    else {
      iVar10 = param_4 + sVar8;
      if (param_4 + sVar8 < 1) goto LAB_004c7caf;
    }
    if (0x15 < iVar10) {
      iVar10 = 0x15;
    }
    iVar9 = CONCAT11(cStack_9,local_a) - 0x3ffe;
    local_a = 0;
    cStack_9 = '\0';
    param_6 = (short *)0x8;
    do {
      FUN_004c7b16((uint *)&local_14);
      param_6 = (short *)((int)param_6 + -1);
    } while (param_6 != (short *)0x0);
    if (iVar9 < 0) {
      param_6 = (short *)0x0;
      for (uVar5 = -iVar9 & 0xff; uVar5 != 0; uVar5 = uVar5 - 1) {
        FUN_004c7b44((uint *)&local_14);
      }
    }
    param_4 = iVar10 + 1;
    psVar6 = psVar3 + 2;
    if (0 < param_4) {
      param_6 = psVar6;
      uVar5 = local_12;
      uVar2 = local_e;
      do {
        (*(uint16_t*)((char*)&local_e+2)) = (undefined2)(uVar2 >> 0x10);
        (*(uint16_t*)((char*)&local_e+0)) = (undefined2)uVar2;
        (*(uint16_t*)((char*)&local_12+2)) = (undefined2)(uVar5 >> 0x10);
        (*(uint16_t*)((char*)&local_12+0)) = (undefined2)uVar5;
        param_1 = CONCAT22((undefined2)local_12,local_14);
        param_2 = CONCAT22((undefined2)local_e,(*(uint16_t*)((char*)&local_12+2)));
        param_3 = CONCAT13(cStack_9,CONCAT12(local_a,(*(uint16_t*)((char*)&local_e+2))));
        local_12 = uVar5;
        local_e = uVar2;
        FUN_004c7b16((uint *)&local_14);
        FUN_004c7b16((uint *)&local_14);
        ___add_12((uint *)&local_14,&param_1);
        FUN_004c7b16((uint *)&local_14);
        cVar4 = cStack_9;
        cStack_9 = '\0';
        psVar6 = (short *)((int)param_6 + 1);
        param_4 = param_4 + -1;
        *(char *)param_6 = cVar4 + '0';
        param_6 = psVar6;
        uVar5 = local_12;
        uVar2 = local_e;
      } while (param_4 != 0);
    }
    psVar7 = psVar6 + -1;
    psVar1 = psVar3 + 2;
    if ('4' < *(char *)((int)psVar6 + -1)) {
      for (; psVar1 <= psVar7; psVar7 = (short *)((int)psVar7 + -1)) {
        if ((char)*psVar7 != '9') {
          if (psVar1 <= psVar7) goto LAB_004c7e8a;
          break;
        }
        *(char *)psVar7 = '0';
      }
      psVar7 = (short *)((int)psVar7 + 1);
      *psVar3 = *psVar3 + 1;
LAB_004c7e8a:
      *(char *)psVar7 = (char)*psVar7 + '\x01';
LAB_004c7e8c:
      cVar4 = ((char)psVar7 - (char)psVar3) + -3;
      *(char *)((int)psVar3 + 3) = cVar4;
      *(undefined1 *)(cVar4 + 4 + (int)psVar3) = 0;
      goto LAB_004c7e9e;
    }
    for (; psVar1 <= psVar7; psVar7 = (short *)((int)psVar7 + -1)) {
      if ((char)*psVar7 != '0') {
        if (psVar1 <= psVar7) goto LAB_004c7e8c;
        break;
      }
    }
    *psVar3 = 0;
    *(undefined1 *)(psVar3 + 1) = 0x20;
    *(undefined1 *)((int)psVar3 + 3) = 1;
    *(char *)psVar1 = '0';
  }
  *(undefined1 *)((int)psVar3 + 5) = 0;
  local_8 = 1;
LAB_004c7e9e:
  return local_8;
}


/* 004c7ecb size=293 */

int __cdecl FUN_004c7ecb(uint param_1,int param_2)

{
  DWORD DVar1;
  DWORD DVar2;
  int iVar3;
  DWORD DVar4;
  int iVar5;
  DWORD *pDVar6;
  HANDLE hFile;
  BOOL BVar7;
  undefined1 unaff_BP;
  int iVar8;
  char local_1008 [4064];
  undefined4 uStackY_28;
  
  FUN_004ba7f0(unaff_BP);
  iVar8 = 0;
  DVar1 = FUN_004c072a(param_1,0,1);
  if ((DVar1 == 0xffffffff) || (DVar2 = FUN_004c072a(param_1,0,2), DVar2 == 0xffffffff)) {
    iVar8 = -1;
  }
  else {
    DVar2 = param_2 - DVar2;
    if ((int)DVar2 < 1) {
      if ((int)DVar2 < 0) {
        FUN_004c072a(param_1,param_2,0);
        hFile = (HANDLE)FUN_004c63f3(param_1);
        BVar7 = SetEndOfFile(hFile);
        iVar8 = (BVar7 != 0) - 1;
        if (iVar8 == -1) {
          pDVar6 = FUN_004c09cc();
          *pDVar6 = 0xd;
          DVar2 = GetLastError();
          pDVar6 = FUN_004c09d5();
          *pDVar6 = DVar2;
        }
      }
    }
    else {
      _memset(local_1008,0,0x1000);
      uStackY_28 = 0x4c7f38;
      iVar3 = FUN_004c8411(param_1,0x8000);
      do {
        DVar4 = 0x1000;
        if ((int)DVar2 < 0x1000) {
          DVar4 = DVar2;
        }
        iVar5 = FUN_004c1c45(param_1,local_1008,DVar4);
        if (iVar5 == -1) {
          pDVar6 = FUN_004c09d5();
          if (*pDVar6 == 5) {
            pDVar6 = FUN_004c09cc();
            *pDVar6 = 0xd;
          }
          iVar8 = -1;
          break;
        }
        DVar2 = DVar2 - iVar5;
      } while (0 < (int)DVar2);
      FUN_004c8411(param_1,iVar3);
    }
    FUN_004c072a(param_1,DVar1,0);
  }
  return iVar8;
}


/* 004c7ff0 size=544 */

void __cdecl FUN_004c7ff0(int *param_1,int *param_2)

{
  int *piVar1;
  short sVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  ushort uVar9;
  uint uVar10;
  ushort uVar11;
  byte local_28;
  undefined1 uStack_27;
  undefined2 uStack_26;
  short local_24;
  undefined2 uStack_22;
  undefined2 local_20;
  undefined1 uStack_1e;
  byte bStack_1d;
  int *local_1c;
  int local_18;
  int local_14;
  ushort *local_10;
  ushort *local_c;
  short *local_8;
  
  piVar5 = param_2;
  piVar4 = param_1;
  local_18 = 0;
  local_28 = 0;
  uStack_27 = 0;
  uStack_26 = 0;
  local_24 = 0;
  uStack_22 = 0;
  local_20 = 0;
  uStack_1e = 0;
  bStack_1d = 0;
  uVar7 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar10 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar11 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar6 = (ushort)uVar7;
  piVar1 = (int *)(uVar10 + uVar7);
  if (((uVar6 < 0x7fff) && (uVar9 = (ushort)uVar10, uVar9 < 0x7fff)) && ((ushort)piVar1 < 0xbffe)) {
    if ((ushort)piVar1 < 0x3fc0) {
LAB_004c8093:
      piVar4[2] = 0;
      piVar4[1] = 0;
      *piVar4 = 0;
      return;
    }
    if (((uVar6 != 0) || (piVar1 = (int *)((int)piVar1 + 1), (param_1[2] & 0x7fffffffU) != 0)) ||
       ((uVar6 = 0, param_1[1] != 0 || (*param_1 != 0)))) {
      param_1 = piVar1;
      if (((uVar9 == 0) && (param_1 = (int *)((int)param_1 + 1), (param_2[2] & 0x7fffffffU) == 0))
         && ((param_2[1] == 0 && (*param_2 == 0)))) goto LAB_004c8093;
      local_14 = 0;
      local_8 = &local_24;
      param_2 = (int *)0x5;
      do {
        if (0 < (int)param_2) {
          local_c = (ushort *)(local_14 * 2 + (int)piVar4);
          local_10 = (ushort *)(piVar5 + 2);
          local_1c = param_2;
          do {
            iVar8 = FUN_004c7a97(*(uint *)(local_8 + -2),(uint)*local_c * (uint)*local_10,
                                 (uint *)(local_8 + -2));
            if (iVar8 != 0) {
              *local_8 = *local_8 + 1;
            }
            local_c = local_c + 1;
            local_10 = local_10 + -1;
            local_1c = (int *)((int)local_1c + -1);
          } while (local_1c != (int *)0x0);
        }
        local_8 = local_8 + 1;
        local_14 = local_14 + 1;
        param_2 = (int *)((int)param_2 + -1);
      } while (0 < (int)param_2);
      param_1 = (int *)((int)param_1 + 0xc002);
      if ((short)(ushort)param_1 < 1) {
LAB_004c8147:
        (*(uint16_t*)((char*)&param_1+0)) = (ushort)param_1 - 1;
        if ((short)(ushort)param_1 < 0) {
          iVar8 = -(int)(short)(ushort)param_1;
          (*(uint16_t*)((char*)&param_1+0)) = (ushort)param_1 + (short)iVar8;
          do {
            if ((local_28 & 1) != 0) {
              local_18 = local_18 + 1;
            }
            FUN_004c7b44((uint *)&local_28);
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
          if (local_18 != 0) {
            local_28 = local_28 | 1;
          }
        }
      }
      else {
        do {
          if ((bStack_1d & 0x80) != 0) break;
          FUN_004c7b16((uint *)&local_28);
          param_1 = (int *)((int)param_1 + 0xffff);
        } while (0 < (short)(ushort)param_1);
        if ((short)(ushort)param_1 < 1) goto LAB_004c8147;
      }
      if ((0x8000 < CONCAT11(uStack_27,local_28)) ||
         (sVar2 = CONCAT11(bStack_1d,uStack_1e), iVar3 = CONCAT22(local_20,uStack_22),
         iVar8 = CONCAT22(local_24,uStack_26),
         (CONCAT22(uStack_26,CONCAT11(uStack_27,local_28)) & 0x1ffff) == 0x18000)) {
        if (CONCAT22(local_24,uStack_26) == -1) {
          iVar8 = 0;
          if (CONCAT22(local_20,uStack_22) == -1) {
            if (CONCAT11(bStack_1d,uStack_1e) == -1) {
              (*(uint16_t*)((char*)&param_1+0)) = (ushort)param_1 + 1;
              sVar2 = -0x8000;
              iVar3 = 0;
              iVar8 = 0;
            }
            else {
              sVar2 = CONCAT11(bStack_1d,uStack_1e) + 1;
              iVar3 = 0;
              iVar8 = 0;
            }
          }
          else {
            sVar2 = CONCAT11(bStack_1d,uStack_1e);
            iVar3 = CONCAT22(local_20,uStack_22) + 1;
          }
        }
        else {
          iVar8 = CONCAT22(local_24,uStack_26) + 1;
          sVar2 = CONCAT11(bStack_1d,uStack_1e);
          iVar3 = CONCAT22(local_20,uStack_22);
        }
      }
      local_24 = (short)((uint)iVar8 >> 0x10);
      uStack_26 = (undefined2)iVar8;
      local_20 = (undefined2)((uint)iVar3 >> 0x10);
      uStack_22 = (undefined2)iVar3;
      bStack_1d = (byte)((ushort)sVar2 >> 8);
      uStack_1e = (undefined1)sVar2;
      if (0x7ffe < (ushort)param_1) goto LAB_004c81f0;
      uVar6 = (ushort)param_1 | uVar11;
      *(undefined2 *)piVar4 = uStack_26;
      *(uint *)((int)piVar4 + 2) = CONCAT22(uStack_22,local_24);
      *(uint *)((int)piVar4 + 6) = CONCAT13(bStack_1d,CONCAT12(uStack_1e,local_20));
    }
    *(ushort *)((int)piVar4 + 10) = uVar6;
  }
  else {
LAB_004c81f0:
    piVar4[1] = 0;
    *piVar4 = 0;
    piVar4[2] = (-(uint)(uVar11 != 0) & 0x80000000) + 0x7fff8000;
  }
  return;
}


