<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-25T17:33:54+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "it"
}
-->
# Un'immersione più profonda nell'IoT

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questa lezione è stata insegnata come parte della serie [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) del [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). La lezione è stata suddivisa in 2 video: una lezione di 1 ora e un'ora di sessione di approfondimento per esplorare ulteriormente alcuni aspetti della lezione e rispondere alle domande.

[![Lezione 2: Un'immersione più profonda nell'IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Lezione 2: Un'immersione più profonda nell'IoT - Sessione di approfondimento](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Clicca sulle immagini sopra per guardare i video

## Quiz preliminare

[Quiz preliminare](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Introduzione

Questa lezione approfondisce alcuni dei concetti trattati nella lezione precedente.

In questa lezione vedremo:

* [Componenti di un'applicazione IoT](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Approfondimento sui microcontrollori](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Approfondimento sui computer a scheda singola](../../../../../1-getting-started/lessons/2-deeper-dive)

## Componenti di un'applicazione IoT

I due componenti principali di un'applicazione IoT sono *Internet* e *l'oggetto*. Esaminiamo questi due componenti in modo più dettagliato.

### L'oggetto

![Un Raspberry Pi 4](../../../../../translated_images/it/raspberry-pi-4.fd4590d308c3d456.webp)

La parte **oggetto** dell'IoT si riferisce a un dispositivo che può interagire con il mondo fisico. Questi dispositivi sono solitamente piccoli computer a basso costo, che funzionano a basse velocità e consumano poca energia - ad esempio, semplici microcontrollori con pochi kilobyte di RAM (rispetto ai gigabyte di un PC) che operano a poche centinaia di megahertz (rispetto ai gigahertz di un PC), ma che consumano così poca energia da poter funzionare per settimane, mesi o addirittura anni con batterie.

Questi dispositivi interagiscono con il mondo fisico utilizzando sensori per raccogliere dati dall'ambiente circostante o controllando uscite o attuatori per apportare modifiche fisiche. Un esempio tipico è un termostato intelligente - un dispositivo che ha un sensore di temperatura, un mezzo per impostare una temperatura desiderata come una manopola o un touchscreen, e una connessione a un sistema di riscaldamento o raffreddamento che può essere attivato quando la temperatura rilevata è al di fuori dell'intervallo desiderato. Il sensore di temperatura rileva che la stanza è troppo fredda e un attuatore accende il riscaldamento.

![Un diagramma che mostra la temperatura e una manopola come input per un dispositivo IoT, e il controllo di un riscaldatore come output](../../../../../translated_images/it/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.png)

Esiste una vasta gamma di dispositivi che possono fungere da dispositivi IoT, dall'hardware dedicato che rileva un solo parametro, a dispositivi generici, persino il tuo smartphone! Uno smartphone può utilizzare sensori per rilevare il mondo circostante e attuatori per interagire con esso - ad esempio, utilizzando un sensore GPS per rilevare la tua posizione e un altoparlante per fornire istruzioni di navigazione verso una destinazione.

✅ Pensa ad altri sistemi che hai intorno a te che leggono dati da un sensore e li utilizzano per prendere decisioni. Un esempio potrebbe essere il termostato di un forno. Riesci a trovarne altri?

### Internet

La parte **Internet** di un'applicazione IoT consiste in applicazioni a cui il dispositivo IoT può connettersi per inviare e ricevere dati, oltre ad altre applicazioni che possono elaborare i dati provenienti dal dispositivo IoT e aiutare a prendere decisioni su quali richieste inviare agli attuatori del dispositivo IoT.

Una configurazione tipica potrebbe prevedere un servizio cloud a cui il dispositivo IoT si connette, e questo servizio cloud gestisce aspetti come la sicurezza, oltre a ricevere messaggi dal dispositivo IoT e inviare messaggi al dispositivo. Questo servizio cloud si collega poi ad altre applicazioni che possono elaborare o archiviare i dati dei sensori, o utilizzare i dati dei sensori insieme a quelli di altri sistemi per prendere decisioni.

I dispositivi non si connettono sempre direttamente a Internet tramite WiFi o connessioni cablate. Alcuni dispositivi utilizzano reti mesh per comunicare tra loro tramite tecnologie come il Bluetooth, connettendosi tramite un dispositivo hub che ha una connessione Internet.

Nel caso di un termostato intelligente, il termostato si connetterebbe utilizzando il WiFi domestico a un servizio cloud. Invierebbe i dati sulla temperatura a questo servizio cloud, che li scriverebbe in un database permettendo al proprietario di casa di controllare le temperature attuali e passate tramite un'app sul telefono. Un altro servizio nel cloud saprebbe quale temperatura desidera il proprietario di casa e invierebbe messaggi al dispositivo IoT tramite il servizio cloud per dire al sistema di riscaldamento di accendersi o spegnersi.

![Un diagramma che mostra la temperatura e una manopola come input per un dispositivo IoT, il dispositivo IoT con comunicazione bidirezionale con il cloud, che a sua volta ha comunicazione bidirezionale con un telefono, e il controllo di un riscaldatore come output dal dispositivo IoT](../../../../../translated_images/it/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.png)

Una versione ancora più intelligente potrebbe utilizzare l'AI nel cloud con dati provenienti da altri sensori collegati ad altri dispositivi IoT, come sensori di occupazione che rilevano quali stanze sono in uso, oltre a dati come il meteo e persino il tuo calendario, per prendere decisioni su come impostare la temperatura in modo intelligente. Ad esempio, potrebbe spegnere il riscaldamento se legge dal tuo calendario che sei in vacanza, o spegnere il riscaldamento stanza per stanza a seconda delle stanze che utilizzi, imparando dai dati per essere sempre più preciso nel tempo.

![Un diagramma che mostra più sensori di temperatura e una manopola come input per un dispositivo IoT, il dispositivo IoT con comunicazione bidirezionale con il cloud, che a sua volta ha comunicazione bidirezionale con un telefono, un calendario e un servizio meteo, e il controllo di un riscaldatore come output dal dispositivo IoT](../../../../../translated_images/it/smarter-thermostat.a75855f15d2d9e63.webp)

✅ Quali altri dati potrebbero aiutare a rendere un termostato connesso a Internet più intelligente?

### IoT al margine (Edge)

Anche se la "I" in IoT sta per Internet, questi dispositivi non devono necessariamente connettersi a Internet. In alcuni casi, i dispositivi possono connettersi a dispositivi "edge" - dispositivi gateway che funzionano sulla tua rete locale, permettendo di elaborare i dati senza effettuare una chiamata su Internet. Questo può essere più veloce quando hai molti dati o una connessione Internet lenta, ti consente di funzionare offline dove la connettività Internet non è possibile, come su una nave o in un'area colpita da una crisi umanitaria, e ti permette di mantenere i dati privati. Alcuni dispositivi contengono codice di elaborazione creato utilizzando strumenti cloud e lo eseguono localmente per raccogliere e rispondere ai dati senza utilizzare una connessione Internet per prendere decisioni.

Un esempio di questo è un dispositivo per la casa intelligente come un Apple HomePod, Amazon Alexa o Google Home, che ascolta la tua voce utilizzando modelli di AI addestrati nel cloud, ma eseguiti localmente sul dispositivo. Questi dispositivi si "attivano" quando viene pronunciata una certa parola o frase, e solo allora inviano il tuo discorso su Internet per l'elaborazione. Il dispositivo smetterà di inviare il discorso quando rileva una pausa nel tuo discorso. Tutto ciò che dici prima di attivare il dispositivo con la parola di attivazione, e tutto ciò che dici dopo che il dispositivo ha smesso di ascoltare, non verrà inviato su Internet al fornitore del dispositivo, e quindi rimarrà privato.

✅ Pensa ad altri scenari in cui la privacy è importante, quindi l'elaborazione dei dati sarebbe meglio eseguita al margine piuttosto che nel cloud. Come suggerimento, pensa ai dispositivi IoT con telecamere o altri dispositivi di imaging.

### Sicurezza IoT

Con qualsiasi connessione Internet, la sicurezza è una considerazione importante. C'è una vecchia battuta che dice che "la S in IoT sta per Sicurezza" - non c'è una "S" in IoT, implicando che non è sicuro.

I dispositivi IoT si connettono a un servizio cloud e sono quindi sicuri solo quanto lo è quel servizio cloud - se il tuo servizio cloud consente a qualsiasi dispositivo di connettersi, possono essere inviati dati dannosi o possono verificarsi attacchi di virus. Questo può avere conseguenze molto reali poiché i dispositivi IoT interagiscono e controllano altri dispositivi. Ad esempio, il [worm Stuxnet](https://wikipedia.org/wiki/Stuxnet) ha manipolato le valvole nelle centrifughe per danneggiarle. Gli hacker hanno anche sfruttato [scarsa sicurezza per accedere ai baby monitor](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) e ad altri dispositivi di sorveglianza domestica.

> 💁 A volte i dispositivi IoT e i dispositivi edge funzionano su una rete completamente isolata da Internet per mantenere i dati privati e sicuri. Questo è noto come [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Approfondimento sui microcontrollori

Nella lezione precedente, abbiamo introdotto i microcontrollori. Ora approfondiamo l'argomento.

### CPU

La CPU è il "cervello" del microcontrollore. È il processore che esegue il tuo codice e può inviare dati a e ricevere dati da qualsiasi dispositivo connesso. Le CPU possono contenere uno o più core - essenzialmente una o più CPU che possono lavorare insieme per eseguire il tuo codice.

Le CPU si basano su un clock che ticchetta milioni o miliardi di volte al secondo. Ogni ticchettio, o ciclo, sincronizza le azioni che la CPU può compiere. Con ogni ticchettio, la CPU può eseguire un'istruzione da un programma, come recuperare dati da un dispositivo esterno o eseguire un calcolo matematico. Questo ciclo regolare consente di completare tutte le azioni prima che venga elaborata l'istruzione successiva.

Più veloce è il ciclo del clock, più istruzioni possono essere elaborate ogni secondo e quindi più veloce è la CPU. La velocità della CPU è misurata in [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), un'unità standard in cui 1 Hz significa un ciclo o ticchettio del clock al secondo.

> 🎓 Le velocità delle CPU sono spesso espresse in MHz o GHz. 1MHz è 1 milione di Hz, 1GHz è 1 miliardo di Hz.

> 💁 Le CPU eseguono programmi utilizzando il [ciclo fetch-decode-execute](https://wikipedia.org/wiki/Instruction_cycle). Per ogni ticchettio del clock, la CPU recupera la prossima istruzione dalla memoria, la decodifica, quindi la esegue, ad esempio utilizzando un'unità logica aritmetica (ALU) per sommare 2 numeri. Alcune esecuzioni richiedono più ticchettii per essere completate, quindi il ciclo successivo verrà eseguito al ticchettio successivo dopo il completamento dell'istruzione.

![Il ciclo fetch-decode-execute che mostra il recupero di un'istruzione dal programma memorizzato nella RAM, quindi la decodifica e l'esecuzione su una CPU](../../../../../translated_images/it/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.png)

I microcontrollori hanno velocità di clock molto più basse rispetto ai computer desktop o laptop, o persino alla maggior parte degli smartphone. Ad esempio, il Wio Terminal ha una CPU che funziona a 120MHz o 120.000.000 cicli al secondo.

✅ Un PC o Mac medio ha una CPU con più core che funzionano a più GigaHertz, il che significa che il clock ticchetta miliardi di volte al secondo. Ricerca la velocità del clock del tuo computer e confronta quante volte è più veloce rispetto al Wio Terminal.

Ogni ciclo del clock consuma energia e genera calore. Più veloce è il ticchettio, più energia viene consumata e più calore viene generato. I PC hanno dissipatori di calore e ventole per rimuovere il calore, senza i quali si surriscalderebbero e si spegnerebbero in pochi secondi. I microcontrollori spesso non hanno né l'uno né l'altro poiché funzionano a temperature molto più basse e quindi molto più lentamente. I PC funzionano con alimentazione di rete o grandi batterie per alcune ore, mentre i microcontrollori possono funzionare per giorni, mesi o persino anni con piccole batterie. I microcontrollori possono anche avere core che funzionano a velocità diverse, passando a core più lenti e a basso consumo quando la domanda sulla CPU è bassa per ridurre il consumo energetico.

> 💁 Alcuni PC e Mac stanno adottando la stessa combinazione di core ad alte prestazioni e core a basso consumo, passando da uno all'altro per risparmiare batteria. Ad esempio, il chip M1 nei più recenti laptop Apple può passare tra 4 core ad alte prestazioni e 4 core ad alta efficienza per ottimizzare la durata della batteria o la velocità a seconda del compito da eseguire.

✅ Fai una piccola ricerca: Leggi sulle CPU nell'[articolo di Wikipedia sulle CPU](https://wikipedia.org/wiki/Central_processing_unit)

#### Compito

Indaga sul Wio Terminal.

Se stai utilizzando un Wio Terminal per queste lezioni, prova a trovare la CPU. Trova la sezione *Hardware Overview* della [pagina del prodotto Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) per un'immagine degli interni e prova a individuare la CPU attraverso la finestra di plastica trasparente sul retro.

### Memoria

I microcontrollori di solito hanno due tipi di memoria: memoria del programma e memoria ad accesso casuale (RAM).

La memoria del programma è non volatile, il che significa che tutto ciò che vi è scritto rimane anche quando il dispositivo è spento. Questa è la memoria che memorizza il codice del tuo programma.

La RAM è la memoria utilizzata dal programma per funzionare, contenente variabili allocate dal tuo programma e dati raccolti dai dispositivi periferici. La RAM è volatile, quindi quando l'alimentazione viene interrotta, il contenuto viene perso, resettando di fatto il tuo programma.
🎓 La memoria del programma conserva il tuo codice e rimane anche quando non c'è alimentazione.
🎓 La RAM viene utilizzata per eseguire il tuo programma e viene resettata quando non c'è alimentazione

Come per la CPU, la memoria di un microcontrollore è di ordini di grandezza inferiore rispetto a quella di un PC o Mac. Un PC tipico potrebbe avere 8 Gigabyte (GB) di RAM, ovvero 8.000.000.000 byte, con ogni byte che offre spazio sufficiente per memorizzare una singola lettera o un numero da 0 a 255. Un microcontrollore avrebbe solo Kilobyte (KB) di RAM, con un kilobyte pari a 1.000 byte. Il terminale Wio menzionato sopra ha 192KB di RAM, ovvero 192.000 byte - più di 40.000 volte meno rispetto a un PC medio!

Il diagramma qui sotto mostra la differenza di dimensione relativa tra 192KB e 8GB - il piccolo punto al centro rappresenta 192KB.

![Un confronto tra 192KB e 8GB - più di 40.000 volte più grande](../../../../../translated_images/it/ram-comparison.6beb73541b42ac6f.webp)

Anche lo spazio di archiviazione per i programmi è più piccolo rispetto a un PC. Un PC tipico potrebbe avere un disco rigido da 500GB per l'archiviazione dei programmi, mentre un microcontrollore potrebbe avere solo kilobyte o forse pochi megabyte (MB) di spazio di archiviazione (1MB è 1.000KB, ovvero 1.000.000 byte). Il terminale Wio ha 4MB di spazio di archiviazione per i programmi.

✅ Fai una piccola ricerca: Quanta RAM e spazio di archiviazione ha il computer che stai usando per leggere questo? Come si confronta con un microcontrollore?

### Input/Output

I microcontrollori necessitano di connessioni di input e output (I/O) per leggere dati dai sensori e inviare segnali di controllo agli attuatori. Di solito contengono un certo numero di pin di input/output generici (GPIO). Questi pin possono essere configurati tramite software come input (cioè ricevono un segnale) o output (inviando un segnale).

🧠⬅️ I pin di input vengono utilizzati per leggere valori dai sensori

🧠➡️ I pin di output inviano istruzioni agli attuatori

✅ Imparerai di più su questo in una lezione successiva.

#### Compito

Esamina il terminale Wio.

Se stai utilizzando un terminale Wio per queste lezioni, trova i pin GPIO. Trova la sezione *Pinout diagram* nella [pagina del prodotto Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) per scoprire quali pin sono quali. Il terminale Wio viene fornito con un adesivo che puoi montare sul retro con i numeri dei pin, quindi aggiungilo ora se non lo hai già fatto.

### Dimensioni fisiche

I microcontrollori sono generalmente piccoli, con i più piccoli, come il [Freescale Kinetis KL03 MCU, abbastanza piccoli da entrare nella fossetta di una pallina da golf](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Solo la CPU di un PC può misurare 40mm x 40mm, e questo senza includere i dissipatori di calore e le ventole necessarie per garantire che la CPU possa funzionare per più di pochi secondi senza surriscaldarsi, sostanzialmente più grande di un microcontrollore completo. Il kit di sviluppo del terminale Wio con un microcontrollore, custodia, schermo e una gamma di connessioni e componenti non è molto più grande di una CPU Intel i9 nuda, e sostanzialmente più piccolo della CPU con dissipatore di calore e ventola!

| Dispositivo                      | Dimensioni            |
| -------------------------------- | --------------------- |
| Freescale Kinetis KL03           | 1.6mm x 2mm x 1mm     |
| Terminale Wio                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, dissipatore e ventola | 136mm x 145mm x 103mm |

### Framework e sistemi operativi

A causa della loro bassa velocità e dimensione della memoria, i microcontrollori non eseguono un sistema operativo (OS) nel senso desktop del termine. Il sistema operativo che fa funzionare il tuo computer (Windows, Linux o macOS) necessita di molta memoria e potenza di elaborazione per eseguire attività completamente inutili per un microcontrollore. Ricorda che i microcontrollori sono solitamente programmati per svolgere uno o più compiti molto specifici, a differenza di un computer generico come un PC o Mac che deve supportare un'interfaccia utente, riprodurre musica o film, fornire strumenti per scrivere documenti o codice, giocare o navigare su Internet.

Per programmare un microcontrollore senza un OS, è necessario qualche strumento che consenta di costruire il codice in modo che il microcontrollore possa eseguirlo, utilizzando API che possono comunicare con eventuali periferiche. Ogni microcontrollore è diverso, quindi i produttori normalmente supportano framework standard che ti permettono di seguire una 'ricetta' standard per costruire il tuo codice e farlo funzionare su qualsiasi microcontrollore che supporti quel framework.

Puoi programmare i microcontrollori utilizzando un OS - spesso chiamato sistema operativo in tempo reale (RTOS), poiché questi sono progettati per gestire l'invio di dati da e verso le periferiche in tempo reale. Questi sistemi operativi sono molto leggeri e offrono funzionalità come:

* Multi-threading, che consente al tuo codice di eseguire più blocchi di codice contemporaneamente, sia su più core che alternandosi su un core
* Networking per comunicare su Internet in modo sicuro
* Componenti dell'interfaccia grafica (GUI) per costruire interfacce utente (UI) su dispositivi con schermi.

✅ Leggi alcuni diversi RTOS: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Il logo Arduino](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) è probabilmente il framework per microcontrollori più popolare, soprattutto tra studenti, hobbisti e maker. Arduino è una piattaforma elettronica open source che combina software e hardware. Puoi acquistare schede compatibili Arduino direttamente da Arduino o da altri produttori, quindi codificare utilizzando il framework Arduino.

Le schede Arduino sono codificate in C o C++. Utilizzare C/C++ consente al tuo codice di essere compilato in modo molto compatto e di funzionare velocemente, qualcosa di necessario su un dispositivo con risorse limitate come un microcontrollore. Il nucleo di un'applicazione Arduino è chiamato sketch ed è codice C/C++ con 2 funzioni - `setup` e `loop`. Quando la scheda si avvia, il codice del framework Arduino eseguirà la funzione `setup` una volta, quindi eseguirà la funzione `loop` ripetutamente, eseguendola continuamente fino a quando l'alimentazione non viene spenta.

Scriveresti il tuo codice di configurazione nella funzione `setup`, come la connessione al WiFi e ai servizi cloud o l'inizializzazione dei pin per input e output. Il tuo codice di elaborazione verrebbe poi inserito nella funzione `loop`, come la lettura da un sensore e l'invio del valore al cloud. Normalmente includeresti un ritardo in ogni ciclo, ad esempio, se desideri che i dati del sensore vengano inviati solo ogni 10 secondi, aggiungeresti un ritardo di 10 secondi alla fine del ciclo in modo che il microcontrollore possa dormire, risparmiando energia, quindi eseguire nuovamente il ciclo quando necessario 10 secondi dopo.

![Uno sketch Arduino che esegue prima setup, poi loop ripetutamente](../../../../../translated_images/it/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.png)

✅ Questa architettura del programma è conosciuta come *event loop* o *message loop*. Molte applicazioni utilizzano questo approccio dietro le quinte ed è lo standard per la maggior parte delle applicazioni desktop che funzionano su OS come Windows, macOS o Linux. Il `loop` ascolta i messaggi dai componenti dell'interfaccia utente come pulsanti, o dispositivi come la tastiera, e risponde a essi. Puoi leggere di più in questo [articolo sul ciclo degli eventi](https://wikipedia.org/wiki/Event_loop).

Arduino fornisce librerie standard per interagire con i microcontrollori e i pin I/O, con diverse implementazioni sotto il cofano per funzionare su diversi microcontrollori. Ad esempio, la funzione [`delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) metterà in pausa il programma per un determinato periodo di tempo, la funzione [`digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) leggerà un valore di `HIGH` o `LOW` dal pin specificato, indipendentemente dalla scheda su cui viene eseguito il codice. Queste librerie standard significano che il codice Arduino scritto per una scheda può essere ricompilato per qualsiasi altra scheda Arduino e funzionerà, supponendo che i pin siano gli stessi e le schede supportino le stesse funzionalità.

Esiste un vasto ecosistema di librerie Arduino di terze parti che ti consentono di aggiungere funzionalità extra ai tuoi progetti Arduino, come l'utilizzo di sensori e attuatori o la connessione ai servizi IoT cloud.

##### Compito

Esamina il terminale Wio.

Se stai utilizzando un terminale Wio per queste lezioni, rileggi il codice che hai scritto nella lezione precedente. Trova le funzioni `setup` e `loop`. Monitora l'output seriale per verificare che la funzione `loop` venga chiamata ripetutamente. Prova ad aggiungere codice alla funzione `setup` per scrivere sulla porta seriale e osserva che questo codice viene chiamato solo una volta ogni volta che riavvii. Prova a riavviare il dispositivo con l'interruttore di alimentazione sul lato per mostrare che viene chiamato ogni volta che il dispositivo si riavvia.

## Approfondimento sui computer a scheda singola

Nella lezione precedente, abbiamo introdotto i computer a scheda singola. Ora approfondiamoli.

### Raspberry Pi

![Il logo Raspberry Pi](../../../../../translated_images/it/raspberry-pi-logo.4efaa16605cee054.webp)

La [Raspberry Pi Foundation](https://www.raspberrypi.org) è un'organizzazione benefica del Regno Unito fondata nel 2009 per promuovere lo studio dell'informatica, soprattutto a livello scolastico. Come parte di questa missione, hanno sviluppato un computer a scheda singola, chiamato Raspberry Pi. I Raspberry Pi sono attualmente disponibili in 3 varianti - una versione a grandezza naturale, il più piccolo Pi Zero, e un modulo di calcolo che può essere integrato nel tuo dispositivo IoT finale.

![Un Raspberry Pi 4](../../../../../translated_images/it/raspberry-pi-4.fd4590d308c3d456.webp)

L'ultima iterazione del Raspberry Pi a grandezza naturale è il Raspberry Pi 4B. Questo ha una CPU quad-core (4 core) che funziona a 1.5GHz, 2, 4 o 8GB di RAM, gigabit ethernet, WiFi, 2 porte HDMI che supportano schermi 4k, una porta audio e video composito, porte USB (2 USB 2.0, 2 USB 3.0), 40 pin GPIO, un connettore per fotocamera per un modulo fotocamera Raspberry Pi e uno slot per schede SD. Tutto questo su una scheda che misura 88mm x 58mm x 19.5mm ed è alimentata da un alimentatore USB-C da 3A. Questi partono da 35 dollari USA, molto più economici di un PC o Mac.

> 💁 C'è anche un Pi400, un computer all-in-one con un Pi4 integrato in una tastiera.

![Un Raspberry Pi Zero](../../../../../translated_images/it/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

Il Pi Zero è molto più piccolo e con un consumo energetico inferiore. Ha una CPU single-core da 1GHz, 512MB di RAM, WiFi (nel modello Zero W), una singola porta HDMI, una porta micro-USB, 40 pin GPIO, un connettore per fotocamera per un modulo fotocamera Raspberry Pi e uno slot per schede SD. Misura 65mm x 30mm x 5mm e consuma pochissima energia. Il Zero costa 5 dollari USA, mentre la versione W con WiFi costa 10 dollari USA.

> 🎓 Le CPU in entrambi questi modelli sono processori ARM, a differenza dei processori Intel/AMD x86 o x64 che trovi nella maggior parte dei PC e Mac. Questi sono simili alle CPU che trovi in alcuni microcontrollori, così come nella quasi totalità dei telefoni cellulari, nel Microsoft Surface X e nei nuovi Mac basati su Apple Silicon.

Tutte le varianti del Raspberry Pi eseguono una versione di Debian Linux chiamata Raspberry Pi OS. Questa è disponibile in una versione lite senza desktop, perfetta per progetti 'headless' dove non è necessario uno schermo, o una versione completa con un ambiente desktop completo, con browser web, applicazioni per ufficio, strumenti di programmazione e giochi. Poiché il sistema operativo è una versione di Debian Linux, puoi installare qualsiasi applicazione o strumento che funziona su Debian e che è costruito per il processore ARM all'interno del Pi.

#### Compito

Esamina il Raspberry Pi.

Se stai utilizzando un Raspberry Pi per queste lezioni, leggi i diversi componenti hardware sulla scheda.

* Puoi trovare dettagli sui processori utilizzati nella [pagina di documentazione hardware del Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Leggi il processore utilizzato nel Pi che stai utilizzando.
* Localizza i pin GPIO. Leggi di più su di essi nella [documentazione GPIO del Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Usa la [guida all'uso dei pin GPIO](https://www.raspberrypi.org/documentation/usage/gpio/README.md) per identificare i diversi pin sul tuo Pi.

### Programmazione dei computer a scheda singola

I computer a scheda singola sono veri e propri computer, che eseguono un sistema operativo completo. Questo significa che c'è una vasta gamma di linguaggi di programmazione, framework e strumenti che puoi utilizzare per codificarli, a differenza dei microcontrollori che si affidano al supporto della scheda in framework come Arduino. La maggior parte dei linguaggi di programmazione ha librerie che possono accedere ai pin GPIO per inviare e ricevere dati da sensori e attuatori.

✅ Quali linguaggi di programmazione conosci? Sono supportati su Linux?

Il linguaggio di programmazione più comune per costruire applicazioni IoT su un Raspberry Pi è Python. Esiste un enorme ecosistema di hardware progettato per il Pi, e quasi tutti includono il codice necessario per utilizzarli come librerie Python. Alcuni di questi ecosistemi si basano su 'hats' - così chiamati perché si posizionano sopra il Pi come un cappello e si collegano con un grande connettore ai 40 pin GPIO. Questi hats forniscono capacità aggiuntive, come schermi, sensori, automobili telecomandate o adattatori per collegare sensori con cavi standardizzati.
### Utilizzo di computer a scheda singola nelle implementazioni IoT professionali

I computer a scheda singola vengono utilizzati per implementazioni IoT professionali, non solo come kit per sviluppatori. Possono offrire un modo potente per controllare l'hardware e gestire attività complesse, come l'esecuzione di modelli di machine learning. Ad esempio, esiste un [Raspberry Pi 4 compute module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) che offre tutta la potenza di un Raspberry Pi 4 ma in una forma compatta e più economica, senza la maggior parte delle porte, progettato per essere installato in hardware personalizzato.

---

## 🚀 Sfida

La sfida della lezione precedente era elencare quanti più dispositivi IoT possibile presenti nella tua casa, scuola o luogo di lavoro. Per ogni dispositivo in questa lista, pensi che siano basati su microcontrollori, computer a scheda singola o persino una combinazione di entrambi?

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Revisione e studio autonomo

* Leggi la [guida introduttiva di Arduino](https://www.arduino.cc/en/Guide/Introduction) per comprendere meglio la piattaforma Arduino.
* Leggi l'[introduzione al Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) per saperne di più sui Raspberry Pi.
* Approfondisci alcuni concetti e acronimi nell'[articolo "What the FAQ are CPUs, MPUs, MCUs, and GPUs" del Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Utilizza queste guide, insieme ai costi mostrati seguendo i link nella [guida hardware](../../../hardware.md), per decidere quale piattaforma hardware vuoi utilizzare o se preferisci utilizzare un dispositivo virtuale.

## Compito

[Confronta e metti a confronto microcontrollori e computer a scheda singola](assignment.md)

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.