# Mesurer l'humidité du sol - Wio Terminal

Dans cette partie de la leçon, vous allez ajouter un capteur capacitif d'humidité du sol à votre Wio Terminal et lire les valeurs qu'il fournit.

## Matériel

Le Wio Terminal nécessite un capteur capacitif d'humidité du sol.

Le capteur que vous utiliserez est un [Capteur capacitif d'humidité du sol](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), qui mesure l'humidité du sol en détectant la capacité du sol, une propriété qui change en fonction de l'humidité. Lorsque l'humidité du sol augmente, la tension diminue.

C'est un capteur analogique, il se connecte donc aux broches analogiques du Wio Terminal, en utilisant un convertisseur analogique-numérique (ADC) intégré pour générer une valeur entre 0 et 1 023.

### Connecter le capteur d'humidité du sol

Le capteur Grove d'humidité du sol peut être connecté au port analogique/numérique configurable du Wio Terminal.

#### Tâche - connecter le capteur d'humidité du sol

Connectez le capteur d'humidité du sol.

![Un capteur Grove d'humidité du sol](../../../../../translated_images/fr/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Insérez une extrémité d'un câble Grove dans la prise du capteur d'humidité du sol. Il ne peut être inséré que dans un seul sens.

1. Avec le Wio Terminal déconnecté de votre ordinateur ou de toute autre source d'alimentation, connectez l'autre extrémité du câble Grove à la prise Grove située à droite sur le Wio Terminal, lorsque vous regardez l'écran. C'est la prise la plus éloignée du bouton d'alimentation.

![Le capteur Grove d'humidité du sol connecté à la prise de droite](../../../../../translated_images/fr/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Insérez le capteur d'humidité du sol dans la terre. Il possède une "ligne de position maximale" - une ligne blanche traversant le capteur. Insérez le capteur jusqu'à cette ligne, mais pas au-delà.

![Le capteur Grove d'humidité du sol dans la terre](../../../../../translated_images/fr/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Vous pouvez maintenant connecter le Wio Terminal à votre ordinateur.

## Programmer le capteur d'humidité du sol

Le Wio Terminal peut maintenant être programmé pour utiliser le capteur d'humidité du sol connecté.

### Tâche - programmer le capteur d'humidité du sol

Programmez l'appareil.

1. Créez un nouveau projet Wio Terminal en utilisant PlatformIO. Appelez ce projet `soil-moisture-sensor`. Ajoutez du code dans la fonction `setup` pour configurer le port série.

    > ⚠️ Vous pouvez vous référer [aux instructions pour créer un projet PlatformIO dans le projet 1, leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Il n'existe pas de bibliothèque pour ce capteur, mais vous pouvez lire la broche analogique en utilisant la fonction [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) intégrée d'Arduino. Commencez par configurer la broche analogique en entrée pour pouvoir lire les valeurs en ajoutant le code suivant à la fonction `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Cela configure la broche `A0`, la broche combinée analogique/numérique, comme une broche d'entrée à partir de laquelle la tension peut être lue.

1. Ajoutez le code suivant à la fonction `loop` pour lire la tension sur cette broche :

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. En dessous de ce code, ajoutez le code suivant pour afficher la valeur sur le port série :

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Enfin, ajoutez un délai de 10 secondes à la fin :

    ```cpp
    delay(10000);
    ```

1. Compilez et téléversez le code sur le Wio Terminal.

    > ⚠️ Vous pouvez vous référer [aux instructions pour créer un projet PlatformIO dans le projet 1, leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Une fois téléversé, vous pouvez surveiller l'humidité du sol en utilisant le moniteur série. Ajoutez de l'eau à la terre ou retirez le capteur de la terre, et observez la valeur changer.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    Dans l'exemple de sortie ci-dessus, vous pouvez voir la tension diminuer lorsque de l'eau est ajoutée.

> 💁 Vous pouvez trouver ce code dans le dossier [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Votre programme pour le capteur d'humidité du sol a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.