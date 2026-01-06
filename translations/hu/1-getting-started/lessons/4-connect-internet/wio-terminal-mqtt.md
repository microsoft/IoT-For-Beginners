<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T22:11:51+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "hu"
}
-->
# Vezéreld az éjszakai fényedet az interneten keresztül - Wio Terminal

Az IoT eszközt úgy kell programozni, hogy az *test.mosquitto.org* szerverrel kommunikáljon MQTT segítségével, telemetriai értékeket küldjön a fényérzékelő olvasata alapján, és parancsokat fogadjon az LED vezérléséhez.

Ebben a leckében csatlakoztatni fogod a Wio Terminalt egy MQTT brokerhez.

## Telepítsd a WiFi és MQTT Arduino könyvtárakat

Ahhoz, hogy kommunikálni tudj az MQTT brokerrel, néhány Arduino könyvtárat kell telepítened, amelyek lehetővé teszik a Wio Terminal WiFi chipjének használatát és az MQTT kommunikációt. Az Arduino eszközökhöz való fejlesztés során számos nyílt forráskódú könyvtárat használhatsz, amelyek rengeteg funkciót valósítanak meg. A Seeed kiadott könyvtárakat a Wio Terminalhoz, amelyek lehetővé teszik a WiFi kommunikációt. Más fejlesztők közzétettek könyvtárakat az MQTT brokerrel való kommunikációhoz, és ezeket fogod használni az eszközöddel.

Ezek a könyvtárak forráskódként érhetők el, amelyeket automatikusan importálhatsz a PlatformIO-ba, és lefordíthatod az eszközödre. Így az Arduino könyvtárak bármely eszközön működnek, amely támogatja az Arduino keretrendszert, feltéve, hogy az eszköz rendelkezik a könyvtár által igényelt specifikus hardverrel. Néhány könyvtár, például a Seeed WiFi könyvtárak, specifikusak bizonyos hardverekhez.

A könyvtárakat globálisan telepítheted és fordíthatod, ha szükséges, vagy egy adott projektbe. Ebben a feladatban a könyvtárakat a projektbe fogod telepíteni.

✅ További információt a könyvtárkezelésről, valamint arról, hogyan találhatod meg és telepítheted a könyvtárakat, a [PlatformIO könyvtár dokumentációjában](https://docs.platformio.org/en/latest/librarymanager/index.html) találhatsz.

### Feladat - Telepítsd a WiFi és MQTT Arduino könyvtárakat

Telepítsd az Arduino könyvtárakat.

1. Nyisd meg a nightlight projektet a VS Code-ban.

1. Add hozzá a következő sorokat a `platformio.ini` fájl végéhez:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Ez importálja a Seeed WiFi könyvtárakat. Az `@ <number>` szintaxis egy adott verziószámra utal.

    > 💁 Az `@ <number>` eltávolításával mindig a könyvtárak legújabb verzióját használhatod, de nincs garancia arra, hogy a későbbi verziók működni fognak az alábbi kóddal. Az itt található kódot ezzel a könyvtárverzióval tesztelték.

    Ez minden, amit tenned kell a könyvtárak hozzáadásához. A következő alkalommal, amikor a PlatformIO felépíti a projektet, letölti a könyvtárak forráskódját, és beépíti a projektedbe.

1. Add hozzá a következő sorokat a `lib_deps`-hez:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Ez importálja a [PubSubClient](https://github.com/knolleary/pubsubclient) nevű Arduino MQTT klienst.

## Csatlakozás WiFi-hez

A Wio Terminal most már csatlakoztatható a WiFi-hez.

### Feladat - Csatlakozás WiFi-hez

Csatlakoztasd a Wio Terminalt a WiFi-hez.

1. Hozz létre egy új fájlt a `src` mappában `config.h` néven. Ezt úgy teheted meg, hogy kijelölöd a `src` mappát, vagy a benne lévő `main.cpp` fájlt, majd az **Új fájl** gombra kattintasz az explorerben. Ez a gomb csak akkor jelenik meg, ha az egérkurzor az explorer felett van.

    ![Az új fájl gomb](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.hu.png)

1. Add hozzá a következő kódot ehhez a fájlhoz, hogy meghatározd a WiFi hitelesítési adatokat:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Cseréld ki `<SSID>`-t a WiFi SSID-jére. Cseréld ki `<PASSWORD>`-t a WiFi jelszavára.

1. Nyisd meg a `main.cpp` fájlt.

1. Add hozzá a következő `#include` direktívákat a fájl tetejéhez:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Ez tartalmazza a korábban hozzáadott könyvtárak fejlécfájljait, valamint a config fejlécfájlt. Ezek a fejlécfájlok szükségesek ahhoz, hogy a PlatformIO beépítse a könyvtárak kódját. Ha nem adod meg explicit módon ezeket a fejlécfájlokat, bizonyos kódok nem kerülnek be a fordításba, és fordítási hibákat kapsz.

1. Add hozzá a következő kódot a `setup` függvény fölé:

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

    Ez a kód addig ismétel, amíg az eszköz nem csatlakozik a WiFi-hez, és megpróbál csatlakozni az SSID és jelszó használatával, amelyet a config fejlécfájlban definiáltál.

1. Hívd meg ezt a függvényt a `setup` függvény alján, miután a pinek konfigurálva lettek.

    ```cpp
    connectWiFi();
    ```

1. Töltsd fel ezt a kódot az eszközödre, hogy ellenőrizd, működik-e a WiFi kapcsolat. Ezt kell látnod a soros monitoron.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Csatlakozás MQTT-hez

Miután a Wio Terminal csatlakozott a WiFi-hez, csatlakozhat az MQTT brokerhez.

### Feladat - Csatlakozás MQTT-hez

Csatlakoztasd az MQTT brokerhez.

1. Add hozzá a következő kódot a `config.h` fájl aljára, hogy meghatározd az MQTT broker csatlakozási adatait:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Cseréld ki `<ID>`-t egy egyedi azonosítóra, amelyet az eszköz kliens neveként fogsz használni, és később az eszköz által publikált és feliratkozott témák neveként. Az *test.mosquitto.org* broker nyilvános, és sokan használják, beleértve más diákokat is, akik ezt a feladatot végzik. Egy egyedi MQTT kliensnév és témanév biztosítja, hogy a kódod ne ütközzön másokéval. Ezt az azonosítót később a szerver kód létrehozásakor is használni fogod.

    > 💁 Használhatsz olyan weboldalt, mint például a [GUIDGen](https://www.guidgen.com), hogy generálj egy egyedi azonosítót.

    A `BROKER` az MQTT broker URL-je.

    A `CLIENT_NAME` az MQTT kliens egyedi neve a brokeren.

1. Nyisd meg a `main.cpp` fájlt, és add hozzá a következő kódot a `connectWiFi` függvény alá, a `setup` függvény fölé:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Ez a kód létrehoz egy WiFi klienst a Wio Terminal WiFi könyvtárak segítségével, és ezt használja egy MQTT kliens létrehozásához.

1. Ezután add hozzá a következőt:

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

    Ez a függvény teszteli az MQTT brokerhez való kapcsolatot, és újracsatlakozik, ha nem csatlakozott. Addig ismétel, amíg nem csatlakozik, és megpróbál csatlakozni az egyedi kliensnév használatával, amelyet a config fejlécfájlban definiáltál.

    Ha a kapcsolat sikertelen, 5 másodperc múlva újrapróbálkozik.

1. Add hozzá a következő kódot a `reconnectMQTTClient` függvény alá:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Ez a kód beállítja az MQTT broker címét a kliens számára, valamint beállítja a callback függvényt, amely akkor fut, amikor üzenet érkezik. Ezután megpróbál csatlakozni a brokerhez.

1. Hívd meg a `createMQTTClient` függvényt a `setup` függvényben, miután a WiFi csatlakozott.

1. Cseréld ki az egész `loop` függvényt a következőre:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Ez a kód először újracsatlakozik az MQTT brokerhez. Ezek a kapcsolatok könnyen megszakadhatnak, ezért érdemes rendszeresen ellenőrizni és újracsatlakozni, ha szükséges. Ezután meghívja az MQTT kliens `loop` metódusát, hogy feldolgozza azokat az üzeneteket, amelyek a feliratkozott témán érkeznek. Ez az alkalmazás egyszálú, így az üzenetek nem érkezhetnek háttérszálon, ezért időt kell szánni a fő szálon arra, hogy feldolgozza a hálózati kapcsolaton várakozó üzeneteket.

    Végül egy 2 másodperces késleltetés biztosítja, hogy a fényerősség értékek ne legyenek túl gyakran elküldve, és csökkenti az eszköz energiafogyasztását.

1. Töltsd fel a kódot a Wio Terminalra, és használd a soros monitort, hogy lásd, az eszköz csatlakozik-e a WiFi-hez és az MQTT-hez.

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

> 💁 Ezt a kódot megtalálhatod a [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) mappában.

😀 Sikeresen csatlakoztattad az eszközödet egy MQTT brokerhez.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.