<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-24T22:48:56+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "fr"
}
-->
# Connectez votre appareil IoT au cloud - Matériel IoT virtuel et Raspberry Pi

Dans cette partie de la leçon, vous allez connecter votre appareil IoT virtuel ou votre Raspberry Pi à votre IoT Hub, pour envoyer des télémétries et recevoir des commandes.

## Connectez votre appareil à IoT Hub

L'étape suivante consiste à connecter votre appareil à IoT Hub.

### Tâche - se connecter à IoT Hub

1. Ouvrez le dossier `soil-moisture-sensor` dans VS Code. Assurez-vous que l'environnement virtuel est actif dans le terminal si vous utilisez un appareil IoT virtuel.

1. Installez quelques packages Pip supplémentaires :

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` est une bibliothèque permettant de communiquer avec votre IoT Hub.

1. Ajoutez les imports suivants en haut du fichier `app.py`, sous les imports existants :

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Ce code importe le SDK pour communiquer avec votre IoT Hub.

1. Supprimez la ligne `import paho.mqtt.client as mqtt`, car cette bibliothèque n'est plus nécessaire. Supprimez tout le code MQTT, y compris les noms des topics, tout le code qui utilise `mqtt_client` et la fonction `handle_command`. Conservez la boucle `while True:`, mais supprimez la ligne `mqtt_client.publish` de cette boucle.

1. Ajoutez le code suivant sous les déclarations d'importation :

    ```python
    connection_string = "<connection string>"
    ```

    Remplacez `<connection string>` par la chaîne de connexion que vous avez récupérée pour l'appareil plus tôt dans cette leçon.

    > 💁 Ce n'est pas une bonne pratique. Les chaînes de connexion ne devraient jamais être stockées dans le code source, car elles pourraient être ajoutées au contrôle de version et découvertes par n'importe qui. Nous faisons cela ici pour simplifier. Idéalement, vous devriez utiliser quelque chose comme une variable d'environnement et un outil comme [`python-dotenv`](https://pypi.org/project/python-dotenv/). Vous en apprendrez davantage à ce sujet dans une leçon à venir.

1. Sous ce code, ajoutez ce qui suit pour créer un objet client d'appareil capable de communiquer avec IoT Hub, et connectez-le :

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Exécutez ce code. Vous verrez votre appareil se connecter.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Envoyer des télémétries

Maintenant que votre appareil est connecté, vous pouvez envoyer des télémétries à IoT Hub au lieu du broker MQTT.

### Tâche - envoyer des télémétries

1. Ajoutez le code suivant dans la boucle `while True`, juste avant la pause (`sleep`) :

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Ce code crée un `Message` IoT Hub contenant la mesure d'humidité du sol sous forme de chaîne JSON, puis l'envoie à IoT Hub comme un message de l'appareil vers le cloud.

## Gérer les commandes

Votre appareil doit gérer une commande envoyée par le code serveur pour contrôler le relais. Cela est envoyé sous forme de requête de méthode directe.

### Tâche - gérer une requête de méthode directe

1. Ajoutez le code suivant avant la boucle `while True` :

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Cela définit une méthode, `handle_method_request`, qui sera appelée lorsqu'une méthode directe sera invoquée par IoT Hub. Chaque méthode directe a un nom, et ce code attend une méthode appelée `relay_on` pour allumer le relais, et `relay_off` pour l'éteindre.

    > 💁 Cela pourrait également être implémenté dans une seule requête de méthode directe, en passant l'état souhaité du relais dans une charge utile qui peut être transmise avec la requête de méthode et disponible à partir de l'objet `request`.

1. Les méthodes directes nécessitent une réponse pour informer le code appelant qu'elles ont été traitées. Ajoutez le code suivant à la fin de la fonction `handle_method_request` pour créer une réponse à la requête :

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Ce code envoie une réponse à la requête de méthode directe avec un code de statut HTTP 200, et la renvoie à IoT Hub.

1. Ajoutez le code suivant sous cette définition de fonction :

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Ce code indique au client IoT Hub d'appeler la fonction `handle_method_request` lorsqu'une méthode directe est invoquée.

> 💁 Vous pouvez trouver ce code dans le dossier [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) ou [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Votre programme de capteur d'humidité du sol est connecté à votre IoT Hub !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.