/* lithtech.exe decompilation - module RenderPassDlg */
#include "ghidra_types.h"

/* 00437560 size=35 */

/* repo: tools/RenderStylesEditor/RenderPassDlg.cpp, FEAR/ObjectDLL/RenderTarget.cpp,
   FEAR/ObjectDLL/PolyGrid.cpp */

void __cdecl RenderPassDlg_437560(int param_1)

{
  undefined **ppuVar1;
  
  ppuVar1 = &PTR_DAT_004d8200;
  do {
    FUN_00426730(param_1,ppuVar1);
    ppuVar1 = ppuVar1 + 4;
  } while (ppuVar1 < s_Mirror_004d8250);
  return;
}


