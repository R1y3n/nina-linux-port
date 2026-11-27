# Native Linux build (no Wine)  -  lithtech_linux (32-bit ELF)

Build: `sh build_linux.sh`  (needs gcc -m32 / libc6-dev-i386; prerequisites: ../lifted_all.s, ../ltdata.bin, ../lttext.bin from lift_all.py / gen_image.py)
Run:   `./lithtech_linux [engine args]`  from the game folder (needs mss32.dll next to it only as a file name; it is NOT loaded - audio is shimmed).
Debug: `LT_TRACE=1` logs LoadLibrary/LoadString; `LT_TRACE_CALLS=1` logs every Win32 call the engine makes.

How it works
- Translated original code (lifted_all_elf.s): same machine code as lithtech.exe, labels instead of addresses.
- start.c maps the original images at their ORIGINAL addresses (0x400000 header, 0x401000 .text bytes, 0x4cb000 data, 0x4ef000 .rsrc),
  creates a Windows-style TEB through set_thread_area/fs (fs:[0] SEH chain, TLS slots, last error), fills the import table with shim functions,
  patches code pointers stored in data, then jumps to the original entry point.
- Win32 shim (written from scratch, no Wine code): core.c (handles, TEB, SEH dispatch incl. RaiseException/RtlUnwind, SIGSEGV/SIGFPE -> exceptions),
  k32_file.c (files with case-insensitive path mapping, FindFirstFile, time, FormatMessage incl. string/module messages),
  k32_sys.c (heaps, VirtualAlloc, threads via pthread, events, critical sections, TLS, env, locale/codepage),
  pe.c (real PE loader for LoadLibrary of game DLLs/.ren/.lto, GetProcAddress, resources, LoadString, auto stubs for unimplemented imports),
  u32.c (user32/gdi32 headless bookkeeping, ole32/dinput = "not available", winsock -> BSD sockets).

Verified (native, no Wine): no args -> "[MessageBox] LithTech: No game resources specified." (same message as the original under Wine);
`-rez <bad path>` -> loads ltmsg.dll through the PE loader, reads the localized string, exits 0.

NOT done / limits (be aware)
- No renderer: d3d.ren (Direct3D/DirectDraw) cannot work on Linux. You need a Linux render module with the same RenderStruct interface (your replacement renderer).
- Window/input are headless stubs (no X11/SDL yet); PeekMessage never delivers input. Hook an SDL2 backend in u32.c.
- Audio: Miles (mss32) calls are stubs returning 0 (auto-generated). DirectMusic/DirectInput report unavailable.
- SEH from hardware faults is implemented but untested; C++ exceptions via RaiseException/RtlUnwind untested.
- Only the engine EXE flow has been exercised; game DLLs (cres/cshell/object.lto) need testing with real AvP2 data.
- The fake PE header page at 0x400000 is the original header bytes, resources are the original .rsrc.

## Renderer (d3d.ren) status
- d3d.ren (and d3d_1.ren, byte-identical) is LithTech's DirectX 7 renderer plugin: imports ddraw.dll (DirectDrawCreateEx / DirectDrawCreate / DirectDrawEnumerateA(+ExA)),
  exports RenderDLLSetup, GetSupportedModes, FreeModeList; RenderDLLSetup fills 38 function pointers at RenderStruct+0x70..; RMode = 0x214 bytes
  {hw, dll[256], name[128], desc[128], w, h, bpp, next}.  It also carries IIDs for DX7 (IDirectDraw7/IDirect3D7) and a DX6 fallback (IDirectDraw4/IDirect3D3).
- dx7.c + gen_dx7.py: DirectDraw7/Direct3D7 compatibility layer. Milestone 1 done: `./lithtech_linux --test-ren d3d.ren` loads the ORIGINAL d3d.ren with the PE loader and
  GetSupportedModes returns 12 modes. All other COM methods are generated, size-correct stubs that log "DX unimplemented: ..." (136 slots) and fail safely.
- Not done: CreateSurface/Flip/Lock, IDirect3D7::EnumDevices/CreateDevice, texture formats, Direct3DDevice7 -> OpenGL. Wine's ddraw/wined3d implement exactly this API
  (LGPL, usable as a reference) but cannot be lifted out standalone; the alternative is a native renderer implementing RenderStruct (needs the Talon SDK header for exact layout).

## Running the game natively (current state)
Layout (like the real game folder): working dir = the folder with lithtech_linux, autoexec.cfg, Profiles/, Save/, d3d.ren, ltmsg.dll, mss32.dll ... and assets = the unzipped main.rez (`assets/`).
```
./lithtech_linux -rez assets          # use a RELATIVE rez path, as the original game is launched (an absolute /unix path confuses the engine's backslash path code)
```
Reached natively (no Wine), with the original d3d.ren and the DX7 compatibility layer:
startup -> cshell/cres/server DLLs via the PE loader -> attributes -> renderer init (surfaces, flip chain, textures, vertex buffers, device) -> "Game initialized" / "LithTech build ... initialized"
-> main menu assets (interface textures, menu loop sounds, localized strings) -> runs its main loop (~50 MB RSS after 20 s, 5 threads) with nothing drawn yet (Direct3D7 draw calls are no-ops).

Added in this round: Miles (mss32) core (memory/lock/startup), DirectInput keyboard+mouse devices (no events yet), DirectSound/OpenFile/ini/system-dir APIs, window-proc get/set, surface/vertex-buffer release (a leak made the engine run out of memory),
case-insensitive path resolver fix for RELATIVE paths, translation map (LT_TRACE shows crash locations as ORIGINAL exe addresses + a call chain), msvcrt layer (real C runtime for modern DLLs; Windows FILE/wchar_t translated),
condition variables / SRW locks / wide-char file APIs, real MD5/SHA-1/SHA-256 for the Crypt API, WGL + OpenGL via SDL2 (loaded at run time; stdcall->cdecl thunks sized from the Mesa headers; contexts fall back to the highest GL the host supports).

opengl.ren (the modern renderer in your folder) status: loads and runs its init natively, creates an SDL window and a GL 4.5 core context (software Mesa under Xvfb), then stops itself:
"CSHELL detect: unsupported DLL SHA256=6effcd94... (CSHELL.DLL)" and its own strings mention engine patches against the original lithtech.exe image ("MSP compat ... no engine patches installed").
It therefore expects a known CSHELL build and to patch the real exe in memory; with the translated engine those patches would not reach the executing code. Needs your input (see questions).

Not done: Direct3D7 -> OpenGL drawing for the original d3d.ren; input events from SDL into DirectInput/window messages; audio output (Miles is a null device); Binkw32 video.
Debug switches: LT_TRACE=1 (LoadLibrary/CreateFile/LoadString/DX log + exceptions with original addresses), LT_TRACE_CALLS=1 (every Win32 call).
Runtime needs for GL: 32-bit libSDL2 + Mesa (e.g. libsdl2-2.0-0:i386 libgl1:i386 libgl1-mesa-dri:i386).
