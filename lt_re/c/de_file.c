/* lithtech.exe decompilation - module de_file */
#include "ghidra_types.h"

/* 00427ad0 size=558 */

/* repo: runtime/kernel/io/src/sys/win/de_file.cpp, runtime/kernel/io/src/sys/linux/linuxfile.cpp */

int * __cdecl de_file_427ad0(int *param_1,char *param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined8 uVar5;
  char *pcVar6;
  LARGE_INTEGER local_200;
  int *local_1f8;
  CHAR local_1f4 [500];
  
  if (param_1 == (int *)0x0) {
    return (int *)0x0;
  }
  if (*param_1 == 1) {
    FUN_004b9f62(local_1f4,(byte *)s__s__s_004d7a34,param_1 + 8);
    FUN_00424310(&local_200,0);
    local_1f8 = &DAT_004e95e4;
    FUN_00424400(&local_200);
    piVar2 = (int *)FUN_004ba1fd(local_1f4,&DAT_004d57f4);
    uVar5 = FUN_00424410((uint *)&local_200);
    *local_1f8 = *local_1f8 + (int)uVar5;
    if (piVar2 == (int *)0x0) {
      return (int *)0x0;
    }
    FUN_004ba72b(piVar2,0,2);
    iVar3 = FUN_004ba5a8((char *)piVar2);
    FUN_004ba72b(piVar2,0,0);
    FUN_0044df50((LPCRITICAL_SECTION)&DAT_004e9590);
    piVar4 = DAT_004e958c;
    if ((DAT_004e958c == (int *)0x0) &&
       (FUN_004b7c60(0x4e9574,DAT_004e957c), piVar4 = DAT_004e958c, DAT_004e958c == (int *)0x0)) {
      piVar4 = (int *)0x0;
    }
    else {
      DAT_004e958c = (int *)*piVar4;
      if (piVar4 != (int *)0x0) {
        linuxfile_427d20(piVar4);
        piVar4[1] = 0;
        piVar4[2] = 0;
        piVar4[3] = 0;
        piVar4[4] = 0;
        piVar4[5] = 0;
        piVar4[6] = 0;
        piVar4[7] = 0;
        piVar4[8] = 0;
        *piVar4 = (int)&PTR_FUN_004cc020;
      }
    }
    FUN_0044df60((LPCRITICAL_SECTION)&DAT_004e9590);
    piVar4[3] = (int)piVar2;
    piVar4[4] = (int)param_1;
    piVar4[1] = iVar3;
    piVar4[2] = 0;
    if (DAT_004e98ac < 1) {
      return piVar4;
    }
    pcVar6 = s_stream__p_open_file__s_size____u_004d7a5c;
  }
  else {
    iVar3 = FUN_004b6ed0((void *)param_1[1],param_2);
    if (iVar3 == 0) {
      return (int *)0x0;
    }
    iVar1 = *(int *)(iVar3 + 0xc);
    FUN_0044df50((LPCRITICAL_SECTION)&DAT_004e95c8);
    piVar4 = DAT_004e95c4;
    if ((DAT_004e95c4 == (int *)0x0) &&
       (FUN_004b7c60(0x4e95ac,DAT_004e95b4), piVar4 = DAT_004e95c4, DAT_004e95c4 == (int *)0x0)) {
      piVar4 = (int *)0x0;
    }
    else {
      DAT_004e95c4 = (int *)*piVar4;
      if (piVar4 != (int *)0x0) {
        piVar4[1] = 0;
        piVar4[2] = 0;
        piVar4[3] = 0;
        piVar4[4] = 0;
        piVar4[5] = 0;
        piVar4[6] = 0;
        piVar4[7] = 0;
        piVar4[8] = 0;
        *piVar4 = (int)&PTR_FUN_004cbff4;
      }
    }
    FUN_0044df60((LPCRITICAL_SECTION)&DAT_004e95c8);
    piVar4[6] = iVar3;
    piVar4[4] = (int)param_1;
    piVar4[1] = iVar1;
    piVar4[2] = 0;
    if (DAT_004e98ac < 1) {
      return piVar4;
    }
    pcVar6 = s_stream__p_open_rez__s_size____u_004d7a3c;
  }
  FUN_00436670((byte *)pcVar6,piVar4);
  return piVar4;
}


/* 00427f40 size=916 */

/* repo: runtime/kernel/io/src/sys/win/de_file.cpp */

undefined4 __cdecl de_file_427f40(int *param_1,char *param_2,uint *param_3)

{
  char cVar1;
  undefined4 *puVar2;
  HANDLE pvVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  char *pcVar10;
  int iVar11;
  uint *puVar12;
  char *pcVar13;
  undefined *puVar14;
  int local_1a0;
  char local_198 [8];
  CHAR local_190 [400];
  
  if (param_1 == (int *)0x0) {
    return 0;
  }
  if (*param_1 == 1) {
    puVar2 = (undefined4 *)param_3[0x43];
    if (puVar2 == (undefined4 *)0x0) {
      FUN_004b9f62(local_190,(byte *)s__s__s_____004d7ac0,param_1 + 8);
      puVar2 = FUN_00430f00(0x130);
      puVar9 = puVar2 + 1;
      *puVar2 = param_1;
      pvVar3 = FUN_004bb45b(local_190,puVar9);
      puVar2[0x47] = pvVar3;
      param_3[0x43] = (uint)puVar2;
    }
    else {
      puVar9 = puVar2 + 1;
      pvVar3 = (HANDLE)FUN_004bb528((HANDLE)puVar2[0x47],puVar9);
    }
    if (pvVar3 != (HANDLE)0xffffffff) {
      do {
        if (*(char *)(puVar2 + 6) != '.') {
          _strncpy((char *)(param_3 + 1),(char *)(puVar2 + 6),0xff);
          param_3[0x41] = puVar2[4];
          param_3[0x42] = puVar2[5];
          *param_3 = ~*puVar9 >> 4 & 1;
          return 1;
        }
        iVar4 = FUN_004bb528((HANDLE)puVar2[0x47],puVar9);
      } while (iVar4 != -1);
    }
    param_3[0x43] = 0;
    if ((HANDLE)puVar2[0x47] != (HANDLE)0xffffffff) {
      FUN_004bb5f0((HANDLE)puVar2[0x47]);
    }
    FUN_00430fe0((undefined *)puVar2);
    return 0;
  }
  puVar2 = (undefined4 *)param_3[0x43];
  if (puVar2 != (undefined4 *)0x0) {
    if (puVar2[0x4a] == 0) {
      iVar4 = FUN_004b5700(puVar2[0x4b]);
      puVar2[0x4b] = iVar4;
      if (iVar4 == 0) {
        puVar14 = (undefined *)param_3[0x43];
LAB_0042824a:
        FUN_00430fe0(puVar14);
        param_3[0x43] = 0;
        return 0;
      }
    }
    else {
      iVar4 = FUN_004b5780(puVar2[0x4a]);
      puVar2[0x4a] = iVar4;
      while (iVar4 == 0) {
        iVar4 = FUN_004b5740(puVar2[0x49]);
        puVar2[0x49] = iVar4;
        if (iVar4 == 0) {
          iVar4 = FUN_004b56e0(puVar2[0x48]);
          puVar2[0x4b] = iVar4;
          if (iVar4 == 0) {
            puVar14 = (undefined *)param_3[0x43];
            goto LAB_0042824a;
          }
          break;
        }
        iVar4 = FUN_004b5760(iVar4);
        puVar2[0x4a] = iVar4;
      }
    }
    goto LAB_00428167;
  }
  iVar4 = FUN_004b6ef0((void *)param_1[1],param_2);
  iVar11 = 0;
  if (iVar4 == 0) {
    return 0;
  }
  iVar5 = FUN_004b5720(iVar4);
  if (iVar5 == 0) {
    local_1a0 = 0;
LAB_004280b0:
    iVar11 = FUN_004b56e0(iVar4);
    if (iVar11 == 0) {
      return 0;
    }
  }
  else {
    local_1a0 = FUN_004b5760(iVar5);
    if (local_1a0 == 0) goto LAB_004280b0;
  }
  puVar2 = FUN_00430f00(0x130);
  param_3[0x43] = (uint)puVar2;
  puVar2[0x48] = iVar4;
  puVar2[0x4b] = iVar11;
  *puVar2 = param_1;
  puVar2[0x49] = iVar5;
  puVar2[0x4a] = local_1a0;
LAB_00428167:
  if ((undefined4 *)puVar2[0x4a] == (undefined4 *)0x0) {
    if ((undefined4 *)puVar2[0x4b] == (undefined4 *)0x0) {
      return 0;
    }
    _strncpy((char *)(param_3 + 1),*(char **)puVar2[0x4b],0xff);
    uVar7 = *(uint *)(puVar2[0x4b] + 0x14);
    *param_3 = 0;
    param_3[0x42] = 0;
    param_3[0x41] = uVar7;
    return 1;
  }
  _strncpy((char *)(param_3 + 1),*(char **)puVar2[0x4a],0xfc);
  pcVar10 = local_198;
  uVar6 = FUN_004b50a0(puVar2[0x4a]);
  FUN_004b6aa0(uVar6,pcVar10);
  uVar7 = 0xffffffff;
  pcVar10 = &DAT_004d7abc;
  do {
    pcVar13 = pcVar10;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar13 = pcVar10 + 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar13;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  iVar4 = -1;
  puVar9 = param_3 + 1;
  do {
    puVar12 = puVar9;
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    puVar12 = (uint *)((int)puVar9 + 1);
    uVar8 = *puVar9;
    puVar9 = puVar12;
  } while ((char)uVar8 != '\0');
  pcVar10 = pcVar13 + -uVar7;
  pcVar13 = (char *)((int)puVar12 + -1);
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar13 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar13 = pcVar13 + 1;
  }
  uVar7 = 0xffffffff;
  pcVar10 = local_198;
  do {
    pcVar13 = pcVar10;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar13 = pcVar10 + 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar13;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  iVar4 = -1;
  puVar9 = param_3 + 1;
  do {
    puVar12 = puVar9;
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    puVar12 = (uint *)((int)puVar9 + 1);
    uVar8 = *puVar9;
    puVar9 = puVar12;
  } while ((char)uVar8 != '\0');
  pcVar10 = pcVar13 + -uVar7;
  pcVar13 = (char *)((int)puVar12 + -1);
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar13 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar13 = pcVar13 + 1;
  }
  uVar7 = *(uint *)(puVar2[0x4a] + 8);
  *param_3 = 1;
  param_3[0x41] = uVar7;
  param_3[0x42] = *(uint *)(puVar2[0x4a] + 0xc);
  return 1;
}


