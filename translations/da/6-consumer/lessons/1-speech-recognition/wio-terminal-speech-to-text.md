<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T21:11:34+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "da"
}
-->
# Tale til tekst - Wio Terminal

I denne del af lektionen skal du skrive kode for at konvertere tale i det optagede lyd til tekst ved hjælp af tale-tjenesten.

## Send lyden til tale-tjenesten

Lyden kan sendes til tale-tjenesten ved hjælp af REST API'en. For at bruge tale-tjenesten skal du først anmode om en adgangstoken og derefter bruge denne token til at få adgang til REST API'en. Disse adgangstokens udløber efter 10 minutter, så din kode skal regelmæssigt anmode om dem for at sikre, at de altid er opdaterede.

### Opgave - få en adgangstoken

1. Åbn `smart-timer`-projektet, hvis det ikke allerede er åbent.

1. Tilføj følgende biblioteksafhængigheder til `platformio.ini`-filen for at få adgang til WiFi og håndtere JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Tilføj følgende kode til `config.h`-headerfilen:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Erstat `<SSID>` og `<PASSWORD>` med de relevante værdier for dit WiFi.

    Erstat `<API_KEY>` med API-nøglen til din tale-tjeneste-ressource. Erstat `<LOCATION>` med den placering, du brugte, da du oprettede tale-tjeneste-ressourcen.

    Erstat `<LANGUAGE>` med lokalitetsnavnet for det sprog, du vil tale på, for eksempel `en-GB` for engelsk eller `zn-HK` for kantonesisk. Du kan finde en liste over de understøttede sprog og deres lokalitetsnavne i [Language and voice support-dokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstanten `TOKEN_URL` er URL'en til token-udstederen uden placeringen. Denne vil senere blive kombineret med placeringen for at få den fulde URL.

1. Ligesom ved forbindelse til Custom Vision skal du bruge en HTTPS-forbindelse for at forbinde til token-udstedelsestjenesten. Tilføj følgende kode til slutningen af `config.h`:

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

    Dette er det samme certifikat, som du brugte, da du forbandt til Custom Vision.

1. Tilføj en include for WiFi-headerfilen og config-headerfilen øverst i `main.cpp`-filen:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Tilføj kode for at forbinde til WiFi i `main.cpp` over `setup`-funktionen:

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

1. Kald denne funktion fra `setup`-funktionen efter, at den serielle forbindelse er blevet etableret:

    ```cpp
    connectWiFi();
    ```

1. Opret en ny headerfil i `src`-mappen kaldet `speech_to_text.h`. I denne headerfil skal du tilføje følgende kode:

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

    Dette inkluderer nogle nødvendige headerfiler til en HTTP-forbindelse, konfiguration og `mic.h`-headerfilen og definerer en klasse kaldet `SpeechToText`, før den erklærer en instans af denne klasse, som kan bruges senere.

1. Tilføj følgende 2 felter til den private sektion af denne klasse:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` er en WiFi-klient, der bruger HTTPS og vil blive brugt til at få adgangstokenet. Denne token vil derefter blive gemt i `_access_token`.

1. Tilføj følgende metode til den private sektion:

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

    Denne kode bygger URL'en til token-udstederens API ved hjælp af placeringen af tale-ressourcen. Den opretter derefter en `HTTPClient` for at lave webanmodningen, konfigureret til at bruge WiFi-klienten med token-endepunktets certifikat. Den sætter API-nøglen som en header for kaldet. Den laver derefter en POST-anmodning for at få certifikatet og prøver igen, hvis der opstår fejl. Til sidst returneres adgangstokenet.

1. Til den offentlige sektion skal du tilføje en metode til at få adgangstokenet. Dette vil være nødvendigt i senere lektioner for at konvertere tekst til tale.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Til den offentlige sektion skal du tilføje en `init`-metode, der opsætter token-klienten:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Dette sætter certifikatet på WiFi-klienten og henter derefter adgangstokenet.

1. I `main.cpp` skal du tilføje denne nye headerfil til include-direktiverne:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Initialiser `SpeechToText`-klassen i slutningen af `setup`-funktionen, efter `mic.init`-kaldet, men før `Ready` skrives til den serielle monitor:

    ```cpp
    speechToText.init();
    ```

### Opgave - læs lyd fra flash-hukommelse

1. I en tidligere del af denne lektion blev lyden optaget til flash-hukommelsen. Denne lyd skal sendes til Speech Services REST API, så den skal læses fra flash-hukommelsen. Den kan ikke indlæses i en in-memory buffer, da den ville være for stor. Klassen `HTTPClient`, der laver REST-kald, kan streame data ved hjælp af en Arduino Stream - en klasse, der kan indlæse data i små stykker og sende dem ét ad gangen som en del af anmodningen. Hver gang du kalder `read` på en stream, returnerer den næste blok af data. En Arduino-stream kan oprettes, der kan læse fra flash-hukommelsen. Opret en ny fil kaldet `flash_stream.h` i `src`-mappen, og tilføj følgende kode til den:

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

    Dette erklærer klassen `FlashStream`, der nedarver fra Arduino `Stream`-klassen. Dette er en abstrakt klasse - nedarvede klasser skal implementere nogle få metoder, før klassen kan instantieres, og disse metoder er defineret i denne klasse.

    ✅ Læs mere om Arduino Streams i [Arduino Stream-dokumentationen](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Tilføj følgende felter til den private sektion:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Dette definerer en midlertidig buffer til at gemme data, der læses fra flash-hukommelsen, sammen med felter til at gemme den aktuelle position, når der læses fra bufferen, den aktuelle adresse til at læse fra flash-hukommelsen og flash-hukommelsesenheden.

1. I den private sektion skal du tilføje følgende metode:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Denne kode læser fra flash-hukommelsen ved den aktuelle adresse og gemmer dataene i en buffer. Den øger derefter adressen, så næste kald læser den næste blok af hukommelse. Bufferen er dimensioneret baseret på den største chunk, som `HTTPClient` vil sende til REST API'en på én gang.

    > 💁 Sletning af flash-hukommelse skal ske ved hjælp af kornstørrelsen, mens læsning ikke behøver det.

1. I den offentlige sektion af denne klasse skal du tilføje en konstruktør:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Denne konstruktør opsætter alle felter til at starte læsning fra starten af flash-hukommelsesblokken og indlæser den første chunk af data i bufferen.

1. Implementer `write`-metoden. Denne stream vil kun læse data, så denne kan gøre ingenting og returnere 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementer `peek`-metoden. Denne returnerer dataene ved den aktuelle position uden at flytte streamen fremad. Hvis du kalder `peek` flere gange, vil det altid returnere de samme data, så længe der ikke læses data fra streamen.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementer `available`-funktionen. Denne returnerer, hvor mange bytes der kan læses fra streamen, eller -1, hvis streamen er færdig. For denne klasse vil det maksimale tilgængelige aldrig være mere end HTTPClients chunk-størrelse. Når denne stream bruges i HTTP-klienten, kalder den denne funktion for at se, hvor meget data der er tilgængeligt, og anmoder derefter om så meget data for at sende til REST API'en. Vi ønsker ikke, at hver chunk skal være større end HTTP-klientens chunk-størrelse, så hvis mere end det er tilgængeligt, returneres chunk-størrelsen. Hvis mindre, returneres det, der er tilgængeligt. Når alle data er streamet, returneres -1.

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

1. Implementer `read`-metoden for at returnere den næste byte fra bufferen og øge positionen. Hvis positionen overstiger størrelsen af bufferen, fylder den bufferen med den næste blok fra flash-hukommelsen og nulstiller positionen.

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

1. I `speech_to_text.h`-headerfilen skal du tilføje en include-direktiv for denne nye headerfil:

    ```cpp
    #include "flash_stream.h"
    ```

### Opgave - konverter tale til tekst

1. Talen kan konverteres til tekst ved at sende lyden til tale-tjenesten via REST API'en. Denne REST API har et andet certifikat end token-udstederen, så tilføj følgende kode til `config.h`-headerfilen for at definere dette certifikat:

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

1. Tilføj en konstant til denne fil for tale-URL'en uden placeringen. Denne vil senere blive kombineret med placeringen og sproget for at få den fulde URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. I `speech_to_text.h`-headerfilen, i den private sektion af `SpeechToText`-klassen, skal du definere et felt for en WiFi-klient, der bruger tale-certifikatet:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. I `init`-metoden skal du sætte certifikatet på denne WiFi-klient:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Tilføj følgende kode til den offentlige sektion af `SpeechToText`-klassen for at definere en metode til at konvertere tale til tekst:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Tilføj følgende kode til denne metode for at oprette en HTTP-klient ved hjælp af WiFi-klienten konfigureret med tale-certifikatet og ved hjælp af tale-URL'en sat med placeringen og sproget:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Nogle headers skal sættes på forbindelsen:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Dette sætter headers for autorisation ved hjælp af adgangstokenet, lydformatet ved hjælp af samplingsfrekvensen og angiver, at klienten forventer resultatet som JSON.

1. Efter dette skal du tilføje følgende kode for at lave REST API-kaldet:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Dette opretter en `FlashStream` og bruger den til at streame data til REST API'en.

1. Under dette skal du tilføje følgende kode:

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

    Denne kode kontrollerer svarkoden.

    Hvis den er 200, koden for succes, hentes resultatet, dekodes fra JSON, og `DisplayText`-egenskaben sættes ind i `text`-variablen. Dette er egenskaben, hvor tekstversionen af talen returneres.

    Hvis svarkoden er 401, er adgangstokenet udløbet (disse tokens varer kun 10 minutter). Et nyt adgangstoken anmodes om, og kaldet udføres igen.

    Ellers sendes en fejl til den serielle monitor, og `text` forbliver tom.

1. Tilføj følgende kode til slutningen af denne metode for at lukke HTTP-klienten og returnere teksten:

    ```cpp
    httpClient.end();

    return text;
    ```

1. I `main.cpp` skal du kalde denne nye `convertSpeechToText`-metode i `processAudio`-funktionen og derefter logge talen ud til den serielle monitor:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Byg denne kode, upload den til din Wio Terminal, og test den gennem den serielle monitor. Når du ser `Ready` i den serielle monitor, skal du trykke på C-knappen (den på venstre side, tættest på tænd/sluk-knappen) og tale. 4 sekunders lyd vil blive optaget og derefter konverteret til tekst.

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

> 💁 Du kan finde denne kode i [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal)-mappen.

😀 Dit tale-til-tekst-program var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.