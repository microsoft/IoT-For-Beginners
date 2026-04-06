# اكتشاف القرب - الأجهزة الافتراضية لإنترنت الأشياء

في هذا الجزء من الدرس، ستضيف مستشعر قرب إلى جهاز إنترنت الأشياء الافتراضي الخاص بك، وتقرأ المسافة منه.

## الأجهزة

سيستخدم جهاز إنترنت الأشياء الافتراضي مستشعر مسافة محاكي.

في جهاز إنترنت الأشياء الفعلي، ستستخدم مستشعرًا مع وحدة قياس بالليزر لاكتشاف المسافة.

### إضافة مستشعر المسافة إلى CounterFit

لاستخدام مستشعر مسافة افتراضي، تحتاج إلى إضافته إلى تطبيق CounterFit.

#### المهمة - إضافة مستشعر المسافة إلى CounterFit

أضف مستشعر المسافة إلى تطبيق CounterFit.

1. افتح الكود `fruit-quality-detector` في VS Code، وتأكد من تفعيل البيئة الافتراضية.

1. قم بتثبيت حزمة Pip إضافية لتثبيت CounterFit shim الذي يمكنه التحدث إلى مستشعرات المسافة عن طريق محاكاة [حزمة rpi-vl53l0x Pip](https://pypi.org/project/rpi-vl53l0x/)، وهي حزمة Python تتفاعل مع [مستشعر مسافة وقت الطيران VL53L0X](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). تأكد من تثبيت هذه الحزمة من خلال نافذة طرفية مع تفعيل البيئة الافتراضية.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. تأكد من تشغيل تطبيق الويب CounterFit.

1. قم بإنشاء مستشعر مسافة:

    1. في مربع *Create sensor* في لوحة *Sensors*، انقر على القائمة المنسدلة *Sensor type* واختر *Distance*.

    1. اترك *Units* كما هي `Millimeter`.

    1. هذا المستشعر هو مستشعر I2C، لذا قم بتعيين العنوان إلى `0x29`. إذا كنت تستخدم مستشعر VL53L0X فعلي، فسيكون هذا العنوان مبرمجًا بشكل ثابت.

    1. اختر زر **Add** لإنشاء مستشعر المسافة.

    ![إعدادات مستشعر المسافة](../../../../../translated_images/ar/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    سيتم إنشاء مستشعر المسافة وسيظهر في قائمة المستشعرات.

    ![تم إنشاء مستشعر المسافة](../../../../../translated_images/ar/counterfit-distance-sensor.079eefeeea0b68af.webp)

## برمجة مستشعر المسافة

يمكن الآن برمجة جهاز إنترنت الأشياء الافتراضي لاستخدام مستشعر المسافة المحاكي.

### المهمة - برمجة مستشعر وقت الطيران

1. قم بإنشاء ملف جديد في مشروع `fruit-quality-detector` باسم `distance-sensor.py`.

    > 💁 طريقة سهلة لمحاكاة أجهزة إنترنت الأشياء المتعددة هي القيام بكل جهاز في ملف Python مختلف، ثم تشغيلها في نفس الوقت.

1. ابدأ اتصالًا مع CounterFit باستخدام الكود التالي:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. أضف الكود التالي أسفل هذا:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    هذا يستورد مكتبة المستشعر shim لمستشعر وقت الطيران VL53L0X.

1. أسفل هذا، أضف الكود التالي للوصول إلى المستشعر:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    هذا الكود يعلن عن مستشعر المسافة، ثم يبدأ تشغيل المستشعر.

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

1. سترى قياسات المسافة تظهر في وحدة التحكم. قم بتغيير القيمة في CounterFit لترى هذه القيمة تتغير، أو استخدم قيمًا عشوائية.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 يمكنك العثور على هذا الكود في المجلد [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 لقد نجحت في برمجة مستشعر القرب!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.