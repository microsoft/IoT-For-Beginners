<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-27T21:29:57+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "nl"
}
-->
# Migreer je plant naar de cloud

![Een schetsnotitie-overzicht van deze les](../../../../../translated_images/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.nl.jpg)

> Schetsnotitie door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

Deze les werd gegeven als onderdeel van het [IoT voor Beginners Project 2 - Digitale Landbouw serie](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) van de [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Verbind je apparaat met de cloud via Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Introductie

In de vorige les heb je geleerd hoe je je plant kunt verbinden met een MQTT-broker en een relais kunt bedienen via servercode die lokaal draait. Dit vormt de kern van het soort internetverbonden geautomatiseerd bewateringssysteem dat wordt gebruikt, van individuele planten thuis tot commerciële boerderijen.

Het IoT-apparaat communiceerde met een openbare MQTT-broker om de principes te demonstreren, maar dit is niet de meest betrouwbare of veilige manier. In deze les leer je over de cloud en de IoT-mogelijkheden die worden geboden door openbare clouddiensten. Je leert ook hoe je je plant kunt migreren naar een van deze clouddiensten vanaf de openbare MQTT-broker.

In deze les behandelen we:

* [Wat is de cloud?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Maak een cloudabonnement aan](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Cloud IoT-diensten](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Maak een IoT-dienst in de cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Communiceer met IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Verbind je apparaat met de IoT-dienst](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Wat is de cloud?

Vóór de cloud, wanneer een bedrijf diensten wilde aanbieden aan hun werknemers (zoals databases of bestandsopslag) of aan het publiek (zoals websites), bouwden en beheerden ze een datacenter. Dit varieerde van een kamer met een klein aantal computers tot een gebouw met veel computers. Het bedrijf beheerde alles, waaronder:

* Computers kopen
* Hardwareonderhoud
* Stroom en koeling
* Netwerken
* Beveiliging, inclusief het beveiligen van het gebouw en de software op de computers
* Software-installatie en updates

Dit kon erg duur zijn, vereiste een breed scala aan gekwalificeerde medewerkers en was erg traag om aan te passen wanneer nodig. Bijvoorbeeld, als een online winkel een drukke feestdagenseizoen moest plannen, moesten ze maanden van tevoren extra hardware kopen, configureren, installeren en de software installeren om hun verkoopproces te draaien. Na het feestdagenseizoen, wanneer de verkoop weer daalt, zouden ze achterblijven met computers die ze hebben betaald maar die tot het volgende drukke seizoen ongebruikt blijven.

✅ Denk je dat dit bedrijven in staat zou stellen om snel te handelen? Als een online kledingwinkel plotseling populair wordt omdat een beroemdheid in hun kleding is gezien, zouden ze dan snel genoeg hun computerkracht kunnen vergroten om de plotselinge toestroom van bestellingen aan te kunnen?

### Iemand anders zijn computer

De cloud wordt vaak gekscherend 'iemand anders zijn computer' genoemd. Het oorspronkelijke idee was simpel: in plaats van computers te kopen, huur je de computer van iemand anders. Iemand anders, een cloudcomputingprovider, zou enorme datacenters beheren. Zij zouden verantwoordelijk zijn voor het kopen en installeren van de hardware, het beheren van stroom en koeling, netwerken, gebouwbeveiliging, hardware- en software-updates, alles. Als klant huur je de computers die je nodig hebt, huurt meer wanneer de vraag piekt en vermindert het aantal dat je huurt als de vraag daalt. Deze cloud-datacenters bevinden zich overal ter wereld.

![Een Microsoft cloud-datacenter](../../../../../translated_images/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.nl.png)
![Een geplande uitbreiding van een Microsoft cloud-datacenter](../../../../../translated_images/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.nl.png)

Deze datacenters kunnen meerdere vierkante kilometers groot zijn. De bovenstaande afbeeldingen zijn een paar jaar geleden genomen bij een Microsoft cloud-datacenter en tonen de oorspronkelijke grootte, samen met een geplande uitbreiding. Het gebied dat is vrijgemaakt voor de uitbreiding is meer dan 5 vierkante kilometer.

> 💁 Deze datacenters vereisen zulke grote hoeveelheden stroom dat sommige hun eigen energiecentrales hebben. Vanwege hun grootte en het niveau van investeringen van de cloudproviders zijn ze meestal erg milieuvriendelijk. Ze zijn efficiënter dan enorme aantallen kleine datacenters, draaien voornamelijk op hernieuwbare energie en cloudproviders werken hard om afval te verminderen, watergebruik te beperken en bossen opnieuw aan te planten om de ruimte te compenseren die nodig was om datacenters te bouwen. Je kunt meer lezen over hoe een cloudprovider werkt aan duurzaamheid op de [Azure duurzaamheidssite](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Doe wat onderzoek: Lees meer over de grote clouds zoals [Azure van Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) of [GCP van Google](https://cloud.google.com). Hoeveel datacenters hebben ze en waar bevinden ze zich in de wereld?

Het gebruik van de cloud houdt de kosten laag voor bedrijven en stelt hen in staat zich te concentreren op waar ze goed in zijn, terwijl de cloudcomputingexpertise in handen blijft van de provider. Bedrijven hoeven geen datacenterruimte meer te huren of kopen, verschillende providers te betalen voor connectiviteit en stroom, of experts in dienst te nemen. In plaats daarvan kunnen ze één maandelijkse rekening betalen aan de cloudprovider om alles te laten verzorgen.

De cloudprovider kan vervolgens schaalvoordelen gebruiken om de kosten te verlagen, computers in bulk tegen lagere kosten kopen, investeren in tooling om hun werkbelasting voor onderhoud te verminderen, en zelfs hun eigen hardware ontwerpen en bouwen om hun cloudaanbod te verbeteren.

### Microsoft Azure

Azure is de ontwikkelaarscloud van Microsoft, en dit is de cloud die je zult gebruiken voor deze lessen. De onderstaande video geeft een korte introductie van Azure:

[![Overzicht van Azure video](../../../../../translated_images/what-is-azure-video-thumbnail.20174db09e03bbb8.nl.png)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Maak een cloudabonnement aan

Om diensten in de cloud te gebruiken, moet je je aanmelden voor een abonnement bij een cloudprovider. Voor deze les meld je je aan voor een Microsoft Azure-abonnement. Als je al een Azure-abonnement hebt, kun je deze taak overslaan. De abonnementsdetails die hier worden beschreven zijn correct op het moment van schrijven, maar kunnen veranderen.

> 💁 Als je deze lessen via je school volgt, heb je mogelijk al een Azure-abonnement beschikbaar. Controleer dit bij je docent.

Er zijn twee verschillende soorten gratis Azure-abonnementen waarvoor je je kunt aanmelden:

* **Azure voor Studenten** - Dit is een abonnement ontworpen voor studenten van 18 jaar en ouder. Je hebt geen creditcard nodig om je aan te melden en je gebruikt je school-e-mailadres om te bevestigen dat je student bent. Bij aanmelding krijg je US$100 om te besteden aan cloudresources, samen met gratis diensten, waaronder een gratis versie van een IoT-dienst. Dit abonnement duurt 12 maanden en kan elk jaar worden verlengd zolang je student blijft.

* **Azure gratis abonnement** - Dit is een abonnement voor iedereen die geen student is. Je hebt een creditcard nodig om je aan te melden, maar je kaart wordt niet belast; deze wordt alleen gebruikt om te verifiëren dat je een echt persoon bent en geen bot. Je krijgt $200 tegoed om te gebruiken in de eerste 30 dagen voor elke dienst, samen met gratis niveaus van Azure-diensten. Zodra je tegoed is opgebruikt, wordt je kaart niet belast tenzij je overschakelt naar een abonnement op basis van gebruik.

> 💁 Microsoft biedt een Azure voor Studenten Starter-abonnement aan voor studenten onder de 18 jaar, maar op het moment van schrijven ondersteunt dit geen IoT-diensten.

### Taak - meld je aan voor een gratis cloudabonnement

Als je een student bent van 18 jaar of ouder, kun je je aanmelden voor een Azure voor Studenten-abonnement. Je moet dit valideren met een school-e-mailadres. Dit kan op twee manieren:

* Meld je aan voor een GitHub Student Developer Pack op [education.github.com/pack](https://education.github.com/pack). Dit geeft je toegang tot een reeks tools en aanbiedingen, waaronder GitHub en Microsoft Azure. Zodra je je aanmeldt voor het Developer Pack, kun je vervolgens het Azure voor Studenten-aanbod activeren.

* Meld je direct aan voor een Azure voor Studenten-account op [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Als je school-e-mailadres niet wordt herkend, meld dit dan via een [issue in deze repo](https://github.com/Microsoft/IoT-For-Beginners/issues) en we zullen kijken of het kan worden toegevoegd aan de Azure voor Studenten-toegangslijst.

Als je geen student bent of geen geldig school-e-mailadres hebt, kun je je aanmelden voor een Azure Gratis abonnement.

* Meld je aan voor een Azure Gratis abonnement op [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Cloud IoT-diensten

De openbare test-MQTT-broker die je hebt gebruikt is een geweldig hulpmiddel om te leren, maar heeft een aantal nadelen als hulpmiddel voor commercieel gebruik:

* Betrouwbaarheid - het is een gratis dienst zonder garanties en kan op elk moment worden uitgeschakeld
* Beveiliging - het is openbaar, dus iedereen kan je telemetrie bekijken of commando's sturen om je hardware te bedienen
* Prestaties - het is ontworpen voor slechts een paar testberichten en zou niet bestand zijn tegen een grote hoeveelheid berichten
* Ontdekking - er is geen manier om te weten welke apparaten zijn verbonden

IoT-diensten in de cloud lossen deze problemen op. Ze worden onderhouden door grote cloudproviders die zwaar investeren in betrouwbaarheid en klaarstaan om eventuele problemen op te lossen. Ze hebben ingebouwde beveiliging om te voorkomen dat hackers je gegevens lezen of ongewenste commando's sturen. Ze zijn ook zeer performant, in staat om miljoenen berichten per dag te verwerken, en maken gebruik van de cloud om naar behoefte te schalen.

> 💁 Hoewel je voor deze voordelen een maandelijkse vergoeding betaalt, bieden de meeste cloudproviders een gratis versie van hun IoT-dienst aan met een beperkt aantal berichten per dag of apparaten die kunnen verbinden. Deze gratis versie is meestal meer dan genoeg voor een ontwikkelaar om de dienst te leren kennen. In deze les gebruik je een gratis versie.

IoT-apparaten verbinden met een clouddienst via een apparaat-SDK (een bibliotheek die code biedt om te werken met de functies van de dienst) of rechtstreeks via een communicatieprotocol zoals MQTT of HTTP. De apparaat-SDK is meestal de gemakkelijkste route omdat deze alles voor je afhandelt, zoals weten welke onderwerpen gepubliceerd of geabonneerd moeten worden en hoe beveiliging moet worden afgehandeld.

![Apparaten verbinden met een dienst via een apparaat-SDK. Servercode verbindt ook met de dienst via een SDK](../../../../../translated_images/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.nl.png)

Je apparaat communiceert vervolgens met andere onderdelen van je applicatie via deze dienst - vergelijkbaar met hoe je telemetrie verzond en commando's ontving via MQTT. Dit gebeurt meestal via een dienst-SDK of een vergelijkbare bibliotheek. Berichten komen van je apparaat naar de dienst waar andere onderdelen van je applicatie ze kunnen lezen, en berichten kunnen vervolgens terug naar je apparaat worden gestuurd.

![Apparaten zonder een geldige geheime sleutel kunnen niet verbinden met de IoT-dienst](../../../../../translated_images/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.nl.png)

Deze diensten implementeren beveiliging door te weten welke apparaten kunnen verbinden en gegevens kunnen verzenden, ofwel door de apparaten vooraf te registreren bij de dienst, of door de apparaten geheime sleutels of certificaten te geven die ze kunnen gebruiken om zichzelf te registreren bij de dienst de eerste keer dat ze verbinden. Onbekende apparaten kunnen niet verbinden; als ze proberen, weigert de dienst de verbinding en negeert de berichten die door hen worden verzonden.

✅ Doe wat onderzoek: Wat is het nadeel van een open IoT-dienst waar elk apparaat of code kan verbinden? Kun je specifieke voorbeelden vinden van hackers die hiervan misbruik hebben gemaakt?

Andere onderdelen van je applicatie kunnen verbinden met de IoT-dienst en leren over alle apparaten die verbonden of geregistreerd zijn, en rechtstreeks communiceren met hen, individueel of in bulk.
💁 IoT-diensten implementeren ook extra mogelijkheden, en de cloudproviders hebben aanvullende diensten en applicaties die aan de dienst kunnen worden gekoppeld. Bijvoorbeeld, als je alle telemetrieberichten die door alle apparaten worden verzonden in een database wilt opslaan, is het meestal slechts een paar klikken in het configuratiehulpmiddel van de cloudprovider om de dienst aan een database te koppelen en de gegevens erin te streamen.
## Maak een IoT-service in de cloud

Nu je een Azure-abonnement hebt, kun je je aanmelden voor een IoT-service. De IoT-service van Microsoft heet Azure IoT Hub.

![Het Azure IoT Hub-logo](../../../../../translated_images/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.nl.png)

De onderstaande video geeft een kort overzicht van Azure IoT Hub:

[![Overzicht van Azure IoT Hub video](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Klik op de afbeelding hierboven om de video te bekijken

✅ Neem even de tijd om onderzoek te doen en lees het overzicht van IoT Hub in de [Microsoft IoT Hub-documentatie](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

De cloudservices die beschikbaar zijn in Azure kunnen worden geconfigureerd via een webgebaseerd portaal of via een command-line interface (CLI). Voor deze taak gebruik je de CLI.

### Taak - installeer de Azure CLI

Om de Azure CLI te gebruiken, moet deze eerst op je pc of Mac worden geïnstalleerd.

1. Volg de instructies in de [Azure CLI-documentatie](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) om de CLI te installeren.

1. De Azure CLI ondersteunt een aantal extensies die mogelijkheden toevoegen om een breed scala aan Azure-services te beheren. Installeer de IoT-extensie door het volgende commando uit te voeren in je command-line of terminal:

    ```sh
    az extension add --name azure-iot
    ```

1. Voer vanuit je command-line of terminal het volgende commando uit om in te loggen op je Azure-abonnement via de Azure CLI.

    ```sh
    az login
    ```

    Er wordt een webpagina geopend in je standaardbrowser. Log in met het account dat je hebt gebruikt om je aan te melden voor je Azure-abonnement. Zodra je bent ingelogd, kun je het browsertabblad sluiten.

1. Als je meerdere Azure-abonnementen hebt, zoals een door school verstrekt abonnement en je eigen Azure for Students-abonnement, moet je degene selecteren die je wilt gebruiken. Voer het volgende commando uit om alle abonnementen te zien waartoe je toegang hebt:

    ```sh
    az account list --output table
    ```

    In de uitvoer zie je de naam van elk abonnement samen met de `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Gebruik het volgende commando om het abonnement te selecteren dat je wilt gebruiken:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Vervang `<SubscriptionId>` door de Id van het abonnement dat je wilt gebruiken. Nadat je dit commando hebt uitgevoerd, voer je opnieuw het commando uit om je accounts te bekijken. Je ziet dat de kolom `IsDefault` is gemarkeerd als `True` voor het abonnement dat je zojuist hebt ingesteld.

### Taak - maak een resourcegroep

Azure-services, zoals IoT Hub-instanties, virtuele machines, databases of AI-services, worden aangeduid als **resources**. Elke resource moet zich bevinden in een **Resource Group**, een logische groepering van een of meer resources.

> 💁 Het gebruik van resourcegroepen betekent dat je meerdere services tegelijk kunt beheren. Bijvoorbeeld, zodra je alle lessen voor dit project hebt voltooid, kun je de resourcegroep verwijderen, en alle resources erin worden automatisch verwijderd.

1. Er zijn meerdere Azure-datacenters over de hele wereld, verdeeld in regio's. Wanneer je een Azure-resource of resourcegroep maakt, moet je specificeren waar je deze wilt maken. Voer het volgende commando uit om de lijst met locaties te krijgen:

    ```sh
    az account list-locations --output table
    ```

    Je ziet een lijst met locaties. Deze lijst zal lang zijn.

    > 💁 Op het moment van schrijven zijn er 65 locaties waar je naar kunt implementeren.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Noteer de waarde uit de kolom `Name` van de regio die het dichtst bij jou in de buurt is. Je kunt de regio's op een kaart vinden op de [Azure geografiepagina](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Voer het volgende commando uit om een resourcegroep genaamd `soil-moisture-sensor` te maken. Namen van resourcegroepen moeten uniek zijn binnen je abonnement.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Vervang `<location>` door de locatie die je in de vorige stap hebt geselecteerd.

### Taak - maak een IoT Hub

Je kunt nu een IoT Hub-resource maken in je resourcegroep.

1. Gebruik het volgende commando om je IoT Hub-resource te maken:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Vervang `<hub_name>` door een naam voor je hub. Deze naam moet wereldwijd uniek zijn - dat wil zeggen dat geen enkele andere IoT Hub, gemaakt door wie dan ook, dezelfde naam mag hebben. Deze naam wordt gebruikt in een URL die naar de hub verwijst, dus moet uniek zijn. Gebruik iets als `soil-moisture-sensor-` en voeg een unieke identificator toe, zoals een paar willekeurige woorden of je naam.

    De optie `--sku F1` geeft aan dat de gratis laag moet worden gebruikt. De gratis laag ondersteunt 8.000 berichten per dag samen met de meeste functies van de volledige betaalde lagen.

    > 🎓 Verschillende prijscategorieën van Azure-services worden aangeduid als lagen. Elke laag heeft een andere kostprijs en biedt verschillende functies of datavolumes.

    > 💁 Als je meer wilt leren over prijzen, kun je de [Azure IoT Hub-prijsgids](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn) bekijken.

    De optie `--partition-count 2` definieert hoeveel datastromen de IoT Hub ondersteunt. Meer partities verminderen datablokkering wanneer meerdere dingen lezen en schrijven vanuit de IoT Hub. Partities vallen buiten de scope van deze lessen, maar deze waarde moet worden ingesteld om een gratis IoT Hub te maken.

    > 💁 Je kunt slechts één gratis IoT Hub per abonnement hebben.

De IoT Hub wordt gemaakt. Dit kan een minuut of zo duren.

## Communiceer met IoT Hub

In de vorige les heb je MQTT gebruikt en berichten heen en weer gestuurd over verschillende onderwerpen, waarbij de verschillende onderwerpen verschillende doeleinden hadden. In plaats van berichten over verschillende onderwerpen te sturen, heeft IoT Hub een aantal gedefinieerde manieren voor het apparaat om te communiceren met de Hub, of voor de Hub om te communiceren met het apparaat.

> 💁 Onder de motorkap kan deze communicatie tussen IoT Hub en je apparaat gebruik maken van MQTT, HTTPS of AMQP.

* Device to cloud (D2C) berichten - dit zijn berichten die van een apparaat naar IoT Hub worden gestuurd, zoals telemetrie. Ze kunnen vervolgens door je applicatiecode van de IoT Hub worden gelezen.

    > 🎓 Onder de motorkap gebruikt IoT Hub een Azure-service genaamd [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Wanneer je code schrijft om berichten te lezen die naar de hub zijn gestuurd, worden deze vaak evenementen genoemd.

* Cloud to device (C2D) berichten - dit zijn berichten die door applicatiecode via een IoT Hub naar een IoT-apparaat worden gestuurd.

* Directe methodeverzoeken - dit zijn berichten die door applicatiecode via een IoT Hub naar een IoT-apparaat worden gestuurd om te verzoeken dat het apparaat iets doet, zoals het bedienen van een actuator. Deze berichten vereisen een reactie zodat je applicatiecode kan zien of het succesvol is verwerkt.

* Device twins - dit zijn JSON-documenten die gesynchroniseerd worden gehouden tussen het apparaat en IoT Hub, en worden gebruikt om instellingen of andere eigenschappen op te slaan die door het apparaat worden gerapporteerd, of die op het apparaat moeten worden ingesteld (bekend als gewenst) door de IoT Hub.

IoT Hub kan berichten en directe methodeverzoeken opslaan voor een configureerbare periode (standaard één dag), zodat als een apparaat of applicatiecode de verbinding verliest, het nog steeds berichten kan ophalen die zijn verzonden terwijl het offline was, nadat het opnieuw verbinding maakt. Device twins worden permanent opgeslagen in de IoT Hub, zodat een apparaat op elk moment opnieuw verbinding kan maken en de nieuwste device twin kan ophalen.

✅ Doe wat onderzoek: Lees meer over deze berichttypen in de [Device-to-cloud communicatiehandleiding](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) en de [Cloud-to-device communicatiehandleiding](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) in de IoT Hub-documentatie.

## Verbind je apparaat met de IoT-service

Zodra de hub is gemaakt, kan je IoT-apparaat ermee verbinden. Alleen geregistreerde apparaten kunnen verbinding maken met een service, dus je moet je apparaat eerst registreren. Wanneer je registreert, kun je een verbindingsreeks terugkrijgen die het apparaat kan gebruiken om verbinding te maken. Deze verbindingsreeks is apparaat specifiek en bevat informatie over de IoT Hub, het apparaat en een geheime sleutel waarmee dit apparaat verbinding kan maken.

> 🎓 Een verbindingsreeks is een algemene term voor een stuk tekst dat verbindingsdetails bevat. Deze worden gebruikt bij het verbinden met IoT Hubs, databases en vele andere services. Ze bestaan meestal uit een identificator voor de service, zoals een URL, en beveiligingsinformatie zoals een geheime sleutel. Deze worden doorgegeven aan SDK's om verbinding te maken met de service.

> ⚠️ Verbindingsreeksen moeten veilig worden bewaard! Beveiliging wordt in een toekomstige les in meer detail behandeld.

### Taak - registreer je IoT-apparaat

Het IoT-apparaat kan worden geregistreerd bij je IoT Hub met behulp van de Azure CLI.

1. Voer het volgende commando uit om een apparaat te registreren:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Vervang `<hub_name>` door de naam die je hebt gebruikt voor je IoT Hub.

    Dit maakt een apparaat met een ID van `soil-moisture-sensor`.

1. Wanneer je IoT-apparaat verbinding maakt met je IoT Hub met behulp van de SDK, moet het een verbindingsreeks gebruiken die de URL van de hub geeft, samen met een geheime sleutel. Voer het volgende commando uit om de verbindingsreeks te krijgen:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Vervang `<hub_name>` door de naam die je hebt gebruikt voor je IoT Hub.

1. Sla de verbindingsreeks op die in de uitvoer wordt weergegeven, want je hebt deze later nodig.

### Taak - verbind je IoT-apparaat met de cloud

Werk de relevante handleiding door om je IoT-apparaat met de cloud te verbinden:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-connect-hub.md)

### Taak - monitor gebeurtenissen

Voor nu ga je je servercode niet bijwerken. In plaats daarvan kun je de Azure CLI gebruiken om gebeurtenissen van je IoT-apparaat te monitoren.

1. Zorg ervoor dat je IoT-apparaat actief is en waarden voor bodemvochtigheidstelemetrie verzendt.

1. Voer het volgende commando uit in je command-prompt of terminal om berichten te monitoren die naar je IoT Hub worden verzonden:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Vervang `<hub_name>` door de naam die je hebt gebruikt voor je IoT Hub.

    Je ziet berichten verschijnen in de console-uitvoer terwijl ze door je IoT-apparaat worden verzonden.

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

    De inhoud van de `payload` komt overeen met het bericht dat door je IoT-apparaat is verzonden.

    > Op het moment van schrijven werkt de `az iot` extensie niet volledig op Apple Silicon. Als je een Apple Silicon-apparaat gebruikt, moet je de berichten op een andere manier monitoren, zoals met behulp van de [Azure IoT Tools voor Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Deze berichten hebben een aantal eigenschappen die automatisch aan hen worden toegevoegd, zoals de tijdstempel waarop ze zijn verzonden. Deze worden *annotaties* genoemd. Gebruik het volgende commando om alle berichtannotaties te bekijken:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Vervang `<hub_name>` door de naam die je hebt gebruikt voor je IoT Hub.

    Je ziet berichten verschijnen in de console-uitvoer terwijl ze door je IoT-apparaat worden verzonden.

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

    De tijdwaarden in de annotaties zijn in [UNIX-tijd](https://wikipedia.org/wiki/Unix_time), wat het aantal seconden sinds middernacht op 1<sup>e</sup> januari 1970 vertegenwoordigt.

    Verlaat de gebeurtenismonitor wanneer je klaar bent.

### Taak - bestuur je IoT-apparaat

Je kunt ook de Azure CLI gebruiken om directe methoden op je IoT-apparaat aan te roepen.

1. Voer het volgende commando uit in je command-prompt of terminal om de methode `relay_on` op het IoT-apparaat aan te roepen:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Vervang `
<hub_naam>
` met de naam die je hebt gebruikt voor je IoT Hub.

    Dit stuurt een directe methode-aanroep voor de methode die is gespecificeerd door `method-name`. Directe methoden kunnen een payload bevatten met gegevens voor de methode, en dit kan worden opgegeven in de parameter `method-payload` als JSON.

    Je zult zien dat het relais wordt ingeschakeld, en de bijbehorende uitvoer van je IoT-apparaat:

    ```output
    Direct method received -  relay_on
    ```

1. Herhaal de bovenstaande stap, maar stel `--method-name` in op `relay_off`. Je zult zien dat het relais wordt uitgeschakeld en de bijbehorende uitvoer van het IoT-apparaat.

---

## 🚀 Uitdaging

De gratis laag van IoT Hub staat 8.000 berichten per dag toe. De code die je hebt geschreven stuurt elke 10 seconden een telemetrisch bericht. Hoeveel berichten per dag is één bericht elke 10 seconden?

Denk na over hoe vaak metingen van bodemvochtigheid moeten worden verzonden. Hoe kun je je code aanpassen om binnen de gratis laag te blijven en zo vaak als nodig te controleren, maar niet te vaak? Wat als je een tweede apparaat wilt toevoegen?

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Herziening & Zelfstudie

De IoT Hub SDK is open source voor zowel Arduino als Python. In de code-repositories op GitHub zijn er een aantal voorbeelden die laten zien hoe je met verschillende functies van IoT Hub kunt werken.

* Als je een Wio Terminal gebruikt, bekijk dan de [Arduino-voorbeelden op GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Als je een Raspberry Pi of virtueel apparaat gebruikt, bekijk dan de [Python-voorbeelden op GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Opdracht

[Leer over cloudservices](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.