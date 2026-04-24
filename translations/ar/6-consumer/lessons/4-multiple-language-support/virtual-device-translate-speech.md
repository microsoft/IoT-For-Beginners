# ترجمة الكلام - جهاز إنترنت الأشياء الافتراضي

في هذا الجزء من الدرس، ستكتب كودًا لترجمة الكلام عند تحويله إلى نص باستخدام خدمة الكلام، ثم ترجمة النص باستخدام خدمة المترجم قبل إنشاء استجابة منطوقة.

## استخدام خدمة الكلام لترجمة الكلام

يمكن لخدمة الكلام أن تأخذ الكلام وتحوله إلى نص ليس فقط بنفس اللغة، بل يمكنها أيضًا ترجمة النص الناتج إلى لغات أخرى.

### المهمة - استخدام خدمة الكلام لترجمة الكلام

1. افتح مشروع `smart-timer` في VS Code، وتأكد من تحميل البيئة الافتراضية في الطرفية.

1. أضف عبارات الاستيراد التالية أسفل عبارات الاستيراد الحالية:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    هذا يستورد الفئات المستخدمة لترجمة الكلام، ومكتبة `requests` التي ستُستخدم لإجراء استدعاء لخدمة المترجم لاحقًا في هذا الدرس.

1. سيكون لجهاز المؤقت الذكي لغتان محددتان - لغة الخادم التي تم استخدامها لتدريب LUIS (وهي نفس اللغة المستخدمة لبناء الرسائل للتحدث مع المستخدم)، ولغة المستخدم. قم بتحديث متغير `language` ليكون اللغة التي سيتحدث بها المستخدم، وأضف متغيرًا جديدًا يسمى `server_language` للغة المستخدمة لتدريب LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    استبدل `<user language>` باسم اللغة المحلية التي ستتحدث بها، على سبيل المثال `fr-FR` للفرنسية، أو `zn-HK` للكانتونية.

    استبدل `<server language>` باسم اللغة المحلية المستخدمة لتدريب LUIS.

    يمكنك العثور على قائمة باللغات المدعومة وأسمائها المحلية في [وثائق دعم اللغة والصوت على موقع Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 إذا كنت لا تتحدث لغات متعددة، يمكنك استخدام خدمة مثل [Bing Translate](https://www.bing.com/translator) أو [Google Translate](https://translate.google.com) لترجمة النصوص من لغتك المفضلة إلى لغة أخرى. يمكن لهذه الخدمات تشغيل الصوت للنصوص المترجمة. لاحظ أن جهاز التعرف على الكلام قد يتجاهل بعض الأصوات الصادرة من جهازك، لذا قد تحتاج إلى استخدام جهاز إضافي لتشغيل النصوص المترجمة.
    >
    > على سبيل المثال، إذا قمت بتدريب LUIS باللغة الإنجليزية، ولكنك تريد استخدام الفرنسية كلغة للمستخدم، يمكنك ترجمة جمل مثل "اضبط مؤقتًا لمدة دقيقتين و27 ثانية" من الإنجليزية إلى الفرنسية باستخدام Bing Translate، ثم استخدام زر **الاستماع إلى الترجمة** للتحدث بالترجمة إلى الميكروفون.
    >
    > ![زر الاستماع إلى الترجمة في Bing Translate](../../../../../translated_images/ar/bing-translate.348aa796d6efe2a9.webp)

1. استبدل تعريفات `recognizer_config` و`recognizer` بالتالي:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    هذا ينشئ تكوين ترجمة للتعرف على الكلام بلغة المستخدم، وإنشاء ترجمات بلغة المستخدم ولغة الخادم. ثم يستخدم هذا التكوين لإنشاء مترجم للتعرف على الكلام - وهو جهاز تعرّف على الكلام يمكنه ترجمة ناتج التعرف على الكلام إلى لغات متعددة.

    > 💁 يجب تحديد اللغة الأصلية في `target_languages`، وإلا فلن تحصل على أي ترجمات.

1. قم بتحديث وظيفة `recognized`، واستبدل محتويات الوظيفة بالكامل بالتالي:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    يتحقق هذا الكود مما إذا كان حدث التعرف قد تم تشغيله بسبب ترجمة الكلام (يمكن أن يتم تشغيل هذا الحدث في أوقات أخرى، مثل عندما يتم التعرف على الكلام ولكن لم يتم ترجمته). إذا تم ترجمة الكلام، فإنه يجد الترجمة في قاموس `args.result.translations` الذي يتطابق مع لغة الخادم.

    قاموس `args.result.translations` يستخدم الجزء الخاص باللغة من إعدادات اللغة المحلية، وليس الإعداد بالكامل. على سبيل المثال، إذا طلبت ترجمة إلى `fr-FR` للفرنسية، فإن القاموس سيحتوي على إدخال لـ `fr`، وليس `fr-FR`.

    يتم بعد ذلك إرسال النص المترجم إلى IoT Hub.

1. قم بتشغيل هذا الكود لاختبار الترجمات. تأكد من تشغيل تطبيق الوظائف الخاص بك، واطلب مؤقتًا بلغة المستخدم، إما عن طريق التحدث بتلك اللغة بنفسك، أو باستخدام تطبيق ترجمة.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## ترجمة النص باستخدام خدمة المترجم

لا تدعم خدمة الكلام ترجمة النصوص مرة أخرى إلى كلام، بدلاً من ذلك يمكنك استخدام خدمة المترجم لترجمة النصوص. تحتوي هذه الخدمة على واجهة برمجة تطبيقات REST يمكنك استخدامها لترجمة النصوص.

### المهمة - استخدام مورد المترجم لترجمة النصوص

1. أضف مفتاح API الخاص بالمترجم أسفل `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    استبدل `<key>` بمفتاح API الخاص بمورد خدمة المترجم.

1. فوق وظيفة `say`، قم بتعريف وظيفة `translate_text` التي ستترجم النصوص من لغة الخادم إلى لغة المستخدم:

    ```python
    def translate_text(text):
    ```

1. داخل هذه الوظيفة، قم بتعريف عنوان URL والرؤوس لاستدعاء واجهة برمجة التطبيقات:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    عنوان URL لهذه الواجهة ليس خاصًا بالموقع، بدلاً من ذلك يتم تمرير الموقع كرأس. يتم استخدام مفتاح API مباشرة، لذا على عكس خدمة الكلام، لا حاجة للحصول على رمز وصول من واجهة برمجة التطبيقات الخاصة بإصدار الرموز.

1. أسفل ذلك، قم بتعريف المعلمات والجسم للاستدعاء:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    يقوم `params` بتعريف المعلمات التي يتم تمريرها لاستدعاء واجهة برمجة التطبيقات، حيث يتم تمرير اللغات المصدر والهدف. سيقوم هذا الاستدعاء بترجمة النصوص من اللغة المصدر إلى اللغة الهدف.

    يحتوي `body` على النصوص المراد ترجمتها. هذا عبارة عن مصفوفة، حيث يمكن ترجمة كتل نصوص متعددة في نفس الاستدعاء.

1. قم بإجراء استدعاء واجهة برمجة التطبيقات REST، واحصل على الاستجابة:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    الاستجابة التي تعود هي مصفوفة JSON، تحتوي على عنصر واحد يحتوي على الترجمات. يحتوي هذا العنصر على مصفوفة لترجمات جميع العناصر التي تم تمريرها في الجسم.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. قم بإرجاع الخاصية `text` من أول ترجمة من أول عنصر في المصفوفة:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. قم بتحديث وظيفة `say` لترجمة النصوص قبل إنشاء SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    يقوم هذا الكود أيضًا بطباعة النسخة الأصلية والمترجمة من النصوص إلى وحدة التحكم.

1. قم بتشغيل الكود الخاص بك. تأكد من تشغيل تطبيق الوظائف الخاص بك، واطلب مؤقتًا بلغة المستخدم، إما عن طريق التحدث بتلك اللغة بنفسك، أو باستخدام تطبيق ترجمة.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 بسبب الطرق المختلفة لقول شيء ما في لغات مختلفة، قد تحصل على ترجمات تختلف قليلاً عن الأمثلة التي قدمتها لـ LUIS. إذا كان هذا هو الحال، أضف المزيد من الأمثلة إلى LUIS، ثم أعد التدريب وأعد نشر النموذج.

> 💁 يمكنك العثور على هذا الكود في المجلد [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 لقد كان برنامج المؤقت متعدد اللغات الخاص بك نجاحًا!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.