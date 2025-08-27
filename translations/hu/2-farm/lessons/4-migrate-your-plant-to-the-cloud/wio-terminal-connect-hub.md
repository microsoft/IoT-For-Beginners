<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T23:13:59+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "hu"
}
-->
# Csatlakoztassa IoT-eszközét a felhőhöz - Wio Terminal

Ebben a leckében csatlakoztatni fogja Wio Terminal eszközét az IoT Hubhoz, hogy telemetriát küldjön és parancsokat fogadjon.

## Csatlakoztassa eszközét az IoT Hubhoz

A következő lépés az eszköz csatlakoztatása az IoT Hubhoz.

### Feladat - csatlakozás az IoT Hubhoz

1. Nyissa meg a `soil-moisture-sensor` projektet a VS Code-ban.

1. Nyissa meg a `platformio.ini` fájlt. Távolítsa el a `knolleary/PubSubClient` könyvtárfüggőséget. Ezt a nyilvános MQTT brokerhez való csatlakozáshoz használták, de az IoT Hubhoz való csatlakozáshoz nincs rá szükség.

1. Adja hozzá a következő könyvtárfüggőségeket:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    A `Seeed Arduino RTC` könyvtár kódot biztosít a Wio Terminal valós idejű órájának kezeléséhez, amely az idő nyomon követésére szolgál. A többi könyvtár lehetővé teszi az IoT eszköz számára, hogy csatlakozzon az IoT Hubhoz.

1. Adja hozzá a következő sort a `platformio.ini` fájl aljára:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Ez egy fordítóflaget állít be, amely szükséges az Arduino IoT Hub kód fordításakor.

1. Nyissa meg a `config.h` fejlécfájlt. Távolítsa el az összes MQTT beállítást, és adja hozzá a következő állandót az eszközkapcsolati karakterlánchoz:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Cserélje ki a `<connection string>` helyére az eszközkapcsolati karakterláncot, amelyet korábban másolt.

1. Az IoT Hubhoz való csatlakozás időalapú tokent használ. Ez azt jelenti, hogy az IoT eszköznek ismernie kell az aktuális időt. Az olyan operációs rendszerekkel ellentétben, mint a Windows, macOS vagy Linux, a mikrokontrollerek nem szinkronizálják automatikusan az aktuális időt az interneten keresztül. Ezért kódot kell hozzáadnia, hogy az aktuális időt egy [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) szerverről lekérje. Miután az időt lekérte, azt el lehet tárolni a Wio Terminal valós idejű órájában, így később is lekérhető a helyes idő, feltéve, hogy az eszköz nem veszít áramot. Hozzon létre egy új fájlt `ntp.h` néven a következő kóddal:

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

    Ennek a kódnak a részletei nem tartoznak a lecke hatókörébe. Ez egy `initTime` nevű függvényt definiál, amely az aktuális időt egy NTP szerverről lekéri, és beállítja a Wio Terminal óráján.

1. Nyissa meg a `main.cpp` fájlt, és távolítsa el az összes MQTT kódot, beleértve a `PubSubClient.h` fejlécfájlt, a `PubSubClient` változó deklarációját, a `reconnectMQTTClient` és `createMQTTClient` metódusokat, valamint az ezekre a változókra és metódusokra történő hivatkozásokat. Ez a fájl csak a WiFi-hez való csatlakozáshoz, a talajnedvesség lekéréséhez és egy JSON dokumentum létrehozásához szükséges kódot tartalmazza.

1. Adja hozzá a következő `#include` direktívákat a `main.cpp` fájl tetejére az IoT Hub könyvtárak és az idő beállításához szükséges fejlécfájlok beillesztéséhez:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Adja hozzá a következő hívást a `setup` függvény végéhez az aktuális idő beállításához:

    ```cpp
    initTime();
    ```

1. Adja hozzá a következő változódeklarációt a fájl tetejére, közvetlenül az include direktívák alá:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Ez egy `IOTHUB_DEVICE_CLIENT_LL_HANDLE`-t deklarál, amely az IoT Hubhoz való kapcsolat kezelésére szolgál.

1. Ezután adja hozzá a következő kódot:

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

    Ez egy visszahívási függvényt deklarál, amelyet akkor hívnak meg, amikor az IoT Hubhoz való kapcsolat állapota megváltozik, például csatlakozáskor vagy bontáskor. Az állapotot a soros porton keresztül küldi el.

1. Ezután adjon hozzá egy függvényt az IoT Hubhoz való csatlakozáshoz:

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

    Ez a kód inicializálja az IoT Hub könyvtár kódját, majd létrehoz egy kapcsolatot a `config.h` fejlécfájlban található kapcsolati karakterlánc segítségével. Ez a kapcsolat MQTT alapú. Ha a kapcsolat sikertelen, ezt a soros porton keresztül jelzi - ha ezt látja a kimenetben, ellenőrizze a kapcsolati karakterláncot. Végül beállítja a kapcsolat állapotának visszahívását.

1. Hívja meg ezt a függvényt a `setup` függvényben az `initTime` hívása után:

    ```cpp
    connectIoTHub();
    ```

1. Az MQTT klienshez hasonlóan ez a kód is egyetlen szálon fut, ezért időre van szüksége az üzenetek feldolgozásához, amelyeket a hub küld és fogad. Adja hozzá a következőt a `loop` függvény tetejéhez ennek érdekében:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Fordítsa le és töltse fel ezt a kódot. A soros monitoron látni fogja a kapcsolatot:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    A kimenetben láthatja az NTP idő lekérését, majd az eszköz kliens csatlakozását. A csatlakozás néhány másodpercet igénybe vehet, így előfordulhat, hogy a talajnedvességet látja a kimenetben, miközben az eszköz csatlakozik.

    > 💁 Az NTP UNIX idejét olvashatóbb formátumra konvertálhatja egy olyan weboldal segítségével, mint például [unixtimestamp.com](https://www.unixtimestamp.com).

## Telemetria küldése

Most, hogy az eszköz csatlakozott, telemetriát küldhet az IoT Hubhoz az MQTT broker helyett.

### Feladat - telemetria küldése

1. Adja hozzá a következő függvényt a `setup` függvény fölé:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Ez a kód létrehoz egy IoT Hub üzenetet egy paraméterként átadott szövegből, elküldi a hubnak, majd felszabadítja az üzenet objektumot.

1. Hívja meg ezt a kódot a `loop` függvényben, közvetlenül azután, hogy a telemetria a soros portra kerül:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Parancsok kezelése

Az eszköznek képesnek kell lennie egy szerver kódból érkező parancs kezelésére a relé vezérléséhez. Ezt közvetlen metóduskérésként küldik.

### Feladat - közvetlen metóduskérés kezelése

1. Adja hozzá a következő kódot a `connectIoTHub` függvény elé:

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

    Ez a kód egy visszahívási metódust definiál, amelyet az IoT Hub könyvtár hívhat meg, amikor közvetlen metóduskérést kap. A kért metódust a `method_name` paraméter tartalmazza. Ez a függvény kiírja a hívott metódust a soros portra, majd a metódus nevének megfelelően be- vagy kikapcsolja a relét.

    > 💁 Ezt egyetlen közvetlen metóduskérésként is meg lehetne valósítani, amely a relé kívánt állapotát egy olyan payloadban adja át, amely a metóduskéréssel együtt küldhető, és a `payload` paraméterből elérhető.

1. Adja hozzá a következő kódot a `directMethodCallback` függvény végéhez:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    A közvetlen metóduskérésekhez válasz szükséges, amely két részből áll - egy szöveges válaszból és egy visszatérési kódból. Ez a kód a következő JSON dokumentumként hoz létre egy eredményt:

    ```JSON
    {
        "Result": ""
    }
    ```

    Ezután ezt bemásolja a `response` paraméterbe, és beállítja a válasz méretét a `response_size` paraméterben. Ez a kód végül `IOTHUB_CLIENT_OK` értéket ad vissza, jelezve, hogy a metódust helyesen kezelték.

1. Kösse össze a visszahívást a következő kód hozzáadásával a `connectIoTHub` függvény végéhez:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. A `loop` függvény az `IoTHubDeviceClient_LL_DoWork` függvényt hívja az IoT Hub által küldött események feldolgozására. Ez azonban csak 10 másodpercenként történik a `delay` miatt, ami azt jelenti, hogy a közvetlen metódusok csak 10 másodpercenként kerülnek feldolgozásra. Ennek hatékonyabbá tétele érdekében a 10 másodperces késleltetést több rövidebb késleltetésként lehet megvalósítani, minden alkalommal meghívva az `IoTHubDeviceClient_LL_DoWork` függvényt. Ehhez adja hozzá a következő kódot a `loop` függvény elé:

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

    Ez a kód ismételten hívja az `IoTHubDeviceClient_LL_DoWork` függvényt, és minden alkalommal 100 ms-ot késleltet. Ezt annyiszor ismétli, ahányszor szükséges a `delay_time` paraméterben megadott idő késleltetéséhez. Ez azt jelenti, hogy az eszköz legfeljebb 100 ms-ot vár a közvetlen metóduskérések feldolgozására.

1. A `loop` függvényben távolítsa el az `IoTHubDeviceClient_LL_DoWork` hívását, és cserélje le a `delay(10000)` hívást a következőre, hogy az új függvényt hívja meg:

    ```cpp
    work_delay(10000);
    ```

> 💁 Ezt a kódot megtalálja a [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) mappában.

😀 A talajnedvesség-érzékelő programja most már csatlakozik az IoT Hubhoz!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.