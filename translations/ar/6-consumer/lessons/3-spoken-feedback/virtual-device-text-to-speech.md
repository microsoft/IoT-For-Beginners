<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T00:17:22+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "ar"
}
-->
# تحويل النص إلى كلام - جهاز إنترنت الأشياء الافتراضي

في هذا الجزء من الدرس، ستكتب كودًا لتحويل النص إلى كلام باستخدام خدمة الكلام.

## تحويل النص إلى كلام

يمكن استخدام حزمة SDK لخدمات الكلام التي استخدمتها في الدرس السابق لتحويل الكلام إلى نص لتحويل النص مرة أخرى إلى كلام. عند طلب الكلام، تحتاج إلى تحديد الصوت الذي سيتم استخدامه، حيث يمكن إنشاء الكلام باستخدام مجموعة متنوعة من الأصوات المختلفة.

كل لغة تدعم مجموعة من الأصوات المختلفة، ويمكنك الحصول على قائمة الأصوات المدعومة لكل لغة من خلال حزمة SDK لخدمات الكلام.

### المهمة - تحويل النص إلى كلام

1. افتح مشروع `smart-timer` في VS Code، وتأكد من تحميل البيئة الافتراضية في الطرفية.

1. قم باستيراد `SpeechSynthesizer` من الحزمة `azure.cognitiveservices.speech` عن طريق إضافته إلى الاستيرادات الحالية:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. فوق وظيفة `say`، قم بإنشاء إعدادات الكلام لاستخدامها مع المولد الصوتي:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    يستخدم هذا نفس مفتاح API، الموقع، واللغة التي استخدمها المميز الصوتي.

1. أسفل هذا، أضف الكود التالي للحصول على صوت وتعيينه في إعدادات الكلام:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    يقوم هذا باسترجاع قائمة بجميع الأصوات المتاحة، ثم يجد أول صوت يتطابق مع اللغة المستخدمة.

    > 💁 يمكنك الحصول على القائمة الكاملة للأصوات المدعومة من [وثائق دعم اللغة والصوت على Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). إذا كنت ترغب في استخدام صوت معين، يمكنك إزالة هذه الوظيفة وتحديد الصوت مباشرة باستخدام اسم الصوت من هذه الوثائق. على سبيل المثال:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. قم بتحديث محتويات وظيفة `say` لإنشاء SSML للاستجابة:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. أسفل هذا، قم بإيقاف التعرف على الكلام، تحدث SSML، ثم أعد تشغيل التعرف:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    يتم إيقاف التعرف أثناء التحدث لتجنب اكتشاف إعلان بدء المؤقت، إرساله إلى LUIS، وربما تفسيره كطلب لتعيين مؤقت جديد.

    > 💁 يمكنك اختبار ذلك عن طريق تعليق الأسطر لإيقاف وإعادة تشغيل التعرف. قم بتعيين مؤقت واحد، وقد تجد أن الإعلان يعين مؤقتًا جديدًا، مما يؤدي إلى إعلان جديد، مما يسبب مؤقتًا جديدًا، وهكذا إلى الأبد!

1. قم بتشغيل التطبيق، وتأكد من تشغيل تطبيق الوظيفة أيضًا. قم بتعيين بعض المؤقتات، وستسمع استجابة صوتية تقول إن المؤقت الخاص بك قد تم تعيينه، ثم استجابة صوتية أخرى عندما يكتمل المؤقت.

> 💁 يمكنك العثور على هذا الكود في مجلد [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 برنامج المؤقت الخاص بك كان ناجحًا!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.