<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T22:45:13+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "da"
}
-->
# Tilslut din IoT-enhed til skyen - Wio Terminal

I denne del af lektionen vil du forbinde din Wio Terminal til din IoT Hub for at sende telemetri og modtage kommandoer.

## Forbind din enhed til IoT Hub

Det næste trin er at forbinde din enhed til IoT Hub.

### Opgave - forbind til IoT Hub

1. Åbn projektet `soil-moisture-sensor` i VS Code.

1. Åbn filen `platformio.ini`. Fjern afhængigheden af biblioteket `knolleary/PubSubClient`. Dette blev brugt til at forbinde til den offentlige MQTT-broker og er ikke nødvendigt for at forbinde til IoT Hub.

1. Tilføj følgende biblioteksafhængigheder:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Biblioteket `Seeed Arduino RTC` giver kode til at interagere med et realtidsur i Wio Terminal, som bruges til at holde styr på tiden. De resterende biblioteker gør det muligt for din IoT-enhed at forbinde til IoT Hub.

1. Tilføj følgende til bunden af filen `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Dette sætter et compiler-flag, der er nødvendigt, når Arduino IoT Hub-koden kompileres.

1. Åbn header-filen `config.h`. Fjern alle MQTT-indstillingerne, og tilføj følgende konstant for enhedens forbindelsesstreng:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Erstat `<connection string>` med forbindelsesstrengen for din enhed, som du kopierede tidligere.

1. Forbindelsen til IoT Hub bruger et tidsbaseret token. Det betyder, at IoT-enheden skal kende den aktuelle tid. I modsætning til operativsystemer som Windows, macOS eller Linux synkroniserer mikrokontrollere ikke automatisk den aktuelle tid over internettet. Det betyder, at du skal tilføje kode for at hente den aktuelle tid fra en [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)-server. Når tiden er hentet, kan den gemmes i et realtidsur i Wio Terminal, så den korrekte tid kan anmodes om senere, forudsat at enheden ikke mister strøm. Tilføj en ny fil kaldet `ntp.h` med følgende kode:

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

    Detaljerne i denne kode ligger uden for denne lektions omfang. Den definerer en funktion kaldet `initTime`, som henter den aktuelle tid fra en NTP-server og bruger den til at indstille uret på Wio Terminal.

1. Åbn filen `main.cpp`, og fjern al MQTT-koden, inklusive header-filen `PubSubClient.h`, deklarationen af variablen `PubSubClient`, metoderne `reconnectMQTTClient` og `createMQTTClient` samt alle kald til disse variabler og metoder. Denne fil skal kun indeholde kode til at forbinde til WiFi, hente jordfugtighed og oprette et JSON-dokument med det.

1. Tilføj følgende `#include`-direktiver øverst i filen `main.cpp` for at inkludere header-filer til IoT Hub-bibliotekerne og til at indstille tiden:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Tilføj følgende kald til slutningen af funktionen `setup` for at indstille den aktuelle tid:

    ```cpp
    initTime();
    ```

1. Tilføj følgende variabeldeklaration øverst i filen, lige under include-direktiverne:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Dette erklærer en `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, et håndtag til en forbindelse til IoT Hub.

1. Tilføj nedenunder følgende kode:

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

    Dette erklærer en callback-funktion, der vil blive kaldt, når forbindelsen til IoT Hub ændrer status, såsom at forbinde eller afbryde. Statussen sendes til den serielle port.

1. Tilføj nedenunder en funktion til at forbinde til IoT Hub:

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

    Denne kode initialiserer IoT Hub-bibliotekskoden og opretter derefter en forbindelse ved hjælp af forbindelsesstrengen i header-filen `config.h`. Denne forbindelse er baseret på MQTT. Hvis forbindelsen fejler, sendes dette til den serielle port - hvis du ser dette i outputtet, skal du tjekke forbindelsesstrengen. Endelig opsættes callback-funktionen for forbindelsesstatus.

1. Kald denne funktion i funktionen `setup` under kaldet til `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Ligesom med MQTT-klienten kører denne kode på en enkelt tråd og har derfor brug for tid til at behandle meddelelser, der sendes af hubben og til hubben. Tilføj følgende øverst i funktionen `loop` for at gøre dette:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Byg og upload denne kode. Du vil se forbindelsen i den serielle monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    I outputtet kan du se, at NTP-tiden hentes, efterfulgt af, at enhedsklienten forbinder. Det kan tage et par sekunder at forbinde, så du kan se jordfugtigheden i outputtet, mens enheden forbinder.

    > 💁 Du kan konvertere UNIX-tiden for NTP til en mere læsbar version ved hjælp af en hjemmeside som [unixtimestamp.com](https://www.unixtimestamp.com)

## Send telemetri

Nu hvor din enhed er forbundet, kan du sende telemetri til IoT Hub i stedet for til MQTT-brokeren.

### Opgave - send telemetri

1. Tilføj følgende funktion over funktionen `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Denne kode opretter en IoT Hub-meddelelse fra en streng, der sendes som en parameter, sender den til hubben og rydder derefter op i meddelelsesobjektet.

1. Kald denne kode i funktionen `loop`, lige efter linjen, hvor telemetrien sendes til den serielle port:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Håndter kommandoer

Din enhed skal kunne håndtere en kommando fra serverkoden for at styre relæet. Dette sendes som en direkte metodeanmodning.

## Opgave - håndter en direkte metodeanmodning

1. Tilføj følgende kode før funktionen `connectIoTHub`:

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

    Denne kode definerer en callback-metode, som IoT Hub-biblioteket kan kalde, når det modtager en direkte metodeanmodning. Den metode, der anmodes om, sendes i parameteren `method_name`. Denne funktion udskriver den kaldte metode til den serielle port og tænder eller slukker for relæet afhængigt af metodenavnet.

    > 💁 Dette kunne også implementeres i en enkelt direkte metodeanmodning, hvor den ønskede tilstand for relæet sendes i en payload, der kan sendes med metodeanmodningen og er tilgængelig fra parameteren `payload`.

1. Tilføj følgende kode til slutningen af funktionen `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Direkte metodeanmodninger kræver et svar, og svaret består af to dele - et svar som tekst og en returkode. Denne kode opretter et resultat som følgende JSON-dokument:

    ```JSON
    {
        "Result": ""
    }
    ```

    Dette kopieres derefter ind i parameteren `response`, og størrelsen af dette svar sættes i parameteren `response_size`. Denne kode returnerer derefter `IOTHUB_CLIENT_OK` for at vise, at metoden blev håndteret korrekt.

1. Tilslut callback-funktionen ved at tilføje følgende til slutningen af funktionen `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funktionen `loop` vil kalde funktionen `IoTHubDeviceClient_LL_DoWork` for at behandle hændelser sendt af IoT Hub. Dette kaldes kun hvert 10. sekund på grund af `delay`, hvilket betyder, at direkte metoder kun behandles hvert 10. sekund. For at gøre dette mere effektivt kan forsinkelsen på 10 sekunder implementeres som mange kortere forsinkelser, hvor `IoTHubDeviceClient_LL_DoWork` kaldes hver gang. For at gøre dette skal du tilføje følgende kode over funktionen `loop`:

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

    Denne kode vil gentage sig gentagne gange, kalde `IoTHubDeviceClient_LL_DoWork` og forsinke i 100 ms hver gang. Den vil gøre dette så mange gange som nødvendigt for at forsinke i den tid, der gives i parameteren `delay_time`. Dette betyder, at enheden højst venter 100 ms på at behandle direkte metodeanmodninger.

1. I funktionen `loop` skal du fjerne kaldet til `IoTHubDeviceClient_LL_DoWork` og erstatte kaldet `delay(10000)` med følgende for at kalde denne nye funktion:

    ```cpp
    work_delay(10000);
    ```

> 💁 Du kan finde denne kode i mappen [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Dit jordfugtighedssensorprogram er nu forbundet til din IoT Hub!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.