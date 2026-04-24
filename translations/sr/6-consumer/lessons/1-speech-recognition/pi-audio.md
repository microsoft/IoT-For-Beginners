# Снимање звука - Raspberry Pi

У овом делу лекције, написаћете код за снимање звука на вашем Raspberry Pi уређају. Снимање звука ће се контролисати помоћу дугмета.

## Хардвер

Raspberry Pi захтева дугме за контролу снимања звука.

Дугме које ћете користити је Grove дугме. Ово је дигитални сензор који укључује или искључује сигнал. Ова дугмад могу бити конфигурисана да шаљу висок сигнал када се дугме притисне, а низак када није, или низак када се притисне и висок када није.

Ако користите ReSpeaker 2-Mics Pi HAT као микрофон, није потребно повезивати дугме јер овај HAT већ има уграђено дугме. Прескочите на следећи одељак.

### Повезивање дугмета

Дугме се може повезати на Grove базни HAT.

#### Задатак - повежите дугме

![Grove дугме](../../../../../translated_images/sr/grove-button.a70cfbb809a85636.webp)

1. Уметните један крај Grove кабла у утичницу на модулу дугмета. Кабл ће ући само у једном смеру.

1. Са искљученим Raspberry Pi уређајем, повежите други крај Grove кабла у дигиталну утичницу означену са **D5** на Grove базном HAT-у који је повезан са Pi уређајем. Ова утичница је друга с лева, у реду утичница поред GPIO пинова.

![Grove дугме повезано на утичницу D5](../../../../../translated_images/sr/pi-button.c7a1a4f55943341c.webp)

## Снимање звука

Можете снимати звук са микрофона користећи Python код.

### Задатак - снимање звука

1. Укључите Pi и сачекајте да се покрене.

1. Покрените VS Code, било директно на Pi уређају или се повежите преко Remote SSH екстензије.

1. PyAudio Pip пакет има функције за снимање и репродукцију звука. Овај пакет зависи од неких аудио библиотека које је потребно прво инсталирати. Покрените следеће команде у терминалу да бисте их инсталирали:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Инсталирајте PyAudio Pip пакет.

    ```sh
    pip3 install pyaudio
    ```

1. Направите нови фолдер под називом `smart-timer` и додајте датотеку под називом `app.py` у овај фолдер.

1. Додајте следеће увозе на врх ове датотеке:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Ово увози `pyaudio` модул, неке стандардне Python модуле за рад са WAV датотекама, и `grove.factory` модул за увоз `Factory` класе за креирање класе дугмета.

1. Испод овога, додајте код за креирање Grove дугмета.

    Ако користите ReSpeaker 2-Mics Pi HAT, користите следећи код:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Ово креира дугме на порту **D17**, порту на који је повезано дугме на ReSpeaker 2-Mics Pi HAT-у. Ово дугме је подешено да шаље низак сигнал када се притисне.

    Ако не користите ReSpeaker 2-Mics Pi HAT, већ Grove дугме повезано на базни HAT, користите овај код:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Ово креира дугме на порту **D5** које је подешено да шаље висок сигнал када се притисне.

1. Испод овога, креирајте инстанцу PyAudio класе за рад са звуком:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Декларишите број хардверске картице за микрофон и звучник. Ово ће бити број картице који сте пронашли покретањем `arecord -l` и `aplay -l` раније у овој лекцији.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Замените `<microphone card number>` бројем ваше микрофонске картице.

    Замените `<speaker card number>` бројем ваше звучничке картице, истим бројем који сте поставили у `alsa.conf` датотеци.

1. Испод овога, декларишите брзину узорковања за снимање и репродукцију звука. Можда ћете морати да промените ово у зависности од хардвера који користите.

    ```python
    rate = 48000 #48KHz
    ```

    Ако добијете грешке у брзини узорковања приликом покретања кода касније, промените ову вредност на `44100` или `16000`. Што је вредност већа, то је бољи квалитет звука.

1. Испод овога, креирајте нову функцију под називом `capture_audio`. Ова функција ће се позивати за снимање звука са микрофона:

    ```python
    def capture_audio():
    ```

1. Унутар ове функције, додајте следеће за снимање звука:

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

    Овај код отвара аудио улазни ток користећи PyAudio објекат. Овај ток ће снимати звук са микрофона на 16KHz, снимајући га у бафере величине 4096 бајтова.

    Код затим петља док је Grove дугме притиснуто, читајући ове бафере од 4096 бајтова у низ сваки пут.

    > 💁 Више о опцијама које се прослеђују `open` методи можете прочитати у [PyAudio документацији](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Када се дугме отпусти, ток се зауставља и затвара.

1. Додајте следеће на крај ове функције:

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

    Овај код креира бинарни бафер и записује сав снимљени звук у њега као [WAV датотеку](https://wikipedia.org/wiki/WAV). Ово је стандардни начин за записивање некомпресованог звука у датотеку. Овај бафер се затим враћа.

1. Додајте следећу функцију `play_audio` за репродукцију аудио бафера:

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

    Ова функција отвара још један аудио ток, овог пута за излаз - за репродукцију звука. Користи исте поставке као и улазни ток. Бафер се затим отвара као WAV датотека и записује у излазни ток у баферима од 4096 бајтова, репродукујући звук. Ток се затим затвара.

1. Додајте следећи код испод функције `capture_audio` за петљу док се дугме не притисне. Када се дугме притисне, звук се снима, а затим репродукује.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Покрените код. Притисните дугме и говорите у микрофон. Отпустите дугме када завршите, и чућете снимак.

    Можда ћете добити неке ALSA грешке када се PyAudio инстанца креира. Ово је због конфигурације на Pi уређају за аудио уређаје које немате. Можете игнорисати ове грешке.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Ако добијете следећу грешку:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    онда промените `rate` на 44100 или 16000.

> 💁 Овај код можете пронаћи у [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) фолдеру.

😀 Ваш програм за снимање звука је успешно завршен!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да превод буде тачан, молимо вас да имате у виду да аутоматизовани преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.