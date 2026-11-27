/* lithtech.exe decompilation - module clientmgr */
#include "ghidra_types.h"

/* 00410250 size=984 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/client/src/clientmgr.cpp */

uint __thiscall
clientmgr_410250(void *this,undefined4 *param_1,uint param_2,LPCSTR param_3,int *param_4)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  LONG LVar5;
  int iVar6;
  void *this_00;
  undefined4 unaff_EDI;
  undefined4 *puVar7;
  undefined4 local_2d4 [3];
  int local_2c8;
  char acStack_2c4 [32];
  undefined1 auStack_2a4 [64];
  undefined4 local_264 [20];
  char acStack_214 [532];
  
  FUN_00470f80(1);
  FUN_0044f590();
  FUN_00411370((int)this);
  *(undefined1 *)((int)this + 0x1608) = 10;
  *(undefined4 *)((int)this + 0x162c) = 1;
  *(undefined4 *)((int)this + 0x1630) = 0;
  *(undefined2 *)((int)this + 0x22bc) = 0;
  FUN_004a3d40((void *)((int)this + 0x6c),(int)this + 0x1f0);
  puVar1 = FUN_00404d60((int)this);
  *(undefined4 **)((int)this + 0x4c4) = puVar1;
  *(undefined4 *)((int)this + 0x1614) = 0;
  *(undefined4 *)((int)this + 0x1610) = 0;
  *(undefined4 *)((int)this + 0x160c) = 0;
  puVar1 = (undefined4 *)((int)this + 0x13bc);
  for (iVar6 = 0x7f; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  *(undefined2 *)puVar1 = 0;
  *(undefined4 *)((int)this + 0x15bc) = 0;
  if (param_2 < 0x15) {
    if (param_2 == 0) {
      FUN_004267b0((int)this,0x39,(char)unaff_EDI);
      FUN_004267e0((int)this,0x4000039);
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientMgr__Init_004d65f8);
      }
      return 0x39;
    }
  }
  else {
    param_2 = 0x14;
  }
  puVar1 = param_1;
  puVar7 = (undefined4 *)((int)this + 0x1648);
  for (iVar6 = 0x14; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar7 = puVar7 + 1;
  }
  *(uint *)((int)this + 0x1698) = param_2;
  FUN_00404640(*(undefined4 **)((int)this + 0x1644),param_1,param_2,local_264,&local_2c8);
  if (local_2c8 == 0) {
    FUN_004267b0((int)this,0x1b,(char)*param_1);
    FUN_004267e0((int)this,0x1b);
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientMgr__Init_004d65f8);
    }
    return 0x1b;
  }
  uVar2 = dsys_interface_4361b0((int)this);
  if (uVar2 != 0) {
    FUN_004267e0((int)this,uVar2 | 0x4000000);
    return uVar2;
  }
  FUN_00423ff0();
  FUN_00420e10();
  FUN_00436730((undefined4 *)((int)this + 0x12e0));
  version_info_4a1430((undefined4 *)((int)this + 0x12e0),acStack_2c4,0x20);
  FUN_004b9f62(auStack_2a4,(byte *)s_version__s_004d65e8,acStack_2c4);
  FUN_00420080(&DAT_004e9500,(byte)auStack_2a4);
  iVar6 = FUN_00436500();
  if (iVar6 != 0) {
    iVar6 = (*(code *)**(undefined4 **)((int)this + 0x1618))
                      (*(undefined4 **)((int)this + 0x1618),&DAT_004e9500);
    if (iVar6 == 0) {
      FUN_004267e0((int)this,0x400001c);
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientMgr__Init_004d65f8);
      }
      return 0x1c;
    }
  }
  _DAT_004e9560 = this;
  FUN_004128b0(this,param_3);
  clientmgr_4127d0(this,2,param_4);
  errorlog_4376e0();
  uVar3 = FUN_004366c0();
  *(undefined4 *)((int)this + 0x10f8) = uVar3;
  uVar3 = FUN_004366b0();
  *(undefined4 *)((int)this + 0x10fc) = uVar3;
  if (DAT_004e98d0 != 0) {
    FUN_00436670((byte *)s_Warning__NullRender_is_ON__004d65c8,unaff_EDI);
  }
  FUN_004128b0(this,param_3);
  clientmgr_4127d0(this,1,param_4);
  *(undefined4 *)((int)this + 0x1628) = 1;
  *(undefined4 *)((int)this + 0x508) = 0;
  puVar1 = FUN_00448670(this);
  *(undefined4 **)((int)this + 0x1724) = puVar1;
  GameClientShell_410190(acStack_214);
  uVar2 = (**(code **)(**(int **)((int)this + 0x620) + 0x4c))(acStack_214,(int)this + 0x600);
  piVar4 = FUN_004a16f0(this_00,this,&DAT_004d65c0);
  *(int **)((int)this + 0x1720) = piVar4;
  if (piVar4 != (int *)0x0) {
    (**(code **)(*piVar4 + 0xc))();
  }
  FUN_00431bc0((void *)((int)this + 0x1300),*(int *)((int)this + 0x4c4),local_2d4 + -3);
  puVar1 = DAT_004e5128;
  if (DAT_004e5128 != (undefined4 *)0x0) {
    LVar5 = InterlockedDecrement(DAT_004e5128 + 1);
    if ((LVar5 < 1) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
    DAT_004e5128 = (undefined4 *)0x0;
  }
  return uVar2;
}


/* 00410b20 size=1397 */

/* repo: runtime/client/src/clientmgr.cpp, runtime/kernel/net/src/sys/win/udpdriver.cpp,
   runtime/client/src/clientde_impl.cpp */

uint __thiscall clientmgr_410b20(void *this,int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int *this_00;
  int *local_20c;
  undefined4 uStack_208;
  uint uStack_204;
  char acStack_200 [256];
  char acStack_100 [256];
  
  this_00 = (int *)0x0;
  local_20c = this;
  FUN_004110a0((int)this);
  puVar1 = (undefined4 *)FUN_00430de0(0x90);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1 = FUN_00414dd0(puVar1);
  }
  puVar1[0x21] = *param_1;
  FUN_00414ec0(puVar1,this);
  FUN_00436600(0);
  iVar2 = *param_1;
  if (iVar2 == 2) {
    local_20c = *(int **)((int)this + 0x610);
    if (local_20c == (int *)0x0) {
LAB_00410e08:
      FUN_004356e0();
      if (DAT_004e4420 < 1) {
        return 0x49;
      }
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_StartGame_004d6664);
      return 0x49;
    }
    if ((*(byte *)(param_1 + 0x479) & 1) == 0) {
      if (param_1[0x65] == 0) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_StartGame_004d6664);
        }
        return 0x3c;
      }
      uVar3 = (**(code **)(*local_20c + 0x34))(param_1[0x65]);
      if (uVar3 != 0) {
        return uVar3;
      }
    }
    else {
      iVar2 = (**(code **)(*local_20c + 0x4c))();
      if (iVar2 == 0) {
LAB_00410c06:
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_StartGame_004d6664);
        }
        return 1;
      }
    }
    uVar3 = FUN_00414ff0(puVar1,local_20c);
    if (uVar3 != 0) {
      return uVar3;
    }
    goto LAB_00410f26;
  }
  if (iVar2 == 3) {
    piVar4 = (int *)FUN_00467ac0((void *)((int)this + 0x510),(byte *)s_internet_004d5ec0);
    if (piVar4 == (int *)0x0) goto LAB_00410e08;
    uVar3 = (**(code **)(*piVar4 + 0x54))(param_1 + 0x1a);
    if (uVar3 != 0) {
      return uVar3;
    }
    uVar3 = FUN_00414ff0(puVar1,piVar4);
    if (uVar3 != 0) {
      return uVar3;
    }
    this = local_20c;
    goto LAB_00410f26;
  }
  local_20c = (int *)0x0;
  if (iVar2 == 0) {
    local_20c = *(int **)((int)this + 0x610);
    if (local_20c == (int *)0x0) {
      FUN_004356e0();
      if (DAT_004e4420 < 1) {
        return 0x49;
      }
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_StartGame_004d6664);
      return 0x49;
    }
    if ((*(byte *)(param_1 + 0x479) & 1) == 0) {
      uVar3 = (**(code **)(*local_20c + 0x30))(param_1 + 0x66);
      if (uVar3 != 0) {
        return uVar3;
      }
    }
    else {
      iVar2 = (**(code **)(*local_20c + 0x48))();
      if (iVar2 != 0) goto LAB_00410c06;
    }
  }
  if ((char)param_1[0x33] == '\0') {
    if ((char)param_1[0x4c] != '\0') {
      uStack_204 = FUN_00434040((void *)((int)this + 0x169c),(LPCSTR)(param_1 + 0x4c));
      if (uStack_204 != 0) {
        if (puVar1 == (undefined4 *)0x0) {
          return uStack_204;
        }
        (**(code **)*puVar1)(1);
        return uStack_208;
      }
      goto LAB_00410cf0;
    }
  }
  else {
    uStack_204 = FUN_00433f60((void *)((int)this + 0x169c),param_1 + 1,(LPCSTR)(param_1 + 0x33));
    if (uStack_204 != 0) {
      if (puVar1 == (undefined4 *)0x0) {
        return uStack_204;
      }
      (**(code **)*puVar1)(1);
      return uStack_208;
    }
LAB_00410cf0:
    *(undefined1 *)(param_1 + 1) = 0;
  }
  uStack_204 = clientshell_415000(puVar1,(int)param_1,(uint)(*param_1 == 0),(int)local_20c);
  if (uStack_204 != 0) {
    if (puVar1 == (undefined4 *)0x0) {
      return uStack_204;
    }
    (**(code **)*puVar1)(1);
    return uStack_208;
  }
  if (((char)param_1[1] == '\0') ||
     (iVar2 = RiotClientShell_487d10((void *)puVar1[0x10],(uint)(param_1 + 1)), iVar2 != 0)) {
    FUN_004869b0((void *)puVar1[0x10],acStack_200,0x100);
    FUN_004267b0((int)this,0x31,'\0');
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
    }
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientMgr__StartShell_004d6628);
    }
    return 0x31;
  }
  if ((char)param_1[0x4c] != '\0') {
    _strncpy((char *)(param_1 + 1),acStack_100,99);
    *(undefined1 *)((int)param_1 + 0x67) = 0;
  }
LAB_00410f26:
  *(undefined4 **)((int)this + 0x161c) = puVar1;
  FUN_00412730((int)this);
  if (*(int *)((int)this + 0x161c) != 0) {
    puVar1 = FUN_0046b170(&local_20c,0x44c,0x44c);
    this_00 = (int *)*puVar1;
    if (this_00 != (int *)0x0) {
      (**(code **)(*this_00 + 4))();
    }
    if (local_20c != (int *)0x0) {
      (**(code **)(*local_20c + 8))();
    }
    uStack_204 = CONCAT22((*(uint16_t*)((char*)&uStack_204+2)),(short)param_1[0x47d]);
    if (*(ushort *)(this_00 + 0xe) + 2 < (uint)*(ushort *)((int)this_00 + 0x36)) {
      if ((uint)this_00[0x16] <= *(ushort *)(this_00 + 0xd) + 2) {
        do {
          uStack_208 = uStack_208 & 0xffffff;
          FUN_00414b10(this_00 + 0x14,(undefined1 *)this_00[0x16],
                       (undefined1 *)((int)&uStack_208 + 3),&DAT_004ecc58);
        } while ((uint)this_00[0x16] <= *(ushort *)(this_00 + 0xd) + 2);
      }
      *(undefined2 *)(this_00[0x15] + (uint)*(ushort *)(this_00 + 0xe)) = (undefined2)uStack_204;
      uVar3 = 0;
      *(short *)(this_00 + 0xe) = (short)this_00[0xe] + 2;
      *(short *)(this_00 + 0xd) = (short)this_00[0xd] + 2;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      uVar3 = this_00[0x10] | 4;
      this_00[0x10] = uVar3;
    }
    FUN_0046b480(this_00,(undefined4 *)param_1[0x47c],
                 CONCAT22((short)(uVar3 >> 0x10),(short)param_1[0x47d]));
    *(undefined1 *)this_00[0x15] = 5;
    FUN_004657c0((int *)((int)this + 0x510),this_00,*(float **)(*(int *)((int)this + 0x161c) + 0x34)
                 ,0x80);
  }
  iVar2 = *param_1;
  if (((iVar2 != 0) && (iVar2 != 1)) && (iVar2 != 4)) {
    FUN_00410630((int)this);
  }
  if (this_00 != (int *)0x0) {
    (**(code **)(*this_00 + 8))();
  }
  return 0;
}


/* 004110d0 size=375 */

/* repo: runtime/client/src/clientmgr.cpp, Blood2/ClientShellDLL/Music.cpp,
   Shogo/ClientShellDLL/Music.cpp */

undefined4 __thiscall clientmgr_4110d0(void *this,char *param_1)

{
  char *_Dest;
  int iVar1;
  char cVar2;
  
  if ((DAT_004d834c == 0) || (DAT_004e992c != 0)) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientMgr__AppInitMusic_004d6678)
      ;
    }
    return 1;
  }
  _Dest = (char *)((int)this + 0x1104);
  if (param_1 == (char *)0x0) {
    param_1 = s_cdaudio_dll_004d6698;
  }
  _strncpy(_Dest,param_1,0xff);
  *(undefined1 *)((int)this + 0x1203) = 0;
  iVar1 = musicdriver_4643e0(_Dest,(undefined4 *)((int)this + 0x1094));
  cVar2 = (char)_Dest;
  if (iVar1 == 1) {
    FUN_004267b0((int)this,0x24,cVar2);
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientMgr__AppInitMusic_004d6678)
      ;
    }
    return 0x24;
  }
  if (iVar1 == 2) {
    FUN_004267b0((int)this,0x25,cVar2);
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientMgr__AppInitMusic_004d6678)
      ;
    }
    return 0x25;
  }
  if (iVar1 != 3) {
    return 0;
  }
  FUN_004267b0((int)this,0x26,cVar2);
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CClientMgr__AppInitMusic_004d6678);
  }
  return 0x26;
}


/* 00411810 size=175 */

/* repo: runtime/client/src/clientmgr.cpp, runtime/server/src/server_iltsoundmgr.cpp,
   runtime/sound/src/soundmgr.cpp */

int __thiscall clientmgr_411810(void *this,uint *param_1,int *param_2)

{
  int *piVar1;
  undefined1 *puVar2;
  int iVar3;
  longlong lVar4;
  
  if (((param_1 != (uint *)0x0) && (*(int *)((int)this + 0x8a8) != 0)) &&
     (*(int *)((int)this + 0x8ac) != 0)) {
    piVar1 = FUN_004047a0(*(int *)((int)this + 0x1644),param_2,'\x04');
    if (piVar1 != (int *)0x0) {
      lVar4 = __ftol();
      iVar3 = FUN_004984a0((void *)((int)this + 0x784),param_1,piVar1,(int)lVar4);
      if (iVar3 == 0) {
        (**(code **)(**(int **)((int)this + 0x620) + 100))(param_1);
        return 0;
      }
      return iVar3;
    }
    puVar2 = FUN_004046f0(*(int *)((int)this + 0x1644),param_2);
    if (1 < DAT_004e4420) {
      FUN_00436670((byte *)s_Missing_sound_file__s_004d66a4,puVar2);
    }
  }
  return 1;
}


/* 004118c0 size=83 */

/* repo: runtime/client/src/clientmgr.cpp */

void __fastcall clientmgr_4118c0(int param_1)

{
  if ((*(int *)(param_1 + 0x8a8) != 0) && (*(int *)(param_1 + 0x8ac) != 0)) {
    FUN_00497b00((int *)(param_1 + 0x784));
    if (DAT_004e9910 != 0) {
      FUN_00420e80(0xff0000,0,(byte *)s_Sounds__playing__d__heard__d_004d66bc,
                   *(undefined4 *)(param_1 + 0xea8));
    }
  }
  return;
}


/* 00411920 size=922 */

/* repo: runtime/client/src/clientmgr.cpp, Blood2/ClientShellDLL/Music.cpp,
   Shogo/ClientShellDLL/Music.cpp */

undefined4 * clientmgr_411920(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  void *pvVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  float local_c [3];
  
  puVar2 = (undefined4 *)FUN_00430de0(0x22c8);
  if (puVar2 != (undefined4 *)0x0) {
    FUN_00428e80(puVar2);
    FUN_00468570(puVar2 + 0x7c);
    FUN_00413050(local_c,0,0xc4fa0000,0);
    FUN_00411ce0(puVar2 + 0x132,local_c);
    puVar2[0x13e] = 0xbf350481;
    FUN_00464770(puVar2 + 0x144);
    FUN_004963f0(puVar2 + 0x1e1);
    FUN_00411cc0(puVar2 + 0x484);
    FUN_00411cc0(puVar2 + 0x488);
    FUN_00414770(puVar2 + 0x493);
    FUN_004798d0(puVar2 + 0x4ac);
    puVar2[0x4b8] = 0xffffffff;
    puVar2[0x4b9] = 0xffffffff;
    FUN_00470b70(puVar2 + 0x4bd);
    FUN_00431a80(puVar2 + 0x4c0);
    FUN_00433eb0((int)(puVar2 + 0x5a7));
    FUN_00417b20(puVar2 + 0x5ae);
    FUN_0046e4e0(puVar2 + 0x5ca);
    FUN_00411370((int)puVar2);
    puVar2[0x5aa] = puVar2;
    puVar2[0x4bb] = 0;
    puVar2[0x4bc] = 0;
    puVar3 = (undefined4 *)FUN_00430de0(0x110);
    if (puVar3 == (undefined4 *)0x0) {
      uVar4 = 0;
    }
    else {
      uVar4 = ltdirectmusic_impl_449460(puVar3);
    }
    puVar2[0x8b0] = uVar4;
    *(undefined1 *)(puVar2 + 0x189) = 0;
    FUN_00430ed0(FUN_00436e70,puVar2);
    puVar2[0x590] = 1;
    puVar2[0x587] = 0;
    puVar2[0x188] = 0;
    puVar2[0x187] = 0;
    puVar2[0x185] = 0;
    uVar7 = 0xffffffff;
    puVar2[0x186] = 0;
    pcVar9 = s_cdaudio_dll_004d6698;
    do {
      pcVar10 = pcVar9;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    pcVar9 = pcVar10 + -uVar7;
    pcVar10 = (char *)(puVar2 + 0x441);
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar10 = pcVar10 + 4;
    }
    puVar3 = puVar2 + 0x485;
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar10 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
    }
    puVar2[0x43c] = 0;
    puVar2[0x581] = 0;
    puVar2[0x58a] = 0;
    puVar2[0x486] = puVar3;
    *puVar3 = puVar3;
    puVar3 = puVar2 + 0x481;
    puVar2[0x484] = 0;
    puVar2[0x482] = puVar3;
    *puVar3 = puVar3;
    puVar2[0x4dd] = 0;
    puVar2[0x1db] = 0x3f800000;
    puVar2[0x1dc] = 0x3f800000;
    puVar2[0x1dd] = 0x3f800000;
    puVar2[0x1de] = 0x3f800000;
    puVar2[0x1df] = 0x3f800000;
    puVar2[0x1e0] = 0x3f800000;
    puVar2[0x1d5] = 0;
    puVar2[0x1d6] = 0;
    puVar2[0x1d7] = 0;
    puVar2[0x1d8] = 0;
    puVar2[0x1d9] = 0;
    puVar2[0x1da] = 0;
    iVar5 = FUN_004040f0(puVar2);
    puVar2[0x591] = iVar5;
    FUN_0046a550((int)(puVar2 + 0x7c),1);
    FUN_004b7be0(puVar2 + 0x48c,10,0x20,0x20);
    FUN_004b7c10((int)(puVar2 + 0x494));
    FUN_004b7be0(puVar2 + 0x494,0x40,0x40,0x40);
    puVar3 = puVar2 + 0x489;
    puVar2[0x48a] = puVar3;
    *puVar3 = puVar3;
    puVar2[0x488] = 0;
    FUN_004438a0(puVar2 + 0x586);
    FUN_00464930(puVar2 + 0x144,s_Player_004d66dc);
    puVar2[0x58f] = 0;
    *(undefined2 *)(puVar2 + 0x4ab) = 0;
    puVar2[0x4ba] = 0;
    puVar2[0x4dc] = 0;
    puVar2[0x4d9] = 0;
    puVar2[0x4db] = 0;
    puVar2[0x56f] = 0;
    puVar2[0x580] = 0;
    puVar2[0x589] = 0;
    puVar2[0x58b] = 0;
    puVar2[0x58c] = 0;
    puVar2[0x58d] = 0;
    puVar2[0x58e] = 0;
    puVar2[0x5a6] = 0;
    pvVar6 = (void *)FUN_00430de0(0x2c8);
    if (pvVar6 == (void *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      puVar3 = FUN_00450760(pvVar6,&DAT_004ecc58,&DAT_004ecc58);
    }
    puVar2[0x5c7] = puVar3;
    puVar3[0x83] = puVar3[0x83] + 1;
    puVar3 = (undefined4 *)FUN_00430de0(8);
    if (puVar3 == (undefined4 *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      *puVar3 = &PTR_LAB_004cbb9c;
      puVar3[1] = puVar2;
    }
    puVar2[0x143] = puVar3;
    pvVar6 = (void *)FUN_00430de0(8);
    if (pvVar6 == (void *)0x0) {
      iVar5 = 0;
    }
    else {
      iVar5 = FUN_004179f0(pvVar6,puVar2);
    }
    puVar2[0x130] = iVar5;
    if (((iVar5 != 0) && (puVar2[0x5c7] != 0)) && (puVar2[0x143] != 0)) {
      iVar5 = FUN_00417b40(puVar2 + 0x5ae,puVar2);
      if (iVar5 != 0) {
        iVar5 = FUN_0044e3f0(puVar2 + 0x5ae,3);
        if (iVar5 == 0) {
          return puVar2;
        }
      }
    }
    clientmgr_411d80(puVar2);
    FUN_00430df0((undefined *)puVar2);
  }
  return (undefined4 *)0x0;
}


/* 00411d80 size=1116 */

/* repo: runtime/client/src/clientmgr.cpp, runtime/kernel/src/sys/win/client.cpp,
   NOLF2/ClientShellDLL/TRON/ScreenControls.cpp */

void __fastcall clientmgr_411d80(void *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  FUN_0044e520((int)param_1 + 0x16b8);
  FUN_004113c0(param_1);
  *(undefined4 *)((int)param_1 + 0x1640) = 0;
  FUN_00412fe0((int)param_1);
  if (*(int **)((int)param_1 + 0x620) != (int *)0x0) {
    (**(code **)(**(int **)((int)param_1 + 0x620) + 0x50))();
  }
  FUN_004109f0((int)param_1);
  iVar1 = (int)param_1 + 0x410;
  iVar2 = 0xb;
  do {
    FUN_00412f90((int)param_1,iVar1,0);
    iVar1 = iVar1 + 0x10;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  FUN_004110a0((int)param_1);
  FUN_004128e0((int)param_1,s_autoexec_cfg_004d57bc);
  (**(code **)(*(int *)((int)param_1 + 0x1618) + 4))(*(int *)((int)param_1 + 0x1618));
  FUN_00437590((int)param_1);
  puVar3 = (undefined4 *)((int)param_1 + 0x1270);
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0xffffffff;
    puVar3 = puVar3 + 1;
  }
  soundmgr_496e50((undefined4 *)((int)param_1 + 0x784),1);
  thunk_FUN_00464490();
  FUN_00431cb0((int *)((int)param_1 + 0x1300));
  FUN_00412200((int)param_1 + 0x1204);
  FUN_00412270((undefined4 *)((int)param_1 + 0x1210));
  FUN_00420e00(1);
  FUN_004649a0((void *)((int)param_1 + 0x510));
  FUN_00471640((int)param_1,2);
  FUN_00426b80((int)param_1);
  FUN_00424080();
  FUN_0046a690((int)param_1 + 0x1f0);
  if (*(undefined **)((int)param_1 + 0x12ec) != (undefined *)0x0) {
    FUN_00430fe0(*(undefined **)((int)param_1 + 0x12ec));
    *(undefined4 *)((int)param_1 + 0x12ec) = 0;
  }
  *(undefined4 *)((int)param_1 + 0x12f0) = 0;
  FUN_004b7c50((int)param_1 + 0x1230);
  thunk_FUN_0040f6a0();
  FUN_0049b5d0(&LAB_004121e0,0);
  if (*(int **)((int)param_1 + 0x1644) != (int *)0x0) {
    FUN_00404200(*(int **)((int)param_1 + 0x1644));
  }
  FUN_00437730();
  if (*(int **)((int)param_1 + 0x4c4) != (int *)0x0) {
    (**(code **)(**(int **)((int)param_1 + 0x4c4) + 0x11c))(1);
    *(undefined4 *)((int)param_1 + 0x4c4) = 0;
  }
  if (*(undefined **)((int)param_1 + 0x50c) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)((int)param_1 + 0x50c));
    *(undefined4 *)((int)param_1 + 0x50c) = 0;
  }
  if (*(undefined **)((int)param_1 + 0x4c0) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)((int)param_1 + 0x4c0));
    *(undefined4 *)((int)param_1 + 0x4c0) = 0;
  }
  iVar1 = *(int *)((int)param_1 + 0x171c);
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0x20c) != 0) {
      *(int *)(iVar1 + 0x20c) = *(int *)(iVar1 + 0x20c) + -1;
    }
    if (*(undefined4 **)((int)param_1 + 0x171c) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)((int)param_1 + 0x171c))(1);
    }
    *(undefined4 *)((int)param_1 + 0x171c) = 0;
  }
  FUN_0044e3b0((undefined4 *)((int)param_1 + 0x16b8));
  thunk_FUN_004341b0((void *)((int)param_1 + 0x169c));
  FUN_00431b40((int *)((int)param_1 + 0x1300));
  *(undefined ***)((int)param_1 + 0x124c) = &PTR_FUN_004cbd94;
  FUN_004b7c10((int)param_1 + 0x1250);
  *(undefined ***)((int)param_1 + 0x124c) = &PTR_LAB_004cb514;
  FUN_004966c0((undefined4 *)((int)param_1 + 0x784));
  FUN_00464870((void *)((int)param_1 + 0x510));
  *(undefined ***)((int)param_1 + 0x3c0) = &PTR_FUN_004cbd84;
  FUN_004b7c10((int)param_1 + 0x3c4);
  *(undefined ***)((int)param_1 + 0x3c0) = &PTR_LAB_004cb514;
  *(undefined ***)((int)param_1 + 0x39c) = &PTR_FUN_004cbd74;
  FUN_004b7c10((int)param_1 + 0x3a0);
  *(undefined ***)((int)param_1 + 0x39c) = &PTR_LAB_004cb514;
  *(undefined ***)((int)param_1 + 0x378) = &PTR_FUN_004cbd64;
  FUN_004b7c10((int)param_1 + 0x37c);
  *(undefined ***)((int)param_1 + 0x378) = &PTR_LAB_004cb514;
  *(undefined ***)((int)param_1 + 0x354) = &PTR_FUN_004cbd54;
  FUN_004b7c10((int)param_1 + 0x358);
  *(undefined ***)((int)param_1 + 0x354) = &PTR_LAB_004cb514;
  *(undefined ***)((int)param_1 + 0x330) = &PTR_FUN_004cbd44;
  FUN_004b7c10((int)param_1 + 0x334);
  *(undefined ***)((int)param_1 + 0x330) = &PTR_LAB_004cb514;
  *(undefined ***)((int)param_1 + 0x30c) = &PTR_FUN_004cbd34;
  FUN_004b7c10((int)param_1 + 0x310);
  *(undefined ***)((int)param_1 + 0x30c) = &PTR_LAB_004cb514;
  *(undefined ***)((int)param_1 + 0x2e8) = &PTR_FUN_004cbd24;
  FUN_004b7c10((int)param_1 + 0x2ec);
  *(undefined ***)((int)param_1 + 0x2e8) = &PTR_LAB_004cb514;
  *(undefined ***)((int)param_1 + 0x2c4) = &PTR_FUN_004cbd14;
  FUN_004b7c10((int)param_1 + 0x2c8);
  *(undefined ***)((int)param_1 + 0x2c4) = &PTR_LAB_004cb514;
  *(undefined ***)((int)param_1 + 0x2a0) = &PTR_FUN_004cbd04;
  FUN_004b7c10((int)param_1 + 0x2a4);
  *(undefined ***)((int)param_1 + 0x2a0) = &PTR_LAB_004cb514;
  *(undefined ***)((int)param_1 + 0x27c) = &PTR_FUN_004cbcf4;
  FUN_004b7c10((int)param_1 + 0x280);
  *(undefined ***)((int)param_1 + 0x27c) = &PTR_LAB_004cb514;
  FUN_004142b0((undefined4 *)((int)param_1 + 600));
  *(undefined4 *)((int)param_1 + 0x19c) = &PTR_LAB_004cbcc4;
  FUN_00468190((undefined4 *)((int)param_1 + 0x19c),0,&DAT_004ecc58);
  *(undefined4 *)((int)param_1 + 0x188) = &PTR_LAB_004cbc94;
  FUN_00468190((undefined4 *)((int)param_1 + 0x188),0,&DAT_004ecc58);
  thunk_FUN_00446310((undefined4 *)((int)param_1 + 0xfc));
  thunk_FUN_004a3950((int)param_1 + 0x78);
  *(undefined4 *)((int)param_1 + 0x54) = &PTR_LAB_004cbc64;
  FUN_004145b0((undefined4 *)((int)param_1 + 0x54),0,&DAT_004ecc58);
  *(undefined4 *)((int)param_1 + 0x40) = &PTR_LAB_004cbb50;
  FUN_0040c870((undefined4 *)((int)param_1 + 0x40),0,&DAT_004ecc58);
  *(undefined4 *)((int)param_1 + 0x2c) = &PTR_LAB_004cbc34;
  FUN_00468190((undefined4 *)((int)param_1 + 0x2c),0,&DAT_004ecc58);
  *(undefined4 *)((int)param_1 + 0x18) = &PTR_LAB_004cbc04;
  if (*(int *)((int)param_1 + 0x1c) != 0) {
    FUN_00433560((undefined4 *)((int)param_1 + 0x18),&DAT_004ecc58);
  }
  *(undefined4 *)((int)param_1 + 0x20) = 0;
  *(undefined ***)((int)param_1 + 4) = &PTR_LAB_004cbbd4;
  if (*(int *)((int)param_1 + 8) != 0) {
    FUN_00456e60(&DAT_004ecc58,*(int *)((int)param_1 + 8));
    *(undefined4 *)((int)param_1 + 8) = 0;
    *(undefined4 *)((int)param_1 + 0x10) = 0;
  }
  *(undefined4 *)((int)param_1 + 0xc) = 0;
  return;
}


/* 004127d0 size=210 */

/* repo: runtime/client/src/clientmgr.cpp */

void __cdecl clientmgr_4127d0(undefined4 param_1,undefined4 param_2,int *param_3)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  undefined1 local_200 [512];
  
  if (param_3 == (int *)0x0) {
    iVar3 = 0;
    if (0 < DAT_004ecc98 + -1) {
      iVar2 = DAT_004ecc9c;
      do {
        pcVar1 = *(char **)(iVar2 + iVar3 * 4);
        if (*pcVar1 == '+') {
          FUN_004b9f62(local_200,(byte *)s___s____s__004d6704,pcVar1 + 1);
          FUN_004200a0(&DAT_004e9500,0);
          iVar2 = DAT_004ecc9c;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < DAT_004ecc98 + -1);
    }
  }
  else {
    iVar3 = 0;
    if (0 < param_3[1]) {
      do {
        pcVar1 = *(char **)(*param_3 + iVar3 * 4);
        if (*pcVar1 == '+') {
          FUN_004b9f62(local_200,(byte *)s___s____s__004d6704,pcVar1 + 1);
          FUN_004200a0(&DAT_004e9500,0);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < param_3[1]);
      return;
    }
  }
  return;
}


/* 00488d30 size=113 */

/* repo: runtime/client/src/clientmgr.cpp, runtime/server/src/server_iltsoundmgr.cpp,
   runtime/sound/src/soundmgr.cpp */

int __fastcall clientmgr_488d30(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  int *piVar6;
  bool bVar7;
  
  uVar4 = 0;
  if (*(uint *)(param_1 + 0x930) != 0) {
    piVar6 = *(int **)(param_1 + 0x92c);
    do {
      pcVar5 = s_local_004d674c;
      pbVar2 = (byte *)(*piVar6 + 4);
      do {
        bVar1 = *pbVar2;
        bVar7 = bVar1 < (byte)*pcVar5;
        if (bVar1 != *pcVar5) {
LAB_00488d7b:
          iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_00488d80;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar7 = bVar1 < (byte)pcVar5[1];
        if (bVar1 != pcVar5[1]) goto LAB_00488d7b;
        pbVar2 = pbVar2 + 2;
        pcVar5 = pcVar5 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00488d80:
      if (iVar3 == 0) {
        return (*(int **)(param_1 + 0x92c))[uVar4];
      }
      uVar4 = uVar4 + 1;
      piVar6 = piVar6 + 1;
    } while (uVar4 < *(uint *)(param_1 + 0x930));
  }
  return 0;
}


/* 0048d890 size=682 */

/* repo: runtime/client/src/clientmgr.cpp, runtime/server/src/servermgr.cpp */

int __cdecl clientmgr_48d890(int param_1,char *param_2,int param_3,int *param_4)

{
  undefined1 uVar1;
  void *this;
  undefined4 *puVar2;
  int iVar3;
  undefined3 extraout_var;
  int iVar4;
  int local_2c;
  char *local_28;
  byte *local_24;
  undefined1 *local_20;
  int *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  int local_4;
  
  local_14 = 0;
  local_24 = (byte *)0x0;
  local_20 = &LAB_0044f5a0;
  local_1c = (int *)0x0;
  local_10 = 1;
  local_c = 1;
  local_8 = 1;
  local_4 = 1;
  local_18 = 0;
  this = (void *)FUN_00430de0(0x2c8);
  if (this == (void *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    puVar2 = FUN_00450760(this,&DAT_004ecc58,&DAT_004ecc58);
  }
  *param_4 = (int)puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_cm_LoadModelData_004dce0c);
    }
    return 0x43;
  }
  local_24 = (byte *)FUN_004049b0(*(int *)(param_1 + 0x1644),param_3);
  if (local_24 == (byte *)0x0) {
    if ((undefined4 *)*param_4 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*param_4)(1);
    }
    FUN_004267b0(param_1,0x2f,(char)param_2);
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_cm_LoadModelData_004dce0c);
    }
    return 0x2f;
  }
  iVar3 = FUN_004590d0((void *)*param_4,local_24,&DAT_004ecc58);
  if (iVar3 == 0) {
    local_2c = param_1;
    local_1c = &local_2c;
    local_28 = param_2;
    local_20 = &LAB_0048d5d0;
    uVar1 = KeyPad_4581d0((void *)*param_4,(int *)&local_24);
    iVar3 = CONCAT31(extraout_var,uVar1);
  }
  (**(code **)(*(int *)local_24 + 4))();
  if ((iVar3 != 0) || (iVar4 = FUN_00451b00((void *)*param_4,param_2), iVar4 == 0)) {
    if ((undefined4 *)*param_4 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*param_4)(1);
    }
    if (0 < DAT_004e4420) {
      FUN_00436670((byte *)s_Error__d_loading_model__s_004dbc0c,iVar3);
    }
    return iVar3;
  }
  if (local_c == 0) {
    if ((undefined4 *)*param_4 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*param_4)(1);
    }
    if (0 < DAT_004e4420) {
      FUN_00436670((byte *)s_Child_model_trees_invalid_in_mod_004dbc5c,param_2);
    }
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_cm_LoadModelData_004dce0c);
      return 0x18;
    }
  }
  else {
    if (local_4 != 0) {
      puVar2 = FUN_00445fe0(&PTR_LAB_004d6570,param_3);
      FUN_00446060((int *)(*param_4 + 0x14),(int)puVar2);
      return 0;
    }
    if ((undefined4 *)*param_4 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*param_4)(1);
    }
    if (0 < DAT_004e4420) {
      FUN_00436670((byte *)s_Missing_one_or_more_child_models_004dbc28,param_2);
    }
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_cm_LoadModelData_004dce0c);
    }
  }
  return 0x18;
}


/* 00498ca0 size=113 */

/* repo: runtime/client/src/clientmgr.cpp, runtime/server/src/server_iltsoundmgr.cpp,
   runtime/sound/src/soundmgr.cpp */

undefined4 __fastcall clientmgr_498ca0(int *param_1)

{
  int iVar1;
  
  if (param_1[0x4f] == 0) {
    if (param_1[0x4d] != 0) {
      if (param_1[0x4c] == 0) {
        return 1;
      }
      _AIL_lock_0();
      iVar1 = _AIL_digital_handle_reacquire_4(param_1[0x4c]);
      if (iVar1 == 0) {
        _AIL_unlock_0();
        param_1[0x4e] = 1;
        return 1;
      }
      _AIL_unlock_0();
      param_1[0x4d] = 0;
      return 0;
    }
  }
  else {
    (**(code **)(*param_1 + 0x6c))();
  }
  return 0;
}


