<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T21:12:05+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "no"
}
-->
# Tale til tekst - Wio Terminal

I denne delen av leksjonen skal du skrive kode for å konvertere tale i det innspilte lydopptaket til tekst ved hjelp av taleservicen.

## Send lyden til taleservicen

Lyden kan sendes til taleservicen ved hjelp av REST API. For å bruke taleservicen må du først be om en tilgangstoken, og deretter bruke denne tokenen for å få tilgang til REST API. Disse tilgangstokenene utløper etter 10 minutter, så koden din bør be om dem regelmessig for å sikre at de alltid er oppdaterte.

### Oppgave - få en tilgangstoken

1. Åpne prosjektet `smart-timer` hvis det ikke allerede er åpent.

1. Legg til følgende bibliotekavhengigheter i `platformio.ini`-filen for å få tilgang til WiFi og håndtere JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Legg til følgende kode i `config.h`-headerfilen:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Erstatt `<SSID>` og `<PASSWORD>` med de relevante verdiene for ditt WiFi.

    Erstatt `<API_KEY>` med API-nøkkelen for ressursen din i taleservicen. Erstatt `<LOCATION>` med plasseringen du brukte da du opprettet ressursen i taleservicen.

    Erstatt `<LANGUAGE>` med lokalitetsnavnet for språket du skal snakke på, for eksempel `en-GB` for engelsk eller `zn-HK` for kantonesisk. Du finner en liste over støttede språk og deres lokalitetsnavn i [dokumentasjonen for språk- og stemmestøtte på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstanten `TOKEN_URL` er URL-en til tokenutstederen uten plasseringen. Denne vil bli kombinert med plasseringen senere for å få den fullstendige URL-en.

1. Akkurat som ved tilkobling til Custom Vision, må du bruke en HTTPS-tilkobling for å koble til tokenutstedelsestjenesten. Legg til følgende kode på slutten av `config.h`:

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

    Dette er det samme sertifikatet du brukte da du koblet til Custom Vision.

1. Legg til en inkludering for WiFi-headerfilen og config-headerfilen øverst i `main.cpp`-filen:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Legg til kode for å koble til WiFi i `main.cpp` over `setup`-funksjonen:

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

1. Kall denne funksjonen fra `setup`-funksjonen etter at serietilkoblingen er opprettet:

    ```cpp
    connectWiFi();
    ```

1. Opprett en ny headerfil i `src`-mappen kalt `speech_to_text.h`. I denne headerfilen legger du til følgende kode:

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

    Dette inkluderer noen nødvendige headerfiler for en HTTP-tilkobling, konfigurasjon og `mic.h`-headerfilen, og definerer en klasse kalt `SpeechToText`, før den erklærer en instans av denne klassen som kan brukes senere.

1. Legg til følgende to felt i den private delen av denne klassen:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` er en WiFi-klient som bruker HTTPS og vil bli brukt til å hente tilgangstokenet. Dette tokenet vil deretter bli lagret i `_access_token`.

1. Legg til følgende metode i den private delen:

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

    Denne koden bygger URL-en for tokenutstederens API ved hjelp av plasseringen til taleserviceressursen. Den oppretter deretter en `HTTPClient` for å gjøre webforespørselen, og setter den opp til å bruke WiFi-klienten konfigurert med sertifikatet for tokenendepunktet. Den setter API-nøkkelen som en header for forespørselen. Deretter gjør den en POST-forespørsel for å få sertifikatet, og prøver på nytt hvis det oppstår feil. Til slutt returneres tilgangstokenet.

1. I den offentlige delen legger du til en metode for å hente tilgangstokenet. Dette vil være nødvendig i senere leksjoner for å konvertere tekst til tale.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. I den offentlige delen legger du til en `init`-metode som setter opp tokenklienten:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Denne setter sertifikatet på WiFi-klienten og henter deretter tilgangstokenet.

1. I `main.cpp` legger du til denne nye headerfilen i inkluderingsdirektivene:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Initialiser `SpeechToText`-klassen på slutten av `setup`-funksjonen, etter `mic.init`-kallet, men før `Ready` skrives til seriemonitoren:

    ```cpp
    speechToText.init();
    ```

### Oppgave - les lyd fra flashminne

1. I en tidligere del av denne leksjonen ble lyden tatt opp til flashminnet. Denne lyden må sendes til taleservicens REST API, så den må leses fra flashminnet. Den kan ikke lastes inn i en buffer i minnet, da den ville vært for stor. Klassen `HTTPClient` som gjør REST-kall kan strømme data ved hjelp av en Arduino Stream - en klasse som kan laste data i små biter og sende dem én om gangen som en del av forespørselen. Hver gang du kaller `read` på en stream, returnerer den neste blokk med data. En Arduino-stream kan opprettes som kan lese fra flashminnet. Opprett en ny fil kalt `flash_stream.h` i `src`-mappen, og legg til følgende kode i den:

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

    Dette erklærer klassen `FlashStream`, som arver fra Arduino `Stream`-klassen. Dette er en abstrakt klasse - avledede klasser må implementere noen metoder før klassen kan instansieres, og disse metodene er definert i denne klassen.

    ✅ Les mer om Arduino Streams i [Arduino Stream-dokumentasjonen](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Legg til følgende felt i den private delen:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Dette definerer en midlertidig buffer for å lagre data som leses fra flashminnet, sammen med felt for å lagre den nåværende posisjonen når du leser fra bufferen, den nåværende adressen for å lese fra flashminnet, og flashminneenheten.

1. I den private delen legger du til følgende metode:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Denne koden leser fra flashminnet på den nåværende adressen og lagrer dataene i en buffer. Den øker deretter adressen, slik at neste kall leser neste blokk med minne. Bufferen er dimensjonert basert på den største biten som `HTTPClient` vil sende til REST API om gangen.

    > 💁 Sletting av flashminne må gjøres med kornstørrelsen, mens lesing ikke har denne begrensningen.

1. I den offentlige delen av denne klassen legger du til en konstruktør:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Denne konstruktøren setter opp alle feltene for å starte lesing fra starten av flashminneblokken, og laster den første biten med data inn i bufferen.

1. Implementer `write`-metoden. Denne streamen vil kun lese data, så denne kan gjøre ingenting og returnere 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementer `peek`-metoden. Denne returnerer dataene på den nåværende posisjonen uten å flytte streamen videre. Å kalle `peek` flere ganger vil alltid returnere de samme dataene så lenge ingen data leses fra streamen.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementer `available`-funksjonen. Denne returnerer hvor mange byte som kan leses fra streamen, eller -1 hvis streamen er ferdig. For denne klassen vil det maksimale tilgjengelige aldri være mer enn HTTP-klientens bitstørrelse. Når denne streamen brukes i HTTP-klienten, kaller den denne funksjonen for å se hvor mye data som er tilgjengelig, og ber deretter om så mye data for å sende til REST API. Vi ønsker ikke at hver bit skal være større enn HTTP-klientens bitstørrelse, så hvis mer enn det er tilgjengelig, returneres bitstørrelsen. Hvis mindre, returneres det som er tilgjengelig. Når alle dataene er strømmet, returneres -1.

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

1. Implementer `read`-metoden for å returnere neste byte fra bufferen, og øk posisjonen. Hvis posisjonen overskrider størrelsen på bufferen, fylles bufferen med neste blokk fra flashminnet, og posisjonen nullstilles.

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

1. I `speech_to_text.h`-headerfilen legger du til en inkludering for denne nye headerfilen:

    ```cpp
    #include "flash_stream.h"
    ```

### Oppgave - konverter tale til tekst

1. Talen kan konverteres til tekst ved å sende lyden til taleservicen via et REST API. Dette REST API har et annet sertifikat enn tokenutstederen, så legg til følgende kode i `config.h`-headerfilen for å definere dette sertifikatet:

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

1. Legg til en konstant i denne filen for tale-URL-en uten plasseringen. Denne vil bli kombinert med plasseringen og språket senere for å få den fullstendige URL-en.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. I `speech_to_text.h`-headerfilen, i den private delen av `SpeechToText`-klassen, definerer du et felt for en WiFi-klient som bruker talesertifikatet:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. I `init`-metoden setter du sertifikatet på denne WiFi-klienten:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Legg til følgende kode i den offentlige delen av `SpeechToText`-klassen for å definere en metode for å konvertere tale til tekst:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Legg til følgende kode i denne metoden for å opprette en HTTP-klient ved hjelp av WiFi-klienten konfigurert med talesertifikatet, og bruke tale-URL-en satt med plasseringen og språket:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Noen headere må settes på tilkoblingen:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Dette setter headere for autorisasjon ved hjelp av tilgangstokenet, lydformatet ved hjelp av samplingsfrekvensen, og angir at klienten forventer resultatet som JSON.

1. Etter dette legger du til følgende kode for å gjøre REST API-kallet:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Dette oppretter en `FlashStream` og bruker den til å strømme data til REST API.

1. Under dette legger du til følgende kode:

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

    Denne koden sjekker responskoden.

    Hvis den er 200, koden for suksess, hentes resultatet, dekodes fra JSON, og `DisplayText`-egenskapen settes inn i `text`-variabelen. Dette er egenskapen der tekstversjonen av talen returneres.

    Hvis responskoden er 401, har tilgangstokenet utløpt (disse tokenene varer kun i 10 minutter). Et nytt tilgangstoken hentes, og kallet gjøres på nytt.

    Ellers sendes en feil til seriemonitoren, og `text` forblir tom.

1. Legg til følgende kode på slutten av denne metoden for å lukke HTTP-klienten og returnere teksten:

    ```cpp
    httpClient.end();

    return text;
    ```

1. I `main.cpp` kaller du denne nye `convertSpeechToText`-metoden i `processAudio`-funksjonen, og logger deretter ut talen til seriemonitoren:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Bygg denne koden, last den opp til Wio Terminal og test den gjennom seriemonitoren. Når du ser `Ready` i seriemonitoren, trykker du på C-knappen (den på venstre side, nærmest strømbryteren), og snakker. 4 sekunder med lyd vil bli tatt opp og deretter konvertert til tekst.

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

> 💁 Du finner denne koden i [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal)-mappen.

😀 Programmet ditt for tale til tekst var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.