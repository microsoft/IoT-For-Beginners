<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-26T21:34:41+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "ar"
}
-->
# عد المخزون باستخدام جهاز إنترنت الأشياء - الأجهزة الافتراضية وإنترنت الأشياء وRaspberry Pi

يمكن استخدام مزيج من التوقعات وإطاراتها المحيطة لعد المخزون في صورة.

## عرض الإطارات المحيطة

كخطوة تصحيح مفيدة، يمكنك ليس فقط طباعة الإطارات المحيطة، ولكن أيضًا رسمها على الصورة التي تم حفظها على القرص عند التقاط صورة.

### المهمة - طباعة الإطارات المحيطة

1. تأكد من أن مشروع `stock-counter` مفتوح في VS Code، وأن البيئة الافتراضية مفعلة إذا كنت تستخدم جهاز إنترنت أشياء افتراضي.

1. قم بتغيير عبارة `print` في حلقة `for` إلى ما يلي لطباعة الإطارات المحيطة إلى وحدة التحكم:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. قم بتشغيل التطبيق مع توجيه الكاميرا نحو بعض المخزون على رف. سيتم طباعة الإطارات المحيطة إلى وحدة التحكم، مع قيم اليسار، الأعلى، العرض والارتفاع من 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### المهمة - رسم الإطارات المحيطة على الصورة

1. يمكن استخدام حزمة Pip [Pillow](https://pypi.org/project/Pillow/) للرسم على الصور. قم بتثبيتها باستخدام الأمر التالي:

    ```sh
    pip3 install pillow
    ```

    إذا كنت تستخدم جهاز إنترنت أشياء افتراضي، تأكد من تشغيل هذا الأمر داخل البيئة الافتراضية المفعلة.

1. أضف عبارة الاستيراد التالية إلى أعلى ملف `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    هذا يستورد الكود اللازم لتحرير الصورة.

1. أضف الكود التالي إلى نهاية ملف `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    يفتح هذا الكود الصورة التي تم حفظها سابقًا لتحريرها. ثم يقوم بالتكرار عبر التوقعات للحصول على الإطارات المحيطة، ويحسب الإحداثيات السفلية اليمنى باستخدام قيم الإطار المحيط من 0-1. يتم تحويل هذه القيم إلى إحداثيات الصورة بضربها في البعد المناسب للصورة. على سبيل المثال، إذا كانت قيمة اليسار 0.5 في صورة عرضها 600 بكسل، فسيتم تحويلها إلى 300 (0.5 × 600 = 300).

    يتم رسم كل إطار محيط على الصورة باستخدام خط أحمر. وأخيرًا، يتم حفظ الصورة المعدلة، مما يؤدي إلى الكتابة فوق الصورة الأصلية.

1. قم بتشغيل التطبيق مع توجيه الكاميرا نحو بعض المخزون على رف. سترى ملف `image.jpg` في مستكشف VS Code، وستتمكن من تحديده لرؤية الإطارات المحيطة.

    ![4 علب من معجون الطماطم مع إطارات محيطة حول كل علبة](../../../../../translated_images/ar/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## عد المخزون

في الصورة الموضحة أعلاه، هناك تداخل بسيط بين الإطارات المحيطة. إذا كان هذا التداخل أكبر بكثير، فقد تشير الإطارات المحيطة إلى نفس الكائن. لعد الكائنات بشكل صحيح، تحتاج إلى تجاهل الإطارات ذات التداخل الكبير.

### المهمة - عد المخزون مع تجاهل التداخل

1. يمكن استخدام حزمة Pip [Shapely](https://pypi.org/project/Shapely/) لحساب التقاطع. إذا كنت تستخدم Raspberry Pi، ستحتاج إلى تثبيت مكتبة تابعة أولاً:

    ```sh
    sudo apt install libgeos-dev
    ```

1. قم بتثبيت حزمة Shapely باستخدام Pip:

    ```sh
    pip3 install shapely
    ```

    إذا كنت تستخدم جهاز إنترنت أشياء افتراضي، تأكد من تشغيل هذا الأمر داخل البيئة الافتراضية المفعلة.

1. أضف عبارة الاستيراد التالية إلى أعلى ملف `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    هذا يستورد الكود اللازم لإنشاء مضلعات لحساب التداخل.

1. فوق الكود الذي يرسم الإطارات المحيطة، أضف الكود التالي:

    ```python
    overlap_threshold = 0.20
    ```

    هذا يحدد نسبة التداخل المسموح بها قبل اعتبار الإطارات المحيطة لنفس الكائن. القيمة 0.20 تعني تداخل بنسبة 20%.

1. لحساب التداخل باستخدام Shapely، يجب تحويل الإطارات المحيطة إلى مضلعات Shapely. أضف الوظيفة التالية للقيام بذلك:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    تقوم هذه الوظيفة بإنشاء مضلع باستخدام الإطار المحيط لتوقع معين.

1. تتضمن منطق إزالة الكائنات المتداخلة مقارنة جميع الإطارات المحيطة، وإذا كان أي زوج من التوقعات يحتوي على إطارات محيطة تتداخل أكثر من الحد المسموح به، يتم حذف أحد التوقعات. لمقارنة جميع التوقعات، يتم مقارنة التوقع 1 مع 2، 3، 4، وهكذا، ثم 2 مع 3، 4، وهكذا. الكود التالي يقوم بذلك:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    يتم حساب التداخل باستخدام طريقة `Polygon.intersection` من Shapely التي تعيد مضلعًا يمثل التداخل. يتم بعد ذلك حساب المساحة من هذا المضلع. هذا الحد للتداخل ليس قيمة مطلقة، ولكنه يحتاج إلى أن يكون نسبة مئوية من الإطار المحيط، لذلك يتم العثور على أصغر إطار محيط، ويتم استخدام حد التداخل لحساب المساحة التي يمكن أن يكون عليها التداخل دون تجاوز نسبة التداخل المسموح بها للإطار المحيط الأصغر. إذا تجاوز التداخل هذا الحد، يتم وضع علامة على التوقع للحذف.

    بمجرد وضع علامة على التوقع للحذف، لا يحتاج إلى التحقق مرة أخرى، لذلك يتم كسر الحلقة الداخلية للتحقق من التوقع التالي. لا يمكنك حذف عناصر من قائمة أثناء التكرار عليها، لذلك يتم إضافة الإطارات المحيطة التي تتداخل أكثر من الحد المسموح به إلى قائمة `to_delete`، ثم يتم حذفها في النهاية.

    أخيرًا، يتم طباعة عدد المخزون إلى وحدة التحكم. يمكن بعد ذلك إرسال هذا العدد إلى خدمة إنترنت الأشياء لتنبيه إذا كانت مستويات المخزون منخفضة. كل هذا الكود يتم قبل رسم الإطارات المحيطة، لذلك سترى توقعات المخزون بدون تداخلات على الصور المولدة.

    > 💁 هذه طريقة بسيطة جدًا لإزالة التداخلات، حيث يتم فقط إزالة الأول في زوج متداخل. بالنسبة لكود الإنتاج، قد ترغب في إضافة المزيد من المنطق هنا، مثل النظر في التداخلات بين كائنات متعددة، أو إذا كان إطار محيط واحد يحتوي على آخر.

1. قم بتشغيل التطبيق مع توجيه الكاميرا نحو بعض المخزون على رف. ستشير النتيجة إلى عدد الإطارات المحيطة بدون تداخلات تتجاوز الحد المسموح به. جرب تعديل قيمة `overlap_threshold` لرؤية التوقعات التي يتم تجاهلها.

> 💁 يمكنك العثور على هذا الكود في مجلد [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) أو [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 لقد كان برنامج عد المخزون الخاص بك نجاحًا!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.