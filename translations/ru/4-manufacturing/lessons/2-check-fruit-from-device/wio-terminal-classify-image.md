<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-26T21:50:48+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "ru"
}
-->
# Классификация изображения - Wio Terminal

В этой части урока вы отправите изображение, снятое камерой, в сервис Custom Vision для его классификации.

## Классификация изображения

Сервис Custom Vision предоставляет REST API, который можно вызвать с Wio Terminal для классификации изображений. Этот REST API доступен через HTTPS-соединение — защищенное HTTP-соединение.

При взаимодействии с HTTPS-эндпоинтами клиентский код должен запросить сертификат открытого ключа у сервера, к которому осуществляется доступ, и использовать его для шифрования передаваемого трафика. Ваш веб-браузер делает это автоматически, но микроконтроллеры — нет. Вам нужно будет запросить этот сертификат вручную и использовать его для создания защищенного соединения с REST API. Эти сертификаты не меняются, поэтому, получив сертификат, его можно жестко закодировать в вашем приложении.

Эти сертификаты содержат открытые ключи и не требуют защиты. Вы можете использовать их в исходном коде и публиковать в открытом доступе, например, на GitHub.

### Задача - настройка SSL-клиента

1. Откройте проект приложения `fruit-quality-detector`, если он еще не открыт.

1. Откройте заголовочный файл `config.h` и добавьте следующее:

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

    Это *Microsoft Azure DigiCert Global Root G2 certificate* — один из сертификатов, используемых многими сервисами Azure по всему миру.

    > 💁 Чтобы убедиться, что это нужный сертификат, выполните следующую команду на macOS или Linux. Если вы используете Windows, вы можете выполнить эту команду через [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Вывод покажет сертификат DigiCert Global Root G2.

1. Откройте `main.cpp` и добавьте следующий директиву include:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Под директивами include объявите экземпляр `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Этот класс содержит код для взаимодействия с веб-эндпоинтами через HTTPS.

1. В методе `connectWiFi` настройте `WifiClientSecure` для использования сертификата DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Задача - классификация изображения

1. Добавьте следующую строку в список `lib_deps` в файле `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Это импортирует [ArduinoJson](https://arduinojson.org), библиотеку JSON для Arduino, которая будет использоваться для декодирования JSON-ответа от REST API.

1. В `config.h` добавьте константы для URL предсказания и ключа из сервиса Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Замените `<PREDICTION_URL>` на URL предсказания из Custom Vision. Замените `<PREDICTION_KEY>` на ключ предсказания.

1. В `main.cpp` добавьте директиву include для библиотеки ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Добавьте следующую функцию в `main.cpp` выше функции `buttonPressed`:

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

    Этот код начинает с объявления `HTTPClient` — класса, содержащего методы для взаимодействия с REST API. Затем он подключает клиент к URL предсказания, используя экземпляр `WiFiClientSecure`, настроенный с публичным ключом Azure.

    После подключения отправляются заголовки — информация о предстоящем запросе к REST API. Заголовок `Content-Type` указывает, что API вызов отправит необработанные бинарные данные, а заголовок `Prediction-Key` передает ключ предсказания Custom Vision.

    Затем выполняется POST-запрос к HTTP-клиенту, загружая массив байтов. Этот массив будет содержать изображение в формате JPEG, снятое камерой при вызове этой функции.

    > 💁 POST-запросы предназначены для отправки данных и получения ответа. Существуют другие типы запросов, такие как GET-запросы, которые извлекают данные. GET-запросы используются вашим веб-браузером для загрузки веб-страниц.

    POST-запрос возвращает код статуса ответа. Это хорошо определенные значения, где 200 означает **OK** — POST-запрос был успешным.

    > 💁 Вы можете увидеть все коды статуса ответа на [странице списка HTTP-кодов статуса в Википедии](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Если возвращается 200, результат считывается из HTTP-клиента. Это текстовый ответ от REST API с результатами предсказания в формате JSON. JSON имеет следующий формат:

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

    Важная часть здесь — массив `predictions`. Он содержит предсказания, с одной записью для каждого тега, включающей имя тега и вероятность. Вероятности возвращаются в виде чисел с плавающей точкой от 0 до 1, где 0 означает 0% вероятность совпадения с тегом, а 1 — 100%.

    > 💁 Классификаторы изображений возвращают проценты для всех использованных тегов. Каждый тег будет иметь вероятность того, что изображение соответствует этому тегу.

    Этот JSON декодируется, и вероятности для каждого тега отправляются в монитор последовательного порта.

1. В функции `buttonPressed` замените код, который сохраняет изображение на SD-карту, вызовом `classifyImage`, или добавьте его после записи изображения, но **до** удаления буфера:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Если вы замените код, который сохраняет изображение на SD-карту, вы можете очистить ваш код, удалив функции `setupSDCard` и `saveToSDCard`.

1. Загрузите и выполните ваш код. Направьте камеру на фрукт и нажмите кнопку C. Вы увидите вывод в мониторе последовательного порта:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Вы сможете увидеть изображение, которое было снято, и эти значения на вкладке **Predictions** в Custom Vision.

    ![Банан в Custom Vision, предсказанный как спелый на 56.8% и неспелый на 43.1%](../../../../../translated_images/ru/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Вы можете найти этот код в папке [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Ваше приложение для классификации качества фруктов успешно завершено!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Хотя мы стремимся к точности, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его исходном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.