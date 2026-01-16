<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-25T16:35:55+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "it"
}
-->
# Esegui il tuo rilevatore di frutta ai margini

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questo video offre una panoramica sull'esecuzione di classificatori di immagini su dispositivi IoT, l'argomento trattato in questa lezione.

[![Custom Vision AI su Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Quiz preliminare alla lezione

[Quiz preliminare alla lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Introduzione

Nella lezione precedente hai utilizzato il tuo classificatore di immagini per distinguere tra frutta matura e acerba, inviando un'immagine catturata dalla fotocamera del tuo dispositivo IoT a un servizio cloud tramite internet. Queste operazioni richiedono tempo, comportano costi e, a seconda del tipo di dati immagine utilizzati, potrebbero avere implicazioni sulla privacy.

In questa lezione imparerai come eseguire modelli di machine learning (ML) ai margini - su dispositivi IoT che operano sulla tua rete locale anziché nel cloud. Scoprirai i vantaggi e gli svantaggi del calcolo ai margini rispetto al calcolo nel cloud, come distribuire il tuo modello AI ai margini e come accedervi dal tuo dispositivo IoT.

In questa lezione tratteremo:

* [Calcolo ai margini](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Registrare un dispositivo IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Configurare un dispositivo IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Esportare il tuo modello](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Preparare il tuo contenitore per la distribuzione](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Distribuire il tuo contenitore](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Utilizzare il tuo dispositivo IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Calcolo ai margini

Il calcolo ai margini implica l'utilizzo di computer che elaborano i dati IoT il più vicino possibile al luogo in cui vengono generati. Invece di eseguire questa elaborazione nel cloud, viene spostata ai margini del cloud - sulla tua rete interna.

![Un diagramma architetturale che mostra i servizi internet nel cloud e i dispositivi IoT su una rete locale](../../../../../translated_images/it/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

Nelle lezioni precedenti, i dispositivi raccoglievano dati e li inviavano al cloud per essere analizzati, eseguendo funzioni serverless o modelli AI nel cloud.

![Un diagramma architetturale che mostra dispositivi IoT su una rete locale che si collegano a dispositivi ai margini, e questi dispositivi ai margini si collegano al cloud](../../../../../translated_images/it/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Il calcolo ai margini sposta alcuni dei servizi cloud fuori dal cloud e li esegue su computer che operano sulla stessa rete dei dispositivi IoT, comunicando con il cloud solo se necessario. Ad esempio, puoi eseguire modelli AI su dispositivi ai margini per analizzare la maturazione della frutta e inviare al cloud solo analisi, come il numero di frutti maturi rispetto a quelli acerbi.

✅ Rifletti sulle applicazioni IoT che hai costruito finora. Quali parti potrebbero essere spostate ai margini?

### Vantaggi

I vantaggi del calcolo ai margini sono:

1. **Velocità** - il calcolo ai margini è ideale per dati sensibili al tempo, poiché le azioni vengono eseguite sulla stessa rete del dispositivo, anziché effettuare chiamate tramite internet. Questo consente velocità più elevate, poiché le reti interne possono funzionare a velocità significativamente superiori rispetto alle connessioni internet, con i dati che viaggiano su distanze molto più brevi.

    > 💁 Nonostante i cavi ottici vengano utilizzati per le connessioni internet, consentendo ai dati di viaggiare alla velocità della luce, i dati possono impiegare tempo per attraversare il mondo fino ai fornitori di servizi cloud. Ad esempio, se invii dati dall'Europa ai servizi cloud negli Stati Uniti, ci vogliono almeno 28 ms per attraversare l'Atlantico tramite un cavo ottico, senza contare il tempo necessario per portare i dati al cavo transatlantico, convertirli da segnali elettrici a segnali luminosi e viceversa dall'altra parte, e infine dal cavo ottico al fornitore di servizi cloud.

    Il calcolo ai margini richiede anche meno traffico di rete, riducendo il rischio che i tuoi dati rallentino a causa della congestione sulla larghezza di banda limitata disponibile per una connessione internet.

1. **Accessibilità remota** - il calcolo ai margini funziona anche quando la connettività è limitata o assente, o quando è troppo costosa per essere utilizzata continuamente. Ad esempio, in aree colpite da disastri umanitari dove l'infrastruttura è limitata, o in nazioni in via di sviluppo.

1. **Costi ridotti** - raccogliere, archiviare, analizzare e attivare azioni sui dispositivi ai margini riduce l'uso dei servizi cloud, il che può ridurre i costi complessivi della tua applicazione IoT. Negli ultimi tempi si è assistito a un aumento di dispositivi progettati per il calcolo ai margini, come le schede acceleratrici AI come il [Jetson Nano di NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), che possono eseguire carichi di lavoro AI utilizzando hardware basato su GPU su dispositivi che costano meno di 100 dollari.

1. **Privacy e sicurezza** - con il calcolo ai margini, i dati rimangono sulla tua rete e non vengono caricati nel cloud. Questo è spesso preferito per informazioni sensibili e identificabili personalmente, soprattutto perché i dati non devono essere archiviati dopo essere stati analizzati, riducendo notevolmente il rischio di fughe di dati. Esempi includono dati medici e filmati di telecamere di sicurezza.

1. **Gestione di dispositivi insicuri** - se hai dispositivi con vulnerabilità di sicurezza note che non vuoi connettere direttamente alla tua rete o a internet, puoi collegarli a una rete separata tramite un dispositivo gateway IoT Edge. Questo dispositivo ai margini può quindi avere una connessione alla tua rete più ampia o a internet, gestendo i flussi di dati avanti e indietro.

1. **Supporto per dispositivi incompatibili** - se hai dispositivi che non possono connettersi a IoT Hub, ad esempio dispositivi che possono connettersi solo tramite connessioni HTTP o dispositivi che hanno solo Bluetooth, puoi utilizzare un dispositivo IoT Edge come dispositivo gateway, inoltrando i messaggi a IoT Hub.

✅ Fai una ricerca: Quali altri vantaggi potrebbe offrire il calcolo ai margini?

### Svantaggi

Ci sono svantaggi nel calcolo ai margini, per cui il cloud potrebbe essere un'opzione preferibile:

1. **Scalabilità e flessibilità** - il calcolo nel cloud può adattarsi alle esigenze di rete e dati in tempo reale aggiungendo o riducendo server e altre risorse. Per aggiungere più computer ai margini è necessario aggiungere manualmente più dispositivi.

1. **Affidabilità e resilienza** - il calcolo nel cloud offre più server spesso in più località per ridondanza e recupero in caso di disastri. Per ottenere lo stesso livello di ridondanza ai margini sono necessari grandi investimenti e molto lavoro di configurazione.

1. **Manutenzione** - i fornitori di servizi cloud si occupano della manutenzione e degli aggiornamenti del sistema.

✅ Fai una ricerca: Quali altri svantaggi potrebbe avere il calcolo ai margini?

Gli svantaggi sono essenzialmente l'opposto dei vantaggi dell'uso del cloud: devi costruire e gestire questi dispositivi da solo, anziché fare affidamento sull'esperienza e sulla scala dei fornitori di servizi cloud.

Alcuni rischi sono mitigati dalla natura stessa del calcolo ai margini. Ad esempio, se hai un dispositivo ai margini che opera in una fabbrica raccogliendo dati da macchinari, non devi preoccuparti di alcuni scenari di recupero in caso di disastri. Se manca l'elettricità nella fabbrica, non hai bisogno di un dispositivo ai margini di backup, poiché anche le macchine che generano i dati elaborati dal dispositivo ai margini saranno senza alimentazione.

Per i sistemi IoT, spesso vorrai una combinazione di calcolo nel cloud e ai margini, sfruttando ciascun servizio in base alle esigenze del sistema, dei suoi utenti e dei suoi manutentori.

## Azure IoT Edge

![Il logo di Azure IoT Edge](../../../../../translated_images/it/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge è un servizio che ti aiuta a spostare i carichi di lavoro fuori dal cloud e ai margini. Configuri un dispositivo come dispositivo ai margini e dal cloud puoi distribuire codice a quel dispositivo. Questo ti consente di combinare le capacità del cloud e dei margini.

> 🎓 *Carichi di lavoro* è un termine che indica qualsiasi servizio che svolge un tipo di lavoro, come modelli AI, applicazioni o funzioni serverless.

Ad esempio, puoi addestrare un classificatore di immagini nel cloud e poi distribuirlo a un dispositivo ai margini. Il tuo dispositivo IoT invia quindi immagini al dispositivo ai margini per la classificazione, anziché inviarle tramite internet. Se hai bisogno di distribuire una nuova iterazione del modello, puoi addestrarlo nel cloud e utilizzare IoT Edge per aggiornare il modello sul dispositivo ai margini con la nuova iterazione.

> 🎓 Il software distribuito su IoT Edge è noto come *moduli*. Per impostazione predefinita, IoT Edge esegue moduli che comunicano con IoT Hub, come i moduli `edgeAgent` e `edgeHub`. Quando distribuisci un classificatore di immagini, questo viene distribuito come modulo aggiuntivo.

IoT Edge è integrato in IoT Hub, quindi puoi gestire i dispositivi ai margini utilizzando lo stesso servizio che utilizzeresti per gestire i dispositivi IoT, con lo stesso livello di sicurezza.

IoT Edge esegue codice da *contenitori* - applicazioni autonome che vengono eseguite in isolamento rispetto al resto delle applicazioni sul tuo computer. Quando esegui un contenitore, si comporta come un computer separato che opera all'interno del tuo computer, con il proprio software, servizi e applicazioni in esecuzione. La maggior parte delle volte i contenitori non possono accedere a nulla sul tuo computer a meno che tu non scelga di condividere, ad esempio, una cartella con il contenitore. Il contenitore espone quindi i servizi tramite una porta aperta a cui puoi connetterti o esporre alla tua rete.

![Una richiesta web reindirizzata a un contenitore](../../../../../translated_images/it/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Ad esempio, puoi avere un contenitore con un sito web in esecuzione sulla porta 80, la porta HTTP predefinita, e puoi quindi esporlo dal tuo computer sempre sulla porta 80.

✅ Fai una ricerca: Leggi informazioni sui contenitori e sui servizi come Docker o Moby.

Puoi utilizzare Custom Vision per scaricare classificatori di immagini e distribuirli come contenitori, eseguendoli direttamente su un dispositivo o distribuendoli tramite IoT Edge. Una volta in esecuzione in un contenitore, possono essere accessibili utilizzando la stessa API REST della versione cloud, ma con l'endpoint che punta al dispositivo ai margini che esegue il contenitore.

## Registrare un dispositivo IoT Edge

Per utilizzare un dispositivo IoT Edge, è necessario registrarlo in IoT Hub.

### Attività - registrare un dispositivo IoT Edge

1. Crea un IoT Hub nel gruppo di risorse `fruit-quality-detector`. Dagli un nome univoco basato su `fruit-quality-detector`.

1. Registra un dispositivo IoT Edge chiamato `fruit-quality-detector-edge` nel tuo IoT Hub. Il comando per farlo è simile a quello utilizzato per registrare un dispositivo non ai margini, ma devi passare il flag `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome del tuo IoT Hub.

1. Ottieni la stringa di connessione per il tuo dispositivo utilizzando il seguente comando:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome del tuo IoT Hub.

    Copia la stringa di connessione mostrata nell'output.

## Configurare un dispositivo IoT Edge

Una volta creata la registrazione del dispositivo ai margini nel tuo IoT Hub, puoi configurare il dispositivo ai margini.

### Attività - Installare e avviare il runtime IoT Edge

**Il runtime IoT Edge esegue solo contenitori Linux.** Può essere eseguito su Linux o su Windows utilizzando macchine virtuali Linux.

* Se stai utilizzando un Raspberry Pi come dispositivo IoT, questo esegue una versione supportata di Linux e può ospitare il runtime IoT Edge. Segui la [guida per installare Azure IoT Edge per Linux su Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) per installare IoT Edge e impostare la stringa di connessione.

    > 💁 Ricorda, Raspberry Pi OS è una variante di Debian Linux.

* Se non stai utilizzando un Raspberry Pi, ma hai un computer Linux, puoi eseguire il runtime IoT Edge. Segui la [guida per installare Azure IoT Edge per Linux su Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) per installare IoT Edge e impostare la stringa di connessione.

* Se stai utilizzando Windows, puoi installare il runtime IoT Edge in una macchina virtuale Linux seguendo la [sezione per installare e avviare il runtime IoT Edge della guida rapida per distribuire il tuo primo modulo IoT Edge su un dispositivo Windows su Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Puoi fermarti quando raggiungi la sezione *Distribuire un modulo*.

* Se stai utilizzando macOS, puoi creare una macchina virtuale (VM) nel cloud da utilizzare come dispositivo IoT Edge. Questi sono computer che puoi creare nel cloud e accedere tramite internet. Puoi creare una VM Linux con IoT Edge installato. Segui la [guida per creare una macchina virtuale che esegue IoT Edge](vm-iotedge.md) per istruzioni su come farlo.

## Esportare il tuo modello

Per eseguire il classificatore ai margini, è necessario esportarlo da Custom Vision. Custom Vision può generare due tipi di modelli: modelli standard e modelli compatti. I modelli compatti utilizzano varie tecniche per ridurre le dimensioni del modello, rendendolo abbastanza piccolo da essere scaricato e distribuito su dispositivi IoT.

Quando hai creato il classificatore di immagini, hai utilizzato il dominio *Food*, una versione del modello ottimizzata per l'addestramento su immagini di cibo. In Custom Vision, puoi cambiare il dominio del tuo progetto, utilizzando i tuoi dati di addestramento per addestrare un nuovo modello con il nuovo dominio. Tutti i domini supportati da Custom Vision sono disponibili sia come standard che come compatti.

### Attività - addestra il tuo modello utilizzando il dominio Food (compatto)
1. Avvia il portale Custom Vision su [CustomVision.ai](https://customvision.ai) e accedi se non lo hai già aperto. Poi apri il tuo progetto `fruit-quality-detector`.

1. Seleziona il pulsante **Impostazioni** (l'icona ⚙).

1. Nella lista *Domini*, seleziona *Food (compact)*.

1. Sotto *Export Capabilities*, assicurati che sia selezionato *Basic platforms (Tensorflow, CoreML, ONNX, ...)*.

1. In fondo alla pagina delle Impostazioni, seleziona **Salva modifiche**.

1. Allena nuovamente il modello con il pulsante **Train**, selezionando *Quick training*.

### Compito - esporta il tuo modello

Una volta che il modello è stato allenato, deve essere esportato come contenitore.

1. Seleziona la scheda **Performance** e trova l'ultima iterazione che è stata allenata utilizzando il dominio compatto.

1. Seleziona il pulsante **Export** in alto.

1. Seleziona **DockerFile**, quindi scegli una versione che corrisponda al tuo dispositivo edge:

    * Se stai eseguendo IoT Edge su un computer Linux, un computer Windows o una macchina virtuale, seleziona la versione *Linux*.
    * Se stai eseguendo IoT Edge su un Raspberry Pi, seleziona la versione *ARM (Raspberry Pi 3)*.

> 🎓 Docker è uno degli strumenti più popolari per gestire i contenitori, e un DockerFile è un insieme di istruzioni su come configurare il contenitore.

1. Seleziona **Export** per far sì che Custom Vision crei i file pertinenti, quindi **Download** per scaricarli in un file zip.

1. Salva i file sul tuo computer, quindi decomprimi la cartella.

## Prepara il tuo contenitore per il deployment

![I contenitori vengono creati, poi inviati a un registro di contenitori, e successivamente distribuiti dal registro di contenitori a un dispositivo edge utilizzando IoT Edge](../../../../../translated_images/it/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Una volta scaricato il tuo modello, deve essere costruito in un contenitore e poi inviato a un registro di contenitori - una posizione online dove puoi archiviare i contenitori. IoT Edge può quindi scaricare il contenitore dal registro e inviarlo al tuo dispositivo.

![Logo di Azure Container Registry](../../../../../translated_images/it/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Il registro di contenitori che utilizzerai per questa lezione è Azure Container Registry. Questo non è un servizio gratuito, quindi per risparmiare denaro assicurati di [pulire il tuo progetto](../../../clean-up.md) una volta terminato.

> 💁 Puoi vedere i costi di utilizzo di un Azure Container Registry nella [pagina dei prezzi di Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Compito - installa Docker

Per costruire e distribuire il classificatore, potresti dover installare [Docker](https://www.docker.com/).

Dovrai farlo solo se prevedi di costruire il contenitore da un dispositivo diverso da quello su cui hai installato IoT Edge - come parte dell'installazione di IoT Edge, Docker viene installato per te.

1. Se stai costruendo il contenitore Docker su un dispositivo diverso dal tuo dispositivo IoT Edge, segui le istruzioni di installazione di Docker sulla [pagina di installazione di Docker](https://www.docker.com/products/docker-desktop) per installare Docker Desktop o il motore Docker. Assicurati che sia in esecuzione dopo l'installazione.

### Compito - crea una risorsa di registro di contenitori

1. Esegui il seguente comando dal tuo Terminale o prompt dei comandi per creare una risorsa Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Sostituisci `<Container registry name>` con un nome univoco per il tuo registro di contenitori, utilizzando solo lettere e numeri. Basalo su `fruitqualitydetector`. Questo nome diventa parte dell'URL per accedere al registro di contenitori, quindi deve essere globalmente unico.

1. Accedi al registro di contenitori Azure con il seguente comando:

    ```sh
    az acr login --name <Container registry name>
    ```

    Sostituisci `<Container registry name>` con il nome che hai usato per il tuo registro di contenitori.

1. Imposta il registro di contenitori in modalità amministratore per poter generare una password con il seguente comando:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Sostituisci `<Container registry name>` con il nome che hai usato per il tuo registro di contenitori.

1. Genera le password per il tuo registro di contenitori con il seguente comando:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Sostituisci `<Container registry name>` con il nome che hai usato per il tuo registro di contenitori.

    Prendi nota del valore di `PASSWORD`, poiché ti servirà più avanti.

### Compito - costruisci il tuo contenitore

Quello che hai scaricato da Custom Vision era un DockerFile contenente istruzioni su come il contenitore dovrebbe essere costruito, insieme al codice applicativo che verrà eseguito all'interno del contenitore per ospitare il tuo modello Custom Vision, insieme a un'API REST per chiamarlo. Puoi usare Docker per costruire un contenitore taggato dal DockerFile e poi inviarlo al tuo registro di contenitori.

> 🎓 I contenitori vengono assegnati un tag che definisce un nome e una versione per loro. Quando hai bisogno di aggiornare un contenitore, puoi costruirlo con lo stesso tag ma una versione più recente.

1. Apri il tuo terminale o prompt dei comandi e naviga al modello decompresso che hai scaricato da Custom Vision.

1. Esegui il seguente comando per costruire e taggare l'immagine:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Sostituisci `<platform>` con la piattaforma su cui questo contenitore verrà eseguito. Se stai eseguendo IoT Edge su un Raspberry Pi, imposta questo valore su `linux/armhf`, altrimenti impostalo su `linux/amd64`.

    > 💁 Se stai eseguendo questo comando dal dispositivo su cui stai eseguendo IoT Edge, come ad esempio dal tuo Raspberry Pi, puoi omettere la parte `--platform <platform>` poiché predefinita alla piattaforma corrente.

    Sostituisci `<Container registry name>` con il nome che hai usato per il tuo registro di contenitori.

    > 💁 Se stai eseguendo su Linux o Raspberry Pi OS potresti dover usare `sudo` per eseguire questo comando.

    Docker costruirà l'immagine, configurando tutto il software necessario. L'immagine verrà poi taggata come `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Compito - invia il tuo contenitore al tuo registro di contenitori

1. Usa il seguente comando per inviare il tuo contenitore al tuo registro di contenitori:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Sostituisci `<Container registry name>` con il nome che hai usato per il tuo registro di contenitori.

    > 💁 Se stai eseguendo su Linux potresti dover usare `sudo` per eseguire questo comando.

    Il contenitore verrà inviato al registro di contenitori.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Per verificare l'invio, puoi elencare i contenitori nel tuo registro con il seguente comando:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Sostituisci `<Container registry name>` con il nome che hai usato per il tuo registro di contenitori.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Vedrai il tuo classificatore elencato nell'output.

## Distribuisci il tuo contenitore

Il tuo contenitore può ora essere distribuito al tuo dispositivo IoT Edge. Per distribuirlo, devi definire un manifesto di distribuzione - un documento JSON che elenca i moduli che verranno distribuiti al dispositivo edge.

### Compito - crea il manifesto di distribuzione

1. Crea un nuovo file chiamato `deployment.json` da qualche parte sul tuo computer.

1. Aggiungi il seguente contenuto a questo file:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Puoi trovare questo file nella cartella [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Sostituisci le tre istanze di `<Container registry name>` con il nome che hai usato per il tuo registro di contenitori. Una è nella sezione del modulo `ImageClassifier`, le altre due sono nella sezione `registryCredentials`.

    Sostituisci `<Container registry password>` nella sezione `registryCredentials` con la password del tuo registro di contenitori.

1. Dalla cartella contenente il tuo manifesto di distribuzione, esegui il seguente comando:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome del tuo IoT Hub.

    Il modulo del classificatore di immagini verrà distribuito al tuo dispositivo edge.

### Compito - verifica che il classificatore sia in esecuzione

1. Connettiti al dispositivo IoT Edge:

    * Se stai utilizzando un Raspberry Pi per eseguire IoT Edge, connettiti utilizzando ssh dal tuo terminale o tramite una sessione SSH remota in VS Code.
    * Se stai eseguendo IoT Edge in un contenitore Linux su Windows, segui i passaggi nella [guida alla verifica della configurazione riuscita](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) per connetterti al dispositivo IoT Edge.
    * Se stai eseguendo IoT Edge su una macchina virtuale, puoi accedere alla macchina tramite SSH utilizzando `adminUsername` e `password` impostati durante la creazione della VM, e utilizzando l'indirizzo IP o il nome DNS:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Oppure:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Inserisci la tua password quando richiesto.

1. Una volta connesso, esegui il seguente comando per ottenere l'elenco dei moduli IoT Edge:

    ```sh
    iotedge list
    ```

    > 💁 Potresti dover eseguire questo comando con `sudo`.

    Vedrai i moduli in esecuzione:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Controlla i log per il modulo del classificatore di immagini con il seguente comando:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Potresti dover eseguire questo comando con `sudo`.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Compito - testa il classificatore di immagini

1. Puoi usare CURL per testare il classificatore di immagini utilizzando l'indirizzo IP o il nome host del computer che sta eseguendo l'agente IoT Edge. Trova l'indirizzo IP:

    * Se sei sulla stessa macchina su cui IoT Edge è in esecuzione, puoi usare `localhost` come nome host.
    * Se stai usando una VM, puoi usare l'indirizzo IP o il nome DNS della VM.
    * Altrimenti puoi ottenere l'indirizzo IP della macchina che esegue IoT Edge:
      * Su Windows 10, segui la [guida per trovare il tuo indirizzo IP](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Su macOS, segui la [guida su come trovare il tuo indirizzo IP su Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Su Linux, segui la sezione su come trovare il tuo indirizzo IP privato nella [guida su come trovare il tuo indirizzo IP in Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Puoi testare il contenitore con un file locale eseguendo il seguente comando curl:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Sostituisci `<IP address or name>` con l'indirizzo IP o il nome host del computer che esegue IoT Edge. Sostituisci `<file_Name>` con il nome del file da testare.

    Vedrai i risultati della previsione nell'output:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Non è necessario fornire una chiave di previsione qui, poiché non si sta utilizzando una risorsa Azure. Invece, la sicurezza verrebbe configurata sulla rete interna basandosi sulle esigenze di sicurezza interne, piuttosto che affidarsi a un endpoint pubblico e a una chiave API.

## Usa il tuo dispositivo IoT Edge

Ora che il tuo classificatore di immagini è stato distribuito su un dispositivo IoT Edge, puoi usarlo dal tuo dispositivo IoT.

### Compito - usa il tuo dispositivo IoT Edge

Segui la guida pertinente per classificare immagini utilizzando il classificatore IoT Edge:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Computer a scheda singola - Raspberry Pi/Dispositivo IoT virtuale](single-board-computer.md)

### Riaddestramento del modello

Uno degli svantaggi di eseguire classificatori di immagini su IoT Edge è che non sono connessi al tuo progetto Custom Vision. Se guardi la scheda **Predictions** in Custom Vision, non vedrai le immagini che sono state classificate utilizzando il classificatore basato su Edge.

Questo è il comportamento previsto - le immagini non vengono inviate al cloud per la classificazione, quindi non saranno disponibili nel cloud. Uno dei vantaggi di utilizzare IoT Edge è la privacy, garantendo che le immagini non lascino la tua rete, un altro è la possibilità di lavorare offline, quindi non dipendere dal caricamento delle immagini quando il dispositivo non ha connessione internet. Lo svantaggio è migliorare il tuo modello - dovresti implementare un altro modo per archiviare le immagini che possono essere riclassificate manualmente per migliorare e riaddestrare il classificatore di immagini.

✅ Pensa a modi per caricare immagini per riaddestrare il classificatore.

---

## 🚀 Sfida

Eseguire modelli di intelligenza artificiale su dispositivi edge può essere più veloce rispetto al cloud - il salto di rete è più breve. Possono anche essere più lenti poiché l'hardware che esegue il modello potrebbe non essere potente come il cloud.

Fai alcune misurazioni e confronta se la chiamata al tuo dispositivo edge è più veloce o più lenta rispetto alla chiamata al cloud? Pensa a motivi per spiegare la differenza, o la mancanza di differenza. Ricerca modi per eseguire modelli di intelligenza artificiale più velocemente sull'edge utilizzando hardware specializzato.

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Revisione e studio autonomo

* Leggi di più sui contenitori nella [pagina sulla virtualizzazione a livello di sistema operativo su Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization).
* Leggi di più sull'edge computing, con un focus su come il 5G può contribuire ad espandere l'edge computing nell'[articolo "Cos'è l'edge computing e perché è importante?" su NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Scopri di più sull'esecuzione di servizi AI in IoT Edge guardando l'[episodio "Impara come utilizzare Azure IoT Edge su un servizio AI preconfigurato sull'Edge per rilevare il linguaggio" di Learn Live su Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Compito

[Esegui altri servizi sull'edge](assignment.md)

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un esperto umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.