<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-24T22:50:23+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "fr"
}
-->
# Connectez votre appareil IoT au cloud - Wio Terminal

Dans cette partie de la leçon, vous allez connecter votre Wio Terminal à votre IoT Hub pour envoyer des données de télémétrie et recevoir des commandes.

## Connectez votre appareil à IoT Hub

L'étape suivante consiste à connecter votre appareil à IoT Hub.

### Tâche - se connecter à IoT Hub

1. Ouvrez le projet `soil-moisture-sensor` dans VS Code.

1. Ouvrez le fichier `platformio.ini`. Supprimez la dépendance de la bibliothèque `knolleary/PubSubClient`. Cette bibliothèque était utilisée pour se connecter au broker MQTT public, mais elle n'est pas nécessaire pour se connecter à IoT Hub.

1. Ajoutez les dépendances de bibliothèque suivantes :

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    La bibliothèque `Seeed Arduino RTC` fournit du code pour interagir avec une horloge temps réel dans le Wio Terminal, utilisée pour suivre l'heure. Les autres bibliothèques permettent à votre appareil IoT de se connecter à IoT Hub.

1. Ajoutez ce qui suit en bas du fichier `platformio.ini` :

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Cela définit un drapeau de compilation nécessaire lors de la compilation du code Arduino IoT Hub.

1. Ouvrez le fichier d'en-tête `config.h`. Supprimez tous les paramètres MQTT et ajoutez la constante suivante pour la chaîne de connexion de l'appareil :

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Remplacez `<connection string>` par la chaîne de connexion de votre appareil que vous avez copiée précédemment.

1. La connexion à IoT Hub utilise un jeton basé sur le temps. Cela signifie que l'appareil IoT doit connaître l'heure actuelle. Contrairement aux systèmes d'exploitation comme Windows, macOS ou Linux, les microcontrôleurs ne synchronisent pas automatiquement l'heure actuelle via Internet. Vous devrez donc ajouter du code pour obtenir l'heure actuelle à partir d'un serveur [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Une fois l'heure récupérée, elle peut être stockée dans une horloge temps réel du Wio Terminal, permettant de demander l'heure correcte ultérieurement, à condition que l'appareil ne perde pas d'alimentation. Ajoutez un nouveau fichier appelé `ntp.h` avec le code suivant :

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    Les détails de ce code sont hors du cadre de cette leçon. Il définit une fonction appelée `initTime` qui obtient l'heure actuelle d'un serveur NTP et l'utilise pour régler l'horloge du Wio Terminal.

1. Ouvrez le fichier `main.cpp` et supprimez tout le code MQTT, y compris le fichier d'en-tête `PubSubClient.h`, la déclaration de la variable `PubSubClient`, les méthodes `reconnectMQTTClient` et `createMQTTClient`, ainsi que tous les appels à ces variables et méthodes. Ce fichier ne doit contenir que du code pour se connecter au WiFi, obtenir l'humidité du sol et créer un document JSON avec ces données.

1. Ajoutez les directives `#include` suivantes en haut du fichier `main.cpp` pour inclure les fichiers d'en-tête des bibliothèques IoT Hub et pour régler l'heure :

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Ajoutez l'appel suivant à la fin de la fonction `setup` pour régler l'heure actuelle :

    ```cpp
    initTime();
    ```

1. Ajoutez la déclaration de variable suivante en haut du fichier, juste en dessous des directives d'inclusion :

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Cela déclare un `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, un handle pour une connexion à IoT Hub.

1. En dessous, ajoutez le code suivant :

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Cela déclare une fonction de rappel qui sera appelée lorsque la connexion à IoT Hub change de statut, comme lors de la connexion ou de la déconnexion. Le statut est envoyé au port série.

1. En dessous, ajoutez une fonction pour se connecter à IoT Hub :

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Ce code initialise le code de la bibliothèque IoT Hub, puis crée une connexion en utilisant la chaîne de connexion dans le fichier d'en-tête `config.h`. Cette connexion est basée sur MQTT. Si la connexion échoue, cela est envoyé au port série - si vous voyez cela dans la sortie, vérifiez la chaîne de connexion. Enfin, la fonction de rappel de statut de connexion est configurée.

1. Appelez cette fonction dans la fonction `setup` sous l'appel à `initTime` :

    ```cpp
    connectIoTHub();
    ```

1. Comme avec le client MQTT, ce code fonctionne sur un seul thread et nécessite du temps pour traiter les messages envoyés par le hub et au hub. Ajoutez ce qui suit en haut de la fonction `loop` pour le faire :

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Compilez et téléchargez ce code. Vous verrez la connexion dans le moniteur série :

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Dans la sortie, vous pouvez voir l'heure NTP récupérée, suivie de la connexion du client de l'appareil. La connexion peut prendre quelques secondes, donc vous pourriez voir l'humidité du sol dans la sortie pendant que l'appareil se connecte.

    > 💁 Vous pouvez convertir l'heure UNIX du NTP en une version plus lisible en utilisant un site web comme [unixtimestamp.com](https://www.unixtimestamp.com)

## Envoyer des données de télémétrie

Maintenant que votre appareil est connecté, vous pouvez envoyer des données de télémétrie à IoT Hub au lieu du broker MQTT.

### Tâche - envoyer des données de télémétrie

1. Ajoutez la fonction suivante au-dessus de la fonction `setup` :

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Ce code crée un message IoT Hub à partir d'une chaîne passée en paramètre, l'envoie au hub, puis nettoie l'objet message.

1. Appelez ce code dans la fonction `loop`, juste après la ligne où la télémétrie est envoyée au port série :

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Gérer les commandes

Votre appareil doit gérer une commande provenant du code serveur pour contrôler le relais. Cela est envoyé sous forme de requête de méthode directe.

### Tâche - gérer une requête de méthode directe

1. Ajoutez le code suivant avant la fonction `connectIoTHub` :

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Ce code définit une méthode de rappel que la bibliothèque IoT Hub peut appeler lorsqu'elle reçoit une requête de méthode directe. La méthode demandée est envoyée dans le paramètre `method_name`. Cette fonction imprime la méthode appelée sur le port série, puis active ou désactive le relais en fonction du nom de la méthode.

    > 💁 Cela pourrait également être implémenté dans une seule requête de méthode directe, en passant l'état souhaité du relais dans une charge utile qui peut être transmise avec la requête de méthode et disponible à partir du paramètre `payload`.

1. Ajoutez le code suivant à la fin de la fonction `directMethodCallback` :

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Les requêtes de méthode directe nécessitent une réponse, et la réponse est en deux parties - une réponse sous forme de texte et un code de retour. Ce code créera un résultat sous forme du document JSON suivant :

    ```JSON
    {
        "Result": ""
    }
    ```

    Cela est ensuite copié dans le paramètre `response`, et la taille de cette réponse est définie dans le paramètre `response_size`. Ce code retourne ensuite `IOTHUB_CLIENT_OK` pour indiquer que la méthode a été correctement gérée.

1. Configurez le rappel en ajoutant ce qui suit à la fin de la fonction `connectIoTHub` :

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. La fonction `loop` appellera la fonction `IoTHubDeviceClient_LL_DoWork` pour traiter les événements envoyés par IoT Hub. Cela n'est appelé que toutes les 10 secondes en raison du `delay`, ce qui signifie que les méthodes directes ne sont traitées que toutes les 10 secondes. Pour rendre cela plus efficace, le délai de 10 secondes peut être implémenté sous forme de nombreux délais plus courts, appelant `IoTHubDeviceClient_LL_DoWork` à chaque fois. Pour ce faire, ajoutez le code suivant au-dessus de la fonction `loop` :

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Ce code bouclera de manière répétée, appelant `IoTHubDeviceClient_LL_DoWork` et retardant de 100 ms à chaque fois. Il le fera autant de fois que nécessaire pour retarder pendant le temps donné dans le paramètre `delay_time`. Cela signifie que l'appareil attend au maximum 100 ms pour traiter les requêtes de méthode directe.

1. Dans la fonction `loop`, supprimez l'appel à `IoTHubDeviceClient_LL_DoWork`, et remplacez l'appel `delay(10000)` par ce qui suit pour appeler cette nouvelle fonction :

    ```cpp
    work_delay(10000);
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Votre programme de capteur d'humidité du sol est connecté à votre IoT Hub !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.