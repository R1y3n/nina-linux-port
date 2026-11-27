/* lithtech.exe decompilation - module unnamed_0042 */
#include "ghidra_types.h"

/* 0042ffdf size=33 */

undefined * Catch_0042ffdf(void)

{
  size_t sVar1;
  undefined4 uVar2;
  int unaff_EBP;
  
  *(int *)(unaff_EBP + -0x1c) = *(int *)(unaff_EBP + 8);
  sVar1 = *(int *)(unaff_EBP + 8) + 2;
  if ((int)sVar1 < 0) {
    sVar1 = 0;
  }
  uVar2 = FUN_00430de0(sVar1);
  *(undefined4 *)(unaff_EBP + -0x18) = uVar2;
  return &DAT_00430000;
}


