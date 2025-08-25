<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-25T17:58:20+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "it"
}
-->
# Da voce a testo - Raspberry Pi

In questa parte della lezione, scriverai del codice per convertire la voce registrata nell'audio in testo utilizzando il servizio di riconoscimento vocale.

## Invia l'audio al servizio di riconoscimento vocale

L'audio può essere inviato al servizio di riconoscimento vocale utilizzando l'API REST. Per utilizzare il servizio, devi prima richiedere un token di accesso, quindi usare quel token per accedere all'API REST. Questi token di accesso scadono dopo 10 minuti, quindi il tuo codice dovrebbe richiederli regolarmente per assicurarsi che siano sempre aggiornati.

### Attività - ottenere un token di accesso

1. Apri il progetto `smart-timer` sul tuo Raspberry Pi.

1. Rimuovi la funzione `play_audio`. Non è più necessaria, poiché non vuoi che il timer intelligente ripeta ciò che hai detto.

1. Aggiungi il seguente import all'inizio del file `app.py`:

    ```python
    import requests
    ```

1. Aggiungi il seguente codice sopra il ciclo `while True` per dichiarare alcune impostazioni per il servizio di riconoscimento vocale:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Sostituisci `<key>` con la chiave API della tua risorsa del servizio di riconoscimento vocale. Sostituisci `<location>` con la posizione che hai utilizzato quando hai creato la risorsa del servizio di riconoscimento vocale.

    Sostituisci `<language>` con il nome della lingua che utilizzerai per parlare, ad esempio `en-GB` per l'inglese o `zn-HK` per il cantonese. Puoi trovare un elenco delle lingue supportate e dei loro nomi locali nella [documentazione sul supporto linguistico e vocale su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Sotto a questo, aggiungi la seguente funzione per ottenere un token di accesso:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Questa funzione chiama un endpoint per l'emissione del token, passando la chiave API come intestazione. La chiamata restituisce un token di accesso che può essere utilizzato per chiamare i servizi di riconoscimento vocale.

1. Sotto a questo, dichiara una funzione per convertire la voce registrata nell'audio in testo utilizzando l'API REST:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. All'interno di questa funzione, configura l'URL dell'API REST e le intestazioni:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Questo costruisce un URL utilizzando la posizione della risorsa del servizio di riconoscimento vocale. Poi popola le intestazioni con il token di accesso ottenuto dalla funzione `get_access_token`, così come il sample rate utilizzato per registrare l'audio. Infine, definisce alcuni parametri da passare con l'URL contenente la lingua dell'audio.

1. Sotto a questo, aggiungi il seguente codice per chiamare l'API REST e ottenere il testo:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Questo codice chiama l'URL e decodifica il valore JSON che arriva nella risposta. Il valore `RecognitionStatus` nella risposta indica se la chiamata è riuscita a estrarre correttamente la voce in testo, e se è `Success`, il testo viene restituito dalla funzione; altrimenti, viene restituita una stringa vuota.

1. Sopra il ciclo `while True:`, definisci una funzione per elaborare il testo restituito dal servizio di riconoscimento vocale. Per ora, questa funzione stamperà semplicemente il testo nella console.

    ```python
    def process_text(text):
        print(text)
    ```

1. Infine, sostituisci la chiamata a `play_audio` nel ciclo `while True` con una chiamata alla funzione `convert_speech_to_text`, passando il testo alla funzione `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Esegui il codice. Premi il pulsante e parla nel microfono. Rilascia il pulsante quando hai finito, e l'audio verrà convertito in testo e stampato nella console.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Prova diversi tipi di frasi, insieme a frasi in cui le parole suonano simili ma hanno significati diversi. Ad esempio, se stai parlando in inglese, dì "I want to buy two bananas and an apple too" e nota come utilizzerà il corretto "to", "two" e "too" in base al contesto della parola, non solo al suo suono.

> 💁 Puoi trovare questo codice nella cartella [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Il tuo programma di riconoscimento vocale è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.