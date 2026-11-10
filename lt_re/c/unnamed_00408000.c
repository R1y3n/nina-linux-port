/* lithtech.exe decompilation - unnamed_00408000 */
#include "ghidra_types.h"

/* 00408120 size=77 */

undefined4 * __thiscall FUN_00408120(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_LAB_004cb52c;
  if (*(undefined **)((int)this + 0x37c) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)((int)this + 0x37c));
    *(undefined4 *)((int)this + 0x37c) = 0;
  }
  *(undefined ***)((int)this + 0x380) = &PTR_LAB_004cba98;
  *(undefined ***)this = &PTR_LAB_004cb890;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 004081c0 size=397 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_004081c0(float *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  float local_c;
  float local_8;
  float local_4;
  
  iVar7 = *(int *)(param_2 + 0x1b0);
  fVar1 = *param_1 - *(float *)(param_2 + 0x194);
  fVar5 = param_1[1] - *(float *)(param_2 + 0x198);
  fVar4 = param_1[2] - *(float *)(param_2 + 0x19c);
  fVar3 = *(float *)(iVar7 + 0xd0) - *(float *)(iVar7 + 0xc4);
  fVar2 = *(float *)(iVar7 + 0xd4) - *(float *)(iVar7 + 200);
  fVar6 = *(float *)(iVar7 + 0xd8) - *(float *)(iVar7 + 0xcc);
  if (fVar1 * fVar1 + fVar5 * fVar5 + fVar4 * fVar4 < fVar3 * fVar3 + fVar2 * fVar2 + fVar6 * fVar6)
  {
    local_4 = _DAT_004cba94 /
              (*(float *)(param_2 + 0x26c) * param_1[1] +
               *(float *)(param_2 + 0x268) * *param_1 + *(float *)(param_2 + 0x270) * param_1[2] +
              *(float *)(param_2 + 0x274));
    local_c = (*(float *)(param_2 + 0x238) * *param_1 +
               *(float *)(param_2 + 0x23c) * param_1[1] + *(float *)(param_2 + 0x240) * param_1[2] +
              *(float *)(param_2 + 0x244)) * local_4;
    local_8 = (*(float *)(param_2 + 0x24c) * param_1[1] +
               *(float *)(param_2 + 0x248) * *param_1 + *(float *)(param_2 + 0x250) * param_1[2] +
              *(float *)(param_2 + 0x254)) * local_4;
    local_4 = (*(float *)(param_2 + 0x25c) * param_1[1] +
               *(float *)(param_2 + 600) * *param_1 + *(float *)(param_2 + 0x260) * param_1[2] +
              *(float *)(param_2 + 0x264)) * local_4;
    iVar7 = FUN_0043ef40(*(int **)(iVar7 + 0x9c),&local_c);
    if (iVar7 == 0) {
      return 1;
    }
  }
  return 0;
}


/* 004088e0 size=128 */

bool __cdecl FUN_004088e0(char *param_1)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 == (char *)0x0) {
    param_1 = s_dplay2_004d5f04;
  }
  piVar1 = (int *)FUN_00467ac0((void *)(DAT_004e516c + 0x510),(byte *)param_1);
  if (piVar1 == (int *)0x0) {
    piVar1 = udpdriver_465470((void *)(DAT_004e516c + 0x510),(byte *)param_1);
    if (piVar1 == (int *)0x0) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     s_CLTClient__IsLobbyLaunched_004d5ee8);
      }
      return true;
    }
  }
  iVar2 = (**(code **)(*piVar1 + 0x40))();
  return (bool)('\x01' - (iVar2 != 0));
}


/* 00408a30 size=1646 */

void __cdecl FUN_00408a30(int param_1)

{
  *(undefined1 **)(param_1 + 0x20) = &LAB_004090a0;
  *(undefined1 **)(param_1 + 0x28) = &LAB_004090c0;
  *(undefined1 **)(param_1 + 0x24) = &LAB_00409160;
  *(undefined1 **)(param_1 + 0x2c) = &LAB_00409190;
  *(undefined1 **)(param_1 + 0x30) = &LAB_004091d0;
  *(undefined1 **)(param_1 + 0x34) = &LAB_004091f0;
  *(undefined1 **)(param_1 + 0x38) = &LAB_00409260;
  *(code **)(param_1 + 0x3c) = FUN_00409220;
  *(undefined1 **)(param_1 + 0x40) = &LAB_00409270;
  *(undefined1 **)(param_1 + 0x44) = &LAB_004092d0;
  *(undefined1 **)(param_1 + 0x48) = &LAB_00409400;
  *(undefined1 **)(param_1 + 0x4c) = &LAB_00409490;
  *(undefined1 **)(param_1 + 0x50) = &LAB_00409580;
  *(undefined1 **)(param_1 + 0x54) = &LAB_004096b0;
  *(undefined1 **)(param_1 + 0x58) = &LAB_00409740;
  *(undefined1 **)(param_1 + 0x5c) = &LAB_004097d0;
  *(undefined1 **)(param_1 + 100) = &LAB_00409870;
  *(undefined1 **)(param_1 + 0x6c) = &LAB_00409910;
  *(undefined1 **)(param_1 + 0x70) = &LAB_00435d80;
  *(undefined1 **)(param_1 + 0x74) = &LAB_00435ea0;
  *(undefined1 **)(param_1 + 0x7c) = &LAB_00435ee0;
  *(undefined1 **)(param_1 + 0x78) = &LAB_00435ec0;
  *(undefined1 **)(param_1 + 0x80) = &LAB_00436040;
  *(undefined1 **)(param_1 + 0x84) = &LAB_004099a0;
  *(code **)(param_1 + 0x88) = FUN_00440140;
  *(undefined1 **)(param_1 + 0x8c) = &LAB_004099c0;
  *(undefined1 **)(param_1 + 0x90) = &LAB_00409aa0;
  *(undefined1 **)(param_1 + 0x94) = &LAB_00409ac0;
  *(undefined1 **)(param_1 + 0x98) = &LAB_00409ae0;
  *(undefined1 **)(param_1 + 0x9c) = &LAB_00409b10;
  *(undefined1 **)(param_1 + 0xa0) = &LAB_00409b40;
  *(undefined1 **)(param_1 + 0xa4) = &LAB_00409b60;
  *(undefined1 **)(param_1 + 0xa8) = &LAB_00409b90;
  *(undefined1 **)(param_1 + 0xac) = &LAB_00409bd0;
  *(undefined1 **)(param_1 + 0xb0) = &LAB_00409c10;
  *(undefined1 **)(param_1 + 0xb8) = &LAB_00409c30;
  *(undefined1 **)(param_1 + 0xbc) = &LAB_00409c90;
  *(undefined1 **)(param_1 + 0xc0) = &LAB_00409cb0;
  *(undefined1 **)(param_1 + 0xc4) = &LAB_00409cd0;
  *(code **)(param_1 + 200) = FUN_00409cf0;
  *(undefined1 **)(param_1 + 0xcc) = &LAB_00409d70;
  *(code **)(param_1 + 0xb4) = FUN_00409db0;
  *(undefined1 **)(param_1 + 0xd0) = &LAB_00409e40;
  *(undefined1 **)(param_1 + 0xd4) = &LAB_00409e80;
  *(undefined1 **)(param_1 + 0xd8) = &LAB_00409eb0;
  *(undefined1 **)(param_1 + 0xdc) = &LAB_00409ee0;
  *(undefined1 **)(param_1 + 0xe8) = &LAB_00409f50;
  *(undefined1 **)(param_1 + 0xe0) = &LAB_00409f10;
  *(undefined1 **)(param_1 + 0xe4) = &LAB_00409f30;
  *(undefined1 **)(param_1 + 0xec) = &LAB_00409f70;
  *(undefined1 **)(param_1 + 0xf0) = &LAB_00409f90;
  *(undefined1 **)(param_1 + 0xf4) = &LAB_00409fb0;
  *(undefined1 **)(param_1 + 0xf8) = &LAB_00409fd0;
  *(undefined1 **)(param_1 + 0xfc) = &LAB_00409ff0;
  *(undefined1 **)(param_1 + 0x100) = &LAB_0040a030;
  *(undefined1 **)(param_1 + 0x104) = &LAB_0040a050;
  *(undefined1 **)(param_1 + 0x108) = &LAB_0040a070;
  *(undefined1 **)(param_1 + 0x10c) = &LAB_0040a080;
  *(undefined1 **)(param_1 + 0x110) = &LAB_0040a090;
  *(undefined1 **)(param_1 + 0x114) = &LAB_0040a0b0;
  *(undefined1 **)(param_1 + 0x118) = &LAB_0040a1c0;
  *(undefined1 **)(param_1 + 0x11c) = &LAB_0040a350;
  *(undefined1 **)(param_1 + 0x120) = &LAB_0040a4b0;
  *(undefined1 **)(param_1 + 0x124) = &LAB_0040a4d0;
  *(undefined1 **)(param_1 + 0x128) = &LAB_0040a4f0;
  *(undefined1 **)(param_1 + 300) = &LAB_0040a510;
  *(undefined1 **)(param_1 + 0x130) = &LAB_0040a5f0;
  *(code **)(param_1 + 0x134) = FUN_00404c00;
  *(undefined1 **)(param_1 + 0x138) = &LAB_0040a740;
  *(undefined1 **)(param_1 + 0x13c) = &LAB_0040a820;
  *(code **)(param_1 + 0x1dc) = FUN_0040a9f0;
  *(undefined1 **)(param_1 + 0x1e0) = &LAB_0040aa60;
  *(undefined1 **)(param_1 + 0x1e4) = &LAB_00471180;
  *(code **)(param_1 + 0x1e8) = FUN_0043c4b0;
  *(undefined1 **)(param_1 + 0x1ec) = &LAB_00447870;
  *(undefined1 **)(param_1 + 0x1f0) = &LAB_0040aae0;
  *(undefined1 **)(param_1 + 500) = &LAB_0040abc0;
  *(undefined1 **)(param_1 + 0x1f8) = &LAB_0040ac30;
  *(undefined1 **)(param_1 + 0x1fc) = &LAB_0040ac50;
  *(undefined1 **)(param_1 + 0x200) = &LAB_0040ac70;
  *(undefined1 **)(param_1 + 0x204) = &LAB_0040ac80;
  *(undefined1 **)(param_1 + 0x208) = &LAB_0040aca0;
  *(undefined1 **)(param_1 + 0x20c) = &LAB_0040acc0;
  *(undefined1 **)(param_1 + 0x210) = &LAB_0040ad10;
  *(undefined1 **)(param_1 + 0x214) = &LAB_0040ad50;
  *(undefined1 **)(param_1 + 0x218) = &LAB_0040ad90;
  *(undefined1 **)(param_1 + 0x21c) = &LAB_0040adb0;
  *(undefined1 **)(param_1 + 0x220) = &LAB_0040add0;
  *(undefined1 **)(param_1 + 0x224) = &LAB_0040ae10;
  *(undefined1 **)(param_1 + 0x228) = &LAB_0040ae40;
  *(undefined1 **)(param_1 + 0x22c) = &LAB_0040ae70;
  *(undefined1 **)(param_1 + 0x230) = &LAB_0040ae90;
  *(code **)(param_1 + 0x234) = FUN_004317e0;
  *(undefined1 **)(param_1 + 0x238) = &LAB_0040aeb0;
  *(undefined1 **)(param_1 + 0x23c) = &LAB_0040aed0;
  *(undefined1 **)(param_1 + 0x240) = &LAB_0040af10;
  *(undefined1 **)(param_1 + 0x244) = &LAB_0040af20;
  *(undefined1 **)(param_1 + 0x248) = &LAB_0040b1b0;
  *(undefined1 **)(param_1 + 0x24c) = &LAB_0040b1d0;
  *(undefined1 **)(param_1 + 0x250) = &LAB_0040b2d0;
  *(undefined1 **)(param_1 + 0x254) = &LAB_0040af40;
  *(undefined1 **)(param_1 + 600) = &LAB_0040af60;
  *(undefined1 **)(param_1 + 0x25c) = &LAB_0040b060;
  *(undefined1 **)(param_1 + 0x264) = &LAB_0040b420;
  *(undefined1 **)(param_1 + 0x278) = &LAB_0040b4f0;
  *(undefined1 **)(param_1 + 0x27c) = &LAB_0040b550;
  *(undefined1 **)(param_1 + 0x268) = &LAB_0040b810;
  *(undefined1 **)(param_1 + 0x26c) = &LAB_0040b840;
  *(undefined1 **)(param_1 + 0x270) = &LAB_0040b880;
  *(undefined1 **)(param_1 + 0x274) = &LAB_0040b4c0;
  *(code **)(param_1 + 0x280) = FUN_0040b5b0;
  *(code **)(param_1 + 0x284) = clientde_impl_40b640;
  *(undefined1 **)(param_1 + 0x288) = &LAB_0040b6a0;
  *(undefined1 **)(param_1 + 0x28c) = &LAB_0040b700;
  *(undefined1 **)(param_1 + 0x290) = &LAB_0040b790;
  *(undefined1 **)(param_1 + 0x294) = &LAB_0040b7b0;
  *(undefined1 **)(param_1 + 0x298) = &LAB_0040b7d0;
  *(undefined1 **)(param_1 + 0x29c) = &LAB_0040b7f0;
  *(undefined1 **)(param_1 + 0x2a0) = &LAB_0040b8b0;
  *(undefined1 **)(param_1 + 0x2a4) = &LAB_0040bb40;
  *(undefined1 **)(param_1 + 0x2a8) = &LAB_0040bb80;
  *(undefined1 **)(param_1 + 0x2ac) = &LAB_0040bc20;
  *(undefined1 **)(param_1 + 0x2b0) = &LAB_0040bc90;
  *(undefined1 **)(param_1 + 0x2b4) = &LAB_0040bce0;
  *(undefined1 **)(param_1 + 0x2b8) = &LAB_0040bd20;
  *(undefined1 **)(param_1 + 700) = &LAB_0040bd60;
  *(code **)(param_1 + 0x2c0) = FUN_0040be20;
  *(undefined1 **)(param_1 + 0x2c4) = &LAB_0040beb0;
  *(undefined1 **)(param_1 + 0x2c8) = &LAB_0040bf00;
  *(undefined1 **)(param_1 + 0x2d4) = &LAB_0040bf70;
  *(undefined1 **)(param_1 + 0x2d8) = &LAB_0040bfc0;
  *(undefined1 **)(param_1 + 0x2cc) = &LAB_0040bf40;
  *(undefined1 **)(param_1 + 0x2d0) = &LAB_0040c010;
  *(undefined1 **)(param_1 + 0x2dc) = &LAB_0040c0f0;
  *(code **)(param_1 + 0x2e0) = FUN_0040c140;
  *(undefined1 **)(param_1 + 0x2e4) = &LAB_004467e0;
  *(undefined1 **)(param_1 + 0x2e8) = &LAB_00446830;
  *(undefined1 **)(param_1 + 0x2ec) = &LAB_00446890;
  *(undefined1 **)(param_1 + 0x2f0) = &LAB_00446ba0;
  *(undefined1 **)(param_1 + 0x2f4) = &LAB_00446ef0;
  *(undefined1 **)(param_1 + 0x2f8) = &LAB_0040c1b0;
  *(undefined1 **)(param_1 + 0x300) = &LAB_0040c2a0;
  *(undefined1 **)(param_1 + 0x2fc) = &LAB_0040c1e0;
  *(undefined1 **)(param_1 + 0x304) = &LAB_0040c390;
  *(undefined1 **)(param_1 + 0x308) = &LAB_0040c470;
  *(undefined1 **)(param_1 + 0x30c) = &LAB_0040c4f0;
  *(undefined1 **)(param_1 + 0x310) = &LAB_0040c590;
  *(undefined1 **)(param_1 + 0x314) = &LAB_0040c740;
  *(undefined1 **)(param_1 + 0x318) = &LAB_0040c760;
  *(undefined1 **)(param_1 + 0x31c) = &LAB_0040c7a0;
  *(undefined1 **)(param_1 + 800) = &LAB_0040c7c0;
  *(undefined1 **)(param_1 + 0x324) = &LAB_0040c800;
  *(undefined1 **)(param_1 + 0x328) = &LAB_0043fda0;
  *(undefined1 **)(param_1 + 0x32c) = &LAB_0043fe20;
  *(undefined1 **)(param_1 + 0x260) = &LAB_0040c830;
  *(code **)(param_1 + 0x330) = iltclient_408350;
  *(undefined1 **)(param_1 + 0x334) = &LAB_004084b0;
  *(undefined1 **)(param_1 + 0x338) = &LAB_00408590;
  *(undefined1 **)(param_1 + 0x33c) = &LAB_00408670;
  *(undefined1 **)(param_1 + 0x344) = &LAB_004086a0;
  *(undefined1 **)(param_1 + 0x348) = &LAB_004086e0;
  *(undefined1 **)(param_1 + 0x34c) = &LAB_00408700;
  *(undefined1 **)(param_1 + 0x350) = &LAB_00408760;
  *(undefined1 **)(param_1 + 0x354) = &LAB_004087c0;
  *(undefined1 **)(param_1 + 0x358) = &LAB_004087e0;
  *(undefined1 **)(param_1 + 0x35c) = &LAB_00408800;
  *(undefined1 **)(param_1 + 0x360) = &LAB_00408840;
  *(undefined1 **)(param_1 + 0x368) = &LAB_00408960;
  *(code **)(param_1 + 0x364) = FUN_004088e0;
  *(undefined1 **)(param_1 + 0x36c) = &LAB_00408880;
  FUN_0040d0c0(param_1);
  return;
}


/* 00409220 size=51 */

void __cdecl FUN_00409220(byte *param_1,undefined4 param_2)

{
  char local_1f4 [500];
  
  FUN_004baabf(local_1f4,499,param_1,&param_2);
  FUN_00436620(local_1f4);
  return;
}


/* 00409cf0 size=126 */

undefined4 __cdecl FUN_00409cf0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = FUN_00410180();
  if (((*(int *)(iVar1 + 0x5c) == 0) || (param_1 == 0)) || (param_2 == 0)) {
    return 0;
  }
  iVar1 = FUN_00410180();
  iVar1 = (**(code **)(iVar1 + 0x24))(param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_00410180();
    iVar1 = (**(code **)(iVar1 + 0x20))(param_1);
    if (iVar1 == 0) {
      return 0;
    }
  }
  iVar2 = FUN_00410180();
  iVar2 = (**(code **)(iVar2 + 0x14))(param_2);
  if (iVar2 == 0) {
    iVar2 = FUN_00410180();
    iVar2 = (**(code **)(iVar2 + 0x10))(param_2);
    if (iVar2 == 0) {
      return 0;
    }
  }
  iVar3 = FUN_00410180();
  uVar4 = (**(code **)(iVar3 + 0x28))(iVar1,iVar2);
  return uVar4;
}


/* 00409db0 size=134 */

undefined4 __cdecl FUN_00409db0(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = FUN_00410180();
  if (*(int *)(iVar1 + 0x5c) == 0) {
    return 0;
  }
  if (param_1 == 0) {
    return 0;
  }
  iVar1 = FUN_00410180();
  iVar1 = (**(code **)(iVar1 + 0x24))(param_1);
  if (iVar1 == 0) {
    return 0;
  }
  iVar4 = 0;
  if (param_2 != 0) {
    iVar4 = FUN_00410180();
    iVar4 = (**(code **)(iVar4 + 0x14))(param_2);
    if (iVar4 == 0) {
      iVar4 = FUN_00410180();
      iVar4 = (**(code **)(iVar4 + 0x10))(param_2);
      if (iVar4 == 0) {
        return 0;
      }
    }
  }
  iVar2 = FUN_00410180();
  uVar3 = (**(code **)(iVar2 + 0x34))(iVar1,iVar4,param_3,param_4);
  return uVar3;
}


/* 0040a9f0 size=104 */

undefined4 __cdecl FUN_0040a9f0(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = FUN_00420810(0x4e9500,param_1);
  if (puVar1 == (undefined4 *)0x0) {
    FUN_00420790(0x4e9500,param_1,param_2,1);
    return 0;
  }
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CLTClient__RegisterConsoleProgra_004d6038);
  }
  return 0x3e;
}


/* 0040b5b0 size=141 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0040b5b0(int param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  if (param_1 != 0) {
    if (param_2 != (float *)0x0) {
      *param_2 = (float)*(byte *)(param_1 + 0x94) * _DAT_004cbb04;
    }
    if (param_3 != (float *)0x0) {
      *param_3 = (float)*(byte *)(param_1 + 0x95) * _DAT_004cbb04;
    }
    if (param_4 != (float *)0x0) {
      *param_4 = (float)*(byte *)(param_1 + 0x96) * _DAT_004cbb04;
    }
    if (param_5 != (float *)0x0) {
      *param_5 = (float)*(byte *)(param_1 + 0x97) * _DAT_004cbb04;
    }
  }
  return;
}


/* 0040be20 size=141 */

ulonglong __cdecl FUN_0040be20(int param_1)

{
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar1;
  longlong lVar2;
  ulonglong uVar3;
  
  if ((param_1 != 0) && (*(char *)(param_1 + 0xbc) == '\x06')) {
    lVar2 = __ftol();
    *(char *)(param_1 + 500) = (char)lVar2;
    lVar2 = __ftol();
    *(char *)(param_1 + 0x1f5) = (char)lVar2;
    uVar3 = __ftol();
    *(char *)(param_1 + 0x1f6) = (char)uVar3;
    return uVar3 & 0xffffffff00000000;
  }
  FUN_004356e0();
  uVar1 = extraout_EDX;
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 s_CLTClient__SetSoftwarePSColor_004d614c);
    uVar1 = extraout_EDX_00;
  }
  return CONCAT44(uVar1,0x3c);
}


