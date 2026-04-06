# Geografske ograje

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-14.63980c5150ae3c15.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

Ta video ponuja pregled geografskih ograj in njihove uporabe v Azure Maps, kar bo obravnavano v tej lekciji:

[![Geografske ograje z Azure Maps iz oddaje Microsoft Developer IoT](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Kliknite zgornjo sliko za ogled videa

## Predhodni kviz

[Predhodni kviz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Uvod

V zadnjih treh lekcijah ste uporabili IoT za lociranje tovornjakov, ki prevažajo vaše pridelke z vaše kmetije do predelovalnega centra. Zajeli ste GPS podatke, jih poslali v oblak za shranjevanje in jih vizualizirali na zemljevidu. Naslednji korak za povečanje učinkovitosti vaše dobavne verige je prejem opozorila, ko se tovornjak približuje predelovalnemu centru, da je ekipa pripravljena z viličarji in drugo opremo takoj, ko vozilo prispe. Na ta način lahko hitro razložijo tovornjak, vi pa ne plačujete za čakanje tovornjaka in voznika.

V tej lekciji se boste naučili o geografskih ograjah - določenih geosocialnih območjih, kot je območje znotraj 2 km vožnje od predelovalnega centra, in kako preveriti, ali so GPS koordinate znotraj ali zunaj geografske ograje, da lahko ugotovite, ali je vaš GPS senzor prispel ali zapustil območje.

V tej lekciji bomo obravnavali:

* [Kaj so geografske ograje](../../../../../3-transport/lessons/4-geofences)
* [Določanje geografske ograje](../../../../../3-transport/lessons/4-geofences)
* [Preverjanje točk glede na geografsko ograjo](../../../../../3-transport/lessons/4-geofences)
* [Uporaba geografskih ograj iz strežniške kode](../../../../../3-transport/lessons/4-geofences)

> 🗑 To je zadnja lekcija v tem projektu, zato po zaključku te lekcije in naloge ne pozabite počistiti svojih oblačnih storitev. Storitve boste potrebovali za dokončanje naloge, zato se prepričajte, da jo najprej dokončate.
>
> Če je potrebno, si oglejte [vodnik za čiščenje projekta](../../../clean-up.md) za navodila, kako to storiti.

## Kaj so geografske ograje

Geografska ograja je virtualni obod za resnično geografsko območje. Geografske ograje so lahko krogi, določeni kot točka in radij (na primer krog s premerom 100 m okoli stavbe), ali poligon, ki pokriva območje, kot je šolska cona, mestne meje ali univerzitetni ali pisarniški kampus.

![Primeri geografskih ograj, ki prikazujejo krožno ograjo okoli Microsoftove trgovine in poligonsko ograjo okoli zahodnega kampusa Microsofta](../../../../../translated_images/sl/geofence-examples.172fbc534665769f.webp)

> 💁 Morda ste že uporabljali geografske ograje, ne da bi to vedeli. Če ste nastavili opomnik z aplikacijo za opomnike iOS ali Google Keep na podlagi lokacije, ste uporabili geografsko ograjo. Te aplikacije nastavijo geografsko ograjo na podlagi podane lokacije in vas opozorijo, ko vaš telefon vstopi v geografsko ograjo.

Obstaja veliko razlogov, zakaj bi želeli vedeti, ali je vozilo znotraj ali zunaj geografske ograje:

* Priprava na razkladanje - prejem obvestila, da je vozilo prispelo na lokacijo, omogoča ekipi, da se pripravi na razkladanje vozila, kar zmanjša čas čakanja vozila. To lahko vozniku omogoči več dostav na dan z manj čakanja.
* Davčna skladnost - nekatere države, kot je Nova Zelandija, zaračunavajo cestne davke za dizelska vozila na podlagi teže vozila, ko vozijo le po javnih cestah. Uporaba geografskih ograj omogoča sledenje prevoženim kilometrom po javnih cestah v primerjavi z zasebnimi cestami na lokacijah, kot so kmetije ali gozdarska območja.
* Spremljanje kraje - če bi vozilo moralo ostati na določenem območju, kot je kmetija, in zapusti geografsko ograjo, je morda bilo ukradeno.
* Skladnost z lokacijo - nekateri deli delovišča, kmetije ali tovarne so lahko prepovedani za določena vozila, na primer za vozila, ki prevažajo umetna gnojila in pesticide, da se izognejo poljem z ekološkimi pridelki. Če se vstopi v geografsko ograjo, je vozilo zunaj skladnosti in voznik je lahko obveščen.

✅ Ali lahko pomislite na druge uporabe geografskih ograj?

Azure Maps, storitev, ki ste jo uporabili v prejšnji lekciji za vizualizacijo GPS podatkov, vam omogoča, da določite geografske ograje in nato preverite, ali je točka znotraj ali zunaj geografske ograje.

## Določanje geografske ograje

Geografske ograje so določene z uporabo GeoJSON, enako kot točke, ki so bile dodane na zemljevid v prejšnji lekciji. V tem primeru namesto `FeatureCollection` točk vsebuje `FeatureCollection` s poligonom.

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

Vsaka točka na poligonu je določena kot par dolžine in širine v polju, te točke pa so v polju, ki je nastavljeno kot `coordinates`. V `Point` v prejšnji lekciji je bil `coordinates` polje, ki je vsebovalo 2 vrednosti, širino in dolžino, za `Polygon` pa je polje polj, ki vsebuje 2 vrednosti, dolžino in širino.

> 💁 Zapomnite si, GeoJSON uporablja `dolžino, širino` za točke, ne `širino, dolžino`.

Poligonovo polje koordinat vedno vsebuje 1 vnos več kot število točk na poligonu, pri čemer je zadnji vnos enak prvemu, kar zapre poligon. Na primer, za pravokotnik bi bilo 5 točk.

![Pravokotnik s koordinatami](../../../../../translated_images/sl/polygon-points.302193da381cb415.webp)

Na zgornji sliki je pravokotnik. Koordinate poligona se začnejo zgoraj levo pri 47,-122, nato se premaknejo desno na 47,-121, nato navzdol na 46,-121, nato desno na 46, -122, nato nazaj gor na začetno točko pri 47, -122. To daje poligonu 5 točk - zgoraj levo, zgoraj desno, spodaj desno, spodaj levo, nato zgoraj levo, da ga zapre.

✅ Poskusite ustvariti GeoJSON poligon okoli svojega doma ali šole. Uporabite orodje, kot je [GeoJSON.io](https://geojson.io/).

### Naloga - določanje geografske ograje

Za uporabo geografske ograje v Azure Maps jo je najprej treba naložiti v vaš Azure Maps račun. Ko je naložena, boste prejeli edinstven ID, ki ga lahko uporabite za preverjanje točke glede na geografsko ograjo. Za nalaganje geografskih ograj v Azure Maps morate uporabiti spletni API za zemljevide. Klic spletnega API-ja Azure Maps lahko izvedete z orodjem, imenovanim [curl](https://curl.se).

> 🎓 Curl je orodje ukazne vrstice za izvajanje zahtevkov proti spletnim končnim točkam

1. Če uporabljate Linux, macOS ali novejšo različico Windows 10, imate curl verjetno že nameščen. Za preverjanje zaženite naslednje iz terminala ali ukazne vrstice:

    ```sh
    curl --version
    ```

    Če ne vidite informacij o različici za curl, ga boste morali namestiti s [strani za prenose curl](https://curl.se/download.html).

    > 💁 Če ste izkušeni z orodjem Postman, ga lahko uporabite namesto tega, če želite.

1. Ustvarite datoteko GeoJSON, ki vsebuje poligon. To boste testirali z vašim GPS senzorjem, zato ustvarite poligon okoli vaše trenutne lokacije. Lahko ga ustvarite ročno z urejanjem zgornjega primera GeoJSON ali uporabite orodje, kot je [GeoJSON.io](https://geojson.io).

    GeoJSON mora vsebovati `FeatureCollection`, ki vsebuje `Feature` z `geometry` tipa `Polygon`.

    Prav tako **MORATE** dodati element `properties` na isti ravni kot element `geometry`, ta pa mora vsebovati `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Če uporabljate [GeoJSON.io](https://geojson.io/), boste morali ta element ročno dodati v prazen element `properties`, bodisi po prenosu datoteke JSON bodisi v urejevalniku JSON v aplikaciji.

    Ta `geometryId` mora biti edinstven v tej datoteki. Več geografskih ograj lahko naložite kot več `Features` v `FeatureCollection` v isti datoteki GeoJSON, dokler ima vsaka drugačen `geometryId`. Poligoni lahko imajo isti `geometryId`, če so naloženi iz druge datoteke ob drugem času.

1. Shranite to datoteko kot `geofence.json` in se v terminalu ali konzoli pomaknite do mesta, kjer je shranjena.

1. Zaženite naslednji ukaz curl za ustvarjanje GeoFence:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Zamenjajte `<subscription_key>` v URL-ju z API ključem za vaš Azure Maps račun.

    URL se uporablja za nalaganje podatkov zemljevida prek API-ja `https://atlas.microsoft.com/mapData/upload`. Klic vključuje parameter `api-version`, da določi, kateri API Azure Maps uporabiti, kar omogoča spreminjanje API-ja skozi čas ob ohranjanju združljivosti za nazaj. Format podatkov, ki se nalaga, je nastavljen na `geojson`.

    To bo izvedlo zahtevo POST na API za nalaganje in vrnilo seznam odgovornih glave, ki vključuje glavo, imenovano `location`.

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

    > 🎓 Pri klicanju spletne končne točke lahko parametre klica posredujete tako, da dodate `?`, ki mu sledijo pari ključ-vrednost kot `key=value`, pri čemer pare ključ-vrednost ločite z `&`.

1. Azure Maps tega ne obdela takoj, zato boste morali preveriti, ali je zahteva za nalaganje končana, tako da uporabite URL, podan v glavi `location`. Izvedite zahtevo GET na to lokacijo, da preverite stanje. Na konec URL-ja `location` boste morali dodati svoj naročniški ključ, tako da dodate `&subscription-key=<subscription_key>` na konec, pri čemer `<subscription_key>` zamenjate z API ključem za vaš Azure Maps račun. Zaženite naslednji ukaz:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Zamenjajte `<location>` z vrednostjo glave `location` in `<subscription_key>` z API ključem za vaš Azure Maps račun.

1. Preverite vrednost `status` v odgovoru. Če ni `Succeeded`, počakajte minuto in poskusite znova.

1. Ko se stanje vrne kot `Succeeded`, si oglejte `resourceLocation` iz odgovora. Ta vsebuje podrobnosti o edinstvenem ID-ju (znanem kot UDID) za GeoJSON objekt. UDID je vrednost po `metadata/`, brez `api-version`. Na primer, če je `resourceLocation` bil:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Potem bi bil UDID `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Shranite kopijo tega UDID, saj ga boste potrebovali za testiranje geografske ograje.

## Preverjanje točk glede na geografsko ograjo

Ko je poligon naložen v Azure Maps, lahko preverite točko, da vidite, ali je znotraj ali zunaj geografske ograje. To storite tako, da izvedete zahtevo spletnega API-ja, pri čemer posredujete UDID geografske ograje ter širino in dolžino točke za testiranje.

Pri izvedbi te zahteve lahko posredujete tudi vrednost, imenovano `searchBuffer`. Ta pove API-ju Maps, kako natančen naj bo pri vračanju rezultatov. Razlog za to je, da GPS ni popolnoma natančen, včasih pa so lokacije lahko odmaknjene za metre ali več. Privzeta vrednost za iskalni buffer je 50 m, vendar lahko nastavite vrednosti od 0 m do 500 m.

Ko so rezultati vrnjeni iz klica API-ja, je eden od delov rezultata `distance`, izmerjen do najbližje točke na robu geografske ograje, s pozitivno vrednostjo, če je točka zunaj geografske ograje, negativno, če je znotraj geografske ograje. Če je ta razdalja manjša od iskalnega bufferja, se vrne dejanska razdalja v metrih, sicer je vrednost 999 ali -999. 999 pomeni, da je točka zunaj geografske ograje za več kot iskalni buffer, -999 pomeni, da je znotraj geografske ograje za več kot iskalni buffer.

![Geografska ograja z iskalnim bufferjem 50 m okoli nje](../../../../../translated_images/sl/search-buffer-and-distance.e6a79af3898183c7.webp)

Na zgornji sliki ima geografska ograja iskalni buffer 50 m.

* Točka v središču geografske ograje, dobro znotraj iskalnega bufferja, ima razdaljo **-999**
* Točka dobro zunaj iskalnega bufferja ima razdaljo **999**
* Točka znotraj geografske ograje in znotraj iskalnega bufferja, 6 m od geografske ograje, ima razdaljo **6 m**
* Točka zunaj geografske ograje in znotraj iskalnega bufferja, 39 m od geografske ograje, ima razdaljo **39 m**

Pomembno je poznati razdaljo do roba geografske ograje in to kombinirati z drugimi informacijami, kot so drugi GPS odčitki, hitrost in podatki o cestah, pri sprejemanju odločitev na podlagi lokacije vozila.

Na primer, predstavljajte si GPS odčitke, ki kažejo, da je vozilo vozilo po cesti, ki poteka ob geografski ograji. Če je en sam GPS odčitek nenatančen in postavi vozilo znotraj geografske ograje, kljub temu da ni dostopa za vozila, ga je mogoče prezreti.

![GPS sled, ki prikazuje vozilo, ki prečka kampus Microsofta na 520, z GPS odčitki vzdolž ceste, razen enega na kampusu, znotraj geografske ograje](../../../../../translated_images/sl/geofence-crossing-inaccurate-gps.6a3ed911202ad9ca.webp)
Na zgornji sliki je geografska ograja nad delom kampusa Microsoft. Rdeča črta prikazuje tovornjak, ki vozi po cesti 520, s krogi, ki označujejo GPS odčitke. Večina teh odčitkov je natančnih in se nahaja ob cesti 520, z enim nenatančnim odčitkom znotraj geografske ograje. Ta odčitek ne more biti pravilen – ni cest, po katerih bi se tovornjak nenadoma odmaknil od ceste 520 na kampus, nato pa se vrnil na cesto 520. Koda, ki preverja to geografsko ograjo, bo morala upoštevati prejšnje odčitke, preden ukrepa na podlagi rezultatov testa geografske ograje.

✅ Katere dodatne podatke bi potrebovali za preverjanje, ali je GPS odčitek lahko veljaven?

### Naloga - testiranje točk glede na geografsko ograjo

1. Začnite z izdelavo URL-ja za poizvedbo spletnega API-ja. Format je:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Zamenjajte `<subscription_key>` z API ključem za vaš račun Azure Maps.

    Zamenjajte `<UDID>` z UDID geografske ograje iz prejšnje naloge.

    Zamenjajte `<lat>` in `<lon>` z zemljepisno širino in dolžino, ki ju želite testirati.

    Ta URL uporablja API `https://atlas.microsoft.com/spatial/geofence/json` za poizvedbo geografske ograje, definirane z GeoJSON. Cilja na različico API-ja `1.0`. Parameter `deviceId` je obvezen in mora biti ime naprave, iz katere prihajata zemljepisna širina in dolžina.

    Privzeti iskalni buffer je 50 m, kar lahko spremenite z dodajanjem dodatnega parametra `searchBuffer=<distance>`, kjer nastavite `<distance>` na razdaljo iskalnega bufferja v metrih, od 0 do 500.

1. Uporabite curl za izvedbo GET zahteve na ta URL:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Če dobite odzivno kodo `BadRequest` z napako:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > potem vaš GeoJSON manjka odsek `properties` z `geometryId`. Popraviti boste morali GeoJSON, nato ponoviti zgornje korake za ponovno nalaganje in pridobitev novega UDID.

1. Odziv bo vseboval seznam `geometries`, enega za vsak poligon, definiran v GeoJSON, uporabljenem za ustvarjanje geografske ograje. Vsaka geometrija ima 3 zanimiva polja: `distance`, `nearestLat` in `nearestLon`.

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

    * `nearestLat` in `nearestLon` sta zemljepisna širina in dolžina točke na robu geografske ograje, ki je najbližja testirani lokaciji.

    * `distance` je razdalja od testirane lokacije do najbližje točke na robu geografske ograje. Negativne vrednosti pomenijo znotraj geografske ograje, pozitivne zunaj. Ta vrednost bo manjša od 50 (privzeti iskalni buffer) ali 999.

1. To večkrat ponovite z lokacijami znotraj in zunaj geografske ograje.

## Uporaba geografskih ograj iz strežniške kode

Zdaj lahko dodate nov sprožilec v vašo aplikacijo Functions za testiranje podatkov GPS dogodkov IoT Hub glede na geografsko ograjo.

### Potrošniške skupine

Kot se spomnite iz prejšnjih lekcij, IoT Hub omogoča ponovno predvajanje dogodkov, ki so bili prejeti v hub, vendar niso obdelani. Kaj pa, če se poveže več sprožilcev? Kako bo vedel, kateri je obdelal katere dogodke?

Odgovor je, da ne more! Namesto tega lahko definirate več ločenih povezav za branje dogodkov, pri čemer vsaka upravlja ponovno predvajanje neprebranih sporočil. Te se imenujejo *potrošniške skupine*. Ko se povežete z endpointom, lahko določite, katero potrošniško skupino želite uporabiti. Vsaka komponenta vaše aplikacije se bo povezala z drugo potrošniško skupino.

![En IoT Hub s 3 potrošniškimi skupinami, ki razdeljujejo ista sporočila na 3 različne funkcijske aplikacije](../../../../../translated_images/sl/consumer-groups.a3262e26fc27ba20.webp)

Teoretično se lahko do 5 aplikacij poveže z vsako potrošniško skupino, in vse bodo prejele sporočila, ko prispejo. Najboljša praksa je, da vsaka aplikacija dostopa do ene potrošniške skupine, da se izognete podvajanju obdelave sporočil in zagotovite, da so ob ponovnem zagonu vsa sporočila v čakalni vrsti pravilno obdelana. Na primer, če bi zagnali svojo aplikacijo Functions lokalno, hkrati pa jo izvajali v oblaku, bi obe obdelovali sporočila, kar bi vodilo do podvojenih blobov, shranjenih v računu za shranjevanje.

Če pregledate datoteko `function.json` za sprožilec IoT Hub, ki ste ga ustvarili v prejšnji lekciji, boste videli potrošniško skupino v odseku sprožilca dogodkov Event Hub:

```json
"consumerGroup": "$Default"
```

Ko ustvarite IoT Hub, se privzeto ustvari potrošniška skupina `$Default`. Če želite dodati dodatni sprožilec, lahko to storite z novo potrošniško skupino.

> 💁 V tej lekciji boste uporabili drugo funkcijo za testiranje geografske ograje kot tisto, ki se uporablja za shranjevanje podatkov GPS. To je prikaz uporabe potrošniških skupin in ločevanja kode za lažje branje in razumevanje. V produkcijski aplikaciji obstaja veliko načinov, kako bi to lahko zasnovali – združitev obeh v eno funkcijo, uporaba sprožilca na računu za shranjevanje za zagon funkcije za preverjanje geografske ograje ali uporaba več funkcij. Ni 'pravega načina', odvisno je od preostale aplikacije in vaših potreb.

### Naloga - ustvarite novo potrošniško skupino

1. Za ustvarjanje nove potrošniške skupine z imenom `geofence` za vaš IoT Hub zaženite naslednji ukaz:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Zamenjajte `<hub_name>` z imenom, ki ste ga uporabili za vaš IoT Hub.

1. Če želite videti vse potrošniške skupine za IoT Hub, zaženite naslednji ukaz:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Zamenjajte `<hub_name>` z imenom, ki ste ga uporabili za vaš IoT Hub. To bo prikazalo seznam vseh potrošniških skupin.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Ko ste v prejšnji lekciji zagnali monitor dogodkov IoT Hub, se je povezal s potrošniško skupino `$Default`. Zaradi tega ne morete hkrati zagnati monitorja dogodkov in sprožilca dogodkov. Če želite zagnati oba, lahko uporabite druge potrošniške skupine za vse vaše funkcijske aplikacije in obdržite `$Default` za monitor dogodkov.

### Naloga - ustvarite nov sprožilec IoT Hub

1. Dodajte nov sprožilec dogodkov IoT Hub v vašo funkcijsko aplikacijo `gps-trigger`, ki ste jo ustvarili v prejšnji lekciji. To funkcijo poimenujte `geofence-trigger`.

    > ⚠️ Lahko se sklicujete na [navodila za ustvarjanje sprožilca dogodkov IoT Hub iz projekta 2, lekcija 5, če je potrebno](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Konfigurirajte povezovalni niz IoT Hub v datoteki `function.json`. Datoteka `local.settings.json` je skupna med vsemi sprožilci v funkcijski aplikaciji.

1. Posodobite vrednost `consumerGroup` v datoteki `function.json`, da se sklicuje na novo potrošniško skupino `geofence`:

    ```json
    "consumerGroup": "geofence"
    ```

1. Za ta sprožilec boste potrebovali naročniški ključ za vaš račun Azure Maps, zato dodajte nov vnos v datoteko `local.settings.json` z imenom `MAPS_KEY`.

1. Zaženite funkcijsko aplikacijo, da zagotovite, da se povezuje in obdeluje sporočila. Sprožilec `iot-hub-trigger` iz prejšnje lekcije bo prav tako deloval in nalagal bloke v shranjevanje.

    > Da se izognete podvojenim GPS odčitkom v shranjevanju blokov, lahko ustavite funkcijsko aplikacijo, ki jo imate zagnano v oblaku. To storite z naslednjim ukazom:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Zamenjajte `<functions_app_name>` z imenom, ki ste ga uporabili za vašo funkcijsko aplikacijo.
    >
    > Kasneje jo lahko ponovno zaženete z naslednjim ukazom:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Zamenjajte `<functions_app_name>` z imenom, ki ste ga uporabili za vašo funkcijsko aplikacijo.

### Naloga - testirajte geografsko ograjo iz sprožilca

V prejšnji lekciji ste uporabili curl za poizvedbo geografske ograje, da preverite, ali se točka nahaja znotraj ali zunaj. Podobno spletno zahtevo lahko izvedete znotraj vašega sprožilca.

1. Za poizvedbo geografske ograje potrebujete njen UDID. Dodajte nov vnos v datoteko `local.settings.json` z imenom `GEOFENCE_UDID` in to vrednost.

1. Odprite datoteko `__init__.py` iz novega sprožilca `geofence-trigger`.

1. Na vrh datoteke dodajte naslednji uvoz:

    ```python
    import json
    import os
    import requests
    ```

    Paket `requests` omogoča izvajanje spletnih API klicev. Azure Maps nima Python SDK-ja, zato morate za uporabo iz Python kode izvajati spletne API klice.

1. Na začetek metode `main` dodajte naslednji dve vrstici za pridobitev naročniškega ključa Maps:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Znotraj zanke `for event in events` dodajte naslednje za pridobitev zemljepisne širine in dolžine iz vsakega dogodka:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Ta koda pretvori JSON iz telesa dogodka v slovar, nato pa iz polja `gps` izvleče `lat` in `lon`.

1. Pri uporabi `requests`, namesto da sestavljate dolg URL, kot ste to storili s curl, lahko uporabite samo del URL-ja in parametre posredujete kot slovar. Dodajte naslednjo kodo za definiranje URL-ja za klic in konfiguracijo parametrov:

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

    Elementi v slovarju `params` bodo ustrezali ključnim vrednostim, ki ste jih uporabili pri klicanju spletnega API-ja prek curl.

1. Dodajte naslednje vrstice kode za klic spletnega API-ja:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    To pokliče URL s parametri in vrne odzivni objekt.

1. Pod to kodo dodajte naslednje:

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

    Ta koda predpostavlja 1 geometrijo in iz te geometrije izvleče razdaljo. Nato beleži različna sporočila glede na razdaljo.

1. Zaženite to kodo. V izhodu dnevnika boste videli, ali so GPS koordinate znotraj ali zunaj geografske ograje, z razdaljo, če je točka znotraj 50 m. Preizkusite to kodo z različnimi geografskimi ograjami glede na lokacijo vašega GPS senzorja, poskusite premakniti senzor (na primer povezan z WiFi iz mobilnega telefona ali z različnimi koordinatami na virtualni IoT napravi), da vidite spremembe.

1. Ko ste pripravljeni, to kodo naložite v vašo funkcijsko aplikacijo v oblaku. Ne pozabite naložiti novih nastavitev aplikacije.

    > ⚠️ Lahko se sklicujete na [navodila za nalaganje nastavitev aplikacije iz projekta 2, lekcija 5, če je potrebno](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Lahko se sklicujete na [navodila za nalaganje vaše funkcijske aplikacije iz projekta 2, lekcija 5, če je potrebno](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 To kodo najdete v mapi [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Izziv

V tej lekciji ste dodali eno geografsko ograjo z datoteko GeoJSON, ki vsebuje en poligon. Lahko naložite več poligonov hkrati, dokler imajo različne vrednosti `geometryId` v odseku `properties`.

Poskusite naložiti datoteko GeoJSON z več poligoni in prilagodite svojo kodo, da ugotovite, kateremu poligonu so GPS koordinate najbližje ali znotraj.

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Pregled in samostojno učenje

* Preberite več o geografskih ograjah in nekaterih njihovih primerih uporabe na [strani o geografskih ograjah na Wikipediji](https://en.wikipedia.org/wiki/Geo-fence).
* Preberite več o API-ju za geografske ograje Azure Maps na [dokumentaciji Microsoft Azure Maps Spatial - Get Geofence](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Preberite več o potrošniških skupinah v [Funkcije in terminologija v Azure Event Hubs - dokumentacija o potrošnikih dogodkov na Microsoft Docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Naloga

[Pošiljanje obvestil z uporabo Twilio](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.