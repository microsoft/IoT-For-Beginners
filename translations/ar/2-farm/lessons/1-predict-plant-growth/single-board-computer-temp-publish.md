<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-26T22:16:00+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "ar"
}
-->
# نشر درجة الحرارة - الأجهزة الافتراضية لإنترنت الأشياء و Raspberry Pi

في هذا الجزء من الدرس، ستقوم بنشر قيم درجة الحرارة التي يكتشفها Raspberry Pi أو جهاز إنترنت الأشياء الافتراضي عبر MQTT حتى يمكن استخدامها لاحقًا لحساب GDD.

## نشر درجة الحرارة

بمجرد قراءة درجة الحرارة، يمكن نشرها عبر MQTT إلى كود "الخادم" الذي سيقرأ القيم ويخزنها لتكون جاهزة للاستخدام في حساب GDD.

### المهمة - نشر درجة الحرارة

برمج الجهاز لنشر بيانات درجة الحرارة.

1. افتح مشروع تطبيق `temperature-sensor` إذا لم يكن مفتوحًا بالفعل.

1. كرر الخطوات التي قمت بها في الدرس الرابع للاتصال بـ MQTT وإرسال البيانات، ستستخدم نفس وسيط Mosquitto العام.

    الخطوات هي:

    - إضافة حزمة pip الخاصة بـ MQTT
    - إضافة الكود للاتصال بوسيط MQTT
    - إضافة الكود لنشر البيانات

    > ⚠️ ارجع إلى [تعليمات الاتصال بـ MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) و[تعليمات إرسال البيانات](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) من الدرس الرابع إذا لزم الأمر.

1. تأكد من أن `client_name` يعكس اسم هذا المشروع:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. بالنسبة للبيانات، بدلاً من إرسال قيمة الضوء، أرسل قيمة درجة الحرارة التي تم قراءتها من مستشعر DHT في خاصية داخل مستند JSON تسمى `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. لا تحتاج قيمة درجة الحرارة إلى القراءة بشكل متكرر - لن تتغير كثيرًا في فترة زمنية قصيرة، لذا قم بتعيين `time.sleep` إلى 10 دقائق:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 تأخذ وظيفة `sleep` الوقت بالثواني، لذا لجعلها أسهل للقراءة يتم تمرير القيمة كنتيجة لعملية حسابية. 60 ثانية في الدقيقة، لذا 10 × (60 ثانية في الدقيقة) تعطي تأخيرًا لمدة 10 دقائق.

1. قم بتشغيل الكود بنفس الطريقة التي قمت بها في الجزء السابق من المهمة. إذا كنت تستخدم جهاز إنترنت أشياء افتراضي، فتأكد من تشغيل تطبيق CounterFit وإنشاء مستشعرات الرطوبة ودرجة الحرارة على المنافذ الصحيحة.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 يمكنك العثور على هذا الكود في مجلد [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) أو مجلد [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 لقد قمت بنجاح بنشر درجة الحرارة كبيانات من جهازك.

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو عدم دقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.