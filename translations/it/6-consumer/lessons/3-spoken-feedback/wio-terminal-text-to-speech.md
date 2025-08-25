<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T17:48:42+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "it"
}
-->
# Testo in voce - Wio Terminal

In questa parte della lezione, convertirai il testo in voce per fornire un feedback vocale.

## Testo in voce

L'SDK dei servizi vocali che hai utilizzato nella lezione precedente per convertire la voce in testo può essere utilizzato anche per convertire il testo in voce.

## Ottenere un elenco di voci

Quando richiedi la sintesi vocale, devi specificare la voce da utilizzare, poiché la voce può essere generata utilizzando una varietà di opzioni diverse. Ogni lingua supporta una gamma di voci differenti, e puoi ottenere l'elenco delle voci supportate per ciascuna lingua dall'SDK dei servizi vocali. Qui entrano in gioco le limitazioni dei microcontrollori: la chiamata per ottenere l'elenco delle voci supportate dai servizi di sintesi vocale restituisce un documento JSON di oltre 77KB, troppo grande per essere elaborato dal Wio Terminal. Al momento della stesura, l'elenco completo contiene 215 voci, ciascuna definita da un documento JSON come il seguente:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

Questo JSON si riferisce alla voce **Aria**, che ha diversi stili vocali. Tutto ciò che serve per convertire il testo in voce è il nome breve, `en-US-AriaNeural`.

Invece di scaricare e decodificare l'intero elenco sul tuo microcontrollore, dovrai scrivere del codice serverless per recuperare l'elenco delle voci per la lingua che stai utilizzando e chiamarlo dal tuo Wio Terminal. Il tuo codice potrà quindi selezionare una voce appropriata dall'elenco, ad esempio la prima che trova.

### Attività - creare una funzione serverless per ottenere un elenco di voci

1. Apri il tuo progetto `smart-timer-trigger` in VS Code e apri il terminale assicurandoti che l'ambiente virtuale sia attivato. In caso contrario, termina e ricrea il terminale.

1. Apri il file `local.settings.json` e aggiungi le impostazioni per la chiave API del servizio vocale e la posizione:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Sostituisci `<key>` con la chiave API per la tua risorsa del servizio vocale. Sostituisci `<location>` con la posizione che hai utilizzato quando hai creato la risorsa del servizio vocale.

1. Aggiungi un nuovo trigger HTTP a questa app chiamato `get-voices` utilizzando il seguente comando all'interno del terminale di VS Code nella cartella principale del progetto dell'app delle funzioni:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Questo creerà un trigger HTTP chiamato `get-voices`.

1. Sostituisci il contenuto del file `__init__.py` nella cartella `get-voices` con il seguente:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Questo codice effettua una richiesta HTTP all'endpoint per ottenere le voci. L'elenco delle voci è un grande blocco di JSON con voci per tutte le lingue, quindi le voci per la lingua passata nel corpo della richiesta vengono filtrate, quindi il nome breve viene estratto e restituito come elenco JSON. Il nome breve è il valore necessario per convertire il testo in voce, quindi viene restituito solo questo valore.

    > 💁 Puoi modificare il filtro secondo necessità per selezionare solo le voci che desideri.

    Questo riduce la dimensione dei dati da 77KB (al momento della stesura) a un documento JSON molto più piccolo. Ad esempio, per le voci statunitensi, questo è di 408 byte.

1. Esegui la tua app delle funzioni localmente. Puoi quindi chiamarla utilizzando uno strumento come curl nello stesso modo in cui hai testato il trigger HTTP `text-to-timer`. Assicurati di passare la tua lingua come corpo JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Sostituisci `<language>` con la tua lingua, ad esempio `en-GB` o `zh-CN`.

> 💁 Puoi trovare questo codice nella cartella [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Attività - recuperare la voce dal tuo Wio Terminal

1. Apri il progetto `smart-timer` in VS Code se non è già aperto.

1. Apri il file di intestazione `config.h` e aggiungi l'URL per la tua app delle funzioni:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Sostituisci `<URL>` con l'URL per il trigger HTTP `get-voices` sulla tua app delle funzioni. Questo sarà lo stesso valore di `TEXT_TO_TIMER_FUNCTION_URL`, tranne per il fatto che il nome della funzione sarà `get-voices` invece di `text-to-timer`.

1. Crea un nuovo file nella cartella `src` chiamato `text_to_speech.h`. Questo verrà utilizzato per definire una classe per convertire il testo in voce.

1. Aggiungi le seguenti direttive di inclusione all'inizio del nuovo file `text_to_speech.h`:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Aggiungi il seguente codice sotto queste direttive per dichiarare la classe `TextToSpeech`, insieme a un'istanza che può essere utilizzata nel resto dell'applicazione:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Per chiamare la tua app delle funzioni, devi dichiarare un client WiFi. Aggiungi il seguente codice alla sezione `private` della classe:

    ```cpp
    WiFiClient _client;
    ```

1. Nella sezione `private`, aggiungi un campo per la voce selezionata:

    ```cpp
    String _voice;
    ```

1. Alla sezione `public`, aggiungi una funzione `init` che otterrà la prima voce:

    ```cpp
    void init()
    {
    }
    ```

1. Per ottenere le voci, è necessario inviare un documento JSON all'app delle funzioni con la lingua. Aggiungi il seguente codice alla funzione `init` per creare questo documento JSON:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Successivamente, crea un `HTTPClient`, quindi usalo per chiamare l'app delle funzioni per ottenere le voci, inviando il documento JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Sotto questo, aggiungi il codice per controllare il codice di risposta e, se è 200 (successo), estrai l'elenco delle voci, recuperando la prima dall'elenco:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Dopo questo, termina la connessione del client HTTP:

    ```cpp
    httpClient.end();
    ```

1. Apri il file `main.cpp` e aggiungi la seguente direttiva di inclusione all'inizio per includere questo nuovo file di intestazione:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Nella funzione `setup`, sotto la chiamata a `speechToText.init();`, aggiungi il seguente codice per inizializzare la classe `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Compila questo codice, caricalo sul tuo Wio Terminal e testalo tramite il monitor seriale. Assicurati che la tua app delle funzioni sia in esecuzione.

    Vedrai l'elenco delle voci disponibili restituito dall'app delle funzioni, insieme alla voce selezionata.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Convertire il testo in voce

Una volta che hai una voce da utilizzare, puoi usarla per convertire il testo in voce. Le stesse limitazioni di memoria con le voci si applicano anche quando si converte il testo in voce, quindi sarà necessario scrivere l'audio su una scheda SD pronto per essere riprodotto tramite il ReSpeaker.

> 💁 Nelle lezioni precedenti di questo progetto hai utilizzato la memoria flash per memorizzare l'audio catturato dal microfono. Questa lezione utilizza una scheda SD poiché è più facile riprodurre l'audio da essa utilizzando le librerie audio Seeed.

C'è anche un'altra limitazione da considerare: i dati audio disponibili dal servizio vocale e i formati supportati dal Wio Terminal. A differenza dei computer completi, le librerie audio per i microcontrollori possono essere molto limitate nei formati audio che supportano. Ad esempio, la libreria Seeed Arduino Audio che può riprodurre suoni tramite il ReSpeaker supporta solo audio con una frequenza di campionamento di 44,1KHz. I servizi vocali di Azure possono fornire audio in diversi formati, ma nessuno di essi utilizza questa frequenza di campionamento; forniscono solo 8KHz, 16KHz, 24KHz e 48KHz. Ciò significa che l'audio deve essere ricampionato a 44,1KHz, qualcosa che richiederebbe più risorse di quelle disponibili sul Wio Terminal, in particolare memoria.

Quando è necessario manipolare dati come questi, è spesso meglio utilizzare codice serverless, specialmente se i dati provengono da una chiamata web. Il Wio Terminal può chiamare una funzione serverless, passando il testo da convertire, e la funzione serverless può sia chiamare il servizio vocale per convertire il testo in voce, sia ricampionare l'audio alla frequenza di campionamento richiesta. Può quindi restituire l'audio nel formato necessario al Wio Terminal per essere memorizzato sulla scheda SD e riprodotto tramite il ReSpeaker.

### Attività - creare una funzione serverless per convertire il testo in voce

1. Apri il tuo progetto `smart-timer-trigger` in VS Code e apri il terminale assicurandoti che l'ambiente virtuale sia attivato. In caso contrario, termina e ricrea il terminale.

1. Aggiungi un nuovo trigger HTTP a questa app chiamato `text-to-speech` utilizzando il seguente comando all'interno del terminale di VS Code nella cartella principale del progetto dell'app delle funzioni:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Questo creerà un trigger HTTP chiamato `text-to-speech`.

1. Il pacchetto Pip [librosa](https://librosa.org) ha funzioni per ricampionare l'audio, quindi aggiungilo al file `requirements.txt`:

    ```sh
    librosa
    ```

    Una volta aggiunto, installa i pacchetti Pip utilizzando il seguente comando dal terminale di VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Se stai utilizzando Linux, incluso Raspberry Pi OS, potresti dover installare `libsndfile` con il seguente comando:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Per convertire il testo in voce, non puoi utilizzare direttamente la chiave API del servizio vocale, ma devi richiedere un token di accesso, utilizzando la chiave API per autenticare la richiesta del token di accesso. Apri il file `__init__.py` dalla cartella `text-to-speech` e sostituisci tutto il codice con il seguente:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Questo definisce le costanti per la posizione e la chiave del servizio vocale che verranno lette dalle impostazioni. Quindi definisce la funzione `get_access_token` che recupererà un token di accesso per il servizio vocale.

1. Sotto questo codice, aggiungi il seguente:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Questo definisce il trigger HTTP che converte il testo in voce. Estrae il testo da convertire, la lingua e la voce dal corpo JSON inviato alla richiesta, costruisce un SSML per richiedere la sintesi vocale, quindi chiama l'API REST pertinente autenticandosi utilizzando il token di accesso. Questa chiamata API REST restituisce l'audio codificato come file WAV mono a 16 bit e 48KHz, definito dal valore di `playback_format`, che viene inviato alla chiamata API REST.

    Questo viene quindi ricampionato da `librosa` da una frequenza di campionamento di 48KHz a una frequenza di campionamento di 44,1KHz, quindi questo audio viene salvato in un buffer binario che viene poi restituito.

1. Esegui la tua app delle funzioni localmente o distribuiscila nel cloud. Puoi quindi chiamarla utilizzando uno strumento come curl nello stesso modo in cui hai testato il trigger HTTP `text-to-timer`. Assicurati di passare la lingua, la voce e il testo come corpo JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Sostituisci `<language>` con la tua lingua, ad esempio `en-GB` o `zh-CN`. Sostituisci `<voice>` con la voce che desideri utilizzare. Sostituisci `<text>` con il testo che desideri convertire in voce. Puoi salvare l'output in un file e riprodurlo con qualsiasi lettore audio che supporti i file WAV.

    Ad esempio, per convertire "Hello" in voce utilizzando l'inglese americano con la voce Jenny Neural, con l'app delle funzioni in esecuzione localmente, puoi utilizzare il seguente comando curl:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Questo salverà l'audio in `hello.wav` nella directory corrente.

> 💁 Puoi trovare questo codice nella cartella [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Attività - recuperare l'audio dal tuo Wio Terminal

1. Apri il progetto `smart-timer` in VS Code se non è già aperto.

1. Apri il file di intestazione `config.h` e aggiungi l'URL per la tua app delle funzioni:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Sostituisci `<URL>` con l'URL per il trigger HTTP `text-to-speech` sulla tua app delle funzioni. Questo sarà lo stesso valore di `TEXT_TO_TIMER_FUNCTION_URL`, tranne per il fatto che il nome della funzione sarà `text-to-speech` invece di `text-to-timer`.

1. Apri il file di intestazione `text_to_speech.h` e aggiungi il seguente metodo alla sezione `public` della classe `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Al metodo `convertTextToSpeech`, aggiungi il seguente codice per creare il JSON da inviare all'app delle funzioni:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Questo scrive la lingua, la voce e il testo nel documento JSON, quindi lo serializza in una stringa.

1. Sotto questo, aggiungi il seguente codice per chiamare l'app delle funzioni:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Questo crea un HTTPClient, quindi effettua una richiesta POST utilizzando il documento JSON al trigger HTTP `text-to-speech`.

1. Se la chiamata funziona, i dati binari grezzi restituiti dalla chiamata all'app delle funzioni possono essere scritti in un file sulla scheda SD. Aggiungi il seguente codice per farlo:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Questo codice controlla la risposta e, se è 200 (successo), i dati binari vengono scritti in un file nella radice della scheda SD chiamato `SPEECH.WAV`.

1. Alla fine di questo metodo, chiudi la connessione HTTP:

    ```cpp
    httpClient.end();
    ```

1. Ora il testo da pronunciare può essere convertito in audio. Nel file `main.cpp`, aggiungi la seguente riga alla fine della funzione `say` per convertire il testo da pronunciare in audio:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Compito - riprodurre audio dal tuo Wio Terminal

**In arrivo**

## Distribuire la tua app di funzioni nel cloud

Il motivo per eseguire l'app di funzioni localmente è che il pacchetto Pip `librosa` su Linux ha una dipendenza da una libreria che non è installata di default e deve essere installata prima che l'app di funzioni possa funzionare. Le app di funzioni sono serverless - non ci sono server che puoi gestire direttamente, quindi non c'è modo di installare questa libreria in anticipo.

Il modo per farlo è invece distribuire la tua app di funzioni utilizzando un container Docker. Questo container viene distribuito dal cloud ogni volta che è necessario avviare una nuova istanza della tua app di funzioni (ad esempio, quando la domanda supera le risorse disponibili o se l'app di funzioni non è stata utilizzata per un po' di tempo ed è stata chiusa).

Puoi trovare le istruzioni per configurare un'app di funzioni e distribuirla tramite Docker nella [documentazione su come creare una funzione su Linux utilizzando un'immagine personalizzata su Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Una volta distribuita, puoi adattare il codice del tuo Wio Terminal per accedere a questa funzione:

1. Aggiungi il certificato di Azure Functions a `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Cambia tutti gli include di `<WiFiClient.h>` in `<WiFiClientSecure.h>`.

1. Modifica tutti i campi `WiFiClient` in `WiFiClientSecure`.

1. In ogni classe che ha un campo `WiFiClientSecure`, aggiungi un costruttore e imposta il certificato in quel costruttore:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.