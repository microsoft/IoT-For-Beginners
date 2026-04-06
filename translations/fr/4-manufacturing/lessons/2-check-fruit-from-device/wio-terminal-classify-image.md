# Classifier une image - Wio Terminal

Dans cette partie de la leçon, vous allez envoyer l'image capturée par la caméra au service Custom Vision pour la classifier.

## Classifier une image

Le service Custom Vision dispose d'une API REST que vous pouvez appeler depuis le Wio Terminal pour classifier des images. Cette API REST est accessible via une connexion HTTPS - une connexion HTTP sécurisée.

Lors de l'interaction avec des points de terminaison HTTPS, le code client doit demander le certificat de clé publique au serveur auquel il accède, et l'utiliser pour chiffrer le trafic qu'il envoie. Votre navigateur web fait cela automatiquement, mais les microcontrôleurs ne le font pas. Vous devrez demander ce certificat manuellement et l'utiliser pour établir une connexion sécurisée avec l'API REST. Ces certificats ne changent pas, donc une fois que vous avez un certificat, il peut être codé en dur dans votre application.

Ces certificats contiennent des clés publiques et n'ont pas besoin d'être gardés secrets. Vous pouvez les utiliser dans votre code source et les partager publiquement sur des plateformes comme GitHub.

### Tâche - configurer un client SSL

1. Ouvrez le projet de l'application `fruit-quality-detector` s'il n'est pas déjà ouvert.

1. Ouvrez le fichier d'en-tête `config.h` et ajoutez ce qui suit :

    ```cpp
    const char *CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    Il s'agit du *certificat Microsoft Azure DigiCert Global Root G2* - c'est l'un des certificats utilisés par de nombreux services Azure dans le monde.

    > 💁 Pour vérifier qu'il s'agit bien du certificat à utiliser, exécutez la commande suivante sur macOS ou Linux. Si vous utilisez Windows, vous pouvez exécuter cette commande en utilisant le [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) :
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > La sortie affichera le certificat DigiCert Global Root G2.

1. Ouvrez `main.cpp` et ajoutez la directive include suivante :

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Sous les directives include, déclarez une instance de `WifiClientSecure` :

    ```cpp
    WiFiClientSecure client;
    ```

    Cette classe contient le code pour communiquer avec des points de terminaison web via HTTPS.

1. Dans la méthode `connectWiFi`, configurez le WiFiClientSecure pour utiliser le certificat DigiCert Global Root G2 :

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Tâche - classifier une image

1. Ajoutez la ligne suivante à la liste `lib_deps` dans le fichier `platformio.ini` :

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Cela importe [ArduinoJson](https://arduinojson.org), une bibliothèque JSON pour Arduino, qui sera utilisée pour décoder la réponse JSON de l'API REST.

1. Dans `config.h`, ajoutez des constantes pour l'URL de prédiction et la clé du service Custom Vision :

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Remplacez `<PREDICTION_URL>` par l'URL de prédiction de Custom Vision. Remplacez `<PREDICTION_KEY>` par la clé de prédiction.

1. Dans `main.cpp`, ajoutez une directive include pour la bibliothèque ArduinoJson :

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Ajoutez la fonction suivante à `main.cpp`, au-dessus de la fonction `buttonPressed`.

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    Ce code commence par déclarer un `HTTPClient` - une classe contenant des méthodes pour interagir avec des API REST. Il connecte ensuite le client à l'URL de prédiction en utilisant l'instance `WiFiClientSecure` configurée avec la clé publique Azure.

    Une fois connecté, il envoie des en-têtes - des informations sur la requête à venir qui sera effectuée contre l'API REST. L'en-tête `Content-Type` indique que l'appel API enverra des données binaires brutes, et l'en-tête `Prediction-Key` transmet la clé de prédiction Custom Vision.

    Ensuite, une requête POST est effectuée sur le client HTTP, téléchargeant un tableau d'octets. Celui-ci contiendra l'image JPEG capturée par la caméra lorsque cette fonction est appelée.

    > 💁 Les requêtes POST sont destinées à envoyer des données et à obtenir une réponse. Il existe d'autres types de requêtes, comme les requêtes GET, qui récupèrent des données. Les requêtes GET sont utilisées par votre navigateur web pour charger des pages web.

    La requête POST retourne un code de statut de réponse. Ce sont des valeurs bien définies, où 200 signifie **OK** - la requête POST a réussi.

    > 💁 Vous pouvez consulter tous les codes de statut de réponse sur la [page Liste des codes de statut HTTP sur Wikipédia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Si un 200 est retourné, le résultat est lu depuis le client HTTP. Il s'agit d'une réponse textuelle de l'API REST contenant les résultats de la prédiction sous forme de document JSON. Le JSON a le format suivant :

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    La partie importante ici est le tableau `predictions`. Celui-ci contient les prédictions, avec une entrée pour chaque étiquette contenant le nom de l'étiquette et la probabilité. Les probabilités retournées sont des nombres à virgule flottante entre 0 et 1, où 0 correspond à une probabilité de 0 % et 1 à une probabilité de 100 %.

    > 💁 Les classificateurs d'images retournent les pourcentages pour toutes les étiquettes utilisées. Chaque étiquette aura une probabilité que l'image corresponde à cette étiquette.

    Ce JSON est décodé, et les probabilités pour chaque étiquette sont envoyées au moniteur série.

1. Dans la fonction `buttonPressed`, remplacez le code qui enregistre sur la carte SD par un appel à `classifyImage`, ou ajoutez-le après l'enregistrement de l'image, mais **avant** que le tampon ne soit supprimé :

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Si vous remplacez le code qui enregistre sur la carte SD, vous pouvez nettoyer votre code en supprimant les fonctions `setupSDCard` et `saveToSDCard`.

1. Téléversez et exécutez votre code. Pointez la caméra vers un fruit et appuyez sur le bouton C. Vous verrez la sortie dans le moniteur série :

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Vous pourrez voir l'image capturée et ces valeurs dans l'onglet **Predictions** de Custom Vision.

    ![Une banane dans Custom Vision prédite mûre à 56,8 % et non mûre à 43,1 %](../../../../../translated_images/fr/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Vous pouvez trouver ce code dans le dossier [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Votre programme de classification de la qualité des fruits est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous ne sommes pas responsables des malentendus ou des interprétations erronées résultant de l'utilisation de cette traduction.