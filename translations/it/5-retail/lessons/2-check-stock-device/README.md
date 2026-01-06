<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-25T16:21:11+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "it"
}
-->
# Controllare le scorte da un dispositivo IoT

![Una panoramica illustrata di questa lezione](../../../../../translated_images/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.it.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

## Quiz pre-lezione

[Quiz pre-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Introduzione

Nella lezione precedente hai imparato i diversi utilizzi del rilevamento di oggetti nel settore retail. Hai anche appreso come addestrare un rilevatore di oggetti per identificare le scorte. In questa lezione imparerai come utilizzare il tuo rilevatore di oggetti da un dispositivo IoT per contare le scorte.

In questa lezione tratteremo:

* [Conteggio delle scorte](../../../../../5-retail/lessons/2-check-stock-device)
* [Chiamare il rilevatore di oggetti dal dispositivo IoT](../../../../../5-retail/lessons/2-check-stock-device)
* [Riquadri di delimitazione](../../../../../5-retail/lessons/2-check-stock-device)
* [Riaddestrare il modello](../../../../../5-retail/lessons/2-check-stock-device)
* [Contare le scorte](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Questa è l'ultima lezione di questo progetto, quindi, dopo aver completato questa lezione e l'assegnazione, non dimenticare di pulire i tuoi servizi cloud. Avrai bisogno dei servizi per completare l'assegnazione, quindi assicurati di completarla prima.
>
> Consulta [la guida per pulire il tuo progetto](../../../clean-up.md) se necessario per istruzioni su come farlo.

## Conteggio delle scorte

I rilevatori di oggetti possono essere utilizzati per controllare le scorte, sia contando gli articoli che assicurandosi che siano al posto giusto. Dispositivi IoT con telecamere possono essere distribuiti in tutto il negozio per monitorare le scorte, iniziando dai punti caldi dove è importante rifornire rapidamente, come le aree in cui sono presenti pochi articoli di alto valore.

Ad esempio, se una telecamera è puntata su uno scaffale che può contenere 8 lattine di concentrato di pomodoro, e un rilevatore di oggetti ne rileva solo 7, significa che una è mancante e deve essere rifornita.

![7 lattine di concentrato di pomodoro su uno scaffale, 4 sulla fila superiore, 3 sulla fila inferiore](../../../../../translated_images/stock-7-cans-tomato-paste.f86059cc573d7bec.it.png)

Nell'immagine sopra, un rilevatore di oggetti ha rilevato 7 lattine di concentrato di pomodoro su uno scaffale che può contenerne 8. Non solo il dispositivo IoT può inviare una notifica della necessità di rifornire, ma può anche indicare la posizione dell'articolo mancante, un dato importante se si utilizzano robot per rifornire gli scaffali.

> 💁 A seconda del negozio e della popolarità dell'articolo, probabilmente non si procederà al rifornimento se manca solo una lattina. Dovresti costruire un algoritmo che determini quando rifornire in base ai tuoi prodotti, clienti e altri criteri.

✅ In quali altri scenari potresti combinare il rilevamento di oggetti e i robot?

A volte sugli scaffali possono esserci articoli sbagliati. Questo potrebbe essere un errore umano durante il rifornimento, o clienti che cambiano idea su un acquisto e rimettono un articolo nel primo spazio disponibile. Quando si tratta di articoli non deperibili come cibi in scatola, è solo un fastidio. Se si tratta di articoli deperibili come prodotti surgelati o refrigerati, ciò può significare che il prodotto non può più essere venduto, poiché potrebbe essere impossibile determinare per quanto tempo l'articolo è stato fuori dal congelatore.

Il rilevamento di oggetti può essere utilizzato per rilevare articoli inaspettati, avvisando nuovamente un umano o un robot per restituire l'articolo non appena viene rilevato.

![Una lattina di mais baby fuori posto accanto al concentrato di pomodoro](../../../../../translated_images/stock-rogue-corn.be1f3ada8c457854.it.png)

Nell'immagine sopra, una lattina di mais baby è stata messa sullo scaffale accanto al concentrato di pomodoro. Il rilevatore di oggetti ha rilevato questo, permettendo al dispositivo IoT di notificare a un umano o a un robot di restituire la lattina alla sua posizione corretta.

## Chiamare il rilevatore di oggetti dal dispositivo IoT

Il rilevatore di oggetti che hai addestrato nella lezione precedente può essere chiamato dal tuo dispositivo IoT.

### Attività - pubblicare un'iterazione del rilevatore di oggetti

Le iterazioni vengono pubblicate dal portale Custom Vision.

1. Avvia il portale Custom Vision su [CustomVision.ai](https://customvision.ai) ed effettua l'accesso se non lo hai già aperto. Quindi apri il tuo progetto `stock-detector`.

1. Seleziona la scheda **Performance** dalle opzioni in alto.

1. Seleziona l'ultima iterazione dall'elenco *Iterations* sul lato.

1. Seleziona il pulsante **Publish** per l'iterazione.

    ![Il pulsante di pubblicazione](../../../../../translated_images/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.it.png)

1. Nella finestra di dialogo *Publish Model*, imposta la risorsa *Prediction resource* sulla risorsa `stock-detector-prediction` che hai creato nella lezione precedente. Lascia il nome come `Iteration2` e seleziona il pulsante **Publish**.

1. Una volta pubblicato, seleziona il pulsante **Prediction URL**. Questo mostrerà i dettagli dell'API di predizione, e avrai bisogno di questi per chiamare il modello dal tuo dispositivo IoT. La sezione inferiore è etichettata *If you have an image file*, ed è questa la sezione che ti interessa. Prendi una copia dell'URL mostrato, che sarà qualcosa come:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Dove `<location>` sarà la posizione che hai usato quando hai creato la tua risorsa Custom Vision, e `<id>` sarà un lungo ID composto da lettere e numeri.

    Prendi anche una copia del valore *Prediction-Key*. Questa è una chiave sicura che devi passare quando chiami il modello. Solo le applicazioni che passano questa chiave sono autorizzate a utilizzare il modello, tutte le altre applicazioni vengono rifiutate.

    ![La finestra di dialogo dell'API di predizione che mostra l'URL e la chiave](../../../../../translated_images/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.it.png)

✅ Quando viene pubblicata una nuova iterazione, avrà un nome diverso. Come pensi che potresti cambiare l'iterazione che un dispositivo IoT sta utilizzando?

### Attività - chiamare il rilevatore di oggetti dal dispositivo IoT

Segui la guida pertinente qui sotto per utilizzare il rilevatore di oggetti dal tuo dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Computer a scheda singola - Raspberry Pi/Dispositivo virtuale](single-board-computer-object-detector.md)

## Riquadri di delimitazione

Quando utilizzi il rilevatore di oggetti, non solo ottieni gli oggetti rilevati con i loro tag e probabilità, ma ottieni anche i riquadri di delimitazione degli oggetti. Questi definiscono dove il rilevatore di oggetti ha rilevato l'oggetto con la probabilità data.

> 💁 Un riquadro di delimitazione è un riquadro che definisce l'area che contiene l'oggetto rilevato, un riquadro che definisce il confine per l'oggetto.

I risultati di una predizione nella scheda **Predictions** in Custom Vision hanno i riquadri di delimitazione disegnati sull'immagine inviata per la predizione.

![4 lattine di concentrato di pomodoro su uno scaffale con predizioni per i 4 rilevamenti di 35.8%, 33.5%, 25.7% e 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.it.png)

Nell'immagine sopra, sono state rilevate 4 lattine di concentrato di pomodoro. Nei risultati, un quadrato rosso è sovrapposto per ogni oggetto rilevato nell'immagine, indicando il riquadro di delimitazione per l'immagine.

✅ Apri le predizioni in Custom Vision e controlla i riquadri di delimitazione.

I riquadri di delimitazione sono definiti con 4 valori - top, left, height e width. Questi valori sono su una scala da 0 a 1, rappresentando le posizioni come percentuale della dimensione dell'immagine. L'origine (la posizione 0,0) è l'angolo in alto a sinistra dell'immagine, quindi il valore top è la distanza dall'alto, e il fondo del riquadro di delimitazione è il top più l'altezza.

![Un riquadro di delimitazione attorno a una lattina di concentrato di pomodoro](../../../../../translated_images/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.it.png)

L'immagine sopra è larga 600 pixel e alta 800 pixel. Il riquadro di delimitazione inizia a 320 pixel dall'alto, dando una coordinata top di 0.4 (800 x 0.4 = 320). Da sinistra, il riquadro di delimitazione inizia a 240 pixel, dando una coordinata left di 0.4 (600 x 0.4 = 240). L'altezza del riquadro di delimitazione è di 240 pixel, dando un valore height di 0.3 (800 x 0.3 = 240). La larghezza del riquadro di delimitazione è di 120 pixel, dando un valore width di 0.2 (600 x 0.2 = 120).

| Coordinata | Valore |
| ---------- | ----: |
| Top        | 0.4   |
| Left       | 0.4   |
| Height     | 0.3   |
| Width      | 0.2   |

Utilizzare valori percentuali da 0 a 1 significa che, indipendentemente dalla dimensione a cui l'immagine viene scalata, il riquadro di delimitazione inizia al 40% della larghezza e altezza, ed è il 30% dell'altezza e il 20% della larghezza.

Puoi utilizzare i riquadri di delimitazione combinati con le probabilità per valutare quanto sia accurato un rilevamento. Ad esempio, un rilevatore di oggetti può rilevare più oggetti che si sovrappongono, ad esempio rilevando una lattina dentro un'altra. Il tuo codice potrebbe esaminare i riquadri di delimitazione, capire che ciò è impossibile e ignorare qualsiasi oggetto che abbia una sovrapposizione significativa con altri oggetti.

![Due riquadri di delimitazione che si sovrappongono a una lattina di concentrato di pomodoro](../../../../../translated_images/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.it.png)

Nell'esempio sopra, un riquadro di delimitazione indica una lattina di concentrato di pomodoro con una probabilità del 78.3%. Un secondo riquadro di delimitazione è leggermente più piccolo ed è all'interno del primo riquadro con una probabilità del 64.3%. Il tuo codice può controllare i riquadri di delimitazione, vedere che si sovrappongono completamente e ignorare la probabilità più bassa poiché non è possibile che una lattina sia dentro un'altra.

✅ Riesci a pensare a una situazione in cui è valido rilevare un oggetto dentro un altro?

## Riaddestrare il modello

Come con il classificatore di immagini, puoi riaddestrare il tuo modello utilizzando i dati catturati dal tuo dispositivo IoT. Utilizzare questi dati reali garantirà che il tuo modello funzioni bene quando viene utilizzato dal tuo dispositivo IoT.

A differenza del classificatore di immagini, non puoi semplicemente etichettare un'immagine. Invece, devi esaminare ogni riquadro di delimitazione rilevato dal modello. Se il riquadro è attorno all'oggetto sbagliato, deve essere eliminato; se è nella posizione sbagliata, deve essere regolato.

### Attività - riaddestrare il modello

1. Assicurati di aver catturato una gamma di immagini utilizzando il tuo dispositivo IoT.

1. Dalla scheda **Predictions**, seleziona un'immagine. Vedrai riquadri rossi che indicano i riquadri di delimitazione degli oggetti rilevati.

1. Esamina ogni riquadro di delimitazione. Selezionalo e vedrai un pop-up che mostra il tag. Usa i manici sugli angoli del riquadro per regolare la dimensione se necessario. Se il tag è sbagliato, rimuovilo con il pulsante **X** e aggiungi il tag corretto. Se il riquadro di delimitazione non contiene un oggetto, eliminalo con il pulsante del cestino.

1. Chiudi l'editor quando hai finito e l'immagine passerà dalla scheda **Predictions** alla scheda **Training Images**. Ripeti il processo per tutte le predizioni.

1. Usa il pulsante **Train** per riaddestrare il tuo modello. Una volta addestrato, pubblica l'iterazione e aggiorna il tuo dispositivo IoT per utilizzare l'URL della nuova iterazione.

1. Ridistribuisci il tuo codice e testa il tuo dispositivo IoT.

## Contare le scorte

Utilizzando una combinazione del numero di oggetti rilevati e dei riquadri di delimitazione, puoi contare le scorte su uno scaffale.

### Attività - contare le scorte

Segui la guida pertinente qui sotto per contare le scorte utilizzando i risultati del rilevatore di oggetti dal tuo dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Computer a scheda singola - Raspberry Pi/Dispositivo virtuale](single-board-computer-count-stock.md)

---

## 🚀 Sfida

Riesci a rilevare scorte errate? Addestra il tuo modello su più oggetti, quindi aggiorna la tua app per avvisarti se vengono rilevate scorte sbagliate.

Magari porta questo concetto oltre e rileva scorte affiancate sullo stesso scaffale, verificando se qualcosa è stato messo nel posto sbagliato definendo limiti sui riquadri di delimitazione.

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Revisione e studio autonomo

* Scopri di più su come progettare un sistema di rilevamento delle scorte end-to-end dalla guida [Out of stock detection at the edge pattern guide on Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Scopri altri modi per costruire soluzioni retail end-to-end combinando una gamma di servizi IoT e cloud guardando questo [Behind the scenes of a retail solution - Hands On! video su YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Assegnazione

[Usa il tuo rilevatore di oggetti al limite](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.