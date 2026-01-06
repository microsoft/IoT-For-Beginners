<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-28T11:05:44+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "sk"
}
-->
# Migrujte logiku svojej aplikácie do cloudu

![Prehľad tejto lekcie v sketchnote](../../../../../translated_images/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.sk.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

Táto lekcia bola súčasťou [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) od [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Ovládajte svoje IoT zariadenie pomocou serverless kódu](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Úvod

V poslednej lekcii ste sa naučili, ako pripojiť monitorovanie vlhkosti pôdy rastlín a ovládanie relé k cloudovej IoT službe. Ďalším krokom je presunúť serverový kód, ktorý riadi načasovanie relé, do cloudu. V tejto lekcii sa naučíte, ako to urobiť pomocou serverless funkcií.

V tejto lekcii sa budeme venovať:

* [Čo je serverless?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Vytvorenie serverless aplikácie](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Vytvorenie triggeru udalostí IoT Hubu](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Odosielanie požiadaviek na priame metódy zo serverless kódu](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Nasadenie serverless kódu do cloudu](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Čo je serverless?

Serverless, alebo serverless computing, zahŕňa vytváranie malých blokov kódu, ktoré sa spúšťajú v cloude ako reakcia na rôzne typy udalostí. Keď sa udalosť stane, váš kód sa spustí a dostane údaje o udalosti. Tieto udalosti môžu pochádzať z rôznych zdrojov, vrátane webových požiadaviek, správ v rade, zmien údajov v databáze alebo správ odoslaných IoT zariadeniami do IoT služby.

![Udalosti odosielané z IoT služby do serverless služby, všetky spracované naraz viacerými funkciami](../../../../../translated_images/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.sk.png)

> 💁 Ak ste už používali databázové triggery, môžete si to predstaviť ako podobný koncept, kód spúšťaný udalosťou, ako je napríklad vloženie riadku.

![Keď sa naraz odošle veľa udalostí, serverless služba sa škáluje tak, aby ich všetky spracovala naraz](../../../../../translated_images/serverless-scaling.f8c769adf0413fd1.sk.png)

Váš kód sa spúšťa iba vtedy, keď sa udalosť stane, inak nie je aktívny. Udalosť sa stane, váš kód sa načíta a spustí. To robí serverless veľmi škálovateľným - ak sa naraz stane veľa udalostí, poskytovateľ cloudu môže spustiť vašu funkciu toľkokrát, koľko je potrebné, na dostupných serveroch. Nevýhodou je, že ak potrebujete zdieľať informácie medzi udalosťami, musíte ich uložiť niekde, napríklad do databázy, namiesto ukladania do pamäte.

Váš kód je napísaný ako funkcia, ktorá prijíma podrobnosti o udalosti ako parameter. Na písanie týchto serverless funkcií môžete použiť širokú škálu programovacích jazykov.

> 🎓 Serverless sa tiež označuje ako Funkcie ako služba (FaaS), pretože každý trigger udalosti je implementovaný ako funkcia v kóde.

Napriek názvu serverless skutočne používa servery. Názov je odvodený od toho, že ako vývojár sa nestaráte o servery potrebné na spustenie vášho kódu, ale len o to, že váš kód sa spustí ako reakcia na udalosť. Poskytovateľ cloudu má serverless *runtime*, ktorý spravuje prideľovanie serverov, sieť, úložisko, CPU, pamäť a všetko ostatné potrebné na spustenie vášho kódu. Tento model znamená, že neplatíte za server, ale za čas, počas ktorého váš kód beží, a za množstvo použitej pamäte.

> 💰 Serverless je jeden z najlacnejších spôsobov, ako spustiť kód v cloude. Napríklad, v čase písania tohto textu, jeden poskytovateľ cloudu umožňuje všetkým vašim serverless funkciám vykonať kombinovane 1 000 000 krát mesačne predtým, než vám začne účtovať, a potom účtuje 0,20 USD za každých 1 000 000 vykonaní. Keď váš kód nebeží, neplatíte.

Ako IoT vývojár je serverless model ideálny. Môžete napísať funkciu, ktorá sa spustí ako reakcia na správy odoslané z akéhokoľvek IoT zariadenia pripojeného k vašej cloudovej IoT službe. Váš kód spracuje všetky odoslané správy, ale bude bežať iba vtedy, keď to bude potrebné.

✅ Pozrite sa späť na kód, ktorý ste napísali ako serverový kód počúvajúci správy cez MQTT. Ako by mohol tento kód bežať v cloude pomocou serverless? Ako si myslíte, že by sa kód mohol zmeniť, aby podporoval serverless computing?

> 💁 Serverless model sa presúva aj do iných cloudových služieb okrem spúšťania kódu. Napríklad serverless databázy sú dostupné v cloude s cenovým modelom serverless, kde platíte za každú požiadavku na databázu, ako je dotaz alebo vloženie, zvyčajne na základe toho, koľko práce je potrebné na obsluhu požiadavky. Napríklad jednoduchý výber jedného riadku podľa primárneho kľúča bude stáť menej ako komplikovaná operácia spájajúca mnoho tabuliek a vracajúca tisíce riadkov.

## Vytvorenie serverless aplikácie

Serverless computing služba od Microsoftu sa nazýva Azure Functions.

![Logo Azure Functions](../../../../../translated_images/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.sk.png)

Krátke video nižšie poskytuje prehľad Azure Functions.

[![Prehľad Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Kliknite na obrázok vyššie pre sledovanie videa.

✅ Venujte chvíľu výskumu a prečítajte si prehľad Azure Functions v [dokumentácii Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Na písanie Azure Functions začnete s aplikáciou Azure Functions v jazyku podľa vášho výberu. Azure Functions podporuje Python, JavaScript, TypeScript, C#, F#, Java a Powershell. V tejto lekcii sa naučíte, ako napísať aplikáciu Azure Functions v Pythone.

> 💁 Azure Functions tiež podporuje vlastné handlery, takže môžete písať svoje funkcie v akomkoľvek jazyku, ktorý podporuje HTTP požiadavky, vrátane starších jazykov, ako je COBOL.

Aplikácie funkcií pozostávajú z jednej alebo viacerých *triggerov* - funkcií, ktoré reagujú na udalosti. Môžete mať viacero triggerov v jednej aplikácii funkcií, ktoré zdieľajú spoločnú konfiguráciu. Napríklad v konfiguračnom súbore vašej aplikácie funkcií môžete mať detaily pripojenia k IoT Hubu a všetky funkcie v aplikácii môžu toto pripojenie použiť na počúvanie udalostí.

### Úloha - inštalácia nástrojov Azure Functions

> V čase písania tohto textu nástroje Azure Functions nie sú plne funkčné na Apple Silicon s projektmi v Pythone. Budete musieť použiť Mac s Intel procesorom, Windows PC alebo Linux PC.

Jednou z výhod Azure Functions je, že ich môžete spustiť lokálne. Rovnaký runtime, ktorý sa používa v cloude, môže bežať na vašom počítači, čo vám umožňuje písať kód, ktorý reaguje na IoT správy, a spustiť ho lokálne. Dokonca môžete debugovať svoj kód počas spracovania udalostí. Keď budete spokojní so svojím kódom, môžete ho nasadiť do cloudu.

Nástroje Azure Functions sú dostupné ako CLI, známe ako Azure Functions Core Tools.

1. Nainštalujte Azure Functions Core Tools podľa pokynov v [dokumentácii Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Nainštalujte rozšírenie Azure Functions pre VS Code. Toto rozšírenie poskytuje podporu pre vytváranie, debugovanie a nasadzovanie Azure Functions. Pozrite si [dokumentáciu rozšírenia Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) pre pokyny na inštaláciu tohto rozšírenia vo VS Code.

Keď nasadíte svoju aplikáciu Azure Functions do cloudu, bude potrebovať malé množstvo cloudového úložiska na ukladanie vecí, ako sú aplikačné súbory a log súbory. Keď spustíte svoju aplikáciu funkcií lokálne, stále sa musíte pripojiť k cloudovému úložisku, ale namiesto použitia skutočného cloudového úložiska môžete použiť emulátor úložiska nazývaný [Azurite](https://github.com/Azure/Azurite). Tento emulátor beží lokálne, ale správa sa ako cloudové úložisko.

> 🎓 V Azure je úložisko, ktoré Azure Functions používa, Azure Storage Account. Tieto účty môžu ukladať súbory, blob, údaje v tabuľkách alebo údaje v radoch. Jeden úložný účet môžete zdieľať medzi mnohými aplikáciami, ako je aplikácia funkcií a webová aplikácia.

1. Azurite je aplikácia v Node.js, takže budete musieť nainštalovať Node.js. Návod na stiahnutie a inštaláciu nájdete na [webovej stránke Node.js](https://nodejs.org/). Ak používate Mac, môžete ho tiež nainštalovať cez [Homebrew](https://formulae.brew.sh/formula/node).

1. Nainštalujte Azurite pomocou nasledujúceho príkazu (`npm` je nástroj, ktorý sa nainštaluje spolu s Node.js):

    ```sh
    npm install -g azurite
    ```

1. Vytvorte priečinok nazvaný `azurite` pre Azurite na ukladanie údajov:

    ```sh
    mkdir azurite
    ```

1. Spustite Azurite a odovzdajte mu tento nový priečinok:

    ```sh
    azurite --location azurite
    ```

    Emulátor úložiska Azurite sa spustí a bude pripravený na pripojenie lokálneho runtime funkcií.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Úloha - vytvorenie projektu Azure Functions

CLI Azure Functions môže byť použité na vytvorenie novej aplikácie funkcií.

1. Vytvorte priečinok pre svoju aplikáciu funkcií a prejdite do neho. Nazvite ho `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Vytvorte virtuálne prostredie Pythonu v tomto priečinku:

    ```sh
    python3 -m venv .venv
    ```

1. Aktivujte virtuálne prostredie:

    * Na Windows:
        * Ak používate Command Prompt alebo Command Prompt cez Windows Terminal, spustite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ak používate PowerShell, spustite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Na macOS alebo Linux spustite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Tieto príkazy by mali byť spustené z rovnakého miesta, kde ste spustili príkaz na vytvorenie virtuálneho prostredia. Nikdy nebudete musieť prejsť do priečinka `.venv`, vždy by ste mali spustiť príkaz na aktiváciu a akékoľvek príkazy na inštaláciu balíkov alebo spustenie kódu z priečinka, kde ste vytvorili virtuálne prostredie.

1. Spustite nasledujúci príkaz na vytvorenie aplikácie funkcií v tomto priečinku:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Tým sa v aktuálnom priečinku vytvoria tri súbory:

    * `host.json` - tento JSON dokument obsahuje nastavenia pre vašu aplikáciu funkcií. Nebudete musieť upravovať tieto nastavenia.
    * `local.settings.json` - tento JSON dokument obsahuje nastavenia, ktoré vaša aplikácia používa pri lokálnom spustení, ako sú reťazce pripojenia k IoT Hubu. Tieto nastavenia sú iba lokálne a nemali by byť pridané do zdrojového kódu. Keď aplikáciu nasadíte do cloudu, tieto nastavenia sa nenasadia, namiesto toho sa vaše nastavenia načítajú z aplikačných nastavení. To bude pokryté neskôr v tejto lekcii.
    * `requirements.txt` - toto je [Pip requirements file](https://pip.pypa.io/en/stable/user_guide/#requirements-files), ktorý obsahuje Pip balíky potrebné na spustenie vašej aplikácie funkcií.

1. Súbor `local.settings.json` má nastavenie pre úložný účet, ktorý aplikácia funkcií použije. Toto nastavenie je predvolene prázdne, takže ho treba nastaviť. Na pripojenie k lokálnemu emulátoru úložiska Azurite nastavte túto hodnotu na:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Nainštalujte potrebné Pip balíky pomocou súboru requirements:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Potrebné Pip balíky musia byť v tomto súbore, aby runtime aplikácie funkcií pri nasadení do cloudu mohol zabezpečiť inštaláciu správnych balíkov.

1. Na otestovanie, či všetko funguje správne, môžete spustiť runtime funkcií. Spustite nasledujúci príkaz:

    ```sh
    func start
    ```

    Uvidíte, že runtime sa spustí a oznámi, že nenašiel žiadne funkcie (triggery).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Ak dostanete upozornenie na firewall, povoľte prístup, pretože aplikácia `func` potrebuje mať možnosť čítať a zapisovať do vašej siete.
> ⚠️ Ak používate macOS, v výstupe sa môžu zobraziť varovania:
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
> Tieto varovania môžete ignorovať, pokiaľ sa aplikácia Functions správne spustí a zobrazí zoznam bežiacich funkcií. Ako je uvedené v [tomto vlákne na Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), tieto varovania nie sú podstatné.

1. Zastavte aplikáciu Functions stlačením `ctrl+c`.

1. Otvorte aktuálny priečinok vo VS Code, buď spustením VS Code a následným otvorením tohto priečinka, alebo spustením nasledujúceho príkazu:

    ```sh
    code .
    ```

    VS Code rozpozná váš projekt Functions a zobrazí upozornenie:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Upozornenie](../../../../../translated_images/vscode-azure-functions-init-notification.bd19b49229963edb.sk.png)

    V tomto upozornení vyberte **Áno**.

1. Uistite sa, že vo VS Code termináli beží Python virtuálne prostredie. Ak je to potrebné, ukončite ho a znova spustite.

## Vytvorenie triggera pre udalosti IoT Hubu

Aplikácia Functions je obal pre váš serverless kód. Na reagovanie na udalosti IoT Hubu môžete do tejto aplikácie pridať trigger pre IoT Hub. Tento trigger sa musí pripojiť k prúdu správ, ktoré sú odosielané do IoT Hubu, a reagovať na ne. Aby ste získali tento prúd správ, váš trigger sa musí pripojiť k *event hub kompatibilnému endpointu* IoT Hubu.

IoT Hub je založený na inej Azure službe s názvom Azure Event Hubs. Event Hubs umožňuje odosielať a prijímať správy, pričom IoT Hub pridáva funkcie špecifické pre IoT zariadenia. Spôsob pripojenia na čítanie správ z IoT Hubu je rovnaký ako pri použití Event Hubs.

✅ Urobte si prieskum: Prečítajte si prehľad Event Hubs v [dokumentácii Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Ako sa základné funkcie porovnávajú s IoT Hubom?

Aby sa IoT zariadenie mohlo pripojiť k IoT Hubu, musí použiť tajný kľúč, ktorý zabezpečí, že sa môžu pripojiť iba povolené zariadenia. To isté platí pri pripojení na čítanie správ – váš kód bude potrebovať pripojovací reťazec obsahujúci tajný kľúč spolu s detailmi o IoT Hube.

> 💁 Predvolený pripojovací reťazec, ktorý získate, má oprávnenia **iothubowner**, čo umožňuje akémukoľvek kódu, ktorý ho používa, plný prístup k IoT Hubu. Ideálne by ste sa mali pripojiť s najnižšou úrovňou potrebných oprávnení. Toto bude pokryté v ďalšej lekcii.

Keď sa váš trigger pripojí, kód vo funkcii sa spustí pre každú správu odoslanú do IoT Hubu, bez ohľadu na to, ktoré zariadenie ju odoslalo. Trigger dostane správu ako parameter.

### Úloha – získanie pripojovacieho reťazca pre event hub kompatibilný endpoint

1. V termináli VS Code spustite nasledujúci príkaz na získanie pripojovacieho reťazca pre event hub kompatibilný endpoint IoT Hubu:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom, ktorý ste použili pre váš IoT Hub.

1. Vo VS Code otvorte súbor `local.settings.json`. Pridajte nasledujúcu hodnotu do sekcie `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Nahraďte `<connection string>` hodnotou z predchádzajúceho kroku. Aby bol JSON platný, budete musieť pridať čiarku za predchádzajúci riadok.

### Úloha – vytvorenie triggera pre udalosti

Teraz ste pripravení vytvoriť trigger pre udalosti.

1. V termináli VS Code spustite nasledujúci príkaz z priečinka `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Tento príkaz vytvorí novú funkciu s názvom `iot-hub-trigger`. Trigger sa pripojí k event hub kompatibilnému endpointu IoT Hubu, takže môžete použiť trigger pre Event Hub. Neexistuje špecifický trigger pre IoT Hub.

Týmto sa v priečinku `soil-moisture-trigger` vytvorí priečinok s názvom `iot-hub-trigger`, ktorý obsahuje túto funkciu. Tento priečinok bude obsahovať nasledujúce súbory:

* `__init__.py` – Python súbor, ktorý obsahuje trigger, pričom používa štandardný názov súboru na označenie priečinka ako Python modulu.

    Tento súbor bude obsahovať nasledujúci kód:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Jadro triggera je funkcia `main`. Táto funkcia sa volá s udalosťami z IoT Hubu. Funkcia má parameter `event`, ktorý obsahuje `EventHubEvent`. Pri každej správe odoslanej do IoT Hubu sa táto funkcia zavolá a odovzdá správu ako `event` spolu s vlastnosťami, ktoré sú rovnaké ako anotácie, ktoré ste videli v predchádzajúcej lekcii.

    Jadro tejto funkcie zapisuje udalosť do logu.

* `function.json` – obsahuje konfiguráciu pre trigger. Hlavná konfigurácia je v sekcii `bindings`. Binding je termín pre spojenie medzi Azure Functions a inými Azure službami. Táto funkcia má vstupný binding na event hub – pripája sa na event hub a prijíma dáta.

    > 💁 Môžete mať aj výstupné bindingy, takže výstup funkcie sa odošle do inej služby. Napríklad môžete pridať výstupný binding do databázy a vrátiť udalosť IoT Hubu z funkcie, ktorá sa automaticky vloží do databázy.

    ✅ Urobte si prieskum: Prečítajte si o bindingoch v [dokumentácii o triggeroch a bindingoch Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Sekcia `bindings` obsahuje konfiguráciu pre binding. Zaujímavé hodnoty sú:

  * `"type": "eventHubTrigger"` – určuje, že funkcia má počúvať udalosti z Event Hubu
  * `"name": "events"` – názov parametra pre udalosti Event Hubu. Tento názov zodpovedá názvu parametra vo funkcii `main` v Python kóde.
  * `"direction": "in"` – ide o vstupný binding, dáta z Event Hubu prichádzajú do funkcie
  * `"connection": ""` – definuje názov nastavenia, z ktorého sa číta pripojovací reťazec. Pri lokálnom spustení sa toto nastavenie číta zo súboru `local.settings.json`.

    > 💁 Pripojovací reťazec nemôže byť uložený v súbore `function.json`, musí byť čítaný z nastavení. Toto je na ochranu pred náhodným zverejnením pripojovacieho reťazca.

1. Kvôli [chybe v šablóne Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250) má `function.json` nesprávnu hodnotu pre pole `cardinality`. Aktualizujte toto pole z hodnoty `many` na `one`:

    ```json
    "cardinality": "one",
    ```

1. Aktualizujte hodnotu `"connection"` v súbore `function.json`, aby ukazovala na novú hodnotu, ktorú ste pridali do súboru `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Pamätajte – toto musí ukazovať na nastavenie, nie obsahovať samotný pripojovací reťazec.

1. Pripojovací reťazec obsahuje hodnotu `eventHubName`, takže hodnota pre toto pole v súbore `function.json` musí byť vymazaná. Aktualizujte túto hodnotu na prázdny reťazec:

    ```json
    "eventHubName": "",
    ```

### Úloha – spustenie triggera pre udalosti

1. Uistite sa, že nemonitorujete udalosti IoT Hubu. Ak je tento monitor spustený súčasne s aplikáciou Functions, aplikácia Functions sa nebude môcť pripojiť a spracovať udalosti.

    > 💁 Viacero aplikácií sa môže pripojiť k endpointom IoT Hubu pomocou rôznych *consumer groups*. Tieto budú pokryté v neskoršej lekcii.

1. Na spustenie aplikácie Functions spustite nasledujúci príkaz z terminálu VS Code:

    ```sh
    func start
    ```

    Aplikácia Functions sa spustí, objaví funkciu `iot-hub-trigger` a začne spracovávať všetky udalosti, ktoré boli odoslané do IoT Hubu za posledný deň.

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

    Každé volanie funkcie bude obklopené blokmi `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` vo výstupe, takže uvidíte, koľko správ bolo spracovaných pri každom volaní funkcie.

1. Uistite sa, že vaše IoT zariadenie beží. V aplikácii Functions sa začnú objavovať nové správy o vlhkosti pôdy.

1. Zastavte a znova spustite aplikáciu Functions. Uvidíte, že predchádzajúce správy už nebudú spracované, spracujú sa iba nové správy.

> 💁 VS Code podporuje aj ladenie vašich funkcií. Môžete nastaviť breakpointy kliknutím na okraj pri začiatku každého riadku kódu, umiestnením kurzora na riadok kódu a výberom *Run -> Toggle breakpoint*, alebo stlačením `F9`. Debugger môžete spustiť výberom *Run -> Start debugging*, stlačením `F5`, alebo výberom panela *Run and debug* a kliknutím na tlačidlo **Start debugging**. Týmto spôsobom môžete vidieť detaily spracovávaných udalostí.

#### Riešenie problémov

* Ak dostanete nasledujúcu chybu:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Skontrolujte, či Azurite beží a či máte v súbore `local.settings.json` nastavené `AzureWebJobsStorage` na `UseDevelopmentStorage=true`.

* Ak dostanete nasledujúcu chybu:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Skontrolujte, či máte v súbore `function.json` nastavené `cardinality` na `one`.

* Ak dostanete nasledujúcu chybu:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Skontrolujte, či máte v súbore `function.json` nastavené `eventHubName` na prázdny reťazec.

## Odosielanie požiadaviek na priame metódy zo serverless kódu

Doteraz vaša aplikácia Functions počúvala správy z IoT Hubu pomocou event hub kompatibilného endpointu. Teraz potrebujete odosielať príkazy do IoT zariadenia. Toto sa vykonáva pomocou iného pripojenia k IoT Hubu cez *Registry Manager*. Registry Manager je nástroj, ktorý umožňuje vidieť, aké zariadenia sú registrované v IoT Hube, a komunikovať s týmito zariadeniami odosielaním správ z cloudu do zariadenia, požiadaviek na priame metódy alebo aktualizáciou zariadenia twin. Tiež ho môžete použiť na registráciu, aktualizáciu alebo odstránenie IoT zariadení z IoT Hubu.

Na pripojenie k Registry Manager potrebujete pripojovací reťazec.

### Úloha – získanie pripojovacieho reťazca pre Registry Manager

1. Na získanie pripojovacieho reťazca spustite nasledujúci príkaz:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom, ktorý ste použili pre váš IoT Hub.

    Pripojovací reťazec sa požaduje pre politiku *ServiceConnect* pomocou parametra `--policy-name service`. Pri požadovaní pripojovacieho reťazca môžete špecifikovať, aké oprávnenia tento reťazec umožní. Politika ServiceConnect umožňuje vášmu kódu pripojiť sa a odosielať správy do IoT zariadení.

    ✅ Urobte si prieskum: Prečítajte si o rôznych politikách v [dokumentácii o oprávneniach IoT Hubu](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn).

1. Vo VS Code otvorte súbor `local.settings.json`. Pridajte nasledujúcu hodnotu do sekcie `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Nahraďte `<connection string>` hodnotou z predchádzajúceho kroku. Aby bol JSON platný, budete musieť pridať čiarku za predchádzajúci riadok.

### Úloha – odoslanie požiadavky na priamu metódu do zariadenia

1. SDK pre Registry Manager je dostupné cez balík Pip. Pridajte nasledujúci riadok do súboru `requirements.txt`, aby ste pridali závislosť na tomto balíku:

    ```sh
    azure-iot-hub
    ```

1. Uistite sa, že terminál VS Code má aktivované virtuálne prostredie, a spustite nasledujúci príkaz na inštaláciu balíkov Pip:

    ```sh
    pip install -r requirements.txt
    ```

1. Pridajte nasledujúce importy do súboru `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Týmto sa importujú niektoré systémové knižnice, ako aj knižnice na interakciu s Registry Manager a odosielanie požiadaviek na priame metódy.

1. Odstráňte kód z funkcie `main`, ale ponechajte samotnú funkciu.

1. Do funkcie `main` pridajte nasledujúci kód:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Tento kód extrahuje telo udalosti, ktoré obsahuje JSON správu odoslanú IoT zariadením.

    Potom získa ID zariadenia z anotácií odovzdaných so správou. Telo udalosti obsahuje správu odoslanú ako telemetriu, zatiaľ čo slovník `iothub_metadata` obsahuje vlastnosti nastavené IoT Hubom, ako je ID zariadenia odosielateľa a čas odoslania správy.

    Tieto informácie sa potom zapisujú do logu. Tento log uvidíte v termináli pri lokálnom spustení aplikácie Functions.

1. Pod tento kód pridajte nasledujúci kód:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Tento kód získa vlhkosť pôdy zo správy. Potom skontroluje vlhkosť pôdy a v závislosti od hodnoty vytvorí pomocnú triedu pre požiadavku na priamu metódu `relay_on` alebo `relay_off`. Požiadavka na metódu nepotrebuje payload, takže sa odosiela prázdny JSON dokument.

1. Pod tento kód pridajte nasledujúci kód:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Tento kód načíta `REGISTRY_MANAGER_CONNECTION_STRING` zo súboru `local.settings.json`. Hodnoty v tomto súbore sú dostupné ako environmentálne premenné, ktoré je možné čítať pomocou funkcie `os.environ`, ktorá vracia slovník všetkých environmentálnych premenných.

> 💁 Keď je tento kód nasadený do cloudu, hodnoty zo súboru `local.settings.json` budú nastavené ako *Application Settings* a je možné ich čítať z environmentálnych premenných.

Kód potom vytvorí inštanciu pomocnej triedy Registry Manager pomocou reťazca pripojenia.

1. Pod toto pridajte nasledujúci kód:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Tento kód hovorí registry managerovi, aby poslal požiadavku na priamu metódu zariadeniu, ktoré odoslalo telemetriu.

    > 💁 V predchádzajúcich verziách aplikácie, ktoré ste vytvorili v skorších lekciách pomocou MQTT, boli príkazy na ovládanie relé odosielané všetkým zariadeniam. Kód predpokladal, že budete mať iba jedno zariadenie. Táto verzia kódu posiela požiadavku na metódu iba jednému zariadeniu, takže by fungovala aj v prípade, že by ste mali viacero nastavení senzorov vlhkosti a relé, pričom posiela správnu požiadavku na priamu metódu správnemu zariadeniu.

1. Spustite aplikáciu Functions a uistite sa, že vaše IoT zariadenie odosiela dáta. Uvidíte správy, ktoré sa spracovávajú, a požiadavky na priame metódy, ktoré sa odosielajú. Presúvajte senzor vlhkosti pôdy dovnútra a von z pôdy, aby ste videli, ako sa hodnoty menia a relé sa zapína a vypína.

> 💁 Tento kód nájdete v priečinku [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Nasadenie vášho serverless kódu do cloudu

Váš kód teraz funguje lokálne, takže ďalším krokom je nasadenie aplikácie Functions do cloudu.

### Úloha - vytvorte cloudové zdroje

Vaša aplikácia Functions musí byť nasadená do zdroja Functions App v Azure, ktorý sa nachádza v Resource Group, ktorú ste vytvorili pre váš IoT Hub. Budete tiež potrebovať Storage Account vytvorený v Azure, ktorý nahradí emulovaný účet, ktorý máte spustený lokálne.

1. Spustite nasledujúci príkaz na vytvorenie Storage Account:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Nahraďte `<storage_name>` názvom pre váš Storage Account. Tento názov musí byť globálne jedinečný, pretože tvorí časť URL, ktorá sa používa na prístup k Storage Account. Môžete použiť iba malé písmená a čísla, žiadne iné znaky, a je obmedzený na 24 znakov. Použite niečo ako `sms` a pridajte jedinečný identifikátor na koniec, napríklad náhodné slová alebo vaše meno.

    `--sku Standard_LRS` vyberá cenovú úroveň, pričom vyberá najlacnejší všeobecný účet. Neexistuje bezplatná úroveň úložiska a platíte za to, čo používate. Náklady sú relatívne nízke, pričom najdrahšie úložisko stojí menej ako 0,05 USD mesačne za gigabajt uložených dát.

    ✅ Prečítajte si o cenách na [stránke s cenami Azure Storage Account](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Spustite nasledujúci príkaz na vytvorenie Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Nahraďte `<location>` lokalitou, ktorú ste použili pri vytváraní Resource Group v predchádzajúcej lekcii.

    Nahraďte `<storage_name>` názvom Storage Account, ktorý ste vytvorili v predchádzajúcom kroku.

    Nahraďte `<functions_app_name>` jedinečným názvom pre vašu Function App. Tento názov musí byť globálne jedinečný, pretože tvorí časť URL, ktorá sa používa na prístup k Function App. Použite niečo ako `soil-moisture-sensor-` a pridajte jedinečný identifikátor na koniec, napríklad náhodné slová alebo vaše meno.

    `--functions-version 3` nastavuje verziu Azure Functions, ktorá sa má použiť. Verzia 3 je najnovšia verzia.

    `--os-type Linux` hovorí runtime Functions, aby použil Linux ako operačný systém na hosťovanie týchto funkcií. Funkcie môžu byť hosťované na Linuxe alebo Windows, v závislosti od použitého programovacieho jazyka. Python aplikácie sú podporované iba na Linuxe.

### Úloha - nahrajte nastavenia aplikácie

Keď ste vyvíjali svoju Function App, uložili ste niektoré nastavenia do súboru `local.settings.json` pre reťazce pripojenia k vášmu IoT Hub. Tieto je potrebné zapísať do Application Settings vo vašej Function App v Azure, aby ich váš kód mohol používať.

> 🎓 Súbor `local.settings.json` je určený iba pre lokálne vývojové nastavenia a nemal by byť kontrolovaný do systému na správu zdrojového kódu, ako je GitHub. Pri nasadení do cloudu sa používajú Application Settings. Application Settings sú páry kľúč/hodnota hosťované v cloude a čítajú sa z environmentálnych premenných buď vo vašom kóde, alebo runtime pri pripájaní vášho kódu k IoT Hub.

1. Spustite nasledujúci príkaz na nastavenie `IOT_HUB_CONNECTION_STRING` v Application Settings pre Function App:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Nahraďte `<functions_app_name>` názvom, ktorý ste použili pre vašu Function App.

    Nahraďte `<connection string>` hodnotou `IOT_HUB_CONNECTION_STRING` zo súboru `local.settings.json`.

1. Opakujte vyššie uvedený krok, ale nastavte hodnotu `REGISTRY_MANAGER_CONNECTION_STRING` na zodpovedajúcu hodnotu zo súboru `local.settings.json`.

Keď spustíte tieto príkazy, zobrazí sa aj zoznam všetkých Application Settings pre Function App. Môžete ho použiť na kontrolu, či sú vaše hodnoty nastavené správne.

> 💁 Uvidíte hodnotu už nastavenú pre `AzureWebJobsStorage`. Vo vašom súbore `local.settings.json` bola táto hodnota nastavená na použitie lokálneho emulátora úložiska. Keď ste vytvorili Function App, zadali ste Storage Account ako parameter, a táto hodnota sa automaticky nastaví v tomto nastavení.

### Úloha - nasadenie vašej Function App do cloudu

Teraz, keď je Function App pripravená, váš kód môže byť nasadený.

1. Spustite nasledujúci príkaz z terminálu VS Code na publikovanie vašej Function App:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Nahraďte `<functions_app_name>` názvom, ktorý ste použili pre vašu Function App.

Kód bude zabalený a odoslaný do Function App, kde bude nasadený a spustený. Zobrazí sa veľa výstupu v konzole, ktorý skončí potvrdením nasadenia a zoznamom nasadených funkcií. V tomto prípade bude zoznam obsahovať iba trigger.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Uistite sa, že vaše IoT zariadenie je spustené. Zmeňte úroveň vlhkosti pôdy úpravou vlhkosti alebo presúvaním senzora dovnútra a von z pôdy. Uvidíte, ako sa relé zapína a vypína, keď sa vlhkosť pôdy mení.

---

## 🚀 Výzva

V predchádzajúcej lekcii ste spravovali časovanie relé odhlásením sa z MQTT správ, zatiaľ čo relé bolo zapnuté, a krátko po jeho vypnutí. Tento spôsob tu nemôžete použiť - nemôžete odhlásiť váš IoT Hub trigger.

Premýšľajte o rôznych spôsoboch, ako by ste mohli tento problém riešiť vo vašej Function App.

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Prehľad a samoštúdium

* Prečítajte si o serverless computingu na [stránke Serverless Computing na Wikipédii](https://wikipedia.org/wiki/Serverless_computing)
* Prečítajte si o používaní serverless v Azure vrátane ďalších príkladov na [blogovom príspevku Azure Go serverless for your IoT needs](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Naučte sa viac o Azure Functions na [YouTube kanáli Azure Functions](https://www.youtube.com/c/AzureFunctions)

## Zadanie

[Pridajte manuálne ovládanie relé](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.