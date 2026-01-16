<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-27T21:04:18+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "hu"
}
-->
# Nyelv megértése

![A lecke áttekintése sketchnote formában](../../../../../translated_images/hu/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.jpg)

> Sketchnote készítette: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

## Előzetes kvíz

[Előzetes kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Bevezetés

Az előző leckében a beszédet szöveggé alakítottad. Ahhoz, hogy ezt egy okos időzítő programozására használhasd, a kódodnak értenie kell, hogy mit mondtak. Feltételezhetnéd, hogy a felhasználó egy fix kifejezést mond, például "Állíts be egy 3 perces időzítőt", és elemezhetnéd ezt a kifejezést, hogy megtudd, mennyi ideig kell az időzítőnek működnie, de ez nem túl felhasználóbarát. Ha egy felhasználó azt mondaná, hogy "Állíts be egy időzítőt 3 percre", te vagy én értenénk, mit jelent, de a kódod nem, mert egy fix kifejezést várna.

Itt jön képbe a nyelv megértése, amely mesterséges intelligencia modelleket használ a szöveg értelmezésére és a szükséges részletek visszaadására. Például képes lenne értelmezni mind a "Állíts be egy 3 perces időzítőt", mind a "Állíts be egy időzítőt 3 percre", és megértené, hogy egy 3 perces időzítőre van szükség.

Ebben a leckében megtanulod, hogyan működnek a nyelvmegértési modellek, hogyan lehet őket létrehozni, tanítani és használni a kódban.

Ebben a leckében az alábbiakat fogjuk áttekinteni:

* [Nyelv megértése](../../../../../6-consumer/lessons/2-language-understanding)
* [Nyelvmegértési modell létrehozása](../../../../../6-consumer/lessons/2-language-understanding)
* [Szándékok és entitások](../../../../../6-consumer/lessons/2-language-understanding)
* [Nyelvmegértési modell használata](../../../../../6-consumer/lessons/2-language-understanding)

## Nyelv megértése

Az emberek több százezer éve használják a nyelvet kommunikációra. Szavakkal, hangokkal vagy cselekvésekkel kommunikálunk, és megértjük, amit mondanak, nemcsak a szavak, hangok vagy cselekvések jelentését, hanem azok kontextusát is. Értjük az őszinteséget és a szarkazmust, lehetővé téve, hogy ugyanazok a szavak különböző dolgokat jelentsenek a hangszíntől függően.

✅ Gondolj néhány közelmúltbeli beszélgetésedre. Mennyire lenne nehéz egy számítógép számára megérteni a beszélgetést, mert kontextusra van szüksége?

A nyelv megértése, más néven természetes nyelv megértése, a mesterséges intelligencia egy területe, amelyet természetes nyelv feldolgozásnak (NLP) neveznek, és az olvasási szövegértéssel foglalkozik, megpróbálva megérteni a szavak vagy mondatok részleteit. Ha olyan hangalapú asszisztenst használsz, mint Alexa vagy Siri, akkor már használtál nyelvmegértési szolgáltatásokat. Ezek azok a háttérben működő AI szolgáltatások, amelyek az "Alexa, játssz le Taylor Swift legújabb albumát" kérést átalakítják a lányom táncára a nappaliban a kedvenc zenéjére.

> 💁 A számítógépek, minden előrelépésük ellenére, még mindig messze vannak attól, hogy igazán megértsék a szöveget. Amikor a nyelv megértéséről beszélünk számítógépekkel, nem olyan fejlett kommunikációra gondolunk, mint az emberi, hanem arra, hogy néhány szóból kulcsfontosságú részleteket nyerjünk ki.

Emberként anélkül értjük meg a nyelvet, hogy igazán gondolkodnánk rajta. Ha megkérnék egy másik embert, hogy "játssza le Taylor Swift legújabb albumát", akkor ösztönösen tudná, mit értek. Egy számítógép számára ez nehezebb. A szavakat, amelyeket beszédből szöveggé alakítottak, elemeznie kell, és az alábbi információkat kell kinyernie:

* Zenét kell lejátszani
* A zene Taylor Swift előadóhoz tartozik
* A konkrét zene egy teljes album, amely több számot tartalmaz sorrendben
* Taylor Swiftnek sok albuma van, tehát időrendi sorrendbe kell őket állítani, és a legutóbb kiadott albumra van szükség

✅ Gondolj néhány más mondatra, amelyet kérések során mondtál, például kávérendeléskor vagy amikor egy családtagtól kérsz valamit. Próbáld meg lebontani azokat az információkat, amelyeket egy számítógépnek ki kellene nyernie a mondat megértéséhez.

A nyelvmegértési modellek olyan AI modellek, amelyeket arra képeznek ki, hogy bizonyos részleteket nyerjenek ki a nyelvből, majd konkrét feladatokra tanítják őket átviteli tanulás segítségével, ugyanúgy, ahogy egy Egyedi Látás modellt tanítottál egy kis képgyűjteménnyel. Egy modellt vehetsz, majd a szöveggel, amelyet meg akarsz érteni, taníthatod.

## Nyelvmegértési modell létrehozása

![A LUIS logója](../../../../../translated_images/hu/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.png)

Nyelvmegértési modelleket hozhatsz létre a LUIS segítségével, amely a Microsoft egyik nyelvmegértési szolgáltatása, és a Cognitive Services része.

### Feladat - szerzői erőforrás létrehozása

A LUIS használatához létre kell hoznod egy szerzői erőforrást.

1. Használd az alábbi parancsot egy szerzői erőforrás létrehozásához a `smart-timer` erőforráscsoportban:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Cseréld ki `<location>`-t arra a helyre, amelyet az erőforráscsoport létrehozásakor használtál.

    > ⚠️ A LUIS nem érhető el minden régióban, így ha az alábbi hibát kapod:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > válassz egy másik régiót.

    Ez létrehoz egy ingyenes LUIS szerzői erőforrást.

### Feladat - nyelvmegértési alkalmazás létrehozása

1. Nyisd meg a LUIS portált a [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) oldalon a böngésződben, és jelentkezz be ugyanazzal a fiókkal, amelyet az Azure használatához használtál.

1. Kövesd a párbeszédablak utasításait az Azure-előfizetés kiválasztásához, majd válaszd ki az imént létrehozott `smart-timer-luis-authoring` erőforrást.

1. A *Conversation apps* listából válaszd ki az **Új alkalmazás** gombot egy új alkalmazás létrehozásához. Nevezd el az új alkalmazást `smart-timer` néven, és állítsd be a *Kultúrát* a nyelvedre.

    > 💁 Van egy mező az előrejelzési erőforráshoz. Létrehozhatsz egy második erőforrást csak előrejelzéshez, de az ingyenes szerzői erőforrás havonta 1000 előrejelzést tesz lehetővé, ami elegendő a fejlesztéshez, így ezt üresen hagyhatod.

1. Olvasd el az útmutatót, amely megjelenik az alkalmazás létrehozása után, hogy megértsd a nyelvmegértési modell tanításához szükséges lépéseket. Zárd be az útmutatót, amikor végeztél.

## Szándékok és entitások

A nyelv megértése *szándékok* és *entitások* köré épül. A szándékok azt jelentik, hogy mi a szavak célja, például zene lejátszása, időzítő beállítása vagy étel rendelése. Az entitások pedig azt jelentik, hogy mire vonatkozik a szándék, például az albumra, az időzítő hosszára vagy az étel típusára. Minden mondatnak, amelyet a modell értelmez, legalább egy szándéka kell legyen, és opcionálisan egy vagy több entitása.

Néhány példa:

| Mondat                                              | Szándék          | Entitások                                   |
| --------------------------------------------------- | ---------------- | ------------------------------------------ |
| "Játssz le Taylor Swift legújabb albumát"           | *zene lejátszása*| *Taylor Swift legújabb albuma*             |
| "Állíts be egy 3 perces időzítőt"                   | *időzítő beállítása*| *3 perc*                                   |
| "Töröld az időzítőmet"                              | *időzítő törlése*| Nincs                                      |
| "Rendelj 3 nagy ananászos pizzát és egy cézár salátát" | *étel rendelése* | *3 nagy ananászos pizza*, *cézár saláta*   |

✅ Azokkal a mondatokkal, amelyeket korábban átgondoltál, mi lenne a szándék és az entitások abban a mondatban?

A LUIS tanításához először az entitásokat kell beállítani. Ezek lehetnek fix kifejezések listája, vagy a szövegből tanultak. Például megadhatsz egy fix listát az étlapodon elérhető ételekről, variációkkal (vagy szinonimákkal) minden szóról, például *padlizsán* és *aubergine* mint a *aubergine* variációi. A LUIS előre elkészített entitásokat is kínál, amelyeket használhatsz, például számokat és helyeket.

Az időzítő beállításához lehetne egy entitás az időre vonatkozó előre elkészített szám entitásokkal, és egy másik az egységekre, például percekre és másodpercekre. Minden egységnek több variációja lenne, hogy lefedje az egyes és többes számú formákat - például perc és percek.

Miután az entitásokat definiáltad, létrehozod a szándékokat. Ezeket a modell tanulja meg az általad megadott példamondatok alapján (ezeket *kifejezéseknek* nevezik). Például egy *időzítő beállítása* szándékhoz az alábbi mondatokat adhatnád meg:

* `állíts be egy 1 másodperces időzítőt`
* `állíts be egy időzítőt 1 perc és 12 másodpercre`
* `állíts be egy időzítőt 3 percre`
* `állíts be egy 9 perc 30 másodperces időzítőt`

Ezután megmondod a LUIS-nak, hogy ezeknek a mondatoknak mely részei felelnek meg az entitásoknak:

![A mondat, állíts be egy időzítőt 1 perc és 12 másodpercre, entitásokra bontva](../../../../../translated_images/hu/sentence-as-intent-entities.301401696f992259.webp)

A mondat `állíts be egy időzítőt 1 perc és 12 másodpercre` szándéka `időzítő beállítása`. Emellett 2 entitása van, mindegyik 2 értékkel:

|            | idő | egység   |
| ---------- | ---: | ------ |
| 1 perc     | 1    | perc   |
| 12 másodperc | 12   | másodperc |

Egy jó modell tanításához különböző példamondatok széles skálájára van szükség, hogy lefedje azokat a sokféle módokat, ahogyan valaki ugyanazt kérheti.

> 💁 Mint minden AI modell esetében, minél több adatot és minél pontosabb adatot használsz a tanításhoz, annál jobb lesz a modell.

✅ Gondolj arra, hogy hányféleképpen kérhetnéd ugyanazt, és elvárnád, hogy egy ember megértse.

### Feladat - entitások hozzáadása a nyelvmegértési modellekhez

Az időzítőhöz 2 entitást kell hozzáadnod - egyet az időegységre (perc vagy másodperc), és egyet a percek vagy másodpercek számára.

A LUIS portál használatára vonatkozó utasításokat megtalálod a [Quickstart: Build your app in LUIS portal dokumentációban a Microsoft Docs-on](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. A LUIS portálon válaszd ki az *Entitások* fület, és add hozzá a *szám* előre elkészített entitást az **Előre elkészített entitás hozzáadása** gombbal, majd válaszd ki a *számot* a listából.

1. Hozz létre egy új entitást az időegységhez az **Új létrehozása** gombbal. Nevezd el az entitást `időegység` néven, és állítsd be a típusát *Lista*-ra. Adj hozzá értékeket a *Normalizált értékek* listához `perc` és `másodperc` néven, és add hozzá az egyes és többes számú formákat a *szinonimák* listához. Nyomd meg az `enter`-t minden szinonima hozzáadása után, hogy hozzáadd a listához.

    | Normalizált érték | Szinonimák        |
    | ---------------- | --------------- |
    | perc             | perc, percek    |
    | másodperc        | másodperc, másodpercek |

### Feladat - szándékok hozzáadása a nyelvmegértési modellekhez

1. Az *Szándékok* fülön válaszd ki az **Új létrehozása** gombot egy új szándék létrehozásához. Nevezd el ezt a szándékot `időzítő beállítása` néven.

1. A példákban adj meg különböző módokat az időzítő beállítására, mind percekkel, másodpercekkel, valamint percek és másodpercek kombinációjával. Példák lehetnek:

    * `állíts be egy 1 másodperces időzítőt`
    * `állíts be egy 4 perces időzítőt`
    * `állíts be egy négy perc hat másodperces időzítőt`
    * `állíts be egy 9 perc 30 másodperces időzítőt`
    * `állíts be egy időzítőt 1 perc és 12 másodpercre`
    * `állíts be egy időzítőt 3 percre`
    * `állíts be egy időzítőt 3 percre és 1 másodpercre`
    * `állíts be egy időzítőt három percre és egy másodpercre`
    * `állíts be egy időzítőt 1 percre és 1 másodpercre`
    * `állíts be egy időzítőt 30 másodpercre`
    * `állíts be egy időzítőt 1 másodpercre`

    Keverd a számokat szavakkal és numerikus formában, hogy a modell megtanulja kezelni mindkettőt.

1. Ahogy minden példát megadsz, a LUIS elkezdi felismerni az entitásokat, és aláhúzza és címkézi azokat, amelyeket talál.

    ![A példák, ahol a számok és időegységek alá vannak húzva a LUIS által](../../../../../translated_images/hu/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.png)

### Feladat - a modell tanítása és tesztelése

1. Miután az entitások és szándékok be vannak állítva, a modellt a **Tanítás** gombbal a felső menüben taníthatod. Válaszd ki ezt a gombot, és a modell néhány másodperc alatt megtanulja. A gomb szürke lesz a tanítás alatt, és újra elérhetővé válik, amikor kész.

1. Válaszd ki a **Tesztelés** gombot a felső menüből a nyelvmegértési modell teszt
1. Az *Azure Resources* szekcióból válaszd ki az *Authoring Resource*-t, és másold ki a *Primary Key*-t és az *Endpoint URL*-t.

1. Futtasd a következő curl parancsot a parancssorban vagy terminálban:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Cseréld ki `<endpoint url>`-t az *Azure Resources* szekcióból származó Endpoint URL-re.

    Cseréld ki `<app id>`-t a *Settings* szekcióból származó App ID-re.

    Cseréld ki `<primary key>`-t az *Azure Resources* szekcióból származó Primary Key-re.

    Cseréld ki `<sentence>`-t arra a mondatra, amivel tesztelni szeretnél.

1. A hívás eredménye egy JSON dokumentum lesz, amely részletezi a lekérdezést, a legvalószínűbb szándékot, valamint az entitások listáját típus szerint bontva.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    A fenti JSON a következő lekérdezésből származik: `set a timer for 45 minutes and 12 seconds`:

    * A `set timer` volt a legvalószínűbb szándék 97%-os valószínűséggel.
    * Két *number* entitást észlelt, `45` és `12`.
    * Két *time-unit* entitást észlelt, `minute` és `second`.

## A nyelvi megértési modell használata

Miután publikáltad, a LUIS modellt kódból is meghívhatod. Korábbi leckékben IoT Hubot használtál a felhőszolgáltatásokkal való kommunikációhoz, telemetria küldésére és parancsok fogadására. Ez nagyon aszinkron működés - ha telemetriát küldesz, a kód nem vár választ, és ha a felhőszolgáltatás nem elérhető, nem fogod tudni.

Egy okos időzítő esetében azonnali választ szeretnénk kapni, hogy jelezhessük a felhasználónak, hogy az időzítő beállításra került, vagy figyelmeztessük, hogy a felhőszolgáltatások nem elérhetők. Ehhez az IoT eszközünk közvetlenül egy webes végpontot fog hívni, ahelyett, hogy IoT Hubra támaszkodna.

Ahelyett, hogy a LUIS-t közvetlenül az IoT eszközről hívnánk, használhatunk szerver nélküli kódot egy másik típusú triggerrel - egy HTTP triggerrel. Ez lehetővé teszi, hogy a funkcióalkalmazás REST kéréseket fogadjon és válaszoljon rájuk. Ez a funkció egy REST végpont lesz, amelyet az eszközöd hívhat.

> 💁 Bár közvetlenül hívhatod a LUIS-t az IoT eszközödről, jobb szerver nélküli kódot használni. Így, ha például egy jobb modellt tanítasz vagy egy másik nyelven tanítasz modellt, csak a felhőkódot kell frissítened, nem pedig több ezer vagy millió IoT eszköz kódját újratelepítened.

### Feladat - hozz létre egy szerver nélküli funkcióalkalmazást

1. Hozz létre egy Azure Functions alkalmazást `smart-timer-trigger` néven, és nyisd meg ezt a VS Code-ban.

1. Adj hozzá egy HTTP triggert az alkalmazáshoz `speech-trigger` néven a következő parancs segítségével a VS Code termináljában:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Ez létrehoz egy HTTP triggert `text-to-timer` néven.

1. Teszteld az HTTP triggert az alkalmazás futtatásával. Amikor fut, a végpont megjelenik a kimenetben:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Teszteld ezt az [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) URL betöltésével a böngésződben.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Feladat - használd a nyelvi megértési modellt

1. A LUIS SDK elérhető egy Pip csomagon keresztül. Add hozzá a következő sort a `requirements.txt` fájlhoz, hogy hozzáadd a függőséget ehhez a csomaghoz:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Győződj meg róla, hogy a VS Code terminálban aktiválva van a virtuális környezet, és futtasd a következő parancsot a Pip csomagok telepítéséhez:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Ha hibákat kapsz, lehet, hogy frissítened kell a pipet a következő parancs segítségével:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Adj hozzá új bejegyzéseket a `local.settings.json` fájlhoz a LUIS API Key, Endpoint URL és App ID értékekkel a LUIS portál **MANAGE** füléről:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Cseréld ki `<endpoint url>`-t az *Azure Resources* szekcióból származó Endpoint URL-re a **MANAGE** fülön. Ez `https://<location>.api.cognitive.microsoft.com/` lesz.

    Cseréld ki `<app id>`-t a *Settings* szekcióból származó App ID-re a **MANAGE** fülön.

    Cseréld ki `<primary key>`-t az *Azure Resources* szekcióból származó Primary Key-re a **MANAGE** fülön.

1. Add hozzá a következő importokat az `__init__.py` fájlhoz:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Ez importál néhány rendszerkönyvtárat, valamint a LUIS-szal való interakcióhoz szükséges könyvtárakat.

1. Töröld a `main` metódus tartalmát, és add hozzá a következő kódot:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Ez betölti a `local.settings.json` fájlban hozzáadott értékeket a LUIS alkalmazásodhoz, létrehoz egy hitelesítési objektumot az API kulcsoddal, majd létrehoz egy LUIS kliens objektumot az alkalmazásoddal való interakcióhoz.

1. Ez a HTTP trigger JSON formátumban kapja meg a megértendő szöveget, a szöveget egy `text` nevű tulajdonságban. A következő kód kinyeri az értéket az HTTP kérés törzséből, és kiírja a konzolra. Add hozzá ezt a kódot a `main` függvényhez:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. A LUIS-tól való előrejelzések kéréséhez egy előrejelzési kérésre van szükség - egy JSON dokumentumra, amely tartalmazza az előrejelzendő szöveget. Hozd létre ezt a következő kóddal:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Ez a kérés elküldhető a LUIS-hoz, az alkalmazásod publikált staging slotját használva:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Az előrejelzési válasz tartalmazza a legvalószínűbb szándékot - a legmagasabb előrejelzési pontszámmal rendelkező szándékot, valamint az entitásokat. Ha a legvalószínűbb szándék a `set timer`, akkor az entitásokból kiolvasható az időzítőhöz szükséges idő:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    A `number` entitások egy számokból álló tömböt alkotnak. Például, ha azt mondod: *"Set a four minute 17 second timer."*, akkor a `number` tömb 2 egész számot tartalmaz - 4 és 17.

    A `time unit` entitások egy karakterláncokból álló tömbök tömbjét alkotják, minden időegység egy karakterláncokból álló tömbként jelenik meg a tömbben. Például, ha azt mondod: *"Set a four minute 17 second timer."*, akkor a `time unit` tömb 2 tömböt tartalmaz, mindegyikben egy-egy értékkel - `['minute']` és `['second']`.

    Az entitások JSON verziója *"Set a four minute 17 second timer."* esetén:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Ez a kód egy számlálót is definiál az időzítő teljes idejére másodpercben. Ez az entitások értékeivel lesz feltöltve.

1. Az entitások nincsenek összekapcsolva, de feltételezéseket tehetünk róluk. Az elhangzott sorrendben lesznek, így a tömbben lévő pozíció használható annak meghatározására, hogy melyik szám melyik időegységhez tartozik. Például:

    * *"Set a 30 second timer"* - ez egy számot tartalmaz, `30`, és egy időegységet, `second`, így az egyetlen szám az egyetlen időegységhez fog tartozni.
    * *"Set a 2 minute and 30 second timer"* - ez két számot tartalmaz, `2` és `30`, valamint két időegységet, `minute` és `second`, így az első szám az első időegységhez fog tartozni (2 perc), a második szám pedig a második időegységhez (30 másodperc).

    A következő kód megszámolja az elemeket a `number` entitásokban, és ezt használja az első elem kinyerésére minden tömbből, majd a második elemre és így tovább. Add hozzá ezt az `if` blokkba.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    *"Set a four minute 17 second timer."* esetén ez kétszer fog végrehajtódni, a következő értékeket adva:

    | ciklus száma | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. Ebben a ciklusban használd a számot és az időegységet az időzítő teljes idejének kiszámításához, hozzáadva 60 másodpercet minden percért, és a másodpercek számát minden másodpercért.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. A cikluson kívül az entitásokon keresztül, írd ki az időzítő teljes idejét:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. A másodpercek számát HTTP válaszként kell visszaadni a függvényből. Az `if` blokk végén add hozzá a következőt:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Ez a kód létrehoz egy payloadot, amely tartalmazza az időzítő teljes másodperceinek számát, JSON karakterlánccá alakítja, és HTTP eredményként visszaadja 200-as státuszkóddal, ami azt jelenti, hogy a hívás sikeres volt.

1. Végül, az `if` blokkon kívül kezeld azt az esetet, ha a szándékot nem ismerték fel, és adj vissza egy hibakódot:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    A 404 a *nem található* státuszkód.

1. Futtasd a funkcióalkalmazást, és teszteld curl segítségével.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Cseréld ki `<text>`-et a kérés szövegére, például `set a 2 minutes 27 second timer`.

    A funkcióalkalmazás a következő kimenetet fogja adni:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    A curl hívás a következőt fogja visszaadni:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Az időzítő másodperceinek száma a `"seconds"` értékben található.

> 💁 Ezt a kódot megtalálhatod a [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions) mappában.

### Feladat - tedd elérhetővé a funkciódat az IoT eszközöd számára

1. Ahhoz, hogy az IoT eszközöd hívhassa a REST végpontodat, ismernie kell az URL-t. Amikor korábban hozzáfértél, a `localhost`-ot használtad, ami egy rövidítés a helyi gépen lévő REST végpontok elérésére. Ahhoz, hogy az IoT eszközöd hozzáférjen, vagy publikálnod kell a felhőbe, vagy meg kell szerezned az IP címedet a helyi eléréshez.

    > ⚠️ Ha Wio Terminalt használsz, könnyebb helyben futtatni a funkcióalkalmazást, mivel lesznek olyan könyvtárfüggőségek, amelyek miatt nem tudod ugyanúgy telepíteni a funkcióalkalmazást, mint korábban. Futtasd a funkcióalkalmazást helyben, és érj el hozzá a számítógéped IP címén keresztül. Ha a felhőbe szeretnéd telepíteni, későbbi leckékben információt kapsz arról, hogyan lehet ezt megtenni.

    * Publikáld a Functions alkalmazást - kövesd a korábbi leckékben található utasításokat a funkcióalkalmazás felhőbe való publikálásához. Miután publikáltad, az URL a következő lesz: `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, ahol `<APP_NAME>` a funkcióalkalmazásod neve lesz. Ügyelj arra, hogy a helyi beállításokat is publikáld.

      HTTP triggerek esetén alapértelmezés szerint egy funkcióalkalmazás kulccsal vannak biztosítva. Ennek a kulcsnak a megszerzéséhez futtasd a következő parancsot:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Másold ki a `default` bejegyzés értékét a `functionKeys` szekcióból.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Ezt a kulcsot hozzá kell adni az URL-hez lekérdezési paraméterként, így a végső URL a következő lesz: `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, ahol `<APP_NAME>` a funkcióalkalmazásod neve, és `<FUNCTION_KEY>` az alapértelmezett funkciókulcsod.

      > 💁 Az HTTP trigger engedélyezési típusát az `authlevel` beállítással módosíthatod a `function.json` fájlban. Erről többet olvashatsz az [Azure Functions HTTP trigger dokumentációjának konfigurációs szekciójában a Microsoft Docs-on](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Futtasd a funkcióalkalmazást helyben, és érj el hozzá az IP címen keresztül - megszerezheted a számítógéped IP címét a helyi hálózaton, és ezt használhatod az URL felépítéséhez.

      Szerezd meg az IP címedet:

      * Windows 10-en kövesd az [IP cím megtalálása útmutatót](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)
      * macOS-en kövesd a [Hogyan találhatod meg az IP címedet Mac-en útmutatót](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)
      * Linuxon kövesd az [Hogyan találhatod meg az IP címedet Linuxon útmutató](https://opensource.com/article/18/5/how-find-ip-address-linux) privát IP cím szekcióját.

      Miután megszerezted az IP címedet, a funkciót elérheted a következő címen: `http://`.

:7071/api/text-to-timer`, ahol `<IP_ADDRESS>` az IP-címed lesz, például `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Ne feledd, hogy ez a 7071-es portot használja, így az IP-cím után szükséges a `:7071`.

      > 💁 Ez csak akkor fog működni, ha az IoT eszközöd ugyanazon a hálózaton van, mint a számítógéped.

1. Teszteld az endpointot curl segítségével.

---

## 🚀 Kihívás

Számos módja van ugyanannak a kérésnek, például egy időzítő beállításának. Gondolj különböző módokra, hogyan lehet ezt megtenni, és használd ezeket példaként a LUIS alkalmazásodban. Teszteld ezeket, hogy lásd, mennyire jól tudja a modelled kezelni az időzítő beállításának különböző módjait.

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Áttekintés és önálló tanulás

* Olvass többet a LUIS-ról és annak képességeiről a [Language Understanding (LUIS) dokumentációs oldalán a Microsoft Docs-on](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Olvass többet a nyelvi megértésről a [natural-language understanding oldalán a Wikipédián](https://wikipedia.org/wiki/Natural-language_understanding)
* Olvass többet az HTTP trigger-ekről az [Azure Functions HTTP trigger dokumentációjában a Microsoft Docs-on](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Feladat

[Időzítő törlése](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.