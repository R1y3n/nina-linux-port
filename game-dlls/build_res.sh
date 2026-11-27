#!/bin/bash
# Resource DLLs (CRes.dll / SRes.dll). usage: build_res.sh <proj dir>
set -e; T=i686-w64-mingw32; P=$(cd "$1" && pwd); H=$(cd "$(dirname "$0")" && pwd); mkdir -p "$H/out"
printf '#include <windows.h>\n#ifndef IDC_STATIC\n#define IDC_STATIC (-1)\n#endif\n' > "$H/out/afxres.h"
for pair in ServerRes:SRes ClientRes:CRes; do d=${pair%%:*}; n=${pair##*:}; (cd "$P/AVP2/$d"
  $T-windres -I"$H/out" -I. -DWIN32 --codepage=1252 -O coff $d.rc "$H/out/$d.res.o"
  $T-g++ -O2 -shared -static-libgcc -static-libstdc++ -o "$H/out/$n.dll" "$(ls | grep -i "^main.cpp$")" "$H/out/$d.res.o" -Wl,--subsystem,windows); done
