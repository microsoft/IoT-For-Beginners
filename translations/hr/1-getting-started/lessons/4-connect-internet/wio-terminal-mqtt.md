<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T13:50:46+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "hr"
}
-->
# Kontrolirajte svoju noćnu lampu putem Interneta - Wio Terminal

IoT uređaj treba biti programiran da komunicira s *test.mosquitto.org* koristeći MQTT za slanje telemetrijskih vrijednosti očitanja senzora svjetla i primanje naredbi za upravljanje LED-om.

U ovom dijelu lekcije povezat ćete svoj Wio Terminal s MQTT brokerom.

## Instalirajte WiFi i MQTT Arduino biblioteke

Kako biste komunicirali s MQTT brokerom, potrebno je instalirati neke Arduino biblioteke za korištenje WiFi čipa u Wio Terminalu i komunikaciju putem MQTT-a. Kada razvijate za Arduino uređaje, možete koristiti širok raspon biblioteka koje sadrže otvoreni kod i implementiraju veliki broj funkcionalnosti. Seeed objavljuje biblioteke za Wio Terminal koje omogućuju komunikaciju putem WiFi-a. Ostali programeri objavili su biblioteke za komunikaciju s MQTT brokerima, a vi ćete koristiti te biblioteke sa svojim uređajem.

Ove biblioteke dostupne su kao izvorni kod koji se može automatski uvesti u PlatformIO i kompajlirati za vaš uređaj. Na taj način Arduino biblioteke će raditi na bilo kojem uređaju koji podržava Arduino framework, pod uvjetom da uređaj ima specifični hardver potreban za tu biblioteku. Neke biblioteke, poput Seeed WiFi biblioteka, specifične su za određeni hardver.

Biblioteke se mogu instalirati globalno i kompajlirati po potrebi, ili unutar specifičnog projekta. Za ovaj zadatak, biblioteke će biti instalirane unutar projekta.

✅ Više o upravljanju bibliotekama i kako pronaći i instalirati biblioteke možete saznati u [PlatformIO dokumentaciji o bibliotekama](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Zadatak - instalirajte WiFi i MQTT Arduino biblioteke

Instalirajte Arduino biblioteke.

1. Otvorite projekt noćne lampe u VS Code-u.

1. Dodajte sljedeće na kraj datoteke `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Ovo uvozi Seeed WiFi biblioteke. Sintaksa `@ <broj>` odnosi se na specifičnu verziju biblioteke.

    > 💁 Možete ukloniti `@ <broj>` kako biste uvijek koristili najnoviju verziju biblioteka, ali nema jamstva da će novije verzije raditi s kodom u nastavku. Kod ovdje je testiran s ovom verzijom biblioteka.

    Ovo je sve što trebate učiniti da biste dodali biblioteke. Sljedeći put kada PlatformIO kompajlira projekt, preuzet će izvorni kod za ove biblioteke i kompajlirati ga u vaš projekt.

1. Dodajte sljedeće u `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Ovo uvozi [PubSubClient](https://github.com/knolleary/pubsubclient), Arduino MQTT klijent.

## Povežite se na WiFi

Wio Terminal sada se može povezati na WiFi.

### Zadatak - povežite se na WiFi

Povežite Wio Terminal na WiFi.

1. Kreirajte novu datoteku u mapi `src` pod nazivom `config.h`. To možete učiniti odabirom mape `src` ili datoteke `main.cpp` unutar nje, te odabirom gumba **New file** u exploreru. Ovaj gumb se pojavljuje samo kada je vaš kursor iznad explorera.

    ![Gumb za novu datoteku](../../../../../translated_images/hr/vscode-new-file-button.182702340fe6723c.webp)

1. Dodajte sljedeći kod u ovu datoteku kako biste definirali konstante za vaše WiFi vjerodajnice:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Zamijenite `<SSID>` s SSID-om vašeg WiFi-a. Zamijenite `<PASSWORD>` s vašom WiFi lozinkom.

1. Otvorite datoteku `main.cpp`.

1. Dodajte sljedeće `#include` direktive na vrh datoteke:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Ovo uključuje zaglavne datoteke za biblioteke koje ste ranije dodali, kao i zaglavnu datoteku konfiguracije. Ove zaglavne datoteke su potrebne kako bi PlatformIO uključio kod iz biblioteka. Bez eksplicitnog uključivanja ovih zaglavnih datoteka, neki kod neće biti kompajliran i dobit ćete greške pri kompajliranju.

1. Dodajte sljedeći kod iznad funkcije `setup`:

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

    Ovaj kod se ponavlja dok uređaj nije povezan na WiFi i pokušava se povezati koristeći SSID i lozinku iz zaglavne datoteke konfiguracije.

1. Dodajte poziv ovoj funkciji na dnu funkcije `setup`, nakon što su pinovi konfigurirani.

    ```cpp
    connectWiFi();
    ```

1. Prenesite ovaj kod na svoj uređaj kako biste provjerili radi li WiFi veza. Trebali biste vidjeti ovo u serijskom monitoru.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Povežite se na MQTT

Nakon što je Wio Terminal povezan na WiFi, može se povezati na MQTT broker.

### Zadatak - povežite se na MQTT

Povežite se na MQTT broker.

1. Dodajte sljedeći kod na dno datoteke `config.h` kako biste definirali detalje veze za MQTT broker:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Zamijenite `<ID>` s jedinstvenim ID-om koji će se koristiti kao ime ovog klijenta uređaja, a kasnije i za teme koje ovaj uređaj objavljuje i na koje se pretplaćuje. Broker *test.mosquitto.org* je javni i koristi ga mnogo ljudi, uključujući druge studente koji rade na ovom zadatku. Imati jedinstveno ime MQTT klijenta i nazive tema osigurava da vaš kod neće biti u sukobu s kodom drugih korisnika. Također ćete trebati ovaj ID kada kasnije budete kreirali kod za server.

    > 💁 Možete koristiti web stranicu poput [GUIDGen](https://www.guidgen.com) za generiranje jedinstvenog ID-a.

    `BROKER` je URL MQTT brokera.

    `CLIENT_NAME` je jedinstveno ime za ovaj MQTT klijent na brokeru.

1. Otvorite datoteku `main.cpp` i dodajte sljedeći kod ispod funkcije `connectWiFi` i iznad funkcije `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Ovaj kod kreira WiFi klijent koristeći Seeed WiFi biblioteke i koristi ga za kreiranje MQTT klijenta.

1. Ispod ovog koda dodajte sljedeće:

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

    Ova funkcija testira vezu s MQTT brokerom i ponovno se povezuje ako nije povezan. Ponavlja se sve dok nije povezan i pokušava se povezati koristeći jedinstveno ime klijenta definirano u zaglavnoj datoteci konfiguracije.

    Ako veza ne uspije, ponovno pokušava nakon 5 sekundi.

1. Dodajte sljedeći kod ispod funkcije `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Ovaj kod postavlja MQTT broker za klijenta, kao i postavlja povratni poziv kada se primi poruka. Zatim pokušava povezati se s brokerom.

1. Pozovite funkciju `createMQTTClient` u funkciji `setup` nakon što je WiFi povezan.

1. Zamijenite cijelu funkciju `loop` sljedećim kodom:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Ovaj kod započinje ponovnim povezivanjem na MQTT broker. Ove veze se lako prekidaju, pa je vrijedno redovito provjeravati i ponovno se povezati ako je potrebno. Zatim poziva metodu `loop` na MQTT klijentu kako bi obradio sve poruke koje dolaze na temu na koju je pretplaćen. Ova aplikacija je jedno-threaded, pa se poruke ne mogu primati u pozadinskom threadu, stoga je potrebno dodijeliti vrijeme na glavnom threadu za obradu poruka koje čekaju na mrežnoj vezi.

    Na kraju, kašnjenje od 2 sekunde osigurava da se razine svjetlosti ne šalju prečesto i smanjuje potrošnju energije uređaja.

1. Prenesite kod na svoj Wio Terminal i koristite Serijski Monitor kako biste vidjeli uređaj kako se povezuje na WiFi i MQTT.

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

> 💁 Ovaj kod možete pronaći u mapi [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Uspješno ste povezali svoj uređaj s MQTT brokerom.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden korištenjem AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.