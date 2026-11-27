#!/bin/sh
# Native 32-bit Linux build (needs gcc-multilib / libc6-dev-i386). Run from lt_re/linux.
set -e
cd "$(dirname "$0")"
python3 gen_dx7.py; python3 gen_gl.py; python3 gen_linux.py
gcc -m32 -g -O0 -no-pie -O1 -w -mstackrealign -pthread -Wa,--noexecstack core.c dx7.c dx7_gen.c dinput.c mss.c msvcrt.c k32_ext.c u32_ext.c gl.c lt_glarity.c k32_file.c k32_sys.c pe.c u32.c start.c lt_exports.c lt_arity.c lt_iat_tab.c blobs.S lifted_all_elf.s -Wl,--dynamic-list=dyn.list -o lithtech_linux -ldl -lm -lSDL2
