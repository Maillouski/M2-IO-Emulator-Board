# Bill of materials — M2 IO Emulator Board

**English** | [Français](BOM.fr.md)

Quantities are **per board**. 121 references, checked one by one against the schematic.

**DigiKey import:** [`BOM-digikey.csv`](BOM-digikey.csv) (Quantity, Digi-Key Part Number, Manufacturer Part Number,
Manufacturer, Customer Reference). Upload it to the DigiKey BOM Manager or a myList, then multiply by the number of boards.

**JLCPCB assembly:** to have JLCPCB solder the SMD parts, see
[`../fabrication/jlcpcb/`](../fabrication/jlcpcb/README.md) (LCSC numbers, BOM and CPL files).

Every DigiKey number below was checked live on digikey.ca on 2026-10-12, in CAD, cut tape, at quantity 1, without tax or
shipping. Prices and stock change, so check again before you order.

## Parts on the board

| Qty | References | Value | Manufacturer part | DigiKey | Note |
|---:|---|---|---|---|---|
| 20 | C1-C16, C18, C20-C22 | 100 nF 50 V X7R 0805 | YAGEO CC0805KRX7R9BB104 | 311-1140-1-ND | |
| 2 | C19, C23 | 10 µF 16 V X7R 0805 | Samsung CL21B106KOQNNNG | 1276-6472-1-ND | |
| 1 | C17 | 100 µF 16 V, Ø 6.3 mm, 2.5 mm pitch | Panasonic EEU-FC1C101 | P11198-ND | low stock (15); any 100 µF ≥ 16 V Ø 6.3 / P2.5 fits |
| 1 | D1 | green LED, 3 mm | Kingbright WP710A10GD | 754-1603-ND | "CAB PWR LED" |
| 1 | J1 (CN1) | 2 × 25 IDC header | 3M N2550-6002-RB | MHC50K-ND | see "Open points" |
| 1 | J2 (CN2) | 2 × 13 IDC header | 3M N2526-6002-RB | MHC26K-ND | see "Open points" |
| 1 | J3 (CN3) | 10-pin JST NH, 2.5 mm | JST B10P-SHF-1AA | 455-B10P-SHF-1AA-ND | ⚠️ not stocked at DigiKey, minimum order 250 |
| 2 | J4 (CN5), J5 (CN6) | 12-pin JST NH, 2.5 mm | JST B12P-SHF-1AA | 455-B12P-SHF-1AA-ND | ⚠️ not stocked at DigiKey, minimum order 6 500 |
| 5 | J6-J10 | 1 × 8 pin header | Würth 61300811121 | 732-5321-ND | to the Arduino Mega |
| 1 | J11 | 1 × 10 pin header | Würth 61301011121 | 732-2670-ND | to the Arduino Mega |
| 1 | J12 | 2 × 18 pin header | Würth 61303621121 | 732-5309-ND | to the Arduino Mega |
| 1 | J13 | VGA (DE-15 HD) female, right angle | Amphenol L77HDE15SD1CH4F | L77HDE15SD1CH4F-ND | VIDEO IN |
| 1 | J14 | 5-pin JST NH, 2.5 mm | JST B5P-SHF-1AA | 455-B5P-SHF-1AA-ND | VIDEO OUT |
| 4 | JP1, JP2-JP4 | 1 × 3 pin header | Würth 61300311121 | 732-5316-ND | JP1 = drive board power, JP2-JP4 = video amp |
| 3 | JP5-JP7 | 1 × 2 pin header | Würth 61300211121 | 732-5315-ND | 75 Ω VGA termination |
| 7 | SH1-SH7 | jumper | TE 382811-8 | A26228-ND | sold by 10 |
| 13 | R1-R13 | 4.7 kΩ 1 % 0805 | YAGEO RC0805FR-074K7L | 311-4.70KCRCT-ND | input pull-ups |
| 25 | R14-R37, R46 | 1 kΩ 1 % 0805 | YAGEO RC0805FR-071KL | 311-1.00KCRCT-ND | |
| 8 | R38-R45 | 10 kΩ 1 % 0805 | YAGEO RC0805FR-0710KL | 311-10.0KCRCT-ND | |
| 1 | R47 | 470 Ω 1 % 0805 | YAGEO RC0805FR-07470RL | 311-470CRCT-ND | composite sync series resistor; low stock (51) |
| 3 | R48-R50 | 75 Ω 1 % 0805 | YAGEO RC0805FR-0775RL | 311-75.0CRCT-ND | VGA termination (through JP5-JP7) |
| 3 | R51-R53 | 604 Ω 1 % 0805 | YAGEO RC0805FR-07604RL | 311-604CRCT-ND | video amp feedback |
| 3 | R54-R56 | 200 Ω 1 % 0805 | YAGEO RC0805FR-07200RL | 311-200CRCT-ND | video amp gain (gain = 4.02) |
| 3 | R57-R59 | 33 Ω 1 % 0805 | YAGEO RC0805FR-0733RL | 311-33.0CRCT-ND | video amp output |
| 1 | SK1 | DIP-18 socket | TE 1-2199298-5 | A120350-ND | for U1 |
| 2 | SW1, SW2 | 6 × 6 mm tactile switch | TE 1825910-6 | 450-1650-ND | TEST, SERVICE |
| 4 | TP1-TP4 | test point | Keystone 5002 | 36-5002-ND | |
| 1 | U1 | ULN2803A, DIP-18 | STMicroelectronics ULN2803A | 497-2356-5-ND | lamps, meters, relay; goes in SK1 |
| 1 | U2 | 74HCT86, SOIC-14 | Nexperia 74HCT86D,653 | 1727-6360-1-ND | composite sync (H XOR V, then inverted) |
| 1 | U3 | OPA3355EA, TSSOP-14 | Texas Instruments OPA3355EA/2K5 | 296-29279-1-ND | triple video amplifier (R, G, B) |

Board-only items, not in the BOM: H1-H4 (mounting holes), LOGO1 (Creative Commons logos), MEGA1 (3D model of the Mega).

## Off-board

| Qty | Item | Manufacturer part | DigiKey | Note |
|---:|---|---|---|---|
| 1 | Arduino Mega 2560 Rev3 | Arduino A000067 | 1050-1018-ND | plugs into J6-J12 (included in the CSV) |
| 1 | HDMI → VGA adapter | any | — | only if you drive the arcade monitor from an HDMI source |

## Cost

About **60 CAD per board** in parts at quantity 1 (2026-10-12), without the Arduino Mega (74.74 CAD) and without J3-J5. Ordering
for several boards lowers the passive prices a lot.

## JST NH headers (J3, J4, J5)

DigiKey does not stock B10P-SHF-1AA and B12P-SHF-1AA (minimum 250 and 6 500 pieces). They are easy to find at LCSC
(C160365 and C160367), Mouser or other JST distributors. B5P-SHF-1AA (J14) is in stock at DigiKey.
