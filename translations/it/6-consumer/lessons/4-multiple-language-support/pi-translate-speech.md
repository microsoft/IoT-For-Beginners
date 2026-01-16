<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-25T17:39:13+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "it"
}
-->
# Tradurre il discorso - Raspberry Pi

In questa parte della lezione, scriverai codice per tradurre il testo utilizzando il servizio di traduzione.

## Convertire il testo in parlato utilizzando il servizio di traduzione

L'API REST del servizio di sintesi vocale non supporta traduzioni dirette, ma puoi utilizzare il servizio Translator per tradurre il testo generato dal servizio di riconoscimento vocale e il testo della risposta vocale. Questo servizio dispone di un'API REST che puoi utilizzare per tradurre il testo.

### Attività - utilizzare la risorsa Translator per tradurre il testo

1. Il tuo timer intelligente avrà impostate 2 lingue: la lingua del server utilizzata per addestrare LUIS (la stessa lingua è anche utilizzata per costruire i messaggi da comunicare all'utente) e la lingua parlata dall'utente. Aggiorna la variabile `language` con la lingua che sarà parlata dall'utente e aggiungi una nuova variabile chiamata `server_language` per la lingua utilizzata per addestrare LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Sostituisci `<user language>` con il nome della locale per la lingua che utilizzerai, ad esempio `fr-FR` per il francese o `zn-HK` per il cantonese.

    Sostituisci `<server language>` con il nome della locale per la lingua utilizzata per addestrare LUIS.

    Puoi trovare un elenco delle lingue supportate e dei loro nomi di locale nella [documentazione sul supporto delle lingue e delle voci su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Se non parli più lingue, puoi utilizzare un servizio come [Bing Translate](https://www.bing.com/translator) o [Google Translate](https://translate.google.com) per tradurre dalla tua lingua preferita a una lingua a tua scelta. Questi servizi possono anche riprodurre l'audio del testo tradotto.
    >
    > Ad esempio, se addestri LUIS in inglese ma vuoi utilizzare il francese come lingua utente, puoi tradurre frasi come "imposta un timer di 2 minuti e 27 secondi" dall'inglese al francese utilizzando Bing Translate, quindi utilizzare il pulsante **Ascolta traduzione** per pronunciare la traduzione nel microfono.
    >
    > ![Il pulsante Ascolta traduzione su Bing Translate](../../../../../translated_images/it/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Aggiungi la chiave API del servizio Translator sotto la variabile `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Sostituisci `<key>` con la chiave API per la risorsa del servizio Translator.

1. Sopra la funzione `say`, definisci una funzione `translate_text` che tradurrà il testo dalla lingua del server alla lingua dell'utente:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Le lingue di origine e destinazione vengono passate a questa funzione: la tua app deve convertire dalla lingua utente alla lingua del server quando riconosce il parlato e dalla lingua del server alla lingua utente quando fornisce un feedback vocale.

1. All'interno di questa funzione, definisci l'URL e gli header per la chiamata API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    L'URL per questa API non è specifico per la posizione; invece, la posizione viene passata come header. La chiave API viene utilizzata direttamente, quindi, a differenza del servizio di sintesi vocale, non è necessario ottenere un token di accesso dall'API di emissione token.

1. Sotto questo, definisci i parametri e il corpo della chiamata:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    I `params` definiscono i parametri da passare alla chiamata API, passando le lingue di origine e destinazione. Questa chiamata tradurrà il testo dalla lingua `from` alla lingua `to`.

    Il `body` contiene il testo da tradurre. Questo è un array, poiché è possibile tradurre più blocchi di testo nella stessa chiamata.

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
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Restituisci la proprietà `test` dalla prima traduzione del primo elemento nell'array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Aggiorna il ciclo `while True` per tradurre il testo dalla chiamata a `convert_speech_to_text` dalla lingua utente alla lingua del server:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Questo codice stampa anche le versioni originale e tradotta del testo nella console.

1. Aggiorna la funzione `say` per tradurre il testo da pronunciare dalla lingua del server alla lingua utente:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Questo codice stampa anche le versioni originale e tradotta del testo nella console.

1. Esegui il tuo codice. Assicurati che la tua funzione app sia in esecuzione e richiedi un timer nella lingua utente, parlando direttamente in quella lingua o utilizzando un'app di traduzione.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 A causa dei diversi modi di esprimere qualcosa in lingue diverse, potresti ottenere traduzioni leggermente diverse dagli esempi forniti a LUIS. In tal caso, aggiungi più esempi a LUIS, riaddestra e ripubblica il modello.

> 💁 Puoi trovare questo codice nella cartella [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Il tuo programma timer multilingue è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.