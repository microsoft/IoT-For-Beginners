<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-28T19:40:48+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "lt"
}
-->
# Geotvoros

![Šios pamokos apžvalga piešiniu](../../../../../translated_images/lt/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.jpg)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

Šiame vaizdo įraše pateikiama geotvorų apžvalga ir kaip jas naudoti Azure Maps. Tai temos, kurios bus aptartos šioje pamokoje:

[![Geotvoros su Azure Maps iš Microsoft Developer IoT laidos](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Spustelėkite aukščiau esantį paveikslėlį, kad peržiūrėtumėte vaizdo įrašą

## Klausimynas prieš paskaitą

[Klausimynas prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Įvadas

Per paskutines tris pamokas naudojote IoT technologijas, kad nustatytumėte sunkvežimių, gabenančių jūsų produkciją iš ūkio į perdirbimo centrą, buvimo vietą. Jūs rinkote GPS duomenis, siuntėte juos į debesį saugojimui ir vizualizavote juos žemėlapyje. Kitas žingsnis, siekiant padidinti tiekimo grandinės efektyvumą, yra gauti pranešimą, kai sunkvežimis artėja prie perdirbimo centro, kad darbuotojai būtų pasiruošę iškrauti naudodami krautuvus ir kitą įrangą vos tik transporto priemonė atvyks. Tokiu būdu iškrovimas vyksta greičiau, ir jums nereikia mokėti už sunkvežimio ir vairuotojo laukimą.

Šioje pamokoje sužinosite apie geotvoras – apibrėžtas geografinio ploto ribas, tokias kaip 2 km spindulio zona aplink perdirbimo centrą, ir kaip patikrinti, ar GPS koordinatės yra geotvoroje ar už jos ribų, kad galėtumėte nustatyti, ar jūsų GPS jutiklis atvyko į tam tikrą vietą ar ją paliko.

Šioje pamokoje aptarsime:

* [Kas yra geotvoros](../../../../../3-transport/lessons/4-geofences)
* [Kaip apibrėžti geotvorą](../../../../../3-transport/lessons/4-geofences)
* [Kaip patikrinti taškus geotvoroje](../../../../../3-transport/lessons/4-geofences)
* [Kaip naudoti geotvoras serverless kode](../../../../../3-transport/lessons/4-geofences)

> 🗑 Tai paskutinė šio projekto pamoka, todėl baigę šią pamoką ir užduotį nepamirškite išvalyti savo debesų paslaugų. Jums reikės šių paslaugų užduočiai atlikti, todėl pirmiausia įsitikinkite, kad ją užbaigėte.
>
> Jei reikia, vadovaukitės [projekto išvalymo vadovu](../../../clean-up.md), kad gautumėte instrukcijas, kaip tai padaryti.

## Kas yra geotvoros

Geotvora yra virtuali realaus pasaulio geografinio regiono perimetro riba. Geotvoros gali būti apskritimai, apibrėžti kaip taškas ir spindulys (pavyzdžiui, 100 m pločio apskritimas aplink pastatą), arba daugiakampiai, apimantys tokias zonas kaip mokyklos teritorija, miesto ribos ar universiteto ar biuro kompleksas.

![Geotvorų pavyzdžiai, rodantys apskritiminę geotvorą aplink Microsoft parduotuvę ir daugiakampę geotvorą aplink Microsoft vakarų kampusą](../../../../../translated_images/lt/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.png)

> 💁 Galbūt jau naudojote geotvoras, to nežinodami. Jei naudojote iOS priminimų programėlę ar Google Keep, kad nustatytumėte priminimą pagal vietą, jūs naudojote geotvorą. Šios programėlės nustato geotvorą pagal nurodytą vietą ir praneša, kai jūsų telefonas patenka į geotvorą.

Yra daug priežasčių, kodėl norėtumėte žinoti, ar transporto priemonė yra geotvoroje ar už jos ribų:

* Iškrovimo pasiruošimas – gavus pranešimą, kad transporto priemonė atvyko į vietą, komanda gali pasiruošti ją iškrauti, taip sumažinant laukimo laiką. Tai leidžia vairuotojui atlikti daugiau pristatymų per dieną su mažesniu laukimo laiku.
* Mokesčių atitikimas – kai kurios šalys, tokios kaip Naujoji Zelandija, taiko kelių mokesčius dyzeliniams automobiliams pagal jų svorį, kai jie važiuoja tik viešaisiais keliais. Naudojant geotvoras galima stebėti, kiek kilometrų nuvažiuota viešaisiais keliais, o kiek privačiais, pavyzdžiui, ūkio ar miško teritorijose.
* Vagysčių stebėjimas – jei transporto priemonė turėtų likti tam tikroje teritorijoje, pavyzdžiui, ūkyje, ir ji palieka geotvorą, tai gali reikšti, kad ji buvo pavogta.
* Vietos atitikimas – kai kurios darbo vietos, ūkio ar gamyklos dalys gali būti uždraustos tam tikroms transporto priemonėms, pavyzdžiui, neleisti transporto priemonėms, vežančioms dirbtines trąšas ir pesticidus, patekti į laukus, kuriuose auginama ekologiška produkcija. Jei geotvora yra pažeista, transporto priemonė yra už atitikties ribų, ir vairuotojas gali būti apie tai informuotas.

✅ Ar galite sugalvoti kitų geotvorų naudojimo būdų?

Azure Maps, paslauga, kurią naudojote ankstesnėje pamokoje GPS duomenims vizualizuoti, leidžia apibrėžti geotvoras ir patikrinti, ar taškas yra geotvoroje ar už jos ribų.

## Kaip apibrėžti geotvorą

Geotvoros apibrėžiamos naudojant GeoJSON, taip pat kaip ir taškai, kurie buvo pridėti prie žemėlapio ankstesnėje pamokoje. Šiuo atveju, vietoj `FeatureCollection` su `Point` reikšmėmis, tai yra `FeatureCollection`, kuriame yra `Polygon`.

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

Kiekvienas daugiakampio taškas apibrėžiamas kaip ilgumos ir platumos pora masyve, o šie taškai yra masyve, kuris nustatomas kaip `coordinates`. Ankstesnėje pamokoje `Point` turėjo `coordinates` masyvą su 2 reikšmėmis – platuma ir ilguma, o `Polygon` turi masyvą masyvų, kuriuose yra 2 reikšmės – ilguma ir platuma.

> 💁 Atminkite, GeoJSON naudoja `ilguma, platuma` taškams, o ne `platuma, ilguma`.

Daugiakampio koordinatės masyvas visada turi 1 įrašą daugiau nei daugiakampio taškų skaičius, nes paskutinis įrašas yra toks pat kaip pirmasis, uždarant daugiakampį. Pavyzdžiui, stačiakampiui būtų 5 taškai.

![Stačiakampis su koordinatėmis](../../../../../translated_images/lt/polygon-points.302193da381cb415.webp)

Aukščiau esančiame paveikslėlyje yra stačiakampis. Daugiakampio koordinatės prasideda viršutiniame kairiajame kampe 47,-122, tada juda į dešinę iki 47,-121, tada žemyn iki 46,-121, tada į kairę iki 46,-122, tada grįžta į pradinį tašką 47,-122. Tai suteikia daugiakampiui 5 taškus – viršutinis kairysis, viršutinis dešinysis, apatinis dešinysis, apatinis kairysis ir viršutinis kairysis, kad uždarytų daugiakampį.

✅ Pabandykite sukurti GeoJSON daugiakampį aplink savo namus ar mokyklą. Naudokite tokią priemonę kaip [GeoJSON.io](https://geojson.io/).

### Užduotis – apibrėžkite geotvorą

Norint naudoti geotvorą Azure Maps, pirmiausia ją reikia įkelti į jūsų Azure Maps paskyrą. Kai ji bus įkelta, gausite unikalų ID, kurį galėsite naudoti taškui patikrinti geotvoroje. Norėdami įkelti geotvoras į Azure Maps, turite naudoti žemėlapių žiniatinklio API. Galite naudoti įrankį, pavyzdžiui, [curl](https://curl.se), kad iškviestumėte Azure Maps žiniatinklio API.

> 🎓 Curl yra komandų eilutės įrankis, skirtas užklausoms į žiniatinklio galinius taškus atlikti.

1. Jei naudojate Linux, macOS arba naujesnę Windows 10 versiją, tikriausiai jau turite įdiegtą curl. Paleiskite šią komandą savo terminale arba komandų eilutėje, kad patikrintumėte:

    ```sh
    curl --version
    ```

    Jei nematote curl versijos informacijos, turėsite ją įdiegti iš [curl atsisiuntimų puslapio](https://curl.se/download.html).

    > 💁 Jei esate patyręs Postman naudotojas, galite naudoti jį vietoj curl, jei norite.

1. Sukurkite GeoJSON failą, kuriame yra daugiakampis. Jūs testuosite tai naudodami savo GPS jutiklį, todėl sukurkite daugiakampį aplink savo dabartinę vietą. Galite sukurti jį rankiniu būdu, redaguodami aukščiau pateiktą GeoJSON pavyzdį, arba naudodami tokią priemonę kaip [GeoJSON.io](https://geojson.io/).

    GeoJSON turi turėti `FeatureCollection`, kuriame yra `Feature` su `geometry` tipo `Polygon`.

    Taip pat **PRIVALOTE** pridėti `properties` elementą tame pačiame lygyje kaip `geometry` elementas, ir jis turi turėti `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Jei naudojate [GeoJSON.io](https://geojson.io/), turėsite rankiniu būdu pridėti šį elementą prie tuščio `properties` elemento, arba atsisiuntę JSON failą, arba JSON redaktoriuje programėlėje.

    Šis `geometryId` turi būti unikalus šiame faile. Galite įkelti kelias geotvoras kaip kelis `Features` `FeatureCollection` faile, jei kiekviena turi skirtingą `geometryId`. Daugiakampiai gali turėti tą patį `geometryId`, jei jie įkeliami iš skirtingų failų skirtingu laiku.

1. Išsaugokite šį failą kaip `geofence.json` ir terminale arba konsolėje pereikite į vietą, kur jis išsaugotas.

1. Paleiskite šią curl komandą, kad sukurtumėte geotvorą:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Pakeiskite `<subscription_key>` URL adresu savo Azure Maps paskyros API raktu.

    URL naudojamas žemėlapių duomenims įkelti per `https://atlas.microsoft.com/mapData/upload` API. Užklausa apima `api-version` parametrą, nurodantį, kurią Azure Maps API versiją naudoti. Tai leidžia API keistis laikui bėgant, išlaikant atgalinį suderinamumą. Įkeliami duomenys nustatomi kaip `geojson`.

    Tai atliks POST užklausą į įkėlimo API ir grąžins atsakymo antraščių sąrašą, įskaitant antraštę `location`.

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

    > 🎓 Kai kviečiate žiniatinklio galinį tašką, galite perduoti parametrus užklausai, pridėdami `?`, po kurio eina raktų ir reikšmių poros kaip `raktas=reikšmė`, atskiriant poras `&`.

1. Azure Maps neapdoroja šios užklausos iš karto, todėl turėsite patikrinti, ar įkėlimo užklausa baigta, naudodami URL, pateiktą `location` antraštėje. Atlikite GET užklausą šiuo adresu, kad pamatytumėte būseną. Turėsite pridėti savo prenumeratos raktą prie `location` URL pabaigos, pridėdami `&subscription-key=<subscription_key>`, pakeisdami `<subscription_key>` savo Azure Maps paskyros API raktu. Paleiskite šią komandą:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Pakeiskite `<location>` `location` antraštės reikšme ir `<subscription_key>` savo Azure Maps paskyros API raktu.

1. Patikrinkite atsakymo `status` reikšmę. Jei ji nėra `Succeeded`, palaukite minutę ir bandykite dar kartą.

1. Kai būsena bus `Succeeded`, peržiūrėkite atsakymo `resourceLocation`. Jame yra informacija apie unikalų ID (vadinamą UDID) GeoJSON objektui. UDID yra reikšmė po `metadata/`, neįskaitant `api-version`. Pavyzdžiui, jei `resourceLocation` buvo:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Tada UDID būtų `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Išsaugokite šį UDID, nes jums jo prireiks geotvorai testuoti.

## Kaip patikrinti taškus geotvoroje

Kai daugiakampis įkeltas į Azure Maps, galite patikrinti tašką, ar jis yra geotvoroje, ar už jos ribų. Tai atliekama naudojant žiniatinklio API užklausą, perduodant geotvoros UDID ir taško platumą bei ilgumą.

Kai atliekate šią užklausą, taip pat galite perduoti reikšmę, vadinamą `searchBuffer`. Ji nurodo Maps API, kokio tikslumo reikia grąžinant rezultatus. Taip yra todėl, kad GPS nėra visiškai tikslus, ir kartais vietos gali būti netikslios keliais metrais ar daugiau. Numatytoji `searchBuffer` reikšmė yra 50 m, tačiau galite nustatyti reikšmes nuo 0 m iki 500 m.

Kai API užklausa grąžina rezultatus, viena iš rezultatų dalių yra `distance`, matuojamas iki artimiausio taško geotvoros krašte. Jei taškas yra už geotvoros, reikšmė bus teigiama, jei viduje – neigiama. Jei ši reikšmė yra mažesnė už `searchBuffer`, grąžinama tikroji reikšmė metrais, kitaip reikšmė bus 999 arba -999. 999 reiškia, kad taškas yra už geotvoros daugiau nei `searchBuffer`, -999 reiškia, kad jis yra geotvoroje daugiau nei `searchBuffer`.

![Geotvora su 50 m paieškos buferiu](../../../../../translated_images/lt/search-buffer-and-distance.e6a79af3898183c7.webp)

Aukščiau esančiame paveikslėlyje geotvora turi 50 m paieškos buferį.

* Taškas geotvoros centre, gerokai viduje paieškos buferio, turi atstumą **-999**
* Taškas gerokai už paieškos buferio ribų turi atstumą **999**
* Taškas geotvoroje ir paieškos buferyje, 6 m nuo geotvoros, turi atstumą **6 m**
* Taškas už geotvoros ir paieškos buferyje, 39 m nuo geotvoros, turi atstumą **39 m**

Svarbu žinoti atstumą iki geotvoros krašto ir derinti šią informaciją su kitais duomenimis, tokiais kaip kiti GPS rodmenys, greitis ir kelių duomenys, priimant sprendimus pagal transporto priemonės buvimo vietą.

Pavyzdžiui, įsivaizduokite GPS rodmenis, rodančius, kad transporto priemonė važiuoja keliu, kuris eina šalia geotvoros. Jei vienas GPS rodmuo yra netikslus ir rodo, kad transporto priemonė yra geotvoroje, nors ten nėra jokio kelio, šį rodmenį galima ignoruoti.

![GPS trajektorija, rodanti transporto priemonę, važiuojančią šalia Microsoft kampuso 520 keliu, su GPS rodmenimis palei kelią, išskyrus vieną kampuso viduje, geotvoroje](../../../images/geofence-crossing-inaccur
Aukščiau pateiktame paveikslėlyje matoma geotvora, apimanti dalį „Microsoft“ miestelio. Raudona linija rodo sunkvežimį, važiuojantį 520 keliu, o apskritimai žymi GPS nuskaitymus. Dauguma jų yra tikslūs ir atitinka 520 kelią, tačiau vienas netikslus nuskaitymas yra geotvoros viduje. Akivaizdu, kad šis nuskaitymas negali būti teisingas – nėra kelių, kuriais sunkvežimis galėtų staiga nukrypti nuo 520 kelio į miestelį ir vėl grįžti į 520 kelią. Kodas, tikrinantis šią geotvorą, turės atsižvelgti į ankstesnius nuskaitymus prieš priimdamas sprendimus pagal geotvoros testo rezultatus.

✅ Kokius papildomus duomenis reikėtų patikrinti, kad nustatytumėte, ar GPS nuskaitymas gali būti laikomas teisingu?

### Užduotis – testuoti taškus pagal geotvorą

1. Pradėkite nuo URL kūrimo žiniatinklio API užklausai. Formatą rasite čia:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Pakeiskite `<subscription_key>` savo „Azure Maps“ paskyros API raktu.

    Pakeiskite `<UDID>` geotvoros UDID, gautu iš ankstesnės užduoties.

    Pakeiskite `<lat>` ir `<lon>` norima patikrinti platuma ir ilguma.

    Šis URL naudoja `https://atlas.microsoft.com/spatial/geofence/json` API, kad užklaustų geotvorą, apibrėžtą naudojant GeoJSON. Jis naudoja `1.0` API versiją. Parametras `deviceId` yra privalomas ir turėtų būti įrenginio, iš kurio gaunami platumos ir ilgumos duomenys, pavadinimas.

    Numatytasis paieškos buferis yra 50 m, tačiau jį galite pakeisti, pridėdami papildomą parametrą `searchBuffer=<distance>`, kur `<distance>` yra paieškos buferio atstumas metrais (nuo 0 iki 500).

1. Naudokite `curl`, kad atliktumėte GET užklausą šiam URL:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Jei gaunate atsakymo kodą `BadRequest` su klaida:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > tuomet jūsų GeoJSON trūksta `properties` skyriaus su `geometryId`. Turėsite pataisyti savo GeoJSON, tada pakartoti aukščiau nurodytus veiksmus, kad iš naujo įkeltumėte ir gautumėte naują UDID.

1. Atsakyme bus pateiktas `geometries` sąrašas, kuriame yra kiekvienas GeoJSON apibrėžtas poligonas, naudojamas geotvorai sukurti. Kiekvienas poligonas turi 3 svarbius laukus: `distance`, `nearestLat` ir `nearestLon`.

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

    * `nearestLat` ir `nearestLon` yra geotvoros krašto taško, esančio arčiausiai tikrinamos vietos, platuma ir ilguma.

    * `distance` yra atstumas nuo tikrinamos vietos iki artimiausio geotvoros krašto taško. Neigiami skaičiai reiškia, kad taškas yra geotvoros viduje, o teigiami – išorėje. Ši reikšmė bus mažesnė nei 50 (numatytasis paieškos buferis) arba 999.

1. Pakartokite šį procesą kelis kartus su vietomis, esančiomis tiek geotvoros viduje, tiek išorėje.

## Naudokite geotvoras iš serverio be serverio kodo

Dabar galite pridėti naują trigerį prie savo „Functions“ programos, kad patikrintumėte IoT Hub GPS įvykių duomenis pagal geotvorą.

### Vartotojų grupės

Kaip prisimenate iš ankstesnių pamokų, IoT Hub leidžia atkurti įvykius, kurie buvo gauti, bet dar neapdoroti. Tačiau kas nutiktų, jei prisijungtų keli trigeriai? Kaip jis žinotų, kurie įvykiai jau buvo apdoroti?

Atsakymas – jis negali! Vietoj to galite apibrėžti kelis atskirus ryšius, kad skaitytumėte įvykius, ir kiekvienas iš jų gali valdyti neperskaitytų pranešimų atkūrimą. Tai vadinama *vartotojų grupėmis*. Kai prisijungiate prie galinio taško, galite nurodyti, prie kurios vartotojų grupės norite prisijungti. Kiekvienas jūsų programos komponentas prisijungs prie skirtingos vartotojų grupės.

![Vienas IoT Hub su 3 vartotojų grupėmis, paskirstančiomis tuos pačius pranešimus 3 skirtingoms funkcijų programoms](../../../../../translated_images/lt/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.png)

Teoriškai prie kiekvienos vartotojų grupės gali prisijungti iki 5 programų, ir jos visos gaus pranešimus, kai jie atvyks. Geriausia praktika yra leisti tik vienai programai pasiekti kiekvieną vartotojų grupę, kad būtų išvengta pranešimų dubliavimo ir užtikrinta, kad paleidus iš naujo visi eilėje esantys pranešimai būtų tinkamai apdoroti. Pavyzdžiui, jei paleistumėte savo „Functions“ programą vietoje ir debesyje vienu metu, abi apdorotų pranešimus, todėl saugykloje būtų saugomi dubliuoti blobai.

Jei peržiūrėsite `function.json` failą, susijusį su IoT Hub trigeriu, kurį sukūrėte ankstesnėje pamokoje, pamatysite vartotojų grupę įvykių centro trigerio susiejimo skyriuje:

```json
"consumerGroup": "$Default"
```

Kai sukuriate IoT Hub, pagal numatytuosius nustatymus sukuriama `$Default` vartotojų grupė. Jei norite pridėti papildomą trigerį, galite tai padaryti naudodami naują vartotojų grupę.

> 💁 Šioje pamokoje naudosite kitą funkciją geotvorai testuoti nei tą, kuri naudojama GPS duomenims saugoti. Tai parodo, kaip naudoti vartotojų grupes ir atskirti kodą, kad būtų lengviau jį skaityti ir suprasti. Produkcijos programoje yra daug būdų, kaip tai sukurti – abi funkcijas galima įdėti į vieną funkciją, naudoti trigerį saugyklos paskyroje, kad paleistumėte funkciją geotvorai tikrinti, arba naudoti kelias funkcijas. Nėra „teisingo būdo“, viskas priklauso nuo jūsų programos ir poreikių.

### Užduotis – sukurti naują vartotojų grupę

1. Paleiskite šią komandą, kad sukurtumėte naują vartotojų grupę, pavadintą `geofence`, savo IoT Hub:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Pakeiskite `<hub_name>` savo IoT Hub pavadinimu.

1. Jei norite pamatyti visas IoT Hub vartotojų grupes, paleiskite šią komandą:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Pakeiskite `<hub_name>` savo IoT Hub pavadinimu. Tai parodys visas vartotojų grupes.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Kai ankstesnėje pamokoje paleidote IoT Hub įvykių monitorių, jis prisijungė prie `$Default` vartotojų grupės. Dėl to negalėjote paleisti įvykių monitoriaus ir įvykių trigerio vienu metu. Jei norite paleisti abu, galite naudoti kitas vartotojų grupes visoms savo funkcijų programoms ir palikti `$Default` įvykių monitoriui.

### Užduotis – sukurti naują IoT Hub trigerį

1. Pridėkite naują IoT Hub įvykių trigerį prie savo `gps-trigger` funkcijų programos, kurią sukūrėte ankstesnėje pamokoje. Pavadinkite šią funkciją `geofence-trigger`.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip sukurti IoT Hub įvykių trigerį iš 2 projekto, 5 pamokos](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Sujunkite IoT Hub ryšio eilutę `function.json` faile. `local.settings.json` yra bendra visiems funkcijų programos trigeriams.

1. Atnaujinkite `consumerGroup` reikšmę `function.json` faile, kad ji nurodytų naują `geofence` vartotojų grupę:

    ```json
    "consumerGroup": "geofence"
    ```

1. Šiame trigerio faile jums reikės „Azure Maps“ paskyros prenumeratos rakto, todėl pridėkite naują įrašą į `local.settings.json` failą, pavadintą `MAPS_KEY`.

1. Paleiskite „Functions“ programą, kad įsitikintumėte, jog ji jungiasi ir apdoroja pranešimus. Ankstesnėje pamokoje sukurtas `iot-hub-trigger` taip pat veiks ir įkels blobus į saugyklą.

    > Kad išvengtumėte dubliuotų GPS nuskaitymų blobų saugykloje, galite sustabdyti debesyje veikiančią „Functions“ programą. Norėdami tai padaryti, naudokite šią komandą:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Pakeiskite `<functions_app_name>` savo „Functions“ programos pavadinimu.
    >
    > Vėliau galite ją paleisti iš naujo naudodami šią komandą:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Pakeiskite `<functions_app_name>` savo „Functions“ programos pavadinimu.

### Užduotis – testuoti geotvorą iš trigerio

Ankstesnėje pamokoje naudojote `curl`, kad užklaustumėte geotvorą ir nustatytumėte, ar taškas yra viduje, ar išorėje. Panašią užklausą galite atlikti iš savo trigerio.

1. Norėdami užklausti geotvorą, jums reikės jos UDID. Pridėkite naują įrašą į `local.settings.json` failą, pavadintą `GEOFENCE_UDID`, su šia reikšme.

1. Atidarykite `__init__.py` failą iš naujo `geofence-trigger` trigerio.

1. Pridėkite šį importą failo viršuje:

    ```python
    import json
    import os
    import requests
    ```

    `requests` paketas leidžia atlikti žiniatinklio API užklausas. „Azure Maps“ neturi Python SDK, todėl norėdami jį naudoti iš Python kodo, turite atlikti žiniatinklio API užklausas.

1. Pridėkite šias 2 eilutes į `main` metodo pradžią, kad gautumėte „Maps“ prenumeratos raktą:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Viduje `for event in events` ciklo pridėkite šį kodą, kad gautumėte platumą ir ilgumą iš kiekvieno įvykio:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Šis kodas konvertuoja JSON iš įvykio kūno į žodyną, tada ištraukia `lat` ir `lon` iš `gps` lauko.

1. Naudodami `requests`, vietoj ilgo URL kūrimo, kaip darėte su `curl`, galite naudoti tik URL dalį ir perduoti parametrus kaip žodyną. Pridėkite šį kodą, kad apibrėžtumėte kviečiamą URL ir sukonfigūruotumėte parametrus:

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

    Elementai `params` žodyne atitiks raktų ir reikšmių poras, kurias naudojote kviesdami žiniatinklio API per `curl`.

1. Pridėkite šias kodo eilutes, kad atliktumėte žiniatinklio API užklausą:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Tai kviečia URL su parametrais ir gauna atsakymo objektą.

1. Pridėkite šį kodą žemiau:

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

    Šis kodas daro prielaidą, kad yra 1 geometrija, ir ištraukia atstumą iš tos vienintelės geometrijos. Tada jis registruoja skirtingas žinutes, atsižvelgiant į atstumą.

1. Paleiskite šį kodą. Žurnalo išvestyje matysite, ar GPS koordinatės yra geotvoros viduje, ar išorėje, su atstumu, jei taškas yra 50 m ribose. Išbandykite šį kodą su skirtingomis geotvoromis, atsižvelgdami į savo GPS jutiklio vietą, pabandykite perkelti jutiklį (pvz., prijungtą prie mobiliojo telefono „WiFi“ arba su skirtingomis koordinatėmis virtualiame IoT įrenginyje), kad pamatytumėte pokyčius.

1. Kai būsite pasiruošę, įkelkite šį kodą į savo „Functions“ programą debesyje. Nepamirškite įkelti naujų programos nustatymų.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip įkelti programos nustatymus iš 2 projekto, 5 pamokos](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip įkelti savo „Functions“ programą iš 2 projekto, 5 pamokos](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Šį kodą galite rasti [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions) aplanke.

---

## 🚀 Iššūkis

Šioje pamokoje pridėjote vieną geotvorą naudodami GeoJSON failą su vienu poligonu. Galite įkelti kelis poligonus vienu metu, jei jie turi skirtingas `geometryId` reikšmes `properties` skyriuje.

Pabandykite įkelti GeoJSON failą su keliais poligonais ir pritaikykite savo kodą, kad nustatytumėte, kuris poligonas yra arčiausiai GPS koordinatės arba kuriame jis yra.

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Peržiūra ir savarankiškas mokymasis

* Skaitykite daugiau apie geotvoras ir jų naudojimo atvejus [Geotvorų puslapyje Vikipedijoje](https://en.wikipedia.org/wiki/Geo-fence).
* Skaitykite daugiau apie „Azure Maps“ geotvorų API [Microsoft Azure Maps Spatial - Get Geofence dokumentacijoje](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Skaitykite daugiau apie vartotojų grupes [„Azure Event Hubs“ funkcijų ir terminų dokumentacijoje](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Užduotis

[Siųsti pranešimus naudojant Twilio](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipkite dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.