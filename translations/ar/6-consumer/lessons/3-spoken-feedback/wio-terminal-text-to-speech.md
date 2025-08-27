<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T00:14:49+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "ar"
}
-->
# تحويل النص إلى كلام - Wio Terminal

في هذا الجزء من الدرس، ستقوم بتحويل النص إلى كلام لتوفير تغذية راجعة صوتية.

## تحويل النص إلى كلام

يمكن استخدام حزمة SDK لخدمات الكلام التي استخدمتها في الدرس السابق لتحويل الكلام إلى نص، لتحويل النص مرة أخرى إلى كلام.

## الحصول على قائمة بالأصوات

عند طلب تحويل النص إلى كلام، تحتاج إلى تحديد الصوت الذي سيتم استخدامه، حيث يمكن إنشاء الكلام باستخدام مجموعة متنوعة من الأصوات المختلفة. يدعم كل لغة مجموعة من الأصوات المختلفة، ويمكنك الحصول على قائمة الأصوات المدعومة لكل لغة من خلال حزمة SDK لخدمات الكلام. هنا تظهر قيود المتحكمات الدقيقة - حيث أن استدعاء الحصول على قائمة الأصوات المدعومة من خدمات تحويل النص إلى كلام ينتج مستند JSON بحجم يزيد عن 77 كيلوبايت، وهو كبير جدًا ليتم معالجته بواسطة Wio Terminal. في وقت كتابة هذا النص، تحتوي القائمة الكاملة على 215 صوتًا، كل منها معرف بمستند JSON مثل التالي:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

هذا JSON خاص بصوت **Aria**، الذي يحتوي على أنماط صوتية متعددة. كل ما تحتاجه عند تحويل النص إلى كلام هو الاسم المختصر، `en-US-AriaNeural`.

بدلاً من تنزيل وفك تشفير هذه القائمة بالكامل على المتحكم الدقيق الخاص بك، ستحتاج إلى كتابة بعض التعليمات البرمجية بدون خادم لاسترداد قائمة الأصوات للغة التي تستخدمها، واستدعاء هذه التعليمات من Wio Terminal الخاص بك. يمكن لشفرتك بعد ذلك اختيار صوت مناسب من القائمة، مثل أول صوت تجده.

### المهمة - إنشاء وظيفة بدون خادم للحصول على قائمة الأصوات

1. افتح مشروعك `smart-timer-trigger` في VS Code، وافتح الطرفية مع التأكد من تفعيل البيئة الافتراضية. إذا لم تكن مفعلة، قم بإيقاف وإعادة إنشاء الطرفية.

1. افتح ملف `local.settings.json` وأضف الإعدادات لمفتاح API الخاص بخدمة الكلام والموقع:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    استبدل `<key>` بمفتاح API الخاص بمورد خدمة الكلام. استبدل `<location>` بالموقع الذي استخدمته عند إنشاء مورد خدمة الكلام.

1. أضف مشغل HTTP جديد لهذا التطبيق يسمى `get-voices` باستخدام الأمر التالي من داخل طرفية VS Code في المجلد الجذر لمشروع تطبيق الوظائف:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    سيؤدي هذا إلى إنشاء مشغل HTTP يسمى `get-voices`.

1. استبدل محتويات ملف `__init__.py` في مجلد `get-voices` بما يلي:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    تقوم هذه الشفرة بإجراء طلب HTTP إلى نقطة النهاية للحصول على الأصوات. قائمة الأصوات هذه عبارة عن كتلة JSON كبيرة تحتوي على أصوات لجميع اللغات، لذلك يتم تصفية الأصوات للغة الممررة في نص الطلب، ثم يتم استخراج الاسم المختصر وإعادته كقائمة JSON. الاسم المختصر هو القيمة المطلوبة لتحويل النص إلى كلام، لذلك يتم إرجاع هذه القيمة فقط.

    > 💁 يمكنك تغيير الفلتر حسب الحاجة لاختيار الأصوات التي تريدها فقط.

    يقلل هذا من حجم البيانات من 77 كيلوبايت (في وقت كتابة هذا النص) إلى مستند JSON أصغر بكثير. على سبيل المثال، بالنسبة للأصوات الأمريكية، يكون الحجم 408 بايت.

1. قم بتشغيل تطبيق الوظائف الخاص بك محليًا. يمكنك بعد ذلك استدعاء هذا باستخدام أداة مثل curl بنفس الطريقة التي اختبرت بها مشغل HTTP `text-to-timer`. تأكد من تمرير لغتك كنص JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    استبدل `<language>` بلغتك، مثل `en-GB` أو `zh-CN`.

> 💁 يمكنك العثور على هذه الشفرة في مجلد [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### المهمة - استرداد الصوت من Wio Terminal الخاص بك

1. افتح مشروع `smart-timer` في VS Code إذا لم يكن مفتوحًا بالفعل.

1. افتح ملف الرأس `config.h` وأضف عنوان URL لتطبيق الوظائف الخاص بك:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    استبدل `<URL>` بعنوان URL لمشغل HTTP `get-voices` في تطبيق الوظائف الخاص بك. سيكون هذا هو نفس القيمة لـ `TEXT_TO_TIMER_FUNCTION_URL`، باستثناء أن اسم الوظيفة سيكون `get-voices` بدلاً من `text-to-timer`.

1. أنشئ ملفًا جديدًا في مجلد `src` يسمى `text_to_speech.h`. سيتم استخدام هذا لتعريف فئة لتحويل النص إلى كلام.

1. أضف توجيهات التضمين التالية إلى أعلى ملف `text_to_speech.h` الجديد:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. أضف الشفرة التالية أسفل ذلك لإعلان فئة `TextToSpeech`، مع مثيل يمكن استخدامه في باقي التطبيق:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. لاستدعاء تطبيق الوظائف الخاص بك، تحتاج إلى إعلان عميل WiFi. أضف ما يلي إلى القسم `private` من الفئة:

    ```cpp
    WiFiClient _client;
    ```

1. في القسم `private`، أضف حقلًا للصوت المحدد:

    ```cpp
    String _voice;
    ```

1. إلى القسم `public`، أضف وظيفة `init` التي ستقوم بالحصول على أول صوت:

    ```cpp
    void init()
    {
    }
    ```

1. للحصول على الأصوات، يجب إرسال مستند JSON إلى تطبيق الوظائف مع اللغة. أضف الشفرة التالية إلى وظيفة `init` لإنشاء هذا المستند:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. بعد ذلك، أنشئ `HTTPClient`، ثم استخدمه لاستدعاء تطبيق الوظائف للحصول على الأصوات، مع إرسال مستند JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. أسفل ذلك، أضف شفرة للتحقق من رمز الاستجابة، وإذا كان 200 (نجاح)، فاستخرج قائمة الأصوات، واسترد أول صوت من القائمة:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. بعد ذلك، قم بإنهاء اتصال عميل HTTP:

    ```cpp
    httpClient.end();
    ```

1. افتح ملف `main.cpp`، وأضف توجيه التضمين التالي في الأعلى لتضمين ملف الرأس الجديد:

    ```cpp
    #include "text_to_speech.h"
    ```

1. في وظيفة `setup`، أسفل استدعاء `speechToText.init();`، أضف ما يلي لتهيئة فئة `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. قم ببناء هذه الشفرة، وارفعها إلى Wio Terminal الخاص بك واختبرها من خلال المراقب التسلسلي. تأكد من تشغيل تطبيق الوظائف الخاص بك.

    سترى قائمة الأصوات المتاحة التي تم إرجاعها من تطبيق الوظائف، إلى جانب الصوت المحدد.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## تحويل النص إلى كلام

بمجرد أن يكون لديك صوت للاستخدام، يمكن استخدامه لتحويل النص إلى كلام. تنطبق نفس قيود الذاكرة مع الأصوات أيضًا عند تحويل النص إلى كلام، لذلك ستحتاج إلى كتابة الكلام على بطاقة SD ليتم تشغيله عبر ReSpeaker.

> 💁 في الدروس السابقة في هذا المشروع، استخدمت ذاكرة الفلاش لتخزين الكلام الملتقط من الميكروفون. يستخدم هذا الدرس بطاقة SD لأنه من الأسهل تشغيل الصوت منها باستخدام مكتبات الصوت من Seeed.

هناك أيضًا قيد آخر يجب مراعاته، وهو البيانات الصوتية المتاحة من خدمة الكلام، والتنسيقات التي يدعمها Wio Terminal. على عكس أجهزة الكمبيوتر الكاملة، يمكن أن تكون مكتبات الصوت للمتحكمات الدقيقة محدودة جدًا في التنسيقات الصوتية التي تدعمها. على سبيل المثال، مكتبة Seeed Arduino Audio التي يمكنها تشغيل الصوت عبر ReSpeaker تدعم فقط الصوت بمعدل عينة 44.1 كيلوهرتز. توفر خدمات Azure للكلام الصوت بعدة تنسيقات، ولكن لا يستخدم أي منها هذا معدل العينة، حيث توفر فقط 8 كيلوهرتز، 16 كيلوهرتز، 24 كيلوهرتز و48 كيلوهرتز. هذا يعني أن الصوت يحتاج إلى إعادة أخذ عينات إلى 44.1 كيلوهرتز، وهو أمر يتطلب موارد أكثر مما يمتلكه Wio Terminal، خاصة الذاكرة.

عند الحاجة إلى معالجة البيانات مثل هذه، من الأفضل غالبًا استخدام التعليمات البرمجية بدون خادم، خاصة إذا كانت البيانات مستمدة عبر استدعاء ويب. يمكن لـ Wio Terminal استدعاء وظيفة بدون خادم، وتمرير النص للتحويل، ويمكن للوظيفة بدون خادم استدعاء خدمة الكلام لتحويل النص إلى كلام، وكذلك إعادة أخذ عينات الصوت إلى معدل العينة المطلوب. يمكنها بعد ذلك إرجاع الصوت بالشكل الذي يحتاجه Wio Terminal ليتم تخزينه على بطاقة SD وتشغيله عبر ReSpeaker.

### المهمة - إنشاء وظيفة بدون خادم لتحويل النص إلى كلام

1. افتح مشروعك `smart-timer-trigger` في VS Code، وافتح الطرفية مع التأكد من تفعيل البيئة الافتراضية. إذا لم تكن مفعلة، قم بإيقاف وإعادة إنشاء الطرفية.

1. أضف مشغل HTTP جديد لهذا التطبيق يسمى `text-to-speech` باستخدام الأمر التالي من داخل طرفية VS Code في المجلد الجذر لمشروع تطبيق الوظائف:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    سيؤدي هذا إلى إنشاء مشغل HTTP يسمى `text-to-speech`.

1. تحتوي حزمة Pip [librosa](https://librosa.org) على وظائف لإعادة أخذ عينات الصوت، لذا أضفها إلى ملف `requirements.txt`:

    ```sh
    librosa
    ```

    بمجرد إضافة ذلك، قم بتثبيت حزم Pip باستخدام الأمر التالي من طرفية VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ إذا كنت تستخدم Linux، بما في ذلك Raspberry Pi OS، قد تحتاج إلى تثبيت `libsndfile` باستخدام الأمر التالي:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. لتحويل النص إلى كلام، لا يمكنك استخدام مفتاح API الخاص بالكلام مباشرة، بدلاً من ذلك تحتاج إلى طلب رمز وصول، باستخدام مفتاح API للمصادقة على طلب رمز الوصول. افتح ملف `__init__.py` من مجلد `text-to-speech` واستبدل كل الشفرة فيه بما يلي:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    هذا يحدد ثوابت للموقع ومفتاح الكلام الذي سيتم قراءته من الإعدادات. ثم يحدد وظيفة `get_access_token` التي ستسترد رمز الوصول لخدمة الكلام.

1. أسفل هذه الشفرة، أضف ما يلي:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    هذا يحدد مشغل HTTP الذي يحول النص إلى كلام. يستخرج النص للتحويل، اللغة والصوت من نص JSON المرسل إلى الطلب، يبني بعض SSML لطلب الكلام، ثم يستدعي REST API المناسب مع المصادقة باستخدام رمز الوصول. يعيد استدعاء REST API هذا الصوت مشفرًا كملف WAV أحادي 16 بت، 48 كيلوهرتز، كما هو محدد بواسطة قيمة `playback_format`، التي يتم إرسالها إلى استدعاء REST API.

    يتم بعد ذلك إعادة أخذ عينات هذا الصوت بواسطة `librosa` من معدل عينة 48 كيلوهرتز إلى معدل عينة 44.1 كيلوهرتز، ثم يتم حفظ هذا الصوت في مخزن ثنائي يتم إرجاعه بعد ذلك.

1. قم بتشغيل تطبيق الوظائف الخاص بك محليًا، أو قم بنشره في السحابة. يمكنك بعد ذلك استدعاء هذا باستخدام أداة مثل curl بنفس الطريقة التي اختبرت بها مشغل HTTP `text-to-timer`. تأكد من تمرير اللغة، الصوت والنص كنص JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    استبدل `<language>` بلغتك، مثل `en-GB` أو `zh-CN`. استبدل `<voice>` بالصوت الذي تريد استخدامه. استبدل `<text>` بالنص الذي تريد تحويله إلى كلام. يمكنك حفظ الإخراج إلى ملف وتشغيله باستخدام أي مشغل صوت يمكنه تشغيل ملفات WAV.

    على سبيل المثال، لتحويل "Hello" إلى كلام باستخدام الإنجليزية الأمريكية مع صوت Jenny Neural، مع تشغيل تطبيق الوظائف محليًا، يمكنك استخدام أمر curl التالي:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    سيحفظ هذا الصوت في `hello.wav` في الدليل الحالي.

> 💁 يمكنك العثور على هذه الشفرة في مجلد [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### المهمة - استرداد الكلام من Wio Terminal الخاص بك

1. افتح مشروع `smart-timer` في VS Code إذا لم يكن مفتوحًا بالفعل.

1. افتح ملف الرأس `config.h` وأضف عنوان URL لتطبيق الوظائف الخاص بك:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    استبدل `<URL>` بعنوان URL لمشغل HTTP `text-to-speech` في تطبيق الوظائف الخاص بك. سيكون هذا هو نفس القيمة لـ `TEXT_TO_TIMER_FUNCTION_URL`، باستثناء أن اسم الوظيفة سيكون `text-to-speech` بدلاً من `text-to-timer`.

1. افتح ملف الرأس `text_to_speech.h`، وأضف الطريقة التالية إلى القسم `public` من فئة `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. إلى طريقة `convertTextToSpeech`، أضف الشفرة التالية لإنشاء JSON لإرساله إلى تطبيق الوظائف:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    يكتب هذا اللغة، الصوت والنص إلى مستند JSON، ثم يقوم بتسلسله إلى سلسلة.

1. أسفل ذلك، أضف الشفرة التالية لاستدعاء تطبيق الوظائف:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    ينشئ هذا `HTTPClient`، ثم يقوم بإجراء طلب POST باستخدام مستند JSON إلى مشغل HTTP لتحويل النص إلى كلام.

1. إذا نجح الاستدعاء، يمكن تدفق البيانات الثنائية الخام التي تم إرجاعها من استدعاء تطبيق الوظائف إلى ملف على بطاقة SD. أضف الشفرة التالية للقيام بذلك:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    تتحقق هذه الشفرة من الاستجابة، وإذا كانت 200 (نجاح)، يتم تدفق البيانات الثنائية إلى ملف في جذر بطاقة SD يسمى `SPEECH.WAV`.

1. في نهاية هذه الطريقة، أغلق اتصال HTTP:

    ```cpp
    httpClient.end();
    ```

1. يمكن الآن تحويل النص الذي سيتم نطقه إلى صوت. في ملف `main.cpp`، أضف السطر التالي إلى نهاية وظيفة `say` لتحويل النص إلى صوت:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### المهمة - تشغيل الصوت من جهاز Wio Terminal الخاص بك

**قريبًا**

## نشر تطبيق الوظائف الخاص بك إلى السحابة

السبب وراء تشغيل تطبيق الوظائف محليًا هو أن حزمة `librosa` الخاصة بـ Pip على نظام Linux تعتمد على مكتبة غير مثبتة بشكل افتراضي، وستحتاج إلى تثبيتها قبل أن يتمكن تطبيق الوظائف من العمل. تطبيقات الوظائف هي بدون خوادم - لا توجد خوادم يمكنك إدارتها بنفسك، لذا لا توجد طريقة لتثبيت هذه المكتبة مسبقًا.

الطريقة للقيام بذلك هي نشر تطبيق الوظائف الخاص بك باستخدام حاوية Docker. يتم نشر هذه الحاوية بواسطة السحابة كلما احتاجت إلى تشغيل نسخة جديدة من تطبيق الوظائف الخاص بك (مثل عندما يتجاوز الطلب الموارد المتاحة، أو إذا لم يتم استخدام تطبيق الوظائف لفترة وتم إغلاقه).

يمكنك العثور على التعليمات لإعداد تطبيق الوظائف والنشر عبر Docker في [وثائق إنشاء وظيفة على Linux باستخدام صورة مخصصة على Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

بمجرد نشر هذا، يمكنك تعديل كود Wio Terminal الخاص بك للوصول إلى هذه الوظيفة:

1. أضف شهادة Azure Functions إلى `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. قم بتغيير جميع الإشارات إلى `<WiFiClient.h>` إلى `<WiFiClientSecure.h>`.

1. قم بتغيير جميع الحقول من `WiFiClient` إلى `WiFiClientSecure`.

1. في كل فئة تحتوي على حقل `WiFiClientSecure`، أضف مُنشئًا وقم بتعيين الشهادة في هذا المُنشئ:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.