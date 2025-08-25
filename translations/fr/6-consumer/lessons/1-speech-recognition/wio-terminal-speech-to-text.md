<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-25T00:28:30+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "fr"
}
-->
# Reconnaissance vocale - Wio Terminal

Dans cette partie de la leçon, vous allez écrire du code pour convertir la parole captée dans l'audio en texte à l'aide du service de reconnaissance vocale.

## Envoyer l'audio au service de reconnaissance vocale

L'audio peut être envoyé au service de reconnaissance vocale en utilisant l'API REST. Pour utiliser ce service, vous devez d'abord demander un jeton d'accès, puis utiliser ce jeton pour accéder à l'API REST. Ces jetons d'accès expirent après 10 minutes, donc votre code doit les demander régulièrement pour s'assurer qu'ils sont toujours à jour.

### Tâche - Obtenir un jeton d'accès

1. Ouvrez le projet `smart-timer` s'il n'est pas déjà ouvert.

1. Ajoutez les dépendances de bibliothèque suivantes au fichier `platformio.ini` pour accéder au WiFi et gérer le JSON :

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Ajoutez le code suivant au fichier d'en-tête `config.h` :

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Remplacez `<SSID>` et `<PASSWORD>` par les valeurs correspondantes pour votre WiFi.

    Remplacez `<API_KEY>` par la clé API de votre ressource de service de reconnaissance vocale. Remplacez `<LOCATION>` par l'emplacement que vous avez utilisé lors de la création de la ressource de service de reconnaissance vocale.

    Remplacez `<LANGUAGE>` par le nom de la langue que vous utiliserez, par exemple `en-GB` pour l'anglais ou `zn-HK` pour le cantonais. Vous pouvez trouver une liste des langues prises en charge et leurs noms de paramètres régionaux dans la [documentation sur le support des langues et des voix sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    La constante `TOKEN_URL` est l'URL de l'émetteur de jetons sans l'emplacement. Cet URL sera combiné avec l'emplacement plus tard pour obtenir l'URL complète.

1. Comme pour la connexion à Custom Vision, vous devrez utiliser une connexion HTTPS pour vous connecter au service d'émission de jetons. Ajoutez le code suivant à la fin de `config.h` :

    ```cpp
    const char *TOKEN_CERTIFICATE =
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

    Il s'agit du même certificat que vous avez utilisé pour vous connecter à Custom Vision.

1. Ajoutez une inclusion pour le fichier d'en-tête WiFi et le fichier d'en-tête de configuration en haut du fichier `main.cpp` :

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Ajoutez du code pour vous connecter au WiFi dans `main.cpp` avant la fonction `setup` :

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

1. Appelez cette fonction depuis la fonction `setup` après que la connexion série a été établie :

    ```cpp
    connectWiFi();
    ```

1. Créez un nouveau fichier d'en-tête dans le dossier `src` appelé `speech_to_text.h`. Dans ce fichier d'en-tête, ajoutez le code suivant :

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    Cela inclut certains fichiers d'en-tête nécessaires pour une connexion HTTP, la configuration et le fichier d'en-tête `mic.h`, et définit une classe appelée `SpeechToText`, avant de déclarer une instance de cette classe qui pourra être utilisée plus tard.

1. Ajoutez les 2 champs suivants à la section `private` de cette classe :

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    Le `_token_client` est un client WiFi qui utilise HTTPS et sera utilisé pour obtenir le jeton d'accès. Ce jeton sera ensuite stocké dans `_access_token`.

1. Ajoutez la méthode suivante à la section `private` :

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    Ce code construit l'URL pour l'API de l'émetteur de jetons en utilisant l'emplacement de la ressource de reconnaissance vocale. Il crée ensuite un `HTTPClient` pour effectuer la requête web, en le configurant pour utiliser le client WiFi avec le certificat des points de terminaison du jeton. Il définit la clé API comme en-tête pour l'appel. Il effectue ensuite une requête POST pour obtenir le certificat, en réessayant en cas d'erreurs. Enfin, le jeton d'accès est retourné.

1. Dans la section `public`, ajoutez une méthode pour obtenir le jeton d'accès. Cela sera nécessaire dans les leçons suivantes pour convertir le texte en parole.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Dans la section `public`, ajoutez une méthode `init` qui configure le client de jetons :

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Cela configure le certificat sur le client WiFi, puis obtient le jeton d'accès.

1. Dans `main.cpp`, ajoutez ce nouveau fichier d'en-tête aux directives d'inclusion :

    ```cpp
    #include "speech_to_text.h"
    ```

1. Initialisez la classe `SpeechToText` à la fin de la fonction `setup`, après l'appel à `mic.init` mais avant que `Ready` ne soit écrit dans le moniteur série :

    ```cpp
    speechToText.init();
    ```

### Tâche - Lire l'audio depuis la mémoire flash

1. Dans une partie précédente de cette leçon, l'audio a été enregistré dans la mémoire flash. Cet audio devra être envoyé à l'API REST des services de reconnaissance vocale, il doit donc être lu depuis la mémoire flash. Il ne peut pas être chargé dans un tampon en mémoire car il serait trop volumineux. La classe `HTTPClient` qui effectue les appels REST peut diffuser des données en utilisant un flux Arduino - une classe qui peut charger des données en petits morceaux, en envoyant les morceaux un par un dans la requête. Chaque fois que vous appelez `read` sur un flux, il retourne le prochain bloc de données. Un flux Arduino peut être créé pour lire depuis la mémoire flash. Créez un nouveau fichier appelé `flash_stream.h` dans le dossier `src`, et ajoutez-y le code suivant :

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    Cela déclare la classe `FlashStream`, dérivée de la classe `Stream` d'Arduino. Il s'agit d'une classe abstraite - les classes dérivées doivent implémenter quelques méthodes avant que la classe puisse être instanciée, et ces méthodes sont définies dans cette classe.

    ✅ En savoir plus sur les flux Arduino dans la [documentation Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Ajoutez les champs suivants à la section `private` :

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Cela définit un tampon temporaire pour stocker les données lues depuis la mémoire flash, ainsi que des champs pour stocker la position actuelle lors de la lecture depuis le tampon, l'adresse actuelle pour lire depuis la mémoire flash, et le périphérique de mémoire flash.

1. Dans la section `private`, ajoutez la méthode suivante :

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Ce code lit depuis la mémoire flash à l'adresse actuelle et stocke les données dans un tampon. Il incrémente ensuite l'adresse, de sorte que le prochain appel lise le prochain bloc de mémoire. Le tampon est dimensionné en fonction du plus grand morceau que le `HTTPClient` enverra à l'API REST en une seule fois.

    > 💁 Effacer la mémoire flash doit être fait en utilisant la taille de grain, mais la lecture n'a pas cette contrainte.

1. Dans la section `public` de cette classe, ajoutez un constructeur :

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Ce constructeur configure tous les champs pour commencer à lire depuis le début du bloc de mémoire flash, et charge le premier morceau de données dans le tampon.

1. Implémentez la méthode `write`. Ce flux ne fera que lire des données, donc cette méthode peut ne rien faire et retourner 0 :

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implémentez la méthode `peek`. Cela retourne les données à la position actuelle sans avancer dans le flux. Appeler `peek` plusieurs fois retournera toujours les mêmes données tant qu'aucune donnée n'est lue depuis le flux.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implémentez la fonction `available`. Cela retourne combien d'octets peuvent être lus depuis le flux, ou -1 si le flux est terminé. Pour cette classe, le maximum disponible ne dépassera jamais la taille de morceau du `HTTPClient`. Lorsque ce flux est utilisé dans le client HTTP, il appelle cette fonction pour voir combien de données sont disponibles, puis demande cette quantité de données à envoyer à l'API REST. Nous ne voulons pas que chaque morceau dépasse la taille de morceau du client HTTP, donc si plus que cela est disponible, la taille de morceau est retournée. Si moins, alors ce qui est disponible est retourné. Une fois que toutes les données ont été diffusées, -1 est retourné.

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. Implémentez la méthode `read` pour retourner le prochain octet depuis le tampon, en incrémentant la position. Si la position dépasse la taille du tampon, il remplit le tampon avec le prochain bloc depuis la mémoire flash et réinitialise la position.

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. Dans le fichier d'en-tête `speech_to_text.h`, ajoutez une directive d'inclusion pour ce nouveau fichier d'en-tête :

    ```cpp
    #include "flash_stream.h"
    ```

### Tâche - Convertir la parole en texte

1. La parole peut être convertie en texte en envoyant l'audio au service de reconnaissance vocale via une API REST. Cette API REST a un certificat différent de celui de l'émetteur de jetons, donc ajoutez le code suivant au fichier `config.h` pour définir ce certificat :

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Ajoutez une constante à ce fichier pour l'URL de reconnaissance vocale sans l'emplacement. Cela sera combiné avec l'emplacement et la langue plus tard pour obtenir l'URL complète.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Dans le fichier d'en-tête `speech_to_text.h`, dans la section `private` de la classe `SpeechToText`, définissez un champ pour un client WiFi utilisant le certificat de reconnaissance vocale :

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Dans la méthode `init`, configurez le certificat sur ce client WiFi :

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Ajoutez le code suivant à la section `public` de la classe `SpeechToText` pour définir une méthode permettant de convertir la parole en texte :

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Ajoutez le code suivant à cette méthode pour créer un client HTTP utilisant le client WiFi configuré avec le certificat de reconnaissance vocale, et en utilisant l'URL de reconnaissance vocale définie avec l'emplacement et la langue :

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Certains en-têtes doivent être définis sur la connexion :

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Cela définit des en-têtes pour l'autorisation en utilisant le jeton d'accès, le format audio en utilisant la fréquence d'échantillonnage, et indique que le client attend le résultat au format JSON.

1. Après cela, ajoutez le code suivant pour effectuer l'appel à l'API REST :

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Cela crée un `FlashStream` et l'utilise pour diffuser des données vers l'API REST.

1. En dessous, ajoutez le code suivant :

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Ce code vérifie le code de réponse.

    Si c'est 200, le code pour le succès, alors le résultat est récupéré, décodé depuis le JSON, et la propriété `DisplayText` est définie dans la variable `text`. C'est la propriété où la version texte de la parole est retournée.

    Si le code de réponse est 401, alors le jeton d'accès a expiré (ces jetons ne durent que 10 minutes). Un nouveau jeton d'accès est demandé, et l'appel est refait.

    Sinon, une erreur est envoyée au moniteur série, et le `text` reste vide.

1. Ajoutez le code suivant à la fin de cette méthode pour fermer le client HTTP et retourner le texte :

    ```cpp
    httpClient.end();

    return text;
    ```

1. Dans `main.cpp`, appelez cette nouvelle méthode `convertSpeechToText` dans la fonction `processAudio`, puis affichez la parole dans le moniteur série :

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Compilez ce code, téléversez-le sur votre Wio Terminal et testez-le via le moniteur série. Une fois que vous voyez `Ready` dans le moniteur série, appuyez sur le bouton C (celui sur le côté gauche, le plus proche de l'interrupteur d'alimentation), et parlez. 4 secondes d'audio seront capturées, puis converties en texte.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Votre programme de reconnaissance vocale a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.