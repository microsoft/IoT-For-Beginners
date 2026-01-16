<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-27T21:34:12+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "no"
}
-->
# Visualisere stedsdata

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne videoen gir en oversikt over Azure Maps med IoT, en tjeneste som vil bli dekket i denne leksjonen.

[![Azure Maps - Microsoft Azure Enterprise Location Platform](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Klikk på bildet over for å se videoen

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Introduksjon

I forrige leksjon lærte du hvordan du kan hente GPS-data fra sensorene dine og lagre dem i skyen i en lagringscontainer ved hjelp av serverløs kode. Nå skal du oppdage hvordan du kan visualisere disse punktene på et Azure-kart. Du vil lære hvordan du oppretter et kart på en nettside, lære om GeoJSON-dataformatet og hvordan du bruker det til å plotte alle de innsamlede GPS-punktene på kartet ditt.

I denne leksjonen dekker vi:

* [Hva er datavisualisering](../../../../../3-transport/lessons/3-visualize-location-data)
* [Karttjenester](../../../../../3-transport/lessons/3-visualize-location-data)
* [Opprett en Azure Maps-ressurs](../../../../../3-transport/lessons/3-visualize-location-data)
* [Vis et kart på en nettside](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON-formatet](../../../../../3-transport/lessons/3-visualize-location-data)
* [Plot GPS-data på et kart ved hjelp av GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Denne leksjonen vil involvere en liten mengde HTML og JavaScript. Hvis du ønsker å lære mer om webutvikling med HTML og JavaScript, sjekk ut [Webutvikling for nybegynnere](https://github.com/microsoft/Web-Dev-For-Beginners).

## Hva er datavisualisering

Datavisualisering, som navnet antyder, handler om å visualisere data på måter som gjør det enklere for mennesker å forstå. Det er vanligvis assosiert med diagrammer og grafer, men det er enhver måte å visuelt representere data på for å hjelpe mennesker med å ikke bare forstå dataene bedre, men også ta beslutninger.

La oss ta et enkelt eksempel - i gårdsprosjektet samlet du inn data om jordfuktighet. En tabell med jordfuktighetsdata samlet inn hver time for 1. juni 2021 kan se slik ut:

| Dato             | Måling |
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

Som menneske kan det være vanskelig å forstå disse dataene. Det er en vegg av tall uten noen mening. Som et første steg for å visualisere disse dataene, kan de plottes på et linjediagram:

![Et linjediagram av dataene ovenfor](../../../../../translated_images/no/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Dette kan forbedres ytterligere ved å legge til en linje som indikerer når det automatiske vanningssystemet ble slått på ved en jordfuktighetsmåling på 450:

![Et linjediagram av jordfuktighet med en linje ved 450](../../../../../translated_images/no/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Dette diagrammet viser raskt ikke bare hva jordfuktighetsnivåene var, men også punktene der vanningssystemet ble slått på.

Diagrammer er ikke det eneste verktøyet for å visualisere data. IoT-enheter som sporer værforhold kan ha web- eller mobilapper som visualiserer værforhold ved hjelp av symboler, som et sky-symbol for overskyede dager, en regnsky for regnværsdager, og så videre. Det finnes et stort antall måter å visualisere data på, noen seriøse, andre morsomme.

✅ Tenk på måter du har sett data visualisert. Hvilke metoder har vært de tydeligste og gjort det enklest å ta beslutninger?

De beste visualiseringene lar mennesker ta beslutninger raskt. For eksempel, å ha en vegg av målere som viser alle slags avlesninger fra industrielt utstyr er vanskelig å prosessere, men et blinkende rødt lys når noe går galt lar en person ta en beslutning. Noen ganger er den beste visualiseringen et blinkende lys!

Når du arbeider med GPS-data, kan den tydeligste visualiseringen være å plotte dataene på et kart. Et kart som viser leveringsbiler, for eksempel, kan hjelpe arbeidere på et behandlingsanlegg med å se når biler vil ankomme. Hvis dette kartet viser mer enn bare bilder av biler på deres nåværende lokasjoner, men også gir en idé om innholdet i en bil, kan arbeiderne på anlegget planlegge deretter - hvis de ser en kjølebil i nærheten, vet de at de må forberede plass i et kjølerom.

## Karttjenester

Å jobbe med kart er en interessant øvelse, og det finnes mange alternativer å velge mellom, som Bing Maps, Leaflet, Open Street Maps og Google Maps. I denne leksjonen vil du lære om [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) og hvordan de kan vise GPS-dataene dine.

![Azure Maps-logoen](../../../../../translated_images/no/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps er "en samling av geospatiale tjenester og SDK-er som bruker oppdatert kartdata for å gi geografisk kontekst til web- og mobilapplikasjoner." Utviklere får verktøy for å lage vakre, interaktive kart som kan gjøre ting som å gi anbefalte trafikkruter, gi informasjon om trafikkhendelser, innendørs navigasjon, søkefunksjoner, høydeinformasjon, værdata og mer.

✅ Eksperimenter med noen [kartkodeeksempler](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Du kan vise kartene som et blankt lerret, fliser, satellittbilder, satellittbilder med veier overlagt, ulike typer gråtonede kart, kart med skygge for å vise høyde, nattvisningskart og et høy-kontrast-kart. Du kan få sanntidsoppdateringer på kartene dine ved å integrere dem med [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Du kan kontrollere oppførselen og utseendet til kartene dine ved å aktivere ulike kontroller som lar kartet reagere på hendelser som klyping, dra og klikk. For å kontrollere utseendet til kartet ditt, kan du legge til lag som inkluderer bobler, linjer, polygoner, varmekart og mer. Hvilken stil av kart du implementerer avhenger av ditt valg av SDK.

Du kan få tilgang til Azure Maps API-er ved å bruke [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), eller, hvis du bygger en mobilapp, [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

I denne leksjonen vil du bruke web-SDK for å tegne et kart og vise GPS-lokasjonens bane fra sensoren din.

## Opprett en Azure Maps-ressurs

Ditt første steg er å opprette en Azure Maps-konto.

### Oppgave - opprett en Azure Maps-ressurs

1. Kjør følgende kommando fra Terminal eller Kommandolinje for å opprette en Azure Maps-ressurs i ressursgruppen `gps-sensor`:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Dette vil opprette en Azure Maps-ressurs kalt `gps-sensor`. Nivået som brukes er `S1`, som er et betalt nivå som inkluderer en rekke funksjoner, men med en sjenerøs mengde gratis kall.

    > 💁 For å se kostnaden ved å bruke Azure Maps, sjekk ut [prissiden for Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Du vil trenge en API-nøkkel for kartressursen. Bruk følgende kommando for å hente denne nøkkelen:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Ta en kopi av verdien `PrimaryKey`.

## Vis et kart på en nettside

Nå kan du ta neste steg, som er å vise kartet ditt på en nettside. Vi vil bruke kun én `html`-fil for din lille webapp; husk at i et produksjons- eller teammiljø vil webappen din mest sannsynlig ha flere bevegelige deler!

### Oppgave - vis et kart på en nettside

1. Opprett en fil kalt index.html i en mappe et sted på din lokale datamaskin. Legg til HTML-markup for å holde et kart:

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

    Kartet vil lastes inn i `div`-en `myMap`. Noen få stiler lar det dekke bredden og høyden på siden.

    > 🎓 En `div` er en seksjon av en nettside som kan navngis og styles.

1. Under den åpne `<head>`-taggen, legg til et eksternt stilark for å kontrollere kartvisningen, og et eksternt skript fra Web SDK for å håndtere oppførselen:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Dette stilarket inneholder innstillingene for hvordan kartet ser ut, og skriptfilen inneholder kode for å laste inn kartet. Å legge til denne koden er likt som å inkludere C++-headerfiler eller importere Python-moduler.

1. Under det skriptet, legg til en skriptblokk for å starte kartet.

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

    Erstatt `<subscription_key>` med API-nøkkelen for din Azure Maps-konto.

    Hvis du åpner `index.html`-siden din i en nettleser, bør du se et kart lastet inn, fokusert på Seattle-området.

    ![Et kart som viser Seattle, en by i delstaten Washington, USA](../../../../../translated_images/no/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Eksperimenter med zoom- og senterparametrene for å endre kartvisningen. Du kan legge til ulike koordinater som tilsvarer dataens breddegrad og lengdegrad for å re-sentrere kartet.

> 💁 En bedre måte å jobbe med webapper lokalt på er å installere [http-server](https://www.npmjs.com/package/http-server). Du vil trenge [node.js](https://nodejs.org/) og [npm](https://www.npmjs.com/) installert før du bruker dette verktøyet. Når disse verktøyene er installert, kan du navigere til plasseringen av `index.html`-filen din og skrive `http-server`. Webappen vil åpne seg på en lokal webserver [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## GeoJSON-formatet

Nå som du har webappen din på plass med kartet vist, må du hente GPS-data fra lagringskontoen din og vise det i et lag med markører oppå kartet. Før vi gjør det, la oss se på [GeoJSON](https://wikipedia.org/wiki/GeoJSON)-formatet som kreves av Azure Maps.

[GeoJSON](https://geojson.org/) er en åpen standard JSON-spesifikasjon med spesiell formatering designet for å håndtere geografisk-spesifikke data. Du kan lære om det ved å teste eksempeldata ved hjelp av [geojson.io](https://geojson.io), som også er et nyttig verktøy for å feilsøke GeoJSON-filer.

Eksempel på GeoJSON-data ser slik ut:

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

Av spesiell interesse er måten dataene er nestet som en `Feature` innenfor en `FeatureCollection`. Innenfor det objektet finnes `geometry` med `coordinates` som indikerer breddegrad og lengdegrad.

✅ Når du bygger GeoJSON-en din, vær oppmerksom på rekkefølgen av `latitude` og `longitude` i objektet, ellers vil punktene dine ikke vises der de skal! GeoJSON forventer data i rekkefølgen `lon,lat` for punkter, ikke `lat,lon`.

`Geometry` kan ha ulike typer, som et enkelt punkt eller en polygon. I dette eksemplet er det et punkt med to spesifiserte koordinater, lengdegrad og breddegrad.
✅ Azure Maps støtter standard GeoJSON pluss noen [utvidede funksjoner](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), inkludert muligheten til å tegne sirkler og andre geometriske figurer.

## Plot GPS-data på et kart ved hjelp av GeoJSON

Nå er du klar til å bruke data fra lagringen du opprettet i forrige leksjon. Som en påminnelse er dataene lagret som en rekke filer i blob-lagring, så du må hente filene og analysere dem slik at Azure Maps kan bruke dataene.

### Oppgave - konfigurer lagring for tilgang fra en nettside

Hvis du prøver å hente data fra lagringen din, kan det hende du blir overrasket over å se feil i nettleserens konsoll. Dette skyldes at du må sette tillatelser for [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) på denne lagringen for å tillate eksterne webapplikasjoner å lese dataene.

> 🎓 CORS står for "Cross-Origin Resource Sharing" og må vanligvis settes eksplisitt i Azure av sikkerhetsgrunner. Det forhindrer uventede nettsteder fra å få tilgang til dataene dine.

1. Kjør følgende kommando for å aktivere CORS:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Erstatt `<storage_name>` med navnet på lagringskontoen din. Erstatt `<key1>` med kontonøkkelen for lagringskontoen din.

    Denne kommandoen tillater at ethvert nettsted (jokertegnet `*` betyr hvilket som helst) kan gjøre en *GET*-forespørsel, altså hente data, fra lagringskontoen din. `--services b` betyr at denne innstillingen kun gjelder for blobs.

### Oppgave - last inn GPS-data fra lagring

1. Erstatt hele innholdet i `init`-funksjonen med følgende kode:

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

    Erstatt `<storage_name>` med navnet på lagringskontoen din. Erstatt `<subscription_key>` med API-nøkkelen for din Azure Maps-konto.

    Det skjer flere ting her. Først henter koden GPS-dataene dine fra blob-beholderen ved hjelp av en URL-endepunkt som bygges ved hjelp av lagringskontonavnet ditt. Denne URL-en henter fra `gps-data`, som indikerer at ressursen er en beholder (`restype=container`), og lister informasjon om alle blobene. Denne listen returnerer ikke selve blobene, men gir en URL for hver blob som kan brukes til å laste inn blob-dataene.

    > 💁 Du kan lime inn denne URL-en i nettleseren din for å se detaljer om alle blobene i beholderen din. Hver post vil ha en `Url`-egenskap som du også kan laste inn i nettleseren for å se innholdet i bloben.

    Deretter laster koden inn hver blob ved å kalle en `loadJSON`-funksjon, som vil bli opprettet neste. Den oppretter deretter kartkontrollen og legger til kode i `ready`-hendelsen. Denne hendelsen kalles når kartet vises på nettsiden.

    `Ready`-hendelsen oppretter en Azure Maps-datakilde - en beholder som inneholder GeoJSON-data som vil bli fylt inn senere. Denne datakilden brukes deretter til å opprette et boblelag - altså et sett med sirkler på kartet sentrert over hvert punkt i GeoJSON.

1. Legg til `loadJSON`-funksjonen i skriptblokken din, under `init`-funksjonen:

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

    Denne funksjonen kalles av hente-rutinen for å analysere JSON-dataene og konvertere dem til å leses som lengde- og breddegrader i GeoJSON-format. Når de er analysert, settes dataene som en del av en GeoJSON `Feature`. Kartet vil bli initialisert, og små bobler vil dukke opp langs stien dataene dine plotter:

1. Last inn HTML-siden i nettleseren din. Den vil laste inn kartet, deretter laste inn all GPS-data fra lagringen og plotte det på kartet.

    ![Et kart over Saint Edward State Park nær Seattle, med sirkler som viser en sti rundt kanten av parken](../../../../../translated_images/no/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Du finner denne koden i [code](../../../../../3-transport/lessons/3-visualize-location-data/code)-mappen.

---

## 🚀 Utfordring

Det er fint å kunne vise statiske data på et kart som markører. Kan du forbedre denne webapplikasjonen til å legge til animasjon og vise stien til markørene over tid, ved hjelp av de tidsstemplede JSON-filene? Her er [noen eksempler](https://azuremapscodesamples.azurewebsites.net/) på bruk av animasjon i kart.

## Quiz etter leksjonen

[Quiz etter leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Gjennomgang og selvstudium

Azure Maps er spesielt nyttig for arbeid med IoT-enheter.

* Undersøk noen av bruksområdene i [Azure Maps-dokumentasjonen på Microsoft Docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Fordyp deg i kartlegging og veipunkter med [opprett din første ruteplanleggingsapp med Azure Maps selvstyrt læringsmodul på Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Oppgave

[Distribuer appen din](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.