# Commander chez JLCPCB (carte + assemblage des CMS)

[English](README.md) | **Français**

JLCPCB fabrique la carte et soude les 83 composants CMS. Vous soudez vous-même les pièces traversantes.

| Fichier | Où le charger |
|---|---|
| [`../m2-io-emulator-board-gerbers.zip`](../m2-io-emulator-board-gerbers.zip) | « Add gerber file » |
| [`m2-io-emulator-board-BOM-jlcpcb.csv`](m2-io-emulator-board-BOM-jlcpcb.csv) | PCB Assembly → « Add BOM File » |
| [`m2-io-emulator-board-CPL-jlcpcb.csv`](m2-io-emulator-board-CPL-jlcpcb.csv) | PCB Assembly → « Add CPL File » |

> Lisez d'abord les [points ouverts](../../README.fr.md#points-ouverts). Le pas des JST NH, surtout, doit être confirmé avant de
> commander des cartes.

## Options de commande

- **PCB :** 2 couches, 180 × 190 mm (la taille est lue dans les Gerbers), 1,6 mm. La couleur et la finition sont au choix. Toutes
  les autres options peuvent garder leur valeur par défaut. Le design utilise des pistes de 0,25 mm avec 0,2 mm d'isolement, des
  vias de 0,8 / 0,4 mm et des trous de 0,8 mm au minimum : tout est dans les règles standard de JLCPCB.
- **PCB Assembly :** **Economic**, **dessus** seulement, 2 cartes ou plus (Economic accepte de 2 à 50 cartes). Economic ne
  demande ni bords de manutention ni repères optiques. Le CMS le plus proche est à 10 mm du bord de la carte.
- **Avant de payer,** vérifiez l'aperçu de placement :
  - **U2 (74HCT86, SOIC-14) et U3 (OPA3355, TSSOP-14) :** le point de la broche 1 de chaque pièce doit tomber sur la broche 1
    de son empreinte. Le CPL tourne ces deux pièces de −90° par rapport à KiCad, pour suivre les empreintes EasyEDA dont JLCPCB
    se sert pour placer. La correction est mesurée sur ces empreintes, mais n'a pas encore été confirmée sur une vraie commande.
  - **Résistances et condensateurs :** ils ne sont pas polarisés et n'ont besoin d'aucune correction de rotation.

## Pièces posées par JLCPCB

Numéros, types, stocks et prix vérifiés en direct sur jlcpcb.com le 2026-10-12, en dollars US la pièce.

| LCSC | Pièce | Repères | Qté / carte | Type | Stock | Prix |
|---|---|---|---:|---|---:|---:|
| C49678 | YAGEO CC0805KRX7R9BB104, 100 nF 50 V X7R | C1-C16, C18, C20-C22 | 20 | Basic | 22,6 M | 0,019 |
| C15850 | Samsung CL21A106KAYNNNE, 10 µF 25 V X5R | C19, C23 | 2 | Basic | 4,1 M | 0,069 |
| C17673 | UNI-ROYAL 0805W8F4701T5E, 4,7 kΩ 1 % | R1-R13 | 13 | Basic | 4,6 M | 0,005 |
| C17513 | UNI-ROYAL 0805W8F1001T5E, 1 kΩ 1 % | R14-R37, R46 | 25 | Basic | 45 M | 0,004 |
| C17414 | UNI-ROYAL 0805W8F1002T5E, 10 kΩ 1 % | R38-R45 | 8 | Basic | 58 M | 0,003 |
| C17710 | UNI-ROYAL 0805W8F4700T5E, 470 Ω 1 % | R47 | 1 | Basic | 2,5 M | 0,005 |
| C141697 | YAGEO RC0805FR-0775RL, 75 Ω 1 % | R48-R50 | 3 | Extended | 138 k | 0,008 |
| C228933 | YAGEO AC0805FR-07604RL, 604 Ω 1 % | R51-R53 | 3 | Extended | 4 838 | 0,007 |
| C17540 | UNI-ROYAL 0805W8F2000T5E, 200 Ω 1 % | R54-R56 | 3 | Basic | 1,2 M | 0,007 |
| C17634 | UNI-ROYAL 0805W8F330JT5E, 33 Ω 1 % | R57-R59 | 3 | Basic | 1,5 M | 0,005 |
| C6005 | Nexperia 74HCT86D,653, SOIC-14 | U2 | 1 | Extended | 936 | 0,36 |
| C2652730 | Texas Instruments OPA3355EA/2K5, TSSOP-14 | U3 | 1 | Extended | **13** | 6,01 |

- **Stock de U3 très faible :** il n'y en avait que 13. S'il s'épuise, achetez-le d'avance dans votre bibliothèque de pièces
  JLCPCB, ou attendez un réassort. U3 n'a pas de remplaçant direct.
- **Pièces Extended :** il y en a 4, et JLCPCB facture des frais de mise en place pour chaque pièce Extended. Les pièces Basic
  n'en ont pas.
- **C19 et C23 :** la BOM JLCPCB utilise un condensateur X5R 25 V, une pièce Basic, au lieu du X7R 16 V de la BOM DigiKey. Les
  deux découplent le 5 V du Mega, et le X5R est garanti jusqu'à 85 °C. Pour garder du X7R, prenez plutôt C95841 (Samsung
  CL21B106KOQNNNE, Extended, 347 k en stock).
- **U2 :** si C6005 s'épuise, C527451 le remplace directement (TI CD74HCT86M96, même boîtier SOIC-14, Extended, 9 846 en
  stock).
- **Valeurs :** toutes les autres valeurs et tous les boîtiers correspondent à [`../../bom/BOM.fr.md`](../../bom/BOM.fr.md).
  Vérifié repère par repère : 83 CMS, et la BOM, le CPL et le fichier de placement de KiCad donnent les mêmes repères aux mêmes
  positions.

## Pièces à souder vous-même

Ce sont les pièces traversantes : C17, D1, J1-J14, JP1-JP7, SK1 (puis U1 dans son support), SW1, SW2 et TP1-TP4, plus les
cavaliers SH1-SH7. Commandez-les avec la [BOM DigiKey](../../bom/BOM-digikey.csv), sans les lignes CMS.

JLCPCB peut aussi souder les pièces traversantes, contre supplément. LCSC a en stock les embases JST NH de 10 et 12 broches
(C160365 : 3 517 pièces ; C160367 : 253 pièces, au 2026-10-12).
