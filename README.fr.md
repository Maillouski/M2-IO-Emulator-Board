# M2 IO Emulator Board

[English](README.md) | **Français**

Carte de remplacement direct de la **carte E/S Sega 837-10539** de la borne **Daytona USA twin** (Sega Model 2), construite autour
d'un **Arduino Mega 2560**. Elle permet à un émulateur de piloter la borne d'origine : commandes, lampes, compteurs, drive board
d'origine (retour de force) et moniteur arcade d'origine.

![Carte, vue 3D](docs/board-3d.png)

> **État : prototype.** Le design passe la DRC et l'ERC, mais aucune carte n'a encore été fabriquée ni testée. Lire les
> [points ouverts](#points-ouverts) avant de commander.

**Version : V2** (2026-10-13), qui ajoute le cavalier d'écran [JP8](#cavalier-décran-jp8). La V1, première carte, commandée chez
JLCPCB le 2026-10-13, est gardée sous l'étiquette [`v1`](https://github.com/Maillouski/M2-IO-Emulator-Board/tree/v1).

## Ce qu'elle fait

L'idée est simple : on sort la carte E/S Sega de la borne et on met celle-ci à sa place. Elle a les mêmes dimensions, les mêmes
trous de fixation et les mêmes noms de connecteurs, donc le faisceau d'origine se branche directement. Rien n'est coupé ni
recâblé.

Une fois en place, l'Arduino Mega fait le pont entre l'émulateur et la borne. Il lit les commandes et pilote tout ce que la carte
d'origine pilotait :

- **Commandes** — volant, accélérateur, frein, levier de vitesses, monnayeur, START, boutons de vue VR, TEST et SERVICE.
- **Lampes, compteurs et relais** — commandés par un ULN2803A : les ampoules et les compteurs d'origine continuent de
  fonctionner.
- **Retour de force** — la drive board d'origine reste dans la borne et reçoit ses ordres du Mega : le volant garde son retour de force
  d'origine.
- **Vidéo** — une entrée VGA va au moniteur arcade d'origine, avec la synchro composite fabriquée sur la carte. Un petit ampli
  vidéo, activable par cavaliers, remonte le signal d'une source PC ou d'un adaptateur HDMI-VGA au niveau qu'attend le tube.

Quelques détails pratiques facilitent la mise en route : boutons TEST et SERVICE directement sur la carte, DEL d'alimentation,
points de test pour chaque alimentation, et un cavalier (JP1) pour choisir si la logique de la drive board est alimentée par le
5 V du Mega ou par celui de la borne.

## Cavaliers vidéo

| VIDEO IN (J13) | JP2-JP4 (VIDEO AMP) | JP5-JP7 (VGA TERM 75 Ω) |
|---|---|---|
| PC / adaptateur HDMI-VGA | ON | ON |
| RGB arcade | OFF | OFF |

Le même tableau est imprimé sur la carte (en anglais).

## Cavalier d'écran (JP8)

Nouveau dans la V2. JP8 relie la broche D36 du Mega à la masse. Le Mega la lit avec son rappel interne et l'envoie à l'hôte avec
les autres entrées : l'hôte peut ainsi choisir son écran au démarrage. Une fois la carte dans la borne, changer d'écran ne
demande que le cavalier, pas de changement de logiciel.

| JP8 | Écran |
|---|---|
| posé (ON) | CRT (4:3) : le moniteur arcade d'origine, par un adaptateur HDMI → VGA |
| retiré (OFF) | écran LVDS (16:9) |

Imprimé sur la carte (en anglais) : SCREEN / ON = CRT (4:3) / OFF = LVDS 16:9. Ce que l'hôte fait de cette entrée dépend de son
logiciel (voir [Piloter la carte depuis un ordinateur](#piloter-la-carte-depuis-un-ordinateur)).

## Piloter la carte depuis un ordinateur

La carte est fournie avec le programme de son Arduino Mega ([`firmware/`](firmware/m2io-mega)) et une console d'essai
([`tools/m2io_console.py`](tools/m2io_console.py)). Pour faire tourner Daytona USA sur votre propre ordinateur ou votre
compilation d'un émulateur et atteindre la borne par cette carte, lisez **[Piloter la carte depuis son propre
hôte](docs/HOST-PROTOCOL.fr.md)** : liaison série, trames, contenu des octets, branchement sur la carte E/S émulée de MAME
et pièges à éviter.

## Vues 3D

Rendus KiCad 10 tirés des fichiers de ce dépôt.

| | |
|---|---|
| ![Vue en perspective](docs/board-3d-back.png) | ![Gros plan de la section vidéo](docs/board-video.png) |
| Vue en perspective | Section vidéo : entrée VGA, ampli OPA3355, cavaliers et tableau de réglage |
| ![Vue de dessus](docs/board-top.png) | ![Vue de dessous](docs/board-bottom.png) |
| Dessus | Dessous |

## Contenu du dépôt

| Chemin | Contenu |
|---|---|
| `kicad/` | projet KiCad 10 : schéma, PCB, règles de conception, librairie d'empreintes du projet (`interface-borne.pretty`), modèles 3D |
| `fabrication/` | Gerbers, fichiers de perçage Excellon et leurs plans (`gerbers/`), les mêmes fichiers en zip pour le fabricant, fichier de placement ; BOM et CPL JLCPCB pour l'assemblage des CMS ([`jlcpcb/`](fabrication/jlcpcb/README.fr.md)) |
| `firmware/` | programme de l'Arduino Mega (`m2io-mega/`) et son essai sur PC, sans Mega (`test/`) |
| `tools/` | console d'essai : joue le rôle de l'hôte depuis n'importe quel ordinateur (Python 3 + pyserial) |
| `bom/` | BOM complète ([`BOM.fr.md`](bom/BOM.fr.md), [English](bom/BOM.md)) et fichier d'import DigiKey ([`BOM-digikey.csv`](bom/BOM-digikey.csv)) |
| `docs/` | [protocole de l'hôte](docs/HOST-PROTOCOL.fr.md), schéma en PDF, rendus de la carte |

Carte : 2 couches, 180 × 190 mm. Les Gerbers sortent des réglages de tracé enregistrés dans le PCB (KiCad 10).

## Points ouverts

**CN1 et CN2** sont des embases 3M simples à quatre murs, sans leviers d'éjection.

## Modèles 3D

Le modèle de l'Arduino Mega dans `kicad/3d/` est dérivé des fichiers CAO d'Arduino (CC BY-SA 4.0) et de modèles de la
bibliothèque KiCad ; voir [`kicad/3d/README.fr.md`](kicad/3d/README.fr.md). Les connecteurs JST NH utilisent des modèles
simplifiés faits pour ce projet (embase et broches).

## Crédits

Sources utilisées pour cette carte : manuels SEGA de Daytona USA ; MAME (Dirk Best pour la carte E/S Model 1 ; R. Belmont,
O. Galibert, ElSemi, A. Salese, M. Daniels pour le Model 2) ; M2Pac de BigPanik (Gamoover) ; DaytonaUSB de SailorSat ;
BackForceFeeder de njz3 ; adaptateurs MEGA de Tibal ; le projet MiSTer (vidéo vers moniteur arcade).

Projet non affilié à SEGA ni approuvé par SEGA.

## Licence

© 2026 Nicolas Mailloux. **CC BY-NC-SA 4.0** — voir [`LICENSE`](LICENSE) (texte officiel en anglais).
Vous pouvez fabriquer, utiliser, modifier et partager cette carte, à condition de citer l'auteur, de garder les crédits et de
partager vos modifications sous la même licence. **Aucun usage commercial** : ne vendez ni la carte, ni les fichiers, ni un dérivé.
Le firmware et les outils sont sous la même licence.
