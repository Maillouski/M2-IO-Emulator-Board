# 3D models

**English** | [Français](README.fr.md)

| File | Used by | Origin | License |
|---|---|---|---|
| `Arduino_Mega2560_Rev3e.stpz` | MEGA1 (Arduino Mega 2560, board-only footprint) | Built from Arduino's official CAD files for the Mega 2560 Rev3e (`A000067-cad-files.zip`, Eagle board), with KiCad library 3D models placed on its parts | CC BY-SA 4.0 (Arduino; KiCad libraries) |
| `USB_B_boite_H11.wrl` | MEGA1 (USB-B jack, plain box 16.6 × 12.2 × 11 mm) | made for this project | CC BY-NC-SA 4.0, like the board |
| `JST_NH_B5P-SHF-1AA_simple.wrl`, `JST_NH_B10P-SHF-1AA_simple.wrl`, `JST_NH_B12P-SHF-1AA_simple.wrl` | J14, J3 (CN3), J4/J5 (CN5/CN6) | simplified models made for this project (plastic base 3.2 mm high, 5.6 mm deep; 0.64 mm pins from −3.4 to +9.2 mm), from the JST NH datasheet and DigiKey dimensions | CC BY-NC-SA 4.0, like the board |
| `RCJ-2223_generique.step` | J16 (Same Sky RCJ-2223, stacked RCA jack) | simplified model made for this project from the RCJ-22 datasheet dimensions (body, red and white insulators, barrels, pins); the side mounting ear is approximate | CC BY-NC-SA 4.0, like the board |

All other parts use the standard KiCad 10 3D library (`${KICAD10_3DMODEL_DIR}`); TP1-TP4 and U5 use the closest model it has (Keystone 5005-5009, QFN-32 5 × 5 with a 3.3 mm pad).
