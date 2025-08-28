<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T13:02:42+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "hr"
}
-->
# Pretvaranje govora u tekst - Wio Terminal

U ovom dijelu lekcije napisat ćete kod za pretvaranje govora iz snimljenog zvuka u tekst koristeći uslugu za govor.

## Slanje zvuka usluzi za govor

Zvuk se može poslati usluzi za govor koristeći REST API. Za korištenje usluge za govor prvo morate zatražiti pristupni token, a zatim koristiti taj token za pristup REST API-ju. Ovi pristupni tokeni istječu nakon 10 minuta, pa vaš kod treba redovito zatražiti nove kako bi uvijek bili ažurirani.

### Zadatak - dobivanje pristupnog tokena

1. Otvorite projekt `smart-timer` ako već nije otvoren.

1. Dodajte sljedeće bibliotečke ovisnosti u datoteku `platformio.ini` za pristup WiFi-u i rukovanje JSON-om:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Dodajte sljedeći kod u zaglavnu datoteku `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Zamijenite `<SSID>` i `<PASSWORD>` odgovarajućim vrijednostima za vaš WiFi.

    Zamijenite `<API_KEY>` API ključem za resurs vaše usluge za govor. Zamijenite `<LOCATION>` lokacijom koju ste koristili prilikom stvaranja resursa usluge za govor.

    Zamijenite `<LANGUAGE>` nazivom lokaliteta jezika kojim ćete govoriti, na primjer `en-GB` za engleski ili `zn-HK` za kantonski. Popis podržanih jezika i njihovih lokaliteta možete pronaći u [dokumentaciji o podršci za jezik i glas na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstantna `TOKEN_URL` je URL izdavatelja tokena bez lokacije. Ovo će se kasnije kombinirati s lokacijom kako bi se dobio puni URL.

1. Kao i kod povezivanja s Custom Vision, trebate koristiti HTTPS vezu za povezivanje s uslugom izdavanja tokena. Na kraj datoteke `config.h` dodajte sljedeći kod:

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

    Ovo je isti certifikat koji ste koristili prilikom povezivanja s Custom Vision.

1. Dodajte uključivanje zaglavne datoteke za WiFi i zaglavne datoteke za konfiguraciju na vrh datoteke `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Dodajte kod za povezivanje s WiFi-jem u datoteku `main.cpp` iznad funkcije `setup`:

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

1. Pozovite ovu funkciju iz funkcije `setup` nakon što je serijska veza uspostavljena:

    ```cpp
    connectWiFi();
    ```

1. Kreirajte novu zaglavnu datoteku u mapi `src` pod nazivom `speech_to_text.h`. U ovu zaglavnu datoteku dodajte sljedeći kod:

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

    Ovo uključuje neke potrebne zaglavne datoteke za HTTP vezu, konfiguraciju i zaglavnu datoteku `mic.h`, te definira klasu pod nazivom `SpeechToText`, prije nego što deklarira instancu te klase koja se može koristiti kasnije.

1. Dodajte sljedeća 2 polja u privatni dio ove klase:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` je WiFi klijent koji koristi HTTPS i bit će korišten za dobivanje pristupnog tokena. Taj token će se zatim pohraniti u `_access_token`.

1. Dodajte sljedeću metodu u privatni dio:

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

    Ovaj kod gradi URL za API izdavatelja tokena koristeći lokaciju resursa za govor. Zatim stvara `HTTPClient` za web zahtjev, postavljajući ga da koristi WiFi klijent konfiguriran s certifikatom za krajnje točke tokena. Postavlja API ključ kao zaglavlje za poziv. Zatim izvršava POST zahtjev za dobivanje certifikata, ponavljajući ako dobije bilo kakve greške. Na kraju se vraća pristupni token.

1. U javni dio dodajte metodu za dobivanje pristupnog tokena. Ovo će biti potrebno u kasnijim lekcijama za pretvaranje teksta u govor.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. U javni dio dodajte metodu `init` koja postavlja klijent za token:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Ovo postavlja certifikat na WiFi klijent, a zatim dobiva pristupni token.

1. U datoteci `main.cpp` dodajte ovu novu zaglavnu datoteku u direktive za uključivanje:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inicijalizirajte klasu `SpeechToText` na kraju funkcije `setup`, nakon poziva `mic.init`, ali prije nego što se `Ready` napiše na serijski monitor:

    ```cpp
    speechToText.init();
    ```

### Zadatak - čitanje zvuka iz flash memorije

1. U ranijem dijelu ove lekcije, zvuk je snimljen u flash memoriju. Taj zvuk će trebati poslati REST API-ju usluge za govor, pa ga treba pročitati iz flash memorije. Ne može se učitati u memorijski međuspremnik jer bi bio prevelik. Klasa `HTTPClient` koja izvršava REST pozive može strujati podatke koristeći Arduino Stream - klasu koja može učitati podatke u malim dijelovima, šaljući dijelove jedan po jedan kao dio zahtjeva. Svaki put kad pozovete `read` na streamu, vraća se sljedeći blok podataka. Može se stvoriti Arduino stream koji može čitati iz flash memorije. Kreirajte novu datoteku pod nazivom `flash_stream.h` u mapi `src` i dodajte sljedeći kod u nju:

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

    Ovo deklarira klasu `FlashStream`, izvedenu iz Arduino klase `Stream`. Ovo je apstraktna klasa - izvedene klase moraju implementirati nekoliko metoda prije nego što se klasa može instancirati, a te metode su definirane u ovoj klasi.

    ✅ Više o Arduino Streamovima pročitajte u [dokumentaciji o Arduino Streamovima](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Dodajte sljedeća polja u privatni dio:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Ovo definira privremeni međuspremnik za pohranu podataka pročitanih iz flash memorije, zajedno s poljima za pohranu trenutne pozicije prilikom čitanja iz međuspremnika, trenutne adrese za čitanje iz flash memorije i uređaja flash memorije.

1. U privatni dio dodajte sljedeću metodu:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Ovaj kod čita iz flash memorije na trenutnoj adresi i pohranjuje podatke u međuspremnik. Zatim povećava adresu, tako da sljedeći poziv čita sljedeći blok memorije. Veličina međuspremnika temelji se na najvećem dijelu koji će `HTTPClient` poslati REST API-ju odjednom.

    > 💁 Brisanje flash memorije mora se obaviti pomoću veličine zrna, dok čitanje ne mora.

1. U javni dio ove klase dodajte konstruktor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Ovaj konstruktor postavlja sva polja za početak čitanja od početka bloka flash memorije i učitava prvi dio podataka u međuspremnik.

1. Implementirajte metodu `write`. Ovaj stream će samo čitati podatke, pa ovo može ne raditi ništa i vratiti 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementirajte metodu `peek`. Ovo vraća podatke na trenutnoj poziciji bez pomicanja streama. Pozivanje `peek` više puta uvijek će vratiti iste podatke sve dok se ne pročitaju podaci iz streama.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementirajte funkciju `available`. Ovo vraća koliko bajtova se može pročitati iz streama, ili -1 ako je stream završen. Za ovu klasu, maksimalno dostupno neće biti više od veličine dijela HTTP klijenta. Kada ovaj stream koristi HTTP klijent, poziva ovu funkciju da vidi koliko je podataka dostupno, a zatim zatraži toliko podataka za slanje REST API-ju. Ne želimo da svaki dio bude veći od veličine dijela HTTP klijenta, pa ako je dostupno više od toga, vraća se veličina dijela. Ako je manje, vraća se ono što je dostupno. Kada su svi podaci strujani, vraća se -1.

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

1. Implementirajte metodu `read` za vraćanje sljedećeg bajta iz međuspremnika, povećavajući poziciju. Ako pozicija premaši veličinu međuspremnika, međuspremnik se popunjava sljedećim blokom iz flash memorije i pozicija se resetira.

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

1. U zaglavnu datoteku `speech_to_text.h` dodajte direktivu za uključivanje ove nove zaglavne datoteke:

    ```cpp
    #include "flash_stream.h"
    ```

### Zadatak - pretvaranje govora u tekst

1. Govor se može pretvoriti u tekst slanjem zvuka usluzi za govor putem REST API-ja. Ovaj REST API ima drugačiji certifikat od izdavatelja tokena, pa dodajte sljedeći kod u zaglavnu datoteku `config.h` za definiranje ovog certifikata:

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

1. Dodajte konstantu u ovu datoteku za URL govora bez lokacije. Ovo će se kombinirati s lokacijom i jezikom kasnije kako bi se dobio puni URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. U zaglavnoj datoteci `speech_to_text.h`, u privatnom dijelu klase `SpeechToText`, definirajte polje za WiFi klijent koristeći certifikat za govor:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. U metodi `init`, postavite certifikat na ovaj WiFi klijent:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Dodajte sljedeći kod u javni dio klase `SpeechToText` za definiranje metode za pretvaranje govora u tekst:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Dodajte sljedeći kod u ovu metodu za stvaranje HTTP klijenta koristeći WiFi klijent konfiguriran s certifikatom za govor i koristeći URL govora postavljen s lokacijom i jezikom:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Potrebno je postaviti neka zaglavlja na vezu:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Ovo postavlja zaglavlja za autorizaciju koristeći pristupni token, audio format koristeći uzorkovanje, i postavlja da klijent očekuje rezultat kao JSON.

1. Nakon ovoga, dodajte sljedeći kod za izvršavanje REST API poziva:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Ovo stvara `FlashStream` i koristi ga za strujanje podataka REST API-ju.

1. Ispod ovoga, dodajte sljedeći kod:

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

    Ovaj kod provjerava kod odgovora.

    Ako je 200, kod za uspjeh, tada se rezultat dohvaća, dekodira iz JSON-a, i svojstvo `DisplayText` postavlja u varijablu `text`. Ovo je svojstvo u kojem se vraća tekstualna verzija govora.

    Ako je kod odgovora 401, tada je pristupni token istekao (ovi tokeni traju samo 10 minuta). Zatraži se novi pristupni token i poziv se ponovno izvršava.

    Inače, greška se šalje na serijski monitor, a `text` ostaje prazan.

1. Dodajte sljedeći kod na kraj ove metode za zatvaranje HTTP klijenta i vraćanje teksta:

    ```cpp
    httpClient.end();

    return text;
    ```

1. U datoteci `main.cpp` pozovite ovu novu metodu `convertSpeechToText` u funkciji `processAudio`, a zatim zabilježite govor na serijski monitor:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Izgradite ovaj kod, učitajte ga na svoj Wio Terminal i testirajte ga putem serijskog monitora. Kada vidite `Ready` na serijskom monitoru, pritisnite C gumb (onaj na lijevoj strani, najbliži prekidaču za napajanje) i govorite. Snimit će se 4 sekunde zvuka, a zatim će se pretvoriti u tekst.

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

> 💁 Ovaj kod možete pronaći u mapi [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Vaš program za pretvaranje govora u tekst bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.