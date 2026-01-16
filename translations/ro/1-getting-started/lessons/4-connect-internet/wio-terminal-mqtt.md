<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T10:11:40+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "ro"
}
-->
# Controlează-ți lampa de veghe prin Internet - Wio Terminal

Dispozitivul IoT trebuie programat pentru a comunica cu *test.mosquitto.org* folosind MQTT, pentru a trimite valori de telemetrie cu citirea senzorului de lumină și pentru a primi comenzi pentru a controla LED-ul.

În această parte a lecției, vei conecta Wio Terminal la un broker MQTT.

## Instalează bibliotecile Arduino pentru WiFi și MQTT

Pentru a comunica cu brokerul MQTT, trebuie să instalezi câteva biblioteci Arduino pentru a utiliza cipul WiFi din Wio Terminal și pentru a comunica cu MQTT. Când dezvolți pentru dispozitive Arduino, poți folosi o gamă largă de biblioteci care conțin cod open-source și implementează o varietate mare de funcționalități. Seeed publică biblioteci pentru Wio Terminal care îi permit să comunice prin WiFi. Alți dezvoltatori au publicat biblioteci pentru a comunica cu brokerii MQTT, iar tu vei folosi aceste biblioteci cu dispozitivul tău.

Aceste biblioteci sunt furnizate ca cod sursă care poate fi importat automat în PlatformIO și compilat pentru dispozitivul tău. Astfel, bibliotecile Arduino vor funcționa pe orice dispozitiv care suportă framework-ul Arduino, presupunând că dispozitivul are hardware-ul specific necesar pentru acea bibliotecă. Unele biblioteci, cum ar fi bibliotecile Seeed WiFi, sunt specifice anumitor hardware-uri.

Bibliotecile pot fi instalate global și compilate dacă este necesar sau într-un proiect specific. Pentru această sarcină, bibliotecile vor fi instalate în proiect.

✅ Poți afla mai multe despre gestionarea bibliotecilor și cum să găsești și să instalezi biblioteci în [documentația PlatformIO pentru biblioteci](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Sarcină - instalează bibliotecile Arduino pentru WiFi și MQTT

Instalează bibliotecile Arduino.

1. Deschide proiectul nightlight în VS Code.

1. Adaugă următoarele la sfârșitul fișierului `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Aceasta importă bibliotecile Seeed WiFi. Sintaxa `@ <number>` se referă la o versiune specifică a bibliotecii.

    > 💁 Poți elimina `@ <number>` pentru a folosi mereu cea mai recentă versiune a bibliotecilor, dar nu există garanții că versiunile ulterioare vor funcționa cu codul de mai jos. Codul de aici a fost testat cu această versiune a bibliotecilor.

    Acesta este tot ce trebuie să faci pentru a adăuga bibliotecile. Data viitoare când PlatformIO construiește proiectul, va descărca codul sursă pentru aceste biblioteci și îl va compila în proiectul tău.

1. Adaugă următoarele la `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Aceasta importă [PubSubClient](https://github.com/knolleary/pubsubclient), un client MQTT pentru Arduino.

## Conectează-te la WiFi

Acum, Wio Terminal poate fi conectat la WiFi.

### Sarcină - conectează-te la WiFi

Conectează Wio Terminal la WiFi.

1. Creează un fișier nou în folderul `src` numit `config.h`. Poți face acest lucru selectând folderul `src` sau fișierul `main.cpp` din interior și selectând butonul **New file** din explorer. Acest buton apare doar când cursorul tău este deasupra explorer-ului.

    ![Butonul pentru fișier nou](../../../../../translated_images/ro/vscode-new-file-button.182702340fe6723c.webp)

1. Adaugă următorul cod în acest fișier pentru a defini constantele pentru credențialele WiFi:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Înlocuiește `<SSID>` cu SSID-ul rețelei tale WiFi. Înlocuiește `<PASSWORD>` cu parola rețelei tale WiFi.

1. Deschide fișierul `main.cpp`.

1. Adaugă următoarele directive `#include` în partea de sus a fișierului:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Acestea includ fișierele header pentru bibliotecile adăugate anterior, precum și fișierul header de configurare. Aceste fișiere header sunt necesare pentru a spune PlatformIO să includă codul din biblioteci. Fără includerea explicită a acestor fișiere header, o parte din cod nu va fi compilată și vei primi erori de compilare.

1. Adaugă următorul cod deasupra funcției `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Acest cod rulează în buclă cât timp dispozitivul nu este conectat la WiFi și încearcă să se conecteze folosind SSID-ul și parola din fișierul header de configurare.

1. Adaugă un apel la această funcție la sfârșitul funcției `setup`, după ce pinii au fost configurați.

    ```cpp
    connectWiFi();
    ```

1. Încarcă acest cod pe dispozitivul tău pentru a verifica dacă conexiunea WiFi funcționează. Ar trebui să vezi acest lucru în monitorul serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Conectează-te la MQTT

După ce Wio Terminal este conectat la WiFi, poate fi conectat la brokerul MQTT.

### Sarcină - conectează-te la MQTT

Conectează-te la brokerul MQTT.

1. Adaugă următorul cod la sfârșitul fișierului `config.h` pentru a defini detaliile conexiunii pentru brokerul MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Înlocuiește `<ID>` cu un ID unic care va fi folosit ca nume al acestui client de dispozitiv și mai târziu pentru subiectele pe care acest dispozitiv le publică și la care se abonează. Brokerul *test.mosquitto.org* este public și folosit de mulți oameni, inclusiv alți studenți care lucrează la această sarcină. Având un nume unic pentru clientul MQTT și subiecte unice asigură că codul tău nu va intra în conflict cu al altcuiva. Vei avea nevoie de acest ID și când creezi codul serverului mai târziu în această sarcină.

    > 💁 Poți folosi un site precum [GUIDGen](https://www.guidgen.com) pentru a genera un ID unic.

    `BROKER` este URL-ul brokerului MQTT.

    `CLIENT_NAME` este un nume unic pentru acest client MQTT pe broker.

1. Deschide fișierul `main.cpp` și adaugă următorul cod sub funcția `connectWiFi` și deasupra funcției `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Acest cod creează un client WiFi folosind bibliotecile WiFi ale Wio Terminal și îl folosește pentru a crea un client MQTT.

1. Sub acest cod, adaugă următorul cod:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Această funcție testează conexiunea la brokerul MQTT și se reconectează dacă nu este conectat. Rulează în buclă cât timp nu este conectat și încearcă să se conecteze folosind numele unic al clientului definit în fișierul header de configurare.

    Dacă conexiunea eșuează, încearcă din nou după 5 secunde.

1. Adaugă următorul cod sub funcția `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Acest cod setează brokerul MQTT pentru client, precum și configurarea callback-ului pentru momentul în care un mesaj este primit. Apoi încearcă să se conecteze la broker.

1. Apelează funcția `createMQTTClient` în funcția `setup` după ce conexiunea WiFi este stabilită.

1. Înlocuiește întreaga funcție `loop` cu următorul cod:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Acest cod începe prin a reconecta la brokerul MQTT. Aceste conexiuni pot fi ușor întrerupte, așa că merită să verifici și să reconectezi dacă este necesar. Apoi apelează metoda `loop` pe clientul MQTT pentru a procesa orice mesaje care vin pe subiectul la care s-a abonat. Această aplicație este single-threaded, așa că mesajele nu pot fi primite pe un thread de fundal, prin urmare este necesar să aloci timp pe thread-ul principal pentru a procesa orice mesaje care așteaptă pe conexiunea de rețea.

    În final, o întârziere de 2 secunde asigură că nivelurile de lumină nu sunt trimise prea des și reduce consumul de energie al dispozitivului.

1. Încarcă codul pe Wio Terminal și folosește Monitorul Serial pentru a vedea dispozitivul conectându-se la WiFi și MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Poți găsi acest cod în folderul [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Ai conectat cu succes dispozitivul tău la un broker MQTT.

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.