<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-25T17:36:43+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "it"
}
-->
# Tradurre il parlato - Wio Terminal

In questa parte della lezione, scriverai del codice per tradurre il testo utilizzando il servizio di traduzione.

## Convertire il testo in parlato utilizzando il servizio di traduzione

L'API REST del servizio di sintesi vocale non supporta traduzioni dirette. Tuttavia, puoi utilizzare il servizio Translator per tradurre il testo generato dal servizio di riconoscimento vocale e il testo della risposta vocale. Questo servizio dispone di un'API REST che puoi utilizzare per tradurre il testo, ma per semplificarne l'uso verrà incapsulato in un altro trigger HTTP nella tua app di funzioni.

### Attività - creare una funzione serverless per tradurre il testo

1. Apri il tuo progetto `smart-timer-trigger` in VS Code e apri il terminale assicurandoti che l'ambiente virtuale sia attivato. In caso contrario, chiudi e ricrea il terminale.

1. Apri il file `local.settings.json` e aggiungi le impostazioni per la chiave API del servizio Translator e la posizione:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Sostituisci `<key>` con la chiave API della tua risorsa del servizio Translator. Sostituisci `<location>` con la posizione che hai utilizzato quando hai creato la risorsa del servizio Translator.

1. Aggiungi un nuovo trigger HTTP a questa app chiamato `translate-text` utilizzando il seguente comando dal terminale di VS Code nella cartella principale del progetto dell'app di funzioni:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Questo creerà un trigger HTTP chiamato `translate-text`.

1. Sostituisci il contenuto del file `__init__.py` nella cartella `translate-text` con il seguente:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Questo codice estrae il testo e le lingue dalla richiesta HTTP. Successivamente, effettua una richiesta all'API REST del servizio Translator, passando le lingue come parametri per l'URL e il testo da tradurre come corpo. Infine, restituisce la traduzione.

1. Esegui localmente la tua app di funzioni. Puoi quindi chiamarla utilizzando uno strumento come curl nello stesso modo in cui hai testato il trigger HTTP `text-to-timer`. Assicurati di passare il testo da tradurre e le lingue come corpo JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Questo esempio traduce *Définir une minuterie de 30 secondes* dal francese all'inglese americano. Restituirà *Set a 30-second timer*.

> 💁 Puoi trovare questo codice nella cartella [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Attività - utilizzare la funzione Translator per tradurre il testo

1. Apri il progetto `smart-timer` in VS Code se non è già aperto.

1. Il tuo timer intelligente avrà impostate 2 lingue: la lingua del server utilizzata per addestrare LUIS (la stessa lingua è utilizzata anche per costruire i messaggi da comunicare all'utente) e la lingua parlata dall'utente. Aggiorna la costante `LANGUAGE` nel file di intestazione `config.h` per impostarla sulla lingua che verrà parlata dall'utente e aggiungi una nuova costante chiamata `SERVER_LANGUAGE` per la lingua utilizzata per addestrare LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Sostituisci `<user language>` con il nome della localizzazione della lingua che utilizzerai per parlare, ad esempio `fr-FR` per il francese o `zn-HK` per il cantonese.

    Sostituisci `<server language>` con il nome della localizzazione della lingua utilizzata per addestrare LUIS.

    Puoi trovare un elenco delle lingue supportate e dei loro nomi di localizzazione nella [documentazione sul supporto delle lingue e delle voci su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Se non parli più lingue, puoi utilizzare un servizio come [Bing Translate](https://www.bing.com/translator) o [Google Translate](https://translate.google.com) per tradurre dalla tua lingua preferita a una lingua a tua scelta. Questi servizi possono anche riprodurre l'audio del testo tradotto.
    >
    > Ad esempio, se addestri LUIS in inglese ma vuoi utilizzare il francese come lingua dell'utente, puoi tradurre frasi come "set a 2 minute and 27 second timer" dall'inglese al francese utilizzando Bing Translate, quindi utilizzare il pulsante **Ascolta traduzione** per pronunciare la traduzione nel tuo microfono.
    >
    > ![Il pulsante ascolta traduzione su Bing Translate](../../../../../translated_images/it/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Aggiungi la chiave API del servizio Translator e la posizione sotto `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Sostituisci `<KEY>` con la chiave API della tua risorsa del servizio Translator. Sostituisci `<LOCATION>` con la posizione che hai utilizzato quando hai creato la risorsa del servizio Translator.

1. Aggiungi l'URL del trigger del servizio Translator sotto `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Sostituisci `<URL>` con l'URL del trigger HTTP `translate-text` nella tua app di funzioni. Questo sarà lo stesso valore di `TEXT_TO_TIMER_FUNCTION_URL`, eccetto che il nome della funzione sarà `translate-text` invece di `text-to-timer`.

1. Aggiungi un nuovo file alla cartella `src` chiamato `text_translator.h`.

1. Questo nuovo file di intestazione `text_translator.h` conterrà una classe per tradurre il testo. Aggiungi il seguente codice a questo file per dichiarare questa classe:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Questo dichiara la classe `TextTranslator`, insieme a un'istanza di questa classe. La classe ha un unico campo per il client WiFi.

1. Nella sezione `public` di questa classe, aggiungi un metodo per tradurre il testo:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Questo metodo prende la lingua da cui tradurre e la lingua in cui tradurre. Quando si gestisce il parlato, il parlato verrà tradotto dalla lingua dell'utente alla lingua del server LUIS, e quando si forniscono risposte verrà tradotto dalla lingua del server LUIS alla lingua dell'utente.

1. In questo metodo, aggiungi il codice per costruire un corpo JSON contenente il testo da tradurre e le lingue:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Sotto questo, aggiungi il seguente codice per inviare il corpo all'app di funzioni serverless:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Successivamente, aggiungi il codice per ottenere la risposta:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Infine, aggiungi il codice per chiudere la connessione e restituire il testo tradotto:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Attività - tradurre il parlato riconosciuto e le risposte

1. Apri il file `main.cpp`.

1. Aggiungi una direttiva include nella parte superiore del file per il file di intestazione della classe `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Il testo pronunciato quando un timer viene impostato o scade deve essere tradotto. Per fare ciò, aggiungi il seguente codice come prima riga della funzione `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Questo tradurrà il testo nella lingua dell'utente.

1. Nella funzione `processAudio`, il testo viene recuperato dall'audio catturato con la chiamata `String text = speechToText.convertSpeechToText();`. Dopo questa chiamata, traduci il testo:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Questo tradurrà il testo dalla lingua dell'utente alla lingua utilizzata sul server.

1. Compila questo codice, caricalo sul tuo Wio Terminal e testalo tramite il monitor seriale. Una volta che vedi `Ready` nel monitor seriale, premi il pulsante C (quello sul lato sinistro, più vicino all'interruttore di accensione) e parla. Assicurati che la tua app di funzioni sia in esecuzione e richiedi un timer nella lingua dell'utente, parlando direttamente in quella lingua o utilizzando un'app di traduzione.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Puoi trovare questo codice nella cartella [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Il tuo programma per il timer multilingue è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.