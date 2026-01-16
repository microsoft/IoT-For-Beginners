<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-25T22:41:04+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "de"
}
-->
# Audio aufnehmen - Raspberry Pi

In diesem Teil der Lektion schreiben Sie Code, um Audio auf Ihrem Raspberry Pi aufzunehmen. Die Audioaufnahme wird durch einen Knopf gesteuert.

## Hardware

Der Raspberry Pi benötigt einen Knopf, um die Audioaufnahme zu steuern.

Der Knopf, den Sie verwenden werden, ist ein Grove-Knopf. Dies ist ein digitaler Sensor, der ein Signal ein- oder ausschaltet. Diese Knöpfe können so konfiguriert werden, dass sie ein hohes Signal senden, wenn der Knopf gedrückt wird, und ein niedriges Signal, wenn er nicht gedrückt wird, oder umgekehrt.

Wenn Sie ein ReSpeaker 2-Mics Pi HAT als Mikrofon verwenden, müssen Sie keinen Knopf anschließen, da dieses HAT bereits einen eingebauten Knopf hat. Überspringen Sie diesen Abschnitt und fahren Sie mit dem nächsten fort.

### Den Knopf anschließen

Der Knopf kann an das Grove Base Hat angeschlossen werden.

#### Aufgabe - Knopf anschließen

![Ein Grove-Knopf](../../../../../translated_images/de/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Stecken Sie ein Ende eines Grove-Kabels in die Buchse des Knopfmoduls. Es passt nur in einer Richtung hinein.

1. Schalten Sie den Raspberry Pi aus und verbinden Sie das andere Ende des Grove-Kabels mit der digitalen Buchse, die mit **D5** auf dem Grove Base Hat am Pi markiert ist. Diese Buchse ist die zweite von links in der Reihe der Buchsen neben den GPIO-Pins.

![Der Grove-Knopf, angeschlossen an Buchse D5](../../../../../translated_images/de/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Audio aufnehmen

Sie können Audio vom Mikrofon mit Python-Code aufnehmen.

### Aufgabe - Audio aufnehmen

1. Schalten Sie den Pi ein und warten Sie, bis er hochgefahren ist.

1. Starten Sie VS Code, entweder direkt auf dem Pi oder über die Remote SSH-Erweiterung.

1. Das PyAudio-Pip-Paket enthält Funktionen, um Audio aufzunehmen und wiederzugeben. Dieses Paket benötigt einige Audiobibliotheken, die zuerst installiert werden müssen. Führen Sie die folgenden Befehle im Terminal aus, um diese zu installieren:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Installieren Sie das PyAudio-Pip-Paket.

    ```sh
    pip3 install pyaudio
    ```

1. Erstellen Sie einen neuen Ordner namens `smart-timer` und fügen Sie eine Datei namens `app.py` zu diesem Ordner hinzu.

1. Fügen Sie die folgenden Importe am Anfang dieser Datei hinzu:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Dies importiert das `pyaudio`-Modul, einige Standard-Python-Module zur Verarbeitung von WAV-Dateien und das `grove.factory`-Modul, um eine `Factory` für die Erstellung einer Knopfklasse zu importieren.

1. Fügen Sie darunter Code hinzu, um einen Grove-Knopf zu erstellen.

    Wenn Sie das ReSpeaker 2-Mics Pi HAT verwenden, verwenden Sie den folgenden Code:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Dies erstellt einen Knopf an Port **D17**, dem Port, an den der Knopf des ReSpeaker 2-Mics Pi HAT angeschlossen ist. Dieser Knopf ist so eingestellt, dass er ein niedriges Signal sendet, wenn er gedrückt wird.

    Wenn Sie das ReSpeaker 2-Mics Pi HAT nicht verwenden und stattdessen einen Grove-Knopf am Base Hat angeschlossen haben, verwenden Sie diesen Code:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Dies erstellt einen Knopf an Port **D5**, der so eingestellt ist, dass er ein hohes Signal sendet, wenn er gedrückt wird.

1. Erstellen Sie darunter eine Instanz der PyAudio-Klasse, um Audio zu verarbeiten:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Deklarieren Sie die Hardware-Kartennummer für das Mikrofon und den Lautsprecher. Dies ist die Nummer der Karte, die Sie zuvor durch Ausführen von `arecord -l` und `aplay -l` gefunden haben.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Ersetzen Sie `<microphone card number>` durch die Nummer Ihrer Mikrofonkarte.

    Ersetzen Sie `<speaker card number>` durch die Nummer Ihrer Lautsprecherkarte, dieselbe Nummer, die Sie in der `alsa.conf`-Datei festgelegt haben.

1. Deklarieren Sie darunter die Abtastrate, die für die Audioaufnahme und -wiedergabe verwendet werden soll. Sie müssen diese möglicherweise je nach verwendeter Hardware ändern.

    ```python
    rate = 48000 #48KHz
    ```

    Wenn Sie später beim Ausführen dieses Codes Abtastratenfehler erhalten, ändern Sie diesen Wert auf `44100` oder `16000`. Je höher der Wert, desto besser die Klangqualität.

1. Erstellen Sie darunter eine neue Funktion namens `capture_audio`. Diese wird aufgerufen, um Audio vom Mikrofon aufzunehmen:

    ```python
    def capture_audio():
    ```

1. Fügen Sie innerhalb dieser Funktion den folgenden Code hinzu, um das Audio aufzunehmen:

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

    Dieser Code öffnet einen Audioeingabestream mit dem PyAudio-Objekt. Dieser Stream nimmt Audio vom Mikrofon mit 16 kHz auf und speichert es in Puffern von jeweils 4096 Bytes.

    Der Code läuft in einer Schleife, solange der Grove-Knopf gedrückt wird, und liest diese 4096-Byte-Puffer jedes Mal in ein Array ein.

    > 💁 Weitere Informationen zu den Optionen, die an die `open`-Methode übergeben werden, finden Sie in der [PyAudio-Dokumentation](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Sobald der Knopf losgelassen wird, wird der Stream gestoppt und geschlossen.

1. Fügen Sie am Ende dieser Funktion den folgenden Code hinzu:

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

    Dieser Code erstellt einen binären Puffer und schreibt alle aufgenommenen Audiodaten als [WAV-Datei](https://wikipedia.org/wiki/WAV). Dies ist eine Standardmethode, um unkomprimiertes Audio in eine Datei zu schreiben. Dieser Puffer wird dann zurückgegeben.

1. Fügen Sie die folgende Funktion `play_audio` hinzu, um den Audiopuffer wiederzugeben:

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

    Diese Funktion öffnet einen weiteren Audiostream, diesmal für die Ausgabe - um das Audio abzuspielen. Sie verwendet dieselben Einstellungen wie der Eingabestream. Der Puffer wird dann als WAV-Datei geöffnet und in 4096-Byte-Stücken in den Ausgabestream geschrieben, um das Audio abzuspielen. Der Stream wird anschließend geschlossen.

1. Fügen Sie den folgenden Code unterhalb der Funktion `capture_audio` hinzu, um in einer Schleife zu laufen, bis der Knopf gedrückt wird. Sobald der Knopf gedrückt wird, wird das Audio aufgenommen und anschließend abgespielt.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Führen Sie den Code aus. Drücken Sie den Knopf und sprechen Sie in das Mikrofon. Lassen Sie den Knopf los, wenn Sie fertig sind, und Sie hören die Aufnahme.

    Sie können einige ALSA-Fehler erhalten, wenn die PyAudio-Instanz erstellt wird. Dies liegt an der Konfiguration des Pi für Audiogeräte, die Sie nicht haben. Sie können diese Fehler ignorieren.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Wenn Sie den folgenden Fehler erhalten:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    ändern Sie die `rate` entweder auf 44100 oder 16000.

> 💁 Sie finden diesen Code im Ordner [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Ihr Audiorekorder-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.