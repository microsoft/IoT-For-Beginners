<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-24T22:57:30+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "fr"
}
-->
# Utiliser le certificat X.509 dans le code de votre appareil - Matériel IoT virtuel et Raspberry Pi

Dans cette partie de la leçon, vous allez connecter votre appareil IoT virtuel ou votre Raspberry Pi à votre IoT Hub en utilisant le certificat X.509.

## Connecter votre appareil à IoT Hub

L'étape suivante consiste à connecter votre appareil à IoT Hub en utilisant les certificats X.509.

### Tâche - se connecter à IoT Hub

1. Copiez les fichiers de clé et de certificat dans le dossier contenant le code de votre appareil IoT. Si vous utilisez un Raspberry Pi via VS Code Remote SSH et que vous avez créé les clés sur votre PC ou Mac, vous pouvez glisser-déposer les fichiers dans l'explorateur de VS Code pour les copier.

1. Ouvrez le fichier `app.py`.

1. Pour vous connecter en utilisant un certificat X.509, vous aurez besoin du nom d'hôte de l'IoT Hub et du certificat X.509. Commencez par créer une variable contenant le nom d'hôte en ajoutant le code suivant avant la création du client de l'appareil :

    ```python
    host_name = "<host_name>"
    ```

    Remplacez `<host_name>` par le nom d'hôte de votre IoT Hub. Vous pouvez le trouver dans la section `HostName` de la `connection_string`. Ce sera le nom de votre IoT Hub, se terminant par `.azure-devices.net`.

1. En dessous, déclarez une variable avec l'ID de l'appareil :

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Vous aurez besoin d'une instance de la classe `X509` contenant les fichiers X.509. Ajoutez `X509` à la liste des classes importées depuis le module `azure.iot.device` :

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Créez une instance de la classe `X509` en utilisant vos fichiers de certificat et de clé en ajoutant ce code sous la déclaration de `host_name` :

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Cela créera la classe `X509` en utilisant les fichiers `soil-moisture-sensor-x509-cert.pem` et `soil-moisture-sensor-x509-key.pem` créés précédemment.

1. Remplacez la ligne de code qui crée le `device_client` à partir d'une chaîne de connexion par ce qui suit :

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Cela permettra de se connecter en utilisant le certificat X.509 au lieu d'une chaîne de connexion.

1. Supprimez la ligne contenant la variable `connection_string`.

1. Exécutez votre code. Surveillez les messages envoyés à IoT Hub et envoyez des requêtes de méthode directe comme auparavant. Vous verrez l'appareil se connecter et envoyer des relevés d'humidité du sol, ainsi que recevoir des requêtes de méthode directe.

> 💁 Vous pouvez trouver ce code dans le dossier [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) ou [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Votre programme de capteur d'humidité du sol est connecté à votre IoT Hub en utilisant un certificat X.509 !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.