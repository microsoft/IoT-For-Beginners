# اكتشاف القرب - Wio Terminal

في هذا الجزء من الدرس، ستضيف مستشعر قرب إلى Wio Terminal الخاص بك، وتقرأ المسافة منه.

## الأجهزة

يحتاج Wio Terminal إلى مستشعر قرب.

المستشعر الذي ستستخدمه هو [مستشعر المسافة Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). يستخدم هذا المستشعر وحدة قياس بالليزر لاكتشاف المسافة. يتراوح نطاق هذا المستشعر من 10 ملم إلى 2000 ملم (1 سم - 2 متر)، وسيقوم بالإبلاغ عن القيم في هذا النطاق بدقة كبيرة، مع الإبلاغ عن المسافات التي تزيد عن 1000 ملم كـ 8109 ملم.

يقع محدد المدى بالليزر في الجزء الخلفي من المستشعر، وهو الجانب المقابل لمقبس Grove.

هذا مستشعر I2C.

### توصيل مستشعر Time of Flight

يمكن توصيل مستشعر Time of Flight بـ Wio Terminal.

#### المهمة - توصيل مستشعر Time of Flight

قم بتوصيل مستشعر Time of Flight.

![مستشعر Grove Time of Flight](../../../../../translated_images/ar/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. أدخل أحد طرفي كابل Grove في المقبس الموجود على مستشعر Time of Flight. لن يدخل إلا بطريقة واحدة.

1. مع فصل Wio Terminal عن جهاز الكمبيوتر الخاص بك أو أي مصدر طاقة آخر، قم بتوصيل الطرف الآخر من كابل Grove بالمقبس الأيسر على Wio Terminal عند النظر إلى الشاشة. هذا هو المقبس الأقرب إلى زر الطاقة. هذا مقبس مشترك بين الرقمي وI2C.

![مستشعر Grove Time of Flight متصل بالمقبس الأيسر](../../../../../translated_images/ar/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. يمكنك الآن توصيل Wio Terminal بجهاز الكمبيوتر الخاص بك.

## برمجة مستشعر Time of Flight

يمكن الآن برمجة Wio Terminal لاستخدام مستشعر Time of Flight المتصل.

### المهمة - برمجة مستشعر Time of Flight

1. قم بإنشاء مشروع جديد تمامًا لـ Wio Terminal باستخدام PlatformIO. أطلق على هذا المشروع اسم `distance-sensor`. أضف كودًا في دالة `setup` لتكوين منفذ التسلسل.

1. أضف تبعية مكتبة لمكتبة مستشعر المسافة Seeed Grove Time of Flight إلى ملف `platformio.ini` الخاص بالمشروع:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. في `main.cpp`، أضف ما يلي أسفل توجيهات التضمين الحالية لإعلان مثيل من فئة `Seeed_vl53l0x` للتفاعل مع مستشعر Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. أضف ما يلي إلى أسفل دالة `setup` لتهيئة المستشعر:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. في دالة `loop`، قم بقراءة قيمة من المستشعر:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    يقوم هذا الكود بتهيئة بنية بيانات لقراءة البيانات فيها، ثم يمررها إلى طريقة `PerformSingleRangingMeasurement` حيث سيتم تعبئتها بقياس المسافة.

1. أسفل ذلك، قم بكتابة قياس المسافة، ثم قم بتأخير لمدة ثانية واحدة:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. قم ببناء هذا الكود وتحميله وتشغيله. ستتمكن من رؤية قياسات المسافة باستخدام المراقب التسلسلي. ضع أشياء بالقرب من المستشعر وسترى قياس المسافة:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    يقع محدد المدى في الجزء الخلفي من المستشعر، لذا تأكد من استخدام الجانب الصحيح عند قياس المسافة.

    ![محدد المدى في الجزء الخلفي من مستشعر Time of Flight يشير إلى موزة](../../../../../translated_images/ar/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 يمكنك العثور على هذا الكود في مجلد [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 لقد نجح برنامج مستشعر القرب الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالترجمة البشرية الاحترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.