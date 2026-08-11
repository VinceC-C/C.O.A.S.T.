# C.O.A.S.T.

## Complete Obstacle Avoidance System

<p align="center"> <strong>An Audio-Based Obstacle Awareness System for Power Wheelchair Users</strong> </p>

<p align="center"> <em>Detect. Process. Alert. Navigate.</em> </p>

<p align="center"> <strong>Un système de détection d'obstacles par rétroaction audio pour les utilisateurs de fauteuils roulants électriques</strong> </p>

<p align="center"> <em>Détecter. Traiter. Alerter. Naviguer.</em> </p>

---

## Table of Contents

* [About C.O.A.S.T.](#about-coast)
* [How It Works](#how-it-works)
* [System Architecture](#system-architecture)
* [Features](#features)
* [Hardware](#hardware)
* [Hardware & Pinout](#hardware--pinout)
* [Alert Zones](#alert-zones)
* [MP3 File Mapping](#mp3-file-mapping)
* [Installation](#installation)
* [Setting Up the MP3 Files](#setting-up-the-mp3-files)
* [Operating the System](#operating-the-system)
* [Important Notes](#important-notes)
* [Project Purpose](#project-purpose)
* [🇫🇷 Version française](#-version-française)
* [À propos de C.O.A.S.T.](#à-propos-de-coast)
* [Fonctionnement](#️fonctionnement)
* [Architecture du système](#architecture-du-système)
* [Fonctionnalités](#fonctionnalités)
* [Matériel](#matériel)
* [Connexions et brochage](#connexions-et-brochage)
* [Zones d'alerte](#zones-dalerte)
* [Correspondance des fichiers MP3](#correspondance-des-fichiers-mp3)
* [Installation](#installation)
* [Installation des fichiers MP3](#installation-des-fichiers-mp3)
* [Utilisation du système](#utilisation)
* [Maintien actif de la banque d'alimentation](#maintien-actif-de-la-banque-dalimentation)
* [Remarques importantes](#️remarques-importantes)
* [Objectif du projet](#objectif-du-projet)




---

# About C.O.A.S.T.

**C.O.A.S.T. (Complete Obstacle Avoidance System)** is a detachable obstacle-awareness system designed to assist a legally blind power wheelchair user when navigating different environments.

The system uses **five ultrasonic sensors** positioned around the wheelchair to detect nearby obstacles. When an obstacle is detected within a predefined distance, C.O.A.S.T. provides the user with a short **directional audio warning** indicating where the obstacle is located.

C.O.A.S.T. is designed as an **assistive awareness system**, not as an autonomous wheelchair controller. The device does **not control the wheelchair's steering, acceleration, or braking**. The user remains entirely responsible for controlling the wheelchair.

The goal of C.O.A.S.T. is to provide legally blind and/or power-wheelchair users with additional environmental information through audio feedback. This addresses an important accessibility problem faced by individuals who may have difficulty navigating independently in unfamiliar or changing environments.

---

# How It Works

C.O.A.S.T. follows a **pipeline architecture**, where sensor data moves through a sequence of processing stages before an audio output is produced.

The system operates approximately as follows:

1. The **Arduino Uno R3** reads the five ultrasonic sensors.
2. The Arduino checks the state of the **four directional switches**.
3. Based on the switch states, the system determines which sensor readings should currently be considered.
4. The ultrasonic measurements are converted into distances.
5. The distances are compared against the predefined alert zones.
6. If an obstacle is detected within an alert zone for the required number of readings, the corresponding alert is triggered.
7. The Arduino sends a command to the **DFPlayer Mini**.
8. The DFPlayer Mini plays the appropriate MP3 file.
9. The audio warning is played through the connected speaker.

A separate **horn button** can trigger its own audio file.

The system also includes a **power-bank keep-alive mechanism**. If no alert has been played for approximately 30 seconds, the Arduino plays a brief silent audio file. This helps prevent a power bank from entering sleep mode when the system is otherwise idle.

---

# System Architecture

The C.O.A.S.T. software and hardware can be represented by the following pipeline:

```text
┌───────────────────────────┐
│     5× HC-SR04 Sensors    │
│                           │
│     FL  FR  BL  BC  BR    │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│      Arduino Uno R3       │
│                           │
│   Read sensor distances   │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│    Directional Switches   │
│                           │
│   Filter active sensors   │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│    Distance Processing    │
│                           │
│   Convert echo time → cm  │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│       Alert Zones         │
│                           │
│  0-30  30–50  50–80  80<  │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│       DFPlayer Mini       │
│                           │
│        Select MP3         │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│         Speaker           │
│                           │
│  Directional Voice Alert  │
└───────────────────────────┘
```

### Data Processing Pipeline

```text
Sensor Input
     ↓
Sensor Filtering
     ↓
Distance Calculation
     ↓
Detection Validation
     ↓
Alert Zone Classification
     ↓
Directional Audio Selection
     ↓
DFPlayer Mini
     ↓
Audio Output
```

---

# Features

*  **Directional voice alerts**
*  **Five ultrasonic obstacle sensors**
*  **Four directional switches**
*  **Dedicated horn button**
*  **Distance-based alert zones**
*  **No alert for extremely close or distant readings outside configured zones**
*  **Multi-reading detection filtering**
*  **Sequential handling of multiple detected directions**
*  **30-second power-bank keep-alive**
*  **MP3 audio stored on a microSD card**
*  **Detachable system architecture**
*  **Designed for power-wheelchair obstacle awareness**
*  **Does not control wheelchair steering or braking**

---

# Hardware

C.O.A.S.T. is designed around the following hardware:

| Component                 | Quantity | Purpose                  |
| ------------------------- | -------: | ------------------------ |
| Arduino Uno R3            |        1 | Main controller          |
| HC-SR04 Ultrasonic Sensor |        5 | Obstacle detection       |
| DFPlayer Mini             |        1 | MP3 audio playback       |
| Speaker                   |        1 | Audio output             |
| Directional Switch        |        4 | Select active directions |
| Horn Button               |        1 | Trigger horn audio       |
| microSD Card              |        1 | Stores MP3 files         |
| Power Source              |        1 | Powers the system        |

### Sensor Positions

| Sensor | Direction   |
| ------ | ----------- |
| FL     | Front Left  |
| FR     | Front Right |
| BL     | Back Left   |
| BC     | Back Center |
| BR     | Back Right  |

---

# Hardware & Pinout

The following pin configuration corresponds to the current C.O.A.S.T. Arduino implementation.

## Ultrasonic Sensors

| Sensor     | TRIG | ECHO | Direction   |
| ---------- | ---: | ---: | ----------- |
| HC-SR04 FL |   D4 |   D5 | Front Left  |
| HC-SR04 FR |   D6 |   D7 | Front Right |
| HC-SR04 BL |   D8 |   D9 | Back Left   |
| HC-SR04 BC |  D10 |  D11 | Back Center |
| HC-SR04 BR |  D12 |  D13 | Back Right  |

## Directional Switches

| Switch  | Arduino Pin | Function    |
| ------- | ----------: | ----------- |
| SW_L    |          A0 | Left        |
| SW_F    |          A1 | Front       |
| SW_R    |          A2 | Right       |
| SW_B    |          A3 | Back        |
| SW_HORN |          A4 | Horn button |

The directional switches use the Arduino's internal pull-up resistors.

Therefore:

```text
LOW  = Switch ON / Pressed
HIGH = Switch OFF / Released
```

## DFPlayer Mini

| Function    | Arduino Pin |
| ----------- | ----------: |
| DFPlayer RX |          D2 |
| DFPlayer TX |          D3 |

The Arduino communicates with the DFPlayer Mini using serial communication.

> **Note:** The exact physical wiring between the Arduino and DFPlayer Mini should follow the wiring used by the project. In particular, the Arduino TX/RX lines must be connected to the appropriate DFPlayer RX/TX pins.

---

# Alert Zones

C.O.A.S.T. classifies detected obstacles according to their distance from the ultrasonic sensor.

| Distance     | Alert Level | Volume |
| ------------ | ----------- | -----: |
| `< 30 cm`    | No alert    |      0 |
| `30–<50 cm`  | High        |     30 |
| `50–<80 cm`  | Medium      |     20 |
| `> 80 cm`    | No alert    |      0 |

The system also requires an obstacle to be detected consistently across multiple readings before triggering an alert.

The current implementation uses:

```text
DETECTION_COUNT = 2
```

This helps reduce alerts caused by isolated or unreliable sensor readings.

---

# MP3 File Mapping

The DFPlayer Mini reads the audio files stored in the `MP3` directory on the microSD card.

The current software uses the following mapping:

| MP3 Number | Function             | Direction   |
| ---------: | -------------------- | ----------- |
| `0001.mp3` | Startup / Keep-alive | —           |
| `0002.mp3` | Obstacle warning     | Front Left  |
| `0003.mp3` | Obstacle warning     | Front Right |
| `0004.mp3` | Obstacle warning     | Back Left   |
| `0005.mp3` | Obstacle warning     | Back Center |
| `0006.mp3` | Obstacle warning     | Back Right  |
| `0007.mp3` | Horn                 | —           |

The expected folder structure is:

```text
microSD
└── MP3
    ├── 0001.mp3
    ├── 0002.mp3
    ├── 0003.mp3
    ├── 0004.mp3
    ├── 0005.mp3
    ├── 0006.mp3
    └── 0007.mp3
```

> **Important:** The file names and numbering must match the values used by the Arduino code. If the MP3 numbering is changed, the corresponding `playMp3Folder()` calls in the code must also be changed.

---

# Installation

## 1. Install Arduino IDE

Download and install the **Arduino IDE** on your computer.

The project requires the Arduino IDE to compile and upload the C.O.A.S.T. software to the Arduino Uno R3.

---

## 2. Download the Repository

Clone the repository using Git:

```bash
git clone <repository-url>
```

Or download the repository as a ZIP file from GitHub and extract it.

---

## 3. Open the Project

Open the C.O.A.S.T. Arduino source file in Arduino IDE.

Make sure the required libraries used by the project are installed.

The project uses the **DFRobot DFPlayer Mini library** and Arduino serial communication functionality.

---

## 4. Connect the Arduino

Connect the **Arduino Uno R3** to your computer using USB.

In Arduino IDE, select:

```text
Tools
 ├── Board → Arduino Uno
 └── Port → <Arduino COM Port>
```

---

## 5. Compile the Code

Click:

```text
Verify
```

or use:

```text
Ctrl + R
```

Make sure the program compiles without errors.

---

## 6. Upload the Code

Click:

```text
Upload
```

or use:

```text
Ctrl + U
```

The C.O.A.S.T. program will then be uploaded to the Arduino Uno R3.

---

# Setting Up the MP3 Files

The DFPlayer Mini requires a microSD card containing the project's MP3 files.

### Step 1 — Prepare the microSD card

Insert the microSD card into your computer.

### Step 2 — Copy the MP3 folder

Copy the `MP3` folder included in this repository directly onto the microSD card.

The final structure should look like:

```text
microSD
└── MP3
    ├── 0001.mp3
    ├── 0002.mp3
    ├── 0003.mp3
    ├── 0004.mp3
    ├── 0005.mp3
    ├── 0006.mp3
    └── 0007.mp3
```

### Step 3 — Insert the card

Safely eject the microSD card from the computer and insert it into the DFPlayer Mini.

### Step 4 — Connect the speaker

Connect the speaker to the DFPlayer Mini according to the project's hardware configuration.

### Step 5 — Power the system

Power the Arduino and the connected hardware.

The system should initialize the DFPlayer Mini and begin operating.

---

# Operating the System

Once powered on, C.O.A.S.T. continuously processes the ultrasonic sensor data.

### Direction Selection

The directional switches determine which sensor combinations are active.

The current logic is:

```text
Front + Left  → Front Left
Front + Right → Front Right

Back + Left   → Back Left
Back          → Back Center
Back + Right  → Back Right
```

This allows the system to focus its obstacle detection on the direction selected by the user.

### Obstacle Detection

When an active sensor detects an obstacle:

```text
Obstacle detected
        ↓
Distance calculated
        ↓
Alert zone determined
        ↓
Detection confirmed
        ↓
Directional MP3 selected
        ↓
Audio played
```

### Horn

Pressing the horn button triggers the dedicated horn MP3 file.

---

# Power-Bank Keep-Alive

Some USB power banks automatically shut down when the connected device consumes very little power for an extended period.

C.O.A.S.T. includes a keep-alive mechanism to reduce this issue.

If no normal alert has been played for approximately:

```text
30 seconds
```

the Arduino triggers the keep-alive audio file.

The keep-alive audio is intended to be effectively silent or inaudible while still creating activity on the DFPlayer Mini.

This feature is particularly useful when the system is powered from a portable USB power bank.

---

# Important Notes

C.O.A.S.T. is an **assistive technology prototype** intended to provide additional environmental awareness.

It should not be considered a replacement for:

* Safe wheelchair operation
* User judgment
* Accessibility equipment
* Professional mobility assistance
* Wheelchair steering or braking systems

The system **does not control the wheelchair**.

Ultrasonic sensors can also be affected by:

* Object shape
* Object material
* Object orientation
* Very small objects
* Environmental conditions
* Sensor-to-sensor interference
* Measurement limitations

For these reasons, C.O.A.S.T. should be thoroughly tested before being used in real-world environments.

---

# Project Purpose

The purpose of C.O.A.S.T. is to explore how embedded systems, ultrasonic sensing, digital audio, and software processing can be combined to improve environmental awareness for power-wheelchair users.

The project focuses on providing the user with **additional information without taking control away from them**.

Instead of automatically steering the wheelchair or applying the brakes, C.O.A.S.T. converts sensor measurements into short directional audio prompts. This allows the user to remain responsible for navigation while receiving additional information about nearby obstacles.

---

# 🇫🇷 Version française

## À propos de C.O.A.S.T.

**C.O.A.S.T. (Complete Obstacle Avoidance System)** est un système détachable de détection d'obstacles conçu pour aider une personne légalement aveugle utilisant un fauteuil roulant électrique à se déplacer dans différents environnements.

Le système utilise **cinq capteurs à ultrasons** placés autour du fauteuil roulant afin de détecter les obstacles à proximité. Lorsqu'un obstacle est détecté dans une distance prédéfinie, C.O.A.S.T. fournit à l'utilisateur une **alerte audio directionnelle** indiquant la position de l'obstacle.

C.O.A.S.T. est conçu comme un **système d'assistance à la perception de l'environnement**, et non comme un système autonome de contrôle du fauteuil roulant. Le dispositif ne contrôle **ni la direction, ni l'accélération, ni le freinage** du fauteuil. L'utilisateur conserve entièrement le contrôle du fauteuil roulant.

L'objectif de C.O.A.S.T. est de fournir aux personnes légalement aveugles et/ou aux utilisateurs de fauteuils roulants électriques des informations supplémentaires sur leur environnement grâce à une rétroaction audio. Cela répond à un problème important d'accessibilité auquel certaines personnes peuvent être confrontées lorsqu'elles tentent de se déplacer de façon autonome dans des environnements nouveaux ou changeants.

---

# Fonctionnement

C.O.A.S.T. utilise une **architecture en pipeline**, dans laquelle les données provenant des capteurs passent par plusieurs étapes de traitement avant de produire une sortie audio.

Le fonctionnement général est le suivant :

1. L'**Arduino Uno R3** lit les cinq capteurs à ultrasons.
2. L'Arduino vérifie l'état des **quatre interrupteurs directionnels**.
3. Le système détermine quels capteurs doivent être pris en compte.
4. Les mesures ultrasoniques sont converties en distances.
5. Les distances sont comparées aux zones d'alerte prédéfinies.
6. Si un obstacle est détecté de façon suffisamment constante dans une zone d'alerte, le système déclenche l'alerte correspondante.
7. L'Arduino envoie une commande au **DFPlayer Mini**.
8. Le DFPlayer Mini lit le fichier MP3 approprié.
9. Le son est diffusé par le haut-parleur.

Un **bouton de klaxon** permet également de déclencher un fichier audio distinct.

Le système possède aussi un **mécanisme de maintien actif de la banque d'alimentation**. Si aucune alerte n'a été jouée pendant environ 30 secondes, l'Arduino joue brièvement un fichier audio silencieux afin de générer suffisamment d'activité pour empêcher une banque d'alimentation de passer en mode veille.

---

# Architecture du système

```text
┌───────────────────────────┐
│    5× Capteurs HC-SR04    │
│                           │
│    FL  FR  BL  BC  BR     │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│      Arduino Uno R3       │
│                           │
│    Lecture des distances  │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│Interrupteurs directionnels│
│                           │
│   Filtrage des capteurs   │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│    Calcul de distance     │
│                           │
│    Temps d'écho → cm      │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│       Zones d'alerte      │
│                           │
│  0-30  30–50  50–80  80<  │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│       DFPlayer Mini       │
│                           │
│      Sélection du MP3     │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│        Haut-parleur       │
│                           │
│Alerte audio directionnelle│
└───────────────────────────┘
```

---

# Fonctionnalités

*  **Alertes vocales directionnelles**
*  **Cinq capteurs à ultrasons**
*  **Quatre interrupteurs directionnels**
*  **Bouton de klaxon dédié**
*  **Détection basée sur la distance**
*  **Zones d'alerte prédéfinies**
*  **Filtrage des détections**
*  **Gestion de plusieurs directions**
*  **Maintien actif de la banque d'alimentation**
*  **Lecture audio à partir d'une carte microSD**
*  **Architecture détachable**
*  **Conçu pour les utilisateurs de fauteuils roulants électriques**
*  **Aucun contrôle de la direction ou du freinage**

---

# Matériel

| Composant                 | Quantité | Fonction                  |
| ------------------------- | -------: | ------------------------- |
| Arduino Uno R3            |        1 | Contrôleur principal      |
| Capteur HC-SR04           |        5 | Détection des obstacles   |
| DFPlayer Mini             |        1 | Lecture des fichiers MP3  |
| Haut-parleur              |        1 | Sortie audio              |
| Interrupteur directionnel |        4 | Sélection des directions  |
| Bouton de klaxon          |        1 | Déclenchement du klaxon   |
| Carte microSD             |        1 | Stockage des fichiers MP3 |
| Source d'alimentation     |        1 | Alimentation du système   |

---

# Connexions et brochage

## Capteurs à ultrasons

| Capteur    | TRIG | ECHO | Direction      |
| ---------- | ---: | ---: | -------------- |
| HC-SR04 FL |   D4 |   D5 | Avant gauche   |
| HC-SR04 FR |   D6 |   D7 | Avant droit    |
| HC-SR04 BL |   D8 |   D9 | Arrière gauche |
| HC-SR04 BC |  D10 |  D11 | Centre arrière |
| HC-SR04 BR |  D12 |  D13 | Arrière droit  |

## Interrupteurs

| Interrupteur | Broche Arduino | Fonction |
| ------------ | -------------: | -------- |
| SW_L         |             A0 | Gauche   |
| SW_F         |             A1 | Avant    |
| SW_R         |             A2 | Droite   |
| SW_B         |             A3 | Arrière  |
| SW_HORN      |             A4 | Klaxon   |

Les interrupteurs utilisent les résistances pull-up internes de l'Arduino :

```text
LOW  = Interrupteur activé / appuyé
HIGH = Interrupteur désactivé / relâché
```

## DFPlayer Mini

| Fonction    | Broche Arduino |
| ----------- | -------------: |
| DFPlayer RX |             D2 |
| DFPlayer TX |             D3 |

---

# Zones d'alerte

| Distance     | Niveau d'alerte | Volume |
| ------------ | --------------- | -----: |
| `< 30 cm`    | Aucune alerte   |      0 |
| `30–<50 cm`  | Élevé           |     30 |
| `50–<80 cm`  | Moyen           |     20 |
| `>80 cm`     | Aucune alerte   |      0 |

Le système utilise également plusieurs lectures consécutives afin de réduire les fausses détections.

La configuration actuelle utilise :

```text
DETECTION_COUNT = 2
```

---

# Correspondance des fichiers MP3

| Numéro MP3 | Fonction                   | Direction      |
| ---------: | -------------------------- | -------------- |
| `0001.mp3` | Démarrage / maintien actif | —              |
| `0002.mp3` | Alerte obstacle            | Avant gauche   |
| `0003.mp3` | Alerte obstacle            | Avant droit    |
| `0004.mp3` | Alerte obstacle            | Arrière gauche |
| `0005.mp3` | Alerte obstacle            | Centre arrière |
| `0006.mp3` | Alerte obstacle            | Arrière droit  |
| `0007.mp3` | Klaxon                     | —              |

Structure attendue :

```text
microSD
└── MP3
    ├── 0001.mp3
    ├── 0002.mp3
    ├── 0003.mp3
    ├── 0004.mp3
    ├── 0005.mp3
    ├── 0006.mp3
    └── 0007.mp3
```

> **Important :** Les noms et numéros des fichiers doivent correspondre à ceux utilisés dans le code Arduino.

---

# Installation

## 1. Installer Arduino IDE

Téléchargez et installez **Arduino IDE** sur votre ordinateur.

## 2. Télécharger le dépôt

Clonez le dépôt :

```bash
git clone <repository-url>
```

Vous pouvez également télécharger le dépôt sous forme de fichier ZIP depuis GitHub.

## 3. Ouvrir le projet

Ouvrez le fichier source Arduino de C.O.A.S.T. dans Arduino IDE.

Assurez-vous que les bibliothèques nécessaires au DFPlayer Mini sont installées.

## 4. Connecter l'Arduino

Connectez l'**Arduino Uno R3** à l'ordinateur par USB.

Dans Arduino IDE :

```text
Tools
 ├── Board → Arduino Uno
 └── Port → <Port COM de l'Arduino>
```

## 5. Compiler

Cliquez sur :

```text
Verify
```

ou utilisez :

```text
Ctrl + R
```

## 6. Téléverser

Cliquez sur :

```text
Upload
```

ou utilisez :

```text
Ctrl + U
```

Le programme C.O.A.S.T. est maintenant installé sur l'Arduino.

---

# Installation des fichiers MP3

1. Insérez une carte microSD dans votre ordinateur.
2. Copiez le dossier `MP3` du dépôt sur la carte.
3. Vérifiez que les fichiers sont correctement nommés.
4. Éjectez la carte microSD.
5. Insérez-la dans le DFPlayer Mini.
6. Connectez le haut-parleur.
7. Connectez le DFPlayer Mini à l'Arduino.
8. Alimentez le système.

La structure finale doit être :

```text
microSD
└── MP3
    ├── 0001.mp3
    ├── 0002.mp3
    ├── 0003.mp3
    ├── 0004.mp3
    ├── 0005.mp3
    ├── 0006.mp3
    └── 0007.mp3
```

---

# Utilisation

Une fois le système alimenté, C.O.A.S.T. traite continuellement les données provenant des capteurs à ultrasons.

### Sélection des directions

La logique actuelle est :

```text
Avant + Gauche  → Avant gauche
Avant + Droite  → Avant droit

Arrière + Gauche → Arrière gauche
Arrière          → Centre arrière
Arrière + Droite → Arrière droit
```

Lorsqu'un obstacle est détecté :

```text
Obstacle détecté
       ↓
Distance calculée
       ↓
Zone d'alerte déterminée
       ↓
Détection confirmée
       ↓
MP3 directionnel sélectionné
       ↓
Alerte audio
```

Le bouton de klaxon déclenche indépendamment le fichier audio du klaxon.

---

# Maintien actif de la banque d'alimentation

Certaines banques d'alimentation USB s'éteignent automatiquement lorsqu'elles détectent une consommation très faible pendant une période prolongée.

C.O.A.S.T. utilise donc un mécanisme de maintien actif.

Après environ :

```text
30 secondes
```

sans alerte normale, l'Arduino déclenche le fichier audio de maintien actif.

Ce fichier est conçu pour être silencieux ou pratiquement inaudible tout en générant suffisamment d'activité pour aider à maintenir la banque d'alimentation sous tension.

---

# Remarques importantes

C.O.A.S.T. est un **prototype de technologie d'assistance** destiné à fournir une meilleure perception de l'environnement.

Il ne doit pas être considéré comme un remplacement pour :

* Une utilisation sécuritaire du fauteuil roulant
* Le jugement de l'utilisateur
* Des équipements d'accessibilité appropriés
* Une assistance professionnelle
* Les systèmes de direction ou de freinage du fauteuil roulant

Le système **ne contrôle pas le fauteuil roulant**.

Les capteurs à ultrasons peuvent également être influencés par :

* La forme des objets
* Le matériau des objets
* L'orientation des objets
* Les petits objets
* Les conditions environnementales
* Les interférences entre les capteurs
* Les limites de mesure des capteurs

Le système doit donc être testé de manière approfondie avant toute utilisation dans un environnement réel.

---

# Objectif du projet

C.O.A.S.T. a été développé afin d'explorer comment les systèmes embarqués, les capteurs à ultrasons, l'audio numérique et le traitement logiciel peuvent être combinés afin d'améliorer la perception de l'environnement des utilisateurs de fauteuils roulants électriques.

Le projet vise à fournir à l'utilisateur **des informations supplémentaires sans lui retirer le contrôle de son fauteuil**.

Plutôt que de diriger automatiquement le fauteuil ou d'appliquer les freins, C.O.A.S.T. transforme les mesures des capteurs en courtes indications audio directionnelles. L'utilisateur conserve ainsi le contrôle de ses déplacements tout en recevant des informations supplémentaires sur les obstacles à proximité.

---

<p align="center">
  <strong>C.O.A.S.T. — Complete Obstacle Avoidance System</strong><br>
  <em>Assistive technology through sensing, processing, and audio feedback.</em>
  <br> <em>Une technologie d'assistance basée sur la détection, le traitement et la rétroaction audio.</em>
</p>
