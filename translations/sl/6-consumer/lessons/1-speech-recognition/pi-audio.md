<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-28T12:54:04+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "sl"
}
-->
# Zajem zvoka - Raspberry Pi

V tem delu lekcije boste napisali kodo za zajem zvoka na vašem Raspberry Pi. Zajem zvoka bo nadzorovan s pomočjo gumba.

## Strojna oprema

Raspberry Pi potrebuje gumb za nadzor zajema zvoka.

Gumb, ki ga boste uporabili, je Grove gumb. To je digitalni senzor, ki vklopi ali izklopi signal. Ti gumbi so lahko konfigurirani tako, da pošljejo visok signal, ko je gumb pritisnjen, in nizek, ko ni, ali obratno - nizek, ko je pritisnjen, in visok, ko ni.

Če uporabljate mikrofon ReSpeaker 2-Mics Pi HAT, ni potrebe po priključitvi gumba, saj ima ta HAT že vgrajen gumb. Preskočite na naslednji razdelek.

### Povežite gumb

Gumb lahko povežete na Grove osnovni HAT.

#### Naloga - povežite gumb

![Grove gumb](../../../../../translated_images/sl/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Vstavite en konec Grove kabla v vtičnico na modulu gumba. Kabel bo šel noter samo v eni smeri.

1. Ko je Raspberry Pi izklopljen, povežite drugi konec Grove kabla z digitalno vtičnico, označeno z **D5**, na Grove osnovnem HAT-u, ki je pritrjen na Pi. Ta vtičnica je druga z leve strani v vrsti vtičnic poleg GPIO pinov.

![Gumb povezan z vtičnico D5](../../../../../translated_images/sl/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Zajem zvoka

Zvok iz mikrofona lahko zajamete s pomočjo Python kode.

### Naloga - zajem zvoka

1. Vklopite Pi in počakajte, da se zažene.

1. Zaženite VS Code, bodisi neposredno na Pi-ju ali pa se povežite prek razširitve Remote SSH.

1. PyAudio Pip paket vsebuje funkcije za snemanje in predvajanje zvoka. Ta paket je odvisen od nekaterih zvočnih knjižnic, ki jih je treba najprej namestiti. Zaženite naslednje ukaze v terminalu, da jih namestite:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Namestite PyAudio Pip paket.

    ```sh
    pip3 install pyaudio
    ```

1. Ustvarite novo mapo z imenom `smart-timer` in dodajte datoteko z imenom `app.py` v to mapo.

1. Na vrh te datoteke dodajte naslednje uvoze:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    To uvozi modul `pyaudio`, nekatere standardne Python module za delo z WAV datotekami in modul `grove.factory` za uvoz `Factory` za ustvarjanje razreda gumba.

1. Pod tem dodajte kodo za ustvarjanje Grove gumba.

    Če uporabljate ReSpeaker 2-Mics Pi HAT, uporabite naslednjo kodo:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    To ustvari gumb na portu **D17**, na katerega je povezan gumb na ReSpeaker 2-Mics Pi HAT. Ta gumb je nastavljen tako, da pošlje nizek signal, ko je pritisnjen.

    Če ne uporabljate ReSpeaker 2-Mics Pi HAT in uporabljate Grove gumb, povezan na osnovni HAT, uporabite to kodo:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    To ustvari gumb na portu **D5**, ki je nastavljen tako, da pošlje visok signal, ko je pritisnjen.

1. Pod tem ustvarite instanco razreda PyAudio za upravljanje zvoka:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Določite številko strojne kartice za mikrofon in zvočnik. To bo številka kartice, ki ste jo našli z ukazoma `arecord -l` in `aplay -l` prej v tej lekciji.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Zamenjajte `<microphone card number>` s številko kartice vašega mikrofona.

    Zamenjajte `<speaker card number>` s številko kartice vašega zvočnika, isto številko, ki ste jo nastavili v datoteki `alsa.conf`.

1. Pod tem določite vzorčno frekvenco za zajem in predvajanje zvoka. To boste morda morali spremeniti glede na uporabljeno strojno opremo.

    ```python
    rate = 48000 #48KHz
    ```

    Če pri zagonu te kode kasneje dobite napake glede vzorčne frekvence, spremenite to vrednost na `44100` ali `16000`. Višja kot je vrednost, boljša je kakovost zvoka.

1. Pod tem ustvarite novo funkcijo z imenom `capture_audio`. Ta funkcija bo klicana za zajem zvoka iz mikrofona:

    ```python
    def capture_audio():
    ```

1. Znotraj te funkcije dodajte naslednje za zajem zvoka:

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

    Ta koda odpre vhodni zvočni tok z uporabo objekta PyAudio. Ta tok bo zajemal zvok iz mikrofona pri 16 kHz, zajemal ga bo v medpomnilnike velikosti 4096 bajtov.

    Koda nato zanko izvaja, dokler je Grove gumb pritisnjen, pri čemer bere te 4096-bajtne medpomnilnike v matriko ob vsakem času.

    > 💁 Več o možnostih, ki jih posredujete metodi `open`, lahko preberete v [dokumentaciji PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Ko je gumb sproščen, se tok ustavi in zapre.

1. Na konec te funkcije dodajte naslednje:

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

    Ta koda ustvari binarni medpomnilnik in vanj zapiše ves zajeti zvok kot [WAV datoteko](https://wikipedia.org/wiki/WAV). To je standarden način za zapisovanje nestisnjenega zvoka v datoteko. Ta medpomnilnik se nato vrne.

1. Dodajte naslednjo funkcijo `play_audio` za predvajanje zvočnega medpomnilnika:

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

    Ta funkcija odpre drug zvočni tok, tokrat za izhod - za predvajanje zvoka. Uporablja iste nastavitve kot vhodni tok. Medpomnilnik se nato odpre kot WAV datoteka in zapiše v izhodni tok v kosih velikosti 4096 bajtov, predvajajoč zvok. Tok se nato zapre.

1. Pod funkcijo `capture_audio` dodajte naslednjo kodo, ki bo zanko izvajala, dokler ni gumb pritisnjen. Ko je gumb pritisnjen, se zajame zvok in nato predvaja.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Zaženite kodo. Pritisnite gumb in govorite v mikrofon. Ko končate, sprostite gumb in slišali boste posnetek.

    Morda boste dobili nekaj ALSA napak, ko se ustvari instanca PyAudio. To je posledica konfiguracije na Pi-ju za zvočne naprave, ki jih nimate. Te napake lahko ignorirate.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Če dobite naslednjo napako:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    potem spremenite `rate` na 44100 ali 16000.

> 💁 To kodo lahko najdete v mapi [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Vaš program za snemanje zvoka je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitne nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.