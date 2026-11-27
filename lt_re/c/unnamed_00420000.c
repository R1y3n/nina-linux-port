/* lithtech.exe decompilation - unnamed_00420000 */
#include "ghidra_types.h"

/* 00420000 size=77 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00420000(void *this,float param_1)

{
  float fVar1;
  
  fVar1 = SQRT(*(float *)((int)this + 8) * *(float *)((int)this + 8) +
               *(float *)((int)this + 4) * *(float *)((int)this + 4) +
               *(float *)this * *(float *)this);
  if (fVar1 == _DAT_004cb524) {
    return;
  }
  fVar1 = param_1 / fVar1;
  *(float *)this = fVar1 * *(float *)this;
  *(float *)((int)this + 4) = fVar1 * *(float *)((int)this + 4);
  *(float *)((int)this + 8) = fVar1 * *(float *)((int)this + 8);
  return;
}


/* 00420080 size=21 */

void __cdecl FUN_00420080(undefined4 param_1,byte param_2)

{
  FUN_004200a0(param_1,param_2);
  return;
}


/* 004200a0 size=26 */

void __cdecl FUN_004200a0(undefined4 param_1,byte param_2)

{
  FUN_004200c0(param_1,param_2);
  return;
}


/* 004200c0 size=736 */

/* FUN_004200c0: lifted from original x86 -> lt_lifted.c */


/* 004203a0 size=81 */

int __cdecl FUN_004203a0(int param_1,char *param_2)

{
  char cVar1;
  int *piVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar3 = 0xffffffff;
  pcVar4 = param_2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  piVar2 = (int *)FUN_00434ec0(*(int **)(param_1 + 0x40),param_2,~uVar3);
  if (piVar2 == (int *)0x0) {
    piVar2 = FUN_00434d70(*(int **)(param_1 + 0x40),(undefined4 *)param_2,~uVar3);
    if (piVar2 == (int *)0x0) {
      return;
    }
  }
  FUN_00434fb0((int)piVar2,(uint *)0x0);
  return;
}


/* 00420400 size=162 */

undefined4 * __cdecl FUN_00420400(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  uint uVar5;
  char *pcVar6;
  undefined4 *puVar7;
  
  uVar5 = 0xffffffff;
  pcVar6 = param_2;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  iVar2 = FUN_00434ec0(*(int **)(param_1 + 0x3c),param_2,~uVar5);
  if (iVar2 != 0) {
    puVar3 = (undefined4 *)FUN_00434fd0(iVar2);
    return puVar3;
  }
  puVar3 = (undefined4 *)(**(code **)(param_1 + 0x28))(0x24);
  if (puVar3 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  puVar7 = puVar3;
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  piVar4 = FUN_00434d70(*(int **)(param_1 + 0x3c),(undefined4 *)param_2,~uVar5);
  if (piVar4 == (int *)0x0) {
    (**(code **)(param_1 + 0x2c))(puVar3);
    return (undefined4 *)0x0;
  }
  iVar2 = FUN_00434fb0((int)piVar4,(uint *)0x0);
  puVar3[4] = iVar2;
  puVar3[7] = piVar4;
  FUN_00434fe0((int)piVar4,puVar3);
  return puVar3;
}


/* 004204b0 size=84 */

void __cdecl FUN_004204b0(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  longlong lVar3;
  
  puVar2 = FUN_00420510(param_1,*(int *)(param_2 + 0x10));
  if (puVar2 != (undefined4 *)0x0) {
    if ((int *)puVar2[3] != (int *)0x0) {
      *(int *)puVar2[3] = param_2;
    }
    if ((undefined4 *)puVar2[1] != (undefined4 *)0x0) {
      *(undefined4 *)puVar2[1] = *(undefined4 *)(param_2 + 0x18);
    }
    puVar1 = (undefined4 *)puVar2[2];
    if (puVar1 != (undefined4 *)0x0) {
      lVar3 = __ftol();
      *puVar1 = (int)lVar3;
    }
    if ((undefined4 *)puVar2[4] != (undefined4 *)0x0) {
      *(undefined4 *)puVar2[4] = *(undefined4 *)(param_2 + 0x14);
    }
  }
  return;
}


/* 00420510 size=123 */

undefined4 * __cdecl FUN_00420510(int param_1,int param_2)

{
  char cVar1;
  char cVar2;
  char cVar3;
  undefined4 *puVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  
  iVar5 = 0;
  if (0 < *(int *)(param_1 + 0xc)) {
    puVar4 = *(undefined4 **)(param_1 + 8);
    do {
      pcVar6 = (char *)*puVar4;
      iVar7 = param_2 - (int)pcVar6;
      while( true ) {
        cVar1 = *pcVar6;
        if ((cVar1 < 'a') || ('z' < cVar1)) {
          cVar3 = cVar1;
        }
        else {
          cVar3 = cVar1 + -0x20;
        }
        cVar2 = pcVar6[iVar7];
        if (('`' < cVar2) && (cVar2 < '{')) {
          cVar2 = cVar2 + -0x20;
        }
        if (cVar3 != cVar2) break;
        if (cVar1 == '\0') {
          return *(undefined4 **)(param_1 + 8) + iVar5 * 5;
        }
        pcVar6 = pcVar6 + 1;
      }
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 5;
    } while (iVar5 < *(int *)(param_1 + 0xc));
  }
  return (undefined4 *)0x0;
}


/* 00420590 size=159 */

void __cdecl FUN_00420590(int param_1,char *param_2,byte *param_3)

{
  undefined *puVar1;
  undefined4 *puVar2;
  undefined *puVar3;
  bool bVar4;
  float10 fVar5;
  
  puVar2 = (undefined4 *)FUN_00420880(param_1,param_2);
  bVar4 = puVar2 == (undefined4 *)0x0;
  if (bVar4) {
    puVar2 = FUN_00420400(param_1,param_2);
  }
  puVar3 = (undefined *)FUN_004203a0(param_1,(char *)param_3);
  puVar1 = (undefined *)puVar2[5];
  if (puVar3 != puVar1) {
    puVar2[5] = puVar3;
    fVar5 = FUN_004baed0(puVar1,param_3);
    puVar2[6] = (float)fVar5;
  }
  FUN_004204b0(param_1,(int)puVar2);
  if (puVar3 != puVar1 || bVar4) {
    if (bVar4) {
      if (*(code **)(param_1 + 0x30) != (code *)0x0) {
        (**(code **)(param_1 + 0x30))(param_1,puVar2);
        return;
      }
    }
    else if (*(code **)(param_1 + 0x34) != (code *)0x0) {
      (**(code **)(param_1 + 0x34))(param_1,puVar2);
    }
  }
  return;
}


/* 00420630 size=99 */

void __cdecl FUN_00420630(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  piVar1 = FUN_00434a60(500,1);
  *(int **)(param_1 + 0x40) = piVar1;
  piVar1 = FUN_00434a60(500,1);
  *(int **)(param_1 + 0x3c) = piVar1;
  iVar3 = param_1 + 0x18;
  iVar4 = 0;
  *(int *)(param_1 + 0x1c) = iVar3;
  *(int *)iVar3 = iVar3;
  if (0 < *(int *)(param_1 + 0x14)) {
    iVar3 = 0;
    do {
      puVar2 = (undefined4 *)(*(int *)(param_1 + 0x10) + iVar3);
      FUN_00420790(param_1,*puVar2,puVar2[1],puVar2[2]);
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0xc;
    } while (iVar4 < *(int *)(param_1 + 0x14));
  }
  return;
}


/* 004206a0 size=232 */

void __cdecl FUN_004206a0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  puVar7 = param_1;
  iVar6 = 0;
  if (0 < (int)param_1[3]) {
    iVar5 = 0;
    do {
      puVar3 = *(undefined4 **)(param_1[2] + 0x10 + iVar5);
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = 0;
      }
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0x14;
    } while (iVar6 < (int)param_1[3]);
  }
  puVar3 = (undefined4 *)param_1[7];
  if (puVar3 != (undefined4 *)0x0) {
    puVar1 = param_1 + 6;
    do {
      if (puVar3 == puVar1) break;
      piVar2 = puVar3 + 2;
      puVar3 = (undefined4 *)puVar3[1];
      FUN_004207e0((int)puVar7,*piVar2);
    } while (puVar3 != (undefined4 *)0x0);
  }
  param_1 = (undefined4 *)FUN_00434ff0(puVar7[0x10]);
  while (param_1 != (undefined4 *)0x0) {
    iVar6 = FUN_00435040((int *)&param_1);
    if (iVar6 != 0) {
      uVar4 = FUN_00434fd0(iVar6);
      (*(code *)puVar7[0xb])(uVar4);
    }
  }
  FUN_00434d00((int *)puVar7[0x10]);
  param_1 = (undefined4 *)FUN_00434ff0(puVar7[0xf]);
  while (param_1 != (undefined4 *)0x0) {
    iVar6 = FUN_00435040((int *)&param_1);
    if (iVar6 != 0) {
      uVar4 = FUN_00434fd0(iVar6);
      (*(code *)puVar7[0xb])(uVar4);
    }
  }
  FUN_00434d00((int *)puVar7[0xf]);
  for (iVar6 = 0x11; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  return;
}


/* 00420790 size=65 */

void __cdecl FUN_00420790(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(**(code **)(param_1 + 0x28))(0x18);
  if (puVar3 == (undefined4 *)0x0) {
    return;
  }
  puVar3[1] = param_3;
  puVar3[5] = param_4;
  *puVar3 = param_2;
  piVar1 = puVar3 + 2;
  puVar3[4] = puVar3;
  *piVar1 = param_1 + 0x18;
  piVar2 = *(int **)(param_1 + 0x1c);
  puVar3[3] = piVar2;
  *piVar2 = (int)piVar1;
  *(int **)(*piVar1 + 4) = piVar1;
  return;
}


/* 004207e0 size=42 */

void __cdecl FUN_004207e0(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(param_2 + 8);
  *(undefined4 *)(*(int *)(param_2 + 8) + 4) = *(undefined4 *)(param_2 + 0xc);
  **(undefined4 **)(param_2 + 0xc) = *puVar1;
  *(undefined4 **)(param_2 + 0xc) = puVar1;
  *puVar1 = puVar1;
  (**(code **)(param_1 + 0x2c))(param_2);
  return;
}


/* 00420810 size=99 */

undefined4 * __cdecl FUN_00420810(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char cVar3;
  char cVar4;
  char *pcVar5;
  int iVar6;
  
  iVar2 = *(int *)(param_1 + 0x1c);
  do {
    if (iVar2 == param_1 + 0x18) {
      return (undefined4 *)0x0;
    }
    pcVar5 = (char *)**(undefined4 **)(iVar2 + 8);
    iVar6 = param_2 - (int)pcVar5;
    while( true ) {
      cVar1 = *pcVar5;
      if ((cVar1 < 'a') || ('z' < cVar1)) {
        cVar4 = cVar1;
      }
      else {
        cVar4 = cVar1 + -0x20;
      }
      cVar3 = pcVar5[iVar6];
      if (('`' < cVar3) && (cVar3 < '{')) {
        cVar3 = cVar3 + -0x20;
      }
      if (cVar4 != cVar3) break;
      if (cVar1 == '\0') {
        return *(undefined4 **)(iVar2 + 8);
      }
      pcVar5 = pcVar5 + 1;
    }
    iVar2 = *(int *)(iVar2 + 4);
  } while( true );
}


/* 00420880 size=52 */

undefined4 __cdecl FUN_00420880(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  char *pcVar5;
  
  uVar4 = 0xffffffff;
  pcVar5 = param_2;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  iVar2 = FUN_00434ec0(*(int **)(param_1 + 0x3c),param_2,~uVar4);
  if (iVar2 == 0) {
    return 0;
  }
  uVar3 = FUN_00434fd0(iVar2);
  return uVar3;
}


/* 004208c0 size=147 */

undefined4 __cdecl FUN_004208c0(undefined4 param_1,LPCSTR param_2)

{
  FILE *pFVar1;
  char *pcVar2;
  char local_1f4 [500];
  
  pFVar1 = (FILE *)FUN_004ba1fd(param_2,&DAT_004d6ad8);
  if (pFVar1 == (FILE *)0x0) {
    return 0;
  }
  pcVar2 = FUN_004ba4e2(local_1f4,500,(undefined4 *)pFVar1);
  while (pcVar2 != (char *)0x0) {
    FUN_004200c0(param_1,(byte)local_1f4);
    pcVar2 = FUN_004ba4e2(local_1f4,500,(undefined4 *)pFVar1);
  }
  FUN_004ba14f(pFVar1);
  return 1;
}


/* 00420960 size=161 */

undefined4 __cdecl FUN_00420960(int *param_1,LPCSTR param_2)

{
  FILE *pFVar1;
  int iVar2;
  
  pFVar1 = (FILE *)FUN_004ba1fd(param_2,&DAT_004d6ae8);
  if (pFVar1 == (FILE *)0x0) {
    return 0;
  }
  param_2 = (LPCSTR)FUN_00434ff0(param_1[0xf]);
  while (param_2 != (LPCSTR)0x0) {
    iVar2 = FUN_00435040((int *)&param_2);
    if ((iVar2 != 0) && (iVar2 = FUN_00434fd0(iVar2), (*(byte *)(iVar2 + 0x20) & 1) != 0)) {
      FUN_004bafcd((int *)pFVar1,(byte *)s___s____s__004d6adc,*(undefined4 *)(iVar2 + 0x10));
    }
  }
  iVar2 = 0;
  param_2 = (LPCSTR)0x0;
  if (0 < param_1[1]) {
    do {
      (**(code **)(*param_1 + iVar2 * 4))(pFVar1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < param_1[1]);
  }
  FUN_004ba14f(pFVar1);
  return 1;
}


/* 00420a30 size=57 */

undefined4 __fastcall FUN_00420a30(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x104) == 0) {
    return 0;
  }
  iVar1 = FUN_00420b20(*(int *)(param_1 + 0x104),(int *)(param_1 + 0x104),param_1 + 0x108,param_1,
                       (int *)(param_1 + 0x100));
  if (iVar1 == 0) {
    *(int *)(param_1 + 0x104) = 0;
  }
  return 1;
}


/* 00420a70 size=168 */

undefined4 __thiscall FUN_00420a70(void *this,byte *param_1,int param_2,int param_3)

{
  byte bVar1;
  void *this_00;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  void *extraout_ECX;
  void *extraout_ECX_00;
  byte *pbVar5;
  bool bVar6;
  
  if (param_3 == 0) {
    param_3 = 1;
  }
  iVar2 = FUN_00420a30((int)this);
  this_00 = extraout_ECX;
  do {
    if (iVar2 == 0) {
      return 0;
    }
    if (param_3 <= *(int *)((int)this + 0x100)) {
      if (param_2 == 0) {
        uVar4 = FUN_004c4c00(this_00,*(byte **)this,param_1);
        bVar6 = uVar4 == 0;
      }
      else {
        pbVar3 = *(byte **)this;
        pbVar5 = param_1;
        do {
          bVar1 = *pbVar3;
          bVar6 = bVar1 < *pbVar5;
          if (bVar1 != *pbVar5) {
LAB_00420ad3:
            bVar6 = 1 - bVar6 == (uint)(bVar6 != 0);
            goto LAB_00420af4;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar6 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_00420ad3;
          pbVar3 = pbVar3 + 2;
          pbVar5 = pbVar5 + 2;
        } while (bVar1 != 0);
        bVar6 = true;
      }
LAB_00420af4:
      if (bVar6) {
        return 1;
      }
    }
    iVar2 = FUN_00420a30((int)this);
    this_00 = extraout_ECX_00;
  } while( true );
}


/* 00420b20 size=116 */

undefined4 __cdecl FUN_00420b20(int param_1,int *param_2,int param_3,int param_4,int *param_5)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  undefined3 extraout_var;
  int iVar5;
  int local_4;
  
  piVar3 = param_5;
  iVar2 = param_4;
  local_4 = param_1;
  param_1 = param_3;
  *param_5 = 0;
  do {
    while( true ) {
      iVar1 = param_1;
      bVar4 = FUN_00420ba0(&local_4,&param_1);
      iVar5 = CONCAT31(extraout_var,bVar4);
      if (iVar5 == 0) {
        return 0;
      }
      if (iVar5 == 1) break;
      if (iVar5 == 2) {
        *param_2 = local_4;
        return 1;
      }
    }
    *(int *)(iVar2 + *piVar3 * 4) = iVar1;
    iVar1 = *piVar3;
    *piVar3 = iVar1 + 1;
  } while (iVar1 + 1 < 0x1e);
  return 0;
}


/* 00420ba0 size=263 */

bool __cdecl FUN_00420ba0(int *param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  uint uVar5;
  char *extraout_ECX;
  char *extraout_ECX_00;
  
  cVar1 = *(char *)*param_1;
  while (cVar1 == ' ') {
    iVar2 = *param_1;
    *param_1 = iVar2 + 1;
    cVar1 = *(char *)(iVar2 + 1);
  }
  pcVar4 = (char *)*param_1;
  if (*pcVar4 == '\0') {
    return false;
  }
  pcVar3 = (char *)*param_2;
LAB_00420bcf:
  do {
    cVar1 = *(char *)*param_1;
    if (cVar1 == '\0') {
LAB_00420c51:
      *(undefined1 *)*param_2 = 0;
      *param_2 = *param_2 + 1;
      return *pcVar3 != '\0';
    }
    if (cVar1 != '%') {
      if ((cVar1 == ';') || (uVar5 = FUN_004bafa5(pcVar4,(int)cVar1), uVar5 != 0)) {
        *(undefined1 *)*param_2 = 0;
        *param_2 = *param_2 + 1;
        if (*pcVar3 == '\0') {
          *param_1 = *param_1 + 1;
          return true;
        }
        return true;
      }
      if (cVar1 == '(') {
        if ((char *)*param_2 == pcVar3) {
          *param_1 = *param_1 + 1;
          FUN_00420ce0(param_1,param_2,(int)pcVar3);
        }
        goto LAB_00420c51;
      }
      if (cVar1 == '\"') {
        if ((char *)*param_2 == pcVar3) {
          *param_1 = *param_1 + 1;
          FUN_00420d80(param_1,param_2,(int)pcVar3);
        }
        goto LAB_00420c51;
      }
      if (cVar1 == ' ') goto LAB_00420c51;
      FUN_00420cb0(param_2,(int)pcVar3,cVar1);
      *param_1 = *param_1 + 1;
      pcVar4 = extraout_ECX_00;
      goto LAB_00420bcf;
    }
    pcVar4 = (char *)*param_1 + 1;
    *param_1 = (int)pcVar4;
    cVar1 = *pcVar4;
    if (cVar1 == '\0') goto LAB_00420c51;
    FUN_00420cb0(param_2,(int)pcVar3,cVar1);
    *param_1 = *param_1 + 1;
    pcVar4 = extraout_ECX;
  } while( true );
}


/* 00420cb0 size=43 */

void __cdecl FUN_00420cb0(int *param_1,int param_2,undefined1 param_3)

{
  *(undefined1 *)*param_1 = param_3;
  if (0xff < *param_1 - param_2) {
    *(undefined1 *)*param_1 = 0;
    *param_1 = *param_1 + -1;
  }
  *param_1 = *param_1 + 1;
  return;
}


/* 00420ce0 size=160 */

undefined4 __cdecl FUN_00420ce0(undefined4 *param_1,int *param_2,int param_3)

{
  char *pcVar1;
  char cVar2;
  
  pcVar1 = (char *)*param_1;
  cVar2 = *pcVar1;
  do {
    if ((cVar2 == '\0') || (cVar2 == ')')) {
      if (*(char *)*param_1 != ')') {
        return 0;
      }
      *param_1 = (char *)*param_1 + 1;
      if (*param_2 == param_3) {
        FUN_00420cb0(param_2,param_3,0x20);
      }
      return 1;
    }
    if (cVar2 == '%') {
      *param_1 = pcVar1 + 1;
      FUN_00420cb0(param_2,param_3,0x25);
      pcVar1 = (char *)*param_1;
      cVar2 = *pcVar1;
      if (cVar2 != '\0') {
LAB_00420d18:
        *param_1 = pcVar1 + 1;
        FUN_00420cb0(param_2,param_3,cVar2);
      }
    }
    else {
      if (cVar2 != '(') goto LAB_00420d18;
      *param_1 = pcVar1 + 1;
      FUN_00420cb0(param_2,param_3,0x28);
      FUN_00420ce0(param_1,param_2,param_3);
      FUN_00420cb0(param_2,param_3,0x29);
    }
    pcVar1 = (char *)*param_1;
    cVar2 = *pcVar1;
  } while( true );
}


/* 00420d80 size=121 */

undefined4 __cdecl FUN_00420d80(undefined4 *param_1,int *param_2,int param_3)

{
  char *pcVar1;
  char cVar2;
  
  pcVar1 = (char *)*param_1;
  cVar2 = *pcVar1;
  do {
    if ((cVar2 == '\0') || (cVar2 == '\"')) {
      if (*(char *)*param_1 != '\"') {
        return 0;
      }
      *param_1 = (char *)*param_1 + 1;
      if (*param_2 == param_3) {
        FUN_00420cb0(param_2,param_3,0x20);
      }
      return 1;
    }
    if (cVar2 == '%') {
      *param_1 = pcVar1 + 1;
      FUN_00420cb0(param_2,param_3,0x25);
      pcVar1 = (char *)*param_1;
      cVar2 = *pcVar1;
      if (cVar2 != '\0') goto LAB_00420db8;
    }
    else {
LAB_00420db8:
      *param_1 = pcVar1 + 1;
      FUN_00420cb0(param_2,param_3,cVar2);
    }
    pcVar1 = (char *)*param_1;
    cVar2 = *pcVar1;
  } while( true );
}


/* 00420e00 size=16 */

void __cdecl FUN_00420e00(int param_1)

{
  FUN_00421ab0(&DAT_004e9110,param_1);
  return;
}


/* 00420e10 size=10 */

void FUN_00420e10(void)

{
  FUN_00421a90(&DAT_004e9110);
  return;
}


/* 00420e20 size=10 */

void FUN_00420e20(void)

{
  FUN_00422320(&DAT_004e9110);
  return;
}


/* 00420e30 size=28 */

void __cdecl FUN_00420e30(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_004219b0(&DAT_004e9110,param_1,param_2,param_3,0);
  return;
}


/* 00420e50 size=10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00420e50(undefined4 param_1)

{
  _DAT_004e94c0 = param_1;
  return;
}


/* 00420e60 size=26 */

void __cdecl FUN_00420e60(int param_1,int param_2,uint *param_3)

{
  FUN_00422790(&DAT_004e9110,param_1,param_2,param_3);
  return;
}


/* 00420e80 size=31 */

void __cdecl FUN_00420e80(int param_1,int param_2,byte *param_3,undefined4 param_4)

{
  FUN_004228f0(&DAT_004e9110,param_1,param_2,param_3,&param_4);
  return;
}


/* 00420ea0 size=28 */

void __cdecl FUN_00420ea0(byte *param_1,undefined4 param_2)

{
  FUN_004228f0(&DAT_004e9110,0xffffff,0,param_1,&param_2);
  return;
}


/* 00420ec0 size=16 */

void __cdecl FUN_00420ec0(UINT param_1)

{
  FUN_00422970(&DAT_004e9110,param_1);
  return;
}


/* 00420ee0 size=10 */

void FUN_00420ee0(void)

{
  FUN_00421870((undefined4 *)&DAT_004e9110);
  return;
}


/* 00420ef0 size=12 */

void FUN_00420ef0(void)

{
  FUN_004b9cf5(&LAB_00420f00);
  return;
}


/* 00420f20 size=11 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00420f20(void)

{
  _DAT_004e9108 = &PTR_LAB_004cbf20;
  return;
}


/* 00420f50 size=12 */

void FUN_00420f50(void)

{
  FUN_004b9cf5(&LAB_00420f60);
  return;
}


/* 00420f70 size=100 */

undefined4 __thiscall FUN_00420f70(void *this,byte *param_1)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  uint uVar5;
  byte *pbVar6;
  
  iVar2 = (*(code *)**(undefined4 **)this)();
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_1 != (byte *)0x0) && (*param_1 != 0)) {
    pcVar3 = (char *)(**(code **)(*(int *)this + 0x24))();
    if (pcVar3 == (char *)0x0) {
      return 0;
    }
    uVar5 = 0xffffffff;
    pbVar6 = param_1;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      bVar1 = *pbVar6;
      pbVar6 = pbVar6 + 1;
    } while (bVar1 != 0);
    iVar2 = FUN_004c8310(param_1,pcVar3,(void *)(~uVar5 - 1));
    if (iVar2 != 0) {
      uVar4 = (**(code **)(*(int *)this + 0x1c))(param_1);
      return uVar4;
    }
  }
  return 1;
}


/* 00420fe0 size=101 */

undefined4 __thiscall FUN_00420fe0(void *this,byte *param_1)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  uint uVar5;
  byte *pbVar6;
  
  iVar2 = (**(code **)(*(int *)this + 4))();
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_1 != (byte *)0x0) && (*param_1 != 0)) {
    pcVar3 = (char *)(**(code **)(*(int *)this + 0x24))();
    if (pcVar3 == (char *)0x0) {
      return 0;
    }
    uVar5 = 0xffffffff;
    pbVar6 = param_1;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      bVar1 = *pbVar6;
      pbVar6 = pbVar6 + 1;
    } while (bVar1 != 0);
    iVar2 = FUN_004c8310(param_1,pcVar3,(void *)(~uVar5 - 1));
    if (iVar2 != 0) {
      uVar4 = (**(code **)(*(int *)this + 0x20))(param_1);
      return uVar4;
    }
  }
  return 1;
}


/* 00421110 size=80 */

undefined4 * __fastcall FUN_00421110(undefined4 *param_1)

{
  param_1[0x46] = 0;
  param_1[0x47] = 0;
  param_1[0x48] = 0;
  param_1[0x49] = 0;
  param_1[0x43] = 0xb4b4ff;
  param_1[0x44] = 0x1e1e1e;
  param_1[0x45] = 0xffffff;
  *param_1 = 0;
  param_1[0x4a] = 500;
  FUN_00421160(param_1);
  return param_1;
}


/* 00421160 size=15 */

void __fastcall FUN_00421160(void *param_1)

{
  *(undefined1 *)((int)param_1 + 8) = 0;
  *(undefined4 *)((int)param_1 + 4) = 0;
  FUN_00421300(param_1,0);
  return;
}


/* 00421170 size=65 */

void __thiscall FUN_00421170(void *this,char *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  if (param_1 == (char *)0x0) {
    FUN_00421160(this);
    return;
  }
  _strncpy((char *)((int)this + 8),param_1,0x100);
  uVar2 = 0xffffffff;
  pcVar3 = (char *)((int)this + 8);
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  *(uint *)((int)this + 4) = ~uVar2 - 1;
  FUN_00421300(this,~uVar2 - 1);
  return;
}


/* 004211c0 size=74 */

void __thiscall FUN_004211c0(void *this,int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  iVar2 = *(int *)((int)this + 300) + param_1;
  if ((-1 < iVar2) && (iVar2 < *(int *)((int)this + 4))) {
    uVar3 = 0xffffffff;
    pcVar5 = (char *)(iVar2 + 9 + (int)this);
    do {
      pcVar6 = pcVar5;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar6 + -uVar3;
    pcVar6 = (char *)(iVar2 + 8 + (int)this);
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar6 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    }
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + -1;
  }
  return;
}


/* 00421210 size=125 */

void __thiscall FUN_00421210(void *this,int param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  bVar4 = param_1 < 0;
  iVar3 = 2;
  do {
    iVar2 = *(int *)((int)this + 300);
    while (((-1 < iVar2 + param_1 &&
            (iVar2 = *(int *)((int)this + 300) + param_1, iVar2 < *(int *)((int)this + 4))) &&
           (puVar1 = FUN_004bb020((uint *)s______004d6af4,*(char *)(iVar2 + 8 + (int)this)),
           (puVar1 == (uint *)0x0) != bVar4))) {
      FUN_004211c0(this,param_1);
      iVar2 = *(int *)((int)this + 300) + param_1;
      *(int *)((int)this + 300) = iVar2;
    }
    bVar4 = bVar4 == false;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


/* 00421290 size=101 */

void __thiscall FUN_00421290(void *this,undefined1 param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)((int)this + 300) < 0xff) {
    iVar1 = *(int *)((int)this + 4);
    if (0xfe < iVar1) {
      *(int *)((int)this + 4) = iVar1 + -1;
      *(undefined1 *)(iVar1 + 7 + (int)this) = 0;
    }
    iVar1 = *(int *)((int)this + 300);
    iVar2 = *(int *)((int)this + 4);
    if (iVar1 < iVar2) {
      FUN_004bab10((undefined4 *)(iVar1 + 9 + (int)this),(undefined4 *)(iVar1 + 8 + (int)this),
                   (iVar2 - iVar1) + 1);
    }
    else {
      *(undefined1 *)(iVar2 + 9 + (int)this) = 0;
    }
    *(undefined1 *)((int)this + *(int *)((int)this + 300) + 8) = param_1;
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  }
  return;
}


/* 00421300 size=53 */

void __thiscall FUN_00421300(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)((int)this + 300) + param_1;
  iVar1 = *(int *)((int)this + 4);
  iVar3 = iVar2;
  if (iVar1 <= iVar2) {
    iVar3 = iVar1;
  }
  if (iVar3 < 1) {
    iVar2 = 0;
  }
  else if (iVar1 <= iVar2) {
    *(int *)((int)this + 300) = iVar1;
    return;
  }
  *(int *)((int)this + 300) = iVar2;
  return;
}


/* 00421340 size=188 */

void __thiscall FUN_00421340(void *this,int param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  bVar4 = param_1 < 0;
  iVar3 = 2;
  do {
    iVar2 = *(int *)((int)this + 300);
    while (((-1 < iVar2 + param_1 &&
            (iVar2 = *(int *)((int)this + 300) + param_1, iVar2 <= *(int *)((int)this + 4))) &&
           (puVar1 = FUN_004bb020((uint *)s______004d6af4,*(char *)(iVar2 + 8 + (int)this)),
           (puVar1 == (uint *)0x0) != bVar4))) {
      iVar2 = *(int *)((int)this + 300) + param_1;
      *(int *)((int)this + 300) = iVar2;
    }
    bVar4 = bVar4 == false;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (-1 < *(int *)((int)this + 300) + param_1) {
    while (*(int *)((int)this + 300) + param_1 <= *(int *)((int)this + 4)) {
      puVar1 = FUN_004bb020((uint *)s______004d6af4,
                            *(char *)(*(int *)((int)this + 300) + 8 + (int)this));
      if (puVar1 == (uint *)0x0) {
        return;
      }
      iVar3 = *(int *)((int)this + 300) + param_1;
      *(int *)((int)this + 300) = iVar3;
      if (iVar3 + param_1 < 0) {
        return;
      }
    }
  }
  return;
}


/* 00421400 size=97 */

uint FUN_00421400(UINT param_1)

{
  BOOL BVar1;
  uint uVar2;
  byte local_102;
  byte local_101;
  BYTE local_100 [256];
  
  BVar1 = GetKeyboardState(local_100);
  uVar2 = 0;
  if (BVar1 != 0) {
    uVar2 = ToAscii(param_1,0,local_100,(LPWORD)&local_102,0);
    if (uVar2 != 0) {
      if (uVar2 == 1) {
        return (uint)local_102;
      }
      uVar2 = uVar2 - 2;
      if (uVar2 == 0) {
        return (uint)local_101;
      }
    }
  }
  return uVar2 & 0xffffff00;
}


/* 00421470 size=286 */

void __thiscall FUN_00421470(void *this,UINT param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  
  switch(param_1) {
  case 8:
    uVar1 = GetAsyncKeyState(0x11);
    if ((uVar1 & 0x8000) == 0) {
      FUN_004211c0(this,-1);
      FUN_00421300(this,-1);
      return;
    }
    FUN_00421210(this,-1);
    return;
  default:
    uVar2 = FUN_00421400(param_1);
    if ((char)uVar2 == '\0') {
      return;
    }
    FUN_00421290(this,(char)uVar2);
    iVar3 = 1;
    break;
  case 0x1b:
    FUN_00421160(this);
    return;
  case 0x23:
    uVar1 = GetAsyncKeyState(0x11);
    if ((uVar1 & 0x8000) == 0) {
      FUN_00421300(this,*(int *)((int)this + 4));
      return;
    }
    FUN_00421290(this,0);
    return;
  case 0x24:
    FUN_00421300(this,-*(int *)((int)this + 300));
    return;
  case 0x25:
    uVar1 = GetAsyncKeyState(0x11);
    iVar3 = -1;
    if ((uVar1 & 0x8000) != 0) {
      FUN_00421340(this,-1);
      return;
    }
    break;
  case 0x27:
    uVar1 = GetAsyncKeyState(0x11);
    iVar3 = 1;
    if ((uVar1 & 0x8000) != 0) {
      FUN_00421340(this,1);
      return;
    }
    break;
  case 0x2e:
    uVar1 = GetAsyncKeyState(0x11);
    if ((uVar1 & 0x8000) == 0) {
      FUN_004211c0(this,0);
      return;
    }
    FUN_00421210(this,0);
    return;
  }
  FUN_00421300(this,iVar3);
  return;
}


/* 004215e0 size=42 */

undefined4 * __thiscall FUN_004215e0(void *this,int param_1)

{
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined ***)this = &PTR_LAB_004cbf48;
  FUN_00421750(this,param_1);
  return this;
}


/* 00421610 size=30 */

undefined4 * __thiscall FUN_00421610(void *this,byte param_1)

{
  FUN_00421630(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00421630 size=24 */

void __fastcall FUN_00421630(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004cbf48;
  FUN_00421750(param_1,0);
  *param_1 = &PTR_LAB_004cbf20;
  return;
}


/* 004216e0 size=99 */

void __thiscall FUN_004216e0(void *this,char *param_1)

{
  int iVar1;
  
  if (*(int *)((int)this + 0xc) != 0) {
    _strncpy((char *)(*(int *)((int)this + 4) + 0xc + *(int *)((int)this + 0x14) * 0x10c),param_1,
             0x100);
    iVar1 = *(int *)((int)this + 0x14) + 1;
    *(int *)((int)this + 0x14) = iVar1;
    if (*(int *)((int)this + 0xc) <= iVar1) {
      *(undefined4 *)((int)this + 0x14) = 0;
    }
    if ((*(int *)((int)this + 0x10) == *(int *)((int)this + 0x14)) &&
       (iVar1 = *(int *)((int)this + 0x10) + 1, *(int *)((int)this + 0x10) = iVar1,
       *(int *)((int)this + 0xc) <= iVar1)) {
      *(undefined4 *)((int)this + 0x10) = 0;
    }
  }
  return;
}


/* 00421750 size=225 */

undefined4 __thiscall FUN_00421750(void *this,int param_1)

{
  int iVar1;
  char *_Source;
  int iVar2;
  char *_Dest;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  iVar4 = param_1;
  iVar2 = param_1 + 1;
  if (*(int *)((int)this + 0xc) == iVar2) {
    return 1;
  }
  bVar5 = param_1 != 0;
  param_1 = 0;
  iVar3 = iVar4;
  if (bVar5) {
    param_1 = FUN_00430de0(iVar2 * 0x10c);
    if (param_1 == 0) {
      return 0;
    }
    iVar1 = (**(code **)(*(int *)this + 4))();
    iVar3 = iVar2;
    if (iVar1 != 0) {
      _Source = (char *)(**(code **)(*(int *)this + 0x24))();
      if (_Source != (char *)0x0) {
        _Dest = (char *)(param_1 + 0xc + iVar4 * 0x10c);
        do {
          _strncpy(_Dest,_Source,0x100);
          iVar4 = iVar4 + -1;
          _Dest = _Dest + -0x10c;
          if ((iVar4 == 0) || (iVar2 = (**(code **)(*(int *)this + 0xc))(), iVar2 == 0)) break;
          _Source = (char *)(**(code **)(*(int *)this + 0x24))();
        } while (_Source != (char *)0x0);
      }
      *(undefined4 *)((int)this + 0x14) = 0;
      *(int *)((int)this + 0x10) = iVar4 + 1;
      goto LAB_0042180a;
    }
  }
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
LAB_0042180a:
  if (*(int *)((int)this + 0xc) != 0) {
    FUN_00430df0(*(undefined **)((int)this + 4));
  }
  *(int *)((int)this + 0xc) = iVar3;
  *(int *)((int)this + 4) = param_1;
  return 1;
}


/* 00421870 size=237 */

undefined4 * __fastcall FUN_00421870(undefined4 *param_1)

{
  FUN_00421110(param_1 + 4);
  FUN_0044df20((LPCRITICAL_SECTION)(param_1 + 0x94));
  param_1[0x9b] = 0;
  param_1[0x9c] = 0;
  param_1[0x9d] = 0;
  param_1[0x9e] = 0;
  param_1[0x9f] = 0;
  param_1[0xa0] = 0;
  param_1[0xa1] = 0;
  param_1[0xa2] = 0;
  param_1[0xa3] = 0;
  param_1[0xa4] = 0;
  param_1[0xa5] = 0;
  param_1[0xa6] = 0;
  param_1[0xee] = &PTR_LAB_004cbf70;
  param_1[0xef] = 0;
  param_1[0xf0] = 0;
  FUN_004215e0(param_1 + 0xf3,0);
  param_1[0xa7] = 0;
  param_1[0xed] = 0;
  param_1[0xf9] = 0;
  param_1[0x51] = 1;
  param_1[0x92] = 0;
  *(undefined2 *)(param_1 + 0xa8) = 1;
  param_1[0x9a] = 0;
  param_1[0xec] = 0;
  param_1[0xe9] = 0;
  param_1[0xeb] = 0;
  *param_1 = 1;
  param_1[1] = 0;
  param_1[0x93] = 0xffffff;
  param_1[0xea] = 0x3f800000;
  param_1[0xfa] = &DAT_004e9108;
  return param_1;
}


/* 00421960 size=70 */

void __fastcall FUN_00421960(undefined4 *param_1)

{
  FUN_00421ab0(param_1,1);
  *param_1 = 0;
  FUN_00421630(param_1 + 0xf3);
  param_1[0xee] = &PTR_LAB_004cbf70;
  param_1[0xf0] = 0;
  param_1[0xef] = 0;
  FUN_0044df40((LPCRITICAL_SECTION)(param_1 + 0x94));
  return;
}


/* 004219b0 size=212 */

undefined4 __thiscall
FUN_004219b0(void *this,undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_004366c0();
  if (*(int *)((int)this + 4) != 0) {
    FUN_00421ab0(this,0);
  }
  *(undefined4 *)((int)this + 4) = 1;
  iVar2 = FUN_00421b70((int)this);
  if (iVar2 == 0) {
    FUN_00421ab0(this,1);
    return 0;
  }
  *(undefined4 *)((int)this + 0x3b4) = uVar1;
  *(undefined4 *)((int)this + 0x27c) = *param_1;
  *(undefined4 *)((int)this + 0x280) = param_1[1];
  *(undefined4 *)((int)this + 0x284) = param_1[2];
  uVar1 = param_1[3];
  *(undefined4 *)((int)this + 0x3e4) = param_2;
  *(undefined4 *)((int)this + 0x288) = uVar1;
  *(undefined4 *)((int)this + 0x268) = param_3;
  *(undefined4 *)((int)this + 0x3c8) = 0;
  if (*(int *)((int)this + 0x3bc) == 0) {
    FUN_00421ee0(this,200);
  }
  *(void **)((int)this + 0x10) = this;
  if ((*(int *)((int)this + 0x3d8) == 0) || (*(int *)((int)this + 0x3d8) == 1)) {
    FUN_00421750((void *)((int)this + 0x3cc),0x14);
  }
  if (param_4 != 0) {
    FUN_00422170(this,param_4);
  }
  FUN_00422030(this);
  return 1;
}


/* 00421a90 size=26 */

undefined4 __fastcall FUN_00421a90(void *param_1)

{
  if (*(int *)((int)param_1 + 0x3bc) == 0) {
    FUN_00421ee0(param_1,200);
  }
  return 1;
}


/* 00421ab0 size=130 */

void __thiscall FUN_00421ab0(void *this,int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined *puVar3;
  
  FUN_00421b40((int)this);
  if (param_1 != 0) {
    puVar3 = *(undefined **)((int)this + 0x3c0);
    while (puVar3 != (undefined *)0x0) {
      uVar1 = *(uint *)((int)this + 0x3c0);
      uVar2 = *(uint *)(puVar3 + 4);
      FUN_00430df0(puVar3);
      puVar3 = (undefined *)(uVar2 & -(uint)(uVar2 != uVar1));
    }
    *(undefined4 *)((int)this + 0x3c0) = 0;
    *(undefined4 *)((int)this + 0x3bc) = 0;
    FUN_00421750((void *)((int)this + 0x3cc),0);
  }
  FUN_00421eb0((int)this);
  FUN_004ad190((undefined4 *)((int)this + 0x10));
  *(undefined4 *)((int)this + 0x3b4) = 0;
  *(undefined4 *)((int)this + 0x3e4) = 0;
  *(undefined4 *)((int)this + 0x268) = 0;
  *(undefined4 *)((int)this + 4) = 0;
  return;
}


/* 00421b40 size=34 */

void __fastcall FUN_00421b40(int param_1)

{
  if (*(int **)(param_1 + 0x3a4) != (int *)0x0) {
    winclientde_impl_40cd70(*(int **)(param_1 + 0x3a4));
    *(undefined4 *)(param_1 + 0x3a4) = 0;
  }
  return;
}


/* 00421b70 size=830 */

undefined4 __fastcall FUN_00421b70(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  HRSRC hResInfo;
  HGLOBAL hResData;
  LPVOID pvVar3;
  int *piVar4;
  DWORD DVar5;
  HDC hDC;
  char *pcVar6;
  void *this;
  uint uVar7;
  uint uVar8;
  int unaff_EBP;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *puVar12;
  uint uVar13;
  undefined4 uVar14;
  uint uVar15;
  int iVar16;
  uint *local_474;
  int iStack_470;
  int *piStack_46c;
  undefined1 auStack_464 [4];
  int *local_460;
  undefined4 local_458 [267];
  uint uStack_2c;
  uint uStack_28;
  int iStack_24;
  undefined **ppuStack_20;
  int iStack_1c;
  undefined **local_14;
  int local_10;
  
  FUN_00447930(local_458);
  iVar2 = FUN_004b7770();
  if (iVar2 != 0) {
    uVar9 = 0x8c;
    iVar2 = FUN_00420880(0x4e9500,s_ConsoleFont_004d6b04);
    if (iVar2 != 0) {
      uVar9 = FUN_004bb167(this,*(byte **)(iVar2 + 0x14));
    }
    hResInfo = FindResourceA((HMODULE)0x0,(LPCSTR)(uVar9 & 0xffff),s__12345_004d6afc);
    if ((((hResInfo != (HRSRC)0x0) ||
         (hResInfo = FindResourceA((HMODULE)0x0,(LPCSTR)0x8c,s__12345_004d6afc),
         hResInfo != (HRSRC)0x0)) &&
        (hResData = LoadResource((HMODULE)0x0,hResInfo), hResData != (HGLOBAL)0x0)) &&
       ((pvVar3 = LockResource(hResData), pvVar3 != (LPVOID)0x0 &&
        (piVar4 = FUN_0049b000(0x100), local_460 = (int *)0x0, piVar4 != (int *)0x0)))) {
      local_460 = piVar4;
      DVar5 = SizeofResource((HMODULE)0x0,hResInfo);
      (**(code **)(*piVar4 + 0x24))(pvVar3,DVar5);
      (**(code **)(*piVar4 + 0x14))(0);
      uVar14 = 0;
      iVar2 = FUN_00447a10(piVar4,(int)auStack_464);
      if ((iVar2 != 0) &&
         ((local_460 == (int *)0x0 && (hDC = GetDC(*(HWND *)(param_1 + 0x3b4)), hDC != (HDC)0x0))))
      {
        uVar10 = uStack_28 >> 4;
        uVar9 = uStack_2c >> 4;
        iVar2 = FUN_00430de0(uVar10 << 10);
        *(int *)(unaff_EBP + 0x29c) = iVar2;
        if (iVar2 != 0) {
          *(short *)(unaff_EBP + 0x2a2) = (short)uVar10;
          uVar1 = (undefined2)uVar9;
          *(short *)(unaff_EBP + 0x2a0) = (short)uVar10;
          puVar12 = (undefined4 *)(unaff_EBP + 0x2a4);
          for (iVar2 = 0x3f; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar12 = CONCAT22(uVar1,uVar1);
            puVar12 = puVar12 + 1;
          }
          *(undefined2 *)puVar12 = uVar1;
          uVar15 = 0;
          do {
            iVar2 = iStack_24 * uVar15 * uVar10 + iStack_1c;
            iStack_470 = uVar15 << 4;
            iVar16 = 0x10;
            do {
              local_474 = (uint *)(*(int *)(unaff_EBP + 0x29c) +
                                  (uint)*(ushort *)(unaff_EBP + 0x2a2) * iStack_470 * 4);
              uVar8 = 0;
              if (uVar10 != 0) {
                do {
                  uVar11 = 0;
                  pcVar6 = (char *)(uVar8 * iStack_24 + iVar2);
                  uVar7 = 1;
                  if (uVar9 != 0) {
                    uVar13 = uVar9;
                    do {
                      if (*pcVar6 != '\0') {
                        uVar11 = uVar11 | uVar7;
                      }
                      uVar7 = uVar7 << 1;
                      pcVar6 = pcVar6 + 1;
                      uVar13 = uVar13 - 1;
                    } while (uVar13 != 0);
                  }
                  *local_474 = uVar11;
                  local_474 = local_474 + 1;
                  uVar8 = uVar8 + 1;
                } while (uVar8 < uVar10);
              }
              iVar2 = iVar2 + uVar9;
              iStack_470 = iStack_470 + 1;
              iVar16 = iVar16 + -1;
            } while (iVar16 != 0);
            uVar15 = uVar15 + 1;
          } while (uVar15 < 0x10);
          uVar14 = 1;
          piVar4 = piStack_46c;
        }
        ReleaseDC(*(HWND *)(unaff_EBP + 0x3b4),hDC);
      }
      (**(code **)(*piVar4 + 4))();
      ppuStack_20 = &PTR_LAB_004cbb50;
      if (iStack_1c != 0) {
        FUN_00456e60(&DAT_004ecc58,iStack_1c);
      }
      return uVar14;
    }
  }
  if (local_10 != 0) {
    local_14 = &PTR_LAB_004cbb50;
    FUN_00433560(&local_14,&DAT_004ecc58);
  }
  return 0;
}


/* 00421eb0 size=34 */

void __fastcall FUN_00421eb0(int param_1)

{
  if (*(undefined **)(param_1 + 0x29c) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)(param_1 + 0x29c));
    *(undefined4 *)(param_1 + 0x29c) = 0;
  }
  return;
}


/* 00421ee0 size=254 */

undefined4 __thiscall FUN_00421ee0(void *this,uint param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  uVar1 = *(uint *)((int)this + 0x3bc);
  if (uVar1 == param_1) {
    return 1;
  }
  while (uVar1 < param_1) {
    piVar2 = (int *)FUN_00430de0(0x10c);
    piVar4 = piVar2;
    for (iVar3 = 0x43; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar4 = 0;
      piVar4 = piVar4 + 1;
    }
    piVar4 = *(int **)((int)this + 0x3c0);
    if (piVar4 == (int *)0x0) {
      piVar2[1] = (int)piVar2;
      *piVar2 = (int)piVar2;
      *(int **)((int)this + 0x3c0) = piVar2;
      *(int *)((int)this + 0x3bc) = *(int *)((int)this + 0x3bc) + 1;
    }
    else {
      *(int **)(*piVar4 + 4) = piVar2;
      *piVar2 = *piVar4;
      piVar2[1] = (int)piVar4;
      *piVar4 = (int)piVar2;
      *(int *)((int)this + 0x3bc) = *(int *)((int)this + 0x3bc) + 1;
      if (piVar2[1] == *(int *)((int)this + 0x3c0)) {
        *(int **)((int)this + 0x3c0) = piVar2;
      }
    }
    uVar1 = *(uint *)((int)this + 0x3bc);
  }
  uVar1 = *(uint *)((int)this + 0x3bc);
  while (param_1 < uVar1) {
    piVar4 = *(int **)((int)this + 0x3c0);
    *(int *)(*piVar4 + 4) = piVar4[1];
    *(int *)piVar4[1] = *piVar4;
    if (piVar4 == *(int **)((int)this + 0x3c0)) {
      *(int *)((int)this + 0x3c0) = (*(int **)((int)this + 0x3c0))[1];
    }
    iVar3 = *(int *)((int)this + 0x3bc) + -1;
    *(int *)((int)this + 0x3bc) = iVar3;
    if (iVar3 == 0) {
      *(undefined4 *)((int)this + 0x3c0) = 0;
    }
    FUN_00430df0((undefined *)piVar4);
    uVar1 = *(uint *)((int)this + 0x3bc);
  }
  return 1;
}


/* 00421fe0 size=75 */

void __fastcall FUN_00421fe0(void *param_1)

{
  uint *puVar1;
  
  winconsole_impl_422310((int)param_1);
  puVar1 = (uint *)((int)param_1 + 0x18);
  if (*(char *)((int)param_1 + 0x18) != '\0') {
    FUN_00422790(param_1,*(int *)((int)param_1 + 0x11c),0,puVar1);
    FUN_004216e0((void *)((int)param_1 + 0x3cc),(char *)puVar1);
    if (*(code **)((int)param_1 + 0x3e4) != (code *)0x0) {
      (**(code **)((int)param_1 + 0x3e4))(puVar1);
    }
    FUN_00421160((void *)((int)param_1 + 0x10));
  }
  return;
}


/* 00422030 size=123 */

void __fastcall FUN_00422030(void *param_1)

{
  uint uVar1;
  int iVar2;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_00422440(param_1,DAT_004d836c);
  uVar1 = DAT_004d8368;
  if ((int)DAT_004d8368 < 0xb) {
    uVar1 = 10;
  }
  FUN_00421ee0(param_1,uVar1);
  iVar2 = DAT_004d8364;
  if (DAT_004d8364 < 6) {
    iVar2 = 5;
  }
  FUN_00421750((void *)((int)param_1 + 0x3cc),iVar2);
  local_c = DAT_004d8374;
  local_10 = DAT_004d8370;
  local_8 = DAT_004d8378;
  local_4 = DAT_004d837c;
  FUN_00422500(param_1,&local_10);
  return;
}


/* 004220b0 size=190 */

void __thiscall FUN_004220b0(void *this,uint param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  if (param_1 != 0) {
    iVar3 = (param_1 ^ (int)param_1 >> 0x1f) - ((int)param_1 >> 0x1f);
    if (*(int *)((int)this + 0xc) != 2) {
      if ((int)param_1 < 1) {
        iVar1 = (**(code **)(*(int *)((int)this + 0x3cc) + 0x18))((int)this + 0x18);
      }
      else {
        iVar1 = (**(code **)(*(int *)((int)this + 0x3cc) + 0x14))();
      }
      if (iVar1 == 0) {
        return;
      }
      FUN_004222e0(this,2);
      iVar3 = iVar3 + -1;
    }
    iVar1 = 1;
    if (iVar3 != 0) {
      do {
        if (iVar1 == 0) goto LAB_00422134;
        if ((int)param_1 < 1) {
          iVar1 = (**(code **)(*(int *)((int)this + 0x3cc) + 0x20))((int)this + 0x148);
        }
        else {
          iVar1 = (**(code **)(*(int *)((int)this + 0x3cc) + 0x1c))();
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      if (iVar1 == 0) {
LAB_00422134:
        FUN_00421170((void *)((int)this + 0x10),(char *)((int)this + 0x148));
        winconsole_impl_422310((int)this);
        return;
      }
    }
    pcVar2 = (char *)(**(code **)(*(int *)((int)this + 0x3cc) + 0x24))();
    FUN_00421170((void *)((int)this + 0x10),pcVar2);
  }
  return;
}


/* 00422170 size=30 */

void __thiscall FUN_00422170(void *this,int param_1)

{
  if (param_1 == 0) {
    *(undefined **)((int)this + 1000) = &DAT_004e9108;
    return;
  }
  *(int *)((int)this + 1000) = param_1;
  return;
}


/* 00422190 size=98 */

void __fastcall FUN_00422190(void *param_1)

{
  int iVar1;
  char *pcVar2;
  
  if (*(int *)((int)param_1 + 0xc) == 1) {
    iVar1 = (**(code **)(**(int **)((int)param_1 + 1000) + 0x1c))((char *)((int)param_1 + 0x148));
    if (iVar1 == 0) {
      FUN_00421170((void *)((int)param_1 + 0x10),(char *)((int)param_1 + 0x148));
      winconsole_impl_422310((int)param_1);
      return;
    }
  }
  else {
    iVar1 = (**(code **)(**(int **)((int)param_1 + 1000) + 0x14))((int)param_1 + 0x18);
    if (iVar1 == 0) {
      return;
    }
    FUN_004222e0(param_1,1);
  }
  pcVar2 = (char *)(**(code **)(**(int **)((int)param_1 + 1000) + 0x24))();
  FUN_00421170((void *)((int)param_1 + 0x10),pcVar2);
  return;
}


/* 00422200 size=98 */

void __fastcall FUN_00422200(void *param_1)

{
  int iVar1;
  char *pcVar2;
  
  if (*(int *)((int)param_1 + 0xc) == 1) {
    iVar1 = (**(code **)(**(int **)((int)param_1 + 1000) + 0x20))((char *)((int)param_1 + 0x148));
    if (iVar1 == 0) {
      FUN_00421170((void *)((int)param_1 + 0x10),(char *)((int)param_1 + 0x148));
      winconsole_impl_422310((int)param_1);
      return;
    }
  }
  else {
    iVar1 = (**(code **)(**(int **)((int)param_1 + 1000) + 0x18))((int)param_1 + 0x18);
    if (iVar1 == 0) {
      return;
    }
    FUN_004222e0(param_1,1);
  }
  pcVar2 = (char *)(**(code **)(**(int **)((int)param_1 + 1000) + 0x24))();
  FUN_00421170((void *)((int)param_1 + 0x10),pcVar2);
  return;
}


/* 00422270 size=98 */

/* FUN_00422270: lifted from original x86 -> lt_lifted.c */


/* 004222e0 size=45 */

void __thiscall FUN_004222e0(void *this,int param_1)

{
  if (*(int *)((int)this + 0xc) != param_1) {
    _strncpy((char *)((int)this + 0x148),(char *)((int)this + 0x18),0x100);
    *(int *)((int)this + 0xc) = param_1;
  }
  return;
}


/* 00422320 size=279 */

bool __fastcall FUN_00422320(void *param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 local_458 [273];
  undefined **local_14;
  int local_10;
  
  FUN_00447930(local_458);
  FUN_00421b40((int)param_1);
  piVar1 = FUN_0049ade0(s_console_pcx_004d6b18,&DAT_004d57f4);
  if (piVar1 == (int *)0x0) {
    local_14 = &PTR_LAB_004cbb50;
    if (local_10 != 0) {
      FUN_00456e60(&DAT_004ecc58,local_10);
    }
    return true;
  }
  iVar2 = FUN_00447a10(piVar1,(int)local_458);
  if (iVar2 != 0) {
    piVar3 = FUN_0040cb20((int)local_458);
    *(int **)((int)param_1 + 0x3a4) = piVar3;
    uVar4 = (**(code **)(*(int *)(DAT_004e447c + 0x4c4) + 0x164))(piVar3,0);
    *(undefined4 *)((int)param_1 + 0x3ac) = uVar4;
    FUN_00422440(param_1,*(undefined4 *)((int)param_1 + 0x3a8));
  }
  (**(code **)(*piVar1 + 4))();
  local_14 = &PTR_LAB_004cbb50;
  if (local_10 != 0) {
    (**(code **)(DAT_004ecc58 + 8))(local_10);
  }
  return iVar2 == 0;
}


/* 00422440 size=99 */

void __thiscall FUN_00422440(void *this,undefined4 param_1)

{
  undefined4 uVar1;
  
  if (*(int *)((int)this + 0x3a4) != 0) {
    *(undefined4 *)((int)this + 0x3a8) = param_1;
    if (*(int *)((int)this + 0x3ac) != 0) {
      uVar1 = (**(code **)(*(int *)(DAT_004e447c + 0x4c4) + 0x164))(*(int *)((int)this + 0x3a4),0);
      *(undefined4 *)((int)this + 0x3ac) = uVar1;
    }
    (**(code **)(*(int *)(DAT_004e447c + 0x4c4) + 0x1d8))
              (*(undefined4 *)((int)this + 0x3a4),param_1);
  }
  return;
}


/* 004224b0 size=66 */

void __thiscall FUN_004224b0(void *this,int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_1 + *(int *)((int)this + 0x3c8);
  uVar1 = (*(int *)((int)this + 0x3bc) - *(int *)((int)this + 0x3c4)) + 1;
  if ((int)(((int)uVar2 < 1) - 1 & uVar2) < (int)uVar1) {
    uVar1 = ((int)uVar2 < 1) - 1 & uVar2;
  }
  *(uint *)((int)this + 0x3c8) = uVar1;
  return;
}


/* 00422500 size=259 */

void __thiscall FUN_00422500(void *this,int *param_1)

{
  int iVar1;
  int iVar2;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  int local_4;
  
  if ((((*(int *)((int)this + 0x26c) != *param_1) || (*(int *)((int)this + 0x270) != param_1[1])) ||
      (*(int *)((int)this + 0x274) != param_1[2])) || (*(int *)((int)this + 0x278) != param_1[3])) {
    *(int *)((int)this + 0x26c) = *param_1;
    *(int *)((int)this + 0x270) = param_1[1];
    *(int *)((int)this + 0x274) = param_1[2];
    *(int *)((int)this + 0x278) = param_1[3];
    local_10 = 0;
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    FUN_00422610(this,&local_10);
    local_20 = 0;
    iVar2 = (local_4 - local_c) / (int)(uint)*(ushort *)((int)this + 0x2a0);
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    iVar1 = iVar2 + -2;
    *(int *)((int)this + 0x3c4) = iVar1;
    FUN_00422610(this,&local_20);
    *(int *)((int)this + 0x128) = local_20 + 8;
    *(uint *)((int)this + 300) = (uint)*(ushort *)((int)this + 0x2a0) * iVar1 + 5 + local_1c;
    *(int *)((int)this + 0x130) = local_18 + -1;
    *(uint *)((int)this + 0x134) =
         (iVar2 + -1) * (uint)*(ushort *)((int)this + 0x2a0) + 1 + local_1c;
  }
  return;
}


/* 00422610 size=373 */

void __thiscall FUN_00422610(void *this,int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)((int)this + 0x268) == 0) {
    *param_1 = *(int *)((int)this + 0x26c);
    param_1[1] = *(int *)((int)this + 0x270);
    param_1[2] = *(int *)((int)this + 0x274);
    param_1[3] = *(int *)((int)this + 0x278);
    return;
  }
  iVar3 = *(int *)((int)this + 0x270);
  if (iVar3 == -1) {
    param_1[1] = 0;
  }
  else if (iVar3 < 0) {
    param_1[1] = -(*(int *)(*(int *)((int)this + 0x268) + 0x40) / iVar3);
  }
  else {
    param_1[1] = iVar3;
  }
  iVar3 = *(int *)((int)this + 0x26c);
  if (iVar3 == -1) {
    *param_1 = 0;
  }
  else if (iVar3 < 0) {
    *param_1 = -(*(int *)(*(int *)((int)this + 0x268) + 0x3c) / iVar3);
  }
  else {
    *param_1 = iVar3;
  }
  iVar3 = *(int *)((int)this + 0x274);
  if (iVar3 == -1) {
    param_1[2] = *(int *)(*(int *)((int)this + 0x268) + 0x3c);
  }
  else if (iVar3 < 0) {
    iVar2 = *(int *)(*(int *)((int)this + 0x268) + 0x3c);
    param_1[2] = iVar2 / iVar3 + iVar2;
  }
  else {
    param_1[2] = iVar3;
  }
  iVar3 = *(int *)((int)this + 0x278);
  if (iVar3 == -1) {
    param_1[3] = *(int *)(*(int *)((int)this + 0x268) + 0x40);
  }
  else if (iVar3 < 0) {
    iVar2 = *(int *)(*(int *)((int)this + 0x268) + 0x40);
    param_1[3] = iVar2 / iVar3 + iVar2;
  }
  else {
    param_1[3] = iVar3;
  }
  iVar3 = *(int *)(*(int *)((int)this + 0x268) + 0x3c);
  if (param_1[2] < iVar3) {
    iVar3 = param_1[2];
  }
  param_1[2] = iVar3;
  iVar2 = *(int *)(*(int *)((int)this + 0x268) + 0x40);
  if (param_1[3] < iVar2) {
    iVar2 = param_1[3];
  }
  param_1[3] = iVar2;
  if (iVar3 < 0xa1) {
    iVar3 = 0xa0;
  }
  param_1[2] = iVar3;
  iVar1 = (uint)*(ushort *)((int)this + 0x2a2) * 4;
  if (iVar1 < iVar2) {
    iVar1 = iVar2;
  }
  param_1[3] = iVar1;
  iVar2 = iVar3 + -0xa0;
  if (*param_1 < iVar3 + -0xa0) {
    iVar2 = *param_1;
  }
  *param_1 = iVar2;
  iVar1 = iVar1 + (uint)*(ushort *)((int)this + 0x2a2) * -4;
  if (param_1[1] < iVar1) {
    iVar1 = param_1[1];
  }
  param_1[1] = iVar1;
  return;
}


/* 00422790 size=338 */

void __thiscall FUN_00422790(void *this,int param_1,int param_2,uint *param_3)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  size_t _Count;
  
  if ((*(int *)this != 0) && (param_2 <= *(int *)((int)this + 0x144))) {
    FUN_0044df50((LPCRITICAL_SECTION)((int)this + 0x250));
    if (*(code **)((int)this + 0x3b0) != (code *)0x0) {
      (**(code **)((int)this + 0x3b0))(param_3);
    }
    if (DAT_004e98a8 != 0) {
      OutputDebugStringA((LPCSTR)param_3);
      OutputDebugStringA(&DAT_004d6b24);
    }
    puVar2 = *(uint **)((int)this + 0x3bc);
    while (puVar2 != (uint *)0x0) {
      puVar2 = FUN_004bb020(param_3,'\n');
      if ((puVar2 == (uint *)0x0) || (*(char *)((int)puVar2 + 1) == '\0')) {
        puVar2 = (uint *)0x0;
        _Count = 0xff;
      }
      else {
        _Count = (int)puVar2 - (int)param_3;
      }
      piVar1 = *(int **)((int)this + 0x3c0);
      *(int *)(*piVar1 + 4) = piVar1[1];
      *(int *)piVar1[1] = *piVar1;
      if (piVar1 == *(int **)((int)this + 0x3c0)) {
        *(int *)((int)this + 0x3c0) = (*(int **)((int)this + 0x3c0))[1];
      }
      iVar3 = *(int *)((int)this + 0x3bc) + -1;
      *(int *)((int)this + 0x3bc) = iVar3;
      if (iVar3 == 0) {
        *(undefined4 *)((int)this + 0x3c0) = 0;
      }
      piVar1[2] = param_1;
      _strncpy((char *)(piVar1 + 3),(char *)param_3,_Count);
      if (puVar2 != (uint *)0x0) {
        param_3 = (uint *)((int)puVar2 + 1);
        *(undefined1 *)((int)piVar1 + _Count + 0xc) = 0;
      }
      if (*(int **)((int)this + 0x3c0) == (int *)0x0) {
        piVar1[1] = (int)piVar1;
        *piVar1 = (int)piVar1;
        *(int **)((int)this + 0x3c0) = piVar1;
      }
      else {
        iVar3 = **(int **)((int)this + 0x3c0);
        **(int **)(iVar3 + 4) = (int)piVar1;
        piVar1[1] = *(int *)(iVar3 + 4);
        *piVar1 = iVar3;
        *(int **)(iVar3 + 4) = piVar1;
      }
      *(int *)((int)this + 0x3bc) = *(int *)((int)this + 0x3bc) + 1;
    }
    FUN_0044df60((LPCRITICAL_SECTION)((int)this + 0x250));
  }
  return;
}


/* 004228f0 size=91 */

void __thiscall FUN_004228f0(void *this,int param_1,int param_2,byte *param_3,undefined4 *param_4)

{
  uint local_1f4 [125];
  
  if (param_2 <= *(int *)((int)this + 0x144)) {
    FUN_004baabf((undefined1 *)local_1f4,499,param_3,param_4);
    FUN_00422790(this,param_1,param_2,local_1f4);
  }
  return;
}


/* 00422950 size=30 */

void __cdecl FUN_00422950(void *param_1,int param_2,int param_3,byte *param_4,undefined4 param_5)

{
  FUN_004228f0(param_1,param_2,param_3,param_4,&param_5);
  return;
}


/* 00422970 size=314 */

void __thiscall FUN_00422970(void *this,UINT param_1)

{
  ushort uVar1;
  
  switch(param_1) {
  case 9:
    break;
  default:
    winconsole_impl_422310((int)this);
    FUN_00421470((void *)((int)this + 0x10),param_1);
    return;
  case 0xd:
    FUN_00421fe0(this);
    return;
  case 0x21:
    uVar1 = GetAsyncKeyState(0x11);
    if ((uVar1 & 0x8000) == 0) {
      FUN_004224b0(this,*(int *)((int)this + 0x3c4));
      return;
    }
    FUN_004224b0(this,*(int *)((int)this + 0x3bc));
    return;
  case 0x22:
    uVar1 = GetAsyncKeyState(0x11);
    if ((uVar1 & 0x8000) == 0) {
      FUN_004224b0(this,-*(int *)((int)this + 0x3c4));
      return;
    }
    FUN_004224b0(this,-*(int *)((int)this + 0x3c8));
    return;
  case 0x26:
    uVar1 = GetAsyncKeyState(0x11);
    if ((uVar1 & 0x8000) == 0) {
      FUN_004220b0(this,0xffffffff);
      return;
    }
    FUN_004224b0(this,1);
    return;
  case 0x28:
    uVar1 = GetAsyncKeyState(0x11);
    if ((uVar1 & 0x8000) == 0) {
      FUN_004220b0(this,1);
      return;
    }
    FUN_004224b0(this,-1);
    return;
  }
  uVar1 = GetAsyncKeyState(0x11);
  if ((uVar1 & 0x8000) != 0) {
    FUN_00422270(this);
    return;
  }
  uVar1 = GetAsyncKeyState(0x11);
  if ((uVar1 & 0x8000) == 0) {
    FUN_00422190(this);
    return;
  }
  FUN_00422200(this);
  return;
}


/* 00422bb0 size=12 */

void FUN_00422bb0(void)

{
  FUN_004b9cf5(&LAB_00422bc0);
  return;
}


/* 00423ff0 size=135 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00423ff0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_004e9500;
  for (iVar1 = 0x11; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_004e9500 = &PTR_input_442680_004d6b28;
  DAT_004e9504 = 2;
  _DAT_004e9508 = FUN_00437680();
  _DAT_004e950c = FUN_00437690();
  DAT_004e9510 = &PTR_s_BlastServer_004d6b30;
  DAT_004e9514 = 0x24;
  _DAT_004e9524 = FUN_00420ea0;
  _DAT_004e9528 = FUN_00430de0;
  _DAT_004e952c = FUN_00430df0;
  FUN_00420630(0x4e9500);
  FUN_00422170(&DAT_004e9110,0x4e9548);
  return;
}


