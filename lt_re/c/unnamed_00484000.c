/* lithtech.exe decompilation - unnamed_00484000 */
#include "ghidra_types.h"

/* 00484030 size=184 */

undefined4 __cdecl FUN_00484030(int param_1,int param_2)

{
  int *piVar1;
  char *pcVar2;
  char *_Source;
  int iVar3;
  size_t sVar4;
  
  if (param_1 == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 0xbc) != '\x01') {
    return 0;
  }
  piVar1 = *(int **)(*(int *)(param_1 + 400) + 0x30);
  if (piVar1 == (int *)0x0) {
    *(undefined1 *)(param_2 + 0x80) = 0;
  }
  else {
    sVar4 = 0x7e;
    pcVar2 = FUN_0047b9b0(DAT_004ebfa4 + 0xc3c,piVar1);
    _strncpy((char *)(param_2 + 0x80),pcVar2,sVar4);
  }
  iVar3 = 0x34;
  pcVar2 = (char *)(param_2 + 0x100);
  do {
    piVar1 = *(int **)(*(int *)(param_1 + 400) + iVar3);
    if (piVar1 == (int *)0x0) {
      *pcVar2 = '\0';
    }
    else {
      sVar4 = 0x7e;
      _Source = FUN_0047b9b0(DAT_004ebfa4 + 0xc3c,piVar1);
      _strncpy(pcVar2,_Source,sVar4);
    }
    iVar3 = iVar3 + 4;
    pcVar2 = pcVar2 + 0x80;
  } while (iVar3 < 0x44);
  return 1;
}


/* 004841b0 size=175 */

void __thiscall FUN_004841b0(void *this,undefined4 *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = param_3;
  piVar3 = param_2;
  if (((*(int *)((int)this + 0xc) == 0) ||
      (piVar1 = *(int **)((int)this + 4), param_2 != (int *)*piVar1)) || (param_3 != piVar1)) {
    while (piVar3 != piVar2) {
      param_2 = piVar3;
      FUN_00485130((int *)&param_2);
      FUN_00484660(this,&param_3,piVar3);
      piVar3 = param_2;
    }
    *param_1 = piVar3;
    return;
  }
  piVar3 = (int *)piVar1[1];
  if ((int *)piVar1[1] != DAT_004ea6f0) {
    do {
      FUN_00484b20((int *)piVar3[2]);
      piVar2 = (int *)*piVar3;
      FUN_004591a0((int)(piVar3 + 3));
      FUN_00430df0((undefined *)piVar3);
      piVar3 = piVar2;
    } while (piVar2 != DAT_004ea6f0);
  }
  *(int **)(*(int *)((int)this + 4) + 4) = DAT_004ea6f0;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)*(undefined4 *)((int)this + 4) = *(undefined4 *)((int)this + 4);
  *(int *)(*(int *)((int)this + 4) + 8) = *(int *)((int)this + 4);
  *param_1 = **(undefined4 **)((int)this + 4);
  return;
}


/* 00484260 size=607 */

/* FUN_00484260: lifted from original x86 -> lt_lifted.c */


/* 004844c0 size=22 */

void __thiscall FUN_004844c0(void *this,undefined4 *param_1,undefined1 *param_2)

{
  *(undefined4 *)this = *param_1;
  *(undefined1 *)((int)this + 4) = *param_2;
  return;
}


/* 004844e0 size=382 */

/* FUN_004844e0: lifted from original x86 -> lt_lifted.c */


/* 00484660 size=1204 */

void __thiscall FUN_00484660(void *this,undefined4 *param_1,int *param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int *piVar10;
  int *piVar11;
  undefined *puVar12;
  int *local_c;
  int *local_8;
  int *local_4;
  
  piVar4 = param_2;
  FUN_00485130((int *)&param_2);
  piVar11 = (int *)*piVar4;
  piVar7 = piVar4 + 2;
  local_c = piVar4;
  piVar10 = piVar7;
  if (piVar11 == DAT_004ea6f0) {
    piVar11 = (int *)*piVar7;
  }
  else {
    piVar2 = (int *)*piVar7;
    if (piVar2 != DAT_004ea6f0) {
      local_c = piVar2;
      for (piVar10 = (int *)*piVar2; piVar10 != DAT_004ea6f0; piVar10 = (int *)*piVar10) {
        local_c = piVar10;
      }
      piVar11 = (int *)local_c[2];
      piVar10 = local_c + 2;
    }
  }
  FUN_004b9b4f(&local_4);
  piVar2 = local_c;
  if (local_c == piVar4) {
    piVar11[1] = local_c[1];
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar4) {
      *(int **)(*(int *)((int)this + 4) + 4) = piVar11;
    }
    else {
      piVar10 = (int *)piVar4[1];
      if ((int *)*piVar10 == piVar4) {
        *piVar10 = (int)piVar11;
      }
      else {
        piVar10[2] = (int)piVar11;
      }
    }
    local_8 = *(int **)((int)this + 4);
    if ((int *)*local_8 == piVar4) {
      if ((int *)*piVar7 == DAT_004ea6f0) {
        *local_8 = piVar4[1];
      }
      else {
        piVar7 = piVar11;
        if ((int *)*piVar11 != DAT_004ea6f0) {
          piVar10 = (int *)*piVar11;
          do {
            piVar7 = piVar10;
            piVar10 = (int *)*piVar7;
          } while ((int *)*piVar7 != DAT_004ea6f0);
        }
        *local_8 = (int)piVar7;
      }
    }
    if (*(int **)(*(int *)((int)this + 4) + 8) == piVar4) {
      if ((int *)*piVar4 == DAT_004ea6f0) {
        piVar7 = (int *)piVar4[1];
      }
      else {
        piVar10 = (int *)piVar11[2];
        piVar7 = piVar11;
        while (piVar4 = piVar10, piVar4 != DAT_004ea6f0) {
          piVar7 = piVar4;
          piVar10 = (int *)piVar4[2];
        }
      }
      *(int **)(*(int *)((int)this + 4) + 8) = piVar7;
    }
  }
  else {
    *(int **)(*piVar4 + 4) = local_c;
    *local_c = *piVar4;
    if (local_c == (int *)*piVar7) {
      piVar11[1] = (int)local_c;
    }
    else {
      piVar11[1] = local_c[1];
      *(int **)local_c[1] = piVar11;
      *piVar10 = *piVar7;
      *(int **)(*piVar7 + 4) = local_c;
    }
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar4) {
      *(int **)(*(int *)((int)this + 4) + 4) = local_c;
    }
    else {
      piVar7 = (int *)piVar4[1];
      if ((int *)*piVar7 == piVar4) {
        *piVar7 = (int)local_c;
      }
      else {
        piVar7[2] = (int)local_c;
      }
    }
    local_c = piVar4;
    piVar2[1] = piVar4[1];
    iVar3 = piVar2[0xb];
    piVar2[0xb] = piVar4[0xb];
    piVar4[0xb] = iVar3;
  }
  if (local_c[0xb] == 1) {
    if (piVar11 != *(int **)(*(int *)((int)this + 4) + 4)) {
      do {
        if (piVar11[0xb] != 1) break;
        piVar7 = *(int **)piVar11[1];
        if (piVar11 == piVar7) {
          piVar7 = (int *)((undefined4 *)piVar11[1])[2];
          if (piVar7[0xb] == 0) {
            piVar7[0xb] = 1;
            *(undefined4 *)(piVar11[1] + 0x2c) = 0;
            iVar3 = piVar11[1];
            piVar7 = *(int **)(iVar3 + 8);
            *(int *)(iVar3 + 8) = *piVar7;
            if ((int *)*piVar7 != DAT_004ea6f0) {
              ((int *)*piVar7)[1] = iVar3;
            }
            piVar7[1] = *(int *)(iVar3 + 4);
            if (iVar3 == *(int *)(*(int *)((int)this + 4) + 4)) {
              *(int **)(*(int *)((int)this + 4) + 4) = piVar7;
            }
            else {
              piVar10 = *(int **)(iVar3 + 4);
              if (iVar3 == *piVar10) {
                *piVar10 = (int)piVar7;
              }
              else {
                piVar10[2] = (int)piVar7;
              }
            }
            *piVar7 = iVar3;
            *(int **)(iVar3 + 4) = piVar7;
            piVar7 = *(int **)(piVar11[1] + 8);
          }
          if ((*(int *)(*piVar7 + 0x2c) != 1) || (*(int *)(piVar7[2] + 0x2c) != 1)) {
            if (*(int *)(piVar7[2] + 0x2c) == 1) {
              *(undefined4 *)(*piVar7 + 0x2c) = 1;
              iVar3 = *piVar7;
              piVar7[0xb] = 0;
              *piVar7 = *(int *)(iVar3 + 8);
              if (*(int **)(iVar3 + 8) != DAT_004ea6f0) {
                (*(int **)(iVar3 + 8))[1] = (int)piVar7;
              }
              *(int *)(iVar3 + 4) = piVar7[1];
              if (piVar7 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int *)(*(int *)((int)this + 4) + 4) = iVar3;
              }
              else {
                piVar10 = (int *)piVar7[1];
                if (piVar7 == (int *)piVar10[2]) {
                  piVar10[2] = iVar3;
                }
                else {
                  *piVar10 = iVar3;
                }
              }
              *(int **)(iVar3 + 8) = piVar7;
              piVar7[1] = iVar3;
              piVar7 = *(int **)(piVar11[1] + 8);
            }
            piVar7[0xb] = *(int *)(piVar11[1] + 0x2c);
            *(undefined4 *)(piVar11[1] + 0x2c) = 1;
            *(undefined4 *)(piVar7[2] + 0x2c) = 1;
            puVar8 = (undefined4 *)piVar11[1];
            puVar9 = (undefined4 *)puVar8[2];
            puVar8[2] = *puVar9;
            if ((int *)*puVar9 != DAT_004ea6f0) {
              ((int *)*puVar9)[1] = (int)puVar8;
            }
            puVar9[1] = puVar8[1];
            if (puVar8 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar9;
              *puVar9 = puVar8;
            }
            else {
              piVar7 = (int *)puVar8[1];
              if (puVar8 == (undefined4 *)*piVar7) {
                *piVar7 = (int)puVar9;
                *puVar9 = puVar8;
              }
              else {
                piVar7[2] = (int)puVar9;
                *puVar9 = puVar8;
              }
            }
            goto LAB_00484a26;
          }
        }
        else {
          if (piVar7[0xb] == 0) {
            piVar7[0xb] = 1;
            *(undefined4 *)(piVar11[1] + 0x2c) = 0;
            piVar7 = (int *)piVar11[1];
            iVar3 = *piVar7;
            *piVar7 = *(int *)(iVar3 + 8);
            if (*(int **)(iVar3 + 8) != DAT_004ea6f0) {
              (*(int **)(iVar3 + 8))[1] = (int)piVar7;
            }
            *(int *)(iVar3 + 4) = piVar7[1];
            if (piVar7 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int *)(*(int *)((int)this + 4) + 4) = iVar3;
            }
            else {
              piVar10 = (int *)piVar7[1];
              if (piVar7 == (int *)piVar10[2]) {
                piVar10[2] = iVar3;
              }
              else {
                *piVar10 = iVar3;
              }
            }
            *(int **)(iVar3 + 8) = piVar7;
            piVar7[1] = iVar3;
            piVar7 = *(int **)piVar11[1];
          }
          if ((*(int *)(piVar7[2] + 0x2c) != 1) || (*(int *)(*piVar7 + 0x2c) != 1)) {
            if (*(int *)(*piVar7 + 0x2c) == 1) {
              *(undefined4 *)(piVar7[2] + 0x2c) = 1;
              piVar10 = (int *)piVar7[2];
              piVar7[0xb] = 0;
              piVar7[2] = *piVar10;
              if ((int *)*piVar10 != DAT_004ea6f0) {
                ((int *)*piVar10)[1] = (int)piVar7;
              }
              piVar10[1] = piVar7[1];
              if (piVar7 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int **)(*(int *)((int)this + 4) + 4) = piVar10;
              }
              else {
                piVar4 = (int *)piVar7[1];
                if (piVar7 == (int *)*piVar4) {
                  *piVar4 = (int)piVar10;
                }
                else {
                  piVar4[2] = (int)piVar10;
                }
              }
              *piVar10 = (int)piVar7;
              piVar7[1] = (int)piVar10;
              piVar7 = *(int **)piVar11[1];
            }
            piVar7[0xb] = *(int *)(piVar11[1] + 0x2c);
            *(undefined4 *)(piVar11[1] + 0x2c) = 1;
            *(undefined4 *)(*piVar7 + 0x2c) = 1;
            puVar8 = (undefined4 *)piVar11[1];
            puVar9 = (undefined4 *)*puVar8;
            *puVar8 = puVar9[2];
            if ((int *)puVar9[2] != DAT_004ea6f0) {
              ((int *)puVar9[2])[1] = (int)puVar8;
            }
            puVar9[1] = puVar8[1];
            if (puVar8 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar9;
            }
            else {
              puVar5 = (undefined4 *)puVar8[1];
              if (puVar8 == (undefined4 *)puVar5[2]) {
                puVar5[2] = puVar9;
              }
              else {
                *puVar5 = puVar9;
              }
            }
            puVar9[2] = puVar8;
LAB_00484a26:
            puVar8[1] = puVar9;
            break;
          }
        }
        piVar7[0xb] = 0;
        piVar11 = (int *)piVar11[1];
      } while (piVar11 != *(int **)(*(int *)((int)this + 4) + 4));
    }
    piVar11[0xb] = 1;
  }
  FUN_004b9beb();
  piVar10 = local_c;
  piVar7 = local_c + 7;
  FUN_004850c0(&local_4,local_c[8]);
  puVar8 = (undefined4 *)FUN_004aa830(piVar10[8]);
  FUN_004850c0(&local_8,*puVar8);
  FUN_00484cd0(piVar7,&local_c,local_8,local_4);
  FUN_00430df0((undefined *)piVar10[8]);
  piVar10[8] = 0;
  piVar10[10] = 0;
  FUN_004b9b4f(&local_4);
  puVar6 = DAT_004ea6ec;
  DAT_004ea6e8 = DAT_004ea6e8 + -1;
  puVar12 = (undefined *)0x0;
  if (DAT_004ea6e8 == 0) {
    DAT_004ea6ec = (undefined *)0x0;
    puVar12 = puVar6;
  }
  FUN_004b9beb();
  if (puVar12 != (undefined *)0x0) {
    FUN_00430df0(puVar12);
  }
  iVar3 = piVar10[4];
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar3 + -1));
    }
    else {
      *(char *)(iVar3 + -1) = cVar1 + -1;
    }
  }
  piVar10[4] = 0;
  piVar10[5] = 0;
  piVar10[6] = 0;
  FUN_00430df0((undefined *)piVar10);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
  *param_1 = param_2;
  return;
}


/* 00484b20 size=251 */

void FUN_00484b20(int *param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  int *piVar7;
  int *piVar8;
  undefined1 local_c [4];
  undefined4 local_8;
  undefined4 local_4;
  
  piVar7 = param_1;
  if (param_1 != DAT_004ea6f0) {
    do {
      FUN_00484b20((int *)piVar7[2]);
      piVar2 = (int *)*piVar7;
      FUN_004850c0(&param_1,piVar7[8]);
      piVar8 = param_1;
      puVar5 = (undefined4 *)FUN_004599d0(piVar7 + 7,&local_8);
      FUN_00484cd0(piVar7 + 7,&local_4,(int *)*puVar5,piVar8);
      FUN_00430df0((undefined *)piVar7[8]);
      piVar7[8] = 0;
      piVar7[10] = 0;
      FUN_004b9b4f(local_c);
      puVar4 = DAT_004ea6ec;
      DAT_004ea6e8 = DAT_004ea6e8 + -1;
      puVar6 = (undefined *)0x0;
      if (DAT_004ea6e8 == 0) {
        DAT_004ea6ec = (undefined *)0x0;
        puVar6 = puVar4;
      }
      FUN_004b9beb();
      if (puVar6 != (undefined *)0x0) {
        FUN_00430df0(puVar6);
      }
      iVar3 = piVar7[4];
      if (iVar3 != 0) {
        cVar1 = *(char *)(iVar3 + -1);
        if ((cVar1 == '\0') || (cVar1 == -1)) {
          FUN_00430df0((char *)(iVar3 + -1));
        }
        else {
          *(char *)(iVar3 + -1) = cVar1 + -1;
        }
      }
      piVar7[4] = 0;
      piVar7[5] = 0;
      piVar7[6] = 0;
      FUN_00430df0((undefined *)piVar7);
      piVar7 = piVar2;
    } while (piVar2 != DAT_004ea6f0);
  }
  return;
}


/* 00484c20 size=172 */

/* FUN_00484c20: lifted from original x86 -> lt_lifted.c */


/* 00484cd0 size=177 */

void __thiscall FUN_00484cd0(void *this,undefined4 *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = param_3;
  piVar3 = param_2;
  if (((*(int *)((int)this + 0xc) == 0) ||
      (piVar1 = *(int **)((int)this + 4), param_2 != (int *)*piVar1)) || (param_3 != piVar1)) {
    while (piVar3 != piVar2) {
      param_2 = piVar3;
      FUN_00459b00((int *)&param_2);
      FUN_00459e20(this,&param_3,piVar3);
      piVar3 = param_2;
    }
    *param_1 = piVar3;
    return;
  }
  piVar3 = (int *)piVar1[1];
  if ((int *)piVar1[1] != DAT_004ea6ec) {
    do {
      FUN_0045a340((int *)piVar3[2]);
      piVar2 = (int *)*piVar3;
      FUN_00414100(piVar3 + 3,'\x01');
      FUN_00430df0((undefined *)piVar3);
      piVar3 = piVar2;
    } while (piVar2 != DAT_004ea6ec);
  }
  *(int **)(*(int *)((int)this + 4) + 4) = DAT_004ea6ec;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)*(undefined4 *)((int)this + 4) = *(undefined4 *)((int)this + 4);
  *(int *)(*(int *)((int)this + 4) + 8) = *(int *)((int)this + 4);
  *param_1 = **(undefined4 **)((int)this + 4);
  return;
}


/* 00484d90 size=619 */

void __thiscall
FUN_00484d90(void *this,undefined4 *param_1,int param_2,int *param_3,undefined1 *param_4)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  
  piVar3 = (int *)FUN_00430de0(0x20);
  piVar3[1] = (int)param_3;
  piVar3[7] = 0;
  *piVar3 = DAT_004ea6ec;
  piVar3[2] = DAT_004ea6ec;
  FUN_00430970((undefined1 *)(piVar3 + 3),param_4);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if ((param_3 != *(int **)((int)this + 4)) && (param_2 == DAT_004ea6ec)) {
    uVar4 = FUN_0045a710(param_4,(int)(param_3 + 3));
    if (-1 < (int)uVar4) {
      param_3[2] = (int)piVar3;
      if (param_3 == *(int **)(*(int *)((int)this + 4) + 8)) {
        *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
      }
      goto LAB_00484e24;
    }
  }
  *param_3 = (int)piVar3;
  piVar5 = *(int **)((int)this + 4);
  if (param_3 == piVar5) {
    piVar5[1] = (int)piVar3;
    *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
  }
  else if (param_3 == (int *)*piVar5) {
    *piVar5 = (int)piVar3;
  }
LAB_00484e24:
  piVar5 = piVar3;
  if (piVar3 != *(int **)(*(int *)((int)this + 4) + 4)) {
    do {
      piVar6 = (int *)piVar5[1];
      if (piVar6[7] != 0) break;
      piVar7 = *(int **)piVar6[1];
      if (piVar6 == piVar7) {
        iVar1 = ((undefined4 *)piVar6[1])[2];
        if (*(int *)(iVar1 + 0x1c) == 0) {
          piVar6[7] = 1;
          *(undefined4 *)(iVar1 + 0x1c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x1c) = 0;
          piVar5 = *(int **)(piVar5[1] + 4);
        }
        else {
          if (piVar5 == (int *)piVar6[2]) {
            piVar5 = (int *)piVar6[2];
            piVar6[2] = *piVar5;
            if (*piVar5 != DAT_004ea6ec) {
              *(int **)(*piVar5 + 4) = piVar6;
            }
            piVar5[1] = piVar6[1];
            if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int **)(*(int *)((int)this + 4) + 4) = piVar5;
            }
            else {
              piVar7 = (int *)piVar6[1];
              if (piVar6 == (int *)*piVar7) {
                *piVar7 = (int)piVar5;
              }
              else {
                piVar7[2] = (int)piVar5;
              }
            }
            *piVar5 = (int)piVar6;
            piVar6[1] = (int)piVar5;
            piVar5 = piVar6;
          }
          *(undefined4 *)(piVar5[1] + 0x1c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x1c) = 0;
          piVar6 = *(int **)(piVar5[1] + 4);
          piVar7 = (int *)*piVar6;
          *piVar6 = piVar7[2];
          if (piVar7[2] != DAT_004ea6ec) {
            *(int **)(piVar7[2] + 4) = piVar6;
          }
          piVar7[1] = piVar6[1];
          if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
            *(int **)(*(int *)((int)this + 4) + 4) = piVar7;
            piVar7[2] = (int)piVar6;
          }
          else {
            piVar2 = (int *)piVar6[1];
            if (piVar6 == (int *)piVar2[2]) {
              piVar2[2] = (int)piVar7;
              piVar7[2] = (int)piVar6;
            }
            else {
              *piVar2 = (int)piVar7;
              piVar7[2] = (int)piVar6;
            }
          }
LAB_00484fd2:
          piVar6[1] = (int)piVar7;
        }
      }
      else {
        if (piVar7[7] != 0) {
          if (piVar5 == (int *)*piVar6) {
            iVar1 = *piVar6;
            *piVar6 = *(int *)(iVar1 + 8);
            if (*(int *)(iVar1 + 8) != DAT_004ea6ec) {
              *(int **)(*(int *)(iVar1 + 8) + 4) = piVar6;
            }
            *(int *)(iVar1 + 4) = piVar6[1];
            if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int *)(*(int *)((int)this + 4) + 4) = iVar1;
            }
            else {
              piVar5 = (int *)piVar6[1];
              if (piVar6 == (int *)piVar5[2]) {
                piVar5[2] = iVar1;
              }
              else {
                *piVar5 = iVar1;
              }
            }
            *(int **)(iVar1 + 8) = piVar6;
            piVar6[1] = iVar1;
            piVar5 = piVar6;
          }
          *(undefined4 *)(piVar5[1] + 0x1c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x1c) = 0;
          piVar6 = *(int **)(piVar5[1] + 4);
          piVar7 = (int *)piVar6[2];
          piVar6[2] = *piVar7;
          if (*piVar7 != DAT_004ea6ec) {
            *(int **)(*piVar7 + 4) = piVar6;
          }
          piVar7[1] = piVar6[1];
          if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
            *(int **)(*(int *)((int)this + 4) + 4) = piVar7;
          }
          else {
            piVar2 = (int *)piVar6[1];
            if (piVar6 == (int *)*piVar2) {
              *piVar2 = (int)piVar7;
            }
            else {
              piVar2[2] = (int)piVar7;
            }
          }
          *piVar7 = (int)piVar6;
          goto LAB_00484fd2;
        }
        piVar6[7] = 1;
        piVar7[7] = 1;
        *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x1c) = 0;
        piVar5 = *(int **)(piVar5[1] + 4);
      }
    } while (piVar5 != *(int **)(*(int *)((int)this + 4) + 4));
  }
  *(undefined4 *)(*(int *)(*(int *)((int)this + 4) + 4) + 0x1c) = 1;
  *param_1 = piVar3;
  return;
}


/* 00485000 size=82 */

void __thiscall FUN_00485000(void *this,int param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = *(int **)(param_1 + 8);
  *(int *)(param_1 + 8) = *piVar1;
  if (*piVar1 != DAT_004ea6ec) {
    *(int *)(*piVar1 + 4) = param_1;
  }
  piVar1[1] = *(int *)(param_1 + 4);
  if (param_1 == *(int *)(*(int *)((int)this + 4) + 4)) {
    *(int **)(*(int *)((int)this + 4) + 4) = piVar1;
    *piVar1 = param_1;
    *(int **)(param_1 + 4) = piVar1;
    return;
  }
  piVar2 = *(int **)(param_1 + 4);
  if (param_1 == *piVar2) {
    *piVar2 = (int)piVar1;
    *piVar1 = param_1;
    *(int **)(param_1 + 4) = piVar1;
    return;
  }
  piVar2[2] = (int)piVar1;
  *piVar1 = param_1;
  *(int **)(param_1 + 4) = piVar1;
  return;
}


/* 00485060 size=86 */

void __thiscall FUN_00485060(void *this,int *param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1;
  *param_1 = *(int *)(iVar1 + 8);
  if (*(int *)(iVar1 + 8) != DAT_004ea6ec) {
    *(int **)(*(int *)(iVar1 + 8) + 4) = param_1;
  }
  *(int *)(iVar1 + 4) = param_1[1];
  if (param_1 == *(int **)(*(int *)((int)this + 4) + 4)) {
    *(int *)(*(int *)((int)this + 4) + 4) = iVar1;
    *(int **)(iVar1 + 8) = param_1;
    param_1[1] = iVar1;
    return;
  }
  piVar2 = (int *)param_1[1];
  if (param_1 == (int *)piVar2[2]) {
    piVar2[2] = iVar1;
    *(int **)(iVar1 + 8) = param_1;
    param_1[1] = iVar1;
    return;
  }
  *piVar2 = iVar1;
  *(int **)(iVar1 + 8) = param_1;
  param_1[1] = iVar1;
  return;
}


/* 004850c0 size=11 */

void __thiscall FUN_004850c0(void *this,undefined4 param_1)

{
  *(undefined4 *)this = param_1;
  return;
}


/* 004850d0 size=81 */

void __fastcall FUN_004850d0(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)*param_1;
  if ((piVar3[7] == 0) && (*(int **)(piVar3[1] + 4) == piVar3)) {
    *param_1 = piVar3[2];
    return;
  }
  iVar1 = *piVar3;
  if (iVar1 != DAT_004ea6ec) {
    for (iVar2 = *(int *)(iVar1 + 8); iVar2 != DAT_004ea6ec; iVar2 = *(int *)(iVar2 + 8)) {
      iVar1 = iVar2;
    }
    *param_1 = iVar1;
    return;
  }
  piVar3 = (int *)piVar3[1];
  if (*param_1 == *piVar3) {
    do {
      *param_1 = (int)piVar3;
      piVar3 = (int *)piVar3[1];
    } while (*param_1 == *piVar3);
  }
  *param_1 = (int)piVar3;
  return;
}


/* 00485130 size=67 */

void __fastcall FUN_00485130(int *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = *(undefined4 **)(*param_1 + 8);
  if (puVar1 != DAT_004ea6f0) {
    for (puVar2 = (undefined4 *)*puVar1; puVar2 != DAT_004ea6f0; puVar2 = (undefined4 *)*puVar2) {
      puVar1 = puVar2;
    }
    *param_1 = (int)puVar1;
    return;
  }
  iVar3 = *(int *)(*param_1 + 4);
  if (*param_1 == *(int *)(iVar3 + 8)) {
    do {
      *param_1 = iVar3;
      iVar3 = *(int *)(iVar3 + 4);
    } while (*param_1 == *(int *)(iVar3 + 8));
  }
  if (*(int *)(*param_1 + 8) != iVar3) {
    *param_1 = iVar3;
  }
  return;
}


/* 00485180 size=105 */

uint __thiscall FUN_00485180(void *this,uint param_1,uint param_2,byte *param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  bool bVar4;
  bool bVar5;
  
  if (*(uint *)((int)this + 8) < param_1) {
    FUN_004b9a1c();
  }
  uVar1 = *(int *)((int)this + 8) - param_1;
  if (uVar1 < param_2) {
    param_2 = uVar1;
  }
  uVar1 = param_2;
  if (param_4 <= param_2) {
    uVar1 = param_4;
  }
  if (*(int *)((int)this + 4) == 0) {
    pbVar3 = (byte *)0x0;
  }
  else {
    pbVar3 = (byte *)(*(int *)((int)this + 4) + param_1);
  }
  bVar4 = false;
  uVar2 = 0;
  bVar5 = true;
  do {
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    bVar4 = *pbVar3 < *param_3;
    bVar5 = *pbVar3 == *param_3;
    pbVar3 = pbVar3 + 1;
    param_3 = param_3 + 1;
  } while (bVar5);
  if (!bVar5) {
    uVar2 = (1 - (uint)bVar4) - (uint)(bVar4 != 0);
  }
  if (uVar2 == 0) {
    if (param_2 < param_4) {
      return 0xffffffff;
    }
    uVar2 = (uint)(param_2 != param_4);
  }
  return uVar2;
}


/* 00485220 size=125 */

void __fastcall FUN_00485220(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar2 = param_1[0x55];
  param_1[0x55] = iVar2 + -1;
  if (iVar2 + -1 == 0) {
    puVar1 = (undefined4 *)param_1[0x53];
    iVar2 = DAT_004ebfa4;
    while (DAT_004ebfa4 = iVar2, puVar1 != param_1 + 0x52) {
      puVar3 = (undefined4 *)puVar1[1];
      puVar4 = (undefined4 *)puVar1[2];
      puVar1 = puVar3;
      if ((puVar4 != (undefined4 *)0x0) && (iVar2 != -0xa74)) {
        *puVar4 = *(undefined4 *)(iVar2 + 0xa8c);
        *(undefined4 **)(iVar2 + 0xa8c) = puVar4;
        iVar2 = DAT_004ebfa4;
      }
    }
    puVar1 = param_1 + 0x52;
    param_1[0x53] = puVar1;
    *puVar1 = puVar1;
    param_1[0x51] = 0;
    iVar2 = DAT_004ebfa4;
    if ((param_1 != (undefined4 *)0x0) && (DAT_004ebfa4 != -0xbe4)) {
      *param_1 = *(undefined4 *)(DAT_004ebfa4 + 0xbfc);
      *(undefined4 **)(iVar2 + 0xbfc) = param_1;
    }
  }
  return;
}


/* 004852e0 size=11 */

void FUN_004852e0(void)

{
  DAT_004ebf68 = 0;
  return;
}


/* 004852f0 size=12 */

void FUN_004852f0(void)

{
  FUN_004b9cf5(&LAB_00485300);
  return;
}


/* 00485330 size=349 */

int __cdecl FUN_00485330(void *param_1,int *param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if ((short)param_3 == -1) {
    for (iVar6 = *(int *)((int)param_1 + 0xad8); iVar6 != (int)param_1 + 0xad4;
        iVar6 = *(int *)(iVar6 + 4)) {
      *param_2 = iVar6;
      if ((*(uint *)(iVar6 + 8) & 0x40000000) == 0) goto LAB_00485402;
    }
    iVar6 = FUN_00489660((int)param_1,param_2);
    if (iVar6 != 0) {
      return iVar6;
    }
  }
  else {
    uVar1 = *(uint *)((int)param_1 + 0xacc);
    while (uVar1 <= (param_3 & 0xffff)) {
      iVar6 = FUN_00489660((int)param_1,param_2);
      if (iVar6 != 0) {
        return iVar6;
      }
      uVar1 = *(uint *)((int)param_1 + 0xacc);
    }
    iVar6 = FUN_0047a0f0((int)param_1,param_3);
    *param_2 = iVar6;
    if (iVar6 == 0) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_AllocateID_004dc814);
      }
      return 1;
    }
  }
LAB_00485402:
  *(uint *)(*param_2 + 8) = *(uint *)(*param_2 + 8) & 0xbfffffff;
  piVar2 = (int *)*param_2;
  *(int *)(*piVar2 + 4) = piVar2[1];
  *(int *)piVar2[1] = *piVar2;
  piVar2[1] = (int)piVar2;
  *piVar2 = (int)piVar2;
  piVar2 = (int *)*param_2;
  *piVar2 = (int)param_1 + 0xae0;
  puVar3 = *(undefined4 **)((int)param_1 + 0xae4);
  piVar2[1] = (int)puVar3;
  *puVar3 = piVar2;
  *(int **)(*piVar2 + 4) = piVar2;
  if (*(uint *)((int)param_1 + 0xac8) < *(uint *)((int)param_1 + 0xacc)) {
    FUN_00486ed0(param_1,*(uint *)((int)param_1 + 0xacc));
  }
  for (iVar6 = *(int *)((int)param_1 + 0x9fc); iVar6 != (int)param_1 + 0x9f8;
      iVar6 = *(int *)(iVar6 + 4)) {
    iVar4 = *(int *)(*param_2 + 8);
    iVar5 = *(int *)(*(int *)(iVar6 + 8) + 400);
    *(undefined2 *)(iVar5 + iVar4 * 4) = 0;
    *(undefined1 *)(iVar5 + 2 + iVar4 * 4) = 0;
  }
  return 0;
}


/* 00485490 size=48 */

void __cdecl FUN_00485490(int param_1,int *param_2)

{
  undefined4 *puVar1;
  
  *(int *)(*param_2 + 4) = param_2[1];
  *(int *)param_2[1] = *param_2;
  param_2[1] = (int)param_2;
  *param_2 = param_1 + 0xad4;
  puVar1 = *(undefined4 **)(param_1 + 0xad8);
  param_2[1] = (int)puVar1;
  *puVar1 = param_2;
  *(int **)(*param_2 + 4) = param_2;
  return;
}


/* 004858f0 size=747 */

void __fastcall FUN_004858f0(undefined2 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  undefined2 *puVar4;
  int iVar5;
  LONG LVar6;
  int *piVar7;
  int *piVar8;
  
  puVar1 = DAT_004ebf68;
  if (DAT_004ebf68 != (undefined4 *)0x0) {
    LVar6 = InterlockedDecrement(DAT_004ebf68 + 1);
    if ((LVar6 < 1) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
    DAT_004ebf68 = (undefined4 *)0x0;
  }
  FUN_00486990((int)param_1);
  FUN_0044e520((int)(param_1 + 0x66a));
  FUN_00486640(param_1);
  servermgr_488360(param_1,0);
  FUN_00430fe0(*(undefined **)(param_1 + 0x63e));
  *(undefined4 *)(param_1 + 0x63e) = 0;
  *(undefined4 *)(param_1 + 0x640) = 0;
  puVar4 = *(undefined2 **)(param_1 + 0x4fe);
  while (puVar4 != param_1 + 0x4fc) {
    puVar1 = (undefined4 *)(puVar4 + 4);
    puVar4 = *(undefined2 **)(puVar4 + 2);
    s_client_4730b0(param_1,(int *)*puVar1);
  }
  puVar4 = param_1 + 0x4fc;
  *(undefined2 **)(param_1 + 0x4fe) = puVar4;
  *(undefined2 **)puVar4 = puVar4;
  *(undefined4 *)(param_1 + 0x4fa) = 0;
  FUN_004649a0(param_1 + 0x476);
  servermgr_485be0((int)param_1,1);
  FUN_00489960((int)param_1);
  piVar3 = (int *)(param_1 + 0x56a);
  if (*(int **)(param_1 + 0x56c) != piVar3) {
    piVar7 = *(int **)(param_1 + 0x56c);
    piVar8 = DAT_004e514c;
    do {
      piVar2 = piVar7 + 1;
      if (piVar7 != (int *)0x0) {
        *piVar7 = (int)piVar8;
        piVar8 = piVar7;
        DAT_004e514c = piVar7;
      }
      piVar7 = (int *)*piVar2;
    } while ((int *)*piVar2 != piVar3);
  }
  *(int **)(param_1 + 0x56c) = piVar3;
  *piVar3 = (int)piVar3;
  *(undefined4 *)(param_1 + 0x566) = 0;
  iVar5 = *(int *)(param_1 + 0x588);
  if (iVar5 != 0) {
    if (iVar5 != 0) {
      (**(code **)(DAT_004ecc58 + 8))(iVar5);
    }
    *(undefined4 *)(param_1 + 0x588) = 0;
    *(undefined4 *)(param_1 + 0x58c) = 0;
  }
  *(undefined4 *)(param_1 + 0x58a) = 0;
  FUN_0042be60((int)(param_1 + 0xd2));
  FUN_00479290((int)param_1);
  FUN_00434d00(*(int **)(param_1 + 0x594));
  *(undefined4 *)(param_1 + 0x594) = 0;
  FUN_00402970((undefined4 *)(param_1 + 0x50e));
  FUN_0043c4b0();
  FUN_00476060((undefined4 *)(param_1 + 0x642));
  FUN_0049b5d0(&LAB_00485c50,0);
  FUN_0047b4d0((int)(param_1 + 0x61e));
  FUN_004b7c50((int)(param_1 + 0x5d6));
  FUN_004b7c50((int)(param_1 + 0x5e4));
  FUN_004b7c50((int)(param_1 + 0x52c));
  FUN_004b7c50((int)(param_1 + 0x5f2));
  FUN_004b7c50((int)(param_1 + 0x53a));
  FUN_004b7c50((int)(param_1 + 6));
  FUN_004b7c50((int)(param_1 + 0x14));
  FUN_004b7c50((int)(param_1 + 0x548));
  FUN_004b7c50((int)(param_1 + 0x556));
  (**(code **)(*(int *)(param_1 + 0x600) + 0xc))();
  FUN_00434d00(*(int **)(param_1 + 0x568));
  *(undefined4 *)(param_1 + 0x568) = 0;
  if (*(undefined **)(param_1 + 0x596) != (undefined *)0x0) {
    FUN_00430fe0(*(undefined **)(param_1 + 0x596));
    *(undefined4 *)(param_1 + 0x596) = 0;
  }
  *(undefined4 *)(param_1 + 0x59a) = 0;
  *(undefined4 *)(param_1 + 0x598) = 0;
  FUN_0046a690((int)(param_1 + 0x1ca));
  if (*(undefined **)(param_1 + 0x45a) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)(param_1 + 0x45a));
    *(undefined4 *)(param_1 + 0x45a) = 0;
  }
  if (*(int **)(param_1 + 0x59c) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x59c) + 0x11c))(1);
    *(undefined4 *)(param_1 + 0x59c) = 0;
  }
  if (*(int **)(param_1 + 0x50c) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x50c) + 4))();
    *(undefined4 *)(param_1 + 0x50c) = 0;
  }
  if (*(undefined **)(param_1 + 0x50a) != (undefined *)0x0) {
    FUN_00430df0(*(undefined **)(param_1 + 0x50a));
    *(undefined4 *)(param_1 + 0x50a) = 0;
  }
  if (*(undefined4 **)(param_1 + 0x69c) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x69c))(1);
    *(undefined4 *)(param_1 + 0x69c) = 0;
  }
  *(undefined4 *)(param_1 + 0x668) = 0;
  DAT_004ebfa4 = 0;
  DAT_004ebfa8 = 0;
  return;
}


/* 00485cc0 size=339 */

/* WARNING: Removing unreachable block (ram,0x00485dc8) */

undefined4 __thiscall FUN_00485cc0(void *this,int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  int *piVar5;
  
  iVar2 = *(int *)(param_1 + 0x48);
  uVar1 = 0;
  if (*(uint *)(iVar2 + 0x44) != 0) {
    piVar5 = *(int **)(iVar2 + 0x40);
    do {
      if (*piVar5 == param_1) {
        if (uVar1 != 0xffffffff) {
          FUN_00433590((void *)(iVar2 + 0x3c),uVar1,&DAT_004ecc58);
        }
        break;
      }
      uVar1 = uVar1 + 1;
      piVar5 = piVar5 + 1;
    } while (uVar1 < *(uint *)(iVar2 + 0x44));
  }
  uVar1 = *(uint *)((int)this + 0x930);
  if (*(int *)((int)this + 0x934) == 0) {
    iVar2 = FUN_00456f10(&DAT_004ecc58,0,*(int *)((int)this + 0x938) + 1 + uVar1);
    if (iVar2 == 0) goto LAB_00485df8;
    uVar3 = 0;
    if (uVar1 != 0) {
      do {
        uVar3 = uVar3 + 1;
        *(undefined4 *)(iVar2 + -4 + uVar3 * 4) =
             *(undefined4 *)(*(int *)((int)this + 0x92c) + -4 + uVar3 * 4);
      } while (uVar3 < uVar1);
    }
    if (uVar1 < *(uint *)((int)this + 0x930)) {
      uVar3 = uVar1;
      puVar4 = (undefined4 *)(iVar2 + 4 + uVar1 * 4);
      do {
        uVar3 = uVar3 + 1;
        *puVar4 = *(undefined4 *)(*(int *)((int)this + 0x92c) + -4 + uVar3 * 4);
        puVar4 = puVar4 + 1;
      } while (uVar3 < *(uint *)((int)this + 0x930));
    }
    *(int *)(iVar2 + uVar1 * 4) = param_1;
    if (*(int *)((int)this + 0x92c) != 0) {
      FUN_00456e60(&DAT_004ecc58,*(int *)((int)this + 0x92c));
      *(undefined4 *)((int)this + 0x92c) = 0;
      *(undefined4 *)((int)this + 0x934) = 0;
    }
    *(int *)((int)this + 0x92c) = iVar2;
    *(undefined4 *)((int)this + 0x934) = *(undefined4 *)((int)this + 0x938);
  }
  else {
    *(int *)((int)this + 0x934) = *(int *)((int)this + 0x934) + -1;
    *(int *)(*(int *)((int)this + 0x92c) + uVar1 * 4) = param_1;
  }
  *(int *)((int)this + 0x930) = *(int *)((int)this + 0x930) + 1;
LAB_00485df8:
  *(int *)((int)this + 0x9ec) = param_1;
  *(int *)(param_1 + 0x48) = (int)this + 0x8ec;
  return 1;
}


/* 00485e20 size=135 */

undefined4 __thiscall FUN_00485e20(void *this,undefined4 *param_1,undefined4 *param_2)

{
  char unaff_DI;
  int local_cc;
  undefined4 local_c8 [50];
  
  FUN_00486990((int)this);
  if (param_2 == (undefined4 *)0x0) {
    FUN_00489880((int)this,0x39,unaff_DI);
    return 0;
  }
  FUN_0047b530((int)this + 0xc3c,param_1,param_2,local_c8,&local_cc);
  if (local_cc == 0) {
    FUN_00489880((int)this,0x1b,(char)*param_1);
    return 0;
  }
  return 1;
}


/* 00485eb0 size=30 */

bool __fastcall FUN_00485eb0(int param_1)

{
  int iVar1;
  
  FUN_00486990(param_1);
  iVar1 = Cothineal_402a60((int *)(param_1 + 0xa1c));
  return (bool)('\x01' - (iVar1 != 0));
}


/* 00485ed0 size=76 */

void __thiscall FUN_00485ed0(void *this,undefined4 *param_1,uint param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  
  FUN_00430fe0(*(undefined **)((int)this + 0xc7c));
  puVar1 = FUN_00430f00(param_2);
  *(undefined4 **)((int)this + 0xc7c) = puVar1;
  if (puVar1 != (undefined4 *)0x0) {
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
    *(uint *)((int)this + 0xc80) = param_2;
  }
  return;
}


/* 00485f20 size=55 */

void __cdecl FUN_00485f20(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xb20);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0xb20) = 0;
    return;
  }
  do {
    *(undefined2 *)(*(int *)(iVar1 + 400) + 0x58) = 0;
    iVar1 = *(int *)(*(int *)(iVar1 + 400) + 0x50);
  } while (iVar1 != 0);
  *(undefined4 *)(param_1 + 0xb20) = 0;
  return;
}


/* 00485f60 size=34 */

void __cdecl FUN_00485f60(int param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)(param_1 + 0xb24); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
    *(undefined2 *)(iVar1 + 0x2c) = 0;
  }
  *(undefined4 *)(param_1 + 0xb24) = 0;
  return;
}


/* 00486360 size=82 */

void __cdecl FUN_00486360(undefined2 *param_1)

{
  undefined2 *puVar1;
  
  FUN_004863c0(param_1);
  FUN_00486430((int)param_1);
  puVar1 = *(undefined2 **)(param_1 + 0x528);
  while (puVar1 != param_1 + 0x526) {
    FUN_0047a020((int)param_1);
    puVar1 = *(undefined2 **)(param_1 + 0x528);
  }
  *(undefined4 *)(param_1 + 0x590) = 0;
  *(undefined4 *)(param_1 + 0x592) = 0;
  FUN_004863f0((uint)param_1);
  return;
}


/* 004863c0 size=47 */

void __cdecl FUN_004863c0(undefined2 *param_1)

{
  undefined2 *puVar1;
  
  for (puVar1 = *(undefined2 **)(param_1 + 0x4fe); puVar1 != param_1 + 0x4fc;
      puVar1 = *(undefined2 **)(puVar1 + 2)) {
    FUN_00473770(param_1,*(int **)(puVar1 + 4));
  }
  return;
}


/* 004863f0 size=61 */

void __cdecl FUN_004863f0(uint param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)(param_1 + 0x9fc); iVar1 != param_1 + 0x9f8; iVar1 = *(int *)(iVar1 + 4)) {
    FUN_00474690(param_1,*(int **)(iVar1 + 8));
  }
  *(undefined4 *)(param_1 + 0xa0c) = 0;
  *(undefined4 *)(param_1 + 0xa10) = 0;
  return;
}


/* 00486430 size=164 */

void __cdecl FUN_00486430(int param_1)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  for (iVar2 = *(int *)(param_1 + 0x9fc); iVar2 != param_1 + 0x9f8; iVar2 = *(int *)(iVar2 + 4)) {
    iVar3 = *(int *)(iVar2 + 8);
    if (*(int *)(iVar3 + 0x3b8) == 3) {
      for (iVar4 = *(int *)(param_1 + 0xb20); iVar4 != 0;
          iVar4 = *(int *)(*(int *)(iVar4 + 400) + 0x50)) {
        puVar1 = (ushort *)(*(int *)(iVar3 + 400) + (uint)*(ushort *)(iVar4 + 0xb8) * 4);
        *puVar1 = *puVar1 | *(ushort *)(*(int *)(iVar4 + 400) + 0x58);
      }
      for (iVar4 = *(int *)(param_1 + 0xb24); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x30)) {
        puVar1 = (ushort *)
                 (*(int *)(iVar3 + 400) + (*(uint *)(*(int *)(iVar4 + 0xc) + 8) & 0xffff) * 4);
        *puVar1 = *puVar1 | *(ushort *)(iVar4 + 0x2c);
      }
    }
  }
  FUN_00485f20(param_1);
  FUN_00485f60(param_1);
  return;
}


/* 004864e0 size=59 */

void __thiscall FUN_004864e0(void *this,float param_1)

{
  int iVar1;
  void *this_00;
  
  iVar1 = *(int *)((int)this + 0x5c);
  while ((iVar1 != (int)this + 0x58 && (this_00 = *(void **)(iVar1 + 8), this_00 != (void *)0x0))) {
    iVar1 = *(int *)(iVar1 + 4);
    if ((*(int *)((int)this_00 + 0x10) == 0) || (*(int *)((int)this_00 + 0x28) != 0)) {
      FUN_0049a700(this_00,param_1);
    }
  }
  return;
}


/* 00486520 size=176 */

void __fastcall FUN_00486520(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x5c);
  if (iVar3 != param_1 + 0x58) {
    do {
      piVar1 = *(int **)(iVar3 + 8);
      if (piVar1 == (int *)0x0) {
        return;
      }
      iVar3 = *(int *)(iVar3 + 4);
      if (((piVar1[4] != 0) && ((short)piVar1[0xb] == 0)) && (piVar1[10] == 0)) {
        if ((((*(byte *)(piVar1 + 0xd) & 8) != 0) && (piVar1[0xe] != 0)) &&
           (iVar2 = *(int *)(piVar1[0xe] + 4), iVar2 != 0)) {
          FUN_004455c0(param_1,iVar2,(int)piVar1,1);
        }
        *(int *)(*piVar1 + 4) = piVar1[1];
        *(int *)piVar1[1] = *piVar1;
        piVar1[1] = (int)piVar1;
        *piVar1 = (int)piVar1;
        *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + -1;
        if ((int *)piVar1[3] != (int *)0x0) {
          FUN_00485490(DAT_004ebfa4,(int *)piVar1[3]);
        }
        piVar1[6] = 0;
        piVar1[3] = 0;
        if (param_1 != -0x28) {
          *piVar1 = *(int *)(param_1 + 0x40);
          *(int **)(param_1 + 0x40) = piVar1;
        }
      }
    } while (iVar3 != param_1 + 0x58);
  }
  return;
}


/* 004865d0 size=106 */

void __thiscall FUN_004865d0(void *this,int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  
  piVar1 = *(int **)((int)this + 0xa30);
  if (*(int *)(param_1 + 0x10) == 0) {
    iVar4 = *(int *)(param_1 + 0x18);
    if (*(int *)(param_1 + 8) == 0) {
      FUN_0047aac0((int)this,iVar4,(int)*(int **)(param_1 + 0x14),1);
      if (piVar1 != (int *)0x0) {
        iVar2 = *piVar1;
        uVar5 = 0;
        uVar3 = FUN_00468720(iVar4);
        (**(code **)(iVar2 + 0x4c))(uVar3,uVar5);
        return;
      }
    }
    else if (piVar1 != (int *)0x0) {
      iVar4 = FUN_00434fb0(**(int **)(param_1 + 0x14),(uint *)0x0);
      (**(code **)(*piVar1 + 0x4c))(iVar4,1);
    }
  }
  return;
}


/* 00486640 size=76 */

void __fastcall FUN_00486640(void *param_1)

{
  int iVar1;
  int local_20 [8];
  
  FUN_0044df70((int)local_20);
  iVar1 = FUN_0044e1e0((void *)((int)param_1 + 0xd00),local_20,0);
  while (iVar1 == 0) {
    FUN_004865d0(param_1,(int)local_20);
    iVar1 = FUN_0044e1e0((void *)((int)param_1 + 0xd00),local_20,0);
  }
  return;
}


/* 00486990 size=19 */

void __fastcall FUN_00486990(int param_1)

{
  DAT_004ebfa4 = param_1;
  DAT_004ebfa8 = param_1 + 0xa1c;
  return;
}


/* 004869b0 size=25 */

void __thiscall FUN_004869b0(void *this,char *param_1,size_t param_2)

{
  _strncpy(param_1,(char *)((int)this + 0x68),param_2);
  return;
}


/* 004869d0 size=188 */

/* FUN_004869d0: lifted from original x86 -> lt_lifted.c */


/* 00486aa0 size=219 */

undefined4 __thiscall FUN_00486aa0(void *this,int *param_1)

{
  void *this_00;
  int iVar1;
  int local_c [3];
  
  this_00 = (void *)((int)this + 0x1a4);
  FUN_0042be60((int)this_00);
  (**(code **)(*param_1 + 0x14))(0);
  FUN_00416bd0();
  iVar1 = FUN_00429060(this_00,local_c + -2);
  if (iVar1 == 0) {
    iVar1 = LightMapMaker_42c380(this_00,param_1);
    if (iVar1 == 0) {
      *(undefined4 *)((int)this + 0x664) = 1;
      return 0;
    }
  }
  FUN_0042be60((int)this_00);
  FUN_00489880((int)this,0x2a,(char)param_1);
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CServerMgr__LoadWorld_004dcab0);
  }
  return 0x2a;
}


/* 00486b80 size=687 */

undefined4 __fastcall FUN_00486b80(int param_1)

{
  char cVar1;
  void *pvVar2;
  uint *_Source;
  uint *puVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  char *pcVar10;
  byte *pbVar11;
  char *pcVar12;
  undefined1 local_394 [4];
  int local_390;
  void *local_38c;
  void *local_388;
  undefined4 local_384;
  char local_380 [128];
  char local_300 [128];
  char local_280 [128];
  byte local_200 [512];
  
  if (*(char *)(param_1 + 0x66c) == '\0') {
    return 0;
  }
  uVar7 = 0xffffffff;
  pcVar10 = (char *)(param_1 + 0x66c);
  do {
    pcVar12 = pcVar10;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar12 = pcVar10 + 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar12;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pbVar9 = (byte *)(pcVar12 + -uVar7);
  pbVar11 = local_200;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pbVar11 = *(undefined4 *)pbVar9;
    pbVar9 = pbVar9 + 4;
    pbVar11 = pbVar11 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pbVar11 = *pbVar9;
    pbVar9 = pbVar9 + 1;
    pbVar11 = pbVar11 + 1;
  }
  local_390 = param_1;
  _Source = (uint *)FUN_004ba43e(local_200,(byte *)s___004d66fc);
  do {
    if (_Source == (uint *)0x0) {
      *(undefined4 *)(param_1 + 0x86c) = 1;
      return 0;
    }
    puVar3 = FUN_004bae50(_Source,&DAT_004d66f8);
    if (puVar3 == (uint *)0x0) {
      piVar4 = (int *)FUN_0047b5e0(param_1 + 0xc3c,(char *)_Source);
      if (piVar4 != (int *)0x0) {
        (**(code **)(**(int **)(*(int *)(param_1 + 0xb38) + 8) + 0x3c))(piVar4,local_394);
        (**(code **)(*piVar4 + 4))();
      }
    }
    else {
      _strncpy(local_300,(char *)_Source,(int)puVar3 - (int)_Source);
      uVar7 = 0xffffffff;
      pcVar10 = (char *)((int)puVar3 + 1);
      do {
        pcVar12 = pcVar10;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar12 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar12;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar10 = pcVar12 + -uVar7;
      pcVar12 = local_280;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar12 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar12 = pcVar12 + 1;
      }
      uVar7 = 0xffffffff;
      local_300[(int)puVar3 - (int)_Source] = '\0';
      pcVar10 = local_300;
      do {
        pcVar12 = pcVar10;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar12 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar12;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar10 = pcVar12 + -uVar7;
      pcVar12 = local_380;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar12 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar12 = pcVar12 + 1;
      }
      uVar7 = 0xffffffff;
      pcVar10 = local_380;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      for (uVar7 = ~uVar7; (0 < (int)(uVar7 - 1) && (local_380[uVar7 - 1] != '\\'));
          uVar7 = uVar7 - 1) {
        local_380[uVar7 - 1] = '\0';
      }
      piVar4 = FUN_0047b7b0(param_1 + 0xc3c,local_380);
      uVar7 = 0xffffffff;
      pcVar10 = local_300;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      local_38c = (void *)(~uVar7 - 1);
      uVar7 = 0xffffffff;
      pcVar10 = local_280;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      local_388 = (void *)(~uVar7 - 1);
      local_384 = piVar4;
      if (piVar4 != (int *)0x0) {
        do {
          pvVar2 = local_388;
          if ((*piVar4 == 1) &&
             (iVar5 = FUN_004c8310((byte *)piVar4[2],local_300,local_38c), iVar5 == 0)) {
            uVar7 = 0xffffffff;
            pcVar10 = (char *)piVar4[2];
            do {
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              cVar1 = *pcVar10;
              pcVar10 = pcVar10 + 1;
            } while (cVar1 != '\0');
            iVar5 = FUN_004c8310((byte *)((char *)piVar4[2] + ((~uVar7 - 1) - (int)pvVar2)),
                                 local_280,pvVar2);
            if ((iVar5 == 0) &&
               (piVar6 = (int *)FUN_0047b5e0(param_1 + 0xc3c,(char *)piVar4[2]),
               piVar6 != (int *)0x0)) {
              (**(code **)(**(int **)(*(int *)(local_390 + 0xb38) + 8) + 0x3c))(piVar6,local_394);
              (**(code **)(*piVar6 + 4))();
            }
          }
          piVar4 = (int *)piVar4[3];
        } while (piVar4 != (int *)0x0);
      }
      FUN_00440140((undefined *)local_384);
      param_1 = local_390;
    }
    _Source = (uint *)FUN_004ba43e((byte *)0x0,(byte *)s___004d66fc);
  } while( true );
}


/* 00486e30 size=156 */

undefined4 __fastcall FUN_00486e30(int param_1)

{
  char *_Source;
  int *piVar1;
  size_t _Count;
  uint local_100 [64];
  
  if (((*(int *)(param_1 + 0x664) != 0) && (*(int **)(param_1 + 0x668) != (int *)0x0)) &&
     (*(int *)(param_1 + 0xb38) != 0)) {
    _Count = 0xff;
    _Source = FUN_0047b9b0(param_1 + 0xc3c,*(int **)(param_1 + 0x668));
    _strncpy((char *)local_100,_Source,_Count);
    FUN_004c8d30(local_100);
    piVar1 = (int *)FUN_0047b5e0(param_1 + 0xc3c,(char *)local_100);
    if (piVar1 != (int *)0x0) {
      (**(code **)(**(int **)(*(int *)(param_1 + 0xb38) + 8) + 0x3c))(piVar1,param_1 + 0x870);
      (**(code **)(*piVar1 + 4))();
      return 0;
    }
  }
  return 1;
}


/* 00486ed0 size=202 */

void __thiscall FUN_00486ed0(void *this,int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  iVar5 = *(int *)((int)this + 0x9fc);
  if (iVar5 == (int)this + 0x9f8) {
    *(int *)((int)this + 0xac8) = param_1 + 0x28;
    return;
  }
  do {
    iVar1 = *(int *)(iVar5 + 8);
    puVar2 = FUN_00430f00(param_1 * 4 + 0xa0);
    puVar6 = *(undefined4 **)(iVar1 + 400);
    puVar7 = puVar2;
    for (uVar3 = *(uint *)((int)this + 0xac8) & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    puVar6 = puVar2 + *(int *)((int)this + 0xac8);
    for (iVar4 = 0x28; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    FUN_00430fe0(*(undefined **)(iVar1 + 400));
    *(undefined4 **)(iVar1 + 400) = puVar2;
    iVar5 = *(int *)(iVar5 + 4);
  } while (iVar5 != (int)this + 0x9f8);
  *(int *)((int)this + 0xac8) = param_1 + 0x28;
  return;
}


/* 00486fa0 size=357 */

undefined4 __cdecl
FUN_00486fa0(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
            undefined4 *param_6)

{
  char *pcVar1;
  char cVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  undefined4 *puVar6;
  char *pcVar7;
  
  *param_6 = 0;
  puVar6 = *(undefined4 **)(param_1 + 0xc1c);
  if (puVar6 == (undefined4 *)0x0) {
    FUN_004b7c60(param_1 + 0xc04,*(int *)(param_1 + 0xc0c));
    puVar6 = *(undefined4 **)(param_1 + 0xc1c);
    if (puVar6 == (undefined4 *)0x0) goto LAB_004870ca;
  }
  *(undefined4 *)(param_1 + 0xc1c) = *puVar6;
  if (puVar6 != (undefined4 *)0x0) {
    puVar6[0xb] = 0;
    puVar6[0xd] = 0;
    puVar6[0xe] = 0;
    puVar6[0xf] = 0;
    puVar6[0x10] = 0;
    puVar6[8] = 0;
    puVar6[0xd] = 0;
    puVar6[0xc] = 0;
    puVar6[9] = param_3;
    puVar6[7] = 0;
    puVar6[4] = *(undefined4 *)(param_2 + 0x380);
    puVar6[5] = *(undefined4 *)(param_2 + 900);
    puVar6[6] = *(undefined4 *)(param_2 + 900);
    if ((int *)puVar6[0xb] != (int *)0x0) {
      (**(code **)(*(int *)puVar6[0xb] + 8))();
    }
    puVar6[0xb] = 0;
    puVar6[10] = 0;
    puVar6[0x15] = 0;
    *(undefined2 *)(puVar6 + 0x16) = 0;
    *(undefined2 *)((int)puVar6 + 0x5a) = 0;
    pcVar1 = (char *)(param_2 + 0x300);
    puVar6[0x15] = *(uint *)(param_2 + 4) & 1;
    cVar2 = *pcVar1;
    puVar6[3] = 0;
    if (cVar2 != '\0') {
      uVar5 = 0xffffffff;
      pcVar7 = pcVar1;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar2 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar2 != '\0');
      piVar4 = FUN_00434d70(*(int **)(param_1 + 0xad0),(undefined4 *)pcVar1,~uVar5);
      puVar6[3] = piVar4;
      FUN_00434fe0((int)piVar4,param_4);
    }
    piVar4 = puVar6 + 0x11;
    puVar6[1] = puVar6;
    *puVar6 = puVar6;
    puVar6[0x13] = param_4;
    *piVar4 = param_1 + 0xaf0;
    piVar3 = *(int **)(param_1 + 0xaf4);
    puVar6[0x12] = piVar3;
    *piVar3 = (int)piVar4;
    *(int **)(*piVar4 + 4) = piVar4;
    *(int *)(param_1 + 0xaec) = *(int *)(param_1 + 0xaec) + 1;
    *param_6 = puVar6;
    return 0;
  }
LAB_004870ca:
  FUN_004356e0();
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_CreateServerData_004dcac8);
  }
  return 0x14;
}


/* 00487110 size=248 */

undefined4 __cdecl FUN_00487110(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  FUN_00487210(param_1,param_2);
  piVar3 = *(int **)(*(int *)(param_2 + 400) + 0xc);
  if (piVar3 != (int *)0x0) {
    FUN_00434e60(*(int **)(param_1 + 0xad0),piVar3);
  }
  if ((*(byte *)(param_2 + 0x124) & 0x80) != 0) {
    piVar3 = (int *)FUN_0047a3a0(param_1,param_2);
    if (piVar3 != (int *)0x0) {
      *(int *)(*piVar3 + 4) = piVar3[1];
      *(int *)piVar3[1] = *piVar3;
      piVar3[1] = (int)piVar3;
      *piVar3 = (int)piVar3;
      *(int *)(param_1 + 0xafc) = *(int *)(param_1 + 0xafc) + -1;
      FUN_00430fe0((undefined *)piVar3);
    }
  }
  FUN_004456b0(param_1,param_2,0,1);
  FUN_004456b0(param_1,param_2,1,0);
  FUN_004456b0(param_1,param_2,2,0);
  FUN_004456b0(param_1,param_2,3,0);
  iVar1 = *(int *)(param_2 + 400);
  piVar3 = (int *)(iVar1 + 0x44);
  *(undefined4 *)(*piVar3 + 4) = *(undefined4 *)(iVar1 + 0x48);
  **(int **)(iVar1 + 0x48) = *piVar3;
  *(int **)(iVar1 + 0x48) = piVar3;
  *piVar3 = (int)piVar3;
  *(int *)(param_1 + 0xaec) = *(int *)(param_1 + 0xaec) + -1;
  puVar2 = *(undefined4 **)(param_2 + 400);
  if ((int *)puVar2[0xb] != (int *)0x0) {
    (**(code **)(*(int *)puVar2[0xb] + 8))();
  }
  if ((puVar2 != (undefined4 *)0x0) && (param_1 != -0xc04)) {
    *puVar2 = *(undefined4 *)(param_1 + 0xc1c);
    *(undefined4 **)(param_1 + 0xc1c) = puVar2;
  }
  return 0;
}


/* 00487210 size=84 */

void __cdecl FUN_00487210(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_2 + 400);
  if ((iVar1 != 0) && (puVar2 = *(undefined4 **)(iVar1 + 0x20), puVar2 != (undefined4 *)0x0)) {
    iVar3 = *(int *)(*(int *)(iVar1 + 0x24) + 0x24 + *(int *)(param_1 + 0xa44) * 4);
    (**(code **)(*(int *)(iVar1 + 0x24) + 0x10))(puVar2);
    if ((puVar2 != (undefined4 *)0x0) && (iVar3 != -8)) {
      *puVar2 = *(undefined4 *)(iVar3 + 0x20);
      *(undefined4 **)(iVar3 + 0x20) = puVar2;
    }
    *(undefined4 *)(*(int *)(param_2 + 400) + 0x20) = 0;
  }
  return;
}


/* 00487270 size=756 */

int __cdecl
FUN_00487270(int *param_1,int *param_2,undefined4 param_3,ushort *param_4,undefined4 param_5,
            undefined4 param_6,undefined4 *param_7)

{
  ushort *puVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int *unaff_EBX;
  int unaff_ESI;
  int unaff_EDI;
  
  puVar1 = param_4;
  piVar3 = param_1;
  *param_7 = 0;
  if (param_1[0x199] == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_AddObjectToWorld_004dcae0);
    }
    return 0x15;
  }
  piVar2 = param_1 + 0xe5;
  iVar5 = FUN_0046a710(piVar2,param_4,&param_1);
  piVar4 = param_2;
  if (iVar5 != 0) {
    return iVar5;
  }
  param_2[2] = (int)param_1;
  iVar5 = FUN_00486fa0((int)piVar3,(int)puVar1,param_3,param_1,param_2,param_1 + 100);
  if (iVar5 != 0) {
    FUN_0046a800((int)piVar2,(int)param_1);
    return iVar5;
  }
  (**(code **)(*piVar4 + 4))(0xc,0,0);
  iVar5 = FUN_0047b2f0(piVar3,(int)unaff_EBX,puVar1);
  if (iVar5 != 0) {
    FUN_00487110((int)piVar3,(int)unaff_EBX);
    FUN_0046a800(unaff_ESI,(int)unaff_EBX);
    return iVar5;
  }
  iVar5 = FUN_00485330(piVar3,(int *)&param_1,(uint)param_2);
  if (iVar5 != 0) {
    FUN_00487110((int)piVar3,(int)unaff_EBX);
    FUN_0046a800(unaff_ESI,(int)unaff_EBX);
    return iVar5;
  }
  unaff_EBX[0x49] = 0x44;
  *(int **)(unaff_EBX[100] + 0x28) = param_1;
  *(short *)(unaff_EBX + 0x2e) = (short)param_1[2];
  *(undefined1 *)(piVar3[0x2c4] + (uint)*(ushort *)(unaff_EBX + 0x2e) * 8) = 1;
  *(int **)(piVar3[0x2c4] + 4 + (uint)*(ushort *)(unaff_EBX + 0x2e) * 8) = unaff_EBX;
  *(int **)(unaff_EBX[100] + 0x20) = piVar4;
  if (((char)unaff_EBX[0x2f] == '\x02') || ((char)unaff_EBX[0x2f] == '\t')) {
    FUN_0045eef0(unaff_EBX);
  }
  FUN_00479120((int)piVar3,unaff_EBX);
  (**(code **)(*piVar4 + 4))(1,puVar1,param_3);
  uVar6 = FUN_00479170(piVar3,unaff_EDI);
  if (((*(uint *)(unaff_EDI + 0x124) & 4) == 0) || ((*(uint *)(unaff_EDI + 0x124) & 1) != 0)) {
    FUN_004356e0();
  }
  else {
    if ((*(char *)(piVar3[0x2c4] + (uint)*(ushort *)(unaff_EDI + 0xb8) * 8) == '\x01') &&
       (*(int *)(piVar3[0x2c4] + (uint)*(ushort *)(unaff_EDI + 0xb8) * 8 + 4) != 0)) {
      if ((*(short *)(*(int *)(unaff_EDI + 400) + 0x58) == 0) && (piVar3[0x199] != 0)) {
        *(int *)(*(int *)(unaff_EDI + 400) + 0x50) = piVar3[0x2c8];
        piVar3[0x2c8] = unaff_EDI;
      }
      puVar1 = (ushort *)(*(int *)(unaff_EDI + 400) + 0x58);
      *puVar1 = *puVar1 | (ushort)uVar6;
      goto LAB_00487543;
    }
    FUN_004356e0();
  }
  if (0 < DAT_004e4420) {
    FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_SetObjectChangeFlags_004d961c);
  }
LAB_00487543:
  DAT_004ebf6c = DAT_004ebf6c + 0x20c;
  *param_1 = unaff_EDI;
  return 0;
}


/* 00487570 size=445 */

undefined4 __cdecl FUN_00487570(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  
  iVar1 = *(int *)(param_2 + 8);
  if (iVar1 == 0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_sm_RemoveObjectFromWorld_004dcaf8)
      ;
    }
    return 1;
  }
  iVar5 = *(int *)(iVar1 + 400);
  if (iVar5 != 0) {
    *(uint *)(iVar1 + 0x124) = *(uint *)(iVar1 + 0x124) | 1;
    if ((~*(uint *)(param_1 + 0x1a0) & 1) != 0) {
      for (iVar2 = *(int *)(iVar1 + 0x98); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x24)) {
        iVar4 = FUN_0047a090(param_1,CONCAT22((short)((uint)iVar5 >> 0x10),
                                              *(undefined2 *)(iVar2 + 0x1e)));
        iVar5 = 0;
        if (iVar4 != 0) {
          iVar5 = (**(code **)(**(int **)(*(int *)(iVar4 + 400) + 0x20) + 4))(10,0,0);
        }
      }
    }
    if ((*(uint *)(iVar1 + 0x124) & 0x100) != 0) {
      FUN_004751a0(param_1);
      FUN_00475580(param_1,iVar1);
      *(uint *)(iVar1 + 0x124) = *(uint *)(iVar1 + 0x124) & 0xfffffeff;
    }
    if (*(int *)(*(int *)(iVar1 + 400) + 0x1c) != 0) {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                     s_sm_RemoveObjectFromWorld_004dcaf8);
      }
      return 0x14;
    }
    FUN_004456b0(param_1,iVar1,0,1);
    piVar3 = *(int **)(*(int *)(iVar1 + 400) + 0x28);
    if (piVar3 != (int *)0x0) {
      FUN_00485490(param_1,piVar3);
      *(undefined1 *)(*(int *)(param_1 + 0xb10) + (uint)*(ushort *)(iVar1 + 0xb8) * 8) = 0;
      *(undefined4 *)(*(int *)(param_1 + 0xb10) + 4 + (uint)*(ushort *)(iVar1 + 0xb8) * 8) = 0;
    }
    FUN_0045ea90(iVar1);
    FUN_0045ead0(iVar1);
    FUN_00431720(iVar1);
    FUN_00487110(param_1,iVar1);
    *(undefined4 *)(iVar1 + 400) = 0;
  }
  FUN_0047b320(param_1,iVar1);
  DAT_004ebf6c = DAT_004ebf6c + -0x20c;
  uVar6 = FUN_0046a800(param_1 + 0x394,iVar1);
  return uVar6;
}


/* 00487730 size=119 */

undefined4 __cdecl FUN_00487730(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1;
  *(undefined4 *)(param_1 + 0xb30) = 0;
  FUN_00489940(param_1);
  param_1 = FUN_00434ff0(*(int *)(iVar1 + 0xb28));
  while (param_1 != 0) {
    iVar2 = FUN_00435040(&param_1);
    iVar2 = FUN_00434fd0(iVar2);
    *(uint *)(iVar2 + 0x20) = *(uint *)(iVar2 + 0x20) & 0xfffffffe;
  }
  if (param_2 == 0) {
    *(uint *)(iVar1 + 0x1a0) = *(uint *)(iVar1 + 0x1a0) & 0xffffffef;
    return 0;
  }
  *(uint *)(iVar1 + 0x1a0) = *(uint *)(iVar1 + 0x1a0) | 0x10;
  return 0;
}


/* 004877b0 size=51 */

undefined4 __cdecl FUN_004877b0(int param_1)

{
  (**(code **)(**(int **)(param_1 + 0xa30) + 0x44))();
  *(uint *)(param_1 + 0x1a0) = *(uint *)(param_1 + 0x1a0) & 0xffffffef;
  FUN_004888e0(param_1);
  FUN_004899b0(param_1);
  return 0;
}


/* 004877f0 size=262 */

undefined4 __cdecl FUN_004877f0(int *param_1)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  
  piVar4 = (int *)param_1[0x173];
  if (piVar4 != param_1 + 0x172) {
    do {
      iVar1 = piVar4[2];
      if (*(int *)(iVar1 + 0x1f8) != param_1[0x34e]) {
        piVar2 = *(int **)(*(int *)(iVar1 + 400) + 0x30);
        if (piVar2 != (int *)0x0) {
          pcVar3 = FUN_0047b9b0(param_1 + 0x30f,piVar2);
          FUN_0048a000(param_1,0,pcVar3);
        }
        iVar5 = 0x34;
        do {
          piVar2 = *(int **)(*(int *)(iVar1 + 400) + iVar5);
          if (piVar2 != (int *)0x0) {
            pcVar3 = FUN_0047b9b0(param_1 + 0x30f,piVar2);
            FUN_0048a000(param_1,2,pcVar3);
          }
          iVar5 = iVar5 + 4;
        } while (iVar5 < 0x44);
        piVar2 = *(int **)(*(int *)(iVar1 + 400) + 0x34);
        if (piVar2 != (int *)0x0) {
          pcVar3 = FUN_0047b9b0(param_1 + 0x30f,piVar2);
          FUN_0048a000(param_1,2,pcVar3);
        }
      }
      piVar4 = (int *)piVar4[1];
    } while (piVar4 != param_1 + 0x172);
  }
  for (piVar4 = (int *)param_1[0x17b]; piVar4 != param_1 + 0x17a; piVar4 = (int *)piVar4[1]) {
    piVar2 = *(int **)(*(int *)(piVar4[2] + 400) + 0x30);
    if (piVar2 != (int *)0x0) {
      pcVar3 = FUN_0047b9b0(param_1 + 0x30f,piVar2);
      FUN_0048a000(param_1,1,pcVar3);
    }
  }
  return 0;
}


/* 00487910 size=178 */

/* FUN_00487910: lifted from original x86 -> lt_lifted.c */


/* 004879d0 size=12 */

void FUN_004879d0(void)

{
  FUN_004b9cf5(&LAB_004879e0);
  return;
}


/* 00487b10 size=29 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00487b10(undefined4 param_1)

{
  undefined1 local_1;
  
  local_1 = (undefined1)((uint)param_1 >> 0x18);
  DAT_004ebf90 = local_1;
  DAT_004ebf94 = 0;
  _DAT_004ebf98 = 0;
  _DAT_004ebf9c = 0;
  return;
}


/* 00487b30 size=12 */

void FUN_00487b30(void)

{
  FUN_004b9cf5(&LAB_00487b40);
  return;
}


/* 00487b90 size=380 */

void __cdecl FUN_00487b90(int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  char *pcVar9;
  uint *puVar10;
  undefined1 uStack_152;
  undefined1 uStack_151;
  undefined1 *puStack_150;
  int iStack_14c;
  undefined1 auStack_148 [4];
  uint *puStack_144;
  undefined1 auStack_138 [16];
  undefined4 auStack_128 [2];
  undefined1 auStack_120 [32];
  uint auStack_100 [64];
  
  (**(code **)(*param_1 + 0x188))();
  uVar6 = 0xffffffff;
  do {
    pcVar9 = param_2;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar9 = param_2 + 1;
    cVar1 = *param_2;
    param_2 = pcVar9;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  puVar8 = (uint *)(pcVar9 + -uVar6);
  puVar10 = auStack_100;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar10 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar10 = puVar10 + 1;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(char *)puVar10 = (char)*puVar8;
    puVar8 = (uint *)((int)puVar8 + 1);
    puVar10 = (uint *)((int)puVar10 + 1);
  }
  FUN_004c8e64(auStack_100);
  auStack_148[0] = uStack_152;
  FUN_00414100(auStack_148,'\0');
  uVar6 = 0xffffffff;
  puVar8 = auStack_100;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    uVar7 = *puVar8;
    puVar8 = (uint *)((int)puVar8 + 1);
  } while ((char)uVar7 != '\0');
  uVar6 = ~uVar6 - 1;
  uVar3 = FUN_0042fe50(auStack_148,uVar6,'\x01');
  if ((char)uVar3 != '\0') {
    puVar8 = auStack_100;
    puVar10 = puStack_144;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar10 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar10 = puVar10 + 1;
    }
    for (uVar7 = uVar6 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(char *)puVar10 = (char)*puVar8;
      puVar8 = (uint *)((int)puVar8 + 1);
      puVar10 = (uint *)((int)puVar10 + 1);
    }
    FUN_0042fe30(auStack_148,uVar6);
  }
  FUN_0048b700(auStack_138,&uStack_151,0,&uStack_152);
  piVar4 = (int *)FUN_0048aaa0(auStack_120,(undefined4 *)auStack_148,auStack_138);
  piVar4 = (int *)FUN_0048a9a0(&DAT_004ebf78,auStack_128,piVar4);
  iVar2 = *piVar4;
  FUN_0048a7a0((int)auStack_120);
  FUN_0048ad20(auStack_138);
  if ((*(int *)(iVar2 + 0x28) != 0) &&
     (iStack_14c = **(int **)(iVar2 + 0x20), (int *)iStack_14c != *(int **)(iVar2 + 0x20))) {
    do {
      puStack_150 = &DAT_004cc108;
      if (*(undefined1 **)(iStack_14c + 0x20) != (undefined1 *)0x0) {
        puStack_150 = *(undefined1 **)(iStack_14c + 0x20);
      }
      puVar5 = *(undefined1 **)(iStack_14c + 0x10);
      if (puVar5 == (undefined1 *)0x0) {
        puVar5 = &DAT_004cc108;
      }
      (**(code **)(*param_1 + 0x184))(puVar5,&puStack_150,1);
      FUN_0048b860(&iStack_14c);
    } while (iStack_14c != *(int *)(iVar2 + 0x20));
  }
  if (puStack_144 != (uint *)0x0) {
    cVar1 = *(char *)((int)puStack_144 + -1);
    if ((cVar1 != '\0') && (cVar1 != -1)) {
      *(char *)((int)puStack_144 + -1) = cVar1 + -1;
      return;
    }
    FUN_00430df0((undefined *)((int)puStack_144 + -1));
  }
  return;
}


/* 00487fe0 size=748 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00487fe0(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  char *pcVar5;
  uint *puVar6;
  uint *puVar7;
  uint *puVar8;
  int *piVar9;
  uint uVar10;
  uint uVar11;
  void *this;
  undefined4 *puVar12;
  undefined1 local_19a;
  undefined1 local_199;
  uint *local_198;
  undefined1 local_194 [4];
  uint *local_190;
  uint local_18c;
  undefined4 local_188;
  undefined4 *local_184;
  undefined4 local_180;
  uint *local_17c;
  undefined1 local_170 [16];
  undefined1 local_160 [16];
  undefined4 local_150 [2];
  undefined4 local_148 [2];
  undefined1 local_140 [32];
  undefined1 local_120 [32];
  byte local_100 [256];
  
  if (DAT_004ebf84 == 0) {
    uVar10 = 0xffffffff;
    pcVar5 = (char *)&DAT_004dcb94;
    do {
      if (uVar10 == 0) break;
      uVar10 = uVar10 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    uVar10 = ~uVar10 - 1;
    uVar3 = FUN_0042fe50(&DAT_004ebf90,uVar10,'\x01');
    if ((char)uVar3 != '\0') {
      puVar4 = &DAT_004dcb94;
      puVar12 = DAT_004ebf94;
      for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *puVar12 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar12 = puVar12 + 1;
      }
      for (uVar11 = uVar10 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined1 *)puVar12 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        puVar12 = (undefined4 *)((int)puVar12 + 1);
      }
      _DAT_004ebf98 = uVar10;
      *(undefined1 *)((int)DAT_004ebf94 + uVar10) = 0;
    }
    puVar4 = (undefined4 *)FUN_004ba1fd(s_childmodel_map_004dcb84,&DAT_004d58b4);
    if (puVar4 != (undefined4 *)0x0) {
      local_184 = puVar4;
      pcVar5 = FUN_004ba4e2((char *)local_100,0x100,puVar4);
      while (pcVar5 != (char *)0x0) {
        puVar6 = (uint *)FUN_004ba43e(local_100,(byte *)s___004dcb7c);
        puVar7 = (uint *)FUN_004ba43e((byte *)0x0,(byte *)s___004dcb7c);
        puVar8 = (uint *)FUN_004ba43e((byte *)0x0,(byte *)s___004dcb7c);
        local_198 = puVar8;
        FUN_004c8e64(puVar6);
        FUN_004c8e64(puVar7);
        FUN_004c8e64(puVar8);
        if (((puVar6 != (uint *)0x0) && (puVar7 != (uint *)0x0)) && (puVar8 != (uint *)0x0)) {
          local_194[0] = local_19a;
          FUN_00414100(local_194,'\0');
          uVar10 = 0xffffffff;
          puVar8 = puVar7;
          do {
            if (uVar10 == 0) break;
            uVar10 = uVar10 - 1;
            uVar11 = *puVar8;
            puVar8 = (uint *)((int)puVar8 + 1);
          } while ((char)uVar11 != '\0');
          uVar10 = ~uVar10 - 1;
          uVar3 = FUN_0042fe50(local_194,uVar10,'\x01');
          if ((char)uVar3 != '\0') {
            puVar8 = local_190;
            for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
            for (uVar11 = uVar10 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
              *(char *)puVar8 = (char)*puVar7;
              puVar7 = (uint *)((int)puVar7 + 1);
              puVar8 = (uint *)((int)puVar8 + 1);
            }
            *(undefined1 *)((int)local_190 + uVar10) = 0;
            local_18c = uVar10;
          }
          (*(uint8_t*)((char*)&local_180+0)) = local_19a;
          FUN_00414100(&local_180,'\0');
          uVar10 = 0xffffffff;
          puVar7 = puVar6;
          do {
            if (uVar10 == 0) break;
            uVar10 = uVar10 - 1;
            uVar11 = *puVar7;
            puVar7 = (uint *)((int)puVar7 + 1);
          } while ((char)uVar11 != '\0');
          uVar10 = ~uVar10 - 1;
          uVar3 = FUN_0042fe50(&local_180,uVar10,'\x01');
          if ((char)uVar3 != '\0') {
            puVar7 = local_17c;
            for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
              *puVar7 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar7 = puVar7 + 1;
            }
            for (uVar11 = uVar10 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
              *(char *)puVar7 = (char)*puVar6;
              puVar6 = (uint *)((int)puVar6 + 1);
              puVar7 = (uint *)((int)puVar7 + 1);
            }
            FUN_0042fe30(&local_180,uVar10);
          }
          FUN_0048b700(local_160,&local_199,0,&local_19a);
          piVar9 = (int *)FUN_0048aaa0(local_140,&local_180,local_160);
          piVar9 = (int *)FUN_0048a9a0(&DAT_004ebf78,local_150,piVar9);
          iVar2 = *piVar9;
          FUN_0048a7a0((int)local_140);
          FUN_0048ad20(local_160);
          local_170[0] = local_199;
          FUN_00414100(local_170,'\0');
          piVar9 = (int *)FUN_0048ae10(local_120,local_194,local_170);
          piVar9 = (int *)FUN_0048ac20((void *)(iVar2 + 0x1c),local_148,piVar9);
          iVar2 = *piVar9;
          FUN_0048a930((int)local_120);
          FUN_00414100(local_170,'\x01');
          uVar10 = 0xffffffff;
          this = (void *)(iVar2 + 0x1c);
          puVar6 = local_198;
          do {
            if (uVar10 == 0) break;
            uVar10 = uVar10 - 1;
            uVar11 = *puVar6;
            puVar6 = (uint *)((int)puVar6 + 1);
          } while ((char)uVar11 != '\0');
          uVar10 = ~uVar10 - 1;
          uVar3 = FUN_0042fe50(this,uVar10,'\x01');
          if ((char)uVar3 != '\0') {
            puVar6 = local_198;
            puVar7 = *(uint **)(iVar2 + 0x20);
            for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
              *puVar7 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar7 = puVar7 + 1;
            }
            for (uVar11 = uVar10 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
              *(char *)puVar7 = (char)*puVar6;
              puVar6 = (uint *)((int)puVar6 + 1);
              puVar7 = (uint *)((int)puVar7 + 1);
            }
            FUN_0042fe30(this,uVar10);
          }
          FUN_00414100(&local_180,'\x01');
          if (local_190 != (uint *)0x0) {
            cVar1 = *(char *)((int)local_190 + -1);
            if ((cVar1 == '\0') || (cVar1 == -1)) {
              FUN_00430df0((char *)((int)local_190 + -1));
            }
            else {
              *(char *)((int)local_190 + -1) = cVar1 + -1;
            }
          }
          local_190 = (uint *)0x0;
          local_18c = 0;
          local_188 = 0;
          puVar4 = local_184;
        }
        pcVar5 = FUN_004ba4e2((char *)local_100,0x100,puVar4);
      }
    }
  }
  return;
}


