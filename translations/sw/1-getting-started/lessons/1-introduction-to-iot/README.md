<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-27T22:15:31+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "sw"
}
-->
# Utangulizi wa IoT

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa zaidi.

Somo hili lilifundishwa kama sehemu ya [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) kutoka [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Somo lilifundishwa kupitia video mbili - somo la saa moja, na saa moja ya maswali na majibu kwa undani zaidi kuhusu sehemu za somo na kujibu maswali.

[![Somo la 1: Utangulizi wa IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Somo la 1: Utangulizi wa IoT - Maswali na majibu](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Bofya picha zilizo juu ili kutazama video

## Jaribio la kabla ya somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Utangulizi

Somo hili linashughulikia mada za msingi kuhusu Mtandao wa Vitu (Internet of Things - IoT), na linakusaidia kuanza kuandaa vifaa vyako.

Katika somo hili tutashughulikia:

* [IoT ni nini?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Vifaa vya IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Kuandaa kifaa chako](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Matumizi ya IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Mifano ya vifaa vya IoT unavyoweza kuwa navyo karibu nawe](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## IoT ni nini?

Neno 'Internet of Things' lilianzishwa na [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) mwaka 1999, likimaanisha kuunganisha mtandao na dunia ya kimwili kupitia sensa. Tangu wakati huo, neno hili limetumika kuelezea kifaa chochote kinachoshirikiana na dunia ya kimwili inayokizunguka, ama kwa kukusanya data kutoka kwa sensa, au kutoa mwingiliano wa kimwili kupitia aktueta (vifaa vinavyofanya kitu kama kuwasha swichi au kuwasha LED), kwa kawaida vikiwa vimeunganishwa na vifaa vingine au mtandao.

> **Sensa** hukusanya taarifa kutoka kwa dunia, kama vile kupima kasi, joto au eneo.
>
> **Aktueta** hubadilisha ishara za umeme kuwa mwingiliano wa kimwili kama vile kuwasha swichi, kuwasha taa, kutoa sauti, au kutuma ishara za kudhibiti vifaa vingine, kwa mfano, kuwasha soketi ya umeme.

IoT kama eneo la teknolojia ni zaidi ya vifaa tu - inajumuisha huduma za wingu zinazoweza kuchakata data ya sensa, au kutuma maombi kwa aktueta zilizounganishwa na vifaa vya IoT. Pia inajumuisha vifaa ambavyo havina au havihitaji muunganisho wa mtandao, mara nyingi hujulikana kama vifaa vya ukingo (edge devices). Hivi ni vifaa vinavyoweza kuchakata na kujibu data ya sensa vyenyewe, kwa kawaida kwa kutumia mifano ya AI iliyofundishwa kwenye wingu.

IoT ni eneo la teknolojia linalokua kwa kasi. Inakadiriwa kwamba kufikia mwisho wa mwaka 2020, vifaa bilioni 30 vya IoT vilikuwa vimewekwa na kuunganishwa na mtandao. Kwa kuangalia siku zijazo, inakadiriwa kwamba kufikia mwaka 2025, vifaa vya IoT vitakuwa vinakusanya karibu zettabyte 80 za data au gigabyte trilioni 80. Hiyo ni data nyingi sana!

![Grafu inayoonyesha vifaa vya IoT vilivyotumika kwa muda, ikionyesha mwelekeo wa juu kutoka chini ya bilioni 5 mwaka 2015 hadi zaidi ya bilioni 30 mwaka 2025](../../../../../images/connected-iot-devices.svg)

✅ Fanya utafiti kidogo: Ni kiasi gani cha data inayozalishwa na vifaa vya IoT hutumika kweli, na ni kiasi gani kinapotea? Kwa nini data nyingi inapuuzwa?

Data hii ndiyo ufunguo wa mafanikio ya IoT. Ili kuwa msanidi wa IoT mwenye mafanikio, unahitaji kuelewa data unayohitaji kukusanya, jinsi ya kuikusanya, jinsi ya kufanya maamuzi kulingana nayo, na jinsi ya kutumia maamuzi hayo kushirikiana na dunia ya kimwili ikiwa inahitajika.

## Vifaa vya IoT

**T** katika IoT inasimama kwa **Vitu** - vifaa vinavyoshirikiana na dunia ya kimwili inayowazunguka ama kwa kukusanya data kutoka kwa sensa au kutoa mwingiliano wa kimwili kupitia aktueta.

Vifaa vya uzalishaji au matumizi ya kibiashara, kama vile vifaa vya kufuatilia mazoezi ya mwili kwa watumiaji, au vidhibiti vya mashine za viwandani, kwa kawaida hutengenezwa maalum. Vinatumia bodi za mzunguko maalum, labda hata wasindikaji maalum, iliyoundwa kukidhi mahitaji ya kazi fulani, iwe ni kuwa ndogo ya kutosha kutoshea kwenye mkono, au kuwa imara ya kutosha kufanya kazi katika mazingira ya joto la juu, msongo mkubwa au mtetemo mkubwa wa kiwanda.

Kama msanidi programu anayejifunza kuhusu IoT au kuunda mfano wa kifaa, utahitaji kuanza na kifaa cha msanidi programu. Hivi ni vifaa vya IoT vya matumizi ya jumla vilivyoundwa kwa ajili ya watengenezaji kutumia, mara nyingi vikiwa na vipengele ambavyo usingekuwa navyo kwenye kifaa cha uzalishaji, kama vile seti ya pini za nje za kuunganisha sensa au aktueta, vifaa vya kusaidia urekebishaji wa hitilafu, au rasilimali za ziada ambazo zingezidisha gharama zisizo za lazima wakati wa uzalishaji mkubwa.

Vifaa hivi vya msanidi programu kwa kawaida huangukia katika makundi mawili - mikrocontroller na kompyuta za bodi moja. Hivi vitatambulishwa hapa, na tutaingia kwa undani zaidi katika somo linalofuata.

> 💁 Simu yako pia inaweza kuchukuliwa kuwa kifaa cha IoT cha matumizi ya jumla, kikiwa na sensa na aktueta zilizojengwa ndani, na programu tofauti zinazotumia sensa na aktueta kwa njia tofauti na huduma tofauti za wingu. Unaweza hata kupata mafunzo ya IoT yanayotumia programu ya simu kama kifaa cha IoT.

### Mikrocontroller

Mikrocontroller (pia hujulikana kama MCU, kifupi cha microcontroller unit) ni kompyuta ndogo inayojumuisha:

🧠 Kituo kimoja au zaidi cha usindikaji (CPU) - 'ubongo' wa mikrocontroller unaoendesha programu yako

💾 Kumbukumbu (RAM na kumbukumbu ya programu) - ambapo programu yako, data na vigezo huhifadhiwa

🔌 Muunganisho wa pembejeo/pembezo (I/O) unaoweza kupangwa - kuzungumza na vifaa vya nje (vifaa vilivyounganishwa) kama sensa na aktueta

Mikrocontroller kwa kawaida ni vifaa vya kompyuta vya gharama ya chini, na bei ya wastani kwa zile zinazotumika katika vifaa maalum ikishuka hadi karibu dola za Marekani $0.50, na baadhi ya vifaa vikiwa vya bei ya chini kama $0.03. Vifaa vya msanidi programu vinaweza kuanza kwa bei ya chini kama $4, na gharama huongezeka unapoongeza vipengele zaidi. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), kifaa cha msanidi programu cha mikrocontroller kutoka [Seeed studios](https://www.seeedstudio.com) ambacho kina sensa, aktueta, WiFi na skrini kinagharimu karibu dola za Marekani $30.

![Wio Terminal](../../../../../translated_images/sw/wio-terminal.b8299ee16587db9a.webp)

> 💁 Unapofanya utafutaji wa mikrocontroller mtandaoni, kuwa makini na kutafuta neno **MCU** kwani hili litarudisha matokeo mengi kuhusu Marvel Cinematic Universe, si mikrocontroller.

Mikrocontroller imeundwa kupangwa kufanya idadi ndogo ya kazi maalum sana, badala ya kuwa kompyuta za matumizi ya jumla kama PC au Mac. Isipokuwa kwa hali maalum sana, huwezi kuunganisha monitor, kibodi na panya na kuzitumia kwa kazi za matumizi ya jumla.

Vifaa vya msanidi programu vya mikrocontroller kwa kawaida huja na sensa na aktueta za ziada zilizojengwa ndani. Bodi nyingi zitakuwa na LED moja au zaidi unazoweza kupanga, pamoja na vifaa vingine kama vile plugs za kawaida za kuongeza sensa au aktueta zaidi kwa kutumia mifumo ya watengenezaji mbalimbali au sensa zilizojengwa ndani (kwa kawaida zile maarufu zaidi kama sensa za joto). Baadhi ya mikrocontroller zina muunganisho wa wireless uliojengwa ndani kama Bluetooth au WiFi au zina mikrocontroller za ziada kwenye bodi kuongeza muunganisho huu.

> 💁 Mikrocontroller kwa kawaida hupangwa kwa kutumia C/C++.

### Kompyuta za bodi moja

Kompyuta ya bodi moja ni kifaa kidogo cha kompyuta ambacho kina vipengele vyote vya kompyuta kamili vilivyomo kwenye bodi moja ndogo. Hivi ni vifaa ambavyo vina vipimo karibu na PC au Mac ya mezani au laptop, vinaendesha mfumo kamili wa uendeshaji, lakini ni vidogo, vinatumia nguvu kidogo, na ni vya bei nafuu sana.

![Raspberry Pi 4](../../../../../translated_images/sw/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi ni mojawapo ya kompyuta za bodi moja maarufu zaidi.

Kama mikrocontroller, kompyuta za bodi moja zina CPU, kumbukumbu na pini za pembejeo/pembezo, lakini zina vipengele vya ziada kama chipu ya grafiki inayokuruhusu kuunganisha monitor, sauti za nje, na bandari za USB kuunganisha kibodi, panya na vifaa vingine vya USB vya kawaida kama kamera za mtandao au hifadhi ya nje. Programu huhifadhiwa kwenye kadi za SD au diski ngumu pamoja na mfumo wa uendeshaji, badala ya chipu ya kumbukumbu iliyojengwa kwenye bodi.

> 🎓 Unaweza kufikiria kompyuta ya bodi moja kama toleo dogo, la bei nafuu la PC au Mac unayosoma hii, pamoja na pini za GPIO (pembejeo/pembezo za matumizi ya jumla) za kushirikiana na sensa na aktueta.

Kompyuta za bodi moja ni kompyuta kamili, kwa hivyo zinaweza kupangwa kwa lugha yoyote. Vifaa vya IoT kwa kawaida hupangwa kwa kutumia Python.

### Uchaguzi wa vifaa kwa masomo yanayofuata

Masomo yote yanayofuata yanajumuisha kazi za kutumia kifaa cha IoT kushirikiana na dunia ya kimwili na kuwasiliana na wingu. Kila somo linaunga mkono chaguo 3 za vifaa - Arduino (kutumia Seeed Studios Wio Terminal), au kompyuta ya bodi moja, ama kifaa halisi (Raspberry Pi 4) au kompyuta ya bodi moja ya virtual inayotumia PC au Mac yako.

Unaweza kusoma kuhusu vifaa vinavyohitajika kukamilisha kazi zote katika [mwongozo wa vifaa](../../../hardware.md).

> 💁 Huhitaji kununua vifaa vyovyote vya IoT kukamilisha kazi, unaweza kufanya kila kitu kwa kutumia kompyuta ya bodi moja ya virtual.

Ni vifaa gani unavyovichagua inategemea na kile unacho nyumbani au shuleni, na lugha ya programu unayojua au unayopanga kujifunza. Aina zote za vifaa zitatumia mfumo wa sensa sawa, kwa hivyo ukianza na moja, unaweza kubadilisha kwenda nyingine bila kubadilisha sehemu kubwa ya vifaa. Kompyuta ya bodi moja ya virtual itakuwa sawa na kujifunza kwenye Raspberry Pi, na sehemu kubwa ya msimbo inaweza kuhamishwa kwenye Pi ikiwa hatimaye utapata kifaa na sensa.

### Kifaa cha msanidi programu cha Arduino

Ikiwa una nia ya kujifunza maendeleo ya mikrocontroller, unaweza kukamilisha kazi kwa kutumia kifaa cha Arduino. Utahitaji uelewa wa msingi wa programu ya C/C++, kwani masomo yatafundisha tu msimbo unaohusiana na mfumo wa Arduino, sensa na aktueta zinazotumika, na maktaba zinazoshirikiana na wingu.

Kazi zitatumia [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) na [kiendelezi cha PlatformIO kwa maendeleo ya mikrocontroller](https://platformio.org). Unaweza pia kutumia Arduino IDE ikiwa una uzoefu na zana hii, kwani maelekezo hayatatolewa.

### Kifaa cha msanidi programu cha kompyuta ya bodi moja

Ikiwa una nia ya kujifunza maendeleo ya IoT kwa kutumia kompyuta za bodi moja, unaweza kukamilisha kazi kwa kutumia Raspberry Pi, au kifaa cha virtual kinachoendesha kwenye PC au Mac yako.

Utahitaji uelewa wa msingi wa programu ya Python, kwani masomo yatafundisha tu msimbo unaohusiana na sensa na aktueta zinazotumika, na maktaba zinazoshirikiana na wingu.

> 💁 Ikiwa unataka kujifunza kuandika programu kwa Python, angalia mfululizo wa video zifuatazo:
>
> * [Python kwa wanaoanza](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Zaidi ya Python kwa wanaoanza](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Kazi zitatumia [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Ikiwa unatumia Raspberry Pi, unaweza kuendesha Pi yako kwa kutumia toleo kamili la desktop la Raspberry Pi OS, na kufanya programu moja kwa moja kwenye Pi kwa kutumia [toleo la Raspberry Pi OS la VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), au kuendesha Pi yako kama kifaa kisicho na skrini na kuandika programu kutoka PC au Mac yako kwa kutumia VS Code na [kiendelezi cha Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) kinachokuruhusu kuunganishwa na Pi yako na kuhariri, kurekebisha hitilafu na kuendesha msimbo kana kwamba unafanya programu moja kwa moja kwenye Pi.

Ikiwa unatumia chaguo la kifaa cha virtual, utaandika programu moja kwa moja kwenye kompyuta yako. Badala ya kufikia sensa na aktueta, utatumia zana ya kuiga vifaa hivi ikitoa thamani za sensa unazoweza kufafanua, na kuonyesha matokeo ya aktueta kwenye skrini.

## Kuandaa kifaa chako

Kabla ya kuanza kuandika programu kwa kifaa chako cha IoT, utahitaji kufanya maandalizi kidogo. Fuata maelekezo husika hapa chini kulingana na kifaa unachotumia.
💁 Ikiwa bado huna kifaa, rejelea [mwongozo wa vifaa](../../../hardware.md) ili kusaidia kuamua ni kifaa gani utakachotumia, na ni vifaa vya ziada gani unavyohitaji kununua. Huna haja ya kununua vifaa, kwani miradi yote inaweza kuendeshwa kwenye vifaa vya mtandaoni.
Maelekezo haya yanajumuisha viungo vya tovuti za wahusika wengine kutoka kwa watengenezaji wa vifaa au zana utakazotumia. Hii ni kuhakikisha unatumia maelekezo ya kisasa zaidi kwa zana na vifaa mbalimbali.

Fuata mwongozo husika ili kuandaa kifaa chako na kukamilisha mradi wa 'Hello World'. Hii itakuwa hatua ya kwanza ya kuunda taa ya usiku ya IoT katika masomo 4 ya sehemu hii ya kuanza.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Kompyuta ya bodi moja - Raspberry Pi](pi.md)
* [Kompyuta ya bodi moja - Kifaa cha mtandaoni](virtual-device.md)

✅ Utatumia VS Code kwa Arduino na Kompyuta za bodi moja. Ikiwa hujawahi kutumia hii kabla, soma zaidi kuhusu hilo kwenye [tovuti ya VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Matumizi ya IoT

IoT inashughulikia matumizi mengi sana, katika makundi makubwa kadhaa:

* IoT ya Wateja
* IoT ya Kibiashara
* IoT ya Viwanda
* IoT ya Miundombinu

✅ Fanya utafiti kidogo: Kwa kila eneo lililoelezwa hapa chini, tafuta mfano mmoja halisi ambao haujapewa katika maandishi.

### IoT ya Wateja

IoT ya wateja inahusu vifaa vya IoT ambavyo wateja hununua na kutumia nyumbani. Baadhi ya vifaa hivi ni vya manufaa sana, kama spika za kisasa, mifumo ya kupasha joto kwa akili, na mashine za kusafisha sakafu za roboti. Vingine vinaweza kuhojiwa kuhusu manufaa yake, kama bomba zinazoendeshwa kwa sauti ambazo haziwezi kuzimwa kwa sababu udhibiti wa sauti hauwezi kusikia kutokana na kelele ya maji yanayotiririka.

Vifaa vya IoT vya wateja vinawawezesha watu kufanikisha zaidi katika mazingira yao, hasa bilioni 1 ambao wana ulemavu. Mashine za kusafisha sakafu za roboti zinaweza kutoa sakafu safi kwa watu wenye matatizo ya uhamaji ambao hawawezi kusafisha wenyewe, majiko yanayoendeshwa kwa sauti yanawaruhusu watu wenye uoni mdogo au udhibiti wa mwili kupasha jiko kwa sauti pekee, na vifaa vya kufuatilia afya vinaweza kuruhusu wagonjwa kufuatilia hali zao za muda mrefu wenyewe kwa taarifa za mara kwa mara na za kina zaidi kuhusu hali zao. Vifaa hivi vinakuwa vya kawaida kiasi kwamba hata watoto wadogo wanavitumia kama sehemu ya maisha yao ya kila siku, kwa mfano, wanafunzi wanaosoma mtandaoni wakati wa janga la COVID wakitumia vifaa vya nyumbani vya akili kuweka muda wa kazi za shule au kengele za kuwakumbusha mikutano ya darasa inayokuja.

✅ Ni vifaa gani vya IoT vya wateja ulivyo navyo nyumbani au mwilini mwako?

### IoT ya Kibiashara

IoT ya kibiashara inahusu matumizi ya IoT mahali pa kazi. Katika mazingira ya ofisi, kunaweza kuwa na sensa za uwepo na sensa za mwendo ili kudhibiti taa na joto ili taa na joto zisiwepo wakati hazihitajiki, kupunguza gharama na uzalishaji wa kaboni. Katika kiwanda, vifaa vya IoT vinaweza kufuatilia hatari za usalama kama wafanyakazi wasio na kofia ngumu au kelele zilizofikia viwango vya hatari. Katika rejareja, vifaa vya IoT vinaweza kupima joto la hifadhi ya baridi, na kumjulisha mmiliki wa duka ikiwa friji au freezer iko nje ya kiwango kinachohitajika, au vinaweza kufuatilia bidhaa kwenye rafu ili kuelekeza wafanyakazi kujaza bidhaa zilizouzwa. Sekta ya usafiri inategemea zaidi na zaidi IoT kufuatilia maeneo ya magari, kufuatilia mileage ya barabara kwa malipo ya watumiaji wa barabara, kufuatilia saa za madereva na kufuata mapumziko, au kuwajulisha wafanyakazi wakati gari linakaribia kituo cha kupakia au kupakua.

✅ Ni vifaa gani vya IoT vya kibiashara ulivyo navyo shuleni au kazini?

### IoT ya Viwanda (IIoT)

IoT ya viwanda, au IIoT, ni matumizi ya vifaa vya IoT kudhibiti na kusimamia mashine kwa kiwango kikubwa. Hii inashughulikia matumizi mengi, kutoka viwanda hadi kilimo cha kidijitali.

Viwanda vinatumia vifaa vya IoT kwa njia nyingi tofauti. Mashine zinaweza kufuatiliwa na sensa nyingi kufuatilia mambo kama joto, mtetemo na kasi ya mzunguko. Data hii inaweza kufuatiliwa ili kuruhusu mashine kusimamishwa ikiwa inazidi viwango fulani - kwa mfano, ikiwa inapata joto kupita kiasi na kuzimwa. Data hii pia inaweza kukusanywa na kuchambuliwa kwa muda ili kufanya matengenezo ya utabiri, ambapo mifano ya AI itatazama data inayoelekea kushindwa, na kutumia hiyo kutabiri kushindwa kwa mashine nyingine kabla ya kutokea.

Kilimo cha kidijitali ni muhimu ikiwa sayari itawalisha idadi ya watu inayoongezeka, hasa kwa watu bilioni 2 katika kaya milioni 500 zinazotegemea [kilimo cha kujikimu](https://wikipedia.org/wiki/Subsistence_agriculture). Kilimo cha kidijitali kinaweza kuanzia sensa za bei nafuu hadi mipangilio mikubwa ya kibiashara. Mkulima anaweza kuanza kwa kufuatilia joto na kutumia [siku za digrii za ukuaji](https://wikipedia.org/wiki/Growing_degree-day) kutabiri wakati mazao yatakuwa tayari kuvunwa. Wanaweza kuunganisha ufuatiliaji wa unyevu wa udongo na mifumo ya kumwagilia maji kiotomatiki ili kutoa maji kwa mimea yao kadri inavyohitajika, lakini si zaidi ili kuhakikisha mazao yao hayakauki bila kupoteza maji. Wakulima hata wanachukua hatua zaidi kwa kutumia drones, data ya satelaiti na AI kufuatilia ukuaji wa mazao, magonjwa na ubora wa udongo katika maeneo makubwa ya mashamba.

✅ Ni vifaa gani vingine vya IoT vinaweza kuwasaidia wakulima?

### IoT ya Miundombinu

IoT ya miundombinu ni kufuatilia na kudhibiti miundombinu ya ndani na ya kimataifa ambayo watu hutumia kila siku.

[Miji ya Akili](https://wikipedia.org/wiki/Smart_city) ni maeneo ya mijini yanayotumia vifaa vya IoT kukusanya data kuhusu jiji na kutumia hiyo kuboresha jinsi jiji linavyoendeshwa. Miji hii kwa kawaida huendeshwa kwa ushirikiano kati ya serikali za mitaa, vyuo vikuu na biashara za mitaa, kufuatilia na kudhibiti mambo mbalimbali kutoka usafiri hadi maegesho na uchafuzi wa mazingira. Kwa mfano, huko Copenhagen, Denmark, uchafuzi wa hewa ni muhimu kwa wakazi wa eneo hilo, kwa hivyo hupimwa na data hutumiwa kutoa taarifa kuhusu njia safi zaidi za baiskeli na jogging.

[Gridi za nguvu za akili](https://wikipedia.org/wiki/Smart_grid) huruhusu uchambuzi bora wa mahitaji ya nguvu kwa kukusanya data ya matumizi katika kiwango cha nyumba za mtu binafsi. Data hii inaweza kuongoza maamuzi katika kiwango cha nchi ikiwa ni pamoja na wapi kujenga vituo vipya vya nguvu, na katika kiwango cha mtu binafsi kwa kuwapa watumiaji maarifa kuhusu kiasi cha nguvu wanayotumia, wakati wanapotumia, na hata mapendekezo ya jinsi ya kupunguza gharama, kama vile kuchaji magari ya umeme usiku.

✅ Ikiwa ungeweza kuongeza vifaa vya IoT kupima chochote mahali unapoishi, ingekuwa nini?

## Mifano ya vifaa vya IoT unavyoweza kuwa navyo karibu nawe

Utashangazwa na idadi ya vifaa vya IoT ulivyo navyo karibu nawe. Ninaandika hii kutoka nyumbani na nina vifaa vifuatavyo vilivyounganishwa na Mtandao na vipengele vya akili kama vile udhibiti wa programu, udhibiti wa sauti, au uwezo wa kutuma data kwangu kupitia simu yangu:

* Spika nyingi za kisasa
* Friji, mashine ya kuosha vyombo, jiko na microwave
* Kifuatilia umeme kwa paneli za jua
* Plug za akili
* Kengele ya mlango ya video na kamera za usalama
* Thermostat ya akili na sensa za chumba za akili
* Kifungua mlango wa gereji
* Mifumo ya burudani ya nyumbani na TV zinazoendeshwa kwa sauti
* Taa
* Vifuatiliaji vya mazoezi na afya

Vifaa vyote vya aina hizi vina sensa na/au actuators na vinaongea na Mtandao. Ninaweza kujua kutoka kwa simu yangu ikiwa mlango wa gereji yangu uko wazi, na kumwambia spika yangu ya akili kuufunga. Ninaweza hata kuiweka kwa muda ili ikiwa bado iko wazi usiku, itafungwa kiotomatiki. Wakati kengele ya mlango wangu inalia, ninaweza kuona kutoka kwa simu yangu ni nani yuko hapo popote nilipo duniani, na kuzungumza nao kupitia spika na kipaza sauti kilichojengwa ndani ya kengele ya mlango. Ninaweza kufuatilia sukari ya damu yangu, kiwango cha moyo na mifumo ya usingizi, nikitafuta mifumo katika data ili kuboresha afya yangu. Ninaweza kudhibiti taa zangu kupitia wingu, na kukaa gizani wakati muunganisho wangu wa Mtandao unapokatika.

---

## 🚀 Changamoto

Orodhesha vifaa vingi vya IoT unavyoweza kuwa navyo nyumbani, shuleni au kazini - kunaweza kuwa na zaidi kuliko unavyofikiria!

## Jaribio la baada ya somo

[Jaribio la baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Mapitio na Kujisomea

Soma kuhusu faida na matatizo ya miradi ya IoT ya wateja. Angalia tovuti za habari kwa makala kuhusu wakati imeenda vibaya, kama masuala ya faragha, matatizo ya vifaa au matatizo yanayosababishwa na ukosefu wa muunganisho.

Baadhi ya mifano:

* Angalia akaunti ya Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(onyo la matusi)* kwa mifano mizuri ya matatizo na IoT ya wateja.
* [c|net - Saa yangu ya Apple iliokoa maisha yangu: Watu 5 wanashiriki hadithi zao](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Fundi wa ADT anakiri kupeleleza kamera za wateja kwa miaka](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(onyo la kichocheo - upelelezi usioidhinishwa)*

## Kazi

[Chunguza mradi wa IoT](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutokuelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.