<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-28T09:53:12+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "ro"
}
-->
# Stocarea datelor de locație

![O prezentare grafică a lecției](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.ro.jpg)

> Prezentare grafică realizată de [Nitya Narasimhan](https://github.com/nitya). Click pe imagine pentru o versiune mai mare.

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Introducere

În lecția anterioară, ai învățat cum să folosești un senzor GPS pentru a captura date de locație. Pentru a utiliza aceste date pentru a vizualiza locația unui camion încărcat cu alimente și traseul său, acestea trebuie trimise către un serviciu IoT în cloud și apoi stocate undeva.

În această lecție vei învăța despre diferitele moduri de a stoca date IoT și cum să stochezi datele din serviciul tău IoT folosind cod serverless.

În această lecție vom acoperi:

* [Date structurate și nestructurate](../../../../../3-transport/lessons/2-store-location-data)
* [Trimiterea datelor GPS către un IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Căi fierbinți, calde și reci](../../../../../3-transport/lessons/2-store-location-data)
* [Gestionarea evenimentelor GPS folosind cod serverless](../../../../../3-transport/lessons/2-store-location-data)
* [Conturi de stocare Azure](../../../../../3-transport/lessons/2-store-location-data)
* [Conectarea codului serverless la stocare](../../../../../3-transport/lessons/2-store-location-data)

## Date structurate și nestructurate

Sistemele informatice lucrează cu date, iar aceste date vin în diverse forme și dimensiuni. Ele pot varia de la numere simple, la cantități mari de text, la videoclipuri și imagini, și la date IoT. Datele pot fi de obicei împărțite în una dintre cele două categorii - *date structurate* și *date nestructurate*.

* **Date structurate** sunt date cu o structură bine definită, rigidă, care nu se schimbă și de obicei se potrivesc cu tabele de date cu relații. Un exemplu este detaliile unei persoane, inclusiv numele, data nașterii și adresa.

* **Date nestructurate** sunt date fără o structură bine definită, rigidă, inclusiv date care pot schimba structura frecvent. Un exemplu este documentele, cum ar fi documentele scrise sau foile de calcul.

✅ Fă un pic de cercetare: Poți să te gândești la alte exemple de date structurate și nestructurate?

> 💁 Există și date semi-structurate care sunt structurate, dar nu se potrivesc în tabele fixe de date.

Datele IoT sunt de obicei considerate date nestructurate.

Imaginează-ți că adaugi dispozitive IoT la o flotă de vehicule pentru o fermă comercială mare. Ai putea dori să folosești dispozitive diferite pentru diferite tipuri de vehicule. De exemplu:

* Pentru vehiculele agricole, cum ar fi tractoarele, vrei date GPS pentru a te asigura că lucrează pe câmpurile corecte.
* Pentru camioanele de livrare care transportă alimente către depozite, vrei date GPS, precum și date despre viteză și accelerație pentru a te asigura că șoferul conduce în siguranță, și date despre identitatea șoferului și pornire/oprire pentru a te asigura că respectă legile locale privind orele de lucru.
* Pentru camioanele frigorifice, vrei și date despre temperatură pentru a te asigura că alimentele nu se încălzesc sau răcesc prea mult și nu se strică în timpul transportului.

Aceste date pot varia constant. De exemplu, dacă dispozitivul IoT se află în cabina unui camion, datele pe care le trimite pot varia pe măsură ce remorca se schimbă, de exemplu trimițând date despre temperatură doar atunci când este utilizată o remorcă frigorifică.

✅ Ce alte date IoT ar putea fi capturate? Gândește-te la tipurile de încărcături pe care le pot transporta camioanele, precum și la datele de întreținere.

Aceste date variază de la vehicul la vehicul, dar toate sunt trimise către același serviciu IoT pentru procesare. Serviciul IoT trebuie să fie capabil să proceseze aceste date nestructurate, stocându-le într-un mod care permite căutarea sau analiza, dar funcționează cu structuri diferite ale acestor date.

### Stocare SQL vs NoSQL

Bazele de date sunt servicii care îți permit să stochezi și să interoghezi date. Bazele de date vin în două tipuri - SQL și NoSQL.

#### Baze de date SQL

Primele baze de date au fost Sisteme de Management al Bazelor de Date Relaționale (RDBMS), sau baze de date relaționale. Acestea sunt cunoscute și sub numele de baze de date SQL datorită limbajului Structured Query Language (SQL) utilizat pentru a interacționa cu ele pentru a adăuga, elimina, actualiza sau interoga date. Aceste baze de date constau într-un schemă - un set bine definit de tabele de date, similar cu o foaie de calcul. Fiecare tabel are mai multe coloane denumite. Când inserezi date, adaugi un rând în tabel, punând valori în fiecare dintre coloane. Acest lucru păstrează datele într-o structură foarte rigidă - deși poți lăsa coloanele goale, dacă vrei să adaugi o nouă coloană trebuie să faci acest lucru în baza de date, populând valori pentru rândurile existente. Aceste baze de date sunt relaționale - în sensul că un tabel poate avea o relație cu altul.

![O bază de date relațională cu ID-ul tabelului User care se referă la coloana user ID din tabelul purchases, și ID-ul tabelului products care se referă la coloana product ID din tabelul purchases](../../../../../translated_images/sql-database.be160f12bfccefd3.ro.png)

De exemplu, dacă stochezi detaliile personale ale unui utilizator într-un tabel, ai avea un fel de ID unic intern pentru fiecare utilizator care este utilizat într-un rând dintr-un tabel care conține numele și adresa utilizatorului. Dacă apoi vrei să stochezi alte detalii despre acel utilizator, cum ar fi achizițiile sale, într-un alt tabel, ai avea o coloană în noul tabel pentru ID-ul utilizatorului. Când cauți un utilizator, poți folosi ID-ul său pentru a obține detaliile personale dintr-un tabel și achizițiile sale din altul.

Baze de date SQL sunt ideale pentru stocarea datelor structurate și pentru atunci când vrei să te asiguri că datele se potrivesc cu schema ta.

✅ Dacă nu ai folosit SQL înainte, ia un moment să citești despre el pe [pagina SQL de pe Wikipedia](https://wikipedia.org/wiki/SQL).

Unele baze de date SQL cunoscute sunt Microsoft SQL Server, MySQL și PostgreSQL.

✅ Fă un pic de cercetare: Citește despre unele dintre aceste baze de date SQL și capacitățile lor.

#### Baze de date NoSQL

Baze de date NoSQL sunt numite NoSQL deoarece nu au aceeași structură rigidă ca bazele de date SQL. Ele sunt cunoscute și sub numele de baze de date de documente, deoarece pot stoca date nestructurate, cum ar fi documente.

> 💁 În ciuda numelui lor, unele baze de date NoSQL îți permit să folosești SQL pentru a interoga datele.

![Documente în foldere într-o bază de date NoSQL](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.ro.png)

Baze de date NoSQL nu au o schemă predefinită care limitează modul în care sunt stocate datele, în schimb poți insera orice date nestructurate, de obicei folosind documente JSON. Aceste documente pot fi organizate în foldere, similar cu fișierele de pe computerul tău. Fiecare document poate avea câmpuri diferite față de alte documente - de exemplu, dacă stocai date IoT de la vehiculele tale agricole, unele ar putea avea câmpuri pentru datele accelerometrului și vitezei, altele ar putea avea câmpuri pentru temperatura din remorcă. Dacă ai adăuga un nou tip de camion, cum ar fi unul cu cântare integrate pentru a urmări greutatea produselor transportate, atunci dispozitivul tău IoT ar putea adăuga acest nou câmp și ar putea fi stocat fără modificări ale bazei de date.

Unele baze de date NoSQL cunoscute includ Azure CosmosDB, MongoDB și CouchDB.

✅ Fă un pic de cercetare: Citește despre unele dintre aceste baze de date NoSQL și capacitățile lor.

În această lecție, vei folosi stocarea NoSQL pentru a stoca date IoT.

## Trimiterea datelor GPS către un IoT Hub

În lecția anterioară, ai capturat date GPS de la un senzor GPS conectat la dispozitivul tău IoT. Pentru a stoca aceste date IoT în cloud, trebuie să le trimiți către un serviciu IoT. Din nou, vei folosi Azure IoT Hub, același serviciu IoT în cloud pe care l-ai utilizat în proiectul anterior.

![Trimiterea telemetriei GPS de la un dispozitiv IoT către IoT Hub](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.ro.png)

### Sarcină - trimite date GPS către un IoT Hub

1. Creează un nou IoT Hub folosind nivelul gratuit.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea unui IoT Hub din proiectul 2, lecția 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) dacă este necesar.

    Amintește-ți să creezi un nou Grup de Resurse. Denumește noul Grup de Resurse `gps-sensor`, iar noul IoT Hub un nume unic bazat pe `gps-sensor`, cum ar fi `gps-sensor-<numele tău>`.

    > 💁 Dacă încă ai IoT Hub-ul din proiectul anterior, îl poți reutiliza. Amintește-ți să folosești numele acestui IoT Hub și Grupul de Resurse în care se află atunci când creezi alte servicii.

1. Adaugă un nou dispozitiv la IoT Hub. Denumește acest dispozitiv `gps-sensor`. Obține șirul de conexiune pentru dispozitiv.

1. Actualizează codul dispozitivului tău pentru a trimite datele GPS către noul IoT Hub folosind șirul de conexiune al dispozitivului din pasul anterior.

    > ⚠️ Poți consulta [instrucțiunile pentru conectarea dispozitivului tău la un IoT din proiectul 2, lecția 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) dacă este necesar.

1. Când trimiți datele GPS, fă-o sub formă de JSON în următorul format:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Trimite date GPS la fiecare minut pentru a nu depăși alocarea zilnică de mesaje.

Dacă folosești Wio Terminal, amintește-ți să adaugi toate bibliotecile necesare și să setezi ora folosind un server NTP. Codul tău va trebui, de asemenea, să se asigure că a citit toate datele de pe portul serial înainte de a trimite locația GPS, folosind codul existent din lecția anterioară. Folosește următorul cod pentru a construi documentul JSON:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Dacă folosești un dispozitiv IoT virtual, amintește-ți să instalezi toate bibliotecile necesare folosind un mediu virtual.

Pentru Raspberry Pi și dispozitivul IoT virtual, folosește codul existent din lecția anterioară pentru a obține valorile de latitudine și longitudine, apoi trimite-le în formatul JSON corect cu următorul cod:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Poți găsi acest cod în folderul [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) sau [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Rulează codul dispozitivului tău și asigură-te că mesajele ajung în IoT Hub folosind comanda CLI `az iot hub monitor-events`.

## Căi fierbinți, calde și reci

Datele care curg de la un dispozitiv IoT către cloud nu sunt întotdeauna procesate în timp real. Unele date necesită procesare în timp real, altele pot fi procesate puțin mai târziu, iar altele pot fi procesate mult mai târziu. Fluxul de date către diferite servicii care procesează datele la momente diferite este denumit căi fierbinți, calde și reci.

### Calea fierbinte

Calea fierbinte se referă la datele care trebuie procesate în timp real sau aproape de timp real. Ai folosi datele din calea fierbinte pentru alerte, cum ar fi primirea de notificări că un vehicul se apropie de un depozit sau că temperatura dintr-un camion frigorific este prea mare.

Pentru a utiliza datele din calea fierbinte, codul tău ar răspunde la evenimente imediat ce sunt primite de serviciile tale cloud.

### Calea caldă

Calea caldă se referă la datele care pot fi procesate la scurt timp după ce au fost primite, de exemplu pentru rapoarte sau analize pe termen scurt. Ai folosi datele din calea caldă pentru rapoarte zilnice despre kilometrajul vehiculelor, folosind datele colectate în ziua precedentă.

Datele din calea caldă sunt stocate imediat ce sunt primite de serviciul cloud într-un tip de stocare care poate fi accesat rapid.

### Calea rece

Calea rece se referă la datele istorice, stocând datele pe termen lung pentru a fi procesate ori de câte ori este nevoie. De exemplu, ai putea folosi calea rece pentru a obține rapoarte anuale despre kilometrajul vehiculelor sau pentru a rula analize pe trasee pentru a găsi ruta cea mai optimă pentru reducerea costurilor de combustibil.

Datele din calea rece sunt stocate în depozite de date - baze de date concepute pentru stocarea unor cantități mari de date care nu se vor schimba și pot fi interogate rapid și ușor. De obicei, ai avea un job regulat în aplicația ta cloud care ar rula la un moment regulat în fiecare zi, săptămână sau lună pentru a muta datele din stocarea căii calde în depozitul de date.

✅ Gândește-te la datele pe care le-ai capturat până acum în aceste lecții. Sunt date din calea fierbinte, caldă sau rece?

## Gestionarea evenimentelor GPS folosind cod serverless

Odată ce datele ajung în IoT Hub, poți scrie cod serverless pentru a asculta evenimentele publicate pe endpoint-ul compatibil Event-Hub. Aceasta este calea caldă - aceste date vor fi stocate și utilizate în lecția următoare pentru raportarea traseului.

![Trimiterea telemetriei GPS de la un dispozitiv IoT către IoT Hub, apoi către Azure Functions printr-un trigger Event Hub](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.ro.png)

### Sarcină - gestionează evenimentele GPS folosind cod serverless

1. Creează o aplicație Azure Functions folosind CLI-ul Azure Functions. Folosește runtime-ul Python și creează-o într-un folder numit `gps-trigger`, folosind același nume pentru proiectul aplicației Functions. Asigură-te că creezi un mediu virtual pentru aceasta.
> ⚠️ Poți consulta [instrucțiunile pentru crearea unui proiect Azure Functions din proiectul 2, lecția 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) dacă este necesar.
1. Adaugă un declanșator de eveniment IoT Hub care utilizează punctul final compatibil Event Hub al IoT Hub.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea unui declanșator de eveniment IoT Hub din proiectul 2, lecția 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) dacă este necesar.

1. Setează șirul de conexiune al punctului final compatibil Event Hub în fișierul `local.settings.json` și folosește cheia pentru acea intrare în fișierul `function.json`.

1. Folosește aplicația Azurite ca emulator de stocare locală.

1. Rulează aplicația de funcții pentru a te asigura că primește evenimente de la dispozitivul tău GPS. Asigură-te că dispozitivul IoT este de asemenea activ și trimite date GPS.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Conturi de stocare Azure

![Logo-ul Azure Storage](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.ro.png)

Conturile de stocare Azure reprezintă un serviciu de stocare generală care poate stoca date în diverse moduri. Poți stoca date sub formă de blob-uri, în cozi, în tabele sau ca fișiere, toate în același timp.

### Stocare de tip Blob

Cuvântul *Blob* înseamnă obiecte binare mari, dar a devenit termenul pentru orice date nestructurate. Poți stoca orice date în stocarea de tip blob, de la documente JSON care conțin date IoT, la fișiere de imagini și filme. Stocarea de tip blob are conceptul de *containere*, niște "buckets" denumite în care poți stoca date, similar cu tabelele dintr-o bază de date relațională. Aceste containere pot avea unul sau mai multe foldere pentru a stoca blob-uri, iar fiecare folder poate conține alte foldere, similar cu modul în care fișierele sunt stocate pe hard disk-ul computerului tău.

Vei folosi stocarea de tip blob în această lecție pentru a stoca date IoT.

✅ Fă niște cercetări: Citește despre [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Stocare de tip Tabel

Stocarea de tip tabel îți permite să stochezi date semi-structurate. Stocarea de tip tabel este de fapt o bază de date NoSQL, deci nu necesită un set definit de tabele în prealabil, dar este concepută pentru a stoca date în unul sau mai multe tabele, cu chei unice pentru a defini fiecare rând.

✅ Fă niște cercetări: Citește despre [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Stocare de tip Cozi

Stocarea de tip cozi îți permite să stochezi mesaje de până la 64KB în dimensiune într-o coadă. Poți adăuga mesaje la sfârșitul cozii și să le citești de la început. Cozile stochează mesaje pe termen nelimitat, atâta timp cât există spațiu de stocare, permițând astfel stocarea mesajelor pe termen lung, apoi citirea lor atunci când este necesar. De exemplu, dacă dorești să rulezi o sarcină lunară pentru procesarea datelor GPS, poți adăuga mesaje în coadă în fiecare zi timp de o lună, apoi, la sfârșitul lunii, să procesezi toate mesajele din coadă.

✅ Fă niște cercetări: Citește despre [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Stocare de tip Fișiere

Stocarea de tip fișiere reprezintă stocarea fișierelor în cloud, iar orice aplicații sau dispozitive se pot conecta folosind protocoale standard din industrie. Poți scrie fișiere în stocarea de tip fișiere, apoi să o montezi ca un drive pe PC-ul sau Mac-ul tău.

✅ Fă niște cercetări: Citește despre [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Conectează codul serverless la stocare

Aplicația ta de funcții trebuie acum să se conecteze la stocarea de tip blob pentru a stoca mesajele de la IoT Hub. Există 2 moduri de a face acest lucru:

* În interiorul codului funcției, conectează-te la stocarea de tip blob folosind SDK-ul Python pentru blob-uri și scrie datele ca blob-uri.
* Folosește o legătură de ieșire a funcției pentru a lega valoarea returnată a funcției la stocarea de tip blob și pentru a salva automat blob-ul.

În această lecție, vei folosi SDK-ul Python pentru a vedea cum să interacționezi cu stocarea de tip blob.

![Trimiterea telemetriei GPS de la un dispozitiv IoT la IoT Hub, apoi la Azure Functions printr-un declanșator Event Hub, apoi salvarea acesteia în stocarea de tip blob](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f1.ro.png)

Datele vor fi salvate ca un blob JSON cu următorul format:

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

### Sarcină - conectează codul serverless la stocare

1. Creează un cont de stocare Azure. Denumește-l ceva de genul `gps<numele tău>`.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea unui cont de stocare din proiectul 2, lecția 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) dacă este necesar.

    Dacă ai deja un cont de stocare din proiectul anterior, îl poți reutiliza.

    > 💁 Vei putea folosi același cont de stocare pentru a implementa aplicația Azure Functions mai târziu în această lecție.

1. Rulează următoarea comandă pentru a obține șirul de conexiune pentru contul de stocare:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Înlocuiește `<storage_name>` cu numele contului de stocare pe care l-ai creat în pasul anterior.

1. Adaugă o nouă intrare în fișierul `local.settings.json` pentru șirul de conexiune al contului de stocare, folosind valoarea din pasul anterior. Denumește-o `STORAGE_CONNECTION_STRING`.

1. Adaugă următoarele în fișierul `requirements.txt` pentru a instala pachetele Pip pentru stocarea Azure:

    ```sh
    azure-storage-blob
    ```

    Instalează pachetele din acest fișier în mediul tău virtual.

    > Dacă primești o eroare, atunci actualizează versiunea Pip din mediul tău virtual la cea mai recentă versiune cu următoarea comandă, apoi încearcă din nou:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. În fișierul `__init__.py` pentru `iot-hub-trigger`, adaugă următoarele declarații de import:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Modulul de sistem `json` va fi folosit pentru a citi și scrie JSON, modulul de sistem `os` va fi folosit pentru a citi șirul de conexiune, modulul de sistem `uuid` va fi folosit pentru a genera un ID unic pentru citirea GPS.

    Pachetul `azure.storage.blob` conține SDK-ul Python pentru a lucra cu stocarea de tip blob.

1. Înainte de metoda `main`, adaugă următoarea funcție auxiliară:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    SDK-ul Python pentru blob-uri nu are o metodă auxiliară pentru a crea un container dacă acesta nu există. Acest cod va încărca șirul de conexiune din fișierul `local.settings.json` (sau din Setările Aplicației odată implementat în cloud), apoi va crea o clasă `BlobServiceClient` din aceasta pentru a interacționa cu contul de stocare de tip blob. Apoi, buclează prin toate containerele contului de stocare de tip blob, căutând unul cu numele furnizat - dacă găsește unul, va returna o clasă `ContainerClient` care poate interacționa cu containerul pentru a crea blob-uri. Dacă nu găsește unul, atunci containerul este creat și clientul pentru noul container este returnat.

    Când noul container este creat, se acordă acces public pentru a interoga blob-urile din container. Acest lucru va fi folosit în lecția următoare pentru a vizualiza datele GPS pe o hartă.

1. Spre deosebire de umiditatea solului, cu acest cod dorim să stocăm fiecare eveniment, așa că adaugă următorul cod în interiorul buclei `for event in events:` din funcția `main`, sub declarația `logging`:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Acest cod obține ID-ul dispozitivului din metadatele evenimentului, apoi îl folosește pentru a crea un nume de blob. Blob-urile pot fi stocate în foldere, iar ID-ul dispozitivului va fi folosit pentru numele folderului, astfel încât fiecare dispozitiv să aibă toate evenimentele GPS într-un singur folder. Numele blob-ului este acest folder, urmat de un nume de document, separat prin slash-uri, similar cu căile Linux și macOS (similar și cu Windows, dar Windows folosește backslash-uri). Numele documentului este un ID unic generat folosind modulul Python `uuid`, cu tipul de fișier `json`.

    De exemplu, pentru ID-ul dispozitivului `gps-sensor`, numele blob-ului ar putea fi `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Adaugă următorul cod sub acesta:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Acest cod obține clientul containerului folosind clasa auxiliară `get_or_create_container`, și apoi obține un obiect client blob folosind numele blob-ului. Acești clienți blob pot face referire la blob-uri existente sau, ca în acest caz, la blob-uri noi.

1. Adaugă următorul cod după acesta:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    Acesta construiește corpul blob-ului care va fi scris în stocarea de tip blob. Este un document JSON care conține ID-ul dispozitivului, timpul când telemetria a fost trimisă la IoT Hub și coordonatele GPS din telemetrie.

    > 💁 Este important să folosești timpul de coadă al mesajului în loc de timpul curent pentru a obține timpul când mesajul a fost trimis. Acesta ar putea sta pe hub o perioadă înainte de a fi preluat dacă aplicația Functions nu este activă.

1. Adaugă următorul cod sub acest cod:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Acest cod loghează faptul că un blob urmează să fie scris cu detaliile sale, apoi încarcă corpul blob-ului ca conținut al noului blob.

1. Rulează aplicația Functions. Vei vedea blob-uri fiind scrise pentru toate evenimentele GPS în output:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Asigură-te că nu rulezi monitorul de evenimente IoT Hub în același timp.

> 💁 Poți găsi acest cod în folderul [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Sarcină - verifică blob-urile încărcate

1. Pentru a vizualiza blob-urile create, poți folosi fie [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), un instrument gratuit care îți permite să vizualizezi și să gestionezi conturile de stocare, fie CLI-ul.

    1. Pentru a folosi CLI-ul, mai întâi vei avea nevoie de o cheie de cont. Rulează următoarea comandă pentru a obține această cheie:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Înlocuiește `<storage_name>` cu numele contului de stocare.

        Copiază valoarea `key1`.

    1. Rulează următoarea comandă pentru a lista blob-urile din container:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Înlocuiește `<storage_name>` cu numele contului de stocare și `<key1>` cu valoarea `key1` pe care ai copiat-o în pasul anterior.

        Aceasta va lista toate blob-urile din container:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Descarcă unul dintre blob-uri folosind următoarea comandă:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Înlocuiește `<storage_name>` cu numele contului de stocare și `<key1>` cu valoarea `key1` pe care ai copiat-o în pasul anterior.

        Înlocuiește `<blob_name>` cu numele complet din coloana `Name` a output-ului din pasul anterior, inclusiv numele folderului. Înlocuiește `<file_name>` cu numele unui fișier local pentru a salva blob-ul.

    Odată descărcat, poți deschide fișierul JSON în VS Code și vei vedea blob-ul conținând detaliile locației GPS:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Sarcină - implementează aplicația Functions în cloud

Acum că aplicația ta Functions funcționează, o poți implementa în cloud.

1. Creează o nouă aplicație Azure Functions, folosind contul de stocare pe care l-ai creat mai devreme. Denumește-o ceva de genul `gps-sensor-` și adaugă un identificator unic la final, cum ar fi câteva cuvinte aleatorii sau numele tău.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea unei aplicații Functions din proiectul 2, lecția 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) dacă este necesar.

1. Încarcă valorile `IOT_HUB_CONNECTION_STRING` și `STORAGE_CONNECTION_STRING` în Setările Aplicației.

    > ⚠️ Poți consulta [instrucțiunile pentru încărcarea Setărilor Aplicației din proiectul 2, lecția 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) dacă este necesar.

1. Implementează aplicația Functions locală în cloud.
> ⚠️ Puteți consulta [instrucțiunile pentru a implementa aplicația Functions din proiectul 2, lecția 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) dacă este necesar.
---

## 🚀 Provocare

Datele GPS nu sunt perfect precise, iar locațiile detectate pot fi deplasate cu câțiva metri, dacă nu mai mult, mai ales în tuneluri și zone cu clădiri înalte.

Gândește-te cum ar putea navigația prin satelit să depășească această problemă? Ce date are sistemul tău de navigație prin satelit care i-ar permite să facă predicții mai bune despre locația ta?

## Test de verificare după curs

[Test de verificare după curs](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Recapitulare & Studiu individual

* Citește despre date structurate pe [pagina despre modelul de date de pe Wikipedia](https://wikipedia.org/wiki/Data_model)
* Citește despre date semi-structurate pe [pagina despre date semi-structurate de pe Wikipedia](https://wikipedia.org/wiki/Semi-structured_data)
* Citește despre date nestructurate pe [pagina despre date nestructurate de pe Wikipedia](https://wikipedia.org/wiki/Unstructured_data)
* Află mai multe despre Azure Storage și diferitele tipuri de stocare în [documentația Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Temă

[Investighează legăturile funcțiilor](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.