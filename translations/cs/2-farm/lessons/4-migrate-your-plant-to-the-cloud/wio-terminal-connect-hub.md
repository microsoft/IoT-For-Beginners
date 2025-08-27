<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T23:14:34+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "cs"
}
-->
# Připojte své IoT zařízení ke cloudu - Wio Terminal

V této části lekce připojíte svůj Wio Terminal k IoT Hubu, abyste mohli odesílat telemetrii a přijímat příkazy.

## Připojte své zařízení k IoT Hubu

Dalším krokem je připojení vašeho zařízení k IoT Hubu.

### Úkol - připojení k IoT Hubu

1. Otevřete projekt `soil-moisture-sensor` ve VS Code.

1. Otevřete soubor `platformio.ini`. Odstraňte závislost na knihovně `knolleary/PubSubClient`. Tato knihovna byla použita pro připojení k veřejnému MQTT brokeru, ale není potřeba pro připojení k IoT Hubu.

1. Přidejte následující závislosti knihoven:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Knihovna `Seeed Arduino RTC` poskytuje kód pro interakci s reálným časem na Wio Terminalu, který se používá ke sledování času. Zbývající knihovny umožňují vašemu IoT zařízení připojit se k IoT Hubu.

1. Přidejte následující na konec souboru `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Toto nastavuje příznak kompilátoru, který je potřeba při kompilaci kódu Arduino IoT Hub.

1. Otevřete hlavičkový soubor `config.h`. Odstraňte všechna nastavení MQTT a přidejte následující konstantu pro připojovací řetězec zařízení:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Nahraďte `<connection string>` připojovacím řetězcem pro vaše zařízení, který jste zkopírovali dříve.

1. Připojení k IoT Hubu používá token založený na čase. To znamená, že IoT zařízení musí znát aktuální čas. Na rozdíl od operačních systémů jako Windows, macOS nebo Linux, mikrokontroléry automaticky nesynchronizují aktuální čas přes internet. To znamená, že musíte přidat kód pro získání aktuálního času ze serveru [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Jakmile je čas získán, může být uložen v reálném časovém hodinách na Wio Terminalu, což umožňuje požadovat správný čas později, za předpokladu, že zařízení neztratí napájení. Přidejte nový soubor nazvaný `ntp.h` s následujícím kódem:

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

    Podrobnosti tohoto kódu jsou mimo rozsah této lekce. Definuje funkci nazvanou `initTime`, která získává aktuální čas ze serveru NTP a používá jej k nastavení hodin na Wio Terminalu.

1. Otevřete soubor `main.cpp` a odstraňte veškerý kód MQTT, včetně hlavičkového souboru `PubSubClient.h`, deklarace proměnné `PubSubClient`, metod `reconnectMQTTClient` a `createMQTTClient` a všech volání těchto proměnných a metod. Tento soubor by měl obsahovat pouze kód pro připojení k WiFi, získání vlhkosti půdy a vytvoření JSON dokumentu s těmito daty.

1. Přidejte následující direktivy `#include` na začátek souboru `main.cpp`, abyste zahrnuli hlavičkové soubory pro knihovny IoT Hubu a pro nastavení času:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Přidejte následující volání na konec funkce `setup`, abyste nastavili aktuální čas:

    ```cpp
    initTime();
    ```

1. Přidejte následující deklaraci proměnné na začátek souboru, těsně pod direktivy `#include`:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Tím se deklaruje `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, což je handle pro připojení k IoT Hubu.

1. Pod tímto přidejte následující kód:

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

    Tím se deklaruje callback funkce, která bude volána, když se změní stav připojení k IoT Hubu, například při připojení nebo odpojení. Stav je odeslán na sériový port.

1. Pod tímto přidejte funkci pro připojení k IoT Hubu:

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

    Tento kód inicializuje knihovnu IoT Hubu, poté vytvoří připojení pomocí připojovacího řetězce v hlavičkovém souboru `config.h`. Toto připojení je založeno na MQTT. Pokud připojení selže, je to odesláno na sériový port - pokud to vidíte ve výstupu, zkontrolujte připojovací řetězec. Nakonec je nastavena callback funkce pro stav připojení.

1. Zavolejte tuto funkci ve funkci `setup` pod voláním `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Stejně jako u MQTT klienta, tento kód běží na jednom vlákně, takže potřebuje čas na zpracování zpráv odesílaných hubem a zpráv odesílaných do hubu. Přidejte následující na začátek funkce `loop`, abyste to umožnili:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Sestavte a nahrajte tento kód. Připojení uvidíte v sériovém monitoru:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Ve výstupu můžete vidět, jak se načítá čas z NTP, následovaný připojením klienta zařízení. Připojení může trvat několik sekund, takže můžete vidět vlhkost půdy ve výstupu, zatímco se zařízení připojuje.

    > 💁 UNIX čas z NTP můžete převést na čitelnější verzi pomocí webové stránky jako [unixtimestamp.com](https://www.unixtimestamp.com)

## Odesílání telemetrie

Nyní, když je vaše zařízení připojeno, můžete odesílat telemetrii do IoT Hubu místo MQTT brokeru.

### Úkol - odesílání telemetrie

1. Přidejte následující funkci nad funkci `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Tento kód vytvoří zprávu IoT Hubu ze řetězce předaného jako parametr, odešle ji do hubu a poté vyčistí objekt zprávy.

1. Zavolejte tento kód ve funkci `loop`, těsně za řádkem, kde je telemetrie odesílána na sériový port:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Zpracování příkazů

Vaše zařízení musí zpracovat příkaz ze serverového kódu pro ovládání relé. Tento příkaz je odeslán jako požadavek na přímou metodu.

## Úkol - zpracování požadavku na přímou metodu

1. Přidejte následující kód před funkci `connectIoTHub`:

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

    Tento kód definuje callback metodu, kterou může knihovna IoT Hubu volat, když obdrží požadavek na přímou metodu. Metoda, která je požadována, je odeslána v parametru `method_name`. Tato funkce vypíše volanou metodu na sériový port a poté zapne nebo vypne relé v závislosti na názvu metody.

    > 💁 Toto by také mohlo být implementováno v jedné přímé metodě, která by předávala požadovaný stav relé v payloadu, který může být předán s požadavkem na metodu a dostupný z parametru `payload`.

1. Přidejte následující kód na konec funkce `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Požadavky na přímé metody potřebují odpověď, která je ve dvou částech - odpověď jako text a návratový kód. Tento kód vytvoří výsledek jako následující JSON dokument:

    ```JSON
    {
        "Result": ""
    }
    ```

    Tento dokument je poté zkopírován do parametru `response` a velikost této odpovědi je nastavena v parametru `response_size`. Tento kód poté vrátí `IOTHUB_CLIENT_OK`, aby ukázal, že metoda byla správně zpracována.

1. Připojte callback přidáním následujícího na konec funkce `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funkce `loop` bude volat funkci `IoTHubDeviceClient_LL_DoWork`, aby zpracovala události odesílané IoT Hubem. Tato funkce je volána pouze každých 10 sekund kvůli `delay`, což znamená, že přímé metody jsou zpracovány pouze každých 10 sekund. Aby to bylo efektivnější, 10sekundové zpoždění může být implementováno jako mnoho kratších zpoždění, přičemž se funkce `IoTHubDeviceClient_LL_DoWork` volá pokaždé. Přidejte následující kód nad funkci `loop`:

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

    Tento kód bude opakovaně volat funkci `IoTHubDeviceClient_LL_DoWork` a zpožďovat o 100 ms pokaždé. Bude to dělat tolikrát, kolik je potřeba, aby zpoždění trvalo dobu uvedenou v parametru `delay_time`. To znamená, že zařízení čeká maximálně 100 ms na zpracování požadavků na přímé metody.

1. Ve funkci `loop` odstraňte volání `IoTHubDeviceClient_LL_DoWork` a nahraďte volání `delay(10000)` následujícím, aby se volala nová funkce:

    ```cpp
    work_delay(10000);
    ```

> 💁 Tento kód najdete ve složce [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Váš program pro senzor vlhkosti půdy je připojen k vašemu IoT Hubu!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.