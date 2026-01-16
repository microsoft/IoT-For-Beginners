<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T21:20:34+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "cs"
}
-->
# Zachycení zvuku - Raspberry Pi

V této části lekce napíšete kód pro zachycení zvuku na vašem Raspberry Pi. Zachycení zvuku bude ovládáno tlačítkem.

## Hardware

Raspberry Pi potřebuje tlačítko pro ovládání zachycení zvuku.

Tlačítko, které použijete, je Grove tlačítko. Jedná se o digitální senzor, který zapíná nebo vypíná signál. Tato tlačítka lze nakonfigurovat tak, aby posílala vysoký signál, když je tlačítko stisknuto, a nízký, když není, nebo naopak nízký při stisknutí a vysoký, když není stisknuto.

Pokud používáte mikrofon ReSpeaker 2-Mics Pi HAT, není třeba připojovat tlačítko, protože tento HAT již jedno tlačítko obsahuje. Přeskočte na další sekci.

### Připojení tlačítka

Tlačítko lze připojit k základní desce Grove.

#### Úkol - připojte tlačítko

![Grove tlačítko](../../../../../translated_images/cs/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Zasuňte jeden konec Grove kabelu do konektoru na modulu tlačítka. Kabel lze zasunout pouze jedním způsobem.

1. S vypnutým Raspberry Pi připojte druhý konec Grove kabelu do digitálního konektoru označeného **D5** na základní desce Grove připojené k Pi. Tento konektor je druhý zleva v řadě konektorů vedle GPIO pinů.

![Grove tlačítko připojené ke konektoru D5](../../../../../translated_images/cs/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Zachycení zvuku

Zvuk z mikrofonu můžete zachytit pomocí Python kódu.

### Úkol - zachyťte zvuk

1. Zapněte Pi a počkejte, až se spustí.

1. Spusťte VS Code, buď přímo na Pi, nebo se připojte pomocí rozšíření Remote SSH.

1. Balíček PyAudio pro Pip obsahuje funkce pro nahrávání a přehrávání zvuku. Tento balíček závisí na některých zvukových knihovnách, které je třeba nejprve nainstalovat. Spusťte následující příkazy v terminálu pro jejich instalaci:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Nainstalujte balíček PyAudio pro Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Vytvořte novou složku s názvem `smart-timer` a přidejte do této složky soubor s názvem `app.py`.

1. Přidejte následující importy na začátek tohoto souboru:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Tím se importuje modul `pyaudio`, některé standardní Python moduly pro práci se soubory WAV a modul `grove.factory` pro import třídy `Factory` k vytvoření třídy tlačítka.

1. Pod tímto kódem přidejte kód pro vytvoření Grove tlačítka.

    Pokud používáte ReSpeaker 2-Mics Pi HAT, použijte následující kód:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Tím se vytvoří tlačítko na portu **D17**, což je port, ke kterému je připojeno tlačítko na ReSpeaker 2-Mics Pi HAT. Toto tlačítko je nastaveno tak, aby posílalo nízký signál při stisknutí.

    Pokud nepoužíváte ReSpeaker 2-Mics Pi HAT a používáte Grove tlačítko připojené k základní desce, použijte tento kód:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Tím se vytvoří tlačítko na portu **D5**, které je nastaveno tak, aby posílalo vysoký signál při stisknutí.

1. Pod tímto kódem vytvořte instanci třídy PyAudio pro práci se zvukem:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Deklarujte číslo hardwarové karty pro mikrofon a reproduktor. Toto bude číslo karty, které jste zjistili spuštěním příkazů `arecord -l` a `aplay -l` dříve v této lekci.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Nahraďte `<microphone card number>` číslem karty vašeho mikrofonu.

    Nahraďte `<speaker card number>` číslem karty vašeho reproduktoru, stejným číslem, které jste nastavili v souboru `alsa.conf`.

1. Pod tímto kódem deklarujte vzorkovací frekvenci pro zachycení a přehrávání zvuku. Možná budete muset tuto hodnotu změnit v závislosti na použitém hardwaru.

    ```python
    rate = 48000 #48KHz
    ```

    Pokud při spuštění tohoto kódu později obdržíte chyby vzorkovací frekvence, změňte tuto hodnotu na `44100` nebo `16000`. Čím vyšší hodnota, tím lepší kvalita zvuku.

1. Pod tímto kódem vytvořte novou funkci s názvem `capture_audio`. Tato funkce bude volána pro zachycení zvuku z mikrofonu:

    ```python
    def capture_audio():
    ```

1. Uvnitř této funkce přidejte následující kód pro zachycení zvuku:

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

    Tento kód otevře zvukový vstupní stream pomocí objektu PyAudio. Tento stream bude zachytávat zvuk z mikrofonu při 16 kHz, přičemž bude zachytávat data v blocích o velikosti 4096 bajtů.

    Kód poté opakovaně čte tyto 4096 bajtové bloky do pole, dokud je stisknuto Grove tlačítko.

    > 💁 Více o možnostech předávaných metodě `open` si můžete přečíst v [dokumentaci PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Jakmile je tlačítko uvolněno, stream se zastaví a zavře.

1. Na konec této funkce přidejte následující kód:

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

    Tento kód vytvoří binární buffer a zapíše do něj veškerý zachycený zvuk jako [WAV soubor](https://wikipedia.org/wiki/WAV). Jedná se o standardní způsob zápisu nekomprimovaného zvuku do souboru. Tento buffer je poté vrácen.

1. Přidejte následující funkci `play_audio` pro přehrání zvukového bufferu:

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

    Tato funkce otevře další zvukový stream, tentokrát pro výstup - přehrání zvuku. Používá stejná nastavení jako vstupní stream. Buffer je poté otevřen jako WAV soubor a zapisován do výstupního streamu v blocích o velikosti 4096 bajtů, čímž se přehrává zvuk. Stream je poté uzavřen.

1. Pod funkci `capture_audio` přidejte následující kód, který bude opakovaně čekat, dokud nebude stisknuto tlačítko. Jakmile je tlačítko stisknuto, zvuk se zachytí a poté přehraje.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Spusťte kód. Stiskněte tlačítko a mluvte do mikrofonu. Uvolněte tlačítko, až budete hotovi, a uslyšíte nahrávku.

    Můžete obdržet některé chyby ALSA při vytváření instance PyAudio. Tyto chyby jsou způsobeny konfigurací na Pi pro zvuková zařízení, která nemáte. Tyto chyby můžete ignorovat.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Pokud obdržíte následující chybu:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    změňte hodnotu `rate` na 44100 nebo 16000.

> 💁 Tento kód najdete ve složce [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Váš program pro nahrávání zvuku byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.