<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T00:49:45+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "ar"
}
-->
# فك بيانات GPS - الأجهزة الافتراضية لإنترنت الأشياء و Raspberry Pi

في هذا الجزء من الدرس، ستقوم بفك رسائل NMEA التي يتم قراءتها من مستشعر GPS بواسطة Raspberry Pi أو جهاز إنترنت الأشياء الافتراضي، واستخراج خط العرض وخط الطول.

## فك بيانات GPS

بمجرد قراءة بيانات NMEA الخام من المنفذ التسلسلي، يمكن فكها باستخدام مكتبة NMEA مفتوحة المصدر.

### المهمة - فك بيانات GPS

قم ببرمجة الجهاز لفك بيانات GPS.

1. افتح مشروع تطبيق `gps-sensor` إذا لم يكن مفتوحًا بالفعل.

1. قم بتثبيت حزمة Pip المسماة `pynmea2`. تحتوي هذه الحزمة على كود لفك رسائل NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. أضف الكود التالي إلى الواردات في ملف `app.py` لاستيراد وحدة `pynmea2`:

    ```python
    import pynmea2
    ```

1. استبدل محتويات وظيفة `print_gps_data` بالكود التالي:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    سيستخدم هذا الكود مكتبة `pynmea2` لتحليل السطر الذي يتم قراءته من منفذ UART التسلسلي.

    إذا كان نوع الجملة في الرسالة هو `GGA`، فهذا يعني أنها رسالة تثبيت الموقع، ويتم معالجتها. يتم قراءة قيم خط العرض وخط الطول من الرسالة وتحويلها إلى درجات عشرية من تنسيق NMEA `(d)ddmm.mmmm`. تقوم وظيفة `dm_to_sd` بهذا التحويل.

    يتم بعد ذلك التحقق من اتجاه خط العرض، وإذا كان خط العرض جنوبًا، يتم تحويل القيمة إلى رقم سالب. نفس الشيء مع خط الطول، إذا كان غربًا يتم تحويله إلى رقم سالب.

    أخيرًا، يتم طباعة الإحداثيات على وحدة التحكم، إلى جانب عدد الأقمار الصناعية المستخدمة لتحديد الموقع.

1. قم بتشغيل الكود. إذا كنت تستخدم جهاز إنترنت الأشياء الافتراضي، فتأكد من تشغيل تطبيق CounterFit وإرسال بيانات GPS.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 يمكنك العثور على هذا الكود في مجلد [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device)، أو في مجلد [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 لقد نجحت في برمجة مستشعر GPS مع فك البيانات!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.