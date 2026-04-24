# Spela in ljud - Raspberry Pi

I den här delen av lektionen kommer du att skriva kod för att spela in ljud på din Raspberry Pi. Ljudinspelningen kommer att styras av en knapp.

## Hårdvara

Raspberry Pi behöver en knapp för att styra ljudinspelningen.

Knappen du kommer att använda är en Grove-knapp. Detta är en digital sensor som slår på eller av en signal. Dessa knappar kan konfigureras för att skicka en hög signal när knappen trycks in, och låg när den inte är det, eller låg när den trycks in och hög när den inte är det.

Om du använder en ReSpeaker 2-Mics Pi HAT som mikrofon behöver du inte ansluta en knapp eftersom denna HAT redan har en inbyggd. Hoppa vidare till nästa avsnitt.

### Anslut knappen

Knappen kan anslutas till Grove Base HAT.

#### Uppgift - anslut knappen

![En Grove-knapp](../../../../../translated_images/sv/grove-button.a70cfbb809a85636.webp)

1. Sätt in ena änden av en Grove-kabel i uttaget på knappmodulen. Den går bara in på ett sätt.

1. Med Raspberry Pi avstängd, anslut den andra änden av Grove-kabeln till det digitala uttaget märkt **D5** på Grove Base HAT som är ansluten till Pi. Detta uttag är det andra från vänster, på raden av uttag bredvid GPIO-stiften.

![Grove-knappen ansluten till uttag D5](../../../../../translated_images/sv/pi-button.c7a1a4f55943341c.webp)

## Spela in ljud

Du kan spela in ljud från mikrofonen med hjälp av Python-kod.

### Uppgift - spela in ljud

1. Starta Pi och vänta tills den har startat upp.

1. Starta VS Code, antingen direkt på Pi eller anslut via Remote SSH-tillägget.

1. PyAudio Pip-paketet har funktioner för att spela in och spela upp ljud. Detta paket är beroende av vissa ljudbibliotek som måste installeras först. Kör följande kommandon i terminalen för att installera dessa:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Installera PyAudio Pip-paketet.

    ```sh
    pip3 install pyaudio
    ```

1. Skapa en ny mapp som heter `smart-timer` och lägg till en fil som heter `app.py` i denna mapp.

1. Lägg till följande imports högst upp i denna fil:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Detta importerar `pyaudio`-modulen, några standardmoduler i Python för att hantera wave-filer, och `grove.factory`-modulen för att importera en `Factory` för att skapa en knappklass.

1. Nedanför detta, lägg till kod för att skapa en Grove-knapp.

    Om du använder ReSpeaker 2-Mics Pi HAT, använd följande kod:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Detta skapar en knapp på port **D17**, porten som knappen på ReSpeaker 2-Mics Pi HAT är ansluten till. Denna knapp är inställd på att skicka en låg signal när den trycks in.

    Om du inte använder ReSpeaker 2-Mics Pi HAT, och istället använder en Grove-knapp ansluten till bas-HAT, använd denna kod:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Detta skapar en knapp på port **D5** som är inställd på att skicka en hög signal när den trycks in.

1. Nedanför detta, skapa en instans av PyAudio-klassen för att hantera ljud:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Deklarera hårdvarukortsnumret för mikrofonen och högtalaren. Detta kommer att vara numret på kortet du hittade genom att köra `arecord -l` och `aplay -l` tidigare i denna lektion.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Ersätt `<microphone card number>` med numret på ditt mikrofonkort.

    Ersätt `<speaker card number>` med numret på ditt högtalarkort, samma nummer som du angav i `alsa.conf`-filen.

1. Nedanför detta, deklarera samplingsfrekvensen som ska användas för ljudinspelning och uppspelning. Du kan behöva ändra detta beroende på vilken hårdvara du använder.

    ```python
    rate = 48000 #48KHz
    ```

    Om du får fel relaterade till samplingsfrekvens när du kör denna kod senare, ändra detta värde till `44100` eller `16000`. Ju högre värde, desto bättre ljudkvalitet.

1. Nedanför detta, skapa en ny funktion som heter `capture_audio`. Denna funktion kommer att anropas för att spela in ljud från mikrofonen:

    ```python
    def capture_audio():
    ```

1. Inuti denna funktion, lägg till följande för att spela in ljud:

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

    Denna kod öppnar en ljudingångsström med hjälp av PyAudio-objektet. Denna ström kommer att spela in ljud från mikrofonen vid 16 kHz, och lagra det i buffertar på 4096 byte.

    Koden loopar sedan medan Grove-knappen är intryckt, och läser dessa 4096-byte-buffertar till en array varje gång.

    > 💁 Du kan läsa mer om alternativen som skickas till `open`-metoden i [PyAudio-dokumentationen](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    När knappen släpps stoppas och stängs strömmen.

1. Lägg till följande i slutet av denna funktion:

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

    Denna kod skapar en binär buffert och skriver allt inspelat ljud till den som en [WAV-fil](https://wikipedia.org/wiki/WAV). Detta är ett standardformat för att skriva okomprimerat ljud till en fil. Bufferten returneras sedan.

1. Lägg till följande funktion `play_audio` för att spela upp ljudbufferten:

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

    Denna funktion öppnar en annan ljudström, denna gång för utgång - för att spela upp ljudet. Den använder samma inställningar som ingångsströmmen. Bufferten öppnas sedan som en wave-fil och skrivs till utgångsströmmen i 4096-byte-chunks, vilket spelar upp ljudet. Strömmen stängs sedan.

1. Lägg till följande kod nedanför `capture_audio`-funktionen för att loopa tills knappen trycks in. När knappen trycks in spelas ljudet in och spelas sedan upp.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Kör koden. Tryck på knappen och tala in i mikrofonen. Släpp knappen när du är klar, och du kommer att höra inspelningen.

    Du kan få några ALSA-fel när PyAudio-instansen skapas. Detta beror på konfigurationen på Pi för ljudenheter som du inte har. Du kan ignorera dessa fel.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Om du får följande fel:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    ändra då `rate` till antingen 44100 eller 16000.

> 💁 Du kan hitta denna kod i [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi)-mappen.

😀 Ditt ljudinspelningsprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.