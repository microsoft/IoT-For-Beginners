<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T23:28:23+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "tl"
}
-->
# Speech to text - Wio Terminal

Sa bahaging ito ng aralin, magsusulat ka ng code upang i-convert ang boses mula sa na-capture na audio patungo sa text gamit ang speech service.

## Ipadala ang audio sa speech service

Maaaring ipadala ang audio sa speech service gamit ang REST API. Upang magamit ang speech service, kailangan mo munang humiling ng access token, pagkatapos ay gamitin ang token na iyon upang ma-access ang REST API. Ang mga access token na ito ay nag-e-expire pagkatapos ng 10 minuto, kaya ang iyong code ay dapat regular na humiling ng mga bagong token upang masigurong laging up-to-date ang mga ito.

### Gawain - kumuha ng access token

1. Buksan ang proyekto na `smart-timer` kung hindi pa ito bukas.

1. Idagdag ang sumusunod na mga library dependency sa `platformio.ini` file upang ma-access ang WiFi at ma-handle ang JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Idagdag ang sumusunod na code sa `config.h` header file:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Palitan ang `<SSID>` at `<PASSWORD>` ng mga kaukulang halaga para sa iyong WiFi.

    Palitan ang `<API_KEY>` ng API key para sa iyong speech service resource. Palitan ang `<LOCATION>` ng lokasyon na ginamit mo noong nilikha mo ang speech service resource.

    Palitan ang `<LANGUAGE>` ng locale name para sa wika na iyong gagamitin, halimbawa `en-GB` para sa English, o `zn-HK` para sa Cantonese. Makikita mo ang listahan ng mga suportadong wika at kanilang mga locale name sa [Language and voice support documentation sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Ang `TOKEN_URL` constant ay ang URL ng token issuer na walang lokasyon. Ito ay pagsasamahin sa lokasyon mamaya upang makuha ang buong URL.

1. Katulad ng pagkonekta sa Custom Vision, kakailanganin mong gumamit ng HTTPS connection upang kumonekta sa token issuing service. Sa dulo ng `config.h`, idagdag ang sumusunod na code:

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

    Ito ay ang parehong certificate na ginamit mo noong kumokonekta sa Custom Vision.

1. Idagdag ang include para sa WiFi header file at ang config header file sa itaas ng `main.cpp` file:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Idagdag ang code upang kumonekta sa WiFi sa `main.cpp` sa itaas ng `setup` function:

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

1. Tawagin ang function na ito mula sa `setup` function pagkatapos ma-establish ang serial connection:

    ```cpp
    connectWiFi();
    ```

1. Gumawa ng bagong header file sa `src` folder na tinatawag na `speech_to_text.h`. Sa header file na ito, idagdag ang sumusunod na code:

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

    Kasama dito ang ilang kinakailangang header file para sa HTTP connection, configuration, at ang `mic.h` header file, at nagde-define ng isang klase na tinatawag na `SpeechToText`, bago ideklara ang isang instance ng klase na maaaring gamitin mamaya.

1. Idagdag ang sumusunod na 2 field sa `private` section ng klase:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    Ang `_token_client` ay isang WiFi Client na gumagamit ng HTTPS at gagamitin upang makuha ang access token. Ang token na ito ay itatabi sa `_access_token`.

1. Idagdag ang sumusunod na method sa `private` section:

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

    Ang code na ito ay bumubuo ng URL para sa token issuer API gamit ang lokasyon ng speech resource. Gumagawa ito ng `HTTPClient` upang magawa ang web request, na naka-set up upang gamitin ang WiFi client na naka-configure gamit ang certificate ng token endpoint. Sinet nito ang API key bilang header para sa tawag. Gumagawa ito ng POST request upang makuha ang certificate, at inuulit ang proseso kung may error. Sa huli, ang access token ay ibinabalik.

1. Sa `public` section, magdagdag ng method upang makuha ang access token. Kakailanganin ito sa mga susunod na aralin upang i-convert ang text patungo sa speech.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Sa `public` section, magdagdag ng `init` method na nagse-set up ng token client:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Sinet nito ang certificate sa WiFi client, pagkatapos ay kinukuha ang access token.

1. Sa `main.cpp`, idagdag ang bagong header file na ito sa include directives:

    ```cpp
    #include "speech_to_text.h"
    ```

1. I-initialize ang `SpeechToText` class sa dulo ng `setup` function, pagkatapos ng `mic.init` call ngunit bago isulat ang `Ready` sa serial monitor:

    ```cpp
    speechToText.init();
    ```

### Gawain - basahin ang audio mula sa flash memory

1. Sa naunang bahagi ng aralin, ang audio ay na-record sa flash memory. Ang audio na ito ay kailangang ipadala sa Speech Services REST API, kaya kailangang basahin ito mula sa flash memory. Hindi ito maaaring i-load sa isang in-memory buffer dahil masyado itong malaki. Ang `HTTPClient` class na gumagawa ng REST calls ay maaaring mag-stream ng data gamit ang Arduino Stream - isang klase na maaaring mag-load ng data sa maliliit na bahagi, na ipinapadala ang mga bahagi isa-isa bilang bahagi ng request. Tuwing tatawagin mo ang `read` sa isang stream, ibinabalik nito ang susunod na bahagi ng data. Maaaring gumawa ng Arduino stream na maaaring magbasa mula sa flash memory. Gumawa ng bagong file na tinatawag na `flash_stream.h` sa `src` folder, at idagdag ang sumusunod na code dito:

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

    Ipinapahayag nito ang `FlashStream` class, na nagmula sa Arduino `Stream` class. Ito ay isang abstract class - ang mga derived class ay kailangang mag-implement ng ilang method bago ma-instantiate ang klase, at ang mga method na ito ay dine-define sa klase.

    ✅ Basahin pa ang tungkol sa Arduino Streams sa [Arduino Stream documentation](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Idagdag ang sumusunod na mga field sa `private` section:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Ito ay nagde-define ng isang temporary buffer upang mag-imbak ng data na nabasa mula sa flash memory, kasama ang mga field upang mag-imbak ng kasalukuyang posisyon kapag nagbabasa mula sa buffer, ang kasalukuyang address upang magbasa mula sa flash memory, at ang flash memory device.

1. Sa `private` section, idagdag ang sumusunod na method:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Ang code na ito ay nagbabasa mula sa flash memory sa kasalukuyang address at iniimbak ang data sa buffer. Pagkatapos nito, ini-increment ang address, kaya ang susunod na tawag ay magbabasa ng susunod na bahagi ng memory. Ang buffer ay naka-size base sa pinakamalaking chunk na ipapadala ng `HTTPClient` sa REST API sa isang pagkakataon.

    > 💁 Ang pag-erase ng flash memory ay kailangang gawin gamit ang grain size, ngunit ang pagbabasa ay hindi.

1. Sa `public` section ng klase, magdagdag ng constructor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Ang constructor na ito ay nagse-set up ng lahat ng field upang magsimulang magbasa mula sa simula ng flash memory block, at naglo-load ng unang bahagi ng data sa buffer.

1. I-implement ang `write` method. Ang stream na ito ay magbabasa lamang ng data, kaya wala itong gagawin at magbabalik ng 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. I-implement ang `peek` method. Ibinabalik nito ang data sa kasalukuyang posisyon nang hindi ginagalaw ang stream. Ang pagtawag sa `peek` nang maraming beses ay palaging magbabalik ng parehong data hangga't walang data na nababasa mula sa stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. I-implement ang `available` function. Ibinabalik nito kung ilang byte ang maaaring basahin mula sa stream, o -1 kung tapos na ang stream. Para sa klase na ito, ang maximum na available ay hindi lalampas sa chunk size ng HTTPClient. Kapag ginamit ang stream na ito sa HTTP client, tinatawag nito ang function na ito upang makita kung gaano karaming data ang available, pagkatapos ay humihiling ng ganoong karaming data upang ipadala sa REST API. Ayaw nating ang bawat chunk ay mas malaki kaysa sa chunk size ng HTTP client, kaya kung higit pa ang available, ang chunk size ang ibinabalik. Kung mas kaunti, kung ano ang available ang ibinabalik. Kapag na-stream na ang lahat ng data, -1 ang ibinabalik.

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

1. I-implement ang `read` method upang ibalik ang susunod na byte mula sa buffer, na ini-increment ang posisyon. Kung ang posisyon ay lumampas sa laki ng buffer, pinupunan nito ang buffer ng susunod na bahagi mula sa flash memory at nire-reset ang posisyon.

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

1. Sa `speech_to_text.h` header file, magdagdag ng include directive para sa bagong header file na ito:

    ```cpp
    #include "flash_stream.h"
    ```

### Gawain - i-convert ang speech sa text

1. Ang speech ay maaaring i-convert sa text sa pamamagitan ng pagpapadala ng audio sa Speech Service gamit ang REST API. Ang REST API na ito ay may ibang certificate kaysa sa token issuer, kaya idagdag ang sumusunod na code sa `config.h` header file upang i-define ang certificate na ito:

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

1. Magdagdag ng constant sa file na ito para sa speech URL na walang lokasyon. Ito ay pagsasamahin sa lokasyon at wika mamaya upang makuha ang buong URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Sa `speech_to_text.h` header file, sa `private` section ng `SpeechToText` class, mag-define ng field para sa WiFi Client gamit ang speech certificate:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Sa `init` method, i-set ang certificate sa WiFi Client na ito:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Idagdag ang sumusunod na code sa `public` section ng `SpeechToText` class upang mag-define ng method upang i-convert ang speech sa text:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Idagdag ang sumusunod na code sa method na ito upang gumawa ng HTTP client gamit ang WiFi client na naka-configure gamit ang speech certificate, at gamit ang speech URL na naka-set sa lokasyon at wika:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Kailangan mag-set ng ilang headers sa koneksyon:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Sinet nito ang headers para sa authorization gamit ang access token, ang audio format gamit ang sample rate, at sinet na ang client ay inaasahan ang resulta bilang JSON.

1. Pagkatapos nito, idagdag ang sumusunod na code upang gawin ang REST API call:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Gumagawa ito ng `FlashStream` at ginagamit ito upang i-stream ang data sa REST API.

1. Sa ibaba nito, idagdag ang sumusunod na code:

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

    Ang code na ito ay nagche-check ng response code.

    Kung ito ay 200, ang code para sa tagumpay, ang resulta ay kinukuha, dine-decode mula sa JSON, at ang `DisplayText` property ay sinet sa `text` variable. Ito ang property kung saan ibinabalik ang text na bersyon ng speech.

    Kung ang response code ay 401, ang access token ay nag-expire na (ang mga token na ito ay tumatagal lamang ng 10 minuto). Humihiling ng bagong access token, at inuulit ang tawag.

    Kung hindi, isang error ang ipinapadala sa serial monitor, at ang `text` ay iniiwang blangko.

1. Idagdag ang sumusunod na code sa dulo ng method na ito upang isara ang HTTP client at ibalik ang text:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Sa `main.cpp`, tawagin ang bagong `convertSpeechToText` method sa `processAudio` function, pagkatapos ay i-log ang speech sa serial monitor:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. I-build ang code na ito, i-upload ito sa iyong Wio Terminal at subukan ito sa pamamagitan ng serial monitor. Kapag nakita mo ang `Ready` sa serial monitor, pindutin ang C button (ang nasa kaliwang bahagi, pinakamalapit sa power switch), at magsalita. 4 na segundo ng audio ang ma-ca-capture, pagkatapos ay iko-convert sa text.

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

> 💁 Makikita mo ang code na ito sa [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) folder.

😀 Tagumpay ang iyong speech to text program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na pinagmulan. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.