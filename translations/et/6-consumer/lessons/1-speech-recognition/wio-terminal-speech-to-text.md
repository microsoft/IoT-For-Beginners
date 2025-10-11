<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-10-11T12:19:06+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "et"
}
-->
# Kõne tekstiks - Wio Terminal

Selles õppetunni osas kirjutad koodi, et muuta salvestatud heli kõne tekstiks, kasutades kõneteenust.

## Saada heli kõneteenusele

Heli saab saata kõneteenusele REST API kaudu. Kõneteenuse kasutamiseks tuleb esmalt taotleda juurdepääsutokenit ja seejärel kasutada seda tokenit REST API-le juurdepääsuks. Need juurdepääsutokenid aeguvad 10 minuti pärast, seega peaks sinu kood neid regulaarselt uuendama, et need oleksid alati ajakohased.

### Ülesanne - juurdepääsutokeni hankimine

1. Ava projekt `smart-timer`, kui see pole veel avatud.

1. Lisa `platformio.ini` faili järgmised teegisõltuvused, et pääseda WiFi-le ja käsitleda JSON-i:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Lisa `config.h` päisefaili järgmine kood:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Asenda `<SSID>` ja `<PASSWORD>` vastavate väärtustega oma WiFi jaoks.

    Asenda `<API_KEY>` oma kõneteenuse ressursi API võtmega. Asenda `<LOCATION>` asukohaga, mida kasutasid kõneteenuse ressursi loomisel.

    Asenda `<LANGUAGE>` keele lokaadi nimega, milles räägid, näiteks `en-GB` inglise keele jaoks või `zn-HK` kantoni keele jaoks. Saad toetatud keelte ja nende lokaadi nimede loendi [Microsofti dokumentatsioonist keele ja hääle toe kohta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    `TOKEN_URL` konstant on tokeni väljastaja URL ilma asukohata. See kombineeritakse hiljem asukohaga, et saada täielik URL.

1. Nagu Custom Visioniga ühenduse loomisel, pead kasutama HTTPS-ühendust, et ühendada tokeni väljastamise teenusega. Lisa `config.h` faili lõppu järgmine kood:

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

    See on sama sertifikaat, mida kasutasid Custom Visioniga ühenduse loomisel.

1. Lisa `main.cpp` faili algusesse WiFi päisefaili ja config päisefaili kaasamine:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Lisa kood WiFi-ga ühenduse loomiseks `main.cpp` faili `setup` funktsiooni kohale:

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

1. Kutsu see funktsioon välja `setup` funktsioonis pärast seda, kui seeriaühendus on loodud:

    ```cpp
    connectWiFi();
    ```

1. Loo `src` kausta uus päisefail nimega `speech_to_text.h`. Lisa sellesse päisefaili järgmine kood:

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

    See sisaldab vajalikke päisefaile HTTP-ühenduse, konfiguratsiooni ja `mic.h` päisefaili jaoks ning defineerib klassi nimega `SpeechToText`, enne kui deklareerib selle klassi eksemplari, mida saab hiljem kasutada.

1. Lisa selle klassi `private` sektsiooni järgmised kaks välja:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` on WiFi klient, mis kasutab HTTPS-i ja mida kasutatakse juurdepääsutokeni hankimiseks. See token salvestatakse `_access_token`-i.

1. Lisa `private` sektsiooni järgmine meetod:

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

    See kood koostab URL-i tokeni väljastaja API jaoks, kasutades kõneressursi asukohta. Seejärel loob `HTTPClient` veebipäringu tegemiseks, seadistades selle kasutama WiFi klienti, mis on konfigureeritud tokeni lõpppunkti sertifikaadiga. API võti määratakse päringu päisesse. Seejärel tehakse POST-päring sertifikaadi hankimiseks, proovides uuesti, kui ilmnevad vead. Lõpuks tagastatakse juurdepääsutoken.

1. Lisa `public` sektsiooni meetod juurdepääsutokeni hankimiseks. Seda on vaja hilisemates õppetundides teksti kõneks muutmiseks.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Lisa `public` sektsiooni `init` meetod, mis seadistab tokeni kliendi:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    See määrab sertifikaadi WiFi kliendile ja seejärel hangib juurdepääsutokeni.

1. Lisa `main.cpp` faili uus päisefail kaasamisdirektiivide hulka:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Initsialiseeri `SpeechToText` klass `setup` funktsiooni lõpus, pärast `mic.init` väljakutset, kuid enne kui `Ready` kirjutatakse seeriamonitori:

    ```cpp
    speechToText.init();
    ```

### Ülesanne - heli lugemine välkmälust

1. Õppetunni varasemas osas salvestati heli välkmällu. See heli tuleb saata kõneteenuse REST API-le, seega tuleb see välkmälust lugeda. Seda ei saa laadida mälupuhvrisse, kuna see oleks liiga suur. `HTTPClient` klass, mis teeb REST-päringuid, saab andmeid voogesitada, kasutades Arduino Streami - klassi, mis saab andmeid väikeste tükkidena laadida ja saata need ükshaaval päringu osana. Iga kord, kui kutsutakse `read` voogesituse puhul, tagastatakse järgmine andmeplokk. Arduino voogesitus saab luua, et lugeda välkmälust. Loo `src` kausta uus fail nimega `flash_stream.h` ja lisa sellesse järgmine kood:

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

    See deklareerib `FlashStream` klassi, mis pärineb Arduino `Stream` klassist. See on abstraktne klass - pärandklassid peavad rakendama mõned meetodid enne, kui klassi saab instantsida, ja need meetodid on selles klassis määratletud.

    ✅ Loe rohkem Arduino voogesituse kohta [Arduino Stream dokumentatsioonist](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Lisa `private` sektsiooni järgmised väljad:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    See määratleb ajutise puhvri, et salvestada andmeid, mis on loetud välkmälust, koos väljadega, mis salvestavad praeguse positsiooni puhvrist lugemisel, praeguse aadressi välkmälust lugemiseks ja välkmälu seadme.

1. Lisa `private` sektsiooni järgmine meetod:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    See kood loeb välkmälust praegusel aadressil ja salvestab andmed puhvris. Seejärel suurendab aadressi, nii et järgmine väljakutse loeb järgmise mäluploki. Puhvri suurus põhineb suurimal tükil, mida `HTTPClient` REST API-le korraga saadab.

    > 💁 Välkmälu kustutamine tuleb teha terasuuruse järgi, lugemine seevastu ei pea.

1. Lisa selle klassi `public` sektsiooni konstruktor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    See konstruktor seadistab kõik väljad, et alustada lugemist välkmälu ploki algusest, ja laadib esimese andmeploki puhvris.

1. Rakenda `write` meetod. See voogesitus loeb ainult andmeid, seega see ei tee midagi ja tagastab 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Rakenda `peek` meetod. See tagastab andmed praegusel positsioonil, liigutamata voogesitust edasi. `peek` korduv väljakutsumine tagastab alati samad andmed, kui voogesitusest pole andmeid loetud.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Rakenda `available` funktsioon. See tagastab, kui palju baite saab voogesitusest lugeda, või -1, kui voogesitus on lõppenud. Selle klassi puhul on maksimaalne saadav suurus mitte rohkem kui HTTPClienti tüki suurus. Kui voogesitust kasutatakse HTTP kliendis, kutsub see funktsiooni, et näha, kui palju andmeid on saadaval, ja seejärel taotleb nii palju andmeid, et saata REST API-le. Me ei taha, et iga tükk oleks suurem kui HTTP kliendi tüki suurus, seega kui rohkem on saadaval, tagastatakse tüki suurus. Kui vähem, siis tagastatakse saadaval olev suurus. Kui kõik andmed on voogesitatud, tagastatakse -1.

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

1. Rakenda `read` meetod, et tagastada järgmine bait puhvrist, suurendades positsiooni. Kui positsioon ületab puhvri suuruse, täidetakse puhver järgmise plokiga välkmälust ja positsioon lähtestatakse.

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

1. Lisa `speech_to_text.h` päisefaili kaasamisdirektiiv selle uue päisefaili jaoks:

    ```cpp
    #include "flash_stream.h"
    ```

### Ülesanne - kõne tekstiks muutmine

1. Kõne saab tekstiks muuta, saates heli kõneteenuse REST API-le. Selle REST API-l on erinev sertifikaat kui tokeni väljastajal, seega lisa `config.h` päisefaili järgmine kood, et määratleda see sertifikaat:

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

1. Lisa sellele failile konstant kõne URL-i jaoks ilma asukohata. See kombineeritakse hiljem asukoha ja keelega, et saada täielik URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` päisefailis, `SpeechToText` klassi `private` sektsioonis, defineeri väli WiFi kliendi jaoks, mis kasutab kõne sertifikaati:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` meetodis määra sertifikaat sellele WiFi kliendile:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Lisa `SpeechToText` klassi `public` sektsiooni järgmine kood, et defineerida meetod kõne tekstiks muutmiseks:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Lisa sellele meetodile järgmine kood, et luua HTTP klient, kasutades WiFi klienti, mis on konfigureeritud kõne sertifikaadiga, ja kasutades kõne URL-i, mis on määratud asukoha ja keelega:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Mõned päised tuleb ühendusel määrata:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    See määrab päised autoriseerimiseks, kasutades juurdepääsutokenit, audio formaati, kasutades näidissagedust, ja määrab, et klient ootab tulemust JSON-is.

1. Pärast seda lisa järgmine kood REST API päringu tegemiseks:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    See loob `FlashStream` ja kasutab seda andmete voogesitamiseks REST API-le.

1. Selle alla lisa järgmine kood:

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

    See kood kontrollib vastusekoodi.

    Kui see on 200, mis on edukuse kood, siis tulemus hangitakse, dekodeeritakse JSON-ist ja `DisplayText` omadus määratakse `text` muutujasse. See on omadus, milles kõne tekstiversioon tagastatakse.

    Kui vastusekood on 401, siis juurdepääsutoken on aegunud (need tokenid kehtivad ainult 10 minutit). Uus juurdepääsutoken taotletakse ja päring tehakse uuesti.

    Vastasel juhul saadetakse veateade seeriamonitori ja `text` jäetakse tühjaks.

1. Lisa selle meetodi lõppu järgmine kood, et sulgeda HTTP klient ja tagastada tekst:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp` failis kutsu `processAudio` funktsioonis välja uus `convertSpeechToText` meetod ja logi kõne seeriamonitori:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Koosta see kood, laadi see oma Wio Terminali ja testi seda seeriamonitori kaudu. Kui näed seeriamonitoris `Ready`, vajuta C nuppu (vasakpoolne nupp, mis on kõige lähemal toitelülitile) ja räägi. 4 sekundit heli salvestatakse ja seejärel muudetakse tekstiks.

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

> 💁 Selle koodi leiad kaustast [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Sinu kõne tekstiks programm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.