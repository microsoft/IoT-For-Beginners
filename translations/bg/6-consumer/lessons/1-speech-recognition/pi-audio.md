# Запис на аудио - Raspberry Pi

В тази част от урока ще напишете код за запис на аудио на вашия Raspberry Pi. Записът на аудио ще се контролира чрез бутон.

## Хардуер

Raspberry Pi се нуждае от бутон, за да контролира записа на аудио.

Бутонът, който ще използвате, е Grove бутон. Това е цифров сензор, който включва или изключва сигнал. Тези бутони могат да бъдат конфигурирани да изпращат висок сигнал, когато бутонът е натиснат, и нисък, когато не е, или нисък, когато е натиснат, и висок, когато не е.

Ако използвате ReSpeaker 2-Mics Pi HAT като микрофон, няма нужда да свързвате бутон, тъй като този HAT вече има вграден бутон. Пропуснете към следващия раздел.

### Свързване на бутона

Бутонът може да бъде свързан към Grove базовия HAT.

#### Задача - свържете бутона

![Grove бутон](../../../../../translated_images/bg/grove-button.a70cfbb809a85636.webp)

1. Поставете единия край на Grove кабела в гнездото на модулa на бутона. Кабелът може да бъде поставен само в една посока.

1. С изключен Raspberry Pi, свържете другия край на Grove кабела към цифровото гнездо, маркирано **D5** на Grove базовия HAT, прикрепен към Pi. Това гнездо е второто отляво, на реда с гнезда до GPIO пиновете.

![Grove бутон, свързан към гнездо D5](../../../../../translated_images/bg/pi-button.c7a1a4f55943341c.webp)

## Запис на аудио

Можете да записвате аудио от микрофона, използвайки Python код.

### Задача - запис на аудио

1. Включете Pi и изчакайте да се зареди.

1. Стартирайте VS Code, директно на Pi или чрез Remote SSH разширението.

1. PyAudio Pip пакетът има функции за запис и възпроизвеждане на аудио. Този пакет зависи от някои аудио библиотеки, които трябва да бъдат инсталирани предварително. Изпълнете следните команди в терминала, за да ги инсталирате:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Инсталирайте PyAudio Pip пакета.

    ```sh
    pip3 install pyaudio
    ```

1. Създайте нова папка, наречена `smart-timer`, и добавете файл, наречен `app.py`, в тази папка.

1. Добавете следните импорти в началото на файла:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Това импортира модула `pyaudio`, някои стандартни Python модули за работа с wave файлове и модула `grove.factory` за създаване на клас за бутон.

1. Под това добавете код за създаване на Grove бутон.

    Ако използвате ReSpeaker 2-Mics Pi HAT, използвайте следния код:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Това създава бутон на порт **D17**, портът, към който е свързан бутонът на ReSpeaker 2-Mics Pi HAT. Този бутон е настроен да изпраща нисък сигнал, когато е натиснат.

    Ако не използвате ReSpeaker 2-Mics Pi HAT, а Grove бутон, свързан към базовия HAT, използвайте този код:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Това създава бутон на порт **D5**, който е настроен да изпраща висок сигнал, когато е натиснат.

1. Под това създайте инстанция на класа PyAudio за управление на аудио:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Декларирайте номера на хардуерната карта за микрофона и високоговорителя. Това ще бъде номерът на картата, който открихте, като изпълнихте `arecord -l` и `aplay -l` по-рано в урока.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Заменете `<microphone card number>` с номера на картата на вашия микрофон.

    Заменете `<speaker card number>` с номера на картата на вашия високоговорител, същия номер, който зададохте в файла `alsa.conf`.

1. Под това декларирайте честотата на семплиране за записа и възпроизвеждането на аудио. Може да се наложи да промените това в зависимост от хардуера, който използвате.

    ```python
    rate = 48000 #48KHz
    ```

    Ако получите грешки, свързани с честотата на семплиране, когато изпълнявате този код, променете стойността на `44100` или `16000`. Колкото по-висока е стойността, толкова по-добро е качеството на звука.

1. Под това създайте нова функция, наречена `capture_audio`. Тази функция ще бъде извикана за запис на аудио от микрофона:

    ```python
    def capture_audio():
    ```

1. Вътре в тази функция добавете следното за запис на аудио:

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

    Този код отваря входен аудио поток, използвайки PyAudio обекта. Този поток ще записва аудио от микрофона на 16KHz, записвайки го в буфери с размер 4096 байта.

    Кодът след това цикли, докато Grove бутонът е натиснат, като чете тези 4096 байтови буфери в масив всеки път.

    > 💁 Можете да прочетете повече за опциите, предадени на метода `open`, в [PyAudio документацията](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    След като бутонът бъде освободен, потокът се спира и затваря.

1. Добавете следното в края на тази функция:

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

    Този код създава двоичен буфер и записва цялото записано аудио в него като [WAV файл](https://wikipedia.org/wiki/WAV). Това е стандартен начин за запис на некомпресирано аудио във файл. Този буфер след това се връща.

1. Добавете следната функция `play_audio`, за да възпроизведете аудио буфера:

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

    Тази функция отваря друг аудио поток, този път за изход - за възпроизвеждане на аудио. Тя използва същите настройки като входния поток. Буферът след това се отваря като wave файл и се записва в изходния поток на парчета от 4096 байта, възпроизвеждайки аудиото. Потокът след това се затваря.

1. Добавете следния код под функцията `capture_audio`, за да циклирате, докато бутонът бъде натиснат. След като бутонът бъде натиснат, аудиото се записва и след това се възпроизвежда.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Изпълнете кода. Натиснете бутона и говорете в микрофона. Освободете бутона, когато сте готови, и ще чуете записа.

    Може да получите някои ALSA грешки, когато PyAudio инстанцията бъде създадена. Това се дължи на конфигурация на Pi за аудио устройства, които нямате. Можете да игнорирате тези грешки.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Ако получите следната грешка:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    тогава променете `rate` на `44100` или `16000`.

> 💁 Можете да намерите този код в папката [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Вашата програма за запис на аудио беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.