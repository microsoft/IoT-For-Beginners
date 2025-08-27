<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-26T23:17:35+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "ar"
}
-->
# التحكم في ضوء الليل عبر الإنترنت - Wio Terminal

في هذا الجزء من الدرس، ستقوم بإرسال بيانات التتبع الخاصة بمستويات الضوء من جهاز Wio Terminal إلى وسيط MQTT.

## تثبيت مكتبات JSON الخاصة بـ Arduino

طريقة شائعة لإرسال الرسائل عبر MQTT هي استخدام JSON. هناك مكتبة Arduino لـ JSON تسهل قراءة وكتابة مستندات JSON.

### المهمة

قم بتثبيت مكتبة Arduino JSON.

1. افتح مشروع ضوء الليل في VS Code.

1. أضف السطر التالي كخط إضافي إلى قائمة `lib_deps` في ملف `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    هذا يقوم باستيراد [ArduinoJson](https://arduinojson.org)، وهي مكتبة JSON خاصة بـ Arduino.

## نشر بيانات التتبع

الخطوة التالية هي إنشاء مستند JSON يحتوي على بيانات التتبع وإرساله إلى وسيط MQTT.

### المهمة - نشر بيانات التتبع

قم بنشر بيانات التتبع إلى وسيط MQTT.

1. أضف الكود التالي إلى أسفل ملف `config.h` لتعريف اسم موضوع التتبع الخاص بوسيط MQTT:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` هو الموضوع الذي سيقوم الجهاز بنشر مستويات الضوء عليه.

1. افتح ملف `main.cpp`.

1. أضف توجيه `#include` التالي إلى أعلى الملف:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. أضف الكود التالي داخل دالة `loop`، مباشرة قبل `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    يقوم هذا الكود بقراءة مستوى الضوء، وإنشاء مستند JSON باستخدام ArduinoJson يحتوي على هذا المستوى. يتم بعد ذلك تحويله إلى سلسلة نصية ونشره على موضوع التتبع الخاص بـ MQTT بواسطة عميل MQTT.

1. قم برفع الكود إلى جهاز Wio Terminal الخاص بك، واستخدم Serial Monitor لرؤية مستويات الضوء التي يتم إرسالها إلى وسيط MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 يمكنك العثور على هذا الكود في المجلد [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 لقد قمت بنجاح بإرسال بيانات التتبع من جهازك.

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.