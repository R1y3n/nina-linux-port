/* lithtech.exe decompilation - unnamed_0049c000 */
#include "ghidra_types.h"

/* 0049c220 size=118 */

void __thiscall FUN_0049c220(void *this,undefined4 *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  char *pcVar7;
  undefined4 *puVar8;
  char *pcVar9;
  
  if (*(undefined **)((int)this + 0x98) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)((int)this + 0x98));
  }
  puVar6 = param_1;
  puVar8 = this;
  for (iVar3 = 0x29; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  if ((char *)param_1[0x26] != (char *)0x0) {
    uVar4 = 0xffffffff;
    pcVar2 = (char *)param_1[0x26];
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    pcVar2 = (char *)FUN_00430de0(~uVar4);
    uVar4 = 0xffffffff;
    *(char **)((int)this + 0x98) = pcVar2;
    pcVar7 = (char *)param_1[0x26];
    do {
      pcVar9 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar7 = pcVar9 + -uVar4;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar2 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar2 = pcVar2 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar2 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar2 = pcVar2 + 1;
    }
  }
  return;
}


/* 0049c2a0 size=80 */

undefined4 __cdecl FUN_0049c2a0(undefined4 *param_1,undefined4 param_2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)param_1 = 2;
  uVar1 = Ordinal_9(param_2);
  *(undefined2 *)((int)param_1 + 2) = uVar1;
  if (DAT_004e9880 == 0) {
    param_1[1] = 0;
    return 1;
  }
  uVar2 = Ordinal_10(DAT_004e9880);
  param_1[1] = uVar2;
  return 1;
}


/* 0049caa0 size=102 */

undefined4 __fastcall FUN_0049caa0(int param_1)

{
  void *pvVar1;
  int iVar2;
  void *this;
  
  if (*(int *)(param_1 + 100) != 0) {
    Ordinal_3(*(int *)(param_1 + 100));
    *(undefined4 *)(param_1 + 100) = 0;
  }
  pvVar1 = *(void **)(param_1 + 0x54);
  if (pvVar1 != (void *)0x0) {
    iVar2 = *(int *)(param_1 + 0x58) + *(int *)(param_1 + 0x5c);
    if (pvVar1 != (void *)0x0) {
      if (iVar2 != 0) {
        this = pvVar1;
        do {
          FUN_0049f080(this,0);
          this = (void *)((int)this + 0xa4);
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      (**(code **)(DAT_004ecc58 + 8))(pvVar1);
    }
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(undefined4 *)(param_1 + 0x5c) = 0;
  }
  *(undefined4 *)(param_1 + 0x58) = 0;
  return 0;
}


/* 0049cb90 size=52 */

undefined4 __thiscall FUN_0049cb90(void *this,char *param_1,size_t param_2)

{
  *param_1 = '\0';
  if (*(char **)((int)this + 0x98) == (char *)0x0) {
    return 0;
  }
  _strncpy(param_1,*(char **)((int)this + 0x98),param_2);
  param_1[param_2 - 1] = '\0';
  return 0;
}


/* 0049cc60 size=226 */

void __thiscall FUN_0049cc60(void *this,undefined *param_1,undefined4 param_2)

{
  int iVar1;
  
  if (param_1 != (undefined *)0x0) {
    if (DAT_004e9898 != 0) {
      Ordinal_15(CONCAT22((short)((uint)DAT_004e9898 >> 0x10),*(undefined2 *)(param_1 + 0xbe)));
      FUN_00436670((byte *)s_TCPDriver__Disconnect___d__on__d_004ddaa8,param_2);
    }
    netmgr_466010(*(void **)((int)this + 0x48),(int)param_1);
    FUN_0049bda0(this,(int)param_1);
    *(undefined4 *)(*(int *)(param_1 + 0xcc) + 4) = *(undefined4 *)(param_1 + 0xd0);
    **(undefined4 **)(param_1 + 0xd0) = *(undefined4 *)(param_1 + 0xcc);
    if ((undefined4 *)(param_1 + 0xcc) == *(undefined4 **)((int)this + 0xa0)) {
      *(undefined4 *)((int)this + 0xa0) = (*(undefined4 **)((int)this + 0xa0))[1];
    }
    iVar1 = *(int *)((int)this + 0x9c) + -1;
    *(int *)((int)this + 0x9c) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)((int)this + 0xa0) = 0;
    }
    if (*(int *)(param_1 + 0xd8) != 0) {
      Ordinal_3(*(int *)(param_1 + 0xd8));
    }
    FUN_004645f0((int)param_1);
    FUN_00430df0(param_1);
  }
  return;
}


/* 0049cea0 size=1431 */

void __thiscall FUN_0049cea0(void *this,int *param_1,int *param_2)

{
  ushort uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 *puVar4;
  char *pcVar5;
  int *piVar6;
  undefined *puVar7;
  undefined2 extraout_var;
  int *piVar8;
  int *piVar9;
  int *piVar10;
  bool bVar11;
  bool bVar12;
  undefined4 uVar13;
  int *piStack_14;
  int local_10 [4];
  
  piVar9 = param_1;
  *(undefined2 *)(param_1 + 0xe) = 1;
  uVar2 = FUN_004680f0((int)param_1);
  piVar6 = param_2;
  param_1 = (int *)CONCAT31((*(uint32_t*)((char*)&param_1+1)),uVar2);
  if ((*(byte *)(piVar9 + 0x10) & 2) != 0) {
    return;
  }
  if (*(int *)((int)this + 0x7c) == 0) {
LAB_0049d345:
    if ((char)param_1 != '\0') {
      return;
    }
    puVar7 = (undefined *)udpdriver_49bde0(this,(int)piVar6);
    if (puVar7 == (undefined *)0x0) {
      return;
    }
    if (DAT_004e9898 != 0) {
      Ordinal_15(*(undefined2 *)((int)piVar6 + 2));
      FUN_00436670((byte *)s_Got_TCPSUB_DISCONNECT_from__d__d_004ddb20,(uint)*(byte *)(piVar6 + 1));
    }
    piVar9 = *(int **)(*(int *)((int)this + 0x48) + 0xb4);
    if (piVar9 != (int *)0x0) {
      (**(code **)(*piVar9 + 0x10))(4,&DAT_004e4424);
    }
    netmgr_466010(*(void **)((int)this + 0x48),(int)puVar7);
    *(undefined4 *)(*(int *)(puVar7 + 0xcc) + 4) = *(undefined4 *)(puVar7 + 0xd0);
    **(undefined4 **)(puVar7 + 0xd0) = *(undefined4 *)(puVar7 + 0xcc);
    if ((undefined4 *)(puVar7 + 0xcc) == *(undefined4 **)((int)this + 0xa0)) {
      *(undefined4 *)((int)this + 0xa0) = (*(undefined4 **)((int)this + 0xa0))[1];
    }
    iVar3 = *(int *)((int)this + 0x9c) + -1;
    *(int *)((int)this + 0x9c) = iVar3;
    if (iVar3 == 0) {
      *(undefined4 *)((int)this + 0xa0) = 0;
    }
    if (*(int *)(puVar7 + 0xd8) != 0) {
      Ordinal_3(*(int *)(puVar7 + 0xd8));
    }
    FUN_004645f0((int)puVar7);
    FUN_00430df0(puVar7);
    return;
  }
  iVar3 = udpdriver_49d440((int)this,(int)param_2);
  if (iVar3 != 0) {
    return;
  }
  if ((char)param_1 == '\x01') {
    FUN_0046b3c0(piVar9,local_10,0x10);
    piVar6 = param_2;
    iVar3 = 4;
    bVar11 = true;
    piVar8 = local_10;
    piVar10 = (int *)(*(int *)((int)this + 0x48) + 0xf0);
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar11 = *piVar8 == *piVar10;
      piVar8 = piVar8 + 1;
      piVar10 = piVar10 + 1;
    } while (bVar11);
    if (!bVar11) {
      return;
    }
    if (DAT_004e9898 != 0) {
      Ordinal_15(*(undefined2 *)((int)param_2 + 2));
      FUN_00436670((byte *)s_IP__Received_query_from__d__d__d_004ddb8c,(uint)*(byte *)(piVar6 + 1));
    }
    uVar2 = FUN_004680f0((int)piVar9);
    param_1 = (int *)CONCAT31((*(uint32_t*)((char*)&param_1+1)),uVar2);
    puVar4 = FUN_0046b170(&param_2,0x44c,0x44c);
    piVar9 = (int *)*puVar4;
    if (piVar9 != (int *)0x0) {
      (**(code **)(*piVar9 + 4))();
    }
    if (param_2 != (int *)0x0) {
      (**(code **)(*param_2 + 8))();
    }
    *(undefined1 *)piVar9[0x15] = 0;
    FUN_004183a0(piVar9,2);
    pcVar5 = *(char **)((int)this + 0x98);
    if (pcVar5 == (char *)0x0) {
      pcVar5 = &DAT_004e4424;
    }
    FUN_0046b440(piVar9,pcVar5);
    FUN_004183a0(piVar9,(char)param_1);
    iVar3 = piVar9[0x15];
    uVar13 = *(undefined4 *)((int)this + 0x90);
    uVar1 = *(ushort *)(piVar9 + 0xd);
  }
  else {
    if ((char)param_1 != '\x03') goto LAB_0049d345;
    if (DAT_004e9898 != 0) {
      Ordinal_15(CONCAT22(extraout_var,*(undefined2 *)((int)piVar6 + 2)));
      FUN_00436670((byte *)s_IP__Received_conn_request_from___004ddb4c,(uint)*(byte *)(piVar6 + 1));
    }
    FUN_004680f0((int)piVar9);
    FUN_0046b3c0(piVar9,local_10,0x10);
    if ((*(byte *)(piVar9 + 0x10) & 2) != 0) {
      return;
    }
    bVar11 = false;
    iVar3 = 4;
    bVar12 = true;
    piVar9 = (int *)(*(int *)((int)this + 0x48) + 0xf0);
    piVar6 = local_10;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar12 = *piVar9 == *piVar6;
      piVar9 = piVar9 + 1;
      piVar6 = piVar6 + 1;
    } while (bVar12);
    if (bVar12) {
      piVar9 = (int *)((int)this + 0x9c);
      if (*(uint *)((int)this + 0x9c) < *(uint *)((int)this + 0x94)) {
        piVar6 = (int *)FUN_00430de0(0xe0);
        if (piVar6 == (int *)0x0) {
          piVar6 = (int *)0x0;
        }
        else {
          FUN_00464580(piVar6);
          piVar6[0x36] = 0;
        }
        piVar6[0x2f] = *param_2;
        piVar6[0x30] = param_2[1];
        piVar6[0x31] = param_2[2];
        iVar3 = param_2[3];
        piVar6[0xc] = (int)this;
        piVar6[0x32] = iVar3;
        piVar6[0x37] = 0;
        iVar3 = netmgr_465e20(*(void **)((int)this + 0x48),(int)piVar6);
        if (iVar3 != 0) {
          piVar8 = piVar6 + 0x33;
          if (*(int **)((int)this + 0xa0) == (int *)0x0) {
            piVar6[0x34] = (int)piVar8;
            *piVar8 = (int)piVar8;
            piVar6[0x35] = (int)piVar6;
            *(int **)((int)this + 0xa0) = piVar8;
            *piVar9 = *piVar9 + 1;
          }
          else {
            FUN_0049ef80(piVar9,*(int **)((int)this + 0xa0),(int)piVar6,piVar8);
          }
          puVar4 = FUN_0046b170(&param_1,0x44c,0x44c);
          piVar9 = (int *)*puVar4;
          if (piVar9 != (int *)0x0) {
            (**(code **)(*piVar9 + 4))();
          }
          if (param_1 != (int *)0x0) {
            (**(code **)(*param_1 + 8))();
          }
          *(undefined1 *)piVar9[0x15] = 0;
          FUN_004183a0(piVar9,5);
          iVar3 = 5;
          do {
            FUN_0049bd70(*(undefined4 *)((int)this + 0x90),piVar9[0x15],
                         (uint)*(ushort *)(piVar9 + 0xd),param_2);
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          piVar6[0x37] = 1;
          FUN_00465a40(*(void **)((int)this + 0x48),piVar6);
          goto LAB_0049cfef;
        }
        if (piVar6 != (int *)0x0) {
          if (piVar6[0x36] != 0) {
            Ordinal_3(piVar6[0x36]);
          }
          FUN_004645f0((int)piVar6);
          FUN_00430df0((undefined *)piVar6);
        }
      }
    }
    else {
      bVar11 = true;
    }
    puVar4 = FUN_0046b170(&piStack_14,0x44c,0x44c);
    piVar9 = (int *)*puVar4;
    if (piVar9 != (int *)0x0) {
      (**(code **)(*piVar9 + 4))();
    }
    if (piStack_14 != (int *)0x0) {
      (**(code **)(*piStack_14 + 8))();
    }
    *(undefined1 *)piVar9[0x15] = 0;
    if (bVar11) {
      if (*(ushort *)(piVar9 + 0xe) + 1 < (uint)*(ushort *)((int)piVar9 + 0x36)) {
        if ((uint)piVar9[0x16] <= *(ushort *)(piVar9 + 0xd) + 1) {
          do {
            param_1 = (int *)((uint)param_1 & 0xffffff00);
            FUN_00414b10(piVar9 + 0x14,(undefined1 *)piVar9[0x16],(undefined1 *)&param_1,
                         &DAT_004ecc58);
          } while ((uint)piVar9[0x16] <= *(ushort *)(piVar9 + 0xd) + 1);
        }
        *(undefined1 *)((uint)*(ushort *)(piVar9 + 0xe) + piVar9[0x15]) = 7;
        *(short *)(piVar9 + 0xe) = (short)piVar9[0xe] + 1;
        *(short *)(piVar9 + 0xd) = (short)piVar9[0xd] + 1;
      }
      else {
        FUN_004356e0();
joined_r0x0049d301:
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
        }
        piVar9[0x10] = piVar9[0x10] | 4;
      }
    }
    else {
      if ((uint)*(ushort *)((int)piVar9 + 0x36) <= *(ushort *)(piVar9 + 0xe) + 1) {
        FUN_004356e0();
        goto joined_r0x0049d301;
      }
      if ((uint)piVar9[0x16] <= *(ushort *)(piVar9 + 0xd) + 1) {
        do {
          param_1 = (int *)((uint)param_1 & 0xffffff00);
          FUN_00414b10(piVar9 + 0x14,(undefined1 *)piVar9[0x16],(undefined1 *)&param_1,&DAT_004ecc58
                      );
        } while ((uint)piVar9[0x16] <= *(ushort *)(piVar9 + 0xd) + 1);
      }
      *(undefined1 *)((uint)*(ushort *)(piVar9 + 0xe) + piVar9[0x15]) = 6;
      *(short *)(piVar9 + 0xe) = (short)piVar9[0xe] + 1;
      *(short *)(piVar9 + 0xd) = (short)piVar9[0xd] + 1;
    }
    iVar3 = piVar9[0x15];
    uVar1 = *(ushort *)(piVar9 + 0xd);
    uVar13 = *(undefined4 *)((int)this + 0x90);
    piVar6 = param_2;
  }
  FUN_0049bd70(uVar13,iVar3,(uint)uVar1,piVar6);
LAB_0049cfef:
  if (piVar9 != (int *)0x0) {
    (**(code **)(*piVar9 + 8))();
  }
  return;
}


/* 0049e030 size=27 */

undefined4 * FUN_0049e030(void)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00430de0(0xb0);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  puVar1 = FUN_0049baa0(puVar1);
  return puVar1;
}


/* 0049e910 size=274 */

undefined4 __thiscall FUN_0049e910(void *this,int param_1,int *param_2)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  void *this_00;
  undefined4 *puVar6;
  
  iVar5 = param_1;
  if ((param_1 != *(int *)((int)this + 8)) || (param_1 == 0)) {
    pvVar1 = *(void **)((int)this + 4);
    if (pvVar1 != (void *)0x0) {
      param_1 = *(int *)((int)this + 0xc) + *(int *)((int)this + 8);
      if (pvVar1 == (void *)0x0) {
        *(undefined4 *)((int)this + 4) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
      }
      else {
        if (param_1 != 0) {
          this_00 = pvVar1;
          do {
            FUN_0049f080(this_00,0);
            this_00 = (void *)((int)this_00 + 0xa4);
            param_1 = param_1 + -1;
          } while (param_1 != 0);
        }
        (**(code **)(*param_2 + 8))(pvVar1);
        *(undefined4 *)((int)this + 4) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
      }
    }
    *(int *)((int)this + 8) = iVar5;
    if (iVar5 != 0) {
      iVar5 = iVar5 + *(int *)((int)this + 0x10);
      iVar2 = (**(code **)(*param_2 + 4))(iVar5 * 0xa4);
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else if (iVar5 != 0) {
        puVar4 = (undefined4 *)(iVar2 + 0x9c);
        do {
          if (puVar4 != (undefined4 *)0x9c) {
            puVar4[-1] = 0;
            *puVar4 = 0;
            puVar4[-7] = 0;
            puVar6 = puVar4 + -0x27;
            for (iVar3 = 0x20; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar6 = 0;
              puVar6 = puVar6 + 1;
            }
            puVar4[1] = 0;
            puVar4[-6] = 0;
          }
          puVar4 = puVar4 + 0x29;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      *(int *)((int)this + 4) = iVar2;
      if (iVar2 == 0) {
        *(undefined4 *)((int)this + 8) = 0;
        *(undefined4 *)((int)this + 0xc) = 0;
        return 0;
      }
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    }
  }
  return 1;
}


/* 0049ea30 size=513 */

undefined4 __thiscall FUN_0049ea30(void *this,uint param_1,int *param_2,int *param_3)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *unaff_EBP;
  undefined4 *puVar8;
  int iVar9;
  undefined4 *puVar10;
  char *pcVar11;
  int iVar12;
  undefined4 *puVar13;
  char *pcVar14;
  uint unaff_retaddr;
  void *pvStack_c;
  
  uVar6 = *(uint *)((int)this + 8);
  if (param_1 < uVar6) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = *(int *)((int)this + 0xc) + (uVar6 - param_1);
    return 1;
  }
  if ((uVar6 < param_1) && (uVar5 = *(int *)((int)this + 0xc) + uVar6, param_1 <= uVar5)) {
    *(uint *)((int)this + 8) = param_1;
    *(uint *)((int)this + 0xc) = uVar5 - param_1;
    return 1;
  }
  if (param_1 == uVar6) {
    return 1;
  }
  iVar9 = param_1 + *(int *)((int)this + 0x10);
  puVar2 = (undefined4 *)(**(code **)(*param_3 + 4))(iVar9 * 0xa4);
  puVar8 = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  for (; iVar9 != 0; iVar9 = iVar9 + -1) {
    if (puVar8 != (undefined4 *)0x0) {
      FUN_0049ec40(puVar8);
    }
    puVar8 = puVar8 + 0x29;
  }
  uVar6 = *(uint *)((int)this + 8);
  if (param_1 < *(uint *)((int)this + 8)) {
    uVar6 = param_1;
  }
  if (param_1 == 0) {
    if (uVar6 != 0) {
      puVar8 = puVar2 + 0x26;
      param_1 = uVar6;
      do {
        puVar7 = (undefined4 *)((int)puVar8 + *(int *)((int)pvStack_c + 4) + (-0x98 - (int)puVar2));
        if ((undefined *)*puVar8 != (undefined *)0x0) {
          FUN_00430df0((undefined *)*puVar8);
        }
        puVar10 = puVar7;
        puVar13 = puVar8 + -0x26;
        for (iVar9 = 0x29; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar13 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar13 = puVar13 + 1;
        }
        if ((char *)puVar7[0x26] != (char *)0x0) {
          uVar6 = 0xffffffff;
          pcVar3 = (char *)puVar7[0x26];
          do {
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          pcVar3 = (char *)FUN_00430de0(~uVar6);
          uVar6 = 0xffffffff;
          *puVar8 = pcVar3;
          pcVar11 = (char *)puVar7[0x26];
          do {
            pcVar14 = pcVar11;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pcVar14 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar14;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          pcVar11 = pcVar14 + -uVar6;
          for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined4 *)pcVar3 = *(undefined4 *)pcVar11;
            pcVar11 = pcVar11 + 4;
            pcVar3 = pcVar3 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pcVar3 = *pcVar11;
            pcVar11 = pcVar11 + 1;
            pcVar3 = pcVar3 + 1;
          }
        }
        puVar8 = puVar8 + 0x29;
        param_1 = param_1 - 1;
      } while (param_1 != 0);
      param_1 = unaff_retaddr;
      this = pvStack_c;
    }
  }
  else {
    puVar8 = *(undefined4 **)((int)this + 4);
    puVar7 = puVar2;
    for (uVar6 = uVar6 * 0xa4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar7 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar7 = puVar7 + 1;
    }
    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar8;
      puVar8 = (undefined4 *)((int)puVar8 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
  }
  iVar9 = *(int *)((int)this + 4);
  if (iVar9 != 0) {
    iVar4 = *(int *)((int)this + 0xc) + *(int *)((int)this + 8);
    if (iVar9 != 0) {
      if (iVar4 != 0) {
        iVar12 = iVar9;
        do {
          FUN_0049ec80(iVar12);
          iVar12 = iVar12 + 0xa4;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      (**(code **)(*param_2 + 8))(iVar9);
      puVar2 = unaff_EBP;
    }
    *(undefined4 *)((int)this + 4) = 0;
  }
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 **)((int)this + 4) = puVar2;
  *(uint *)((int)this + 8) = param_1;
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
  return 1;
}


/* 0049ec40 size=52 */

undefined4 * __fastcall FUN_0049ec40(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  param_1[0x26] = 0;
  param_1[0x27] = 0;
  param_1[0x20] = 0;
  puVar2 = param_1;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x28] = 0;
  param_1[0x21] = 0;
  return param_1;
}


/* 0049ec80 size=18 */

void __fastcall FUN_0049ec80(int param_1)

{
  if (*(undefined **)(param_1 + 0x98) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)(param_1 + 0x98));
  }
  return;
}


/* 0049eca0 size=634 */

undefined4 __thiscall FUN_0049eca0(void *this,uint param_1,undefined4 *param_2,int *param_3)

{
  undefined4 *puVar1;
  char cVar2;
  undefined *puVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  void *pvVar8;
  void *this_00;
  undefined4 *puVar9;
  char *pcVar10;
  int iVar11;
  undefined4 *puVar12;
  char *pcVar13;
  uint local_4;
  
  local_4 = *(uint *)((int)this + 8);
  if (local_4 < param_1) {
    return 0;
  }
  if (*(int *)((int)this + 0xc) == 0) {
    iVar4 = FUN_0049f010(param_3,0,*(int *)((int)this + 0x10) + 1 + local_4);
    if (iVar4 == 0) {
      return 0;
    }
    if (param_1 != 0) {
      iVar11 = 0;
      uVar7 = param_1;
      do {
        FUN_0049c220((void *)(iVar11 + iVar4),(undefined4 *)(*(int *)((int)this + 4) + iVar11));
        iVar11 = iVar11 + 0xa4;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
    }
    local_4 = param_1;
    if (param_1 < *(uint *)((int)this + 8)) {
      iVar11 = param_1 * 0xa4;
      pvVar8 = (void *)(iVar4 + param_1 * 0xa4 + 0xa4);
      do {
        FUN_0049c220(pvVar8,(undefined4 *)(*(int *)((int)this + 4) + iVar11));
        local_4 = local_4 + 1;
        iVar11 = iVar11 + 0xa4;
        pvVar8 = (void *)((int)pvVar8 + 0xa4);
      } while (local_4 < *(uint *)((int)this + 8));
    }
    FUN_0049c220((void *)(iVar4 + param_1 * 0xa4),param_2);
    pvVar8 = *(void **)((int)this + 4);
    if (pvVar8 != (void *)0x0) {
      iVar11 = *(int *)((int)this + 0xc) + *(int *)((int)this + 8);
      if (pvVar8 != (void *)0x0) {
        if (iVar11 != 0) {
          this_00 = pvVar8;
          do {
            FUN_0049f080(this_00,0);
            this_00 = (void *)((int)this_00 + 0xa4);
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
        }
        (**(code **)(*param_3 + 8))(pvVar8);
      }
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    *(undefined4 *)((int)this + 0xc) = *(undefined4 *)((int)this + 0x10);
    *(int *)((int)this + 4) = iVar4;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    return 1;
  }
  if (param_1 < local_4) {
    param_3 = (int *)(local_4 * 0xa4);
    local_4 = local_4 - param_1;
    do {
      puVar1 = (undefined4 *)(*(int *)((int)this + 4) + (int)param_3);
      puVar3 = *(undefined **)(*(int *)((int)this + 4) + 0x98 + (int)param_3);
      if (puVar3 != (undefined *)0x0) {
        FUN_00430df0(puVar3);
      }
      puVar9 = puVar1 + -0x29;
      puVar12 = puVar1;
      for (iVar4 = 0x29; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar12 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar12 = puVar12 + 1;
      }
      if ((char *)puVar1[-3] != (char *)0x0) {
        uVar7 = 0xffffffff;
        pcVar5 = (char *)puVar1[-3];
        do {
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          cVar2 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar2 != '\0');
        pcVar5 = (char *)FUN_00430de0(~uVar7);
        uVar7 = 0xffffffff;
        puVar1[0x26] = pcVar5;
        pcVar10 = (char *)puVar1[-3];
        do {
          pcVar13 = pcVar10;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar13 = pcVar10 + 1;
          cVar2 = *pcVar10;
          pcVar10 = pcVar13;
        } while (cVar2 != '\0');
        uVar7 = ~uVar7;
        pcVar10 = pcVar13 + -uVar7;
        for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar5 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar5 = pcVar5 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar5 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar5 = pcVar5 + 1;
        }
      }
      param_3 = param_3 + -0x29;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
  }
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
  puVar1 = (undefined4 *)(*(int *)((int)this + 4) + param_1 * 0xa4);
  puVar3 = *(undefined **)(*(int *)((int)this + 4) + 0x98 + param_1 * 0xa4);
  if (puVar3 != (undefined *)0x0) {
    FUN_00430df0(puVar3);
  }
  puVar9 = param_2;
  puVar12 = puVar1;
  for (iVar4 = 0x29; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar12 = puVar12 + 1;
  }
  if ((char *)param_2[0x26] != (char *)0x0) {
    uVar7 = 0xffffffff;
    pcVar5 = (char *)param_2[0x26];
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar2 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar2 != '\0');
    pcVar5 = (char *)FUN_00430de0(~uVar7);
    puVar1[0x26] = pcVar5;
    uVar7 = 0xffffffff;
    pcVar10 = (char *)param_2[0x26];
    do {
      pcVar13 = pcVar10;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar13 = pcVar10 + 1;
      cVar2 = *pcVar10;
      pcVar10 = pcVar13;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    pcVar10 = pcVar13 + -uVar7;
    for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar5 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar5 = pcVar5 + 1;
    }
  }
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
  return 1;
}


/* 0049ef20 size=90 */

void __thiscall FUN_0049ef20(void *this,int *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 == 0) {
    *(undefined4 *)((int)this + 0xc) = 0;
    return;
  }
  if (param_2 != 0) {
    puVar2 = (undefined4 *)(iVar1 + 0x98);
    do {
      if ((undefined *)*puVar2 != (undefined *)0x0) {
        FUN_00430df0((undefined *)*puVar2);
      }
      puVar2 = puVar2 + 0x29;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  (**(code **)(*param_1 + 8))(iVar1);
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  return;
}


/* 0049ef80 size=52 */

void __thiscall FUN_0049ef80(void *this,int *param_1,int param_2,int *param_3)

{
  *(int **)(*param_1 + 4) = param_3;
  *param_3 = *param_1;
  param_3[1] = (int)param_1;
  *param_1 = (int)param_3;
  param_3[2] = param_2;
  *(int *)this = *(int *)this + 1;
  if (param_3[1] == *(int *)((int)this + 4)) {
    *(int **)((int)this + 4) = param_3;
  }
  return;
}


/* 0049efc0 size=65 */

void __cdecl FUN_0049efc0(int *param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  
  if (param_2 != 0) {
    if (param_3 != 0) {
      puVar1 = (undefined4 *)(param_2 + 0x98);
      do {
        if ((undefined *)*puVar1 != (undefined *)0x0) {
          FUN_00430df0((undefined *)*puVar1);
        }
        puVar1 = puVar1 + 0x29;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
    }
    (**(code **)(*param_1 + 8))(param_2);
  }
  return;
}


/* 0049f010 size=106 */

int __cdecl FUN_0049f010(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = (**(code **)(*param_1 + 4))(param_3 * 0xa4);
  if (iVar1 == 0) {
    return 0;
  }
  if (param_3 != 0) {
    puVar3 = (undefined4 *)(iVar1 + 0x9c);
    do {
      if (puVar3 != (undefined4 *)0x9c) {
        puVar3[-1] = 0;
        *puVar3 = 0;
        puVar3[-7] = 0;
        puVar4 = puVar3 + -0x27;
        for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        puVar3[1] = 0;
        puVar3[-6] = 0;
      }
      puVar3 = puVar3 + 0x29;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return iVar1;
}


/* 0049f080 size=44 */

undefined * __thiscall FUN_0049f080(void *this,byte param_1)

{
  if (*(undefined **)((int)this + 0x98) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)((int)this + 0x98));
  }
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0049f0b0 size=18 */

void __thiscall FUN_0049f0b0(void *this,undefined4 param_1)

{
  *(undefined ***)this = &PTR_LAB_004cda94;
  *(undefined4 *)((int)this + 4) = param_1;
  return;
}


/* 0049f3d0 size=135 */

undefined4 FUN_0049f3d0(int param_1)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = FUN_0049f460(param_1);
  if (iVar2 == 0) {
    FUN_004356e0();
    if (1 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                   PTR_s_LTTexMod_ReleaseTextureHandle_004dddf4);
    }
    return 0x3c;
  }
  uVar1 = *(ushort *)(param_1 + 0x32);
  uVar1 = (uVar1 ^ (uVar1 & 0x7fff) - 1) & 0x7fff ^ uVar1;
  *(ushort *)(param_1 + 0x32) = uVar1;
  if (((uVar1 & 0x7fff) == 0) && (*(undefined4 **)(param_1 + 8) != (undefined4 *)0x0)) {
    FUN_00436de0(*(undefined4 **)(param_1 + 8));
  }
  return 0;
}


/* 0049f460 size=45 */

undefined4 __cdecl FUN_0049f460(int param_1)

{
  int iVar1;
  
  if ((((param_1 == 0) || ((*(ushort *)(param_1 + 0x32) & 0x7fff) == 0)) ||
      (iVar1 = *(int *)(param_1 + 8), iVar1 == 0)) ||
     ((*(short *)(iVar1 + 0x14) != 1 || ((*(byte *)(iVar1 + 0x18) & 0x40) == 0)))) {
    return 0;
  }
  return 1;
}


/* 0049f4f0 size=124 */

undefined4 FUN_0049f4f0(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  *param_2 = 0;
  param_2[1] = 0;
  iVar1 = FUN_0049f460(param_1);
  if (iVar1 != 0) {
    iVar1 = *(int *)(param_1 + 8);
    *param_2 = *(undefined4 *)(iVar1 + 0xcc);
    param_2[1] = *(undefined4 *)(iVar1 + 0xd0);
    return 0;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_LTTexMod_GetTextureInfo_004dddfc
                );
  }
  return 0x3c;
}


/* 0049f710 size=95 */

undefined4 FUN_0049f710(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0049f460(param_1);
  if (iVar1 != 0) {
    FUN_00471750(param_1,1);
    return 0;
  }
  FUN_004356e0();
  if (1 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,PTR_s_LTTexMod_UnlockTexture_004dde04)
    ;
  }
  return 0x3c;
}


/* 0049f7b0 size=23 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0049f7b0(void)

{
  _DAT_004ec3f0 = &PTR_LAB_004cdaac;
  DAT_004ec3f4 = 0;
  DAT_004ec3f8 = 0;
  return;
}


/* 0049f7d0 size=12 */

void FUN_0049f7d0(void)

{
  FUN_004b9cf5(&LAB_0049f7e0);
  return;
}


/* 0049f800 size=211 */

void __cdecl FUN_0049f800(int param_1)

{
  HGDIOBJ h;
  
  *(undefined1 **)(param_1 + 0x140) = &LAB_0049f8e0;
  *(undefined1 **)(param_1 + 0x144) = &LAB_0049f990;
  *(undefined1 **)(param_1 + 0x148) = &LAB_0049fa00;
  *(undefined1 **)(param_1 + 0x14c) = &LAB_0049fa50;
  *(undefined1 **)(param_1 + 400) = &LAB_0049faa0;
  *(undefined1 **)(param_1 + 0x194) = &LAB_0049fb30;
  *(undefined1 **)(param_1 + 0x174) = &LAB_004a02c0;
  DAT_004ec3fc = CreateCompatibleDC((HDC)0x0);
  h = GetStockObject(4);
  DAT_004ec408 = SelectObject(DAT_004ec3fc,h);
  SetTextColor(DAT_004ec3fc,0xffffff);
  SetBkMode(DAT_004ec3fc,2);
  SetTextColor(DAT_004ec3fc,0xffffff);
  SetBkColor(DAT_004ec3fc,0);
  DAT_004ec400 = 0;
  DAT_004ec404 = 0;
  DAT_004ec410 = 0;
  DAT_004ec40c = 0;
  DAT_004ec418 = 0;
  return;
}


/* 0049f9a0 size=82 */

/* FUN_0049f9a0: lifted from original x86 -> lt_lifted.c */


/* 0049fbd0 size=336 */

void __cdecl
FUN_0049fbd0(undefined *param_1,int param_2,int param_3,int *param_4,uint param_5,uint param_6,
            uint *param_7)

{
  undefined2 uVar1;
  HGDIOBJ h;
  undefined2 extraout_var;
  int c;
  LPCSTR lpString;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10 [4];
  
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_10[3] = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  if (((param_3 != 0) && (param_2 != 0)) && (param_1 != (undefined *)0x0)) {
    FUN_0049fd20(param_7);
    if ((DAT_004ec400 != 0) && (DAT_004ec418 != 0)) {
      h = SelectObject(DAT_004ec3fc,*(HGDIOBJ *)(param_2 + 8));
      uVar1 = FUN_0049b8c0(param_3);
      c = CONCAT22(extraout_var,uVar1);
      Rectangle(DAT_004ec3fc,0,0,*param_7,param_7[1]);
      lpString = (LPCSTR)FUN_0049b8e0(param_3,(uint *)0x0);
      TextOutA(DAT_004ec3fc,0,0,lpString,c);
      SelectObject(DAT_004ec3fc,h);
      if (param_4 == (int *)0x0) {
        local_1c = 0;
        local_20 = 0;
        local_18 = *(int *)(param_1 + 0x10);
        local_14 = *(int *)(param_1 + 0x14);
      }
      else {
        local_20 = *param_4;
        local_1c = param_4[1];
        local_18 = param_4[2];
        local_14 = param_4[3];
      }
      local_10[2] = *param_7;
      local_10[3] = param_7[1];
      local_10[1] = 0;
      local_10[0] = 0;
      FUN_0049fe10(param_1,local_10,&local_20,param_5,param_6);
    }
  }
  return;
}


/* 0049fd20 size=236 */

void __cdecl FUN_0049fd20(uint *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  DWORD *pDVar4;
  DWORD local_28;
  uint local_24;
  int local_20;
  WORD local_1c;
  WORD local_1a;
  DWORD local_18;
  
  if (((int)DAT_004ec40c < (int)*param_1) || ((int)DAT_004ec410 < (int)param_1[1])) {
    if (DAT_004ec404 != (HGDIOBJ)0x0) {
      SelectObject(DAT_004ec3fc,DAT_004ec404);
    }
    if (DAT_004ec400 != (HBITMAP)0x0) {
      DeleteObject(DAT_004ec400);
    }
    uVar3 = *param_1;
    uVar1 = uVar3 & 0x8000001f;
    if ((int)uVar1 < 0) {
      uVar1 = (uVar1 - 1 | 0xffffffe0) + 1;
    }
    if (uVar1 != 0) {
      uVar3 = uVar3 + (0x20 - uVar1);
    }
    uVar1 = param_1[1];
    pDVar4 = &local_28;
    for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pDVar4 = 0;
      pDVar4 = pDVar4 + 1;
    }
    local_18 = 0;
    local_28 = 0x28;
    local_20 = -uVar1;
    local_1a = 0x10;
    local_1c = 1;
    local_24 = uVar3;
    DAT_004ec400 = CreateDIBSection(DAT_004ec3fc,(BITMAPINFO *)&local_28,0,(void **)&DAT_004ec418,
                                    (HANDLE)0x0,0);
    DAT_004ec404 = SelectObject(DAT_004ec3fc,DAT_004ec400);
    DAT_004ec410 = param_1[1];
    DAT_004ec414 = uVar3 * 2;
    DAT_004ec40c = uVar3;
  }
  return;
}


/* 0049fe10 size=1199 */

void __cdecl FUN_0049fe10(undefined *param_1,int *param_2,int *param_3,uint param_4,uint param_5)

{
  uint uVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  void *pvVar4;
  short *psVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined2 uVar9;
  int *piVar10;
  undefined4 *puVar11;
  undefined *puVar12;
  uint uVar13;
  uint uVar14;
  int **ppiVar15;
  int *piStack_34;
  int local_30;
  int *piStack_2c;
  int *piStack_28;
  int *piStack_24;
  uint local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  if (((DAT_004ec418 != 0) &&
      (bVar2 = FUN_00443ae0(DAT_004ec40c,DAT_004ec410,*param_2,param_2[1],param_2[2],param_2[3],
                            *(int *)(param_1 + 0x10),*(int *)(param_1 + 0x14),*param_3,param_3[1],
                            (int *)&local_20,&local_10), CONCAT31(extraout_var,bVar2) != 0)) &&
     (DAT_004e5124 != 0)) {
    param_3 = (int *)0x0;
    if (param_1 == &DAT_004e4fa0) {
      iVar3 = (**(code **)(DAT_004e5124 + 0xec))(0,0,DAT_004e4fb0,DAT_004e4fb4,&local_30,&param_3);
      if (iVar3 == 0) {
        return;
      }
    }
    else {
      param_3 = *(int **)(param_1 + 0x18);
      local_30 = (**(code **)(DAT_004e5124 + 0xdc))(*(undefined4 *)(param_1 + 0xc));
      if (local_30 == 0) {
        return;
      }
      if (param_1 != (undefined *)0x0) {
        *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 4;
      }
    }
    uVar1 = param_4;
    if (local_30 != 0) {
      puVar11 = (undefined4 *)(local_c * (int)param_3 + local_30 + DAT_004e5114 * local_10);
      ppiVar15 = &piStack_34;
      puVar12 = &DAT_004e50d8;
      iVar3 = DAT_004ec414 * local_1c + DAT_004ec418;
      uVar13 = param_4;
      pvVar4 = (void *)FUN_0040c9e0();
      FUN_0046e730(pvVar4,(int)puVar12,(char)uVar13,ppiVar15);
      uVar13 = param_5;
      ppiVar15 = &param_2;
      puVar12 = &DAT_004e50d8;
      uVar14 = param_5;
      pvVar4 = (void *)FUN_0040c9e0();
      FUN_0046e730(pvVar4,(int)puVar12,(char)uVar14,ppiVar15);
      if (((uVar1 & 0x80000000) == 0) || ((uVar13 & 0x80000000) == 0)) {
        if ((uVar1 & 0x80000000) == 0) {
          if ((uVar13 & 0x80000000) == 0) {
            if (DAT_004e50dc == 2) {
              piStack_28 = param_2;
              piStack_2c = piStack_34;
              piStack_24 = param_3;
              param_5 = local_20;
              if (local_14 - local_1c != 0) {
                param_4 = local_14 - local_1c;
                do {
                  if (local_18 - local_20 != 0) {
                    puVar7 = puVar11;
                    iVar8 = local_18 - local_20;
                    do {
                      uVar9 = (short)piStack_34;
                      if (*(short *)((local_20 * 2 - (int)puVar11) + iVar3 + (int)puVar7) == 0) {
                        uVar9 = (short)param_2;
                      }
                      *(undefined2 *)puVar7 = uVar9;
                      puVar7 = (undefined4 *)((int)puVar7 + 2);
                      iVar8 = iVar8 + -1;
                    } while (iVar8 != 0);
                  }
                  iVar3 = iVar3 + DAT_004ec414;
                  puVar11 = (undefined4 *)((int)puVar11 + (int)param_3);
                  param_4 = param_4 - 1;
                } while (param_4 != 0);
                param_4 = 0;
              }
            }
            else if (DAT_004e50dc == 3) {
              piStack_28 = param_2;
              piStack_24 = piStack_34;
              piStack_2c = param_3;
              if (local_14 - local_1c != 0) {
                param_5 = local_20 * 2;
                param_4 = local_14 - local_1c;
                do {
                  psVar5 = (short *)(param_5 + iVar3);
                  if (local_18 - local_20 != 0) {
                    iVar8 = local_18 - local_20;
                    puVar7 = puVar11;
                    do {
                      piVar10 = piStack_34;
                      if (*psVar5 == 0) {
                        piVar10 = param_2;
                      }
                      *puVar7 = piVar10;
                      psVar5 = psVar5 + 1;
                      puVar7 = puVar7 + 1;
                      iVar8 = iVar8 + -1;
                    } while (iVar8 != 0);
                  }
                  iVar3 = iVar3 + DAT_004ec414;
                  puVar11 = (undefined4 *)((int)puVar11 + (int)param_3);
                  param_4 = param_4 - 1;
                } while (param_4 != 0);
              }
            }
          }
          else if (DAT_004e50dc == 2) {
            piStack_2c = param_3;
            if (local_14 - local_1c != 0) {
              param_5 = local_20 * 2;
              param_4 = local_14 - local_1c;
              do {
                psVar5 = (short *)(param_5 + iVar3);
                if (local_18 - local_20 != 0) {
                  iVar6 = (int)puVar11 - (int)psVar5;
                  iVar8 = local_18 - local_20;
                  do {
                    if (*psVar5 != 0) {
                      *(short *)(iVar6 + (int)psVar5) = (short)piStack_34;
                    }
                    psVar5 = psVar5 + 1;
                    iVar8 = iVar8 + -1;
                  } while (iVar8 != 0);
                }
                iVar3 = iVar3 + DAT_004ec414;
                puVar11 = (undefined4 *)((int)puVar11 + (int)param_3);
                param_4 = param_4 - 1;
              } while (param_4 != 0);
              param_4 = 0;
            }
          }
          else if (DAT_004e50dc == 3) {
            piStack_2c = param_3;
            if (local_14 - local_1c != 0) {
              param_5 = local_20 * 2;
              param_4 = local_14 - local_1c;
              do {
                psVar5 = (short *)(param_5 + iVar3);
                if (local_18 - local_20 != 0) {
                  iVar8 = local_18 - local_20;
                  puVar7 = puVar11;
                  do {
                    if (*psVar5 != 0) {
                      *puVar7 = piStack_34;
                    }
                    psVar5 = psVar5 + 1;
                    puVar7 = puVar7 + 1;
                    iVar8 = iVar8 + -1;
                  } while (iVar8 != 0);
                }
                iVar3 = iVar3 + DAT_004ec414;
                puVar11 = (undefined4 *)((int)puVar11 + (int)param_3);
                param_4 = param_4 - 1;
              } while (param_4 != 0);
              param_4 = 0;
            }
          }
        }
        else if (DAT_004e50dc == 2) {
          piStack_2c = param_3;
          if (local_14 - local_1c != 0) {
            param_5 = local_20 * 2;
            param_4 = local_14 - local_1c;
            do {
              psVar5 = (short *)(param_5 + iVar3);
              if (local_18 - local_20 != 0) {
                iVar6 = (int)puVar11 - (int)psVar5;
                iVar8 = local_18 - local_20;
                do {
                  if (*psVar5 == 0) {
                    *(short *)(iVar6 + (int)psVar5) = (short)param_2;
                  }
                  psVar5 = psVar5 + 1;
                  iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
              }
              iVar3 = iVar3 + DAT_004ec414;
              puVar11 = (undefined4 *)((int)puVar11 + (int)param_3);
              param_4 = param_4 - 1;
            } while (param_4 != 0);
            param_4 = 0;
          }
        }
        else if (DAT_004e50dc == 3) {
          piStack_2c = param_3;
          if (local_14 - local_1c != 0) {
            param_5 = local_20 * 2;
            param_4 = local_14 - local_1c;
            do {
              psVar5 = (short *)(param_5 + iVar3);
              if (local_18 - local_20 != 0) {
                iVar8 = local_18 - local_20;
                puVar7 = puVar11;
                do {
                  if (*psVar5 == 0) {
                    *puVar7 = param_2;
                  }
                  psVar5 = psVar5 + 1;
                  puVar7 = puVar7 + 1;
                  iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
              }
              iVar3 = iVar3 + DAT_004ec414;
              puVar11 = (undefined4 *)((int)puVar11 + (int)param_3);
              param_4 = param_4 - 1;
            } while (param_4 != 0);
            param_4 = 0;
          }
        }
      }
      if (param_1 == &DAT_004e4fa0) {
        (**(code **)(DAT_004e5124 + 0xf0))();
        return;
      }
      (**(code **)(DAT_004e5124 + 0xe0))(*(undefined4 *)(param_1 + 0xc));
    }
  }
  return;
}


