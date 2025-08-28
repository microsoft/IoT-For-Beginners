<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T15:05:46+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "sl"
}
-->
# Povežite svojo IoT napravo z oblakom - Wio Terminal

V tem delu lekcije boste povezali svoj Wio Terminal z IoT Hub, da boste lahko pošiljali telemetrijo in prejemali ukaze.

## Povežite svojo napravo z IoT Hub

Naslednji korak je povezava vaše naprave z IoT Hub.

### Naloga - povezava z IoT Hub

1. Odprite projekt `soil-moisture-sensor` v VS Code.

1. Odprite datoteko `platformio.ini`. Odstranite odvisnost knjižnice `knolleary/PubSubClient`. Ta je bila uporabljena za povezavo z javnim MQTT posrednikom, vendar ni potrebna za povezavo z IoT Hub.

1. Dodajte naslednje odvisnosti knjižnic:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Knjižnica `Seeed Arduino RTC` omogoča kodo za interakcijo z realnočasovno uro v Wio Terminal, ki se uporablja za sledenje času. Preostale knjižnice omogočajo vaši IoT napravi povezavo z IoT Hub.

1. Na dno datoteke `platformio.ini` dodajte naslednje:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    To nastavi zastavico prevajalnika, ki je potrebna pri prevajanju kode za Arduino IoT Hub.

1. Odprite glavno datoteko `config.h`. Odstranite vse nastavitve MQTT in dodajte naslednjo konstanto za povezovalni niz naprave:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Zamenjajte `<connection string>` s povezovalnim nizom za vašo napravo, ki ste ga prej kopirali.

1. Povezava z IoT Hub uporablja žeton, ki temelji na času. To pomeni, da mora IoT naprava poznati trenutni čas. Za razliko od operacijskih sistemov, kot so Windows, macOS ali Linux, mikrokrmilniki ne sinhronizirajo samodejno trenutnega časa prek interneta. Zato morate dodati kodo za pridobitev trenutnega časa s strežnika [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Ko je čas pridobljen, se lahko shrani v realnočasovno uro v Wio Terminal, kar omogoča pridobitev pravilnega časa pozneje, če naprava ne izgubi napajanja. Dodajte novo datoteko z imenom `ntp.h` z naslednjo kodo:

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

    Podrobnosti te kode so zunaj obsega te lekcije. Določa funkcijo `initTime`, ki pridobi trenutni čas s strežnika NTP in ga uporabi za nastavitev ure na Wio Terminal.

1. Odprite datoteko `main.cpp` in odstranite vso kodo MQTT, vključno z glavno datoteko `PubSubClient.h`, deklaracijo spremenljivke `PubSubClient`, metodama `reconnectMQTTClient` in `createMQTTClient` ter vse klice teh spremenljivk in metod. Ta datoteka naj vsebuje samo kodo za povezavo z WiFi, pridobitev vlažnosti tal in ustvarjanje JSON dokumenta s temi podatki.

1. Na vrh datoteke `main.cpp` dodajte naslednje direktive `#include`, da vključite glavne datoteke za knjižnice IoT Hub in za nastavitev časa:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Na konec funkcije `setup` dodajte naslednji klic za nastavitev trenutnega časa:

    ```cpp
    initTime();
    ```

1. Na vrh datoteke, tik pod direktive `#include`, dodajte naslednjo deklaracijo spremenljivke:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    To deklarira `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, ročaj za povezavo z IoT Hub.

1. Pod to dodajte naslednjo kodo:

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

    To deklarira povratno funkcijo, ki se bo klicala, ko se spremeni stanje povezave z IoT Hub, na primer ob povezovanju ali prekinitvi povezave. Stanje se pošlje na serijski vmesnik.

1. Pod to dodajte funkcijo za povezavo z IoT Hub:

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

    Ta koda inicializira knjižnično kodo IoT Hub, nato ustvari povezavo z uporabo povezovalnega niza v glavni datoteki `config.h`. Ta povezava temelji na MQTT. Če povezava ne uspe, se to pošlje na serijski vmesnik - če to vidite v izhodu, preverite povezovalni niz. Na koncu se nastavi povratni klic za stanje povezave.

1. To funkcijo pokličite v funkciji `setup` pod klicem `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Tako kot pri MQTT odjemalcu, ta koda deluje na enem niti, zato potrebuje čas za obdelavo sporočil, ki jih pošilja hub in ki so poslana hubu. Na vrh funkcije `loop` dodajte naslednje:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Sestavite in naložite to kodo. Povezavo boste videli v serijskem monitorju:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    V izhodu lahko vidite, kako se pridobi čas NTP, nato pa se naprava poveže z IoT Hub. Povezava lahko traja nekaj sekund, zato lahko medtem v izhodu vidite vlažnost tal.

    > 💁 UNIX čas za NTP lahko pretvorite v bolj berljivo obliko s spletnim mestom, kot je [unixtimestamp.com](https://www.unixtimestamp.com)

## Pošiljanje telemetrije

Zdaj, ko je vaša naprava povezana, lahko pošiljate telemetrijo v IoT Hub namesto v MQTT posrednik.

### Naloga - pošiljanje telemetrije

1. Nad funkcijo `setup` dodajte naslednjo funkcijo:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Ta koda ustvari sporočilo IoT Hub iz niza, ki je podan kot parameter, ga pošlje v hub in nato počisti objekt sporočila.

1. To kodo pokličite v funkciji `loop`, takoj za vrstico, kjer se telemetrija pošlje na serijski vmesnik:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Obdelava ukazov

Vaša naprava mora obdelati ukaz iz strežniške kode za nadzor releja. To se pošlje kot zahteva za neposredno metodo.

## Naloga - obdelava zahteve za neposredno metodo

1. Pred funkcijo `connectIoTHub` dodajte naslednjo kodo:

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

    Ta koda določa povratno metodo, ki jo lahko knjižnica IoT Hub pokliče, ko prejme zahtevo za neposredno metodo. Metoda, ki je zahtevana, je poslana v parametru `method_name`. Ta funkcija izpiše ime metode na serijski vmesnik, nato pa vklopi ali izklopi rele, odvisno od imena metode.

    > 💁 To bi lahko izvedli tudi z eno samo zahtevo za neposredno metodo, pri čemer bi želeno stanje releja poslali v vsebini, ki jo je mogoče posredovati z zahtevo metode in je na voljo v parametru `payload`.

1. Na konec funkcije `directMethodCallback` dodajte naslednjo kodo:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Zahteve za neposredno metodo potrebujejo odgovor, ki je sestavljen iz dveh delov - odgovora kot besedilo in povratne kode. Ta koda ustvari rezultat kot naslednji JSON dokument:

    ```JSON
    {
        "Result": ""
    }
    ```

    Ta se nato kopira v parameter `response`, velikost tega odgovora pa se nastavi v parametru `response_size`. Ta koda nato vrne `IOTHUB_CLIENT_OK`, da pokaže, da je bila metoda pravilno obdelana.

1. Povratno funkcijo povežite tako, da na konec funkcije `connectIoTHub` dodate naslednje:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funkcija `loop` bo klicala funkcijo `IoTHubDeviceClient_LL_DoWork` za obdelavo dogodkov, ki jih pošlje IoT Hub. To se trenutno kliče vsakih 10 sekund zaradi `delay`, kar pomeni, da se neposredne metode obdelajo le vsakih 10 sekund. Da bi to naredili bolj učinkovito, lahko 10-sekundno zamudo izvedemo kot več krajših zamud, pri čemer vsakič pokličemo `IoTHubDeviceClient_LL_DoWork`. Za to nad funkcijo `loop` dodajte naslednjo kodo:

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

    Ta koda bo ponavljala zanke, klicala `IoTHubDeviceClient_LL_DoWork` in vsakič zamudila za 100 ms. To bo storila tolikokrat, kolikor je potrebno, da zamudi za čas, podan v parametru `delay_time`. To pomeni, da naprava čaka največ 100 ms za obdelavo zahtev za neposredno metodo.

1. V funkciji `loop` odstranite klic `IoTHubDeviceClient_LL_DoWork` in zamenjajte klic `delay(10000)` z naslednjim, da pokličete to novo funkcijo:

    ```cpp
    work_delay(10000);
    ```

> 💁 To kodo lahko najdete v mapi [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Vaš program za senzor vlažnosti tal je povezan z vašim IoT Hub!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve AI za prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.