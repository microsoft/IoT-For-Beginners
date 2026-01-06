<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T21:47:29+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "nl"
}
-->
# Bedien je nachtlampje via het internet - Wio Terminal

Het IoT-apparaat moet worden geprogrammeerd om te communiceren met *test.mosquitto.org* via MQTT om telemetriegegevens te verzenden met de lichtsensorlezing en om opdrachten te ontvangen om de LED te bedienen.

In dit deel van de les verbind je je Wio Terminal met een MQTT-broker.

## Installeer de WiFi- en MQTT Arduino-bibliotheken

Om te communiceren met de MQTT-broker, moet je enkele Arduino-bibliotheken installeren om de WiFi-chip in de Wio Terminal te gebruiken en te communiceren met MQTT. Bij het ontwikkelen voor Arduino-apparaten kun je gebruik maken van een breed scala aan bibliotheken die open-source code bevatten en een enorme reeks mogelijkheden implementeren. Seeed publiceert bibliotheken voor de Wio Terminal waarmee deze via WiFi kan communiceren. Andere ontwikkelaars hebben bibliotheken gepubliceerd om te communiceren met MQTT-brokers, en je zult deze gebruiken met je apparaat.

Deze bibliotheken worden geleverd als broncode die automatisch kan worden geïmporteerd in PlatformIO en gecompileerd voor je apparaat. Op deze manier werken Arduino-bibliotheken op elk apparaat dat het Arduino-framework ondersteunt, ervan uitgaande dat het apparaat beschikt over specifieke hardware die door die bibliotheek nodig is. Sommige bibliotheken, zoals de Seeed WiFi-bibliotheken, zijn specifiek voor bepaalde hardware.

Bibliotheken kunnen globaal worden geïnstalleerd en gecompileerd indien nodig, of in een specifiek project. Voor deze opdracht worden de bibliotheken in het project geïnstalleerd.

✅ Je kunt meer leren over bibliotheekbeheer en hoe je bibliotheken kunt vinden en installeren in de [PlatformIO bibliotheekdocumentatie](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Taak - installeer de WiFi- en MQTT Arduino-bibliotheken

Installeer de Arduino-bibliotheken.

1. Open het nachtlampproject in VS Code.

1. Voeg het volgende toe aan het einde van het `platformio.ini`-bestand:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Dit importeert de Seeed WiFi-bibliotheken. De `@ <nummer>`-syntax verwijst naar een specifieke versie van de bibliotheek.

    > 💁 Je kunt de `@ <nummer>` verwijderen om altijd de nieuwste versie van de bibliotheken te gebruiken, maar er is geen garantie dat latere versies werken met de onderstaande code. De code hier is getest met deze versie van de bibliotheken.

    Dit is alles wat je hoeft te doen om de bibliotheken toe te voegen. De volgende keer dat PlatformIO het project bouwt, downloadt het de broncode van deze bibliotheken en compileert het deze in je project.

1. Voeg het volgende toe aan de `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Dit importeert [PubSubClient](https://github.com/knolleary/pubsubclient), een Arduino MQTT-client.

## Verbinden met WiFi

De Wio Terminal kan nu worden verbonden met WiFi.

### Taak - verbinden met WiFi

Verbind de Wio Terminal met WiFi.

1. Maak een nieuw bestand in de `src`-map genaamd `config.h`. Je kunt dit doen door de `src`-map of het `main.cpp`-bestand erin te selecteren en op de knop **Nieuw bestand** te klikken in de verkenner. Deze knop verschijnt alleen wanneer je cursor boven de verkenner zweeft.

    ![De knop nieuw bestand](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.nl.png)

1. Voeg de volgende code toe aan dit bestand om constanten te definiëren voor je WiFi-inloggegevens:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Vervang `<SSID>` door de SSID van je WiFi. Vervang `<PASSWORD>` door je WiFi-wachtwoord.

1. Open het `main.cpp`-bestand.

1. Voeg de volgende `#include`-directieven toe aan de bovenkant van het bestand:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Dit bevat headerbestanden voor de eerder toegevoegde bibliotheken, evenals het config-headerbestand. Deze headerbestanden zijn nodig om PlatformIO te vertellen de code uit de bibliotheken op te nemen. Zonder expliciet deze headerbestanden op te nemen, wordt sommige code niet gecompileerd en krijg je compilerfouten.

1. Voeg de volgende code toe boven de `setup`-functie:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Deze code blijft in een lus terwijl het apparaat niet verbonden is met WiFi en probeert verbinding te maken met de SSID en het wachtwoord uit het config-headerbestand.

1. Voeg een oproep aan deze functie toe onderaan de `setup`-functie, nadat de pinnen zijn geconfigureerd.

    ```cpp
    connectWiFi();
    ```

1. Upload deze code naar je apparaat om te controleren of de WiFi-verbinding werkt. Je zou dit moeten zien in de seriële monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Verbinden met MQTT

Zodra de Wio Terminal is verbonden met WiFi, kan deze verbinding maken met de MQTT-broker.

### Taak - verbinden met MQTT

Verbind met de MQTT-broker.

1. Voeg de volgende code toe aan de onderkant van het `config.h`-bestand om de verbindingsdetails voor de MQTT-broker te definiëren:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Vervang `<ID>` door een unieke ID die wordt gebruikt als de naam van deze apparaatclient en later voor de onderwerpen die dit apparaat publiceert en waarop het zich abonneert. De *test.mosquitto.org* broker is openbaar en wordt door veel mensen gebruikt, waaronder andere studenten die deze opdracht uitvoeren. Het hebben van een unieke MQTT-clientnaam en onderwerpnamen zorgt ervoor dat je code niet in conflict komt met die van anderen. Je hebt deze ID ook nodig wanneer je later in deze opdracht de servercode maakt.

    > 💁 Je kunt een website zoals [GUIDGen](https://www.guidgen.com) gebruiken om een unieke ID te genereren.

    De `BROKER` is de URL van de MQTT-broker.

    De `CLIENT_NAME` is een unieke naam voor deze MQTT-client op de broker.

1. Open het `main.cpp`-bestand en voeg de volgende code toe onder de `connectWiFi`-functie en boven de `setup`-functie:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Deze code maakt een WiFi-client met behulp van de Wio Terminal WiFi-bibliotheken en gebruikt deze om een MQTT-client te maken.

1. Voeg hieronder het volgende toe:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Deze functie test de verbinding met de MQTT-broker en maakt opnieuw verbinding als deze niet verbonden is. Het blijft in een lus zolang het niet verbonden is en probeert verbinding te maken met de unieke clientnaam die is gedefinieerd in het config-headerbestand.

    Als de verbinding mislukt, probeert het opnieuw na 5 seconden.

1. Voeg de volgende code toe onder de `reconnectMQTTClient`-functie:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Deze code stelt de MQTT-broker in voor de client en configureert de callback voor wanneer een bericht wordt ontvangen. Vervolgens probeert het verbinding te maken met de broker.

1. Roep de `createMQTTClient`-functie aan in de `setup`-functie nadat de WiFi is verbonden.

1. Vervang de volledige `loop`-functie door het volgende:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Deze code begint met het opnieuw verbinden met de MQTT-broker. Deze verbindingen kunnen gemakkelijk worden verbroken, dus het is de moeite waard om regelmatig te controleren en opnieuw verbinding te maken indien nodig. Vervolgens roept het de `loop`-methode op de MQTT-client aan om eventuele berichten te verwerken die binnenkomen op het onderwerp waarop is geabonneerd. Deze app is single-threaded, dus berichten kunnen niet op een achtergrondthread worden ontvangen; daarom moet tijd op de hoofdthread worden toegewezen om eventuele berichten te verwerken die wachten op de netwerkverbinding.

    Ten slotte zorgt een vertraging van 2 seconden ervoor dat de lichtniveaus niet te vaak worden verzonden en vermindert het stroomverbruik van het apparaat.

1. Upload de code naar je Wio Terminal en gebruik de seriële monitor om te zien dat het apparaat verbinding maakt met WiFi en MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Je kunt deze code vinden in de [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) map.

😀 Je hebt je apparaat succesvol verbonden met een MQTT-broker.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, willen we u erop wijzen dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.