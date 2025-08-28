<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T13:03:19+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "sl"
}
-->
# Pretvorba govora v besedilo - Wio Terminal

V tem delu lekcije boste napisali kodo za pretvorbo govora v zajetem zvoku v besedilo z uporabo storitve za govor.

## Pošlji zvok storitvi za govor

Zvok lahko pošljete storitvi za govor prek REST API-ja. Za uporabo storitve za govor morate najprej pridobiti dostopni žeton, nato pa uporabiti ta žeton za dostop do REST API-ja. Ti dostopni žetoni potečejo po 10 minutah, zato mora vaša koda redno pridobivati nove žetone, da zagotovi, da so vedno posodobljeni.

### Naloga - pridobite dostopni žeton

1. Odprite projekt `smart-timer`, če še ni odprt.

1. Dodajte naslednje knjižnične odvisnosti v datoteko `platformio.ini`, da omogočite dostop do WiFi-ja in obdelavo JSON-a:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Dodajte naslednjo kodo v glavno datoteko `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Zamenjajte `<SSID>` in `<PASSWORD>` z ustreznimi vrednostmi za vaš WiFi.

    Zamenjajte `<API_KEY>` z API ključem za vašo storitev za govor. Zamenjajte `<LOCATION>` z lokacijo, ki ste jo uporabili pri ustvarjanju vira storitve za govor.

    Zamenjajte `<LANGUAGE>` z imenom lokalizacije jezika, v katerem boste govorili, na primer `en-GB` za angleščino ali `zn-HK` za kantonščino. Seznam podprtih jezikov in njihovih lokalizacijskih imen najdete v [dokumentaciji o podpori jezika in glasov na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstanta `TOKEN_URL` je URL izdajatelja žetonov brez lokacije. Ta bo kasneje združen z lokacijo, da dobite celoten URL.

1. Tako kot pri povezovanju s Custom Vision, boste morali uporabiti HTTPS povezavo za povezavo s storitvijo za izdajo žetonov. Na konec datoteke `config.h` dodajte naslednjo kodo:

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

    To je isti certifikat, ki ste ga uporabili pri povezovanju s Custom Vision.

1. Na vrh datoteke `main.cpp` dodajte vključitev za WiFi glavno datoteko in datoteko `config.h`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Dodajte kodo za povezavo z WiFi v datoteko `main.cpp` nad funkcijo `setup`:

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

1. Pokličite to funkcijo iz funkcije `setup` po vzpostavitvi serijske povezave:

    ```cpp
    connectWiFi();
    ```

1. Ustvarite novo glavno datoteko v mapi `src`, imenovano `speech_to_text.h`. V to glavno datoteko dodajte naslednjo kodo:

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

    To vključuje nekaj potrebnih glavnih datotek za HTTP povezavo, konfiguracijo in glavno datoteko `mic.h`, ter definira razred `SpeechToText`, preden deklarira instanco tega razreda, ki jo lahko kasneje uporabite.

1. Dodajte naslednja dva polja v razdelek `private` tega razreda:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` je WiFi odjemalec, ki uporablja HTTPS in bo uporabljen za pridobitev dostopnega žetona. Ta žeton bo nato shranjen v `_access_token`.

1. Dodajte naslednjo metodo v razdelek `private`:

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

    Ta koda sestavi URL za API izdajatelja žetonov z uporabo lokacije vira za govor. Nato ustvari `HTTPClient` za izvedbo spletne zahteve, ki jo nastavi za uporabo WiFi odjemalca, konfiguriranega s certifikatom za končne točke žetonov. API ključ nastavi kot glavo za klic. Nato izvede POST zahtevo za pridobitev certifikata, pri čemer ponovi zahtevo, če pride do napak. Na koncu se vrne dostopni žeton.

1. V razdelek `public` dodajte metodo za pridobitev dostopnega žetona. Ta bo potrebna v kasnejših lekcijah za pretvorbo besedila v govor.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. V razdelek `public` dodajte metodo `init`, ki nastavi odjemalca za žetone:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Ta nastavi certifikat na WiFi odjemalcu, nato pridobi dostopni žeton.

1. V datoteki `main.cpp` dodajte to novo glavno datoteko v direktive za vključitev:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inicializirajte razred `SpeechToText` na koncu funkcije `setup`, po klicu `mic.init`, vendar pred zapisom `Ready` v serijski monitor:

    ```cpp
    speechToText.init();
    ```

### Naloga - preberite zvok iz flash pomnilnika

1. V prejšnjem delu te lekcije je bil zvok posnet v flash pomnilnik. Ta zvok bo treba poslati REST API-ju storitve za govor, zato ga je treba prebrati iz flash pomnilnika. Ne more biti naložen v pomnilniški medpomnilnik, saj bi bil prevelik. Razred `HTTPClient`, ki izvaja REST klice, lahko pretaka podatke z uporabo Arduino Stream - razreda, ki lahko nalaga podatke v majhnih kosih in jih pošilja enega za drugim kot del zahteve. Vsakič, ko pokličete `read` na streamu, vrne naslednji blok podatkov. Arduino stream je mogoče ustvariti, da bere iz flash pomnilnika. Ustvarite novo datoteko, imenovano `flash_stream.h`, v mapi `src` in vanjo dodajte naslednjo kodo:

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

    To deklarira razred `FlashStream`, ki izhaja iz Arduino razreda `Stream`. To je abstraktni razred - izpeljani razredi morajo implementirati nekaj metod, preden je mogoče razred instancirati, te metode pa so definirane v tem razredu.

    ✅ Več o Arduino Streams si preberite v [Arduino Stream dokumentaciji](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Dodajte naslednja polja v razdelek `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    To definira začasni medpomnilnik za shranjevanje podatkov, prebranih iz flash pomnilnika, skupaj s polji za shranjevanje trenutnega položaja pri branju iz medpomnilnika, trenutnega naslova za branje iz flash pomnilnika in naprave flash pomnilnika.

1. V razdelek `private` dodajte naslednjo metodo:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Ta koda bere iz flash pomnilnika na trenutnem naslovu in shranjuje podatke v medpomnilnik. Nato poveča naslov, tako da naslednji klic prebere naslednji blok pomnilnika. Medpomnilnik je velik glede na največji kos, ki ga bo `HTTPClient` poslal REST API-ju naenkrat.

    > 💁 Brisanje flash pomnilnika je treba opraviti z velikostjo zrna, branje pa ne.

1. V razdelek `public` tega razreda dodajte konstruktor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Ta konstruktor nastavi vsa polja za začetek branja od začetka bloka flash pomnilnika in naloži prvi kos podatkov v medpomnilnik.

1. Implementirajte metodo `write`. Ta stream bo samo bral podatke, zato lahko ta metoda ne naredi ničesar in vrne 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementirajte metodo `peek`. Ta vrne podatke na trenutnem položaju, ne da bi premaknila stream naprej. Večkratni klici metode `peek` bodo vedno vrnili iste podatke, dokler se iz streama ne preberejo podatki.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementirajte funkcijo `available`. Ta vrne, koliko bajtov je mogoče prebrati iz streama, ali -1, če je stream končan. Za ta razred bo največje število razpoložljivih bajtov največ velikost kosa HTTP odjemalca. Ko ta stream uporablja HTTP odjemalec, pokliče to funkcijo, da vidi, koliko podatkov je na voljo, nato zahteva toliko podatkov za pošiljanje REST API-ju. Ne želimo, da je vsak kos večji od velikosti kosa HTTP odjemalca, zato če je na voljo več, se vrne velikost kosa. Če je na voljo manj, se vrne, kar je na voljo. Ko so vsi podatki pretakani, se vrne -1.

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

1. Implementirajte metodo `read`, da vrne naslednji bajt iz medpomnilnika, pri čemer poveča položaj. Če položaj preseže velikost medpomnilnika, napolni medpomnilnik z naslednjim blokom iz flash pomnilnika in ponastavi položaj.

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

1. V glavni datoteki `speech_to_text.h` dodajte direktivo za vključitev te nove glavne datoteke:

    ```cpp
    #include "flash_stream.h"
    ```

### Naloga - pretvorite govor v besedilo

1. Govor je mogoče pretvoriti v besedilo s pošiljanjem zvoka storitvi za govor prek REST API-ja. Ta REST API ima drugačen certifikat kot izdajatelj žetonov, zato dodajte naslednjo kodo v glavno datoteko `config.h`, da definirate ta certifikat:

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

1. Dodajte konstanto v to datoteko za URL govora brez lokacije. Ta bo kasneje združen z lokacijo in jezikom, da dobite celoten URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. V glavni datoteki `speech_to_text.h`, v razdelku `private` razreda `SpeechToText`, definirajte polje za WiFi odjemalca, ki uporablja certifikat za govor:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. V metodi `init` nastavite certifikat na tem WiFi odjemalcu:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Dodajte naslednjo kodo v razdelek `public` razreda `SpeechToText`, da definirate metodo za pretvorbo govora v besedilo:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Dodajte naslednjo kodo v to metodo, da ustvarite HTTP odjemalca z uporabo WiFi odjemalca, konfiguriranega s certifikatom za govor, in z uporabo URL-ja govora, nastavljenega z lokacijo in jezikom:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Nekatere glave je treba nastaviti na povezavi:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    To nastavi glave za avtorizacijo z uporabo dostopnega žetona, format zvoka z uporabo vzorčne frekvence in nastavi, da odjemalec pričakuje rezultat kot JSON.

1. Po tem dodajte naslednjo kodo za izvedbo REST API klica:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    To ustvari `FlashStream` in ga uporabi za pretakanje podatkov v REST API.

1. Pod to kodo dodajte naslednjo kodo:

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

    Ta koda preveri odzivno kodo.

    Če je 200, koda za uspeh, se rezultat pridobi, dekodira iz JSON-a, in lastnost `DisplayText` se nastavi v spremenljivko `text`. To je lastnost, v kateri je vrnjena besedilna različica govora.

    Če je odzivna koda 401, je dostopni žeton potekel (ti žetoni trajajo le 10 minut). Pridobi se nov dostopni žeton, nato se klic ponovi.

    V nasprotnem primeru se napaka pošlje v serijski monitor, spremenljivka `text` pa ostane prazna.

1. Dodajte naslednjo kodo na konec te metode, da zaprete HTTP odjemalca in vrnete besedilo:

    ```cpp
    httpClient.end();

    return text;
    ```

1. V datoteki `main.cpp` pokličite to novo metodo `convertSpeechToText` v funkciji `processAudio`, nato pa zapišite govor v serijski monitor:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Sestavite to kodo, naložite jo na vaš Wio Terminal in jo preizkusite prek serijskega monitorja. Ko vidite `Ready` v serijskem monitorju, pritisnite gumb C (tisti na levi strani, najbližje stikalu za vklop), in govorite. 4 sekunde zvoka bodo zajete, nato pa pretvorjene v besedilo.

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

> 💁 To kodo najdete v mapi [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Vaš program za pretvorbo govora v besedilo je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve AI za prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.