/* lithtech.exe decompilation - module winclientde_impl */
#include "ghidra_types.h"

/* 0040cd70 size=236 */

/* repo: runtime/client/src/sys/win/winclientde_impl.cpp */

undefined4 __cdecl winclientde_impl_40cd70(int *param_1)

{
  if (param_1 == (int *)0x0) {
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTClient__DeleteSurface_004d62f0)
      ;
      return 1;
    }
  }
  else {
    if (DAT_004e5124 != 0) {
      if (param_1 != (int *)&DAT_004e4fa0) {
        *(int *)(*param_1 + 4) = param_1[1];
        *(int *)param_1[1] = *param_1;
        if (param_1 == DAT_004e5120) {
          DAT_004e5120 = (int *)DAT_004e5120[1];
        }
        DAT_004e511c = DAT_004e511c + -1;
        if (DAT_004e511c == 0) {
          DAT_004e5120 = (int *)0x0;
        }
        FUN_0040ce90((int)param_1);
        FUN_0040ce60((int)param_1);
        *param_1 = (int)DAT_004e4f98;
        DAT_004e4f98 = param_1;
      }
      return 0;
    }
    FUN_004356e0();
    if (0 < DAT_004e4420) {
      FUN_00436670(PTR_s_LT_ERROR___s_returned__s___s__004d52cc,s_ILTClient__DeleteSurface_004d62f0)
      ;
    }
  }
  return 1;
}


/* 0040e9e0 size=517 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/client/src/sys/win/winclientde_impl.cpp */

undefined4 __cdecl
winclientde_impl_40e9e0
          (undefined4 param_1,uint param_2,uint param_3,uint param_4,undefined4 param_5,
          undefined1 param_6)

{
  __builtin_trap(); /* STUB: decompiled body did not compile */
}


/* 0040ed90 size=1204 */

/* WARNING: Removing unreachable block (ram,0x0040f0af) */
/* WARNING: Removing unreachable block (ram,0x0040f032) */
/* WARNING: Removing unreachable block (ram,0x0040f07d) */
/* WARNING: Removing unreachable block (ram,0x0040f0fa) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* repo: runtime/client/src/sys/win/winclientde_impl.cpp,
   NOLF2/ClientShellDLL/ClientShellShared/ClientUtilities.cpp, Blood2/ClientShellDLL/Credits.cpp */

undefined4 __cdecl
winclientde_impl_40ed90
          (undefined *param_1,uint param_2,float *param_3,int param_4,int param_5,float param_6,
          float param_7,float param_8,int param_9,undefined1 param_10)

{
  __builtin_trap(); /* STUB: decompiled body did not compile */
}


