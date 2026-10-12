# M2 IO Emulator Board

A drop-in replacement for the **Sega 837-10539 I/O board** of the **Daytona USA twin** cabinet (Sega Model 2), built around an
**Arduino Mega 2560**. It lets an emulator drive the original cabinet: controls, lamps, meters, the original drive board (force
feedback) and the original arcade monitor.

![Board, 3D view](docs/board-3d.png)

> **Status: prototype.** The design passes DRC and ERC, but no board has been built or tested yet. Read
> [Open points](#open-points) before you order.

## What it does

- **Same size and holes as the Sega board** (180 × 190 mm, four Ø 4 mm holes 5.3 mm from the edges) and the same connector names
  (CN1, CN2, CN3, CN5, CN6): the original harness plugs in, nothing is cut.
- **CN1 (50 pins):** coin, TEST, SERVICE, START, VR1-VR4 and shifter inputs (4.7 kΩ pull-up, 1 kΩ / 100 nF filter), and lamp,
  meter and relay outputs through a ULN2803A (U1, socketed).
- **CN2 (26 pins):** steering, accelerator and brake potentiometers to the Mega's analog inputs (A0-A2), with RC filters.
- **CN6 / CN5 (12 pins each):** command byte to the drive board and its answer byte (1 kΩ series, 10 kΩ pull-up to the Mega 5 V), for the
  original force feedback.
- **CN3 (10 pins):** cabinet +5 V and ground. Cabinet +5 V is never tied to the Mega's 5 V.
- **JP1:** drive board logic supply. 1-2 = 5 V from the Mega, 2-3 = 5 V from the cabinet.
- **TEST and SERVICE** buttons on the board, **CAB PWR LED**, and test points for GND, +5 V Mega, +5 V cabinet and the drive board
  supply.
- **Video:** VGA in (J13) to the arcade monitor connector (J14, R/G/B + composite sync). U2 (74HCT86) makes negative composite sync
  from H and V sync. U3 (OPA3355, gain ≈ 4) can boost R/G/B for a 0.7 V VGA source.

## Video jumpers

| VIDEO IN (J13) | JP2-JP4 (VIDEO AMP) | JP5-JP7 (VGA TERM 75 Ω) |
|---|---|---|
| PC / HDMI-VGA adapter | ON | ON |
| Arcade RGB | OFF | OFF |

The same table is printed on the board.

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
