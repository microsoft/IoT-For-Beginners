# Attivare il rilevamento della qualità della frutta da un sensore

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-18.92c32ed1d354caa5.webp)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

## Quiz preliminare alla lezione

[Quiz preliminare alla lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Introduzione

Un'applicazione IoT non è semplicemente un singolo dispositivo che cattura dati e li invia al cloud, ma spesso è composta da più dispositivi che lavorano insieme per raccogliere dati dal mondo fisico tramite sensori, prendere decisioni basate su quei dati e interagire con il mondo fisico tramite attuatori o visualizzazioni.

In questa lezione imparerai di più sull'architettura di applicazioni IoT complesse, integrando più sensori, diversi servizi cloud per analizzare e archiviare i dati, e mostrando una risposta tramite un attuatore. Imparerai come progettare un prototipo di sistema di controllo della qualità della frutta, incluso l'uso di sensori di prossimità per attivare l'applicazione IoT e quale sarebbe l'architettura di questo prototipo.

In questa lezione tratteremo:

* [Progettare applicazioni IoT complesse](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Progettare un sistema di controllo della qualità della frutta](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Attivare il controllo della qualità della frutta da un sensore](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Dati utilizzati per un rilevatore di qualità della frutta](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Utilizzare dispositivi di sviluppo per simulare più dispositivi IoT](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Passare alla produzione](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Questa è l'ultima lezione di questo progetto, quindi dopo aver completato questa lezione e l'assegnazione, non dimenticare di pulire i tuoi servizi cloud. Avrai bisogno dei servizi per completare l'assegnazione, quindi assicurati di completarla prima.
>
> Consulta [la guida per pulire il tuo progetto](../../../clean-up.md) se necessario per istruzioni su come farlo.

## Progettare applicazioni IoT complesse

Le applicazioni IoT sono composte da molti componenti. Questo include una varietà di dispositivi e servizi internet.

Le applicazioni IoT possono essere descritte come *cose* (dispositivi) che inviano dati che generano *intuizioni*. Queste *intuizioni* generano *azioni* per migliorare un'attività o un processo. Un esempio è un motore (la cosa) che invia dati sulla temperatura. Questi dati vengono utilizzati per valutare se il motore sta funzionando come previsto (l'intuizione). L'intuizione viene utilizzata per dare priorità proattiva alla manutenzione del motore (l'azione).

* Dispositivi diversi raccolgono dati diversi.
* I servizi IoT forniscono intuizioni su quei dati, a volte arricchendoli con dati provenienti da fonti aggiuntive.
* Queste intuizioni guidano azioni, inclusa la gestione degli attuatori nei dispositivi o la visualizzazione dei dati.

### Architettura IoT di riferimento

![Un'architettura IoT di riferimento](../../../../../translated_images/it/iot-reference-architecture.2278b98b55c6d4e8.webp)

Il diagramma sopra mostra un'architettura IoT di riferimento.

> 🎓 Un'architettura di riferimento è un esempio di architettura che puoi utilizzare come guida quando progetti nuovi sistemi. In questo caso, se stai costruendo un nuovo sistema IoT, puoi seguire l'architettura di riferimento, sostituendo i tuoi dispositivi e servizi dove appropriato.

* **Cose** sono dispositivi che raccolgono dati dai sensori, magari interagendo con servizi edge per interpretare quei dati, come classificatori di immagini per interpretare dati visivi. I dati dai dispositivi vengono inviati a un servizio IoT.
* **Intuizioni** derivano da applicazioni serverless o da analisi eseguite su dati archiviati.
* **Azioni** possono essere comandi inviati ai dispositivi o visualizzazioni di dati che permettono agli esseri umani di prendere decisioni.

![Un'architettura IoT di riferimento](../../../../../translated_images/it/iot-reference-architecture-azure.0b8d2161af924cb1.webp)

Il diagramma sopra mostra alcuni dei componenti e servizi trattati finora in queste lezioni e come si collegano insieme in un'architettura IoT di riferimento.

* **Cose** - hai scritto codice per dispositivi per catturare dati dai sensori e analizzare immagini utilizzando Custom Vision, sia nel cloud che su un dispositivo edge. Questi dati sono stati inviati a IoT Hub.
* **Intuizioni** - hai utilizzato Azure Functions per rispondere ai messaggi inviati a un IoT Hub e archiviare dati per analisi successive in Azure Storage.
* **Azioni** - hai controllato attuatori basandoti su decisioni prese nel cloud e comandi inviati ai dispositivi, e hai visualizzato dati utilizzando Azure Maps.

✅ Pensa ad altri dispositivi IoT che hai utilizzato, come elettrodomestici intelligenti. Quali sono le cose, le intuizioni e le azioni coinvolte in quel dispositivo e nel suo software?

Questo schema può essere scalato in grande o in piccolo, aggiungendo più dispositivi e più servizi.

### Dati e sicurezza

Quando definisci l'architettura del tuo sistema, devi considerare costantemente i dati e la sicurezza.

* Quali dati invia e riceve il tuo dispositivo?
* Come dovrebbero essere protetti e garantiti quei dati?
* Come dovrebbe essere controllato l'accesso al dispositivo e al servizio cloud?

✅ Pensa alla sicurezza dei dati di qualsiasi dispositivo IoT che possiedi. Quanto di quei dati è personale e dovrebbe essere mantenuto privato, sia durante il transito che quando archiviato? Quali dati non dovrebbero essere archiviati?

## Progettare un sistema di controllo della qualità della frutta

Applichiamo ora l'idea di cose, intuizioni e azioni al nostro rilevatore di qualità della frutta per progettare un'applicazione end-to-end più grande.

Immagina di aver ricevuto il compito di costruire un rilevatore di qualità della frutta da utilizzare in un impianto di lavorazione. La frutta viaggia su un sistema di nastri trasportatori dove attualmente i dipendenti dedicano tempo a controllare la frutta manualmente e a rimuovere quella acerba. Per ridurre i costi, il proprietario dell'impianto vuole un sistema automatizzato.

✅ Una delle tendenze con l'ascesa dell'IoT (e della tecnologia in generale) è che i lavori manuali vengono sostituiti dalle macchine. Fai una ricerca: Quanti lavori si stima saranno persi a causa dell'IoT? Quanti nuovi lavori saranno creati per costruire dispositivi IoT?

Devi costruire un sistema in cui la frutta viene rilevata quando arriva sul nastro trasportatore, viene fotografata e controllata utilizzando un modello AI che gira sull'edge. I risultati vengono poi inviati al cloud per essere archiviati e, se la frutta è acerba, viene inviata una notifica per rimuoverla.

|   |   |
| - | - |
| **Cose** | Rilevatore per la frutta che arriva sul nastro trasportatore<br>Fotocamera per fotografare e classificare la frutta<br>Dispositivo edge che esegue il classificatore<br>Dispositivo per notificare la presenza di frutta acerba |
| **Intuizioni** | Decidere di controllare la maturità della frutta<br>Archiviare i risultati della classificazione della maturità<br>Determinare se è necessario un avviso per la frutta acerba |
| **Azioni** | Inviare un comando a un dispositivo per fotografare la frutta e controllarla con un classificatore di immagini<br>Inviare un comando a un dispositivo per avvisare che la frutta è acerba |

### Prototipare la tua applicazione

![Un'architettura IoT di riferimento per il controllo della qualità della frutta](../../../../../translated_images/it/iot-reference-architecture-fruit-quality.cc705f121c3b6fa7.webp)

Il diagramma sopra mostra un'architettura di riferimento per questa applicazione prototipo.

* Un dispositivo IoT con un sensore di prossimità rileva l'arrivo della frutta. Questo invia un messaggio al cloud per segnalare che la frutta è stata rilevata.
* Un'applicazione serverless nel cloud invia un comando a un altro dispositivo per scattare una fotografia e classificare l'immagine.
* Un dispositivo IoT con una fotocamera scatta una foto e la invia a un classificatore di immagini che gira sull'edge. I risultati vengono poi inviati al cloud.
* Un'applicazione serverless nel cloud archivia queste informazioni per essere analizzate successivamente per vedere quale percentuale di frutta è acerba. Se la frutta è acerba, invia un comando a un altro dispositivo IoT per avvisare i lavoratori della fabbrica tramite un LED.

> 💁 Questa intera applicazione IoT potrebbe essere implementata come un singolo dispositivo, con tutta la logica per avviare la classificazione delle immagini e controllare il LED integrata. Potrebbe utilizzare un IoT Hub solo per tracciare il numero di frutti acerbi rilevati e configurare il dispositivo. In questa lezione è espansa per dimostrare i concetti per applicazioni IoT su larga scala.

Per il prototipo, implementerai tutto questo su un singolo dispositivo. Se stai utilizzando un microcontrollore, utilizzerai un dispositivo edge separato per eseguire il classificatore di immagini. Hai già imparato la maggior parte delle cose di cui avrai bisogno per costruirlo.

## Attivare il controllo della qualità della frutta da un sensore

Il dispositivo IoT ha bisogno di un qualche tipo di trigger per indicare quando la frutta è pronta per essere classificata. Un trigger potrebbe essere misurare quando la frutta è nella posizione giusta sul nastro trasportatore, rilevando la distanza con un sensore.

![I sensori di prossimità inviano raggi laser agli oggetti come le banane e misurano il tempo necessario affinché il raggio venga riflesso](../../../../../translated_images/it/proximity-sensor.f5cd752c77fb62fe.webp)

I sensori di prossimità possono essere utilizzati per misurare la distanza tra il sensore e un oggetto. Solitamente trasmettono un raggio di radiazione elettromagnetica, come un raggio laser o luce infrarossa, e rilevano la radiazione riflessa da un oggetto. Il tempo tra l'invio del raggio laser e il segnale riflesso può essere utilizzato per calcolare la distanza dal sensore.

> 💁 Probabilmente hai utilizzato sensori di prossimità senza nemmeno accorgertene. La maggior parte degli smartphone spegne lo schermo quando li avvicini all'orecchio per evitare di terminare accidentalmente una chiamata con il lobo dell'orecchio, e questo funziona grazie a un sensore di prossimità che rileva un oggetto vicino allo schermo durante una chiamata e disabilita le capacità touch finché il telefono non è a una certa distanza.

### Compito - attivare il rilevamento della qualità della frutta con un sensore di distanza

Segui la guida pertinente per utilizzare un sensore di prossimità per rilevare un oggetto utilizzando il tuo dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Computer a scheda singola - Raspberry Pi](pi-proximity.md)
* [Computer a scheda singola - Dispositivo virtuale](virtual-device-proximity.md)

## Dati utilizzati per un rilevatore di qualità della frutta

Il prototipo del rilevatore di frutta ha più componenti che comunicano tra loro.

![I componenti che comunicano tra loro](../../../../../translated_images/it/fruit-quality-detector-message-flow.adf2a65da8fd8741.webp)

* Un sensore di prossimità che misura la distanza da un pezzo di frutta e invia questi dati a IoT Hub
* Il comando per controllare la fotocamera proveniente da IoT Hub al dispositivo con la fotocamera
* I risultati della classificazione delle immagini inviati a IoT Hub
* Il comando per controllare un LED per avvisare quando la frutta è acerba inviato da IoT Hub al dispositivo con il LED

È utile definire la struttura di questi messaggi in anticipo, prima di costruire l'applicazione.

> 💁 Praticamente ogni sviluppatore esperto ha passato ore, giorni o persino settimane a cercare di risolvere bug causati da differenze nei dati inviati rispetto a quelli previsti.

Ad esempio - se stai inviando informazioni sulla temperatura, come definiresti il JSON? Potresti avere un campo chiamato `temperature`, oppure potresti usare l'abbreviazione comune `temp`.

```json
{
    "temperature": 20.7
}
```

rispetto a:

```json
{
    "temp": 20.7
}
```

Devi anche considerare le unità - la temperatura è in °C o °F? Se stai misurando la temperatura con un dispositivo consumer e l'utente cambia le unità di visualizzazione, devi assicurarti che le unità inviate al cloud rimangano coerenti.

✅ Fai una ricerca: Come hanno causato problemi di unità il crash del Mars Climate Orbiter da 125 milioni di dollari?

Pensa ai dati inviati per il rilevatore di qualità della frutta. Come definiresti ogni messaggio? Dove analizzeresti i dati e prenderesti decisioni su quali dati inviare?

Ad esempio - attivare la classificazione delle immagini utilizzando il sensore di prossimità. Il dispositivo IoT misura la distanza, ma dove viene presa la decisione? Il dispositivo decide che la frutta è abbastanza vicina e invia un messaggio per dire a IoT Hub di attivare la classificazione? Oppure invia misurazioni di prossimità e lascia che IoT Hub decida?

La risposta a domande come questa è - dipende. Ogni caso d'uso è diverso, motivo per cui come sviluppatore IoT devi comprendere il sistema che stai costruendo, come viene utilizzato e i dati rilevati.

* Se la decisione viene presa da IoT Hub, devi inviare più misurazioni di distanza.
* Se invii troppi messaggi, aumenti il costo di IoT Hub e la quantità di larghezza di banda necessaria ai tuoi dispositivi IoT (soprattutto in una fabbrica con milioni di dispositivi). Può anche rallentare il tuo dispositivo.
* Se prendi la decisione sul dispositivo, dovrai fornire un modo per configurare il dispositivo per ottimizzare la macchina.

## Utilizzare dispositivi di sviluppo per simulare più dispositivi IoT

Per costruire il tuo prototipo, avrai bisogno del tuo kit di sviluppo IoT per simulare più dispositivi, inviando telemetria e rispondendo ai comandi.

### Simulare più dispositivi IoT su un Raspberry Pi o hardware IoT virtuale

Quando utilizzi un computer a scheda singola come un Raspberry Pi, puoi eseguire più applicazioni contemporaneamente. Questo significa che puoi simulare più dispositivi IoT creando più applicazioni, una per ogni 'dispositivo IoT'. Ad esempio, puoi implementare ogni dispositivo come un file Python separato ed eseguirli in sessioni terminali diverse.
💁 Tieni presente che alcuni hardware potrebbero non funzionare se vengono utilizzati contemporaneamente da più applicazioni in esecuzione.
### Simulare più dispositivi su un microcontrollore

I microcontrollori sono più complicati da utilizzare per simulare più dispositivi. A differenza dei computer a scheda singola, non è possibile eseguire più applicazioni contemporaneamente; è necessario includere tutta la logica per tutti i dispositivi IoT separati in un'unica applicazione.

Alcuni suggerimenti per rendere questo processo più semplice sono:

* Creare una o più classi per ogni dispositivo IoT - ad esempio, classi chiamate `DistanceSensor`, `ClassifierCamera`, `LEDController`. Ognuna di queste può avere i propri metodi `setup` e `loop` chiamati dalle funzioni principali `setup` e `loop`.
* Gestire i comandi in un unico punto e indirizzarli alla classe del dispositivo pertinente, secondo necessità.
* Nella funzione principale `loop`, sarà necessario considerare il timing per ogni dispositivo diverso. Ad esempio, se si dispone di una classe di dispositivo che deve elaborare ogni 10 secondi e un'altra che deve elaborare ogni 1 secondo, allora nella funzione principale `loop` si utilizza un ritardo di 1 secondo. Ogni chiamata a `loop` attiva il codice pertinente per il dispositivo che deve elaborare ogni secondo e utilizza un contatore per contare ogni ciclo, elaborando l'altro dispositivo quando il contatore raggiunge 10 (resettando il contatore successivamente).

## Passaggio alla produzione

Il prototipo costituirà la base di un sistema di produzione finale. Alcune delle differenze quando si passa alla produzione potrebbero essere:

* Componenti robusti - utilizzo di hardware progettato per resistere al rumore, al calore, alle vibrazioni e allo stress di un ambiente industriale.
* Comunicazioni interne - alcuni componenti comunicherebbero direttamente evitando il passaggio al cloud, inviando dati al cloud solo per essere archiviati. Come ciò viene fatto dipende dalla configurazione della fabbrica, con comunicazioni dirette o eseguendo parte del servizio IoT sul bordo utilizzando un dispositivo gateway.
* Opzioni di configurazione - ogni fabbrica e caso d'uso è diverso, quindi l'hardware dovrebbe essere configurabile. Ad esempio, il sensore di prossimità potrebbe dover rilevare frutti diversi a distanze diverse. Piuttosto che codificare la distanza per attivare la classificazione, si vorrebbe che questa fosse configurabile tramite il cloud, ad esempio utilizzando un device twin.
* Rimozione automatica della frutta - invece di un LED per segnalare che la frutta non è matura, dispositivi automatizzati la rimuoverebbero.

✅ Fai una ricerca: In quali altri modi i dispositivi di produzione differirebbero dai kit per sviluppatori?

---

## 🚀 Sfida

In questa lezione hai appreso alcuni dei concetti necessari per progettare un sistema IoT. Ripensa ai progetti precedenti. Come si inseriscono nell'architettura di riferimento mostrata sopra?

Scegli uno dei progetti svolti finora e pensa al design di una soluzione più complessa che integri più funzionalità rispetto a quelle trattate nei progetti. Disegna l'architettura e pensa a tutti i dispositivi e servizi di cui avresti bisogno.

Ad esempio - un dispositivo di tracciamento veicoli che combina GPS con sensori per monitorare aspetti come la temperatura in un camion refrigerato, i tempi di accensione e spegnimento del motore e l'identità del conducente. Quali sono i dispositivi coinvolti, i servizi utilizzati, i dati trasmessi e le considerazioni sulla sicurezza e sulla privacy?

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Revisione e studio autonomo

* Leggi di più sull'architettura IoT nella [documentazione sull'architettura di riferimento IoT di Azure su Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Leggi di più sui device twin nella [documentazione su come comprendere e utilizzare i device twin in IoT Hub su Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Leggi di OPC-UA, un protocollo di comunicazione macchina-macchina utilizzato nell'automazione industriale, sulla [pagina OPC-UA su Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Compito

[Costruisci un rilevatore di qualità della frutta](assignment.md)

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.