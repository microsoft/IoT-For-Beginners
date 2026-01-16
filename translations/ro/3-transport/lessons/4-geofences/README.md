<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-28T09:42:58+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "ro"
}
-->
# Geofencing

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.jpg)

> Schiță realizată de [Nitya Narasimhan](https://github.com/nitya). Faceți clic pe imagine pentru o versiune mai mare.

Acest videoclip oferă o prezentare generală a geofencing-ului și a modului de utilizare a acestuia în Azure Maps, subiecte care vor fi abordate în această lecție:

[![Geofencing cu Azure Maps din emisiunea Microsoft Developer IoT](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Faceți clic pe imaginea de mai sus pentru a viziona videoclipul

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Introducere

În ultimele 3 lecții, ați utilizat IoT pentru a localiza camioanele care transportă produsele de la ferma dvs. la un centru de procesare. Ați capturat date GPS, le-ați trimis în cloud pentru stocare și le-ați vizualizat pe o hartă. Următorul pas pentru creșterea eficienței lanțului dvs. de aprovizionare este să primiți o alertă atunci când un camion este pe cale să ajungă la centrul de procesare, astfel încât echipa necesară pentru descărcare să fie pregătită cu stivuitoare și alte echipamente imediat ce vehiculul ajunge. În acest fel, descărcarea se poate face rapid, iar dvs. nu plătiți pentru ca un camion și un șofer să aștepte.

În această lecție veți învăța despre geofencing - regiuni geospațiale definite, cum ar fi o zonă aflată la o distanță de 2 km de un centru de procesare, și cum să testați dacă coordonatele GPS sunt în interiorul sau în afara unei geofence, astfel încât să puteți vedea dacă senzorul GPS a ajuns sau a părăsit o zonă.

În această lecție vom acoperi:

* [Ce sunt geofence-urile](../../../../../3-transport/lessons/4-geofences)
* [Definirea unei geofence](../../../../../3-transport/lessons/4-geofences)
* [Testarea punctelor față de o geofence](../../../../../3-transport/lessons/4-geofences)
* [Utilizarea geofence-urilor din cod serverless](../../../../../3-transport/lessons/4-geofences)

> 🗑 Aceasta este ultima lecție din acest proiect, așa că după ce finalizați lecția și sarcina, nu uitați să curățați serviciile cloud. Veți avea nevoie de servicii pentru a finaliza sarcina, așa că asigurați-vă că o finalizați mai întâi.
>
> Consultați [ghidul pentru curățarea proiectului](../../../clean-up.md) dacă este necesar pentru instrucțiuni despre cum să faceți acest lucru.

## Ce sunt Geofence-urile

O geofence este un perimetru virtual pentru o regiune geografică reală. Geofence-urile pot fi cercuri definite ca un punct și o rază (de exemplu, un cerc cu diametrul de 100m în jurul unei clădiri) sau un poligon care acoperă o zonă, cum ar fi o zonă școlară, limitele unui oraș sau campusul unei universități sau al unui birou.

![Exemple de geofence care arată un geofence circular în jurul magazinului Microsoft și un geofence poligonal în jurul campusului Microsoft West](../../../../../translated_images/ro/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.png)

> 💁 Este posibil să fi folosit deja geofence-uri fără să știți. Dacă ați setat o reamintire folosind aplicația de reamintiri iOS sau Google Keep bazată pe o locație, ați folosit o geofence. Aceste aplicații vor configura o geofence pe baza locației date și vă vor alerta când telefonul dvs. intră în geofence.

Există multe motive pentru care ați dori să știți dacă un vehicul este în interiorul sau în afara unei geofence:

* Pregătirea pentru descărcare - primirea unei notificări că un vehicul a ajuns la fața locului permite echipei să fie pregătită pentru descărcare, reducând timpul de așteptare al vehiculului. Acest lucru poate permite unui șofer să facă mai multe livrări într-o zi cu mai puțin timp de așteptare.
* Conformitate fiscală - unele țări, cum ar fi Noua Zeelandă, percep taxe rutiere pentru vehiculele diesel pe baza greutății vehiculului atunci când circulă doar pe drumuri publice. Utilizarea geofence-urilor vă permite să urmăriți kilometrajul parcurs pe drumurile publice, spre deosebire de drumurile private de pe site-uri precum fermele sau zonele de exploatare forestieră.
* Monitorizarea furtului - dacă un vehicul ar trebui să rămână doar într-o anumită zonă, cum ar fi pe o fermă, și părăsește geofence-ul, este posibil să fi fost furat.
* Conformitate cu locația - unele părți ale unui șantier, ferme sau fabrici pot fi interzise anumitor vehicule, cum ar fi păstrarea vehiculelor care transportă îngrășăminte artificiale și pesticide departe de câmpurile care cultivă produse organice. Dacă o geofence este încălcată, atunci vehiculul este în afara conformității și șoferul poate fi notificat.

✅ Puteți gândi alte utilizări pentru geofence-uri?

Azure Maps, serviciul pe care l-ați utilizat în lecția anterioară pentru a vizualiza datele GPS, vă permite să definiți geofence-uri, apoi să testați dacă un punct este în interiorul sau în afara geofence-ului.

## Definirea unei geofence

Geofence-urile sunt definite folosind GeoJSON, la fel ca punctele care au fost adăugate pe hartă în lecția anterioară. În acest caz, în loc să fie o `FeatureCollection` de valori `Point`, este o `FeatureCollection` care conține un `Polygon`.

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

Fiecare punct de pe poligon este definit ca o pereche longitudine, latitudine într-un array, iar aceste puncte sunt într-un array care este setat ca `coordinates`. Într-un `Point` din lecția anterioară, `coordinates` era un array care conținea 2 valori, latitudine și longitudine, pentru un `Polygon` este un array de array-uri care conțin 2 valori, longitudine, latitudine.

> 💁 Rețineți, GeoJSON folosește `longitudine, latitudine` pentru puncte, nu `latitudine, longitudine`

Array-ul de coordonate ale poligonului are întotdeauna cu 1 intrare mai mult decât numărul de puncte de pe poligon, ultima intrare fiind aceeași cu prima, închizând poligonul. De exemplu, pentru un dreptunghi ar exista 5 puncte.

![Un dreptunghi cu coordonate](../../../../../translated_images/ro/polygon-points.302193da381cb415.webp)

În imaginea de mai sus, există un dreptunghi. Coordonatele poligonului încep din colțul stânga-sus la 47,-122, apoi se deplasează spre dreapta la 47,-121, apoi în jos la 46,-121, apoi spre stânga la 46, -122, apoi înapoi la punctul de pornire la 47, -122. Acest lucru oferă poligonului 5 puncte - stânga-sus, dreapta-sus, dreapta-jos, stânga-jos, apoi stânga-sus pentru a-l închide.

✅ Încercați să creați un poligon GeoJSON în jurul casei sau școlii dvs. Utilizați un instrument precum [GeoJSON.io](https://geojson.io/).

### Sarcină - definirea unei geofence

Pentru a utiliza o geofence în Azure Maps, mai întâi trebuie să fie încărcată în contul dvs. Azure Maps. Odată încărcată, veți primi un ID unic pe care îl puteți utiliza pentru a testa un punct față de geofence. Pentru a încărca geofence-uri în Azure Maps, trebuie să utilizați API-ul web al hărților. Puteți apela API-ul web Azure Maps folosind un instrument numit [curl](https://curl.se).

> 🎓 Curl este un instrument de linie de comandă pentru a face cereri către endpoint-uri web

1. Dacă utilizați Linux, macOS sau o versiune recentă de Windows 10, probabil aveți curl deja instalat. Rulați următoarea comandă din terminal sau linia de comandă pentru a verifica:

    ```sh
    curl --version
    ```

    Dacă nu vedeți informații despre versiunea curl, va trebui să îl instalați de pe [pagina de descărcare curl](https://curl.se/download.html).

    > 💁 Dacă aveți experiență cu Postman, puteți utiliza acest instrument în loc, dacă preferați.

1. Creați un fișier GeoJSON care conține un poligon. Veți testa acest lucru folosind senzorul dvs. GPS, așa că creați un poligon în jurul locației dvs. curente. Puteți fie să creați unul manual editând exemplul GeoJSON dat mai sus, fie să utilizați un instrument precum [GeoJSON.io](https://geojson.io/).

    GeoJSON-ul trebuie să conțină o `FeatureCollection`, care conține o `Feature` cu o `geometry` de tip `Polygon`.

    Trebuie să adăugați și un element `properties` la același nivel cu elementul `geometry`, iar acesta trebuie să conțină un `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Dacă utilizați [GeoJSON.io](https://geojson.io/), va trebui să adăugați manual acest element în `properties`, fie după descărcarea fișierului JSON, fie în editorul JSON din aplicație.

    Acest `geometryId` trebuie să fie unic în acest fișier. Puteți încărca mai multe geofence-uri ca multiple `Features` în `FeatureCollection` în același fișier GeoJSON, atâta timp cât fiecare are un `geometryId` diferit. Poligoanele pot avea același `geometryId` dacă sunt încărcate dintr-un fișier diferit la un moment diferit.

1. Salvați acest fișier ca `geofence.json` și navigați la locația unde este salvat în terminal sau consolă.

1. Rulați următoarea comandă curl pentru a crea GeoFence-ul:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Înlocuiți `<subscription_key>` din URL cu cheia API pentru contul dvs. Azure Maps.

    URL-ul este utilizat pentru a încărca datele hărții prin API-ul `https://atlas.microsoft.com/mapData/upload`. Apelul include un parametru `api-version` pentru a specifica ce API Azure Maps să utilizeze, acest lucru fiind pentru a permite API-ului să se schimbe în timp, dar să mențină compatibilitatea inversă. Formatul datelor încărcate este setat la `geojson`.

    Aceasta va rula cererea POST către API-ul de încărcare și va returna o listă de anteturi de răspuns care include un antet numit `location`.

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

    > 🎓 Când apelați un endpoint web, puteți transmite parametri apelului adăugând un `?` urmat de perechi cheie-valoare ca `cheie=valoare`, separând perechile cheie-valoare printr-un `&`.

1. Azure Maps nu procesează acest lucru imediat, așa că va trebui să verificați dacă cererea de încărcare a fost finalizată utilizând URL-ul dat în antetul `location`. Faceți o cerere GET la această locație pentru a vedea starea. Va trebui să adăugați cheia de abonament la sfârșitul URL-ului `location` adăugând `&subscription-key=<subscription_key>` la sfârșit, înlocuind `<subscription_key>` cu cheia API pentru contul dvs. Azure Maps. Rulați următoarea comandă:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Înlocuiți `<location>` cu valoarea antetului `location` și `<subscription_key>` cu cheia API pentru contul dvs. Azure Maps.

1. Verificați valoarea `status` din răspuns. Dacă nu este `Succeeded`, așteptați un minut și încercați din nou.

1. Odată ce starea revine ca `Succeeded`, uitați-vă la `resourceLocation` din răspuns. Acesta conține detalii despre ID-ul unic (cunoscut ca UDID) pentru obiectul GeoJSON. UDID-ul este valoarea după `metadata/`, fără a include `api-version`. De exemplu, dacă `resourceLocation` era:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Atunci UDID-ul ar fi `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Păstrați o copie a acestui UDID, deoarece veți avea nevoie de el pentru a testa geofence-ul.

## Testarea punctelor față de o geofence

Odată ce poligonul a fost încărcat în Azure Maps, puteți testa un punct pentru a vedea dacă este în interiorul sau în afara geofence-ului. Faceți acest lucru printr-o cerere API web, transmițând UDID-ul geofence-ului și latitudinea și longitudinea punctului de testat.

Când faceți această cerere, puteți transmite și o valoare numită `searchBuffer`. Aceasta indică API-ului Maps cât de precis să fie atunci când returnează rezultatele. Motivul pentru aceasta este că GPS-ul nu este perfect precis, iar uneori locațiile pot fi greșite cu câțiva metri sau mai mult. Valoarea implicită pentru bufferul de căutare este de 50m, dar puteți seta valori între 0m și 500m.

Când rezultatele sunt returnate din apelul API, una dintre părțile rezultatului este o `distance` măsurată până la cel mai apropiat punct de pe marginea geofence-ului, cu o valoare pozitivă dacă punctul este în afara geofence-ului, negativă dacă este în interiorul geofence-ului. Dacă această distanță este mai mică decât bufferul de căutare, distanța reală este returnată în metri, altfel valoarea este 999 sau -999. 999 înseamnă că punctul este în afara geofence-ului cu mai mult decât bufferul de căutare, -999 înseamnă că este în interiorul geofence-ului cu mai mult decât bufferul de căutare.

![O geofence cu un buffer de căutare de 50m în jurul său](../../../../../translated_images/ro/search-buffer-and-distance.e6a79af3898183c7.webp)

În imaginea de mai sus, geofence-ul are un buffer de căutare de 50m.

* Un punct în centrul geofence-ului, bine în interiorul bufferului de căutare, are o distanță de **-999**
* Un punct bine în afara bufferului de căutare are o distanță de **999**
* Un punct în interiorul geofence-ului și în interiorul bufferului de căutare, la 6m de geofence, are o distanță de **6m**
* Un punct în afara geofence-ului și în interiorul bufferului de căutare, la 39m de geofence, are o distanță de **39m**

Este important să cunoașteți distanța până la marginea geofence-ului și să combinați aceasta cu alte informații, cum ar fi alte citiri GPS, viteza și datele despre drumuri, atunci când luați decizii bazate pe locația unui vehicul.

De exemplu, imaginați-vă citiri GPS care arată că un vehicul circula pe un drum care ajunge să treacă pe lângă o geofence. Dacă o singură valoare GPS este inexactă și plasează vehiculul în interiorul geofence-ului, în ciuda faptului că nu există acces rutier, aceasta poate fi ignorată.

![O urmă GPS care arată un vehicul trecând pe lângă campusul Microsoft pe 520, cu citiri GPS de-a lungul drumului, cu excepția uneia pe campus, în interiorul unei geofence](../../../../../translated_images/ro/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.png)
În imaginea de mai sus, există o geofence peste o parte a campusului Microsoft. Linia roșie arată un camion care circulă de-a lungul autostrăzii 520, cu cercuri care indică citirile GPS. Majoritatea acestor citiri sunt corecte și se află de-a lungul autostrăzii 520, cu o citire inexactă în interiorul geofence-ului. Nu există nicio posibilitate ca acea citire să fie corectă - nu există drumuri care să permită camionului să se abată brusc de pe autostrada 520 către campus și apoi să revină pe autostrada 520. Codul care verifică acest geofence va trebui să ia în considerare citirile anterioare înainte de a acționa pe baza rezultatelor testului geofence.

✅ Ce date suplimentare ar fi necesare pentru a verifica dacă o citire GPS poate fi considerată corectă?

### Sarcină - testează punctele față de un geofence

1. Începe prin construirea URL-ului pentru interogarea API-ului web. Formatul este:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Înlocuiește `<subscription_key>` cu cheia API pentru contul tău Azure Maps.

    Înlocuiește `<UDID>` cu UDID-ul geofence-ului din sarcina anterioară.

    Înlocuiește `<lat>` și `<lon>` cu latitudinea și longitudinea pe care vrei să le testezi.

    Acest URL folosește API-ul `https://atlas.microsoft.com/spatial/geofence/json` pentru a interoga un geofence definit folosind GeoJSON. Se adresează versiunii API `1.0`. Parametrul `deviceId` este obligatoriu și ar trebui să fie numele dispozitivului de la care provin latitudinea și longitudinea.

    Buffer-ul de căutare implicit este de 50m, și poți modifica acest lucru adăugând un parametru suplimentar `searchBuffer=<distance>`, setând `<distance>` la distanța buffer-ului de căutare în metri, între 0 și 500.

1. Folosește curl pentru a face o cerere GET la acest URL:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Dacă primești un cod de răspuns `BadRequest`, cu o eroare de:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > atunci GeoJSON-ul tău lipsește secțiunea `properties` cu `geometryId`. Va trebui să corectezi GeoJSON-ul, apoi să repeți pașii de mai sus pentru a-l reîncărca și a obține un nou UDID.

1. Răspunsul va conține o listă de `geometries`, câte unul pentru fiecare poligon definit în GeoJSON-ul folosit pentru a crea geofence-ul. Fiecare geometrie are 3 câmpuri de interes: `distance`, `nearestLat` și `nearestLon`.

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

    * `nearestLat` și `nearestLon` sunt latitudinea și longitudinea unui punct de pe marginea geofence-ului care este cel mai apropiat de locația testată.

    * `distance` este distanța de la locația testată până la cel mai apropiat punct de pe marginea geofence-ului. Numerele negative înseamnă că locația este în interiorul geofence-ului, cele pozitive în afara acestuia. Această valoare va fi mai mică de 50 (buffer-ul de căutare implicit) sau 999.

1. Repetă acest lucru de mai multe ori cu locații din interiorul și exteriorul geofence-ului.

## Folosește geofence-uri din cod serverless

Acum poți adăuga un nou trigger în aplicația ta Functions pentru a testa datele GPS ale evenimentelor IoT Hub față de geofence.

### Grupuri de consumatori

După cum îți amintești din lecțiile anterioare, IoT Hub îți permite să redai evenimentele care au fost primite de hub, dar nu procesate. Dar ce se întâmplă dacă se conectează mai multe trigger-uri? Cum va ști care dintre ele a procesat ce evenimente?

Răspunsul este că nu poate! În schimb, poți defini mai multe conexiuni separate pentru a citi evenimentele, iar fiecare dintre ele poate gestiona redarea mesajelor necitite. Acestea se numesc *grupuri de consumatori*. Când te conectezi la endpoint, poți specifica grupul de consumatori la care vrei să te conectezi. Fiecare componentă a aplicației tale se va conecta la un grup de consumatori diferit.

![Un IoT Hub cu 3 grupuri de consumatori distribuind aceleași mesaje către 3 aplicații Functions diferite](../../../../../translated_images/ro/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.png)

În teorie, până la 5 aplicații pot să se conecteze la fiecare grup de consumatori, și toate vor primi mesaje când acestea sosesc. Este o practică recomandată să ai doar o aplicație care accesează fiecare grup de consumatori pentru a evita procesarea duplicată a mesajelor și pentru a te asigura că, la repornire, toate mesajele în coadă sunt procesate corect. De exemplu, dacă lansezi aplicația Functions local, precum și o rulezi în cloud, ambele vor procesa mesaje, ceea ce va duce la stocarea duplicată a bloburilor în contul de stocare.

Dacă revizuiești fișierul `function.json` pentru trigger-ul IoT Hub pe care l-ai creat într-o lecție anterioară, vei vedea grupul de consumatori în secțiunea de legare a trigger-ului event hub:

```json
"consumerGroup": "$Default"
```

Când creezi un IoT Hub, primești grupul de consumatori `$Default` creat implicit. Dacă vrei să adaugi un trigger suplimentar, poți face acest lucru folosind un nou grup de consumatori.

> 💁 În această lecție, vei folosi o funcție diferită pentru a testa geofence-ul față de cea folosită pentru a stoca datele GPS. Acest lucru este pentru a arăta cum să folosești grupuri de consumatori și să separi codul pentru a-l face mai ușor de citit și înțeles. Într-o aplicație de producție, există multe moduri în care ai putea arhitecta acest lucru - punând ambele într-o singură funcție, folosind un trigger pe contul de stocare pentru a rula o funcție care verifică geofence-ul sau folosind funcții multiple. Nu există un "mod corect", depinde de restul aplicației tale și de nevoile tale.

### Sarcină - creează un nou grup de consumatori

1. Rulează următoarea comandă pentru a crea un nou grup de consumatori numit `geofence` pentru IoT Hub-ul tău:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Înlocuiește `<hub_name>` cu numele pe care l-ai folosit pentru IoT Hub-ul tău.

1. Dacă vrei să vezi toate grupurile de consumatori pentru un IoT Hub, rulează următoarea comandă:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Înlocuiește `<hub_name>` cu numele pe care l-ai folosit pentru IoT Hub-ul tău. Aceasta va lista toate grupurile de consumatori.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Când ai rulat monitorul de evenimente IoT Hub într-o lecție anterioară, acesta s-a conectat la grupul de consumatori `$Default`. Acesta a fost motivul pentru care nu poți rula monitorul de evenimente și un trigger de evenimente. Dacă vrei să rulezi ambele, atunci poți folosi alte grupuri de consumatori pentru toate aplicațiile tale Functions și să păstrezi `$Default` pentru monitorul de evenimente.

### Sarcină - creează un nou trigger IoT Hub

1. Adaugă un nou trigger de evenimente IoT Hub în aplicația ta `gps-trigger` pe care ai creat-o într-o lecție anterioară. Denumește această funcție `geofence-trigger`.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea unui trigger de evenimente IoT Hub din proiectul 2, lecția 5 dacă este necesar](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Configurează șirul de conexiune IoT Hub în fișierul `function.json`. Fișierul `local.settings.json` este partajat între toate trigger-urile din aplicația Functions.

1. Actualizează valoarea `consumerGroup` din fișierul `function.json` pentru a face referire la noul grup de consumatori `geofence`:

    ```json
    "consumerGroup": "geofence"
    ```

1. Va trebui să folosești cheia de abonament pentru contul tău Azure Maps în acest trigger, așa că adaugă o nouă intrare în fișierul `local.settings.json` numită `MAPS_KEY`.

1. Rulează aplicația Functions pentru a te asigura că se conectează și procesează mesaje. Trigger-ul `iot-hub-trigger` din lecția anterioară va rula și va încărca bloburi în stocare.

    > Pentru a evita citirile GPS duplicate în stocarea bloburilor, poți opri aplicația Functions pe care o ai rulând în cloud. Pentru a face acest lucru, folosește următoarea comandă:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Înlocuiește `<functions_app_name>` cu numele pe care l-ai folosit pentru aplicația ta Functions.
    >
    > O poți reporni mai târziu cu următoarea comandă:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Înlocuiește `<functions_app_name>` cu numele pe care l-ai folosit pentru aplicația ta Functions.

### Sarcină - testează geofence-ul din trigger

Mai devreme în această lecție ai folosit curl pentru a interoga un geofence pentru a vedea dacă un punct se află în interior sau în exterior. Poți face o cerere web similară din interiorul trigger-ului tău.

1. Pentru a interoga geofence-ul, ai nevoie de UDID-ul său. Adaugă o nouă intrare în fișierul `local.settings.json` numită `GEOFENCE_UDID` cu această valoare.

1. Deschide fișierul `__init__.py` din noul trigger `geofence-trigger`.

1. Adaugă următoarea importare în partea de sus a fișierului:

    ```python
    import json
    import os
    import requests
    ```

    Pachetul `requests` îți permite să faci apeluri API web. Azure Maps nu are un SDK pentru Python, trebuie să faci apeluri API web pentru a-l folosi din codul Python.

1. Adaugă următoarele 2 linii la începutul metodei `main` pentru a obține cheia de abonament Maps:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. În interiorul buclei `for event in events`, adaugă următoarele pentru a obține latitudinea și longitudinea din fiecare eveniment:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Acest cod convertește JSON-ul din corpul evenimentului într-un dicționar, apoi extrage `lat` și `lon` din câmpul `gps`.

1. Când folosești `requests`, în loc să construiești un URL lung așa cum ai făcut cu curl, poți folosi doar partea URL și să transmiți parametrii ca dicționar. Adaugă următorul cod pentru a defini URL-ul de apelat și pentru a configura parametrii:

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

    Elementele din dicționarul `params` vor corespunde perechilor cheie-valoare pe care le-ai folosit când ai apelat API-ul web prin curl.

1. Adaugă următoarele linii de cod pentru a apela API-ul web:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Acest cod apelează URL-ul cu parametrii și primește un obiect de răspuns.

1. Adaugă următorul cod sub acesta:

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

    Acest cod presupune o singură geometrie și extrage distanța din acea geometrie unică. Apoi înregistrează mesaje diferite în funcție de distanță.

1. Rulează acest cod. Vei vedea în jurnalul de ieșire dacă coordonatele GPS sunt în interiorul sau în exteriorul geofence-ului, cu o distanță dacă punctul se află în raza de 50m. Încearcă acest cod cu diferite geofence-uri bazate pe locația senzorului tău GPS, încearcă să muți senzorul (de exemplu, conectat la WiFi de pe un telefon mobil sau cu coordonate diferite pe dispozitivul IoT virtual) pentru a vedea această schimbare.

1. Când ești gata, distribuie acest cod în aplicația ta Functions din cloud. Nu uita să distribui noile Setări ale Aplicației.

    > ⚠️ Poți consulta [instrucțiunile pentru încărcarea Setărilor Aplicației din proiectul 2, lecția 5 dacă este necesar](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Poți consulta [instrucțiunile pentru distribuirea aplicației tale Functions din proiectul 2, lecția 5 dacă este necesar](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Poți găsi acest cod în folderul [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Provocare

În această lecție ai adăugat un geofence folosind un fișier GeoJSON cu un singur poligon. Poți încărca mai multe poligoane în același timp, atâta timp cât au valori diferite pentru `geometryId` în secțiunea `properties`.

Încearcă să încarci un fișier GeoJSON cu mai multe poligoane și ajustează codul pentru a găsi care poligon este cel mai apropiat sau în care se află coordonatele GPS.

## Quiz post-lectură

[Quiz post-lectură](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Recapitulare și Studiu Individual

* Citește mai multe despre geofence-uri și unele dintre utilizările lor pe [pagina Geofencing de pe Wikipedia](https://en.wikipedia.org/wiki/Geo-fence).
* Citește mai multe despre API-ul de geofencing Azure Maps în [documentația Microsoft Azure Maps Spatial - Get Geofence](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Citește mai multe despre grupurile de consumatori în [documentația Microsoft despre caracteristicile și terminologia Event Hubs - Event consumers](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Temă

[Trimite notificări folosind Twilio](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.