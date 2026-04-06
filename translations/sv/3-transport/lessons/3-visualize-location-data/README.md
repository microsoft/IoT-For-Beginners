# Visualisera platsdata

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-13.a259db1485021be7.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

Den här videon ger en översikt av Azure Maps med IoT, en tjänst som kommer att behandlas i denna lektion.

[![Azure Maps - Microsoft Azures plattform för platsdata](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Klicka på bilden ovan för att titta på videon

## Quiz före lektionen

[Quiz före lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Introduktion

I den senaste lektionen lärde du dig hur du hämtar GPS-data från dina sensorer och sparar det i molnet i en lagringsbehållare med hjälp av serverlös kod. Nu ska du upptäcka hur du kan visualisera dessa punkter på en Azure-karta. Du kommer att lära dig hur man skapar en karta på en webbsida, lära dig om GeoJSON-dataformatet och hur man använder det för att plotta alla insamlade GPS-punkter på din karta.

I denna lektion kommer vi att behandla:

* [Vad är datavisualisering](../../../../../3-transport/lessons/3-visualize-location-data)
* [Karttjänster](../../../../../3-transport/lessons/3-visualize-location-data)
* [Skapa en Azure Maps-resurs](../../../../../3-transport/lessons/3-visualize-location-data)
* [Visa en karta på en webbsida](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON-formatet](../../../../../3-transport/lessons/3-visualize-location-data)
* [Plotta GPS-data på en karta med GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Denna lektion kommer att involvera en liten mängd HTML och JavaScript. Om du vill lära dig mer om webbutveckling med HTML och JavaScript, kolla in [Webbutveckling för nybörjare](https://github.com/microsoft/Web-Dev-For-Beginners).

## Vad är datavisualisering

Datavisualisering handlar, som namnet antyder, om att visualisera data på sätt som gör det enklare för människor att förstå. Det förknippas ofta med diagram och grafer, men det kan vara vilket sätt som helst att visuellt representera data för att hjälpa människor att inte bara förstå datan bättre, utan också fatta beslut.

Ta ett enkelt exempel – i gårdsprojektet samlade du in data om jordfuktighet. En tabell med jordfuktighetsdata som samlats in varje timme den 1 juni 2021 kan se ut så här:

| Datum            | Avläsning |
| ---------------- | --------: |
| 01/06/2021 00:00 |       257 |
| 01/06/2021 01:00 |       268 |
| 01/06/2021 02:00 |       295 |
| 01/06/2021 03:00 |       305 |
| 01/06/2021 04:00 |       325 |
| 01/06/2021 05:00 |       359 |
| 01/06/2021 06:00 |       398 |
| 01/06/2021 07:00 |       410 |
| 01/06/2021 08:00 |       429 |
| 01/06/2021 09:00 |       451 |
| 01/06/2021 10:00 |       460 |
| 01/06/2021 11:00 |       452 |
| 01/06/2021 12:00 |       420 |
| 01/06/2021 13:00 |       408 |
| 01/06/2021 14:00 |       431 |
| 01/06/2021 15:00 |       462 |
| 01/06/2021 16:00 |       432 |
| 01/06/2021 17:00 |       402 |
| 01/06/2021 18:00 |       387 |
| 01/06/2021 19:00 |       360 |
| 01/06/2021 20:00 |       358 |
| 01/06/2021 21:00 |       354 |
| 01/06/2021 22:00 |       356 |
| 01/06/2021 23:00 |       362 |

Som människa kan det vara svårt att förstå denna data. Det är en vägg av siffror utan någon tydlig mening. Som ett första steg för att visualisera denna data kan den plottas i ett linjediagram:

![Ett linjediagram av ovanstående data](../../../../../translated_images/sv/chart-soil-moisture.fd6d9d0cdc0b5f75.webp)

Detta kan förbättras ytterligare genom att lägga till en linje som visar när det automatiska bevattningssystemet aktiverades vid en jordfuktighetsavläsning på 450:

![Ett linjediagram av jordfuktighet med en linje vid 450](../../../../../translated_images/sv/chart-soil-moisture-relay.fbb391236d34a64d.webp)

Detta diagram visar snabbt inte bara vad jordfuktighetsnivåerna var, utan också de punkter där bevattningssystemet aktiverades.

Diagram är inte det enda verktyget för att visualisera data. IoT-enheter som spårar väder kan ha webbappar eller mobilappar som visualiserar väderförhållanden med symboler, som en molnsymbol för molniga dagar, en regnmolnssymbol för regniga dagar och så vidare. Det finns många sätt att visualisera data, vissa seriösa, andra roliga.

✅ Fundera på sätt du har sett data visualiseras. Vilka metoder har varit tydligast och hjälpt dig att fatta beslut snabbast?

De bästa visualiseringarna gör det möjligt för människor att fatta beslut snabbt. Till exempel är det svårt att bearbeta en vägg av mätare som visar olika avläsningar från industriella maskiner, men ett blinkande rött ljus när något går fel gör det möjligt för en människa att fatta ett beslut. Ibland är den bästa visualiseringen ett blinkande ljus!

När du arbetar med GPS-data kan den tydligaste visualiseringen vara att plotta datan på en karta. En karta som visar leveransbilar kan till exempel hjälpa arbetare på en bearbetningsanläggning att se när bilar kommer att anlända. Om denna karta visar mer än bara bilder av bilar på deras aktuella platser, men också ger en uppfattning om innehållet i en bil, kan arbetarna på anläggningen planera därefter – om de ser en kylbil i närheten vet de att de ska förbereda plats i ett kylrum.

## Karttjänster

Att arbeta med kartor är en intressant övning, och det finns många att välja mellan, såsom Bing Maps, Leaflet, Open Street Maps och Google Maps. I denna lektion kommer du att lära dig om [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) och hur de kan visa din GPS-data.

![Azure Maps-logotypen](../../../../../translated_images/sv/azure-maps-logo.35d01dcfbd81fe61.webp)

Azure Maps är "en samling geospatiala tjänster och SDK:er som använder färska kartdata för att ge geografisk kontext till webb- och mobilapplikationer." Utvecklare får verktyg för att skapa vackra, interaktiva kartor som kan göra saker som att ge rekommenderade trafikvägar, ge information om trafikincidenter, inomhusnavigering, sökfunktioner, höjdinformation, vädertjänster och mer.

✅ Experimentera med några [kodexempel för kartor](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Du kan visa kartorna som en tom duk, kakel, satellitbilder, satellitbilder med vägar överlagrade, olika typer av gråskalekartor, kartor med skuggad relief för att visa höjd, nattkartor och en högkontrastkarta. Du kan få realtidsuppdateringar på dina kartor genom att integrera dem med [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Du kan styra kartans beteende och utseende genom att aktivera olika kontroller som gör att kartan reagerar på händelser som nyp, dra och klicka. För att styra kartans utseende kan du lägga till lager som inkluderar bubblor, linjer, polygoner, värmekartor och mer. Vilken stil av karta du implementerar beror på ditt val av SDK.

Du kan komma åt Azure Maps API:er genom att använda dess [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), dess [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), eller, om du bygger en mobilapp, dess [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

I denna lektion kommer du att använda web-SDK för att rita en karta och visa din sensors GPS-positionsväg.

## Skapa en Azure Maps-resurs

Ditt första steg är att skapa ett Azure Maps-konto.

### Uppgift – skapa en Azure Maps-resurs

1. Kör följande kommando från din terminal eller kommandotolk för att skapa en Azure Maps-resurs i din `gps-sensor`-resursgrupp:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Detta kommer att skapa en Azure Maps-resurs som heter `gps-sensor`. Den nivå som används är `S1`, som är en betald nivå som inkluderar en rad funktioner, men med ett generöst antal gratisanrop.

    > 💁 För att se kostnaden för att använda Azure Maps, kolla in [prissidan för Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Du kommer att behöva en API-nyckel för kartresursen. Använd följande kommando för att hämta denna nyckel:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Kopiera värdet för `PrimaryKey`.

## Visa en karta på en webbsida

Nu kan du ta nästa steg, vilket är att visa din karta på en webbsida. Vi kommer att använda endast en `html`-fil för din lilla webbapp; kom ihåg att i en produktions- eller teammiljö kommer din webbapp troligen att ha fler rörliga delar!

### Uppgift – visa en karta på en webbsida

1. Skapa en fil som heter index.html i en mapp någonstans på din lokala dator. Lägg till HTML-markup för att hålla en karta:

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

    Kartan kommer att laddas i `myMap`-`div`:en. Några stilar gör att den täcker sidans bredd och höjd.

    > 🎓 en `div` är en sektion av en webbsida som kan namnges och stylas.

1. Under den öppnande `<head>`-taggen, lägg till ett externt stilark för att styra kartans utseende och ett externt skript från Web SDK för att hantera dess beteende:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Detta stilark innehåller inställningarna för hur kartan ser ut, och skriptfilen innehåller kod för att ladda kartan. Att lägga till denna kod är liknande att inkludera C++-headerfiler eller importera Python-moduler.

1. Under det skriptet, lägg till ett skriptblock för att starta kartan.

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

    Ersätt `<subscription_key>` med API-nyckeln för ditt Azure Maps-konto.

    Om du öppnar din `index.html`-sida i en webbläsare bör du se en karta laddad och fokuserad på Seattle-området.

    ![En karta som visar Seattle, en stad i delstaten Washington, USA](../../../../../translated_images/sv/map-image.8fb2c53eb23ef39c.webp)

    ✅ Experimentera med zoom- och centerparametrarna för att ändra kartans visning. Du kan lägga till olika koordinater som motsvarar din datas latitud och longitud för att centrera om kartan.

> 💁 Ett bättre sätt att arbeta med webbappar lokalt är att installera [http-server](https://www.npmjs.com/package/http-server). Du behöver [node.js](https://nodejs.org/) och [npm](https://www.npmjs.com/) installerat innan du använder detta verktyg. När dessa verktyg är installerade kan du navigera till platsen för din `index.html`-fil och skriva `http-server`. Webbappen öppnas på en lokal webbserver [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## GeoJSON-formatet

Nu när du har din webbapp på plats med kartan visad, behöver du extrahera GPS-data från ditt lagringskonto och visa det i ett lager av markörer ovanpå kartan. Innan vi gör det, låt oss titta på [GeoJSON](https://wikipedia.org/wiki/GeoJSON)-formatet som krävs av Azure Maps.

[GeoJSON](https://geojson.org/) är en öppen standard för JSON-specifikation med särskild formatering utformad för att hantera geografisk specifik data. Du kan lära dig om det genom att testa exempeldata med [geojson.io](https://geojson.io), som också är ett användbart verktyg för att felsöka GeoJSON-filer.

Exempel på GeoJSON-data ser ut så här:

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

Av särskilt intresse är hur datan är inbäddad som en `Feature` inom en `FeatureCollection`. Inom det objektet finns `geometry` med `coordinates` som anger latitud och longitud.

✅ När du bygger din GeoJSON, var uppmärksam på ordningen av `latitud` och `longitud` i objektet, annars kommer dina punkter inte att visas där de ska! GeoJSON förväntar sig data i ordningen `lon,lat` för punkter, inte `lat,lon`.

`Geometry` kan ha olika typer, såsom en enskild punkt eller en polygon. I detta exempel är det en punkt med två angivna koordinater, longitud och latitud.
✅ Azure Maps stöder standard GeoJSON samt några [utökade funktioner](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), inklusive möjligheten att rita cirklar och andra geometrier.

## Plotta GPS-data på en karta med GeoJSON

Nu är du redo att använda data från lagringen som du byggde i den föregående lektionen. Som en påminnelse lagras den som ett antal filer i bloblagring, så du behöver hämta filerna och tolka dem så att Azure Maps kan använda datan.

### Uppgift - konfigurera lagring för att kunna nås från en webbsida

Om du gör ett anrop till din lagring för att hämta data kan du bli förvånad över att se fel i webbläsarens konsol. Det beror på att du behöver ställa in behörigheter för [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) på denna lagring för att tillåta externa webbappar att läsa dess data.

> 🎓 CORS står för "Cross-Origin Resource Sharing" och behöver vanligtvis ställas in explicit i Azure av säkerhetsskäl. Det förhindrar att oväntade webbplatser får åtkomst till din data.

1. Kör följande kommando för att aktivera CORS:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Ersätt `<storage_name>` med namnet på ditt lagringskonto. Ersätt `<key1>` med kontonyckeln för ditt lagringskonto.

    Detta kommando tillåter vilken webbplats som helst (wildcard `*` betyder vilken som helst) att göra ett *GET*-anrop, det vill säga hämta data, från ditt lagringskonto. `--services b` betyder att denna inställning endast gäller för blobs.

### Uppgift - ladda GPS-data från lagring

1. Ersätt hela innehållet i funktionen `init` med följande kod:

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

    Ersätt `<storage_name>` med namnet på ditt lagringskonto. Ersätt `<subscription_key>` med API-nyckeln för ditt Azure Maps-konto.

    Här händer flera saker. Först hämtar koden din GPS-data från din blobcontainer med hjälp av en URL-slutpunkt som byggs med ditt lagringskontos namn. Denna URL hämtar från `gps-data`, vilket indikerar att resurstypen är en container (`restype=container`), och listar information om alla blobs. Denna lista returnerar inte själva blobs, men returnerar en URL för varje blob som kan användas för att ladda blobdatan.

    > 💁 Du kan lägga in denna URL i din webbläsare för att se detaljer om alla blobs i din container. Varje objekt kommer att ha en `Url`-egenskap som du också kan ladda i din webbläsare för att se innehållet i blobben.

    Denna kod laddar sedan varje blob genom att anropa en funktion `loadJSON`, som kommer att skapas härnäst. Den skapar sedan kartkontrollen och lägger till kod till `ready`-händelsen. Denna händelse anropas när kartan visas på webbsidan.

    Ready-händelsen skapar en Azure Maps-datakälla - en container som innehåller GeoJSON-data som kommer att fyllas på senare. Denna datakälla används sedan för att skapa ett bubbellager - det vill säga en uppsättning cirklar på kartan centrerade över varje punkt i GeoJSON.

1. Lägg till funktionen `loadJSON` i ditt skriptblock, under funktionen `init`:

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

    Denna funktion anropas av hämtproceduren för att tolka JSON-datan och konvertera den till longitud- och latitudkoordinater som GeoJSON.
    När den har tolkats sätts datan som en del av en GeoJSON-`Feature`. Kartan kommer att initieras och små bubblor kommer att visas längs den väg som din data plottar:

1. Ladda HTML-sidan i din webbläsare. Den kommer att ladda kartan, sedan ladda all GPS-data från lagringen och plotta den på kartan.

    ![En karta över Saint Edward State Park nära Seattle, med cirklar som visar en väg runt parkens kant](../../../../../translated_images/sv/map-path.896832e72dc696ff.webp)

> 💁 Du kan hitta denna kod i [code](../../../../../3-transport/lessons/3-visualize-location-data/code)-mappen.

---

## 🚀 Utmaning

Det är trevligt att kunna visa statisk data på en karta som markörer. Kan du förbättra denna webbapp för att lägga till animation och visa markörernas väg över tid, med hjälp av de tidsstämplade JSON-filerna? Här är [några exempel](https://azuremapscodesamples.azurewebsites.net/) på att använda animation i kartor.

## Efterföreläsningsquiz

[Efterföreläsningsquiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Granskning & Självstudier

Azure Maps är särskilt användbart för att arbeta med IoT-enheter.

* Undersök några av användningsområdena i [Azure Maps-dokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Fördjupa din kunskap om kartskapande och waypoints med [skapa din första ruttplaneringsapp med Azure Maps självstyrda inlärningsmodul på Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Uppgift

[Distribuera din app](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.