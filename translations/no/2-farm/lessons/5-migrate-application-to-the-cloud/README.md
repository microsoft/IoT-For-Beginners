# Flytt applikasjonslogikken din til skyen

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-9.dfe99c8e891f48e1.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne leksjonen ble undervist som en del av [IoT for Beginners Project 2 - Digital Agriculture-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Kontroller IoT-enheten din med serverløs kode](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Introduksjon

I forrige leksjon lærte du hvordan du kobler overvåkingen av jordfuktighet og reléstyring til en skybasert IoT-tjeneste. Neste steg er å flytte serverkoden som styrer reléets timing til skyen. I denne leksjonen vil du lære hvordan du gjør dette ved hjelp av serverløse funksjoner.

I denne leksjonen dekker vi:

* [Hva er serverløst?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Opprett en serverløs applikasjon](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Opprett en IoT Hub-hendelsestrigger](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Send direkte metodeforespørsler fra serverløs kode](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Distribuer serverløs kode til skyen](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Hva er serverløst?

Serverløst, eller serverløs databehandling, innebærer å lage små kodeblokker som kjøres i skyen som respons på ulike typer hendelser. Når hendelsen oppstår, kjøres koden din, og den får data om hendelsen. Disse hendelsene kan komme fra mange forskjellige kilder, inkludert webforespørsler, meldinger lagt på en kø, endringer i data i en database, eller meldinger sendt til en IoT-tjeneste av IoT-enheter.

![Hendelser som sendes fra en IoT-tjeneste til en serverløs tjeneste, alle behandles samtidig av flere funksjoner som kjøres](../../../../../translated_images/no/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Hvis du har brukt databasetriggere før, kan du tenke på dette som det samme: kode som trigges av en hendelse, som å sette inn en rad.

![Når mange hendelser sendes samtidig, skalerer den serverløse tjenesten opp for å kjøre dem alle samtidig](../../../../../translated_images/no/serverless-scaling.f8c769adf0413fd1.webp)

Koden din kjøres kun når hendelsen oppstår, og det er ingenting som holder koden din aktiv på andre tidspunkter. Hendelsen oppstår, koden din lastes og kjøres. Dette gjør serverløst svært skalerbart – hvis mange hendelser oppstår samtidig, kan skyleverandøren kjøre funksjonen din så mange ganger som nødvendig samtidig på tvers av tilgjengelige servere. Ulempen med dette er at hvis du trenger å dele informasjon mellom hendelser, må du lagre den et sted, som i en database, i stedet for å lagre den i minnet.

Koden din skrives som en funksjon som tar detaljer om hendelsen som en parameter. Du kan bruke et bredt spekter av programmeringsspråk for å skrive disse serverløse funksjonene.

> 🎓 Serverløst kalles også Funksjoner som en tjeneste (FaaS), ettersom hver hendelsestrigger implementeres som en funksjon i kode.

Til tross for navnet bruker serverløst faktisk servere. Navnet kommer av at du som utvikler ikke trenger å bry deg om serverne som trengs for å kjøre koden din; alt du bryr deg om er at koden din kjøres som respons på en hendelse. Skyleverandøren har en serverløs *runtime* som administrerer tildeling av servere, nettverk, lagring, CPU, minne og alt annet som trengs for å kjøre koden din. Denne modellen betyr at du ikke betaler per server for tjenesten, siden det ikke er noen server. I stedet betaler du for tiden koden din kjører, og mengden minne som brukes.

> 💰 Serverløst er en av de billigste måtene å kjøre kode i skyen. For eksempel, på tidspunktet for skriving, lar en skyleverandør alle serverløse funksjoner kjøre til sammen 1 000 000 ganger per måned før de begynner å belaste deg, og etter det belaster de deg US$0,20 for hver 1 000 000 kjøringer. Når koden din ikke kjører, betaler du ingenting.

Som IoT-utvikler er den serverløse modellen ideell. Du kan skrive en funksjon som kalles som respons på meldinger sendt fra hvilken som helst IoT-enhet som er koblet til din skybaserte IoT-tjeneste. Koden din vil håndtere alle meldinger som sendes, men vil kun være aktiv når det er nødvendig.

✅ Se tilbake på koden du skrev som serverkode som lytter til meldinger over MQTT. Hvordan kan denne kjøre i skyen ved hjelp av serverløst? Hvordan tror du koden må endres for å støtte serverløs databehandling?

> 💁 Den serverløse modellen utvides til andre skytjenester i tillegg til å kjøre kode. For eksempel er serverløse databaser tilgjengelige i skyen med en serverløs prismodell der du betaler per forespørsel mot databasen, som en spørring eller innsetting, vanligvis basert på hvor mye arbeid som gjøres for å håndtere forespørselen. For eksempel vil en enkel seleksjon av én rad mot en primærnøkkel koste mindre enn en komplisert operasjon som kobler mange tabeller og returnerer tusenvis av rader.

## Opprett en serverløs applikasjon

Den serverløse databehandlingstjenesten fra Microsoft kalles Azure Functions.

![Azure Functions-logoen](../../../../../translated_images/no/azure-functions-logo.1cfc8e3204c9c44a.webp)

Den korte videoen nedenfor gir en oversikt over Azure Functions.

[![Azure Functions oversiktsvideo](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Klikk på bildet ovenfor for å se videoen.

✅ Ta deg tid til å gjøre litt research og les oversikten over Azure Functions i [Microsoft Azure Functions-dokumentasjonen](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

For å skrive Azure Functions starter du med en Azure Functions-app i språket du foretrekker. Azure Functions støtter Python, JavaScript, TypeScript, C#, F#, Java og Powershell. I denne leksjonen vil du lære hvordan du skriver en Azure Functions-app i Python.

> 💁 Azure Functions støtter også tilpassede håndterere, slik at du kan skrive funksjonene dine i hvilket som helst språk som støtter HTTP-forespørsler, inkludert eldre språk som COBOL.

Funksjonsapper består av én eller flere *triggere* – funksjoner som reagerer på hendelser. Du kan ha flere triggere i én funksjonsapp, som alle deler felles konfigurasjon. For eksempel kan du ha tilkoblingsdetaljer for din IoT Hub i konfigurasjonsfilen for funksjonsappen din, og alle funksjonene i appen kan bruke dette for å koble til og lytte etter hendelser.

### Oppgave – installer Azure Functions-verktøyene

> På tidspunktet for skriving fungerer ikke Azure Functions-verktøyene fullt ut på Apple Silicon med Python-prosjekter. Du må bruke en Intel-basert Mac, Windows-PC eller Linux-PC i stedet.

En flott funksjon med Azure Functions er at du kan kjøre dem lokalt. Den samme runtime som brukes i skyen kan kjøres på datamaskinen din, slik at du kan skrive kode som reagerer på IoT-meldinger og kjøre den lokalt. Du kan til og med feilsøke koden din mens hendelser håndteres. Når du er fornøyd med koden din, kan den distribueres til skyen.

Azure Functions-verktøyene er tilgjengelige som en CLI, kjent som Azure Functions Core Tools.

1. Installer Azure Functions Core Tools ved å følge instruksjonene i [Azure Functions Core Tools-dokumentasjonen](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Installer Azure Functions-utvidelsen for VS Code. Denne utvidelsen gir støtte for å opprette, feilsøke og distribuere Azure Functions. Se [Azure Functions-utvidelsesdokumentasjonen](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) for instruksjoner om hvordan du installerer denne utvidelsen i VS Code.

Når du distribuerer Azure Functions-appen din til skyen, trenger den å bruke en liten mengde skylagring for å lagre ting som applikasjonsfiler og loggfiler. Når du kjører funksjonsappen din lokalt, må du fortsatt koble til skylagring, men i stedet for å bruke faktisk skylagring, kan du bruke en lagringsemulator kalt [Azurite](https://github.com/Azure/Azurite). Denne kjører lokalt, men oppfører seg som skylagring.

> 🎓 I Azure er lagringen som Azure Functions bruker en Azure Storage Account. Disse kontoene kan lagre filer, blobs, data i tabeller eller data i køer. Du kan dele én lagringskonto mellom mange apper, som en funksjonsapp og en webapp.

1. Azurite er en Node.js-app, så du må installere Node.js. Du finner nedlastings- og installasjonsinstruksjoner på [Node.js-nettstedet](https://nodejs.org/). Hvis du bruker en Mac, kan du også installere det fra [Homebrew](https://formulae.brew.sh/formula/node).

1. Installer Azurite ved å bruke følgende kommando (`npm` er et verktøy som installeres når du installerer Node.js):

    ```sh
    npm install -g azurite
    ```

1. Opprett en mappe kalt `azurite` for Azurite å bruke til å lagre data:

    ```sh
    mkdir azurite
    ```

1. Kjør Azurite, og pass denne nye mappen til den:

    ```sh
    azurite --location azurite
    ```

    Azurite-lagringsemulatoren vil starte og være klar for den lokale funksjonsruntime å koble til.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Oppgave – opprett et Azure Functions-prosjekt

Azure Functions CLI kan brukes til å opprette en ny funksjonsapp.

1. Opprett en mappe for funksjonsappen din og naviger til den. Kall den `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Opprett et Python-virtuelt miljø inne i denne mappen:

    ```sh
    python3 -m venv .venv
    ```

1. Aktiver det virtuelle miljøet:

    * På Windows:
        * Hvis du bruker Command Prompt, eller Command Prompt gjennom Windows Terminal, kjør:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Hvis du bruker PowerShell, kjør:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * På macOS eller Linux, kjør:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Disse kommandoene bør kjøres fra samme sted som du kjørte kommandoen for å opprette det virtuelle miljøet. Du trenger aldri å navigere inn i `.venv`-mappen; du bør alltid kjøre aktiveringskommandoen og eventuelle kommandoer for å installere pakker eller kjøre kode fra mappen du var i da du opprettet det virtuelle miljøet.

1. Kjør følgende kommando for å opprette en funksjonsapp i denne mappen:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Dette vil opprette tre filer inne i den nåværende mappen:

    * `host.json` – dette JSON-dokumentet inneholder innstillinger for funksjonsappen din. Du trenger ikke å endre disse innstillingene.
    * `local.settings.json` – dette JSON-dokumentet inneholder innstillinger appen din vil bruke når den kjører lokalt, som tilkoblingsstrenger for din IoT Hub. Disse innstillingene er kun lokale og bør ikke legges til kildekodekontroll. Når du distribuerer appen til skyen, distribueres ikke disse innstillingene; i stedet lastes innstillingene dine fra applikasjonsinnstillinger. Dette vil bli dekket senere i denne leksjonen.
    * `requirements.txt` – dette er en [Pip-kravfil](https://pip.pypa.io/en/stable/user_guide/#requirements-files) som inneholder Pip-pakkene som trengs for å kjøre funksjonsappen din.

1. `local.settings.json`-filen har en innstilling for lagringskontoen som funksjonsappen vil bruke. Dette er som standard tomt, så det må settes. For å koble til Azurite-lokal lagringsemulator, sett denne verdien til følgende:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Installer nødvendige Pip-pakker ved hjelp av kravfilen:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 De nødvendige Pip-pakkene må være i denne filen, slik at når funksjonsappen distribueres til skyen, kan runtime sørge for at den installerer de riktige pakkene.

1. For å teste at alt fungerer som det skal, kan du starte funksjonsruntime. Kjør følgende kommando for å gjøre dette:

    ```sh
    func start
    ```

    Du vil se at runtime starter opp og rapporterer at den ikke har funnet noen jobbfunksjoner (triggere).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Hvis du får en brannmurvarsling, gi tilgang ettersom `func`-applikasjonen må kunne lese og skrive til nettverket ditt.
> ⚠️ Hvis du bruker macOS, kan det være advarsler i utdataene:
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
> Du kan ignorere disse så lenge Functions-appen starter korrekt og viser de kjørende funksjonene. Som nevnt i [dette spørsmålet på Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) kan de ignoreres.

1. Stopp Functions-appen ved å trykke `ctrl+c`.

1. Åpne den nåværende mappen i VS Code, enten ved å åpne VS Code og deretter åpne denne mappen, eller ved å kjøre følgende kommando:

    ```sh
    code .
    ```

    VS Code vil oppdage Functions-prosjektet ditt og vise en varsling som sier:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Varslingen](../../../../../translated_images/no/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Velg **Yes** fra denne varslingen.

1. Sørg for at det virtuelle Python-miljøet kjører i VS Code-terminalen. Avslutt det og start det på nytt om nødvendig.

## Opprett en IoT Hub-hendelsestrigger

Functions-appen er skallet for din serverløse kode. For å reagere på IoT Hub-hendelser kan du legge til en IoT Hub-trigger i denne appen. Denne triggeren må koble seg til strømmen av meldinger som sendes til IoT Hub og reagere på dem. For å få denne strømmen av meldinger må triggeren koble seg til IoT Hubs *event hub-kompatible endepunkt*.

IoT Hub er basert på en annen Azure-tjeneste kalt Azure Event Hubs. Event Hubs er en tjeneste som lar deg sende og motta meldinger, og IoT Hub utvider dette med funksjoner for IoT-enheter. Måten du kobler deg til for å lese meldinger fra IoT Hub er den samme som om du brukte Event Hubs.

✅ Gjør litt research: Les oversikten over Event Hubs i [Azure Event Hubs-dokumentasjonen](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Hvordan sammenlignes de grunnleggende funksjonene med IoT Hub?

For at en IoT-enhet skal koble seg til IoT Hub, må den bruke en hemmelig nøkkel som sikrer at kun tillatte enheter kan koble seg til. Det samme gjelder når du kobler deg til for å lese meldinger; koden din trenger en tilkoblingsstreng som inneholder en hemmelig nøkkel, sammen med detaljer om IoT Hub.

> 💁 Standard tilkoblingsstreng du får har **iothubowner**-tillatelser, som gir all kode som bruker den full tilgang til IoT Hub. Ideelt sett bør du koble deg til med det laveste nivået av tillatelser som trengs. Dette vil bli dekket i neste leksjon.

Når triggeren din har koblet seg til, vil koden inne i funksjonen bli kalt for hver melding som sendes til IoT Hub, uavhengig av hvilken enhet som sendte den. Triggeren vil få meldingen som en parameter.

### Oppgave - få tilkoblingsstrengen for Event Hub-kompatibelt endepunkt

1. Fra VS Code-terminalen, kjør følgende kommando for å få tilkoblingsstrengen for IoT Hubs Event Hub-kompatible endepunkt:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Erstatt `<hub_name>` med navnet du brukte for din IoT Hub.

1. I VS Code, åpne filen `local.settings.json`. Legg til følgende verdi inne i `Values`-seksjonen:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Erstatt `<connection string>` med verdien fra forrige steg. Du må legge til et komma etter linjen over for å gjøre dette til gyldig JSON.

### Oppgave - opprett en hendelsestrigger

Du er nå klar til å opprette hendelsestriggeren.

1. Fra VS Code-terminalen, kjør følgende kommando fra innsiden av `soil-moisture-trigger`-mappen:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Dette oppretter en ny funksjon kalt `iot-hub-trigger`. Triggeren vil koble seg til Event Hub-kompatibelt endepunkt på IoT Hub, så du kan bruke en Event Hub-trigger. Det finnes ingen spesifikk IoT Hub-trigger.

Dette vil opprette en mappe inne i `soil-moisture-trigger`-mappen kalt `iot-hub-trigger` som inneholder denne funksjonen. Denne mappen vil ha følgende filer:

* `__init__.py` - dette er Python-kodefilen som inneholder triggeren, ved å bruke standard Python-filnavnkonvensjon for å gjøre denne mappen til et Python-modul.

    Denne filen vil inneholde følgende kode:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Kjernen i triggeren er `main`-funksjonen. Det er denne funksjonen som kalles med hendelsene fra IoT Hub. Funksjonen har en parameter kalt `event` som inneholder en `EventHubEvent`. Hver gang en melding sendes til IoT Hub, kalles denne funksjonen med meldingen som `event`, sammen med egenskaper som er de samme som annotasjonene du så i forrige leksjon.

    Kjernen i denne funksjonen logger hendelsen.

* `function.json` - denne inneholder konfigurasjon for triggeren. Hovedkonfigurasjonen er i en seksjon kalt `bindings`. En binding er begrepet for en kobling mellom Azure Functions og andre Azure-tjenester. Denne funksjonen har en input-binding til en Event Hub - den kobler seg til en Event Hub og mottar data.

    > 💁 Du kan også ha output-bindings slik at utdataene fra en funksjon sendes til en annen tjeneste. For eksempel kan du legge til en output-binding til en database og returnere IoT Hub-hendelsen fra funksjonen, og den vil automatisk bli satt inn i databasen.

    ✅ Gjør litt research: Les om bindings i [Azure Functions triggers and bindings concepts-dokumentasjonen](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    `bindings`-seksjonen inkluderer konfigurasjon for bindingen. Verdiene av interesse er:

  * `"type": "eventHubTrigger"` - dette forteller funksjonen at den må lytte til hendelser fra en Event Hub
  * `"name": "events"` - dette er parameternavnet som skal brukes for Event Hub-hendelsene. Dette samsvarer med parameternavnet i `main`-funksjonen i Python-koden.
  * `"direction": "in"` - dette er en input-binding, dataene fra Event Hub kommer inn i funksjonen
  * `"connection": ""` - dette definerer navnet på innstillingen for å lese tilkoblingsstrengen fra. Når du kjører lokalt, vil denne innstillingen leses fra `local.settings.json`-filen.

    > 💁 Tilkoblingsstrengen kan ikke lagres i `function.json`-filen, den må leses fra innstillingene. Dette er for å forhindre at du ved et uhell eksponerer tilkoblingsstrengen.

1. På grunn av [en feil i Azure Functions-malen](https://github.com/Azure/azure-functions-templates/issues/1250), har `function.json` en feil verdi for feltet `cardinality`. Oppdater dette feltet fra `many` til `one`:

    ```json
    "cardinality": "one",
    ```

1. Oppdater verdien av `"connection"` i `function.json`-filen til å peke til den nye verdien du la til i `local.settings.json`-filen:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Husk - dette må peke til innstillingen, ikke inneholde den faktiske tilkoblingsstrengen.

1. Tilkoblingsstrengen inneholder verdien `eventHubName`, så verdien for dette i `function.json`-filen må tømmes. Oppdater denne verdien til en tom streng:

    ```json
    "eventHubName": "",
    ```

### Oppgave - kjør hendelsestriggeren

1. Sørg for at du ikke kjører IoT Hub-hendelsesmonitoren. Hvis denne kjører samtidig som Functions-appen, vil ikke Functions-appen kunne koble seg til og konsumere hendelser.

    > 💁 Flere apper kan koble seg til IoT Hub-endepunktene ved å bruke forskjellige *consumer groups*. Disse dekkes i en senere leksjon.

1. For å kjøre Functions-appen, kjør følgende kommando fra VS Code-terminalen:

    ```sh
    func start
    ```

    Functions-appen vil starte opp og oppdage `iot-hub-trigger`-funksjonen. Den vil deretter prosessere alle hendelser som allerede har blitt sendt til IoT Hub det siste døgnet.

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

    Hver kall til funksjonen vil være omgitt av en `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'`-blokk i utdataene, slik at du kan se hvor mange meldinger som ble prosessert i hvert funksjonskall.

1. Sørg for at IoT-enheten din kjører. Du vil se nye meldinger om jordfuktighet dukke opp i Functions-appen.

1. Stopp og start Functions-appen på nytt. Du vil se at den ikke prosesserer tidligere meldinger igjen, den vil kun prosessere nye meldinger.

> 💁 VS Code støtter også debugging av dine Functions. Du kan sette breakpoints ved å klikke på kanten ved starten av hver linje med kode, eller ved å plassere markøren på en linje med kode og velge *Run -> Toggle breakpoint*, eller trykke `F9`. Du kan starte debuggeren ved å velge *Run -> Start debugging*, trykke `F5`, eller velge *Run and debug*-panelet og velge **Start debugging**-knappen. Ved å gjøre dette kan du se detaljene for hendelsene som prosesseres.

#### Feilsøking

* Hvis du får følgende feil:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Sjekk at Azurite kjører og at du har satt `AzureWebJobsStorage` i `local.settings.json`-filen til `UseDevelopmentStorage=true`.

* Hvis du får følgende feil:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Sjekk at du har satt `cardinality` i `function.json`-filen til `one`.

* Hvis du får følgende feil:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Sjekk at du har satt `eventHubName` i `function.json`-filen til en tom streng.

## Send direkte metodeforespørsler fra serverløs kode

Så langt lytter Functions-appen din til meldinger fra IoT Hub ved å bruke Event Hub-kompatibelt endepunkt. Du må nå sende kommandoer til IoT-enheten. Dette gjøres ved å bruke en annen tilkobling til IoT Hub via *Registry Manager*. Registry Manager er et verktøy som lar deg se hvilke enheter som er registrert med IoT Hub, og kommunisere med disse enhetene ved å sende sky-til-enhet-meldinger, direkte metodeforespørsler eller oppdatere enhetens tvilling. Du kan også bruke det til å registrere, oppdatere eller slette IoT-enheter fra IoT Hub.

For å koble til Registry Manager trenger du en tilkoblingsstreng.

### Oppgave - få tilkoblingsstrengen for Registry Manager

1. For å få tilkoblingsstrengen, kjør følgende kommando:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Erstatt `<hub_name>` med navnet du brukte for din IoT Hub.

    Tilkoblingsstrengen blir forespurt for *ServiceConnect*-policyen ved å bruke parameteren `--policy-name service`. Når du forespør en tilkoblingsstreng, kan du spesifisere hvilke tillatelser den tilkoblingsstrengen skal tillate. ServiceConnect-policyen lar koden din koble seg til og sende meldinger til IoT-enheter.

    ✅ Gjør litt research: Les om de forskjellige policyene i [IoT Hub-tillatelsesdokumentasjonen](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. I VS Code, åpne filen `local.settings.json`. Legg til følgende verdi inne i `Values`-seksjonen:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Erstatt `<connection string>` med verdien fra forrige steg. Du må legge til et komma etter linjen over for å gjøre dette til gyldig JSON.

### Oppgave - send en direkte metodeforespørsel til en enhet

1. SDK-en for Registry Manager er tilgjengelig via en Pip-pakke. Legg til følgende linje i `requirements.txt`-filen for å legge til avhengigheten til denne pakken:

    ```sh
    azure-iot-hub
    ```

1. Sørg for at VS Code-terminalen har det virtuelle miljøet aktivert, og kjør følgende kommando for å installere Pip-pakkene:

    ```sh
    pip install -r requirements.txt
    ```

1. Legg til følgende imports i `__init__.py`-filen:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Dette importerer noen systembiblioteker, samt bibliotekene for å interagere med Registry Manager og sende direkte metodeforespørsler.

1. Fjern koden fra innsiden av `main`-metoden, men behold selve metoden.

1. I `main`-metoden, legg til følgende kode:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Denne koden henter kroppen til hendelsen som inneholder JSON-meldingen sendt av IoT-enheten.

    Den henter deretter enhets-ID-en fra annotasjonene som sendes med meldingen. Kroppen til hendelsen inneholder meldingen sendt som telemetri, mens `iothub_metadata`-ordboken inneholder egenskaper satt av IoT Hub, som enhets-ID-en til avsenderen og tidspunktet meldingen ble sendt.

    Denne informasjonen logges deretter. Du vil se denne loggingen i terminalen når du kjører Functions-appen lokalt.

1. Under dette, legg til følgende kode:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Denne koden henter jordfuktigheten fra meldingen. Den sjekker deretter jordfuktigheten, og avhengig av verdien, oppretter den en hjelpeklasse for den direkte metodeforespørselen for `relay_on` eller `relay_off` direkte metode. Metodeforespørselen trenger ikke en payload, så et tomt JSON-dokument sendes.

1. Under dette, legg til følgende kode:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Denne koden laster inn `REGISTRY_MANAGER_CONNECTION_STRING` fra `local.settings.json`-filen. Verdiene i denne filen gjøres tilgjengelige som miljøvariabler, og disse kan leses ved hjelp av `os.environ`-funksjonen, en funksjon som returnerer en ordbok med alle miljøvariablene.

> 💁 Når denne koden distribueres til skyen, vil verdiene i `local.settings.json`-filen bli satt som *Application Settings*, og disse kan leses fra miljøvariabler.

Koden oppretter deretter en instans av Registry Manager-hjelpeklassen ved hjelp av tilkoblingsstrengen.

1. Legg til følgende kode nedenfor:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Denne koden instruerer registry manager om å sende forespørselen om direkte metode til enheten som sendte telemetrien.

    > 💁 I versjonene av appen du opprettet i tidligere leksjoner ved bruk av MQTT, ble kommandoene for relékontroll sendt til alle enheter. Koden antok at du kun hadde én enhet. Denne versjonen av koden sender metodeforespørselen til én enkelt enhet, og vil derfor fungere hvis du har flere oppsett med fuktighetssensorer og reléer, og sender riktig metodeforespørsel til riktig enhet.

1. Kjør Functions-appen, og sørg for at IoT-enheten din sender data. Du vil se meldingene bli behandlet og forespørslene om direkte metode bli sendt. Flytt jordfuktighetssensoren inn og ut av jorden for å se verdiene endre seg og reléet slå seg av og på.

> 💁 Du finner denne koden i [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions)-mappen.

## Distribuer koden din til skyen

Koden din fungerer nå lokalt, så neste steg er å distribuere Functions App til skyen.

### Oppgave - opprett skyressursene

Functions-appen din må distribueres til en Functions App-ressurs i Azure, som ligger i Ressursgruppen du opprettet for IoT Hub. Du må også opprette en Storage Account i Azure for å erstatte den emulerte som kjører lokalt.

1. Kjør følgende kommando for å opprette en lagringskonto:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Erstatt `<storage_name>` med et navn for lagringskontoen din. Dette må være globalt unikt, da det utgjør en del av URL-en som brukes for å få tilgang til lagringskontoen. Du kan kun bruke små bokstaver og tall for dette navnet, ingen andre tegn, og det er begrenset til 24 tegn. Bruk noe som `sms` og legg til en unik identifikator på slutten, som noen tilfeldige ord eller navnet ditt.

    `--sku Standard_LRS` velger prisnivået, og velger den rimeligste generelle kontoen. Det finnes ingen gratis lagringsnivå, og du betaler for det du bruker. Kostnadene er relativt lave, med den dyreste lagringen på under 0,05 USD per måned per gigabyte lagret.

    ✅ Les mer om priser på [Azure Storage Account-prissiden](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Kjør følgende kommando for å opprette en Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Erstatt `<location>` med plasseringen du brukte da du opprettet Ressursgruppen i forrige leksjon.

    Erstatt `<storage_name>` med navnet på lagringskontoen du opprettet i forrige steg.

    Erstatt `<functions_app_name>` med et unikt navn for Functions App. Dette må være globalt unikt, da det utgjør en del av en URL som kan brukes for å få tilgang til Functions App. Bruk noe som `soil-moisture-sensor-` og legg til en unik identifikator på slutten, som noen tilfeldige ord eller navnet ditt.

    `--functions-version 3` angir versjonen av Azure Functions som skal brukes. Versjon 3 er den nyeste versjonen.

    `--os-type Linux` forteller Functions-runtime å bruke Linux som OS for å være vert for disse funksjonene. Funksjoner kan være vert på Linux eller Windows, avhengig av programmeringsspråket som brukes. Python-apper støttes kun på Linux.

### Oppgave - last opp applikasjonsinnstillingene dine

Da du utviklet Functions App, lagret du noen innstillinger i `local.settings.json`-filen for tilkoblingsstrengene til IoT Hub. Disse må skrives til Application Settings i Functions App i Azure slik at de kan brukes av koden din.

> 🎓 `local.settings.json`-filen er kun for lokale utviklingsinnstillinger, og disse bør ikke sjekkes inn i kildekodekontroll, som GitHub. Når de distribueres til skyen, brukes Application Settings. Application Settings er nøkkel/verdi-par som er vert i skyen og leses fra miljøvariabler enten i koden din eller av runtime når koden kobles til IoT Hub.

1. Kjør følgende kommando for å sette `IOT_HUB_CONNECTION_STRING`-innstillingen i Functions App Application Settings:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Erstatt `<functions_app_name>` med navnet du brukte for Functions App.

    Erstatt `<connection string>` med verdien av `IOT_HUB_CONNECTION_STRING` fra `local.settings.json`-filen din.

1. Gjenta steget ovenfor, men sett verdien av `REGISTRY_MANAGER_CONNECTION_STRING` til den tilsvarende verdien fra `local.settings.json`-filen din.

Når du kjører disse kommandoene, vil de også vise en liste over alle Application Settings for funksjonsappen. Du kan bruke dette til å sjekke at verdiene dine er satt riktig.

> 💁 Du vil se en verdi som allerede er satt for `AzureWebJobsStorage`. I `local.settings.json`-filen din var denne satt til en verdi for å bruke den lokale lagringsemulatoren. Når du opprettet Functions App, sendte du lagringskontoen som en parameter, og dette blir automatisk satt i denne innstillingen.

### Oppgave - distribuer Functions App til skyen

Nå som Functions App er klar, kan koden din distribueres.

1. Kjør følgende kommando fra VS Code-terminalen for å publisere Functions App:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Erstatt `<functions_app_name>` med navnet du brukte for Functions App.

Koden vil bli pakket og sendt til Functions App, hvor den vil bli distribuert og startet. Det vil være mye konsollutdata, som avsluttes med en bekreftelse på distribusjonen og en liste over de distribuerte funksjonene. I dette tilfellet vil listen kun inneholde triggeren.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Sørg for at IoT-enheten din kjører. Endre fuktighetsnivåene ved å justere jordfuktigheten, eller flytte sensoren inn og ut av jorden. Du vil se reléet slå seg av og på etter hvert som jordfuktigheten endres.

---

## 🚀 Utfordring

I forrige leksjon håndterte du timing for reléet ved å melde deg av MQTT-meldinger mens reléet var på, og en kort stund etter at det ble slått av. Du kan ikke bruke denne metoden her - du kan ikke melde deg av IoT Hub-triggeren.

Tenk på forskjellige måter du kan håndtere dette i Functions App.

## Quiz etter leksjonen

[Quiz etter leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Gjennomgang og selvstudium

* Les om serverløs databehandling på [Serverless Computing-siden på Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Les om bruk av serverløs i Azure, inkludert flere eksempler, på [Go serverless for your IoT needs Azure-blogginnlegget](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Lær mer om Azure Functions på [Azure Functions YouTube-kanalen](https://www.youtube.com/c/AzureFunctions)

## Oppgave

[Legg til manuell relékontroll](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.