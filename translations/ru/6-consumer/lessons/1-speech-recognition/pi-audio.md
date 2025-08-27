<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T00:17:59+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "ru"
}
-->
# Захват аудио - Raspberry Pi

В этой части урока вы напишете код для захвата аудио на вашем Raspberry Pi. Управление захватом аудио будет осуществляться с помощью кнопки.

## Оборудование

Для управления захватом аудио Raspberry Pi требуется кнопка.

Кнопка, которую вы будете использовать, — это кнопка Grove. Это цифровой датчик, который включает или выключает сигнал. Эти кнопки можно настроить так, чтобы они отправляли высокий сигнал при нажатии и низкий, когда не нажаты, или наоборот — низкий при нажатии и высокий, когда не нажаты.

Если вы используете микрофон ReSpeaker 2-Mics Pi HAT, то подключать кнопку не нужно, так как она уже встроена в этот модуль. Перейдите к следующему разделу.

### Подключение кнопки

Кнопка может быть подключена к базовому модулю Grove.

#### Задача - подключить кнопку

![Кнопка Grove](../../../../../translated_images/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.ru.png)

1. Вставьте один конец кабеля Grove в разъем на модуле кнопки. Он вставляется только в одном направлении.

1. С выключенным Raspberry Pi подключите другой конец кабеля Grove к цифровому разъему, обозначенному как **D5**, на базовом модуле Grove, подключенном к Pi. Этот разъем — второй слева в ряду разъемов рядом с GPIO-пинами.

![Кнопка Grove, подключенная к разъему D5](../../../../../translated_images/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.ru.png)

## Захват аудио

Вы можете захватывать аудио с микрофона, используя код на Python.

### Задача - захват аудио

1. Включите Pi и дождитесь его загрузки.

1. Запустите VS Code, либо непосредственно на Pi, либо подключившись через расширение Remote SSH.

1. Пакет PyAudio для Pip содержит функции для записи и воспроизведения аудио. Этот пакет зависит от некоторых аудиобиблиотек, которые нужно установить заранее. Выполните следующие команды в терминале для их установки:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Установите пакет PyAudio для Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Создайте новую папку с названием `smart-timer` и добавьте в нее файл с именем `app.py`.

1. Добавьте следующие импорты в начало этого файла:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Это импортирует модуль `pyaudio`, стандартные модули Python для работы с WAV-файлами, а также модуль `grove.factory` для импорта `Factory` для создания класса кнопки.

1. Ниже добавьте код для создания кнопки Grove.

    Если вы используете ReSpeaker 2-Mics Pi HAT, используйте следующий код:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Этот код создает кнопку на порту **D17**, к которому подключена кнопка на ReSpeaker 2-Mics Pi HAT. Эта кнопка настроена на отправку низкого сигнала при нажатии.

    Если вы не используете ReSpeaker 2-Mics Pi HAT, а используете кнопку Grove, подключенную к базовому модулю, используйте этот код:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Этот код создает кнопку на порту **D5**, настроенную на отправку высокого сигнала при нажатии.

1. Ниже создайте экземпляр класса PyAudio для работы с аудио:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Укажите номер аппаратной карты для микрофона и динамика. Это будет номер карты, который вы нашли, запустив команды `arecord -l` и `aplay -l` ранее в этом уроке.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Замените `<microphone card number>` на номер карты вашего микрофона.

    Замените `<speaker card number>` на номер карты вашего динамика, тот же номер, который вы указали в файле `alsa.conf`.

1. Ниже укажите частоту дискретизации для захвата и воспроизведения аудио. Возможно, вам придется изменить это значение в зависимости от используемого оборудования.

    ```python
    rate = 48000 #48KHz
    ```

    Если при запуске кода вы получите ошибки, связанные с частотой дискретизации, измените это значение на `44100` или `16000`. Чем выше значение, тем лучше качество звука.

1. Ниже создайте новую функцию с названием `capture_audio`. Она будет вызываться для захвата аудио с микрофона:

    ```python
    def capture_audio():
    ```

1. Внутри этой функции добавьте следующий код для захвата аудио:

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

    Этот код открывает входной аудиопоток с использованием объекта PyAudio. Поток будет захватывать аудио с микрофона с частотой 16 кГц, записывая его в буферы размером 4096 байт.

    Затем код выполняет цикл, пока кнопка Grove нажата, считывая эти буферы по 4096 байт в массив каждый раз.

    > 💁 Подробнее о параметрах, передаваемых методу `open`, можно прочитать в [документации PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    После того как кнопка отпущена, поток останавливается и закрывается.

1. Добавьте следующий код в конец этой функции:

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

    Этот код создает бинарный буфер и записывает все захваченное аудио в него как [WAV-файл](https://wikipedia.org/wiki/WAV). Это стандартный способ записи несжатого аудио в файл. Затем этот буфер возвращается.

1. Добавьте следующую функцию `play_audio` для воспроизведения аудиобуфера:

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

    Эта функция открывает другой аудиопоток, на этот раз для вывода — воспроизведения аудио. Она использует те же настройки, что и входной поток. Буфер открывается как WAV-файл и записывается в выходной поток кусками по 4096 байт, воспроизводя аудио. Затем поток закрывается.

1. Добавьте следующий код ниже функции `capture_audio`, чтобы выполнять цикл до нажатия кнопки. После нажатия кнопки аудио захватывается, а затем воспроизводится.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Запустите код. Нажмите кнопку и говорите в микрофон. Отпустите кнопку, когда закончите, и вы услышите запись.

    Вы можете получить некоторые ошибки ALSA при создании экземпляра PyAudio. Это связано с конфигурацией Pi для аудиоустройств, которых у вас нет. Эти ошибки можно игнорировать.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Если вы получите следующую ошибку:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    измените значение `rate` на 44100 или 16000.

> 💁 Вы можете найти этот код в папке [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Ваше приложение для записи аудио успешно работает!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия по обеспечению точности, автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.