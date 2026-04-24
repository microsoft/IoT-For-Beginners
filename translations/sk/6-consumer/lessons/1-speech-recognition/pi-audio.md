# Zachytávanie zvuku - Raspberry Pi

V tejto časti lekcie napíšete kód na zachytávanie zvuku na vašom Raspberry Pi. Zachytávanie zvuku bude ovládané tlačidlom.

## Hardvér

Raspberry Pi potrebuje tlačidlo na ovládanie zachytávania zvuku.

Tlačidlo, ktoré použijete, je tlačidlo Grove. Ide o digitálny senzor, ktorý zapína alebo vypína signál. Tieto tlačidlá je možné nastaviť tak, aby posielali vysoký signál, keď je tlačidlo stlačené, a nízky, keď nie je, alebo nízky, keď je stlačené, a vysoký, keď nie je.

Ak používate ReSpeaker 2-Mics Pi HAT ako mikrofón, nie je potrebné pripojiť tlačidlo, pretože tento HAT už jedno tlačidlo obsahuje. Preskočte na ďalšiu sekciu.

### Pripojenie tlačidla

Tlačidlo je možné pripojiť k základnému HAT-u Grove.

#### Úloha - pripojenie tlačidla

![Tlačidlo Grove](../../../../../translated_images/sk/grove-button.a70cfbb809a85636.webp)

1. Zasuňte jeden koniec kábla Grove do zásuvky na module tlačidla. Pôjde to iba jedným spôsobom.

1. Pri vypnutom Raspberry Pi pripojte druhý koniec kábla Grove do digitálnej zásuvky označenej **D5** na základnom HAT-e Grove pripojenom k Pi. Táto zásuvka je druhá zľava v rade zásuviek vedľa GPIO pinov.

![Tlačidlo Grove pripojené k zásuvke D5](../../../../../translated_images/sk/pi-button.c7a1a4f55943341c.webp)

## Zachytávanie zvuku

Zvuk z mikrofónu môžete zachytiť pomocou kódu v Pythone.

### Úloha - zachytávanie zvuku

1. Zapnite Pi a počkajte, kým sa spustí.

1. Spustite VS Code, buď priamo na Pi, alebo sa pripojte cez rozšírenie Remote SSH.

1. Balík PyAudio Pip obsahuje funkcie na nahrávanie a prehrávanie zvuku. Tento balík závisí od niektorých zvukových knižníc, ktoré je potrebné najskôr nainštalovať. Spustite nasledujúce príkazy v termináli na ich inštaláciu:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Nainštalujte balík PyAudio Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Vytvorte nový priečinok s názvom `smart-timer` a pridajte do tohto priečinka súbor s názvom `app.py`.

1. Pridajte nasledujúce importy na začiatok tohto súboru:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Týmto sa importuje modul `pyaudio`, niektoré štandardné moduly Pythonu na prácu so súbormi WAV a modul `grove.factory` na importovanie `Factory` na vytvorenie triedy tlačidla.

1. Pod týmto pridajte kód na vytvorenie tlačidla Grove.

    Ak používate ReSpeaker 2-Mics Pi HAT, použite nasledujúci kód:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Týmto sa vytvorí tlačidlo na porte **D17**, porte, ku ktorému je pripojené tlačidlo na ReSpeaker 2-Mics Pi HAT. Toto tlačidlo je nastavené na posielanie nízkeho signálu, keď je stlačené.

    Ak nepoužívate ReSpeaker 2-Mics Pi HAT, ale používate tlačidlo Grove pripojené k základnému HAT-u, použite tento kód:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Týmto sa vytvorí tlačidlo na porte **D5**, ktoré je nastavené na posielanie vysokého signálu, keď je stlačené.

1. Pod týmto vytvorte inštanciu triedy PyAudio na prácu so zvukom:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Deklarujte číslo hardvérovej karty pre mikrofón a reproduktor. Toto bude číslo karty, ktoré ste našli spustením `arecord -l` a `aplay -l` skôr v tejto lekcii.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Nahraďte `<microphone card number>` číslom karty vášho mikrofónu.

    Nahraďte `<speaker card number>` číslom karty vášho reproduktora, rovnakým číslom, ktoré ste nastavili v súbore `alsa.conf`.

1. Pod týmto deklarujte vzorkovaciu frekvenciu na použitie pri zachytávaní a prehrávaní zvuku. Možno budete musieť túto hodnotu zmeniť v závislosti od hardvéru, ktorý používate.

    ```python
    rate = 48000 #48KHz
    ```

    Ak pri spustení tohto kódu neskôr dostanete chyby vzorkovacej frekvencie, zmeňte túto hodnotu na `44100` alebo `16000`. Čím vyššia hodnota, tým lepšia kvalita zvuku.

1. Pod týmto vytvorte novú funkciu s názvom `capture_audio`. Táto funkcia bude volaná na zachytávanie zvuku z mikrofónu:

    ```python
    def capture_audio():
    ```

1. Vo vnútri tejto funkcie pridajte nasledujúce na zachytávanie zvuku:

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

    Tento kód otvorí zvukový vstupný stream pomocou objektu PyAudio. Tento stream bude zachytávať zvuk z mikrofónu pri 16 kHz, zachytávajúc ho v blokoch o veľkosti 4096 bajtov.

    Kód potom opakovane číta tieto bloky o veľkosti 4096 bajtov do poľa, kým je tlačidlo Grove stlačené.

    > 💁 Viac o možnostiach odovzdávaných metóde `open` si môžete prečítať v [dokumentácii PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Po uvoľnení tlačidla sa stream zastaví a zatvorí.

1. Pridajte nasledujúce na koniec tejto funkcie:

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

    Tento kód vytvorí binárny buffer a zapíše všetok zachytený zvuk do neho ako [WAV súbor](https://wikipedia.org/wiki/WAV). Ide o štandardný spôsob zápisu nekomprimovaného zvuku do súboru. Tento buffer sa potom vráti.

1. Pridajte nasledujúcu funkciu `play_audio` na prehrávanie zvukového bufferu:

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

    Táto funkcia otvorí ďalší zvukový stream, tentoraz na výstup - na prehrávanie zvuku. Používa rovnaké nastavenia ako vstupný stream. Buffer sa potom otvorí ako súbor WAV a zapíše sa do výstupného streamu v blokoch o veľkosti 4096 bajtov, čím sa prehrá zvuk. Stream sa potom zatvorí.

1. Pridajte nasledujúci kód pod funkciu `capture_audio` na opakovanie, kým nie je tlačidlo stlačené. Po stlačení tlačidla sa zvuk zachytí a následne prehrá.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Spustite kód. Stlačte tlačidlo a hovorte do mikrofónu. Uvoľnite tlačidlo, keď skončíte, a budete počuť nahrávku.

    Môžete dostať niektoré chyby ALSA pri vytváraní inštancie PyAudio. Je to kvôli konfigurácii na Pi pre zvukové zariadenia, ktoré nemáte. Tieto chyby môžete ignorovať.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Ak dostanete nasledujúcu chybu:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    zmeňte hodnotu `rate` na buď 44100 alebo 16000.

> 💁 Tento kód nájdete v priečinku [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Váš program na nahrávanie zvuku bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za záväzný zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.