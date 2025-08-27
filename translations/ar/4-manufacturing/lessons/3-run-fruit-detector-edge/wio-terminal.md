<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-26T22:03:20+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "ar"
}
-->
# تصنيف صورة باستخدام مصنف صور يعتمد على IoT Edge - Wio Terminal

في هذا الجزء من الدرس، ستستخدم مصنف الصور الذي يعمل على جهاز IoT Edge.

## استخدام مصنف IoT Edge

يمكن إعادة توجيه جهاز IoT لاستخدام مصنف الصور الخاص بـ IoT Edge. عنوان URL الخاص بمصنف الصور هو `http://<عنوان IP أو الاسم>/image`، مع استبدال `<عنوان IP أو الاسم>` بعنوان IP أو اسم المضيف الخاص بالحاسوب الذي يعمل عليه IoT Edge.

### المهمة - استخدام مصنف IoT Edge

1. افتح مشروع تطبيق `fruit-quality-detector` إذا لم يكن مفتوحًا بالفعل.

1. يعمل مصنف الصور كواجهة برمجية REST API باستخدام HTTP وليس HTTPS، لذا يجب أن يتم الاتصال باستخدام عميل WiFi يعمل فقط مع مكالمات HTTP. هذا يعني أن الشهادة غير مطلوبة. احذف `CERTIFICATE` من ملف `config.h`.

1. يجب تحديث عنوان URL الخاص بالتنبؤ في ملف `config.h` إلى العنوان الجديد. يمكنك أيضًا حذف `PREDICTION_KEY` لأنه غير مطلوب.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    استبدل `<URL>` بعنوان URL الخاص بالمصنف الخاص بك.

1. في `main.cpp`، قم بتغيير توجيه الاستيراد الخاص بـ WiFi Client Secure لاستيراد النسخة القياسية لـ HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. قم بتغيير تعريف `WiFiClient` ليكون النسخة الخاصة بـ HTTP:

    ```cpp
    WiFiClient client;
    ```

1. حدد السطر الذي يحدد الشهادة على عميل WiFi. احذف السطر `client.setCACert(CERTIFICATE);` من وظيفة `connectWiFi`.

1. في وظيفة `classifyImage`، احذف السطر `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` الذي يحدد مفتاح التنبؤ في الترويسة.

1. قم برفع وتشغيل الكود الخاص بك. وجه الكاميرا نحو بعض الفواكه واضغط على الزر C. سترى الناتج في شاشة المراقبة التسلسلية:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 يمكنك العثور على هذا الكود في المجلد [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 لقد نجح برنامج مصنف جودة الفواكه الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.