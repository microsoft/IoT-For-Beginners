<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-26T23:20:57+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "ar"
}
-->
# التحكم في ضوء الليل عبر الإنترنت - Wio Terminal

في هذا الجزء من الدرس، ستقوم بالاشتراك في الأوامر المرسلة من وسيط MQTT إلى جهاز Wio Terminal الخاص بك.

## الاشتراك في الأوامر

الخطوة التالية هي الاشتراك في الأوامر المرسلة من وسيط MQTT، والاستجابة لها.

### المهمة

الاشتراك في الأوامر.

1. افتح مشروع ضوء الليل في VS Code.

1. أضف الكود التالي إلى أسفل ملف `config.h` لتعريف اسم الموضوع الخاص بالأوامر:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` هو الموضوع الذي سيشترك فيه الجهاز لتلقي أوامر تشغيل وإطفاء الـ LED.

1. أضف السطر التالي إلى نهاية دالة `reconnectMQTTClient` للاشتراك في موضوع الأوامر عند إعادة الاتصال بعميل MQTT:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. أضف الكود التالي أسفل دالة `reconnectMQTTClient`.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    هذه الدالة ستكون رد النداء (callback) الذي سيستدعيه عميل MQTT عند استلام رسالة من الخادم.

    يتم استلام الرسالة كمصفوفة من أعداد صحيحة غير موقعة مكونة من 8 بت، لذا يجب تحويلها إلى مصفوفة أحرف ليتم التعامل معها كنص.

    تحتوي الرسالة على مستند JSON، ويتم فك تشفيره باستخدام مكتبة ArduinoJson. يتم قراءة خاصية `led_on` من مستند JSON، وبناءً على قيمتها يتم تشغيل أو إطفاء الـ LED.

1. أضف الكود التالي إلى دالة `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    هذا الكود يحدد `clientCallback` كدالة رد النداء التي سيتم استدعاؤها عند استلام رسالة من وسيط MQTT.

    > 💁 يتم استدعاء معالج `clientCallback` لجميع المواضيع التي تم الاشتراك فيها. إذا قمت لاحقًا بكتابة كود يستمع إلى مواضيع متعددة، يمكنك الحصول على الموضوع الذي أُرسلت الرسالة إليه من خلال معامل `topic` الذي يتم تمريره إلى دالة رد النداء.

1. قم برفع الكود إلى جهاز Wio Terminal الخاص بك، واستخدم Serial Monitor لرؤية مستويات الضوء التي يتم إرسالها إلى وسيط MQTT.

1. قم بضبط مستويات الضوء التي يتم اكتشافها بواسطة جهازك الفعلي أو الافتراضي. سترى الرسائل التي يتم استلامها والأوامر التي يتم إرسالها في الطرفية. ستلاحظ أيضًا تشغيل وإطفاء الـ LED بناءً على مستوى الضوء.

> 💁 يمكنك العثور على هذا الكود في مجلد [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 لقد قمت ببرمجة جهازك بنجاح للاستجابة للأوامر المرسلة من وسيط MQTT.

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.