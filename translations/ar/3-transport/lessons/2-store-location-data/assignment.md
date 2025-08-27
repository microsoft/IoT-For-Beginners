<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T01:03:10+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "ar"
}
-->
# التحقيق في ارتباطات الوظائف

## التعليمات

تتيح لك ارتباطات الوظائف حفظ الكتل (blobs) في تخزين الكتل عن طريق إرجاعها من وظيفة `main`. يتم تكوين حساب تخزين Azure، المجموعة، والتفاصيل الأخرى في ملف `function.json`.

عند العمل مع Azure أو تقنيات Microsoft الأخرى، فإن أفضل مصدر للمعلومات هو [وثائق Microsoft على docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). في هذه المهمة، ستحتاج إلى قراءة وثائق ارتباطات وظائف Azure لمعرفة كيفية إعداد ارتباط الإخراج.

بعض الصفحات التي يمكنك البدء بها هي:

* [مفاهيم مشغلات وارتباطات وظائف Azure](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [نظرة عامة على ارتباطات تخزين الكتل لوظائف Azure](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [ارتباط إخراج تخزين الكتل لوظائف Azure](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## التقييم

| المعايير | ممتاز | مقبول | يحتاج إلى تحسين |
| -------- | ------- | ------- | --------------- |
| إعداد ارتباط إخراج تخزين الكتل | تم إعداد ارتباط الإخراج بنجاح، وتم إرجاع الكتلة وتخزينها بنجاح في تخزين الكتل | تم إعداد ارتباط الإخراج أو إرجاع الكتلة ولكن لم يتم تخزينها بنجاح في تخزين الكتل | لم يتم إعداد ارتباط الإخراج |

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو عدم دقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالترجمة البشرية الاحترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.