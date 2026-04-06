# اكتشاف القرب - Raspberry Pi

في هذا الجزء من الدرس، ستضيف مستشعر قرب إلى Raspberry Pi وتقرأ المسافة منه.

## الأجهزة

يحتاج Raspberry Pi إلى مستشعر قرب.

المستشعر الذي ستستخدمه هو [مستشعر المسافة Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). يستخدم هذا المستشعر وحدة قياس بالليزر لاكتشاف المسافة. نطاق هذا المستشعر يتراوح بين 10 ملم إلى 2000 ملم (1 سم - 2 متر)، وسيقوم بالإبلاغ عن القيم في هذا النطاق بدقة كبيرة، مع الإبلاغ عن المسافات التي تزيد عن 1000 ملم كـ 8109 ملم.

محدد المدى بالليزر موجود في الجزء الخلفي من المستشعر، على الجانب المقابل لمقبس Grove.

هذا مستشعر I²C.

### توصيل مستشعر Time of Flight

يمكن توصيل مستشعر Time of Flight بـ Raspberry Pi.

#### المهمة - توصيل مستشعر Time of Flight

قم بتوصيل مستشعر Time of Flight.

![مستشعر Time of Flight من نوع Grove](../../../../../translated_images/ar/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. أدخل أحد طرفي كابل Grove في المقبس الموجود على مستشعر Time of Flight. لن يدخل إلا بطريقة واحدة.

1. مع إيقاف تشغيل Raspberry Pi، قم بتوصيل الطرف الآخر من كابل Grove بأحد مقابس I²C المميزة بـ **I²C** على قبعة Grove Base المثبتة على Pi. هذه المقابس موجودة في الصف السفلي، على الطرف المقابل لدبابيس GPI وبجوار فتحة كابل الكاميرا.

![مستشعر Time of Flight من نوع Grove متصل بمقبس I²C](../../../../../translated_images/ar/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## برمجة مستشعر Time of Flight

يمكن الآن برمجة Raspberry Pi لاستخدام مستشعر Time of Flight المتصل.

### المهمة - برمجة مستشعر Time of Flight

قم ببرمجة الجهاز.

1. قم بتشغيل Pi وانتظر حتى يتم الإقلاع.

1. افتح كود `fruit-quality-detector` في VS Code، إما مباشرة على Pi، أو قم بالاتصال عبر امتداد Remote SSH.

1. قم بتثبيت حزمة rpi-vl53l0x باستخدام Pip، وهي حزمة Python تتفاعل مع مستشعر المسافة VL53L0X. قم بتثبيتها باستخدام أمر pip التالي:

    ```sh
    pip install rpi-vl53l0x
    ```

1. أنشئ ملفًا جديدًا في هذا المشروع يسمى `distance-sensor.py`.

    > 💁 طريقة سهلة لمحاكاة أجهزة IoT متعددة هي القيام بكل جهاز في ملف Python مختلف، ثم تشغيلها في نفس الوقت.

1. أضف الكود التالي إلى هذا الملف:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    هذا يستورد مكتبة Grove I²C bus، ومكتبة مستشعر للأجهزة الأساسية المدمجة في مستشعر Time of Flight من نوع Grove.

1. أسفل هذا، أضف الكود التالي للوصول إلى المستشعر:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    هذا الكود يعلن عن مستشعر مسافة باستخدام Grove I²C bus، ثم يبدأ تشغيل المستشعر.

1. أخيرًا، أضف حلقة لا نهائية لقراءة المسافات:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    هذا الكود ينتظر قيمة جاهزة للقراءة من المستشعر، ثم يطبعها إلى وحدة التحكم.

1. قم بتشغيل هذا الكود.

    > 💁 لا تنسَ أن هذا الملف يسمى `distance-sensor.py`! تأكد من تشغيله عبر Python، وليس `app.py`.

1. سترى قياسات المسافة تظهر في وحدة التحكم. ضع الأشياء بالقرب من المستشعر وسترى قياس المسافة:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    محدد المدى موجود في الجزء الخلفي من المستشعر، لذا تأكد من استخدام الجانب الصحيح عند قياس المسافة.

    ![محدد المدى في الجزء الخلفي من مستشعر Time of Flight يشير إلى موزة](../../../../../translated_images/ar/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 يمكنك العثور على هذا الكود في مجلد [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 لقد نجحت في برمجة مستشعر القرب!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.