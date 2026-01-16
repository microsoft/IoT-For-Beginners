<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-28T12:32:05+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "sr"
}
-->
# Класификуј слику - Wio Terminal

У овом делу лекције, послаћете слику коју је камера снимила на услугу Custom Vision ради класификације.

## Класификуј слику

Услуга Custom Vision има REST API који можете позвати са Wio Terminal-а за класификацију слика. Овај REST API се приступа преко HTTPS везе - сигурне HTTP везе.

Приликом интеракције са HTTPS крајњим тачкама, клијентски код мора затражити јавни кључ сертификата од сервера коме се приступа и користити га за шифровање саобраћаја који шаље. Ваш веб прегледач то ради аутоматски, али микроконтролери не. Мораћете ручно да затражите овај сертификат и користите га за креирање сигурне везе са REST API-јем. Ови сертификати се не мењају, па када добијете сертификат, можете га тврдо кодирати у вашој апликацији.

Ови сертификати садрже јавне кључеве и не морају бити чувани као поверљиви. Можете их користити у вашем изворном коду и делити их јавно на местима као што је GitHub.

### Задатак - подеси SSL клијента

1. Отворите пројекат апликације `fruit-quality-detector` ако већ није отворен.

1. Отворите хедер датотеку `config.h` и додајте следеће:

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

    Ово је *Microsoft Azure DigiCert Global Root G2 сертификат* - један од сертификата који користе многе Azure услуге широм света.

    > 💁 Да бисте видели да је ово сертификат који треба користити, покрените следећу команду на macOS-у или Linux-у. Ако користите Windows, можете покренути ову команду користећи [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Излаз ће приказати DigiCert Global Root G2 сертификат.

1. Отворите `main.cpp` и додајте следећу директиву за укључивање:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Испод директива за укључивање, декларишите инстанцу `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Ова класа садржи код за комуникацију са веб крајњим тачкама преко HTTPS-а.

1. У методи `connectWiFi`, подесите да `WiFiClientSecure` користи DigiCert Global Root G2 сертификат:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Задатак - класификуј слику

1. Додајте следеће као додатну линију у листу `lib_deps` у датотеци `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ово увози [ArduinoJson](https://arduinojson.org), Arduino JSON библиотеку, која ће се користити за декодирање JSON одговора из REST API-ја.

1. У `config.h`, додајте константе за URL предикције и кључ из услуге Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Замените `<PREDICTION_URL>` са URL предикције из Custom Vision-а. Замените `<PREDICTION_KEY>` са кључем предикције.

1. У `main.cpp`, додајте директиву за укључивање ArduinoJson библиотеке:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Додајте следећу функцију у `main.cpp`, изнад функције `buttonPressed`.

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

    Овај код почиње декларисањем `HTTPClient` - класе која садржи методе за интеракцију са REST API-јем. Затим повезује клијента са URL-ом предикције користећи инстанцу `WiFiClientSecure` која је подешена са Azure јавним кључем.

    Када се повежете, шаљу се хедери - информације о предстојећем захтеву који ће бити направљен према REST API-ју. Хедер `Content-Type` указује да ће API позив послати сирове бинарне податке, а хедер `Prediction-Key` прослеђује кључ предикције Custom Vision-а.

    Затим се прави POST захтев HTTP клијенту, отпремајући низ бајтова. Ово ће садржати JPEG слику снимљену камером када се ова функција позове.

    > 💁 POST захтеви су намењени за слање података и добијање одговора. Постоје и други типови захтева као што су GET захтеви који преузимају податке. GET захтеве користи ваш веб прегледач за учитавање веб страница.

    POST захтев враћа статусни код одговора. Ово су добро дефинисане вредности, где 200 значи **OK** - POST захтев је био успешан.

    > 💁 Можете видети све статусне кодове одговора на [страници са листом HTTP статусних кодова на Википедији](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Ако се врати 200, резултат се чита из HTTP клијента. Ово је текстуални одговор из REST API-ја са резултатима предикције као JSON документ. JSON је у следећем формату:

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

    Важан део овде је низ `predictions`. Ово садржи предикције, са једним уносом за сваки таг који садржи име тега и вероватноћу. Вероватноће које се враћају су бројеви са покретним зарезом од 0-1, где је 0 шанса од 0% да одговара тегу, а 1 шанса од 100%.

    > 💁 Класификатори слика ће вратити проценат за све тагове који су коришћени. Сваки таг ће имати вероватноћу да слика одговара том тегу.

    Овај JSON се декодира, а вероватноће за сваки таг се шаљу на серијски монитор.

1. У функцији `buttonPressed`, замените код који чува на SD картицу позивом функције `classifyImage`, или га додајте након што је слика записана, али **пре** него што је бафер избрисан:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Ако замените код који чува на SD картицу, можете очистити ваш код уклањањем функција `setupSDCard` и `saveToSDCard`.

1. Отпремите и покрените ваш код. Усмерите камеру ка неком воћу и притисните C дугме. Видећете излаз на серијском монитору:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Моћи ћете да видите слику која је снимљена и ове вредности у картици **Predictions** у Custom Vision-у.

    ![Банана у Custom Vision-у предвиђена као зрела са 56.8% и незрела са 43.1%](../../../../../translated_images/sr/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Овај код можете пронаћи у фасцикли [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Ваш програм за класификацију квалитета воћа је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.