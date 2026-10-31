# Éclairage automatique selon la luminosité

Projet IoT n°4 · TP Séance 4 · IGBEGA X

Un montage Arduino qui **allume une lampe quand il fait sombre** et **l'éteint quand la lumière revient**, sans intervention manuelle. La luminosité est lue par un capteur à photorésistance, puis un relais commande la lampe. Les valeurs mesurées s'affichent sur le moniteur série.

> **Mesurer · Afficher · Agir**

[![Ouvrir la simulation dans Wokwi](https://img.shields.io/badge/Simulation-Wokwi-4CAF50)](https://wokwi.com/projects/479406080444882945)

![Schéma de la simulation](images/schema-simulation.png)

## Sommaire

- [Fonctionnement](#fonctionnement)
- [Matériel](#matériel)
- [Branchements](#branchements)
- [Installation et utilisation](#installation-et-utilisation)
- [Résultats des tests](#résultats-des-tests)
- [Réglages et dépannage](#réglages-et-dépannage)
- [Structure du dépôt](#structure-du-dépôt)
- [Démarche en 8 étapes](#démarche-en-8-étapes)
- [Améliorations possibles](#améliorations-possibles)
- [Auteur](#auteur)

## Fonctionnement

1. L'Arduino lit la sortie analogique du capteur sur **A0** (valeur de 0 à 1023) toutes les 500 ms.
2. Il compare cette valeur à **deux seuils** :
   - sous **300** : il fait sombre, la lampe s'allume ;
   - au-dessus de **400** : il fait clair, la lampe s'éteint ;
   - entre 300 et 400 : l'état précédent est conservé.
3. Il commande le **relais** sur la broche **D7**, qui ferme ou ouvre le circuit de la lampe.
4. Il envoie la valeur et l'état de la lampe au **moniteur série**.

Les deux seuils forment une zone d'**hystérésis** : sans elle, la lampe clignoterait quand la lumière est proche de la limite.

## Matériel

| Composant | Quantité | Rôle |
| --- | --- | --- |
| Carte Arduino Uno | 1 | Lit le capteur, exécute le programme et pilote le relais |
| Module capteur de luminosité à photorésistance (LDR), 4 broches : VCC, GND, DO, AO | 1 | Mesure la luminosité ambiante |
| Module relais 5 V, 1 canal | 1 | Allume ou éteint la lampe |
| LED (ou lampe) avec résistance de protection | 1 | Éclairage commandé |
| Plaque d'essai et fils de liaison | 1 lot | Câblage sans soudure |
| Câble USB | 1 | Alimente la carte et téléverse le programme |

Aucun écran n'est utilisé : l'affichage se fait sur le moniteur série.

## Branchements

| Depuis | Vers | Remarque |
| --- | --- | --- |
| Capteur `VCC` | `5V` | Alimentation |
| Capteur `GND` | `GND` | Masse commune |
| Capteur `AO` | `A0` | Sortie analogique lue par le programme |
| Relais `VCC` | `5V` | Alimentation |
| Relais `GND` | `GND` | Masse commune |
| Relais `IN` | `D7` | Commande du relais |
| LED + résistance | Contacts de puissance du relais | Le relais ferme le circuit quand il est activé |

La sortie numérique `DO` du capteur n'est pas utilisée par le programme.

![Schéma du montage](images/schema-simulation.png)

> **Attention :** une LED basse tension suffit pour la démonstration. Ne raccordez pas une lampe sur le secteur sans l'accord de votre encadrant.

## Installation et utilisation

### Dans le simulateur

Ouvrez le [projet Wokwi](https://wokwi.com/projects/479406080444882945) et lancez la simulation. Faites varier la luminosité du capteur et observez la LED, le relais et le moniteur série.

### Sur le montage réel

1. Installez l'[Arduino IDE](https://www.arduino.cc/en/software).
2. Clonez le dépôt :
   ```bash
   git clone https://github.com/<votre-utilisateur>/<nom-du-depot>.git
   ```
3. Ouvrez `eclairage_auto/eclairage_auto.ino` dans l'Arduino IDE.
4. Choisissez la carte **Arduino Uno** et le bon port, puis cliquez sur **Téléverser**.
5. Ouvrez le **moniteur série** à **9600 bauds**.

Exemple de sortie :

```
Lumiere = 405 | Lampe = OFF
Lumiere = 262 | Lampe = ON
```

Le programme n'a besoin d'aucune bibliothèque externe.

## Résultats des tests

Valeurs relevées sur le moniteur série pendant les essais :

| N° | Action | Résultat attendu | Valeur mesurée | Résultat |
| --- | --- | --- | --- | --- |
| 1 | Pièce éclairée | Lampe éteinte | 405 | Conforme |
| 2 | Cacher la LDR | Lampe allumée | 262 | Conforme |
| 3 | Retirer la main | Lampe éteinte | 405 | Conforme |

### Captures de la simulation

| Simulation 1 | Simulation 2 |
| --- | --- |
| ![Simulation 1](images/simulation-1.png) | ![Simulation 2](images/simulation-2.png) |

| Simulation 3 | Simulation 4 |
| --- | --- |
| ![Simulation 3](images/simulation-3.png) | ![Simulation 4](images/simulation-4.png) |

## Réglages et dépannage

- **Seuils :** adaptez `SEUIL_ALLUMER` et `SEUIL_ETEINDRE` dans le code après avoir lu les valeurs réelles de votre capteur sur le moniteur série.
- **Comportement inversé :** selon le capteur et le câblage, la valeur peut augmenter dans le noir au lieu de baisser. Inversez alors les deux comparaisons (`<` et `>`) dans `loop()`.
- **Rien n'apparaît sur le moniteur série :** vérifiez la vitesse (9600 bauds) et le port choisi.
- **Le relais ne réagit pas :** vérifiez l'alimentation 5 V, la masse commune et le fil `IN` sur `D7`.

## Structure du dépôt

```
.
├── README.md
├── eclairage_auto/
│   └── eclairage_auto.ino      # Programme Arduino
├── images/                      # schema-simulation.png et simulation-1 à 4.png
└── docs/
    ├── Rapport_Projet4_Eclairage_automatique.docx
    └── Presentation_Projet4_Eclairage_automatique.pptx
```

## Démarche en 8 étapes

Le projet suit la méthode vue en cours. Le détail de chaque étape est dans le [rapport](docs/Rapport_Projet4_Eclairage_automatique.docx) et la [présentation](docs/Presentation_Projet4_Eclairage_automatique.pptx).

| Étape | Contenu |
| --- | --- |
| 01. Objectif | Allumer la lampe dans l'obscurité, l'éteindre à la lumière |
| 02. Composants | Arduino Uno, capteur de luminosité, relais, LED |
| 03. Schéma et simulation | Montage simulé sur Wokwi |
| 04. Code | `eclairage_auto/eclairage_auto.ino` |
| 05. Validation | Trois scénarios validés en simulation |
| 06. Câblage réel | Montage sur plaque d'essai |
| 07. Tests | Valeurs relevées sur le moniteur série |
| 08. Documentation et publication | Ce dépôt et le lien Wokwi |

## Améliorations possibles

- Régler le seuil avec un potentiomètre.
- Ajouter une temporisation avant l'extinction.
- Envoyer la luminosité vers un tableau de bord IoT avec un module Wi-Fi.

## Auteur

**Jeannot HOUNMENOU** · IGBEGA X · TP Séance 4 IoT
