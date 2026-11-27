/* lithtech.exe decompilation - module serverde_impl */
#include "ghidra_types.h"

/* 004815a0 size=98 */

/* repo: runtime/server/src/serverde_impl.cpp */

int __cdecl serverde_impl_4815a0(byte *param_1)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  iVar2 = *(int *)(DAT_004ebfa4 + 0xc78);
  do {
    if (iVar2 == 0) {
      return 0;
    }
    pbVar3 = (byte *)(iVar2 + 4);
    pbVar5 = param_1;
    do {
      bVar1 = *pbVar3;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_004815e4:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_004815e9;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_004815e4;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_004815e9:
    if (iVar4 == 0) {
      return iVar2;
    }
    iVar2 = *(int *)(iVar2 + 0x54);
  } while( true );
}


/* 0049c8a0 size=62 */

/* repo: runtime/server/src/serverde_impl.cpp, runtime/kernel/net/src/sys/win/udpdriver.cpp,
   runtime/client/src/clientde_impl.cpp */

uint __cdecl serverde_impl_49c8a0(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  bool bVar6;
  
  uVar1 = 0;
  if (*(uint *)(param_2 + 8) != 0) {
    piVar3 = (int *)(*(int *)(param_2 + 4) + 0x88);
    do {
      iVar2 = 4;
      bVar6 = true;
      piVar4 = param_1;
      piVar5 = piVar3;
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar6 = *piVar4 == *piVar5;
        piVar4 = piVar4 + 1;
        piVar5 = piVar5 + 1;
      } while (bVar6);
      if (bVar6) {
        return uVar1;
      }
      uVar1 = uVar1 + 1;
      piVar3 = piVar3 + 0x29;
    } while (uVar1 < *(uint *)(param_2 + 8));
  }
  return 0xffffffff;
}


