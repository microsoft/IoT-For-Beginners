<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-24T22:04:26+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "fr"
}
-->
# Mesurer la température - Wio Terminal

Dans cette partie de la leçon, vous allez ajouter un capteur de température à votre Wio Terminal et lire les valeurs de température qu'il fournit.

## Matériel

Le Wio Terminal a besoin d'un capteur de température.

Le capteur que vous utiliserez est un [capteur d'humidité et de température DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), qui combine deux capteurs dans un seul module. Ce capteur est assez populaire, avec de nombreux modèles disponibles commercialement combinant température, humidité et parfois pression atmosphérique. Le composant capteur de température est une thermistance à coefficient de température négatif (NTC), une thermistance dont la résistance diminue lorsque la température augmente.

C'est un capteur numérique, il dispose donc d'un convertisseur analogique-numérique (ADC) intégré pour générer un signal numérique contenant les données de température et d'humidité que le microcontrôleur peut lire.

### Connecter le capteur de température

Le capteur de température Grove peut être connecté au port numérique du Wio Terminal.

#### Tâche - connecter le capteur de température

Connectez le capteur de température.

![Un capteur de température Grove](../../../../../translated_images/fr/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Insérez une extrémité d'un câble Grove dans la prise du capteur d'humidité et de température. Il ne peut être inséré que dans un seul sens.

1. Avec le Wio Terminal déconnecté de votre ordinateur ou de toute autre source d'alimentation, connectez l'autre extrémité du câble Grove à la prise Grove située à droite sur le Wio Terminal, lorsque vous regardez l'écran. C'est la prise la plus éloignée du bouton d'alimentation.

![Le capteur de température Grove connecté à la prise de droite](../../../../../translated_images/fr/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programmer le capteur de température

Le Wio Terminal peut maintenant être programmé pour utiliser le capteur de température connecté.

### Tâche - programmer le capteur de température

Programmez l'appareil.

1. Créez un nouveau projet Wio Terminal en utilisant PlatformIO. Nommez ce projet `temperature-sensor`. Ajoutez du code dans la fonction `setup` pour configurer le port série.

    > ⚠️ Vous pouvez vous référer [aux instructions pour créer un projet PlatformIO dans le projet 1, leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Ajoutez une dépendance de bibliothèque pour la bibliothèque Seeed Grove Humidity and Temperature sensor dans le fichier `platformio.ini` du projet :

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Vous pouvez vous référer [aux instructions pour ajouter des bibliothèques à un projet PlatformIO dans le projet 1, leçon 4 si nécessaire](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Ajoutez les directives `#include` suivantes en haut du fichier, sous l'existant `#include <Arduino.h>` :

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Cela importe les fichiers nécessaires pour interagir avec le capteur. Le fichier d'en-tête `DHT.h` contient le code pour le capteur lui-même, et l'ajout de l'en-tête `SPI.h` garantit que le code nécessaire pour communiquer avec le capteur est lié lors de la compilation de l'application.

1. Avant la fonction `setup`, déclarez le capteur DHT :

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Cela déclare une instance de la classe `DHT` qui gère le capteur numérique d'humidité et de température (**D**igital **H**umidity and **T**emperature). Celui-ci est connecté au port `D0`, la prise Grove située à droite sur le Wio Terminal. Le second paramètre indique au code que le capteur utilisé est le capteur *DHT11* - la bibliothèque que vous utilisez prend en charge d'autres variantes de ce capteur.

1. Dans la fonction `setup`, ajoutez du code pour configurer la connexion série :

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. À la fin de la fonction `setup`, après le dernier `delay`, ajoutez un appel pour démarrer le capteur DHT :

    ```cpp
    dht.begin();
    ```

1. Dans la fonction `loop`, ajoutez du code pour appeler le capteur et afficher la température sur le port série :

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Ce code déclare un tableau vide de 2 nombres flottants et le passe à l'appel de `readTempAndHumidity` sur l'instance `DHT`. Cet appel remplit le tableau avec 2 valeurs - l'humidité est placée dans le premier élément du tableau (indice 0, car en C++ les tableaux commencent à 0), et la température est placée dans le deuxième élément (indice 1).

    La température est lue à partir du deuxième élément du tableau et affichée sur le port série.

    > 🇺🇸 La température est lue en Celsius. Pour les Américains, pour convertir cette valeur en Fahrenheit, divisez la valeur en Celsius par 5, puis multipliez par 9, puis ajoutez 32. Par exemple, une lecture de température de 20°C devient ((20/5)*9) + 32 = 68°F.

1. Compilez et téléversez le code sur le Wio Terminal.

    > ⚠️ Vous pouvez vous référer [aux instructions pour créer un projet PlatformIO dans le projet 1, leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Une fois téléversé, vous pouvez surveiller la température en utilisant le moniteur série :

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Votre programme de capteur de température a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.