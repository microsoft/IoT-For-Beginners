# Építs egy éjjeli fényt - Wio Terminal

Ebben a leckében hozzáadsz egy LED-et a Wio Terminalhoz, és éjjeli fényt készítesz belőle.

## Hardver

Az éjjeli fényhez most egy működtetőre van szükség.

A működtető egy **LED**, egy [fénykibocsátó dióda](https://wikipedia.org/wiki/Light-emitting_diode), amely fényt bocsát ki, amikor áram folyik rajta keresztül. Ez egy digitális működtető, amelynek két állapota van: be és ki. Az 1-es érték bekapcsolja a LED-et, a 0 pedig kikapcsolja. Ez egy külső Grove működtető, amelyet csatlakoztatni kell a Wio Terminalhoz.

Az éjjeli fény logikája pszeudokódban:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Csatlakoztasd a LED-et

A Grove LED egy modul formájában érkezik, amely több LED-et tartalmaz, így kiválaszthatod a színt.

#### Feladat - csatlakoztasd a LED-et

Csatlakoztasd a LED-et.

![Egy Grove LED](../../../../../translated_images/hu/grove-led.6c853be93f473cf2.webp)

1. Válaszd ki a kedvenc LED-edet, és helyezd be a lábait a LED modul két lyukába.

    A LED-ek fénykibocsátó diódák, és a diódák olyan elektronikai eszközök, amelyek csak egy irányban tudnak áramot vezetni. Ez azt jelenti, hogy a LED-et megfelelő irányban kell csatlakoztatni, különben nem fog működni.

    A LED egyik lába a pozitív csatlakozó, a másik a negatív. A LED nem teljesen kerek, az egyik oldala kissé laposabb. A kissé laposabb oldal a negatív csatlakozó. Amikor csatlakoztatod a LED-et a modulhoz, győződj meg róla, hogy a kerekebb oldal melletti láb a modul külső részén található **+** jelzésű aljzathoz van csatlakoztatva, míg a laposabb oldal a modul középső részéhez közelebb eső aljzathoz.

1. A LED modulon van egy forgatható gomb, amely lehetővé teszi a fényerő szabályozását. Kezdetben tekerd teljesen fel, az óramutató járásával ellentétes irányba forgatva, ameddig csak lehet, egy kis csillagcsavarhúzóval.

1. Helyezd be a Grove kábel egyik végét a LED modul aljzatába. Csak egy irányban illeszkedik.

1. Miután a Wio Terminal nincs csatlakoztatva a számítógéphez vagy más áramforráshoz, csatlakoztasd a Grove kábel másik végét a Wio Terminal jobb oldali Grove aljzatába, miközben a képernyőt nézed. Ez az aljzat van a legtávolabb a bekapcsoló gombtól.

    > 💁 A jobb oldali Grove aljzat analóg vagy digitális érzékelőkkel és működtetőkkel használható. A bal oldali aljzat csak digitális érzékelőkkel és működtetőkkel használható.

![A Grove LED csatlakoztatva a jobb oldali aljzathoz](../../../../../translated_images/hu/wio-led.265a1897e72d7f21.webp)

## Programozd az éjjeli fényt

Az éjjeli fényt most már programozhatod a beépített fényérzékelő és a Grove LED segítségével.

### Feladat - programozd az éjjeli fényt

Programozd az éjjeli fényt.

1. Nyisd meg az éjjeli fény projektet a VS Code-ban, amelyet a feladat előző részében hoztál létre.

1. Add hozzá a következő sort a `setup` függvény aljára:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Ez a sor konfigurálja a LED-del való kommunikációhoz használt csatlakozót a Grove porton keresztül.

    A `D0` csatlakozó a jobb oldali Grove aljzat digitális csatlakozója. Ez a csatlakozó `OUTPUT` állapotba van állítva, ami azt jelenti, hogy egy működtetőhöz csatlakozik, és adatokat fog írni a csatlakozóra.

1. Add hozzá a következő kódot közvetlenül a `delay` előtt a loop függvényben:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Ez a kód ellenőrzi a `light` értéket. Ha ez kisebb, mint 300, akkor `HIGH` értéket küld a `D0` digitális csatlakozóra. Ez a `HIGH` érték 1-es érték, amely bekapcsolja a LED-et. Ha a fény nagyobb vagy egyenlő 300-zal, akkor `LOW` értéket küld a csatlakozóra, amely kikapcsolja a LED-et.

    > 💁 Digitális értékek küldésekor a működtetőknek a LOW érték 0V, a HIGH érték pedig az eszköz maximális feszültsége. A Wio Terminal esetében a HIGH feszültség 3.3V.

1. Csatlakoztasd újra a Wio Terminalt a számítógéphez, és töltsd fel az új kódot, ahogy korábban tetted.

1. Csatlakoztasd a Serial Monitor-t. A fényértékek megjelennek a terminálon.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Takard le és fedd fel a fényérzékelőt. Figyeld meg, hogy a LED világítani kezd, ha a fény szintje 300 vagy kevesebb, és kikapcsol, ha a fény szintje nagyobb, mint 300.

![A LED, amely a WIO-hoz csatlakozik, bekapcsol és kikapcsol, ahogy a fény szintje változik](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Ezt a kódot megtalálod a [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal) mappában.

😀 Az éjjeli fény programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.