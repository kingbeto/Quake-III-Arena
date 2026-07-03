# Quake III Arena — GPL Source

Official GPL source release of **Quake III Arena** (id Software, 2005). This tree builds the game client and native modules on **macOS** (Apple Silicon and Intel) and **GNU/Linux**.

Game assets (`baseq3/*.pk3`) are **not** included. You need a legal copy of Quake III Arena.

## Requirements

| Platform | Toolchain | Runtime |
|----------|-----------|---------|
| **macOS** 11+ | Xcode Command Line Tools (`clang`, `make`) | OpenGL (system framework) |
| **Linux** | `gcc`, `g++`, `make`, `nasm` | X11 with DGA and XVideo extension headers |

## Game data

The engine expects a `baseq3/` directory containing `.pk3` files from a retail install.

**macOS** — either:

- Place `baseq3/` next to `Quake3.app` (same folder as the `.app`), or
- On first launch, select the folder that **contains** `baseq3/` (not `baseq3` itself).  
  Example: `.../steamapps/common/Quake 3 Arena` when pak files live in `.../Quake 3 Arena/baseq3/`.

**Linux** — put `baseq3/` where the build expects it (see [Linux build](#linux) below; default layout uses `run/baseq3/` relative to the repo).

---

## macOS

Build from `code/macosx/`:

```bash
cd code/macosx
make
```

Apple Silicon (default):

```bash
make          # ARCH=arm64
```

Intel Mac:

```bash
make ARCH=x86_64
```

Output: `code/macosx/build/Quake3.app` with `qagame`, `cgame`, and `ui` bundles inside the app.

Run:

```bash
open build/Quake3.app
```

### macOS notes

- Defaults to **windowed** mode (`r_fullscreen 0`). Legacy OpenGL fullscreen is unreliable on modern displays; toggle with `r_fullscreen` in-game if you want to try it.
- Mouse input does not apply legacy macOS mouse scaling; sensitivity may differ from the original Mac release.
- **Unsigned builds** are blocked by Gatekeeper on other machines. For distribution, sign and notarize the `.app` (`codesign`, `notarytool`), or tell users to right-click → Open on first launch.

Clean:

```bash
make clean
```

---

## Linux

The upstream Linux build uses the Makefile in `code/unix/`. From the `code/` directory:

```bash
cd code/unix
make
```

Release build:

```bash
make build_release
```

Typical dependencies (Debian/Ubuntu):

```bash
sudo apt install build-essential nasm libx11-dev libxxf86dga-dev libxxf86vm-dev
```

By default, binaries and `baseq3/` are expected under `run/` at the repository root (`../run` relative to `code/unix`). Adjust `BDIR` in `code/unix/Makefile` if you use a different layout.

An older **cons**-based build script is also in the tree (`code/unix/cons`); the Makefile is the usual path today.

Further historical notes: `code/unix/README.Linux`.

---

## Repository layout

```
code/           Engine, renderer, game logic, platform layers
  macosx/       macOS client build (Makefile → Quake3.app)
  unix/         Linux client/server build
  game/         Server game module (qagame)
  cgame/        Client game module
  q3_ui/        Menu UI module
lcc/            LCC compiler (QVM bytecode; optional)
q3asm/          QVM assembler
q3map/          BSP map compiler (Radiant)
q3radiant/      Q3Radiant map editor
```

Tools under `q3map/`, `q3radiant/`, and `lcc/` are editor/compiler utilities, not required to play the game.

---

## License

See [COPYING.txt](COPYING.txt) for the GNU General Public License.

Some bundled components use separate licenses (zlib/unzip, MD4, Berkeley `bg_lib`, ADPCM, Independent JPEG Group). See file headers and per-package `README` files under `code/jpeg-6/`, `libs/jpeg6/`, and similar paths for attribution.
