<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T15:05:06+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "hr"
}
-->
# Povežite svoj IoT uređaj s oblakom - Wio Terminal

U ovom dijelu lekcije povezat ćete svoj Wio Terminal s IoT Hubom kako biste slali telemetriju i primali naredbe.

## Povežite svoj uređaj s IoT Hubom

Sljedeći korak je povezivanje vašeg uređaja s IoT Hubom.

### Zadatak - povezivanje s IoT Hubom

1. Otvorite projekt `soil-moisture-sensor` u VS Codeu.

1. Otvorite datoteku `platformio.ini`. Uklonite ovisnost o biblioteci `knolleary/PubSubClient`. Ova biblioteka je korištena za povezivanje s javnim MQTT brokerom i nije potrebna za povezivanje s IoT Hubom.

1. Dodajte sljedeće ovisnosti o bibliotekama:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Biblioteka `Seeed Arduino RTC` omogućuje interakciju s real-time satom u Wio Terminalu, koji se koristi za praćenje vremena. Preostale biblioteke omogućuju vašem IoT uređaju povezivanje s IoT Hubom.

1. Dodajte sljedeće na dno datoteke `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Ovo postavlja zastavicu kompajlera koja je potrebna prilikom kompajliranja Arduino IoT Hub koda.

1. Otvorite zaglavlje `config.h`. Uklonite sve MQTT postavke i dodajte sljedeću konstantu za connection string uređaja:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Zamijenite `<connection string>` s connection stringom vašeg uređaja koji ste ranije kopirali.

1. Povezivanje s IoT Hubom koristi token temeljen na vremenu. To znači da IoT uređaj mora znati trenutno vrijeme. Za razliku od operativnih sustava poput Windowsa, macOS-a ili Linuxa, mikrokontroleri ne sinkroniziraju automatski trenutno vrijeme putem Interneta. To znači da ćete morati dodati kod za dobivanje trenutnog vremena s [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) servera. Kada se vrijeme preuzme, može se pohraniti u real-time sat u Wio Terminalu, omogućujući kasnije dohvaćanje točnog vremena, pod uvjetom da uređaj ne izgubi napajanje. Dodajte novu datoteku pod nazivom `ntp.h` sa sljedećim kodom:

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

    Detalji ovog koda nisu obuhvaćeni ovom lekcijom. Definira funkciju `initTime` koja dohvaća trenutno vrijeme s NTP servera i koristi ga za postavljanje sata na Wio Terminalu.

1. Otvorite datoteku `main.cpp` i uklonite sav MQTT kod, uključujući zaglavlje `PubSubClient.h`, deklaraciju varijable `PubSubClient`, metode `reconnectMQTTClient` i `createMQTTClient`, te sve pozive tim varijablama i metodama. Ova datoteka treba sadržavati samo kod za povezivanje s WiFi-jem, dobivanje vlažnosti tla i stvaranje JSON dokumenta s tim podacima.

1. Dodajte sljedeće `#include` direktive na vrh datoteke `main.cpp` kako biste uključili zaglavlja za IoT Hub biblioteke i za postavljanje vremena:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Dodajte sljedeći poziv na kraj funkcije `setup` za postavljanje trenutnog vremena:

    ```cpp
    initTime();
    ```

1. Dodajte sljedeću deklaraciju varijable na vrh datoteke, odmah ispod direktiva za uključivanje:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Ovo deklarira `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, ručku za povezivanje s IoT Hubom.

1. Ispod toga dodajte sljedeći kod:

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

    Ovo deklarira callback funkciju koja će se pozvati kada se status veze s IoT Hubom promijeni, poput povezivanja ili prekida veze. Status se šalje na serijski port.

1. Ispod toga dodajte funkciju za povezivanje s IoT Hubom:

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

    Ovaj kod inicijalizira IoT Hub bibliotečki kod, zatim stvara vezu koristeći connection string u zaglavlju `config.h`. Ova veza temelji se na MQTT-u. Ako veza ne uspije, to se šalje na serijski port - ako to vidite u izlazu, provjerite connection string. Na kraju se postavlja callback za status veze.

1. Pozovite ovu funkciju u funkciji `setup` ispod poziva `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Kao i kod MQTT klijenta, ovaj kod radi na jednom threadu pa treba vremena za obradu poruka koje hub šalje i prima. Dodajte sljedeće na vrh funkcije `loop` kako biste to omogućili:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Izgradite i učitajte ovaj kod. Vidjet ćete vezu u serijskom monitoru:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    U izlazu možete vidjeti kako se dohvaća NTP vrijeme, nakon čega se uređaj povezuje s IoT Hubom. Može proći nekoliko sekundi da se poveže, pa ćete možda vidjeti vlažnost tla u izlazu dok se uređaj povezuje.

    > 💁 UNIX vrijeme iz NTP-a možete pretvoriti u čitljiviji format koristeći web stranicu poput [unixtimestamp.com](https://www.unixtimestamp.com)

## Slanje telemetrije

Sada kada je vaš uređaj povezan, možete slati telemetriju na IoT Hub umjesto na MQTT broker.

### Zadatak - slanje telemetrije

1. Dodajte sljedeću funkciju iznad funkcije `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Ovaj kod stvara IoT Hub poruku iz stringa proslijeđenog kao parametar, šalje je na hub, a zatim čisti objekt poruke.

1. Pozovite ovaj kod u funkciji `loop`, odmah nakon linije gdje se telemetrija šalje na serijski port:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Obrada naredbi

Vaš uređaj treba obraditi naredbu s poslužiteljskog koda za upravljanje relejem. Ovo se šalje kao zahtjev za izravnu metodu.

## Zadatak - obrada zahtjeva za izravnu metodu

1. Dodajte sljedeći kod prije funkcije `connectIoTHub`:

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

    Ovaj kod definira callback metodu koju IoT Hub biblioteka može pozvati kada primi zahtjev za izravnu metodu. Metoda koja se traži šalje se u parametru `method_name`. Ova funkcija ispisuje pozvanu metodu na serijski port, a zatim uključuje ili isključuje relej ovisno o nazivu metode.

    > 💁 Ovo bi se također moglo implementirati u jednoj izravnoj metodi, prosljeđujući željeno stanje releja u payloadu koji se može proslijediti sa zahtjevom metode i koji je dostupan iz parametra `payload`.

1. Dodajte sljedeći kod na kraj funkcije `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Zahtjevi za izravne metode trebaju odgovor, a odgovor se sastoji od dva dijela - odgovora kao teksta i povratnog koda. Ovaj kod stvara rezultat kao sljedeći JSON dokument:

    ```JSON
    {
        "Result": ""
    }
    ```

    Ovo se zatim kopira u parametar `response`, a veličina ovog odgovora postavlja se u parametar `response_size`. Ovaj kod zatim vraća `IOTHUB_CLIENT_OK` kako bi pokazao da je metoda ispravno obrađena.

1. Povežite callback dodavanjem sljedećeg na kraj funkcije `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funkcija `loop` će pozvati funkciju `IoTHubDeviceClient_LL_DoWork` za obradu događaja koje šalje IoT Hub. Ovo se poziva samo svakih 10 sekundi zbog `delay`, što znači da se izravne metode obrađuju samo svakih 10 sekundi. Kako bi ovo bilo učinkovitije, 10-sekundno kašnjenje može se implementirati kao mnogo kraćih kašnjenja, pozivajući `IoTHubDeviceClient_LL_DoWork` svaki put. Da biste to učinili, dodajte sljedeći kod iznad funkcije `loop`:

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

    Ovaj kod će se ponavljati, pozivajući `IoTHubDeviceClient_LL_DoWork` i odgađajući za 100 ms svaki put. To će činiti onoliko puta koliko je potrebno da se odgodi za vrijeme dano u parametru `delay_time`. To znači da uređaj čeka najviše 100 ms za obradu zahtjeva za izravne metode.

1. U funkciji `loop`, uklonite poziv `IoTHubDeviceClient_LL_DoWork` i zamijenite poziv `delay(10000)` sljedećim kako biste pozvali ovu novu funkciju:

    ```cpp
    work_delay(10000);
    ```

> 💁 Ovaj kod možete pronaći u mapi [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Vaš program za senzor vlažnosti tla povezan je s vašim IoT Hubom!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.