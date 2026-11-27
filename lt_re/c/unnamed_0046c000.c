/* lithtech.exe decompilation - unnamed_0046c000 */
#include "ghidra_types.h"

/* 0046c030 size=47 */

void __cdecl FUN_0046c030(int param_1)

{
  *(undefined4 *)(param_1 + 0x220) = *(undefined4 *)(param_1 + 0x210);
  *(undefined4 *)(param_1 + 0x224) = *(undefined4 *)(param_1 + 0x214);
  *(undefined4 *)(param_1 + 0x228) = *(undefined4 *)(param_1 + 0x218);
  *(undefined4 *)(param_1 + 0x22c) = *(undefined4 *)(param_1 + 0x21c);
  return;
}


/* 0046c060 size=101 */

undefined4 __cdecl FUN_0046c060(int param_1)

{
  FUN_0046bf00(param_1);
  if ((((*(float *)(param_1 + 0x220) == *(float *)(param_1 + 0x210)) &&
       (*(float *)(param_1 + 0x224) == *(float *)(param_1 + 0x214))) &&
      (*(float *)(param_1 + 0x228) == *(float *)(param_1 + 0x218))) &&
     (*(float *)(param_1 + 0x21c) <= *(float *)(param_1 + 0x22c))) {
    return 0;
  }
  return 1;
}


/* 0046c0d0 size=365 */

void __cdecl FUN_0046c0d0(int param_1)

{
  float *pfVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x1d0) == param_1 + 0x1b0) {
    *(undefined4 *)(param_1 + 0x238) = 0;
    *(undefined4 *)(param_1 + 0x23c) = 0;
    *(undefined4 *)(param_1 + 0x240) = 0;
    *(undefined4 *)(param_1 + 0x244) = 0;
    *(undefined4 *)(param_1 + 0x248) = 0;
    *(undefined4 *)(param_1 + 0x24c) = 0;
    *(undefined4 *)(param_1 + 0x210) = 0;
    *(undefined4 *)(param_1 + 0x214) = 0;
    *(undefined4 *)(param_1 + 0x218) = 0;
    *(undefined4 *)(param_1 + 0x21c) = 0x3f800000;
    return;
  }
  *(undefined4 *)(param_1 + 0x238) = 0x47c35000;
  *(undefined4 *)(param_1 + 0x23c) = 0x47c35000;
  *(undefined4 *)(param_1 + 0x240) = 0x47c35000;
  pfVar1 = (float *)(param_1 + 0x244);
  *pfVar1 = -*(float *)(param_1 + 0x238);
  *(float *)(param_1 + 0x248) = -*(float *)(param_1 + 0x23c);
  *(float *)(param_1 + 0x24c) = -*(float *)(param_1 + 0x240);
  for (iVar2 = *(int *)(param_1 + 0x1d0); iVar2 != param_1 + 0x1b0; iVar2 = *(int *)(iVar2 + 0x20))
  {
    if (*(float *)(iVar2 + 0x24) < *(float *)(param_1 + 0x238)) {
      *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(iVar2 + 0x24);
    }
    if (*(float *)(iVar2 + 0x28) < *(float *)(param_1 + 0x23c)) {
      *(undefined4 *)(param_1 + 0x23c) = *(undefined4 *)(iVar2 + 0x28);
    }
    if (*(float *)(iVar2 + 0x2c) < *(float *)(param_1 + 0x240)) {
      *(undefined4 *)(param_1 + 0x240) = *(undefined4 *)(iVar2 + 0x2c);
    }
    if (*pfVar1 < *(float *)(iVar2 + 0x24)) {
      *pfVar1 = *(float *)(iVar2 + 0x24);
    }
    if (*(float *)(param_1 + 0x248) < *(float *)(iVar2 + 0x28)) {
      *(undefined4 *)(param_1 + 0x248) = *(undefined4 *)(iVar2 + 0x28);
    }
    if (*(float *)(param_1 + 0x24c) < *(float *)(iVar2 + 0x2c)) {
      *(undefined4 *)(param_1 + 0x24c) = *(undefined4 *)(iVar2 + 0x2c);
    }
  }
  FUN_0046bf00(param_1);
  return;
}


/* 0046c330 size=461 */

undefined4 __cdecl FUN_0046c330(undefined4 param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  uint *puVar11;
  undefined4 *puVar12;
  uint uVar13;
  int iVar14;
  undefined4 *puVar15;
  uint local_8;
  uint local_4;
  
  puVar3 = param_2;
  uVar6 = param_2[7];
  uVar4 = FUN_0046e320(*param_2);
  puVar7 = (uint *)param_2[5];
  puVar11 = (uint *)param_2[1];
  uVar9 = uVar6 << ((byte)uVar4 & 0x1f);
  iVar1 = *(int *)(*param_2 + 4);
  if (((iVar1 == 4) || (iVar1 == 5)) || (iVar1 == 6)) {
    iVar14 = 1;
  }
  else {
    iVar14 = 0;
  }
  iVar5 = *(int *)(param_2[4] + 4);
  if (((iVar5 == 4) || (iVar5 == 5)) || (iVar5 == 6)) {
    iVar5 = 1;
  }
  else {
    iVar5 = 0;
  }
  if (iVar14 != iVar5) {
    return 1;
  }
  if (((iVar1 == 4) || (iVar1 == 5)) || (iVar1 == 6)) {
    uVar4 = 1;
    if ((param_2[9] & 1) == 0) {
      uVar6 = FUN_0046e7b0(iVar1,uVar6,param_2[8]);
      puVar12 = (undefined4 *)param_2[1];
      puVar15 = (undefined4 *)param_2[5];
      for (uVar9 = uVar6 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *puVar15 = *puVar12;
        puVar12 = puVar12 + 1;
        puVar15 = puVar15 + 1;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined1 *)puVar15 = *(undefined1 *)puVar12;
        puVar12 = (undefined4 *)((int)puVar12 + 1);
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
      return 0;
    }
  }
  else {
    if ((param_2[9] & 1) == 0) {
      local_4 = param_2[8];
      if (local_4 != 0) {
        param_2 = puVar7;
        do {
          puVar7 = puVar11;
          puVar8 = param_2;
          for (uVar6 = uVar9 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
          for (uVar6 = uVar9 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(byte *)puVar8 = (byte)*puVar7;
            puVar7 = (uint *)((int)puVar7 + 1);
            puVar8 = (uint *)((int)puVar8 + 1);
          }
          puVar11 = (uint *)((int)puVar11 + puVar3[2]);
          param_2 = (uint *)((int)param_2 + puVar3[6]);
          local_4 = local_4 - 1;
        } while (local_4 != 0);
      }
    }
    else {
      uVar6 = 0;
      local_8 = 0;
      if ((((uint)puVar11 & 3) == 0) && (((uint)puVar7 & 3) == 0)) {
        uVar6 = uVar9 >> 2;
        uVar9 = uVar9 + uVar6 * -4;
      }
      else if ((((uint)puVar11 & 1) == 0) && (((uint)puVar7 & 1) == 0)) {
        local_8 = uVar9 >> 1;
        uVar9 = uVar9 + local_8 * -2;
      }
      local_4 = param_2[8];
      if (local_4 != 0) {
        param_2 = puVar7;
        do {
          puVar7 = puVar11;
          puVar8 = param_2;
          uVar13 = local_8;
          if (uVar6 != 0) {
            uVar10 = uVar6;
            do {
              uVar2 = *puVar8;
              puVar8 = puVar8 + 1;
              *puVar7 = *puVar7 | uVar2;
              puVar7 = puVar7 + 1;
              uVar10 = uVar10 - 1;
            } while (uVar10 != 0);
          }
          for (; uVar13 != 0; uVar13 = uVar13 - 1) {
            *(ushort *)puVar7 = (ushort)*puVar7 | (ushort)*puVar8;
            puVar7 = (uint *)((int)puVar7 + 2);
            puVar8 = (uint *)((int)puVar8 + 2);
          }
          for (uVar13 = uVar9; uVar13 != 0; uVar13 = uVar13 - 1) {
            *(byte *)puVar7 = (byte)*puVar7 | (byte)*puVar8;
            puVar8 = (uint *)((int)puVar8 + 1);
            puVar7 = (uint *)((int)puVar7 + 1);
          }
          param_2 = (uint *)((int)param_2 + puVar3[6]);
          puVar11 = (uint *)((int)puVar11 + puVar3[2]);
          local_4 = local_4 - 1;
        } while (local_4 != 0);
        return 0;
      }
    }
    uVar4 = 0;
  }
  return uVar4;
}


/* 0046c680 size=67 */

void __thiscall FUN_0046c680(void *this,int param_1,int param_2)

{
  *(int *)((int)this + 0x10) = param_2;
  *(int *)this = *(int *)(param_2 + 0x18) * 0x100 + 0x70 + param_1;
  *(int *)((int)this + 4) = *(int *)(param_2 + 0x1c) * 0x100 + 0x70 + param_1;
  *(int *)((int)this + 8) = *(int *)(param_2 + 0x20) * 0x100 + 0x70 + param_1;
  *(int *)((int)this + 0xc) = *(int *)(param_2 + 0x24) * 0x100 + 0x70 + param_1;
  return;
}


/* 0046c6d0 size=94 */

/* FUN_0046c6d0: lifted from original x86 -> lt_lifted.c */


/* 0046c8b0 size=102 */

uint __thiscall FUN_0046c8b0(void *this,uint *param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = *param_1;
  iVar2 = *(int *)((int)this + 0x10);
  return CONCAT22((short)((uint)*(int *)((int)this + 8) >> 0x10),
                  (ushort)*(byte *)((uVar1 >> 8 & 0xff) + *(int *)((int)this + 8))) <<
         ((byte)*(undefined4 *)(iVar2 + 0x30) & 0x1f) |
         CONCAT22((short)((uint)*(int *)((int)this + 4) >> 0x10),
                  (ushort)*(byte *)((uVar1 >> 0x10 & 0xff) + *(int *)((int)this + 4))) <<
         ((byte)*(undefined4 *)(iVar2 + 0x2c) & 0x1f) |
         CONCAT22((short)((uint)*(int *)this >> 0x10),
                  (ushort)*(byte *)((uVar1 >> 0x18) + *(int *)this)) <<
         ((byte)*(undefined4 *)(iVar2 + 0x28) & 0x1f) |
         CONCAT22((short)((uint)*(int *)((int)this + 0xc) >> 0x10),
                  (ushort)*(byte *)((uVar1 & 0xff) + *(int *)((int)this + 0xc))) <<
         ((byte)*(undefined4 *)(iVar2 + 0x34) & 0x1f);
}


/* 0046cae0 size=38 */

uint __thiscall FUN_0046cae0(void *this,byte *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)this;
  uVar2 = (uint)*param_1;
  return (uint)CONCAT21(CONCAT11(*(undefined1 *)(iVar1 + 1 + uVar2 * 4),
                                 *(undefined1 *)(iVar1 + 2 + uVar2 * 4)),
                        *(undefined1 *)(iVar1 + uVar2 * 4 + 3));
}


/* 0046cb10 size=108 */

uint __thiscall FUN_0046cb10(void *this,uint *param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = *param_1;
  iVar2 = *(int *)((int)this + 0x10);
  return (uint)*(byte *)((uVar1 >> 8 & 0xff) + *(int *)((int)this + 8)) <<
         ((byte)*(undefined4 *)(iVar2 + 0x30) & 0x1f) |
         (uint)*(byte *)((uVar1 >> 0x10 & 0xff) + *(int *)((int)this + 4)) <<
         ((byte)*(undefined4 *)(iVar2 + 0x2c) & 0x1f) |
         (uint)*(byte *)(*(int *)this + (uVar1 >> 0x18)) <<
         ((byte)*(undefined4 *)(iVar2 + 0x28) & 0x1f) |
         (uint)*(byte *)((uVar1 & 0xff) + *(int *)((int)this + 0xc)) <<
         ((byte)*(undefined4 *)(iVar2 + 0x34) & 0x1f);
}


/* 0046cd00 size=67 */

void __thiscall FUN_0046cd00(void *this,int param_1,int param_2)

{
  undefined4 uVar1;
  
  *(undefined4 *)((int)this + 4) = *(undefined4 *)(param_1 + 0x970 + *(int *)(param_2 + 0x18) * 4);
  *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 0x970 + *(int *)(param_2 + 0x1c) * 4);
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0x970 + *(int *)(param_2 + 0x20) * 4)
  ;
  uVar1 = *(undefined4 *)(param_1 + 0x970 + *(int *)(param_2 + 0x24) * 4);
  *(int *)this = param_2;
  *(undefined4 *)((int)this + 0x10) = uVar1;
  return;
}


/* 0046cd50 size=130 */

undefined4 __thiscall FUN_0046cd50(void *this,byte *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)this;
  uVar2 = (uint)*param_1;
  return CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)
                                     (((*(uint *)(iVar1 + 8) & uVar2) >>
                                      ((byte)*(undefined4 *)(iVar1 + 0x28) & 0x1f)) +
                                     *(int *)((int)this + 4)),
                                    *(undefined1 *)
                                     (((*(uint *)(iVar1 + 0xc) & uVar2) >>
                                      ((byte)*(undefined4 *)(iVar1 + 0x2c) & 0x1f)) +
                                     *(int *)((int)this + 8))),
                           *(undefined1 *)
                            (((*(uint *)(iVar1 + 0x10) & uVar2) >>
                             ((byte)*(undefined4 *)(iVar1 + 0x30) & 0x1f)) +
                            *(int *)((int)this + 0xc))),
                  *(undefined1 *)
                   (*(int *)((int)this + 0x10) +
                   ((*(uint *)(iVar1 + 0x14) & uVar2) >>
                   ((byte)*(undefined4 *)(iVar1 + 0x34) & 0x1f))));
}


/* 0046d220 size=129 */

undefined4 __thiscall FUN_0046d220(void *this,ushort *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)this;
  uVar2 = (uint)*param_1;
  return CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)
                                     (((*(uint *)(iVar1 + 8) & uVar2) >>
                                      ((byte)*(undefined4 *)(iVar1 + 0x28) & 0x1f)) +
                                     *(int *)((int)this + 4)),
                                    *(undefined1 *)
                                     (((*(uint *)(iVar1 + 0xc) & uVar2) >>
                                      ((byte)*(undefined4 *)(iVar1 + 0x2c) & 0x1f)) +
                                     *(int *)((int)this + 8))),
                           *(undefined1 *)
                            (((*(uint *)(iVar1 + 0x10) & uVar2) >>
                             ((byte)*(undefined4 *)(iVar1 + 0x30) & 0x1f)) +
                            *(int *)((int)this + 0xc))),
                  *(undefined1 *)
                   (*(int *)((int)this + 0x10) +
                   ((*(uint *)(iVar1 + 0x14) & uVar2) >>
                   ((byte)*(undefined4 *)(iVar1 + 0x34) & 0x1f))));
}


/* 0046d5e0 size=81 */

uint __thiscall FUN_0046d5e0(void *this,uint *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)this;
  uVar2 = *param_1;
  return (((uVar2 >> ((byte)*(undefined4 *)(iVar1 + 0x28) & 0x1f) & 0xff) << 8 |
          uVar2 >> ((byte)*(undefined4 *)(iVar1 + 0x2c) & 0x1f) & 0xff) << 8 |
         uVar2 >> ((byte)*(undefined4 *)(iVar1 + 0x30) & 0x1f) & 0xff) << 8 |
         uVar2 >> ((byte)*(undefined4 *)(iVar1 + 0x34) & 0x1f) & 0xff;
}


/* 0046e230 size=62 */

void __thiscall
FUN_0046e230(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  uint uVar1;
  
  uVar1 = 0;
  *(undefined4 *)((int)this + 4) = param_1;
  *(undefined4 *)((int)this + 8) = param_2;
  *(undefined4 *)((int)this + 0xc) = param_3;
  *(undefined4 *)((int)this + 0x10) = param_4;
  *(undefined4 *)((int)this + 0x14) = param_5;
  do {
    FUN_0046e270((int)this,uVar1);
    uVar1 = uVar1 + 1;
  } while (uVar1 < 4);
  return;
}


/* 0046e270 size=54 */

void __cdecl FUN_0046e270(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_2;
  iVar1 = param_1;
  FUN_0046e2b0(*(uint *)(param_1 + 8 + param_2 * 4),&param_1,&param_2);
  *(int *)(iVar1 + 0x18 + iVar2 * 4) = param_1 - param_2;
  *(int *)(iVar1 + 0x28 + iVar2 * 4) = param_2;
  return;
}


/* 0046e2b0 size=70 */

void __cdecl FUN_0046e2b0(uint param_1,int *param_2,int *param_3)

{
  uint uVar1;
  uint uVar2;
  
  *param_3 = 0;
  uVar1 = 1;
  uVar2 = 0;
  do {
    if ((param_1 & uVar1) != 0) break;
    uVar1 = uVar1 << 1;
    uVar2 = uVar2 + 1;
    *param_3 = *param_3 + 1;
  } while (uVar2 < 0x20);
  *param_2 = *param_3;
  uVar2 = 0;
  do {
    if ((param_1 & uVar1) == 0) {
      return;
    }
    uVar1 = uVar1 << 1;
    uVar2 = uVar2 + 1;
    *param_2 = *param_2 + 1;
  } while (uVar2 < 0x20);
  return;
}


/* 0046e300 size=27 */

void __fastcall FUN_0046e300(undefined4 *param_1)

{
  (**(code **)*param_1)(3,0xff000000,0xff0000,0xff00,0xff);
  return;
}


/* 0046e320 size=11 */

undefined4 __fastcall FUN_0046e320(int param_1)

{
  return *(undefined4 *)(&DAT_004db5b4 + *(int *)(param_1 + 4) * 4);
}


/* 0046e330 size=68 */

undefined4 __thiscall FUN_0046e330(void *this,int param_1)

{
  if ((((*(int *)((int)this + 4) == *(int *)(param_1 + 4)) &&
       (*(int *)((int)this + 8) == *(int *)(param_1 + 8))) &&
      (*(int *)((int)this + 0xc) == *(int *)(param_1 + 0xc))) &&
     ((*(int *)((int)this + 0x10) == *(int *)(param_1 + 0x10) &&
      (*(int *)((int)this + 0x14) == *(int *)(param_1 + 0x14))))) {
    return 1;
  }
  return 0;
}


/* 0046e380 size=11 */

undefined4 __fastcall FUN_0046e380(int param_1)

{
  return *(undefined4 *)(&DAT_004db5d4 + *(int *)(param_1 + 4) * 4);
}


/* 0046e390 size=55 */

void __fastcall FUN_0046e390(int *param_1)

{
  param_1[10] = (int)&PTR_FUN_004cbb4c;
  param_1[0x18] = (int)&PTR_FUN_004cbb4c;
  *param_1 = (int)(param_1 + 10);
  param_1[4] = (int)(param_1 + 0x18);
  param_1[3] = 0;
  param_1[1] = 0;
  param_1[2] = -1;
  param_1[5] = 0;
  param_1[6] = -1;
  param_1[7] = -1;
  param_1[8] = -1;
  param_1[9] = 0;
  return;
}


/* 0046e3d0 size=190 */

undefined4 __fastcall FUN_0046e3d0(int *param_1)

{
  int iVar1;
  int iVar2;
  
  if ((((((((*param_1 == 0) || (param_1[1] == 0)) || (param_1[4] == 0)) ||
         ((param_1[5] == 0 || (param_1[7] == -1)))) ||
        ((param_1[8] == 0xffffffff ||
         (((iVar1 = *(int *)(*param_1 + 4), iVar1 != 4 && (iVar1 != 5)) &&
          ((iVar1 != 6 && (param_1[2] == -1)))))))) ||
       ((((iVar2 = *(int *)(param_1[4] + 4), iVar2 != 4 && (iVar2 != 5)) && (iVar2 != 6)) &&
        (param_1[6] == -1)))) ||
      (((((iVar1 == 4 || (iVar1 == 5)) || ((iVar1 == 6 || ((iVar2 == 4 || (iVar2 == 5)))))) ||
        (iVar2 == 6)) && (((*(byte *)(param_1 + 7) & 3) != 0 || ((param_1[8] & 3U) != 0)))))) ||
     (((iVar1 == 0 && (param_1[3] == 0)) || ((iVar1 == 7 && (param_1[3] == 0)))))) {
    return 0;
  }
  return 1;
}


/* 0046e490 size=37 */

void __fastcall FUN_0046e490(int *param_1)

{
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[8] = (int)&PTR_FUN_004cbb4c;
  *param_1 = (int)(param_1 + 8);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[7] = 0;
  return;
}


/* 0046e4c0 size=21 */

undefined4 __fastcall FUN_0046e4c0(int *param_1)

{
  if ((*param_1 == 0) || (param_1[1] == 0)) {
    return 0;
  }
  return 1;
}


/* 0046e4e0 size=58 */

undefined4 * __fastcall FUN_0046e4e0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004cbb4c;
  param_1[0xe] = &PTR_FUN_004cbb4c;
  FUN_0046e300(param_1);
  (**(code **)param_1[0xe])(2,0,0xf800,0x7e0,0x1f);
  FUN_0046e640((int)param_1);
  return param_1;
}


/* 0046e520 size=84 */

undefined4 __thiscall FUN_0046e520(void *this,int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0046e3d0(param_1);
  if (iVar1 == 0) {
    return 1;
  }
  iVar1 = FUN_00468720(param_1[4]);
  iVar2 = FUN_00468720(*param_1);
  if ((code *)(&PTR_FUN_004db5f4)[iVar1 + iVar2 * 8] == (code *)0x0) {
    return 0x53;
  }
  uVar3 = (*(code *)(&PTR_FUN_004db5f4)[iVar1 + iVar2 * 8])(this,param_1);
  return uVar3;
}


/* 0046e580 size=191 */

undefined4 __thiscall FUN_0046e580(void *this,int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  
  piVar2 = param_1;
  iVar3 = FUN_0046e4c0(param_1);
  if (iVar3 != 0) {
    iVar3 = *(int *)(*piVar2 + 4);
    if ((iVar3 == 2) || (iVar3 == 3)) {
      FUN_0046e730(this,*piVar2,(char)piVar2[7],&param_1);
      iVar3 = piVar2[4];
      iVar7 = piVar2[1];
      iVar1 = piVar2[2];
      iVar6 = piVar2[3];
      iVar4 = FUN_0046e380(*piVar2);
      puVar8 = (undefined4 *)(iVar3 * iVar1 + iVar7 + iVar4 * iVar6);
      iVar6 = piVar2[5] - iVar6;
      iVar3 = piVar2[6] - piVar2[4];
      if (iVar3 != 0) {
        do {
          if (*(int *)(*piVar2 + 4) == 2) {
            if (iVar6 != 0) {
              puVar5 = puVar8;
              iVar7 = iVar6;
              do {
                *(undefined2 *)puVar5 = (*(uint16_t*)((char*)&param_1+0));
                puVar5 = (undefined4 *)((int)puVar5 + 2);
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
          }
          else if ((*(int *)(*piVar2 + 4) == 3) && (iVar6 != 0)) {
            puVar5 = puVar8;
            iVar7 = iVar6;
            do {
              *puVar5 = param_1;
              puVar5 = puVar5 + 1;
              iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
          }
          puVar8 = (undefined4 *)((int)puVar8 + piVar2[2]);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      return 0;
    }
  }
  return 1;
}


/* 0046e640 size=235 */

void __fastcall FUN_0046e640(int param_1)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int local_4;
  
  piVar3 = (int *)(param_1 + 0x970);
  *piVar3 = param_1 + 0x994;
  *(int *)(param_1 + 0x974) = param_1 + 0x995;
  *(int *)(param_1 + 0x978) = param_1 + 0x997;
  *(int *)(param_1 + 0x97c) = param_1 + 0x99b;
  *(int *)(param_1 + 0x980) = param_1 + 0x9a3;
  *(int *)(param_1 + 0x984) = param_1 + 0x9b3;
  *(int *)(param_1 + 0x988) = param_1 + 0x9d3;
  *(int *)(param_1 + 0x98c) = param_1 + 0xa13;
  *(int *)(param_1 + 0x990) = param_1 + 0xa93;
  uVar1 = 0;
  local_4 = param_1 + 0x70;
  do {
    uVar5 = 0;
    uVar4 = (1 << ((byte)uVar1 & 0x1f)) - 1;
    uVar2 = 0;
    do {
      if (uVar4 == 0) {
        *(undefined1 *)(uVar5 + *piVar3) = 0;
      }
      else {
        *(char *)(uVar5 + *piVar3) = (char)(uVar2 / uVar4);
      }
      uVar5 = uVar5 + 1;
      uVar2 = uVar2 + 0xff;
    } while (uVar5 <= uVar4);
    uVar5 = 0;
    uVar2 = 0;
    do {
      *(char *)(local_4 + uVar5) = (char)(uVar2 / 0xff);
      uVar5 = uVar5 + 1;
      uVar2 = uVar2 + uVar4;
    } while (uVar5 < 0x100);
    uVar1 = uVar1 + 1;
    piVar3 = piVar3 + 1;
    local_4 = local_4 + 0x100;
  } while (uVar1 < 9);
  return;
}


/* 0046e730 size=50 */

undefined4 __thiscall FUN_0046e730(void *this,int param_1,undefined1 param_2,undefined4 param_3)

{
  if (*(code **)(&DAT_004db6f4 + *(int *)(param_1 + 4) * 4) == (code *)0x0) {
    return 1;
  }
  (**(code **)(&DAT_004db6f4 + *(int *)(param_1 + 4) * 4))(this,param_1,&param_2,param_3);
  return 0;
}


/* 0046e770 size=50 */

undefined4 __thiscall FUN_0046e770(void *this,int param_1,undefined1 param_2,undefined4 param_3)

{
  if (*(code **)(&DAT_004db714 + *(int *)(param_1 + 4) * 4) == (code *)0x0) {
    return 1;
  }
  (**(code **)(&DAT_004db714 + *(int *)(param_1 + 4) * 4))(this,param_1,&param_2,param_3);
  return 0;
}


/* 0046e7b0 size=59 */

uint __cdecl FUN_0046e7b0(int param_1,int param_2,int param_3)

{
  if (param_1 == 4) {
    return (uint)(param_2 * param_3) >> 1;
  }
  if ((param_1 == 5) || (param_1 == 6)) {
    return param_2 * param_3;
  }
  return *(int *)(&DAT_004db5d4 + param_1 * 4) * param_2 * param_3;
}


/* 0046e7f0 size=2741 */

/* FUN_0046e7f0: lifted from original x86 -> lt_lifted.c */


/* 0046f2b0 size=2704 */

/* FUN_0046f2b0: lifted from original x86 -> lt_lifted.c */


/* 0046fd40 size=320 */

undefined4 __cdecl FUN_0046fd40(int param_1,uint param_2,uint param_3,int param_4)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  void *pvVar6;
  short *psVar7;
  short *psVar8;
  int iVar9;
  short sVar10;
  int iVar11;
  int local_8;
  int local_4;
  
  uVar3 = param_2;
  iVar2 = param_1;
  FUN_0046fe80(param_1);
  if (((param_2 < 2) || (param_3 < 2)) || (65000 < param_2 * param_3)) {
    return 0;
  }
  puVar4 = FUN_00430fb0(param_2 * param_3);
  local_4 = param_3 - 1;
  *(undefined4 **)(param_1 + 0x1b0) = puVar4;
  iVar11 = 2 - (uint)(param_4 != 0);
  iVar5 = iVar11 * local_4 * (param_2 - 1);
  *(int *)(param_1 + 0x1e4) = iVar5;
  *(int *)(param_1 + 0x1e8) = iVar5 * 3;
  pvVar6 = FUN_00430f00(iVar5 * 6);
  *(void **)(param_1 + 0x1b4) = pvVar6;
  if (local_4 != 0) {
    iVar5 = param_2 - 1;
    local_8 = 0;
    param_1 = 0;
    do {
      param_2 = uVar3 - 1;
      if (param_2 != 0) {
        psVar7 = (short *)(*(int *)(iVar2 + 0x1b4) + param_1);
        iVar9 = local_8;
        do {
          sVar1 = (short)iVar9;
          sVar10 = sVar1 + 1 + (short)uVar3;
          *psVar7 = sVar10;
          psVar7[1] = sVar1 + 1;
          psVar7[2] = sVar1;
          psVar8 = psVar7 + 3;
          if (param_4 == 0) {
            *psVar8 = sVar1 + (short)uVar3;
            psVar7[4] = sVar10;
            psVar7[5] = sVar1;
            psVar8 = psVar7 + 6;
          }
          iVar9 = iVar9 + 1;
          param_2 = param_2 - 1;
          psVar7 = psVar8;
        } while (param_2 != 0);
      }
      param_1 = param_1 + iVar11 * iVar5 * 6;
      local_8 = local_8 + uVar3;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
  }
  *(uint *)(iVar2 + 0x1f8) = uVar3;
  *(uint *)(iVar2 + 0x1fc) = param_3;
  return 1;
}


/* 0046fe80 size=65 */

void __cdecl FUN_0046fe80(int param_1)

{
  if (*(undefined **)(param_1 + 0x1b0) != (undefined *)0x0) {
    FUN_00430fe0(*(undefined **)(param_1 + 0x1b0));
    *(undefined4 *)(param_1 + 0x1b0) = 0;
  }
  if (*(undefined **)(param_1 + 0x1b4) != (undefined *)0x0) {
    FUN_00430fe0(*(undefined **)(param_1 + 0x1b4));
    *(undefined4 *)(param_1 + 0x1b4) = 0;
  }
  return;
}


/* 0046ff00 size=40 */

void __cdecl FUN_0046ff00(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  *(undefined4 *)(param_1 + 0x28) = param_2;
  iVar1 = param_1 + 0x44;
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(*(int *)(param_1 + 0x78) + 0x136c);
  iVar2 = param_1 + 0x50;
  *(int *)(param_1 + 0x48) = iVar1;
  *(int *)iVar1 = iVar1;
  *(int *)(param_1 + 0x54) = iVar2;
  *(int *)iVar2 = iVar2;
  return;
}


/* 0046ff30 size=638 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_0046ff30(int param_1,int *param_2,float *param_3,float *param_4,int param_5,int param_6)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  float fVar4;
  undefined4 uVar5;
  
  piVar2 = *(int **)(*(int *)(param_1 + 0x78) + 0x620);
  if ((float)param_2[0x4c] <= *param_3) {
    fVar4 = *param_3 - (float)param_2[0x4c];
  }
  else {
    fVar4 = (float)param_2[0x4c] - *param_3;
  }
  if (fVar4 <= _DAT_004cbeec) {
    if ((float)param_2[0x4d] <= param_3[1]) {
      fVar4 = param_3[1] - (float)param_2[0x4d];
    }
    else {
      fVar4 = (float)param_2[0x4d] - param_3[1];
    }
    if (fVar4 <= _DAT_004cbeec) {
      if ((float)param_2[0x4e] <= param_3[2]) {
        fVar4 = param_3[2] - (float)param_2[0x4e];
      }
      else {
        fVar4 = (float)param_2[0x4e] - param_3[2];
      }
      if ((fVar4 <= _DAT_004cbeec) &&
         (SQRT(param_4[2] * param_4[2] + param_4[1] * param_4[1] + *param_4 * *param_4) <
          _DAT_004cbec0)) {
        param_6 = 1;
      }
    }
  }
  fVar4 = *(float *)(param_1 + 0x28) - (float)param_2[0x4b];
  param_2[0x4b] = *(int *)(param_1 + 0x28);
  param_2[0x4c] = (int)*param_3;
  param_2[0x4d] = (int)param_3[1];
  param_2[0x4e] = (int)param_3[2];
  param_2[0x4f] = (int)*param_4;
  param_2[0x50] = (int)param_4[1];
  param_2[0x51] = (int)param_4[2];
  param_2[0x52] = param_2[0x65];
  param_2[0x53] = param_2[0x66];
  param_2[0x54] = param_2[0x67];
  if (DAT_004e98e8 == 0) {
    if ((param_5 == 0) && (param_6 == 0)) {
      uVar5 = 0;
      goto LAB_0047017c;
    }
  }
  else {
    if (((param_5 == 0) && (param_6 == 0)) && (fVar4 != _DAT_004cb524)) {
      piVar2 = param_2 + 0x55;
      *(int *)(param_2[0x55] + 4) = param_2[0x56];
      *(int *)param_2[0x56] = *piVar2;
      param_2[0x56] = (int)piVar2;
      *piVar2 = (int)piVar2;
      *piVar2 = param_1 + 0x44;
      puVar3 = *(undefined4 **)(param_1 + 0x48);
      param_2[0x56] = (int)puVar3;
      *puVar3 = piVar2;
      *(int **)(*piVar2 + 4) = piVar2;
      param_2[0x4a] = (int)(_DAT_004db734 * fVar4);
      return;
    }
    piVar1 = param_2 + 0x55;
    *(int *)(param_2[0x55] + 4) = param_2[0x56];
    *(int *)param_2[0x56] = *piVar1;
    param_2[0x56] = (int)piVar1;
    *piVar1 = (int)piVar1;
    param_2[0x56] = (int)piVar1;
    *piVar1 = (int)piVar1;
    if (_DAT_004cbec0 < param_4[2] * param_4[2] + param_4[1] * param_4[1] + *param_4 * *param_4) {
      *piVar1 = param_1 + 0x44;
      puVar3 = *(undefined4 **)(param_1 + 0x48);
      param_2[0x56] = (int)puVar3;
      *puVar3 = piVar1;
      *(int **)(*piVar1 + 4) = piVar1;
    }
    uVar5 = 0;
    param_2[0x4a] = 0;
    if ((param_5 == 0) && (param_6 == 0)) goto LAB_0047017c;
  }
  uVar5 = 1;
LAB_0047017c:
  (**(code **)(*piVar2 + 0x44))(param_2,uVar5,param_3);
  FUN_00427310(*(int *)(param_1 + 0x78),param_2,param_3,1);
  return;
}


