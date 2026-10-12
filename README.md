# M2 IO Emulator Board

**English** | [Français](README.fr.md)

A drop-in replacement for the **Sega 837-10539 I/O board** of the **Daytona USA twin** cabinet (Sega Model 2), built around an
**Arduino Mega 2560**. It lets an emulator drive the original cabinet: controls, lamps, meters, the original drive board (force
feedback) and the original arcade monitor.

![Board, 3D view](docs/board-3d.png)

> **Status: prototype.** The design passes DRC and ERC, but no board has been built or tested yet. Read
> [Open points](#open-points) before you order.

## What it does

The idea is simple: pull the Sega I/O board out of the cabinet and put this one in its place. It has the same size, the same
mounting holes and the same connector names, so the original harness plugs straight in. Nothing gets cut or rewired.

Once it's in, the Arduino Mega becomes the bridge between the emulator and the cabinet. It reads the controls and drives
everything the original board used to drive:

- **Controls** — steering, accelerator, brake, shifter, coin, START, the VR view buttons, TEST and SERVICE.
- **Lamps, meters and relay** — switched by a socketed ULN2803A, so the original bulbs and coin meters keep working.
- **Force feedback** — the original drive board stays in the cabinet and gets its commands from the Mega, so the wheel keeps
  its original force feedback.
- **Video** — a VGA input goes to the original arcade monitor, with composite sync built on the board. A small switchable video
  amplifier lifts a PC or HDMI-to-VGA signal to the level the tube expects.

A few practical details make bring-up easier: TEST and SERVICE buttons right on the board, a power LED, test points for each
supply, and a jumper (JP1) to choose whether the drive board logic runs from the Mega's 5 V or from the cabinet's.

## Video jumpers

| VIDEO IN (J13) | JP2-JP4 (VIDEO AMP) | JP5-JP7 (VGA TERM 75 Ω) |
|---|---|---|
| PC / HDMI-VGA adapter | ON | ON |
| Arcade RGB | OFF | OFF |

The same table is printed on the board.

## 3D views

Rendered with KiCad 10 from the files in this repository (the JST NH connectors have no 3D model, so only their pads show).

| | |
|---|---|
| ![Perspective view](docs/board-3d-back.png) | ![Video section close-up](docs/board-video.png) |
| Perspective view | Video section: VGA in, OPA3355 amplifier, jumpers and settings table |
| ![Top view](docs/board-top.png) | ![Bottom view](docs/board-bottom.png) |
| Top | Bottom |

## Repository

| Path | Contents |
|---|---|
| `kicad/` | KiCad 10 project: schematic, PCB, design rules, project footprint library (`interface-borne.pretty`), 3D models |
| `fabrication/` | Gerbers, Excellon drill files and drill maps (`gerbers/`), the same files zipped for the fab, pick-and-place file |
| `bom/` | Full BOM ([`BOM.md`](bom/BOM.md)) and DigiKey import file ([`BOM-digikey.csv`](bom/BOM-digikey.csv)) |
| `docs/` | Schematic PDF, board renders |

Board: 2 layers, 180 × 190 mm. Gerbers come from the PCB's own plot settings (KiCad 10).

## Open points

Check these before you order or power anything:

1. **JST NH pitch.** CN3, CN5, CN6 and J14 use JST NH footprints at **2.5 mm pitch**. The pitch on the original Sega board has
   not been measured yet. If it turns out to be 2.54 mm, these footprints must change.
2. **J14 pin order** (R, G, B, sync, ground) is still provisional. Check it against your cabinet's video plug.
3. **Video level.** The amplifier gain (4.02, set by R51-R56) assumes a source that outputs 0.7 V into 75 Ω. This has not been
   measured. Change R54-R56 to adjust it.
4. **CN1 and CN2** are plain 3M four-wall headers. The original board uses headers with ejector latches, so the plug goes in but is
   not held.
5. **Firmware** for the Mega is not part of this repository.

## 3D models

The Arduino Mega model in `kicad/3d/` is derived from Arduino's CAD files (CC BY-SA 4.0) and KiCad library models; see
[`kicad/3d/README.md`](kicad/3d/README.md). The JST NH connectors have no 3D model in this repository.

## Credits

Sources used for this board: SEGA Daytona USA manuals; MAME (Dirk Best for the Model 1 I/O board; R. Belmont, O. Galibert,
ElSemi, A. Salese, M. Daniels for Model 2); M2Pac by BigPanik (Gamoover); DaytonaUSB by SailorSat; BackForceFeeder by njz3; MEGA
adapters by Tibal; the MiSTer project (video to arcade monitor).

Not affiliated with or endorsed by SEGA.

## License

© 2026 Nicolas Mailloux. **CC BY-NC-SA 4.0** — see [`LICENSE`](LICENSE).
You may build, use, modify and share this board, as long as you credit the author, keep the credits, and share changes under the
same license. **No commercial use**: don't sell the board, the files or a derivative.
