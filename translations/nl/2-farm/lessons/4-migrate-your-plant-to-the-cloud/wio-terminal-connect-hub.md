<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T21:33:53+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "nl"
}
-->
# Verbind je IoT-apparaat met de cloud - Wio Terminal

In dit deel van de les verbind je je Wio Terminal met je IoT Hub om telemetrie te verzenden en opdrachten te ontvangen.

## Verbind je apparaat met IoT Hub

De volgende stap is om je apparaat te verbinden met IoT Hub.

### Taak - verbinden met IoT Hub

1. Open het `soil-moisture-sensor` project in VS Code.

1. Open het bestand `platformio.ini`. Verwijder de afhankelijkheid van de `knolleary/PubSubClient` bibliotheek. Deze werd gebruikt om verbinding te maken met de openbare MQTT-broker en is niet nodig om verbinding te maken met IoT Hub.

1. Voeg de volgende bibliotheekafhankelijkheden toe:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    De `Seeed Arduino RTC` bibliotheek biedt code om te communiceren met een real-time klok in de Wio Terminal, die wordt gebruikt om de tijd bij te houden. De overige bibliotheken maken het mogelijk dat je IoT-apparaat verbinding maakt met IoT Hub.

1. Voeg het volgende toe aan de onderkant van het bestand `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Dit stelt een compiler-vlag in die nodig is bij het compileren van de Arduino IoT Hub-code.

1. Open het headerbestand `config.h`. Verwijder alle MQTT-instellingen en voeg de volgende constante toe voor de apparaatverbindingsreeks:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Vervang `<connection string>` door de verbindingsreeks voor je apparaat die je eerder hebt gekopieerd.

1. De verbinding met IoT Hub gebruikt een op tijd gebaseerd token. Dit betekent dat het IoT-apparaat de huidige tijd moet weten. In tegenstelling tot besturingssystemen zoals Windows, macOS of Linux synchroniseren microcontrollers niet automatisch de huidige tijd via internet. Dit betekent dat je code moet toevoegen om de huidige tijd op te halen van een [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server. Zodra de tijd is opgehaald, kan deze worden opgeslagen in een real-time klok in de Wio Terminal, zodat de juiste tijd later kan worden opgevraagd, mits het apparaat niet zonder stroom komt te zitten. Voeg een nieuw bestand toe genaamd `ntp.h` met de volgende code:

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

    De details van deze code vallen buiten de scope van deze les. Het definieert een functie genaamd `initTime` die de huidige tijd ophaalt van een NTP-server en deze gebruikt om de klok op de Wio Terminal in te stellen.

1. Open het bestand `main.cpp` en verwijder alle MQTT-code, inclusief het headerbestand `PubSubClient.h`, de declaratie van de `PubSubClient`-variabele, de methoden `reconnectMQTTClient` en `createMQTTClient`, en alle oproepen naar deze variabelen en methoden. Dit bestand mag alleen code bevatten om verbinding te maken met WiFi, de bodemvochtigheid op te halen en een JSON-document ermee te maken.

1. Voeg de volgende `#include`-directives toe aan de bovenkant van het bestand `main.cpp` om headerbestanden voor de IoT Hub-bibliotheken en voor het instellen van de tijd op te nemen:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Voeg de volgende oproep toe aan het einde van de `setup`-functie om de huidige tijd in te stellen:

    ```cpp
    initTime();
    ```

1. Voeg de volgende variabeledeclaratie toe aan de bovenkant van het bestand, net onder de include-directives:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Dit declareert een `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, een handle naar een verbinding met de IoT Hub.

1. Voeg hieronder de volgende code toe:

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

    Dit declareert een callbackfunctie die wordt aangeroepen wanneer de verbinding met de IoT Hub van status verandert, zoals verbinden of verbreken. De status wordt naar de seriële poort gestuurd.

1. Voeg hieronder een functie toe om verbinding te maken met IoT Hub:

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

    Deze code initialiseert de IoT Hub-bibliotheekcode en maakt vervolgens een verbinding met behulp van de verbindingsreeks in het headerbestand `config.h`. Deze verbinding is gebaseerd op MQTT. Als de verbinding mislukt, wordt dit naar de seriële poort gestuurd - als je dit in de uitvoer ziet, controleer dan de verbindingsreeks. Ten slotte wordt de callback voor de verbindingsstatus ingesteld.

1. Roep deze functie aan in de `setup`-functie onder de oproep naar `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Net zoals bij de MQTT-client, draait deze code op een enkele thread en heeft tijd nodig om berichten te verwerken die door de hub worden verzonden en naar de hub worden verzonden. Voeg het volgende toe aan de bovenkant van de `loop`-functie om dit te doen:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Bouw en upload deze code. Je zult de verbinding zien in de seriële monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    In de uitvoer kun je zien dat de NTP-tijd wordt opgehaald, gevolgd door het verbinden van de apparaatclient. Het kan enkele seconden duren om verbinding te maken, dus je kunt de bodemvochtigheid in de uitvoer zien terwijl het apparaat verbinding maakt.

    > 💁 Je kunt de UNIX-tijd van de NTP omzetten naar een meer leesbare versie met een website zoals [unixtimestamp.com](https://www.unixtimestamp.com).

## Telemetrie verzenden

Nu je apparaat is verbonden, kun je telemetrie naar de IoT Hub verzenden in plaats van naar de MQTT-broker.

### Taak - telemetrie verzenden

1. Voeg de volgende functie toe boven de `setup`-functie:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Deze code maakt een IoT Hub-bericht van een string die als parameter wordt doorgegeven, verzendt het naar de hub en ruimt vervolgens het berichtobject op.

1. Roep deze code aan in de `loop`-functie, net na de regel waar de telemetrie naar de seriële poort wordt verzonden:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Opdrachten verwerken

Je apparaat moet een opdracht van de servercode verwerken om het relais te bedienen. Dit wordt verzonden als een directe methodeaanvraag.

## Taak - een directe methodeaanvraag verwerken

1. Voeg de volgende code toe vóór de functie `connectIoTHub`:

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

    Deze code definieert een callbackmethode die de IoT Hub-bibliotheek kan aanroepen wanneer deze een directe methodeaanvraag ontvangt. De methode die wordt aangevraagd, wordt verzonden in de parameter `method_name`. Deze functie print de aangeroepen methode naar de seriële poort en schakelt het relais in of uit afhankelijk van de methode naam.

    > 💁 Dit kan ook worden geïmplementeerd in een enkele directe methodeaanvraag, waarbij de gewenste status van het relais wordt doorgegeven in een payload die kan worden doorgegeven met de methodeaanvraag en beschikbaar is vanuit de parameter `payload`.

1. Voeg de volgende code toe aan het einde van de functie `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Directe methodeaanvragen hebben een antwoord nodig, en het antwoord bestaat uit twee delen - een antwoord als tekst en een retourcode. Deze code maakt een resultaat als het volgende JSON-document:

    ```JSON
    {
        "Result": ""
    }
    ```

    Dit wordt vervolgens gekopieerd naar de parameter `response`, en de grootte van dit antwoord wordt ingesteld in de parameter `response_size`. Deze code retourneert vervolgens `IOTHUB_CLIENT_OK` om aan te geven dat de methode correct is afgehandeld.

1. Koppel de callback door het volgende toe te voegen aan het einde van de functie `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. De `loop`-functie roept de functie `IoTHubDeviceClient_LL_DoWork` aan om gebeurtenissen te verwerken die door IoT Hub worden verzonden. Dit wordt slechts om de 10 seconden aangeroepen vanwege de `delay`, wat betekent dat directe methoden slechts om de 10 seconden worden verwerkt. Om dit efficiënter te maken, kan de vertraging van 10 seconden worden geïmplementeerd als veel kortere vertragingen, waarbij `IoTHubDeviceClient_LL_DoWork` elke keer wordt aangeroepen. Voeg hiervoor de volgende code toe boven de `loop`-functie:

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

    Deze code zal herhaaldelijk in een lus draaien, `IoTHubDeviceClient_LL_DoWork` aanroepen en elke keer 100ms vertragen. Het zal dit zo vaak doen als nodig is om te vertragen voor de hoeveelheid tijd die wordt gegeven in de parameter `delay_time`. Dit betekent dat het apparaat maximaal 100ms wacht om directe methodeaanvragen te verwerken.

1. Verwijder in de `loop`-functie de oproep naar `IoTHubDeviceClient_LL_DoWork` en vervang de oproep `delay(10000)` door het volgende om deze nieuwe functie aan te roepen:

    ```cpp
    work_delay(10000);
    ```

> 💁 Je kunt deze code vinden in de [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) map.

😀 Je bodemvochtigheidssensorprogramma is verbonden met je IoT Hub!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.