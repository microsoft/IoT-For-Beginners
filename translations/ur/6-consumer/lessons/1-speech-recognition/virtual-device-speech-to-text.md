<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T00:23:57+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "ur"
}
-->
# تقریر سے متن - ورچوئل IoT ڈیوائس

اس سبق کے اس حصے میں، آپ مائیکروفون سے حاصل کردہ تقریر کو متن میں تبدیل کرنے کے لیے اسپیچ سروس کا استعمال کرتے ہوئے کوڈ لکھیں گے۔

## تقریر کو متن میں تبدیل کریں

ونڈوز، لینکس، اور میک او ایس پر، اسپیچ سروسز کا پائتھون SDK آپ کے مائیکروفون کو سننے اور کسی بھی معلوم شدہ تقریر کو متن میں تبدیل کرنے کے لیے استعمال کیا جا سکتا ہے۔ یہ مسلسل سنتا ہے، آڈیو لیولز کا پتہ لگاتا ہے اور جب آڈیو لیول کم ہوتا ہے، جیسے تقریر کے بلاک کے اختتام پر، تو تقریر کو متن میں تبدیل کرنے کے لیے بھیجتا ہے۔

### کام - تقریر کو متن میں تبدیل کریں

1. اپنے کمپیوٹر پر `smart-timer` نامی فولڈر میں ایک نیا پائتھون ایپ بنائیں، جس میں ایک فائل `app.py` ہو اور ایک پائتھون ورچوئل ماحول ہو۔

1. اسپیچ سروسز کے لیے Pip پیکیج انسٹال کریں۔ یقینی بنائیں کہ آپ یہ انسٹالیشن ایک ایسے ٹرمینل سے کر رہے ہیں جس میں ورچوئل ماحول فعال ہو۔

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ اگر آپ کو درج ذیل ایرر ملے:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > تو آپ کو Pip کو اپ ڈیٹ کرنے کی ضرورت ہوگی۔ یہ درج ذیل کمانڈ کے ذریعے کریں، پھر دوبارہ پیکیج انسٹال کرنے کی کوشش کریں:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py` فائل میں درج ذیل امپورٹس شامل کریں:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    یہ کچھ کلاسز کو امپورٹ کرتا ہے جو تقریر کو پہچاننے کے لیے استعمال ہوتی ہیں۔

1. کچھ کنفیگریشن کو ڈکلیئر کرنے کے لیے درج ذیل کوڈ شامل کریں:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>` کو اپنی اسپیچ سروس کے API کلید سے تبدیل کریں۔ `<location>` کو اس مقام سے تبدیل کریں جو آپ نے اسپیچ سروس ریسورس بناتے وقت استعمال کیا تھا۔

    `<language>` کو اس زبان کے لوکیل نام سے تبدیل کریں جس میں آپ بات کریں گے، مثلاً `en-GB` انگریزی کے لیے، یا `zn-HK` کینٹونیز کے لیے۔ آپ مائیکروسافٹ ڈاکس پر [زبان اور آواز کی سپورٹ کی دستاویزات](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) میں سپورٹ شدہ زبانوں اور ان کے لوکیل ناموں کی فہرست دیکھ سکتے ہیں۔

    یہ کنفیگریشن ایک `SpeechConfig` آبجیکٹ بنانے کے لیے استعمال ہوتی ہے جو اسپیچ سروسز کو کنفیگر کرے گا۔

1. ایک اسپیچ ریکگنائزر بنانے کے لیے درج ذیل کوڈ شامل کریں:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. اسپیچ ریکگنائزر ایک بیک گراؤنڈ تھریڈ پر چلتا ہے، آڈیو سنتا ہے اور اس میں موجود تقریر کو متن میں تبدیل کرتا ہے۔ آپ کال بیک فنکشن کے ذریعے متن حاصل کر سکتے ہیں - ایک ایسا فنکشن جو آپ ڈیفائن کرتے ہیں اور ریکگنائزر کو پاس کرتے ہیں۔ جب بھی تقریر کا پتہ چلتا ہے، کال بیک کو کال کیا جاتا ہے۔ درج ذیل کوڈ شامل کریں تاکہ ایک کال بیک ڈیفائن کریں، اور اس کال بیک کو ریکگنائزر کو پاس کریں، ساتھ ہی ایک فنکشن ڈیفائن کریں جو متن کو پروسیس کرے اور کنسول پر لکھے:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. ریکگنائزر صرف اس وقت سننا شروع کرتا ہے جب آپ اسے واضح طور پر شروع کریں۔ ریکگنیشن شروع کرنے کے لیے درج ذیل کوڈ شامل کریں۔ یہ بیک گراؤنڈ میں چلتا ہے، اس لیے آپ کی ایپلیکیشن کو ایک لامتناہی لوپ کی بھی ضرورت ہوگی جو ایپلیکیشن کو چلتا رکھنے کے لیے سوتی رہے۔

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. اس ایپ کو چلائیں۔ اپنے مائیکروفون میں بولیں اور آڈیو کو متن میں تبدیل کر کے کنسول پر آؤٹ پٹ کیا جائے گا۔

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    مختلف قسم کے جملے آزمائیں، ساتھ ہی ایسے جملے جہاں الفاظ ایک جیسے لگتے ہیں لیکن ان کے معنی مختلف ہوتے ہیں۔ مثال کے طور پر، اگر آپ انگریزی میں بول رہے ہیں، تو کہیں 'I want to buy two bananas and an apple too'، اور دیکھیں کہ یہ سیاق و سباق کی بنیاد پر صحیح to، two اور too کا استعمال کیسے کرتا ہے، نہ کہ صرف ان کی آواز پر۔

> 💁 آپ اس کوڈ کو [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا تقریر سے متن پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔