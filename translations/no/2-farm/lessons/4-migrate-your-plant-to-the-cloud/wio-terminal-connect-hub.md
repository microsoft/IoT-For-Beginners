<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T22:45:40+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "no"
}
-->
# Koble IoT-enheten din til skyen - Wio Terminal

I denne delen av leksjonen skal du koble Wio Terminal til IoT Hub for å sende telemetri og motta kommandoer.

## Koble enheten til IoT Hub

Neste steg er å koble enheten til IoT Hub.

### Oppgave - koble til IoT Hub

1. Åpne prosjektet `soil-moisture-sensor` i VS Code.

1. Åpne filen `platformio.ini`. Fjern bibliotekavhengigheten `knolleary/PubSubClient`. Dette ble brukt for å koble til en offentlig MQTT-broker og er ikke nødvendig for å koble til IoT Hub.

1. Legg til følgende bibliotekavhengigheter:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Biblioteket `Seeed Arduino RTC` gir kode for å bruke en sanntidsklokke i Wio Terminal, som brukes til å holde styr på tiden. De andre bibliotekene lar IoT-enheten din koble til IoT Hub.

1. Legg til følgende nederst i filen `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Dette setter et kompilatorflagg som er nødvendig når Arduino IoT Hub-koden kompileres.

1. Åpne header-filen `config.h`. Fjern alle MQTT-innstillingene og legg til følgende konstant for enhetens tilkoblingsstreng:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Erstatt `<connection string>` med tilkoblingsstrengen for enheten din som du kopierte tidligere.

1. Tilkoblingen til IoT Hub bruker en tidsbasert token. Dette betyr at IoT-enheten må vite gjeldende tid. I motsetning til operativsystemer som Windows, macOS eller Linux, synkroniserer ikke mikrokontrollere automatisk tiden over Internett. Dette betyr at du må legge til kode for å hente gjeldende tid fra en [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)-server. Når tiden er hentet, kan den lagres i en sanntidsklokke i Wio Terminal, slik at korrekt tid kan hentes senere, forutsatt at enheten ikke mister strøm. Legg til en ny fil kalt `ntp.h` med følgende kode:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    Detaljene i denne koden er utenfor omfanget av denne leksjonen. Den definerer en funksjon kalt `initTime` som henter gjeldende tid fra en NTP-server og bruker den til å stille klokken på Wio Terminal.

1. Åpne filen `main.cpp` og fjern all MQTT-kode, inkludert header-filen `PubSubClient.h`, deklarasjonen av variabelen `PubSubClient`, metodene `reconnectMQTTClient` og `createMQTTClient`, og alle kall til disse variablene og metodene. Denne filen skal kun inneholde kode for å koble til WiFi, hente jordfuktighet og lage et JSON-dokument med det.

1. Legg til følgende `#include`-direktiver øverst i filen `main.cpp` for å inkludere header-filer for IoT Hub-bibliotekene og for å stille inn tiden:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Legg til følgende kall på slutten av `setup`-funksjonen for å stille inn gjeldende tid:

    ```cpp
    initTime();
    ```

1. Legg til følgende variabeldeklarasjon øverst i filen, rett under `include`-direktivene:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Dette deklarerer en `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, et håndtak for en tilkobling til IoT Hub.

1. Under dette, legg til følgende kode:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Dette deklarerer en callback-funksjon som vil bli kalt når tilkoblingen til IoT Hub endrer status, for eksempel ved tilkobling eller frakobling. Statusen sendes til seriellporten.

1. Under dette, legg til en funksjon for å koble til IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Denne koden initialiserer IoT Hub-bibliotekskoden og oppretter deretter en tilkobling ved hjelp av tilkoblingsstrengen i header-filen `config.h`. Denne tilkoblingen er basert på MQTT. Hvis tilkoblingen mislykkes, sendes dette til seriellporten - hvis du ser dette i utdataene, sjekk tilkoblingsstrengen. Til slutt settes callback-funksjonen for tilkoblingsstatus opp.

1. Kall denne funksjonen i `setup`-funksjonen under kallet til `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Akkurat som med MQTT-klienten, kjører denne koden på en enkelt tråd og trenger tid til å behandle meldinger som sendes av huben og til huben. Legg til følgende øverst i `loop`-funksjonen for å gjøre dette:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Bygg og last opp denne koden. Du vil se tilkoblingen i seriellmonitoren:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    I utdataene kan du se at NTP-tiden hentes, etterfulgt av at enhetsklienten kobler til. Det kan ta noen sekunder å koble til, så du kan se jordfuktigheten i utdataene mens enheten kobler til.

    > 💁 Du kan konvertere UNIX-tiden for NTP til en mer lesbar versjon ved å bruke et nettsted som [unixtimestamp.com](https://www.unixtimestamp.com)

## Send telemetri

Nå som enheten din er koblet til, kan du sende telemetri til IoT Hub i stedet for MQTT-brokeren.

### Oppgave - send telemetri

1. Legg til følgende funksjon over `setup`-funksjonen:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Denne koden oppretter en IoT Hub-melding fra en streng som sendes som en parameter, sender den til huben, og rydder deretter opp i meldingsobjektet.

1. Kall denne koden i `loop`-funksjonen, rett etter linjen der telemetrien sendes til seriellporten:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Håndtere kommandoer

Enheten din må håndtere en kommando fra serverkoden for å kontrollere reléet. Dette sendes som en direkte metodeforespørsel.

## Oppgave - håndtere en direkte metodeforespørsel

1. Legg til følgende kode før funksjonen `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Denne koden definerer en callback-metode som IoT Hub-biblioteket kan kalle når det mottar en direkte metodeforespørsel. Metoden som forespørres, sendes i parameteren `method_name`. Denne funksjonen skriver metoden som ble kalt til seriellporten, og slår deretter reléet av eller på avhengig av metodenavnet.

    > 💁 Dette kan også implementeres i en enkelt direkte metodeforespørsel, der ønsket tilstand for reléet sendes i en nyttelast som kan sendes med metodeforespørselen og er tilgjengelig fra parameteren `payload`.

1. Legg til følgende kode på slutten av funksjonen `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Direkte metodeforespørsler trenger et svar, og svaret består av to deler - et svar som tekst og en returkode. Denne koden vil opprette et resultat som følgende JSON-dokument:

    ```JSON
    {
        "Result": ""
    }
    ```

    Dette kopieres deretter inn i parameteren `response`, og størrelsen på dette svaret settes i parameteren `response_size`. Denne koden returnerer deretter `IOTHUB_CLIENT_OK` for å vise at metoden ble håndtert korrekt.

1. Koble opp callback-funksjonen ved å legge til følgende på slutten av funksjonen `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funksjonen `loop` vil kalle funksjonen `IoTHubDeviceClient_LL_DoWork` for å behandle hendelser sendt av IoT Hub. Dette kalles bare hvert 10. sekund på grunn av `delay`, noe som betyr at direkte metoder bare behandles hvert 10. sekund. For å gjøre dette mer effektivt kan 10-sekunders forsinkelsen implementeres som mange kortere forsinkelser, der `IoTHubDeviceClient_LL_DoWork` kalles hver gang. For å gjøre dette, legg til følgende kode over funksjonen `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Denne koden vil loope gjentatte ganger, kalle `IoTHubDeviceClient_LL_DoWork` og forsinke i 100 ms hver gang. Den vil gjøre dette så mange ganger som nødvendig for å forsinke i den tiden som er gitt i parameteren `delay_time`. Dette betyr at enheten venter maksimalt 100 ms for å behandle direkte metodeforespørsler.

1. I funksjonen `loop`, fjern kallet til `IoTHubDeviceClient_LL_DoWork`, og erstatt kallet til `delay(10000)` med følgende for å kalle denne nye funksjonen:

    ```cpp
    work_delay(10000);
    ```

> 💁 Du finner denne koden i mappen [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Programmet for jordfuktighetssensoren din er nå koblet til IoT Hub!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.