<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T21:51:14+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "no"
}
-->
# Kontroller nattlyset ditt over Internett - Wio Terminal

IoT-enheten må kodes for å kommunisere med *test.mosquitto.org* ved hjelp av MQTT for å sende telemetridata med lysmålinger og motta kommandoer for å kontrollere LED-en.

I denne delen av leksjonen skal du koble Wio Terminal til en MQTT-broker.

## Installer WiFi- og MQTT Arduino-biblioteker

For å kommunisere med MQTT-brokeren må du installere noen Arduino-biblioteker som gjør det mulig å bruke WiFi-brikken i Wio Terminal og kommunisere med MQTT. Når du utvikler for Arduino-enheter, kan du bruke et bredt spekter av biblioteker som inneholder åpen kildekode og implementerer mange ulike funksjoner. Seeed publiserer biblioteker for Wio Terminal som gjør det mulig å kommunisere over WiFi. Andre utviklere har publisert biblioteker for å kommunisere med MQTT-brokere, og du vil bruke disse med enheten din.

Disse bibliotekene leveres som kildekode som kan importeres automatisk til PlatformIO og kompileres for enheten din. På denne måten vil Arduino-biblioteker fungere på alle enheter som støtter Arduino-rammeverket, forutsatt at enheten har nødvendig maskinvare som biblioteket krever. Noen biblioteker, som Seeed WiFi-bibliotekene, er spesifikke for visse maskinvaretyper.

Biblioteker kan installeres globalt og kompileres ved behov, eller installeres i et spesifikt prosjekt. For denne oppgaven vil bibliotekene bli installert i prosjektet.

✅ Du kan lære mer om bibliotekshåndtering og hvordan du finner og installerer biblioteker i [PlatformIOs bibliotekdokumentasjon](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Oppgave - installer WiFi- og MQTT Arduino-biblioteker

Installer Arduino-bibliotekene.

1. Åpne nattlysprosjektet i VS Code.

1. Legg til følgende på slutten av `platformio.ini`-filen:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Dette importerer Seeed WiFi-bibliotekene. `@ <number>`-syntaksen refererer til et spesifikt versjonsnummer av biblioteket.

    > 💁 Du kan fjerne `@ <number>` for alltid å bruke den nyeste versjonen av bibliotekene, men det er ingen garantier for at senere versjoner vil fungere med koden nedenfor. Koden her er testet med denne versjonen av bibliotekene.

    Dette er alt du trenger å gjøre for å legge til bibliotekene. Neste gang PlatformIO bygger prosjektet, vil det laste ned kildekoden for disse bibliotekene og kompilere dem inn i prosjektet ditt.

1. Legg til følgende i `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Dette importerer [PubSubClient](https://github.com/knolleary/pubsubclient), en Arduino MQTT-klient.

## Koble til WiFi

Wio Terminal kan nå kobles til WiFi.

### Oppgave - koble til WiFi

Koble Wio Terminal til WiFi.

1. Opprett en ny fil i `src`-mappen kalt `config.h`. Du kan gjøre dette ved å velge `src`-mappen, eller `main.cpp`-filen inni, og velge **Ny fil**-knappen fra utforskeren. Denne knappen vises bare når markøren din er over utforskeren.

    ![Knappen for ny fil](../../../../../translated_images/no/vscode-new-file-button.182702340fe6723c.png)

1. Legg til følgende kode i denne filen for å definere konstanter for WiFi-legitimasjonen din:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Erstatt `<SSID>` med SSID-en til WiFi-nettverket ditt. Erstatt `<PASSWORD>` med WiFi-passordet ditt.

1. Åpne `main.cpp`-filen.

1. Legg til følgende `#include`-direktiver øverst i filen:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Dette inkluderer headerfiler for bibliotekene du la til tidligere, samt config-headerfilen. Disse headerfilene er nødvendige for å fortelle PlatformIO å inkludere koden fra bibliotekene. Uten eksplisitt å inkludere disse headerfilene, vil ikke all kode bli kompilert inn, og du vil få kompilatorfeil.

1. Legg til følgende kode over `setup`-funksjonen:

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

    Denne koden kjører i en løkke mens enheten ikke er koblet til WiFi, og prøver å koble til ved hjelp av SSID og passord fra config-headerfilen.

1. Legg til et kall til denne funksjonen nederst i `setup`-funksjonen, etter at pinnene er konfigurert.

    ```cpp
    connectWiFi();
    ```

1. Last opp denne koden til enheten din for å sjekke at WiFi-tilkoblingen fungerer. Du bør se dette i seriemonitoren.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Koble til MQTT

Når Wio Terminal er koblet til WiFi, kan den koble til MQTT-brokeren.

### Oppgave - koble til MQTT

Koble til MQTT-brokeren.

1. Legg til følgende kode nederst i `config.h`-filen for å definere tilkoblingsdetaljene for MQTT-brokeren:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Erstatt `<ID>` med en unik ID som vil bli brukt som navnet på denne enhetsklienten, og senere for emnene som denne enheten publiserer og abonnerer på. *test.mosquitto.org*-brokeren er offentlig og brukes av mange, inkludert andre studenter som jobber med denne oppgaven. Å ha et unikt MQTT-klientnavn og emnenavn sikrer at koden din ikke kolliderer med andres. Du vil også trenge denne ID-en når du lager serverkoden senere i oppgaven.

    > 💁 Du kan bruke et nettsted som [GUIDGen](https://www.guidgen.com) for å generere en unik ID.

    `BROKER` er URL-en til MQTT-brokeren.

    `CLIENT_NAME` er et unikt navn for denne MQTT-klienten på brokeren.

1. Åpne `main.cpp`-filen, og legg til følgende kode under `connectWiFi`-funksjonen og over `setup`-funksjonen:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Denne koden oppretter en WiFi-klient ved hjelp av Wio Terminal WiFi-bibliotekene og bruker den til å opprette en MQTT-klient.

1. Under denne koden, legg til følgende:

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

    Denne funksjonen tester tilkoblingen til MQTT-brokeren og kobler til igjen hvis den ikke er tilkoblet. Den kjører i en løkke så lenge den ikke er tilkoblet og forsøker å koble til ved hjelp av det unike klientnavnet som er definert i config-headerfilen.

    Hvis tilkoblingen mislykkes, prøver den igjen etter 5 sekunder.

1. Legg til følgende kode under `reconnectMQTTClient`-funksjonen:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Denne koden setter MQTT-brokeren for klienten, samt setter opp callback-funksjonen når en melding mottas. Den forsøker deretter å koble til brokeren.

1. Kall `createMQTTClient`-funksjonen i `setup`-funksjonen etter at WiFi er tilkoblet.

1. Erstatt hele `loop`-funksjonen med følgende:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Denne koden starter med å koble til MQTT-brokeren igjen. Disse tilkoblingene kan lett brytes, så det er verdt å regelmessig sjekke og koble til igjen hvis nødvendig. Den kaller deretter `loop`-metoden på MQTT-klienten for å behandle eventuelle meldinger som kommer inn på emnet det abonneres på. Denne appen er enkelttrådet, så meldinger kan ikke mottas på en bakgrunnstråd, derfor må det settes av tid på hovedtråden til å behandle eventuelle meldinger som venter på nettverkstilkoblingen.

    Til slutt sørger en forsinkelse på 2 sekunder for at lysnivåene ikke sendes for ofte og reduserer strømforbruket til enheten.

1. Last opp koden til Wio Terminal, og bruk seriemonitoren for å se enheten koble til WiFi og MQTT.

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

> 💁 Du finner denne koden i [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal)-mappen.

😀 Du har nå koblet enheten din til en MQTT-broker.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.