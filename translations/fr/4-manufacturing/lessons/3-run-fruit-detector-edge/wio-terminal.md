<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-24T21:46:58+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "fr"
}
-->
# Classifier une image à l'aide d'un classificateur d'images basé sur IoT Edge - Wio Terminal

Dans cette partie de la leçon, vous utiliserez le classificateur d'images fonctionnant sur l'appareil IoT Edge.

## Utiliser le classificateur IoT Edge

L'appareil IoT peut être redirigé pour utiliser le classificateur d'images IoT Edge. L'URL du classificateur d'images est `http://<adresse IP ou nom>/image`, en remplaçant `<adresse IP ou nom>` par l'adresse IP ou le nom d'hôte de l'ordinateur exécutant IoT Edge.

### Tâche - utiliser le classificateur IoT Edge

1. Ouvrez le projet de l'application `fruit-quality-detector` s'il n'est pas déjà ouvert.

1. Le classificateur d'images fonctionne comme une API REST utilisant HTTP, et non HTTPS, donc l'appel doit utiliser un client WiFi compatible uniquement avec les appels HTTP. Cela signifie que le certificat n'est pas nécessaire. Supprimez le `CERTIFICATE` du fichier `config.h`.

1. L'URL de prédiction dans le fichier `config.h` doit être mise à jour avec la nouvelle URL. Vous pouvez également supprimer le `PREDICTION_KEY`, car il n'est pas nécessaire.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Remplacez `<URL>` par l'URL de votre classificateur.

1. Dans `main.cpp`, modifiez la directive d'inclusion pour le WiFi Client Secure afin d'importer la version standard HTTP :

    ```cpp
    #include <WiFiClient.h>
    ```

1. Changez la déclaration de `WiFiClient` pour utiliser la version HTTP :

    ```cpp
    WiFiClient client;
    ```

1. Sélectionnez la ligne qui définit le certificat sur le client WiFi. Supprimez la ligne `client.setCACert(CERTIFICATE);` de la fonction `connectWiFi`.

1. Dans la fonction `classifyImage`, supprimez la ligne `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` qui définit la clé de prédiction dans l'en-tête.

1. Téléversez et exécutez votre code. Pointez la caméra vers un fruit et appuyez sur le bouton C. Vous verrez le résultat dans le moniteur série :

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Votre programme de classification de la qualité des fruits a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.