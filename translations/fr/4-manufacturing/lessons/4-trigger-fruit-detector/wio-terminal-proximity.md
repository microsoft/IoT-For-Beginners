<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-24T21:54:56+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "fr"
}
-->
# Détecter la proximité - Wio Terminal

Dans cette partie de la leçon, vous allez ajouter un capteur de proximité à votre Wio Terminal et lire les distances qu'il mesure.

## Matériel

Le Wio Terminal a besoin d'un capteur de proximité.

Le capteur que vous utiliserez est un [capteur de distance Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ce capteur utilise un module de télémétrie laser pour détecter les distances. Il a une portée de 10 mm à 2000 mm (1 cm - 2 m) et fournit des mesures assez précises dans cette plage, avec des distances supérieures à 1000 mm rapportées comme 8109 mm.

Le télémètre laser se trouve à l'arrière du capteur, du côté opposé à la prise Grove.

C'est un socket I2C.

### Connecter le capteur Time of Flight

Le capteur Grove Time of Flight peut être connecté au Wio Terminal.

#### Tâche - connecter le capteur Time of Flight

Connectez le capteur Time of Flight.

![Un capteur Grove Time of Flight](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.fr.png)

1. Insérez une extrémité d'un câble Grove dans la prise du capteur Time of Flight. Il ne peut être inséré que dans un seul sens.

1. Avec le Wio Terminal déconnecté de votre ordinateur ou de toute autre source d'alimentation, connectez l'autre extrémité du câble Grove à la prise Grove située sur le côté gauche du Wio Terminal lorsque vous regardez l'écran. C'est la prise la plus proche du bouton d'alimentation. Il s'agit d'une prise combinée numérique et I2C.

![Le capteur Grove Time of Flight connecté à la prise de gauche](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73d.fr.png)

1. Vous pouvez maintenant connecter le Wio Terminal à votre ordinateur.

## Programmer le capteur Time of Flight

Le Wio Terminal peut maintenant être programmé pour utiliser le capteur Time of Flight connecté.

### Tâche - programmer le capteur Time of Flight

1. Créez un nouveau projet Wio Terminal en utilisant PlatformIO. Appelez ce projet `distance-sensor`. Ajoutez du code dans la fonction `setup` pour configurer le port série.

1. Ajoutez une dépendance de bibliothèque pour la bibliothèque Seeed Grove Time of Flight Distance Sensor dans le fichier `platformio.ini` du projet :

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. Dans `main.cpp`, ajoutez ce qui suit sous les directives d'inclusion existantes pour déclarer une instance de la classe `Seeed_vl53l0x` afin d'interagir avec le capteur Time of Flight :

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Ajoutez ce qui suit à la fin de la fonction `setup` pour initialiser le capteur :

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Dans la fonction `loop`, lisez une valeur depuis le capteur :

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Ce code initialise une structure de données pour y lire les données, puis la passe à la méthode `PerformSingleRangingMeasurement` où elle sera remplie avec la mesure de distance.

1. En dessous, écrivez la mesure de distance, puis ajoutez un délai d'une seconde :

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Compilez, téléversez et exécutez ce code. Vous pourrez voir les mesures de distance dans le moniteur série. Placez des objets près du capteur et vous verrez la mesure de distance :

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Le télémètre se trouve à l'arrière du capteur, alors assurez-vous d'utiliser le bon côté pour mesurer la distance.

    ![Le télémètre à l'arrière du capteur Time of Flight pointant vers une banane](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.fr.png)

> 💁 Vous pouvez trouver ce code dans le dossier [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Votre programme de capteur de proximité est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.