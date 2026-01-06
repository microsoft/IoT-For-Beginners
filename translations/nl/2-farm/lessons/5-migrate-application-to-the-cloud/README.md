<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-27T21:16:51+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "nl"
}
-->
# Migreer je applicatielogica naar de cloud

![Een schetsmatige samenvatting van deze les](../../../../../translated_images/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.nl.jpg)

> Sketchnote door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

Deze les werd gegeven als onderdeel van de [IoT for Beginners Project 2 - Digital Agriculture serie](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) van de [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Bedien je IoT-apparaat met serverloze code](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Introductie

In de vorige les heb je geleerd hoe je de monitoring van bodemvochtigheid en relaisbesturing van je plant kunt verbinden met een cloudgebaseerde IoT-service. De volgende stap is om de servercode die de timing van het relais regelt naar de cloud te verplaatsen. In deze les leer je hoe je dit kunt doen met behulp van serverloze functies.

In deze les behandelen we:

* [Wat is serverloos?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Maak een serverloze applicatie](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Maak een IoT Hub-eventtrigger](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Verstuur directe methodeverzoeken vanuit serverloze code](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Implementeer je serverloze code in de cloud](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Wat is serverloos?

Serverloos, of serverloze computing, houdt in dat je kleine blokken code maakt die in de cloud worden uitgevoerd als reactie op verschillende soorten gebeurtenissen. Wanneer de gebeurtenis plaatsvindt, wordt je code uitgevoerd en krijgt het gegevens over de gebeurtenis mee. Deze gebeurtenissen kunnen afkomstig zijn van verschillende bronnen, zoals webverzoeken, berichten in een wachtrij, wijzigingen in gegevens in een database, of berichten die door IoT-apparaten naar een IoT-service worden gestuurd.

![Gebeurtenissen die worden verzonden van een IoT-service naar een serverloze service, allemaal tegelijkertijd verwerkt door meerdere functies](../../../../../translated_images/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.nl.png)

> 💁 Als je eerder database-triggers hebt gebruikt, kun je dit zien als iets vergelijkbaars: code die wordt geactiveerd door een gebeurtenis, zoals het invoegen van een rij.

![Wanneer veel gebeurtenissen tegelijkertijd worden verzonden, schaalt de serverloze service op om ze allemaal tegelijkertijd te verwerken](../../../../../translated_images/serverless-scaling.f8c769adf0413fd1.nl.png)

Je code wordt alleen uitgevoerd wanneer de gebeurtenis plaatsvindt; op andere momenten blijft je code inactief. De gebeurtenis vindt plaats, je code wordt geladen en uitgevoerd. Dit maakt serverloos zeer schaalbaar - als er veel gebeurtenissen tegelijkertijd plaatsvinden, kan de cloudprovider je functie zo vaak als nodig tegelijkertijd uitvoeren op de beschikbare servers. Het nadeel hiervan is dat als je informatie tussen gebeurtenissen wilt delen, je deze ergens moet opslaan, zoals in een database, in plaats van in het geheugen.

Je code wordt geschreven als een functie die details over de gebeurtenis als parameter ontvangt. Je kunt een breed scala aan programmeertalen gebruiken om deze serverloze functies te schrijven.

> 🎓 Serverloos wordt ook wel Functions as a Service (FaaS) genoemd, omdat elke gebeurtenistrigger wordt geïmplementeerd als een functie in code.

Ondanks de naam maakt serverloos wel gebruik van servers. De naamgeving komt voort uit het feit dat jij als ontwikkelaar je geen zorgen hoeft te maken over de servers die nodig zijn om je code uit te voeren; je hoeft alleen maar te weten dat je code wordt uitgevoerd als reactie op een gebeurtenis. De cloudprovider heeft een serverloze *runtime* die het beheer van servers, netwerken, opslag, CPU, geheugen en alles wat nodig is om je code uit te voeren, regelt. Dit model betekent dat je niet per server betaalt voor de service, omdat er geen server is. In plaats daarvan betaal je voor de tijd dat je code wordt uitgevoerd en de hoeveelheid geheugen die wordt gebruikt.

> 💰 Serverloos is een van de goedkoopste manieren om code in de cloud uit te voeren. Bijvoorbeeld, op het moment van schrijven, staat een cloudprovider toe dat al je serverloze functies samen 1.000.000 keer per maand worden uitgevoerd voordat ze kosten in rekening brengen. Daarna rekenen ze US$0,20 per 1.000.000 uitvoeringen. Wanneer je code niet wordt uitgevoerd, betaal je niets.

Als IoT-ontwikkelaar is het serverloze model ideaal. Je kunt een functie schrijven die wordt aangeroepen als reactie op berichten die worden verzonden door elk IoT-apparaat dat is verbonden met je cloud-gehoste IoT-service. Je code zal alle verzonden berichten verwerken, maar alleen actief zijn wanneer nodig.

✅ Kijk terug naar de code die je hebt geschreven als servercode die luistert naar berichten via MQTT. Hoe zou deze code in de cloud kunnen werken met serverloos? Hoe denk je dat de code moet worden aangepast om serverloze computing te ondersteunen?

> 💁 Het serverloze model wordt ook toegepast op andere cloudservices naast het uitvoeren van code. Bijvoorbeeld, serverloze databases zijn beschikbaar in de cloud met een serverloos prijsmodel waarbij je betaalt per verzoek dat tegen de database wordt gedaan, zoals een query of invoeging. De kosten zijn meestal gebaseerd op hoeveel werk nodig is om het verzoek te verwerken. Bijvoorbeeld, een eenvoudige selectie van één rij op basis van een primaire sleutel kost minder dan een complexe operatie waarbij veel tabellen worden samengevoegd en duizenden rijen worden geretourneerd.

## Maak een serverloze applicatie

De serverloze computing-service van Microsoft heet Azure Functions.

![Het Azure Functions-logo](../../../../../translated_images/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.nl.png)

De korte video hieronder geeft een overzicht van Azure Functions.

[![Azure Functions overzichtsvideo](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Klik op de afbeelding hierboven om de video te bekijken.

✅ Neem even de tijd om wat onderzoek te doen en lees het overzicht van Azure Functions in de [Microsoft Azure Functions documentatie](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Om Azure Functions te schrijven, begin je met een Azure Functions-app in de taal van jouw keuze. Azure Functions ondersteunt standaard Python, JavaScript, TypeScript, C#, F#, Java en Powershell. In deze les leer je hoe je een Azure Functions-app in Python schrijft.

> 💁 Azure Functions ondersteunt ook aangepaste handlers, zodat je je functies kunt schrijven in elke taal die HTTP-verzoeken ondersteunt, inclusief oudere talen zoals COBOL.

Functions-apps bestaan uit een of meer *triggers* - functies die reageren op gebeurtenissen. Je kunt meerdere triggers hebben binnen één Functions-app, die allemaal gemeenschappelijke configuratie delen. Bijvoorbeeld, in het configuratiebestand van je Functions-app kun je de verbindingsdetails van je IoT Hub opnemen, en alle functies in de app kunnen deze gebruiken om verbinding te maken en te luisteren naar gebeurtenissen.

### Taak - installeer de Azure Functions-tools

> Op het moment van schrijven werken de Azure Functions-codehulpmiddelen niet volledig op Apple Silicon met Python-projecten. Je zult een Intel-gebaseerde Mac, Windows-pc of Linux-pc moeten gebruiken.

Een geweldige functie van Azure Functions is dat je ze lokaal kunt uitvoeren. Dezelfde runtime die in de cloud wordt gebruikt, kan op je computer worden uitgevoerd, zodat je code kunt schrijven die reageert op IoT-berichten en deze lokaal kunt uitvoeren. Je kunt zelfs je code debuggen terwijl gebeurtenissen worden verwerkt. Zodra je tevreden bent met je code, kan deze worden geïmplementeerd in de cloud.

De Azure Functions-tools zijn beschikbaar als een CLI, bekend als de Azure Functions Core Tools.

1. Installeer de Azure Functions Core Tools door de instructies te volgen in de [Azure Functions Core Tools documentatie](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Installeer de Azure Functions-extensie voor VS Code. Deze extensie biedt ondersteuning voor het maken, debuggen en implementeren van Azure Functions. Raadpleeg de [Azure Functions-extensie documentatie](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) voor instructies over het installeren van deze extensie in VS Code.

Wanneer je je Azure Functions-app in de cloud implementeert, moet deze een kleine hoeveelheid cloudopslag gebruiken om dingen zoals applicatiebestanden en logbestanden op te slaan. Wanneer je je Functions-app lokaal uitvoert, moet je nog steeds verbinding maken met cloudopslag, maar in plaats van echte cloudopslag te gebruiken, kun je een opslagemulator genaamd [Azurite](https://github.com/Azure/Azurite) gebruiken. Dit werkt lokaal maar gedraagt zich als cloudopslag.

> 🎓 In Azure is de opslag die Azure Functions gebruikt een Azure Storage Account. Deze accounts kunnen bestanden, blobs, gegevens in tabellen of gegevens in wachtrijen opslaan. Je kunt één opslagaccount delen tussen meerdere apps, zoals een Functions-app en een webapp.

1. Azurite is een Node.js-app, dus je moet Node.js installeren. Je kunt de download- en installatie-instructies vinden op de [Node.js-website](https://nodejs.org/). Als je een Mac gebruikt, kun je het ook installeren via [Homebrew](https://formulae.brew.sh/formula/node).

1. Installeer Azurite met het volgende commando (`npm` is een tool die wordt geïnstalleerd wanneer je Node.js installeert):

    ```sh
    npm install -g azurite
    ```

1. Maak een map genaamd `azurite` voor Azurite om gegevens op te slaan:

    ```sh
    mkdir azurite
    ```

1. Start Azurite en geef deze nieuwe map door:

    ```sh
    azurite --location azurite
    ```

    De Azurite-opslagemulator wordt gestart en is klaar om verbinding te maken met de lokale Functions-runtime.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Taak - maak een Azure Functions-project

De Azure Functions CLI kan worden gebruikt om een nieuwe Functions-app te maken.

1. Maak een map voor je Functions-app en navigeer ernaar. Noem deze `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Maak een Python-virtuele omgeving in deze map:

    ```sh
    python3 -m venv .venv
    ```

1. Activeer de virtuele omgeving:

    * Op Windows:
        * Als je de Command Prompt of de Command Prompt via Windows Terminal gebruikt, voer je uit:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Als je PowerShell gebruikt, voer je uit:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Op macOS of Linux, voer uit:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Deze commando's moeten worden uitgevoerd vanuit dezelfde locatie waar je het commando hebt uitgevoerd om de virtuele omgeving te maken. Je hoeft nooit naar de `.venv`-map te navigeren; je moet altijd het activeringscommando en eventuele commando's om pakketten te installeren of code uit te voeren vanuit de map waar je was toen je de virtuele omgeving maakte.

1. Voer het volgende commando uit om een Functions-app in deze map te maken:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Dit zal drie bestanden in de huidige map maken:

    * `host.json` - dit JSON-document bevat instellingen voor je Functions-app. Je hoeft deze instellingen niet te wijzigen.
    * `local.settings.json` - dit JSON-document bevat instellingen die je app zou gebruiken bij lokaal uitvoeren, zoals verbindingsstrings voor je IoT Hub. Deze instellingen zijn alleen lokaal en mogen niet worden toegevoegd aan broncodebeheer. Wanneer je de app in de cloud implementeert, worden deze instellingen niet geïmplementeerd; in plaats daarvan worden je instellingen geladen uit applicatie-instellingen. Dit wordt later in deze les behandeld.
    * `requirements.txt` - dit is een [Pip requirements-bestand](https://pip.pypa.io/en/stable/user_guide/#requirements-files) dat de Pip-pakketten bevat die nodig zijn om je Functions-app uit te voeren.

1. Het `local.settings.json`-bestand heeft een instelling voor het opslagaccount dat de Functions-app zal gebruiken. Dit is standaard leeg, dus moet worden ingesteld. Om verbinding te maken met de Azurite lokale opslagemulator, stel je deze waarde in op het volgende:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Installeer de benodigde Pip-pakketten met behulp van het requirements-bestand:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 De vereiste Pip-pakketten moeten in dit bestand staan, zodat wanneer de Functions-app in de cloud wordt geïmplementeerd, de runtime ervoor kan zorgen dat de juiste pakketten worden geïnstalleerd.

1. Om te testen of alles correct werkt, kun je de Functions-runtime starten. Voer het volgende commando uit om dit te doen:

    ```sh
    func start
    ```

    Je zult zien dat de runtime start en meldt dat er geen jobfuncties (triggers) zijn gevonden.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Als je een firewallmelding krijgt, geef dan toegang omdat de `func` applicatie toegang nodig heeft om je netwerk te kunnen lezen en schrijven.
> ⚠️ Als je macOS gebruikt, kunnen er waarschuwingen in de uitvoer verschijnen:
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
> Je kunt deze negeren zolang de Functions-app correct start en de actieve functies weergeeft. Zoals vermeld in [deze vraag op Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) kan dit genegeerd worden.

1. Stop de Functions-app door `ctrl+c` in te drukken.

1. Open de huidige map in VS Code, door VS Code te openen en vervolgens deze map te openen, of door het volgende uit te voeren:

    ```sh
    code .
    ```

    VS Code detecteert je Functions-project en toont een melding met de tekst:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![De melding](../../../../../translated_images/vscode-azure-functions-init-notification.bd19b49229963edb.nl.png)

    Selecteer **Ja** in deze melding.

1. Zorg ervoor dat de Python virtuele omgeving actief is in de VS Code-terminal. Beëindig en herstart deze indien nodig.

## Maak een IoT Hub event trigger

De Functions-app is de basis van je serverloze code. Om te reageren op IoT Hub-evenementen kun je een IoT Hub-trigger toevoegen aan deze app. Deze trigger moet verbinding maken met de stroom van berichten die naar de IoT Hub worden verzonden en hierop reageren. Om deze stroom van berichten te ontvangen, moet je trigger verbinding maken met het *event hub compatibele eindpunt* van de IoT Hub.

IoT Hub is gebaseerd op een andere Azure-service genaamd Azure Event Hubs. Event Hubs is een service waarmee je berichten kunt verzenden en ontvangen. IoT Hub breidt dit uit met functies voor IoT-apparaten. De manier waarop je verbinding maakt om berichten van de IoT Hub te lezen, is hetzelfde als bij het gebruik van Event Hubs.

✅ Doe wat onderzoek: Lees het overzicht van Event Hubs in de [Azure Event Hubs-documentatie](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Hoe vergelijken de basisfuncties met IoT Hub?

Om een IoT-apparaat verbinding te laten maken met de IoT Hub, moet het een geheime sleutel gebruiken die ervoor zorgt dat alleen toegestane apparaten verbinding kunnen maken. Hetzelfde geldt voor het lezen van berichten; je code heeft een verbindingsreeks nodig die een geheime sleutel bevat, samen met details van de IoT Hub.

> 💁 De standaard verbindingsreeks die je krijgt, heeft **iothubowner**-rechten, wat betekent dat elke code die deze gebruikt volledige rechten heeft op de IoT Hub. Idealiter zou je verbinding moeten maken met het laagste niveau van rechten dat nodig is. Dit wordt behandeld in de volgende les.

Zodra je trigger is verbonden, wordt de code binnen de functie aangeroepen voor elk bericht dat naar de IoT Hub wordt verzonden, ongeacht welk apparaat het heeft verzonden. Het bericht wordt als parameter doorgegeven aan de trigger.

### Taak - verkrijg de Event Hub compatibele eindpunt verbindingsreeks

1. Voer vanuit de VS Code-terminal het volgende commando uit om de verbindingsreeks voor het Event Hub compatibele eindpunt van de IoT Hub te verkrijgen:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Vervang `<hub_name>` door de naam die je hebt gebruikt voor je IoT Hub.

1. Open in VS Code het bestand `local.settings.json`. Voeg de volgende extra waarde toe binnen de sectie `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Vervang `<connection string>` door de waarde uit de vorige stap. Je moet een komma toevoegen na de bovenstaande regel om dit geldige JSON te maken.

### Taak - maak een event trigger

Je bent nu klaar om de event trigger te maken.

1. Voer vanuit de VS Code-terminal het volgende commando uit vanuit de map `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Dit maakt een nieuwe functie genaamd `iot-hub-trigger`. De trigger maakt verbinding met het Event Hub compatibele eindpunt op de IoT Hub, zodat je een Event Hub-trigger kunt gebruiken. Er is geen specifieke IoT Hub-trigger.

Dit zal een map maken binnen de map `soil-moisture-trigger` genaamd `iot-hub-trigger` die deze functie bevat. Deze map zal de volgende bestanden bevatten:

* `__init__.py` - dit is het Python-codebestand dat de trigger bevat, met behulp van de standaard Python-bestandsnaamconventie om deze map om te zetten in een Python-module.

    Dit bestand bevat de volgende code:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    De kern van de trigger is de `main`-functie. Deze functie wordt aangeroepen met de gebeurtenissen van de IoT Hub. Deze functie heeft een parameter genaamd `event` die een `EventHubEvent` bevat. Elke keer dat een bericht naar de IoT Hub wordt verzonden, wordt deze functie aangeroepen en wordt dat bericht doorgegeven als de `event`, samen met eigenschappen die hetzelfde zijn als de annotaties die je in de vorige les hebt gezien.

    De kern van deze functie logt het event.

* `function.json` - dit bevat configuratie voor de trigger. De belangrijkste configuratie bevindt zich in een sectie genaamd `bindings`. Een binding is de term voor een verbinding tussen Azure Functions en andere Azure-services. Deze functie heeft een inputbinding naar een Event Hub - het maakt verbinding met een Event Hub en ontvangt gegevens.

    > 💁 Je kunt ook outputbindings hebben, zodat de output van een functie naar een andere service wordt verzonden. Bijvoorbeeld, je zou een outputbinding naar een database kunnen toevoegen en het IoT Hub-event van de functie retourneren, en het wordt automatisch in de database ingevoegd.

    ✅ Doe wat onderzoek: Lees meer over bindings in de [Azure Functions triggers en bindings concepten-documentatie](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    De sectie `bindings` bevat configuratie voor de binding. De interessante waarden zijn:

  * `"type": "eventHubTrigger"` - dit vertelt de functie dat het moet luisteren naar events van een Event Hub
  * `"name": "events"` - dit is de parameternaam die wordt gebruikt voor de Event Hub-events. Dit komt overeen met de parameternaam in de `main`-functie in de Python-code.
  * `"direction": "in"` - dit is een inputbinding, de gegevens van de Event Hub komen binnen in de functie
  * `"connection": ""` - dit definieert de naam van de instelling om de verbindingsreeks uit te lezen. Bij lokaal draaien, zal dit deze instelling lezen uit het bestand `local.settings.json`.

    > 💁 De verbindingsreeks kan niet worden opgeslagen in het bestand `function.json`, het moet worden gelezen uit de instellingen. Dit is om te voorkomen dat je per ongeluk je verbindingsreeks blootstelt.

1. Door [een bug in de Azure Functions-template](https://github.com/Azure/azure-functions-templates/issues/1250) heeft de `function.json` een onjuiste waarde voor het veld `cardinality`. Werk dit veld bij van `many` naar `one`:

    ```json
    "cardinality": "one",
    ```

1. Werk de waarde van `"connection"` in het bestand `function.json` bij zodat deze verwijst naar de nieuwe waarde die je hebt toegevoegd aan het bestand `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Onthoud - dit moet verwijzen naar de instelling, niet de daadwerkelijke verbindingsreeks bevatten.

1. De verbindingsreeks bevat de waarde `eventHubName`, dus de waarde hiervoor in het bestand `function.json` moet worden leeggemaakt. Werk deze waarde bij naar een lege string:

    ```json
    "eventHubName": "",
    ```

### Taak - voer de event trigger uit

1. Zorg ervoor dat je de IoT Hub event monitor niet uitvoert. Als deze tegelijkertijd met de Functions-app draait, kan de Functions-app geen verbinding maken en events consumeren.

    > 💁 Meerdere apps kunnen verbinding maken met de IoT Hub-eindpunten met behulp van verschillende *consumer groups*. Deze worden behandeld in een latere les.

1. Om de Functions-app uit te voeren, voer je het volgende commando uit vanuit de VS Code-terminal:

    ```sh
    func start
    ```

    De Functions-app zal starten en de functie `iot-hub-trigger` ontdekken. Het zal vervolgens alle events verwerken die in de afgelopen dag naar de IoT Hub zijn verzonden.

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

    Elke oproep naar de functie wordt omgeven door een blok `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` in de uitvoer, zodat je kunt zien hoeveel berichten in elke functieoproep zijn verwerkt.

1. Zorg ervoor dat je IoT-apparaat actief is. Je zult nieuwe berichten over bodemvochtigheid zien verschijnen in de Functions-app.

1. Stop en herstart de Functions-app. Je zult zien dat het geen eerdere berichten opnieuw verwerkt, maar alleen nieuwe berichten verwerkt.

> 💁 VS Code ondersteunt ook het debuggen van je Functions. Je kunt breakpoints instellen door op de rand bij het begin van elke regel code te klikken, of door de cursor op een regel code te plaatsen en *Run -> Toggle breakpoint* te selecteren, of door op `F9` te drukken. Je kunt de debugger starten door *Run -> Start debugging* te selecteren, op `F5` te drukken, of door het *Run and debug*-paneel te selecteren en op de knop **Start debugging** te klikken. Hiermee kun je de details van de verwerkte events bekijken.

#### Problemen oplossen

* Als je de volgende foutmelding krijgt:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Controleer of Azurite actief is en je de `AzureWebJobsStorage` in het bestand `local.settings.json` hebt ingesteld op `UseDevelopmentStorage=true`.

* Als je de volgende foutmelding krijgt:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Controleer of je de `cardinality` in het bestand `function.json` hebt ingesteld op `one`.

* Als je de volgende foutmelding krijgt:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Controleer of je de `eventHubName` in het bestand `function.json` hebt ingesteld op een lege string.

## Verstuur directe methodeverzoeken vanuit serverloze code

Tot nu toe luistert je Functions-app naar berichten van de IoT Hub via het Event Hub compatibele eindpunt. Nu moet je opdrachten naar het IoT-apparaat sturen. Dit wordt gedaan door een andere verbinding met de IoT Hub te gebruiken via de *Registry Manager*. De Registry Manager is een tool waarmee je kunt zien welke apparaten zijn geregistreerd bij de IoT Hub en kunt communiceren met die apparaten door cloud-naar-apparaatberichten, directe methodeverzoeken of het bijwerken van de device twin te verzenden. Je kunt het ook gebruiken om IoT-apparaten te registreren, bij te werken of te verwijderen uit de IoT Hub.

Om verbinding te maken met de Registry Manager, heb je een verbindingsreeks nodig.

### Taak - verkrijg de Registry Manager verbindingsreeks

1. Om de verbindingsreeks te verkrijgen, voer je het volgende commando uit:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Vervang `<hub_name>` door de naam die je hebt gebruikt voor je IoT Hub.

    De verbindingsreeks wordt opgevraagd voor het *ServiceConnect*-beleid met behulp van de parameter `--policy-name service`. Wanneer je een verbindingsreeks opvraagt, kun je specificeren welke rechten die verbindingsreeks toestaat. Het ServiceConnect-beleid staat je code toe om verbinding te maken en berichten naar IoT-apparaten te verzenden.

    ✅ Doe wat onderzoek: Lees meer over de verschillende beleidsregels in de [IoT Hub-rechten documentatie](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. Open in VS Code het bestand `local.settings.json`. Voeg de volgende extra waarde toe binnen de sectie `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Vervang `<connection string>` door de waarde uit de vorige stap. Je moet een komma toevoegen na de bovenstaande regel om dit geldige JSON te maken.

### Taak - verstuur een direct methodeverzoek naar een apparaat

1. De SDK voor de Registry Manager is beschikbaar via een Pip-pakket. Voeg de volgende regel toe aan het bestand `requirements.txt` om de afhankelijkheid van dit pakket toe te voegen:

    ```sh
    azure-iot-hub
    ```

1. Zorg ervoor dat de VS Code-terminal de virtuele omgeving geactiveerd heeft, en voer het volgende commando uit om de Pip-pakketten te installeren:

    ```sh
    pip install -r requirements.txt
    ```

1. Voeg de volgende imports toe aan het bestand `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Dit importeert enkele systeembibliotheken, evenals de bibliotheken om te communiceren met de Registry Manager en directe methodeverzoeken te verzenden.

1. Verwijder de code uit de `main`-methode, maar behoud de methode zelf.

1. Voeg de volgende code toe aan de `main`-methode:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Deze code haalt de body van het event op, die de JSON-bericht bevat dat door het IoT-apparaat is verzonden.

    Vervolgens haalt het de apparaat-ID op uit de annotaties die met het bericht zijn meegegeven. De body van het event bevat het bericht dat als telemetrie is verzonden, de `iothub_metadata`-dictionary bevat eigenschappen die door de IoT Hub zijn ingesteld, zoals de apparaat-ID van de afzender en de tijd waarop het bericht is verzonden.

    Deze informatie wordt vervolgens gelogd. Je zult deze logging zien in de terminal wanneer je de Functions-app lokaal uitvoert.

1. Voeg hieronder de volgende code toe:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Deze code haalt de bodemvochtigheid uit het bericht. Vervolgens controleert het de bodemvochtigheid en, afhankelijk van de waarde, maakt het een helperklasse voor het directe methodeverzoek voor de `relay_on` of `relay_off` directe methode. Het methodeverzoek heeft geen payload nodig, dus wordt een leeg JSON-document verzonden.

1. Voeg hieronder de volgende code toe:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Deze code laadt de `REGISTRY_MANAGER_CONNECTION_STRING` uit het bestand `local.settings.json`. De waarden in dit bestand worden beschikbaar gesteld als omgevingsvariabelen, en deze kunnen worden gelezen met behulp van de functie `os.environ`, een functie die een woordenboek retourneert van alle omgevingsvariabelen.

> 💁 Wanneer deze code naar de cloud wordt gedeployed, worden de waarden in het bestand `local.settings.json` ingesteld als *Application Settings*, en deze kunnen worden gelezen uit omgevingsvariabelen.

De code maakt vervolgens een instantie van de Registry Manager helperklasse aan met behulp van de verbindingsreeks.

1. Voeg hieronder de volgende code toe:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Deze code geeft de registry manager opdracht om het directe methodeverzoek te sturen naar het apparaat dat de telemetrie heeft verzonden.

    > 💁 In de versies van de app die je in eerdere lessen hebt gemaakt met MQTT, werden de relaisbesturingscommando's naar alle apparaten gestuurd. De code ging ervan uit dat je slechts één apparaat zou hebben. Deze versie van de code stuurt het methodeverzoek naar één enkel apparaat, zodat het werkt als je meerdere opstellingen hebt van vochtigheidssensoren en relais, en het juiste directe methodeverzoek naar het juiste apparaat stuurt.

1. Start de Functions-app en zorg ervoor dat je IoT-apparaat gegevens verzendt. Je zult zien dat de berichten worden verwerkt en de directe methodeverzoeken worden verzonden. Beweeg de bodemvochtigheidssensor in en uit de grond om de waarden te zien veranderen en het relais aan en uit te zien gaan.

> 💁 Je kunt deze code vinden in de map [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Deploy je serverloze code naar de cloud

Je code werkt nu lokaal, dus de volgende stap is om de Functions App naar de cloud te deployen.

### Taak - maak de cloudresources aan

Je Functions-app moet worden gedeployed naar een Functions App-resource in Azure, die zich bevindt binnen de Resource Group die je hebt aangemaakt voor je IoT Hub. Je hebt ook een Storage Account nodig dat in Azure wordt aangemaakt om de gesimuleerde opslag die je lokaal gebruikt te vervangen.

1. Voer de volgende opdracht uit om een opslagaccount aan te maken:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Vervang `<storage_name>` door een naam voor je opslagaccount. Deze moet wereldwijd uniek zijn, omdat het deel uitmaakt van de URL die wordt gebruikt om toegang te krijgen tot het opslagaccount. Je kunt alleen kleine letters en cijfers gebruiken voor deze naam, geen andere tekens, en het is beperkt tot 24 tekens. Gebruik iets als `sms` en voeg een unieke identificator toe, zoals willekeurige woorden of je naam.

    De `--sku Standard_LRS` selecteert de prijscategorie, waarbij de laagste kosten voor een algemeen opslagaccount worden gekozen. Er is geen gratis opslaglaag, en je betaalt voor wat je gebruikt. De kosten zijn relatief laag, met de duurste opslag minder dan US$0,05 per maand per opgeslagen gigabyte.

    ✅ Lees meer over de prijzen op de [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Voer de volgende opdracht uit om een Function App aan te maken:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Vervang `<location>` door de locatie die je hebt gebruikt bij het aanmaken van de Resource Group in de vorige les.

    Vervang `<storage_name>` door de naam van het opslagaccount dat je in de vorige stap hebt aangemaakt.

    Vervang `<functions_app_name>` door een unieke naam voor je Functions App. Deze moet wereldwijd uniek zijn, omdat het deel uitmaakt van een URL die kan worden gebruikt om toegang te krijgen tot de Functions App. Gebruik iets als `soil-moisture-sensor-` en voeg een unieke identificator toe, zoals willekeurige woorden of je naam.

    De optie `--functions-version 3` stelt de versie van Azure Functions in die moet worden gebruikt. Versie 3 is de nieuwste versie.

    De `--os-type Linux` geeft aan dat de Functions-runtime Linux moet gebruiken als besturingssysteem om deze functies te hosten. Functions kunnen worden gehost op Linux of Windows, afhankelijk van de gebruikte programmeertaal. Python-apps worden alleen ondersteund op Linux.

### Taak - upload je applicatie-instellingen

Toen je je Functions App ontwikkelde, heb je enkele instellingen opgeslagen in het bestand `local.settings.json` voor de verbindingsreeksen voor je IoT Hub. Deze moeten worden geschreven naar Application Settings in je Function App in Azure, zodat ze door je code kunnen worden gebruikt.

> 🎓 Het bestand `local.settings.json` is alleen bedoeld voor lokale ontwikkelinstellingen en mag niet worden opgenomen in broncodebeheer, zoals GitHub. Wanneer gedeployed naar de cloud, worden Application Settings gebruikt. Application Settings zijn sleutel/waarde-paren die in de cloud worden gehost en worden gelezen uit omgevingsvariabelen, hetzij in je code, hetzij door de runtime wanneer je code wordt verbonden met IoT Hub.

1. Voer de volgende opdracht uit om de instelling `IOT_HUB_CONNECTION_STRING` in te stellen in de Application Settings van de Functions App:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Vervang `<functions_app_name>` door de naam die je hebt gebruikt voor je Functions App.

    Vervang `<connection string>` door de waarde van `IOT_HUB_CONNECTION_STRING` uit je bestand `local.settings.json`.

1. Herhaal de bovenstaande stap, maar stel de waarde van `REGISTRY_MANAGER_CONNECTION_STRING` in op de overeenkomstige waarde uit je bestand `local.settings.json`.

Wanneer je deze opdrachten uitvoert, zullen ze ook een lijst met alle Application Settings voor de Functions App weergeven. Je kunt deze gebruiken om te controleren of je waarden correct zijn ingesteld.

> 💁 Je zult een waarde zien die al is ingesteld voor `AzureWebJobsStorage`. In je bestand `local.settings.json` was dit ingesteld op een waarde om de lokale opslagemulator te gebruiken. Wanneer je de Functions App aanmaakt, geef je het opslagaccount als parameter door, en dit wordt automatisch ingesteld in deze instelling.

### Taak - deploy je Functions App naar de cloud

Nu de Functions App klaar is, kan je code worden gedeployed.

1. Voer de volgende opdracht uit vanuit de VS Code-terminal om je Functions App te publiceren:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Vervang `<functions_app_name>` door de naam die je hebt gebruikt voor je Functions App.

De code wordt verpakt en verzonden naar de Functions App, waar deze wordt gedeployed en gestart. Er zal veel console-uitvoer zijn, eindigend met een bevestiging van de deployment en een lijst van de gedeployde functies. In dit geval zal de lijst alleen de trigger bevatten.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Zorg ervoor dat je IoT-apparaat actief is. Verander de vochtigheidsniveaus door de bodemvochtigheid aan te passen of de sensor in en uit de grond te bewegen. Je zult zien dat het relais aan en uit gaat naarmate de bodemvochtigheid verandert.

---

## 🚀 Uitdaging

In de vorige les beheerde je de timing voor het relais door je af te melden voor MQTT-berichten terwijl het relais aan stond, en voor een korte tijd nadat het was uitgeschakeld. Je kunt deze methode hier niet gebruiken - je kunt je IoT Hub-trigger niet afmelden.

Denk na over verschillende manieren waarop je dit in je Functions App zou kunnen aanpakken.

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Review & Zelfstudie

* Lees meer over serverless computing op de [Serverless Computing-pagina op Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Lees meer over het gebruik van serverless in Azure, inclusief enkele voorbeelden, in de [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Leer meer over Azure Functions op het [Azure Functions YouTube-kanaal](https://www.youtube.com/c/AzureFunctions)

## Opdracht

[Voeg handmatige relaisbesturing toe](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.