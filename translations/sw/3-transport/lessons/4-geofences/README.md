<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-27T21:44:27+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "sw"
}
-->
# Geofences

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa zaidi.

Video hii inatoa muhtasari wa geofences na jinsi ya kuzitumia katika Azure Maps, mada zitakazojadiliwa katika somo hili:

[![Geofencing na Azure Maps kutoka kwa Microsoft Developer IoT show](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Bofya picha hapo juu kutazama video

## Maswali ya awali ya somo

[Maswali ya awali ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Utangulizi

Katika masomo matatu yaliyopita, umetumia IoT kufuatilia malori yanayobeba mazao yako kutoka shambani hadi kituo cha usindikaji. Umenasa data ya GPS, kuipeleka kwenye wingu kuhifadhi, na kuiona kwenye ramani. Hatua inayofuata ya kuongeza ufanisi wa mnyororo wako wa usambazaji ni kupata arifa wakati lori linakaribia kufika kituo cha usindikaji, ili wafanyakazi wanaohitajika kupakua wawe tayari na vifaa kama forklifts mara tu gari linapofika. Kwa njia hii wanaweza kupakua haraka, na hautalipa kwa lori na dereva kusubiri.

Katika somo hili utajifunza kuhusu geofences - maeneo maalum ya kijiografia kama eneo ndani ya umbali wa dakika 2km kutoka kituo cha usindikaji, na jinsi ya kujaribu kama viwianishi vya GPS viko ndani au nje ya geofence, ili kuona kama sensor yako ya GPS imefika au kuondoka eneo fulani.

Katika somo hili tutajadili:

* [Geofences ni nini](../../../../../3-transport/lessons/4-geofences)
* [Kufafanua geofence](../../../../../3-transport/lessons/4-geofences)
* [Kujaribu pointi dhidi ya geofence](../../../../../3-transport/lessons/4-geofences)
* [Kutumia geofences kutoka kwa msimbo usio na seva](../../../../../3-transport/lessons/4-geofences)

> 🗑 Hili ni somo la mwisho katika mradi huu, kwa hivyo baada ya kukamilisha somo hili na kazi, usisahau kusafisha huduma zako za wingu. Utahitaji huduma hizo kukamilisha kazi, kwa hivyo hakikisha unakamilisha hiyo kwanza.
>
> Rejelea [mwongozo wa kusafisha mradi wako](../../../clean-up.md) ikiwa ni lazima kwa maelekezo ya jinsi ya kufanya hivyo.

## Geofences ni nini

Geofence ni mpaka wa kielektroniki kwa eneo halisi la kijiografia. Geofences zinaweza kuwa duara lililofafanuliwa kama nukta na radius (kwa mfano duara lenye upana wa 100m karibu na jengo), au poligoni inayofunika eneo kama eneo la shule, mipaka ya jiji, au kampasi ya chuo kikuu au ofisi.

![Mifano ya geofence inayoonyesha geofence ya duara karibu na duka la kampuni ya Microsoft, na geofence ya poligoni karibu na kampasi ya magharibi ya Microsoft](../../../../../translated_images/sw/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.png)

> 💁 Huenda tayari umetumia geofences bila kujua. Ikiwa umewahi kuweka kikumbusho kwa kutumia programu ya iOS reminders au Google Keep kulingana na eneo, umeshatumia geofence. Programu hizi huweka geofence kulingana na eneo lililotolewa na kukuarifu simu yako inapoingia kwenye geofence.

Kuna sababu nyingi za kutaka kujua kama gari liko ndani au nje ya geofence:

* Maandalizi ya kupakua - kupata arifa kwamba gari limefika kwenye eneo huruhusu wafanyakazi kujiandaa kupakua gari, kupunguza muda wa kusubiri wa gari. Hii inaweza kuruhusu dereva kufanya usafirishaji zaidi kwa siku bila muda mwingi wa kusubiri.
* Uzingatiaji wa kodi - baadhi ya nchi, kama New Zealand, hutoza kodi ya barabara kwa magari ya dizeli kulingana na uzito wa gari wakati wa kuendesha kwenye barabara za umma pekee. Kutumia geofences huruhusu kufuatilia umbali uliosafiri kwenye barabara za umma tofauti na barabara za kibinafsi kwenye maeneo kama mashamba au maeneo ya ukataji miti.
* Ufuatiliaji wa wizi - ikiwa gari linapaswa kubaki tu katika eneo fulani kama shambani, na linaondoka kwenye geofence, huenda limeibiwa.
* Uzingatiaji wa eneo - baadhi ya sehemu za eneo la kazi, shamba au kiwanda zinaweza kuwa marufuku kwa magari fulani, kama kuweka magari yanayobeba mbolea za bandia na dawa mbali na mashamba yanayolima mazao ya kikaboni. Ikiwa geofence itaingiliwa, basi gari liko nje ya uzingatiaji na dereva anaweza kuarifiwa.

✅ Je, unaweza kufikiria matumizi mengine ya geofences?

Azure Maps, huduma uliyotumia katika somo lililopita kuonyesha data ya GPS, inakuruhusu kufafanua geofences, kisha kujaribu kuona kama nukta iko ndani au nje ya geofence.

## Kufafanua geofence

Geofences hufafanuliwa kwa kutumia GeoJSON, sawa na nukta zilizoongezwa kwenye ramani katika somo lililopita. Katika kesi hii, badala ya kuwa `FeatureCollection` ya maadili ya `Point`, ni `FeatureCollection` inayojumuisha `Polygon`.

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

Kila nukta kwenye poligoni hufafanuliwa kama jozi la longitudo na latitudo katika safu, na nukta hizi ziko katika safu ambayo imewekwa kama `coordinates`. Katika `Point` katika somo lililopita, `coordinates` ilikuwa safu yenye maadili 2, latitudo na longitudo, kwa `Polygon` ni safu ya safu zenye maadili 2, longitudo, latitudo.

> 💁 Kumbuka, GeoJSON hutumia `longitudo, latitudo` kwa nukta, si `latitudo, longitudo`

Safu ya viwianishi vya poligoni daima ina kiingilio 1 zaidi kuliko idadi ya nukta kwenye poligoni, na kiingilio cha mwisho kuwa sawa na cha kwanza, kufunga poligoni. Kwa mfano, kwa mstatili kutakuwa na nukta 5.

![Mstatili na viwianishi](../../../../../translated_images/sw/polygon-points.302193da381cb415.webp)

Katika picha hapo juu, kuna mstatili. Viwianishi vya poligoni vinaanza upande wa juu-kushoto kwa 47,-122, kisha vinaenda kulia kwa 47,-121, kisha chini kwa 46,-121, kisha kulia kwa 46, -122, kisha kurudi juu kwa nukta ya mwanzo kwa 47, -122. Hii inatoa poligoni nukta 5 - juu-kushoto, juu-kulia, chini-kulia, chini-kushoto, kisha juu-kushoto kufunga.

✅ Jaribu kuunda poligoni ya GeoJSON karibu na nyumbani au shule yako. Tumia zana kama [GeoJSON.io](https://geojson.io/).

### Kazi - kufafanua geofence

Ili kutumia geofence katika Azure Maps, kwanza lazima ipakiwa kwenye akaunti yako ya Azure Maps. Mara baada ya kupakiwa, utapata ID ya kipekee ambayo unaweza kutumia kujaribu nukta dhidi ya geofence. Ili kupakia geofences kwenye Azure Maps, unahitaji kutumia API ya wavuti ya ramani. Unaweza kuita API ya wavuti ya Azure Maps kwa kutumia zana inayoitwa [curl](https://curl.se).

> 🎓 Curl ni zana ya mstari wa amri kufanya maombi dhidi ya viunganishi vya wavuti

1. Ikiwa unatumia Linux, macOS, au toleo la hivi karibuni la Windows 10 huenda tayari una curl imewekwa. Endesha amri ifuatayo kutoka kwa terminal au mstari wa amri ili kuangalia:

    ```sh
    curl --version
    ```

    Ikiwa huoni maelezo ya toleo la curl, utahitaji kuisakinisha kutoka kwa [ukurasa wa kupakua curl](https://curl.se/download.html).

    > 💁 Ikiwa una uzoefu na Postman, basi unaweza kutumia hiyo badala yake ikiwa unapendelea.

1. Unda faili ya GeoJSON inayojumuisha poligoni. Utajaribu hii kwa kutumia sensor yako ya GPS, kwa hivyo unda poligoni karibu na eneo lako la sasa. Unaweza kuunda moja kwa mkono kwa kuhariri mfano wa GeoJSON uliotolewa hapo juu, au kutumia zana kama [GeoJSON.io](https://geojson.io).

    GeoJSON itahitaji kuwa na `FeatureCollection`, inayojumuisha `Feature` yenye `geometry` ya aina `Polygon`.

    Lazima pia uongeze kipengele cha `properties` katika kiwango sawa na kipengele cha `geometry`, na hii lazima iwe na `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Ikiwa unatumia [GeoJSON.io](https://geojson.io), basi utalazimika kuongeza kipengele hiki kwa mkono kwenye kipengele cha `properties` kilicho tupu, ama baada ya kupakua faili ya JSON, au katika mhariri wa JSON kwenye programu.

    Hii `geometryId` lazima iwe ya kipekee katika faili hii. Unaweza kupakia geofences nyingi kama `Features` nyingi katika `FeatureCollection` katika faili moja ya GeoJSON, mradi kila moja ina `geometryId` tofauti. Poligoni zinaweza kuwa na `geometryId` sawa ikiwa zimepakiwa kutoka faili tofauti kwa wakati tofauti.

1. Hifadhi faili hii kama `geofence.json`, na nenda mahali ilipo hifadhiwa kwenye terminal au console yako.

1. Endesha amri ifuatayo ya curl kuunda GeoFence:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Badilisha `<subscription_key>` katika URL na API key ya akaunti yako ya Azure Maps.

    URL inatumika kupakia data ya ramani kupitia API ya `https://atlas.microsoft.com/mapData/upload`. Simu inajumuisha parameter ya `api-version` ili kubainisha ni API gani ya Azure Maps ya kutumia, hii ni kuruhusu API kubadilika kwa muda lakini kudumisha utangamano wa nyuma. Muundo wa data unaopakiwa umewekwa kuwa `geojson`.

    Hii itaendesha ombi la POST kwa API ya kupakia na kurudisha orodha ya vichwa vya majibu ambavyo vinajumuisha kichwa kinachoitwa `location`.

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

    > 🎓 Wakati wa kuita kiunganishi cha wavuti, unaweza kupitisha vigezo kwa simu kwa kuongeza `?` ikifuatiwa na jozi za thamani ya ufunguo kama `key=value`, ukitenganisha jozi za thamani ya ufunguo kwa `&`.

1. Azure Maps haichakata hii mara moja, kwa hivyo utahitaji kuangalia ili kuona ikiwa ombi la kupakia limekamilika kwa kutumia URL iliyotolewa katika kichwa cha `location`. Fanya ombi la GET kwa eneo hili ili kuona hali. Utahitaji kuongeza subscription key yako mwishoni mwa URL ya `location` kwa kuongeza `&subscription-key=<subscription_key>` mwishoni, ukibadilisha `<subscription_key>` na API key ya akaunti yako ya Azure Maps. Endesha amri ifuatayo:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Badilisha `<location>` na thamani ya kichwa cha `location`, na `<subscription_key>` na API key ya akaunti yako ya Azure Maps.

1. Angalia thamani ya `status` katika majibu. Ikiwa si `Succeeded`, basi subiri dakika moja na jaribu tena.

1. Mara hali inapokuja kama `Succeeded`, angalia `resourceLocation` kutoka kwa majibu. Hii ina maelezo kuhusu ID ya kipekee (inayojulikana kama UDID) kwa kitu cha GeoJSON. UDID ni thamani baada ya `metadata/`, na si pamoja na `api-version`. Kwa mfano, ikiwa `resourceLocation` ilikuwa:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Basi UDID itakuwa `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Hifadhi nakala ya UDID hii kwani utahitaji kuijaribu geofence.

## Kujaribu pointi dhidi ya geofence

Mara poligoni inapopakiwa kwenye Azure Maps, unaweza kujaribu nukta kuona kama iko ndani au nje ya geofence. Unafanya hivi kwa kufanya ombi la API ya wavuti, ukipita UDID ya geofence, na latitudo na longitudo ya nukta ya kujaribu.

Wakati unafanya ombi hili, unaweza pia kupitisha thamani inayoitwa `searchBuffer`. Hii inaambia API ya Ramani jinsi ya kuwa sahihi wakati wa kurudisha matokeo. Sababu ya hii ni kwamba GPS si sahihi kabisa, na wakati mwingine maeneo yanaweza kuwa nje kwa mita ikiwa si zaidi. Chaguo-msingi kwa search buffer ni 50m, lakini unaweza kuweka maadili kutoka 0m hadi 500m.

Wakati matokeo yanarudishwa kutoka kwa simu ya API, moja ya sehemu za matokeo ni `distance` iliyopimwa hadi nukta ya karibu kwenye ukingo wa geofence, na thamani chanya ikiwa nukta iko nje ya geofence, hasi ikiwa iko ndani ya geofence. Ikiwa umbali huu ni chini ya search buffer, umbali halisi unarudishwa kwa mita, vinginevyo thamani ni 999 au -999. 999 inamaanisha kwamba nukta iko nje ya geofence kwa zaidi ya search buffer, -999 inamaanisha iko ndani ya geofence kwa zaidi ya search buffer.

![Geofence na search buffer ya 50m karibu nayo](../../../../../translated_images/sw/search-buffer-and-distance.e6a79af3898183c7.webp)

Katika picha hapo juu, geofence ina search buffer ya 50m.

* Nukta katikati ya geofence, ndani kabisa ya search buffer ina umbali wa **-999**
* Nukta nje kabisa ya search buffer ina umbali wa **999**
* Nukta ndani ya geofence na ndani ya search buffer, 6m kutoka geofence, ina umbali wa **6m**
* Nukta nje ya geofence na ndani ya search buffer, 39m kutoka geofence, ina umbali wa **39m**

Ni muhimu kujua umbali hadi ukingo wa geofence, na kuunganisha hii na taarifa nyingine kama maelezo ya GPS mengine, kasi na data ya barabara wakati wa kufanya maamuzi kulingana na eneo la gari.

Kwa mfano, fikiria maelezo ya GPS yanayoonyesha gari lilikuwa linaendesha barabara inayomalizika karibu na geofence. Ikiwa thamani moja ya GPS si sahihi na inaweka gari ndani ya geofence, licha ya kutokuwepo kwa ufikiaji wa gari, basi inaweza kupuuzwa.

![Njia ya GPS inayoonyesha gari likipita kampasi ya Microsoft kwenye 520, na maelezo ya GPS kando ya barabara isipokuwa moja kwenye kampasi, ndani ya geofence](../../../../../translated_images/sw/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.png)
Katika picha hapo juu, kuna geofence juu ya sehemu ya kampasi ya Microsoft. Mstari mwekundu unaonyesha lori likiendeshwa kando ya barabara ya 520, na duara zinaonyesha vipimo vya GPS. Vipimo vingi ni sahihi na viko kando ya barabara ya 520, lakini kuna kipimo kimoja kisicho sahihi ndani ya geofence. Haiwezekani kipimo hicho kuwa sahihi - hakuna barabara kwa lori kubadilisha ghafla kutoka barabara ya 520 kwenda kampasi, kisha kurudi tena kwenye barabara ya 520. Msimbo unaochunguza geofence hii utahitaji kuzingatia vipimo vya awali kabla ya kuchukua hatua kulingana na matokeo ya jaribio la geofence.

✅ Ni data gani ya ziada unayohitaji kuangalia ili kuthibitisha kama kipimo cha GPS kinaweza kuchukuliwa kuwa sahihi?

### Kazi - jaribu pointi dhidi ya geofence

1. Anza kwa kujenga URL ya swali la API ya wavuti. Muundo ni:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Badilisha `<subscription_key>` na ufunguo wa API wa akaunti yako ya Azure Maps.

    Badilisha `<UDID>` na UDID ya geofence kutoka kwenye kazi ya awali.

    Badilisha `<lat>` na `<lon>` na latitudo na longitudo unayotaka kujaribu.

    URL hii inatumia API ya `https://atlas.microsoft.com/spatial/geofence/json` kuuliza geofence iliyofafanuliwa kwa kutumia GeoJSON. Inalenga toleo la API `1.0`. Kipengele cha `deviceId` kinahitajika na kinapaswa kuwa jina la kifaa ambacho latitudo na longitudo zinatoka.

    Buffer ya utafutaji ya chaguo-msingi ni 50m, na unaweza kubadilisha hii kwa kupitisha kipengele cha ziada cha `searchBuffer=<distance>`, ukibadilisha `<distance>` na umbali wa buffer ya utafutaji kwa mita, kutoka 0 hadi 500.

1. Tumia curl kufanya ombi la GET kwa URL hii:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Ukipata msimbo wa majibu wa `BadRequest`, na kosa la:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > basi GeoJSON yako inakosa sehemu ya `properties` yenye `geometryId`. Utahitaji kurekebisha GeoJSON yako, kisha kurudia hatua zilizo hapo juu ili kupakia tena na kupata UDID mpya.

1. Majibu yatakuwa na orodha ya `geometries`, moja kwa kila poligoni iliyofafanuliwa katika GeoJSON iliyotumika kuunda geofence. Kila geometry ina sehemu 3 za kuvutia, `distance`, `nearestLat` na `nearestLon`.

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

    * `nearestLat` na `nearestLon` ni latitudo na longitudo ya sehemu kwenye ukingo wa geofence ambayo iko karibu zaidi na eneo linalojaribiwa.

    * `distance` ni umbali kutoka eneo linalojaribiwa hadi sehemu ya karibu zaidi kwenye ukingo wa geofence. Nambari hasi zinaonyesha ndani ya geofence, nambari chanya nje. Thamani hii itakuwa chini ya 50 (buffer ya utafutaji ya chaguo-msingi), au 999.

1. Rudia hii mara kadhaa na maeneo ndani na nje ya geofence.

## Tumia geofences kutoka kwa msimbo wa serverless

Sasa unaweza kuongeza trigger mpya kwenye programu yako ya Functions ili kujaribu data ya tukio la GPS la IoT Hub dhidi ya geofence.

### Vikundi vya watumiaji

Kama unavyokumbuka kutoka masomo ya awali, IoT Hub itakuruhusu kurudia matukio ambayo yamepokelewa na hub lakini hayajashughulikiwa. Lakini nini kitatokea ikiwa triggers nyingi zimeunganishwa? Itawezaje kujua ni ipi imechakata matukio gani?

Jibu ni kwamba haiwezi! Badala yake unaweza kufafanua miunganisho tofauti kusoma matukio, na kila moja inaweza kudhibiti kurudia kwa ujumbe ambao haujasomwa. Hizi zinaitwa *vikundi vya watumiaji*. Unapounganisha kwenye endpoint, unaweza kubainisha ni kikundi gani cha watumiaji unataka kuunganishwa nacho. Kila sehemu ya programu yako itaunganishwa na kikundi tofauti cha watumiaji.

![IoT Hub moja na vikundi 3 vya watumiaji vinavyosambaza ujumbe sawa kwa programu 3 tofauti za Functions](../../../../../translated_images/sw/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.png)

Kwa nadharia, hadi programu 5 zinaweza kuunganishwa kwa kila kikundi cha watumiaji, na zote zitapokea ujumbe unapowasili. Ni bora kuwa na programu moja tu inayopata kila kikundi cha watumiaji ili kuepuka uchakataji wa ujumbe mara mbili, na kuhakikisha unapowasha tena ujumbe wote ulio kwenye foleni unachakatwa kwa usahihi. Kwa mfano, ikiwa ulizindua programu yako ya Functions kwa ndani pamoja na kuiendesha kwenye wingu, zote mbili zingechakata ujumbe, na kusababisha blobs maradufu kuhifadhiwa kwenye akaunti ya hifadhi.

Ukikagua faili ya `function.json` kwa trigger ya IoT Hub uliyounda katika somo la awali, utaona kikundi cha watumiaji katika sehemu ya binding ya trigger ya event hub:

```json
"consumerGroup": "$Default"
```

Unapounda IoT Hub, unapata kikundi cha watumiaji cha `$Default` kilichoundwa kwa chaguo-msingi. Ikiwa unataka kuongeza trigger ya ziada, unaweza kuongeza hii kwa kutumia kikundi kipya cha watumiaji.

> 💁 Katika somo hili, utatumia function tofauti kujaribu geofence na ile iliyotumika kuhifadhi data ya GPS. Hii ni kuonyesha jinsi ya kutumia vikundi vya watumiaji na kutenganisha msimbo ili iwe rahisi kusoma na kuelewa. Katika programu ya uzalishaji kuna njia nyingi unazoweza kupanga hili - kuweka zote kwenye function moja, kutumia trigger kwenye akaunti ya hifadhi kuendesha function ya kuangalia geofence, au kutumia functions nyingi. Hakuna 'njia sahihi', inategemea programu yako yote na mahitaji yako.

### Kazi - unda kikundi kipya cha watumiaji

1. Endesha amri ifuatayo kuunda kikundi kipya cha watumiaji kinachoitwa `geofence` kwa IoT Hub yako:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Badilisha `<hub_name>` na jina ulilotumia kwa IoT Hub yako.

1. Ikiwa unataka kuona vikundi vyote vya watumiaji kwa IoT Hub, endesha amri ifuatayo:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Badilisha `<hub_name>` na jina ulilotumia kwa IoT Hub yako. Hii itaorodhesha vikundi vyote vya watumiaji.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Ulipoendesha monitor ya tukio la IoT Hub katika somo la awali, iliunganishwa na kikundi cha watumiaji cha `$Default`. Hii ndiyo sababu huwezi kuendesha monitor ya tukio na trigger ya tukio. Ikiwa unataka kuendesha zote mbili, basi unaweza kutumia vikundi vingine vya watumiaji kwa programu zako zote za function, na kuweka `$Default` kwa monitor ya tukio.

### Kazi - unda trigger mpya ya IoT Hub

1. Ongeza trigger mpya ya tukio la IoT Hub kwenye programu yako ya `gps-trigger` ya function uliyounda katika somo la awali. Ita function hii `geofence-trigger`.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunda trigger ya tukio la IoT Hub kutoka mradi wa 2, somo la 5 ikiwa inahitajika](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Sanidi string ya muunganisho wa IoT Hub katika faili ya `function.json`. Faili ya `local.settings.json` inashirikiwa kati ya triggers zote katika programu ya Function.

1. Sasisha thamani ya `consumerGroup` katika faili ya `function.json` ili kurejelea kikundi kipya cha watumiaji cha `geofence`:

    ```json
    "consumerGroup": "geofence"
    ```

1. Utahitaji kutumia ufunguo wa usajili wa akaunti yako ya Azure Maps katika trigger hii, kwa hivyo ongeza kipengele kipya kwenye faili ya `local.settings.json` kinachoitwa `MAPS_KEY`.

1. Endesha programu ya Functions ili kuhakikisha inaunganishwa na kuchakata ujumbe. Trigger ya `iot-hub-trigger` kutoka somo la awali pia itaendesha na kupakia blobs kwenye hifadhi.

    > Ili kuepuka vipimo vya GPS maradufu katika hifadhi ya blob, unaweza kusimamisha programu ya Functions unayoendesha kwenye wingu. Ili kufanya hivyo, tumia amri ifuatayo:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Badilisha `<functions_app_name>` na jina ulilotumia kwa programu yako ya Functions.
    >
    > Unaweza kuianzisha tena baadaye kwa amri ifuatayo:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Badilisha `<functions_app_name>` na jina ulilotumia kwa programu yako ya Functions.

### Kazi - jaribu geofence kutoka trigger

Mapema katika somo hili ulitumia curl kuuliza geofence ili kuona kama pointi iko ndani au nje. Unaweza kufanya ombi la wavuti kama hilo kutoka ndani ya trigger yako.

1. Ili kuuliza geofence, unahitaji UDID yake. Ongeza kipengele kipya kwenye faili ya `local.settings.json` kinachoitwa `GEOFENCE_UDID` na thamani hii.

1. Fungua faili ya `__init__.py` kutoka trigger mpya ya `geofence-trigger`.

1. Ongeza import ifuatayo juu ya faili:

    ```python
    import json
    import os
    import requests
    ```

    Kipengele cha `requests` kinakuruhusu kufanya maombi ya API ya wavuti. Azure Maps haina SDK ya Python, unahitaji kufanya maombi ya API ya wavuti kuitumia kutoka kwa msimbo wa Python.

1. Ongeza mistari 2 ifuatayo mwanzoni mwa njia ya `main` ili kupata ufunguo wa usajili wa Maps:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Ndani ya kitanzi cha `for event in events`, ongeza ifuatayo ili kupata latitudo na longitudo kutoka kila tukio:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Msimbo huu hubadilisha JSON kutoka mwili wa tukio kuwa kamusi, kisha hutoa `lat` na `lon` kutoka sehemu ya `gps`.

1. Unapotumia `requests`, badala ya kujenga URL ndefu kama ulivyofanya na curl, unaweza kutumia sehemu ya URL tu na kupitisha vipengele kama kamusi. Ongeza msimbo ufuatao ili kufafanua URL ya kupiga na kusanidi vipengele:

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

    Vipengele katika kamusi ya `params` vitafanana na jozi za funguo na thamani ulizotumia ulipoita API ya wavuti kupitia curl.

1. Ongeza mistari ifuatayo ya msimbo ili kupiga API ya wavuti:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Hii inaita URL na vipengele, na kurudisha kitu cha majibu.

1. Ongeza msimbo ufuatao chini ya hii:

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

    Msimbo huu unadhani geometry moja, na hutoa umbali kutoka geometry hiyo moja. Kisha huandika ujumbe tofauti kulingana na umbali.

1. Endesha msimbo huu. Utaona katika matokeo ya kuandika ikiwa vipimo vya GPS viko ndani au nje ya geofence, na umbali ikiwa pointi iko ndani ya 50m. Jaribu msimbo huu na geofences tofauti kulingana na eneo la sensor yako ya GPS, jaribu kuhamisha sensor (kwa mfano kwa kuunganisha kwenye WiFi kutoka simu ya mkononi, au kwa kutumia latitudo na longitudo tofauti kwenye kifaa cha IoT cha virtual) ili kuona mabadiliko haya.

1. Unapokuwa tayari, pakia msimbo huu kwenye programu yako ya Functions kwenye wingu. Usisahau kupakia mipangilio mpya ya programu.

    > ⚠️ Unaweza kurejelea [maelekezo ya kupakia mipangilio ya programu kutoka mradi wa 2, somo la 5 ikiwa inahitajika](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Unaweza kurejelea [maelekezo ya kupakia programu yako ya Functions kutoka mradi wa 2, somo la 5 ikiwa inahitajika](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Unaweza kupata msimbo huu katika folda ya [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Changamoto

Katika somo hili umeongeza geofence moja kwa kutumia faili ya GeoJSON yenye poligoni moja. Unaweza kupakia poligoni nyingi kwa wakati mmoja, mradi tu zina `geometryId` tofauti katika sehemu ya `properties`.

Jaribu kupakia faili ya GeoJSON yenye poligoni nyingi na rekebisha msimbo wako ili kupata ni poligoni gani vipimo vya GPS viko karibu nayo au ndani yake.

## Maswali ya baada ya somo

[Maswali ya baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Mapitio na Kujisomea

* Soma zaidi kuhusu geofences na baadhi ya matumizi yake kwenye [ukurasa wa Geofencing kwenye Wikipedia](https://en.wikipedia.org/wiki/Geo-fence).
* Soma zaidi kuhusu API ya geofencing ya Azure Maps kwenye [Microsoft Azure Maps Spatial - Get Geofence documentation](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Soma zaidi kuhusu vikundi vya watumiaji katika [Features and terminology in Azure Event Hubs - Event consumers documentation on Microsoft docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers)

## Kazi

[Tuma arifa kwa kutumia Twilio](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.