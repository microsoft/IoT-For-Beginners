<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-25T17:10:23+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "it"
}
-->
# Mantieni la tua pianta al sicuro

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.jpg)

> Schizzo di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

## Quiz preliminare alla lezione

[Quiz preliminare alla lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Introduzione

Nelle ultime lezioni hai creato un dispositivo IoT per il monitoraggio del suolo e lo hai connesso al cloud. Ma cosa succederebbe se hacker al servizio di un agricoltore rivale riuscissero a prendere il controllo dei tuoi dispositivi IoT? E se inviassero letture elevate di umidità del suolo, impedendo alle tue piante di essere irrigate, o accendessero il sistema di irrigazione continuamente, uccidendo le tue piante per eccesso di acqua e facendoti spendere una fortuna in bollette?

In questa lezione imparerai a proteggere i dispositivi IoT. Essendo l'ultima lezione di questo progetto, imparerai anche come pulire le risorse cloud, riducendo eventuali costi.

In questa lezione tratteremo:

* [Perché è necessario proteggere i dispositivi IoT?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Crittografia](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Proteggi i tuoi dispositivi IoT](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Genera e utilizza un certificato X.509](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Questa è l'ultima lezione di questo progetto, quindi dopo aver completato la lezione e l'esercizio, non dimenticare di pulire i tuoi servizi cloud. Avrai bisogno dei servizi per completare l'esercizio, quindi assicurati di farlo prima.
>
> Consulta [la guida per pulire il progetto](../../../clean-up.md) se necessario per istruzioni su come farlo.

## Perché è necessario proteggere i dispositivi IoT?

La sicurezza IoT consiste nel garantire che solo i dispositivi previsti possano connettersi al tuo servizio cloud IoT e inviare telemetria, e che solo il tuo servizio cloud possa inviare comandi ai tuoi dispositivi. I dati IoT possono anche essere personali, inclusi dati medici o intimi, quindi tutta la tua applicazione deve considerare la sicurezza per evitare che questi dati vengano divulgati.

Se la tua applicazione IoT non è sicura, ci sono diversi rischi:

* Un dispositivo falso potrebbe inviare dati errati, causando una risposta errata della tua applicazione. Ad esempio, potrebbe inviare letture costanti di alta umidità del suolo, impedendo al sistema di irrigazione di accendersi e facendo morire le tue piante per mancanza di acqua.
* Utenti non autorizzati potrebbero leggere dati dai dispositivi IoT, inclusi dati personali o critici per l'azienda.
* Gli hacker potrebbero inviare comandi per controllare un dispositivo in modo da danneggiare il dispositivo o l'hardware connesso.
* Collegandosi a un dispositivo IoT, gli hacker potrebbero accedere a reti aggiuntive per ottenere accesso a sistemi privati.
* Utenti malintenzionati potrebbero accedere a dati personali e usarli per ricatti.

Questi sono scenari reali e accadono continuamente. Alcuni esempi sono stati forniti nelle lezioni precedenti, ma eccone altri:

* Nel 2018, gli hacker hanno utilizzato un punto di accesso WiFi aperto su un termostato di un acquario per accedere alla rete di un casinò e rubare dati. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* Nel 2016, il botnet Mirai ha lanciato un attacco di negazione del servizio contro Dyn, un fornitore di servizi Internet, causando il blocco di ampie porzioni di Internet. Questo botnet ha utilizzato malware per connettersi a dispositivi IoT come DVR e telecamere che utilizzavano nomi utente e password predefiniti, e da lì ha lanciato l'attacco. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys aveva un database di utenti dei loro giocattoli CloudPets connessi, disponibile pubblicamente su Internet. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava taggava i corridori che incontravi lungo il percorso e mostrava i loro itinerari, permettendo agli estranei di vedere dove vivi. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Fai una ricerca: Cerca altri esempi di attacchi IoT e violazioni di dati IoT, soprattutto con oggetti personali come spazzolini da denti o bilance connesse a Internet. Pensa all'impatto che questi attacchi potrebbero avere sulle vittime o sui clienti.

> 💁 La sicurezza è un argomento vasto, e questa lezione toccherà solo alcune delle basi relative alla connessione del tuo dispositivo al cloud. Altri argomenti che non verranno trattati includono il monitoraggio delle modifiche ai dati in transito, l'hacking diretto dei dispositivi o le modifiche alle configurazioni dei dispositivi. L'hacking IoT è una minaccia così grande che sono stati sviluppati strumenti come [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn). Questi strumenti sono simili agli antivirus e agli strumenti di sicurezza che potresti avere sul tuo computer, ma progettati per piccoli dispositivi IoT a basso consumo.

## Crittografia

Quando un dispositivo si connette a un servizio IoT, utilizza un ID per identificarsi. Il problema è che questo ID può essere clonato: un hacker potrebbe configurare un dispositivo dannoso che utilizza lo stesso ID di un dispositivo reale ma invia dati falsi.

![Sia i dispositivi validi che quelli dannosi potrebbero utilizzare lo stesso ID per inviare telemetria](../../../../../translated_images/it/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.png)

La soluzione è convertire i dati inviati in un formato criptato, utilizzando un valore noto solo al dispositivo e al cloud. Questo processo si chiama *crittografia*, e il valore utilizzato per crittografare i dati è chiamato *chiave di crittografia*.

![Se viene utilizzata la crittografia, solo i messaggi crittografati saranno accettati, gli altri saranno rifiutati](../../../../../translated_images/it/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.png)

Il servizio cloud può quindi convertire i dati in un formato leggibile, utilizzando un processo chiamato *decrittografia*, utilizzando la stessa chiave di crittografia o una *chiave di decrittografia*. Se il messaggio crittografato non può essere decrittato dalla chiave, il dispositivo è stato hackerato e il messaggio viene rifiutato.

La tecnica per eseguire crittografia e decrittografia si chiama *crittografia*.

### Crittografia antica

I primi tipi di crittografia erano cifrari di sostituzione, risalenti a 3.500 anni fa. I cifrari di sostituzione prevedono la sostituzione di una lettera con un'altra. Ad esempio, il [cifrario di Cesare](https://wikipedia.org/wiki/Caesar_cipher) prevede lo spostamento dell'alfabeto di una quantità definita, con solo il mittente del messaggio crittografato e il destinatario previsto che conoscono il numero di lettere da spostare.

Il [cifrario di Vigenère](https://wikipedia.org/wiki/Vigenère_cipher) ha portato questo concetto oltre, utilizzando parole per crittografare il testo, in modo che ogni lettera nel testo originale fosse spostata di una quantità diversa, anziché sempre dello stesso numero di lettere.

La crittografia è stata utilizzata per una vasta gamma di scopi, come proteggere una ricetta per la smaltatura della ceramica nell'antica Mesopotamia, scrivere biglietti d'amore segreti in India o mantenere segreti incantesimi magici nell'antico Egitto.

### Crittografia moderna

La crittografia moderna è molto più avanzata, rendendo più difficile da decifrare rispetto ai metodi antichi. La crittografia moderna utilizza complicati calcoli matematici per crittografare i dati con un numero di chiavi possibili troppo elevato per rendere praticabili gli attacchi a forza bruta.

La crittografia viene utilizzata in molti modi per comunicazioni sicure. Se stai leggendo questa pagina su GitHub, potresti notare che l'indirizzo del sito web inizia con *HTTPS*, il che significa che la comunicazione tra il tuo browser e i server web di GitHub è crittografata. Se qualcuno fosse in grado di leggere il traffico Internet tra il tuo browser e GitHub, non sarebbe in grado di leggere i dati poiché sono crittografati. Il tuo computer potrebbe persino crittografare tutti i dati sul tuo disco rigido, così se qualcuno lo rubasse, non potrebbe leggere nessuno dei tuoi dati senza la tua password.

> 🎓 HTTPS sta per HyperText Transfer Protocol **Secure**

Purtroppo, non tutto è sicuro. Alcuni dispositivi non hanno alcuna sicurezza, altri sono protetti con chiavi facili da decifrare, o a volte tutti i dispositivi dello stesso tipo utilizzano la stessa chiave. Ci sono stati casi di dispositivi IoT molto personali che hanno tutti la stessa password per connettersi tramite WiFi o Bluetooth. Se puoi connetterti al tuo dispositivo, puoi connetterti anche a quello di qualcun altro. Una volta connesso, potresti accedere a dati molto privati o avere il controllo sul loro dispositivo.

> 💁 Nonostante le complessità della crittografia moderna e le affermazioni che decifrare la crittografia possa richiedere miliardi di anni, l'ascesa del calcolo quantistico ha portato alla possibilità di decifrare tutta la crittografia conosciuta in un tempo molto breve!

### Chiavi simmetriche e asimmetriche

La crittografia si divide in due tipi: simmetrica e asimmetrica.

La crittografia **simmetrica** utilizza la stessa chiave per crittografare e decrittografare i dati. Sia il mittente che il destinatario devono conoscere la stessa chiave. Questo è il tipo meno sicuro, poiché la chiave deve essere condivisa in qualche modo. Per un mittente che invia un messaggio crittografato a un destinatario, il mittente potrebbe prima dover inviare al destinatario la chiave.

![La crittografia con chiave simmetrica utilizza la stessa chiave per crittografare e decrittografare un messaggio](../../../../../translated_images/it/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Se la chiave viene rubata durante il transito, o il mittente o il destinatario vengono hackerati e la chiave viene trovata, la crittografia può essere violata.

![La crittografia con chiave simmetrica è sicura solo se un hacker non ottiene la chiave - in caso contrario può intercettare e decrittografare il messaggio](../../../../../translated_images/it/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

La crittografia **asimmetrica** utilizza 2 chiavi: una chiave di crittografia e una chiave di decrittografia, chiamate coppia di chiavi pubblica/privata. La chiave pubblica viene utilizzata per crittografare il messaggio, ma non può essere utilizzata per decrittografarlo; la chiave privata viene utilizzata per decrittografare il messaggio, ma non può essere utilizzata per crittografarlo.

![La crittografia asimmetrica utilizza una chiave diversa per crittografare e decrittografare. La chiave di crittografia viene inviata ai mittenti dei messaggi affinché possano crittografare un messaggio prima di inviarlo al destinatario che possiede le chiavi](../../../../../translated_images/it/send-message-asymmetric.7abe327c62615b8c.webp)

Il destinatario condivide la propria chiave pubblica, e il mittente la utilizza per crittografare il messaggio. Una volta inviato il messaggio, il destinatario lo decrittografa con la propria chiave privata. La crittografia asimmetrica è più sicura poiché la chiave privata viene mantenuta privata dal destinatario e non viene mai condivisa. Chiunque può avere la chiave pubblica, poiché può essere utilizzata solo per crittografare i messaggi.

La crittografia simmetrica è più veloce di quella asimmetrica, mentre quella asimmetrica è più sicura. Alcuni sistemi utilizzano entrambe: la crittografia asimmetrica per crittografare e condividere la chiave simmetrica, e la crittografia simmetrica per crittografare tutti i dati. Questo rende più sicuro condividere la chiave simmetrica tra mittente e destinatario, e più veloce crittografare e decrittografare i dati.

## Proteggi i tuoi dispositivi IoT

I dispositivi IoT possono essere protetti utilizzando crittografia simmetrica o asimmetrica. La crittografia simmetrica è più semplice, ma meno sicura.

### Chiavi simmetriche

Quando hai configurato il tuo dispositivo IoT per interagire con IoT Hub, hai utilizzato una stringa di connessione. Un esempio di stringa di connessione è:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Questa stringa di connessione è composta da tre parti separate da punti e virgola, con ciascuna parte costituita da una chiave e un valore:

| Chiave | Valore | Descrizione |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | L'URL di IoT Hub |
| DeviceId | `soil-moisture-sensor` | L'ID univoco del dispositivo |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Una chiave simmetrica nota al dispositivo e a IoT Hub |

L'ultima parte di questa stringa di connessione, la `SharedAccessKey`, è la chiave simmetrica nota sia al dispositivo che a IoT Hub. Questa chiave non viene mai inviata dal dispositivo al cloud, né dal cloud al dispositivo. Viene invece utilizzata per crittografare i dati inviati o ricevuti.

✅ Fai un esperimento. Cosa pensi che accadrà se modifichi la parte `SharedAccessKey` della stringa di connessione quando connetti il tuo dispositivo IoT? Provalo.

Quando il dispositivo tenta di connettersi per la prima volta, invia un token di firma di accesso condiviso (SAS) composto dall'URL di IoT Hub, un timestamp che indica quando la firma di accesso scadrà (di solito 1 giorno dal momento attuale) e una firma. Questa firma consiste nell'URL e nel tempo di scadenza crittografati con la chiave di accesso condivisa della stringa di connessione.

IoT Hub decrittografa questa firma con la chiave di accesso condivisa e, se il valore decrittografato corrisponde all'URL e alla scadenza, il dispositivo è autorizzato a connettersi. Verifica anche che l'ora corrente sia precedente alla scadenza, per impedire a un dispositivo dannoso di catturare il token SAS di un dispositivo reale e utilizzarlo.

Questo è un modo elegante per verificare che il mittente sia il dispositivo corretto. Inviando alcuni dati noti sia in forma decrittografata che crittografata, il server può verificare il dispositivo assicurandosi che, quando decrittografa i dati crittografati, il risultato corrisponda alla versione decrittografata inviata. Se corrisponde, allora sia il mittente che il destinatario hanno la stessa chiave di crittografia simmetrica.
💁 Poiché il dispositivo IoT ha un tempo di scadenza, è necessario che conosca l'ora esatta, solitamente letta da un server [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Se l'ora non è precisa, la connessione fallirà.
Dopo la connessione, tutti i dati inviati all'IoT Hub dal dispositivo, o al dispositivo dall'IoT Hub, saranno crittografati con la chiave di accesso condivisa.

✅ Cosa pensi che accada se più dispositivi condividono la stessa stringa di connessione?

> 💁 È una cattiva pratica di sicurezza memorizzare questa chiave nel codice. Se un hacker ottiene il tuo codice sorgente, può ottenere la tua chiave. Inoltre, diventa più complicato durante il rilascio del codice, poiché sarebbe necessario ricompilare con una chiave aggiornata per ogni dispositivo. È meglio caricare questa chiave da un modulo di sicurezza hardware - un chip sul dispositivo IoT che memorizza valori crittografati che possono essere letti dal tuo codice.
>
> Quando si impara l'IoT, spesso è più semplice inserire la chiave nel codice, come hai fatto in una lezione precedente, ma devi assicurarti che questa chiave non venga controllata in un sistema di controllo del codice sorgente pubblico.

I dispositivi hanno 2 chiavi e 2 stringhe di connessione corrispondenti. Questo consente di ruotare le chiavi, ovvero passare da una chiave all'altra se la prima viene compromessa, e rigenerare la prima chiave.

### Certificati X.509

Quando utilizzi la crittografia asimmetrica con una coppia di chiavi pubblica/privata, devi fornire la tua chiave pubblica a chiunque voglia inviarti dati. Il problema è: come può il destinatario della tua chiave essere sicuro che sia effettivamente la tua chiave pubblica e non quella di qualcun altro che finge di essere te? Invece di fornire una chiave, puoi fornire la tua chiave pubblica all'interno di un certificato che è stato verificato da una terza parte fidata, chiamato certificato X.509.

I certificati X.509 sono documenti digitali che contengono la parte pubblica della coppia di chiavi pubblica/privata. Di solito vengono emessi da una serie di organizzazioni fidate chiamate [Autorità di certificazione](https://wikipedia.org/wiki/Certificate_authority) (CA) e firmati digitalmente dalla CA per indicare che la chiave è valida e proviene da te. Si ha fiducia nel certificato e che la chiave pubblica provenga da chi il certificato dichiara, perché si ha fiducia nella CA, in modo simile a come si avrebbe fiducia in un passaporto o una patente di guida perché si ha fiducia nel paese che li emette. I certificati hanno un costo, ma è anche possibile "auto-firmarli", ovvero creare un certificato da soli che viene firmato da te stesso, per scopi di test.

> 💁 Non dovresti mai utilizzare un certificato auto-firmato per una versione di produzione.

Questi certificati contengono diversi campi, tra cui chi ha emesso la chiave pubblica, i dettagli della CA che l'ha emesso, la durata della validità e la chiave pubblica stessa. Prima di utilizzare un certificato, è buona pratica verificarlo controllando che sia stato firmato dalla CA originale.

✅ Puoi leggere un elenco completo dei campi del certificato nel [tutorial Microsoft Understanding X.509 Public Key Certificates](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields).

Quando utilizzi certificati X.509, sia il mittente che il destinatario avranno le proprie chiavi pubbliche e private, oltre a certificati X.509 che contengono la chiave pubblica. Scambiano quindi i certificati X.509 in qualche modo, utilizzando le chiavi pubbliche reciproche per crittografare i dati che inviano e le proprie chiavi private per decrittografare i dati che ricevono.

![Invece di condividere una chiave pubblica, puoi condividere un certificato. L'utente del certificato può verificare che provenga da te controllando con l'autorità di certificazione che lo ha firmato.](../../../../../translated_images/it/send-message-certificate.9cc576ac1e46b76e.webp)

Un grande vantaggio dell'utilizzo dei certificati X.509 è che possono essere condivisi tra dispositivi. Puoi creare un certificato, caricarlo su IoT Hub e utilizzarlo per tutti i tuoi dispositivi. Ogni dispositivo deve solo conoscere la chiave privata per decrittografare i messaggi che riceve da IoT Hub.

Il certificato utilizzato dal tuo dispositivo per crittografare i messaggi che invia all'IoT Hub è pubblicato da Microsoft. È lo stesso certificato che molti servizi Azure utilizzano ed è talvolta integrato negli SDK.

> 💁 Ricorda, una chiave pubblica è proprio questo - pubblica. La chiave pubblica di Azure può essere utilizzata solo per crittografare i dati inviati ad Azure, non per decrittografarli, quindi può essere condivisa ovunque, incluso nel codice sorgente. Ad esempio, puoi vederla nel [codice sorgente Azure IoT C SDK](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Ci sono molti termini tecnici legati ai certificati X.509. Puoi leggere le definizioni di alcuni dei termini che potresti incontrare in [La guida semplice al gergo dei certificati X.509](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn).

## Generare e utilizzare un certificato X.509

I passaggi per generare un certificato X.509 sono:

1. Creare una coppia di chiavi pubblica/privata. Uno degli algoritmi più utilizzati per generare una coppia di chiavi pubblica/privata è chiamato [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA).

1. Inviare la chiave pubblica con i dati associati per la firma, sia da una CA che tramite auto-firma.

L'Azure CLI ha comandi per creare una nuova identità del dispositivo in IoT Hub e generare automaticamente la coppia di chiavi pubblica/privata e creare un certificato auto-firmato.

> 💁 Se vuoi vedere i passaggi in dettaglio, invece di utilizzare l'Azure CLI, puoi trovarli nel [tutorial sull'utilizzo di OpenSSL per creare certificati auto-firmati nella documentazione Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn).

### Attività - creare un'identità del dispositivo utilizzando un certificato X.509

1. Esegui il seguente comando per registrare la nuova identità del dispositivo, generando automaticamente le chiavi e i certificati:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome che hai utilizzato per il tuo IoT Hub.

    Questo creerà un dispositivo con un ID di `soil-moisture-sensor-x509` per distinguerlo dall'identità del dispositivo che hai creato nella lezione precedente. Questo comando creerà anche 2 file nella directory corrente:

    * `soil-moisture-sensor-x509-key.pem` - questo file contiene la chiave privata per il dispositivo.
    * `soil-moisture-sensor-x509-cert.pem` - questo è il file del certificato X.509 per il dispositivo.

    Tieni questi file al sicuro! Il file della chiave privata non dovrebbe essere controllato in un sistema di controllo del codice sorgente pubblico.

### Attività - utilizzare il certificato X.509 nel codice del tuo dispositivo

Segui la guida pertinente per connettere il tuo dispositivo IoT al cloud utilizzando il certificato X.509:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Computer a scheda singola - Raspberry Pi/Dispositivo IoT virtuale](single-board-computer-x509.md)

---

## 🚀 Sfida

Esistono diversi modi per creare, gestire e eliminare servizi Azure come Gruppi di Risorse e IoT Hub. Uno di questi è il [Portale Azure](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) - un'interfaccia web che ti offre una GUI per gestire i tuoi servizi Azure.

Vai su [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) e esplora il portale. Vedi se riesci a creare un IoT Hub utilizzando il portale, quindi eliminarlo.

**Suggerimento** - quando crei servizi tramite il portale, non è necessario creare un Gruppo di Risorse in anticipo, uno può essere creato durante la creazione del servizio. Assicurati di eliminarlo quando hai finito!

Puoi trovare molta documentazione, tutorial e guide sul Portale Azure nella [documentazione del portale Azure](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Revisione e studio autonomo

* Leggi la storia della crittografia sulla [pagina Storia della crittografia su Wikipedia](https://wikipedia.org/wiki/History_of_cryptography).
* Leggi sui certificati X.509 sulla [pagina X.509 su Wikipedia](https://wikipedia.org/wiki/X.509).

## Compito

[Costruisci un nuovo dispositivo IoT](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.