# Liste des pièces (BOM) — M2 IO Emulator Board

[English](BOM.md) | **Français**

Quantités **par carte**. 167 repères, vérifiés un par un contre le schéma (V3, 2026-10-16) : 165 dans le fichier DigiKey, U4
d'une autre source, et 1 non posé (DNP).

**Import DigiKey :** [`BOM-digikey.csv`](BOM-digikey.csv) (Quantity, Digi-Key Part Number, Manufacturer Part Number,
Manufacturer, Customer Reference). Le charger dans le gestionnaire de BOM de DigiKey ou dans une myList, puis multiplier par le
nombre de cartes.

**Assemblage JLCPCB :** pour faire souder les CMS par JLCPCB, voir
[`../fabrication/jlcpcb/`](../fabrication/jlcpcb/README.fr.md) (numéros LCSC, fichiers BOM et CPL).

Chaque numéro DigiKey ci-dessous a été vérifié en direct sur digikey.ca le 2026-10-16, en dollars canadiens, bande coupée, à la
quantité 1, sans taxes ni livraison. Prix et stocks changent : revérifier avant de commander.

## Pièces sur la carte

| Qté | Repères | Valeur | Pièce du fabricant | DigiKey | Remarque |
|---:|---|---|---|---|---|
| 32 | C1-C16, C18, C20-C22, C24, C27-C29, C31, C33, C35, C36, C38, C43, C44, C46 | 100 nF 50 V X7R 0805 | YAGEO CC0805KRX7R9BB104 | 311-1140-1-ND | |
| 11 | C19, C23, C25, C26, C30, C32, C34, C37, C41, C42, C45 | 10 µF 25 V X5R 0805 | Samsung CL21A106KAYNNNE | 1276-2891-1-ND | même pièce que l'assemblage JLCPCB (C15850) ; tout 10 µF ≥ 16 V X5R/X7R 0805 convient |
| 2 | C39, C40 | 10 nF 50 V X7R 0805 | YAGEO CC0805KRX7R9BB103 | 311-1136-1-ND | filtre audio (V3) |
| 2 | C47, C48 | 22 µF 16 V X5R 0805 | Samsung CL21A226MOCLRNC | 1276-6780-1-ND | moyenne des synchros (synchro composite) ; tout 22 µF ≥ 10 V X5R/X7R 0805 convient |
| 1 | C17 | 100 µF 16 V, Ø 6,3 mm, pas 2,5 mm | Panasonic EEU-FC1C101H | P19632CT-ND | même série FC que l'EEU-FC1C101, en bande ; tout 100 µF ≥ 16 V Ø 6,3 / pas 2,5 convient |
| 1 | D1 | DEL verte 3 mm | Kingbright WP710A10GD | 754-1603-ND | « CAB PWR LED » |
| 1 | FB1 | ferrite 600 Ω, 0805 | Murata BLM21PG601SN1D | 490-BLM21PG601SN1DCT-ND | V3 ; le schéma indique Sunlord GZ2012D601TF (600 Ω à 100 MHz, la pièce JLCPCB), absente chez DigiKey |
| 1 | J1 (CN1) | embase IDC 2 × 25 | 3M N2550-6002-RB | MHC50K-ND | voir « Points ouverts » |
| 1 | J2 (CN2) | embase IDC 2 × 13 | 3M N2526-6002-RB | MHC26K-ND | voir « Points ouverts » |
| 1 | J3 (CN3) | JST NH 10 broches, pas 2,5 mm | JST B10P-SHF-1AA | 455-B10P-SHF-1AA-ND | ⚠️ ni chez DigiKey (minimum 250) ni chez Mouser : acheter chez LCSC (C160365), voir [plus bas](#embases-jst-nh-j3-j4-j5) |
| 2 | J4 (CN5), J5 (CN6) | JST NH 12 broches, pas 2,5 mm | JST B12P-SHF-1AA | 455-B12P-SHF-1AA-ND | ⚠️ ni chez DigiKey (minimum 6 500) ni chez Mouser : acheter chez LCSC (C160367), voir [plus bas](#embases-jst-nh-j3-j4-j5) |
| 5 | J6-J10 | barrette 1 × 8 | Würth 61300811121 | 732-5321-ND | vers l'Arduino Mega |
| 1 | J11 | barrette 1 × 10 | Würth 61301011121 | 732-2670-ND | vers l'Arduino Mega |
| 1 | J12 | barrette 2 × 18 | Würth 61303621121 | 732-5309-ND | vers l'Arduino Mega |
| 1 | J13 | VGA (DE-15 HD) femelle, coudée | Amphenol L77HDE15SD1CH4F | L77HDE15SD1CH4F-ND | entrée VGA 24 kHz |
| 1 | J14 | JST NH 5 broches, pas 2,5 mm | JST B5P-SHF-1AA | 455-B5P-SHF-1AA-ND | VIDEO OUT |
| 1 | J15 | prise HDMI type A, coudée | Amphenol 10029449-001RLF | 609-1010-1-ND | entrée HDMI (V3) ; l'assemblage JLCPCB utilise la 10029449-111RLF (C427307), épuisée chez DigiKey ; la -001RLF est celle pour laquelle l'empreinte KiCad est dessinée |
| 1 | J16 | double prise RCA superposée (rouge / blanche), coudée | Same Sky RCJ-2223 | CP-1435-ND | sortie stéréo (V3) : rouge = droite, blanche = gauche |
| 5 | JP1, JP2-JP4, JP10 | barrette 1 × 3 | Würth 61300311121 | 732-5316-ND | JP1 = alim. drive board, JP2-JP4 = ampli vidéo, JP10 = 5 V de la puce HDMI |
| 5 | JP5-JP9 | barrette 1 × 2 | Würth 61300211121 | 732-5315-ND | JP5-JP7 = terminaison VGA 75 Ω, JP8 = choix d'écran, JP9 = source vidéo |
| 10 | SH1-SH10 | cavalier | TE 382811-8 | A26228-ND | vendu par 10 |
| 13 | R1-R13 | 4,7 kΩ 1 % 0805 | YAGEO RC0805FR-074K7L | 311-4.70KCRCT-ND | rappels des entrées |
| 26 | R14-R37, R46, R60 | 1 kΩ 1 % 0805 | YAGEO RC0805FR-071KL | 311-1.00KCRCT-ND | R60 = rappel du hot-plug HDMI |
| 13 | R38-R45, R61-R65 | 10 kΩ 1 % 0805 | YAGEO RC0805FR-0710KL | 311-10.0KCRCT-ND | R61 = rappel du choix de source, R62-R65 = tirages à la masse des entrées de synchro |
| 1 | R47 | 470 Ω 1 % 0805 | Stackpole RMCF0805FT470R | RMCF0805FT470RCT-ND | résistance série de la synchro composite |
| 3 | R48-R50 | 75 Ω 1 % 0805 | YAGEO RC0805FR-0775RL | 311-75.0CRCT-ND | terminaison VGA (par JP5-JP7) |
| 3 | R51-R53 | 604 Ω 1 % 0805 | YAGEO RC0805FR-07604RL | 311-604CRCT-ND | contre-réaction de l'ampli vidéo |
| 3 | R54-R56 | 200 Ω 1 % 0805 | YAGEO RC0805FR-07200RL | 311-200CRCT-ND | gain de l'ampli vidéo (gain = 4,02) |
| 3 | R57-R59 | 33 Ω 1 % 0805 | YAGEO RC0805FR-0733RL | 311-33.0CRCT-ND | sortie de l'ampli vidéo |
| 2 | R66, R67 | 2,2 kΩ 1 % 0805 | YAGEO RC0805FR-072K2L | 311-2.20KCRCT-ND | moyenne des synchros (avec C47, C48) |
| 2 | SW1, SW2 | bouton tactile 6 × 6 mm | TE 1825910-6 | 450-1650-ND | TEST, SERVICE |
| 4 | TP1-TP4 | point de test | Keystone 5002 | 36-5002-ND | |
| 1 | U1 | ULN2803A, DIP-18 | STMicroelectronics ULN2803A | 497-2356-5-ND | lampes, compteurs, relais ; soudé directement, sans support |
| 1 | U2 | 74HCT86, SOIC-14 | Nexperia 74HCT86D,653 | 1727-6360-1-ND | synchro composite, négative quelle que soit la polarité de H et V (voir le [README](../README.fr.md#synchro-composite)) |
| 1 | U3 | OPA3355EA, TSSOP-14 | Texas Instruments OPA3355EA/2K5 | 296-29279-1-ND | triple ampli vidéo (R, V, B) |
| 1 | U6 | AT24C02, SOIC-8 | Microchip AT24C02C-SSHM-T | AT24C02C-SSHM-TCT-ND | EEPROM d'EDID sur les lignes DDC du HDMI (adresse 0x50, protection en écriture à la masse), alimentée par le +5 V du HDMI ; arrive vierge |
| 1 | U4 | CS5213, QFN-32 4 × 4 mm, pas 0,4 mm | Capstone CS5213AN | — | convertisseur HDMI → VGA (V3) ; ni chez DigiKey ni chez JLCPCB, voir [plus bas](#u4-cs5213) |
| 1 | U7 | TS5V330, TSSOP-16 | Texas Instruments TS5V330CPWR | 296-27548-1-ND | choix de source R/V/B (V3) |
| 1 | U8 | 74HCT157, SOIC-16 | Texas Instruments SN74HCT157DR | 296-31835-1-ND | choix de source des synchros H/V (V3) |

Éléments propres à la carte, hors BOM : H1-H4 (trous de fixation), LOGO1 (logos Creative Commons), MEGA1 (modèle 3D du Mega).

## Non posés (DNP)

Cette empreinte est sur la carte mais reste vide. Elle n'est ni dans le fichier DigiKey ni dans les fichiers
JLCPCB.

| Repère | Pièce | Empreinte | Rôle |
|---|---|---|---|
| U5 | NX3303X (HDMI → VGA, QFN-32 5 × 5 mm) | QFN-32, pas 0,5 mm | empreinte de secours pour une deuxième puce de conversion ; **poser U4 ou U5, jamais les deux** (elles partagent les lignes HDMI) |

## Hors carte

| Qté | Article | Pièce du fabricant | DigiKey | Remarque |
|---:|---|---|---|---|
| 1 | Arduino Mega 2560 Rev3 | Arduino A000067 | 1050-1018-ND | s'enfiche sur J6-J12 (inclus dans le CSV) |

La V3 n'a plus besoin d'adaptateur HDMI → VGA externe : U4 fait la conversion sur la carte.

## U4 (CS5213)

Le CS5213 n'est stocké ni par DigiKey, ni par Mouser, ni par JLCPCB (JLCPCB n'a que des fiches de pièces fournies par des
clients, sans stock). Le 2026-10-15, il se trouvait sur AliExpress (recherche « CS5213 », environ 2 à 8 $ CA pièce). C'est une
source du marché gris : l'authenticité n'est pas garantie.

U4 est un QFN à pastille centrale, au pas de 0,4 mm : le souder à l'air chaud ou au four de refusion. Sa pastille centrale a
16 vias vers le plan de masse ; demander à JLCPCB des vias « Epoxy Filled & Capped » (pas « Plugged ») à la commande du PCB, ou réduire la pâte sur
cette pastille, sinon la brasure peut fuir par les trous.

## Coût

Environ **77 $ CA par carte** en pièces DigiKey à la quantité 1 (2026-10-16), sans l'Arduino Mega (74,74 $ CA), sans J3-J5 et
sans U4. Commander pour plusieurs cartes fait beaucoup baisser le prix des passifs.

## Embases JST NH (J3, J4, J5)

DigiKey ne stocke pas les B10P-SHF-1AA et B12P-SHF-1AA (minimum 250 et 6 500 pièces). Mouser ne les a pas.
LCSC les a (C160365 et C160367), comme d'autres distributeurs JST. Le B5P-SHF-1AA (J14) est en stock chez DigiKey.
