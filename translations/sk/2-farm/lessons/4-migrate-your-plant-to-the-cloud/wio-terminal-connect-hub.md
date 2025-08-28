<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T11:25:32+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "sk"
}
-->
# Pripojte svoje IoT zariadenie do cloudu - Wio Terminal

V tejto časti lekcie pripojíte svoj Wio Terminal k IoT Hubu, aby ste mohli odosielať telemetriu a prijímať príkazy.

## Pripojenie zariadenia k IoT Hubu

Ďalším krokom je pripojenie vášho zariadenia k IoT Hubu.

### Úloha - pripojenie k IoT Hubu

1. Otvorte projekt `soil-moisture-sensor` vo VS Code.

1. Otvorte súbor `platformio.ini`. Odstráňte závislosť knižnice `knolleary/PubSubClient`. Táto knižnica sa používala na pripojenie k verejnému MQTT brokeru, ale na pripojenie k IoT Hubu nie je potrebná.

1. Pridajte nasledujúce závislosti knižníc:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Knižnica `Seeed Arduino RTC` poskytuje kód na interakciu s reálnym časom v zariadení Wio Terminal, ktorý sa používa na sledovanie času. Zvyšné knižnice umožňujú vášmu IoT zariadeniu pripojiť sa k IoT Hubu.

1. Pridajte nasledujúci riadok na koniec súboru `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Tento riadok nastavuje kompilátorovú vlajku, ktorá je potrebná pri kompilácii kódu pre Arduino IoT Hub.

1. Otvorte hlavičkový súbor `config.h`. Odstráňte všetky nastavenia MQTT a pridajte nasledujúcu konštantu pre reťazec pripojenia zariadenia:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Nahraďte `<connection string>` reťazcom pripojenia vášho zariadenia, ktorý ste skopírovali skôr.

1. Pripojenie k IoT Hubu používa token založený na čase. To znamená, že IoT zariadenie musí poznať aktuálny čas. Na rozdiel od operačných systémov ako Windows, macOS alebo Linux, mikrokontroléry automaticky nesynchronizujú aktuálny čas cez internet. Preto musíte pridať kód na získanie aktuálneho času zo servera [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Po získaní času ho môžete uložiť do reálneho času v zariadení Wio Terminal, čo umožní neskôr získať správny čas, pokiaľ zariadenie nestratí napájanie. Pridajte nový súbor s názvom `ntp.h` s nasledujúcim kódom:

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

    Podrobnosti tohto kódu sú mimo rozsahu tejto lekcie. Definuje funkciu s názvom `initTime`, ktorá získava aktuálny čas zo servera NTP a používa ho na nastavenie hodín v zariadení Wio Terminal.

1. Otvorte súbor `main.cpp` a odstráňte všetok kód MQTT, vrátane hlavičkového súboru `PubSubClient.h`, deklarácie premennej `PubSubClient`, metód `reconnectMQTTClient` a `createMQTTClient` a všetkých volaní týchto premenných a metód. Tento súbor by mal obsahovať iba kód na pripojenie k WiFi, získanie vlhkosti pôdy a vytvorenie JSON dokumentu s týmito údajmi.

1. Pridajte nasledujúce direktívy `#include` na začiatok súboru `main.cpp`, aby ste zahrnuli hlavičkové súbory pre knižnice IoT Hub a nastavenie času:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Pridajte nasledujúci riadok na koniec funkcie `setup`, aby ste nastavili aktuálny čas:

    ```cpp
    initTime();
    ```

1. Pridajte nasledujúcu deklaráciu premennej na začiatok súboru, hneď pod direktívy `include`:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Táto deklarácia vytvára `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, čo je ukazovateľ na pripojenie k IoT Hubu.

1. Pod týmto riadkom pridajte nasledujúci kód:

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

    Tento kód deklaruje spätnú volaciu funkciu, ktorá sa zavolá, keď sa zmení stav pripojenia k IoT Hubu, napríklad pri pripojení alebo odpojení. Stav sa odošle na sériový port.

1. Pod týmto riadkom pridajte funkciu na pripojenie k IoT Hubu:

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

    Tento kód inicializuje knižnicu IoT Hub, potom vytvorí pripojenie pomocou reťazca pripojenia v hlavičkovom súbore `config.h`. Toto pripojenie je založené na MQTT. Ak pripojenie zlyhá, táto informácia sa odošle na sériový port - ak to vidíte vo výstupe, skontrolujte reťazec pripojenia. Nakoniec sa nastaví spätná volacia funkcia pre stav pripojenia.

1. Zavolajte túto funkciu vo funkcii `setup` pod volaním `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Rovnako ako pri MQTT klientovi, tento kód beží na jednom vlákne, takže potrebuje čas na spracovanie správ odosielaných hubom a do hubu. Pridajte nasledujúci riadok na začiatok funkcie `loop`, aby ste to umožnili:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Skontrolujte a nahrajte tento kód. Pripojenie uvidíte v sériovom monitore:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Vo výstupe môžete vidieť, ako sa načítava čas NTP, po ktorom sa zariadenie pripája. Pripojenie môže trvať niekoľko sekúnd, takže môžete vidieť vlhkosť pôdy vo výstupe, zatiaľ čo sa zariadenie pripája.

    > 💁 UNIX čas z NTP môžete previesť na čitateľnejší formát pomocou webovej stránky ako [unixtimestamp.com](https://www.unixtimestamp.com)

## Odosielanie telemetrie

Teraz, keď je vaše zariadenie pripojené, môžete odosielať telemetriu do IoT Hubu namiesto MQTT brokeru.

### Úloha - odosielanie telemetrie

1. Pridajte nasledujúcu funkciu nad funkciu `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Tento kód vytvára správu IoT Hubu z reťazca odovzdaného ako parameter, odošle ju do hubu a potom vyčistí objekt správy.

1. Zavolajte tento kód vo funkcii `loop`, hneď po riadku, kde sa telemetria odosiela na sériový port:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Spracovanie príkazov

Vaše zariadenie musí spracovať príkaz zo serverového kódu na ovládanie relé. Tento príkaz sa odosiela ako požiadavka na priamu metódu.

## Úloha - spracovanie požiadavky na priamu metódu

1. Pridajte nasledujúci kód pred funkciu `connectIoTHub`:

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

    Tento kód definuje spätnú volaciu metódu, ktorú môže knižnica IoT Hub zavolať, keď prijme požiadavku na priamu metódu. Metóda, ktorá sa požaduje, sa odovzdáva v parametri `method_name`. Táto funkcia vypíše názov metódy na sériový port a potom zapne alebo vypne relé v závislosti od názvu metódy.

    > 💁 Toto by sa dalo implementovať aj ako jedna požiadavka na priamu metódu, pričom požadovaný stav relé by sa odovzdal v údajoch, ktoré môžu byť odovzdané s požiadavkou na metódu a dostupné z parametra `payload`.

1. Pridajte nasledujúci kód na koniec funkcie `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Požiadavky na priamu metódu potrebujú odpoveď, ktorá pozostáva z dvoch častí - odpovede ako text a návratového kódu. Tento kód vytvorí výsledok vo forme nasledujúceho JSON dokumentu:

    ```JSON
    {
        "Result": ""
    }
    ```

    Tento dokument sa potom skopíruje do parametra `response` a veľkosť tejto odpovede sa nastaví v parametri `response_size`. Tento kód potom vráti `IOTHUB_CLIENT_OK`, aby ukázal, že metóda bola správne spracovaná.

1. Prepojte spätnú volaciu funkciu pridaním nasledujúceho riadku na koniec funkcie `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funkcia `loop` zavolá funkciu `IoTHubDeviceClient_LL_DoWork` na spracovanie udalostí odoslaných IoT Hubom. Táto funkcia sa však volá iba každých 10 sekúnd kvôli volaniu `delay`, čo znamená, že priame metódy sa spracovávajú iba každých 10 sekúnd. Aby to bolo efektívnejšie, 10-sekundové oneskorenie môže byť implementované ako viacero kratších oneskorení, pričom funkcia `IoTHubDeviceClient_LL_DoWork` sa volá pri každom z nich. Na to pridajte nasledujúci kód nad funkciu `loop`:

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

    Tento kód bude opakovane volať funkciu `IoTHubDeviceClient_LL_DoWork` a oneskorovať o 100 ms pri každom volaní. Bude to robiť toľkokrát, koľkokrát je potrebné na oneskorenie o čas uvedený v parametri `delay_time`. To znamená, že zariadenie čaká maximálne 100 ms na spracovanie požiadaviek na priamu metódu.

1. Vo funkcii `loop` odstráňte volanie `IoTHubDeviceClient_LL_DoWork` a nahraďte volanie `delay(10000)` nasledujúcim kódom, ktorý zavolá túto novú funkciu:

    ```cpp
    work_delay(10000);
    ```

> 💁 Tento kód nájdete v priečinku [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Váš program na meranie vlhkosti pôdy je pripojený k vášmu IoT Hubu!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.