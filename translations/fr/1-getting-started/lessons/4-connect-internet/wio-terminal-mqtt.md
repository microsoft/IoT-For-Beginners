<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-24T23:11:19+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "fr"
}
-->
# Contrôlez votre veilleuse via Internet - Wio Terminal

L'appareil IoT doit être programmé pour communiquer avec *test.mosquitto.org* en utilisant MQTT afin d'envoyer des valeurs de télémétrie avec les relevés du capteur de lumière, et recevoir des commandes pour contrôler la LED.

Dans cette partie de la leçon, vous allez connecter votre Wio Terminal à un broker MQTT.

## Installer les bibliothèques Arduino pour WiFi et MQTT

Pour communiquer avec le broker MQTT, vous devez installer certaines bibliothèques Arduino pour utiliser la puce WiFi du Wio Terminal et communiquer avec MQTT. Lors du développement pour des appareils Arduino, vous pouvez utiliser une large gamme de bibliothèques contenant du code open-source et offrant une multitude de fonctionnalités. Seeed publie des bibliothèques pour le Wio Terminal qui lui permettent de communiquer via WiFi. D'autres développeurs ont publié des bibliothèques pour communiquer avec des brokers MQTT, et vous utiliserez ces bibliothèques avec votre appareil.

Ces bibliothèques sont fournies sous forme de code source qui peut être importé automatiquement dans PlatformIO et compilé pour votre appareil. Ainsi, les bibliothèques Arduino fonctionneront sur tout appareil prenant en charge le framework Arduino, à condition que l'appareil dispose du matériel spécifique requis par cette bibliothèque. Certaines bibliothèques, comme les bibliothèques WiFi de Seeed, sont spécifiques à certains matériels.

Les bibliothèques peuvent être installées globalement et compilées si nécessaire, ou dans un projet spécifique. Pour cet exercice, les bibliothèques seront installées dans le projet.

✅ Vous pouvez en apprendre davantage sur la gestion des bibliothèques et comment les trouver et les installer dans la [documentation des bibliothèques PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Tâche - installer les bibliothèques Arduino pour WiFi et MQTT

Installez les bibliothèques Arduino.

1. Ouvrez le projet de veilleuse dans VS Code.

1. Ajoutez ce qui suit à la fin du fichier `platformio.ini` :

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Cela importe les bibliothèques WiFi de Seeed. La syntaxe `@ <number>` fait référence à une version spécifique de la bibliothèque.

    > 💁 Vous pouvez supprimer le `@ <number>` pour toujours utiliser la dernière version des bibliothèques, mais il n'y a aucune garantie que les versions ultérieures fonctionneront avec le code ci-dessous. Le code ici a été testé avec cette version des bibliothèques.

    C'est tout ce que vous avez à faire pour ajouter les bibliothèques. La prochaine fois que PlatformIO construira le projet, il téléchargera le code source de ces bibliothèques et le compilera dans votre projet.

1. Ajoutez ce qui suit à `lib_deps` :

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Cela importe [PubSubClient](https://github.com/knolleary/pubsubclient), un client MQTT pour Arduino.

## Connexion au WiFi

Le Wio Terminal peut maintenant être connecté au WiFi.

### Tâche - se connecter au WiFi

Connectez le Wio Terminal au WiFi.

1. Créez un nouveau fichier dans le dossier `src` appelé `config.h`. Vous pouvez le faire en sélectionnant le dossier `src`, ou le fichier `main.cpp` à l'intérieur, et en cliquant sur le bouton **Nouveau fichier** dans l'explorateur. Ce bouton n'apparaît que lorsque votre curseur est sur l'explorateur.

    ![Le bouton nouveau fichier](../../../../../translated_images/fr/vscode-new-file-button.182702340fe6723c.webp)

1. Ajoutez le code suivant à ce fichier pour définir des constantes pour vos identifiants WiFi :

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Remplacez `<SSID>` par le SSID de votre WiFi. Remplacez `<PASSWORD>` par le mot de passe de votre WiFi.

1. Ouvrez le fichier `main.cpp`.

1. Ajoutez les directives `#include` suivantes en haut du fichier :

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Cela inclut les fichiers d'en-tête pour les bibliothèques que vous avez ajoutées précédemment, ainsi que le fichier d'en-tête de configuration. Ces fichiers d'en-tête sont nécessaires pour indiquer à PlatformIO d'intégrer le code des bibliothèques. Sans inclure explicitement ces fichiers d'en-tête, une partie du code ne sera pas compilée et vous obtiendrez des erreurs de compilation.

1. Ajoutez le code suivant au-dessus de la fonction `setup` :

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Ce code boucle tant que l'appareil n'est pas connecté au WiFi et tente de se connecter en utilisant le SSID et le mot de passe du fichier d'en-tête de configuration.

1. Ajoutez un appel à cette fonction à la fin de la fonction `setup`, après que les broches aient été configurées.

    ```cpp
    connectWiFi();
    ```

1. Téléversez ce code sur votre appareil pour vérifier que la connexion WiFi fonctionne. Vous devriez voir ceci dans le moniteur série.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Connexion à MQTT

Une fois le Wio Terminal connecté au WiFi, il peut se connecter au broker MQTT.

### Tâche - se connecter à MQTT

Connectez-vous au broker MQTT.

1. Ajoutez le code suivant à la fin du fichier `config.h` pour définir les détails de connexion au broker MQTT :

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Remplacez `<ID>` par un ID unique qui sera utilisé comme nom de ce client appareil, et plus tard pour les topics que cet appareil publiera et auxquels il s'abonnera. Le broker *test.mosquitto.org* est public et utilisé par de nombreuses personnes, y compris d'autres étudiants travaillant sur cet exercice. Avoir un nom de client MQTT et des noms de topics uniques garantit que votre code ne sera pas en conflit avec celui de quelqu'un d'autre. Vous aurez également besoin de cet ID lorsque vous créerez le code serveur plus tard dans cet exercice.

    > 💁 Vous pouvez utiliser un site web comme [GUIDGen](https://www.guidgen.com) pour générer un ID unique.

    Le `BROKER` est l'URL du broker MQTT.

    Le `CLIENT_NAME` est un nom unique pour ce client MQTT sur le broker.

1. Ouvrez le fichier `main.cpp` et ajoutez le code suivant sous la fonction `connectWiFi` et au-dessus de la fonction `setup` :

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Ce code crée un client WiFi en utilisant les bibliothèques WiFi du Wio Terminal et l'utilise pour créer un client MQTT.

1. Ajoutez ensuite ce qui suit sous ce code :

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Cette fonction teste la connexion au broker MQTT et se reconnecte si elle n'est pas établie. Elle boucle tant que la connexion n'est pas établie et tente de se connecter en utilisant le nom de client unique défini dans le fichier d'en-tête de configuration.

    Si la connexion échoue, elle réessaie après 5 secondes.

1. Ajoutez le code suivant sous la fonction `reconnectMQTTClient` :

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Ce code configure le broker MQTT pour le client, ainsi que le callback pour la réception des messages. Il tente ensuite de se connecter au broker.

1. Appelez la fonction `createMQTTClient` dans la fonction `setup` après la connexion au WiFi.

1. Remplacez l'intégralité de la fonction `loop` par ce qui suit :

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Ce code commence par se reconnecter au broker MQTT. Ces connexions peuvent être facilement interrompues, il est donc utile de vérifier régulièrement et de se reconnecter si nécessaire. Il appelle ensuite la méthode `loop` sur le client MQTT pour traiter les messages entrants sur le topic auquel il est abonné. Cette application est mono-thread, donc les messages ne peuvent pas être reçus sur un thread en arrière-plan, il faut donc allouer du temps sur le thread principal pour traiter les messages en attente sur la connexion réseau.

    Enfin, un délai de 2 secondes garantit que les niveaux de lumière ne sont pas envoyés trop fréquemment et réduit la consommation d'énergie de l'appareil.

1. Téléversez le code sur votre Wio Terminal et utilisez le Moniteur Série pour voir l'appareil se connecter au WiFi et à MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Vous avez réussi à connecter votre appareil à un broker MQTT.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.