#!/bin/sh
# Build lithtech_exact.exe: translated original code + original data/text images at their VAs.
set -e
cd "$(dirname "$0")"
i686-w64-mingw32-as lifted_all.s -o obj_lifted_all.o
i686-w64-mingw32-gcc -c lttext.S -o lttext.o
i686-w64-mingw32-gcc -c -w lt_init.c -o lt_init.o
i686-w64-mingw32-gcc -c -w c/lt_iat.c -o lt_iat.o
i686-w64-mingw32-gcc -nostdlib -nostartfiles -mwindows obj_lifted_all.o lttext.o ltdata.o rsrc.o lt_iat.o lt_init.o -o lithtech_exact.exe \
  -Wl,--image-base=0x400000 -Wl,--section-start,.lttext=0x401000 -Wl,--section-start,.ltdata=0x4cb000 -Wl,--section-start,.text=0x1000000 -Wl,-e,_lt_start -lkernel32
