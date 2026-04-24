# Migrer planten din til skyen

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-8.3f21f3c11159e6a0.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne leksjonen ble undervist som en del av [IoT for Beginners Prosjekt 2 - Digital Agriculture-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Koble enheten din til skyen med Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Introduksjon

I forrige leksjon lærte du hvordan du kobler planten din til en MQTT-broker og kontrollerer et relé fra serverkode som kjører lokalt. Dette utgjør kjernen i den typen internett-tilkoblede automatiserte vanningssystemer som brukes fra individuelle planter hjemme til kommersielle gårder.

IoT-enheten kommuniserte med en offentlig MQTT-broker for å demonstrere prinsippene, men dette er ikke den mest pålitelige eller sikre måten. I denne leksjonen vil du lære om skyen og IoT-funksjonene som tilbys av offentlige skytjenester. Du vil også lære hvordan du migrerer planten din til en av disse skytjenestene fra den offentlige MQTT-brokeren.

I denne leksjonen dekker vi:

* [Hva er skyen?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Opprett et skyabonnement](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Skybaserte IoT-tjenester](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Opprett en IoT-tjeneste i skyen](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Kommuniser med IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Koble enheten din til IoT-tjenesten](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Hva er skyen?

Før skyen, når en bedrift ønsket å tilby tjenester til sine ansatte (som databaser eller fil-lagring) eller til offentligheten (som nettsider), måtte de bygge og drifte et datasenter. Dette kunne variere fra et rom med et lite antall datamaskiner til en bygning med mange datamaskiner. Bedriften måtte administrere alt, inkludert:

* Kjøp av datamaskiner
* Vedlikehold av maskinvare
* Strøm og kjøling
* Nettverk
* Sikkerhet, inkludert sikring av bygningen og programvaren på datamaskinene
* Installasjon og oppdatering av programvare

Dette kunne være svært kostbart, kreve et bredt spekter av dyktige ansatte, og være veldig tregt å endre når det var nødvendig. For eksempel, hvis en nettbutikk måtte planlegge for en travel høytidssesong, måtte de planlegge måneder i forveien for å kjøpe mer maskinvare, konfigurere den, installere den og installere programvaren for å kjøre salgsprosessen. Etter høytidssesongen, når salget gikk tilbake til normalen, ville de sitte igjen med datamaskiner de hadde betalt for som sto ubrukt til neste travle sesong.

✅ Tror du dette ville tillate bedrifter å bevege seg raskt? Hvis en nettbutikk for klær plutselig ble populær fordi en kjendis ble sett i klærne deres, ville de kunne øke datakraften raskt nok til å håndtere den plutselige økningen i bestillinger?

### Noen andres datamaskin

Skyen blir ofte spøkefullt referert til som "noen andres datamaskin". Den opprinnelige ideen var enkel – i stedet for å kjøpe datamaskiner, leier du noen andres datamaskin. En annen part, en skyleverandør, ville administrere enorme datasentre. De ville være ansvarlige for å kjøpe og installere maskinvaren, administrere strøm og kjøling, nettverk, bygningssikkerhet, maskinvare- og programvareoppdateringer, alt. Som kunde ville du leie de datamaskinene du trenger, leie flere når etterspørselen øker, og redusere antallet du leier hvis etterspørselen synker. Disse datasentrene finnes over hele verden.

![Et Microsoft sky-datasenter](../../../../../translated_images/no/azure-region-existing.73f704604f2aa6cb.webp)
![Planlagt utvidelse av et Microsoft sky-datasenter](../../../../../translated_images/no/azure-region-planned-expansion.a5074a1e8af74f15.webp)

Disse datasentrene kan være flere kvadratkilometer store. Bildene ovenfor ble tatt for noen år siden ved et Microsoft sky-datasenter og viser den opprinnelige størrelsen, sammen med en planlagt utvidelse. Området ryddet for utvidelsen er over 5 kvadratkilometer.

> 💁 Disse datasentrene krever så store mengder strøm at noen har egne kraftstasjoner. På grunn av størrelsen og investeringen fra skyleverandørene er de vanligvis svært miljøvennlige. De er mer effektive enn store mengder små datasentre, de drives hovedsakelig av fornybar energi, og skyleverandører jobber hardt for å redusere avfall, kutte vannforbruk og plante nye skoger for å kompensere for de som ble fjernet for å bygge datasentre. Du kan lese mer om hvordan en skyleverandør jobber med bærekraft på [Azure bærekraft-nettsiden](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Gjør litt research: Les om de store skyene som [Azure fra Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) eller [GCP fra Google](https://cloud.google.com). Hvor mange datasentre har de, og hvor i verden befinner de seg?

Å bruke skyen holder kostnadene nede for bedrifter og lar dem fokusere på det de gjør best, mens ekspertisen innen skyteknologi overlates til leverandøren. Bedrifter trenger ikke lenger å leie eller kjøpe datasenterplass, betale ulike leverandører for tilkobling og strøm, eller ansette eksperter. I stedet kan de betale én månedlig regning til skyleverandøren for å få alt tatt hånd om.

Skyleverandøren kan deretter bruke stordriftsfordeler for å redusere kostnadene, kjøpe datamaskiner i bulk til lavere priser, investere i verktøy for å redusere arbeidsbelastningen for vedlikehold, og til og med designe og bygge sin egen maskinvare for å forbedre skytilbudet.

### Microsoft Azure

Azure er utviklerskyen fra Microsoft, og det er denne skyen du vil bruke i disse leksjonene. Videoen nedenfor gir en kort oversikt over Azure:

[![Oversikt over Azure-video](../../../../../translated_images/no/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Opprett et skyabonnement

For å bruke tjenester i skyen må du registrere deg for et abonnement hos en skyleverandør. For denne leksjonen vil du registrere deg for et Microsoft Azure-abonnement. Hvis du allerede har et Azure-abonnement, kan du hoppe over denne oppgaven. Abonnementsdetaljene som er beskrevet her, er korrekte på tidspunktet for skriving, men kan endres.

> 💁 Hvis du får tilgang til disse leksjonene gjennom skolen din, kan det hende du allerede har et Azure-abonnement tilgjengelig. Sjekk med læreren din.

Det finnes to forskjellige typer gratis Azure-abonnement du kan registrere deg for:

* **Azure for Students** - Dette er et abonnement designet for studenter over 18 år. Du trenger ikke et kredittkort for å registrere deg, og du bruker skole-e-postadressen din for å bekrefte at du er student. Når du registrerer deg, får du US$100 å bruke på skyressurser, sammen med gratis tjenester inkludert en gratis versjon av en IoT-tjeneste. Dette varer i 12 måneder, og du kan fornye hvert år så lenge du forblir student.

* **Azure gratis abonnement** - Dette er et abonnement for alle som ikke er studenter. Du trenger et kredittkort for å registrere deg for abonnementet, men kortet ditt vil ikke bli belastet, det brukes bare for å bekrefte at du er et ekte menneske, ikke en bot. Du får $200 i kreditt til å bruke de første 30 dagene på hvilken som helst tjeneste, sammen med gratis nivåer av Azure-tjenester. Når kredittbeløpet er brukt opp, vil kortet ditt ikke bli belastet med mindre du konverterer til et abonnement med betaling etter bruk.

> 💁 Microsoft tilbyr et Azure for Students Starter-abonnement for studenter under 18 år, men på tidspunktet for skriving støtter dette ikke IoT-tjenester.

### Oppgave - registrer deg for et gratis skyabonnement

Hvis du er student over 18 år, kan du registrere deg for et Azure for Students-abonnement. Du må bekrefte med en skole-e-postadresse. Du kan gjøre dette på to måter:

* Registrer deg for en GitHub studentutviklerpakke på [education.github.com/pack](https://education.github.com/pack). Dette gir deg tilgang til en rekke verktøy og tilbud, inkludert GitHub og Microsoft Azure. Når du registrerer deg for utviklerpakken, kan du deretter aktivere Azure for Students-tilbudet.

* Registrer deg direkte for en Azure for Students-konto på [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Hvis skole-e-postadressen din ikke blir gjenkjent, opprett en [issue i dette repoet](https://github.com/Microsoft/IoT-For-Beginners/issues), så ser vi om den kan legges til i Azure for Students tillatelseslisten.

Hvis du ikke er student, eller du ikke har en gyldig skole-e-postadresse, kan du registrere deg for et Azure gratis abonnement.

* Registrer deg for et Azure gratis abonnement på [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Skybaserte IoT-tjenester

Den offentlige test-MQTT-brokeren du har brukt, er et flott verktøy når du lærer, men har en rekke ulemper som et verktøy å bruke i kommersiell sammenheng:

* Pålitelighet - det er en gratis tjeneste uten garantier og kan bli slått av når som helst
* Sikkerhet - den er offentlig, så hvem som helst kan lytte til telemetrien din eller sende kommandoer for å kontrollere maskinvaren din
* Ytelse - den er designet for bare noen få testmeldinger, så den ville ikke takle et stort antall meldinger som sendes
* Oppdagelse - det er ingen måte å vite hvilke enheter som er tilkoblet

IoT-tjenester i skyen løser disse problemene. De vedlikeholdes av store skyleverandører som investerer tungt i pålitelighet og er tilgjengelige for å fikse eventuelle problemer som kan oppstå. De har innebygd sikkerhet for å forhindre hackere i å lese dataene dine eller sende falske kommandoer. De er også høyytelses, i stand til å håndtere mange millioner meldinger hver dag, og tar i bruk skyen for å skalere etter behov.

> 💁 Selv om du betaler for disse fordelene med en månedlig avgift, tilbyr de fleste skyleverandører en gratis versjon av IoT-tjenesten sin med et begrenset antall meldinger per dag eller enheter som kan koble til. Denne gratis versjonen er vanligvis mer enn nok for en utvikler til å lære om tjenesten. I denne leksjonen vil du bruke en gratis versjon.

IoT-enheter kobler seg til en skytjeneste enten ved å bruke en enhets-SDK (et bibliotek som gir kode for å jobbe med funksjonene til tjenesten) eller direkte via en kommunikasjonsprotokoll som MQTT eller HTTP. Enhets-SDK er vanligvis den enkleste ruten å ta, da den håndterer alt for deg, som å vite hvilke emner som skal publiseres eller abonneres på, og hvordan man håndterer sikkerhet.

![Enheter kobler seg til en tjeneste ved hjelp av en enhets-SDK. Serverkode kobler seg også til tjenesten via en SDK](../../../../../translated_images/no/iot-service-connectivity.7e873847921a5d6f.webp)

Enheten din kommuniserer deretter med andre deler av applikasjonen din via denne tjenesten – på samme måte som du sendte telemetri og mottok kommandoer via MQTT. Dette gjøres vanligvis ved hjelp av en tjeneste-SDK eller et lignende bibliotek. Meldinger kommer fra enheten din til tjenesten, hvor andre komponenter i applikasjonen din kan lese dem, og meldinger kan deretter sendes tilbake til enheten din.

![Enheter uten en gyldig hemmelig nøkkel kan ikke koble seg til IoT-tjenesten](../../../../../translated_images/no/iot-service-allowed-denied-connection.818b0063ac213fb8.webp)

Disse tjenestene implementerer sikkerhet ved å vite om alle enhetene som kan koble til og sende data, enten ved å ha enhetene forhåndsregistrert med tjenesten eller ved å gi enhetene hemmelige nøkler eller sertifikater de kan bruke til å registrere seg med tjenesten første gang de kobler til. Ukjente enheter kan ikke koble seg til; hvis de prøver, avviser tjenesten tilkoblingen og ignorerer meldinger sendt av dem.

✅ Gjør litt research: Hva er ulempen med å ha en åpen IoT-tjeneste der hvilken som helst enhet eller kode kan koble seg til? Kan du finne spesifikke eksempler på hackere som har utnyttet dette?

Andre komponenter i applikasjonen din kan koble seg til IoT-tjenesten og lære om alle enhetene som er tilkoblet eller registrert, og kommunisere med dem direkte, enten i bulk eller individuelt.
💁 IoT-tjenester implementerer også ekstra funksjoner, og skyleverandørene har tilleggstjenester og applikasjoner som kan kobles til tjenesten. For eksempel, hvis du ønsker å lagre alle telemetrimeldingene som sendes av alle enhetene i en database, er det vanligvis bare noen få klikk i skyleverandørens konfigurasjonsverktøy for å koble tjenesten til en database og strømme dataene inn.
## Opprett en IoT-tjeneste i skyen

Nå som du har et Azure-abonnement, kan du registrere deg for en IoT-tjeneste. IoT-tjenesten fra Microsoft heter Azure IoT Hub.

![Azure IoT Hub-logoen](../../../../../translated_images/no/azure-iot-hub-logo.28a19de76d0a1932.webp)

Videoen nedenfor gir en kort oversikt over Azure IoT Hub:

[![Oversikt over Azure IoT Hub-video](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Klikk på bildet over for å se videoen

✅ Ta deg tid til å gjøre litt research og les oversikten over IoT Hub i [Microsoft IoT Hub-dokumentasjonen](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

De tilgjengelige skytjenestene i Azure kan konfigureres via en nettbasert portal eller gjennom et kommandolinjegrensesnitt (CLI). For denne oppgaven skal du bruke CLI.

### Oppgave - installer Azure CLI

For å bruke Azure CLI må det først installeres på din PC eller Mac.

1. Følg instruksjonene i [Azure CLI-dokumentasjonen](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) for å installere CLI.

1. Azure CLI støtter en rekke utvidelser som legger til funksjonalitet for å administrere et bredt spekter av Azure-tjenester. Installer IoT-utvidelsen ved å kjøre følgende kommando fra kommandolinjen eller terminalen din:

    ```sh
    az extension add --name azure-iot
    ```

1. Fra kommandolinjen eller terminalen din, kjør følgende kommando for å logge inn på Azure-abonnementet ditt via Azure CLI.

    ```sh
    az login
    ```

    En nettside vil åpnes i standardnettleseren din. Logg inn med kontoen du brukte til å registrere deg for Azure-abonnementet. Når du er logget inn, kan du lukke nettleserfanen.

1. Hvis du har flere Azure-abonnementer, for eksempel et som er levert av skolen og ditt eget Azure for Students-abonnement, må du velge hvilket du vil bruke. Kjør følgende kommando for å liste opp alle abonnementene du har tilgang til:

    ```sh
    az account list --output table
    ```

    I utdataene vil du se navnet på hvert abonnement sammen med dets `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    For å velge abonnementet du vil bruke, bruk følgende kommando:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Erstatt `<SubscriptionId>` med ID-en til abonnementet du vil bruke. Etter å ha kjørt denne kommandoen, kjør kommandoen for å liste opp kontoene dine på nytt. Du vil se at kolonnen `IsDefault` er merket som `True` for abonnementet du nettopp har valgt.

### Oppgave - opprett en ressursgruppe

Azure-tjenester, som IoT Hub-instansene, virtuelle maskiner, databaser eller AI-tjenester, kalles **ressurser**. Hver ressurs må tilhøre en **ressursgruppe**, en logisk gruppering av én eller flere ressurser.

> 💁 Ved å bruke ressursgrupper kan du administrere flere tjenester samtidig. For eksempel, når du er ferdig med alle leksjonene for dette prosjektet, kan du slette ressursgruppen, og alle ressursene i den vil bli slettet automatisk.

1. Det finnes flere Azure-datasentre rundt om i verden, delt opp i regioner. Når du oppretter en Azure-ressurs eller ressursgruppe, må du spesifisere hvor du vil at den skal opprettes. Kjør følgende kommando for å få en liste over lokasjoner:

    ```sh
    az account list-locations --output table
    ```

    Du vil se en liste over lokasjoner. Denne listen vil være lang.

    > 💁 På tidspunktet for skriving er det 65 lokasjoner du kan distribuere til.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Noter verdien fra kolonnen `Name` for regionen som er nærmest deg. Du kan finne regionene på et kart på [Azure geographies-siden](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Kjør følgende kommando for å opprette en ressursgruppe kalt `soil-moisture-sensor`. Navn på ressursgrupper må være unike i abonnementet ditt.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Erstatt `<location>` med lokasjonen du valgte i forrige trinn.

### Oppgave - opprett en IoT Hub

Du kan nå opprette en IoT Hub-ressurs i ressursgruppen din.

1. Bruk følgende kommando for å opprette IoT Hub-ressursen din:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Erstatt `<hub_name>` med et navn for huben din. Dette navnet må være globalt unikt – det vil si at ingen andre IoT Hub-er opprettet av noen andre kan ha samme navn. Dette navnet brukes i en URL som peker til huben, så det må være unikt. Bruk noe som `soil-moisture-sensor-` og legg til en unik identifikator på slutten, som noen tilfeldige ord eller navnet ditt.

    Alternativet `--sku F1` angir at den skal bruke en gratisnivå. Gratisnivået støtter 8 000 meldinger per dag sammen med de fleste funksjonene til de fullprisede nivåene.

    > 🎓 Ulike prisnivåer for Azure-tjenester kalles nivåer. Hvert nivå har en annen kostnad og tilbyr ulike funksjoner eller datavolumer.

    > 💁 Hvis du vil lære mer om prising, kan du sjekke ut [Azure IoT Hub-prisguiden](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Alternativet `--partition-count 2` definerer hvor mange datastrømmer IoT Hub støtter. Flere partisjoner reduserer datablokkering når flere enheter leser og skriver til IoT Hub. Partisjoner er utenfor omfanget av disse leksjonene, men denne verdien må settes for å opprette en gratisnivå IoT Hub.

    > 💁 Du kan kun ha én gratisnivå IoT Hub per abonnement.

IoT Hub vil bli opprettet. Det kan ta et minutt eller to før dette er fullført.

## Kommuniser med IoT Hub

I forrige leksjon brukte du MQTT og sendte meldinger frem og tilbake på forskjellige emner, hvor de forskjellige emnene hadde ulike formål. I stedet for å sende meldinger over forskjellige emner, har IoT Hub en rekke definerte måter for enheten å kommunisere med huben, eller for huben å kommunisere med enheten.

> 💁 Under panseret kan kommunikasjonen mellom IoT Hub og enheten din bruke MQTT, HTTPS eller AMQP.

* Enhet til sky (D2C) meldinger – dette er meldinger sendt fra en enhet til IoT Hub, som telemetri. Disse kan deretter leses av applikasjonskoden din.

    > 🎓 Under panseret bruker IoT Hub en Azure-tjeneste kalt [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Når du skriver kode for å lese meldinger sendt til huben, kalles disse ofte hendelser.

* Sky til enhet (C2D) meldinger – dette er meldinger sendt fra applikasjonskode, via en IoT Hub til en IoT-enhet.

* Direkte metodeforespørsler – dette er meldinger sendt fra applikasjonskode via en IoT Hub til en IoT-enhet for å be enheten om å gjøre noe, som å kontrollere en aktuator. Disse meldingene krever et svar slik at applikasjonskoden din kan vite om forespørselen ble behandlet vellykket.

* Enhetstvillinger – dette er JSON-dokumenter som holdes synkronisert mellom enheten og IoT Hub, og brukes til å lagre innstillinger eller andre egenskaper enten rapportert av enheten, eller som skal settes på enheten (kalt ønsket) av IoT Hub.

IoT Hub kan lagre meldinger og direkte metodeforespørsler i en konfigurerbar periode (standard én dag), slik at hvis en enhet eller applikasjonskode mister tilkoblingen, kan den fortsatt hente meldinger sendt mens den var offline etter at den kobler til igjen. Enhetstvillinger oppbevares permanent i IoT Hub, slik at en enhet når som helst kan koble til igjen og få den nyeste enhetstvillingen.

✅ Gjør litt research: Les mer om disse meldingstypene i [Veiledning for enhet-til-sky-kommunikasjon](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn), og [Veiledning for sky-til-enhet-kommunikasjon](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) i IoT Hub-dokumentasjonen.

## Koble enheten din til IoT-tjenesten

Når huben er opprettet, kan IoT-enheten din koble til den. Kun registrerte enheter kan koble til en tjeneste, så du må registrere enheten din først. Når du registrerer den, får du tilbake en tilkoblingsstreng som enheten kan bruke for å koble til. Denne tilkoblingsstrengen er spesifikk for enheten og inneholder informasjon om IoT Hub, enheten og en hemmelig nøkkel som lar denne enheten koble til.

> 🎓 En tilkoblingsstreng er et generelt begrep for en tekst som inneholder tilkoblingsdetaljer. Disse brukes når man kobler til IoT Hub-er, databaser og mange andre tjenester. De består vanligvis av en identifikator for tjenesten, som en URL, og sikkerhetsinformasjon som en hemmelig nøkkel. Disse sendes til SDK-er for å koble til tjenesten.

> ⚠️ Tilkoblingsstrenger bør holdes sikre! Sikkerhet vil bli dekket mer detaljert i en senere leksjon.

### Oppgave - registrer IoT-enheten din

IoT-enheten kan registreres med IoT Hub ved hjelp av Azure CLI.

1. Kjør følgende kommando for å registrere en enhet:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Erstatt `<hub_name>` med navnet du brukte for IoT Hub.

    Dette vil opprette en enhet med ID-en `soil-moisture-sensor`.

1. Når IoT-enheten din kobler til IoT Hub ved hjelp av SDK, må den bruke en tilkoblingsstreng som gir URL-en til huben, sammen med en hemmelig nøkkel. Kjør følgende kommando for å hente tilkoblingsstrengen:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Erstatt `<hub_name>` med navnet du brukte for IoT Hub.

1. Lagre tilkoblingsstrengen som vises i utdataene, da du vil trenge den senere.

### Oppgave - koble IoT-enheten din til skyen

Følg den relevante veiledningen for å koble IoT-enheten din til skyen:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Enkeltkortdatamaskin - Raspberry Pi/Virtual IoT device](single-board-computer-connect-hub.md)

### Oppgave - overvåk hendelser

For nå skal du ikke oppdatere serverkoden din. I stedet kan du bruke Azure CLI til å overvåke hendelser fra IoT-enheten din.

1. Sørg for at IoT-enheten din kjører og sender telemetridata om jordfuktighet.

1. Kjør følgende kommando i kommandolinjen eller terminalen din for å overvåke meldinger sendt til IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Erstatt `<hub_name>` med navnet du brukte for IoT Hub.

    Du vil se meldinger vises i konsollutdataene etter hvert som de sendes av IoT-enheten din.

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

    Innholdet i `payload` vil samsvare med meldingen sendt av IoT-enheten din.

    > På tidspunktet for skriving fungerer ikke `az iot`-utvidelsen fullt ut på Apple Silicon. Hvis du bruker en Apple Silicon-enhet, må du overvåke meldingene på en annen måte, for eksempel ved å bruke [Azure IoT Tools for Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Disse meldingene har en rekke egenskaper som automatisk legges til, som tidsstempelet de ble sendt. Disse kalles *annotasjoner*. For å se alle meldingsannotasjonene, bruk følgende kommando:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Erstatt `<hub_name>` med navnet du brukte for IoT Hub.

    Du vil se meldinger vises i konsollutdataene etter hvert som de sendes av IoT-enheten din.

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

    Tidspunktene i annotasjonene er i [UNIX-tid](https://wikipedia.org/wiki/Unix_time), som representerer antall sekunder siden midnatt 1. januar 1970.

    Avslutt hendelsesovervåkingen når du er ferdig.

### Oppgave - kontroller IoT-enheten din

Du kan også bruke Azure CLI til å kalle direkte metoder på IoT-enheten din.

1. Kjør følgende kommando i kommandolinjen eller terminalen din for å utføre metoden `relay_on` på IoT-enheten:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Erstatt `
<hub_name>
` med navnet du brukte for din IoT Hub.

    Dette sender en direkte metodeforespørsel for metoden spesifisert av `method-name`. Direkte metoder kan ta en nyttelast som inneholder data for metoden, og dette kan spesifiseres i parameteren `method-payload` som JSON.

    Du vil se reléet slå seg på, og den tilsvarende utgangen fra IoT-enheten din:

    ```output
    Direct method received -  relay_on
    ```

1. Gjenta trinnet ovenfor, men sett `--method-name` til `relay_off`. Du vil se reléet slå seg av og den tilsvarende utgangen fra IoT-enheten.

---

## 🚀 Utfordring

Gratisnivået for IoT Hub tillater 8 000 meldinger per dag. Koden du skrev sender telemetrimeldinger hvert 10. sekund. Hvor mange meldinger per dag er én melding hvert 10. sekund?

Tenk på hvor ofte målinger av jordfuktighet bør sendes? Hvordan kan du endre koden din for å holde deg innenfor gratisnivået og sjekke så ofte som nødvendig, men ikke for ofte? Hva hvis du ønsket å legge til en annen enhet?

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Gjennomgang og selvstudium

IoT Hub SDK er åpen kildekode for både Arduino og Python. I kode-repositoriene på GitHub finnes det en rekke eksempler som viser hvordan man kan jobbe med ulike IoT Hub-funksjoner.

* Hvis du bruker en Wio Terminal, sjekk ut [Arduino-eksemplene på GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Hvis du bruker en Raspberry Pi eller virtuell enhet, sjekk ut [Python-eksemplene på GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Oppgave

[Lær om skytjenester](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.