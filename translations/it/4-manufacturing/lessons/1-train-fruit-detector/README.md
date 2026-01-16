<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-25T16:27:34+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "it"
}
-->
# Addestrare un rilevatore di qualità della frutta

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questo video offre una panoramica del servizio Azure Custom Vision, un servizio che verrà trattato in questa lezione.

[![Custom Vision – Machine Learning Made Easy | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Clicca sull'immagine sopra per guardare il video

## Quiz preliminare alla lezione

[Quiz preliminare alla lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Introduzione

La recente crescita dell'Intelligenza Artificiale (AI) e del Machine Learning (ML) sta fornendo una vasta gamma di capacità agli sviluppatori di oggi. I modelli di ML possono essere addestrati per riconoscere diversi elementi nelle immagini, inclusa la frutta acerba, e questo può essere utilizzato nei dispositivi IoT per aiutare a selezionare i prodotti sia durante la raccolta che durante la lavorazione in fabbrica o nei magazzini.

In questa lezione imparerai la classificazione delle immagini - utilizzando modelli di ML per distinguere tra immagini di cose diverse. Imparerai come addestrare un classificatore di immagini per distinguere tra frutta buona e frutta cattiva, sia acerba che troppo matura, ammaccata o marcia.

In questa lezione tratteremo:

* [Utilizzare AI e ML per selezionare il cibo](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Classificazione delle immagini tramite Machine Learning](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Addestrare un classificatore di immagini](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Testare il tuo classificatore di immagini](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Riaddestrare il tuo classificatore di immagini](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Utilizzare AI e ML per selezionare il cibo

Nutrire la popolazione globale è difficile, soprattutto a un prezzo che renda il cibo accessibile a tutti. Uno dei costi maggiori è la manodopera, quindi gli agricoltori si stanno sempre più orientando verso l'automazione e strumenti come l'IoT per ridurre i costi del lavoro. La raccolta manuale è intensiva (e spesso un lavoro faticoso), e viene sostituita da macchinari, soprattutto nei paesi più ricchi. Nonostante i risparmi nei costi derivanti dall'uso di macchinari per la raccolta, c'è un lato negativo: la capacità di selezionare il cibo durante la raccolta.

Non tutte le colture maturano uniformemente. I pomodori, ad esempio, possono avere ancora alcuni frutti verdi sulla pianta quando la maggior parte è pronta per la raccolta. Sebbene sia uno spreco raccogliere questi frutti acerbi, è più economico e facile per l'agricoltore raccogliere tutto utilizzando macchinari e smaltire successivamente i prodotti acerbi.

✅ Osserva diversi tipi di frutta o verdura, sia che crescano vicino a te in fattorie o nel tuo giardino, sia nei negozi. Sono tutti della stessa maturazione o noti variazioni?

L'ascesa della raccolta automatizzata ha spostato la selezione dei prodotti dalla raccolta alla fabbrica. Il cibo viaggiava su lunghe cinture trasportatrici con squadre di persone che selezionavano i prodotti rimuovendo tutto ciò che non soddisfaceva gli standard di qualità richiesti. La raccolta era più economica grazie ai macchinari, ma c'era ancora un costo per la selezione manuale del cibo.

![Se viene rilevato un pomodoro rosso, continua il suo percorso senza interruzioni. Se viene rilevato un pomodoro verde, viene spinto in un cestino di scarto da una leva](../../../../../translated_images/it/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.png)

L'evoluzione successiva è stata l'uso di macchine per la selezione, integrate nella mietitrice o negli impianti di lavorazione. La prima generazione di queste macchine utilizzava sensori ottici per rilevare i colori, controllando attuatori per spingere i pomodori verdi in un cestino di scarto utilizzando leve o getti d'aria, lasciando che i pomodori rossi continuassero su una rete di nastri trasportatori.

In questo video, mentre i pomodori cadono da un nastro trasportatore all'altro, i pomodori verdi vengono rilevati e spinti in un cestino utilizzando leve.

✅ Quali condizioni sarebbero necessarie in una fabbrica o in un campo affinché questi sensori ottici funzionino correttamente?

Le ultime evoluzioni di queste macchine di selezione sfruttano AI e ML, utilizzando modelli addestrati per distinguere i prodotti buoni da quelli cattivi, non solo attraverso evidenti differenze di colore come pomodori verdi contro rossi, ma anche attraverso differenze più sottili nell'aspetto che possono indicare malattie o ammaccature.

## Classificazione delle immagini tramite Machine Learning

La programmazione tradizionale consiste nel prendere dati, applicare un algoritmo ai dati e ottenere un output. Ad esempio, nel progetto precedente hai preso coordinate GPS e un geofence, applicato un algoritmo fornito da Azure Maps e ottenuto un risultato che indicava se il punto era dentro o fuori dal geofence. Inserisci più dati, ottieni più output.

![Lo sviluppo tradizionale prende input e un algoritmo e restituisce output. Il machine learning utilizza dati di input e output per addestrare un modello, e questo modello può prendere nuovi dati di input per generare nuovi output](../../../../../translated_images/it/traditional-vs-ml.5c20c169621fa539.webp)

Il machine learning ribalta questo processo: si parte dai dati e dagli output noti, e l'algoritmo di machine learning apprende dai dati. Puoi quindi prendere quell'algoritmo addestrato, chiamato *modello di machine learning* o *modello*, e inserire nuovi dati per ottenere nuovi output.

> 🎓 Il processo in cui un algoritmo di machine learning apprende dai dati è chiamato *addestramento*. Gli input e gli output noti sono chiamati *dati di addestramento*.

Ad esempio, potresti fornire a un modello milioni di immagini di banane acerbe come dati di input per l'addestramento, con l'output di addestramento impostato su `acerba`, e milioni di immagini di banane mature come dati di addestramento con l'output impostato su `matura`. L'algoritmo di ML creerà quindi un modello basato su questi dati. Successivamente, puoi fornire a questo modello una nuova immagine di una banana e il modello predirà se la nuova immagine rappresenta una banana matura o acerba.

> 🎓 I risultati dei modelli di ML sono chiamati *predizioni*

![2 banane, una matura con una predizione del 99,7% matura, 0,3% acerba, e una acerba con una predizione dell'1,4% matura, 98,6% acerba](../../../../../translated_images/it/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.png)

I modelli di ML non forniscono una risposta binaria, ma piuttosto probabilità. Ad esempio, un modello potrebbe ricevere un'immagine di una banana e predire `matura` al 99,7% e `acerba` allo 0,3%. Il tuo codice sceglierebbe quindi la predizione migliore e deciderebbe che la banana è matura.

Il modello di ML utilizzato per rilevare immagini come questa è chiamato *classificatore di immagini* - viene fornito con immagini etichettate e poi classifica nuove immagini basandosi su queste etichette.

> 💁 Questa è una semplificazione, e ci sono molti altri modi per addestrare modelli che non richiedono sempre output etichettati, come l'apprendimento non supervisionato. Se vuoi saperne di più sul ML, dai un'occhiata a [ML for beginners, un curriculum di 24 lezioni sul Machine Learning](https://aka.ms/ML-beginners).

## Addestrare un classificatore di immagini

Per addestrare con successo un classificatore di immagini, hai bisogno di milioni di immagini. Tuttavia, una volta che hai un classificatore di immagini addestrato su milioni o miliardi di immagini assortite, puoi riutilizzarlo e riaddestrarlo utilizzando un piccolo set di immagini ottenendo ottimi risultati, grazie a un processo chiamato *transfer learning*.

> 🎓 Il transfer learning è il processo di trasferire l'apprendimento da un modello di ML esistente a un nuovo modello basato su nuovi dati.

Una volta che un classificatore di immagini è stato addestrato su una vasta gamma di immagini, le sue componenti interne sono ottime nel riconoscere forme, colori e schemi. Il transfer learning consente al modello di utilizzare ciò che ha già appreso nel riconoscere parti di immagini e di applicarlo al riconoscimento di nuove immagini.

![Una volta che puoi riconoscere le forme, possono essere messe in configurazioni diverse per creare una barca o un gatto](../../../../../translated_images/it/shapes-to-images.1a309f0ea88dd66f.webp)

Puoi pensare a questo come ai libri di forme per bambini, dove una volta che puoi riconoscere un semicerchio, un rettangolo e un triangolo, puoi riconoscere una barca a vela o un gatto a seconda della configurazione di queste forme. Il classificatore di immagini può riconoscere le forme, e il transfer learning gli insegna quale combinazione crea una barca o un gatto - o una banana matura.

Esistono una vasta gamma di strumenti che possono aiutarti a fare questo, inclusi servizi basati sul cloud che possono aiutarti ad addestrare il tuo modello e utilizzarlo tramite API web.

> 💁 L'addestramento di questi modelli richiede molta potenza di calcolo, solitamente tramite unità di elaborazione grafica (GPU). Lo stesso hardware specializzato che rende i giochi sulla tua Xbox incredibili può essere utilizzato per addestrare modelli di machine learning. Utilizzando il cloud, puoi noleggiare tempo su computer potenti con GPU per addestrare questi modelli, ottenendo accesso alla potenza di calcolo necessaria solo per il tempo necessario.

## Custom Vision

Custom Vision è uno strumento basato sul cloud per l'addestramento di classificatori di immagini. Ti consente di addestrare un classificatore utilizzando solo un piccolo numero di immagini. Puoi caricare immagini tramite un portale web, un'API web o un SDK, assegnando a ogni immagine un *tag* che rappresenta la classificazione di quell'immagine. Successivamente, puoi addestrare il modello e testarlo per vedere quanto bene funziona. Una volta che sei soddisfatto del modello, puoi pubblicare versioni di esso che possono essere accessibili tramite un'API web o un SDK.

![Il logo di Azure Custom Vision](../../../../../translated_images/it/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.png)

> 💁 Puoi addestrare un modello Custom Vision con solo 5 immagini per classificazione, ma più immagini sono meglio. Puoi ottenere risultati migliori con almeno 30 immagini.

Custom Vision fa parte di una gamma di strumenti AI di Microsoft chiamati Cognitive Services. Questi sono strumenti AI che possono essere utilizzati senza alcun addestramento o con una piccola quantità di addestramento. Includono riconoscimento e traduzione vocale, comprensione del linguaggio e analisi delle immagini. Sono disponibili con un livello gratuito come servizi in Azure.

> 💁 Il livello gratuito è più che sufficiente per creare un modello, addestrarlo e utilizzarlo per il lavoro di sviluppo. Puoi leggere i limiti del livello gratuito sulla [pagina Limiti e quote di Custom Vision nei documenti Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Compito - creare una risorsa di servizi cognitivi

Per utilizzare Custom Vision, devi prima creare due risorse di servizi cognitivi in Azure utilizzando l'Azure CLI, una per l'addestramento di Custom Vision e una per la predizione di Custom Vision.

1. Crea un gruppo di risorse per questo progetto chiamato `fruit-quality-detector`.

1. Usa il seguente comando per creare una risorsa gratuita di Custom Vision per l'addestramento:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Sostituisci `<location>` con la posizione che hai utilizzato quando hai creato il gruppo di risorse.

    Questo creerà una risorsa di Custom Vision per l'addestramento nel tuo gruppo di risorse. Si chiamerà `fruit-quality-detector-training` e utilizzerà lo sku `F0`, che è il livello gratuito. L'opzione `--yes` significa che accetti i termini e le condizioni dei servizi cognitivi.

> 💁 Usa lo sku `S0` se hai già un account gratuito che utilizza uno qualsiasi dei servizi cognitivi.

1. Usa il seguente comando per creare una risorsa gratuita di Custom Vision per la predizione:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Sostituisci `<location>` con la posizione che hai utilizzato quando hai creato il gruppo di risorse.

    Questo creerà una risorsa di Custom Vision per la predizione nel tuo gruppo di risorse. Si chiamerà `fruit-quality-detector-prediction` e utilizzerà lo sku `F0`, che è il livello gratuito. L'opzione `--yes` significa che accetti i termini e le condizioni dei servizi cognitivi.

### Compito - creare un progetto di classificatore di immagini

1. Avvia il portale Custom Vision su [CustomVision.ai](https://customvision.ai) e accedi con l'account Microsoft che hai utilizzato per il tuo account Azure.

1. Segui la [sezione "creare un nuovo progetto" del quickstart per costruire un classificatore nei documenti Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) per creare un nuovo progetto Custom Vision. L'interfaccia utente potrebbe cambiare e questi documenti sono sempre la risorsa più aggiornata.

    Chiama il tuo progetto `fruit-quality-detector`.

    Quando crei il tuo progetto, assicurati di utilizzare la risorsa `fruit-quality-detector-training` che hai creato in precedenza. Usa un tipo di progetto *Classification*, un tipo di classificazione *Multiclass* e il dominio *Food*.

    ![Le impostazioni per il progetto Custom Vision con il nome impostato su fruit-quality-detector, nessuna descrizione, la risorsa impostata su fruit-quality-detector-training, il tipo di progetto impostato su classification, il tipo di classificazione impostato su multi class e il dominio impostato su food](../../../../../translated_images/it/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.png)

✅ Prenditi del tempo per esplorare l'interfaccia utente di Custom Vision per il tuo classificatore di immagini.

### Compito - addestrare il tuo progetto di classificatore di immagini

Per addestrare un classificatore di immagini, avrai bisogno di più immagini di frutta, sia di buona che di cattiva qualità, da etichettare come buona e cattiva, ad esempio una banana matura e una troppo matura.
💁 Questi classificatori possono classificare immagini di qualsiasi cosa, quindi se non hai frutta di qualità diversa a portata di mano, puoi usare due tipi diversi di frutta, oppure gatti e cani!
Idealmente, ogni immagine dovrebbe mostrare solo il frutto, con uno sfondo coerente o una varietà di sfondi. Assicurati che non ci sia nulla nello sfondo che sia specifico per distinguere frutti maturi da quelli acerbi.

> 💁 È importante non avere sfondi specifici o elementi che non siano correlati all'oggetto classificato per ogni etichetta, altrimenti il classificatore potrebbe basarsi solo sullo sfondo. C'è stato un classificatore per il cancro della pelle che è stato addestrato su nei normali e cancerosi, e quelli cancerosi avevano tutti righelli accanto per misurarne la dimensione. Si è scoperto che il classificatore era quasi al 100% accurato nell'identificare i righelli nelle immagini, non i nei cancerosi.

I classificatori di immagini funzionano a risoluzioni molto basse. Ad esempio, Custom Vision può utilizzare immagini di addestramento e previsione fino a 10240x10240, ma addestra ed esegue il modello su immagini a 227x227. Le immagini più grandi vengono ridotte a questa dimensione, quindi assicurati che l'oggetto che stai classificando occupi una parte significativa dell'immagine, altrimenti potrebbe risultare troppo piccolo nell'immagine ridotta utilizzata dal classificatore.

1. Raccogli immagini per il tuo classificatore. Avrai bisogno di almeno 5 immagini per ogni etichetta per addestrare il classificatore, ma più sono, meglio è. Avrai anche bisogno di alcune immagini aggiuntive per testare il classificatore. Queste immagini dovrebbero essere tutte diverse immagini dello stesso oggetto. Ad esempio:

    * Utilizzando 2 banane mature, scatta alcune foto di ciascuna da diverse angolazioni, facendo almeno 7 foto (5 per l'addestramento, 2 per il test), ma idealmente di più.

        ![Foto di 2 banane diverse](../../../../../translated_images/it/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.png)

    * Ripeti lo stesso processo utilizzando 2 banane acerbe.

    Dovresti avere almeno 10 immagini di addestramento, con almeno 5 mature e 5 acerbe, e 4 immagini di test, 2 mature e 2 acerbe. Le tue immagini dovrebbero essere in formato png o jpeg, di dimensioni inferiori a 6MB. Se le crei con un iPhone, ad esempio, potrebbero essere immagini HEIC ad alta risoluzione, quindi dovranno essere convertite e possibilmente ridotte. Più immagini hai, meglio è, e dovresti avere un numero simile di frutti maturi e acerbi.

    Se non hai sia frutti maturi che acerbi, puoi utilizzare frutti diversi o qualsiasi altro oggetto disponibile. Puoi anche trovare alcune immagini di esempio nella cartella [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) di banane mature e acerbe che puoi utilizzare.

1. Segui la [sezione carica e etichetta immagini del quickstart per creare un classificatore nei documenti Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) per caricare le tue immagini di addestramento. Etichetta i frutti maturi come `ripe` e quelli acerbi come `unripe`.

    ![Le finestre di dialogo di caricamento che mostrano il caricamento di immagini di banane mature e acerbe](../../../../../translated_images/it/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.png)

1. Segui la [sezione addestra il classificatore del quickstart per creare un classificatore nei documenti Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier) per addestrare il classificatore di immagini sulle immagini caricate.

    Ti verrà data una scelta sul tipo di addestramento. Seleziona **Quick Training**.

Il classificatore inizierà l'addestramento. Ci vorranno alcuni minuti per completare l'addestramento.

> 🍌 Se decidi di mangiare il tuo frutto mentre il classificatore si sta addestrando, assicurati di avere abbastanza immagini per il test prima!

## Testa il tuo classificatore di immagini

Una volta che il tuo classificatore è stato addestrato, puoi testarlo fornendogli una nuova immagine da classificare.

### Compito - testa il tuo classificatore di immagini

1. Segui la [documentazione per testare il tuo modello nei documenti Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model) per testare il tuo classificatore di immagini. Usa le immagini di test che hai creato in precedenza, non quelle utilizzate per l'addestramento.

    ![Una banana acerba prevista come acerba con una probabilità del 98,9%, matura con una probabilità dell'1,1%](../../../../../translated_images/it/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.png)

1. Prova tutte le immagini di test a tua disposizione e osserva le probabilità.

## Riaddestra il tuo classificatore di immagini

Quando testi il tuo classificatore, potrebbe non fornire i risultati che ti aspetti. I classificatori di immagini utilizzano l'apprendimento automatico per fare previsioni su ciò che è presente in un'immagine, basandosi su probabilità che determinate caratteristiche di un'immagine corrispondano a una particolare etichetta. Non comprende cosa c'è nell'immagine - non sa cosa sia una banana né capisce cosa rende una banana una banana invece di una barca. Puoi migliorare il tuo classificatore riaddestrandolo con immagini che ha classificato in modo errato.

Ogni volta che fai una previsione utilizzando l'opzione di test rapido, l'immagine e i risultati vengono memorizzati. Puoi utilizzare queste immagini per riaddestrare il tuo modello.

### Compito - riaddestra il tuo classificatore di immagini

1. Segui la [documentazione per utilizzare l'immagine prevista per l'addestramento nei documenti Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training) per riaddestrare il tuo modello, utilizzando l'etichetta corretta per ogni immagine.

1. Una volta che il tuo modello è stato riaddestrato, testalo su nuove immagini.

---

## 🚀 Sfida

Cosa pensi che accadrebbe se utilizzassi un'immagine di una fragola con un modello addestrato sulle banane, o un'immagine di una banana gonfiabile, o una persona in un costume da banana, o persino un personaggio giallo dei cartoni animati come qualcuno dei Simpson?

Prova e osserva le previsioni. Puoi trovare immagini da provare utilizzando [Bing Image search](https://www.bing.com/images/trending).

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Revisione e studio autonomo

* Quando hai addestrato il tuo classificatore, avrai visto valori per *Precision*, *Recall* e *AP* che valutano il modello creato. Leggi cosa significano questi valori utilizzando [la sezione valuta il classificatore del quickstart per creare un classificatore nei documenti Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)
* Leggi come migliorare il tuo classificatore dalla [guida per migliorare il tuo modello Custom Vision nei documenti Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)

## Compito

[Addestra il tuo classificatore per frutta e verdura multiple](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.