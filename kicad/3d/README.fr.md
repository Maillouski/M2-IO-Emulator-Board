# Modèles 3D

[English](README.md) | **Français**

| Fichier | Utilisé par | Origine | Licence |
|---|---|---|---|
| `Arduino_Mega2560_Rev3e.stpz` | MEGA1 (Arduino Mega 2560, empreinte de carte seulement) | construit à partir des fichiers CAO officiels d'Arduino pour le Mega 2560 Rev3e (`A000067-cad-files.zip`, carte Eagle), avec des modèles 3D de la bibliothèque KiCad posés sur ses composants | CC BY-SA 4.0 (Arduino ; bibliothèques KiCad) |
| `USB_B_boite_H11.wrl` | MEGA1 (prise USB-B, simple boîte de 16,6 × 12,2 × 11 mm) | fait pour ce projet | CC BY-NC-SA 4.0, comme la carte |
| `JST_NH_B5P-SHF-1AA_simple.wrl`, `JST_NH_B10P-SHF-1AA_simple.wrl`, `JST_NH_B12P-SHF-1AA_simple.wrl` | J14, J3 (CN3), J4/J5 (CN5/CN6) | modèles simplifiés faits pour ce projet (embase de 3,2 mm de haut et 5,6 mm de profondeur ; broches de 0,64 mm de −3,4 à +9,2 mm), d'après les cotes de la fiche JST NH et de DigiKey | CC BY-NC-SA 4.0, comme la carte |
| `RCJ-2223_generique.step` | J16 (Same Sky RCJ-2223, double prise RCA superposée) | modèle simplifié fait pour ce projet aux cotes de la fiche technique RCJ-22 (boîtier, isolants rouge et blanc, fûts, broches) ; l'oreille de fixation latérale est approximative | CC BY-NC-SA 4.0, comme la carte |

Toutes les autres pièces utilisent la bibliothèque 3D standard de KiCad 10 (`${KICAD10_3DMODEL_DIR}`) ; TP1-TP4 et U5 prennent le modèle le plus proche qu'elle contient (Keystone 5005-5009, QFN-32 5 × 5 à pastille de 3,3 mm).
