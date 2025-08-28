<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T09:21:12+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "sk"
}
-->
# Prevod reči na text - Wio Terminal

V tejto časti lekcie napíšete kód na konverziu reči zo zachyteného zvuku na text pomocou služby na rozpoznávanie reči.

## Odoslanie zvuku do služby na rozpoznávanie reči

Zvuk je možné odoslať do služby na rozpoznávanie reči pomocou REST API. Na použitie tejto služby je najprv potrebné požiadať o prístupový token, ktorý sa následne použije na prístup k REST API. Tieto prístupové tokeny vypršia po 10 minútach, takže váš kód by mal pravidelne žiadať nové tokeny, aby boli vždy aktuálne.

### Úloha - získanie prístupového tokenu

1. Otvorte projekt `smart-timer`, ak ešte nie je otvorený.

1. Pridajte nasledujúce závislosti knižníc do súboru `platformio.ini`, aby ste získali prístup k WiFi a mohli pracovať s JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Pridajte nasledujúci kód do hlavičkového súboru `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Nahraďte `<SSID>` a `<PASSWORD>` relevantnými hodnotami pre vašu WiFi.

    Nahraďte `<API_KEY>` API kľúčom pre váš zdroj služby na rozpoznávanie reči. Nahraďte `<LOCATION>` lokalitou, ktorú ste použili pri vytváraní zdroja služby na rozpoznávanie reči.

    Nahraďte `<LANGUAGE>` názvom lokalizácie jazyka, v ktorom budete hovoriť, napríklad `en-GB` pre angličtinu alebo `zn-HK` pre kantončinu. Zoznam podporovaných jazykov a ich lokalizácií nájdete v [dokumentácii o podpore jazykov a hlasov na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konštanta `TOKEN_URL` je URL tokenového vydavateľa bez lokality. Táto URL bude neskôr kombinovaná s lokalitou na získanie úplnej URL.

1. Rovnako ako pri pripojení k Custom Vision, budete potrebovať HTTPS pripojenie na pripojenie k službe vydávajúcej tokeny. Na koniec súboru `config.h` pridajte nasledujúci kód:

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

    Toto je rovnaký certifikát, aký ste použili pri pripojení k Custom Vision.

1. Pridajte direktívu na zahrnutie hlavičkového súboru WiFi a hlavičkového súboru config na začiatok súboru `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Pridajte kód na pripojenie k WiFi do súboru `main.cpp` nad funkciu `setup`:

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

1. Zavolajte túto funkciu z funkcie `setup` po tom, ako bola nadviazaná sériová komunikácia:

    ```cpp
    connectWiFi();
    ```

1. Vytvorte nový hlavičkový súbor v priečinku `src` s názvom `speech_to_text.h`. Do tohto hlavičkového súboru pridajte nasledujúci kód:

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

    Tento kód zahŕňa potrebné hlavičkové súbory pre HTTP pripojenie, konfiguráciu a hlavičkový súbor `mic.h`, a definuje triedu s názvom `SpeechToText`, predtým ako deklaruje inštanciu tejto triedy, ktorá bude použitá neskôr.

1. Pridajte nasledujúce 2 polia do sekcie `private` tejto triedy:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` je WiFi klient, ktorý používa HTTPS a bude použitý na získanie prístupového tokenu. Tento token bude následne uložený v `_access_token`.

1. Pridajte nasledujúcu metódu do sekcie `private`:

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

    Tento kód vytvára URL pre API tokenového vydavateľa pomocou lokality zdroja reči. Potom vytvára `HTTPClient` na vykonanie webového požiadavku, nastavuje ho na použitie WiFi klienta nakonfigurovaného s certifikátom tokenového vydavateľa. Nastavuje API kľúč ako hlavičku pre požiadavku. Potom vykonáva POST požiadavku na získanie certifikátu, opakuje pokus v prípade chyby. Nakoniec sa prístupový token vráti.

1. Do sekcie `public` pridajte metódu na získanie prístupového tokenu. Táto metóda bude potrebná v neskorších lekciách na konverziu textu na reč.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Do sekcie `public` pridajte metódu `init`, ktorá nastaví tokenového klienta:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Táto metóda nastaví certifikát na WiFi klientovi a potom získa prístupový token.

1. V súbore `main.cpp` pridajte tento nový hlavičkový súbor do direktív na zahrnutie:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inicializujte triedu `SpeechToText` na konci funkcie `setup`, po volaní `mic.init`, ale pred tým, ako sa do sériového monitora zapíše `Ready`:

    ```cpp
    speechToText.init();
    ```

### Úloha - čítanie zvuku z flash pamäte

1. V predchádzajúcej časti tejto lekcie bol zvuk zaznamenaný do flash pamäte. Tento zvuk bude potrebné odoslať do REST API služby na rozpoznávanie reči, takže ho bude potrebné prečítať z flash pamäte. Nemôže byť načítaný do pamäťového bufferu, pretože by bol príliš veľký. Trieda `HTTPClient`, ktorá vykonáva REST požiadavky, môže streamovať dáta pomocou Arduino Stream - triedy, ktorá dokáže načítať dáta v malých blokoch a odosielať ich jeden po druhom ako súčasť požiadavky. Každé volanie `read` na stream vráti ďalší blok dát. Arduino stream môže byť vytvorený tak, aby čítal z flash pamäte. Vytvorte nový súbor s názvom `flash_stream.h` v priečinku `src` a pridajte do neho nasledujúci kód:

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

    Tento kód deklaruje triedu `FlashStream`, ktorá je odvodená od Arduino triedy `Stream`. Táto trieda je abstraktná - odvodené triedy musia implementovať niekoľko metód, aby mohla byť trieda inštanciovaná, a tieto metódy sú definované v tejto triede.

    ✅ Viac o Arduino Streams si môžete prečítať v [dokumentácii Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Pridajte nasledujúce polia do sekcie `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Tieto polia definujú dočasný buffer na ukladanie dát načítaných z flash pamäte, spolu s poľami na ukladanie aktuálnej pozície pri čítaní z bufferu, aktuálnej adresy na čítanie z flash pamäte a flash pamäťového zariadenia.

1. Do sekcie `private` pridajte nasledujúcu metódu:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Tento kód číta z flash pamäte na aktuálnej adrese a ukladá dáta do bufferu. Potom inkrementuje adresu, takže ďalšie volanie načíta ďalší blok pamäte. Buffer je veľký podľa najväčšieho bloku, ktorý `HTTPClient` odošle do REST API naraz.

    > 💁 Mazanie flash pamäte musí byť vykonané pomocou veľkosti zrna, čítanie však nie.

1. Do sekcie `public` tejto triedy pridajte konštruktor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Tento konštruktor nastaví všetky polia na začiatok čítania z flash pamäťového bloku a načíta prvý blok dát do bufferu.

1. Implementujte metódu `write`. Tento stream bude iba čítať dáta, takže táto metóda môže nič nerobiť a vrátiť 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementujte metódu `peek`. Táto metóda vráti dáta na aktuálnej pozícii bez posunutia streamu. Opakované volanie `peek` vždy vráti rovnaké dáta, pokiaľ sa zo streamu nečítajú nové dáta.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementujte funkciu `available`. Táto funkcia vráti, koľko bajtov je možné prečítať zo streamu, alebo -1, ak je stream dokončený. Pre túto triedu bude maximálne dostupné množstvo nie viac ako veľkosť bloku HTTP klienta. Keď tento stream používa HTTP klient, volá túto funkciu, aby zistil, koľko dát je dostupných, a potom požaduje toľko dát na odoslanie do REST API. Nechceme, aby každý blok bol väčší ako veľkosť bloku HTTP klienta, takže ak je dostupné viac, vráti sa veľkosť bloku. Ak je dostupné menej, vráti sa dostupné množstvo. Keď sú všetky dáta streamované, vráti sa -1.

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

1. Implementujte metódu `read`, ktorá vráti ďalší bajt z bufferu a inkrementuje pozíciu. Ak pozícia presiahne veľkosť bufferu, buffer sa naplní ďalším blokom z flash pamäte a pozícia sa resetuje.

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

1. V hlavičkovom súbore `speech_to_text.h` pridajte direktívu na zahrnutie tohto nového hlavičkového súboru:

    ```cpp
    #include "flash_stream.h"
    ```

### Úloha - konverzia reči na text

1. Reč môže byť konvertovaná na text odoslaním zvuku do služby na rozpoznávanie reči cez REST API. Toto REST API má iný certifikát ako tokenový vydavateľ, takže pridajte nasledujúci kód do hlavičkového súboru `config.h`, aby ste definovali tento certifikát:

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

1. Pridajte konštantu do tohto súboru pre URL služby na rozpoznávanie reči bez lokality. Táto URL bude neskôr kombinovaná s lokalitou a jazykom na získanie úplnej URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. V hlavičkovom súbore `speech_to_text.h`, v sekcii `private` triedy `SpeechToText`, definujte pole pre WiFi klienta používajúceho certifikát služby na rozpoznávanie reči:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. V metóde `init` nastavte certifikát na tomto WiFi klientovi:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Do sekcie `public` triedy `SpeechToText` pridajte metódu na konverziu reči na text:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Pridajte nasledujúci kód do tejto metódy na vytvorenie HTTP klienta používajúceho WiFi klienta nakonfigurovaného s certifikátom služby na rozpoznávanie reči a používajúceho URL služby nastavenú s lokalitou a jazykom:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Na pripojenie je potrebné nastaviť niektoré hlavičky:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Tieto hlavičky nastavujú autorizáciu pomocou prístupového tokenu, formát zvuku pomocou vzorkovacej frekvencie a nastavujú, že klient očakáva výsledok vo formáte JSON.

1. Po tomto pridajte nasledujúci kód na vykonanie REST API požiadavky:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Tento kód vytvára `FlashStream` a používa ho na streamovanie dát do REST API.

1. Pod týmto kódom pridajte nasledujúci kód:

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

    Tento kód kontroluje odpovedný kód.

    Ak je to 200, kód pre úspech, výsledok sa načíta, dekóduje z JSON a vlastnosť `DisplayText` sa nastaví do premennej `text`. Toto je vlastnosť, v ktorej je vrátená textová verzia reči.

    Ak je odpovedný kód 401, prístupový token vypršal (tieto tokeny platia iba 10 minút). Požiada sa o nový prístupový token a požiadavka sa vykoná znova.

    Inak sa chyba odošle do sériového monitora a `text` zostane prázdny.

1. Na koniec tejto metódy pridajte nasledujúci kód na zatvorenie HTTP klienta a vrátenie textu:

    ```cpp
    httpClient.end();

    return text;
    ```

1. V súbore `main.cpp` zavolajte novú metódu `convertSpeechToText` vo funkcii `processAudio`, potom vypíšte reč do sériového monitora:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Zostavte tento kód, nahrajte ho do vášho Wio Terminalu a otestujte ho cez sériový monitor. Keď uvidíte `Ready` v sériovom monitore, stlačte tlačidlo C (to na ľavej strane, najbližšie k vypínaču) a hovorte. 4 sekundy zvuku budú zachytené a následne konvertované na text.

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

> 💁 Tento kód nájdete v priečinku [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Váš program na prevod reči na text bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.