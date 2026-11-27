/* lithtech.exe decompilation - module moveobject */
#include "ghidra_types.h"

/* 00462e70 size=172 */

/* repo: runtime/shared/src/moveobject.cpp */

void __cdecl
moveobject_462e70(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                 float *param_6)

{
  float fVar1;
  
  if (*param_4 <= *param_2) {
    fVar1 = *param_4;
  }
  else {
    fVar1 = *param_2;
  }
  *param_6 = fVar1;
  if (param_4[1] <= param_2[1]) {
    fVar1 = param_4[1];
  }
  else {
    fVar1 = param_2[1];
  }
  param_6[1] = fVar1;
  if (param_4[2] <= param_2[2]) {
    fVar1 = param_4[2];
  }
  else {
    fVar1 = param_2[2];
  }
  param_6[2] = fVar1;
  if (*param_1 <= *param_3) {
    fVar1 = *param_3;
  }
  else {
    fVar1 = *param_1;
  }
  *param_5 = fVar1;
  if (param_1[1] <= param_3[1]) {
    fVar1 = param_3[1];
  }
  else {
    fVar1 = param_1[1];
  }
  param_5[1] = fVar1;
  if (param_3[2] < param_1[2]) {
    param_5[2] = param_1[2];
    return;
  }
  param_5[2] = param_3[2];
  return;
}


