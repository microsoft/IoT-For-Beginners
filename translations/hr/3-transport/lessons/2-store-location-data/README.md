# Podaci o lokaciji trgovine

![Sketchnote pregled ove lekcije](../../../../../translated_images/hr/lesson-12.ca7f53039712a3ec.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Uvod

U prethodnoj lekciji naučili ste kako koristiti GPS senzor za prikupljanje podataka o lokaciji. Da biste te podatke koristili za vizualizaciju lokacije kamiona s hranom i njegovog putovanja, potrebno ih je poslati IoT usluzi u oblaku, a zatim negdje pohraniti.

U ovoj lekciji naučit ćete o različitim načinima pohrane IoT podataka i kako pohraniti podatke iz vaše IoT usluge koristeći serverless kod.

U ovoj lekciji obradit ćemo:

* [Strukturirani i nestrukturirani podaci](../../../../../3-transport/lessons/2-store-location-data)
* [Slanje GPS podataka u IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Vrući, topli i hladni putevi](../../../../../3-transport/lessons/2-store-location-data)
* [Obrada GPS događaja pomoću serverless koda](../../../../../3-transport/lessons/2-store-location-data)
* [Azure Storage računi](../../../../../3-transport/lessons/2-store-location-data)
* [Povezivanje serverless koda s pohranom](../../../../../3-transport/lessons/2-store-location-data)

## Strukturirani i nestrukturirani podaci

Računalni sustavi rade s podacima, a ti podaci dolaze u različitim oblicima i veličinama. Mogu varirati od pojedinačnih brojeva, do velikih količina teksta, do videozapisa i slika, pa sve do IoT podataka. Podaci se obično dijele u dvije kategorije - *strukturirani* podaci i *nestrukturirani* podaci.

* **Strukturirani podaci** su podaci s dobro definiranim, krutim strukturama koje se ne mijenjaju i obično se mapiraju na tablice podataka s odnosima. Jedan primjer su detalji osobe, uključujući ime, datum rođenja i adresu.

* **Nestrukturirani podaci** su podaci bez dobro definirane, krute strukture, uključujući podatke koji često mijenjaju strukturu. Jedan primjer su dokumenti poput pisanih dokumenata ili proračunskih tablica.

✅ Istražite: Možete li smisliti neke druge primjere strukturiranih i nestrukturiranih podataka?

> 💁 Postoje i polustrukturirani podaci koji su strukturirani, ali ne odgovaraju fiksnim tablicama podataka.

IoT podaci obično se smatraju nestrukturiranim podacima.

Zamislite da dodajete IoT uređaje voznom parku vozila za veliku komercijalnu farmu. Možda biste željeli koristiti različite uređaje za različite vrste vozila. Na primjer:

* Za poljoprivredna vozila poput traktora želite GPS podatke kako biste osigurali da rade na ispravnim poljima.
* Za dostavne kamione koji prevoze hranu u skladišta želite GPS podatke, kao i podatke o brzini i ubrzanju kako biste osigurali sigurnu vožnju, te identitet vozača i podatke o početku/završetku vožnje kako biste osigurali usklađenost vozača s lokalnim zakonima o radnom vremenu.
* Za kamione s hladnjačama također želite podatke o temperaturi kako biste osigurali da hrana ne postane previše topla ili hladna i pokvari se tijekom transporta.

Ovi podaci mogu se stalno mijenjati. Na primjer, ako je IoT uređaj u kabini kamiona, podaci koje šalje mogu se mijenjati kako se mijenja prikolica, na primjer, slanjem podataka o temperaturi samo kada se koristi prikolica s hladnjačom.

✅ Koje druge IoT podatke biste mogli prikupljati? Razmislite o vrstama tereta koje kamioni mogu prevoziti, kao i o podacima o održavanju.

Ovi podaci variraju od vozila do vozila, ali svi se šalju istoj IoT usluzi na obradu. IoT usluga mora biti sposobna obraditi ove nestrukturirane podatke, pohranjujući ih na način koji omogućuje pretraživanje ili analizu, ali funkcionira s različitim strukturama tih podataka.

### SQL vs NoSQL pohrana

Baze podataka su usluge koje omogućuju pohranu i upite podataka. Baze podataka dolaze u dva tipa - SQL i NoSQL.

#### SQL baze podataka

Prve baze podataka bile su sustavi za upravljanje relacijskim bazama podataka (RDBMS), ili relacijske baze podataka. Također su poznate kao SQL baze podataka prema jeziku Structured Query Language (SQL) koji se koristi za interakciju s njima radi dodavanja, uklanjanja, ažuriranja ili upita podataka. Ove baze podataka sastoje se od sheme - dobro definiranog skupa tablica podataka, sličnog proračunskoj tablici. Svaka tablica ima više imenovanih stupaca. Kada unosite podatke, dodajete redak u tablicu, stavljajući vrijednosti u svaki od stupaca. To održava podatke u vrlo krutoj strukturi - iako možete ostaviti stupce prazne, ako želite dodati novi stupac, morate to učiniti na bazi podataka, popunjavajući vrijednosti za postojeće retke. Ove baze podataka su relacijske - u smislu da jedna tablica može imati odnos prema drugoj.

![Relacijska baza podataka s ID-om tablice korisnika koji se odnosi na stupac ID korisnika tablice kupovina, i ID-om tablice proizvoda koji se odnosi na ID proizvoda tablice kupovina](../../../../../translated_images/hr/sql-database.be160f12bfccefd3.webp)

Na primjer, ako pohranjujete osobne podatke korisnika u tablicu, imali biste neku vrstu internog jedinstvenog ID-a po korisniku koji se koristi u retku u tablici koja sadrži ime i adresu korisnika. Ako zatim želite pohraniti druge detalje o tom korisniku, poput njegovih kupovina, u drugu tablicu, imali biste jedan stupac u novoj tablici za ID tog korisnika. Kada tražite korisnika, možete koristiti njegov ID za dobivanje osobnih podataka iz jedne tablice i njegovih kupovina iz druge.

SQL baze podataka idealne su za pohranu strukturiranih podataka i za osiguranje da podaci odgovaraju vašoj shemi.

✅ Ako niste koristili SQL prije, odvojite trenutak da pročitate o njemu na [SQL stranici na Wikipediji](https://wikipedia.org/wiki/SQL).

Neke poznate SQL baze podataka su Microsoft SQL Server, MySQL i PostgreSQL.

✅ Istražite: Pročitajte o nekim od ovih SQL baza podataka i njihovim mogućnostima.

#### NoSQL baze podataka

NoSQL baze podataka nazivaju se NoSQL jer nemaju istu krutu strukturu kao SQL baze podataka. Također su poznate kao dokumentne baze podataka jer mogu pohranjivati nestrukturirane podatke poput dokumenata.

> 💁 Unatoč njihovom nazivu, neke NoSQL baze podataka omogućuju korištenje SQL-a za upite podataka.

![Dokumenti u mapama u NoSQL bazi podataka](../../../../../translated_images/hr/noqsl-database.62d24ccf5b73f60d.webp)

NoSQL baze podataka nemaju unaprijed definiranu shemu koja ograničava način pohrane podataka, umjesto toga možete umetnuti bilo koje nestrukturirane podatke, obično koristeći JSON dokumente. Ovi dokumenti mogu se organizirati u mape, slično datotekama na vašem računalu. Svaki dokument može imati različita polja od drugih dokumenata - na primjer, ako pohranjujete IoT podatke s vaših poljoprivrednih vozila, neki mogu imati polja za podatke akcelerometra i brzine, drugi mogu imati polja za temperaturu u prikolici. Ako biste dodali novu vrstu kamiona, poput onog s ugrađenim vagama za praćenje težine prevezenih proizvoda, vaš IoT uređaj mogao bi dodati ovo novo polje i ono bi se moglo pohraniti bez ikakvih promjena u bazi podataka.

Neke poznate NoSQL baze podataka uključuju Azure CosmosDB, MongoDB i CouchDB.

✅ Istražite: Pročitajte o nekim od ovih NoSQL baza podataka i njihovim mogućnostima.

U ovoj lekciji koristit ćete NoSQL pohranu za pohranu IoT podataka.

## Slanje GPS podataka u IoT Hub

U prethodnoj lekciji ste prikupili GPS podatke s GPS senzora povezanog s vašim IoT uređajem. Da biste pohranili ove IoT podatke u oblaku, morate ih poslati IoT usluzi. Ponovno ćete koristiti Azure IoT Hub, istu IoT uslugu u oblaku koju ste koristili u prethodnom projektu.

![Slanje GPS telemetrije s IoT uređaja u IoT Hub](../../../../../translated_images/hr/gps-telemetry-iot-hub.8115335d51cd2c12.webp)

### Zadatak - slanje GPS podataka u IoT Hub

1. Kreirajte novi IoT Hub koristeći besplatni sloj.

    > ⚠️ Možete se referirati na [upute za kreiranje IoT Hub-a iz projekta 2, lekcija 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) ako je potrebno.

    Zapamtite da kreirate novu Resource Group. Nazovite novu Resource Group `gps-sensor`, a novi IoT Hub jedinstvenim imenom temeljenim na `gps-sensor`, poput `gps-sensor-<vaše ime>`.

    > 💁 Ako još uvijek imate svoj IoT Hub iz prethodnog projekta, možete ga ponovno koristiti. Zapamtite koristiti ime ovog IoT Hub-a i Resource Group u kojoj se nalazi prilikom kreiranja drugih usluga.

1. Dodajte novi uređaj u IoT Hub. Nazovite ovaj uređaj `gps-sensor`. Zabilježite vezni niz za uređaj.

1. Ažurirajte kod vašeg uređaja kako biste poslali GPS podatke u novi IoT Hub koristeći vezni niz uređaja iz prethodnog koraka.

    > ⚠️ Možete se referirati na [upute za povezivanje vašeg uređaja s IoT-om iz projekta 2, lekcija 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) ako je potrebno.

1. Kada šaljete GPS podatke, učinite to kao JSON u sljedećem formatu:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Šaljite GPS podatke svake minute kako ne biste potrošili dnevnu kvotu poruka.

Ako koristite Wio Terminal, zapamtite dodati sve potrebne biblioteke i postaviti vrijeme koristeći NTP server. Vaš kod također mora osigurati da je pročitao sve podatke s serijskog porta prije slanja GPS lokacije, koristeći postojeći kod iz prethodne lekcije. Koristite sljedeći kod za konstrukciju JSON dokumenta:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Ako koristite virtualni IoT uređaj, zapamtite instalirati sve potrebne biblioteke koristeći virtualno okruženje.

Za Raspberry Pi i virtualni IoT uređaj, koristite postojeći kod iz prethodne lekcije za dobivanje vrijednosti latitude i longitude, zatim ih pošaljite u ispravnom JSON formatu koristeći sljedeći kod:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Ovaj kod možete pronaći u mapi [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) ili [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Pokrenite kod vašeg uređaja i osigurajte da poruke teku u IoT Hub koristeći CLI naredbu `az iot hub monitor-events`.

## Vrući, topli i hladni putevi

Podaci koji teku s IoT uređaja u oblak ne obrađuju se uvijek u stvarnom vremenu. Neki podaci zahtijevaju obradu u stvarnom vremenu, drugi se mogu obraditi malo kasnije, a neki se mogu obraditi mnogo kasnije. Tok podataka prema različitim uslugama koje obrađuju podatke u različitim vremenskim okvirima naziva se vrući, topli i hladni putevi.

### Vrući put

Vrući put odnosi se na podatke koji se moraju obraditi u stvarnom vremenu ili gotovo stvarnom vremenu. Koristili biste podatke vrućeg puta za upozorenja, poput dobivanja upozorenja da se vozilo približava skladištu ili da je temperatura u kamionu s hladnjačom previsoka.

Za korištenje podataka vrućeg puta, vaš kod bi reagirao na događaje čim ih primi vaše usluge u oblaku.

### Topli put

Topli put odnosi se na podatke koji se mogu obraditi malo nakon što su primljeni, na primjer za izvještavanje ili kratkoročnu analitiku. Koristili biste podatke toplog puta za dnevna izvješća o kilometraži vozila, koristeći podatke prikupljene prethodnog dana.

Podaci toplog puta pohranjuju se čim ih primi usluga u oblaku unutar neke vrste pohrane koja se može brzo pristupiti.

### Hladni put

Hladni put odnosi se na povijesne podatke, pohranjivanje podataka za dugoročno korištenje i obradu kad god je potrebno. Na primjer, mogli biste koristiti hladni put za dobivanje godišnjih izvješća o kilometraži vozila ili za analizu ruta kako biste pronašli najoptimalniju rutu za smanjenje troškova goriva.

Podaci hladnog puta pohranjuju se u skladištima podataka - bazama podataka dizajniranim za pohranu velikih količina podataka koji se nikada neće mijenjati i mogu se brzo i jednostavno upititi. Obično biste imali redoviti zadatak u vašoj aplikaciji u oblaku koji bi se pokretao u redovitim intervalima svaki dan, tjedan ili mjesec za premještanje podataka iz pohrane toplog puta u skladište podataka.

✅ Razmislite o podacima koje ste dosad prikupili u ovim lekcijama. Jesu li to podaci vrućeg, toplog ili hladnog puta?

## Obrada GPS događaja pomoću serverless koda

Kada podaci teku u vaš IoT Hub, možete napisati serverless kod za slušanje događaja objavljenih na Event-Hub kompatibilnom endpointu. Ovo je topli put - ovi podaci će se pohraniti i koristiti u sljedećoj lekciji za izvještavanje o putovanju.

![Slanje GPS telemetrije s IoT uređaja u IoT Hub, zatim u Azure Functions putem okidača event hub-a](../../../../../translated_images/hr/gps-telemetry-iot-hub-functions.24d3fa5592455e9f.webp)

### Zadatak - obrada GPS događaja pomoću serverless koda

1. Kreirajte Azure Functions aplikaciju koristeći Azure Functions CLI. Koristite Python runtime i kreirajte je u mapi nazvanoj `gps-trigger`, koristeći isto ime za naziv projekta Functions App. Obavezno kreirajte virtualno okruženje za korištenje.
> ⚠️ Možete se referirati na [upute za kreiranje Azure Functions projekta iz projekta 2, lekcije 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) ako je potrebno.
1. Dodajte IoT Hub događajni okidač koji koristi kompatibilnu krajnju točku Event Hub-a IoT Hub-a.

    > ⚠️ Možete se pozvati na [upute za stvaranje IoT Hub događajnog okidača iz projekta 2, lekcija 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) ako je potrebno.

1. Postavite niz za povezivanje kompatibilne krajnje točke Event Hub-a u datoteku `local.settings.json` i koristite ključ za taj unos u datoteci `function.json`.

1. Koristite aplikaciju Azurite kao lokalni emulator za pohranu.

1. Pokrenite svoju funkcijsku aplikaciju kako biste osigurali da prima događaje s vašeg GPS uređaja. Provjerite je li vaš IoT uređaj također pokrenut i šalje GPS podatke.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storage računi

![Logo Azure Storage-a](../../../../../translated_images/hr/azure-storage-logo.605c0f602c640d48.webp)

Azure Storage računi su univerzalna usluga za pohranu koja može pohranjivati podatke na različite načine. Možete pohranjivati podatke kao blobove, u redovima, u tablicama ili kao datoteke, i sve to istovremeno.

### Blob pohrana

Riječ *Blob* označava binarne velike objekte, ali se koristi za bilo koje nestrukturirane podatke. U blob pohranu možete pohranjivati bilo koje podatke, od JSON dokumenata koji sadrže IoT podatke, do slika i video datoteka. Blob pohrana ima koncept *kontejnera*, nazvanih spremnika u koje možete pohranjivati podatke, slično tablicama u relacijskim bazama podataka. Ti kontejneri mogu imati jednu ili više mapa za pohranu blobova, a svaka mapa može sadržavati druge mape, slično načinu na koji su datoteke pohranjene na tvrdom disku vašeg računala.

U ovoj lekciji koristit ćete blob pohranu za pohranu IoT podataka.

✅ Istražite: Pročitajte više o [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Pohrana u tablicama

Pohrana u tablicama omogućuje pohranu polustrukturiranih podataka. Pohrana u tablicama zapravo je NoSQL baza podataka, pa ne zahtijeva unaprijed definirani skup tablica, ali je dizajnirana za pohranu podataka u jednoj ili više tablica, s jedinstvenim ključevima za definiranje svakog retka.

✅ Istražite: Pročitajte više o [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Pohrana u redovima

Pohrana u redovima omogućuje pohranu poruka veličine do 64KB u red. Možete dodavati poruke na kraj reda i čitati ih s početka. Redovi pohranjuju poruke neograničeno dugo dok god ima prostora za pohranu, što omogućuje dugoročno pohranjivanje poruka koje se mogu čitati kada je potrebno. Na primjer, ako želite pokrenuti mjesečni zadatak za obradu GPS podataka, možete ih dodavati u red svaki dan tijekom mjeseca, a zatim na kraju mjeseca obraditi sve poruke iz reda.

✅ Istražite: Pročitajte više o [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Pohrana datoteka

Pohrana datoteka omogućuje pohranu datoteka u oblaku, a aplikacije ili uređaji mogu se povezati koristeći standardne industrijske protokole. Možete zapisivati datoteke u pohranu datoteka, a zatim ih montirati kao disk na vašem PC-u ili Mac-u.

✅ Istražite: Pročitajte više o [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Povežite svoj serverless kod s pohranom

Vaša funkcijska aplikacija sada treba povezati blob pohranu kako bi pohranjivala poruke iz IoT Hub-a. Postoje dva načina za to:

* Unutar koda funkcije, povežite se s blob pohranom koristeći Python SDK za blob pohranu i zapisujte podatke kao blobove.
* Koristite izlaznu funkcijsku vezu za povezivanje povratne vrijednosti funkcije s blob pohranom i automatski spremite blob.

U ovoj lekciji koristit ćete Python SDK kako biste vidjeli kako raditi s blob pohranom.

![Slanje GPS telemetrije s IoT uređaja na IoT Hub, zatim na Azure Functions putem okidača Event Hub-a, pa spremanje u blob pohranu](../../../../../translated_images/hr/save-telemetry-to-storage-from-functions.ed3b1820980097f1.webp)

Podaci će biti pohranjeni kao JSON blob u sljedećem formatu:

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

### Zadatak - povežite svoj serverless kod s pohranom

1. Kreirajte Azure Storage račun. Nazovite ga nešto poput `gps<vaše ime>`.

    > ⚠️ Možete se pozvati na [upute za kreiranje računa za pohranu iz projekta 2, lekcija 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) ako je potrebno.

    Ako još uvijek imate račun za pohranu iz prethodnog projekta, možete ga ponovno koristiti.

    > 💁 Moći ćete koristiti isti račun za pohranu za implementaciju vaše Azure Functions aplikacije kasnije u ovoj lekciji.

1. Pokrenite sljedeću naredbu kako biste dobili niz za povezivanje za račun za pohranu:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Zamijenite `<storage_name>` imenom računa za pohranu koji ste kreirali u prethodnom koraku.

1. Dodajte novi unos u datoteku `local.settings.json` za niz za povezivanje vašeg računa za pohranu, koristeći vrijednost iz prethodnog koraka. Nazovite ga `STORAGE_CONNECTION_STRING`.

1. Dodajte sljedeće u datoteku `requirements.txt` kako biste instalirali Azure storage Pip pakete:

    ```sh
    azure-storage-blob
    ```

    Instalirajte pakete iz ove datoteke u vašem virtualnom okruženju.

    > Ako dobijete grešku, nadogradite svoju verziju Pip-a u virtualnom okruženju na najnoviju verziju koristeći sljedeću naredbu, a zatim pokušajte ponovno:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. U datoteci `__init__.py` za `iot-hub-trigger`, dodajte sljedeće naredbe za uvoz:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Modul sustava `json` koristit će se za čitanje i pisanje JSON-a, modul sustava `os` koristit će se za čitanje niza za povezivanje, modul sustava `uuid` koristit će se za generiranje jedinstvenog ID-a za GPS očitanje.

    Paket `azure.storage.blob` sadrži Python SDK za rad s blob pohranom.

1. Prije metode `main`, dodajte sljedeću pomoćnu funkciju:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    Python blob SDK nema pomoćnu metodu za kreiranje kontejnera ako ne postoji. Ovaj kod učitava niz za povezivanje iz datoteke `local.settings.json` (ili iz postavki aplikacije nakon implementacije u oblak), zatim kreira klasu `BlobServiceClient` iz ovog niza za interakciju s računom za blob pohranu. Zatim prolazi kroz sve kontejnere za račun blob pohrane, tražeći onaj s danim imenom - ako ga pronađe, vraća klasu `ContainerClient` koja može komunicirati s kontejnerom za kreiranje blobova. Ako ga ne pronađe, kontejner se kreira i vraća se klijent za novi kontejner.

    Kada se kreira novi kontejner, javni pristup se omogućuje za upite blobova u kontejneru. Ovo će se koristiti u sljedećoj lekciji za vizualizaciju GPS podataka na karti.

1. Za razliku od vlažnosti tla, s ovim kodom želimo pohraniti svaki događaj, pa dodajte sljedeći kod unutar petlje `for event in events:` u funkciji `main`, ispod `logging` izjave:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Ovaj kod dobiva ID uređaja iz metapodataka događaja, zatim ga koristi za kreiranje imena bloba. Blobovi se mogu pohranjivati u mape, a ID uređaja koristit će se za ime mape, tako da svaki uređaj ima sve svoje GPS događaje u jednoj mapi. Ime bloba je ova mapa, praćena imenom dokumenta, odvojena kosim crticama, slično Linux i macOS putanjama (slično i Windowsu, ali Windows koristi obrnute kose crte). Ime dokumenta je jedinstveni ID generiran pomoću Python modula `uuid`, s tipom datoteke `json`.

    Na primjer, za ID uređaja `gps-sensor`, ime bloba može biti `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Dodajte sljedeći kod ispod ovoga:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Ovaj kod dobiva klijent kontejnera koristeći pomoćnu klasu `get_or_create_container`, a zatim dobiva objekt klijenta bloba koristeći ime bloba. Ovi klijenti bloba mogu se odnositi na postojeće blobove ili, kao u ovom slučaju, na nove blobove.

1. Dodajte sljedeći kod nakon ovoga:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    Ovo gradi tijelo bloba koje će biti zapisano u blob pohranu. To je JSON dokument koji sadrži ID uređaja, vrijeme kada je telemetrija poslana na IoT Hub i GPS koordinate iz telemetrije.

    > 💁 Važno je koristiti vrijeme kada je poruka stavljena u red (enqueued time) umjesto trenutnog vremena kako biste dobili vrijeme kada je poruka poslana. Mogla bi biti na hub-u neko vrijeme prije nego što je preuzme Functions aplikacija ako nije pokrenuta.

1. Dodajte sljedeće ispod ovog koda:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Ovaj kod bilježi da će blob biti zapisan s njegovim detaljima, zatim učitava tijelo bloba kao sadržaj novog bloba.

1. Pokrenite Functions aplikaciju. Vidjet ćete da se blobovi zapisuju za sve GPS događaje u izlazu:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Provjerite da ne pokrećete IoT Hub monitor događaja u isto vrijeme.

> 💁 Ovaj kod možete pronaći u [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions) mapi.

### Zadatak - provjerite učitane blobove

1. Za pregled kreiranih blobova možete koristiti [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), besplatan alat koji omogućuje pregled i upravljanje vašim računima za pohranu, ili CLI.

    1. Za korištenje CLI-a, prvo ćete trebati ključ računa. Pokrenite sljedeću naredbu kako biste dobili ovaj ključ:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Zamijenite `<storage_name>` imenom računa za pohranu.

        Kopirajte vrijednost `key1`.

    1. Pokrenite sljedeću naredbu za popis blobova u kontejneru:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Zamijenite `<storage_name>` imenom računa za pohranu i `<key1>` vrijednošću `key1` koju ste kopirali u prethodnom koraku.

        Ovo će popisati sve blobove u kontejneru:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Preuzmite jedan od blobova koristeći sljedeću naredbu:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Zamijenite `<storage_name>` imenom računa za pohranu i `<key1>` vrijednošću `key1` koju ste kopirali u prethodnom koraku.

        Zamijenite `<blob_name>` punim imenom iz stupca `Name` izlaza iz prethodnog koraka, uključujući ime mape. Zamijenite `<file_name>` imenom lokalne datoteke za spremanje bloba.

    Nakon preuzimanja, možete otvoriti JSON datoteku u VS Code-u i vidjet ćete blob koji sadrži detalje GPS lokacije:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Zadatak - implementirajte svoju Functions aplikaciju u oblak

Sada kada vaša Functions aplikacija radi, možete je implementirati u oblak.

1. Kreirajte novu Azure Functions aplikaciju, koristeći račun za pohranu koji ste kreirali ranije. Nazovite je nešto poput `gps-sensor-` i dodajte jedinstveni identifikator na kraju, poput nasumičnih riječi ili vašeg imena.

    > ⚠️ Možete se pozvati na [upute za kreiranje Functions aplikacije iz projekta 2, lekcija 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) ako je potrebno.

1. Učitajte vrijednosti `IOT_HUB_CONNECTION_STRING` i `STORAGE_CONNECTION_STRING` u postavke aplikacije.

    > ⚠️ Možete se pozvati na [upute za učitavanje postavki aplikacije iz projekta 2, lekcija 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) ako je potrebno.

1. Implementirajte svoju lokalnu Functions aplikaciju u oblak.
> ⚠️ Možete se pozvati na [upute za implementaciju vaše Functions aplikacije iz projekta 2, lekcije 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) ako je potrebno.
## 🚀 Izazov

GPS podaci nisu savršeno precizni, a lokacije koje se detektiraju mogu odstupati za nekoliko metara, ako ne i više, posebno u tunelima i područjima s visokim zgradama.

Razmislite o tome kako satelitska navigacija može prevladati ovaj problem? Koje podatke vaš sat-nav ima koji bi mu omogućili da bolje predvidi vašu lokaciju?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Pregled i samostalno učenje

* Pročitajte o strukturiranim podacima na [stranici o modelu podataka na Wikipediji](https://wikipedia.org/wiki/Data_model)
* Pročitajte o polustrukturiranim podacima na [stranici o polustrukturiranim podacima na Wikipediji](https://wikipedia.org/wiki/Semi-structured_data)
* Pročitajte o nestrukturiranim podacima na [stranici o nestrukturiranim podacima na Wikipediji](https://wikipedia.org/wiki/Unstructured_data)
* Saznajte više o Azure Storage i različitim vrstama pohrane u [dokumentaciji za Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Zadatak

[Istražite funkcijske veze](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.