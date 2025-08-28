<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T16:34:09+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "uk"
}
-->
# Перетворення мови в текст - Wio Terminal

У цій частині уроку ви напишете код для перетворення мови в захопленому аудіо на текст за допомогою сервісу розпізнавання мови.

## Надсилання аудіо до сервісу розпізнавання мови

Аудіо можна надіслати до сервісу розпізнавання мови через REST API. Для використання сервісу спочатку потрібно запросити токен доступу, а потім використовувати цей токен для доступу до REST API. Токени доступу мають термін дії 10 хвилин, тому ваш код повинен регулярно запитувати їх, щоб забезпечити актуальність.

### Завдання - отримати токен доступу

1. Відкрийте проект `smart-timer`, якщо він ще не відкритий.

1. Додайте наступні залежності бібліотек до файлу `platformio.ini` для доступу до WiFi та обробки JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Додайте наступний код до заголовкового файлу `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Замініть `<SSID>` і `<PASSWORD>` на відповідні значення для вашого WiFi.

    Замініть `<API_KEY>` на ключ API для вашого ресурсу сервісу розпізнавання мови. Замініть `<LOCATION>` на місце, яке ви використовували при створенні ресурсу сервісу розпізнавання мови.

    Замініть `<LANGUAGE>` на назву локалі мови, якою ви будете говорити, наприклад, `en-GB` для англійської або `zn-HK` для кантонської. Список підтримуваних мов і їх локалей можна знайти в [документації про підтримку мов і голосів на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Константа `TOKEN_URL` — це URL видавця токенів без місця розташування. Пізніше це буде об'єднано з місцем розташування для отримання повного URL.

1. Як і при підключенні до Custom Vision, вам потрібно використовувати HTTPS-з'єднання для підключення до сервісу видачі токенів. Додайте наступний код до кінця `config.h`:

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

    Це той самий сертифікат, який ви використовували при підключенні до Custom Vision.

1. Додайте включення заголовкового файлу WiFi і заголовкового файлу конфігурації на початку файлу `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Додайте код для підключення до WiFi у `main.cpp` перед функцією `setup`:

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

1. Викличте цю функцію з функції `setup` після встановлення серійного з'єднання:

    ```cpp
    connectWiFi();
    ```

1. Створіть новий заголовковий файл у папці `src`, назвавши його `speech_to_text.h`. У цьому заголовковому файлі додайте наступний код:

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

    Це включає необхідні заголовкові файли для HTTP-з'єднання, конфігурації та заголовковий файл `mic.h`, а також визначає клас `SpeechToText`, перед тим як оголосити екземпляр цього класу для подальшого використання.

1. Додайте наступні два поля до секції `private` цього класу:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` — це WiFi Client, який використовує HTTPS і буде використовуватися для отримання токена доступу. Цей токен буде збережений у `_access_token`.

1. Додайте наступний метод до секції `private`:

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

    Цей код створює URL для API видавця токенів, використовуючи місце розташування ресурсу розпізнавання мови. Потім створюється `HTTPClient` для виконання веб-запиту, налаштовуючи його для використання WiFi-клієнта, налаштованого з сертифікатом кінцевої точки токенів. Ключ API встановлюється як заголовок для виклику. Потім виконується POST-запит для отримання сертифіката, повторюючи спробу у разі помилок. Нарешті, токен доступу повертається.

1. У секції `public` додайте метод для отримання токена доступу. Це буде потрібно в наступних уроках для перетворення тексту в мову.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. У секції `public` додайте метод `init`, який налаштовує клієнт токенів:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Це встановлює сертифікат на WiFi-клієнті, а потім отримує токен доступу.

1. У `main.cpp` додайте цей новий заголовковий файл до директив включення:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Ініціалізуйте клас `SpeechToText` у кінці функції `setup`, після виклику `mic.init`, але перед записом `Ready` у серійний монітор:

    ```cpp
    speechToText.init();
    ```

### Завдання - читання аудіо з флеш-пам'яті

1. У попередній частині цього уроку аудіо було записано у флеш-пам'ять. Це аудіо потрібно надіслати до REST API сервісу розпізнавання мови, тому його потрібно прочитати з флеш-пам'яті. Його не можна завантажити в буфер пам'яті, оскільки воно буде занадто великим. Клас `HTTPClient`, який виконує REST-виклики, може передавати дані за допомогою Arduino Stream — класу, який може завантажувати дані невеликими блоками, надсилаючи їх один за одним як частину запиту. Кожного разу, коли ви викликаєте `read` на потоці, він повертає наступний блок даних. Arduino Stream можна створити для читання з флеш-пам'яті. Створіть новий файл під назвою `flash_stream.h` у папці `src` і додайте до нього наступний код:

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

    Це оголошує клас `FlashStream`, який успадковується від Arduino `Stream`. Це абстрактний клас — похідні класи повинні реалізувати кілька методів, перш ніж клас можна буде створити, і ці методи визначені в цьому класі.

    ✅ Дізнайтеся більше про Arduino Streams у [документації Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Додайте наступні поля до секції `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Це визначає тимчасовий буфер для зберігання даних, прочитаних із флеш-пам'яті, а також поля для зберігання поточної позиції при читанні з буфера, поточної адреси для читання з флеш-пам'яті та пристрою флеш-пам'яті.

1. У секції `private` додайте наступний метод:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Цей код читає з флеш-пам'яті за поточною адресою і зберігає дані в буфері. Потім адреса збільшується, щоб наступний виклик читав наступний блок пам'яті. Розмір буфера базується на найбільшому блоці, який `HTTPClient` надішле до REST API за один раз.

    > 💁 Стирання флеш-пам'яті має виконуватися за розміром зерна, читання ж не обмежене.

1. У секції `public` цього класу додайте конструктор:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Цей конструктор налаштовує всі поля для початку читання з початку блоку флеш-пам'яті і завантажує перший блок даних у буфер.

1. Реалізуйте метод `write`. Цей потік буде лише читати дані, тому він може нічого не робити і повертати 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Реалізуйте метод `peek`. Цей метод повертає дані за поточною позицією без переміщення потоку. Виклик `peek` кілька разів завжди повертає ті самі дані, якщо з потоку не було прочитано дані.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Реалізуйте функцію `available`. Вона повертає, скільки байтів можна прочитати з потоку, або -1, якщо потік завершено. Для цього класу максимальна доступна кількість буде не більше розміру блоку HTTPClient. Коли цей потік використовується в HTTP-клієнті, він викликає цю функцію, щоб дізнатися, скільки даних доступно, а потім запитує стільки даних для надсилання до REST API. Ми не хочемо, щоб кожен блок перевищував розмір блоку HTTP-клієнта, тому якщо доступно більше, повертається розмір блоку. Якщо менше, повертається доступна кількість. Після того, як усі дані були передані, повертається -1.

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

1. Реалізуйте метод `read`, щоб повернути наступний байт із буфера, збільшуючи позицію. Якщо позиція перевищує розмір буфера, він заповнює буфер наступним блоком із флеш-пам'яті і скидає позицію.

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

1. У заголовковому файлі `speech_to_text.h` додайте директиву включення для цього нового заголовкового файлу:

    ```cpp
    #include "flash_stream.h"
    ```

### Завдання - перетворення мови в текст

1. Мову можна перетворити на текст, надіславши аудіо до сервісу розпізнавання мови через REST API. Цей REST API має інший сертифікат, ніж видавець токенів, тому додайте наступний код до заголовкового файлу `config.h`, щоб визначити цей сертифікат:

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

1. Додайте константу до цього файлу для URL сервісу розпізнавання мови без місця розташування. Це буде об'єднано з місцем розташування і мовою пізніше для отримання повного URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. У заголовковому файлі `speech_to_text.h` у секції `private` класу `SpeechToText` визначте поле для WiFi-клієнта, який використовує сертифікат сервісу розпізнавання мови:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. У методі `init` встановіть сертифікат на цьому WiFi-клієнті:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Додайте наступний код до секції `public` класу `SpeechToText`, щоб визначити метод для перетворення мови в текст:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Додайте наступний код до цього методу, щоб створити HTTP-клієнт, використовуючи WiFi-клієнт, налаштований із сертифікатом сервісу розпізнавання мови, і використовуючи URL сервісу розпізнавання мови, встановлений із місцем розташування і мовою:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Деякі заголовки потрібно встановити на з'єднанні:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Це встановлює заголовки для авторизації за допомогою токена доступу, аудіо-формату за допомогою частоти вибірки і встановлює, що клієнт очікує результат у форматі JSON.

1. Після цього додайте наступний код для виконання REST API виклику:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Це створює `FlashStream` і використовує його для передачі даних до REST API.

1. Нижче цього додайте наступний код:

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

    Цей код перевіряє код відповіді.

    Якщо це 200, код успіху, то результат отримується, декодується з JSON, і властивість `DisplayText` встановлюється в змінну `text`. Це властивість, у якій повертається текстова версія мови.

    Якщо код відповіді 401, то токен доступу закінчився (ці токени діють лише 10 хвилин). Запитується новий токен доступу, і виклик виконується знову.

    В іншому випадку помилка надсилається до серійного монітора, і `text` залишається порожнім.

1. Додайте наступний код до кінця цього методу, щоб закрити HTTP-клієнт і повернути текст:

    ```cpp
    httpClient.end();

    return text;
    ```

1. У `main.cpp` викличте новий метод `convertSpeechToText` у функції `processAudio`, а потім виведіть мову до серійного монітора:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Зберіть цей код, завантажте його на ваш Wio Terminal і протестуйте через серійний монітор. Як тільки ви побачите `Ready` у серійному моніторі, натисніть кнопку C (ту, що зліва, найближче до перемикача живлення) і говоріть. 4 секунди аудіо буде захоплено, а потім перетворено на текст.

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

> 💁 Ви можете знайти цей код у папці [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Ваше програмне забезпечення для перетворення мови в текст успішно працює!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматизовані переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.