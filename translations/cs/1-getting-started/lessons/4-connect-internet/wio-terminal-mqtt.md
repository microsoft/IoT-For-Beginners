<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T22:12:17+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "cs"
}
-->
# Ovládejte svůj noční světlo přes internet - Wio Terminal

IoT zařízení musí být naprogramováno tak, aby komunikovalo s *test.mosquitto.org* pomocí MQTT, odesílalo telemetrické hodnoty na základě čtení světelného senzoru a přijímalo příkazy k ovládání LED.

V této části lekce připojíte svůj Wio Terminal k MQTT brokeru.

## Instalace knihoven WiFi a MQTT pro Arduino

Pro komunikaci s MQTT brokerem je třeba nainstalovat některé knihovny Arduino, které umožní použití WiFi čipu v zařízení Wio Terminal a komunikaci přes MQTT. Při vývoji pro zařízení Arduino můžete využít širokou škálu knihoven, které obsahují open-source kód a implementují mnoho funkcí. Seeed zveřejňuje knihovny pro Wio Terminal, které umožňují komunikaci přes WiFi. Jiní vývojáři zveřejnili knihovny pro komunikaci s MQTT brokery, které budete používat se svým zařízením.

Tyto knihovny jsou poskytovány jako zdrojový kód, který lze automaticky importovat do PlatformIO a zkompilovat pro vaše zařízení. Díky tomu budou knihovny Arduino fungovat na jakémkoli zařízení podporujícím Arduino framework, za předpokladu, že zařízení má potřebný hardware pro danou knihovnu. Některé knihovny, jako například Seeed WiFi knihovny, jsou specifické pro určitý hardware.

Knihovny lze instalovat globálně a kompilovat podle potřeby, nebo do konkrétního projektu. Pro tento úkol budou knihovny instalovány do projektu.

✅ Více o správě knihoven a o tom, jak najít a nainstalovat knihovny, se dozvíte v [dokumentaci PlatformIO ke správě knihoven](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Úkol - instalace knihoven WiFi a MQTT pro Arduino

Nainstalujte knihovny Arduino.

1. Otevřete projekt nočního světla ve VS Code.

1. Přidejte následující na konec souboru `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Tím se importují Seeed WiFi knihovny. Syntaxe `@ <číslo>` odkazuje na konkrétní verzi knihovny.

    > 💁 Můžete odstranit `@ <číslo>` a vždy používat nejnovější verzi knihoven, ale není zaručeno, že novější verze budou fungovat s níže uvedeným kódem. Kód zde byl testován s touto verzí knihoven.

    To je vše, co je třeba udělat pro přidání knihoven. Při příštím sestavení projektu PlatformIO stáhne zdrojový kód těchto knihoven a zkompiluje jej do vašeho projektu.

1. Přidejte následující do `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Tím se importuje [PubSubClient](https://github.com/knolleary/pubsubclient), klient MQTT pro Arduino.

## Připojení k WiFi

Wio Terminal nyní může být připojen k WiFi.

### Úkol - připojení k WiFi

Připojte Wio Terminal k WiFi.

1. Vytvořte nový soubor ve složce `src` s názvem `config.h`. Můžete to udělat tak, že vyberete složku `src` nebo soubor `main.cpp` uvnitř a kliknete na tlačítko **Nový soubor** v průzkumníku. Toto tlačítko se zobrazí pouze tehdy, když je kurzor nad průzkumníkem.

    ![Tlačítko nového souboru](../../../../../translated_images/vscode-new-file-button.182702340fe6723c8cbb4cfa1a9a9fb0d0a5227643b4e46b91ff67b07a39a92f.cs.png)

1. Přidejte následující kód do tohoto souboru pro definování konstant pro vaše WiFi přihlašovací údaje:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Nahraďte `<SSID>` názvem vaší WiFi. Nahraďte `<PASSWORD>` heslem vaší WiFi.

1. Otevřete soubor `main.cpp`.

1. Přidejte následující direktivy `#include` na začátek souboru:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Tím se zahrnou hlavičkové soubory pro knihovny, které jste přidali dříve, stejně jako hlavičkový soubor config. Tyto hlavičkové soubory jsou potřebné k tomu, aby PlatformIO přineslo kód z knihoven. Bez explicitního zahrnutí těchto hlavičkových souborů nebude některý kód zkompilován a dojde k chybám kompilace.

1. Přidejte následující kód nad funkci `setup`:

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

    Tento kód se opakovaně pokouší připojit k WiFi pomocí SSID a hesla z hlavičkového souboru config, dokud není zařízení připojeno.

1. Přidejte volání této funkce na konec funkce `setup`, po konfiguraci pinů.

    ```cpp
    connectWiFi();
    ```

1. Nahrajte tento kód do svého zařízení a zkontrolujte, zda připojení k WiFi funguje. Měli byste to vidět v sériovém monitoru.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Připojení k MQTT

Jakmile je Wio Terminal připojen k WiFi, může se připojit k MQTT brokeru.

### Úkol - připojení k MQTT

Připojte se k MQTT brokeru.

1. Přidejte následující kód na konec souboru `config.h` pro definování přihlašovacích údajů pro připojení k MQTT brokeru:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Nahraďte `<ID>` unikátním ID, které bude použito jako název tohoto klienta zařízení a později pro témata, která toto zařízení publikuje a odebírá. Broker *test.mosquitto.org* je veřejný a používá ho mnoho lidí, včetně dalších studentů pracujících na tomto úkolu. Mít unikátní název MQTT klienta a názvy témat zajistí, že váš kód nebude kolidovat s kódem někoho jiného. Toto ID budete také potřebovat při vytváření serverového kódu později v tomto úkolu.

    > 💁 Můžete použít webovou stránku jako [GUIDGen](https://www.guidgen.com) pro generování unikátního ID.

    `BROKER` je URL MQTT brokeru.

    `CLIENT_NAME` je unikátní název tohoto MQTT klienta na brokeru.

1. Otevřete soubor `main.cpp` a přidejte následující kód pod funkci `connectWiFi` a nad funkci `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Tento kód vytvoří WiFi klienta pomocí knihoven WiFi pro Wio Terminal a použije ho k vytvoření MQTT klienta.

1. Pod tento kód přidejte následující:

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

    Tato funkce testuje připojení k MQTT brokeru a znovu se připojuje, pokud není připojeno. Opakuje se, dokud není připojeno, a pokouší se připojit pomocí unikátního názvu klienta definovaného v hlavičkovém souboru config.

    Pokud připojení selže, znovu se pokusí po 5 sekundách.

1. Přidejte následující kód pod funkci `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Tento kód nastaví MQTT broker pro klienta, stejně jako nastaví zpětné volání při přijetí zprávy. Poté se pokusí připojit k brokeru.

1. Zavolejte funkci `createMQTTClient` ve funkci `setup` po připojení k WiFi.

1. Nahraďte celou funkci `loop` následujícím:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Tento kód začíná znovupřipojením k MQTT brokeru. Tato připojení mohou být snadno přerušena, takže je dobré pravidelně kontrolovat a znovu se připojit, pokud je to nutné. Poté volá metodu `loop` na MQTT klientovi, aby zpracoval všechny zprávy, které přicházejí na téma, na které je přihlášen. Tato aplikace je jedno-vláknová, takže zprávy nemohou být přijímány na pozadí, a proto je třeba na hlavním vlákně vyhradit čas na zpracování všech zpráv čekajících na síťovém připojení.

    Nakonec zpoždění 2 sekundy zajistí, že úrovně světla nejsou odesílány příliš často a snižuje spotřebu energie zařízení.

1. Nahrajte kód do svého Wio Terminal a použijte sériový monitor k zobrazení připojení zařízení k WiFi a MQTT.

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

> 💁 Tento kód najdete ve složce [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Úspěšně jste připojili své zařízení k MQTT brokeru.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.