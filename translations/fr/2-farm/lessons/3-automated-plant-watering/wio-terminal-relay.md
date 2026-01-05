<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-24T22:16:38+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "fr"
}
-->
# Contrôler un relais - Wio Terminal

Dans cette partie de la leçon, vous allez ajouter un relais à votre Wio Terminal en plus du capteur d'humidité du sol, et le contrôler en fonction du niveau d'humidité du sol.

## Matériel

Le Wio Terminal nécessite un relais.

Le relais que vous utiliserez est un [relais Grove](https://www.seeedstudio.com/Grove-Relay.html), un relais normalement ouvert (ce qui signifie que le circuit de sortie est ouvert ou déconnecté lorsqu'aucun signal n'est envoyé au relais) qui peut gérer des circuits de sortie jusqu'à 250V et 10A.

C'est un actionneur numérique, il se connecte donc aux broches numériques du Wio Terminal. Le port combiné analogique/numérique est déjà utilisé avec le capteur d'humidité du sol, donc ce relais se branche sur l'autre port, qui est un port combiné I2C et numérique.

### Connecter le relais

Le relais Grove peut être connecté au port numérique du Wio Terminal.

#### Tâche

Connectez le relais.

![Un relais Grove](../../../../../translated_images/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.fr.png)

1. Insérez une extrémité d'un câble Grove dans la prise du relais. Il ne peut être inséré que dans un seul sens.

1. Avec le Wio Terminal déconnecté de votre ordinateur ou de toute autre source d'alimentation, connectez l'autre extrémité du câble Grove à la prise Grove située à gauche sur le Wio Terminal, en regardant l'écran. Laissez le capteur d'humidité du sol connecté à la prise de droite.

![Le relais Grove connecté à la prise de gauche, et le capteur d'humidité du sol connecté à la prise de droite](../../../../../translated_images/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.fr.png)

1. Insérez le capteur d'humidité du sol dans la terre, s'il n'est pas déjà en place depuis la leçon précédente.

## Programmer le relais

Le Wio Terminal peut maintenant être programmé pour utiliser le relais connecté.

### Tâche

Programmez l'appareil.

1. Ouvrez le projet `soil-moisture-sensor` de la leçon précédente dans VS Code s'il n'est pas déjà ouvert. Vous allez ajouter du code à ce projet.

2. Il n'existe pas de bibliothèque pour cet actionneur - c'est un actionneur numérique contrôlé par un signal haut ou bas. Pour l'allumer, vous envoyez un signal haut à la broche (3.3V), pour l'éteindre, vous envoyez un signal bas (0V). Vous pouvez le faire en utilisant la fonction Arduino intégrée [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/). Commencez par ajouter ce qui suit à la fin de la fonction `setup` pour configurer le port combiné I2C/numérique comme une broche de sortie afin d'envoyer une tension au relais :

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` est le numéro de port pour le port combiné I2C/numérique.

1. Pour tester si le relais fonctionne, ajoutez ce qui suit à la fonction `loop`, sous le dernier `delay` :

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Ce code envoie un signal haut à la broche à laquelle le relais est connecté pour l'allumer, attend 500ms (une demi-seconde), puis envoie un signal bas pour éteindre le relais.

1. Compilez et téléchargez le code sur le Wio Terminal.

1. Une fois le code téléchargé, le relais s'allumera et s'éteindra toutes les 10 secondes, avec un délai d'une demi-seconde entre l'allumage et l'extinction. Vous entendrez le relais cliquer pour s'allumer, puis cliquer pour s'éteindre. Une LED sur la carte Grove s'allumera lorsque le relais est activé, puis s'éteindra lorsque le relais est désactivé.

    ![Le relais s'allume et s'éteint](../../../../../images/relay-turn-on-off.gif)

## Contrôler le relais en fonction de l'humidité du sol

Maintenant que le relais fonctionne, il peut être contrôlé en réponse aux relevés d'humidité du sol.

### Tâche

Contrôlez le relais.

1. Supprimez les 3 lignes de code que vous avez ajoutées pour tester le relais. Remplacez-les par le code suivant :

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Ce code vérifie le niveau d'humidité du sol à partir du capteur d'humidité du sol. Si le niveau est supérieur à 450, il allume le relais, et l'éteint lorsqu'il descend en dessous de 450.

    > 💁 Rappelez-vous que le capteur capacitif d'humidité du sol fonctionne ainsi : plus le niveau d'humidité du sol est bas, plus il y a d'humidité dans le sol, et inversement.

1. Compilez et téléchargez le code sur le Wio Terminal.

1. Surveillez l'appareil via le moniteur série. Vous verrez le relais s'allumer ou s'éteindre en fonction du niveau d'humidité du sol. Essayez dans un sol sec, puis ajoutez de l'eau.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Votre programme de contrôle du relais par le capteur d'humidité du sol est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.