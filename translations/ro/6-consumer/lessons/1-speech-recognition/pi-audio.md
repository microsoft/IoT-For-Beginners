# Capturarea audio - Raspberry Pi

În această parte a lecției, vei scrie cod pentru a captura audio pe Raspberry Pi-ul tău. Capturarea audio va fi controlată de un buton.

## Hardware

Raspberry Pi-ul are nevoie de un buton pentru a controla capturarea audio.

Butonul pe care îl vei folosi este un buton Grove. Acesta este un senzor digital care activează sau dezactivează un semnal. Aceste butoane pot fi configurate să trimită un semnal ridicat atunci când butonul este apăsat și unul scăzut când nu este, sau invers - scăzut când este apăsat și ridicat când nu este.

Dacă folosești un microfon ReSpeaker 2-Mics Pi HAT, nu este nevoie să conectezi un buton, deoarece acest HAT are deja unul integrat. Treci direct la secțiunea următoare.

### Conectarea butonului

Butonul poate fi conectat la baza Grove hat.

#### Sarcină - conectează butonul

![Un buton Grove](../../../../../translated_images/ro/grove-button.a70cfbb809a85636.webp)

1. Introdu un capăt al unui cablu Grove în mufa de pe modulul butonului. Acesta va intra doar într-un singur sens.

1. Cu Raspberry Pi-ul oprit, conectează celălalt capăt al cablului Grove la mufa digitală marcată **D5** de pe baza Grove hat atașată la Pi. Această mufă este a doua de la stânga, pe rândul de mufe de lângă pini GPIO.

![Butonul Grove conectat la mufa D5](../../../../../translated_images/ro/pi-button.c7a1a4f55943341c.webp)

## Capturarea audio

Poți captura audio de la microfon folosind cod Python.

### Sarcină - capturează audio

1. Pornește Raspberry Pi-ul și așteaptă să se încarce sistemul.

1. Lansează VS Code, fie direct pe Pi, fie conectându-te prin extensia Remote SSH.

1. Pachetul PyAudio Pip are funcții pentru a înregistra și reda audio. Acest pachet depinde de câteva biblioteci audio care trebuie instalate mai întâi. Rulează următoarele comenzi în terminal pentru a le instala:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Instalează pachetul PyAudio Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Creează un nou folder numit `smart-timer` și adaugă un fișier numit `app.py` în acest folder.

1. Adaugă următoarele importuri la începutul acestui fișier:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Acestea importă modulul `pyaudio`, câteva module standard Python pentru a gestiona fișierele wave și modulul `grove.factory` pentru a importa o clasă `Factory` pentru a crea un buton.

1. Mai jos, adaugă cod pentru a crea un buton Grove.

    Dacă folosești ReSpeaker 2-Mics Pi HAT, folosește următorul cod:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Acest cod creează un buton pe portul **D17**, portul la care este conectat butonul de pe ReSpeaker 2-Mics Pi HAT. Acest buton este configurat să trimită un semnal scăzut când este apăsat.

    Dacă nu folosești ReSpeaker 2-Mics Pi HAT și folosești un buton Grove conectat la baza hat, folosește acest cod:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Acest cod creează un buton pe portul **D5**, configurat să trimită un semnal ridicat când este apăsat.

1. Mai jos, creează o instanță a clasei PyAudio pentru a gestiona audio-ul:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Declară numărul cardului hardware pentru microfon și difuzor. Acesta va fi numărul cardului pe care l-ai găsit rulând `arecord -l` și `aplay -l` mai devreme în această lecție.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Înlocuiește `<microphone card number>` cu numărul cardului microfonului tău.

    Înlocuiește `<speaker card number>` cu numărul cardului difuzorului tău, același număr pe care l-ai setat în fișierul `alsa.conf`.

1. Mai jos, declară rata de eșantionare pentru capturarea și redarea audio. Este posibil să fie nevoie să modifici această valoare în funcție de hardware-ul pe care îl folosești.

    ```python
    rate = 48000 #48KHz
    ```

    Dacă primești erori legate de rata de eșantionare când rulezi acest cod mai târziu, schimbă această valoare la `44100` sau `16000`. Cu cât valoarea este mai mare, cu atât calitatea sunetului este mai bună.

1. Mai jos, creează o nouă funcție numită `capture_audio`. Aceasta va fi apelată pentru a captura audio de la microfon:

    ```python
    def capture_audio():
    ```

1. În interiorul acestei funcții, adaugă următorul cod pentru a captura audio:

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

    Acest cod deschide un flux de intrare audio folosind obiectul PyAudio. Acest flux va captura audio de la microfon la 16KHz, capturându-l în buffer-uri de 4096 de octeți.

    Codul apoi intră într-un ciclu cât timp butonul Grove este apăsat, citind aceste buffer-uri de 4096 de octeți într-un array de fiecare dată.

    > 💁 Poți citi mai multe despre opțiunile transmise metodei `open` în [documentația PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Odată ce butonul este eliberat, fluxul este oprit și închis.

1. Adaugă următorul cod la finalul acestei funcții:

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

    Acest cod creează un buffer binar și scrie tot audio-ul capturat în acesta ca un [fișier WAV](https://wikipedia.org/wiki/WAV). Acesta este un mod standard de a scrie audio necomprimat într-un fișier. Buffer-ul este apoi returnat.

1. Adaugă următoarea funcție `play_audio` pentru a reda buffer-ul audio:

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

    Această funcție deschide un alt flux audio, de data aceasta pentru ieșire - pentru a reda audio-ul. Folosește aceleași setări ca fluxul de intrare. Buffer-ul este apoi deschis ca un fișier wave și scris în fluxul de ieșire în bucăți de 4096 de octeți, redând audio-ul. Fluxul este apoi închis.

1. Adaugă următorul cod sub funcția `capture_audio` pentru a intra într-un ciclu până când butonul este apăsat. Odată ce butonul este apăsat, audio-ul este capturat, apoi redat.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Rulează codul. Apasă butonul și vorbește în microfon. Eliberează butonul când ai terminat, iar înregistrarea va fi redată.

    Este posibil să primești câteva erori ALSA când instanța PyAudio este creată. Acest lucru se datorează configurației de pe Pi pentru dispozitive audio pe care nu le ai. Poți ignora aceste erori.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Dacă primești următoarea eroare:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    atunci schimbă `rate` la 44100 sau 16000.

> 💁 Poți găsi acest cod în folderul [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Programul tău de înregistrare audio a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.