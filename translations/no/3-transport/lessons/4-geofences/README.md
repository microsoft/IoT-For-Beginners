<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-27T21:31:00+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "no"
}
-->
# Geogjerder

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne videoen gir en oversikt over geogjerder og hvordan du bruker dem i Azure Maps, temaer som vil bli dekket i denne leksjonen:

[![Geogjerder med Azure Maps fra Microsoft Developer IoT-showet](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Klikk på bildet ovenfor for å se videoen

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Introduksjon

I de siste tre leksjonene har du brukt IoT til å spore lastebilene som frakter produktene dine fra gården til et prosesseringsanlegg. Du har fanget opp GPS-data, sendt dem til skyen for lagring, og visualisert dem på et kart. Neste steg for å øke effektiviteten i forsyningskjeden din er å få et varsel når en lastebil nærmer seg prosesseringsanlegget, slik at mannskapet som skal losse kan være klare med gaffeltrucker og annet utstyr så snart kjøretøyet ankommer. På denne måten kan de losse raskt, og du slipper å betale for at lastebilen og sjåføren må vente.

I denne leksjonen vil du lære om geogjerder – definerte geografiske områder, som for eksempel et område innenfor en 2 km kjøretur fra et prosesseringsanlegg, og hvordan du tester om GPS-koordinater er innenfor eller utenfor et geogjerde, slik at du kan se om GPS-sensoren din har ankommet eller forlatt et område.

I denne leksjonen dekker vi:

* [Hva er geogjerder](../../../../../3-transport/lessons/4-geofences)
* [Definer et geogjerde](../../../../../3-transport/lessons/4-geofences)
* [Test punkter mot et geogjerde](../../../../../3-transport/lessons/4-geofences)
* [Bruk geogjerder fra serverløs kode](../../../../../3-transport/lessons/4-geofences)

> 🗑 Dette er den siste leksjonen i dette prosjektet, så etter at du har fullført denne leksjonen og oppgaven, ikke glem å rydde opp i skytjenestene dine. Du vil trenge tjenestene for å fullføre oppgaven, så sørg for å fullføre den først.
>
> Se [veiledningen for å rydde opp i prosjektet ditt](../../../clean-up.md) hvis du trenger instruksjoner for hvordan du gjør dette.

## Hva er geogjerder

Et geogjerde er en virtuell grense for et geografisk område i den virkelige verden. Geogjerder kan være sirkler definert som et punkt og en radius (for eksempel en sirkel med en diameter på 100m rundt en bygning), eller en polygon som dekker et område som en skole, bygrenser, eller et universitets- eller kontorområde.

![Noen eksempler på geogjerder som viser et sirkulært geogjerde rundt Microsofts firmabutikk, og et polygon-geogjerde rundt Microsofts vestcampus](../../../../../translated_images/no/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.png)

> 💁 Du har kanskje allerede brukt geogjerder uten å vite det. Hvis du har satt en påminnelse i iOS-påminnelsesappen eller Google Keep basert på en lokasjon, har du brukt et geogjerde. Disse appene setter opp et geogjerde basert på den angitte lokasjonen og varsler deg når telefonen din går inn i geogjerdet.

Det finnes mange grunner til at du vil vite om et kjøretøy er innenfor eller utenfor et geogjerde:

* Forberedelse for lossing – å få et varsel om at et kjøretøy har ankommet stedet gjør det mulig for mannskapet å være klare til å losse kjøretøyet, noe som reduserer ventetiden for kjøretøyet. Dette kan gjøre det mulig for sjåføren å utføre flere leveranser på en dag med mindre ventetid.
* Skatteoverholdelse – noen land, som New Zealand, krever veiskatter for dieselkjøretøy basert på kjøretøyets vekt når det kjører på offentlige veier. Ved å bruke geogjerder kan du spore kjørelengden på offentlige veier i motsetning til private veier på steder som gårder eller skogsområder.
* Tyveriovervåking – hvis et kjøretøy kun skal være innenfor et bestemt område, som på en gård, og det forlater geogjerdet, kan det ha blitt stjålet.
* Lokasjonsregler – noen deler av en arbeidsplass, gård eller fabrikk kan være forbudt for visse kjøretøy, som å holde kjøretøy som frakter kunstgjødsel og plantevernmidler unna felt som dyrker økologiske produkter. Hvis et geogjerde krysses, er kjøretøyet utenfor regelverket, og sjåføren kan bli varslet.

✅ Kan du komme på andre bruksområder for geogjerder?

Azure Maps, tjenesten du brukte i forrige leksjon for å visualisere GPS-data, lar deg definere geogjerder og teste om et punkt er innenfor eller utenfor geogjerdet.

## Definer et geogjerde

Geogjerder defineres ved hjelp av GeoJSON, det samme som punktene som ble lagt til kartet i forrige leksjon. I dette tilfellet, i stedet for å være en `FeatureCollection` av `Point`-verdier, er det en `FeatureCollection` som inneholder en `Polygon`.

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

Hvert punkt på polygonet defineres som et lengdegrad-, breddegrad-par i en array, og disse punktene er i en array som settes som `coordinates`. I en `Point` i forrige leksjon var `coordinates` en array som inneholdt 2 verdier, breddegrad og lengdegrad. For en `Polygon` er det en array av arrays som inneholder 2 verdier, lengdegrad og breddegrad.

> 💁 Husk, GeoJSON bruker `lengdegrad, breddegrad` for punkter, ikke `breddegrad, lengdegrad`.

Polygon-koordinatene har alltid én mer oppføring enn antall punkter på polygonet, med den siste oppføringen som den samme som den første, for å lukke polygonet. For eksempel, for et rektangel vil det være 5 punkter.

![Et rektangel med koordinater](../../../../../translated_images/no/polygon-points.302193da381cb415.png)

I bildet ovenfor er det et rektangel. Polygon-koordinatene starter øverst til venstre ved 47,-122, deretter beveger seg til høyre til 47,-121, deretter ned til 46,-121, deretter til venstre til 46,-122, og til slutt tilbake til startpunktet ved 47,-122. Dette gir polygonet 5 punkter – øverst til venstre, øverst til høyre, nederst til høyre, nederst til venstre, og til slutt øverst til venstre for å lukke det.

✅ Prøv å lage en GeoJSON-polygon rundt hjemmet eller skolen din. Bruk et verktøy som [GeoJSON.io](https://geojson.io/).

### Oppgave – definer et geogjerde

For å bruke et geogjerde i Azure Maps, må det først lastes opp til Azure Maps-kontoen din. Når det er lastet opp, vil du få en unik ID som du kan bruke til å teste et punkt mot geogjerdet. For å laste opp geogjerder til Azure Maps, må du bruke kartets web-API. Du kan kalle Azure Maps web-API ved hjelp av et verktøy som [curl](https://curl.se).

> 🎓 Curl er et kommandolinjeverktøy for å gjøre forespørsler mot web-endepunkter.

1. Hvis du bruker Linux, macOS eller en nyere versjon av Windows 10, har du sannsynligvis curl installert allerede. Kjør følgende fra terminalen eller kommandolinjen for å sjekke:

    ```sh
    curl --version
    ```

    Hvis du ikke ser versjonsinformasjon for curl, må du installere det fra [curl nedlastingssiden](https://curl.se/download.html).

    > 💁 Hvis du er erfaren med Postman, kan du bruke det i stedet hvis du foretrekker det.

1. Lag en GeoJSON-fil som inneholder en polygon. Du vil teste denne med GPS-sensoren din, så lag en polygon rundt din nåværende lokasjon. Du kan enten lage en manuelt ved å redigere GeoJSON-eksempelet gitt ovenfor, eller bruke et verktøy som [GeoJSON.io](https://geojson.io/).

    GeoJSON må inneholde en `FeatureCollection` som inneholder en `Feature` med en `geometry` av typen `Polygon`.

    Du **MÅ** også legge til et `properties`-element på samme nivå som `geometry`-elementet, og dette må inneholde en `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Hvis du bruker [GeoJSON.io](https://geojson.io/), må du manuelt legge til dette elementet i det tomme `properties`-elementet, enten etter at du har lastet ned JSON-filen, eller i JSON-editoren i appen.

    Denne `geometryId` må være unik i denne filen. Du kan laste opp flere geogjerder som flere `Features` i `FeatureCollection` i samme GeoJSON-fil, så lenge hver har en forskjellig `geometryId`. Polygoner kan ha samme `geometryId` hvis de lastes opp fra en annen fil på et annet tidspunkt.

1. Lagre denne filen som `geofence.json`, og naviger til der den er lagret i terminalen eller konsollen.

1. Kjør følgende curl-kommando for å opprette geogjerdet:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Erstatt `<subscription_key>` i URL-en med API-nøkkelen for Azure Maps-kontoen din.

    URL-en brukes til å laste opp kartdata via `https://atlas.microsoft.com/mapData/upload`-API-et. Forespørselen inkluderer en `api-version`-parameter for å spesifisere hvilken Azure Maps-API som skal brukes, dette er for å tillate API-et å endre seg over tid, men opprettholde bakoverkompatibilitet. Dataformatet som lastes opp settes til `geojson`.

    Dette vil kjøre POST-forespørselen til opplastings-API-et og returnere en liste over responsoverskrifter som inkluderer en overskrift kalt `location`.

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

    > 🎓 Når du kaller et web-endepunkt, kan du sende parametere til forespørselen ved å legge til en `?` etterfulgt av nøkkel-verdi-par som `key=value`, og skille nøkkel-verdi-parene med en `&`.

1. Azure Maps behandler ikke dette umiddelbart, så du må sjekke om opplastingsforespørselen er ferdig ved å bruke URL-en gitt i `location`-overskriften. Gjør en GET-forespørsel til denne lokasjonen for å se statusen. Du må legge til abonnementsnøkkelen din til slutten av `location`-URL-en ved å legge til `&subscription-key=<subscription_key>` til slutten, og erstatte `<subscription_key>` med API-nøkkelen for Azure Maps-kontoen din. Kjør følgende kommando:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Erstatt `<location>` med verdien av `location`-overskriften, og `<subscription_key>` med API-nøkkelen for Azure Maps-kontoen din.

1. Sjekk verdien av `status` i responsen. Hvis den ikke er `Succeeded`, vent et minutt og prøv igjen.

1. Når statusen kommer tilbake som `Succeeded`, se på `resourceLocation` fra responsen. Dette inneholder detaljer om den unike ID-en (kjent som UDID) for GeoJSON-objektet. UDID er verdien etter `metadata/`, og ikke inkludert `api-version`. For eksempel, hvis `resourceLocation` var:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Da ville UDID være `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Ta vare på denne UDID-en, da du vil trenge den for å teste geogjerdet.

## Test punkter mot et geogjerde

Når polygonet er lastet opp til Azure Maps, kan du teste et punkt for å se om det er innenfor eller utenfor geogjerdet. Dette gjør du ved å sende en web-API-forespørsel, der du sender inn UDID-en til geogjerdet, og breddegrad og lengdegrad for punktet som skal testes.

Når du gjør denne forespørselen, kan du også sende en verdi kalt `searchBuffer`. Dette angir hvor nøyaktig API-et skal være når det returnerer resultater. Grunnen til dette er at GPS ikke er helt nøyaktig, og noen ganger kan lokasjoner være feil med flere meter eller mer. Standardverdien for søkebufferen er 50m, men du kan sette verdier fra 0m til 500m.

Når resultater returneres fra API-forespørselen, er en av delene av resultatet en `distance` målt til det nærmeste punktet på kanten av geogjerdet, med en positiv verdi hvis punktet er utenfor geogjerdet, og negativ hvis det er innenfor geogjerdet. Hvis denne avstanden er mindre enn søkebufferen, returneres den faktiske avstanden i meter, ellers er verdien 999 eller -999. 999 betyr at punktet er utenfor geogjerdet med mer enn søkebufferen, -999 betyr at det er innenfor geogjerdet med mer enn søkebufferen.

![Et geogjerde med en 50m søkebuffer rundt det](../../../../../translated_images/no/search-buffer-and-distance.e6a79af3898183c7.png)

I bildet ovenfor har geogjerdet en 50m søkebuffer.

* Et punkt i midten av geogjerdet, godt innenfor søkebufferen, har en avstand på **-999**.
* Et punkt godt utenfor søkebufferen har en avstand på **999**.
* Et punkt innenfor geogjerdet og innenfor søkebufferen, 6m fra geogjerdet, har en avstand på **6m**.
* Et punkt utenfor geogjerdet og innenfor søkebufferen, 39m fra geogjerdet, har en avstand på **39m**.

Det er viktig å kjenne avstanden til kanten av geogjerdet og kombinere dette med annen informasjon, som andre GPS-avlesninger, hastighet og veidata, når du tar beslutninger basert på kjøretøyets lokasjon.

For eksempel, tenk deg GPS-avlesninger som viser at et kjøretøy kjørte langs en vei som ender opp ved siden av et geogjerde. Hvis en enkelt GPS-verdi er unøyaktig og plasserer kjøretøyet innenfor geogjerdet, til tross for at det ikke er noen kjøretøystilgang, kan det ignoreres.

![En GPS-spor som viser et kjøretøy som passerer Microsoft-campus på 520, med GPS-avlesninger langs veien bortsett fra én på campus, innenfor et geogjerde](../../../../../translated_images/no/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.png)
På bildet ovenfor er det en geofence over en del av Microsoft-campus. Den røde linjen viser en lastebil som kjører langs 520, med sirkler som representerer GPS-avlesningene. De fleste av disse er nøyaktige og langs 520, med én unøyaktig avlesning inne i geofencen. Det er ingen måte denne avlesningen kan være korrekt – det finnes ingen veier som gjør det mulig for lastebilen å plutselig svinge av fra 520 inn på campus og deretter tilbake til 520. Koden som sjekker denne geofencen må ta tidligere avlesninger i betraktning før den handler basert på resultatene fra geofence-testen.

✅ Hvilke ekstra data ville du trenge for å sjekke om en GPS-avlesning kan anses som korrekt?

### Oppgave – test punkter mot en geofence

1. Start med å bygge URL-en for web-API-spørringen. Formatet er:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Erstatt `<subscription_key>` med API-nøkkelen for din Azure Maps-konto.

    Erstatt `<UDID>` med UDID-en til geofencen fra den forrige oppgaven.

    Erstatt `<lat>` og `<lon>` med breddegrad og lengdegrad du ønsker å teste.

    Denne URL-en bruker `https://atlas.microsoft.com/spatial/geofence/json`-API-et for å gjøre en spørring mot en geofence definert med GeoJSON. Den retter seg mot API-versjonen `1.0`. Parameteren `deviceId` er påkrevd og bør være navnet på enheten breddegraden og lengdegraden kommer fra.

    Standard søkebuffer er 50m, og du kan endre dette ved å legge til en ekstra parameter `searchBuffer=<distance>`, hvor `<distance>` er søkebufferavstanden i meter, fra 0 til 500.

1. Bruk curl for å gjøre en GET-forespørsel til denne URL-en:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Hvis du får en svarkode `BadRequest` med en feil som:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > mangler GeoJSON-filen din seksjonen `properties` med `geometryId`. Du må fikse GeoJSON-filen, deretter gjenta trinnene ovenfor for å laste opp på nytt og få en ny UDID.

1. Svaret vil inneholde en liste over `geometries`, én for hver polygon definert i GeoJSON-filen som ble brukt til å opprette geofencen. Hver geometri har tre interessante felt: `distance`, `nearestLat` og `nearestLon`.

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

    * `nearestLat` og `nearestLon` er breddegrad og lengdegrad til et punkt på kanten av geofencen som er nærmest stedet som testes.

    * `distance` er avstanden fra stedet som testes til det nærmeste punktet på kanten av geofencen. Negative tall betyr innenfor geofencen, positive utenfor. Denne verdien vil være mindre enn 50 (standard søkebuffer), eller 999.

1. Gjenta dette flere ganger med steder både innenfor og utenfor geofencen.

## Bruk geofencer fra serverløs kode

Du kan nå legge til en ny trigger i Functions-appen din for å teste IoT Hub GPS-hendelsesdata mot geofencen.

### Konsumentgrupper

Som du husker fra tidligere leksjoner, lar IoT Hub deg spille av hendelser som har blitt mottatt av huben, men ikke behandlet. Men hva skjer hvis flere triggere kobler seg til? Hvordan vet den hvilken som har behandlet hvilke hendelser?

Svaret er at den ikke kan! I stedet kan du definere flere separate tilkoblinger for å lese av hendelser, og hver av dem kan administrere avspilling av uleste meldinger. Disse kalles *konsumentgrupper*. Når du kobler til endepunktet, kan du spesifisere hvilken konsumentgruppe du vil koble til. Hver komponent i applikasjonen din vil koble til en annen konsumentgruppe.

![Én IoT Hub med 3 konsumentgrupper som distribuerer de samme meldingene til 3 forskjellige funksjonsapper](../../../../../translated_images/no/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.png)

I teorien kan opptil 5 applikasjoner koble seg til hver konsumentgruppe, og de vil alle motta meldinger når de ankommer. Det er beste praksis å ha kun én applikasjon som får tilgang til hver konsumentgruppe for å unngå duplisert meldingsbehandling og sikre at alle køede meldinger behandles korrekt ved omstart. For eksempel, hvis du lanserte Functions-appen din lokalt samtidig som den kjører i skyen, ville begge behandle meldinger, noe som fører til dupliserte blobber lagret i lagringskontoen.

Hvis du ser på `function.json`-filen for IoT Hub-triggeren du opprettet i en tidligere leksjon, vil du se konsumentgruppen i seksjonen for event hub-triggerbinding:

```json
"consumerGroup": "$Default"
```

Når du oppretter en IoT Hub, får du konsumentgruppen `$Default` opprettet som standard. Hvis du vil legge til en ekstra trigger, kan du gjøre dette ved å bruke en ny konsumentgruppe.

> 💁 I denne leksjonen vil du bruke en annen funksjon for å teste geofencen enn den som brukes til å lagre GPS-dataene. Dette er for å vise hvordan man bruker konsumentgrupper og separerer koden for å gjøre den enklere å lese og forstå. I en produksjonsapplikasjon finnes det mange måter du kan arkitektere dette på – legge begge på én funksjon, bruke en trigger på lagringskontoen for å kjøre en funksjon for å sjekke geofencen, eller bruke flere funksjoner. Det finnes ingen "riktig måte", det avhenger av resten av applikasjonen din og dine behov.

### Oppgave – opprett en ny konsumentgruppe

1. Kjør følgende kommando for å opprette en ny konsumentgruppe kalt `geofence` for din IoT Hub:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Erstatt `<hub_name>` med navnet du brukte for din IoT Hub.

1. Hvis du vil se alle konsumentgruppene for en IoT Hub, kjør følgende kommando:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Erstatt `<hub_name>` med navnet du brukte for din IoT Hub. Dette vil liste opp alle konsumentgruppene.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Når du kjørte IoT Hub-hendelsesmonitoren i en tidligere leksjon, koblet den seg til konsumentgruppen `$Default`. Dette var grunnen til at du ikke kan kjøre hendelsesmonitoren og en hendelsestrigger samtidig. Hvis du vil kjøre begge, kan du bruke andre konsumentgrupper for alle funksjonsappene dine og beholde `$Default` for hendelsesmonitoren.

### Oppgave – opprett en ny IoT Hub-trigger

1. Legg til en ny IoT Hub-hendelsestrigger i din `gps-trigger`-funksjonsapp som du opprettet i en tidligere leksjon. Kall denne funksjonen `geofence-trigger`.

    > ⚠️ Du kan referere til [instruksjonene for å opprette en IoT Hub-hendelsestrigger fra prosjekt 2, leksjon 5 hvis nødvendig](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Konfigurer IoT Hub-tilkoblingsstrengen i `function.json`-filen. `local.settings.json` deles mellom alle triggere i funksjonsappen.

1. Oppdater verdien av `consumerGroup` i `function.json`-filen for å referere til den nye konsumentgruppen `geofence`:

    ```json
    "consumerGroup": "geofence"
    ```

1. Du vil trenge abonnementsnøkkelen for din Azure Maps-konto i denne triggeren, så legg til en ny oppføring i `local.settings.json`-filen kalt `MAPS_KEY`.

1. Kjør funksjonsappen for å sikre at den kobler til og behandler meldinger. `iot-hub-trigger` fra den tidligere leksjonen vil også kjøre og laste opp blobber til lagring.

    > For å unngå dupliserte GPS-avlesninger i bloblagring, kan du stoppe funksjonsappen du har kjørende i skyen. For å gjøre dette, bruk følgende kommando:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Erstatt `<functions_app_name>` med navnet du brukte for din funksjonsapp.
    >
    > Du kan starte den på nytt senere med følgende kommando:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Erstatt `<functions_app_name>` med navnet du brukte for din funksjonsapp.

### Oppgave – test geofencen fra triggeren

Tidligere i denne leksjonen brukte du curl for å gjøre en spørring mot en geofence for å se om et punkt var innenfor eller utenfor. Du kan gjøre en lignende webforespørsel fra triggeren din.

1. For å gjøre en spørring mot geofencen, trenger du dens UDID. Legg til en ny oppføring i `local.settings.json`-filen kalt `GEOFENCE_UDID` med denne verdien.

1. Åpne `__init__.py`-filen fra den nye `geofence-trigger`-triggeren.

1. Legg til følgende import øverst i filen:

    ```python
    import json
    import os
    import requests
    ```

    `requests`-pakken lar deg gjøre web-API-kall. Azure Maps har ikke en Python SDK, så du må gjøre web-API-kall for å bruke det fra Python-kode.

1. Legg til følgende 2 linjer i starten av `main`-metoden for å hente Maps-abonnementsnøkkelen:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Inne i `for event in events`-løkken, legg til følgende for å hente breddegrad og lengdegrad fra hver hendelse:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Denne koden konverterer JSON fra hendelsesinnholdet til et ordbokformat og henter deretter `lat` og `lon` fra `gps`-feltet.

1. Når du bruker `requests`, i stedet for å bygge opp en lang URL som du gjorde med curl, kan du bruke bare URL-delen og sende parameterne som en ordbok. Legg til følgende kode for å definere URL-en som skal kalles og konfigurere parameterne:

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

    Elementene i `params`-ordboken vil samsvare med nøkkel-verdi-parene du brukte da du kalte web-API-et via curl.

1. Legg til følgende linjer med kode for å kalle web-API-et:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Dette kaller URL-en med parameterne og får tilbake et svarobjekt.

1. Legg til følgende kode under dette:

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

    Denne koden antar én geometri og henter avstanden fra den ene geometrien. Den logger deretter forskjellige meldinger basert på avstanden.

1. Kjør denne koden. Du vil se i loggeutdataene om GPS-koordinatene er innenfor eller utenfor geofencen, med en avstand hvis punktet er innenfor 50m. Prøv denne koden med forskjellige geofencer basert på plasseringen av GPS-sensoren din, prøv å flytte sensoren (for eksempel koblet til WiFi fra en mobiltelefon, eller med forskjellige koordinater på den virtuelle IoT-enheten) for å se endringer.

1. Når du er klar, distribuer denne koden til funksjonsappen din i skyen. Ikke glem å distribuere de nye applikasjonsinnstillingene.

    > ⚠️ Du kan referere til [instruksjonene for opplasting av applikasjonsinnstillinger fra prosjekt 2, leksjon 5 hvis nødvendig](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Du kan referere til [instruksjonene for distribusjon av funksjonsappen din fra prosjekt 2, leksjon 5 hvis nødvendig](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Du finner denne koden i [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions)-mappen.

---

## 🚀 Utfordring

I denne leksjonen la du til én geofence ved hjelp av en GeoJSON-fil med én polygon. Du kan laste opp flere polygoner samtidig, så lenge de har forskjellige `geometryId`-verdier i `properties`-seksjonen.

Prøv å laste opp en GeoJSON-fil med flere polygoner og juster koden din for å finne hvilken polygon GPS-koordinatene er nærmest eller innenfor.

## Etterforelesningsquiz

[Etterforelesningsquiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Gjennomgang og selvstudium

* Les mer om geofencer og noen av deres bruksområder på [Geofencing-siden på Wikipedia](https://en.wikipedia.org/wiki/Geo-fence).
* Les mer om Azure Maps geofencing-API på [Microsoft Azure Maps Spatial - Get Geofence-dokumentasjonen](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Les mer om konsumentgrupper i [Funksjoner og terminologi i Azure Event Hubs - Event consumers-dokumentasjonen på Microsoft Docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Oppgave

[Send varsler ved hjelp av Twilio](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.