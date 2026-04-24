# Garso įrašymas - Raspberry Pi

Šioje pamokos dalyje rašysite kodą, skirtą garso įrašymui naudojant Raspberry Pi. Garso įrašymas bus valdomas mygtuku.

## Aparatinė įranga

Raspberry Pi reikalingas mygtukas, kad būtų galima valdyti garso įrašymą.

Naudojamas mygtukas yra Grove mygtukas. Tai skaitmeninis jutiklis, kuris įjungia arba išjungia signalą. Šiuos mygtukus galima sukonfigūruoti taip, kad jie siųstų aukštą signalą, kai mygtukas paspaustas, ir žemą, kai nepaspaustas, arba žemą, kai paspaustas, ir aukštą, kai nepaspaustas.

Jei kaip mikrofoną naudojate ReSpeaker 2-Mics Pi HAT, tuomet nereikia prijungti mygtuko, nes šis HAT jau turi integruotą mygtuką. Pereikite prie kitos skilties.

### Prijunkite mygtuką

Mygtukas gali būti prijungtas prie Grove bazinio HAT.

#### Užduotis - prijunkite mygtuką

![Grove mygtukas](../../../../../translated_images/lt/grove-button.a70cfbb809a85636.webp)

1. Įstatykite vieną Grove kabelio galą į lizdą ant mygtuko modulio. Kabelis įsistatys tik viena kryptimi.

1. Kai Raspberry Pi yra išjungtas, prijunkite kitą Grove kabelio galą prie skaitmeninio lizdo, pažymėto **D5**, ant Grove bazinio HAT, prijungto prie Pi. Šis lizdas yra antras iš kairės, eilėje šalia GPIO pinų.

![Grove mygtukas prijungtas prie lizdo D5](../../../../../translated_images/lt/pi-button.c7a1a4f55943341c.webp)

## Garso įrašymas

Garso įrašymą iš mikrofono galite atlikti naudodami Python kodą.

### Užduotis - įrašykite garsą

1. Įjunkite Pi ir palaukite, kol jis užsikraus.

1. Paleiskite VS Code tiesiogiai ant Pi arba prisijunkite per Remote SSH plėtinį.

1. PyAudio Pip paketas turi funkcijas garso įrašymui ir atkūrimui. Šis paketas priklauso nuo tam tikrų garso bibliotekų, kurias reikia įdiegti pirmiausia. Paleiskite šias komandas terminale, kad jas įdiegtumėte:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Įdiekite PyAudio Pip paketą.

    ```sh
    pip3 install pyaudio
    ```

1. Sukurkite naują aplanką pavadinimu `smart-timer` ir pridėkite failą pavadinimu `app.py` į šį aplanką.

1. Pridėkite šiuos importus failo viršuje:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Tai importuoja `pyaudio` modulį, kai kuriuos standartinius Python modulius, skirtus WAV failų apdorojimui, ir `grove.factory` modulį, kad būtų galima importuoti `Factory` klasę mygtuko kūrimui.

1. Po to pridėkite kodą Grove mygtuko sukūrimui.

    Jei naudojate ReSpeaker 2-Mics Pi HAT, naudokite šį kodą:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Tai sukuria mygtuką porte **D17**, kuris yra prijungtas prie ReSpeaker 2-Mics Pi HAT mygtuko. Šis mygtukas nustatytas siųsti žemą signalą, kai paspaustas.

    Jei nenaudojate ReSpeaker 2-Mics Pi HAT, o naudojate Grove mygtuką, prijungtą prie bazinio HAT, naudokite šį kodą:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Tai sukuria mygtuką porte **D5**, kuris nustatytas siųsti aukštą signalą, kai paspaustas.

1. Po to sukurkite PyAudio klasės instanciją, skirtą garso apdorojimui:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Nurodykite mikrofono ir garsiakalbio aparatūros kortelės numerį. Tai bus numeris, kurį radote paleidę `arecord -l` ir `aplay -l` anksčiau šioje pamokoje.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Pakeiskite `<microphone card number>` į savo mikrofono kortelės numerį.

    Pakeiskite `<speaker card number>` į savo garsiakalbio kortelės numerį, tą patį numerį, kurį nustatėte `alsa.conf` faile.

1. Po to nurodykite garso įrašymo ir atkūrimo pavyzdžių dažnį. Jums gali tekti pakeisti šią reikšmę, priklausomai nuo naudojamos aparatūros.

    ```python
    rate = 48000 #48KHz
    ```

    Jei vėliau paleidžiant kodą gausite pavyzdžių dažnio klaidų, pakeiskite šią reikšmę į `44100` arba `16000`. Kuo didesnė reikšmė, tuo geresnė garso kokybė.

1. Po to sukurkite naują funkciją pavadinimu `capture_audio`. Ji bus naudojama garso įrašymui iš mikrofono:

    ```python
    def capture_audio():
    ```

1. Šios funkcijos viduje pridėkite šį kodą garso įrašymui:

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

    Šis kodas atidaro garso įvesties srautą naudojant PyAudio objektą. Šis srautas įrašo garsą iš mikrofono 16KHz dažniu, įrašydamas jį į 4096 baitų dydžio buferius.

    Kodas tada kartojasi, kol Grove mygtukas yra paspaustas, kiekvieną kartą skaitydamas šiuos 4096 baitų buferius į masyvą.

    > 💁 Daugiau apie `open` metodo parametrus galite perskaityti [PyAudio dokumentacijoje](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Kai mygtukas atleidžiamas, srautas sustabdomas ir uždaromas.

1. Pridėkite šį kodą funkcijos pabaigoje:

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

    Šis kodas sukuria dvejetainį buferį ir įrašo visą įrašytą garsą į jį kaip [WAV failą](https://wikipedia.org/wiki/WAV). Tai standartinis būdas įrašyti nesuspaustą garsą į failą. Šis buferis tada grąžinamas.

1. Pridėkite šią `play_audio` funkciją, skirtą garso buferio atkūrimui:

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

    Ši funkcija atidaro kitą garso srautą, šį kartą išvesties - garso atkūrimui. Ji naudoja tuos pačius nustatymus kaip ir įvesties srautas. Buferis tada atidaromas kaip WAV failas ir įrašomas į išvesties srautą 4096 baitų dalimis, atkuriant garsą. Srautas tada uždaromas.

1. Pridėkite šį kodą po `capture_audio` funkcijos, kad ciklas kartotųsi, kol mygtukas bus paspaustas. Kai mygtukas paspaustas, garsas įrašomas, o tada atkuriamas.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Paleiskite kodą. Paspauskite mygtuką ir kalbėkite į mikrofoną. Atleiskite mygtuką, kai baigsite, ir išgirsite įrašą.

    Jūs galite gauti keletą ALSA klaidų, kai sukuriamas PyAudio instancija. Tai yra dėl Pi konfigūracijos garso įrenginiams, kurių neturite. Šias klaidas galite ignoruoti.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Jei gaunate šią klaidą:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    pakeiskite `rate` į 44100 arba 16000.

> 💁 Šį kodą galite rasti [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) aplanke.

😀 Jūsų garso įrašymo programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.