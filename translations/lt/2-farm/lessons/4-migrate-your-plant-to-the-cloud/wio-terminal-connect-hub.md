<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T20:34:49+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "lt"
}
-->
# Prijunkite savo IoT įrenginį prie debesies - Wio Terminal

Šioje pamokos dalyje prijungsite savo Wio Terminal prie IoT Hub, kad galėtumėte siųsti telemetriją ir gauti komandas.

## Prijunkite savo įrenginį prie IoT Hub

Kitas žingsnis - prijungti savo įrenginį prie IoT Hub.

### Užduotis - prisijungti prie IoT Hub

1. Atidarykite `soil-moisture-sensor` projektą VS Code.

1. Atidarykite `platformio.ini` failą. Pašalinkite `knolleary/PubSubClient` bibliotekos priklausomybę. Ji buvo naudojama prisijungti prie viešojo MQTT brokerio, tačiau nėra reikalinga jungiantis prie IoT Hub.

1. Pridėkite šias bibliotekų priklausomybes:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` biblioteka suteikia kodą, skirtą sąveikai su realaus laiko laikrodžiu Wio Terminal įrenginyje, kuris naudojamas laikui sekti. Likusios bibliotekos leidžia jūsų IoT įrenginiui prisijungti prie IoT Hub.

1. Pridėkite šį kodą į `platformio.ini` failo apačią:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Tai nustato kompiliatoriaus vėliavą, kuri reikalinga kompiliuojant Arduino IoT Hub kodą.

1. Atidarykite `config.h` antraštės failą. Pašalinkite visus MQTT nustatymus ir pridėkite šią konstantą įrenginio prisijungimo eilutei:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Pakeiskite `<connection string>` į jūsų įrenginio prisijungimo eilutę, kurią nukopijavote anksčiau.

1. Prisijungimas prie IoT Hub naudoja laiko pagrindu sukurtą žetoną. Tai reiškia, kad IoT įrenginys turi žinoti dabartinį laiką. Skirtingai nuo operacinių sistemų, tokių kaip Windows, macOS ar Linux, mikrovaldikliai automatiškai nesinchronizuoja dabartinio laiko per internetą. Todėl turėsite pridėti kodą, kuris gautų dabartinį laiką iš [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) serverio. Kai laikas bus gautas, jis gali būti saugomas realaus laiko laikrodyje Wio Terminal įrenginyje, leidžiant vėliau gauti teisingą laiką, jei įrenginys nepraranda maitinimo. Sukurkite naują failą pavadinimu `ntp.h` su šiuo kodu:

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

    Šio kodo detalės nėra šios pamokos dalis. Jis apibrėžia funkciją `initTime`, kuri gauna dabartinį laiką iš NTP serverio ir naudoja jį laikrodžio nustatymui Wio Terminal įrenginyje.

1. Atidarykite `main.cpp` failą ir pašalinkite visą MQTT kodą, įskaitant `PubSubClient.h` antraštės failą, `PubSubClient` kintamojo deklaraciją, `reconnectMQTTClient` ir `createMQTTClient` metodus bei visus šių kintamųjų ir metodų iškvietimus. Šiame faile turėtų likti tik kodas, skirtas prisijungti prie WiFi, gauti dirvožemio drėgmės duomenis ir sukurti JSON dokumentą su šiais duomenimis.

1. Pridėkite šias `#include` direktyvas į `main.cpp` failo viršų, kad įtrauktumėte antraštės failus, skirtus IoT Hub bibliotekoms ir laikui nustatyti:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Pridėkite šį iškvietimą į `setup` funkcijos pabaigą, kad nustatytumėte dabartinį laiką:

    ```cpp
    initTime();
    ```

1. Pridėkite šią kintamojo deklaraciją failo viršuje, iškart po `include` direktyvų:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Tai deklaruoja `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, kuris yra ryšio su IoT Hub rankena.

1. Po to pridėkite šį kodą:

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

    Tai deklaruoja atgalinio iškvietimo funkciją, kuri bus iškviečiama, kai ryšio su IoT Hub būsena pasikeis, pvz., prisijungiant ar atsijungiant. Būsena bus išsiųsta į serijinį prievadą.

1. Po to pridėkite funkciją, skirtą prisijungti prie IoT Hub:

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

    Šis kodas inicializuoja IoT Hub bibliotekos kodą, tada sukuria ryšį, naudodamas prisijungimo eilutę iš `config.h` antraštės failo. Šis ryšys yra pagrįstas MQTT. Jei ryšys nepavyksta, tai bus išsiųsta į serijinį prievadą - jei tai matote išvestyje, patikrinkite prisijungimo eilutę. Galiausiai nustatomas ryšio būsenos atgalinis iškvietimas.

1. Iškvieskite šią funkciją `setup` funkcijoje, po `initTime` iškvietimo:

    ```cpp
    connectIoTHub();
    ```

1. Kaip ir su MQTT klientu, šis kodas veikia viename siūle, todėl jam reikia laiko apdoroti žinutes, siunčiamas iš hub'o ir į hub'ą. Pridėkite šį kodą į `loop` funkcijos viršų, kad tai atliktumėte:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Sukompiliuokite ir įkelkite šį kodą. Serijiniame monitoriuje pamatysite ryšį:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Išvestyje galite matyti, kaip gaunamas NTP laikas, po to įrenginio klientas prisijungia. Prisijungimas gali užtrukti kelias sekundes, todėl galite matyti dirvožemio drėgmės duomenis išvestyje, kol įrenginys jungiasi.

    > 💁 UNIX laiką iš NTP galite konvertuoti į labiau suprantamą formatą naudodami tokias svetaines kaip [unixtimestamp.com](https://www.unixtimestamp.com)

## Siųskite telemetriją

Dabar, kai jūsų įrenginys prijungtas, galite siųsti telemetriją į IoT Hub vietoj MQTT brokerio.

### Užduotis - siųsti telemetriją

1. Pridėkite šią funkciją virš `setup` funkcijos:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Šis kodas sukuria IoT Hub žinutę iš eilutės, perduotos kaip parametras, išsiunčia ją į hub'ą, tada išvalo žinutės objektą.

1. Iškvieskite šį kodą `loop` funkcijoje, iškart po eilutės, kur telemetrija siunčiama į serijinį prievadą:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Apdorokite komandas

Jūsų įrenginys turi apdoroti komandą iš serverio kodo, kad valdytų relę. Tai siunčiama kaip tiesioginio metodo užklausa.

## Užduotis - apdoroti tiesioginio metodo užklausą

1. Pridėkite šį kodą prieš `connectIoTHub` funkciją:

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

    Šis kodas apibrėžia atgalinio iškvietimo metodą, kurį IoT Hub biblioteka gali iškviesti, kai gauna tiesioginio metodo užklausą. Metodas, kuris yra užklaustas, perduodamas `method_name` parametru. Ši funkcija išspausdina iškviestą metodą į serijinį prievadą, tada įjungia arba išjungia relę, priklausomai nuo metodo pavadinimo.

    > 💁 Tai taip pat galėtų būti įgyvendinta vienoje tiesioginio metodo užklausoje, perduodant norimą relės būseną kaip naudingąją apkrovą, kurią galima perduoti su metodo užklausa ir pasiekti iš `payload` parametro.

1. Pridėkite šį kodą į `directMethodCallback` funkcijos pabaigą:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Tiesioginio metodo užklausoms reikia atsakymo, kuris susideda iš dviejų dalių - atsakymo kaip teksto ir grąžinimo kodo. Šis kodas sukurs rezultatą kaip šį JSON dokumentą:

    ```JSON
    {
        "Result": ""
    }
    ```

    Tada jis bus nukopijuotas į `response` parametrą, o šio atsakymo dydis bus nustatytas `response_size` parametru. Šis kodas grąžins `IOTHUB_CLIENT_OK`, kad parodytų, jog metodas buvo tinkamai apdorotas.

1. Prijunkite atgalinį iškvietimą, pridėdami šį kodą į `connectIoTHub` funkcijos pabaigą:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` funkcija iškvies `IoTHubDeviceClient_LL_DoWork` funkciją, kad apdorotų įvykius, siunčiamus IoT Hub. Tai iškviečiama tik kas 10 sekundžių dėl `delay`, todėl tiesioginiai metodai apdorojami tik kas 10 sekundžių. Kad tai būtų efektyviau, 10 sekundžių vėlavimą galima įgyvendinti kaip daug trumpesnių vėlavimų, kiekvieną kartą iškviečiant `IoTHubDeviceClient_LL_DoWork`. Norėdami tai padaryti, pridėkite šį kodą virš `loop` funkcijos:

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

    Šis kodas kartosis, iškviesdamas `IoTHubDeviceClient_LL_DoWork` ir vėluodamas po 100 ms kiekvieną kartą. Tai darys tiek kartų, kiek reikia, kad vėluotų nurodytą laiką `delay_time` parametru. Tai reiškia, kad įrenginys laukia daugiausiai 100 ms, kad apdorotų tiesioginio metodo užklausas.

1. `loop` funkcijoje pašalinkite `IoTHubDeviceClient_LL_DoWork` iškvietimą ir pakeiskite `delay(10000)` iškvietimu šiuo kodu:

    ```cpp
    work_delay(10000);
    ```

> 💁 Šį kodą galite rasti [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) aplanke.

😀 Jūsų dirvožemio drėgmės jutiklio programa prijungta prie jūsų IoT Hub!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.