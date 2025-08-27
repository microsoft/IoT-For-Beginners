<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-26T22:01:33+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "ar"
}
-->
# تشغيل خدمات أخرى على الحافة

## التعليمات

ليس فقط مصنّفات الصور يمكن تشغيلها على الحافة، بل أي شيء يمكن تعبئته في حاوية يمكن نشره على جهاز IoT Edge. يمكن تشغيل التعليمات البرمجية بدون خادم كوظائف Azure Functions، مثل المشغلات التي قمت بإنشائها في الدروس السابقة، داخل الحاويات، وبالتالي على IoT Edge.

اختر أحد الدروس السابقة وحاول تشغيل تطبيق Azure Functions في حاوية IoT Edge. يمكنك العثور على دليل يوضح كيفية القيام بذلك باستخدام مشروع تطبيق Functions مختلف في [Tutorial: Deploy Azure Functions as IoT Edge modules on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## معايير التقييم

| المعايير | ممتاز | مقبول | يحتاج إلى تحسين |
| -------- | ------ | ------ | --------------- |
| نشر تطبيق Azure Functions إلى IoT Edge | تمكن من نشر تطبيق Azure Functions إلى IoT Edge واستخدامه مع جهاز IoT لتشغيل مشغل من بيانات IoT | تمكن من نشر تطبيق Functions إلى IoT Edge، لكنه لم يتمكن من تشغيل المشغل | لم يتمكن من نشر تطبيق Functions إلى IoT Edge |

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.