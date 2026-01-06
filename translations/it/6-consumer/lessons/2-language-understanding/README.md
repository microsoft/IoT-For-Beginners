<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-25T17:42:11+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "it"
}
-->
# Comprendere il linguaggio

![Una panoramica illustrata di questa lezione](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.it.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

## Quiz preliminare alla lezione

[Quiz preliminare alla lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Introduzione

Nella lezione precedente hai convertito il parlato in testo. Per utilizzare questo risultato per programmare un timer intelligente, il tuo codice dovrà comprendere ciò che è stato detto. Potresti supporre che l'utente utilizzi una frase fissa, come "Imposta un timer di 3 minuti", e analizzare quell'espressione per determinare la durata del timer. Tuttavia, questo approccio non è molto intuitivo. Se un utente dicesse "Imposta un timer per 3 minuti", tu o io capiremmo cosa intende, ma il tuo codice no, poiché si aspetterebbe una frase fissa.

È qui che entra in gioco la comprensione del linguaggio, utilizzando modelli di intelligenza artificiale per interpretare il testo e restituire i dettagli necessari. Ad esempio, essere in grado di comprendere sia "Imposta un timer di 3 minuti" sia "Imposta un timer per 3 minuti" e capire che è necessario un timer di 3 minuti.

In questa lezione imparerai i modelli di comprensione del linguaggio, come crearli, addestrarli e utilizzarli nel tuo codice.

In questa lezione tratteremo:

* [Comprensione del linguaggio](../../../../../6-consumer/lessons/2-language-understanding)
* [Creare un modello di comprensione del linguaggio](../../../../../6-consumer/lessons/2-language-understanding)
* [Intenzioni ed entità](../../../../../6-consumer/lessons/2-language-understanding)
* [Utilizzare il modello di comprensione del linguaggio](../../../../../6-consumer/lessons/2-language-understanding)

## Comprensione del linguaggio

Gli esseri umani utilizzano il linguaggio per comunicare da centinaia di migliaia di anni. Comunichiamo con parole, suoni o azioni e comprendiamo ciò che viene detto, sia il significato delle parole, dei suoni o delle azioni, sia il loro contesto. Comprendiamo sincerità e sarcasmo, permettendo alle stesse parole di avere significati diversi a seconda del tono della voce.

✅ Pensa ad alcune conversazioni che hai avuto di recente. Quanto di queste conversazioni sarebbe difficile da comprendere per un computer perché richiede contesto?

La comprensione del linguaggio, chiamata anche comprensione del linguaggio naturale, fa parte di un campo dell'intelligenza artificiale chiamato elaborazione del linguaggio naturale (o NLP) e si occupa della comprensione del testo, cercando di interpretare i dettagli di parole o frasi. Se utilizzi un assistente vocale come Alexa o Siri, hai già utilizzato servizi di comprensione del linguaggio. Questi sono i servizi di intelligenza artificiale dietro le quinte che convertono "Alexa, riproduci l'ultimo album di Taylor Swift" in mia figlia che balla in soggiorno sulle sue canzoni preferite.

> 💁 I computer, nonostante tutti i loro progressi, hanno ancora molta strada da fare per comprendere veramente il testo. Quando ci riferiamo alla comprensione del linguaggio con i computer, non intendiamo nulla di lontanamente avanzato come la comunicazione umana, ma piuttosto l'estrazione di dettagli chiave da alcune parole.

Come esseri umani, comprendiamo il linguaggio senza pensarci troppo. Se chiedessi a un altro essere umano di "riprodurre l'ultimo album di Taylor Swift", saprebbe istintivamente cosa intendo. Per un computer, questo è più difficile. Dovrebbe prendere le parole, convertite dal parlato in testo, e determinare i seguenti dettagli:

* La musica deve essere riprodotta
* La musica è dell'artista Taylor Swift
* La musica specifica è un intero album composto da più tracce in ordine
* Taylor Swift ha molti album, quindi devono essere ordinati cronologicamente e quello più recente è quello richiesto

✅ Pensa ad alcune frasi che hai pronunciato facendo richieste, come ordinare un caffè o chiedere a un familiare di passarti qualcosa. Prova a scomporle nei dettagli che un computer dovrebbe estrarre per comprendere la frase.

I modelli di comprensione del linguaggio sono modelli di intelligenza artificiale addestrati per estrarre determinati dettagli dal linguaggio e vengono poi addestrati per compiti specifici utilizzando il trasferimento di apprendimento, nello stesso modo in cui hai addestrato un modello di visione personalizzato utilizzando un piccolo set di immagini. Puoi prendere un modello e poi addestrarlo utilizzando il testo che vuoi che comprenda.

## Creare un modello di comprensione del linguaggio

![Il logo di LUIS](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.it.png)

Puoi creare modelli di comprensione del linguaggio utilizzando LUIS, un servizio di comprensione del linguaggio di Microsoft che fa parte dei Servizi Cognitivi.

### Attività - creare una risorsa di authoring

Per utilizzare LUIS, devi creare una risorsa di authoring.

1. Usa il seguente comando per creare una risorsa di authoring nel tuo gruppo di risorse `smart-timer`:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Sostituisci `<location>` con la posizione che hai utilizzato quando hai creato il gruppo di risorse.

    > ⚠️ LUIS non è disponibile in tutte le regioni, quindi se ricevi il seguente errore:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > scegli una regione diversa.

    Questo creerà una risorsa di authoring LUIS di livello gratuito.

### Attività - creare un'app di comprensione del linguaggio

1. Apri il portale LUIS su [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) nel tuo browser e accedi con lo stesso account che hai utilizzato per Azure.

1. Segui le istruzioni nella finestra di dialogo per selezionare il tuo abbonamento Azure, quindi seleziona la risorsa `smart-timer-luis-authoring` che hai appena creato.

1. Dalla lista *Conversation apps*, seleziona il pulsante **New app** per creare una nuova applicazione. Dai alla nuova app il nome `smart-timer` e imposta la *Culture* sulla tua lingua.

    > 💁 C'è un campo per una risorsa di previsione. Puoi creare una seconda risorsa solo per la previsione, ma la risorsa di authoring gratuita consente 1.000 previsioni al mese, che dovrebbero essere sufficienti per lo sviluppo, quindi puoi lasciare questo campo vuoto.

1. Leggi la guida che appare una volta creata l'app per comprendere i passaggi necessari per addestrare il modello di comprensione del linguaggio. Chiudi questa guida quando hai finito.

## Intenzioni ed entità

La comprensione del linguaggio si basa su *intenzioni* ed *entità*. Le intenzioni rappresentano ciò che si intende fare con le parole, ad esempio riprodurre musica, impostare un timer o ordinare cibo. Le entità rappresentano ciò a cui si riferisce l'intenzione, come l'album, la durata del timer o il tipo di cibo. Ogni frase interpretata dal modello dovrebbe avere almeno un'intenzione e, facoltativamente, una o più entità.

Alcuni esempi:

| Frase                                              | Intenzione        | Entità                                      |
| -------------------------------------------------- | ----------------- | ------------------------------------------- |
| "Riproduci l'ultimo album di Taylor Swift"         | *riprodurre musica* | *l'ultimo album di Taylor Swift*            |
| "Imposta un timer di 3 minuti"                     | *impostare un timer* | *3 minuti*                                  |
| "Annulla il mio timer"                             | *annullare un timer* | Nessuna                                     |
| "Ordina 3 pizze grandi all'ananas e un'insalata Caesar" | *ordinare cibo*    | *3 pizze grandi all'ananas*, *insalata Caesar* |

✅ Con le frasi che hai pensato prima, quale sarebbe l'intenzione e quali sarebbero le entità in quella frase?

Per addestrare LUIS, prima devi impostare le entità. Queste possono essere un elenco fisso di termini o apprese dal testo. Ad esempio, potresti fornire un elenco fisso di cibi disponibili nel tuo menu, con variazioni (o sinonimi) di ogni parola, come *melanzana* e *aubergine* come variazioni di *aubergine*. LUIS ha anche entità predefinite che possono essere utilizzate, come numeri e località.

Per impostare un timer, potresti avere un'entità che utilizza le entità predefinite per i numeri relativi al tempo e un'altra per le unità, come minuti e secondi. Ogni unità avrebbe più variazioni per coprire le forme singolari e plurali - come minuto e minuti.

Una volta definite le entità, crei le intenzioni. Queste vengono apprese dal modello basandosi su frasi di esempio che fornisci (note come utterances). Ad esempio, per un'intenzione *impostare timer*, potresti fornire le seguenti frasi:

* `imposta un timer di 1 secondo`
* `imposta un timer di 1 minuto e 12 secondi`
* `imposta un timer di 3 minuti`
* `imposta un timer di 9 minuti e 30 secondi`

Poi indichi a LUIS quali parti di queste frasi corrispondono alle entità:

![La frase "imposta un timer di 1 minuto e 12 secondi" suddivisa in entità](../../../../../translated_images/sentence-as-intent-entities.301401696f992259.it.png)

La frase `imposta un timer di 1 minuto e 12 secondi` ha l'intenzione di `impostare timer`. Ha anche 2 entità con 2 valori ciascuna:

|            | tempo | unità   |
| ---------- | ----: | ------- |
| 1 minuto   | 1     | minuto  |
| 12 secondi | 12    | secondo |

Per addestrare un buon modello, hai bisogno di una gamma di frasi di esempio diverse per coprire i molti modi in cui qualcuno potrebbe chiedere la stessa cosa.

> 💁 Come per qualsiasi modello di intelligenza artificiale, più dati e più accurati sono i dati utilizzati per l'addestramento, migliore sarà il modello.

✅ Pensa ai diversi modi in cui potresti chiedere la stessa cosa e aspettarti che un essere umano comprenda.

### Attività - aggiungere entità ai modelli di comprensione del linguaggio

Per il timer, devi aggiungere 2 entità: una per l'unità di tempo (minuti o secondi) e una per il numero di minuti o secondi.

Puoi trovare istruzioni per utilizzare il portale LUIS nella documentazione [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Dal portale LUIS, seleziona la scheda *Entities* e aggiungi l'entità predefinita *number* selezionando il pulsante **Add prebuilt entity**, quindi selezionando *number* dall'elenco.

1. Crea una nuova entità per l'unità di tempo utilizzando il pulsante **Create**. Dai all'entità il nome `time unit` e imposta il tipo su *List*. Aggiungi valori per `minute` e `second` alla lista *Normalized values*, aggiungendo le forme singolari e plurali alla lista *synonyms*. Premi `return` dopo aver aggiunto ogni sinonimo per aggiungerlo alla lista.

    | Valore normalizzato | Sinonimi        |
    | ------------------- | --------------- |
    | minute              | minuto, minuti  |
    | second              | secondo, secondi |

### Attività - aggiungere intenzioni ai modelli di comprensione del linguaggio

1. Dalla scheda *Intents*, seleziona il pulsante **Create** per creare una nuova intenzione. Dai a questa intenzione il nome `set timer`.

1. Negli esempi, inserisci diversi modi per impostare un timer utilizzando sia minuti, secondi e combinazioni di minuti e secondi. Gli esempi potrebbero essere:

    * `imposta un timer di 1 secondo`
    * `imposta un timer di 4 minuti`
    * `imposta un timer di quattro minuti e sei secondi`
    * `imposta un timer di 9 minuti e 30 secondi`
    * `imposta un timer di 1 minuto e 12 secondi`
    * `imposta un timer di 3 minuti`
    * `imposta un timer di 3 minuti e 1 secondo`
    * `imposta un timer di tre minuti e un secondo`
    * `imposta un timer di 1 minuto e 1 secondo`
    * `imposta un timer di 30 secondi`
    * `imposta un timer di 1 secondo`

    Mescola numeri come parole e numeri per far sì che il modello impari a gestire entrambi.

1. Mentre inserisci ogni esempio, LUIS inizierà a rilevare le entità e sottolineerà e etichetterà quelle che trova.

    ![Gli esempi con i numeri e le unità di tempo sottolineati da LUIS](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.it.png)

### Attività - addestrare e testare il modello

1. Una volta configurate le entità e le intenzioni, puoi addestrare il modello utilizzando il pulsante **Train** nel menu superiore. Seleziona questo pulsante e il modello dovrebbe addestrarsi in pochi secondi. Il pulsante sarà disattivato durante l'addestramento e verrà riattivato una volta completato.

1. Seleziona il pulsante **Test** dal menu superiore per testare il modello di comprensione del linguaggio. Inserisci un testo come `imposta un timer di 5 minuti e 4 secondi` e premi invio. La frase apparirà in una casella sotto la casella di testo in cui l'hai digitata, e sotto di essa ci sarà l'*intenzione principale*, ovvero l'intenzione rilevata con la probabilità più alta. Questa dovrebbe essere `set timer`. Il nome dell'intenzione sarà seguito dalla probabilità che l'intenzione rilevata sia quella corretta.

1. Seleziona l'opzione **Inspect** per vedere una suddivisione dei risultati. Vedrai l'intenzione con il punteggio più alto e la sua percentuale di probabilità, insieme agli elenchi delle entità rilevate.

1. Chiudi il pannello *Test* quando hai finito di testare.

### Attività - pubblicare il modello

Per utilizzare questo modello nel codice, devi pubblicarlo. Quando pubblichi da LUIS, puoi pubblicare in un ambiente di staging per i test o in un ambiente di produzione per un rilascio completo. In questa lezione, un ambiente di staging è sufficiente.

1. Dal portale LUIS, seleziona il pulsante **Publish** dal menu superiore.

1. Assicurati che sia selezionato lo *Staging slot*, quindi seleziona **Done**. Vedrai una notifica quando l'app sarà pubblicata.

1. Puoi testare questo modello utilizzando curl. Per costruire il comando curl, hai bisogno di tre valori: l'endpoint, l'ID dell'applicazione (App ID) e una chiave API. Questi possono essere accessibili dalla scheda **MANAGE** che può essere selezionata dal menu superiore.

    1. Dalla sezione *Settings*, copia l'App ID.
1. Dalla sezione *Azure Resources*, seleziona *Authoring Resource* e copia la *Primary Key* e l'*Endpoint URL*.

1. Esegui il seguente comando curl nel tuo prompt dei comandi o terminale:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Sostituisci `<endpoint url>` con l'Endpoint URL dalla sezione *Azure Resources*.

    Sostituisci `<app id>` con l'App ID dalla sezione *Settings*.

    Sostituisci `<primary key>` con la Primary Key dalla sezione *Azure Resources*.

    Sostituisci `<sentence>` con la frase che vuoi testare.

1. L'output di questa chiamata sarà un documento JSON che dettaglia la query, l'intento principale e un elenco di entità suddivise per tipo.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    Il JSON sopra proviene da una query con `set a timer for 45 minutes and 12 seconds`:

    * `set timer` è stato l'intento principale con una probabilità del 97%.
    * Sono state rilevate due entità *number*, `45` e `12`.
    * Sono state rilevate due entità *time-unit*, `minute` e `second`.

## Utilizzare il modello di comprensione del linguaggio

Una volta pubblicato, il modello LUIS può essere chiamato dal codice. Nelle lezioni precedenti, hai utilizzato un IoT Hub per gestire la comunicazione con i servizi cloud, inviando telemetria e ascoltando comandi. Questo approccio è molto asincrono: una volta inviata la telemetria, il tuo codice non attende una risposta, e se il servizio cloud non è disponibile, non lo sapresti.

Per un timer intelligente, vogliamo una risposta immediata, così possiamo informare l'utente che un timer è stato impostato o avvisarlo che i servizi cloud non sono disponibili. Per fare ciò, il nostro dispositivo IoT chiamerà direttamente un endpoint web, invece di fare affidamento su un IoT Hub.

Invece di chiamare LUIS direttamente dal dispositivo IoT, puoi utilizzare codice serverless con un tipo di trigger diverso: un trigger HTTP. Questo consente alla tua app di funzione di ascoltare richieste REST e rispondere a esse. Questa funzione sarà un endpoint REST che il tuo dispositivo può chiamare.

> 💁 Anche se puoi chiamare LUIS direttamente dal tuo dispositivo IoT, è meglio utilizzare qualcosa come codice serverless. In questo modo, quando vuoi cambiare l'app LUIS che chiami, ad esempio quando alleni un modello migliore o un modello in una lingua diversa, devi solo aggiornare il codice cloud, senza dover ridistribuire il codice su potenzialmente migliaia o milioni di dispositivi IoT.

### Attività - creare un'app di funzioni serverless

1. Crea un'app di funzioni Azure chiamata `smart-timer-trigger` e aprila in VS Code.

1. Aggiungi un trigger HTTP a questa app chiamato `speech-trigger` utilizzando il seguente comando all'interno del terminale di VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Questo creerà un trigger HTTP chiamato `text-to-timer`.

1. Testa il trigger HTTP eseguendo l'app di funzioni. Quando viene eseguita, vedrai l'endpoint elencato nell'output:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Testalo caricando l'URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) nel tuo browser.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Attività - utilizzare il modello di comprensione del linguaggio

1. L'SDK per LUIS è disponibile tramite un pacchetto Pip. Aggiungi la seguente riga al file `requirements.txt` per aggiungere la dipendenza da questo pacchetto:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Assicurati che il terminale di VS Code abbia l'ambiente virtuale attivato ed esegui il seguente comando per installare i pacchetti Pip:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Se riscontri errori, potresti dover aggiornare pip con il seguente comando:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Aggiungi nuove voci al file `local.settings.json` per la tua LUIS API Key, Endpoint URL e App ID dalla scheda **MANAGE** del portale LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Sostituisci `<endpoint url>` con l'Endpoint URL dalla sezione *Azure Resources* della scheda **MANAGE**. Questo sarà `https://<location>.api.cognitive.microsoft.com/`.

    Sostituisci `<app id>` con l'App ID dalla sezione *Settings* della scheda **MANAGE**.

    Sostituisci `<primary key>` con la Primary Key dalla sezione *Azure Resources* della scheda **MANAGE**.

1. Aggiungi le seguenti importazioni al file `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Questo importa alcune librerie di sistema, oltre alle librerie per interagire con LUIS.

1. Elimina il contenuto del metodo `main` e aggiungi il seguente codice:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Questo carica i valori che hai aggiunto al file `local.settings.json` per la tua app LUIS, crea un oggetto credenziali con la tua API key, quindi crea un oggetto client LUIS per interagire con la tua app LUIS.

1. Questo trigger HTTP sarà chiamato passando il testo da comprendere come JSON, con il testo in una proprietà chiamata `text`. Il seguente codice estrae il valore dal corpo della richiesta HTTP e lo registra nella console. Aggiungi questo codice alla funzione `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Le previsioni vengono richieste a LUIS inviando una richiesta di previsione - un documento JSON contenente il testo da prevedere. Crealo con il seguente codice:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Questa richiesta può quindi essere inviata a LUIS, utilizzando lo slot di staging a cui la tua app è stata pubblicata:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. La risposta alla previsione contiene l'intento principale - l'intento con il punteggio di previsione più alto, insieme alle entità. Se l'intento principale è `set timer`, allora le entità possono essere lette per ottenere il tempo necessario per il timer:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Le entità `number` saranno un array di numeri. Ad esempio, se hai detto *"Set a four minute 17 second timer."*, allora l'array `number` conterrà 2 interi - 4 e 17.

    Le entità `time unit` saranno un array di array di stringhe, con ogni unità di tempo come un array di stringhe all'interno dell'array. Ad esempio, se hai detto *"Set a four minute 17 second timer."*, allora l'array `time unit` conterrà 2 array con valori singoli ciascuno - `['minute']` e `['second']`.

    La versione JSON di queste entità per *"Set a four minute 17 second timer."* è:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Questo codice definisce anche un conteggio per il tempo totale del timer in secondi. Questo sarà popolato dai valori delle entità.

1. Le entità non sono collegate, ma possiamo fare alcune ipotesi su di esse. Saranno nell'ordine in cui sono state pronunciate, quindi la posizione nell'array può essere utilizzata per determinare quale numero corrisponde a quale unità di tempo. Ad esempio:

    * *"Set a 30 second timer"* - avrà un numero, `30`, e un'unità di tempo, `second`, quindi il singolo numero corrisponderà alla singola unità di tempo.
    * *"Set a 2 minute and 30 second timer"* - avrà due numeri, `2` e `30`, e due unità di tempo, `minute` e `second`, quindi il primo numero sarà per la prima unità di tempo (2 minuti) e il secondo numero per la seconda unità di tempo (30 secondi).

    Il seguente codice ottiene il conteggio degli elementi nelle entità `number` e utilizza questo per estrarre il primo elemento da ogni array, poi il secondo e così via. Aggiungi questo all'interno del blocco `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Per *"Set a four minute 17 second timer."*, questo ciclo si ripeterà due volte, dando i seguenti valori:

    | loop count | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. All'interno di questo ciclo, utilizza il numero e l'unità di tempo per calcolare il tempo totale per il timer, aggiungendo 60 secondi per ogni minuto e il numero di secondi per eventuali secondi.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Al di fuori di questo ciclo attraverso le entità, registra il tempo totale per il timer:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Il numero di secondi deve essere restituito dalla funzione come risposta HTTP. Alla fine del blocco `if`, aggiungi il seguente codice:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Questo codice crea un payload contenente il numero totale di secondi per il timer, lo converte in una stringa JSON e lo restituisce come risultato HTTP con un codice di stato 200, che significa che la chiamata è stata eseguita con successo.

1. Infine, al di fuori del blocco `if`, gestisci il caso in cui l'intento non sia stato riconosciuto restituendo un codice di errore:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 è il codice di stato per *non trovato*.

1. Esegui l'app di funzioni e testala utilizzando curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Sostituisci `<text>` con il testo della tua richiesta, ad esempio `set a 2 minutes 27 second timer`.

    Vedrai il seguente output dall'app di funzioni:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    La chiamata a curl restituirà il seguente risultato:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Il numero di secondi per il timer è nel valore `"seconds"`.

> 💁 Puoi trovare questo codice nella cartella [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Attività - rendere la tua funzione disponibile al tuo dispositivo IoT

1. Per consentire al tuo dispositivo IoT di chiamare il tuo endpoint REST, avrà bisogno di conoscere l'URL. Quando lo hai accesso in precedenza, hai utilizzato `localhost`, che è un collegamento per accedere agli endpoint REST sulla tua macchina locale. Per consentire al tuo dispositivo IoT di accedere, devi pubblicare nel cloud o ottenere il tuo indirizzo IP per accedervi localmente.

    > ⚠️ Se stai utilizzando un Wio Terminal, è più semplice eseguire l'app di funzioni localmente, poiché ci sarà una dipendenza da librerie che significa che non puoi distribuire l'app di funzioni nello stesso modo in cui hai fatto prima. Esegui l'app di funzioni localmente e accedila tramite l'indirizzo IP del tuo computer. Se vuoi distribuirla nel cloud, verranno fornite informazioni in una lezione successiva su come farlo.

    * Pubblica l'app di funzioni - segui le istruzioni delle lezioni precedenti per pubblicare la tua app di funzioni nel cloud. Una volta pubblicata, l'URL sarà `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, dove `<APP_NAME>` sarà il nome della tua app di funzioni. Assicurati di pubblicare anche le impostazioni locali.

      Quando lavori con trigger HTTP, sono protetti per impostazione predefinita con una chiave dell'app di funzioni. Per ottenere questa chiave, esegui il seguente comando:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Copia il valore della voce `default` dalla sezione `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Questa chiave dovrà essere aggiunta come parametro di query all'URL, quindi l'URL finale sarà `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, dove `<APP_NAME>` sarà il nome della tua app di funzioni e `<FUNCTION_KEY>` sarà la tua chiave di funzione predefinita.

      > 💁 Puoi cambiare il tipo di autorizzazione del trigger HTTP utilizzando l'impostazione `authlevel` nel file `function.json`. Puoi leggere di più su questo nella [sezione di configurazione della documentazione del trigger HTTP di Azure Functions su Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Esegui l'app di funzioni localmente e accedi utilizzando l'indirizzo IP - puoi ottenere l'indirizzo IP del tuo computer sulla rete locale e utilizzarlo per costruire l'URL.

      Trova il tuo indirizzo IP:

      * Su Windows 10, segui la [guida per trovare il tuo indirizzo IP](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Su macOS, segui la [guida su come trovare l'indirizzo IP su un Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Su Linux, segui la sezione su come trovare l'indirizzo IP privato nella [guida su come trovare l'indirizzo IP in Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Una volta ottenuto il tuo indirizzo IP, sarai in grado di accedere alla funzione su `http://`.

:7071/api/text-to-timer`, dove `<IP_ADDRESS>` sarà il tuo indirizzo IP, ad esempio `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Nota che questo utilizza la porta 7071, quindi dopo l'indirizzo IP dovrai aggiungere `:7071`.

      > 💁 Questo funzionerà solo se il tuo dispositivo IoT si trova sulla stessa rete del tuo computer.

1. Testa l'endpoint accedendovi utilizzando curl.

---

## 🚀 Sfida

Esistono molti modi per richiedere la stessa cosa, come impostare un timer. Pensa a diversi modi per farlo e usali come esempi nella tua app LUIS. Provali per vedere quanto bene il tuo modello riesce a gestire modi diversi di richiedere un timer.

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Revisione e studio autonomo

* Leggi di più su LUIS e le sue capacità nella [pagina della documentazione di Language Understanding (LUIS) su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Approfondisci la comprensione del linguaggio naturale nella [pagina sulla comprensione del linguaggio naturale su Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Leggi di più sui trigger HTTP nella [documentazione sui trigger HTTP di Azure Functions su Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Compito

[Annulla il timer](assignment.md)

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.