<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-27T23:00:40+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "cs"
}
-->
# Přesuňte logiku své aplikace do cloudu

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Tato lekce byla součástí [IoT for Beginners Project 2 - série Digitální zemědělství](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) od [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Ovládejte své IoT zařízení pomocí serverless kódu](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Úvod

V minulé lekci jste se naučili, jak připojit monitorování vlhkosti půdy a ovládání relé k cloudové IoT službě. Dalším krokem je přesunout serverový kód, který řídí časování relé, do cloudu. V této lekci se naučíte, jak to udělat pomocí serverless funkcí.

V této lekci se zaměříme na:

* [Co je serverless?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Vytvoření serverless aplikace](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Vytvoření triggeru události IoT Hubu](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Odesílání požadavků na přímé metody ze serverless kódu](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Nasazení serverless kódu do cloudu](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Co je serverless?

Serverless, nebo serverless computing, zahrnuje vytváření malých bloků kódu, které se spouštějí v cloudu v reakci na různé typy událostí. Když k události dojde, váš kód se spustí a předají se mu data o této události. Tyto události mohou pocházet z různých zdrojů, včetně webových požadavků, zpráv vložených do fronty, změn dat v databázi nebo zpráv odeslaných IoT zařízeními do IoT služby.

![Události odesílané z IoT služby do serverless služby, všechny zpracovávané současně více funkcemi](../../../../../translated_images/cs/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.png)

> 💁 Pokud jste někdy používali databázové triggery, můžete si to představit jako něco podobného – kód se spouští na základě události, například vložení řádku.

![Když je odesláno mnoho událostí současně, serverless služba se škáluje tak, aby je všechny zpracovala současně](../../../../../translated_images/cs/serverless-scaling.f8c769adf0413fd1.webp)

Váš kód se spouští pouze tehdy, když dojde k události, jinak není aktivní. Událost nastane, váš kód se načte a spustí. To činí serverless velmi škálovatelným – pokud dojde k mnoha událostem současně, poskytovatel cloudu může spustit vaši funkci tolikrát, kolikrát je potřeba, a to na různých serverech, které má k dispozici. Nevýhodou je, že pokud potřebujete sdílet informace mezi událostmi, musíte je uložit například do databáze, místo abyste je uchovávali v paměti.

Váš kód je napsán jako funkce, která přijímá podrobnosti o události jako parametr. Pro psaní těchto serverless funkcí můžete použít širokou škálu programovacích jazyků.

> 🎓 Serverless se také označuje jako Functions as a Service (FaaS), protože každý trigger události je implementován jako funkce v kódu.

Navzdory názvu serverless ve skutečnosti servery používá. Název vychází z toho, že jako vývojář se nemusíte starat o servery potřebné ke spuštění vašeho kódu, zajímá vás pouze to, že váš kód je spuštěn v reakci na událost. Poskytovatel cloudu má serverless *runtime*, který spravuje přidělování serverů, síť, úložiště, CPU, paměť a vše ostatní potřebné ke spuštění vašeho kódu. Tento model znamená, že neplatíte za server, ale za dobu, po kterou váš kód běží, a za množství použité paměti.

> 💰 Serverless je jedním z nejlevnějších způsobů, jak spouštět kód v cloudu. Například v době psaní tohoto textu jeden poskytovatel cloudu umožňuje všem vašim serverless funkcím provést dohromady 1 000 000 spuštění měsíčně zdarma, a poté účtuje 0,20 USD za každých 1 000 000 spuštění. Když váš kód neběží, neplatíte.

Pro IoT vývojáře je serverless model ideální. Můžete napsat funkci, která se spustí v reakci na zprávy odeslané z jakéhokoli IoT zařízení připojeného k vaší cloudové IoT službě. Váš kód zpracuje všechny odeslané zprávy, ale bude spuštěn pouze tehdy, když to bude potřeba.

✅ Podívejte se zpět na kód, který jste napsali jako serverový kód naslouchající zprávám přes MQTT. Jak by mohl tento kód běžet v cloudu pomocí serverless? Jak si myslíte, že by se kód mohl změnit, aby podporoval serverless computing?

> 💁 Serverless model se rozšiřuje i na další cloudové služby kromě spouštění kódu. Například serverless databáze jsou dostupné v cloudu s cenovým modelem, kde platíte za každý požadavek na databázi, například dotaz nebo vložení, obvykle na základě toho, kolik práce je potřeba k obsloužení požadavku. Například jednoduchý výběr jednoho řádku podle primárního klíče bude stát méně než složitá operace spojující mnoho tabulek a vracející tisíce řádků.

## Vytvoření serverless aplikace

Serverless služba od Microsoftu se nazývá Azure Functions.

![Logo Azure Functions](../../../../../translated_images/cs/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.png)

Krátké video níže poskytuje přehled Azure Functions.

[![Přehled Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Klikněte na obrázek výše pro zhlédnutí videa.

✅ Udělejte si chvíli na průzkum a přečtěte si přehled Azure Functions v [dokumentaci Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Pro psaní Azure Functions začínáte s aplikací Azure Functions v jazyce dle vašeho výběru. Azure Functions podporuje Python, JavaScript, TypeScript, C#, F#, Java a Powershell. V této lekci se naučíte, jak napsat aplikaci Azure Functions v Pythonu.

> 💁 Azure Functions také podporuje vlastní handlery, takže své funkce můžete psát v jakémkoli jazyce, který podporuje HTTP požadavky, včetně starších jazyků, jako je COBOL.

Aplikace funkcí se skládají z jednoho nebo více *triggerů* – funkcí, které reagují na události. Můžete mít více triggerů v jedné aplikaci funkcí, všechny sdílející společnou konfiguraci. Například v konfiguračním souboru vaší aplikace funkcí můžete mít připojovací údaje k IoT Hubu a všechny funkce v aplikaci mohou tyto údaje použít k připojení a naslouchání událostem.

### Úkol – instalace nástrojů Azure Functions

> V době psaní tohoto textu nástroje pro kódování Azure Functions nejsou plně funkční na Apple Silicon s Python projekty. Budete potřebovat Mac s procesorem Intel, Windows PC nebo Linux PC.

Jednou z výhod Azure Functions je, že je můžete spouštět lokálně. Stejný runtime, který se používá v cloudu, lze spustit na vašem počítači, což vám umožní psát kód, který reaguje na IoT zprávy, a spouštět ho lokálně. Dokonce můžete ladit svůj kód při zpracování událostí. Jakmile budete s kódem spokojeni, můžete ho nasadit do cloudu.

Nástroje Azure Functions jsou dostupné jako CLI, známé jako Azure Functions Core Tools.

1. Nainstalujte Azure Functions Core Tools podle pokynů v [dokumentaci Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Nainstalujte rozšíření Azure Functions pro VS Code. Toto rozšíření poskytuje podporu pro vytváření, ladění a nasazování Azure Functions. Podívejte se na [dokumentaci rozšíření Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) pro pokyny k instalaci tohoto rozšíření ve VS Code.

Když nasadíte svou aplikaci Azure Functions do cloudu, potřebuje malé množství cloudového úložiště pro ukládání věcí, jako jsou aplikační soubory a logy. Když spouštíte svou aplikaci funkcí lokálně, stále potřebujete připojení k cloudovému úložišti, ale místo skutečného cloudového úložiště můžete použít emulátor úložiště nazvaný [Azurite](https://github.com/Azure/Azurite). Tento emulátor běží lokálně, ale chová se jako cloudové úložiště.

> 🎓 V Azure je úložiště, které Azure Functions používá, Azure Storage Account. Tyto účty mohou ukládat soubory, blob objekty, data v tabulkách nebo data ve frontách. Jeden storage account můžete sdílet mezi mnoha aplikacemi, například aplikací funkcí a webovou aplikací.

1. Azurite je aplikace v Node.js, takže budete muset nainstalovat Node.js. Stáhněte si ho a nainstalujte podle pokynů na [webu Node.js](https://nodejs.org/). Pokud používáte Mac, můžete ho také nainstalovat pomocí [Homebrew](https://formulae.brew.sh/formula/node).

1. Nainstalujte Azurite pomocí následujícího příkazu (`npm` je nástroj, který se nainstaluje spolu s Node.js):

    ```sh
    npm install -g azurite
    ```

1. Vytvořte složku nazvanou `azurite` pro ukládání dat Azurite:

    ```sh
    mkdir azurite
    ```

1. Spusťte Azurite a předejte mu tuto novou složku:

    ```sh
    azurite --location azurite
    ```

    Emulátor úložiště Azurite se spustí a bude připraven k připojení lokálního runtime Functions.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Úkol – vytvoření projektu Azure Functions

CLI Azure Functions lze použít k vytvoření nové aplikace funkcí.

1. Vytvořte složku pro svou aplikaci funkcí a přejděte do ní. Nazvěte ji `soil-moisture-trigger`:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Vytvořte v této složce virtuální prostředí Python:

    ```sh
    python3 -m venv .venv
    ```

1. Aktivujte virtuální prostředí:

    * Na Windows:
        * Pokud používáte Command Prompt nebo Command Prompt přes Windows Terminal, spusťte:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Pokud používáte PowerShell, spusťte:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Na macOS nebo Linuxu spusťte:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Tyto příkazy by měly být spuštěny ze stejného umístění, kde jste spustili příkaz pro vytvoření virtuálního prostředí. Nikdy nebudete muset přecházet do složky `.venv`, vždy byste měli spouštět příkaz pro aktivaci a jakékoli příkazy pro instalaci balíčků nebo spuštění kódu z umístění, kde jste vytvořili virtuální prostředí.

1. Spusťte následující příkaz pro vytvoření aplikace funkcí v této složce:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Tím se v aktuální složce vytvoří tři soubory:

    * `host.json` – tento JSON dokument obsahuje nastavení vaší aplikace funkcí. Tato nastavení nebudete muset měnit.
    * `local.settings.json` – tento JSON dokument obsahuje nastavení, která vaše aplikace používá při lokálním spuštění, například připojovací řetězce k IoT Hubu. Tato nastavení jsou pouze lokální a neměla by být přidána do systému správy verzí. Když aplikaci nasadíte do cloudu, tato nastavení se nenasadí, místo toho se vaše nastavení načtou z aplikačních nastavení. To bude pokryto později v této lekci.
    * `requirements.txt` – to je [soubor požadavků Pip](https://pip.pypa.io/en/stable/user_guide/#requirements-files), který obsahuje balíčky Pip potřebné pro běh vaší aplikace funkcí.

1. Soubor `local.settings.json` má nastavení pro storage account, který aplikace funkcí použije. Toto nastavení je ve výchozím stavu prázdné, takže je třeba ho nastavit. Pro připojení k lokálnímu emulátoru úložiště Azurite nastavte tuto hodnotu na následující:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Nainstalujte potřebné balíčky Pip pomocí souboru požadavků:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Požadované balíčky Pip musí být v tomto souboru, aby runtime při nasazení aplikace funkcí do cloudu mohl zajistit instalaci správných balíčků.

1. Pro otestování, zda vše funguje správně, můžete spustit runtime Functions. Spusťte následující příkaz:

    ```sh
    func start
    ```

    Uvidíte, že runtime se spustí a oznámí, že nenašel žádné job funkce (triggery).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Pokud obdržíte oznámení o firewallu, udělte přístup, protože aplikace `func` potřebuje mít možnost číst a zapisovat do vaší sítě.
> ⚠️ Pokud používáte macOS, mohou se v výstupu objevit varování:
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
> Tato varování můžete ignorovat, pokud aplikace Functions správně startuje a zobrazuje běžící funkce. Jak je uvedeno v [této otázce na Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), lze je ignorovat.

1. Zastavte aplikaci Functions stisknutím `ctrl+c`.

1. Otevřete aktuální složku ve VS Code, buď otevřením VS Code a následným otevřením této složky, nebo spuštěním následujícího příkazu:

    ```sh
    code .
    ```

    VS Code rozpozná váš projekt Functions a zobrazí oznámení:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Oznámení](../../../../../translated_images/cs/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Vyberte **Ano** z tohoto oznámení.

1. Ujistěte se, že virtuální prostředí Python běží v terminálu VS Code. Pokud je to nutné, ukončete ho a znovu spusťte.

## Vytvoření triggeru událostí IoT Hubu

Aplikace Functions je obal vašeho serverless kódu. Pro reakci na události IoT Hubu můžete do této aplikace přidat trigger IoT Hubu. Tento trigger se musí připojit k proudu zpráv, které jsou odesílány do IoT Hubu, a na ně reagovat. Aby bylo možné získat tento proud zpráv, váš trigger se musí připojit k *event hub kompatibilnímu endpointu* IoT Hubu.

IoT Hub je založen na jiné službě Azure nazvané Azure Event Hubs. Event Hubs je služba, která umožňuje odesílat a přijímat zprávy, IoT Hub tuto funkci rozšiřuje o funkce pro IoT zařízení. Způsob, jakým se připojujete k čtení zpráv z IoT Hubu, je stejný jako při použití Event Hubs.

✅ Udělejte si průzkum: Přečtěte si přehled Event Hubs v [dokumentaci Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Jak se základní funkce porovnávají s IoT Hubem?

Aby se IoT zařízení mohlo připojit k IoT Hubu, musí použít tajný klíč, který zajistí, že se mohou připojit pouze povolená zařízení. Totéž platí při připojení ke čtení zpráv – váš kód bude potřebovat připojovací řetězec, který obsahuje tajný klíč spolu s detaily IoT Hubu.

> 💁 Výchozí připojovací řetězec, který získáte, má oprávnění **iothubowner**, což dává jakémukoli kódu, který ho používá, plná oprávnění na IoT Hubu. Ideálně byste se měli připojit s nejnižší úrovní oprávnění, která je potřebná. Toto bude pokryto v další lekci.

Jakmile se váš trigger připojí, kód uvnitř funkce bude volán pro každou zprávu odeslanou do IoT Hubu, bez ohledu na to, které zařízení ji odeslalo. Trigger bude předávat zprávu jako parametr.

### Úkol - získání připojovacího řetězce event hub kompatibilního endpointu

1. Z terminálu VS Code spusťte následující příkaz pro získání připojovacího řetězce pro event hub kompatibilní endpoint IoT Hubu:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem, který jste použili pro váš IoT Hub.

1. Ve VS Code otevřete soubor `local.settings.json`. Přidejte následující hodnotu do sekce `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Nahraďte `<connection string>` hodnotou z předchozího kroku. Budete muset přidat čárku za předchozí řádek, aby byl JSON platný.

### Úkol - vytvoření triggeru událostí

Nyní jste připraveni vytvořit trigger událostí.

1. Z terminálu VS Code spusťte následující příkaz ze složky `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Tento příkaz vytvoří novou funkci nazvanou `iot-hub-trigger`. Trigger se připojí k event hub kompatibilnímu endpointu IoT Hubu, takže můžete použít trigger event hubu. Neexistuje specifický trigger IoT Hubu.

Tím se vytvoří složka uvnitř složky `soil-moisture-trigger` nazvaná `iot-hub-trigger`, která obsahuje tuto funkci. Tato složka bude obsahovat následující soubory:

* `__init__.py` - Python soubor, který obsahuje trigger, používající standardní konvenci názvů Python souborů k tomu, aby se tato složka stala Python modulem.

    Tento soubor bude obsahovat následující kód:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Jádrem triggeru je funkce `main`. Tato funkce je volána s událostmi z IoT Hubu. Funkce má parametr nazvaný `event`, který obsahuje `EventHubEvent`. Pokaždé, když je zpráva odeslána do IoT Hubu, tato funkce je volána a předává tuto zprávu jako `event` spolu s vlastnostmi, které odpovídají anotacím, které jste viděli v předchozí lekci.

    Jádrem této funkce je logování události.

* `function.json` - obsahuje konfiguraci pro trigger. Hlavní konfigurace je v sekci nazvané `bindings`. Binding je termín pro spojení mezi Azure Functions a jinými službami Azure. Tato funkce má vstupní binding k event hubu – připojuje se k event hubu a přijímá data.

    > 💁 Můžete mít také výstupní bindingy, takže výstup funkce je odeslán do jiné služby. Například můžete přidat výstupní binding do databáze a vrátit událost IoT Hubu z funkce, a ta bude automaticky vložena do databáze.

    ✅ Udělejte si průzkum: Přečtěte si o bindingech v [dokumentaci konceptů triggerů a bindingů Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Sekce `bindings` obsahuje konfiguraci pro binding. Zajímavé hodnoty jsou:

  * `"type": "eventHubTrigger"` - říká funkci, že musí poslouchat události z Event Hubu
  * `"name": "events"` - název parametru pro události Event Hubu. Odpovídá názvu parametru ve funkci `main` v Python kódu.
  * `"direction": "in"` - jedná se o vstupní binding, data z event hubu přicházejí do funkce
  * `"connection": ""` - definuje název nastavení, ze kterého se čte připojovací řetězec. Při lokálním běhu se toto nastavení čte ze souboru `local.settings.json`.

    > 💁 Připojovací řetězec nemůže být uložen v souboru `function.json`, musí být čten z nastavení. To je proto, aby se zabránilo náhodnému zveřejnění připojovacího řetězce.

1. Kvůli [chybě v šabloně Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250) má `function.json` nesprávnou hodnotu pro pole `cardinality`. Aktualizujte toto pole z `many` na `one`:

    ```json
    "cardinality": "one",
    ```

1. Aktualizujte hodnotu `"connection"` v souboru `function.json`, aby odkazovala na novou hodnotu, kterou jste přidali do souboru `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Pamatujte - toto musí odkazovat na nastavení, ne obsahovat skutečný připojovací řetězec.

1. Připojovací řetězec obsahuje hodnotu `eventHubName`, takže hodnota pro toto pole v souboru `function.json` musí být vymazána. Aktualizujte tuto hodnotu na prázdný řetězec:

    ```json
    "eventHubName": "",
    ```

### Úkol - spuštění triggeru událostí

1. Ujistěte se, že nemonitorujete události IoT Hubu. Pokud je tento monitor spuštěn současně s aplikací Functions, aplikace Functions se nebude moci připojit a spotřebovávat události.

    > 💁 Více aplikací se může připojit k endpointům IoT Hubu pomocí různých *consumer groups*. Tyto budou pokryty v pozdější lekci.

1. Pro spuštění aplikace Functions spusťte následující příkaz z terminálu VS Code:

    ```sh
    func start
    ```

    Aplikace Functions se spustí a objeví funkci `iot-hub-trigger`. Poté zpracuje všechny události, které byly odeslány do IoT Hubu za poslední den.

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

    Každé volání funkce bude obklopeno blokem `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` ve výstupu, takže uvidíte, kolik zpráv bylo zpracováno při každém volání funkce.

1. Ujistěte se, že vaše IoT zařízení běží. Uvidíte nové zprávy o vlhkosti půdy objevující se v aplikaci Functions.

1. Zastavte a znovu spusťte aplikaci Functions. Uvidíte, že již nebude zpracovávat předchozí zprávy, ale pouze nové zprávy.

> 💁 VS Code také podporuje ladění vašich funkcí. Můžete nastavit break pointy kliknutím na okraj u začátku každého řádku kódu, nebo umístěním kurzoru na řádek kódu a výběrem *Run -> Toggle breakpoint*, nebo stisknutím `F9`. Můžete spustit debugger výběrem *Run -> Start debugging*, stisknutím `F5`, nebo výběrem panelu *Run and debug* a kliknutím na tlačítko **Start debugging**. Tímto způsobem můžete vidět detaily událostí, které jsou zpracovávány.

#### Řešení problémů

* Pokud obdržíte následující chybu:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Zkontrolujte, zda běží Azurite a zda jste nastavili `AzureWebJobsStorage` v souboru `local.settings.json` na `UseDevelopmentStorage=true`.

* Pokud obdržíte následující chybu:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Zkontrolujte, zda jste nastavili `cardinality` v souboru `function.json` na `one`.

* Pokud obdržíte následující chybu:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Zkontrolujte, zda jste nastavili `eventHubName` v souboru `function.json` na prázdný řetězec.

## Odesílání požadavků na přímé metody z serverless kódu

Doposud vaše aplikace Functions poslouchá zprávy z IoT Hubu pomocí endpointu kompatibilního s Event Hubem. Nyní potřebujete odesílat příkazy do IoT zařízení. To se provádí pomocí jiného připojení k IoT Hubu přes *Registry Manager*. Registry Manager je nástroj, který vám umožňuje vidět, jaká zařízení jsou registrována v IoT Hubu, a komunikovat s těmito zařízeními odesíláním zpráv z cloudu do zařízení, požadavků na přímé metody nebo aktualizací dvojčete zařízení. Můžete jej také použít k registraci, aktualizaci nebo odstranění IoT zařízení z IoT Hubu.

Pro připojení k Registry Manageru potřebujete připojovací řetězec.

### Úkol - získání připojovacího řetězce Registry Manageru

1. Pro získání připojovacího řetězce spusťte následující příkaz:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem, který jste použili pro váš IoT Hub.

    Připojovací řetězec je požadován pro politiku *ServiceConnect* pomocí parametru `--policy-name service`. Když požadujete připojovací řetězec, můžete specifikovat, jaká oprávnění tento připojovací řetězec umožní. Politika ServiceConnect umožňuje vašemu kódu připojit se a odesílat zprávy do IoT zařízení.

    ✅ Udělejte si průzkum: Přečtěte si o různých politikách v [dokumentaci oprávnění IoT Hubu](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. Ve VS Code otevřete soubor `local.settings.json`. Přidejte následující hodnotu do sekce `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Nahraďte `<connection string>` hodnotou z předchozího kroku. Budete muset přidat čárku za předchozí řádek, aby byl JSON platný.

### Úkol - odeslání požadavku na přímou metodu do zařízení

1. SDK pro Registry Manager je dostupné přes balíček Pip. Přidejte následující řádek do souboru `requirements.txt`, abyste přidali závislost na tomto balíčku:

    ```sh
    azure-iot-hub
    ```

1. Ujistěte se, že terminál VS Code má aktivované virtuální prostředí, a spusťte následující příkaz pro instalaci balíčků Pip:

    ```sh
    pip install -r requirements.txt
    ```

1. Přidejte následující importy do souboru `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Tyto importy zahrnují některé systémové knihovny, stejně jako knihovny pro interakci s Registry Managerem a odesílání požadavků na přímé metody.

1. Odstraňte kód uvnitř metody `main`, ale ponechte samotnou metodu.

1. Do metody `main` přidejte následující kód:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Tento kód extrahuje tělo události, které obsahuje JSON zprávu odeslanou IoT zařízením.

    Poté získá ID zařízení z anotací předaných se zprávou. Tělo události obsahuje zprávu odeslanou jako telemetrii, slovník `iothub_metadata` obsahuje vlastnosti nastavené IoT Hubem, jako je ID zařízení odesílatele a čas, kdy byla zpráva odeslána.

    Tyto informace jsou poté zalogovány. Toto logování uvidíte v terminálu, když spustíte aplikaci Functions lokálně.

1. Pod tento kód přidejte následující:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Tento kód získá vlhkost půdy ze zprávy. Poté zkontroluje vlhkost půdy a v závislosti na hodnotě vytvoří pomocnou třídu pro požadavek na přímou metodu `relay_on` nebo `relay_off`. Požadavek na metodu nepotřebuje payload, takže je odeslán prázdný JSON dokument.

1. Pod tento kód přidejte následující:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Tento kód načte `REGISTRY_MANAGER_CONNECTION_STRING` ze souboru `local.settings.json`. Hodnoty v tomto souboru jsou zpřístupněny jako proměnné prostředí, které lze přečíst pomocí funkce `os.environ`, což je funkce, která vrací slovník všech proměnných prostředí.

> 💁 Když je tento kód nasazen do cloudu, hodnoty v souboru `local.settings.json` budou nastaveny jako *Application Settings* a lze je přečíst z proměnných prostředí.

Kód poté vytvoří instanci pomocné třídy Registry Manager pomocí připojovacího řetězce.

1. Pod toto přidejte následující kód:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Tento kód říká správci registru, aby odeslal požadavek na přímou metodu zařízení, které odeslalo telemetrii.

    > 💁 V dřívějších verzích aplikace, které jste vytvořili v předchozích lekcích pomocí MQTT, byly příkazy pro ovládání relé odesílány všem zařízením. Kód předpokládal, že budete mít pouze jedno zařízení. Tato verze kódu odesílá požadavek na metodu pouze jednomu zařízení, takže by fungovala, i kdybyste měli více sad senzorů vlhkosti a relé, přičemž správný požadavek na přímou metodu by byl odeslán správnému zařízení.

1. Spusťte aplikaci Functions a ujistěte se, že vaše IoT zařízení odesílá data. Uvidíte, jak jsou zprávy zpracovávány a požadavky na přímé metody odesílány. Pohybujte senzorem vlhkosti půdy dovnitř a ven ze země, abyste viděli, jak se hodnoty mění a relé se zapíná a vypíná.

> 💁 Tento kód najdete ve složce [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Nasazení vašeho serverless kódu do cloudu

Váš kód nyní funguje lokálně, takže dalším krokem je nasazení aplikace Functions App do cloudu.

### Úkol - vytvoření cloudových prostředků

Vaše aplikace Functions musí být nasazena do prostředku Functions App v Azure, který se nachází ve skupině prostředků, kterou jste vytvořili pro váš IoT Hub. Budete také potřebovat vytvořit Účet úložiště v Azure, který nahradí emulovaný účet, který máte spuštěný lokálně.

1. Spusťte následující příkaz pro vytvoření účtu úložiště:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Nahraďte `<storage_name>` názvem pro váš účet úložiště. Tento název musí být globálně jedinečný, protože tvoří část URL používané pro přístup k účtu úložiště. Pro tento název můžete použít pouze malá písmena a čísla, žádné jiné znaky, a je omezen na 24 znaků. Použijte například `sms` a přidejte na konec jedinečný identifikátor, například náhodná slova nebo vaše jméno.

    Parametr `--sku Standard_LRS` vybírá cenovou úroveň, přičemž vybírá nejlevnější účet pro obecné účely. Neexistuje bezplatná úroveň úložiště a platíte za to, co používáte. Náklady jsou relativně nízké, přičemž nejdražší úložiště stojí méně než 0,05 USD za měsíc na gigabajt uložených dat.

    ✅ Přečtěte si více o cenách na [stránce s cenami Azure Storage Account](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn).

1. Spusťte následující příkaz pro vytvoření aplikace Functions App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Nahraďte `<location>` umístěním, které jste použili při vytváření skupiny prostředků v předchozí lekci.

    Nahraďte `<storage_name>` názvem účtu úložiště, který jste vytvořili v předchozím kroku.

    Nahraďte `<functions_app_name>` jedinečným názvem pro vaši aplikaci Functions App. Tento název musí být globálně jedinečný, protože tvoří část URL, která může být použita pro přístup k aplikaci Functions App. Použijte například `soil-moisture-sensor-` a přidejte na konec jedinečný identifikátor, například náhodná slova nebo vaše jméno.

    Parametr `--functions-version 3` nastavuje verzi Azure Functions, která se má použít. Verze 3 je nejnovější verzí.

    Parametr `--os-type Linux` říká runtime Functions, aby používal Linux jako operační systém pro hostování těchto funkcí. Funkce mohou být hostovány na Linuxu nebo Windows, v závislosti na použitém programovacím jazyce. Python aplikace jsou podporovány pouze na Linuxu.

### Úkol - nahrání nastavení aplikace

Když jste vyvíjeli svou aplikaci Functions App, uložili jste některá nastavení do souboru `local.settings.json` pro připojovací řetězce k vašemu IoT Hubu. Tato nastavení je třeba zapsat do Application Settings ve vaší aplikaci Functions App v Azure, aby je mohl váš kód používat.

> 🎓 Soubor `local.settings.json` je určen pouze pro nastavení lokálního vývoje a neměl by být zařazen do systému správy zdrojového kódu, jako je GitHub. Při nasazení do cloudu se používají Application Settings. Application Settings jsou páry klíč/hodnota hostované v cloudu a jsou čteny z proměnných prostředí buď ve vašem kódu, nebo runtime při připojování vašeho kódu k IoT Hubu.

1. Spusťte následující příkaz pro nastavení hodnoty `IOT_HUB_CONNECTION_STRING` v Application Settings aplikace Functions App:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Nahraďte `<functions_app_name>` názvem, který jste použili pro vaši aplikaci Functions App.

    Nahraďte `<connection string>` hodnotou `IOT_HUB_CONNECTION_STRING` z vašeho souboru `local.settings.json`.

1. Opakujte výše uvedený krok, ale nastavte hodnotu `REGISTRY_MANAGER_CONNECTION_STRING` na odpovídající hodnotu ze souboru `local.settings.json`.

Když spustíte tyto příkazy, zobrazí se také seznam všech Application Settings pro aplikaci Functions App. Můžete jej použít k ověření, že vaše hodnoty jsou nastaveny správně.

> 💁 Uvidíte hodnotu již nastavenou pro `AzureWebJobsStorage`. Ve vašem souboru `local.settings.json` byla tato hodnota nastavena na hodnotu pro použití lokálního emulátoru úložiště. Když jste vytvořili aplikaci Functions App, předali jste účet úložiště jako parametr a tato hodnota byla automaticky nastavena v tomto nastavení.

### Úkol - nasazení vaší aplikace Functions App do cloudu

Nyní, když je aplikace Functions App připravena, váš kód může být nasazen.

1. Spusťte následující příkaz z terminálu VS Code pro publikování vaší aplikace Functions App:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Nahraďte `<functions_app_name>` názvem, který jste použili pro vaši aplikaci Functions App.

Kód bude zabalen a odeslán do aplikace Functions App, kde bude nasazen a spuštěn. Na konzoli se zobrazí mnoho výstupů, které skončí potvrzením nasazení a seznamem nasazených funkcí. V tomto případě bude seznam obsahovat pouze trigger.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Ujistěte se, že vaše IoT zařízení běží. Změňte úroveň vlhkosti půdy úpravou vlhkosti nebo pohybem senzoru dovnitř a ven ze země. Uvidíte, jak se relé zapíná a vypíná podle změn vlhkosti půdy.

---

## 🚀 Výzva

V předchozí lekci jste spravovali časování relé odhlášením z MQTT zpráv, zatímco bylo relé zapnuté, a na krátkou dobu poté, co bylo vypnuto. Tento způsob zde nelze použít - nemůžete odhlásit váš IoT Hub trigger.

Přemýšlejte o různých způsobech, jak byste mohli tuto situaci řešit ve vaší aplikaci Functions App.

## Kvíz po lekci

[Kvíz po lekci](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Přehled a samostudium

* Přečtěte si o serverless computingu na [stránce Serverless Computing na Wikipedii](https://wikipedia.org/wiki/Serverless_computing)
* Přečtěte si o používání serverless v Azure včetně dalších příkladů na [blogovém příspěvku Azure Go serverless for your IoT needs](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Zjistěte více o Azure Functions na [YouTube kanálu Azure Functions](https://www.youtube.com/c/AzureFunctions)

## Zadání

[Ruční ovládání relé](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.