<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-26T22:17:31+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "ar"
}
-->
# قياس درجة الحرارة - Wio Terminal

في هذا الجزء من الدرس، ستقوم بإضافة مستشعر درجة حرارة إلى جهاز Wio Terminal الخاص بك، وقراءة قيم درجة الحرارة منه.

## الأجهزة

يحتاج Wio Terminal إلى مستشعر درجة حرارة.

المستشعر الذي ستستخدمه هو [مستشعر الرطوبة ودرجة الحرارة DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)، الذي يجمع بين مستشعرين في حزمة واحدة. هذا المستشعر شائع جدًا، حيث تتوفر العديد من المستشعرات التجارية التي تجمع بين قياس درجة الحرارة والرطوبة وأحيانًا الضغط الجوي. مكون مستشعر درجة الحرارة هو مقاوم حراري ذو معامل حراري سلبي (NTC)، وهو مقاوم تقل مقاومته مع زيادة درجة الحرارة.

هذا مستشعر رقمي، لذا يحتوي على محول تناظري إلى رقمي (ADC) مدمج لإنشاء إشارة رقمية تحتوي على بيانات درجة الحرارة والرطوبة التي يمكن لوحدة التحكم الدقيقة قراءتها.

### توصيل مستشعر درجة الحرارة

يمكن توصيل مستشعر درجة الحرارة Grove بمنفذ رقمي في Wio Terminal.

#### المهمة - توصيل مستشعر درجة الحرارة

قم بتوصيل مستشعر درجة الحرارة.

![مستشعر درجة الحرارة Grove](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.ar.png)

1. أدخل أحد طرفي كابل Grove في المقبس الموجود على مستشعر الرطوبة ودرجة الحرارة. لن يدخل إلا في اتجاه واحد.

1. مع فصل Wio Terminal عن جهاز الكمبيوتر أو أي مصدر طاقة آخر، قم بتوصيل الطرف الآخر من كابل Grove بالمقبس الموجود على الجانب الأيمن من Wio Terminal أثناء النظر إلى الشاشة. هذا هو المقبس الأبعد عن زر الطاقة.

![مستشعر درجة الحرارة Grove متصل بالمقبس الأيمن](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a68d24879d2c8986c78244696f931e2e33c293f426ecdc0ad.ar.png)

## برمجة مستشعر درجة الحرارة

يمكن الآن برمجة Wio Terminal لاستخدام مستشعر درجة الحرارة المتصل.

### المهمة - برمجة مستشعر درجة الحرارة

قم ببرمجة الجهاز.

1. أنشئ مشروعًا جديدًا تمامًا لـ Wio Terminal باستخدام PlatformIO. سمِّ هذا المشروع `temperature-sensor`. أضف الكود في دالة `setup` لتكوين منفذ الاتصال التسلسلي.

    > ⚠️ يمكنك الرجوع إلى [التعليمات لإنشاء مشروع PlatformIO في المشروع 1، الدرس 1 إذا لزم الأمر](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. أضف تبعية مكتبة مستشعر الرطوبة ودرجة الحرارة Seeed Grove إلى ملف `platformio.ini` الخاص بالمشروع:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ يمكنك الرجوع إلى [التعليمات لإضافة مكتبات إلى مشروع PlatformIO في المشروع 1، الدرس 4 إذا لزم الأمر](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. أضف توجيهات `#include` التالية إلى أعلى الملف، تحت `#include <Arduino.h>` الموجودة:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    هذا يستورد الملفات اللازمة للتفاعل مع المستشعر. يحتوي ملف الرأس `DHT.h` على الكود الخاص بالمستشعر نفسه، وإضافة ملف الرأس `SPI.h` يضمن ربط الكود اللازم للتواصل مع المستشعر عند تجميع التطبيق.

1. قبل دالة `setup`، قم بتعريف مستشعر DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    هذا يعرّف مثيلًا من فئة `DHT` التي تدير مستشعر **D**igital **H**umidity و**T**emperature. هذا المستشعر متصل بالمنفذ `D0`، وهو المقبس الموجود على الجانب الأيمن من Wio Terminal. المعامل الثاني يخبر الكود بأن المستشعر المستخدم هو مستشعر *DHT11* - المكتبة التي تستخدمها تدعم أنواعًا أخرى من هذا المستشعر.

1. في دالة `setup`، أضف الكود لإعداد الاتصال التسلسلي:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. في نهاية دالة `setup`، بعد آخر `delay`، أضف استدعاءً لبدء تشغيل مستشعر DHT:

    ```cpp
    dht.begin();
    ```

1. في دالة `loop`، أضف الكود لاستدعاء المستشعر وطباعة درجة الحرارة إلى المنفذ التسلسلي:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    يقوم هذا الكود بتعريف مصفوفة فارغة تحتوي على عددين عشريين، ويمررها إلى استدعاء `readTempAndHumidity` على مثيل `DHT`. يقوم هذا الاستدعاء بملء المصفوفة بقيمتين - يتم وضع الرطوبة في العنصر 0 من المصفوفة (تذكر أن المصفوفات في C++ تبدأ من 0، لذا فإن العنصر 0 هو "الأول" في المصفوفة)، وتوضع درجة الحرارة في العنصر 1.

    يتم قراءة درجة الحرارة من العنصر 1 في المصفوفة، وطبعها إلى المنفذ التسلسلي.

    > 🇺🇸 يتم قراءة درجة الحرارة بوحدة السيلسيوس. للأمريكيين، لتحويلها إلى فهرنهايت، قسّم القيمة المقروءة بالسيلسيوس على 5، ثم اضربها في 9، ثم أضف 32. على سبيل المثال، قراءة درجة حرارة 20°C تصبح ((20/5)*9) + 32 = 68°F.

1. قم ببناء ورفع الكود إلى Wio Terminal.

    > ⚠️ يمكنك الرجوع إلى [التعليمات لإنشاء مشروع PlatformIO في المشروع 1، الدرس 1 إذا لزم الأمر](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. بمجرد الرفع، يمكنك مراقبة درجة الحرارة باستخدام المراقب التسلسلي:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 يمكنك العثور على هذا الكود في المجلد [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 لقد نجحت في برمجة مستشعر درجة الحرارة!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.