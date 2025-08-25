<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T00:54:50+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "fr"
}
-->
# Décoder les données GPS - Wio Terminal

Dans cette partie de la leçon, vous allez décoder les messages NMEA lus depuis le capteur GPS par le Wio Terminal et extraire la latitude et la longitude.

## Décoder les données GPS

Une fois les données brutes NMEA lues depuis le port série, elles peuvent être décodées à l'aide d'une bibliothèque NMEA open source.

### Tâche - décoder les données GPS

Programmez l'appareil pour décoder les données GPS.

1. Ouvrez le projet de l'application `gps-sensor` s'il n'est pas déjà ouvert.

1. Ajoutez une dépendance de bibliothèque pour la bibliothèque [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) au fichier `platformio.ini` du projet. Cette bibliothèque contient du code pour décoder les données NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Dans `main.cpp`, ajoutez une directive d'inclusion pour la bibliothèque TinyGPSPlus :

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Sous la déclaration de `Serial3`, déclarez un objet TinyGPSPlus pour traiter les phrases NMEA :

    ```cpp
    TinyGPSPlus gps;
    ```

1. Modifiez le contenu de la fonction `printGPSData` comme suit :

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Ce code lit le prochain caractère du port série UART dans le décodeur NMEA `gps`. Après chaque caractère, il vérifie si le décodeur a lu une phrase valide, puis s'il a lu une localisation valide. Si la localisation est valide, elle est envoyée au moniteur série, accompagnée du nombre de satellites ayant contribué à cette localisation.

1. Compilez et téléchargez le code sur le Wio Terminal.

1. Une fois téléchargé, vous pouvez surveiller les données de localisation GPS à l'aide du moniteur série.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Votre programme de capteur GPS avec décodage des données a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.