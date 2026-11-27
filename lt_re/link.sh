#!/bin/sh
cd "$(dirname "$0")"
i686-w64-mingw32-gcc obj/*.o ltdata.o lt_syms.ld -o lithtech_recomp.exe -Wl,--image-base=0x400000 -Wl,--section-start,.ltdata=0x4cb000 -Wl,--section-start,.text=0x1000000 -Wl,--enable-stdcall-fixup -nostartfiles -Wl,-e,_lt_start -luser32 -lgdi32 -lkernel32 -lwinmm -lole32 -lws2_32 -ladvapi32
