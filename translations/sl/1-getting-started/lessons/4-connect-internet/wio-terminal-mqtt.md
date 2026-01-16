<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T13:51:19+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "sl"
}
-->
# Nadzorujte svojo nočno lučko prek interneta - Wio Terminal

IoT napravo je treba programirati tako, da komunicira z *test.mosquitto.org* prek MQTT za pošiljanje telemetričnih vrednosti z odčitki svetlobnega senzorja in prejemanje ukazov za nadzor LED.

V tem delu lekcije boste svoj Wio Terminal povezali z MQTT posrednikom.

## Namestite knjižnice WiFi in MQTT za Arduino

Za komunikacijo z MQTT posrednikom morate namestiti nekaj knjižnic za Arduino, ki omogočajo uporabo WiFi čipa v Wio Terminalu in komunikacijo z MQTT. Pri razvoju za Arduino naprave lahko uporabljate širok nabor knjižnic, ki vsebujejo odprtokodno kodo in omogočajo številne funkcionalnosti. Seeed objavlja knjižnice za Wio Terminal, ki omogočajo komunikacijo prek WiFi. Drugi razvijalci so objavili knjižnice za komunikacijo z MQTT posredniki, ki jih boste uporabili z vašo napravo.

Te knjižnice so na voljo kot izvorna koda, ki jo je mogoče samodejno uvoziti v PlatformIO in prevesti za vašo napravo. Na ta način bodo knjižnice Arduino delovale na kateri koli napravi, ki podpira Arduino okvir, pod pogojem, da ima naprava specifično strojno opremo, ki jo knjižnica potrebuje. Nekatere knjižnice, kot so Seeed WiFi knjižnice, so specifične za določeno strojno opremo.

Knjižnice je mogoče namestiti globalno in jih po potrebi prevesti ali pa v določen projekt. Za to nalogo bodo knjižnice nameščene v projekt.

✅ Več o upravljanju knjižnic in kako jih najti ter namestiti lahko izveste v [dokumentaciji knjižničnega upravitelja PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Naloga - namestite knjižnice WiFi in MQTT za Arduino

Namestite knjižnice za Arduino.

1. Odprite projekt nočne lučke v VS Code.

1. Na konec datoteke `platformio.ini` dodajte naslednje:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    To uvozi Seeed WiFi knjižnice. Sintaksa `@ <številka>` se nanaša na določeno različico knjižnice.

    > 💁 Lahko odstranite `@ <številka>`, da vedno uporabljate najnovejšo različico knjižnic, vendar ni zagotovila, da bodo novejše različice delovale s spodnjo kodo. Koda tukaj je bila testirana s to različico knjižnic.

    To je vse, kar morate storiti za dodajanje knjižnic. Naslednjič, ko PlatformIO sestavi projekt, bo prenesel izvorno kodo teh knjižnic in jo vključil v vaš projekt.

1. Dodajte naslednje v `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    To uvozi [PubSubClient](https://github.com/knolleary/pubsubclient), MQTT odjemalca za Arduino.

## Povežite se z WiFi

Zdaj lahko Wio Terminal povežete z WiFi.

### Naloga - povežite se z WiFi

Povežite Wio Terminal z WiFi.

1. Ustvarite novo datoteko v mapi `src` z imenom `config.h`. To lahko storite tako, da izberete mapo `src` ali datoteko `main.cpp` znotraj nje in kliknete gumb **New file** v raziskovalcu. Ta gumb se prikaže le, ko je vaš kazalec nad raziskovalcem.

    ![Gumb za novo datoteko](../../../../../translated_images/sl/vscode-new-file-button.182702340fe6723c.webp)

1. V to datoteko dodajte naslednjo kodo za definiranje konstant za vaše WiFi poverilnice:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Zamenjajte `<SSID>` z imenom vašega WiFi omrežja. Zamenjajte `<PASSWORD>` z geslom vašega WiFi omrežja.

1. Odprite datoteko `main.cpp`.

1. Na vrh datoteke dodajte naslednje `#include` direktive:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    To vključuje glave datotek za knjižnice, ki ste jih prej dodali, kot tudi glavo datoteke za konfiguracijo. Te glave datotek so potrebne, da PlatformIO vključuje kodo iz knjižnic. Brez izrecnega vključevanja teh glave datotek nekatere kode ne bodo prevedene in boste dobili napake pri prevajanju.

1. Nad funkcijo `setup` dodajte naslednjo kodo:

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

    Ta koda se izvaja, dokler naprava ni povezana z WiFi, in poskuša povezavo z uporabo SSID in gesla iz konfiguracijske glave datoteke.

1. Na dno funkcije `setup`, po konfiguraciji pinov, dodajte klic te funkcije.

    ```cpp
    connectWiFi();
    ```

1. Naložite to kodo na vašo napravo, da preverite, ali povezava z WiFi deluje. To bi morali videti v serijskem monitorju.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Povežite se z MQTT

Ko je Wio Terminal povezan z WiFi, se lahko poveže z MQTT posrednikom.

### Naloga - povežite se z MQTT

Povežite se z MQTT posrednikom.

1. Na dno datoteke `config.h` dodajte naslednjo kodo za definiranje podrobnosti povezave z MQTT posrednikom:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Zamenjajte `<ID>` z unikatnim ID-jem, ki bo uporabljen kot ime te naprave odjemalca in kasneje za teme, ki jih ta naprava objavlja in na katere se naroča. Posrednik *test.mosquitto.org* je javen in ga uporablja veliko ljudi, vključno z drugimi študenti, ki delajo na tej nalogi. Unikatno ime MQTT odjemalca in imena tem zagotavljajo, da vaša koda ne bo v konfliktu z drugimi.

    > 💁 Uporabite lahko spletno stran, kot je [GUIDGen](https://www.guidgen.com), za generiranje unikatnega ID-ja.

    `BROKER` je URL MQTT posrednika.

    `CLIENT_NAME` je unikatno ime za tega MQTT odjemalca na posredniku.

1. Odprite datoteko `main.cpp` in pod funkcijo `connectWiFi` ter nad funkcijo `setup` dodajte naslednjo kodo:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Ta koda ustvari WiFi odjemalca z uporabo WiFi knjižnic Wio Terminala in ga uporabi za ustvarjanje MQTT odjemalca.

1. Pod to kodo dodajte naslednje:

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

    Ta funkcija testira povezavo z MQTT posrednikom in se ponovno poveže, če ni povezana. Izvaja se v zanki, dokler ni povezana, in poskuša povezavo z unikatnim imenom odjemalca, definiranega v konfiguracijski glavi datoteke.

    Če povezava ne uspe, poskusi znova po 5 sekundah.

1. Pod funkcijo `reconnectMQTTClient` dodajte naslednjo kodo:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Ta koda nastavi MQTT posrednika za odjemalca, kot tudi nastavitev povratnega klica, ko je prejeto sporočilo. Nato poskuša vzpostaviti povezavo s posrednikom.

1. Pokličite funkcijo `createMQTTClient` v funkciji `setup` po tem, ko je WiFi povezan.

1. Celotno funkcijo `loop` zamenjajte z naslednjo:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Ta koda začne s ponovnim povezovanjem z MQTT posrednikom. Te povezave se lahko zlahka prekinejo, zato je vredno redno preverjati in se po potrebi ponovno povezati. Nato pokliče metodo `loop` na MQTT odjemalcu za obdelavo vseh sporočil, ki prihajajo na temo, na katero je naročen. Ta aplikacija je enonitna, zato sporočil ni mogoče prejeti v ozadju, zato je treba na glavnem niti dodeliti čas za obdelavo vseh sporočil, ki čakajo na omrežni povezavi.

    Na koncu 2-sekundna zamuda zagotavlja, da se ravni svetlobe ne pošiljajo prepogosto in zmanjšuje porabo energije naprave.

1. Naložite kodo na vaš Wio Terminal in uporabite serijski monitor za ogled povezovanja naprave z WiFi in MQTT.

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

> 💁 To kodo lahko najdete v mapi [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Uspešno ste povezali svojo napravo z MQTT posrednikom.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitne nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.