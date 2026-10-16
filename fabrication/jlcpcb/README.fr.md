# Commander chez JLCPCB (carte + assemblage des CMS)

[English](README.md) | **Français**

JLCPCB fabrique la carte et soude 115 composants CMS. Vous soudez vous-même U4 (le CS5213, que JLCPCB n'a pas en stock) et les
pièces traversantes.

| Fichier | Où le charger |
|---|---|
| [`../m2-io-emulator-board-gerbers.zip`](../m2-io-emulator-board-gerbers.zip) | « Add gerber file » |
| [`m2-io-emulator-board-BOM-jlcpcb.csv`](m2-io-emulator-board-BOM-jlcpcb.csv) | PCB Assembly → « Add BOM File » |
| [`m2-io-emulator-board-CPL-jlcpcb.csv`](m2-io-emulator-board-CPL-jlcpcb.csv) | PCB Assembly → « Add CPL File » |

> Lisez d'abord les [points ouverts](../../README.fr.md#points-ouverts).

## Options de commande

- **PCB :** 2 couches, 180 × 190 mm (la taille est lue dans les Gerbers), 1,6 mm. La couleur et la finition sont au choix. Le
  design utilise des pistes de 0,2 mm au minimum avec 0,2 mm d'isolement, des vias de 0,7 / 0,3 mm et 0,8 / 0,4 mm et des trous
  de composants de 0,8 mm au minimum : tout est dans les règles standard de JLCPCB.
  - **Via-in-pad :** la pastille centrale de U4 porte 16 vias. Choisissez des vias bouchés et recouverts (option via-in-pad de
    JLCPCB) pour que la brasure ne fuie pas par les trous. Sans cette option, mettez moins de pâte sur cette pastille en
    soudant U4.
- **PCB Assembly :** **dessus** seulement, 2 cartes ou plus. Economic accepte de 2 à 50 cartes et ne demande pas de repères
  optiques. La pastille CMS la plus proche du bord est à 7,85 mm (J15, la prise HDMI, posée au bord) ; toutes les autres sont à
  10 mm ou plus. JLCPCB pourrait quand même demander des bords de manutention à cause de J15.
- **Avant de payer,** vérifiez l'aperçu de placement :
  - **SOIC et TSSOP (U2, U3, U7, U8) :** le point de la broche 1 de chaque pièce doit tomber sur la broche 1 de son empreinte.
    Le CPL les tourne de −90° par rapport à KiCad, pour suivre les empreintes EasyEDA dont JLCPCB se sert pour placer.
  - **J15 (HDMI) :** le CPL déplace son centre de 2,05 mm vers ses broches (loin du bord de la carte), car l'empreinte EasyEDA de C427307 a son
    origine à cet endroit ; pastilles et orientation sont par ailleurs celles de KiCad. L'ouverture de la prise doit faire face
    au bord de la carte.
  - **Résistances, condensateurs, FB1 :** ils ne sont pas polarisés et n'ont besoin d'aucune correction de rotation.

## Pièces posées par JLCPCB

Numéros, types, stocks et prix vérifiés en direct sur jlcpcb.com le 2026-10-16, en dollars US la pièce à la plus petite quantité.

| LCSC | Pièce | Repères | Qté / carte | Type | Stock | Prix |
|---|---|---|---:|---|---:|---:|
| C49678 | YAGEO CC0805KRX7R9BB104, 100 nF 50 V X7R | C1-C16, C18, C20-C22, C27-C29, C31, C33, C35, C36, C38, C43, C44, C46 | 31 | Basic | 21 M | 0,020 |
| C15850 | Samsung CL21A106KAYNNNE, 10 µF 25 V X5R | C19, C23, C25, C26, C30, C32, C34, C37, C41, C42, C45 | 11 | Basic | 6,6 M | 0,044 |
| C1710 | Samsung CL21B103KBANNNC, 10 nF 50 V X7R | C39, C40 | 2 | Basic | 1,6 M | 0,012 |
| C1017 | Sunlord GZ2012D601TF, 600 Ω à 100 MHz | FB1 | 1 | Basic | 679 k | 0,020 |
| C427307 | Amphenol 10029449-111RLF, HDMI type A | J15 | 1 | Extended | 1 514 | 0,62 |
| C17673 | UNI-ROYAL 0805W8F4701T5E, 4,7 kΩ 1 % | R1-R13 | 13 | Basic | 4,2 M | 0,005 |
| C17513 | UNI-ROYAL 0805W8F1001T5E, 1 kΩ 1 % | R14-R37, R46, R60 | 26 | Basic | 44 M | 0,004 |
| C17414 | UNI-ROYAL 0805W8F1002T5E, 10 kΩ 1 % | R38-R45, R61-R65 | 13 | Basic | 57 M | 0,003 |
| C17710 | UNI-ROYAL 0805W8F4700T5E, 470 Ω 1 % | R47 | 1 | Basic | 2,3 M | 0,005 |
| C141697 | YAGEO RC0805FR-0775RL, 75 Ω 1 % | R48-R50 | 3 | Extended | 123 k | 0,008 |
| C228933 | YAGEO AC0805FR-07604RL, 604 Ω 1 % | R51-R53 | 3 | Extended | 4 446 | 0,007 |
| C17540 | UNI-ROYAL 0805W8F2000T5E, 200 Ω 1 % | R54-R56 | 3 | Basic | 1,2 M | 0,007 |
| C17634 | UNI-ROYAL 0805W8F330JT5E, 33 Ω 1 % | R57-R59 | 3 | Basic | 1,4 M | 0,005 |
| C6005 | Nexperia 74HCT86D,653, SOIC-14 | U2 | 1 | Extended | 911 | 0,36 |
| C2652730 | Texas Instruments OPA3355EA/2K5, TSSOP-14 | U3 | 1 | Extended | **11** | 6,02 |
| C2652470 | Texas Instruments TS5V330CPWR, TSSOP-16 | U7 | 1 | Extended | 6 599 | 0,42 |
| C6771 | Texas Instruments SN74HCT157DR, SOIC-16 | U8 | 1 | Extended | 155 | 0,41 |

- **Stock de U3 très faible :** il n'y en avait que 11. S'il s'épuise, achetez-le d'avance dans votre bibliothèque de pièces
  JLCPCB, ou attendez un réassort. U3 n'a pas de remplaçant direct.
- **Pièces Extended :** il y en a 7, et JLCPCB facture des frais de mise en place pour chaque pièce Extended. Les pièces Basic
  n'en ont pas.
- **Condensateurs de 10 µF :** la BOM JLCPCB utilise un X5R 25 V, une pièce Basic, au lieu du X7R 16 V de la BOM DigiKey ; le
  X5R est garanti jusqu'à 85 °C. Pour garder du X7R, prenez plutôt C95841 (Samsung CL21B106KOQNNNE, Extended, 268 k en stock).
- **U2 :** si C6005 s'épuise, C527451 le remplace directement (TI CD74HCT86M96, même boîtier SOIC-14, Extended, 10 826 en
  stock).
- **Non posés par JLCPCB :** U4 (CS5213, voir [`../../bom/BOM.fr.md`](../../bom/BOM.fr.md#u4-cs5213)) et les pièces DNP U5, U6
  et C24.
- **Valeurs :** toutes les autres valeurs et tous les boîtiers correspondent à [`../../bom/BOM.fr.md`](../../bom/BOM.fr.md)
  (FB1 : la BOM DigiKey prend un équivalent Murata). Vérifié repère par repère : 115 CMS, et la BOM, le CPL et le fichier de
  placement de KiCad donnent les mêmes repères ; positions identiques sauf J15 (voir plus haut).

## Pièces à souder vous-même

- **U4** (CS5213, QFN-32 au pas de 0,4 mm) : air chaud ou four de refusion.
- **Pièces traversantes :** C17, D1, J1-J14, J16, JP1-JP10, U1, SW1, SW2 et TP1-TP4, plus les cavaliers SH1-SH10. Commandez-les
  avec la [BOM DigiKey](../../bom/BOM-digikey.csv), sans les lignes CMS.

JLCPCB peut aussi souder les pièces traversantes, contre supplément. LCSC a en stock les embases JST NH de 10 et 12 broches
(C160365 : 3 292 pièces ; C160367 : 133 pièces, au 2026-10-16).
