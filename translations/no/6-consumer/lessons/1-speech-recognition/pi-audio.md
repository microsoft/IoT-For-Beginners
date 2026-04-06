# Ta opp lyd - Raspberry Pi

I denne delen av leksjonen skal du skrive kode for å ta opp lyd på din Raspberry Pi. Lydopptaket vil bli styrt av en knapp.

## Maskinvare

Raspberry Pi trenger en knapp for å kontrollere lydopptaket.

Knappen du skal bruke er en Grove-knapp. Dette er en digital sensor som slår et signal av eller på. Disse knappene kan konfigureres til å sende et høyt signal når knappen trykkes, og lavt når den ikke trykkes, eller lavt når den trykkes og høyt når den ikke trykkes.

Hvis du bruker en ReSpeaker 2-Mics Pi HAT som mikrofon, trenger du ikke å koble til en knapp, da denne HAT-en allerede har en innebygd knapp. Hopp til neste seksjon.

### Koble til knappen

Knappen kan kobles til Grove base-hatten.

#### Oppgave - koble til knappen

![En Grove-knapp](../../../../../translated_images/no/grove-button.a70cfbb809a85636.webp)

1. Sett den ene enden av en Grove-kabel inn i kontakten på knappemodulen. Den vil bare passe på én måte.

1. Med Raspberry Pi slått av, koble den andre enden av Grove-kabelen til den digitale kontakten merket **D5** på Grove Base-hatten som er festet til Pi-en. Denne kontakten er den andre fra venstre, på raden av kontakter ved siden av GPIO-pinnene.

![Grove-knappen koblet til kontakt D5](../../../../../translated_images/no/pi-button.c7a1a4f55943341c.webp)

## Ta opp lyd

Du kan ta opp lyd fra mikrofonen ved hjelp av Python-kode.

### Oppgave - ta opp lyd

1. Slå på Pi-en og vent til den starter opp.

1. Start VS Code, enten direkte på Pi-en, eller koble til via Remote SSH-utvidelsen.

1. PyAudio Pip-pakken har funksjoner for å ta opp og spille av lyd. Denne pakken er avhengig av noen lydbiblioteker som må installeres først. Kjør følgende kommandoer i terminalen for å installere disse:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Installer PyAudio Pip-pakken.

    ```sh
    pip3 install pyaudio
    ```

1. Opprett en ny mappe kalt `smart-timer` og legg til en fil kalt `app.py` i denne mappen.

1. Legg til følgende imports øverst i denne filen:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Dette importerer `pyaudio`-modulen, noen standard Python-moduler for å håndtere WAV-filer, og `grove.factory`-modulen for å importere en `Factory` for å opprette en knappklasse.

1. Under dette, legg til kode for å opprette en Grove-knapp.

    Hvis du bruker ReSpeaker 2-Mics Pi HAT, bruk følgende kode:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Dette oppretter en knapp på port **D17**, porten som knappen på ReSpeaker 2-Mics Pi HAT er koblet til. Denne knappen er satt til å sende et lavt signal når den trykkes.

    Hvis du ikke bruker ReSpeaker 2-Mics Pi HAT, men en Grove-knapp koblet til base-hatten, bruk denne koden:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Dette oppretter en knapp på port **D5** som er satt til å sende et høyt signal når den trykkes.

1. Under dette, opprett en instans av PyAudio-klassen for å håndtere lyd:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Angi maskinvarekortnummeret for mikrofonen og høyttaleren. Dette vil være nummeret på kortet du fant ved å kjøre `arecord -l` og `aplay -l` tidligere i denne leksjonen.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Erstatt `<microphone card number>` med nummeret på mikrofonens kort.

    Erstatt `<speaker card number>` med nummeret på høyttalerens kort, det samme nummeret du satte i `alsa.conf`-filen.

1. Under dette, angi samplingsfrekvensen som skal brukes for lydopptak og avspilling. Du må kanskje endre dette avhengig av maskinvaren du bruker.

    ```python
    rate = 48000 #48KHz
    ```

    Hvis du får feil relatert til samplingsfrekvens når du kjører denne koden senere, endre denne verdien til `44100` eller `16000`. Jo høyere verdi, desto bedre lydkvalitet.

1. Under dette, opprett en ny funksjon kalt `capture_audio`. Denne vil bli kalt for å ta opp lyd fra mikrofonen:

    ```python
    def capture_audio():
    ```

1. Inne i denne funksjonen, legg til følgende for å ta opp lyden:

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

    Denne koden åpner en lydinngangsstrøm ved hjelp av PyAudio-objektet. Denne strømmen vil ta opp lyd fra mikrofonen ved 16KHz, og fange den i buffere på 4096 byte.

    Koden går deretter i en løkke mens Grove-knappen er trykket, og leser disse 4096-byte-bufferne inn i en liste hver gang.

    > 💁 Du kan lese mer om alternativene som sendes til `open`-metoden i [PyAudio-dokumentasjonen](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Når knappen slippes, stoppes og lukkes strømmen.

1. Legg til følgende på slutten av denne funksjonen:

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

    Denne koden oppretter en binær buffer og skriver all den innspilte lyden til den som en [WAV-fil](https://wikipedia.org/wiki/WAV). Dette er en standard måte å skrive ukomprimert lyd til en fil. Denne bufferen returneres deretter.

1. Legg til følgende `play_audio`-funksjon for å spille av lyd fra bufferen:

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

    Denne funksjonen åpner en annen lydstrøm, denne gangen for utgang - for å spille av lyden. Den bruker de samme innstillingene som inngangsstrømmen. Bufferen åpnes deretter som en WAV-fil og skrives til utgangsstrømmen i 4096-byte-chunks, og spiller av lyden. Strømmen lukkes deretter.

1. Legg til følgende kode under `capture_audio`-funksjonen for å gå i en løkke til knappen trykkes. Når knappen trykkes, tas lyden opp og spilles deretter av.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Kjør koden. Trykk på knappen og snakk inn i mikrofonen. Slipp knappen når du er ferdig, og du vil høre opptaket.

    Du kan få noen ALSA-feil når PyAudio-instansen opprettes. Dette skyldes konfigurasjon på Pi-en for lydenheter du ikke har. Du kan ignorere disse feilene.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Hvis du får følgende feil:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    endre da `rate` til enten 44100 eller 16000.

> 💁 Du finner denne koden i [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi)-mappen.

😀 Programmet ditt for lydopptak var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.