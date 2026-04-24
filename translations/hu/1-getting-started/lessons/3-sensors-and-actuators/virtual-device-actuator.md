# Építs egy éjszakai fényt - Virtuális IoT Hardver

Ebben a leckében hozzáadsz egy LED-et a virtuális IoT eszközödhöz, és éjszakai fényt készítesz belőle.

## Virtuális Hardver

Az éjszakai fényhez egy működtetőre van szükség, amelyet a CounterFit alkalmazásban hozunk létre.

A működtető egy **LED**. Egy fizikai IoT eszközben ez egy [fénykibocsátó dióda](https://wikipedia.org/wiki/Light-emitting_diode) lenne, amely világít, amikor áram folyik rajta keresztül. Ez egy digitális működtető, amelynek 2 állapota van: be- és kikapcsolt. Ha 1-es értéket küldünk, a LED bekapcsol, ha 0-t, akkor kikapcsol.

Az éjszakai fény logikája pszeudokódban:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Működtető hozzáadása a CounterFit-hez

Ahhoz, hogy virtuális LED-et használj, hozzá kell adnod azt a CounterFit alkalmazáshoz.

#### Feladat - működtető hozzáadása a CounterFit-hez

Add hozzá a LED-et a CounterFit alkalmazáshoz.

1. Győződj meg róla, hogy a CounterFit webalkalmazás fut az előző feladatból. Ha nem, indítsd el, és add hozzá újra a fényérzékelőt.

1. Hozz létre egy LED-et:

    1. A *Create actuator* mezőben az *Actuator* panelen nyisd le az *Actuator type* mezőt, és válaszd ki a *LED*-et.

    1. Állítsd a *Pin*-t *5*-re.

    1. Válaszd ki az **Add** gombot, hogy létrehozd a LED-et az 5-ös lábon.

    ![A LED beállításai](../../../../../translated_images/hu/counterfit-create-led.ba9db1c9b8c622a6.webp)

    A LED létrejön, és megjelenik a működtetők listájában.

    ![A létrehozott LED](../../../../../translated_images/hu/counterfit-led.c0ab02de6d256ad8.webp)

    Miután a LED létrejött, megváltoztathatod a színét a *Color* színválasztóval. A szín kiválasztása után nyomd meg a **Set** gombot a szín megváltoztatásához.

### Programozd az éjszakai fényt

Most már programozhatod az éjszakai fényt a CounterFit fényérzékelő és LED segítségével.

#### Feladat - éjszakai fény programozása

Programozd az éjszakai fényt.

1. Nyisd meg az éjszakai fény projektet a VS Code-ban, amelyet az előző feladat során hoztál létre. Ha szükséges, állítsd le és hozd létre újra a terminált, hogy az a virtuális környezetet használja.

1. Nyisd meg az `app.py` fájlt.

1. Add hozzá a következő kódot az `app.py` fájlhoz, hogy importálj egy szükséges könyvtárat. Ezt a többi `import` sor alá kell hozzáadni.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    A `from counterfit_shims_grove.grove_led import GroveLed` sor importálja a `GroveLed` osztályt a CounterFit Grove shim Python könyvtárakból. Ez a könyvtár tartalmazza a LED-del való interakcióhoz szükséges kódot, amelyet a CounterFit alkalmazásban hoztál létre.

1. Add hozzá a következő kódot a `light_sensor` deklaráció után, hogy létrehozz egy példányt a LED-et kezelő osztályból:

    ```python
    led = GroveLed(5)
    ```

    A `led = GroveLed(5)` sor létrehoz egy példányt a `GroveLed` osztályból, amely az 5-ös lábra csatlakozik - ez az a CounterFit Grove láb, amelyhez a LED csatlakozik.

1. Adj hozzá egy ellenőrzést a `while` cikluson belül, a `time.sleep` előtt, hogy ellenőrizd a fényerősséget, és kapcsold be vagy ki a LED-et:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ez a kód ellenőrzi a `light` értéket. Ha ez kisebb, mint 300, meghívja a `GroveLed` osztály `on` metódusát, amely digitális 1-es értéket küld a LED-nek, bekapcsolva azt. Ha a fényérték nagyobb vagy egyenlő 300-zal, meghívja az `off` metódust, amely digitális 0-t küld a LED-nek, kikapcsolva azt.

    > 💁 Ennek a kódnak ugyanazon a szinten kell behúzva lennie, mint a `print('Light level:', light)` sor, hogy a while cikluson belül legyen!

1. A VS Code termináljában futtasd a következőt, hogy elindítsd a Python alkalmazásodat:

    ```sh
    python3 app.py
    ```

    A fényértékek megjelennek a konzolon.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Módosítsd a *Value* vagy a *Random* beállításokat, hogy a fényerősség 300 fölé és alá változzon. A LED be- és kikapcsol.

![A LED a CounterFit alkalmazásban, ahogy a fényerősség változásával be- és kikapcsol](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Ezt a kódot megtalálod a [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) mappában.

😀 Az éjszakai fény programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.