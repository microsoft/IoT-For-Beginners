<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-27T21:33:24+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "da"
}
-->
# Visualiser lokationsdata

![En sketchnote oversigt over denne lektion](../../../../../translated_images/da/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

Denne video giver en oversigt over Azure Maps med IoT, en tjeneste der vil blive dækket i denne lektion.

[![Azure Maps - Microsoft Azure Enterprise Location Platform](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Klik på billedet ovenfor for at se videoen

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Introduktion

I den sidste lektion lærte du, hvordan du får GPS-data fra dine sensorer og gemmer dem i skyen i en lagercontainer ved hjælp af serverløs kode. Nu vil du opdage, hvordan du visualiserer disse punkter på et Azure-kort. Du vil lære, hvordan du opretter et kort på en webside, lære om GeoJSON-dataformatet og hvordan du bruger det til at plotte alle de indsamlede GPS-punkter på dit kort.

I denne lektion dækker vi:

* [Hvad er datavisualisering](../../../../../3-transport/lessons/3-visualize-location-data)
* [Korttjenester](../../../../../3-transport/lessons/3-visualize-location-data)
* [Opret en Azure Maps-ressource](../../../../../3-transport/lessons/3-visualize-location-data)
* [Vis et kort på en webside](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON-formatet](../../../../../3-transport/lessons/3-visualize-location-data)
* [Plot GPS-data på et kort ved hjælp af GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Denne lektion vil involvere en lille smule HTML og JavaScript. Hvis du gerne vil lære mere om webudvikling med HTML og JavaScript, kan du tjekke [Webudvikling for begyndere](https://github.com/microsoft/Web-Dev-For-Beginners).

## Hvad er datavisualisering

Datavisualisering handler, som navnet antyder, om at visualisere data på måder, der gør det lettere for mennesker at forstå. Det forbindes ofte med diagrammer og grafer, men det kan være enhver form for billedlig repræsentation af data, der hjælper mennesker med ikke kun at forstå data bedre, men også med at træffe beslutninger.

Lad os tage et simpelt eksempel - tilbage i landbrugsprojektet indsamlede du data om jordfugtighed. En tabel med jordfugtighedsdata indsamlet hver time den 1. juni 2021 kunne se sådan ud:

| Dato             | Aflæsning |
| ---------------- | -------: |
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

Som menneske kan det være svært at forstå disse data. Det er en mur af tal uden nogen mening. Som et første skridt til at visualisere disse data kan de plottes på et linjediagram:

![Et linjediagram af ovenstående data](../../../../../translated_images/da/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Dette kan yderligere forbedres ved at tilføje en linje, der indikerer, hvornår det automatiske vandingssystem blev tændt ved en jordfugtighedsaflæsning på 450:

![Et linjediagram af jordfugtighed med en linje ved 450](../../../../../translated_images/da/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Dette diagram viser meget hurtigt ikke kun, hvad jordfugtighedsniveauerne var, men også de punkter, hvor vandingssystemet blev tændt.

Diagrammer er ikke det eneste værktøj til at visualisere data. IoT-enheder, der sporer vejret, kan have webapps eller mobilapps, der visualiserer vejrforhold ved hjælp af symboler, såsom et sky-symbol for overskyede dage, en regnsky for regnfulde dage og så videre. Der er et enormt antal måder at visualisere data på, nogle seriøse, andre sjove.

✅ Tænk over måder, du har set data visualiseret. Hvilke metoder har været de mest klare og har gjort det muligt for dig at træffe beslutninger hurtigst?

De bedste visualiseringer gør det muligt for mennesker at træffe beslutninger hurtigt. For eksempel kan det være svært at bearbejde en væg af målere, der viser alle mulige aflæsninger fra industrimaskiner, men et blinkende rødt lys, når noget går galt, gør det muligt for en person at træffe en beslutning. Nogle gange er den bedste visualisering et blinkende lys!

Når man arbejder med GPS-data, kan den mest klare visualisering være at plotte dataene på et kort. Et kort, der viser leveringslastbiler, kan for eksempel hjælpe medarbejdere på et behandlingsanlæg med at se, hvornår lastbilerne ankommer. Hvis dette kort viser mere end blot billeder af lastbiler på deres nuværende placeringer, men også giver en idé om indholdet af en lastbil, kan medarbejderne på anlægget planlægge derefter - hvis de ser en kølelastbil tæt på, ved de, at de skal forberede plads i et køleskab.

## Korttjenester

At arbejde med kort er en interessant øvelse, og der er mange at vælge imellem, såsom Bing Maps, Leaflet, Open Street Maps og Google Maps. I denne lektion vil du lære om [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) og hvordan de kan vise dine GPS-data.

![Azure Maps-logoet](../../../../../translated_images/da/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps er "en samling af geospatiale tjenester og SDK'er, der bruger friske kortdata til at give geografisk kontekst til web- og mobilapplikationer." Udviklere får værktøjer til at skabe smukke, interaktive kort, der kan gøre ting som at give anbefalede trafikruter, give information om trafikulykker, indendørs navigation, søgefunktioner, højdeinformation, vejrtjenester og mere.

✅ Eksperimentér med nogle [kodeeksempler til kort](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Du kan vise kortene som et tomt lærred, fliser, satellitbilleder, satellitbilleder med veje overlejret, forskellige typer gråtonede kort, kort med skygget relief for at vise højde, natvisningskort og et kort med høj kontrast. Du kan få realtidsopdateringer på dine kort ved at integrere dem med [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Du kan kontrollere kortets adfærd og udseende ved at aktivere forskellige kontroller, der gør det muligt for kortet at reagere på begivenheder som knib, træk og klik. For at kontrollere kortets udseende kan du tilføje lag, der inkluderer bobler, linjer, polygoner, varmekort og mere. Hvilken stil af kort du implementerer afhænger af dit valg af SDK.

Du kan få adgang til Azure Maps API'er ved at bruge dens [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), dens [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), eller, hvis du bygger en mobilapp, dens [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

I denne lektion vil du bruge web-SDK'et til at tegne et kort og vise din sensors GPS-lokationssti.

## Opret en Azure Maps-ressource

Dit første skridt er at oprette en Azure Maps-konto.

### Opgave - opret en Azure Maps-ressource

1. Kør følgende kommando fra din Terminal eller Kommandoprompt for at oprette en Azure Maps-ressource i din `gps-sensor` ressourcegruppe:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Dette vil oprette en Azure Maps-ressource kaldet `gps-sensor`. Den anvendte tier er `S1`, som er en betalt tier, der inkluderer en række funktioner, men med et generøst antal gratis opkald.

    > 💁 For at se omkostningerne ved at bruge Azure Maps, tjek [Azure Maps-prissiden](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Du skal bruge en API-nøgle til kortressourcen. Brug følgende kommando for at få denne nøgle:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Tag en kopi af værdien `PrimaryKey`.

## Vis et kort på en webside

Nu kan du tage det næste skridt, som er at vise dit kort på en webside. Vi vil kun bruge én `html`-fil til din lille webapp; husk, at i et produktions- eller teammiljø vil din webapp sandsynligvis have flere bevægelige dele!

### Opgave - vis et kort på en webside

1. Opret en fil kaldet index.html i en mappe et sted på din lokale computer. Tilføj HTML-markup for at holde et kort:

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

    Kortet vil blive indlæst i `myMap` `div`. Et par stilarter gør det muligt for det at strække sig over hele sidens bredde og højde.

    > 🎓 En `div` er en sektion af en webside, der kan navngives og styles.

1. Under den åbne `<head>`-tag, tilføj et eksternt stylesheet for at kontrollere kortets udseende og et eksternt script fra Web SDK'et for at styre dets adfærd:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Dette stylesheet indeholder indstillingerne for, hvordan kortet ser ud, og scriptfilen indeholder kode til at indlæse kortet. At tilføje denne kode svarer til at inkludere C++ header-filer eller importere Python-moduler.

1. Under det script, tilføj et scriptblok for at starte kortet.

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

    Erstat `<subscription_key>` med API-nøglen til din Azure Maps-konto.

    Hvis du åbner din `index.html`-side i en webbrowser, bør du se et kort indlæst og fokuseret på Seattle-området.

    ![Et kort, der viser Seattle, en by i staten Washington, USA](../../../../../translated_images/da/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Eksperimentér med zoom- og centerparametrene for at ændre dit korts visning. Du kan tilføje forskellige koordinater, der svarer til din datas bredde- og længdegrad, for at re-centrere kortet.

> 💁 En bedre måde at arbejde med webapps lokalt er at installere [http-server](https://www.npmjs.com/package/http-server). Du skal have [node.js](https://nodejs.org/) og [npm](https://www.npmjs.com/) installeret, før du bruger dette værktøj. Når disse værktøjer er installeret, kan du navigere til placeringen af din `index.html`-fil og skrive `http-server`. Webappen vil åbne på en lokal webserver [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## GeoJSON-formatet

Nu hvor du har din webapp på plads med kortet vist, skal du udtrække GPS-data fra din lagerkonto og vise dem i et lag af markører oven på kortet. Før vi gør det, lad os se på [GeoJSON](https://wikipedia.org/wiki/GeoJSON)-formatet, som kræves af Azure Maps.

[GeoJSON](https://geojson.org/) er en åben standard JSON-specifikation med speciel formatering designet til at håndtere geografisk-specifikke data. Du kan lære om det ved at teste eksempeldata ved hjælp af [geojson.io](https://geojson.io), som også er et nyttigt værktøj til at fejlfinde GeoJSON-filer.

Eksempel på GeoJSON-data ser sådan ud:

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

Af særlig interesse er måden, dataene er indlejret som en `Feature` inden for en `FeatureCollection`. Inden for dette objekt kan man finde `geometry` med `coordinates`, der angiver bredde- og længdegrad.

✅ Når du bygger din geoJSON, skal du være opmærksom på rækkefølgen af `latitude` og `longitude` i objektet, ellers vil dine punkter ikke vises, hvor de skal! GeoJSON forventer data i rækkefølgen `lon,lat` for punkter, ikke `lat,lon`.

`Geometry` kan have forskellige typer, såsom et enkelt punkt eller en polygon. I dette eksempel er det et punkt med to specificerede koordinater, længdegraden og breddegraden.
✅ Azure Maps understøtter standard GeoJSON plus nogle [udvidede funktioner](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), herunder muligheden for at tegne cirkler og andre geometriske figurer.

## Plot GPS-data på et kort ved hjælp af GeoJSON

Nu er du klar til at bruge data fra den lagring, du oprettede i den forrige lektion. Som en påmindelse er det gemt som en række filer i blob-lagring, så du skal hente filerne og analysere dem, så Azure Maps kan bruge dataene.

### Opgave - konfigurer lagring til at blive tilgået fra en webside

Hvis du foretager et kald til din lagring for at hente dataene, kan du blive overrasket over at se fejl i din browsers konsol. Det skyldes, at du skal indstille tilladelser for [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) på denne lagring for at tillade eksterne webapps at læse dens data.

> 🎓 CORS står for "Cross-Origin Resource Sharing" og skal normalt eksplicit indstilles i Azure af sikkerhedsmæssige årsager. Det forhindrer uventede sider i at få adgang til dine data.

1. Kør følgende kommando for at aktivere CORS:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Erstat `<storage_name>` med navnet på din lagringskonto. Erstat `<key1>` med kontonøglen for din lagringskonto.

    Denne kommando tillader enhver hjemmeside (jokertegnet `*` betyder enhver) at foretage en *GET*-anmodning, det vil sige hente data, fra din lagringskonto. `--services b` betyder, at denne indstilling kun gælder for blobs.

### Opgave - indlæs GPS-data fra lagring

1. Erstat hele indholdet af `init`-funktionen med følgende kode:

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

    Erstat `<storage_name>` med navnet på din lagringskonto. Erstat `<subscription_key>` med API-nøglen for din Azure Maps-konto.

    Der sker flere ting her. Først henter koden dine GPS-data fra din blob-container ved hjælp af et URL-endepunkt, der er bygget ved hjælp af navnet på din lagringskonto. Denne URL henter fra `gps-data`, hvilket angiver, at ressource-typen er en container (`restype=container`), og lister information om alle blobs. Denne liste returnerer ikke selve blobs, men returnerer en URL for hver blob, der kan bruges til at indlæse blob-data.

    > 💁 Du kan indsætte denne URL i din browser for at se detaljer om alle blobs i din container. Hvert element vil have en `Url`-egenskab, som du også kan indlæse i din browser for at se indholdet af blobben.

    Denne kode indlæser derefter hver blob og kalder en `loadJSON`-funktion, som vil blive oprettet næste gang. Den opretter derefter kortkontrollen og tilføjer kode til `ready`-hændelsen. Denne hændelse kaldes, når kortet vises på websiden.

    Ready-hændelsen opretter en Azure Maps-datakilde - en container, der indeholder GeoJSON-data, som vil blive udfyldt senere. Denne datakilde bruges derefter til at oprette et boblelag - det vil sige et sæt cirkler på kortet centreret over hvert punkt i GeoJSON.

1. Tilføj `loadJSON`-funktionen til dit script-blok, under `init`-funktionen:

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

    Denne funktion kaldes af fetch-rutinen for at analysere JSON-dataene og konvertere dem til at blive læst som længde- og breddegrader som geoJSON. Når de er analyseret, sættes dataene som en del af en geoJSON `Feature`. Kortet vil blive initialiseret, og små bobler vil dukke op langs den rute, dine data afbilder:

1. Indlæs HTML-siden i din browser. Den vil indlæse kortet, derefter indlæse alle GPS-data fra lagringen og plotte dem på kortet.

    ![Et kort over Saint Edward State Park nær Seattle, med cirkler, der viser en rute rundt om parkens kant](../../../../../translated_images/da/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Du kan finde denne kode i [code](../../../../../3-transport/lessons/3-visualize-location-data/code)-mappen.

---

## 🚀 Udfordring

Det er rart at kunne vise statiske data på et kort som markører. Kan du forbedre denne webapp til at tilføje animation og vise ruten for markørerne over tid ved hjælp af de tidsstemplede JSON-filer? Her er [nogle eksempler](https://azuremapscodesamples.azurewebsites.net/) på brug af animation i kort.

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Gennemgang & Selvstudie

Azure Maps er særligt nyttigt til at arbejde med IoT-enheder.

* Undersøg nogle af anvendelserne i [Azure Maps-dokumentationen på Microsoft docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Uddyb din viden om kortlægning og waypoints med [opret din første ruteplanlægningsapp med Azure Maps selvstudie på Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Opgave

[Udrul din app](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.