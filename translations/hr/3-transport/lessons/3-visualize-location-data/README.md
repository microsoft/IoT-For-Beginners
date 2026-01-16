<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-28T13:27:39+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "hr"
}
-->
# Vizualizacija podataka o lokaciji

![Sketchnote pregled ove lekcije](../../../../../translated_images/hr/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ovaj video pruža pregled Azure Maps s IoT-om, usluge koja će biti obrađena u ovoj lekciji.

[![Azure Maps - Microsoft Azure Enterprise Location Platform](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Kliknite na sliku iznad za gledanje videa

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Uvod

U prethodnoj lekciji naučili ste kako dobiti GPS podatke sa svojih senzora i spremiti ih u oblak u spremnik za pohranu koristeći serverless kod. Sada ćete otkriti kako vizualizirati te točke na Azure karti. Naučit ćete kako stvoriti kartu na web stranici, upoznati se s GeoJSON formatom podataka i kako ga koristiti za iscrtavanje svih prikupljenih GPS točaka na vašoj karti.

U ovoj lekciji obradit ćemo:

* [Što je vizualizacija podataka](../../../../../3-transport/lessons/3-visualize-location-data)
* [Usluge karata](../../../../../3-transport/lessons/3-visualize-location-data)
* [Kreiranje Azure Maps resursa](../../../../../3-transport/lessons/3-visualize-location-data)
* [Prikaz karte na web stranici](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON format](../../../../../3-transport/lessons/3-visualize-location-data)
* [Iscrtavanje GPS podataka na karti koristeći GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Ova lekcija uključuje malu količinu HTML-a i JavaScripta. Ako želite naučiti više o web razvoju koristeći HTML i JavaScript, pogledajte [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners).

## Što je vizualizacija podataka

Vizualizacija podataka, kako i samo ime sugerira, odnosi se na prikazivanje podataka na način koji ljudima olakšava razumijevanje. Obično se povezuje s grafikonima i dijagramima, ali zapravo uključuje bilo koji način slikovitog prikazivanja podataka kako bi se ljudima omogućilo bolje razumijevanje i donošenje odluka.

Uzmimo jednostavan primjer - u projektu farme prikupljali ste podatke o vlažnosti tla. Tablica podataka o vlažnosti tla prikupljenih svakog sata za 1. lipnja 2021. mogla bi izgledati ovako:

| Datum            | Očitavanje |
| ---------------- | ---------: |
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

Kao ljudima, razumijevanje ovih podataka može biti teško. To je zid brojeva bez ikakvog značenja. Kao prvi korak u vizualizaciji ovih podataka, mogu se iscrtati na linijskom grafikonu:

![Linijski grafikon gore navedenih podataka](../../../../../translated_images/hr/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Ovo se može dodatno poboljšati dodavanjem linije koja označava kada je automatski sustav za zalijevanje uključen pri očitanju vlažnosti tla od 450:

![Linijski grafikon vlažnosti tla s linijom na 450](../../../../../translated_images/hr/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Ovaj grafikon vrlo brzo pokazuje ne samo razine vlažnosti tla, već i točke kada je sustav za zalijevanje uključen.

Grafikoni nisu jedini alat za vizualizaciju podataka. IoT uređaji koji prate vremenske uvjete mogu imati web ili mobilne aplikacije koje vizualiziraju vremenske uvjete koristeći simbole, poput simbola oblaka za oblačne dane, simbola kišnog oblaka za kišne dane i slično. Postoji ogroman broj načina za vizualizaciju podataka, neki ozbiljni, neki zabavni.

✅ Razmislite o načinima na koje ste vidjeli vizualizirane podatke. Koje su metode bile najjasnije i omogućile vam najbrže donošenje odluka?

Najbolje vizualizacije omogućuju ljudima brzo donošenje odluka. Na primjer, zid s mnoštvom mjerača koji prikazuju razne očitanja industrijskih strojeva teško je obraditi, ali trepćuće crveno svjetlo kada nešto pođe po zlu omogućuje čovjeku donošenje odluke. Ponekad je najbolja vizualizacija trepćuće svjetlo!

Kada radite s GPS podacima, najjasnija vizualizacija može biti iscrtavanje podataka na karti. Karta koja prikazuje dostavna vozila, na primjer, može pomoći radnicima u pogonu da vide kada će vozila stići. Ako ta karta prikazuje više od samih slika vozila na njihovim trenutnim lokacijama, već daje i informacije o sadržaju vozila, tada radnici u pogonu mogu planirati u skladu s tim - ako vide rashladno vozilo u blizini, znaju da trebaju pripremiti prostor u hladnjaku.

## Usluge karata

Rad s kartama je zanimljiv zadatak, a postoji mnogo opcija poput Bing Maps, Leaflet, Open Street Maps i Google Maps. U ovoj lekciji naučit ćete o [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) i kako oni mogu prikazati vaše GPS podatke.

![Azure Maps logo](../../../../../translated_images/hr/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps je "zbirka geoprostornih usluga i SDK-ova koji koriste svježe podatke o kartama kako bi pružili geografski kontekst za web i mobilne aplikacije." Programerima su dostupni alati za stvaranje lijepih, interaktivnih karata koje mogu, primjerice, pružiti preporučene prometne rute, informacije o prometnim incidentima, unutarnju navigaciju, mogućnosti pretraživanja, informacije o nadmorskoj visini, vremenske usluge i još mnogo toga.

✅ Eksperimentirajte s nekim [primjerima koda za karte](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Možete prikazati karte kao prazno platno, pločice, satelitske slike, satelitske slike s ucrtanim cestama, razne vrste sivih karata, karte s osjenčanim reljefom za prikaz nadmorske visine, karte noćnog prikaza i karte visokog kontrasta. Možete dobiti ažuriranja u stvarnom vremenu na svojim kartama integrirajući ih s [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Možete kontrolirati ponašanje i izgled svojih karata omogućavanjem raznih kontrola koje omogućuju karti da reagira na događaje poput štipanja, povlačenja i klikanja. Kako biste kontrolirali izgled svoje karte, možete dodati slojeve koji uključuju mjehuriće, linije, poligone, toplinske karte i još mnogo toga. Koji stil karte implementirati ovisi o vašem izboru SDK-a.

Azure Maps API-je možete koristiti putem [REST API-ja](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), [Web SDK-a](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn) ili, ako gradite mobilnu aplikaciju, [Android SDK-a](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

U ovoj lekciji koristit ćete web SDK za crtanje karte i prikazivanje puta GPS lokacija vašeg senzora.

## Kreiranje Azure Maps resursa

Prvi korak je kreiranje Azure Maps računa.

### Zadatak - kreiranje Azure Maps resursa

1. Pokrenite sljedeću naredbu iz svog Terminala ili Command Prompt-a kako biste kreirali Azure Maps resurs u svojoj `gps-sensor` grupi resursa:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Ovo će kreirati Azure Maps resurs nazvan `gps-sensor`. Korišteni sloj je `S1`, koji je plaćeni sloj koji uključuje niz značajki, ali s velikodušnim brojem besplatnih poziva.

    > 💁 Za pregled troškova korištenja Azure Maps, pogledajte [stranicu s cijenama Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Trebat će vam API ključ za resurs karata. Koristite sljedeću naredbu za dobivanje ovog ključa:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Zabilježite vrijednost `PrimaryKey`.

## Prikaz karte na web stranici

Sada možete prijeći na sljedeći korak, a to je prikazivanje karte na web stranici. Koristit ćemo samo jednu `html` datoteku za vašu malu web aplikaciju; imajte na umu da će u produkcijskom ili timskom okruženju vaša web aplikacija vjerojatno imati više dijelova!

### Zadatak - prikaz karte na web stranici

1. Kreirajte datoteku pod nazivom `index.html` u nekoj mapi na svom lokalnom računalu. Dodajte HTML oznake za prikaz karte:

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

    Karta će se učitati u `myMap` `div`. Nekoliko stilova omogućuje joj da zauzme širinu i visinu stranice.

    > 🎓 `div` je dio web stranice koji se može imenovati i stilizirati.

1. Ispod otvarajuće `<head>` oznake, dodajte vanjski stilopis za kontrolu prikaza karte i vanjsku skriptu iz Web SDK-a za upravljanje njenim ponašanjem:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Ovaj stilopis sadrži postavke za izgled karte, a datoteka sa skriptom sadrži kod za učitavanje karte. Dodavanje ovog koda slično je uključivanju C++ zaglavnih datoteka ili uvozu Python modula.

1. Ispod te skripte, dodajte blok skripte za pokretanje karte.

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

    Zamijenite `<subscription_key>` s API ključem za vaš Azure Maps račun.

    Ako otvorite svoju `index.html` stranicu u web pregledniku, trebali biste vidjeti kartu učitanu i fokusiranu na područje Seattlea.

    ![Karta koja prikazuje Seattle, grad u saveznoj državi Washington, SAD](../../../../../translated_images/hr/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Eksperimentirajte s parametrima za zumiranje i centriranje kako biste promijenili prikaz karte. Možete dodati različite koordinate koje odgovaraju širini i dužini vaših podataka kako biste ponovno centrirali kartu.

> 💁 Bolji način za rad s web aplikacijama lokalno je instalacija [http-server](https://www.npmjs.com/package/http-server). Trebat će vam [node.js](https://nodejs.org/) i [npm](https://www.npmjs.com/) instalirani prije korištenja ovog alata. Nakon što su ti alati instalirani, možete navigirati do lokacije svoje `index.html` datoteke i upisati `http-server`. Web aplikacija će se otvoriti na lokalnom web poslužitelju [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## GeoJSON format

Sada kada imate svoju web aplikaciju s prikazanom kartom, trebate izvući GPS podatke iz svog spremnika za pohranu i prikazati ih u sloju markera na vrhu karte. Prije nego što to učinimo, pogledajmo [GeoJSON](https://wikipedia.org/wiki/GeoJSON) format koji zahtijeva Azure Maps.

[GeoJSON](https://geojson.org/) je otvoreni standard JSON specifikacije s posebnim formatiranjem dizajniranim za rukovanje geografskim podacima. Možete ga proučiti testiranjem uzoraka podataka koristeći [geojson.io](https://geojson.io), koji je također koristan alat za otklanjanje pogrešaka u GeoJSON datotekama.

Uzorak GeoJSON podataka izgleda ovako:

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

Posebno je zanimljiv način na koji su podaci ugniježđeni kao `Feature` unutar `FeatureCollection`. Unutar tog objekta nalazi se `geometry` s `coordinates` koji označavaju geografsku dužinu i širinu.

✅ Kada gradite svoj GeoJSON, obratite pažnju na redoslijed `latitude` i `longitude` u objektu, inače se vaše točke neće pojaviti na pravom mjestu! GeoJSON očekuje podatke u redoslijedu `lon,lat` za točke, a ne `lat,lon`.

`Geometry` može imati različite tipove, poput jedne točke ili poligona. U ovom primjeru, to je točka s dvije specificirane koordinate, geografskom dužinom i širinom.
✅ Azure Maps podržava standardni GeoJSON uz neke [napredne značajke](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), uključujući mogućnost crtanja krugova i drugih geometrijskih oblika.

## Prikaz GPS podataka na karti koristeći GeoJSON

Sada ste spremni koristiti podatke iz pohrane koju ste izgradili u prethodnoj lekciji. Podsjetimo, podaci su pohranjeni kao niz datoteka u blob pohrani, pa ćete morati dohvatiti te datoteke i obraditi ih kako bi Azure Maps mogao koristiti te podatke.

### Zadatak - konfiguriranje pohrane za pristup s web stranice

Ako pokušate pristupiti svojoj pohrani kako biste dohvatili podatke, mogli biste se iznenaditi kada vidite pogreške u konzoli vašeg preglednika. To je zato što trebate postaviti dozvole za [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) na ovoj pohrani kako biste omogućili vanjskim web aplikacijama da čitaju njezine podatke.

> 🎓 CORS označava "Cross-Origin Resource Sharing" i obično ga je potrebno eksplicitno postaviti u Azureu iz sigurnosnih razloga. Sprječava neželjene stranice da pristupe vašim podacima.

1. Pokrenite sljedeću naredbu kako biste omogućili CORS:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Zamijenite `<storage_name>` nazivom vašeg računa za pohranu. Zamijenite `<key1>` ključem računa za vašu pohranu.

    Ova naredba omogućuje bilo kojoj web stranici (zvjezdica `*` označava bilo koju) da napravi *GET* zahtjev, odnosno da dobije podatke iz vašeg računa za pohranu. `--services b` znači da se ovo postavljanje primjenjuje samo na blobove.

### Zadatak - učitavanje GPS podataka iz pohrane

1. Zamijenite cijeli sadržaj funkcije `init` sljedećim kodom:

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

    Zamijenite `<storage_name>` nazivom vašeg računa za pohranu. Zamijenite `<subscription_key>` API ključem za vaš Azure Maps račun.

    Ovdje se događa nekoliko stvari. Prvo, kod dohvaća vaše GPS podatke iz vašeg blob spremnika koristeći URL endpoint koji se gradi pomoću naziva vašeg računa za pohranu. Ovaj URL dohvaća podatke iz `gps-data`, što označava da je vrsta resursa spremnik (`restype=container`), i navodi informacije o svim blobovima. Ovaj popis neće vratiti same blobove, već će vratiti URL za svaki blob koji se može koristiti za učitavanje podataka iz bloba.

    > 💁 Ovaj URL možete staviti u svoj preglednik kako biste vidjeli detalje o svim blobovima u vašem spremniku. Svaka stavka imat će svojstvo `Url` koje također možete učitati u pregledniku kako biste vidjeli sadržaj bloba.

    Kod zatim učitava svaki blob, pozivajući funkciju `loadJSON`, koju ćete kreirati u sljedećem koraku. Zatim kreira kontrolu karte i dodaje kod u događaj `ready`. Ovaj događaj se poziva kada se karta prikaže na web stranici.

    Događaj `ready` kreira izvor podataka za Azure Maps - spremnik koji sadrži GeoJSON podatke koji će kasnije biti popunjeni. Ovaj izvor podataka se zatim koristi za kreiranje sloja mjehurića - to jest skupa krugova na karti centriranih oko svake točke u GeoJSON-u.

1. Dodajte funkciju `loadJSON` u svoj blok skripte, ispod funkcije `init`:

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

    Ova funkcija se poziva od strane rutine za dohvaćanje kako bi obradila JSON podatke i pretvorila ih u format koji se čita kao geografske koordinate (dužina i širina) u GeoJSON-u. 
    Nakon obrade, podaci se postavljaju kao dio GeoJSON `Feature`. Karta će se inicijalizirati i mali mjehurići će se pojaviti duž puta koji vaši podaci prikazuju:

1. Učitajte HTML stranicu u svoj preglednik. Stranica će učitati kartu, zatim učitati sve GPS podatke iz pohrane i prikazati ih na karti.

    ![Karta Saint Edward State Parka blizu Seattlea, s krugovima koji prikazuju put oko ruba parka](../../../../../translated_images/hr/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Ovaj kod možete pronaći u [code](../../../../../3-transport/lessons/3-visualize-location-data/code) mapi.

---

## 🚀 Izazov

Lijepo je moći prikazati statične podatke na karti kao oznake. Možete li unaprijediti ovu web aplikaciju kako biste dodali animaciju i prikazali put oznaka tijekom vremena, koristeći JSON datoteke s vremenskim oznakama? Evo [nekih primjera](https://azuremapscodesamples.azurewebsites.net/) korištenja animacije unutar karata.

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Pregled i samostalno učenje

Azure Maps je posebno koristan za rad s IoT uređajima.

* Istražite neke od primjena u [dokumentaciji Azure Maps na Microsoft docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Produbite svoje znanje o izradi karata i točkama puta s [modulom za samostalno učenje "create your first route finding app with Azure Maps" na Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Zadatak

[Postavite svoju aplikaciju](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.