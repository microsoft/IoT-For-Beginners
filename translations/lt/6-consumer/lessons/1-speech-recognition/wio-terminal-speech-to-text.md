<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T19:30:01+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "lt"
}
-->
# Kalbos pavertimas tekstu - Wio Terminal

Šioje pamokos dalyje rašysite kodą, kuris užfiksuotą garsą pavers tekstu naudodamas kalbos paslaugą.

## Siųskite garsą į kalbos paslaugą

Garsą galima siųsti į kalbos paslaugą naudojant REST API. Norint naudotis kalbos paslauga, pirmiausia reikia gauti prieigos žetoną, o tada naudoti tą žetoną REST API pasiekimui. Šie prieigos žetonai galioja tik 10 minučių, todėl jūsų kodas turėtų reguliariai juos atnaujinti, kad jie visada būtų galiojantys.

### Užduotis - gauti prieigos žetoną

1. Atidarykite projektą `smart-timer`, jei jis dar neatidarytas.

1. Pridėkite šias bibliotekų priklausomybes į `platformio.ini` failą, kad galėtumėte naudotis WiFi ir apdoroti JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Pridėkite šį kodą į `config.h` antraštės failą:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Pakeiskite `<SSID>` ir `<PASSWORD>` į atitinkamas jūsų WiFi reikšmes.

    Pakeiskite `<API_KEY>` į jūsų kalbos paslaugos ištekliaus API raktą. Pakeiskite `<LOCATION>` į vietą, kurią nurodėte kurdami kalbos paslaugos išteklį.

    Pakeiskite `<LANGUAGE>` į kalbos, kuria kalbėsite, lokalės pavadinimą, pavyzdžiui, `en-GB` anglų kalbai arba `zn-HK` kantoniečių kalbai. Palaikomų kalbų ir jų lokalės pavadinimų sąrašą galite rasti [Microsoft dokumentacijoje apie kalbų ir balsų palaikymą](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstantą `TOKEN_URL` sudaro žetono išdavimo paslaugos URL be vietos. Vėliau tai bus sujungta su vieta, kad būtų gautas pilnas URL.

1. Kaip ir jungiantis prie Custom Vision, jums reikės naudoti HTTPS ryšį, kad prisijungtumėte prie žetono išdavimo paslaugos. Pridėkite šį kodą į `config.h` failo pabaigą:

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

    Tai tas pats sertifikatas, kurį naudojote jungdamiesi prie Custom Vision.

1. Pridėkite `WiFi` antraštės failo ir `config` antraštės failo įtraukimą į `main.cpp` failo viršų:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Pridėkite kodą, kuris prisijungia prie WiFi, į `main.cpp` virš `setup` funkcijos:

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

1. Iškvieskite šią funkciją iš `setup` funkcijos po to, kai bus užmegztas serijinis ryšys:

    ```cpp
    connectWiFi();
    ```

1. Sukurkite naują antraštės failą `src` aplanke, pavadintą `speech_to_text.h`. Šiame antraštės faile pridėkite šį kodą:

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

    Tai apima būtinus antraštės failus HTTP ryšiui, konfigūracijai ir `mic.h` antraštės failą, taip pat apibrėžia klasę `SpeechToText`, prieš paskelbiant šios klasės egzempliorių, kuris bus naudojamas vėliau.

1. Pridėkite šiuos 2 laukus į šios klasės `private` sekciją:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` yra WiFi klientas, naudojantis HTTPS ir bus naudojamas prieigos žetonui gauti. Šis žetonas bus saugomas `_access_token`.

1. Pridėkite šį metodą į `private` sekciją:

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

    Šis kodas sukuria URL žetono išdavimo API, naudodamas kalbos ištekliaus vietą. Tada jis sukuria `HTTPClient`, kad atliktų žiniatinklio užklausą, nustatydamas jį naudoti WiFi klientą, sukonfigūruotą su žetono galinių taškų sertifikatu. Jis nustato API raktą kaip antraštę užklausai. Tada jis atlieka POST užklausą, kad gautų sertifikatą, pakartodamas, jei gauna klaidų. Galiausiai grąžinamas prieigos žetonas.

1. Į `public` sekciją pridėkite metodą, skirtą gauti prieigos žetoną. Jis bus reikalingas vėlesnėse pamokose tekstui paversti į kalbą.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Į `public` sekciją pridėkite `init` metodą, kuris nustato žetono klientą:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Tai nustato sertifikatą WiFi klientui, tada gauna prieigos žetoną.

1. `main.cpp` faile pridėkite šį naują antraštės failą į įtraukimų direktyvas:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inicializuokite `SpeechToText` klasę `setup` funkcijos pabaigoje, po `mic.init` iškvietimo, bet prieš `Ready` išvedimą į serijinį monitorių:

    ```cpp
    speechToText.init();
    ```

### Užduotis - skaityti garsą iš flash atminties

1. Ankstesnėje šios pamokos dalyje garsas buvo įrašytas į flash atmintį. Šis garsas turės būti siunčiamas į Kalbos paslaugų REST API, todėl jį reikia perskaityti iš flash atminties. Jo negalima įkelti į atminties buferį, nes jis būtų per didelis. `HTTPClient` klasė, kuri atlieka REST užklausas, gali perduoti duomenis naudodama Arduino Stream - klasę, kuri gali įkelti duomenis mažais gabalėliais, siųsdama juos po vieną kaip užklausos dalį. Kiekvieną kartą, kai iškviečiate `read` ant srauto, jis grąžina kitą duomenų bloką. Arduino srautas gali būti sukurtas, kad galėtų skaityti iš flash atminties. Sukurkite naują failą, pavadintą `flash_stream.h`, `src` aplanke, ir pridėkite šį kodą:

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

    Tai deklaruoja `FlashStream` klasę, paveldinčią iš Arduino `Stream` klasės. Tai yra abstrakti klasė - paveldinčios klasės turi įgyvendinti kelis metodus, kol klasė gali būti instancijuota, ir šie metodai yra apibrėžti šioje klasėje.

    ✅ Daugiau apie Arduino srautus skaitykite [Arduino Stream dokumentacijoje](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Pridėkite šiuos laukus į `private` sekciją:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Tai apibrėžia laikiną buferį duomenims, skaitomiems iš flash atminties, saugoti, kartu su laukais, skirtais dabartinei pozicijai buferyje ir dabartiniam adresui flash atmintyje saugoti.

1. `private` sekcijoje pridėkite šį metodą:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Šis kodas skaito iš flash atminties dabartiniu adresu ir saugo duomenis buferyje. Tada jis padidina adresą, kad kitas iškvietimas skaitytų kitą atminties bloką. Buferio dydis nustatytas pagal didžiausią gabalą, kurį `HTTPClient` siunčia REST API vienu metu.

    > 💁 Flash atminties trynimas turi būti atliekamas naudojant grūdų dydį, tačiau skaitymas to nereikalauja.

1. `public` sekcijoje šios klasės pridėkite konstruktorių:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Šis konstruktorius nustato visus laukus, kad pradėtų skaityti nuo flash atminties bloko pradžios, ir įkelia pirmą duomenų gabalą į buferį.

1. Įgyvendinkite `write` metodą. Šis srautas tik skaitys duomenis, todėl šis metodas nieko nedaro ir grąžina 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Įgyvendinkite `peek` metodą. Šis metodas grąžina duomenis dabartinėje pozicijoje, nejudindamas srauto į priekį. Keli `peek` iškvietimai visada grąžins tuos pačius duomenis, jei iš srauto nebus skaitoma.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Įgyvendinkite `available` funkciją. Ši funkcija grąžina, kiek baitų galima skaityti iš srauto, arba -1, jei srautas baigtas. Šiai klasei maksimalus galimas dydis neviršys `HTTPClient` gabalo dydžio. Kai šis srautas naudojamas HTTP kliente, jis iškviečia šią funkciją, kad pamatytų, kiek duomenų yra prieinama, tada prašo tiek duomenų siųsti REST API. Nenorime, kad kiekvienas gabalas būtų didesnis nei HTTP kliento gabalo dydis, todėl jei yra daugiau duomenų, grąžinamas gabalo dydis. Jei mažiau, grąžinama, kiek yra prieinama. Kai visi duomenys perduoti, grąžinama -1.

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

1. Įgyvendinkite `read` metodą, kad grąžintų kitą baitą iš buferio, padidindamas poziciją. Jei pozicija viršija buferio dydį, jis užpildo buferį kitu bloku iš flash atminties ir atstato poziciją.

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

1. `speech_to_text.h` antraštės faile pridėkite įtraukimo direktyvą šiam naujam antraštės failui:

    ```cpp
    #include "flash_stream.h"
    ```

### Užduotis - paversti kalbą tekstu

1. Kalba gali būti paversta tekstu siunčiant garsą į Kalbos paslaugą per REST API. Šis REST API turi kitą sertifikatą nei žetono išdavėjas, todėl pridėkite šį kodą į `config.h` antraštės failą, kad apibrėžtumėte šį sertifikatą:

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

1. Pridėkite konstantą šiame faile kalbos URL be vietos. Tai bus sujungta su vieta ir kalba vėliau, kad būtų gautas pilnas URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` antraštės faile, `private` sekcijoje `SpeechToText` klasės, apibrėžkite lauką WiFi klientui, naudojančiam kalbos sertifikatą:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` metode nustatykite šio WiFi kliento sertifikatą:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Pridėkite šį kodą į `public` sekciją `SpeechToText` klasės, kad apibrėžtumėte metodą kalbai paversti tekstu:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Pridėkite šį kodą į šį metodą, kad sukurtumėte HTTP klientą, naudojantį WiFi klientą, sukonfigūruotą su kalbos sertifikatu, ir naudodami kalbos URL, nustatytą su vieta ir kalba:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Kai kurios antraštės turi būti nustatytos ryšiui:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Tai nustato antraštes autorizacijai naudojant prieigos žetoną, garso formatui naudojant mėginių ėmimo dažnį ir nustato, kad klientas tikisi rezultato JSON formatu.

1. Po to pridėkite šį kodą, kad atliktumėte REST API užklausą:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Tai sukuria `FlashStream` ir naudoja jį duomenims perduoti REST API.

1. Po to pridėkite šį kodą:

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

    Šis kodas tikrina atsakymo kodą.

    Jei jis yra 200, sėkmės kodas, tada rezultatas gaunamas, dekoduojamas iš JSON, ir `DisplayText` savybė nustatoma į `text` kintamąjį. Tai yra savybė, kurioje grąžinamas kalbos tekstinis variantas.

    Jei atsakymo kodas yra 401, tada prieigos žetonas pasibaigė (šie žetonai galioja tik 10 minučių). Gaunamas naujas prieigos žetonas ir užklausa atliekama dar kartą.

    Kitu atveju klaida siunčiama į serijinį monitorių, o `text` lieka tuščias.

1. Pridėkite šį kodą šio metodo pabaigoje, kad uždarytumėte HTTP klientą ir grąžintumėte tekstą:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp` faile iškvieskite šį naują `convertSpeechToText` metodą `processAudio` funkcijoje, tada išveskite kalbą į serijinį monitorių:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Sukurkite šį kodą, įkelkite jį į savo Wio Terminal ir išbandykite per serijinį monitorių. Kai serijiniame monitore pamatysite `Ready`, paspauskite C mygtuką (kairėje pusėje, arčiausiai maitinimo jungiklio) ir kalbėkite. 4 sekundės garso bus užfiksuotos, tada paverstos tekstu.

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

> 💁 Šį kodą galite rasti [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) aplanke.

😀 Jūsų kalbos pavertimo tekstu programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipiame dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudotis profesionalių vertėjų paslaugomis. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.