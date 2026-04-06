# التقاط الصوت - Raspberry Pi

في هذا الجزء من الدرس، ستكتب كودًا لالتقاط الصوت باستخدام Raspberry Pi. سيتم التحكم في عملية التقاط الصوت بواسطة زر.

## الأجهزة

يحتاج Raspberry Pi إلى زر للتحكم في التقاط الصوت.

الزر الذي ستستخدمه هو زر Grove. هذا الزر هو مستشعر رقمي يقوم بتشغيل أو إيقاف الإشارة. يمكن تكوين هذه الأزرار لإرسال إشارة عالية عند الضغط على الزر، وإشارة منخفضة عند عدم الضغط، أو العكس.

إذا كنت تستخدم ميكروفون ReSpeaker 2-Mics Pi HAT، فلا حاجة لتوصيل زر إضافي، حيث يحتوي هذا الملحق على زر مدمج. انتقل إلى القسم التالي.

### توصيل الزر

يمكن توصيل الزر بقاعدة Grove Base Hat.

#### المهمة - توصيل الزر

![زر Grove](../../../../../translated_images/ar/grove-button.a70cfbb809a85636.webp)

1. أدخل أحد طرفي كابل Grove في المقبس الموجود على وحدة الزر. لن يدخل إلا في اتجاه واحد.

1. مع إيقاف تشغيل Raspberry Pi، قم بتوصيل الطرف الآخر من كابل Grove بالمقبس الرقمي المسمى **D5** على قاعدة Grove Base Hat المثبتة على Pi. هذا المقبس هو الثاني من اليسار في صف المقابس بجانب دبابيس GPIO.

![زر Grove متصل بالمقبس D5](../../../../../translated_images/ar/pi-button.c7a1a4f55943341c.webp)

## التقاط الصوت

يمكنك التقاط الصوت من الميكروفون باستخدام كود Python.

### المهمة - التقاط الصوت

1. قم بتشغيل Raspberry Pi وانتظر حتى يتم الإقلاع.

1. افتح VS Code، إما مباشرة على Raspberry Pi، أو عبر الاتصال باستخدام امتداد Remote SSH.

1. تحتوي حزمة PyAudio Pip على وظائف لتسجيل وتشغيل الصوت. تعتمد هذه الحزمة على بعض مكتبات الصوت التي تحتاج إلى تثبيتها أولاً. قم بتشغيل الأوامر التالية في الطرفية لتثبيتها:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. قم بتثبيت حزمة PyAudio Pip.

    ```sh
    pip3 install pyaudio
    ```

1. أنشئ مجلدًا جديدًا باسم `smart-timer` وأضف ملفًا باسم `app.py` إلى هذا المجلد.

1. أضف الواردات التالية إلى أعلى هذا الملف:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    هذا يستورد وحدة `pyaudio`، وبعض الوحدات القياسية في Python للتعامل مع ملفات الصوت، ووحدة `grove.factory` لاستيراد `Factory` لإنشاء فئة الزر.

1. بعد ذلك، أضف كودًا لإنشاء زر Grove.

    إذا كنت تستخدم ميكروفون ReSpeaker 2-Mics Pi HAT، استخدم الكود التالي:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    هذا ينشئ زرًا على المنفذ **D17**، وهو المنفذ الذي يتصل به الزر على ReSpeaker 2-Mics Pi HAT. يتم ضبط هذا الزر لإرسال إشارة منخفضة عند الضغط عليه.

    إذا كنت لا تستخدم ReSpeaker 2-Mics Pi HAT، وتستخدم زر Grove متصلًا بقاعدة Grove Base Hat، استخدم هذا الكود:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    هذا ينشئ زرًا على المنفذ **D5** يتم ضبطه لإرسال إشارة عالية عند الضغط عليه.

1. بعد ذلك، أنشئ مثيلًا لفئة PyAudio للتعامل مع الصوت:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. قم بتحديد رقم بطاقة الأجهزة للميكروفون ومكبر الصوت. سيكون هذا الرقم هو الرقم الذي وجدته عند تشغيل الأمرين `arecord -l` و`aplay -l` في وقت سابق من هذا الدرس.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    استبدل `<microphone card number>` برقم بطاقة الميكروفون الخاصة بك.

    استبدل `<speaker card number>` برقم بطاقة مكبر الصوت الخاصة بك، وهو نفس الرقم الذي قمت بتعيينه في ملف `alsa.conf`.

1. بعد ذلك، قم بتحديد معدل العينة المستخدم لالتقاط وتشغيل الصوت. قد تحتاج إلى تغيير هذا بناءً على الأجهزة التي تستخدمها.

    ```python
    rate = 48000 #48KHz
    ```

    إذا واجهت أخطاء في معدل العينة عند تشغيل الكود لاحقًا، قم بتغيير هذه القيمة إلى `44100` أو `16000`. كلما زادت القيمة، زادت جودة الصوت.

1. بعد ذلك، أنشئ دالة جديدة باسم `capture_audio`. سيتم استدعاء هذه الدالة لالتقاط الصوت من الميكروفون:

    ```python
    def capture_audio():
    ```

1. داخل هذه الدالة، أضف الكود التالي لالتقاط الصوت:

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

    يقوم هذا الكود بفتح تدفق إدخال صوتي باستخدام كائن PyAudio. يقوم هذا التدفق بالتقاط الصوت من الميكروفون بمعدل 16 كيلوهرتز، ويقوم بالتقاطه في مخازن بحجم 4096 بايت.

    ثم يقوم الكود بالتكرار أثناء الضغط على زر Grove، حيث يقرأ هذه المخازن بحجم 4096 بايت في كل مرة.

    > 💁 يمكنك قراءة المزيد عن الخيارات الممررة إلى طريقة `open` في [توثيق PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    بمجرد تحرير الزر، يتم إيقاف التدفق وإغلاقه.

1. أضف الكود التالي إلى نهاية هذه الدالة:

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

    يقوم هذا الكود بإنشاء مخزن ثنائي، ويكتب جميع الصوت الملتقط فيه كملف [WAV](https://wikipedia.org/wiki/WAV). هذا هو الطريقة القياسية لكتابة الصوت غير المضغوط إلى ملف. يتم بعد ذلك إرجاع هذا المخزن.

1. أضف دالة `play_audio` التالية لتشغيل مخزن الصوت:

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

    تقوم هذه الدالة بفتح تدفق صوتي آخر، هذه المرة للإخراج - لتشغيل الصوت. تستخدم نفس الإعدادات مثل تدفق الإدخال. يتم فتح المخزن كملف صوتي ويتم كتابته إلى تدفق الإخراج في أجزاء بحجم 4096 بايت، مما يؤدي إلى تشغيل الصوت. ثم يتم إغلاق التدفق.

1. أضف الكود التالي أسفل دالة `capture_audio` للتكرار حتى يتم الضغط على الزر. بمجرد الضغط على الزر، يتم التقاط الصوت ثم تشغيله.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. قم بتشغيل الكود. اضغط على الزر وتحدث في الميكروفون. حرر الزر عند الانتهاء، وستسمع التسجيل.

    قد تواجه بعض أخطاء ALSA عند إنشاء مثيل PyAudio. يرجع ذلك إلى تكوين Raspberry Pi لأجهزة صوتية لا تمتلكها. يمكنك تجاهل هذه الأخطاء.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    إذا واجهت الخطأ التالي:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    قم بتغيير `rate` إلى 44100 أو 16000.

> 💁 يمكنك العثور على هذا الكود في المجلد [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 لقد نجحت في إنشاء برنامج تسجيل الصوت!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.