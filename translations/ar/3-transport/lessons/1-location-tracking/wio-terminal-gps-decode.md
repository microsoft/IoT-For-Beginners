<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T00:51:50+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "ar"
}
-->
# فك تشفير بيانات GPS - Wio Terminal

في هذا الجزء من الدرس، ستقوم بفك تشفير رسائل NMEA التي يتم قراءتها من مستشعر GPS بواسطة Wio Terminal، واستخراج خطوط الطول والعرض.

## فك تشفير بيانات GPS

بمجرد قراءة بيانات NMEA الخام من المنفذ التسلسلي، يمكن فك تشفيرها باستخدام مكتبة NMEA مفتوحة المصدر.

### المهمة - فك تشفير بيانات GPS

قم ببرمجة الجهاز لفك تشفير بيانات GPS.

1. افتح مشروع تطبيق `gps-sensor` إذا لم يكن مفتوحًا بالفعل.

1. أضف تبعية مكتبة [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) إلى ملف `platformio.ini` الخاص بالمشروع. تحتوي هذه المكتبة على كود لفك تشفير بيانات NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. في ملف `main.cpp`، أضف توجيه تضمين لمكتبة TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. أسفل إعلان `Serial3`، قم بإعلان كائن TinyGPSPlus لمعالجة جمل NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. قم بتغيير محتويات دالة `printGPSData` إلى ما يلي:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    يقوم هذا الكود بقراءة الحرف التالي من منفذ UART التسلسلي إلى وحدة فك تشفير NMEA الخاصة بـ `gps`. بعد كل حرف، سيتحقق مما إذا كانت وحدة فك التشفير قد قرأت جملة صالحة، ثم يتحقق مما إذا كانت قد قرأت موقعًا صالحًا. إذا كان الموقع صالحًا، فسيتم إرساله إلى شاشة المراقبة التسلسلية، مع عدد الأقمار الصناعية التي ساهمت في هذا التحديد.

1. قم ببناء ورفع الكود إلى Wio Terminal.

1. بمجرد رفع الكود، يمكنك مراقبة بيانات موقع GPS باستخدام شاشة المراقبة التسلسلية.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 يمكنك العثور على هذا الكود في المجلد [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 لقد نجحت في برمجة مستشعر GPS مع فك تشفير البيانات!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.