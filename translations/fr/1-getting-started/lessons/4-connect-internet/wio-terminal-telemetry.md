<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-24T23:08:34+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "fr"
}
-->
# Contrôlez votre veilleuse via Internet - Wio Terminal

Dans cette partie de la leçon, vous allez envoyer des données de télémétrie sur les niveaux de lumière depuis votre Wio Terminal vers le broker MQTT.

## Installer les bibliothèques JSON pour Arduino

Une méthode courante pour envoyer des messages via MQTT est d'utiliser JSON. Il existe une bibliothèque Arduino pour JSON qui facilite la lecture et l'écriture de documents JSON.

### Tâche

Installez la bibliothèque Arduino JSON.

1. Ouvrez le projet de veilleuse dans VS Code.

1. Ajoutez la ligne suivante à la liste `lib_deps` dans le fichier `platformio.ini` :

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Cela importe [ArduinoJson](https://arduinojson.org), une bibliothèque JSON pour Arduino.

## Publier la télémétrie

L'étape suivante consiste à créer un document JSON contenant les données de télémétrie et à l'envoyer au broker MQTT.

### Tâche - publier la télémétrie

Publiez les données de télémétrie sur le broker MQTT.

1. Ajoutez le code suivant à la fin du fichier `config.h` pour définir le nom du sujet de télémétrie pour le broker MQTT :

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    Le `CLIENT_TELEMETRY_TOPIC` est le sujet sur lequel l'appareil publiera les niveaux de lumière.

1. Ouvrez le fichier `main.cpp`.

1. Ajoutez la directive `#include` suivante en haut du fichier :

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Ajoutez le code suivant à l'intérieur de la fonction `loop`, juste avant le `delay` :

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Ce code lit le niveau de lumière et crée un document JSON à l'aide d'ArduinoJson contenant ce niveau. Ce document est ensuite sérialisé en une chaîne et publié sur le sujet MQTT de télémétrie par le client MQTT.

1. Téléversez le code sur votre Wio Terminal et utilisez le Moniteur Série pour voir les niveaux de lumière envoyés au broker MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Vous avez envoyé avec succès des données de télémétrie depuis votre appareil.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.