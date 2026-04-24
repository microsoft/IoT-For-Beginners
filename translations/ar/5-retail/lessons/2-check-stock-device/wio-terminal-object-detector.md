# استدعاء كاشف الكائنات من جهاز إنترنت الأشياء الخاص بك - Wio Terminal

بمجرد نشر كاشف الكائنات الخاص بك، يمكن استخدامه من جهاز إنترنت الأشياء الخاص بك.

## نسخ مشروع تصنيف الصور

معظم كاشف المخزون الخاص بك مشابه لمصنف الصور الذي أنشأته في درس سابق.

### المهمة - نسخ مشروع تصنيف الصور

1. قم بتوصيل كاميرا ArduCam بجهاز Wio Terminal الخاص بك، باتباع الخطوات من [الدرس الثاني من مشروع التصنيع](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    قد ترغب أيضًا في تثبيت الكاميرا في وضع ثابت، على سبيل المثال، عن طريق تعليق الكابل فوق صندوق أو علبة، أو تثبيت الكاميرا على صندوق باستخدام شريط لاصق مزدوج.

1. قم بإنشاء مشروع جديد تمامًا لجهاز Wio Terminal باستخدام PlatformIO. قم بتسمية هذا المشروع `stock-counter`.

1. قم بتكرار الخطوات من [الدرس الثاني من مشروع التصنيع](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) لالتقاط الصور من الكاميرا.

1. قم بتكرار الخطوات من [الدرس الثاني من مشروع التصنيع](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) لاستدعاء مصنف الصور. سيتم إعادة استخدام معظم هذا الكود لاكتشاف الكائنات.

## تغيير الكود من مصنف إلى كاشف الصور

الكود الذي استخدمته لتصنيف الصور مشابه جدًا للكود المستخدم لاكتشاف الكائنات. الفرق الرئيسي هو عنوان URL الذي يتم استدعاؤه والذي حصلت عليه من Custom Vision، ونتائج الاستدعاء.

### المهمة - تغيير الكود من مصنف إلى كاشف الصور

1. أضف التوجيه التالي إلى أعلى ملف `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. قم بإعادة تسمية وظيفة `classifyImage` إلى `detectStock`، سواء اسم الوظيفة أو الاستدعاء في وظيفة `buttonPressed`.

1. فوق وظيفة `detectStock`، قم بتحديد عتبة لتصفية أي اكتشافات ذات احتمالية منخفضة:

    ```cpp
    const float threshold = 0.3f;
    ```

    على عكس مصنف الصور الذي يعيد نتيجة واحدة فقط لكل علامة، فإن كاشف الكائنات سيعيد نتائج متعددة، لذا يجب تصفية أي نتائج ذات احتمالية منخفضة.

1. فوق وظيفة `detectStock`، قم بتحديد وظيفة لمعالجة التوقعات:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    هذه الوظيفة تأخذ قائمة بالتوقعات وتطبعها إلى شاشة المراقبة التسلسلية.

1. في وظيفة `detectStock`، استبدل محتويات الحلقة `for` التي تدور عبر التوقعات بما يلي:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    هذه الحلقة تدور عبر التوقعات، وتقارن الاحتمالية بالعتبة. يتم إضافة جميع التوقعات التي لديها احتمالية أعلى من العتبة إلى قائمة ويتم تمريرها إلى وظيفة `processPredictions`.

1. قم برفع وتشغيل الكود الخاص بك. وجه الكاميرا نحو الكائنات على رف واضغط على زر C. سترى الإخراج في شاشة المراقبة التسلسلية:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 قد تحتاج إلى ضبط قيمة `threshold` لتناسب صورك.

    ستتمكن من رؤية الصورة التي تم التقاطها، وهذه القيم في علامة التبويب **Predictions** في Custom Vision.

    ![4 علب من معجون الطماطم على رف مع توقعات لـ 4 اكتشافات بنسبة 35.8%، 33.5%، 25.7% و16.6%](../../../../../translated_images/ar/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 يمكنك العثور على هذا الكود في مجلد [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 برنامج عداد المخزون الخاص بك كان ناجحًا!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.