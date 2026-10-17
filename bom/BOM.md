# Bill of materials — M2 IO Emulator Board

**English** | [Français](BOM.fr.md)

Quantities are **per board**. 167 references, checked one by one against the schematic (V3, 2026-10-16): 165 in the DigiKey
file, U4 from another source, and 1 not fitted (DNP).

**DigiKey import:** [`BOM-digikey.csv`](BOM-digikey.csv) (Quantity, Digi-Key Part Number, Manufacturer Part Number,
Manufacturer, Customer Reference). Upload it to the DigiKey BOM Manager or a myList, then multiply by the number of boards.

**JLCPCB assembly:** to have JLCPCB solder the SMD parts, see
[`../fabrication/jlcpcb/`](../fabrication/jlcpcb/README.md) (LCSC numbers, BOM and CPL files).

Every DigiKey number below was checked live on digikey.ca on 2026-10-16, in CAD, cut tape, at quantity 1, without tax or
shipping. Prices and stock change, so check again before you order.

## Parts on the board

| Qty | References | Value | Manufacturer part | DigiKey | Note |
|---:|---|---|---|---|---|
| 32 | C1-C16, C18, C20-C22, C24, C27-C29, C31, C33, C35, C36, C38, C43, C44, C46 | 100 nF 50 V X7R 0805 | YAGEO CC0805KRX7R9BB104 | 311-1140-1-ND | |
| 11 | C19, C23, C25, C26, C30, C32, C34, C37, C41, C42, C45 | 10 µF 25 V X5R 0805 | Samsung CL21A106KAYNNNE | 1276-2891-1-ND | same part as the JLCPCB assembly (C15850); any 10 µF ≥ 16 V X5R/X7R 0805 fits |
| 2 | C39, C40 | 10 nF 50 V X7R 0805 | YAGEO CC0805KRX7R9BB103 | 311-1136-1-ND | audio filter (V3) |
| 2 | C47, C48 | 22 µF 16 V X5R 0805 | Samsung CL21A226MOCLRNC | 1276-6780-1-ND | composite sync averaging; any 22 µF ≥ 10 V X5R/X7R 0805 fits |
| 1 | C17 | 100 µF 16 V, Ø 6.3 mm, 2.5 mm pitch | Panasonic EEU-FC1C101H | P19632CT-ND | same FC series as EEU-FC1C101, on tape; any 100 µF ≥ 16 V Ø 6.3 / P2.5 fits |
| 1 | D1 | green LED, 3 mm | Kingbright WP710A10GD | 754-1603-ND | "CAB PWR LED" |
| 1 | FB1 | ferrite bead, 600 Ω, 0805 | Murata BLM21PG601SN1D | 490-BLM21PG601SN1DCT-ND | V3; the schematic names Sunlord GZ2012D601TF (600 Ω at 100 MHz, the JLCPCB part), not sold by DigiKey |
| 1 | J1 (CN1) | 2 × 25 IDC header | 3M N2550-6002-RB | MHC50K-ND | see "Open points" |
| 1 | J2 (CN2) | 2 × 13 IDC header | 3M N2526-6002-RB | MHC26K-ND | see "Open points" |
| 1 | J3 (CN3) | 10-pin JST NH, 2.5 mm | JST B10P-SHF-1AA | 455-B10P-SHF-1AA-ND | ⚠️ not stocked at DigiKey (minimum 250) or Mouser: buy at LCSC (C160365), see [below](#jst-nh-headers-j3-j4-j5) |
| 2 | J4 (CN5), J5 (CN6) | 12-pin JST NH, 2.5 mm | JST B12P-SHF-1AA | 455-B12P-SHF-1AA-ND | ⚠️ not stocked at DigiKey (minimum 6 500) or Mouser: buy at LCSC (C160367), see [below](#jst-nh-headers-j3-j4-j5) |
| 5 | J6-J10 | 1 × 8 pin header | Würth 61300811121 | 732-5321-ND | to the Arduino Mega |
| 1 | J11 | 1 × 10 pin header | Würth 61301011121 | 732-2670-ND | to the Arduino Mega |
| 1 | J12 | 2 × 18 pin header | Würth 61303621121 | 732-5309-ND | to the Arduino Mega |
| 1 | J13 | VGA (DE-15 HD) female, right angle | Amphenol L77HDE15SD1CH4F | L77HDE15SD1CH4F-ND | VGA 24 kHz input |
| 1 | J14 | 5-pin JST NH, 2.5 mm | JST B5P-SHF-1AA | 455-B5P-SHF-1AA-ND | VIDEO OUT |
| 1 | J15 | HDMI type A receptacle, right angle | Amphenol 10029449-001RLF | 609-1010-1-ND | V3 HDMI input; the JLCPCB assembly uses 10029449-111RLF (C427307), out of stock at DigiKey; -001RLF is the part the KiCad footprint is drawn for |
| 1 | J16 | dual stacked RCA jack (red / white), right angle | Same Sky RCJ-2223 | CP-1435-ND | V3 stereo out: red = right, white = left |
| 5 | JP1, JP2-JP4, JP10 | 1 × 3 pin header | Würth 61300311121 | 732-5316-ND | JP1 = drive board power, JP2-JP4 = video amp, JP10 = HDMI chip 5 V |
| 5 | JP5-JP9 | 1 × 2 pin header | Würth 61300211121 | 732-5315-ND | JP5-JP7 = 75 Ω VGA termination, JP8 = screen select, JP9 = video source |
| 10 | SH1-SH10 | jumper | TE 382811-8 | A26228-ND | sold by 10 |
| 13 | R1-R13 | 4.7 kΩ 1 % 0805 | YAGEO RC0805FR-074K7L | 311-4.70KCRCT-ND | input pull-ups |
| 26 | R14-R37, R46, R60 | 1 kΩ 1 % 0805 | YAGEO RC0805FR-071KL | 311-1.00KCRCT-ND | R60 = HDMI hot-plug pull-up |
| 13 | R38-R45, R61-R65 | 10 kΩ 1 % 0805 | YAGEO RC0805FR-0710KL | 311-10.0KCRCT-ND | R61 = source select pull-up, R62-R65 = sync input pull-downs |
| 1 | R47 | 470 Ω 1 % 0805 | Stackpole RMCF0805FT470R | RMCF0805FT470RCT-ND | composite sync series resistor |
| 3 | R48-R50 | 75 Ω 1 % 0805 | YAGEO RC0805FR-0775RL | 311-75.0CRCT-ND | VGA termination (through JP5-JP7) |
| 3 | R51-R53 | 604 Ω 1 % 0805 | YAGEO RC0805FR-07604RL | 311-604CRCT-ND | video amp feedback |
| 3 | R54-R56 | 200 Ω 1 % 0805 | YAGEO RC0805FR-07200RL | 311-200CRCT-ND | video amp gain (gain = 4.02) |
| 3 | R57-R59 | 33 Ω 1 % 0805 | YAGEO RC0805FR-0733RL | 311-33.0CRCT-ND | video amp output |
| 2 | R66, R67 | 2.2 kΩ 1 % 0805 | YAGEO RC0805FR-072K2L | 311-2.20KCRCT-ND | composite sync averaging (with C47, C48) |
| 2 | SW1, SW2 | 6 × 6 mm tactile switch | TE 1825910-6 | 450-1650-ND | TEST, SERVICE |
| 4 | TP1-TP4 | test point | Keystone 5002 | 36-5002-ND | |
| 1 | U1 | ULN2803A, DIP-18 | STMicroelectronics ULN2803A | 497-2356-5-ND | lamps, meters, relay; soldered directly, no socket |
| 1 | U2 | 74HCT86, SOIC-14 | Nexperia 74HCT86D,653 | 1727-6360-1-ND | composite sync, negative whatever the H/V polarity (see the [README](../README.md#composite-sync)) |
| 1 | U3 | OPA3355EA, TSSOP-14 | Texas Instruments OPA3355EA/2K5 | 296-29279-1-ND | triple video amplifier (R, G, B) |
| 1 | U6 | AT24C02, SOIC-8 | Microchip AT24C02C-SSHM-T | AT24C02C-SSHM-TCT-ND | EDID EEPROM on the HDMI DDC lines (address 0x50, write protect tied low), powered by the HDMI +5 V; comes blank |
| 1 | U4 | CS5213, QFN-32 4 × 4 mm, 0.4 mm pitch | Capstone CS5213AN | — | V3 HDMI → VGA converter; not sold by DigiKey or JLCPCB, see [below](#u4-cs5213) |
| 1 | U7 | TS5V330, TSSOP-16 | Texas Instruments TS5V330CPWR | 296-27548-1-ND | V3 R/G/B source switch |
| 1 | U8 | 74HCT157, SOIC-16 | Texas Instruments SN74HCT157DR | 296-31835-1-ND | V3 H/V sync source switch |

Board-only items, not in the BOM: H1-H4 (mounting holes), LOGO1 (Creative Commons logos), MEGA1 (3D model of the Mega).

## Not fitted (DNP)

This footprint is on the board but is left empty. It is not in the DigiKey file or in the JLCPCB files.

| Ref. | Part | Footprint | Why it is there |
|---|---|---|---|
| U5 | NX3303X (HDMI → VGA, QFN-32 5 × 5 mm) | QFN-32, 0.5 mm pitch | spare footprint for a second converter chip; **fit U4 or U5, never both** (they share the HDMI lines) |

## Off-board

| Qty | Item | Manufacturer part | DigiKey | Note |
|---:|---|---|---|---|
| 1 | Arduino Mega 2560 Rev3 | Arduino A000067 | 1050-1018-ND | plugs into J6-J12 (included in the CSV) |

V3 no longer needs an external HDMI → VGA adapter: U4 does the conversion on the board.

## U4 (CS5213)

The CS5213 is not stocked by DigiKey, Mouser or JLCPCB (JLCPCB only lists customer-consigned entries, with no stock). On
2026-10-15 it was found on AliExpress (search "CS5213", about 2 to 8 CAD each). This is a grey-market source: authenticity is not
guaranteed.

U4 is a QFN with an exposed pad and a 0.4 mm pitch: solder it with hot air or a reflow oven. Its exposed pad has 16 vias to the
ground plane; ask JLCPCB for "Epoxy Filled & Capped" vias (not "Plugged") when you order the PCB, or reduce the paste on that pad, otherwise
solder can wick through the holes.

## Cost

About **77 CAD per board** in DigiKey parts at quantity 1 (2026-10-16), without the Arduino Mega (74.74 CAD), without J3-J5 and
without U4. Ordering for several boards lowers the passive prices a lot.

## JST NH headers (J3, J4, J5)

DigiKey does not stock B10P-SHF-1AA and B12P-SHF-1AA (minimum 250 and 6 500 pieces). Mouser does not list them.
LCSC has them (C160365 and C160367), as do other JST distributors. B5P-SHF-1AA (J14) is in stock at DigiKey.
