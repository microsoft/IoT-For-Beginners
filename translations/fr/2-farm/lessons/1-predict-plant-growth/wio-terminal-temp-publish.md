<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-24T22:05:44+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "fr"
}
-->
# Publier la température - Wio Terminal

Dans cette partie de la leçon, vous allez publier les valeurs de température détectées par le Wio Terminal via MQTT afin qu'elles puissent être utilisées ultérieurement pour calculer les GDD.

## Publier la température

Une fois la température lue, elle peut être publiée via MQTT vers un code "serveur" qui lira les valeurs et les stockera pour être utilisées dans un calcul de GDD. Les microcontrôleurs ne lisent pas l'heure sur Internet et ne suivent pas le temps avec une horloge en temps réel par défaut ; l'appareil doit être programmé pour cela, à condition qu'il dispose du matériel nécessaire.

Pour simplifier les choses dans cette leçon, l'heure ne sera pas envoyée avec les données du capteur. Elle pourra être ajoutée plus tard par le code serveur lorsqu'il recevra les messages.

### Tâche

Programmez l'appareil pour publier les données de température.

1. Ouvrez le projet `temperature-sensor` du Wio Terminal.

1. Répétez les étapes effectuées dans la leçon 4 pour vous connecter à MQTT et envoyer des télémétries. Vous utiliserez le même broker public Mosquitto.

    Les étapes sont les suivantes :

    - Ajoutez les bibliothèques Seeed WiFi et MQTT au fichier `.ini`
    - Ajoutez le fichier de configuration et le code pour se connecter au WiFi
    - Ajoutez le code pour se connecter au broker MQTT
    - Ajoutez le code pour publier les télémétries

    > ⚠️ Consultez les [instructions pour se connecter à MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) et les [instructions pour envoyer des télémétries](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) de la leçon 4 si nécessaire.

1. Assurez-vous que le `CLIENT_NAME` dans le fichier d'en-tête `config.h` reflète ce projet :

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Pour la télémétrie, au lieu d'envoyer une valeur de lumière, envoyez la valeur de température lue par le capteur DHT dans une propriété du document JSON appelée `temperature` en modifiant la fonction `loop` dans `main.cpp` :

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. La valeur de température n'a pas besoin d'être lue très souvent - elle ne changera pas beaucoup en peu de temps. Réglez donc le `delay` dans la fonction `loop` à 10 minutes :

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 La fonction `delay` prend le temps en millisecondes. Pour simplifier la lecture, la valeur est passée comme le résultat d'un calcul. 1 000 ms dans une seconde, 60 s dans une minute, donc 10 x (60 s dans une minute) x (1 000 ms dans une seconde) donne un délai de 10 minutes.

1. Téléversez cela sur votre Wio Terminal et utilisez le moniteur série pour voir la température envoyée au broker MQTT.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Vous avez publié avec succès la température en tant que télémétrie depuis votre appareil.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.