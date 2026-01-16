<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-25T18:08:49+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "it"
}
-->
# Visualizzare i dati di localizzazione

![Una panoramica illustrata di questa lezione](../../../../../translated_images/it/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questo video offre una panoramica di Azure Maps con IoT, un servizio che verrà trattato in questa lezione.

[![Azure Maps - La piattaforma di localizzazione aziendale di Microsoft Azure](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Clicca sull'immagine sopra per guardare il video

## Quiz preliminare alla lezione

[Quiz preliminare alla lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Introduzione

Nella lezione precedente hai imparato come ottenere dati GPS dai tuoi sensori e salvarli nel cloud in un contenitore di archiviazione utilizzando codice serverless. Ora scoprirai come visualizzare quei punti su una mappa di Azure. Imparerai a creare una mappa su una pagina web, a conoscere il formato dei dati GeoJSON e a utilizzarlo per tracciare tutti i punti GPS catturati sulla tua mappa.

In questa lezione tratteremo:

* [Cos'è la visualizzazione dei dati](../../../../../3-transport/lessons/3-visualize-location-data)
* [Servizi di mappe](../../../../../3-transport/lessons/3-visualize-location-data)
* [Creare una risorsa Azure Maps](../../../../../3-transport/lessons/3-visualize-location-data)
* [Mostrare una mappa su una pagina web](../../../../../3-transport/lessons/3-visualize-location-data)
* [Il formato GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)
* [Tracciare dati GPS su una mappa utilizzando GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Questa lezione coinvolgerà una piccola quantità di HTML e JavaScript. Se desideri approfondire lo sviluppo web utilizzando HTML e JavaScript, dai un'occhiata a [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners).

## Cos'è la visualizzazione dei dati

La visualizzazione dei dati, come suggerisce il nome, riguarda la rappresentazione visiva dei dati in modi che rendano più facile per gli esseri umani comprenderli. Di solito è associata a grafici e diagrammi, ma può essere qualsiasi modo di rappresentare i dati in forma visiva per aiutare le persone non solo a comprenderli meglio, ma anche a prendere decisioni.

Prendendo un esempio semplice: nel progetto agricolo hai catturato le letture di umidità del suolo. Una tabella di dati sull'umidità del suolo catturati ogni ora per il 1° giugno 2021 potrebbe essere simile alla seguente:

| Data             | Lettura |
| ---------------- | ------: |
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

Per un essere umano, comprendere questi dati può essere difficile. È una parete di numeri senza significato. Come primo passo per visualizzare questi dati, possono essere tracciati su un grafico a linee:

![Un grafico a linee dei dati sopra](../../../../../translated_images/it/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Questo può essere ulteriormente migliorato aggiungendo una linea per indicare quando il sistema di irrigazione automatizzato è stato attivato a una lettura di umidità del suolo di 450:

![Un grafico a linee dell'umidità del suolo con una linea a 450](../../../../../translated_images/it/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Questo grafico mostra molto rapidamente non solo quali erano i livelli di umidità del suolo, ma anche i punti in cui il sistema di irrigazione è stato attivato.

I grafici non sono l'unico strumento per visualizzare i dati. I dispositivi IoT che monitorano il meteo possono avere app web o mobili che visualizzano le condizioni meteorologiche utilizzando simboli, come un'icona di nuvola per giorni nuvolosi, un'icona di pioggia per giorni piovosi e così via. Esistono moltissimi modi per visualizzare i dati, alcuni seri, altri divertenti.

✅ Pensa ai modi in cui hai visto i dati visualizzati. Quali metodi sono stati i più chiari e ti hanno permesso di prendere decisioni più velocemente?

Le migliori visualizzazioni permettono agli esseri umani di prendere decisioni rapidamente. Ad esempio, avere una parete di indicatori che mostrano ogni tipo di lettura da macchinari industriali è difficile da elaborare, ma una luce rossa lampeggiante quando qualcosa va storto permette a una persona di prendere una decisione. A volte la migliore visualizzazione è una luce lampeggiante!

Quando si lavora con dati GPS, la visualizzazione più chiara può essere quella di tracciare i dati su una mappa. Una mappa che mostra i camion di consegna, ad esempio, può aiutare i lavoratori in un impianto di lavorazione a vedere quando i camion arriveranno. Se questa mappa mostra non solo immagini dei camion nelle loro posizioni attuali, ma anche informazioni sul contenuto di un camion, allora i lavoratori dell'impianto possono pianificare di conseguenza - se vedono un camion refrigerato vicino, sanno di dover preparare spazio in un frigorifero.

## Servizi di mappe

Lavorare con le mappe è un esercizio interessante, e ce ne sono molte tra cui scegliere, come Bing Maps, Leaflet, Open Street Maps e Google Maps. In questa lezione, imparerai a conoscere [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) e come possono visualizzare i tuoi dati GPS.

![Il logo di Azure Maps](../../../../../translated_images/it/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps è "una raccolta di servizi geospaziali e SDK che utilizzano dati di mappatura aggiornati per fornire contesto geografico alle applicazioni web e mobili." Ai sviluppatori vengono forniti strumenti per creare mappe belle e interattive che possono fare cose come fornire percorsi di traffico consigliati, informazioni sugli incidenti stradali, navigazione interna, capacità di ricerca, informazioni sull'elevazione, servizi meteorologici e altro.

✅ Sperimenta con alcuni [esempi di codice per mappe](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Puoi visualizzare le mappe come una tela vuota, immagini satellitari, immagini satellitari con strade sovrapposte, vari tipi di mappe in scala di grigi, mappe con rilievo ombreggiato per mostrare l'elevazione, mappe in modalità notturna e una mappa ad alto contrasto. Puoi ottenere aggiornamenti in tempo reale sulle tue mappe integrandole con [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Puoi controllare il comportamento e l'aspetto delle tue mappe abilitando vari controlli per permettere alla mappa di reagire a eventi come pizzicare, trascinare e cliccare. Per controllare l'aspetto della tua mappa, puoi aggiungere livelli che includono bolle, linee, poligoni, mappe di calore e altro. Lo stile di mappa che implementi dipende dalla tua scelta di SDK.

Puoi accedere alle API di Azure Maps utilizzando la sua [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), il suo [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), o, se stai costruendo un'app mobile, il suo [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

In questa lezione, utilizzerai il Web SDK per disegnare una mappa e visualizzare il percorso della posizione GPS del tuo sensore.

## Creare una risorsa Azure Maps

Il primo passo è creare un account Azure Maps.

### Attività - creare una risorsa Azure Maps

1. Esegui il seguente comando dal tuo Terminale o Prompt dei comandi per creare una risorsa Azure Maps nel tuo gruppo di risorse `gps-sensor`:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Questo creerà una risorsa Azure Maps chiamata `gps-sensor`. Il livello utilizzato è `S1`, che è un livello a pagamento che include una gamma di funzionalità, ma con un generoso numero di chiamate gratuite.

    > 💁 Per vedere il costo di utilizzo di Azure Maps, consulta la [pagina dei prezzi di Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Avrai bisogno di una chiave API per la risorsa delle mappe. Usa il seguente comando per ottenere questa chiave:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Prendi una copia del valore `PrimaryKey`.

## Mostrare una mappa su una pagina web

Ora puoi fare il passo successivo, ovvero visualizzare la tua mappa su una pagina web. Utilizzeremo solo un file `html` per la tua piccola app web; tieni presente che in un ambiente di produzione o di team, la tua app web avrà probabilmente più parti in movimento!

### Attività - mostrare una mappa su una pagina web

1. Crea un file chiamato index.html in una cartella sul tuo computer locale. Aggiungi il markup HTML per contenere una mappa:

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    La mappa verrà caricata nel `div` `myMap`. Alcuni stili permettono di farla occupare la larghezza e l'altezza della pagina.

    > 🎓 un `div` è una sezione di una pagina web che può essere nominata e stilizzata.

1. Sotto il tag di apertura `<head>`, aggiungi un foglio di stile esterno per controllare la visualizzazione della mappa e uno script esterno dal Web SDK per gestirne il comportamento:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Questo foglio di stile contiene le impostazioni per l'aspetto della mappa, e il file script contiene il codice per caricare la mappa. Aggiungere questo codice è simile a includere file di intestazione C++ o importare moduli Python.

1. Sotto quello script, aggiungi un blocco di script per avviare la mappa.

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    Sostituisci `<subscription_key>` con la chiave API per il tuo account Azure Maps.

    Se apri la tua pagina `index.html` in un browser web, dovresti vedere una mappa caricata, focalizzata sull'area di Seattle.

    ![Una mappa che mostra Seattle, una città nello stato di Washington, USA](../../../../../translated_images/it/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Sperimenta con i parametri di zoom e centro per modificare la visualizzazione della tua mappa. Puoi aggiungere diverse coordinate corrispondenti alla latitudine e longitudine dei tuoi dati per ricentrare la mappa.

> 💁 Un modo migliore per lavorare con app web localmente è installare [http-server](https://www.npmjs.com/package/http-server). Avrai bisogno di [node.js](https://nodejs.org/) e [npm](https://www.npmjs.com/) installati prima di utilizzare questo strumento. Una volta installati questi strumenti, puoi navigare nella posizione del tuo file `index.html` e digitare `http-server`. L'app web si aprirà su un server web locale [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## Il formato GeoJSON

Ora che hai la tua app web in funzione con la mappa visualizzata, devi estrarre i dati GPS dal tuo account di archiviazione e visualizzarli in un livello di marcatori sopra la mappa. Prima di farlo, diamo un'occhiata al formato [GeoJSON](https://wikipedia.org/wiki/GeoJSON) richiesto da Azure Maps.

[GeoJSON](https://geojson.org/) è uno standard aperto di specifica JSON con una formattazione speciale progettata per gestire dati specifici geografici. Puoi imparare a conoscerlo testando dati di esempio utilizzando [geojson.io](https://geojson.io), che è anche uno strumento utile per il debug dei file GeoJSON.

Un esempio di dati GeoJSON appare così:

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [
          -2.10237979888916,
          57.164918677004714
        ]
      }
    }
  ]
}
```

Di particolare interesse è il modo in cui i dati sono nidificati come `Feature` all'interno di una `FeatureCollection`. All'interno di quell'oggetto si trova `geometry` con le `coordinates` che indicano latitudine e longitudine.

✅ Quando costruisci il tuo geoJSON, presta attenzione all'ordine di `latitude` e `longitude` nell'oggetto, o i tuoi punti non appariranno dove dovrebbero! GeoJSON si aspetta dati nell'ordine `lon,lat` per i punti, non `lat,lon`.

`Geometry` può avere diversi tipi, come un singolo punto o un poligono. In questo esempio, è un punto con due coordinate specificate, la longitudine e la latitudine.
✅ Azure Maps supporta GeoJSON standard più alcune [funzionalità avanzate](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), inclusa la possibilità di disegnare cerchi e altre geometrie.

## Tracciare dati GPS su una mappa utilizzando GeoJSON

Ora sei pronto per utilizzare i dati dallo storage che hai creato nella lezione precedente. Come promemoria, i dati sono archiviati come una serie di file in un blob storage, quindi dovrai recuperare i file e analizzarli affinché Azure Maps possa utilizzarli.

### Attività - configurare lo storage per l'accesso da una pagina web

Se effettui una chiamata al tuo storage per recuperare i dati, potresti essere sorpreso di vedere errori nella console del browser. Questo accade perché devi impostare i permessi per [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) su questo storage per consentire alle app web esterne di leggere i suoi dati.

> 🎓 CORS sta per "Cross-Origin Resource Sharing" e di solito deve essere configurato esplicitamente in Azure per motivi di sicurezza. Impedisce a siti non autorizzati di accedere ai tuoi dati.

1. Esegui il seguente comando per abilitare CORS:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Sostituisci `<storage_name>` con il nome del tuo account di storage. Sostituisci `<key1>` con la chiave dell'account per il tuo account di storage.

    Questo comando consente a qualsiasi sito web (il carattere jolly `*` significa qualsiasi) di effettuare una richiesta *GET*, ovvero ottenere dati, dal tuo account di storage. Il parametro `--services b` significa che questa impostazione si applica solo ai blob.

### Attività - caricare i dati GPS dallo storage

1. Sostituisci l'intero contenuto della funzione `init` con il seguente codice:

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    Sostituisci `<storage_name>` con il nome del tuo account di storage. Sostituisci `<subscription_key>` con la chiave API per il tuo account Azure Maps.

    Qui accadono diverse cose. Innanzitutto, il codice recupera i tuoi dati GPS dal contenitore blob utilizzando un endpoint URL costruito con il nome del tuo account di storage. Questo URL recupera da `gps-data`, indicando che il tipo di risorsa è un contenitore (`restype=container`), e elenca informazioni su tutti i blob. Questo elenco non restituirà i blob stessi, ma restituirà un URL per ciascun blob che può essere utilizzato per caricare i dati del blob.

    > 💁 Puoi inserire questo URL nel tuo browser per vedere i dettagli di tutti i blob nel tuo contenitore. Ogni elemento avrà una proprietà `Url` che puoi anche caricare nel browser per vedere il contenuto del blob.

    Questo codice quindi carica ogni blob, chiamando una funzione `loadJSON`, che sarà creata successivamente. Successivamente, crea il controllo della mappa e aggiunge codice all'evento `ready`. Questo evento viene chiamato quando la mappa viene visualizzata sulla pagina web.

    L'evento ready crea una fonte dati di Azure Maps - un contenitore che contiene dati GeoJSON che saranno popolati successivamente. Questa fonte dati viene poi utilizzata per creare un livello di bolle - ovvero un insieme di cerchi sulla mappa centrati su ciascun punto nel GeoJSON.

1. Aggiungi la funzione `loadJSON` al tuo blocco script, sotto la funzione `init`:

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    Questa funzione viene chiamata dalla routine di fetch per analizzare i dati JSON e convertirli in coordinate di longitudine e latitudine come geoJSON. 
    Una volta analizzati, i dati vengono impostati come parte di una `Feature` geoJSON. La mappa sarà inizializzata e appariranno piccole bolle lungo il percorso tracciato dai tuoi dati:

1. Carica la pagina HTML nel tuo browser. Verrà caricata la mappa, quindi tutti i dati GPS dallo storage saranno caricati e tracciati sulla mappa.

    ![Una mappa del Saint Edward State Park vicino a Seattle, con cerchi che mostrano un percorso attorno al bordo del parco](../../../../../translated_images/it/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Puoi trovare questo codice nella [cartella del codice](../../../../../3-transport/lessons/3-visualize-location-data/code).

---

## 🚀 Sfida

È bello poter visualizzare dati statici su una mappa come marker. Puoi migliorare questa app web per aggiungere animazione e mostrare il percorso dei marker nel tempo, utilizzando i file JSON con timestamp? Ecco [alcuni esempi](https://azuremapscodesamples.azurewebsites.net/) di utilizzo dell'animazione all'interno delle mappe.

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Revisione e studio autonomo

Azure Maps è particolarmente utile per lavorare con dispositivi IoT.

* Esplora alcuni degli utilizzi nella [documentazione di Azure Maps su Microsoft docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Approfondisci le tue conoscenze sulla creazione di mappe e punti di passaggio con il [modulo di apprendimento autonomo "crea la tua prima app di ricerca percorsi con Azure Maps" su Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Compito

[Distribuisci la tua app](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.