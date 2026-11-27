/* lithtech.exe decompilation - module ltdirectmusic_impl */
#include "ghidra_types.h"

/* 00448ab0 size=19 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp, tools/ltdmtest/ltdirectmusic_impl.cpp */

void __cdecl ltdirectmusic_impl_448ab0(undefined4 param_1)

{
  FUN_004488d0((byte *)s_ERROR__LTDirectMusic_not_Initial_004d9dc4,param_1);
  return;
}


/* 00449460 size=163 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp, tools/ltdmtest/ltdirectmusic_impl.cpp */

int __fastcall ltdirectmusic_impl_449460(undefined4 *param_1)

{
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  param_1[0x21] = 0;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  param_1[0x24] = 0;
  *param_1 = &PTR_LAB_004cc67c;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[0x35] = 0;
  param_1[0x33] = 0;
  param_1[0x36] = 0;
  param_1[0x37] = 0;
  param_1[0x30] = 0x40;
  param_1[0x31] = 0x40;
  param_1[0x32] = 0xac44;
  param_1[0x1e] = 0;
  DAT_004ea628 = param_1;
  return;
}


/* 0044b010 size=382 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp, tools/ltdmtest/ltdirectmusic_impl.cpp */

undefined4 __thiscall ltdirectmusic_impl_44b010(void *this,byte *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int *this_00;
  int *unaff_EDI;
  undefined1 local_354 [4];
  undefined4 local_350;
  undefined4 local_34c;
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined4 local_32c;
  WCHAR local_218 [268];
  
  puVar1 = FUN_0044bc60((void *)((int)this + 0x40),param_1);
  if (puVar1 != (undefined4 *)0x0) {
    return 1;
  }
  if (DAT_004ea5a8 == (int *)0x0) {
    iVar2 = FUN_0044c710(0x4ea598);
    if (iVar2 == 0) {
      return 0;
    }
    this_00 = DAT_004ea5a8;
    if (DAT_004ea5a8 != (int *)0x0) {
      DAT_004ea5a8 = (int *)*DAT_004ea5a8;
    }
  }
  else {
    this_00 = DAT_004ea5a8;
    DAT_004ea5a8 = (int *)*DAT_004ea5a8;
  }
  if (this_00 != (int *)0x0) {
    this_00[2] = 0;
    *(undefined1 *)(this_00 + 3) = 0;
    this_00[0x13] = 0;
    this_00[0x14] = 4;
    local_338 = DAT_004ced3c;
    local_330 = DAT_004ced44;
    local_334 = DAT_004ced40;
    local_32c = DAT_004ced48;
    local_350 = 0x350;
    MultiByteToWideChar(0,1,(LPCSTR)param_1,-1,local_218,0x104);
    local_34c = 0x12;
    iVar2 = (**(code **)(**(int **)((int)this + 0x10) + 0xc))
                      (*(int **)((int)this + 0x10),&local_350,&DAT_004cec9c,local_354);
    if (-1 < iVar2) {
      iVar2 = 0;
      (**(code **)(*unaff_EDI + 0x4c))(unaff_EDI,&DAT_004cecec,0xffffffff,0,0,0);
      this_00[2] = iVar2;
      FUN_0044bb90(this_00,(char *)param_1);
      FUN_004b4f00((void *)((int)this + 0x40),this_00);
      FUN_00448a10(3,(byte *)s_LTDirectMusic_loaded_segment__s_004da6a4,param_1);
      return 1;
    }
    FUN_00448970((byte *)s_WARNING__LTDirectMusic_failed_to_004da670,param_1);
    if ((undefined *)this_00[0x13] != (undefined *)0x0) {
      FUN_00430df0((undefined *)this_00[0x13]);
    }
    *this_00 = (int)DAT_004ea5a8;
    DAT_004ea5a8 = this_00;
  }
  return 0;
}


/* 0044b280 size=465 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp, tools/ltdmtest/ltdirectmusic_impl.cpp */

undefined4 __thiscall ltdirectmusic_impl_44b280(void *this,byte *param_1)

{
  int iVar1;
  int *this_00;
  undefined4 *puVar2;
  int *piVar3;
  uint uVar4;
  void *this_01;
  void *unaff_ESI;
  int *unaff_EDI;
  undefined1 local_560 [4];
  void *local_55c;
  undefined4 local_558;
  undefined4 local_554;
  undefined4 local_540;
  undefined4 local_53c;
  undefined4 local_538;
  undefined4 local_534;
  short local_420 [268];
  WCHAR local_208 [256];
  void *pvStack_8;
  
  local_55c = this;
  MultiByteToWideChar(0,1,(LPCSTR)param_1,-1,local_208,0x104);
  iVar1 = FUN_004bc284((ushort *)local_208,(ushort *)&DAT_004ea62c);
  if (iVar1 == 0) {
    return 1;
  }
  if (DAT_004ea5c0 == (int *)0x0) {
    iVar1 = FUN_0044c910(0x4ea5b0);
    if (iVar1 == 0) {
      return 0;
    }
    this_00 = (int *)FUN_0044c660(0x4ea5b0);
  }
  else {
    this_00 = DAT_004ea5c0;
    DAT_004ea5c0 = (int *)*DAT_004ea5c0;
  }
  if (this_00 != (int *)0x0) {
    this_00[2] = 0;
    *(undefined1 *)(this_00 + 3) = 0;
    this_00[0x13] = 0;
    local_53c = DAT_004ced30;
    local_538 = DAT_004ced34;
    local_540 = DAT_004ced2c;
    local_534 = DAT_004ced38;
    FUN_004bc2e3(local_420,local_208);
    local_554 = 0x12;
    local_558 = 0x350;
    iVar1 = (**(code **)(**(int **)((int)this + 0x10) + 0xc))
                      (*(int **)((int)this + 0x10),&local_558,&DAT_004cec8c,local_560);
    if (-1 < iVar1) {
      FUN_00448a10(3,(byte *)s_LTDirectMusic_loaded_style__s_004da6d0,param_1);
      puVar2 = FUN_004b8dd0(pvStack_8,(byte *)0x0,&DAT_004da6c8);
      if (puVar2 != (undefined4 *)0x0) {
        do {
          piVar3 = (int *)FUN_004b8a20((int)puVar2);
          if (((piVar3 != (int *)0x0) &&
              (uVar4 = FUN_004c4c00(this_01,(byte *)piVar3[2],param_1), uVar4 == 0)) &&
             (*piVar3 != 0)) {
            ltdirectmusic_impl_44b460(unaff_ESI,unaff_EDI,*(LPCSTR *)(*piVar3 + 8));
          }
          puVar2 = FUN_004b8a30(puVar2);
        } while (puVar2 != (undefined4 *)0x0);
        this = unaff_ESI;
      }
      this_00[2] = (int)unaff_EDI;
      FUN_0044bb90(this_00,(char *)param_1);
      FUN_004b4f00((void *)((int)this + 0x58),this_00);
      return 1;
    }
    FUN_00448970((byte *)s_WARNING__LTDirectMusic_failed_to_004da6f0,param_1);
    if ((undefined *)this_00[0x13] != (undefined *)0x0) {
      FUN_00430df0((undefined *)this_00[0x13]);
    }
    *this_00 = (int)DAT_004ea5c0;
    DAT_004ea5c0 = this_00;
  }
  return 0;
}


/* 0044b460 size=363 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp, tools/ltdmtest/ltdirectmusic_impl.cpp */

undefined4 __thiscall ltdirectmusic_impl_44b460(void *this,int *param_1,LPCSTR param_2)

{
  int iVar1;
  int *unaff_ESI;
  int *piVar2;
  WCHAR *pWVar3;
  int *piVar4;
  undefined4 local_210;
  WCHAR local_208 [260];
  
  if (param_1 == (int *)0x0) {
    return 0;
  }
  if (DAT_004ea608 == (int *)0x0) {
    iVar1 = FUN_0044c890(0x4ea5f8);
    if (iVar1 == 0) {
      return 0;
    }
    piVar2 = DAT_004ea608;
    if (DAT_004ea608 != (int *)0x0) {
      DAT_004ea608 = (int *)*DAT_004ea608;
    }
  }
  else {
    piVar2 = DAT_004ea608;
    DAT_004ea608 = (int *)*DAT_004ea608;
  }
  if (piVar2 == (int *)0x0) {
    return 0;
  }
  MultiByteToWideChar(0,1,param_2,-1,local_208,0x104);
  iVar1 = FUN_004bc284((ushort *)local_208,(ushort *)&DAT_004ea62c);
  if (iVar1 != 0) {
    piVar4 = &local_210;
    pWVar3 = local_208;
    (**(code **)(*param_1 + 0xc))(param_1);
    if (unaff_ESI == (int *)0x0) {
      *piVar2 = (int)DAT_004ea608;
      DAT_004ea608 = piVar2;
      return 0;
    }
    iVar1 = (**(code **)(*unaff_ESI + 0x10))(unaff_ESI,*(undefined4 *)((int)this + 0x14));
    if (iVar1 < 0) {
      FUN_00448970((byte *)s_WARNING__LTDirectMusic_failed_to_004da780,param_2);
    }
    piVar2[2] = (int)piVar4;
    FUN_004b4f00((void *)((int)this + 0x50),piVar2);
    iVar1 = (**(code **)(*piVar4 + 0xc))(piVar4,local_208 + -0xc);
    if (iVar1 < 0) {
      FUN_00448970((byte *)s_WARNING__LTDirectMusic_failed_to_004da73c,param_2);
    }
    else {
      (**(code **)(**(int **)((int)this + 0x14) + 0x10))
                (*(int **)((int)this + 0x14),pWVar3,0x80,0,0,0);
      piVar2[3] = (int)pWVar3;
    }
    FUN_00448a10(3,(byte *)s_LTDirectMusic_loaded_band__s_004da71c,param_2);
  }
  return 1;
}


/* 0044b5d0 size=71 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp, tools/ltdmtest/ltdirectmusic_impl.cpp */

undefined4 __thiscall ltdirectmusic_impl_44b5d0(void *this,void *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  for (puVar1 = FUN_004b8dd0(param_1,(byte *)0x0,(byte *)s_DLSBANK_004da7b0);
      puVar1 != (undefined4 *)0x0; puVar1 = FUN_004b8a30(puVar1)) {
    iVar2 = FUN_004b8a20((int)puVar1);
    if (iVar2 != 0) {
      FUN_0044b190(this,*(LPCSTR *)(iVar2 + 8));
    }
  }
  return 1;
}


/* 0044b670 size=400 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp, tools/ltdmtest/ltdirectmusic_impl.cpp,
   NOLF2/ObjectDLL/ObjectShared/PlayerObj.cpp */

undefined4 __thiscall ltdirectmusic_impl_44b670(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  param_1 = FUN_004b8dd0(param_1,(byte *)0x0,(byte *)s_INTENSITY_004da7c0);
  if (param_1 == (undefined4 *)0x0) {
    return 1;
  }
  do {
    puVar1 = (undefined4 *)FUN_004b8a20((int)param_1);
    if (puVar1 != (undefined4 *)0x0) {
      local_c = 0;
      FUN_004b89e0(puVar1,&local_c);
      if (((0 < local_c) && (local_c <= *(int *)((int)this + 0xb0))) &&
         (puVar1 = (undefined4 *)*puVar1, puVar1 != (undefined4 *)0x0)) {
        local_8 = 0xffffffff;
        FUN_004b89e0(puVar1,&local_8);
        piVar4 = (int *)*puVar1;
        if (piVar4 != (int *)0x0) {
          local_4 = 0;
          FUN_004b89e0(piVar4,&local_4);
          piVar4 = (int *)*piVar4;
          if (piVar4 != (int *)0x0) {
            do {
              ltdirectmusic_impl_44b010(this,(byte *)piVar4[2]);
              puVar1 = FUN_0044bc60((void *)((int)this + 0x40),(byte *)piVar4[2]);
              if ((puVar1 == (undefined4 *)0x0) || (puVar1[2] == 0)) break;
              if (DAT_004ea5a8 == (undefined4 *)0x0) {
                iVar2 = FUN_0044c710(0x4ea598);
                if (iVar2 == 0) break;
                puVar3 = (undefined4 *)FUN_0044c660(0x4ea598);
              }
              else {
                puVar3 = DAT_004ea5a8;
                DAT_004ea5a8 = (undefined4 *)*DAT_004ea5a8;
              }
              if (puVar3 == (undefined4 *)0x0) break;
              puVar3[2] = 0;
              *(undefined1 *)(puVar3 + 3) = 0;
              puVar3[0x13] = 0;
              puVar3[0x14] = 4;
              puVar3[2] = puVar1[2];
              FUN_004b4f30((void *)(*(int *)((int)this + 0xcc) + 8 + local_c * 0x10),puVar3);
              piVar4 = (int *)*piVar4;
            } while (piVar4 != (int *)0x0);
            *(undefined4 *)(local_c * 0x10 + *(int *)((int)this + 0xcc)) = local_8;
            *(undefined4 *)(local_c * 0x10 + 4 + *(int *)((int)this + 0xcc)) = local_4;
          }
        }
      }
    }
    param_1 = FUN_004b8a30(param_1);
    if (param_1 == (undefined4 *)0x0) {
      return 1;
    }
  } while( true );
}


/* 0044b800 size=125 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp, tools/ltdmtest/ltdirectmusic_impl.cpp,
   tools/ltdmtest/LTDMTestDlg.cpp */

undefined4 __thiscall ltdirectmusic_impl_44b800(void *this,void *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  puVar1 = FUN_004b8dd0(param_1,(byte *)0x0,(byte *)s_SECONDARYSEGMENT_004da7cc);
  if (puVar1 == (undefined4 *)0x0) {
    return 1;
  }
  do {
    piVar2 = (int *)FUN_004b8a20((int)puVar1);
    if (piVar2 != (int *)0x0) {
      ltdirectmusic_impl_44b010(this,(byte *)piVar2[2]);
      puVar3 = FUN_0044bc60((void *)((int)this + 0x40),(byte *)piVar2[2]);
      if ((puVar3 != (undefined4 *)0x0) && (*piVar2 != 0)) {
        uVar4 = (**(code **)(*(int *)this + 0x3c))(*(undefined4 *)(*piVar2 + 8));
        puVar3[0x14] = uVar4;
      }
    }
    puVar1 = FUN_004b8a30(puVar1);
  } while (puVar1 != (undefined4 *)0x0);
  return 1;
}


/* 0044b9e0 size=423 */

/* repo: tools/ltdmtest/ltdirectmusic_impl.cpp, runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp,
   FEAR/ObjectDLL/TransitionArea.cpp */

undefined4 __thiscall ltdirectmusic_impl_44b9e0(void *this,void *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  void *this_00;
  void *this_01;
  undefined4 uVar7;
  int local_8;
  int iStack_4;
  
  puVar2 = FUN_004b8dd0(param_1,(byte *)0x0,(byte *)s_TRANSITION_004da7fc);
  if (puVar2 == (undefined4 *)0x0) {
    return 1;
  }
  do {
    uVar7 = 0;
    puVar3 = (undefined4 *)FUN_004b8a20((int)puVar2);
    if (puVar3 == (undefined4 *)0x0) {
LAB_0044bb59:
      puVar2 = FUN_004b8a30(puVar2);
    }
    else {
      local_8 = 0;
      FUN_004b89e0(puVar3,&local_8);
      if (((local_8 < 1) || (*(int *)((int)this + 0xb0) < local_8)) ||
         (piVar6 = (int *)*puVar3, piVar6 == (int *)0x0)) goto LAB_0044bb59;
      param_1 = (void *)0x0;
      FUN_004b89e0(piVar6,&param_1);
      if ((((int)param_1 < 1) || (*(int *)((int)this + 0xb0) < (int)param_1)) ||
         ((piVar6 = (int *)*piVar6, piVar6 == (int *)0x0 ||
          ((iStack_4 = (**(code **)(*(int *)this + 0x3c))(piVar6[2]), iStack_4 == 0 ||
           (piVar6 = (int *)*piVar6, piVar6 == (int *)0x0)))))) goto LAB_0044bb59;
      uVar4 = FUN_004c4c00(this_00,(byte *)piVar6[2],(byte *)s_MANUAL_004da7f4);
      if (uVar4 == 0) {
        uVar7 = 1;
      }
      else {
        uVar4 = FUN_004c4c00(this_01,(byte *)piVar6[2],(byte *)s_AUTOMATIC_004da7e8);
        if (uVar4 != 0) goto LAB_0044bb59;
      }
      iVar5 = *piVar6;
      if (iVar5 != 0) {
        ltdirectmusic_impl_44b010(this,*(byte **)(iVar5 + 8));
        puVar3 = FUN_0044bc60((void *)((int)this + 0x40),*(byte **)(iVar5 + 8));
        if (puVar3 == (undefined4 *)0x0) {
          iVar5 = FUN_0044bdd0(this,local_8,(int)param_1);
          *(undefined4 *)(iVar5 + 8) = 0;
        }
        else {
          uVar1 = puVar3[2];
          iVar5 = FUN_0044bdd0(this,local_8,(int)param_1);
          *(undefined4 *)(iVar5 + 8) = uVar1;
        }
      }
      piVar6 = (int *)FUN_0044bdd0(this,local_8,(int)param_1);
      *piVar6 = iStack_4;
      iVar5 = FUN_0044bdd0(this,local_8,(int)param_1);
      *(undefined4 *)(iVar5 + 4) = uVar7;
      puVar2 = FUN_004b8a30(puVar2);
    }
    if (puVar2 == (undefined4 *)0x0) {
      return 1;
    }
  } while( true );
}


/* 0044c2c0 size=259 */

/* repo: runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp, tools/ltdmtest/ltdirectmusic_impl.cpp */

undefined4 __thiscall ltdirectmusic_impl_44c2c0(void *this,void *param_1)

{
  uint uVar1;
  char local_8 [8];
  
  *(undefined4 *)((int)this + 0xfc) = 0;
  *(float *)((int)this + 0x100) = 0.0;
  *(float *)((int)this + 0x10c) = -10.0;
  *(undefined4 *)((int)this + 0x104) = 0x447a0000;
  *(undefined4 *)((int)this + 0x108) = 0x3a83126f;
  FUN_004b8e80(param_1,(byte *)0x0,(byte *)s_REVERB_004da84c,local_8,4);
  uVar1 = FUN_004c4c00(local_8,(byte *)local_8,&DAT_004da848);
  if (uVar1 == 0) {
    *(undefined4 *)((int)this + 0xfc) = 1;
  }
  FUN_004b8e40(param_1,(byte *)0x0,(byte *)s_REVERBINGAIN_004da838,(float *)((int)this + 0x100));
  FUN_004b8e40(param_1,(byte *)0x0,(byte *)s_REVERBHIGHFREQRTRATIO_004da820,
               (float *)((int)this + 0x10c));
  FUN_004b8e40(param_1,(byte *)0x0,(byte *)s_REVERBMIX_004da814,(float *)((int)this + 0x104));
  FUN_004b8e40(param_1,(byte *)0x0,(byte *)s_REVERBTIME_004da808,(float *)((int)this + 0x108));
  FUN_0044c050((int)this);
  if (*(int *)((int)this + 0xfc) != 0) {
    FUN_0044c0f0((int)this);
  }
  return 1;
}


/* 0044c3d0 size=21 */

/* repo: tools/ltdmtest/ltdirectmusic_impl.cpp, runtime/kernel/src/sys/win/ltdirectmusic_impl.cpp,
   NOLF/ClientShellDLL/Music.cpp */

undefined4 __fastcall ltdirectmusic_impl_44c3d0(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0xfc) == 0) {
    return 1;
  }
  uVar1 = FUN_0044c1a0(param_1);
  return uVar1;
}


