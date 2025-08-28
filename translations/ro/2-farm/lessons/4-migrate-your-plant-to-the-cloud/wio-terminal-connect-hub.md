<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T11:26:06+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "ro"
}
-->
# Conectează dispozitivul IoT la cloud - Wio Terminal

În această parte a lecției, vei conecta Wio Terminal la IoT Hub pentru a trimite telemetrie și a primi comenzi.

## Conectează dispozitivul la IoT Hub

Următorul pas este să conectezi dispozitivul la IoT Hub.

### Sarcină - conectează-te la IoT Hub

1. Deschide proiectul `soil-moisture-sensor` în VS Code.

1. Deschide fișierul `platformio.ini`. Elimină dependența de biblioteca `knolleary/PubSubClient`. Aceasta a fost utilizată pentru conectarea la brokerul MQTT public și nu este necesară pentru conectarea la IoT Hub.

1. Adaugă următoarele dependențe de bibliotecă:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Biblioteca `Seeed Arduino RTC` oferă cod pentru interacțiunea cu un ceas în timp real în Wio Terminal, utilizat pentru a urmări timpul. Restul bibliotecilor permit dispozitivului IoT să se conecteze la IoT Hub.

1. Adaugă următoarele la sfârșitul fișierului `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Aceasta setează un flag de compilator necesar pentru compilarea codului Arduino IoT Hub.

1. Deschide fișierul header `config.h`. Elimină toate setările MQTT și adaugă următoarea constantă pentru șirul de conexiune al dispozitivului:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Înlocuiește `<connection string>` cu șirul de conexiune al dispozitivului pe care l-ai copiat anterior.

1. Conexiunea la IoT Hub utilizează un token bazat pe timp. Acest lucru înseamnă că dispozitivul IoT trebuie să cunoască ora curentă. Spre deosebire de sisteme de operare precum Windows, macOS sau Linux, microcontrolerele nu sincronizează automat ora curentă prin Internet. Acest lucru înseamnă că va trebui să adaugi cod pentru a obține ora curentă de la un server [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). După ce ora a fost obținută, aceasta poate fi stocată într-un ceas în timp real în Wio Terminal, permițând solicitarea orei corecte la o dată ulterioară, presupunând că dispozitivul nu pierde alimentarea. Adaugă un fișier nou numit `ntp.h` cu următorul cod:

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

    Detaliile acestui cod sunt în afara scopului lecției. Acesta definește o funcție numită `initTime` care obține ora curentă de la un server NTP și o utilizează pentru a seta ceasul pe Wio Terminal.

1. Deschide fișierul `main.cpp` și elimină tot codul MQTT, inclusiv fișierul header `PubSubClient.h`, declarația variabilei `PubSubClient`, metodele `reconnectMQTTClient` și `createMQTTClient`, și orice apeluri către aceste variabile și metode. Acest fișier ar trebui să conțină doar cod pentru conectarea la WiFi, obținerea umidității solului și crearea unui document JSON cu aceasta.

1. Adaugă următoarele directive `#include` în partea de sus a fișierului `main.cpp` pentru a include fișierele header ale bibliotecilor IoT Hub și pentru setarea timpului:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Adaugă următorul apel la sfârșitul funcției `setup` pentru a seta ora curentă:

    ```cpp
    initTime();
    ```

1. Adaugă următoarea declarație de variabilă în partea de sus a fișierului, chiar sub directivele include:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Aceasta declară un `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, un handle pentru o conexiune la IoT Hub.

1. Sub aceasta, adaugă următorul cod:

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

    Aceasta declară o funcție de callback care va fi apelată atunci când conexiunea la IoT Hub își schimbă starea, cum ar fi conectarea sau deconectarea. Starea este trimisă către portul serial.

1. Sub aceasta, adaugă o funcție pentru conectarea la IoT Hub:

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

    Acest cod inițializează codul bibliotecii IoT Hub, apoi creează o conexiune utilizând șirul de conexiune din fișierul header `config.h`. Această conexiune se bazează pe MQTT. Dacă conexiunea eșuează, acest lucru este trimis către portul serial - dacă vezi acest lucru în output, verifică șirul de conexiune. În final, funcția de callback pentru starea conexiunii este configurată.

1. Apelează această funcție în funcția `setup` sub apelul către `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. La fel ca în cazul clientului MQTT, acest cod rulează pe un singur thread, așa că are nevoie de timp pentru a procesa mesajele trimise de hub și către hub. Adaugă următorul cod în partea de sus a funcției `loop` pentru a face acest lucru:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Compilează și încarcă acest cod. Vei vedea conexiunea în monitorul serial:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    În output poți vedea ora NTP fiind obținută, urmată de clientul dispozitivului conectându-se. Poate dura câteva secunde pentru a se conecta, așa că este posibil să vezi umiditatea solului în output în timp ce dispozitivul se conectează.

    > 💁 Poți converti timpul UNIX pentru NTP într-o versiune mai ușor de citit utilizând un site web precum [unixtimestamp.com](https://www.unixtimestamp.com)

## Trimite telemetrie

Acum că dispozitivul tău este conectat, poți trimite telemetrie către IoT Hub în loc de brokerul MQTT.

### Sarcină - trimite telemetrie

1. Adaugă următoarea funcție deasupra funcției `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Acest cod creează un mesaj IoT Hub dintr-un șir transmis ca parametru, îl trimite către hub, apoi curăță obiectul mesajului.

1. Apelează acest cod în funcția `loop`, imediat după linia unde telemetria este trimisă către portul serial:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Gestionează comenzi

Dispozitivul tău trebuie să gestioneze o comandă de la codul serverului pentru a controla releul. Aceasta este trimisă ca o cerere de metodă directă.

## Sarcină - gestionează o cerere de metodă directă

1. Adaugă următorul cod înainte de funcția `connectIoTHub`:

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

    Acest cod definește o funcție de callback pe care biblioteca IoT Hub o poate apela atunci când primește o cerere de metodă directă. Metoda solicitată este transmisă în parametrul `method_name`. Această funcție afișează metoda apelată pe portul serial, apoi pornește sau oprește releul în funcție de numele metodei.

    > 💁 Acest lucru ar putea fi implementat și într-o singură cerere de metodă directă, transmițând starea dorită a releului într-un payload care poate fi transmis cu cererea de metodă și disponibil din parametrul `payload`.

1. Adaugă următorul cod la sfârșitul funcției `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Cererile de metodă directă necesită un răspuns, iar răspunsul este în două părți - un răspuns ca text și un cod de returnare. Acest cod va crea un rezultat ca următorul document JSON:

    ```JSON
    {
        "Result": ""
    }
    ```

    Acesta este apoi copiat în parametrul `response`, iar dimensiunea acestui răspuns este setată în parametrul `response_size`. Acest cod returnează apoi `IOTHUB_CLIENT_OK` pentru a arăta că metoda a fost gestionată corect.

1. Configurează funcția de callback adăugând următorul cod la sfârșitul funcției `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funcția `loop` va apela funcția `IoTHubDeviceClient_LL_DoWork` pentru a procesa evenimentele trimise de IoT Hub. Aceasta este apelată doar la fiecare 10 secunde din cauza `delay`, ceea ce înseamnă că metodele directe sunt procesate doar la fiecare 10 secunde. Pentru a face acest lucru mai eficient, întârzierea de 10 secunde poate fi implementată ca multe întârzieri mai scurte, apelând `IoTHubDeviceClient_LL_DoWork` de fiecare dată. Pentru a face acest lucru, adaugă următorul cod deasupra funcției `loop`:

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

    Acest cod va bucla repetat, apelând `IoTHubDeviceClient_LL_DoWork` și întârziind pentru 100ms de fiecare dată. Va face acest lucru de câte ori este necesar pentru a întârzia pentru timpul dat în parametrul `delay_time`. Acest lucru înseamnă că dispozitivul așteaptă cel mult 100ms pentru a procesa cererile de metodă directă.

1. În funcția `loop`, elimină apelul către `IoTHubDeviceClient_LL_DoWork` și înlocuiește apelul `delay(10000)` cu următorul cod pentru a apela această funcție nouă:

    ```cpp
    work_delay(10000);
    ```

> 💁 Poți găsi acest cod în folderul [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Programul senzorului de umiditate a solului este conectat la IoT Hub!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.