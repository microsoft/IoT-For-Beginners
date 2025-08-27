<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-26T21:29:24+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "ar"
}
-->
# استدعاء كاشف الكائنات من جهاز إنترنت الأشياء الخاص بك - الأجهزة الافتراضية لإنترنت الأشياء و Raspberry Pi

بمجرد نشر كاشف الكائنات الخاص بك، يمكنك استخدامه من جهاز إنترنت الأشياء الخاص بك.

## نسخ مشروع مصنف الصور

معظم كود كاشف المخزون مشابه تمامًا لمصنف الصور الذي قمت بإنشائه في درس سابق.

### المهمة - نسخ مشروع مصنف الصور

1. قم بإنشاء مجلد يسمى `stock-counter` إما على جهاز الكمبيوتر الخاص بك إذا كنت تستخدم جهاز إنترنت أشياء افتراضي، أو على Raspberry Pi. إذا كنت تستخدم جهاز إنترنت أشياء افتراضي، تأكد من إعداد بيئة افتراضية.

1. قم بإعداد أجهزة الكاميرا.

   * إذا كنت تستخدم Raspberry Pi، ستحتاج إلى تركيب PiCamera. قد ترغب أيضًا في تثبيت الكاميرا في وضع ثابت، على سبيل المثال، عن طريق تعليق الكابل فوق صندوق أو علبة، أو تثبيت الكاميرا على صندوق باستخدام شريط لاصق مزدوج.
   * إذا كنت تستخدم جهاز إنترنت أشياء افتراضي، فستحتاج إلى تثبيت CounterFit و CounterFit PyCamera shim. إذا كنت ستستخدم صورًا ثابتة، فقم بالتقاط بعض الصور التي لم يرها كاشف الكائنات الخاص بك بعد. إذا كنت ستستخدم كاميرا الويب، فتأكد من وضعها بطريقة تمكنها من رؤية المخزون الذي تقوم بالكشف عنه.

1. قم بتكرار الخطوات من [الدرس الثاني من مشروع التصنيع](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) لالتقاط الصور من الكاميرا.

1. قم بتكرار الخطوات من [الدرس الثاني من مشروع التصنيع](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) لاستدعاء مصنف الصور. سيتم إعادة استخدام معظم هذا الكود للكشف عن الكائنات.

## تعديل الكود من مصنف إلى كاشف كائنات

الكود الذي استخدمته لتصنيف الصور مشابه جدًا للكود المستخدم للكشف عن الكائنات. الفرق الرئيسي هو الطريقة المستدعاة من Custom Vision SDK، ونتائج الاستدعاء.

### المهمة - تعديل الكود من مصنف إلى كاشف كائنات

1. احذف الأسطر الثلاثة من الكود التي تصنف الصورة وتعالج التوقعات:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    قم بإزالة هذه الأسطر الثلاثة.

1. أضف الكود التالي للكشف عن الكائنات في الصورة:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    هذا الكود يستدعي طريقة `detect_image` على الكائن predictor لتشغيل كاشف الكائنات. ثم يجمع جميع التوقعات التي تتجاوز احتمالية معينة، ويطبعها على وحدة التحكم.

    على عكس مصنف الصور الذي يعيد نتيجة واحدة فقط لكل علامة، كاشف الكائنات يعيد نتائج متعددة، لذلك يجب تصفية أي نتائج ذات احتمالية منخفضة.

1. قم بتشغيل هذا الكود، وسيقوم بالتقاط صورة، وإرسالها إلى كاشف الكائنات، وطباعة الكائنات المكتشفة. إذا كنت تستخدم جهاز إنترنت أشياء افتراضي، تأكد من تعيين صورة مناسبة في CounterFit، أو أن كاميرا الويب الخاصة بك محددة. إذا كنت تستخدم Raspberry Pi، تأكد من أن الكاميرا تشير إلى الكائنات الموجودة على الرف.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 قد تحتاج إلى ضبط قيمة `threshold` لتناسب الصور الخاصة بك.

    ستتمكن من رؤية الصورة التي تم التقاطها، وهذه القيم في علامة التبويب **Predictions** في Custom Vision.

    ![4 علب من معجون الطماطم على رف مع توقعات للكشف الأربعة بنسبة 35.8%، 33.5%، 25.7% و16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.ar.png)

> 💁 يمكنك العثور على هذا الكود في المجلد [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) أو [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 لقد نجح برنامج عداد المخزون الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.