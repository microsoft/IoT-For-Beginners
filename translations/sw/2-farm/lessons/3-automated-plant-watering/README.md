<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f7bb24ba53fb627ddb38a8b24a05e594",
  "translation_date": "2025-08-27T23:24:18+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/README.md",
  "language_code": "sw"
}
-->
# Kumwagilia mimea kiotomatiki

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-7.30b5f577d3cb8e031238751475cb519c7d6dbaea261b5df4643d086ffb2a03bb.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa zaidi.

Somo hili lilifundishwa kama sehemu ya [Mradi wa IoT kwa Kompyuta - Mfululizo wa Kilimo Kidigitali](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) kutoka [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Mfumo wa kumwagilia mimea kiotomatiki unaotumia IoT](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Jaribio la kabla ya somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Utangulizi

Katika somo la mwisho, ulijifunza jinsi ya kufuatilia unyevu wa udongo. Katika somo hili, utajifunza jinsi ya kujenga vipengele vya msingi vya mfumo wa kumwagilia kiotomatiki unaojibu unyevu wa udongo. Pia utajifunza kuhusu muda - jinsi sensa zinavyoweza kuchukua muda kujibu mabadiliko, na jinsi actuators zinavyoweza kuchukua muda kubadilisha mali zinazopimwa na sensa.

Katika somo hili tutashughulikia:

* [Kudhibiti vifaa vya nguvu kubwa kutoka kwa kifaa cha IoT chenye nguvu ndogo](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Kudhibiti relay](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Kudhibiti mmea wako kupitia MQTT](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Muda wa sensa na actuator](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Kuongeza muda kwenye seva yako ya kudhibiti mimea](../../../../../2-farm/lessons/3-automated-plant-watering)

## Kudhibiti vifaa vya nguvu kubwa kutoka kwa kifaa cha IoT chenye nguvu ndogo

Vifaa vya IoT hutumia voltage ndogo. Ingawa hii inatosha kwa sensa na actuators zenye nguvu ndogo kama LED, hii ni ndogo sana kudhibiti vifaa vikubwa, kama pampu ya maji inayotumika kwa umwagiliaji. Hata pampu ndogo unazoweza kutumia kwa mimea ya nyumbani zinachukua umeme mwingi kwa kifaa cha IoT na zinaweza kuharibu bodi.

> 🎓 Umeme, unaopimwa kwa Amps (A), ni kiasi cha umeme kinachosafiri kupitia mzunguko. Voltage hutoa msukumo, umeme ni kiasi kinachosukumwa. Unaweza kusoma zaidi kuhusu umeme kwenye [ukurasa wa umeme wa Wikipedia](https://wikipedia.org/wiki/Electric_current).

Suluhisho la hili ni kuwa na pampu iliyounganishwa na chanzo cha umeme wa nje, na kutumia actuator kuwasha pampu, sawa na jinsi unavyowasha taa. Inachukua kiasi kidogo cha nguvu (kwa njia ya nishati mwilini mwako) kwa kidole chako kubonyeza swichi, na hii inaunganisha taa na umeme wa nyumbani unaoendesha kwa 110v/240v.

![Swichi ya taa inawasha taa](../../../../../translated_images/sw/light-switch.760317ad6ab8bd6d611da5352dfe9c73a94a0822ccec7df3c8bae35da18e1658.png)

> 🎓 [Umeme wa nyumbani](https://wikipedia.org/wiki/Mains_electricity) unarejelea umeme unaosambazwa kwa nyumba na biashara kupitia miundombinu ya kitaifa katika sehemu nyingi za dunia.

✅ Vifaa vya IoT vinaweza kawaida kutoa 3.3V au 5V, kwa chini ya 1 amp (1A) ya umeme. Linganisha hili na umeme wa nyumbani ambao mara nyingi ni 230V (120V Amerika Kaskazini na 100V Japani), na unaweza kutoa nguvu kwa vifaa vinavyotumia 30A.

Kuna actuators kadhaa zinazoweza kufanya hili, ikiwa ni pamoja na vifaa vya mitambo unavyoweza kuunganisha kwenye swichi zilizopo zinazofanya kazi kama kidole kinachowasha. Maarufu zaidi ni relay.

### Relay

Relay ni swichi ya kielektroniki inayobadilisha ishara ya umeme kuwa harakati ya mitambo inayowasha swichi. Msingi wa relay ni sumaku ya umeme.

> 🎓 [Sumaku za umeme](https://wikipedia.org/wiki/Electromagnet) ni sumaku zinazoundwa kwa kupitisha umeme kupitia coil ya waya. Umeme unapowashwa, coil inakuwa na sumaku. Umeme unapozimwa, coil inapoteza sumaku yake.

![Wakati imewashwa, sumaku ya umeme inaunda uwanja wa sumaku, kuwasha swichi kwa mzunguko wa nje](../../../../../translated_images/sw/relay-on.4db16a0fd6b66926.webp)

Katika relay, mzunguko wa kudhibiti huendesha sumaku ya umeme. Sumaku ya umeme inapowashwa, inavuta lever inayosogeza swichi, kufunga mawasiliano na kukamilisha mzunguko wa nje.

![Wakati imezimwa, sumaku ya umeme haizalishi uwanja wa sumaku, kuzima swichi kwa mzunguko wa nje](../../../../../translated_images/sw/relay-off.c34a178a2960fecd.webp)

Mzunguko wa kudhibiti unapozimwa, sumaku ya umeme inazimwa, ikiachilia lever na kufungua mawasiliano, kuzima mzunguko wa nje. Relay ni actuators za kidigitali - ishara ya juu kwa relay inaiwasha, ishara ya chini inazima.

Mzunguko wa nje unaweza kutumika kuendesha vifaa vya ziada, kama mfumo wa umwagiliaji. Kifaa cha IoT kinaweza kuwasha relay, kukamilisha mzunguko wa nje unaoendesha mfumo wa umwagiliaji, na mimea inapata maji. Kifaa cha IoT kinaweza kisha kuzima relay, kukata umeme kwa mfumo wa umwagiliaji, kuzima maji.

![Relay inawashwa, kuwasha pampu inayotuma maji kwa mmea](../../../../../images/strawberry-pump.gif)

Katika video hapo juu, relay inawashwa. LED kwenye relay inawaka kuonyesha kuwa imewashwa (baadhi ya bodi za relay zina LED kuonyesha ikiwa relay imewashwa au imezimwa), na umeme unatumwa kwa pampu, kuiwasha na kusukuma maji kwenye mmea.

> 💁 Relay zinaweza pia kutumika kubadilisha kati ya mizunguko miwili ya nje badala ya kuwasha au kuzima moja. Lever inaposogea, inasogeza swichi kutoka kukamilisha mzunguko mmoja wa nje hadi kukamilisha mzunguko tofauti wa nje, mara nyingi ikishiriki muunganisho wa umeme wa kawaida, au muunganisho wa ardhi wa kawaida.

✅ Fanya utafiti: Kuna aina nyingi za relay, zenye tofauti kama ikiwa mzunguko wa kudhibiti unawasha au kuzima relay wakati umeme unatumika, au mizunguko mingi ya nje. Tafuta kuhusu aina hizi tofauti.

Lever inaposogea, mara nyingi unaweza kuisikia ikigusa sumaku ya umeme kwa sauti ya kubofya iliyoeleweka vizuri.

> 💁 Relay inaweza kuunganishwa ili kufanya muunganisho kuvunja umeme kwa relay, kuizima relay, ambayo kisha inatuma umeme kwa relay kuirudisha kuwashwa tena, na kadhalika. Hii inamaanisha relay itabofya haraka sana ikitoa sauti ya buzzing. Hivi ndivyo baadhi ya buzzers za kwanza zilizotumika kwenye kengele za milango za umeme zilivyofanya kazi.

### Nguvu ya relay

Sumaku ya umeme haitaji nguvu nyingi kuamsha na kuvuta lever, inaweza kudhibitiwa kwa kutumia 3.3V au 5V kutoka kwa kifaa cha IoT. Mzunguko wa nje unaweza kubeba nguvu zaidi, kulingana na relay, ikiwa ni pamoja na voltage ya nyumbani au hata viwango vya juu vya nguvu kwa matumizi ya viwandani. Kwa njia hii kifaa cha IoT kinaweza kudhibiti mfumo wa umwagiliaji, kutoka pampu ndogo kwa mmea mmoja, hadi mfumo mkubwa wa viwandani kwa shamba zima la kibiashara.

![Relay ya Grove ikiwa na mzunguko wa kudhibiti, mzunguko wa nje na relay vimewekwa alama](../../../../../translated_images/sw/grove-relay-labelled.293e068f5c3c2a199bd7892f2661fdc9e10c920b535cfed317fbd6d1d4ae1168.png)

Picha hapo juu inaonyesha relay ya Grove. Mzunguko wa kudhibiti unaunganisha na kifaa cha IoT na kuwasha au kuzima relay kwa kutumia 3.3V au 5V. Mzunguko wa nje una vituo viwili, chochote kinaweza kuwa umeme au ardhi. Mzunguko wa nje unaweza kushughulikia hadi 250V kwa 10A, ya kutosha kwa vifaa mbalimbali vinavyotumia umeme wa nyumbani. Unaweza kupata relay zinazoweza kushughulikia hata viwango vya juu vya nguvu.

![Pampu iliyounganishwa kupitia relay](../../../../../translated_images/sw/pump-wired-to-relay.66c5cfc0d8918990.webp)

Katika picha hapo juu, umeme unapelekwa kwa pampu kupitia relay. Kuna waya nyekundu inayounganisha terminal ya +5V ya chanzo cha umeme cha USB na terminal moja ya mzunguko wa nje wa relay, na waya nyekundu nyingine inayounganisha terminal nyingine ya mzunguko wa nje na pampu. Waya nyeusi inaunganisha pampu na ardhi kwenye chanzo cha umeme cha USB. Relay inapowashwa, inakamilisha mzunguko, kutuma 5V kwa pampu, kuiwasha pampu.

## Kudhibiti relay

Unaweza kudhibiti relay kutoka kwa kifaa chako cha IoT.

### Kazi - kudhibiti relay

Fanya kazi kupitia mwongozo husika kudhibiti relay kwa kutumia kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Kompyuta ya bodi moja - Raspberry Pi](pi-relay.md)
* [Kompyuta ya bodi moja - Kifaa cha virtual](virtual-device-relay.md)

## Kudhibiti mmea wako kupitia MQTT

Hadi sasa relay yako inadhibitiwa moja kwa moja na kifaa cha IoT kulingana na usomaji mmoja wa unyevu wa udongo. Katika mfumo wa umwagiliaji wa kibiashara, mantiki ya kudhibiti itakuwa ya kati, ikiruhusu kufanya maamuzi ya kumwagilia kwa kutumia data kutoka sensa nyingi, na kuruhusu mabadiliko yoyote ya usanidi kufanywa mahali pamoja. Ili kuiga hili, unaweza kudhibiti relay kupitia MQTT.

### Kazi - kudhibiti relay kupitia MQTT

1. Ongeza maktaba/pakiti za pip za MQTT husika na msimbo kwenye mradi wako wa `soil-moisture-sensor` ili kuunganishwa na MQTT. Taja kitambulisho cha mteja kama `soilmoisturesensor_client` kilichotanguliwa na kitambulisho chako.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunganishwa na MQTT katika mradi wa 1, somo la 4 ikiwa inahitajika](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Ongeza msimbo wa kifaa husika kutuma telemetry na mipangilio ya unyevu wa udongo. Kwa ujumbe wa telemetry, taja mali `soil_moisture`.

    > ⚠️ Unaweza kurejelea [maelekezo ya kutuma telemetry kwa MQTT katika mradi wa 1, somo la 4 ikiwa inahitajika](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Unda msimbo wa seva ya ndani ili kujiunga na telemetry na kutuma amri ya kudhibiti relay katika folda inayoitwa `soil-moisture-sensor-server`. Taja mali katika ujumbe wa amri kama `relay_on`, na weka kitambulisho cha mteja kama `soilmoisturesensor_server` kilichotanguliwa na kitambulisho chako. Weka muundo sawa na msimbo wa seva uliouandika kwa mradi wa 1, somo la 4 kwani utaongeza msimbo huu baadaye katika somo hili.

    > ⚠️ Unaweza kurejelea [maelekezo ya kutuma telemetry kwa MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) na [kutuma amri kupitia MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) katika mradi wa 1, somo la 4 ikiwa inahitajika.

1. Ongeza msimbo wa kifaa husika kudhibiti relay kutoka kwa amri zilizopokelewa, ukitumia mali `relay_on` kutoka kwa ujumbe. Tuma kweli kwa `relay_on` ikiwa `soil_moisture` ni kubwa kuliko 450, vinginevyo tuma uongo, sawa na mantiki uliyoongeza kwa kifaa cha IoT hapo awali.

    > ⚠️ Unaweza kurejelea [maelekezo ya kujibu amri kutoka MQTT katika mradi wa 1, somo la 4 ikiwa inahitajika](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Unaweza kupata msimbo huu katika folda ya [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt).

Hakikisha msimbo unaendesha kwenye kifaa chako na seva ya ndani, na ujaribu kwa kubadilisha viwango vya unyevu wa udongo, ama kwa kubadilisha thamani zinazotumwa na sensa ya virtual, au kwa kubadilisha viwango vya unyevu wa udongo kwa kuongeza maji au kuondoa sensa kutoka kwenye udongo.

## Muda wa sensa na actuator

Katika somo la 3 ulijenga taa ya usiku - LED inayowashwa mara tu kiwango cha chini cha mwanga kinapogunduliwa na sensa ya mwanga. Sensa ya mwanga iligundua mabadiliko ya viwango vya mwanga mara moja, na kifaa kiliweza kujibu haraka, kikizuiliwa tu na urefu wa kuchelewa katika kazi ya `loop` au `while True:`. Kama msanidi wa IoT, huwezi kila wakati kutegemea mzunguko wa maoni wa haraka kama huo.

### Muda kwa unyevu wa udongo

Ikiwa ulifanya somo la mwisho kuhusu unyevu wa udongo kwa kutumia sensa ya kimwili, ungeweza kugundua kuwa ilichukua sekunde chache kwa usomaji wa unyevu wa udongo kushuka baada ya kumwagilia mmea wako. Hii si kwa sababu sensa ni polepole, lakini kwa sababu inachukua muda kwa maji kupenya kwenye udongo.
💁 Ikiwa ulimwagilia maji karibu sana na kihisi, huenda uliona usomaji ukishuka haraka kisha kurudi juu - hii inasababishwa na maji karibu na kihisi kusambaa kwenye sehemu nyingine ya udongo, na kupunguza unyevu wa udongo karibu na kihisi.
![Kipimo cha unyevu wa udongo cha 658 hakibadiliki wakati wa kumwagilia, kinashuka tu hadi 320 baada ya maji kupenya kwenye udongo](../../../../../translated_images/sw/soil-moisture-travel.a0e31af222cf1438.webp)

Katika mchoro hapo juu, kipimo cha unyevu wa udongo kinaonyesha 658. Mmea unamwagiliwa maji, lakini kipimo hiki hakibadiliki mara moja kwa sababu maji bado hayajafika kwenye kihisi. Kumwagilia maji kunaweza hata kumalizika kabla ya maji kufika kwenye kihisi na thamani kushuka ili kuonyesha kiwango kipya cha unyevu.

Ikiwa ungekuwa unaandika msimbo wa kudhibiti mfumo wa umwagiliaji kupitia relay kwa kutumia viwango vya unyevu wa udongo, ungehitaji kuzingatia ucheleweshaji huu na kujenga muda wa busara zaidi kwenye kifaa chako cha IoT.

✅ Chukua muda kufikiria jinsi unavyoweza kufanya hivi.

### Kudhibiti muda wa kihisi na actuator

Fikiria umepewa jukumu la kujenga mfumo wa umwagiliaji kwa shamba. Kulingana na aina ya udongo, kiwango bora cha unyevu wa udongo kwa mimea inayolimwa kimepatikana kuwa sawa na kipimo cha voltage ya analogi cha 400-450.

Ungeweza kuandika programu ya kifaa kwa njia sawa na taa ya usiku - kila wakati kihisi kinaposoma zaidi ya 450, washa relay ili kuwasha pampu. Tatizo ni kwamba maji huchukua muda kufika kutoka kwenye pampu, kupitia udongo hadi kwenye kihisi. Kihisi kitasimamisha maji kinapogundua kiwango cha 450, lakini kiwango cha maji kitaendelea kushuka kwa sababu maji yaliyopampiwa yanaendelea kupenya kwenye udongo. Matokeo ya mwisho ni maji kupotea, na hatari ya kuharibu mizizi.

✅ Kumbuka - maji mengi yanaweza kuwa mabaya kwa mimea kama maji kidogo, na yanapoteza rasilimali muhimu.

Suluhisho bora ni kuelewa kwamba kuna ucheleweshaji kati ya actuator kuwashwa na mali inayosomwa na kihisi kubadilika. Hii inamaanisha sio tu kwamba kihisi kinapaswa kusubiri kwa muda kabla ya kupima thamani tena, lakini actuator inahitaji kuzimwa kwa muda kabla ya kipimo kingine cha kihisi kuchukuliwa.

Je, relay inapaswa kuwashwa kwa muda gani kila wakati? Ni bora kuwa mwangalifu na kuwasha relay kwa muda mfupi tu, kisha kusubiri maji kupenya, kisha kuangalia tena viwango vya unyevu. Baada ya yote, unaweza kuwasha tena kuongeza maji zaidi, huwezi kuondoa maji kutoka kwenye udongo.

> 💁 Udhibiti wa muda wa aina hii ni maalum sana kwa kifaa cha IoT unachojenga, mali unayopima na vihisi na actuators vinavyotumika.

![Mmea wa strawberry umeunganishwa na maji kupitia pampu, na pampu imeunganishwa na relay. Relay na kihisi cha unyevu wa udongo kwenye mmea vyote vimeunganishwa na Raspberry Pi](../../../../../translated_images/sw/strawberry-with-pump.b410fc72ac6aabad.webp)

Kwa mfano, nina mmea wa strawberry na kihisi cha unyevu wa udongo na pampu inayodhibitiwa na relay. Nimegundua kwamba ninapoongeza maji inachukua takriban sekunde 20 kwa kipimo cha unyevu wa udongo kutulia. Hii inamaanisha ninahitaji kuzima relay na kusubiri sekunde 20 kabla ya kuangalia viwango vya unyevu. Ningependelea kuwa na maji kidogo kuliko mengi - naweza kuwasha pampu tena, lakini siwezi kuondoa maji kutoka kwenye mmea.

![Hatua ya 1, chukua kipimo. Hatua ya 2, ongeza maji. Hatua ya 3, subiri maji kupenya kwenye udongo. Hatua ya 4, chukua kipimo tena](../../../../../translated_images/sw/soil-moisture-delay.865f3fae206db01d.webp)

Hii inamaanisha mchakato bora wa kumwagilia ungekuwa kama:

* Washa pampu kwa sekunde 5
* Subiri sekunde 20
* Angalia unyevu wa udongo
* Ikiwa kiwango bado kiko juu ya kile unachohitaji, rudia hatua zilizo hapo juu

Sekunde 5 zinaweza kuwa nyingi kwa pampu, hasa ikiwa viwango vya unyevu viko juu kidogo tu ya kiwango kinachohitajika. Njia bora ya kujua muda wa kutumia ni kujaribu, kisha kurekebisha unapopata data ya kihisi, kwa mchakato wa maoni wa mara kwa mara. Hii inaweza hata kusababisha muda wa kina zaidi, kama kuwasha pampu kwa sekunde 1 kwa kila 100 juu ya kiwango kinachohitajika cha unyevu wa udongo, badala ya sekunde 5 zilizowekwa.

✅ Fanya utafiti: Je, kuna mambo mengine ya muda ya kuzingatia? Je, mmea unaweza kumwagiliwa wakati wowote unyevu wa udongo ukiwa chini, au kuna nyakati maalum za siku ambazo ni nzuri na mbaya kwa kumwagilia mimea?

> 💁 Utabiri wa hali ya hewa pia unaweza kuzingatiwa wakati wa kudhibiti mifumo ya umwagiliaji wa moja kwa moja kwa kilimo cha nje. Ikiwa mvua inatarajiwa, basi umwagiliaji unaweza kusimamishwa hadi mvua itakapomalizika. Wakati huo udongo unaweza kuwa na unyevu wa kutosha kwamba hauhitaji kumwagiliwa, njia bora zaidi kuliko kupoteza maji kwa kumwagilia kabla ya mvua.

## Ongeza muda kwenye seva yako ya kudhibiti mimea

Msimbo wa seva unaweza kubadilishwa ili kuongeza udhibiti kuhusu muda wa mzunguko wa umwagiliaji, na kusubiri viwango vya unyevu wa udongo kubadilika. Mantiki ya seva ya kudhibiti muda wa relay ni:

1. Ujumbe wa telemetry unapokelewa
1. Angalia kiwango cha unyevu wa udongo
1. Ikiwa kiko sawa, usifanye chochote. Ikiwa kipimo ni kikubwa sana (inamaanisha unyevu wa udongo ni mdogo sana) basi:
    1. Tuma amri ya kuwasha relay
    1. Subiri sekunde 5
    1. Tuma amri ya kuzima relay
    1. Subiri sekunde 20 kwa viwango vya unyevu wa udongo kutulia

Mzunguko wa umwagiliaji, mchakato kutoka kupokea ujumbe wa telemetry hadi kuwa tayari kushughulikia viwango vya unyevu wa udongo tena, huchukua takriban sekunde 25. Tunatuma viwango vya unyevu wa udongo kila sekunde 10, kwa hivyo kuna mwingiliano ambapo ujumbe unapokelewa wakati seva inasubiri viwango vya unyevu wa udongo kutulia, ambavyo vinaweza kuanzisha mzunguko mwingine wa umwagiliaji.

Kuna chaguo mbili za kushughulikia hili:

* Badilisha msimbo wa kifaa cha IoT kutuma telemetry kila dakika moja tu, kwa njia hii mzunguko wa umwagiliaji utakuwa umekamilika kabla ya ujumbe mwingine kutumwa
* Jiondoe kwenye telemetry wakati wa mzunguko wa umwagiliaji

Chaguo la kwanza si suluhisho bora kila wakati kwa mashamba makubwa. Mkulima anaweza kutaka kukusanya viwango vya unyevu wa udongo wakati udongo unamwagiliwa kwa uchambuzi wa baadaye, kwa mfano kufahamu mtiririko wa maji katika maeneo tofauti ya shamba ili kuongoza umwagiliaji ulio na lengo zaidi. Chaguo la pili ni bora - msimbo unapuuzia tu telemetry wakati hauwezi kuitumia, lakini telemetry bado ipo kwa huduma zingine ambazo zinaweza kujiandikisha nayo.

> 💁 Data ya IoT haitumwi kutoka kifaa kimoja tu kwenda huduma moja tu, badala yake vifaa vingi vinaweza kutuma data kwa broker, na huduma nyingi zinaweza kusikiliza data kutoka kwa broker. Kwa mfano, huduma moja inaweza kusikiliza data ya unyevu wa udongo na kuihifadhi kwenye hifadhidata kwa uchambuzi wa baadaye. Huduma nyingine pia inaweza kusikiliza telemetry hiyo hiyo kudhibiti mfumo wa umwagiliaji.

### Kazi - ongeza muda kwenye seva yako ya kudhibiti mimea

Sasisha msimbo wa seva yako ili kuwasha relay kwa sekunde 5, kisha kusubiri sekunde 20.

1. Fungua folda ya `soil-moisture-sensor-server` kwenye VS Code ikiwa haijafunguliwa tayari. Hakikisha mazingira halisi yamewashwa.

1. Fungua faili ya `app.py`

1. Ongeza msimbo ufuatao kwenye faili ya `app.py` chini ya uingizaji uliopo:

    ```python
    import threading
    ```

    Kauli hii inaingiza `threading` kutoka maktaba za Python, threading inaruhusu Python kutekeleza msimbo mwingine wakati wa kusubiri.

1. Ongeza msimbo ufuatao kabla ya kazi ya `handle_telemetry` inayoshughulikia ujumbe wa telemetry unaopokelewa na msimbo wa seva:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Hii inafafanua muda wa kuwasha relay (`water_time`), na muda wa kusubiri baadaye kuangalia unyevu wa udongo (`wait_time`).

1. Chini ya msimbo huu, ongeza yafuatayo:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Msimbo huu unafafanua kazi inayoitwa `send_relay_command` ambayo inatuma amri kupitia MQTT kudhibiti relay. Telemetry inaundwa kama kamusi, kisha inabadilishwa kuwa kamba ya JSON. Thamani inayopitishwa kwenye `state` inaamua ikiwa relay inapaswa kuwashwa au kuzimwa.

1. Baada ya kazi ya `send_relay_code`, ongeza msimbo ufuatao:

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    Hii inafafanua kazi ya kudhibiti relay kulingana na muda unaohitajika. Inaanza kwa kujiondoa kwenye telemetry ili ujumbe wa unyevu wa udongo usishughulikiwe wakati umwagiliaji unafanyika. Kisha inatuma amri ya kuwasha relay. Inasubiri kwa `water_time` kabla ya kutuma amri ya kuzima relay. Hatimaye inasubiri viwango vya unyevu wa udongo kutulia kwa sekunde `wait_time`. Kisha inajiandikisha tena kwenye telemetry.

1. Badilisha kazi ya `handle_telemetry` kuwa ifuatayo:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Msimbo huu unakagua kiwango cha unyevu wa udongo. Ikiwa ni zaidi ya 450, udongo unahitaji kumwagiliwa, kwa hivyo inaita kazi ya `control_relay`. Kazi hii inaendeshwa kwenye thread tofauti, ikifanya kazi kwa nyuma.

1. Hakikisha kifaa chako cha IoT kinafanya kazi, kisha endesha msimbo huu. Badilisha viwango vya unyevu wa udongo na uangalie kinachotokea kwa relay - inapaswa kuwashwa kwa sekunde 5 kisha kubaki imezimwa kwa angalau sekunde 20, ikiwashwa tu ikiwa viwango vya unyevu wa udongo havitoshi.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    Njia nzuri ya kujaribu hii kwenye mfumo wa umwagiliaji uliosimuliwa ni kutumia udongo mkavu, kisha kumimina maji kwa mikono wakati relay imewashwa, ukisimamisha kumimina maji wakati relay inazimwa.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing).

> 💁 Ikiwa unataka kutumia pampu kujenga mfumo halisi wa umwagiliaji, basi unaweza kutumia [pampu ya maji ya 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) na [usambazaji wa umeme wa terminal ya USB](https://www.adafruit.com/product/3628). Hakikisha umeme unaoingia au kutoka kwenye pampu umeunganishwa kupitia relay.

---

## 🚀 Changamoto

Je, unaweza kufikiria vifaa vingine vya IoT au vya umeme ambavyo vina tatizo kama hili ambapo inachukua muda kwa matokeo ya actuator kufikia kihisi? Labda unavyo kadhaa nyumbani au shuleni.

* Ni mali gani wanapima?
* Inachukua muda gani kwa mali kubadilika baada ya actuator kutumika?
* Je, ni sawa kwa mali kubadilika kupita thamani inayohitajika?
* Inawezaje kurudishwa kwenye thamani inayohitajika ikiwa inahitajika?

## Jaribio la baada ya somo

[Jaribio la baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Mapitio na Kujisomea

* Soma zaidi kuhusu relay ikiwa ni pamoja na matumizi yake ya kihistoria kwenye ubadilishaji wa simu kwenye [ukurasa wa Wikipedia wa relay](https://wikipedia.org/wiki/Relay).

## Kazi

[Jenga mzunguko wa umwagiliaji ulio bora zaidi](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.