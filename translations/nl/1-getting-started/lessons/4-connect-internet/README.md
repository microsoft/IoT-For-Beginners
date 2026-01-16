<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "71b5040e0b3472f1c0949c9b55f224c0",
  "translation_date": "2025-08-27T21:42:34+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/README.md",
  "language_code": "nl"
}
-->
# Verbind je apparaat met het internet

![Een schetsnotitie-overzicht van deze les](../../../../../translated_images/nl/lesson-4.7344e074ea68fa545fd320b12dce36d72dd62d28c3b4596cb26cf315f434b98f.jpg)

> Schetsnotitie door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

Deze les werd gegeven als onderdeel van de [Hello IoT-serie](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) van de [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). De les bestond uit twee video's: een les van 1 uur en een vragensessie van 1 uur waarin dieper werd ingegaan op onderdelen van de les en vragen werden beantwoord.

[![Les 4: Verbind je apparaat met het internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Les 4: Verbind je apparaat met het internet - Vragensessie](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Klik op de bovenstaande afbeeldingen om de video's te bekijken

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Introductie

De **I** in IoT staat voor **Internet** - de cloudconnectiviteit en -diensten die veel van de functies van IoT-apparaten mogelijk maken, van het verzamelen van metingen van de sensoren die op het apparaat zijn aangesloten tot het verzenden van berichten om de actuatoren te besturen. IoT-apparaten maken doorgaans verbinding met één enkele cloud-IoT-service via een standaard communicatieprotocol, en die service is verbonden met de rest van je IoT-toepassing, van AI-diensten om slimme beslissingen te nemen op basis van je gegevens tot webapps voor controle of rapportage.

> 🎓 Gegevens die van sensoren worden verzameld en naar de cloud worden verzonden, worden telemetrie genoemd.

IoT-apparaten kunnen berichten van de cloud ontvangen. Vaak bevatten deze berichten opdrachten - instructies om een actie uit te voeren, hetzij intern (zoals herstarten of firmware bijwerken), hetzij met behulp van een actuator (zoals het inschakelen van een lamp).

Deze les introduceert enkele van de communicatieprotocollen die IoT-apparaten kunnen gebruiken om verbinding te maken met de cloud, en de soorten gegevens die ze kunnen verzenden of ontvangen. Je gaat ook praktisch aan de slag met deze protocollen door internetbesturing toe te voegen aan je nachtlampje en de LED-besturingslogica te verplaatsen naar 'server'-code die lokaal wordt uitgevoerd.

In deze les behandelen we:

* [Communicatieprotocollen](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetrie](../../../../../1-getting-started/lessons/4-connect-internet)
* [Opdrachten](../../../../../1-getting-started/lessons/4-connect-internet)

## Communicatieprotocollen

Er zijn verschillende populaire communicatieprotocollen die door IoT-apparaten worden gebruikt om met het internet te communiceren. De meest gebruikte protocollen zijn gebaseerd op het publiceren/abonneren-model via een soort broker. De IoT-apparaten maken verbinding met de broker en publiceren telemetrie en abonneren zich op opdrachten. De clouddiensten maken ook verbinding met de broker, abonneren zich op alle telemetrieberichten en publiceren opdrachten, hetzij aan specifieke apparaten, hetzij aan groepen apparaten.

![IoT-apparaten maken verbinding met een broker, publiceren telemetrie en abonneren zich op opdrachten. Clouddiensten maken verbinding met de broker, abonneren zich op alle telemetrie en sturen opdrachten naar specifieke apparaten.](../../../../../translated_images/nl/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT is het meest populaire communicatieprotocol voor IoT-apparaten en wordt in deze les behandeld. Andere protocollen zijn onder andere AMQP en HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) is een lichtgewicht, open standaard berichtenprotocol dat berichten tussen apparaten kan verzenden. Het werd in 1999 ontworpen om oliepijpleidingen te monitoren en 15 jaar later door IBM vrijgegeven als een open standaard.

MQTT heeft één broker en meerdere clients. Alle clients maken verbinding met de broker, en de broker stuurt berichten door naar de relevante clients. Berichten worden gerouteerd via benoemde onderwerpen (topics), in plaats van rechtstreeks naar een individuele client te worden verzonden. Een client kan publiceren naar een onderwerp, en alle clients die zich op dat onderwerp hebben geabonneerd, ontvangen het bericht.

![IoT-apparaat publiceert telemetrie op het /telemetry-onderwerp, en de clouddienst abonneert zich op dat onderwerp](../../../../../translated_images/nl/mqtt.cbf7f21d9adc3e17548b359444cc11bb4bf2010543e32ece9a47becf54438c23.png)

✅ Doe wat onderzoek. Als je veel IoT-apparaten hebt, hoe kun je ervoor zorgen dat je MQTT-broker alle berichten aankan?

### Verbind je IoT-apparaat met MQTT

Het eerste deel van het toevoegen van internetbesturing aan je nachtlampje is het verbinden met een MQTT-broker.

#### Taak

Verbind je apparaat met een MQTT-broker.

In dit deel van de les verbind je je IoT-nachtlampje met het internet, zodat het op afstand kan worden bediend. Later in deze les zal je IoT-apparaat een telemetriebericht met het lichtniveau via MQTT naar een openbare MQTT-broker sturen. Dit bericht wordt opgepikt door servercode die je zelf schrijft. Deze code controleert het lichtniveau en stuurt een opdrachtbericht terug naar het apparaat om de LED aan of uit te zetten.

Een realistisch gebruiksscenario voor een dergelijke opzet zou kunnen zijn om gegevens van meerdere lichtsensoren te verzamelen voordat wordt besloten om lampen aan te zetten, bijvoorbeeld in een stadion met veel lampen. Dit kan voorkomen dat de lampen worden ingeschakeld als slechts één sensor wordt bedekt door wolken of een vogel, terwijl de andere sensoren voldoende licht detecteren.

✅ Welke andere situaties vereisen dat gegevens van meerdere sensoren worden geëvalueerd voordat opdrachten worden verzonden?

In plaats van de complexiteit van het opzetten van een MQTT-broker als onderdeel van deze opdracht, kun je een openbare testserver gebruiken die [Eclipse Mosquitto](https://www.mosquitto.org), een open-source MQTT-broker, uitvoert. Deze testbroker is openbaar beschikbaar op [test.mosquitto.org](https://test.mosquitto.org) en vereist geen account, wat het een geweldig hulpmiddel maakt voor het testen van MQTT-clients en -servers.

> 💁 Deze testbroker is openbaar en niet beveiligd. Iedereen kan luisteren naar wat je publiceert, dus het mag niet worden gebruikt voor gegevens die privé moeten blijven.

![Een stroomdiagram van de opdracht met lichtniveaus die worden gelezen en gecontroleerd, en de LED die wordt bestuurd](../../../../../translated_images/nl/assignment-1-internet-flow.3256feab5f052fd273bf4e331157c574c2c3fa42e479836fc9c3586f41db35a5.png)

Volg de relevante stap hieronder om je apparaat te verbinden met de MQTT-broker:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-mqtt.md)

### Een diepere duik in MQTT

Onderwerpen (topics) kunnen een hiërarchie hebben, en clients kunnen zich abonneren op verschillende niveaus van de hiërarchie met behulp van wildcards. Bijvoorbeeld, je kunt temperatuurtelemetrieberichten verzenden naar het onderwerp `/telemetry/temperature` en vochtigheidberichten naar `/telemetry/humidity`, en in je cloudapplicatie abonneren op het onderwerp `/telemetry/*` om zowel de temperatuur- als vochtigheidstelemetrieberichten te ontvangen.

Berichten kunnen worden verzonden met een kwaliteitsniveau (QoS), wat bepaalt hoe gegarandeerd het is dat het bericht wordt ontvangen.

* Hooguit één keer - het bericht wordt slechts één keer verzonden en de client en broker nemen geen extra stappen om de levering te bevestigen (fire and forget).
* Minstens één keer - het bericht wordt meerdere keren door de afzender opnieuw verzonden totdat een bevestiging is ontvangen (acknowledged delivery).
* Precies één keer - de afzender en ontvanger voeren een tweevoudige handdruk uit om ervoor te zorgen dat slechts één kopie van het bericht wordt ontvangen (assured delivery).

✅ In welke situaties is een gegarandeerde levering belangrijker dan een fire-and-forget-bericht?

Hoewel de naam Message Queueing (de M en Q in MQTT) suggereert dat het wachtrijen ondersteunt, is dit niet het geval. Dit betekent dat als een client de verbinding verbreekt en opnieuw verbindt, het geen berichten ontvangt die tijdens de onderbreking zijn verzonden, behalve die berichten die het al begon te verwerken via het QoS-proces. Berichten kunnen echter een "retained"-vlag hebben. Als deze is ingesteld, slaat de MQTT-broker het laatste bericht op dat naar een onderwerp is verzonden met deze vlag, en stuurt dit naar alle clients die zich later op dat onderwerp abonneren. Op deze manier ontvangen clients altijd het laatste bericht.

MQTT ondersteunt ook een keep-alive-functie die controleert of de verbinding nog actief is tijdens lange pauzes tussen berichten.

> 🦟 [Mosquitto van de Eclipse Foundation](https://mosquitto.org) biedt een gratis MQTT-broker die je zelf kunt draaien om met MQTT te experimenteren, evenals een openbare MQTT-broker die je kunt gebruiken om je code te testen, gehost op [test.mosquitto.org](https://test.mosquitto.org).

MQTT-verbindingen kunnen openbaar en open zijn, of versleuteld en beveiligd met gebruikersnamen en wachtwoorden, of certificaten.

> 💁 MQTT communiceert via TCP/IP, hetzelfde onderliggende netwerkprotocol als HTTP, maar op een andere poort. Je kunt MQTT ook via websockets gebruiken om te communiceren met webapps die in een browser draaien, of in situaties waarin firewalls of andere netwerkregels standaard MQTT-verbindingen blokkeren.

## Telemetrie

Het woord telemetrie is afgeleid van Griekse wortels die "op afstand meten" betekenen. Telemetrie is het verzamelen van gegevens van sensoren en het verzenden ervan naar de cloud.

> 💁 Een van de eerste telemetrieapparaten werd in 1874 in Frankrijk uitgevonden en verzond realtime weer- en sneeuwdieptemetingen van de Mont Blanc naar Parijs. Het gebruikte fysieke draden, omdat draadloze technologieën destijds niet beschikbaar waren.

Laten we terugkijken naar het voorbeeld van de slimme thermostaat uit Les 1.

![Een internetverbonden thermostaat met meerdere kamertemperatuursensoren](../../../../../translated_images/nl/telemetry.21e5d8b97649d2eb.webp)

De thermostaat heeft temperatuursensoren om telemetrie te verzamelen. Het heeft waarschijnlijk één ingebouwde temperatuursensor en kan verbinding maken met meerdere externe temperatuursensoren via een draadloos protocol zoals [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Een voorbeeld van de telemetriegegevens die het zou verzenden, kan zijn:

| Naam | Waarde | Beschrijving |
| ---- | ------ | ------------ |
| `thermostat_temperature` | 18°C | De temperatuur gemeten door de ingebouwde temperatuursensor van de thermostaat |
| `livingroom_temperature` | 19°C | De temperatuur gemeten door een externe temperatuursensor die `livingroom` is genoemd om de kamer te identificeren |
| `bedroom_temperature` | 21°C | De temperatuur gemeten door een externe temperatuursensor die `bedroom` is genoemd om de kamer te identificeren |

De clouddienst kan deze telemetriegegevens vervolgens gebruiken om beslissingen te nemen over welke opdrachten moeten worden verzonden om de verwarming te regelen.

### Verstuur telemetrie vanaf je IoT-apparaat

Het volgende deel van het toevoegen van internetbesturing aan je nachtlampje is het verzenden van het lichtniveau als telemetrie naar de MQTT-broker op een telemetrieonderwerp.

#### Taak - verstuur telemetrie vanaf je IoT-apparaat

Verstuur lichtniveau-telemetrie naar de MQTT-broker.

Gegevens worden gecodeerd als JSON - een standaard voor het coderen van gegevens in tekst met sleutel/waarde-paren.

✅ Als je nog niet bekend bent met JSON, kun je er meer over leren in de [JSON.org-documentatie](https://www.json.org/).

Volg de relevante stap hieronder om telemetrie vanaf je apparaat naar de MQTT-broker te sturen:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-telemetry.md)

### Ontvang telemetrie van de MQTT-broker

Het heeft geen zin om telemetrie te verzenden als er niets is om het te ontvangen. De lichtniveau-telemetrie heeft iets nodig dat luistert om de gegevens te verwerken. Deze 'server'-code is het soort code dat je zou implementeren op een clouddienst als onderdeel van een grotere IoT-toepassing, maar hier ga je deze code lokaal op je computer uitvoeren (of op je Raspberry Pi als je daar direct op codeert). De servercode bestaat uit een Python-app die luistert naar telemetrieberichten via MQTT met lichtniveaus. Later in deze les laat je het reageren met een opdrachtbericht met instructies om de LED aan of uit te zetten.

✅ Doe wat onderzoek: Wat gebeurt er met MQTT-berichten als er geen luisteraar is?

#### Installeer Python en VS Code

Als je Python en VS Code niet lokaal hebt geïnstalleerd, moet je beide installeren om de server te coderen. Als je een virtueel IoT-apparaat gebruikt of werkt op je Raspberry Pi, kun je deze stap overslaan, omdat dit al geïnstalleerd en geconfigureerd zou moeten zijn.

##### Taak - installeer Python en VS Code

Installeer Python en VS Code.

1. Installeer Python. Raadpleeg de [Python-downloadpagina](https://www.python.org/downloads/) voor instructies over het installeren van de nieuwste versie van Python.

2. Installeer Visual Studio Code (VS Code). Dit is de editor die je zult gebruiken om je virtuele apparaatcode in Python te schrijven. Raadpleeg de [VS Code-documentatie](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) voor instructies over het installeren van VS Code.
💁 Je bent vrij om elke Python IDE of editor te gebruiken voor deze lessen als je een voorkeursprogramma hebt, maar de lessen zullen instructies geven gebaseerd op het gebruik van VS Code.
1. Installeer de VS Code Pylance-extensie. Dit is een extensie voor VS Code die ondersteuning biedt voor de programmeertaal Python. Raadpleeg de [Pylance-extensie documentatie](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) voor instructies over het installeren van deze extensie in VS Code.

#### Configureer een Python virtuele omgeving

Een van de krachtige functies van Python is de mogelijkheid om [pip-pakketten](https://pypi.org) te installeren - dit zijn pakketten met code die door anderen zijn geschreven en op het internet zijn gepubliceerd. Je kunt een pip-pakket met één opdracht op je computer installeren en dat pakket vervolgens in je code gebruiken. Je zult pip gebruiken om een pakket te installeren waarmee je via MQTT kunt communiceren.

Standaard is een geïnstalleerd pakket overal op je computer beschikbaar, wat kan leiden tot problemen met pakketversies. Bijvoorbeeld: een applicatie is afhankelijk van een bepaalde versie van een pakket, maar die versie werkt niet meer als je een nieuwere versie installeert voor een andere applicatie. Om dit probleem te omzeilen, kun je een [Python virtuele omgeving](https://docs.python.org/3/library/venv.html) gebruiken. Dit is in feite een kopie van Python in een aparte map, en alle geïnstalleerde pip-pakketten worden alleen in die map opgeslagen.

##### Taak - configureer een Python virtuele omgeving

Configureer een Python virtuele omgeving en installeer de MQTT pip-pakketten.

1. Voer vanuit je terminal of opdrachtregel het volgende uit op een locatie naar keuze om een nieuwe map te maken en ernaartoe te navigeren:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Voer nu het volgende uit om een virtuele omgeving te maken in de map `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Je moet expliciet `python3` aanroepen om de virtuele omgeving te maken, voor het geval je Python 2 naast Python 3 (de nieuwste versie) hebt geïnstalleerd. Als je Python 2 hebt geïnstalleerd, zal het aanroepen van `python` Python 2 gebruiken in plaats van Python 3.

1. Activeer de virtuele omgeving:

    * Op Windows:
        * Als je de Command Prompt of de Command Prompt via Windows Terminal gebruikt, voer dan het volgende uit:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Als je PowerShell gebruikt, voer dan het volgende uit:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Op macOS of Linux, voer het volgende uit:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Deze opdrachten moeten worden uitgevoerd vanuit dezelfde locatie waar je de opdracht hebt uitgevoerd om de virtuele omgeving te maken. Je hoeft nooit naar de `.venv`-map te navigeren; je moet altijd de activeringsopdracht en eventuele opdrachten om pakketten te installeren of code uit te voeren, uitvoeren vanuit de map waar je de virtuele omgeving hebt gemaakt.

1. Zodra de virtuele omgeving is geactiveerd, zal de standaard `python`-opdracht de versie van Python uitvoeren die is gebruikt om de virtuele omgeving te maken. Voer het volgende uit om de versie te controleren:

    ```sh
    python --version
    ```

    De uitvoer zal vergelijkbaar zijn met het volgende:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Je Python-versie kan anders zijn - zolang het versie 3.6 of hoger is, zit je goed. Zo niet, verwijder dan deze map, installeer een nieuwere versie van Python en probeer het opnieuw.

1. Voer de volgende opdrachten uit om het pip-pakket voor [Paho-MQTT](https://pypi.org/project/paho-mqtt/), een populaire MQTT-bibliotheek, te installeren:

    ```sh
    pip install paho-mqtt
    ```

    Dit pip-pakket wordt alleen in de virtuele omgeving geïnstalleerd en is niet beschikbaar buiten deze omgeving.

#### Schrijf de servercode

De servercode kan nu in Python worden geschreven.

##### Taak - schrijf de servercode

Schrijf de servercode.

1. Voer vanuit je terminal of opdrachtregel het volgende uit binnen de virtuele omgeving om een Python-bestand genaamd `app.py` te maken:

    * Op Windows voer je uit:

        ```cmd
        type nul > app.py
        ```

    * Op macOS of Linux voer je uit:

        ```cmd
        touch app.py
        ```

1. Open de huidige map in VS Code:

    ```sh
    code .
    ```

1. Wanneer VS Code wordt gestart, zal het de Python virtuele omgeving activeren. Dit wordt weergegeven in de onderste statusbalk:

    ![VS Code toont de geselecteerde virtuele omgeving](../../../../../translated_images/nl/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Als de VS Code Terminal al actief is wanneer VS Code wordt gestart, zal de virtuele omgeving niet geactiveerd zijn in de terminal. Het eenvoudigste is om de terminal te sluiten met de knop **Kill the active terminal instance**:

    ![VS Code Kill the active terminal instance-knop](../../../../../translated_images/nl/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Start een nieuwe VS Code Terminal door *Terminal -> New Terminal* te selecteren of door `` CTRL+` `` in te drukken. De nieuwe terminal zal de virtuele omgeving laden, waarbij de activeringsopdracht in de terminal verschijnt. De naam van de virtuele omgeving (`.venv`) zal ook in de prompt staan:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Open het bestand `app.py` vanuit de VS Code Explorer en voeg de volgende code toe:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Vervang `<ID>` op regel 6 door de unieke ID die je hebt gebruikt bij het aanmaken van je apparaatcode.

    ⚠️ Dit **moet** dezelfde ID zijn die je op je apparaat hebt gebruikt, anders zal de servercode zich niet abonneren op of publiceren naar het juiste onderwerp.

    Deze code maakt een MQTT-client met een unieke naam en verbindt met de *test.mosquitto.org* broker. Vervolgens start het een verwerkingslus die op een achtergrondthread draait en luistert naar berichten op alle geabonneerde onderwerpen.

    De client abonneert zich vervolgens op berichten op het telemetrieonderwerp en definieert een functie die wordt aangeroepen wanneer een bericht wordt ontvangen. Wanneer een telemetriebericht wordt ontvangen, wordt de functie `handle_telemetry` aangeroepen, die het ontvangen bericht naar de console print.

    Tot slot houdt een oneindige lus de applicatie draaiende. De MQTT-client luistert naar berichten op een achtergrondthread en blijft actief zolang de hoofdapplicatie draait.

1. Voer vanuit de VS Code Terminal het volgende uit om je Python-app te starten:

    ```sh
    python app.py
    ```

    De app begint te luisteren naar berichten van het IoT-apparaat.

1. Zorg ervoor dat je apparaat actief is en telemetrieberichten verzendt. Pas de lichtniveaus aan die door je fysieke of virtuele apparaat worden gedetecteerd. Ontvangen berichten worden naar de terminal geprint.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Het bestand `app.py` in de nightlight virtuele omgeving moet actief zijn om ervoor te zorgen dat het bestand `app.py` in de nightlight-server virtuele omgeving de verzonden berichten ontvangt.

> 💁 Je kunt deze code vinden in de map [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Hoe vaak moet telemetrie worden verzonden?

Een belangrijke overweging bij telemetrie is hoe vaak je gegevens moet meten en verzenden. Het antwoord is - dat hangt ervan af. Als je vaak meet, kun je sneller reageren op veranderingen, maar je gebruikt meer stroom, meer bandbreedte, genereert meer gegevens en hebt meer cloudresources nodig om deze te verwerken. Je moet vaak genoeg meten, maar niet te vaak.

Voor een thermostaat is meten om de paar minuten waarschijnlijk meer dan genoeg, omdat temperaturen niet zo vaak veranderen. Als je slechts één keer per dag meet, kun je je huis verwarmen voor nachtelijke temperaturen midden op een zonnige dag. Als je echter elke seconde meet, krijg je duizenden onnodig gedupliceerde temperatuurmetingen die de internetsnelheid en bandbreedte van gebruikers kunnen belasten (een probleem voor mensen met beperkte bandbreedte), meer stroom verbruiken (een probleem voor apparaten op batterijen zoals externe sensoren) en de kosten verhogen van de cloudcomputingresources die nodig zijn om ze te verwerken en op te slaan.

Als je gegevens rond een machine in een fabriek bewaakt die bij een storing catastrofale schade en miljoenen dollars aan verloren inkomsten kan veroorzaken, kan het nodig zijn om meerdere keren per seconde te meten. Het is beter om bandbreedte te verspillen dan telemetrie te missen die aangeeft dat een machine moet worden gestopt en gerepareerd voordat deze kapot gaat.

> 💁 In zo'n situatie kun je overwegen een edge-apparaat te gebruiken om de telemetrie eerst te verwerken en zo de afhankelijkheid van internet te verminderen.

### Verlies van connectiviteit

Internetverbindingen kunnen onbetrouwbaar zijn, met veelvoorkomende storingen. Wat moet een IoT-apparaat doen in dergelijke omstandigheden - moet het de gegevens verliezen of opslaan totdat de verbinding is hersteld? Wederom hangt het antwoord ervan af.

Voor een thermostaat kunnen de gegevens waarschijnlijk worden genegeerd zodra een nieuwe temperatuurmeting is gedaan. Het verwarmingssysteem maakt zich niet druk over het feit dat het 20 minuten geleden 20,5°C was als de temperatuur nu 19°C is; het is de huidige temperatuur die bepaalt of de verwarming aan of uit moet.

Voor machines wil je de gegevens misschien bewaren, vooral als ze worden gebruikt om trends te analyseren. Er zijn machine learning-modellen die anomalieën in gegevensstromen kunnen detecteren door gegevens over een bepaalde periode (bijvoorbeeld het afgelopen uur) te bekijken en afwijkende gegevens te signaleren. Dit wordt vaak gebruikt voor voorspellend onderhoud, waarbij wordt gezocht naar aanwijzingen dat iets binnenkort kapot kan gaan, zodat je het kunt repareren of vervangen voordat dat gebeurt. Je wilt misschien dat alle telemetrie van een machine wordt verzonden, zodat deze kan worden verwerkt voor anomaliedetectie. Zodra het IoT-apparaat weer verbinding heeft, zal het alle telemetrie verzenden die tijdens de internetstoring is gegenereerd.

Ontwerpers van IoT-apparaten moeten ook overwegen of het IoT-apparaat kan worden gebruikt tijdens een internetstoring of signaalverlies door locatie. Een slimme thermostaat moet in staat zijn om enkele beperkte beslissingen te nemen om de verwarming te regelen als het geen telemetrie naar de cloud kan verzenden vanwege een storing.

[![Deze Ferrari werd onbruikbaar omdat iemand probeerde hem te upgraden op een plek zonder mobiel bereik](../../../../../translated_images/nl/bricked-car.dc38f8efadc6c59d76211f981a521efb300939283dee468f79503aae3ec67615.png)](https://twitter.com/internetofshit/status/1315736960082808832)

Voor MQTT om met een verlies van connectiviteit om te gaan, moeten het apparaat en de servercode verantwoordelijk zijn voor het waarborgen van berichtlevering indien nodig. Bijvoorbeeld door te eisen dat alle verzonden berichten worden beantwoord met aanvullende berichten op een antwoordonderwerp. Als dat niet gebeurt, worden ze handmatig in een wachtrij geplaatst om later opnieuw te worden verzonden.

## Opdrachten

Opdrachten zijn berichten die door de cloud naar een apparaat worden verzonden om het te instrueren iets te doen. Meestal houdt dit in dat er een soort uitvoer wordt gegeven via een actuator, maar het kan ook een instructie zijn voor het apparaat zelf, zoals opnieuw opstarten of extra telemetrie verzamelen en deze als reactie op de opdracht retourneren.

![Een internetverbonden thermostaat die een opdracht ontvangt om de verwarming aan te zetten](../../../../../translated_images/nl/commands.d6c06bbbb3a02cce95f2831a1c331daf6dedd4e470c4aa2b0ae54f332016e504.png)

Een thermostaat kan een opdracht van de cloud ontvangen om de verwarming aan te zetten. Op basis van de telemetriegegevens van alle sensoren heeft de cloudservice besloten dat de verwarming aan moet, dus stuurt het de relevante opdracht.

### Verstuur opdrachten naar de MQTT-broker

De volgende stap voor onze internetgestuurde nachtlamp is dat de servercode een opdracht terugstuurt naar het IoT-apparaat om het licht te regelen op basis van de gedetecteerde lichtniveaus.

1. Open de servercode in VS Code.

1. Voeg de volgende regel toe na de declaratie van de `client_telemetry_topic` om te definiëren naar welk onderwerp opdrachten moeten worden verzonden:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Voeg de volgende code toe aan het einde van de functie `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Dit stuurt een JSON-bericht naar het opdrachtonderwerp met de waarde van `led_on` ingesteld op true of false, afhankelijk van of het licht minder dan 300 is of niet. Als het licht minder dan 300 is, wordt true verzonden om het apparaat te instrueren de LED aan te zetten.

1. Voer de code uit zoals eerder.

1. Pas de lichtniveaus aan die door je fysieke of virtuele apparaat worden gedetecteerd. Ontvangen berichten en verzonden opdrachten worden naar de terminal geschreven:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 De telemetrie en opdrachten worden verzonden op één enkel onderwerp. Dit betekent dat telemetrie van meerdere apparaten op hetzelfde telemetrieonderwerp verschijnt en opdrachten naar meerdere apparaten op hetzelfde opdrachtonderwerp. Als je een opdracht naar een specifiek apparaat wilt sturen, kun je meerdere onderwerpen gebruiken, genoemd met een unieke apparaat-ID, zoals `/commands/device1`, `/commands/device2`. Op die manier kan een apparaat alleen luisteren naar berichten die voor dat ene apparaat bedoeld zijn.

> 💁 Je kunt deze code vinden in de map [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Verwerk opdrachten op het IoT-apparaat

Nu opdrachten worden verzonden vanuit de server, kun je nu code toevoegen aan het IoT-apparaat om deze te verwerken en de LED te regelen.

Volg de relevante stap hieronder om te luisteren naar opdrachten van de MQTT-broker:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-commands.md)

Zodra deze code is geschreven en actief is, kun je experimenteren met het veranderen van lichtniveaus. Bekijk de uitvoer van de server en het apparaat, en kijk naar de LED terwijl je de lichtniveaus aanpast.

### Verlies van connectiviteit

Wat moet een cloudservice doen als het een opdracht moet sturen naar een IoT-apparaat dat offline is? Wederom hangt het antwoord ervan af.

Als de nieuwste opdracht een eerdere overschrijft, kunnen de eerdere waarschijnlijk worden genegeerd. Als een cloudservice een opdracht stuurt om de verwarming aan te zetten en vervolgens een opdracht stuurt om deze uit te zetten, kan de aan-opdracht worden genegeerd en niet opnieuw worden verzonden.

Als de opdrachten in volgorde moeten worden verwerkt, zoals het bewegen van een robotarm omhoog en vervolgens het sluiten van een grijper, moeten ze in volgorde worden verzonden zodra de connectiviteit is hersteld.

✅ Hoe kan de apparaat- of servercode ervoor zorgen dat opdrachten altijd in de juiste volgorde worden verzonden en verwerkt via MQTT indien nodig?

---

## 🚀 Uitdaging

De uitdaging in de laatste drie lessen was om zoveel mogelijk IoT-apparaten in je huis, school of werkplek op te sommen en te bepalen of ze zijn gebouwd rond microcontrollers of single-board computers, of zelfs een combinatie van beide, en na te denken over welke sensoren en actuatoren ze gebruiken.
Voor deze apparaten, denk na over welke berichten ze mogelijk verzenden of ontvangen. Welke telemetrie verzenden ze? Welke berichten of commando's zouden ze kunnen ontvangen? Denk je dat ze veilig zijn?

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Review & Zelfstudie

Lees meer over MQTT op de [MQTT Wikipedia-pagina](https://wikipedia.org/wiki/MQTT).

Probeer zelf een MQTT-broker te draaien met behulp van [Mosquitto](https://www.mosquitto.org) en maak verbinding ermee vanuit je IoT-apparaat en servercode.

> 💁 Tip - standaard staat Mosquitto geen anonieme verbindingen toe (dat wil zeggen verbindingen zonder gebruikersnaam en wachtwoord), en staat geen verbindingen toe van buiten de computer waarop het draait.
> Je kunt dit oplossen met een [`mosquitto.conf` configuratiebestand](https://www.mosquitto.org/man/mosquitto-conf-5.html) met het volgende:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Opdracht

[Vergelijk en contrasteer MQTT met andere communicatieprotocollen](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.