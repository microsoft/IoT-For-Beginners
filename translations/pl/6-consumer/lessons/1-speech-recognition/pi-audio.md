# Przechwytywanie dźwięku - Raspberry Pi

W tej części lekcji napiszesz kod do przechwytywania dźwięku na Raspberry Pi. Przechwytywanie dźwięku będzie kontrolowane za pomocą przycisku.

## Sprzęt

Raspberry Pi potrzebuje przycisku do kontrolowania przechwytywania dźwięku.

Przycisk, którego użyjesz, to przycisk Grove. Jest to cyfrowy sensor, który włącza lub wyłącza sygnał. Te przyciski można skonfigurować tak, aby wysyłały wysoki sygnał po naciśnięciu i niski, gdy nie są naciśnięte, lub niski po naciśnięciu i wysoki, gdy nie są naciśnięte.

Jeśli używasz mikrofonu ReSpeaker 2-Mics Pi HAT, nie musisz podłączać przycisku, ponieważ ten HAT ma już wbudowany przycisk. Przejdź do następnej sekcji.

### Podłączanie przycisku

Przycisk można podłączyć do podstawowego HAT-a Grove.

#### Zadanie - podłącz przycisk

![Przycisk Grove](../../../../../translated_images/pl/grove-button.a70cfbb809a85636.webp)

1. Włóż jeden koniec kabla Grove do gniazda na module przycisku. Kabel wejdzie tylko w jeden sposób.

1. Przy wyłączonym Raspberry Pi podłącz drugi koniec kabla Grove do cyfrowego gniazda oznaczonego **D5** na podstawowym HAT-cie Grove przymocowanym do Pi. To gniazdo jest drugie od lewej, w rzędzie gniazd obok pinów GPIO.

![Przycisk Grove podłączony do gniazda D5](../../../../../translated_images/pl/pi-button.c7a1a4f55943341c.webp)

## Przechwytywanie dźwięku

Możesz przechwytywać dźwięk z mikrofonu za pomocą kodu w Pythonie.

### Zadanie - przechwyć dźwięk

1. Włącz Raspberry Pi i poczekaj, aż się uruchomi.

1. Uruchom VS Code, bezpośrednio na Pi lub połącz się za pomocą rozszerzenia Remote SSH.

1. Pakiet PyAudio Pip zawiera funkcje do nagrywania i odtwarzania dźwięku. Ten pakiet wymaga zainstalowania kilku bibliotek audio. Uruchom następujące polecenia w terminalu, aby je zainstalować:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Zainstaluj pakiet PyAudio Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Utwórz nowy folder o nazwie `smart-timer` i dodaj do niego plik o nazwie `app.py`.

1. Dodaj następujące importy na początku tego pliku:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Importuje to moduł `pyaudio`, kilka standardowych modułów Pythona do obsługi plików WAV oraz moduł `grove.factory` do importowania klasy `Factory` w celu utworzenia klasy przycisku.

1. Poniżej dodaj kod do utworzenia przycisku Grove.

    Jeśli używasz ReSpeaker 2-Mics Pi HAT, użyj następującego kodu:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Tworzy to przycisk na porcie **D17**, do którego podłączony jest przycisk na ReSpeaker 2-Mics Pi HAT. Ten przycisk jest ustawiony na wysyłanie niskiego sygnału po naciśnięciu.

    Jeśli nie używasz ReSpeaker 2-Mics Pi HAT, a używasz przycisku Grove podłączonego do podstawowego HAT-a, użyj tego kodu:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Tworzy to przycisk na porcie **D5**, który jest ustawiony na wysyłanie wysokiego sygnału po naciśnięciu.

1. Poniżej utwórz instancję klasy PyAudio do obsługi dźwięku:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Zdeklaruj numer karty sprzętowej dla mikrofonu i głośnika. Będzie to numer karty, który znalazłeś, uruchamiając `arecord -l` i `aplay -l` wcześniej w tej lekcji.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Zamień `<microphone card number>` na numer karty mikrofonu.

    Zamień `<speaker card number>` na numer karty głośnika, ten sam numer, który ustawiłeś w pliku `alsa.conf`.

1. Poniżej zdeklaruj częstotliwość próbkowania do użycia podczas przechwytywania i odtwarzania dźwięku. Może być konieczne zmienienie tego w zależności od używanego sprzętu.

    ```python
    rate = 48000 #48KHz
    ```

    Jeśli podczas uruchamiania tego kodu pojawią się błędy związane z częstotliwością próbkowania, zmień tę wartość na `44100` lub `16000`. Im wyższa wartość, tym lepsza jakość dźwięku.

1. Poniżej utwórz nową funkcję o nazwie `capture_audio`. Będzie ona wywoływana w celu przechwytywania dźwięku z mikrofonu:

    ```python
    def capture_audio():
    ```

1. Wewnątrz tej funkcji dodaj następujący kod do przechwytywania dźwięku:

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

    Ten kod otwiera strumień wejściowy audio za pomocą obiektu PyAudio. Strumień ten przechwytuje dźwięk z mikrofonu z częstotliwością 16 kHz, przechwytując go w buforach o rozmiarze 4096 bajtów.

    Kod następnie pętli się, dopóki przycisk Grove jest naciśnięty, odczytując te bufory o rozmiarze 4096 bajtów do tablicy za każdym razem.

    > 💁 Więcej informacji o opcjach przekazywanych do metody `open` znajdziesz w [dokumentacji PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Po zwolnieniu przycisku strumień jest zatrzymywany i zamykany.

1. Dodaj następujący kod na końcu tej funkcji:

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

    Ten kod tworzy binarny bufor i zapisuje cały przechwycony dźwięk jako [plik WAV](https://wikipedia.org/wiki/WAV). Jest to standardowy sposób zapisywania nieskompresowanego dźwięku do pliku. Bufor ten jest następnie zwracany.

1. Dodaj następującą funkcję `play_audio`, aby odtworzyć bufor audio:

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

    Ta funkcja otwiera kolejny strumień audio, tym razem do wyjścia - aby odtworzyć dźwięk. Używa tych samych ustawień co strumień wejściowy. Bufor jest następnie otwierany jako plik WAV i zapisywany do strumienia wyjściowego w kawałkach o rozmiarze 4096 bajtów, odtwarzając dźwięk. Strumień jest następnie zamykany.

1. Dodaj następujący kod poniżej funkcji `capture_audio`, aby pętlić się, dopóki przycisk nie zostanie naciśnięty. Po naciśnięciu przycisku dźwięk jest przechwytywany, a następnie odtwarzany.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Uruchom kod. Naciśnij przycisk i mów do mikrofonu. Zwolnij przycisk, gdy skończysz, a usłyszysz nagranie.

    Możesz otrzymać pewne błędy ALSA podczas tworzenia instancji PyAudio. Wynika to z konfiguracji na Pi dla urządzeń audio, których nie masz. Możesz zignorować te błędy.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Jeśli otrzymasz następujący błąd:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    zmień wartość `rate` na 44100 lub 16000.

> 💁 Ten kod znajdziesz w folderze [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Twój program do nagrywania dźwięku zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.