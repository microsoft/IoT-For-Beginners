<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T00:27:16+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "ru"
}
-->
# Речь в текст - Wio Terminal

В этой части урока вы напишете код для преобразования речи из записанного аудио в текст с использованием службы распознавания речи.

## Отправка аудио в службу распознавания речи

Аудио можно отправить в службу распознавания речи с помощью REST API. Чтобы использовать эту службу, сначала нужно запросить токен доступа, а затем использовать его для доступа к REST API. Эти токены доступа истекают через 10 минут, поэтому ваш код должен регулярно запрашивать их, чтобы они всегда были актуальными.

### Задание - получение токена доступа

1. Откройте проект `smart-timer`, если он еще не открыт.

1. Добавьте следующие зависимости библиотек в файл `platformio.ini` для доступа к WiFi и работы с JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Добавьте следующий код в заголовочный файл `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Замените `<SSID>` и `<PASSWORD>` на соответствующие значения для вашего WiFi.

    Замените `<API_KEY>` на ключ API для вашего ресурса службы распознавания речи. Замените `<LOCATION>` на местоположение, которое вы указали при создании ресурса службы распознавания речи.

    Замените `<LANGUAGE>` на имя локали языка, на котором вы будете говорить, например, `en-GB` для английского или `zn-HK` для кантонского. Вы можете найти список поддерживаемых языков и их локалей в [документации о поддержке языков и голосов на сайте Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Константа `TOKEN_URL` — это URL-адрес эмитента токенов без указания местоположения. Позже он будет объединен с местоположением для получения полного URL-адреса.

1. Как и при подключении к Custom Vision, вам нужно будет использовать HTTPS-соединение для подключения к службе выдачи токенов. В конец файла `config.h` добавьте следующий код:

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

    Это тот же сертификат, который вы использовали при подключении к Custom Vision.

1. Добавьте включение заголовочного файла WiFi и заголовочного файла config в начало файла `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Добавьте код для подключения к WiFi в `main.cpp` перед функцией `setup`:

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

1. Вызовите эту функцию из функции `setup` после установления последовательного соединения:

    ```cpp
    connectWiFi();
    ```

1. Создайте новый заголовочный файл в папке `src` с именем `speech_to_text.h`. В этом заголовочном файле добавьте следующий код:

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

    Это включает необходимые заголовочные файлы для HTTP-соединения, конфигурации и заголовочный файл `mic.h`, а также определяет класс `SpeechToText`, после чего объявляется экземпляр этого класса для дальнейшего использования.

1. Добавьте следующие два поля в секцию `private` этого класса:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` — это WiFi Client, использующий HTTPS, который будет использоваться для получения токена доступа. Этот токен затем будет сохранен в `_access_token`.

1. Добавьте следующий метод в секцию `private`:

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

    Этот код создает URL-адрес для API эмитента токенов, используя местоположение ресурса распознавания речи. Затем создается `HTTPClient` для выполнения веб-запроса, настроенного на использование WiFi-клиента с сертификатом конечной точки токенов. Ключ API устанавливается в качестве заголовка для вызова. Затем выполняется POST-запрос для получения сертификата, повторяющийся в случае ошибок. Наконец, возвращается токен доступа.

1. В секцию `public` добавьте метод для получения токена доступа. Он понадобится в следующих уроках для преобразования текста в речь.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. В секцию `public` добавьте метод `init`, который настраивает клиент токенов:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Этот метод устанавливает сертификат на WiFi-клиенте, а затем получает токен доступа.

1. В `main.cpp` добавьте этот новый заголовочный файл в директивы включения:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Инициализируйте класс `SpeechToText` в конце функции `setup`, после вызова `mic.init`, но перед записью `Ready` в последовательный монитор:

    ```cpp
    speechToText.init();
    ```

### Задание - чтение аудио из флеш-памяти

1. На более раннем этапе этого урока аудио было записано во флеш-память. Это аудио нужно будет отправить в REST API службы распознавания речи, поэтому его нужно считать из флеш-памяти. Оно не может быть загружено в буфер памяти, так как будет слишком большим. Класс `HTTPClient`, который выполняет REST-вызовы, может передавать данные с использованием Arduino Stream — класса, который может загружать данные небольшими блоками, отправляя их по одному за раз в рамках запроса. Каждый раз, когда вы вызываете `read` на потоке, он возвращает следующий блок данных. Arduino Stream можно создать для чтения из флеш-памяти. Создайте новый файл с именем `flash_stream.h` в папке `src` и добавьте в него следующий код:

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

    Это объявляет класс `FlashStream`, производный от Arduino `Stream`. Это абстрактный класс — производные классы должны реализовать несколько методов, прежде чем класс можно будет использовать, и эти методы определены в этом классе.

    ✅ Подробнее о потоках Arduino можно прочитать в [документации Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Добавьте следующие поля в секцию `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Это определяет временный буфер для хранения данных, считанных из флеш-памяти, а также поля для хранения текущей позиции при чтении из буфера, текущего адреса для чтения из флеш-памяти и устройства флеш-памяти.

1. В секции `private` добавьте следующий метод:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Этот код считывает данные из флеш-памяти по текущему адресу и сохраняет их в буфере. Затем он увеличивает адрес, чтобы следующий вызов считывал следующий блок памяти. Размер буфера основан на максимальном размере блока, который `HTTPClient` отправит в REST API за один раз.

    > 💁 Стирание флеш-памяти должно выполняться с использованием размера зерна, чтение же этого ограничения не имеет.

1. В секции `public` этого класса добавьте конструктор:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Этот конструктор настраивает все поля для начала чтения с начала блока флеш-памяти и загружает первый блок данных в буфер.

1. Реализуйте метод `write`. Этот поток будет только читать данные, поэтому этот метод может ничего не делать и возвращать 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Реализуйте метод `peek`. Этот метод возвращает данные по текущей позиции, не перемещая поток. Многократный вызов `peek` всегда будет возвращать одни и те же данные, пока из потока не будет считано что-либо новое.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Реализуйте функцию `available`. Она возвращает, сколько байтов можно считать из потока, или -1, если поток завершен. Для этого класса максимальное доступное количество байтов не будет превышать размер блока HTTPClient. Когда этот поток используется в HTTP-клиенте, он вызывает эту функцию, чтобы узнать, сколько данных доступно, а затем запрашивает это количество для отправки в REST API. Мы не хотим, чтобы каждый блок превышал размер блока HTTP-клиента, поэтому, если доступно больше, возвращается размер блока. Если меньше, возвращается доступное количество. Когда все данные переданы, возвращается -1.

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

1. Реализуйте метод `read`, чтобы возвращать следующий байт из буфера, увеличивая позицию. Если позиция превышает размер буфера, буфер заполняется следующим блоком из флеш-памяти, а позиция сбрасывается.

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

1. В заголовочном файле `speech_to_text.h` добавьте директиву включения для этого нового заголовочного файла:

    ```cpp
    #include "flash_stream.h"
    ```

### Задание - преобразование речи в текст

1. Речь можно преобразовать в текст, отправив аудио в службу распознавания речи через REST API. У этого REST API другой сертификат, чем у эмитента токенов, поэтому добавьте следующий код в заголовочный файл `config.h`, чтобы определить этот сертификат:

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

1. Добавьте в этот файл константу для URL-адреса службы распознавания речи без указания местоположения. Позже он будет объединен с местоположением и языком для получения полного URL-адреса.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. В заголовочном файле `speech_to_text.h` в секции `private` класса `SpeechToText` определите поле для WiFi-клиента, использующего сертификат службы распознавания речи:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. В методе `init` установите сертификат на этом WiFi-клиенте:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Добавьте следующий код в секцию `public` класса `SpeechToText`, чтобы определить метод для преобразования речи в текст:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Добавьте следующий код в этот метод для создания HTTP-клиента, использующего WiFi-клиент, настроенный с сертификатом службы распознавания речи, и URL-адрес службы распознавания речи, установленный с местоположением и языком:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Установите некоторые заголовки на соединении:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Это устанавливает заголовки для авторизации с использованием токена доступа, формата аудио с использованием частоты дискретизации и указывает, что клиент ожидает результат в формате JSON.

1. После этого добавьте следующий код для выполнения REST API вызова:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Это создает `FlashStream` и использует его для передачи данных в REST API.

1. Ниже добавьте следующий код:

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

    Этот код проверяет код ответа.

    Если это 200, код успешного выполнения, то результат извлекается, декодируется из JSON, и свойство `DisplayText` сохраняется в переменной `text`. Это свойство, в котором возвращается текстовая версия речи.

    Если код ответа 401, то токен доступа истек (эти токены действительны только 10 минут). Запрашивается новый токен доступа, и вызов выполняется снова.

    В противном случае ошибка выводится в последовательный монитор, а `text` остается пустым.

1. Добавьте следующий код в конец этого метода, чтобы закрыть HTTP-клиент и вернуть текст:

    ```cpp
    httpClient.end();

    return text;
    ```

1. В `main.cpp` вызовите новый метод `convertSpeechToText` в функции `processAudio`, затем выведите текст речи в последовательный монитор:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Соберите этот код, загрузите его на ваш Wio Terminal и протестируйте через последовательный монитор. Как только вы увидите `Ready` в последовательном мониторе, нажмите кнопку C (слева, ближе к переключателю питания) и начните говорить. 4 секунды аудио будут записаны, а затем преобразованы в текст.

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

> 💁 Вы можете найти этот код в папке [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Ваше приложение для преобразования речи в текст успешно работает!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникающие в результате использования данного перевода.