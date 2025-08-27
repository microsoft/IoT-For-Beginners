<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-26T22:18:39+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "ar"
}
-->
# نشر درجة الحرارة - Wio Terminal

في هذا الجزء من الدرس، ستقوم بنشر قيم درجة الحرارة التي يتم اكتشافها بواسطة Wio Terminal عبر MQTT حتى يمكن استخدامها لاحقًا لحساب GDD.

## نشر درجة الحرارة

بمجرد قراءة درجة الحرارة، يمكن نشرها عبر MQTT إلى كود "الخادم" الذي سيقوم بقراءة القيم وتخزينها لتكون جاهزة للاستخدام في حساب GDD. وحدات التحكم الدقيقة لا تقرأ الوقت من الإنترنت ولا تتعقب الوقت باستخدام ساعة الوقت الحقيقي بشكل افتراضي، لذلك يجب برمجة الجهاز للقيام بذلك، بافتراض أنه يحتوي على الأجهزة اللازمة.

لتبسيط الأمور في هذا الدرس، لن يتم إرسال الوقت مع بيانات المستشعر، بل يمكن إضافته بواسطة كود الخادم لاحقًا عند استلام الرسائل.

### المهمة

برمج الجهاز لنشر بيانات درجة الحرارة.

1. افتح مشروع `temperature-sensor` الخاص بـ Wio Terminal.

1. كرر الخطوات التي قمت بها في الدرس الرابع للاتصال بـ MQTT وإرسال البيانات، ستستخدم نفس وسيط Mosquitto العام.

    الخطوات لهذا هي:

    - أضف مكتبات Seeed WiFi و MQTT إلى ملف `.ini`
    - أضف ملف الإعدادات والكود للاتصال بشبكة WiFi
    - أضف الكود للاتصال بوسيط MQTT
    - أضف الكود لنشر البيانات

    > ⚠️ ارجع إلى [تعليمات الاتصال بـ MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) و[تعليمات إرسال البيانات](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) من الدرس الرابع إذا لزم الأمر.

1. تأكد من أن `CLIENT_NAME` في ملف الرأس `config.h` يعكس هذا المشروع:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. بالنسبة للبيانات، بدلاً من إرسال قيمة الضوء، أرسل قيمة درجة الحرارة التي تم قراءتها من مستشعر DHT في خاصية داخل مستند JSON تسمى `temperature` عن طريق تغيير وظيفة `loop` في `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. لا تحتاج قيمة درجة الحرارة إلى القراءة بشكل متكرر - لن تتغير كثيرًا في فترة زمنية قصيرة، لذا قم بتعيين `delay` في وظيفة `loop` إلى 10 دقائق:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 وظيفة `delay` تأخذ الوقت بالمللي ثانية، لذا لجعل الأمر أسهل للقراءة يتم تمرير القيمة كنتيجة لعملية حسابية. 1,000 مللي ثانية في الثانية، 60 ثانية في الدقيقة، لذا 10 × (60 ثانية في الدقيقة) × (1000 مللي ثانية في الثانية) يعطي تأخيرًا لمدة 10 دقائق.

1. قم برفع الكود إلى Wio Terminal الخاص بك، واستخدم شاشة المراقبة التسلسلية لرؤية درجة الحرارة التي يتم إرسالها إلى وسيط MQTT.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 يمكنك العثور على هذا الكود في مجلد [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 لقد نجحت في نشر درجة الحرارة كبيانات من جهازك.

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.