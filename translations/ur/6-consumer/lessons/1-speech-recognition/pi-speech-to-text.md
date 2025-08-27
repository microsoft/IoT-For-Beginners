<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T00:32:47+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "ur"
}
-->
# تقریر کو متن میں تبدیل کرنا - راسپبیری پائی

اس سبق کے اس حصے میں، آپ ایسا کوڈ لکھیں گے جو ریکارڈ شدہ آڈیو میں تقریر کو متن میں تبدیل کرے گا، اس کے لیے اسپیک سروس کا استعمال کیا جائے گا۔

## آڈیو کو اسپیک سروس پر بھیجنا

آڈیو کو اسپیک سروس پر REST API کے ذریعے بھیجا جا سکتا ہے۔ اسپیک سروس استعمال کرنے کے لیے، سب سے پہلے آپ کو ایک ایکسیس ٹوکن کی درخواست کرنی ہوگی، پھر اس ٹوکن کو REST API تک رسائی کے لیے استعمال کریں۔ یہ ایکسیس ٹوکن 10 منٹ کے بعد ختم ہو جاتے ہیں، اس لیے آپ کے کوڈ کو باقاعدگی سے ان کی درخواست کرنی چاہیے تاکہ یہ ہمیشہ تازہ رہیں۔

### کام - ایکسیس ٹوکن حاصل کریں

1. اپنے پائی پر `smart-timer` پروجیکٹ کھولیں۔

1. `play_audio` فنکشن کو ہٹا دیں۔ یہ اب ضروری نہیں ہے کیونکہ آپ نہیں چاہتے کہ اسمارٹ ٹائمر آپ کی کہی ہوئی بات کو دہرا دے۔

1. `app.py` فائل کے شروع میں درج ذیل امپورٹ شامل کریں:

    ```python
    import requests
    ```

1. `while True` لوپ سے اوپر درج ذیل کوڈ شامل کریں تاکہ اسپیک سروس کے لیے کچھ سیٹنگز ڈکلیئر کی جا سکیں:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>` کو اپنی اسپیک سروس ریسورس کی API key سے تبدیل کریں۔ `<location>` کو اس مقام سے تبدیل کریں جو آپ نے اسپیک سروس ریسورس بناتے وقت استعمال کیا تھا۔

    `<language>` کو اس زبان کے لوکیل نام سے تبدیل کریں جس میں آپ بات کریں گے، مثلاً انگریزی کے لیے `en-GB` یا کینٹونیز کے لیے `zn-HK`۔ آپ مائیکروسافٹ ڈاکس پر [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) میں سپورٹ شدہ زبانوں اور ان کے لوکیل ناموں کی فہرست دیکھ سکتے ہیں۔

1. اس کے نیچے، ایک فنکشن شامل کریں جو ایکسیس ٹوکن حاصل کرے:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    یہ ایک ٹوکن جاری کرنے والے اینڈ پوائنٹ کو کال کرتا ہے، API key کو ہیڈر کے طور پر پاس کرتے ہوئے۔ یہ کال ایک ایکسیس ٹوکن واپس کرتی ہے جسے اسپیک سروسز کو کال کرنے کے لیے استعمال کیا جا سکتا ہے۔

1. اس کے نیچے، ایک فنکشن ڈکلیئر کریں جو ریکارڈ شدہ آڈیو میں تقریر کو REST API کے ذریعے متن میں تبدیل کرے:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. اس فنکشن کے اندر، REST API URL اور ہیڈرز سیٹ کریں:

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

    یہ اسپیک سروسز ریسورس کے مقام کا استعمال کرتے ہوئے ایک URL بناتا ہے۔ پھر یہ `get_access_token` فنکشن سے ایکسیس ٹوکن کے ساتھ ہیڈرز کو پاپولیٹ کرتا ہے، اور آڈیو کیپچر کرنے کے لیے استعمال ہونے والے سیمپل ریٹ کو بھی شامل کرتا ہے۔ آخر میں، یہ کچھ پیرامیٹرز کو URL کے ساتھ پاس کرتا ہے جو آڈیو کی زبان پر مشتمل ہوتے ہیں۔

1. اس کے نیچے، REST API کو کال کرنے اور متن واپس حاصل کرنے کے لیے درج ذیل کوڈ شامل کریں:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    یہ URL کو کال کرتا ہے اور JSON ویلیو کو ڈی کوڈ کرتا ہے جو رسپانس میں آتی ہے۔ رسپانس میں `RecognitionStatus` ویلیو یہ ظاہر کرتی ہے کہ آیا کال نے تقریر کو کامیابی سے متن میں تبدیل کیا یا نہیں، اور اگر یہ `Success` ہو تو فنکشن سے متن واپس کیا جاتا ہے، ورنہ ایک خالی سٹرنگ واپس کی جاتی ہے۔

1. `while True:` لوپ سے اوپر، ایک فنکشن ڈکلیئر کریں جو اسپیک ٹو ٹیکسٹ سروس سے واپس کیے گئے متن کو پروسیس کرے۔ یہ فنکشن فی الحال صرف کنسول پر متن پرنٹ کرے گا۔

    ```python
    def process_text(text):
        print(text)
    ```

1. آخر میں، `while True` لوپ میں `play_audio` کال کو `convert_speech_to_text` فنکشن کی کال سے تبدیل کریں، اور متن کو `process_text` فنکشن میں پاس کریں:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. کوڈ چلائیں۔ بٹن دبائیں اور مائیکروفون میں بولیں۔ جب آپ بولنا ختم کریں تو بٹن چھوڑ دیں، اور آڈیو کو متن میں تبدیل کر کے کنسول پر پرنٹ کیا جائے گا۔

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    مختلف قسم کے جملے آزمائیں، ساتھ ہی ایسے جملے بھی جہاں الفاظ کی آواز ایک جیسی ہو لیکن ان کے معنی مختلف ہوں۔ مثال کے طور پر، اگر آپ انگریزی میں بول رہے ہیں، تو کہیں 'I want to buy two bananas and an apple too'، اور دیکھیں کہ یہ کس طرح سیاق و سباق کی بنیاد پر درست to، two اور too کا استعمال کرتا ہے، نہ کہ صرف ان کی آواز پر۔

> 💁 آپ اس کوڈ کو [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا اسپیک ٹو ٹیکسٹ پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔