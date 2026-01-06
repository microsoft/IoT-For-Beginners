<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-27T23:06:50+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "tl"
}
-->
# Unawain ang Wika

![Isang sketchnote overview ng aralin na ito](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture Quiz

[Pre-lecture Quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Panimula

Sa nakaraang aralin, ginamit mo ang speech-to-text. Para magamit ito sa pag-program ng smart timer, kailangang maunawaan ng iyong code kung ano ang sinabi. Maaari mong ipagpalagay na magsasalita ang user ng isang nakatakdang parirala, tulad ng "Mag-set ng 3 minutong timer", at i-parse ang expression na iyon para malaman kung gaano katagal ang timer, ngunit hindi ito masyadong user-friendly. Kung sasabihin ng user na "Mag-set ng timer para sa 3 minuto", mauunawaan mo o ako ang ibig sabihin nito, ngunit hindi ito mauunawaan ng iyong code dahil inaasahan nito ang nakatakdang parirala.

Dito papasok ang pag-unawa sa wika, gamit ang mga AI model para i-interpret ang text at ibalik ang mga detalyeng kailangan, halimbawa ang kakayahang maunawaan ang parehong "Mag-set ng 3 minutong timer" at "Mag-set ng timer para sa 3 minuto", at maintindihan na kailangan ng timer para sa 3 minuto.

Sa araling ito, matututo ka tungkol sa mga model ng pag-unawa sa wika, kung paano gumawa, mag-train, at gamitin ang mga ito mula sa iyong code.

Sa araling ito, tatalakayin natin:

* [Pag-unawa sa wika](../../../../../6-consumer/lessons/2-language-understanding)
* [Gumawa ng model ng pag-unawa sa wika](../../../../../6-consumer/lessons/2-language-understanding)
* [Intensyon at mga entidad](../../../../../6-consumer/lessons/2-language-understanding)
* [Gamitin ang model ng pag-unawa sa wika](../../../../../6-consumer/lessons/2-language-understanding)

## Pag-unawa sa Wika

Ang tao ay gumagamit ng wika para makipag-usap sa loob ng daan-daang libong taon. Nakikipag-usap tayo gamit ang mga salita, tunog, o kilos at nauunawaan ang sinasabi, hindi lamang ang kahulugan ng mga salita, tunog, o kilos, kundi pati na rin ang konteksto nito. Nauunawaan natin ang sinseridad at sarkasmo, na nagpapahintulot sa parehong mga salita na magkaroon ng iba't ibang kahulugan depende sa tono ng ating boses.

✅ Pag-isipan ang ilan sa mga pag-uusap na nagkaroon ka kamakailan. Gaano karami sa pag-uusap ang mahirap para sa isang computer na maunawaan dahil nangangailangan ito ng konteksto?

Ang pag-unawa sa wika, na tinatawag ding natural-language understanding, ay bahagi ng larangan ng artificial intelligence na tinatawag na natural-language processing (o NLP), at tumutukoy sa reading comprehension, sinusubukang unawain ang mga detalye ng mga salita o pangungusap. Kung gumagamit ka ng voice assistant tulad ng Alexa o Siri, gumagamit ka ng mga serbisyo ng pag-unawa sa wika. Ang mga ito ang mga AI service sa likod ng eksena na nagko-convert ng "Alexa, i-play ang pinakabagong album ni Taylor Swift" sa anak kong sumasayaw sa sala sa kanyang paboritong musika.

> 💁 Kahit na napakalayo na ng narating ng mga computer, marami pa rin silang kailangang gawin para tunay na maunawaan ang text. Kapag tinutukoy natin ang pag-unawa sa wika gamit ang mga computer, hindi natin ibig sabihin ang anumang kasing-advanced ng komunikasyon ng tao, sa halip ay ang pagkuha ng ilang mga salita at pagkuha ng mahahalagang detalye.

Bilang tao, nauunawaan natin ang wika nang hindi masyadong iniisip. Kung hihilingin ko sa isang tao na "i-play ang pinakabagong album ni Taylor Swift", agad nilang mauunawaan ang ibig kong sabihin. Para sa isang computer, mas mahirap ito. Kailangan nitong kunin ang mga salita, na-convert mula sa speech-to-text, at tukuyin ang mga sumusunod na impormasyon:

* Kailangang i-play ang musika
* Ang musika ay mula sa artist na si Taylor Swift
* Ang partikular na musika ay isang buong album na may maraming track sa tamang pagkakasunod-sunod
* Maraming album si Taylor Swift, kaya kailangang i-sort ang mga ito ayon sa chronological order at ang pinakabagong inilathala ang kailangan

✅ Mag-isip ng iba pang mga pangungusap na sinabi mo kapag humihiling, tulad ng pag-order ng kape o paghingi sa isang miyembro ng pamilya na ipasa ang isang bagay. Subukang hatiin ang mga ito sa mga piraso ng impormasyon na kailangang kunin ng isang computer para maunawaan ang pangungusap.

Ang mga model ng pag-unawa sa wika ay mga AI model na sinasanay para kunin ang ilang mga detalye mula sa wika, at pagkatapos ay sinasanay para sa mga partikular na gawain gamit ang transfer learning, sa parehong paraan na sinanay mo ang isang Custom Vision model gamit ang maliit na set ng mga imahe. Maaari kang kumuha ng isang model, pagkatapos ay sanayin ito gamit ang text na nais mong maunawaan.

## Gumawa ng Model ng Pag-unawa sa Wika

![Ang logo ng LUIS](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.tl.png)

Maaari kang gumawa ng mga model ng pag-unawa sa wika gamit ang LUIS, isang serbisyo ng pag-unawa sa wika mula sa Microsoft na bahagi ng Cognitive Services.

### Gawain - Gumawa ng Authoring Resource

Para magamit ang LUIS, kailangan mong gumawa ng authoring resource.

1. Gamitin ang sumusunod na command para gumawa ng authoring resource sa iyong `smart-timer` resource group:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Palitan ang `<location>` ng lokasyon na ginamit mo noong ginawa ang Resource Group.

    > ⚠️ Hindi available ang LUIS sa lahat ng rehiyon, kaya kung makakakuha ka ng sumusunod na error:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > pumili ng ibang rehiyon.

    Ito ay gagawa ng free-tier LUIS authoring resource.

### Gawain - Gumawa ng Language Understanding App

1. Buksan ang LUIS portal sa [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) sa iyong browser, at mag-sign in gamit ang parehong account na ginagamit mo para sa Azure.

1. Sundin ang mga tagubilin sa dialog para piliin ang iyong Azure subscription, pagkatapos ay piliin ang `smart-timer-luis-authoring` resource na kakagawa mo lang.

1. Mula sa *Conversation apps* list, piliin ang **New app** button para gumawa ng bagong application. Pangalanan ang bagong app na `smart-timer`, at itakda ang *Culture* sa iyong wika.

    > 💁 May field para sa prediction resource. Maaari kang gumawa ng pangalawang resource para sa prediction, ngunit ang free authoring resource ay nagbibigay ng 1,000 predictions bawat buwan na dapat sapat para sa development, kaya maaari mong iwanang blangko ito.

1. Basahin ang gabay na lalabas kapag ginawa mo ang app para maunawaan ang mga hakbang na kailangan mong gawin para sanayin ang model ng pag-unawa sa wika. Isara ang gabay kapag tapos ka na.

## Intensyon at mga Entidad

Ang pag-unawa sa wika ay nakabatay sa *intensyon* at *mga entidad*. Ang intensyon ay kung ano ang layunin ng mga salita, halimbawa ang pag-play ng musika, pag-set ng timer, o pag-order ng pagkain. Ang mga entidad ay kung ano ang tinutukoy ng intensyon, tulad ng album, haba ng timer, o uri ng pagkain. Ang bawat pangungusap na ini-interpret ng model ay dapat mayroong hindi bababa sa isang intensyon, at opsyonal na isa o higit pang mga entidad.

Mga halimbawa:

| Pangungusap                                         | Intensyon        | Mga Entidad                                |
| --------------------------------------------------- | ---------------- | ------------------------------------------ |
| "I-play ang pinakabagong album ni Taylor Swift"     | *mag-play ng musika* | *ang pinakabagong album ni Taylor Swift*   |
| "Mag-set ng 3 minutong timer"                       | *mag-set ng timer* | *3 minuto*                                 |
| "I-cancel ang timer ko"                             | *i-cancel ang timer* | Wala                                       |
| "Mag-order ng 3 malaking pineapple pizza at isang caesar salad" | *mag-order ng pagkain* | *3 malaking pineapple pizza*, *caesar salad* |

✅ Sa mga pangungusap na naisip mo kanina, ano ang intensyon at mga entidad sa pangungusap na iyon?

Para sanayin ang LUIS, una mong itatakda ang mga entidad. Ang mga ito ay maaaring isang nakatakdang listahan ng mga termino, o natutunan mula sa text. Halimbawa, maaari kang magbigay ng nakatakdang listahan ng pagkain mula sa iyong menu, na may mga variation (o synonyms) ng bawat salita, tulad ng *egg plant* at *aubergine* bilang mga variation ng *aubergine*. Ang LUIS ay mayroon ding mga pre-built na entidad na maaaring gamitin, tulad ng mga numero at lokasyon.

Para sa pag-set ng timer, maaari kang magkaroon ng isang entidad gamit ang pre-built number entities para sa oras, at isa pa para sa mga unit, tulad ng minuto at segundo. Ang bawat unit ay magkakaroon ng maraming variation para masakop ang singular at plural forms - tulad ng minuto at mga minuto.

Kapag naitakda na ang mga entidad, gagawa ka ng mga intensyon. Ang mga ito ay natutunan ng model batay sa mga halimbawa ng pangungusap na ibinibigay mo (kilala bilang utterances). Halimbawa, para sa isang *set timer* intensyon, maaari kang magbigay ng mga sumusunod na pangungusap:

* `mag-set ng 1 segundong timer`
* `mag-set ng timer para sa 1 minuto at 12 segundo`
* `mag-set ng timer para sa 3 minuto`
* `mag-set ng 9 minutong 30 segundong timer`

Pagkatapos, sasabihin mo sa LUIS kung aling bahagi ng mga pangungusap ang tumutugma sa mga entidad:

![Ang pangungusap na mag-set ng timer para sa 1 minuto at 12 segundo na hinati sa mga entidad](../../../../../translated_images/sentence-as-intent-entities.301401696f992259.tl.png)

Ang pangungusap na `mag-set ng timer para sa 1 minuto at 12 segundo` ay may intensyon na `mag-set ng timer`. Mayroon din itong 2 entidad na may 2 halaga bawat isa:

|            | oras | unit   |
| ---------- | ---: | ------ |
| 1 minuto   | 1    | minuto |
| 12 segundo | 12   | segundo |

Para sanayin ang isang mahusay na model, kailangan mo ng iba't ibang mga halimbawa ng pangungusap para masakop ang maraming iba't ibang paraan ng paghingi ng parehong bagay.

> 💁 Tulad ng anumang AI model, mas maraming data at mas tumpak ang data na ginagamit mo para sa training, mas maganda ang model.

✅ Pag-isipan ang iba't ibang paraan na maaari mong hilingin ang parehong bagay at asahan na mauunawaan ito ng tao.

### Gawain - Magdagdag ng mga Entidad sa Model ng Pag-unawa sa Wika

Para sa timer, kailangan mong magdagdag ng 2 entidad - isa para sa unit ng oras (minuto o segundo), at isa para sa bilang ng minuto o segundo.

Makakahanap ka ng mga tagubilin para sa paggamit ng LUIS portal sa [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Mula sa LUIS portal, piliin ang *Entities* tab at idagdag ang *number* prebuilt entity sa pamamagitan ng pagpili sa **Add prebuilt entity** button, pagkatapos ay piliin ang *number* mula sa listahan.

1. Gumawa ng bagong entidad para sa unit ng oras gamit ang **Create** button. Pangalanan ang entidad na `time unit` at itakda ang type sa *List*. Magdagdag ng mga halaga para sa `minute` at `second` sa *Normalized values* list, at idagdag ang singular at plural forms sa *synonyms* list. Pindutin ang `return` pagkatapos idagdag ang bawat synonym para idagdag ito sa listahan.

    | Normalized value | Synonyms        |
    | ---------------- | --------------- |
    | minuto           | minuto, mga minuto |
    | segundo          | segundo, mga segundo |

### Gawain - Magdagdag ng Intensyon sa Model ng Pag-unawa sa Wika

1. Mula sa *Intents* tab, piliin ang **Create** button para gumawa ng bagong intensyon. Pangalanan ang intensyon na ito na `set timer`.

1. Sa mga halimbawa, maglagay ng iba't ibang paraan para mag-set ng timer gamit ang parehong minuto, segundo, at kombinasyon ng minuto at segundo. Ang mga halimbawa ay maaaring:

    * `mag-set ng 1 segundong timer`
    * `mag-set ng 4 minutong timer`
    * `mag-set ng apat na minutong anim na segundong timer`
    * `mag-set ng 9 minutong 30 segundong timer`
    * `mag-set ng timer para sa 1 minuto at 12 segundo`
    * `mag-set ng timer para sa 3 minuto`
    * `mag-set ng timer para sa 3 minuto at 1 segundo`
    * `mag-set ng timer para sa tatlong minuto at isang segundo`
    * `mag-set ng timer para sa 1 minuto at 1 segundo`
    * `mag-set ng timer para sa 30 segundo`
    * `mag-set ng timer para sa 1 segundo`

    Paghaluin ang mga numero bilang mga salita at numeriko upang matutunan ng model na hawakan ang pareho.

1. Habang inilalagay mo ang bawat halimbawa, magsisimulang tukuyin ng LUIS ang mga entidad, at i-underline at i-label ang anumang natuklasan nito.

    ![Ang mga halimbawa na may mga numero at unit ng oras na naka-underline ng LUIS](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.tl.png)

### Gawain - I-train at I-test ang Model

1. Kapag na-configure na ang mga entidad at intensyon, maaari mong i-train ang model gamit ang **Train** button sa top menu. Piliin ang button na ito, at ang model ay dapat mag-train sa loob ng ilang segundo. Ang button ay magiging greyed out habang nagte-train, at muling ma-enable kapag tapos na.

1. Piliin ang **Test** button mula sa top menu para i-test ang model ng pag-unawa sa wika. Maglagay ng text tulad ng `mag-set ng timer para sa 5 minuto at 4 segundo` at pindutin ang return. Ang pangungusap ay lalabas sa isang kahon sa ilalim ng text box na tinype mo, at sa ilalim nito ay ang *top intent*, o ang intensyon na natukoy na may pinakamataas na probability. Dapat itong `set timer`. Ang pangalan ng intensyon ay susundan ng probability na ang natukoy na intensyon ay tama.

1. Piliin ang **Inspect** option para makita ang breakdown ng mga resulta. Makikita mo ang top-scoring intent kasama ang percentage probability nito, pati na rin ang mga listahan ng mga natukoy na entidad.

1. Isara ang *Test* pane kapag tapos ka na sa pag-test.

### Gawain - I-publish ang Model

Para magamit ang model na ito mula sa code, kailangan mo itong i-publish. Kapag nag-publish mula sa LUIS, maaari kang mag-publish sa staging environment para sa testing, o sa product environment para sa full release. Sa araling ito, ang staging environment ay sapat na.

1. Mula sa LUIS portal, piliin ang **Publish** button mula sa top menu.

1. Siguraduhing naka-select ang *Staging slot*, pagkatapos ay piliin ang **Done**. Makakakita ka ng notification kapag na-publish na ang app.

1. Maaari mo itong i-test gamit ang curl. Para mabuo ang curl command, kailangan mo ng tatlong halaga - ang endpoint, ang application ID (App ID), at isang API key. Makikita ang mga ito sa **MANAGE** tab na maaaring piliin mula sa top menu.

    1. Mula sa *Settings* section, kopyahin ang App ID
1. Mula sa seksyong *Azure Resources*, piliin ang *Authoring Resource*, at kopyahin ang *Primary Key* at *Endpoint URL*.

1. Patakbuhin ang sumusunod na curl command sa iyong command prompt o terminal:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Palitan ang `<endpoint url>` ng Endpoint URL mula sa seksyong *Azure Resources*.

    Palitan ang `<app id>` ng App ID mula sa seksyong *Settings*.

    Palitan ang `<primary key>` ng Primary Key mula sa seksyong *Azure Resources*.

    Palitan ang `<sentence>` ng pangungusap na nais mong subukan.

1. Ang output ng tawag na ito ay isang JSON document na naglalaman ng detalye ng query, ang top intent, at isang listahan ng mga entities na nakategorya ayon sa uri.

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

    Ang JSON sa itaas ay nagmula sa pag-query gamit ang `set a timer for 45 minutes and 12 seconds`:

    * Ang `set timer` ang naging top intent na may probability na 97%.
    * Dalawang *number* entities ang natukoy, `45` at `12`.
    * Dalawang *time-unit* entities ang natukoy, `minute` at `second`.

## Gamitin ang language understanding model

Kapag na-publish na, maaaring tawagin ang LUIS model mula sa code. Sa mga nakaraang aralin, gumamit ka ng IoT Hub para sa komunikasyon sa cloud services, pagpapadala ng telemetry, at pakikinig sa mga utos. Ito ay napaka-asynchronous - kapag naipadala na ang telemetry, hindi naghihintay ang iyong code para sa sagot, at kung ang cloud service ay hindi gumagana, hindi mo ito malalaman.

Para sa isang smart timer, nais natin ng agarang tugon upang masabi sa user na na-set na ang timer, o alertuhan sila na hindi available ang cloud services. Para magawa ito, tatawagin ng IoT device ang isang web endpoint nang direkta, sa halip na umasa sa IoT Hub.

Sa halip na tawagin ang LUIS mula sa IoT device, maaari kang gumamit ng serverless code na may ibang uri ng trigger - isang HTTP trigger. Pinapayagan nito ang iyong function app na makinig sa REST requests at tumugon sa mga ito. Ang function na ito ay magiging isang REST endpoint na maaaring tawagin ng iyong device.

> 💁 Bagamat maaari mong tawagin ang LUIS nang direkta mula sa iyong IoT device, mas mainam na gumamit ng serverless code. Sa ganitong paraan, kapag nais mong baguhin ang LUIS app na tinatawag mo, halimbawa kapag nag-train ka ng mas mahusay na model o nag-train ng model sa ibang wika, kailangan mo lang i-update ang iyong cloud code, hindi na kailangang i-redeploy ang code sa libu-libo o milyon-milyong IoT device.

### Gawain - gumawa ng serverless functions app

1. Gumawa ng Azure Functions app na tinatawag na `smart-timer-trigger`, at buksan ito sa VS Code.

1. Magdagdag ng HTTP trigger sa app na ito na tinatawag na `speech-trigger` gamit ang sumusunod na command mula sa loob ng VS Code terminal:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Ito ay lilikha ng HTTP trigger na tinatawag na `text-to-timer`.

1. Subukan ang HTTP trigger sa pamamagitan ng pagpapatakbo ng functions app. Kapag tumakbo ito, makikita mo ang endpoint na nakalista sa output:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Subukan ito sa pamamagitan ng pag-load ng [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) URL sa iyong browser.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Gawain - gamitin ang language understanding model

1. Ang SDK para sa LUIS ay available sa pamamagitan ng Pip package. Idagdag ang sumusunod na linya sa `requirements.txt` file upang idagdag ang dependency sa package na ito:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Siguraduhing naka-activate ang virtual environment sa VS Code terminal, at patakbuhin ang sumusunod na command upang i-install ang Pip packages:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Kung makakakuha ka ng errors, maaaring kailangan mong i-upgrade ang pip gamit ang sumusunod na command:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Magdagdag ng mga bagong entry sa `local.settings.json` file para sa iyong LUIS API Key, Endpoint URL, at App ID mula sa **MANAGE** tab ng LUIS portal:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Palitan ang `<endpoint url>` ng Endpoint URL mula sa seksyong *Azure Resources* ng **MANAGE** tab. Ito ay magiging `https://<location>.api.cognitive.microsoft.com/`.

    Palitan ang `<app id>` ng App ID mula sa seksyong *Settings* ng **MANAGE** tab.

    Palitan ang `<primary key>` ng Primary Key mula sa seksyong *Azure Resources* ng **MANAGE** tab.

1. Idagdag ang sumusunod na imports sa `__init__.py` file:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Ito ay nag-i-import ng ilang system libraries, pati na rin ang mga libraries para makipag-ugnayan sa LUIS.

1. Burahin ang nilalaman ng `main` method, at idagdag ang sumusunod na code:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Ito ay naglo-load ng mga values na idinagdag mo sa `local.settings.json` file para sa iyong LUIS app, gumagawa ng credentials object gamit ang iyong API key, at gumagawa ng LUIS client object para makipag-ugnayan sa iyong LUIS app.

1. Ang HTTP trigger na ito ay tatawagin na may JSON na naglalaman ng text na iintindihin, na may text sa property na tinatawag na `text`. Ang sumusunod na code ay nag-e-extract ng value mula sa body ng HTTP request, at naglo-log nito sa console. Idagdag ang code na ito sa `main` function:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Ang mga predictions ay hinihingi mula sa LUIS sa pamamagitan ng pagpapadala ng prediction request - isang JSON document na naglalaman ng text na ipredict. Gumawa nito gamit ang sumusunod na code:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Ang request na ito ay maaaring ipadala sa LUIS, gamit ang staging slot kung saan na-publish ang iyong app:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Ang prediction response ay naglalaman ng top intent - ang intent na may pinakamataas na prediction score, kasama ang mga entities. Kung ang top intent ay `set timer`, ang mga entities ay maaaring basahin upang makuha ang oras na kailangan para sa timer:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Ang `number` entities ay magiging isang array ng mga numero. Halimbawa, kung sinabi mo *"Set a four minute 17 second timer."*, ang `number` array ay maglalaman ng 2 integers - 4 at 17.

    Ang `time unit` entities ay magiging isang array ng arrays ng strings, na may bawat time unit bilang isang array ng strings sa loob ng array. Halimbawa, kung sinabi mo *"Set a four minute 17 second timer."*, ang `time unit` array ay maglalaman ng 2 arrays na may single values bawat isa - `['minute']` at `['second']`.

    Ang JSON version ng mga entities para sa *"Set a four minute 17 second timer."* ay:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Ang code na ito ay nagde-define din ng count para sa kabuuang oras ng timer sa seconds. Ito ay mapupunan ng mga values mula sa entities.

1. Ang mga entities ay hindi naka-link, ngunit maaari tayong gumawa ng ilang assumptions tungkol sa mga ito. Ang mga ito ay nasa order kung paano ito sinabi, kaya ang posisyon sa array ay maaaring gamitin upang matukoy kung aling numero ang tumutugma sa aling time unit. Halimbawa:

    * *"Set a 30 second timer"* - ito ay magkakaroon ng isang numero, `30`, at isang time unit, `second` kaya ang single number ay magmamatch sa single time unit.
    * *"Set a 2 minute and 30 second timer"* - ito ay magkakaroon ng dalawang numero, `2` at `30`, at dalawang time units, `minute` at `second` kaya ang unang numero ay para sa unang time unit (2 minutes), at ang pangalawang numero para sa pangalawang time unit (30 seconds).

    Ang sumusunod na code ay kumukuha ng count ng items sa number entities, at ginagamit ito upang kunin ang unang item mula sa bawat array, pagkatapos ang pangalawa, at iba pa. Idagdag ito sa loob ng `if` block.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Para sa *"Set a four minute 17 second timer."*, ito ay mag-loop nang dalawang beses, na nagbibigay ng sumusunod na values:

    | loop count | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. Sa loob ng loop na ito, gamitin ang number at time unit upang kalkulahin ang kabuuang oras para sa timer, na nagdadagdag ng 60 seconds para sa bawat minuto, at ang bilang ng seconds para sa anumang seconds.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Sa labas ng loop sa entities, i-log ang kabuuang oras para sa timer:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Ang bilang ng seconds ay kailangang ibalik mula sa function bilang HTTP response. Sa dulo ng `if` block, idagdag ang sumusunod:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Ang code na ito ay gumagawa ng payload na naglalaman ng kabuuang bilang ng seconds para sa timer, kino-convert ito sa JSON string, at ibinabalik ito bilang HTTP result na may status code na 200, na nangangahulugang matagumpay ang tawag.

1. Sa wakas, sa labas ng `if` block, i-handle kung ang intent ay hindi natukoy sa pamamagitan ng pagbabalik ng error code:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    Ang 404 ay ang status code para sa *not found*.

1. Patakbuhin ang function app at subukan ito gamit ang curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Palitan ang `<text>` ng text ng iyong request, halimbawa `set a 2 minutes 27 second timer`.

    Makikita mo ang sumusunod na output mula sa functions app:

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

    Ang tawag sa curl ay magbabalik ng sumusunod:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Ang bilang ng seconds para sa timer ay nasa `"seconds"` value.

> 💁 Maaari mong makita ang code na ito sa [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions) folder.

### Gawain - gawing available ang iyong function sa iyong IoT device

1. Para matawag ng iyong IoT device ang iyong REST endpoint, kailangan nitong malaman ang URL. Kapag na-access mo ito kanina, ginamit mo ang `localhost`, na shortcut para ma-access ang REST endpoints sa iyong local machine. Para ma-access ng iyong IoT device, kailangan mong i-publish sa cloud, o kunin ang iyong IP address para ma-access ito nang lokal.

    > ⚠️ Kung gumagamit ka ng Wio Terminal, mas madali ang pagpapatakbo ng function app nang lokal, dahil magkakaroon ng dependency sa mga libraries na nangangahulugang hindi mo ma-deploy ang function app sa parehong paraan tulad ng ginawa mo dati. Patakbuhin ang function app nang lokal at i-access ito gamit ang IP address ng iyong computer. Kung nais mong i-deploy sa cloud, magbibigay ng impormasyon sa susunod na aralin kung paano ito gagawin.

    * I-publish ang Functions app - sundin ang mga instruksyon sa mga naunang aralin upang i-publish ang iyong functions app sa cloud. Kapag na-publish, ang URL ay magiging `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, kung saan ang `<APP_NAME>` ay ang pangalan ng iyong functions app. Siguraduhing i-publish din ang iyong local settings.

      Kapag nagtatrabaho sa HTTP triggers, ang mga ito ay secured by default gamit ang function app key. Para makuha ang key na ito, patakbuhin ang sumusunod na command:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Kopyahin ang value ng `default` entry mula sa `functionKeys` section.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Ang key na ito ay kailangang idagdag bilang query parameter sa URL, kaya ang final URL ay magiging `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, kung saan ang `<APP_NAME>` ay ang pangalan ng iyong functions app, at `<FUNCTION_KEY>` ay ang iyong default function key.

      > 💁 Maaari mong baguhin ang uri ng authorization ng HTTP trigger gamit ang `authlevel` setting sa `function.json` file. Maaari mong basahin ang higit pa tungkol dito sa [configuration section ng Azure Functions HTTP trigger documentation sa Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Patakbuhin ang functions app nang lokal, at i-access gamit ang IP address - maaari mong makuha ang IP address ng iyong computer sa iyong local network, at gamitin ito upang buuin ang URL.

      Hanapin ang iyong IP address:

      * Sa Windows 10, sundin ang [find your IP address guide](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)
      * Sa macOS, sundin ang [how to find you IP address on a Mac guide](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)
      * Sa linux, sundin ang seksyon sa paghahanap ng iyong private IP address sa [how to find your IP address in Linux guide](https://opensource.com/article/18/5/how-find-ip-address-linux)

      Kapag nakuha mo na ang iyong IP address, maa-access mo ang function sa `http://`.

:7071/api/text-to-timer`, kung saan ang `<IP_ADDRESS>` ay ang iyong IP address, halimbawa `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Tandaan na gumagamit ito ng port 7071, kaya pagkatapos ng IP address kailangan mong idagdag ang `:7071`.

      > 💁 Gagana lamang ito kung ang iyong IoT device ay nasa parehong network ng iyong computer.

1. Subukan ang endpoint sa pamamagitan ng pag-access dito gamit ang curl.

---

## 🚀 Hamon

Maraming paraan upang humiling ng parehong bagay, tulad ng pag-set ng timer. Mag-isip ng iba't ibang paraan upang gawin ito, at gamitin ang mga ito bilang halimbawa sa iyong LUIS app. Subukan ang mga ito upang makita kung gaano kahusay ang iyong modelo sa pag-handle ng iba't ibang paraan ng paghingi ng timer.

## Quiz pagkatapos ng lektura

[Quiz pagkatapos ng lektura](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Review at Pag-aaral sa Sarili

* Magbasa pa tungkol sa LUIS at ang mga kakayahan nito sa [Language Understanding (LUIS) documentation page sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Magbasa pa tungkol sa language understanding sa [natural-language understanding page sa Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Magbasa pa tungkol sa HTTP triggers sa [Azure Functions HTTP trigger documentation sa Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Takdang Aralin

[Ikansela ang timer](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.