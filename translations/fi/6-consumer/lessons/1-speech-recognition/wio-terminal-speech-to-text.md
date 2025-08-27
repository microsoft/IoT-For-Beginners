<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T22:39:22+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "fi"
}
-->
# Puhe tekstiksi - Wio Terminal

Tässä osassa oppituntia kirjoitat koodia, joka muuntaa tallennetun äänen puheen tekstiksi käyttämällä puhepalvelua.

## Lähetä ääni puhepalveluun

Ääni voidaan lähettää puhepalveluun käyttämällä REST-rajapintaa. Puhepalvelun käyttöön tarvitset ensin käyttöoikeustunnuksen, jonka avulla pääset REST-rajapintaan. Nämä käyttöoikeustunnukset vanhenevat 10 minuutin kuluttua, joten koodisi tulisi pyytää niitä säännöllisesti varmistaakseen, että ne ovat aina ajan tasalla.

### Tehtävä - hanki käyttöoikeustunnus

1. Avaa `smart-timer`-projekti, jos se ei ole jo auki.

1. Lisää seuraavat kirjastoriippuvuudet `platformio.ini`-tiedostoon, jotta voit käyttää WiFi-yhteyttä ja käsitellä JSON-dataa:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Lisää seuraava koodi `config.h`-otsikkotiedostoon:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Korvaa `<SSID>` ja `<PASSWORD>` WiFi-yhteytesi vastaavilla arvoilla.

    Korvaa `<API_KEY>` puhepalveluresurssisi API-avaimella. Korvaa `<LOCATION>` sijainnilla, jonka valitsit luodessasi puhepalveluresurssin.

    Korvaa `<LANGUAGE>` kielen paikallisella nimellä, esimerkiksi `en-GB` englannille tai `zn-HK` kantonille. Löydät tuettujen kielten ja niiden paikalliset nimet [Microsoftin dokumentaatiosta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    `TOKEN_URL`-vakio on tokenin myöntäjän URL ilman sijaintia. Tämä yhdistetään sijaintiin myöhemmin, jotta saadaan täydellinen URL.

1. Aivan kuten Custom Vision -yhteydessä, sinun täytyy käyttää HTTPS-yhteyttä yhdistääksesi tokenin myöntämispalveluun. Lisää `config.h`-tiedoston loppuun seuraava koodi:

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

    Tämä on sama varmenne, jota käytit yhdistäessäsi Custom Visioniin.

1. Lisää WiFi-otsikkotiedoston ja config-otsikkotiedoston sisällytys `main.cpp`-tiedoston alkuun:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Lisää koodi WiFi-yhteyden muodostamiseksi `main.cpp`-tiedostoon `setup`-funktion yläpuolelle:

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

1. Kutsu tätä funktiota `setup`-funktiossa sen jälkeen, kun sarjayhteys on muodostettu:

    ```cpp
    connectWiFi();
    ```

1. Luo uusi otsikkotiedosto `src`-kansioon nimeltä `speech_to_text.h`. Lisää tähän otsikkotiedostoon seuraava koodi:

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

    Tämä sisältää tarvittavat otsikkotiedostot HTTP-yhteyttä, konfiguraatiota ja `mic.h`-otsikkotiedostoa varten, ja määrittelee luokan nimeltä `SpeechToText`, ennen kuin luo instanssin tästä luokasta myöhempää käyttöä varten.

1. Lisää seuraavat kaksi kenttää tämän luokan `private`-osioon:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` on HTTPS-yhteyttä käyttävä WiFi Client, jota käytetään käyttöoikeustunnuksen hankkimiseen. Tämä tunnus tallennetaan sitten `_access_token`-muuttujaan.

1. Lisää seuraava metodi luokan `private`-osioon:

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

    Tämä koodi rakentaa URL:n tokenin myöntäjän API:lle käyttäen puhepalveluresurssin sijaintia. Se luo `HTTPClient`-instanssin verkkopyyntöä varten, asettaen sen käyttämään WiFi Clientia, joka on konfiguroitu token-päätepisteen varmenteella. Se asettaa API-avaimen pyynnön otsikkoon. Lopuksi käyttöoikeustunnus palautetaan.

1. Lisää `public`-osioon metodi käyttöoikeustunnuksen hakemiseksi. Tätä tarvitaan myöhemmissä oppitunneissa tekstin muuntamiseksi puheeksi.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Lisää `public`-osioon `init`-metodi, joka asettaa token-clientin:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Tämä asettaa varmenteen WiFi Clientille ja hakee käyttöoikeustunnuksen.

1. Lisää tämä uusi otsikkotiedosto `main.cpp`-tiedoston sisällytysdirektiiveihin:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Alusta `SpeechToText`-luokka `setup`-funktion lopussa, `mic.init`-kutsun jälkeen mutta ennen kuin `Ready` kirjoitetaan sarjamonitoriin:

    ```cpp
    speechToText.init();
    ```

### Tehtävä - lue ääni flash-muistista

1. Oppitunnin aiemmassa osassa ääni tallennettiin flash-muistiin. Tämä ääni täytyy lähettää Speech Services REST API:lle, joten se täytyy lukea flash-muistista. Sitä ei voida ladata muistiin kokonaisuudessaan, koska se olisi liian suuri. `HTTPClient`-luokka, joka tekee REST-kutsuja, voi suoratoistaa dataa käyttämällä Arduino Streamia - luokkaa, joka voi ladata dataa pienissä paloissa ja lähettää palat yksi kerrallaan osana pyyntöä. Joka kerta kun kutsut `read`-metodia streamissa, se palauttaa seuraavan datalohkon. Arduino-stream voidaan luoda lukemaan flash-muistista. Luo uusi tiedosto nimeltä `flash_stream.h` `src`-kansioon ja lisää siihen seuraava koodi:

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

    Tämä määrittelee `FlashStream`-luokan, joka periytyy Arduino `Stream`-luokasta. Tämä on abstrakti luokka - perityt luokat täytyy toteuttaa muutama metodi ennen kuin luokka voidaan instansioida, ja nämä metodit määritellään tässä luokassa.

    ✅ Lue lisää Arduino Streamista [Arduino Stream -dokumentaatiosta](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Lisää seuraavat kentät luokan `private`-osioon:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Tämä määrittelee väliaikaisen puskurin flash-muistista luetun datan tallentamiseen, sekä kentät nykyisen lukuposition, flash-muistin osoitteen ja flash-muistilaitteen tallentamiseen.

1. Lisää `private`-osioon seuraava metodi:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Tämä koodi lukee flash-muistista nykyisessä osoitteessa ja tallentaa datan puskurin. Se sitten kasvattaa osoitetta, joten seuraava kutsu lukee seuraavan muistilohkon. Puskurin koko perustuu suurimpaan lohkoon, jonka `HTTPClient` lähettää REST API:lle kerralla.

    > 💁 Flash-muistin tyhjentäminen täytyy tehdä viljakoossa, mutta lukeminen ei.

1. Lisää luokan `public`-osioon konstruktori:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Tämä konstruktori asettaa kaikki kentät aloittamaan lukemisen flash-muistilohkon alusta ja lataa ensimmäisen datalohkon puskurin.

1. Toteuta `write`-metodi. Tämä stream lukee vain dataa, joten tämä voi tehdä ei mitään ja palauttaa 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Toteuta `peek`-metodi. Tämä palauttaa datan nykyisessä positiossa siirtämättä streamia eteenpäin. `peek`-kutsut palauttavat aina saman datan, kunnes streamista luetaan dataa.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Toteuta `available`-funktio. Tämä palauttaa, kuinka monta tavua streamista voidaan lukea, tai -1, jos stream on valmis. Tämän luokan tapauksessa maksimimäärä on enintään HTTPClientin lohkokoko. Kun streamia käytetään HTTPClientissa, se kutsuu tätä funktiota nähdäkseen, kuinka paljon dataa on saatavilla, ja pyytää sitten sen verran dataa lähetettäväksi REST API:lle. Emme halua, että jokainen lohko on suurempi kuin HTTPClientin lohkokoko, joten jos enemmän on saatavilla, palautetaan lohkokoko. Jos vähemmän, palautetaan saatavilla oleva määrä. Kun kaikki data on suoratoistettu, palautetaan -1.

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

1. Toteuta `read`-metodi palauttamaan seuraava tavu puskurista, kasvattaen positiota. Jos positio ylittää puskurin koon, se täyttää puskurin seuraavalla lohkolla flash-muistista ja nollaa position.

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

1. Lisää `speech_to_text.h`-otsikkotiedostoon sisällytysdirektiivi tälle uudelle otsikkotiedostolle:

    ```cpp
    #include "flash_stream.h"
    ```

### Tehtävä - muunna puhe tekstiksi

1. Puhe voidaan muuntaa tekstiksi lähettämällä ääni puhepalveluun REST API:n kautta. Tämä REST API käyttää eri varmennetta kuin tokenin myöntäjä, joten lisää seuraava koodi `config.h`-otsikkotiedostoon määrittämään tämä varmenne:

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

1. Lisää tähän tiedostoon vakio puhe-URL:lle ilman sijaintia. Tämä yhdistetään sijaintiin ja kieleen myöhemmin täydellisen URL:n saamiseksi.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Lisää `speech_to_text.h`-otsikkotiedostoon `private`-osioon kenttä WiFi Clientille, joka käyttää puhevarmennetta:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Aseta varmenne tälle WiFi Clientille `init`-metodissa:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Lisää seuraava koodi `SpeechToText`-luokan `public`-osioon määrittämään metodi puheen muuntamiseksi tekstiksi:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Lisää tähän metodiin seuraava koodi luomaan HTTPClient WiFi Clientilla, joka on konfiguroitu puhevarmenteella, ja käyttämään puhe-URL:ää, joka on asetettu sijainnilla ja kielellä:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Jotkut otsikot täytyy asettaa yhteydelle:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Tämä asettaa otsikot käyttöoikeustunnukselle, äänen formaatille näytteenottotaajuuden mukaan ja määrittää, että asiakas odottaa tuloksen JSON-muodossa.

1. Tämän jälkeen lisää seuraava koodi tekemään REST API -kutsu:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Tämä luo `FlashStream`-instanssin ja käyttää sitä datan suoratoistamiseen REST API:lle.

1. Lisää tämän alle seuraava koodi:

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

    Tämä koodi tarkistaa vastauskoodin.

    Jos koodi on 200, joka tarkoittaa onnistumista, tulos haetaan, dekoodataan JSON-muodosta, ja `DisplayText`-ominaisuus asetetaan `text`-muuttujaan. Tämä ominaisuus sisältää puheen tekstiversion.

    Jos vastauskoodi on 401, käyttöoikeustunnus on vanhentunut (nämä tunnukset kestävät vain 10 minuuttia). Uusi käyttöoikeustunnus pyydetään, ja kutsu tehdään uudelleen.

    Muussa tapauksessa virhe lähetetään sarjamonitoriin, ja `text` jätetään tyhjäksi.

1. Lisää tämän metodin loppuun seuraava koodi sulkemaan HTTPClient ja palauttamaan tekstin:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Kutsu tätä uutta `convertSpeechToText`-metodia `processAudio`-funktiossa `main.cpp`-tiedostossa ja kirjaa puhe sarjamonitoriin:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Rakenna tämä koodi, lataa se Wio Terminal -laitteeseesi ja testaa sitä sarjamonitorin kautta. Kun näet `Ready` sarjamonitorissa, paina C-painiketta (vasemmanpuoleinen painike, lähimpänä virtakytkintä) ja puhu. 4 sekuntia ääntä tallennetaan ja muunnetaan tekstiksi.

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

> 💁 Löydät tämän koodin [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) -kansiosta.

😀 Puhe tekstiksi -ohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.