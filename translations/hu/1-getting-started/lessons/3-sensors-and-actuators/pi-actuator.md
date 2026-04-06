# Építs egy éjjeli fényt - Raspberry Pi

Ebben a leckében hozzáadsz egy LED-et a Raspberry Pi-hez, és éjjeli fényt készítesz belőle.

## Hardver

Az éjjeli fényhez most egy működtető elemre van szükség.

A működtető elem egy **LED**, egy [fénykibocsátó dióda](https://wikipedia.org/wiki/Light-emitting_diode), amely világít, amikor áram folyik rajta keresztül. Ez egy digitális működtető elem, amelynek két állapota van: be és ki. Az 1-es érték bekapcsolja a LED-et, a 0 pedig kikapcsolja. A LED egy külső Grove működtető elem, amelyet a Raspberry Pi-hez csatlakoztatott Grove Base hat-hoz kell csatlakoztatni.

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

    A LED-ek fénykibocsátó diódák, és a diódák olyan elektronikai eszközök, amelyek csak egy irányban tudnak áramot vezetni. Ez azt jelenti, hogy a LED-et megfelelően kell csatlakoztatni, különben nem fog működni.

    A LED egyik lába a pozitív csatlakozó, a másik a negatív csatlakozó. A LED nem teljesen kerek, az egyik oldala kissé laposabb. A kissé laposabb oldal a negatív csatlakozó. Amikor a LED-et a modulhoz csatlakoztatod, győződj meg róla, hogy a kerekebb oldalhoz tartozó láb a modul külső részén lévő **+** jelzésű aljzathoz van csatlakoztatva, a laposabb oldal pedig a modul közepéhez közelebb eső aljzathoz.

1. A LED modulnak van egy forgatható gombja, amely lehetővé teszi a fényerő szabályozását. Kezdetben tekerd teljesen fel, az óramutató járásával ellentétes irányba forgatva, ameddig csak lehet, egy kis csillagcsavarhúzóval.

1. Helyezd be a Grove kábel egyik végét a LED modul aljzatába. Csak egy irányban illeszkedik.

1. Kapcsold ki a Raspberry Pi-t, és csatlakoztasd a Grove kábel másik végét a Grove Base hat-on lévő **D5** jelzésű digitális aljzathoz, amely a Pi-hez van csatlakoztatva. Ez az aljzat a második balról, a GPIO csatlakozók melletti aljzatsoron.

![A Grove LED csatlakoztatva a D5 aljzathoz](../../../../../translated_images/hu/pi-led.97f1d474981dc35d.webp)

## Programozd az éjjeli fényt

Az éjjeli fényt most már programozhatod a Grove fényérzékelő és a Grove LED segítségével.

### Feladat - programozd az éjjeli fényt

Programozd az éjjeli fényt.

1. Kapcsold be a Pi-t, és várd meg, amíg elindul.

1. Nyisd meg az éjjeli fény projektet a VS Code-ban, amelyet a feladat előző részében hoztál létre, akár közvetlenül a Pi-n futtatva, akár a Remote SSH bővítmény segítségével csatlakozva.

1. Add hozzá a következő kódot az `app.py` fájlhoz, hogy importálj egy szükséges könyvtárat. Ezt a többi `import` sor alá kell hozzáadni.

    ```python
    from grove.grove_led import GroveLed
    ```

    A `from grove.grove_led import GroveLed` utasítás importálja a `GroveLed`-et a Grove Python könyvtárakból. Ez a könyvtár tartalmazza a Grove LED kezeléséhez szükséges kódot.

1. Add hozzá a következő kódot a `light_sensor` deklaráció után, hogy létrehozz egy példányt a LED-et kezelő osztályból:

    ```python
    led = GroveLed(5)
    ```

    A `led = GroveLed(5)` sor létrehoz egy példányt a `GroveLed` osztályból, amely a **D5** csatlakozóhoz kapcsolódik - a digitális Grove csatlakozóhoz, amelyhez a LED csatlakozik.

    > 💁 Minden aljzatnak egyedi csatlakozószáma van. A 0, 2, 4 és 6 csatlakozók analóg csatlakozók, az 5, 16, 18, 22, 24 és 26 csatlakozók digitális csatlakozók.

1. Adj hozzá egy ellenőrzést a `while` cikluson belül, a `time.sleep` előtt, hogy ellenőrizd a fény szintjét, és kapcsolja be vagy ki a LED-et:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ez a kód ellenőrzi a `light` értéket. Ha ez kisebb, mint 300, akkor meghívja a `GroveLed` osztály `on` metódusát, amely egy digitális 1-es értéket küld a LED-nek, bekapcsolva azt. Ha a fény értéke nagyobb vagy egyenlő 300-zal, akkor meghívja az `off` metódust, amely egy digitális 0 értéket küld a LED-nek, kikapcsolva azt.

    > 💁 Ennek a kódnak ugyanazon a szinten kell behúzva lennie, mint a `print('Light level:', light)` sor, hogy a while cikluson belül legyen!

    > 💁 Digitális értékek küldésekor a működtető elemeknek a 0 érték 0V, az 1 érték pedig az eszköz maximális feszültsége. A Raspberry Pi esetében a Grove érzékelőkkel és működtető elemekkel az 1 feszültsége 3.3V.

1. A VS Code termináljában futtasd a következőt, hogy elindítsd a Python alkalmazásodat:

    ```sh
    python3 app.py
    ```

    A fény értékek megjelennek a konzolon.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Takarj le és fedj fel a fényérzékelőt. Figyeld meg, hogy a LED világít, ha a fény szintje 300 vagy kevesebb, és kikapcsol, ha a fény szintje nagyobb, mint 300.

    > 💁 Ha a LED nem kapcsol be, győződj meg róla, hogy megfelelően van csatlakoztatva, és a forgatható gomb teljesen fel van tekerve.

![A LED csatlakoztatva a Pi-hez, bekapcsol és kikapcsol a fény szintjének változásával](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Ezt a kódot megtalálod a [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi) mappában.

😀 Az éjjeli fény programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.