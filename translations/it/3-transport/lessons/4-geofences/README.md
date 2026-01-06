<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-25T18:00:50+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "it"
}
-->
# Georecinzioni

![Una panoramica illustrata di questa lezione](../../../../../translated_images/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.it.jpg)

> Illustrazione di [Nitya Narasimhan](https://github.com/nitya). Clicca sull'immagine per una versione più grande.

Questo video offre una panoramica sulle georecinzioni e su come utilizzarle in Azure Maps, argomenti che verranno trattati in questa lezione:

[![Georecinzioni con Azure Maps dallo show Microsoft Developer IoT](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Clicca sull'immagine sopra per guardare il video

## Quiz preliminare

[Quiz preliminare](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Introduzione

Nelle ultime 3 lezioni, hai utilizzato l'IoT per localizzare i camion che trasportano i tuoi prodotti dalla tua fattoria a un centro di lavorazione. Hai acquisito dati GPS, li hai inviati al cloud per archiviarli e li hai visualizzati su una mappa. Il prossimo passo per aumentare l'efficienza della tua catena di approvvigionamento è ricevere un avviso quando un camion sta per arrivare al centro di lavorazione, in modo che il personale necessario per lo scarico possa essere pronto con muletti e altre attrezzature non appena il veicolo arriva. In questo modo, lo scarico può avvenire rapidamente e non stai pagando un camion e un autista per aspettare.

In questa lezione imparerai cosa sono le georecinzioni - regioni geospaziali definite, come un'area entro un raggio di 2 km da un centro di lavorazione - e come verificare se le coordinate GPS si trovano all'interno o all'esterno di una georecinzione, così da sapere se il tuo sensore GPS è arrivato o ha lasciato un'area.

In questa lezione tratteremo:

* [Cosa sono le georecinzioni](../../../../../3-transport/lessons/4-geofences)
* [Definire una georecinzione](../../../../../3-transport/lessons/4-geofences)
* [Testare punti rispetto a una georecinzione](../../../../../3-transport/lessons/4-geofences)
* [Utilizzare georecinzioni con codice serverless](../../../../../3-transport/lessons/4-geofences)

> 🗑 Questa è l'ultima lezione di questo progetto, quindi dopo aver completato questa lezione e l'esercizio, non dimenticare di pulire i tuoi servizi cloud. Avrai bisogno dei servizi per completare l'esercizio, quindi assicurati di completarlo prima.
>
> Consulta [la guida per pulire il tuo progetto](../../../clean-up.md) se necessario per istruzioni su come farlo.

## Cosa sono le georecinzioni

Una georecinzione è un perimetro virtuale per una regione geografica reale. Le georecinzioni possono essere cerchi definiti come un punto e un raggio (ad esempio un cerchio di 100m intorno a un edificio) o poligoni che coprono un'area come una zona scolastica, i confini di una città o un campus universitario o aziendale.

![Alcuni esempi di georecinzioni che mostrano una georecinzione circolare intorno al negozio aziendale Microsoft e una georecinzione poligonale intorno al campus ovest di Microsoft](../../../../../translated_images/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.it.png)

> 💁 Potresti aver già utilizzato le georecinzioni senza saperlo. Se hai impostato un promemoria utilizzando l'app Promemoria di iOS o Google Keep basato su una posizione, hai utilizzato una georecinzione. Queste app configurano una georecinzione basata sulla posizione fornita e ti avvisano quando il tuo telefono entra nella georecinzione.

Ci sono molte ragioni per cui potresti voler sapere se un veicolo si trova all'interno o all'esterno di una georecinzione:

* Preparazione per lo scarico - ricevere una notifica che un veicolo è arrivato sul posto consente al personale di essere pronto per scaricare il veicolo, riducendo i tempi di attesa. Questo può permettere a un autista di effettuare più consegne in un giorno con meno tempi morti.
* Conformità fiscale - alcuni paesi, come la Nuova Zelanda, applicano tasse stradali per i veicoli diesel basate sul peso del veicolo quando si guida su strade pubbliche. Utilizzare le georecinzioni consente di tracciare i chilometri percorsi su strade pubbliche rispetto a quelle private, come fattorie o aree di disboscamento.
* Monitoraggio dei furti - se un veicolo dovrebbe rimanere solo in una determinata area, come una fattoria, e lascia la georecinzione, potrebbe essere stato rubato.
* Conformità alla posizione - alcune parti di un sito di lavoro, una fattoria o una fabbrica possono essere vietate a determinati veicoli, come mantenere i veicoli che trasportano fertilizzanti artificiali e pesticidi lontani dai campi che coltivano prodotti biologici. Se una georecinzione viene attraversata, il veicolo è fuori conformità e l'autista può essere avvisato.

✅ Riesci a pensare ad altri usi per le georecinzioni?

Azure Maps, il servizio che hai utilizzato nella lezione precedente per visualizzare i dati GPS, ti consente di definire georecinzioni e verificare se un punto si trova all'interno o all'esterno della georecinzione.

## Definire una georecinzione

Le georecinzioni sono definite utilizzando GeoJSON, lo stesso formato dei punti aggiunti alla mappa nella lezione precedente. In questo caso, invece di essere una `FeatureCollection` di valori `Point`, è una `FeatureCollection` contenente un `Polygon`.

```json
{
   "type": "FeatureCollection",
   "features": [
     {
       "type": "Feature",
       "geometry": {
         "type": "Polygon",
         "coordinates": [
           [
             [
               -122.13393688201903,
               47.63829579223815
             ],
             [
               -122.13389128446579,
               47.63782047131512
             ],
             [
               -122.13240802288054,
               47.63783312249837
             ],
             [
               -122.13238388299942,
               47.63829037035086
             ],
             [
               -122.13393688201903,
               47.63829579223815
             ]
           ]
         ]
       },
       "properties": {
         "geometryId": "1"
       }
     }
   ]
}
```

Ogni punto del poligono è definito come una coppia longitudine, latitudine in un array, e questi punti sono in un array impostato come `coordinates`. In un `Point` nella lezione precedente, le `coordinates` erano un array contenente 2 valori, latitudine e longitudine; per un `Polygon` è un array di array contenenti 2 valori, longitudine e latitudine.

> 💁 Ricorda, GeoJSON utilizza `longitudine, latitudine` per i punti, non `latitudine, longitudine`.

L'array delle coordinate del poligono ha sempre 1 voce in più rispetto al numero di punti del poligono, con l'ultima voce uguale alla prima, chiudendo il poligono. Ad esempio, per un rettangolo ci sarebbero 5 punti.

![Un rettangolo con coordinate](../../../../../translated_images/polygon-points.302193da381cb415.it.png)

Nell'immagine sopra, c'è un rettangolo. Le coordinate del poligono iniziano in alto a sinistra a 47,-122, poi si spostano a destra a 47,-121, poi in basso a 46,-121, poi a sinistra a 46,-122, e infine tornano al punto di partenza a 47,-122. Questo dà al poligono 5 punti: in alto a sinistra, in alto a destra, in basso a destra, in basso a sinistra, e infine in alto a sinistra per chiuderlo.

✅ Prova a creare un poligono GeoJSON intorno alla tua casa o scuola. Usa uno strumento come [GeoJSON.io](https://geojson.io/).

### Compito - definire una georecinzione

Per utilizzare una georecinzione in Azure Maps, prima deve essere caricata nel tuo account Azure Maps. Una volta caricata, riceverai un ID univoco che puoi utilizzare per testare un punto rispetto alla georecinzione. Per caricare le georecinzioni su Azure Maps, devi utilizzare l'API web di Azure Maps. Puoi chiamare l'API web di Azure Maps utilizzando uno strumento chiamato [curl](https://curl.se).

> 🎓 Curl è uno strumento da riga di comando per effettuare richieste a endpoint web.

1. Se stai utilizzando Linux, macOS o una versione recente di Windows 10, probabilmente hai già curl installato. Esegui il seguente comando dal tuo terminale o prompt dei comandi per verificare:

    ```sh
    curl --version
    ```

    Se non vedi informazioni sulla versione di curl, dovrai installarlo dalla [pagina di download di curl](https://curl.se/download.html).

    > 💁 Se hai esperienza con Postman, puoi utilizzare quello al posto di curl, se preferisci.

1. Crea un file GeoJSON contenente un poligono. Lo testerai utilizzando il tuo sensore GPS, quindi crea un poligono intorno alla tua posizione attuale. Puoi crearlo manualmente modificando l'esempio GeoJSON fornito sopra o utilizzare uno strumento come [GeoJSON.io](https://geojson.io/).

    Il GeoJSON dovrà contenere una `FeatureCollection`, contenente una `Feature` con una `geometry` di tipo `Polygon`.

    Devi **OBBLIGATORIAMENTE** aggiungere anche un elemento `properties` allo stesso livello dell'elemento `geometry`, e questo deve contenere un `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Se utilizzi [GeoJSON.io](https://geojson.io/), dovrai aggiungere manualmente questo elemento all'elemento `properties` vuoto, o dopo aver scaricato il file JSON o nell'editor JSON dell'app.

    Questo `geometryId` deve essere univoco in questo file. Puoi caricare più georecinzioni come più `Features` nella `FeatureCollection` nello stesso file GeoJSON, purché ognuna abbia un `geometryId` diverso. I poligoni possono avere lo stesso `geometryId` se vengono caricati da un file diverso in un momento diverso.

1. Salva questo file come `geofence.json` e naviga nella directory in cui è salvato tramite il terminale o la console.

1. Esegui il seguente comando curl per creare la georecinzione:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Sostituisci `<subscription_key>` nell'URL con la chiave API del tuo account Azure Maps.

    L'URL viene utilizzato per caricare i dati della mappa tramite l'API `https://atlas.microsoft.com/mapData/upload`. La chiamata include un parametro `api-version` per specificare quale API di Azure Maps utilizzare, per consentire all'API di cambiare nel tempo mantenendo la compatibilità retroattiva. Il formato dei dati caricati è impostato su `geojson`.

    Questo eseguirà la richiesta POST all'API di caricamento e restituirà un elenco di intestazioni di risposta che include un'intestazione chiamata `location`.

    ```output
    content-type: application/json
    location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
    x-ms-azuremaps-region: West US 2
    x-content-type-options: nosniff
    strict-transport-security: max-age=31536000; includeSubDomains
    x-cache: CONFIG_NOCACHE
    date: Sat, 22 May 2021 21:34:57 GMT
    content-length: 0
    ```

    > 🎓 Quando si chiama un endpoint web, è possibile passare parametri alla chiamata aggiungendo un `?` seguito da coppie chiave-valore come `chiave=valore`, separando le coppie chiave-valore con un `&`.

1. Azure Maps non elabora immediatamente questa richiesta, quindi dovrai verificare se la richiesta di caricamento è stata completata utilizzando l'URL fornito nell'intestazione `location`. Effettua una richiesta GET a questa posizione per verificare lo stato. Dovrai aggiungere la tua chiave di sottoscrizione alla fine dell'URL `location` aggiungendo `&subscription-key=<subscription_key>` alla fine, sostituendo `<subscription_key>` con la chiave API del tuo account Azure Maps. Esegui il seguente comando:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Sostituisci `<location>` con il valore dell'intestazione `location` e `<subscription_key>` con la chiave API del tuo account Azure Maps.

1. Controlla il valore di `status` nella risposta. Se non è `Succeeded`, attendi un minuto e riprova.

1. Una volta che lo stato ritorna come `Succeeded`, guarda il valore di `resourceLocation` nella risposta. Questo contiene i dettagli sull'ID univoco (noto come UDID) per l'oggetto GeoJSON. L'UDID è il valore dopo `metadata/`, escludendo `api-version`. Ad esempio, se il `resourceLocation` fosse:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Allora l'UDID sarebbe `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Conserva una copia di questo UDID, poiché ti servirà per testare la georecinzione.

## Testare punti rispetto a una georecinzione

Una volta che il poligono è stato caricato su Azure Maps, puoi testare un punto per verificare se si trova all'interno o all'esterno della georecinzione. Puoi farlo effettuando una richiesta all'API web, passando l'UDID della georecinzione e la latitudine e longitudine del punto da testare.

Quando effettui questa richiesta, puoi anche passare un valore chiamato `searchBuffer`. Questo indica all'API Maps quanto essere accurati nel restituire i risultati. Il motivo è che il GPS non è perfettamente accurato e a volte le posizioni possono essere sbagliate di metri o più. Il valore predefinito per il search buffer è 50m, ma puoi impostare valori da 0m a 500m.

Quando i risultati vengono restituiti dalla chiamata API, una delle parti del risultato è una `distance` misurata fino al punto più vicino sul bordo della georecinzione, con un valore positivo se il punto è all'esterno della georecinzione, negativo se è all'interno. Se questa distanza è inferiore al search buffer, viene restituito il valore effettivo in metri, altrimenti il valore è 999 o -999. 999 significa che il punto è all'esterno della georecinzione di oltre il search buffer, -999 significa che è all'interno della georecinzione di oltre il search buffer.

![Una georecinzione con un search buffer di 50m intorno ad essa](../../../../../translated_images/search-buffer-and-distance.e6a79af3898183c7.it.png)

Nell'immagine sopra, la georecinzione ha un search buffer di 50m.

* Un punto al centro della georecinzione, ben all'interno del search buffer, ha una distanza di **-999**.
* Un punto ben al di fuori del search buffer ha una distanza di **999**.
* Un punto all'interno della georecinzione e all'interno del search buffer, a 6m dalla georecinzione, ha una distanza di **6m**.
* Un punto all'esterno della georecinzione e all'interno del search buffer, a 39m dalla georecinzione, ha una distanza di **39m**.

È importante conoscere la distanza dal bordo della georecinzione e combinarla con altre informazioni, come altre letture GPS, velocità e dati stradali, quando si prendono decisioni basate sulla posizione di un veicolo.

Ad esempio, immagina letture GPS che mostrano un veicolo che percorre una strada che finisce per correre accanto a una georecinzione. Se un singolo valore GPS è impreciso e colloca il veicolo all'interno della georecinzione, nonostante non ci sia accesso veicolare, allora può essere ignorato.

![Un percorso GPS che mostra un veicolo che passa accanto al campus Microsoft sulla 520, con letture GPS lungo la strada tranne una sul campus, all'interno di una georecinzione](../../../../../translated_images/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.it.png)
Nell'immagine sopra, c'è una geofence che copre una parte del campus di Microsoft. La linea rossa mostra un camion che percorre la 520, con cerchi che rappresentano le letture GPS. La maggior parte di queste letture sono accurate e si trovano lungo la 520, ma c'è una lettura imprecisa all'interno della geofence. Non è possibile che questa lettura sia corretta: non ci sono strade che permettano al camion di deviare improvvisamente dalla 520 verso il campus e poi tornare sulla 520. Il codice che verifica questa geofence dovrà considerare le letture precedenti prima di agire sui risultati del test della geofence.

✅ Quali dati aggiuntivi ti servirebbero per verificare se una lettura GPS può essere considerata corretta?

### Attività - testare punti rispetto a una geofence

1. Inizia costruendo l'URL per la query dell'API web. Il formato è:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Sostituisci `<subscription_key>` con la chiave API del tuo account Azure Maps.

    Sostituisci `<UDID>` con l'UDID della geofence dal compito precedente.

    Sostituisci `<lat>` e `<lon>` con la latitudine e la longitudine che desideri testare.

    Questo URL utilizza l'API `https://atlas.microsoft.com/spatial/geofence/json` per interrogare una geofence definita utilizzando GeoJSON. Si riferisce alla versione `1.0` dell'API. Il parametro `deviceId` è obbligatorio e dovrebbe essere il nome del dispositivo da cui provengono latitudine e longitudine.

    Il buffer di ricerca predefinito è di 50m, ma puoi modificarlo aggiungendo un parametro aggiuntivo `searchBuffer=<distance>`, impostando `<distance>` alla distanza del buffer di ricerca in metri, da 0 a 500.

1. Usa curl per effettuare una richiesta GET a questo URL:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Se ricevi un codice di risposta `BadRequest`, con un errore:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > allora il tuo GeoJSON manca della sezione `properties` con il `geometryId`. Dovrai correggere il tuo GeoJSON, quindi ripetere i passaggi sopra per ricaricarlo e ottenere un nuovo UDID.

1. La risposta conterrà un elenco di `geometries`, uno per ogni poligono definito nel GeoJSON utilizzato per creare la geofence. Ogni geometria ha 3 campi di interesse: `distance`, `nearestLat` e `nearestLon`.

    ```output
    {
        "geometries": [
            {
                "deviceId": "gps-sensor",
                "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
                "geometryId": "1",
                "distance": 999.0,
                "nearestLat": 47.645875,
                "nearestLon": -122.142713
            }
        ],
        "expiredGeofenceGeometryId": [],
        "invalidPeriodGeofenceGeometryId": []
    }
    ```

    * `nearestLat` e `nearestLon` sono la latitudine e la longitudine di un punto sul bordo della geofence più vicino alla posizione testata.

    * `distance` è la distanza dalla posizione testata al punto più vicino sul bordo della geofence. Numeri negativi indicano che il punto è all'interno della geofence, numeri positivi all'esterno. Questo valore sarà inferiore a 50 (il buffer di ricerca predefinito) o 999.

1. Ripeti questo processo più volte con posizioni all'interno e all'esterno della geofence.

## Utilizzare le geofence con codice serverless

Ora puoi aggiungere un nuovo trigger alla tua app Functions per testare i dati GPS dell'IoT Hub rispetto alla geofence.

### Gruppi di consumatori

Come ricorderai dalle lezioni precedenti, l'IoT Hub ti consente di riprodurre eventi ricevuti dall'hub ma non ancora elaborati. Ma cosa succede se si connettono più trigger? Come saprà quale trigger ha elaborato quali eventi?

La risposta è che non può! Invece, puoi definire più connessioni separate per leggere gli eventi, e ciascuna può gestire la riproduzione dei messaggi non letti. Questi sono chiamati *gruppi di consumatori*. Quando ti connetti all'endpoint, puoi specificare a quale gruppo di consumatori vuoi connetterti. Ogni componente della tua applicazione si connetterà a un gruppo di consumatori diverso.

![Un IoT Hub con 3 gruppi di consumatori che distribuiscono gli stessi messaggi a 3 diverse app Functions](../../../../../translated_images/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.it.png)

In teoria, fino a 5 applicazioni possono connettersi a ciascun gruppo di consumatori, e tutte riceveranno i messaggi quando arrivano. È una buona pratica avere una sola applicazione che accede a ciascun gruppo di consumatori per evitare l'elaborazione duplicata dei messaggi e garantire che, al riavvio, tutti i messaggi in coda vengano elaborati correttamente. Ad esempio, se lanciassi la tua app Functions localmente e la stessi eseguendo anche nel cloud, entrambe elaborerebbero i messaggi, portando a blob duplicati archiviati nell'account di archiviazione.

Se esamini il file `function.json` per il trigger dell'IoT Hub che hai creato in una lezione precedente, vedrai il gruppo di consumatori nella sezione di binding del trigger dell'event hub:

```json
"consumerGroup": "$Default"
```

Quando crei un IoT Hub, viene creato automaticamente il gruppo di consumatori `$Default`. Se desideri aggiungere un trigger aggiuntivo, puoi farlo utilizzando un nuovo gruppo di consumatori.

> 💁 In questa lezione, utilizzerai una funzione diversa per testare la geofence rispetto a quella utilizzata per archiviare i dati GPS. Questo serve a mostrare come utilizzare i gruppi di consumatori e separare il codice per renderlo più leggibile e comprensibile. In un'applicazione di produzione ci sono molti modi per architettare questo - mettendo entrambi in una funzione, utilizzando un trigger sull'account di archiviazione per eseguire una funzione che controlla la geofence, o utilizzando più funzioni. Non esiste un "modo giusto", dipende dal resto della tua applicazione e dalle tue esigenze.

### Attività - creare un nuovo gruppo di consumatori

1. Esegui il seguente comando per creare un nuovo gruppo di consumatori chiamato `geofence` per il tuo IoT Hub:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome che hai utilizzato per il tuo IoT Hub.

1. Se desideri vedere tutti i gruppi di consumatori per un IoT Hub, esegui il seguente comando:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Sostituisci `<hub_name>` con il nome che hai utilizzato per il tuo IoT Hub. Questo elencherà tutti i gruppi di consumatori.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Quando hai eseguito il monitoraggio degli eventi dell'IoT Hub in una lezione precedente, si è connesso al gruppo di consumatori `$Default`. Questo è il motivo per cui non puoi eseguire contemporaneamente il monitoraggio degli eventi e un trigger di eventi. Se desideri eseguire entrambi, puoi utilizzare altri gruppi di consumatori per tutte le tue app Functions e mantenere `$Default` per il monitoraggio degli eventi.

### Attività - creare un nuovo trigger per l'IoT Hub

1. Aggiungi un nuovo trigger di eventi dell'IoT Hub alla tua app `gps-trigger` che hai creato in una lezione precedente. Chiama questa funzione `geofence-trigger`.

    > ⚠️ Puoi fare riferimento [alle istruzioni per creare un trigger di eventi dell'IoT Hub dal progetto 2, lezione 5 se necessario](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Configura la stringa di connessione dell'IoT Hub nel file `function.json`. Il file `local.settings.json` è condiviso tra tutti i trigger nell'app Functions.

1. Aggiorna il valore di `consumerGroup` nel file `function.json` per fare riferimento al nuovo gruppo di consumatori `geofence`:

    ```json
    "consumerGroup": "geofence"
    ```

1. Avrai bisogno della chiave di sottoscrizione per il tuo account Azure Maps in questo trigger, quindi aggiungi una nuova voce al file `local.settings.json` chiamata `MAPS_KEY`.

1. Esegui l'app Functions per assicurarti che si stia connettendo ed elaborando i messaggi. Il `iot-hub-trigger` della lezione precedente verrà eseguito e caricherà anche i blob nell'archiviazione.

    > Per evitare letture GPS duplicate nell'archiviazione blob, puoi interrompere l'app Functions che hai in esecuzione nel cloud. Per farlo, usa il seguente comando:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Sostituisci `<functions_app_name>` con il nome che hai utilizzato per la tua app Functions.
    >
    > Puoi riavviarla successivamente con il seguente comando:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Sostituisci `<functions_app_name>` con il nome che hai utilizzato per la tua app Functions.

### Attività - testare la geofence dal trigger

In una lezione precedente hai utilizzato curl per interrogare una geofence e verificare se un punto si trovava all'interno o all'esterno. Puoi effettuare una richiesta web simile all'interno del tuo trigger.

1. Per interrogare la geofence, hai bisogno del suo UDID. Aggiungi una nuova voce al file `local.settings.json` chiamata `GEOFENCE_UDID` con questo valore.

1. Apri il file `__init__.py` dal nuovo trigger `geofence-trigger`.

1. Aggiungi il seguente import all'inizio del file:

    ```python
    import json
    import os
    import requests
    ```

    Il pacchetto `requests` ti consente di effettuare chiamate API web. Azure Maps non ha un SDK per Python, quindi devi effettuare chiamate API web per utilizzarlo dal codice Python.

1. Aggiungi le seguenti 2 righe all'inizio del metodo `main` per ottenere la chiave di sottoscrizione di Maps:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. All'interno del ciclo `for event in events`, aggiungi il seguente codice per ottenere latitudine e longitudine da ciascun evento:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Questo codice converte il JSON dal corpo dell'evento in un dizionario, quindi estrae `lat` e `lon` dal campo `gps`.

1. Quando utilizzi `requests`, invece di costruire un URL lungo come hai fatto con curl, puoi utilizzare solo la parte dell'URL e passare i parametri come dizionario. Aggiungi il seguente codice per definire l'URL da chiamare e configurare i parametri:

    ```python
    url = 'https://atlas.microsoft.com/spatial/geofence/json'

    params = {
        'api-version': 1.0,
        'deviceId': 'gps-sensor',
        'subscription-key': maps_key,
        'udid' : geofence_udid,
        'lat' : lat,
        'lon' : lon
    }
    ```

    Gli elementi nel dizionario `params` corrisponderanno alle coppie chiave-valore che hai utilizzato quando hai chiamato l'API web tramite curl.

1. Aggiungi le seguenti righe di codice per chiamare l'API web:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Questo chiama l'URL con i parametri e ottiene un oggetto di risposta.

1. Aggiungi il seguente codice sotto questo:

    ```python
    distance = response_body['geometries'][0]['distance']

    if distance == 999:
        logging.info('Point is outside geofence')
    elif distance > 0:
        logging.info(f'Point is just outside geofence by a distance of {distance}m')
    elif distance == -999:
        logging.info(f'Point is inside geofence')
    else:
        logging.info(f'Point is just inside geofence by a distance of {distance}m')
    ```

    Questo codice presume 1 geometria e estrae la distanza da quella singola geometria. Quindi registra messaggi diversi in base alla distanza.

1. Esegui questo codice. Vedrai nell'output dei log se le coordinate GPS sono all'interno o all'esterno della geofence, con una distanza se il punto si trova entro 50m. Prova questo codice con geofence diverse in base alla posizione del tuo sensore GPS, prova a spostare il sensore (ad esempio collegandolo al WiFi di un telefono cellulare o utilizzando coordinate diverse sul dispositivo IoT virtuale) per vedere il cambiamento.

1. Quando sei pronto, distribuisci questo codice alla tua app Functions nel cloud. Non dimenticare di distribuire le nuove impostazioni dell'applicazione.

    > ⚠️ Puoi fare riferimento [alle istruzioni per caricare le impostazioni dell'applicazione dal progetto 2, lezione 5 se necessario](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Puoi fare riferimento [alle istruzioni per distribuire la tua app Functions dal progetto 2, lezione 5 se necessario](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Puoi trovare questo codice nella cartella [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Sfida

In questa lezione hai aggiunto una geofence utilizzando un file GeoJSON con un singolo poligono. Puoi caricare più poligoni contemporaneamente, purché abbiano valori `geometryId` diversi nella sezione `properties`.

Prova a caricare un file GeoJSON con più poligoni e adatta il tuo codice per trovare quale poligono è più vicino o contiene le coordinate GPS.

## Quiz post-lezione

[Quiz post-lezione](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Revisione e studio autonomo

* Leggi di più sulle geofence e alcuni dei loro casi d'uso sulla [pagina Geofencing di Wikipedia](https://en.wikipedia.org/wiki/Geo-fence).
* Leggi di più sull'API di geofencing di Azure Maps nella [documentazione Microsoft Azure Maps Spatial - Get Geofence](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Leggi di più sui gruppi di consumatori nella [documentazione sulle funzionalità e la terminologia di Azure Event Hubs - Event consumers](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Compito

[Invia notifiche utilizzando Twilio](assignment.md)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un esperto umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.