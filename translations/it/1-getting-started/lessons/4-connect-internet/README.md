# Collega il tuo dispositivo a Internet

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-4.7344e074ea68fa54.webp)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questa lezione è stata insegnata come parte della serie [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) del [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). La lezione è stata suddivisa in 2 video: una lezione di 1 ora e un'ora di sessione di domande e risposte per approfondire alcuni aspetti e rispondere alle domande.

[![Lezione 4: Collega il tuo dispositivo a Internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lezione 4: Collega il tuo dispositivo a Internet - Sessione di domande e risposte](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Clicca sulle immagini sopra per guardare i video

## Quiz preliminare

[Quiz preliminare](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Introduzione

La **I** in IoT sta per **Internet** - la connettività cloud e i servizi che abilitano molte delle funzionalità dei dispositivi IoT, dalla raccolta di misurazioni dai sensori collegati al dispositivo, all'invio di messaggi per controllare gli attuatori. I dispositivi IoT si connettono tipicamente a un singolo servizio cloud IoT utilizzando un protocollo di comunicazione standard, e quel servizio è connesso al resto della tua applicazione IoT, dai servizi di intelligenza artificiale per prendere decisioni intelligenti sui tuoi dati, alle app web per il controllo o la reportistica.

> 🎓 I dati raccolti dai sensori e inviati al cloud sono chiamati telemetria.

I dispositivi IoT possono ricevere messaggi dal cloud. Spesso questi messaggi contengono comandi, ovvero istruzioni per eseguire un'azione internamente (come riavviare o aggiornare il firmware) o utilizzando un attuatore (come accendere una luce).

Questa lezione introduce alcuni dei protocolli di comunicazione che i dispositivi IoT possono utilizzare per connettersi al cloud e i tipi di dati che potrebbero inviare o ricevere. Inoltre, avrai l'opportunità di sperimentarli direttamente, aggiungendo il controllo via Internet alla tua luce notturna, spostando la logica di controllo del LED al codice 'server' in esecuzione localmente.

In questa lezione tratteremo:

* [Protocolli di comunicazione](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetria](../../../../../1-getting-started/lessons/4-connect-internet)
* [Comandi](../../../../../1-getting-started/lessons/4-connect-internet)

## Protocolli di comunicazione

Esistono diversi protocolli di comunicazione popolari utilizzati dai dispositivi IoT per comunicare con Internet. I più comuni si basano sulla messaggistica publish/subscribe tramite un broker. I dispositivi IoT si connettono al broker, pubblicano telemetria e si iscrivono ai comandi. Anche i servizi cloud si connettono al broker, si iscrivono a tutti i messaggi di telemetria e pubblicano comandi a dispositivi specifici o a gruppi di dispositivi.

![I dispositivi IoT si connettono a un broker, pubblicano telemetria e si iscrivono ai comandi. I servizi cloud si connettono al broker, si iscrivono a tutta la telemetria e inviano comandi a dispositivi specifici.](../../../../../translated_images/it/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT è il protocollo di comunicazione più popolare per i dispositivi IoT ed è trattato in questa lezione. Altri protocolli includono AMQP e HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) è un protocollo di messaggistica leggero e open standard che può inviare messaggi tra dispositivi. È stato progettato nel 1999 per monitorare oleodotti, prima di essere rilasciato come standard open 15 anni dopo da IBM.

MQTT utilizza un singolo broker e più client. Tutti i client si connettono al broker, e il broker instrada i messaggi ai client pertinenti. I messaggi vengono instradati utilizzando argomenti denominati, piuttosto che essere inviati direttamente a un singolo client. Un client può pubblicare su un argomento, e tutti i client che si iscrivono a quell'argomento riceveranno il messaggio.

![Dispositivo IoT che pubblica telemetria sull'argomento /telemetry, e il servizio cloud che si iscrive a quell'argomento](../../../../../translated_images/it/mqtt.cbf7f21d9adc3e17.webp)

✅ Fai una ricerca. Se hai molti dispositivi IoT, come puoi assicurarti che il tuo broker MQTT sia in grado di gestire tutti i messaggi?

### Collega il tuo dispositivo IoT a MQTT

La prima parte per aggiungere il controllo via Internet alla tua luce notturna è connetterla a un broker MQTT.

#### Compito

Collega il tuo dispositivo a un broker MQTT.

In questa parte della lezione, collegherai la tua luce notturna IoT a Internet per consentirne il controllo remoto. Più avanti nella lezione, il tuo dispositivo IoT invierà un messaggio di telemetria tramite MQTT a un broker MQTT pubblico con il livello di luce, dove sarà raccolto da un codice server che scriverai. Questo codice controllerà il livello di luce e invierà un messaggio di comando al dispositivo per accendere o spegnere il LED.

Un caso d'uso reale per una configurazione del genere potrebbe essere raccogliere dati da più sensori di luce prima di decidere di accendere le luci, in un luogo con molte luci, come uno stadio. Questo potrebbe impedire l'accensione delle luci se solo un sensore fosse coperto da nuvole o da un uccello, ma gli altri sensori rilevassero abbastanza luce.

✅ Quali altre situazioni richiederebbero la valutazione dei dati di più sensori prima di inviare comandi?

Piuttosto che affrontare le complessità di configurare un broker MQTT come parte di questo compito, puoi utilizzare un server di test pubblico che esegue [Eclipse Mosquitto](https://www.mosquitto.org), un broker MQTT open-source. Questo broker di test è disponibile pubblicamente su [test.mosquitto.org](https://test.mosquitto.org) e non richiede la creazione di un account, rendendolo uno strumento ideale per testare client e server MQTT.

> 💁 Questo broker di test è pubblico e non sicuro. Chiunque potrebbe ascoltare ciò che pubblichi, quindi non dovrebbe essere utilizzato con dati che devono rimanere privati.

![Diagramma di flusso dell'assegnazione che mostra i livelli di luce letti e controllati, e il controllo del LED](../../../../../translated_images/it/assignment-1-internet-flow.3256feab5f052fd2.webp)

Segui il passaggio pertinente qui sotto per connettere il tuo dispositivo al broker MQTT:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Computer a scheda singola - Raspberry Pi/Dispositivo IoT virtuale](single-board-computer-mqtt.md)

### Un approfondimento su MQTT

Gli argomenti possono avere una gerarchia, e i client possono iscriversi a diversi livelli della gerarchia utilizzando caratteri jolly. Ad esempio, puoi inviare messaggi di telemetria della temperatura all'argomento `/telemetry/temperature` e messaggi di umidità all'argomento `/telemetry/humidity`, quindi nella tua app cloud iscriverti all'argomento `/telemetry/*` per ricevere sia i messaggi di telemetria della temperatura che dell'umidità.

I messaggi possono essere inviati con un livello di qualità del servizio (QoS), che determina la garanzia di ricezione del messaggio.

* Al massimo una volta - il messaggio viene inviato solo una volta e il client e il broker non intraprendono ulteriori azioni per riconoscere la consegna (fire and forget).
* Almeno una volta - il messaggio viene ritentato dal mittente più volte fino a quando non viene ricevuta una conferma (consegna riconosciuta).
* Esattamente una volta - il mittente e il destinatario si impegnano in una stretta di mano a due livelli per garantire che venga ricevuta solo una copia del messaggio (consegna garantita).

✅ Quali situazioni potrebbero richiedere un messaggio con consegna garantita rispetto a un messaggio fire and forget?

Sebbene il nome sia Message Queueing (le iniziali in MQTT), in realtà non supporta le code di messaggi. Ciò significa che se un client si disconnette e poi si riconnette, non riceverà i messaggi inviati durante la disconnessione, tranne per quei messaggi che aveva già iniziato a elaborare utilizzando il processo QoS. I messaggi possono avere un flag di conservazione impostato su di essi. Se questo è impostato, il broker MQTT memorizzerà l'ultimo messaggio inviato su un argomento con questo flag e lo invierà a qualsiasi client che successivamente si iscrive all'argomento. In questo modo, i client riceveranno sempre l'ultimo messaggio.

MQTT supporta anche una funzione di keep alive che controlla se la connessione è ancora attiva durante lunghi intervalli tra i messaggi.

> 🦟 [Mosquitto della Eclipse Foundation](https://mosquitto.org) offre un broker MQTT gratuito che puoi eseguire per sperimentare MQTT, insieme a un broker MQTT pubblico che puoi utilizzare per testare il tuo codice, ospitato su [test.mosquitto.org](https://test.mosquitto.org).

Le connessioni MQTT possono essere pubbliche e aperte, o crittografate e protette utilizzando nomi utente e password, o certificati.

> 💁 MQTT comunica su TCP/IP, lo stesso protocollo di rete sottostante di HTTP, ma su una porta diversa. Puoi anche utilizzare MQTT su websocket per comunicare con app web in esecuzione in un browser, o in situazioni in cui firewall o altre regole di rete bloccano le connessioni MQTT standard.

## Telemetria

La parola telemetria deriva da radici greche che significano misurare a distanza. La telemetria è l'atto di raccogliere dati dai sensori e inviarli al cloud.

> 💁 Uno dei primi dispositivi di telemetria fu inventato in Francia nel 1874 e inviava in tempo reale dati meteorologici e sulla neve dal Monte Bianco a Parigi. Utilizzava fili fisici poiché le tecnologie wireless non erano disponibili all'epoca.

Torniamo all'esempio del termostato intelligente dalla Lezione 1.

![Un termostato connesso a Internet che utilizza sensori in più stanze](../../../../../translated_images/it/telemetry.21e5d8b97649d2eb.webp)

Il termostato ha sensori di temperatura per raccogliere telemetria. Probabilmente avrebbe un sensore di temperatura integrato e potrebbe connettersi a più sensori di temperatura esterni tramite un protocollo wireless come il [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Un esempio di dati di telemetria che potrebbe inviare potrebbe essere:

| Nome | Valore | Descrizione |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | La temperatura misurata dal sensore di temperatura integrato del termostato |
| `livingroom_temperature` | 19°C | La temperatura misurata da un sensore di temperatura remoto che è stato chiamato `livingroom` per identificare la stanza in cui si trova |
| `bedroom_temperature` | 21°C | La temperatura misurata da un sensore di temperatura remoto che è stato chiamato `bedroom` per identificare la stanza in cui si trova |

Il servizio cloud può quindi utilizzare questi dati di telemetria per prendere decisioni sui comandi da inviare per controllare il riscaldamento.

### Invia telemetria dal tuo dispositivo IoT

La prossima parte per aggiungere il controllo via Internet alla tua luce notturna è inviare la telemetria del livello di luce al broker MQTT su un argomento di telemetria.

#### Compito - invia telemetria dal tuo dispositivo IoT

Invia la telemetria del livello di luce al broker MQTT.

I dati vengono inviati codificati come JSON - acronimo di JavaScript Object Notation, uno standard per codificare i dati in testo utilizzando coppie chiave/valore.

✅ Se non hai mai sentito parlare di JSON prima, puoi saperne di più nella [documentazione di JSON.org](https://www.json.org/).

Segui il passaggio pertinente qui sotto per inviare telemetria dal tuo dispositivo al broker MQTT:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Computer a scheda singola - Raspberry Pi/Dispositivo IoT virtuale](single-board-computer-telemetry.md)

### Ricevi telemetria dal broker MQTT

Non ha senso inviare telemetria se non c'è nulla dall'altra parte per ascoltarla. La telemetria del livello di luce ha bisogno di qualcosa che la ascolti per elaborare i dati. Questo codice 'server' è il tipo di codice che distribuirai a un servizio cloud come parte di un'applicazione IoT più ampia, ma qui eseguirai questo codice localmente sul tuo computer (o sul tuo Pi se stai programmando direttamente lì). Il codice server consiste in un'app Python che ascolta i messaggi di telemetria tramite MQTT con i livelli di luce. Più avanti in questa lezione, lo farai rispondere con un messaggio di comando con istruzioni per accendere o spegnere il LED.

✅ Fai una ricerca: Cosa succede ai messaggi MQTT se non c'è nessun ascoltatore?

#### Installa Python e VS Code

Se non hai Python e VS Code installati localmente, dovrai installarli entrambi per scrivere il codice del server. Se stai utilizzando un dispositivo IoT virtuale o stai lavorando sul tuo Raspberry Pi, puoi saltare questo passaggio poiché dovresti già averli installati e configurati.

##### Compito - installa Python e VS Code

Installa Python e VS Code.

1. Installa Python. Consulta la [pagina dei download di Python](https://www.python.org/downloads/) per le istruzioni su come installare l'ultima versione di Python.

2. Installa Visual Studio Code (VS Code). Questo è l'editor che utilizzerai per scrivere il codice del dispositivo virtuale in Python. Consulta la [documentazione di VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) per le istruzioni su come installare VS Code.
💁 Sei libero di utilizzare qualsiasi IDE o editor Python per queste lezioni se hai uno strumento preferito, ma le lezioni forniranno istruzioni basate sull'uso di VS Code.
1. Installa l'estensione Pylance per VS Code. Questa è un'estensione per VS Code che fornisce supporto per il linguaggio Python. Consulta la [documentazione dell'estensione Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) per le istruzioni su come installare questa estensione in VS Code.

#### Configurare un ambiente virtuale Python

Una delle caratteristiche più potenti di Python è la possibilità di installare [pacchetti pip](https://pypi.org), ovvero pacchetti di codice scritti da altri e pubblicati su Internet. Puoi installare un pacchetto pip sul tuo computer con un solo comando e poi utilizzarlo nel tuo codice. Userai pip per installare un pacchetto per comunicare tramite MQTT.

Per impostazione predefinita, quando installi un pacchetto, esso è disponibile ovunque sul tuo computer, e questo può causare problemi con le versioni dei pacchetti, ad esempio quando un'applicazione dipende da una versione di un pacchetto che smette di funzionare se installi una nuova versione per un'altra applicazione. Per risolvere questo problema, puoi utilizzare un [ambiente virtuale Python](https://docs.python.org/3/library/venv.html), essenzialmente una copia di Python in una cartella dedicata, e quando installi pacchetti pip, essi vengono installati solo in quella cartella.

##### Attività - configurare un ambiente virtuale Python

Configura un ambiente virtuale Python e installa i pacchetti pip per MQTT.

1. Dal tuo terminale o dalla riga di comando, esegui il seguente comando in una posizione a tua scelta per creare e navigare in una nuova directory:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Ora esegui il seguente comando per creare un ambiente virtuale nella cartella `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Devi chiamare esplicitamente `python3` per creare l'ambiente virtuale nel caso in cui tu abbia installato Python 2 oltre a Python 3 (l'ultima versione). Se hai Python 2 installato, chiamando `python` verrà utilizzato Python 2 invece di Python 3.

1. Attiva l'ambiente virtuale:

    * Su Windows:
        * Se stai usando il Prompt dei comandi o il Prompt dei comandi tramite Windows Terminal, esegui:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Se stai usando PowerShell, esegui:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Su macOS o Linux, esegui:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Questi comandi devono essere eseguiti dalla stessa posizione in cui hai eseguito il comando per creare l'ambiente virtuale. Non sarà mai necessario navigare nella cartella `.venv`, dovresti sempre eseguire il comando di attivazione e qualsiasi comando per installare pacchetti o eseguire codice dalla cartella in cui ti trovavi quando hai creato l'ambiente virtuale.

1. Una volta attivato l'ambiente virtuale, il comando predefinito `python` eseguirà la versione di Python utilizzata per creare l'ambiente virtuale. Esegui il seguente comando per ottenere la versione:

    ```sh
    python --version
    ```

    L'output sarà simile al seguente:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 La tua versione di Python potrebbe essere diversa: finché è la versione 3.6 o superiore, va bene. In caso contrario, elimina questa cartella, installa una versione più recente di Python e riprova.

1. Esegui i seguenti comandi per installare il pacchetto pip per [Paho-MQTT](https://pypi.org/project/paho-mqtt/), una libreria MQTT popolare.

    ```sh
    pip install paho-mqtt
    ```

    Questo pacchetto pip sarà installato solo nell'ambiente virtuale e non sarà disponibile al di fuori di esso.

#### Scrivere il codice del server

Ora è possibile scrivere il codice del server in Python.

##### Attività - scrivere il codice del server

Scrivi il codice del server.

1. Dal tuo terminale o dalla riga di comando, esegui il seguente comando all'interno dell'ambiente virtuale per creare un file Python chiamato `app.py`:

    * Su Windows, esegui:

        ```cmd
        type nul > app.py
        ```

    * Su macOS o Linux, esegui:

        ```cmd
        touch app.py
        ```

1. Apri la cartella corrente in VS Code:

    ```sh
    code .
    ```

1. Quando VS Code si avvia, attiverà l'ambiente virtuale Python. Questo sarà riportato nella barra di stato in basso:

    ![VS Code che mostra l'ambiente virtuale selezionato](../../../../../translated_images/it/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Se il terminale di VS Code è già in esecuzione quando VS Code si avvia, non avrà l'ambiente virtuale attivato. La cosa più semplice da fare è chiudere il terminale utilizzando il pulsante **Kill the active terminal instance**:

    ![Pulsante di chiusura del terminale attivo in VS Code](../../../../../translated_images/it/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Avvia un nuovo terminale di VS Code selezionando *Terminal -> New Terminal*, o premendo `` CTRL+` ``. Il nuovo terminale caricherà l'ambiente virtuale, con la chiamata per attivarlo che apparirà nel terminale. Il nome dell'ambiente virtuale (`.venv`) sarà anche nel prompt:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Apri il file `app.py` dall'esploratore di VS Code e aggiungi il seguente codice:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Sostituisci `<ID>` alla riga 6 con l'ID univoco che hai usato quando hai creato il codice del tuo dispositivo.

    ⚠️ Questo **deve** essere lo stesso ID che hai usato sul tuo dispositivo, altrimenti il codice del server non si iscriverà o pubblicherà sul topic corretto.

    Questo codice crea un client MQTT con un nome univoco e si connette al broker *test.mosquitto.org*. Successivamente avvia un ciclo di elaborazione che funziona su un thread in background ascoltando i messaggi su qualsiasi topic sottoscritto.

    Il client si iscrive quindi ai messaggi sul topic di telemetria e definisce una funzione che viene chiamata quando un messaggio viene ricevuto. Quando un messaggio di telemetria viene ricevuto, la funzione `handle_telemetry` viene chiamata, stampando il messaggio ricevuto sulla console.

    Infine, un ciclo infinito mantiene l'applicazione in esecuzione. Il client MQTT ascolta i messaggi su un thread in background e funziona per tutto il tempo in cui l'applicazione principale è in esecuzione.

1. Dal terminale di VS Code, esegui il seguente comando per eseguire la tua app Python:

    ```sh
    python app.py
    ```

    L'app inizierà ad ascoltare i messaggi dal dispositivo IoT.

1. Assicurati che il tuo dispositivo sia in esecuzione e stia inviando messaggi di telemetria. Regola i livelli di luce rilevati dal tuo dispositivo fisico o virtuale. I messaggi ricevuti verranno stampati nel terminale.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Il file app.py nell'ambiente virtuale nightlight deve essere in esecuzione affinché il file app.py nell'ambiente virtuale nightlight-server riceva i messaggi inviati.

> 💁 Puoi trovare questo codice nella cartella [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Con quale frequenza inviare la telemetria?

Una considerazione importante con la telemetria è: con quale frequenza misurare e inviare i dati? La risposta è: dipende. Se misuri spesso, puoi rispondere più rapidamente ai cambiamenti, ma utilizzi più energia, più larghezza di banda, generi più dati e hai bisogno di più risorse cloud per elaborarli. Devi misurare abbastanza spesso, ma non troppo spesso.

Per un termostato, misurare ogni pochi minuti è probabilmente più che sufficiente, poiché le temperature non cambiano così frequentemente. Se misuri solo una volta al giorno, potresti finire per riscaldare la tua casa per temperature notturne nel bel mezzo di una giornata di sole, mentre se misuri ogni secondo avrai migliaia di misurazioni duplicate inutilmente che consumeranno la velocità e la larghezza di banda di Internet degli utenti (un problema per chi ha piani di larghezza di banda limitata), utilizzeranno più energia, il che può essere un problema per dispositivi alimentati a batteria come i sensori remoti, e aumenteranno il costo delle risorse di elaborazione e archiviazione del cloud del fornitore.

Se stai monitorando i dati di un macchinario in una fabbrica che, se si guasta, potrebbe causare danni catastrofici e milioni di dollari di perdite, allora potrebbe essere necessario misurare più volte al secondo. È meglio sprecare larghezza di banda che perdere telemetria che indica che una macchina deve essere fermata e riparata prima che si rompa.

> 💁 In questa situazione, potresti considerare di avere un dispositivo edge per elaborare prima la telemetria e ridurre la dipendenza da Internet.

### Perdita di connettività

Le connessioni Internet possono essere inaffidabili, con interruzioni comuni. Cosa dovrebbe fare un dispositivo IoT in queste circostanze: perdere i dati o conservarli fino al ripristino della connettività? Ancora una volta, la risposta è: dipende.

Per un termostato, i dati possono probabilmente essere persi non appena viene effettuata una nuova misurazione della temperatura. Il sistema di riscaldamento non si preoccupa che 20 minuti fa fosse 20,5°C se ora la temperatura è 19°C; è la temperatura attuale che determina se il riscaldamento deve essere acceso o spento.

Per i macchinari, potresti voler conservare i dati, specialmente se vengono utilizzati per cercare tendenze. Esistono modelli di machine learning che possono rilevare anomalie nei flussi di dati osservando i dati di un determinato periodo di tempo (ad esempio l'ultima ora) e individuando dati anomali. Questo viene spesso utilizzato per la manutenzione predittiva, cercando indicazioni che qualcosa potrebbe rompersi presto in modo da poterlo riparare o sostituire prima che accada. Potresti voler inviare ogni bit di telemetria di una macchina affinché possa essere elaborata per il rilevamento delle anomalie, quindi una volta che il dispositivo IoT può riconnettersi, invierà tutta la telemetria generata durante l'interruzione di Internet.

I progettisti di dispositivi IoT dovrebbero anche considerare se il dispositivo IoT può essere utilizzato durante un'interruzione di Internet o una perdita di segnale causata dalla posizione. Un termostato intelligente dovrebbe essere in grado di prendere alcune decisioni limitate per controllare il riscaldamento se non può inviare telemetria al cloud a causa di un'interruzione.

[![Questa Ferrari è stata bloccata perché qualcuno ha provato ad aggiornarla sottoterra dove non c'è ricezione cellulare](../../../../../translated_images/it/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Per MQTT, per gestire una perdita di connettività, il codice del dispositivo e del server dovrà essere responsabile di garantire la consegna dei messaggi se necessario, ad esempio richiedendo che tutti i messaggi inviati siano risposti con messaggi aggiuntivi su un topic di risposta, e se non lo sono, vengono messi in coda manualmente per essere riprodotti in seguito.

## Comandi

I comandi sono messaggi inviati dal cloud a un dispositivo, che gli istruiscono di fare qualcosa. La maggior parte delle volte ciò comporta la generazione di un output tramite un attuatore, ma può essere un'istruzione per il dispositivo stesso, come riavviarsi o raccogliere telemetria aggiuntiva e restituirla come risposta al comando.

![Un termostato connesso a Internet che riceve un comando per accendere il riscaldamento](../../../../../translated_images/it/commands.d6c06bbbb3a02cce.webp)

Un termostato potrebbe ricevere un comando dal cloud per accendere il riscaldamento. Basandosi sui dati di telemetria di tutti i sensori, se il servizio cloud ha deciso che il riscaldamento deve essere acceso, invia il comando pertinente.

### Inviare comandi al broker MQTT

Il passo successivo per la nostra luce notturna controllata da Internet è che il codice del server invii un comando al dispositivo IoT per controllare la luce in base ai livelli di luce che rileva.

1. Apri il codice del server in VS Code.

1. Aggiungi la seguente riga dopo la dichiarazione del `client_telemetry_topic` per definire quale topic utilizzare per inviare comandi:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Aggiungi il seguente codice alla fine della funzione `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Questo invia un messaggio JSON al topic dei comandi con il valore di `led_on` impostato su true o false a seconda che la luce sia inferiore a 300 o meno. Se la luce è inferiore a 300, viene inviato true per istruire il dispositivo ad accendere il LED.

1. Esegui il codice come prima.

1. Regola i livelli di luce rilevati dal tuo dispositivo fisico o virtuale. I messaggi ricevuti e i comandi inviati verranno scritti nel terminale:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 La telemetria e i comandi vengono inviati su un singolo topic ciascuno. Ciò significa che la telemetria di più dispositivi apparirà sullo stesso topic di telemetria e i comandi per più dispositivi appariranno sullo stesso topic di comandi. Se volessi inviare un comando a un dispositivo specifico, potresti utilizzare più topic, nominati con un ID dispositivo univoco, come `/commands/device1`, `/commands/device2`. In questo modo un dispositivo può ascoltare solo i messaggi destinati a quel dispositivo specifico.

> 💁 Puoi trovare questo codice nella cartella [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Gestire i comandi sul dispositivo IoT

Ora che i comandi vengono inviati dal server, puoi aggiungere il codice al dispositivo IoT per gestirli e controllare il LED.

Segui il passaggio pertinente qui sotto per ascoltare i comandi dal broker MQTT:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-commands.md)

Una volta che questo codice è stato scritto ed eseguito, sperimenta cambiando i livelli di luce. Osserva l'output dal server e dal dispositivo, e guarda il LED mentre cambi i livelli di luce.

### Perdita di connettività

Cosa dovrebbe fare un servizio cloud se deve inviare un comando a un dispositivo IoT che è offline? Ancora una volta, la risposta è: dipende.

Se l'ultimo comando sovrascrive uno precedente, allora i comandi precedenti possono probabilmente essere ignorati. Se un servizio cloud invia un comando per accendere il riscaldamento, poi invia un comando per spegnerlo, allora il comando di accensione può essere ignorato e non reinviato.

Se i comandi devono essere elaborati in sequenza, ad esempio spostare un braccio robotico verso l'alto e poi chiudere una pinza, allora devono essere inviati in ordine una volta ripristinata la connettività.

✅ Come potrebbe il codice del dispositivo o del server garantire che i comandi vengano sempre inviati e gestiti in ordine tramite MQTT, se necessario?

---

## 🚀 Sfida

La sfida nelle ultime tre lezioni era elencare quanti più dispositivi IoT possibile che si trovano nella tua casa, scuola o luogo di lavoro e decidere se sono basati su microcontrollori o single-board computer, o anche una combinazione di entrambi, e pensare a quali sensori e attuatori stanno utilizzando.
Per questi dispositivi, pensa ai messaggi che potrebbero inviare o ricevere. Quali dati di telemetria inviano? Quali messaggi o comandi potrebbero ricevere? Pensi che siano sicuri?

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Revisione e studio autonomo

Leggi di più su MQTT nella [pagina Wikipedia di MQTT](https://wikipedia.org/wiki/MQTT).

Prova a eseguire un broker MQTT da solo utilizzando [Mosquitto](https://www.mosquitto.org) e connettiti ad esso dal tuo dispositivo IoT e dal codice del server.

> 💁 Suggerimento - per impostazione predefinita, Mosquitto non consente connessioni anonime (cioè connessioni senza nome utente e password) e non consente connessioni dall'esterno del computer su cui è in esecuzione.  
> Puoi risolvere questo problema con un [`mosquitto.conf` file di configurazione](https://www.mosquitto.org/man/mosquitto-conf-5.html) con il seguente contenuto:  
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Compito

[Confronta e metti a confronto MQTT con altri protocolli di comunicazione](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.