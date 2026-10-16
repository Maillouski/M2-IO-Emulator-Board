# Piloter la carte depuis son propre hôte

[English](HOST-PROTOCOL.md) | **Français**

Cette page s'adresse à qui veut faire tourner Daytona USA sur son propre ordinateur (PC, ordinateur monocarte, sa propre
compilation d'un émulateur) et passer par cette carte pour atteindre la borne. Elle décrit tout ce qui circule sur le câble
USB entre l'hôte et l'Arduino Mega, et ce que l'hôte doit en faire.

## 1. Principe

Le Mega n'a aucune logique de jeu. C'est un pont qui transporte les **octets bruts des ports de la carte E/S d'origine
837-10539** :

- **Mega → hôte, toutes les 1 ms :** les contacts, le levier de vitesses, les trois potentiomètres et la réponse de la drive
  board, tels que la carte E/S d'origine les verrait sur ses broches.
- **Hôte → Mega :** deux octets, l'ordre de la drive board et les lampes et compteurs, que le Mega recopie tels quels sur ses
  ports de sortie.

L'hôte doit donc **émuler lui-même la carte E/S**, puis brancher les ports de cette carte émulée sur le Mega au lieu d'un
clavier ou d'une manette. MAME émule déjà cette carte (`model1io`, qui exécute la vraie ROM Sega de la carte E/S). Le jeu
voit donc exactement ce qu'il voyait dans la borne d'origine : c'est la ROM qui décide quand une lampe s'allume, quand un
compteur avance et ce qui part vers la drive board.

```
contacts, potentiomètres, drive board  ──>  Mega  ──USB──>  hôte : carte E/S émulée  ──>  jeu
lampes, compteurs, drive board         <──  Mega  <──USB──  hôte : carte E/S émulée  <──  jeu
```

## 2. Premiers pas

1. Programmer le Mega avec [`firmware/m2io-mega`](../firmware/m2io-mega) (IDE Arduino, ou `arduino-cli`) :

   ```bash
   arduino-cli compile --fqbn arduino:avr:mega firmware/m2io-mega
   arduino-cli upload --fqbn arduino:avr:mega -p /dev/ttyACM0 firmware/m2io-mega
   ```

2. Vérifier la carte sans émulateur avec [`tools/m2io_console.py`](../tools/m2io_console.py) (Python 3 + pyserial). La console
   affiche toutes les entrées en direct et peut allumer des lampes ou envoyer un ordre à la drive board :

   ```bash
   python3 tools/m2io_console.py /dev/ttyACM0
   ```

   Appuyer sur chaque bouton de la borne et bouger le levier, le volant et les pédales : chacun doit apparaître. Essayer
   ensuite `--chase` (lampes tour à tour, compteurs laissés de côté).

3. Facultatif : [`firmware/test/host_test.cpp`](../firmware/test/host_test.cpp) fait tourner le programme du Mega sur un PC,
   sans Mega (`c++ -std=c++17 -o host_test firmware/test/host_test.cpp && ./host_test`).

[`firmware/m2io-mega/m2io_proto.h`](../firmware/m2io-mega/m2io_proto.h) est du C++ pur, sans dépendance à Arduino : un hôte
écrit en C++ peut l'inclure tel quel pour fabriquer et décoder les trames.

## 3. Liaison série

| | |
|---|---|
| Port | le port USB du Mega : `/dev/ttyACM0` sous Linux (Mega d'origine), `/dev/ttyUSB0` (clones à CH340), `/dev/cu.usbmodem…` sous macOS, `COMx` sous Windows |
| Réglages | **250 000 bauds**, 8N1, sans contrôle de flux |

**Ouvrir le port redémarre le Mega** (DTR), comme tout Arduino :

- Dans les ~5 premières ms arrivent 10 à 25 **vieilles trames**, restes de la session précédente. Jeter tout ce qui arrive
  pendant les **300 premières ms**.
- Le chargeur démarre ensuite. La première vraie trame arrive environ **0,9 s** après l'ouverture, compteur reparti de 0.
- **Ne rien envoyer avant cette première vraie trame.** Le chargeur prend tout octet reçu pour le début d'un téléversement
  et ne lance plus le programme.

## 4. Trames

| Sens | Longueur | Octets |
|---|---|---|
| Mega → hôte, toutes les 1 ms | 9 | `A5`, compteur, IN0, IN1, réponse de la drive board, volant, accélérateur, frein, somme |
| Hôte → Mega | 4 | `5A`, ordre de la drive board, lampes, somme |

- **Somme :** choisie pour que la somme de **tous** les octets de la trame, en-tête compris, vaille 0 modulo 256
  (`somme = (0x100 - somme des octets précédents) & 0xFF`).
- **Compteur :** augmente de 1 à chaque trame et repart à 0 après 255. Un trou signale une trame perdue.
- **Réception :** utiliser une fenêtre glissante. Y pousser chaque octet reçu ; dès qu'elle contient 9 octets, commence par
  `A5` et a une somme nulle, c'est une trame. Après un octet perdu ou abîmé, la réception se recale toute seule
  (`m2io::Receiver` dans `m2io_proto.h`).
- **Envoi :** envoyer une trame d'ordres à chaque changement de l'octet de drive board ou de lampes, et **au moins toutes les
  16 ms** même si rien ne change.
- **Chien de garde :** si le Mega ne reçoit aucune trame valide pendant **200 ms**, il envoie `00` à la drive board, éteint
  toutes les lampes et coupe les compteurs. C'est aussi l'état de ses sorties à la mise sous tension.

## 5. Contenu des octets

Un bit « actif à 0 » vaut 0 quand le contact est appuyé.

| Octet | Bits |
|---|---|
| **IN0** | 0 pièce 1 · 1 pièce 2 · 2 TEST · 3 SERVICE · 4 START · 5 VR1 · 6 VR2 · 7 VR3 (tous actifs à 0) |
| **IN1** | 0 VR4 (actif à 0) · 1 cavalier d'écran JP8, voir plus bas · 2-3 non câblés, lus à 1 · 4-6 contacts du levier · 7 4e contact du levier |
| **Réponse de la drive board** | les 8 lignes qui reviennent de la drive board (port E de la carte E/S, en lecture) |
| **Volant, accélérateur, frein** | les potentiomètres, de 0 à 255 (convertisseur 10 bits divisé par 4, comme le MSM6253 8 bits de la carte E/S) |
| **Ordre de la drive board** | les 8 lignes vers la drive board (port E de la carte E/S, en écriture). `00` = moteur coupé |
| **Lampes** | 0 compteur de pièces 1 · 1 compteur de pièces 2 · 2 START · 3 VR1 · 4 VR2 · 5 VR3 · 6 VR4 · 7 leader (1 = allumé) |

- **Les bits 0-1 des lampes commandent les compteurs de pièces d'origine :** chaque impulsion ajoute une pièce à un compteur
  mécanique. Ne pas s'en servir pour des essais.
- **JP8** (cartes V2 et V3) relie D36 du Mega à la masse. Le bit 1 de IN1 vaut **0 quand le cavalier est posé** et 1 quand il est
  retiré. Ce n'est pas une entrée du jeu : il sert à l'hôte pour choisir son écran au démarrage (posé = tube 4:3 par l'entrée HDMI
  de la carte ou un adaptateur HDMI → VGA, retiré = dalle LVDS 16:9). L'usage qu'en fait l'hôte lui appartient. Avant de transmettre IN1 à la
  carte E/S, forcer le bit 1 à 1 : Daytona n'utilise pas les bits 1-3 (MAME les marque inutilisés), qui valent 1 sur la carte
  d'origine.
- **Le levier passe tel quel.** Les contacts de la borne produisent eux-mêmes le code de vitesse attendu par le jeu : ne pas
  le convertir. `daytona_gearbox_r` de MAME ne sert qu'à fabriquer ce code à partir de touches.

## 6. Brancher sur une carte E/S émulée

Chaque octet correspond à un port du circuit 315-5338A de la carte E/S ou à son convertisseur MSM6253. Dans MAME, le
périphérique `model1io` a déjà un branchement (callback) pour chacun (`src/mame/sega/model1io.h`) :

| Octet | Port de la carte E/S | Callback de `model1io` (MAME) | Branchement actuel de MAME pour Daytona |
|---|---|---|---|
| IN0 | 315-5338A port B (lecture) | `in_callback<0>` | ioport `IN0` |
| IN1 | 315-5338A port C (lecture) | `in_callback<1>` | ioport `IN1` (vitesses fabriquées à partir de touches) |
| Volant, accélérateur, frein | MSM6253 voies 0-2 | `an_callback<0>` à `<2>` | ioports `STEER`, `ACCEL`, `BRAKE` |
| Réponse de la drive board | 315-5338A port E (lecture) | `drive_read_callback` | non branché : lit `0xFF` |
| Ordre de la drive board | 315-5338A port E (écriture) | `drive_write_callback` | `drive_board_w`, vers le processeur de drive board émulé |
| Lampes | 315-5338A port F (écriture) | `output_callback` | `lamp_output_w` (compteurs de pièces, sorties des lampes) |

La dernière colonne décrit MAME master d'octobre 2026 (commit `74b9fae`), dans `model2o_state::daytona()` et `model2o()` de
`src/mame/sega/model2.cpp`.

**Le retour de force demande un émulateur modifié.** Dans MAME tel quel, l'ordre de drive board va à un processeur de drive
board émulé, mais la sortie moteur de ce processeur n'est reliée à rien (`driveio_port_w` est marquée TODO). Rien ne sort
donc de MAME qui puisse piloter le vrai moteur. Avec cette carte, c'est la **vraie** drive board de la borne qui travaille :
`drive_write_callback` doit envoyer l'ordre au Mega, et `drive_read_callback` doit rendre la réponse du Mega. La drive board
émulée ne sert alors plus.

**Lampes et entrées** passent par les mêmes branchements. Rebrancher les cinq autres callbacks pour qu'ils lisent et écrivent
les dernières valeurs échangées avec le Mega.

## 7. Ce que l'hôte doit faire

1. Ouvrir le port à 250 000 bauds. Tout jeter pendant 300 ms, puis attendre la première trame valide avant d'envoyer quoi que
   ce soit.
2. Lire les trames dans un fil (thread) à part, à 1 kHz. Garder les derniers IN0, IN1, potentiomètres et réponse de la drive
   board là où le fil d'émulation peut les lire.
3. **Filtrer les rebonds de IN0 et du bit 0 de IN1** (pièce, START, VR, TEST, SERVICE). Un appui compte tout de suite ; un
   relâchement ne compte qu'une fois le bit resté à 1 pendant environ **25 trames de suite** (25 ms).
   - Les contacts rebondissent jusqu'à environ 60 ms. Sans ce filtre, une pièce peut compter deux fois.
   - Le filtre allonge aussi chaque appui au-delà d'une trame du jeu (environ 17 ms) : une impulsion de pièce courte ne peut
     pas tomber entre deux lectures.
4. Alimenter la carte E/S émulée avec ces valeurs (§ 6), bit 1 de IN1 forcé à 1.
5. À chaque écriture de la carte émulée sur le port E ou le port F, envoyer `5A, ordre, lampes, somme`. Renvoyer aussi au
   moins toutes les 16 ms.
6. **Ne plus rien envoyer quand l'émulation est en pause ou figée.** Le Mega remet alors la drive board et les lampes à l'état
   sûr 200 ms plus tard, au lieu de laisser une force ou une lampe collée.
7. Sans trame depuis environ 100 ms, considérer la liaison comme perdue : tous les contacts relâchés, les potentiomètres au
   repos et la réponse de la drive board à `0xFF`. Si le Mega a été débranché, rouvrir le port.
8. En quittant, envoyer `5A 00 00 A6` (moteur coupé, tout éteint), puis fermer le port.

## 8. Précautions avec une vraie drive board

- **Mains hors du volant la première fois.** `00`, l'ordre que le Mega envoie à la mise sous tension et après le chien de
  garde, coupe le moteur d'après la ROM de la drive board (EPR-16488A).
- **Lignes de la drive board pendant le redémarrage :** pendant les ~0,9 s de chargeur du Mega après l'ouverture du port, ses
  sorties vers la drive board ne sont pas pilotées, et la carte n'a pas de résistances sur ces lignes. Ouvrir le port une
  seule fois, au démarrage de l'hôte, et le garder ouvert.
