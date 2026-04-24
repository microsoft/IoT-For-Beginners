# تصنيف صورة - أجهزة إنترنت الأشياء الافتراضية و Raspberry Pi

في هذا الجزء من الدرس، ستقوم بإرسال الصورة التي تم التقاطها بواسطة الكاميرا إلى خدمة Custom Vision لتصنيفها.

## إرسال الصور إلى Custom Vision

تحتوي خدمة Custom Vision على مكتبة SDK بلغة Python يمكنك استخدامها لتصنيف الصور.

### المهمة - إرسال الصور إلى Custom Vision

1. افتح مجلد `fruit-quality-detector` في VS Code. إذا كنت تستخدم جهاز إنترنت الأشياء الافتراضي، تأكد من تشغيل البيئة الافتراضية في الطرفية.

1. مكتبة SDK الخاصة بـ Python لإرسال الصور إلى Custom Vision متوفرة كحزمة Pip. قم بتثبيتها باستخدام الأمر التالي:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. أضف عبارات الاستيراد التالية في أعلى ملف `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    هذا يجلب بعض الوحدات من مكتبات Custom Vision، واحدة للمصادقة باستخدام مفتاح التنبؤ، وأخرى لتوفير فئة عميل التنبؤ التي يمكنها الاتصال بـ Custom Vision.

1. أضف الكود التالي إلى نهاية الملف:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    استبدل `<prediction_url>` بالرابط الذي نسخته من مربع الحوار *Prediction URL* سابقًا في هذا الدرس. استبدل `<prediction key>` بمفتاح التنبؤ الذي نسخته من نفس مربع الحوار.

1. الرابط الذي تم توفيره من مربع الحوار *Prediction URL* مصمم للاستخدام عند الاتصال بنقطة النهاية REST مباشرة. مكتبة SDK الخاصة بـ Python تستخدم أجزاء من الرابط في أماكن مختلفة. أضف الكود التالي لتقسيم هذا الرابط إلى الأجزاء المطلوبة:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    هذا يقوم بتقسيم الرابط، مستخرجًا نقطة النهاية `https://<location>.api.cognitive.microsoft.com`، ومعرف المشروع، واسم النسخة المنشورة.

1. قم بإنشاء كائن تنبؤ لتنفيذ التنبؤ باستخدام الكود التالي:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` تغلف مفتاح التنبؤ. يتم استخدام هذه لإنشاء كائن عميل التنبؤ الذي يشير إلى نقطة النهاية.

1. أرسل الصورة إلى Custom Vision باستخدام الكود التالي:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    هذا يعيد الصورة إلى البداية، ثم يرسلها إلى عميل التنبؤ.

1. أخيرًا، اعرض النتائج باستخدام الكود التالي:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    هذا سيقوم بالدوران عبر جميع التنبؤات التي تم إرجاعها وعرضها في الطرفية. الاحتمالات التي يتم إرجاعها هي أرقام عشرية بين 0-1، حيث 0 يعني احتمال 0% لمطابقة العلامة، و1 يعني احتمال 100%.

    > 💁 مصنفات الصور ستقوم بإرجاع النسب المئوية لجميع العلامات التي تم استخدامها. كل علامة سيكون لها احتمال أن الصورة تطابق تلك العلامة.

1. قم بتشغيل الكود الخاص بك، مع توجيه الكاميرا نحو بعض الفواكه، أو مجموعة صور مناسبة، أو فواكه مرئية على كاميرا الويب الخاصة بك إذا كنت تستخدم أجهزة إنترنت الأشياء الافتراضية. سترى الإخراج في وحدة التحكم:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    ستتمكن من رؤية الصورة التي تم التقاطها، وهذه القيم في علامة التبويب **Predictions** في Custom Vision.

    ![موزة في Custom Vision تم التنبؤ بأنها ناضجة بنسبة 56.8% وغير ناضجة بنسبة 43.1%](../../../../../translated_images/ar/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 يمكنك العثور على هذا الكود في مجلد [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) أو [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 برنامج تصنيف جودة الفواكه الخاص بك كان ناجحًا!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.