/* lithtech.exe decompilation - module KeyPad */
#include "ghidra_types.h"

/* 004581d0 size=3715 */

/* repo: NOLF/ObjectDLL/KeyPad.cpp, FEAR/Shared/FXDB.h, FEAR/ObjectDLL/SpecialMove.cpp */

undefined1 __thiscall KeyPad_4581d0(void *this,int *param_1)

{
  uint uVar1;
  undefined1 uVar2;
  undefined3 extraout_var;
  int iVar3;
  undefined4 *puVar4;
  void *pvVar5;
  undefined1 *puVar6;
  int *piVar7;
  byte *pbVar8;
  undefined4 uVar9;
  undefined *puVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int *piVar14;
  undefined4 *puVar15;
  int *local_184;
  undefined1 uStack_17d;
  undefined1 auStack_17c [4];
  undefined *puStack_178;
  undefined4 *puStack_174;
  undefined4 uStack_170;
  undefined1 auStack_16c [4];
  undefined *puStack_168;
  undefined4 *puStack_164;
  undefined4 uStack_160;
  undefined1 auStack_15c [4];
  undefined *puStack_158;
  undefined4 *puStack_154;
  undefined4 uStack_150;
  int *piStack_14c;
  uint uStack_148;
  int *piStack_144;
  undefined1 auStack_140 [4];
  undefined *puStack_13c;
  undefined4 *puStack_138;
  undefined4 uStack_134;
  char cStack_12e;
  undefined1 uStack_12d;
  uint uStack_12c;
  uint uStack_128;
  uint uStack_124;
  undefined1 uStack_11f;
  undefined1 uStack_11e;
  undefined1 uStack_11d;
  uint uStack_11c;
  int iStack_118;
  byte *local_114;
  int *piStack_110;
  undefined4 uStack_10c;
  int *piStack_108;
  int iStack_104;
  undefined4 uStack_100;
  undefined4 local_fc;
  code *local_f8;
  int local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined1 auStack_d8 [16];
  undefined1 auStack_c8 [16];
  undefined1 auStack_b8 [16];
  int iStack_a8;
  undefined1 auStack_a4 [16];
  undefined1 auStack_94 [16];
  undefined4 auStack_84 [2];
  undefined4 auStack_7c [2];
  undefined1 auStack_74 [32];
  undefined1 auStack_54 [32];
  undefined4 local_34 [13];
  
  local_ec = 0;
  local_fc = 0;
  local_f8 = (code *)&LAB_0044f5a0;
  local_f4 = 0;
  local_e8 = 1;
  local_e4 = 1;
  local_e0 = 1;
  local_dc = 1;
  local_f0 = 0;
  FUN_0045a970(local_34);
  if ((*param_1 == 0) || ((param_1[5] != 0 && (param_1[1] == 0)))) {
    return 0x3c;
  }
  FUN_00450bd0(this,0);
  pbVar8 = (byte *)*param_1;
  local_114 = pbVar8;
  uVar2 = LayoutDB_459060(this,pbVar8);
  if (CONCAT31(extraout_var,uVar2) != 0) {
    iVar3 = FUN_00457d50();
    if (iVar3 == 0) {
      uVar2 = 1;
    }
    else {
      (**(code **)(*(int *)pbVar8 + 8))((int)this + 0xa4,4);
      (**(code **)(*(int *)pbVar8 + 8))(&uStack_124,2);
      iVar3 = 0x3e;
      do {
        (**(code **)(*(int *)pbVar8 + 8))(&uStack_17d,1);
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      piStack_14c = *(int **)((int)this + 0x174);
      uStack_148 = uStack_11c & 0xffff;
      if ((uStack_148 != *(uint *)((int)this + 0x94)) || (uStack_148 == 0)) {
        if (*(int *)((int)this + 0x90) != 0) {
          FUN_00433560((void *)((int)this + 0x8c),piStack_14c);
        }
        *(uint *)((int)this + 0x94) = uStack_148;
        if (uStack_148 != 0) {
          iVar3 = FUN_00457040(piStack_14c,0,*(int *)((int)this + 0x9c) + uStack_148);
          *(int *)((int)this + 0x90) = iVar3;
          if (iVar3 == 0) {
            *(undefined4 *)((int)this + 0x94) = 0;
            *(undefined4 *)((int)this + 0x98) = 0;
            return 0;
          }
          *(undefined4 *)((int)this + 0x98) = *(undefined4 *)((int)this + 0x9c);
        }
      }
      uVar13 = 0;
      if ((short)uStack_11c != 0) {
        do {
          (**(code **)(*(int *)pbVar8 + 8))(*(int *)((int)this + 0x90) + uVar13 * 4,4);
          uVar13 = uVar13 + 1;
        } while (uVar13 < (uStack_11c & 0xffff));
      }
      iVar3 = FUN_004570e0(pbVar8);
      if (iVar3 == 0) {
        uVar2 = 2;
      }
      else {
        (**(code **)(*(int *)pbVar8 + 8))(&piStack_108,4);
        piStack_144 = *(int **)((int)this + 0x174);
        piStack_14c = piStack_108;
        if ((piStack_108 != *(int **)((int)this + 0x5c)) || (piStack_108 == (int *)0x0)) {
          if (*(int *)((int)this + 0x58) != 0) {
            FUN_00456ac0((void *)((int)this + 0x54),piStack_144);
          }
          *(int **)((int)this + 0x5c) = piStack_14c;
          if (piStack_14c != (int *)0x0) {
            puVar4 = FUN_00456f30(piStack_144,0,(int)piStack_14c);
            *(undefined4 **)((int)this + 0x58) = puVar4;
            if (puVar4 == (undefined4 *)0x0) {
              *(undefined4 *)((int)this + 0x5c) = 0;
              uVar2 = 3;
              goto LAB_00459023;
            }
          }
        }
        (**(code **)(*(int *)pbVar8 + 8))(&uStack_124,4);
        uStack_12c = 0;
        iVar3 = FUN_0045a760((void *)((int)this + 0x34),uStack_124,&uStack_12c,
                             *(int **)((int)this + 0x174));
        if (iVar3 == 0) {
          uVar2 = 4;
        }
        else {
          uStack_10c = 0;
          local_184 = (int *)0x0;
          if (uStack_124 != 0) {
            do {
              pvVar5 = (void *)(**(code **)(**(int **)((int)this + 0x174) + 4))(0x6c);
              if (pvVar5 == (void *)0x0) {
                FUN_00450bd0(this,0);
                uVar2 = 5;
                goto LAB_00459023;
              }
              FUN_00450540(pvVar5,this);
              *(void **)(*(int *)((int)this + 0x38) + (int)local_184 * 4) = pvVar5;
              iVar3 = FUN_00457af0(pvVar5,(int *)pbVar8);
              if (iVar3 == 0) {
                uVar2 = 6;
                goto LAB_00459023;
              }
              local_184 = (int *)((int)local_184 + 1);
            } while (local_184 < uStack_124);
          }
          iVar3 = FUN_004570e0(pbVar8);
          if (iVar3 == 0) {
            uVar2 = 7;
          }
          else {
            iVar3 = FUN_004574a0(*(void **)((int)this + 0x2c4),(int *)pbVar8);
            if (iVar3 == 0) {
              uVar2 = 8;
            }
            else {
              iVar3 = FUN_00458070(this,(int *)pbVar8);
              if (iVar3 == 0) {
                uVar2 = 9;
              }
              else {
                iVar3 = FUN_00450ef0(this,1);
                if (iVar3 == 0) {
                  uVar2 = 10;
                }
                else {
                  iVar3 = FUN_004570e0(pbVar8);
                  if (iVar3 == 0) {
                    uVar2 = 0xb;
                  }
                  else {
                    (**(code **)(*(int *)pbVar8 + 8))(&uStack_128,4);
                    if ((uStack_128 == 0) || (0x10 < uStack_128)) {
                      uVar2 = 0xc;
                    }
                    else {
                      auStack_15c[0] = uStack_17d;
                      auStack_140[0] = uStack_17d;
                      pvVar5 = (void *)param_1[3];
                      auStack_17c[0] = uStack_17d;
                      puStack_13c = (undefined *)0x0;
                      puStack_138 = (undefined4 *)0x0;
                      uStack_134 = 0;
                      puStack_158 = (undefined *)0x0;
                      puStack_154 = (undefined4 *)0x0;
                      uStack_150 = 0;
                      puStack_178 = (undefined *)0x0;
                      puStack_174 = (undefined4 *)0x0;
                      uStack_170 = 0;
                      auStack_16c[0] = uStack_17d;
                      puStack_168 = (undefined *)0x0;
                      puStack_164 = (undefined4 *)0x0;
                      uStack_160 = 0;
                      uStack_148 = 0;
                      iVar3 = FUN_00451c40(this,0,(int)this + 0x1d8,(int)this,&DAT_004daa9c);
                      if (iVar3 == 0) {
                        uVar2 = 0xd;
                      }
                      else {
                        iVar3 = FUN_00457700((void *)((int)this + 0x1d8),(int *)pbVar8);
                        if (iVar3 != 0) {
                          FUN_00451c40(this,0,(int)this + 0x1d8,(int)this,&DAT_004daa9c);
                          local_184 = (int *)0x0;
                          if (uStack_128 != 1) {
                            do {
                              piStack_14c = (int *)0x0;
                              iVar3 = FUN_00457d50();
                              if (iVar3 == 0) {
                                uVar2 = 0xf;
                                goto LAB_00458b41;
                              }
                              FUN_00459330(auStack_140,puStack_138,&piStack_14c);
                              puVar4 = (undefined4 *)FUN_00430de0(0x30);
                              if (puVar4 == (undefined4 *)0x0) {
                                piStack_144 = (int *)0x0;
                              }
                              else {
                                piStack_144 = FUN_0044f820(puVar4);
                              }
                              piStack_144[9] = (int)this;
                              iVar3 = FUN_00457700(piStack_144,(int *)pbVar8);
                              if (iVar3 == 0) {
                                uVar2 = 0x10;
                                goto LAB_00458b41;
                              }
                              FUN_00459330(auStack_17c,puStack_174,&piStack_144);
                              local_184 = (int *)((int)local_184 + 1);
                            } while (local_184 < uStack_128 - 1);
                          }
                          local_184 = (int *)0x0;
                          if (uStack_128 != 1) {
                            do {
                              piVar7 = *(int **)(puStack_13c + (int)local_184 * 4);
                              uStack_12c = *(uint *)(puStack_178 + (int)local_184 * 4);
                              piStack_144 = piVar7;
                              if (pvVar5 == (void *)0x0) {
LAB_004589ab:
                                FUN_00459330(auStack_15c,puStack_154,&piStack_144);
                                FUN_00459330(auStack_16c,puStack_164,&uStack_12c);
                                uStack_148 = uStack_148 + 1;
                              }
                              else {
                                auStack_c8[0] = uStack_17d;
                                FUN_00414100(auStack_c8,'\0');
                                uVar13 = 0xffffffff;
                                piVar14 = piVar7;
                                do {
                                  if (uVar13 == 0) break;
                                  uVar13 = uVar13 - 1;
                                  iVar3 = *piVar14;
                                  piVar14 = (int *)((int)piVar14 + 1);
                                } while ((char)iVar3 != '\0');
                                FUN_0042f7f0(auStack_c8,piVar7,~uVar13 - 1);
                                iVar3 = *(int *)((int)pvVar5 + 4);
                                FUN_00459600(pvVar5,&iStack_104,(int)auStack_c8);
                                cStack_12e = iStack_104 != iVar3;
                                FUN_00414100(auStack_c8,'\x01');
                                piVar7 = piStack_144;
                                if (cStack_12e == '\0') goto LAB_004589ab;
                                auStack_d8[0] = uStack_17d;
                                FUN_00414100(auStack_d8,'\0');
                                uVar13 = 0xffffffff;
                                piVar14 = piVar7;
                                do {
                                  if (uVar13 == 0) break;
                                  uVar13 = uVar13 - 1;
                                  iVar3 = *piVar14;
                                  piVar14 = (int *)((int)piVar14 + 1);
                                } while ((char)iVar3 != '\0');
                                FUN_0042f7f0(auStack_d8,piVar7,~uVar13 - 1);
                                puVar6 = FUN_00459830(auStack_a4,&uStack_12d,&uStack_11f);
                                piVar7 = (int *)FUN_004596b0(auStack_74,(undefined4 *)auStack_d8,
                                                             puVar6);
                                piVar7 = (int *)FUN_00459500(pvVar5,auStack_7c,piVar7);
                                iVar3 = *piVar7;
                                FUN_004591a0((int)auStack_74);
                                FUN_004598e0(auStack_a4);
                                FUN_004599d0((void *)(iVar3 + 0x1c),&piStack_14c);
                                FUN_00414100(auStack_d8,'\x01');
                                piVar7 = piStack_144;
                                auStack_b8[0] = uStack_12d;
                                FUN_00414100(auStack_b8,'\0');
                                uVar13 = 0xffffffff;
                                piVar14 = piVar7;
                                do {
                                  if (uVar13 == 0) break;
                                  uVar13 = uVar13 - 1;
                                  iVar3 = *piVar14;
                                  piVar14 = (int *)((int)piVar14 + 1);
                                } while ((char)iVar3 != '\0');
                                FUN_0042f7f0(auStack_b8,piVar7,~uVar13 - 1);
                                puVar6 = FUN_00459830(auStack_94,&uStack_11e,&uStack_11d);
                                piVar7 = (int *)FUN_004596b0(auStack_54,(undefined4 *)auStack_b8,
                                                             puVar6);
                                FUN_00459500(pvVar5,auStack_84,piVar7);
                                FUN_004591a0((int)auStack_54);
                                FUN_004598e0(auStack_94);
                                FUN_00414100(auStack_b8,'\x01');
                                *(undefined4 *)((int)this + 400) = 1;
                                pbVar8 = (byte *)piStack_14c[4];
                                if (pbVar8 == (byte *)0x0) {
                                  pbVar8 = &DAT_004cc108;
                                }
                                uStack_100 = FUN_004511d0(this,pbVar8);
                                FUN_00459330(auStack_15c,puStack_154,&uStack_100);
                                FUN_00459330(auStack_16c,puStack_164,&uStack_12c);
                                uStack_148 = uStack_148 + 1;
                                FUN_00459b00((int *)&piStack_14c);
                              }
                              local_184 = (int *)((int)local_184 + 1);
                            } while (local_184 < uStack_128 - 1);
                          }
                          uVar13 = 0;
                          if (uStack_148 != 0) {
LAB_004589fb:
                            local_f4 = param_1[2];
                            local_ec = *(undefined4 *)(puStack_158 + uVar13 * 4);
                            local_f8 = (code *)param_1[1];
                            local_fc = 0;
                            local_e8 = 0;
                            iStack_118 = 0;
                            if (param_1[5] == 0) {
LAB_00458a64:
                              param_1[8] = 0;
                            }
                            else {
                              iVar3 = (*local_f8)(&local_fc,&iStack_118);
                              if ((iVar3 != 0) && (iVar3 != 0x46)) {
                                uVar2 = 0x15;
LAB_00458b41:
                                FUN_004594f0();
                                FUN_00430df0(puStack_168);
                                puStack_168 = (undefined *)0x0;
                                puStack_164 = (undefined4 *)0x0;
                                uStack_160 = 0;
                                FUN_004594f0();
                                FUN_00430df0(puStack_178);
                                puStack_178 = (undefined *)0x0;
                                puStack_174 = (undefined4 *)0x0;
                                uStack_170 = 0;
                                FUN_004594f0();
                                FUN_00430df0(puStack_158);
                                puStack_158 = (undefined *)0x0;
                                puStack_154 = (undefined4 *)0x0;
                                uStack_150 = 0;
                                FUN_004594f0();
                                FUN_00430df0(puStack_13c);
                                goto LAB_00459023;
                              }
                              if (iStack_118 == 0) goto LAB_00458a64;
                              if (1 < *(uint *)(iStack_118 + 0x1d4)) {
                                uVar2 = 0x12;
                                goto LAB_00458b41;
                              }
                            }
                            puVar4 = (undefined4 *)
                                     (**(code **)(**(int **)((int)this + 0x174) + 4))(0x30);
                            if (puVar4 == (undefined4 *)0x0) {
                              uVar2 = 0x13;
                              FUN_004594f0();
                              FUN_00430df0(puStack_168);
                              puStack_168 = (undefined *)0x0;
                              puStack_164 = (undefined4 *)0x0;
                              uStack_160 = 0;
                              FUN_004594f0();
                              FUN_00430df0(puStack_178);
                              puStack_178 = (undefined *)0x0;
                              puStack_174 = (undefined4 *)0x0;
                              uStack_170 = 0;
                              FUN_004594f0();
                              FUN_00430df0(puStack_158);
LAB_00458d0d:
                              uStack_150 = 0;
                              puStack_154 = (undefined4 *)0x0;
                              puStack_158 = (undefined *)0x0;
                              FUN_004594f0();
                              FUN_00430df0(puStack_13c);
                              goto LAB_00459023;
                            }
                            FUN_0044f820(puVar4);
                            uVar1 = *(uint *)(puStack_168 + uVar13 * 4);
                            FUN_0045a830(puVar4,uVar1,&DAT_004ecc58);
                            uVar13 = uVar13 + 1;
                            puVar4[5] = *(undefined4 *)(uVar1 + 0x14);
                            puVar4[6] = *(undefined4 *)(uVar1 + 0x18);
                            puVar4[7] = *(undefined4 *)(uVar1 + 0x1c);
                            puVar4[8] = *(undefined4 *)(uVar1 + 0x20);
                            puVar4[9] = *(undefined4 *)(uVar1 + 0x24);
                            puVar4[10] = *(undefined4 *)(uVar1 + 0x28);
                            puVar4[0xb] = *(undefined4 *)(uVar1 + 0x2c);
                            iVar3 = FUN_00451c40(this,uVar13,(int)puVar4,iStack_118,local_ec);
                            if (iVar3 == 0) {
                              uVar2 = 0x14;
                              FUN_004594f0();
                              FUN_00430df0(puStack_168);
                              puStack_168 = (undefined *)0x0;
                              puStack_164 = (undefined4 *)0x0;
                              uStack_160 = 0;
                              FUN_004594f0();
                              FUN_00430df0(puStack_178);
                              puStack_178 = (undefined *)0x0;
                              puStack_174 = (undefined4 *)0x0;
                              uStack_170 = 0;
                              FUN_004594f0();
                              FUN_00430df0(puStack_158);
                              goto LAB_00458d0d;
                            }
                            *(int *)((int)this + 0x1d4) = *(int *)((int)this + 0x1d4) + 1;
                            puVar4[0xb] = 0;
                            if (puVar4[10] != 0) {
                              uVar9 = FUN_00451b90(this,puVar4[10],&iStack_a8);
                              puVar4[0xb] = uVar9;
                            }
                            Sleep(0);
                            if (uStack_148 <= uVar13) goto LAB_00458d34;
                            goto LAB_004589fb;
                          }
LAB_00458d34:
                          puVar10 = puStack_178;
                          for (uVar13 = 0;
                              (puVar10 != (undefined *)0x0 &&
                              (uVar13 < (uint)((int)puStack_174 - (int)puVar10 >> 2)));
                              uVar13 = uVar13 + 1) {
                            puVar4 = *(undefined4 **)(puVar10 + uVar13 * 4);
                            if (puVar4 != (undefined4 *)0x0) {
                              FUN_0044f8b0(puVar4);
                              FUN_00430df0((undefined *)puVar4);
                              puVar10 = puStack_178;
                            }
                          }
                          FUN_004594f0();
                          FUN_00430df0(puStack_168);
                          puStack_168 = (undefined *)0x0;
                          puStack_164 = (undefined4 *)0x0;
                          uStack_160 = 0;
                          FUN_004594f0();
                          FUN_00430df0(puStack_178);
                          puStack_178 = (undefined *)0x0;
                          puStack_174 = (undefined4 *)0x0;
                          uStack_170 = 0;
                          FUN_00459170((int)auStack_15c);
                          FUN_00459170((int)auStack_140);
                          pbVar8 = local_114;
                          iVar3 = FUN_004570e0(local_114);
                          if (iVar3 == 0) {
                            uVar2 = 0x16;
                          }
                          else {
                            (**(code **)(*(int *)pbVar8 + 8))(&piStack_110,4);
                            iVar3 = FUN_00451540(this,0);
                            iVar3 = FUN_00456900((void *)((int)this + 0x164),
                                                 (int)(iVar3 + (int)piStack_110),
                                                 *(int **)((int)this + 0x178));
                            if (iVar3 == 0) {
                              uVar2 = 0x17;
                            }
                            else {
                              local_184 = (int *)0x0;
                              if (piStack_110 != (int *)0x0) {
                                iVar3 = 0;
                                do {
                                  puVar4 = FUN_0045a4e0(*(int **)((int)this + 0x174),0,1);
                                  if (puVar4 == (undefined4 *)0x0) {
                                    uVar2 = 0x18;
                                    goto LAB_00459023;
                                  }
                                  *(undefined4 **)(*(int *)((int)this + 0x168) + iVar3) = puVar4;
                                  *(int *)(*(int *)((int)this + 0x168) + 4 + iVar3) =
                                       (int)this + 0x1d8;
                                  iVar11 = FUN_004576b0((void *)(*(int *)((int)this + 0x168) + iVar3
                                                                ),(int *)local_114);
                                  if (iVar11 == 0) {
                                    FUN_0045a530(*(int **)((int)this + 0x174),puVar4,1);
                                    uVar2 = 0x19;
                                    goto LAB_00459023;
                                  }
                                  local_184 = (int *)((int)local_184 + 1);
                                  iVar3 = iVar3 + 0x20;
                                } while (local_184 < piStack_110);
                              }
                              pbVar8 = local_114;
                              local_184 = (int *)0x0;
                              piStack_144 = piStack_110;
                              if (*(int *)((int)this + 0x1d4) != 0) {
                                piStack_14c = (int *)((int)this + 0x194);
                                do {
                                  iVar3 = *piStack_14c;
                                  pvVar5 = *(void **)(iVar3 + 0x28);
                                  if ((pvVar5 != (void *)0x0) && (pvVar5 != this)) {
                                    uStack_12c = 0;
                                    *(int **)(iVar3 + 0x18) = piStack_144;
                                    if (*(int *)((int)pvVar5 + 0x16c) != 0) {
                                      iVar11 = (int)piStack_144 << 5;
                                      uStack_148 = 0;
                                      do {
                                        puVar4 = (undefined4 *)
                                                 (*(int *)((int)pvVar5 + 0x168) + uStack_148);
                                        puVar15 = (undefined4 *)
                                                  (*(int *)((int)this + 0x168) + iVar11);
                                        for (iVar12 = 8; iVar12 != 0; iVar12 = iVar12 + -1) {
                                          *puVar15 = *puVar4;
                                          puVar4 = puVar4 + 1;
                                          puVar15 = puVar15 + 1;
                                        }
                                        piStack_144 = (int *)((int)piStack_144 + 1);
                                        *(int *)(*(int *)((int)this + 0x168) + 4 + iVar11) = iVar3;
                                        pvVar5 = *(void **)(iVar3 + 0x28);
                                        iVar11 = iVar11 + 0x20;
                                        uStack_12c = uStack_12c + 1;
                                        uStack_148 = uStack_148 + 0x20;
                                      } while (uStack_12c < *(uint *)((int)pvVar5 + 0x16c));
                                    }
                                  }
                                  local_184 = (int *)((int)local_184 + 1);
                                  piStack_14c = piStack_14c + 1;
                                } while (local_184 < *(uint *)((int)this + 0x1d4));
                              }
                              iVar3 = FUN_00457db0(this,(int)param_1,local_114);
                              if (iVar3 == 0) {
                                uVar2 = 0x1a;
                              }
                              else {
                                iVar3 = ModelsDB_457f40(this,pbVar8);
                                if (iVar3 == 0) {
                                  uVar2 = 0x1b;
                                }
                                else {
                                  iVar3 = (**(code **)(*(int *)pbVar8 + 0x10))();
                                  if (iVar3 == 0) {
                                    iVar3 = FUN_00450ef0(this,0);
                                    if (iVar3 != 0) {
                                      model_4515c0();
                                      FUN_00451340((int)this);
                                      return 0;
                                    }
                                    uVar2 = 0x1d;
                                  }
                                  else {
                                    uVar2 = 0x1c;
                                  }
                                }
                              }
                            }
                          }
                          goto LAB_00459023;
                        }
                        uVar2 = 0xe;
                      }
                      FUN_004594f0();
                      FUN_00430df0(puStack_168);
                      puStack_168 = (undefined *)0x0;
                      puStack_164 = (undefined4 *)0x0;
                      uStack_160 = 0;
                      FUN_004594f0();
                      FUN_00430df0(puStack_178);
                      puStack_178 = (undefined *)0x0;
                      puStack_174 = (undefined4 *)0x0;
                      uStack_170 = 0;
                      FUN_004594f0();
                      FUN_00430df0(puStack_158);
                      puStack_158 = (undefined *)0x0;
                      puStack_154 = (undefined4 *)0x0;
                      uStack_150 = 0;
                      FUN_004594f0();
                      FUN_00430df0(puStack_13c);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_00459023:
  FUN_00450bd0(this,0);
  return uVar2;
}


