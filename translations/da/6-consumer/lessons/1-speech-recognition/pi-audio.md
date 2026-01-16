<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T21:04:17+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "da"
}
-->
# Optag lyd - Raspberry Pi

I denne del af lektionen skal du skrive kode for at optage lyd på din Raspberry Pi. Lydoptagelsen vil blive styret af en knap.

## Hardware

Raspberry Pi'en har brug for en knap til at styre lydoptagelsen.

Den knap, du skal bruge, er en Grove-knap. Dette er en digital sensor, der tænder eller slukker et signal. Disse knapper kan konfigureres til at sende et højt signal, når knappen trykkes, og lavt, når den ikke trykkes, eller lavt, når den trykkes, og højt, når den ikke trykkes.

Hvis du bruger en ReSpeaker 2-Mics Pi HAT som mikrofon, behøver du ikke at tilslutte en knap, da denne HAT allerede har en indbygget knap. Spring til næste afsnit.

### Tilslut knappen

Knappen kan tilsluttes Grove-basen.

#### Opgave - tilslut knappen

![En Grove-knap](../../../../../translated_images/da/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Sæt den ene ende af et Grove-kabel i stikket på knapmodulet. Det kan kun sættes i på én måde.

1. Med Raspberry Pi'en slukket, tilslut den anden ende af Grove-kablet til det digitale stik mærket **D5** på Grove Base HAT'en, der er tilsluttet Pi'en. Dette stik er det andet fra venstre i rækken af stik ved siden af GPIO-pindene.

![Grove-knappen tilsluttet stik D5](../../../../../translated_images/da/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Optag lyd

Du kan optage lyd fra mikrofonen ved hjælp af Python-kode.

### Opgave - optag lyd

1. Tænd for Pi'en og vent, indtil den er startet op.

1. Start VS Code, enten direkte på Pi'en eller ved at oprette forbindelse via Remote SSH-udvidelsen.

1. PyAudio Pip-pakken har funktioner til at optage og afspille lyd. Denne pakke afhænger af nogle lydbiblioteker, der skal installeres først. Kør følgende kommandoer i terminalen for at installere dem:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Installer PyAudio Pip-pakken.

    ```sh
    pip3 install pyaudio
    ```

1. Opret en ny mappe kaldet `smart-timer`, og tilføj en fil kaldet `app.py` til denne mappe.

1. Tilføj følgende imports øverst i denne fil:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Dette importerer `pyaudio`-modulet, nogle standard Python-moduler til at håndtere WAV-filer, og `grove.factory`-modulet for at importere en `Factory` til at oprette en knapklasse.

1. Tilføj nedenunder kode for at oprette en Grove-knap.

    Hvis du bruger ReSpeaker 2-Mics Pi HAT, skal du bruge følgende kode:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Dette opretter en knap på port **D17**, som er den port, knappen på ReSpeaker 2-Mics Pi HAT er tilsluttet. Denne knap er indstillet til at sende et lavt signal, når den trykkes.

    Hvis du ikke bruger ReSpeaker 2-Mics Pi HAT, men en Grove-knap tilsluttet basen, skal du bruge denne kode:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Dette opretter en knap på port **D5**, der er indstillet til at sende et højt signal, når den trykkes.

1. Tilføj nedenunder en instans af PyAudio-klassen til at håndtere lyd:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Angiv hardwarekortnummeret for mikrofonen og højttaleren. Dette vil være nummeret på det kort, du fandt ved at køre `arecord -l` og `aplay -l` tidligere i denne lektion.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Erstat `<microphone card number>` med nummeret på dit mikrofonkort.

    Erstat `<speaker card number>` med nummeret på dit højttalerkort, det samme nummer, du angav i `alsa.conf`-filen.

1. Angiv nedenunder samplingsfrekvensen, der skal bruges til lydoptagelse og afspilning. Du kan muligvis ændre dette afhængigt af det hardware, du bruger.

    ```python
    rate = 48000 #48KHz
    ```

    Hvis du får fejl med samplingsfrekvensen, når du kører denne kode senere, skal du ændre denne værdi til `44100` eller `16000`. Jo højere værdi, desto bedre lydkvalitet.

1. Opret nedenunder en ny funktion kaldet `capture_audio`. Denne funktion vil blive kaldt for at optage lyd fra mikrofonen:

    ```python
    def capture_audio():
    ```

1. Indsæt følgende i denne funktion for at optage lyden:

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

    Denne kode åbner en lydinputstrøm ved hjælp af PyAudio-objektet. Denne strøm vil optage lyd fra mikrofonen ved 16KHz og gemme den i buffere på 4096 bytes.

    Koden kører i en løkke, mens Grove-knappen er trykket ned, og læser disse 4096-byte buffere ind i et array hver gang.

    > 💁 Du kan læse mere om de muligheder, der sendes til `open`-metoden, i [PyAudio-dokumentationen](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Når knappen slippes, stoppes og lukkes strømmen.

1. Tilføj følgende til slutningen af denne funktion:

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

    Denne kode opretter en binær buffer og skriver al den optagede lyd til den som en [WAV-fil](https://wikipedia.org/wiki/WAV). Dette er en standardmetode til at skrive ukomprimeret lyd til en fil. Bufferen returneres derefter.

1. Tilføj følgende `play_audio`-funktion for at afspille lydbufferen:

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

    Denne funktion åbner en anden lydstrøm, denne gang til output - for at afspille lyden. Den bruger de samme indstillinger som inputstrømmen. Bufferen åbnes derefter som en WAV-fil og skrives til outputstrømmen i 4096-byte stykker, hvilket afspiller lyden. Strømmen lukkes derefter.

1. Tilføj følgende kode nedenunder `capture_audio`-funktionen for at køre i en løkke, indtil knappen trykkes. Når knappen trykkes, optages lyden og afspilles derefter.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Kør koden. Tryk på knappen og tal ind i mikrofonen. Slip knappen, når du er færdig, og du vil høre optagelsen.

    Du kan få nogle ALSA-fejl, når PyAudio-instansen oprettes. Dette skyldes konfigurationen på Pi'en for lydenheder, du ikke har. Du kan ignorere disse fejl.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Hvis du får følgende fejl:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    skal du ændre `rate` til enten 44100 eller 16000.

> 💁 Du kan finde denne kode i [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi)-mappen.

😀 Dit lydoptagelsesprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.