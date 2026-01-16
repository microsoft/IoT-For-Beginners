<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-25T17:50:25+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "it"
}
-->
# Acquisire audio - Raspberry Pi

In questa parte della lezione, scriverai del codice per acquisire audio sul tuo Raspberry Pi. L'acquisizione audio sarà controllata da un pulsante.

## Hardware

Il Raspberry Pi necessita di un pulsante per controllare l'acquisizione audio.

Il pulsante che utilizzerai è un pulsante Grove. Questo è un sensore digitale che attiva o disattiva un segnale. Questi pulsanti possono essere configurati per inviare un segnale alto quando il pulsante viene premuto e basso quando non lo è, oppure basso quando premuto e alto quando non lo è.

Se stai utilizzando un ReSpeaker 2-Mics Pi HAT come microfono, non è necessario collegare un pulsante poiché questo HAT ne ha già uno integrato. Passa alla sezione successiva.

### Collegare il pulsante

Il pulsante può essere collegato al Grove Base Hat.

#### Attività - collegare il pulsante

![Un pulsante Grove](../../../../../translated_images/it/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Inserisci un'estremità di un cavo Grove nella presa del modulo pulsante. Entrerà solo in un verso.

1. Con il Raspberry Pi spento, collega l'altra estremità del cavo Grove alla presa digitale contrassegnata **D5** sul Grove Base Hat collegato al Pi. Questa presa è la seconda da sinistra, nella fila di prese accanto ai pin GPIO.

![Il pulsante Grove collegato alla presa D5](../../../../../translated_images/it/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Acquisire audio

Puoi acquisire audio dal microfono utilizzando il codice Python.

### Attività - acquisire audio

1. Accendi il Pi e attendi che si avvii.

1. Avvia VS Code, direttamente sul Pi o connettendoti tramite l'estensione Remote SSH.

1. Il pacchetto PyAudio di Pip ha funzioni per registrare e riprodurre audio. Questo pacchetto dipende da alcune librerie audio che devono essere installate prima. Esegui i seguenti comandi nel terminale per installarle:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Installa il pacchetto PyAudio di Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Crea una nuova cartella chiamata `smart-timer` e aggiungi un file chiamato `app.py` a questa cartella.

1. Aggiungi le seguenti importazioni all'inizio di questo file:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Questo importa il modulo `pyaudio`, alcuni moduli standard di Python per gestire file wave e il modulo `grove.factory` per importare una `Factory` per creare una classe pulsante.

1. Sotto queste importazioni, aggiungi il codice per creare un pulsante Grove.

    Se stai utilizzando il ReSpeaker 2-Mics Pi HAT, usa il seguente codice:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Questo crea un pulsante sulla porta **D17**, la porta a cui è collegato il pulsante sul ReSpeaker 2-Mics Pi HAT. Questo pulsante è configurato per inviare un segnale basso quando premuto.

    Se non stai utilizzando il ReSpeaker 2-Mics Pi HAT e stai utilizzando un pulsante Grove collegato al Base Hat, usa questo codice:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Questo crea un pulsante sulla porta **D5** configurato per inviare un segnale alto quando premuto.

1. Sotto questo, crea un'istanza della classe PyAudio per gestire l'audio:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Dichiarare il numero della scheda hardware per il microfono e l'altoparlante. Questo sarà il numero della scheda che hai trovato eseguendo `arecord -l` e `aplay -l` in precedenza in questa lezione.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Sostituisci `<microphone card number>` con il numero della scheda del tuo microfono.

    Sostituisci `<speaker card number>` con il numero della scheda del tuo altoparlante, lo stesso numero che hai impostato nel file `alsa.conf`.

1. Sotto questo, dichiara la frequenza di campionamento da utilizzare per l'acquisizione e la riproduzione audio. Potrebbe essere necessario modificarla a seconda dell'hardware che stai utilizzando.

    ```python
    rate = 48000 #48KHz
    ```

    Se riscontri errori di frequenza di campionamento quando esegui questo codice, modifica questo valore a `44100` o `16000`. Più alto è il valore, migliore sarà la qualità del suono.

1. Sotto questo, crea una nuova funzione chiamata `capture_audio`. Questa sarà chiamata per acquisire audio dal microfono:

    ```python
    def capture_audio():
    ```

1. All'interno di questa funzione, aggiungi il seguente codice per acquisire l'audio:

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

    Questo codice apre un flusso di input audio utilizzando l'oggetto PyAudio. Questo flusso acquisirà audio dal microfono a 16KHz, catturandolo in buffer di 4096 byte.

    Il codice poi esegue un ciclo mentre il pulsante Grove è premuto, leggendo questi buffer di 4096 byte in un array ogni volta.

    > 💁 Puoi leggere di più sulle opzioni passate al metodo `open` nella [documentazione di PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Una volta che il pulsante viene rilasciato, il flusso viene fermato e chiuso.

1. Aggiungi il seguente codice alla fine di questa funzione:

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

    Questo codice crea un buffer binario e scrive tutto l'audio acquisito in esso come un file [WAV](https://wikipedia.org/wiki/WAV). Questo è un modo standard per scrivere audio non compresso in un file. Questo buffer viene poi restituito.

1. Aggiungi la seguente funzione `play_audio` per riprodurre il buffer audio:

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

    Questa funzione apre un altro flusso audio, questa volta per l'output - per riprodurre l'audio. Utilizza le stesse impostazioni del flusso di input. Il buffer viene poi aperto come file wave e scritto nel flusso di output in blocchi di 4096 byte, riproducendo l'audio. Il flusso viene poi chiuso.

1. Aggiungi il seguente codice sotto la funzione `capture_audio` per eseguire un ciclo fino a quando il pulsante viene premuto. Una volta premuto, l'audio viene acquisito e poi riprodotto.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Esegui il codice. Premi il pulsante e parla nel microfono. Rilascia il pulsante quando hai finito e sentirai la registrazione.

    Potresti ricevere alcuni errori ALSA quando viene creata l'istanza PyAudio. Questo è dovuto alla configurazione sul Pi per dispositivi audio che non possiedi. Puoi ignorare questi errori.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Se ricevi il seguente errore:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    allora modifica il valore di `rate` a 44100 o 16000.

> 💁 Puoi trovare questo codice nella cartella [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Il tuo programma di registrazione audio è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.