# ترجمة الكلام - Wio Terminal

في هذا الجزء من الدرس، ستكتب كودًا لترجمة النص باستخدام خدمة الترجمة.

## تحويل النص إلى كلام باستخدام خدمة الترجمة

واجهة برمجة التطبيقات REST الخاصة بخدمة الكلام لا تدعم الترجمات المباشرة. بدلاً من ذلك، يمكنك استخدام خدمة الترجمة لترجمة النص الناتج عن خدمة تحويل الكلام إلى نص، وكذلك النص الخاص بالرد المنطوق. تحتوي هذه الخدمة على واجهة برمجة تطبيقات REST يمكنك استخدامها لترجمة النص، ولكن لتسهيل الاستخدام سيتم تغليفها في مشغل HTTP آخر داخل تطبيق الوظائف الخاص بك.

### المهمة - إنشاء وظيفة بدون خادم لترجمة النص

1. افتح مشروعك `smart-timer-trigger` في VS Code، وافتح الطرفية مع التأكد من تنشيط البيئة الافتراضية. إذا لم تكن نشطة، قم بإنهاء الطرفية وإعادة إنشائها.

1. افتح ملف `local.settings.json` وأضف إعدادات مفتاح API الخاص بخدمة الترجمة والموقع:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    استبدل `<key>` بمفتاح API الخاص بمورد خدمة الترجمة. استبدل `<location>` بالموقع الذي استخدمته عند إنشاء مورد خدمة الترجمة.

1. أضف مشغل HTTP جديد إلى هذا التطبيق يسمى `translate-text` باستخدام الأمر التالي داخل الطرفية في VS Code في المجلد الجذر لمشروع تطبيق الوظائف:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    سيقوم هذا بإنشاء مشغل HTTP يسمى `translate-text`.

1. استبدل محتويات ملف `__init__.py` في مجلد `translate-text` بما يلي:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    يقوم هذا الكود باستخراج النص واللغات من طلب HTTP. ثم يقوم بإجراء طلب إلى واجهة برمجة التطبيقات REST الخاصة بخدمة الترجمة، مع تمرير اللغات كمعلمات للعنوان والنص المراد ترجمته كجسم الطلب. وأخيرًا، يتم إرجاع الترجمة.

1. قم بتشغيل تطبيق الوظائف الخاص بك محليًا. يمكنك بعد ذلك استدعاء هذا باستخدام أداة مثل curl بنفس الطريقة التي اختبرت بها مشغل HTTP الخاص بـ `text-to-timer`. تأكد من تمرير النص المراد ترجمته واللغات كجسم JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    يترجم هذا المثال *Définir une minuterie de 30 secondes* من الفرنسية إلى الإنجليزية الأمريكية. وسيعيد *Set a 30-second timer*.

> 💁 يمكنك العثور على هذا الكود في مجلد [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### المهمة - استخدام وظيفة الترجمة لترجمة النص

1. افتح مشروع `smart-timer` في VS Code إذا لم يكن مفتوحًا بالفعل.

1. سيكون للمؤقت الذكي الخاص بك لغتان محددتان - لغة الخادم التي تم استخدامها لتدريب LUIS (تُستخدم نفس اللغة أيضًا لبناء الرسائل للتحدث مع المستخدم)، ولغة المستخدم المنطوقة. قم بتحديث الثابت `LANGUAGE` في ملف الرأس `config.h` لتكون اللغة التي سيتم التحدث بها من قبل المستخدم، وأضف ثابتًا جديدًا يسمى `SERVER_LANGUAGE` للغة المستخدمة لتدريب LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    استبدل `<user language>` باسم المنطقة للغة التي ستتحدث بها، على سبيل المثال `fr-FR` للفرنسية، أو `zn-HK` للكانتونية.

    استبدل `<server language>` باسم المنطقة للغة المستخدمة لتدريب LUIS.

    يمكنك العثور على قائمة باللغات المدعومة وأسماء المناطق الخاصة بها في [وثائق دعم اللغة والصوت على Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 إذا كنت لا تتحدث لغات متعددة، يمكنك استخدام خدمة مثل [Bing Translate](https://www.bing.com/translator) أو [Google Translate](https://translate.google.com) لترجمة النص من لغتك المفضلة إلى لغة أخرى من اختيارك. يمكن لهذه الخدمات تشغيل الصوت للنص المترجم.
    >
    > على سبيل المثال، إذا قمت بتدريب LUIS باللغة الإنجليزية، ولكنك تريد استخدام الفرنسية كلغة المستخدم، يمكنك ترجمة جمل مثل "اضبط مؤقتًا لمدة دقيقتين و27 ثانية" من الإنجليزية إلى الفرنسية باستخدام Bing Translate، ثم استخدام زر **Listen translation** للتحدث بالترجمة إلى الميكروفون الخاص بك.
    >
    > ![زر الاستماع للترجمة على Bing Translate](../../../../../translated_images/ar/bing-translate.348aa796d6efe2a9.webp)

1. أضف مفتاح API الخاص بخدمة الترجمة والموقع أسفل `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    استبدل `<KEY>` بمفتاح API الخاص بمورد خدمة الترجمة. استبدل `<LOCATION>` بالموقع الذي استخدمته عند إنشاء مورد خدمة الترجمة.

1. أضف عنوان URL الخاص بمشغل الترجمة أسفل `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    استبدل `<URL>` بعنوان URL الخاص بمشغل HTTP `translate-text` في تطبيق الوظائف الخاص بك. سيكون هذا هو نفس القيمة لـ `TEXT_TO_TIMER_FUNCTION_URL`، باستثناء أن اسم الوظيفة سيكون `translate-text` بدلاً من `text-to-timer`.

1. أضف ملفًا جديدًا إلى مجلد `src` يسمى `text_translator.h`.

1. يحتوي ملف الرأس الجديد `text_translator.h` على فئة لترجمة النص. أضف ما يلي إلى هذا الملف لإعلان هذه الفئة:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    يعلن هذا عن فئة `TextTranslator`، إلى جانب مثيل لهذه الفئة. تحتوي الفئة على حقل واحد لعميل WiFi.

1. إلى القسم `public` لهذه الفئة، أضف طريقة لترجمة النص:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    تأخذ هذه الطريقة اللغة المراد الترجمة منها، واللغة المراد الترجمة إليها. عند التعامل مع الكلام، سيتم ترجمة الكلام من لغة المستخدم إلى لغة خادم LUIS، وعند إعطاء الردود سيتم الترجمة من لغة خادم LUIS إلى لغة المستخدم.

1. في هذه الطريقة، أضف كودًا لإنشاء جسم JSON يحتوي على النص المراد ترجمته واللغات:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. أسفل هذا، أضف الكود التالي لإرسال الجسم إلى تطبيق الوظائف بدون خادم:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. بعد ذلك، أضف كودًا للحصول على الرد:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. أخيرًا، أضف كودًا لإغلاق الاتصال وإرجاع النص المترجم:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### المهمة - ترجمة الكلام المعترف به والردود

1. افتح ملف `main.cpp`.

1. أضف توجيه تضمين في أعلى الملف لفئة `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. النص الذي يُقال عند ضبط المؤقت أو انتهاء صلاحيته يحتاج إلى ترجمة. للقيام بذلك، أضف ما يلي كأول سطر في وظيفة `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    سيقوم هذا بترجمة النص إلى لغة المستخدم.

1. في وظيفة `processAudio`، يتم استرداد النص من الصوت الملتقط باستخدام الاستدعاء `String text = speechToText.convertSpeechToText();`. بعد هذا الاستدعاء، قم بترجمة النص:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    سيقوم هذا بترجمة النص من لغة المستخدم إلى اللغة المستخدمة على الخادم.

1. قم ببناء هذا الكود، ورفعه إلى Wio Terminal الخاص بك واختبره من خلال المراقب التسلسلي. بمجرد رؤية `Ready` في المراقب التسلسلي، اضغط على زر C (الزر الموجود على الجانب الأيسر، الأقرب إلى مفتاح التشغيل)، وتحدث. تأكد من تشغيل تطبيق الوظائف الخاص بك، واطلب مؤقتًا بلغة المستخدم، إما عن طريق التحدث بتلك اللغة بنفسك، أو باستخدام تطبيق ترجمة.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 يمكنك العثور على هذا الكود في مجلد [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 لقد نجحت في إنشاء برنامج المؤقت متعدد اللغات!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.