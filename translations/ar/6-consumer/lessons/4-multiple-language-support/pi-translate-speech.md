# ترجمة الكلام - Raspberry Pi

في هذا الجزء من الدرس، ستكتب كودًا لترجمة النص باستخدام خدمة الترجمة.

## تحويل النص إلى كلام باستخدام خدمة الترجمة

واجهة برمجة التطبيقات REST الخاصة بخدمة الكلام لا تدعم الترجمة المباشرة، ولكن يمكنك استخدام خدمة الترجمة لترجمة النص الناتج عن خدمة تحويل الكلام إلى نص، وكذلك النص الخاص بالرد المنطوق. هذه الخدمة تحتوي على واجهة برمجة التطبيقات REST التي يمكنك استخدامها لترجمة النص.

### المهمة - استخدام مورد الترجمة لترجمة النص

1. سيكون لديك لغتان محددتان في المؤقت الذكي - لغة الخادم التي تم استخدامها لتدريب LUIS (وهي نفس اللغة التي تُستخدم لبناء الرسائل للتحدث مع المستخدم)، ولغة المستخدم المنطوقة. قم بتحديث المتغير `language` ليكون اللغة التي سيتم التحدث بها من قبل المستخدم، وأضف متغيرًا جديدًا يسمى `server_language` للغة المستخدمة لتدريب LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    استبدل `<user language>` باسم المنطقة للغة التي ستتحدث بها، على سبيل المثال `fr-FR` للفرنسية، أو `zn-HK` للكانتونية.

    استبدل `<server language>` باسم المنطقة للغة المستخدمة لتدريب LUIS.

    يمكنك العثور على قائمة باللغات المدعومة وأسماء المناطق الخاصة بها في [وثائق دعم اللغة والصوت على موقع Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 إذا كنت لا تتحدث لغات متعددة، يمكنك استخدام خدمة مثل [Bing Translate](https://www.bing.com/translator) أو [Google Translate](https://translate.google.com) لترجمة النص من لغتك المفضلة إلى لغة أخرى من اختيارك. يمكن لهذه الخدمات تشغيل الصوت للنص المترجم.
    >
    > على سبيل المثال، إذا قمت بتدريب LUIS باللغة الإنجليزية، ولكنك ترغب في استخدام الفرنسية كلغة المستخدم، يمكنك ترجمة جمل مثل "اضبط مؤقت لمدة دقيقتين و27 ثانية" من الإنجليزية إلى الفرنسية باستخدام Bing Translate، ثم استخدام زر **الاستماع إلى الترجمة** للتحدث بالترجمة إلى الميكروفون.
    >
    > ![زر الاستماع إلى الترجمة في Bing Translate](../../../../../translated_images/ar/bing-translate.348aa796d6efe2a9.webp)

1. أضف مفتاح واجهة برمجة التطبيقات الخاص بخدمة الترجمة أسفل `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    استبدل `<key>` بمفتاح واجهة برمجة التطبيقات الخاص بمورد خدمة الترجمة.

1. فوق وظيفة `say`، قم بتعريف وظيفة `translate_text` التي ستقوم بترجمة النص من لغة الخادم إلى لغة المستخدم:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    يتم تمرير اللغات المصدر والهدف إلى هذه الوظيفة - يحتاج التطبيق الخاص بك إلى التحويل من لغة المستخدم إلى لغة الخادم عند التعرف على الكلام، ومن لغة الخادم إلى لغة المستخدم عند تقديم رد منطوق.

1. داخل هذه الوظيفة، قم بتعريف عنوان URL والرؤوس الخاصة باستدعاء واجهة برمجة التطبيقات REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    عنوان URL لهذه الواجهة ليس خاصًا بالموقع، بل يتم تمرير الموقع كرأس. يتم استخدام مفتاح واجهة برمجة التطبيقات مباشرة، لذا على عكس خدمة الكلام، لا توجد حاجة للحصول على رمز وصول من واجهة برمجة التطبيقات الخاصة بإصدار الرموز.

1. أسفل ذلك، قم بتعريف المعلمات والجسم الخاص بالاستدعاء:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    يقوم `params` بتعريف المعلمات التي يتم تمريرها إلى استدعاء واجهة برمجة التطبيقات، حيث يتم تمرير اللغات المصدر والهدف. يقوم هذا الاستدعاء بترجمة النص من اللغة المصدر إلى اللغة الهدف.

    يحتوي `body` على النص المراد ترجمته. هذا عبارة عن مصفوفة، حيث يمكن ترجمة عدة كتل نصية في نفس الاستدعاء.

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
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. قم بإرجاع الخاصية `test` من أول ترجمة من أول عنصر في المصفوفة:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. قم بتحديث الحلقة `while True` لترجمة النص من استدعاء `convert_speech_to_text` من لغة المستخدم إلى لغة الخادم:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    يقوم هذا الكود أيضًا بطباعة النسخة الأصلية والمترجمة من النص إلى وحدة التحكم.

1. قم بتحديث وظيفة `say` لترجمة النص الذي سيتم قوله من لغة الخادم إلى لغة المستخدم:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    يقوم هذا الكود أيضًا بطباعة النسخة الأصلية والمترجمة من النص إلى وحدة التحكم.

1. قم بتشغيل الكود الخاص بك. تأكد من تشغيل تطبيق الوظائف الخاص بك، واطلب مؤقتًا بلغة المستخدم، إما عن طريق التحدث بهذه اللغة بنفسك، أو باستخدام تطبيق ترجمة.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 نظرًا للاختلافات في طرق التعبير عن شيء ما في لغات مختلفة، قد تحصل على ترجمات تختلف قليلاً عن الأمثلة التي قدمتها لـ LUIS. إذا كان هذا هو الحال، أضف المزيد من الأمثلة إلى LUIS، ثم أعد التدريب وأعد نشر النموذج.

> 💁 يمكنك العثور على هذا الكود في [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) المجلد.

😀 لقد كان برنامج المؤقت متعدد اللغات الخاص بك ناجحًا!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.