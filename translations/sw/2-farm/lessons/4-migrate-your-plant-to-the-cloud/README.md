<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-27T23:07:59+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "sw"
}
-->
# Hamisha mmea wako kwenye wingu

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.sw.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa zaidi.

Somo hili lilifundishwa kama sehemu ya [Mradi wa IoT kwa Kompyuta 2 - Mfululizo wa Kilimo Kidijitali](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) kutoka [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Unganisha kifaa chako na wingu kwa Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Jaribio la kabla ya somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Utangulizi

Katika somo lililopita, ulijifunza jinsi ya kuunganisha mmea wako na MQTT broker na kudhibiti relay kutoka kwa msimbo wa seva unaoendesha ndani ya nchi. Hii ni msingi wa aina ya mfumo wa kumwagilia maji kiotomatiki unaounganishwa na mtandao, unaotumika kutoka kwa mimea ya mtu binafsi nyumbani hadi mashamba ya kibiashara.

Kifaa cha IoT kilichokuwasiliana na MQTT broker ya umma kilitumika kuonyesha kanuni, lakini hii si njia ya kuaminika au salama zaidi. Katika somo hili, utajifunza kuhusu wingu na uwezo wa IoT unaotolewa na huduma za wingu za umma. Pia utajifunza jinsi ya kuhamisha mmea wako kwenye mojawapo ya huduma hizi za wingu kutoka kwa MQTT broker ya umma.

Katika somo hili tutashughulikia:

* [Wingu ni nini?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Unda usajili wa wingu](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Huduma za IoT za wingu](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Unda huduma ya IoT kwenye wingu](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Wasiliana na IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Unganisha kifaa chako na huduma ya IoT](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Wingu ni nini?

Kabla ya wingu, kampuni zilipotaka kutoa huduma kwa wafanyakazi wao (kama vile hifadhidata au uhifadhi wa faili), au kwa umma (kama vile tovuti), walijenga na kuendesha kituo cha data. Hii ilihusisha chumba chenye kompyuta chache hadi jengo lenye kompyuta nyingi. Kampuni ilihitaji kusimamia kila kitu, ikiwa ni pamoja na:

* Kununua kompyuta
* Matengenezo ya vifaa
* Umeme na baridi
* Mtandao
* Usalama, ikiwa ni pamoja na kulinda jengo na programu kwenye kompyuta
* Usakinishaji wa programu na masasisho

Hii ilikuwa ghali sana, ilihitaji wafanyakazi wenye ujuzi mbalimbali, na ilikuwa polepole kubadilika inapohitajika. Kwa mfano, ikiwa duka la mtandaoni lilihitaji kupanga msimu wa likizo wenye shughuli nyingi, walihitaji kupanga miezi kadhaa mapema kununua vifaa zaidi, kuviweka, na kusakinisha programu ya kuendesha mchakato wa mauzo. Baada ya msimu wa likizo kuisha na mauzo kushuka, walibaki na kompyuta walizolipia zikiwa hazitumiki hadi msimu mwingine wenye shughuli nyingi.

✅ Je, unadhani hii ingewawezesha kampuni kusonga haraka? Ikiwa muuzaji wa nguo mtandaoni ghafla akawa maarufu kwa sababu ya mtu mashuhuri kuonekana akiwa amevaa nguo zao, je, wangeweza kuongeza nguvu ya kompyuta haraka vya kutosha kushughulikia ongezeko la ghafla la maagizo?

### Kompyuta ya mtu mwingine

Wingu mara nyingi hurejelewa kwa utani kama 'kompyuta ya mtu mwingine'. Wazo la awali lilikuwa rahisi - badala ya kununua kompyuta, unakodisha kompyuta ya mtu mwingine. Mtoa huduma wa wingu angeweza kusimamia vituo vikubwa vya data. Wao wangekuwa na jukumu la kununua na kusakinisha vifaa, kusimamia umeme na baridi, mtandao, usalama wa jengo, masasisho ya vifaa na programu, kila kitu. Kama mteja, ungekodisha kompyuta unazohitaji, ukikodisha zaidi wakati mahitaji yanapoongezeka, kisha kupunguza idadi unayokodisha ikiwa mahitaji yanapungua. Vituo hivi vya data vya wingu viko kote ulimwenguni.

![Kituo cha data cha wingu cha Microsoft](../../../../../translated_images/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.sw.png)
![Upanuzi uliopangwa wa kituo cha data cha wingu cha Microsoft](../../../../../translated_images/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.sw.png)

Vituo hivi vya data vinaweza kuwa na ukubwa wa kilomita za mraba nyingi. Picha zilizo hapo juu zilipigwa miaka michache iliyopita katika kituo cha data cha wingu cha Microsoft, na zinaonyesha ukubwa wa awali, pamoja na upanuzi uliopangwa. Eneo lililoandaliwa kwa ajili ya upanuzi lina zaidi ya kilomita za mraba 5.

> 💁 Vituo hivi vya data vinahitaji kiasi kikubwa cha umeme kiasi kwamba vingine vina vituo vyao vya kuzalisha umeme. Kwa sababu ya ukubwa wao na kiwango cha uwekezaji kutoka kwa watoa huduma wa wingu, mara nyingi ni rafiki wa mazingira. Ni bora zaidi kuliko vituo vidogo vidogo vya data, vinaendeshwa zaidi kwa nishati mbadala, na watoa huduma wa wingu hufanya kazi kwa bidii kupunguza taka, kupunguza matumizi ya maji, na kupanda tena misitu ili kufidia ile iliyokatwa ili kutoa nafasi ya kujenga vituo vya data. Unaweza kusoma zaidi kuhusu jinsi mtoa huduma mmoja wa wingu anavyofanya kazi kwenye uendelevu kwenye [tovuti ya uendelevu ya Azure](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Fanya utafiti: Soma kuhusu wingu kuu kama [Azure kutoka Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) au [GCP kutoka Google](https://cloud.google.com). Vituo vya data vina ngapi, na viko wapi duniani?

Kutumia wingu hupunguza gharama kwa kampuni, na huwapa nafasi ya kuzingatia kile wanachofanya vizuri zaidi, huku utaalamu wa kompyuta za wingu ukiwa mikononi mwa mtoa huduma. Kampuni hazihitaji tena kukodisha au kununua nafasi ya kituo cha data, kulipa watoa huduma tofauti kwa muunganisho na umeme, au kuajiri wataalamu. Badala yake, wanaweza kulipa bili moja ya kila mwezi kwa mtoa huduma wa wingu ili kila kitu kishughulikiwe.

Mtoa huduma wa wingu anaweza kutumia uchumi wa kiwango kupunguza gharama, kununua kompyuta kwa wingi kwa bei ya chini, kuwekeza katika zana za kupunguza kazi yao ya matengenezo, hata kubuni na kujenga vifaa vyao wenyewe ili kuboresha huduma yao ya wingu.

### Microsoft Azure

Azure ni wingu la watengenezaji kutoka Microsoft, na hili ndilo wingu utakalotumia kwa masomo haya. Video iliyo hapa chini inatoa muhtasari mfupi wa Azure:

[![Video ya muhtasari wa Azure](../../../../../translated_images/what-is-azure-video-thumbnail.20174db09e03bbb8.sw.png)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Unda usajili wa wingu

Ili kutumia huduma kwenye wingu, utahitaji kujisajili kwa usajili na mtoa huduma wa wingu. Kwa somo hili, utajisajili kwa usajili wa Microsoft Azure. Ikiwa tayari una usajili wa Azure unaweza kuruka kazi hii. Maelezo ya usajili yaliyoelezwa hapa ni sahihi wakati wa kuandika, lakini yanaweza kubadilika.

> 💁 Ikiwa unapata masomo haya kupitia shule yako, huenda tayari una usajili wa Azure unaopatikana kwako. Angalia na mwalimu wako.

Kuna aina mbili tofauti za usajili wa bure wa Azure unazoweza kujisajili:

* **Azure kwa Wanafunzi** - Huu ni usajili ulioundwa kwa wanafunzi wenye umri wa miaka 18+. Huhitaji kadi ya mkopo kujisajili, na unatumia barua pepe ya shule yako kuthibitisha kuwa wewe ni mwanafunzi. Unapojisajili unapata Dola za Marekani $100 za kutumia kwenye rasilimali za wingu, pamoja na huduma za bure ikiwa ni pamoja na toleo la bure la huduma ya IoT. Hii hudumu kwa miezi 12, na unaweza kuhuisha kila mwaka unapobaki kuwa mwanafunzi.

* **Usajili wa bure wa Azure** - Huu ni usajili kwa yeyote ambaye si mwanafunzi. Utahitaji kadi ya mkopo kujisajili kwa usajili, lakini kadi yako haitatozwa, hii ni kwa ajili ya kuthibitisha kuwa wewe ni binadamu halisi, si roboti. Unapata $200 za mkopo kutumia katika siku 30 za kwanza kwenye huduma yoyote, pamoja na viwango vya bure vya huduma za Azure. Mara mkopo wako unapokwisha, kadi yako haitatozwa isipokuwa ubadilishe kuwa usajili wa kulipa kadri unavyotumia.

> 💁 Microsoft pia inatoa usajili wa Azure kwa Wanafunzi Starter kwa wanafunzi walio chini ya miaka 18, lakini kwa wakati wa kuandika hii haiauni huduma yoyote ya IoT.

### Kazi - jisajili kwa usajili wa bure wa wingu

Ikiwa wewe ni mwanafunzi mwenye umri wa miaka 18+, basi unaweza kujisajili kwa usajili wa Azure kwa Wanafunzi. Utahitaji kuthibitisha kwa barua pepe ya shule. Unaweza kufanya hivi kwa njia mbili:

* Jisajili kwa kifurushi cha GitHub student developer pack kwenye [education.github.com/pack](https://education.github.com/pack). Hii inakupa ufikiaji wa zana na ofa mbalimbali, ikiwa ni pamoja na GitHub na Microsoft Azure. Mara unapojisajili kwa kifurushi cha developer, unaweza kisha kuamsha ofa ya Azure kwa Wanafunzi.

* Jisajili moja kwa moja kwa akaunti ya Azure kwa Wanafunzi kwenye [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Ikiwa barua pepe ya shule yako haitambuliki, fungua [suala katika repo hii](https://github.com/Microsoft/IoT-For-Beginners/issues) na tutaangalia ikiwa inaweza kuongezwa kwenye orodha ya kuruhusiwa ya Azure kwa Wanafunzi.

Ikiwa si mwanafunzi, au huna barua pepe halali ya shule, basi unaweza kujisajili kwa usajili wa bure wa Azure.

* Jisajili kwa Usajili wa Bure wa Azure kwenye [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Huduma za IoT za wingu

MQTT broker ya majaribio ya umma uliyokuwa ukitumia ni zana nzuri unapojifunza, lakini ina changamoto kadhaa kama zana ya kutumia katika mazingira ya kibiashara:

* Uaminifu - ni huduma ya bure isiyo na dhamana, na inaweza kuzimwa wakati wowote
* Usalama - ni ya umma, hivyo mtu yeyote anaweza kusikiliza telemetry yako au kutuma amri za kudhibiti vifaa vyako
* Utendaji - imeundwa kwa ujumbe wa majaribio machache tu, hivyo haiwezi kushughulikia idadi kubwa ya ujumbe unaotumwa
* Ugunduzi - hakuna njia ya kujua ni vifaa gani vimeunganishwa

Huduma za IoT kwenye wingu hutatua matatizo haya. Zinasimamiwa na watoa huduma wakubwa wa wingu ambao wanawekeza sana katika uaminifu na wako tayari kushughulikia matatizo yoyote yanayoweza kutokea. Zina usalama uliojengewa ndani ili kuzuia wadukuzi kusoma data yako au kutuma amri za uongo. Pia zina utendaji wa hali ya juu, zikiwa na uwezo wa kushughulikia mamilioni ya ujumbe kila siku, zikichukua faida ya wingu kupanuka inapohitajika.

> 💁 Ingawa unalipia faida hizi kwa ada ya kila mwezi, watoa huduma wengi wa wingu hutoa toleo la bure la huduma yao ya IoT lenye idadi ndogo ya ujumbe kwa siku au vifaa vinavyoweza kuunganishwa. Toleo hili la bure mara nyingi linatosha kwa msanidi programu kujifunza kuhusu huduma hiyo. Katika somo hili utatumia toleo la bure.

Vifaa vya IoT vinaunganishwa na huduma ya wingu ama kwa kutumia SDK ya kifaa (maktaba inayotoa msimbo wa kufanya kazi na vipengele vya huduma), au moja kwa moja kupitia itifaki ya mawasiliano kama vile MQTT au HTTP. SDK ya kifaa mara nyingi ni njia rahisi zaidi kwani inashughulikia kila kitu kwa niaba yako, kama vile kujua mada za kuchapisha au kujiandikisha, na jinsi ya kushughulikia usalama.

![Vifaa vinaunganishwa na huduma kwa kutumia SDK ya kifaa. Msimbo wa seva pia unaunganishwa na huduma kupitia SDK](../../../../../translated_images/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.sw.png)

Kifaa chako kisha huwasiliana na sehemu nyingine za programu yako kupitia huduma hii - sawa na jinsi ulivyotuma telemetry na kupokea amri kupitia MQTT. Hii mara nyingi hufanyika kwa kutumia SDK ya huduma au maktaba kama hiyo. Ujumbe hutoka kwenye kifaa chako kwenda kwenye huduma ambapo sehemu nyingine za programu yako zinaweza kuusoma, na ujumbe unaweza kutumwa kurudi kwenye kifaa chako.

![Vifaa visivyo na ufunguo wa siri halali haviwezi kuunganishwa na huduma ya IoT](../../../../../translated_images/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.sw.png)

Huduma hizi hutekeleza usalama kwa kujua kuhusu vifaa vyote vinavyoweza kuunganishwa na kutuma data, ama kwa kuwa na vifaa vilivyosajiliwa mapema na huduma, au kwa kuvipa vifaa funguo za siri au vyeti ambavyo vinaweza kutumia kujisajili na huduma mara ya kwanza vinapounganishwa. Vifaa visivyojulikana haviwezi kuunganishwa, vikijaribu huduma hukataa muunganisho na kupuuza ujumbe unaotumwa navyo.

✅ Fanya utafiti: Ni hasara gani ya kuwa na huduma ya IoT iliyo wazi ambapo kifaa chochote au msimbo unaweza kuunganishwa? Je, unaweza kupata mifano mahususi ya wadukuzi kutumia hali hii vibaya?

Sehemu nyingine za programu yako zinaweza kuunganishwa na huduma ya IoT na kujifunza kuhusu vifaa vyote vilivyounganishwa au vilivyosajiliwa, na kuwasiliana navyo moja kwa moja kwa wingi au kibinafsi.
💁 Huduma za IoT pia hutekeleza uwezo wa ziada, na watoa huduma wa wingu wana huduma na programu za ziada ambazo zinaweza kuunganishwa na huduma hiyo. Kwa mfano, ikiwa unataka kuhifadhi ujumbe wote wa telemetry uliotumwa na vifaa vyote kwenye hifadhidata, mara nyingi ni suala la kubofya mara chache tu kwenye zana ya usanidi ya mtoa huduma wa wingu ili kuunganisha huduma hiyo na hifadhidata na kusambaza data ndani.
## Unda huduma ya IoT kwenye wingu

Sasa kwa kuwa una usajili wa Azure, unaweza kujisajili kwa huduma ya IoT. Huduma ya IoT kutoka Microsoft inaitwa Azure IoT Hub.

![Nembo ya Azure IoT Hub](../../../../../translated_images/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.sw.png)

Video hapa chini inatoa muhtasari mfupi wa Azure IoT Hub:

[![Muhtasari wa video ya Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Bofya picha hapo juu kutazama video

✅ Chukua muda kufanya utafiti na kusoma muhtasari wa IoT Hub katika [Microsoft IoT Hub documentation](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Huduma za wingu zinazopatikana kwenye Azure zinaweza kusanidiwa kupitia portal ya mtandao, au kupitia kiolesura cha mstari wa amri (CLI). Kwa kazi hii, utatumia CLI.

### Kazi - Sakinisha Azure CLI

Ili kutumia Azure CLI, kwanza lazima isakinishwe kwenye PC au Mac yako.

1. Fuata maelekezo katika [Azure CLI documentation](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) kusakinisha CLI.

1. Azure CLI inaunga mkono idadi ya viendelezi vinavyoongeza uwezo wa kusimamia huduma mbalimbali za Azure. Sakinisha kiendelezi cha IoT kwa kuendesha amri ifuatayo kutoka kwa mstari wa amri au terminal yako:

    ```sh
    az extension add --name azure-iot
    ```

1. Kutoka kwa mstari wa amri au terminal yako, endesha amri ifuatayo kuingia kwenye usajili wako wa Azure kutoka Azure CLI.

    ```sh
    az login
    ```

    Ukurasa wa wavuti utafunguliwa kwenye kivinjari chako cha chaguo-msingi. Ingia kwa kutumia akaunti uliyotumia kujisajili kwa usajili wa Azure. Mara tu umeingia, unaweza kufunga tab ya kivinjari.

1. Ikiwa una usajili mwingi wa Azure, kama ule uliotolewa na shule, na usajili wako wa Azure kwa Wanafunzi, utahitaji kuchagua ule unaotaka kutumia. Endesha amri ifuatayo kuorodhesha usajili wote ulio nao:

    ```sh
    az account list --output table
    ```

    Katika matokeo, utaona jina la kila usajili pamoja na `SubscriptionId` yake.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Ili kuchagua usajili unaotaka kutumia, tumia amri ifuatayo:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Badilisha `<SubscriptionId>` na Id ya usajili unaotaka kutumia. Baada ya kuendesha amri hii, endesha tena amri ya kuorodhesha akaunti zako. Utaona safu ya `IsDefault` itawekwa alama kama `True` kwa usajili ulioweka.

### Kazi - Unda kikundi cha rasilimali

Huduma za Azure, kama vile mifano ya IoT Hub, mashine pepe, hifadhidata, au huduma za AI, zinajulikana kama **rasilimali**. Kila rasilimali lazima iwe ndani ya **Kikundi cha Rasilimali**, kikundi cha kimantiki cha rasilimali moja au zaidi.

> 💁 Kutumia vikundi vya rasilimali inamaanisha unaweza kusimamia huduma nyingi mara moja. Kwa mfano, mara tu unapomaliza masomo yote ya mradi huu unaweza kufuta kikundi cha rasilimali, na rasilimali zote ndani yake zitafutwa moja kwa moja.

1. Kuna vituo vya data vya Azure vingi duniani kote, vilivyogawanywa katika maeneo. Unapounda rasilimali au kikundi cha rasilimali cha Azure, lazima ueleze mahali unapotaka iundwe. Endesha amri ifuatayo kupata orodha ya maeneo:

    ```sh
    az account list-locations --output table
    ```

    Utaona orodha ya maeneo. Orodha hii itakuwa ndefu.

    > 💁 Kwa wakati wa kuandika, kuna maeneo 65 unayoweza kupeleka.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Andika thamani kutoka safu ya `Name` ya eneo lililo karibu nawe. Unaweza kupata maeneo kwenye ramani kwenye [Azure geographies page](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Endesha amri ifuatayo kuunda kikundi cha rasilimali kinachoitwa `soil-moisture-sensor`. Majina ya vikundi vya rasilimali lazima yawe ya kipekee katika usajili wako.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Badilisha `<location>` na eneo ulilochagua katika hatua ya awali.

### Kazi - Unda IoT Hub

Sasa unaweza kuunda rasilimali ya IoT Hub katika kikundi chako cha rasilimali.

1. Tumia amri ifuatayo kuunda rasilimali yako ya IoT Hub:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Badilisha `<hub_name>` na jina la hub yako. Jina hili linahitaji kuwa la kipekee duniani kote - yaani hakuna IoT Hub nyingine iliyoundwa na mtu yeyote inaweza kuwa na jina sawa. Jina hili linatumika katika URL inayotaja hub, kwa hivyo linahitaji kuwa la kipekee. Tumia kitu kama `soil-moisture-sensor-` na ongeza kitambulisho cha kipekee mwishoni, kama maneno ya nasibu au jina lako.

    Chaguo la `--sku F1` linaeleza kutumia kiwango cha bure. Kiwango cha bure kinaunga mkono ujumbe 8,000 kwa siku pamoja na vipengele vingi vya viwango vya bei kamili.

    > 🎓 Viwango tofauti vya bei vya huduma za Azure vinajulikana kama tiers. Kila tier ina gharama tofauti na hutoa vipengele au kiasi cha data tofauti.

    > 💁 Ikiwa unataka kujifunza zaidi kuhusu bei, unaweza kuangalia [Azure IoT Hub pricing guide](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Chaguo la `--partition-count 2` linafafanua idadi ya mitiririko ya data ambayo IoT Hub inaunga mkono, partitions zaidi hupunguza kuzuia data wakati vitu vingi vinasoma na kuandika kutoka IoT Hub. Partitions ziko nje ya wigo wa masomo haya, lakini thamani hii inahitaji kuwekwa ili kuunda IoT Hub ya kiwango cha bure.

    > 💁 Unaweza kuwa na IoT Hub moja tu ya kiwango cha bure kwa usajili.

IoT Hub itaundwa. Inaweza kuchukua dakika moja au zaidi kukamilika.

## Kuwasiliana na IoT Hub

Katika somo la awali, ulitumia MQTT na kutuma ujumbe mbele na nyuma kwenye mada tofauti, huku mada tofauti zikiwa na madhumuni tofauti. Badala ya kutuma ujumbe juu ya mada tofauti, IoT Hub ina njia kadhaa zilizofafanuliwa kwa kifaa kuwasiliana na Hub, au kwa Hub kuwasiliana na kifaa.

> 💁 Chini ya kapoti, mawasiliano haya kati ya IoT Hub na kifaa chako yanaweza kutumia MQTT, HTTPS au AMQP.

* Ujumbe wa kifaa kwenda wingu (D2C) - hizi ni ujumbe unaotumwa kutoka kwa kifaa kwenda IoT Hub, kama telemetry. Kisha zinaweza kusomwa kutoka IoT Hub na msimbo wa programu yako.

    > 🎓 Chini ya kapoti, IoT Hub hutumia huduma ya Azure inayoitwa [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Unapoandika msimbo wa kusoma ujumbe uliotumwa kwa hub, mara nyingi huitwa matukio.

* Ujumbe wa wingu kwenda kifaa (C2D) - hizi ni ujumbe unaotumwa kutoka kwa msimbo wa programu, kupitia IoT Hub kwenda kifaa cha IoT.

* Maombi ya njia ya moja kwa moja - hizi ni ujumbe unaotumwa kutoka kwa msimbo wa programu kupitia IoT Hub kwenda kifaa cha IoT kuomba kifaa kifanye kitu, kama kudhibiti actuator. Ujumbe huu unahitaji majibu ili msimbo wa programu yako uweze kujua ikiwa ulifanyiwa kazi kwa mafanikio.

* Device twins - hizi ni hati za JSON zinazohifadhiwa kwa usawazishaji kati ya kifaa na IoT Hub, na hutumika kuhifadhi mipangilio au mali nyingine ama zilizoripotiwa na kifaa, au zinapaswa kuwekwa kwenye kifaa (zinajulikana kama zinazotakiwa) na IoT Hub.

IoT Hub inaweza kuhifadhi ujumbe na maombi ya njia ya moja kwa moja kwa muda unaoweza kusanidiwa (kwa chaguo-msingi siku moja), kwa hivyo ikiwa kifaa au msimbo wa programu unapoteza muunganisho, bado kinaweza kupata ujumbe uliotumwa wakati kilikuwa nje ya mtandao baada ya kuunganishwa tena. Device twins zinahifadhiwa daima katika IoT Hub, kwa hivyo wakati wowote kifaa kinaweza kuunganishwa tena na kupata device twin ya hivi karibuni.

✅ Fanya utafiti: Soma zaidi kuhusu aina hizi za ujumbe kwenye [Device-to-cloud communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn), na [Cloud-to-device communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) katika IoT Hub documentation.

## Unganisha kifaa chako na huduma ya IoT

Mara tu hub imeundwa, kifaa chako cha IoT kinaweza kuunganishwa nayo. Ni vifaa vilivyosajiliwa tu vinaweza kuunganishwa na huduma, kwa hivyo utahitaji kusajili kifaa chako kwanza. Unaposajili unaweza kupata kamba ya muunganisho ambayo kifaa kinaweza kutumia kuunganishwa. Kamba ya muunganisho ni maalum kwa kifaa, na ina taarifa kuhusu IoT Hub, kifaa, na ufunguo wa siri ambao utaruhusu kifaa hiki kuunganishwa.

> 🎓 Kamba ya muunganisho ni neno la jumla kwa kipande cha maandishi kinachojumuisha maelezo ya muunganisho. Hizi hutumiwa wakati wa kuunganishwa na IoT Hubs, hifadhidata na huduma nyingine nyingi. Kwa kawaida huwa na kitambulisho cha huduma, kama URL, na taarifa za usalama kama ufunguo wa siri. Hizi hupitishwa kwa SDKs kuunganishwa na huduma.

> ⚠️ Kamba za muunganisho zinapaswa kuhifadhiwa salama! Usalama utajadiliwa kwa undani zaidi katika somo la baadaye.

### Kazi - Sajili kifaa chako cha IoT

Kifaa cha IoT kinaweza kusajiliwa na IoT Hub yako kwa kutumia Azure CLI.

1. Endesha amri ifuatayo kusajili kifaa:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Badilisha `<hub_name>` na jina ulilotumia kwa IoT Hub yako.

    Hii itaunda kifaa chenye ID ya `soil-moisture-sensor`.

1. Wakati kifaa chako cha IoT kinaunganishwa na IoT Hub yako kwa kutumia SDK, kinahitaji kutumia kamba ya muunganisho inayotoa URL ya hub, pamoja na ufunguo wa siri. Endesha amri ifuatayo kupata kamba ya muunganisho:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Badilisha `<hub_name>` na jina ulilotumia kwa IoT Hub yako.

1. Hifadhi kamba ya muunganisho inayoonyeshwa kwenye matokeo kwani utaihitaji baadaye.

### Kazi - Unganisha kifaa chako cha IoT na wingu

Fanya kazi kupitia mwongozo husika kuunganisha kifaa chako cha IoT na wingu:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Kompyuta ya bodi moja - Raspberry Pi/Kifaa cha IoT cha Kijijini](single-board-computer-connect-hub.md)

### Kazi - Fuatilia matukio

Kwa sasa, hautasasisha msimbo wa seva yako. Badala yake unaweza kutumia Azure CLI kufuatilia matukio kutoka kwa kifaa chako cha IoT.

1. Hakikisha kifaa chako cha IoT kinafanya kazi na kinatuma thamani za telemetry za unyevu wa udongo.

1. Endesha amri ifuatayo kwenye terminal yako kufuatilia ujumbe uliotumwa kwa IoT Hub yako:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Badilisha `<hub_name>` na jina ulilotumia kwa IoT Hub yako.

    Utaona ujumbe ukionekana kwenye matokeo ya terminal kadri unavyotumwa na kifaa chako cha IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Yaliyomo ya `payload` yatalingana na ujumbe uliotumwa na kifaa chako cha IoT.

    > Kwa wakati wa kuandika, kiendelezi cha `az iot` hakifanyi kazi kikamilifu kwenye Apple Silicon. Ikiwa unatumia kifaa cha Apple Silicon, utahitaji kufuatilia ujumbe kwa njia tofauti, kama kutumia [Azure IoT Tools for Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Ujumbe huu una mali kadhaa zilizoambatanishwa nao moja kwa moja, kama timestamp walivyotumwa. Hizi zinajulikana kama *annotations*. Ili kuona annotations zote za ujumbe, tumia amri ifuatayo:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Badilisha `<hub_name>` na jina ulilotumia kwa IoT Hub yako.

    Utaona ujumbe ukionekana kwenye matokeo ya terminal kadri unavyotumwa na kifaa chako cha IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Thamani za wakati katika annotations ziko katika [UNIX time](https://wikipedia.org/wiki/Unix_time), zinazoonyesha idadi ya sekunde tangu usiku wa manane tarehe 1 Januari 1970.

    Toka kwenye monitor ya matukio unapomaliza.

### Kazi - Dhibiti kifaa chako cha IoT

Unaweza pia kutumia Azure CLI kuita njia za moja kwa moja kwenye kifaa chako cha IoT.

1. Endesha amri ifuatayo kwenye terminal yako kuamsha njia ya `relay_on` kwenye kifaa cha IoT:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Badilisha `
<hub_name>
` na jina ulilotumia kwa IoT Hub yako.

Hii inatuma ombi la moja kwa moja la njia kwa njia iliyobainishwa na `method-name`. Njia za moja kwa moja zinaweza kuchukua mzigo wa data kwa njia hiyo, na hii inaweza kubainishwa katika kipengele cha `method-payload` kama JSON.

Utaona relay ikiwashwa, na matokeo yanayolingana kutoka kwa kifaa chako cha IoT:

```output
    Direct method received -  relay_on
    ```

1. Rudia hatua ya juu, lakini weka `--method-name` kuwa `relay_off`. Utaona relay ikizimwa na matokeo yanayolingana kutoka kwa kifaa cha IoT.

---

## 🚀 Changamoto

Kiwango cha bure cha IoT Hub huruhusu jumla ya ujumbe 8,000 kwa siku. Msimbo uliouandika hutuma ujumbe wa telemetry kila sekunde 10. Je, ujumbe mmoja kila sekunde 10 unamaanisha ujumbe ngapi kwa siku?

Fikiria kuhusu mara ngapi vipimo vya unyevu wa udongo vinapaswa kutumwa? Unawezaje kubadilisha msimbo wako ili kubaki ndani ya kiwango cha bure na kuangalia mara nyingi inavyohitajika lakini si mara nyingi sana? Je, itakuwaje kama ungependa kuongeza kifaa cha pili?

## Jaribio baada ya somo

[Jaribio baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Mapitio na Kujisomea

SDK ya IoT Hub ni chanzo huria kwa Arduino na Python. Katika hazina za msimbo kwenye GitHub kuna sampuli kadhaa zinazoonyesha jinsi ya kufanya kazi na vipengele tofauti vya IoT Hub.

* Ikiwa unatumia Wio Terminal, angalia [sampuli za Arduino kwenye GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Ikiwa unatumia Raspberry Pi au kifaa cha Virtual, angalia [sampuli za Python kwenye GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Kazi

[Jifunze kuhusu huduma za wingu](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya kiasili inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.