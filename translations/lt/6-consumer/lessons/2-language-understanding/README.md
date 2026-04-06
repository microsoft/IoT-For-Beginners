# Supraskite kalbą

![Šios pamokos apžvalga piešinyje](../../../../../translated_images/lt/lesson-22.6148ea28500d9e00.webp)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

## Klausimynas prieš paskaitą

[Klausimynas prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Įvadas

Paskutinėje pamokoje jūs konvertavote kalbą į tekstą. Kad tai būtų galima panaudoti išmaniojo laikmačio programavimui, jūsų kodas turės suprasti, kas buvo pasakyta. Galėtumėte manyti, kad vartotojas pasakys fiksuotą frazę, pavyzdžiui, „Nustatyk 3 minučių laikmatį“, ir analizuoti tą išraišką, kad nustatytumėte laikmačio trukmę, tačiau tai nėra labai patogu vartotojui. Jei vartotojas pasakytų „Nustatyk laikmatį 3 minutėms“, jūs ar aš suprastume, ką jis turi omenyje, tačiau jūsų kodas nesuprastų, nes jis tikisi fiksuotos frazės.

Čia į pagalbą ateina kalbos supratimas, naudojant dirbtinio intelekto modelius tekstui interpretuoti ir grąžinti reikalingas detales, pavyzdžiui, sugebant suprasti tiek „Nustatyk 3 minučių laikmatį“, tiek „Nustatyk laikmatį 3 minutėms“ ir suprasti, kad reikia laikmačio 3 minutėms.

Šioje pamokoje jūs sužinosite apie kalbos supratimo modelius, kaip juos kurti, treniruoti ir naudoti savo kode.

Šioje pamokoje aptarsime:

* [Kalbos supratimą](../../../../../6-consumer/lessons/2-language-understanding)
* [Kalbos supratimo modelio kūrimą](../../../../../6-consumer/lessons/2-language-understanding)
* [Ketinimus ir esybes](../../../../../6-consumer/lessons/2-language-understanding)
* [Kalbos supratimo modelio naudojimą](../../../../../6-consumer/lessons/2-language-understanding)

## Kalbos supratimas

Žmonės naudoja kalbą bendravimui jau šimtus tūkstančių metų. Mes bendraujame žodžiais, garsais ar veiksmais ir suprantame, kas buvo pasakyta – tiek žodžių, garsų ar veiksmų reikšmę, tiek jų kontekstą. Mes suprantame nuoširdumą ir sarkazmą, leidžiantį tiems patiems žodžiams reikšti skirtingus dalykus, priklausomai nuo balso tono.

✅ Pagalvokite apie kai kuriuos pokalbius, kuriuos neseniai turėjote. Kiek iš jų būtų sunku suprasti kompiuteriui, nes jiems reikia konteksto?

Kalbos supratimas, dar vadinamas natūralios kalbos supratimu, yra dirbtinio intelekto srities, vadinamos natūralios kalbos apdorojimu (arba NLP), dalis ir susijęs su skaitymo suvokimu, bandant suprasti žodžių ar sakinių detales. Jei naudojate balso asistentą, pvz., Alexa ar Siri, jūs jau naudojatės kalbos supratimo paslaugomis. Tai yra užkulisinės dirbtinio intelekto paslaugos, kurios paverčia „Alexa, paleisk naujausią Taylor Swift albumą“ į mano dukrą, šokančią svetainėje pagal savo mėgstamas dainas.

> 💁 Nepaisant visų kompiuterių pažangų, jie vis dar turi nueiti ilgą kelią, kad tikrai suprastų tekstą. Kai kalbame apie kalbos supratimą kompiuteriuose, mes neturime omenyje nieko, kas būtų bent kiek panašu į žmogaus bendravimą. Vietoj to, mes turime omenyje žodžių paėmimą ir pagrindinių detalių išgavimą.

Kaip žmonės, mes suprantame kalbą beveik negalvodami apie tai. Jei paprašyčiau kito žmogaus „paleisti naujausią Taylor Swift albumą“, jis instinktyviai suprastų, ką turiu omenyje. Kompiuteriui tai yra sudėtingiau. Jis turėtų paimti žodžius, konvertuotus iš kalbos į tekstą, ir išsiaiškinti šiuos informacijos gabalus:

* Reikia paleisti muziką
* Muzika yra Taylor Swift kūryba
* Konkretus kūrinys yra visas albumas, sudarytas iš kelių takelių tam tikra tvarka
* Taylor Swift turi daug albumų, todėl juos reikia surūšiuoti chronologine tvarka, o naujausias yra tas, kurio reikia

✅ Pagalvokite apie kitus sakinius, kuriuos sakėte, kai darėte užklausas, pvz., užsisakydami kavą ar prašydami šeimos nario paduoti ką nors. Pabandykite suskaidyti juos į informacijos dalis, kurias kompiuteris turėtų išgauti, kad suprastų sakinį.

Kalbos supratimo modeliai yra dirbtinio intelekto modeliai, kurie yra apmokomi išgauti tam tikras detales iš kalbos, o tada yra apmokomi konkrečioms užduotims naudojant perkėlimo mokymą, taip pat kaip jūs apmokėte „Custom Vision“ modelį naudodami nedidelį vaizdų rinkinį. Galite paimti modelį, tada jį apmokyti naudodami tekstą, kurį norite, kad jis suprastų.

## Kalbos supratimo modelio kūrimas

![LUIS logotipas](../../../../../translated_images/lt/luis-logo.5cb4f3e88c020ee6.webp)

Galite kurti kalbos supratimo modelius naudodami LUIS – „Microsoft“ kalbos supratimo paslaugą, kuri yra „Cognitive Services“ dalis.

### Užduotis – sukurti autorių išteklių

Norėdami naudoti LUIS, turite sukurti autorių išteklių.

1. Naudokite šią komandą, kad sukurtumėte autorių išteklių savo `smart-timer` išteklių grupėje:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Pakeiskite `<location>` vieta, kurią naudojote kurdami išteklių grupę.

    > ⚠️ LUIS nėra prieinamas visose regionuose, todėl jei gausite šią klaidą:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > pasirinkite kitą regioną.

    Tai sukurs nemokamą LUIS autorių išteklių.

### Užduotis – sukurti kalbos supratimo programą

1. Atidarykite LUIS portalą [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) savo naršyklėje ir prisijunkite naudodami tą pačią paskyrą, kurią naudojote „Azure“.

1. Sekite dialogo instrukcijas, kad pasirinktumėte savo „Azure“ prenumeratą, tada pasirinkite ką tik sukurtą `smart-timer-luis-authoring` išteklių.

1. Iš *Conversation apps* sąrašo pasirinkite **New app** mygtuką, kad sukurtumėte naują programą. Pavadinkite naują programą `smart-timer` ir nustatykite *Culture* savo kalbai.

    > 💁 Yra laukas prognozavimo ištekliui. Galite sukurti antrą išteklių tik prognozavimui, tačiau nemokamas autorių išteklius leidžia atlikti 1 000 prognozių per mėnesį, kas turėtų būti pakankama kūrimui, todėl galite palikti šį lauką tuščią.

1. Perskaitykite vadovą, kuris pasirodys sukūrus programą, kad suprastumėte veiksmus, kuriuos reikia atlikti norint apmokyti kalbos supratimo modelį. Uždarykite šį vadovą, kai baigsite.

## Ketinimai ir esybės

Kalbos supratimas pagrįstas *ketinimais* ir *esybėmis*. Ketinimai yra tai, ką žodžiai reiškia, pavyzdžiui, muzikos paleidimas, laikmačio nustatymas ar maisto užsakymas. Esybės yra tai, į ką ketinimas nukreiptas, pavyzdžiui, albumas, laikmačio trukmė ar maisto rūšis. Kiekvienas sakinys, kurį modelis interpretuoja, turėtų turėti bent vieną ketinimą ir, jei reikia, vieną ar daugiau esybių.

Keletas pavyzdžių:

| Sakinys                                              | Ketinimas        | Esybės                                     |
| ---------------------------------------------------- | ---------------- | ------------------------------------------ |
| „Paleisk naujausią Taylor Swift albumą“             | *paleisti muziką*| *naujausias Taylor Swift albumas*          |
| „Nustatyk 3 minučių laikmatį“                       | *nustatyti laikmatį* | *3 minutės*                                |
| „Atšauk mano laikmatį“                              | *atšaukti laikmatį* | Nėra                                       |
| „Užsisakyk 3 dideles picos su ananasais ir Cezario salotas“ | *užsisakyti maisto* | *3 didelės picos su ananasais*, *Cezario salotos* |

✅ Su sakiniais, apie kuriuos galvojote anksčiau, koks būtų ketinimas ir kokios būtų esybės tame sakinyje?

Norint apmokyti LUIS, pirmiausia reikia nustatyti esybes. Jos gali būti fiksuotas terminų sąrašas arba išmoktos iš teksto. Pavyzdžiui, galite pateikti fiksuotą meniu maisto sąrašą su kiekvieno žodžio variantais (arba sinonimais), pvz., *baklažanas* ir *auberginas* kaip *aubergino* variantus. LUIS taip pat turi iš anksto sukurtas esybes, kurios gali būti naudojamos, pvz., skaičiai ir vietos.

Norint nustatyti laikmatį, galite turėti vieną esybę, naudojant iš anksto sukurtą skaičių esybę laikui, ir kitą vienetams, pvz., minutėms ir sekundėms. Kiekvienas vienetas turėtų turėti kelis variantus, kad apimtų vienaskaitos ir daugiskaitos formas – pvz., minutė ir minutės.

Kai esybės yra apibrėžtos, sukuriate ketinimus. Jie yra išmokomi modelio remiantis pateiktais pavyzdiniais sakiniais (vadinamais *utterances*). Pavyzdžiui, ketinimui *nustatyti laikmatį* galite pateikti šiuos sakinius:

* `nustatyk 1 sekundės laikmatį`
* `nustatyk laikmatį 1 minutei ir 12 sekundžių`
* `nustatyk laikmatį 3 minutėms`
* `nustatyk 9 minučių 30 sekundžių laikmatį`

Tada nurodote LUIS, kurios sakinio dalys atitinka esybes:

![Sakinys „nustatyk laikmatį 1 minutei ir 12 sekundžių“ suskaidytas į esybes](../../../../../translated_images/lt/sentence-as-intent-entities.301401696f992259.webp)

Sakinys `nustatyk laikmatį 1 minutei ir 12 sekundžių` turi ketinimą `nustatyti laikmatį`. Jame taip pat yra 2 esybės su 2 reikšmėmis kiekviena:

|            | laikas | vienetas   |
| ---------- | ---: | ------ |
| 1 minutė   | 1    | minutė |
| 12 sekundžių | 12   | sekundė |

Norint apmokyti gerą modelį, reikia įvairių pavyzdinių sakinių, kad būtų apimti visi skirtingi būdai, kaip kas nors gali paprašyti to paties dalyko.

> 💁 Kaip ir su bet kuriuo dirbtinio intelekto modeliu, kuo daugiau duomenų ir kuo tikslesni duomenys naudojami mokymui, tuo geresnis modelis.

✅ Pagalvokite apie skirtingus būdus, kaip galėtumėte paprašyti to paties dalyko ir tikėtis, kad žmogus supras.

### Užduotis – pridėti esybes prie kalbos supratimo modelių

Laikmačiui reikia pridėti 2 esybes – vieną laiko vienetui (minutėms ar sekundėms) ir vieną skaičiui minučių ar sekundžių.

Instrukcijas, kaip naudoti LUIS portalą, galite rasti [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. LUIS portale pasirinkite *Entities* skirtuką ir pridėkite iš anksto sukurtą *number* esybę, pasirinkdami **Add prebuilt entity** mygtuką, tada pasirinkdami *number* iš sąrašo.

1. Sukurkite naują esybę laiko vienetui naudodami **Create** mygtuką. Pavadinkite esybę `time unit` ir nustatykite tipą kaip *List*. Pridėkite reikšmes `minute` ir `second` į *Normalized values* sąrašą, pridėdami vienaskaitos ir daugiskaitos formas į *synonyms* sąrašą. Paspauskite `return` po kiekvieno sinonimo pridėjimo, kad pridėtumėte jį į sąrašą.

    | Normalizuota reikšmė | Sinonimai        |
    | -------------------- | --------------- |
    | minute               | minute, minutes |
    | second               | second, seconds |

### Užduotis – pridėti ketinimus prie kalbos supratimo modelių

1. Iš *Intents* skirtuko pasirinkite **Create** mygtuką, kad sukurtumėte naują ketinimą. Pavadinkite šį ketinimą `set timer`.

1. Pavyzdžiuose įveskite skirtingus būdus, kaip nustatyti laikmatį, naudojant tiek minutes, tiek sekundes, tiek jų kombinacijas. Pavyzdžiai galėtų būti:

    * `nustatyk 1 sekundės laikmatį`
    * `nustatyk 4 minučių laikmatį`
    * `nustatyk keturių minučių šešių sekundžių laikmatį`
    * `nustatyk 9 minučių 30 sekundžių laikmatį`
    * `nustatyk laikmatį 1 minutei ir 12 sekundžių`
    * `nustatyk laikmatį 3 minutėms`
    * `nustatyk laikmatį 3 minutėms ir 1 sekundei`
    * `nustatyk laikmatį trims minutėms ir vienai sekundei`
    * `nustatyk laikmatį 1 minutei ir 1 sekundei`
    * `nustatyk laikmatį 30 sekundėms`
    * `nustatyk laikmatį 1 sekundei`

    Maišykite skaičius kaip žodžius ir skaitmenis, kad modelis išmoktų apdoroti abu.

1. Kai įvesite kiekvieną pavyzdį, LUIS pradės aptikti esybes ir pabrauks bei pažymės bet kurias rastas.

    ![Pavyzdžiai su pabrauktais skaičiais ir laiko vienetais, kuriuos aptiko LUIS](../../../../../translated_images/lt/luis-intent-examples.25716580b2d2723c.webp)

### Užduotis – apmokyti ir išbandyti modelį

1. Kai esybės ir ketinimai yra sukonfigūruoti, galite apmokyti modelį naudodami **Train** mygtuką viršutiniame meniu. Pasirinkite šį mygtuką, ir modelis turėtų būti apmokytas per kelias sekundes. Mygtukas bus pilkas mokymo metu ir vėl aktyvus, kai mokymas bus baigtas.

1. Pasirinkite **Test** mygtuką iš viršutinio meniu, kad išbandytumėte kalbos supratimo modelį. Įveskite tekstą, pvz., `nustatyk laikmatį 5 minutėms ir 4 sekundėms`, ir paspauskite Enter. Sakinys pasirodys dėžutėje po teksto laukeliu, į kurį jį įvedėte, o po juo bus *top intent* arba ketinimas, kuris buvo aptiktas su didžiausia tikimybe. Tai turėtų būti `set timer`. Ketinimo pavadinimas bus pateiktas kartu su tikimybe, kad aptiktas ketinimas yra teisingas.

1. Pasirinkite **Inspect** parinktį, kad pamatytumėte rezultatų suskirstymą. Matysite aukščiausią ketinimą su jo procentine tikimybe, taip pat aptiktų esybių sąrašus.

1. Uždarykite *Test* langą, kai baigsite testavimą.

### Užduotis – publikuoti modelį

Norėdami naudoti šį modelį iš kodo, turite jį publiku
1. Iš *Azure Resources* skyriaus pasirinkite *Authoring Resource* ir nukopijuokite *Primary Key* bei *Endpoint URL*.

1. Paleiskite šią curl komandą savo komandinėje eilutėje arba terminale:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Pakeiskite `<endpoint url>` į Endpoint URL iš *Azure Resources* skyriaus.

    Pakeiskite `<app id>` į App ID iš *Settings* skyriaus.

    Pakeiskite `<primary key>` į Primary Key iš *Azure Resources* skyriaus.

    Pakeiskite `<sentence>` į sakinį, kurį norite išbandyti.

1. Šios užklausos rezultatas bus JSON dokumentas, kuriame pateikiama užklausos informacija, pagrindinis ketinimas ir sąrašas objektų, suskirstytų pagal tipus.

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

    Aukščiau pateiktas JSON buvo gautas užklausus su `set a timer for 45 minutes and 12 seconds`:

    * `set timer` buvo pagrindinis ketinimas su 97% tikimybe.
    * Buvo aptikti du *number* objektai: `45` ir `12`.
    * Buvo aptikti du *time-unit* objektai: `minute` ir `second`.

## Naudokite kalbos supratimo modelį

Kai modelis LUIS yra publikuotas, jį galima iškviesti iš kodo. Ankstesnėse pamokose naudojote IoT Hub, kad galėtumėte bendrauti su debesų paslaugomis, siųsti telemetriją ir klausytis komandų. Tai labai asinchroniška - kai telemetrija išsiunčiama, jūsų kodas nelaukia atsakymo, ir jei debesų paslauga neveikia, jūs to nežinotumėte.

Išmaniam laikmačiui norime gauti atsakymą iš karto, kad galėtume informuoti vartotoją, jog laikmatis nustatytas, arba perspėti, kad debesų paslaugos nepasiekiamos. Tam mūsų IoT įrenginys tiesiogiai iškvies internetinį endpoint'ą, o ne pasikliaus IoT Hub.

Užuot iškvietę LUIS tiesiogiai iš IoT įrenginio, galite naudoti serverless kodą su kitokio tipo trigeriu - HTTP trigeriu. Tai leidžia jūsų funkcijų programai klausytis REST užklausų ir atsakyti į jas. Ši funkcija bus REST endpoint'as, kurį jūsų įrenginys galės iškviesti.

> 💁 Nors galite tiesiogiai iškviesti LUIS iš savo IoT įrenginio, geriau naudoti serverless kodą. Tokiu būdu, kai norėsite pakeisti LUIS programą, kurią iškviečiate, pavyzdžiui, kai apmokysite geresnį modelį arba modelį kita kalba, jums reikės atnaujinti tik debesų kodą, o ne perrašyti kodą potencialiai tūkstančiams ar milijonams IoT įrenginių.

### Užduotis - sukurkite serverless funkcijų programą

1. Sukurkite Azure Functions programą, pavadintą `smart-timer-trigger`, ir atidarykite ją VS Code.

1. Pridėkite HTTP trigerį šiai programai, pavadintą `speech-trigger`, naudodami šią komandą iš VS Code terminalo:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Tai sukurs HTTP trigerį, pavadintą `text-to-timer`.

1. Išbandykite HTTP trigerį paleisdami funkcijų programą. Kai ji veiks, pamatysite endpoint'ą išvestyje:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Išbandykite tai įkeldami [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) URL į savo naršyklę.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Užduotis - naudokite kalbos supratimo modelį

1. LUIS SDK yra pasiekiamas per Pip paketą. Pridėkite šią eilutę į `requirements.txt` failą, kad pridėtumėte priklausomybę nuo šio paketo:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Įsitikinkite, kad VS Code terminale aktyvuota virtuali aplinka, ir paleiskite šią komandą, kad įdiegtumėte Pip paketus:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Jei gaunate klaidų, gali reikėti atnaujinti pip naudojant šią komandą:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Pridėkite naujus įrašus į `local.settings.json` failą savo LUIS API Key, Endpoint URL ir App ID iš **MANAGE** skyriaus LUIS portale:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Pakeiskite `<endpoint url>` į Endpoint URL iš *Azure Resources* skyriaus **MANAGE** skyriaus. Tai bus `https://<location>.api.cognitive.microsoft.com/`.

    Pakeiskite `<app id>` į App ID iš *Settings* skyriaus **MANAGE** skyriaus.

    Pakeiskite `<primary key>` į Primary Key iš *Azure Resources* skyriaus **MANAGE** skyriaus.

1. Pridėkite šiuos importus į `__init__.py` failą:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Tai importuoja kai kurias sistemos bibliotekas, taip pat bibliotekas, skirtas sąveikai su LUIS.

1. Ištrinkite `main` metodo turinį ir pridėkite šį kodą:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Tai įkelia vertes, kurias pridėjote į `local.settings.json` failą savo LUIS programai, sukuria kredencialų objektą su jūsų API raktu, tada sukuria LUIS klientą sąveikai su jūsų LUIS programa.

1. Šis HTTP trigeris bus iškviečiamas perduodant tekstą suprasti kaip JSON, su tekstu savybėje `text`. Šis kodas ištraukia vertę iš HTTP užklausos kūno ir įrašo ją į konsolę. Pridėkite šį kodą į `main` funkciją:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Prognozės iš LUIS yra prašomos siunčiant prognozės užklausą - JSON dokumentą, kuriame yra tekstas prognozuoti. Sukurkite tai naudodami šį kodą:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Ši užklausa gali būti siunčiama į LUIS, naudojant jūsų programos publikuotą staging slot'ą:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Prognozės atsakyme yra pagrindinis ketinimas - ketinimas su didžiausiu prognozės balu, kartu su objektais. Jei pagrindinis ketinimas yra `set timer`, tada objektai gali būti perskaityti, kad gautumėte laikmačio laiką:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number` objektai bus skaičių masyvas. Pavyzdžiui, jei pasakėte *"Set a four minute 17 second timer."*, tada `number` masyvas turės 2 sveikus skaičius - 4 ir 17.

    `time unit` objektai bus masyvas masyvų su eilutėmis, kur kiekvienas laiko vienetas yra masyvas eilutėse. Pavyzdžiui, jei pasakėte *"Set a four minute 17 second timer."*, tada `time unit` masyvas turės 2 masyvus su vienu elementu kiekviename - `['minute']` ir `['second']`.

    JSON versija šių objektų *"Set a four minute 17 second timer."* yra:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Šis kodas taip pat apibrėžia bendrą laiką laikmačiui sekundėmis. Tai bus užpildyta vertėmis iš objektų.

1. Objektai nėra susieti, bet galime daryti tam tikras prielaidas apie juos. Jie bus tokia tvarka, kokia buvo pasakyta, todėl pozicija masyve gali būti naudojama nustatyti, kuris skaičius atitinka kurį laiko vienetą. Pavyzdžiui:

    * *"Set a 30 second timer"* - tai turės vieną skaičių, `30`, ir vieną laiko vienetą, `second`, todėl vienas skaičius atitiks vieną laiko vienetą.
    * *"Set a 2 minute and 30 second timer"* - tai turės du skaičius, `2` ir `30`, ir du laiko vienetus, `minute` ir `second`, todėl pirmas skaičius bus pirmam laiko vienetui (2 minutės), o antras skaičius - antram laiko vienetui (30 sekundžių).

    Šis kodas gauna objektų skaičių masyve ir naudoja tai ištraukti pirmą elementą iš kiekvieno masyvo, tada antrą ir t. t. Pridėkite tai į `if` bloką.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Pavyzdžiui, *"Set a four minute 17 second timer."*, šis kodas kartosis du kartus, pateikdamas šias vertes:

    | ciklo skaičius | `number` | `time_unit` |
    | --------------: | -------: | ----------- |
    | 0               | 4        | minute      |
    | 1               | 17       | second      |

1. Šiame cikle naudokite skaičių ir laiko vienetą, kad apskaičiuotumėte bendrą laiką laikmačiui, pridėdami 60 sekundžių už kiekvieną minutę ir skaičių sekundžių už bet kokias sekundes.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Už šio ciklo per objektus, įrašykite bendrą laiką laikmačiui:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Sekundžių skaičius turi būti grąžintas iš funkcijos kaip HTTP atsakymas. `if` bloko pabaigoje pridėkite šį kodą:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Šis kodas sukuria payload'ą, kuriame yra bendras sekundžių skaičius laikmačiui, konvertuoja jį į JSON eilutę ir grąžina kaip HTTP rezultatą su statuso kodu 200, kuris reiškia, kad užklausa buvo sėkminga.

1. Galiausiai, už `if` bloko, apdorokite, jei ketinimas nebuvo atpažintas, grąžindami klaidos kodą:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 yra statuso kodas, reiškiantis *nerasta*.

1. Paleiskite funkcijų programą ir išbandykite ją naudodami curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Pakeiskite `<text>` į savo užklausos tekstą, pavyzdžiui, `set a 2 minutes 27 second timer`.

    Pamatysite šią išvestį iš funkcijų programos:

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

    Curl užklausa grąžins šį rezultatą:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Sekundžių skaičius laikmačiui yra `"seconds"` reikšmėje.

> 💁 Šį kodą galite rasti [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions) aplanke.

### Užduotis - padarykite savo funkciją prieinamą IoT įrenginiui

1. Kad jūsų IoT įrenginys galėtų iškviesti jūsų REST endpoint'ą, jam reikės žinoti URL. Kai anksčiau prie jo prisijungėte, naudojote `localhost`, kuris yra nuoroda į REST endpoint'us jūsų vietiniame kompiuteryje. Kad jūsų IoT įrenginys galėtų pasiekti, turite arba publikuoti į debesį, arba gauti savo IP adresą, kad pasiektumėte vietoje.

    > ⚠️ Jei naudojate Wio Terminal, lengviau paleisti funkcijų programą vietoje, nes bus priklausomybė nuo bibliotekų, kurios reiškia, kad negalite publikuoti funkcijų programos taip, kaip darėte anksčiau. Paleiskite funkcijų programą vietoje ir pasiekite ją per savo kompiuterio IP adresą. Jei vis dėlto norite publikuoti į debesį, informacija apie tai bus pateikta vėlesnėje pamokoje.

    * Publikuokite funkcijų programą - sekite instrukcijas ankstesnėse pamokose, kad publikuotumėte savo funkcijų programą į debesį. Kai publikuota, URL bus `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, kur `<APP_NAME>` bus jūsų funkcijų programos pavadinimas. Įsitikinkite, kad taip pat publikuojate savo vietinius nustatymus.

      Dirbant su HTTP trigeriais, jie pagal numatymą yra apsaugoti funkcijų programos raktu. Norėdami gauti šį raktą, paleiskite šią komandą:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Nukopijuokite `default` įrašo reikšmę iš `functionKeys` skyriaus.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Šis raktas turi būti pridėtas kaip užklausos parametras prie URL, todėl galutinis URL bus `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, kur `<APP_NAME>` bus jūsų funkcijų programos pavadinimas, o `<FUNCTION_KEY>` bus jūsų numatytasis funkcijų raktas.

      > 💁 Galite pakeisti HTTP trigerio autorizacijos tipą naudodami `authlevel` nustatymą `function.json` faile. Daugiau apie tai galite perskaityti [Azure Functions HTTP trigerio dokumentacijoje Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Paleiskite funkcijų programą vietoje ir pasiekite naudodami IP adresą - galite gauti savo kompiuterio IP adresą vietiniame tinkle ir naudoti jį URL kūrimui.

      Raskite savo IP adresą:

      * Windows 10, sekite [kaip rasti IP adresą](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)
      * macOS, sekite [kaip rasti IP adresą Mac'e](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)
      * Linux, sekite skyrių apie privatų IP adresą [kaip rasti IP adresą Linux'e](https://opensource.com/article/18/5/how-find-ip-address-linux)

      Kai turėsite savo IP adresą, galėsite pasiekti funkciją adresu `http://`.

:7071/api/text-to-timer`, kur `<IP_ADDRESS>` bus jūsų IP adresas, pavyzdžiui, `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Atkreipkite dėmesį, kad čia naudojamas prievadas 7071, todėl po IP adreso turėsite pridėti `:7071`.

      > 💁 Tai veiks tik tuo atveju, jei jūsų IoT įrenginys yra toje pačioje tinkle kaip ir jūsų kompiuteris.

1. Išbandykite galinį tašką, pasiekdami jį naudodami curl.

---

## 🚀 Iššūkis

Yra daug būdų paprašyti to paties dalyko, pavyzdžiui, nustatyti laikmatį. Pagalvokite apie skirtingus būdus tai padaryti ir naudokite juos kaip pavyzdžius savo LUIS programoje. Išbandykite juos, kad pamatytumėte, kaip gerai jūsų modelis gali susidoroti su įvairiais laikmačio nustatymo būdais.

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Apžvalga ir savarankiškas mokymasis

* Skaitykite daugiau apie LUIS ir jo galimybes [Language Understanding (LUIS) dokumentacijos puslapyje Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Skaitykite daugiau apie kalbos supratimą [natūralios kalbos supratimo puslapyje Vikipedijoje](https://wikipedia.org/wiki/Natural-language_understanding)
* Skaitykite daugiau apie HTTP trigerius [Azure Functions HTTP trigerio dokumentacijoje Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Užduotis

[Atšaukti laikmatį](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipkite dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.