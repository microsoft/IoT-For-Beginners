# Hőmérséklet mérése - Wio Terminal

Ebben a leckében hozzáadunk egy hőmérséklet-érzékelőt a Wio Terminalhoz, és kiolvassuk belőle a hőmérsékleti értékeket.

## Hardver

A Wio Terminalhoz szükség van egy hőmérséklet-érzékelőre.

Az érzékelő, amit használni fogsz, egy [DHT11 páratartalom- és hőmérséklet-érzékelő](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), amely két érzékelőt kombinál egy csomagban. Ez egy meglehetősen népszerű érzékelő, és számos kereskedelmi forgalomban kapható változata létezik, amelyek hőmérsékletet, páratartalmat és néha légnyomást is mérnek. A hőmérséklet-érzékelő komponens egy negatív hőmérsékleti együtthatójú (NTC) termisztor, amelynek ellenállása csökken, ahogy a hőmérséklet nő.

Ez egy digitális érzékelő, amely beépített ADC-vel rendelkezik, hogy digitális jelet hozzon létre, amely tartalmazza a hőmérséklet- és páratartalom-adatokat, amelyeket a mikrokontroller ki tud olvasni.

### Csatlakoztasd a hőmérséklet-érzékelőt

A Grove hőmérséklet-érzékelő csatlakoztatható a Wio Terminal digitális portjához.

#### Feladat - csatlakoztasd a hőmérséklet-érzékelőt

Csatlakoztasd a hőmérséklet-érzékelőt.

![Egy Grove hőmérséklet-érzékelő](../../../../../translated_images/hu/grove-dht11.07f8eafceee17004.webp)

1. Illeszd be a Grove kábel egyik végét a páratartalom- és hőmérséklet-érzékelő aljzatába. Csak egyféleképpen illeszkedik.

1. Miután a Wio Terminal nincs csatlakoztatva a számítógéphez vagy más áramforráshoz, csatlakoztasd a Grove kábel másik végét a Wio Terminal jobb oldali Grove aljzatába, ahogy a képernyőre nézel. Ez az aljzat van a legtávolabb a bekapcsológombtól.

![A Grove hőmérséklet-érzékelő csatlakoztatva a jobb oldali aljzathoz](../../../../../translated_images/hu/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programozd a hőmérséklet-érzékelőt

Most programozhatod a Wio Terminalt, hogy használja a csatlakoztatott hőmérséklet-érzékelőt.

### Feladat - programozd a hőmérséklet-érzékelőt

Programozd az eszközt.

1. Hozz létre egy teljesen új Wio Terminal projektet a PlatformIO segítségével. Nevezd el ezt a projektet `temperature-sensor`-nak. Adj hozzá kódot a `setup` függvényben a soros port konfigurálásához.

    > ⚠️ Hivatkozhatsz [az 1. projekt, 1. lecke PlatformIO projekt létrehozására vonatkozó utasításaira, ha szükséges](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Adj hozzá egy könyvtárfüggőséget a Seeed Grove páratartalom- és hőmérséklet-érzékelő könyvtárhoz a projekt `platformio.ini` fájljában:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Hivatkozhatsz [az 1. projekt, 4. lecke PlatformIO projekthez könyvtárak hozzáadására vonatkozó utasításaira, ha szükséges](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Add hozzá a következő `#include` direktívákat a fájl tetejére, a meglévő `#include <Arduino.h>` alá:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Ez importálja az érzékelővel való interakcióhoz szükséges fájlokat. A `DHT.h` fejlécfájl tartalmazza az érzékelőhöz szükséges kódot, és a `SPI.h` fejléc hozzáadása biztosítja, hogy az érzékelővel való kommunikációhoz szükséges kód is bekerüljön a fordítás során.

1. A `setup` függvény előtt deklaráld a DHT érzékelőt:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Ez deklarál egy példányt a `DHT` osztályból, amely kezeli a **D**igitális **H**umidity és **T**emperature érzékelőt. Ez a `D0` porthoz van csatlakoztatva, amely a Wio Terminal jobb oldali Grove aljzata. A második paraméter megadja, hogy a használt érzékelő a *DHT11* típusú - a használt könyvtár más változatokat is támogat.

1. A `setup` függvényben adj hozzá kódot a soros kapcsolat beállításához:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. A `setup` függvény végén, az utolsó `delay` után, add hozzá a DHT érzékelő indítására vonatkozó hívást:

    ```cpp
    dht.begin();
    ```

1. A `loop` függvényben adj hozzá kódot az érzékelő hívásához és a hőmérséklet soros portra történő kiírásához:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Ez a kód deklarál egy üres tömböt 2 lebegőpontos számmal, és ezt adja át a `readTempAndHumidity` hívásnak a `DHT` példányon. Ez a hívás feltölti a tömböt 2 értékkel - a páratartalom a tömb 0. elemébe kerül (ne feledd, hogy a C++ tömbök 0-alapúak, tehát a 0. elem az első elem), a hőmérséklet pedig az 1. elembe.

    A hőmérséklet az 1. elemből kerül kiolvasásra, és kiírásra kerül a soros portra.

    > 🇺🇸 A hőmérséklet Celsiusban kerül kiolvasásra. Az amerikaiak számára, ha ezt Fahrenheitre szeretnéd átváltani, oszd el a Celsius értéket 5-tel, majd szorozd meg 9-cel, és adj hozzá 32-t. Például egy 20°C-os hőmérséklet ((20/5)*9) + 32 = 68°F lesz.

1. Fordítsd le és töltsd fel a kódot a Wio Terminalra.

    > ⚠️ Hivatkozhatsz [az 1. projekt, 1. lecke PlatformIO projekt létrehozására vonatkozó utasításaira, ha szükséges](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Feltöltés után a soros monitor segítségével figyelheted a hőmérsékletet:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Ezt a kódot megtalálod a [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) mappában.

😀 Sikeresen elkészült a hőmérséklet-érzékelő programod!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.