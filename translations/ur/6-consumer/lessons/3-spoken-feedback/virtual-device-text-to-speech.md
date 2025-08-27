<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T00:17:32+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "ur"
}
-->
# متن کو آواز میں تبدیل کریں - ورچوئل IoT ڈیوائس

اس سبق کے اس حصے میں، آپ کوڈ لکھیں گے تاکہ متن کو آواز میں تبدیل کیا جا سکے، اس کے لیے اسپیکنگ سروس استعمال کی جائے گی۔

## متن کو آواز میں تبدیل کریں

اسپیکنگ سروسز SDK، جو آپ نے پچھلے سبق میں آواز کو متن میں تبدیل کرنے کے لیے استعمال کیا تھا، متن کو دوبارہ آواز میں تبدیل کرنے کے لیے بھی استعمال کیا جا سکتا ہے۔ جب آواز کی درخواست کی جاتی ہے، تو آپ کو وہ آواز فراہم کرنی ہوگی جو استعمال کی جائے گی، کیونکہ مختلف آوازوں کے ذریعے آواز پیدا کی جا سکتی ہے۔

ہر زبان مختلف آوازوں کی ایک رینج کو سپورٹ کرتی ہے، اور آپ اسپیکنگ سروسز SDK سے ہر زبان کے لیے سپورٹ شدہ آوازوں کی فہرست حاصل کر سکتے ہیں۔

### کام - متن کو آواز میں تبدیل کریں

1. `smart-timer` پروجیکٹ کو VS Code میں کھولیں، اور یقینی بنائیں کہ ورچوئل ماحول ٹرمینل میں لوڈ ہو چکا ہے۔

1. `azure.cognitiveservices.speech` پیکج سے `SpeechSynthesizer` کو موجودہ امپورٹس میں شامل کریں:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say` فنکشن کے اوپر، اسپیکنگ کنفیگریشن بنائیں تاکہ اسپیکنگ سِن تھیسائزر کے ساتھ استعمال ہو سکے:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    یہ وہی API key، مقام اور زبان استعمال کرتا ہے جو ریکگنائزر کے ذریعے استعمال کی گئی تھی۔

1. اس کے نیچے، درج ذیل کوڈ شامل کریں تاکہ ایک آواز حاصل کی جا سکے اور اسے اسپیکنگ کنفیگریشن پر سیٹ کیا جا سکے:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    یہ تمام دستیاب آوازوں کی فہرست حاصل کرتا ہے، پھر پہلی آواز تلاش کرتا ہے جو استعمال کی جا رہی زبان سے مطابقت رکھتی ہے۔

    > 💁 آپ مائیکروسافٹ ڈاکس پر [زبان اور آواز کی سپورٹ کی دستاویزات](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) سے سپورٹ شدہ آوازوں کی مکمل فہرست حاصل کر سکتے ہیں۔ اگر آپ کسی خاص آواز کو استعمال کرنا چاہتے ہیں، تو آپ اس فنکشن کو ہٹا کر آواز کو اس دستاویزات میں دی گئی آواز کے نام سے ہارڈ کوڈ کر سکتے ہیں۔ مثال کے طور پر:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say` فنکشن کے مواد کو اپ ڈیٹ کریں تاکہ جواب کے لیے SSML تیار کیا جا سکے:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. اس کے نیچے، اسپیکنگ ریکگنیشن کو روکیں، SSML کو بولیں، پھر ریکگنیشن کو دوبارہ شروع کریں:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    جب متن بولا جا رہا ہو تو ریکگنیشن کو روکا جاتا ہے تاکہ ٹائمر شروع ہونے کے اعلان کو ڈیٹیکٹ ہونے سے بچایا جا سکے، جو LUIS کو بھیجا جا سکتا ہے اور ممکنہ طور پر نئے ٹائمر سیٹ کرنے کی درخواست کے طور پر سمجھا جا سکتا ہے۔

    > 💁 آپ اس کو آزما سکتے ہیں کہ ریکگنیشن کو روکنے اور دوبارہ شروع کرنے والی لائنز کو کمنٹ کر دیں۔ ایک ٹائمر سیٹ کریں، اور آپ دیکھ سکتے ہیں کہ اعلان ایک نیا ٹائمر سیٹ کرتا ہے، جو ایک نیا اعلان پیدا کرتا ہے، اور یہ سلسلہ ہمیشہ کے لیے جاری رہ سکتا ہے!

1. ایپ چلائیں، اور یقینی بنائیں کہ فنکشن ایپ بھی چل رہی ہے۔ کچھ ٹائمر سیٹ کریں، اور آپ ایک بولی ہوئی جواب سنیں گے جو کہے گا کہ آپ کا ٹائمر سیٹ ہو گیا ہے، پھر ایک اور بولی ہوئی جواب جب ٹائمر مکمل ہو جائے گا۔

> 💁 آپ اس کوڈ کو [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا ٹائمر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔