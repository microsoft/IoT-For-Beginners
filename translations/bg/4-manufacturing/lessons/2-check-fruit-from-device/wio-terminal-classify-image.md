<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-28T08:49:38+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "bg"
}
-->
# Класифициране на изображение - Wio Terminal

В тази част от урока ще изпратите изображението, заснето от камерата, към услугата Custom Vision, за да го класифицирате.

## Класифициране на изображение

Услугата Custom Vision има REST API, който можете да извикате от Wio Terminal, за да класифицирате изображения. Този REST API се достъпва чрез HTTPS връзка - защитена HTTP връзка.

При взаимодействие с HTTPS крайни точки, клиентският код трябва да поиска публичния ключов сертификат от сървъра, към който се осъществява достъп, и да го използва за криптиране на изпратения трафик. Вашият уеб браузър прави това автоматично, но микроконтролерите не го правят. Ще трябва ръчно да поискате този сертификат и да го използвате, за да създадете защитена връзка с REST API. Тези сертификати не се променят, така че след като имате сертификат, той може да бъде твърдо кодиран във вашето приложение.

Тези сертификати съдържат публични ключове и не е необходимо да се пазят в тайна. Можете да ги използвате във вашия изходен код и да ги споделяте публично на места като GitHub.

### Задача - настройка на SSL клиент

1. Отворете проекта на приложението `fruit-quality-detector`, ако вече не е отворен.

1. Отворете заглавния файл `config.h` и добавете следното:

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

    Това е *Microsoft Azure DigiCert Global Root G2 сертификат* - един от сертификатите, използвани от много Azure услуги глобално.

    > 💁 За да видите, че това е сертификатът, който трябва да използвате, изпълнете следната команда на macOS или Linux. Ако използвате Windows, можете да изпълните тази команда чрез [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Изходът ще покаже DigiCert Global Root G2 сертификата.

1. Отворете `main.cpp` и добавете следната директива за включване:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Под директивите за включване, декларирайте инстанция на `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Този клас съдържа код за комуникация с уеб крайни точки чрез HTTPS.

1. В метода `connectWiFi` задайте WiFiClientSecure да използва DigiCert Global Root G2 сертификата:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Задача - класифициране на изображение

1. Добавете следното като допълнителен ред към списъка `lib_deps` в файла `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Това импортира [ArduinoJson](https://arduinojson.org), библиотека за JSON за Arduino, която ще се използва за декодиране на JSON отговора от REST API.

1. В `config.h` добавете константи за URL адреса за предсказание и ключа от услугата Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Заменете `<PREDICTION_URL>` с URL адреса за предсказание от Custom Vision. Заменете `<PREDICTION_KEY>` с ключа за предсказание.

1. В `main.cpp` добавете директива за включване на библиотеката ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Добавете следната функция в `main.cpp`, над функцията `buttonPressed`.

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

    Този код започва с деклариране на `HTTPClient` - клас, който съдържа методи за взаимодействие с REST API. След това свързва клиента към URL адреса за предсказание, използвайки инстанцията `WiFiClientSecure`, която беше настроена с публичния ключ на Azure.

    След като се свърже, изпраща заглавки - информация за предстоящата заявка, която ще бъде направена към REST API. Заглавката `Content-Type` указва, че API заявката ще изпрати сурови бинарни данни, а заглавката `Prediction-Key` предава ключа за предсказание от Custom Vision.

    След това се прави POST заявка към HTTP клиента, качвайки масив от байтове. Това ще съдържа JPEG изображението, заснето от камерата, когато тази функция бъде извикана.

    > 💁 POST заявките са предназначени за изпращане на данни и получаване на отговор. Има и други типове заявки, като GET заявки, които извличат данни. GET заявките се използват от вашия уеб браузър за зареждане на уеб страници.

    POST заявката връща статус код на отговора. Това са добре дефинирани стойности, като 200 означава **OK** - POST заявката е успешна.

    > 💁 Можете да видите всички статус кодове на отговорите в [страницата със списък на HTTP статус кодове в Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Ако се върне 200, резултатът се прочита от HTTP клиента. Това е текстов отговор от REST API с резултатите от предсказанието като JSON документ. JSON е в следния формат:

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

    Важната част тук е масивът `predictions`. Той съдържа предсказанията, като всяко предсказание включва името на етикета и вероятността. Върнатите вероятности са числа с плаваща запетая от 0 до 1, като 0 означава 0% шанс за съвпадение с етикета, а 1 означава 100% шанс.

    > 💁 Класификаторите на изображения ще върнат процентите за всички етикети, които са били използвани. Всеки етикет ще има вероятност, че изображението съответства на този етикет.

    Този JSON се декодира и вероятностите за всеки етикет се изпращат към серийния монитор.

1. В функцията `buttonPressed`, заменете кода, който записва на SD картата, с извикване на `classifyImage`, или го добавете след записването на изображението, но **преди** буферът да бъде изтрит:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Ако замените кода, който записва на SD картата, можете да почистите кода си, като премахнете функциите `setupSDCard` и `saveToSDCard`.

1. Качете и изпълнете кода си. Насочете камерата към някакъв плод и натиснете бутон C. Ще видите изхода в серийния монитор:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Ще можете да видите изображението, което е заснето, и тези стойности в раздела **Predictions** в Custom Vision.

    ![Банан в Custom Vision, предсказан като узрял с 56.8% и неузрял с 43.1%](../../../../../translated_images/bg/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Можете да намерите този код в папката [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Вашата програма за класифициране на качеството на плодове беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматичните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.