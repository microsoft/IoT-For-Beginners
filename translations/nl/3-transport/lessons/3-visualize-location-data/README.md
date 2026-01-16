<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-27T22:57:42+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "nl"
}
-->
# Locatiegegevens visualiseren

![Een schetsnotitie-overzicht van deze les](../../../../../translated_images/nl/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Schetsnotitie door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

Deze video geeft een overzicht van Azure Maps met IoT, een service die in deze les wordt behandeld.

[![Azure Maps - Het Microsoft Azure Enterprise Locatieplatform](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Klik op de afbeelding hierboven om de video te bekijken

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Introductie

In de vorige les heb je geleerd hoe je GPS-gegevens van je sensoren naar de cloud kunt sturen en opslaan in een opslagcontainer met behulp van serverloze code. Nu ontdek je hoe je die punten kunt visualiseren op een Azure-kaart. Je leert hoe je een kaart op een webpagina maakt, meer over het GeoJSON-gegevensformaat en hoe je dit kunt gebruiken om alle vastgelegde GPS-punten op je kaart te plotten.

In deze les behandelen we:

* [Wat is datavisualisatie](../../../../../3-transport/lessons/3-visualize-location-data)
* [Kaartservices](../../../../../3-transport/lessons/3-visualize-location-data)
* [Een Azure Maps-resource maken](../../../../../3-transport/lessons/3-visualize-location-data)
* [Een kaart weergeven op een webpagina](../../../../../3-transport/lessons/3-visualize-location-data)
* [Het GeoJSON-formaat](../../../../../3-transport/lessons/3-visualize-location-data)
* [GPS-gegevens plotten op een kaart met GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Deze les bevat een kleine hoeveelheid HTML en JavaScript. Als je meer wilt leren over webontwikkeling met HTML en JavaScript, bekijk dan [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners).

## Wat is datavisualisatie

Datavisualisatie, zoals de naam al aangeeft, gaat over het visualiseren van gegevens op manieren die het voor mensen gemakkelijker maken om te begrijpen. Het wordt meestal geassocieerd met grafieken en diagrammen, maar het is elke manier om gegevens visueel weer te geven om mensen niet alleen te helpen de gegevens beter te begrijpen, maar ook om beslissingen te nemen.

Een eenvoudig voorbeeld: in het landbouwproject heb je vochtigheidsmetingen van de bodem vastgelegd. Een tabel met bodemvochtgegevens die elk uur op 1 juni 2021 zijn vastgelegd, kan er als volgt uitzien:

| Datum            | Meting  |
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

Voor een mens kan het begrijpen van deze gegevens lastig zijn. Het is een muur van cijfers zonder betekenis. Als eerste stap om deze gegevens te visualiseren, kunnen ze worden uitgezet in een lijndiagram:

![Een lijndiagram van de bovenstaande gegevens](../../../../../translated_images/nl/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Dit kan verder worden verbeterd door een lijn toe te voegen die aangeeft wanneer het automatische bewateringssysteem werd ingeschakeld bij een bodemvochtmeting van 450:

![Een lijndiagram van bodemvocht met een lijn bij 450](../../../../../translated_images/nl/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Dit diagram laat heel snel zien niet alleen wat de bodemvochtigheidsniveaus waren, maar ook de punten waarop het bewateringssysteem werd ingeschakeld.

Grafieken zijn niet het enige hulpmiddel om gegevens te visualiseren. IoT-apparaten die het weer volgen, kunnen webapps of mobiele apps hebben die weersomstandigheden visualiseren met symbolen, zoals een wolksymbool voor bewolkte dagen, een regenwolk voor regenachtige dagen, enzovoort. Er zijn talloze manieren om gegevens te visualiseren, sommige serieus, andere leuk.

✅ Denk na over manieren waarop je gegevens hebt zien visualiseren. Welke methoden waren het duidelijkst en stelden je in staat om het snelst beslissingen te nemen?

De beste visualisaties stellen mensen in staat om snel beslissingen te nemen. Bijvoorbeeld, een muur vol meters die allerlei metingen van industriële machines weergeven, is moeilijk te verwerken, maar een knipperend rood licht wanneer er iets misgaat, stelt een mens in staat om direct actie te ondernemen. Soms is de beste visualisatie een knipperend licht!

Bij het werken met GPS-gegevens kan de duidelijkste visualisatie zijn om de gegevens op een kaart te plotten. Een kaart die bijvoorbeeld bezorgtrucks toont, kan werknemers in een verwerkingsfabriek helpen zien wanneer trucks arriveren. Als deze kaart meer toont dan alleen afbeeldingen van trucks op hun huidige locaties, maar ook informatie geeft over de inhoud van een truck, kunnen de werknemers in de fabriek dienovereenkomstig plannen - als ze een gekoelde truck dichtbij zien, weten ze dat ze ruimte in een koelkast moeten voorbereiden.

## Kaartservices

Werken met kaarten is een interessante oefening, en er zijn veel opties om uit te kiezen, zoals Bing Maps, Leaflet, Open Street Maps en Google Maps. In deze les leer je over [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) en hoe je hiermee je GPS-gegevens kunt weergeven.

![Het Azure Maps-logo](../../../../../translated_images/nl/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps is "een verzameling geospatiale services en SDK's die gebruik maken van actuele kaartgegevens om geografische context te bieden aan web- en mobiele applicaties." Ontwikkelaars krijgen tools om prachtige, interactieve kaarten te maken die dingen kunnen doen zoals aanbevolen verkeersroutes bieden, informatie geven over verkeersincidenten, indoor navigatie, zoekmogelijkheden, hoogte-informatie, weerservices en meer.

✅ Experimenteer met enkele [codevoorbeelden voor kaarten](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Je kunt de kaarten weergeven als een leeg canvas, tegels, satellietbeelden, satellietbeelden met wegen eroverheen, verschillende soorten grijstintenkaarten, kaarten met schaduwwerking om hoogte te tonen, nachtweergavekaarten en een kaart met hoog contrast. Je kunt realtime updates op je kaarten krijgen door ze te integreren met [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Je kunt het gedrag en de uitstraling van je kaarten beheren door verschillende controles in te schakelen, zodat de kaart reageert op gebeurtenissen zoals knijpen, slepen en klikken. Om de uitstraling van je kaart te beheren, kun je lagen toevoegen met bubbels, lijnen, polygonen, heatmaps en meer. Welke stijl van kaart je implementeert, hangt af van je keuze van SDK.

Je kunt toegang krijgen tot Azure Maps API's door gebruik te maken van de [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), de [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), of, als je een mobiele app bouwt, de [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

In deze les gebruik je de web SDK om een kaart te tekenen en het pad van de GPS-locatie van je sensor weer te geven.

## Een Azure Maps-resource maken

De eerste stap is het maken van een Azure Maps-account.

### Taak - een Azure Maps-resource maken

1. Voer de volgende opdracht uit in je Terminal of Command Prompt om een Azure Maps-resource te maken in je `gps-sensor` resourcegroep:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Dit maakt een Azure Maps-resource genaamd `gps-sensor`. De gebruikte laag is `S1`, een betaalde laag die een reeks functies bevat, maar met een genereus aantal gratis oproepen.

    > 💁 Om de kosten van het gebruik van Azure Maps te zien, bekijk de [Azure Maps-prijspagina](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Je hebt een API-sleutel nodig voor de maps-resource. Gebruik de volgende opdracht om deze sleutel te verkrijgen:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Kopieer de waarde van `PrimaryKey`.

## Een kaart weergeven op een webpagina

Nu kun je de volgende stap zetten, namelijk je kaart weergeven op een webpagina. We gebruiken slechts één `html`-bestand voor je kleine webapp; houd er rekening mee dat in een productie- of teamomgeving je webapp waarschijnlijk meer onderdelen zal hebben!

### Taak - een kaart weergeven op een webpagina

1. Maak een bestand genaamd index.html in een map ergens op je lokale computer. Voeg HTML-markup toe om een kaart te bevatten:

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

    De kaart wordt geladen in de `myMap` `div`. Een paar stijlen zorgen ervoor dat deze de breedte en hoogte van de pagina beslaat.

    > 🎓 een `div` is een sectie van een webpagina die kan worden benoemd en gestyled.

1. Onder de openingstag `<head>` voeg je een externe stylesheet toe om de kaartweergave te beheren, en een extern script van de Web SDK om het gedrag ervan te beheren:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Deze stylesheet bevat de instellingen voor hoe de kaart eruitziet, en het scriptbestand bevat code om de kaart te laden. Het toevoegen van deze code is vergelijkbaar met het opnemen van C++-headerbestanden of het importeren van Python-modules.

1. Onder dat script voeg je een scriptblok toe om de kaart te starten.

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

    Vervang `<subscription_key>` door de API-sleutel voor je Azure Maps-account.

    Als je je `index.html`-pagina opent in een webbrowser, zou je een kaart moeten zien die is geladen en gericht is op het gebied van Seattle.

    ![Een kaart die Seattle toont, een stad in de staat Washington, VS](../../../../../translated_images/nl/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Experimenteer met de zoom- en middenparameters om je kaartweergave te wijzigen. Je kunt verschillende coördinaten toevoegen die overeenkomen met de breedte- en lengtegraad van je gegevens om de kaart opnieuw te centreren.

> 💁 Een betere manier om lokaal met webapps te werken, is door [http-server](https://www.npmjs.com/package/http-server) te installeren. Je hebt [node.js](https://nodejs.org/) en [npm](https://www.npmjs.com/) nodig voordat je deze tool kunt gebruiken. Zodra deze tools zijn geïnstalleerd, kun je naar de locatie van je `index.html`-bestand navigeren en `http-server` typen. De webapp wordt geopend op een lokale webserver [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## Het GeoJSON-formaat

Nu je je webapp hebt opgezet met de kaartweergave, moet je GPS-gegevens uit je opslagaccount halen en deze weergeven in een laag met markeringen bovenop de kaart. Voordat we dat doen, bekijken we het [GeoJSON](https://wikipedia.org/wiki/GeoJSON)-formaat dat vereist is door Azure Maps.

[GeoJSON](https://geojson.org/) is een open standaard JSON-specificatie met speciale opmaak die is ontworpen om geografisch-specifieke gegevens te verwerken. Je kunt er meer over leren door voorbeeldgegevens te testen met [geojson.io](https://geojson.io), wat ook een handig hulpmiddel is om GeoJSON-bestanden te debuggen.

Voorbeeld GeoJSON-gegevens zien er als volgt uit:

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

Van bijzonder belang is de manier waarop de gegevens zijn genest als een `Feature` binnen een `FeatureCollection`. Binnen dat object bevindt zich `geometry` met de `coordinates` die de breedte- en lengtegraad aangeven.

✅ Let bij het bouwen van je GeoJSON op de volgorde van `latitude` en `longitude` in het object, anders verschijnen je punten niet waar ze zouden moeten! GeoJSON verwacht gegevens in de volgorde `lon,lat` voor punten, niet `lat,lon`.

`Geometry` kan verschillende typen hebben, zoals een enkel punt of een polygoon. In dit voorbeeld is het een punt met twee opgegeven coördinaten, de lengtegraad en de breedtegraad.
✅ Azure Maps ondersteunt standaard GeoJSON plus enkele [uitgebreide functies](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), waaronder de mogelijkheid om cirkels en andere geometrieën te tekenen.

## GPS-gegevens plotten op een kaart met GeoJSON

Nu ben je klaar om gegevens te gebruiken uit de opslag die je in de vorige les hebt gebouwd. Ter herinnering: deze gegevens worden opgeslagen als een aantal bestanden in blobopslag, dus je moet de bestanden ophalen en parseren zodat Azure Maps de gegevens kan gebruiken.

### Taak - opslag configureren voor toegang vanaf een webpagina

Als je een oproep doet naar je opslag om de gegevens op te halen, kun je verrast worden door fouten die in de console van je browser verschijnen. Dat komt omdat je de rechten voor [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) op deze opslag moet instellen om externe webapps toegang te geven tot de gegevens.

> 🎓 CORS staat voor "Cross-Origin Resource Sharing" en moet meestal expliciet worden ingesteld in Azure om veiligheidsredenen. Het voorkomt dat onverwachte sites toegang krijgen tot je gegevens.

1. Voer de volgende opdracht uit om CORS in te schakelen:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Vervang `<storage_name>` door de naam van je opslagaccount. Vervang `<key1>` door de accountsleutel van je opslagaccount.

    Deze opdracht staat elke website toe (het wildcard `*` betekent elke) om een *GET*-verzoek te doen, oftewel gegevens op te halen, van je opslagaccount. De `--services b` betekent dat deze instelling alleen wordt toegepast op blobs.

### Taak - GPS-gegevens laden vanuit opslag

1. Vervang de volledige inhoud van de `init`-functie door de volgende code:

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

    Vervang `<storage_name>` door de naam van je opslagaccount. Vervang `<subscription_key>` door de API-sleutel van je Azure Maps-account.

    Hier gebeuren verschillende dingen. Eerst haalt de code je GPS-gegevens op uit je blobcontainer via een URL-endpoint dat is opgebouwd met de naam van je opslagaccount. Deze URL haalt gegevens op uit `gps-data`, wat aangeeft dat het brontype een container is (`restype=container`), en geeft informatie over alle blobs. Deze lijst retourneert niet de blobs zelf, maar geeft een URL voor elke blob die kan worden gebruikt om de blobgegevens te laden.

    > 💁 Je kunt deze URL in je browser plakken om details te zien van alle blobs in je container. Elk item heeft een `Url`-eigenschap die je ook in je browser kunt laden om de inhoud van de blob te bekijken.

    Deze code laadt vervolgens elke blob, waarbij een `loadJSON`-functie wordt aangeroepen, die hierna wordt gemaakt. Vervolgens wordt de kaartcontrole gemaakt en code toegevoegd aan het `ready`-evenement. Dit evenement wordt aangeroepen wanneer de kaart op de webpagina wordt weergegeven.

    Het `ready`-evenement maakt een Azure Maps-gegevensbron aan - een container die GeoJSON-gegevens bevat die later worden gevuld. Deze gegevensbron wordt vervolgens gebruikt om een bubbellaag te maken - een set cirkels op de kaart, gecentreerd op elk punt in de GeoJSON.

1. Voeg de `loadJSON`-functie toe aan je scriptblok, onder de `init`-functie:

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

    Deze functie wordt aangeroepen door de ophaalroutine om de JSON-gegevens te parseren en om te zetten zodat ze kunnen worden gelezen als lengte- en breedtecoördinaten in GeoJSON.
    Zodra ze zijn geparsed, worden de gegevens ingesteld als onderdeel van een GeoJSON `Feature`. De kaart wordt geïnitialiseerd en kleine bubbels verschijnen rond het pad dat je gegevens plotten:

1. Laad de HTML-pagina in je browser. De kaart wordt geladen, vervolgens worden alle GPS-gegevens uit de opslag geladen en op de kaart geplot.

    ![Een kaart van Saint Edward State Park nabij Seattle, met cirkels die een pad rond de rand van het park tonen](../../../../../translated_images/nl/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Je kunt deze code vinden in de [code](../../../../../3-transport/lessons/3-visualize-location-data/code) map.

---

## 🚀 Uitdaging

Het is leuk om statische gegevens als markeringen op een kaart weer te geven. Kun je deze webapp verbeteren door animatie toe te voegen en het pad van de markeringen in de loop van de tijd weer te geven, met behulp van de JSON-bestanden met tijdstempels? Hier zijn [enkele voorbeelden](https://azuremapscodesamples.azurewebsites.net/) van het gebruik van animatie binnen kaarten.

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Herziening & Zelfstudie

Azure Maps is bijzonder nuttig voor het werken met IoT-apparaten.

* Onderzoek enkele toepassingen in de [Azure Maps-documentatie op Microsoft Docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Verdiep je kennis van kaartmaken en waypoints met de [zelfstudie "Maak je eerste route-app met Azure Maps" op Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Opdracht

[Implementeer je app](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.