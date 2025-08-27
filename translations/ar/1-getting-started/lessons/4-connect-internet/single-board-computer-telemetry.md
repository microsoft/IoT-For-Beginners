<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-26T23:10:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "ar"
}
-->
# التحكم في ضوء الليل عبر الإنترنت - الأجهزة الافتراضية لإنترنت الأشياء و Raspberry Pi

في هذا الجزء من الدرس، ستقوم بإرسال بيانات التتبع (telemetry) الخاصة بمستويات الإضاءة من جهاز Raspberry Pi أو جهاز إنترنت الأشياء الافتراضي إلى وسيط MQTT.

## نشر بيانات التتبع

الخطوة التالية هي إنشاء مستند JSON يحتوي على بيانات التتبع وإرساله إلى وسيط MQTT.

### المهمة

نشر بيانات التتبع إلى وسيط MQTT.

1. افتح مشروع ضوء الليل في VS Code.

1. إذا كنت تستخدم جهاز إنترنت أشياء افتراضي، تأكد من أن الطرفية تعمل ضمن البيئة الافتراضية. إذا كنت تستخدم Raspberry Pi، فلن تحتاج إلى استخدام بيئة افتراضية.

1. أضف الاستيراد التالي إلى أعلى ملف `app.py`:

    ```python
    import json
    ```

    تُستخدم مكتبة `json` لترميز بيانات التتبع كمستند JSON.

1. أضف السطر التالي بعد تعريف `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` هو الموضوع (topic) الخاص بـ MQTT الذي سيقوم الجهاز بنشر مستويات الإضاءة إليه.

1. استبدل محتويات حلقة `while True:` الموجودة في نهاية الملف بما يلي:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    يقوم هذا الكود بتعبئة مستوى الإضاءة في مستند JSON ونشره إلى وسيط MQTT. ثم ينتظر لفترة لتقليل تكرار إرسال الرسائل.

1. قم بتشغيل الكود بنفس الطريقة التي شغّلت بها الكود في الجزء السابق من المهمة. إذا كنت تستخدم جهاز إنترنت أشياء افتراضي، فتأكد من أن تطبيق CounterFit يعمل وأن مستشعر الضوء وLED قد تم إنشاؤهما على الدبابيس الصحيحة.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 يمكنك العثور على هذا الكود في المجلد [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) أو المجلد [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 لقد قمت بنجاح بإرسال بيانات التتبع من جهازك.

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.