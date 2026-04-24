# Tradurre il parlato - Dispositivo IoT Virtuale

In questa parte della lezione, scriverai del codice per tradurre il parlato durante la conversione in testo utilizzando il servizio di riconoscimento vocale, quindi tradurrai il testo utilizzando il servizio Translator prima di generare una risposta vocale.

## Utilizzare il servizio di riconoscimento vocale per tradurre il parlato

Il servizio di riconoscimento vocale può prendere il parlato e non solo convertirlo in testo nella stessa lingua, ma anche tradurre l'output in altre lingue.

### Attività - utilizzare il servizio di riconoscimento vocale per tradurre il parlato

1. Apri il progetto `smart-timer` in VS Code e assicurati che l'ambiente virtuale sia caricato nel terminale.

1. Aggiungi le seguenti istruzioni di importazione sotto gli import esistenti:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Questo importa le classi utilizzate per tradurre il parlato e una libreria `requests` che verrà utilizzata per effettuare una chiamata al servizio Translator più avanti in questa lezione.

1. Il tuo timer intelligente avrà impostate 2 lingue: la lingua del server utilizzata per addestrare LUIS (la stessa lingua è anche utilizzata per costruire i messaggi da comunicare all'utente) e la lingua parlata dall'utente. Aggiorna la variabile `language` per indicare la lingua che verrà parlata dall'utente e aggiungi una nuova variabile chiamata `server_language` per la lingua utilizzata per addestrare LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Sostituisci `<user language>` con il nome della locale della lingua che utilizzerai per parlare, ad esempio `fr-FR` per il francese o `zn-HK` per il cantonese.

    Sostituisci `<server language>` con il nome della locale della lingua utilizzata per addestrare LUIS.

    Puoi trovare un elenco delle lingue supportate e dei loro nomi di locale nella [documentazione sul supporto delle lingue e delle voci su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Se non parli più lingue, puoi utilizzare un servizio come [Bing Translate](https://www.bing.com/translator) o [Google Translate](https://translate.google.com) per tradurre dalla tua lingua preferita a una lingua a tua scelta. Questi servizi possono poi riprodurre l'audio del testo tradotto. Tieni presente che il riconoscitore vocale ignorerà alcuni output audio dal tuo dispositivo, quindi potresti dover utilizzare un dispositivo aggiuntivo per riprodurre il testo tradotto.
    >
    > Ad esempio, se addestri LUIS in inglese ma vuoi utilizzare il francese come lingua dell'utente, puoi tradurre frasi come "imposta un timer di 2 minuti e 27 secondi" dall'inglese al francese utilizzando Bing Translate, quindi utilizzare il pulsante **Ascolta traduzione** per pronunciare la traduzione nel tuo microfono.
    >
    > ![Il pulsante ascolta traduzione su Bing Translate](../../../../../translated_images/it/bing-translate.348aa796d6efe2a9.webp)

1. Sostituisci le dichiarazioni `recognizer_config` e `recognizer` con le seguenti:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Questo crea una configurazione di traduzione per riconoscere il parlato nella lingua dell'utente e creare traduzioni nella lingua dell'utente e del server. Successivamente utilizza questa configurazione per creare un riconoscitore di traduzione, un riconoscitore vocale che può tradurre l'output del riconoscimento vocale in più lingue.

    > 💁 La lingua originale deve essere specificata nei `target_languages`, altrimenti non otterrai alcuna traduzione.

1. Aggiorna la funzione `recognized`, sostituendo l'intero contenuto della funzione con il seguente:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Questo codice verifica se l'evento riconosciuto è stato attivato perché il parlato è stato tradotto (questo evento può essere attivato in altri momenti, ad esempio quando il parlato è stato riconosciuto ma non tradotto). Se il parlato è stato tradotto, trova la traduzione nel dizionario `args.result.translations` che corrisponde alla lingua del server.

    Il dizionario `args.result.translations` è indicizzato in base alla parte linguistica dell'impostazione della locale, non all'intera impostazione. Ad esempio, se richiedi una traduzione in `fr-FR` per il francese, il dizionario conterrà una voce per `fr`, non per `fr-FR`.

    Il testo tradotto viene quindi inviato all'IoT Hub.

1. Esegui questo codice per testare le traduzioni. Assicurati che la tua app di funzione sia in esecuzione e richiedi un timer nella lingua dell'utente, parlando direttamente in quella lingua o utilizzando un'app di traduzione.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Tradurre il testo utilizzando il servizio Translator

Il servizio di riconoscimento vocale non supporta la traduzione del testo in parlato, ma puoi utilizzare il servizio Translator per tradurre il testo. Questo servizio ha un'API REST che puoi utilizzare per tradurre il testo.

### Attività - utilizzare la risorsa Translator per tradurre il testo

1. Aggiungi la chiave API del Translator sotto la variabile `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Sostituisci `<key>` con la chiave API per la tua risorsa del servizio Translator.

1. Sopra la funzione `say`, definisci una funzione `translate_text` che tradurrà il testo dalla lingua del server alla lingua dell'utente:

    ```python
    def translate_text(text):
    ```

1. All'interno di questa funzione, definisci l'URL e gli header per la chiamata all'API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    L'URL per questa API non è specifico per la posizione, invece la posizione viene passata come header. La chiave API viene utilizzata direttamente, quindi a differenza del servizio di riconoscimento vocale non è necessario ottenere un token di accesso dall'API del token issuer.

1. Sotto questo, definisci i parametri e il corpo per la chiamata:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    I `params` definiscono i parametri da passare alla chiamata API, passando le lingue di origine e di destinazione. Questa chiamata tradurrà il testo dalla lingua `from` alla lingua `to`.

    Il `body` contiene il testo da tradurre. Questo è un array, poiché più blocchi di testo possono essere tradotti nella stessa chiamata.

1. Effettua la chiamata all'API REST e ottieni la risposta:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    La risposta che arriva è un array JSON, con un elemento che contiene le traduzioni. Questo elemento ha un array per le traduzioni di tutti gli elementi passati nel corpo.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Restituisci la proprietà `text` dalla prima traduzione del primo elemento nell'array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Aggiorna la funzione `say` per tradurre il testo da pronunciare prima che venga generato l'SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Questo codice stampa anche la versione originale e tradotta del testo nella console.

1. Esegui il tuo codice. Assicurati che la tua app di funzione sia in esecuzione e richiedi un timer nella lingua dell'utente, parlando direttamente in quella lingua o utilizzando un'app di traduzione.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 A causa dei diversi modi di esprimere qualcosa in lingue diverse, potresti ottenere traduzioni leggermente diverse dagli esempi forniti a LUIS. In tal caso, aggiungi più esempi a LUIS, riaddestra e ripubblica il modello.

> 💁 Puoi trovare questo codice nella cartella [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Il tuo programma di timer multilingue è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione AI [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale umana. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.