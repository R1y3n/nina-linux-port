/* lithtech.exe decompilation - unnamed_004ac000 */
#include "ghidra_types.h"

/* 004ac050 size=328 */

int * __thiscall FUN_004ac050(void *this,undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 **ppuVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  undefined1 auStack_1a [2];
  undefined4 *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puVar1 = param_2;
  local_8 = 0xffffffff;
  puStack_c = &LAB_004c9d00;
  local_10 = ExceptionList;
  local_14 = auStack_1a + -0xe;
  if (param_1 != param_2) {
    puVar2 = (undefined4 *)(*(int *)((int)this + 4) - *(int *)this);
    puVar4 = (undefined4 *)((int)param_2 - (int)param_1);
    param_2 = puVar2;
    if ((puVar4 == (undefined4 *)0xffffffff) ||
       (ExceptionList = &local_10, (undefined4 *)(-(int)puVar4 - 2U) < puVar2)) {
      ExceptionList = &local_10;
      FUN_004a5b30(s_basic_string_004de5c8);
    }
    if ((*(int *)((int)this + 8) - *(int *)this) - 1U < (uint)((int)puVar4 + (int)param_2)) {
      local_18 = puVar4;
      ppuVar3 = &local_18;
      if (puVar4 <= param_2) {
        ppuVar3 = &param_2;
      }
      local_18 = (undefined4 *)((int)*ppuVar3 + 1 + (int)param_2);
      if (local_18 == (undefined4 *)0x0) {
        param_2 = (undefined4 *)0x0;
      }
      else {
        param_2 = (undefined4 *)FUN_004aa520((uint)local_18);
      }
      local_8 = 0;
      puVar2 = (undefined4 *)
               FUN_004aca90(*(undefined1 **)this,*(int *)((int)this + 4),(undefined1 *)param_2);
      FUN_004bab10(puVar2,param_1,(uint)puVar4);
      puVar5 = (undefined1 *)((int)puVar2 + ((int)puVar1 - (int)param_1));
      *puVar5 = 0;
      puVar1 = *(undefined4 **)this;
      if (puVar1 != (undefined4 *)0x0) {
        FUN_004aa6f0(puVar1,*(int *)((int)this + 8) - (int)puVar1);
      }
      *(undefined4 **)this = param_2;
      *(undefined1 **)((int)this + 4) = puVar5;
      *(int *)((int)this + 8) = (int)param_2 + (int)local_18;
    }
    else {
      FUN_004bab10((undefined4 *)(*(int *)((int)this + 4) + 1),(undefined4 *)((int)param_1 + 1),
                   (int)puVar1 - ((int)param_1 + 1));
      *(undefined1 *)(*(int *)((int)this + 4) + (int)puVar4) = 0;
      **(undefined1 **)((int)this + 4) = *(undefined1 *)param_1;
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + (int)puVar4;
    }
  }
  ExceptionList = local_10;
  return this;
}


/* 004ac1c0 size=289 */

undefined4 * __cdecl FUN_004ac1c0(uint param_1,uint *param_2)

{
  size_t sVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = DAT_004ec68c - (int)DAT_004ec690;
  uVar3 = *param_2 * param_1;
  puVar2 = DAT_004ec690;
  if (uVar4 < uVar3) {
    do {
      if (param_1 <= uVar4) {
        *param_2 = uVar4 / param_1;
        puVar2 = DAT_004ec690;
        DAT_004ec690 = (undefined4 *)((int)DAT_004ec690 + (uVar4 / param_1) * param_1);
        return puVar2;
      }
      sVar1 = ((DAT_004ec688 >> 4) + 7 & 0xfffffff8) + uVar3 * 2;
      if (uVar4 != 0) {
        *DAT_004ec690 = *(undefined4 *)(&DAT_004ec644 + (uVar4 - 1 >> 3) * 4);
        *(undefined4 **)(&DAT_004ec644 + (uVar4 - 1 >> 3) * 4) = DAT_004ec690;
      }
      DAT_004ec690 = (undefined4 *)FUN_00430de0(sVar1);
      uVar3 = param_1;
      if (DAT_004ec690 == (undefined4 *)0x0) {
        for (; uVar3 < 0x81; uVar3 = uVar3 + 8) {
          puVar2 = *(undefined4 **)(&DAT_004ec644 + (uVar3 - 1 >> 3) * 4);
          if (puVar2 != (undefined4 *)0x0) {
            *(undefined4 *)(&DAT_004ec644 + (uVar3 - 1 >> 3) * 4) = *puVar2;
            DAT_004ec68c = (int)puVar2 + uVar3;
            DAT_004ec690 = puVar2;
            goto LAB_004ac284;
          }
        }
        DAT_004ec68c = 0;
        DAT_004ec690 = (undefined4 *)FUN_00430de0(sVar1);
      }
      DAT_004ec68c = (int)DAT_004ec690 + sVar1;
      DAT_004ec688 = DAT_004ec688 + sVar1;
LAB_004ac284:
      uVar4 = DAT_004ec68c - (int)DAT_004ec690;
      uVar3 = *param_2 * param_1;
      puVar2 = DAT_004ec690;
    } while (uVar4 < uVar3);
  }
  DAT_004ec690 = (undefined4 *)((int)puVar2 + uVar3);
  return puVar2;
}


/* 004ac2f0 size=328 */

int * __thiscall FUN_004ac2f0(void *this,undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 **ppuVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  undefined1 auStack_1a [2];
  undefined4 *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puVar1 = param_2;
  local_8 = 0xffffffff;
  puStack_c = &LAB_004c9d10;
  local_10 = ExceptionList;
  local_14 = auStack_1a + -0xe;
  if (param_1 != param_2) {
    puVar2 = (undefined4 *)(*(int *)((int)this + 4) - *(int *)this);
    puVar4 = (undefined4 *)((int)param_2 - (int)param_1);
    param_2 = puVar2;
    if ((puVar4 == (undefined4 *)0xffffffff) ||
       (ExceptionList = &local_10, (undefined4 *)(-(int)puVar4 - 2U) < puVar2)) {
      ExceptionList = &local_10;
      FUN_004a5b30(s_basic_string_004de5c8);
    }
    if ((*(int *)((int)this + 8) - *(int *)this) - 1U < (uint)((int)puVar4 + (int)param_2)) {
      local_18 = puVar4;
      ppuVar3 = &local_18;
      if (puVar4 <= param_2) {
        ppuVar3 = &param_2;
      }
      local_18 = (undefined4 *)((int)*ppuVar3 + 1 + (int)param_2);
      if (local_18 == (undefined4 *)0x0) {
        param_2 = (undefined4 *)0x0;
      }
      else {
        param_2 = (undefined4 *)FUN_004aa520((uint)local_18);
      }
      local_8 = 0;
      puVar2 = (undefined4 *)
               FUN_004aca90(*(undefined1 **)this,*(int *)((int)this + 4),(undefined1 *)param_2);
      FUN_004bab10(puVar2,param_1,(uint)puVar4);
      puVar5 = (undefined1 *)((int)puVar2 + ((int)puVar1 - (int)param_1));
      *puVar5 = 0;
      puVar1 = *(undefined4 **)this;
      if (puVar1 != (undefined4 *)0x0) {
        FUN_004aa6f0(puVar1,*(int *)((int)this + 8) - (int)puVar1);
      }
      *(undefined4 **)this = param_2;
      *(undefined1 **)((int)this + 4) = puVar5;
      *(int *)((int)this + 8) = (int)param_2 + (int)local_18;
    }
    else {
      FUN_004bab10((undefined4 *)(*(int *)((int)this + 4) + 1),(undefined4 *)((int)param_1 + 1),
                   (int)puVar1 - ((int)param_1 + 1));
      *(undefined1 *)(*(int *)((int)this + 4) + (int)puVar4) = 0;
      **(undefined1 **)((int)this + 4) = *(undefined1 *)param_1;
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + (int)puVar4;
    }
  }
  ExceptionList = local_10;
  return this;
}


/* 004ac460 size=320 */

/* FUN_004ac460: lifted from original x86 -> lt_lifted.c */


/* 004ac5c0 size=320 */

/* FUN_004ac5c0: lifted from original x86 -> lt_lifted.c */


/* 004ac720 size=357 */

/* FUN_004ac720: lifted from original x86 -> lt_lifted.c */


/* 004ac8b0 size=347 */

/* FUN_004ac8b0: lifted from original x86 -> lt_lifted.c */


/* 004aca30 size=34 */

int __cdecl FUN_004aca30(int param_1,int param_2,undefined1 *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_2 - param_1;
  if (0 < iVar1) {
    iVar2 = param_1 - (int)param_3;
    do {
      *param_3 = param_3[iVar2];
      param_3 = param_3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}


/* 004aca60 size=38 */

int __cdecl FUN_004aca60(int param_1,int param_2,undefined2 *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_2 - param_1 >> 1;
  if (0 < iVar1) {
    iVar2 = param_1 - (int)param_3;
    do {
      *param_3 = *(undefined2 *)(iVar2 + (int)param_3);
      param_3 = param_3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}


/* 004aca90 size=37 */

undefined1 * __cdecl FUN_004aca90(undefined1 *param_1,int param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = param_2 - (int)param_1;
  if (iVar2 < 1) {
    return param_3;
  }
  do {
    uVar1 = *param_1;
    param_1 = param_1 + 1;
    *param_3 = uVar1;
    param_3 = param_3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return param_3;
}


/* 004acac0 size=45 */

undefined2 * __cdecl FUN_004acac0(undefined2 *param_1,int param_2,undefined2 *param_3)

{
  undefined2 uVar1;
  int iVar2;
  
  iVar2 = param_2 - (int)param_1 >> 1;
  if (iVar2 < 1) {
    return param_3;
  }
  do {
    uVar1 = *param_1;
    param_1 = param_1 + 1;
    *param_3 = uVar1;
    param_3 = param_3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return param_3;
}


/* 004acaf0 size=30 */

undefined4 * __thiscall FUN_004acaf0(void *this,byte param_1)

{
  FUN_004acbc0(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004acb10 size=163 */

undefined4 * __thiscall FUN_004acb10(void *this,undefined4 *param_1,uint param_2,char param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9d68;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)((int)this + 4) = 0;
  local_4 = 0;
  *(undefined ***)this = &PTR_FUN_004cdbd4;
  if (param_3 == '\0') {
    puVar1 = (undefined4 *)FUN_00430de0(param_2);
    *(undefined4 **)((int)this + 8) = puVar1;
    *(uint *)((int)this + 0xc) = param_2;
    if (param_2 != 0) {
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
      ExceptionList = local_c;
      return this;
    }
  }
  else {
    *(undefined4 **)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = param_2;
  }
  ExceptionList = local_c;
  return this;
}


/* 004acbc0 size=29 */

void __fastcall FUN_004acbc0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cdbd4;
  FUN_00430df0((undefined *)param_1[2]);
  *param_1 = &PTR_LAB_004cdb70;
  return;
}


/* 004acbe0 size=26 */

void * __thiscall FUN_004acbe0(void *this,undefined4 param_1,undefined4 param_2)

{
  FUN_004acc00(this,param_1,param_2);
  return this;
}


/* 004acc00 size=22 */

void __thiscall FUN_004acc00(void *this,undefined4 param_1,undefined4 param_2)

{
  *(undefined4 *)((int)this + 4) = param_1;
  *(undefined4 *)((int)this + 8) = param_2;
  FUN_004ad190(this);
  return;
}


/* 004acd30 size=30 */

exception * __thiscall FUN_004acd30(void *this,byte param_1)

{
  FUN_004acd50(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004acd50 size=155 */

void __fastcall FUN_004acd50(exception *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9dd3;
  local_c = ExceptionList;
  puVar1 = *(undefined4 **)(param_1 + 0xc);
  iVar2 = *(int *)(param_1 + 0x14);
  local_4 = 1;
  ExceptionList = &local_c;
  if (puVar1 != (undefined4 *)0x0) {
    if ((uint)(iVar2 - (int)puVar1) < 0x81) {
      ExceptionList = &local_c;
      FUN_004a94b0(&DAT_004ed050);
      *puVar1 = *(undefined4 *)(&DAT_004ec644 + ((iVar2 - (int)puVar1) - 1U >> 3) * 4);
      *(undefined4 **)(&DAT_004ec644 + ((iVar2 - (int)puVar1) - 1U >> 3) * 4) = puVar1;
      DAT_004ed050 = 0;
    }
    else {
      ExceptionList = &local_c;
      FUN_00430df0((undefined *)puVar1);
    }
  }
  local_4 = 0xffffffff;
  exception__dtor_exception(param_1);
  ExceptionList = local_c;
  return;
}


/* 004acdf0 size=301 */

undefined4 * __thiscall FUN_004acdf0(void *this,int param_1)

{
  undefined4 *puVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 *puVar4;
  uint uVar5;
  int iVar6;
  int unaff_EDI;
  char *pcVar7;
  undefined1 local_131;
  undefined1 *local_130;
  void *local_12c;
  undefined4 local_128 [3];
  undefined4 *local_11c;
  undefined1 local_118 [268];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9e17;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_12c = this;
  FUN_004bccd7(this,param_1);
  puVar1 = (undefined4 *)((int)this + 0xc);
  local_4 = 0;
  local_11c = puVar1;
  FUN_004a8710(&local_131);
  *puVar1 = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  local_130 = *(undefined1 **)(param_1 + 0xc);
  iVar6 = *(int *)(param_1 + 0x10) - (int)local_130;
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
  uVar5 = iVar6 + 1;
  if (uVar5 != 0) {
    puVar4 = (undefined1 *)FUN_004aa520(uVar5);
    *puVar1 = puVar4;
    *(undefined1 **)((int)this + 0x10) = puVar4;
    *(undefined1 **)((int)this + 0x14) = puVar4 + uVar5;
    if (0 < iVar6) {
      do {
        uVar3 = *local_130;
        local_130 = local_130 + 1;
        *puVar4 = uVar3;
        puVar4 = puVar4 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    *(undefined1 **)((int)this + 0x10) = puVar4;
    *puVar4 = 0;
    *(undefined ***)this = &PTR_FUN_004cdbdc;
    ExceptionList = local_c;
    return this;
  }
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004a8730(local_128);
  uVar5 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  pcVar7 = s_basic_string_004de5c8;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  FUN_004aa340(local_128,(undefined4 *)s_basic_string_004de5c8,
               (int)(s___AVAuth2Certificate_WONAPI___004de5a8 + ~uVar5 + 0x1f),unaff_EDI);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),4);
  FUN_004a7ed0(local_118,local_128);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_118,&DAT_004d0380);
}


/* 004acf20 size=10 */

undefined1 __fastcall FUN_004acf20(void *param_1)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)ReadBuffer_4acc20(param_1,1);
  return *puVar1;
}


/* 004acf30 size=11 */

undefined2 __fastcall FUN_004acf30(void *param_1)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)ReadBuffer_4acc20(param_1,2);
  return *puVar1;
}


/* 004acf40 size=10 */

undefined4 __fastcall FUN_004acf40(void *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)ReadBuffer_4acc20(param_1,4);
  return *puVar1;
}


/* 004acf50 size=55 */

int __thiscall FUN_004acf50(void *this,char param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  if (param_1 == '\x01') {
    cVar1 = FUN_004acf20(this);
    return (int)cVar1;
  }
  if (param_1 == '\x02') {
    sVar2 = FUN_004acf30(this);
    return (int)sVar2;
  }
  if (param_1 == '\x04') {
    iVar3 = FUN_004acf40(this);
    return iVar3;
  }
  return 0;
}


/* 004acf90 size=114 */

void __thiscall FUN_004acf90(void *this,undefined4 *param_1,uint param_2)

{
  int *piVar1;
  undefined4 *this_00;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 **ppuVar4;
  undefined4 *puVar5;
  undefined4 *local_4;
  
  this_00 = param_1;
  piVar1 = param_1 + 1;
  puVar3 = (undefined4 *)*param_1;
  param_1 = (undefined4 *)(*piVar1 - (int)puVar3);
  local_4 = (undefined4 *)0xffffffff;
  ppuVar4 = &param_1;
  if (param_1 == (undefined4 *)0xffffffff) {
    ppuVar4 = &local_4;
  }
  puVar5 = (undefined4 *)((int)*ppuVar4 + (int)puVar3);
  if (puVar3 != puVar5) {
    FUN_004bab10(puVar3,puVar5,(*piVar1 - (int)puVar5) + 1);
    this_00[1] = (int)puVar3 + (this_00[1] - (int)puVar5);
  }
  uVar2 = param_2;
  puVar3 = (undefined4 *)ReadBuffer_4acc20(this,param_2);
  FUN_004ac2f0(this_00,puVar3,(undefined4 *)((int)puVar3 + uVar2));
  return;
}


/* 004ad010 size=30 */

void __thiscall FUN_004ad010(void *this,undefined4 *param_1,char param_2)

{
  uint uVar1;
  
  uVar1 = FUN_004acf50(this,param_2);
  FUN_004acf90(this,param_1,uVar1);
  return;
}


/* 004ad030 size=130 */

void __thiscall FUN_004ad030(void *this,undefined4 *param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *this_00;
  undefined4 **ppuVar4;
  undefined4 *puVar5;
  undefined4 *local_4;
  
  this_00 = param_1;
  piVar1 = param_1 + 1;
  puVar5 = (undefined4 *)*param_1;
  local_4 = (undefined4 *)0xffffffff;
  param_1 = (undefined4 *)(*piVar1 - (int)puVar5 >> 1);
  ppuVar4 = &param_1;
  if (param_1 == (undefined4 *)0xffffffff) {
    ppuVar4 = &local_4;
  }
  puVar2 = (undefined4 *)((int)puVar5 + (int)*ppuVar4 * 2);
  if (puVar5 != puVar2) {
    FUN_004bab10(puVar5,puVar2,(*piVar1 - (int)puVar2 >> 1) * 2 + 2);
    this_00[1] = this_00[1] + ((int)puVar2 - (int)puVar5 >> 1) * -2;
  }
  uVar3 = param_2 * 2;
  puVar5 = (undefined4 *)ReadBuffer_4acc20(this,uVar3);
  FUN_004ac8b0(this_00,puVar5,(undefined4 *)(uVar3 + (int)puVar5));
  return;
}


/* 004ad0c0 size=30 */

void __thiscall FUN_004ad0c0(void *this,undefined4 *param_1,char param_2)

{
  int iVar1;
  
  iVar1 = FUN_004acf50(this,param_2);
  FUN_004ad030(this,param_1,iVar1);
  return;
}


/* 004ad0e0 size=164 */

int __thiscall FUN_004ad0e0(void *this,undefined4 *param_1,char param_2)

{
  uint uVar1;
  void *this_00;
  undefined4 *puVar2;
  char cVar3;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9e3b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  uVar1 = FUN_004acf50(this,param_2);
  this_00 = (void *)FUN_00430de0(0x10);
  local_4 = 0;
  if (this_00 != (void *)0x0) {
    cVar3 = '\0';
    puVar2 = (undefined4 *)ReadBuffer_4acc20(this,uVar1);
    puVar2 = FUN_004acb10(this_00,puVar2,uVar1,cVar3);
    if (puVar2 != (undefined4 *)0x0) {
      InterlockedIncrement(puVar2 + 1);
      *param_1 = puVar2;
      ExceptionList = local_c;
      return;
    }
  }
  *param_1 = 0;
  ExceptionList = local_c;
  return;
}


/* 004ad190 size=7 */

void __fastcall FUN_004ad190(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}


/* 004ad1a0 size=48 */

void __fastcall FUN_004ad1a0(void *param_1)

{
  FUN_00430df0(*(undefined **)((int)param_1 + 0x10));
  *(undefined4 *)((int)param_1 + 0x10) = 0;
  *(undefined4 *)((int)param_1 + 0xc) = 0;
  *(undefined4 *)((int)param_1 + 8) = 0;
  if (*(byte *)((int)param_1 + 4) != 0) {
    FUN_004ad2d0(param_1,(uint)*(byte *)((int)param_1 + 4));
  }
  return;
}


/* 004ad1d0 size=12 */

void __fastcall FUN_004ad1d0(void *param_1)

{
  *(undefined4 *)((int)param_1 + 0x10) = 0;
  FUN_004ad1a0(param_1);
  return;
}


/* 004ad1e0 size=43 */

undefined4 * __thiscall FUN_004ad1e0(void *this,undefined1 param_1,undefined1 param_2)

{
  *(undefined1 *)((int)this + 5) = param_2;
  *(undefined ***)this = &PTR_FUN_004cdbe8;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined1 *)((int)this + 4) = param_1;
  FUN_004ad1a0(this);
  return this;
}


/* 004ad210 size=30 */

undefined4 * __thiscall FUN_004ad210(void *this,byte param_1)

{
  FUN_004ad230(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004ad230 size=17 */

void __fastcall FUN_004ad230(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cdbe8;
  FUN_00430df0((undefined *)param_1[4]);
  return;
}


/* 004ad250 size=45 */

void __thiscall FUN_004ad250(void *this,int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = *(int *)((int)this + 0xc) + param_1;
  uVar1 = *(uint *)((int)this + 8);
  if (uVar1 < uVar2) {
    if ((int)uVar1 < 0x20) {
      uVar1 = 0x20;
    }
    for (; (int)uVar1 < (int)uVar2; uVar1 = uVar1 * 2) {
    }
    FUN_004ad280(this,uVar1);
  }
  return;
}


/* 004ad280 size=74 */

void __thiscall FUN_004ad280(void *this,uint param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (*(uint *)((int)this + 8) < param_1) {
    puVar1 = (undefined4 *)FUN_00430de0(param_1);
    uVar3 = *(uint *)((int)this + 0xc);
    puVar4 = *(undefined4 **)((int)this + 0x10);
    puVar5 = puVar1;
    for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    FUN_00430df0(*(undefined **)((int)this + 0x10));
    *(undefined4 **)((int)this + 0x10) = puVar1;
    *(uint *)((int)this + 8) = param_1;
  }
  return;
}


/* 004ad2d0 size=27 */

void __thiscall FUN_004ad2d0(void *this,int param_1)

{
  FUN_004ad250(this,param_1);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + param_1;
  return;
}


/* 004ad2f0 size=59 */

void __thiscall FUN_004ad2f0(void *this,undefined4 *param_1,uint param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  
  FUN_004ad250(this,param_2);
  puVar2 = (undefined4 *)(*(int *)((int)this + 0x10) + *(int *)((int)this + 0xc));
  for (uVar1 = param_2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  for (uVar1 = param_2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar2 = *(undefined1 *)param_1;
    param_1 = (undefined4 *)((int)param_1 + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  *(uint *)((int)this + 0xc) = *(int *)((int)this + 0xc) + param_2;
  return;
}


/* 004ad330 size=15 */

int __thiscall FUN_004ad330(void *this,undefined4 param_1)

{
  FUN_004ad2f0(this,&param_1,1);
  return;
}


/* 004ad340 size=15 */

void __thiscall FUN_004ad340(void *this,undefined4 param_1)

{
  FUN_004ad2f0(this,&param_1,2);
  return;
}


/* 004ad350 size=15 */

void __thiscall FUN_004ad350(void *this,undefined4 param_1)

{
  FUN_004ad2f0(this,&param_1,4);
  return;
}


/* 004ad360 size=59 */

void __thiscall FUN_004ad360(void *this,undefined4 param_1,char param_2)

{
  if (param_2 == '\x01') {
    FUN_004ad330(this,param_1);
  }
  else {
    if (param_2 == '\x02') {
      FUN_004ad340(this,param_1);
      return;
    }
    if (param_2 == '\x04') {
      FUN_004ad350(this,param_1);
      return;
    }
  }
  return;
}


/* 004ad3a0 size=49 */

void __thiscall FUN_004ad3a0(void *this,int *param_1,char param_2)

{
  FUN_004ad360(this,param_1[1] - *param_1,param_2);
  FUN_004ad2f0(this,(undefined4 *)*param_1,param_1[1] - *param_1);
  return;
}


/* 004ad3e0 size=59 */

void __thiscall FUN_004ad3e0(void *this,int param_1,char param_2)

{
  uint uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0xc);
  }
  FUN_004ad360(this,uVar1,param_2);
  if ((param_1 != 0) && (uVar1 != 0)) {
    FUN_004ad2f0(this,*(undefined4 **)(param_1 + 8),uVar1);
  }
  return;
}


/* 004ad420 size=211 */

int __thiscall FUN_004ad420(void *this,undefined4 *param_1,char param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  void *this_00;
  undefined4 *puVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9e5b;
  local_c = ExceptionList;
  iVar3 = *(int *)((int)this + 0xc);
  if (*(char *)((int)this + 5) == '\0') {
    iVar3 = iVar3 - (uint)*(byte *)((int)this + 4);
  }
  cVar1 = *(char *)((int)this + 4);
  if (cVar1 == '\x01') {
    ExceptionList = &local_c;
    **(undefined1 **)((int)this + 0x10) = (char)iVar3;
  }
  else if (cVar1 == '\x02') {
    ExceptionList = &local_c;
    **(undefined2 **)((int)this + 0x10) = (short)iVar3;
  }
  else {
    ExceptionList = &local_c;
    if (cVar1 == '\x04') {
      ExceptionList = &local_c;
      **(int **)((int)this + 0x10) = iVar3;
    }
  }
  puVar4 = *(undefined4 **)((int)this + 0x10);
  uVar2 = *(uint *)((int)this + 0xc);
  if (param_2 != '\0') {
    FUN_004ad1d0(this);
  }
  this_00 = (void *)FUN_00430de0(0x10);
  local_4 = 0;
  if (this_00 != (void *)0x0) {
    puVar4 = FUN_004acb10(this_00,puVar4,uVar2,param_2);
    if (puVar4 != (undefined4 *)0x0) {
      InterlockedIncrement(puVar4 + 1);
      *param_1 = puVar4;
      ExceptionList = local_c;
      return;
    }
  }
  *param_1 = 0;
  ExceptionList = local_c;
  return;
}


/* 004ad500 size=96 */

void __thiscall FUN_004ad500(void *this,undefined4 *param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  
  uVar1 = (param_2 - (int)param_1) + 1;
  if (uVar1 == 0) {
    FUN_004a5b30(s_basic_string_004de5c8);
  }
  else {
    iVar3 = FUN_004aa520(uVar1);
    *(int *)this = iVar3;
    *(int *)((int)this + 4) = iVar3;
    *(uint *)((int)this + 8) = iVar3 + uVar1;
  }
  puVar2 = *(undefined4 **)this;
  FUN_004bab10(puVar2,param_1,param_2 - (int)param_1);
  puVar4 = (undefined1 *)((int)puVar2 + (param_3 - (int)param_1));
  *(undefined1 **)((int)this + 4) = puVar4;
  *puVar4 = 0;
  return;
}


/* 004ad560 size=22 */

int __fastcall FUN_004ad560(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004ad580(param_1);
  return (int)(iVar1 + 7 + (iVar1 + 7 >> 0x1f & 7U)) >> 3;
}


/* 004ad580 size=44 */

int __cdecl FUN_004ad580(int param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(param_1 + 0x1a);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = uVar2 * 0x20 + -0x20;
  for (uVar2 = *(uint *)(*(int *)(param_1 + 0x14) + -4 + uVar2 * 4); uVar2 != 0; uVar2 = uVar2 >> 1)
  {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}


/* 004ad5b0 size=329 */

undefined4 * __cdecl FUN_004ad5b0(undefined4 *param_1,int param_2,void *param_3)

{
  int iVar1;
  byte *pbVar2;
  undefined1 *puVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  byte *local_18;
  byte *local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  iVar1 = param_2;
  puStack_8 = &LAB_004c9eaf;
  local_c = ExceptionList;
  uVar5 = (int)(param_2 + 7 + (param_2 + 7 >> 0x1f & 7U)) >> 3;
  local_4 = 1;
  local_18 = (byte *)0x0;
  local_14 = (byte *)0x0;
  ExceptionList = &local_c;
  FUN_004a93e0(&local_10,&param_2,0);
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004a9380(&local_18,uVar5 + 1);
  local_14 = local_18;
  if (uVar5 != 0) {
    pbVar6 = local_18;
    for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      pbVar6[0] = 0;
      pbVar6[1] = 0;
      pbVar6[2] = 0;
      pbVar6[3] = 0;
      pbVar6 = pbVar6 + 4;
    }
    for (uVar4 = uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar6 = 0;
      pbVar6 = pbVar6 + 1;
    }
    local_14 = local_18 + uVar5;
  }
  *local_14 = 0;
  (*(uint8_t*)((char*)&local_4+0)) = 4;
  if (0 < (int)uVar5) {
    FUN_004b3450(param_3,(int *)&local_18);
    *local_18 = *local_18 & ('\x01' << (8U - ((char)uVar5 * '\b' - (char)iVar1) & 0x1f)) - 1U;
  }
  FUN_004a8710(&param_3);
  pbVar2 = local_14;
  pbVar6 = local_18;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),5);
  FUN_004a9380(param_1,(uint)(local_14 + (1 - (int)local_18)));
  puVar3 = (undefined1 *)FUN_004aca30((int)pbVar6,(int)pbVar2,(undefined1 *)*param_1);
  param_1[1] = puVar3;
  *puVar3 = 0;
  local_4 = 6;
  if (local_18 != (byte *)0x0) {
    FUN_004aa6f0((undefined4 *)local_18,local_10 - (int)local_18);
  }
  ExceptionList = local_c;
  return param_1;
}


/* 004ad700 size=66 */

/* FUN_004ad700: lifted from original x86 -> lt_lifted.c */


/* 004ad750 size=60 */

void __cdecl FUN_004ad750(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  
  iVar2 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if (iVar2 < (int)(uint)*(ushort *)(param_1 + 0x1a)) {
    puVar1 = (uint *)(*(int *)(param_1 + 0x14) + iVar2 * 4);
    *puVar1 = *puVar1 | 1 << ((byte)param_2 & 0x1f);
  }
  return;
}


/* 004ad790 size=48 */

void __cdecl FUN_004ad790(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  if (param_1 == param_2) {
    FUN_004bab10(param_1,param_2,param_3 * 4);
    return;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    *param_1 = *param_2;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


/* 004ad7c0 size=120 */

void __thiscall FUN_004ad7c0(void *this,int param_1,undefined4 *param_2,int param_3)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar1 = *(undefined **)((int)this + 0x14);
  if (param_1 < 5) {
    *(int *)((int)this + 0x14) = (int)this + 4;
  }
  else {
    uVar2 = FUN_00430de0(param_1 * 4);
    *(undefined4 *)((int)this + 0x14) = uVar2;
  }
  if (param_2 != *(undefined4 **)((int)this + 0x14)) {
    puVar4 = *(undefined4 **)((int)this + 0x14);
    for (iVar3 = param_1; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
  }
  *(short *)((int)this + 0x18) = (short)param_1;
  *(short *)((int)this + 0x1a) = (short)param_3;
  if ((param_2 != (undefined4 *)0x0) &&
     (puVar4 = *(undefined4 **)((int)this + 0x14), param_2 != *(undefined4 **)((int)this + 0x14))) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      *puVar4 = *param_2;
      param_2 = param_2 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  if (puVar1 != (undefined *)((int)this + 4)) {
    FUN_00430df0(puVar1);
  }
  return;
}


/* 004ad840 size=27 */

void __fastcall FUN_004ad840(void *param_1)

{
  *(undefined4 *)((int)param_1 + 0x14) = 0;
  FUN_004ad7c0(param_1,4,(undefined4 *)0x0,0);
  *(undefined1 *)((int)param_1 + 0x1c) = 0;
  return;
}


/* 004ad860 size=24 */

int __fastcall FUN_004ad860(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cec3c;
  if ((undefined4 *)param_1[5] != param_1 + 1) {
    FUN_00430df0((undefined *)param_1[5]);
  }
  return;
}


/* 004ad880 size=30 */

undefined4 * __thiscall FUN_004ad880(void *this,byte param_1)

{
  FUN_004ad860(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004ad8a0 size=48 */

void __cdecl FUN_004ad8a0(void *param_1,void *param_2)

{
  if (param_1 != param_2) {
    FUN_004ad7c0(param_1,(uint)*(ushort *)((int)param_2 + 0x18),
                 *(undefined4 **)((int)param_2 + 0x14),(uint)*(ushort *)((int)param_2 + 0x1a));
    *(undefined1 *)((int)param_1 + 0x1c) = *(undefined1 *)((int)param_2 + 0x1c);
  }
  return;
}


/* 004ad8d0 size=58 */

void __cdecl FUN_004ad8d0(void *param_1,int param_2,char param_3)

{
  if ((int)(uint)*(ushort *)((int)param_1 + 0x18) < param_2) {
    if (param_3 != '\0') {
      FUN_004ad7c0(param_1,param_2 + 0x10,*(undefined4 **)((int)param_1 + 0x14),
                   (uint)*(ushort *)((int)param_1 + 0x1a));
      return;
    }
    FUN_004ad7c0(param_1,param_2 + 0x10,(undefined4 *)0x0,0);
  }
  return;
}


/* 004ad910 size=349 */

int __thiscall FUN_004ad910(void *this,int *param_1)

{
  int *piVar1;
  undefined1 *puVar2;
  undefined1 uVar3;
  undefined4 *puVar4;
  int *this_00;
  byte bVar5;
  int iVar6;
  int **ppiVar7;
  undefined1 *puVar8;
  int *piVar9;
  undefined1 *puVar10;
  int iVar11;
  undefined4 *puVar12;
  int iVar13;
  int *local_4;
  
  iVar6 = FUN_004ad580((int)this);
  this_00 = param_1;
  piVar1 = param_1 + 1;
  puVar4 = (undefined4 *)*param_1;
  param_1 = (int *)(*piVar1 - (int)puVar4);
  local_4 = (int *)0xffffffff;
  piVar9 = (int *)((int)((iVar6 + 7 >> 0x1f & 7U) + iVar6 + 7) >> 3);
  ppiVar7 = &param_1;
  if (param_1 == (int *)0xffffffff) {
    ppiVar7 = &local_4;
  }
  puVar12 = (undefined4 *)((int)puVar4 + (int)*ppiVar7);
  if (puVar4 != puVar12) {
    FUN_004bab10(puVar4,puVar12,(*piVar1 - (int)puVar12) + 1);
    this_00[1] = (int)puVar4 + (this_00[1] - (int)puVar12);
  }
  FUN_004b3970(this_00,(undefined4 *)((int)piVar9 + 1));
  if (piVar9 == (int *)0x0) {
    FUN_004b3910(this_00,0);
  }
  if (0 < (int)piVar9) {
    iVar13 = 0;
    iVar6 = 0;
    param_1 = piVar9;
    do {
      iVar11 = iVar6 + 8;
      bVar5 = (byte)(*(uint *)(iVar13 + *(int *)((int)this + 0x14)) >> ((byte)iVar6 & 0x1f));
      if (0x1f < iVar11) {
        iVar11 = iVar6 + -0x18;
        iVar13 = iVar13 + 4;
        if (0 < iVar11) {
          bVar5 = bVar5 | (byte)(*(int *)(iVar13 + *(int *)((int)this + 0x14)) <<
                                (8U - (char)iVar11 & 0x1f));
        }
      }
      FUN_004b3910(this_00,bVar5);
      param_1 = (int *)((int)param_1 + -1);
      iVar6 = iVar11;
    } while (param_1 != (int *)0x0);
  }
  if ((*(char *)((int)this + 0x1c) == '\0') && (iVar6 = this_00[1], *(char *)(iVar6 + -1) < '\0')) {
    if (iVar6 + 1 == this_00[2]) {
      param_1 = (int *)0x1;
      local_4 = (int *)(iVar6 - *this_00);
      ppiVar7 = &param_1;
      if (local_4 != (int *)0x0) {
        ppiVar7 = &local_4;
      }
      FUN_004b3970(this_00,(undefined4 *)((int)*ppiVar7 + (int)local_4));
    }
    *(undefined1 *)(this_00[1] + 1) = 0;
    *(undefined1 *)this_00[1] = 0;
    this_00[1] = this_00[1] + 1;
  }
  puVar8 = (undefined1 *)this_00[1];
  puVar10 = (undefined1 *)*this_00;
  if (puVar10 < puVar8) {
    do {
      puVar2 = puVar8 + -1;
      uVar3 = *puVar10;
      puVar8 = puVar8 + -1;
      *puVar10 = *puVar2;
      puVar10 = puVar10 + 1;
      *puVar8 = uVar3;
    } while (puVar10 < puVar8);
  }
  return (int)piVar9;
}


/* 004ada70 size=220 */

void __thiscall FUN_004ada70(void *this,int *param_1)

{
  uint *puVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int local_4;
  
  *(undefined1 *)((int)this + 0x1c) = 0;
  uVar7 = (*param_1 * 0x1fffffff + param_1[1]) * 8 + 0x1fU >> 5;
  FUN_004ad8d0(this,uVar7,'\0');
  *(short *)((int)this + 0x1a) = (short)uVar7;
  **(undefined4 **)((int)this + 0x14) = 0;
  local_4 = (param_1[1] - *param_1) + -1;
  if (-1 < local_4) {
    iVar6 = 0;
    iVar4 = 0;
    do {
      bVar2 = *(byte *)(*param_1 + local_4);
      puVar1 = (uint *)(*(int *)((int)this + 0x14) + iVar6);
      iVar5 = iVar4 + 8;
      *puVar1 = *puVar1 | (uint)bVar2 << ((byte)iVar4 & 0x1f);
      if ((0x1f < iVar5) && (0 < local_4)) {
        iVar6 = iVar6 + 4;
        iVar5 = iVar4 + -0x18;
        *(undefined4 *)(*(int *)((int)this + 0x14) + iVar6) = 0;
        if (0 < iVar5) {
          *(uint *)(*(int *)((int)this + 0x14) + iVar6) = (uint)(bVar2 >> (8U - (char)iVar5 & 0x1f))
          ;
        }
      }
      local_4 = local_4 + -1;
      iVar4 = iVar5;
    } while (-1 < local_4);
  }
  if (*(short *)((int)this + 0x1a) != 0) {
    do {
      if (*(int *)(*(int *)((int)this + 0x14) + -4 + (uint)*(ushort *)((int)this + 0x1a) * 4) != 0)
      {
        return;
      }
      sVar3 = *(ushort *)((int)this + 0x1a) - 1;
      *(short *)((int)this + 0x1a) = sVar3;
    } while (sVar3 != 0);
  }
  return;
}


/* 004adb50 size=19 */

void __cdecl FUN_004adb50(int param_1)

{
  **(undefined4 **)(param_1 + 0x14) = 0;
  *(undefined1 *)(param_1 + 0x1c) = 0;
  *(undefined2 *)(param_1 + 0x1a) = 0;
  return;
}


/* 004adb70 size=24 */

void __cdecl FUN_004adb70(int param_1)

{
  **(undefined4 **)(param_1 + 0x14) = 1;
  *(undefined1 *)(param_1 + 0x1c) = 0;
  *(undefined2 *)(param_1 + 0x1a) = 1;
  return;
}


/* 004adb90 size=185 */

int __cdecl FUN_004adb90(int param_1,uint *param_2,uint *param_3,int param_4,int param_5)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  
  iVar4 = param_5;
  iVar5 = param_4;
  puVar2 = param_2;
  if (param_4 < param_5) {
    do {
      param_2 = param_3;
      param_3 = puVar2;
      param_5 = iVar5;
      iVar5 = iVar4;
      iVar4 = param_5;
      puVar2 = param_2;
    } while (iVar5 < param_5);
  }
  uVar8 = 0;
  iVar4 = 0;
  if (0 < param_5) {
    iVar6 = (int)param_2 - (int)param_3;
    iVar4 = param_1 - (int)param_3;
    param_4 = param_5;
    do {
      uVar1 = *(uint *)((int)param_3 + iVar6);
      uVar3 = uVar1 + uVar8;
      uVar8 = (uint)CARRY4(uVar1,uVar8) + (uint)CARRY4(uVar3,*param_3);
      *(uint *)(iVar4 + (int)param_3) = uVar3 + *param_3;
      param_3 = param_3 + 1;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
    iVar4 = param_5;
  }
  if (iVar4 < iVar5) {
    iVar5 = iVar5 - iVar4;
    piVar7 = (int *)(param_1 + iVar4 * 4);
    iVar4 = iVar4 + iVar5;
    do {
      uVar1 = *(uint *)((int)piVar7 + ((int)param_2 - param_1));
      iVar6 = uVar1 + uVar8;
      uVar8 = (uint)CARRY4(uVar1,uVar8);
      *piVar7 = iVar6;
      piVar7 = piVar7 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  if (uVar8 != 0) {
    *(uint *)(param_1 + iVar4 * 4) = uVar8;
    iVar4 = iVar4 + 1;
  }
  return iVar4;
}


/* 004adc50 size=166 */

void __cdecl FUN_004adc50(int param_1,uint *param_2,uint *param_3,int param_4,int param_5)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  int *piVar9;
  
  puVar5 = (uint *)param_5;
  puVar2 = param_2;
  puVar8 = param_3;
  param_4 = param_4;
  if (param_4 < param_5) {
    do {
      param_5 = param_4;
      param_2 = param_3;
      puVar8 = puVar2;
      param_4 = (int)puVar5;
      puVar5 = (uint *)param_5;
      puVar2 = param_2;
      param_3 = puVar8;
    } while (param_4 < param_5);
  }
  uVar3 = 0;
  puVar5 = (uint *)0x0;
  if (0 < param_5) {
    iVar6 = (int)param_2 - (int)puVar8;
    iVar7 = param_1 - (int)puVar8;
    param_3 = (uint *)param_5;
    do {
      uVar1 = *(uint *)(iVar6 + (int)puVar8);
      uVar4 = uVar1 - uVar3;
      uVar3 = -(-(uint)(uVar4 < *puVar8) - (uint)(uVar1 < uVar3));
      *(uint *)(iVar7 + (int)puVar8) = uVar4 - *puVar8;
      puVar8 = puVar8 + 1;
      param_3 = (uint *)((int)param_3 + -1);
    } while (param_3 != (uint *)0x0);
    puVar5 = (uint *)param_5;
  }
  if ((int)puVar5 < param_4) {
    piVar9 = (int *)(param_1 + (int)puVar5 * 4);
    iVar6 = param_4 - (int)puVar5;
    do {
      uVar1 = *(uint *)(((int)param_2 - param_1) + (int)piVar9);
      iVar7 = uVar1 - uVar3;
      uVar3 = (uint)(uVar1 < uVar3);
      *piVar9 = iVar7;
      piVar9 = piVar9 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  return;
}


/* 004add00 size=242 */

void __cdecl FUN_004add00(uint *param_1,int param_2,uint *param_3,int param_4,int param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  longlong lVar8;
  int local_1c;
  int local_18;
  
  puVar5 = param_1;
  for (uVar1 = param_4 + param_5 & 0x3fffffff; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar5 = 0;
    puVar5 = (uint *)((int)puVar5 + 1);
  }
  local_18 = 0;
  if (0 < param_4) {
    local_1c = param_5 * 4;
    iVar2 = param_2 - (int)param_1;
    puVar5 = param_1;
    do {
      uVar1 = *(uint *)((int)puVar5 + iVar2);
      uVar7 = 0;
      iVar3 = local_18 * 4;
      if (0 < param_5) {
        puVar4 = param_3;
        puVar6 = puVar5;
        param_2 = param_5;
        do {
          lVar8 = __allmul(*puVar4,0,uVar1,0);
          lVar8 = lVar8 + (ulonglong)*puVar6 + (ulonglong)uVar7;
          *puVar6 = (uint)lVar8;
          uVar7 = (uint)((ulonglong)lVar8 >> 0x20);
          puVar6 = puVar6 + 1;
          puVar4 = puVar4 + 1;
          param_2 = param_2 + -1;
        } while (param_2 != 0);
        iVar3 = local_1c;
      }
      *(uint *)(iVar3 + (int)param_1) = uVar7;
      local_18 = local_18 + 1;
      puVar5 = puVar5 + 1;
      local_1c = local_1c + 4;
    } while (local_18 < param_4);
  }
  return;
}


/* 004ade00 size=87 */

void __cdecl FUN_004ade00(undefined4 *param_1,int param_2,uint param_3,int param_4)

{
  ulonglong uVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  longlong lVar5;
  
  uVar4 = 0;
  if (param_4 < 1) {
    *param_1 = 0;
    return;
  }
  iVar2 = param_4;
  puVar3 = param_1;
  do {
    lVar5 = __allmul(*(uint *)((param_2 - (int)param_1) + (int)puVar3),0,param_3,0);
    uVar1 = (ulonglong)uVar4;
    uVar4 = (uint)(lVar5 + uVar1 >> 0x20);
    *puVar3 = (int)(lVar5 + uVar1);
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  param_1[param_4] = uVar4;
  return;
}


/* 004ade60 size=98 */

int __cdecl FUN_004ade60(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  
  if (param_3 != param_4) {
    return ((param_3 <= param_4) - 1 & 2) - 1;
  }
  iVar1 = param_3 + -1;
  if (-1 < iVar1) {
    piVar2 = (int *)(param_2 + iVar1 * 4);
    do {
      if (*(int *)((param_1 - param_2) + (int)piVar2) != *piVar2) {
        return (-(uint)(*(uint *)(param_2 + iVar1 * 4) < *(uint *)(param_1 + iVar1 * 4)) & 2) - 1;
      }
      iVar1 = iVar1 + -1;
      piVar2 = piVar2 + -1;
    } while (-1 < iVar1);
  }
  return 0;
}


/* 004aded0 size=630 */

void __cdecl
FUN_004aded0(uint *param_1,uint *param_2,uint *param_3,uint *param_4,uint param_5,undefined4 param_6
            ,int param_7)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  bool bVar5;
  
  if ((int)param_5 < 0x11) {
    FUN_004add00(param_1,(int)param_3,param_4,param_5,param_5);
    return;
  }
  uVar3 = (int)param_5 >> 1;
  puVar4 = param_4 + uVar3;
  iVar2 = param_5 * 2;
  puVar1 = param_2 + param_5;
  if ((int)uVar3 < param_7) {
    iVar2 = FUN_004ade60((int)(param_3 + uVar3),(int)param_3,uVar3,uVar3);
    bVar5 = iVar2 < 1;
    if (bVar5) {
      FUN_004adc50((int)param_1,param_3,param_3 + uVar3,uVar3,uVar3);
    }
    else {
      FUN_004adc50((int)param_1,param_3 + uVar3,param_3,uVar3,uVar3);
    }
    iVar2 = FUN_004ade60((int)puVar4,(int)param_4,uVar3,uVar3);
    if (iVar2 < 1) {
      FUN_004adc50((int)(param_1 + uVar3 * 2),param_4,puVar4,uVar3,uVar3);
    }
    else {
      FUN_004adc50((int)(param_1 + uVar3 * 2),puVar4,param_4,uVar3,uVar3);
      bVar5 = !bVar5;
    }
    FUN_004aded0(param_2,puVar1,param_1,param_1 + uVar3 * 2,uVar3,uVar3,uVar3);
    FUN_004aded0(param_1,puVar1,param_3,param_4,uVar3,uVar3,uVar3);
    FUN_004aded0(param_1 + uVar3 * 2,puVar1,param_3 + uVar3,puVar4,uVar3,uVar3,uVar3);
    iVar2 = FUN_004adb90((int)puVar1,param_1,param_1 + uVar3 * 2,uVar3 * 2,uVar3 * 2);
    if (bVar5) {
      FUN_004adc50((int)puVar1,puVar1,param_2,iVar2,uVar3 * 2);
    }
    else {
      iVar2 = FUN_004adb90((int)puVar1,puVar1,param_2,iVar2,uVar3 * 2);
    }
    FUN_004adb90((int)(param_1 + uVar3),param_1 + uVar3,puVar1,uVar3 + param_5,iVar2);
  }
  else {
    puVar4 = param_1;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    FUN_004aded0(param_1 + uVar3,puVar1,param_3 + uVar3,param_4,uVar3,uVar3,param_7);
    FUN_004aded0(param_2,puVar1,param_3,param_4,uVar3,uVar3,param_7);
    FUN_004adb90((int)param_1,param_1,param_2,uVar3 + param_5,param_5);
  }
  if ((param_5 & 1) != 0) {
    if (param_4[param_5 - 1] != 0) {
      FUN_004ade00(param_2,(int)param_3,param_4[param_5 - 1],param_5 - 1);
      FUN_004adb90((int)(param_1 + (param_5 - 1)),param_1 + (param_5 - 1),param_2,param_5,param_5);
    }
    FUN_004ade00(puVar1,(int)param_4,param_3[param_5 - 1],param_5 - 1);
    FUN_004adb90((int)(param_1 + (param_5 - 1)),param_1 + (param_5 - 1),puVar1,param_5,param_5);
    param_1[param_5 * 2 + -2] =
         param_3[param_5 - 1] * param_4[param_5 - 1] + param_1[param_5 * 2 + -2];
    param_1[param_5 * 2 + -1] = 0;
  }
  return;
}


/* 004ae150 size=30 */

int __cdecl FUN_004ae150(int param_1,int param_2)

{
  int *piVar1;
  
  if (0 < param_2) {
    piVar1 = (int *)(param_1 + -4 + param_2 * 4);
    do {
      if (*piVar1 != 0) {
        return;
      }
      param_2 = param_2 + -1;
      piVar1 = piVar1 + -1;
    } while (0 < param_2);
  }
  return;
}


/* 004ae170 size=144 */

void __cdecl FUN_004ae170(void *param_1,void *param_2,void *param_3)

{
  if (*(short *)((int)param_2 + 0x1a) == 0) {
    FUN_004ad8a0(param_1,param_3);
    return;
  }
  if (*(short *)((int)param_3 + 0x1a) == 0) {
    FUN_004ad8a0(param_1,param_2);
    return;
  }
  if (*(char *)((int)param_2 + 0x1c) == '\0') {
    if (*(char *)((int)param_3 + 0x1c) == '\0') {
      FUN_004ae540(param_1,(int)param_2,(int)param_3);
      return;
    }
    FUN_004ae5b0(param_1,(int)param_2,(int)param_3,'\x01');
    return;
  }
  if (*(char *)((int)param_3 + 0x1c) == '\0') {
    FUN_004ae5b0(param_1,(int)param_3,(int)param_2,'\x01');
    return;
  }
  FUN_004ae540(param_1,(int)param_2,(int)param_3);
  *(undefined1 *)((int)param_1 + 0x1c) = 1;
  return;
}


/* 004ae200 size=179 */

void __cdecl FUN_004ae200(void *param_1,void *param_2,void *param_3)

{
  if (*(short *)((int)param_2 + 0x1a) == 0) {
    FUN_004ad8a0(param_1,param_3);
    if (*(short *)((int)param_3 + 0x1a) != 0) {
      *(byte *)((int)param_1 + 0x1c) = *(byte *)((int)param_3 + 0x1c) ^ 1;
      return;
    }
  }
  else {
    if (*(short *)((int)param_3 + 0x1a) == 0) {
      FUN_004ad8a0(param_1,param_2);
      return;
    }
    if (*(char *)((int)param_2 + 0x1c) != '\0') {
      if (*(char *)((int)param_3 + 0x1c) == '\0') {
        FUN_004ae540(param_1,(int)param_3,(int)param_2);
        *(undefined1 *)((int)param_1 + 0x1c) = 1;
        return;
      }
      FUN_004ae5b0(param_1,(int)param_3,(int)param_2,'\x01');
      return;
    }
    if (*(char *)((int)param_3 + 0x1c) != '\0') {
      FUN_004ae540(param_1,(int)param_2,(int)param_3);
      return;
    }
    FUN_004ae5b0(param_1,(int)param_2,(int)param_3,'\x01');
  }
  return;
}


/* 004ae2c0 size=75 */

undefined4 __cdecl FUN_004ae2c0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((*(short *)(param_1 + 0x1a) == 0) && (*(short *)(param_2 + 0x1a) == 0)) {
    return 0;
  }
  if (*(char *)(param_1 + 0x1c) == '\0') {
    if (*(char *)(param_2 + 0x1c) == '\0') {
      uVar1 = FUN_004ae310(param_1,param_2);
      return uVar1;
    }
    return 1;
  }
  if (*(char *)(param_2 + 0x1c) == '\0') {
    return 0xffffffff;
  }
  uVar1 = FUN_004ae310(param_2,param_1);
  return uVar1;
}


/* 004ae310 size=39 */

int __cdecl FUN_004ae310(int param_1,int param_2)

{
  FUN_004ade60(*(int *)(param_1 + 0x14),*(int *)(param_2 + 0x14),(uint)*(ushort *)(param_1 + 0x1a),
               (uint)*(ushort *)(param_2 + 0x1a));
  return;
}


/* 004ae340 size=269 */

void __cdecl FUN_004ae340(void *param_1,int param_2,uint param_3)

{
  ushort uVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  
  uVar1 = *(ushort *)(param_2 + 0x1a);
  if (uVar1 == 0) {
    FUN_004adb50((int)param_1);
    return;
  }
  uVar9 = param_3 & 0x8000001f;
  if ((int)uVar9 < 0) {
    uVar9 = (uVar9 - 1 | 0xffffffe0) + 1;
  }
  iVar8 = (int)(param_3 + ((int)param_3 >> 0x1f & 0x1fU)) >> 5;
  FUN_004ad8d0(param_1,(uint)uVar1 + iVar8,'\x01');
  *(ushort *)((int)param_1 + 0x1a) = (short)iVar8 + uVar1;
  iVar4 = *(int *)((int)param_1 + 0x14);
  puVar5 = (uint *)(iVar4 + iVar8 * 4);
  FUN_004ad790(puVar5,*(undefined4 **)(param_2 + 0x14),(uint)uVar1);
  if ((0 < iVar8) && (-1 < iVar8 + -1)) {
    puVar2 = (undefined4 *)(iVar4 + (iVar8 + -1) * 4);
    iVar4 = iVar8;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + -1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (uVar9 != 0) {
    uVar7 = (uint)*(ushort *)((int)param_1 + 0x1a);
    if (iVar8 < (int)uVar7) {
      param_2 = uVar7 - iVar8;
      uVar6 = 0;
      do {
        uVar3 = *puVar5 >> (0x20 - (byte)uVar9 & 0x1f);
        *puVar5 = *puVar5 << ((byte)uVar9 & 0x1f) | uVar6;
        param_2 = param_2 + -1;
        puVar5 = puVar5 + 1;
        uVar6 = uVar3;
      } while (param_2 != 0);
      if (uVar3 != 0) {
        iVar4 = uVar7 + 1;
        FUN_004ad8d0(param_1,iVar4,'\x01');
        *(uint *)(*(int *)((int)param_1 + 0x14) + -4 + iVar4 * 4) = uVar3;
        *(short *)((int)param_1 + 0x1a) = (short)iVar4;
      }
    }
  }
  return;
}


/* 004ae450 size=240 */

void __cdecl FUN_004ae450(void *param_1,int param_2,uint param_3)

{
  uint *puVar1;
  ushort uVar2;
  uint uVar3;
  byte bVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  uVar6 = param_3 & 0x8000001f;
  if ((int)uVar6 < 0) {
    uVar6 = (uVar6 - 1 | 0xffffffe0) + 1;
  }
  iVar7 = (int)(param_3 + ((int)param_3 >> 0x1f & 0x1fU)) >> 5;
  if ((int)(uint)*(ushort *)(param_2 + 0x1a) <= iVar7) {
    FUN_004adb50((int)param_1);
    return;
  }
  FUN_004ad8d0(param_1,(uint)*(ushort *)(param_2 + 0x1a) - iVar7,'\x01');
  uVar2 = *(short *)(param_2 + 0x1a) - (short)iVar7;
  *(ushort *)((int)param_1 + 0x1a) = uVar2;
  FUN_004ad790(*(undefined4 **)((int)param_1 + 0x14),
               (undefined4 *)(*(int *)(param_2 + 0x14) + iVar7 * 4),(uint)uVar2);
  if (uVar6 != 0) {
    puVar1 = *(uint **)((int)param_1 + 0x14);
    uVar3 = (uint)*(ushort *)((int)param_1 + 0x1a);
    uVar8 = 0;
    param_3 = uVar3 - 1;
    bVar4 = (byte)uVar6;
    if (0 < (int)param_3) {
      puVar5 = puVar1 + param_3;
      uVar6 = uVar8;
      do {
        uVar8 = *puVar5 << (0x20 - bVar4 & 0x1f);
        *puVar5 = *puVar5 >> (bVar4 & 0x1f) | uVar6;
        param_3 = param_3 - 1;
        puVar5 = puVar5 + -1;
        uVar6 = uVar8;
      } while (param_3 != 0);
    }
    *puVar1 = *puVar1 >> (bVar4 & 0x1f) | uVar8;
    if ((uVar3 != 0) && (puVar1[uVar3 - 1] == 0)) {
      *(short *)((int)param_1 + 0x1a) = *(short *)((int)param_1 + 0x1a) + -1;
    }
  }
  return;
}


/* 004ae540 size=109 */

void __cdecl FUN_004ae540(void *param_1,int param_2,int param_3)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  
  iVar3 = param_2;
  param_3 = param_3;
  if (*(ushort *)(param_2 + 0x1a) < *(ushort *)(param_3 + 0x1a)) {
    do {
      param_2 = param_3;
      param_3 = iVar3;
      iVar3 = param_2;
    } while (*(ushort *)(param_2 + 0x1a) < *(ushort *)(param_3 + 0x1a));
  }
  uVar1 = *(ushort *)(param_2 + 0x1a);
  uVar2 = *(ushort *)(param_3 + 0x1a);
  FUN_004ad8d0(param_1,uVar1 + 1,'\x01');
  *(undefined1 *)((int)param_1 + 0x1c) = 0;
  iVar3 = FUN_004adb90(*(int *)((int)param_1 + 0x14),*(uint **)(param_2 + 0x14),
                       *(uint **)(param_3 + 0x14),(uint)uVar1,(uint)uVar2);
  *(short *)((int)param_1 + 0x1a) = (short)iVar3;
  return;
}


/* 004ae5b0 size=171 */

void __cdecl FUN_004ae5b0(void *param_1,int param_2,int param_3,char param_4)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  
  iVar3 = FUN_004ae310(param_2,param_3);
  while (iVar1 = param_2, iVar3 == -1) {
    if (param_4 != '\0') {
      *(undefined1 *)((int)param_1 + 0x1c) = 1;
    }
    param_4 = '\0';
    iVar3 = FUN_004ae310(param_3,iVar1);
    param_2 = param_3;
    param_3 = iVar1;
  }
  if (iVar3 == 0) {
    FUN_004adb50((int)param_1);
    return;
  }
  if ((iVar3 == 1) && (param_4 != '\0')) {
    *(undefined1 *)((int)param_1 + 0x1c) = 0;
  }
  FUN_004ad8d0(param_1,(uint)*(ushort *)(iVar1 + 0x1a),'\x01');
  FUN_004adc50(*(int *)((int)param_1 + 0x14),*(uint **)(iVar1 + 0x14),*(uint **)(param_3 + 0x14),
               (uint)*(ushort *)(iVar1 + 0x1a),(uint)*(ushort *)(param_3 + 0x1a));
  uVar2 = FUN_004ae150(*(int *)((int)param_1 + 0x14),(uint)*(ushort *)(iVar1 + 0x1a));
  *(undefined2 *)((int)param_1 + 0x1a) = uVar2;
  return;
}


/* 004ae810 size=30 */

exception * __thiscall FUN_004ae810(void *this,byte param_1)

{
  FUN_004ae830(this);
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004ae830 size=155 */

void __fastcall FUN_004ae830(exception *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004c9f13;
  local_c = ExceptionList;
  puVar1 = *(undefined4 **)(param_1 + 0xc);
  iVar2 = *(int *)(param_1 + 0x14);
  local_4 = 1;
  ExceptionList = &local_c;
  if (puVar1 != (undefined4 *)0x0) {
    if ((uint)(iVar2 - (int)puVar1) < 0x81) {
      ExceptionList = &local_c;
      FUN_004a94b0(&DAT_004ed050);
      *puVar1 = *(undefined4 *)(&DAT_004ec644 + ((iVar2 - (int)puVar1) - 1U >> 3) * 4);
      *(undefined4 **)(&DAT_004ec644 + ((iVar2 - (int)puVar1) - 1U >> 3) * 4) = puVar1;
      DAT_004ed050 = 0;
    }
    else {
      ExceptionList = &local_c;
      FUN_00430df0((undefined *)puVar1);
    }
  }
  local_4 = 0xffffffff;
  exception__dtor_exception(param_1);
  ExceptionList = local_c;
  return;
}


/* 004ae8d0 size=301 */

undefined4 * __thiscall FUN_004ae8d0(void *this,int param_1)

{
  undefined4 *puVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 *puVar4;
  uint uVar5;
  int iVar6;
  int unaff_EDI;
  char *pcVar7;
  undefined1 local_131;
  undefined1 *local_130;
  void *local_12c;
  undefined4 local_128 [3];
  undefined4 *local_11c;
  undefined1 local_118 [268];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004c9f57;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_12c = this;
  FUN_004bccd7(this,param_1);
  puVar1 = (undefined4 *)((int)this + 0xc);
  local_4 = 0;
  local_11c = puVar1;
  FUN_004a8710(&local_131);
  *puVar1 = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  local_130 = *(undefined1 **)(param_1 + 0xc);
  iVar6 = *(int *)(param_1 + 0x10) - (int)local_130;
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
  uVar5 = iVar6 + 1;
  if (uVar5 != 0) {
    puVar4 = (undefined1 *)FUN_004aa520(uVar5);
    *puVar1 = puVar4;
    *(undefined1 **)((int)this + 0x10) = puVar4;
    *(undefined1 **)((int)this + 0x14) = puVar4 + uVar5;
    if (0 < iVar6) {
      do {
        uVar3 = *local_130;
        local_130 = local_130 + 1;
        *puVar4 = uVar3;
        puVar4 = puVar4 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    *(undefined1 **)((int)this + 0x10) = puVar4;
    *puVar4 = 0;
    *(undefined ***)this = &PTR_FUN_004cec4c;
    ExceptionList = local_c;
    return this;
  }
  (*(uint8_t*)((char*)&local_4+0)) = 2;
  FUN_004a8730(local_128);
  uVar5 = 0xffffffff;
  (*(uint8_t*)((char*)&local_4+0)) = 3;
  pcVar7 = s_basic_string_004de5c8;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  FUN_004aa340(local_128,(undefined4 *)s_basic_string_004de5c8,
               (int)(s___AVAuth2Certificate_WONAPI___004de5a8 + ~uVar5 + 0x1f),unaff_EDI);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),4);
  FUN_004a7ed0(local_118,local_128);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_118,&DAT_004d0380);
}


/* 004af0d0 size=303 */

void __cdecl
FUN_004af0d0(void *param_1,void *param_2,int param_3,void *param_4,void *param_5,short param_6)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca078;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  BigInteger_4aec10(local_2c,param_2,param_4);
  iVar1 = FUN_004ad580(param_3);
  if ((**(byte **)(param_3 + 0x14) & 1) == 0) {
    FUN_004adb70((int)param_1);
  }
  else {
    BigInteger_4aec10(param_1,param_2,param_4);
  }
  puVar2 = (uint *)FUN_00430de0((uint)*(ushort *)((int)param_4 + 0x1a) * 0x18);
  iVar4 = 1;
  if (1 < iVar1) {
    do {
      BigInteger_4af410(local_2c,local_2c,local_2c,param_4,param_5,param_6,puVar2);
      iVar3 = FUN_004ad700(param_3,iVar4);
      if ((char)iVar3 != '\0') {
        BigInteger_4af410(param_1,param_1,local_2c,param_4,param_5,param_6,puVar2);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < iVar1);
  }
  FUN_00430df0((undefined *)puVar2);
  if (*(char *)(param_3 + 0x1c) != '\0') {
    BigInteger_4af670(param_1,param_1,param_4);
  }
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return;
}


/* 004af200 size=134 */

int __cdecl FUN_004af200(int *param_1,int param_2)

{
  int iVar1;
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca098;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  FUN_004adb70((int)local_2c);
  iVar1 = FUN_004ad580(param_2);
  FUN_004ae340(local_2c,(int)local_2c,iVar1 * 2);
  BigInteger_4aedf0(param_1,(int *)0x0,local_2c,param_2);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return iVar1 + 1;
}


/* 004af290 size=306 */

void __cdecl FUN_004af290(void *param_1,void *param_2,void *param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_4c [6];
  short local_32;
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca0c0;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  FUN_004afb30(local_4c);
  local_4 = CONCAT31((*(uint32_t*)((char*)&local_4+1)),1);
  FUN_004ad8a0(local_2c,param_2);
  FUN_004ad8a0(local_4c,param_3);
  uVar2 = 0;
  puVar4 = local_2c;
  puVar5 = local_4c;
  puVar3 = puVar4;
  if (local_32 != 0) {
    do {
      puVar4 = puVar3;
      if ((*(byte *)puVar3[5] & 1) == 0) {
        puVar6 = puVar3;
        if ((*(byte *)puVar5[5] & 1) != 0) goto LAB_004af33b;
        FUN_004ae450(puVar3,(int)puVar3,1);
        FUN_004ae450(puVar5,(int)puVar5,1);
        uVar2 = uVar2 + 1;
      }
      else if ((*(byte *)puVar5[5] & 1) == 0) {
        puVar6 = puVar5;
LAB_004af33b:
        FUN_004ae450(puVar6,(int)puVar6,1);
        iVar1 = FUN_004ae2c0((int)puVar3,(int)puVar5);
        if (iVar1 < 0) {
          puVar4 = puVar5;
          puVar5 = puVar3;
        }
      }
      else {
        FUN_004ae200(puVar3,puVar3,puVar5);
        FUN_004ae450(puVar3,(int)puVar3,1);
        iVar1 = FUN_004ae2c0((int)puVar3,(int)puVar5);
        if (iVar1 < 0) {
          puVar4 = puVar5;
          puVar5 = puVar3;
        }
      }
      puVar3 = puVar4;
    } while (*(short *)((int)puVar5 + 0x1a) != 0);
    if (0 < (int)uVar2) {
      FUN_004ae340(param_1,(int)puVar4,uVar2);
      goto LAB_004af39e;
    }
  }
  FUN_004ad8a0(param_1,puVar4);
LAB_004af39e:
  FUN_004ad860(local_4c);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return;
}


/* 004af3d0 size=60 */

void __cdecl FUN_004af3d0(void *param_1,void *param_2,void *param_3)

{
  int iVar1;
  
  iVar1 = FUN_004ae2c0((int)param_2,(int)param_3);
  if (iVar1 < 1) {
    FUN_004af290(param_1,param_3,param_2);
    return;
  }
  FUN_004af290(param_1,param_2,param_3);
  return;
}


/* 004afaa0 size=13 */

void FUN_004afaa0(void)

{
  FUN_004afb80(&DAT_004ec698,0);
  return;
}


/* 004afab0 size=12 */

void FUN_004afab0(void)

{
  FUN_004b9cf5(&LAB_004afac0);
  return;
}


/* 004afaf0 size=13 */

void FUN_004afaf0(void)

{
  FUN_004afb80(&DAT_004ec6b8,1);
  return;
}


/* 004afb00 size=12 */

void FUN_004afb00(void)

{
  FUN_004b9cf5(&LAB_004afb10);
  return;
}


/* 004afb30 size=18 */

undefined4 * __fastcall FUN_004afb30(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cec3c;
  FUN_004ad840(param_1);
  return param_1;
}


/* 004afb50 size=34 */

undefined4 * __thiscall FUN_004afb50(void *this,void *param_1)

{
  *(undefined ***)this = &PTR_FUN_004cec3c;
  FUN_004ad840(this);
  FUN_004ad8a0(this,param_1);
  return this;
}


/* 004afb80 size=66 */

undefined4 * __thiscall FUN_004afb80(void *this,int param_1)

{
  *(undefined ***)this = &PTR_FUN_004cec3c;
  FUN_004ad840(this);
  *(bool *)((int)this + 0x1c) = param_1 < 0;
  if (param_1 < 0) {
    **(int **)((int)this + 0x14) = -param_1;
  }
  else {
    **(int **)((int)this + 0x14) = param_1;
  }
  *(undefined2 *)((int)this + 0x1a) = 1;
  if (param_1 == 0) {
    *(undefined2 *)((int)this + 0x1a) = 0;
  }
  return this;
}


/* 004afbd0 size=32 */

undefined4 * __thiscall FUN_004afbd0(void *this,int *param_1)

{
  *(undefined ***)this = &PTR_FUN_004cec3c;
  FUN_004ad840(this);
  FUN_004ada70(this,param_1);
  return this;
}


/* 004afbf0 size=202 */

undefined4 * __thiscall FUN_004afbf0(void *this,int param_1,void *param_2)

{
  int *piVar1;
  undefined4 *local_18 [2];
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca220;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined ***)this = &PTR_FUN_004cec3c;
  FUN_004ad840(this);
  piVar1 = FUN_004ad5b0(local_18,param_1,param_2);
  local_4 = 0;
  FUN_004ada70(this,piVar1);
  local_4 = 1;
  if (local_18[0] != (undefined4 *)0x0) {
    if ((uint)(local_10 - (int)local_18[0]) < 0x81) {
      FUN_004a94b0(&DAT_004ed050);
      *local_18[0] = *(undefined4 *)(&DAT_004ec644 + ((local_10 - (int)local_18[0]) - 1U >> 3) * 4);
      *(undefined4 **)(&DAT_004ec644 + ((local_10 - (int)local_18[0]) - 1U >> 3) * 4) = local_18[0];
      DAT_004ed050 = 0;
      ExceptionList = local_c;
      return this;
    }
    FUN_00430df0((undefined *)local_18[0]);
  }
  ExceptionList = local_c;
  return this;
}


/* 004afcc0 size=23 */

void * __thiscall FUN_004afcc0(void *this,void *param_1)

{
  FUN_004ad8a0(this,param_1);
  return this;
}


/* 004afce0 size=17 */

int __thiscall FUN_004afce0(void *this,int param_1)

{
  FUN_004ad700((int)this,param_1);
  return;
}


/* 004afd00 size=23 */

int __thiscall FUN_004afd00(void *this,int param_1)

{
  FUN_004ad750((int)this,param_1);
  return (int)this;
}


/* 004afd20 size=116 */

void * __thiscall FUN_004afd20(void *this,void *param_1,void *param_2)

{
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca238;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  FUN_004af3d0(local_2c,this,param_2);
  FUN_004afb50(param_1,local_2c);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return param_1;
}


/* 004afda0 size=10 */

int __fastcall FUN_004afda0(int param_1)

{
  FUN_004ad580(param_1);
  return;
}


/* 004afdb0 size=131 */

void * __thiscall
FUN_004afdb0(void *this,void *param_1,int param_2,void *param_3,void *param_4,short param_5)

{
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca258;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  FUN_004af0d0(local_2c,this,param_2,param_3,param_4,param_5);
  FUN_004afb50(param_1,local_2c);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return param_1;
}


/* 004afe40 size=116 */

void * __thiscall FUN_004afe40(void *this,void *param_1,void *param_2)

{
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca278;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  BigInteger_4af670(local_2c,this,param_2);
  FUN_004afb50(param_1,local_2c);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return param_1;
}


/* 004afec0 size=116 */

void * __thiscall FUN_004afec0(void *this,void *param_1,void *param_2)

{
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca298;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  BigInteger_4aec10(local_2c,this,param_2);
  FUN_004afb50(param_1,local_2c);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return param_1;
}


/* 004aff40 size=116 */

void * __thiscall FUN_004aff40(void *this,void *param_1,void *param_2)

{
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca2b8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  FUN_004ae170(local_2c,this,param_2);
  FUN_004afb50(param_1,local_2c);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return param_1;
}


/* 004affc0 size=116 */

void * __thiscall FUN_004affc0(void *this,void *param_1,void *param_2)

{
  undefined4 local_2c [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004ca2d8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004afb30(local_2c);
  local_4 = 0;
  FUN_004ae200(local_2c,this,param_2);
  FUN_004afb50(param_1,local_2c);
  FUN_004ad860(local_2c);
  ExceptionList = local_c;
  return param_1;
}


