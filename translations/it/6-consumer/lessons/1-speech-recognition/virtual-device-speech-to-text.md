<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-25T17:53:27+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "it"
}
-->
# Da voce a testo - Dispositivo IoT virtuale

In questa parte della lezione, scriverai del codice per convertire la voce catturata dal tuo microfono in testo utilizzando il servizio di riconoscimento vocale.

## Convertire voce in testo

Su Windows, Linux e macOS, l'SDK Python dei servizi vocali può essere utilizzato per ascoltare il tuo microfono e convertire in testo qualsiasi voce rilevata. Ascolterà in modo continuo, rilevando i livelli audio e inviando la voce per la conversione in testo quando il livello audio scende, ad esempio alla fine di un blocco di parlato.

### Attività - convertire voce in testo

1. Crea una nuova app Python sul tuo computer in una cartella chiamata `smart-timer` con un unico file chiamato `app.py` e un ambiente virtuale Python.

1. Installa il pacchetto Pip per i servizi vocali. Assicurati di installarlo da un terminale con l'ambiente virtuale attivato.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Se ricevi il seguente errore:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Dovrai aggiornare Pip. Fallo con il seguente comando, quindi prova a installare nuovamente il pacchetto:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Aggiungi i seguenti import al file `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Questo importa alcune classi utilizzate per riconoscere la voce.

1. Aggiungi il seguente codice per dichiarare alcune configurazioni:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Sostituisci `<key>` con la chiave API per il tuo servizio vocale. Sostituisci `<location>` con la posizione che hai utilizzato quando hai creato la risorsa del servizio vocale.

    Sostituisci `<language>` con il nome della lingua che utilizzerai per parlare, ad esempio `en-GB` per l'inglese o `zn-HK` per il cantonese. Puoi trovare un elenco delle lingue supportate e dei loro nomi locali nella [documentazione sul supporto linguistico e vocale su Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Questa configurazione viene quindi utilizzata per creare un oggetto `SpeechConfig` che sarà usato per configurare i servizi vocali.

1. Aggiungi il seguente codice per creare un riconoscitore vocale:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Il riconoscitore vocale funziona su un thread in background, ascoltando l'audio e convertendo qualsiasi voce in testo. Puoi ottenere il testo utilizzando una funzione di callback - una funzione che definisci e passi al riconoscitore. Ogni volta che viene rilevata una voce, il callback viene chiamato. Aggiungi il seguente codice per definire un callback e passarlo al riconoscitore, oltre a definire una funzione per elaborare il testo, scrivendolo nella console:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Il riconoscitore inizia ad ascoltare solo quando lo avvii esplicitamente. Aggiungi il seguente codice per avviare il riconoscimento. Questo funziona in background, quindi la tua applicazione avrà anche bisogno di un ciclo infinito che dorme per mantenere l'applicazione in esecuzione.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Esegui questa app. Parla nel tuo microfono e l'audio convertito in testo verrà mostrato nella console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Prova diversi tipi di frasi, insieme a frasi in cui le parole suonano uguali ma hanno significati diversi. Ad esempio, se stai parlando in inglese, dì "I want to buy two bananas and an apple too" e nota come utilizzerà correttamente "to", "two" e "too" in base al contesto della parola, non solo al suo suono.

> 💁 Puoi trovare questo codice nella cartella [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Il tuo programma di conversione da voce a testo è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.