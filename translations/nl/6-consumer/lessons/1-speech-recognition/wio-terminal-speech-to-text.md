<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T22:39:53+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "nl"
}
-->
# Spraak naar tekst - Wio Terminal

In dit deel van de les schrijf je code om spraak in de opgenomen audio om te zetten naar tekst met behulp van de spraakservice.

## Verstuur de audio naar de spraakservice

De audio kan naar de spraakservice worden gestuurd via de REST API. Om de spraakservice te gebruiken, moet je eerst een toegangstoken aanvragen en dat token gebruiken om toegang te krijgen tot de REST API. Deze toegangstokens verlopen na 10 minuten, dus je code moet ze regelmatig aanvragen om ervoor te zorgen dat ze altijd up-to-date zijn.

### Taak - verkrijg een toegangstoken

1. Open het `smart-timer`-project als het nog niet geopend is.

1. Voeg de volgende bibliotheekafhankelijkheden toe aan het `platformio.ini`-bestand om toegang te krijgen tot WiFi en JSON te verwerken:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Voeg de volgende code toe aan het `config.h`-headerbestand:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Vervang `<SSID>` en `<PASSWORD>` door de relevante waarden voor je WiFi.

    Vervang `<API_KEY>` door de API-sleutel voor je spraakserviceresource. Vervang `<LOCATION>` door de locatie die je hebt gebruikt bij het aanmaken van de spraakserviceresource.

    Vervang `<LANGUAGE>` door de taalcode van de taal waarin je zult spreken, bijvoorbeeld `en-GB` voor Engels of `zn-HK` voor Kantonees. Je kunt een lijst met ondersteunde talen en hun taalcodes vinden in de [documentatie over taal- en stemondersteuning op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    De constante `TOKEN_URL` is de URL van de tokenuitgever zonder de locatie. Deze wordt later gecombineerd met de locatie om de volledige URL te verkrijgen.

1. Net zoals bij het verbinden met Custom Vision, moet je een HTTPS-verbinding gebruiken om verbinding te maken met de tokenuitgevende service. Voeg de volgende code toe aan het einde van `config.h`:

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

    Dit is hetzelfde certificaat dat je hebt gebruikt bij het verbinden met Custom Vision.

1. Voeg een include toe voor het WiFi-headerbestand en het config-headerbestand aan de bovenkant van het `main.cpp`-bestand:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Voeg code toe om verbinding te maken met WiFi in `main.cpp` boven de `setup`-functie:

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

1. Roep deze functie aan vanuit de `setup`-functie nadat de seriële verbinding is opgezet:

    ```cpp
    connectWiFi();
    ```

1. Maak een nieuw headerbestand in de `src`-map genaamd `speech_to_text.h`. Voeg in dit headerbestand de volgende code toe:

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

    Dit bevat enkele noodzakelijke headerbestanden voor een HTTP-verbinding, configuratie en het `mic.h`-headerbestand, en definieert een klasse genaamd `SpeechToText`, voordat een instantie van die klasse wordt gedeclareerd die later kan worden gebruikt.

1. Voeg de volgende 2 velden toe aan het `private`-gedeelte van deze klasse:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    De `_token_client` is een WiFi Client die HTTPS gebruikt en zal worden gebruikt om het toegangstoken te verkrijgen. Dit token wordt vervolgens opgeslagen in `_access_token`.

1. Voeg de volgende methode toe aan het `private`-gedeelte:

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

    Deze code bouwt de URL voor de tokenuitgever-API met behulp van de locatie van de spraakresource. Vervolgens maakt het een `HTTPClient` om de webaanvraag te doen, waarbij het wordt ingesteld om de WiFi-client te gebruiken die is geconfigureerd met het certificaat van de tokenendpoints. Het stelt de API-sleutel in als een header voor de oproep. Vervolgens wordt een POST-verzoek gedaan om het certificaat te verkrijgen, waarbij opnieuw wordt geprobeerd als er fouten optreden. Uiteindelijk wordt het toegangstoken geretourneerd.

1. Voeg aan het `public`-gedeelte een methode toe om het toegangstoken te verkrijgen. Dit zal nodig zijn in latere lessen om tekst om te zetten naar spraak.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Voeg aan het `public`-gedeelte een `init`-methode toe die de tokenclient instelt:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Dit stelt het certificaat in op de WiFi-client en verkrijgt vervolgens het toegangstoken.

1. Voeg in `main.cpp` dit nieuwe headerbestand toe aan de include-directieven:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Initialiseer de `SpeechToText`-klasse aan het einde van de `setup`-functie, na de `mic.init`-aanroep maar vóór `Ready` wordt geschreven naar de seriële monitor:

    ```cpp
    speechToText.init();
    ```

### Taak - lees audio uit flashgeheugen

1. In een eerder deel van deze les is de audio opgenomen in het flashgeheugen. Deze audio moet worden verzonden naar de REST API van de spraakservice, dus het moet worden gelezen uit het flashgeheugen. Het kan niet worden geladen in een in-memory buffer omdat het te groot zou zijn. De `HTTPClient`-klasse die REST-oproepen maakt, kan gegevens streamen met behulp van een Arduino Stream - een klasse die gegevens in kleine stukjes kan laden en de stukjes één voor één kan verzenden als onderdeel van het verzoek. Elke keer dat je `read` aanroept op een stream, retourneert het het volgende blok gegevens. Een Arduino-stream kan worden gemaakt die kan lezen uit het flashgeheugen. Maak een nieuw bestand genaamd `flash_stream.h` in de `src`-map en voeg de volgende code toe:

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

    Dit declareert de `FlashStream`-klasse, afgeleid van de Arduino `Stream`-klasse. Dit is een abstracte klasse - afgeleide klassen moeten een paar methoden implementeren voordat de klasse kan worden geïnstantieerd, en deze methoden worden gedefinieerd in deze klasse.

    ✅ Lees meer over Arduino Streams in de [Arduino Stream-documentatie](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Voeg de volgende velden toe aan het `private`-gedeelte:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Dit definieert een tijdelijke buffer om gegevens op te slaan die worden gelezen uit het flashgeheugen, samen met velden om de huidige positie bij te houden bij het lezen uit de buffer, het huidige adres om te lezen uit het flashgeheugen en het flashgeheugenapparaat.

1. Voeg in het `private`-gedeelte de volgende methode toe:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Deze code leest uit het flashgeheugen op het huidige adres en slaat de gegevens op in een buffer. Vervolgens wordt het adres verhoogd, zodat de volgende oproep het volgende blok geheugen leest. De buffer is afgestemd op de grootste chunk die de `HTTPClient` in één keer naar de REST API zal sturen.

    > 💁 Flashgeheugen wissen moet worden gedaan met de korrelgrootte, lezen daarentegen niet.

1. Voeg in het `public`-gedeelte van deze klasse een constructor toe:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Deze constructor stelt alle velden in om te beginnen met lezen vanaf het begin van het flashgeheugenblok en laadt het eerste blok gegevens in de buffer.

1. Implementeer de `write`-methode. Deze stream zal alleen gegevens lezen, dus deze kan niets doen en 0 retourneren:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementeer de `peek`-methode. Deze retourneert de gegevens op de huidige positie zonder de stream verder te bewegen. Het meerdere keren aanroepen van `peek` zal altijd dezelfde gegevens retourneren zolang er geen gegevens worden gelezen uit de stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementeer de `available`-functie. Deze retourneert hoeveel bytes kunnen worden gelezen uit de stream, of -1 als de stream compleet is. Voor deze klasse zal het maximum dat beschikbaar is nooit meer zijn dan de chunkgrootte van de HTTPClient. Wanneer deze stream wordt gebruikt in de HTTP-client, roept deze functie op om te zien hoeveel gegevens beschikbaar zijn en vraagt vervolgens dat aantal gegevens op om naar de REST API te sturen. We willen niet dat elke chunk groter is dan de chunkgrootte van de HTTP-client, dus als er meer beschikbaar is, wordt de chunkgrootte geretourneerd. Als er minder beschikbaar is, wordt wat beschikbaar is geretourneerd. Zodra alle gegevens zijn gestreamd, wordt -1 geretourneerd.

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

1. Implementeer de `read`-methode om het volgende byte uit de buffer te retourneren en de positie te verhogen. Als de positie de grootte van de buffer overschrijdt, vult het de buffer met het volgende blok uit het flashgeheugen en reset de positie.

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

1. Voeg in het `speech_to_text.h`-headerbestand een include-directive toe voor dit nieuwe headerbestand:

    ```cpp
    #include "flash_stream.h"
    ```

### Taak - zet de spraak om naar tekst

1. De spraak kan worden omgezet naar tekst door de audio naar de Spraakservice te sturen via een REST API. Deze REST API heeft een ander certificaat dan de tokenuitgever, dus voeg de volgende code toe aan het `config.h`-headerbestand om dit certificaat te definiëren:

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

1. Voeg een constante toe aan dit bestand voor de spraak-URL zonder de locatie. Deze wordt later gecombineerd met de locatie en taal om de volledige URL te verkrijgen.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Voeg in het `speech_to_text.h`-headerbestand, in het `private`-gedeelte van de `SpeechToText`-klasse, een veld toe voor een WiFi Client die het spraakcertificaat gebruikt:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Stel in de `init`-methode het certificaat in op deze WiFi Client:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Voeg de volgende code toe aan het `public`-gedeelte van de `SpeechToText`-klasse om een methode te definiëren om spraak om te zetten naar tekst:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Voeg de volgende code toe aan deze methode om een HTTP-client te maken met behulp van de WiFi-client die is geconfigureerd met het spraakcertificaat, en gebruikmakend van de spraak-URL ingesteld met de locatie en taal:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Er moeten enkele headers worden ingesteld op de verbinding:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Dit stelt headers in voor de autorisatie met behulp van het toegangstoken, het audioformaat met behulp van de sample rate, en stelt in dat de client het resultaat als JSON verwacht.

1. Voeg hierna de volgende code toe om de REST API-oproep te maken:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Dit maakt een `FlashStream` en gebruikt deze om gegevens te streamen naar de REST API.

1. Voeg hieronder de volgende code toe:

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

    Deze code controleert de responscode.

    Als het 200 is, de code voor succes, dan wordt het resultaat opgehaald, gedecodeerd van JSON, en wordt de eigenschap `DisplayText` ingesteld in de `text`-variabele. Dit is de eigenschap waarin de tekstversie van de spraak wordt geretourneerd.

    Als de responscode 401 is, dan is het toegangstoken verlopen (deze tokens zijn slechts 10 minuten geldig). Een nieuw toegangstoken wordt aangevraagd en de oproep wordt opnieuw gedaan.

    Anders wordt een fout naar de seriële monitor gestuurd en blijft de `text` leeg.

1. Voeg de volgende code toe aan het einde van deze methode om de HTTP-client te sluiten en de tekst te retourneren:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Roep in `main.cpp` deze nieuwe `convertSpeechToText`-methode aan in de `processAudio`-functie en log de spraak naar de seriële monitor:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Bouw deze code, upload deze naar je Wio Terminal en test het via de seriële monitor. Zodra je `Ready` ziet in de seriële monitor, druk op de C-knop (de knop aan de linkerkant, het dichtst bij de aan/uit-schakelaar) en spreek. 4 seconden audio worden opgenomen en vervolgens omgezet naar tekst.

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

> 💁 Je kunt deze code vinden in de [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) map.

😀 Je spraak-naar-tekst-programma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.