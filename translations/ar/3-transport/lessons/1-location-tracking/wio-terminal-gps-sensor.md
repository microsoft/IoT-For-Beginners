<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T00:42:13+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "ar"
}
-->
# قراءة بيانات GPS - Wio Terminal

في هذا الجزء من الدرس، ستقوم بإضافة مستشعر GPS إلى جهاز Wio Terminal الخاص بك وقراءة القيم منه.

## الأجهزة

يحتاج Wio Terminal إلى مستشعر GPS.

المستشعر الذي ستستخدمه هو [مستشعر Grove GPS Air530](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). يمكن لهذا المستشعر الاتصال بأنظمة GPS متعددة للحصول على إشارة سريعة ودقيقة. يتكون المستشعر من جزأين - الإلكترونيات الأساسية للمستشعر وهوائي خارجي متصل بسلك رفيع لالتقاط موجات الراديو من الأقمار الصناعية.

هذا المستشعر يعمل عبر UART، لذا يقوم بإرسال بيانات GPS عبر UART.

### توصيل مستشعر GPS

يمكن توصيل مستشعر Grove GPS بجهاز Wio Terminal.

#### المهمة - توصيل مستشعر GPS

قم بتوصيل مستشعر GPS.

![مستشعر GPS من نوع Grove](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.ar.png)

1. أدخل أحد طرفي كابل Grove في المقبس الموجود على مستشعر GPS. لن يدخل إلا في اتجاه واحد.

1. مع فصل Wio Terminal عن الكمبيوتر أو أي مصدر طاقة آخر، قم بتوصيل الطرف الآخر من كابل Grove بالمقبس الأيسر لجهاز Wio Terminal عند النظر إلى الشاشة. هذا هو المقبس الأقرب إلى زر الطاقة.

    ![مستشعر GPS متصل بالمقبس الأيسر](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095d5deb3d4e5a1fdd88818d76569b00b1f0d740c92dc986525.ar.png)

1. ضع مستشعر GPS بحيث يكون الهوائي المتصل لديه رؤية واضحة للسماء - من الأفضل أن يكون بجانب نافذة مفتوحة أو في الخارج. من الأسهل الحصول على إشارة واضحة عندما لا يكون هناك عوائق أمام الهوائي.

1. يمكنك الآن توصيل Wio Terminal بجهاز الكمبيوتر الخاص بك.

1. يحتوي مستشعر GPS على مصباحين LED - مصباح أزرق يومض عند إرسال البيانات، ومصباح أخضر يومض كل ثانية عند استقبال البيانات من الأقمار الصناعية. تأكد من أن المصباح الأزرق يومض عند تشغيل Wio Terminal. بعد بضع دقائق، سيبدأ المصباح الأخضر في الوميض - إذا لم يحدث ذلك، قد تحتاج إلى إعادة وضع الهوائي.

## برمجة مستشعر GPS

يمكن الآن برمجة Wio Terminal لاستخدام مستشعر GPS المتصل.

### المهمة - برمجة مستشعر GPS

قم ببرمجة الجهاز.

1. أنشئ مشروعًا جديدًا لجهاز Wio Terminal باستخدام PlatformIO. قم بتسمية هذا المشروع `gps-sensor`. أضف الكود في دالة `setup` لتكوين منفذ الاتصال التسلسلي.

1. أضف التوجيه التالي للإدراج في أعلى ملف `main.cpp`. يتضمن هذا ملف رأس يحتوي على وظائف لتكوين منفذ Grove الأيسر لـ UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. بعد ذلك، أضف السطر التالي من الكود للإعلان عن اتصال منفذ تسلسلي بمنفذ UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. تحتاج إلى إضافة بعض الكود لإعادة توجيه بعض معالجات الإشارات الداخلية إلى هذا المنفذ التسلسلي. أضف الكود التالي أسفل إعلان `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. في دالة `setup`، أسفل المكان الذي يتم فيه تكوين منفذ `Serial`، قم بتكوين منفذ UART التسلسلي باستخدام الكود التالي:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. أسفل هذا الكود في دالة `setup`، أضف الكود التالي لتوصيل دبوس Grove بالمنفذ التسلسلي:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. أضف الدالة التالية قبل دالة `loop` لإرسال بيانات GPS إلى شاشة المراقبة التسلسلية:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. في دالة `loop`، أضف الكود التالي لقراءة البيانات من منفذ UART التسلسلي وطباعة الإخراج إلى شاشة المراقبة التسلسلية:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    يقوم هذا الكود بقراءة البيانات من منفذ UART التسلسلي. تقوم دالة `readStringUntil` بقراءة البيانات حتى تصل إلى حرف محدد، وفي هذه الحالة سطر جديد. سيقوم هذا بقراءة جملة NMEA كاملة (جمل NMEA تنتهي بحرف سطر جديد). طالما يمكن قراءة البيانات من منفذ UART التسلسلي، يتم قراءتها وإرسالها إلى شاشة المراقبة التسلسلية عبر دالة `printGPSData`. بمجرد عدم وجود بيانات إضافية للقراءة، تتأخر دالة `loop` لمدة ثانية واحدة (1,000 مللي ثانية).

1. قم ببناء ورفع الكود إلى جهاز Wio Terminal.

1. بمجرد الرفع، يمكنك مراقبة بيانات GPS باستخدام شاشة المراقبة التسلسلية.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 يمكنك العثور على هذا الكود في المجلد [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 لقد نجحت في برمجة مستشعر GPS!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.