<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T21:33:31+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "fi"
}
-->
# Yhdistä IoT-laitteesi pilveen - Wio Terminal

Tässä osassa oppituntia yhdistät Wio Terminal -laitteesi IoT Hubiin, jotta voit lähettää telemetriatietoja ja vastaanottaa komentoja.

## Yhdistä laite IoT Hubiin

Seuraava vaihe on yhdistää laite IoT Hubiin.

### Tehtävä - yhdistäminen IoT Hubiin

1. Avaa `soil-moisture-sensor`-projekti VS Codessa.

1. Avaa `platformio.ini`-tiedosto. Poista `knolleary/PubSubClient`-kirjastoriippuvuus. Tätä käytettiin yhteyden muodostamiseen julkiseen MQTT-välittäjään, mutta sitä ei tarvita IoT Hubiin yhdistämisessä.

1. Lisää seuraavat kirjastoriippuvuudet:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC`-kirjasto tarjoaa koodin reaaliaikaisen kellon käyttöön Wio Terminalissa, jota käytetään ajan seuraamiseen. Loput kirjastot mahdollistavat IoT-laitteen yhdistämisen IoT Hubiin.

1. Lisää seuraava `platformio.ini`-tiedoston loppuun:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Tämä asettaa kääntäjän lipun, joka tarvitaan Arduino IoT Hub -koodin kääntämisessä.

1. Avaa `config.h`-otsikkotiedosto. Poista kaikki MQTT-asetukset ja lisää seuraava vakio laitteen yhteysmerkkijonolle:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Korvaa `<connection string>` laitteen aiemmin kopioimallasi yhteysmerkkijonolla.

1. Yhteys IoT Hubiin käyttää aikaan perustuvaa tunnistetta. Tämä tarkoittaa, että IoT-laitteen täytyy tietää nykyinen aika. Toisin kuin käyttöjärjestelmät kuten Windows, macOS tai Linux, mikrokontrollerit eivät automaattisesti synkronoi nykyistä aikaa Internetin kautta. Tämä tarkoittaa, että sinun täytyy lisätä koodi, joka hakee nykyisen ajan [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)-palvelimelta. Kun aika on haettu, se voidaan tallentaa reaaliaikakelloon Wio Terminalissa, jolloin oikea aika voidaan pyytää myöhemmin, olettaen että laite ei menetä virtaa. Lisää uusi tiedosto nimeltä `ntp.h` seuraavalla koodilla:

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

    Tämän koodin yksityiskohdat ovat oppitunnin ulkopuolella. Se määrittää funktion nimeltä `initTime`, joka hakee nykyisen ajan NTP-palvelimelta ja käyttää sitä Wio Terminalin kellon asettamiseen.

1. Avaa `main.cpp`-tiedosto ja poista kaikki MQTT-koodi, mukaan lukien `PubSubClient.h`-otsikkotiedosto, `PubSubClient`-muuttujan määrittely, `reconnectMQTTClient`- ja `createMQTTClient`-metodit sekä kaikki kutsut näihin muuttujiin ja metodeihin. Tiedoston tulisi sisältää vain koodi WiFi-yhteyden muodostamiseen, maaperän kosteuden hakemiseen ja JSON-dokumentin luomiseen siitä.

1. Lisää seuraavat `#include`-direktiivit `main.cpp`-tiedoston alkuun IoT Hub -kirjastojen ja ajan asettamisen otsikkotiedostojen sisällyttämiseksi:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Lisää seuraava kutsu `setup`-funktion loppuun nykyisen ajan asettamiseksi:

    ```cpp
    initTime();
    ```

1. Lisää seuraava muuttujan määrittely tiedoston alkuun, juuri sisällytysdirektiivien alapuolelle:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Tämä määrittää `IOTHUB_DEVICE_CLIENT_LL_HANDLE`-muuttujan, joka toimii yhteytenä IoT Hubiin.

1. Lisää tämän alapuolelle seuraava koodi:

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

    Tämä määrittää takaisinsoittotoiminnon, joka kutsutaan, kun yhteyden tila IoT Hubiin muuttuu, kuten yhdistettäessä tai katkaistaessa yhteys. Tila lähetetään sarjaporttiin.

1. Lisää tämän alapuolelle funktio IoT Hubiin yhdistämiseksi:

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

    Tämä koodi alustaa IoT Hub -kirjastokoodin ja luo yhteyden käyttäen `config.h`-otsikkotiedostossa olevaa yhteysmerkkijonoa. Tämä yhteys perustuu MQTT:hen. Jos yhteys epäonnistuu, tämä lähetetään sarjaporttiin - jos näet tämän tulosteessa, tarkista yhteysmerkkijono. Lopuksi yhteyden tilan takaisinsoitto asetetaan.

1. Kutsu tätä funktiota `setup`-funktiossa `initTime`-kutsun alapuolella:

    ```cpp
    connectIoTHub();
    ```

1. Kuten MQTT-asiakkaan kanssa, tämä koodi toimii yksittäisellä säikeellä, joten se tarvitsee aikaa käsitellä viestejä, joita hubi lähettää ja vastaanottaa. Lisää seuraava `loop`-funktion alkuun tämän tekemiseksi:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Käännä ja lataa tämä koodi. Näet yhteyden sarjavalvonnassa:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Tulosteessa näet NTP-ajan haun, jota seuraa laitteen asiakasohjelman yhdistäminen. Yhdistäminen voi kestää muutaman sekunnin, joten saatat nähdä maaperän kosteuden tulosteessa laitteen yhdistämisen aikana.

    > 💁 Voit muuntaa NTP:n UNIX-ajan luettavampaan muotoon käyttämällä verkkosivustoa kuten [unixtimestamp.com](https://www.unixtimestamp.com)

## Lähetä telemetriaa

Nyt kun laitteesi on yhdistetty, voit lähettää telemetriatietoja IoT Hubiin MQTT-välittäjän sijaan.

### Tehtävä - telemetrian lähettäminen

1. Lisää seuraava funktio `setup`-funktion yläpuolelle:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Tämä koodi luo IoT Hub -viestin parametrina annetusta merkkijonosta, lähettää sen hubiin ja siivoaa viestiobjektin.

1. Kutsu tätä koodia `loop`-funktiossa heti rivin jälkeen, jossa telemetria lähetetään sarjaporttiin:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Käsittele komentoja

Laitteesi täytyy käsitellä palvelinkoodista tuleva komento releen ohjaamiseksi. Tämä lähetetään suoran metodipyynnön muodossa.

### Tehtävä - suoran metodipyynnön käsittely

1. Lisää seuraava koodi ennen `connectIoTHub`-funktiota:

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

    Tämä koodi määrittää takaisinsoittometodin, jonka IoT Hub -kirjasto voi kutsua vastaanottaessaan suoran metodipyynnön. Pyydetty metodi lähetetään `method_name`-parametrissa. Tämä funktio tulostaa kutsutun metodin sarjaporttiin ja kytkee releen päälle tai pois päältä metodin nimen mukaan.

    > 💁 Tämä voitaisiin myös toteuttaa yhtenä suorana metodipyyntönä, jossa haluttu releen tila välitetään hyötykuormassa, joka voidaan välittää metodipyynnön mukana ja on saatavilla `payload`-parametrista.

1. Lisää seuraava koodi `directMethodCallback`-funktion loppuun:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Suorille metodipyynnöille tarvitaan vastaus, ja vastaus koostuu kahdesta osasta - tekstivastauksesta ja palautuskoodista. Tämä koodi luo tuloksen seuraavana JSON-dokumenttina:

    ```JSON
    {
        "Result": ""
    }
    ```

    Tämä kopioidaan `response`-parametriin, ja tämän vastauksen koko asetetaan `response_size`-parametriin. Tämä koodi palauttaa `IOTHUB_CLIENT_OK` osoittamaan, että metodi käsiteltiin oikein.

1. Kytke takaisinsoitto lisäämällä seuraava `connectIoTHub`-funktion loppuun:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop`-funktio kutsuu `IoTHubDeviceClient_LL_DoWork`-funktion IoT Hubin lähettämien tapahtumien käsittelemiseksi. Tämä kutsutaan vain 10 sekunnin välein `delay`-kutsun vuoksi, mikä tarkoittaa, että suoria metodeja käsitellään vain 10 sekunnin välein. Tämän tehokkuuden parantamiseksi 10 sekunnin viive voidaan toteuttaa useina lyhyempinä viiveinä, kutsuen `IoTHubDeviceClient_LL_DoWork` joka kerta. Lisää seuraava koodi `loop`-funktion yläpuolelle:

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

    Tämä koodi toistaa kutsuen `IoTHubDeviceClient_LL_DoWork`-funktiota ja viivästyen 100 ms joka kerta. Se tekee tämän niin monta kertaa kuin tarvitaan viivästämään annetun `delay_time`-parametrin ajan. Tämä tarkoittaa, että laite odottaa enintään 100 ms suorien metodipyyntöjen käsittelemiseksi.

1. Poista `loop`-funktiosta `IoTHubDeviceClient_LL_DoWork`-kutsu ja korvaa `delay(10000)`-kutsu seuraavalla kutsuaksesi tämän uuden funktion:

    ```cpp
    work_delay(10000);
    ```

> 💁 Löydät tämän koodin [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal)-kansiosta.

😀 Maaperän kosteusanturin ohjelmasi on yhdistetty IoT Hubiin!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.