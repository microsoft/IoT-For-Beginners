# Publier la température - Terminal Wio

Dans cette partie de la leçon, vous allez publier les valeurs de température détectées par le terminal Wio sur MQTT afin qu'elles puissent être utilisées ultérieurement pour calculer le DJC.

## Publier la température

Une fois la température lue, elle peut être publiée via MQTT vers un code "serveur" qui lira les valeurs et les stockera, prêtes à être utilisées pour un calcul de DJC. Les microcontrôleurs ne lisent pas l'heure sur Internet et ne suivent pas l'heure avec une horloge en temps réel. Le dispositif doit être programmé pour le faire, en supposant qu'il dispose du matériel nécessaire.

Afin de simplifier les choses pour cette leçon, l'heure ne sera pas envoyée avec les données du capteur, mais pourra être ajoutée par le code du serveur plus tard, lorsqu'il recevra les messages.

### Tâche

Programmez l'appareil pour qu'il publie les données de température.

1. Ouvrez le projet Wio Terminal `temperature-sensor`.

1. Répétez les étapes de la leçon 4 pour vous connecter à MQTT et envoyer la télémétrie. Vous utiliserez le même courtier public Mosquitto.

    Les étapes à suivre sont les suivantes :

    - Ajouter les bibliothèques Seeed WiFi et MQTT au fichier `.ini`.
    - Ajouter le fichier de configuration et le code pour se connecter au WiFi
    - Ajouter le code pour se connecter au broker MQTT
    - Ajouter le code pour publier la télémétrie

    > ⚠️ Consultez les [instructions pour la connexion à MQTT].(../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) ainsi que les [instructions pour l'envoi de la télémétrie](../../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) de la leçon 4 si nécessaire.

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

1. La valeur de la température n'a pas besoin d'être lue très souvent - elle ne changera pas beaucoup dans un court laps de temps, donc réglez le "retard" de la fonction "boucle" à 10 minutes :

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 La fonction `delay` prend le temps en millisecondes, donc pour faciliter la lecture, la valeur est passée comme le résultat d'un calcul. 1 000 ms en une seconde, 60s en une minute, donc 10 x (60s en une minute) x (1000 ms en une seconde) donne un délai de 10 minutes.

1. Téléchargez-le sur votre terminal Wio, et utilisez le moniteur série pour voir la température envoyée au courtier MQTT.

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

> 💁 Vous pouvez trouver ce code dans le fichier [code-publish-temperature/wio-terminal].(../code-publish-temperature/wio-terminal).

😀 Vous avez publié avec succès la température en tant que télémétrie de votre appareil!
