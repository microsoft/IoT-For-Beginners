# Visualisoi sijaintitiedot

![Tämän oppitunnin yleiskuvaus sketchnotena](../../../../../translated_images/fi/lesson-13.a259db1485021be7.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä video antaa yleiskatsauksen Azure Maps -palvelusta IoT:n kanssa, jota käsitellään tässä oppitunnissa.

[![Azure Maps - Microsoft Azuren yritystason sijaintialusta](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Klikkaa yllä olevaa kuvaa katsoaksesi videon

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Johdanto

Edellisessä oppitunnissa opit, kuinka GPS-tiedot saadaan antureista ja tallennetaan pilveen säilöön palvelimettoman koodin avulla. Nyt opit, kuinka nämä pisteet voidaan visualisoida Azure-kartalla. Opit luomaan kartan verkkosivulle, tutustut GeoJSON-tiedostomuotoon ja opit käyttämään sitä kaikkien tallennettujen GPS-pisteiden piirtämiseen kartallesi.

Tässä oppitunnissa käsitellään:

* [Mitä on datan visualisointi](../../../../../3-transport/lessons/3-visualize-location-data)
* [Karttapalvelut](../../../../../3-transport/lessons/3-visualize-location-data)
* [Azure Maps -resurssin luominen](../../../../../3-transport/lessons/3-visualize-location-data)
* [Kartta verkkosivulle](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON-muoto](../../../../../3-transport/lessons/3-visualize-location-data)
* [GPS-datan piirtäminen kartalle GeoJSONin avulla](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Tämä oppitunti sisältää hieman HTML- ja JavaScript-koodia. Jos haluat oppia lisää verkkokehityksestä HTML:n ja JavaScriptin avulla, tutustu [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners).

## Mitä on datan visualisointi

Datan visualisointi tarkoittaa datan esittämistä visuaalisessa muodossa, joka helpottaa ihmisten ymmärrystä. Se liittyy usein kaavioihin ja graafeihin, mutta voi olla mikä tahansa tapa esittää dataa kuvallisesti, jotta ihmiset ymmärtävät sen paremmin ja voivat tehdä päätöksiä.

Yksinkertainen esimerkki: maatilaprojektissa tallensit maaperän kosteustietoja. Taulukko, joka näyttää maaperän kosteustiedot tunnin välein 1. kesäkuuta 2021, voisi näyttää tältä:

| Päivämäärä        | Lukema |
| ----------------- | ------: |
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

Ihmisen on vaikea ymmärtää tällaista dataa. Se on pelkkä numeroseinä ilman merkitystä. Ensimmäinen askel datan visualisoinnissa voisi olla sen piirtäminen viivakaavioon:

![Viivakaavio yllä olevasta datasta](../../../../../translated_images/fi/chart-soil-moisture.fd6d9d0cdc0b5f75.webp)

Tätä voidaan parantaa lisäämällä viiva, joka osoittaa, milloin automaattinen kastelujärjestelmä käynnistyi kosteusarvolla 450:

![Viivakaavio maaperän kosteudesta ja viiva arvolla 450](../../../../../translated_images/fi/chart-soil-moisture-relay.fbb391236d34a64d.webp)

Tämä kaavio näyttää nopeasti paitsi maaperän kosteustasot myös kohdat, joissa kastelujärjestelmä käynnistyi.

Kaaviot eivät ole ainoa tapa visualisoida dataa. IoT-laitteet, jotka seuraavat säätä, voivat käyttää verkkosovelluksia tai mobiilisovelluksia, jotka visualisoivat sääolosuhteita symboleilla, kuten pilvisymbolilla pilvisille päiville tai sadepilvellä sateisille päiville. Datan visualisointitapoja on lukemattomia, osa vakavia, osa hauskoja.

✅ Mieti tapoja, joilla olet nähnyt dataa visualisoitavan. Mitkä menetelmät ovat olleet selkeimpiä ja auttaneet sinua tekemään päätöksiä nopeimmin?

Parhaat visualisoinnit auttavat ihmisiä tekemään päätöksiä nopeasti. Esimerkiksi teollisuuskoneiden lukemien näyttäminen mittaritaululla voi olla vaikeaa käsitellä, mutta vilkkuva punainen valo, kun jokin menee pieleen, auttaa ihmistä tekemään päätöksen. Joskus paras visualisointi on vilkkuva valo!

Kun työskentelet GPS-datan kanssa, selkein tapa visualisoida dataa on piirtää se kartalle. Esimerkiksi kartta, joka näyttää jakeluautot, voi auttaa työntekijöitä käsittelylaitoksessa näkemään, milloin autot saapuvat. Jos kartta näyttää enemmän kuin vain kuvia autoista niiden nykyisissä sijainneissa, kuten tietoa auton sisällöstä, työntekijät voivat suunnitella toimintaansa sen mukaan – jos he näkevät lähistöllä olevan kylmäauton, he tietävät valmistautua jääkaappitilaan.

## Karttapalvelut

Karttojen kanssa työskentely on mielenkiintoista, ja valittavana on monia vaihtoehtoja, kuten Bing Maps, Leaflet, Open Street Maps ja Google Maps. Tässä oppitunnissa opit [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) -palvelusta ja siitä, kuinka se voi näyttää GPS-datasi.

![Azure Maps -logo](../../../../../translated_images/fi/azure-maps-logo.35d01dcfbd81fe61.webp)

Azure Maps on "kokoelma paikkatietopalveluita ja SDK:ita, jotka käyttävät ajankohtaista karttatietoa tarjotakseen maantieteellistä kontekstia verkkosovelluksille ja mobiilisovelluksille." Kehittäjille tarjotaan työkaluja luoda kauniita, interaktiivisia karttoja, jotka voivat esimerkiksi tarjota suositeltuja liikennereittejä, tietoa liikenneonnettomuuksista, sisätilanavigointia, hakutoimintoja, korkeustietoja, säätietopalveluita ja paljon muuta.

✅ Kokeile joitakin [karttakoodiesimerkkejä](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Voit näyttää karttoja tyhjänä kankaana, laattoina, satelliittikuvina, satelliittikuvina teiden kanssa, erilaisina harmaasävyinä, korkeustietoja korostavina karttoina, yötilakarttoina ja korkean kontrastin karttoina. Voit saada reaaliaikaisia päivityksiä kartoillesi integroimalla ne [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn) -palveluun. Voit hallita karttojesi käyttäytymistä ja ulkoasua ottamalla käyttöön erilaisia ohjaimia, jotka mahdollistavat kartan reagoimisen tapahtumiin, kuten nipistämiseen, vetämiseen ja klikkaukseen. Kartan ulkoasua voit hallita lisäämällä kerroksia, jotka sisältävät kuplia, viivoja, monikulmioita, lämpökarttoja ja paljon muuta. Kartan tyyli riippuu valitsemastasi SDK:sta.

Voit käyttää Azure Maps -rajapintoja hyödyntämällä sen [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest) -rajapintaa, [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn) -ohjelmistokehityspakettia tai, jos rakennat mobiilisovellusta, sen [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android) -ohjelmistokehityspakettia.

Tässä oppitunnissa käytät Web SDK:ta piirtääksesi kartan ja näyttääksesi anturisi GPS-sijaintien reitin.

## Azure Maps -resurssin luominen

Ensimmäinen askel on luoda Azure Maps -tili.

### Tehtävä - Azure Maps -resurssin luominen

1. Suorita seuraava komento terminaalissasi tai komentokehotteessasi luodaksesi Azure Maps -resurssin `gps-sensor`-resurssiryhmään:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Tämä luo Azure Maps -resurssin nimeltä `gps-sensor`. Käytettävä taso on `S1`, joka on maksullinen taso, mutta sisältää runsaasti ilmaisia kutsuja.

    > 💁 Katso Azure Maps -käytön kustannukset [Azure Maps -hinnoittelusivulta](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Tarvitset API-avaimen karttaresurssille. Käytä seuraavaa komentoa saadaksesi tämän avaimen:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Kopioi `PrimaryKey`-arvo.

## Kartta verkkosivulle

Seuraava askel on näyttää kartta verkkosivulla. Käytämme vain yhtä `html`-tiedostoa pienelle verkkosovelluksellesi; pidä mielessä, että tuotanto- tai tiimiympäristössä verkkosovelluksesi sisältää todennäköisesti enemmän osia!

### Tehtävä - kartan näyttäminen verkkosivulla

1. Luo tiedosto nimeltä index.html johonkin kansioon paikallisella tietokoneellasi. Lisää HTML-rakenne kartan näyttämiseksi:

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

    Kartta latautuu `myMap`-nimiseen `div`-elementtiin. Muutamat tyylit mahdollistavat sen venymisen sivun leveyteen ja korkeuteen.

    > 🎓 `div` on verkkosivun osa, joka voidaan nimetä ja tyylittää.

1. Lisää `<head>`-tagin alle ulkoinen tyylitiedosto kartan ulkoasun hallitsemiseksi ja ulkoinen skripti Web SDK:sta sen toiminnan hallitsemiseksi:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Tämä tyylitiedosto sisältää asetukset kartan ulkoasulle, ja skriptitiedosto sisältää koodin kartan lataamiseen. Tämän koodin lisääminen on samanlaista kuin C++-otsikkotiedostojen sisällyttäminen tai Python-moduulien tuominen.

1. Lisää tämän skriptin alle skriptiblokki kartan käynnistämiseksi.

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

    Korvaa `<subscription_key>` Azure Maps -tilisi API-avaimella.

    Jos avaat `index.html`-sivusi verkkoselaimessa, sinun pitäisi nähdä kartta, joka on keskitetty Seattlen alueelle.

    ![Kartta, joka näyttää Seattlen, kaupungin Washingtonin osavaltiossa, USA:ssa](../../../../../translated_images/fi/map-image.8fb2c53eb23ef39c.webp)

    ✅ Kokeile zoomaus- ja keskitysparametreja muuttaaksesi kartan näkymää. Voit lisätä eri koordinaatit, jotka vastaavat datasi leveys- ja pituusasteita, keskittääksesi kartan uudelleen.

> 💁 Parempi tapa työskennellä verkkosovellusten kanssa paikallisesti on asentaa [http-server](https://www.npmjs.com/package/http-server). Tarvitset [node.js](https://nodejs.org/) ja [npm](https://www.npmjs.com/) -työkalut ennen tämän työkalun käyttöä. Kun nämä työkalut on asennettu, voit siirtyä `index.html`-tiedostosi sijaintiin ja kirjoittaa `http-server`. Verkkosovellus avautuu paikallisessa verkkopalvelimessa [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## GeoJSON-muoto

Nyt kun verkkosovelluksesi on paikallaan ja kartta näkyy, sinun täytyy hakea GPS-data tallennustililtäsi ja näyttää se kartan päällä kerroksena merkkejä. Ennen kuin teemme tämän, tarkastellaan [GeoJSON](https://wikipedia.org/wiki/GeoJSON)-muotoa, jota Azure Maps vaatii.

[GeoJSON](https://geojson.org/) on avoin JSON-standardispesifikaatio, joka on suunniteltu käsittelemään maantieteellistä dataa. Voit oppia siitä testaamalla esimerkkidataa [geojson.io](https://geojson.io)-sivustolla, joka on myös hyödyllinen työkalu GeoJSON-tiedostojen virheenkorjaukseen.

Esimerkkidata GeoJSON-muodossa näyttää tältä:

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

Erityisen kiinnostavaa on tapa, jolla data on sisäkkäin `Feature`-objektina `FeatureCollection`-objektin sisällä. Tämän objektin sisällä on `geometry`, jossa `coordinates` osoittaa leveys- ja pituusasteet.

✅ Kun rakennat GeoJSON-tiedostoasi, kiinnitä huomiota `latitude`- ja `longitude`-järjestykseen objektissa, tai pisteesi eivät näy oikeassa paikassa! GeoJSON odottaa dataa järjestyksessä `lon,lat` pisteille, ei `lat,lon`.

`Geometry` voi olla eri tyyppinen, kuten yksittäinen piste tai monikulmio. Tässä esimerkissä se on piste, jossa on kaksi koordinaattia, pituus- ja leveysaste.
✅ Azure Maps tukee standardia GeoJSON-muotoa sekä joitakin [laajennettuja ominaisuuksia](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), kuten mahdollisuutta piirtää ympyröitä ja muita geometrioita.

## GPS-datan esittäminen kartalla GeoJSON-muodossa

Nyt olet valmis käyttämään edellisessä osiossa luomasi tallennustilan dataa. Muistutuksena, data on tallennettu useisiin tiedostoihin blob-tallennustilassa, joten sinun täytyy hakea ja jäsentää tiedostot, jotta Azure Maps voi käyttää niitä.

### Tehtävä - määritä tallennustila verkkosivulta käytettäväksi

Kun teet kutsun tallennustilaasi hakeaksesi dataa, saatat yllättyä, jos selaimesi konsolissa näkyy virheitä. Tämä johtuu siitä, että sinun täytyy asettaa [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS)-oikeudet tälle tallennustilalle, jotta ulkoiset verkkosovellukset voivat lukea sen dataa.

> 🎓 CORS tarkoittaa "Cross-Origin Resource Sharing" ja se täytyy yleensä määrittää erikseen Azureen turvallisuussyistä. Se estää odottamattomia sivustoja pääsemästä käsiksi dataasi.

1. Suorita seuraava komento ottaaksesi CORS käyttöön:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Korvaa `<storage_name>` tallennustilisi nimellä. Korvaa `<key1>` tallennustilisi tilin avaimella.

    Tämä komento sallii minkä tahansa verkkosivuston (tähtimerkki `*` tarkoittaa mitä tahansa) tehdä *GET*-pyynnön, eli hakea dataa tallennustilastasi. `--services b` tarkoittaa, että tämä asetus koskee vain blob-tallennustilaa.

### Tehtävä - lataa GPS-data tallennustilasta

1. Korvaa `init`-funktion koko sisältö seuraavalla koodilla:

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

    Korvaa `<storage_name>` tallennustilisi nimellä. Korvaa `<subscription_key>` Azure Maps -tilisi API-avaimella.

    Tässä tapahtuu useita asioita. Ensinnäkin koodi hakee GPS-datasi blob-kontista URL-osoitteen avulla, joka on rakennettu tallennustilisi nimen perusteella. Tämä URL hakee `gps-data`-kontista, mikä osoittaa, että resurssityyppi on kontti (`restype=container`), ja listaa tietoja kaikista blob-tiedostoista. Tämä lista ei palauta itse blob-tiedostoja, mutta antaa URL-osoitteen jokaiselle blobille, jota voidaan käyttää blobin datan lataamiseen.

    > 💁 Voit laittaa tämän URL-osoitteen selaimeesi nähdäksesi kaikki konttisi blobit. Jokaisella kohteella on `Url`-ominaisuus, jonka voit myös ladata selaimessasi nähdäksesi blobin sisällön.

    Tämä koodi lataa sitten jokaisen blobin kutsumalla `loadJSON`-funktiota, joka luodaan seuraavaksi. Se luo myös karttakomponentin ja lisää koodia `ready`-tapahtumaan. Tämä tapahtuma kutsutaan, kun kartta näytetään verkkosivulla.

    Ready-tapahtuma luo Azure Maps -datalähteen - säiliön, joka sisältää GeoJSON-dataa, joka lisätään myöhemmin. Tämä datalähde käytetään sitten luomaan kuplakerros - joukko ympyröitä kartalle, jotka on keskitetty GeoJSON:n jokaisen pisteen kohdalle.

1. Lisää `loadJSON`-funktio skriptiblokkiisi `init`-funktion alapuolelle:

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

    Tämä funktio kutsutaan hakurutiinista jäsentämään JSON-data ja muuntamaan se luettavaksi pituus- ja leveyskoordinaatteina GeoJSON-muodossa. Kun data on jäsennelty, se asetetaan osaksi GeoJSON `Feature`-ominaisuutta. Kartta alustetaan, ja pieniä ympyröitä ilmestyy reitille, jota datasi kuvaa:

1. Lataa HTML-sivu selaimeesi. Se lataa kartan, hakee kaikki GPS-datat tallennustilasta ja piirtää ne kartalle.

    ![Kartta Saint Edward State Parkista Seattlen lähellä, jossa ympyrät näyttävät reitin puiston reunalla](../../../../../translated_images/fi/map-path.896832e72dc696ff.webp)

> 💁 Löydät tämän koodin [code](../../../../../3-transport/lessons/3-visualize-location-data/code)-kansiosta.

---

## 🚀 Haaste

On hienoa pystyä näyttämään staattista dataa kartalla merkkeinä. Voitko parantaa tätä verkkosovellusta lisäämällä animaation ja näyttämällä merkkien reitin ajan kuluessa, käyttäen aikaleimattuja json-tiedostoja? Tässä on [joitakin esimerkkejä](https://azuremapscodesamples.azurewebsites.net/) animaation käytöstä kartoilla.

## Luentojälkeinen kysely

[Luentojälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Kertaus ja itseopiskelu

Azure Maps on erityisen hyödyllinen IoT-laitteiden kanssa työskentelyyn.

* Tutki joitakin käyttötapoja [Azure Maps -dokumentaatiosta Microsoft Docsissa](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Syvennä tietämystäsi karttojen tekemisestä ja reittipisteistä [Luo ensimmäinen reitinhakusovelluksesi Azure Mapsilla -itseopiskelumoduulin avulla Microsoft Learnissa](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Tehtävä

[Ota sovelluksesi käyttöön](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.