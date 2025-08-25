<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-24T23:10:04+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "fr"
}
-->
# Contrôlez votre veilleuse via Internet - Matériel IoT virtuel et Raspberry Pi

L'appareil IoT doit être programmé pour communiquer avec *test.mosquitto.org* en utilisant MQTT afin d'envoyer des valeurs de télémétrie avec la lecture du capteur de lumière, et recevoir des commandes pour contrôler la LED.

Dans cette partie de la leçon, vous allez connecter votre Raspberry Pi ou appareil IoT virtuel à un broker MQTT.

## Installer le package client MQTT

Pour communiquer avec le broker MQTT, vous devez installer une bibliothèque MQTT via un package pip, soit sur votre Pi, soit dans votre environnement virtuel si vous utilisez un appareil virtuel.

### Tâche

Installez le package pip

1. Ouvrez le projet de veilleuse dans VS Code.

1. Si vous utilisez un appareil IoT virtuel, assurez-vous que le terminal exécute l'environnement virtuel. Si vous utilisez un Raspberry Pi, vous n'utiliserez pas d'environnement virtuel.

1. Exécutez la commande suivante pour installer le package pip MQTT :

    ```sh
    pip3 install paho-mqtt
    ```

## Programmer l'appareil

L'appareil est prêt à être programmé.

### Tâche

Écrivez le code de l'appareil.

1. Ajoutez l'import suivant en haut du fichier `app.py` :

    ```python
    import paho.mqtt.client as mqtt
    ```

    La bibliothèque `paho.mqtt.client` permet à votre application de communiquer via MQTT.

1. Ajoutez le code suivant après les définitions du capteur de lumière et de la LED :

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Remplacez `<ID>` par un identifiant unique qui sera utilisé comme nom de ce client appareil, et plus tard pour les topics que cet appareil publie et auxquels il s'abonne. Le broker *test.mosquitto.org* est public et utilisé par de nombreuses personnes, y compris d'autres étudiants travaillant sur cet exercice. Avoir un nom de client MQTT et des noms de topics uniques garantit que votre code ne sera pas en conflit avec celui des autres. Vous aurez également besoin de cet identifiant lorsque vous créerez le code serveur plus tard dans cet exercice.

    > 💁 Vous pouvez utiliser un site web comme [GUIDGen](https://www.guidgen.com) pour générer un identifiant unique.

    Le `client_name` est un nom unique pour ce client MQTT sur le broker.

1. Ajoutez le code suivant sous ce nouveau code pour créer un objet client MQTT et se connecter au broker MQTT :

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Ce code crée l'objet client, se connecte au broker MQTT public, et démarre une boucle de traitement qui s'exécute dans un thread en arrière-plan, écoutant les messages sur tous les topics abonnés.

1. Exécutez le code de la même manière que vous avez exécuté le code de la partie précédente de l'exercice. Si vous utilisez un appareil IoT virtuel, assurez-vous que l'application CounterFit est en cours d'exécution et que le capteur de lumière et la LED ont été créés sur les broches correctes.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) ou le dossier [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Vous avez connecté avec succès votre appareil à un broker MQTT.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.