# Ordering from JLCPCB (board + SMD assembly)

**English** | [Français](README.fr.md)

JLCPCB makes the board and solders the 83 SMD parts. You solder the through-hole parts yourself.

| File | Upload it at |
|---|---|
| [`../m2-io-emulator-board-gerbers.zip`](../m2-io-emulator-board-gerbers.zip) | "Add gerber file" |
| [`m2-io-emulator-board-BOM-jlcpcb.csv`](m2-io-emulator-board-BOM-jlcpcb.csv) | PCB Assembly → "Add BOM File" |
| [`m2-io-emulator-board-CPL-jlcpcb.csv`](m2-io-emulator-board-CPL-jlcpcb.csv) | PCB Assembly → "Add CPL File" |

> Read the [open points](../../README.md#open-points) first. The JST NH pitch in particular has to be confirmed before you
> order bare boards.

## Order settings

- **PCB:** 2 layers, 180 × 190 mm (the size is read from the Gerbers), 1.6 mm. Colour and surface finish are your choice. Every
  other option can stay at its default value. The design uses 0.25 mm tracks with 0.2 mm clearance, 0.8 / 0.4 mm vias and
  0.8 mm minimum holes, all within JLCPCB's standard rules.
- **PCB Assembly:** **Economic**, **top side** only, quantity 2 or more (Economic accepts 2 to 50 boards). Economic needs no edge
  rails and no fiducials. The closest SMD part is 10 mm from the board edge.
- **Before paying,** check the placement preview:
  - **U2 (74HCT86, SOIC-14) and U3 (OPA3355, TSSOP-14):** the pin-1 dot of each part must sit on pin 1 of its footprint. The CPL
    rotates both parts by −90° relative to KiCad, to match the EasyEDA footprints JLCPCB places from. The correction is
    measured on those footprints, but has not yet been confirmed on a real order.
  - **Resistors and capacitors:** they are not polarised and need no rotation correction.

## Parts placed by JLCPCB

All numbers, types, stock levels and prices were checked live on jlcpcb.com on 2026-10-12, in USD per piece.

| LCSC | Part | References | Qty / board | Type | Stock | Price |
|---|---|---|---:|---|---:|---:|
| C49678 | YAGEO CC0805KRX7R9BB104, 100 nF 50 V X7R | C1-C16, C18, C20-C22 | 20 | Basic | 22.6 M | 0.019 |
| C15850 | Samsung CL21A106KAYNNNE, 10 µF 25 V X5R | C19, C23 | 2 | Basic | 4.1 M | 0.069 |
| C17673 | UNI-ROYAL 0805W8F4701T5E, 4.7 kΩ 1 % | R1-R13 | 13 | Basic | 4.6 M | 0.005 |
| C17513 | UNI-ROYAL 0805W8F1001T5E, 1 kΩ 1 % | R14-R37, R46 | 25 | Basic | 45 M | 0.004 |
| C17414 | UNI-ROYAL 0805W8F1002T5E, 10 kΩ 1 % | R38-R45 | 8 | Basic | 58 M | 0.003 |
| C17710 | UNI-ROYAL 0805W8F4700T5E, 470 Ω 1 % | R47 | 1 | Basic | 2.5 M | 0.005 |
| C141697 | YAGEO RC0805FR-0775RL, 75 Ω 1 % | R48-R50 | 3 | Extended | 138 k | 0.008 |
| C228933 | YAGEO AC0805FR-07604RL, 604 Ω 1 % | R51-R53 | 3 | Extended | 4 838 | 0.007 |
| C17540 | UNI-ROYAL 0805W8F2000T5E, 200 Ω 1 % | R54-R56 | 3 | Basic | 1.2 M | 0.007 |
| C17634 | UNI-ROYAL 0805W8F330JT5E, 33 Ω 1 % | R57-R59 | 3 | Basic | 1.5 M | 0.005 |
| C6005 | Nexperia 74HCT86D,653, SOIC-14 | U2 | 1 | Extended | 936 | 0.36 |
| C2652730 | Texas Instruments OPA3355EA/2K5, TSSOP-14 | U3 | 1 | Extended | **13** | 6.01 |

- **U3 stock is very low:** only 13 pieces were in stock. If it runs out, buy it ahead of time in your JLCPCB parts library, or
  wait for a restock. U3 has no drop-in replacement.
- **Extended parts:** there are 4 of them, and JLCPCB charges a setup fee for each extended part. Basic parts have no such fee.
- **C19 and C23:** the JLCPCB BOM uses a 25 V X5R capacitor, a Basic part, instead of the 16 V X7R in the DigiKey BOM. Both
  decouple the Mega's 5 V supply, and X5R is rated up to 85 °C. To keep X7R, use C95841 instead (Samsung CL21B106KOQNNNE,
  Extended, 347 k in stock).
- **U2:** if C6005 runs out, C527451 is a drop-in replacement (TI CD74HCT86M96, same SOIC-14 package, Extended, 9 846 in stock).
- **Values:** all the other values and packages match [`../../bom/BOM.md`](../../bom/BOM.md). This was checked reference by
  reference: 83 SMD parts, and the BOM, the CPL and the KiCad placement file list the same references at the same
  positions.

## Parts you solder yourself

These are the through-hole parts: C17, D1, J1-J14, JP1-JP7, SK1 (then U1 in its socket), SW1, SW2 and TP1-TP4, plus the
SH1-SH7 jumpers. Order them with the [DigiKey BOM](../../bom/BOM-digikey.csv), leaving out the SMD lines.

JLCPCB can also solder through-hole parts, at extra cost. LCSC stocks the 10-pin and 12-pin JST NH headers (C160365: 3 517 in
stock; C160367: 253 in stock, on 2026-10-12).
