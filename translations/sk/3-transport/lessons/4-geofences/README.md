# Geofences

![Prehľad lekcie v sketchnote](../../../../../translated_images/sk/lesson-14.63980c5150ae3c15.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

Toto video poskytuje prehľad o geofencoch a ich použití v Azure Maps, čo sú témy, ktoré budú pokryté v tejto lekcii:

[![Geofencing s Azure Maps z relácie Microsoft Developer IoT](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Kliknite na obrázok vyššie a pozrite si video

## Kvíz pred lekciou

[Kvíz pred lekciou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Úvod

V posledných troch lekciách ste použili IoT na lokalizáciu kamiónov, ktoré prepravujú vaše produkty z farmy do spracovateľského centra. Zaznamenali ste GPS údaje, poslali ich do cloudu na uloženie a vizualizovali ich na mape. Ďalším krokom na zvýšenie efektivity vášho dodávateľského reťazca je získanie upozornenia, keď sa kamión blíži k spracovateľskému centru, aby tím, ktorý ho má vyložiť, mohol byť pripravený s vysokozdvižnými vozíkmi a ďalším vybavením hneď po príchode vozidla. Týmto spôsobom môžu rýchlo vyložiť náklad a vy neplatíte za čakajúci kamión a vodiča.

V tejto lekcii sa naučíte o geofencoch - definovaných geospaceálnych oblastiach, ako je napríklad oblasť v dosahu 2 km jazdy od spracovateľského centra, a ako testovať, či GPS súradnice sú vo vnútri alebo mimo geofence, aby ste mohli zistiť, či váš GPS senzor dorazil alebo opustil oblasť.

V tejto lekcii sa budeme venovať:

* [Čo sú geofences](../../../../../3-transport/lessons/4-geofences)
* [Definovanie geofence](../../../../../3-transport/lessons/4-geofences)
* [Testovanie bodov voči geofence](../../../../../3-transport/lessons/4-geofences)
* [Použitie geofencov zo serverless kódu](../../../../../3-transport/lessons/4-geofences)

> 🗑 Toto je posledná lekcia v tomto projekte, takže po dokončení tejto lekcie a zadania nezabudnite vyčistiť svoje cloudové služby. Budete ich potrebovať na dokončenie zadania, takže sa uistite, že ho najskôr dokončíte.
>
> Ak je to potrebné, pozrite si [príručku na vyčistenie projektu](../../../clean-up.md) pre pokyny, ako to urobiť.

## Čo sú geofences

Geofence je virtuálny obvod pre geografickú oblasť v reálnom svete. Geofences môžu byť kruhy definované ako bod a polomer (napríklad kruh s priemerom 100m okolo budovy) alebo polygóny pokrývajúce oblasť, ako je školská zóna, mestské hranice alebo univerzitný či kancelársky kampus.

![Príklady geofencov zobrazujúce kruhový geofence okolo obchodu Microsoft a polygonový geofence okolo západného kampusu Microsoft](../../../../../translated_images/sk/geofence-examples.172fbc534665769f.webp)

> 💁 Možno ste už používali geofences bez toho, aby ste o tom vedeli. Ak ste nastavili pripomienku pomocou aplikácie iOS Reminders alebo Google Keep na základe polohy, použili ste geofence. Tieto aplikácie nastavia geofence na základe zadanej polohy a upozornia vás, keď váš telefón vstúpi do geofence.

Existuje mnoho dôvodov, prečo by ste chceli vedieť, že vozidlo je vo vnútri alebo mimo geofence:

* Príprava na vykladanie - získanie upozornenia, že vozidlo dorazilo na miesto, umožňuje tímu pripraviť sa na vyloženie vozidla, čím sa znižuje čas čakania vozidla. To môže vodičovi umožniť vykonať viac dodávok za deň s menším časom čakania.
* Daňová zhoda - niektoré krajiny, ako napríklad Nový Zéland, účtujú cestné dane za dieselové vozidlá na základe hmotnosti vozidla pri jazde iba na verejných cestách. Použitie geofencov umožňuje sledovať najazdené kilometre na verejných cestách oproti súkromným cestám na miestach, ako sú farmy alebo oblasti ťažby dreva.
* Monitorovanie krádeže - ak by vozidlo malo zostať iba v určitej oblasti, napríklad na farme, a opustí geofence, mohlo byť ukradnuté.
* Zhoda s polohou - niektoré časti pracoviska, farmy alebo továrne môžu byť zakázané pre určité vozidlá, napríklad udržiavanie vozidiel, ktoré prepravujú umelé hnojivá a pesticídy, mimo polí s organickými produktmi. Ak sa geofence vstúpi, vozidlo je mimo zhody a vodič môže byť upozornený.

✅ Dokážete si predstaviť ďalšie využitia geofencov?

Azure Maps, služba, ktorú ste použili v poslednej lekcii na vizualizáciu GPS údajov, vám umožňuje definovať geofences a testovať, či je bod vo vnútri alebo mimo geofence.

## Definovanie geofence

Geofences sú definované pomocou GeoJSON, rovnako ako body, ktoré boli pridané na mapu v predchádzajúcej lekcii. V tomto prípade, namiesto `FeatureCollection` bodov, ide o `FeatureCollection` obsahujúce `Polygon`.

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

Každý bod na polygóne je definovaný ako dvojica zemepisnej dĺžky a šírky v poli, a tieto body sú v poli, ktoré je nastavené ako `coordinates`. V `Point` v predchádzajúcej lekcii bolo `coordinates` pole obsahujúce 2 hodnoty, zemepisnú šírku a dĺžku, pre `Polygon` je to pole polí obsahujúce 2 hodnoty, zemepisnú dĺžku a šírku.

> 💁 Pamätajte, GeoJSON používa `zemepisnú dĺžku, zemepisnú šírku` pre body, nie `zemepisnú šírku, zemepisnú dĺžku`

Pole súradníc polygónu má vždy o 1 záznam viac ako počet bodov na polygóne, pričom posledný záznam je rovnaký ako prvý, čím sa polygón uzavrie. Napríklad pre obdĺžnik by tam bolo 5 bodov.

![Obdĺžnik so súradnicami](../../../../../translated_images/sk/polygon-points.302193da381cb415.webp)

Na obrázku vyššie je obdĺžnik. Súradnice polygónu začínajú v ľavom hornom rohu na 47,-122, potom sa posúvajú doprava na 47,-121, potom dole na 46,-121, potom doprava na 46,-122, a nakoniec späť hore na počiatočný bod na 47,-122. To dáva polygónu 5 bodov - ľavý horný, pravý horný, pravý dolný, ľavý dolný a nakoniec ľavý horný na uzavretie.

✅ Skúste vytvoriť GeoJSON polygón okolo vášho domova alebo školy. Použite nástroj ako [GeoJSON.io](https://geojson.io/).

### Úloha - definovanie geofence

Na použitie geofence v Azure Maps ho najskôr musíte nahrať do svojho účtu Azure Maps. Po nahraní získate jedinečné ID, ktoré môžete použiť na testovanie bodu voči geofence. Na nahranie geofencov do Azure Maps musíte použiť webové API mapy. Môžete zavolať webové API Azure Maps pomocou nástroja [curl](https://curl.se).

> 🎓 Curl je nástroj príkazového riadku na vykonávanie požiadaviek na webové koncové body

1. Ak používate Linux, macOS alebo novšiu verziu Windows 10, pravdepodobne už máte curl nainštalovaný. Spustite nasledujúci príkaz z terminálu alebo príkazového riadku na kontrolu:

    ```sh
    curl --version
    ```

    Ak nevidíte informácie o verzii curl, budete ho musieť nainštalovať zo [stránky na stiahnutie curl](https://curl.se/download.html).

    > 💁 Ak máte skúsenosti s Postmanom, môžete ho použiť namiesto curl, ak preferujete.

1. Vytvorte GeoJSON súbor obsahujúci polygón. Budete ho testovať pomocou vášho GPS senzora, takže vytvorte polygón okolo vašej aktuálnej polohy. Môžete ho vytvoriť manuálne úpravou GeoJSON príkladu uvedeného vyššie alebo použiť nástroj ako [GeoJSON.io](https://geojson.io).

    GeoJSON musí obsahovať `FeatureCollection`, obsahujúce `Feature` s `geometry` typu `Polygon`.

    Musíte tiež pridať prvok `properties` na rovnakej úrovni ako prvok `geometry`, a tento musí obsahovať `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Ak použijete [GeoJSON.io](https://geojson.io), budete musieť manuálne pridať tento prvok do prázdneho `properties` prvku, buď po stiahnutí JSON súboru, alebo v JSON editore v aplikácii.

    Tento `geometryId` musí byť jedinečný v tomto súbore. Môžete nahrať viacero geofencov ako viacero `Features` v `FeatureCollection` v tom istom GeoJSON súbore, pokiaľ má každý z nich iný `geometryId`. Polygóny môžu mať rovnaký `geometryId`, ak sú nahrané z iného súboru v inom čase.

1. Uložte tento súbor ako `geofence.json` a prejdite do miesta, kde je uložený, vo vašom termináli alebo konzole.

1. Spustite nasledujúci curl príkaz na vytvorenie GeoFence:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Nahraďte `<subscription_key>` v URL API kľúčom vášho účtu Azure Maps.

    URL sa používa na nahranie mapových údajov cez API `https://atlas.microsoft.com/mapData/upload`. Požiadavka obsahuje parameter `api-version` na špecifikáciu, ktorú verziu API Azure Maps použiť, aby sa API mohlo časom meniť, ale zachovať spätnú kompatibilitu. Formát údajov, ktorý sa nahráva, je nastavený na `geojson`.

    Tento príkaz vykoná POST požiadavku na API nahrávania a vráti zoznam hlavičiek odpovede, ktorý obsahuje hlavičku nazvanú `location`.

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

    > 🎓 Pri volaní webového koncového bodu môžete odovzdať parametre požiadavky pridaním `?` nasledovaného dvojicami kľúč-hodnota ako `key=value`, oddelenými `&`.

1. Azure Maps nespracováva túto požiadavku okamžite, takže budete musieť skontrolovať, či požiadavka na nahranie bola dokončená, pomocou URL uvedeného v hlavičke `location`. Vykonajte GET požiadavku na túto URL na kontrolu stavu. Musíte pridať váš API kľúč na koniec URL `location` pridaním `&subscription-key=<subscription_key>` na koniec, pričom `<subscription_key>` nahradíte API kľúčom vášho účtu Azure Maps. Spustite nasledujúci príkaz:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Nahraďte `<location>` hodnotou hlavičky `location` a `<subscription_key>` API kľúčom vášho účtu Azure Maps.

1. Skontrolujte hodnotu `status` v odpovedi. Ak nie je `Succeeded`, počkajte minútu a skúste znova.

1. Keď sa stav vráti ako `Succeeded`, pozrite sa na `resourceLocation` z odpovede. Obsahuje podrobnosti o jedinečnom ID (známom ako UDID) pre GeoJSON objekt. UDID je hodnota po `metadata/`, bez zahrnutia `api-version`. Napríklad, ak `resourceLocation` bolo:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Potom UDID by bolo `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Uchovajte si kópiu tohto UDID, pretože ho budete potrebovať na testovanie geofence.

## Testovanie bodov voči geofence

Keď je polygón nahraný do Azure Maps, môžete testovať bod, či je vo vnútri alebo mimo geofence. Urobíte to vykonaním požiadavky na webové API, pričom odovzdáte UDID geofence a zemepisnú šírku a dĺžku bodu na testovanie.

Pri vykonávaní tejto požiadavky môžete tiež odovzdať hodnotu nazvanú `searchBuffer`. Táto hodnota určuje, akú presnosť má API pri vracaní výsledkov. Dôvodom je, že GPS nie je dokonale presné a niekedy môžu byť polohy nepresné o niekoľko metrov alebo viac. Predvolená hodnota pre `searchBuffer` je 50m, ale môžete nastaviť hodnoty od 0m do 500m.

Keď API vráti výsledky, jedna z častí výsledku je `distance`, meraná k najbližšiemu bodu na okraji geofence, s kladnou hodnotou, ak je bod mimo geofence, a zápornou hodnotou, ak je vo vnútri geofence. Ak je táto vzdialenosť menšia ako `searchBuffer`, skutočná vzdialenosť sa vráti v metroch, inak je hodnota 999 alebo -999. 999 znamená, že bod je mimo geofence o viac ako `searchBuffer`, -999 znamená, že je vo vnútri geofence o viac ako `searchBuffer`.

![Geofence s 50m vyhľadávacím bufferom okolo neho](../../../../../translated_images/sk/search-buffer-and-distance.e6a79af3898183c7.webp)

Na obrázku vyššie má geofence 50m vyhľadávací buffer.

* Bod v strede geofence, dobre vo vnútri vyhľadávacieho bufferu, má vzdialenosť **-999**
* Bod dobre mimo vyhľadávacieho bufferu má vzdialenosť **999**
* Bod vo vnútri geofence a vo vnútri vyhľadávacieho bufferu, 6m od geofence, má vzdialenosť **6m**
* Bod mimo geofence a vo vnútri vyhľadávacieho bufferu, 39m od geofence, má vzdialenosť **39m**

Je dôležité poznať vzdialenosť k okraju geofence a kombinovať ju s ďalšími informáciami, ako sú iné GPS hodnoty, rýchlosť a údaje o cestách, pri rozhodovaní na základe polohy vozidla.

Napríklad si predstavte GPS hodnoty ukazujúce, že vozidlo jazdilo po ceste, ktorá vedie vedľa geofence. Ak jedna GPS hodnota je nepresná a umiestni vozidlo vo vnútri geofence, napriek tomu, že tam nie je prístup pre vozidlá, môže byť ignorovaná.

![GPS trasa ukazujúca vozidlo prechádzajúce okolo kampusu Microsoft na 520, s GPS hodnotami pozdĺž cesty okrem jednej na kampuse, vo vnútri geofence](../../../../../translated_images/sk/geofence-crossing-inaccurate-gps.6a3ed911202ad9ca.webp)
Na vyššie uvedenom obrázku je geofence nad časťou kampusu Microsoft. Červená čiara ukazuje nákladné auto jazdiace po 520, pričom kruhy označujú GPS údaje. Väčšina z nich je presná a nachádza sa na 520, s jedným nepresným údajom vo vnútri geofence. Tento údaj nemôže byť správny – neexistujú žiadne cesty, po ktorých by sa nákladné auto mohlo náhle odkloniť z 520 na kampus a potom späť na 520. Kód, ktorý kontroluje tento geofence, bude musieť zohľadniť predchádzajúce údaje predtým, než bude konať na základe výsledkov testu geofence.

✅ Aké ďalšie údaje by ste potrebovali skontrolovať, aby ste zistili, či GPS údaj môže byť považovaný za správny?

### Úloha - testovanie bodov voči geofence

1. Začnite vytvorením URL pre dotaz na webové API. Formát je:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Nahraďte `<subscription_key>` API kľúčom pre váš účet Azure Maps.

    Nahraďte `<UDID>` UDID geofence z predchádzajúcej úlohy.

    Nahraďte `<lat>` a `<lon>` zemepisnou šírkou a dĺžkou, ktoré chcete testovať.

    Táto URL používa API `https://atlas.microsoft.com/spatial/geofence/json` na dotazovanie geofence definovaného pomocou GeoJSON. Cieli na verziu API `1.0`. Parameter `deviceId` je povinný a mal by byť názvom zariadenia, z ktorého pochádzajú zemepisná šírka a dĺžka.

    Predvolený vyhľadávací buffer je 50m, a môžete ho zmeniť pridaním ďalšieho parametra `searchBuffer=<distance>`, kde `<distance>` je vzdialenosť vyhľadávacieho bufferu v metroch, od 0 do 500.

1. Použite curl na vykonanie GET požiadavky na túto URL:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Ak dostanete odpoveďový kód `BadRequest` s chybou:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > potom váš GeoJSON chýba sekcia `properties` s `geometryId`. Budete musieť opraviť váš GeoJSON, potom zopakovať vyššie uvedené kroky na opätovné nahranie a získanie nového UDID.

1. Odpoveď bude obsahovať zoznam `geometries`, jeden pre každý polygon definovaný v GeoJSON použitom na vytvorenie geofence. Každá geometria má 3 zaujímavé polia: `distance`, `nearestLat` a `nearestLon`.

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

    * `nearestLat` a `nearestLon` sú zemepisná šírka a dĺžka bodu na okraji geofence, ktorý je najbližšie k testovanej lokalite.

    * `distance` je vzdialenosť od testovanej lokality k najbližšiemu bodu na okraji geofence. Záporné čísla znamenajú, že bod je vo vnútri geofence, kladné mimo. Táto hodnota bude menšia ako 50 (predvolený vyhľadávací buffer) alebo 999.

1. Opakujte tento proces viackrát s lokalitami vo vnútri a mimo geofence.

## Použitie geofence zo serverless kódu

Teraz môžete pridať nový trigger do vašej Functions aplikácie na testovanie GPS údajov z IoT Hub voči geofence.

### Consumer groups

Ako si pamätáte z predchádzajúcich lekcií, IoT Hub umožňuje prehrávať udalosti, ktoré boli prijaté hubom, ale neboli spracované. Ale čo sa stane, ak sa pripojí viacero triggerov? Ako bude vedieť, ktorý spracoval ktoré udalosti?

Odpoveď je, že to nevie! Namiesto toho môžete definovať viacero samostatných pripojení na čítanie udalostí, pričom každé z nich môže spravovať prehrávanie neprečítaných správ. Tieto sa nazývajú *consumer groups*. Keď sa pripojíte k endpointu, môžete špecifikovať, ku ktorému consumer group sa chcete pripojiť. Každá súčasť vašej aplikácie sa pripojí k inému consumer group.

![Jeden IoT Hub s 3 consumer groups distribuujúcimi rovnaké správy do 3 rôznych Functions aplikácií](../../../../../translated_images/sk/consumer-groups.a3262e26fc27ba20.webp)

Teoreticky sa môže k každému consumer group pripojiť až 5 aplikácií, a všetky dostanú správy, keď prídu. Najlepšou praxou je mať iba jednu aplikáciu prístupnú k každému consumer group, aby sa zabránilo duplicitnému spracovaniu správ a zabezpečilo, že pri reštarte budú všetky čakajúce správy správne spracované. Napríklad, ak spustíte svoju Functions aplikáciu lokálne, ako aj v cloude, obe by spracovávali správy, čo by viedlo k duplicitným blobom uloženým v úložnom účte.

Ak si prezriete súbor `function.json` pre IoT Hub trigger, ktorý ste vytvorili v predchádzajúcej lekcii, uvidíte consumer group v sekcii event hub trigger binding:

```json
"consumerGroup": "$Default"
```

Keď vytvoríte IoT Hub, predvolene sa vytvorí consumer group `$Default`. Ak chcete pridať ďalší trigger, môžete ho pridať pomocou nového consumer group.

> 💁 V tejto lekcii použijete inú funkciu na testovanie geofence ako tú, ktorá sa používa na ukladanie GPS údajov. Toto je na ukážku použitia consumer groups a oddelenia kódu, aby bol ľahšie čitateľný a pochopiteľný. V produkčnej aplikácii existuje mnoho spôsobov, ako by ste to mohli navrhnúť – umiestnením oboch do jednej funkcie, použitím triggeru na úložnom účte na spustenie funkcie na kontrolu geofence, alebo použitím viacerých funkcií. Neexistuje "správny spôsob", záleží na zvyšku vašej aplikácie a vašich potrebách.

### Úloha - vytvorenie nového consumer group

1. Spustite nasledujúci príkaz na vytvorenie nového consumer group s názvom `geofence` pre váš IoT Hub:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom, ktorý ste použili pre váš IoT Hub.

1. Ak chcete vidieť všetky consumer groups pre IoT Hub, spustite nasledujúci príkaz:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom, ktorý ste použili pre váš IoT Hub. Toto zobrazí všetky consumer groups.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Keď ste v predchádzajúcej lekcii spustili monitor udalostí IoT Hub, pripojil sa k consumer group `$Default`. Preto nemôžete spustiť monitor udalostí a trigger udalostí. Ak chcete spustiť oboje, môžete použiť iné consumer groups pre všetky vaše Functions aplikácie a ponechať `$Default` pre monitor udalostí.

### Úloha - vytvorenie nového IoT Hub triggeru

1. Pridajte nový IoT Hub event trigger do vašej `gps-trigger` Functions aplikácie, ktorú ste vytvorili v predchádzajúcej lekcii. Nazvite túto funkciu `geofence-trigger`.

    > ⚠️ Môžete sa odvolať na [pokyny na vytvorenie IoT Hub event triggeru z projektu 2, lekcia 5, ak je to potrebné](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Nakonfigurujte IoT Hub connection string v súbore `function.json`. Súbor `local.settings.json` je zdieľaný medzi všetkými triggermi v Functions aplikácii.

1. Aktualizujte hodnotu `consumerGroup` v súbore `function.json`, aby odkazovala na nový consumer group `geofence`:

    ```json
    "consumerGroup": "geofence"
    ```

1. Budete potrebovať subscription key pre váš účet Azure Maps v tomto triggeri, takže pridajte nový záznam do súboru `local.settings.json` s názvom `MAPS_KEY`.

1. Spustite Functions aplikáciu, aby ste sa uistili, že sa pripája a spracováva správy. Trigger `iot-hub-trigger` z predchádzajúcej lekcie bude tiež bežať a nahrávať blob do úložiska.

    > Aby ste sa vyhli duplicitným GPS údajom v blob úložisku, môžete zastaviť Functions aplikáciu, ktorú máte spustenú v cloude. Na to použite nasledujúci príkaz:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Nahraďte `<functions_app_name>` názvom, ktorý ste použili pre vašu Functions aplikáciu.
    >
    > Neskôr ju môžete znova spustiť nasledujúcim príkazom:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Nahraďte `<functions_app_name>` názvom, ktorý ste použili pre vašu Functions aplikáciu.

### Úloha - testovanie geofence z triggeru

V predchádzajúcej časti tejto lekcie ste použili curl na dotazovanie geofence, aby ste zistili, či sa bod nachádza vo vnútri alebo mimo. Podobnú webovú požiadavku môžete vykonať z vnútra vášho triggeru.

1. Na dotazovanie geofence potrebujete jeho UDID. Pridajte nový záznam do súboru `local.settings.json` s názvom `GEOFENCE_UDID` s touto hodnotou.

1. Otvorte súbor `__init__.py` z nového triggeru `geofence-trigger`.

1. Pridajte nasledujúci import na začiatok súboru:

    ```python
    import json
    import os
    import requests
    ```

    Balík `requests` umožňuje vykonávať webové API požiadavky. Azure Maps nemá Python SDK, musíte vykonávať webové API požiadavky na jeho použitie z Python kódu.

1. Pridajte nasledujúce 2 riadky na začiatok metódy `main`, aby ste získali subscription key pre Maps:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Vo vnútri cyklu `for event in events` pridajte nasledujúce na získanie zemepisnej šírky a dĺžky z každého eventu:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Tento kód konvertuje JSON z tela eventu na slovník a potom extrahuje `lat` a `lon` z poľa `gps`.

1. Pri použití `requests`, namiesto vytvárania dlhej URL ako ste to robili s curl, môžete použiť iba časť URL a odovzdať parametre ako slovník. Pridajte nasledujúci kód na definovanie URL na volanie a konfiguráciu parametrov:

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

    Položky v slovníku `params` budú zodpovedať kľúčovým hodnotám, ktoré ste použili pri volaní webového API cez curl.

1. Pridajte nasledujúce riadky kódu na volanie webového API:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Toto volá URL s parametrami a získava späť objekt odpovede.

1. Pridajte nasledujúci kód pod toto:

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

    Tento kód predpokladá 1 geometriu a extrahuje vzdialenosť z tejto jednej geometrie. Potom zapisuje rôzne správy na základe vzdialenosti.

1. Spustite tento kód. V logovacom výstupe uvidíte, či GPS súradnice sú vo vnútri alebo mimo geofence, s vzdialenosťou, ak je bod do 50m. Vyskúšajte tento kód s rôznymi geofence na základe polohy vášho GPS senzora, skúste presunúť senzor (napríklad pripojený k WiFi z mobilného telefónu alebo s rôznymi súradnicami na virtuálnom IoT zariadení), aby ste videli túto zmenu.

1. Keď budete pripravení, nasadte tento kód do vašej Functions aplikácie v cloude. Nezabudnite nasadiť nové Application Settings.

    > ⚠️ Môžete sa odvolať na [pokyny na nahranie Application Settings z projektu 2, lekcia 5, ak je to potrebné](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Môžete sa odvolať na [pokyny na nasadenie vašej Functions aplikácie z projektu 2, lekcia 5, ak je to potrebné](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Tento kód nájdete v priečinku [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Výzva

V tejto lekcii ste pridali jeden geofence pomocou GeoJSON súboru s jedným polygon. Môžete nahrať viacero polygonov naraz, pokiaľ majú rôzne hodnoty `geometryId` v sekcii `properties`.

Vyskúšajte nahrať GeoJSON súbor s viacerými polygonmi a upravte váš kód tak, aby našiel, ku ktorému polygonu sú GPS súradnice najbližšie alebo v ktorom sa nachádzajú.

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Prehľad & Samoštúdium

* Prečítajte si viac o geofence a niektorých ich použitiach na [stránke Geofencing na Wikipédii](https://en.wikipedia.org/wiki/Geo-fence).
* Prečítajte si viac o Azure Maps geofencing API na [dokumentácii Microsoft Azure Maps Spatial - Get Geofence](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Prečítajte si viac o consumer groups v [dokumentácii Microsoft docs o funkciách a terminológii v Azure Event Hubs - Event consumers](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Zadanie

[Posielanie notifikácií pomocou Twilio](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.