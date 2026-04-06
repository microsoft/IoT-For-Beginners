# Vizualizacija podatkov o lokaciji

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-13.a259db1485021be7.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite sliko za večjo različico.

Ta video ponuja pregled Azure Maps z IoT, storitve, ki bo obravnavana v tej lekciji.

[![Azure Maps - Microsoftova platforma za lokacijske storitve](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Kliknite zgornjo sliko za ogled videa

## Predlekcijski kviz

[Predlekcijski kviz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Uvod

V prejšnji lekciji ste se naučili, kako pridobiti GPS podatke iz svojih senzorjev in jih shraniti v oblačno shrambo s pomočjo strežniške kode. Zdaj boste odkrili, kako te točke vizualizirati na zemljevidu Azure. Naučili se boste, kako ustvariti zemljevid na spletni strani, spoznali format podatkov GeoJSON in kako ga uporabiti za prikaz vseh zajetih GPS točk na vašem zemljevidu.

V tej lekciji bomo obravnavali:

* [Kaj je vizualizacija podatkov](../../../../../3-transport/lessons/3-visualize-location-data)
* [Storitve zemljevidov](../../../../../3-transport/lessons/3-visualize-location-data)
* [Ustvarjanje vira Azure Maps](../../../../../3-transport/lessons/3-visualize-location-data)
* [Prikaz zemljevida na spletni strani](../../../../../3-transport/lessons/3-visualize-location-data)
* [Format GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)
* [Prikaz GPS podatkov na zemljevidu z uporabo GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Ta lekcija vključuje nekaj osnov HTML in JavaScript. Če želite izvedeti več o spletnem razvoju z uporabo HTML in JavaScript, si oglejte [Spletni razvoj za začetnike](https://github.com/microsoft/Web-Dev-For-Beginners).

## Kaj je vizualizacija podatkov

Vizualizacija podatkov, kot že ime pove, pomeni prikazovanje podatkov na način, ki ljudem olajša razumevanje. Običajno je povezana z grafikoni in diagrami, vendar vključuje vsak način slikovnega prikaza podatkov, ki pomaga ljudem bolje razumeti podatke in sprejemati odločitve.

Vzemimo preprost primer - v projektu na kmetiji ste zajeli podatke o vlažnosti tal. Tabela podatkov o vlažnosti tal, zajetih vsako uro 1. junija 2021, bi lahko izgledala takole:

| Datum            | Branje |
| ---------------- | ------: |
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

Za človeka je razumevanje teh podatkov lahko težavno. Gre za steno številk brez pravega pomena. Kot prvi korak k vizualizaciji teh podatkov jih lahko prikažemo na linijskem grafikonu:

![Linijski grafikon zgornjih podatkov](../../../../../translated_images/sl/chart-soil-moisture.fd6d9d0cdc0b5f75.webp)

To lahko še izboljšamo z dodajanjem črte, ki označuje, kdaj je bil avtomatski namakalni sistem vklopljen pri branju vlažnosti tal 450:

![Linijski grafikon vlažnosti tal z označeno črto pri 450](../../../../../translated_images/sl/chart-soil-moisture-relay.fbb391236d34a64d.webp)

Ta grafikon hitro pokaže ne samo, kakšne so bile ravni vlažnosti tal, temveč tudi točke, kjer je bil namakalni sistem vklopljen.

Grafikoni niso edino orodje za vizualizacijo podatkov. IoT naprave, ki spremljajo vreme, lahko uporabljajo spletne ali mobilne aplikacije za prikaz vremenskih razmer s simboli, kot so oblak za oblačne dni, dežni oblak za deževne dni in podobno. Obstaja ogromno načinov za vizualizacijo podatkov, nekateri resni, drugi zabavni.

✅ Razmislite o načinih, kako ste že videli vizualizirane podatke. Kateri načini so bili najbolj jasni in so vam omogočili najhitrejše sprejemanje odločitev?

Najboljše vizualizacije omogočajo ljudem hitro sprejemanje odločitev. Na primer, stena merilnikov z vsemi možnimi odčitki industrijskih strojev je težko razumljiva, vendar utripajoča rdeča lučka, ko gre kaj narobe, omogoča hitro odločitev. Včasih je najboljša vizualizacija utripajoča lučka!

Pri delu z GPS podatki je najjasnejša vizualizacija pogosto prikaz podatkov na zemljevidu. Zemljevid, ki prikazuje dostavna vozila, lahko na primer pomaga delavcem v obratu videti, kdaj bodo vozila prispela. Če ta zemljevid prikazuje več kot le slike vozil na njihovih trenutnih lokacijah, ampak tudi informacije o vsebini vozila, lahko delavci v obratu ustrezno načrtujejo - če vidijo, da je v bližini hladilno vozilo, vedo, da morajo pripraviti prostor v hladilniku.

## Storitve zemljevidov

Delo z zemljevidi je zanimiva naloga, saj je na voljo veliko možnosti, kot so Bing Maps, Leaflet, Open Street Maps in Google Maps. V tej lekciji boste spoznali [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) in kako lahko prikažejo vaše GPS podatke.

![Logotip Azure Maps](../../../../../translated_images/sl/azure-maps-logo.35d01dcfbd81fe61.webp)

Azure Maps je "zbirka geolokacijskih storitev in SDK-jev, ki uporabljajo sveže podatke o zemljevidih za zagotavljanje geografskega konteksta spletnim in mobilnim aplikacijam." Razvijalcem so na voljo orodja za ustvarjanje čudovitih, interaktivnih zemljevidov, ki lahko na primer priporočajo prometne poti, zagotavljajo informacije o prometnih incidentih, omogočajo notranjo navigacijo, iskalne zmogljivosti, informacije o nadmorski višini, vremenske storitve in še več.

✅ Preizkusite nekaj [primerov kode za zemljevide](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Zemljevide lahko prikažete kot prazno platno, ploščice, satelitske slike, satelitske slike s cestami, različne vrste sivinskih zemljevidov, zemljevide s senčenjem za prikaz nadmorske višine, nočne zemljevide in zemljevide z visokim kontrastom. Realnočasovne posodobitve na zemljevidih lahko omogočite z integracijo z [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Izgled in obnašanje zemljevidov lahko nadzorujete z omogočanjem različnih kontrol, ki omogočajo, da zemljevid reagira na dogodke, kot so ščipanje, vlečenje in klikanje. Izgled zemljevida lahko prilagodite z dodajanjem slojev, ki vključujejo mehurčke, črte, poligone, toplotne zemljevide in še več. Kateri slog zemljevida boste uporabili, je odvisno od izbire SDK-ja.

V tej lekciji boste uporabili spletni SDK za risanje zemljevida in prikaz poti GPS lokacij vašega senzorja.

## Ustvarjanje vira Azure Maps

Vaš prvi korak je ustvariti račun Azure Maps.

### Naloga - ustvarite vir Azure Maps

1. Zaženite naslednji ukaz v terminalu ali ukazni vrstici, da ustvarite vir Azure Maps v svoji skupini virov `gps-sensor`:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    To bo ustvarilo vir Azure Maps z imenom `gps-sensor`. Uporabljena stopnja je `S1`, kar je plačljiva stopnja, ki vključuje širok nabor funkcij, vendar z velikodušno količino brezplačnih klicev.

    > 💁 Če želite izvedeti stroške uporabe Azure Maps, si oglejte [stran s cenami Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Potrebovali boste API ključ za vir zemljevidov. Uporabite naslednji ukaz za pridobitev tega ključa:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Shranite vrednost `PrimaryKey`.

## Prikaz zemljevida na spletni strani

Zdaj lahko naredite naslednji korak, to je prikaz zemljevida na spletni strani. Uporabili bomo samo eno datoteko `html` za vašo majhno spletno aplikacijo; upoštevajte, da bo v produkcijskem ali timskem okolju vaša spletna aplikacija verjetno imela več delov!

### Naloga - prikaz zemljevida na spletni strani

1. Ustvarite datoteko z imenom index.html v mapi na svojem lokalnem računalniku. Dodajte HTML oznake za prikaz zemljevida:

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

    Zemljevid se bo naložil v `div` z imenom `myMap`. Nekaj slogov omogoča, da zavzame širino in višino strani.

    > 🎓 `div` je odsek spletne strani, ki ga je mogoče poimenovati in oblikovati.

1. Pod začetno oznako `<head>` dodajte zunanji slogovni list za nadzor prikaza zemljevida in zunanji skript iz spletnega SDK-ja za upravljanje njegovega obnašanja:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Ta slogovni list vsebuje nastavitve za izgled zemljevida, datoteka skripta pa vsebuje kodo za nalaganje zemljevida. Dodajanje te kode je podobno vključevanju C++ glavičnih datotek ali uvažanju Python modulov.

1. Pod tem skriptom dodajte blok skripta za zagon zemljevida.

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

    Zamenjajte `<subscription_key>` z API ključem za vaš račun Azure Maps.

    Če odprete svojo datoteko `index.html` v spletnem brskalniku, bi morali videti zemljevid, osredotočen na območje Seattla.

    ![Zemljevid, ki prikazuje Seattle, mesto v zvezni državi Washington, ZDA](../../../../../translated_images/sl/map-image.8fb2c53eb23ef39c.webp)

    ✅ Eksperimentirajte s parametri za povečavo in središče, da spremenite prikaz zemljevida. Dodate lahko različne koordinate, ki ustrezajo zemljepisni širini in dolžini vaših podatkov, da ponovno centrirate zemljevid.

> 💁 Boljši način za delo s spletnimi aplikacijami lokalno je namestitev [http-server](https://www.npmjs.com/package/http-server). Pred uporabo tega orodja boste potrebovali nameščena [node.js](https://nodejs.org/) in [npm](https://www.npmjs.com/). Ko so ta orodja nameščena, lahko navigirate do lokacije vaše datoteke `index.html` in vtipkate `http-server`. Spletna aplikacija se bo odprla na lokalnem spletnem strežniku [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## Format GeoJSON

Zdaj, ko imate svojo spletno aplikacijo pripravljeno z zemljevidom, morate iz svojega računa za shranjevanje pridobiti GPS podatke in jih prikazati v sloju markerjev na zemljevidu. Preden to storimo, si oglejmo format [GeoJSON](https://wikipedia.org/wiki/GeoJSON), ki ga zahteva Azure Maps.

[GeoJSON](https://geojson.org/) je odprt standard JSON specifikacije s posebnim formatiranjem, zasnovanim za obravnavo geografskih podatkov. O njem se lahko naučite več s testiranjem vzorčnih podatkov z uporabo [geojson.io](https://geojson.io), ki je tudi uporabno orodje za odpravljanje napak v GeoJSON datotekah.

Vzorčni GeoJSON podatki izgledajo takole:

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

Posebej zanimiva je struktura podatkov kot `Feature` znotraj `FeatureCollection`. Znotraj tega objekta najdemo `geometry` z `coordinates`, ki označujejo zemljepisno dolžino in širino.

✅ Pri gradnji svojega GeoJSON bodite pozorni na vrstni red `latitude` in `longitude` v objektu, sicer se vaše točke ne bodo pojavile na pravem mestu! GeoJSON pričakuje podatke v vrstnem redu `lon,lat` za točke, ne `lat,lon`.

`Geometry` lahko ima različne tipe, kot so posamezna točka ali poligon. V tem primeru gre za točko z dvema določenima koordinatama, zemljepisno dolžino in širino.
✅ Azure Maps podpira standardni GeoJSON ter nekaj [izboljšanih funkcij](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), vključno z možnostjo risanja krogov in drugih geometrij.

## Prikaz GPS podatkov na zemljevidu z uporabo GeoJSON

Sedaj ste pripravljeni na uporabo podatkov iz shrambe, ki ste jo ustvarili v prejšnji lekciji. Kot opomnik, podatki so shranjeni kot več datotek v blob shrambi, zato jih morate pridobiti in razčleniti, da jih lahko Azure Maps uporabi.

### Naloga - konfigurirajte shrambo za dostop iz spletne strani

Če pokličete svojo shrambo za pridobitev podatkov, vas lahko preseneti pojav napak v konzoli vašega brskalnika. To se zgodi, ker morate nastaviti dovoljenja za [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) v tej shrambi, da omogočite zunanjim spletnim aplikacijam dostop do podatkov.

> 🎓 CORS pomeni "Cross-Origin Resource Sharing" in ga je običajno treba izrecno nastaviti v Azure zaradi varnostnih razlogov. Preprečuje, da bi nepričakovane strani dostopale do vaših podatkov.

1. Za omogočanje CORS zaženite naslednji ukaz:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Zamenjajte `<storage_name>` z imenom vašega računa za shranjevanje. Zamenjajte `<key1>` z ključem računa za vašo shrambo.

    Ta ukaz omogoča katerikoli spletni strani (zvezdica `*` pomeni katerokoli) izvedbo *GET* zahteve, torej pridobitev podatkov iz vašega računa za shranjevanje. Parameter `--services b` pomeni, da se ta nastavitev uporablja samo za blob shrambo.

### Naloga - nalaganje GPS podatkov iz shrambe

1. Zamenjajte celotno vsebino funkcije `init` z naslednjo kodo:

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

    Zamenjajte `<storage_name>` z imenom vašega računa za shranjevanje. Zamenjajte `<subscription_key>` z API ključem za vaš Azure Maps račun.

    Tukaj se dogaja več stvari. Najprej koda pridobi vaše GPS podatke iz blob shrambe z uporabo URL-ja, ki je sestavljen z imenom vašega računa za shranjevanje. Ta URL pridobi podatke iz `gps-data`, kar označuje, da je vrsta vira vsebnik (`restype=container`), in prikaže informacije o vseh blobih. Ta seznam ne bo vrnil samih blobov, ampak URL za vsak blob, ki ga je mogoče uporabiti za nalaganje podatkov bloba.

    > 💁 Ta URL lahko vnesete v svoj brskalnik, da si ogledate podrobnosti o vseh blobih v vašem vsebniku. Vsak element bo imel lastnost `Url`, ki jo lahko prav tako naložite v brskalnik, da si ogledate vsebino bloba.

    Nato koda naloži vsak blob, pri čemer pokliče funkcijo `loadJSON`, ki jo bomo ustvarili v naslednjem koraku. Nato ustvari kontrolnik zemljevida in doda kodo za dogodek `ready`. Ta dogodek se sproži, ko je zemljevid prikazan na spletni strani.

    Dogodek `ready` ustvari vir podatkov za Azure Maps - vsebnik, ki vsebuje GeoJSON podatke, ki bodo kasneje napolnjeni. Ta vir podatkov se nato uporabi za ustvarjanje sloja mehurčkov - to je niz krogov na zemljevidu, ki so centrirani nad vsako točko v GeoJSON.

1. Dodajte funkcijo `loadJSON` v svoj skriptni blok, pod funkcijo `init`:

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

    Ta funkcija se pokliče med rutino pridobivanja podatkov za razčlenitev JSON podatkov in njihovo pretvorbo v format, ki ga je mogoče brati kot geografske koordinate (dolžina in širina) v GeoJSON.
    Ko so podatki razčlenjeni, se nastavijo kot del GeoJSON `Feature`. Zemljevid bo inicializiran in majhni mehurčki se bodo pojavili okoli poti, ki jo vaši podatki prikazujejo:

1. Naložite HTML stran v svoj brskalnik. Stran bo naložila zemljevid, nato pa vse GPS podatke iz shrambe in jih prikazala na zemljevidu.

    ![Zemljevid Saint Edward State Park blizu Seattla, s krogi, ki prikazujejo pot okoli roba parka](../../../../../translated_images/sl/map-path.896832e72dc696ff.webp)

> 💁 To kodo lahko najdete v [code](../../../../../3-transport/lessons/3-visualize-location-data/code) mapi.

---

## 🚀 Izziv

Lepo je prikazati statične podatke na zemljevidu kot označevalce. Ali lahko izboljšate to spletno aplikacijo tako, da dodate animacijo in prikažete pot označevalcev skozi čas, z uporabo časovno označenih JSON datotek? Tukaj so [nekateri primeri](https://azuremapscodesamples.azurewebsites.net/) uporabe animacije znotraj zemljevidov.

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Pregled in samostojno učenje

Azure Maps je še posebej uporaben za delo z IoT napravami.

* Raziščite nekatere uporabe v [dokumentaciji Azure Maps na Microsoft docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Poglobite svoje znanje o izdelavi zemljevidov in točkah poti z [modulom za samostojno učenje o ustvarjanju prve aplikacije za iskanje poti z Azure Maps na Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Naloga

[Namestite svojo aplikacijo](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.