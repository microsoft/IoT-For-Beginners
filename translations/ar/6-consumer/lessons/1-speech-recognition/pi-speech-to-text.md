<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T00:32:32+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "ar"
}
-->
# تحويل الكلام إلى نص - Raspberry Pi

في هذا الجزء من الدرس، ستكتب كودًا لتحويل الكلام في الصوت الملتقط إلى نص باستخدام خدمة التعرف على الكلام.

## إرسال الصوت إلى خدمة التعرف على الكلام

يمكن إرسال الصوت إلى خدمة التعرف على الكلام باستخدام واجهة REST API. لاستخدام الخدمة، تحتاج أولاً إلى طلب رمز وصول (Access Token)، ثم استخدام هذا الرمز للوصول إلى واجهة REST API. تنتهي صلاحية رموز الوصول بعد 10 دقائق، لذا يجب أن يطلب الكود الخاص بك الرموز بشكل منتظم لضمان أنها دائمًا محدثة.

### المهمة - الحصول على رمز وصول

1. افتح مشروع `smart-timer` على جهاز Raspberry Pi الخاص بك.

1. قم بإزالة وظيفة `play_audio`. لم تعد هذه الوظيفة ضرورية لأنك لا تريد أن يكرر المؤقت الذكي ما قلته.

1. أضف الاستيراد التالي إلى أعلى ملف `app.py`:

    ```python
    import requests
    ```

1. أضف الكود التالي فوق حلقة `while True` لتحديد بعض الإعدادات لخدمة التعرف على الكلام:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    استبدل `<key>` بمفتاح API الخاص بمورد خدمة التعرف على الكلام. استبدل `<location>` بالموقع الذي استخدمته عند إنشاء مورد خدمة التعرف على الكلام.

    استبدل `<language>` باسم اللغة التي ستتحدث بها، على سبيل المثال `en-GB` للإنجليزية، أو `zn-HK` للكانتونية. يمكنك العثور على قائمة باللغات المدعومة وأسمائها في [وثائق دعم اللغة والصوت على موقع Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. أسفل ذلك، أضف الوظيفة التالية للحصول على رمز الوصول:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    تستدعي هذه الوظيفة نقطة نهاية لإصدار الرموز، مع تمرير مفتاح API كعنوان. تعيد هذه الاستدعاء رمز وصول يمكن استخدامه لاستدعاء خدمات التعرف على الكلام.

1. أسفل ذلك، قم بتعريف وظيفة لتحويل الكلام في الصوت الملتقط إلى نص باستخدام REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. داخل هذه الوظيفة، قم بإعداد عنوان URL الخاص بـ REST API والعناوين:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    يقوم هذا الكود ببناء عنوان URL باستخدام موقع مورد خدمات التعرف على الكلام. ثم يملأ العناوين برمز الوصول من وظيفة `get_access_token`، بالإضافة إلى معدل العينة المستخدم لالتقاط الصوت. وأخيرًا، يحدد بعض المعلمات التي يتم تمريرها مع عنوان URL والتي تحتوي على اللغة في الصوت.

1. أسفل ذلك، أضف الكود التالي لاستدعاء REST API واسترجاع النص:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    يستدعي هذا الكود عنوان URL ويفك تشفير القيمة JSON التي تأتي في الاستجابة. يشير الحقل `RecognitionStatus` في الاستجابة إلى ما إذا كان الاستدعاء قد تمكن من استخراج الكلام وتحويله إلى نص بنجاح، وإذا كانت القيمة `Success`، يتم إرجاع النص من الوظيفة، وإلا يتم إرجاع سلسلة فارغة.

1. فوق حلقة `while True:`، قم بتعريف وظيفة لمعالجة النص الذي تم إرجاعه من خدمة تحويل الكلام إلى نص. ستقوم هذه الوظيفة فقط بطباعة النص إلى وحدة التحكم في الوقت الحالي.

    ```python
    def process_text(text):
        print(text)
    ```

1. أخيرًا، استبدل استدعاء `play_audio` في حلقة `while True` باستدعاء وظيفة `convert_speech_to_text`، مع تمرير النص إلى وظيفة `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. قم بتشغيل الكود. اضغط على الزر وتحدث في الميكروفون. حرر الزر عند الانتهاء، وسيتم تحويل الصوت إلى نص وطباعة النص إلى وحدة التحكم.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    جرب أنواعًا مختلفة من الجمل، بالإضافة إلى الجمل التي تحتوي على كلمات تبدو متشابهة ولكن لها معانٍ مختلفة. على سبيل المثال، إذا كنت تتحدث باللغة الإنجليزية، قل "I want to buy two bananas and an apple too"، ولاحظ كيف سيتم استخدام الكلمات الصحيحة "to"، "two"، و"too" بناءً على سياق الكلمة، وليس فقط صوتها.

> 💁 يمكنك العثور على هذا الكود في المجلد [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 لقد نجح برنامج تحويل الكلام إلى نص الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.