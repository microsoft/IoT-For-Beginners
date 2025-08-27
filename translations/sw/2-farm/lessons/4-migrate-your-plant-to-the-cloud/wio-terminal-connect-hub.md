<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T23:13:28+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "sw"
}
-->
# Unganisha kifaa chako cha IoT na wingu - Wio Terminal

Katika sehemu hii ya somo, utaunganisha Wio Terminal yako na IoT Hub yako, ili kutuma data za telemetry na kupokea amri.

## Unganisha kifaa chako na IoT Hub

Hatua inayofuata ni kuunganisha kifaa chako na IoT Hub.

### Kazi - unganisha na IoT Hub

1. Fungua mradi wa `soil-moisture-sensor` kwenye VS Code.

1. Fungua faili ya `platformio.ini`. Ondoa utegemezi wa maktaba ya `knolleary/PubSubClient`. Hii ilitumika kuunganishwa na broker ya umma ya MQTT, na haihitajiki kuunganishwa na IoT Hub.

1. Ongeza utegemezi wa maktaba zifuatazo:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Maktaba ya `Seeed Arduino RTC` inatoa msimbo wa kuingiliana na saa ya wakati halisi kwenye Wio Terminal, inayotumika kufuatilia muda. Maktaba zilizobaki zinakuruhusu kifaa chako cha IoT kuunganishwa na IoT Hub.

1. Ongeza yafuatayo chini ya faili ya `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Hii inaweka bendera ya mkusanyaji inayohitajika wakati wa kukusanya msimbo wa Arduino IoT Hub.

1. Fungua faili ya kichwa `config.h`. Ondoa mipangilio yote ya MQTT na ongeza thamani ya kudumu kwa mnyororo wa muunganisho wa kifaa:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Badilisha `<connection string>` na mnyororo wa muunganisho wa kifaa chako uliyonakili awali.

1. Muunganisho na IoT Hub hutumia tokeni inayotegemea muda. Hii inamaanisha kifaa cha IoT kinahitaji kujua muda wa sasa. Tofauti na mifumo ya uendeshaji kama Windows, macOS au Linux, microcontrollers hazisawazishi muda wa sasa moja kwa moja kupitia mtandao. Hii inamaanisha unahitaji kuongeza msimbo wa kupata muda wa sasa kutoka kwa [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server. Baada ya muda kupatikana, unaweza kuhifadhiwa kwenye saa ya wakati halisi kwenye Wio Terminal, kuruhusu muda sahihi kuombwa baadaye, mradi kifaa hakipotezi nguvu. Ongeza faili mpya inayoitwa `ntp.h` na msimbo ufuatao:

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

    Maelezo ya msimbo huu yako nje ya wigo wa somo hili. Inafafanua kazi inayoitwa `initTime` inayopata muda wa sasa kutoka kwa NTP server na kuutumia kuweka saa kwenye Wio Terminal.

1. Fungua faili ya `main.cpp` na ondoa msimbo wote wa MQTT, ikijumuisha faili ya kichwa `PubSubClient.h`, tangazo la kigezo cha `PubSubClient`, mbinu za `reconnectMQTTClient` na `createMQTTClient`, na miito yoyote kwa vigezo na mbinu hizi. Faili hii inapaswa kuwa na msimbo wa kuunganishwa na WiFi, kupata unyevu wa udongo na kuunda hati ya JSON nayo pekee.

1. Ongeza maagizo yafuatayo ya `#include` juu ya faili ya `main.cpp` ili kujumuisha faili za kichwa kwa maktaba za IoT Hub, na kwa kuweka muda:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Ongeza mwito ufuatao mwishoni mwa kazi ya `setup` ili kuweka muda wa sasa:

    ```cpp
    initTime();
    ```

1. Ongeza tangazo la kigezo kifuatacho juu ya faili, chini tu ya maagizo ya kujumuisha:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Hii inatangaza `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, kigezo cha muunganisho na IoT Hub.

1. Chini ya hii, ongeza msimbo ufuatao:

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

    Hii inatangaza kazi ya callback ambayo itaitwa wakati muunganisho na IoT Hub unabadilisha hali, kama kuunganishwa au kukatwa. Hali inatumwa kwenye bandari ya serial.

1. Chini ya hii, ongeza kazi ya kuunganishwa na IoT Hub:

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

    Msimbo huu unaanzisha msimbo wa maktaba ya IoT Hub, kisha unaunda muunganisho kwa kutumia mnyororo wa muunganisho kwenye faili ya kichwa ya `config.h`. Muunganisho huu unategemea MQTT. Ikiwa muunganisho unashindwa, hii inatumwa kwenye bandari ya serial - ikiwa utaona hili kwenye matokeo, angalia mnyororo wa muunganisho. Hatimaye callback ya hali ya muunganisho inasanidiwa.

1. Ita kazi hii kwenye kazi ya `setup` chini ya mwito wa `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Kama ilivyo kwa mteja wa MQTT, msimbo huu unakimbia kwenye thread moja hivyo unahitaji muda wa kushughulikia ujumbe unaotumwa na hub, na unaotumwa kwa hub. Ongeza yafuatayo juu ya kazi ya `loop` ili kufanya hivi:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Jenga na pakia msimbo huu. Utaona muunganisho kwenye monitor ya serial:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Katika matokeo unaweza kuona muda wa NTP ukipatikana, ukifuatiwa na mteja wa kifaa kuunganishwa. Inaweza kuchukua sekunde chache kuunganishwa, hivyo unaweza kuona unyevu wa udongo kwenye matokeo wakati kifaa kinaunganishwa.

    > 💁 Unaweza kubadilisha muda wa UNIX wa NTP kuwa toleo linalosomeka zaidi kwa kutumia tovuti kama [unixtimestamp.com](https://www.unixtimestamp.com)

## Tuma telemetry

Sasa kifaa chako kimeunganishwa, unaweza kutuma telemetry kwa IoT Hub badala ya broker ya MQTT.

### Kazi - tuma telemetry

1. Ongeza kazi ifuatayo juu ya kazi ya `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Msimbo huu unaunda ujumbe wa IoT Hub kutoka kwa kamba iliyopitishwa kama parameter, unautuma kwa hub, kisha unasafisha kitu cha ujumbe.

1. Ita msimbo huu kwenye kazi ya `loop`, mara tu baada ya mstari ambapo telemetry inatumwa kwenye bandari ya serial:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Shughulikia amri

Kifaa chako kinahitaji kushughulikia amri kutoka kwa msimbo wa seva ili kudhibiti relay. Hii inatumwa kama ombi la moja kwa moja la mbinu.

## Kazi - shughulikia ombi la moja kwa moja la mbinu

1. Ongeza msimbo ufuatao kabla ya kazi ya `connectIoTHub`:

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

    Msimbo huu unafafanua kazi ya callback ambayo maktaba ya IoT Hub inaweza kuita inapopokea ombi la moja kwa moja la mbinu. Mbinu inayotakiwa inatumwa kwenye parameter ya `method_name`. Kazi hii inachapisha mbinu iliyoitwa kwenye bandari ya serial, kisha inawasha au inazima relay kulingana na jina la mbinu.

    > 💁 Hii pia inaweza kutekelezwa katika ombi moja la moja kwa moja la mbinu, kwa kupitisha hali inayotakiwa ya relay kwenye payload inayoweza kupitishwa na ombi la mbinu na kupatikana kutoka kwa parameter ya `payload`.

1. Ongeza msimbo ufuatao mwishoni mwa kazi ya `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Maombi ya moja kwa moja ya mbinu yanahitaji majibu, na majibu yako katika sehemu mbili - jibu kama maandishi, na msimbo wa kurudi. Msimbo huu utaunda matokeo kama hati ya JSON ifuatayo:

    ```JSON
    {
        "Result": ""
    }
    ```

    Hii kisha inanakiliwa kwenye parameter ya `response`, na ukubwa wa jibu hili unawekwa kwenye parameter ya `response_size`. Msimbo huu kisha unarudisha `IOTHUB_CLIENT_OK` kuonyesha mbinu ilishughulikiwa kwa usahihi.

1. Unganisha callback kwa kuongeza yafuatayo mwishoni mwa kazi ya `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Kazi ya `loop` itaita kazi ya `IoTHubDeviceClient_LL_DoWork` kushughulikia matukio yanayotumwa na IoT Hub. Hii inaitwa kila sekunde 10 kutokana na `delay`, ikimaanisha mbinu za moja kwa moja zinashughulikiwa kila sekunde 10 tu. Ili kufanya hii kuwa bora zaidi, kuchelewesha kwa sekunde 10 kunaweza kutekelezwa kama kuchelewesha kwa muda mfupi zaidi, kwa kuita `IoTHubDeviceClient_LL_DoWork` kila wakati. Ili kufanya hivi, ongeza msimbo ufuatao juu ya kazi ya `loop`:

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

    Msimbo huu utarudia mara kwa mara, ukipiga `IoTHubDeviceClient_LL_DoWork` na kuchelewesha kwa 100ms kila wakati. Itafanya hivi mara nyingi kama inavyohitajika kuchelewesha kwa muda uliotolewa kwenye parameter ya `delay_time`. Hii inamaanisha kifaa kinangoja kwa muda wa juu zaidi wa 100ms kushughulikia maombi ya moja kwa moja ya mbinu.

1. Katika kazi ya `loop`, ondoa mwito wa `IoTHubDeviceClient_LL_DoWork`, na badilisha mwito wa `delay(10000)` na yafuatayo ili kuita kazi hii mpya:

    ```cpp
    work_delay(10000);
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Programu yako ya sensor ya unyevu wa udongo imeunganishwa na IoT Hub yako!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.