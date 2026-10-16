# Ordering from JLCPCB (board + SMD assembly)

**English** | [Français](README.fr.md)

JLCPCB makes the board and solders 115 SMD parts. You solder U4 (the CS5213, which JLCPCB does not stock) and the through-hole
parts yourself.

| File | Upload it at |
|---|---|
| [`../m2-io-emulator-board-gerbers.zip`](../m2-io-emulator-board-gerbers.zip) | "Add gerber file" |
| [`m2-io-emulator-board-BOM-jlcpcb.csv`](m2-io-emulator-board-BOM-jlcpcb.csv) | PCB Assembly → "Add BOM File" |
| [`m2-io-emulator-board-CPL-jlcpcb.csv`](m2-io-emulator-board-CPL-jlcpcb.csv) | PCB Assembly → "Add CPL File" |

> Read the [open points](../../README.md#open-points) first.

## Order settings

- **PCB:** 2 layers, 180 × 190 mm (the size is read from the Gerbers), 1.6 mm. Colour and surface finish are your choice. The
  design uses 0.2 mm minimum tracks with 0.2 mm clearance, 0.7 / 0.3 mm and 0.8 / 0.4 mm vias and 0.8 mm minimum component
  holes, all within JLCPCB's standard rules.
  - **Via-in-pad:** the exposed pad of U4 has 16 vias. Choose plugged and capped vias (JLCPCB's via-in-pad option) so solder
    does not wick through them. Without that option, put less paste on that pad when you solder U4.
- **PCB Assembly:** **top side** only, quantity 2 or more. Economic accepts 2 to 50 boards and needs no fiducials. The closest
  SMD pad is 7.85 mm from the board edge (J15, the HDMI jack, which sits on the edge); every other SMD pad is at least 10 mm away.
  JLCPCB may still ask for edge rails because of J15.
- **Before paying,** check the placement preview:
  - **SOIC and TSSOP parts (U2, U3, U7, U8):** the pin-1 dot of each part must sit on pin 1 of its footprint. The CPL rotates
    them by −90° relative to KiCad, to match the EasyEDA footprints JLCPCB places from.
  - **J15 (HDMI):** the CPL moves its centre by 2.05 mm toward its pins (away from the board edge), because the EasyEDA footprint of C427307 has its
    origin there; pads and orientation are otherwise the same as in KiCad. The jack opening must face the board edge.
  - **Resistors, capacitors, FB1:** they are not polarised and need no rotation correction.

## Parts placed by JLCPCB

All numbers, types, stock levels and prices were checked live on jlcpcb.com on 2026-10-16, in USD per piece at the lowest
quantity.

| LCSC | Part | References | Qty / board | Type | Stock | Price |
|---|---|---|---:|---|---:|---:|
| C49678 | YAGEO CC0805KRX7R9BB104, 100 nF 50 V X7R | C1-C16, C18, C20-C22, C27-C29, C31, C33, C35, C36, C38, C43, C44, C46 | 31 | Basic | 21 M | 0.020 |
| C15850 | Samsung CL21A106KAYNNNE, 10 µF 25 V X5R | C19, C23, C25, C26, C30, C32, C34, C37, C41, C42, C45 | 11 | Basic | 6.6 M | 0.044 |
| C1710 | Samsung CL21B103KBANNNC, 10 nF 50 V X7R | C39, C40 | 2 | Basic | 1.6 M | 0.012 |
| C1017 | Sunlord GZ2012D601TF, 600 Ω at 100 MHz | FB1 | 1 | Basic | 679 k | 0.020 |
| C427307 | Amphenol 10029449-111RLF, HDMI type A | J15 | 1 | Extended | 1 514 | 0.62 |
| C17673 | UNI-ROYAL 0805W8F4701T5E, 4.7 kΩ 1 % | R1-R13 | 13 | Basic | 4.2 M | 0.005 |
| C17513 | UNI-ROYAL 0805W8F1001T5E, 1 kΩ 1 % | R14-R37, R46, R60 | 26 | Basic | 44 M | 0.004 |
| C17414 | UNI-ROYAL 0805W8F1002T5E, 10 kΩ 1 % | R38-R45, R61-R65 | 13 | Basic | 57 M | 0.003 |
| C17710 | UNI-ROYAL 0805W8F4700T5E, 470 Ω 1 % | R47 | 1 | Basic | 2.3 M | 0.005 |
| C141697 | YAGEO RC0805FR-0775RL, 75 Ω 1 % | R48-R50 | 3 | Extended | 123 k | 0.008 |
| C228933 | YAGEO AC0805FR-07604RL, 604 Ω 1 % | R51-R53 | 3 | Extended | 4 446 | 0.007 |
| C17540 | UNI-ROYAL 0805W8F2000T5E, 200 Ω 1 % | R54-R56 | 3 | Basic | 1.2 M | 0.007 |
| C17634 | UNI-ROYAL 0805W8F330JT5E, 33 Ω 1 % | R57-R59 | 3 | Basic | 1.4 M | 0.005 |
| C6005 | Nexperia 74HCT86D,653, SOIC-14 | U2 | 1 | Extended | 911 | 0.36 |
| C2652730 | Texas Instruments OPA3355EA/2K5, TSSOP-14 | U3 | 1 | Extended | **11** | 6.02 |
| C2652470 | Texas Instruments TS5V330CPWR, TSSOP-16 | U7 | 1 | Extended | 6 599 | 0.42 |
| C6771 | Texas Instruments SN74HCT157DR, SOIC-16 | U8 | 1 | Extended | 155 | 0.41 |

- **U3 stock is very low:** only 11 pieces were in stock. If it runs out, buy it ahead of time in your JLCPCB parts library, or
  wait for a restock. U3 has no drop-in replacement.
- **Extended parts:** there are 7 of them, and JLCPCB charges a setup fee for each extended part. Basic parts have no such fee.
- **10 µF capacitors:** the JLCPCB BOM uses a 25 V X5R capacitor, a Basic part, instead of the 16 V X7R in the DigiKey BOM; X5R
  is rated up to 85 °C. To keep X7R, use C95841 instead (Samsung CL21B106KOQNNNE, Extended, 268 k in stock).
- **U2:** if C6005 runs out, C527451 is a drop-in replacement (TI CD74HCT86M96, same SOIC-14 package, Extended, 10 826 in stock).
- **Not placed:** U4 (CS5213, see [`../../bom/BOM.md`](../../bom/BOM.md#u4-cs5213)), and the DNP parts U5, U6 and C24.
- **Values:** all the other values and packages match [`../../bom/BOM.md`](../../bom/BOM.md) (FB1: the DigiKey BOM uses a Murata
  equivalent). This was checked reference by reference: 115 SMD parts, and the BOM, the CPL and the KiCad placement file list
  the same references; positions are the same except J15 (see above).

## Parts you solder yourself

- **U4** (CS5213, QFN-32 0.4 mm pitch): hot air or reflow.
- **Through-hole parts:** C17, D1, J1-J14, J16, JP1-JP10, U1, SW1, SW2 and TP1-TP4, plus the SH1-SH10 jumpers. Order them with
  the [DigiKey BOM](../../bom/BOM-digikey.csv), leaving out the SMD lines.

JLCPCB can also solder through-hole parts, at extra cost. LCSC stocks the 10-pin and 12-pin JST NH headers (C160365: 3 292 in
stock; C160367: 133 in stock, on 2026-10-16).
