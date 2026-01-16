<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-25T16:55:45+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "it"
}
-->
# Migrare la logica della tua applicazione al cloud

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questa lezione è stata insegnata come parte del [Progetto IoT per Principianti 2 - Serie sull'Agricoltura Digitale](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) del [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Controlla il tuo dispositivo IoT con codice serverless](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Quiz preliminare alla lezione

[Quiz preliminare alla lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Introduzione

Nella lezione precedente, hai imparato a connettere il monitoraggio dell'umidità del suolo delle piante e il controllo del relè a un servizio IoT basato sul cloud. Il passo successivo è spostare il codice server che controlla il timing del relè nel cloud. In questa lezione imparerai come farlo utilizzando funzioni serverless.

In questa lezione tratteremo:

* [Cos'è il serverless?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Creare un'applicazione serverless](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Creare un trigger di evento per IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Inviare richieste di metodo diretto dal codice serverless](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Distribuire il tuo codice serverless nel cloud](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Cos'è il serverless?

Il serverless, o calcolo serverless, consiste nel creare piccoli blocchi di codice che vengono eseguiti nel cloud in risposta a diversi tipi di eventi. Quando si verifica l'evento, il tuo codice viene eseguito e riceve i dati relativi all'evento. Questi eventi possono provenire da molte fonti diverse, inclusi richieste web, messaggi messi in una coda, modifiche ai dati in un database o messaggi inviati a un servizio IoT da dispositivi IoT.

![Eventi inviati da un servizio IoT a un servizio serverless, tutti elaborati contemporaneamente da più funzioni in esecuzione](../../../../../translated_images/it/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.png)

> 💁 Se hai già utilizzato trigger di database, puoi pensare a questo come qualcosa di simile: codice attivato da un evento come l'inserimento di una riga.

![Quando molti eventi vengono inviati contemporaneamente, il servizio serverless si scala per eseguirli tutti contemporaneamente](../../../../../translated_images/it/serverless-scaling.f8c769adf0413fd1.webp)

Il tuo codice viene eseguito solo quando si verifica l'evento, non c'è nulla che mantenga il tuo codice attivo in altri momenti. L'evento si verifica, il tuo codice viene caricato ed eseguito. Questo rende il serverless molto scalabile: se molti eventi si verificano contemporaneamente, il provider cloud può eseguire la tua funzione tutte le volte necessarie contemporaneamente su qualsiasi server disponibile. Lo svantaggio è che, se hai bisogno di condividere informazioni tra eventi, devi salvarle da qualche parte, come in un database, piuttosto che conservarle in memoria.

Il tuo codice è scritto come una funzione che prende i dettagli dell'evento come parametro. Puoi utilizzare una vasta gamma di linguaggi di programmazione per scrivere queste funzioni serverless.

> 🎓 Il serverless è anche noto come Functions as a Service (FaaS), poiché ogni trigger di evento è implementato come una funzione nel codice.

Nonostante il nome, il serverless utilizza effettivamente server. Il nome deriva dal fatto che, come sviluppatore, non ti preoccupi dei server necessari per eseguire il tuo codice; tutto ciò che ti interessa è che il tuo codice venga eseguito in risposta a un evento. Il provider cloud ha un *runtime* serverless che gestisce l'allocazione dei server, la rete, lo storage, la CPU, la memoria e tutto il necessario per eseguire il tuo codice. Questo modello significa che non puoi pagare per server, poiché non c'è un server dedicato. Invece, paghi per il tempo in cui il tuo codice è in esecuzione e per la quantità di memoria utilizzata.

> 💰 Il serverless è uno dei modi più economici per eseguire codice nel cloud. Ad esempio, al momento della scrittura, un provider cloud consente a tutte le tue funzioni serverless di essere eseguite un totale combinato di 1.000.000 di volte al mese prima di iniziare a addebitarti, e dopo di ciò ti addebita 0,20 USD per ogni 1.000.000 di esecuzioni. Quando il tuo codice non è in esecuzione, non paghi.

Come sviluppatore IoT, il modello serverless è ideale. Puoi scrivere una funzione che viene chiamata in risposta ai messaggi inviati da qualsiasi dispositivo IoT connesso al tuo servizio IoT ospitato nel cloud. Il tuo codice gestirà tutti i messaggi inviati, ma sarà in esecuzione solo quando necessario.

✅ Riguarda il codice che hai scritto come server per ascoltare i messaggi tramite MQTT. Come potrebbe funzionare nel cloud utilizzando il serverless? Come pensi che il codice potrebbe essere modificato per supportare il calcolo serverless?

> 💁 Il modello serverless si sta espandendo ad altri servizi cloud oltre all'esecuzione del codice. Ad esempio, i database serverless sono disponibili nel cloud utilizzando un modello di prezzo serverless, dove paghi per ogni richiesta effettuata contro il database, come una query o un inserimento, solitamente con prezzi basati sulla quantità di lavoro necessario per soddisfare la richiesta. Ad esempio, una singola selezione di una riga contro una chiave primaria costerà meno di un'operazione complessa che unisce molte tabelle e restituisce migliaia di righe.

## Creare un'applicazione serverless

Il servizio di calcolo serverless di Microsoft si chiama Azure Functions.

![Il logo di Azure Functions](../../../../../translated_images/it/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.png)

Il breve video qui sotto offre una panoramica di Azure Functions.

[![Video panoramica di Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Clicca sull'immagine sopra per guardare il video.

✅ Prenditi un momento per fare qualche ricerca e leggi la panoramica di Azure Functions nella [documentazione di Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Per scrivere Azure Functions, inizi con un'app Azure Functions nel linguaggio di tua scelta. Azure Functions supporta nativamente Python, JavaScript, TypeScript, C#, F#, Java e Powershell. In questa lezione imparerai a scrivere un'app Azure Functions in Python.

> 💁 Azure Functions supporta anche gestori personalizzati, quindi puoi scrivere le tue funzioni in qualsiasi linguaggio che supporti richieste HTTP, inclusi linguaggi più vecchi come COBOL.

Le app di funzioni consistono in uno o più *trigger* - funzioni che rispondono agli eventi. Puoi avere più trigger all'interno di un'unica app di funzioni, tutte condividendo una configurazione comune. Ad esempio, nel file di configurazione della tua app di funzioni puoi avere i dettagli di connessione del tuo IoT Hub, e tutte le funzioni nell'app possono usarli per connettersi e ascoltare gli eventi.

### Attività - installare gli strumenti di Azure Functions

> Al momento della scrittura, gli strumenti di codice di Azure Functions non funzionano completamente su Apple Silicon con progetti Python. Dovrai utilizzare un Mac basato su Intel, un PC Windows o un PC Linux.

Una grande caratteristica di Azure Functions è che puoi eseguirle localmente. Lo stesso runtime utilizzato nel cloud può essere eseguito sul tuo computer, permettendoti di scrivere codice che risponde ai messaggi IoT ed eseguirlo localmente. Puoi persino eseguire il debug del tuo codice mentre gli eventi vengono gestiti. Una volta che sei soddisfatto del tuo codice, può essere distribuito nel cloud.

Gli strumenti di Azure Functions sono disponibili come CLI, noto come Azure Functions Core Tools.

1. Installa gli strumenti core di Azure Functions seguendo le istruzioni nella [documentazione di Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Installa l'estensione Azure Functions per VS Code. Questa estensione fornisce supporto per la creazione, il debug e la distribuzione di funzioni Azure. Consulta la [documentazione dell'estensione Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) per le istruzioni su come installare questa estensione in VS Code.

Quando distribuisci la tua app Azure Functions nel cloud, essa deve utilizzare una piccola quantità di storage cloud per archiviare cose come i file dell'applicazione e i file di log. Quando esegui la tua app di funzioni localmente, devi comunque connetterti allo storage cloud, ma invece di utilizzare uno storage cloud reale, puoi utilizzare un emulatore di storage chiamato [Azurite](https://github.com/Azure/Azurite). Questo viene eseguito localmente ma agisce come uno storage cloud.

> 🎓 In Azure, lo storage che Azure Functions utilizza è un Azure Storage Account. Questi account possono archiviare file, blob, dati in tabelle o dati in code. Puoi condividere un account di storage tra molte app, come un'app di funzioni e un'app web.

1. Azurite è un'app Node.js, quindi dovrai installare Node.js. Puoi trovare le istruzioni per il download e l'installazione sul [sito web di Node.js](https://nodejs.org/). Se stai utilizzando un Mac, puoi anche installarlo da [Homebrew](https://formulae.brew.sh/formula/node).

1. Installa Azurite utilizzando il seguente comando (`npm` è uno strumento che viene installato quando installi Node.js):

    ```sh
    npm install -g azurite
    ```

1. Crea una cartella chiamata `azurite` per Azurite da utilizzare per archiviare i dati:

    ```sh
    mkdir azurite
    ```

1. Esegui Azurite, passandogli questa nuova cartella:

    ```sh
    azurite --location azurite
    ```

    L'emulatore di storage Azurite verrà avviato e sarà pronto per la connessione al runtime locale delle funzioni.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Attività - creare un progetto Azure Functions

La CLI di Azure Functions può essere utilizzata per creare una nuova app di funzioni.

1. Crea una cartella per la tua app di funzioni e naviga al suo interno. Chiamala `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Crea un ambiente virtuale Python all'interno di questa cartella:

    ```sh
    python3 -m venv .venv
    ```

1. Attiva l'ambiente virtuale:

    * Su Windows:
        * Se stai utilizzando il Prompt dei Comandi, o il Prompt dei Comandi tramite Windows Terminal, esegui:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Se stai utilizzando PowerShell, esegui:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Su macOS o Linux, esegui:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Questi comandi devono essere eseguiti dalla stessa posizione in cui hai eseguito il comando per creare l'ambiente virtuale. Non dovrai mai navigare nella cartella `.venv`; dovresti sempre eseguire il comando di attivazione e qualsiasi comando per installare pacchetti o eseguire codice dalla cartella in cui ti trovavi quando hai creato l'ambiente virtuale.

1. Esegui il seguente comando per creare un'app di funzioni in questa cartella:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Questo creerà tre file all'interno della cartella corrente:

    * `host.json` - questo documento JSON contiene le impostazioni per la tua app di funzioni. Non sarà necessario modificare queste impostazioni.
    * `local.settings.json` - questo documento JSON contiene le impostazioni che la tua app utilizzerà quando verrà eseguita localmente, come le stringhe di connessione per il tuo IoT Hub. Queste impostazioni sono solo locali e non dovrebbero essere aggiunte al controllo del codice sorgente. Quando distribuisci l'app nel cloud, queste impostazioni non vengono distribuite; invece, le tue impostazioni vengono caricate dalle impostazioni dell'applicazione. Questo sarà trattato più avanti in questa lezione.
    * `requirements.txt` - questo è un [file di requisiti Pip](https://pip.pypa.io/en/stable/user_guide/#requirements-files) che contiene i pacchetti Pip necessari per eseguire la tua app di funzioni.

1. Il file `local.settings.json` ha un'impostazione per l'account di storage che l'app di funzioni utilizzerà. Questo valore predefinito è vuoto, quindi deve essere impostato. Per connettersi all'emulatore di storage locale Azurite, imposta questo valore come segue:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Installa i pacchetti Pip necessari utilizzando il file dei requisiti:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 I pacchetti Pip richiesti devono essere in questo file, in modo che quando l'app di funzioni viene distribuita nel cloud, il runtime possa assicurarsi di installare i pacchetti corretti.

1. Per verificare che tutto funzioni correttamente, puoi avviare il runtime delle funzioni. Esegui il seguente comando per farlo:

    ```sh
    func start
    ```

    Vedrai il runtime avviarsi e segnalare che non ha trovato funzioni di lavoro (trigger).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Se ricevi una notifica del firewall, concedi l'accesso poiché l'applicazione `func` deve essere in grado di leggere e scrivere sulla tua rete.
> ⚠️ Se stai utilizzando macOS, potrebbero esserci avvisi nell'output:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Puoi ignorarli purché l'app Functions si avvii correttamente e mostri le funzioni in esecuzione. Come indicato in [questa domanda su Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), possono essere ignorati.

1. Arresta l'app Functions premendo `ctrl+c`.

1. Apri la cartella corrente in VS Code, o aprendo VS Code e poi questa cartella, oppure eseguendo il seguente comando:

    ```sh
    code .
    ```

    VS Code rileverà il tuo progetto Functions e mostrerà una notifica che dice:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![La notifica](../../../../../translated_images/it/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Seleziona **Sì** da questa notifica.

1. Assicurati che l'ambiente virtuale Python sia in esecuzione nel terminale di VS Code. Termina e riavvia se necessario.

## Creare un trigger per eventi IoT Hub

L'app Functions è il contenitore del tuo codice serverless. Per rispondere agli eventi di IoT Hub, puoi aggiungere un trigger IoT Hub a questa app. Questo trigger deve connettersi al flusso di messaggi inviati a IoT Hub e rispondere a essi. Per ottenere questo flusso di messaggi, il trigger deve connettersi all'*endpoint compatibile con Event Hub* di IoT Hub.

IoT Hub si basa su un altro servizio Azure chiamato Azure Event Hubs. Event Hubs è un servizio che consente di inviare e ricevere messaggi, e IoT Hub lo estende aggiungendo funzionalità per dispositivi IoT. Il modo in cui ti connetti per leggere i messaggi da IoT Hub è lo stesso che utilizzeresti con Event Hubs.

✅ Fai una ricerca: Leggi la panoramica di Event Hubs nella [documentazione di Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Come si confrontano le funzionalità di base con IoT Hub?

Per connettersi a IoT Hub, un dispositivo IoT deve utilizzare una chiave segreta che garantisce che solo i dispositivi autorizzati possano connettersi. Lo stesso vale per la connessione per leggere i messaggi: il tuo codice avrà bisogno di una stringa di connessione che contenga una chiave segreta, insieme ai dettagli di IoT Hub.

> 💁 La stringa di connessione predefinita che ottieni ha permessi **iothubowner**, che danno a qualsiasi codice che la utilizza permessi completi su IoT Hub. Idealmente, dovresti connetterti con il livello più basso di permessi necessario. Questo sarà trattato nella prossima lezione.

Una volta che il trigger è connesso, il codice all'interno della funzione verrà chiamato per ogni messaggio inviato a IoT Hub, indipendentemente dal dispositivo che lo ha inviato. Il trigger riceverà il messaggio come parametro.

### Attività - ottenere la stringa di connessione dell'endpoint compatibile con Event Hub

1. Dal terminale di VS Code, esegui il seguente comando per ottenere la stringa di connessione per l'endpoint compatibile con Event Hub di IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome che hai usato per il tuo IoT Hub.

1. In VS Code, apri il file `local.settings.json`. Aggiungi il seguente valore aggiuntivo all'interno della sezione `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Sostituisci `<connection string>` con il valore ottenuto nel passaggio precedente. Dovrai aggiungere una virgola dopo la riga precedente per rendere valido il JSON.

### Attività - creare un trigger per eventi

Ora sei pronto per creare il trigger per eventi.

1. Dal terminale di VS Code, esegui il seguente comando dalla cartella `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Questo crea una nuova funzione chiamata `iot-hub-trigger`. Il trigger si connetterà all'endpoint compatibile con Event Hub su IoT Hub, quindi puoi utilizzare un trigger di Event Hub. Non esiste un trigger specifico per IoT Hub.

Questo creerà una cartella all'interno della cartella `soil-moisture-trigger` chiamata `iot-hub-trigger` che contiene questa funzione. Questa cartella avrà i seguenti file al suo interno:

* `__init__.py` - questo è il file di codice Python che contiene il trigger, utilizzando la convenzione standard dei nomi dei file Python per trasformare questa cartella in un modulo Python.

    Questo file conterrà il seguente codice:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Il cuore del trigger è la funzione `main`. È questa funzione che viene chiamata con gli eventi da IoT Hub. Questa funzione ha un parametro chiamato `event` che contiene un `EventHubEvent`. Ogni volta che un messaggio viene inviato a IoT Hub, questa funzione viene chiamata passando quel messaggio come `event`, insieme alle proprietà che sono le stesse delle annotazioni viste nella lezione precedente.

    Il cuore di questa funzione registra l'evento.

* `function.json` - questo contiene la configurazione per il trigger. La configurazione principale è in una sezione chiamata `bindings`. Un binding è il termine per una connessione tra Azure Functions e altri servizi Azure. Questa funzione ha un binding di input a un Event Hub - si connette a un Event Hub e riceve dati.

    > 💁 Puoi anche avere binding di output in modo che l'output di una funzione venga inviato a un altro servizio. Ad esempio, potresti aggiungere un binding di output a un database e restituire l'evento di IoT Hub dalla funzione, e verrà automaticamente inserito nel database.

    ✅ Fai una ricerca: Leggi i binding nella [documentazione sui concetti di trigger e binding di Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    La sezione `bindings` include la configurazione per il binding. I valori di interesse sono:

  * `"type": "eventHubTrigger"` - indica alla funzione che deve ascoltare eventi da un Event Hub
  * `"name": "events"` - questo è il nome del parametro da utilizzare per gli eventi di Event Hub. Questo corrisponde al nome del parametro nella funzione `main` nel codice Python.
  * `"direction": "in"` - questo è un binding di input, i dati dall'Event Hub entrano nella funzione
  * `"connection": ""` - definisce il nome dell'impostazione da cui leggere la stringa di connessione. Quando si esegue localmente, questa impostazione verrà letta dal file `local.settings.json`.

    > 💁 La stringa di connessione non può essere memorizzata nel file `function.json`, deve essere letta dalle impostazioni. Questo per evitare di esporre accidentalmente la stringa di connessione.

1. A causa di [un bug nel template di Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250), il file `function.json` ha un valore errato per il campo `cardinality`. Aggiorna questo campo da `many` a `one`:

    ```json
    "cardinality": "one",
    ```

1. Aggiorna il valore di `"connection"` nel file `function.json` per puntare al nuovo valore che hai aggiunto al file `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Ricorda - questo deve puntare all'impostazione, non contenere la stringa di connessione effettiva.

1. La stringa di connessione contiene il valore `eventHubName`, quindi il valore per questo nel file `function.json` deve essere svuotato. Aggiorna questo valore a una stringa vuota:

    ```json
    "eventHubName": "",
    ```

### Attività - eseguire il trigger per eventi

1. Assicurati di non eseguire il monitor degli eventi di IoT Hub. Se questo è in esecuzione contemporaneamente all'app Functions, l'app Functions non sarà in grado di connettersi e consumare eventi.

    > 💁 Più app possono connettersi agli endpoint di IoT Hub utilizzando diversi *consumer group*. Questi saranno trattati in una lezione successiva.

1. Per eseguire l'app Functions, esegui il seguente comando dal terminale di VS Code:

    ```sh
    func start
    ```

    L'app Functions si avvierà e scoprirà la funzione `iot-hub-trigger`. Elaborerà quindi tutti gli eventi che sono stati già inviati a IoT Hub nell'ultimo giorno.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Ogni chiamata alla funzione sarà circondata da un blocco `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` nell'output, così potrai vedere quanti messaggi sono stati elaborati in ogni chiamata alla funzione.

1. Assicurati che il tuo dispositivo IoT sia in esecuzione. Vedrai nuovi messaggi di umidità del suolo apparire nell'app Functions.

1. Arresta e riavvia l'app Functions. Vedrai che non elaborerà di nuovo i messaggi precedenti, ma solo i nuovi messaggi.

> 💁 VS Code supporta anche il debug delle tue Functions. Puoi impostare punti di interruzione cliccando sul bordo all'inizio di ogni riga di codice, oppure posizionando il cursore su una riga di codice e selezionando *Esegui -> Attiva punto di interruzione*, o premendo `F9`. Puoi avviare il debugger selezionando *Esegui -> Avvia debug*, premendo `F5`, o selezionando il pannello *Esegui e debug* e cliccando sul pulsante **Avvia debug**. In questo modo puoi vedere i dettagli degli eventi elaborati.

#### Risoluzione dei problemi

* Se ricevi il seguente errore:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Controlla che Azurite sia in esecuzione e che tu abbia impostato `AzureWebJobsStorage` nel file `local.settings.json` su `UseDevelopmentStorage=true`.

* Se ricevi il seguente errore:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Controlla che tu abbia impostato `cardinality` nel file `function.json` su `one`.

* Se ricevi il seguente errore:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Controlla che tu abbia impostato `eventHubName` nel file `function.json` su una stringa vuota.

## Inviare richieste di metodo diretto dal codice serverless

Finora la tua app Functions sta ascoltando i messaggi da IoT Hub utilizzando l'endpoint compatibile con Event Hub. Ora devi inviare comandi al dispositivo IoT. Questo viene fatto utilizzando una connessione diversa a IoT Hub tramite il *Registry Manager*. Il Registry Manager è uno strumento che ti consente di vedere quali dispositivi sono registrati con IoT Hub e comunicare con quei dispositivi inviando messaggi cloud-to-device, richieste di metodo diretto o aggiornando il device twin. Puoi anche usarlo per registrare, aggiornare o eliminare dispositivi IoT da IoT Hub.

Per connetterti al Registry Manager, hai bisogno di una stringa di connessione.

### Attività - ottenere la stringa di connessione del Registry Manager

1. Per ottenere la stringa di connessione, esegui il seguente comando:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome che hai usato per il tuo IoT Hub.

    La stringa di connessione viene richiesta per la policy *ServiceConnect* utilizzando il parametro `--policy-name service`. Quando richiedi una stringa di connessione, puoi specificare quali permessi quella stringa di connessione consentirà. La policy ServiceConnect consente al tuo codice di connettersi e inviare messaggi ai dispositivi IoT.

    ✅ Fai una ricerca: Leggi le diverse policy nella [documentazione sui permessi di IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. In VS Code, apri il file `local.settings.json`. Aggiungi il seguente valore aggiuntivo all'interno della sezione `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Sostituisci `<connection string>` con il valore ottenuto nel passaggio precedente. Dovrai aggiungere una virgola dopo la riga precedente per rendere valido il JSON.

### Attività - inviare una richiesta di metodo diretto a un dispositivo

1. L'SDK per il Registry Manager è disponibile tramite un pacchetto Pip. Aggiungi la seguente riga al file `requirements.txt` per aggiungere la dipendenza da questo pacchetto:

    ```sh
    azure-iot-hub
    ```

1. Assicurati che il terminale di VS Code abbia l'ambiente virtuale attivato ed esegui il seguente comando per installare i pacchetti Pip:

    ```sh
    pip install -r requirements.txt
    ```

1. Aggiungi i seguenti import al file `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Questo importa alcune librerie di sistema, oltre alle librerie per interagire con il Registry Manager e inviare richieste di metodo diretto.

1. Rimuovi il codice dall'interno del metodo `main`, ma mantieni il metodo stesso.

1. Nel metodo `main`, aggiungi il seguente codice:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Questo codice estrae il corpo dell'evento che contiene il messaggio JSON inviato dal dispositivo IoT.

    Ottiene quindi l'ID del dispositivo dalle annotazioni passate con il messaggio. Il corpo dell'evento contiene il messaggio inviato come telemetria, il dizionario `iothub_metadata` contiene proprietà impostate da IoT Hub come l'ID del dispositivo del mittente e l'ora in cui il messaggio è stato inviato.

    Queste informazioni vengono quindi registrate. Vedrai questa registrazione nel terminale quando esegui l'app Functions localmente.

1. Sotto questo, aggiungi il seguente codice:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Questo codice ottiene l'umidità del suolo dal messaggio. Quindi controlla l'umidità del suolo e, a seconda del valore, crea una classe helper per la richiesta di metodo diretto per il metodo diretto `relay_on` o `relay_off`. La richiesta del metodo non necessita di un payload, quindi viene inviato un documento JSON vuoto.

1. Sotto questo, aggiungi il seguente codice:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Questo codice carica la `REGISTRY_MANAGER_CONNECTION_STRING` dal file `local.settings.json`. I valori in questo file sono resi disponibili come variabili d'ambiente e possono essere letti utilizzando la funzione `os.environ`, una funzione che restituisce un dizionario di tutte le variabili d'ambiente.

> 💁 Quando questo codice viene distribuito nel cloud, i valori nel file `local.settings.json` saranno impostati come *Application Settings* e potranno essere letti dalle variabili d'ambiente.

Il codice crea quindi un'istanza della classe helper Registry Manager utilizzando la stringa di connessione.

1. Aggiungi il seguente codice:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Questo codice indica al registry manager di inviare la richiesta di metodo diretto al dispositivo che ha inviato la telemetria.

    > 💁 Nelle versioni dell'app che hai creato nelle lezioni precedenti utilizzando MQTT, i comandi di controllo del relè venivano inviati a tutti i dispositivi. Il codice presupponeva che avessi un solo dispositivo. Questa versione del codice invia la richiesta di metodo a un singolo dispositivo, quindi funzionerebbe se avessi più configurazioni di sensori di umidità e relè, inviando la richiesta di metodo diretto al dispositivo corretto.

1. Esegui l'app Functions e assicurati che il tuo dispositivo IoT stia inviando dati. Vedrai i messaggi elaborati e le richieste di metodo diretto inviate. Sposta il sensore di umidità del terreno dentro e fuori dal terreno per vedere i valori cambiare e il relè accendersi e spegnersi.

> 💁 Puoi trovare questo codice nella cartella [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Distribuisci il tuo codice serverless nel cloud

Il tuo codice ora funziona localmente, quindi il prossimo passo è distribuire l'app Functions nel cloud.

### Attività - crea le risorse cloud

La tua app Functions deve essere distribuita in una risorsa Functions App in Azure, all'interno del Resource Group che hai creato per il tuo IoT Hub. Avrai anche bisogno di un Storage Account creato in Azure per sostituire quello emulato che stai eseguendo localmente.

1. Esegui il seguente comando per creare un account di archiviazione:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Sostituisci `<storage_name>` con un nome per il tuo account di archiviazione. Questo dovrà essere univoco a livello globale poiché fa parte dell'URL utilizzato per accedere all'account di archiviazione. Puoi utilizzare solo lettere minuscole e numeri per questo nome, nessun altro carattere, ed è limitato a 24 caratteri. Usa qualcosa come `sms` e aggiungi un identificatore univoco alla fine, come alcune parole casuali o il tuo nome.

    L'opzione `--sku Standard_LRS` seleziona il livello di prezzo, scegliendo l'account generale a costo più basso. Non esiste un livello gratuito di archiviazione e paghi per ciò che utilizzi. I costi sono relativamente bassi, con l'archiviazione più costosa a meno di 0,05 USD al mese per gigabyte archiviato.

    ✅ Leggi i dettagli sui prezzi nella [pagina dei prezzi di Azure Storage Account](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Esegui il seguente comando per creare un'app Functions:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Sostituisci `<location>` con la posizione che hai utilizzato quando hai creato il Resource Group nella lezione precedente.

    Sostituisci `<storage_name>` con il nome dell'account di archiviazione che hai creato nel passaggio precedente.

    Sostituisci `<functions_app_name>` con un nome univoco per la tua app Functions. Questo dovrà essere univoco a livello globale poiché fa parte di un URL che può essere utilizzato per accedere all'app Functions. Usa qualcosa come `soil-moisture-sensor-` e aggiungi un identificatore univoco alla fine, come alcune parole casuali o il tuo nome.

    L'opzione `--functions-version 3` imposta la versione di Azure Functions da utilizzare. La versione 3 è l'ultima versione.

    L'opzione `--os-type Linux` indica al runtime di Functions di utilizzare Linux come sistema operativo per ospitare queste funzioni. Le funzioni possono essere ospitate su Linux o Windows, a seconda del linguaggio di programmazione utilizzato. Le app Python sono supportate solo su Linux.

### Attività - carica le impostazioni dell'applicazione

Quando hai sviluppato la tua app Functions, hai memorizzato alcune impostazioni nel file `local.settings.json` per le stringhe di connessione del tuo IoT Hub. Queste devono essere scritte nelle Application Settings della tua app Functions in Azure in modo che possano essere utilizzate dal tuo codice.

> 🎓 Il file `local.settings.json` è solo per le impostazioni di sviluppo locale e non dovrebbe essere inserito nel controllo del codice sorgente, come GitHub. Quando distribuito nel cloud, vengono utilizzate le Application Settings. Le Application Settings sono coppie chiave/valore ospitate nel cloud e vengono lette dalle variabili d'ambiente, sia nel tuo codice che dal runtime quando collega il tuo codice all'IoT Hub.

1. Esegui il seguente comando per impostare la configurazione `IOT_HUB_CONNECTION_STRING` nelle Application Settings della tua app Functions:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Sostituisci `<functions_app_name>` con il nome che hai utilizzato per la tua app Functions.

    Sostituisci `<connection string>` con il valore di `IOT_HUB_CONNECTION_STRING` dal tuo file `local.settings.json`.

1. Ripeti il passaggio sopra, ma imposta il valore di `REGISTRY_MANAGER_CONNECTION_STRING` al valore corrispondente dal tuo file `local.settings.json`.

Quando esegui questi comandi, verrà anche visualizzato un elenco di tutte le Application Settings per l'app Functions. Puoi utilizzare questo elenco per verificare che i tuoi valori siano impostati correttamente.

> 💁 Vedrai un valore già impostato per `AzureWebJobsStorage`. Nel tuo file `local.settings.json`, questo era impostato su un valore per utilizzare l'emulatore di archiviazione locale. Quando hai creato l'app Functions, hai passato l'account di archiviazione come parametro, e questo viene impostato automaticamente in questa configurazione.

### Attività - distribuisci la tua app Functions nel cloud

Ora che l'app Functions è pronta, il tuo codice può essere distribuito.

1. Esegui il seguente comando dal terminale di VS Code per pubblicare la tua app Functions:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Sostituisci `<functions_app_name>` con il nome che hai utilizzato per la tua app Functions.

Il codice verrà impacchettato e inviato all'app Functions, dove verrà distribuito e avviato. Ci sarà molto output nella console, che terminerà con la conferma della distribuzione e un elenco delle funzioni distribuite. In questo caso, l'elenco conterrà solo il trigger.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Assicurati che il tuo dispositivo IoT sia in esecuzione. Modifica i livelli di umidità regolando l'umidità del terreno o spostando il sensore dentro e fuori dal terreno. Vedrai il relè accendersi e spegnersi mentre l'umidità del terreno cambia.

---

## 🚀 Sfida

Nella lezione precedente, hai gestito il tempo per il relè disiscrivendoti dai messaggi MQTT mentre il relè era acceso e per un breve periodo dopo che era stato spento. Non puoi utilizzare questo metodo qui: non puoi disiscriverti dal trigger del tuo IoT Hub.

Pensa a modi diversi per gestire questa situazione nella tua app Functions.

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Revisione e studio autonomo

* Leggi informazioni sul computing serverless nella [pagina Serverless Computing su Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Leggi sull'utilizzo del serverless in Azure, inclusi alcuni esempi, nel [post del blog di Azure "Go serverless for your IoT needs"](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Scopri di più su Azure Functions nel [canale YouTube di Azure Functions](https://www.youtube.com/c/AzureFunctions)

## Compito

[Controllo manuale del relè](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.