<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-25T17:26:21+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "it"
}
-->
# Introduzione all'IoT

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.jpg)

> Disegno di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questa lezione è stata insegnata come parte della serie [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) del [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). La lezione è stata suddivisa in 2 video: una lezione di 1 ora e un'ora di sessione di domande e approfondimenti su alcune parti della lezione.

[![Lezione 1: Introduzione all'IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lezione 1: Introduzione all'IoT - Sessione di domande](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Clicca sulle immagini sopra per guardare i video

## Quiz preliminare alla lezione

[Quiz preliminare alla lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Introduzione

Questa lezione copre alcuni argomenti introduttivi sull'Internet delle Cose e ti guida nella configurazione del tuo hardware.

In questa lezione tratteremo:

* [Cos'è l'Internet delle Cose?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Dispositivi IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Configura il tuo dispositivo](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Applicazioni dell'IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Esempi di dispositivi IoT che potresti avere intorno a te](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Cos'è l'Internet delle Cose?

Il termine "Internet delle Cose" è stato coniato da [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) nel 1999 per descrivere la connessione tra Internet e il mondo fisico tramite sensori. Da allora, il termine è stato utilizzato per descrivere qualsiasi dispositivo che interagisce con il mondo fisico circostante, raccogliendo dati dai sensori o fornendo interazioni reali tramite attuatori (dispositivi che svolgono azioni come accendere un interruttore o illuminare un LED), generalmente connessi ad altri dispositivi o a Internet.

> **Sensori** raccolgono informazioni dal mondo, come la velocità, la temperatura o la posizione.
>
> **Attuatori** convertono segnali elettrici in interazioni reali, come attivare un interruttore, accendere luci, emettere suoni o inviare segnali di controllo ad altri hardware, ad esempio per accendere una presa di corrente.

L'IoT come area tecnologica non si limita ai dispositivi: include servizi basati su cloud che possono elaborare i dati dei sensori o inviare richieste agli attuatori collegati ai dispositivi IoT. Include anche dispositivi che non hanno o non necessitano di connettività Internet, spesso chiamati dispositivi edge. Questi dispositivi possono elaborare e rispondere ai dati dei sensori autonomamente, solitamente utilizzando modelli di intelligenza artificiale addestrati nel cloud.

L'IoT è un campo tecnologico in rapida crescita. Si stima che entro la fine del 2020 siano stati distribuiti e connessi a Internet 30 miliardi di dispositivi IoT. Guardando al futuro, si prevede che entro il 2025 i dispositivi IoT raccoglieranno quasi 80 zettabyte di dati, ovvero 80 trilioni di gigabyte. È una quantità enorme di dati!

![Un grafico che mostra il numero di dispositivi IoT attivi nel tempo, con una tendenza al rialzo da meno di 5 miliardi nel 2015 a oltre 30 miliardi nel 2025](../../../../../images/connected-iot-devices.svg)

✅ Fai una piccola ricerca: Quanta parte dei dati generati dai dispositivi IoT viene effettivamente utilizzata e quanta viene ignorata? Perché così tanti dati vengono trascurati?

Questi dati sono la chiave del successo dell'IoT. Per essere un sviluppatore IoT di successo, devi comprendere quali dati raccogliere, come raccoglierli, come prendere decisioni basate su di essi e come utilizzare queste decisioni per interagire con il mondo fisico, se necessario.

## Dispositivi IoT

La **T** in IoT sta per **Things** (Cose) - dispositivi che interagiscono con il mondo fisico circostante raccogliendo dati dai sensori o fornendo interazioni reali tramite attuatori.

I dispositivi per uso produttivo o commerciale, come i tracker di fitness per i consumatori o i controller di macchine industriali, sono solitamente realizzati su misura. Utilizzano circuiti stampati personalizzati, magari anche processori personalizzati, progettati per soddisfare le esigenze di un compito specifico, che si tratti di essere abbastanza piccoli da adattarsi a un polso o abbastanza robusti da funzionare in ambienti ad alta temperatura, stress o vibrazione.

Come sviluppatore che sta imparando sull'IoT o creando un prototipo di dispositivo, dovrai iniziare con un kit per sviluppatori. Questi sono dispositivi IoT generici progettati per gli sviluppatori, spesso con funzionalità che non troveresti su un dispositivo di produzione, come una serie di pin esterni per collegare sensori o attuatori, hardware per il debug o risorse aggiuntive che aumenterebbero inutilmente i costi in una produzione su larga scala.

Questi kit per sviluppatori di solito rientrano in due categorie: microcontrollori e computer a scheda singola. Questi saranno introdotti qui e approfonditi nella prossima lezione.

> 💁 Anche il tuo telefono può essere considerato un dispositivo IoT generico, con sensori e attuatori integrati, utilizzati in modi diversi da diverse app con diversi servizi cloud. Puoi persino trovare alcuni tutorial IoT che utilizzano un'app per telefono come dispositivo IoT.

### Microcontrollori

Un microcontrollore (spesso chiamato MCU, abbreviazione di microcontroller unit) è un piccolo computer composto da:

🧠 Una o più unità di elaborazione centrale (CPU) - il "cervello" del microcontrollore che esegue il tuo programma

💾 Memoria (RAM e memoria del programma) - dove vengono archiviati il tuo programma, i dati e le variabili

🔌 Connessioni di input/output (I/O) programmabili - per comunicare con periferiche esterne (dispositivi collegati) come sensori e attuatori

I microcontrollori sono dispositivi di calcolo a basso costo, con prezzi medi per quelli utilizzati in hardware personalizzato che scendono a circa 0,50 USD, e alcuni dispositivi che costano solo 0,03 USD. I kit per sviluppatori possono partire da 4 USD, con costi che aumentano aggiungendo più funzionalità. Il [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), un kit per sviluppatori di microcontrollori di [Seeed studios](https://www.seeedstudio.com) che include sensori, attuatori, WiFi e uno schermo, costa circa 30 USD.

![Un Wio Terminal](../../../../../translated_images/it/wio-terminal.b8299ee16587db9a.webp)

> 💁 Quando cerchi microcontrollori su Internet, fai attenzione a cercare il termine **MCU**, poiché potrebbe restituire molti risultati relativi al Marvel Cinematic Universe, non ai microcontrollori.

I microcontrollori sono progettati per essere programmati per svolgere un numero limitato di compiti molto specifici, piuttosto che essere computer generici come PC o Mac. Salvo scenari molto specifici, non puoi collegare un monitor, una tastiera e un mouse e usarli per compiti generici.

I kit per sviluppatori di microcontrollori di solito includono sensori e attuatori aggiuntivi integrati. La maggior parte delle schede avrà uno o più LED programmabili, insieme ad altri dispositivi come connettori standard per aggiungere più sensori o attuatori utilizzando ecosistemi di vari produttori o sensori integrati (solitamente i più popolari, come i sensori di temperatura). Alcuni microcontrollori hanno connettività wireless integrata come Bluetooth o WiFi o hanno microcontrollori aggiuntivi sulla scheda per aggiungere questa connettività.

> 💁 I microcontrollori sono solitamente programmati in C/C++.

### Computer a scheda singola

Un computer a scheda singola è un piccolo dispositivo di calcolo che contiene tutti gli elementi di un computer completo su una singola scheda. Questi dispositivi hanno specifiche simili a un PC desktop o laptop, eseguono un sistema operativo completo, ma sono piccoli, consumano meno energia e sono significativamente più economici.

![Un Raspberry Pi 4](../../../../../translated_images/it/raspberry-pi-4.fd4590d308c3d456.webp)

Il Raspberry Pi è uno dei computer a scheda singola più popolari.

Come un microcontrollore, i computer a scheda singola hanno una CPU, memoria e pin di input/output, ma hanno funzionalità aggiuntive come un chip grafico per collegare monitor, uscite audio e porte USB per collegare tastiere, mouse e altri dispositivi USB standard come webcam o archiviazione esterna. I programmi sono archiviati su schede SD o dischi rigidi insieme a un sistema operativo, invece di un chip di memoria integrato nella scheda.

> 🎓 Puoi pensare a un computer a scheda singola come a una versione più piccola ed economica del PC o Mac che stai utilizzando, con l'aggiunta di pin GPIO (general-purpose input/output) per interagire con sensori e attuatori.

I computer a scheda singola sono computer completi, quindi possono essere programmati in qualsiasi linguaggio. I dispositivi IoT sono tipicamente programmati in Python.

### Scelte hardware per le lezioni successive

Tutte le lezioni successive includono esercizi che utilizzano un dispositivo IoT per interagire con il mondo fisico e comunicare con il cloud. Ogni lezione supporta 3 opzioni di dispositivo: Arduino (utilizzando un Seeed Studios Wio Terminal) o un computer a scheda singola, sia un dispositivo fisico (un Raspberry Pi 4) sia un computer a scheda singola virtuale che gira sul tuo PC o Mac.

Puoi leggere l'hardware necessario per completare tutti gli esercizi nella [guida hardware](../../../hardware.md).

> 💁 Non è necessario acquistare hardware IoT per completare gli esercizi, puoi fare tutto utilizzando un computer a scheda singola virtuale.

La scelta dell'hardware dipende da ciò che hai disponibile a casa o a scuola e dal linguaggio di programmazione che conosci o che intendi imparare. Entrambe le varianti hardware utilizzeranno lo stesso ecosistema di sensori, quindi se inizi con una, puoi passare all'altra senza dover sostituire la maggior parte del kit. Il computer a scheda singola virtuale sarà equivalente all'apprendimento su un Raspberry Pi, con la maggior parte del codice trasferibile al Pi se in futuro acquisti un dispositivo e sensori.

### Kit per sviluppatori Arduino

Se sei interessato a imparare lo sviluppo di microcontrollori, puoi completare gli esercizi utilizzando un dispositivo Arduino. Avrai bisogno di una conoscenza di base della programmazione in C/C++, poiché le lezioni insegneranno solo il codice rilevante per il framework Arduino, i sensori e gli attuatori utilizzati e le librerie che interagiscono con il cloud.

Gli esercizi utilizzeranno [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) con l'estensione [PlatformIO per lo sviluppo di microcontrollori](https://platformio.org). Puoi anche utilizzare l'IDE Arduino se hai esperienza con questo strumento, poiché non verranno fornite istruzioni.

### Kit per sviluppatori di computer a scheda singola

Se sei interessato a imparare lo sviluppo IoT utilizzando computer a scheda singola, puoi completare gli esercizi utilizzando un Raspberry Pi o un dispositivo virtuale che gira sul tuo PC o Mac.

Avrai bisogno di una conoscenza di base della programmazione in Python, poiché le lezioni insegneranno solo il codice rilevante per i sensori e gli attuatori utilizzati e le librerie che interagiscono con il cloud.

> 💁 Se vuoi imparare a programmare in Python, dai un'occhiata alle seguenti serie di video:
>
> * [Python per principianti](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Più Python per principianti](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Gli esercizi utilizzeranno [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Se utilizzi un Raspberry Pi, puoi eseguire il tuo Pi utilizzando la versione desktop completa di Raspberry Pi OS e fare tutto il coding direttamente sul Pi utilizzando [la versione Raspberry Pi OS di VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), oppure eseguire il tuo Pi come dispositivo senza testa e programmare dal tuo PC o Mac utilizzando VS Code con l'estensione [Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) che ti consente di connetterti al tuo Pi e modificare, eseguire il debug e eseguire il codice come se stessi programmando direttamente su di esso.

Se utilizzi l'opzione del dispositivo virtuale, programmerai direttamente sul tuo computer. Invece di accedere a sensori e attuatori, utilizzerai uno strumento per simulare questo hardware fornendo valori di sensori che puoi definire e mostrando i risultati degli attuatori sullo schermo.

## Configura il tuo dispositivo

Prima di iniziare a programmare il tuo dispositivo IoT, dovrai fare una piccola configurazione. Segui le istruzioni pertinenti in base al dispositivo che utilizzerai.
💁 Se non hai ancora un dispositivo, consulta la [guida hardware](../../../hardware.md) per decidere quale dispositivo utilizzare e quale hardware aggiuntivo acquistare. Non è necessario acquistare hardware, poiché tutti i progetti possono essere eseguiti su hardware virtuale.
Queste istruzioni includono link a siti web di terze parti creati dai produttori dell'hardware o degli strumenti che utilizzerai. Questo serve a garantire che tu stia sempre utilizzando le istruzioni più aggiornate per i vari strumenti e hardware.

Segui la guida pertinente per configurare il tuo dispositivo e completare un progetto "Hello World". Questo sarà il primo passo per creare una luce notturna IoT durante le 4 lezioni di questa parte introduttiva.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Computer a scheda singola - Raspberry Pi](pi.md)
* [Computer a scheda singola - Dispositivo virtuale](virtual-device.md)

✅ Utilizzerai VS Code sia per Arduino che per i computer a scheda singola. Se non lo hai mai usato prima, leggi di più sul sito di [VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Applicazioni dell'IoT

L'IoT copre un'ampia gamma di casi d'uso, suddivisi in alcuni grandi gruppi:

* IoT per i consumatori
* IoT commerciale
* IoT industriale
* IoT per le infrastrutture

✅ Fai una piccola ricerca: Per ciascuna delle aree descritte di seguito, trova un esempio concreto che non sia già menzionato nel testo.

### IoT per i consumatori

L'IoT per i consumatori si riferisce ai dispositivi IoT che i consumatori acquistano e utilizzano nelle loro case. Alcuni di questi dispositivi sono incredibilmente utili, come gli altoparlanti intelligenti, i sistemi di riscaldamento smart e i robot aspirapolvere. Altri sono discutibili nella loro utilità, come i rubinetti controllati dalla voce che poi non possono essere spenti perché il controllo vocale non riesce a sentirti sopra il rumore dell'acqua che scorre.

I dispositivi IoT per i consumatori stanno dando alle persone la possibilità di fare di più nel loro ambiente, specialmente al miliardo di persone che hanno una disabilità. I robot aspirapolvere possono fornire pavimenti puliti a persone con problemi di mobilità che non possono pulire da sole, i forni controllati dalla voce permettono a persone con problemi di vista o di controllo motorio di riscaldare il forno usando solo la voce, i monitor di salute permettono ai pazienti di controllare condizioni croniche con aggiornamenti più regolari e dettagliati. Questi dispositivi stanno diventando così comuni che persino i bambini li usano nella loro vita quotidiana, ad esempio, studenti che seguono lezioni virtuali durante la pandemia di COVID impostano timer sui dispositivi smart per monitorare il loro lavoro scolastico o sveglie per ricordare loro le lezioni imminenti.

✅ Quali dispositivi IoT per i consumatori hai con te o nella tua casa?

### IoT commerciale

L'IoT commerciale riguarda l'uso dell'IoT sul posto di lavoro. In un ufficio, potrebbero esserci sensori di occupazione e rilevatori di movimento per gestire l'illuminazione e il riscaldamento, mantenendo luci e calore spenti quando non necessari, riducendo i costi e le emissioni di carbonio. In una fabbrica, i dispositivi IoT possono monitorare i rischi per la sicurezza, come lavoratori che non indossano caschi protettivi o rumori che hanno raggiunto livelli pericolosi. Nel settore retail, i dispositivi IoT possono misurare la temperatura dei frigoriferi, avvisando il proprietario del negozio se un frigorifero o un congelatore è fuori dal range di temperatura richiesto, oppure possono monitorare gli articoli sugli scaffali per indirizzare i dipendenti a rifornire i prodotti venduti. L'industria dei trasporti si affida sempre di più all'IoT per monitorare la posizione dei veicoli, tracciare il chilometraggio su strada per la tariffazione degli utenti, verificare il rispetto delle ore di guida e delle pause, o notificare al personale quando un veicolo si avvicina a un deposito per prepararsi al carico o scarico.

✅ Quali dispositivi IoT commerciali hai nella tua scuola o sul posto di lavoro?

### IoT industriale (IIoT)

L'IoT industriale, o IIoT, è l'uso di dispositivi IoT per controllare e gestire macchinari su larga scala. Questo copre una vasta gamma di casi d'uso, dalle fabbriche all'agricoltura digitale.

Le fabbriche utilizzano dispositivi IoT in molti modi diversi. I macchinari possono essere monitorati con sensori multipli per tracciare cose come temperatura, vibrazione e velocità di rotazione. Questi dati possono essere monitorati per permettere di fermare la macchina se supera certe tolleranze - ad esempio, se si surriscalda viene arrestata. Questi dati possono anche essere raccolti e analizzati nel tempo per fare manutenzione predittiva, dove modelli di intelligenza artificiale analizzano i dati che precedono un guasto e li usano per prevedere altri guasti prima che si verifichino.

L'agricoltura digitale è importante per nutrire la popolazione in crescita, specialmente per i 2 miliardi di persone in 500 milioni di famiglie che vivono di [agricoltura di sussistenza](https://wikipedia.org/wiki/Subsistence_agriculture). L'agricoltura digitale può variare da sensori economici a grandi installazioni commerciali. Un agricoltore può iniziare monitorando le temperature e utilizzando i [giorni di grado di crescita](https://wikipedia.org/wiki/Growing_degree-day) per prevedere quando un raccolto sarà pronto per la raccolta. Può collegare il monitoraggio dell'umidità del suolo a sistemi di irrigazione automatizzati per dare alle piante la quantità d'acqua necessaria, senza sprechi. Gli agricoltori stanno andando oltre, utilizzando droni, dati satellitari e intelligenza artificiale per monitorare la crescita delle colture, le malattie e la qualità del suolo su vaste aree di terreno agricolo.

✅ Quali altri dispositivi IoT potrebbero aiutare gli agricoltori?

### IoT per le infrastrutture

L'IoT per le infrastrutture riguarda il monitoraggio e il controllo delle infrastrutture locali e globali che le persone utilizzano ogni giorno.

Le [Smart Cities](https://wikipedia.org/wiki/Smart_city) sono aree urbane che utilizzano dispositivi IoT per raccogliere dati sulla città e usarli per migliorare il funzionamento della città stessa. Queste città sono solitamente gestite con collaborazioni tra governi locali, università e imprese locali, monitorando e gestendo aspetti che variano dal trasporto al parcheggio e all'inquinamento. Ad esempio, a Copenaghen, Danimarca, l'inquinamento atmosferico è importante per i residenti locali, quindi viene misurato e i dati vengono utilizzati per fornire informazioni sui percorsi più puliti per andare in bicicletta o fare jogging.

Le [reti elettriche intelligenti](https://wikipedia.org/wiki/Smart_grid) permettono migliori analisi della domanda di energia raccogliendo dati di utilizzo a livello di singole abitazioni. Questi dati possono guidare decisioni a livello nazionale, come dove costruire nuove centrali elettriche, e a livello personale, fornendo agli utenti informazioni su quanta energia stanno usando, quando la stanno usando e persino suggerimenti su come ridurre i costi, ad esempio caricando le auto elettriche di notte.

✅ Se potessi aggiungere dispositivi IoT per misurare qualcosa dove vivi, cosa sarebbe?

## Esempi di dispositivi IoT che potresti avere intorno a te

Saresti sorpreso di quanti dispositivi IoT hai intorno a te. Sto scrivendo questo da casa e ho i seguenti dispositivi connessi a Internet con funzionalità smart come controllo tramite app, controllo vocale o la capacità di inviarmi dati tramite il telefono:

* Molti altoparlanti intelligenti
* Frigorifero, lavastoviglie, forno e microonde
* Monitor elettrico per pannelli solari
* Prese intelligenti
* Videocitofono e telecamere di sicurezza
* Termostato intelligente con sensori smart per le stanze
* Apriporta del garage
* Sistemi di intrattenimento domestico e TV controllate dalla voce
* Luci
* Tracker per fitness e salute

Tutti questi tipi di dispositivi hanno sensori e/o attuatori e comunicano con Internet. Posso sapere dal mio telefono se la porta del garage è aperta e chiedere al mio altoparlante intelligente di chiuderla per me. Posso persino impostare un timer, così se è ancora aperta di notte, si chiuderà automaticamente. Quando suona il campanello, posso vedere dal mio telefono chi è lì, ovunque mi trovi nel mondo, e parlare con loro tramite un altoparlante e un microfono integrati nel videocitofono. Posso monitorare la mia glicemia, il battito cardiaco e i modelli di sonno, cercando schemi nei dati per migliorare la mia salute. Posso controllare le luci tramite il cloud e rimanere al buio quando la connessione Internet si interrompe.

---

## 🚀 Sfida

Elenca quanti più dispositivi IoT puoi che si trovano nella tua casa, scuola o luogo di lavoro - potrebbero essere più di quanto pensi!

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Revisione e studio autonomo

Leggi i vantaggi e i fallimenti dei progetti IoT per i consumatori. Controlla i siti di notizie per articoli su quando qualcosa è andato storto, come problemi di privacy, problemi hardware o problemi causati dalla mancanza di connettività.

Alcuni esempi:

* Dai un'occhiata all'account Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(avviso di linguaggio volgare)* per alcuni buoni esempi di fallimenti con l'IoT per i consumatori.
* [c|net - Il mio Apple Watch mi ha salvato la vita: 5 persone condividono le loro storie](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Tecnico ADT si dichiara colpevole di aver spiato i feed delle telecamere dei clienti per anni](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(avviso di contenuto sensibile - voyeurismo non consensuale)*

## Compito

[Indaga su un progetto IoT](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.