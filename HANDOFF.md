# HANDOFF — reconstruction de lithtech.exe (AvP2 / LithTech Talon) : traduction statique + exécution native Linux

Dernière session : novembre 2026. Ce document permet de reprendre le projet dans une nouvelle conversation sans rien perdre.
Utilisateur : Joe (dev licencié, projet de port PS4 AvP2/"Nina" financé ; il a déjà analysé SDK/moteur : https://github.com/nolffan/avp2src et https://github.com/nolffan/nolfsrc — ne pas refaire ce travail, s'en servir comme référence).

## 1. Objectif
Obtenir, à partir de `lithtech.exe` (VC6, 2002, 962 560 octets), (a) une base de code compréhensible/documentée, et surtout (b) un exécutable qui a **la même logique** que l'original, d'abord sous Windows puis **nativement sous Linux sans Wine** (shim Win32). Demande finale : faire tourner le jeu (rendu inclus) sur Linux.

## 2. État actuel (résumé)
| Livrable | État |
|---|---|
| Décompilation C (Ghidra, 3512 fonctions, noms issus du dépôt jsj2008/lithtech par chaînes) | Fait, **référence seulement** (non exact : ex. `__chkstk` impossible en C). `c/` |
| `lithtech_exact.exe` (Windows) : traduction statique de TOUT le code (259 248 instructions) + données/ressources PE d'origine | Fait. Testé sous Wine : même comportement que l'original dans 2 scénarios |
| `linux/lithtech_linux` (ELF 32 bits natif) : même code traduit + shim Win32 écrit à la main | **Le jeu démarre et tourne dans sa boucle principale (menu chargé)**, sans rien afficher (draw calls D3D7 = no-op). RSS ~50 Mo après 20 s (légère croissance ≈2 Mo/s à surveiller) |
| Rendu | **Non fait.** Voir §7 (deux pistes) |
| Entrées (clavier/souris), audio, vidéo Bink | Stubs (aucun évènement, audio nul, Binkw32 non géré) |

## 3. Fichiers fournis par l'utilisateur (à re-téléverser dans la nouvelle session)
- `lithtech.exe`, `d3d.ren` (== `d3d_1.ren`, identiques), `ltmsg.dll`, `mss32.dll`, `LOCALE.REZ` (ancien, plus utile), 
- `main.rez` : **ZIP** (pas un REZ LithTech) de l'arborescence `assets/` (ATTRIBUTES, INTERFACE, MODELS, MUSIC, SKINS, SOUNDS, SPRITES, WORLDS, WORLDTEXTURES, CRES.DLL, CSHELL.DLL, OBJECT.LTO, SRES.DLL, *.DEP). Le jeu n'a **jamais eu `cresl.dll`** (l'échec de son chargement est sans importance).
- `forclaude.7z` : dossier de travail réel (Launch.dll, server.dll, cdaudio.dll, binkw32.dll, Smackw32.dll, mss32.dll, MP3DEC.AS6/.ASI, ltmsg.dll, **opengl.ren**, autoexec.cfg, Profiles/{Default.prf,Player_0.txt}, Save/...).
- `opengl_talon-master.zip` : sources du moteur de rendu OpenGL (opengl.ren) — voir §7.
Entrées du build : `lithtech.exe` + `ltdata.bin`/`lttext.bin` (générés par gen_image.py / lift_all.py depuis lithtech.exe, chemins `/mnt/user-data/uploads/...` codés en dur dans plusieurs scripts : à adapter).

## 4. Architecture (dossier `lt_re/`)
- `lift_all.py` : traduction statique. Lit `data/code_units.txt` (liste d'instructions exportée de Ghidra par `support/ghidra_scripts/ExportCode.java`), désassemble avec capstone et écrit `lifted_all.s` (GAS Intel). Une étiquette `.Llt_<VA>` par instruction ; cibles de branchement/appels → étiquettes ; immédiats égaux à une adresse de code → `offset .Llt_…`. Table `lt_patch_tab` : 3 738 pointeurs de code stockés dans les données (vtables, callbacks, jump tables) à réécrire au démarrage.
- `gen_image.py` : `ltdata.bin` (copie de .rdata/.data/.bss de l'exe à leurs **adresses d'origine**, 0x4cb000–0x4ef000), `lt_syms.ld`, `funcmap.json` (VA→nom/taille).
- Images mappées à l'exécution aux adresses d'origine : 0x400000 en-tête PE, 0x401000 octets .text d'origine (lecture de tables), 0x4cb000 données, 0x4ef000 .rsrc. La table d'imports (IAT, slots d'origine) est remplie au démarrage par le shim.
- Windows : `link_exact.sh` → `lithtech_exact.exe` (+ `rsrc.rc` = 25 ressources d'origine, vérifiées identiques).
- Linux : `linux/` (voir §5). `sh linux/build_linux.sh` → `linux/lithtech_linux` (ELF i386 non-PIE ; code lifté dans `.text` normal ; `lifted_all_elf.s` = copie sans préfixes `_`, + table `lt_map` (adresse lifté → VA d'origine) utilisée par le handler de crash).
- Autres : `map_funcs.py`/`func_string_map.json` (appariement fonctions↔dépôt jsj2008/lithtech par chaînes, ~150 correspondances bruyantes), `infer_types.py`, `lift_stubs.py` (ancienne piste : 199 fonctions non compilables relevées en asm, `lt_lifted.c`), `build_stub.py`, `gen_support.py` (ancien premier exe `lithtech_recomp.exe`, **obsolète**).

## 5. Shim Win32 natif (`linux/`, écrit de zéro, pas de code Wine)
`win.h` types/handles · `core.c` table de handles, TEB via `set_thread_area`/fs (fs:[0]=chaîne SEH, TLS, LastError), SEH (RaiseException/RtlUnwind, SIGSEGV/SIGFPE→exceptions, chaîne d'appel en adresses d'origine avec LT_TRACE) · `k32_file.c` (fichiers, **chemins Windows→Unix insensibles à la casse**, FindFirstFile, temps, FormatMessage module/chaîne, ini, OpenFile…) · `k32_sys.c` (tas, VirtualAlloc, threads pthread + ExitThread par longjmp, events, sections critiques, TLS, env, locale) · `k32_ext.c` (APIs larges, condition variables/SRW, Crypt MD5/SHA-1/SHA-256 réels, registre vide, dwmapi) · `pe.c` (**chargeur PE** pour LoadLibrary, imports, ressources, LoadString, stubs auto générés pour imports non implémentés, mutex récursif) · `u32.c`/`u32_ext.c` (user32/gdi32 sans fenêtre réelle, winsock→BSD) · `msvcrt.c` (CRT cdecl : _iob/FILE et wchar_t 16 bits traduits) · `mss.c` (Miles : mémoire/lock/startup réels, audio nul) · `dinput.c` (clavier+souris sans évènements) · `dx7.c`+`gen_dx7.py` (DirectDraw7/Direct3D7 : modes, surfaces + chaîne de flip, textures, VB, device **sans dessin**, 136 slots COM générés en stubs à taille d'arguments correcte) · `gl.c`+`gen_gl.py` (WGL→SDL2 chargé par dlopen, thunks stdcall→cdecl dimensionnés depuis les en-têtes Mesa, repli de version GL) · `start.c` (mappe les images, TEB, IAT, patchs, point d'entrée `lt_entry`; mode test `--test-ren <dll>` = GetSupportedModes de d3d.ren → 12 modes) · `build_linux.sh`, `gen_linux.py`.
Variables d'environnement : `LT_TRACE=1` (LoadLibrary/CreateFile/LoadString/DX + exceptions avec VA d'origine), `LT_TRACE_CALLS=1` (tous les appels Win32).

## 6. Lancer / tester
Dossier de travail (comme le vrai jeu) : contient `lithtech_linux`, `autoexec.cfg`, `Profiles/`, `Save/`, `d3d.ren`, `ltmsg.dll`, `mss32.dll`… et `assets` (= main.rez décompressé).
```
unzip main.rez -d game ; ln -s game/assets assets
./lithtech_linux -rez assets        # CHEMIN RELATIF obligatoire (un chemin absolu /unix déroute le code de chemins à antislashs du moteur)
```
Attendu : « Game initialized in … » puis boucle principale (timeout = normal). Sans args : `[MessageBox] LithTech: No game resources specified.`
GL/Xvfb (test) : `LIBGL_ALWAYS_SOFTWARE=1 SDL_VIDEODRIVER=x11 xvfb-run -a -s "-screen 0 1920x1080x24 +extension GLX +extension RANDR +render" ./lithtech_linux -rez assets`. Prérequis 32 bits : libsdl2-2.0-0:i386, libgl1:i386, mesa dri i386 (voir `support/setup_env.sh`).

## 7. Rendu : état et décision à prendre
**Piste A — `opengl.ren` fourni (sources `opengl_talon-master.zip`)** : moteur de rendu OpenGL 4.6 complet pour AvP2 Talon. Il charge et s'initialise nativement chez nous (fenêtre SDL, contexte GL 4.5 core sur Mesa logiciel, repli depuis 4.6) puis **se refuse** : `CSHELL detect: unsupported DLL SHA256=6effcd9489c7efc1bf5d21316cff268256763e554d23d1ec4cc39a5ded7d41db`. Cause (src/subsystems/cshell/cshell_build.cpp) : il identifie le CSHELL par **SHA-256 exact** et utilise des RVA internes propres à chaque build : profil *Original* (e4f8fa8e…2146), profil *MSP* (9ca8f929…7b2), *Coop* non mappé. Le CSHELL.DLL de l'utilisateur est une 3ᵉ variante (build « Nina »/custom) → il faut soit **ajouter un profil** (cartographier les RVA du CSHELL de l'utilisateur ; il a le source dans avp2src), soit tester avec un CSHELL connu. Par ailleurs `src/subsystems/cshell/msp_compat.cpp` installe des **patchs moteur en mémoire** sur l'image de lithtech.exe (RVA 0x33186 timer QPC, 0x9C130, 0x9B5B5 qualité de police…) après vérification de signature : dans notre build l'image d'origine à 0x401000 n'est qu'une copie de données, le code exécuté est le code traduit → ces patchs sont sans effet/invalides. Pistes : appliquer les mêmes patchs au niveau de la traduction (lift_all.py) ou les désactiver ; docs utiles dans le zip : `skills.md`, `engine_layout.md`, `lt_renderer_abi.h`.
**Piste B — original `d3d.ren` (DX7)** : nécessite de terminer `dx7.c` (Direct3DDevice7 → OpenGL : états, textures DDS/surfaces, DrawPrimitive*/VB, Clear, viewport/transforms, Blt/Flip→SwapWindow).
Recommandation : piste A si le profil CSHELL peut être cartographié (qualité de rendu réelle, c'est le renderer cible du projet) ; sinon B comme base de comparaison.

## 8. Problèmes ouverts / à surveiller
1. Fuite mémoire lente (~2 Mo/s en boucle de menu) : suspect = couche DX7/GDI (CreateDIBSection jamais libéré, Lock de surfaces…) ou allocations moteur.
2. Évènements : relier SDL (clavier/souris/fermeture) à `PeekMessage` et aux devices DirectInput (`dev_GetDeviceState`, mapping scancodes HID→DIK).
3. Audio : Miles nul (`AIL_waveOutOpen` renvoie 1). Binkw32 (vidéo) non chargé. `DirectSoundCreate` renvoie « pas de driver ».
4. Messages « Symbol not found - [BasicLayout]:… » et « duplicate symbol … MaxHitPoints » du parseur d'attributs du jeu : probablement données du pack (non vérifié face à Windows).
5. SEH matériel + exceptions C++ implémentés mais peu testés (le handler de crash du jeu écrit bien `crashlog.txt`).
6. `W_GetFileTime`/horodatages, `GetDiskFreeSpace` etc. : approximations. `GetModuleHandle(NULL)=0x400000` pointe sur l'en-tête PE d'origine mappé.
7. Non testé : Windows réel (seulement Wine 9) ; parties multi-joueur/réseau (winsock→BSD écrit, jamais exercé).

## 9. Pièges appris (utile pour ne pas les refaire)
- Le chargeur de modules doit avoir un **mutex récursif** (DllMain rappelle GetModuleHandle).
- `realpath` fortifié exige un tampon de PATH_MAX (4096).
- `pthread_exit` demande libgcc_s i386 : remplacé par setjmp/longjmp.
- Les fonctions GL Windows sont stdcall, celles de l'hôte cdecl → thunks avec taille d'arguments (parser les en-têtes Mesa : regex `\s*APIENTRY`).
- Les stubs d'imports non implémentés doivent connaître la taille d'arguments (stdcall) ; table dérivée des bibliothèques mingw + suffixe `@N` des noms Miles.
- Casse + antislashs : `win2unix()` (k32_file.c) ; bug corrigé : résolution relative sautait le dossier courant.
- Ne pas faire `rm` des sources C avant de relancer des scripts qui les lisent (lift_stubs avait écrasé son propre fichier).
- Le système de fichiers de /tmp refusait parfois l'exécution : `chmod +x` ou copier ailleurs.
- Quand une commande dépasse 300 s dans l'outil : la scinder ; lancer les gros builds avec `timeout`.

## 10. Reprise rapide (checklist pour la nouvelle session)
1. Téléverser `lt_re_project.tar.gz` + les fichiers du §3. Décompresser, lancer `sh lt_re/support/setup_env.sh`.
2. Réexporter si besoin : `python3 lift_all.py && python3 gen_image.py` (utilise `data/code_units.txt`, pas besoin de Ghidra), puis `cd linux && sh build_linux.sh`.
3. Lancer le test §6 pour vérifier l'état.
4. Décider piste A/B (§7) avec l'utilisateur ; question à lui poser : « peux-tu fournir/identifier le build exact de CSHELL.DLL (source) et ses RVA, ou un CSHELL reconnu par opengl.ren ? »


---
# SESSION 2 ADDENDUM (Nov 2026)

## Which lithtech.exe
- `lithtechreal.exe` (962,560 B, sha256 62e63afc...605d) = the REAL target; section layout matches the original lift (.text 0x401000, .rdata 0x4cb000, .rsrc 0x4ef000).
- `lithtech.exe` (937,984 B, sha256 62c8f980...b0be) = the MSP build: bytes at RVA 0x33186 = E8 A5 8F 06 00 (signature checked by opengl_talon msp_compat.cpp). Pipeline works for it too.
- Pick with `export LT_EXE=/path/to/exe` before the steps below. Nothing is hardcoded to the old layout any more (layout.h/layout.json are generated).

## Ghidra no longer needed
`disco.py <exe> data/code_units.txt` = recursive-descent code discovery (capstone). Validated on the real exe against the old Ghidra export:
Ghidra 259,248 instructions, mine 263,216; every Ghidra instruction is present, 3,968 extra (12 KB, spot-checked as real code), 0 overlaps, 1.4 KB of non-padding bytes left uncovered (ctype/index/jump tables).
`data/code_units_ghidra.txt` = the old export, kept as reference.

## Rebuild (about a minute on a weak box, mostly the assembler)
```
apt: gcc-multilib libc6-dev-i386 libsdl2-2.0-0:i386 libgl1:i386 libgl1-mesa-dri:i386 libglx-mesa0:i386 mesa-common-dev xvfb ; pip: pefile capstone
export LT_EXE=/path/to/lithtechreal.exe
python3 disco.py $LT_EXE data/code_units.txt      # optional, a validated data/code_units.txt is shipped
python3 build_images.py && python3 lift_all.py
cd linux && sh build_linux.sh                      # -> linux/lithtech_linux
```
Game dir: contents of forclaude.7z + `python3 rez_extract.py assets.rez -o .` (assets.rez is a REAL REZ now, extracts to ./assets, 1918 files, CSHELL.DLL sha 6effcd94...) ; run `./lithtech_linux -rez assets`.
The engine loads the renderer by name (RENDERDLL "d3d.ren" in autoexec.cfg): copy opengl.ren over d3d.ren to use it.

## Status
- Real exe, original d3d.ren: no exceptions, loads DLLs/attributes/renderer init/textures, runs until timeout. Draws nothing (D3D7 draws are no-ops).
- opengl.ren as d3d.ren: loads at its preferred base 0x6d300000, SDL window + GL 4.5 context (4.6 refused by Mesa swrast), then an empty-name LoadLibrary() fails and the engine prints "Couldn't set render mode!". Root cause NOT found yet.
  Correction to section 7: "CSHELL unsupported" is only logged; in the renderer source the profile gates the options menu, material authoring and msp_compat patches (the latter only for Build::AVP2Original), not rendering.
  Next: LT_TRACE_CALLS=1 around that LoadLibrary to find the caller; check renderer_exports.cpp (~line 2027, glGetString version check) and what the renderer needs from GL 4.6; try a host with real GL 4.6.
- Still stubs/not done (see section 8): Miles audio null, DirectSound none, DirectInput/PeekMessage no events (SDL not wired), Binkw32/Smackw32 not working, auto-stubs for unimplemented imports, d3d7 drawing.
- Game DLLs from avp2src/opengl_talon are PE DLLs: they run through the shim's PE loader as native i386 code (no ELF port needed or possible: the engine ABI is MSVC). Not compiled in this session.
- Fixed: pe.c MAIN_RSRC_RVA was hardcoded for one layout; now derived from layout.h.


---
# SESSION 3 ADDENDUM: native ELF renderer (opengl.ren as a Linux shared object)

## Result
`port/` builds the AVP2 OpenGL renderer (opengl_talon sources, + a Win32-surface layer "winport") as `opengl.ren`, a 32-bit ELF shared object
(`make -j$(nproc)` in port/, ~1.5 min on one slow core; needs g++-multilib, libgl1:i386, imgui 1.90.9 checked out at ../imgui or IMGUI=path).
The native engine (`lt_re/linux/lithtech_linux`) `dlopen`s it when the engine calls LoadLibrary("d3d.ren") (ELF magic detected in pe.c; GetProcAddress -> dlsym).
Verified in this sandbox: engine boots on `lithtechreal.exe`, loads the renderer, creates the GL context, and renders the NINA main menu (screenshot: native_linux_menu.png).
No Wine, no PE renderer. Game DLLs (CSHELL/CRES/SRES/server/OBJECT.LTO) are still PE files run by the shim's native PE loader (x86 code executes natively; this is not emulation).

## The earlier "Couldn't set render mode!" was the sandbox GL, not a bug
Renderer log: `Shader 'renderer.2d' vertex compile failed: GLSL 4.60 is not supported` (opengl.ren needs real OpenGL 4.6; the sandbox only has Mesa llvmpipe 4.5).
The "LoadLibrary()" with an empty name is just the engine's rollback: SetRenderMode (0x471240) failed, so it tries to restore the previous, all-zero mode.
Test without a 4.6 GPU: `MESA_GL_VERSION_OVERRIDE=4.6 MESA_GLSL_VERSION_OVERRIDE=460 LIBGL_ALWAYS_SOFTWARE=1 ./lithtech_linux -rez assets`.
Renderer logging: `AVP2_OGL_LOG=1` (file name is currently a literal 'Z:\\...log' in the cwd: path code still joins with backslashes; harmless, cosmetic TODO).

## How the port works (winport)
- `winport/windows.h` (+ ddraw.h from MinGW public headers, wincrypt.h): Win32 types/consts/COM macros. Calls that need a window, GL context, input, cursor, display, memory or crypto are
  declared with asm labels `W_<name>` and resolve at dlopen time to the host's existing SDL2-backed Win32 layer (exported via `linux/dyn.list` = `-Wl,--dynamic-list`). One window/input authority.
- `winport/winport.cpp`: native pieces: QPC/ticks/Sleep (clock_gettime), SRW locks, resources (28 GLSL shaders embedded by `gen_shaders.py` -> `src/shader_table.cpp`), LoadStringA, secure-CRT string functions,
  registry (none: returns not found), GetModuleFileName for the module itself (dladdr), AdjustWindowRectEx/MapWindowPoints.
- `winport/imgui_impl_winport.cpp` + `backends/imgui_impl_win32.h`: ImGui platform backend over the same host input APIs.
- Source edits are `#ifdef AVP2_LINUX`: gl_loader.cpp (gl* via host `W_lt_GetGLProcNative` = SDL_GL_GetProcAddress, cdecl; wgl* stay stdcall via host), dllmain.cpp (ELF constructor/destructor), 5 path-splitting sites (both separators).
- Exports `GetSupportedModes/FreeModeList/RenderDLLSetup` are aliases of the rdll_* functions via `--defsym` in the Makefile. libstdc++/libgcc are linked statically; only libGL.so.1, libc, libdl, libpthread are needed.
- Host changes (lt_re/linux): pe.c ELF LoadLibrary/GetProcAddress (+LT_TRACE diagnostics: caller VA, RMode dump), gl.c W_lt_GetGLProcNative, build_linux.sh dyn.list, default LT_EXE=lithtechreal.exe.

## Environment trap
Installing i386 dev packages here pulled `python3.12:i386` over the amd64 python (capstone then fails with "wrong ELF class"). Fix: `apt-get install python3.12:amd64 python3.12-minimal:amd64 libpython3.12-minimal:amd64 libpython3.12-stdlib:amd64`.

## Not done / still stubs (unchanged, listed honestly)
Keyboard/mouse events (SDL -> PeekMessage/DirectInput, GetAsyncKeyState backend), audio (Miles/DirectSound), Bink/Smack video, auto-generated stubs for unimplemented imports, in-game testing beyond the menu,
renderer engine-hooks (hook_manager/high_refresh_timing/msp_compat patch the mapped ORIGINAL bytes, which are not executed in this design; they are skipped for unsupported builds/signature mismatch - unverified at runtime),
CSHELL profile for your CSHELL.DLL (only affects the renderer's options-menu integration), memory growth ~2 MB/s seen earlier in menu (not re-measured).
