<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T21:41:40+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "hu"
}
-->
# GPS-adatok olvasása - Wio Terminal

Ebben a leckében hozzáad egy GPS-érzékelőt a Wio Terminalhoz, és adatokat olvas le róla.

## Hardver

A Wio Terminalhoz szükség van egy GPS-érzékelőre.

Az érzékelő, amit használni fog, a [Grove GPS Air530 érzékelő](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ez az érzékelő több GPS-rendszerhez is tud csatlakozni, hogy gyors és pontos helymeghatározást biztosítson. Az érzékelő két részből áll: az érzékelő alapvető elektronikájából és egy vékony vezetékkel csatlakoztatott külső antennából, amely a műholdak rádióhullámait fogja.

Ez egy UART érzékelő, tehát UART-on keresztül küldi a GPS-adatokat.

### Csatlakoztassa a GPS-érzékelőt

A Grove GPS-érzékelő csatlakoztatható a Wio Terminalhoz.

#### Feladat - csatlakoztassa a GPS-érzékelőt

Csatlakoztassa a GPS-érzékelőt.

![Egy Grove GPS-érzékelő](../../../../../translated_images/hu/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Helyezze be a Grove kábel egyik végét a GPS-érzékelő aljzatába. Csak egyféleképpen illeszkedik.

1. Amikor a Wio Terminal nincs csatlakoztatva a számítógépéhez vagy más áramforráshoz, csatlakoztassa a Grove kábel másik végét a Wio Terminal bal oldali Grove aljzatába, ahogy a képernyőre néz. Ez az aljzat van legközelebb a bekapcsológombhoz.

    ![A Grove GPS-érzékelő csatlakoztatva a bal oldali aljzathoz](../../../../../translated_images/hu/wio-gps-sensor.19fd52b81ce58095.webp)

1. Helyezze el a GPS-érzékelőt úgy, hogy a csatlakoztatott antennának legyen rálátása az égre - ideális esetben egy nyitott ablak mellett vagy a szabadban. Az antenna akadálytalan elhelyezése tisztább jelet biztosít.

1. Most csatlakoztathatja a Wio Terminalt a számítógépéhez.

1. A GPS-érzékelőnek 2 LED-je van - egy kék LED, amely villog, amikor adatokat továbbít, és egy zöld LED, amely másodpercenként villog, amikor adatokat fogad a műholdakról. Győződjön meg róla, hogy a kék LED villog, amikor bekapcsolja a Wio Terminalt. Néhány perc múlva a zöld LED is villogni fog - ha nem, lehet, hogy újra kell pozícionálnia az antennát.

## Programozza a GPS-érzékelőt

Most már programozhatja a Wio Terminalt, hogy használja a csatlakoztatott GPS-érzékelőt.

### Feladat - programozza a GPS-érzékelőt

Programozza az eszközt.

1. Hozzon létre egy teljesen új Wio Terminal projektet a PlatformIO segítségével. Nevezze el ezt a projektet `gps-sensor`-nak. Adjon hozzá kódot a `setup` függvényben a soros port konfigurálásához.

1. Adja hozzá a következő include direktívát a `main.cpp` fájl tetejéhez. Ez tartalmaz egy fejlécfájlt, amely funkciókat biztosít a bal oldali Grove port UART-ra történő konfigurálásához.

    ```cpp
    #include <wiring_private.h>
    ```

1. Ezután adja hozzá az alábbi kódsort, hogy deklaráljon egy soros port kapcsolatot az UART porthoz:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Néhány kódot kell hozzáadnia, hogy bizonyos belső jelkezelőket átirányítson erre a soros portra. Adja hozzá a következő kódot a `Serial3` deklaráció alá:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. A `setup` függvényben, ott, ahol a `Serial` portot konfigurálja, konfigurálja az UART soros portot a következő kóddal:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Ezután a `setup` függvényben adja hozzá a következő kódot, hogy a Grove csatlakozót összekapcsolja a soros porttal:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Adja hozzá a következő függvényt a `loop` függvény elé, hogy a GPS-adatokat elküldje a soros monitorra:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. A `loop` függvényben adja hozzá a következő kódot, hogy olvassa az UART soros portot, és nyomtassa ki a kimenetet a soros monitorra:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Ez a kód az UART soros portról olvas. A `readStringUntil` függvény egy terminátor karakterig olvas, ebben az esetben egy új sorig. Ez egy teljes NMEA mondatot olvas be (az NMEA mondatok új sor karakterrel végződnek). Amíg adat olvasható az UART soros portról, az adatokat beolvassa, és a `printGPSData` függvényen keresztül elküldi a soros monitorra. Ha már nincs több olvasható adat, a `loop` 1 másodpercet (1,000ms) késleltet.

1. Fordítsa le és töltse fel a kódot a Wio Terminalra.

1. Feltöltés után a soros monitor segítségével figyelheti a GPS-adatokat.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Ezt a kódot megtalálja a [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) mappában.

😀 A GPS-érzékelő programja sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.