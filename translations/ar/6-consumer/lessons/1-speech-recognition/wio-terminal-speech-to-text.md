<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T00:27:50+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "ar"
}
-->
# تحويل الكلام إلى نص - Wio Terminal

في هذا الجزء من الدرس، ستكتب كودًا لتحويل الكلام في الصوت المسجل إلى نص باستخدام خدمة الكلام.

## إرسال الصوت إلى خدمة الكلام

يمكن إرسال الصوت إلى خدمة الكلام باستخدام واجهة برمجة التطبيقات REST. لاستخدام خدمة الكلام، تحتاج أولاً إلى طلب رمز وصول، ثم استخدام هذا الرمز للوصول إلى واجهة برمجة التطبيقات REST. تنتهي صلاحية رموز الوصول بعد 10 دقائق، لذا يجب أن يطلب الكود الخاص بك هذه الرموز بانتظام لضمان تحديثها دائمًا.

### المهمة - الحصول على رمز الوصول

1. افتح مشروع `smart-timer` إذا لم يكن مفتوحًا بالفعل.

1. أضف تبعيات المكتبة التالية إلى ملف `platformio.ini` للوصول إلى WiFi ومعالجة JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. أضف الكود التالي إلى ملف الرأس `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    استبدل `<SSID>` و `<PASSWORD>` بالقيم المناسبة لشبكة WiFi الخاصة بك.

    استبدل `<API_KEY>` بمفتاح API الخاص بمورد خدمة الكلام. استبدل `<LOCATION>` بالموقع الذي استخدمته عند إنشاء مورد خدمة الكلام.

    استبدل `<LANGUAGE>` باسم اللغة التي ستتحدث بها، على سبيل المثال `en-GB` للإنجليزية أو `zn-HK` للكانتونية. يمكنك العثور على قائمة باللغات المدعومة وأسماء المواقع الخاصة بها في [وثائق دعم اللغة والصوت على Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    الثابت `TOKEN_URL` هو عنوان URL لمصدر الرموز بدون الموقع. سيتم دمجه مع الموقع لاحقًا للحصول على عنوان URL الكامل.

1. تمامًا مثل الاتصال بـ Custom Vision، ستحتاج إلى استخدام اتصال HTTPS للاتصال بخدمة إصدار الرموز. أضف الكود التالي إلى نهاية `config.h`:

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

    هذه هي نفس الشهادة التي استخدمتها عند الاتصال بـ Custom Vision.

1. أضف تضمينًا لملف الرأس الخاص بـ WiFi وملف الرأس الخاص بـ config إلى أعلى ملف `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. أضف كودًا للاتصال بـ WiFi في `main.cpp` فوق وظيفة `setup`:

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

1. استدعِ هذه الوظيفة من وظيفة `setup` بعد إنشاء الاتصال التسلسلي:

    ```cpp
    connectWiFi();
    ```

1. أنشئ ملف رأس جديد في مجلد `src` يسمى `speech_to_text.h`. في هذا الملف، أضف الكود التالي:

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

    يتضمن هذا بعض ملفات الرأس الضرورية لاتصال HTTP، التكوين وملف الرأس `mic.h`، ويعرّف فئة تسمى `SpeechToText`، قبل إعلان مثيل لهذه الفئة يمكن استخدامه لاحقًا.

1. أضف الحقلين التاليين إلى القسم `private` من هذه الفئة:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` هو عميل WiFi يستخدم HTTPS وسيتم استخدامه للحصول على رمز الوصول. سيتم تخزين هذا الرمز لاحقًا في `_access_token`.

1. أضف الطريقة التالية إلى القسم `private`:

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

    يقوم هذا الكود ببناء عنوان URL لواجهة برمجة التطبيقات الخاصة بمصدر الرموز باستخدام موقع مورد الكلام. ثم ينشئ `HTTPClient` لإجراء طلب الويب، ويقوم بإعداده لاستخدام عميل WiFi المكوّن بشهادة نقاط نهاية الرموز. يضع مفتاح API كعنوان للطلب. ثم يقوم بإجراء طلب POST للحصول على الشهادة، ويعيد المحاولة إذا حصل على أي أخطاء. وأخيرًا يتم إرجاع رمز الوصول.

1. إلى القسم `public`، أضف طريقة للحصول على رمز الوصول. ستكون هذه الطريقة مطلوبة في الدروس اللاحقة لتحويل النص إلى كلام.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. إلى القسم `public`، أضف طريقة `init` لإعداد عميل الرموز:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    يقوم هذا بتعيين الشهادة على عميل WiFi، ثم يحصل على رمز الوصول.

1. في `main.cpp`، أضف ملف الرأس الجديد إلى توجيهات التضمين:

    ```cpp
    #include "speech_to_text.h"
    ```

1. قم بتهيئة فئة `SpeechToText` في نهاية وظيفة `setup`، بعد استدعاء `mic.init` ولكن قبل كتابة `Ready` إلى المراقب التسلسلي:

    ```cpp
    speechToText.init();
    ```

### المهمة - قراءة الصوت من ذاكرة الفلاش

1. في جزء سابق من هذا الدرس، تم تسجيل الصوت في ذاكرة الفلاش. يجب إرسال هذا الصوت إلى واجهة برمجة التطبيقات REST الخاصة بخدمات الكلام، لذا يجب قراءته من ذاكرة الفلاش. لا يمكن تحميله في ذاكرة مؤقتة لأنه سيكون كبيرًا جدًا. يمكن لفئة `HTTPClient` التي تقوم بإجراء طلبات REST أن تبث البيانات باستخدام Arduino Stream - وهي فئة يمكنها تحميل البيانات في أجزاء صغيرة، وإرسال الأجزاء واحدة تلو الأخرى كجزء من الطلب. في كل مرة تستدعي `read` على stream، يتم إرجاع الكتلة التالية من البيانات. يمكن إنشاء stream من Arduino يمكنه القراءة من ذاكرة الفلاش. أنشئ ملفًا جديدًا يسمى `flash_stream.h` في مجلد `src`، وأضف الكود التالي إليه:

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

    يعلن هذا عن فئة `FlashStream`، مشتقة من فئة Arduino `Stream`. هذه فئة مجردة - يجب على الفئات المشتقة تنفيذ بعض الطرق قبل أن يتم إنشاء مثيل للفئة، ويتم تعريف هذه الطرق في هذه الفئة.

    ✅ اقرأ المزيد عن Arduino Streams في [وثائق Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. أضف الحقول التالية إلى القسم `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    يعرّف هذا ذاكرة مؤقتة مؤقتة لتخزين البيانات المقروءة من ذاكرة الفلاش، إلى جانب الحقول لتخزين الموضع الحالي عند القراءة من الذاكرة المؤقتة، العنوان الحالي للقراءة من ذاكرة الفلاش، وجهاز ذاكرة الفلاش.

1. في القسم `private`، أضف الطريقة التالية:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    يقوم هذا الكود بالقراءة من ذاكرة الفلاش عند العنوان الحالي ويخزن البيانات في ذاكرة مؤقتة. ثم يزيد العنوان، بحيث تقرأ المكالمة التالية الكتلة التالية من الذاكرة. يتم تحديد حجم الذاكرة المؤقتة بناءً على أكبر كتلة سيرسلها `HTTPClient` إلى واجهة برمجة التطبيقات REST في وقت واحد.

    > 💁 يجب مسح ذاكرة الفلاش باستخدام حجم الحبوب، أما القراءة فلا تحتاج لذلك.

1. في القسم `public` من هذه الفئة، أضف منشئًا:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    يقوم هذا المنشئ بإعداد جميع الحقول لبدء القراءة من بداية كتلة ذاكرة الفلاش، ويقوم بتحميل أول كتلة من البيانات في الذاكرة المؤقتة.

1. نفذ طريقة `write`. سيقوم هذا stream فقط بقراءة البيانات، لذا يمكن أن يفعل هذا لا شيء ويعيد 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. نفذ طريقة `peek`. تقوم هذه الطريقة بإرجاع البيانات عند الموضع الحالي دون تحريك stream. استدعاء `peek` عدة مرات سيعيد دائمًا نفس البيانات طالما لم يتم قراءة أي بيانات من stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. نفذ وظيفة `available`. تقوم هذه الوظيفة بإرجاع عدد البايتات التي يمكن قراءتها من stream، أو -1 إذا كان stream مكتملًا. بالنسبة لهذه الفئة، الحد الأقصى المتاح لن يكون أكثر من حجم كتلة HTTPClient. عندما يتم استخدام هذا stream في عميل HTTP، فإنه يستدعي هذه الوظيفة لمعرفة مقدار البيانات المتاحة، ثم يطلب هذا المقدار لإرساله إلى واجهة برمجة التطبيقات REST. لا نريد أن تكون كل كتلة أكبر من حجم كتلة HTTPClient، لذا إذا كان المتاح أكثر من ذلك، يتم إرجاع حجم الكتلة. إذا كان أقل، يتم إرجاع ما هو متاح. بمجرد بث جميع البيانات، يتم إرجاع -1.

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

1. نفذ طريقة `read` لإرجاع البايت التالي من الذاكرة المؤقتة، مع زيادة الموضع. إذا تجاوز الموضع حجم الذاكرة المؤقتة، فإنه يملأ الذاكرة المؤقتة بالكتلة التالية من ذاكرة الفلاش ويعيد تعيين الموضع.

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

1. في ملف الرأس `speech_to_text.h`، أضف توجيه تضمين لهذا الملف الجديد:

    ```cpp
    #include "flash_stream.h"
    ```

### المهمة - تحويل الكلام إلى نص

1. يمكن تحويل الكلام إلى نص عن طريق إرسال الصوت إلى خدمة الكلام عبر واجهة برمجة التطبيقات REST. تحتوي واجهة برمجة التطبيقات REST هذه على شهادة مختلفة عن مصدر الرموز، لذا أضف الكود التالي إلى ملف الرأس `config.h` لتعريف هذه الشهادة:

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

1. أضف ثابتًا إلى هذا الملف لعنوان URL الخاص بالكلام بدون الموقع. سيتم دمجه مع الموقع واللغة لاحقًا للحصول على عنوان URL الكامل.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. في ملف الرأس `speech_to_text.h`، في القسم `private` من فئة `SpeechToText`، عرّف حقلًا لعميل WiFi باستخدام شهادة الكلام:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. في طريقة `init`، قم بتعيين الشهادة على هذا العميل:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. أضف الكود التالي إلى القسم `public` من فئة `SpeechToText` لتعريف طريقة لتحويل الكلام إلى نص:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. أضف الكود التالي إلى هذه الطريقة لإنشاء عميل HTTP باستخدام عميل WiFi المكوّن بشهادة الكلام، واستخدام عنوان URL الخاص بالكلام مع الموقع واللغة:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. يجب تعيين بعض العناوين على الاتصال:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    يقوم هذا بتعيين عناوين للتفويض باستخدام رمز الوصول، تنسيق الصوت باستخدام معدل العينة، ويحدد أن العميل يتوقع النتيجة كـ JSON.

1. بعد ذلك، أضف الكود التالي لإجراء طلب واجهة برمجة التطبيقات REST:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    يقوم هذا بإنشاء `FlashStream` ويستخدمه لبث البيانات إلى واجهة برمجة التطبيقات REST.

1. أسفل هذا، أضف الكود التالي:

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

    يقوم هذا الكود بالتحقق من رمز الاستجابة.

    إذا كان 200، وهو رمز النجاح، يتم استرداد النتيجة، فك تشفيرها من JSON، ويتم تعيين خاصية `DisplayText` في المتغير `text`. هذه هي الخاصية التي يتم فيها إرجاع النص الذي يمثل الكلام.

    إذا كان رمز الاستجابة 401، فإن رمز الوصول قد انتهت صلاحيته (هذه الرموز تستمر فقط لمدة 10 دقائق). يتم طلب رمز وصول جديد، ويتم إجراء المكالمة مرة أخرى.

    خلاف ذلك، يتم إرسال خطأ إلى المراقب التسلسلي، ويتم ترك `text` فارغًا.

1. أضف الكود التالي إلى نهاية هذه الطريقة لإغلاق عميل HTTP وإرجاع النص:

    ```cpp
    httpClient.end();

    return text;
    ```

1. في `main.cpp`، استدعِ طريقة `convertSpeechToText` الجديدة في وظيفة `processAudio`، ثم قم بتسجيل الكلام في المراقب التسلسلي:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. قم ببناء هذا الكود، ورفعه إلى Wio Terminal الخاص بك واختبره من خلال المراقب التسلسلي. بمجرد رؤية `Ready` في المراقب التسلسلي، اضغط على زر C (الزر الموجود على الجانب الأيسر، الأقرب إلى مفتاح التشغيل)، وتحدث. سيتم التقاط 4 ثوانٍ من الصوت، ثم تحويلها إلى نص.

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

> 💁 يمكنك العثور على هذا الكود في مجلد [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 لقد نجحت في برنامج تحويل الكلام إلى نص!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.