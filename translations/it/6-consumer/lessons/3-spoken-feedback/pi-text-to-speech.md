<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-25T17:47:33+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "it"
}
-->
# Sintesi vocale - Raspberry Pi

In questa parte della lezione, scriverai del codice per convertire il testo in voce utilizzando il servizio di sintesi vocale.

## Convertire il testo in voce utilizzando il servizio di sintesi vocale

Il testo può essere inviato al servizio di sintesi vocale tramite l'API REST per ottenere un file audio che può essere riprodotto sul tuo dispositivo IoT. Quando richiedi la sintesi vocale, devi specificare la voce da utilizzare, poiché la voce può essere generata utilizzando una varietà di opzioni diverse.

Ogni lingua supporta una gamma di voci differenti, e puoi effettuare una richiesta REST al servizio di sintesi vocale per ottenere l'elenco delle voci supportate per ciascuna lingua.

### Attività - ottenere una voce

1. Apri il progetto `smart-timer` in VS Code.

1. Aggiungi il seguente codice sopra la funzione `say` per richiedere l'elenco delle voci per una lingua:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Questo codice definisce una funzione chiamata `get_voice` che utilizza il servizio di sintesi vocale per ottenere un elenco di voci. Successivamente, trova la prima voce che corrisponde alla lingua utilizzata.

    Questa funzione viene quindi chiamata per memorizzare la prima voce, e il nome della voce viene stampato nella console. Questa voce può essere richiesta una sola volta e il valore può essere utilizzato per ogni chiamata per convertire il testo in voce.

    > 💁 Puoi ottenere l'elenco completo delle voci supportate dalla [documentazione sul supporto delle lingue e delle voci su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Se desideri utilizzare una voce specifica, puoi rimuovere questa funzione e inserire direttamente il nome della voce dalla documentazione. Ad esempio:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Attività - convertire il testo in voce

1. Sotto questo, definisci una costante per il formato audio da recuperare dai servizi di sintesi vocale. Quando richiedi l'audio, puoi farlo in una gamma di formati diversi.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Il formato che puoi utilizzare dipende dal tuo hardware. Se ricevi errori di tipo `Invalid sample rate` durante la riproduzione dell'audio, cambia questo valore con un altro. Puoi trovare l'elenco dei valori supportati nella [documentazione dell'API REST per la sintesi vocale su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Dovrai utilizzare l'audio in formato `riff`, e i valori da provare sono `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` e `riff-48khz-16bit-mono-pcm`.

1. Sotto questo, dichiara una funzione chiamata `get_speech` che convertirà il testo in voce utilizzando l'API REST del servizio di sintesi vocale:

    ```python
    def get_speech(text):
    ```

1. Nella funzione `get_speech`, definisci l'URL da chiamare e gli header da passare:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Questo imposta gli header per utilizzare un token di accesso generato, definisce il contenuto come SSML e specifica il formato audio richiesto.

1. Sotto questo, definisci l'SSML da inviare all'API REST:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Questo SSML imposta la lingua e la voce da utilizzare, insieme al testo da convertire.

1. Infine, aggiungi del codice in questa funzione per effettuare la richiesta REST e restituire i dati audio in formato binario:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Attività - riprodurre l'audio

1. Sotto la funzione `get_speech`, definisci una nuova funzione per riprodurre l'audio restituito dalla chiamata all'API REST:

    ```python
    def play_speech(speech):
    ```

1. Il parametro `speech` passato a questa funzione sarà il dato audio binario restituito dall'API REST. Usa il seguente codice per aprire questo dato come file wave e passarlo a PyAudio per riprodurre l'audio:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Questo codice utilizza uno stream PyAudio, lo stesso utilizzato per catturare l'audio. La differenza qui è che lo stream è impostato come stream di output, e i dati vengono letti dall'audio e inviati allo stream.

    Invece di codificare manualmente i dettagli dello stream, come la frequenza di campionamento, questi vengono letti direttamente dai dati audio.

1. Sostituisci il contenuto della funzione `say` con il seguente:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Questo codice converte il testo in voce come dati audio binari e riproduce l'audio.

1. Esegui l'app e assicurati che l'applicazione della funzione sia in esecuzione. Imposta alcuni timer e sentirai una risposta vocale che ti informa che il timer è stato impostato, seguita da un'altra risposta vocale quando il timer è completato.

    Se ricevi errori di tipo `Invalid sample rate`, modifica il valore di `playback_format` come descritto sopra.

> 💁 Puoi trovare questo codice nella cartella [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Il tuo programma timer è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.