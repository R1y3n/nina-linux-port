/* lithtech.exe decompilation - module cmoveabstract */
#include "ghidra_types.h"

/* 00418090 size=81 */

/* repo: runtime/client/src/cmoveabstract.cpp */

void __thiscall cmoveabstract_418090(void *this,float *param_1,float *param_2)

{
  *param_2 = *param_1 * *(float *)this +
             *(float *)((int)this + 8) * param_1[2] + *(float *)((int)this + 4) * param_1[1];
  param_2[1] = *(float *)((int)this + 0x18) * param_1[2] +
               *(float *)((int)this + 0x14) * param_1[1] + *(float *)((int)this + 0x10) * *param_1;
  param_2[2] = *(float *)((int)this + 0x28) * param_1[2] +
               *(float *)((int)this + 0x24) * param_1[1] + *(float *)((int)this + 0x20) * *param_1;
  return;
}


