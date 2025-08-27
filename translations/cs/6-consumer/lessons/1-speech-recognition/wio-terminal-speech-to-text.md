<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T21:29:12+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "cs"
}
-->
# Převod řeči na text - Wio Terminal

V této části lekce napíšete kód pro převod řeči z nahraného zvuku na text pomocí služby pro rozpoznávání řeči.

## Odeslání zvuku do služby pro rozpoznávání řeči

Zvuk lze odeslat do služby pro rozpoznávání řeči pomocí REST API. Pro použití této služby je nejprve nutné požádat o přístupový token, který následně použijete k přístupu k REST API. Tyto přístupové tokeny vyprší po 10 minutách, takže váš kód by měl tokeny pravidelně obnovovat, aby byly vždy aktuální.

### Úkol - získání přístupového tokenu

1. Otevřete projekt `smart-timer`, pokud již není otevřený.

1. Přidejte následující závislosti knihoven do souboru `platformio.ini`, abyste mohli přistupovat k WiFi a pracovat s JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Přidejte následující kód do hlavičkového souboru `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Nahraďte `<SSID>` a `<PASSWORD>` odpovídajícími hodnotami pro vaši WiFi.

    Nahraďte `<API_KEY>` klíčem API pro váš zdroj služby rozpoznávání řeči. Nahraďte `<LOCATION>` místem, které jste použili při vytváření zdroje služby rozpoznávání řeči.

    Nahraďte `<LANGUAGE>` názvem jazykové oblasti, ve které budete mluvit, například `en-GB` pro angličtinu nebo `zn-HK` pro kantonštinu. Seznam podporovaných jazyků a jejich názvů jazykových oblastí najdete v [dokumentaci o podpoře jazyků a hlasů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstantní proměnná `TOKEN_URL` je URL tokenového serveru bez uvedení lokace. Tato URL bude později kombinována s lokací pro získání úplné URL.

1. Stejně jako při připojení k Custom Vision budete potřebovat HTTPS připojení k tokenovému serveru. Na konec souboru `config.h` přidejte následující kód:

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

    Toto je stejný certifikát, který jste použili při připojení k Custom Vision.

1. Přidejte direktivu pro zahrnutí hlavičkového souboru WiFi a hlavičkového souboru config na začátek souboru `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Přidejte kód pro připojení k WiFi do souboru `main.cpp` nad funkci `setup`:

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

1. Zavolejte tuto funkci z funkce `setup` po navázání sériového připojení:

    ```cpp
    connectWiFi();
    ```

1. Vytvořte nový hlavičkový soubor ve složce `src` s názvem `speech_to_text.h`. Do tohoto hlavičkového souboru přidejte následující kód:

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

    Tento kód zahrnuje potřebné hlavičkové soubory pro HTTP připojení, konfiguraci a hlavičkový soubor `mic.h`, a definuje třídu `SpeechToText`, předtím než deklaruje instanci této třídy, která bude později použita.

1. Přidejte následující dvě pole do sekce `private` této třídy:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` je WiFi klient, který používá HTTPS a bude použit pro získání přístupového tokenu. Tento token bude následně uložen do `_access_token`.

1. Přidejte následující metodu do sekce `private`:

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

    Tento kód sestavuje URL pro tokenový server pomocí lokace zdroje služby rozpoznávání řeči. Poté vytvoří `HTTPClient` pro provedení webového požadavku, nastaví jej tak, aby používal WiFi klienta nakonfigurovaného s certifikátem tokenového serveru. API klíč je nastaven jako hlavička požadavku. Poté provede POST požadavek pro získání certifikátu, opakuje požadavek v případě chyb. Nakonec je přístupový token vrácen.

1. Do sekce `public` přidejte metodu pro získání přístupového tokenu. Tato metoda bude potřebná v dalších lekcích pro převod textu na řeč.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Do sekce `public` přidejte metodu `init`, která nastaví tokenového klienta:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Tato metoda nastaví certifikát na WiFi klientovi a poté získá přístupový token.

1. V souboru `main.cpp` přidejte tento nový hlavičkový soubor do direktiv pro zahrnutí:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inicializujte třídu `SpeechToText` na konci funkce `setup`, po volání `mic.init`, ale před tím, než je do sériového monitoru zapsáno `Ready`:

    ```cpp
    speechToText.init();
    ```

### Úkol - čtení zvuku z flash paměti

1. V dřívější části této lekce byl zvuk nahrán do flash paměti. Tento zvuk bude potřeba odeslat do REST API služby rozpoznávání řeči, takže musí být přečten z flash paměti. Nelze jej načíst do paměťového bufferu, protože by byl příliš velký. Třída `HTTPClient`, která provádí REST požadavky, může streamovat data pomocí Arduino Stream - třídy, která dokáže načítat data v malých blocích a odesílat je jeden po druhém jako součást požadavku. Pokaždé, když zavoláte `read` na streamu, vrátí další blok dat. Arduino stream může být vytvořen tak, aby četl z flash paměti. Vytvořte nový soubor s názvem `flash_stream.h` ve složce `src` a přidejte do něj následující kód:

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

    Tento kód deklaruje třídu `FlashStream`, která je odvozena z Arduino třídy `Stream`. Jedná se o abstraktní třídu - odvozené třídy musí implementovat několik metod, než může být třída instanciována, a tyto metody jsou definovány v této třídě.

    ✅ Více o Arduino Streams najdete v [dokumentaci Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Přidejte následující pole do sekce `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Tato pole definují dočasný buffer pro ukládání dat načtených z flash paměti, spolu s poli pro uložení aktuální pozice při čtení z bufferu, aktuální adresy pro čtení z flash paměti a zařízení flash paměti.

1. Do sekce `private` přidejte následující metodu:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Tento kód načítá data z flash paměti na aktuální adrese a ukládá je do bufferu. Poté adresu zvýší, takže další volání načte další blok paměti. Velikost bufferu je nastavena na největší blok, který `HTTPClient` odešle do REST API najednou.

    > 💁 Mazání flash paměti musí být prováděno pomocí velikosti zrna, čtení na druhou stranu nikoliv.

1. Do sekce `public` této třídy přidejte konstruktor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Tento konstruktor nastaví všechna pole tak, aby začala číst od začátku bloku flash paměti, a načte první blok dat do bufferu.

1. Implementujte metodu `write`. Tento stream bude pouze číst data, takže tato metoda může nic nedělat a vrátit 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementujte metodu `peek`. Tato metoda vrací data na aktuální pozici bez posunutí streamu. Opakované volání `peek` vždy vrátí stejná data, pokud nebyla ze streamu načtena žádná data.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementujte funkci `available`. Tato funkce vrací, kolik bajtů lze ze streamu načíst, nebo -1, pokud je stream kompletní. Pro tuto třídu bude maximální dostupné množství nikdy větší než velikost bloku HTTP klienta. Když tento stream používá HTTP klient, volá tuto funkci, aby zjistil, kolik dat je dostupných, a poté požaduje tolik dat, aby je odeslal do REST API. Nechceme, aby každý blok byl větší než velikost bloku HTTP klienta, takže pokud je dostupné více, vrátí se velikost bloku. Pokud je dostupné méně, vrátí se dostupné množství. Jakmile jsou všechna data streamována, vrátí se -1.

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

1. Implementujte metodu `read`, která vrátí další bajt z bufferu a zvýší pozici. Pokud pozice přesáhne velikost bufferu, buffer se naplní dalším blokem z flash paměti a pozice se resetuje.

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

1. Do hlavičkového souboru `speech_to_text.h` přidejte direktivu pro zahrnutí tohoto nového hlavičkového souboru:

    ```cpp
    #include "flash_stream.h"
    ```

### Úkol - převod řeči na text

1. Řeč může být převedena na text odesláním zvuku do služby rozpoznávání řeči přes REST API. Toto REST API má jiný certifikát než tokenový server, takže přidejte následující kód do hlavičkového souboru `config.h`, abyste definovali tento certifikát:

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

1. Přidejte konstantu do tohoto souboru pro URL služby rozpoznávání řeči bez lokace. Tato URL bude později kombinována s lokací a jazykem pro získání úplné URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Do hlavičkového souboru `speech_to_text.h`, do sekce `private` třídy `SpeechToText`, definujte pole pro WiFi klienta používajícího certifikát služby rozpoznávání řeči:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. V metodě `init` nastavte certifikát na tomto WiFi klientovi:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Do sekce `public` třídy `SpeechToText` přidejte metodu pro převod řeči na text:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Do této metody přidejte následující kód pro vytvoření HTTP klienta používajícího WiFi klienta nakonfigurovaného s certifikátem služby rozpoznávání řeči a používajícího URL služby rozpoznávání řeči nastavenou s lokací a jazykem:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Na připojení je potřeba nastavit některé hlavičky:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Tato hlavička nastavuje autorizaci pomocí přístupového tokenu, formát zvuku pomocí vzorkovací frekvence a nastavuje, že klient očekává výsledek jako JSON.

1. Poté přidejte následující kód pro provedení REST API požadavku:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Tento kód vytvoří `FlashStream` a použije jej pro streamování dat do REST API.

1. Pod tento kód přidejte následující:

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

    Tento kód kontroluje odpovědní kód.

    Pokud je kód 200, což je kód pro úspěch, výsledek je získán, dekódován z JSON a vlastnost `DisplayText` je nastavena do proměnné `text`. Tato vlastnost obsahuje textovou verzi řeči.

    Pokud je kód odpovědi 401, přístupový token vypršel (tyto tokeny platí pouze 10 minut). Je požádán nový přístupový token a požadavek je proveden znovu.

    Jinak je do sériového monitoru odeslána chyba a proměnná `text` zůstane prázdná.

1. Na konec této metody přidejte následující kód pro uzavření HTTP klienta a vrácení textu:

    ```cpp
    httpClient.end();

    return text;
    ```

1. V souboru `main.cpp` zavolejte novou metodu `convertSpeechToText` ve funkci `processAudio` a poté výsledek řeči vypište do sériového monitoru:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Sestavte tento kód, nahrajte jej do svého Wio Terminalu a otestujte jej přes sériový monitor. Jakmile uvidíte `Ready` v sériovém monitoru, stiskněte tlačítko C (to na levé straně, nejblíže k vypínači) a mluvte. 4 sekundy zvuku budou nahrány a poté převedeny na text.

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

> 💁 Tento kód najdete ve složce [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Váš program pro převod řeči na text byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.