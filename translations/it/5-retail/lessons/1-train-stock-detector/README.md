# Addestrare un rilevatore di scorte

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-19.cf6973cecadf080c.webp)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questo video offre una panoramica del rilevamento di oggetti con il servizio Azure Custom Vision, un servizio che verrà trattato in questa lezione.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Clicca sull'immagine sopra per guardare il video

## Quiz pre-lezione

[Quiz pre-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Introduzione

Nel progetto precedente, hai utilizzato l'IA per addestrare un classificatore di immagini - un modello che può determinare se un'immagine contiene qualcosa, come frutta matura o acerba. Un altro tipo di modello IA che può essere utilizzato con le immagini è il rilevamento di oggetti. Questi modelli non classificano un'immagine tramite tag, ma sono addestrati a riconoscere oggetti e possono trovarli nelle immagini, non solo rilevando che l'oggetto è presente, ma anche individuando dove si trova nell'immagine. Questo consente di contare gli oggetti nelle immagini.

In questa lezione imparerai il rilevamento di oggetti, incluso come può essere utilizzato nel settore retail. Imparerai anche come addestrare un rilevatore di oggetti nel cloud.

In questa lezione tratteremo:

* [Rilevamento di oggetti](../../../../../5-retail/lessons/1-train-stock-detector)
* [Utilizzare il rilevamento di oggetti nel retail](../../../../../5-retail/lessons/1-train-stock-detector)
* [Addestrare un rilevatore di oggetti](../../../../../5-retail/lessons/1-train-stock-detector)
* [Testare il tuo rilevatore di oggetti](../../../../../5-retail/lessons/1-train-stock-detector)
* [Riaddestrare il tuo rilevatore di oggetti](../../../../../5-retail/lessons/1-train-stock-detector)

## Rilevamento di oggetti

Il rilevamento di oggetti consiste nel rilevare oggetti nelle immagini utilizzando l'IA. A differenza del classificatore di immagini che hai addestrato nel progetto precedente, il rilevamento di oggetti non riguarda la previsione del miglior tag per un'immagine nel suo complesso, ma il riconoscimento di uno o più oggetti in un'immagine.

### Rilevamento di oggetti vs classificazione di immagini

La classificazione di immagini riguarda la classificazione di un'immagine nel suo complesso - quali sono le probabilità che l'intera immagine corrisponda a ciascun tag. Ottieni indietro le probabilità per ogni tag utilizzato per addestrare il modello.

![Classificazione di immagini di anacardi e concentrato di pomodoro](../../../../../translated_images/it/image-classifier-cashews-tomato.bc2e16ab8f05cf9a.webp)

Nell'esempio sopra, due immagini sono classificate utilizzando un modello addestrato per classificare contenitori di anacardi o lattine di concentrato di pomodoro. La prima immagine è un contenitore di anacardi e ha due risultati dal classificatore di immagini:

| Tag            | Probabilità |
| -------------- | ----------: |
| `anacardi`     | 98.4%       |
| `concentrato di pomodoro` | 1.6%        |

La seconda immagine è una lattina di concentrato di pomodoro, e i risultati sono:

| Tag            | Probabilità |
| -------------- | ----------: |
| `anacardi`     | 0.7%        |
| `concentrato di pomodoro` | 99.3%       |

Potresti utilizzare questi valori con una percentuale di soglia per prevedere cosa c'è nell'immagine. Ma cosa succede se un'immagine contiene più lattine di concentrato di pomodoro, o sia anacardi che concentrato di pomodoro? I risultati probabilmente non ti daranno ciò che desideri. È qui che entra in gioco il rilevamento di oggetti.

Il rilevamento di oggetti consiste nell'addestrare un modello a riconoscere oggetti. Invece di fornire immagini contenenti l'oggetto e dire che ogni immagine è un tag o un altro, evidenzi la sezione di un'immagine che contiene l'oggetto specifico e la tagghi. Puoi taggare un singolo oggetto in un'immagine o più oggetti. In questo modo il modello impara come appare l'oggetto stesso, non solo come appaiono le immagini che contengono l'oggetto.

Quando lo utilizzi per prevedere immagini, invece di ottenere un elenco di tag e percentuali, ottieni un elenco di oggetti rilevati, con il loro riquadro di delimitazione e la probabilità che l'oggetto corrisponda al tag assegnato.

> 🎓 *Riquadri di delimitazione* sono i riquadri intorno a un oggetto.

![Rilevamento di oggetti di anacardi e concentrato di pomodoro](../../../../../translated_images/it/object-detector-cashews-tomato.1af7c26686b4db0e.webp)

L'immagine sopra contiene sia un contenitore di anacardi che tre lattine di concentrato di pomodoro. Il rilevatore di oggetti ha rilevato gli anacardi, restituendo il riquadro di delimitazione che contiene gli anacardi con la percentuale di probabilità che il riquadro di delimitazione contenga l'oggetto, in questo caso 97.6%. Il rilevatore di oggetti ha anche rilevato tre lattine di concentrato di pomodoro e fornisce tre riquadri di delimitazione separati, uno per ogni lattina rilevata, e ciascuno ha una probabilità percentuale che il riquadro di delimitazione contenga una lattina di concentrato di pomodoro.

✅ Pensa a diversi scenari in cui potresti voler utilizzare modelli IA basati su immagini. Quali richiederebbero la classificazione e quali il rilevamento di oggetti?

### Come funziona il rilevamento di oggetti

Il rilevamento di oggetti utilizza modelli di ML complessi. Questi modelli funzionano suddividendo l'immagine in più celle, quindi verificano se il centro del riquadro di delimitazione è il centro di un'immagine che corrisponde a una delle immagini utilizzate per addestrare il modello. Puoi pensarlo come una sorta di classificatore di immagini che analizza diverse parti dell'immagine per cercare corrispondenze.

> 💁 Questa è una semplificazione drastica. Esistono molte tecniche per il rilevamento di oggetti, e puoi leggere di più su di esse nella [pagina sul rilevamento di oggetti su Wikipedia](https://wikipedia.org/wiki/Object_detection).

Esistono diversi modelli che possono eseguire il rilevamento di oggetti. Un modello particolarmente famoso è [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), che è incredibilmente veloce e può rilevare 20 diverse classi di oggetti, come persone, cani, bottiglie e automobili.

✅ Leggi di più sul modello YOLO su [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

I modelli di rilevamento di oggetti possono essere riaddestrati utilizzando il transfer learning per rilevare oggetti personalizzati.

## Utilizzare il rilevamento di oggetti nel retail

Il rilevamento di oggetti ha molteplici utilizzi nel settore retail. Alcuni includono:

* **Controllo e conteggio delle scorte** - riconoscere quando le scorte sono basse sugli scaffali. Se le scorte sono troppo basse, possono essere inviate notifiche al personale o ai robot per rifornire gli scaffali.
* **Rilevamento delle mascherine** - nei negozi con politiche sulle mascherine durante eventi di salute pubblica, il rilevamento di oggetti può riconoscere persone con mascherine e senza.
* **Fatturazione automatizzata** - rilevare gli articoli prelevati dagli scaffali nei negozi automatizzati e fatturare i clienti in modo appropriato.
* **Rilevamento di pericoli** - riconoscere oggetti rotti sul pavimento o liquidi versati, avvisando le squadre di pulizia.

✅ Fai una ricerca: Quali sono altri casi d'uso per il rilevamento di oggetti nel retail?

## Addestrare un rilevatore di oggetti

Puoi addestrare un rilevatore di oggetti utilizzando Custom Vision, in modo simile a come hai addestrato un classificatore di immagini.

### Attività - creare un rilevatore di oggetti

1. Crea un gruppo di risorse per questo progetto chiamato `stock-detector`.

1. Crea una risorsa di addestramento Custom Vision gratuita e una risorsa di previsione Custom Vision gratuita nel gruppo di risorse `stock-detector`. Nominale `stock-detector-training` e `stock-detector-prediction`.

    > 💁 Puoi avere solo una risorsa di addestramento e previsione gratuita, quindi assicurati di aver eliminato il progetto dalle lezioni precedenti.

    > ⚠️ Puoi fare riferimento alle [istruzioni per creare risorse di addestramento e previsione dal progetto 4, lezione 1 se necessario](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Avvia il portale Custom Vision su [CustomVision.ai](https://customvision.ai) e accedi con l'account Microsoft che hai utilizzato per il tuo account Azure.

1. Segui la [sezione Crea un nuovo progetto del quickstart per costruire un rilevatore di oggetti sulla documentazione Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) per creare un nuovo progetto Custom Vision. L'interfaccia utente potrebbe cambiare e questa documentazione è sempre la più aggiornata.

    Chiama il tuo progetto `stock-detector`.

    Quando crei il tuo progetto, assicurati di utilizzare la risorsa `stock-detector-training` che hai creato in precedenza. Usa il tipo di progetto *Object Detection* e il dominio *Products on Shelves*.

    ![Le impostazioni per il progetto Custom Vision con il nome impostato su fruit-quality-detector, nessuna descrizione, la risorsa impostata su fruit-quality-detector-training, il tipo di progetto impostato su classificazione, i tipi di classificazione impostati su multi class e i domini impostati su food](../../../../../translated_images/it/custom-vision-create-object-detector-project.32d4fb9aa8e7e737.webp)

    ✅ Il dominio "Products on Shelves" è specificamente mirato al rilevamento di scorte sugli scaffali dei negozi. Leggi di più sui diversi domini nella [documentazione Seleziona un dominio su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection)

✅ Prenditi del tempo per esplorare l'interfaccia utente di Custom Vision per il tuo rilevatore di oggetti.

### Attività - addestrare il tuo rilevatore di oggetti

Per addestrare il tuo modello avrai bisogno di un set di immagini contenenti gli oggetti che vuoi rilevare.

1. Raccogli immagini che contengano l'oggetto da rilevare. Avrai bisogno di almeno 15 immagini contenenti ciascun oggetto da rilevare da una varietà di angolazioni diverse e in condizioni di illuminazione diverse, ma più immagini hai, meglio è. Questo rilevatore di oggetti utilizza il dominio *Products on Shelves*, quindi cerca di posizionare gli oggetti come se fossero su uno scaffale di un negozio. Avrai anche bisogno di alcune immagini per testare il modello. Se stai rilevando più di un oggetto, vorrai alcune immagini di test che contengano tutti gli oggetti.

    > 💁 Le immagini con più oggetti diversi contano per il minimo di 15 immagini per tutti gli oggetti nell'immagine.

    Le tue immagini dovrebbero essere png o jpeg, più piccole di 6MB. Se le crei con un iPhone, ad esempio, potrebbero essere immagini HEIC ad alta risoluzione, quindi dovranno essere convertite e possibilmente ridotte. Più immagini hai, meglio è, e dovresti avere un numero simile di oggetti maturi e acerbi.

    Il modello è progettato per prodotti sugli scaffali, quindi cerca di scattare le foto degli oggetti sugli scaffali.

    Puoi trovare alcune immagini di esempio che puoi utilizzare nella cartella [images](../../../../../5-retail/lessons/1-train-stock-detector/images) di anacardi e concentrato di pomodoro che puoi utilizzare.

1. Segui la [sezione Carica e tagga immagini del quickstart per costruire un rilevatore di oggetti sulla documentazione Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) per caricare le tue immagini di addestramento. Crea tag pertinenti a seconda dei tipi di oggetti che vuoi rilevare.

    ![I dialoghi di caricamento che mostrano il caricamento di immagini di banane mature e acerbe](../../../../../translated_images/it/image-upload-object-detector.77c7892c3093cb59.webp)

    Quando disegni i riquadri di delimitazione per gli oggetti, tienili ben stretti intorno all'oggetto. Può richiedere del tempo per delineare tutte le immagini, ma lo strumento rileverà ciò che pensa siano i riquadri di delimitazione, rendendo il processo più veloce.

    ![Taggando del concentrato di pomodoro](../../../../../translated_images/it/object-detector-tag-tomato-paste.f47c362fb0f0eb58.webp)

    > 💁 Se hai più di 15 immagini per ciascun oggetto, puoi addestrare dopo 15 e utilizzare la funzione **Tag suggeriti**. Questo utilizzerà il modello addestrato per rilevare gli oggetti nell'immagine non taggata. Puoi quindi confermare gli oggetti rilevati o rifiutare e ridisegnare i riquadri di delimitazione. Questo può risparmiare *molto* tempo.

1. Segui la [sezione Addestra il rilevatore del quickstart per costruire un rilevatore di oggetti sulla documentazione Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) per addestrare il rilevatore di oggetti sulle tue immagini taggate.

    Ti verrà data una scelta del tipo di addestramento. Seleziona **Quick Training**.

Il rilevatore di oggetti verrà quindi addestrato. Ci vorranno alcuni minuti per completare l'addestramento.

## Testare il tuo rilevatore di oggetti

Una volta che il tuo rilevatore di oggetti è stato addestrato, puoi testarlo fornendogli nuove immagini per rilevare gli oggetti.

### Attività - testare il tuo rilevatore di oggetti

1. Usa il pulsante **Quick Test** per caricare immagini di test e verificare che gli oggetti siano rilevati. Usa le immagini di test che hai creato in precedenza, non quelle utilizzate per l'addestramento.

    ![3 lattine di concentrato di pomodoro rilevate con probabilità del 38%, 35.5% e 34.6%](../../../../../translated_images/it/object-detector-detected-tomato-paste.52656fe87af4c37b.webp)

1. Prova tutte le immagini di test a tua disposizione e osserva le probabilità.

## Riaddestrare il tuo rilevatore di oggetti

Quando testi il tuo rilevatore di oggetti, potrebbe non fornire i risultati che ti aspetti, proprio come con i classificatori di immagini nel progetto precedente. Puoi migliorare il tuo rilevatore di oggetti riaddestrandolo con immagini che ha sbagliato.

Ogni volta che fai una previsione utilizzando l'opzione di test rapido, l'immagine e i risultati vengono memorizzati. Puoi utilizzare queste immagini per riaddestrare il tuo modello.

1. Usa la scheda **Predictions** per individuare le immagini che hai utilizzato per il test.

1. Conferma eventuali rilevamenti accurati, elimina quelli errati e aggiungi eventuali oggetti mancanti.

1. Riaddestra e ritesta il modello.

---

## 🚀 Sfida

Cosa accadrebbe se utilizzassi il rilevatore di oggetti con articoli dall'aspetto simile, come lattine della stessa marca di concentrato di pomodoro e pomodori a pezzi?

Se hai articoli dall'aspetto simile, testalo aggiungendo immagini di questi al tuo rilevatore di oggetti.

## Quiz post-lezione
[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Revisione e Studio Autonomo

* Quando hai addestrato il tuo rilevatore di oggetti, avrai visto valori come *Precision*, *Recall* e *mAP* che valutano il modello creato. Approfondisci cosa significano questi valori utilizzando [la sezione Valutare il rilevatore della guida rapida per creare un rilevatore di oggetti nei documenti Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Leggi di più sul rilevamento di oggetti nella [pagina sul rilevamento di oggetti su Wikipedia](https://wikipedia.org/wiki/Object_detection)

## Compito

[Confronta i domini](assignment.md)

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.