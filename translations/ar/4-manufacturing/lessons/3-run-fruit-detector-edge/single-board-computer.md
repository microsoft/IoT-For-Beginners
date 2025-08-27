<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-26T22:04:01+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "ar"
}
-->
# تصنيف صورة باستخدام مصنف صور يعتمد على IoT Edge - أجهزة IoT الافتراضية و Raspberry Pi

في هذا الجزء من الدرس، ستستخدم مصنف الصور الذي يعمل على جهاز IoT Edge.

## استخدام مصنف IoT Edge

يمكن إعادة توجيه جهاز IoT لاستخدام مصنف الصور الخاص بـ IoT Edge. عنوان URL لمصنف الصور هو `http://<IP address or name>/image`، مع استبدال `<IP address or name>` بعنوان IP أو اسم المضيف الخاص بالحاسوب الذي يعمل عليه IoT Edge.

مكتبة Python الخاصة بـ Custom Vision تعمل فقط مع النماذج المستضافة على السحابة، وليس النماذج المستضافة على IoT Edge. هذا يعني أنك ستحتاج إلى استخدام REST API لاستدعاء المصنف.

### المهمة - استخدام مصنف IoT Edge

1. افتح مشروع `fruit-quality-detector` في VS Code إذا لم يكن مفتوحًا بالفعل. إذا كنت تستخدم جهاز IoT افتراضي، فتأكد من تفعيل البيئة الافتراضية.

1. افتح ملف `app.py`، وقم بإزالة عبارات الاستيراد من `azure.cognitiveservices.vision.customvision.prediction` و `msrest.authentication`.

1. أضف الاستيراد التالي في أعلى الملف:

    ```python
    import requests
    ```

1. احذف كل الكود بعد حفظ الصورة في ملف، من `image_file.write(image.read())` إلى نهاية الملف.

1. أضف الكود التالي إلى نهاية الملف:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    استبدل `<URL>` بعنوان URL الخاص بالمصنف.

    يقوم هذا الكود بإجراء طلب REST POST إلى المصنف، ويرسل الصورة كجسم الطلب. النتائج تعود بصيغة JSON، ويتم فك تشفيرها لعرض الاحتمالات.

1. قم بتشغيل الكود الخاص بك، مع توجيه الكاميرا نحو بعض الفواكه، أو مجموعة صور مناسبة، أو فواكه مرئية على كاميرا الويب إذا كنت تستخدم أجهزة IoT افتراضية. سترى النتائج في وحدة التحكم:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 يمكنك العثور على هذا الكود في مجلد [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) أو [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 لقد نجح برنامج مصنف جودة الفواكه الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.