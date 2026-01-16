<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T00:18:35+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "ur"
}
-->
# آڈیو ریکارڈ کریں - راسپبیری پائی

اس سبق کے اس حصے میں، آپ کوڈ لکھیں گے تاکہ راسپبیری پائی پر آڈیو ریکارڈ کیا جا سکے۔ آڈیو ریکارڈنگ ایک بٹن کے ذریعے کنٹرول کی جائے گی۔

## ہارڈویئر

راسپبیری پائی کو آڈیو ریکارڈنگ کنٹرول کرنے کے لیے ایک بٹن کی ضرورت ہے۔

جو بٹن آپ استعمال کریں گے وہ ایک Grove بٹن ہے۔ یہ ایک ڈیجیٹل سینسر ہے جو سگنل کو آن یا آف کرتا ہے۔ ان بٹنوں کو اس طرح ترتیب دیا جا سکتا ہے کہ جب بٹن دبایا جائے تو ہائی سگنل بھیجے، اور جب نہ دبایا جائے تو لو سگنل، یا جب دبایا جائے تو لو سگنل اور جب نہ دبایا جائے تو ہائی سگنل۔

اگر آپ ReSpeaker 2-Mics Pi HAT کو مائیکروفون کے طور پر استعمال کر رہے ہیں، تو بٹن کو جوڑنے کی ضرورت نہیں ہے کیونکہ اس HAT میں پہلے سے ہی ایک بٹن موجود ہے۔ اگلے حصے پر جائیں۔

### بٹن کو جوڑیں

بٹن کو Grove Base HAT سے جوڑا جا سکتا ہے۔

#### کام - بٹن کو جوڑیں

![ایک Grove بٹن](../../../../../translated_images/ur/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Grove کیبل کے ایک سرے کو بٹن ماڈیول کے ساکٹ میں ڈالیں۔ یہ صرف ایک ہی سمت میں جائے گا۔

1. راسپبیری پائی کو بند حالت میں رکھتے ہوئے، Grove کیبل کے دوسرے سرے کو Grove Base HAT پر **D5** کے نشان والے ڈیجیٹل ساکٹ میں جوڑیں۔ یہ ساکٹ GPIO پنز کے ساتھ والی قطار میں بائیں جانب سے دوسرا ہے۔

![Grove بٹن D5 ساکٹ سے جڑا ہوا](../../../../../translated_images/ur/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## آڈیو ریکارڈ کریں

آپ Python کوڈ کے ذریعے مائیکروفون سے آڈیو ریکارڈ کر سکتے ہیں۔

### کام - آڈیو ریکارڈ کریں

1. پائی کو آن کریں اور بوٹ ہونے کا انتظار کریں۔

1. VS Code لانچ کریں، یا تو براہ راست پائی پر، یا Remote SSH ایکسٹینشن کے ذریعے کنیکٹ کریں۔

1. PyAudio Pip پیکج میں آڈیو ریکارڈ اور پلے بیک کرنے کے فنکشنز موجود ہیں۔ اس پیکج کو کچھ آڈیو لائبریریز کی ضرورت ہوتی ہے جو پہلے انسٹال کرنی ہوں گی۔ درج ذیل کمانڈز کو ٹرمینل میں چلائیں:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pip پیکج انسٹال کریں۔

    ```sh
    pip3 install pyaudio
    ```

1. ایک نیا فولڈر بنائیں جس کا نام `smart-timer` ہو اور اس فولڈر میں ایک فائل `app.py` کے نام سے شامل کریں۔

1. اس فائل کے اوپر درج ذیل امپورٹس شامل کریں:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    یہ `pyaudio` ماڈیول، کچھ معیاری Python ماڈیولز جو ویو فائلز کو ہینڈل کرتے ہیں، اور `grove.factory` ماڈیول کو امپورٹ کرتا ہے تاکہ بٹن کلاس بنانے کے لیے `Factory` کو امپورٹ کیا جا سکے۔

1. اس کے نیچے، Grove بٹن بنانے کے لیے کوڈ شامل کریں۔

    اگر آپ ReSpeaker 2-Mics Pi HAT استعمال کر رہے ہیں، تو درج ذیل کوڈ استعمال کریں:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    یہ **D17** پورٹ پر ایک بٹن بناتا ہے، وہ پورٹ جس پر ReSpeaker 2-Mics Pi HAT کا بٹن جڑا ہوا ہے۔ یہ بٹن دبائے جانے پر لو سگنل بھیجنے کے لیے سیٹ کیا گیا ہے۔

    اگر آپ ReSpeaker 2-Mics Pi HAT استعمال نہیں کر رہے ہیں اور Grove بٹن کو Base HAT سے جوڑ رہے ہیں، تو یہ کوڈ استعمال کریں:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    یہ **D5** پورٹ پر ایک بٹن بناتا ہے جو دبائے جانے پر ہائی سگنل بھیجنے کے لیے سیٹ کیا گیا ہے۔

1. اس کے نیچے، PyAudio کلاس کا ایک انسٹینس بنائیں تاکہ آڈیو کو ہینڈل کیا جا سکے:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. مائیکروفون اور اسپیکر کے لیے ہارڈویئر کارڈ نمبر کا اعلان کریں۔ یہ وہ نمبر ہوگا جو آپ نے اس سبق کے پہلے حصے میں `arecord -l` اور `aplay -l` کمانڈز چلا کر پایا تھا۔

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>` کو اپنے مائیکروفون کے کارڈ نمبر سے تبدیل کریں۔

    `<speaker card number>` کو اپنے اسپیکر کے کارڈ نمبر سے تبدیل کریں، وہی نمبر جو آپ نے `alsa.conf` فائل میں سیٹ کیا تھا۔

1. اس کے نیچے، آڈیو ریکارڈنگ اور پلے بیک کے لیے استعمال ہونے والے سیمپل ریٹ کا اعلان کریں۔ آپ کو یہ ہارڈویئر کے مطابق تبدیل کرنا پڑ سکتا ہے۔

    ```python
    rate = 48000 #48KHz
    ```

    اگر آپ کو بعد میں کوڈ چلانے پر سیمپل ریٹ کی غلطیاں ملیں، تو اس ویلیو کو `44100` یا `16000` میں تبدیل کریں۔ ویلیو جتنی زیادہ ہوگی، آواز کا معیار اتنا بہتر ہوگا۔

1. اس کے نیچے، ایک نیا فنکشن `capture_audio` بنائیں۔ یہ مائیکروفون سے آڈیو ریکارڈ کرنے کے لیے کال کیا جائے گا:

    ```python
    def capture_audio():
    ```

1. اس فنکشن کے اندر، آڈیو ریکارڈ کرنے کے لیے درج ذیل شامل کریں:

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    یہ کوڈ PyAudio آبجیکٹ کا استعمال کرتے ہوئے ایک آڈیو ان پٹ اسٹریم کھولتا ہے۔ یہ اسٹریم مائیکروفون سے 16KHz پر آڈیو ریکارڈ کرے گا، اور 4096 بائٹس کے سائز کے بفرز میں آڈیو کو کیپچر کرے گا۔

    کوڈ اس وقت تک لوپ کرتا ہے جب تک Grove بٹن دبایا جاتا ہے، ہر بار 4096 بائٹس کے بفرز کو ایک ارے میں پڑھتا ہے۔

    > 💁 آپ `open` میتھڈ کو پاس کیے گئے آپشنز کے بارے میں مزید معلومات [PyAudio دستاویزات](https://people.csail.mit.edu/hubert/pyaudio/docs/) میں پڑھ سکتے ہیں۔

    جیسے ہی بٹن چھوڑا جاتا ہے، اسٹریم کو روکا اور بند کر دیا جاتا ہے۔

1. اس فنکشن کے آخر میں درج ذیل شامل کریں:

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    یہ کوڈ ایک بائنری بفر بناتا ہے، اور تمام ریکارڈ شدہ آڈیو کو [WAV فائل](https://wikipedia.org/wiki/WAV) کے طور پر لکھتا ہے۔ یہ غیر کمپریسڈ آڈیو کو فائل میں لکھنے کا ایک معیاری طریقہ ہے۔ یہ بفر پھر واپس کیا جاتا ہے۔

1. آڈیو بفر کو پلے بیک کرنے کے لیے درج ذیل `play_audio` فنکشن شامل کریں:

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    یہ فنکشن ایک اور آڈیو اسٹریم کھولتا ہے، اس بار آؤٹ پٹ کے لیے - آڈیو کو پلے کرنے کے لیے۔ یہ ان پٹ اسٹریم کی طرح ہی سیٹنگز استعمال کرتا ہے۔ بفر کو ویو فائل کے طور پر کھولا جاتا ہے اور 4096 بائٹس کے چنکس میں آؤٹ پٹ اسٹریم میں لکھا جاتا ہے، آڈیو کو پلے کرتے ہوئے۔ پھر اسٹریم بند کر دیا جاتا ہے۔

1. `capture_audio` فنکشن کے نیچے درج ذیل کوڈ شامل کریں تاکہ بٹن دبائے جانے تک لوپ کیا جا سکے۔ جیسے ہی بٹن دبایا جاتا ہے، آڈیو ریکارڈ کیا جاتا ہے اور پھر پلے کیا جاتا ہے۔

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. کوڈ چلائیں۔ بٹن دبائیں اور مائیکروفون میں بولیں۔ جب آپ فارغ ہو جائیں تو بٹن چھوڑ دیں، اور آپ ریکارڈنگ سنیں گے۔

    جب PyAudio انسٹینس بنایا جاتا ہے تو آپ کو کچھ ALSA غلطیاں مل سکتی ہیں۔ یہ پائی پر ان آڈیو ڈیوائسز کی کنفیگریشن کی وجہ سے ہے جو آپ کے پاس نہیں ہیں۔ آپ ان غلطیوں کو نظر انداز کر سکتے ہیں۔

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    اگر آپ کو درج ذیل غلطی ملے:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    تو `rate` کو یا تو 44100 یا 16000 میں تبدیل کریں۔

> 💁 آپ اس کوڈ کو [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا آڈیو ریکارڈنگ پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔