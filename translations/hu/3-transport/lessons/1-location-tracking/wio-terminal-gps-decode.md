<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T21:41:06+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "hu"
}
-->
# GPS adatok dekódolása - Wio Terminal

Ebben a leckében dekódolni fogod a GPS szenzortól a Wio Terminal által olvasott NMEA üzeneteket, és kinyered a szélességi és hosszúsági adatokat.

## GPS adatok dekódolása

Miután a nyers NMEA adatokat beolvastad a soros portból, egy nyílt forráskódú NMEA könyvtár segítségével dekódolhatod azokat.

### Feladat - GPS adatok dekódolása

Programozd be az eszközt, hogy dekódolja a GPS adatokat.

1. Nyisd meg a `gps-sensor` alkalmazás projektet, ha még nincs megnyitva.

1. Adj hozzá egy könyvtárfüggőséget a [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) könyvtárhoz a projekt `platformio.ini` fájljában. Ez a könyvtár tartalmazza az NMEA adatok dekódolásához szükséges kódot.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. A `main.cpp` fájlban adj hozzá egy include direktívát a TinyGPSPlus könyvtárhoz:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. A `Serial3` deklarációja alatt deklarálj egy TinyGPSPlus objektumot az NMEA mondatok feldolgozásához:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Módosítsd a `printGPSData` függvény tartalmát az alábbiakra:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Ez a kód beolvassa a következő karaktert az UART soros portból a `gps` NMEA dekóderbe. Minden karakter után ellenőrzi, hogy a dekóder olvasott-e érvényes mondatot, majd azt is, hogy olvasott-e érvényes helyadatot. Ha a helyadat érvényes, elküldi azt a soros monitorra, valamint megjeleníti a fixáláshoz hozzájáruló műholdak számát.

1. Fordítsd le és töltsd fel a kódot a Wio Terminalra.

1. Feltöltés után a soros monitor segítségével figyelheted a GPS helyadatokat.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Ezt a kódot megtalálod a [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) mappában.

😀 Sikeresen elkészítetted a GPS szenzor programot adatdekódolással!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.