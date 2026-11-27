# AVP2 source -> MinGW-w64 cross-build on Linux

Output is **32-bit Windows PE DLLs** (not Linux ELF). They load into the Windows LithTech engine
(run under Wine/Proton). A native-ELF game would need an engine port; this is not that.

## Use
    sudo apt install mingw-w64 patch python3
    unrar x si_avp2_sourcecode_v1.rar            # any RAR tool
    cd si_avp2_sourcecode_v1 && patch -p1 < ../avp2-linux-build/patches/avp2-mingw.patch
    ./avp2-linux-build/build_res.sh proj          # -> out/CRes.dll, out/SRes.dll   (works, complete)
    ./avp2-linux-build/build.py proj --link       # compiles object.lto + cshell.dll sources, then links

## Status (verified from a fresh extract + patch)
| Target | Sources compiled | Link |
|---|---|---|
| CRes.dll / SRes.dll | done | **built** |
| object.lto | 215 / 215 | 32 undefined symbols |
| cshell.dll | 188 / 188 | 176 undefined symbols |

Sources compiled = exactly the files listed in the .dsp projects (7 files on disk are not in any project and are skipped).

## What is still missing (library code with no source in either upload nor in osgcc/no-one-lives-forever)
See reports/undefined_*.demangled.txt. object.lto: CButeMgr (22), CGameSpyMgr (8), CCryptMgr (2).
cshell.dll adds: ltguimgr controls (CLTGUI*), LithFontMgr, LithTrackMgr, CGameSpyClientMgr/Server/Player, StdLith helpers.
Provide those sources (or compatible implementations) as objects named out/ext_*.o and re-run with --link.
`libshim/mfcstub.cpp` is my clean-room CString/CPoint/CRect (already linked in).
CButeMgr's file grammar and CCryptMgr's algorithm/key are not documented anywhere I could see, so I did not guess them.

## Notes on the patch (47 files, ~1400 lines)
fsm.h template-friend fix; `this->` in ltbasedefs.h; `typename`; for-loop scope hoists (VC6 leaky scope);
MSVC temp->non-const-ref sites wrapped with AsLvalue<>; ClearScreen/FindPoliesTouchingBox default-arg function
pointers; stdlithdefs.h BOOL/DWORD/WORD/BYTE macros vs windows.h; PlaySoundFromPos const char*; misc.
Shims (shim/compat): iostream.h, strstrea.h, fstream.h, hash_map/hash_set (+hash<string>), lt_debugnew.h (debug_new, AsLvalue).
