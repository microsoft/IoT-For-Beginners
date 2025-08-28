<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T09:21:58+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "ro"
}
-->
# Conversie vorbire în text - Wio Terminal

În această parte a lecției, vei scrie cod pentru a converti vorbirea din audio capturat în text folosind serviciul de vorbire.

## Trimite audio către serviciul de vorbire

Audio poate fi trimis către serviciul de vorbire utilizând API-ul REST. Pentru a folosi serviciul de vorbire, mai întâi trebuie să soliciți un token de acces, apoi să folosești acel token pentru a accesa API-ul REST. Aceste tokenuri de acces expiră după 10 minute, așa că codul tău ar trebui să le solicite în mod regulat pentru a se asigura că sunt mereu actualizate.

### Sarcină - obține un token de acces

1. Deschide proiectul `smart-timer` dacă nu este deja deschis.

1. Adaugă următoarele dependențe de bibliotecă în fișierul `platformio.ini` pentru a accesa WiFi și a gestiona JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Adaugă următorul cod în fișierul header `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Înlocuiește `<SSID>` și `<PASSWORD>` cu valorile relevante pentru WiFi-ul tău.

    Înlocuiește `<API_KEY>` cu cheia API pentru resursa serviciului de vorbire. Înlocuiește `<LOCATION>` cu locația pe care ai folosit-o când ai creat resursa serviciului de vorbire.

    Înlocuiește `<LANGUAGE>` cu numele localizării pentru limba în care vei vorbi, de exemplu `en-GB` pentru engleză sau `zn-HK` pentru cantoneză. Poți găsi o listă a limbilor suportate și a numelor lor de localizare în [documentația despre suportul pentru limbă și voce pe Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Constanta `TOKEN_URL` este URL-ul emitentului de token fără locație. Acesta va fi combinat cu locația mai târziu pentru a obține URL-ul complet.

1. La fel ca la conectarea la Custom Vision, va trebui să folosești o conexiune HTTPS pentru a te conecta la serviciul de emitere a tokenurilor. La sfârșitul fișierului `config.h`, adaugă următorul cod:

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

    Acesta este același certificat pe care l-ai folosit când te-ai conectat la Custom Vision.

1. Adaugă un include pentru fișierul header WiFi și fișierul header config în partea de sus a fișierului `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Adaugă cod pentru a te conecta la WiFi în `main.cpp` deasupra funcției `setup`:

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

1. Apelează această funcție din funcția `setup` după ce conexiunea serială a fost stabilită:

    ```cpp
    connectWiFi();
    ```

1. Creează un nou fișier header în folderul `src` numit `speech_to_text.h`. În acest fișier header, adaugă următorul cod:

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

    Acesta include câteva fișiere header necesare pentru o conexiune HTTP, configurare și fișierul header `mic.h`, și definește o clasă numită `SpeechToText`, înainte de a declara o instanță a acestei clase care poate fi utilizată mai târziu.

1. Adaugă următoarele 2 câmpuri în secțiunea `private` a acestei clase:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` este un WiFi Client care folosește HTTPS și va fi utilizat pentru a obține tokenul de acces. Acest token va fi apoi stocat în `_access_token`.

1. Adaugă următoarea metodă în secțiunea `private`:

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

    Acest cod construiește URL-ul pentru API-ul emitentului de tokenuri folosind locația resursei de vorbire. Apoi creează un `HTTPClient` pentru a face cererea web, configurându-l să folosească clientul WiFi configurat cu certificatul punctului final al tokenului. Setează cheia API ca header pentru apel. Apoi face o cerere POST pentru a obține certificatul, încercând din nou dacă întâmpină erori. În final, tokenul de acces este returnat.

1. În secțiunea `public`, adaugă o metodă pentru a obține tokenul de acces. Aceasta va fi necesară în lecțiile ulterioare pentru a converti textul în vorbire.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. În secțiunea `public`, adaugă o metodă `init` care configurează clientul de tokenuri:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Aceasta setează certificatul pe clientul WiFi, apoi obține tokenul de acces.

1. În `main.cpp`, adaugă acest nou fișier header la directivele include:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inițializează clasa `SpeechToText` la sfârșitul funcției `setup`, după apelul `mic.init`, dar înainte ca `Ready` să fie scris pe monitorul serial:

    ```cpp
    speechToText.init();
    ```

### Sarcină - citește audio din memoria flash

1. Într-o parte anterioară a lecției, audio a fost înregistrat în memoria flash. Acest audio va trebui trimis către API-ul REST al Serviciului de Vorbire, așa că trebuie citit din memoria flash. Nu poate fi încărcat într-un buffer în memorie deoarece ar fi prea mare. Clasa `HTTPClient` care face apeluri REST poate transmite date folosind un Arduino Stream - o clasă care poate încărca date în blocuri mici, trimițând blocurile unul câte unul ca parte a cererii. De fiecare dată când apelezi `read` pe un stream, acesta returnează următorul bloc de date. Poate fi creat un stream Arduino care poate citi din memoria flash. Creează un nou fișier numit `flash_stream.h` în folderul `src` și adaugă următorul cod în el:

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

    Acesta declară clasa `FlashStream`, derivată din clasa `Stream` Arduino. Aceasta este o clasă abstractă - clasele derivate trebuie să implementeze câteva metode înainte ca clasa să poată fi instanțiată, iar aceste metode sunt definite în această clasă.

    ✅ Citește mai multe despre Stream-urile Arduino în [documentația despre Stream Arduino](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Adaugă următoarele câmpuri în secțiunea `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Acesta definește un buffer temporar pentru a stoca datele citite din memoria flash, împreună cu câmpuri pentru a stoca poziția curentă la citirea din buffer, adresa curentă pentru citirea din memoria flash și dispozitivul de memorie flash.

1. În secțiunea `private`, adaugă următoarea metodă:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Acest cod citește din memoria flash la adresa curentă și stochează datele într-un buffer. Apoi incrementează adresa, astfel încât următorul apel să citească următorul bloc de memorie. Bufferul este dimensionat pe baza celui mai mare bloc pe care `HTTPClient` îl va trimite la API-ul REST într-un moment dat.

    > 💁 Ștergerea memoriei flash trebuie făcută folosind dimensiunea grainului, citirea pe de altă parte nu.

1. În secțiunea `public` a acestei clase, adaugă un constructor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Acest constructor configurează toate câmpurile pentru a începe citirea de la începutul blocului de memorie flash și încarcă primul bloc de date în buffer.

1. Implementează metoda `write`. Acest stream va citi doar date, așa că aceasta poate să nu facă nimic și să returneze 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementează metoda `peek`. Aceasta returnează datele la poziția curentă fără a muta stream-ul mai departe. Apelarea `peek` de mai multe ori va returna mereu aceleași date atât timp cât nu se citesc date din stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementează funcția `available`. Aceasta returnează câți octeți pot fi citiți din stream sau -1 dacă stream-ul este complet. Pentru această clasă, maximul disponibil nu va fi mai mare decât dimensiunea blocului clientului HTTP. Când acest stream este utilizat în clientul HTTP, acesta apelează această funcție pentru a vedea câte date sunt disponibile, apoi solicită acele date pentru a le trimite la API-ul REST. Nu dorim ca fiecare bloc să fie mai mare decât dimensiunea blocului clientului HTTP, așa că dacă mai mult decât atât este disponibil, se returnează dimensiunea blocului. Dacă mai puțin, atunci ceea ce este disponibil este returnat. Odată ce toate datele au fost transmise, se returnează -1.

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

1. Implementează metoda `read` pentru a returna următorul octet din buffer, incrementând poziția. Dacă poziția depășește dimensiunea bufferului, acesta populează bufferul cu următorul bloc din memoria flash și resetează poziția.

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

1. În fișierul header `speech_to_text.h`, adaugă o directivă include pentru acest nou fișier header:

    ```cpp
    #include "flash_stream.h"
    ```

### Sarcină - convertește vorbirea în text

1. Vorbirea poate fi convertită în text prin trimiterea audio-ului către Serviciul de Vorbire printr-un API REST. Acest API REST are un certificat diferit față de emitentul de tokenuri, așa că adaugă următorul cod în fișierul header `config.h` pentru a defini acest certificat:

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

1. Adaugă o constantă în acest fișier pentru URL-ul vorbirii fără locație. Acesta va fi combinat cu locația și limba mai târziu pentru a obține URL-ul complet.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. În fișierul header `speech_to_text.h`, în secțiunea `private` a clasei `SpeechToText`, definește un câmp pentru un WiFi Client folosind certificatul vorbirii:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. În metoda `init`, setează certificatul pe acest WiFi Client:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Adaugă următorul cod în secțiunea `public` a clasei `SpeechToText` pentru a defini o metodă de conversie a vorbirii în text:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Adaugă următorul cod în această metodă pentru a crea un client HTTP folosind clientul WiFi configurat cu certificatul vorbirii și folosind URL-ul vorbirii setat cu locația și limba:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Unele headere trebuie setate pe conexiune:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Acesta setează headere pentru autorizare folosind tokenul de acces, formatul audio folosind rata de eșantionare și setează că clientul așteaptă rezultatul ca JSON.

1. După aceasta, adaugă următorul cod pentru a face apelul API REST:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Acesta creează un `FlashStream` și îl folosește pentru a transmite date către API-ul REST.

1. Sub acest cod, adaugă următorul cod:

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

    Acest cod verifică codul de răspuns.

    Dacă este 200, codul pentru succes, atunci rezultatul este preluat, decodat din JSON, și proprietatea `DisplayText` este setată în variabila `text`. Aceasta este proprietatea în care textul vorbirii este returnat.

    Dacă codul de răspuns este 401, atunci tokenul de acces a expirat (aceste tokenuri durează doar 10 minute). Se solicită un nou token de acces și apelul este făcut din nou.

    În caz contrar, o eroare este trimisă pe monitorul serial, iar `text` rămâne gol.

1. Adaugă următorul cod la sfârșitul acestei metode pentru a închide clientul HTTP și a returna textul:

    ```cpp
    httpClient.end();

    return text;
    ```

1. În `main.cpp`, apelează această nouă metodă `convertSpeechToText` în funcția `processAudio`, apoi afișează vorbirea pe monitorul serial:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Construiește acest cod, încarcă-l pe Wio Terminal și testează-l prin monitorul serial. Odată ce vezi `Ready` pe monitorul serial, apasă butonul C (cel din partea stângă, cel mai aproape de comutatorul de alimentare) și vorbește. Vor fi capturate 4 secunde de audio, apoi convertite în text.

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

> 💁 Poți găsi acest cod în folderul [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Programul tău de conversie vorbire în text a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus utilizând serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să aveți în vedere că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.