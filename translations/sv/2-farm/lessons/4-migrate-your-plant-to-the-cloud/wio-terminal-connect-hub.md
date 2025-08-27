<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T22:44:48+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "sv"
}
-->
# Anslut din IoT-enhet till molnet - Wio Terminal

I den här delen av lektionen kommer du att ansluta din Wio Terminal till din IoT Hub för att skicka telemetri och ta emot kommandon.

## Anslut din enhet till IoT Hub

Nästa steg är att ansluta din enhet till IoT Hub.

### Uppgift - anslut till IoT Hub

1. Öppna projektet `soil-moisture-sensor` i VS Code.

1. Öppna filen `platformio.ini`. Ta bort biblioteket `knolleary/PubSubClient` som används för att ansluta till den publika MQTT-brokern. Detta behövs inte för att ansluta till IoT Hub.

1. Lägg till följande bibliotek:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Biblioteket `Seeed Arduino RTC` innehåller kod för att interagera med en realtidsklocka i Wio Terminal, som används för att hålla koll på tiden. De övriga biblioteken gör det möjligt för din IoT-enhet att ansluta till IoT Hub.

1. Lägg till följande längst ner i filen `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Detta ställer in en kompilatorflagga som behövs när Arduino IoT Hub-koden kompileras.

1. Öppna headerfilen `config.h`. Ta bort alla MQTT-inställningar och lägg till följande konstant för enhetens anslutningssträng:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Ersätt `<connection string>` med anslutningssträngen för din enhet som du kopierade tidigare.

1. Anslutningen till IoT Hub använder en tidsbaserad token. Detta innebär att IoT-enheten behöver veta den aktuella tiden. Till skillnad från operativsystem som Windows, macOS eller Linux synkroniserar mikrokontroller inte automatiskt tiden via Internet. Du måste därför lägga till kod för att hämta den aktuella tiden från en [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)-server. När tiden har hämtats kan den lagras i en realtidsklocka i Wio Terminal, vilket gör det möjligt att begära korrekt tid senare, förutsatt att enheten inte förlorar ström. Skapa en ny fil som heter `ntp.h` med följande kod:

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

    Detaljerna för denna kod ligger utanför lektionens omfattning. Den definierar en funktion som heter `initTime` som hämtar den aktuella tiden från en NTP-server och använder den för att ställa in klockan på Wio Terminal.

1. Öppna filen `main.cpp` och ta bort all MQTT-kod, inklusive headerfilen `PubSubClient.h`, deklarationen av variabeln `PubSubClient`, metoderna `reconnectMQTTClient` och `createMQTTClient`, samt alla anrop till dessa variabler och metoder. Denna fil ska endast innehålla kod för att ansluta till WiFi, hämta jordfuktighet och skapa ett JSON-dokument med det.

1. Lägg till följande `#include`-direktiv högst upp i filen `main.cpp` för att inkludera headerfiler för IoT Hub-biblioteken och för att ställa in tiden:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Lägg till följande anrop i slutet av funktionen `setup` för att ställa in den aktuella tiden:

    ```cpp
    initTime();
    ```

1. Lägg till följande variabeldeklaration högst upp i filen, precis under `include`-direktiven:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Detta deklarerar en `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, en hantering för anslutningen till IoT Hub.

1. Lägg till följande kod under detta:

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

    Detta deklarerar en callback-funktion som anropas när anslutningen till IoT Hub ändrar status, exempelvis vid anslutning eller frånkoppling. Statusen skickas till seriella porten.

1. Lägg till en funktion för att ansluta till IoT Hub:

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

    Denna kod initierar IoT Hub-bibliotekskoden och skapar en anslutning med hjälp av anslutningssträngen i headerfilen `config.h`. Anslutningen baseras på MQTT. Om anslutningen misslyckas skickas detta till seriella porten - om du ser detta i utdata, kontrollera anslutningssträngen. Slutligen ställs callback-funktionen för anslutningsstatus in.

1. Anropa denna funktion i `setup`-funktionen under anropet till `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Precis som med MQTT-klienten körs denna kod på en enda tråd och behöver tid för att bearbeta meddelanden som skickas av hubben och till hubben. Lägg till följande högst upp i funktionen `loop` för att göra detta:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Bygg och ladda upp denna kod. Du kommer att se anslutningen i seriella monitorn:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    I utdata kan du se NTP-tiden hämtas, följt av att enhetsklienten ansluter. Det kan ta några sekunder att ansluta, så du kan se jordfuktigheten i utdata medan enheten ansluter.

    > 💁 Du kan konvertera UNIX-tiden från NTP till en mer läsbar version med en webbplats som [unixtimestamp.com](https://www.unixtimestamp.com)

## Skicka telemetri

Nu när din enhet är ansluten kan du skicka telemetri till IoT Hub istället för till MQTT-brokern.

### Uppgift - skicka telemetri

1. Lägg till följande funktion ovanför `setup`-funktionen:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Denna kod skapar ett IoT Hub-meddelande från en sträng som skickas som parameter, skickar det till hubben och rensar sedan upp meddelandeobjektet.

1. Anropa denna kod i `loop`-funktionen, precis efter raden där telemetrin skickas till seriella porten:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Hantera kommandon

Din enhet behöver hantera ett kommando från serverkoden för att styra reläet. Detta skickas som en direkt metodförfrågan.

## Uppgift - hantera en direkt metodförfrågan

1. Lägg till följande kod före funktionen `connectIoTHub`:

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

    Denna kod definierar en callback-metod som IoT Hub-biblioteket kan anropa när det tar emot en direkt metodförfrågan. Metoden som begärs skickas i parametern `method_name`. Denna funktion skriver ut den anropade metoden till seriella porten och slår på eller av reläet beroende på metodnamnet.

    > 💁 Detta kan också implementeras i en enda direkt metodförfrågan, där det önskade tillståndet för reläet skickas i en payload som kan skickas med metodförfrågan och är tillgänglig från parametern `payload`.

1. Lägg till följande kod i slutet av funktionen `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Direkt metodförfrågningar behöver ett svar, och svaret består av två delar - ett svar som text och en returkod. Denna kod skapar ett resultat som följande JSON-dokument:

    ```JSON
    {
        "Result": ""
    }
    ```

    Detta kopieras sedan till parametern `response`, och storleken på detta svar ställs in i parametern `response_size`. Denna kod returnerar sedan `IOTHUB_CLIENT_OK` för att visa att metoden hanterades korrekt.

1. Koppla callback-funktionen genom att lägga till följande i slutet av funktionen `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funktionen `loop` kommer att anropa funktionen `IoTHubDeviceClient_LL_DoWork` för att bearbeta händelser som skickas av IoT Hub. Detta anropas endast var 10:e sekund på grund av `delay`, vilket innebär att direktmetoder endast bearbetas var 10:e sekund. För att göra detta mer effektivt kan 10 sekunders fördröjning implementeras som många kortare fördröjningar, där `IoTHubDeviceClient_LL_DoWork` anropas varje gång. Lägg till följande kod ovanför funktionen `loop`:

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

    Denna kod kommer att loopa upprepade gånger, anropa `IoTHubDeviceClient_LL_DoWork` och fördröja med 100 ms varje gång. Den gör detta så många gånger som behövs för att fördröja den tid som anges i parametern `delay_time`. Detta innebär att enheten väntar högst 100 ms för att bearbeta direkt metodförfrågningar.

1. I funktionen `loop`, ta bort anropet till `IoTHubDeviceClient_LL_DoWork` och ersätt anropet till `delay(10000)` med följande för att anropa denna nya funktion:

    ```cpp
    work_delay(10000);
    ```

> 💁 Du kan hitta denna kod i mappen [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Ditt jordfuktighetssensorprogram är anslutet till din IoT Hub!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.