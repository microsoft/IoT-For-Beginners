# تصنيف صورة - Wio Terminal

في هذا الجزء من الدرس، ستقوم بإرسال الصورة التي التقطتها الكاميرا إلى خدمة Custom Vision لتصنيفها.

## تصنيف صورة

تحتوي خدمة Custom Vision على واجهة برمجة تطبيقات REST يمكنك استدعاؤها من Wio Terminal لتصنيف الصور. يتم الوصول إلى واجهة برمجة التطبيقات هذه عبر اتصال HTTPS - وهو اتصال HTTP آمن.

عند التفاعل مع نقاط نهاية HTTPS، يحتاج كود العميل إلى طلب شهادة المفتاح العام من الخادم الذي يتم الوصول إليه، واستخدامها لتشفير البيانات المرسلة. يقوم متصفح الويب الخاص بك بذلك تلقائيًا، لكن وحدات التحكم الدقيقة لا تفعل ذلك. ستحتاج إلى طلب هذه الشهادة يدويًا واستخدامها لإنشاء اتصال آمن مع واجهة برمجة التطبيقات REST. هذه الشهادات لا تتغير، لذا بمجرد الحصول على شهادة، يمكن تضمينها بشكل ثابت في تطبيقك.

تحتوي هذه الشهادات على مفاتيح عامة، ولا تحتاج إلى أن تكون آمنة. يمكنك استخدامها في كود المصدر الخاص بك ومشاركتها علنًا في أماكن مثل GitHub.

### المهمة - إعداد عميل SSL

1. افتح مشروع تطبيق `fruit-quality-detector` إذا لم يكن مفتوحًا بالفعل.

1. افتح ملف الرأس `config.h`، وأضف ما يلي:

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

    هذه هي *شهادة Microsoft Azure DigiCert Global Root G2* - وهي واحدة من الشهادات المستخدمة من قبل العديد من خدمات Azure عالميًا.

    > 💁 لرؤية أن هذه هي الشهادة التي يجب استخدامها، قم بتشغيل الأمر التالي على macOS أو Linux. إذا كنت تستخدم Windows، يمكنك تشغيل هذا الأمر باستخدام [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > سيعرض الإخراج شهادة DigiCert Global Root G2.

1. افتح `main.cpp` وأضف توجيه التضمين التالي:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. أسفل توجيهات التضمين، قم بتعريف مثيل لـ `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    تحتوي هذه الفئة على كود للتواصل مع نقاط نهاية الويب عبر HTTPS.

1. في طريقة `connectWiFi`، قم بتعيين WiFiClientSecure لاستخدام شهادة DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### المهمة - تصنيف صورة

1. أضف السطر التالي كإضافة إلى قائمة `lib_deps` في ملف `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    يقوم هذا باستيراد [ArduinoJson](https://arduinojson.org)، وهي مكتبة JSON لـ Arduino، وستُستخدم لفك تشفير استجابة JSON من واجهة برمجة التطبيقات REST.

1. في `config.h`، أضف ثوابت لعنوان التنبؤ والمفتاح من خدمة Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    استبدل `<PREDICTION_URL>` بعنوان التنبؤ من Custom Vision. استبدل `<PREDICTION_KEY>` بمفتاح التنبؤ.

1. في `main.cpp`، أضف توجيه تضمين لمكتبة ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. أضف الوظيفة التالية إلى `main.cpp`، فوق وظيفة `buttonPressed`.

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

    يبدأ هذا الكود بتعريف `HTTPClient` - وهي فئة تحتوي على طرق للتفاعل مع واجهات برمجة التطبيقات REST. ثم يقوم بتوصيل العميل بعنوان التنبؤ باستخدام مثيل `WiFiClientSecure` الذي تم إعداده باستخدام المفتاح العام لـ Azure.

    بمجرد الاتصال، يتم إرسال الرؤوس - وهي معلومات حول الطلب القادم الذي سيتم إجراؤه ضد واجهة برمجة التطبيقات REST. يشير رأس `Content-Type` إلى أن استدعاء واجهة برمجة التطبيقات سيرسل بيانات ثنائية خام، بينما يمرر رأس `Prediction-Key` مفتاح التنبؤ الخاص بـ Custom Vision.

    بعد ذلك، يتم إرسال طلب POST إلى عميل HTTP، مع تحميل مصفوفة بايت. ستحتوي هذه المصفوفة على صورة JPEG التي تم التقاطها من الكاميرا عند استدعاء هذه الوظيفة.

    > 💁 طلبات POST مخصصة لإرسال البيانات والحصول على استجابة. هناك أنواع أخرى من الطلبات مثل طلبات GET التي تسترجع البيانات. يتم استخدام طلبات GET من قبل متصفح الويب الخاص بك لتحميل صفحات الويب.

    يعيد طلب POST رمز حالة استجابة. هذه القيم محددة جيدًا، حيث يعني 200 **OK** - أن طلب POST كان ناجحًا.

    > 💁 يمكنك رؤية جميع رموز حالة الاستجابة في [صفحة قائمة رموز حالة HTTP على ويكيبيديا](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    إذا تم إرجاع 200، يتم قراءة النتيجة من عميل HTTP. هذه استجابة نصية من واجهة برمجة التطبيقات REST تحتوي على نتائج التنبؤ كوثيقة JSON. يكون JSON بالتنسيق التالي:

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

    الجزء المهم هنا هو مصفوفة `predictions`. تحتوي هذه المصفوفة على التنبؤات، مع إدخال واحد لكل علامة يحتوي على اسم العلامة والاحتمالية. الاحتمالات التي يتم إرجاعها هي أرقام عشرية تتراوح من 0-1، حيث 0 تعني احتمال 0% لمطابقة العلامة، و1 تعني احتمال 100%.

    > 💁 ستعيد مصنفات الصور النسب المئوية لجميع العلامات التي تم استخدامها. سيكون لكل علامة احتمال أن الصورة تطابق تلك العلامة.

    يتم فك تشفير JSON، ويتم إرسال الاحتمالات لكل علامة إلى شاشة المراقبة التسلسلية.

1. في وظيفة `buttonPressed`، استبدل الكود الذي يحفظ على بطاقة SD باستدعاء `classifyImage`، أو أضفه بعد كتابة الصورة، ولكن **قبل** حذف المخزن المؤقت:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 إذا استبدلت الكود الذي يحفظ على بطاقة SD، يمكنك تنظيف الكود الخاص بك عن طريق إزالة وظائف `setupSDCard` و`saveToSDCard`.

1. قم بتحميل وتشغيل الكود الخاص بك. وجه الكاميرا نحو بعض الفواكه واضغط على الزر C. سترى الإخراج في شاشة المراقبة التسلسلية:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    ستتمكن من رؤية الصورة التي تم التقاطها، وهذه القيم في علامة التبويب **Predictions** في Custom Vision.

    ![موزة في Custom Vision تم التنبؤ بأنها ناضجة بنسبة 56.8% وغير ناضجة بنسبة 43.1%](../../../../../translated_images/ar/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 يمكنك العثور على هذا الكود في المجلد [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 لقد نجح برنامج تصنيف جودة الفواكه الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.