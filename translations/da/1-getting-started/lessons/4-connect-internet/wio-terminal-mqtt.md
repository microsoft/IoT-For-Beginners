<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T21:50:47+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "da"
}
-->
# Styr din natlampe over internettet - Wio Terminal

IoT-enheden skal kodes til at kommunikere med *test.mosquitto.org* ved hjælp af MQTT for at sende telemetriværdier med lysfølerens aflæsning og modtage kommandoer til at styre LED'en.

I denne del af lektionen vil du forbinde din Wio Terminal til en MQTT-broker.

## Installer WiFi- og MQTT Arduino-biblioteker

For at kommunikere med MQTT-brokeren skal du installere nogle Arduino-biblioteker, der gør det muligt at bruge WiFi-chippen i Wio Terminal og kommunikere med MQTT. Når du udvikler til Arduino-enheder, kan du bruge et bredt udvalg af biblioteker, der indeholder open source-kode og implementerer en lang række funktioner. Seeed udgiver biblioteker til Wio Terminal, som gør det muligt at kommunikere via WiFi. Andre udviklere har udgivet biblioteker til at kommunikere med MQTT-brokere, og du vil bruge disse med din enhed.

Disse biblioteker leveres som kildekode, der kan importeres automatisk til PlatformIO og kompileres til din enhed. På denne måde vil Arduino-biblioteker fungere på enhver enhed, der understøtter Arduino-frameworket, forudsat at enheden har den specifikke hardware, som biblioteket kræver. Nogle biblioteker, såsom Seeed WiFi-bibliotekerne, er specifikke for visse hardwaretyper.

Biblioteker kan installeres globalt og kompileres efter behov eller i et specifikt projekt. Til denne opgave vil bibliotekerne blive installeret i projektet.

✅ Du kan lære mere om bibliotekshåndtering og hvordan du finder og installerer biblioteker i [PlatformIO library documentation](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Opgave - installer WiFi- og MQTT Arduino-biblioteker

Installer Arduino-bibliotekerne.

1. Åbn natlampeprojektet i VS Code.

1. Tilføj følgende til slutningen af `platformio.ini`-filen:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Dette importerer Seeed WiFi-bibliotekerne. `@ <number>`-syntaksen refererer til et specifikt versionsnummer af biblioteket.

    > 💁 Du kan fjerne `@ <number>` for altid at bruge den nyeste version af bibliotekerne, men der er ingen garantier for, at senere versioner vil fungere med koden nedenfor. Koden her er testet med denne version af bibliotekerne.

    Dette er alt, hvad du behøver for at tilføje bibliotekerne. Næste gang PlatformIO bygger projektet, vil det downloade kildekoden til disse biblioteker og kompilere dem ind i dit projekt.

1. Tilføj følgende til `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Dette importerer [PubSubClient](https://github.com/knolleary/pubsubclient), en Arduino MQTT-klient.

## Forbind til WiFi

Wio Terminal kan nu forbindes til WiFi.

### Opgave - forbind til WiFi

Forbind Wio Terminal til WiFi.

1. Opret en ny fil i `src`-mappen kaldet `config.h`. Du kan gøre dette ved at vælge `src`-mappen eller `main.cpp`-filen indeni og vælge **Ny fil**-knappen fra explorer. Denne knap vises kun, når din cursor er over explorer.

    ![Den nye fil-knap](../../../../../translated_images/da/vscode-new-file-button.182702340fe6723c.png)

1. Tilføj følgende kode til denne fil for at definere konstanter for dine WiFi-legitimationsoplysninger:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Erstat `<SSID>` med SSID'en for dit WiFi. Erstat `<PASSWORD>` med din WiFi-adgangskode.

1. Åbn `main.cpp`-filen.

1. Tilføj følgende `#include`-direktiver til toppen af filen:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Dette inkluderer headerfilerne for de biblioteker, du tilføjede tidligere, samt config-headerfilen. Disse headerfiler er nødvendige for at fortælle PlatformIO at inkludere koden fra bibliotekerne. Uden eksplicit at inkludere disse headerfiler vil noget kode ikke blive kompileret, og du vil få compiler-fejl.

1. Tilføj følgende kode over `setup`-funktionen:

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

    Denne kode kører i en løkke, mens enheden ikke er forbundet til WiFi, og forsøger at oprette forbindelse ved hjælp af SSID og adgangskode fra config-headerfilen.

1. Tilføj et kald til denne funktion nederst i `setup`-funktionen, efter at pins er blevet konfigureret.

    ```cpp
    connectWiFi();
    ```

1. Upload denne kode til din enhed for at kontrollere, at WiFi-forbindelsen fungerer. Du bør se dette i den serielle monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Forbind til MQTT

Når Wio Terminal er forbundet til WiFi, kan den forbindes til MQTT-brokeren.

### Opgave - forbind til MQTT

Forbind til MQTT-brokeren.

1. Tilføj følgende kode nederst i `config.h`-filen for at definere forbindelsesdetaljer for MQTT-brokeren:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Erstat `<ID>` med et unikt ID, der vil blive brugt som navnet på denne enhedsklient og senere til de emner, som denne enhed publicerer og abonnerer på. *test.mosquitto.org*-brokeren er offentlig og bruges af mange mennesker, inklusive andre studerende, der arbejder med denne opgave. At have et unikt MQTT-klientnavn og emnenavne sikrer, at din kode ikke kolliderer med andres. Du vil også bruge dette ID, når du opretter serverkoden senere i denne opgave.

    > 💁 Du kan bruge en hjemmeside som [GUIDGen](https://www.guidgen.com) til at generere et unikt ID.

    `BROKER` er URL'en til MQTT-brokeren.

    `CLIENT_NAME` er et unikt navn for denne MQTT-klient på brokeren.

1. Åbn `main.cpp`-filen, og tilføj følgende kode under `connectWiFi`-funktionen og over `setup`-funktionen:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Denne kode opretter en WiFi-klient ved hjælp af Wio Terminal WiFi-bibliotekerne og bruger den til at oprette en MQTT-klient.

1. Tilføj følgende kode nedenunder:

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

    Denne funktion tester forbindelsen til MQTT-brokeren og genopretter forbindelsen, hvis den ikke er forbundet. Den kører i en løkke, mens den ikke er forbundet, og forsøger at oprette forbindelse ved hjælp af det unikke klientnavn, der er defineret i config-headerfilen.

    Hvis forbindelsen mislykkes, prøver den igen efter 5 sekunder.

1. Tilføj følgende kode under `reconnectMQTTClient`-funktionen:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Denne kode indstiller MQTT-brokeren for klienten samt opsætter callback-funktionen, når en besked modtages. Den forsøger derefter at oprette forbindelse til brokeren.

1. Kald `createMQTTClient`-funktionen i `setup`-funktionen, efter at WiFi er forbundet.

1. Erstat hele `loop`-funktionen med følgende:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Denne kode starter med at genoprette forbindelsen til MQTT-brokeren. Disse forbindelser kan nemt blive afbrudt, så det er værd at regelmæssigt kontrollere og genoprette forbindelsen, hvis det er nødvendigt. Derefter kalder den `loop`-metoden på MQTT-klienten for at behandle eventuelle beskeder, der kommer ind på det emne, der er abonneret på. Denne app er enkelttrådet, så beskeder kan ikke modtages på en baggrundstråd, derfor skal der afsættes tid på hovedtråden til at behandle eventuelle beskeder, der venter på netværksforbindelsen.

    Endelig sikrer en forsinkelse på 2 sekunder, at lysniveauerne ikke sendes for ofte og reducerer enhedens strømforbrug.

1. Upload koden til din Wio Terminal, og brug den serielle monitor til at se enheden oprette forbindelse til WiFi og MQTT.

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

> 💁 Du kan finde denne kode i [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal)-mappen.

😀 Du har med succes forbundet din enhed til en MQTT-broker.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.