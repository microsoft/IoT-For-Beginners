<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-27T23:16:50+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "sw"
}
-->
# Kutabiri Ukuaji wa Mimea kwa IoT

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.sw.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa zaidi.

## Maswali ya awali ya somo

[Maswali ya awali ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Utangulizi

Mimea inahitaji vitu fulani ili kukua - maji, dioksidi ya kaboni, virutubisho, mwanga, na joto. Katika somo hili, utajifunza jinsi ya kuhesabu viwango vya ukuaji na ukomavu wa mimea kwa kupima joto la hewa.

Katika somo hili tutashughulikia:

* [Kilimo cha kidijitali](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Kwa nini joto ni muhimu katika kilimo?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Kupima joto la mazingira](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Siku za digrii za ukuaji (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Hesabu GDD kwa kutumia data ya sensa ya joto](../../../../../2-farm/lessons/1-predict-plant-growth)

## Kilimo cha kidijitali

Kilimo cha Kidijitali kinabadilisha jinsi tunavyolima, kwa kutumia zana za kukusanya, kuhifadhi na kuchambua data kutoka kwenye kilimo. Kwa sasa tuko katika kipindi kinachojulikana kama 'Mapinduzi ya Nne ya Viwanda' na Jukwaa la Uchumi wa Dunia, na kuongezeka kwa kilimo cha kidijitali kumetajwa kama 'Mapinduzi ya Nne ya Kilimo', au 'Kilimo 4.0'.

> 🎓 Neno Kilimo cha Kidijitali pia linajumuisha 'mnyororo wa thamani wa kilimo', yaani safari nzima kutoka shambani hadi mezani. Hii inajumuisha kufuatilia ubora wa mazao wakati chakula kinaposafirishwa na kusindikwa, mifumo ya maghala na biashara mtandaoni, hata programu za kukodisha matrekta!

Mabadiliko haya yanawaruhusu wakulima kuongeza mavuno, kutumia mbolea na dawa za kuua wadudu kwa kiasi kidogo, na kutumia maji kwa ufanisi zaidi. Ingawa kwa kiasi kikubwa hutumika katika mataifa tajiri, sensa na vifaa vingine vinapungua bei polepole, na kuifanya iweze kufikiwa zaidi katika mataifa yanayoendelea.

Baadhi ya mbinu zinazowezeshwa na kilimo cha kidijitali ni:

* Upimaji wa joto - kupima joto kunawaruhusu wakulima kutabiri ukuaji na ukomavu wa mimea.
* Kumwagilia kiotomatiki - kupima unyevu wa udongo na kuwasha mifumo ya umwagiliaji wakati udongo ni mkavu sana, badala ya kumwagilia kwa wakati maalum. Kumwagilia kwa wakati maalum kunaweza kusababisha mazao kuwa na maji kidogo wakati wa joto kali, au maji mengi wakati wa mvua. Kwa kumwagilia tu wakati udongo unahitaji, wakulima wanaweza kuboresha matumizi yao ya maji.
* Udhibiti wa wadudu - wakulima wanaweza kutumia kamera kwenye roboti za kiotomatiki au drones kuangalia wadudu, kisha kutumia dawa za kuua wadudu tu pale inapohitajika, kupunguza kiasi cha dawa zinazotumika na kupunguza uchafuzi wa maji ya karibu.

✅ Fanya utafiti. Ni mbinu gani nyingine zinazotumika kuboresha mavuno ya kilimo?

> 🎓 Neno 'Kilimo cha Usahihi' linatumika kufafanua uchunguzi, upimaji na kujibu mahitaji ya mazao kwa msingi wa shamba moja, au hata sehemu za shamba. Hii inajumuisha kupima viwango vya maji, virutubisho na wadudu na kujibu kwa usahihi, kama vile kumwagilia sehemu ndogo tu ya shamba.

## Kwa nini joto ni muhimu katika kilimo?

Wakati wa kujifunza kuhusu mimea, wanafunzi wengi hufundishwa kuhusu umuhimu wa maji, mwanga, dioksidi ya kaboni, na virutubisho. Mimea pia inahitaji joto ili kukua - ndiyo sababu mimea huchanua wakati wa masika joto linapoongezeka, kwa nini snowdrops au daffodils zinaweza kuchipua mapema kutokana na kipindi kifupi cha joto, na kwa nini nyumba za joto na greenhouses ni nzuri katika kufanya mimea kukua.

> 🎓 Nyumba za joto na greenhouses hufanya kazi sawa, lakini kuna tofauti muhimu. Nyumba za joto huwashwa kwa njia ya bandia na kuruhusu wakulima kudhibiti joto kwa usahihi zaidi, greenhouses hutegemea jua kwa joto na kawaida udhibiti pekee ni madirisha au sehemu nyingine za kufungua ili kuruhusu joto kutoka.

Mimea ina joto la msingi au la chini, joto bora, na joto la juu, yote yanategemea wastani wa joto la kila siku.

* Joto la msingi - hili ndilo joto la wastani la kila siku la chini linalohitajika kwa mmea kukua.
* Joto bora - hili ndilo joto bora la wastani la kila siku kupata ukuaji wa haraka zaidi.
* Joto la juu - hili ndilo joto la juu zaidi ambalo mmea unaweza kuvumilia. Zaidi ya hili mmea utasimamisha ukuaji wake ili kuhifadhi maji na kuendelea kuishi.

> 💁 Haya ni wastani wa joto, yaliyopatikana kwa kujumlisha joto la mchana na usiku. Mimea pia inahitaji joto tofauti mchana na usiku ili kusaidia mchakato wa fotosinthesisi kwa ufanisi zaidi na kuhifadhi nishati usiku.

Kila aina ya mmea ina thamani tofauti kwa joto lake la msingi, bora, na la juu. Hii ndiyo sababu mimea mingine hustawi katika nchi za joto, na mingine katika nchi za baridi.

✅ Fanya utafiti. Kwa mimea yoyote uliyo nayo kwenye bustani yako, shule, au mbuga ya karibu, angalia kama unaweza kupata joto la msingi.

![Grafu inayoonyesha kiwango cha ukuaji kinavyoongezeka joto linapoongezeka, kisha kushuka joto linapokuwa juu sana](../../../../../translated_images/plant-growth-temp-graph.c6d69c9478e6ca83.sw.png)

Grafu hapo juu inaonyesha mfano wa grafu ya ukuaji kulingana na joto. Hadi joto la msingi hakuna ukuaji. Kiwango cha ukuaji kinaongezeka hadi joto bora, kisha kushuka baada ya kufikia kilele hiki. Katika joto la juu ukuaji husimama.

Umbo la grafu hii hutofautiana kutoka kwa aina moja ya mmea hadi nyingine. Baadhi zina mteremko mkali zaidi juu ya joto bora, nyingine zina ongezeko polepole kutoka joto la msingi hadi bora.

> 💁 Ili mkulima apate ukuaji bora, atahitaji kujua thamani za joto tatu na kuelewa umbo la grafu kwa mimea anayolima.

Ikiwa mkulima ana udhibiti wa joto, kwa mfano katika nyumba ya joto ya kibiashara, basi anaweza kuboresha ukuaji wa mimea yake. Nyumba ya joto ya kibiashara inayolima nyanya kwa mfano itakuwa na joto lililowekwa karibu na 25°C wakati wa mchana na 20°C usiku ili kupata ukuaji wa haraka zaidi.

> 🍅 Kwa kuchanganya joto hili na taa za bandia, mbolea, na viwango vilivyodhibitiwa vya dioksidi ya kaboni, wakulima wa kibiashara wanaweza kulima na kuvuna mwaka mzima.

## Kupima joto la mazingira

Sensor za joto zinaweza kutumika na vifaa vya IoT kupima joto la mazingira.

### Kazi - kupima joto

Fanya kazi kupitia mwongozo husika ili kufuatilia joto kwa kutumia kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-temp.md)
* [Kompyuta ya bodi moja - Raspberry Pi](pi-temp.md)
* [Kompyuta ya bodi moja - Kifaa cha mtandaoni](virtual-device-temp.md)

## Siku za digrii za ukuaji

Siku za digrii za ukuaji (pia zinajulikana kama vitengo vya digrii za ukuaji) ni njia ya kupima ukuaji wa mimea kulingana na joto. Ikiwa mmea una maji ya kutosha, virutubisho, na dioksidi ya kaboni, joto linaamua kiwango cha ukuaji.

Siku za digrii za ukuaji, au GDD, zinahesabiwa kwa siku kama wastani wa joto kwa siku katika Celsius juu ya joto la msingi la mmea. Kila mmea unahitaji idadi fulani ya GDD ili kukua, kuchanua au kutoa mazao na kukomaa. Kadri GDD inavyokuwa nyingi kila siku, ndivyo mmea utakavyokua haraka.

> 🇺🇸 Kwa Wamarekani, siku za digrii za ukuaji zinaweza pia kuhesabiwa kwa kutumia Fahrenheit. 5 GDD (siku za digrii za ukuaji katika Celsius) ni sawa na 9 GDD (siku za digrii za ukuaji katika Fahrenheit).

Mchoro kamili wa GDD ni mgumu kidogo, lakini kuna mlinganyo rahisi ambao mara nyingi hutumika kama makadirio mazuri:

![GDD = T max + T min kugawanywa kwa 2, yote ikipunguzwa na T base](../../../../../translated_images/gdd-calculation.79b3660f9c5757aa92dc2dd2cdde75344e2d2c1565c4b3151640f7887edc0275.sw.png)

* **GDD** - hii ni idadi ya siku za digrii za ukuaji
* **T max** - hii ni joto la juu la kila siku katika digrii Celsius
* **T min** - hii ni joto la chini la kila siku katika digrii Celsius
* **T base** - hii ni joto la msingi la mmea katika digrii Celsius

> 💁 Kuna tofauti zinazoshughulikia T max juu ya 30°C au T min chini ya T base, lakini tutazipuuza kwa sasa.

### Mfano - Mahindi 🌽

Kulingana na aina, mahindi yanahitaji kati ya 800 na 2,700 GDD ili kukomaa, na joto la msingi la 10°C.

Katika siku ya kwanza juu ya joto la msingi, joto lifuatalo lilipimwa:

| Kipimo      | Joto °C |
| :---------- | :-----: |
| Juu         | 16      |
| Chini       | 12      |

Tukijaza namba hizi kwenye hesabu yetu:

* T max = 16
* T min = 12
* T base = 10

Hii inatoa hesabu ya:

![GDD = 16 + 12 kugawanywa kwa 2, yote ikipunguzwa na 10, ikitoa jibu la 4](../../../../../translated_images/gdd-calculation-corn.64a58b7a7afcd0dfd46ff733996d939f17f4f3feac9f0d1c632be3523e51ebd9.sw.png)

Mahindi yalipata 4 GDD siku hiyo. Tukichukulia aina ya mahindi inayohitaji 800 GDD ili kukomaa, itahitaji GDD nyingine 796 kufikia ukomavu.

✅ Fanya utafiti. Kwa mimea yoyote uliyo nayo kwenye bustani yako, shule, au mbuga ya karibu, angalia kama unaweza kupata idadi ya GDD inayohitajika kufikia ukomavu au kutoa mazao.

## Hesabu GDD kwa kutumia data ya sensa ya joto

Mimea haikui kwa tarehe maalum - kwa mfano huwezi kupanda mbegu na kujua kwamba mmea utazaa matunda siku 100 baadaye. Badala yake, kama mkulima unaweza kuwa na wazo la takriban muda gani mmea unachukua kukua, kisha ungeangalia kila siku kuona mazao yako yameiva.

Hii ina athari kubwa ya kazi kwenye shamba kubwa, na inahatarisha mkulima kukosa mazao ambayo yameiva mapema bila kutarajiwa. Kwa kupima joto, mkulima anaweza kuhesabu GDD ambayo mmea umepokea, na kumruhusu kuangalia tu karibu na ukomavu unaotarajiwa.

Kwa kukusanya data ya joto kwa kutumia kifaa cha IoT, mkulima anaweza kuarifiwa kiotomatiki wakati mimea iko karibu na ukomavu. Muundo wa kawaida wa hili ni kuwa na vifaa vya IoT kupima joto, kisha kuchapisha data hii ya telemetry kupitia mtandao kwa kutumia kitu kama MQTT. Nambari ya seva kisha husikiliza data hii na kuihifadhi mahali fulani, kama kwenye hifadhidata. Hii inamaanisha data inaweza kuchambuliwa baadaye, kama kazi ya usiku ya kuhesabu GDD kwa siku, kujumlisha GDD kwa kila zao hadi sasa na kutoa tahadhari ikiwa mmea uko karibu na ukomavu.

![Data ya telemetry inatumwa kwa seva na kisha kuhifadhiwa kwenye hifadhidata](../../../../../translated_images/save-telemetry-database.ddc9c6bea0c5ba39.sw.png)

Nambari ya seva pia inaweza kuongeza data ya ziada. Kwa mfano, kifaa cha IoT kinaweza kuchapisha kitambulisho kuonyesha ni kifaa gani, na nambari ya seva inaweza kutumia hii kutafuta eneo la kifaa, na mazao gani kinachofuatilia. Pia inaweza kuongeza data ya msingi kama wakati wa sasa kwani baadhi ya vifaa vya IoT havina vifaa vinavyohitajika kufuatilia wakati sahihi, au vinahitaji nambari ya ziada kusoma wakati wa sasa kupitia mtandao.

✅ Kwa nini unadhani mashamba tofauti yanaweza kuwa na joto tofauti?

### Kazi - kuchapisha taarifa za joto

Fanya kazi kupitia mwongozo husika ili kuchapisha data ya joto kupitia MQTT kwa kutumia kifaa chako cha IoT ili iweze kuchambuliwa baadaye:

* [Arduino - Wio Terminal](wio-terminal-temp-publish.md)
* [Kompyuta ya bodi moja - Raspberry Pi/Kifaa cha IoT cha mtandaoni](single-board-computer-temp-publish.md)

### Kazi - kukamata na kuhifadhi taarifa za joto

Baada ya kifaa cha IoT kuchapisha telemetry, nambari ya seva inaweza kuandikwa ili kujiunga na data hii na kuihifadhi. Badala ya kuihifadhi kwenye hifadhidata, nambari ya seva itaihifadhi kwenye faili ya Comma Separated Values (CSV). Faili za CSV huhifadhi data kama safu za thamani kama maandishi, na kila thamani ikitenganishwa na koma, na kila rekodi kwenye mstari mpya. Ni njia rahisi, inayosomeka na binadamu na inayoungwa mkono vizuri ya kuhifadhi data kama faili.

Faili ya CSV itakuwa na safu mbili - *tarehe* na *joto*. Safu ya *tarehe* imewekwa kama tarehe na wakati wa sasa ambapo ujumbe ulipokelewa na seva, *joto* linatoka kwenye ujumbe wa telemetry.

1. Rudia hatua katika somo la 4 kuunda nambari ya seva ya kujiunga na telemetry. Huna haja ya kuongeza nambari ya kuchapisha amri.

    Hatua za hili ni:

    * Sanidi na wezesha Mazingira ya Virtual ya Python

    * Sakinisha kifurushi cha paho-mqtt kupitia pip

    * Andika nambari ya kusikiliza ujumbe wa MQTT uliyochapishwa kwenye mada ya telemetry

      > ⚠️ Unaweza kurejelea [maelekezo katika somo la 4 ya kuunda programu ya Python ya kupokea telemetry ikiwa inahitajika](../../../1-getting-started/lessons/4-connect-internet/README.md#receive-telemetry-from-the-mqtt-broker).

    Peana jina la folda ya mradi huu `temperature-sensor-server`.

1. Hakikisha `client_name` inaakisi mradi huu:

    ```cpp
    client_name = id + 'temperature_sensor_server'
    ```

1. Ongeza uingizaji ufuatao juu ya faili, chini ya uingizaji uliopo:

    ```python
    from os import path
    import csv
    from datetime import datetime
    ```

    Hii inaingiza maktaba ya kusoma faili, maktaba ya kuingiliana na faili za CSV, na maktaba ya kusaidia na tarehe na wakati.

1. Ongeza nambari ifuatayo kabla ya kazi ya `handle_telemetry`:

    ```python
    temperature_file_name = 'temperature.csv'
    fieldnames = ['date', 'temperature']
    
    if not path.exists(temperature_file_name):
        with open(temperature_file_name, mode='w') as csv_file:
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
            writer.writeheader()
    ```

    Nambari hii inatangaza baadhi ya constants kwa jina la faili la kuandika, na jina la vichwa vya safu kwa faili ya CSV. Safu ya kwanza ya faili ya CSV kwa kawaida ina vichwa vya safu vilivyotenganishwa na koma.

    Nambari kisha inakagua kuona kama faili ya CSV tayari ipo. Ikiwa haipo, inaundwa na vichwa vya safu kwenye safu ya kwanza.

1. Ongeza nambari ifuatayo mwishoni mwa kazi ya `handle_telemetry`:

    ```python
    with open(temperature_file_name, mode='a') as temperature_file:        
        temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
        temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})
    ```
Faili hii inafungua faili la CSV, kisha inaongeza safu mpya mwishoni. Safu hiyo ina tarehe na muda wa sasa uliopangwa katika muundo unaosomeka kwa urahisi, ikifuatiwa na joto lililopokelewa kutoka kwa kifaa cha IoT. Data huhifadhiwa katika [muundo wa ISO 8601](https://wikipedia.org/wiki/ISO_8601) na eneo la saa, lakini bila microseconds.

1. Endesha msimbo huu kama ulivyofanya awali, ukihakikisha kifaa chako cha IoT kinatuma data. Faili la CSV linaloitwa `temperature.csv` litaundwa katika folda hiyo hiyo. Ukilitazama utaona tarehe/muda na vipimo vya joto:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Endesha msimbo huu kwa muda ili kukusanya data. Kwa hali bora, unapaswa kuendesha hii kwa siku nzima ili kukusanya data ya kutosha kwa mahesabu ya GDD.

    
> 💁 Ikiwa unatumia Kifaa cha IoT cha Virtual, chagua kisanduku cha random na weka kiwango ili kuepuka kupata joto sawa kila wakati thamani ya joto inarudishwa.
    ![Chagua kisanduku cha random na weka kiwango](../../../../../translated_images/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.sw.png) 

    > 💁 Ikiwa unataka kuendesha hii kwa siku nzima, basi unahitaji kuhakikisha kompyuta ambayo msimbo wa seva yako unaendesha haitalala, ama kwa kubadilisha mipangilio ya nguvu, au kuendesha kitu kama [msimbo huu wa Python wa kuweka mfumo ukiwa hai](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Unaweza kupata msimbo huu katika folda ya [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Kazi - hesabu GDD ukitumia data iliyohifadhiwa

Mara seva inapokusanya data ya joto, GDD ya mmea inaweza kuhesabiwa.

Hatua za kufanya hivi kwa mikono ni:

1. Tafuta joto la msingi la mmea. Kwa mfano, kwa strawberry joto la msingi ni 10°C.

1. Kutoka kwa `temperature.csv`, tafuta joto la juu na la chini kwa siku hiyo.

1. Tumia hesabu ya GDD iliyotolewa awali kuhesabu GDD.

Kwa mfano, ikiwa joto la juu kwa siku ni 25°C, na la chini ni 12°C:

![GDD = 25 + 12 gawanya kwa 2, kisha toa 10 kutoka kwa matokeo ukipata 8.5](../../../../../translated_images/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.sw.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Kwa hivyo strawberry zimepokea **8.5** GDD. Strawberry zinahitaji takriban 250 GDD ili kuzaa matunda, kwa hivyo bado kuna muda kidogo.

---

## 🚀 Changamoto

Mimea inahitaji zaidi ya joto ili kukua. Ni vitu gani vingine vinahitajika?

Kwa hivi, tafuta kama kuna sensa zinazoweza kupima vitu hivyo. Je, kuna actuators za kudhibiti viwango hivi? Unawezaje kuweka pamoja kifaa kimoja au zaidi cha IoT ili kuboresha ukuaji wa mimea?

## Maswali ya Baada ya Somo

[Maswali ya Baada ya Somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Mapitio & Kujisomea

* Soma zaidi kuhusu kilimo cha kidijitali kwenye [ukurasa wa Wikipedia wa Kilimo Kidijitali](https://wikipedia.org/wiki/Digital_agriculture). Pia soma zaidi kuhusu kilimo cha usahihi kwenye [ukurasa wa Wikipedia wa Kilimo cha Usahihi](https://wikipedia.org/wiki/Precision_agriculture).
* Hesabu kamili ya growing degree days ni ngumu zaidi kuliko ile rahisi iliyotolewa hapa. Soma zaidi kuhusu equation ngumu na jinsi ya kushughulikia joto chini ya msingi kwenye [ukurasa wa Wikipedia wa Growing Degree Day](https://wikipedia.org/wiki/Growing_degree-day).
* Chakula kinaweza kuwa adimu siku zijazo ikiwa bado tutatumia mbinu zile zile za kilimo. Jifunze zaidi kuhusu mbinu za kilimo za teknolojia ya juu katika [video ya Hi-Tech Farms of Future kwenye YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Kazi

[Onyesha data ya GDD ukitumia Jupyter Notebook](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.