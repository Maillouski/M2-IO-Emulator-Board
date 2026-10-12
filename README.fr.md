# M2 IO Emulator Board

[English](README.md) | **Français**

Carte de remplacement direct de la **carte E/S Sega 837-10539** de la borne **Daytona USA twin** (Sega Model 2), construite autour
d'un **Arduino Mega 2560**. Elle permet à un émulateur de piloter la borne d'origine : commandes, lampes, compteurs, drive board
d'origine (retour de force) et moniteur arcade d'origine.

![Carte, vue 3D](docs/board-3d.png)

> **État : prototype.** Le design passe la DRC et l'ERC, mais aucune carte n'a encore été fabriquée ni testée. Lire les
> [points ouverts](#points-ouverts) avant de commander.

## Ce qu'elle fait

- **Mêmes dimensions et mêmes trous que la carte Sega** (180 × 190 mm, quatre trous Ø 4 mm à 5,3 mm des bords) et mêmes noms de
  connecteurs (CN1, CN2, CN3, CN5, CN6) : le faisceau d'origine se branche tel quel, rien n'est coupé.
- **CN1 (50 broches) :** entrées monnayeur, TEST, SERVICE, START, VR1-VR4 et levier de vitesses (rappel 4,7 kΩ, filtre 1 kΩ /
  100 nF), et sorties lampes, compteurs et relais par un ULN2803A (U1, sur support).
- **CN2 (26 broches) :** potentiomètres du volant, de l'accélérateur et du frein vers les entrées analogiques du Mega (A0-A2), avec
  filtres RC.
- **CN6 / CN5 (12 broches chacun) :** octet d'ordre vers la drive board et son octet de réponse (1 kΩ en série, rappel 10 kΩ au
  5 V du Mega), pour le retour de force d'origine.
- **CN3 (10 broches) :** +5 V et masse de la borne. Le +5 V de la borne n'est jamais relié au 5 V du Mega.
- **JP1 :** alimentation logique de la drive board. 1-2 = 5 V du Mega, 2-3 = 5 V de la borne.
- Boutons **TEST** et **SERVICE** sur la carte, DEL **CAB PWR LED**, et points de test pour la masse, le +5 V du Mega, le +5 V de
  la borne et l'alimentation de la drive board.
- **Vidéo :** entrée VGA (J13) vers la fiche du moniteur arcade (J14, R/V/B + synchro composite). U2 (74HCT86) fabrique la synchro
  composite négative à partir des synchros H et V. U3 (OPA3355, gain ≈ 4) peut amplifier R/V/B pour une source VGA à 0,7 V.

## Cavaliers vidéo

| VIDEO IN (J13) | JP2-JP4 (VIDEO AMP) | JP5-JP7 (VGA TERM 75 Ω) |
|---|---|---|
| PC / adaptateur HDMI-VGA | ON | ON |
| RGB arcade | OFF | OFF |

Le même tableau est imprimé sur la carte (en anglais).

## Contenu du dépôt

| Chemin | Contenu |
|---|---|
| `kicad/` | projet KiCad 10 : schéma, PCB, règles de conception, librairie d'empreintes du projet (`interface-borne.pretty`), modèles 3D |
| `fabrication/` | Gerbers, fichiers de perçage Excellon et leurs plans (`gerbers/`), les mêmes fichiers en zip pour le fabricant, fichier de placement |
| `bom/` | BOM complète ([`BOM.fr.md`](bom/BOM.fr.md), [English](bom/BOM.md)) et fichier d'import DigiKey ([`BOM-digikey.csv`](bom/BOM-digikey.csv)) |
| `docs/` | schéma en PDF, rendus de la carte |

Carte : 2 couches, 180 × 190 mm. Les Gerbers sortent des réglages de tracé enregistrés dans le PCB (KiCad 10).

## Points ouverts

À vérifier avant de commander ou de mettre sous tension :

1. **Pas des JST NH.** CN3, CN5, CN6 et J14 utilisent des empreintes JST NH au **pas de 2,5 mm**. Le pas sur la carte Sega
   d'origine n'a pas encore été mesuré. S'il est de 2,54 mm, ces empreintes doivent changer.
2. **Ordre des broches de J14** (R, V, B, synchro, masse) : encore provisoire. À vérifier sur la fiche vidéo de votre borne.
3. **Niveau vidéo.** Le gain de l'ampli (4,02, fixé par R51-R56) suppose une source qui sort 0,7 V sur 75 Ω. Ce n'est pas mesuré.
   Changer R54-R56 pour l'ajuster.
4. **CN1 et CN2** sont des embases 3M simples à quatre murs. La carte d'origine a des embases à leviers d'éjection : la fiche entre,
   mais elle n'est pas retenue.
5. **Le firmware** du Mega ne fait pas partie de ce dépôt.

## Modèles 3D

Le modèle de l'Arduino Mega dans `kicad/3d/` est dérivé des fichiers CAO d'Arduino (CC BY-SA 4.0) et de modèles de la
bibliothèque KiCad ; voir [`kicad/3d/README.fr.md`](kicad/3d/README.fr.md). Les connecteurs JST NH n'ont pas de modèle 3D dans ce
dépôt.

## Crédits

Sources utilisées pour cette carte : manuels SEGA de Daytona USA ; MAME (Dirk Best pour la carte E/S Model 1 ; R. Belmont,
O. Galibert, ElSemi, A. Salese, M. Daniels pour le Model 2) ; M2Pac de BigPanik (Gamoover) ; DaytonaUSB de SailorSat ;
BackForceFeeder de njz3 ; adaptateurs MEGA de Tibal ; le projet MiSTer (vidéo vers moniteur arcade).

Projet non affilié à SEGA ni approuvé par SEGA.

## Licence

© 2026 Nicolas Mailloux. **CC BY-NC-SA 4.0** — voir [`LICENSE`](LICENSE) (texte officiel en anglais).
Vous pouvez fabriquer, utiliser, modifier et partager cette carte, à condition de citer l'auteur, de garder les crédits et de
partager vos modifications sous la même licence. **Aucun usage commercial** : ne vendez ni la carte, ni les fichiers, ni un dérivé.
