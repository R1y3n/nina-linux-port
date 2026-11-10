#!/bin/sh
# Rebuild lithtech_recomp.exe (needs gcc-mingw-w64-i686). mss32.dll must sit next to the exe at runtime.
set -e
cd "$(dirname "$0")/c"; mkdir -p ../obj
for f in *.c; do i686-w64-mingw32-gcc -c -w -fpermissive -x c -include ghidra_types.h "$f" -o "../obj/${f%.c}.o" 2>/dev/null || [ "$f" = lt_support.c ] && i686-w64-mingw32-gcc -c -w lt_support.c -o ../obj/lt_support.o; done
cd ..; i686-w64-mingw32-gcc obj/*.o -o lithtech_recomp.exe -luser32 -lgdi32 -lkernel32 -lwinmm -lole32 -lws2_32 -ladvapi32
