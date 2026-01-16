<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-27T22:29:26+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "sv"
}
-->
# Migrera din applikationslogik till molnet

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

Denna lektion ingick som en del av [IoT för nybörjare Projekt 2 - Digital Agriculture-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) från [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Styr din IoT-enhet med serverlös kod](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Quiz före föreläsningen

[Quiz före föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Introduktion

I den senaste lektionen lärde du dig hur du ansluter din övervakning av jordfuktighet och relästyrning till en molnbaserad IoT-tjänst. Nästa steg är att flytta serverkoden som styr reläets timing till molnet. I denna lektion kommer du att lära dig hur du gör detta med hjälp av serverlösa funktioner.

I denna lektion kommer vi att täcka:

* [Vad är serverlöst?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Skapa en serverlös applikation](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Skapa en IoT Hub-händelsetrigger](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Skicka direkta metodförfrågningar från serverlös kod](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Distribuera din serverlösa kod till molnet](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Vad är serverlöst?

Serverlöst, eller serverlös databehandling, innebär att skapa små kodblock som körs i molnet som svar på olika typer av händelser. När händelsen inträffar körs din kod och får data om händelsen. Dessa händelser kan komma från många olika saker, inklusive webbförfrågningar, meddelanden som läggs i en kö, ändringar av data i en databas eller meddelanden som skickas till en IoT-tjänst av IoT-enheter.

![Händelser som skickas från en IoT-tjänst till en serverlös tjänst, alla bearbetas samtidigt av flera funktioner som körs](../../../../../translated_images/sv/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.png)

> 💁 Om du har använt databasutlösare tidigare kan du tänka på detta som samma sak, kod som triggas av en händelse som att infoga en rad.

![När många händelser skickas samtidigt skalar den serverlösa tjänsten upp för att köra dem alla samtidigt](../../../../../translated_images/sv/serverless-scaling.f8c769adf0413fd1.webp)

Din kod körs endast när händelsen inträffar, det finns inget som håller din kod aktiv vid andra tillfällen. Händelsen inträffar, din kod laddas och körs. Detta gör serverlöst mycket skalbart - om många händelser inträffar samtidigt kan molnleverantören köra din funktion så många gånger som behövs samtidigt över de servrar de har tillgängliga. Nackdelen med detta är att om du behöver dela information mellan händelser måste du spara den någonstans, som i en databas, istället för att lagra den i minnet.

Din kod skrivs som en funktion som tar detaljer om händelsen som en parameter. Du kan använda ett brett utbud av programmeringsspråk för att skriva dessa serverlösa funktioner.

> 🎓 Serverlöst kallas också för Functions as a Service (FaaS), eftersom varje händelsetrigger implementeras som en funktion i kod.

Trots namnet använder serverlöst faktiskt servrar. Namnet kommer från att du som utvecklare inte behöver bry dig om servrarna som behövs för att köra din kod, allt du bryr dig om är att din kod körs som svar på en händelse. Molnleverantören har en serverlös *runtime* som hanterar tilldelning av servrar, nätverk, lagring, CPU, minne och allt annat som behövs för att köra din kod. Denna modell innebär att du inte kan betala per server för tjänsten, eftersom det inte finns någon server. Istället betalar du för den tid din kod körs och mängden minne som används.

> 💰 Serverlöst är ett av de billigaste sätten att köra kod i molnet. Till exempel, vid tidpunkten för skrivandet, tillåter en molnleverantör att alla dina serverlösa funktioner körs totalt 1 000 000 gånger per månad innan de börjar ta betalt, och efter det tar de ut 0,20 USD för varje 1 000 000 körningar. När din kod inte körs betalar du ingenting.

Som IoT-utvecklare är den serverlösa modellen idealisk. Du kan skriva en funktion som anropas som svar på meddelanden som skickas från vilken IoT-enhet som helst som är ansluten till din molnvärd IoT-tjänst. Din kod hanterar alla meddelanden som skickas, men körs endast när det behövs.

✅ Titta tillbaka på koden du skrev som serverkod som lyssnar på meddelanden via MQTT. Hur skulle detta kunna köras i molnet med serverlöst? Hur tror du att koden kan behöva ändras för att stödja serverlös databehandling?

> 💁 Den serverlösa modellen sprider sig till andra molntjänster utöver att köra kod. Till exempel finns det serverlösa databaser i molnet som använder en serverlös prismodell där du betalar per begäran mot databasen, såsom en fråga eller infogning, vanligtvis med prissättning baserad på hur mycket arbete som görs för att hantera begäran. Till exempel kommer en enkel sökning av en rad mot en primärnyckel att kosta mindre än en komplicerad operation som sammanfogar många tabeller och returnerar tusentals rader.

## Skapa en serverlös applikation

Den serverlösa databehandlingstjänsten från Microsoft kallas Azure Functions.

![Azure Functions-logotypen](../../../../../translated_images/sv/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.png)

Den korta videon nedan ger en översikt över Azure Functions.

[![Azure Functions översiktsvideo](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Klicka på bilden ovan för att titta på videon.

✅ Ta en stund att göra lite research och läs översikten av Azure Functions i [Microsoft Azure Functions-dokumentationen](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

För att skriva Azure Functions börjar du med en Azure Functions-app i det språk du föredrar. Azure Functions stöder Python, JavaScript, TypeScript, C#, F#, Java och Powershell direkt. I denna lektion kommer du att lära dig hur man skriver en Azure Functions-app i Python.

> 💁 Azure Functions stöder också anpassade hanterare, så du kan skriva dina funktioner i vilket språk som helst som stöder HTTP-förfrågningar, inklusive äldre språk som COBOL.

Functions-appar består av en eller flera *triggers* - funktioner som svarar på händelser. Du kan ha flera triggers i en Functions-app, alla delar gemensam konfiguration. Till exempel kan du i konfigurationsfilen för din Functions-app ha anslutningsdetaljer för din IoT Hub, och alla funktioner i appen kan använda detta för att ansluta och lyssna på händelser.

### Uppgift - installera Azure Functions-verktygen

> Vid tidpunkten för skrivandet fungerar inte Azure Functions kodverktyg fullt ut på Apple Silicon med Python-projekt. Du måste använda en Intel-baserad Mac, Windows PC eller Linux PC istället.

En fantastisk funktion med Azure Functions är att du kan köra dem lokalt. Samma runtime som används i molnet kan köras på din dator, vilket gör att du kan skriva kod som svarar på IoT-meddelanden och köra den lokalt. Du kan till och med felsöka din kod medan händelser hanteras. När du är nöjd med din kod kan den distribueras till molnet.

Azure Functions-verktygen är tillgängliga som en CLI, känd som Azure Functions Core Tools.

1. Installera Azure Functions Core Tools genom att följa instruktionerna i [Azure Functions Core Tools-dokumentationen](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Installera Azure Functions-tillägget för VS Code. Detta tillägg ger stöd för att skapa, felsöka och distribuera Azure Functions. Se [Azure Functions-tilläggsdokumentationen](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) för instruktioner om hur du installerar detta tillägg i VS Code.

När du distribuerar din Azure Functions-app till molnet behöver den använda en liten mängd molnlagring för att lagra saker som applikationsfiler och loggfiler. När du kör din Functions-app lokalt måste du fortfarande ansluta till molnlagring, men istället för att använda faktisk molnlagring kan du använda en lagringsemulator som [Azurite](https://github.com/Azure/Azurite). Denna körs lokalt men fungerar som molnlagring.

> 🎓 I Azure är lagringen som Azure Functions använder ett Azure Storage Account. Dessa konton kan lagra filer, blobbar, data i tabeller eller data i köer. Du kan dela ett lagringskonto mellan många appar, såsom en Functions-app och en webbapp.

1. Azurite är en Node.js-app, så du måste installera Node.js. Du kan hitta nedladdnings- och installationsinstruktioner på [Node.js-webbplatsen](https://nodejs.org/). Om du använder en Mac kan du också installera det från [Homebrew](https://formulae.brew.sh/formula/node).

1. Installera Azurite med följande kommando (`npm` är ett verktyg som installeras när du installerar Node.js):

    ```sh
    npm install -g azurite
    ```

1. Skapa en mapp som heter `azurite` för Azurite att använda för att lagra data:

    ```sh
    mkdir azurite
    ```

1. Kör Azurite och ange denna nya mapp:

    ```sh
    azurite --location azurite
    ```

    Azurite-lagringsemulatorn startar och är redo för den lokala Functions-runtime att ansluta.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Uppgift - skapa ett Azure Functions-projekt

Azure Functions CLI kan användas för att skapa en ny Functions-app.

1. Skapa en mapp för din Functions-app och navigera till den. Kalla den `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Skapa en Python-virtuell miljö i denna mapp:

    ```sh
    python3 -m venv .venv
    ```

1. Aktivera den virtuella miljön:

    * På Windows:
        * Om du använder Kommandotolken eller Kommandotolken via Windows Terminal, kör:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Om du använder PowerShell, kör:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * På macOS eller Linux, kör:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Dessa kommandon bör köras från samma plats som du körde kommandot för att skapa den virtuella miljön. Du behöver aldrig navigera in i `.venv`-mappen, du bör alltid köra aktiveringskommandot och eventuella kommandon för att installera paket eller köra kod från mappen du var i när du skapade den virtuella miljön.

1. Kör följande kommando för att skapa en Functions-app i denna mapp:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Detta kommer att skapa tre filer i den aktuella mappen:

    * `host.json` - detta JSON-dokument innehåller inställningar för din Functions-app. Du behöver inte ändra dessa inställningar.
    * `local.settings.json` - detta JSON-dokument innehåller inställningar som din app skulle använda när den körs lokalt, såsom anslutningssträngar för din IoT Hub. Dessa inställningar är endast lokala och bör inte läggas till i källkodskontroll. När du distribuerar appen till molnet distribueras inte dessa inställningar, istället laddas dina inställningar från applikationsinställningar. Detta kommer att täckas senare i denna lektion.
    * `requirements.txt` - detta är en [Pip-kravfil](https://pip.pypa.io/en/stable/user_guide/#requirements-files) som innehåller de Pip-paket som behövs för att köra din Functions-app.

1. `local.settings.json`-filen har en inställning för lagringskontot som Functions-appen kommer att använda. Detta är som standard tomt och behöver ställas in. För att ansluta till Azurite-lagringsemulatorn lokalt, ställ in detta värde till följande:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Installera de nödvändiga Pip-paketen med hjälp av kravfilen:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 De nödvändiga Pip-paketen måste finnas i denna fil, så att när Functions-appen distribueras till molnet kan runtime säkerställa att den installerar rätt paket.

1. För att testa att allt fungerar korrekt kan du starta Functions-runtime. Kör följande kommando för att göra detta:

    ```sh
    func start
    ```

    Du kommer att se att runtime startar och rapporterar att den inte har hittat några jobbfunktioner (triggers).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Om du får en brandväggsnotifikation, ge åtkomst eftersom applikationen `func` behöver kunna läsa och skriva till ditt nätverk.
> ⚠️ Om du använder macOS kan det förekomma varningar i utdata:
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
> Du kan ignorera dessa så länge Functions-appen startar korrekt och listar de körande funktionerna. Som nämnts i [denna fråga på Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) kan detta ignoreras.

1. Stoppa Functions-appen genom att trycka på `ctrl+c`.

1. Öppna den aktuella mappen i VS Code, antingen genom att öppna VS Code och sedan öppna denna mapp, eller genom att köra följande kommando:

    ```sh
    code .
    ```

    VS Code kommer att upptäcka ditt Functions-projekt och visa en notis som säger:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Notisen](../../../../../translated_images/sv/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Välj **Yes** i denna notis.

1. Se till att den virtuella Python-miljön körs i VS Code-terminalen. Avsluta och starta om den om det behövs.

## Skapa en IoT Hub-händelseutlösare

Functions-appen är skalet för din serverlösa kod. För att svara på IoT Hub-händelser kan du lägga till en IoT Hub-utlösare i denna app. Denna utlösare behöver ansluta till strömmen av meddelanden som skickas till IoT Hub och svara på dem. För att få denna meddelandeström behöver din utlösare ansluta till IoT Hubs *event hub-kompatibla slutpunkt*.

IoT Hub är baserad på en annan Azure-tjänst som heter Azure Event Hubs. Event Hubs är en tjänst som låter dig skicka och ta emot meddelanden, och IoT Hub utökar detta med funktioner för IoT-enheter. Sättet du ansluter för att läsa meddelanden från IoT Hub är detsamma som om du använde Event Hubs.

✅ Gör lite efterforskning: Läs översikten om Event Hubs i [Azure Event Hubs-dokumentationen](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Hur jämförs de grundläggande funktionerna med IoT Hub?

För att en IoT-enhet ska kunna ansluta till IoT Hub måste den använda en hemlig nyckel som säkerställer att endast tillåtna enheter kan ansluta. Samma sak gäller när du ansluter för att läsa meddelanden; din kod behöver en anslutningssträng som innehåller en hemlig nyckel tillsammans med detaljer om IoT Hub.

> 💁 Standardanslutningssträngen du får har **iothubowner**-behörigheter, vilket ger all kod som använder den fullständiga behörigheter på IoT Hub. Idealiskt sett bör du ansluta med den lägsta nödvändiga behörighetsnivån. Detta kommer att täckas i nästa lektion.

När din utlösare har anslutit kommer koden inuti funktionen att anropas för varje meddelande som skickas till IoT Hub, oavsett vilken enhet som skickade det. Utlösaren kommer att skicka meddelandet som en parameter.

### Uppgift - hämta anslutningssträngen för den event hub-kompatibla slutpunkten

1. Kör följande kommando från VS Code-terminalen för att hämta anslutningssträngen för IoT Hubs event hub-kompatibla slutpunkt:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Ersätt `<hub_name>` med namnet du använde för din IoT Hub.

1. Öppna filen `local.settings.json` i VS Code. Lägg till följande värde i avsnittet `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Ersätt `<connection string>` med värdet från föregående steg. Du behöver lägga till ett kommatecken efter raden ovan för att göra detta till giltig JSON.

### Uppgift - skapa en händelseutlösare

Nu är du redo att skapa händelseutlösaren.

1. Kör följande kommando från VS Code-terminalen inifrån mappen `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Detta skapar en ny funktion som heter `iot-hub-trigger`. Utlösaren kommer att ansluta till den event hub-kompatibla slutpunkten på IoT Hub, så du kan använda en event hub-utlösare. Det finns ingen specifik IoT Hub-utlösare.

Detta kommer att skapa en mapp inuti mappen `soil-moisture-trigger` som heter `iot-hub-trigger` och som innehåller denna funktion. Denna mapp kommer att innehålla följande filer:

* `__init__.py` - detta är Python-kodfilen som innehåller utlösaren, med standardnamngivningskonventionen för Python-filer för att göra denna mapp till en Python-modul.

    Denna fil kommer att innehålla följande kod:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Kärnan i utlösaren är funktionen `main`. Det är denna funktion som anropas med händelserna från IoT Hub. Denna funktion har en parameter som heter `event` som innehåller en `EventHubEvent`. Varje gång ett meddelande skickas till IoT Hub anropas denna funktion och skickar meddelandet som `event`, tillsammans med egenskaper som är desamma som de annoteringar du såg i förra lektionen.

    Kärnan i denna funktion loggar händelsen.

* `function.json` - denna fil innehåller konfigurationen för utlösaren. Huvudkonfigurationen finns i ett avsnitt som heter `bindings`. En binding är termen för en anslutning mellan Azure Functions och andra Azure-tjänster. Denna funktion har en input-binding till en event hub - den ansluter till en event hub och tar emot data.

    > 💁 Du kan också ha output-bindings så att utdata från en funktion skickas till en annan tjänst. Till exempel kan du lägga till en output-binding till en databas och returnera IoT Hub-händelsen från funktionen, och den kommer automatiskt att infogas i databasen.

    ✅ Gör lite efterforskning: Läs om bindings i [Azure Functions triggers and bindings concepts-dokumentationen](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Avsnittet `bindings` innehåller konfigurationen för bindningen. De intressanta värdena är:

  * `"type": "eventHubTrigger"` - detta anger att funktionen behöver lyssna på händelser från en Event Hub
  * `"name": "events"` - detta är parameternamnet som används för Event Hub-händelserna. Detta matchar parameternamnet i funktionen `main` i Python-koden.
  * `"direction": "in"` - detta är en input-binding, data från event hub kommer in i funktionen
  * `"connection": ""` - detta definierar namnet på inställningen för att läsa anslutningssträngen från. När du kör lokalt kommer detta att läsa denna inställning från filen `local.settings.json`.

    > 💁 Anslutningssträngen kan inte lagras i filen `function.json`, den måste läsas från inställningarna. Detta är för att förhindra att du av misstag exponerar din anslutningssträng.

1. På grund av [en bugg i Azure Functions-mallen](https://github.com/Azure/azure-functions-templates/issues/1250) har `function.json` ett felaktigt värde för fältet `cardinality`. Uppdatera detta fält från `many` till `one`:

    ```json
    "cardinality": "one",
    ```

1. Uppdatera värdet för `"connection"` i filen `function.json` så att det pekar på det nya värdet du lade till i filen `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Kom ihåg - detta måste peka på inställningen, inte innehålla den faktiska anslutningssträngen.

1. Anslutningssträngen innehåller värdet `eventHubName`, så värdet för detta i filen `function.json` måste rensas. Uppdatera detta värde till en tom sträng:

    ```json
    "eventHubName": "",
    ```

### Uppgift - kör händelseutlösaren

1. Se till att du inte kör IoT Hub-händelseövervakaren. Om denna körs samtidigt som Functions-appen kommer Functions-appen inte att kunna ansluta och konsumera händelser.

    > 💁 Flera appar kan ansluta till IoT Hub-slutpunkter med olika *konsumentgrupper*. Dessa täcks i en senare lektion.

1. För att köra Functions-appen, kör följande kommando från VS Code-terminalen:

    ```sh
    func start
    ```

    Functions-appen startar och upptäcker funktionen `iot-hub-trigger`. Den kommer sedan att bearbeta alla händelser som redan har skickats till IoT Hub under det senaste dygnet.

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

    Varje anrop till funktionen kommer att omges av ett block `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` i utdata, så att du kan se hur många meddelanden som bearbetades i varje funktionsanrop.

1. Se till att din IoT-enhet körs. Du kommer att se nya jordfuktighetsmeddelanden dyka upp i Functions-appen.

1. Stoppa och starta om Functions-appen. Du kommer att se att den inte bearbetar tidigare meddelanden igen, utan endast bearbetar nya meddelanden.

> 💁 VS Code stöder också felsökning av dina funktioner. Du kan sätta brytpunkter genom att klicka på kanten vid början av varje kodrad, eller placera markören på en kodrad och välja *Run -> Toggle breakpoint*, eller trycka på `F9`. Du kan starta felsökaren genom att välja *Run -> Start debugging*, trycka på `F5`, eller välja *Run and debug*-panelen och välja knappen **Start debugging**. Genom att göra detta kan du se detaljerna för de händelser som bearbetas.

#### Felsökning

* Om du får följande fel:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Kontrollera att Azurite körs och att du har ställt in `AzureWebJobsStorage` i filen `local.settings.json` till `UseDevelopmentStorage=true`.

* Om du får följande fel:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Kontrollera att du har ställt in `cardinality` i filen `function.json` till `one`.

* Om du får följande fel:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Kontrollera att du har ställt in `eventHubName` i filen `function.json` till en tom sträng.

## Skicka direkta metodförfrågningar från serverlös kod

Hittills lyssnar din Functions-app på meddelanden från IoT Hub via den event hub-kompatibla slutpunkten. Nu behöver du skicka kommandon till IoT-enheten. Detta görs genom att använda en annan anslutning till IoT Hub via *Registry Manager*. Registry Manager är ett verktyg som låter dig se vilka enheter som är registrerade i IoT Hub och kommunicera med dessa enheter genom att skicka moln-till-enhet-meddelanden, direkta metodförfrågningar eller uppdatera enhetstvillingen. Du kan också använda det för att registrera, uppdatera eller ta bort IoT-enheter från IoT Hub.

För att ansluta till Registry Manager behöver du en anslutningssträng.

### Uppgift - hämta anslutningssträngen för Registry Manager

1. För att hämta anslutningssträngen, kör följande kommando:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Ersätt `<hub_name>` med namnet du använde för din IoT Hub.

    Anslutningssträngen begärs för *ServiceConnect*-policyn med parametern `--policy-name service`. När du begär en anslutningssträng kan du specificera vilka behörigheter denna anslutningssträng ska tillåta. ServiceConnect-policyn tillåter din kod att ansluta och skicka meddelanden till IoT-enheter.

    ✅ Gör lite efterforskning: Läs om de olika policys i [IoT Hub-behörighetsdokumentationen](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. Öppna filen `local.settings.json` i VS Code. Lägg till följande värde i avsnittet `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Ersätt `<connection string>` med värdet från föregående steg. Du behöver lägga till ett kommatecken efter raden ovan för att göra detta till giltig JSON.

### Uppgift - skicka en direkt metodförfrågan till en enhet

1. SDK:n för Registry Manager är tillgänglig via ett Pip-paket. Lägg till följande rad i filen `requirements.txt` för att lägga till beroendet för detta paket:

    ```sh
    azure-iot-hub
    ```

1. Se till att VS Code-terminalen har den virtuella miljön aktiverad och kör följande kommando för att installera Pip-paketen:

    ```sh
    pip install -r requirements.txt
    ```

1. Lägg till följande imports i filen `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Detta importerar några systembibliotek samt biblioteken för att interagera med Registry Manager och skicka direkta metodförfrågningar.

1. Ta bort koden inuti metoden `main`, men behåll själva metoden.

1. Lägg till följande kod i metoden `main`:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Denna kod extraherar innehållet i händelsen som innehåller JSON-meddelandet som skickats av IoT-enheten.

    Den hämtar sedan enhetens ID från annoteringarna som skickas med meddelandet. Innehållet i händelsen innehåller meddelandet som skickats som telemetri, och ordboken `iothub_metadata` innehåller egenskaper som ställts in av IoT Hub, såsom enhetens ID för avsändaren och tiden då meddelandet skickades.

    Denna information loggas sedan. Du kommer att se denna loggning i terminalen när du kör Functions-appen lokalt.

1. Lägg till följande kod nedanför detta:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Denna kod hämtar jordfuktigheten från meddelandet. Den kontrollerar sedan jordfuktigheten och, beroende på värdet, skapar en hjälparklass för den direkta metodförfrågan för antingen `relay_on` eller `relay_off`. Metodförfrågan behöver ingen nyttolast, så ett tomt JSON-dokument skickas.

1. Lägg till följande kod nedanför detta:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Den här koden laddar `REGISTRY_MANAGER_CONNECTION_STRING` från filen `local.settings.json`. Värdena i den här filen görs tillgängliga som miljövariabler och kan läsas med funktionen `os.environ`, en funktion som returnerar en ordbok med alla miljövariabler.

> 💁 När den här koden distribueras till molnet kommer värdena i filen `local.settings.json` att ställas in som *Application Settings*, och dessa kan läsas från miljövariabler.

Koden skapar sedan en instans av hjälparklassen Registry Manager med hjälp av anslutningssträngen.

1. Lägg till följande kod nedanför detta:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Den här koden instruerar registry manager att skicka en direkt metodförfrågan till enheten som skickade telemetrin.

    > 💁 I de versioner av appen som du skapade i tidigare lektioner med MQTT skickades reläkontrollkommandon till alla enheter. Koden antog att du bara skulle ha en enhet. Den här versionen av koden skickar metodförfrågan till en enda enhet, vilket gör att den fungerar om du har flera uppsättningar av fuktighetssensorer och reläer, och skickar rätt direkt metodförfrågan till rätt enhet.

1. Kör Functions-appen och se till att din IoT-enhet skickar data. Du kommer att se meddelandena bearbetas och de direkta metodförfrågningarna skickas. Flytta jordfuktighetssensorn in och ut ur jorden för att se värdena ändras och reläet slås på och av.

> 💁 Du hittar den här koden i mappen [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Distribuera din serverlösa kod till molnet

Din kod fungerar nu lokalt, så nästa steg är att distribuera Functions-appen till molnet.

### Uppgift - skapa molnresurserna

Din Functions-app behöver distribueras till en Functions App-resurs i Azure, som ligger i den resursgrupp du skapade för din IoT Hub. Du behöver också skapa ett lagringskonto i Azure för att ersätta det emulerade som körs lokalt.

1. Kör följande kommando för att skapa ett lagringskonto:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Ersätt `<storage_name>` med ett namn för ditt lagringskonto. Detta måste vara globalt unikt eftersom det utgör en del av URL:en som används för att komma åt lagringskontot. Du kan bara använda små bokstäver och siffror för detta namn, inga andra tecken, och det är begränsat till 24 tecken. Använd något som `sms` och lägg till en unik identifierare i slutet, som några slumpmässiga ord eller ditt namn.

    `--sku Standard_LRS` väljer prissättningsnivån och väljer det billigaste allmänna kontot. Det finns ingen gratisnivå för lagring, och du betalar för det du använder. Kostnaderna är relativt låga, med den dyraste lagringen på mindre än 0,05 USD per månad per gigabyte lagrad.

    ✅ Läs mer om prissättning på [Azure Storage Account-prissättningssidan](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Kör följande kommando för att skapa en Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Ersätt `<location>` med platsen du använde när du skapade resursgruppen i föregående lektion.

    Ersätt `<storage_name>` med namnet på lagringskontot du skapade i föregående steg.

    Ersätt `<functions_app_name>` med ett unikt namn för din Functions App. Detta måste vara globalt unikt eftersom det utgör en del av en URL som kan användas för att komma åt Functions App. Använd något som `soil-moisture-sensor-` och lägg till en unik identifierare i slutet, som några slumpmässiga ord eller ditt namn.

    `--functions-version 3` anger vilken version av Azure Functions som ska användas. Version 3 är den senaste versionen.

    `--os-type Linux` instruerar Functions-runtime att använda Linux som operativsystem för att vara värd för dessa funktioner. Funktioner kan vara värd på Linux eller Windows, beroende på vilket programmeringsspråk som används. Python-appar stöds endast på Linux.

### Uppgift - ladda upp dina applikationsinställningar

När du utvecklade din Functions App lagrade du några inställningar i filen `local.settings.json` för anslutningssträngarna till din IoT Hub. Dessa måste skrivas till Application Settings i din Function App i Azure så att de kan användas av din kod.

> 🎓 Filen `local.settings.json` är endast för lokala utvecklingsinställningar och bör inte checkas in i versionshantering, som GitHub. När den distribueras till molnet används Application Settings. Application Settings är nyckel/värde-par som är värd i molnet och läses från miljövariabler antingen i din kod eller av runtime när den ansluter din kod till IoT Hub.

1. Kör följande kommando för att ställa in inställningen `IOT_HUB_CONNECTION_STRING` i Functions App Application Settings:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Ersätt `<functions_app_name>` med namnet du använde för din Functions App.

    Ersätt `<connection string>` med värdet av `IOT_HUB_CONNECTION_STRING` från din fil `local.settings.json`.

1. Upprepa steget ovan, men ställ in värdet för `REGISTRY_MANAGER_CONNECTION_STRING` till motsvarande värde från din fil `local.settings.json`.

När du kör dessa kommandon kommer de också att skriva ut en lista över alla Application Settings för funktionappen. Du kan använda detta för att kontrollera att dina värden är korrekt inställda.

> 💁 Du kommer att se ett värde som redan är inställt för `AzureWebJobsStorage`. I din fil `local.settings.json` var detta inställt på ett värde för att använda den lokala lagringsemulatorn. När du skapade Functions App skickar du lagringskontot som en parameter, och detta ställs in automatiskt i denna inställning.

### Uppgift - distribuera din Functions App till molnet

Nu när Functions App är redo kan din kod distribueras.

1. Kör följande kommando från VS Code-terminalen för att publicera din Functions App:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Ersätt `<functions_app_name>` med namnet du använde för din Functions App.

Koden kommer att paketeras och skickas till Functions App, där den distribueras och startas. Det kommer att finnas mycket konsolutdata, som slutar med en bekräftelse på distributionen och en lista över de funktioner som distribuerats. I detta fall kommer listan endast att innehålla triggern.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Se till att din IoT-enhet körs. Ändra fuktnivåerna genom att justera jordfukten eller flytta sensorn in och ut ur jorden. Du kommer att se reläet slås på och av när jordfukten ändras.

---

## 🚀 Utmaning

I föregående lektion hanterade du tidtagning för reläet genom att avregistrera dig från MQTT-meddelanden medan reläet var på och en kort stund efter att det stängts av. Du kan inte använda den här metoden här - du kan inte avregistrera din IoT Hub-trigger.

Fundera på olika sätt du skulle kunna hantera detta i din Functions App.

## Efterföreläsningsquiz

[Efterföreläsningsquiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Granskning & Självstudier

* Läs om serverlös databehandling på [Serverless Computing-sidan på Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Läs om att använda serverlös i Azure inklusive några fler exempel i [Go serverless for your IoT needs Azure-blogginlägget](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Lär dig mer om Azure Functions på [Azure Functions YouTube-kanalen](https://www.youtube.com/c/AzureFunctions)

## Uppgift

[Lägg till manuell reläkontroll](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.