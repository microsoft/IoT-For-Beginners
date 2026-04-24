# Podatki o lokaciji trgovine

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-12.ca7f53039712a3ec.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

## Kviz pred predavanjem

[Kviz pred predavanjem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Uvod

V prejšnji lekciji ste se naučili, kako uporabiti GPS senzor za zajem podatkov o lokaciji. Da bi te podatke uporabili za vizualizacijo lokacije tovornjaka, naloženega s hrano, in njegove poti, jih je treba poslati v IoT storitev v oblaku in jih nato nekje shraniti.

V tej lekciji se boste naučili o različnih načinih shranjevanja IoT podatkov ter kako shraniti podatke iz vaše IoT storitve z uporabo strežniške kode.

V tej lekciji bomo obravnavali:

* [Strukturirani in nestrukturirani podatki](../../../../../3-transport/lessons/2-store-location-data)
* [Pošiljanje GPS podatkov v IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Vroče, tople in hladne poti](../../../../../3-transport/lessons/2-store-location-data)
* [Obravnavanje GPS dogodkov z uporabo strežniške kode](../../../../../3-transport/lessons/2-store-location-data)
* [Azure Storage Accounts](../../../../../3-transport/lessons/2-store-location-data)
* [Povezava strežniške kode s shrambo](../../../../../3-transport/lessons/2-store-location-data)

## Strukturirani in nestrukturirani podatki

Računalniški sistemi obdelujejo podatke, ki so lahko zelo raznoliki. Ti podatki lahko segajo od posameznih številk do velikih količin besedila, videov in slik ter IoT podatkov. Podatke običajno razdelimo v dve kategoriji - *strukturirani* podatki in *nestrukturirani* podatki.

* **Strukturirani podatki** so podatki z dobro definirano, togo strukturo, ki se ne spreminja, in običajno ustrezajo tabelam podatkov z odnosi. Primer so osebni podatki, kot so ime, datum rojstva in naslov.

* **Nestrukturirani podatki** so podatki brez dobro definirane, toge strukture, vključno s podatki, ki lahko pogosto spreminjajo strukturo. Primer so dokumenti, kot so pisni dokumenti ali preglednice.

✅ Raziskujte: Ali lahko pomislite na druge primere strukturiranih in nestrukturiranih podatkov?

> 💁 Obstajajo tudi polstrukturirani podatki, ki so strukturirani, vendar ne ustrezajo fiksnim tabelam podatkov.

IoT podatki se običajno štejejo za nestrukturirane podatke.

Predstavljajte si, da dodajate IoT naprave voznemu parku vozil velikega komercialnega kmetijskega podjetja. Morda boste želeli uporabiti različne naprave za različne vrste vozil. Na primer:

* Za kmetijska vozila, kot so traktorji, želite GPS podatke, da zagotovite, da delajo na pravih poljih.
* Za dostavne tovornjake, ki prevažajo hrano v skladišča, želite GPS podatke ter podatke o hitrosti in pospešku, da zagotovite varno vožnjo, identiteto voznika in podatke o začetku/koncu vožnje, da zagotovite skladnost z lokalnimi zakoni o delovnih urah.
* Za hladilne tovornjake želite tudi podatke o temperaturi, da zagotovite, da hrana med prevozom ne postane pretopla ali prehladna in se pokvari.

Ti podatki se lahko nenehno spreminjajo. Na primer, če je IoT naprava v kabini tovornjaka, se lahko podatki, ki jih pošilja, spremenijo, ko se priklopnik zamenja, na primer pošiljanje podatkov o temperaturi le, ko se uporablja hladilni priklopnik.

✅ Kakšne druge IoT podatke bi lahko zajeli? Razmislite o vrstah tovora, ki ga lahko tovornjaki prevažajo, ter o podatkih o vzdrževanju.

Ti podatki se razlikujejo od vozila do vozila, vendar se vsi pošiljajo isti IoT storitvi za obdelavo. IoT storitev mora biti sposobna obdelati te nestrukturirane podatke, jih shraniti na način, ki omogoča iskanje ali analizo, vendar deluje z različnimi strukturami teh podatkov.

### SQL vs NoSQL shranjevanje

Podatkovne baze so storitve, ki omogočajo shranjevanje in poizvedovanje podatkov. Podatkovne baze so dveh vrst - SQL in NoSQL.

#### SQL podatkovne baze

Prve podatkovne baze so bile Relacijski Sistemi za Upravljanje Podatkovnih Baz (RDBMS), ali relacijske podatkovne baze. Te so znane tudi kot SQL podatkovne baze po jeziku Structured Query Language (SQL), ki se uporablja za interakcijo z njimi za dodajanje, odstranjevanje, posodabljanje ali poizvedovanje podatkov. Te podatkovne baze sestavljajo shema - dobro definirana zbirka tabel podatkov, podobna preglednici. Vsaka tabela ima več poimenovanih stolpcev. Ko vstavite podatke, dodate vrstico v tabelo, pri čemer vnesete vrednosti v vsak stolpec. To ohranja podatke v zelo togi strukturi - čeprav lahko stolpce pustite prazne, morate ob dodajanju novega stolpca to storiti v podatkovni bazi, pri čemer morate vnesti vrednosti za obstoječe vrstice. Te podatkovne baze so relacijske - ena tabela lahko ima odnos do druge.

![Relacijska podatkovna baza, kjer ID tabele uporabnikov ustreza stolpcu ID uporabnika v tabeli nakupov, ID tabele izdelkov pa ustreza stolpcu ID izdelka v tabeli nakupov](../../../../../translated_images/sl/sql-database.be160f12bfccefd3.webp)

Na primer, če shranite osebne podatke uporabnika v tabelo, bi imeli nekakšen notranji edinstven ID za vsakega uporabnika, ki se uporablja v vrstici v tabeli, ki vsebuje ime in naslov uporabnika. Če bi nato želeli shraniti druge podrobnosti o tem uporabniku, kot so njegovi nakupi, v drugo tabelo, bi imeli en stolpec v novi tabeli za ID tega uporabnika. Ko poiščete uporabnika, lahko uporabite njegov ID za pridobitev njegovih osebnih podatkov iz ene tabele in njegovih nakupov iz druge.

SQL podatkovne baze so idealne za shranjevanje strukturiranih podatkov in za zagotavljanje, da podatki ustrezajo vaši shemi.

✅ Če še niste uporabljali SQL, si vzemite trenutek in preberite o njem na [SQL strani na Wikipediji](https://wikipedia.org/wiki/SQL).

Nekatere znane SQL podatkovne baze so Microsoft SQL Server, MySQL in PostgreSQL.

✅ Raziskujte: Preberite o nekaterih teh SQL podatkovnih bazah in njihovih zmožnostih.

#### NoSQL podatkovne baze

NoSQL podatkovne baze se imenujejo NoSQL, ker nimajo enake toge strukture kot SQL podatkovne baze. Znane so tudi kot dokumentne podatkovne baze, saj lahko shranjujejo nestrukturirane podatke, kot so dokumenti.

> 💁 Kljub svojemu imenu nekatere NoSQL podatkovne baze omogočajo uporabo SQL za poizvedovanje podatkov.

![Dokumenti v mapah v NoSQL podatkovni bazi](../../../../../translated_images/sl/noqsl-database.62d24ccf5b73f60d.webp)

NoSQL podatkovne baze nimajo vnaprej določene sheme, ki omejuje način shranjevanja podatkov, namesto tega lahko vstavite kakršne koli nestrukturirane podatke, običajno z uporabo JSON dokumentov. Ti dokumenti se lahko organizirajo v mape, podobno kot datoteke na vašem računalniku. Vsak dokument lahko ima različna polja od drugih dokumentov - na primer, če shranjujete IoT podatke iz vaših kmetijskih vozil, nekateri lahko imajo polja za podatke o pospešku in hitrosti, drugi pa polja za temperaturo v priklopniku. Če bi dodali novo vrsto tovornjaka, na primer takšnega z vgrajenimi tehtnicami za spremljanje teže prevoženega pridelka, bi vaša IoT naprava lahko dodala to novo polje, ki bi se shranilo brez kakršnih koli sprememb v podatkovni bazi.

Nekatere znane NoSQL podatkovne baze vključujejo Azure CosmosDB, MongoDB in CouchDB.

✅ Raziskujte: Preberite o nekaterih teh NoSQL podatkovnih bazah in njihovih zmožnostih.

V tej lekciji boste uporabljali NoSQL shranjevanje za shranjevanje IoT podatkov.

## Pošiljanje GPS podatkov v IoT Hub

V prejšnji lekciji ste zajeli GPS podatke iz GPS senzorja, povezanega z vašo IoT napravo. Da bi te IoT podatke shranili v oblaku, jih morate poslati v IoT storitev. Ponovno boste uporabljali Azure IoT Hub, isto IoT storitev v oblaku, ki ste jo uporabljali v prejšnjem projektu.

![Pošiljanje GPS telemetrije iz IoT naprave v IoT Hub](../../../../../translated_images/sl/gps-telemetry-iot-hub.8115335d51cd2c12.webp)

### Naloga - pošiljanje GPS podatkov v IoT Hub

1. Ustvarite nov IoT Hub z uporabo brezplačne stopnje.

    > ⚠️ Lahko se sklicujete na [navodila za ustvarjanje IoT Hub iz projekta 2, lekcija 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud), če je potrebno.

    Ne pozabite ustvariti nove skupine virov. Poimenujte novo skupino virov `gps-sensor`, nov IoT Hub pa z edinstvenim imenom, ki temelji na `gps-sensor`, na primer `gps-sensor-<vaše ime>`.

    > 💁 Če še imate svoj IoT Hub iz prejšnjega projekta, ga lahko ponovno uporabite. Ne pozabite uporabiti imena tega IoT Hub in skupine virov, v kateri je, pri ustvarjanju drugih storitev.

1. Dodajte novo napravo v IoT Hub. Poimenujte to napravo `gps-sensor`. Pridobite povezovalni niz za napravo.

1. Posodobite kodo naprave, da pošlje GPS podatke v nov IoT Hub z uporabo povezovalnega niza naprave iz prejšnjega koraka.

    > ⚠️ Lahko se sklicujete na [navodila za povezovanje vaše naprave z IoT iz projekta 2, lekcija 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service), če je potrebno.

1. Ko pošiljate GPS podatke, to storite kot JSON v naslednjem formatu:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Pošiljajte GPS podatke vsako minuto, da ne presežete dnevne omejitve sporočil.

Če uporabljate Wio Terminal, ne pozabite dodati vseh potrebnih knjižnic in nastaviti časa z uporabo NTP strežnika. Vaša koda mora tudi zagotoviti, da je prebrala vse podatke iz serijskega porta, preden pošlje GPS lokacijo, z uporabo obstoječe kode iz prejšnje lekcije. Uporabite naslednjo kodo za sestavljanje JSON dokumenta:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Če uporabljate virtualno IoT napravo, ne pozabite namestiti vseh potrebnih knjižnic z uporabo virtualnega okolja.

Za Raspberry Pi in virtualno IoT napravo uporabite obstoječo kodo iz prejšnje lekcije za pridobitev vrednosti zemljepisne širine in dolžine, nato jih pošljite v pravilnem JSON formatu z naslednjo kodo:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 To kodo lahko najdete v mapi [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) ali [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Zaženite kodo naprave in zagotovite, da sporočila tečejo v IoT Hub z uporabo ukaza CLI `az iot hub monitor-events`.

## Vroče, tople in hladne poti

Podatki, ki tečejo iz IoT naprave v oblak, niso vedno obdelani v realnem času. Nekateri podatki potrebujejo obdelavo v realnem času, drugi podatki se lahko obdelajo malo kasneje, tretji pa veliko kasneje. Tok podatkov v različne storitve, ki obdelujejo podatke ob različnih časih, se imenuje vroče, tople in hladne poti.

### Vroča pot

Vroča pot se nanaša na podatke, ki jih je treba obdelati v realnem času ali skoraj v realnem času. Vroče poti bi uporabili za opozorila, na primer za prejemanje opozoril, da se vozilo približuje skladišču ali da je temperatura v hladilnem tovornjaku previsoka.

Za uporabo podatkov vroče poti bi vaša koda reagirala na dogodke takoj, ko jih prejmejo vaše storitve v oblaku.

### Topla pot

Topla pot se nanaša na podatke, ki jih je mogoče obdelati kmalu po prejemu, na primer za poročanje ali kratkoročno analitiko. Toplo pot bi uporabili za dnevna poročila o prevoženih kilometrih vozil, z uporabo podatkov, zbranih prejšnji dan.

Podatki tople poti se shranijo takoj, ko jih prejme storitev v oblaku, v nekakšno shrambo, ki je hitro dostopna.

### Hladna pot

Hladna pot se nanaša na zgodovinske podatke, ki se shranjujejo dolgoročno in jih je mogoče obdelati kadar koli. Na primer, hladno pot bi lahko uporabili za pridobitev letnih poročil o prevoženih kilometrih vozil ali za analitiko poti, da bi našli najbolj optimalno pot za zmanjšanje stroškov goriva.

Podatki hladne poti se shranjujejo v podatkovnih skladiščih - podatkovnih bazah, zasnovanih za shranjevanje velikih količin podatkov, ki se nikoli ne spreminjajo in jih je mogoče hitro in enostavno poizvedovati. Običajno bi imeli redno nalogo v vaši aplikaciji v oblaku, ki bi se izvajala ob rednem času vsak dan, teden ali mesec, da bi premaknila podatke iz shrambe tople poti v podatkovno skladišče.

✅ Razmislite o podatkih, ki ste jih zajeli doslej v teh lekcijah. Ali so to vroči, topli ali hladni podatki?

## Obravnava GPS dogodkov z uporabo strežniške kode

Ko podatki tečejo v vaš IoT Hub, lahko napišete strežniško kodo, ki posluša dogodke, objavljene na Event-Hub združljivem končnem mestu. To je topla pot - ti podatki bodo shranjeni in uporabljeni v naslednji lekciji za poročanje o poti.

![Pošiljanje GPS telemetrije iz IoT naprave v IoT Hub, nato v Azure Functions prek sprožilca Event Hub](../../../../../translated_images/sl/gps-telemetry-iot-hub-functions.24d3fa5592455e9f.webp)

### Naloga - obravnava GPS dogodkov z uporabo strežniške kode

1. Ustvarite aplikacijo Azure Functions z uporabo CLI za Azure Functions. Uporabite Python runtime in jo ustvarite v mapi `gps-trigger`, pri čemer uporabite isto ime za ime projekta aplikacije Functions. Poskrbite, da ustvarite virtualno okolje za uporabo tega.
> ⚠️ Lahko se sklicujete na [navodila za ustvarjanje projekta Azure Functions iz projekta 2, lekcija 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application), če je potrebno.
1. Dodajte sprožilec dogodka IoT Hub, ki uporablja združljivo končno točko Event Hub.

    > ⚠️ Če potrebujete pomoč, si lahko ogledate [navodila za ustvarjanje sprožilca dogodka IoT Hub iz projekta 2, lekcija 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Nastavite niz povezave združljive končne točke Event Hub v datoteki `local.settings.json` in uporabite ključ za ta vnos v datoteki `function.json`.

1. Uporabite aplikacijo Azurite kot lokalni emulator za shranjevanje.

1. Zaženite aplikacijo funkcij, da preverite, ali prejema dogodke iz vaše GPS naprave. Prepričajte se, da vaša IoT naprava deluje in pošilja GPS podatke.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storage Accounts

![Logotip Azure Storage](../../../../../translated_images/sl/azure-storage-logo.605c0f602c640d48.webp)

Azure Storage Accounts je vsestranska storitev za shranjevanje podatkov, ki omogoča shranjevanje podatkov na različne načine. Podatke lahko shranjujete kot blob, v vrstah, tabelah ali datotekah, in to vse hkrati.

### Blob shranjevanje

Beseda *Blob* pomeni velike binarne objekte, vendar se uporablja za označevanje kakršnih koli nestrukturiranih podatkov. V blob shranjevanje lahko shranjujete kakršne koli podatke, od JSON dokumentov z IoT podatki do slik in filmskih datotek. Blob shranjevanje ima koncept *kontejnerjev*, imenovanih vedra, v katerih lahko shranjujete podatke, podobno kot tabele v relacijski bazi podatkov. Ti kontejnerji lahko vsebujejo eno ali več map za shranjevanje blobov, vsaka mapa pa lahko vsebuje druge mape, podobno kot datoteke na trdem disku vašega računalnika.

V tej lekciji boste uporabili blob shranjevanje za shranjevanje IoT podatkov.

✅ Raziskujte: Preberite več o [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Tabelno shranjevanje

Tabelno shranjevanje omogoča shranjevanje polstrukturiranih podatkov. Tabelno shranjevanje je pravzaprav NoSQL baza podatkov, zato ne zahteva vnaprej določenega nabora tabel, vendar je zasnovano za shranjevanje podatkov v eni ali več tabelah z edinstvenimi ključi za določanje vsake vrstice.

✅ Raziskujte: Preberite več o [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Vrstno shranjevanje

Vrstno shranjevanje omogoča shranjevanje sporočil velikosti do 64 KB v vrsti. Sporočila lahko dodate na konec vrste in jih preberete z začetka. Vrste shranjujejo sporočila neomejeno dolgo, dokler je na voljo prostor za shranjevanje, kar omogoča dolgoročno shranjevanje sporočil, ki jih lahko preberete, ko jih potrebujete. Na primer, če želite mesečno obdelati GPS podatke, jih lahko vsak dan dodate v vrsto, nato pa na koncu meseca obdelate vsa sporočila iz vrste.

✅ Raziskujte: Preberite več o [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Datotečno shranjevanje

Datotečno shranjevanje omogoča shranjevanje datotek v oblaku, do katerih lahko dostopajo aplikacije ali naprave prek standardnih industrijskih protokolov. Datoteke lahko zapišete v datotečno shranjevanje in ga nato priključite kot disk na vašem računalniku.

✅ Raziskujte: Preberite več o [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Povežite svojo strežniško kodo s shranjevanjem

Vaša aplikacija funkcij mora zdaj vzpostaviti povezavo z blob shranjevanjem za shranjevanje sporočil iz IoT Hub. Obstajata dva načina za to:

* Znotraj kode funkcije se povežite z blob shranjevanjem z uporabo Python SDK za blob shranjevanje in zapišite podatke kot blob.
* Uporabite izhodno vezavo funkcije, da povežete vrnjeno vrednost funkcije z blob shranjevanjem in samodejno shranite blob.

V tej lekciji boste uporabili Python SDK, da se naučite, kako delati z blob shranjevanjem.

![Pošiljanje GPS telemetrije iz IoT naprave v IoT Hub, nato v Azure Functions prek sprožilca dogodka Event Hub, nato pa shranjevanje v blob shranjevanje](../../../../../translated_images/sl/save-telemetry-to-storage-from-functions.ed3b1820980097f1.webp)

Podatki bodo shranjeni kot JSON blob v naslednji obliki:

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

### Naloga - povežite svojo strežniško kodo s shranjevanjem

1. Ustvarite Azure Storage račun. Poimenujte ga nekaj takega kot `gps<vaše ime>`.

    > ⚠️ Če potrebujete pomoč, si lahko ogledate [navodila za ustvarjanje računa za shranjevanje iz projekta 2, lekcija 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources).

    Če imate še vedno račun za shranjevanje iz prejšnjega projekta, ga lahko ponovno uporabite.

    > 💁 Ta račun za shranjevanje boste lahko uporabili za namestitev aplikacije Azure Functions pozneje v tej lekciji.

1. Zaženite naslednji ukaz, da pridobite niz povezave za račun za shranjevanje:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Zamenjajte `<storage_name>` z imenom računa za shranjevanje, ki ste ga ustvarili v prejšnjem koraku.

1. Dodajte nov vnos v datoteko `local.settings.json` za niz povezave vašega računa za shranjevanje, z uporabo vrednosti iz prejšnjega koraka. Poimenujte ga `STORAGE_CONNECTION_STRING`.

1. Dodajte naslednje v datoteko `requirements.txt`, da namestite Azure storage Pip pakete:

    ```sh
    azure-storage-blob
    ```

    Namestite pakete iz te datoteke v vašem virtualnem okolju.

    > Če dobite napako, posodobite svojo različico Pip v virtualnem okolju na najnovejšo različico z naslednjim ukazom, nato poskusite znova:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. V datoteki `__init__.py` za `iot-hub-trigger` dodajte naslednje uvozne izjave:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Sistem modul `json` bo uporabljen za branje in pisanje JSON, sistem modul `os` bo uporabljen za branje niza povezave, sistem modul `uuid` bo uporabljen za generiranje edinstvenega ID-ja za GPS odčitke.

    Paket `azure.storage.blob` vsebuje Python SDK za delo z blob shranjevanjem.

1. Pred metodo `main` dodajte naslednjo pomožno funkcijo:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    Python blob SDK nima pomožne metode za ustvarjanje kontejnerja, če ta ne obstaja. Ta koda bo naložila niz povezave iz datoteke `local.settings.json` (ali iz nastavitev aplikacije, ko bo nameščena v oblaku), nato pa ustvarila razred `BlobServiceClient`, da bo lahko delovala z računom za blob shranjevanje. Nato bo preiskala vse kontejnerje računa za blob shranjevanje in poiskala tistega z danim imenom - če ga najde, bo vrnila razred `ContainerClient`, ki lahko deluje s kontejnerjem za ustvarjanje blobov. Če ga ne najde, bo kontejner ustvarjen in vrnjen bo odjemalec za nov kontejner.

    Ko je nov kontejner ustvarjen, je omogočen javni dostop za poizvedovanje blobov v kontejnerju. To bo uporabljeno v naslednji lekciji za vizualizacijo GPS podatkov na zemljevidu.

1. Za razliko od podatkov o vlažnosti tal želimo s to kodo shraniti vsak dogodek, zato dodajte naslednjo kodo znotraj zanke `for event in events:` v funkciji `main`, pod izjavo `logging`:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Ta koda pridobi ID naprave iz metapodatkov dogodka in ga uporabi za ustvarjanje imena bloba. Blobi se lahko shranjujejo v mapah, ID naprave pa bo uporabljen za ime mape, tako da bo vsaka naprava imela vse svoje GPS dogodke v eni mapi. Ime bloba je ta mapa, ki ji sledi ime dokumenta, ločeno s poševnicami, podobno kot poti v Linuxu in macOS (podobno tudi v Windows, vendar Windows uporablja obrnjene poševnice). Ime dokumenta je edinstven ID, ustvarjen z modulom Python `uuid`, z datotečno končnico `json`.

    Na primer, za ID naprave `gps-sensor` bi lahko ime bloba bilo `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Dodajte naslednjo kodo pod to:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Ta koda pridobi odjemalca kontejnerja z uporabo pomožnega razreda `get_or_create_container`, nato pa pridobi objekt odjemalca bloba z uporabo imena bloba. Ti odjemalci blobov lahko se nanašajo na obstoječe blobe ali, kot v tem primeru, na nove blobe.

1. Dodajte naslednjo kodo za tem:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    To ustvari telo bloba, ki bo zapisano v blob shranjevanje. To je JSON dokument, ki vsebuje ID naprave, čas, ko je bila telemetrija poslana v IoT Hub, in GPS koordinate iz telemetrije.

    > 💁 Pomembno je uporabiti čas, ko je bilo sporočilo postavljeno v vrsto (enqueued time), namesto trenutnega časa, da dobimo čas, ko je bilo sporočilo poslano. Sporočilo bi lahko nekaj časa čakalo na hubu, preden ga prevzame aplikacija Functions.

1. Dodajte naslednje pod to kodo:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Ta koda zabeleži, da bo blob zapisan z njegovimi podrobnostmi, nato pa naloži telo bloba kot vsebino novega bloba.

1. Zaženite aplikacijo Functions. Videli boste, da se blobi zapisujejo za vse GPS dogodke v izhodu:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Prepričajte se, da ne izvajate monitorja dogodkov IoT Hub hkrati.

> 💁 To kodo lahko najdete v mapi [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Naloga - preverite naložene blobe

1. Za ogled ustvarjenih blobov lahko uporabite [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), brezplačno orodje, ki omogoča ogled in upravljanje vaših računov za shranjevanje, ali CLI.

    1. Za uporabo CLI najprej potrebujete ključ računa. Zaženite naslednji ukaz, da pridobite ta ključ:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Zamenjajte `<storage_name>` z imenom računa za shranjevanje.

        Kopirajte vrednost `key1`.

    1. Zaženite naslednji ukaz, da prikažete blobe v kontejnerju:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Zamenjajte `<storage_name>` z imenom računa za shranjevanje in `<key1>` z vrednostjo `key1`, ki ste jo kopirali v prejšnjem koraku.

        To bo prikazalo vse blobe v kontejnerju:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Prenesite enega od blobov z naslednjim ukazom:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Zamenjajte `<storage_name>` z imenom računa za shranjevanje in `<key1>` z vrednostjo `key1`, ki ste jo kopirali v prejšnjem koraku.

        Zamenjajte `<blob_name>` z polnim imenom iz stolpca `Name` v izhodu prejšnjega koraka, vključno z imenom mape. Zamenjajte `<file_name>` z imenom lokalne datoteke, kamor želite shraniti blob.

    Ko je prenesen, lahko odprete JSON datoteko v VS Code in videli boste blob, ki vsebuje podrobnosti GPS lokacije:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Naloga - namestite svojo aplikacijo Functions v oblak

Ko vaša aplikacija Functions deluje, jo lahko namestite v oblak.

1. Ustvarite novo aplikacijo Azure Functions, z uporabo računa za shranjevanje, ki ste ga ustvarili prej. Poimenujte jo nekaj takega kot `gps-sensor-` in dodajte edinstven identifikator na koncu, kot so naključne besede ali vaše ime.

    > ⚠️ Če potrebujete pomoč, si lahko ogledate [navodila za ustvarjanje aplikacije Functions iz projekta 2, lekcija 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources).

1. Naložite vrednosti `IOT_HUB_CONNECTION_STRING` in `STORAGE_CONNECTION_STRING` v nastavitve aplikacije.

    > ⚠️ Če potrebujete pomoč, si lahko ogledate [navodila za nalaganje nastavitev aplikacije iz projekta 2, lekcija 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

1. Namestite svojo lokalno aplikacijo Functions v oblak.
> ⚠️ Navodila za namestitev vaše aplikacije Functions iz projekta 2, lekcija 5, lahko najdete [tukaj](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud), če jih potrebujete.
---

## 🚀 Izziv

GPS podatki niso popolnoma natančni, zaznane lokacije pa so lahko oddaljene za nekaj metrov ali več, še posebej v predorih in območjih z visokimi stavbami.

Razmislite, kako bi satelitska navigacija lahko premagala to težavo? Katere podatke ima vaš sat-nav, ki bi mu omogočili boljše napovedi vaše lokacije?

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Pregled in samostojno učenje

* Preberite o strukturiranih podatkih na [strani o podatkovnih modelih na Wikipediji](https://wikipedia.org/wiki/Data_model)
* Preberite o polstrukturiranih podatkih na [strani o polstrukturiranih podatkih na Wikipediji](https://wikipedia.org/wiki/Semi-structured_data)
* Preberite o nestrukturiranih podatkih na [strani o nestrukturiranih podatkih na Wikipediji](https://wikipedia.org/wiki/Unstructured_data)
* Preberite več o Azure Storage in različnih vrstah shranjevanja v [dokumentaciji Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Naloga

[Raziskovanje funkcijskih vezav](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.