<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-25T17:05:24+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "it"
}
-->
# Migra la tua pianta al cloud

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questa lezione è stata insegnata come parte della serie [IoT for Beginners Project 2 - Digital Agriculture](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) del [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Collega il tuo dispositivo al cloud con Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Quiz preliminare alla lezione

[Quiz preliminare alla lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Introduzione

Nella lezione precedente, hai imparato a collegare la tua pianta a un broker MQTT e a controllare un relè tramite codice server in esecuzione localmente. Questo rappresenta il nucleo di un sistema di irrigazione automatizzato connesso a Internet, utilizzato sia per piante singole a casa che per aziende agricole commerciali.

Il dispositivo IoT ha comunicato con un broker MQTT pubblico per dimostrare i principi di base, ma questo non è il metodo più affidabile o sicuro. In questa lezione imparerai cos'è il cloud e le capacità IoT offerte dai servizi cloud pubblici. Inoltre, scoprirai come migrare la tua pianta da un broker MQTT pubblico a uno di questi servizi cloud.

In questa lezione tratteremo:

* [Cos'è il cloud?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Crea un abbonamento al cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Servizi IoT nel cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Crea un servizio IoT nel cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Comunica con IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Collega il tuo dispositivo al servizio IoT](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Cos'è il cloud?

Prima del cloud, quando un'azienda voleva fornire servizi ai propri dipendenti (come database o archiviazione file) o al pubblico (come siti web), doveva costruire e gestire un data center. Questo poteva variare da una stanza con pochi computer a un edificio con molti computer. L'azienda doveva gestire tutto, inclusi:

* Acquisto dei computer
* Manutenzione dell'hardware
* Alimentazione e raffreddamento
* Rete
* Sicurezza, sia dell'edificio che del software sui computer
* Installazione e aggiornamenti del software

Questo poteva essere molto costoso, richiedere una vasta gamma di competenze e risultare molto lento da adattare ai cambiamenti. Ad esempio, se un negozio online doveva prepararsi per una stagione di vacanze intensa, doveva pianificare mesi in anticipo per acquistare più hardware, configurarlo, installarlo e installare il software necessario per gestire le vendite. Dopo la stagione intensa, con il calo delle vendite, si ritrovava con computer inutilizzati fino alla prossima stagione.

✅ Pensi che questo permettesse alle aziende di muoversi rapidamente? Se un rivenditore di abbigliamento online diventasse improvvisamente popolare perché una celebrità indossa i suoi vestiti, sarebbe in grado di aumentare rapidamente la potenza di calcolo per gestire l'afflusso improvviso di ordini?

### Il computer di qualcun altro

Il cloud viene spesso scherzosamente definito "il computer di qualcun altro". L'idea iniziale era semplice: invece di acquistare computer, si affittano quelli di qualcun altro. Un fornitore di cloud computing gestisce enormi data center, occupandosi di acquistare e installare l'hardware, gestire alimentazione e raffreddamento, rete, sicurezza dell'edificio, aggiornamenti hardware e software, tutto. Come cliente, affitti i computer di cui hai bisogno, aumentando il numero durante i picchi di domanda e riducendolo quando la domanda cala. Questi data center cloud sono distribuiti in tutto il mondo.

![Un data center cloud di Microsoft](../../../../../translated_images/it/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.png)
![Espansione pianificata di un data center cloud di Microsoft](../../../../../translated_images/it/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.png)

Questi data center possono occupare diversi chilometri quadrati. Le immagini sopra, scattate alcuni anni fa in un data center cloud di Microsoft, mostrano le dimensioni iniziali e un'espansione pianificata. L'area destinata all'espansione supera i 5 chilometri quadrati.

> 💁 Questi data center richiedono così tanta energia che alcuni hanno proprie centrali elettriche. Grazie alle loro dimensioni e agli investimenti dei fornitori di cloud, sono solitamente molto ecologici. Sono più efficienti rispetto a numerosi piccoli data center, funzionano principalmente con energia rinnovabile e i fornitori di cloud lavorano per ridurre gli sprechi, limitare l'uso dell'acqua e ripiantare foreste per compensare quelle abbattute per costruire i data center. Puoi leggere di più su come un fornitore di cloud sta lavorando sulla sostenibilità sul sito [Azure sustainability](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Fai una ricerca: Leggi sui principali fornitori di cloud come [Azure di Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) o [GCP di Google](https://cloud.google.com). Quanti data center hanno e dove si trovano nel mondo?

Utilizzare il cloud riduce i costi per le aziende e consente loro di concentrarsi su ciò che sanno fare meglio, lasciando l'expertise sul cloud computing nelle mani del fornitore. Le aziende non devono più affittare o acquistare spazi per data center, pagare diversi fornitori per connettività e alimentazione o assumere esperti. Invece, possono pagare una sola fattura mensile al fornitore di cloud per avere tutto gestito.

Il fornitore di cloud può quindi sfruttare le economie di scala per ridurre i costi, acquistando computer in grandi quantità a prezzi più bassi, investendo in strumenti per ridurre il carico di lavoro per la manutenzione e persino progettando e costruendo il proprio hardware per migliorare l'offerta cloud.

### Microsoft Azure

Azure è il cloud per sviluppatori di Microsoft, ed è il cloud che utilizzerai in queste lezioni. Il video qui sotto offre una breve panoramica di Azure:

[![Video panoramica di Azure](../../../../../translated_images/it/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Crea un abbonamento al cloud

Per utilizzare i servizi nel cloud, dovrai registrarti per un abbonamento con un fornitore di cloud. In questa lezione, ti registrerai per un abbonamento a Microsoft Azure. Se hai già un abbonamento Azure, puoi saltare questa attività. I dettagli dell'abbonamento descritti qui sono corretti al momento della scrittura, ma potrebbero cambiare.

> 💁 Se stai seguendo queste lezioni tramite la tua scuola, potresti già avere un abbonamento Azure disponibile. Controlla con il tuo insegnante.

Esistono due tipi di abbonamento gratuito a Azure a cui puoi registrarti:

* **Azure for Students** - Questo abbonamento è pensato per studenti di età pari o superiore a 18 anni. Non è necessaria una carta di credito per registrarsi e si utilizza l'indirizzo email scolastico per convalidare lo stato di studente. Quando ti registri, ricevi 100 USD da spendere in risorse cloud, oltre a servizi gratuiti, incluso una versione gratuita di un servizio IoT. Questo abbonamento dura 12 mesi e può essere rinnovato ogni anno in cui rimani studente.

* **Abbonamento gratuito Azure** - Questo abbonamento è per chiunque non sia studente. È necessaria una carta di credito per registrarsi, ma la carta non verrà addebitata, serve solo per verificare che tu sia una persona reale e non un bot. Ricevi 200 USD di credito da utilizzare nei primi 30 giorni su qualsiasi servizio, oltre a livelli gratuiti di servizi Azure. Una volta esaurito il credito, la carta non verrà addebitata a meno che tu non converta l'abbonamento in uno a consumo.

> 💁 Microsoft offre un abbonamento Azure for Students Starter per studenti sotto i 18 anni, ma al momento della scrittura non supporta servizi IoT.

### Attività - registrati per un abbonamento cloud gratuito

Se sei uno studente di età pari o superiore a 18 anni, puoi registrarti per un abbonamento Azure for Students. Dovrai convalidare con un indirizzo email scolastico. Puoi farlo in due modi:

* Registrati per un pacchetto GitHub Student Developer Pack su [education.github.com/pack](https://education.github.com/pack). Questo ti dà accesso a una gamma di strumenti e offerte, incluso GitHub e Microsoft Azure. Una volta registrato per il pacchetto sviluppatore, puoi attivare l'offerta Azure for Students.

* Registrati direttamente per un account Azure for Students su [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Se il tuo indirizzo email scolastico non viene riconosciuto, apri un [issue in questo repository](https://github.com/Microsoft/IoT-For-Beginners/issues) e vedremo se può essere aggiunto alla lista consentita di Azure for Students.

Se non sei uno studente o non hai un indirizzo email scolastico valido, puoi registrarti per un abbonamento gratuito Azure.

* Registrati per un abbonamento gratuito Azure su [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Servizi IoT nel cloud

Il broker MQTT pubblico che hai utilizzato è uno strumento eccellente per imparare, ma presenta diversi svantaggi per un utilizzo in ambito commerciale:

* Affidabilità - è un servizio gratuito senza garanzie, che può essere disattivato in qualsiasi momento
* Sicurezza - è pubblico, quindi chiunque potrebbe intercettare la tua telemetria o inviare comandi per controllare il tuo hardware
* Prestazioni - è progettato per pochi messaggi di test, quindi non sarebbe in grado di gestire un grande volume di messaggi
* Scoperta - non c'è modo di sapere quali dispositivi sono connessi

I servizi IoT nel cloud risolvono questi problemi. Sono gestiti da grandi fornitori di cloud che investono molto nell'affidabilità e sono pronti a risolvere eventuali problemi. Hanno la sicurezza integrata per impedire agli hacker di leggere i tuoi dati o inviare comandi non autorizzati. Inoltre, offrono alte prestazioni, essendo in grado di gestire milioni di messaggi ogni giorno, sfruttando il cloud per scalare secondo necessità.

> 💁 Sebbene questi vantaggi abbiano un costo mensile, la maggior parte dei fornitori di cloud offre una versione gratuita del proprio servizio IoT con un numero limitato di messaggi al giorno o dispositivi che possono connettersi. Questa versione gratuita è solitamente più che sufficiente per uno sviluppatore che vuole imparare a utilizzare il servizio. In questa lezione utilizzerai una versione gratuita.

I dispositivi IoT si connettono a un servizio cloud utilizzando un SDK per dispositivi (una libreria che fornisce codice per lavorare con le funzionalità del servizio) o direttamente tramite un protocollo di comunicazione come MQTT o HTTP. L'SDK per dispositivi è solitamente la strada più semplice, poiché gestisce tutto per te, come sapere a quali topic pubblicare o sottoscriversi e come gestire la sicurezza.

![I dispositivi si connettono a un servizio utilizzando un SDK per dispositivi. Anche il codice server si connette al servizio tramite un SDK](../../../../../translated_images/it/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.png)

Il tuo dispositivo comunica quindi con altre parti della tua applicazione tramite questo servizio, in modo simile a come hai inviato telemetria e ricevuto comandi tramite MQTT. Questo avviene solitamente utilizzando un SDK per servizi o una libreria simile. I messaggi arrivano dal tuo dispositivo al servizio, dove altre componenti della tua applicazione possono leggerli, e i messaggi possono essere inviati al tuo dispositivo.

![I dispositivi senza una chiave segreta valida non possono connettersi al servizio IoT](../../../../../translated_images/it/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.png)

Questi servizi implementano la sicurezza conoscendo tutti i dispositivi che possono connettersi e inviare dati, sia registrando i dispositivi in anticipo, sia fornendo loro chiavi segrete o certificati che possono utilizzare per registrarsi al servizio la prima volta che si connettono. I dispositivi sconosciuti non possono connettersi: se ci provano, il servizio rifiuta la connessione e ignora i messaggi inviati da loro.

✅ Fai una ricerca: Qual è lo svantaggio di avere un servizio IoT aperto dove qualsiasi dispositivo o codice può connettersi? Riesci a trovare esempi specifici di hacker che hanno sfruttato questa situazione?

Altre componenti della tua applicazione possono connettersi al servizio IoT e conoscere tutti i dispositivi connessi o registrati, comunicando con loro direttamente, sia in massa che individualmente.
💁 I servizi IoT implementano anche funzionalità aggiuntive, e i provider cloud offrono ulteriori servizi e applicazioni che possono essere collegati al servizio. Ad esempio, se desideri archiviare tutti i messaggi di telemetria inviati da tutti i dispositivi in un database, di solito bastano pochi clic nello strumento di configurazione del provider cloud per collegare il servizio a un database e trasmettere i dati.
## Crea un servizio IoT nel cloud

Ora che hai un abbonamento Azure, puoi iscriverti a un servizio IoT. Il servizio IoT di Microsoft si chiama Azure IoT Hub.

![Il logo di Azure IoT Hub](../../../../../translated_images/it/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.png)

Il video qui sotto offre una breve panoramica di Azure IoT Hub:

[![Video panoramica di Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Clicca sull'immagine sopra per guardare il video

✅ Dedica un momento a fare qualche ricerca e leggi la panoramica di IoT Hub nella [documentazione di Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

I servizi cloud disponibili in Azure possono essere configurati tramite un portale web o un'interfaccia a riga di comando (CLI). Per questo compito, utilizzerai la CLI.

### Compito - installare Azure CLI

Per utilizzare Azure CLI, devi prima installarla sul tuo PC o Mac.

1. Segui le istruzioni nella [documentazione di Azure CLI](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) per installare la CLI.

1. Azure CLI supporta una serie di estensioni che aggiungono funzionalità per gestire una vasta gamma di servizi Azure. Installa l'estensione IoT eseguendo il seguente comando dalla tua riga di comando o terminale:

    ```sh
    az extension add --name azure-iot
    ```

1. Dalla tua riga di comando o terminale, esegui il seguente comando per accedere al tuo abbonamento Azure tramite Azure CLI.

    ```sh
    az login
    ```

    Si aprirà una pagina web nel tuo browser predefinito. Accedi utilizzando l'account che hai usato per registrarti al tuo abbonamento Azure. Una volta effettuato l'accesso, puoi chiudere la scheda del browser.

1. Se hai più abbonamenti Azure, come uno fornito dalla scuola e uno tuo personale Azure for Students, dovrai selezionare quello che desideri utilizzare. Esegui il seguente comando per elencare tutti gli abbonamenti a cui hai accesso:

    ```sh
    az account list --output table
    ```

    Nell'output, vedrai il nome di ciascun abbonamento insieme al suo `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Per selezionare l'abbonamento che desideri utilizzare, usa il seguente comando:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Sostituisci `<SubscriptionId>` con l'Id dell'abbonamento che desideri utilizzare. Dopo aver eseguito questo comando, esegui nuovamente il comando per elencare i tuoi account. Vedrai che la colonna `IsDefault` sarà contrassegnata come `True` per l'abbonamento appena impostato.

### Compito - creare un gruppo di risorse

I servizi Azure, come le istanze di IoT Hub, le macchine virtuali, i database o i servizi di intelligenza artificiale, sono chiamati **risorse**. Ogni risorsa deve appartenere a un **gruppo di risorse**, un raggruppamento logico di una o più risorse.

> 💁 Utilizzare i gruppi di risorse significa che puoi gestire più servizi contemporaneamente. Ad esempio, una volta completate tutte le lezioni di questo progetto, puoi eliminare il gruppo di risorse e tutte le risorse al suo interno verranno eliminate automaticamente.

1. Esistono diversi data center Azure in tutto il mondo, suddivisi in regioni. Quando crei una risorsa o un gruppo di risorse Azure, devi specificare dove desideri che venga creato. Esegui il seguente comando per ottenere l'elenco delle posizioni:

    ```sh
    az account list-locations --output table
    ```

    Vedrai un elenco di posizioni. Questo elenco sarà lungo.

    > 💁 Al momento della scrittura, ci sono 65 posizioni in cui puoi distribuire.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Annota il valore della colonna `Name` della regione più vicina a te. Puoi trovare le regioni su una mappa nella [pagina delle geografie di Azure](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Esegui il seguente comando per creare un gruppo di risorse chiamato `soil-moisture-sensor`. I nomi dei gruppi di risorse devono essere unici nel tuo abbonamento.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Sostituisci `<location>` con la posizione selezionata nel passaggio precedente.

### Compito - creare un IoT Hub

Ora puoi creare una risorsa IoT Hub nel tuo gruppo di risorse.

1. Usa il seguente comando per creare la tua risorsa IoT Hub:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Sostituisci `<hub_name>` con un nome per il tuo hub. Questo nome deve essere univoco a livello globale - cioè nessun altro IoT Hub creato da chiunque può avere lo stesso nome. Questo nome viene utilizzato in un URL che punta all'hub, quindi deve essere univoco. Usa qualcosa come `soil-moisture-sensor-` e aggiungi un identificatore univoco alla fine, come alcune parole casuali o il tuo nome.

    L'opzione `--sku F1` indica di utilizzare un livello gratuito. Il livello gratuito supporta 8.000 messaggi al giorno insieme alla maggior parte delle funzionalità dei livelli a pagamento.

    > 🎓 I diversi livelli di prezzo dei servizi Azure sono chiamati tier. Ogni tier ha un costo diverso e offre funzionalità o volumi di dati differenti.

    > 💁 Se vuoi saperne di più sui prezzi, puoi consultare la [guida ai prezzi di Azure IoT Hub](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    L'opzione `--partition-count 2` definisce quante stream di dati l'IoT Hub supporta. Più partizioni riducono i blocchi di dati quando più dispositivi leggono e scrivono dall'IoT Hub. Le partizioni sono al di fuori dello scopo di queste lezioni, ma questo valore deve essere impostato per creare un IoT Hub di livello gratuito.

    > 💁 Puoi avere solo un IoT Hub di livello gratuito per abbonamento.

L'IoT Hub verrà creato. Potrebbe volerci un minuto o due per completare l'operazione.

## Comunicare con IoT Hub

Nella lezione precedente, hai utilizzato MQTT per inviare messaggi avanti e indietro su diversi topic, con i diversi topic che avevano scopi differenti. Invece di inviare messaggi su diversi topic, IoT Hub ha una serie di modalità definite per consentire al dispositivo di comunicare con l'Hub o viceversa.

> 💁 Dietro le quinte, questa comunicazione tra IoT Hub e il tuo dispositivo può utilizzare MQTT, HTTPS o AMQP.

* Messaggi da dispositivo a cloud (D2C) - questi sono messaggi inviati da un dispositivo a IoT Hub, come la telemetria. Possono poi essere letti dall'IoT Hub tramite il codice della tua applicazione.

    > 🎓 Dietro le quinte, IoT Hub utilizza un servizio Azure chiamato [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Quando scrivi codice per leggere i messaggi inviati all'hub, questi sono spesso chiamati eventi.

* Messaggi da cloud a dispositivo (C2D) - questi sono messaggi inviati dal codice dell'applicazione, tramite un IoT Hub, a un dispositivo IoT.

* Richieste di metodo diretto - questi sono messaggi inviati dal codice dell'applicazione tramite un IoT Hub a un dispositivo IoT per richiedere che il dispositivo esegua un'azione, come controllare un attuatore. Questi messaggi richiedono una risposta affinché il codice dell'applicazione possa sapere se sono stati elaborati con successo.

* Device twins - questi sono documenti JSON mantenuti sincronizzati tra il dispositivo e IoT Hub, e vengono utilizzati per memorizzare impostazioni o altre proprietà segnalate dal dispositivo o che devono essere impostate sul dispositivo (note come desiderate) da IoT Hub.

IoT Hub può memorizzare messaggi e richieste di metodo diretto per un periodo di tempo configurabile (di default un giorno), quindi se un dispositivo o il codice dell'applicazione perde la connessione, può comunque recuperare i messaggi inviati mentre era offline una volta riconnesso. I device twins vengono mantenuti permanentemente in IoT Hub, quindi in qualsiasi momento un dispositivo può riconnettersi e ottenere l'ultimo device twin.

✅ Fai qualche ricerca: Leggi di più su questi tipi di messaggi nella [guida alla comunicazione da dispositivo a cloud](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) e nella [guida alla comunicazione da cloud a dispositivo](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) nella documentazione di IoT Hub.

## Connettere il tuo dispositivo al servizio IoT

Una volta creato l'hub, il tuo dispositivo IoT può connettersi ad esso. Solo i dispositivi registrati possono connettersi a un servizio, quindi dovrai registrare il tuo dispositivo per primo. Quando lo registri, otterrai una stringa di connessione che il dispositivo può utilizzare per connettersi. Questa stringa di connessione è specifica per il dispositivo e contiene informazioni sull'IoT Hub, sul dispositivo e una chiave segreta che consentirà a questo dispositivo di connettersi.

> 🎓 Una stringa di connessione è un termine generico per un testo che contiene dettagli di connessione. Vengono utilizzate per connettersi a IoT Hub, database e molti altri servizi. Di solito consistono in un identificatore per il servizio, come un URL, e informazioni di sicurezza come una chiave segreta. Queste vengono passate agli SDK per connettersi al servizio.

> ⚠️ Le stringhe di connessione devono essere mantenute sicure! La sicurezza verrà trattata in modo più dettagliato in una lezione futura.

### Compito - registrare il tuo dispositivo IoT

Il dispositivo IoT può essere registrato con il tuo IoT Hub utilizzando Azure CLI.

1. Esegui il seguente comando per registrare un dispositivo:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome che hai usato per il tuo IoT Hub.

    Questo creerà un dispositivo con un ID di `soil-moisture-sensor`.

1. Quando il tuo dispositivo IoT si connette al tuo IoT Hub utilizzando l'SDK, deve utilizzare una stringa di connessione che fornisce l'URL dell'hub, insieme a una chiave segreta. Esegui il seguente comando per ottenere la stringa di connessione:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome che hai usato per il tuo IoT Hub.

1. Conserva la stringa di connessione mostrata nell'output poiché ti servirà più avanti.

### Compito - connettere il tuo dispositivo IoT al cloud

Segui la guida pertinente per connettere il tuo dispositivo IoT al cloud:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-connect-hub.md)

### Compito - monitorare gli eventi

Per ora, non aggiornerai il codice del server. Invece, puoi utilizzare Azure CLI per monitorare gli eventi dal tuo dispositivo IoT.

1. Assicurati che il tuo dispositivo IoT sia in esecuzione e stia inviando valori di telemetria sull'umidità del suolo.

1. Esegui il seguente comando nel tuo prompt dei comandi o terminale per monitorare i messaggi inviati al tuo IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome che hai usato per il tuo IoT Hub.

    Vedrai i messaggi apparire nell'output della console man mano che vengono inviati dal tuo dispositivo IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Il contenuto del `payload` corrisponderà al messaggio inviato dal tuo dispositivo IoT.

    > Al momento della scrittura, l'estensione `az iot` non funziona completamente su Apple Silicon. Se stai utilizzando un dispositivo Apple Silicon, dovrai monitorare i messaggi in un modo diverso, ad esempio utilizzando gli [Azure IoT Tools per Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Questi messaggi hanno un certo numero di proprietà allegate automaticamente, come il timestamp in cui sono stati inviati. Queste sono note come *annotazioni*. Per visualizzare tutte le annotazioni dei messaggi, utilizza il seguente comando:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome che hai usato per il tuo IoT Hub.

    Vedrai i messaggi apparire nell'output della console man mano che vengono inviati dal tuo dispositivo IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    I valori temporali nelle annotazioni sono in [tempo UNIX](https://wikipedia.org/wiki/Unix_time), che rappresenta il numero di secondi trascorsi dalla mezzanotte del 1° gennaio 1970.

    Esci dal monitor eventi quando hai finito.

### Compito - controllare il tuo dispositivo IoT

Puoi anche utilizzare Azure CLI per chiamare metodi diretti sul tuo dispositivo IoT.

1. Esegui il seguente comando nel tuo prompt dei comandi o terminale per invocare il metodo `relay_on` sul dispositivo IoT:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Sostituisci `
<hub_name>
` con il nome che hai usato per il tuo IoT Hub.

    Questo invia una richiesta di metodo diretto per il metodo specificato da `method-name`. I metodi diretti possono accettare un payload contenente dati per il metodo, e questo può essere specificato nel parametro `method-payload` come JSON.

    Vedrai il relè accendersi e l'output corrispondente dal tuo dispositivo IoT:

    ```output
    Direct method received -  relay_on
    ```

1. Ripeti il passaggio precedente, ma imposta `--method-name` su `relay_off`. Vedrai il relè spegnersi e l'output corrispondente dal dispositivo IoT.

---

## 🚀 Sfida

Il livello gratuito di IoT Hub consente 8.000 messaggi al giorno. Il codice che hai scritto invia messaggi di telemetria ogni 10 secondi. Quanti messaggi al giorno corrispondono a un messaggio ogni 10 secondi?

Pensa a quanto spesso dovrebbero essere inviati i dati sull'umidità del suolo. Come puoi modificare il tuo codice per rimanere entro il limite del livello gratuito e controllare con la frequenza necessaria ma non troppo spesso? E se volessi aggiungere un secondo dispositivo?

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Revisione e studio autonomo

L'SDK di IoT Hub è open source sia per Arduino che per Python. Nei repository di codice su GitHub ci sono numerosi esempi che mostrano come lavorare con diverse funzionalità di IoT Hub.

* Se stai usando un Wio Terminal, dai un'occhiata agli [esempi Arduino su GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Se stai usando un Raspberry Pi o un dispositivo virtuale, dai un'occhiata agli [esempi Python su GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Compito

[Scopri i servizi cloud](assignment.md)

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale eseguita da un traduttore umano. Non siamo responsabili per eventuali malintesi o interpretazioni errate derivanti dall'uso di questa traduzione.