# Liste des pièces (BOM) — M2 IO Emulator Board

[English](BOM.md) | **Français**

Quantités **par carte**. 121 repères, vérifiés un par un contre le schéma.

**Import DigiKey :** [`BOM-digikey.csv`](BOM-digikey.csv) (Quantity, Digi-Key Part Number, Manufacturer Part Number,
Manufacturer, Customer Reference). Le charger dans le gestionnaire de BOM de DigiKey ou dans une myList, puis multiplier par le
nombre de cartes.

**Assemblage JLCPCB :** pour faire souder les CMS par JLCPCB, voir
[`../fabrication/jlcpcb/`](../fabrication/jlcpcb/README.fr.md) (numéros LCSC, fichiers BOM et CPL).

Chaque numéro DigiKey ci-dessous a été vérifié en direct sur digikey.ca le 2026-10-12, en dollars canadiens, bande coupée, à la
quantité 1, sans taxes ni livraison. Prix et stocks changent : revérifier avant de commander.

## Pièces sur la carte

| Qté | Repères | Valeur | Pièce du fabricant | DigiKey | Remarque |
|---:|---|---|---|---|---|
| 20 | C1-C16, C18, C20-C22 | 100 nF 50 V X7R 0805 | YAGEO CC0805KRX7R9BB104 | 311-1140-1-ND | |
| 2 | C19, C23 | 10 µF 16 V X7R 0805 | Samsung CL21B106KOQNNNG | 1276-6472-1-ND | |
| 1 | C17 | 100 µF 16 V, Ø 6,3 mm, pas 2,5 mm | Panasonic EEU-FC1C101 | P11198-ND | stock faible (15) ; tout 100 µF ≥ 16 V Ø 6,3 / pas 2,5 convient |
| 1 | D1 | DEL verte 3 mm | Kingbright WP710A10GD | 754-1603-ND | « CAB PWR LED » |
| 1 | J1 (CN1) | embase IDC 2 × 25 | 3M N2550-6002-RB | MHC50K-ND | voir « Points ouverts » du README |
| 1 | J2 (CN2) | embase IDC 2 × 13 | 3M N2526-6002-RB | MHC26K-ND | voir « Points ouverts » du README |
| 1 | J3 (CN3) | JST NH 10 broches, pas 2,5 mm | JST B10P-SHF-1AA | 455-B10P-SHF-1AA-ND | ⚠️ pas en stock chez DigiKey, minimum 250 |
| 2 | J4 (CN5), J5 (CN6) | JST NH 12 broches, pas 2,5 mm | JST B12P-SHF-1AA | 455-B12P-SHF-1AA-ND | ⚠️ pas en stock chez DigiKey, minimum 6 500 |
| 5 | J6-J10 | barrette 1 × 8 | Würth 61300811121 | 732-5321-ND | vers l'Arduino Mega |
| 1 | J11 | barrette 1 × 10 | Würth 61301011121 | 732-2670-ND | vers l'Arduino Mega |
| 1 | J12 | barrette 2 × 18 | Würth 61303621121 | 732-5309-ND | vers l'Arduino Mega |
| 1 | J13 | VGA (DE-15 HD) femelle, coudée | Amphenol L77HDE15SD1CH4F | L77HDE15SD1CH4F-ND | VIDEO IN |
| 1 | J14 | JST NH 5 broches, pas 2,5 mm | JST B5P-SHF-1AA | 455-B5P-SHF-1AA-ND | VIDEO OUT |
| 4 | JP1, JP2-JP4 | barrette 1 × 3 | Würth 61300311121 | 732-5316-ND | JP1 = alimentation de la drive board, JP2-JP4 = ampli vidéo |
| 3 | JP5-JP7 | barrette 1 × 2 | Würth 61300211121 | 732-5315-ND | terminaison VGA 75 Ω |
| 7 | SH1-SH7 | cavalier | TE 382811-8 | A26228-ND | vendu par 10 |
| 13 | R1-R13 | 4,7 kΩ 1 % 0805 | YAGEO RC0805FR-074K7L | 311-4.70KCRCT-ND | rappels des entrées |
| 25 | R14-R37, R46 | 1 kΩ 1 % 0805 | YAGEO RC0805FR-071KL | 311-1.00KCRCT-ND | |
| 8 | R38-R45 | 10 kΩ 1 % 0805 | YAGEO RC0805FR-0710KL | 311-10.0KCRCT-ND | |
| 1 | R47 | 470 Ω 1 % 0805 | YAGEO RC0805FR-07470RL | 311-470CRCT-ND | série de la synchro composite ; stock faible (51) |
| 3 | R48-R50 | 75 Ω 1 % 0805 | YAGEO RC0805FR-0775RL | 311-75.0CRCT-ND | terminaison VGA (par JP5-JP7) |
| 3 | R51-R53 | 604 Ω 1 % 0805 | YAGEO RC0805FR-07604RL | 311-604CRCT-ND | contre-réaction de l'ampli vidéo |
| 3 | R54-R56 | 200 Ω 1 % 0805 | YAGEO RC0805FR-07200RL | 311-200CRCT-ND | gain de l'ampli vidéo (gain = 4,02) |
| 3 | R57-R59 | 33 Ω 1 % 0805 | YAGEO RC0805FR-0733RL | 311-33.0CRCT-ND | sortie de l'ampli vidéo |
| 1 | SK1 | support DIP-18 | TE 1-2199298-5 | A120350-ND | pour U1 |
| 2 | SW1, SW2 | bouton tactile 6 × 6 mm | TE 1825910-6 | 450-1650-ND | TEST, SERVICE |
| 4 | TP1-TP4 | point de test | Keystone 5002 | 36-5002-ND | |
| 1 | U1 | ULN2803A, DIP-18 | STMicroelectronics ULN2803A | 497-2356-5-ND | lampes, compteurs, relais ; dans SK1 |
| 1 | U2 | 74HCT86, SOIC-14 | Nexperia 74HCT86D,653 | 1727-6360-1-ND | synchro composite (H XOR V, puis inversion) |
| 1 | U3 | OPA3355EA, TSSOP-14 | Texas Instruments OPA3355EA/2K5 | 296-29279-1-ND | triple ampli vidéo (R, V, B) |

Éléments de la carte hors BOM : H1-H4 (trous de fixation), LOGO1 (logos Creative Commons), MEGA1 (modèle 3D du Mega).

## Hors carte

| Qté | Article | Pièce du fabricant | DigiKey | Remarque |
|---:|---|---|---|---|
| 1 | Arduino Mega 2560 Rev3 | Arduino A000067 | 1050-1018-ND | s'enfiche sur J6-J12 (inclus dans le CSV) |
| 1 | adaptateur HDMI → VGA | au choix | — | seulement pour alimenter le moniteur arcade à partir d'une source HDMI |

## Coût

Environ **60 $ CA de pièces par carte** à la quantité 1 (2026-10-12), sans l'Arduino Mega (74,74 $) ni J3-J5. Commander pour
plusieurs cartes fait beaucoup baisser le prix des passifs.

## Embases JST NH (J3, J4, J5)

DigiKey ne stocke pas les B10P-SHF-1AA et B12P-SHF-1AA (minimum 250 et 6 500 pièces). On les trouve facilement chez LCSC
(C160365 et C160367), Mouser ou d'autres distributeurs JST. La B5P-SHF-1AA (J14) est en stock chez DigiKey.
