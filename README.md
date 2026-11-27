<p align="center"><img src="img3.jpg" alt="Nina port image"></p>
<p align="center"><img src="img2.jpg" alt="Nina port image"></p>
<p align="center"><img src="img1.jpg" alt="Nina port image"></p>

<div align="center">
  <img src="assets/icon.png" alt="Nina Agent Chronicles" width="148">
  <h1>NINA / LINUX PORT</h1>
  <p><b>LithTech Talon, rebuilt for Linux.</b></p>
</div>

---

### What this is

Source-only snapshot of the Linux rebuild of **Nina Agent Chronicles**: the native engine shim, static-lift tooling, a replacement OpenGL renderer, and the game-DLL patches.

### Layout

| Path | Purpose |
|---|---|
| `lt_re/` | Disassembly/debugging tools, Win32 shim, decompiled reference code |
| `port/` | Native OpenGL renderer and Win32 compatibility layer |
| `game-dlls/` | Linux-side rebuild patches for the game DLLs |
| `docs/` | Work log and project notes |

### Scope

Private working repo. Original executables, generated lift output, `.REZ` game archives, and third-party dependencies stay local and are not part of this snapshot. The work log lives in `docs/HANDOFF.md`.

<div align="center"><sub>SOURCE ONLY · PRIVATE · IN PROGRESS</sub></div>
