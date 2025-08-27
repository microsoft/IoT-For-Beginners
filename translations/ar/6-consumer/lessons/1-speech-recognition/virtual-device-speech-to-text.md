<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T00:23:43+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "ar"
}
-->
# تحويل الكلام إلى نص - جهاز إنترنت الأشياء الافتراضي

في هذا الجزء من الدرس، ستكتب كودًا لتحويل الكلام الملتقط من الميكروفون الخاص بك إلى نص باستخدام خدمة التعرف على الكلام.

## تحويل الكلام إلى نص

على أنظمة Windows وLinux وmacOS، يمكن استخدام Python SDK الخاص بخدمات التعرف على الكلام للاستماع إلى الميكروفون وتحويل أي كلام يتم اكتشافه إلى نص. سيستمع البرنامج بشكل مستمر، حيث يكتشف مستويات الصوت ويرسل الكلام للتحويل إلى نص عندما ينخفض مستوى الصوت، مثلما يحدث في نهاية فقرة من الكلام.

### المهمة - تحويل الكلام إلى نص

1. قم بإنشاء تطبيق Python جديد على جهاز الكمبيوتر الخاص بك في مجلد يسمى `smart-timer` يحتوي على ملف واحد يسمى `app.py` وبيئة افتراضية لـ Python.

1. قم بتثبيت حزمة Pip الخاصة بخدمات التعرف على الكلام. تأكد من تثبيتها من خلال نافذة طرفية مع تفعيل البيئة الافتراضية.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ إذا واجهت الخطأ التالي:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > ستحتاج إلى تحديث Pip. قم بذلك باستخدام الأمر التالي، ثم حاول تثبيت الحزمة مرة أخرى:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. أضف الواردات التالية إلى ملف `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    هذه الواردات تستخدم لاستيراد بعض الفئات المستخدمة للتعرف على الكلام.

1. أضف الكود التالي لتحديد بعض الإعدادات:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    استبدل `<key>` بمفتاح API الخاص بخدمة التعرف على الكلام. استبدل `<location>` بالموقع الذي استخدمته عند إنشاء مورد خدمة التعرف على الكلام.

    استبدل `<language>` باسم اللغة التي ستتحدث بها، على سبيل المثال `en-GB` للغة الإنجليزية أو `zn-HK` للغة الكانتونية. يمكنك العثور على قائمة باللغات المدعومة وأسمائها في [وثائق دعم اللغة والصوت على موقع Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    يتم استخدام هذه الإعدادات لإنشاء كائن `SpeechConfig` الذي سيُستخدم لتكوين خدمات التعرف على الكلام.

1. أضف الكود التالي لإنشاء أداة التعرف على الكلام:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. تعمل أداة التعرف على الكلام في خلفية التطبيق، حيث تستمع للصوت وتحول أي كلام يتم اكتشافه إلى نص. يمكنك الحصول على النص باستخدام دالة رد نداء (callback) - وهي دالة تقوم بتعريفها وتمريرها إلى أداة التعرف. في كل مرة يتم اكتشاف كلام، يتم استدعاء دالة رد النداء. أضف الكود التالي لتعريف دالة رد النداء وتمريرها إلى أداة التعرف، بالإضافة إلى تعريف دالة لمعالجة النص وكتابته إلى وحدة التحكم:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. لا تبدأ أداة التعرف على الكلام بالاستماع إلا عند تشغيلها صراحة. أضف الكود التالي لبدء عملية التعرف. تعمل هذه العملية في الخلفية، لذا سيحتاج تطبيقك إلى حلقة لا نهائية مع وضع السكون للحفاظ على تشغيل التطبيق.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. قم بتشغيل هذا التطبيق. تحدث في الميكروفون وسيتم تحويل الصوت إلى نص وعرضه في وحدة التحكم.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    جرب أنواعًا مختلفة من الجمل، بالإضافة إلى الجمل التي تحتوي على كلمات متشابهة في الصوت ولكن لها معانٍ مختلفة. على سبيل المثال، إذا كنت تتحدث باللغة الإنجليزية، قل "I want to buy two bananas and an apple too"، ولاحظ كيف سيتم استخدام الكلمات الصحيحة "to"، "two"، و"too" بناءً على سياق الكلمة، وليس فقط صوتها.

> 💁 يمكنك العثور على هذا الكود في المجلد [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 لقد نجح برنامج تحويل الكلام إلى نص الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.