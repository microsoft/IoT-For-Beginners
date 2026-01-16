<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "71b5040e0b3472f1c0949c9b55f224c0",
  "translation_date": "2025-08-27T22:03:59+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/README.md",
  "language_code": "sw"
}
-->
# Unganisha kifaa chako na Intaneti

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-4.7344e074ea68fa545fd320b12dce36d72dd62d28c3b4596cb26cf315f434b98f.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa zaidi.

Somo hili lilifundishwa kama sehemu ya [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) kutoka [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Somo lilifundishwa kupitia video mbili - somo la saa moja, na saa moja ya maswali na majibu kwa undani zaidi kuhusu sehemu za somo na kujibu maswali.

[![Somo la 4: Unganisha Kifaa Chako na Intaneti](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Somo la 4: Unganisha Kifaa Chako na Intaneti - Maswali na Majibu](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Bofya picha zilizo juu kutazama video

## Jaribio la kabla ya somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Utangulizi

**I** katika IoT inasimama kwa **Intaneti** - muunganisho wa wingu na huduma zinazowezesha vipengele vingi vya vifaa vya IoT, kuanzia kukusanya vipimo kutoka kwa sensa zilizounganishwa na kifaa, hadi kutuma ujumbe wa kudhibiti vichochezi. Vifaa vya IoT kwa kawaida huunganishwa na huduma moja ya wingu ya IoT kwa kutumia itifaki ya mawasiliano ya kawaida, na huduma hiyo inaunganishwa na programu yako ya IoT, kuanzia huduma za AI za kufanya maamuzi ya busara kuhusu data yako, hadi programu za wavuti za udhibiti au ripoti.

> 🎓 Data inayokusanywa kutoka kwa sensa na kutumwa kwenye wingu inaitwa telemetry.

Vifaa vya IoT vinaweza kupokea ujumbe kutoka kwenye wingu. Mara nyingi ujumbe huu huwa na amri - maelekezo ya kutekeleza kitendo aidha ndani (kama vile kuwasha upya au kusasisha programu), au kwa kutumia kichochezi (kama vile kuwasha taa).

Somo hili linaanzisha baadhi ya itifaki za mawasiliano ambazo vifaa vya IoT vinaweza kutumia kuunganishwa na wingu, na aina za data ambazo vinaweza kutuma au kupokea. Pia utajifunza kwa vitendo, kuongeza udhibiti wa intaneti kwenye taa yako ya usiku, na kuhamisha mantiki ya udhibiti wa LED kwenye 'server' inayotumia msimbo wa ndani.

Katika somo hili tutashughulikia:

* [Itifaki za mawasiliano](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetry](../../../../../1-getting-started/lessons/4-connect-internet)
* [Amri](../../../../../1-getting-started/lessons/4-connect-internet)

## Itifaki za mawasiliano

Kuna itifaki kadhaa maarufu za mawasiliano zinazotumiwa na vifaa vya IoT kuwasiliana na Intaneti. Maarufu zaidi zinategemea ujumbe wa kuchapisha/kusubscribe kupitia aina fulani ya broker. Vifaa vya IoT vinaunganishwa na broker na kuchapisha telemetry na kusubscribe kwa amri. Huduma za wingu pia zinaunganishwa na broker na kusubscribe kwa ujumbe wote wa telemetry na kuchapisha amri kwa vifaa maalum, au kwa vikundi vya vifaa.

![Vifaa vya IoT vinaunganishwa na broker na kuchapisha telemetry na kusubscribe kwa amri. Huduma za wingu zinaunganishwa na broker na kusubscribe kwa telemetry yote na kutuma amri kwa vifaa maalum.](../../../../../translated_images/sw/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT ni itifaki maarufu zaidi ya mawasiliano kwa vifaa vya IoT na imeelezwa katika somo hili. Itifaki nyingine ni pamoja na AMQP na HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) ni itifaki nyepesi, ya wazi ya ujumbe inayoweza kutuma ujumbe kati ya vifaa. Iliundwa mwaka 1999 kufuatilia mabomba ya mafuta, kabla ya kutolewa kama kiwango cha wazi miaka 15 baadaye na IBM.

MQTT ina broker mmoja na wateja wengi. Wateja wote huunganishwa na broker, na broker husambaza ujumbe kwa wateja husika. Ujumbe husambazwa kwa kutumia mada zilizotajwa, badala ya kutumwa moja kwa moja kwa mteja mmoja. Mteja anaweza kuchapisha kwenye mada, na wateja wowote wanaosubscribe kwa mada hiyo watapokea ujumbe.

![Kifaa cha IoT kinachochapisha telemetry kwenye mada ya /telemetry, na huduma ya wingu inayosubscribe kwa mada hiyo](../../../../../translated_images/sw/mqtt.cbf7f21d9adc3e17548b359444cc11bb4bf2010543e32ece9a47becf54438c23.png)

✅ Fanya utafiti. Ikiwa una vifaa vingi vya IoT, unaweza kuhakikisha vipi kwamba broker yako ya MQTT inaweza kushughulikia ujumbe wote?

### Unganisha kifaa chako cha IoT na MQTT

Sehemu ya kwanza ya kuongeza udhibiti wa Intaneti kwenye taa yako ya usiku ni kuunganisha na broker ya MQTT.

#### Kazi

Unganisha kifaa chako na broker ya MQTT.

Katika sehemu hii ya somo, utaunganisha taa yako ya usiku ya IoT na intaneti ili iweze kudhibitiwa kwa mbali. Baadaye katika somo hili, kifaa chako cha IoT kitatuma ujumbe wa telemetry kupitia MQTT kwa broker ya MQTT ya umma na kiwango cha mwanga, ambapo itachukuliwa na msimbo wa server ambao utaandika. Msimbo huu utachunguza kiwango cha mwanga na kutuma ujumbe wa amri kurudi kwa kifaa ukielekeza kuwasha au kuzima LED.

Matumizi halisi ya mpangilio kama huu yanaweza kuwa kukusanya data kutoka kwa sensa nyingi za mwanga kabla ya kuamua kuwasha taa, katika eneo lenye taa nyingi, kama uwanja wa michezo. Hii inaweza kuzuia taa kuwashwa ikiwa sensa moja tu imefunikwa na mawingu au ndege, lakini sensa nyingine zinagundua mwanga wa kutosha.

✅ Ni hali gani nyingine zinazoweza kuhitaji data kutoka kwa sensa nyingi kutathminiwa kabla ya kutuma amri?

Badala ya kushughulikia ugumu wa kusanidi broker ya MQTT kama sehemu ya kazi hii, unaweza kutumia server ya majaribio ya umma inayotumia [Eclipse Mosquitto](https://www.mosquitto.org), broker ya MQTT ya chanzo huria. Broker hii ya majaribio inapatikana kwa umma kwenye [test.mosquitto.org](https://test.mosquitto.org), na haihitaji akaunti kusanidiwa, hivyo ni zana nzuri ya kujaribu wateja na server za MQTT.

> 💁 Broker hii ya majaribio ni ya umma na si salama. Mtu yeyote anaweza kusikiliza unachochapisha, hivyo haipaswi kutumiwa na data yoyote inayohitaji kubaki siri.

![Mchoro wa mtiririko wa kazi unaonyesha viwango vya mwanga vinavyosomwa na kuchunguzwa, na LED ikidhibitiwa](../../../../../translated_images/sw/assignment-1-internet-flow.3256feab5f052fd273bf4e331157c574c2c3fa42e479836fc9c3586f41db35a5.png)

Fuata hatua husika hapa chini kuunganisha kifaa chako na broker ya MQTT:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Kompyuta ya bodi moja - Raspberry Pi/Kifaa cha IoT cha Virtual](single-board-computer-mqtt.md)

### Kuchunguza zaidi kuhusu MQTT

Mada zinaweza kuwa na uhierarkia, na wateja wanaweza kusubscribe kwa viwango tofauti vya uhierarkia kwa kutumia wildcards. Kwa mfano, unaweza kutuma ujumbe wa telemetry wa joto kwenye mada ya `/telemetry/temperature` na ujumbe wa unyevunyevu kwenye mada ya `/telemetry/humidity`, kisha katika programu yako ya wingu kusubscribe kwa mada ya `/telemetry/*` ili kupokea ujumbe wa telemetry wa joto na unyevunyevu.

Ujumbe unaweza kutumwa na ubora wa huduma (QoS), ambao huamua uhakika wa ujumbe kupokelewa.

* Mara moja tu - ujumbe hutumwa mara moja tu na mteja na broker hawachukui hatua za ziada kuthibitisha utoaji (tuma na usahau).
* Angalau mara moja - ujumbe unajaribiwa tena na mtumaji mara nyingi hadi uthibitisho upokewe (utoaji uliothibitishwa).
* Mara moja tu - mtumaji na mpokeaji wanashiriki katika mkono wa salamu wa viwango viwili ili kuhakikisha nakala moja tu ya ujumbe inapokelewa (utoaji uliohakikishwa).

✅ Ni hali gani zinaweza kuhitaji ujumbe uliohakikishwa zaidi ya ujumbe wa tuma na usahau?

Ingawa jina ni Message Queueing (herufi za mwanzo katika MQTT), haijumuishi foleni za ujumbe. Hii inamaanisha kwamba ikiwa mteja atakatika, kisha kuunganishwa tena, hatapokea ujumbe uliotumwa wakati wa kukatika, isipokuwa kwa ujumbe ambao tayari ulianza kushughulikiwa kwa kutumia mchakato wa QoS. Ujumbe unaweza kuwa na bendera ya kuhifadhiwa. Ikiwa bendera hii imewekwa, broker ya MQTT itahifadhi ujumbe wa mwisho uliotumwa kwenye mada hiyo na bendera hii, na kutuma kwa wateja wowote watakaosubscribe baadaye kwenye mada hiyo. Kwa njia hii, wateja watapata ujumbe wa hivi karibuni kila wakati.

MQTT pia inaunga mkono kazi ya kuendelea kuangalia ikiwa muunganisho bado hai wakati wa mapengo marefu kati ya ujumbe.

> 🦟 [Mosquitto kutoka Eclipse Foundation](https://mosquitto.org) ina broker ya MQTT ya bure unayoweza kuendesha mwenyewe ili kujaribu MQTT, pamoja na broker ya MQTT ya umma unayoweza kutumia kujaribu msimbo wako, iliyohifadhiwa kwenye [test.mosquitto.org](https://test.mosquitto.org).

Muunganisho wa MQTT unaweza kuwa wa umma na wazi, au wa usalama kwa kutumia majina ya mtumiaji na nywila, au vyeti.

> 💁 MQTT huwasiliana kupitia TCP/IP, itifaki ya mtandao ya msingi sawa na HTTP, lakini kwenye bandari tofauti. Unaweza pia kutumia MQTT kupitia websockets kuwasiliana na programu za wavuti zinazotumika kwenye kivinjari, au katika hali ambapo firewalls au sheria nyingine za mtandao zinazuia muunganisho wa kawaida wa MQTT.

## Telemetry

Neno telemetry linatokana na mizizi ya Kigiriki inayomaanisha kupima kwa mbali. Telemetry ni kitendo cha kukusanya data kutoka kwa sensa na kuituma kwenye wingu.

> 💁 Mojawapo ya vifaa vya kwanza vya telemetry vilivumbuliwa nchini Ufaransa mwaka 1874 na vilituma hali ya hewa ya wakati halisi na kina cha theluji kutoka Mont Blanc hadi Paris. Ilitumia waya za kimwili kwani teknolojia za bila waya hazikuwepo wakati huo.

Hebu tuangalie tena mfano wa thermostat ya kisasa kutoka Somo la 1.

![Thermostat iliyounganishwa na Intaneti ikitumia sensa nyingi za chumba](../../../../../translated_images/sw/telemetry.21e5d8b97649d2eb.webp)

Thermostat ina sensa za joto za kukusanya telemetry. Inaweza kuwa na sensa moja ya joto iliyojengwa ndani, na inaweza kuunganishwa na sensa nyingi za joto za nje kupitia itifaki ya bila waya kama [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Mfano wa data ya telemetry ambayo ingekuwa inatuma inaweza kuwa:

| Jina | Thamani | Maelezo |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Joto lililopimwa na sensa ya joto iliyojengwa ndani ya thermostat |
| `livingroom_temperature` | 19°C | Joto lililopimwa na sensa ya joto ya mbali ambayo imepewa jina `livingroom` kutambua chumba ilipo |
| `bedroom_temperature` | 21°C | Joto lililopimwa na sensa ya joto ya mbali ambayo imepewa jina `bedroom` kutambua chumba ilipo |

Huduma ya wingu inaweza kutumia data hii ya telemetry kufanya maamuzi kuhusu amri za kudhibiti joto.

### Tuma telemetry kutoka kwa kifaa chako cha IoT

Sehemu inayofuata ya kuongeza udhibiti wa Intaneti kwenye taa yako ya usiku ni kutuma kiwango cha mwanga cha telemetry kwa broker ya MQTT kwenye mada ya telemetry.

#### Kazi - tuma telemetry kutoka kwa kifaa chako cha IoT

Tuma kiwango cha mwanga cha telemetry kwa broker ya MQTT.

Data inatumwa ikiwa imekodwa kama JSON - kifupi cha JavaScript Object Notation, kiwango cha kuandika data kwa maandishi kwa kutumia jozi za funguo/thamani.

✅ Ikiwa hujawahi kukutana na JSON hapo awali, unaweza kujifunza zaidi kuhusu hilo kwenye [JSON.org documentation](https://www.json.org/).

Fuata hatua husika hapa chini kutuma telemetry kutoka kwa kifaa chako kwa broker ya MQTT:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Kompyuta ya bodi moja - Raspberry Pi/Kifaa cha IoT cha Virtual](single-board-computer-telemetry.md)

### Pokea telemetry kutoka kwa broker ya MQTT

Hakuna maana ya kutuma telemetry ikiwa hakuna kitu kingine kinachosikiliza. Telemetry ya kiwango cha mwanga inahitaji kitu kinachosikiliza ili kuchakata data. Msimbo wa 'server' ni aina ya msimbo ambao utapelekwa kwenye huduma ya wingu kama sehemu ya programu kubwa ya IoT, lakini hapa utauendesha msimbo huu ndani ya kompyuta yako (au kwenye Pi yako ikiwa unafanya kazi moja kwa moja hapo). Msimbo wa server unajumuisha programu ya Python inayosikiliza ujumbe wa telemetry kupitia MQTT na viwango vya mwanga. Baadaye katika somo hili utaufanya ujibu kwa ujumbe wa amri na maelekezo ya kuwasha au kuzima LED.

✅ Fanya utafiti: Nini kinatokea kwa ujumbe wa MQTT ikiwa hakuna msikilizaji?

#### Sakinisha Python na VS Code

Ikiwa huna Python na VS Code vilivyowekwa ndani, utahitaji kuvipakua vyote ili kuandika msimbo wa server. Ikiwa unatumia kifaa cha IoT cha virtual, au unafanya kazi kwenye Raspberry Pi yako unaweza kuruka hatua hii kwani unapaswa kuwa tayari umeweka na kusanidi.

##### Kazi - sakinisha Python na VS Code

Sakinisha Python na VS Code.

1. Sakinisha Python. Rejelea [ukurasa wa upakuaji wa Python](https://www.python.org/downloads/) kwa maelekezo ya kusakinisha toleo la hivi karibuni la Python.

1. Sakinisha Visual Studio Code (VS Code). Hii ni mhariri utakaotumia kuandika msimbo wa kifaa chako cha virtual kwa Python. Rejelea [maelezo ya VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) kwa maelekezo ya kusakinisha VS Code.
> 💁 Una uhuru wa kutumia IDE yoyote ya Python au mhariri kwa masomo haya ikiwa una chombo unachopendelea, lakini masomo yatatoa maelekezo kulingana na kutumia VS Code.
1. Sakinisha kiendelezi cha Pylance cha VS Code. Hiki ni kiendelezi cha VS Code kinachotoa msaada wa lugha ya Python. Rejelea [hati za kiendelezi cha Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) kwa maelekezo ya jinsi ya kusakinisha kiendelezi hiki kwenye VS Code.

#### Sanidi mazingira halisi ya Python

Moja ya vipengele vyenye nguvu vya Python ni uwezo wa kusakinisha [pakiti za pip](https://pypi.org) - hizi ni pakiti za msimbo zilizoandikwa na watu wengine na kuchapishwa mtandaoni. Unaweza kusakinisha pakiti ya pip kwenye kompyuta yako kwa amri moja, kisha kuitumia kwenye msimbo wako. Utatumia pip kusakinisha pakiti ya kuwasiliana kupitia MQTT.

Kwa chaguo-msingi, unapoweka pakiti, inapatikana kila mahali kwenye kompyuta yako, na hii inaweza kusababisha matatizo ya matoleo ya pakiti - kama programu moja kutegemea toleo moja la pakiti ambalo linavunjika unapoweka toleo jipya kwa programu tofauti. Ili kuepuka tatizo hili, unaweza kutumia [mazingira halisi ya Python](https://docs.python.org/3/library/venv.html), kimsingi nakala ya Python kwenye folda maalum, na unapoweka pakiti za pip, zinapakiwa tu kwenye folda hiyo.

##### Kazi - sanidi mazingira halisi ya Python

Sanidi mazingira halisi ya Python na usakinishe pakiti za pip za MQTT.

1. Kutoka kwenye terminal yako au mstari wa amri, endesha yafuatayo kwenye eneo la chaguo lako ili kuunda na kuhamia kwenye saraka mpya:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Sasa endesha yafuatayo ili kuunda mazingira halisi kwenye folda ya `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Unahitaji kuita waziwazi `python3` ili kuunda mazingira halisi endapo una Python 2 iliyosakinishwa pamoja na Python 3 (toleo la hivi karibuni). Ikiwa una Python 2, basi kuita `python` kutatumia Python 2 badala ya Python 3.

1. Washa mazingira halisi:

    * Kwenye Windows:
        * Ikiwa unatumia Command Prompt, au Command Prompt kupitia Windows Terminal, endesha:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ikiwa unatumia PowerShell, endesha:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Kwenye macOS au Linux, endesha:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Amri hizi zinapaswa kuendeshwa kutoka eneo lile lile uliloendesha amri ya kuunda mazingira halisi. Hautahitaji kamwe kuingia kwenye folda ya `.venv`, unapaswa kila mara kuendesha amri ya kuamsha na amri zozote za kusakinisha pakiti au kuendesha msimbo kutoka kwenye folda uliyokuwa wakati wa kuunda mazingira halisi.

1. Mara mazingira halisi yanapowashwa, amri ya chaguo-msingi `python` itaendesha toleo la Python lililotumika kuunda mazingira halisi. Endesha yafuatayo ili kupata toleo:

    ```sh
    python --version
    ```

    Matokeo yatakuwa sawa na yafuatayo:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Toleo lako la Python linaweza kuwa tofauti - mradi tu ni toleo la 3.6 au zaidi, uko sawa. Ikiwa si hivyo, futa folda hii, sakinisha toleo jipya la Python na ujaribu tena.

1. Endesha amri zifuatazo kusakinisha pakiti ya pip ya [Paho-MQTT](https://pypi.org/project/paho-mqtt/), maktaba maarufu ya MQTT.

    ```sh
    pip install paho-mqtt
    ```

    Pakiti hii ya pip itasakinishwa tu kwenye mazingira halisi, na haitapatikana nje ya mazingira haya.

#### Andika msimbo wa seva

Sasa msimbo wa seva unaweza kuandikwa kwa Python.

##### Kazi - andika msimbo wa seva

Andika msimbo wa seva.

1. Kutoka kwenye terminal yako au mstari wa amri, endesha yafuatayo ndani ya mazingira halisi ili kuunda faili ya Python inayoitwa `app.py`:

    * Kutoka Windows endesha:

        ```cmd
        type nul > app.py
        ```

    * Kwenye macOS au Linux, endesha:

        ```cmd
        touch app.py
        ```

1. Fungua folda ya sasa kwenye VS Code:

    ```sh
    code .
    ```

1. VS Code itakapoanzishwa, itawasha mazingira halisi ya Python. Hii itaonyeshwa kwenye upau wa hali wa chini:

    ![VS Code ikionyesha mazingira halisi yaliyochaguliwa](../../../../../translated_images/sw/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Ikiwa Terminal ya VS Code tayari inaendesha wakati VS Code inaanza, haitakuwa na mazingira halisi yaliyoamilishwa ndani yake. Jambo rahisi kufanya ni kuua terminal kwa kutumia kitufe cha **Kill the active terminal instance**:

    ![Kitufe cha VS Code Kill the active terminal instance](../../../../../translated_images/sw/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Zindua Terminal mpya ya VS Code kwa kuchagua *Terminal -> New Terminal*, au kubonyeza `` CTRL+` ``. Terminal mpya itapakia mazingira halisi, na wito wa kuamsha hii utaonekana kwenye terminal. Jina la mazingira halisi (`.venv`) pia litakuwa kwenye prompt:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Fungua faili ya `app.py` kutoka kwa VS Code explorer na ongeza msimbo ufuatao:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Badilisha `<ID>` kwenye mstari wa 6 na kitambulisho cha kipekee ulichotumia wakati wa kuunda msimbo wa kifaa chako.

    ⚠️ Hii **lazima** iwe kitambulisho sawa na ulichotumia kwenye kifaa chako, la sivyo msimbo wa seva hautajiandikisha au kuchapisha kwenye mada sahihi.

    Msimbo huu huunda mteja wa MQTT na jina la kipekee, na kuunganisha kwenye broker ya *test.mosquitto.org*. Kisha huanza mchakato wa usindikaji unaoendesha kwenye thread ya nyuma kusikiliza ujumbe kwenye mada yoyote iliyosajiliwa.

    Mteja kisha hujiandikisha kwa ujumbe kwenye mada ya telemetry, na hufafanua kazi inayoitwa wakati ujumbe unapokelewa. Ujumbe wa telemetry unapopokelewa, kazi ya `handle_telemetry` inaitwa, ikichapisha ujumbe uliopokelewa kwenye terminal.

    Hatimaye, kitanzi kisicho na mwisho huweka programu ikiendelea. Mteja wa MQTT anasikiliza ujumbe kwenye thread ya nyuma na huendesha wakati wote programu kuu inapofanya kazi.

1. Kutoka kwenye terminal ya VS Code, endesha yafuatayo kuendesha programu yako ya Python:

    ```sh
    python app.py
    ```

    Programu itaanza kusikiliza ujumbe kutoka kwa kifaa cha IoT.

1. Hakikisha kifaa chako kinafanya kazi na kinatuma ujumbe wa telemetry. Rekebisha viwango vya mwanga vinavyogunduliwa na kifaa chako halisi au cha mtandaoni. Ujumbe unaopokelewa utaonyeshwa kwenye terminal.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Faili ya `app.py` katika mazingira halisi ya nightlight lazima iwe inaendesha ili faili ya `app.py` katika mazingira halisi ya nightlight-server ipokee ujumbe unaotumwa.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Ni mara ngapi telemetry inapaswa kutumwa?

Jambo moja muhimu la kuzingatia na telemetry ni mara ngapi kupima na kutuma data? Jibu ni - inategemea. Ukipima mara kwa mara unaweza kujibu mabadiliko kwa haraka, lakini unatumia nguvu zaidi, kipimo data zaidi, unazalisha data zaidi na unahitaji rasilimali zaidi za wingu kushughulikia.

Kwa thermostat, kupima kila dakika chache labda kunatosha kwani joto halibadiliki mara kwa mara. Ukipima mara moja kwa siku unaweza kuishia kuwasha joto kwa joto la usiku katikati ya mchana wa jua, wakati ukipima kila sekunde utakuwa na maelfu ya vipimo vya joto vilivyorudiwa bila sababu, ambavyo vitapunguza kasi ya mtandao wa mtumiaji na kipimo data (tatizo kwa watu wenye mipango ya kipimo data kidogo), kutumia nguvu zaidi ambayo inaweza kuwa tatizo kwa vifaa vinavyotumia betri kama sensorer za mbali, na kuongeza gharama za rasilimali za wingu za mtoa huduma kushughulikia na kuhifadhi.

Ikiwa unafuatilia data karibu na mashine kwenye kiwanda ambayo ikiharibika inaweza kusababisha uharibifu mkubwa na hasara ya mamilioni ya dola, basi kupima mara nyingi kwa sekunde kunaweza kuwa muhimu. Ni bora kupoteza kipimo data kuliko kukosa telemetry inayoonyesha kuwa mashine inahitaji kusimamishwa na kutengenezwa kabla haijavunjika.

> 💁 Katika hali hii, unaweza kufikiria kuwa na kifaa cha ukingo kushughulikia telemetry kwanza ili kupunguza utegemezi wa mtandao.

### Kupoteza muunganisho

Muunganisho wa mtandao unaweza kuwa wa kutegemewa, na kukatika ni jambo la kawaida. Kifaa cha IoT kinapaswa kufanya nini chini ya hali hizi - je, kinapaswa kupoteza data, au kinapaswa kuihifadhi hadi muunganisho urejeshwe? Tena, jibu ni inategemea.

Kwa thermostat, data inaweza kupotea mara tu kipimo kipya cha joto kinapochukuliwa. Mfumo wa joto haujali kuwa dakika 20 zilizopita ilikuwa 20.5°C ikiwa joto sasa ni 19°C, ni joto la sasa linaloamua ikiwa joto linapaswa kuwashwa au kuzimwa.

Kwa mashine unaweza kutaka kuhifadhi data, hasa ikiwa inatumika kutafuta mwenendo. Kuna mifano ya kujifunza kwa mashine inayoweza kugundua hali zisizo za kawaida kwenye mito ya data kwa kuangalia data kutoka kipindi fulani cha muda (kama saa moja iliyopita) na kugundua data isiyo ya kawaida. Hii mara nyingi hutumika kwa matengenezo ya utabiri, kutafuta dalili kwamba kitu kinaweza kuvunjika hivi karibuni ili uweze kutengeneza au kubadilisha kabla ya kutokea. Unaweza kutaka kila kipande cha telemetry kwa mashine kutumwa ili kiweze kushughulikiwa kwa kugundua hali zisizo za kawaida, kwa hivyo mara kifaa cha IoT kinapoweza kuunganishwa tena, kitume telemetry yote iliyozalishwa wakati wa kukatika kwa mtandao.

Wabunifu wa vifaa vya IoT wanapaswa pia kuzingatia ikiwa kifaa cha IoT kinaweza kutumika wakati wa kukatika kwa mtandao au kupoteza ishara kunakosababishwa na eneo. Thermostat ya kisasa inapaswa kuwa na uwezo wa kufanya maamuzi machache ya kudhibiti joto ikiwa haiwezi kutuma telemetry kwa wingu kutokana na kukatika.

[![Ferrari hii iliharibika kwa sababu mtu alijaribu kuiboresha chini ya ardhi ambapo hakuna mawasiliano ya simu](../../../../../translated_images/sw/bricked-car.dc38f8efadc6c59d76211f981a521efb300939283dee468f79503aae3ec67615.png)](https://twitter.com/internetofshit/status/1315736960082808832)

Kwa MQTT kushughulikia kupoteza muunganisho, msimbo wa kifaa na seva utahitaji kuwajibika kuhakikisha ujumbe unafika ikiwa unahitajika, kwa mfano kwa kuhitaji kwamba ujumbe wote uliotumwa ujibiwe na ujumbe wa ziada kwenye mada ya majibu, na ikiwa sivyo, ujumbe huo uhifadhiwe kwa mkono ili utumwe tena baadaye.

## Amri

Amri ni ujumbe unaotumwa na wingu kwenda kwa kifaa, ukielekeza kifaa kufanya jambo fulani. Mara nyingi hii inahusisha kutoa aina fulani ya pato kupitia actuator, lakini inaweza kuwa maagizo kwa kifaa chenyewe, kama kuwasha upya, au kukusanya telemetry ya ziada na kuirudisha kama jibu kwa amri.

![Thermostat iliyounganishwa na mtandao ikipokea amri ya kuwasha joto](../../../../../translated_images/sw/commands.d6c06bbbb3a02cce95f2831a1c331daf6dedd4e470c4aa2b0ae54f332016e504.png)

Thermostat inaweza kupokea amri kutoka kwa wingu kuwasha joto. Kulingana na data ya telemetry kutoka kwa sensorer zote, ikiwa huduma ya wingu imeamua kuwa joto linapaswa kuwashwa, basi inatuma amri husika.

### Tuma amri kwa broker wa MQTT

Hatua inayofuata kwa taa yetu ya usiku inayodhibitiwa na mtandao ni kwa msimbo wa seva kutuma amri kurudi kwa kifaa cha IoT kudhibiti taa kulingana na viwango vya mwanga inavyogundua.

1. Fungua msimbo wa seva kwenye VS Code

1. Ongeza mstari ufuatao baada ya tangazo la `client_telemetry_topic` ili kufafanua mada ya kutuma amri:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Ongeza msimbo ufuatao mwishoni mwa kazi ya `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Hii inatuma ujumbe wa JSON kwenye mada ya amri na thamani ya `led_on` ikiwa imewekwa kuwa kweli au si kweli kulingana na ikiwa mwanga ni chini ya 300 au la. Ikiwa mwanga ni chini ya 300, kweli inatumwa kuagiza kifaa kuwasha LED.

1. Endesha msimbo kama hapo awali

1. Rekebisha viwango vya mwanga vinavyogunduliwa na kifaa chako halisi au cha mtandaoni. Ujumbe unaopokelewa na amri zinazotumwa zitaandikwa kwenye terminal:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetry na amri zinatumwa kwenye mada moja kila moja. Hii inamaanisha telemetry kutoka kwa vifaa vingi itaonekana kwenye mada moja ya telemetry, na amri kwa vifaa vingi zitaonekana kwenye mada moja ya amri. Ikiwa ungependa kutuma amri kwa kifaa maalum, unaweza kutumia mada nyingi, zilizoorodheshwa kwa kitambulisho cha kipekee cha kifaa, kama `/commands/device1`, `/commands/device2`. Kwa njia hiyo kifaa kinaweza kusikiliza ujumbe unaokusudiwa kifaa hicho pekee.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Shughulikia amri kwenye kifaa cha IoT

Sasa kwa kuwa amri zinatumwa kutoka kwa seva, unaweza sasa kuongeza msimbo kwenye kifaa cha IoT kushughulikia amri hizo na kudhibiti LED.

Fuata hatua husika hapa chini kusikiliza amri kutoka kwa broker wa MQTT:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Kompyuta ya bodi moja - Raspberry Pi/Kifaa cha IoT cha mtandaoni](single-board-computer-commands.md)

Mara msimbo huu umeandikwa na kuendesha, jaribu kubadilisha viwango vya mwanga. Angalia pato kutoka kwa seva na kifaa, na angalia LED inavyobadilika unapobadilisha viwango vya mwanga.

### Kupoteza muunganisho

Huduma ya wingu inapaswa kufanya nini ikiwa inahitaji kutuma amri kwa kifaa cha IoT ambacho kimekatika? Tena, jibu ni inategemea.

Ikiwa amri ya hivi karibuni inachukua nafasi ya ile ya awali basi zile za awali zinaweza kupuuzwa. Ikiwa huduma ya wingu inatuma amri ya kuwasha joto, kisha inatuma amri ya kuzima, basi amri ya kuwasha inaweza kupuuzwa na isitumwe tena.

Ikiwa amri zinahitaji kushughulikiwa kwa mpangilio, kama vile kusogeza mkono wa roboti juu, kisha kufunga kifaa cha kushika, basi zinahitaji kutumwa kwa mpangilio mara muunganisho unaporejeshwa.

✅ Je, kifaa au msimbo wa seva unaweza kuhakikisha amri zinatumwa na kushughulikiwa kwa mpangilio kila wakati juu ya MQTT ikiwa inahitajika?

---

## 🚀 Changamoto

Changamoto katika masomo matatu yaliyopita ilikuwa kuorodhesha vifaa vingi vya IoT unavyoweza ambavyo viko nyumbani kwako, shuleni au kazini na kuamua ikiwa vimejengwa kuzunguka microcontrollers au kompyuta za bodi moja, au hata mchanganyiko wa vyote viwili, na kufikiria kuhusu sensorer na actuators wanazotumia.
Kwa vifaa hivi, fikiria ni ujumbe gani vinaweza kuwa vinatuma au kupokea. Je, vinatuma telemetry gani? Ni ujumbe au amri gani vinaweza kupokea? Je, unadhani ni salama?

## Jaribio la baada ya somo

[Jaribio la baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Mapitio na Kujisomea

Soma zaidi kuhusu MQTT kwenye [ukurasa wa Wikipedia wa MQTT](https://wikipedia.org/wiki/MQTT).

Jaribu kuendesha broker ya MQTT mwenyewe ukitumia [Mosquitto](https://www.mosquitto.org) na uunganishe na kifaa chako cha IoT na msimbo wa seva.

> 💁 Kidokezo - kwa chaguo-msingi Mosquitto hairuhusu miunganisho ya bila majina (yaani kuunganishwa bila jina la mtumiaji na nenosiri), na hairuhusu miunganisho kutoka nje ya kompyuta inayoendesha.
> Unaweza kurekebisha hili kwa kutumia faili ya [`mosquitto.conf` config file](https://www.mosquitto.org/man/mosquitto-conf-5.html) yenye yafuatayo:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Kazi

[Linganisha na tofautisha MQTT na itifaki nyingine za mawasiliano](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kwa usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.