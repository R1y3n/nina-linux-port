# lithtech.exe reconstruction

## What to run: lithtech_exact.exe  (build: sh link_exact.sh, needs gcc-mingw-w64-i686)
A STATIC TRANSLATION of the original machine code, not a re-interpretation:
- lift_all.py   all 259,248 instructions Ghidra found in .text -> lifted_all.s (GAS Intel syntax); branch/call targets become labels.
- ltdata.bin    original .rdata/.data/.bss placed at their ORIGINAL addresses (0x4cb000..).  lttext.bin: original .text bytes kept at 0x401000 for table reads.
- lt_patch_tab  3,738 code pointers stored in data (vtables, callbacks, jump tables) rewritten to the translated addresses at startup.
- c/lt_iat.c    fills the original import table (incl. mss32.dll, Winsock-by-ordinal) at startup, so original `call [IAT]` code works unchanged.
- lt_init.c     startup: IAT -> patch table -> original entry point.
Verified (Wine 9, headless): identical behaviour to the original exe in the two cases tried
  (no args: "No game resources specified."; `-rez <bad path>`: same window/hang). NOT yet tested with real AvP2 game data,
  real D3D/audio, or on Windows.  Known gap: the .rsrc resources (icons/dialogs/version) are not copied into the new exe.
Heuristic risk: any 32-bit value in data that equals a code address is treated as a pointer (some could be plain integers).

## Readable source: c/  (Ghidra decompilation, 3512 functions, repo-name hints, lt_types.h etc.)
Reference only. It is NOT exact: some functions are wrong when expressed in C (e.g. the CRT stack probe __chkstk takes EAX and moves ESP),
and 203 did not compile (199 were lifted from the disassembly into c/lt_lifted.c; first-pass build: lithtech_recomp.exe, superseded).
Path to real source: replace translated functions with C one at a time, rebuild, and compare behaviour with the original.

## Other
map_funcs.py / func_string_map.json: function -> jsj2008/lithtech repo file (string matches). infer_types.py: global types from disassembly.
