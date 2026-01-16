<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-26T21:33:27+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ar"
}
-->
# عد المخزون باستخدام جهاز إنترنت الأشياء - Wio Terminal

يمكن استخدام مزيج من التوقعات وإطارات التحديد الخاصة بها لعد المخزون في صورة.

## عد المخزون

![4 علب من معجون الطماطم مع إطارات تحديد حول كل علبة](../../../../../translated_images/ar/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

في الصورة الموضحة أعلاه، هناك تداخل بسيط بين إطارات التحديد. إذا كان هذا التداخل أكبر بكثير، فقد تشير إطارات التحديد إلى نفس الكائن. لعد الكائنات بشكل صحيح، تحتاج إلى تجاهل الإطارات ذات التداخل الكبير.

### المهمة - عد المخزون مع تجاهل التداخل

1. افتح مشروعك `stock-counter` إذا لم يكن مفتوحًا بالفعل.

1. فوق دالة `processPredictions`، أضف الكود التالي:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    هذا يحدد النسبة المئوية للتداخل المسموح بها قبل اعتبار إطارات التحديد لنفس الكائن. القيمة 0.20 تعني تداخل بنسبة 20%.

1. أسفل هذا، وفوق دالة `processPredictions`، أضف الكود التالي لحساب التداخل بين مستطيلين:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    هذا الكود يعرّف بنية `Point` لتخزين النقاط على الصورة، وبنية `Rect` لتعريف مستطيل باستخدام إحداثيات الزاوية العلوية اليسرى والسفلية اليمنى. ثم يعرّف دالة `area` التي تحسب مساحة المستطيل من إحداثيات الزاوية العلوية اليسرى والسفلية اليمنى.

    بعد ذلك، يعرّف دالة `overlappingArea` التي تحسب مساحة التداخل بين مستطيلين. إذا لم يكن هناك تداخل، تعيد القيمة 0.

1. أسفل دالة `overlappingArea`، قم بتعريف دالة لتحويل إطار التحديد إلى `Rect`:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    هذه الدالة تأخذ توقعًا من كاشف الكائنات، وتستخرج إطار التحديد وتستخدم القيم الموجودة في إطار التحديد لتعريف مستطيل. يتم حساب الجانب الأيمن من خلال جمع اليسار مع العرض. ويتم حساب الأسفل من خلال جمع الأعلى مع الارتفاع.

1. يجب مقارنة التوقعات مع بعضها البعض، وإذا كان هناك تداخل بين توقعين يتجاوز العتبة المحددة، يجب حذف أحدهما. عتبة التداخل هي نسبة مئوية، لذا يجب ضربها في حجم أصغر إطار تحديد للتحقق مما إذا كان التداخل يتجاوز النسبة المحددة من إطار التحديد، وليس النسبة المحددة من الصورة بأكملها. ابدأ بحذف محتوى دالة `processPredictions`.

1. أضف التالي إلى دالة `processPredictions` الفارغة:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    هذا الكود يعرّف متجهًا لتخزين التوقعات التي لا تتداخل. ثم يقوم بالتكرار عبر جميع التوقعات، ويقوم بإنشاء `Rect` من إطار التحديد.

    بعد ذلك، يقوم هذا الكود بالتكرار عبر التوقعات المتبقية، بدءًا من التوقع الذي يلي التوقع الحالي. هذا يمنع مقارنة التوقعات أكثر من مرة - بمجرد مقارنة 1 و2، لا حاجة لمقارنة 2 مع 1، فقط مع 3، 4، وهكذا.

    لكل زوج من التوقعات، يتم حساب مساحة التداخل. ثم يتم مقارنة هذه المساحة بمساحة أصغر إطار تحديد - إذا تجاوز التداخل النسبة المئوية المحددة من أصغر إطار تحديد، يتم وضع علامة على التوقع بأنه لم ينجح. إذا اجتاز التوقع الفحوصات بعد مقارنة جميع التداخلات، يتم إضافته إلى مجموعة `passed_predictions`.

    > 💁 هذه طريقة بسيطة جدًا لإزالة التداخلات، حيث يتم فقط إزالة الأول في زوج التداخل. بالنسبة للكود الإنتاجي، قد ترغب في إضافة المزيد من المنطق هنا، مثل النظر في التداخلات بين كائنات متعددة، أو إذا كان أحد إطارات التحديد يحتوي على الآخر.

1. بعد ذلك، أضف الكود التالي لإرسال تفاصيل التوقعات التي اجتازت الفحوصات إلى شاشة المراقبة التسلسلية:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    هذا الكود يقوم بالتكرار عبر التوقعات التي اجتازت الفحوصات ويطبع تفاصيلها إلى شاشة المراقبة التسلسلية.

1. أسفل هذا، أضف كودًا لطباعة عدد العناصر التي تم عدها إلى شاشة المراقبة التسلسلية:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    يمكن بعد ذلك إرسال هذا إلى خدمة إنترنت الأشياء لتنبيهك إذا كانت مستويات المخزون منخفضة.

1. قم بتحميل وتشغيل الكود الخاص بك. وجه الكاميرا نحو الكائنات على رف واضغط على الزر C. حاول تعديل قيمة `overlap_threshold` لرؤية التوقعات التي يتم تجاهلها.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 يمكنك العثور على هذا الكود في المجلد [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 لقد كان برنامج عد المخزون الخاص بك ناجحًا!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.