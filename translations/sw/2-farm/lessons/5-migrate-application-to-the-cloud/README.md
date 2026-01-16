<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-27T22:56:46+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "sw"
}
-->
# Hamishia mantiki ya programu yako kwenye wingu

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa.

Somo hili lilifundishwa kama sehemu ya [Mradi wa IoT kwa Kompyuta - Mfululizo wa Kilimo Kidigitali](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) kutoka [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Dhibiti kifaa chako cha IoT kwa kutumia msimbo usio na seva](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Jaribio la kabla ya somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Utangulizi

Katika somo la mwisho, ulijifunza jinsi ya kuunganisha ufuatiliaji wa unyevu wa udongo wa mimea yako na udhibiti wa relay kwenye huduma ya IoT inayotegemea wingu. Hatua inayofuata ni kuhamisha msimbo wa seva unaodhibiti muda wa relay kwenye wingu. Katika somo hili, utajifunza jinsi ya kufanya hivyo kwa kutumia kazi zisizo na seva.

Katika somo hili tutashughulikia:

* [Serverless ni nini?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Unda programu isiyo na seva](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Unda kichocheo cha tukio la IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Tuma maombi ya njia ya moja kwa moja kutoka kwa msimbo usio na seva](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Hamisha msimbo wako usio na seva kwenye wingu](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Serverless ni nini?

Serverless, au kompyuta isiyo na seva, inahusisha kuunda vizuizi vidogo vya msimbo vinavyoendeshwa kwenye wingu kwa kujibu aina tofauti za matukio. Tukio linapotokea, msimbo wako unaendeshwa, na unapokea data kuhusu tukio hilo. Matukio haya yanaweza kutoka kwa vitu vingi tofauti, ikiwa ni pamoja na maombi ya wavuti, ujumbe uliowekwa kwenye foleni, mabadiliko ya data kwenye hifadhidata, au ujumbe uliotumwa kwa huduma ya IoT na vifaa vya IoT.

![Matukio yanayotumwa kutoka kwa huduma ya IoT kwenda kwa huduma isiyo na seva, yote yakichakatwa kwa wakati mmoja na kazi nyingi zinazotendeka](../../../../../translated_images/sw/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.png)

> 💁 Ikiwa umewahi kutumia vichocheo vya hifadhidata, unaweza kufikiria hili kama kitu sawa, msimbo unaochochewa na tukio kama kuingiza safu.

![Wakati matukio mengi yanatumwa kwa wakati mmoja, huduma isiyo na seva inapanuka ili kuyashughulikia yote kwa wakati mmoja](../../../../../translated_images/sw/serverless-scaling.f8c769adf0413fd1.webp)

Msimbo wako unaendeshwa tu tukio linapotokea, hakuna kitu kinachohifadhi msimbo wako ukiwa hai nyakati nyingine. Tukio linatokea, msimbo wako unapakiwa na kuendeshwa. Hii inafanya serverless kuwa na uwezo mkubwa wa kupanuka - ikiwa matukio mengi yanatokea kwa wakati mmoja, mtoa huduma wa wingu anaweza kuendesha kazi yako mara nyingi kadri unavyohitaji kwa wakati mmoja kwenye seva zozote walizonazo. Hasara ya hili ni kwamba ikiwa unahitaji kushiriki taarifa kati ya matukio, unahitaji kuziokoa mahali fulani kama hifadhidata badala ya kuzihifadhi kwenye kumbukumbu.

Msimbo wako unaandikwa kama kazi inayochukua maelezo kuhusu tukio kama parameter. Unaweza kutumia lugha mbalimbali za programu kuandika kazi hizi zisizo na seva.

> 🎓 Serverless pia inajulikana kama Functions as a Service (FaaS) kwani kila kichocheo cha tukio kinatekelezwa kama kazi katika msimbo.

Licha ya jina, serverless kwa kweli hutumia seva. Jina linatokana na kwamba wewe kama msanidi programu haujali kuhusu seva zinazohitajika kuendesha msimbo wako, unachojali ni kwamba msimbo wako unaendeshwa kwa kujibu tukio. Mtoa huduma wa wingu ana *runtime* isiyo na seva inayosimamia kugawa seva, mitandao, hifadhi, CPU, kumbukumbu na kila kitu kingine kinachohitajika kuendesha msimbo wako. Mfano huu unamaanisha huwezi kulipa kwa seva kwa huduma, kwani hakuna seva. Badala yake unalipa kwa muda msimbo wako unavyoendeshwa, na kiasi cha kumbukumbu kinachotumika.

> 💰 Serverless ni mojawapo ya njia za gharama nafuu za kuendesha msimbo kwenye wingu. Kwa mfano, wakati wa kuandika, mtoa huduma mmoja wa wingu huruhusu kazi zako zote zisizo na seva kutekelezwa mara 1,000,000 kwa mwezi kabla ya kuanza kukutoza, na baada ya hapo wanatoza US$0.20 kwa kila utekelezaji 1,000,000. Wakati msimbo wako hauendeshwi, hulipi.

Kama msanidi programu wa IoT, mfano wa serverless ni bora. Unaweza kuandika kazi inayoitwa kwa kujibu ujumbe uliotumwa kutoka kwa kifaa chochote cha IoT kilichounganishwa na huduma yako ya IoT inayohifadhiwa kwenye wingu. Msimbo wako utashughulikia ujumbe wote uliotumwa, lakini utaendeshwa tu unapohitajika.

✅ Angalia tena msimbo uliouandika kama msimbo wa seva unaosikiliza ujumbe kupitia MQTT. Je, unaweza kufikiria jinsi hii inaweza kuendeshwa kwenye wingu kwa kutumia serverless? Je, unafikiri msimbo unaweza kubadilishwa vipi ili kuunga mkono kompyuta isiyo na seva?

> 💁 Mfano wa serverless unahamia huduma nyingine za wingu pamoja na kuendesha msimbo. Kwa mfano, hifadhidata zisizo na seva zinapatikana kwenye wingu kwa kutumia mfano wa bei ya serverless ambapo unalipa kwa ombi lililofanywa dhidi ya hifadhidata, kama swala au kuingiza, kwa kawaida kwa kutumia bei kulingana na kiasi cha kazi inayofanywa kuhudumia ombi. Kwa mfano, kuchagua safu moja dhidi ya ufunguo wa msingi kutagharimu kidogo kuliko operesheni ngumu inayounganisha meza nyingi na kurudisha maelfu ya safu.

## Unda programu isiyo na seva

Huduma ya kompyuta isiyo na seva kutoka Microsoft inaitwa Azure Functions.

![Nembo ya Azure Functions](../../../../../translated_images/sw/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.png)

Video fupi hapa chini ina muhtasari wa Azure Functions.

[![Video ya muhtasari wa Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Bofya picha hapo juu kutazama video.

✅ Chukua muda kufanya utafiti na usome muhtasari wa Azure Functions katika [Nyaraka za Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Ili kuandika Azure Functions, unaanza na programu ya Azure Functions katika lugha unayopendelea. Azure Functions inasaidia Python, JavaScript, TypeScript, C#, F#, Java, na Powershell. Katika somo hili utajifunza jinsi ya kuandika programu ya Azure Functions kwa kutumia Python.

> 💁 Azure Functions pia inasaidia wahandisi maalum ili uweze kuandika kazi zako katika lugha yoyote inayounga mkono maombi ya HTTP, ikiwa ni pamoja na lugha za zamani kama COBOL.

Programu za Functions zinajumuisha moja au zaidi *vichocheo* - kazi zinazojibu matukio. Unaweza kuwa na vichocheo vingi ndani ya programu moja ya Functions, vyote vikishiriki usanidi wa kawaida. Kwa mfano, katika faili ya usanidi wa programu yako ya Functions unaweza kuwa na maelezo ya muunganisho wa IoT Hub yako, na kazi zote katika programu zinaweza kutumia hii kuungana na kusikiliza matukio.

### Kazi - weka zana za Azure Functions

> Wakati wa kuandika, zana za msimbo wa Azure Functions hazifanyi kazi kikamilifu kwenye Apple Silicon na miradi ya Python. Utahitaji kutumia Mac inayotegemea Intel, PC ya Windows, au PC ya Linux badala yake.

Moja ya vipengele bora vya Azure Functions ni kwamba unaweza kuziendesha ndani ya kompyuta yako. Runtime sawa inayotumika kwenye wingu inaweza kuendeshwa kwenye kompyuta yako, ikikuruhusu kuandika msimbo unaojibu ujumbe wa IoT na kuendesha ndani ya kompyuta yako. Unaweza hata kufuatilia msimbo wako unaposhughulikia matukio. Mara tu unapokuwa na uhakika na msimbo wako, unaweza kuuhamisha kwenye wingu.

Zana za Azure Functions zinapatikana kama CLI, inayojulikana kama Azure Functions Core Tools.

1. Weka zana za msingi za Azure Functions kwa kufuata maelekezo kwenye [Nyaraka za Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Weka kiendelezi cha Azure Functions kwa VS Code. Kiendelezi hiki kinatoa msaada wa kuunda, kufuatilia, na kuhamisha Azure Functions. Rejelea [Nyaraka za kiendelezi cha Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) kwa maelekezo ya jinsi ya kuweka kiendelezi hiki kwenye VS Code.

Unapohamisha programu yako ya Azure Functions kwenye wingu, inahitaji kutumia kiasi kidogo cha hifadhi ya wingu kuhifadhi vitu kama faili za programu na faili za kumbukumbu. Unapokimbia programu yako ya Functions ndani ya kompyuta yako, bado unahitaji kuungana na hifadhi ya wingu, lakini badala ya kutumia hifadhi halisi ya wingu, unaweza kutumia emulator ya hifadhi inayoitwa [Azurite](https://github.com/Azure/Azurite). Hii inaendeshwa ndani ya kompyuta yako lakini inafanya kazi kama hifadhi ya wingu.

> 🎓 Katika Azure, hifadhi inayotumiwa na Azure Functions ni Akaunti ya Hifadhi ya Azure. Akaunti hizi zinaweza kuhifadhi faili, blobs, data kwenye meza au data kwenye foleni. Unaweza kushiriki akaunti moja ya hifadhi kati ya programu nyingi, kama programu ya Functions na programu ya wavuti.

1. Azurite ni programu ya Node.js, kwa hivyo utahitaji kuweka Node.js. Unaweza kupata maelekezo ya kupakua na kuweka kwenye [Tovuti ya Node.js](https://nodejs.org/). Ikiwa unatumia Mac, unaweza pia kuiweka kutoka [Homebrew](https://formulae.brew.sh/formula/node).

1. Weka Azurite kwa kutumia amri ifuatayo (`npm` ni zana inayowekwa unapoweka Node.js):

    ```sh
    npm install -g azurite
    ```

1. Unda folda inayoitwa `azurite` kwa Azurite kutumia kuhifadhi data:

    ```sh
    mkdir azurite
    ```

1. Endesha Azurite, ukiipatia folda hii mpya:

    ```sh
    azurite --location azurite
    ```

    Emulator ya hifadhi ya Azurite itazinduliwa na kuwa tayari kwa runtime ya Functions kuungana.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Kazi - unda mradi wa Azure Functions

CLI ya Azure Functions inaweza kutumika kuunda programu mpya ya Functions.

1. Unda folda kwa programu yako ya Functions na uingie ndani yake. Ipe jina `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Unda mazingira ya kawaida ya Python ndani ya folda hii:

    ```sh
    python3 -m venv .venv
    ```

1. Washa mazingira ya kawaida:

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

    > 💁 Amri hizi zinapaswa kuendeshwa kutoka eneo lile uliloendesha amri ya kuunda mazingira ya kawaida. Hautahitaji kamwe kuingia kwenye folda ya `.venv`, unapaswa kila wakati kuendesha amri ya kuamsha na amri zozote za kuweka vifurushi au kuendesha msimbo kutoka folda ulipokuwa ulipoanzisha mazingira ya kawaida.

1. Endesha amri ifuatayo kuunda programu ya Functions ndani ya folda hii:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Hii itaunda faili tatu ndani ya folda ya sasa:

    * `host.json` - hati hii ya JSON ina mipangilio ya programu yako ya Functions. Hautahitaji kurekebisha mipangilio hii.
    * `local.settings.json` - hati hii ya JSON ina mipangilio ambayo programu yako ingekuwa nayo wakati wa kuendesha ndani ya kompyuta yako, kama kamba za muunganisho kwa IoT Hub yako. Mipangilio hii ni ya ndani tu, na haipaswi kuongezwa kwenye udhibiti wa msimbo wa chanzo. Unapohamisha programu kwenye wingu, mipangilio hii haihamishwi, badala yake mipangilio yako inapakiwa kutoka mipangilio ya programu. Hii itashughulikiwa baadaye katika somo hili.
    * `requirements.txt` - hii ni [Faili ya mahitaji ya Pip](https://pip.pypa.io/en/stable/user_guide/#requirements-files) inayojumuisha vifurushi vya Pip vinavyohitajika kuendesha programu yako ya Functions.

1. Faili ya `local.settings.json` ina mipangilio ya akaunti ya hifadhi ambayo programu ya Functions itatumia. Hii kwa kawaida ina mipangilio tupu, kwa hivyo inahitaji kuwekwa. Ili kuungana na emulator ya hifadhi ya Azurite, weka thamani hii kwa:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Weka vifurushi vya Pip vinavyohitajika kwa kutumia faili ya mahitaji:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Vifurushi vya Pip vinavyohitajika vinapaswa kuwa kwenye faili hii, ili wakati programu ya Functions inahamishwa kwenye wingu, runtime inaweza kuhakikisha inaweka vifurushi sahihi.

1. Ili kujaribu kila kitu kinafanya kazi vizuri, unaweza kuanza runtime ya Functions. Endesha amri ifuatayo kufanya hivyo:

    ```sh
    func start
    ```

    Utaona runtime ikianza na kuripoti kwamba haijapata kazi zozote za kazi (vichocheo).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Ikiwa unapata arifa ya ukuta wa moto, ruhusu ufikiaji kwani programu ya `func` inahitaji uwezo wa kusoma na kuandika kwenye mtandao wako.
> ⚠️ Ikiwa unatumia macOS, kunaweza kuwa na maonyo kwenye matokeo:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Unaweza kupuuza haya mradi tu programu ya Functions inaanza kwa usahihi na kuorodhesha kazi zinazofanya kazi. Kama ilivyoelezwa katika [swali hili kwenye Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), unaweza kupuuza.

1. Zima programu ya Functions kwa kubonyeza `ctrl+c`.

1. Fungua folda ya sasa kwenye VS Code, ama kwa kufungua VS Code kisha kufungua folda hii, au kwa kuendesha amri ifuatayo:

    ```sh
    code .
    ```

    VS Code itatambua mradi wako wa Functions na kuonyesha arifa ikisema:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Arifa](../../../../../translated_images/sw/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Chagua **Yes** kutoka kwenye arifa hii.

1. Hakikisha mazingira ya kawaida ya Python yanafanya kazi kwenye terminal ya VS Code. Ikomeshe na uianzishe tena ikiwa ni lazima.

## Unda kichocheo cha tukio la IoT Hub

Programu ya Functions ni ganda la msimbo wako wa serverless. Ili kujibu matukio ya IoT Hub, unaweza kuongeza kichocheo cha IoT Hub kwenye programu hii. Kichocheo hiki kinahitaji kuunganishwa na mkondo wa ujumbe unaotumwa kwa IoT Hub na kujibu ujumbe huo. Ili kupata mkondo huu wa ujumbe, kichocheo chako kinahitaji kuunganishwa na *endpoint inayolingana na Event Hub* ya IoT Hub.

IoT Hub inategemea huduma nyingine ya Azure inayoitwa Azure Event Hubs. Event Hubs ni huduma inayokuwezesha kutuma na kupokea ujumbe, IoT Hub inapanua hili kwa kuongeza vipengele kwa vifaa vya IoT. Njia unayounganisha kusoma ujumbe kutoka IoT Hub ni sawa na unavyotumia Event Hubs.

✅ Fanya utafiti: Soma muhtasari wa Event Hubs katika [hati za Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Je, vipengele vya msingi vinavyolinganishwa na IoT Hub vinafanana vipi?

Ili kifaa cha IoT kiunganishwe na IoT Hub, kinapaswa kutumia ufunguo wa siri unaohakikisha kuwa ni vifaa vilivyoruhusiwa pekee vinaweza kuunganishwa. Hali hiyo hiyo inatumika wakati wa kuunganishwa kusoma ujumbe, msimbo wako utahitaji kamba ya muunganisho inayojumuisha ufunguo wa siri, pamoja na maelezo ya IoT Hub.

> 💁 Kamba ya muunganisho ya msingi unayopata ina ruhusa za **iothubowner**, ambazo zinatoa ruhusa kamili kwa msimbo wowote unaoitumia kwenye IoT Hub. Kwa kawaida, unapaswa kuunganishwa na kiwango cha chini kabisa cha ruhusa kinachohitajika. Hili litafunikwa katika somo linalofuata.

Mara kichocheo chako kinapounganishwa, msimbo ndani ya kazi utaitwa kwa kila ujumbe unaotumwa kwa IoT Hub, bila kujali ni kifaa gani kilichotuma. Kichocheo kitapokea ujumbe kama parameter.

### Kazi - pata kamba ya muunganisho ya endpoint inayolingana na Event Hub

1. Kutoka kwenye terminal ya VS Code, endesha amri ifuatayo ili kupata kamba ya muunganisho kwa endpoint inayolingana na Event Hub ya IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Badilisha `<hub_name>` na jina ulilotumia kwa IoT Hub yako.

1. Katika VS Code, fungua faili `local.settings.json`. Ongeza thamani ifuatayo ya ziada ndani ya sehemu ya `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Badilisha `<connection string>` na thamani kutoka hatua ya awali. Utahitaji kuongeza koma baada ya mstari wa juu ili kufanya hii kuwa JSON halali.

### Kazi - unda kichocheo cha tukio

Sasa uko tayari kuunda kichocheo cha tukio.

1. Kutoka kwenye terminal ya VS Code, endesha amri ifuatayo kutoka ndani ya folda ya `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Hii inaunda Kazi mpya inayoitwa `iot-hub-trigger`. Kichocheo kitaunganishwa na endpoint inayolingana na Event Hub kwenye IoT Hub, kwa hivyo unaweza kutumia kichocheo cha Event Hub. Hakuna kichocheo maalum cha IoT Hub.

Hii itaunda folda ndani ya folda ya `soil-moisture-trigger` inayoitwa `iot-hub-trigger` ambayo ina kazi hii. Folda hii itakuwa na faili zifuatazo ndani yake:

* `__init__.py` - hii ni faili ya msimbo wa Python inayojumuisha kichocheo, kwa kutumia mkataba wa kawaida wa jina la faili za Python kugeuza folda hii kuwa moduli ya Python.

    Faili hii itakuwa na msimbo ufuatao:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Msingi wa kichocheo ni kazi ya `main`. Ni kazi hii inayoitwa na matukio kutoka IoT Hub. Kazi hii ina parameter inayoitwa `event` inayojumuisha `EventHubEvent`. Kila wakati ujumbe unapotumwa kwa IoT Hub, kazi hii inaitwa ikipitisha ujumbe huo kama `event`, pamoja na mali ambazo ni sawa na maelezo uliyoyaona katika somo la mwisho.

    Msingi wa kazi hii ni kuandika kumbukumbu ya tukio.

* `function.json` - hii inajumuisha usanidi wa kichocheo. Usanidi mkuu uko katika sehemu inayoitwa `bindings`. Binding ni neno linalomaanisha muunganisho kati ya Azure Functions na huduma nyingine za Azure. Kazi hii ina binding ya pembejeo kwa Event Hub - inaunganishwa na Event Hub na kupokea data.

    > 💁 Unaweza pia kuwa na binding za matokeo ili matokeo ya kazi yatumwe kwa huduma nyingine. Kwa mfano, unaweza kuongeza binding ya matokeo kwa hifadhidata na kurudisha tukio la IoT Hub kutoka kwa kazi, na litaingizwa moja kwa moja kwenye hifadhidata.

    ✅ Fanya utafiti: Soma kuhusu bindings katika [hati za dhana za triggers na bindings za Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Sehemu ya `bindings` inajumuisha usanidi wa binding. Thamani za kuvutia ni:

  * `"type": "eventHubTrigger"` - hii inaiambia kazi kuwa inahitaji kusikiliza matukio kutoka Event Hub
  * `"name": "events"` - hii ni jina la parameter ya kutumia kwa matukio ya Event Hub. Hii inalingana na jina la parameter katika kazi ya `main` kwenye msimbo wa Python.
  * `"direction": "in"` - hii ni binding ya pembejeo, data kutoka Event Hub inaingia kwenye kazi
  * `"connection": ""` - hii inafafanua jina la mpangilio wa kusoma kamba ya muunganisho. Wakati wa kuendesha kwa ndani, hii itasoma mpangilio huu kutoka faili ya `local.settings.json`.

    > 💁 Kamba ya muunganisho haiwezi kuhifadhiwa kwenye faili ya `function.json`, inapaswa kusomwa kutoka kwa mipangilio. Hii ni kuzuia kufichua kamba yako ya muunganisho kwa bahati mbaya.

1. Kutokana na [hitilafu katika kiolezo cha Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250), faili ya `function.json` ina thamani isiyo sahihi kwa uwanja wa `cardinality`. Sasisha uwanja huu kutoka `many` hadi `one`:

    ```json
    "cardinality": "one",
    ```

1. Sasisha thamani ya `"connection"` katika faili ya `function.json` ili kuelekeza kwenye thamani mpya uliyoongeza kwenye faili ya `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Kumbuka - hii inahitaji kuelekeza kwenye mpangilio, si kuwa na kamba halisi ya muunganisho.

1. Kamba ya muunganisho inajumuisha thamani ya `eventHubName`, kwa hivyo thamani ya hii katika faili ya `function.json` inahitaji kufutwa. Sasisha thamani hii kuwa kamba tupu:

    ```json
    "eventHubName": "",
    ```

### Kazi - endesha kichocheo cha tukio

1. Hakikisha huendeshi mfuatiliaji wa matukio ya IoT Hub. Ikiwa hii inaendesha wakati huo huo na programu ya Functions, programu ya Functions haitakuwa na uwezo wa kuunganishwa na kutumia matukio.

    > 💁 Programu nyingi zinaweza kuunganishwa na endpoints za IoT Hub kwa kutumia *vikundi vya watumiaji* tofauti. Haya yatafunikwa katika somo la baadaye.

1. Ili kuendesha programu ya Functions, endesha amri ifuatayo kutoka kwenye terminal ya VS Code:

    ```sh
    func start
    ```

    Programu ya Functions itaanza, na itagundua kazi ya `iot-hub-trigger`. Kisha itashughulikia matukio yoyote ambayo tayari yametumwa kwa IoT Hub katika siku iliyopita.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Kila wito kwa kazi utazungukwa na block ya `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` kwenye matokeo, kwa hivyo unaweza kuona ni ujumbe ngapi zilishughulikiwa katika kila wito wa kazi.

1. Hakikisha kifaa chako cha IoT kinafanya kazi. Utaona ujumbe mpya wa unyevu wa udongo ukionekana kwenye programu ya Functions.

1. Zima na uanzishe tena programu ya Functions. Utaona kuwa haitashughulikia ujumbe wa awali tena, itashughulikia tu ujumbe mpya.

> 💁 VS Code pia inasaidia kufuatilia hitilafu kwenye Functions zako. Unaweza kuweka sehemu za kusimamisha kwa kubofya kwenye mpaka karibu na mwanzo wa kila mstari wa msimbo, au kuweka mshale kwenye mstari wa msimbo na kuchagua *Run -> Toggle breakpoint*, au kubonyeza `F9`. Unaweza kuzindua kifuatiliaji hitilafu kwa kuchagua *Run -> Start debugging*, kubonyeza `F5`, au kuchagua paneli ya *Run and debug* na kuchagua kitufe cha **Start debugging**. Kwa kufanya hivi unaweza kuona maelezo ya matukio yanayoshughulikiwa.

#### Utatuzi wa matatizo

* Ikiwa unapata hitilafu ifuatayo:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Hakikisha Azurite inaendesha na umeweka `AzureWebJobsStorage` katika faili ya `local.settings.json` kuwa `UseDevelopmentStorage=true`.

* Ikiwa unapata hitilafu ifuatayo:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Hakikisha kuwa umeweka `cardinality` katika faili ya `function.json` kuwa `one`.

* Ikiwa unapata hitilafu ifuatayo:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Hakikisha kuwa umeweka `eventHubName` katika faili ya `function.json` kuwa kamba tupu.

## Tuma maombi ya njia ya moja kwa moja kutoka kwa msimbo wa serverless

Hadi sasa programu yako ya Functions inasikiliza ujumbe kutoka IoT Hub kwa kutumia endpoint inayolingana na Event Hub. Sasa unahitaji kutuma amri kwa kifaa cha IoT. Hii inafanywa kwa kutumia muunganisho tofauti kwa IoT Hub kupitia *Registry Manager*. Registry Manager ni zana inayokuwezesha kuona ni vifaa gani vimesajiliwa na IoT Hub, na kuwasiliana na vifaa hivyo kwa kutuma ujumbe kutoka wingu kwenda kifaa, maombi ya njia ya moja kwa moja au kusasisha "device twin". Pia unaweza kuitumia kusajili, kusasisha au kufuta vifaa vya IoT kutoka IoT Hub.

Ili kuunganishwa na Registry Manager, unahitaji kamba ya muunganisho.

### Kazi - pata kamba ya muunganisho ya Registry Manager

1. Ili kupata kamba ya muunganisho, endesha amri ifuatayo:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Badilisha `<hub_name>` na jina ulilotumia kwa IoT Hub yako.

    Kamba ya muunganisho inaombwa kwa sera ya *ServiceConnect* kwa kutumia parameter `--policy-name service`. Unapoomba kamba ya muunganisho, unaweza kubainisha ni ruhusa gani kamba hiyo itaruhusu. Sera ya ServiceConnect inaruhusu msimbo wako kuunganishwa na kutuma ujumbe kwa vifaa vya IoT.

    ✅ Fanya utafiti: Soma kuhusu sera tofauti katika [hati za ruhusa za IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. Katika VS Code, fungua faili ya `local.settings.json`. Ongeza thamani ifuatayo ya ziada ndani ya sehemu ya `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Badilisha `<connection string>` na thamani kutoka hatua ya awali. Utahitaji kuongeza koma baada ya mstari wa juu ili kufanya hii kuwa JSON halali.

### Kazi - tuma ombi la njia ya moja kwa moja kwa kifaa

1. SDK ya Registry Manager inapatikana kupitia kifurushi cha Pip. Ongeza mstari ufuatao kwenye faili ya `requirements.txt` ili kuongeza utegemezi wa kifurushi hiki:

    ```sh
    azure-iot-hub
    ```

1. Hakikisha terminal ya VS Code imeamilisha mazingira ya kawaida, na endesha amri ifuatayo kusakinisha vifurushi vya Pip:

    ```sh
    pip install -r requirements.txt
    ```

1. Ongeza uingizaji ufuatao kwenye faili ya `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Hii inaingiza maktaba za mfumo, pamoja na maktaba za kuingiliana na Registry Manager na kutuma maombi ya njia ya moja kwa moja.

1. Ondoa msimbo kutoka ndani ya njia ya `main`, lakini weka njia yenyewe.

1. Katika njia ya `main`, ongeza msimbo ufuatao:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Msimbo huu unatoa mwili wa tukio ambalo lina ujumbe wa JSON uliotumwa na kifaa cha IoT.

    Kisha unapata kitambulisho cha kifaa kutoka kwa maelezo yaliyopitishwa na ujumbe. Mwili wa tukio unajumuisha ujumbe uliotumwa kama telemetry, wakati kamusi ya `iothub_metadata` inajumuisha mali zilizowekwa na IoT Hub kama vile kitambulisho cha kifaa cha mtumaji, na wakati ujumbe ulipotumwa.

    Taarifa hii kisha inaandikwa kwenye kumbukumbu. Utaona kumbukumbu hii kwenye terminal unapokimbia programu ya Function kwa ndani.

1. Chini ya hii, ongeza msimbo ufuatao:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Msimbo huu unapata unyevu wa udongo kutoka kwa ujumbe. Kisha unakagua unyevu wa udongo, na kulingana na thamani, unaunda darasa la msaidizi kwa ombi la njia ya moja kwa moja kwa njia ya `relay_on` au `relay_off`. Ombi la njia halihitaji mzigo wa data, kwa hivyo hati tupu ya JSON inatumwa.

1. Chini ya hii ongeza msimbo ufuatao:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Maelezo haya yanapakia `REGISTRY_MANAGER_CONNECTION_STRING` kutoka kwenye faili ya `local.settings.json`. Thamani zilizomo kwenye faili hii zinapatikana kama vigezo vya mazingira, na zinaweza kusomwa kwa kutumia kazi ya `os.environ`, kazi inayorejesha kamusi ya vigezo vyote vya mazingira.

> 💁 Wakati maelezo haya yanapowekwa kwenye wingu, thamani zilizomo kwenye faili ya `local.settings.json` zitawekwa kama *Application Settings*, na zinaweza kusomwa kutoka kwenye vigezo vya mazingira.

Kisha, maelezo haya yanaunda mfano wa darasa la msaidizi la Registry Manager kwa kutumia connection string.

1. Chini ya haya ongeza msimbo ufuatao:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Msimbo huu unamwambia Registry Manager kutuma ombi la njia ya moja kwa moja kwa kifaa kilichotuma telemetry.

    > 💁 Katika matoleo ya programu uliyotengeneza kwenye masomo ya awali kwa kutumia MQTT, amri za kudhibiti relay zilitumwa kwa vifaa vyote. Msimbo ulidhani ungekuwa na kifaa kimoja tu. Toleo hili la msimbo linatuma ombi la njia moja kwa moja kwa kifaa kimoja, hivyo linaweza kufanya kazi ikiwa una seti nyingi za sensa za unyevu wa udongo na relay, likituma ombi sahihi kwa kifaa sahihi.

1. Endesha programu ya Functions, na hakikisha kifaa chako cha IoT kinatuma data. Utaona ujumbe ukichakatwa na maombi ya njia moja kwa moja yakitumwa. Hamisha sensa ya unyevu wa udongo ndani na nje ya udongo ili kuona thamani zikibadilika na relay kuwashwa na kuzimwa.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Weka msimbo wako wa serverless kwenye wingu

Sasa msimbo wako unafanya kazi kwa ndani, hatua inayofuata ni kuweka programu ya Functions kwenye wingu.

### Kazi - unda rasilimali za wingu

Programu yako ya Functions inahitaji kuwekwa kwenye rasilimali ya Functions App ndani ya Azure, ikiishi ndani ya Resource Group uliyounda kwa ajili ya IoT Hub yako. Pia utahitaji akaunti ya hifadhi iliyoundwa ndani ya Azure ili kuchukua nafasi ya emulator unayotumia kwa ndani.

1. Endesha amri ifuatayo kuunda akaunti ya hifadhi:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Badilisha `<storage_name>` na jina la akaunti yako ya hifadhi. Jina hili linahitaji kuwa la kipekee kimataifa kwani linakuwa sehemu ya URL inayotumika kufikia akaunti ya hifadhi. Unaweza kutumia herufi ndogo na namba tu kwa jina hili, hakuna wahusika wengine, na linapunguzwa hadi herufi 24. Tumia kitu kama `sms` na ongeza kitambulisho cha kipekee mwishoni, kama maneno ya nasibu au jina lako.

    Chaguo la `--sku Standard_LRS` linachagua kiwango cha bei, likichagua akaunti ya gharama ya chini ya matumizi ya jumla. Hakuna kiwango cha bure cha hifadhi, na unalipa kwa kile unachotumia. Gharama ni za chini, na hifadhi ya gharama kubwa zaidi ikiwa chini ya US$0.05 kwa mwezi kwa gigabyte moja iliyohifadhiwa.

    ✅ Soma zaidi kuhusu bei kwenye [ukurasa wa bei wa Azure Storage Account](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Endesha amri ifuatayo kuunda Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Badilisha `<location>` na eneo ulilotumia wakati wa kuunda Resource Group kwenye somo la awali.

    Badilisha `<storage_name>` na jina la akaunti ya hifadhi uliyounda kwenye hatua ya awali.

    Badilisha `<functions_app_name>` na jina la kipekee kwa Functions App yako. Jina hili linahitaji kuwa la kipekee kimataifa kwani linakuwa sehemu ya URL inayotumika kufikia Functions App. Tumia kitu kama `soil-moisture-sensor-` na ongeza kitambulisho cha kipekee mwishoni, kama maneno ya nasibu au jina lako.

    Chaguo la `--functions-version 3` linaweka toleo la Azure Functions la kutumia. Toleo la 3 ni toleo la hivi karibuni.

    Chaguo la `--os-type Linux` linaambia runtime ya Functions kutumia Linux kama OS ya kuendesha hizi functions. Functions zinaweza kuendeshwa kwenye Linux au Windows, kulingana na lugha ya programu inayotumika. Programu za Python zinasaidiwa tu kwenye Linux.

### Kazi - pakia mipangilio ya programu yako

Wakati ulipokuwa unatengeneza Functions App yako, ulihifadhi mipangilio fulani kwenye faili ya `local.settings.json` kwa ajili ya connection strings za IoT Hub yako. Hizi zinahitaji kuandikwa kwenye Application Settings ndani ya Function App yako kwenye Azure ili ziweze kutumika na msimbo wako.

> 🎓 Faili ya `local.settings.json` ni kwa ajili ya mipangilio ya maendeleo ya ndani tu, na haipaswi kuingizwa kwenye udhibiti wa msimbo wa chanzo, kama GitHub. Wakati imewekwa kwenye wingu, Application Settings zinatumika. Application Settings ni jozi za funguo/thamani zinazohifadhiwa kwenye wingu na zinasomwa kutoka kwenye vigezo vya mazingira aidha kwenye msimbo wako au na runtime wakati wa kuunganisha msimbo wako na IoT Hub.

1. Endesha amri ifuatayo kuweka mipangilio ya `IOT_HUB_CONNECTION_STRING` kwenye Application Settings za Functions App:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Badilisha `<functions_app_name>` na jina ulilotumia kwa Functions App yako.

    Badilisha `<connection string>` na thamani ya `IOT_HUB_CONNECTION_STRING` kutoka kwenye faili yako ya `local.settings.json`.

1. Rudia hatua ya juu, lakini weka thamani ya `REGISTRY_MANAGER_CONNECTION_STRING` kwa thamani inayolingana kutoka kwenye faili yako ya `local.settings.json`.

Wakati unaendesha amri hizi, zitaonyesha pia orodha ya Application Settings zote za function app. Unaweza kutumia hii kuangalia kama thamani zako zimewekwa kwa usahihi.

> 💁 Utaona thamani tayari imewekwa kwa `AzureWebJobsStorage`. Kwenye faili yako ya `local.settings.json`, hii ilikuwa imewekwa kwa thamani ya kutumia emulator ya hifadhi ya ndani. Wakati uliunda Functions App, ulipitisha akaunti ya hifadhi kama parameter, na hii imewekwa kiotomatiki kwenye mipangilio hii.

### Kazi - weka Functions App yako kwenye wingu

Sasa Functions App iko tayari, msimbo wako unaweza kuwekwa.

1. Endesha amri ifuatayo kutoka kwenye terminal ya VS Code ili kuchapisha Functions App yako:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Badilisha `<functions_app_name>` na jina ulilotumia kwa Functions App yako.

Msimbo utapakizwa na kutumwa kwenye Functions App, ambapo utawekwa na kuanza. Kutakuwa na matokeo mengi ya console, yakimalizika na uthibitisho wa uwekaji na orodha ya functions zilizowekwa. Katika kesi hii orodha itakuwa na trigger pekee.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Hakikisha kifaa chako cha IoT kinafanya kazi. Badilisha viwango vya unyevu kwa kurekebisha unyevu wa udongo, au kuhamisha sensa ndani na nje ya udongo. Utaona relay ikiwashwa na kuzimwa kadri unyevu wa udongo unavyobadilika.

---

## 🚀 Changamoto

Katika somo la awali, ulisimamia muda wa relay kwa kujiondoa kutoka kwa ujumbe wa MQTT wakati relay ilikuwa imewashwa, na kwa muda mfupi baada ya kuzimwa. Huwezi kutumia njia hii hapa - huwezi kujiondoa kwenye trigger ya IoT Hub yako.

Fikiria njia tofauti unazoweza kutumia kushughulikia hili kwenye Functions App yako.

## Jaribio la baada ya somo

[Jaribio la baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Mapitio na Kujisomea

* Soma kuhusu serverless computing kwenye [ukurasa wa Serverless Computing kwenye Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Soma kuhusu kutumia serverless ndani ya Azure ikiwa ni pamoja na mifano zaidi kwenye [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Jifunze zaidi kuhusu Azure Functions kwenye [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions)

## Kazi

[Ongeza udhibiti wa relay wa mwongozo](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.