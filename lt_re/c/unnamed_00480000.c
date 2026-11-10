/* lithtech.exe decompilation - unnamed_00480000 */
#include "ghidra_types.h"

/* 00480000 size=119 */

undefined4 __thiscall FUN_00480000(void *this,int *param_1,int *param_2)

{
  int iVar1;
  
  if (param_2 != (int *)0x0) {
    iVar1 = (**(code **)(*param_2 + 0x90))();
    if (iVar1 == 0) {
      FUN_0047a130(*(int *)((int)this + 0x244),param_1,param_2[2]);
      return 0;
    }
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 PTR_s_CLTServer_SetObjectSFXMessage_004dc458);
  }
  return 0x3c;
}


/* 00480080 size=126 */

undefined4 __thiscall FUN_00480080(void *this,int *param_1,undefined4 *param_2,uint param_3)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    iVar1 = (**(code **)(*param_1 + 0x90))();
    if (iVar1 == 0) {
      FUN_00489e60(*(int *)((int)this + 0x244),0x12,(int *)param_1[2],0,param_2,param_3);
      return 0;
    }
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                 PTR_s_CLTServer_SendSFXMessage_004dc478);
  }
  return 0x3c;
}


/* 00480100 size=196 */

undefined4 FUN_00480100(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 != (int *)0x0) {
    iVar2 = (**(code **)(*param_1 + 0x90))();
    if (iVar2 == 0) {
      piVar1 = *(int **)(DAT_004ebfa4 + 0xa30);
      if (piVar1 != (int *)0x0) {
        *(undefined2 *)(param_1[2] + 0x38) = 1;
        (**(code **)(*piVar1 + 0x30))
                  (*(undefined4 *)(*(int *)(param_1[5] + 400) + 0x20),param_1[7],param_1);
        return 0;
      }
      FUN_004356e0();
      if (1 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     s_ILTPhysics__SendToServer_004dc498);
      }
      return 0x49;
    }
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_CLTServer_SendToServer_004dc494)
    ;
  }
  return 0x3c;
}


/* 004802d0 size=319 */

void __cdecl FUN_004802d0(uint *param_1,uint *param_2,int *param_3)

{
  uint uVar1;
  int *piVar2;
  float fVar3;
  float *pfVar4;
  int iVar5;
  int *piVar6;
  uint *puVar7;
  uint *local_10;
  
  puVar7 = (uint *)&DAT_004eafc8;
  local_10 = (uint *)&DAT_004eafc8;
  do {
    while( true ) {
      while( true ) {
        if ((*(byte *)((int)param_1 + 0x16) & 3) != 0) {
          if (puVar7 == (uint *)&DAT_004eafc8) {
            return;
          }
          param_1 = (uint *)puVar7[-1];
          puVar7 = puVar7 + -1;
          local_10 = puVar7;
        }
        uVar1 = *param_1;
        if ((uVar1 == 0) || (*(int *)(uVar1 + 0x2c) == 0)) {
          pfVar4 = (float *)0x0;
        }
        else {
          pfVar4 = *(float **)(uVar1 + 0x28);
        }
        fVar3 = ((float)param_2[5] * *pfVar4 +
                (float)param_2[6] * pfVar4[1] + (float)param_2[7] * pfVar4[2]) - pfVar4[3];
        if (fVar3 <= (float)param_2[8]) break;
        param_1 = (uint *)param_1[2];
      }
      if (-(float)param_2[8] <= fVar3) break;
      param_1 = (uint *)param_1[1];
    }
    if (uVar1 != 0) {
      iVar5 = FUN_004175b0(uVar1,(float *)0x0,(float *)0x0);
      if (iVar5 != 0) {
        iVar5 = (**(code **)(*param_3 + 8))(param_1);
        piVar2 = (int *)*param_2;
        piVar6 = piVar2;
        if (piVar2 < piVar2 + param_2[1]) {
          do {
            if ((piVar2 + param_2[2] <= piVar6) || (*piVar6 == iVar5)) break;
            piVar6 = piVar6 + 1;
          } while (piVar6 < piVar2 + param_2[1]);
        }
        if (piVar2 + param_2[2] <= piVar6) {
          if ((piVar2 != (int *)0x0) && (param_2[2] < param_2[1])) {
            piVar2[param_2[2]] = iVar5;
          }
          param_2[2] = param_2[2] + 1;
        }
        puVar7 = local_10;
      }
    }
    if ((*(byte *)(param_1[1] + 0x16) & 3) == 0) {
      *puVar7 = param_1[1];
      puVar7 = puVar7 + 1;
      local_10 = puVar7;
    }
    param_1 = (uint *)param_1[2];
  } while( true );
}


/* 004804f0 size=293 */

void __cdecl FUN_004804f0(float *param_1,float param_2)

{
  int iVar1;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 *local_14;
  float *local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar1 = DAT_004ebfa4;
  local_14 = *(undefined4 **)(DAT_004ebfa4 + 0xbc4);
  if (local_14 == (undefined4 *)0x0) {
    FUN_004b7c60(DAT_004ebfa4 + 0xbac,*(int *)(DAT_004ebfa4 + 0xbb4));
    local_14 = *(undefined4 **)(iVar1 + 0xbc4);
    if (local_14 == (undefined4 *)0x0) goto LAB_00480522;
  }
  *(undefined4 *)(iVar1 + 0xbc4) = *local_14;
LAB_00480522:
  if (local_14 == (undefined4 *)0x0) {
    return;
  }
  local_8 = param_2 * param_2;
  local_14[1] = 0;
  *local_14 = 0;
  local_4 = param_2 + param_2;
  local_c = param_2;
  local_10 = param_1;
  local_20 = *param_1 - param_2;
  local_1c = param_1[1] - param_2;
  local_18 = param_1[2] - param_2;
  local_2c = param_2 + *param_1;
  local_28 = param_2 + param_1[1];
  local_24 = param_2 + param_1[2];
  (**(code **)(*(int *)(DAT_004ebfa4 + 0x210) + 4))(&local_20,&local_2c,&LAB_00480410,&local_14,0);
  DAT_004ebf88 = DAT_004ebf88 + *(int *)((int)local_28 + 4);
  return;
}


/* 00480620 size=80 */

void __cdecl FUN_00480620(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*param_1;
    iVar3 = DAT_004ebfa4;
    while (puVar2 = puVar1, DAT_004ebfa4 = iVar3, puVar2 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)puVar2[1];
      if ((puVar2 != (undefined4 *)0x0) && (iVar3 != -0xbc8)) {
        *puVar2 = *(undefined4 *)(iVar3 + 0xbe0);
        *(undefined4 **)(iVar3 + 0xbe0) = puVar2;
        iVar3 = DAT_004ebfa4;
      }
    }
    if (iVar3 != -0xbac) {
      *param_1 = *(undefined4 *)(iVar3 + 0xbc4);
      *(undefined4 **)(iVar3 + 0xbc4) = param_1;
    }
  }
  return;
}


/* 00480b90 size=1260 */

void __cdecl FUN_00480b90(int param_1)

{
  *(undefined1 **)(param_1 + 0x20) = &LAB_00481080;
  *(undefined1 **)(param_1 + 0x24) = &LAB_004810c0;
  *(undefined1 **)(param_1 + 0x28) = &LAB_004810d0;
  *(undefined1 **)(param_1 + 0x2c) = &LAB_004810e0;
  *(undefined1 **)(param_1 + 0x30) = &LAB_00481110;
  *(undefined1 **)(param_1 + 0x34) = &LAB_00481150;
  *(undefined1 **)(param_1 + 0x38) = &LAB_004811e0;
  *(undefined1 **)(param_1 + 0x3c) = &LAB_00481240;
  *(undefined1 **)(param_1 + 0x40) = &LAB_004818f0;
  *(undefined1 **)(param_1 + 0x44) = &LAB_00481920;
  *(undefined1 **)(param_1 + 0x48) = &LAB_00481be0;
  *(undefined1 **)(param_1 + 0x4c) = &LAB_00481c10;
  *(undefined1 **)(param_1 + 0x50) = &LAB_00481c30;
  *(code **)(param_1 + 0x54) = FUN_00481d80;
  *(code **)(param_1 + 0x58) = FUN_00481c50;
  *(code **)(param_1 + 0x5c) = FUN_0043c4b0;
  *(undefined1 **)(param_1 + 0x60) = &LAB_00447870;
  *(undefined1 **)(param_1 + 100) = &LAB_00440160;
  *(undefined1 **)(param_1 + 0x68) = &LAB_00481e60;
  *(undefined1 **)(param_1 + 0x6c) = &LAB_00481e80;
  *(undefined1 **)(param_1 + 0x70) = &LAB_00481ea0;
  *(code **)(param_1 + 0x74) = FUN_004317e0;
  *(undefined1 **)(param_1 + 0x78) = &LAB_00481ee0;
  *(undefined1 **)(param_1 + 0x7c) = &LAB_00481f00;
  *(undefined1 **)(param_1 + 0x80) = &LAB_00481f30;
  *(undefined1 **)(param_1 + 0x84) = &LAB_00481ff0;
  *(undefined1 **)(param_1 + 0x88) = &LAB_00482040;
  *(undefined1 **)(param_1 + 0x8c) = &LAB_00482060;
  *(undefined1 **)(param_1 + 0x90) = &LAB_00481270;
  *(undefined1 **)(param_1 + 0x94) = &LAB_004812e0;
  *(code **)(param_1 + 0x98) = FUN_004760d0;
  *(undefined1 **)(param_1 + 0x9c) = &LAB_00481300;
  *(code **)(param_1 + 0xa8) = FUN_0047ba00;
  *(code **)(param_1 + 0xac) = FUN_004804f0;
  *(undefined1 **)(param_1 + 0xb0) = &LAB_004813c0;
  *(code **)(param_1 + 0xb4) = FUN_00480620;
  *(undefined1 **)(param_1 + 0x138) = &LAB_004818c0;
  *(undefined1 **)(param_1 + 0x13c) = &LAB_004818d0;
  *(undefined1 **)(param_1 + 0xb8) = &LAB_00480670;
  *(undefined1 **)(param_1 + 0xbc) = &LAB_004806c0;
  *(undefined1 **)(param_1 + 0xc0) = &LAB_00480710;
  *(undefined1 **)(param_1 + 0x10c) = &LAB_00481560;
  *(undefined1 **)(param_1 + 0x110) = &LAB_00481610;
  *(undefined1 **)(param_1 + 0x114) = &LAB_00481610;
  *(undefined1 **)(param_1 + 0x118) = &LAB_00481650;
  *(undefined1 **)(param_1 + 0x11c) = &LAB_00481680;
  *(undefined1 **)(param_1 + 0x120) = &LAB_004816b0;
  *(undefined1 **)(param_1 + 0x124) = &LAB_004816e0;
  *(undefined1 **)(param_1 + 0x128) = &LAB_00481710;
  *(undefined1 **)(param_1 + 300) = &LAB_00481770;
  *(undefined1 **)(param_1 + 0x130) = &LAB_004817c0;
  *(undefined1 **)(param_1 + 0x134) = &LAB_00481890;
  *(undefined1 **)(param_1 + 0xc4) = &LAB_00482080;
  *(undefined1 **)(param_1 + 200) = &LAB_004820e0;
  *(undefined1 **)(param_1 + 0xcc) = &LAB_00482130;
  *(undefined1 **)(param_1 + 0xd0) = &LAB_00482170;
  *(undefined1 **)(param_1 + 0xd4) = &LAB_004821a0;
  *(undefined1 **)(param_1 + 0xd8) = &LAB_004821c0;
  *(undefined1 **)(param_1 + 0xdc) = &LAB_004821f0;
  *(undefined1 **)(param_1 + 0xe0) = &LAB_00482210;
  *(undefined1 **)(param_1 + 0xe4) = &LAB_00482230;
  *(undefined1 **)(param_1 + 0xe8) = &LAB_00482260;
  *(undefined1 **)(param_1 + 0xec) = &LAB_004822c0;
  *(undefined1 **)(param_1 + 0xf0) = &LAB_00482310;
  *(undefined1 **)(param_1 + 0xf4) = &LAB_00482330;
  *(undefined1 **)(param_1 + 0xf8) = &LAB_00482340;
  *(undefined1 **)(param_1 + 0xfc) = &LAB_00482370;
  *(undefined1 **)(param_1 + 0x100) = &LAB_004823d0;
  *(undefined1 **)(param_1 + 0x104) = &LAB_004823f0;
  *(undefined1 **)(param_1 + 0x108) = &LAB_00482420;
  *(undefined1 **)(param_1 + 0x140) = &LAB_00482440;
  *(undefined1 **)(param_1 + 0x144) = &LAB_0043f130;
  *(undefined1 **)(param_1 + 0x1b4) = &LAB_00482480;
  *(undefined1 **)(param_1 + 0x14c) = &LAB_00482540;
  *(undefined1 **)(param_1 + 0x154) = &LAB_00482580;
  *(undefined1 **)(param_1 + 0x150) = &LAB_00482560;
  *(undefined1 **)(param_1 + 0x158) = &LAB_004825a0;
  *(undefined1 **)(param_1 + 0x15c) = &LAB_004825c0;
  *(undefined1 **)(param_1 + 0x160) = &LAB_004825e0;
  *(undefined1 **)(param_1 + 0x164) = &LAB_00482640;
  *(code **)(param_1 + 0x168) = FUN_00482670;
  *(undefined1 **)(param_1 + 0x16c) = &LAB_004826f0;
  *(undefined1 **)(param_1 + 0x170) = &LAB_00483220;
  *(code **)(param_1 + 0x174) = FUN_004835a0;
  *(undefined1 **)(param_1 + 0x178) = &LAB_00483880;
  *(code **)(param_1 + 0x17c) = FUN_00482740;
  *(code **)(param_1 + 0x180) = FUN_004827d0;
  *(undefined1 **)(param_1 + 0x184) = &LAB_00482980;
  *(code **)(param_1 + 0x188) = FUN_00482990;
  *(undefined1 **)(param_1 + 0x18c) = &LAB_00482ae0;
  *(undefined1 **)(param_1 + 400) = &LAB_00482b30;
  *(undefined1 **)(param_1 + 0x194) = &LAB_00482b80;
  *(code **)(param_1 + 0x198) = FUN_00482ba0;
  *(undefined1 **)(param_1 + 0x19c) = &LAB_00482c10;
  *(undefined1 **)(param_1 + 0x1a0) = &LAB_00482c30;
  *(code **)(param_1 + 0x1a4) = FUN_00482c70;
  *(undefined1 **)(param_1 + 0x1a8) = &LAB_00483050;
  *(undefined1 **)(param_1 + 0x1ac) = &LAB_00483160;
  *(undefined1 **)(param_1 + 0x1b0) = &LAB_004831d0;
  *(undefined1 **)(param_1 + 0x1b8) = &LAB_00482d40;
  *(code **)(param_1 + 0x1bc) = FUN_00482dc0;
  *(undefined1 **)(param_1 + 0x1c0) = &LAB_00483030;
  *(undefined1 **)(param_1 + 0x1d4) = &LAB_00483920;
  *(undefined1 **)(param_1 + 0x1d0) = &LAB_00483a60;
  *(code **)(param_1 + 0x1d8) = FUN_00483940;
  *(undefined1 **)(param_1 + 0x1c4) = &LAB_00483a80;
  *(undefined1 **)(param_1 + 0x1cc) = &LAB_00482d10;
  *(undefined1 **)(param_1 + 0x1c8) = &LAB_00482c90;
  *(undefined1 **)(param_1 + 0x1dc) = &LAB_00483c10;
  *(undefined1 **)(param_1 + 0x1e0) = &LAB_00483c40;
  *(undefined1 **)(param_1 + 0x1e4) = &LAB_0040c7a0;
  *(code **)(param_1 + 0x1e8) = FUN_00483c80;
  *(undefined1 **)(param_1 + 0x1ec) = &LAB_0043fda0;
  *(undefined1 **)(param_1 + 0x1f0) = &LAB_0043fe20;
  *(undefined1 **)(param_1 + 500) = &LAB_00483d80;
  *(undefined1 **)(param_1 + 0x200) = &LAB_0043ff00;
  *(code **)(param_1 + 0x204) = FUN_00483e30;
  *(undefined1 **)(param_1 + 0x208) = &LAB_00483f60;
  *(code **)(param_1 + 0x20c) = FUN_00483f80;
  *(code **)(param_1 + 0x210) = FUN_00484030;
  *(undefined1 **)(param_1 + 0x148) = &LAB_0040c830;
  *(undefined1 **)(param_1 + 0x214) = &LAB_004840f0;
  *(undefined1 **)(param_1 + 0x218) = &LAB_00484150;
  *(undefined1 **)(param_1 + 0x21c) = &LAB_00480930;
  *(undefined1 **)(param_1 + 0x220) = &LAB_004809b0;
  *(undefined1 **)(param_1 + 0x224) = &LAB_00480a30;
  *(undefined1 **)(param_1 + 0x228) = &LAB_00480a50;
  *(undefined1 **)(param_1 + 0x22c) = &LAB_00480a60;
  *(undefined1 **)(param_1 + 0x230) = &LAB_00480a80;
  *(undefined1 **)(param_1 + 0x234) = &LAB_00480b40;
  *(undefined1 **)(param_1 + 0x238) = &LAB_00480ae0;
  *(undefined1 **)(param_1 + 0x23c) = &LAB_00480b70;
  *(code **)(param_1 + 0x240) = FUN_00440140;
  return;
}


/* 00481c50 size=296 */

undefined4 __cdecl FUN_00481c50(uint *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_1 == (uint *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTServer__GetNextWMPoly_004dc574)
      ;
      return 0x3c;
    }
  }
  else {
    if (param_2 != 0) {
      iVar1 = (**(code **)**(undefined4 **)(param_2 + 0x1b8))();
      if ((iVar1 != 0) || (iVar1 = *(int *)(param_2 + 0x1b8), iVar1 == 0)) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                       s_ILTServer__GetNextWMPoly_004dc574);
        }
        return 0x42;
      }
      if (*param_1 == 0xffffffff) {
        *param_1 = (uint)*(ushort *)(iVar1 + 0xf8) << 0x10;
        return 0;
      }
      uVar2 = (*param_1 & 0xffff) + 1;
      if (uVar2 < *(uint *)(iVar1 + 0xa4)) {
        *param_1 = (uint)*(ushort *)(iVar1 + 0xf8) << 0x10 | uVar2 & 0xffff;
        return 0;
      }
      *param_1 = 0xffffffff;
      return 2;
    }
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTServer__GetNextWMPoly_004dc574)
      ;
    }
  }
  return 0x3c;
}


/* 00481d80 size=223 */

undefined4 __cdecl FUN_00481d80(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1 == (uint *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTPhysics__GetNextPoly_004dc590);
    }
    return 0x3c;
  }
  if (*(int *)(DAT_004ebfa4 + 0x370) == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTPhysics__GetNextPoly_004dc590);
    }
    return 0x49;
  }
  uVar2 = *param_1;
  if (uVar2 == 0xffffffff) {
    *param_1 = 0xffff;
    return 0;
  }
  uVar1 = uVar2 >> 0x10;
  uVar2 = (uVar2 & 0xffff) + 1;
  if (*(uint *)(*(int *)(*(int *)(*(int *)(DAT_004ebfa4 + 0x330) + uVar1 * 4) + 4) + 0x74) <= uVar2)
  {
    uVar1 = uVar1 + 1;
    uVar2 = 0;
  }
  if (uVar1 < *(uint *)(DAT_004ebfa4 + 0x334)) {
    *param_1 = uVar1 << 0x10 | uVar2 & 0xffff;
    return 0;
  }
  return 2;
}


/* 00482670 size=122 */

undefined4 __cdecl FUN_00482670(int param_1,undefined4 *param_2)

{
  int *piVar1;
  undefined4 uVar2;
  
  if ((param_1 == 0) || (param_2 == (undefined4 *)0x0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_ILTPhysics__CreateSmartLink_004dc698);
    }
    return 0x3c;
  }
  uVar2 = 0;
  *param_2 = 0;
  piVar1 = FUN_004454d0(param_1);
  *param_2 = piVar1;
  if (piVar1 != (int *)0x0) {
    uVar2 = FUN_004457d0(DAT_004ebfa4,param_1,(int)piVar1,3);
  }
  return uVar2;
}


/* 00482740 size=143 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_00482740(int param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  if (param_1 == 0) {
    return 0;
  }
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
  return 1;
}


/* 004827d0 size=177 */

undefined4 __cdecl FUN_004827d0(int param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  
  if (param_1 == 0) {
    return 0;
  }
  lVar1 = __ftol();
  lVar2 = __ftol();
  lVar3 = __ftol();
  lVar4 = __ftol();
  if ((((*(char *)(param_1 + 0x94) != (char)lVar1) || (*(char *)(param_1 + 0x95) != (char)lVar2)) ||
      (*(char *)(param_1 + 0x96) != (char)lVar3)) || (*(char *)(param_1 + 0x97) != (char)lVar4)) {
    *(char *)(param_1 + 0x94) = (char)lVar1;
    *(char *)(param_1 + 0x95) = (char)lVar2;
    *(char *)(param_1 + 0x96) = (char)lVar3;
    *(char *)(param_1 + 0x97) = (char)lVar4;
    FUN_00482890(param_1);
  }
  return 1;
}


/* 00482890 size=231 */

void __cdecl FUN_00482890(int param_1)

{
  byte *pbVar1;
  char *pcVar2;
  int iVar3;
  
  iVar3 = DAT_004ebfa4;
  if (((*(uint *)(param_1 + 0x124) & 4) == 0) || ((*(uint *)(param_1 + 0x124) & 1) != 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
    }
  }
  else {
    pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(param_1 + 0xb8) * 8);
    if ((*pcVar2 == '\x01') && (*(int *)(pcVar2 + 4) != 0)) {
      if ((*(short *)(*(int *)(param_1 + 400) + 0x58) == 0) && (*(int *)(DAT_004ebfa4 + 0x664) != 0)
         ) {
        *(undefined4 *)(*(int *)(param_1 + 400) + 0x50) = *(undefined4 *)(DAT_004ebfa4 + 0xb20);
        *(int *)(iVar3 + 0xb20) = param_1;
      }
      pbVar1 = (byte *)(*(int *)(param_1 + 400) + 0x58);
      *pbVar1 = *pbVar1 | 0x40;
      return;
    }
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
      return;
    }
  }
  return;
}


/* 00482990 size=321 */

undefined4 __cdecl FUN_00482990(int param_1,int param_2)

{
  byte *pbVar1;
  char *pcVar2;
  int iVar3;
  
  if (param_1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_ILTPhysics__SetObjectUserFlags_004dc6d8);
    }
    return 1;
  }
  if (*(int *)(param_1 + 0x90) != param_2) {
    *(int *)(param_1 + 0x90) = param_2;
    iVar3 = DAT_004ebfa4;
    if (((*(uint *)(param_1 + 0x124) & 4) == 0) || ((*(uint *)(param_1 + 0x124) & 1) != 0)) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
      }
    }
    else {
      pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(param_1 + 0xb8) * 8);
      if ((*pcVar2 == '\x01') && (*(int *)(pcVar2 + 4) != 0)) {
        if ((*(short *)(*(int *)(param_1 + 400) + 0x58) == 0) &&
           (*(int *)(DAT_004ebfa4 + 0x664) != 0)) {
          *(undefined4 *)(*(int *)(param_1 + 400) + 0x50) = *(undefined4 *)(DAT_004ebfa4 + 0xb20);
          *(int *)(iVar3 + 0xb20) = param_1;
        }
        pbVar1 = (byte *)(*(int *)(param_1 + 400) + 0x58);
        *pbVar1 = *pbVar1 | 8;
        return 0;
      }
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
        return 0;
      }
    }
  }
  return 0;
}


/* 00482ba0 size=109 */

void __cdecl FUN_00482ba0(int *param_1,undefined4 param_2)

{
  if (param_1 != (int *)0x0) {
    *(undefined4 *)(param_1[100] + 0x14) = param_2;
    *(undefined4 *)(param_1[100] + 0x18) = param_2;
    if ((param_1[0x49] & 0x20U) != 0) {
      FUN_0047a260(DAT_004ebfa4,(int)param_1,param_1[0x49] & 0x18);
    }
    if (((DAT_004e9930 != 0) && (param_1[0x16] == -1)) || (*(int *)(DAT_004ebfa4 + 0x370) == 0)) {
      FUN_004a3df0((void *)(DAT_004ebfa4 + 0x210),param_1);
    }
  }
  return;
}


/* 00482c70 size=32 */

void __cdecl FUN_00482c70(int param_1,float *param_2)

{
  if (param_1 != 0) {
    FUN_00492ed0(DAT_004ebfa4,param_1,param_2);
  }
  return;
}


/* 00482dc0 size=21 */

void __cdecl FUN_00482dc0(int param_1,float *param_2)

{
  FUN_00482de0(param_1,param_2,1);
  return;
}


/* 00482de0 size=586 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_00482de0(int param_1,float *param_2,int param_3)

{
  ushort *puVar1;
  char *pcVar2;
  int iVar3;
  float local_6c;
  undefined4 local_68;
  int local_64;
  uint local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_8;
  undefined4 local_4;
  
  local_6c = 0.0;
  local_68 = 0;
  local_64 = 0;
  local_8 = 0;
  local_4 = 0;
  if (param_1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_ILTPhysics__SetObjectRotation_004dc718);
    }
    return 1;
  }
  if ((((ABS(*(float *)(param_1 + 0x9c) - *param_2) <= (float)_DAT_004cd628) &&
       (ABS(*(float *)(param_1 + 0xa0) - param_2[1]) <= (float)_DAT_004cd628)) &&
      (ABS(*(float *)(param_1 + 0xa4) - param_2[2]) <= (float)_DAT_004cd628)) &&
     (ABS(*(float *)(param_1 + 0xa8) - param_2[3]) <= (float)_DAT_004cd628)) {
    return 0;
  }
  if ((*(char *)(param_1 + 0xbc) == '\x02') || (*(char *)(param_1 + 0xbc) == '\t')) {
    local_68 = *(undefined4 *)(DAT_004ebfa4 + 0x8b4);
    local_6c = (float)(DAT_004ebfa4 + 0x210);
    local_60 = (uint)*(byte *)(param_1 + 0xbd);
    local_64 = param_1;
    local_5c = 0;
    local_58 = 0;
    FUN_004636a0(&local_6c,param_2,(uint)(param_3 == 0));
  }
  else {
    *(float *)(param_1 + 0x9c) = *param_2;
    *(float *)(param_1 + 0xa0) = param_2[1];
    *(float *)(param_1 + 0xa4) = param_2[2];
    *(float *)(param_1 + 0xa8) = param_2[3];
  }
  iVar3 = DAT_004ebfa4;
  if (((*(uint *)(param_1 + 0x124) & 4) == 0) || ((*(uint *)(param_1 + 0x124) & 1) != 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
    }
  }
  else {
    pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(param_1 + 0xb8) * 8);
    if ((*pcVar2 == '\x01') && (*(int *)(pcVar2 + 4) != 0)) {
      if ((*(short *)(*(int *)(param_1 + 400) + 0x58) == 0) && (*(int *)(DAT_004ebfa4 + 0x664) != 0)
         ) {
        *(undefined4 *)(*(int *)(param_1 + 400) + 0x50) = *(undefined4 *)(DAT_004ebfa4 + 0xb20);
        *(int *)(iVar3 + 0xb20) = param_1;
      }
      puVar1 = (ushort *)(*(int *)(param_1 + 400) + 0x58);
      *puVar1 = *puVar1 | -(ushort)(param_3 != 0) & 0x400 | 4;
      return 0;
    }
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
      return 0;
    }
  }
  return 0;
}


/* 004835a0 size=731 */

undefined4 __thiscall FUN_004835a0(void *this,undefined4 *param_1)

{
  byte *pbVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined2 uVar7;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  
  if (param_1 == (undefined4 *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_ILTPhysics__RemoveAttachment_004dc794);
    }
    return 0x3c;
  }
  iVar5 = FUN_0047a090(DAT_004ebfa4,
                       CONCAT22((short)((uint)this >> 0x10),*(undefined2 *)(param_1 + 7)));
  if (iVar5 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_ILTPhysics__RemoveAttachment_004dc794);
    }
    return 1;
  }
  iVar6 = FUN_0046a930(DAT_004ebfa4 + 0x394,iVar5,param_1);
  iVar4 = DAT_004ebfa4;
  if (iVar6 != 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   s_ILTPhysics__RemoveAttachment_004dc794);
    }
    return 0x3d;
  }
  if (((*(uint *)(iVar5 + 0x124) & 4) == 0) || ((*(uint *)(iVar5 + 0x124) & 1) != 0)) {
    FUN_004356e0();
    uVar7 = extraout_var_00;
  }
  else {
    pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(iVar5 + 0xb8) * 8);
    if ((*pcVar2 == '\x01') && (iVar6 = *(int *)(pcVar2 + 4), iVar6 != 0)) {
      if ((*(short *)(*(int *)(iVar5 + 400) + 0x58) == 0) &&
         (iVar6 = 0, *(int *)(DAT_004ebfa4 + 0x664) != 0)) {
        iVar6 = *(int *)(DAT_004ebfa4 + 0xb20);
        *(int *)(*(int *)(iVar5 + 400) + 0x50) = iVar6;
        *(int *)(iVar4 + 0xb20) = iVar5;
      }
      uVar7 = (undefined2)((uint)iVar6 >> 0x10);
      pbVar1 = (byte *)(*(int *)(iVar5 + 400) + 0x59);
      *pbVar1 = *pbVar1 | 1;
      goto LAB_0048372c;
    }
    FUN_004356e0();
    uVar7 = extraout_var;
  }
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
    uVar7 = extraout_var_01;
  }
LAB_0048372c:
  iVar5 = FUN_0047a090(DAT_004ebfa4,CONCAT22(uVar7,*(undefined2 *)((int)param_1 + 0x1e)));
  if (iVar5 != 0) {
    uVar3 = *(uint *)(iVar5 + 0x124);
    *(uint *)(iVar5 + 0x124) = uVar3 & 0xfffffbff;
    iVar4 = DAT_004ebfa4;
    if (((uVar3 & 4) == 0) || ((uVar3 & 1) != 0)) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
      }
    }
    else {
      pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(iVar5 + 0xb8) * 8);
      if ((*pcVar2 == '\x01') && (*(int *)(pcVar2 + 4) != 0)) {
        if ((*(short *)(*(int *)(iVar5 + 400) + 0x58) == 0) && (*(int *)(DAT_004ebfa4 + 0x664) != 0)
           ) {
          *(undefined4 *)(*(int *)(iVar5 + 400) + 0x50) = *(undefined4 *)(DAT_004ebfa4 + 0xb20);
          *(int *)(iVar4 + 0xb20) = iVar5;
        }
        pbVar1 = (byte *)(*(int *)(iVar5 + 400) + 0x59);
        *pbVar1 = *pbVar1 | 1;
        return 0;
      }
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
        return 0;
      }
    }
  }
  return 0;
}


/* 00483940 size=288 */

undefined4 __cdecl FUN_00483940(int param_1,int param_2)

{
  byte *pbVar1;
  char *pcVar2;
  int iVar3;
  
  if (param_1 == 0) {
    return 1;
  }
  if (*(char *)(param_1 + 0xbc) != '\x03') {
    return 1;
  }
  if (*(int *)(param_1 + 0x1c4) != param_2) {
    *(int *)(param_1 + 0x1c4) = param_2;
    iVar3 = DAT_004ebfa4;
    if (((*(uint *)(param_1 + 0x124) & 4) == 0) || ((*(uint *)(param_1 + 0x124) & 1) != 0)) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
      }
    }
    else {
      pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(param_1 + 0xb8) * 8);
      if ((*pcVar2 == '\x01') && (*(int *)(pcVar2 + 4) != 0)) {
        if ((*(short *)(*(int *)(param_1 + 400) + 0x58) == 0) &&
           (*(int *)(DAT_004ebfa4 + 0x664) != 0)) {
          *(undefined4 *)(*(int *)(param_1 + 400) + 0x50) = *(undefined4 *)(DAT_004ebfa4 + 0xb20);
          *(int *)(iVar3 + 0xb20) = param_1;
        }
        pbVar1 = (byte *)(*(int *)(param_1 + 400) + 0x58);
        *pbVar1 = *pbVar1 | 0x20;
        return 0;
      }
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
        return 0;
      }
    }
  }
  return 0;
}


/* 00483c80 size=254 */

void __cdecl FUN_00483c80(int param_1,undefined4 param_2)

{
  byte *pbVar1;
  char *pcVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0xbc) == '\x04') {
    *(undefined4 *)(param_1 + 0x1b0) = param_2;
    iVar3 = DAT_004ebfa4;
    if (((*(uint *)(param_1 + 0x124) & 4) == 0) || ((*(uint *)(param_1 + 0x124) & 1) != 0)) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
      }
    }
    else {
      pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(param_1 + 0xb8) * 8);
      if ((*pcVar2 == '\x01') && (*(int *)(pcVar2 + 4) != 0)) {
        if ((*(short *)(*(int *)(param_1 + 400) + 0x58) == 0) &&
           (*(int *)(DAT_004ebfa4 + 0x664) != 0)) {
          *(undefined4 *)(*(int *)(param_1 + 400) + 0x50) = *(undefined4 *)(DAT_004ebfa4 + 0xb20);
          *(int *)(iVar3 + 0xb20) = param_1;
        }
        pbVar1 = (byte *)(*(int *)(param_1 + 400) + 0x58);
        *pbVar1 = *pbVar1 | 0x40;
        return;
      }
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
        return;
      }
    }
  }
  return;
}


/* 00483e30 size=297 */

void __cdecl FUN_00483e30(int param_1,int param_2)

{
  byte *pbVar1;
  char *pcVar2;
  int iVar3;
  ushort uVar4;
  
  if (*(char *)(param_1 + 0xbc) == '\x01') {
    uVar4 = *(ushort *)(param_1 + 0x1e8);
    if ((uVar4 & 1) != (ushort)(param_2 != 0)) {
      if (param_2 == 0) {
        uVar4 = uVar4 & 0xfffe;
      }
      else {
        uVar4 = uVar4 | 1;
      }
      *(ushort *)(param_1 + 0x1e8) = uVar4;
      iVar3 = DAT_004ebfa4;
      if (((*(uint *)(param_1 + 0x124) & 4) == 0) || ((*(uint *)(param_1 + 0x124) & 1) != 0)) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c)
          ;
        }
      }
      else {
        pcVar2 = (char *)(*(int *)(DAT_004ebfa4 + 0xb10) + (uint)*(ushort *)(param_1 + 0xb8) * 8);
        if ((*pcVar2 == '\x01') && (*(int *)(pcVar2 + 4) != 0)) {
          if ((*(short *)(*(int *)(param_1 + 400) + 0x58) == 0) &&
             (*(int *)(DAT_004ebfa4 + 0x664) != 0)) {
            *(undefined4 *)(*(int *)(param_1 + 400) + 0x50) = *(undefined4 *)(DAT_004ebfa4 + 0xb20);
            *(int *)(iVar3 + 0xb20) = param_1;
          }
          pbVar1 = (byte *)(*(int *)(param_1 + 400) + 0x58);
          *pbVar1 = *pbVar1 | 0x20;
          return;
        }
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c)
          ;
          return;
        }
      }
    }
  }
  return;
}


/* 00483f80 size=175 */

undefined4 __cdecl FUN_00483f80(int param_1,char *param_2,int param_3,char *param_4,int param_5)

{
  int *piVar1;
  char *pcVar2;
  size_t sVar3;
  
  if (param_1 == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 0xbc) != '\x01') {
    return 0;
  }
  if ((param_2 != (char *)0x0) && (0 < param_3)) {
    piVar1 = *(int **)(*(int *)(param_1 + 400) + 0x30);
    if (piVar1 == (int *)0x0) {
      *param_2 = '\0';
    }
    else {
      sVar3 = param_3 - 1;
      pcVar2 = FUN_0047b9b0(DAT_004ebfa4 + 0xc3c,piVar1);
      _strncpy(param_2,pcVar2,sVar3);
    }
  }
  if ((param_4 != (char *)0x0) && (0 < param_5)) {
    piVar1 = *(int **)(*(int *)(param_1 + 400) + 0x34);
    if (piVar1 != (int *)0x0) {
      sVar3 = param_5 - 1;
      pcVar2 = FUN_0047b9b0(DAT_004ebfa4 + 0xc3c,piVar1);
      _strncpy(param_4,pcVar2,sVar3);
      return 1;
    }
    *param_4 = '\0';
  }
  return 1;
}


