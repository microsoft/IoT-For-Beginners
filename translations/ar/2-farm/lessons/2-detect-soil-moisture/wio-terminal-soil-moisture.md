# قياس رطوبة التربة - Wio Terminal

في هذا الجزء من الدرس، ستقوم بإضافة مستشعر رطوبة التربة السعوي إلى Wio Terminal الخاص بك، وقراءة القيم منه.

## الأجهزة

يحتاج Wio Terminal إلى مستشعر رطوبة التربة السعوي.

المستشعر الذي ستستخدمه هو [مستشعر رطوبة التربة السعوي](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)، الذي يقيس رطوبة التربة عن طريق الكشف عن السعة الكهربائية للتربة، وهي خاصية تتغير مع تغير رطوبة التربة. مع زيادة رطوبة التربة، ينخفض الجهد الكهربائي.

هذا مستشعر تناظري، لذا يتم توصيله بدبابيس التناظرية على Wio Terminal، باستخدام محول ADC مدمج لإنشاء قيمة تتراوح بين 0-1023.

### توصيل مستشعر رطوبة التربة

يمكن توصيل مستشعر رطوبة التربة Grove بمنفذ التناظري/الرقمي القابل للتكوين في Wio Terminal.

#### المهمة - توصيل مستشعر رطوبة التربة

قم بتوصيل مستشعر رطوبة التربة.

![مستشعر رطوبة التربة Grove](../../../../../translated_images/ar/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. أدخل أحد طرفي كابل Grove في المقبس الموجود على مستشعر رطوبة التربة. يمكن إدخاله في اتجاه واحد فقط.

1. مع فصل Wio Terminal عن الكمبيوتر أو مصدر الطاقة الآخر، قم بتوصيل الطرف الآخر من كابل Grove بالمقبس الموجود على الجانب الأيمن من Wio Terminal كما يظهر على الشاشة. هذا هو المقبس الأبعد عن زر الطاقة.

![مستشعر رطوبة التربة Grove متصل بالمقبس الأيمن](../../../../../translated_images/ar/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. أدخل مستشعر رطوبة التربة في التربة. يحتوي على "خط أعلى موضع" - خط أبيض عبر المستشعر. أدخل المستشعر حتى هذا الخط ولكن لا تتجاوزه.

![مستشعر رطوبة التربة Grove في التربة](../../../../../translated_images/ar/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. يمكنك الآن توصيل Wio Terminal بجهاز الكمبيوتر الخاص بك.

## برمجة مستشعر رطوبة التربة

يمكن الآن برمجة Wio Terminal لاستخدام مستشعر رطوبة التربة المرفق.

### المهمة - برمجة مستشعر رطوبة التربة

قم ببرمجة الجهاز.

1. قم بإنشاء مشروع جديد لـ Wio Terminal باستخدام PlatformIO. قم بتسمية هذا المشروع `soil-moisture-sensor`. أضف الكود في وظيفة `setup` لتكوين منفذ التسلسل.

    > ⚠️ يمكنك الرجوع إلى [التعليمات لإنشاء مشروع PlatformIO في المشروع 1، الدرس 1 إذا لزم الأمر](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. لا توجد مكتبة لهذا المستشعر، بدلاً من ذلك يمكنك القراءة من الدبوس التناظري باستخدام وظيفة Arduino المدمجة [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). ابدأ بتكوين الدبوس التناظري للإدخال حتى يمكن قراءة القيم منه عن طريق إضافة التالي إلى وظيفة `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    هذا يحدد دبوس `A0`، الدبوس التناظري/الرقمي المدمج، كدبوس إدخال يمكن قراءة الجهد الكهربائي منه.

1. أضف التالي إلى وظيفة `loop` لقراءة الجهد الكهربائي من هذا الدبوس:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. أسفل هذا الكود، أضف الكود التالي لطباعة القيمة إلى منفذ التسلسل:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. أخيرًا أضف تأخيرًا لمدة 10 ثوانٍ في النهاية:

    ```cpp
    delay(10000);
    ```

1. قم ببناء ورفع الكود إلى Wio Terminal.

    > ⚠️ يمكنك الرجوع إلى [التعليمات لإنشاء مشروع PlatformIO في المشروع 1، الدرس 1 إذا لزم الأمر](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. بمجرد رفع الكود، يمكنك مراقبة رطوبة التربة باستخدام شاشة التسلسل. أضف بعض الماء إلى التربة، أو قم بإزالة المستشعر من التربة، وشاهد تغير القيمة.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    في المثال أعلاه، يمكنك رؤية انخفاض الجهد الكهربائي عند إضافة الماء.

> 💁 يمكنك العثور على هذا الكود في مجلد [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 لقد نجحت في برمجة مستشعر رطوبة التربة!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.