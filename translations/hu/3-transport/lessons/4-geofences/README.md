<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-27T21:45:40+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "hu"
}
-->
# Geokerítések

![A lecke vázlatos áttekintése](../../../../../translated_images/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.hu.jpg)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ez a videó bemutatja a geokerítések működését és azok használatát az Azure Maps-ben, amelyekről ebben a leckében lesz szó:

[![Geokerítések az Azure Maps segítségével a Microsoft Developer IoT show-ból](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Kattints a fenti képre a videó megtekintéséhez

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Bevezetés

Az elmúlt három leckében az IoT segítségével nyomon követted a teherautókat, amelyek a farmodról a feldolgozóközpontba szállítják a termékeidet. GPS-adatokat gyűjtöttél, elküldted azokat a felhőbe tárolásra, és megjelenítetted egy térképen. A következő lépés az ellátási láncod hatékonyságának növelésében az, hogy értesítést kapj, amikor egy teherautó közeledik a feldolgozóközponthoz, hogy a kirakodáshoz szükséges személyzet készen álljon targoncákkal és egyéb eszközökkel, amint a jármű megérkezik. Így gyorsan kirakodhatnak, és nem kell fizetned a teherautó és a sofőr várakozásáért.

Ebben a leckében megismered a geokerítéseket – meghatározott földrajzi régiókat, például egy feldolgozóközpont 2 km-es körzetét –, és azt, hogyan tesztelheted, hogy a GPS-koordináták egy geokerítésen belül vagy kívül vannak-e, hogy láthasd, a GPS-érzékelőd megérkezett-e egy területre vagy elhagyta azt.

Ebben a leckében a következőkről lesz szó:

* [Mik azok a geokerítések](../../../../../3-transport/lessons/4-geofences)
* [Geokerítés meghatározása](../../../../../3-transport/lessons/4-geofences)
* [Pontok tesztelése egy geokerítés ellen](../../../../../3-transport/lessons/4-geofences)
* [Geokerítések használata szerver nélküli kódból](../../../../../3-transport/lessons/4-geofences)

> 🗑 Ez a projekt utolsó leckéje, ezért a lecke és a feladat befejezése után ne felejtsd el törölni a felhőszolgáltatásaidat. A feladat elvégzéséhez szükséged lesz ezekre a szolgáltatásokra, ezért először győződj meg róla, hogy befejezted a feladatot.
>
> Ha szükséges, olvasd el [a projekt törlésének útmutatóját](../../../clean-up.md) az utasításokért.

## Mik azok a geokerítések

A geokerítés egy virtuális határ egy valós földrajzi régió körül. A geokerítések lehetnek körök, amelyeket egy pont és egy sugár határoz meg (például egy 100 méter széles kör egy épület körül), vagy poligonok, amelyek egy területet fednek le, például egy iskolaövezetet, városhatárt, egyetemi vagy irodai kampuszt.

![Néhány geokerítés példa, amely egy kör alakú geokerítést mutat a Microsoft vállalati boltja körül, és egy poligon geokerítést a Microsoft nyugati kampusza körül](../../../../../translated_images/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.hu.png)

> 💁 Lehet, hogy már használtál geokerítéseket anélkül, hogy tudtál volna róla. Ha például az iOS emlékeztetők alkalmazásában vagy a Google Keepben helyalapú emlékeztetőt állítottál be, akkor geokerítést használtál. Ezek az alkalmazások a megadott hely alapján geokerítést állítanak fel, és értesítenek, amikor a telefonod belép a geokerítésbe.

Számos oka lehet annak, hogy miért szeretnéd tudni, hogy egy jármű egy geokerítésen belül vagy kívül van:

* Kirakodás előkészítése – ha értesítést kapsz arról, hogy egy jármű megérkezett a helyszínre, a személyzet felkészülhet a jármű kirakodására, csökkentve a jármű várakozási idejét. Ez lehetővé teszi, hogy a sofőr kevesebb várakozási idővel több szállítást végezzen egy nap alatt.
* Adózási megfelelés – egyes országok, például Új-Zéland, az útdíjakat csak a közutakon megtett távolság alapján számítják ki dízeljárművek esetében. A geokerítések használatával nyomon követheted a közutakon megtett távolságot a magánutakon, például farmokon vagy fakitermelő területeken megtett távolsággal szemben.
* Lopásfigyelés – ha egy járműnek csak egy bizonyos területen, például egy farmon belül kellene maradnia, és elhagyja a geokerítést, akkor lehet, hogy ellopták.
* Helyszíni megfelelés – egy munkaterület, farm vagy gyár bizonyos részei bizonyos járművek számára tiltottak lehetnek, például a műtrágyát és növényvédő szereket szállító járműveket távol kell tartani a bioélelmiszert termelő mezőktől. Ha egy geokerítésbe belépnek, akkor a jármű megszegi a szabályokat, és a sofőrt értesíteni lehet.

✅ Tudsz más felhasználási módokat kitalálni a geokerítésekre?

Az Azure Maps, amelyet az előző leckében használtál a GPS-adatok megjelenítésére, lehetővé teszi geokerítések meghatározását, majd annak tesztelését, hogy egy pont a geokerítésen belül vagy kívül van-e.

## Geokerítés meghatározása

A geokerítéseket GeoJSON formátumban határozzuk meg, ugyanúgy, mint az előző leckében a térképre felvett pontokat. Ebben az esetben azonban nem `Point` értékekből álló `FeatureCollection`, hanem egy `Polygon`-t tartalmazó `FeatureCollection`.

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

A poligon minden pontját egy hosszúsági és szélességi párként definiáljuk egy tömbben, és ezek a pontok egy tömbben vannak, amelyet `coordinates`-ként állítunk be. Az előző leckében a `Point` esetében a `coordinates` egy két értéket tartalmazó tömb volt (szélesség és hosszúság), míg a `Polygon` esetében ez egy tömbök tömbje, amely két értéket tartalmaz (hosszúság, szélesség).

> 💁 Ne feledd, hogy a GeoJSON a pontok esetében `hosszúság, szélesség` sorrendet használ, nem pedig `szélesség, hosszúság` sorrendet.

A poligon koordináták tömbje mindig egy bejegyzéssel több, mint a poligon pontjainak száma, az utolsó bejegyzés megegyezik az elsővel, lezárva a poligont. Például egy téglalap esetében 5 pont lenne.

![Egy téglalap koordinátákkal](../../../../../translated_images/polygon-points.302193da381cb415.hu.png)

A fenti képen egy téglalap látható. A poligon koordináták a bal felső sarokban kezdődnek 47,-122-nél, majd jobbra haladnak 47,-121-hez, majd lefelé 46,-121-hez, majd balra 46,-122-höz, végül vissza az indulóponthoz 47,-122-nél. Ez 5 pontot ad a poligonnak – bal felső, jobb felső, jobb alsó, bal alsó, majd bal felső a lezáráshoz.

✅ Próbálj meg egy GeoJSON poligont létrehozni az otthonod vagy az iskolád körül. Használj egy eszközt, például a [GeoJSON.io](https://geojson.io/) oldalt.

### Feladat – geokerítés meghatározása

Ahhoz, hogy egy geokerítést használni tudj az Azure Maps-ben, először fel kell töltened azt az Azure Maps fiókodba. A feltöltés után kapsz egy egyedi azonosítót, amelyet használhatsz a pont tesztelésére a geokerítés ellen. A geokerítések feltöltéséhez az Azure Maps-be a térképek webes API-ját kell használnod. Az Azure Maps webes API-ját egy [curl](https://curl.se) nevű eszközzel hívhatod meg.

> 🎓 A Curl egy parancssori eszköz, amely lehetővé teszi webes végpontok elérését.

1. Ha Linuxot, macOS-t vagy egy újabb Windows 10 verziót használsz, valószínűleg már telepítve van a curl. Futtasd a következő parancsot a terminálban vagy a parancssorban az ellenőrzéshez:

    ```sh
    curl --version
    ```

    Ha nem látsz verzióinformációt a curl-ről, akkor telepítened kell azt a [curl letöltési oldaláról](https://curl.se/download.html).

    > 💁 Ha jártas vagy a Postman használatában, akkor azt is használhatod, ha úgy jobban tetszik.

1. Hozz létre egy GeoJSON fájlt, amely tartalmaz egy poligont. Ezt a GPS-érzékelőddel fogod tesztelni, ezért hozz létre egy poligont az aktuális helyed körül. Ezt manuálisan is megteheted az alábbi GeoJSON példa szerkesztésével, vagy használhatsz egy eszközt, például a [GeoJSON.io](https://geojson.io/) oldalt.

    A GeoJSON-nak tartalmaznia kell egy `FeatureCollection`-t, amely egy `Feature`-t tartalmaz `geometry`-vel, amelynek típusa `Polygon`.

    **KÖTELEZŐ** továbbá hozzáadni egy `properties` elemet ugyanarra a szintre, mint a `geometry` elem, és ennek tartalmaznia kell egy `geometryId`-t:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Ha a [GeoJSON.io](https://geojson.io/) oldalt használod, akkor manuálisan kell hozzáadnod ezt az elemet az üres `properties` elemhez, akár a JSON fájl letöltése után, akár az alkalmazás JSON szerkesztőjében.

    Ez a `geometryId` egyedi kell, hogy legyen ebben a fájlban. Több geokerítést is feltölthetsz több `Feature`-ként ugyanabban a `FeatureCollection`-ben, amennyiben mindegyiknek különböző `geometryId`-ja van. A poligonoknak lehet ugyanaz a `geometryId`-juk, ha külön fájlból, külön időben töltik fel őket.

1. Mentse el ezt a fájlt `geofence.json` néven, és navigálj oda, ahol elmentetted a terminálban vagy konzolban.

1. Futtasd a következő curl parancsot a GeoFence létrehozásához:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Cseréld ki a `<subscription_key>` értéket az Azure Maps fiókod API kulcsára.

    Az URL-t a térképadatok feltöltésére használják a `https://atlas.microsoft.com/mapData/upload` API-n keresztül. A hívás tartalmaz egy `api-version` paramétert, amely meghatározza, hogy melyik Azure Maps API-t használja, ez lehetővé teszi az API időbeli változását, miközben fenntartja a visszafelé kompatibilitást. A feltöltött adatformátum `geojson`.

    Ez a POST kérést futtatja a feltöltési API-ra, és visszaad egy válaszfejlécek listáját, amely tartalmaz egy `location` nevű fejlécet.

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

    > 🎓 Webes végpont hívásakor paramétereket adhatsz a híváshoz úgy, hogy a `?` után kulcs-érték párokat adsz meg `kulcs=érték` formátumban, az egyes kulcs-érték párokat `&` jellel elválasztva.

1. Az Azure Maps nem dolgozza fel az adatokat azonnal, ezért ellenőrizned kell, hogy a feltöltési kérés befejeződött-e a `location` fejlécben megadott URL használatával. Küldj egy GET kérést erre a helyre az állapot ellenőrzéséhez. Az `location` URL végére hozzá kell adnod az előfizetési kulcsodat úgy, hogy `&subscription-key=<subscription_key>`-et adsz hozzá, ahol `<subscription_key>` az Azure Maps fiókod API kulcsa. Futtasd a következő parancsot:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Cseréld ki a `<location>` értéket a `location` fejléc értékére, és `<subscription_key>`-t az Azure Maps fiókod API kulcsára.

1. Ellenőrizd a válaszban a `status` értékét. Ha nem `Succeeded`, várj egy percet, majd próbáld újra.

1. Amint az állapot `Succeeded` értéket ad vissza, nézd meg a válaszban a `resourceLocation` értékét. Ez tartalmazza a GeoJSON objektum egyedi azonosítójának (UDID) részleteit. Az UDID a `metadata/` után található érték, az `api-version` nélkül. Például, ha a `resourceLocation`:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Akkor az UDID `7c3776eb-da87-4c52-ae83-caadf980323a` lenne.

    Jegyezd fel ezt az UDID-t, mert szükséged lesz rá a geokerítés teszteléséhez.

## Pontok tesztelése egy geokerítés ellen

Miután a poligont feltöltötted az Azure Maps-be, tesztelheted, hogy egy pont a geokerítésen belül vagy kívül van-e. Ezt úgy teheted meg, hogy egy webes API kérést küldesz, amelyben megadod a geokerítés UDID-ját, valamint a tesztelendő pont szélességi és hosszúsági koordinátáit.

A kérés során megadhatsz egy `searchBuffer` nevű értéket is. Ez azt határozza meg, hogy az API milyen pontossággal térjen vissza eredményekkel. Ennek oka, hogy a GPS nem tökéletesen pontos, és néha a helyek méterekkel vagy még többel is eltérhetnek. Az alapértelmezett keresési puffer 50 méter, de 0 és 500 méter közötti értékeket is beállíthatsz.

Az API hívás eredményei között szerepel egy `distance` nevű érték, amely a geokerítés széléhez legközelebbi pont távolságát méri. Ez pozitív érték, ha a pont a geokerítésen kívül van, és negatív, ha a geokerítésen belül van. Ha ez a távolság kisebb, mint a keresési puffer, akkor az aktuális távolság méterben kerül visszaadásra, különben az érték 999 vagy -999. A 999 azt jelenti, hogy a pont a geokerítésen kívül van a keresési pufferen túl, a -999 pedig azt, hogy a pont a geokerítésen belül van a keresési pufferen túl.

![Egy geokerítés 50 méteres keresési pufferrel](../../../../../translated_images/search-buffer-and-distance.e6a79af3898183c7.hu.png)

A fenti képen a geokerítésnek 50 méteres keresési puffere van.

* Egy pont a geokerítés közepén, jóval a keresési pufferen belül, távolsága **-999**
* Egy pont jóval a keresési pufferen kívül, távolsága **999**
* Egy pont a geokerítésen belül és a keresési pufferen belül, 6 méterre a geokerítéstől, távolsága **6m**
* Egy pont a geokerítésen kívül és a keresési pufferen belül, 39 méterre a geokerítéstől, távolsága **39m**

Fontos ismerni a geokerítés széléhez mért távolságot, és ezt más információkkal, például más GPS-olvasatokkal, sebességgel és úti adatokkal kombinálni, amikor döntéseket hozol egy jármű helyzete alapján.

Például képzeld el, hogy a GPS
A fenti képen egy geokerítés látható a Microsoft campus egy részén. A piros vonal egy teherautó útját mutatja az 520-as úton, körökkel jelölve a GPS-leolvasásokat. A legtöbb leolvasás pontos és az 520-as úton van, de van egy pontatlan leolvasás a geokerítésen belül. Ez a leolvasás nem lehet helyes – nincsenek utak, amelyek lehetővé tennék, hogy a teherautó hirtelen letérjen az 520-as útról a campusra, majd visszatérjen az 520-as útra. A geokerítést ellenőrző kódnak figyelembe kell vennie az előző leolvasásokat, mielőtt a geokerítés teszt eredményei alapján cselekedne.

✅ Milyen további adatokat lenne szükséges ellenőrizni, hogy megállapítsuk, egy GPS-leolvasás helyesnek tekinthető-e?

### Feladat - pontok tesztelése geokerítés ellen

1. Kezdje azzal, hogy összeállítja a webes API lekérdezés URL-jét. A formátum:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Cserélje ki `<subscription_key>`-t az Azure Maps fiókjához tartozó API kulcsra.

    Cserélje ki `<UDID>`-t az előző feladatból származó geokerítés UDID-jére.

    Cserélje ki `<lat>` és `<lon>`-t a tesztelni kívánt szélességi és hosszúsági fokra.

    Ez az URL a `https://atlas.microsoft.com/spatial/geofence/json` API-t használja egy GeoJSON-nal definiált geokerítés lekérdezésére. Az `1.0` API verziót célozza meg. A `deviceId` paraméter kötelező, és annak az eszköznek a neve kell legyen, amelyből a szélességi és hosszúsági fok származik.

    Az alapértelmezett keresési puffer 50 m, és ezt megváltoztathatja egy további `searchBuffer=<distance>` paraméter megadásával, ahol `<distance>` a keresési puffer távolsága méterben, 0-tól 500-ig.

1. Használja a curl-t, hogy GET kérést küldjön az URL-re:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Ha `BadRequest` válaszkódot kap, az alábbi hibával:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > akkor a GeoJSON fájlból hiányzik a `properties` szekció a `geometryId`-vel. Javítsa ki a GeoJSON fájlt, majd ismételje meg a fenti lépéseket, hogy új UDID-t kapjon.

1. A válasz tartalmazni fog egy `geometries` listát, amelyben minden poligon szerepel, amelyet a geokerítés létrehozásához használt GeoJSON definiált. Minden geometria három érdekes mezőt tartalmaz: `distance`, `nearestLat` és `nearestLon`.

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

    * A `nearestLat` és `nearestLon` a geokerítés szélének azon pontjának szélességi és hosszúsági foka, amely a legközelebb van a tesztelt helyhez.

    * A `distance` a tesztelt hely és a geokerítés szélének legközelebbi pontja közötti távolság. Negatív számok a geokerítésen belül, pozitív számok kívül. Ez az érték kevesebb lesz, mint 50 (az alapértelmezett keresési puffer), vagy 999.

1. Ismételje meg ezt többször, különböző helyekkel a geokerítésen belül és kívül.

## Geokerítések használata szerver nélküli kódból

Most hozzáadhat egy új trigger-t a Functions alkalmazásához, hogy a geokerítést tesztelje az IoT Hub GPS eseményadataival szemben.

### Fogyasztói csoportok

Ahogy az előző leckékből emlékezhet, az IoT Hub lehetővé teszi, hogy újra lejátsza azokat az eseményeket, amelyeket a hub fogadott, de még nem dolgozott fel. De mi történik, ha több trigger csatlakozik? Hogyan tudja, melyik dolgozta fel az eseményeket?

A válasz az, hogy nem tudja! Ehelyett több különálló kapcsolatot definiálhat az események olvasására, és mindegyik kezelheti az olvasatlan üzenetek újrajátszását. Ezeket *fogyasztói csoportoknak* nevezzük. Amikor csatlakozik az endpointhoz, megadhatja, melyik fogyasztói csoporthoz kíván csatlakozni. Az alkalmazás minden komponense más fogyasztói csoporthoz csatlakozik.

![Egy IoT Hub 3 fogyasztói csoporttal, amelyek ugyanazokat az üzeneteket osztják szét 3 különböző Functions alkalmazásnak](../../../../../translated_images/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.hu.png)

Elméletileg akár 5 alkalmazás is csatlakozhat minden fogyasztói csoporthoz, és mindegyik üzeneteket kap, amikor azok megérkeznek. A legjobb gyakorlat az, hogy minden fogyasztói csoporthoz csak egy alkalmazás férjen hozzá, hogy elkerülje az üzenetek duplikált feldolgozását, és biztosítsa, hogy újraindításkor minden sorban álló üzenet helyesen legyen feldolgozva. Például, ha a Functions alkalmazását helyben indítja el, miközben a felhőben is fut, mindkettő feldolgozná az üzeneteket, ami duplikált blobokat eredményezne a tárhelyfiókban.

Ha megnézi az IoT Hub triggerhez létrehozott `function.json` fájlt egy korábbi leckében, látni fogja a fogyasztói csoportot az esemény hub trigger kötési szekciójában:

```json
"consumerGroup": "$Default"
```

Amikor létrehoz egy IoT Hubot, automatikusan létrejön a `$Default` fogyasztói csoport. Ha új trigger-t szeretne hozzáadni, ezt egy új fogyasztói csoport használatával teheti meg.

> 💁 Ebben a leckében egy másik funkciót fog használni a geokerítés tesztelésére, mint amit a GPS adatok tárolására használt. Ez azért van, hogy bemutassa, hogyan lehet fogyasztói csoportokat használni, és elkülöníteni a kódot, hogy könnyebben olvasható és érthető legyen. Egy éles alkalmazásban számos módon lehet ezt megtervezni – mindkettőt egy funkcióban elhelyezni, egy trigger-t használni a tárhelyfiókon, hogy futtasson egy funkciót a geokerítés ellenőrzésére, vagy több funkciót használni. Nincs "helyes út", ez az alkalmazás többi részétől és az igényektől függ.

### Feladat - új fogyasztói csoport létrehozása

1. Futtassa az alábbi parancsot, hogy létrehozzon egy új fogyasztói csoportot `geofence` néven az IoT Hubhoz:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Cserélje ki `<hub_name>`-t az IoT Hubhoz használt névre.

1. Ha látni szeretné az IoT Hub összes fogyasztói csoportját, futtassa az alábbi parancsot:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Cserélje ki `<hub_name>`-t az IoT Hubhoz használt névre. Ez felsorolja az összes fogyasztói csoportot.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Amikor az IoT Hub eseménymonitorját futtatta egy korábbi leckében, az a `$Default` fogyasztói csoporthoz csatlakozott. Ezért nem tudja futtatni az eseménymonitor és az esemény trigger-t egyszerre. Ha mindkettőt futtatni szeretné, akkor más fogyasztói csoportokat használhat az összes Functions alkalmazáshoz, és megtarthatja a `$Default`-ot az eseménymonitorhoz.

### Feladat - új IoT Hub trigger létrehozása

1. Adjon hozzá egy új IoT Hub esemény trigger-t a korábbi leckében létrehozott `gps-trigger` Functions alkalmazáshoz. Nevezze el ezt a funkciót `geofence-trigger`-nek.

    > ⚠️ Ha szükséges, hivatkozhat [a projekt 2, 5. leckéjében található IoT Hub esemény trigger létrehozására vonatkozó utasításokra](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Konfigurálja az IoT Hub kapcsolat karakterláncát a `function.json` fájlban. A `local.settings.json` megosztott az összes trigger között a Functions alkalmazásban.

1. Frissítse a `consumerGroup` értékét a `function.json` fájlban, hogy az új `geofence` fogyasztói csoportra hivatkozzon:

    ```json
    "consumerGroup": "geofence"
    ```

1. Szüksége lesz az Azure Maps fiókjához tartozó előfizetési kulcsra ebben a triggerben, ezért adjon hozzá egy új bejegyzést a `local.settings.json` fájlhoz `MAPS_KEY` néven.

1. Futtassa a Functions alkalmazást, hogy megbizonyosodjon arról, hogy csatlakozik és feldolgozza az üzeneteket. Az előző leckéből származó `iot-hub-trigger` is futni fog, és blobokat tölt fel a tárhelyre.

    > Az ismétlődő GPS-leolvasások elkerülése érdekében leállíthatja a felhőben futó Functions alkalmazást. Ehhez használja az alábbi parancsot:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Cserélje ki `<functions_app_name>`-t a Functions alkalmazásához használt névre.
    >
    > Később újraindíthatja az alábbi parancs segítségével:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Cserélje ki `<functions_app_name>`-t a Functions alkalmazásához használt névre.

### Feladat - geokerítés tesztelése a triggerből

Korábban ebben a leckében curl-t használt a geokerítés lekérdezésére, hogy megállapítsa, egy pont belül vagy kívül található-e. Hasonló webes kérést tehet a triggerből.

1. A geokerítés lekérdezéséhez szüksége van az UDID-jére. Adjon hozzá egy új bejegyzést a `local.settings.json` fájlhoz `GEOFENCE_UDID` néven ezzel az értékkel.

1. Nyissa meg az új `geofence-trigger` trigger `__init__.py` fájlját.

1. Adja hozzá az alábbi importot a fájl tetejéhez:

    ```python
    import json
    import os
    import requests
    ```

    A `requests` csomag lehetővé teszi webes API hívások végrehajtását. Az Azure Maps nem rendelkezik Python SDK-val, ezért webes API hívásokat kell végrehajtania Python kódból.

1. Adja hozzá az alábbi 2 sort a `main` metódus elejéhez, hogy megszerezze a Maps előfizetési kulcsot:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Az `for event in events` cikluson belül adja hozzá az alábbiakat, hogy megszerezze a szélességi és hosszúsági fokot minden eseményből:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Ez a kód átalakítja az esemény törzsét JSON-ból szótárrá, majd kinyeri a `lat` és `lon` értékeket a `gps` mezőből.

1. A `requests` használatakor, ahelyett hogy egy hosszú URL-t építene fel, ahogy curl-lel tette, csak az URL részt használhatja, és a paramétereket szótárként adhatja át. Adja hozzá az alábbi kódot az URL meghívásához és a paraméterek konfigurálásához:

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

    A `params` szótár elemei megfelelnek azoknak a kulcs-érték pároknak, amelyeket a webes API curl-lel történő meghívásakor használt.

1. Adja hozzá az alábbi sorokat a webes API meghívásához:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Ez meghívja az URL-t a paraméterekkel, és visszakap egy válasz objektumot.

1. Adja hozzá az alábbi kódot ez alá:

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

    Ez a kód feltételezi, hogy 1 geometria van, és kinyeri a távolságot abból az egyetlen geometriából. Ezután különböző üzeneteket naplóz a távolság alapján.

1. Futtassa ezt a kódot. A naplózási kimenetben látni fogja, hogy a GPS koordináták a geokerítésen belül vagy kívül vannak-e, és ha 50 m-en belül vannak, akkor a távolságot is. Próbálja ki ezt a kódot különböző geokerítésekkel a GPS érzékelő helye alapján, próbálja meg mozgatni az érzékelőt (például mobiltelefon WiFi-jéhez csatlakoztatva, vagy különböző koordinátákkal a virtuális IoT eszközön), hogy lássa a változást.

1. Ha készen áll, telepítse ezt a kódot a Functions alkalmazásába a felhőben. Ne felejtse el telepíteni az új alkalmazásbeállításokat.

    > ⚠️ Ha szükséges, hivatkozhat [a projekt 2, 5. leckéjében található alkalmazásbeállítások feltöltésére vonatkozó utasításokra](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Ha szükséges, hivatkozhat [a projekt 2, 5. leckéjében található Functions alkalmazás felhőbe történő telepítésére vonatkozó utasításokra](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Ezt a kódot megtalálhatja a [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions) mappában.

---

## 🚀 Kihívás

Ebben a leckében egy geokerítést adott hozzá egy GeoJSON fájl segítségével, amely egyetlen poligont tartalmazott. Több poligont is feltölthet egyszerre, amennyiben a `properties` szekcióban különböző `geometryId` értékekkel rendelkeznek.

Próbáljon meg feltölteni egy GeoJSON fájlt több poligonnal, és módosítsa a kódját, hogy megtalálja, melyik poligonhoz van legközelebb vagy melyikben található a GPS koordináta.

## Utólagos kvíz

[Utólagos kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Áttekintés és önálló tanulás

* Olvasson többet a geokerítésekről és azok felhasználási eseteiről a [Geokerítés oldalán a Wikipédián](https://en.wikipedia.org/wiki/Geo-fence).
* Olvasson többet az Azure Maps geokerítés API-ról a [Microsoft Azure Maps Spatial - Get Geofence dokumentációban](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Olvasson többet a fogyasztói csoportokról az [Azure Event Hubs funkciók és terminológia - Eseményfogyasztók dokumentációban a Microsoft Docs-on](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Feladat

[Értesítések küldése Twilio segítségével](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget a fordítás használatából eredő félreértésekért vagy téves értelmezésekért.