# Snimanje zvuka - Raspberry Pi

U ovom dijelu lekcije napisat ćete kod za snimanje zvuka na vašem Raspberry Pi uređaju. Snimanje zvuka bit će kontrolirano pomoću gumba.

## Hardver

Raspberry Pi treba gumb za kontrolu snimanja zvuka.

Gumb koji ćete koristiti je Grove gumb. Ovo je digitalni senzor koji uključuje ili isključuje signal. Ovi gumbi mogu biti konfigurirani da šalju visoki signal kada je gumb pritisnut, a niski kada nije, ili niski kada je pritisnut i visoki kada nije.

Ako koristite ReSpeaker 2-Mics Pi HAT kao mikrofon, tada nije potrebno spajati gumb jer ovaj HAT već ima ugrađen gumb. Preskočite na sljedeći odjeljak.

### Spojite gumb

Gumb se može spojiti na Grove bazni HAT.

#### Zadatak - spojite gumb

![Grove gumb](../../../../../translated_images/hr/grove-button.a70cfbb809a85636.webp)

1. Umetnite jedan kraj Grove kabela u utičnicu na modulu gumba. Kabel će ući samo na jedan način.

1. S isključenim Raspberry Pi uređajem, spojite drugi kraj Grove kabela na digitalnu utičnicu označenu **D5** na Grove baznom HAT-u pričvršćenom na Pi. Ova utičnica je druga s lijeva, u redu utičnica pored GPIO pinova.

![Grove gumb spojen na utičnicu D5](../../../../../translated_images/hr/pi-button.c7a1a4f55943341c.webp)

## Snimanje zvuka

Možete snimati zvuk s mikrofona koristeći Python kod.

### Zadatak - snimanje zvuka

1. Uključite Pi i pričekajte da se pokrene.

1. Pokrenite VS Code, bilo izravno na Pi uređaju ili se povežite putem Remote SSH ekstenzije.

1. PyAudio Pip paket ima funkcije za snimanje i reprodukciju zvuka. Ovaj paket ovisi o nekim audio bibliotekama koje prvo treba instalirati. Pokrenite sljedeće naredbe u terminalu kako biste ih instalirali:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Instalirajte PyAudio Pip paket.

    ```sh
    pip3 install pyaudio
    ```

1. Kreirajte novu mapu pod nazivom `smart-timer` i dodajte datoteku pod nazivom `app.py` u ovu mapu.

1. Dodajte sljedeće uvoze na vrh ove datoteke:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Ovo uvozi modul `pyaudio`, neke standardne Python module za rad s WAV datotekama i modul `grove.factory` za uvoz `Factory` klase za kreiranje klase gumba.

1. Ispod ovoga, dodajte kod za kreiranje Grove gumba.

    Ako koristite ReSpeaker 2-Mics Pi HAT, koristite sljedeći kod:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Ovo kreira gumb na portu **D17**, portu na koji je povezan gumb na ReSpeaker 2-Mics Pi HAT-u. Ovaj gumb je postavljen da šalje niski signal kada je pritisnut.

    Ako ne koristite ReSpeaker 2-Mics Pi HAT, već koristite Grove gumb povezan na bazni HAT, koristite ovaj kod:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Ovo kreira gumb na portu **D5** koji je postavljen da šalje visoki signal kada je pritisnut.

1. Ispod ovoga, kreirajte instancu PyAudio klase za rad sa zvukom:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Deklarirajte broj hardverske kartice za mikrofon i zvučnik. Ovo će biti broj kartice koji ste pronašli pokretanjem `arecord -l` i `aplay -l` ranije u ovoj lekciji.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Zamijenite `<microphone card number>` brojem kartice vašeg mikrofona.

    Zamijenite `<speaker card number>` brojem kartice vašeg zvučnika, istim brojem koji ste postavili u datoteci `alsa.conf`.

1. Ispod ovoga, deklarirajte brzinu uzorkovanja za snimanje i reprodukciju zvuka. Možda ćete trebati promijeniti ovu vrijednost ovisno o hardveru koji koristite.

    ```python
    rate = 48000 #48KHz
    ```

    Ako dobijete greške vezane uz brzinu uzorkovanja prilikom pokretanja koda, promijenite ovu vrijednost na `44100` ili `16000`. Što je vrijednost veća, to je bolja kvaliteta zvuka.

1. Ispod ovoga, kreirajte novu funkciju pod nazivom `capture_audio`. Ova funkcija će se pozivati za snimanje zvuka s mikrofona:

    ```python
    def capture_audio():
    ```

1. Unutar ove funkcije, dodajte sljedeće za snimanje zvuka:

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

    Ovaj kod otvara ulazni audio stream koristeći PyAudio objekt. Ovaj stream će snimati zvuk s mikrofona na 16KHz, snimajući ga u međuspremnike veličine 4096 bajtova.

    Kod zatim ponavlja dok je Grove gumb pritisnut, čitajući ove međuspremnike od 4096 bajtova u niz svaki put.

    > 💁 Više o opcijama proslijeđenim metodi `open` možete pročitati u [PyAudio dokumentaciji](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Kada se gumb otpusti, stream se zaustavlja i zatvara.

1. Dodajte sljedeće na kraj ove funkcije:

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

    Ovaj kod kreira binarni međuspremnik i zapisuje sav snimljeni zvuk u njega kao [WAV datoteku](https://wikipedia.org/wiki/WAV). Ovo je standardni način zapisivanja nekomprimiranog zvuka u datoteku. Ovaj međuspremnik se zatim vraća.

1. Dodajte sljedeću funkciju `play_audio` za reprodukciju audio međuspremnika:

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

    Ova funkcija otvara drugi audio stream, ovaj put za izlaz - za reprodukciju zvuka. Koristi iste postavke kao i ulazni stream. Međuspremnik se zatim otvara kao WAV datoteka i zapisuje u izlazni stream u dijelovima od 4096 bajtova, reproducirajući zvuk. Stream se zatim zatvara.

1. Dodajte sljedeći kod ispod funkcije `capture_audio` za ponavljanje dok gumb nije pritisnut. Kada se gumb pritisne, zvuk se snima, a zatim reproducira.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Pokrenite kod. Pritisnite gumb i govorite u mikrofon. Otpustite gumb kada završite, i čut ćete snimku.

    Možda ćete dobiti neke ALSA greške kada se kreira PyAudio instanca. Ovo je zbog konfiguracije na Pi uređaju za audio uređaje koje nemate. Možete ignorirati ove greške.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Ako dobijete sljedeću grešku:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    tada promijenite `rate` na 44100 ili 16000.

> 💁 Ovaj kod možete pronaći u mapi [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Vaš program za snimanje zvuka je uspješno završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.