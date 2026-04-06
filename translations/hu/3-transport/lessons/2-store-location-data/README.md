# Tárolja a helyadatokat

![A leckéről készült vázlatrajz](../../../../../translated_images/hu/lesson-12.ca7f53039712a3ec.webp)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattintson a képre a nagyobb verzióért.

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Bevezetés

Az előző leckében megtanulta, hogyan használjon GPS-érzékelőt helyadatok rögzítésére. Ahhoz, hogy ezeket az adatokat felhasználhassa egy élelmiszerrel megrakott teherautó helyének és útvonalának megjelenítésére, azokat egy IoT-szolgáltatásba kell küldeni a felhőben, majd valahol tárolni.

Ebben a leckében megismeri az IoT-adatok tárolásának különböző módjait, és megtanulja, hogyan tárolja az adatokat az IoT-szolgáltatásból szerver nélküli kód használatával.

A lecke témái:

* [Strukturált és strukturálatlan adatok](../../../../../3-transport/lessons/2-store-location-data)
* [GPS-adatok küldése egy IoT Hubba](../../../../../3-transport/lessons/2-store-location-data)
* [Forró, meleg és hideg útvonalak](../../../../../3-transport/lessons/2-store-location-data)
* [GPS-események kezelése szerver nélküli kóddal](../../../../../3-transport/lessons/2-store-location-data)
* [Azure Storage-fiókok](../../../../../3-transport/lessons/2-store-location-data)
* [Kapcsolja össze szerver nélküli kódját a tárolással](../../../../../3-transport/lessons/2-store-location-data)

## Strukturált és strukturálatlan adatok

A számítógépes rendszerek adatokat kezelnek, amelyek különböző formákban és méretekben érkeznek. Ezek lehetnek egyszerű számok, nagy mennyiségű szöveg, videók és képek, valamint IoT-adatok. Az adatokat általában két kategóriába sorolhatjuk: *strukturált* adatok és *strukturálatlan* adatok.

* **Strukturált adatok**: Jól definiált, merev szerkezettel rendelkező adatok, amelyek nem változnak, és általában táblázatokhoz kapcsolódnak. Példa erre egy személy adatai, például neve, születési dátuma és címe.

* **Strukturálatlan adatok**: Jól definiált, merev szerkezettel nem rendelkező adatok, amelyek szerkezete gyakran változhat. Példa erre dokumentumok, például írott szövegek vagy táblázatok.

✅ Kutatás: Tudna más példákat mondani strukturált és strukturálatlan adatokra?

> 💁 Léteznek félig strukturált adatok is, amelyek strukturáltak, de nem illeszkednek fix táblázatokba.

Az IoT-adatokat általában strukturálatlan adatoknak tekintjük.

Képzelje el, hogy IoT-eszközöket ad hozzá egy nagy kereskedelmi farm járműflottájához. Különböző típusú járművekhez különböző eszközöket szeretne használni. Például:

* Mezőgazdasági járművek, például traktorok esetében GPS-adatokra van szükség, hogy biztosítsa, hogy a megfelelő földeken dolgoznak.
* Élelmiszert raktárakba szállító teherautók esetében GPS-adatokra, valamint sebesség- és gyorsulási adatokra van szükség, hogy biztosítsa a biztonságos vezetést, valamint a vezető azonosítására és a munkaidőre vonatkozó adatokra a helyi törvények betartása érdekében.
* Hűtött teherautók esetében hőmérsékleti adatokra van szükség, hogy az élelmiszer ne melegedjen túl vagy hűljön le túlságosan, és ne romoljon meg szállítás közben.

Ezek az adatok folyamatosan változhatnak. Például, ha az IoT-eszköz egy teherautó fülkéjében van, akkor az általa küldött adatok változhatnak, ahogy a pótkocsi változik, például csak hőmérsékleti adatokat küld, ha hűtött pótkocsit használnak.

✅ Milyen más IoT-adatokat lehetne rögzíteni? Gondoljon a teherautók által szállított rakományokra, valamint a karbantartási adatokra.

Ezek az adatok járművenként változnak, de mind ugyanabba az IoT-szolgáltatásba kerülnek feldolgozásra. Az IoT-szolgáltatásnak képesnek kell lennie feldolgozni ezeket a strukturálatlan adatokat, olyan módon tárolva őket, amely lehetővé teszi a keresést vagy elemzést, de az adatok különböző szerkezeteivel is működik.

### SQL vs NoSQL tárolás

Az adatbázisok olyan szolgáltatások, amelyek lehetővé teszik az adatok tárolását és lekérdezését. Az adatbázisok két típusba sorolhatók: SQL és NoSQL.

#### SQL adatbázisok

Az első adatbázisok Relációs Adatbázis-kezelő Rendszerek (RDBMS) voltak, vagy relációs adatbázisok. Ezeket SQL adatbázisoknak is nevezik, az általuk használt Structured Query Language (SQL) után, amelyet az adatok hozzáadására, eltávolítására, frissítésére vagy lekérdezésére használnak. Ezek az adatbázisok egy sémából állnak - egy jól definiált táblázatkészletből, hasonlóan egy táblázathoz. Minden táblázatnak több elnevezett oszlopa van. Amikor adatokat ad hozzá, egy sort ad a táblázathoz, értékeket helyezve az oszlopokba. Ez az adatokat nagyon merev szerkezetben tartja - bár az oszlopokat üresen hagyhatja, ha új oszlopot szeretne hozzáadni, azt az adatbázisban kell megtennie, az értékeket kitöltve a meglévő sorokhoz. Ezek az adatbázisok relációsak - azaz egy táblázat kapcsolatban állhat egy másikkal.

![Egy relációs adatbázis, ahol a Felhasználó táblázat ID-ja kapcsolódik a vásárlások táblázat felhasználói ID oszlopához, és a termékek táblázat ID-ja kapcsolódik a vásárlások táblázat termék ID oszlopához](../../../../../translated_images/hu/sql-database.be160f12bfccefd3.webp)

Például, ha egy felhasználó személyes adatait tárolja egy táblázatban, akkor valamilyen belső egyedi ID-t használna felhasználónként, amelyet egy sorban tárolna egy táblázatban, amely tartalmazza a felhasználó nevét és címét. Ha további adatokat szeretne tárolni a felhasználóról, például a vásárlásait, egy másik táblázatban, akkor az új táblázatban lenne egy oszlop a felhasználó ID-jéhez. Amikor egy felhasználót keres, az ID-jét használhatja, hogy megszerezze személyes adatait az egyik táblázatból, és vásárlásait egy másikból.

Az SQL adatbázisok ideálisak strukturált adatok tárolására, és amikor biztosítani szeretné, hogy az adatok megfeleljenek a sémának.

✅ Ha még nem használt SQL-t, szánjon egy pillanatot arra, hogy olvasson róla a [SQL Wikipedia oldalán](https://wikipedia.org/wiki/SQL).

Néhány ismert SQL adatbázis: Microsoft SQL Server, MySQL és PostgreSQL.

✅ Kutatás: Olvasson ezekről az SQL adatbázisokról és képességeikről.

#### NoSQL adatbázisok

A NoSQL adatbázisokat azért nevezik NoSQL-nek, mert nem rendelkeznek az SQL adatbázisok merev szerkezetével. Dokumentumadatbázisoknak is nevezik őket, mivel strukturálatlan adatokat, például dokumentumokat tudnak tárolni.

> 💁 A nevük ellenére néhány NoSQL adatbázis lehetővé teszi az SQL használatát az adatok lekérdezésére.

![Dokumentumok mappákban egy NoSQL adatbázisban](../../../../../translated_images/hu/noqsl-database.62d24ccf5b73f60d.webp)

A NoSQL adatbázisoknak nincs előre definiált sémája, amely korlátozná az adatok tárolását, ehelyett bármilyen strukturálatlan adatot beilleszthet, általában JSON dokumentumok formájában. Ezek a dokumentumok mappákba szervezhetők, hasonlóan a számítógépen lévő fájlokhoz. Minden dokumentum különböző mezőkkel rendelkezhet, mint más dokumentumok - például, ha a farmjárművekből származó IoT-adatokat tárolná, néhány dokumentum tartalmazhat gyorsulásmérő és sebességadatokat, mások pedig a pótkocsi hőmérsékletét. Ha új teherautótípust adna hozzá, például olyat, amely beépített mérlegekkel rendelkezik a szállított termékek súlyának nyomon követésére, akkor az IoT-eszköz hozzáadhatná ezt az új mezőt, és azt tárolhatná anélkül, hogy változtatásokat kellene végezni az adatbázison.

Néhány ismert NoSQL adatbázis: Azure CosmosDB, MongoDB és CouchDB.

✅ Kutatás: Olvasson ezekről a NoSQL adatbázisokról és képességeikről.

Ebben a leckében NoSQL tárolást fog használni IoT-adatok tárolására.

## GPS-adatok küldése egy IoT Hubba

Az előző leckében GPS-adatokat rögzített egy IoT-eszközhöz csatlakoztatott GPS-érzékelőből. Ahhoz, hogy ezeket az IoT-adatokat a felhőben tárolhassa, el kell küldenie őket egy IoT-szolgáltatásba. Ismét az Azure IoT Hubot fogja használni, ugyanazt az IoT-felhőszolgáltatást, amelyet az előző projektben használt.

![GPS telemetria küldése egy IoT-eszközről az IoT Hubba](../../../../../translated_images/hu/gps-telemetry-iot-hub.8115335d51cd2c12.webp)

### Feladat - GPS-adatok küldése egy IoT Hubba

1. Hozzon létre egy új IoT Hubot az ingyenes szint használatával.

    > ⚠️ Ha szükséges, hivatkozhat a [2. projekt, 4. lecke IoT Hub létrehozására vonatkozó utasításaira](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud).

    Ne felejtse el létrehozni egy új Erőforráscsoportot. Nevezze el az új Erőforráscsoportot `gps-sensor`-nak, és az új IoT Hubot egyedi névvel `gps-sensor` alapján, például `gps-sensor-<az ön neve>`.

    > 💁 Ha még mindig megvan az IoT Hubja az előző projektből, újra felhasználhatja. Ne felejtse el használni ennek az IoT Hubnak a nevét és az Erőforráscsoportot, amelyben található, amikor más szolgáltatásokat hoz létre.

1. Adjon hozzá egy új eszközt az IoT Hubhoz. Nevezze el ezt az eszközt `gps-sensor`-nak. Szerezze meg az eszköz kapcsolati karakterláncát.

1. Frissítse az eszköz kódját, hogy az új IoT Hubba küldje a GPS-adatokat az előző lépésben kapott kapcsolati karakterlánc használatával.

    > ⚠️ Ha szükséges, hivatkozhat a [2. projekt, 4. lecke eszköz csatlakoztatására vonatkozó utasításaira](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service).

1. Amikor a GPS-adatokat küldi, JSON formátumban tegye a következőképpen:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Küldjön GPS-adatokat percenként, hogy ne használja el a napi üzenetkeretét.

Ha Wio Terminalt használ, ne felejtse el hozzáadni az összes szükséges könyvtárat, és állítsa be az időt egy NTP-szerver segítségével. A kódjának biztosítania kell, hogy az összes adatot beolvassa a soros portból, mielőtt elküldi a GPS-helyet, az előző lecke meglévő kódját használva. Használja a következő kódot a JSON dokumentum létrehozásához:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Ha virtuális IoT-eszközt használ, ne felejtse el telepíteni az összes szükséges könyvtárat egy virtuális környezet használatával.

Mind a Raspberry Pi, mind a virtuális IoT-eszköz esetében használja az előző lecke meglévő kódját a szélességi és hosszúsági értékek megszerzéséhez, majd küldje el őket a megfelelő JSON formátumban a következő kóddal:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Ezt a kódot megtalálja a [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) vagy [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device) mappában.

Futtassa az eszköz kódját, és győződjön meg róla, hogy az üzenetek az IoT Hubba áramlanak az `az iot hub monitor-events` CLI parancs használatával.

## Forró, meleg és hideg útvonalak

Az IoT-eszközből a felhőbe áramló adatokat nem mindig dolgozzák fel valós időben. Egyes adatok valós időben történő feldolgozást igényelnek, más adatok rövid időn belül feldolgozhatók, míg más adatok sokkal később kerülnek feldolgozásra. Az adatok különböző szolgáltatásokba történő áramlását, amelyek különböző időpontokban dolgozzák fel az adatokat, forró, meleg és hideg útvonalaknak nevezzük.

### Forró útvonal

A forró útvonal olyan adatokra utal, amelyeket valós időben vagy közel valós időben kell feldolgozni. Forró útvonal adatokat használna például riasztásokhoz, például amikor egy jármű közeledik egy raktárhoz, vagy amikor a hűtött teherautó hőmérséklete túl magas.

A forró útvonal adatok használatához a kódja azonnal reagálna az eseményekre, amint azokat a felhőszolgáltatások megkapják.

### Meleg útvonal

A meleg útvonal olyan adatokra utal, amelyeket röviddel a beérkezés után lehet feldolgozni, például jelentésekhez vagy rövid távú elemzésekhez. Meleg útvonal adatokat használna például napi jelentésekhez a járművek futásteljesítményéről, az előző nap összegyűjtött adatok alapján.

A meleg útvonal adatok tárolásra kerülnek, amint a felhőszolgáltatás megkapja őket, valamilyen gyorsan elérhető tárolóban.

### Hideg útvonal

A hideg útvonal történelmi adatokra utal, amelyek hosszú távú tárolásra kerülnek, és bármikor feldolgozhatók. Például a hideg útvonalat használhatná éves futásteljesítmény-jelentések készítésére a járművekről, vagy útvonalak elemzésére az üzemanyagköltségek csökkentésére legoptimálisabb útvonalak megtalálásához.

A hideg útvonal adatok adatközpontokban kerülnek tárolásra - olyan adatbázisokban, amelyek nagy mennyiségű adat tárolására vannak tervezve, amelyek soha nem változnak, és gyorsan és könnyen lekérdezhetők. Általában rendszeres feladatot futtatna a felhőalkalmazásában, amely rendszeres időközönként, például naponta, hetente vagy havonta áthelyezi az adatokat a meleg útvonal tárolásából az adatközpontba.

✅ Gondolja át az eddig rögzített adatokat ezekben a leckékben. Ezek forró, meleg vagy hideg útvonal adatok
> ⚠️ Az [Azure Functions projekt létrehozására vonatkozó utasításokat a 2. projekt, 5. lecke](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) alatt találod, ha szükséges.
1. Adj hozzá egy IoT Hub eseményindítót, amely az IoT Hub Event Hub kompatibilis végpontját használja.

   > ⚠️ Ha szükséges, hivatkozhatsz az [IoT Hub eseményindító létrehozására vonatkozó utasításokra a 2. projekt 5. leckéjéből](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Állítsd be az Event Hub kompatibilis végpont kapcsolat karakterláncát a `local.settings.json` fájlban, és használd ennek a bejegyzésnek a kulcsát a `function.json` fájlban.

1. Használd az Azurite alkalmazást helyi tároló emulátorként.

1. Futtasd a Functions alkalmazásodat, hogy megbizonyosodj arról, hogy fogadja az eseményeket a GPS eszközödről. Győződj meg arról is, hogy az IoT eszközöd fut és küldi a GPS adatokat.

   ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storage-fiókok

![Az Azure Storage logója](../../../../../translated_images/hu/azure-storage-logo.605c0f602c640d48.webp)

Az Azure Storage-fiókok egy általános célú tárolási szolgáltatás, amely különböző módokon képes adatokat tárolni. Tárolhatsz adatokat blobokként, sorokban, táblákban vagy fájlokként, akár egyszerre is.

### Blob tárolás

A *Blob* szó bináris nagy objektumokat jelent, de mára bármilyen strukturálatlan adat megnevezésére használják. Blob tárolásban bármilyen adatot tárolhatsz, például IoT adatokat tartalmazó JSON dokumentumokat, képeket vagy filmfájlokat. A blob tárolás tartalmazza a *konténerek* fogalmát, amelyek elnevezett tárolók, hasonlóan az adatbázisok tábláihoz. Ezek a konténerek tartalmazhatnak egy vagy több mappát a blobok tárolására, és minden mappa tartalmazhat további mappákat, hasonlóan ahhoz, ahogy a fájlok a számítógéped merevlemezén tárolódnak.

Ebben a leckében blob tárolást fogsz használni IoT adatok tárolására.

✅ Kutass egy kicsit: Olvass az [Azure Blob Storage-ról](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn).

### Tábla tárolás

A tábla tárolás lehetővé teszi félig strukturált adatok tárolását. A tábla tárolás valójában egy NoSQL adatbázis, így nem igényel előre meghatározott táblakészletet, de úgy van kialakítva, hogy egy vagy több táblában tárolja az adatokat, egyedi kulcsokkal az egyes sorok meghatározásához.

✅ Kutass egy kicsit: Olvass az [Azure Table Storage-ról](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn).

### Sor tárolás

A sor tárolás lehetővé teszi legfeljebb 64 KB méretű üzenetek tárolását egy sorban. Üzeneteket adhatsz hozzá a sor végéhez, és olvashatod ki őket az elejéről. A sorok határozatlan ideig tárolják az üzeneteket, amíg van tárhely, így lehetővé teszik az üzenetek hosszú távú tárolását, majd szükség esetén kiolvasását. Például, ha havi munkát szeretnél futtatni GPS adatok feldolgozására, minden nap hozzáadhatod az adatokat a sorhoz, majd a hónap végén feldolgozhatod az összes üzenetet.

✅ Kutass egy kicsit: Olvass az [Azure Queue Storage-ról](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn).

### Fájl tárolás

A fájl tárolás lehetővé teszi fájlok tárolását a felhőben, amelyhez bármilyen alkalmazás vagy eszköz csatlakozhat ipari szabvány protokollok használatával. Fájlokat írhatsz a fájl tárolásba, majd meghajtóként csatolhatod azokat a PC-dhez vagy Mac-edhez.

✅ Kutass egy kicsit: Olvass az [Azure File Storage-ról](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn).

## Kapcsold össze a szerver nélküli kódodat a tárolással

A Functions alkalmazásodnak most csatlakoznia kell a blob tároláshoz, hogy tárolja az IoT Hub üzeneteit. Két módon teheted ezt meg:

* A funkció kódjában csatlakozz a blob tároláshoz a blob tárolás Python SDK használatával, és írd az adatokat blobként.
* Használj egy kimeneti funkció kötést, hogy a funkció visszatérési értékét blob tároláshoz kösd, és a blob automatikusan mentésre kerüljön.

Ebben a leckében a Python SDK-t fogod használni, hogy megtanuld, hogyan lehet interakcióba lépni a blob tárolással.

![GPS telemetria küldése egy IoT eszközről az IoT Hubba, majd Azure Functions-be egy eseményindító segítségével, végül mentés blob tárolásba](../../../../../translated_images/hu/save-telemetry-to-storage-from-functions.ed3b1820980097f1.webp)

Az adatok JSON blobként lesznek mentve a következő formátumban:

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### Feladat - Kapcsold össze a szerver nélküli kódodat a tárolással

1. Hozz létre egy Azure Storage-fiókot. Nevezd el például `gps<neved>` formátumban.

   > ⚠️ Ha szükséges, hivatkozhatsz az [Azure Storage-fiók létrehozására vonatkozó utasításokra a 2. projekt 5. leckéjéből](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources).

   Ha van még tároló fiókod az előző projektből, újra felhasználhatod azt.

   > 💁 Ugyanazt a tároló fiókot fogod tudni használni az Azure Functions alkalmazásod későbbi telepítéséhez ebben a leckében.

1. Futtasd a következő parancsot, hogy megszerezd a tároló fiók kapcsolat karakterláncát:

   ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

   Cseréld le `<storage_name>`-t a tároló fiók nevére, amelyet az előző lépésben hoztál létre.

1. Adj hozzá egy új bejegyzést a `local.settings.json` fájlhoz a tároló fiók kapcsolat karakterláncához, az előző lépésben kapott értéket használva. Nevezd el `STORAGE_CONNECTION_STRING`-nek.

1. Add hozzá a következőket a `requirements.txt` fájlhoz az Azure tárolási Pip csomagok telepítéséhez:

   ```sh
    azure-storage-blob
    ```

   Telepítsd a csomagokat ebből a fájlból a virtuális környezetedben.

   > Ha hibát kapsz, frissítsd a Pip verzióját a virtuális környezetedben a legújabb verzióra a következő parancs segítségével, majd próbáld újra:
   >
   > ```sh
    > pip install --upgrade pip
    > ```

1. Az `iot-hub-trigger` mappában található `__init__.py` fájlban add hozzá a következő import utasításokat:

   ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

   A `json` rendszer modul JSON olvasására és írására lesz használva, az `os` rendszer modul a kapcsolat karakterlánc olvasására, az `uuid` rendszer modul pedig egyedi azonosítók generálására a GPS adatokhoz.

   Az `azure.storage.blob` csomag tartalmazza a Python SDK-t a blob tárolás kezeléséhez.

1. A `main` metódus előtt add hozzá a következő segédfüggvényt:

   ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

   A Python blob SDK nem tartalmaz segédfüggvényt konténer létrehozására, ha az nem létezik. Ez a kód betölti a kapcsolat karakterláncot a `local.settings.json` fájlból (vagy az Alkalmazás Beállításokból, ha a felhőbe van telepítve), majd létrehoz egy `BlobServiceClient` osztályt, hogy interakcióba lépjen a blob tároló fiókkal. Ezután végigmegy a blob tároló fiók összes konténerén, és ha talál egyet a megadott névvel, visszaad egy `ContainerClient` osztályt, amely interakcióba léphet a konténerrel a blobok létrehozásához. Ha nem talál ilyet, akkor létrehozza a konténert, és visszaadja az új konténer kliensét.

   Amikor az új konténer létrejön, nyilvános hozzáférést kap a konténer blobjainak lekérdezéséhez. Ezt a következő leckében fogod használni a GPS adatok térképen való megjelenítéséhez.

1. A talajnedvességgel ellentétben ebben a kódban minden eseményt tárolni szeretnénk, ezért add hozzá a következő kódot a `for event in events:` ciklusban a `main` függvényben, a `logging` utasítás alá:

   ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

   Ez a kód az esemény metaadataiból megszerzi az eszköz azonosítóját, majd ezt használja a blob név létrehozásához. A blobok mappákban tárolhatók, és az eszköz azonosítója lesz a mappa neve, így minden eszköz összes GPS eseménye egy mappában lesz. A blob neve ez a mappa, amelyet egy dokumentumnév követ, előrejelző perjelekkel elválasztva, hasonlóan a Linux és macOS útvonalakhoz (hasonlóan a Windows-hoz is, de a Windows visszaperjeleket használ). A dokumentumnév egyedi azonosító, amelyet a Python `uuid` modul generál, a fájltípus pedig `json`.

   Például a `gps-sensor` eszköz azonosító esetén a blob neve lehet `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Add hozzá a következő kódot ez alá:

   ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

   Ez a kód megszerzi a konténer klienst a `get_or_create_container` segédosztály segítségével, majd egy blob kliens objektumot hoz létre a blob név használatával. Ezek a blob kliensek hivatkozhatnak meglévő blobokra, vagy mint ebben az esetben, új blobokra.

1. Add hozzá a következő kódot ezután:

   ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

   Ez felépíti a blob tartalmát, amelyet blob tárolásba fog írni. Ez egy JSON dokumentum, amely tartalmazza az eszköz azonosítóját, az időt, amikor a telemetria az IoT Hubba került, és a telemetria GPS koordinátáit.

   > 💁 Fontos, hogy az üzenet sorba állítási idejét használd, ne az aktuális időt, hogy megkapd az üzenet küldésének idejét. Az üzenet egy ideig az IoT Hubban várakozhat, mielőtt a Functions App feldolgozza.

1. Add hozzá a következőt ez alá:

   ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

   Ez a kód naplózza, hogy egy blob írása fog történni a részleteivel, majd feltölti a blob tartalmát az új blob tartalmaként.

1. Futtasd a Functions alkalmazást. Látni fogod, hogy blobok íródnak az összes GPS eseményhez a kimenetben:

   ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

   > 💁 Győződj meg arról, hogy nem fut az IoT Hub eseménymonitor egyidejűleg.

> 💁 Ezt a kódot megtalálod a [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions) mappában.

### Feladat - Ellenőrizd a feltöltött blobokat

1. A létrehozott blobok megtekintéséhez használhatod az [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn) alkalmazást, amely egy ingyenes eszköz a tároló fiókok megtekintésére és kezelésére, vagy a CLI-t.

   1. A CLI használatához először szükséged lesz egy fiókkulcsra. Futtasd a következő parancsot a kulcs megszerzéséhez:

      ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

      Cseréld le `<storage_name>`-t a tároló fiók nevére.

      Másold ki a `key1` értékét.

   1. Futtasd a következő parancsot a konténerben lévő blobok listázásához:

      ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

      Cseréld le `<storage_name>`-t a tároló fiók nevére, és `<key1>`-t a korábban kimásolt `key1` értékére.

      Ez kilistázza az összes blobot a konténerben:

      ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

   1. Tölts le egy blobot a következő parancs segítségével:

      ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

      Cseréld le `<storage_name>`-t a tároló fiók nevére, `<key1>`-t a korábban kimásolt `key1` értékére.

      Cseréld le `<blob_name>`-t a `Name` oszlop teljes nevére az előző lépés kimenetében, beleértve a mappa nevét. Cseréld le `<file_name>`-t egy helyi fájl nevére, ahová a blobot menteni szeretnéd.

   Miután letöltötted, megnyithatod a JSON fájlt a VS Code-ban, és látni fogod a blobot, amely tartalmazza a GPS helyadatokat:

   ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Feladat - Telepítsd a Functions alkalmazásodat a felhőbe

Most, hogy a Functions alkalmazásod működik, telepítheted a felhőbe.

1. Hozz létre egy új Azure Functions alkalmazást, a korábban létrehozott tároló fiókot használva. Nevezd el például `gps-sensor-` formátumban, és adj hozzá egy egyedi azonosítót, például néhány véletlenszerű szót vagy a nevedet.

   > ⚠️ Ha szükséges, hivatkozhatsz az [Azure Functions alkalmazás létrehozására vonatkozó utasításokra a 2. projekt 5. leckéjéből](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources).

1. Töltsd fel az `IOT_HUB_CONNECTION_STRING` és `STORAGE_CONNECTION_STRING` értékeket az Alkalmazás Beállításokhoz.

   > ⚠️ Ha szükséges, hivatkozhatsz az [Alkalmazás Beállítások feltöltésére vonatkozó utasításokra a 2. projekt 5. leckéjéből](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

1. Telepítsd a helyi Functions alkalmazásodat a felhőbe.
> ⚠️ Szükség esetén hivatkozhatsz a [2. projekt, 5. lecke útmutatójára a Functions alkalmazás telepítéséhez](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).
## 🚀 Kihívás

A GPS adatok nem tökéletesen pontosak, és az érzékelt helyek néhány méterrel, vagy akár többel is eltérhetnek, különösen alagutakban és magas épületek környékén.

Gondolkodj el azon, hogyan tudná a műholdas navigáció ezt kiküszöbölni! Milyen adatok állnak rendelkezésére a navigációs rendszerednek, amelyek segítségével pontosabb helymeghatározást tudna végezni?

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Áttekintés és önálló tanulás

* Olvass a strukturált adatokról a [Wikipedia adatmodell oldalán](https://wikipedia.org/wiki/Data_model)
* Olvass a félig strukturált adatokról a [Wikipedia félig strukturált adat oldalán](https://wikipedia.org/wiki/Semi-structured_data)
* Olvass a strukturálatlan adatokról a [Wikipedia strukturálatlan adat oldalán](https://wikipedia.org/wiki/Unstructured_data)
* Tudj meg többet az Azure Storage-ról és a különböző tárolási típusokról az [Azure Storage dokumentációban](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Feladat

[Vizsgáld meg a függvénykapcsolatokat](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.