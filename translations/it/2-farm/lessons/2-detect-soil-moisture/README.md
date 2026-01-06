<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-25T17:00:25+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "it"
}
-->
C, pronunciato *I-squared-C*, è un protocollo multi-controller e multi-periferica, in cui qualsiasi dispositivo connesso può agire come controller o periferica comunicando tramite il bus I²C (il nome per un sistema di comunicazione che trasferisce dati). I dati vengono inviati sotto forma di pacchetti indirizzati, con ogni pacchetto contenente l'indirizzo del dispositivo connesso a cui è destinato.

> 💁 Questo modello era precedentemente noto come master/slave, ma questa terminologia sta venendo abbandonata a causa della sua associazione con la schiavitù. La [Open Source Hardware Association ha adottato i termini controller/peripheral](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), ma potresti ancora trovare riferimenti alla vecchia terminologia.

I dispositivi hanno un indirizzo che viene utilizzato quando si connettono al bus I²C, e di solito è codificato direttamente sul dispositivo. Ad esempio, ogni tipo di sensore Grove di Seeed ha lo stesso indirizzo, quindi tutti i sensori di luce hanno lo stesso indirizzo, tutti i pulsanti hanno un indirizzo diverso da quello dei sensori di luce. Alcuni dispositivi offrono modi per modificare l'indirizzo, cambiando le impostazioni dei jumper o saldando i pin insieme.

I²C ha un bus composto da 2 fili principali, insieme a 2 fili di alimentazione:

| Filo | Nome | Descrizione |
| ---- | --------- | ----------- |
| SDA | Serial Data | Questo filo serve per inviare dati tra i dispositivi. |
| SCL | Serial Clock | Questo filo invia un segnale di clock a una velocità impostata dal controller. |
| VCC | Voltage common collector | L'alimentazione per i dispositivi. Questo è collegato ai fili SDA e SCL per fornire loro energia tramite una resistenza pull-up che spegne il segnale quando nessun dispositivo è il controller. |
| GND | Ground | Fornisce una massa comune per il circuito elettrico. |

![Bus I2C con 3 dispositivi collegati ai fili SDA e SCL, condividendo un filo di massa comune](../../../../../translated_images/i2c.83da845dde02256bdd462dbe0d5145461416b74930571b89d1ae142841eeb584.it.png)

Per inviare dati, un dispositivo emette una condizione di avvio per indicare che è pronto a inviare dati. Diventerà quindi il controller. Il controller invia l'indirizzo del dispositivo con cui vuole comunicare, insieme all'indicazione se vuole leggere o scrivere dati. Dopo che i dati sono stati trasmessi, il controller invia una condizione di stop per indicare che ha terminato. Dopo di ciò, un altro dispositivo può diventare il controller e inviare o ricevere dati.

2</sup>C ha limiti di velocità, con 3 modalità diverse che funzionano a velocità fisse. La più veloce è la modalità ad alta velocità con una velocità massima di 3,4 Mbps (megabit al secondo), anche se pochissimi dispositivi supportano questa velocità. Il Raspberry Pi, ad esempio, è limitato alla modalità veloce a 400 Kbps (kilobit al secondo). La modalità standard funziona a 100 Kbps.

> 💁 Se stai utilizzando un Raspberry Pi con un Grove Base hat come hardware IoT, potrai vedere un certo numero di prese I<sup>2</sup>C sulla scheda che puoi utilizzare per comunicare con i sensori I<sup>2</sup>C. I sensori analogici Grove utilizzano anche I<sup>2</sup>C con un ADC per inviare valori analogici come dati digitali, quindi il sensore di luce che hai utilizzato simulava un pin analogico, con il valore inviato tramite I<sup>2</sup>C poiché il Raspberry Pi supporta solo pin digitali.

### Ricevitore-trasmettitore asincrono universale (UART)

UART coinvolge circuiti fisici che permettono a due dispositivi di comunicare. Ogni dispositivo ha 2 pin di comunicazione - trasmettitore (Tx) e ricevitore (Rx), con il pin Tx del primo dispositivo collegato al pin Rx del secondo, e con il pin Tx del secondo dispositivo collegato al pin Rx del primo. Questo consente di inviare dati in entrambe le direzioni.

* Il dispositivo 1 trasmette dati dal suo pin Tx, che vengono ricevuti dal dispositivo 2 sul suo pin Rx
* Il dispositivo 1 riceve dati sul suo pin Rx che vengono trasmessi dal dispositivo 2 dal suo pin Tx

![UART con il pin Tx su un chip collegato al pin Rx su un altro, e viceversa](../../../../../translated_images/uart.d0dbd3fb9e3728c6.it.png)

> 🎓 I dati vengono inviati un bit alla volta, e questo è noto come comunicazione *seriale*. La maggior parte dei sistemi operativi e microcontrollori ha *porte seriali*, ovvero connessioni che possono inviare e ricevere dati seriali disponibili per il tuo codice.

I dispositivi UART hanno una [velocità di trasmissione](https://wikipedia.org/wiki/Symbol_rate) (nota anche come Symbol rate), che è la velocità con cui i dati vengono inviati e ricevuti in bit al secondo. Una velocità di trasmissione comune è 9.600, il che significa che 9.600 bit (0 e 1) di dati vengono inviati ogni secondo.

UART utilizza bit di inizio e fine - ovvero invia un bit di inizio per indicare che sta per inviare un byte (8 bit) di dati, quindi un bit di fine dopo aver inviato gli 8 bit.

La velocità di UART dipende dall'hardware, ma anche le implementazioni più veloci non superano i 6,5 Mbps (megabit al secondo, o milioni di bit, 0 o 1, inviati al secondo).

Puoi utilizzare UART sui pin GPIO - puoi impostare un pin come Tx e un altro come Rx, quindi collegarli a un altro dispositivo.

> 💁 Se stai utilizzando un Raspberry Pi con un Grove Base hat come hardware IoT, potrai vedere una presa UART sulla scheda che puoi utilizzare per comunicare con sensori che utilizzano il protocollo UART.

### Interfaccia periferica seriale (SPI)

SPI è progettata per comunicare su brevi distanze, ad esempio su un microcontrollore per parlare con un dispositivo di archiviazione come la memoria flash. Si basa su un modello controller/periferica con un singolo controller (di solito il processore del dispositivo IoT) che interagisce con più periferiche. Il controller controlla tutto selezionando una periferica e inviando o richiedendo dati.

> 💁 Come I<sup>2</sup>C, i termini controller e periferica sono cambiamenti recenti, quindi potresti vedere ancora i termini più vecchi utilizzati.

I controller SPI utilizzano 3 fili, insieme a 1 filo extra per periferica. Le periferiche utilizzano 4 fili. Questi fili sono:

| Filo | Nome | Descrizione |
| ---- | --------- | ----------- |
| COPI | Controller Output, Peripheral Input | Questo filo serve per inviare dati dal controller alla periferica. |
| CIPO | Controller Input, Peripheral Output | Questo filo serve per inviare dati dalla periferica al controller. |
| SCLK | Serial Clock | Questo filo invia un segnale di clock a una velocità impostata dal controller. |
| CS   | Chip Select | Il controller ha più fili, uno per periferica, e ogni filo si collega al filo CS sulla periferica corrispondente. |

![SPI con un controller e due periferiche](../../../../../translated_images/spi.297431d6f98b386b.it.png)

Il filo CS viene utilizzato per attivare una periferica alla volta, comunicando tramite i fili COPI e CIPO. Quando il controller deve cambiare periferica, disattiva il filo CS collegato alla periferica attualmente attiva, quindi attiva il filo collegato alla periferica con cui vuole comunicare successivamente.

SPI è *full-duplex*, il che significa che il controller può inviare e ricevere dati contemporaneamente dalla stessa periferica utilizzando i fili COPI e CIPO. SPI utilizza un segnale di clock sul filo SCLK per mantenere i dispositivi sincronizzati, quindi a differenza dell'invio diretto tramite UART non ha bisogno di bit di inizio e fine.

Non ci sono limiti di velocità definiti per SPI, con implementazioni spesso in grado di trasmettere più megabyte di dati al secondo.

I kit di sviluppo IoT spesso supportano SPI su alcuni dei pin GPIO. Ad esempio, su un Raspberry Pi puoi utilizzare i pin GPIO 19, 21, 23, 24 e 26 per SPI.

### Wireless

Alcuni sensori possono comunicare tramite protocolli wireless standard, come Bluetooth (principalmente Bluetooth Low Energy, o BLE), LoRaWAN (un protocollo di rete a basso consumo a **Lo**nga **Ra**ggia), o WiFi. Questi permettono di avere sensori remoti non fisicamente collegati a un dispositivo IoT.

Un esempio è nei sensori commerciali di umidità del suolo. Questi misurano l'umidità del suolo in un campo, quindi inviano i dati tramite LoRaWAN a un dispositivo hub, che elabora i dati o li invia su Internet. Questo permette al sensore di essere lontano dal dispositivo IoT che gestisce i dati, riducendo il consumo energetico e la necessità di grandi reti WiFi o cavi lunghi.

BLE è popolare per sensori avanzati come i tracker di fitness che funzionano sul polso. Questi combinano più sensori e inviano i dati dei sensori a un dispositivo IoT sotto forma del tuo telefono tramite BLE.

✅ Hai sensori Bluetooth con te, nella tua casa o nella tua scuola? Questi potrebbero includere sensori di temperatura, sensori di occupazione, tracker di dispositivi e dispositivi di fitness.

Un modo popolare per i dispositivi commerciali di connettersi è Zigbee. Zigbee utilizza il WiFi per formare reti mesh tra dispositivi, dove ogni dispositivo si connette a quanti più dispositivi vicini possibile, formando un gran numero di connessioni come una ragnatela. Quando un dispositivo vuole inviare un messaggio su Internet può inviarlo ai dispositivi più vicini, che poi lo inoltrano ad altri dispositivi vicini e così via, fino a raggiungere un coordinatore e poter essere inviato su Internet.

> 🐝 Il nome Zigbee si riferisce alla danza delle api dopo il loro ritorno all'alveare.

## Misurare i livelli di umidità nel suolo

Puoi misurare il livello di umidità nel suolo utilizzando un sensore di umidità del suolo, un dispositivo IoT e una pianta domestica o un pezzo di terreno vicino.

### Compito - misurare l'umidità del suolo

Segui la guida pertinente per misurare l'umidità del suolo utilizzando il tuo dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Computer a scheda singola - Raspberry Pi](pi-soil-moisture.md)
* [Computer a scheda singola - Dispositivo virtuale](virtual-device-soil-moisture.md)

## Calibrazione del sensore

I sensori si basano sulla misurazione di proprietà elettriche come la resistenza o la capacità.

> 🎓 La resistenza, misurata in ohm (Ω), è quanto ostacolo c'è al passaggio della corrente elettrica attraverso qualcosa. Quando una tensione viene applicata a un materiale, la quantità di corrente che lo attraversa dipende dalla resistenza del materiale. Puoi leggere di più sulla [pagina della resistenza elettrica su Wikipedia](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 La capacità, misurata in farad (F), è la capacità di un componente o circuito di raccogliere e immagazzinare energia elettrica. Puoi leggere di più sulla capacità sulla [pagina della capacità su Wikipedia](https://wikipedia.org/wiki/Capacitance).

Queste misurazioni non sono sempre utili - immagina un sensore di temperatura che ti dia una misurazione di 22,5KΩ! Invece il valore misurato deve essere convertito in un'unità utile tramite la calibrazione - ovvero abbinare i valori misurati alla quantità misurata per consentire la conversione di nuove misurazioni nell'unità corretta.

Alcuni sensori vengono pre-calibrati. Ad esempio, il sensore di temperatura che hai utilizzato nella lezione precedente era già calibrato in modo da poter restituire una misurazione della temperatura in °C. In fabbrica il primo sensore creato verrebbe esposto a una gamma di temperature note e la resistenza misurata. Questo verrebbe poi utilizzato per costruire un calcolo che può convertire dal valore misurato in Ω (l'unità di resistenza) a °C.

> 💁 La formula per calcolare la resistenza dalla temperatura si chiama [equazione di Steinhart–Hart](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Calibrazione del sensore di umidità del suolo

L'umidità del suolo viene misurata utilizzando il contenuto d'acqua gravimetrico o volumetrico.

* Gravimetrico è il peso dell'acqua in un'unità di peso del suolo misurato, come il numero di chilogrammi di acqua per chilogrammo di suolo secco
* Volumetrico è il volume di acqua in un'unità di volume del suolo misurato, come il numero di metri cubi di acqua per metri cubi di suolo secco

> 🇺🇸 Per gli americani, grazie alla coerenza delle unità, questi possono essere misurati in libbre invece di chilogrammi o piedi cubi invece di metri cubi.

I sensori di umidità del suolo misurano la resistenza elettrica o la capacità - questo non varia solo in base all'umidità del suolo, ma anche al tipo di suolo poiché i componenti nel suolo possono cambiare le sue caratteristiche elettriche. Idealmente i sensori dovrebbero essere calibrati - ovvero prendere letture dal sensore e confrontarle con misurazioni ottenute utilizzando un approccio più scientifico. Ad esempio, un laboratorio può calcolare l'umidità gravimetrica del suolo utilizzando campioni di un campo specifico prelevati alcune volte all'anno, e questi numeri utilizzati per calibrare il sensore, abbinando la lettura del sensore all'umidità gravimetrica del suolo.

![Un grafico della tensione rispetto al contenuto di umidità del suolo](../../../../../translated_images/soil-moisture-to-voltage.df86d80cda158700.it.png)

Il grafico sopra mostra come calibrare un sensore. La tensione viene catturata per un campione di suolo che viene poi misurato in laboratorio confrontando il peso umido con il peso secco (misurando il peso umido, poi asciugandolo in un forno e misurando il peso secco). Una volta prese alcune letture, queste possono essere tracciate su un grafico e una linea adattata ai punti. Questa linea può poi essere utilizzata per convertire le letture del sensore di umidità del suolo prese da un dispositivo IoT in misurazioni effettive dell'umidità del suolo.

💁 Per i sensori resistivi di umidità del suolo, la tensione aumenta con l'aumento dell'umidità del suolo. Per i sensori capacitivi di umidità del suolo, la tensione diminuisce con l'aumento dell'umidità del suolo, quindi i grafici per questi avrebbero una pendenza verso il basso, non verso l'alto.

![Un valore di umidità del suolo interpolato dal grafico](../../../../../translated_images/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.it.png)

Il grafico sopra mostra una lettura di tensione da un sensore di umidità del suolo, e seguendo quella linea sul grafico, l'umidità effettiva del suolo può essere calcolata.

Questo approccio significa che l'agricoltore deve solo ottenere alcune misurazioni di laboratorio per un campo, quindi può utilizzare dispositivi IoT per misurare l'umidità del suolo - accelerando drasticamente il tempo necessario per prendere misurazioni.

---

## 🚀 Sfida

I sensori resistivi e capacitivi di umidità del suolo hanno una serie di differenze. Quali sono queste differenze, e quale tipo (se esiste) è il migliore per un agricoltore? Questa risposta cambia tra paesi in via di sviluppo e paesi sviluppati?

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Revisione e studio autonomo

Leggi sull'hardware e i protocolli utilizzati dai sensori e dagli attuatori:

* [Pagina Wikipedia GPIO](https://wikipedia.org/wiki/General-purpose_input/output)
* [Pagina Wikipedia UART](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [Pagina Wikipedia SPI](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [Pagina Wikipedia I<sup>2</sup>C](https://wikipedia.org/wiki/I²C)
* [Pagina Wikipedia Zigbee](https://wikipedia.org/wiki/Zigbee)

## Compito

[Calibra il tuo sensore](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un esperto umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.