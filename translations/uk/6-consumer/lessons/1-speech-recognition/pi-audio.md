<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-28T16:26:15+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "uk"
}
-->
# Захоплення аудіо - Raspberry Pi

У цій частині уроку ви напишете код для захоплення аудіо на вашому Raspberry Pi. Захоплення аудіо буде контролюватися кнопкою.

## Апаратне забезпечення

Raspberry Pi потребує кнопки для управління захопленням аудіо.

Кнопка, яку ви будете використовувати, — це кнопка Grove. Це цифровий датчик, який вмикає або вимикає сигнал. Ці кнопки можна налаштувати так, щоб вони надсилали високий сигнал, коли кнопка натиснута, і низький, коли ні, або низький, коли натиснута, і високий, коли ні.

Якщо ви використовуєте мікрофон ReSpeaker 2-Mics Pi HAT, то немає потреби підключати кнопку, оскільки ця плата вже має вбудовану кнопку. Перейдіть до наступного розділу.

### Підключення кнопки

Кнопку можна підключити до базової плати Grove.

#### Завдання - підключити кнопку

![Кнопка Grove](../../../../../translated_images/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.uk.png)

1. Вставте один кінець кабелю Grove у роз'єм на модулі кнопки. Він вставляється лише в одному напрямку.

1. З вимкненим Raspberry Pi підключіть інший кінець кабелю Grove до цифрового роз'єму, позначеного **D5**, на базовій платі Grove, підключеній до Pi. Цей роз'єм є другим зліва в ряду роз'ємів поруч із GPIO-пінами.

![Кнопка Grove підключена до роз'єму D5](../../../../../translated_images/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.uk.png)

## Захоплення аудіо

Ви можете захоплювати аудіо з мікрофона за допомогою коду на Python.

### Завдання - захопити аудіо

1. Увімкніть Pi і дочекайтеся його завантаження.

1. Запустіть VS Code, або безпосередньо на Pi, або підключіться через розширення Remote SSH.

1. Пакет PyAudio Pip має функції для запису та відтворення аудіо. Цей пакет залежить від деяких аудіо-бібліотек, які потрібно встановити спочатку. Виконайте наступні команди в терміналі для їх встановлення:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Встановіть пакет PyAudio Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Створіть нову папку під назвою `smart-timer` і додайте файл під назвою `app.py` до цієї папки.

1. Додайте наступні імпорти на початку цього файлу:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Це імпортує модуль `pyaudio`, деякі стандартні модулі Python для роботи з wave-файлами, а також модуль `grove.factory` для імпорту `Factory` для створення класу кнопки.

1. Нижче цього додайте код для створення кнопки Grove.

    Якщо ви використовуєте ReSpeaker 2-Mics Pi HAT, використовуйте наступний код:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Це створює кнопку на порту **D17**, порту, до якого підключена кнопка на ReSpeaker 2-Mics Pi HAT. Ця кнопка налаштована на надсилання низького сигналу при натисканні.

    Якщо ви не використовуєте ReSpeaker 2-Mics Pi HAT, а використовуєте кнопку Grove, підключену до базової плати, використовуйте цей код:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Це створює кнопку на порту **D5**, яка налаштована на надсилання високого сигналу при натисканні.

1. Нижче цього створіть екземпляр класу PyAudio для роботи з аудіо:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Вкажіть номер апаратної карти для мікрофона та динаміка. Це буде номер карти, який ви знайшли, виконавши `arecord -l` і `aplay -l` раніше в цьому уроці.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Замініть `<microphone card number>` на номер карти вашого мікрофона.

    Замініть `<speaker card number>` на номер карти вашого динаміка, той самий номер, який ви встановили у файлі `alsa.conf`.

1. Нижче цього вкажіть частоту вибірки для захоплення та відтворення аудіо. Можливо, вам доведеться змінити це залежно від апаратного забезпечення, яке ви використовуєте.

    ```python
    rate = 48000 #48KHz
    ```

    Якщо ви отримаєте помилки частоти вибірки під час виконання цього коду, змініть це значення на `44100` або `16000`. Чим вище значення, тим краща якість звуку.

1. Нижче цього створіть нову функцію під назвою `capture_audio`. Вона буде викликатися для захоплення аудіо з мікрофона:

    ```python
    def capture_audio():
    ```

1. Всередині цієї функції додайте наступне для захоплення аудіо:

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

    Цей код відкриває аудіо-вхідний потік за допомогою об'єкта PyAudio. Цей потік буде захоплювати аудіо з мікрофона на частоті 16 кГц, захоплюючи його в буфери розміром 4096 байт.

    Код потім циклічно працює, поки кнопка Grove натиснута, зчитуючи ці буфери розміром 4096 байт у масив кожного разу.

    > 💁 Ви можете дізнатися більше про параметри, передані методу `open`, у [документації PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Після того, як кнопка відпущена, потік зупиняється і закривається.

1. Додайте наступне в кінці цієї функції:

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

    Цей код створює двійковий буфер і записує все захоплене аудіо в нього як [WAV-файл](https://wikipedia.org/wiki/WAV). Це стандартний спосіб запису незжатого аудіо у файл. Потім цей буфер повертається.

1. Додайте наступну функцію `play_audio` для відтворення аудіо з буфера:

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

    Ця функція відкриває інший аудіо-потік, цього разу для виводу - для відтворення аудіо. Вона використовує ті ж налаштування, що й вхідний потік. Буфер відкривається як wave-файл і записується у вихідний потік шматками по 4096 байт, відтворюючи аудіо. Потік потім закривається.

1. Додайте наступний код нижче функції `capture_audio`, щоб виконувати цикл до натискання кнопки. Після натискання кнопки аудіо захоплюється, а потім відтворюється.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Запустіть код. Натисніть кнопку і говоріть у мікрофон. Відпустіть кнопку, коли закінчите, і ви почуєте запис.

    Ви можете отримати деякі помилки ALSA при створенні екземпляра PyAudio. Це пов'язано з конфігурацією на Pi для аудіо-пристроїв, яких у вас немає. Ви можете ігнорувати ці помилки.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Якщо ви отримаєте наступну помилку:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    тоді змініть `rate` на 44100 або 16000.

> 💁 Ви можете знайти цей код у папці [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Ваша програма для запису аудіо була успішною!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають у результаті використання цього перекладу.