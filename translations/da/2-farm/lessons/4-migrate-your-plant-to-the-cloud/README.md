# Migrér din plante til skyen

![En sketchnote-oversigt over denne lektion](../../../../../translated_images/da/lesson-8.3f21f3c11159e6a0.webp)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

Denne lektion blev undervist som en del af [IoT for Beginners Projekt 2 - Digital Agriculture-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Forbind din enhed til skyen med Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Introduktion

I den sidste lektion lærte du, hvordan du forbinder din plante til en MQTT-broker og styrer et relæ fra serverkode, der kører lokalt. Dette udgør kernen i den slags internetforbundne automatiske vandingssystemer, der bruges fra individuelle planter derhjemme til kommercielle landbrug.

IoT-enheden kommunikerede med en offentlig MQTT-broker som en måde at demonstrere principperne på, men dette er ikke den mest pålidelige eller sikre metode. I denne lektion vil du lære om skyen og de IoT-funktioner, der tilbydes af offentlige cloud-tjenester. Du vil også lære, hvordan du migrerer din plante til en af disse cloud-tjenester fra den offentlige MQTT-broker.

I denne lektion dækker vi:

* [Hvad er skyen?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Opret et cloud-abonnement](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Cloud IoT-tjenester](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Opret en IoT-tjeneste i skyen](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Kommunikér med IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Forbind din enhed til IoT-tjenesten](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Hvad er skyen?

Før skyen, når en virksomhed ønskede at levere tjenester til deres medarbejdere (såsom databaser eller filopbevaring) eller til offentligheden (såsom hjemmesider), byggede og drev de et datacenter. Dette kunne variere fra et rum med et lille antal computere til en bygning med mange computere. Virksomheden skulle selv håndtere alt, herunder:

* Køb af computere
* Vedligeholdelse af hardware
* Strøm og køling
* Netværk
* Sikkerhed, herunder sikring af bygningen og softwaren på computerne
* Installation og opdatering af software

Dette kunne være meget dyrt, kræve en bred vifte af dygtige medarbejdere og være meget langsomt at ændre, når det var nødvendigt. For eksempel, hvis en onlinebutik skulle planlægge til en travl højsæson, skulle de planlægge måneder i forvejen for at købe mere hardware, konfigurere det, installere det og installere den nødvendige software til at håndtere salgsprocessen. Efter højsæsonen, når salget faldt igen, ville de stå tilbage med computere, de havde betalt for, som stod ubrugte indtil næste travle periode.

✅ Tror du, at dette ville give virksomheder mulighed for at handle hurtigt? Hvis en online tøjforhandler pludselig blev populær, fordi en kendis blev set i deres tøj, ville de så kunne øge deres computerkraft hurtigt nok til at håndtere den pludselige stigning i ordrer?

### En andens computer

Skyen omtales ofte spøgende som 'en andens computer'. Den oprindelige idé var simpel - i stedet for at købe computere, lejer du en andens computer. En anden, en cloud-udbyder, ville administrere enorme datacentre. De ville være ansvarlige for at købe og installere hardware, håndtere strøm og køling, netværk, bygningssikkerhed, hardware- og softwareopdateringer, alt. Som kunde ville du leje de computere, du har brug for, leje flere, når efterspørgslen stiger, og reducere antallet, når efterspørgslen falder. Disse cloud-datacentre findes over hele verden.

![Et Microsoft cloud-datacenter](../../../../../translated_images/da/azure-region-existing.73f704604f2aa6cb.webp)
![Planlagt udvidelse af et Microsoft cloud-datacenter](../../../../../translated_images/da/azure-region-planned-expansion.a5074a1e8af74f15.webp)

Disse datacentre kan være flere kvadratkilometer store. Billederne ovenfor blev taget for nogle år siden i et Microsoft cloud-datacenter og viser den oprindelige størrelse sammen med en planlagt udvidelse. Området, der er ryddet til udvidelsen, er over 5 kvadratkilometer.

> 💁 Disse datacentre kræver så store mængder strøm, at nogle har deres egne kraftværker. På grund af deres størrelse og cloud-udbydernes investeringer er de normalt meget miljøvenlige. De er mere effektive end et stort antal små datacentre, de kører hovedsageligt på vedvarende energi, og cloud-udbydere arbejder hårdt på at reducere affald, skære ned på vandforbrug og genplante skove for at kompensere for dem, der blev fældet for at give plads til at bygge datacentre. Du kan læse mere om, hvordan en cloud-udbyder arbejder med bæredygtighed på [Azure bæredygtighedssiden](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Lav noget research: Læs om de store cloud-udbydere som [Azure fra Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) eller [GCP fra Google](https://cloud.google.com). Hvor mange datacentre har de, og hvor i verden er de placeret?

Ved at bruge skyen kan virksomheder holde omkostningerne nede og fokusere på det, de er bedst til, mens cloud-ekspertisen overlades til udbyderen. Virksomheder behøver ikke længere at leje eller købe datacenterplads, betale forskellige leverandører for forbindelse og strøm eller ansætte eksperter. I stedet kan de betale én månedlig regning til cloud-udbyderen for at få alt håndteret.

Cloud-udbyderen kan derefter bruge stordriftsfordele til at reducere omkostningerne, købe computere i store mængder til lavere priser, investere i værktøjer til at reducere arbejdsbyrden for vedligeholdelse og endda designe og bygge deres egen hardware for at forbedre deres cloud-tilbud.

### Microsoft Azure

Azure er udviklerens cloud fra Microsoft, og det er den cloud, du vil bruge i disse lektioner. Videoen nedenfor giver en kort oversigt over Azure:

[![Oversigt over Azure-video](../../../../../translated_images/da/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Opret et cloud-abonnement

For at bruge tjenester i skyen skal du tilmelde dig et abonnement hos en cloud-udbyder. Til denne lektion skal du tilmelde dig et Microsoft Azure-abonnement. Hvis du allerede har et Azure-abonnement, kan du springe denne opgave over. De abonnementdetaljer, der beskrives her, er korrekte på tidspunktet for skrivningen, men kan ændre sig.

> 💁 Hvis du får adgang til disse lektioner gennem din skole, har du måske allerede et Azure-abonnement til rådighed. Tjek med din lærer.

Der er to forskellige typer gratis Azure-abonnementer, du kan tilmelde dig:

* **Azure for Studerende** - Dette er et abonnement designet til studerende på 18+. Du behøver ikke et kreditkort for at tilmelde dig, og du bruger din skole-e-mailadresse til at bekræfte, at du er studerende. Når du tilmelder dig, får du 100 USD til at bruge på cloud-ressourcer sammen med gratis tjenester, herunder en gratis version af en IoT-tjeneste. Dette varer i 12 måneder, og du kan forny det hvert år, du forbliver studerende.

* **Azure gratis abonnement** - Dette er et abonnement for alle, der ikke er studerende. Du skal bruge et kreditkort for at tilmelde dig abonnementet, men dit kort bliver ikke opkrævet; det bruges kun til at verificere, at du er et rigtigt menneske og ikke en bot. Du får 200 USD i kredit til at bruge i de første 30 dage på enhver tjeneste sammen med gratis niveauer af Azure-tjenester. Når din kredit er brugt op, bliver dit kort ikke opkrævet, medmindre du konverterer til et betalingsabonnement.

> 💁 Microsoft tilbyder et Azure for Students Starter-abonnement for studerende under 18 år, men på tidspunktet for skrivningen understøtter dette ikke IoT-tjenester.

### Opgave - tilmeld dig et gratis cloud-abonnement

Hvis du er studerende på 18+, kan du tilmelde dig et Azure for Studerende-abonnement. Du skal bekræfte med en skole-e-mailadresse. Dette kan gøres på to måder:

* Tilmeld dig en GitHub Student Developer Pack på [education.github.com/pack](https://education.github.com/pack). Dette giver dig adgang til en række værktøjer og tilbud, herunder GitHub og Microsoft Azure. Når du har tilmeldt dig udviklerpakken, kan du derefter aktivere Azure for Studerende-tilbuddet.

* Tilmeld dig direkte til en Azure for Studerende-konto på [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Hvis din skole-e-mailadresse ikke genkendes, skal du oprette en [issue i dette repo](https://github.com/Microsoft/IoT-For-Beginners/issues), så vi kan undersøge, om den kan tilføjes til Azure for Studerende-allow-listen.

Hvis du ikke er studerende, eller du ikke har en gyldig skole-e-mailadresse, kan du tilmelde dig et Azure gratis abonnement.

* Tilmeld dig et Azure gratis abonnement på [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Cloud IoT-tjenester

Den offentlige test-MQTT-broker, du har brugt, er et fantastisk værktøj til læring, men har en række ulemper som et værktøj til brug i en kommerciel sammenhæng:

* Pålidelighed - det er en gratis tjeneste uden garantier og kan slukkes når som helst
* Sikkerhed - den er offentlig, så enhver kunne lytte til din telemetri eller sende kommandoer til at styre din hardware
* Ydeevne - den er designet til kun et par testbeskeder og ville ikke kunne håndtere et stort antal beskeder, der sendes
* Opdagelse - der er ingen måde at vide, hvilke enheder der er forbundet

IoT-tjenester i skyen løser disse problemer. De vedligeholdes af store cloud-udbydere, der investerer massivt i pålidelighed og er klar til at løse eventuelle problemer, der måtte opstå. De har sikkerhed indbygget for at forhindre hackere i at læse dine data eller sende falske kommandoer. De er også højtydende og kan håndtere mange millioner beskeder hver dag ved at udnytte skyen til at skalere efter behov.

> 💁 Selvom du betaler for disse fordele med et månedligt gebyr, tilbyder de fleste cloud-udbydere en gratis version af deres IoT-tjeneste med et begrænset antal beskeder pr. dag eller enheder, der kan tilsluttes. Denne gratis version er normalt mere end nok for en udvikler til at lære om tjenesten. I denne lektion vil du bruge en gratis version.

IoT-enheder forbinder til en cloud-tjeneste enten ved hjælp af en enheds-SDK (et bibliotek, der leverer kode til at arbejde med tjenestens funktioner) eller direkte via en kommunikationsprotokol som MQTT eller HTTP. Enheds-SDK'en er normalt den nemmeste vej at tage, da den håndterer alt for dig, såsom at vide, hvilke emner der skal publiceres eller abonneres på, og hvordan man håndterer sikkerhed.

![Enheder forbinder til en tjeneste ved hjælp af en enheds-SDK. Serverkode forbinder også til tjenesten via en SDK](../../../../../translated_images/da/iot-service-connectivity.7e873847921a5d6f.webp)

Din enhed kommunikerer derefter med andre dele af din applikation via denne tjeneste - ligesom du sendte telemetri og modtog kommandoer via MQTT. Dette sker normalt ved hjælp af en service-SDK eller et lignende bibliotek. Beskeder kommer fra din enhed til tjenesten, hvor andre komponenter i din applikation derefter kan læse dem, og beskeder kan derefter sendes tilbage til din enhed.

![Enheder uden en gyldig hemmelig nøgle kan ikke forbinde til IoT-tjenesten](../../../../../translated_images/da/iot-service-allowed-denied-connection.818b0063ac213fb8.webp)

Disse tjenester implementerer sikkerhed ved at kende til alle de enheder, der kan forbinde og sende data, enten ved at have enhederne forudregistreret hos tjenesten eller ved at give enhederne hemmelige nøgler eller certifikater, som de kan bruge til at registrere sig selv hos tjenesten første gang, de forbinder. Ukendte enheder kan ikke forbinde; hvis de prøver, afviser tjenesten forbindelsen og ignorerer beskeder sendt af dem.

✅ Lav noget research: Hvad er ulempen ved at have en åben IoT-tjeneste, hvor enhver enhed eller kode kan forbinde? Kan du finde specifikke eksempler på hackere, der har udnyttet dette?

Andre komponenter i din applikation kan forbinde til IoT-tjenesten og lære om alle de enheder, der er forbundet eller registreret, og kommunikere med dem direkte enten samlet eller individuelt.
💁 IoT-tjenester implementerer også yderligere funktioner, og cloud-udbydere har ekstra tjenester og applikationer, der kan tilsluttes tjenesten. For eksempel, hvis du ønsker at gemme alle telemetribeskeder sendt af alle enheder i en database, kræver det som regel kun få klik i cloud-udbyderens konfigurationsværktøj for at forbinde tjenesten til en database og strømme dataene ind.
## Opret en IoT-tjeneste i skyen

Nu hvor du har et Azure-abonnement, kan du tilmelde dig en IoT-tjeneste. IoT-tjenesten fra Microsoft hedder Azure IoT Hub.

![Azure IoT Hub-logoet](../../../../../translated_images/da/azure-iot-hub-logo.28a19de76d0a1932.webp)

Videoen nedenfor giver en kort oversigt over Azure IoT Hub:

[![Oversigt over Azure IoT Hub-video](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Klik på billedet ovenfor for at se videoen

✅ Tag et øjeblik til at lave lidt research og læs oversigten over IoT Hub i [Microsoft IoT Hub-dokumentationen](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

De cloud-tjenester, der er tilgængelige i Azure, kan konfigureres via en webbaseret portal eller via en kommandolinjegrænseflade (CLI). Til denne opgave vil du bruge CLI.

### Opgave - installer Azure CLI

For at bruge Azure CLI skal det først installeres på din PC eller Mac.

1. Følg instruktionerne i [Azure CLI-dokumentationen](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) for at installere CLI.

1. Azure CLI understøtter en række udvidelser, der tilføjer funktioner til at administrere en bred vifte af Azure-tjenester. Installer IoT-udvidelsen ved at køre følgende kommando fra din kommandolinje eller terminal:

    ```sh
    az extension add --name azure-iot
    ```

1. Fra din kommandolinje eller terminal skal du køre følgende kommando for at logge ind på dit Azure-abonnement fra Azure CLI.

    ```sh
    az login
    ```

    En webside vil blive åbnet i din standardbrowser. Log ind med den konto, du brugte til at tilmelde dig dit Azure-abonnement. Når du er logget ind, kan du lukke browsertabben.

1. Hvis du har flere Azure-abonnementer, såsom et skoleabonnement og dit eget Azure for Students-abonnement, skal du vælge det, du vil bruge. Kør følgende kommando for at liste alle de abonnementer, du har adgang til:

    ```sh
    az account list --output table
    ```

    I outputtet vil du se navnet på hvert abonnement sammen med dets `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    For at vælge det abonnement, du vil bruge, skal du bruge følgende kommando:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Erstat `<SubscriptionId>` med Id'et for det abonnement, du vil bruge. Efter at have kørt denne kommando, skal du genkøre kommandoen for at liste dine konti. Du vil se, at kolonnen `IsDefault` er markeret som `True` for det abonnement, du lige har valgt.

### Opgave - opret en ressourcegruppe

Azure-tjenester, såsom IoT Hub-instanser, virtuelle maskiner, databaser eller AI-tjenester, kaldes **ressourcer**. Hver ressource skal placeres i en **Ressourcegruppe**, en logisk gruppering af en eller flere ressourcer.

> 💁 Ved at bruge ressourcegrupper kan du administrere flere tjenester på én gang. For eksempel, når du har afsluttet alle lektionerne for dette projekt, kan du slette ressourcegruppen, og alle ressourcerne i den vil automatisk blive slettet.

1. Der er flere Azure-datacentre rundt om i verden, opdelt i regioner. Når du opretter en Azure-ressource eller ressourcegruppe, skal du angive, hvor du vil have den oprettet. Kør følgende kommando for at få listen over placeringer:

    ```sh
    az account list-locations --output table
    ```

    Du vil se en liste over placeringer. Denne liste vil være lang.

    > 💁 På tidspunktet for skrivningen er der 65 placeringer, du kan implementere til.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Notér værdien fra kolonnen `Name` for den region, der er tættest på dig. Du kan finde regionerne på et kort på [Azure geographies-siden](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Kør følgende kommando for at oprette en ressourcegruppe kaldet `soil-moisture-sensor`. Navne på ressourcegrupper skal være unikke i dit abonnement.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Erstat `<location>` med den placering, du valgte i det foregående trin.

### Opgave - opret en IoT Hub

Du kan nu oprette en IoT Hub-ressource i din ressourcegruppe.

1. Brug følgende kommando til at oprette din IoT Hub-ressource:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Erstat `<hub_name>` med et navn til din hub. Dette navn skal være globalt unikt - det vil sige, at ingen anden IoT Hub oprettet af nogen kan have det samme navn. Dette navn bruges i en URL, der peger på hubben, så det skal være unikt. Brug noget som `soil-moisture-sensor-` og tilføj en unik identifikator på slutningen, som nogle tilfældige ord eller dit navn.

    Muligheden `--sku F1` angiver, at der skal bruges en gratis tier. Den gratis tier understøtter 8.000 beskeder om dagen sammen med de fleste funktioner fra de fuldt betalte tiers.

    > 🎓 Forskellige prisniveauer for Azure-tjenester kaldes tiers. Hver tier har en forskellig pris og tilbyder forskellige funktioner eller datamængder.

    > 💁 Hvis du vil lære mere om priser, kan du tjekke [Azure IoT Hub-prisguiden](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Muligheden `--partition-count 2` definerer, hvor mange datastrømme IoT Hub understøtter. Flere partitioner reducerer datablokering, når flere enheder læser og skriver fra IoT Hub. Partitioner er uden for omfanget af disse lektioner, men denne værdi skal indstilles for at oprette en gratis tier IoT Hub.

    > 💁 Du kan kun have én gratis tier IoT Hub pr. abonnement.

IoT Hub vil blive oprettet. Det kan tage et minut eller to at fuldføre.

## Kommuniker med IoT Hub

I den forrige lektion brugte du MQTT og sendte beskeder frem og tilbage på forskellige emner, hvor de forskellige emner havde forskellige formål. I stedet for at sende beskeder over forskellige emner har IoT Hub en række definerede måder for enheden at kommunikere med hubben eller for hubben at kommunikere med enheden.

> 💁 Under overfladen kan denne kommunikation mellem IoT Hub og din enhed bruge MQTT, HTTPS eller AMQP.

* Enhed-til-sky (D2C) beskeder - dette er beskeder sendt fra en enhed til IoT Hub, såsom telemetri. De kan derefter læses fra IoT Hub af din applikationskode.

    > 🎓 Under overfladen bruger IoT Hub en Azure-tjeneste kaldet [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Når du skriver kode for at læse beskeder sendt til hubben, kaldes disse ofte begivenheder.

* Sky-til-enhed (C2D) beskeder - dette er beskeder sendt fra applikationskode via en IoT Hub til en IoT-enhed.

* Direkte metodeanmodninger - dette er beskeder sendt fra applikationskode via en IoT Hub til en IoT-enhed for at anmode om, at enheden gør noget, såsom at kontrollere en aktuator. Disse beskeder kræver et svar, så din applikationskode kan se, om det blev behandlet korrekt.

* Enhedstvillinger - dette er JSON-dokumenter, der holdes synkroniseret mellem enheden og IoT Hub og bruges til at gemme indstillinger eller andre egenskaber, enten rapporteret af enheden eller som skal indstilles på enheden (kendt som ønsket) af IoT Hub.

IoT Hub kan gemme beskeder og direkte metodeanmodninger i en konfigurerbar periode (standard er én dag), så hvis en enhed eller applikationskode mister forbindelsen, kan den stadig hente beskeder sendt, mens den var offline, efter den genopretter forbindelsen. Enhedstvillinger gemmes permanent i IoT Hub, så en enhed til enhver tid kan genoprette forbindelsen og få den nyeste enhedstvilling.

✅ Lav lidt research: Læs mere om disse beskedtyper i [Device-to-cloud communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) og [Cloud-to-device communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) i IoT Hub-dokumentationen.

## Tilslut din enhed til IoT-tjenesten

Når hubben er oprettet, kan din IoT-enhed tilslutte sig den. Kun registrerede enheder kan tilslutte sig en tjeneste, så du skal registrere din enhed først. Når du registrerer, kan du få en forbindelsesstreng tilbage, som enheden kan bruge til at tilslutte sig. Denne forbindelsesstreng er enhedsspecifik og indeholder information om IoT Hub, enheden og en hemmelig nøgle, der giver denne enhed mulighed for at tilslutte sig.

> 🎓 En forbindelsesstreng er et generelt udtryk for et stykke tekst, der indeholder forbindelsesdetaljer. Disse bruges, når man tilslutter sig IoT Hubs, databaser og mange andre tjenester. De består normalt af en identifikator for tjenesten, såsom en URL, og sikkerhedsoplysninger såsom en hemmelig nøgle. Disse gives til SDK'er for at tilslutte sig tjenesten.

> ⚠️ Forbindelsesstrenge bør holdes sikre! Sikkerhed vil blive dækket mere detaljeret i en fremtidig lektion.

### Opgave - registrer din IoT-enhed

IoT-enheden kan registreres med din IoT Hub ved hjælp af Azure CLI.

1. Kør følgende kommando for at registrere en enhed:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Erstat `<hub_name>` med det navn, du brugte til din IoT Hub.

    Dette vil oprette en enhed med et ID af `soil-moisture-sensor`.

1. Når din IoT-enhed tilslutter sig din IoT Hub ved hjælp af SDK'en, skal den bruge en forbindelsesstreng, der giver URL'en til hubben sammen med en hemmelig nøgle. Kør følgende kommando for at få forbindelsesstrengen:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Erstat `<hub_name>` med det navn, du brugte til din IoT Hub.

1. Gem forbindelsesstrengen, der vises i outputtet, da du vil få brug for den senere.

### Opgave - tilslut din IoT-enhed til skyen

Arbejd dig igennem den relevante guide for at tilslutte din IoT-enhed til skyen:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-connect-hub.md)

### Opgave - overvåg begivenheder

For nu vil du ikke opdatere din serverkode. I stedet kan du bruge Azure CLI til at overvåge begivenheder fra din IoT-enhed.

1. Sørg for, at din IoT-enhed kører og sender jordfugtigheds-telemetriværdier.

1. Kør følgende kommando i din kommandoprompt eller terminal for at overvåge beskeder sendt til din IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Erstat `<hub_name>` med det navn, du brugte til din IoT Hub.

    Du vil se beskeder dukke op i konsoloutputtet, efterhånden som de sendes af din IoT-enhed.

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

    Indholdet af `payload` vil matche beskeden sendt af din IoT-enhed.

    > På tidspunktet for skrivningen fungerer `az iot`-udvidelsen ikke fuldt ud på Apple Silicon. Hvis du bruger en Apple Silicon-enhed, skal du overvåge beskederne på en anden måde, såsom ved at bruge [Azure IoT Tools for Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Disse beskeder har en række egenskaber knyttet til dem automatisk, såsom tidsstemplet de blev sendt. Disse kaldes *annoteringer*. For at se alle beskedannoteringerne skal du bruge følgende kommando:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Erstat `<hub_name>` med det navn, du brugte til din IoT Hub.

    Du vil se beskeder dukke op i konsoloutputtet, efterhånden som de sendes af din IoT-enhed.

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

    Tidsværdierne i annoteringerne er i [UNIX-tid](https://wikipedia.org/wiki/Unix_time), der repræsenterer antallet af sekunder siden midnat den 1. januar 1970.

    Afslut begivenhedsovervågningen, når du er færdig.

### Opgave - kontrolér din IoT-enhed

Du kan også bruge Azure CLI til at kalde direkte metoder på din IoT-enhed.

1. Kør følgende kommando i din kommandoprompt eller terminal for at kalde metoden `relay_on` på IoT-enheden:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Erstat `
<hub_name>
` med det navn, du brugte til din IoT Hub.

    Dette sender en direkte metodeanmodning for den metode, der er angivet af `method-name`. Direkte metoder kan tage en payload, der indeholder data til metoden, og dette kan specificeres i parameteren `method-payload` som JSON.

    Du vil se relæet tænde, og den tilsvarende output fra din IoT-enhed:

    ```output
    Direct method received -  relay_on
    ```

1. Gentag ovenstående trin, men sæt `--method-name` til `relay_off`. Du vil se relæet slukke og den tilsvarende output fra IoT-enheden.

---

## 🚀 Udfordring

Den gratis version af IoT Hub tillader 8.000 beskeder om dagen. Den kode, du skrev, sender telemetribeskeder hvert 10. sekund. Hvor mange beskeder om dagen svarer det til, hvis der sendes én besked hvert 10. sekund?

Tænk over, hvor ofte målinger af jordfugtighed bør sendes? Hvordan kan du ændre din kode for at holde dig inden for den gratis version og tjekke så ofte som nødvendigt, men ikke for ofte? Hvad hvis du ønskede at tilføje en anden enhed?

## Quiz efter forelæsning

[Quiz efter forelæsning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Gennemgang & Selvstudie

IoT Hub SDK er open source for både Arduino og Python. I kode-repos på GitHub er der en række eksempler, der viser, hvordan man arbejder med forskellige IoT Hub-funktioner.

* Hvis du bruger en Wio Terminal, kan du tjekke [Arduino-eksemplerne på GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Hvis du bruger en Raspberry Pi eller en virtuel enhed, kan du tjekke [Python-eksemplerne på GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Opgave

[Lær om cloud-tjenester](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.