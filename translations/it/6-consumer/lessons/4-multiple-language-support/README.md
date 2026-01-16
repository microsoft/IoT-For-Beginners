<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-25T17:37:51+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "it"
}
-->
# Supporto per più lingue

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questo video offre una panoramica dei servizi di riconoscimento vocale di Azure, trattando il riconoscimento vocale e la sintesi vocale delle lezioni precedenti, oltre alla traduzione del parlato, argomento trattato in questa lezione:

[![Riconoscere il parlato con poche righe di Python da Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Clicca sull'immagine sopra per guardare il video

## Quiz pre-lezione

[Quiz pre-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Introduzione

Nelle ultime 3 lezioni hai imparato a convertire il parlato in testo, a comprendere il linguaggio e a convertire il testo in parlato, tutto grazie all'AI. Un'altra area della comunicazione umana in cui l'AI può essere d'aiuto è la traduzione linguistica - convertire da una lingua a un'altra, ad esempio dall'inglese al francese.

In questa lezione imparerai a utilizzare l'AI per tradurre il testo, permettendo al tuo timer intelligente di interagire con gli utenti in più lingue.

In questa lezione tratteremo:

* [Tradurre il testo](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Servizi di traduzione](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Creare una risorsa di traduzione](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Supportare più lingue nelle applicazioni con traduzioni](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Tradurre il testo utilizzando un servizio AI](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Questa è l'ultima lezione di questo progetto, quindi dopo aver completato questa lezione e l'assegnazione, non dimenticare di pulire i tuoi servizi cloud. Avrai bisogno dei servizi per completare l'assegnazione, quindi assicurati di completarla prima.
>
> Consulta [la guida per pulire il tuo progetto](../../../clean-up.md) se necessario per istruzioni su come farlo.

## Tradurre il testo

La traduzione del testo è stata un problema della scienza informatica studiato per oltre 70 anni, e solo ora, grazie ai progressi dell'AI e della potenza di calcolo, si avvicina a essere risolto a un livello quasi pari a quello dei traduttori umani.

> 💁 Le origini possono essere fatte risalire ancora più indietro, a [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), un crittografo arabo del IX secolo che sviluppò tecniche per la traduzione linguistica.

### Traduzioni automatiche

La traduzione del testo è iniziata come una tecnologia nota come Traduzione Automatica (MT), che può tradurre tra diverse coppie di lingue. La MT funziona sostituendo le parole in una lingua con altre, aggiungendo tecniche per selezionare i modi corretti di tradurre frasi o parti di frasi quando una semplice traduzione parola per parola non ha senso.

> 🎓 Quando i traduttori supportano la traduzione tra una lingua e un'altra, queste sono note come *coppie di lingue*. Strumenti diversi supportano coppie di lingue diverse, e queste potrebbero non essere complete. Ad esempio, un traduttore potrebbe supportare inglese-spagnolo come coppia di lingue, e spagnolo-italiano come coppia di lingue, ma non inglese-italiano.

Ad esempio, tradurre "Hello world" dall'inglese al francese può essere eseguito con una sostituzione - "Bonjour" per "Hello", e "le monde" per "world", portando alla traduzione corretta "Bonjour le monde".

Le sostituzioni non funzionano quando lingue diverse usano modi diversi per dire la stessa cosa. Ad esempio, la frase inglese "My name is Jim" si traduce in "Je m'appelle Jim" in francese - letteralmente "Io mi chiamo Jim". "Je" è francese per "Io", "moi" è "me", ma viene concatenato con il verbo poiché inizia con una vocale, diventando "m'", "appelle" significa chiamare, e "Jim" non viene tradotto poiché è un nome e non una parola traducibile. Anche l'ordine delle parole diventa un problema - una semplice sostituzione di "Je m'appelle Jim" diventa "Io mi chiamo Jim", con un ordine delle parole diverso rispetto all'inglese.

> 💁 Alcune parole non vengono mai tradotte - il mio nome è Jim indipendentemente dalla lingua utilizzata per presentarmi. Quando si traduce in lingue che utilizzano alfabeti diversi, o lettere diverse per suoni diversi, le parole possono essere *traslitterate*, ovvero selezionando lettere o caratteri che producono il suono appropriato per suonare come la parola data.

Anche gli idiomi rappresentano un problema per la traduzione. Questi sono frasi che hanno un significato compreso diverso da un'interpretazione diretta delle parole. Ad esempio, in inglese l'idioma "I've got ants in my pants" non si riferisce letteralmente ad avere formiche nei vestiti, ma a essere irrequieti. Se traduci questo in tedesco, finiresti per confondere l'ascoltatore, poiché la versione tedesca è "Ho bombi nel sedere".

> 💁 Diversi contesti culturali aggiungono complessità. Con l'idioma "ants in your pants", in inglese americano "pants" si riferisce ai pantaloni, mentre in inglese britannico "pants" significa biancheria intima.

✅ Se parli più lingue, pensa a qualche frase che non si traduce direttamente.

I sistemi di traduzione automatica si basano su grandi database di regole che descrivono come tradurre determinate frasi e idiomi, insieme a metodi statistici per scegliere le traduzioni appropriate tra le opzioni possibili. Questi metodi statistici utilizzano enormi database di opere tradotte da umani in più lingue per scegliere la traduzione più probabile, una tecnica chiamata *traduzione automatica statistica*. Alcuni di questi utilizzano rappresentazioni intermedie della lingua, permettendo a una lingua di essere tradotta nell'intermedio, poi dall'intermedio a un'altra lingua. In questo modo aggiungere più lingue implica traduzioni verso e dall'intermedio, non verso e da tutte le altre lingue.

### Traduzioni neurali

Le traduzioni neurali utilizzano la potenza dell'AI per tradurre, tipicamente traducendo intere frasi utilizzando un unico modello. Questi modelli sono addestrati su enormi set di dati tradotti da umani, come pagine web, libri e documentazione delle Nazioni Unite.

I modelli di traduzione neurale sono generalmente più piccoli rispetto ai modelli di traduzione automatica poiché non necessitano di enormi database di frasi e idiomi. I moderni servizi AI che offrono traduzioni spesso mescolano più tecniche, combinando traduzione automatica statistica e traduzione neurale.

Non esiste una traduzione 1:1 per nessuna coppia di lingue. Modelli di traduzione diversi produrranno risultati leggermente diversi a seconda dei dati utilizzati per addestrare il modello. Le traduzioni non sono sempre simmetriche - ovvero, se traduci una frase da una lingua a un'altra, poi torni alla prima lingua potresti ottenere una frase leggermente diversa come risultato.

✅ Prova diversi traduttori online come [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) o l'app di traduzione di Apple. Confronta le versioni tradotte di alcune frasi. Prova anche a tradurre in uno, poi tornare indietro in un altro.

## Servizi di traduzione

Esistono numerosi servizi AI che possono essere utilizzati dalle tue applicazioni per tradurre parlato e testo.

### Servizio vocale di Cognitive Services

![Il logo del servizio vocale](../../../../../translated_images/it/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

Il servizio vocale che hai utilizzato nelle lezioni precedenti ha capacità di traduzione per il riconoscimento vocale. Quando riconosci il parlato, puoi richiedere non solo il testo del parlato nella stessa lingua, ma anche in altre lingue.

> 💁 Questo è disponibile solo tramite l'SDK vocale, l'API REST non ha traduzioni integrate.

### Servizio Translator di Cognitive Services

![Il logo del servizio Translator](../../../../../translated_images/it/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

Il servizio Translator è un servizio di traduzione dedicato che può tradurre testo da una lingua a una o più lingue di destinazione. Oltre alla traduzione, supporta una vasta gamma di funzionalità extra, tra cui la mascheratura delle volgarità. Ti consente anche di fornire una traduzione specifica per una particolare parola o frase, per lavorare con termini che non vuoi tradurre o che hanno una traduzione specifica ben nota.

Ad esempio, quando traduci la frase "I have a Raspberry Pi", riferendoti al computer a scheda singola, in un'altra lingua come il francese, vorresti mantenere il nome "Raspberry Pi" così com'è, e non tradurlo, ottenendo "J’ai un Raspberry Pi" invece di "J’ai une pi aux framboises".

## Creare una risorsa di traduzione

Per questa lezione avrai bisogno di una risorsa Translator. Utilizzerai l'API REST per tradurre il testo.

### Compito - creare una risorsa di traduzione

1. Dal tuo terminale o prompt dei comandi, esegui il seguente comando per creare una risorsa Translator nel tuo gruppo di risorse `smart-timer`.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Sostituisci `<location>` con la posizione che hai utilizzato quando hai creato il gruppo di risorse.

1. Ottieni la chiave per il servizio Translator:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Prendi una copia di una delle chiavi.

## Supportare più lingue nelle applicazioni con traduzioni

In un mondo ideale, tutta la tua applicazione dovrebbe comprendere il maggior numero possibile di lingue diverse, dall'ascolto del parlato, alla comprensione del linguaggio, fino alla risposta con il parlato. Questo richiede molto lavoro, quindi i servizi di traduzione possono accelerare il tempo di consegna della tua applicazione.

![Un'architettura di timer intelligente che traduce dal giapponese all'inglese, elabora in inglese e poi traduce di nuovo in giapponese](../../../../../translated_images/it/translated-smart-timer.08ac20057fdc5c37.webp)

Immagina di costruire un timer intelligente che utilizza l'inglese end-to-end, comprendendo l'inglese parlato e convertendolo in testo, eseguendo la comprensione del linguaggio in inglese, costruendo risposte in inglese e rispondendo con parlato in inglese. Se volessi aggiungere il supporto per il giapponese, potresti iniziare traducendo il giapponese parlato in testo inglese, mantenendo il nucleo dell'applicazione invariato, poi traducendo il testo di risposta in giapponese prima di pronunciare la risposta. Questo ti permetterebbe di aggiungere rapidamente il supporto per il giapponese, e potresti espandere per fornire un supporto completo end-to-end per il giapponese in seguito.

> 💁 Lo svantaggio di affidarsi alla traduzione automatica è che lingue e culture diverse hanno modi diversi di esprimere le stesse cose, quindi la traduzione potrebbe non corrispondere all'espressione che ti aspetti.

Le traduzioni automatiche aprono anche possibilità per app e dispositivi che possono tradurre contenuti creati dagli utenti mentre vengono creati. La fantascienza presenta regolarmente "traduttori universali", dispositivi che possono tradurre da lingue aliene in (tipicamente) inglese americano. Questi dispositivi sono meno fantascienza e più realtà scientifica, se si ignora la parte aliena. Esistono già app e dispositivi che forniscono traduzioni in tempo reale di parlato e testo scritto, utilizzando combinazioni di servizi di riconoscimento vocale e traduzione.

Un esempio è l'app per telefoni cellulari [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), dimostrata in questo video:

[![Funzionalità live di Microsoft Translator in azione](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Clicca sull'immagine sopra per guardare il video

Immagina di avere un dispositivo del genere a tua disposizione, soprattutto quando viaggi o interagisci con persone la cui lingua non conosci. Avere dispositivi di traduzione automatici negli aeroporti o negli ospedali fornirebbe miglioramenti molto necessari in termini di accessibilità.

✅ Fai una ricerca: Esistono dispositivi IoT di traduzione disponibili in commercio? E le capacità di traduzione integrate nei dispositivi intelligenti?

> 👽 Sebbene non esistano veri traduttori universali che ci permettano di parlare con gli alieni, il [Microsoft Translator supporta il Klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Tradurre il testo utilizzando un servizio AI

Puoi utilizzare un servizio AI per aggiungere questa capacità di traduzione al tuo timer intelligente.

### Compito - tradurre il testo utilizzando un servizio AI

Segui la guida pertinente per tradurre il testo sul tuo dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Computer a scheda singola - Raspberry Pi](pi-translate-speech.md)
* [Computer a scheda singola - Dispositivo virtuale](virtual-device-translate-speech.md)

---

## 🚀 Sfida

In che modo le traduzioni automatiche possono beneficiare altre applicazioni IoT oltre ai dispositivi intelligenti? Pensa a modi diversi in cui le traduzioni possono essere utili, non solo con le parole pronunciate ma anche con il testo.

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Revisione e studio autonomo

* Leggi di più sulla traduzione automatica sulla [pagina di traduzione automatica su Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Leggi di più sulla traduzione automatica neurale sulla [pagina di traduzione automatica neurale su Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Dai un'occhiata all'elenco delle lingue supportate dai servizi di riconoscimento vocale Microsoft nella [documentazione sul supporto linguistico e vocale per il servizio vocale su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Assegnazione

[Costruisci un traduttore universale](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.