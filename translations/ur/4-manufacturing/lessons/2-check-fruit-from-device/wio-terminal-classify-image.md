<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-26T21:51:34+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "ur"
}
-->
# تصویر کو درجہ بندی کریں - Wio Terminal

اس سبق کے اس حصے میں، آپ کیمرے سے لی گئی تصویر کو Custom Vision سروس پر بھیجیں گے تاکہ اسے درجہ بندی کیا جا سکے۔

## تصویر کو درجہ بندی کریں

Custom Vision سروس میں ایک REST API موجود ہے جسے آپ Wio Terminal سے تصاویر کی درجہ بندی کے لیے کال کر سکتے ہیں۔ یہ REST API ایک HTTPS کنکشن کے ذریعے قابل رسائی ہے - جو کہ ایک محفوظ HTTP کنکشن ہے۔

جب HTTPS endpoints کے ساتھ تعامل کرتے ہیں، تو کلائنٹ کوڈ کو اس سرور سے عوامی کلید کا سرٹیفکیٹ طلب کرنا ہوتا ہے جس تک رسائی حاصل کی جا رہی ہے، اور اس کا استعمال کرتے ہوئے بھیجی گئی ٹریفک کو انکرپٹ کرنا ہوتا ہے۔ آپ کا ویب براؤزر یہ خود بخود کرتا ہے، لیکن مائیکرو کنٹرولرز ایسا نہیں کرتے۔ آپ کو یہ سرٹیفکیٹ دستی طور پر طلب کرنا ہوگا اور اسے REST API کے ساتھ محفوظ کنکشن بنانے کے لیے استعمال کرنا ہوگا۔ یہ سرٹیفکیٹس تبدیل نہیں ہوتے، لہذا ایک بار جب آپ کے پاس سرٹیفکیٹ ہو، تو اسے آپ کی ایپلیکیشن میں ہارڈ کوڈ کیا جا سکتا ہے۔

یہ سرٹیفکیٹس عوامی کلیدیں رکھتے ہیں اور انہیں محفوظ رکھنے کی ضرورت نہیں ہوتی۔ آپ انہیں اپنے سورس کوڈ میں استعمال کر سکتے ہیں اور انہیں عوامی جگہوں جیسے GitHub پر شیئر کر سکتے ہیں۔

### کام - SSL کلائنٹ سیٹ اپ کریں

1. `fruit-quality-detector` ایپ پروجیکٹ کھولیں اگر یہ پہلے سے کھلا نہیں ہے۔

1. `config.h` ہیڈر فائل کھولیں، اور درج ذیل شامل کریں:

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

    یہ *Microsoft Azure DigiCert Global Root G2 certificate* ہے - یہ ان سرٹیفکیٹس میں سے ایک ہے جو دنیا بھر میں بہت سے Azure سروسز استعمال کرتے ہیں۔

    > 💁 یہ دیکھنے کے لیے کہ یہ استعمال کرنے کے لیے صحیح سرٹیفکیٹ ہے، macOS یا Linux پر درج ذیل کمانڈ چلائیں۔ اگر آپ Windows استعمال کر رہے ہیں، تو آپ یہ کمانڈ [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) استعمال کرتے ہوئے چلا سکتے ہیں:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > آؤٹ پٹ DigiCert Global Root G2 سرٹیفکیٹ کی فہرست دے گا۔

1. `main.cpp` کھولیں اور درج ذیل include directive شامل کریں:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. include directives کے نیچے، `WifiClientSecure` کا ایک instance ڈکلیئر کریں:

    ```cpp
    WiFiClientSecure client;
    ```

    یہ کلاس HTTPS کے ذریعے ویب endpoints کے ساتھ بات چیت کرنے کے لیے کوڈ پر مشتمل ہے۔

1. `connectWiFi` میتھڈ میں، WiFiClientSecure کو DigiCert Global Root G2 سرٹیفکیٹ استعمال کرنے کے لیے سیٹ کریں:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### کام - تصویر کو درجہ بندی کریں

1. `platformio.ini` فائل میں `lib_deps` لسٹ میں درج ذیل کو ایک اضافی لائن کے طور پر شامل کریں:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    یہ [ArduinoJson](https://arduinojson.org)، ایک Arduino JSON لائبریری، کو درآمد کرتا ہے، اور REST API کے JSON جواب کو ڈی کوڈ کرنے کے لیے استعمال کیا جائے گا۔

1. `config.h` میں، Custom Vision سروس سے prediction URL اور Key کے لیے constants شامل کریں:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` کو Custom Vision سے prediction URL کے ساتھ تبدیل کریں۔ `<PREDICTION_KEY>` کو prediction key کے ساتھ تبدیل کریں۔

1. `main.cpp` میں، ArduinoJson لائبریری کے لیے ایک include directive شامل کریں:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp` میں، `buttonPressed` فنکشن کے اوپر درج ذیل فنکشن شامل کریں:

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

    یہ کوڈ ایک `HTTPClient` ڈکلیئر کرنے سے شروع ہوتا ہے - ایک کلاس جو REST APIs کے ساتھ تعامل کرنے کے لیے میتھڈز پر مشتمل ہے۔ پھر یہ کلائنٹ کو Azure عوامی کلید کے ساتھ سیٹ اپ کیے گئے `WiFiClientSecure` instance کا استعمال کرتے ہوئے prediction URL سے جوڑتا ہے۔

    ایک بار جڑنے کے بعد، یہ headers بھیجتا ہے - REST API کے خلاف کیے جانے والے آنے والے درخواست کے بارے میں معلومات۔ `Content-Type` header اشارہ کرتا ہے کہ API کال خام بائنری ڈیٹا بھیجے گی، `Prediction-Key` header Custom Vision prediction key کو پاس کرتا ہے۔

    اس کے بعد HTTP کلائنٹ پر ایک POST درخواست کی جاتی ہے، جس میں ایک byte array اپلوڈ کیا جاتا ہے۔ یہ اس وقت کیمرے سے لی گئی JPEG تصویر پر مشتمل ہوگا جب یہ فنکشن کال کیا جائے گا۔

    > 💁 POST درخواستیں ڈیٹا بھیجنے اور جواب حاصل کرنے کے لیے ہوتی ہیں۔ دیگر درخواست کی اقسام جیسے GET درخواستیں ڈیٹا حاصل کرتی ہیں۔ GET درخواستیں آپ کا ویب براؤزر ویب صفحات لوڈ کرنے کے لیے استعمال کرتا ہے۔

    POST درخواست ایک response status code واپس کرتی ہے۔ یہ اچھی طرح سے متعین کردہ اقدار ہیں، جن میں 200 کا مطلب **OK** ہے - POST درخواست کامیاب رہی۔

    > 💁 آپ تمام response status codes کو [List of HTTP status codes page on Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes) پر دیکھ سکتے ہیں۔

    اگر 200 واپس کیا جاتا ہے، تو نتیجہ HTTP کلائنٹ سے پڑھا جاتا ہے۔ یہ REST API سے پیش گوئی کے نتائج کے ساتھ ایک JSON دستاویز کے طور پر ایک text response ہے۔ JSON درج ذیل فارمیٹ میں ہے:

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

    یہاں اہم حصہ `predictions` array ہے۔ اس میں پیش گوئیاں شامل ہیں، ہر tag کے لیے ایک entry کے ساتھ جس میں tag کا نام اور probability شامل ہے۔ واپس کی گئی probabilities 0-1 کے floating point numbers ہیں، جہاں 0 کا مطلب ہے کہ tag سے مطابقت کا 0% امکان ہے، اور 1 کا مطلب ہے کہ tag سے مطابقت کا 100% امکان ہے۔

    > 💁 تصویر کے classifiers تمام tags کے لیے فیصد واپس کریں گے جو استعمال کیے گئے ہیں۔ ہر tag کے پاس اس بات کا امکان ہوگا کہ تصویر اس tag سے مطابقت رکھتی ہے۔

    یہ JSON ڈی کوڈ کیا جاتا ہے، اور ہر tag کے لیے probabilities کو serial monitor پر بھیجا جاتا ہے۔

1. `buttonPressed` فنکشن میں، SD کارڈ پر محفوظ کرنے والے کوڈ کو `classifyImage` کال کے ساتھ تبدیل کریں، یا اسے تصویر لکھنے کے بعد شامل کریں، لیکن **buffer کو حذف کرنے سے پہلے**:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 اگر آپ SD کارڈ پر محفوظ کرنے والے کوڈ کو تبدیل کرتے ہیں تو آپ اپنے کوڈ کو صاف کر سکتے ہیں اور `setupSDCard` اور `saveToSDCard` فنکشنز کو ہٹا سکتے ہیں۔

1. اپنا کوڈ اپلوڈ کریں اور چلائیں۔ کیمرے کو کچھ پھلوں کی طرف اشارہ کریں اور C بٹن دبائیں۔ آپ serial monitor میں آؤٹ پٹ دیکھ سکیں گے:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    آپ Custom Vision کے **Predictions** tab میں لی گئی تصویر اور ان اقدار کو دیکھ سکیں گے۔

    ![ایک کیلا Custom Vision میں 56.8% پکا ہوا اور 43.1% کچا ہونے کی پیش گوئی کے ساتھ](../../../../../translated_images/ur/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 آپ اس کوڈ کو [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا پھل معیار درجہ بندی کرنے والا پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔