<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T09:22:39+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "bg"
}
-->
# Преобразуване на реч в текст - Wio Terminal

В тази част от урока ще напишете код за преобразуване на реч от записаното аудио в текст, използвайки услугата за разпознаване на реч.

## Изпращане на аудио към услугата за разпознаване на реч

Аудиото може да бъде изпратено към услугата за разпознаване на реч чрез REST API. За да използвате услугата, първо трябва да заявите токен за достъп, след което да използвате този токен за достъп до REST API. Тези токени за достъп изтичат след 10 минути, така че кодът ви трябва редовно да ги заявява, за да гарантира, че са винаги актуални.

### Задача - получаване на токен за достъп

1. Отворете проекта `smart-timer`, ако вече не е отворен.

1. Добавете следните зависимости на библиотеката към файла `platformio.ini`, за да получите достъп до WiFi и да обработвате JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Добавете следния код към хедър файла `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Заменете `<SSID>` и `<PASSWORD>` със съответните стойности за вашата WiFi мрежа.

    Заменете `<API_KEY>` с API ключа за вашия ресурс за разпознаване на реч. Заменете `<LOCATION>` с местоположението, което сте използвали при създаването на ресурса.

    Заменете `<LANGUAGE>` с локалното име на езика, на който ще говорите, например `en-GB` за английски или `zn-HK` за кантонски. Можете да намерите списък с поддържаните езици и техните локални имена в [документацията за поддръжка на езици и гласове на Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Константата `TOKEN_URL` е URL адресът на издаващия токени без местоположението. Това ще бъде комбинирано с местоположението по-късно, за да се получи пълният URL адрес.

1. Както при свързването с Custom Vision, ще трябва да използвате HTTPS връзка, за да се свържете с услугата за издаване на токени. В края на `config.h` добавете следния код:

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

    Това е същият сертификат, който използвахте при свързването с Custom Vision.

1. Добавете include за хедър файла на WiFi и хедър файла на конфигурацията в началото на файла `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Добавете код за свързване към WiFi в `main.cpp` над функцията `setup`:

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

1. Извикайте тази функция от функцията `setup` след като е установена серийната връзка:

    ```cpp
    connectWiFi();
    ```

1. Създайте нов хедър файл в папката `src`, наречен `speech_to_text.h`. В този хедър файл добавете следния код:

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

    Това включва някои необходими хедър файлове за HTTP връзка, конфигурация и хедър файла `mic.h`, и дефинира клас, наречен `SpeechToText`, преди да декларира инстанция на този клас, която може да се използва по-късно.

1. Добавете следните 2 полета в секцията `private` на този клас:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` е WiFi клиент, който използва HTTPS и ще бъде използван за получаване на токена за достъп. Този токен след това ще бъде съхранен в `_access_token`.

1. Добавете следния метод в секцията `private`:

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

    Този код изгражда URL адреса за API на издаващия токени, използвайки местоположението на ресурса за разпознаване на реч. След това създава `HTTPClient`, за да направи уеб заявката, като го конфигурира да използва WiFi клиента с конфигурирания сертификат за издаване на токени. Задава API ключа като хедър за заявката. След това прави POST заявка, за да получи сертификата, като повтаря опита при грешки. Накрая токенът за достъп се връща.

1. В секцията `public` добавете метод за получаване на токена за достъп. Това ще бъде необходимо в следващите уроци за преобразуване на текст в реч.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. В секцията `public` добавете метод `init`, който настройва клиента за токени:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Това задава сертификата на WiFi клиента, след което получава токена за достъп.

1. В `main.cpp` добавете този нов хедър файл към директивите за включване:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Инициализирайте класа `SpeechToText` в края на функцията `setup`, след извикването на `mic.init`, но преди `Ready` да бъде записано в серийния монитор:

    ```cpp
    speechToText.init();
    ```

### Задача - четене на аудио от флаш памет

1. В по-ранна част от урока аудиото беше записано във флаш паметта. Това аудио ще трябва да бъде изпратено към REST API на услугата за разпознаване на реч, така че трябва да бъде прочетено от флаш паметта. Не може да бъде заредено в буфер в паметта, тъй като ще бъде твърде голямо. Класът `HTTPClient`, който прави REST заявки, може да стриймва данни, използвайки Arduino Stream - клас, който може да зарежда данни на малки части, изпращайки ги една по една като част от заявката. Всеки път, когато извикате `read` на стрийм, той връща следващия блок от данни. Arduino стрийм може да бъде създаден, който да чете от флаш паметта. Създайте нов файл, наречен `flash_stream.h` в папката `src`, и добавете следния код към него:

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

    Това декларира класа `FlashStream`, наследяващ от Arduino `Stream` класа. Това е абстрактен клас - наследените класове трябва да имплементират няколко метода, преди класът да може да бъде инстанциран, и тези методи са дефинирани в този клас.

    ✅ Прочетете повече за Arduino Streams в [документацията за Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Добавете следните полета в секцията `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Това дефинира временен буфер за съхранение на данни, прочетени от флаш паметта, заедно с полета за съхранение на текущата позиция при четене от буфера, текущия адрес за четене от флаш паметта и устройството за флаш памет.

1. В секцията `private` добавете следния метод:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Този код чете от флаш паметта на текущия адрес и съхранява данните в буфер. След това увеличава адреса, така че следващото извикване чете следващия блок от паметта. Буферът е оразмерен според най-големия блок, който `HTTPClient` ще изпрати към REST API наведнъж.

    > 💁 Изтриването на флаш памет трябва да се извършва с размера на зърното, но четенето не изисква това.

1. В секцията `public` на този клас добавете конструктор:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Този конструктор настройва всички полета, за да започне четенето от началото на блока на флаш паметта, и зарежда първия блок от данни в буфера.

1. Имплементирайте метода `write`. Този стрийм ще чете само данни, така че този метод може да не прави нищо и да връща 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Имплементирайте метода `peek`. Този метод връща данните на текущата позиция, без да премества стрийма напред. Извикването на `peek` няколко пъти ще връща същите данни, докато не се прочетат нови данни от стрийма.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Имплементирайте функцията `available`. Тази функция връща колко байта могат да бъдат прочетени от стрийма или -1, ако стриймът е завършен. За този клас максималната наличност няма да бъде повече от размера на блока на `HTTPClient`. Когато този стрийм се използва в HTTP клиента, той извиква тази функция, за да види колко данни са налични, след което заявява толкова данни, за да ги изпрати към REST API. Не искаме всеки блок да бъде по-голям от размера на блока на HTTP клиента, така че ако повече от това е налично, се връща размерът на блока. Ако е по-малко, се връща наличното. След като всички данни са стриймвани, се връща -1.

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

1. Имплементирайте метода `read`, за да върне следващия байт от буфера, увеличавайки позицията. Ако позицията надвиши размера на буфера, той попълва буфера със следващия блок от флаш паметта и нулира позицията.

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

1. В хедър файла `speech_to_text.h` добавете директива за включване на този нов хедър файл:

    ```cpp
    #include "flash_stream.h"
    ```

### Задача - преобразуване на реч в текст

1. Речта може да бъде преобразувана в текст, като се изпрати аудиото към услугата за разпознаване на реч чрез REST API. Този REST API има различен сертификат от издаващия токени, така че добавете следния код към хедър файла `config.h`, за да дефинирате този сертификат:

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

1. Добавете константа към този файл за URL адреса на речта без местоположението. Това ще бъде комбинирано с местоположението и езика по-късно, за да се получи пълният URL адрес.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. В хедър файла `speech_to_text.h`, в секцията `private` на класа `SpeechToText`, дефинирайте поле за WiFi клиент, използващ сертификата за реч:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. В метода `init` задайте сертификата на този WiFi клиент:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Добавете следния код в секцията `public` на класа `SpeechToText`, за да дефинирате метод за преобразуване на реч в текст:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Добавете следния код към този метод, за да създадете HTTP клиент, използващ WiFi клиента, конфигуриран със сертификата за реч, и използвайки URL адреса за реч, зададен с местоположението и езика:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Някои хедъри трябва да бъдат зададени на връзката:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Това задава хедъри за авторизация, използвайки токена за достъп, формата на аудиото, използвайки честотата на семплиране, и задава, че клиентът очаква резултата като JSON.

1. След това добавете следния код, за да направите REST API заявката:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Това създава `FlashStream` и го използва, за да стриймва данни към REST API.

1. Под това добавете следния код:

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

    Този код проверява кода на отговора.

    Ако е 200, кодът за успех, тогава резултатът се извлича, декодира от JSON, и свойството `DisplayText` се задава в променливата `text`. Това е свойството, в което текстовата версия на речта се връща.

    Ако кодът на отговора е 401, тогава токенът за достъп е изтекъл (тези токени са валидни само 10 минути). Заявява се нов токен за достъп и заявката се прави отново.

    В противен случай се изпраща грешка към серийния монитор и `text` остава празен.

1. Добавете следния код в края на този метод, за да затворите HTTP клиента и да върнете текста:

    ```cpp
    httpClient.end();

    return text;
    ```

1. В `main.cpp` извикайте този нов метод `convertSpeechToText` във функцията `processAudio`, след което логнете речта в серийния монитор:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Създайте този код, качете го на вашия Wio Terminal и го тествайте през серийния монитор. След като видите `Ready` в серийния монитор, натиснете бутона C (този от лявата страна, най-близо до превключвателя за захранване) и говорете. Ще бъдат записани 4 секунди аудио, след което ще бъдат преобразувани в текст.

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

> 💁 Можете да намерите този код в папката [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Вашата програма за преобразуване на реч в текст беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.