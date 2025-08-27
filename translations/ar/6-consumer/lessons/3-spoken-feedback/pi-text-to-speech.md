<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T00:12:40+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "ar"
}
-->
# تحويل النص إلى كلام - Raspberry Pi

في هذا الجزء من الدرس، ستقوم بكتابة كود لتحويل النص إلى كلام باستخدام خدمة الكلام.

## تحويل النص إلى كلام باستخدام خدمة الكلام

يمكن إرسال النص إلى خدمة الكلام باستخدام واجهة REST API للحصول على الكلام كملف صوتي يمكن تشغيله على جهاز إنترنت الأشياء الخاص بك. عند طلب الكلام، تحتاج إلى تحديد الصوت الذي سيتم استخدامه، حيث يمكن توليد الكلام باستخدام مجموعة متنوعة من الأصوات المختلفة.

كل لغة تدعم مجموعة من الأصوات المختلفة، ويمكنك إرسال طلب REST إلى خدمة الكلام للحصول على قائمة الأصوات المدعومة لكل لغة.

### المهمة - الحصول على صوت

1. افتح مشروع `smart-timer` في VS Code.

1. أضف الكود التالي فوق دالة `say` لطلب قائمة الأصوات للغة معينة:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    يقوم هذا الكود بتعريف دالة تسمى `get_voice` تستخدم خدمة الكلام للحصول على قائمة الأصوات. ثم يعثر على أول صوت يتطابق مع اللغة المستخدمة.

    يتم استدعاء هذه الدالة لتخزين أول صوت، ويتم طباعة اسم الصوت إلى وحدة التحكم. يمكن طلب هذا الصوت مرة واحدة واستخدام القيمة لكل استدعاء لتحويل النص إلى كلام.

    > 💁 يمكنك الحصول على القائمة الكاملة للأصوات المدعومة من [وثائق دعم اللغة والصوت على Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). إذا كنت ترغب في استخدام صوت معين، يمكنك إزالة هذه الدالة وتحديد الصوت يدويًا باستخدام اسم الصوت من هذه الوثائق. على سبيل المثال:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### المهمة - تحويل النص إلى كلام

1. أسفل هذا، قم بتعريف ثابت لتنسيق الصوت الذي سيتم استرداده من خدمات الكلام. عند طلب الصوت، يمكنك القيام بذلك بمجموعة من التنسيقات المختلفة.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    يعتمد التنسيق الذي يمكنك استخدامه على جهازك. إذا واجهت أخطاء `Invalid sample rate` عند تشغيل الصوت، قم بتغيير هذا إلى قيمة أخرى. يمكنك العثور على قائمة القيم المدعومة في [وثائق REST API لتحويل النص إلى كلام على Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). ستحتاج إلى استخدام صوت بتنسيق `riff`، والقيم التي يمكنك تجربتها هي `riff-16khz-16bit-mono-pcm`، `riff-24khz-16bit-mono-pcm` و `riff-48khz-16bit-mono-pcm`.

1. أسفل هذا، قم بتعريف دالة تسمى `get_speech` لتحويل النص إلى كلام باستخدام REST API لخدمة الكلام:

    ```python
    def get_speech(text):
    ```

1. في دالة `get_speech`، قم بتعريف عنوان URL الذي سيتم استدعاؤه والرؤوس التي سيتم تمريرها:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    يتم هنا إعداد الرؤوس لاستخدام رمز وصول تم إنشاؤه، وتحديد المحتوى كـ SSML وتحديد تنسيق الصوت المطلوب.

1. أسفل هذا، قم بتعريف SSML الذي سيتم إرساله إلى REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    يقوم هذا SSML بتحديد اللغة والصوت المستخدم، بالإضافة إلى النص الذي سيتم تحويله.

1. أخيرًا، أضف كودًا في هذه الدالة لإجراء طلب REST وإرجاع البيانات الصوتية الثنائية:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### المهمة - تشغيل الصوت

1. أسفل دالة `get_speech`، قم بتعريف دالة جديدة لتشغيل الصوت الذي تم إرجاعه من استدعاء REST API:

    ```python
    def play_speech(speech):
    ```

1. الصوت `speech` الذي يتم تمريره إلى هذه الدالة سيكون البيانات الصوتية الثنائية التي تم إرجاعها من REST API. استخدم الكود التالي لفتح هذا كملف wave وتمريره إلى PyAudio لتشغيل الصوت:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    يستخدم هذا الكود تدفق PyAudio، تمامًا مثل التقاط الصوت. الفرق هنا هو أن التدفق يتم إعداده كتدفق إخراج، ويتم قراءة البيانات من البيانات الصوتية ودفعها إلى التدفق.

    بدلاً من تحديد تفاصيل التدفق مثل معدل العينة يدويًا، يتم قراءتها من البيانات الصوتية.

1. استبدل محتويات دالة `say` بالتالي:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    يقوم هذا الكود بتحويل النص إلى كلام كبيانات صوتية ثنائية، ثم يقوم بتشغيل الصوت.

1. قم بتشغيل التطبيق، وتأكد من تشغيل تطبيق الوظيفة أيضًا. قم بضبط بعض المؤقتات، وستسمع استجابة صوتية تخبرك بأنه تم ضبط المؤقت الخاص بك، ثم استجابة صوتية أخرى عند انتهاء المؤقت.

    إذا واجهت أخطاء `Invalid sample rate`، قم بتغيير `playback_format` كما هو موضح أعلاه.

> 💁 يمكنك العثور على هذا الكود في [المجلد code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 لقد كان برنامج المؤقت الخاص بك ناجحًا!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.