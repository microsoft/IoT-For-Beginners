# Controlla la qualità della frutta con un dispositivo IoT

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-16.215daf18b00631fb.webp)

> Sketchnote di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

## Quiz preliminare

[Quiz preliminare](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Introduzione

Nella lezione precedente hai imparato a conoscere i classificatori di immagini e come addestrarli per rilevare frutta buona e cattiva. Per utilizzare questo classificatore di immagini in un'applicazione IoT, è necessario essere in grado di catturare un'immagine utilizzando una fotocamera e inviarla al cloud per la classificazione.

In questa lezione imparerai a conoscere i sensori delle fotocamere e come utilizzarli con un dispositivo IoT per catturare un'immagine. Inoltre, scoprirai come chiamare il classificatore di immagini dal tuo dispositivo IoT.

In questa lezione tratteremo:

* [Sensori delle fotocamere](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Catturare un'immagine con un dispositivo IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Pubblicare il tuo classificatore di immagini](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Classificare immagini dal tuo dispositivo IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Migliorare il modello](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Sensori delle fotocamere

I sensori delle fotocamere, come suggerisce il nome, sono fotocamere che puoi collegare al tuo dispositivo IoT. Possono scattare immagini statiche o catturare video in streaming. Alcuni restituiscono dati grezzi dell'immagine, altri comprimono i dati in un file immagine come JPEG o PNG. Di solito, le fotocamere che funzionano con dispositivi IoT sono molto più piccole e a bassa risoluzione rispetto a quelle a cui potresti essere abituato, ma puoi ottenere fotocamere ad alta risoluzione che competono con i migliori telefoni. Puoi trovare una vasta gamma di obiettivi intercambiabili, configurazioni con più fotocamere, fotocamere termiche a infrarossi o fotocamere UV.

![La luce di una scena passa attraverso un obiettivo e viene focalizzata su un sensore CMOS](../../../../../translated_images/it/cmos-sensor.75f9cd74decb1371.webp)

La maggior parte dei sensori delle fotocamere utilizza sensori di immagine in cui ogni pixel è un fotodiodo. Un obiettivo focalizza l'immagine sul sensore di immagine, e migliaia o milioni di fotodiodi rilevano la luce che cade su ciascuno di essi, registrandola come dati pixel.

> 💁 Gli obiettivi invertono le immagini, il sensore della fotocamera le ribalta nuovamente nel verso corretto. Lo stesso accade nei tuoi occhi: ciò che vedi viene rilevato capovolto sul retro del tuo occhio e il tuo cervello lo corregge.

> 🎓 Il sensore di immagine è noto come sensore a pixel attivi (APS), e il tipo più popolare di APS è un sensore a semiconduttore a ossido di metallo complementare, o CMOS. Potresti aver sentito il termine sensore CMOS usato per i sensori delle fotocamere.

I sensori delle fotocamere sono sensori digitali, che inviano dati immagine come dati digitali, solitamente con l'aiuto di una libreria che fornisce la comunicazione. Le fotocamere si collegano utilizzando protocolli come SPI per consentire loro di inviare grandi quantità di dati: le immagini sono sostanzialmente più grandi rispetto ai singoli numeri di un sensore come un sensore di temperatura.

✅ Quali sono le limitazioni relative alla dimensione delle immagini con i dispositivi IoT? Pensa ai vincoli, soprattutto sull'hardware dei microcontrollori.

## Catturare un'immagine con un dispositivo IoT

Puoi utilizzare il tuo dispositivo IoT per catturare un'immagine da classificare.

### Attività - catturare un'immagine con un dispositivo IoT

Segui la guida pertinente per catturare un'immagine utilizzando il tuo dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Computer a scheda singola - Raspberry Pi](pi-camera.md)
* [Computer a scheda singola - Dispositivo virtuale](virtual-device-camera.md)

## Pubblicare il tuo classificatore di immagini

Hai addestrato il tuo classificatore di immagini nella lezione precedente. Prima di poterlo utilizzare dal tuo dispositivo IoT, devi pubblicare il modello.

### Iterazioni del modello

Quando il tuo modello è stato addestrato nella lezione precedente, potresti aver notato che la scheda **Performance** mostra le iterazioni sul lato. Quando hai addestrato il modello per la prima volta, avresti visto *Iterazione 1* durante l'addestramento. Quando hai migliorato il modello utilizzando le immagini di previsione, avresti visto *Iterazione 2* durante l'addestramento.

Ogni volta che addestri il modello, ottieni una nuova iterazione. Questo è un modo per tenere traccia delle diverse versioni del tuo modello addestrate su diversi set di dati. Quando esegui un **Quick Test**, c'è un menu a tendina che puoi utilizzare per selezionare l'iterazione, così puoi confrontare i risultati tra più iterazioni.

Quando sei soddisfatto di un'iterazione, puoi pubblicarla per renderla disponibile per essere utilizzata da applicazioni esterne. In questo modo puoi avere una versione pubblicata che viene utilizzata dai tuoi dispositivi, quindi lavorare su una nuova versione attraverso più iterazioni e pubblicarla una volta che sei soddisfatto.

### Attività - pubblicare un'iterazione

Le iterazioni vengono pubblicate dal portale Custom Vision.

1. Avvia il portale Custom Vision su [CustomVision.ai](https://customvision.ai) e accedi se non lo hai già aperto. Quindi apri il tuo progetto `fruit-quality-detector`.

1. Seleziona la scheda **Performance** dalle opzioni in alto.

1. Seleziona l'ultima iterazione dall'elenco *Iterations* sul lato.

1. Seleziona il pulsante **Publish** per l'iterazione.

    ![Il pulsante di pubblicazione](../../../../../translated_images/it/custom-vision-publish-button.b7174e1977b0c33b.webp)

1. Nella finestra di dialogo *Publish Model*, imposta la *Prediction resource* sulla risorsa `fruit-quality-detector-prediction` che hai creato nella lezione precedente. Lascia il nome come `Iteration2` e seleziona il pulsante **Publish**.

1. Una volta pubblicato, seleziona il pulsante **Prediction URL**. Questo mostrerà i dettagli dell'API di previsione, e avrai bisogno di questi per chiamare il modello dal tuo dispositivo IoT. La sezione inferiore è etichettata *If you have an image file*, e questi sono i dettagli che ti servono. Prendi una copia dell'URL mostrato, che sarà qualcosa come:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Dove `<location>` sarà la posizione che hai utilizzato quando hai creato la tua risorsa Custom Vision, e `<id>` sarà un lungo ID composto da lettere e numeri.

    Prendi anche una copia del valore *Prediction-Key*. Questa è una chiave sicura che devi passare quando chiami il modello. Solo le applicazioni che passano questa chiave sono autorizzate a utilizzare il modello, tutte le altre applicazioni vengono rifiutate.

    ![La finestra di dialogo dell'API di previsione che mostra l'URL e la chiave](../../../../../translated_images/it/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Quando viene pubblicata una nuova iterazione, avrà un nome diverso. Come pensi che potresti cambiare l'iterazione che un dispositivo IoT sta utilizzando?

## Classificare immagini dal tuo dispositivo IoT

Ora puoi utilizzare questi dettagli di connessione per chiamare il classificatore di immagini dal tuo dispositivo IoT.

### Attività - classificare immagini dal tuo dispositivo IoT

Segui la guida pertinente per classificare immagini utilizzando il tuo dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Computer a scheda singola - Raspberry Pi/Dispositivo IoT virtuale](single-board-computer-classify-image.md)

## Migliorare il modello

Potresti scoprire che i risultati che ottieni utilizzando la fotocamera collegata al tuo dispositivo IoT non corrispondono a ciò che ti aspetteresti. Le previsioni non sono sempre accurate come quando utilizzi immagini caricate dal tuo computer. Questo accade perché il modello è stato addestrato su dati diversi rispetto a quelli utilizzati per le previsioni.

Per ottenere i migliori risultati da un classificatore di immagini, è necessario addestrare il modello con immagini il più simili possibile a quelle utilizzate per le previsioni. Se, ad esempio, hai utilizzato la fotocamera del tuo telefono per catturare immagini per l'addestramento, la qualità dell'immagine, la nitidezza e il colore saranno diversi rispetto a una fotocamera collegata a un dispositivo IoT.

![2 immagini di banane, una a bassa risoluzione con scarsa illuminazione da un dispositivo IoT e una ad alta risoluzione con buona illuminazione da un telefono](../../../../../translated_images/it/banana-picture-compare.174df164dc326a42.webp)

Nell'immagine sopra, la foto della banana a sinistra è stata scattata utilizzando una fotocamera Raspberry Pi, quella a destra è stata scattata della stessa banana nello stesso luogo utilizzando un iPhone. C'è una differenza evidente nella qualità: la foto dell'iPhone è più nitida, con colori più brillanti e maggiore contrasto.

✅ Cos'altro potrebbe causare previsioni errate per le immagini catturate dal tuo dispositivo IoT? Pensa all'ambiente in cui potrebbe essere utilizzato un dispositivo IoT, quali fattori possono influenzare l'immagine catturata?

Per migliorare il modello, puoi riaddestrarlo utilizzando le immagini catturate dal dispositivo IoT.

### Attività - migliorare il modello

1. Classifica più immagini di frutta matura e acerba utilizzando il tuo dispositivo IoT.

1. Nel portale Custom Vision, riaddestra il modello utilizzando le immagini nella scheda *Predictions*.

    > ⚠️ Puoi fare riferimento [alle istruzioni per riaddestrare il tuo classificatore nella lezione 1 se necessario](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Se le tue immagini appaiono molto diverse da quelle originali utilizzate per l'addestramento, puoi eliminare tutte le immagini originali selezionandole nella scheda *Training Images* e selezionando il pulsante **Delete**. Per selezionare un'immagine, sposta il cursore su di essa e apparirà un segno di spunta, seleziona quel segno di spunta per selezionare o deselezionare l'immagine.

1. Addestra una nuova iterazione del modello e pubblicala utilizzando i passaggi sopra.

1. Aggiorna l'URL dell'endpoint nel tuo codice e riesegui l'app.

1. Ripeti questi passaggi finché non sei soddisfatto dei risultati delle previsioni.

---

## 🚀 Sfida

Quanto influiscono la risoluzione dell'immagine o l'illuminazione sulla previsione?

Prova a cambiare la risoluzione delle immagini nel codice del tuo dispositivo e verifica se fa la differenza nella qualità delle immagini. Prova anche a cambiare l'illuminazione.

Se dovessi creare un dispositivo di produzione da vendere a fattorie o fabbriche, come garantiresti risultati costanti tutto il tempo?

## Quiz finale

[Quiz finale](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Revisione e studio autonomo

Hai addestrato il tuo modello Custom Vision utilizzando il portale. Questo si basa sulla disponibilità di immagini - e nel mondo reale potresti non essere in grado di ottenere dati di addestramento che corrispondano a ciò che la fotocamera del tuo dispositivo cattura. Puoi aggirare questo problema addestrando direttamente dal tuo dispositivo utilizzando l'API di addestramento, per addestrare un modello utilizzando immagini catturate dal tuo dispositivo IoT.

* Leggi l'API di addestramento nella [guida introduttiva all'uso del Custom Vision SDK](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Compito

[Rispondi ai risultati della classificazione](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione AI [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatizzate possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.