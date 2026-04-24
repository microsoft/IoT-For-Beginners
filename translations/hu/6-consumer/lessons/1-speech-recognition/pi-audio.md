# Hangrögzítés - Raspberry Pi

Ebben a leckében kódot fogsz írni, hogy hangot rögzíts a Raspberry Pi eszközödön. A hangrögzítést egy gombbal fogod vezérelni.

## Hardver

A Raspberry Pi-hoz szükség van egy gombra, amely vezérli a hangrögzítést.

Az általad használt gomb egy Grove gomb lesz. Ez egy digitális érzékelő, amely jelet kapcsol be vagy ki. Ezek a gombok úgy konfigurálhatók, hogy magas jelet küldjenek, amikor a gombot megnyomják, és alacsonyat, amikor nem, vagy fordítva: alacsonyat, amikor megnyomják, és magasat, amikor nem.

Ha ReSpeaker 2-Mics Pi HAT mikrofont használsz, akkor nincs szükség külön gomb csatlakoztatására, mivel ez a HAT már tartalmaz egyet. Ugorj a következő szakaszra.

### A gomb csatlakoztatása

A gomb csatlakoztatható a Grove alaplaphoz.

#### Feladat - a gomb csatlakoztatása

![Egy Grove gomb](../../../../../translated_images/hu/grove-button.a70cfbb809a85636.webp)

1. Illeszd be a Grove kábel egyik végét a gombmodul aljzatába. Csak egyféleképpen illeszkedik.

1. Kapcsold ki a Raspberry Pi-t, majd csatlakoztasd a Grove kábel másik végét a **D5** jelzésű digitális aljzathoz a Grove alaplapon, amely a Pi-hez van csatlakoztatva. Ez az aljzat a második balról, a GPIO tüskék melletti aljzatsoron.

![A Grove gomb csatlakoztatva a D5 aljzathoz](../../../../../translated_images/hu/pi-button.c7a1a4f55943341c.webp)

## Hang rögzítése

Python kód segítségével rögzíthetsz hangot a mikrofonról.

### Feladat - hang rögzítése

1. Kapcsold be a Pi-t, és várd meg, amíg elindul.

1. Indítsd el a VS Code-ot, akár közvetlenül a Pi-n, akár a Remote SSH bővítményen keresztül csatlakozva.

1. A PyAudio Pip csomag funkciókat biztosít a hang rögzítéséhez és visszajátszásához. Ez a csomag néhány hangkönyvtártól függ, amelyeket először telepíteni kell. Futtasd a következő parancsokat a terminálban ezek telepítéséhez:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Telepítsd a PyAudio Pip csomagot.

    ```sh
    pip3 install pyaudio
    ```

1. Hozz létre egy új mappát `smart-timer` néven, és adj hozzá egy `app.py` nevű fájlt ebbe a mappába.

1. Add hozzá a következő importokat a fájl tetejéhez:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Ez importálja a `pyaudio` modult, néhány szabványos Python modult a WAV fájlok kezeléséhez, valamint a `grove.factory` modult, hogy létrehozz egy gomb osztályt.

1. Ezután adj hozzá kódot egy Grove gomb létrehozásához.

    Ha ReSpeaker 2-Mics Pi HAT-ot használsz, használd a következő kódot:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Ez létrehoz egy gombot a **D17** porton, amelyhez a ReSpeaker 2-Mics Pi HAT gombja csatlakozik. Ez a gomb alacsony jelet küld, amikor megnyomják.

    Ha nem ReSpeaker 2-Mics Pi HAT-ot használsz, hanem egy Grove gombot, amely az alaplaphoz van csatlakoztatva, használd ezt a kódot:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Ez létrehoz egy gombot a **D5** porton, amely magas jelet küld, amikor megnyomják.

1. Ezután hozz létre egy PyAudio osztály példányt a hang kezeléséhez:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Add meg a mikrofon és a hangszóró hardverkártya számát. Ez az a szám, amelyet az `arecord -l` és `aplay -l` parancsok futtatásával találtál meg korábban ebben a leckében.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Cseréld ki a `<microphone card number>` helyére a mikrofon kártyaszámát.

    Cseréld ki a `<speaker card number>` helyére a hangszóró kártyaszámát, ugyanazt a számot, amelyet az `alsa.conf` fájlban beállítottál.

1. Ezután add meg a mintavételi frekvenciát, amelyet a hang rögzítéséhez és visszajátszásához használsz. Ezt a hardvered függvényében módosíthatod.

    ```python
    rate = 48000 #48KHz
    ```

    Ha mintavételi frekvencia hibákat kapsz a kód futtatásakor, változtasd meg ezt az értéket `44100` vagy `16000`-ra. Minél magasabb az érték, annál jobb a hangminőség.

1. Ezután hozz létre egy új `capture_audio` nevű függvényt. Ez a függvény felelős a mikrofonról érkező hang rögzítéséért:

    ```python
    def capture_audio():
    ```

1. A függvényen belül add hozzá a következőt a hang rögzítéséhez:

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

    Ez a kód megnyit egy hangbemeneti adatfolyamot a PyAudio objektum segítségével. Ez az adatfolyam 16 kHz-en rögzíti a hangot, 4096 bájtos puffer méretben.

    A kód addig ismétlődik, amíg a Grove gombot nyomva tartják, és minden alkalommal beolvassa ezeket a 4096 bájtos puffereket egy tömbbe.

    > 💁 További információt az `open` metódushoz átadott opciókról a [PyAudio dokumentációjában](https://people.csail.mit.edu/hubert/pyaudio/docs/) találsz.

    Amikor a gombot elengedik, az adatfolyam leáll és bezáródik.

1. Add hozzá a következőt a függvény végéhez:

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

    Ez a kód létrehoz egy bináris puffert, és az összes rögzített hangot WAV fájlként írja bele. Ez egy szabványos módja a tömörítetlen hang fájlba írásának. Ezután a puffer visszatér.

1. Add hozzá a következő `play_audio` függvényt a hangpuffer visszajátszásához:

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

    Ez a függvény megnyit egy másik hangadatfolyamot, ezúttal kimenetre - a hang lejátszásához. Ugyanazokat a beállításokat használja, mint a bemeneti adatfolyam. A puffer WAV fájlként nyílik meg, és 4096 bájtos darabokban íródik a kimeneti adatfolyamba, lejátszva a hangot. Az adatfolyam ezután bezáródik.

1. Add hozzá a következő kódot a `capture_audio` függvény alá, hogy addig ismétlődjön, amíg a gombot megnyomják. Amikor a gombot megnyomják, a hang rögzítésre kerül, majd lejátszásra kerül.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Futtasd a kódot. Nyomd meg a gombot, és beszélj a mikrofonba. Engedd el a gombot, amikor végeztél, és hallani fogod a felvételt.

    Előfordulhat, hogy néhány ALSA hibát kapsz, amikor a PyAudio példány létrejön. Ez a Pi konfigurációjából adódik olyan hangeszközökhöz, amelyek nincsenek csatlakoztatva. Ezeket a hibákat figyelmen kívül hagyhatod.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Ha a következő hibát kapod:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    akkor változtasd meg a `rate` értékét 44100-ra vagy 16000-re.

> 💁 Ezt a kódot megtalálod a [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) mappában.

😀 A hangrögzítő programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.