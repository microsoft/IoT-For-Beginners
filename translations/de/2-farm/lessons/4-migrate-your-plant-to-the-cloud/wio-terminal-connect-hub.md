<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-25T21:47:34+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "de"
}
-->
# Verbinden Sie Ihr IoT-Gerät mit der Cloud - Wio Terminal

In diesem Teil der Lektion verbinden Sie Ihr Wio Terminal mit Ihrem IoT Hub, um Telemetrie zu senden und Befehle zu empfangen.

## Verbinden Sie Ihr Gerät mit dem IoT Hub

Der nächste Schritt besteht darin, Ihr Gerät mit dem IoT Hub zu verbinden.

### Aufgabe - Verbindung mit dem IoT Hub herstellen

1. Öffnen Sie das Projekt `soil-moisture-sensor` in VS Code.

1. Öffnen Sie die Datei `platformio.ini`. Entfernen Sie die Bibliotheksabhängigkeit `knolleary/PubSubClient`. Diese wurde verwendet, um eine Verbindung zu einem öffentlichen MQTT-Broker herzustellen, ist jedoch nicht erforderlich, um eine Verbindung zum IoT Hub herzustellen.

1. Fügen Sie die folgenden Bibliotheksabhängigkeiten hinzu:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Die Bibliothek `Seeed Arduino RTC` stellt Code bereit, um mit einer Echtzeituhr im Wio Terminal zu interagieren, die zur Zeitverfolgung verwendet wird. Die übrigen Bibliotheken ermöglichen Ihrem IoT-Gerät die Verbindung mit dem IoT Hub.

1. Fügen Sie Folgendes am Ende der Datei `platformio.ini` hinzu:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Dies setzt ein Compiler-Flag, das beim Kompilieren des Arduino IoT Hub-Codes benötigt wird.

1. Öffnen Sie die Header-Datei `config.h`. Entfernen Sie alle MQTT-Einstellungen und fügen Sie die folgende Konstante für den Geräte-Verbindungsstring hinzu:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Ersetzen Sie `<connection string>` durch den Verbindungsstring für Ihr Gerät, den Sie zuvor kopiert haben.

1. Die Verbindung zum IoT Hub verwendet ein zeitbasiertes Token. Das bedeutet, dass das IoT-Gerät die aktuelle Zeit kennen muss. Im Gegensatz zu Betriebssystemen wie Windows, macOS oder Linux synchronisieren Mikrocontroller die aktuelle Zeit nicht automatisch über das Internet. Daher müssen Sie Code hinzufügen, um die aktuelle Zeit von einem [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)-Server abzurufen. Sobald die Zeit abgerufen wurde, kann sie in einer Echtzeituhr im Wio Terminal gespeichert werden, sodass die korrekte Zeit zu einem späteren Zeitpunkt angefordert werden kann, vorausgesetzt, das Gerät verliert nicht die Stromversorgung. Fügen Sie eine neue Datei namens `ntp.h` mit folgendem Code hinzu:

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

    Die Details dieses Codes liegen außerhalb des Umfangs dieser Lektion. Er definiert eine Funktion namens `initTime`, die die aktuelle Zeit von einem NTP-Server abruft und verwendet, um die Uhr im Wio Terminal einzustellen.

1. Öffnen Sie die Datei `main.cpp` und entfernen Sie den gesamten MQTT-Code, einschließlich der Header-Datei `PubSubClient.h`, der Deklaration der `PubSubClient`-Variable, der Methoden `reconnectMQTTClient` und `createMQTTClient` sowie aller Aufrufe dieser Variablen und Methoden. Diese Datei sollte nur Code enthalten, um eine Verbindung zu WiFi herzustellen, die Bodenfeuchtigkeit abzurufen und ein JSON-Dokument damit zu erstellen.

1. Fügen Sie die folgenden `#include`-Direktiven oben in der Datei `main.cpp` hinzu, um Header-Dateien für die IoT Hub-Bibliotheken und zum Einstellen der Zeit einzubinden:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Fügen Sie am Ende der Funktion `setup` den folgenden Aufruf hinzu, um die aktuelle Zeit einzustellen:

    ```cpp
    initTime();
    ```

1. Fügen Sie die folgende Variablendeklaration oben in der Datei hinzu, direkt unter den Include-Direktiven:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Dies deklariert ein `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, einen Handle für eine Verbindung zum IoT Hub.

1. Fügen Sie darunter den folgenden Code hinzu:

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

    Dies deklariert eine Callback-Funktion, die aufgerufen wird, wenn sich der Verbindungsstatus zum IoT Hub ändert, z. B. beim Verbinden oder Trennen. Der Status wird an den seriellen Port gesendet.

1. Fügen Sie darunter eine Funktion hinzu, um eine Verbindung zum IoT Hub herzustellen:

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

    Dieser Code initialisiert den IoT Hub-Bibliothekscode und erstellt dann eine Verbindung mithilfe des Verbindungsstrings in der Header-Datei `config.h`. Diese Verbindung basiert auf MQTT. Wenn die Verbindung fehlschlägt, wird dies an den seriellen Port gesendet - wenn Sie dies in der Ausgabe sehen, überprüfen Sie den Verbindungsstring. Schließlich wird der Callback für den Verbindungsstatus eingerichtet.

1. Rufen Sie diese Funktion in der Funktion `setup` unterhalb des Aufrufs von `initTime` auf:

    ```cpp
    connectIoTHub();
    ```

1. Genau wie beim MQTT-Client läuft dieser Code in einem einzelnen Thread und benötigt Zeit, um Nachrichten zu verarbeiten, die vom Hub gesendet und an den Hub gesendet werden. Fügen Sie Folgendes oben in der Funktion `loop` hinzu, um dies zu tun:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Bauen und laden Sie diesen Code hoch. Sie sehen die Verbindung im seriellen Monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    In der Ausgabe können Sie sehen, wie die NTP-Zeit abgerufen wird, gefolgt von der Verbindung des Geräte-Clients. Es kann einige Sekunden dauern, bis die Verbindung hergestellt ist, sodass Sie möglicherweise die Bodenfeuchtigkeit in der Ausgabe sehen, während das Gerät sich verbindet.

    > 💁 Sie können die UNIX-Zeit des NTP in eine lesbarere Version umwandeln, indem Sie eine Website wie [unixtimestamp.com](https://www.unixtimestamp.com) verwenden.

## Telemetrie senden

Jetzt, da Ihr Gerät verbunden ist, können Sie Telemetrie an den IoT Hub senden, anstatt an den MQTT-Broker.

### Aufgabe - Telemetrie senden

1. Fügen Sie die folgende Funktion oberhalb der Funktion `setup` hinzu:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Dieser Code erstellt eine IoT Hub-Nachricht aus einem als Parameter übergebenen String, sendet sie an den Hub und bereinigt anschließend das Nachrichtenobjekt.

1. Rufen Sie diesen Code in der Funktion `loop` direkt nach der Zeile auf, in der die Telemetrie an den seriellen Port gesendet wird:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Befehle verarbeiten

Ihr Gerät muss einen Befehl vom Servercode verarbeiten, um das Relais zu steuern. Dies wird als direkte Methodenanforderung gesendet.

## Aufgabe - eine direkte Methodenanforderung verarbeiten

1. Fügen Sie den folgenden Code vor der Funktion `connectIoTHub` hinzu:

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

    Dieser Code definiert eine Callback-Methode, die von der IoT Hub-Bibliothek aufgerufen werden kann, wenn sie eine direkte Methodenanforderung erhält. Die angeforderte Methode wird im Parameter `method_name` übergeben. Diese Funktion gibt die aufgerufene Methode an den seriellen Port aus und schaltet das Relais je nach Methodenname ein oder aus.

    > 💁 Dies könnte auch in einer einzigen direkten Methodenanforderung implementiert werden, indem der gewünschte Zustand des Relais in einer Nutzlast übergeben wird, die mit der Methodenanforderung übergeben und im Parameter `payload` verfügbar ist.

1. Fügen Sie den folgenden Code am Ende der Funktion `directMethodCallback` hinzu:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Direkte Methodenanforderungen benötigen eine Antwort, und die Antwort besteht aus zwei Teilen - einer Antwort als Text und einem Rückgabecode. Dieser Code erstellt ein Ergebnis als folgendes JSON-Dokument:

    ```JSON
    {
        "Result": ""
    }
    ```

    Dieses wird dann in den Parameter `response` kopiert, und die Größe dieser Antwort wird im Parameter `response_size` festgelegt. Dieser Code gibt dann `IOTHUB_CLIENT_OK` zurück, um zu zeigen, dass die Methode korrekt verarbeitet wurde.

1. Verkabeln Sie den Callback, indem Sie Folgendes am Ende der Funktion `connectIoTHub` hinzufügen:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Die Funktion `loop` ruft die Funktion `IoTHubDeviceClient_LL_DoWork` auf, um Ereignisse zu verarbeiten, die vom IoT Hub gesendet werden. Dies wird aufgrund des `delay` nur alle 10 Sekunden aufgerufen, was bedeutet, dass direkte Methoden nur alle 10 Sekunden verarbeitet werden. Um dies effizienter zu gestalten, kann die Verzögerung von 10 Sekunden in viele kürzere Verzögerungen implementiert werden, wobei `IoTHubDeviceClient_LL_DoWork` jedes Mal aufgerufen wird. Fügen Sie dazu den folgenden Code oberhalb der Funktion `loop` hinzu:

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

    Dieser Code wird wiederholt durchlaufen, ruft `IoTHubDeviceClient_LL_DoWork` auf und verzögert jedes Mal um 100 ms. Dies wird so oft wie nötig durchgeführt, um die im Parameter `delay_time` angegebene Verzögerungszeit zu erreichen. Das bedeutet, dass das Gerät höchstens 100 ms wartet, um direkte Methodenanforderungen zu verarbeiten.

1. Entfernen Sie in der Funktion `loop` den Aufruf von `IoTHubDeviceClient_LL_DoWork` und ersetzen Sie den Aufruf `delay(10000)` durch Folgendes, um diese neue Funktion aufzurufen:

    ```cpp
    work_delay(10000);
    ```

> 💁 Sie finden diesen Code im Ordner [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Ihr Bodenfeuchtigkeitssensor-Programm ist mit Ihrem IoT Hub verbunden!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, weisen wir darauf hin, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.