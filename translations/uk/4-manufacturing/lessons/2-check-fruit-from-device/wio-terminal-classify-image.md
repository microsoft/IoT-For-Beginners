<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-28T16:10:03+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "uk"
}
-->
# Класифікація зображення - Wio Terminal

У цій частині уроку ви відправите зображення, захоплене камерою, до служби Custom Vision для його класифікації.

## Класифікація зображення

Служба Custom Vision має REST API, яке можна викликати з Wio Terminal для класифікації зображень. Це REST API доступне через HTTPS-з'єднання — захищене HTTP-з'єднання.

Під час взаємодії з HTTPS-ендпоінтами клієнтський код повинен запитати сертифікат відкритого ключа у сервера, до якого здійснюється доступ, і використовувати його для шифрування переданого трафіку. Ваш веб-браузер робить це автоматично, але мікроконтролери — ні. Вам потрібно буде вручну запросити цей сертифікат і використовувати його для створення захищеного з'єднання з REST API. Ці сертифікати не змінюються, тому після отримання сертифіката його можна жорстко закодувати у вашому додатку.

Ці сертифікати містять відкриті ключі і не потребують захисту. Ви можете використовувати їх у вихідному коді та ділитися ними публічно, наприклад, на GitHub.

### Завдання - налаштування SSL-клієнта

1. Відкрийте проект додатку `fruit-quality-detector`, якщо він ще не відкритий.

1. Відкрийте заголовковий файл `config.h` і додайте наступне:

    ```cpp
    const char *CERTIFICATE =
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

    Це *Microsoft Azure DigiCert Global Root G2 сертифікат* — один із сертифікатів, які використовуються багатьма службами Azure у всьому світі.

    > 💁 Щоб переконатися, що це сертифікат, який потрібно використовувати, виконайте наступну команду на macOS або Linux. Якщо ви використовуєте Windows, ви можете виконати цю команду за допомогою [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Вивід покаже сертифікат DigiCert Global Root G2.

1. Відкрийте `main.cpp` і додайте наступну директиву включення:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Під директивами включення оголосіть екземпляр `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Цей клас містить код для взаємодії з веб-ендпоінтами через HTTPS.

1. У методі `connectWiFi` налаштуйте `WiFiClientSecure` для використання сертифіката DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Завдання - класифікація зображення

1. Додайте наступний рядок до списку `lib_deps` у файлі `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Це імпортує [ArduinoJson](https://arduinojson.org), бібліотеку JSON для Arduino, яка буде використовуватися для декодування JSON-відповіді від REST API.

1. У `config.h` додайте константи для URL прогнозу та ключа від служби Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Замініть `<PREDICTION_URL>` на URL прогнозу з Custom Vision. Замініть `<PREDICTION_KEY>` на ключ прогнозу.

1. У `main.cpp` додайте директиву включення для бібліотеки ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Додайте наступну функцію до `main.cpp`, над функцією `buttonPressed`.

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    Цей код починається з оголошення `HTTPClient` — класу, який містить методи для взаємодії з REST API. Потім він підключає клієнт до URL прогнозу, використовуючи екземпляр `WiFiClientSecure`, налаштований з відкритим ключем Azure.

    Після підключення він надсилає заголовки — інформацію про майбутній запит до REST API. Заголовок `Content-Type` вказує, що API-запит буде надсилати необроблені двійкові дані, а заголовок `Prediction-Key` передає ключ прогнозу Custom Vision.

    Далі виконується POST-запит до HTTP-клієнта, завантажуючи масив байтів. Він міститиме зображення JPEG, захоплене камерою, коли викликається ця функція.

    > 💁 POST-запити призначені для надсилання даних і отримання відповіді. Існують інші типи запитів, такі як GET-запити, які отримують дані. GET-запити використовуються вашим веб-браузером для завантаження веб-сторінок.

    POST-запит повертає код статусу відповіді. Це добре визначені значення, де 200 означає **OK** — POST-запит був успішним.

    > 💁 Ви можете переглянути всі коди статусу відповіді на [сторінці Список кодів статусу HTTP у Вікіпедії](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Якщо повертається 200, результат зчитується з HTTP-клієнта. Це текстова відповідь від REST API з результатами прогнозу у вигляді JSON-документа. JSON має наступний формат:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    Важлива частина тут — масив `predictions`. Він містить прогнози, де кожен запис для кожного тегу містить назву тегу та ймовірність. Ймовірності, що повертаються, є числами з плаваючою точкою від 0 до 1, де 0 означає 0% ймовірності відповідності тегу, а 1 — 100% ймовірності.

    > 💁 Класифікатори зображень повертають відсотки для всіх тегів, які були використані. Кожен тег матиме ймовірність того, що зображення відповідає цьому тегу.

    Цей JSON декодується, і ймовірності для кожного тегу надсилаються до серійного монітора.

1. У функції `buttonPressed` замініть код, який зберігає дані на SD-карті, викликом `classifyImage`, або додайте його після запису зображення, але **перед** видаленням буфера:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Якщо ви заміните код, який зберігає дані на SD-карті, ви можете очистити свій код, видаливши функції `setupSDCard` та `saveToSDCard`.

1. Завантажте та запустіть ваш код. Наведіть камеру на фрукт і натисніть кнопку C. Ви побачите результат у серійному моніторі:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Ви зможете побачити зображення, яке було зроблено, і ці значення у вкладці **Predictions** у Custom Vision.

    ![Банан у Custom Vision, передбачений як стиглий на 56.8% і нестиглий на 43.1%](../../../../../translated_images/uk/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Ви можете знайти цей код у папці [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Ваш додаток для класифікації якості фруктів був успішним!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.