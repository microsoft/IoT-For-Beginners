<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T00:11:15+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "ar"
}
-->
# ضبط مؤقت - Wio Terminal

في هذا الجزء من الدرس، ستقوم باستدعاء الكود الخالي من الخوادم لفهم الكلام، وضبط مؤقت على جهاز Wio Terminal بناءً على النتائج.

## ضبط مؤقت

النص الذي يتم إرجاعه من استدعاء تحويل الكلام إلى نص يحتاج إلى إرساله إلى الكود الخالي من الخوادم ليتم معالجته بواسطة LUIS، حيث يتم إرجاع عدد الثواني للمؤقت. يمكن استخدام هذا العدد من الثواني لضبط المؤقت.

الميكروكنترولرز لا تدعم بشكل طبيعي تعدد الخيوط في Arduino، لذلك لا توجد فئات مؤقت قياسية كما قد تجد عند البرمجة بلغة Python أو لغات عالية المستوى الأخرى. بدلاً من ذلك، يمكنك استخدام مكتبات المؤقت التي تعمل عن طريق قياس الوقت المنقضي في وظيفة `loop` واستدعاء الوظائف عند انتهاء الوقت.

### المهمة - إرسال النص إلى الدالة الخالية من الخوادم

1. افتح مشروع `smart-timer` في VS Code إذا لم يكن مفتوحًا بالفعل.

1. افتح ملف الرأس `config.h` وأضف عنوان URL لتطبيق الدالة الخاص بك:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    استبدل `<URL>` بعنوان URL لتطبيق الدالة الذي حصلت عليه في الخطوة الأخيرة من الدرس السابق، مشيرًا إلى عنوان IP لجهازك المحلي الذي يشغل تطبيق الدالة.

1. أنشئ ملفًا جديدًا في مجلد `src` باسم `language_understanding.h`. سيتم استخدام هذا الملف لتعريف فئة لإرسال الكلام المعترف به إلى تطبيق الدالة لتحويله إلى ثوانٍ باستخدام LUIS.

1. أضف ما يلي إلى أعلى هذا الملف:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    يتضمن هذا بعض ملفات الرأس المطلوبة.

1. عرف فئة باسم `LanguageUnderstanding`، وأعلن عن مثيل لهذه الفئة:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. لاستدعاء تطبيق الدالة الخاص بك، تحتاج إلى إعلان عميل WiFi. أضف ما يلي إلى القسم `private` من الفئة:

    ```cpp
    WiFiClient _client;
    ```

1. في القسم `public`، أعلن عن طريقة باسم `GetTimerDuration` لاستدعاء تطبيق الدالة:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. في طريقة `GetTimerDuration`، أضف الكود التالي لبناء JSON ليتم إرساله إلى تطبيق الدالة:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    يقوم هذا بتحويل النص الممرر إلى طريقة `GetTimerDuration` إلى JSON بالشكل التالي:

    ```json
    {
        "text" : "<text>"
    }
    ```

    حيث `<text>` هو النص الممرر إلى الدالة.

1. أسفل هذا، أضف الكود التالي لإجراء استدعاء لتطبيق الدالة:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    يقوم هذا بإجراء طلب POST إلى تطبيق الدالة، مع تمرير جسم JSON والحصول على رمز الاستجابة.

1. أضف الكود التالي أسفل هذا:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    يتحقق هذا الكود من رمز الاستجابة. إذا كان 200 (نجاح)، يتم استرداد عدد الثواني للمؤقت من جسم الاستجابة. خلاف ذلك، يتم إرسال خطأ إلى شاشة المراقبة التسلسلية ويتم تعيين عدد الثواني إلى 0.

1. أضف الكود التالي إلى نهاية هذه الطريقة لإغلاق الاتصال بـ HTTP وإرجاع عدد الثواني:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. في ملف `main.cpp`، قم بتضمين ملف الرأس الجديد هذا:

    ```cpp
    #include "speech_to_text.h"
    ```

1. في نهاية وظيفة `processAudio`، استدعِ طريقة `GetTimerDuration` للحصول على مدة المؤقت:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    يقوم هذا بتحويل النص من استدعاء فئة `SpeechToText` إلى عدد الثواني للمؤقت.

### المهمة - ضبط مؤقت

يمكن استخدام عدد الثواني لضبط مؤقت.

1. أضف تبعية مكتبة المؤقت إلى ملف `platformio.ini` لإضافة مكتبة لضبط المؤقت:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. أضف توجيه تضمين لهذه المكتبة إلى ملف `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. فوق وظيفة `processAudio`، أضف الكود التالي:

    ```cpp
    auto timer = timer_create_default();
    ```

    يقوم هذا الكود بإعلان مؤقت باسم `timer`.

1. أسفل هذا، أضف الكود التالي:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    تقوم وظيفة `say` في النهاية بتحويل النص إلى كلام، ولكن في الوقت الحالي ستكتب النص الممرر إلى شاشة المراقبة التسلسلية.

1. أسفل وظيفة `say`، أضف الكود التالي:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    هذه وظيفة رد نداء يتم استدعاؤها عند انتهاء المؤقت. يتم تمرير رسالة لتُقال عند انتهاء المؤقت. يمكن أن تتكرر المؤقتات، ويمكن التحكم في ذلك من خلال قيمة الإرجاع لهذه الوظيفة - تُرجع `false`، لإخبار المؤقت بعدم التشغيل مرة أخرى.

1. أضف الكود التالي إلى نهاية وظيفة `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    يتحقق هذا الكود من إجمالي عدد الثواني، وإذا كان 0، فإنه يعود من استدعاء الوظيفة بحيث لا يتم ضبط أي مؤقتات. ثم يقوم بتحويل إجمالي عدد الثواني إلى دقائق وثوانٍ.

1. أسفل هذا الكود، أضف ما يلي لإنشاء رسالة تُقال عند بدء المؤقت:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. أسفل هذا، أضف كودًا مشابهًا لإنشاء رسالة تُقال عند انتهاء المؤقت:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. بعد ذلك، قل رسالة بدء المؤقت:

    ```cpp
    say(begin_message);
    ```

1. في نهاية هذه الوظيفة، قم بتشغيل المؤقت:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    يقوم هذا بتشغيل المؤقت. يتم ضبط المؤقت باستخدام المللي ثانية، لذلك يتم ضرب إجمالي عدد الثواني في 1,000 لتحويله إلى مللي ثانية. يتم تمرير وظيفة `timerExpired` كوظيفة رد نداء، ويتم تمرير `end_message` كوسيطة لتمريرها إلى رد النداء. تقبل هذه الوظيفة فقط الوسيطات من النوع `void *`، لذلك يتم تحويل النص بشكل مناسب.

1. أخيرًا، يحتاج المؤقت إلى *العمل*، ويتم ذلك في وظيفة `loop`. أضف الكود التالي إلى نهاية وظيفة `loop`:

    ```cpp
    timer.tick();
    ```

1. قم ببناء هذا الكود، وارفعه إلى جهاز Wio Terminal الخاص بك واختبره من خلال شاشة المراقبة التسلسلية. بمجرد رؤية `Ready` في شاشة المراقبة التسلسلية، اضغط على الزر C (الزر الموجود على الجانب الأيسر، الأقرب إلى مفتاح التشغيل)، وتحدث. سيتم التقاط 4 ثوانٍ من الصوت، وتحويلها إلى نص، ثم إرسالها إلى تطبيق الدالة الخاص بك، وسيتم ضبط مؤقت. تأكد من تشغيل تطبيق الدالة الخاص بك محليًا.

    سترى متى يبدأ المؤقت، ومتى ينتهي.

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
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 يمكنك العثور على هذا الكود في المجلد [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 لقد نجح برنامج المؤقت الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية هو المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.