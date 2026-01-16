<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-26T23:58:36+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "ur"
}
-->
# تقریر کا ترجمہ - ورچوئل IoT ڈیوائس

اس سبق کے اس حصے میں، آپ تقریر کو متن میں تبدیل کرنے کے دوران تقریر کے ترجمے کے لیے کوڈ لکھیں گے، پھر متن کا ترجمہ Translator سروس کے ذریعے کریں گے اور آخر میں ایک بولی جانے والی جواب تیار کریں گے۔

## تقریر کے ترجمے کے لیے اسپیک سروس کا استعمال کریں

اسپیک سروس تقریر کو نہ صرف اسی زبان میں متن میں تبدیل کر سکتی ہے بلکہ آؤٹ پٹ کو دیگر زبانوں میں بھی ترجمہ کر سکتی ہے۔

### کام - اسپیک سروس کے ذریعے تقریر کا ترجمہ کریں

1. `smart-timer` پروجیکٹ کو VS Code میں کھولیں اور یقینی بنائیں کہ ورچوئل ماحول ٹرمینل میں لوڈ ہو چکا ہے۔

1. موجودہ درآمدات کے نیچے درج ذیل درآمدی بیانات شامل کریں:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    یہ کلاسز درآمد کرتا ہے جو تقریر کے ترجمے کے لیے استعمال ہوتی ہیں، اور ایک `requests` لائبریری جو اس سبق کے بعد Translator سروس کو کال کرنے کے لیے استعمال ہوگی۔

1. آپ کے اسمارٹ ٹائمر میں 2 زبانیں سیٹ ہوں گی - وہ زبان جو LUIS کو تربیت دینے کے لیے استعمال ہوئی (یہی زبان صارف سے بات کرنے کے پیغامات بنانے کے لیے بھی استعمال ہوتی ہے)، اور وہ زبان جو صارف بولے گا۔ `language` متغیر کو اپ ڈیٹ کریں تاکہ وہ زبان ہو جو صارف بولے گا، اور ایک نیا متغیر `server_language` شامل کریں جو LUIS کو تربیت دینے کے لیے استعمال ہوئی زبان کے لیے ہو:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` کو اس زبان کے لوکیل نام سے تبدیل کریں جس میں آپ بولیں گے، جیسے `fr-FR` فرانسیسی کے لیے، یا `zn-HK` کینٹونیز کے لیے۔

    `<server language>` کو اس زبان کے لوکیل نام سے تبدیل کریں جو LUIS کو تربیت دینے کے لیے استعمال ہوئی۔

    آپ Microsoft Docs پر [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) میں معاون زبانوں اور ان کے لوکیل ناموں کی فہرست دیکھ سکتے ہیں۔

    > 💁 اگر آپ کئی زبانیں نہیں بولتے تو آپ [Bing Translate](https://www.bing.com/translator) یا [Google Translate](https://translate.google.com) جیسی سروسز استعمال کر سکتے ہیں تاکہ اپنی پسندیدہ زبان سے کسی اور زبان میں ترجمہ کریں۔ یہ سروسز ترجمہ شدہ متن کی آڈیو بھی چلا سکتی ہیں۔ یاد رکھیں کہ اسپیک ریکگنائزر آپ کے ڈیوائس سے کچھ آڈیو آؤٹ پٹ کو نظر انداز کر سکتا ہے، اس لیے آپ کو ترجمہ شدہ متن چلانے کے لیے اضافی ڈیوائس کی ضرورت ہو سکتی ہے۔
    >
    > مثال کے طور پر، اگر آپ نے LUIS کو انگریزی میں تربیت دی ہے لیکن صارف کی زبان کے طور پر فرانسیسی استعمال کرنا چاہتے ہیں، تو آپ جملے جیسے "set a 2 minute and 27 second timer" کو Bing Translate کے ذریعے انگریزی سے فرانسیسی میں ترجمہ کر سکتے ہیں، پھر **Listen translation** بٹن استعمال کر کے ترجمہ کو اپنے مائیکروفون میں بول سکتے ہیں۔
    >
    > ![Bing Translate پر Listen translation بٹن](../../../../../translated_images/ur/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `recognizer_config` اور `recognizer` کے اعلانات کو درج ذیل سے تبدیل کریں:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    یہ ایک ترجمہ کنفیگریشن بناتا ہے تاکہ صارف کی زبان میں تقریر کو پہچانا جا سکے، اور صارف اور سرور زبان میں ترجمے بنائے جا سکیں۔ پھر یہ اس کنفیگریشن کو استعمال کر کے ایک ترجمہ ریکگنائزر بناتا ہے - ایک اسپیک ریکگنائزر جو تقریر کی پہچان کے آؤٹ پٹ کو کئی زبانوں میں ترجمہ کر سکتا ہے۔

    > 💁 اصل زبان کو `target_languages` میں مخصوص کرنا ضروری ہے، ورنہ آپ کو کوئی ترجمہ نہیں ملے گا۔

1. `recognized` فنکشن کو اپ ڈیٹ کریں، اور فنکشن کے تمام مواد کو درج ذیل سے تبدیل کریں:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    یہ کوڈ چیک کرتا ہے کہ آیا پہچان کا ایونٹ تقریر کے ترجمے کی وجہ سے فائر ہوا تھا (یہ ایونٹ دیگر مواقع پر بھی فائر ہو سکتا ہے، جیسے جب تقریر پہچانی گئی ہو لیکن ترجمہ نہ ہوا ہو)۔ اگر تقریر کا ترجمہ ہوا ہو، تو یہ `args.result.translations` ڈکشنری میں وہ ترجمہ تلاش کرتا ہے جو سرور زبان سے میل کھاتا ہو۔

    `args.result.translations` ڈکشنری لوکیل سیٹنگ کے پورے نام کے بجائے زبان کے حصے پر مبنی ہوتی ہے۔ مثال کے طور پر، اگر آپ فرانسیسی کے لیے `fr-FR` میں ترجمہ کی درخواست کرتے ہیں، تو ڈکشنری میں `fr` کے لیے ایک اندراج ہوگا، نہ کہ `fr-FR`۔

    ترجمہ شدہ متن پھر IoT Hub کو بھیجا جاتا ہے۔

1. اس کوڈ کو چلائیں تاکہ ترجمے کی جانچ کریں۔ یقینی بنائیں کہ آپ کی فنکشن ایپ چل رہی ہے، اور صارف کی زبان میں ٹائمر کی درخواست کریں، چاہے وہ زبان خود بول کر یا ترجمہ ایپ استعمال کر کے۔

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Translator سروس کے ذریعے متن کا ترجمہ کریں

اسپیک سروس متن کو دوبارہ تقریر میں ترجمہ کرنے کی حمایت نہیں کرتی، اس کے بجائے آپ Translator سروس استعمال کر سکتے ہیں تاکہ متن کا ترجمہ کریں۔ اس سروس میں ایک REST API ہے جسے آپ متن کے ترجمے کے لیے استعمال کر سکتے ہیں۔

### کام - Translator ریسورس کے ذریعے متن کا ترجمہ کریں

1. `speech_api_key` کے نیچے Translator API کلید شامل کریں:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` کو اپنے Translator سروس ریسورس کے API کلید سے تبدیل کریں۔

1. `say` فنکشن کے اوپر ایک `translate_text` فنکشن تعریف کریں جو متن کو سرور زبان سے صارف زبان میں ترجمہ کرے گا:

    ```python
    def translate_text(text):
    ```

1. اس فنکشن کے اندر، REST API کال کے لیے URL اور ہیڈرز تعریف کریں:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    اس API کا URL مقام مخصوص نہیں ہے، بلکہ مقام کو ہیڈر کے طور پر پاس کیا جاتا ہے۔ API کلید براہ راست استعمال ہوتی ہے، اس لیے اسپیک سروس کے برعکس ٹوکن جاری کرنے والے API سے ایکسیس ٹوکن حاصل کرنے کی ضرورت نہیں ہے۔

1. اس کے نیچے کال کے پیرامیٹرز اور باڈی تعریف کریں:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API کال کے پیرامیٹرز کو تعریف کرتا ہے، جس میں `from` اور `to` زبانیں پاس کی جاتی ہیں۔ یہ کال `from` زبان میں متن کو `to` زبان میں ترجمہ کرے گی۔

    `body` ترجمہ کرنے کے لیے متن کو رکھتا ہے۔ یہ ایک array ہے، کیونکہ ایک ہی کال میں کئی متن کے بلاکس کا ترجمہ کیا جا سکتا ہے۔

1. REST API کو کال کریں، اور جواب حاصل کریں:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    جواب جو واپس آتا ہے وہ ایک JSON array ہے، جس میں ایک آئٹم ہوتا ہے جو ترجمے رکھتا ہے۔ اس آئٹم میں ان تمام آئٹمز کے ترجمے کے لیے ایک array ہوتا ہے جو باڈی میں پاس کیے گئے تھے۔

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

1. array میں پہلے آئٹم سے پہلے ترجمے کے `text` پراپرٹی کو واپس کریں:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `say` فنکشن کو اپ ڈیٹ کریں تاکہ SSML تیار کرنے سے پہلے کہنے کے لیے متن کا ترجمہ کریں:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    یہ کوڈ اصل اور ترجمہ شدہ متن کو کنسول میں بھی پرنٹ کرتا ہے۔

1. اپنا کوڈ چلائیں۔ یقینی بنائیں کہ آپ کی فنکشن ایپ چل رہی ہے، اور صارف کی زبان میں ٹائمر کی درخواست کریں، چاہے وہ زبان خود بول کر یا ترجمہ ایپ استعمال کر کے۔

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

    > 💁 مختلف زبانوں میں کچھ کہنے کے مختلف طریقوں کی وجہ سے، آپ کو ترجمے مل سکتے ہیں جو LUIS کو دیے گئے مثالوں سے تھوڑا مختلف ہوں۔ اگر ایسا ہو، تو LUIS میں مزید مثالیں شامل کریں، دوبارہ تربیت دیں اور ماڈل کو دوبارہ شائع کریں۔

> 💁 آپ اس کوڈ کو [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا کثیرالسان ٹائمر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔