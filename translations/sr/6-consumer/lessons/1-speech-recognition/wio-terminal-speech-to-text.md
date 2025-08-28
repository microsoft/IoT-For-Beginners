<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T13:01:59+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "sr"
}
-->
# Претварање говора у текст - Wio Terminal

У овом делу лекције, написаћете код за претварање говора из снимљеног аудио записа у текст користећи услугу за говор.

## Слање аудио записа услузи за говор

Аудио запис се може послати услузи за говор користећи REST API. Да бисте користили услугу за говор, прво морате затражити приступни токен, а затим користити тај токен за приступ REST API-ју. Ови приступни токени истичу након 10 минута, па ваш код треба редовно да их захтева како би увек били ажурни.

### Задатак - добијање приступног токена

1. Отворите пројекат `smart-timer` ако већ није отворен.

1. Додајте следеће библиотечке зависности у датотеку `platformio.ini` за приступ WiFi-ју и руковање JSON-ом:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Додајте следећи код у заглавну датотеку `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Замените `<SSID>` и `<PASSWORD>` одговарајућим вредностима за ваш WiFi.

    Замените `<API_KEY>` API кључем за ваш ресурс услуге за говор. Замените `<LOCATION>` локацијом коју сте користили приликом креирања ресурса услуге за говор.

    Замените `<LANGUAGE>` називом локала за језик на којем ћете говорити, на пример `en-GB` за енглески или `zn-HK` за кантонски. Листу подржаних језика и њихових назива локала можете пронаћи у [документацији о подршци за језик и глас на Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Константа `TOKEN_URL` је URL издавача токена без локације. Ово ће касније бити комбиновано са локацијом да би се добио пуни URL.

1. Као и код повезивања са Custom Vision, потребно је користити HTTPS везу за повезивање са услугом за издавање токена. На крај `config.h` додајте следећи код:

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

    Ово је исти сертификат који сте користили приликом повезивања са Custom Vision.

1. Додајте укључивање заглавне датотеке за WiFi и заглавне датотеке за конфигурацију на врх датотеке `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Додајте код за повезивање са WiFi-јем у `main.cpp` изнад функције `setup`:

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

1. Позовите ову функцију из функције `setup` након што је успостављена серијска веза:

    ```cpp
    connectWiFi();
    ```

1. Направите нову заглавну датотеку у фасцикли `src` под називом `speech_to_text.h`. У овој заглавној датотеци додајте следећи код:

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

    Ово укључује неке неопходне заглавне датотеке за HTTP везу, конфигурацију и заглавну датотеку `mic.h`, и дефинише класу под називом `SpeechToText`, пре него што декларише инстанцу те класе која ће касније бити коришћена.

1. Додајте следећа два поља у `private` секцију ове класе:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` је WiFi клијент који користи HTTPS и биће коришћен за добијање приступног токена. Овај токен ће затим бити сачуван у `_access_token`.

1. Додајте следећи метод у `private` секцију:

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

    Овај код гради URL за API издавача токена користећи локацију ресурса за говор. Затим креира `HTTPClient` за прављење веб захтева, подешавајући га да користи WiFi клијент конфигурисан са сертификатом за крајну тачку токена. Поставља API кључ као заглавље за позив. Затим прави POST захтев за добијање сертификата, поново покушавајући ако добије било какве грешке. На крају се враћа приступни токен.

1. У `public` секцију додајте метод за добијање приступног токена. Ово ће бити потребно у каснијим лекцијама за претварање текста у говор.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. У `public` секцију додајте `init` метод који подешава клијент за токен:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Ово поставља сертификат на WiFi клијент, а затим добија приступни токен.

1. У `main.cpp` додајте ову нову заглавну датотеку у директиве за укључивање:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Иницијализујте класу `SpeechToText` на крају функције `setup`, након позива `mic.init`, али пре него што се `Ready` испише на серијски монитор:

    ```cpp
    speechToText.init();
    ```

### Задатак - читање аудио записа из флеш меморије

1. У ранијем делу ове лекције, аудио је снимљен у флеш меморију. Овај аудио ће бити потребно послати REST API-ју услуге за говор, па га треба прочитати из флеш меморије. Не може се учитати у бафер у меморији јер би био превелик. Класа `HTTPClient` која прави REST позиве може стримовати податке користећи Arduino Stream - класу која може учитавати податке у малим блоковима, шаљући блокове један по један као део захтева. Сваки пут када позовете `read` на стриму, он враћа следећи блок података. Arduino стрим се може креирати који може читати из флеш меморије. Направите нову датотеку под називом `flash_stream.h` у фасцикли `src`, и додајте следећи код у њу:

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

    Ово декларише класу `FlashStream`, која наследи Arduino `Stream` класу. Ово је апстрактна класа - изведене класе морају имплементирати неколико метода пре него што класа може бити инстанцирана, а ти методи су дефинисани у овој класи.

    ✅ Прочитајте више о Arduino стримовима у [документацији о Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Додајте следећа поља у `private` секцију:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Ово дефинише привремени бафер за чување података прочитаних из флеш меморије, заједно са пољима за чување тренутне позиције приликом читања из бафера, тренутне адресе за читање из флеш меморије, и уређаја флеш меморије.

1. У `private` секцији додајте следећи метод:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Овај код чита из флеш меморије на тренутној адреси и чува податке у баферу. Затим повећава адресу, тако да следећи позив чита следећи блок меморије. Бафер је величине засноване на највећем блоку који `HTTPClient` шаље REST API-ју у једном тренутку.

    > 💁 Брисање флеш меморије мора се обавити користећи величину зрна, док читање не мора.

1. У `public` секцији ове класе додајте конструктор:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Овај конструктор подешава сва поља за почетак читања од почетка блока флеш меморије, и учитава први блок података у бафер.

1. Имплементирајте `write` метод. Овај стрим ће само читати податке, тако да ово може не радити ништа и вратити 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Имплементирајте `peek` метод. Ово враћа податке на тренутној позицији без померања стрима. Позивање `peek` више пута увек ће враћати исте податке све док се не прочитају подаци из стрима.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Имплементирајте `available` функцију. Ово враћа колико бајтова може бити прочитано из стрима, или -1 ако је стрим завршен. За ову класу, максимално доступно неће бити више од величине блока `HTTPClient`. Када овај стрим користи HTTP клијент, он позива ову функцију да види колико је података доступно, а затим захтева толико података за слање REST API-ју. Не желимо да сваки блок буде већи од величине блока HTTP клијента, па ако је доступно више од тога, враћа се величина блока. Ако је мање, онда се враћа оно што је доступно. Када се сви подаци стримују, враћа се -1.

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

1. Имплементирајте `read` метод да врати следећи бајт из бафера, повећавајући позицију. Ако позиција пређе величину бафера, попуњава бафер следећим блоком из флеш меморије и ресетује позицију.

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

1. У заглавној датотеци `speech_to_text.h` додајте директиву за укључивање ове нове заглавне датотеке:

    ```cpp
    #include "flash_stream.h"
    ```

### Задатак - претварање говора у текст

1. Говор се може претворити у текст слањем аудио записа услузи за говор преко REST API-ја. Овај REST API има другачији сертификат од издавача токена, па додајте следећи код у заглавну датотеку `config.h` да дефинишете овај сертификат:

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

1. Додајте константу у ову датотеку за URL говора без локације. Ово ће бити комбиновано са локацијом и језиком касније да би се добио пуни URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. У заглавној датотеци `speech_to_text.h`, у `private` секцији класе `SpeechToText`, дефинишите поље за WiFi клијент користећи сертификат за говор:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. У `init` методу поставите сертификат на овај WiFi клијент:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Додајте следећи код у `public` секцију класе `SpeechToText` да дефинишете метод за претварање говора у текст:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Додајте следећи код у овај метод да креирате HTTP клијент користећи WiFi клијент конфигурисан са сертификатом за говор, и користећи URL говора постављен са локацијом и језиком:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Потребно је поставити нека заглавља на везу:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Ово поставља заглавља за ауторизацију користећи приступни токен, аудио формат користећи sample rate, и поставља да клијент очекује резултат као JSON.

1. Након овога, додајте следећи код да направите REST API позив:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Ово креира `FlashStream` и користи га за стримовање података REST API-ју.

1. Испод овога, додајте следећи код:

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

    Овај код проверава код одговора.

    Ако је 200, код за успех, онда се резултат преузима, декодира из JSON-а, и својство `DisplayText` се поставља у променљиву `text`. Ово је својство у којем се враћа текстуална верзија говора.

    Ако је код одговора 401, онда је приступни токен истекао (ови токени трају само 10 минута). Захтева се нови приступни токен, и позив се поново прави.

    У супротном, грешка се шаље на серијски монитор, и `text` остаје празан.

1. Додајте следећи код на крај овог метода да затворите HTTP клијент и вратите текст:

    ```cpp
    httpClient.end();

    return text;
    ```

1. У `main.cpp` позовите овај нови метод `convertSpeechToText` у функцији `processAudio`, а затим испишите говор на серијски монитор:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Компилирајте овај код, отпремите га на ваш Wio Terminal и тестирајте га преко серијског монитора. Када видите `Ready` на серијском монитору, притисните C дугме (оно са леве стране, најближе прекидачу за напајање), и говорите. 4 секунде аудио записа ће бити снимљено, а затим претворено у текст.

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

> 💁 Овај код можете пронаћи у фасцикли [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Ваш програм за претварање говора у текст је успешно завршен!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.