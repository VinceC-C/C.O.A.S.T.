# Documentation README

## Electrical System

The C.O.A.S.T. electrical subsystem connects the **Arduino Uno R3**, five ultrasonic sensors, the **DFPlayer Mini**, its voltage divider and capacitor, four directional switches, and the horn button. The circuit is designed to be assembled by following the provided schematic. Unlike a strict step-by-step assembly process, there is no required order for making the connections; as long as every connection matches the schematic, the system should function correctly.

A **protoboard or perfboard** is recommended for assembling the ultrasonic sensors, DFPlayer Mini, voltage divider, and capacitor. The common ground connections for the four directional switches and horn button can also be connected to the perfboard to simplify the wiring and provide a common ground point.

### Pin Configuration

The connections shown in the schematic are **not permanently tied to specific Arduino pins**. The digital I/O pins used for the ultrasonic sensors' **TRIG and ECHO** signals, as well as the **RX and TX** connections for the DFPlayer Mini, can be reassigned if necessary. If the pin layout is changed, the corresponding pin definitions in the Arduino code must also be updated.

The same principle applies to the analog I/O pins used for the directional switches and horn button. These can be reassigned as long as the Arduino code is modified to reflect the new configuration.

The only pins that should generally be avoided are **digital pins 0 and 1**, which are used for serial communication on the Arduino Uno. Using these pins for other components can interfere with programming and serial communication. For additional information about the Arduino Uno's pins and electrical characteristics, refer to the official Arduino Uno documentation.


## Système électrique

Le sous-système électrique de C.O.A.S.T. relie l'**Arduino Uno R3**, cinq capteurs à ultrasons, le **DFPlayer Mini**, son diviseur de tension et son condensateur, quatre interrupteurs directionnels ainsi que le bouton de klaxon. Le circuit est conçu pour être assemblé en suivant le schéma électrique fourni. Contrairement à un processus d'assemblage strict étape par étape, aucun ordre particulier n'est requis pour effectuer les connexions. Tant que chaque connexion correspond au schéma, le système devrait fonctionner correctement.

Il est recommandé d'utiliser une **plaque d'essai ou une plaque perforée (protoboard/perfboard)** pour assembler les capteurs à ultrasons, le DFPlayer Mini, le diviseur de tension et le condensateur. Les connexions de masse communes des quatre interrupteurs directionnels et du bouton de klaxon peuvent également être reliées à la plaque afin de simplifier le câblage et de fournir un point de masse commun.

### Configuration des broches

Les connexions indiquées dans le schéma ne sont **pas obligatoirement liées à des broches Arduino spécifiques**. Les broches d'E/S numériques utilisées pour les signaux **TRIG et ECHO** des capteurs à ultrasons, ainsi que les connexions **RX et TX** du DFPlayer Mini, peuvent être réassignées au besoin. Si la configuration des broches est modifiée, les définitions correspondantes dans le code Arduino doivent également être mises à jour.

Le même principe s'applique aux broches d'E/S analogiques utilisées pour les interrupteurs directionnels et le bouton de klaxon. Ces broches peuvent être réassignées à condition que le code Arduino soit modifié pour correspondre à la nouvelle configuration.

Les seules broches qui devraient généralement être évitées sont les **broches numériques 0 et 1**, qui sont utilisées pour la communication série sur l'Arduino Uno. Leur utilisation pour d'autres composants peut interférer avec la programmation et la communication série. Pour plus d'informations sur les broches et les caractéristiques électriques de l'Arduino Uno, consultez la documentation officielle de l'Arduino Uno.
