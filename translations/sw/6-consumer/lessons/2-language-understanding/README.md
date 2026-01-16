<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-27T21:02:27+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "sw"
}
-->
# Elewa Lugha

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa zaidi.

## Jaribio la kabla ya somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Utangulizi

Katika somo lililopita uligeuza sauti kuwa maandishi. Ili hili litumike kuendesha kipima muda cha kisasa, msimbo wako utahitaji kuelewa kilichosemwa. Unaweza kudhani mtumiaji atasema sentensi maalum, kama vile "Weka kipima muda cha dakika 3", na kuchanganua usemi huo ili kupata muda wa kipima muda, lakini hii si rafiki kwa mtumiaji. Ikiwa mtumiaji atasema "Weka kipima muda kwa dakika 3", wewe au mimi tutaelewa maana yake, lakini msimbo wako hautaelewa, kwani unatarajia sentensi maalum.

Hapa ndipo uelewa wa lugha unapoingia, kwa kutumia mifano ya AI kutafsiri maandishi na kurudisha maelezo yanayohitajika, kwa mfano, kuwa na uwezo wa kuelewa "Weka kipima muda cha dakika 3" na "Weka kipima muda kwa dakika 3", na kuelewa kuwa kipima muda kinahitajika kwa dakika 3.

Katika somo hili utajifunza kuhusu mifano ya uelewa wa lugha, jinsi ya kuunda, kuifundisha, na kuitumia kutoka kwa msimbo wako.

Katika somo hili tutashughulikia:

* [Uelewa wa lugha](../../../../../6-consumer/lessons/2-language-understanding)
* [Kuunda mfano wa uelewa wa lugha](../../../../../6-consumer/lessons/2-language-understanding)
* [Mikusudi na vyombo](../../../../../6-consumer/lessons/2-language-understanding)
* [Kutumia mfano wa uelewa wa lugha](../../../../../6-consumer/lessons/2-language-understanding)

## Uelewa wa lugha

Binadamu wamekuwa wakitumia lugha kuwasiliana kwa maelfu ya miaka. Tunawasiliana kwa maneno, sauti, au vitendo na kuelewa kilichosemwa, si tu maana ya maneno, sauti au vitendo, bali pia muktadha wake. Tunaelewa unyoofu na kejeli, tukiruhusu maneno yale yale kuwa na maana tofauti kulingana na sauti ya sauti yetu.

✅ Fikiria baadhi ya mazungumzo uliyokuwa nayo hivi karibuni. Ni kiasi gani cha mazungumzo hayo kingekuwa kigumu kwa kompyuta kuelewa kwa sababu kinahitaji muktadha?

Uelewa wa lugha, pia huitwa uelewa wa lugha asilia, ni sehemu ya uwanja wa akili bandia unaoitwa usindikaji wa lugha asilia (au NLP), na unahusiana na ufahamu wa kusoma, ukijaribu kuelewa maelezo ya maneno au sentensi. Ikiwa unatumia msaidizi wa sauti kama Alexa au Siri, umewahi kutumia huduma za uelewa wa lugha. Hizi ni huduma za AI zinazofanya kazi nyuma ya pazia kubadilisha "Alexa, cheza albamu mpya ya Taylor Swift" kuwa binti yangu akicheza sebuleni kwa nyimbo zake anazozipenda.

> 💁 Kompyuta, licha ya maendeleo yote, bado zina safari ndefu kufikia kuelewa maandishi kwa kina. Tunapozungumzia uelewa wa lugha kwa kompyuta, hatumaanishi kitu chochote karibu na mawasiliano ya kibinadamu, badala yake tunamaanisha kuchukua maneno na kutoa maelezo muhimu.

Kama binadamu, tunaelewa lugha bila kufikiria sana. Ikiwa ningemuuliza binadamu mwingine "cheza albamu mpya ya Taylor Swift" basi angeelewa mara moja ninachomaanisha. Kwa kompyuta, hili ni gumu zaidi. Itabidi ichukue maneno, yaliyobadilishwa kutoka sauti kuwa maandishi, na kuchambua vipande vifuatavyo vya taarifa:

* Muziki unahitaji kuchezwa
* Muziki ni wa msanii Taylor Swift
* Muziki maalum ni albamu nzima yenye nyimbo nyingi kwa mpangilio
* Taylor Swift ana albamu nyingi, kwa hivyo zinahitaji kupangwa kwa mpangilio wa muda na albamu iliyochapishwa hivi karibuni ndiyo inayohitajika

✅ Fikiria baadhi ya sentensi nyingine ulizozungumza wakati wa kufanya maombi, kama kuagiza kahawa au kumuomba mwanafamilia akupatie kitu. Jaribu kuzivunja katika vipande vya taarifa ambavyo kompyuta ingehitaji kutoa ili kuelewa sentensi.

Mifano ya uelewa wa lugha ni mifano ya AI inayofundishwa kutoa maelezo fulani kutoka kwa lugha, na kisha kufundishwa kwa kazi maalum kwa kutumia kujifunza kwa uhamisho, kwa njia ile ile ulivyofundisha mfano wa Custom Vision kwa kutumia seti ndogo ya picha. Unaweza kuchukua mfano, kisha kuufundisha kwa kutumia maandishi unayotaka kuelewa.

## Kuunda mfano wa uelewa wa lugha

![Nembo ya LUIS](../../../../../translated_images/sw/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.png)

Unaweza kuunda mifano ya uelewa wa lugha kwa kutumia LUIS, huduma ya uelewa wa lugha kutoka Microsoft ambayo ni sehemu ya Huduma za Utambuzi.

### Kazi - kuunda rasilimali ya uandishi

Ili kutumia LUIS, unahitaji kuunda rasilimali ya uandishi.

1. Tumia amri ifuatayo kuunda rasilimali ya uandishi katika kikundi chako cha rasilimali `smart-timer`:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Badilisha `<location>` na eneo ulilotumia wakati wa kuunda Kikundi cha Rasilimali.

    > ⚠️ LUIS haipatikani katika maeneo yote, kwa hivyo ikiwa utapata kosa lifuatalo:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > chagua eneo tofauti.

    Hii itaunda rasilimali ya uandishi ya kiwango cha bure.

### Kazi - kuunda programu ya uelewa wa lugha

1. Fungua lango la LUIS kwenye [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) kwenye kivinjari chako, na uingie kwa akaunti ile ile ambayo umekuwa ukitumia kwa Azure.

1. Fuata maagizo kwenye kisanduku cha mazungumzo ili kuchagua usajili wako wa Azure, kisha uchague rasilimali ya `smart-timer-luis-authoring` ambayo umeunda hivi punde.

1. Kutoka kwenye orodha ya *Programu za Mazungumzo*, chagua kitufe cha **Programu Mpya** ili kuunda programu mpya. Ipe jina programu mpya `smart-timer`, na weka *Utamaduni* kwa lugha yako.

    > 💁 Kuna sehemu ya rasilimali ya utabiri. Unaweza kuunda rasilimali ya pili kwa ajili ya utabiri, lakini rasilimali ya uandishi ya bure inaruhusu utabiri 1,000 kwa mwezi ambayo inapaswa kutosha kwa maendeleo, kwa hivyo unaweza kuiacha tupu.

1. Soma mwongozo unaoonekana mara tu unapounda programu ili kupata uelewa wa hatua unazohitaji kuchukua ili kufundisha mfano wa uelewa wa lugha. Funga mwongozo huu unapomaliza.

## Mikusudi na vyombo

Uelewa wa lugha unategemea *makusudi* na *vyombo*. Makusudi ni kile ambacho maneno yanakusudia, kwa mfano kucheza muziki, kuweka kipima muda, au kuagiza chakula. Vyombo ni kile makusudi yanarejelea, kama vile albamu, muda wa kipima muda, au aina ya chakula. Kila sentensi ambayo mfano unatafsiri inapaswa kuwa na angalau kusudi moja, na kwa hiari chombo kimoja au zaidi.

Baadhi ya mifano:

| Sentensi                                           | Kusudi           | Vyombo                                    |
| -------------------------------------------------- | ---------------- | ----------------------------------------- |
| "Cheza albamu mpya ya Taylor Swift"               | *cheza muziki*   | *albamu mpya ya Taylor Swift*            |
| "Weka kipima muda cha dakika 3"                   | *weka kipima muda* | *dakika 3*                               |
| "Futa kipima muda changu"                         | *futa kipima muda* | Hakuna                                   |
| "Agiza pizza 3 kubwa za mananasi na saladi ya caesar" | *agiza chakula*  | *pizza 3 kubwa za mananasi*, *saladi ya caesar* |

✅ Kwa sentensi ulizofikiria awali, ni nini kingekuwa kusudi na vyombo vyovyote katika sentensi hiyo?

Ili kufundisha LUIS, kwanza unaweka vyombo. Hivi vinaweza kuwa orodha ya maneno maalum, au kujifunza kutoka kwa maandishi. Kwa mfano, unaweza kutoa orodha ya chakula kinachopatikana kwenye menyu yako, na tofauti (au visawe) vya kila neno, kama vile *biringanya* na *auberjine* kama tofauti za *auberjine*. LUIS pia ina vyombo vilivyotengenezwa tayari ambavyo vinaweza kutumika, kama vile namba na maeneo.

Kwa kuweka kipima muda, unaweza kuwa na chombo kimoja kinachotumia vyombo vya namba vilivyotengenezwa tayari kwa muda, na kingine kwa vitengo, kama vile dakika na sekunde. Kila kitengo kingekuwa na tofauti nyingi kufunika umoja na wingi - kama vile dakika na dakika.

Baada ya kufafanua vyombo, unaunda makusudi. Haya yanajifunza na mfano kulingana na sentensi za mfano unazotoa (zinazojulikana kama matamshi). Kwa mfano, kwa kusudi la *weka kipima muda*, unaweza kutoa sentensi zifuatazo:

* `weka kipima muda cha sekunde 1`
* `weka kipima muda kwa dakika 1 na sekunde 12`
* `weka kipima muda kwa dakika 3`
* `weka kipima muda cha dakika 9 na sekunde 30`

Kisha unaiambia LUIS ni sehemu gani za sentensi hizi zinahusiana na vyombo:

![Sentensi "weka kipima muda kwa dakika 1 na sekunde 12" imegawanywa katika vyombo](../../../../../translated_images/sw/sentence-as-intent-entities.301401696f992259.webp)

Sentensi `weka kipima muda kwa dakika 1 na sekunde 12` ina kusudi la `weka kipima muda`. Pia ina vyombo 2 vyenye thamani 2 kila moja:

|            | muda | kitengo   |
| ---------- | ---: | --------- |
| 1 dakika   | 1    | dakika    |
| 12 sekunde | 12   | sekunde   |

Ili kufundisha mfano mzuri, unahitaji anuwai ya sentensi tofauti za mfano kufunika njia nyingi tofauti ambazo mtu anaweza kuuliza kitu kimoja.

> 💁 Kama ilivyo kwa mfano wowote wa AI, data zaidi na data sahihi zaidi unayotumia kufundisha, ndivyo mfano unavyokuwa bora zaidi.

✅ Fikiria njia tofauti unazoweza kuuliza kitu kimoja na kutarajia binadamu kuelewa.

### Kazi - kuongeza vyombo kwenye mifano ya uelewa wa lugha

Kwa kipima muda, unahitaji kuongeza vyombo 2 - kimoja kwa kitengo cha muda (dakika au sekunde), na kingine kwa idadi ya dakika au sekunde.

Unaweza kupata maagizo ya kutumia lango la LUIS katika [Mwongozo wa Haraka: Jenga programu yako katika nyaraka za lango la LUIS kwenye Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Kutoka kwenye lango la LUIS, chagua kichupo cha *Vyombo* na ongeza chombo kilichojengwa tayari cha *namba* kwa kuchagua kitufe cha **Ongeza chombo kilichojengwa tayari**, kisha uchague *namba* kutoka kwenye orodha.

1. Unda chombo kipya kwa ajili ya kitengo cha muda kwa kutumia kitufe cha **Unda**. Kipe jina chombo `kitengo cha muda` na weka aina kuwa *Orodha*. Ongeza thamani za `dakika` na `sekunde` kwenye orodha ya *Thamani Zilizowekwa Kawaida*, ukiongeza umoja na wingi kwenye orodha ya *Visawe*. Bonyeza `return` baada ya kuongeza kila kisawe ili kukiongeza kwenye orodha.

    | Thamani Iliyowekwa Kawaida | Visawe          |
    | -------------------------- | --------------- |
    | dakika                     | dakika, dakika  |
    | sekunde                    | sekunde, sekunde |

### Kazi - kuongeza makusudi kwenye mifano ya uelewa wa lugha

1. Kutoka kwenye kichupo cha *Makusudi*, chagua kitufe cha **Unda** ili kuunda kusudi jipya. Kipe jina kusudi hili `weka kipima muda`.

1. Katika mifano, ingiza njia tofauti za kuweka kipima muda kwa kutumia dakika, sekunde na mchanganyiko wa dakika na sekunde. Mifano inaweza kuwa:

    * `weka kipima muda cha sekunde 1`
    * `weka kipima muda cha dakika 4`
    * `weka kipima muda cha dakika nne na sekunde sita`
    * `weka kipima muda cha dakika 9 na sekunde 30`
    * `weka kipima muda kwa dakika 1 na sekunde 12`
    * `weka kipima muda kwa dakika 3`
    * `weka kipima muda kwa dakika 3 na sekunde 1`
    * `weka kipima muda kwa dakika tatu na sekunde moja`
    * `weka kipima muda kwa dakika 1 na sekunde 1`
    * `weka kipima muda kwa sekunde 30`
    * `weka kipima muda kwa sekunde 1`

    Changanya namba kama maneno na namba ili mfano ujifunze kushughulikia zote.

1. Unapoongeza kila mfano, LUIS itaanza kugundua vyombo, na itaweka mstari chini na kuweka lebo yoyote inayopatikana.

    ![Mifano na namba na vitengo vya muda vikiwa vimewekwa mstari chini na LUIS](../../../../../translated_images/sw/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.png)

### Kazi - kufundisha na kujaribu mfano

1. Mara vyombo na makusudi vimewekwa, unaweza kufundisha mfano kwa kutumia kitufe cha **Fundisha** kwenye menyu ya juu. Chagua kitufe hiki, na mfano unapaswa kufundishwa kwa sekunde chache. Kitufe kitakuwa kimezimwa wakati wa kufundisha, na kitawashwa tena mara baada ya kumaliza.

1. Chagua kitufe cha **Jaribu** kutoka kwenye menyu ya juu ili kujaribu mfano wa uelewa wa lugha. Ingiza maandishi kama `weka kipima muda kwa dakika 5 na sekunde 4` na bonyeza return. Sentensi itaonekana kwenye kisanduku chini ya kisanduku cha maandishi ulichotumia kuingiza, na chini yake kutakuwa na *kusudi kuu*, au kusudi lililogunduliwa kwa uwezekano wa juu zaidi. Hili linapaswa kuwa `weka kipima muda`. Jina la kusudi litafuatiwa na uwezekano kwamba kusudi lililogunduliwa ni sahihi.

1. Chagua chaguo la **Chunguza** ili kuona uchambuzi wa matokeo. Utaona kusudi lililopata alama ya juu zaidi na asilimia yake ya uwezekano, pamoja na orodha za vyombo vilivyogunduliwa.

1. Funga kidirisha cha *Jaribu* unapomaliza kujaribu.

### Kazi - kuchapisha mfano

Ili kutumia mfano huu kutoka kwa msimbo, unahitaji kuuchapisha. Unapochapisha kutoka LUIS, unaweza kuchapisha kwenye mazingira ya majaribio kwa kupima, au mazingira ya bidhaa kwa toleo kamili. Katika somo hili, mazingira ya majaribio yanatosha.

1. Kutoka kwenye lango la LUIS, chagua kitufe cha **Chapisha** kutoka kwenye menyu ya juu.

1. Hakikisha *Sehemu ya majaribio* imechaguliwa, kisha uchague **Imemaliza**. Utaona arifa wakati programu imechapishwa.

1. Unaweza kujaribu hili kwa kutumia curl. Ili kuunda amri ya curl, unahitaji maadili matatu - endpoint, ID ya programu (App ID) na API key. Hizi zinaweza kupatikana kutoka kwenye kichupo cha **MANAGE** kinachoweza kuchaguliwa kutoka kwenye menyu ya juu.

    1. Kutoka kwenye sehemu ya *Mipangilio*, nakili App ID
1. Kutoka sehemu ya *Azure Resources*, chagua *Authoring Resource*, na nakili *Primary Key* na *Endpoint URL*

1. Endesha amri ifuatayo ya curl kwenye command prompt au terminal yako:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Badilisha `<endpoint url>` na Endpoint URL kutoka sehemu ya *Azure Resources*.

    Badilisha `<app id>` na App ID kutoka sehemu ya *Settings*.

    Badilisha `<primary key>` na Primary Key kutoka sehemu ya *Azure Resources*.

    Badilisha `<sentence>` na sentensi unayotaka kujaribu nayo.

1. Matokeo ya mwito huu yatakuwa hati ya JSON inayotoa maelezo ya swali, nia kuu (*top intent*), na orodha ya viashiria (*entities*) vilivyogawanywa kulingana na aina.

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

    JSON hapo juu ilitokana na kuuliza `set a timer for 45 minutes and 12 seconds`:

    * `set timer` ilikuwa nia kuu (*top intent*) na uwezekano wa 97%.
    * Viashiria viwili vya *number* viligunduliwa, `45` na `12`.
    * Viashiria viwili vya *time-unit* viligunduliwa, `minute` na `second`.

## Tumia mfano wa uelewa wa lugha

Baada ya kuchapishwa, mfano wa LUIS unaweza kuitwa kutoka kwa msimbo. Katika masomo ya awali, umetumia IoT Hub kushughulikia mawasiliano na huduma za wingu, kutuma telemetry na kusikiliza amri. Hii ni asinkroni sana - mara telemetry inapowasilishwa msimbo wako hausubiri majibu, na ikiwa huduma za wingu ziko chini, hautajua.

Kwa kipima muda mahiri, tunataka majibu mara moja, ili tuweze kumwambia mtumiaji kuwa kipima muda kimewekwa, au kumjulisha kuwa huduma za wingu hazipatikani. Ili kufanya hivyo, kifaa chetu cha IoT kitaweza kupiga moja kwa moja kwenye *web endpoint*, badala ya kutegemea IoT Hub.

Badala ya kupiga LUIS moja kwa moja kutoka kwa kifaa cha IoT, unaweza kutumia msimbo usio na seva (*serverless code*) na aina tofauti ya kichochezi (*trigger*) - kichochezi cha HTTP. Hii inaruhusu programu yako ya kazi (*function app*) kusikiliza maombi ya REST, na kujibu.

> 💁 Ingawa unaweza kupiga LUIS moja kwa moja kutoka kwa kifaa chako cha IoT, ni bora kutumia kitu kama msimbo usio na seva. Kwa njia hii, unapohitaji kubadilisha programu ya LUIS unayopiga, kwa mfano unapofundisha mfano bora au mfano katika lugha tofauti, unahitaji tu kusasisha msimbo wa wingu, badala ya kupeleka tena msimbo kwa maelfu au mamilioni ya vifaa vya IoT.

### Kazi - unda programu ya kazi isiyo na seva

1. Unda programu ya Azure Functions inayoitwa `smart-timer-trigger`, na ifungue kwenye VS Code.

1. Ongeza kichochezi cha HTTP kwenye programu hii kinachoitwa `speech-trigger` ukitumia amri ifuatayo kutoka ndani ya terminal ya VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Hii itaunda kichochezi cha HTTP kinachoitwa `text-to-timer`.

1. Jaribu kichochezi cha HTTP kwa kuendesha programu ya kazi. Itakapoendesha utaona *endpoint* iliyoorodheshwa kwenye matokeo:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Jaribu hii kwa kufungua URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) kwenye kivinjari chako.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Kazi - tumia mfano wa uelewa wa lugha

1. SDK ya LUIS inapatikana kupitia pakiti ya Pip. Ongeza mstari ufuatao kwenye faili ya `requirements.txt` ili kuongeza utegemezi wa pakiti hii:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Hakikisha terminal ya VS Code imeamilisha mazingira halisi (*virtual environment*), na endesha amri ifuatayo kusakinisha pakiti za Pip:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Ikiwa unapata makosa, huenda ukahitaji kusasisha pip kwa amri ifuatayo:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Ongeza maingizo mapya kwenye faili ya `local.settings.json` kwa ajili ya LUIS API Key, Endpoint URL, na App ID kutoka tabo ya **MANAGE** ya portal ya LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Badilisha `<endpoint url>` na Endpoint URL kutoka sehemu ya *Azure Resources* ya tabo ya **MANAGE**. Hii itakuwa `https://<location>.api.cognitive.microsoft.com/`.

    Badilisha `<app id>` na App ID kutoka sehemu ya *Settings* ya tabo ya **MANAGE**.

    Badilisha `<primary key>` na Primary Key kutoka sehemu ya *Azure Resources* ya tabo ya **MANAGE**.

1. Ongeza maingizo yafuatayo kwenye faili ya `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Hii inaingiza maktaba za mfumo, pamoja na maktaba za kuingiliana na LUIS.

1. Futa yaliyomo kwenye njia ya `main`, na ongeza msimbo ufuatao:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Hii inasoma maadili uliyoongeza kwenye faili ya `local.settings.json` kwa programu yako ya LUIS, inaunda kitu cha sifa (*credentials object*) na API key yako, kisha inaunda kitu cha mteja wa LUIS (*LUIS client object*) kuingiliana na programu yako ya LUIS.

1. Kichochezi hiki cha HTTP kitaitwa kwa kupitisha maandishi ya kuelewa kama JSON, na maandishi kwenye mali inayoitwa `text`. Msimbo ufuatao unatoa thamani kutoka kwa mwili wa ombi la HTTP, na kuandika kwenye koni. Ongeza msimbo huu kwenye kazi ya `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Utabiri unahitajika kutoka LUIS kwa kutuma ombi la utabiri - hati ya JSON inayojumuisha maandishi ya kutabiri. Unda hii kwa msimbo ufuatao:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Ombi hili linaweza kutumwa kwa LUIS, ukitumia nafasi ya majaribio (*staging slot*) ambayo programu yako ilichapishwa:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Majibu ya utabiri yanajumuisha nia kuu (*top intent*) - nia yenye alama ya juu zaidi ya utabiri, pamoja na viashiria (*entities*). Ikiwa nia kuu ni `set timer`, basi viashiria vinaweza kusomwa ili kupata muda unaohitajika kwa kipima muda:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Viashiria vya `number` vitakuwa safu ya namba. Kwa mfano, ukisema *"Set a four minute 17 second timer."*, basi safu ya `number` itakuwa na namba 2 - 4 na 17.

    Viashiria vya `time unit` vitakuwa safu ya safu za maneno, kila kipimo cha muda kama safu ya maneno ndani ya safu. Kwa mfano, ukisema *"Set a four minute 17 second timer."*, basi safu ya `time unit` itakuwa na safu 2 zenye thamani moja kila moja - `['minute']` na `['second']`.

    Toleo la JSON la viashiria hivi kwa *"Set a four minute 17 second timer."* ni:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Msimbo huu pia unafafanua hesabu ya muda wa jumla kwa kipima muda kwa sekunde. Hii itajazwa na maadili kutoka kwa viashiria.

1. Viashiria havijaunganishwa, lakini tunaweza kufanya dhana fulani kuhusu wao. Watakuwa katika mpangilio uliozungumzwa, kwa hivyo nafasi katika safu inaweza kutumika kuamua namba gani inalingana na kipimo gani cha muda. Kwa mfano:

    * *"Set a 30 second timer"* - hii itakuwa na namba moja, `30`, na kipimo kimoja cha muda, `second` kwa hivyo namba moja italingana na kipimo kimoja cha muda.
    * *"Set a 2 minute and 30 second timer"* - hii itakuwa na namba mbili, `2` na `30`, na vipimo viwili vya muda, `minute` na `second` kwa hivyo namba ya kwanza itakuwa kwa kipimo cha kwanza cha muda (dakika 2), na namba ya pili kwa kipimo cha pili cha muda (sekunde 30).

    Msimbo ufuatao unapata hesabu ya vitu katika viashiria vya namba, na kutumia hiyo kutoa kipengele cha kwanza kutoka kila safu, kisha cha pili na kadhalika. Ongeza hii ndani ya kizuizi cha `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Kwa *"Set a four minute 17 second timer."*, hii itazunguka mara mbili, ikitoa maadili yafuatayo:

    | hesabu ya mzunguko | `number` | `time_unit` |
    | ------------------: | -------: | ----------- |
    | 0                  | 4        | minute      |
    | 1                  | 17       | second      |

1. Ndani ya mzunguko huu, tumia namba na kipimo cha muda kuhesabu muda wa jumla kwa kipima muda, ukiongeza sekunde 60 kwa kila dakika, na idadi ya sekunde kwa sekunde zozote.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Nje ya mzunguko huu kupitia viashiria, andika muda wa jumla kwa kipima muda:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Idadi ya sekunde inahitaji kurudishwa kutoka kwa kazi kama jibu la HTTP. Mwisho wa kizuizi cha `if`, ongeza yafuatayo:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Msimbo huu unaunda mzigo unaojumuisha idadi ya sekunde kwa kipima muda, unabadilisha kuwa kamba ya JSON na kuirudisha kama matokeo ya HTTP na msimbo wa hali ya 200, unaomaanisha mwito ulifanikiwa.

1. Hatimaye, nje ya kizuizi cha `if`, shughulikia ikiwa nia haikutambulika kwa kurudisha msimbo wa kosa:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 ni msimbo wa hali kwa *not found*.

1. Endesha programu ya kazi na ujaribu kwa kutumia curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Badilisha `<text>` na maandishi ya ombi lako, kwa mfano `set a 2 minutes 27 second timer`.

    Utaona matokeo yafuatayo kutoka kwa programu ya kazi:

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

    Mwito wa curl utarudisha yafuatayo:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Idadi ya sekunde kwa kipima muda iko kwenye thamani ya `"seconds"`.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Kazi - fanya kazi yako ipatikane kwa kifaa chako cha IoT

1. Ili kifaa chako cha IoT kiweze kupiga *REST endpoint* yako, kitahitaji kujua URL. Ulipoipata awali, ulitumia `localhost`, ambayo ni njia ya mkato ya kufikia *REST endpoints* kwenye kompyuta yako ya ndani. Ili kuruhusu kifaa chako cha IoT kupata, unahitaji kuchapisha kwenye wingu, au kupata anwani yako ya IP ili kufikia kwa ndani.

    > ⚠️ Ikiwa unatumia Wio Terminal, ni rahisi kuendesha programu ya kazi kwa ndani, kwani kutakuwa na utegemezi wa maktaba ambazo zinamaanisha huwezi kuchapisha programu ya kazi kwa njia sawa na ulivyofanya awali. Endesha programu ya kazi kwa ndani na ufikie kupitia anwani ya IP ya kompyuta yako. Ikiwa unataka kuchapisha kwenye wingu, maelezo yatatolewa katika somo la baadaye kuhusu njia ya kufanya hivyo.

    * Chapisha programu ya Functions - fuata maelekezo katika masomo ya awali kuchapisha programu yako ya Functions kwenye wingu. Mara baada ya kuchapishwa, URL itakuwa `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, ambapo `<APP_NAME>` itakuwa jina la programu yako ya Functions. Hakikisha pia kuchapisha mipangilio yako ya ndani.

      Unapofanya kazi na vichochezi vya HTTP, vinalindwa kwa chaguo-msingi na funguo ya programu ya kazi. Ili kupata funguo hii, endesha amri ifuatayo:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Nakili thamani ya ingizo la `default` kutoka sehemu ya `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Funguo hii itahitaji kuongezwa kama parameter ya swali kwenye URL, kwa hivyo URL ya mwisho itakuwa `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, ambapo `<APP_NAME>` itakuwa jina la programu yako ya Functions, na `<FUNCTION_KEY>` itakuwa funguo yako ya kazi ya chaguo-msingi.

      > 💁 Unaweza kubadilisha aina ya idhini ya kichochezi cha HTTP kwa kutumia mipangilio ya `authlevel` kwenye faili ya `function.json`. Unaweza kusoma zaidi kuhusu hili katika [sehemu ya usanidi ya nyaraka za Microsoft kuhusu kichochezi cha HTTP cha Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Endesha programu ya Functions kwa ndani, na ufikie kwa kutumia anwani ya IP - unaweza kupata anwani ya IP ya kompyuta yako kwenye mtandao wa ndani, na kuitumia kujenga URL.

      Pata anwani yako ya IP:

      * Kwenye Windows 10, fuata [mwongozo wa kupata anwani yako ya IP](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)
      * Kwenye macOS, fuata [jinsi ya kupata anwani yako ya IP kwenye Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)
      * Kwenye Linux, fuata sehemu ya kupata anwani yako ya IP ya kibinafsi katika [jinsi ya kupata anwani yako ya IP kwenye Linux](https://opensource.com/article/18/5/how-find-ip-address-linux)

      Mara baada ya kupata anwani yako ya IP, utaweza kufikia kazi kwenye `http://`.

:7071/api/text-to-timer`, ambapo `<IP_ADDRESS>` itakuwa anwani yako ya IP, kwa mfano `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Kumbuka kuwa hii inatumia bandari 7071, kwa hivyo baada ya anwani ya IP utahitaji kuwa na `:7071`.

      > 💁 Hii itafanya kazi tu ikiwa kifaa chako cha IoT kiko kwenye mtandao sawa na kompyuta yako.

1. Jaribu endpoint kwa kuifikia ukitumia curl.

---

## 🚀 Changamoto

Kuna njia nyingi za kuomba kitu kimoja, kama vile kuweka kipima muda. Fikiria njia tofauti za kufanya hivi, na uzitumie kama mifano katika programu yako ya LUIS. Jaribu hizi, ili kuona jinsi modeli yako inavyoweza kushughulikia njia mbalimbali za kuomba kipima muda.

## Maswali ya baada ya somo

[Maswali ya baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Mapitio & Kujisomea

* Soma zaidi kuhusu LUIS na uwezo wake kwenye [ukurasa wa nyaraka za Language Understanding (LUIS) kwenye Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Soma zaidi kuhusu uelewa wa lugha kwenye [ukurasa wa uelewa wa lugha asilia kwenye Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Soma zaidi kuhusu vichocheo vya HTTP kwenye [nyaraka za Azure Functions HTTP trigger kwenye Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Kazi

[Futa kipima muda](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kwa usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, inashauriwa kutumia huduma ya tafsiri ya kibinadamu ya kitaalamu. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.