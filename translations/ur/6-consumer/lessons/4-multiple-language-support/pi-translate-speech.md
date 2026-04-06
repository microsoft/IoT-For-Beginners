# تقریر کا ترجمہ - راسپبیری پائی

اس سبق کے اس حصے میں، آپ مترجم سروس کا استعمال کرتے ہوئے متن کا ترجمہ کرنے کے لیے کوڈ لکھیں گے۔

## مترجم سروس کا استعمال کرتے ہوئے متن کو تقریر میں تبدیل کریں

تقریر سروس REST API براہ راست ترجمے کی حمایت نہیں کرتی، لیکن آپ تقریر سے متن سروس کے ذریعے تیار کردہ متن اور بولے گئے جواب کے متن کا ترجمہ کرنے کے لیے مترجم سروس استعمال کر سکتے ہیں۔ اس سروس میں ایک REST API موجود ہے جسے آپ متن کا ترجمہ کرنے کے لیے استعمال کر سکتے ہیں۔

### کام - مترجم وسائل کا استعمال کرتے ہوئے متن کا ترجمہ کریں

1. آپ کے اسمارٹ ٹائمر میں 2 زبانیں سیٹ ہوں گی - وہ زبان جو LUIS کو تربیت دینے کے لیے استعمال کی گئی (یہی زبان صارف سے بات کرنے کے پیغامات بنانے کے لیے بھی استعمال ہوتی ہے)، اور وہ زبان جو صارف بولتا ہے۔ `language` ویری ایبل کو اپ ڈیٹ کریں تاکہ وہ زبان ہو جو صارف بولے گا، اور ایک نیا ویری ایبل `server_language` کے نام سے شامل کریں جو LUIS کو تربیت دینے کے لیے استعمال ہونے والی زبان کو ظاہر کرے:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` کو اس زبان کے لوکیل نام سے تبدیل کریں جس میں آپ بات کریں گے، مثلاً فرانسیسی کے لیے `fr-FR` یا کینٹونیز کے لیے `zn-HK`۔

    `<server language>` کو اس زبان کے لوکیل نام سے تبدیل کریں جو LUIS کو تربیت دینے کے لیے استعمال ہوئی۔

    آپ Microsoft Docs پر [زبان اور آواز کی حمایت کی دستاویزات](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) میں معاون زبانوں اور ان کے لوکیل ناموں کی فہرست دیکھ سکتے ہیں۔

    > 💁 اگر آپ کئی زبانیں نہیں بولتے تو آپ [بنگ ٹرانسلیٹ](https://www.bing.com/translator) یا [گوگل ٹرانسلیٹ](https://translate.google.com) جیسی سروسز کا استعمال کر سکتے ہیں تاکہ اپنی پسندیدہ زبان سے کسی اور زبان میں ترجمہ کریں۔ یہ سروسز ترجمہ شدہ متن کی آڈیو بھی چلا سکتی ہیں۔
    >
    > مثال کے طور پر، اگر آپ نے LUIS کو انگریزی میں تربیت دی ہے لیکن صارف کی زبان کے طور پر فرانسیسی استعمال کرنا چاہتے ہیں، تو آپ جملوں جیسے "set a 2 minute and 27 second timer" کو انگریزی سے فرانسیسی میں بنگ ٹرانسلیٹ کے ذریعے ترجمہ کر سکتے ہیں، پھر **Listen translation** بٹن کا استعمال کرتے ہوئے ترجمہ کو اپنے مائیکروفون میں بول سکتے ہیں۔
    >
    > ![بنگ ٹرانسلیٹ پر Listen translation بٹن](../../../../../translated_images/ur/bing-translate.348aa796d6efe2a9.webp)

1. `speech_api_key` کے نیچے مترجم API کلید شامل کریں:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` کو اپنے مترجم سروس وسائل کے API کلید سے تبدیل کریں۔

1. `say` فنکشن کے اوپر ایک `translate_text` فنکشن ڈیفائن کریں جو متن کو سرور زبان سے صارف کی زبان میں ترجمہ کرے:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    اس فنکشن میں `from` اور `to` زبانیں پاس کی جاتی ہیں - آپ کی ایپ کو تقریر کو پہچاننے کے لیے صارف کی زبان سے سرور زبان میں تبدیل کرنا ہوگا، اور بولے گئے فیڈبیک کے لیے سرور زبان سے صارف کی زبان میں۔

1. اس فنکشن کے اندر REST API کال کے لیے URL اور ہیڈرز ڈیفائن کریں:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    اس API کا URL مقام کے لحاظ سے مخصوص نہیں ہے، بلکہ مقام کو ہیڈر کے طور پر پاس کیا جاتا ہے۔ API کلید کو براہ راست استعمال کیا جاتا ہے، اس لیے تقریر سروس کے برعکس ٹوکن جاری کرنے والے API سے ایکسیس ٹوکن حاصل کرنے کی ضرورت نہیں۔

1. اس کے نیچے کال کے لیے پیرامیٹرز اور باڈی ڈیفائن کریں:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` ان پیرامیٹرز کو ڈیفائن کرتا ہے جو API کال کو پاس کیے جائیں گے، `from` اور `to` زبانوں کو پاس کرتے ہوئے۔ یہ کال `from` زبان میں متن کو `to` زبان میں ترجمہ کرے گی۔

    `body` میں ترجمہ کرنے کے لیے متن شامل ہوتا ہے۔ یہ ایک ارے ہے، کیونکہ ایک ہی کال میں کئی متن کے بلاکس کا ترجمہ کیا جا سکتا ہے۔

1. REST API کو کال کریں اور جواب حاصل کریں:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    جوابی JSON ارے کی شکل میں واپس آتا ہے، جس میں ایک آئٹم شامل ہوتا ہے جو ترجمے پر مشتمل ہوتا ہے۔ اس آئٹم میں ان تمام آئٹمز کے ترجمے کے لیے ایک ارے ہوتا ہے جو باڈی میں پاس کیے گئے ہیں۔

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

1. ارے میں پہلے آئٹم کے پہلے ترجمے سے `test` پراپرٹی کو واپس کریں:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` لوپ کو اپ ڈیٹ کریں تاکہ `convert_speech_to_text` کال سے متن کو صارف کی زبان سے سرور زبان میں ترجمہ کرے:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    یہ کوڈ کنسول پر متن کے اصل اور ترجمہ شدہ ورژنز کو بھی پرنٹ کرتا ہے۔

1. `say` فنکشن کو اپ ڈیٹ کریں تاکہ سرور زبان سے صارف کی زبان میں کہنے کے لیے متن کا ترجمہ کرے:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    یہ کوڈ کنسول پر متن کے اصل اور ترجمہ شدہ ورژنز کو بھی پرنٹ کرتا ہے۔

1. اپنا کوڈ چلائیں۔ یقینی بنائیں کہ آپ کا فنکشن ایپ چل رہی ہے، اور صارف کی زبان میں ٹائمر کی درخواست کریں، یا تو خود وہ زبان بول کر، یا ترجمہ ایپ کا استعمال کرتے ہوئے۔

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

    > 💁 مختلف زبانوں میں کچھ کہنے کے مختلف طریقوں کی وجہ سے، آپ کو ایسے ترجمے مل سکتے ہیں جو LUIS کو دیے گئے مثالوں سے تھوڑے مختلف ہوں۔ اگر ایسا ہو تو LUIS میں مزید مثالیں شامل کریں، دوبارہ تربیت دیں اور ماڈل کو دوبارہ شائع کریں۔

> 💁 آپ اس کوڈ کو [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا کثیر لسانی ٹائمر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔