# ضبط صدا - رزبری پای

در این بخش از درس، شما کدی خواهید نوشت که صدا را روی رزبری پای ضبط کند. ضبط صدا توسط یک دکمه کنترل خواهد شد.

## سخت‌افزار

رزبری پای به یک دکمه نیاز دارد تا ضبط صدا را کنترل کند.

دکمه‌ای که استفاده می‌کنید یک دکمه Grove است. این یک حسگر دیجیتال است که سیگنال را روشن یا خاموش می‌کند. این دکمه‌ها می‌توانند طوری تنظیم شوند که هنگام فشار دادن دکمه سیگنال بالا ارسال کنند و وقتی فشار داده نشده سیگنال پایین، یا برعکس.

اگر از میکروفون ReSpeaker 2-Mics Pi HAT استفاده می‌کنید، نیازی به اتصال دکمه نیست زیرا این هت یک دکمه داخلی دارد. به بخش بعدی بروید.

### اتصال دکمه

دکمه می‌تواند به هت پایه Grove متصل شود.

#### وظیفه - اتصال دکمه

![یک دکمه Grove](../../../../../translated_images/fa/grove-button.a70cfbb809a85636.webp)

1. یک سر کابل Grove را به سوکت روی ماژول دکمه وارد کنید. کابل فقط به یک جهت وارد می‌شود.

1. با خاموش بودن رزبری پای، سر دیگر کابل Grove را به سوکت دیجیتال با علامت **D5** روی هت پایه Grove که به پای متصل است وصل کنید. این سوکت دومین سوکت از سمت چپ در ردیف سوکت‌های کنار پین‌های GPIO است.

![دکمه Grove متصل به سوکت D5](../../../../../translated_images/fa/pi-button.c7a1a4f55943341c.webp)

## ضبط صدا

شما می‌توانید با استفاده از کد پایتون صدا را از میکروفون ضبط کنید.

### وظیفه - ضبط صدا

1. پای را روشن کنید و منتظر بمانید تا بوت شود.

1. VS Code را اجرا کنید، یا مستقیماً روی پای یا از طریق افزونه Remote SSH متصل شوید.

1. بسته PyAudio Pip دارای توابعی برای ضبط و پخش صدا است. این بسته به برخی کتابخانه‌های صوتی نیاز دارد که ابتدا باید نصب شوند. دستورات زیر را در ترمینال اجرا کنید تا این کتابخانه‌ها نصب شوند:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. بسته PyAudio Pip را نصب کنید.

    ```sh
    pip3 install pyaudio
    ```

1. یک پوشه جدید به نام `smart-timer` ایجاد کنید و یک فایل به نام `app.py` به این پوشه اضافه کنید.

1. واردات زیر را به بالای این فایل اضافه کنید:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    این کد ماژول `pyaudio`، برخی ماژول‌های استاندارد پایتون برای مدیریت فایل‌های wave و ماژول `grove.factory` را برای وارد کردن یک کلاس دکمه از Factory وارد می‌کند.

1. در زیر این واردات، کدی برای ایجاد یک دکمه Grove اضافه کنید.

    اگر از ReSpeaker 2-Mics Pi HAT استفاده می‌کنید، از کد زیر استفاده کنید:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    این کد یک دکمه روی پورت **D17** ایجاد می‌کند، پورتی که دکمه روی ReSpeaker 2-Mics Pi HAT به آن متصل است. این دکمه طوری تنظیم شده که هنگام فشار دادن سیگنال پایین ارسال کند.

    اگر از ReSpeaker 2-Mics Pi HAT استفاده نمی‌کنید و از دکمه Grove متصل به هت پایه استفاده می‌کنید، از این کد استفاده کنید:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    این کد یک دکمه روی پورت **D5** ایجاد می‌کند که طوری تنظیم شده که هنگام فشار دادن سیگنال بالا ارسال کند.

1. در زیر این کد، یک نمونه از کلاس PyAudio برای مدیریت صدا ایجاد کنید:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. شماره کارت سخت‌افزار برای میکروفون و بلندگو را اعلام کنید. این شماره کارت همان شماره‌ای است که با اجرای `arecord -l` و `aplay -l` در بخش قبلی درس پیدا کردید.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>` را با شماره کارت میکروفون خود جایگزین کنید.

    `<speaker card number>` را با شماره کارت بلندگوی خود جایگزین کنید، همان شماره‌ای که در فایل `alsa.conf` تنظیم کردید.

1. در زیر این کد، نرخ نمونه‌برداری برای ضبط و پخش صدا را اعلام کنید. ممکن است لازم باشد این مقدار را بسته به سخت‌افزار خود تغییر دهید.

    ```python
    rate = 48000 #48KHz
    ```

    اگر هنگام اجرای این کد خطاهای نرخ نمونه‌برداری دریافت کردید، این مقدار را به `44100` یا `16000` تغییر دهید. هرچه مقدار بالاتر باشد، کیفیت صدا بهتر خواهد بود.

1. در زیر این کد، یک تابع جدید به نام `capture_audio` ایجاد کنید. این تابع برای ضبط صدا از میکروفون فراخوانی خواهد شد:

    ```python
    def capture_audio():
    ```

1. داخل این تابع، کد زیر را برای ضبط صدا اضافه کنید:

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

    این کد یک جریان ورودی صوتی با استفاده از شی PyAudio باز می‌کند. این جریان صدا را از میکروفون با نرخ 16KHz ضبط می‌کند و آن را در بافرهایی به اندازه 4096 بایت ذخیره می‌کند.

    کد سپس در حالی که دکمه Grove فشار داده شده است، این بافرهای 4096 بایتی را در یک آرایه می‌خواند.

    > 💁 می‌توانید اطلاعات بیشتری درباره گزینه‌های ارسال شده به متد `open` در [مستندات PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/) بخوانید.

    وقتی دکمه رها شد، جریان متوقف و بسته می‌شود.

1. کد زیر را به انتهای این تابع اضافه کنید:

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

    این کد یک بافر باینری ایجاد می‌کند و تمام صدای ضبط شده را به عنوان یک [فایل WAV](https://wikipedia.org/wiki/WAV) می‌نویسد. این یک روش استاندارد برای نوشتن صدای فشرده‌نشده در یک فایل است. سپس این بافر بازگردانده می‌شود.

1. تابع زیر به نام `play_audio` را برای پخش بافر صوتی اضافه کنید:

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

    این تابع یک جریان صوتی دیگر باز می‌کند، این بار برای خروجی - برای پخش صدا. از تنظیمات مشابه جریان ورودی استفاده می‌کند. بافر به عنوان یک فایل wave باز می‌شود و در قطعات 4096 بایتی به جریان خروجی نوشته می‌شود، صدا را پخش می‌کند. سپس جریان بسته می‌شود.

1. کد زیر را در زیر تابع `capture_audio` اضافه کنید تا حلقه‌ای ایجاد شود که تا زمانی که دکمه فشار داده شود اجرا شود. وقتی دکمه فشار داده شد، صدا ضبط و سپس پخش می‌شود.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. کد را اجرا کنید. دکمه را فشار دهید و در میکروفون صحبت کنید. وقتی کارتان تمام شد دکمه را رها کنید و ضبط را بشنوید.

    ممکن است هنگام ایجاد نمونه PyAudio خطاهای ALSA دریافت کنید. این خطاها به دلیل تنظیمات پای برای دستگاه‌های صوتی است که ندارید. می‌توانید این خطاها را نادیده بگیرید.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    اگر خطای زیر را دریافت کردید:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    نرخ `rate` را به 44100 یا 16000 تغییر دهید.

> 💁 می‌توانید این کد را در پوشه [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) پیدا کنید.

😀 برنامه ضبط صدای شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.