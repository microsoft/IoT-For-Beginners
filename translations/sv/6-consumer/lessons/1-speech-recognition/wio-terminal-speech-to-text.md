<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T21:10:58+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "sv"
}
-->
# Tal till text - Wio Terminal

I den här delen av lektionen kommer du att skriva kod för att omvandla tal i det inspelade ljudet till text med hjälp av tal-tjänsten.

## Skicka ljudet till tal-tjänsten

Ljudet kan skickas till tal-tjänsten med hjälp av REST API. För att använda tal-tjänsten behöver du först begära en åtkomsttoken och sedan använda den token för att komma åt REST API. Dessa åtkomsttokens går ut efter 10 minuter, så din kod bör regelbundet begära nya för att säkerställa att de alltid är aktuella.

### Uppgift - hämta en åtkomsttoken

1. Öppna projektet `smart-timer` om det inte redan är öppet.

1. Lägg till följande bibliotek som beroenden i filen `platformio.ini` för att få åtkomst till WiFi och hantera JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Lägg till följande kod i header-filen `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Ersätt `<SSID>` och `<PASSWORD>` med relevanta värden för ditt WiFi.

    Ersätt `<API_KEY>` med API-nyckeln för din tal-tjänstresurs. Ersätt `<LOCATION>` med platsen du använde när du skapade tal-tjänstresursen.

    Ersätt `<LANGUAGE>` med lokalnamnet för det språk du kommer att tala, till exempel `en-GB` för engelska eller `zn-HK` för kantonesiska. Du kan hitta en lista över de språk och lokaler som stöds i [dokumentationen om språk- och röststöd på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstanten `TOKEN_URL` är URL:en för tokenutgivaren utan platsen. Denna kommer senare att kombineras med platsen för att få den fullständiga URL:en.

1. Precis som när du ansluter till Custom Vision behöver du använda en HTTPS-anslutning för att ansluta till tokenutgivningstjänsten. Lägg till följande kod i slutet av `config.h`:

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

    Detta är samma certifikat som du använde när du anslöt till Custom Vision.

1. Lägg till en inkludering för WiFi-headerfilen och config-headerfilen högst upp i filen `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Lägg till kod för att ansluta till WiFi i `main.cpp` ovanför funktionen `setup`:

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

1. Anropa denna funktion från `setup`-funktionen efter att seriell anslutning har etablerats:

    ```cpp
    connectWiFi();
    ```

1. Skapa en ny header-fil i mappen `src` som heter `speech_to_text.h`. I denna header-fil, lägg till följande kod:

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

    Detta inkluderar några nödvändiga header-filer för en HTTP-anslutning, konfiguration och `mic.h`-headerfilen, samt definierar en klass som heter `SpeechToText`, innan en instans av den klassen deklareras som kan användas senare.

1. Lägg till följande två fält i den privata sektionen av denna klass:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` är en WiFi-klient som använder HTTPS och kommer att användas för att hämta åtkomsttoken. Denna token kommer sedan att lagras i `_access_token`.

1. Lägg till följande metod i den privata sektionen:

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

    Denna kod bygger URL:en för tokenutgivnings-API:t med hjälp av platsen för talresursen. Den skapar sedan en `HTTPClient` för att göra webbförfrågan, konfigurerad för att använda WiFi-klienten med tokenutgivningens certifikat. Den ställer in API-nyckeln som en header för anropet. Därefter görs en POST-förfrågan för att hämta certifikatet, och om det uppstår några fel försöker den igen. Slutligen returneras åtkomsttoken.

1. Lägg till en metod i den publika sektionen för att hämta åtkomsttoken. Denna kommer att behövas i senare lektioner för att omvandla text till tal.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Lägg till en `init`-metod i den publika sektionen som konfigurerar token-klienten:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Denna ställer in certifikatet på WiFi-klienten och hämtar sedan åtkomsttoken.

1. I `main.cpp`, lägg till denna nya header-fil i inkluderingsdirektiven:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Initiera klassen `SpeechToText` i slutet av `setup`-funktionen, efter anropet till `mic.init` men innan `Ready` skrivs till seriell monitor:

    ```cpp
    speechToText.init();
    ```

### Uppgift - läsa ljud från flashminne

1. I en tidigare del av lektionen spelades ljudet in i flashminnet. Detta ljud behöver skickas till Speech Services REST API, så det måste läsas från flashminnet. Det kan inte laddas in i en minnesbuffert eftersom det skulle vara för stort. Klassen `HTTPClient` som gör REST-anrop kan strömma data med hjälp av en Arduino Stream - en klass som kan läsa data i små bitar och skicka dem en i taget som en del av förfrågan. Varje gång du anropar `read` på en stream returneras nästa databit. En Arduino-stream kan skapas som kan läsa från flashminnet. Skapa en ny fil som heter `flash_stream.h` i mappen `src` och lägg till följande kod i den:

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

    Detta deklarerar klassen `FlashStream`, som härstammar från Arduino-klassen `Stream`. Detta är en abstrakt klass - härledda klasser måste implementera några metoder innan klassen kan instansieras, och dessa metoder definieras i denna klass.

    ✅ Läs mer om Arduino Streams i [Arduino Stream-dokumentationen](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Lägg till följande fält i den privata sektionen:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Detta definierar en temporär buffert för att lagra data som läses från flashminnet, tillsammans med fält för att lagra den aktuella positionen vid läsning från bufferten, den aktuella adressen för att läsa från flashminnet och flashminnesenheten.

1. I den privata sektionen, lägg till följande metod:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Denna kod läser från flashminnet vid den aktuella adressen och lagrar data i en buffert. Den ökar sedan adressen, så nästa anrop läser nästa block av minnet. Bufferten är dimensionerad baserat på den största bit som `HTTPClient` kommer att skicka till REST API åt gången.

    > 💁 Radering av flashminne måste göras med hjälp av kornstorleken, medan läsning inte har denna begränsning.

1. I den publika sektionen av denna klass, lägg till en konstruktor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Denna konstruktor ställer in alla fält för att börja läsa från början av flashminnesblocket och laddar den första biten data i bufferten.

1. Implementera metoden `write`. Denna stream kommer endast att läsa data, så denna metod kan göra ingenting och returnera 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementera metoden `peek`. Denna returnerar data vid den aktuella positionen utan att flytta streamen framåt. Att anropa `peek` flera gånger returnerar alltid samma data så länge ingen data läses från streamen.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementera funktionen `available`. Denna returnerar hur många byte som kan läsas från streamen, eller -1 om streamen är klar. För denna klass kommer det maximala tillgängliga aldrig att vara mer än HTTP-klientens bitstorlek. När denna stream används i HTTP-klienten anropar den denna funktion för att se hur mycket data som är tillgängligt och begär sedan så mycket data att skicka till REST API. Vi vill inte att varje bit ska vara större än HTTP-klientens bitstorlek, så om mer än detta är tillgängligt returneras bitstorleken. Om mindre, returneras det som är tillgängligt. När all data har strömmats returneras -1.

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

1. Implementera metoden `read` för att returnera nästa byte från bufferten och öka positionen. Om positionen överskrider buffertens storlek fylls bufferten med nästa block från flashminnet och positionen återställs.

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

1. I header-filen `speech_to_text.h`, lägg till en inkludering för denna nya header-fil:

    ```cpp
    #include "flash_stream.h"
    ```

### Uppgift - omvandla tal till text

1. Talet kan omvandlas till text genom att skicka ljudet till tal-tjänsten via ett REST API. Detta REST API har ett annat certifikat än tokenutgivaren, så lägg till följande kod i header-filen `config.h` för att definiera detta certifikat:

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

1. Lägg till en konstant i denna fil för tal-URL:en utan platsen. Denna kommer att kombineras med platsen och språket senare för att få den fullständiga URL:en.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. I header-filen `speech_to_text.h`, i den privata sektionen av klassen `SpeechToText`, definiera ett fält för en WiFi-klient som använder talcertifikatet:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. I metoden `init`, ställ in certifikatet på denna WiFi-klient:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Lägg till följande kod i den publika sektionen av klassen `SpeechToText` för att definiera en metod för att omvandla tal till text:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Lägg till följande kod i denna metod för att skapa en HTTP-klient med WiFi-klienten konfigurerad med talcertifikatet och använda tal-URL:en inställd med plats och språk:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Några headers behöver ställas in på anslutningen:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Detta ställer in headers för auktorisering med hjälp av åtkomsttoken, ljudformatet med hjälp av samplingsfrekvensen och anger att klienten förväntar sig resultatet som JSON.

1. Efter detta, lägg till följande kod för att göra REST API-anropet:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Detta skapar en `FlashStream` och använder den för att strömma data till REST API.

1. Nedanför detta, lägg till följande kod:

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

    Denna kod kontrollerar svarskoden.

    Om den är 200, koden för framgång, hämtas resultatet, avkodas från JSON och egenskapen `DisplayText` sätts in i variabeln `text`. Detta är egenskapen där textversionen av talet returneras.

    Om svarskoden är 401 har åtkomsttoken gått ut (dessa tokens varar endast i 10 minuter). En ny åtkomsttoken begärs och anropet görs igen.

    Annars skickas ett fel till seriell monitor och `text` lämnas tom.

1. Lägg till följande kod i slutet av denna metod för att stänga HTTP-klienten och returnera texten:

    ```cpp
    httpClient.end();

    return text;
    ```

1. I `main.cpp`, anropa denna nya metod `convertSpeechToText` i funktionen `processAudio` och logga sedan ut talet till seriell monitor:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Bygg denna kod, ladda upp den till din Wio Terminal och testa den genom seriell monitor. När du ser `Ready` i seriell monitor, tryck på C-knappen (den på vänster sida, närmast strömbrytaren) och tala. 4 sekunder av ljud kommer att spelas in och sedan omvandlas till text.

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

> 💁 Du kan hitta denna kod i mappen [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Ditt tal-till-text-program blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.