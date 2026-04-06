# Migrera din växt till molnet

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-8.3f21f3c11159e6a0.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

Denna lektion ingick i [IoT för nybörjare Projekt 2 - Digital Agriculture-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) från [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Anslut din enhet till molnet med Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Quiz före föreläsningen

[Quiz före föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Introduktion

I den förra lektionen lärde du dig hur du ansluter din växt till en MQTT-broker och styrde ett relä från serverkod som kördes lokalt. Detta utgör kärnan i den typ av internetanslutna automatiska bevattningssystem som används från enskilda växter hemma till kommersiella gårdar.

IoT-enheten kommunicerade med en offentlig MQTT-broker som ett sätt att demonstrera principerna, men detta är inte det mest pålitliga eller säkra sättet. I denna lektion kommer du att lära dig om molnet och IoT-funktionerna som erbjuds av offentliga molntjänster. Du kommer också att lära dig hur du migrerar din växt till en av dessa molntjänster från den offentliga MQTT-brokern.

I denna lektion kommer vi att täcka:

* [Vad är molnet?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Skapa ett molnabonnemang](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Moln-IoT-tjänster](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Skapa en IoT-tjänst i molnet](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Kommunicera med IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Anslut din enhet till IoT-tjänsten](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Vad är molnet?

Innan molnet, när ett företag ville tillhandahålla tjänster till sina anställda (som databaser eller filhantering) eller till allmänheten (som webbplatser), byggde och drev de ett datacenter. Detta kunde vara allt från ett rum med ett fåtal datorer till en byggnad med många datorer. Företaget ansvarade för allt, inklusive:

* Köpa datorer
* Underhåll av hårdvara
* Ström och kylning
* Nätverk
* Säkerhet, inklusive att säkra byggnaden och mjukvaran på datorerna
* Installation och uppdatering av mjukvara

Detta kunde vara mycket dyrt, kräva en bred kompetens hos anställda och vara mycket långsamt att förändra vid behov. Till exempel, om en onlinebutik behövde planera för en hektisk julhandel, skulle de behöva planera månader i förväg för att köpa mer hårdvara, konfigurera den, installera den och installera mjukvaran för att hantera försäljningsprocessen. Efter julhandeln, när försäljningen minskade, skulle de ha datorer som de betalat för som står oanvända tills nästa hektiska period.

✅ Tror du att detta skulle göra det möjligt för företag att agera snabbt? Om en onlinebutik för kläder plötsligt blev populär på grund av att en kändis sågs bära deras kläder, skulle de kunna öka sin datorkapacitet tillräckligt snabbt för att hantera den plötsliga ökningen av beställningar?

### Någon annans dator

Molnet kallas ofta skämtsamt för "någon annans dator". Den ursprungliga idén var enkel - istället för att köpa datorer, hyr du någon annans dator. Någon annan, en molnleverantör, skulle hantera enorma datacenter. De skulle ansvara för att köpa och installera hårdvaran, hantera ström och kylning, nätverk, byggnadssäkerhet, hårdvaru- och mjukvaruuppdateringar, allt. Som kund hyr du de datorer du behöver, hyr fler när efterfrågan ökar och minskar antalet du hyr när efterfrågan sjunker. Dessa molndatacenter finns över hela världen.

![Ett Microsoft-molndatacenter](../../../../../translated_images/sv/azure-region-existing.73f704604f2aa6cb.webp)
![Planerad expansion av ett Microsoft-molndatacenter](../../../../../translated_images/sv/azure-region-planned-expansion.a5074a1e8af74f15.webp)

Dessa datacenter kan vara flera kvadratkilometer stora. Bilderna ovan togs för några år sedan vid ett Microsoft-molndatacenter och visar den ursprungliga storleken, tillsammans med en planerad expansion. Det område som röjts för expansionen är över 5 kvadratkilometer.

> 💁 Dessa datacenter kräver så stora mängder energi att vissa har egna kraftverk. På grund av sin storlek och investeringarna från molnleverantörerna är de vanligtvis mycket miljövänliga. De är mer effektiva än ett stort antal små datacenter, de drivs mestadels med förnybar energi, och molnleverantörer arbetar hårt för att minska avfall, minska vattenanvändning och återplantera skogar för att kompensera för de som skövlats för att ge plats åt datacenter. Du kan läsa mer om hur en molnleverantör arbetar med hållbarhet på [Azure hållbarhetssida](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Gör lite research: Läs om de stora molntjänsterna som [Azure från Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) eller [GCP från Google](https://cloud.google.com). Hur många datacenter har de, och var finns de i världen?

Att använda molnet håller kostnaderna nere för företag och gör det möjligt för dem att fokusera på det de gör bäst, medan molnexpertisen lämnas i leverantörens händer. Företag behöver inte längre hyra eller köpa datacenterutrymme, betala olika leverantörer för anslutning och ström eller anställa experter. Istället kan de betala en månatlig faktura till molnleverantören för att få allt skött.

Molnleverantören kan sedan använda stordriftsfördelar för att sänka kostnaderna, köpa datorer i bulk till lägre priser, investera i verktyg för att minska arbetsbelastningen för underhåll, och till och med designa och bygga sin egen hårdvara för att förbättra sitt molnerbjudande.

### Microsoft Azure

Azure är utvecklarmolnet från Microsoft, och det är det moln du kommer att använda i dessa lektioner. Videon nedan ger en kort översikt av Azure:

[![Översikt av Azure-video](../../../../../translated_images/sv/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Skapa ett molnabonnemang

För att använda tjänster i molnet behöver du registrera dig för ett abonnemang hos en molnleverantör. För denna lektion kommer du att registrera dig för ett Microsoft Azure-abonnemang. Om du redan har ett Azure-abonnemang kan du hoppa över denna uppgift. Abonnemangsdetaljerna som beskrivs här är korrekta vid tidpunkten för skrivandet, men kan ändras.

> 💁 Om du har tillgång till dessa lektioner via din skola kan du redan ha ett Azure-abonnemang tillgängligt för dig. Kontrollera med din lärare.

Det finns två olika typer av gratis Azure-abonnemang du kan registrera dig för:

* **Azure för studenter** - Detta är ett abonnemang utformat för studenter 18+. Du behöver inte ett kreditkort för att registrera dig, och du använder din skolmailadress för att verifiera att du är student. När du registrerar dig får du 100 USD att spendera på molnresurser, tillsammans med gratis tjänster inklusive en gratis version av en IoT-tjänst. Detta varar i 12 månader, och du kan förnya varje år så länge du förblir student.

* **Azure gratis abonnemang** - Detta är ett abonnemang för alla som inte är studenter. Du behöver ett kreditkort för att registrera dig för abonnemanget, men ditt kort kommer inte att debiteras, det används bara för att verifiera att du är en riktig människa, inte en bot. Du får 200 USD i kredit att använda under de första 30 dagarna på vilken tjänst som helst, tillsammans med gratis nivåer av Azure-tjänster. När din kredit har använts kommer ditt kort inte att debiteras om du inte konverterar till ett betalabonnemang.

> 💁 Microsoft erbjuder ett Azure för Studenter Starter-abonnemang för studenter under 18 år, men vid tidpunkten för skrivandet stöder detta inte några IoT-tjänster.

### Uppgift - registrera dig för ett gratis molnabonnemang

Om du är student och 18 år eller äldre kan du registrera dig för ett Azure för Studenter-abonnemang. Du behöver verifiera med en skolmailadress. Du kan göra detta på två sätt:

* Registrera dig för ett GitHub Student Developer Pack på [education.github.com/pack](https://education.github.com/pack). Detta ger dig tillgång till en rad verktyg och erbjudanden, inklusive GitHub och Microsoft Azure. När du registrerar dig för utvecklarpaketet kan du sedan aktivera Azure för Studenter-erbjudandet.

* Registrera dig direkt för ett Azure för Studenter-konto på [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Om din skolmailadress inte känns igen, skapa ett [ärende i detta repo](https://github.com/Microsoft/IoT-For-Beginners/issues) så ser vi om den kan läggas till i Azure för Studenter tillåtna lista.

Om du inte är student eller inte har en giltig skolmailadress kan du registrera dig för ett Azure Gratis-abonnemang.

* Registrera dig för ett Azure Gratis-abonnemang på [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Moln-IoT-tjänster

Den offentliga test-MQTT-brokern du har använt är ett utmärkt verktyg när du lär dig, men har ett antal nackdelar som ett verktyg att använda i en kommersiell miljö:

* Tillförlitlighet - det är en gratis tjänst utan garantier och kan stängas av när som helst
* Säkerhet - den är offentlig, så vem som helst kan lyssna på din telemetri eller skicka kommandon för att styra din hårdvara
* Prestanda - den är utformad för endast några få testmeddelanden och skulle inte klara av en stor mängd meddelanden som skickas
* Upptäckt - det finns inget sätt att veta vilka enheter som är anslutna

IoT-tjänster i molnet löser dessa problem. De underhålls av stora molnleverantörer som investerar mycket i tillförlitlighet och är redo att åtgärda eventuella problem som kan uppstå. De har säkerhet inbyggd för att hindra hackare från att läsa din data eller skicka falska kommandon. De är också högpresterande och kan hantera många miljoner meddelanden varje dag, med hjälp av molnet för att skala efter behov.

> 💁 Även om du betalar för dessa fördelar med en månadsavgift, erbjuder de flesta molnleverantörer en gratis version av sin IoT-tjänst med ett begränsat antal meddelanden per dag eller enheter som kan ansluta. Denna gratis version är vanligtvis mer än tillräcklig för en utvecklare att lära sig om tjänsten. I denna lektion kommer du att använda en gratis version.

IoT-enheter ansluter till en molntjänst antingen med hjälp av ett enhets-SDK (ett bibliotek som tillhandahåller kod för att arbeta med tjänstens funktioner) eller direkt via ett kommunikationsprotokoll som MQTT eller HTTP. Enhets-SDK är vanligtvis den enklaste vägen att ta eftersom det hanterar allt åt dig, såsom att veta vilka ämnen som ska publiceras eller prenumereras på och hur man hanterar säkerhet.

![Enheter ansluter till en tjänst med hjälp av ett enhets-SDK. Serverkod ansluter också till tjänsten via ett SDK](../../../../../translated_images/sv/iot-service-connectivity.7e873847921a5d6f.webp)

Din enhet kommunicerar sedan med andra delar av din applikation via denna tjänst - liknande hur du skickade telemetri och tog emot kommandon via MQTT. Detta görs vanligtvis med hjälp av ett tjänst-SDK eller ett liknande bibliotek. Meddelanden kommer från din enhet till tjänsten där andra komponenter i din applikation kan läsa dem, och meddelanden kan sedan skickas tillbaka till din enhet.

![Enheter utan en giltig hemlig nyckel kan inte ansluta till IoT-tjänsten](../../../../../translated_images/sv/iot-service-allowed-denied-connection.818b0063ac213fb8.webp)

Dessa tjänster implementerar säkerhet genom att känna till alla enheter som kan ansluta och skicka data, antingen genom att ha enheterna förregistrerade med tjänsten eller genom att ge enheterna hemliga nycklar eller certifikat som de kan använda för att registrera sig själva med tjänsten första gången de ansluter. Okända enheter kan inte ansluta; om de försöker avvisar tjänsten anslutningen och ignorerar meddelanden som skickas av dem.

✅ Gör lite research: Vad är nackdelen med att ha en öppen IoT-tjänst där vilken enhet eller kod som helst kan ansluta? Kan du hitta specifika exempel på hackare som utnyttjat detta?

Andra komponenter i din applikation kan ansluta till IoT-tjänsten och få information om alla enheter som är anslutna eller registrerade, och kommunicera med dem direkt, antingen individuellt eller i bulk.
💁 IoT-tjänster implementerar också ytterligare funktioner, och molnleverantörerna har extra tjänster och applikationer som kan kopplas till tjänsten. Till exempel, om du vill lagra alla telemetrimeddelanden som skickas av alla enheter i en databas, är det vanligtvis bara några få klick i molnleverantörens konfigurationsverktyg för att ansluta tjänsten till en databas och strömma in data.
## Skapa en IoT-tjänst i molnet

Nu när du har en Azure-prenumeration kan du registrera dig för en IoT-tjänst. IoT-tjänsten från Microsoft kallas Azure IoT Hub.

![Azure IoT Hub-logotypen](../../../../../translated_images/sv/azure-iot-hub-logo.28a19de76d0a1932.webp)

Videon nedan ger en kort översikt av Azure IoT Hub:

[![Översikt av Azure IoT Hub-video](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Klicka på bilden ovan för att titta på videon

✅ Ta en stund och gör lite research genom att läsa översikten av IoT Hub i [Microsoft IoT Hub-dokumentationen](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

De molntjänster som finns tillgängliga i Azure kan konfigureras via en webbaserad portal eller via ett kommandoradsgränssnitt (CLI). För denna uppgift kommer du att använda CLI.

### Uppgift - installera Azure CLI

För att använda Azure CLI måste det först installeras på din PC eller Mac.

1. Följ instruktionerna i [Azure CLI-dokumentationen](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) för att installera CLI.

1. Azure CLI stöder ett antal tillägg som lägger till funktioner för att hantera ett brett utbud av Azure-tjänster. Installera IoT-tillägget genom att köra följande kommando från din kommandorad eller terminal:

    ```sh
    az extension add --name azure-iot
    ```

1. Från din kommandorad eller terminal, kör följande kommando för att logga in på din Azure-prenumeration via Azure CLI.

    ```sh
    az login
    ```

    En webbsida kommer att öppnas i din standardwebbläsare. Logga in med det konto du använde för att registrera dig för din Azure-prenumeration. När du har loggat in kan du stänga webbläsarfliken.

1. Om du har flera Azure-prenumerationer, till exempel en som tillhandahålls av skolan och din egen Azure för Studenter-prenumeration, måste du välja vilken du vill använda. Kör följande kommando för att lista alla prenumerationer du har tillgång till:

    ```sh
    az account list --output table
    ```

    I utdata kommer du att se namnet på varje prenumeration tillsammans med dess `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    För att välja den prenumeration du vill använda, använd följande kommando:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Ersätt `<SubscriptionId>` med Id för den prenumeration du vill använda. Efter att ha kört detta kommando, kör kommandot för att lista dina konton igen. Du kommer att se att kolumnen `IsDefault` är markerad som `True` för den prenumeration du just har valt.

### Uppgift - skapa en resursgrupp

Azure-tjänster, såsom IoT Hub-instanser, virtuella maskiner, databaser eller AI-tjänster, kallas **resurser**. Varje resurs måste finnas i en **resursgrupp**, en logisk gruppering av en eller flera resurser.

> 💁 Genom att använda resursgrupper kan du hantera flera tjänster samtidigt. Till exempel, när du har avslutat alla lektioner för detta projekt kan du ta bort resursgruppen, och alla resurser i den kommer att tas bort automatiskt.

1. Det finns flera Azure-datacenter runt om i världen, uppdelade i regioner. När du skapar en Azure-resurs eller resursgrupp måste du ange var du vill att den ska skapas. Kör följande kommando för att få listan över platser:

    ```sh
    az account list-locations --output table
    ```

    Du kommer att se en lista över platser. Denna lista kommer att vara lång.

    > 💁 Vid tidpunkten för skrivandet finns det 65 platser du kan distribuera till.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Notera värdet från kolumnen `Name` för den region som är närmast dig. Du kan hitta regionerna på en karta på [Azure geographies-sidan](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Kör följande kommando för att skapa en resursgrupp som heter `soil-moisture-sensor`. Namn på resursgrupper måste vara unika i din prenumeration.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Ersätt `<location>` med platsen du valde i föregående steg.

### Uppgift - skapa en IoT Hub

Du kan nu skapa en IoT Hub-resurs i din resursgrupp.

1. Använd följande kommando för att skapa din IoT Hub-resurs:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Ersätt `<hub_name>` med ett namn för din hub. Detta namn måste vara globalt unikt - det vill säga att ingen annan IoT Hub skapad av någon annan kan ha samma namn. Detta namn används i en URL som pekar på hubben, så det måste vara unikt. Använd något som `soil-moisture-sensor-` och lägg till en unik identifierare i slutet, som några slumpmässiga ord eller ditt namn.

    Alternativet `--sku F1` anger att det ska använda en gratisnivå. Gratisnivån stöder 8 000 meddelanden per dag tillsammans med de flesta funktionerna i de fullständiga betalnivåerna.

    > 🎓 Olika prisnivåer för Azure-tjänster kallas nivåer. Varje nivå har olika kostnader och erbjuder olika funktioner eller datavolymer.

    > 💁 Om du vill lära dig mer om prissättning kan du kolla in [Azure IoT Hub-prisguiden](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Alternativet `--partition-count 2` definierar hur många dataströmmar IoT Hub stöder. Fler partitioner minskar dataspärrar när flera enheter läser och skriver från IoT Hub. Partitioner ligger utanför omfattningen av dessa lektioner, men detta värde måste ställas in för att skapa en gratisnivå IoT Hub.

    > 💁 Du kan bara ha en gratisnivå IoT Hub per prenumeration.

IoT Hub kommer att skapas. Det kan ta en minut eller så för att slutföra detta.

## Kommunicera med IoT Hub

I föregående lektion använde du MQTT och skickade meddelanden fram och tillbaka på olika ämnen, där de olika ämnena hade olika syften. Istället för att skicka meddelanden över olika ämnen har IoT Hub ett antal definierade sätt för enheten att kommunicera med hubben, eller för hubben att kommunicera med enheten.

> 💁 Under ytan kan denna kommunikation mellan IoT Hub och din enhet använda MQTT, HTTPS eller AMQP.

* Enhet-till-moln (D2C) meddelanden - dessa är meddelanden som skickas från en enhet till IoT Hub, såsom telemetri. De kan sedan läsas av IoT Hub av din applikationskod.

    > 🎓 Under ytan använder IoT Hub en Azure-tjänst som heter [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). När du skriver kod för att läsa meddelanden som skickas till hubben kallas dessa ofta för händelser.

* Moln-till-enhet (C2D) meddelanden - dessa är meddelanden som skickas från applikationskod, via en IoT Hub till en IoT-enhet.

* Direktmetodsförfrågningar - dessa är meddelanden som skickas från applikationskod via en IoT Hub till en IoT-enhet för att begära att enheten gör något, såsom att styra en aktuator. Dessa meddelanden kräver ett svar så att din applikationskod kan avgöra om det bearbetades framgångsrikt.

* Enhetstvillingar - dessa är JSON-dokument som hålls synkroniserade mellan enheten och IoT Hub, och används för att lagra inställningar eller andra egenskaper som antingen rapporteras av enheten eller ska ställas in på enheten (kallas önskade) av IoT Hub.

IoT Hub kan lagra meddelanden och direktmetodsförfrågningar under en konfigurerbar tidsperiod (standard är en dag), så om en enhet eller applikationskod tappar anslutningen kan den fortfarande hämta meddelanden som skickades medan den var offline efter att den återansluter. Enhetstvillingar hålls permanent i IoT Hub, så när som helst kan en enhet återansluta och få den senaste enhetstvillingen.

✅ Gör lite research: Läs mer om dessa meddelandetyper i [Vägledning för enhet-till-moln-kommunikation](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) och [Vägledning för moln-till-enhet-kommunikation](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) i IoT Hub-dokumentationen.

## Anslut din enhet till IoT-tjänsten

När hubben är skapad kan din IoT-enhet ansluta till den. Endast registrerade enheter kan ansluta till en tjänst, så du måste registrera din enhet först. När du registrerar den kan du få tillbaka en anslutningssträng som enheten kan använda för att ansluta. Denna anslutningssträng är enhetsspecifik och innehåller information om IoT Hub, enheten och en hemlig nyckel som gör att denna enhet kan ansluta.

> 🎓 En anslutningssträng är en generell term för en textbit som innehåller anslutningsdetaljer. Dessa används vid anslutning till IoT Hubs, databaser och många andra tjänster. De består vanligtvis av en identifierare för tjänsten, såsom en URL, och säkerhetsinformation såsom en hemlig nyckel. Dessa skickas till SDK:er för att ansluta till tjänsten.

> ⚠️ Anslutningssträngar bör hållas säkra! Säkerhet kommer att behandlas mer detaljerat i en framtida lektion.

### Uppgift - registrera din IoT-enhet

IoT-enheten kan registreras med din IoT Hub med hjälp av Azure CLI.

1. Kör följande kommando för att registrera en enhet:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Ersätt `<hub_name>` med namnet du använde för din IoT Hub.

    Detta kommer att skapa en enhet med ett ID av `soil-moisture-sensor`.

1. När din IoT-enhet ansluter till din IoT Hub med hjälp av SDK måste den använda en anslutningssträng som ger URL:en till hubben, tillsammans med en hemlig nyckel. Kör följande kommando för att få anslutningssträngen:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Ersätt `<hub_name>` med namnet du använde för din IoT Hub.

1. Spara anslutningssträngen som visas i utdata eftersom du kommer att behöva den senare.

### Uppgift - anslut din IoT-enhet till molnet

Följ den relevanta guiden för att ansluta din IoT-enhet till molnet:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Enkorts-dator - Raspberry Pi/Virtual IoT-enhet](single-board-computer-connect-hub.md)

### Uppgift - övervaka händelser

För tillfället kommer du inte att uppdatera din serverkod. Istället kan du använda Azure CLI för att övervaka händelser från din IoT-enhet.

1. Se till att din IoT-enhet körs och skickar telemetrivärden för jordfuktighet.

1. Kör följande kommando i din kommandorad eller terminal för att övervaka meddelanden som skickas till din IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Ersätt `<hub_name>` med namnet du använde för din IoT Hub.

    Du kommer att se meddelanden dyka upp i konsolutdata när de skickas av din IoT-enhet.

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

    Innehållet i `payload` kommer att matcha meddelandet som skickas av din IoT-enhet.

    > Vid tidpunkten för skrivandet fungerar inte tillägget `az iot` fullt ut på Apple Silicon. Om du använder en Apple Silicon-enhet måste du övervaka meddelandena på ett annat sätt, såsom med [Azure IoT Tools för Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Dessa meddelanden har ett antal egenskaper som automatiskt bifogas dem, såsom tidsstämpeln när de skickades. Dessa kallas *annoteringar*. För att visa alla meddelandeannoteringar, använd följande kommando:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Ersätt `<hub_name>` med namnet du använde för din IoT Hub.

    Du kommer att se meddelanden dyka upp i konsolutdata när de skickas av din IoT-enhet.

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

    Tidsvärdena i annoteringarna är i [UNIX-tid](https://wikipedia.org/wiki/Unix_time), vilket representerar antalet sekunder sedan midnatt den 1<sup>a</sup> januari 1970.

    Avsluta händelseövervakningen när du är klar.

### Uppgift - kontrollera din IoT-enhet

Du kan också använda Azure CLI för att anropa direktmetoder på din IoT-enhet.

1. Kör följande kommando i din kommandorad eller terminal för att anropa metoden `relay_on` på IoT-enheten:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Ersätt `
<hub_name>
` med namnet du använde för din IoT Hub.

    Detta skickar en direkt metodförfrågan för den metod som anges av `method-name`. Direkta metoder kan ta en nyttolast som innehåller data för metoden, och detta kan anges i parametern `method-payload` som JSON.

    Du kommer att se reläet slå på och motsvarande output från din IoT-enhet:

    ```output
    Direct method received -  relay_on
    ```

1. Upprepa steget ovan, men ställ in `--method-name` till `relay_off`. Du kommer att se reläet stängas av och motsvarande output från IoT-enheten.

---

## 🚀 Utmaning

Den kostnadsfria nivån för IoT Hub tillåter 8 000 meddelanden per dag. Koden du skrev skickar telemetrimeddelanden var tionde sekund. Hur många meddelanden per dag blir det om ett meddelande skickas var tionde sekund?

Fundera på hur ofta mätningar av jordfuktighet bör skickas? Hur kan du ändra din kod för att hålla dig inom den kostnadsfria nivån och kontrollera så ofta som behövs men inte för ofta? Vad händer om du vill lägga till en andra enhet?

## Quiz efter föreläsningen

[Quiz efter föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Granskning & Självstudier

IoT Hub SDK är öppen källkod för både Arduino och Python. I kodarkiven på GitHub finns ett antal exempel som visar hur man arbetar med olika funktioner i IoT Hub.

* Om du använder en Wio Terminal, kolla in [Arduino-exemplen på GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Om du använder en Raspberry Pi eller virtuell enhet, kolla in [Python-exemplen på GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Uppgift

[Lär dig om molntjänster](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.