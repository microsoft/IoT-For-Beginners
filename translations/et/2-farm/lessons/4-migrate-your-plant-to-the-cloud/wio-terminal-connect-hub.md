<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-10-11T12:29:20+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "et"
}
-->
# Ühenda oma IoT-seade pilvega - Wio Terminal

Selles õppetunni osas ühendad oma Wio Terminali IoT Hubiga, et saata telemeetriat ja vastu võtta käske.

## Ühenda oma seade IoT Hubiga

Järgmine samm on seadme ühendamine IoT Hubiga.

### Ülesanne - ühendamine IoT Hubiga

1. Ava projekt `soil-moisture-sensor` VS Code'is.

1. Ava fail `platformio.ini`. Eemalda `knolleary/PubSubClient` teegi sõltuvus. Seda kasutati avaliku MQTT maakleri ühendamiseks, kuid IoT Hubiga ühendamiseks pole seda vaja.

1. Lisa järgmised teegi sõltuvused:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

   `Seeed Arduino RTC` teek pakub koodi, et suhelda Wio Terminali reaalaja kellaga, mida kasutatakse aja jälgimiseks. Ülejäänud teegid võimaldavad IoT-seadmel IoT Hubiga ühendust luua.

1. Lisa järgmine `platformio.ini` faili lõppu:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

   See määrab kompilaatori lipu, mis on vajalik Arduino IoT Hub koodi kompileerimisel.

1. Ava päisefail `config.h`. Eemalda kõik MQTT seaded ja lisa järgmine konstant seadme ühenduse stringi jaoks:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

   Asenda `<connection string>` seadme ühenduse stringiga, mille varem kopeerisid.

1. IoT Hubiga ühendus kasutab ajapõhist tokenit. See tähendab, et IoT-seade peab teadma praegust aega. Erinevalt operatsioonisüsteemidest nagu Windows, macOS või Linux, ei sünkroniseeri mikrokontrollerid automaatselt praegust aega Interneti kaudu. Seetõttu pead lisama koodi, et saada praegune aeg [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) serverist. Kui aeg on saadud, saab selle salvestada Wio Terminali reaalaja kellas, mis võimaldab hiljem õiget aega küsida, eeldades, et seade ei kaota voolu. Lisa uus fail nimega `ntp.h` järgmise koodiga:

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

   Selle koodi üksikasjad jäävad õppetunni ulatusest välja. See määratleb funktsiooni `initTime`, mis saab praeguse aja NTP serverist ja kasutab seda Wio Terminali kella seadistamiseks.

1. Ava fail `main.cpp` ja eemalda kogu MQTT kood, sealhulgas päisefail `PubSubClient.h`, `PubSubClient` muutuja deklaratsioon, meetodid `reconnectMQTTClient` ja `createMQTTClient` ning kõik viited nendele muutujatele ja meetoditele. Fail peaks sisaldama ainult koodi WiFi-ühenduse loomiseks, mulla niiskuse saamiseks ja selle JSON-dokumendiks muutmiseks.

1. Lisa järgmised `#include` direktiivid faili `main.cpp` ülaossa, et lisada IoT Hubi teekide ja aja seadistamise päisefailid:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Lisa järgmine kutse `setup` funktsiooni lõppu, et määrata praegune aeg:

    ```cpp
    initTime();
    ```

1. Lisa järgmine muutuja deklaratsioon faili ülaossa, kohe pärast `include` direktiive:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

   See deklareerib `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, mis on käepide IoT Hubi ühenduse jaoks.

1. Lisa selle alla järgmine kood:

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

   See määratleb tagasihelistamise funktsiooni, mida kutsutakse, kui IoT Hubi ühenduse olek muutub, näiteks ühendamine või lahtiühendamine. Oleku teave saadetakse serial porti.

1. Lisa selle alla funktsioon IoT Hubiga ühendamiseks:

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

   See kood algatab IoT Hubi teegi koodi, seejärel loob ühenduse, kasutades `config.h` päisefailis olevat ühenduse stringi. See ühendus põhineb MQTT-l. Kui ühendus ebaõnnestub, saadetakse see serial porti - kui näed seda väljundis, kontrolli ühenduse stringi. Lõpuks seadistatakse ühenduse oleku tagasihelistamine.

1. Kutsu seda funktsiooni `setup` funktsioonis, kohe pärast `initTime` kutset:

    ```cpp
    connectIoTHub();
    ```

1. Nagu MQTT kliendi puhul, töötab see kood ühel lõimel, seega vajab aega sõnumite töötlemiseks, mida saadetakse hubist ja hubi. Lisa järgmine kood `loop` funktsiooni algusesse, et seda teha:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Koosta ja laadi see kood üles. Näed ühendust serial monitoris:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

   Väljundis näed NTP aja hankimist, millele järgneb seadme kliendi ühendamine. Ühendamine võib võtta paar sekundit, seega võid näha mulla niiskust väljundis, samal ajal kui seade ühendub.

   > 💁 Saad UNIX aja NTP jaoks muuta loetavamaks versiooniks, kasutades veebisaiti nagu [unixtimestamp.com](https://www.unixtimestamp.com).

## Telemeetria saatmine

Nüüd, kui seade on ühendatud, saad saata telemeetria IoT Hubi asemel MQTT maaklerile.

### Ülesanne - telemeetria saatmine

1. Lisa järgmine funktsioon `setup` funktsiooni kohale:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

   See kood loob IoT Hubi sõnumi stringist, mis antakse parameetrina, saadab selle hubi, seejärel puhastab sõnumi objekti.

1. Kutsu seda koodi `loop` funktsioonis, kohe pärast rida, kus telemeetria saadetakse serial porti:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Käskude käsitlemine

Sinu seade peab käsitlema serveri koodi käsku relee juhtimiseks. See saadetakse otsese meetodi päringuna.

## Ülesanne - otsese meetodi päringu käsitlemine

1. Lisa järgmine kood enne funktsiooni `connectIoTHub`:

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

   See kood määratleb tagasihelistamise meetodi, mida IoT Hubi teek saab kutsuda, kui see saab otsese meetodi päringu. Meetod, mida küsitakse, saadetakse parameetris `method_name`. See funktsioon prindib kutsutud meetodi serial porti, seejärel lülitab relee sisse või välja sõltuvalt meetodi nimest.

   > 💁 Seda võiks rakendada ka ühe otsese meetodi päringuna, edastades soovitud relee oleku koormuses, mida saab päringuga kaasa anda ja mis on saadaval parameetrist `payload`.

1. Lisa järgmine kood funktsiooni `directMethodCallback` lõppu:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

   Otsese meetodi päringud vajavad vastust, mis koosneb kahest osast - vastus tekstina ja tagastuskood. See kood loob tulemuse järgmise JSON-dokumendina:

    ```JSON
    {
        "Result": ""
    }
    ```

   See kopeeritakse parameetrisse `response` ja selle suurus määratakse parameetris `response_size`. See kood tagastab `IOTHUB_CLIENT_OK`, et näidata, et meetod käsitleti õigesti.

1. Ühenda tagasihelistamine, lisades järgmise funktsiooni `connectIoTHub` lõppu:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funktsioon `loop` kutsub funktsiooni `IoTHubDeviceClient_LL_DoWork`, et töödelda IoT Hubi saadetud sündmusi. Seda kutsutakse ainult iga 10 sekundi järel `delay` tõttu, mis tähendab, et otseseid meetodeid töödeldakse ainult iga 10 sekundi järel. Selle tõhusamaks muutmiseks saab 10-sekundilise viivituse rakendada mitme lühema viivitusena, kutsudes `IoTHubDeviceClient_LL_DoWork` iga kord. Selleks lisa järgmine kood `loop` funktsiooni kohale:

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

   See kood kordab korduvalt, kutsudes `IoTHubDeviceClient_LL_DoWork` ja viivitades iga kord 100 ms. See teeb seda nii mitu korda, kui on vaja viivitada antud aja jooksul parameetris `delay_time`. See tähendab, et seade ootab maksimaalselt 100 ms, et töödelda otsese meetodi päringuid.

1. Funktsioonis `loop` eemalda kutse `IoTHubDeviceClient_LL_DoWork` ja asenda `delay(10000)` järgmisega, et kutsuda uut funktsiooni:

    ```cpp
    work_delay(10000);
    ```

> 💁 Selle koodi leiad kaustast [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Sinu mulla niiskuse sensori programm on ühendatud IoT Hubiga!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.