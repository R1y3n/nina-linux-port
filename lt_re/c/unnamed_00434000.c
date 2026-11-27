/* lithtech.exe decompilation - unnamed_00434000 */
#include "ghidra_types.h"

/* 00434040 size=365 */

undefined4 __thiscall FUN_00434040(void *this,LPCSTR param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int unaff_EDI;
  int iVar3;
  undefined4 unaff_retaddr;
  undefined1 local_8 [2];
  undefined1 auStack_6 [6];
  
  FUN_004341b0(this);
  piVar1 = FUN_0049b2d0(param_1);
  *(int **)((int)this + 0x10) = piVar1;
  if (piVar1 == (int *)0x0) {
    return 1;
  }
  (**(code **)(*piVar1 + 8))(local_8,4);
  if (unaff_EDI != -0xf0f5544) {
    FUN_00436670((byte *)s_Invalid_version___d__wanted__d__004d7d40,unaff_EDI);
    return 0x45;
  }
  iVar3 = 0x10;
  do {
    (**(code **)(**(int **)((int)this + 0x10) + 8))(local_8 + -4,4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = (**(code **)(**(int **)((int)this + 0x10) + 0xc))(unaff_retaddr,param_1);
  if (iVar3 != 0) {
    (**(code **)(**(int **)((int)this + 0x10) + 4))();
    return 1;
  }
  (**(code **)(**(int **)((int)this + 0x10) + 8))(*(int *)((int)this + 0xc) + 0x136c,4);
  (**(code **)(**(int **)((int)this + 0x10) + 8))(*(int *)((int)this + 0xc) + 0x1364,4);
  *(undefined4 *)(*(int *)((int)this + 0xc) + 0x1368) = 0;
  *(undefined4 *)(*(int *)((int)this + 0xc) + 0x15bc) = 0;
  puVar2 = (undefined4 *)(*(int *)((int)this + 0xc) + 0x13bc);
  for (iVar3 = 0x3f; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)puVar2 = 0;
  *(undefined1 *)((int)puVar2 + 2) = 0;
  *(undefined4 *)((int)this + 0x18) = 2;
  *(undefined4 *)((int)this + 8) = 0xbf800000;
  *(undefined4 *)this = 0;
  *(undefined4 *)(*(int *)((int)this + 0xc) + 0x1604) = 0;
  puVar2 = FUN_0049b000(0x100);
  *(undefined4 **)((int)this + 0x14) = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    FUN_004341b0(this);
    return 1;
  }
  FUN_00433f30(this,puVar2,0);
  FUN_00433f30(this,*(undefined4 *)((int)this + 0x10),1);
  FUN_00433f00((int)this);
  return 0;
}


/* 004341b0 size=105 */

/* FUN_004341b0: lifted from original x86 -> lt_lifted.c */


/* 00434220 size=729 */

int __thiscall
FUN_00434220(void *this,int param_1,uint *param_2,int param_3,int *param_4,int param_5)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  byte unaff_BL;
  byte unaff_BP;
  uint *puVar7;
  undefined4 *puVar8;
  int *unaff_retaddr;
  undefined1 *puVar9;
  undefined1 auStack_8 [2];
  undefined1 auStack_6 [2];
  uint *puStack_4;
  
  puVar4 = param_2;
  *param_2 = 0;
  *param_4 = 0;
  if ((*(int *)((int)this + 0x18) == 2) && (iVar5 = FUN_004345e0(this,1), iVar5 != 2)) {
    if (iVar5 == 0) {
      iVar5 = 0x160c;
      do {
        (**(code **)(**(int **)((int)this + 0x10) + 8))(iVar5 + *(int *)((int)this + 0xc),4);
        iVar5 = iVar5 + 4;
      } while (iVar5 < 0x1618);
      puVar9 = auStack_8;
      (**(code **)(**(int **)((int)this + 0x10) + 8))(puVar9,1);
      if (unaff_BP == 0xff) {
        FUN_00436670((byte *)s_DemoMgr__Invalid_number_of_chang_004d7d78,puVar9);
        return 1;
      }
      iVar5 = 0;
      if (unaff_BP != 0) {
        puVar7 = puStack_4;
        do {
          (**(code **)(**(int **)((int)this + 0x10) + 8))(auStack_8 + -4,1);
          if (unaff_BL == 0xff) {
            FUN_00436670((byte *)s_DemoMgr__Invalid_change_004d7d60,puVar9);
            return 1;
          }
          iVar5 = iVar5 + 1;
          *puVar7 = (uint)unaff_BL;
          puVar7 = puVar7 + 1;
        } while (iVar5 < (int)(uint)unaff_BP);
      }
      iVar5 = 0;
      *puVar4 = (uint)unaff_BP;
      if (unaff_BP != 0) {
        do {
          pcVar1 = (char *)(*(int *)((int)this + 0xc) + 0x13bc + *puStack_4);
          *pcVar1 = *pcVar1 == '\0';
          iVar5 = iVar5 + 1;
          puStack_4 = puStack_4 + 1;
        } while (iVar5 < (int)*puVar4);
      }
      iVar5 = 0;
      do {
        if (*(char *)(*(int *)((int)this + 0xc) + 0x13bc + iVar5) != '\0') {
          *(int *)(param_1 + *param_2 * 4) = iVar5;
          *param_2 = *param_2 + 1;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 0xff);
      return 0;
    }
  }
  else {
    iVar5 = *(int *)((int)this + 0xc);
    iVar3 = *(int *)(iVar5 + 0x15bc);
    puVar2 = (undefined4 *)((uint)(iVar3 == 0) * 0xff + 0x13bc + iVar5);
    puVar8 = puVar2;
    for (iVar6 = 0x3f; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = 0;
      puVar8 = puVar8 + 1;
    }
    *(undefined2 *)puVar8 = 0;
    *(undefined1 *)((int)puVar8 + 2) = 0;
    iVar6 = *(int *)((int)this + 0xc);
    if (*(int *)(iVar6 + 0x1630) == 0) {
      (**(code **)(*(int *)(iVar6 + 0x1618) + 0x14))(*(int *)(iVar6 + 0x1618),puVar2,iVar6 + 0x160c)
      ;
    }
    if ((*(int *)(*(int *)((int)this + 0xc) + 0x162c) == 0) || (param_5 != 0)) {
      puVar8 = puVar2;
      for (iVar6 = 0x3f; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar8 = 0;
        puVar8 = puVar8 + 1;
      }
      *(undefined2 *)puVar8 = 0;
      *(undefined1 *)((int)puVar8 + 2) = 0;
      iVar6 = *(int *)((int)this + 0xc);
      *(undefined4 *)(iVar6 + 0x160c) = 0;
      *(undefined4 *)(iVar6 + 0x1610) = 0;
      *(undefined4 *)(iVar6 + 0x1614) = 0;
    }
    iVar6 = 0;
    param_5 = (iVar3 * 0xff + 0x13bc + iVar5) - (int)puVar2;
    do {
      if (*(char *)(iVar6 + (int)puVar2) != '\0') {
        *(int *)(param_3 + *param_4 * 4) = iVar6;
        *param_4 = *param_4 + 1;
      }
      if (*(char *)(iVar6 + (int)puVar2) != ((char *)(iVar6 + (int)puVar2))[param_5]) {
        *(int *)(param_1 + *param_2 * 4) = iVar6;
        *param_2 = *param_2 + 1;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 0xff);
    *(uint *)(*(int *)((int)this + 0xc) + 0x15bc) =
         (uint)(*(int *)(*(int *)((int)this + 0xc) + 0x15bc) == 0);
    if (*(int *)((int)this + 0x18) == 1) {
      param_4 = (int *)CONCAT31((*(uint32_t*)((char*)&param_4+1)),1);
      (**(code **)(**(int **)((int)this + 0x10) + 0x24))(&param_4,1);
      iVar5 = 0x160c;
      do {
        (**(code **)(**(int **)((int)this + 0x10) + 0x24))(iVar5 + *(int *)((int)this + 0xc),4);
        iVar5 = iVar5 + 4;
      } while (iVar5 < 0x1618);
      param_2 = (uint *)CONCAT31((*(uint32_t*)((char*)&param_2+1)),(char)*unaff_retaddr);
      (**(code **)(**(int **)((int)this + 0x10) + 0x24))(&param_2,1);
      iVar5 = 0;
      if (0 < *unaff_retaddr) {
        do {
          (**(code **)(**(int **)((int)this + 0x10) + 0x24))(auStack_8 + -4,1);
          iVar5 = iVar5 + 1;
        } while (iVar5 < *unaff_retaddr);
      }
    }
    iVar5 = 0;
  }
  return iVar5;
}


/* 00434500 size=212 */

int __fastcall FUN_00434500(void *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  float10 fVar4;
  undefined4 uStack_4;
  
  uStack_4 = param_1;
  if (*(int *)((int)param_1 + 0x18) == 2) {
    if ((*(int *)((int)param_1 + 8) == -0x40800000) &&
       (*(int *)(*(int *)((int)param_1 + 0xc) + 0x1cc) != 0)) {
      fVar4 = FUN_004a0540();
      *(float *)((int)param_1 + 8) = (float)fVar4;
      puVar2 = &DAT_004e96b8;
      do {
        puVar1 = (undefined4 *)*puVar2;
        puVar2 = puVar2 + 4;
        *puVar1 = 0;
      } while (puVar2 < &DAT_004e97c8);
    }
    iVar3 = FUN_004345e0(param_1,0);
    if (iVar3 != 0) {
      return iVar3;
    }
    (**(code **)(**(int **)((int)param_1 + 0x10) + 8))(*(int *)((int)param_1 + 0xc) + 0x136c,4);
  }
  else {
    fVar4 = FUN_004a0540();
    *(float *)(*(int *)((int)param_1 + 0xc) + 0x136c) =
         (float)(fVar4 + (float10)*(float *)((int)param_1 + 4));
    if (*(int *)((int)param_1 + 0x18) == 1) {
      uStack_4 = (void *)((uint)uStack_4 & 0xffffff);
      (**(code **)(**(int **)((int)param_1 + 0x10) + 0x24))((int)&uStack_4 + 3,1);
      (**(code **)(**(int **)((int)param_1 + 0x10) + 0x24))(*(int *)((int)param_1 + 0xc) + 0x136c,4)
      ;
    }
  }
  iVar3 = *(int *)((int)param_1 + 0xc);
  *(float *)(iVar3 + 0x1368) = *(float *)(iVar3 + 0x136c) - *(float *)(iVar3 + 0x1364);
  *(undefined4 *)(*(int *)((int)param_1 + 0xc) + 0x1364) =
       *(undefined4 *)(*(int *)((int)param_1 + 0xc) + 0x136c);
  FUN_00426980(*(int *)((int)param_1 + 0xc));
  return 0;
}


/* 004345e0 size=899 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004345e0(void *this,uint param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  float fVar4;
  uint uVar5;
  uint *puVar6;
  undefined4 *puVar7;
  float10 fVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  ulonglong uStack_48;
  byte bStack_3c;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  double dStack_18;
  
  if ((*(int **)((int)this + 0x10) != (int *)0x0) && (*(int *)((int)this + 0x18) == 2)) {
    puVar7 = &local_34;
    (**(code **)(**(int **)((int)this + 0x10) + 8))(puVar7,1);
    if (bStack_3c == 2) {
      fVar8 = FUN_004a0540();
      uStack_48 = (ulonglong)*(uint *)this;
      fVar1 = (float)(fVar8 - (float10)*(float *)((int)this + 8));
      fVar4 = (float)uStack_48 / fVar1;
      FUN_00434970((byte *)s_Demo_played_in___3f_seconds_004d7ee0,SUB84((double)fVar1,0));
      FUN_00434970((byte *)s__d_frames_drawn__average___3f_fp_004d7ebc,*(undefined4 *)this);
      if (fVar1 <= _DAT_004d7c4c) {
        _DAT_004d7c4c = fVar1;
      }
      if (_DAT_004e97c8 <= fVar1) {
        _DAT_004e97c8 = fVar1;
      }
      if (fVar4 <= _DAT_004d7c50) {
        _DAT_004d7c50 = fVar4;
      }
      if (_DAT_004e97cc <= fVar4) {
        _DAT_004e97cc = fVar4;
      }
      puVar6 = &DAT_004e96c0;
      do {
        if (DAT_004e9868 != 0) {
          uStack_48 = (ulonglong)*(uint *)puVar6[-2];
          dStack_18 = (double)uStack_48;
          FUN_004242e0();
          FUN_00434970((byte *)s__s____3f_004d7eb0,puVar6[-1]);
        }
        uVar2 = *(uint *)puVar6[-2];
        uVar5 = *puVar6;
        if (uVar2 <= *puVar6) {
          uVar5 = uVar2;
        }
        *puVar6 = uVar5;
        uVar2 = *(uint *)puVar6[-2];
        uVar5 = puVar6[1];
        if (puVar6[1] <= uVar2) {
          uVar5 = uVar2;
        }
        puVar6[1] = uVar5;
        puVar6 = puVar6 + 4;
      } while (puVar6 < &DAT_004e97d0);
      if (1 < DAT_004e9864) {
        if (DAT_004e4d50 == DAT_004e9864) {
          FUN_00434970((byte *)s_PlayDemoReps_info_______________004d7e90,puVar7);
          FUN_00434970((byte *)s_Min_time____3f__Max_time____3f__d_004d7e54,
                       SUB84((double)_DAT_004d7c4c,0));
          FUN_00434970((byte *)s_Min_FPS____3f__Max_FPS____3f__di_004d7e28,
                       SUB84((double)_DAT_004d7c50,0));
          if (DAT_004e9868 != 0) {
            FUN_00434970((byte *)s_value___min_time___max_time__var_004d7e00,puVar7);
            puVar7 = &DAT_004e96c0;
            do {
              FUN_004242e0();
              local_34 = 0;
              uStack_30 = puVar7[1];
              uStack_2c = 0;
              uVar9 = FUN_004242e0();
              uStack_28 = (undefined4)uVar9;
              uStack_24 = 0;
              uStack_20 = *puVar7;
              uStack_1c = 0;
              uVar10 = FUN_004242e0();
              dStack_18 = (double)(uVar10 & 0xffffffff);
              FUN_00434970((byte *)s__s_____3f_____3f___variance____3_004d7dcc,puVar7[-1]);
              puVar7 = puVar7 + 4;
            } while (puVar7 < &DAT_004e97d0);
          }
        }
        else {
          FUN_00436620((char *)0x0);
        }
      }
      FUN_00436600(1);
      FUN_004341b0(this);
      iVar3 = *(int *)((int)this + 0xc);
      fVar8 = FUN_004a0540();
      *(float *)((int)this + 4) = (float)((float10)*(float *)(iVar3 + 0x136c) - fVar8);
      return 2;
    }
    if (bStack_3c != param_1) {
      FUN_00436670((byte *)s_DemoMgr__Sync_byte_wrong__wanted_004d7d9c,param_1);
      FUN_004341b0(this);
      return 2;
    }
  }
  return 0;
}


/* 00434970 size=77 */

void __cdecl FUN_00434970(byte *param_1,undefined4 param_2)

{
  undefined1 local_400 [1024];
  
  FUN_004baabf(local_400,0x3ff,param_1,&param_2);
  FUN_00436670(&DAT_004d5678,local_400);
  FUN_004317e0();
  return;
}


/* 00434a00 size=30 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00434a00(void)

{
  _DAT_004e97d0 = &PTR_FUN_004cc350;
  FUN_004b7be0((uint *)&DAT_004e97d4,0x18,0x20,0x40);
  return;
}


/* 00434a20 size=12 */

void FUN_00434a20(void)

{
  FUN_004b9cf5(&LAB_00434a30);
  return;
}


/* 00434a60 size=203 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __cdecl FUN_00434a60(uint param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  
  if (((param_1 == 0) || (param_2 < 0)) || (3 < param_2)) {
    return (int *)0x0;
  }
  uVar3 = param_1 * 0x18 + 0xc;
  piVar1 = FUN_00430f00(uVar3);
  piVar5 = piVar1;
  for (uVar3 = uVar3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined1 *)piVar5 = 0;
    piVar5 = (int *)((int)piVar5 + 1);
  }
  uVar3 = 0;
  *piVar1 = param_2;
  piVar1[2] = param_1;
  piVar5 = piVar1;
  if (param_1 != 0) {
    do {
      piVar2 = piVar5 + 6;
      piVar5[3] = (int)piVar1;
      piVar5[4] = uVar3;
      piVar5[7] = (int)piVar2;
      *piVar2 = (int)piVar2;
      uVar3 = uVar3 + 1;
      piVar5 = piVar2;
    } while (uVar3 < param_1);
  }
  _DAT_004e97f4 = &LAB_00434b30;
  _DAT_004e97f8 = FUN_00434b40;
  _DAT_004e97fc = &LAB_00434b80;
  _DAT_004e9800 = FUN_00434bb0;
  _DAT_004e9804 = &LAB_00434bf0;
  _DAT_004e9808 = &LAB_00434c10;
  _DAT_004e980c = &LAB_00434c60;
  _DAT_004e9810 = &LAB_00434ca0;
  return piVar1;
}


/* 00434b40 size=50 */

int __cdecl FUN_00434b40(int param_1,uint param_2)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  
  iVar1 = 0;
  uVar3 = 0;
  if (param_2 != 0) {
    do {
      cVar2 = *(char *)(uVar3 + param_1);
      if (('`' < cVar2) && (cVar2 < '{')) {
        cVar2 = cVar2 + -0x20;
      }
      iVar1 = iVar1 + (int)cVar2 * uVar3;
      uVar3 = uVar3 + 1;
    } while (uVar3 < param_2);
  }
  return iVar1;
}


/* 00434bb0 size=57 */

int __cdecl FUN_00434bb0(int param_1,uint param_2)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  
  iVar1 = 0;
  uVar3 = 0;
  if (param_2 != 0) {
    do {
      cVar2 = *(char *)(uVar3 + param_1);
      if (('`' < cVar2) && (cVar2 < '{')) {
        cVar2 = cVar2 + -0x20;
      }
      if (cVar2 == '/') {
        cVar2 = '\\';
      }
      iVar1 = iVar1 + (int)cVar2 * uVar3;
      uVar3 = uVar3 + 1;
    } while (uVar3 < param_2);
  }
  return iVar1;
}


/* 00434d00 size=111 */

void __cdecl FUN_00434d00(int *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  
  if (param_1 != (int *)0x0) {
    uVar5 = 0;
    if (param_1[2] != 0) {
      piVar3 = param_1;
      do {
        piVar4 = (int *)piVar3[7];
        while (piVar4 != piVar3 + 6) {
          piVar1 = (int *)piVar4[1];
          puVar2 = (undefined4 *)piVar4[2];
          piVar4 = piVar1;
          if (*param_1 == 0) {
            if (puVar2 != (undefined4 *)0x0) {
              *puVar2 = DAT_004e97ec;
              DAT_004e97ec = puVar2;
            }
          }
          else {
            FUN_00430fe0((undefined *)puVar2);
          }
        }
        uVar5 = uVar5 + 1;
        piVar3 = piVar3 + 6;
      } while (uVar5 < (uint)param_1[2]);
    }
    FUN_00430fe0((undefined *)param_1);
  }
  return;
}


/* 00434d70 size=185 */

int * __cdecl FUN_00434d70(int *param_1,undefined4 *param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 *puVar5;
  
  if (param_1 == (int *)0x0) {
    return (int *)0x0;
  }
  uVar3 = FUN_00434e30(param_1,param_2,param_3);
  piVar1 = param_1 + uVar3 * 6 + 3;
  if (*param_1 == 0) {
    piVar4 = DAT_004e97ec;
    if (DAT_004e97ec == (int *)0x0) {
      FUN_004b7c60(0x4e97d4,DAT_004e97dc);
      piVar4 = DAT_004e97ec;
      if (DAT_004e97ec == (int *)0x0) goto LAB_00434ddd;
    }
    DAT_004e97ec = (int *)*piVar4;
  }
  else {
    piVar4 = FUN_00430f00(param_3 + 0x16);
  }
LAB_00434ddd:
  *(short *)(piVar4 + 5) = (short)param_3;
  puVar5 = (undefined4 *)((int)piVar4 + 0x16);
  for (uVar3 = param_3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar5 = *param_2;
    param_2 = param_2 + 1;
    puVar5 = puVar5 + 1;
  }
  for (uVar3 = param_3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)puVar5 = *(undefined1 *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  piVar4[4] = 0;
  piVar4[3] = (int)piVar1;
  piVar4[2] = (int)piVar4;
  *piVar4 = (int)(piVar1 + 3);
  puVar5 = (undefined4 *)piVar1[4];
  piVar4[1] = (int)puVar5;
  *puVar5 = piVar4;
  *(int **)(*piVar4 + 4) = piVar4;
  iVar2 = piVar1[2];
  piVar1[2] = iVar2 + 1U;
  if (1 < iVar2 + 1U) {
    param_1[1] = param_1[1] + 1;
  }
  return piVar4;
}


/* 00434e30 size=39 */

uint __cdecl FUN_00434e30(int *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  
  uVar1 = (**(code **)(&DAT_004e97f4 + *param_1 * 4))(param_2,param_3);
  return uVar1 % (param_1[2] - 1U);
}


/* 00434e60 size=85 */

void __cdecl FUN_00434e60(int *param_1,int *param_2)

{
  if ((param_1 != (int *)0x0) && (param_2 != (int *)0x0)) {
    *(int *)(param_2[3] + 8) = *(int *)(param_2[3] + 8) + -1;
    *(int *)(*param_2 + 4) = param_2[1];
    *(int *)param_2[1] = *param_2;
    param_2[1] = (int)param_2;
    *param_2 = (int)param_2;
    if (*param_1 == 0) {
      *param_2 = (int)DAT_004e97ec;
      DAT_004e97ec = param_2;
      return;
    }
    FUN_00430fe0((undefined *)param_2);
  }
  return;
}


/* 00434ec0 size=118 */

int __cdecl FUN_00434ec0(int *param_1,undefined4 param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if (param_1 != (int *)0x0) {
    uVar3 = FUN_00434e30(param_1,param_2,param_3);
    for (piVar1 = (int *)param_1[uVar3 * 6 + 7]; piVar1 != param_1 + uVar3 * 6 + 6;
        piVar1 = (int *)piVar1[1]) {
      iVar2 = piVar1[2];
      if ((*(ushort *)(iVar2 + 0x14) == param_3) &&
         (iVar4 = (**(code **)(&DAT_004e9804 + *param_1 * 4))(iVar2 + 0x16,param_2,param_3),
         iVar4 != 0)) {
        return iVar2;
      }
    }
  }
  return 0;
}


/* 00434f40 size=101 */

int __cdecl FUN_00434f40(int *param_1,int param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((param_1 != (int *)0x0) && (param_2 != 0)) {
    iVar1 = *(int *)(param_2 + 0xc);
    for (iVar2 = *(int *)(param_2 + 4); iVar2 != iVar1 + 0xc; iVar2 = *(int *)(iVar2 + 4)) {
      iVar3 = *(int *)(iVar2 + 8);
      if ((*(ushort *)(iVar3 + 0x14) == param_4) &&
         (iVar4 = (**(code **)(&DAT_004e9804 + *param_1 * 4))(iVar3 + 0x16,param_3,param_4),
         iVar4 != 0)) {
        return iVar3;
      }
    }
  }
  return 0;
}


/* 00434fb0 size=31 */

int __cdecl FUN_00434fb0(int param_1,uint *param_2)

{
  if (param_1 == 0) {
    return 0;
  }
  if (param_2 != (uint *)0x0) {
    *param_2 = (uint)*(ushort *)(param_1 + 0x14);
  }
  return param_1 + 0x16;
}


/* 00434fd0 size=13 */

undefined4 __cdecl FUN_00434fd0(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x10);
}


/* 00434fe0 size=16 */

void __cdecl FUN_00434fe0(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x10) = param_2;
  }
  return;
}


/* 00434ff0 size=26 */

int __cdecl FUN_00434ff0(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  FUN_00435010((int *)(param_1 + 0xc),param_1 + 0x18);
  return;
}


/* 00435010 size=48 */

int * __cdecl FUN_00435010(int *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_2 + 4);
  if (piVar2 == param_1 + 3) {
    while (param_1[1] != *(int *)(*param_1 + 8) + -1) {
      piVar2 = param_1 + 10;
      piVar1 = param_1 + 9;
      param_1 = param_1 + 6;
      if ((int *)*piVar2 != piVar1) {
        return (int *)*piVar2;
      }
    }
    piVar2 = (int *)0x0;
  }
  return piVar2;
}


/* 00435040 size=42 */

undefined4 __cdecl FUN_00435040(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  if ((param_1 == (int *)0x0) || (iVar1 = *param_1, iVar1 == 0)) {
    return 0;
  }
  piVar2 = FUN_00435010(*(int **)(iVar1 + 0xc),iVar1);
  *param_1 = (int)piVar2;
  return *(undefined4 *)(iVar1 + 8);
}


/* 00435090 size=52 */

undefined4 * __thiscall FUN_00435090(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004cc350;
  FUN_004b7c10((int)this + 4);
  *(undefined ***)this = &PTR_LAB_004cb514;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 00435160 size=189 */

undefined4 __thiscall FUN_00435160(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  
  EnterCriticalSection(*(LPCRITICAL_SECTION *)((int)this + 0xc));
  if (*(int *)((int)this + 0x10) != 0) {
    LeaveCriticalSection(*(LPCRITICAL_SECTION *)((int)this + 0xc));
    return 1;
  }
  if (*(int *)((int)this + 8) != 0) {
    FUN_00435220(this);
  }
  if (param_1 != (char *)0x0) {
    if (*(undefined **)((int)this + 0x18) != (undefined *)0x0) {
      FUN_00430df0(*(undefined **)((int)this + 0x18));
    }
    uVar4 = 0xffffffff;
    pcVar2 = param_1;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    pcVar2 = (char *)FUN_00430de0(~uVar4);
    *(char **)((int)this + 0x18) = pcVar2;
    if (pcVar2 == (char *)0x0) {
      LeaveCriticalSection(*(LPCRITICAL_SECTION *)((int)this + 0xc));
      return 1;
    }
    uVar4 = 0xffffffff;
    do {
      pcVar6 = param_1;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar6 = param_1 + 1;
      cVar1 = *param_1;
      param_1 = pcVar6;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar6 = pcVar6 + -uVar4;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar2 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar2 = pcVar2 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar2 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar2 = pcVar2 + 1;
    }
  }
  uVar3 = FUN_00435340(this);
  LeaveCriticalSection(*(LPCRITICAL_SECTION *)((int)this + 0xc));
  return uVar3;
}


/* 00435220 size=83 */

undefined4 __fastcall FUN_00435220(int *param_1)

{
  undefined4 uVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)param_1[3]);
  if (param_1[4] != 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
    return 1;
  }
  if (param_1[2] == 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
    return 0;
  }
  uVar1 = FUN_00435400(param_1);
  LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
  return uVar1;
}


/* 00435280 size=115 */

int __fastcall FUN_00435280(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)param_1[3]);
  param_1[4] = param_1[4] + 1;
  if (param_1[2] == 0) {
    iVar2 = FUN_00435340(param_1);
    if (iVar2 != 0) {
      param_1[4] = param_1[4] + -1;
      LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
      return 0;
    }
  }
  else {
    iVar2 = param_1[3];
    if (*(int **)(iVar2 + 0x18) != param_1) {
      *(int *)(iVar2 + 0x20) = *(int *)(iVar2 + 0x20) + -1;
      FUN_004b4f60((void *)(iVar2 + 0x18),param_1);
      iVar2 = param_1[3];
      piVar1 = (int *)(iVar2 + 0x20);
      *piVar1 = *piVar1 + 1;
      FUN_004b4f00((void *)(iVar2 + 0x18),param_1);
    }
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
  return param_1[2];
}


/* 00435300 size=56 */

void __fastcall FUN_00435300(int param_1)

{
  EnterCriticalSection(*(LPCRITICAL_SECTION *)(param_1 + 0xc));
  if (*(int *)(param_1 + 0x10) == 0) {
    LeaveCriticalSection(*(LPCRITICAL_SECTION *)(param_1 + 0xc));
    return;
  }
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
  FUN_00435660(*(LPCRITICAL_SECTION *)(param_1 + 0xc));
  LeaveCriticalSection(*(LPCRITICAL_SECTION *)(param_1 + 0xc));
  return;
}


/* 00435340 size=179 */

undefined4 __fastcall FUN_00435340(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)param_1[3]);
  if (param_1[6] == 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
    return 1;
  }
  if (param_1[2] != 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
    return 0;
  }
  param_1[5] = 0;
  piVar2 = FUN_004049e0(*(int *)(DAT_004e516c + 0x1644),param_1 + 5);
  param_1[2] = (int)piVar2;
  if (piVar2 == (int *)0x0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
    return 1;
  }
  if (param_1[8] != 0) {
    (**(code **)(*piVar2 + 0x14))(param_1[8]);
  }
  iVar1 = param_1[3];
  piVar2 = (int *)(iVar1 + 0x2c);
  *piVar2 = *piVar2 + -1;
  FUN_004b4f60((void *)(iVar1 + 0x24),param_1);
  iVar1 = param_1[3];
  piVar2 = (int *)(iVar1 + 0x20);
  *piVar2 = *piVar2 + 1;
  FUN_004b4f00((void *)(iVar1 + 0x18),param_1);
  FUN_00435660((LPCRITICAL_SECTION)param_1[3]);
  LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
  return 0;
}


/* 00435400 size=102 */

undefined4 __fastcall FUN_00435400(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)param_1[3]);
  if ((int *)param_1[2] == (int *)0x0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
    return 0;
  }
  (**(code **)(*(int *)param_1[2] + 0x18))(param_1 + 8);
  (**(code **)(*(int *)param_1[2] + 4))();
  iVar2 = param_1[3];
  param_1[2] = 0;
  piVar1 = (int *)(iVar2 + 0x20);
  *piVar1 = *piVar1 + -1;
  FUN_004b4f60((void *)(iVar2 + 0x18),param_1);
  iVar2 = param_1[3];
  piVar1 = (int *)(iVar2 + 0x2c);
  *piVar1 = *piVar1 + 1;
  FUN_004b4f00((void *)(iVar2 + 0x24),param_1);
  LeaveCriticalSection((LPCRITICAL_SECTION)param_1[3]);
  return 0;
}


/* 00435470 size=21 */

void __thiscall FUN_00435470(void *this,PRTL_CRITICAL_SECTION_DEBUG param_1)

{
  InitializeCriticalSection(this);
  *(PRTL_CRITICAL_SECTION_DEBUG *)((int)this + 0x30) = param_1;
  return;
}


/* 00435490 size=17 */

void __fastcall FUN_00435490(LPCRITICAL_SECTION param_1)

{
  FUN_004355d0(param_1);
  DeleteCriticalSection(param_1);
  return;
}


/* 004354b0 size=174 */

int * __thiscall FUN_004354b0(void *this,char *param_1)

{
  char cVar1;
  int *piVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  
  if (param_1 == (char *)0x0) {
    return (int *)0x0;
  }
  piVar2 = (int *)FUN_00430de0(0x24);
  if (piVar2 != (int *)0x0) {
    piVar2[5] = 0;
    piVar2[6] = 0;
    *(undefined2 *)(piVar2 + 7) = 0;
    piVar2[2] = 0;
    piVar2[4] = 0;
    piVar2[6] = 0;
    piVar2[8] = 0;
    uVar4 = 0xffffffff;
    piVar2[3] = (int)this;
    pcVar3 = param_1;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar3 = (char *)FUN_00430de0(~uVar4);
    piVar2[6] = (int)pcVar3;
    if (pcVar3 != (char *)0x0) {
      uVar4 = 0xffffffff;
      do {
        pcVar6 = param_1;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar6 = param_1 + 1;
        cVar1 = *param_1;
        param_1 = pcVar6;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      pcVar6 = pcVar6 + -uVar4;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar3 = pcVar3 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar3 = pcVar3 + 1;
      }
      EnterCriticalSection(this);
      *(int *)((int)this + 0x2c) = *(int *)((int)this + 0x2c) + 1;
      FUN_004b4f00((void *)((int)this + 0x24),piVar2);
      LeaveCriticalSection(this);
      return piVar2;
    }
  }
  return (int *)0x0;
}


/* 00435560 size=107 */

void __thiscall FUN_00435560(void *this,int *param_1)

{
  int iVar1;
  void *this_00;
  
  if (param_1 == (int *)0x0) {
    return;
  }
  EnterCriticalSection(this);
  if (param_1[2] != 0) {
    iVar1 = FUN_00435220(param_1);
    this_00 = (void *)((int)this + 0x18);
    if (iVar1 != 0) goto LAB_0043558b;
  }
  this_00 = (void *)((int)this + 0x24);
LAB_0043558b:
  *(int *)((int)this_00 + 8) = *(int *)((int)this_00 + 8) + -1;
  FUN_004b4f60(this_00,param_1);
  LeaveCriticalSection(this);
  if (param_1[2] != 0) {
    FUN_00435220(param_1);
  }
  if ((undefined *)param_1[6] != (undefined *)0x0) {
    FUN_00430df0((undefined *)param_1[6]);
  }
  FUN_00430df0((undefined *)param_1);
  return;
}


/* 004355d0 size=74 */

void __fastcall FUN_004355d0(LPCRITICAL_SECTION param_1)

{
  PRTL_CRITICAL_SECTION_DEBUG p_Var1;
  int *piVar2;
  int iVar3;
  
  EnterCriticalSection(param_1);
  iVar3 = FUN_00435620(param_1);
  if (iVar3 != 0) {
    p_Var1 = param_1[1].DebugInfo;
    while (p_Var1 != (PRTL_CRITICAL_SECTION_DEBUG)0x0) {
      FUN_00435560(param_1,(int *)p_Var1);
      p_Var1 = param_1[1].DebugInfo;
    }
  }
  piVar2 = param_1[1].OwningThread;
  while (piVar2 != (int *)0x0) {
    FUN_00435560(param_1,piVar2);
    piVar2 = param_1[1].OwningThread;
  }
  LeaveCriticalSection(param_1);
  return;
}


/* 00435620 size=62 */

undefined4 __fastcall FUN_00435620(LPCRITICAL_SECTION param_1)

{
  PRTL_CRITICAL_SECTION_DEBUG p_Var1;
  int iVar2;
  
  EnterCriticalSection(param_1);
  p_Var1 = param_1[1].DebugInfo;
  while( true ) {
    if (p_Var1 == (PRTL_CRITICAL_SECTION_DEBUG)0x0) {
      LeaveCriticalSection(param_1);
      return 0;
    }
    iVar2 = FUN_00435220((int *)p_Var1);
    if (iVar2 != 0) break;
    p_Var1 = *(PRTL_CRITICAL_SECTION_DEBUG *)p_Var1;
  }
  LeaveCriticalSection(param_1);
  return 1;
}


/* 00435660 size=65 */

void __fastcall FUN_00435660(LPCRITICAL_SECTION param_1)

{
  int *piVar1;
  int *piVar2;
  
  EnterCriticalSection(param_1);
  piVar2 = (int *)param_1[1].LockCount;
  if (param_1[2].DebugInfo < (PRTL_CRITICAL_SECTION_DEBUG)param_1[1].RecursionCount) {
    do {
      if (piVar2 == (int *)0x0) break;
      piVar1 = (int *)piVar2[1];
      if (piVar2[4] == 0) {
        FUN_00435400(piVar2);
      }
      piVar2 = piVar1;
    } while (param_1[2].DebugInfo < (PRTL_CRITICAL_SECTION_DEBUG)param_1[1].RecursionCount);
  }
  LeaveCriticalSection(param_1);
  return;
}


/* 004356e0 size=16 */

void FUN_004356e0(void)

{
  if (DAT_004e4484 == 0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x004356e9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DebugBreak();
  return;
}


/* 004357f0 size=70 */

undefined4 FUN_004357f0(void)

{
  bool bVar1;
  HRESULT HVar2;
  undefined3 extraout_var;
  
  HVar2 = CoInitialize((LPVOID)0x0);
  if (-1 < HVar2) {
    DAT_004e9820 = 1;
    FUN_00430e20();
    FUN_0049b560();
    FUN_00427770();
    FUN_00431110();
    FUN_0046b100();
    bVar1 = dsys_interface_435840();
    if (CONCAT31(extraout_var,bVar1) != 0) {
      return 0;
    }
    FUN_00435860();
  }
  return 1;
}


/* 00435860 size=56 */

void FUN_00435860(void)

{
  FUN_0046b110();
  FUN_00431140();
  FUN_0043c4b0();
  FUN_0049b580();
  FUN_00430e80();
  FUN_004358a0();
  if (DAT_004e9820 != 0) {
    CoUninitialize();
    DAT_004e9820 = 0;
  }
  return;
}


/* 004358a0 size=27 */

void FUN_004358a0(void)

{
  if (DAT_004e9824 != (HMODULE)0x0) {
    FreeLibrary(DAT_004e9824);
    DAT_004e9824 = (HMODULE)0x0;
  }
  return;
}


/* 004358c0 size=264 */

int __cdecl FUN_004358c0(int param_1,LPCSTR param_2,char *param_3,LPCSTR param_4,int param_5)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  undefined3 extraout_var;
  UINT UVar4;
  undefined3 extraout_var_00;
  int local_108;
  CHAR local_104 [260];
  
  iVar1 = param_1 + 0xc3c;
  iVar3 = FUN_0047b730(iVar1,param_3,&local_108,(undefined4 *)0x0);
  if ((iVar3 != 0) && (iVar3 = FUN_00427940(*(undefined4 **)(local_108 + 0xc)), iVar3 == 1)) {
    FUN_00427a90(*(int **)(local_108 + 0xc),param_3,param_4);
    return 0;
  }
  FUN_004b9f62(param_4,&DAT_004d56a0,param_2);
  uVar2 = FUN_0047b6d0(iVar1,param_3,param_4);
  iVar3 = CONCAT31(extraout_var,uVar2);
  if (iVar3 == 0) {
    return 0;
  }
  UVar4 = GetTempFileNameA(param_2,param_3,0,local_104);
  if (UVar4 != 0) {
    uVar2 = FUN_0047b6d0(iVar1,param_3,local_104);
    iVar3 = CONCAT31(extraout_var_00,uVar2);
    if (iVar3 == 0) {
      _strncpy(param_4,local_104,param_5 - 1);
      return 0;
    }
  }
  return iVar3;
}


/* 00436090 size=287 */

int __cdecl FUN_00436090(int param_1,LPCSTR param_2,char *param_3,LPCSTR param_4,int param_5)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined3 extraout_var;
  UINT UVar4;
  undefined3 extraout_var_00;
  int local_110;
  char *local_10c;
  undefined2 local_108;
  CHAR local_104 [260];
  
  local_108 = 0;
  local_110 = 0;
  local_10c = param_3;
  puVar2 = FUN_004047a0(*(int *)(param_1 + 0x1644),&local_110,'\x05');
  if ((puVar2 != (undefined4 *)0x0) && (iVar3 = FUN_00427940((undefined4 *)puVar2[4]), iVar3 == 1))
  {
    FUN_00427a90((int *)puVar2[4],param_3,param_4);
    return 0;
  }
  FUN_004b9f62(param_4,&DAT_004d56a0,param_2);
  bVar1 = FUN_00404a70(*(int *)(param_1 + 0x1644),param_3,param_4);
  iVar3 = CONCAT31(extraout_var,bVar1);
  if (iVar3 == 0) {
    return 0;
  }
  UVar4 = GetTempFileNameA(param_2,param_3,0,local_104);
  if (UVar4 != 0) {
    bVar1 = FUN_00404a70(*(int *)(param_1 + 0x1644),param_3,local_104);
    iVar3 = CONCAT31(extraout_var_00,bVar1);
    if (iVar3 == 0) {
      _strncpy(param_4,local_104,param_5 - 1);
      return 0;
    }
  }
  return iVar3;
}


/* 004364e0 size=12 */

void FUN_004364e0(void)

{
                    /* WARNING: Subroutine does not return */
  _longjmp(&DAT_004e442c,1);
}


/* 004364f0 size=16 */

void __cdecl FUN_004364f0(DWORD param_1)

{
  if (param_1 != 0) {
    Sleep(param_1);
  }
  return;
}


/* 00436500 size=6 */

undefined4 FUN_00436500(void)

{
  return DAT_004e4b54;
}


/* 00436510 size=7 */

undefined2 FUN_00436510(void)

{
  return (undefined2)DAT_004e4b4c;
}


/* 00436520 size=7 */

undefined2 FUN_00436520(void)

{
  return (*(uint16_t*)((char*)&DAT_004e4b4c+2));
}


/* 00436530 size=12 */

undefined4 __cdecl FUN_00436530(int param_1)

{
  return *(undefined4 *)(&DAT_004e469c + param_1 * 4);
}


/* 00436540 size=12 */

undefined4 __cdecl FUN_00436540(int param_1)

{
  return *(undefined4 *)(&DAT_004e49bc + param_1 * 4);
}


/* 00436550 size=12 */

undefined4 __cdecl FUN_00436550(int param_1)

{
  return *(undefined4 *)(&DAT_004e482c + param_1 * 4);
}


/* 00436560 size=10 */

void FUN_00436560(void)

{
  (*(uint16_t*)((char*)&DAT_004e4b4c+0)) = 0;
  return;
}


/* 00436570 size=10 */

void FUN_00436570(void)

{
  (*(uint16_t*)((char*)&DAT_004e4b4c+2)) = 0;
  return;
}


/* 00436580 size=98 */

void FUN_00436580(void)

{
  BOOL BVar1;
  int iVar2;
  tagMSG local_1c;
  
  iVar2 = 0;
  do {
    BVar1 = PeekMessageA(&local_1c,DAT_004e446c,0x100,0x100,1);
    if (BVar1 == 0) break;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 500);
  iVar2 = 0;
  do {
    BVar1 = PeekMessageA(&local_1c,DAT_004e446c,0x101,0x101,1);
    if (BVar1 == 0) {
      return;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 500);
  return;
}


/* 004365f0 size=6 */

undefined4 FUN_004365f0(void)

{
  return DAT_004e4b50;
}


/* 00436600 size=10 */

void __cdecl FUN_00436600(undefined4 param_1)

{
  DAT_004e4b50 = param_1;
  return;
}


/* 00436610 size=6 */

undefined4 FUN_00436610(void)

{
  return DAT_004e4488;
}


/* 00436620 size=66 */

void __cdecl FUN_00436620(char *param_1)

{
  if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    DAT_004e4b58 = 0;
  }
  else {
    _strncpy(&DAT_004e4b58,param_1,499);
    DAT_004e4d4b = 0;
  }
  if (DAT_004e4428 != 0) {
    PostQuitMessage(0);
  }
  return;
}


/* 00436670 size=53 */

int __cdecl FUN_00436670(byte *param_1,undefined4 param_2)

{
  uint local_1f4 [125];
  
  FUN_004bbd09((undefined1 *)local_1f4,param_1,&param_2);
  FUN_00420e60(0xffff00,0,local_1f4);
  return;
}


/* 004366b0 size=6 */

undefined4 FUN_004366b0(void)

{
  return DAT_004e4470;
}


/* 004366c0 size=6 */

undefined4 FUN_004366c0(void)

{
  return DAT_004e446c;
}


/* 004366d0 size=56 */

undefined4 __cdecl FUN_004366d0(uint *param_1)

{
  FUN_00420e60(0xffffff,0,param_1);
  if (DAT_004eaa9c == 0) {
    MessageBoxA(DAT_004e446c,(LPCSTR)param_1,DAT_004e4478,0);
  }
  return 0;
}


/* 00436710 size=26 */

void __cdecl FUN_00436710(LPCSTR param_1,LPCSTR param_2)

{
  MessageBoxA(DAT_004e446c,param_1,param_2,0);
  return;
}


/* 00436730 size=21 */

void __cdecl FUN_00436730(undefined4 *param_1)

{
  FUN_004a1490(DAT_004e4470,param_1);
  return;
}


/* 00436780 size=22 */

void __fastcall FUN_00436780(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return;
}


/* 004367a0 size=51 */

undefined4 * __fastcall FUN_004367a0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = param_1 + 0x33;
  iVar2 = 8;
  do {
    FUN_00436780(puVar1);
    puVar1 = puVar1 + 6;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  *param_1 = &PTR_LAB_004cc3d4;
  param_1[0x32] = 0;
  return param_1;
}


/* 004367e0 size=112 */

void __fastcall FUN_004367e0(undefined4 *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  *param_1 = &PTR_LAB_004cc3d4;
  if (((*(byte *)(param_1 + 6) & 4) != 0) && (uVar3 = 0, *(short *)(param_1 + 5) != 0)) {
    puVar4 = param_1 + 0x35;
    do {
      if ((undefined *)*puVar4 != (undefined *)0x0) {
        FUN_00430fe0((undefined *)*puVar4);
      }
      uVar3 = uVar3 + 1;
      puVar4 = puVar4 + 6;
    } while (uVar3 < *(ushort *)(param_1 + 5));
  }
  if ((undefined *)param_1[0x32] != (undefined *)0x0) {
    FUN_00430df0((undefined *)param_1[0x32]);
  }
  puVar2 = (undefined *)param_1[0x2f];
  while (puVar2 != (undefined *)0x0) {
    puVar1 = *(undefined **)(puVar2 + 0x20);
    FUN_00430fe0(puVar2);
    puVar2 = puVar1;
  }
  return;
}


/* 00436890 size=455 */

undefined4 * __cdecl
FUN_00436890(int param_1,uint param_2,uint param_3,int param_4,undefined4 *param_5,size_t *param_6,
            int param_7)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  size_t sVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  size_t local_4;
  
  sVar4 = 0;
  local_4 = 0;
  if (param_4 != 0) {
    local_4 = param_4;
    uVar5 = param_3;
    uVar6 = param_2;
    do {
      uVar1 = FUN_0046e7b0(param_1,uVar6,uVar5);
      if (param_7 != 0) {
        uVar1 = uVar1 + uVar5 * uVar6;
      }
      sVar4 = sVar4 + uVar1;
      uVar6 = uVar6 >> 1;
      uVar5 = uVar5 >> 1;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
    local_4 = sVar4;
  }
  puVar2 = (undefined4 *)FUN_00430de0(0x18c);
  if ((puVar2 == (undefined4 *)0x0) || (puVar2 = FUN_004367a0(puVar2), puVar2 == (undefined4 *)0x0))
  {
    return (undefined4 *)0x0;
  }
  iVar3 = FUN_00430de0(local_4);
  puVar2[0x32] = iVar3;
  if (iVar3 == 0) {
    FUN_004367e0(puVar2);
    FUN_00430df0((undefined *)puVar2);
    return (undefined4 *)0x0;
  }
  puVar2[1] = 0;
  puVar2[0x2e] = local_4 + 0x18c;
  puVar2[2] = 0;
  puVar2[6] = 8;
  puVar2[7] = 0;
  *(undefined2 *)(puVar2 + 5) = (undefined2)param_4;
  *(short *)(puVar2 + 4) = (short)param_2;
  *(short *)((int)puVar2 + 0x12) = (short)param_3;
  puVar2[3] = 0xfffffffb;
  *(undefined1 *)(puVar2 + 0xb) = 0;
  puVar2[0x2d] = puVar2;
  puVar2[0x2f] = 0;
  *(undefined2 *)((int)puVar2 + 0x16) = 0;
  puVar2[10] = 0;
  puVar2[9] = 0;
  puVar2[8] = 0;
  *(undefined1 *)((int)puVar2 + 0x22) = (undefined1)param_1;
  puVar2[0x30] = 0;
  puVar2[0x31] = 0;
  if (param_4 != 0) {
    puVar7 = puVar2 + 0x36;
    uVar5 = param_2;
    param_2 = puVar2[0x32];
    do {
      puVar7[-3] = uVar5;
      puVar7[-2] = param_3;
      puVar7[-1] = param_2;
      if (param_1 == 3) {
        *puVar7 = uVar5 * 4;
      }
      else {
        *puVar7 = (param_1 != 7) - 1 & uVar5;
      }
      uVar6 = FUN_0046e7b0(param_1,uVar5,param_3);
      param_2 = param_2 + uVar6;
      if (param_7 != 0) {
        puVar7[1] = param_2;
        param_2 = param_2 + param_3 * uVar5;
        puVar7[2] = uVar5;
      }
      puVar7 = puVar7 + 6;
      uVar5 = uVar5 >> 1;
      param_3 = param_3 >> 1;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = puVar2[0x2e];
  }
  if (param_6 != (size_t *)0x0) {
    *param_6 = local_4;
  }
  return puVar2;
}


/* 00436a60 size=786 */

undefined4 __cdecl FUN_00436a60(int *param_1,int param_2)

{
  undefined4 *puVar1;
  size_t *psVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  uint *puVar6;
  size_t *psVar7;
  int *piVar8;
  uint uVar9;
  size_t *psVar10;
  undefined4 *unaff_retaddr;
  size_t asStack_d4 [2];
  undefined1 auStack_cc [20];
  int iStack_b8;
  int aiStack_ac [2];
  ushort local_a4;
  ushort uStack_a2;
  ushort uStack_a0;
  ushort uStack_9e;
  byte bStack_9c;
  uint uStack_92;
  
  (**(code **)(*param_1 + 8))(&local_a4,0xa4);
  if (aiStack_ac[0] == 0) {
    if (aiStack_ac[1] != -5) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_dtx_Create_004d81f0);
      }
      return 0x45;
    }
    if ((uStack_a0 == 0) || (0xf < uStack_a0)) {
      FUN_004356e0();
    }
    else {
      if ((char)uStack_92 == '\0') {
        uVar3 = 3;
      }
      else {
        uVar3 = uStack_92 & 0xff;
      }
      puVar1 = FUN_00436890(uVar3,(uint)local_a4,(uint)uStack_a2,(uint)uStack_a0,asStack_d4 + 1,
                            asStack_d4,0);
      if (puVar1 == (undefined4 *)0x0) {
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_dtx_Create_004d81f0);
        }
        return 0x43;
      }
      puVar1[0x30] = 0;
      piVar5 = aiStack_ac;
      piVar8 = puVar1 + 2;
      for (iVar4 = 0x29; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar8 = *piVar5;
        piVar5 = piVar5 + 1;
        piVar8 = piVar8 + 1;
      }
      uVar3 = 0;
      if (uStack_a0 != 0) {
        puVar6 = puVar1 + 0x34;
        do {
          if (((char)uStack_92 == '\0') || ((uStack_92 & 0xff) == 3)) {
            uVar9 = 0;
            if (*puVar6 != 0) {
              do {
                FUN_00436d80(param_2,param_1,(undefined4 *)(puVar6[2] * uVar9 + puVar6[1]),
                             puVar6[-1] << 2);
                uVar9 = uVar9 + 1;
              } while (uVar9 < *puVar6);
            }
          }
          else {
            uVar9 = FUN_0046e7b0(uStack_92 & 0xff,puVar6[-1],*puVar6);
            FUN_00436d80(param_2,param_1,(undefined4 *)puVar6[1],uVar9);
          }
          uVar3 = uVar3 + 1;
          puVar6 = puVar6 + 6;
        } while (uVar3 < uStack_a0);
      }
      if ((bStack_9c & 8) == 0) {
        *(undefined2 *)((int)puVar1 + 0x16) = 0;
        puVar1[6] = puVar1[6] | 8;
      }
      else if ((param_1 != (int *)0x0) && (uVar3 = 0, uStack_9e != 0)) {
        do {
          (**(code **)(*param_1 + 8))(auStack_cc,0x20);
          psVar2 = FUN_00430f00(iStack_b8 + 0x27);
          psVar7 = asStack_d4;
          psVar10 = psVar2;
          for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
            *psVar10 = *psVar7;
            psVar7 = psVar7 + 1;
            psVar10 = psVar10 + 1;
          }
          (**(code **)(*param_1 + 8))(psVar2 + 9,iStack_b8);
          psVar2[8] = puVar1[0x2f];
          puVar1[0x2f] = psVar2;
          uVar3 = uVar3 + 1;
        } while (uVar3 < uStack_9e);
      }
      iVar4 = (**(code **)(*param_1 + 0x10))();
      if (iVar4 == 0) {
        *unaff_retaddr = puVar1;
        return 0;
      }
      FUN_00436de0(puVar1);
      FUN_004356e0();
    }
  }
  else {
    FUN_004356e0();
  }
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_dtx_Create_004d81f0);
  }
  return 0x42;
}


/* 00436d80 size=91 */

void __cdecl FUN_00436d80(int param_1,int *param_2,undefined4 *param_3,uint param_4)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  uVar2 = param_4;
  piVar1 = param_2;
  if (param_1 == 0) {
    (**(code **)(*param_2 + 8))(param_3,param_4);
    return;
  }
  puVar4 = param_3;
  for (uVar3 = param_4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  for (uVar3 = param_4 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)puVar4 = 0;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  (**(code **)(*param_2 + 0x18))(&param_2);
  (**(code **)(*piVar1 + 0x14))(param_1 + uVar2);
  return;
}


/* 00436de0 size=27 */

void __cdecl FUN_00436de0(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    FUN_004367e0(param_1);
    FUN_00430df0((undefined *)param_1);
  }
  return;
}


/* 00436e00 size=32 */

void __cdecl FUN_00436e00(int param_1,undefined4 *param_2)

{
  if (param_1 == 3) {
    FUN_0046e300(param_2);
    return;
  }
  (**(code **)*param_2)(param_1,0,0,0,0);
  return;
}


/* 00436e20 size=68 */

undefined4 __cdecl FUN_00436e20(char *param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  char cVar3;
  
  while( true ) {
    cVar1 = *param_1;
    if ((cVar1 < 'a') || ('z' < cVar1)) {
      cVar3 = cVar1;
    }
    else {
      cVar3 = cVar1 + -0x20;
    }
    cVar2 = *param_2;
    if (('`' < cVar2) && (cVar2 < '{')) {
      cVar2 = cVar2 + -0x20;
    }
    if (cVar3 != cVar2) break;
    if (cVar1 == '\0') {
      return 1;
    }
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  }
  return 0;
}


/* 00436e70 size=1 */

void FUN_00436e70(void)

{
  return;
}


/* 00436f60 size=377 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FUN_00436f60: lifted from original x86 -> lt_lifted.c */


/* 004371d0 size=16 */

void __cdecl FUN_004371d0(undefined *param_1)

{
  if (param_1 != (undefined *)0x0) {
    FUN_00430fe0(param_1);
  }
  return;
}


/* 00437590 size=35 */

void __cdecl FUN_00437590(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar2 = *(undefined **)(param_1 + 0x12e8);
  while (puVar2 != (undefined *)0x0) {
    puVar1 = *(undefined **)(puVar2 + 0xc);
    FUN_00430fe0(puVar2);
    puVar2 = puVar1;
  }
  return;
}


/* 00437680 size=6 */

undefined ** FUN_00437680(void)

{
  return &PTR_s_BindIP_004d8388;
}


/* 00437690 size=6 */

undefined4 FUN_00437690(void)

{
  return 0x60;
}


/* 00437730 size=40 */

void FUN_00437730(void)

{
  if (DAT_004e9948 != (FILE *)0x0) {
    FUN_004bbe95((int *)DAT_004e9948);
    FUN_004ba14f(DAT_004e9948);
    DAT_004e9948 = (FILE *)0x0;
  }
  return;
}


/* 00437c80 size=75 */

void __cdecl FUN_00437c80(HANDLE param_1,LPCSTR param_2,char param_3)

{
  DWORD nNumberOfBytesToWrite;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  DWORD local_7d4;
  CHAR local_7d0 [2000];
  
  lpNumberOfBytesWritten = &local_7d4;
  wvsprintfA(local_7d0,param_2,&param_3);
  lpOverlapped = (LPOVERLAPPED)0x0;
  nNumberOfBytesToWrite = lstrlenA(local_7d0);
  WriteFile(param_1,local_7d0,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
  return;
}


/* 00437cd0 size=160 */

void __cdecl FUN_00437cd0(HANDLE param_1)

{
  PVOID pvVar1;
  SIZE_T SVar2;
  uint uVar3;
  HMODULE pHVar4;
  uint uVar5;
  char unaff_DI;
  _MEMORY_BASIC_INFORMATION local_40;
  _SYSTEM_INFO local_24;
  
  FUN_00437c80(param_1,s_Module_list__names__addresses__s_004d929c,unaff_DI);
  GetSystemInfo(&local_24);
  uVar5 = 0;
  pHVar4 = (HMODULE)0x0;
  uVar3 = (int)(0x40000000 / (ulonglong)local_24.dwPageSize) << 2;
  if (uVar3 != 0) {
    do {
      SVar2 = VirtualQuery((LPCVOID)(uVar5 * local_24.dwPageSize),&local_40,0x1c);
      pvVar1 = local_40.AllocationBase;
      if ((SVar2 == 0) || (local_40.RegionSize == 0)) {
        uVar5 = uVar5 + (int)(0x10000 / (ulonglong)local_24.dwPageSize);
      }
      else {
        uVar5 = uVar5 + local_40.RegionSize / local_24.dwPageSize;
        if ((local_40.State == 0x1000) && (pHVar4 < local_40.AllocationBase)) {
          FUN_00437d70(param_1,local_40.AllocationBase);
          pHVar4 = pvVar1;
        }
      }
    } while (uVar5 < uVar3);
  }
  return;
}


/* 00437d70 size=375 */

void __cdecl FUN_00437d70(HANDLE param_1,HMODULE param_2)

{
  __builtin_trap(); /* STUB: decompiled body did not compile */
}


/* 00437ef0 size=147 */

void __cdecl FUN_00437ef0(LPSTR param_1,FILETIME param_2)

{
  BOOL BVar1;
  uint local_8;
  uint local_4;
  
  BVar1 = FileTimeToLocalFileTime(&param_2,&param_2);
  if (BVar1 != 0) {
    BVar1 = FileTimeToDosDateTime(&param_2,(LPWORD)&local_4,(LPWORD)&local_8);
    if (BVar1 != 0) {
      wsprintfA(param_1,s__d__d__d__02d__02d__02d_004d9324,(local_4 & 0xffff) >> 5 & 0xf,
                local_4 & 0x1f,((local_4 & 0xffff) >> 9) + 0x7bc,(local_8 & 0xffff) >> 0xb,
                (local_8 & 0xffff) >> 5 & 0x3f,(local_8 & 0x1f) << 1);
      return;
    }
  }
  *param_1 = '\0';
  return;
}


