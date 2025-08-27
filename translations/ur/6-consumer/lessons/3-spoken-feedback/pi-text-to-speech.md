<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T00:12:57+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "ur"
}
-->
# ٹیکسٹ کو آواز میں تبدیل کریں - راسپبیری پائی

اس سبق کے اس حصے میں، آپ ایسا کوڈ لکھیں گے جو ٹیکسٹ کو آواز میں تبدیل کرے گا، اسپیکنگ سروس کا استعمال کرتے ہوئے۔

## اسپیکنگ سروس کے ذریعے ٹیکسٹ کو آواز میں تبدیل کریں

ٹیکسٹ کو اسپیکنگ سروس کے ذریعے REST API کا استعمال کرتے ہوئے بھیجا جا سکتا ہے تاکہ اسے ایک آڈیو فائل میں تبدیل کیا جا سکے، جسے آپ کے IoT ڈیوائس پر چلایا جا سکے۔ آواز کی درخواست کرتے وقت، آپ کو وہ آواز فراہم کرنی ہوگی جو استعمال کی جائے گی، کیونکہ مختلف آوازوں کے ذریعے آواز پیدا کی جا سکتی ہے۔

ہر زبان مختلف آوازوں کی ایک رینج کو سپورٹ کرتی ہے، اور آپ اسپیکنگ سروس کے خلاف REST درخواست کر سکتے ہیں تاکہ ہر زبان کے لیے سپورٹ شدہ آوازوں کی فہرست حاصل کی جا سکے۔

### کام - ایک آواز حاصل کریں

1. VS Code میں `smart-timer` پروجیکٹ کھولیں۔

1. زبان کے لیے آوازوں کی فہرست کی درخواست کرنے کے لیے `say` فنکشن کے اوپر درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ ایک فنکشن `get_voice` کو ڈیفائن کرتا ہے جو اسپیکنگ سروس کا استعمال کرتے ہوئے آوازوں کی فہرست حاصل کرتا ہے۔ پھر یہ پہلی آواز تلاش کرتا ہے جو استعمال ہونے والی زبان سے میل کھاتی ہو۔

    اس فنکشن کو پھر پہلی آواز کو اسٹور کرنے کے لیے کال کیا جاتا ہے، اور آواز کا نام کنسول میں پرنٹ کیا جاتا ہے۔ اس آواز کو ایک بار درخواست کیا جا سکتا ہے اور ہر بار ٹیکسٹ کو آواز میں تبدیل کرنے کے لیے اس کی ویلیو استعمال کی جا سکتی ہے۔

    > 💁 آپ سپورٹ شدہ آوازوں کی مکمل فہرست [Microsoft Docs پر زبان اور آواز کی سپورٹ کی دستاویزات](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) سے حاصل کر سکتے ہیں۔ اگر آپ کسی خاص آواز کو استعمال کرنا چاہتے ہیں، تو آپ اس فنکشن کو ہٹا سکتے ہیں اور اس دستاویزات سے آواز کے نام کو ہارڈ کوڈ کر سکتے ہیں۔ مثال کے طور پر:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### کام - ٹیکسٹ کو آواز میں تبدیل کریں

1. اس کے نیچے، اسپیکنگ سروسز سے حاصل ہونے والے آڈیو فارمیٹ کے لیے ایک کانسٹنٹ ڈیفائن کریں۔ جب آپ آڈیو کی درخواست کرتے ہیں، تو آپ اسے مختلف فارمیٹس میں حاصل کر سکتے ہیں۔

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    آپ کے ہارڈویئر پر منحصر ہے کہ آپ کون سا فارمیٹ استعمال کر سکتے ہیں۔ اگر آپ کو آڈیو چلاتے وقت `Invalid sample rate` کی غلطیاں ملتی ہیں، تو اسے کسی اور ویلیو میں تبدیل کریں۔ آپ سپورٹ شدہ ویلیوز کی فہرست [Microsoft Docs پر ٹیکسٹ ٹو اسپیک REST API کی دستاویزات](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) میں دیکھ سکتے ہیں۔ آپ کو `riff` فارمیٹ آڈیو استعمال کرنے کی ضرورت ہوگی، اور کوشش کرنے کے لیے ویلیوز ہیں `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` اور `riff-48khz-16bit-mono-pcm`۔

1. اس کے نیچے، ایک فنکشن `get_speech` ڈیفائن کریں جو اسپیکنگ سروس REST API کا استعمال کرتے ہوئے ٹیکسٹ کو آواز میں تبدیل کرے گا:

    ```python
    def get_speech(text):
    ```

1. `get_speech` فنکشن میں، کال کرنے کے لیے URL اور پاس کرنے کے لیے ہیڈرز ڈیفائن کریں:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    یہ ہیڈرز کو ایک جنریٹڈ ایکسیس ٹوکن استعمال کرنے، مواد کو SSML پر سیٹ کرنے اور مطلوبہ آڈیو فارمیٹ کو ڈیفائن کرنے کے لیے سیٹ کرتا ہے۔

1. اس کے نیچے، REST API کو بھیجنے کے لیے SSML ڈیفائن کریں:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    یہ SSML زبان اور استعمال کرنے کے لیے آواز کو سیٹ کرتا ہے، ساتھ ہی تبدیل کرنے کے لیے ٹیکسٹ کو بھی۔

1. آخر میں، اس فنکشن میں کوڈ شامل کریں تاکہ REST درخواست کی جائے اور بائنری آڈیو ڈیٹا واپس کیا جائے:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### کام - آڈیو چلائیں

1. `get_speech` فنکشن کے نیچے، ایک نیا فنکشن ڈیفائن کریں تاکہ REST API کال کے ذریعے واپس کیے گئے آڈیو کو چلایا جا سکے:

    ```python
    def play_speech(speech):
    ```

1. اس فنکشن کو پاس کیا گیا `speech` REST API سے واپس کیا گیا بائنری آڈیو ڈیٹا ہوگا۔ درج ذیل کوڈ کا استعمال کریں تاکہ اسے ایک ویو فائل کے طور پر کھولا جا سکے اور PyAudio کے ذریعے آڈیو چلایا جا سکے:

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

    یہ کوڈ PyAudio اسٹریم کا استعمال کرتا ہے، جیسا کہ آڈیو کیپچر کرتے وقت۔ فرق یہ ہے کہ یہاں اسٹریم کو آؤٹ پٹ اسٹریم کے طور پر سیٹ کیا گیا ہے، اور آڈیو ڈیٹا سے ڈیٹا پڑھا جاتا ہے اور اسٹریم میں بھیجا جاتا ہے۔

    اسٹریم کی تفصیلات جیسے سیمپل ریٹ کو ہارڈ کوڈ کرنے کے بجائے، یہ آڈیو ڈیٹا سے پڑھا جاتا ہے۔

1. `say` فنکشن کے مواد کو درج ذیل سے تبدیل کریں:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    یہ کوڈ ٹیکسٹ کو بائنری آڈیو ڈیٹا کے طور پر آواز میں تبدیل کرتا ہے، اور آڈیو چلاتا ہے۔

1. ایپ چلائیں، اور یقینی بنائیں کہ فنکشن ایپ بھی چل رہی ہے۔ کچھ ٹائمر سیٹ کریں، اور آپ کو ایک بولی ہوئی جواب سنائی دے گا جو کہے گا کہ آپ کا ٹائمر سیٹ ہو گیا ہے، پھر ایک اور بولی ہوئی جواب جب ٹائمر مکمل ہو جائے گا۔

    اگر آپ کو `Invalid sample rate` کی غلطیاں ملتی ہیں، تو `playback_format` کو اوپر بیان کردہ کے مطابق تبدیل کریں۔

> 💁 آپ اس کوڈ کو [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) فولڈر میں دیکھ سکتے ہیں۔

😀 آپ کا ٹائمر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔