/* lithtech.exe decompilation - unnamed_0048c000 */
#include "ghidra_types.h"

/* 0048c000 size=67 */

void __fastcall FUN_0048c000(int *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = *(undefined4 **)(*param_1 + 8);
  if (puVar1 != DAT_004ebfb8) {
    for (puVar2 = (undefined4 *)*puVar1; puVar2 != DAT_004ebfb8; puVar2 = (undefined4 *)*puVar2) {
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


/* 0048c050 size=619 */

void __thiscall
FUN_0048c050(void *this,undefined4 *param_1,int param_2,int *param_3,undefined1 *param_4)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  
  piVar3 = (int *)FUN_00430de0(0x30);
  piVar3[1] = (int)param_3;
  piVar3[0xb] = 0;
  *piVar3 = DAT_004ebfb0;
  piVar3[2] = DAT_004ebfb0;
  FUN_0048ceb0(piVar3 + 3,param_4);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if ((param_3 != *(int **)((int)this + 4)) && (param_2 == DAT_004ebfb0)) {
    uVar4 = FUN_0045a710(param_4,(int)(param_3 + 3));
    if (-1 < (int)uVar4) {
      param_3[2] = (int)piVar3;
      if (param_3 == *(int **)(*(int *)((int)this + 4) + 8)) {
        *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
      }
      goto LAB_0048c0e4;
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
LAB_0048c0e4:
  piVar5 = piVar3;
  if (piVar3 != *(int **)(*(int *)((int)this + 4) + 4)) {
    do {
      piVar6 = (int *)piVar5[1];
      if (piVar6[0xb] != 0) break;
      piVar7 = *(int **)piVar6[1];
      if (piVar6 == piVar7) {
        iVar1 = ((undefined4 *)piVar6[1])[2];
        if (*(int *)(iVar1 + 0x2c) == 0) {
          piVar6[0xb] = 1;
          *(undefined4 *)(iVar1 + 0x2c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
          piVar5 = *(int **)(piVar5[1] + 4);
        }
        else {
          if (piVar5 == (int *)piVar6[2]) {
            piVar5 = (int *)piVar6[2];
            piVar6[2] = *piVar5;
            if (*piVar5 != DAT_004ebfb0) {
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
          *(undefined4 *)(piVar5[1] + 0x2c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
          piVar6 = *(int **)(piVar5[1] + 4);
          piVar7 = (int *)*piVar6;
          *piVar6 = piVar7[2];
          if (piVar7[2] != DAT_004ebfb0) {
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
LAB_0048c292:
          piVar6[1] = (int)piVar7;
        }
      }
      else {
        if (piVar7[0xb] != 0) {
          if (piVar5 == (int *)*piVar6) {
            iVar1 = *piVar6;
            *piVar6 = *(int *)(iVar1 + 8);
            if (*(int *)(iVar1 + 8) != DAT_004ebfb0) {
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
          *(undefined4 *)(piVar5[1] + 0x2c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
          piVar6 = *(int **)(piVar5[1] + 4);
          piVar7 = (int *)piVar6[2];
          piVar6[2] = *piVar7;
          if (*piVar7 != DAT_004ebfb0) {
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
          goto LAB_0048c292;
        }
        piVar6[0xb] = 1;
        piVar7[0xb] = 1;
        *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
        piVar5 = *(int **)(piVar5[1] + 4);
      }
    } while (piVar5 != *(int **)(*(int *)((int)this + 4) + 4));
  }
  *(undefined4 *)(*(int *)(*(int *)((int)this + 4) + 4) + 0x2c) = 1;
  *param_1 = piVar3;
  return;
}


/* 0048c2c0 size=1111 */

void __thiscall FUN_0048c2c0(void *this,undefined4 *param_1,int *param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int *piVar9;
  int *piVar10;
  int *local_c;
  undefined1 local_4 [4];
  
  piVar4 = param_2;
  FUN_0048b860((int *)&param_2);
  piVar10 = (int *)*piVar4;
  piVar6 = piVar4 + 2;
  local_c = piVar4;
  piVar9 = piVar6;
  if (piVar10 == DAT_004ebfc0) {
    piVar10 = (int *)*piVar6;
  }
  else {
    piVar2 = (int *)*piVar6;
    if (piVar2 != DAT_004ebfc0) {
      local_c = piVar2;
      for (piVar9 = (int *)*piVar2; piVar9 != DAT_004ebfc0; piVar9 = (int *)*piVar9) {
        local_c = piVar9;
      }
      piVar10 = (int *)local_c[2];
      piVar9 = local_c + 2;
    }
  }
  piVar2 = local_c;
  FUN_004b9b4f(local_4);
  if (local_c == piVar4) {
    piVar10[1] = local_c[1];
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar4) {
      *(int **)(*(int *)((int)this + 4) + 4) = piVar10;
    }
    else {
      piVar9 = (int *)piVar4[1];
      if ((int *)*piVar9 == piVar4) {
        *piVar9 = (int)piVar10;
      }
      else {
        piVar9[2] = (int)piVar10;
      }
    }
    piVar9 = *(int **)((int)this + 4);
    if ((int *)*piVar9 == piVar4) {
      if ((int *)*piVar6 == DAT_004ebfc0) {
        *piVar9 = piVar4[1];
      }
      else {
        piVar6 = piVar10;
        if ((int *)*piVar10 != DAT_004ebfc0) {
          piVar2 = (int *)*piVar10;
          do {
            piVar6 = piVar2;
            piVar2 = (int *)*piVar6;
          } while ((int *)*piVar6 != DAT_004ebfc0);
        }
        *piVar9 = (int)piVar6;
      }
    }
    if (*(int **)(*(int *)((int)this + 4) + 8) == piVar4) {
      if ((int *)*piVar4 == DAT_004ebfc0) {
        piVar6 = (int *)piVar4[1];
      }
      else {
        piVar9 = (int *)piVar10[2];
        piVar6 = piVar10;
        while (piVar4 = piVar9, piVar4 != DAT_004ebfc0) {
          piVar6 = piVar4;
          piVar9 = (int *)piVar4[2];
        }
      }
      *(int **)(*(int *)((int)this + 4) + 8) = piVar6;
    }
  }
  else {
    *(int **)(*piVar4 + 4) = local_c;
    *local_c = *piVar4;
    if (local_c == (int *)*piVar6) {
      piVar10[1] = (int)local_c;
    }
    else {
      piVar10[1] = local_c[1];
      *(int **)local_c[1] = piVar10;
      *piVar9 = *piVar6;
      *(int **)(*piVar6 + 4) = local_c;
    }
    if (*(int **)(*(int *)((int)this + 4) + 4) == piVar4) {
      *(int **)(*(int *)((int)this + 4) + 4) = local_c;
    }
    else {
      piVar6 = (int *)piVar4[1];
      if ((int *)*piVar6 == piVar4) {
        *piVar6 = (int)local_c;
      }
      else {
        piVar6[2] = (int)local_c;
      }
    }
    local_c = piVar4;
    piVar2[1] = piVar4[1];
    iVar3 = piVar2[0xb];
    piVar2[0xb] = piVar4[0xb];
    piVar4[0xb] = iVar3;
  }
  if (local_c[0xb] == 1) {
    if (piVar10 != *(int **)(*(int *)((int)this + 4) + 4)) {
      do {
        if (piVar10[0xb] != 1) break;
        piVar6 = *(int **)piVar10[1];
        if (piVar10 == piVar6) {
          piVar6 = (int *)((undefined4 *)piVar10[1])[2];
          if (piVar6[0xb] == 0) {
            piVar6[0xb] = 1;
            *(undefined4 *)(piVar10[1] + 0x2c) = 0;
            iVar3 = piVar10[1];
            piVar6 = *(int **)(iVar3 + 8);
            *(int *)(iVar3 + 8) = *piVar6;
            if ((int *)*piVar6 != DAT_004ebfc0) {
              ((int *)*piVar6)[1] = iVar3;
            }
            piVar6[1] = *(int *)(iVar3 + 4);
            if (iVar3 == *(int *)(*(int *)((int)this + 4) + 4)) {
              *(int **)(*(int *)((int)this + 4) + 4) = piVar6;
            }
            else {
              piVar9 = *(int **)(iVar3 + 4);
              if (iVar3 == *piVar9) {
                *piVar9 = (int)piVar6;
              }
              else {
                piVar9[2] = (int)piVar6;
              }
            }
            *piVar6 = iVar3;
            *(int **)(iVar3 + 4) = piVar6;
            piVar6 = *(int **)(piVar10[1] + 8);
          }
          if ((*(int *)(*piVar6 + 0x2c) != 1) || (*(int *)(piVar6[2] + 0x2c) != 1)) {
            if (*(int *)(piVar6[2] + 0x2c) == 1) {
              *(undefined4 *)(*piVar6 + 0x2c) = 1;
              iVar3 = *piVar6;
              piVar6[0xb] = 0;
              *piVar6 = *(int *)(iVar3 + 8);
              if (*(int **)(iVar3 + 8) != DAT_004ebfc0) {
                (*(int **)(iVar3 + 8))[1] = (int)piVar6;
              }
              *(int *)(iVar3 + 4) = piVar6[1];
              if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int *)(*(int *)((int)this + 4) + 4) = iVar3;
              }
              else {
                piVar9 = (int *)piVar6[1];
                if (piVar6 == (int *)piVar9[2]) {
                  piVar9[2] = iVar3;
                }
                else {
                  *piVar9 = iVar3;
                }
              }
              *(int **)(iVar3 + 8) = piVar6;
              piVar6[1] = iVar3;
              piVar6 = *(int **)(piVar10[1] + 8);
            }
            piVar6[0xb] = *(int *)(piVar10[1] + 0x2c);
            *(undefined4 *)(piVar10[1] + 0x2c) = 1;
            *(undefined4 *)(piVar6[2] + 0x2c) = 1;
            puVar7 = (undefined4 *)piVar10[1];
            puVar8 = (undefined4 *)puVar7[2];
            puVar7[2] = *puVar8;
            if ((int *)*puVar8 != DAT_004ebfc0) {
              ((int *)*puVar8)[1] = (int)puVar7;
            }
            puVar8[1] = puVar7[1];
            if (puVar7 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar8;
              *puVar8 = puVar7;
            }
            else {
              piVar6 = (int *)puVar7[1];
              if (puVar7 == (undefined4 *)*piVar6) {
                *piVar6 = (int)puVar8;
                *puVar8 = puVar7;
              }
              else {
                piVar6[2] = (int)puVar8;
                *puVar8 = puVar7;
              }
            }
            goto LAB_0048c686;
          }
        }
        else {
          if (piVar6[0xb] == 0) {
            piVar6[0xb] = 1;
            *(undefined4 *)(piVar10[1] + 0x2c) = 0;
            piVar6 = (int *)piVar10[1];
            iVar3 = *piVar6;
            *piVar6 = *(int *)(iVar3 + 8);
            if (*(int **)(iVar3 + 8) != DAT_004ebfc0) {
              (*(int **)(iVar3 + 8))[1] = (int)piVar6;
            }
            *(int *)(iVar3 + 4) = piVar6[1];
            if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
              *(int *)(*(int *)((int)this + 4) + 4) = iVar3;
            }
            else {
              piVar9 = (int *)piVar6[1];
              if (piVar6 == (int *)piVar9[2]) {
                piVar9[2] = iVar3;
              }
              else {
                *piVar9 = iVar3;
              }
            }
            *(int **)(iVar3 + 8) = piVar6;
            piVar6[1] = iVar3;
            piVar6 = *(int **)piVar10[1];
          }
          if ((*(int *)(piVar6[2] + 0x2c) != 1) || (*(int *)(*piVar6 + 0x2c) != 1)) {
            if (*(int *)(*piVar6 + 0x2c) == 1) {
              *(undefined4 *)(piVar6[2] + 0x2c) = 1;
              piVar9 = (int *)piVar6[2];
              piVar6[0xb] = 0;
              piVar6[2] = *piVar9;
              if ((int *)*piVar9 != DAT_004ebfc0) {
                ((int *)*piVar9)[1] = (int)piVar6;
              }
              piVar9[1] = piVar6[1];
              if (piVar6 == *(int **)(*(int *)((int)this + 4) + 4)) {
                *(int **)(*(int *)((int)this + 4) + 4) = piVar9;
              }
              else {
                piVar4 = (int *)piVar6[1];
                if (piVar6 == (int *)*piVar4) {
                  *piVar4 = (int)piVar9;
                }
                else {
                  piVar4[2] = (int)piVar9;
                }
              }
              *piVar9 = (int)piVar6;
              piVar6[1] = (int)piVar9;
              piVar6 = *(int **)piVar10[1];
            }
            piVar6[0xb] = *(int *)(piVar10[1] + 0x2c);
            *(undefined4 *)(piVar10[1] + 0x2c) = 1;
            *(undefined4 *)(*piVar6 + 0x2c) = 1;
            puVar7 = (undefined4 *)piVar10[1];
            puVar8 = (undefined4 *)*puVar7;
            *puVar7 = puVar8[2];
            if ((int *)puVar8[2] != DAT_004ebfc0) {
              ((int *)puVar8[2])[1] = (int)puVar7;
            }
            puVar8[1] = puVar7[1];
            if (puVar7 == *(undefined4 **)(*(int *)((int)this + 4) + 4)) {
              *(undefined4 **)(*(int *)((int)this + 4) + 4) = puVar8;
            }
            else {
              puVar5 = (undefined4 *)puVar7[1];
              if (puVar7 == (undefined4 *)puVar5[2]) {
                puVar5[2] = puVar8;
              }
              else {
                *puVar5 = puVar8;
              }
            }
            puVar8[2] = puVar7;
LAB_0048c686:
            puVar7[1] = puVar8;
            break;
          }
        }
        piVar6[0xb] = 0;
        piVar10 = (int *)piVar10[1];
      } while (piVar10 != *(int **)(*(int *)((int)this + 4) + 4));
    }
    piVar10[0xb] = 1;
  }
  FUN_004b9beb();
  iVar3 = local_c[8];
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar3 + -1));
    }
    else {
      *(char *)(iVar3 + -1) = cVar1 + -1;
    }
  }
  local_c[8] = 0;
  local_c[9] = 0;
  local_c[10] = 0;
  iVar3 = local_c[4];
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar3 + -1));
    }
    else {
      *(char *)(iVar3 + -1) = cVar1 + -1;
    }
  }
  local_c[4] = 0;
  local_c[5] = 0;
  local_c[6] = 0;
  FUN_00430df0((undefined *)local_c);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + -1;
  *param_1 = param_2;
  return;
}


/* 0048c720 size=235 */

void __thiscall FUN_0048c720(void *this,int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int *local_8;
  
  piVar3 = *(int **)((int)this + 4);
  piVar6 = *(int **)(*(int *)(param_1 + 4) + 4);
  piVar5 = piVar3;
  local_8 = piVar6;
  if (piVar6 != DAT_004ebfc0) {
    do {
      iVar1 = piVar6[0xb];
      piVar3 = (int *)FUN_00430de0(0x30);
      piVar3[0xb] = iVar1;
      piVar3[1] = (int)piVar5;
      if (local_8 == piVar6) {
        local_8 = piVar3;
      }
      piVar4 = FUN_0048cc80((int *)piVar6[2],piVar3);
      piVar3[2] = (int)piVar4;
      FUN_0048cff0((undefined1 *)(piVar3 + 3),(undefined1 *)(piVar6 + 3));
      *piVar5 = (int)piVar3;
      piVar6 = (int *)*piVar6;
      piVar5 = piVar3;
    } while (piVar6 != DAT_004ebfc0);
  }
  *piVar3 = (int)DAT_004ebfc0;
  *(int **)(*(int *)((int)this + 4) + 4) = local_8;
  puVar2 = *(undefined4 **)((int)this + 4);
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
  piVar3 = (int *)puVar2[1];
  if (piVar3 == DAT_004ebfc0) {
    *puVar2 = puVar2;
    *(int *)(*(int *)((int)this + 4) + 8) = *(int *)((int)this + 4);
    return;
  }
  for (piVar6 = (int *)*piVar3; piVar6 != DAT_004ebfc0; piVar6 = (int *)*piVar6) {
    piVar3 = piVar6;
  }
  *puVar2 = piVar3;
  piVar3 = *(int **)(*(int *)((int)this + 4) + 4);
  for (piVar6 = (int *)piVar3[2]; piVar6 != DAT_004ebfc0; piVar6 = (int *)piVar6[2]) {
    piVar3 = piVar6;
  }
  *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
  return;
}


/* 0048c810 size=153 */

void FUN_0048c810(int *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  
  if (param_1 != DAT_004ebfc0) {
    do {
      FUN_0048c810((int *)param_1[2]);
      iVar2 = param_1[8];
      piVar3 = (int *)*param_1;
      if (iVar2 != 0) {
        cVar1 = *(char *)(iVar2 + -1);
        if ((cVar1 == '\0') || (cVar1 == -1)) {
          FUN_00430df0((char *)(iVar2 + -1));
        }
        else {
          *(char *)(iVar2 + -1) = cVar1 + -1;
        }
      }
      param_1[8] = 0;
      param_1[9] = 0;
      param_1[10] = 0;
      iVar2 = param_1[4];
      if (iVar2 != 0) {
        cVar1 = *(char *)(iVar2 + -1);
        if ((cVar1 == '\0') || (cVar1 == -1)) {
          FUN_00430df0((char *)(iVar2 + -1));
        }
        else {
          *(char *)(iVar2 + -1) = cVar1 + -1;
        }
      }
      param_1[4] = 0;
      param_1[5] = 0;
      param_1[6] = 0;
      FUN_00430df0((undefined *)param_1);
      param_1 = piVar3;
    } while (piVar3 != DAT_004ebfc0);
  }
  return;
}


/* 0048c8b0 size=619 */

void __thiscall
FUN_0048c8b0(void *this,undefined4 *param_1,int param_2,int *param_3,undefined1 *param_4)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  
  piVar3 = (int *)FUN_00430de0(0x30);
  piVar3[1] = (int)param_3;
  piVar3[0xb] = 0;
  *piVar3 = DAT_004ebfc0;
  piVar3[2] = DAT_004ebfc0;
  FUN_0048cff0((undefined1 *)(piVar3 + 3),param_4);
  *(int *)((int)this + 0xc) = *(int *)((int)this + 0xc) + 1;
  if ((param_3 != *(int **)((int)this + 4)) && (param_2 == DAT_004ebfc0)) {
    uVar4 = FUN_0045a710(param_4,(int)(param_3 + 3));
    if (-1 < (int)uVar4) {
      param_3[2] = (int)piVar3;
      if (param_3 == *(int **)(*(int *)((int)this + 4) + 8)) {
        *(int **)(*(int *)((int)this + 4) + 8) = piVar3;
      }
      goto LAB_0048c944;
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
LAB_0048c944:
  piVar5 = piVar3;
  if (piVar3 != *(int **)(*(int *)((int)this + 4) + 4)) {
    do {
      piVar6 = (int *)piVar5[1];
      if (piVar6[0xb] != 0) break;
      piVar7 = *(int **)piVar6[1];
      if (piVar6 == piVar7) {
        iVar1 = ((undefined4 *)piVar6[1])[2];
        if (*(int *)(iVar1 + 0x2c) == 0) {
          piVar6[0xb] = 1;
          *(undefined4 *)(iVar1 + 0x2c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
          piVar5 = *(int **)(piVar5[1] + 4);
        }
        else {
          if (piVar5 == (int *)piVar6[2]) {
            piVar5 = (int *)piVar6[2];
            piVar6[2] = *piVar5;
            if (*piVar5 != DAT_004ebfc0) {
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
          *(undefined4 *)(piVar5[1] + 0x2c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
          piVar6 = *(int **)(piVar5[1] + 4);
          piVar7 = (int *)*piVar6;
          *piVar6 = piVar7[2];
          if (piVar7[2] != DAT_004ebfc0) {
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
LAB_0048caf2:
          piVar6[1] = (int)piVar7;
        }
      }
      else {
        if (piVar7[0xb] != 0) {
          if (piVar5 == (int *)*piVar6) {
            iVar1 = *piVar6;
            *piVar6 = *(int *)(iVar1 + 8);
            if (*(int *)(iVar1 + 8) != DAT_004ebfc0) {
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
          *(undefined4 *)(piVar5[1] + 0x2c) = 1;
          *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
          piVar6 = *(int **)(piVar5[1] + 4);
          piVar7 = (int *)piVar6[2];
          piVar6[2] = *piVar7;
          if (*piVar7 != DAT_004ebfc0) {
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
          goto LAB_0048caf2;
        }
        piVar6[0xb] = 1;
        piVar7[0xb] = 1;
        *(undefined4 *)(*(int *)(piVar5[1] + 4) + 0x2c) = 0;
        piVar5 = *(int **)(piVar5[1] + 4);
      }
    } while (piVar5 != *(int **)(*(int *)((int)this + 4) + 4));
  }
  *(undefined4 *)(*(int *)(*(int *)((int)this + 4) + 4) + 0x2c) = 1;
  *param_1 = piVar3;
  return;
}


/* 0048cb20 size=82 */

void __thiscall FUN_0048cb20(void *this,int param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = *(int **)(param_1 + 8);
  *(int *)(param_1 + 8) = *piVar1;
  if (*piVar1 != DAT_004ebfb8) {
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


/* 0048cb80 size=25 */

int __cdecl FUN_0048cb80(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  for (puVar1 = (undefined4 *)*param_1; puVar1 != DAT_004ebfb8; puVar1 = (undefined4 *)*puVar1) {
  }
  return;
}


/* 0048cba0 size=86 */

void __thiscall FUN_0048cba0(void *this,int *param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1;
  *param_1 = *(int *)(iVar1 + 8);
  if (*(int *)(iVar1 + 8) != DAT_004ebfb8) {
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


/* 0048cc00 size=27 */

int FUN_0048cc00(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_00430de0(0x14);
  *(undefined4 *)(iVar1 + 4) = param_1;
  *(undefined4 *)(iVar1 + 0x10) = param_2;
  return;
}


/* 0048cc20 size=81 */

void __fastcall FUN_0048cc20(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)*param_1;
  if ((piVar3[4] == 0) && (*(int **)(piVar3[1] + 4) == piVar3)) {
    *param_1 = piVar3[2];
    return;
  }
  iVar1 = *piVar3;
  if (iVar1 != DAT_004ebfb8) {
    for (iVar2 = *(int *)(iVar1 + 8); iVar2 != DAT_004ebfb8; iVar2 = *(int *)(iVar2 + 8)) {
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


/* 0048cc80 size=220 */

int * FUN_0048cc80(int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  piVar5 = param_1;
  if (param_1 == DAT_004ebfc0) {
    *param_2 = (int)DAT_004ebfc0;
    return param_1;
  }
  do {
    iVar1 = piVar5[0xb];
    piVar2 = (int *)FUN_00430de0(0x30);
    piVar2[1] = (int)param_2;
    piVar2[0xb] = iVar1;
    if (param_1 == piVar5) {
      param_1 = piVar2;
    }
    piVar3 = FUN_0048cc80((int *)piVar5[2],piVar2);
    piVar4 = piVar2 + 3;
    piVar2[2] = (int)piVar3;
    if (piVar4 != (int *)0x0) {
      *(char *)piVar4 = (char)piVar5[3];
      FUN_00414100(piVar4,'\0');
      FUN_0042fc30(piVar4,piVar5 + 3,0,DAT_004cc284);
      piVar4 = piVar2 + 7;
      *(char *)piVar4 = (char)piVar5[7];
      FUN_00414100(piVar4,'\0');
      FUN_0042fc30(piVar4,piVar5 + 7,0,DAT_004cc284);
    }
    *param_2 = (int)piVar2;
    piVar5 = (int *)*piVar5;
    param_2 = piVar2;
  } while (piVar5 != DAT_004ebfc0);
  *piVar2 = (int)DAT_004ebfc0;
  return param_1;
}


/* 0048cd60 size=27 */

int FUN_0048cd60(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_00430de0(0x30);
  *(undefined4 *)(iVar1 + 4) = param_1;
  *(undefined4 *)(iVar1 + 0x2c) = param_2;
  return;
}


/* 0048cd80 size=81 */

void __fastcall FUN_0048cd80(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)*param_1;
  if ((piVar3[0xb] == 0) && (*(int **)(piVar3[1] + 4) == piVar3)) {
    *param_1 = piVar3[2];
    return;
  }
  iVar1 = *piVar3;
  if (iVar1 != DAT_004ebfc0) {
    for (iVar2 = *(int *)(iVar1 + 8); iVar2 != DAT_004ebfc0; iVar2 = *(int *)(iVar2 + 8)) {
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


/* 0048cde0 size=81 */

void __fastcall FUN_0048cde0(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)*param_1;
  if ((piVar3[0xb] == 0) && (*(int **)(piVar3[1] + 4) == piVar3)) {
    *param_1 = piVar3[2];
    return;
  }
  iVar1 = *piVar3;
  if (iVar1 != DAT_004ebfb0) {
    for (iVar2 = *(int *)(iVar1 + 8); iVar2 != DAT_004ebfb0; iVar2 = *(int *)(iVar2 + 8)) {
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


/* 0048ce40 size=67 */

void __fastcall FUN_0048ce40(int *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = *(undefined4 **)(*param_1 + 8);
  if (puVar1 != DAT_004ebfb0) {
    for (puVar2 = (undefined4 *)*puVar1; puVar2 != DAT_004ebfb0; puVar2 = (undefined4 *)*puVar2) {
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


/* 0048ce90 size=17 */

void __cdecl FUN_0048ce90(undefined4 *param_1,undefined4 *param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = *param_2;
  }
  return;
}


/* 0048ceb0 size=317 */

/* FUN_0048ceb0: lifted from original x86 -> lt_lifted.c */


/* 0048cff0 size=254 */

void __cdecl FUN_0048cff0(undefined1 *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  if (param_1 != (undefined1 *)0x0) {
    uVar1 = *param_2;
    *(undefined4 *)(param_1 + 4) = 0;
    *param_1 = uVar1;
    *(undefined4 *)(param_1 + 8) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    FUN_0042fc30(param_1,param_2,0,DAT_004cc284);
    puVar3 = param_1 + 0x10;
    *puVar3 = param_2[0x10];
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x1c) = 0;
    uVar5 = *(uint *)(param_2 + 0x18);
    uVar6 = uVar5;
    if (DAT_004cc284 < uVar5) {
      uVar6 = DAT_004cc284;
    }
    if (puVar3 == param_2 + 0x10) {
      FUN_004599e0(puVar3,uVar6,DAT_004cc284);
      FUN_004599e0(puVar3,0,0);
      return;
    }
    if ((uVar6 != 0) && (uVar6 == uVar5)) {
      puVar2 = *(undefined1 **)(param_2 + 0x14);
      if (puVar2 == (undefined1 *)0x0) {
        puVar2 = &DAT_004cc108;
      }
      if ((byte)puVar2[-1] < 0xfe) {
        *(undefined4 *)(param_1 + 0x14) = 0;
        *(undefined4 *)(param_1 + 0x18) = 0;
        *(undefined4 *)(param_1 + 0x1c) = 0;
        puVar3 = *(undefined1 **)(param_2 + 0x14);
        if (puVar3 == (undefined1 *)0x0) {
          puVar3 = &DAT_004cc108;
        }
        *(undefined1 **)(param_1 + 0x14) = puVar3;
        *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_2 + 0x18);
        *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
        puVar3[-1] = puVar3[-1] + '\x01';
        return;
      }
    }
    uVar4 = FUN_0042fe50(puVar3,uVar6,'\x01');
    if ((char)uVar4 != '\0') {
      puVar7 = (undefined4 *)&DAT_004cc108;
      if (*(undefined4 **)(param_2 + 0x14) != (undefined4 *)0x0) {
        puVar7 = *(undefined4 **)(param_2 + 0x14);
      }
      puVar8 = *(undefined4 **)(param_1 + 0x14);
      for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar5 = uVar6 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      FUN_0042fe30(puVar3,uVar6);
    }
  }
  return;
}


/* 0048d0f0 size=302 */

undefined * __thiscall FUN_0048d0f0(void *this,byte param_1)

{
  void *this_00;
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined *puVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  undefined4 *local_10;
  int local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar2 = *(undefined4 **)((int)this + 0x14);
  this_00 = (void *)((int)this + 0x10);
  local_10 = (undefined4 *)*puVar2;
  if (((*(int *)((int)this + 0x1c) == 0) ||
      (piVar5 = (int *)FUN_004599d0(this_00,&local_c), local_10 != (undefined4 *)*piVar5)) ||
     (puVar2 != *(undefined4 **)((int)this + 0x14))) {
    while (local_10 != puVar2) {
      puVar6 = (undefined4 *)FUN_0048a8d0(&local_10,&local_c);
      FUN_0048c2c0(this_00,&local_4,(int *)*puVar6);
    }
  }
  else {
    FUN_0048c810((int *)(*(undefined4 **)((int)this + 0x14))[1]);
    *(undefined **)(*(int *)((int)this + 0x14) + 4) = DAT_004ebfc0;
    *(undefined4 *)((int)this + 0x1c) = 0;
    *(undefined4 *)*(undefined4 *)((int)this + 0x14) = *(undefined4 *)((int)this + 0x14);
    *(int *)(*(int *)((int)this + 0x14) + 8) = *(int *)((int)this + 0x14);
    FUN_004599d0(this_00,&local_8);
  }
  FUN_00430df0(*(undefined **)((int)this + 0x14));
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  FUN_004b9b4f(&local_10);
  puVar4 = DAT_004ebfc0;
  DAT_004ebfbc = DAT_004ebfbc + -1;
  puVar7 = (undefined *)0x0;
  if (DAT_004ebfbc == 0) {
    DAT_004ebfc0 = (undefined *)0x0;
    puVar7 = puVar4;
  }
  FUN_004b9beb();
  if (puVar7 != (undefined *)0x0) {
    FUN_00430df0(puVar7);
  }
  iVar3 = *(int *)((int)this + 4);
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar3 + -1));
    }
    else {
      *(char *)(iVar3 + -1) = cVar1 + -1;
    }
  }
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0048d220 size=120 */

undefined * __thiscall FUN_0048d220(void *this,byte param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)((int)this + 0x14);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar2 + -1));
    }
    else {
      *(char *)(iVar2 + -1) = cVar1 + -1;
    }
  }
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  iVar2 = *(int *)((int)this + 4);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      FUN_00430df0((char *)(iVar2 + -1));
    }
    else {
      *(char *)(iVar2 + -1) = cVar1 + -1;
    }
  }
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  if ((param_1 & 1) != 0) {
    FUN_00430df0(this);
  }
  return this;
}


/* 0048d470 size=183 */

int __cdecl FUN_0048d470(int param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  int local_20 [2];
  undefined4 local_18;
  undefined4 local_10;
  int local_c;
  
  if (1 < DAT_004e4420) {
    FUN_00436670((byte *)s__Client__loading_model___s_004dcdd0,*(undefined4 *)(param_2 + 0x1c));
  }
  if (param_4 == 0) {
    iVar1 = FUN_00417b50((void *)(param_1 + 0x16b8),param_2);
    if (iVar1 == 0) {
      FUN_0044df70((int)local_20);
      local_18 = 0;
      local_10 = 0;
      local_c = param_2;
      FUN_0044e0a0((void *)(param_1 + 0x16bc),local_20);
      return 0x54;
    }
    return 0x54;
  }
  iVar1 = clientmgr_48d890(param_1,*(char **)(param_2 + 0x1c),param_2,param_3);
  if (iVar1 == 0) {
    FUN_0048db40(param_1,*param_3,(char)param_2,1);
  }
  return iVar1;
}


/* 0048d530 size=146 */

int __cdecl
FUN_0048d530(int param_1,int *param_2,int *param_3,undefined4 *param_4,int param_5,int param_6)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = FUN_004047a0(*(int *)(param_1 + 0x1644),param_2,'\x01');
  *param_4 = piVar1;
  if (piVar1 == (int *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_LoadModel2_004dcdec);
    }
    return 0x16;
  }
  if (*piVar1 != 0) {
    *param_3 = *piVar1;
    return 0;
  }
  if (param_5 == 0) {
    return 0x54;
  }
  iVar2 = FUN_0048d470(param_1,(int)piVar1,param_3,param_6);
  return iVar2;
}


/* 0048db40 size=281 */

undefined4 __cdecl
FUN_0048db40(undefined4 param_1,undefined4 param_2,undefined1 param_3,undefined4 param_4)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined1 local_res0;
  undefined4 uStack00000110;
  int in_stack_00001518;
  undefined4 *in_stack_0000151c;
  int *in_stack_00001520;
  int in_stack_00001524;
  
  FUN_004ba7f0(local_res0);
  uStack00000110 = 0;
  if (*in_stack_00001520 != 0) {
    if (in_stack_0000151c != (undefined4 *)0x0) {
      (**(code **)*in_stack_0000151c)(1);
    }
    return 0;
  }
  uStack00000110 = in_stack_0000151c[0x20];
  iVar3 = FUN_00420a70(&param_3,(byte *)s_FadeSpriteTex_004dce20,0,1);
  if (iVar3 != 0) {
    uVar4 = FUN_00426ae0(in_stack_00001518,(int *)&local_res0);
    in_stack_0000151c[0x30] = uVar4;
  }
  piVar1 = in_stack_0000151c + 2;
  *piVar1 = in_stack_00001518 + 0x1204;
  piVar2 = *(int **)(in_stack_00001518 + 0x1208);
  in_stack_0000151c[3] = piVar2;
  *piVar2 = (int)piVar1;
  *(int **)(*piVar1 + 4) = piVar1;
  *in_stack_00001520 = (int)in_stack_0000151c;
  puVar5 = FUN_00445fe0(&PTR_LAB_004d6570,in_stack_00001520);
  FUN_00446060(in_stack_0000151c + 5,(int)puVar5);
  if ((in_stack_00001524 != 0) && ((*(byte *)((int)in_stack_00001520 + 0x19) & 1) != 0)) {
    for (iVar3 = *(int *)(in_stack_00001518 + 0x428); iVar3 != in_stack_00001518 + 0x424;
        iVar3 = *(int *)(iVar3 + 4)) {
      if (*(int **)(*(int *)(iVar3 + 8) + 0x1b4) == in_stack_00001520) {
        *(undefined4 **)(*(int *)(iVar3 + 8) + 0x1f8) = in_stack_0000151c;
      }
    }
    *(byte *)((int)in_stack_00001520 + 0x19) = *(byte *)((int)in_stack_00001520 + 0x19) & 0xfe;
  }
  return 0;
}


/* 0048dc60 size=24 */

bool __cdecl FUN_0048dc60(undefined4 param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = FUN_00468530((void *)(param_2 + 0x14),0x4d6570);
  return piVar1 != (int *)0x0;
}


/* 0048dc80 size=111 */

void __cdecl FUN_0048dc80(int param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  undefined3 extraout_var;
  
  iVar4 = *(int *)(param_1 + 0x428);
  while (iVar4 != param_1 + 0x424) {
    iVar3 = *(int *)(iVar4 + 4);
    piVar1 = (int *)(iVar4 + 8);
    iVar4 = iVar3;
    if (*(int *)(*piVar1 + 0x1f8) == param_2) {
      FUN_00412f00(param_1,*piVar1);
    }
  }
  *param_3 = 0;
  bVar5 = FUN_0048dc60(param_1,param_2);
  if (CONCAT31(extraout_var,bVar5) == 0) {
    puVar2 = (undefined4 *)(param_2 + 8);
    *(undefined4 *)(*(int *)(param_2 + 8) + 4) = *(undefined4 *)(param_2 + 0xc);
    **(undefined4 **)(param_2 + 0xc) = *puVar2;
    *(undefined4 **)(param_2 + 0xc) = puVar2;
    *puVar2 = puVar2;
  }
  return;
}


/* 0048de90 size=306 */

int __cdecl FUN_0048de90(int param_1,int *param_2,int *param_3,uint param_4)

{
  char cVar1;
  int *piVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  
  uVar3 = param_4;
  iVar6 = param_4 * 4 + 0x250;
  *(undefined4 *)(*param_3 + iVar6) = 0;
  pcVar4 = FUN_004046f0(*(int *)(param_1 + 0x1644),param_2);
  uVar7 = 0xffffffff;
  pcVar8 = pcVar4;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  if (3 < (int)(uVar7 - 1)) {
    param_4 = (uint)CONCAT12(pcVar4[uVar7 - 2],CONCAT11(pcVar4[uVar7 - 3],pcVar4[uVar7 - 4]));
    iVar5 = FUN_00436e20((char *)&param_4,&DAT_004db5b0);
    if (iVar5 != 0) {
      iVar6 = FUN_00426aa0(param_1,param_2,(int *)(*param_3 + 0x1c0 + uVar3 * 4));
      return iVar6;
    }
    iVar5 = FUN_00436e20((char *)&param_4,&DAT_004db5ac);
    if (iVar5 != 0) {
      iVar5 = setupobject_48d2d0(param_1,param_2,(int *)(*param_3 + iVar6));
      if (iVar5 != 0) {
        return iVar5;
      }
      FUN_0049aaf0((int *)(uVar3 * 0x14 + 0x260 + *param_3),*(int *)(*param_3 + iVar6));
      piVar2 = *(int **)(*param_3 + 0x268 + uVar3 * 0x14);
      if (piVar2 != (int *)0x0) {
        param_2[1] = *(int *)(*(int *)(*piVar2 + 0x24) + 0x1c);
        iVar6 = FUN_00426aa0(param_1,param_2,(int *)(*param_3 + 0x1c0 + uVar3 * 4));
        return iVar6;
      }
    }
  }
  return 1;
}


/* 0048e1e0 size=47 */

undefined4 __cdecl
FUN_0048e1e0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (*(code **)(&DAT_004dcd28 + *(char *)(param_2 + 0xbc) * 8) == (code *)0x0) {
    return 0;
  }
  uVar1 = (**(code **)(&DAT_004dcd28 + *(char *)(param_2 + 0xbc) * 8))
                    (param_1,param_2,param_3,param_4);
  return uVar1;
}


/* 0048e210 size=37 */

undefined4 __cdecl FUN_0048e210(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(code **)(&DAT_004dcd2c + *(char *)(param_2 + 0xbc) * 8) == (code *)0x0) {
    return 0;
  }
  uVar1 = (**(code **)(&DAT_004dcd2c + *(char *)(param_2 + 0xbc) * 8))(param_1,param_2);
  return uVar1;
}


/* 0048e270 size=294 */

undefined4 __cdecl
FUN_0048e270(LPCSTR param_1,undefined4 param_2,undefined4 *param_3,int param_4,int *param_5)

{
  undefined4 uVar1;
  int iVar2;
  code *pcVar3;
  code *pcVar4;
  undefined4 *puVar5;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  CHAR local_64 [100];
  
  iVar2 = FUN_00401790(param_1,&param_1);
  if (iVar2 == 0) {
    return 0;
  }
  bindmgr_4017f0((undefined4 *)param_1);
  uVar1 = param_2;
  FUN_004b9f62(local_64,(byte *)s_Get_sFunctions_004dce6c,param_2);
  pcVar3 = (code *)FUN_004018a0((undefined4 *)param_1,local_64);
  if (pcVar3 == (code *)0x0) {
    FUN_004017d0((undefined4 *)param_1);
    return 1;
  }
  FUN_004b9f62(local_64,(byte *)s_Get_sVersion_004dce5c,uVar1);
  pcVar4 = (code *)FUN_004018a0((undefined4 *)param_1,local_64);
  if (pcVar4 == (code *)0x0) {
    FUN_004017d0((undefined4 *)param_1);
    return 1;
  }
  iVar2 = (*pcVar4)();
  *param_5 = iVar2;
  if (iVar2 == param_4) {
    (*pcVar3)(&uStack_6c,&uStack_68);
    puVar5 = _malloc(0xc);
    *puVar5 = param_1;
    puVar5[1] = uStack_6c;
    puVar5[2] = uStack_68;
    *param_3 = puVar5;
    return 0xffffffff;
  }
  FUN_004017d0((undefined4 *)param_1);
  return 2;
}


/* 0048e3a0 size=24 */

void __cdecl FUN_0048e3a0(undefined4 *param_1)

{
  FUN_004017d0((undefined4 *)*param_1);
  FUN_004b9d3f((undefined *)param_1);
  return;
}


/* 0048e3c0 size=23 */

void __cdecl FUN_0048e3c0(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  *param_2 = *(undefined4 *)(param_1 + 4);
  *param_3 = *(undefined4 *)(param_1 + 8);
  return;
}


/* 0048e6a0 size=298 */

int __cdecl FUN_0048e6a0(void *param_1,int *param_2)

{
  int *piVar1;
  void *pvVar2;
  int iVar3;
  undefined4 *puVar4;
  
  pvVar2 = param_1;
  *(undefined2 *)((int)param_1 + 0x6c) = 0xffff;
  iVar3 = clientshell_415c40(param_1,(int)param_2);
  if (iVar3 == 0) {
    puVar4 = FUN_0046b170(&param_2,0x44c,0x44c);
    piVar1 = (int *)*puVar4;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 4))();
    }
    if (param_2 != (int *)0x0) {
      (**(code **)(*param_2 + 8))();
    }
    *(undefined1 *)piVar1[0x15] = 9;
    if (*(ushort *)(piVar1 + 0xe) + 1 < (uint)*(ushort *)((int)piVar1 + 0x36)) {
      if ((uint)piVar1[0x16] <= *(ushort *)(piVar1 + 0xd) + 1) {
        do {
          param_1 = (void *)((uint)param_1 & 0xffffff00);
          FUN_00414b10(piVar1 + 0x14,(undefined1 *)piVar1[0x16],(undefined1 *)&param_1,&DAT_004ecc58
                      );
        } while ((uint)piVar1[0x16] <= *(ushort *)(piVar1 + 0xd) + 1);
      }
      *(undefined1 *)((uint)*(ushort *)(piVar1 + 0xe) + piVar1[0x15]) = 0;
      *(short *)(piVar1 + 0xe) = (short)piVar1[0xe] + 1;
      *(short *)(piVar1 + 0xd) = (short)piVar1[0xd] + 1;
    }
    else {
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__WriteType_004d5cf0);
      }
      piVar1[0x10] = piVar1[0x10] | 4;
    }
    FUN_004657c0((void *)(*(int *)((int)pvVar2 + 0x78) + 0x510),piVar1,
                 *(float **)((int)pvVar2 + 0x34),0x80);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))();
    }
  }
  return iVar3;
}


/* 0048ee00 size=127 */

void __fastcall FUN_0048ee00(undefined2 *param_1)

{
  undefined2 *puVar1;
  int iVar2;
  
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined4 *)(param_1 + 2) = 1;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 6) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 10) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0xe) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x12) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x14) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x16) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1a) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1e) = 0;
  *(undefined1 *)(param_1 + 0x20) = 0;
  *(undefined1 *)(param_1 + 0x40) = 0;
  puVar1 = param_1 + 0x80;
  iVar2 = 4;
  do {
    *(undefined1 *)puVar1 = 0;
    puVar1 = puVar1 + 0x40;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  *(undefined1 *)(param_1 + 0x180) = 0;
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  *(undefined4 *)(param_1 + 0x1c2) = 0;
  *(undefined4 *)(param_1 + 0x1c4) = 1;
  return;
}


/* 0048ee80 size=49 */

void __fastcall FUN_0048ee80(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 4;
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined2 *)(param_1 + 2) = 0;
  puVar1 = param_1;
  do {
    puVar1[3] = 0;
    puVar1[4] = 0;
    *(undefined2 *)(puVar1 + 5) = 0;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + 3;
  } while (iVar2 != 0);
  param_1[0xf] = 0;
  param_1[0x10] = 1;
  return;
}


/* 0048eec0 size=188 */

int __cdecl FUN_0048eec0(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  
  uVar4 = *(uint *)(param_2 + 0x220);
  uVar3 = 0;
  if (*(int *)(param_5 + 0x300) != 0) {
    pbVar5 = (byte *)(param_5 + 0xc);
    do {
      if (uVar4 == 0) {
        return 0;
      }
      *(uint *)(uVar4 + 0x24) = (uint)*pbVar5;
      iVar1 = *(int *)(pbVar5 + 4);
      iVar2 = *(int *)(pbVar5 + 8);
      if (iVar1 == 0) {
        iVar1 = 1;
      }
      *(int *)(uVar4 + 0x20) = iVar1;
      if (iVar2 == 0) {
        iVar2 = 1;
      }
      *(int *)(uVar4 + 0x1c) = iVar2;
      if (param_4 != 0) {
        if (*pbVar5 == 0) {
          *(undefined4 *)(uVar4 + 0x34) = *(undefined4 *)(pbVar5 + -8);
        }
        else {
          *(undefined4 *)(uVar4 + 0x34) = *(undefined4 *)(pbVar5 + -0xc);
        }
      }
      *(undefined4 *)(uVar4 + 0x40) = *(undefined4 *)(pbVar5 + -8);
      iVar1 = FUN_0048ef80(param_1,param_2,uVar4,(uint)*(ushort *)(pbVar5 + -4),
                           (uint)*(ushort *)(pbVar5 + -2),param_3,param_4);
      if (iVar1 != 0) {
        return iVar1;
      }
      uVar4 = *(uint *)(uVar4 + 4);
      uVar3 = uVar3 + 1;
      pbVar5 = pbVar5 + 0x18;
    } while (uVar3 < *(uint *)(param_5 + 0x300));
  }
  return 0;
}


/* 0048ef80 size=240 */

undefined4 __cdecl
FUN_0048ef80(int param_1,int param_2,uint param_3,uint param_4,int param_5,int param_6,int param_7)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (((*(byte *)(param_2 + 0x88) & 0x80) == 0) || (param_6 == 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  uVar1 = param_4 & 0xffff3fff;
  if (uVar1 < *(uint *)(*(int *)(param_3 + 0x28) + 0x16c)) {
    iVar2 = *(int *)(*(int *)(*(int *)(param_3 + 0x28) + 0x168) + uVar1 * 0x20);
  }
  else {
    iVar2 = 0;
  }
  uVar4 = param_4 >> 0xe & 1;
  if ((param_4 & 0x8000) == 0) {
    *(ushort *)(param_3 + 0x18) = *(ushort *)(param_3 + 0x18) & 0xfffd;
  }
  else {
    *(byte *)(param_3 + 0x18) = *(byte *)(param_3 + 0x18) | 2;
  }
  if (uVar4 == 0) {
    *(ushort *)(param_3 + 0x18) = *(ushort *)(param_3 + 0x18) & 0xfffe;
  }
  else {
    *(byte *)(param_3 + 0x18) = *(byte *)(param_3 + 0x18) | 1;
    if ((param_7 == 0) && (uVar1 == *(ushort *)(param_3 + 0x38))) {
      return 0;
    }
  }
  FUN_00401200(param_3,uVar1,uVar3);
  FUN_00427200(*(int *)(param_1 + 0x78),param_2);
  if (iVar2 == 0) {
    iVar2 = 1;
  }
  else {
    iVar2 = FUN_00450020(iVar2);
  }
  uVar1 = (uint)(iVar2 * param_5) / 0xff;
  if (uVar4 == 0) {
    FUN_00401310(param_3,uVar1);
    return 0;
  }
  FUN_004011a0(param_3,uVar1,uVar3);
  return 0;
}


/* 0048f070 size=1818 */

int __cdecl FUN_0048f070(uint param_1,uint param_2,int *param_3,float param_4,uint param_5)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  float fVar4;
  undefined1 uVar5;
  ushort uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  float10 fVar10;
  float afStack_5c [3];
  uint uStack_50;
  int *piStack_4c;
  float fStack_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  uint local_2c;
  int *piStack_28;
  float fStack_24;
  float local_20 [4];
  undefined4 auStack_10 [4];
  
  fVar4 = param_4;
  piVar3 = param_3;
  shellnet_48f790((int)param_3,param_2 & 0xffff);
  uVar9 = param_2;
  if ((param_2 & 1) != 0) {
    uVar9 = (uint)(ushort)((ushort)param_2 | 0x200);
    uVar5 = FUN_004680f0((int)param_4);
    *(undefined1 *)((int)param_3 + 0xbd) = uVar5;
  }
  if ((uVar9 & 0x2020) != 0) {
    if ((char)param_3[0x2f] == '\x01') {
      iVar7 = FUN_0048f8c0(param_1,(int)param_3,(uint)param_4,(byte)~(byte)uVar9 & 1,1,param_5);
      if (iVar7 != 0) {
        return iVar7;
      }
    }
    else if ((char)param_3[0x2f] == '\x03') {
      iVar7 = FUN_00438530((int)param_4);
      param_3[0x71] = iVar7;
    }
  }
  if ((uVar9 & 8) != 0) {
    uVar8 = FUN_00438530((int)param_4);
    param_3[0x22] = uVar8 | param_3[0x22] & 0xfffb0000U;
    uVar6 = FUN_004384b0((int)param_4);
    param_3[0x23] = (uint)uVar6;
    iVar7 = FUN_00438530((int)param_4);
    param_3[0x24] = iVar7;
    if ((short)param_3[0x2e] == *(short *)(param_1 + 0x6c)) {
      param_3[0x22] = param_3[0x22] | 0x8000;
    }
  }
  if ((uVar9 & 0x40) == 0) {
LAB_0048f1e0:
    if ((uVar9 & 0x10) == 0) goto LAB_0048f232;
  }
  else {
    uVar5 = FUN_004680f0((int)param_4);
    *(undefined1 *)(param_3 + 0x25) = uVar5;
    uVar5 = FUN_004680f0((int)param_4);
    *(undefined1 *)((int)param_3 + 0x95) = uVar5;
    uVar5 = FUN_004680f0((int)param_4);
    *(undefined1 *)((int)param_3 + 0x96) = uVar5;
    uVar5 = FUN_004680f0((int)param_4);
    *(undefined1 *)((int)param_3 + 0x97) = uVar5;
    if ((char)param_3[0x2f] != '\x04') goto LAB_0048f1e0;
    uVar6 = FUN_004384b0((int)param_4);
    param_2 = (uint)uVar6;
    param_3[0x6c] = (int)(float)param_2;
    if ((uVar9 & 0x10) == 0) {
      FUN_004271e0(*(int *)(param_1 + 0x78),param_3);
      goto LAB_0048f1e0;
    }
  }
  fVar10 = FUN_004925c0(param_4);
  local_44 = (float)fVar10;
  fVar10 = FUN_004925c0(param_4);
  local_40 = (float)fVar10;
  if ((char)param_3[0x2f] == '\x03') {
    local_3c = 1.0;
  }
  else {
    fVar10 = FUN_004925c0(param_4);
    local_3c = (float)fVar10;
  }
  FUN_004270f0(*(int *)(param_1 + 0x78),param_3,&local_44);
LAB_0048f232:
  if ((uVar9 & 0x202) != 0) {
    if ((param_3[0x22] & 0x100U) == 0) {
      iVar7 = FUN_00416dd0(param_1);
      FUN_0043f3b0((int *)((int)param_4 + 8),&local_38,iVar7);
      (**(code **)(*(int *)((int)param_4 + 8) + 0x2c))(&local_2c);
    }
    else {
      fVar10 = FUN_004925c0(param_4);
      local_38 = (float)fVar10;
      fVar10 = FUN_004925c0(param_4);
      local_34 = (float)fVar10;
      fVar10 = FUN_004925c0(param_4);
      local_30 = (float)fVar10;
      (**(code **)(*(int *)((int)param_4 + 8) + 0x28))(&local_2c);
    }
    FUN_0046ff30(param_1,param_3,&local_38,afStack_5c,uVar9 & 1,uVar9 & 0x200);
  }
  if ((uVar9 & 0x404) != 0) {
    if ((param_3[0x22] & 0x100U) == 0) {
      FUN_0043f7a0((int *)((int)param_4 + 8));
    }
    else {
      (**(code **)(*(int *)((int)param_4 + 8) + 0x34))(local_20);
    }
    FUN_004701b0(param_1,param_3,local_20,uVar9 & 1,uVar9 & 0x600);
  }
  if ((uVar9 & 0x100) != 0) {
    uVar6 = *(ushort *)((int)param_4 + 0x38);
    uVar9 = uVar6 + 1;
    if ((uVar9 < *(uint *)((int)param_4 + 0x58)) && (uVar9 <= *(ushort *)((int)param_4 + 0x34))) {
      uVar5 = *(undefined1 *)(*(int *)((int)param_4 + 0x54) + (uint)uVar6);
      *(ushort *)((int)param_4 + 0x38) = uVar6 + 1;
      param_2 = CONCAT31((*(uint32_t*)((char*)&param_2+1)),uVar5);
    }
    else {
      *(uint *)((int)param_4 + 0x40) = *(uint *)((int)param_4 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
    }
    if ((char)param_2 == '\0') {
      uVar9 = param_3[0x49] & 0xfffffbff;
    }
    else {
      uVar9 = param_3[0x49] | 0x400;
    }
    param_3[0x49] = uVar9;
    iVar7 = *(int *)(param_1 + 0x78);
    puVar1 = (undefined4 *)param_3[0x26];
    while (puVar2 = puVar1, puVar2 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)puVar2[9];
      if ((puVar2 != (undefined4 *)0x0) && (iVar7 != -0x23c)) {
        *puVar2 = *(undefined4 *)(iVar7 + 0x254);
        *(undefined4 **)(iVar7 + 0x254) = puVar2;
      }
    }
    param_3[0x26] = 0;
    uVar9 = param_1;
    while( true ) {
      uVar6 = *(ushort *)((int)fVar4 + 0x38);
      uVar8 = uVar6 + 2;
      if ((uVar8 < *(uint *)((int)fVar4 + 0x58)) && (uVar8 <= *(ushort *)((int)fVar4 + 0x34))) {
        uVar9 = (uint)*(ushort *)(*(int *)((int)fVar4 + 0x54) + (uint)uVar6);
        *(ushort *)((int)fVar4 + 0x38) = uVar6 + 2;
      }
      else {
        *(uint *)((int)fVar4 + 0x40) = *(uint *)((int)fVar4 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      if ((short)uVar9 == -1) break;
      uVar6 = *(ushort *)((int)fVar4 + 0x38);
      uVar8 = uVar6 + 4;
      if ((uVar8 < *(uint *)((int)fVar4 + 0x58)) && (uVar8 <= *(ushort *)((int)fVar4 + 0x34))) {
        param_5 = *(uint *)(*(int *)((int)fVar4 + 0x54) + (uint)uVar6);
        *(ushort *)((int)fVar4 + 0x38) = uVar6 + 4;
      }
      else {
        *(uint *)((int)fVar4 + 0x40) = *(uint *)((int)fVar4 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      if ((piVar3[0x22] & 0x100U) == 0) {
        (**(code **)(*(int *)((int)fVar4 + 8) + 0x2c))(&local_2c);
        uStack_50 = local_2c;
        piStack_4c = piStack_28;
        fStack_48 = fStack_24;
        FUN_0043f7a0((int *)((int)fVar4 + 8));
      }
      else {
        uVar6 = *(ushort *)((int)fVar4 + 0x38);
        uVar8 = uVar6 + 4;
        if ((uVar8 < *(uint *)((int)fVar4 + 0x58)) && (uVar8 <= *(ushort *)((int)fVar4 + 0x34))) {
          param_2 = *(uint *)(*(int *)((int)fVar4 + 0x54) + (uint)uVar6);
          *(ushort *)((int)fVar4 + 0x38) = uVar6 + 4;
        }
        else {
          *(uint *)((int)fVar4 + 0x40) = *(uint *)((int)fVar4 + 0x40) | 2;
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
          }
        }
        uStack_50 = param_2;
        uVar6 = *(ushort *)((int)fVar4 + 0x38);
        uVar8 = uVar6 + 4;
        if ((uVar8 < *(uint *)((int)fVar4 + 0x58)) && (uVar8 <= *(ushort *)((int)fVar4 + 0x34))) {
          param_3 = *(int **)(*(int *)((int)fVar4 + 0x54) + (uint)uVar6);
          *(ushort *)((int)fVar4 + 0x38) = uVar6 + 4;
        }
        else {
          *(uint *)((int)fVar4 + 0x40) = *(uint *)((int)fVar4 + 0x40) | 2;
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
          }
        }
        piStack_4c = param_3;
        uVar6 = *(ushort *)((int)fVar4 + 0x38);
        uVar8 = uVar6 + 4;
        if ((uVar8 < *(uint *)((int)fVar4 + 0x58)) && (uVar8 <= *(ushort *)((int)fVar4 + 0x34))) {
          param_4 = *(float *)(*(int *)((int)fVar4 + 0x54) + (uint)uVar6);
          *(ushort *)((int)fVar4 + 0x38) = uVar6 + 4;
        }
        else {
          *(uint *)((int)fVar4 + 0x40) = *(uint *)((int)fVar4 + 0x40) | 2;
          FUN_004356e0();
          if (0 < DAT_004e4420) {
            FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
          }
        }
        fStack_48 = param_4;
        (**(code **)(*(int *)((int)fVar4 + 8) + 0x34))(auStack_10);
      }
      FUN_0046a860(*(int *)(param_1 + 0x78) + 0x1f0,(int)piVar3,(short)uVar9,param_5,&uStack_50,
                   auStack_10,(undefined4 *)0x0);
    }
    if ((char)piVar3[0x2f] == '\x01') {
      uVar6 = *(ushort *)((int)fVar4 + 0x38);
      uVar9 = uVar6 + 4;
      if ((uVar9 < *(uint *)((int)fVar4 + 0x58)) && (uVar9 <= *(ushort *)((int)fVar4 + 0x34))) {
        iVar7 = *(int *)(*(int *)((int)fVar4 + 0x54) + (uint)uVar6);
        *(ushort *)((int)fVar4 + 0x38) = uVar6 + 4;
        piVar3[0x93] = iVar7;
        return 0;
      }
      *(uint *)((int)fVar4 + 0x40) = *(uint *)((int)fVar4 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
      piVar3[0x93] = param_1;
    }
  }
  return 0;
}


/* 0048f8c0 size=50 */

int __cdecl FUN_0048f8c0(int param_1,int param_2,uint param_3,int param_4,int param_5,uint param_6)

{
  FUN_0048f900(param_1,param_3,param_6);
  FUN_0048eec0(param_1,param_2,param_4,param_5,param_6);
  return;
}


/* 0048f900 size=827 */

void __cdecl FUN_0048f900(undefined4 param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint *puVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  byte bVar6;
  undefined2 uVar7;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_8;
  uint local_4;
  
  uVar5 = param_3;
  uVar4 = param_2;
  *(undefined4 *)(param_3 + 0x300) = 0;
  bVar6 = FUN_004680f0(param_2);
  local_18 = (uint)bVar6;
  if (local_18 != 0) {
    do {
      uVar7 = FUN_004384b0(uVar4);
      uVar3 = *(ushort *)(uVar4 + 0x38);
      uVar1 = uVar3 + 1;
      if ((uVar1 < *(uint *)(uVar4 + 0x58)) && (uVar1 <= *(ushort *)(uVar4 + 0x34))) {
        bVar6 = *(byte *)(*(int *)(uVar4 + 0x54) + (uint)uVar3);
        *(ushort *)(uVar4 + 0x38) = uVar3 + 1;
        param_3 = (uint)bVar6;
      }
      else {
        *(uint *)(uVar4 + 0x40) = *(uint *)(uVar4 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      uVar3 = *(ushort *)(uVar4 + 0x38);
      uVar1 = uVar3 + 1;
      if ((uVar1 < *(uint *)(uVar4 + 0x58)) && (uVar1 <= *(ushort *)(uVar4 + 0x34))) {
        bVar6 = *(byte *)(*(int *)(uVar4 + 0x54) + (uint)uVar3);
        *(ushort *)(uVar4 + 0x38) = uVar3 + 1;
        param_2 = (uint)bVar6;
      }
      else {
        *(uint *)(uVar4 + 0x40) = *(uint *)(uVar4 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      uVar3 = *(ushort *)(uVar4 + 0x38);
      uVar1 = uVar3 + 4;
      if ((uVar1 < *(uint *)(uVar4 + 0x58)) && (uVar1 <= *(ushort *)(uVar4 + 0x34))) {
        local_8 = *(uint *)(*(int *)(uVar4 + 0x54) + (uint)uVar3);
        *(ushort *)(uVar4 + 0x38) = uVar3 + 4;
      }
      else {
        *(uint *)(uVar4 + 0x40) = *(uint *)(uVar4 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      uVar3 = *(ushort *)(uVar4 + 0x38);
      uVar1 = uVar3 + 4;
      if ((uVar1 < *(uint *)(uVar4 + 0x58)) && (uVar1 <= *(ushort *)(uVar4 + 0x34))) {
        local_4 = *(uint *)(*(int *)(uVar4 + 0x54) + (uint)uVar3);
        *(ushort *)(uVar4 + 0x38) = uVar3 + 4;
      }
      else {
        *(uint *)(uVar4 + 0x40) = *(uint *)(uVar4 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      uVar3 = *(ushort *)(uVar4 + 0x38);
      uVar1 = uVar3 + 1;
      if ((uVar1 < *(uint *)(uVar4 + 0x58)) && (uVar1 <= *(ushort *)(uVar4 + 0x34))) {
        bVar6 = *(byte *)(*(int *)(uVar4 + 0x54) + (uint)uVar3);
        *(ushort *)(uVar4 + 0x38) = uVar3 + 1;
        local_14 = (uint)bVar6;
      }
      else {
        *(uint *)(uVar4 + 0x40) = *(uint *)(uVar4 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      uVar3 = *(ushort *)(uVar4 + 0x38);
      uVar1 = uVar3 + 1;
      if ((uVar1 < *(uint *)(uVar4 + 0x58)) && (uVar1 <= *(ushort *)(uVar4 + 0x34))) {
        bVar6 = *(byte *)(*(int *)(uVar4 + 0x54) + (uint)uVar3);
        *(ushort *)(uVar4 + 0x38) = uVar3 + 1;
        local_10 = (uint)bVar6;
      }
      else {
        *(uint *)(uVar4 + 0x40) = *(uint *)(uVar4 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      if (*(uint *)(uVar5 + 0x300) < 0x20) {
        puVar2 = (uint *)(uVar5 + *(uint *)(uVar5 + 0x300) * 0x18);
        puVar2[1] = local_10 & 0xff;
        *(undefined2 *)(puVar2 + 2) = uVar7;
        *(ushort *)((int)puVar2 + 10) = (ushort)(byte)param_3;
        *(undefined1 *)(puVar2 + 3) = (undefined1)param_2;
        *puVar2 = local_14 & 0xff;
        puVar2[4] = local_8;
        puVar2[5] = local_4;
        *(int *)(uVar5 + 0x300) = *(int *)(uVar5 + 0x300) + 1;
      }
      local_18 = local_18 - 1;
    } while (local_18 != 0);
  }
  return;
}


/* 0048fc40 size=922 */

undefined4 __thiscall FUN_0048fc40(void *this,void *param_1,undefined4 *param_2,uint param_3)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 *puVar3;
  byte bVar4;
  undefined2 uVar5;
  undefined2 extraout_var;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  byte bVar9;
  undefined4 *puVar10;
  size_t sVar11;
  byte local_1;
  
  puVar3 = param_2;
  local_1 = (byte)((uint)this >> 0x18);
  bVar4 = FUN_004680f0((int)param_1);
  uVar8 = *(uint *)(param_2[0xf] + 4);
  if ((bVar4 & 0x20) == 0) {
    uVar8 = uVar8 & 0xfffffffe;
  }
  else {
    uVar8 = uVar8 | 1;
  }
  *(uint *)(param_2[0xf] + 4) = uVar8;
  uVar5 = 0;
  if ((bVar4 & 0x40) == 0) {
    *(undefined2 *)(param_3 + 0x34) = 0;
  }
  else if ((bVar4 & 0x80) == 0) {
    uVar1 = *(ushort *)((int)param_1 + 0x38);
    uVar8 = uVar1 + 1;
    if ((uVar8 < *(uint *)((int)param_1 + 0x58)) && (uVar8 <= *(ushort *)((int)param_1 + 0x34))) {
      local_1 = *(byte *)(*(int *)((int)param_1 + 0x54) + (uint)uVar1);
      *(ushort *)((int)param_1 + 0x38) = uVar1 + 1;
      iVar6 = 0;
    }
    else {
      *(uint *)((int)param_1 + 0x40) = *(uint *)((int)param_1 + 0x40) | 2;
      FUN_004356e0();
      iVar6 = DAT_004e4420;
      if (0 < DAT_004e4420) {
        iVar6 = FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,
                             s_CPacket__ReadType_004d6874);
      }
    }
    uVar5 = (undefined2)((uint)iVar6 >> 0x10);
    *(ushort *)(param_3 + 0x34) = (ushort)local_1;
  }
  else {
    uVar5 = FUN_004384b0((int)param_1);
    *(undefined2 *)(param_3 + 0x34) = uVar5;
    uVar5 = extraout_var;
  }
  if (*(short *)(param_3 + 0x34) != 0) {
    FUN_0046b3c0(param_1,(undefined4 *)(*(int *)(param_3 + 0x54) + 1),
                 CONCAT22(uVar5,*(short *)(param_3 + 0x34)));
    *(short *)(param_3 + 0x34) = *(short *)(param_3 + 0x34) + 1;
  }
  bVar9 = bVar4 & 0x1f;
  *param_2 = 2;
  if (bVar9 == 2) {
    sVar11 = 0x7f;
    pcVar7 = (char *)FUN_0046b370((int)param_1);
    _strncpy((char *)(param_2[0xf] + 0x80),pcVar7,sVar11);
  }
  else if (bVar9 == 9) {
    sVar11 = 0x7f;
    pcVar7 = (char *)FUN_0046b370((int)param_1);
    _strncpy((char *)(param_2[0xf] + 0x80),pcVar7,sVar11);
    uVar1 = *(ushort *)((int)param_1 + 0x38);
    uVar8 = uVar1 + 2;
    if ((uVar8 < *(uint *)((int)param_1 + 0x58)) && (uVar8 <= *(ushort *)((int)param_1 + 0x34))) {
      uVar5 = *(undefined2 *)(*(int *)((int)param_1 + 0x54) + (uint)uVar1);
      *(ushort *)((int)param_1 + 0x38) = uVar1 + 2;
      *(undefined2 *)(param_2[0xf] + 2) = uVar5;
    }
    else {
      *(uint *)((int)param_1 + 0x40) = *(uint *)((int)param_1 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
      *(undefined2 *)(param_2[0xf] + 2) = (*(uint16_t*)((char*)&param_2+0));
    }
  }
  else if (bVar9 == 1) {
    *param_2 = 2;
    uVar1 = *(ushort *)((int)param_1 + 0x38);
    uVar8 = uVar1 + 2;
    if ((uVar8 < *(uint *)((int)param_1 + 0x58)) && (uVar8 <= *(ushort *)((int)param_1 + 0x34))) {
      uVar2 = *(ushort *)(*(int *)((int)param_1 + 0x54) + (uint)uVar1);
      *(ushort *)((int)param_1 + 0x38) = uVar1 + 2;
      param_3 = (uint)uVar2;
    }
    else {
      *(uint *)((int)param_1 + 0x40) = *(uint *)((int)param_1 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
    }
    *(undefined2 *)(param_2 + 2) = (undefined2)param_3;
    puVar10 = param_2 + 5;
    param_3 = 4;
    do {
      puVar10[-2] = 2;
      uVar1 = *(ushort *)((int)param_1 + 0x38);
      uVar8 = uVar1 + 2;
      if ((uVar8 < *(uint *)((int)param_1 + 0x58)) && (uVar8 <= *(ushort *)((int)param_1 + 0x34))) {
        param_2 = (undefined4 *)(uint)*(ushort *)(*(int *)((int)param_1 + 0x54) + (uint)uVar1);
        *(ushort *)((int)param_1 + 0x38) = uVar1 + 2;
      }
      else {
        *(uint *)((int)param_1 + 0x40) = *(uint *)((int)param_1 + 0x40) | 2;
        FUN_004356e0();
        if (0 < DAT_004e4420) {
          FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
        }
      }
      *(short *)puVar10 = (short)param_2;
      puVar10 = puVar10 + 3;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
  }
  else if (bVar9 == 3) {
    uVar1 = *(ushort *)((int)param_1 + 0x38);
    uVar8 = uVar1 + 2;
    if ((uVar8 < *(uint *)((int)param_1 + 0x58)) && (uVar8 <= *(ushort *)((int)param_1 + 0x34))) {
      uVar2 = *(ushort *)(*(int *)((int)param_1 + 0x54) + (uint)uVar1);
      *(ushort *)((int)param_1 + 0x38) = uVar1 + 2;
      param_2 = (undefined4 *)(uint)uVar2;
    }
    else {
      *(uint *)((int)param_1 + 0x40) = *(uint *)((int)param_1 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
    }
    *puVar3 = 2;
    *(undefined2 *)(puVar3 + 2) = (*(uint16_t*)((char*)&param_2+0));
  }
  *(ushort *)puVar3[0xf] = (ushort)(bVar4 & 0x1f);
  return 0;
}


/* 0048ffe0 size=967 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0048ffe0(void *param_1,int param_2)

{
  uint uVar1;
  ushort uVar2;
  ushort uVar3;
  byte bVar4;
  undefined2 uVar5;
  byte *pbVar6;
  int iVar7;
  uint *puVar8;
  undefined1 local_159;
  uint local_158;
  int local_154 [2];
  uint local_14c;
  byte local_148 [12];
  uint local_13c [69];
  byte local_28;
  float local_24;
  float local_20;
  undefined1 local_1c;
  uint local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8;
  uint local_4;
  
  local_154[0] = 2;
  puVar8 = local_13c;
  for (iVar7 = 0x4f; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  local_154[1] = 0;
  local_14c = local_14c & 0xffff0000;
  uVar5 = FUN_004384b0(param_2);
  local_14c = CONCAT22((*(uint16_t*)((char*)&local_14c+2)),uVar5);
  pbVar6 = (byte *)FUN_00416d10(param_1,local_14c);
  if (pbVar6 == (byte *)0x0) {
    pbVar6 = local_148;
  }
  bVar4 = FUN_004680f0(param_2);
  *pbVar6 = bVar4;
  if ((bVar4 & 1) != 0) {
    uVar5 = FUN_004384b0(param_2);
    *(undefined2 *)(pbVar6 + 2) = uVar5;
  }
  uVar2 = *(ushort *)(pbVar6 + 2);
  local_13c[0] = uVar2 | 0x200;
  if ((*pbVar6 & 2) != 0) {
    bVar4 = FUN_004680f0(param_2);
    pbVar6[4] = bVar4;
  }
  local_28 = pbVar6[4];
  if ((local_13c[0] & 3) != 0) {
    if ((*pbVar6 & 4) != 0) {
      uVar5 = FUN_004384b0(param_2);
      *(undefined2 *)(pbVar6 + 6) = uVar5;
      bVar4 = FUN_004680f0(param_2);
      pbVar6[8] = bVar4;
    }
    local_24 = (float)*(ushort *)(pbVar6 + 6);
    local_158 = (uint)pbVar6[8];
    local_20 = (float)local_158 * (float)*(ushort *)(pbVar6 + 6) * _DAT_004cbaf0;
  }
  if ((local_13c[0] & 0x40) == 0) {
    local_1c = 100;
  }
  else {
    uVar3 = *(ushort *)(param_2 + 0x38);
    uVar1 = uVar3 + 1;
    if ((uVar1 < *(uint *)(param_2 + 0x58)) && (uVar1 <= *(ushort *)(param_2 + 0x34))) {
      local_159 = *(undefined1 *)(*(int *)(param_2 + 0x54) + (uint)uVar3);
      *(ushort *)(param_2 + 0x38) = uVar3 + 1;
      local_1c = local_159;
    }
    else {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
      local_1c = local_159;
    }
  }
  if ((local_13c[0] & 0x80) == 0) {
    local_18 = 0x3f800000;
  }
  else {
    uVar3 = *(ushort *)(param_2 + 0x38);
    uVar1 = uVar3 + 4;
    if ((uVar1 < *(uint *)(param_2 + 0x58)) && (uVar1 <= *(ushort *)(param_2 + 0x34))) {
      local_18 = *(uint *)(*(int *)(param_2 + 0x54) + (uint)uVar3);
      *(ushort *)(param_2 + 0x38) = uVar3 + 4;
    }
    else {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
      local_18 = local_158;
    }
  }
  if ((local_13c[0] & 3) != 0) {
    if ((uVar2 >> 0xb & 1) == 0) {
      iVar7 = FUN_00416dd0((int)param_1);
      FUN_0043f3b0((int *)(param_2 + 8),&local_14,iVar7);
    }
    else {
      iVar7 = *(int *)((int)param_1 + 0x88);
      if (iVar7 == 0) {
        local_c = 0;
        local_10 = 0;
        local_14 = 0;
      }
      else {
        local_14 = *(undefined4 *)(iVar7 + 0x194);
        local_10 = *(undefined4 *)(iVar7 + 0x198);
        local_c = *(undefined4 *)(iVar7 + 0x19c);
      }
    }
  }
  if ((local_13c[0] & 0x2000) != 0) {
    uVar2 = *(ushort *)(param_2 + 0x38);
    uVar1 = uVar2 + 1;
    if ((uVar1 < *(uint *)(param_2 + 0x58)) && (uVar1 <= *(ushort *)(param_2 + 0x34))) {
      local_159 = *(undefined1 *)(*(int *)(param_2 + 0x54) + (uint)uVar2);
      *(ushort *)(param_2 + 0x38) = uVar2 + 1;
    }
    else {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
    }
    local_8 = local_159;
  }
  if ((local_13c[0] & 0x4000) != 0) {
    uVar2 = *(ushort *)(param_2 + 0x38);
    uVar1 = uVar2 + 4;
    if ((uVar1 < *(uint *)(param_2 + 0x58)) && (uVar1 <= *(ushort *)(param_2 + 0x34))) {
      local_158 = *(uint *)(*(int *)(param_2 + 0x54) + (uint)uVar2);
      *(ushort *)(param_2 + 0x38) = uVar2 + 4;
    }
    else {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 2;
      FUN_004356e0();
      if (0 < DAT_004e4420) {
        FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_CPacket__ReadType_004d6874);
      }
    }
    local_4 = local_158;
  }
  clientmgr_411810(*(void **)((int)param_1 + 0x78),local_13c,local_154);
  return 0;
}


