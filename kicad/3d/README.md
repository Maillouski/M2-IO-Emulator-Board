# 3D models

| File | Used by | Origin | License |
|---|---|---|---|
| `Arduino_Mega2560_Rev3e.stpz` | MEGA1 (Arduino Mega 2560, board-only footprint) | Built from Arduino's official CAD files for the Mega 2560 Rev3e (`A000067-cad-files.zip`, Eagle board), with KiCad library 3D models placed on its parts | CC BY-SA 4.0 (Arduino; KiCad libraries) |
| `USB_B_boite_H11.wrl` | MEGA1 (USB-B jack, plain box 16.6 × 12.2 × 11 mm) | made for this project | CC BY-NC-SA 4.0, like the board |

All other parts use the standard KiCad 10 3D library (`${KICAD10_3DMODEL_DIR}`).
The JST NH headers (J3, J4, J5, J14) have no 3D model here: KiCad will report them as missing, which does not affect the
Gerbers.
