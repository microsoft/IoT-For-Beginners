<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T10:11:05+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "sk"
}
-->
# Ovládajte svoje nočné svetlo cez internet - Wio Terminal

IoT zariadenie musí byť naprogramované tak, aby komunikovalo s *test.mosquitto.org* pomocou MQTT na odosielanie telemetrických hodnôt zo snímača svetla a prijímanie príkazov na ovládanie LED.

V tejto časti lekcie pripojíte svoj Wio Terminal k MQTT brokeru.

## Nainštalujte WiFi a MQTT knižnice pre Arduino

Na komunikáciu s MQTT brokerom je potrebné nainštalovať niektoré Arduino knižnice, ktoré umožnia používať WiFi čip vo Wio Terminal a komunikovať cez MQTT. Pri vývoji pre Arduino zariadenia môžete využiť širokú škálu knižníc, ktoré obsahujú open-source kód a implementujú množstvo funkcií. Seeed poskytuje knižnice pre Wio Terminal, ktoré umožňujú komunikáciu cez WiFi. Iní vývojári zverejnili knižnice na komunikáciu s MQTT brokermi, ktoré budete používať so svojím zariadením.

Tieto knižnice sú poskytované ako zdrojový kód, ktorý môže byť automaticky importovaný do PlatformIO a skompilovaný pre vaše zariadenie. Týmto spôsobom budú Arduino knižnice fungovať na akomkoľvek zariadení, ktoré podporuje Arduino framework, za predpokladu, že zariadenie má potrebný hardvér pre danú knižnicu. Niektoré knižnice, ako napríklad Seeed WiFi knižnice, sú špecifické pre určitý hardvér.

Knižnice môžu byť nainštalované globálne a skompilované podľa potreby, alebo pre konkrétny projekt. Pre túto úlohu budú knižnice nainštalované do projektu.

✅ Viac o správe knižníc a o tom, ako ich nájsť a nainštalovať, sa môžete dozvedieť v [dokumentácii PlatformIO o knižniciach](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Úloha - nainštalujte WiFi a MQTT knižnice pre Arduino

Nainštalujte Arduino knižnice.

1. Otvorte projekt nočného svetla vo VS Code.

1. Pridajte nasledujúci kód na koniec súboru `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Týmto sa importujú Seeed WiFi knižnice. Syntax `@ <číslo>` odkazuje na konkrétnu verziu knižnice.

    > 💁 Môžete odstrániť `@ <číslo>`, aby ste vždy používali najnovšiu verziu knižníc, ale nie je zaručené, že novšie verzie budú fungovať s kódom nižšie. Kód tu bol testovaný s touto verziou knižníc.

    Toto je všetko, čo musíte urobiť na pridanie knižníc. Pri ďalšom zostavení projektu PlatformIO stiahne zdrojový kód týchto knižníc a skompiluje ho do vášho projektu.

1. Pridajte nasledujúci kód do `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Týmto sa importuje [PubSubClient](https://github.com/knolleary/pubsubclient), MQTT klient pre Arduino.

## Pripojenie k WiFi

Wio Terminal teraz môže byť pripojený k WiFi.

### Úloha - pripojenie k WiFi

Pripojte Wio Terminal k WiFi.

1. Vytvorte nový súbor v priečinku `src` s názvom `config.h`. Môžete to urobiť tak, že vyberiete priečinok `src` alebo súbor `main.cpp` vo vnútri a kliknete na tlačidlo **New file** v prieskumníku. Toto tlačidlo sa zobrazí iba vtedy, keď je kurzor nad prieskumníkom.

    ![Tlačidlo na vytvorenie nového súboru](../../../../../translated_images/sk/vscode-new-file-button.182702340fe6723c.png)

1. Pridajte nasledujúci kód do tohto súboru na definovanie konštánt pre vaše WiFi prihlasovacie údaje:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Nahraďte `<SSID>` názvom vašej WiFi siete. Nahraďte `<PASSWORD>` heslom vašej WiFi siete.

1. Otvorte súbor `main.cpp`.

1. Pridajte nasledujúce `#include` direktívy na začiatok súboru:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Týmto sa zahrnú hlavičkové súbory pre knižnice, ktoré ste pridali skôr, ako aj hlavičkový súbor config. Tieto hlavičkové súbory sú potrebné na to, aby PlatformIO zahrnulo kód z knižníc. Bez explicitného zahrnutia týchto hlavičkových súborov nebude niektorý kód skompilovaný a dostanete chyby kompilátora.

1. Pridajte nasledujúci kód nad funkciu `setup`:

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

    Tento kód sa opakovane pokúša pripojiť zariadenie k WiFi, kým nie je pripojené, a používa SSID a heslo zo súboru config.

1. Zavolajte túto funkciu na konci funkcie `setup`, po nakonfigurovaní pinov.

    ```cpp
    connectWiFi();
    ```

1. Nahrajte tento kód do svojho zariadenia, aby ste overili, že pripojenie k WiFi funguje. V sériovom monitore by ste mali vidieť toto:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Pripojenie k MQTT

Keď je Wio Terminal pripojený k WiFi, môže sa pripojiť k MQTT brokeru.

### Úloha - pripojenie k MQTT

Pripojte sa k MQTT brokeru.

1. Pridajte nasledujúci kód na koniec súboru `config.h`, aby ste definovali údaje o pripojení k MQTT brokeru:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Nahraďte `<ID>` jedinečným ID, ktoré bude použité ako názov tohto zariadenia klienta a neskôr pre témy, ktoré toto zariadenie publikuje a odoberá. Broker *test.mosquitto.org* je verejný a používa ho mnoho ľudí, vrátane iných študentov pracujúcich na tejto úlohe. Použitie jedinečného názvu MQTT klienta a názvov tém zabezpečí, že váš kód nebude kolidovať s kódom niekoho iného. Toto ID budete potrebovať aj pri vytváraní serverového kódu neskôr v tejto úlohe.

    > 💁 Môžete použiť webovú stránku ako [GUIDGen](https://www.guidgen.com) na generovanie jedinečného ID.

    `BROKER` je URL adresa MQTT brokeru.

    `CLIENT_NAME` je jedinečný názov tohto MQTT klienta na brokeri.

1. Otvorte súbor `main.cpp` a pridajte nasledujúci kód pod funkciu `connectWiFi` a nad funkciu `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Tento kód vytvára WiFi klienta pomocou WiFi knižníc Wio Terminal a používa ho na vytvorenie MQTT klienta.

1. Pod tento kód pridajte nasledujúci kód:

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

    Táto funkcia testuje pripojenie k MQTT brokeru a znovu sa pripojí, ak nie je pripojené. Opakovane sa pokúša pripojiť pomocou jedinečného názvu klienta definovaného v hlavičkovom súbore config.

    Ak pripojenie zlyhá, pokúsi sa znova po 5 sekundách.

1. Pridajte nasledujúci kód pod funkciu `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Tento kód nastaví MQTT broker pre klienta, ako aj nastaví spätné volanie pri prijatí správy. Potom sa pokúsi pripojiť k brokeru.

1. Zavolajte funkciu `createMQTTClient` vo funkcii `setup` po pripojení k WiFi.

1. Nahraďte celú funkciu `loop` nasledujúcim kódom:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Tento kód začína opätovným pripojením k MQTT brokeru. Tieto pripojenia môžu byť ľahko prerušené, takže je dobré pravidelne kontrolovať a znovu sa pripojiť, ak je to potrebné. Potom zavolá metódu `loop` na MQTT klientovi, aby spracoval akékoľvek správy, ktoré prichádzajú na odoberanú tému. Táto aplikácia je jednovláknová, takže správy nemôžu byť prijímané na pozadí, preto je potrebné prideliť čas na hlavnom vlákne na spracovanie čakajúcich správ na sieťovom pripojení.

    Nakoniec, oneskorenie 2 sekundy zabezpečí, že úrovne svetla nebudú odosielané príliš často a zníži sa spotreba energie zariadenia.

1. Nahrajte kód do svojho Wio Terminal a použite sériový monitor na sledovanie pripojenia zariadenia k WiFi a MQTT.

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

> 💁 Tento kód nájdete v priečinku [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Úspešne ste pripojili svoje zariadenie k MQTT brokeru.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.