/* lithtech.exe decompilation - module unnamed_004c */
#include "ghidra_types.h"

/* 004c0218 size=43 */

/* Library Function - Single Match
    __freebuf
   
   Library: Visual Studio 2003 Release */

void __cdecl __freebuf(FILE *_File)

{
  if (((_File->_flag & 0x83U) != 0) && ((_File->_flag & 8U) != 0)) {
    FUN_004b9d3f(_File->_base);
    *(ushort *)&_File->_flag = (ushort)_File->_flag & 0xfbf7;
    _File->_ptr = (char *)0x0;
    _File->_base = (char *)0x0;
    _File->_cnt = 0;
  }
  return;
}


/* 004c1096 size=18 */

/* Library Function - Single Match
    __frnd
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release,
   Visual Studio 2019 Release */

float10 __cdecl __frnd(double param_1)

{
  return (float10)ROUND(param_1);
}


/* 004c1430 size=103 */

/* Library Function - Single Match
    __trandisp1
   
   Library: Visual Studio */

/* __trandisp1: lifted from original x86 -> lt_lifted.c */


/* 004c1497 size=140 */

/* Library Function - Single Match
    __trandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2005, Visual Studio 2008 */

/* __trandisp2: lifted from original x86 -> lt_lifted.c */


/* 004c1617 size=60 */

/* Library Function - Single Match
    __startOneArgErrorHandling
   
   Library: Visual Studio */

float10 __fastcall
__startOneArgErrorHandling
          (undefined4 param_1,uint param_2,ushort param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6)

{
  float10 in_ST0;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  double local_c;
  
  local_c = (double)in_ST0;
  local_1c = param_5;
  local_18 = param_6;
  local_20 = param_1;
  FUN_004c6da2(param_2,&local_24,&param_3);
  return (float10)local_c;
}


/* 004c170b size=42 */

/* Library Function - Single Match
    __math_exit
   
   Library: Visual Studio */

void __fastcall
__math_exit(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
           )

{
  ushort in_FPUStatusWord;
  ushort unaff_retaddr;
  
  if (((unaff_retaddr == 0x27f) || ((unaff_retaddr & 0x20) == 0)) ||
     ((in_FPUStatusWord & 0x20) == 0)) {
    return;
  }
  __startOneArgErrorHandling(param_1,param_2,unaff_retaddr,param_3,param_4,param_5);
  return;
}


/* 004c30a0 size=76 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* Library Function - Single Match
    __CallSettingFrame@12
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

int __CallSettingFrame_12(undefined4 param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  
  pcVar1 = (code *)__NLG_Notify1(param_3);
  (*pcVar1)();
  if (param_3 == 0x100) {
    param_3 = 2;
  }
  __NLG_Notify1(param_3);
  return;
}


/* 004c3780 size=62 */

/* Library Function - Single Match
    __cintrindisp2
   
   Library: Visual Studio */

void __fastcall __cintrindisp2(undefined4 param_1,int param_2)

{
  __trandisp2(param_1,param_2);
  FUN_004c384a();
  return;
}


/* 004c37be size=61 */

/* Library Function - Single Match
    __cintrindisp1
   
   Library: Visual Studio */

void __fastcall __cintrindisp1(undefined4 param_1,int param_2)

{
  __trandisp1(param_1,param_2);
  FUN_004c384a();
  return;
}


/* 004c37fb size=72 */

/* Library Function - Single Match
    __ctrandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2005, Visual Studio 2008 */

void __cdecl __ctrandisp2(uint param_1,int param_2,uint param_3,int param_4)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  
  __fload(param_1,param_2);
  __fload(param_3,param_4);
  __trandisp2(extraout_ECX,extraout_EDX);
  FUN_004c3843();
  return;
}


/* 004c397b size=51 */

/* Library Function - Single Match
    __ctrandisp1
   
   Library: Visual Studio */

void __cdecl __ctrandisp1(uint param_1,int param_2)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  
  __fload(param_1,param_2);
  __trandisp1(extraout_ECX,extraout_EDX);
  FUN_004c3843();
  return;
}


/* 004c39ae size=60 */

/* Library Function - Single Match
    __fload
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2005, Visual Studio 2008 */

float10 __cdecl __fload(uint param_1,int param_2)

{
  float10 fVar1;
  
  if (((*(uint16_t*)((char*)&param_2+2)) & 0x7ff0) == 0x7ff0) {
    fVar1 = (float10)CONCAT28((*(uint16_t*)((char*)&param_2+2)) | 0x7fff,
                              CONCAT44(param_2 << 0xb | param_1 >> 0x15,param_1));
  }
  else {
    fVar1 = (float10)(double)CONCAT26((*(uint16_t*)((char*)&param_2+2)),CONCAT24((undefined2)param_2,param_1));
  }
  return fVar1;
}


/* 004c4b70 size=129 */

/* Library Function - Single Match
    _strcmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strcmp(char *_Str1,char *_Str2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  byte bVar3;
  bool bVar4;
  
  if (((uint)_Str1 & 3) != 0) {
    if (((uint)_Str1 & 1) != 0) {
      bVar3 = *_Str1;
      _Str1 = _Str1 + 1;
      bVar4 = bVar3 < (byte)*_Str2;
      if (bVar3 != *_Str2) goto LAB_004c4bb4;
      _Str2 = _Str2 + 1;
      if (bVar3 == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_004c4b80;
    }
    uVar1 = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    bVar3 = (byte)uVar1;
    bVar4 = bVar3 < (byte)*_Str2;
    if (bVar3 != *_Str2) goto LAB_004c4bb4;
    if (bVar3 == 0) {
      return 0;
    }
    bVar3 = (byte)((ushort)uVar1 >> 8);
    bVar4 = bVar3 < (byte)_Str2[1];
    if (bVar3 != _Str2[1]) goto LAB_004c4bb4;
    if (bVar3 == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_004c4b80:
  while( true ) {
    uVar2 = *(undefined4 *)_Str1;
    bVar3 = (byte)uVar2;
    bVar4 = bVar3 < (byte)*_Str2;
    if (bVar3 != *_Str2) break;
    if (bVar3 == 0) {
      return 0;
    }
    bVar3 = (byte)((uint)uVar2 >> 8);
    bVar4 = bVar3 < (byte)_Str2[1];
    if (bVar3 != _Str2[1]) break;
    if (bVar3 == 0) {
      return 0;
    }
    bVar3 = (byte)((uint)uVar2 >> 0x10);
    bVar4 = bVar3 < (byte)_Str2[2];
    if (bVar3 != _Str2[2]) break;
    if (bVar3 == 0) {
      return 0;
    }
    bVar3 = (byte)((uint)uVar2 >> 0x18);
    bVar4 = bVar3 < (byte)_Str2[3];
    if (bVar3 != _Str2[3]) break;
    _Str2 = _Str2 + 4;
    _Str1 = _Str1 + 4;
    if (bVar3 == 0) {
      return 0;
    }
  }
LAB_004c4bb4:
  return (uint)bVar4 * -2 + 1;
}


/* 004c5db0 size=88 */

/* Library Function - Single Match
    _memset
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

void * __cdecl _memset(void *_Dst,int _Val,size_t _Size)

{
  uint uVar1;
  uint uVar2;
  size_t sVar3;
  uint *puVar4;
  
  if (_Size == 0) {
    return _Dst;
  }
  uVar1 = _Val & 0xff;
  puVar4 = _Dst;
  if (3 < _Size) {
    uVar2 = -(int)_Dst & 3;
    sVar3 = _Size;
    if (uVar2 != 0) {
      sVar3 = _Size - uVar2;
      do {
        *(undefined1 *)puVar4 = (undefined1)_Val;
        puVar4 = (uint *)((int)puVar4 + 1);
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    uVar1 = uVar1 * 0x1010101;
    _Size = sVar3 & 3;
    uVar2 = sVar3 >> 2;
    if (uVar2 != 0) {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
      }
      if (_Size == 0) {
        return _Dst;
      }
    }
  }
  do {
    *(char *)puVar4 = (char)uVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
    _Size = _Size - 1;
  } while (_Size != 0);
  return _Dst;
}


/* 004c6160 size=117 */

/* Library Function - Single Match
    __aullrem
   
   Library: Visual Studio */

undefined8 __aullrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  bool bVar10;
  
  if (param_4 == 0) {
    iVar7 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
    iVar8 = 0;
  }
  else {
    uVar5 = param_1;
    uVar6 = param_4;
    uVar9 = param_2;
    uVar4 = param_3;
    do {
      uVar3 = uVar6 & 1;
      uVar6 = uVar6 >> 1;
      uVar4 = (uint)(CONCAT14(uVar3 != 0,uVar4) >> 1);
      uVar3 = uVar9 & 1;
      uVar9 = uVar9 >> 1;
      uVar5 = (uint)(CONCAT14(uVar3 != 0,uVar5) >> 1);
    } while (uVar6 != 0);
    uVar1 = CONCAT44(uVar9,uVar5) / (ulonglong)uVar4;
    uVar4 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar6 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar5 = (uint)lVar2;
    uVar9 = uVar6 + uVar4;
    if (((CARRY4(uVar6,uVar4)) || (param_2 < uVar9)) || ((param_2 <= uVar9 && (param_1 < uVar5)))) {
      bVar10 = uVar5 < param_3;
      uVar5 = uVar5 - param_3;
      uVar9 = (uVar9 - param_4) - (uint)bVar10;
    }
    iVar7 = -(uVar5 - param_1);
    iVar8 = -(uint)(uVar5 - param_1 != 0) - ((uVar9 - param_2) - (uint)(uVar5 < param_1));
  }
  return CONCAT44(iVar8,iVar7);
}


/* 004c7560 size=31 */

/* Library Function - Single Match
    __allshl
   
   Library: Visual Studio */

longlong __fastcall __allshl(byte param_1,int param_2)

{
  uint in_EAX;
  
  if (0x3f < param_1) {
    return 0;
  }
  if (param_1 < 0x20) {
    return CONCAT44(param_2 << (param_1 & 0x1f) | in_EAX >> 0x20 - (param_1 & 0x1f),
                    in_EAX << (param_1 & 0x1f));
  }
  return (ulonglong)(in_EAX << (param_1 & 0x1f)) << 0x20;
}


/* 004c7ab8 size=94 */

/* Library Function - Single Match
    ___add_12
   
   Library: Visual Studio 2003 Release */

void __cdecl ___add_12(uint *param_1,uint *param_2)

{
  int iVar1;
  
  iVar1 = FUN_004c7a97(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_004c7a97(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = FUN_004c7a97(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  FUN_004c7a97(param_1[2],param_2[2],param_1 + 2);
  return;
}


/* 004c8472 size=63 */

/* Library Function - Single Match
    __mbsnbicoll
   
   Library: Visual Studio 2003 Release */

int __cdecl __mbsnbicoll(uchar *_Str1,uchar *_Str2,size_t _MaxCount)

{
  int iVar1;
  
  if (_MaxCount == 0) {
    return 0;
  }
  iVar1 = FUN_004c851f(DAT_004ed284,1,_Str1,_MaxCount,_Str2,_MaxCount,DAT_004ed058);
  if (iVar1 == 0) {
    return 0x7fffffff;
  }
  return iVar1 + -2;
}


/* 004c8fe0 size=8 */

void Unwind_004c8fe0(void)

{
  int unaff_EBP;
  
  FUN_004a4b20(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c8fe8 size=11 */

void Unwind_004c8fe8(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(*(int *)(unaff_EBP + -0x10) + 8));
  return;
}


/* 004c8ff3 size=11 */

void Unwind_004c8ff3(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


/* 004c9010 size=8 */

void Unwind_004c9010(void)

{
  int unaff_EBP;
  
  FUN_004a4b20(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9040 size=8 */

void Unwind_004c9040(void)

{
  int unaff_EBP;
  
  FUN_004a4b70(*(undefined4 **)(unaff_EBP + -0x18));
  return;
}


/* 004c9048 size=8 */

void Unwind_004c9048(void)

{
  int unaff_EBP;
  
  FUN_004a4fa0(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c9050 size=14 */

void Unwind_004c9050(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0xd0));
  return;
}


/* 004c905e size=14 */

void Unwind_004c905e(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0xf0));
  return;
}


/* 004c906c size=14 */

void Unwind_004c906c(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x110));
  return;
}


/* 004c907a size=14 */

void Unwind_004c907a(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x130));
  return;
}


/* 004c9088 size=14 */

void Unwind_004c9088(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x150));
  return;
}


/* 004c9096 size=8 */

void Unwind_004c9096(void)

{
  int unaff_EBP;
  
  FUN_004a8010(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c909e size=11 */

void Unwind_004c909e(void)

{
  int unaff_EBP;
  
  FUN_004a5080((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x10));
  return;
}


/* 004c90a9 size=11 */

void Unwind_004c90a9(void)

{
  FUN_004a82f0();
  return;
}


/* 004c90b4 size=11 */

void Unwind_004c90b4(void)

{
  FUN_004a82f0();
  return;
}


/* 004c90bf size=11 */

void Unwind_004c90bf(void)

{
  FUN_004a82f0();
  return;
}


/* 004c90e0 size=8 */

void Unwind_004c90e0(void)

{
  int unaff_EBP;
  
  FUN_004a4b70(*(undefined4 **)(unaff_EBP + -0x18));
  return;
}


/* 004c90e8 size=8 */

void Unwind_004c90e8(void)

{
  int unaff_EBP;
  
  FUN_004a4fa0(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c90f0 size=14 */

void Unwind_004c90f0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0xd0));
  return;
}


/* 004c90fe size=14 */

void Unwind_004c90fe(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0xf0));
  return;
}


/* 004c910c size=14 */

void Unwind_004c910c(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x110));
  return;
}


/* 004c911a size=14 */

void Unwind_004c911a(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x130));
  return;
}


/* 004c9128 size=14 */

void Unwind_004c9128(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x150));
  return;
}


/* 004c9136 size=8 */

void Unwind_004c9136(void)

{
  int unaff_EBP;
  
  FUN_004a8010(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c913e size=11 */

void Unwind_004c913e(void)

{
  int unaff_EBP;
  
  FUN_004a5080((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x10));
  return;
}


/* 004c9149 size=11 */

void Unwind_004c9149(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9154 size=11 */

void Unwind_004c9154(void)

{
  FUN_004a82f0();
  return;
}


/* 004c915f size=11 */

void Unwind_004c915f(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9180 size=8 */

void Unwind_004c9180(void)

{
  int unaff_EBP;
  
  FUN_004a8010(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c9188 size=11 */

void Unwind_004c9188(void)

{
  int unaff_EBP;
  
  FUN_004a5080((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x10));
  return;
}


/* 004c9193 size=11 */

void Unwind_004c9193(void)

{
  FUN_004a82f0();
  return;
}


/* 004c919e size=11 */

void Unwind_004c919e(void)

{
  FUN_004a82f0();
  return;
}


/* 004c91a9 size=11 */

void Unwind_004c91a9(void)

{
  FUN_004a82f0();
  return;
}


/* 004c91c0 size=11 */

void Unwind_004c91c0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c91e0 size=8 */

void Unwind_004c91e0(void)

{
  int unaff_EBP;
  
  FUN_004a4e90(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c91e8 size=14 */

void Unwind_004c91e8(void)

{
  int unaff_EBP;
  
  FUN_004a8260((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x1c0));
  return;
}


/* 004c91f6 size=14 */

void Unwind_004c91f6(void)

{
  int unaff_EBP;
  
  FUN_004a53e0((int *)(*(int *)(unaff_EBP + -0x14) + 0x1cc));
  return;
}


/* 004c9204 size=14 */

void Unwind_004c9204(void)

{
  int unaff_EBP;
  
  FUN_004a5490((int *)(*(int *)(unaff_EBP + -0x14) + 0x1d8));
  return;
}


/* 004c9212 size=14 */

void Unwind_004c9212(void)

{
  int unaff_EBP;
  
  FUN_004a5540((int *)(*(int *)(unaff_EBP + -0x14) + 0x1e4));
  return;
}


/* 004c9220 size=8 */

void Unwind_004c9220(void)

{
  int unaff_EBP;
  
  FUN_004a91b0(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9228 size=8 */

void Unwind_004c9228(void)

{
  int unaff_EBP;
  
  FUN_004a9120(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9230 size=8 */

void Unwind_004c9230(void)

{
  int unaff_EBP;
  
  FUN_004a9090(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9238 size=8 */

void Unwind_004c9238(void)

{
  int unaff_EBP;
  
  FUN_004a8f60(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9240 size=11 */

void Unwind_004c9240(void)

{
  FUN_004a82f0();
  return;
}


/* 004c924b size=8 */

void Unwind_004c924b(void)

{
  int unaff_EBP;
  
  FUN_004a4b70(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c9253 size=8 */

void Unwind_004c9253(void)

{
  int unaff_EBP;
  
  FUN_004a4fa0(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c925b size=14 */

void Unwind_004c925b(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0xd0));
  return;
}


/* 004c9269 size=14 */

void Unwind_004c9269(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0xf0));
  return;
}


/* 004c9277 size=14 */

void Unwind_004c9277(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x110));
  return;
}


/* 004c9285 size=14 */

void Unwind_004c9285(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x130));
  return;
}


/* 004c9293 size=14 */

void Unwind_004c9293(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x150));
  return;
}


/* 004c92b0 size=8 */

void Unwind_004c92b0(void)

{
  int unaff_EBP;
  
  FUN_004a8f60(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c92b8 size=8 */

void Unwind_004c92b8(void)

{
  FUN_004a82f0();
  return;
}


/* 004c92d0 size=8 */

void Unwind_004c92d0(void)

{
  int unaff_EBP;
  
  FUN_004a9090(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c92d8 size=8 */

void Unwind_004c92d8(void)

{
  FUN_004a82f0();
  return;
}


/* 004c92f0 size=8 */

void Unwind_004c92f0(void)

{
  int unaff_EBP;
  
  FUN_004a9120(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c92f8 size=8 */

void Unwind_004c92f8(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9310 size=8 */

void Unwind_004c9310(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x58));
  return;
}


/* 004c9318 size=11 */

void Unwind_004c9318(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x84));
  return;
}


/* 004c9323 size=8 */

void Unwind_004c9323(void)

{
  int unaff_EBP;
  
  FUN_004a86e0(unaff_EBP + -0x48);
  return;
}


/* 004c932b size=11 */

void Unwind_004c932b(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9336 size=8 */

void Unwind_004c9336(void)

{
  int unaff_EBP;
  
  FUN_004a8260((undefined4 *)(unaff_EBP + -0x7c));
  return;
}


/* 004c933e size=11 */

void Unwind_004c933e(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9349 size=8 */

void Unwind_004c9349(void)

{
  int unaff_EBP;
  
  FUN_004a8260((undefined4 *)(unaff_EBP + -0x70));
  return;
}


/* 004c9351 size=8 */

void Unwind_004c9351(void)

{
  int unaff_EBP;
  
  FUN_004a8260((undefined4 *)(unaff_EBP + -0x38));
  return;
}


/* 004c9359 size=8 */

void Unwind_004c9359(void)

{
  int unaff_EBP;
  
  FUN_004a85f0((undefined4 *)(unaff_EBP + -0x24));
  return;
}


/* 004c9370 size=11 */

void Unwind_004c9370(void)

{
  FUN_004a82f0();
  return;
}


/* 004c937b size=11 */

void Unwind_004c937b(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c9386 size=11 */

void Unwind_004c9386(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c93a0 size=8 */

void Unwind_004c93a0(void)

{
  int unaff_EBP;
  
  FUN_004a4fa0(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c93a8 size=14 */

void Unwind_004c93a8(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0xd0));
  return;
}


/* 004c93b6 size=14 */

void Unwind_004c93b6(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0xf0));
  return;
}


/* 004c93c4 size=14 */

void Unwind_004c93c4(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x110));
  return;
}


/* 004c93d2 size=14 */

void Unwind_004c93d2(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x130));
  return;
}


/* 004c93e0 size=14 */

void Unwind_004c93e0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x150));
  return;
}


/* 004c93ee size=8 */

void Unwind_004c93ee(void)

{
  int unaff_EBP;
  
  FUN_004a8010(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c93f6 size=11 */

void Unwind_004c93f6(void)

{
  int unaff_EBP;
  
  FUN_004a5080((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x10));
  return;
}


/* 004c9401 size=11 */

void Unwind_004c9401(void)

{
  FUN_004a82f0();
  return;
}


/* 004c940c size=11 */

void Unwind_004c940c(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9417 size=11 */

void Unwind_004c9417(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9430 size=8 */

void Unwind_004c9430(void)

{
  int unaff_EBP;
  
  FUN_004a91b0(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9438 size=8 */

void Unwind_004c9438(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9450 size=8 */

void Unwind_004c9450(void)

{
  int unaff_EBP;
  
  FUN_0048a6c0(unaff_EBP + 0xc);
  return;
}


/* 004c9458 size=8 */

void Unwind_004c9458(void)

{
  int unaff_EBP;
  
  FUN_004a4b20(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c9460 size=11 */

void Unwind_004c9460(void)

{
  FUN_004a82f0();
  return;
}


/* 004c946b size=8 */

void Unwind_004c946b(void)

{
  int unaff_EBP;
  
  FUN_004a8b90(*(undefined4 **)(unaff_EBP + 8));
  return;
}


/* 004c9473 size=14 */

void Unwind_004c9473(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(*(int *)(unaff_EBP + 4) + 0x1048));
  return;
}


/* 004c9481 size=8 */

void Unwind_004c9481(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9489 size=8 */

void Unwind_004c9489(void)

{
  int unaff_EBP;
  
  FUN_004a8b90(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9491 size=11 */

void Unwind_004c9491(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + 0x1054));
  return;
}


/* 004c949c size=14 */

void Unwind_004c949c(void)

{
  FUN_004a82f0();
  return;
}


/* 004c94aa size=14 */

void Unwind_004c94aa(void)

{
  FUN_004a82f0();
  return;
}


/* 004c94d0 size=8 */

void Unwind_004c94d0(void)

{
  int unaff_EBP;
  
  FUN_004a4b20(*(undefined4 **)(unaff_EBP + -0x18));
  return;
}


/* 004c94d8 size=14 */

void Unwind_004c94d8(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x1048));
  return;
}


/* 004c94e6 size=11 */

void Unwind_004c94e6(void)

{
  FUN_004a82f0();
  return;
}


/* 004c94f1 size=11 */

void Unwind_004c94f1(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9510 size=8 */

void Unwind_004c9510(void)

{
  int unaff_EBP;
  
  FUN_004a4b70(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9530 size=8 */

void Unwind_004c9530(void)

{
  int unaff_EBP;
  
  FUN_004a80a0(*(int **)(unaff_EBP + -0x10));
  return;
}


/* 004c9538 size=11 */

void Unwind_004c9538(void)

{
  int unaff_EBP;
  
  FUN_0048a6c0(*(int *)(unaff_EBP + -0x10) + 8);
  return;
}


/* 004c9543 size=14 */

void Unwind_004c9543(void)

{
  int unaff_EBP;
  
  FUN_0048a6c0(*(int *)(unaff_EBP + -0x10) + 0x10b4);
  return;
}


/* 004c9551 size=14 */

void Unwind_004c9551(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(*(int *)(unaff_EBP + -0x10) + 0x2164));
  return;
}


/* 004c955f size=14 */

void Unwind_004c955f(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(*(int *)(unaff_EBP + -0x10) + 0x2168));
  return;
}


/* 004c9580 size=8 */

void Unwind_004c9580(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + 4));
  return;
}


/* 004c9588 size=11 */

void Unwind_004c9588(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -0x10));
  return;
}


/* 004c9593 size=8 */

void Unwind_004c9593(void)

{
  int unaff_EBP;
  
  FUN_004a4e90(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c959b size=14 */

void Unwind_004c959b(void)

{
  int unaff_EBP;
  
  FUN_004a8260((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x1c0));
  return;
}


/* 004c95a9 size=14 */

void Unwind_004c95a9(void)

{
  int unaff_EBP;
  
  FUN_004a53e0((int *)(*(int *)(unaff_EBP + -0x10) + 0x1cc));
  return;
}


/* 004c95b7 size=14 */

void Unwind_004c95b7(void)

{
  int unaff_EBP;
  
  FUN_004a5490((int *)(*(int *)(unaff_EBP + -0x10) + 0x1d8));
  return;
}


/* 004c95c5 size=14 */

void Unwind_004c95c5(void)

{
  int unaff_EBP;
  
  FUN_004a5540((int *)(*(int *)(unaff_EBP + -0x10) + 0x1e4));
  return;
}


/* 004c95d3 size=14 */

void Unwind_004c95d3(void)

{
  int unaff_EBP;
  
  FUN_004a5ee0((int *)(*(int *)(unaff_EBP + -0x10) + 0x1f0));
  return;
}


/* 004c95e1 size=11 */

void Unwind_004c95e1(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -0x10));
  return;
}


/* 004c95ec size=8 */

void Unwind_004c95ec(void)

{
  int unaff_EBP;
  
  FUN_004a4e90(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9600 size=8 */

void Unwind_004c9600(void)

{
  int unaff_EBP;
  
  FUN_004ad230((undefined4 *)(unaff_EBP + -0x20));
  return;
}


/* 004c9608 size=8 */

void Unwind_004c9608(void)

{
  int unaff_EBP;
  
  FUN_004ad230((undefined4 *)(unaff_EBP + -0x34));
  return;
}


/* 004c9610 size=8 */

void Unwind_004c9610(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x3c));
  return;
}


/* 004c9618 size=8 */

void Unwind_004c9618(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x38));
  return;
}


/* 004c9630 size=8 */

void Unwind_004c9630(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9638 size=8 */

void Unwind_004c9638(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004c9640 size=8 */

void Unwind_004c9640(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x20));
  return;
}


/* 004c9648 size=11 */

void Unwind_004c9648(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


/* 004c9660 size=8 */

void Unwind_004c9660(void)

{
  int unaff_EBP;
  
  FUN_004a8b90(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9668 size=14 */

void Unwind_004c9668(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x1048));
  return;
}


/* 004c9676 size=8 */

void Unwind_004c9676(void)

{
  int unaff_EBP;
  
  FUN_004a8b90(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9690 size=8 */

void Unwind_004c9690(void)

{
  int unaff_EBP;
  
  FUN_004ad230((undefined4 *)(unaff_EBP + -0x20));
  return;
}


/* 004c9698 size=23 */

void Unwind_004c9698(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x24) & 1) == 0) {
    return;
  }
  FUN_004a80a0(*(int **)(unaff_EBP + 4));
  return;
}


/* 004c96d0 size=8 */

void Unwind_004c96d0(void)

{
  int unaff_EBP;
  
  FUN_004a80a0(*(int **)(unaff_EBP + -0x10));
  return;
}


/* 004c96d8 size=11 */

void Unwind_004c96d8(void)

{
  int unaff_EBP;
  
  FUN_0048a6c0(*(int *)(unaff_EBP + -0x10) + 8);
  return;
}


/* 004c96f0 size=8 */

void Unwind_004c96f0(void)

{
  int unaff_EBP;
  
  FUN_004ad230((undefined4 *)(unaff_EBP + -0x34));
  return;
}


/* 004c96f8 size=8 */

void Unwind_004c96f8(void)

{
  int unaff_EBP;
  
  FUN_004ad230((undefined4 *)(unaff_EBP + -0x20));
  return;
}


/* 004c9700 size=8 */

void Unwind_004c9700(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x3c));
  return;
}


/* 004c9708 size=8 */

void Unwind_004c9708(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x38));
  return;
}


/* 004c9710 size=8 */

void Unwind_004c9710(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x38));
  return;
}


/* 004c9718 size=8 */

void Unwind_004c9718(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x38));
  return;
}


/* 004c9730 size=11 */

void Unwind_004c9730(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


/* 004c973b size=8 */

void Unwind_004c973b(void)

{
  int unaff_EBP;
  
  FUN_004a4e90(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004c9743 size=14 */

void Unwind_004c9743(void)

{
  int unaff_EBP;
  
  FUN_004a8260((undefined4 *)(*(int *)(unaff_EBP + 4) + 0x1c0));
  return;
}


/* 004c9751 size=8 */

void Unwind_004c9751(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9759 size=14 */

void Unwind_004c9759(void)

{
  int unaff_EBP;
  
  FUN_004a53e0((int *)(*(int *)(unaff_EBP + 4) + 0x1cc));
  return;
}


/* 004c9767 size=14 */

void Unwind_004c9767(void)

{
  int unaff_EBP;
  
  FUN_004a5490((int *)(*(int *)(unaff_EBP + 4) + 0x1d8));
  return;
}


/* 004c9775 size=14 */

void Unwind_004c9775(void)

{
  int unaff_EBP;
  
  FUN_004a5540((int *)(*(int *)(unaff_EBP + 4) + 0x1e4));
  return;
}


/* 004c9783 size=14 */

void Unwind_004c9783(void)

{
  int unaff_EBP;
  
  FUN_004a5ee0((int *)(*(int *)(unaff_EBP + 4) + 0x1f0));
  return;
}


/* 004c9791 size=11 */

void Unwind_004c9791(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


/* 004c979c size=8 */

void Unwind_004c979c(void)

{
  int unaff_EBP;
  
  FUN_004a4e90(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004c97b0 size=8 */

void Unwind_004c97b0(void)

{
  int unaff_EBP;
  
  FUN_004ad230((undefined4 *)(unaff_EBP + -0x20));
  return;
}


/* 004c97b8 size=8 */

void Unwind_004c97b8(void)

{
  FUN_004a82f0();
  return;
}


/* 004c97c0 size=8 */

void Unwind_004c97c0(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x34));
  return;
}


/* 004c97c8 size=8 */

void Unwind_004c97c8(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x34));
  return;
}


/* 004c97d0 size=8 */

void Unwind_004c97d0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c97d8 size=8 */

void Unwind_004c97d8(void)

{
  int unaff_EBP;
  
  FUN_004ad230((undefined4 *)(unaff_EBP + -0x34));
  return;
}


/* 004c97e0 size=8 */

void Unwind_004c97e0(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + 4));
  return;
}


/* 004c97e8 size=11 */

void Unwind_004c97e8(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -0x3c));
  return;
}


/* 004c97f3 size=8 */

void Unwind_004c97f3(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + -0x3c));
  return;
}


/* 004c9810 size=8 */

void Unwind_004c9810(void)

{
  int unaff_EBP;
  
  FUN_004a80a0((int *)(unaff_EBP + 4));
  return;
}


/* 004c9840 size=11 */

void Unwind_004c9840(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9860 size=11 */

void Unwind_004c9860(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9880 size=8 */

void Unwind_004c9880(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9888 size=11 */

void Unwind_004c9888(void)

{
  FUN_004a82f0();
  return;
}


/* 004c98a0 size=11 */

void Unwind_004c98a0(void)

{
  int unaff_EBP;
  
  FUN_004a8dc0(*(undefined4 **)(unaff_EBP + -0x128));
  return;
}


/* 004c98ab size=11 */

void Unwind_004c98ab(void)

{
  FUN_004a82f0();
  return;
}


/* 004c98b6 size=11 */

void Unwind_004c98b6(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c98c1 size=11 */

void Unwind_004c98c1(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c98e0 size=11 */

void Unwind_004c98e0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9900 size=8 */

void Unwind_004c9900(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9908 size=8 */

void Unwind_004c9908(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9910 size=8 */

void Unwind_004c9910(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9930 size=8 */

void Unwind_004c9930(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9938 size=8 */

void Unwind_004c9938(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9940 size=8 */

void Unwind_004c9940(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9960 size=8 */

void Unwind_004c9960(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9968 size=8 */

void Unwind_004c9968(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9970 size=8 */

void Unwind_004c9970(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9990 size=8 */

void Unwind_004c9990(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9998 size=8 */

void Unwind_004c9998(void)

{
  FUN_004a82f0();
  return;
}


/* 004c99a0 size=8 */

void Unwind_004c99a0(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c99c0 size=8 */

void Unwind_004c99c0(void)

{
  int unaff_EBP;
  
  FUN_004a8260(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c99c8 size=11 */

void Unwind_004c99c8(void)

{
  FUN_004a82f0();
  return;
}


/* 004c99d3 size=11 */

void Unwind_004c99d3(void)

{
  FUN_004a82f0();
  return;
}


/* 004c99f0 size=14 */

void Unwind_004c99f0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c99fe size=8 */

void Unwind_004c99fe(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9a06 size=11 */

void Unwind_004c9a06(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9a11 size=11 */

void Unwind_004c9a11(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c9a1c size=11 */

void Unwind_004c9a1c(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c9a40 size=11 */

void Unwind_004c9a40(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9a60 size=14 */

void Unwind_004c9a60(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9a6e size=8 */

void Unwind_004c9a6e(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9a76 size=11 */

void Unwind_004c9a76(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9a81 size=11 */

void Unwind_004c9a81(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c9a8c size=11 */

void Unwind_004c9a8c(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c9ab0 size=11 */

void Unwind_004c9ab0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9ad0 size=14 */

void Unwind_004c9ad0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9ade size=8 */

void Unwind_004c9ade(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9ae6 size=11 */

void Unwind_004c9ae6(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9af1 size=11 */

void Unwind_004c9af1(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c9afc size=11 */

void Unwind_004c9afc(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c9b20 size=11 */

void Unwind_004c9b20(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9b40 size=8 */

void Unwind_004c9b40(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9b48 size=8 */

void Unwind_004c9b48(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9b60 size=8 */

void Unwind_004c9b60(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9b80 size=8 */

void Unwind_004c9b80(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9ba0 size=8 */

void Unwind_004c9ba0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9bc0 size=8 */

void Unwind_004c9bc0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9be0 size=8 */

void Unwind_004c9be0(void)

{
  int unaff_EBP;
  
  FUN_004a8dc0(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9be8 size=8 */

void Unwind_004c9be8(void)

{
  int unaff_EBP;
  
  FUN_004a8260(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9bf0 size=8 */

void Unwind_004c9bf0(void)

{
  int unaff_EBP;
  
  FUN_004a8dc0(*(undefined4 **)(unaff_EBP + -0x14));
  return;
}


/* 004c9c10 size=11 */

void Unwind_004c9c10(void)

{
  int unaff_EBP;
  
  FUN_004a8920(*(undefined4 **)(unaff_EBP + -0x128));
  return;
}


/* 004c9c1b size=11 */

void Unwind_004c9c1b(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9c26 size=11 */

void Unwind_004c9c26(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x124));
  return;
}


/* 004c9c40 size=8 */

void Unwind_004c9c40(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9c60 size=8 */

void Unwind_004c9c60(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9c80 size=8 */

void Unwind_004c9c80(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9c88 size=17 */

void Unwind_004c9c88(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9c99 size=8 */

void Unwind_004c9c99(void)

{
  int unaff_EBP;
  
  FUN_004a8dc0(*(undefined4 **)(unaff_EBP + -0x1c));
  return;
}


/* 004c9ca1 size=8 */

void Unwind_004c9ca1(void)

{
  int unaff_EBP;
  
  FUN_004a8260(*(undefined4 **)(unaff_EBP + -0x1c));
  return;
}


/* 004c9cc0 size=8 */

void Unwind_004c9cc0(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9ce0 size=8 */

void Unwind_004c9ce0(void)

{
  FUN_004aa8d0();
  return;
}


/* 004c9d60 size=8 */

void Unwind_004c9d60(void)

{
  int unaff_EBP;
  
  FUN_004a4b20(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004c9d80 size=8 */

void Unwind_004c9d80(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9d88 size=8 */

void Unwind_004c9d88(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x30));
  return;
}


/* 004c9d90 size=8 */

void Unwind_004c9d90(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x30));
  return;
}


/* 004c9d98 size=8 */

void Unwind_004c9d98(void)

{
  int unaff_EBP;
  
  exception__dtor_exception((exception *)(unaff_EBP + -0x24));
  return;
}


/* 004c9da0 size=8 */

void Unwind_004c9da0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9da8 size=8 */

void Unwind_004c9da8(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004c9dc0 size=8 */

void Unwind_004c9dc0(void)

{
  int unaff_EBP;
  
  exception__dtor_exception(*(exception **)(unaff_EBP + -0x14));
  return;
}


/* 004c9dc8 size=11 */

void Unwind_004c9dc8(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9de0 size=11 */

void Unwind_004c9de0(void)

{
  int unaff_EBP;
  
  exception__dtor_exception(*(exception **)(unaff_EBP + -300));
  return;
}


/* 004c9deb size=11 */

void Unwind_004c9deb(void)

{
  int unaff_EBP;
  
  FUN_004a8920(*(undefined4 **)(unaff_EBP + -0x11c));
  return;
}


/* 004c9df6 size=11 */

void Unwind_004c9df6(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9e01 size=11 */

void Unwind_004c9e01(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x128));
  return;
}


/* 004c9e0c size=11 */

void Unwind_004c9e0c(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x128));
  return;
}


/* 004c9e30 size=11 */

void Unwind_004c9e30(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 8));
  return;
}


/* 004c9e50 size=11 */

void Unwind_004c9e50(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 8));
  return;
}


/* 004c9e70 size=8 */

void Unwind_004c9e70(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9e78 size=8 */

void Unwind_004c9e78(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9e80 size=8 */

void Unwind_004c9e80(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004c9e88 size=8 */

void Unwind_004c9e88(void)

{
  int unaff_EBP;
  
  FUN_004a8b90(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004c9e90 size=23 */

void Unwind_004c9e90(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x1c) & 1) == 0) {
    return;
  }
  FUN_004a8010(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004c9ea7 size=8 */

void Unwind_004c9ea7(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9ec0 size=8 */

void Unwind_004c9ec0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9ec8 size=8 */

void Unwind_004c9ec8(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x30));
  return;
}


/* 004c9ed0 size=8 */

void Unwind_004c9ed0(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x30));
  return;
}


/* 004c9ed8 size=8 */

void Unwind_004c9ed8(void)

{
  int unaff_EBP;
  
  exception__dtor_exception((exception *)(unaff_EBP + -0x24));
  return;
}


/* 004c9ee0 size=8 */

void Unwind_004c9ee0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9ee8 size=8 */

void Unwind_004c9ee8(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004c9f00 size=8 */

void Unwind_004c9f00(void)

{
  int unaff_EBP;
  
  exception__dtor_exception(*(exception **)(unaff_EBP + -0x14));
  return;
}


/* 004c9f08 size=11 */

void Unwind_004c9f08(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9f20 size=11 */

void Unwind_004c9f20(void)

{
  int unaff_EBP;
  
  exception__dtor_exception(*(exception **)(unaff_EBP + -300));
  return;
}


/* 004c9f2b size=11 */

void Unwind_004c9f2b(void)

{
  int unaff_EBP;
  
  FUN_004a8920(*(undefined4 **)(unaff_EBP + -0x11c));
  return;
}


/* 004c9f36 size=11 */

void Unwind_004c9f36(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9f41 size=11 */

void Unwind_004c9f41(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x128));
  return;
}


/* 004c9f4c size=11 */

void Unwind_004c9f4c(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x128));
  return;
}


/* 004c9f70 size=8 */

void Unwind_004c9f70(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9f78 size=8 */

void Unwind_004c9f78(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x30));
  return;
}


/* 004c9f80 size=8 */

void Unwind_004c9f80(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x30));
  return;
}


/* 004c9f88 size=8 */

void Unwind_004c9f88(void)

{
  int unaff_EBP;
  
  exception__dtor_exception((exception *)(unaff_EBP + -0x24));
  return;
}


/* 004c9f90 size=8 */

void Unwind_004c9f90(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9f98 size=8 */

void Unwind_004c9f98(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004c9fb0 size=8 */

void Unwind_004c9fb0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9fb8 size=8 */

void Unwind_004c9fb8(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x50));
  return;
}


/* 004c9fc0 size=8 */

void Unwind_004c9fc0(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x50));
  return;
}


/* 004c9fc8 size=8 */

void Unwind_004c9fc8(void)

{
  int unaff_EBP;
  
  exception__dtor_exception((exception *)(unaff_EBP + -0x44));
  return;
}


/* 004c9fd0 size=8 */

void Unwind_004c9fd0(void)

{
  FUN_004a82f0();
  return;
}


/* 004c9fd8 size=8 */

void Unwind_004c9fd8(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x38));
  return;
}


/* 004c9fe0 size=8 */

void Unwind_004c9fe0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca000 size=8 */

void Unwind_004ca000(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca008 size=8 */

void Unwind_004ca008(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0x50));
  return;
}


/* 004ca010 size=8 */

void Unwind_004ca010(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x50));
  return;
}


/* 004ca018 size=8 */

void Unwind_004ca018(void)

{
  int unaff_EBP;
  
  exception__dtor_exception((exception *)(unaff_EBP + -0x44));
  return;
}


/* 004ca020 size=8 */

void Unwind_004ca020(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca028 size=8 */

void Unwind_004ca028(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x38));
  return;
}


/* 004ca030 size=11 */

void Unwind_004ca030(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


/* 004ca03b size=11 */

void Unwind_004ca03b(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


/* 004ca046 size=8 */

void Unwind_004ca046(void)

{
  int unaff_EBP;
  
  FUN_004b3900((int *)(unaff_EBP + 4));
  return;
}


/* 004ca04e size=8 */

void Unwind_004ca04e(void)

{
  int unaff_EBP;
  
  FUN_004b3900((int *)(unaff_EBP + -0x54));
  return;
}


/* 004ca056 size=8 */

void Unwind_004ca056(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca070 size=8 */

void Unwind_004ca070(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca090 size=8 */

void Unwind_004ca090(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca0b0 size=8 */

void Unwind_004ca0b0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca0b8 size=8 */

void Unwind_004ca0b8(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x4c));
  return;
}


/* 004ca0d0 size=8 */

void Unwind_004ca0d0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x6c));
  return;
}


/* 004ca0d8 size=11 */

void Unwind_004ca0d8(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x8c));
  return;
}


/* 004ca0e3 size=8 */

void Unwind_004ca0e3(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca0eb size=8 */

void Unwind_004ca0eb(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x4c));
  return;
}


/* 004ca0f3 size=11 */

void Unwind_004ca0f3(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca0fe size=11 */

void Unwind_004ca0fe(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -0xb4));
  return;
}


/* 004ca109 size=11 */

void Unwind_004ca109(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0xb4));
  return;
}


/* 004ca114 size=11 */

void Unwind_004ca114(void)

{
  int unaff_EBP;
  
  exception__dtor_exception((exception *)(unaff_EBP + -0xa8));
  return;
}


/* 004ca11f size=11 */

void Unwind_004ca11f(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca12a size=11 */

void Unwind_004ca12a(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x9c));
  return;
}


/* 004ca140 size=11 */

void Unwind_004ca140(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0xec));
  return;
}


/* 004ca14b size=11 */

void Unwind_004ca14b(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x10c));
  return;
}


/* 004ca156 size=11 */

void Unwind_004ca156(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -300));
  return;
}


/* 004ca161 size=11 */

void Unwind_004ca161(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0xcc));
  return;
}


/* 004ca16c size=11 */

void Unwind_004ca16c(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0xac));
  return;
}


/* 004ca177 size=11 */

void Unwind_004ca177(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x16c));
  return;
}


/* 004ca182 size=8 */

void Unwind_004ca182(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca18a size=8 */

void Unwind_004ca18a(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x4c));
  return;
}


/* 004ca192 size=8 */

void Unwind_004ca192(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x6c));
  return;
}


/* 004ca19a size=11 */

void Unwind_004ca19a(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x14c));
  return;
}


/* 004ca1a5 size=11 */

void Unwind_004ca1a5(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x8c));
  return;
}


/* 004ca1b0 size=11 */

void Unwind_004ca1b0(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca1bb size=11 */

void Unwind_004ca1bb(void)

{
  int unaff_EBP;
  
  FUN_004a8920((undefined4 *)(unaff_EBP + -400));
  return;
}


/* 004ca1c6 size=11 */

void Unwind_004ca1c6(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -400));
  return;
}


/* 004ca1d1 size=11 */

void Unwind_004ca1d1(void)

{
  int unaff_EBP;
  
  exception__dtor_exception((exception *)(unaff_EBP + -0x184));
  return;
}


/* 004ca1dc size=11 */

void Unwind_004ca1dc(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca1e7 size=14 */

void Unwind_004ca1e7(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca1f5 size=11 */

void Unwind_004ca1f5(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x178));
  return;
}


/* 004ca210 size=8 */

void Unwind_004ca210(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004ca218 size=8 */

void Unwind_004ca218(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca230 size=8 */

void Unwind_004ca230(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca250 size=8 */

void Unwind_004ca250(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca270 size=8 */

void Unwind_004ca270(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca290 size=8 */

void Unwind_004ca290(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca2b0 size=8 */

void Unwind_004ca2b0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca2d0 size=8 */

void Unwind_004ca2d0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca2f0 size=8 */

void Unwind_004ca2f0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca310 size=8 */

void Unwind_004ca310(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca330 size=8 */

void Unwind_004ca330(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca338 size=11 */

void Unwind_004ca338(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca343 size=14 */

void Unwind_004ca343(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x1048));
  return;
}


/* 004ca351 size=8 */

void Unwind_004ca351(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca359 size=11 */

void Unwind_004ca359(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca370 size=11 */

void Unwind_004ca370(void)

{
  int unaff_EBP;
  
  FUN_004a4fa0((undefined4 *)(unaff_EBP + -0xdc));
  return;
}


/* 004ca37b size=11 */

void Unwind_004ca37b(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca386 size=11 */

void Unwind_004ca386(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca391 size=11 */

void Unwind_004ca391(void)

{
  int unaff_EBP;
  
  FUN_004a8b90((undefined4 *)(unaff_EBP + -0xec));
  return;
}


/* 004ca39c size=11 */

void Unwind_004ca39c(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0xec));
  return;
}


/* 004ca3a7 size=11 */

void Unwind_004ca3a7(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca3b2 size=11 */

void Unwind_004ca3b2(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0xdc));
  return;
}


/* 004ca3bd size=11 */

void Unwind_004ca3bd(void)

{
  int unaff_EBP;
  
  FUN_004a5080((undefined4 *)(unaff_EBP + -0xcc));
  return;
}


/* 004ca3c8 size=14 */

void Unwind_004ca3c8(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca3d6 size=14 */

void Unwind_004ca3d6(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca3e4 size=11 */

void Unwind_004ca3e4(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca400 size=8 */

void Unwind_004ca400(void)

{
  int unaff_EBP;
  
  FUN_004a4fa0(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004ca408 size=14 */

void Unwind_004ca408(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0xd0));
  return;
}


/* 004ca416 size=14 */

void Unwind_004ca416(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0xf0));
  return;
}


/* 004ca424 size=14 */

void Unwind_004ca424(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x110));
  return;
}


/* 004ca432 size=14 */

void Unwind_004ca432(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x130));
  return;
}


/* 004ca440 size=14 */

void Unwind_004ca440(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x150));
  return;
}


/* 004ca44e size=14 */

void Unwind_004ca44e(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x170));
  return;
}


/* 004ca470 size=8 */

void Unwind_004ca470(void)

{
  int unaff_EBP;
  
  FUN_004a4fa0(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004ca478 size=14 */

void Unwind_004ca478(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0xd0));
  return;
}


/* 004ca486 size=14 */

void Unwind_004ca486(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0xf0));
  return;
}


/* 004ca494 size=14 */

void Unwind_004ca494(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x110));
  return;
}


/* 004ca4a2 size=14 */

void Unwind_004ca4a2(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x130));
  return;
}


/* 004ca4b0 size=14 */

void Unwind_004ca4b0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x150));
  return;
}


/* 004ca4be size=14 */

void Unwind_004ca4be(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x170));
  return;
}


/* 004ca4e0 size=8 */

void Unwind_004ca4e0(void)

{
  int unaff_EBP;
  
  FUN_004b0af0((undefined4 *)(unaff_EBP + -0x40));
  return;
}


/* 004ca4e8 size=8 */

void Unwind_004ca4e8(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca4f0 size=8 */

void Unwind_004ca4f0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca510 size=11 */

void Unwind_004ca510(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca530 size=8 */

void Unwind_004ca530(void)

{
  int unaff_EBP;
  
  FUN_004b0af0((undefined4 *)(unaff_EBP + -0x40));
  return;
}


/* 004ca538 size=8 */

void Unwind_004ca538(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca540 size=8 */

void Unwind_004ca540(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca560 size=26 */

void Unwind_004ca560(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x9c) & 1) == 0) {
    return;
  }
  FUN_004a80a0(*(int **)(unaff_EBP + 4));
  return;
}


/* 004ca57a size=8 */

void Unwind_004ca57a(void)

{
  int unaff_EBP;
  
  FUN_004ad230((undefined4 *)(unaff_EBP + -0x80));
  return;
}


/* 004ca582 size=11 */

void Unwind_004ca582(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca58d size=11 */

void Unwind_004ca58d(void)

{
  int unaff_EBP;
  
  FUN_004a8b90((undefined4 *)(unaff_EBP + -0xa8));
  return;
}


/* 004ca598 size=11 */

void Unwind_004ca598(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0xa8));
  return;
}


/* 004ca5a3 size=19 */

void Unwind_004ca5a3(void)

{
  int unaff_EBP;
  
  FUN_004bd049(unaff_EBP + -0x6c,0x20,2,FUN_004ad860);
  return;
}


/* 004ca5b6 size=8 */

void Unwind_004ca5b6(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca5be size=11 */

void Unwind_004ca5be(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca5c9 size=11 */

void Unwind_004ca5c9(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x98));
  return;
}


/* 004ca5d4 size=11 */

void Unwind_004ca5d4(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca5df size=11 */

void Unwind_004ca5df(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x8c));
  return;
}


/* 004ca5ea size=11 */

void Unwind_004ca5ea(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca5f5 size=11 */

void Unwind_004ca5f5(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca600 size=11 */

void Unwind_004ca600(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca60b size=11 */

void Unwind_004ca60b(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca620 size=26 */

void Unwind_004ca620(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0xac) & 1) == 0) {
    return;
  }
  FUN_004a80a0(*(int **)(unaff_EBP + 4));
  return;
}


/* 004ca63a size=11 */

void Unwind_004ca63a(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca645 size=11 */

void Unwind_004ca645(void)

{
  int unaff_EBP;
  
  FUN_004a8b90((undefined4 *)(unaff_EBP + -0xa4));
  return;
}


/* 004ca650 size=11 */

void Unwind_004ca650(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0xa4));
  return;
}


/* 004ca65b size=11 */

void Unwind_004ca65b(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca666 size=11 */

void Unwind_004ca666(void)

{
  int unaff_EBP;
  
  FUN_004a8b90((undefined4 *)(unaff_EBP + -0x98));
  return;
}


/* 004ca671 size=11 */

void Unwind_004ca671(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x98));
  return;
}


/* 004ca67c size=8 */

void Unwind_004ca67c(void)

{
  int unaff_EBP;
  
  FUN_004ad230((undefined4 *)(unaff_EBP + -0x80));
  return;
}


/* 004ca684 size=8 */

void Unwind_004ca684(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x2c));
  return;
}


/* 004ca68c size=8 */

void Unwind_004ca68c(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x6c));
  return;
}


/* 004ca694 size=8 */

void Unwind_004ca694(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x4c));
  return;
}


/* 004ca69c size=11 */

void Unwind_004ca69c(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca6a7 size=11 */

void Unwind_004ca6a7(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x8c));
  return;
}


/* 004ca6b2 size=11 */

void Unwind_004ca6b2(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca6bd size=11 */

void Unwind_004ca6bd(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca6c8 size=11 */

void Unwind_004ca6c8(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca6d3 size=11 */

void Unwind_004ca6d3(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca6de size=11 */

void Unwind_004ca6de(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca6e9 size=11 */

void Unwind_004ca6e9(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca6f4 size=11 */

void Unwind_004ca6f4(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca6ff size=11 */

void Unwind_004ca6ff(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca70a size=11 */

void Unwind_004ca70a(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca715 size=11 */

void Unwind_004ca715(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca720 size=11 */

void Unwind_004ca720(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca740 size=8 */

void Unwind_004ca740(void)

{
  int unaff_EBP;
  
  FUN_004b0af0((undefined4 *)(unaff_EBP + -0x20));
  return;
}


/* 004ca748 size=8 */

void Unwind_004ca748(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca750 size=8 */

void Unwind_004ca750(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca770 size=11 */

void Unwind_004ca770(void)

{
  int unaff_EBP;
  
  FUN_004a5080((undefined4 *)(unaff_EBP + -0xb4));
  return;
}


/* 004ca77b size=11 */

void Unwind_004ca77b(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x120));
  return;
}


/* 004ca786 size=11 */

void Unwind_004ca786(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x114));
  return;
}


/* 004ca791 size=11 */

void Unwind_004ca791(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca79c size=11 */

void Unwind_004ca79c(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca7a7 size=11 */

void Unwind_004ca7a7(void)

{
  int unaff_EBP;
  
  FUN_004a8b90((undefined4 *)(unaff_EBP + -0x130));
  return;
}


/* 004ca7b2 size=11 */

void Unwind_004ca7b2(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x130));
  return;
}


/* 004ca7bd size=11 */

void Unwind_004ca7bd(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca7c8 size=11 */

void Unwind_004ca7c8(void)

{
  int unaff_EBP;
  
  FUN_004a8b90((undefined4 *)(unaff_EBP + -0x13c));
  return;
}


/* 004ca7d3 size=11 */

void Unwind_004ca7d3(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x13c));
  return;
}


/* 004ca7de size=11 */

void Unwind_004ca7de(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0xf4));
  return;
}


/* 004ca7e9 size=11 */

void Unwind_004ca7e9(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0xd4));
  return;
}


/* 004ca7f4 size=11 */

void Unwind_004ca7f4(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca7ff size=11 */

void Unwind_004ca7ff(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca80a size=11 */

void Unwind_004ca80a(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca820 size=8 */

void Unwind_004ca820(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x50));
  return;
}


/* 004ca828 size=8 */

void Unwind_004ca828(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x30));
  return;
}


/* 004ca830 size=8 */

void Unwind_004ca830(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x70));
  return;
}


/* 004ca838 size=11 */

void Unwind_004ca838(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x90));
  return;
}


/* 004ca843 size=11 */

void Unwind_004ca843(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x90));
  return;
}


/* 004ca84e size=8 */

void Unwind_004ca84e(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x70));
  return;
}


/* 004ca856 size=11 */

void Unwind_004ca856(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x90));
  return;
}


/* 004ca870 size=8 */

void Unwind_004ca870(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x70));
  return;
}


/* 004ca878 size=8 */

void Unwind_004ca878(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x50));
  return;
}


/* 004ca880 size=8 */

void Unwind_004ca880(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x30));
  return;
}


/* 004ca8a0 size=8 */

void Unwind_004ca8a0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x70));
  return;
}


/* 004ca8a8 size=8 */

void Unwind_004ca8a8(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x50));
  return;
}


/* 004ca8b0 size=8 */

void Unwind_004ca8b0(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x30));
  return;
}


/* 004ca8b8 size=11 */

void Unwind_004ca8b8(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x90));
  return;
}


/* 004ca8c3 size=11 */

void Unwind_004ca8c3(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x90));
  return;
}


/* 004ca8ce size=11 */

void Unwind_004ca8ce(void)

{
  int unaff_EBP;
  
  FUN_004ad860((undefined4 *)(unaff_EBP + -0x90));
  return;
}


/* 004ca8f0 size=8 */

void Unwind_004ca8f0(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca8f8 size=8 */

void Unwind_004ca8f8(void)

{
  int unaff_EBP;
  
  FUN_004a8b90(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004ca900 size=8 */

void Unwind_004ca900(void)

{
  int unaff_EBP;
  
  FUN_004a8010(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004ca920 size=8 */

void Unwind_004ca920(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca928 size=8 */

void Unwind_004ca928(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca930 size=8 */

void Unwind_004ca930(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004ca938 size=8 */

void Unwind_004ca938(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca950 size=8 */

void Unwind_004ca950(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca958 size=11 */

void Unwind_004ca958(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca963 size=8 */

void Unwind_004ca963(void)

{
  int unaff_EBP;
  
  FUN_004a8010(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004ca980 size=8 */

void Unwind_004ca980(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca988 size=8 */

void Unwind_004ca988(void)

{
  int unaff_EBP;
  
  FUN_004a8b90((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004ca990 size=8 */

void Unwind_004ca990(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004ca998 size=23 */

void Unwind_004ca998(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x1c) & 1) == 0) {
    return;
  }
  FUN_004a8010(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004ca9af size=8 */

void Unwind_004ca9af(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca9d0 size=8 */

void Unwind_004ca9d0(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca9d8 size=8 */

void Unwind_004ca9d8(void)

{
  FUN_004a82f0();
  return;
}


/* 004ca9e0 size=8 */

void Unwind_004ca9e0(void)

{
  int unaff_EBP;
  
  FUN_004a8b90((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004ca9e8 size=8 */

void Unwind_004ca9e8(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004ca9f0 size=8 */

void Unwind_004ca9f0(void)

{
  int unaff_EBP;
  
  FUN_004a8b90(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004ca9f8 size=23 */

void Unwind_004ca9f8(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x1c) & 1) == 0) {
    return;
  }
  FUN_004a8010(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004caa0f size=8 */

void Unwind_004caa0f(void)

{
  FUN_004a82f0();
  return;
}


/* 004caa30 size=8 */

void Unwind_004caa30(void)

{
  FUN_004a82f0();
  return;
}


/* 004caa38 size=11 */

void Unwind_004caa38(void)

{
  FUN_004a82f0();
  return;
}


/* 004caa43 size=8 */

void Unwind_004caa43(void)

{
  int unaff_EBP;
  
  FUN_004a8010(*(undefined4 **)(unaff_EBP + -0x20));
  return;
}


/* 004caa4b size=11 */

void Unwind_004caa4b(void)

{
  int unaff_EBP;
  
  FUN_004a5080((undefined4 *)(*(int *)(unaff_EBP + -0x20) + 0x10));
  return;
}


/* 004caa56 size=8 */

void Unwind_004caa56(void)

{
  FUN_004a82f0();
  return;
}


/* 004caa5e size=11 */

void Unwind_004caa5e(void)

{
  FUN_004a82f0();
  return;
}


/* 004caa69 size=14 */

void Unwind_004caa69(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(*(int *)(unaff_EBP + -0x20) + 0xb8));
  return;
}


/* 004caa77 size=8 */

void Unwind_004caa77(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004caa7f size=8 */

void Unwind_004caa7f(void)

{
  FUN_004a82f0();
  return;
}


/* 004caaa0 size=8 */

void Unwind_004caaa0(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004caaa8 size=8 */

void Unwind_004caaa8(void)

{
  FUN_004a82f0();
  return;
}


/* 004caac0 size=8 */

void Unwind_004caac0(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004caac8 size=8 */

void Unwind_004caac8(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x24));
  return;
}


/* 004caad0 size=8 */

void Unwind_004caad0(void)

{
  FUN_004a82f0();
  return;
}


/* 004caad8 size=8 */

void Unwind_004caad8(void)

{
  FUN_004a82f0();
  return;
}


/* 004caaf0 size=8 */

void Unwind_004caaf0(void)

{
  FUN_004a82f0();
  return;
}


/* 004caaf8 size=8 */

void Unwind_004caaf8(void)

{
  FUN_004a82f0();
  return;
}


/* 004cab00 size=8 */

void Unwind_004cab00(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004cab08 size=8 */

void Unwind_004cab08(void)

{
  FUN_004a82f0();
  return;
}


/* 004cab10 size=8 */

void Unwind_004cab10(void)

{
  int unaff_EBP;
  
  FUN_004a8b90(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004cab18 size=23 */

void Unwind_004cab18(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x2c) & 1) == 0) {
    return;
  }
  FUN_004a8010(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004cab2f size=8 */

void Unwind_004cab2f(void)

{
  FUN_004a82f0();
  return;
}


/* 004cab50 size=8 */

void Unwind_004cab50(void)

{
  FUN_004a82f0();
  return;
}


/* 004cab58 size=8 */

void Unwind_004cab58(void)

{
  FUN_004a82f0();
  return;
}


/* 004cab60 size=8 */

void Unwind_004cab60(void)

{
  int unaff_EBP;
  
  FUN_004a8010((undefined4 *)(unaff_EBP + -0x18));
  return;
}


/* 004cab68 size=8 */

void Unwind_004cab68(void)

{
  int unaff_EBP;
  
  FUN_004a8b90(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004cab70 size=23 */

void Unwind_004cab70(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x1c) & 1) == 0) {
    return;
  }
  FUN_004a8010(*(undefined4 **)(unaff_EBP + 4));
  return;
}


/* 004cab87 size=8 */

void Unwind_004cab87(void)

{
  FUN_004a82f0();
  return;
}


/* 004caba0 size=11 */

void Unwind_004caba0(void)

{
  FUN_004a82f0();
  return;
}


/* 004cabab size=11 */

void Unwind_004cabab(void)

{
  int unaff_EBP;
  
  FUN_004a7f10((undefined4 *)(unaff_EBP + -0x128));
  return;
}


/* 004cabb6 size=11 */

void Unwind_004cabb6(void)

{
  FUN_004aa8d0();
  return;
}


/* 004cabd0 size=11 */

void Unwind_004cabd0(void)

{
  int unaff_EBP;
  
  thunk_FUN_004c8bd0(*(int *)(unaff_EBP + -0x10) + 0x1c);
  return;
}


/* 004cabf0 size=11 */

void Unwind_004cabf0(void)

{
  int unaff_EBP;
  
  thunk_FUN_004c8bd0(*(int *)(unaff_EBP + -0x10) + 0x1c);
  return;
}


/* 004cac10 size=11 */

void Unwind_004cac10(void)

{
  int unaff_EBP;
  
  thunk_FUN_004c8bd0(*(int *)(unaff_EBP + -0x10) + 0x1c);
  return;
}


/* 004cac1b size=11 */

void Unwind_004cac1b(void)

{
  int unaff_EBP;
  
  thunk_FUN_004c8bd0(*(int *)(unaff_EBP + -0x10) + 0x24);
  return;
}


/* 004cac30 size=11 */

void Unwind_004cac30(void)

{
  int unaff_EBP;
  
  thunk_FUN_004c8bd0(*(int *)(unaff_EBP + -0x10) + 0x38);
  return;
}


/* 004cac3b size=11 */

void Unwind_004cac3b(void)

{
  int unaff_EBP;
  
  thunk_FUN_004c8bd0(*(int *)(unaff_EBP + -0x10) + 0x40);
  return;
}


/* 004cac50 size=11 */

void Unwind_004cac50(void)

{
  int unaff_EBP;
  
  thunk_FUN_004c8bd0(*(int *)(unaff_EBP + -0x10) + 0x38);
  return;
}


/* 004cac5b size=11 */

void Unwind_004cac5b(void)

{
  int unaff_EBP;
  
  thunk_FUN_004c8bd0(*(int *)(unaff_EBP + -0x10) + 0x40);
  return;
}


/* 004cac70 size=11 */

void Unwind_004cac70(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


/* 004cac90 size=11 */

void Unwind_004cac90(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -0x18));
  return;
}


/* 004cacb0 size=11 */

void Unwind_004cacb0(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


/* 004cacbb size=11 */

void Unwind_004cacbb(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


/* 004cacd0 size=11 */

void Unwind_004cacd0(void)

{
  int unaff_EBP;
  
  FUN_004b7710((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x10));
  return;
}


/* 004cacf0 size=11 */

void Unwind_004cacf0(void)

{
  int unaff_EBP;
  
  FUN_004b7710((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x10));
  return;
}


/* 004cacfb size=14 */

void Unwind_004cacfb(void)

{
  int unaff_EBP;
  
  thunk_FUN_004c8bd0(*(int *)(unaff_EBP + -0x10) + 0x80);
  return;
}


/* 004cad09 size=14 */

void Unwind_004cad09(void)

{
  FUN_004a82f0();
  return;
}


/* 004cad30 size=14 */

void Unwind_004cad30(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -0xbc));
  return;
}


/* 004cad3e size=14 */

void Unwind_004cad3e(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -0xbc));
  return;
}


/* 004cad4c size=14 */

void Unwind_004cad4c(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -0xbc));
  return;
}


/* 004cad5a size=14 */

void Unwind_004cad5a(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -0xbc));
  return;
}


/* 004cad68 size=14 */

void Unwind_004cad68(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -0xbc));
  return;
}


/* 004cad80 size=14 */

void Unwind_004cad80(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + -6000));
  return;
}


/* 004cada0 size=8 */

void Unwind_004cada0(void)

{
  int unaff_EBP;
  
  FUN_004b7240(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004cadc0 size=8 */

void Unwind_004cadc0(void)

{
  int unaff_EBP;
  
  FUN_004b7240(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004cadc8 size=11 */

void Unwind_004cadc8(void)

{
  int unaff_EBP;
  
  FUN_004b7710((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x10));
  return;
}


/* 004cadd3 size=11 */

void Unwind_004cadd3(void)

{
  int unaff_EBP;
  
  FUN_004b7710((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x1c));
  return;
}


/* 004cadf0 size=8 */

void Unwind_004cadf0(void)

{
  int unaff_EBP;
  
  FUN_004b7240(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004cae10 size=8 */

void Unwind_004cae10(void)

{
  int unaff_EBP;
  
  FUN_004b7240(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004cae30 size=8 */

void Unwind_004cae30(void)

{
  int unaff_EBP;
  
  FUN_004b8310(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004cae50 size=8 */

void Unwind_004cae50(void)

{
  int unaff_EBP;
  
  FUN_004b8700(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004cae70 size=8 */

void Unwind_004cae70(void)

{
  int unaff_EBP;
  
  FUN_004b8700(*(undefined4 **)(unaff_EBP + -0x10));
  return;
}


/* 004cae90 size=11 */

void Unwind_004cae90(void)

{
  int unaff_EBP;
  
  FUN_004b97d0((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 8));
  return;
}


/* 004cae9b size=11 */

void Unwind_004cae9b(void)

{
  int unaff_EBP;
  
  FUN_004b97d0((undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0xc));
  return;
}


/* 004caea6 size=11 */

void Unwind_004caea6(void)

{
  FUN_004a82f0();
  return;
}


/* 004caeb1 size=11 */

void Unwind_004caeb1(void)

{
  FUN_004a82f0();
  return;
}


/* 004caec8 size=8 */

void Unwind_004caec8(void)

{
  int unaff_EBP;
  
  FUN_004b9b04((void *)(unaff_EBP + -0x20));
  return;
}


/* 004caedc size=8 */

void Unwind_004caedc(void)

{
  int unaff_EBP;
  
  exception__dtor_exception(*(exception **)(unaff_EBP + -0x14));
  return;
}


/* 004caef0 size=8 */

void Unwind_004caef0(void)

{
  int unaff_EBP;
  
  exception__dtor_exception(*(exception **)(unaff_EBP + -0x10));
  return;
}


/* 004caf04 size=8 */

void Unwind_004caf04(void)

{
  int unaff_EBP;
  
  exception__dtor_exception(*(exception **)(unaff_EBP + -0x10));
  return;
}


/* 004caf18 size=8 */

void Unwind_004caf18(void)

{
  int unaff_EBP;
  
  exception__dtor_exception(*(exception **)(unaff_EBP + -0x10));
  return;
}


/* 004caf2c size=8 */

void Unwind_004caf2c(void)

{
  int unaff_EBP;
  
  FUN_004b9b04((void *)(unaff_EBP + -0x20));
  return;
}


/* 004caf40 size=8 */

void Unwind_004caf40(void)

{
  int unaff_EBP;
  
  exception__dtor_exception(*(exception **)(unaff_EBP + -0x10));
  return;
}


/* 004caf60 size=11 */

void Unwind_004caf60(void)

{
  int unaff_EBP;
  
  FUN_00430df0(*(undefined **)(unaff_EBP + 4));
  return;
}


