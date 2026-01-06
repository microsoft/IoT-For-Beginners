<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-27T22:44:47+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "fi"
}
-->
# Geoaidat

![Tämän oppitunnin yleiskatsaus sketchnotena](../../../../../translated_images/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.fi.jpg)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä video tarjoaa yleiskatsauksen geoaidoista ja niiden käytöstä Azure Mapsissa, aiheita, joita käsitellään tässä oppitunnissa:

[![Geoaidat Azure Mapsissa Microsoft Developer IoT -ohjelmassa](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Klikkaa yllä olevaa kuvaa katsoaksesi videon

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Johdanto

Viimeisten kolmen oppitunnin aikana olet käyttänyt IoT:ta paikantamaan kuorma-autoja, jotka kuljettavat tuotteitasi maatilaltasi käsittelykeskukseen. Olet tallentanut GPS-tiedot pilveen ja visualisoinut ne kartalla. Seuraava askel toimitusketjun tehokkuuden parantamisessa on saada ilmoitus, kun kuorma-auto on saapumassa käsittelykeskukseen, jotta purkamisesta vastaava tiimi voi olla valmiina trukkien ja muiden laitteiden kanssa heti ajoneuvon saapuessa. Näin purkaminen sujuu nopeasti, eikä sinun tarvitse maksaa kuorma-auton ja kuljettajan odotusajasta.

Tässä oppitunnissa opit geoaidoista – määritellyistä maantieteellisistä alueista, kuten alueesta, joka on 2 km ajomatkan päässä käsittelykeskuksesta – ja siitä, miten testata, ovatko GPS-koordinaatit geoaidan sisä- vai ulkopuolella, jotta voit nähdä, onko GPS-anturi saapunut alueelle tai poistunut sieltä.

Tässä oppitunnissa käsitellään:

* [Mitä geoaidat ovat](../../../../../3-transport/lessons/4-geofences)
* [Geoaidan määrittäminen](../../../../../3-transport/lessons/4-geofences)
* [Pisteiden testaaminen geoaidan suhteen](../../../../../3-transport/lessons/4-geofences)
* [Geoaidan käyttö palvelimettomassa koodissa](../../../../../3-transport/lessons/4-geofences)

> 🗑 Tämä on projektin viimeinen oppitunti, joten kun olet suorittanut tämän oppitunnin ja tehtävän, muista siivota pilvipalvelusi. Tarvitset palvelut tehtävän suorittamiseen, joten varmista, että teet sen ensin.
>
> Katso tarvittaessa [projektin siivousopas](../../../clean-up.md) saadaksesi ohjeita.

## Mitä geoaidat ovat

Geoaidat ovat virtuaalisia rajoja todellisille maantieteellisille alueille. Geoaidat voivat olla ympyröitä, jotka määritellään pisteenä ja säteenä (esimerkiksi 100 m leveä ympyrä rakennuksen ympärillä), tai monikulmioita, jotka kattavat alueen, kuten koulun alueen, kaupungin rajat tai yliopiston tai toimiston kampuksen.

![Esimerkkejä geoaidoista: ympyrä Microsoftin yrityskaupan ympärillä ja monikulmio Microsoftin länsikampuksen ympärillä](../../../../../translated_images/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.fi.png)

> 💁 Olet ehkä jo käyttänyt geoaidoja tietämättäsi. Jos olet asettanut muistutuksen iOS-muistutussovelluksessa tai Google Keepissä sijainnin perusteella, olet käyttänyt geoaitaa. Nämä sovellukset luovat geoaidan annetun sijainnin perusteella ja ilmoittavat sinulle, kun puhelimesi saapuu geoaidan sisälle.

On monia syitä, miksi haluaisit tietää, onko ajoneuvo geoaidan sisä- vai ulkopuolella:

* Purkamisen valmistelu – ilmoitus ajoneuvon saapumisesta paikalle mahdollistaa tiimin valmistautumisen ajoneuvon purkamiseen, mikä vähentää ajoneuvon odotusaikaa. Tämä voi mahdollistaa kuljettajan tekemään enemmän toimituksia päivässä vähemmällä odotusajalla.
* Veronmukaisuus – jotkut maat, kuten Uusi-Seelanti, perivät dieselajoneuvoilta tiekuluja ajoneuvon painon perusteella vain julkisilla teillä ajettaessa. Geoaidat mahdollistavat julkisilla teillä ajetun matkan seuraamisen verrattuna yksityisteihin, kuten maatiloilla tai hakkuualueilla.
* Varkauden valvonta – jos ajoneuvon pitäisi pysyä tietyllä alueella, kuten maatilalla, ja se poistuu geoaidan ulkopuolelle, se on voitu varastaa.
* Sijaintimukaisuus – tietyt työmaan, maatilan tai tehtaan osat voivat olla kiellettyjä tietyiltä ajoneuvoilta, kuten ajoneuvoilta, jotka kuljettavat keinotekoisia lannoitteita ja torjunta-aineita, jotta ne eivät pääse orgaanista tuotantoa kasvattaville pelloille. Jos geoaidan sisälle mennään, ajoneuvo on sääntöjen vastainen, ja kuljettajalle voidaan ilmoittaa.

✅ Keksitkö muita käyttötarkoituksia geoaidoille?

Azure Maps, palvelu, jota käytit viime oppitunnissa GPS-tietojen visualisointiin, mahdollistaa geoaidan määrittämisen ja pisteen testaamisen geoaidan suhteen.

## Geoaidan määrittäminen

Geoaidat määritellään GeoJSON-muodossa, kuten edellisessä oppitunnissa kartalle lisätyt pisteet. Tässä tapauksessa kyseessä ei ole `FeatureCollection`, joka sisältää `Point`-arvoja, vaan `FeatureCollection`, joka sisältää `Polygon`.

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

Jokainen monikulmion piste määritellään pituus- ja leveysasteparina taulukossa, ja nämä pisteet ovat taulukossa, joka asetetaan `coordinates`-elementiksi. Edellisessä oppitunnissa `Point`-elementin `coordinates` oli taulukko, joka sisälsi kaksi arvoa, leveys- ja pituusasteen. `Polygon`-elementissä se on taulukko taulukoita, jotka sisältävät kaksi arvoa, pituus- ja leveysasteen.

> 💁 Muista, että GeoJSON käyttää pisteille `pituus, leveys`, ei `leveys, pituus`.

Monikulmion koordinaattitaulukossa on aina yksi merkintä enemmän kuin monikulmion pisteiden lukumäärä, ja viimeinen merkintä on sama kuin ensimmäinen, sulkien monikulmion. Esimerkiksi suorakulmiossa olisi viisi pistettä.

![Suorakulmio koordinaatteineen](../../../../../translated_images/polygon-points.302193da381cb415.fi.png)

Yllä olevassa kuvassa on suorakulmio. Monikulmion koordinaatit alkavat vasemmasta yläkulmasta kohdasta 47,-122, sitten siirtyvät oikealle kohtaan 47,-121, sitten alas kohtaan 46,-121, sitten vasemmalle kohtaan 46,-122 ja lopuksi takaisin alkuun kohtaan 47,-122. Tämä antaa monikulmiolle viisi pistettä – vasen yläkulma, oikea yläkulma, oikea alakulma, vasen alakulma ja vasen yläkulma sulkemaan sen.

✅ Kokeile luoda GeoJSON-monikulmio kotisi tai koulusi ympärille. Käytä työkalua, kuten [GeoJSON.io](https://geojson.io/).

### Tehtävä – geoaidan määrittäminen

Jotta geoaidan voi käyttää Azure Mapsissa, se täytyy ensin ladata Azure Maps -tilillesi. Kun se on ladattu, saat yksilöllisen tunnuksen, jota voit käyttää pisteen testaamiseen geoaidan suhteen. Geoaidat ladataan Azure Mapsiin käyttämällä karttojen verkkosovellusliittymää. Voit kutsua Azure Mapsin verkkosovellusliittymää työkalulla nimeltä [curl](https://curl.se).

> 🎓 Curl on komentorivityökalu, jolla voi tehdä pyyntöjä verkkopäätepisteisiin.

1. Jos käytät Linuxia, macOS:ia tai Windows 10:n uudempaa versiota, curl on todennäköisesti jo asennettu. Suorita seuraava komento terminaalissasi tai komentorivillä tarkistaaksesi:

    ```sh
    curl --version
    ```

    Jos curl-versiotietoja ei näy, sinun täytyy asentaa se [curl-lataussivulta](https://curl.se/download.html).

    > 💁 Jos olet kokenut Postmanin käyttäjä, voit käyttää sitä vaihtoehtoisesti.

1. Luo GeoJSON-tiedosto, joka sisältää monikulmion. Testaat tätä GPS-anturin avulla, joten luo monikulmio nykyisen sijaintisi ympärille. Voit joko luoda sen manuaalisesti muokkaamalla yllä annettua GeoJSON-esimerkkiä tai käyttää työkalua, kuten [GeoJSON.io](https://geojson.io).

    GeoJSON-tiedoston täytyy sisältää `FeatureCollection`, joka sisältää `Feature`-elementin, jonka `geometry`-tyyppi on `Polygon`.

    Sinun **TÄYTYY** myös lisätä `properties`-elementti samalle tasolle kuin `geometry`-elementti, ja sen täytyy sisältää `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Jos käytät [GeoJSON.io](https://geojson.io), sinun täytyy manuaalisesti lisätä tämä elementti tyhjään `properties`-elementtiin joko ladattuasi JSON-tiedoston tai sovelluksen JSON-editorissa.

    Tämä `geometryId` täytyy olla yksilöllinen tässä tiedostossa. Voit ladata useita geoaidat useina `Feature`-elementteinä `FeatureCollection`-elementissä samassa GeoJSON-tiedostossa, kunhan jokaisella on eri `geometryId`. Monikulmioilla voi olla sama `geometryId`, jos ne ladataan eri tiedostosta eri aikaan.

1. Tallenna tämä tiedosto nimellä `geofence.json` ja siirry sen tallennuspaikkaan terminaalissasi tai konsolissasi.

1. Suorita seuraava curl-komento luodaksesi geoaidan:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Korvaa `<subscription_key>` URL-osoitteessa Azure Maps -tilisi API-avaimella.

    URL-osoitetta käytetään karttatietojen lataamiseen `https://atlas.microsoft.com/mapData/upload`-sovellusliittymän kautta. Kutsussa on mukana `api-version`-parametri, joka määrittää, mitä Azure Maps -sovellusliittymää käytetään. Tämä mahdollistaa sovellusliittymän muuttumisen ajan myötä säilyttäen taaksepäin yhteensopivuuden. Ladattavan datan muoto on asetettu `geojson`.

    Tämä suorittaa POST-pyynnön lataussovellusliittymään ja palauttaa vastausotsikoiden listan, joka sisältää otsikon nimeltä `location`.

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

    > 🎓 Kun kutsut verkkopäätepistettä, voit välittää parametreja kutsuun lisäämällä `?` ja sen jälkeen avain-arvoparit muodossa `avain=arvo`, erottaen avain-arvoparit `&`-merkillä.

1. Azure Maps ei käsittele tätä välittömästi, joten sinun täytyy tarkistaa, onko latauspyyntö valmis käyttämällä `location`-otsikossa annettua URL-osoitetta. Tee GET-pyyntö tähän sijaintiin nähdäksesi tilan. Sinun täytyy lisätä tilausavaimesi `location`-URL-osoitteen loppuun lisäämällä `&subscription-key=<subscription_key>` URL-osoitteen loppuun, korvaten `<subscription_key>` Azure Maps -tilisi API-avaimella. Suorita seuraava komento:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Korvaa `<location>` `location`-otsikon arvolla ja `<subscription_key>` Azure Maps -tilisi API-avaimella.

1. Tarkista vastauksen `status`-arvo. Jos se ei ole `Succeeded`, odota minuutti ja yritä uudelleen.

1. Kun tila palautuu arvolla `Succeeded`, katso vastauksen `resourceLocation`. Tämä sisältää yksityiskohdat GeoJSON-objektin yksilöllisestä tunnuksesta (tunnetaan nimellä UDID). UDID on arvo `metadata/`-kohdan jälkeen, mutta ei sisällä `api-version`-kohtaa. Esimerkiksi, jos `resourceLocation` oli:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    UDID olisi `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Pidä kopio tästä UDID:stä, sillä tarvitset sitä geoaidan testaamiseen.

## Pisteiden testaaminen geoaidan suhteen

Kun monikulmio on ladattu Azure Mapsiin, voit testata pisteen nähdäksesi, onko se geoaidan sisä- vai ulkopuolella. Tämä tehdään tekemällä verkkosovellusliittymäpyyntö, jossa välitetään geoaidan UDID sekä testattavan pisteen leveys- ja pituusaste.

Kun teet tämän pyynnön, voit myös välittää arvon nimeltä `searchBuffer`. Tämä kertoo Maps-sovellusliittymälle, kuinka tarkka sen tulisi olla tuloksia palauttaessaan. Syynä tähän on, että GPS ei ole täysin tarkka, ja joskus sijainnit voivat olla metrejä tai enemmän pielessä. Oletusarvo hakupuskurille on 50 m, mutta voit asettaa arvot 0 m:stä 500 m:iin.

Kun tulokset palautetaan sovellusliittymäpyynnöstä, yksi tuloksen osista on `distance`, joka mitataan lähimpään pisteeseen geoaidan reunalla. Positiivinen arvo tarkoittaa, että piste on geoaidan ulkopuolella, negatiivinen arvo tarkoittaa, että se on geoaidan sisällä. Jos tämä etäisyys on pienempi kuin hakupuskuri, todellinen etäisyys palautetaan metreinä, muuten arvo on 999 tai -999. 999 tarkoittaa, että piste on geoaidan ulkopuolella enemmän kuin hakupuskuri, -999 tarkoittaa, että se on geoaidan sisällä enemmän kuin hakupuskuri.

![Geoaidan ympärillä 50 m hakupuskuri](../../../../../translated_images/search-buffer-and-distance.e6a79af3898183c7.fi.png)

Yllä olevassa kuvassa geoaidalla on 50 m hakupuskuri.

* Piste geoaidan keskellä, hyvin hakupuskurin sisällä, on etäisyydellä **-999**
* Piste hyvin hakupuskurin ulkopuolella on etäisyydellä **999**
* Piste geoaidan sisällä ja hakupuskurin sisällä, 6 m päässä geoaidasta, on etäisyydellä **6 m**
* Piste geoaidan ulkopuolella ja hakupuskurin sisällä, 39 m päässä geoaidasta, on etäisyydellä **39 m**

On tärkeää tietää etäisyys geoaidan reunaan ja yhdistää tämä tieto muihin tietoihin, kuten muihin GPS-lukemiin, nopeuteen ja tiekarttatietoihin, kun tehdään päätöksiä ajoneuvon sijainnin perusteella.

Esimerkiksi, kuvittele GPS-lukemia, jotka osoittavat ajoneuvon ajavan tietä pitkin, joka kulkee geoaidan vieressä. Jos yksi GPS-arvo on epätarkka ja sijoittaa ajoneuvon geoaidan sisälle, vaikka sinne ei ole ajoneuvoyhteyttä, se voidaan jättää huomiotta.

![GPS-jälki, joka näyttää ajoneuvon kulkevan Microsoftin kampuksen ohi 520-tietä pitkin, GPS-lukemat tien varrella paitsi yksi kampuksella, geoaidan sisällä](../../../../../translated_images/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.fi.png)
Yllä olevassa kuvassa on geofence Microsoftin kampuksen osan päällä. Punainen viiva näyttää rekan ajavan pitkin 520-tietä, ja ympyrät osoittavat GPS-lukemat. Suurin osa näistä lukemista on tarkkoja ja sijaitsee 520-tien varrella, mutta yksi epätarkka lukema on geofencen sisällä. Tämä lukema ei voi olla oikea – ei ole teitä, joiden kautta rekka voisi yhtäkkiä poiketa 520-tieltä kampukselle ja palata sitten takaisin 520-tielle. Geofencen tarkistava koodi tarvitsee ottaa huomioon aiemmat lukemat ennen kuin se toimii geofencen testitulosten perusteella.

✅ Mitä lisätietoja tarvitsisit tarkistaaksesi, voiko GPS-lukema olla oikea?

### Tehtävä - testaa pisteitä geofenceä vastaan

1. Aloita rakentamalla URL web-API-kyselyä varten. Muoto on:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Korvaa `<subscription_key>` Azure Maps -tilisi API-avaimella.

    Korvaa `<UDID>` geofencen UDID:llä edellisestä tehtävästä.

    Korvaa `<lat>` ja `<lon>` testattavalla leveys- ja pituusasteella.

    Tämä URL käyttää `https://atlas.microsoft.com/spatial/geofence/json` API:a kysyäkseen GeoJSON:lla määriteltyä geofenceä. Se kohdistuu `1.0` API-versioon. `deviceId`-parametri on pakollinen ja sen tulee olla laitteen nimi, josta leveys- ja pituusaste tulevat.

    Oletushakupuskuri on 50 m, ja voit muuttaa tätä lisäämällä lisäparametrin `searchBuffer=<distance>`, jossa `<distance>` on hakupuskurin etäisyys metreinä, välillä 0–500.

1. Käytä curlia tehdäksesi GET-pyynnön tähän URL:iin:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Jos saat vastauskoodin `BadRequest` ja virheen:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > GeoJSON-tiedostostasi puuttuu `properties`-osio, jossa on `geometryId`. Sinun täytyy korjata GeoJSON-tiedostosi ja toistaa yllä olevat vaiheet uudelleen lataamiseksi ja uuden UDID:n saamiseksi.

1. Vastaus sisältää listan `geometries`, yhden jokaiselle GeoJSON:lla määritetylle polygonille, joita käytettiin geofencen luomiseen. Jokaisella geometrialla on kolme kiinnostavaa kenttää: `distance`, `nearestLat` ja `nearestLon`.

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

    * `nearestLat` ja `nearestLon` ovat geofencen reunalla olevan pisteen leveys- ja pituusaste, joka on lähimpänä testattavaa sijaintia.

    * `distance` on etäisyys testattavasta sijainnista lähimpään pisteeseen geofencen reunalla. Negatiiviset arvot tarkoittavat geofencen sisällä, positiiviset ulkopuolella. Tämä arvo on alle 50 (oletushakupuskuri) tai 999.

1. Toista tämä useita kertoja sijainneilla geofencen sisällä ja ulkopuolella.

## Käytä geofencejä serverittömästä koodista

Voit nyt lisätä uuden triggerin Functions-sovellukseesi testataksesi IoT Hubin GPS-tapahtumatietoja geofenceä vastaan.

### Kuluttajaryhmät

Kuten muistat aiemmista oppitunneista, IoT Hub mahdollistaa tapahtumien uudelleen toistamisen, jotka on vastaanotettu hubissa mutta joita ei ole käsitelty. Mutta mitä tapahtuu, jos useita triggereitä yhdistetään? Miten se tietää, mikä niistä on käsitellyt mitkä tapahtumat?

Vastaus on, että se ei tiedä! Sen sijaan voit määritellä useita erillisiä yhteyksiä tapahtumien lukemiseen, ja jokainen niistä voi hallita lukemattomien viestien uudelleen toistoa. Näitä kutsutaan *kuluttajaryhmiksi*. Kun yhdistät päätepisteeseen, voit määrittää, mihin kuluttajaryhmään haluat yhdistää. Sovelluksesi jokainen komponentti yhdistyy eri kuluttajaryhmään.

![Yksi IoT Hub, jossa 3 kuluttajaryhmää jakaa samat viestit 3 eri Functions-sovellukseen](../../../../../translated_images/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.fi.png)

Teoriassa jopa 5 sovellusta voi yhdistyä jokaiseen kuluttajaryhmään, ja ne kaikki vastaanottavat viestejä niiden saapuessa. Paras käytäntö on, että vain yksi sovellus käyttää kutakin kuluttajaryhmää välttääkseen viestien kaksoiskäsittelyn ja varmistaakseen, että kaikki jonossa olevat viestit käsitellään oikein uudelleenkäynnistyksen yhteydessä. Esimerkiksi, jos käynnistäisit Functions-sovelluksesi paikallisesti sekä pilvessä, ne molemmat käsittelisivät viestejä, mikä johtaisi kaksoiskopioihin tallennustilin blob-tallennuksessa.

Jos tarkastelet IoT Hub -triggerin `function.json`-tiedostoa, jonka loit aiemmassa oppitunnissa, näet kuluttajaryhmän tapahtumahub-triggerin sitomisosiossa:

```json
"consumerGroup": "$Default"
```

Kun luot IoT Hubin, saat `$Default`-kuluttajaryhmän oletuksena. Jos haluat lisätä uuden triggerin, voit lisätä sen käyttämällä uutta kuluttajaryhmää.

> 💁 Tässä oppitunnissa käytät eri funktiota geofencen testaamiseen kuin GPS-tietojen tallentamiseen. Tämä on tarkoitettu näyttämään, miten kuluttajaryhmiä käytetään ja koodin erottaminen helpottamaan lukemista ja ymmärtämistä. Tuotantosovelluksessa on monia tapoja, joilla voit suunnitella tämän – laittamalla molemmat yhteen funktioon, käyttämällä triggeriä tallennustilillä funktiota geofencen tarkistamiseen tai käyttämällä useita funktioita. Ei ole yhtä "oikeaa tapaa", vaan se riippuu sovelluksesi muusta rakenteesta ja tarpeistasi.

### Tehtävä - luo uusi kuluttajaryhmä

1. Suorita seuraava komento luodaksesi uuden kuluttajaryhmän nimeltä `geofence` IoT Hubillesi:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Korvaa `<hub_name>` IoT Hubin nimellä, jota käytit.

1. Jos haluat nähdä kaikki kuluttajaryhmät IoT Hubille, suorita seuraava komento:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Korvaa `<hub_name>` IoT Hubin nimellä, jota käytit. Tämä listaa kaikki kuluttajaryhmät.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Kun suoritat IoT Hub -tapahtumamonitorin aiemmassa oppitunnissa, se yhdistyi `$Default`-kuluttajaryhmään. Tämän vuoksi et voi suorittaa tapahtumamonitoria ja tapahtumatriggeriä samanaikaisesti. Jos haluat suorittaa molemmat, voit käyttää muita kuluttajaryhmiä kaikille Functions-sovelluksillesi ja pitää `$Default` tapahtumamonitorille.

### Tehtävä - luo uusi IoT Hub -triggeri

1. Lisää uusi IoT Hub -tapahtumatriggeri `gps-trigger`-Functions-sovellukseen, jonka loit aiemmassa oppitunnissa. Nimeä tämä funktio `geofence-trigger`.

    > ⚠️ Voit viitata [ohjeisiin IoT Hub -tapahtumatriggerin luomisesta projektista 2, oppitunti 5 tarvittaessa](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Määritä IoT Hub -yhteysmerkkijono `function.json`-tiedostossa. `local.settings.json` jaetaan kaikkien Functions-sovelluksen triggerien kesken.

1. Päivitä `function.json`-tiedoston `consumerGroup`-arvo viittaamaan uuteen `geofence`-kuluttajaryhmään:

    ```json
    "consumerGroup": "geofence"
    ```

1. Tarvitset Azure Maps -tilisi tilausavaimen tässä triggerissä, joten lisää uusi merkintä `local.settings.json`-tiedostoon nimeltä `MAPS_KEY`.

1. Suorita Functions-sovellus varmistaaksesi, että se yhdistyy ja käsittelee viestejä. Aiemman oppitunnin `iot-hub-trigger` suoritetaan myös ja lataa blobit tallennukseen.

    > Välttääksesi GPS-lukemien kaksoiskappaleet blob-tallennuksessa, voit pysäyttää pilvessä toimivan Functions-sovelluksen. Voit tehdä tämän seuraavalla komennolla:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Korvaa `<functions_app_name>` Functions-sovelluksen nimellä, jota käytit.
    >
    > Voit käynnistää sen uudelleen seuraavalla komennolla:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Korvaa `<functions_app_name>` Functions-sovelluksen nimellä, jota käytit.

### Tehtävä - testaa geofenceä triggeristä

Aiemmin tässä oppitunnissa käytit curlia kysyäksesi geofenceä nähdäksesi, sijaitseeko piste sisällä vai ulkona. Voit tehdä samanlaisen web-pyynnön triggerisi sisältä.

1. Geofencen kysymiseen tarvitset sen UDID:n. Lisää uusi merkintä `local.settings.json`-tiedostoon nimeltä `GEOFENCE_UDID` tämän arvon kanssa.

1. Avaa uuden `geofence-trigger`-triggerin `__init__.py`-tiedosto.

1. Lisää seuraava tuonti tiedoston alkuun:

    ```python
    import json
    import os
    import requests
    ```

    `requests`-paketti mahdollistaa web-API-kutsujen tekemisen. Azure Mapsilla ei ole Python SDK:ta, joten sinun täytyy tehdä web-API-kutsuja käyttääksesi sitä Python-koodista.

1. Lisää seuraavat 2 riviä `main`-metodin alkuun saadaksesi Maps-tilausavaimen:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Lisää `for event in events`-silmukan sisään seuraava koodi saadaksesi leveys- ja pituusasteen jokaisesta tapahtumasta:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Tämä koodi muuntaa tapahtuman rungon JSON-muodosta sanakirjaksi ja poimii `lat` ja `lon` `gps`-kentästä.

1. Kun käytät `requests`-kirjastoa, pitkän URL:n rakentamisen sijaan, kuten teit curlilla, voit käyttää vain URL-osaa ja välittää parametrit sanakirjana. Lisää seuraava koodi määrittääksesi kutsuttavan URL:n ja konfiguroidaksesi parametrit:

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

    `params`-sanakirjan kohteet vastaavat avain-arvopareja, joita käytit kutsuessasi web-API:a curlilla.

1. Lisää seuraavat koodirivit kutsuaksesi web-API:a:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Tämä kutsuu URL:ia parametreilla ja saa takaisin vastausobjektin.

1. Lisää tämän alle seuraava koodi:

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

    Tämä koodi olettaa yhden geometrian ja poimii etäisyyden tästä yksittäisestä geometriasta. Se sitten kirjaa eri viestejä etäisyyden perusteella.

1. Suorita tämä koodi. Näet lokitulosteessa, ovatko GPS-koordinaatit geofencen sisällä vai ulkopuolella, etäisyyden kanssa, jos piste on 50 metrin sisällä. Kokeile tätä koodia eri geofenceillä GPS-anturin sijainnin perusteella, kokeile siirtää anturia (esimerkiksi WiFi-yhteyden kautta mobiilipuhelimesta tai eri koordinaateilla virtuaalisessa IoT-laitteessa) nähdäksesi muutoksen.

1. Kun olet valmis, ota tämä koodi käyttöön Functions-sovelluksessasi pilvessä. Älä unohda ottaa käyttöön uusia sovellusasetuksia.

    > ⚠️ Voit viitata [ohjeisiin sovellusasetusten lataamisesta projektista 2, oppitunti 5 tarvittaessa](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Voit viitata [ohjeisiin Functions-sovelluksen käyttöönotosta projektista 2, oppitunti 5 tarvittaessa](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Löydät tämän koodin [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions) -kansiosta.

---

## 🚀 Haaste

Tässä oppitunnissa lisäsit yhden geofencen käyttämällä GeoJSON-tiedostoa, jossa on yksi polygoni. Voit ladata useita polygoneja samanaikaisesti, kunhan niillä on eri `geometryId`-arvot `properties`-osiossa.

Kokeile ladata GeoJSON-tiedosto, jossa on useita polygoneja, ja säädä koodiasi löytääksesi, mikä polygoni on lähimpänä GPS-koordinaatteja tai missä ne sijaitsevat.

## Oppitunnin jälkeinen kysely

[Oppitunnin jälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Kertaus ja itseopiskelu

* Lue lisää geofenceistä ja niiden käyttötapauksista [Geofencing-sivulta Wikipediassa](https://en.wikipedia.org/wiki/Geo-fence).
* Lue lisää Azure Maps geofencing API:sta [Microsoft Azure Maps Spatial - Get Geofence -dokumentaatiosta](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Lue lisää kuluttajaryhmistä [Azure Event Hubs -ominaisuudet ja terminologia - Event consumers -dokumentaatiosta Microsoft Docsissa](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Tehtävä

[Lähetä ilmoituksia Twilion avulla](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.