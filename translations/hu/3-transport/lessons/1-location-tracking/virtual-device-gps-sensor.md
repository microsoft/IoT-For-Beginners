# GPS-adatok olvasása - Virtuális IoT hardver

Ebben a leckében hozzáad egy GPS-érzékelőt a virtuális IoT-eszközéhez, és adatokat olvas le róla.

## Virtuális hardver

A virtuális IoT-eszköz egy szimulált GPS-érzékelőt fog használni, amely UART-on keresztül érhető el egy soros porton.

Egy fizikai GPS-érzékelő antennával rendelkezik, amely a GPS-műholdak rádióhullámait veszi, és a GPS-jeleket GPS-adatokká alakítja. A virtuális változat ezt úgy szimulálja, hogy lehetővé teszi a szélességi és hosszúsági fok beállítását, nyers NMEA mondatok küldését, vagy egy GPX fájl feltöltését több helyszínnel, amelyeket sorban visszaadhat.

> 🎓 Az NMEA mondatokról később lesz szó ebben a leckében.

### Érzékelő hozzáadása a CounterFithez

Ahhoz, hogy virtuális GPS-érzékelőt használhasson, hozzá kell adnia egyet a CounterFit alkalmazáshoz.

#### Feladat - érzékelő hozzáadása a CounterFithez

Adja hozzá a GPS-érzékelőt a CounterFit alkalmazáshoz.

1. Hozzon létre egy új Python alkalmazást a számítógépén egy `gps-sensor` nevű mappában, amely egyetlen `app.py` fájlt és egy Python virtuális környezetet tartalmaz, majd adja hozzá a CounterFit pip csomagokat.

    > ⚠️ Ha szükséges, hivatkozhat [az 1. leckében található utasításokra a CounterFit Python projekt létrehozásához és beállításához](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Telepítsen egy további Pip csomagot, amely egy CounterFit shim-et biztosít, amely UART-alapú érzékelőkkel tud kommunikálni soros kapcsolaton keresztül. Győződjön meg róla, hogy ezt egy olyan terminálból telepíti, ahol a virtuális környezet aktiválva van.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Győződjön meg róla, hogy a CounterFit webalkalmazás fut.

1. Hozzon létre egy GPS-érzékelőt:

    1. A *Create sensor* mezőben, a *Sensors* panelen, nyissa le a *Sensor type* mezőt, és válassza ki az *UART GPS*-t.

    1. Hagyja a *Port* mezőt */dev/ttyAMA0* értéken.

    1. Válassza ki az **Add** gombot, hogy létrehozza a GPS-érzékelőt a `/dev/ttyAMA0` porton.

    ![A GPS-érzékelő beállításai](../../../../../translated_images/hu/counterfit-create-gps-sensor.6385dc9357d85ad1.webp)

    A GPS-érzékelő létrejön, és megjelenik az érzékelők listájában.

    ![A létrehozott GPS-érzékelő](../../../../../translated_images/hu/counterfit-gps-sensor.3fbb15af0a536756.webp)

## A GPS-érzékelő programozása

A virtuális IoT-eszköz most már programozható a virtuális GPS-érzékelő használatára.

### Feladat - a GPS-érzékelő programozása

Programozza be a GPS-érzékelő alkalmazást.

1. Győződjön meg róla, hogy a `gps-sensor` alkalmazás meg van nyitva a VS Code-ban.

1. Nyissa meg az `app.py` fájlt.

1. Adja hozzá a következő kódot az `app.py` tetejére, hogy az alkalmazást csatlakoztassa a CounterFithez:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Adja hozzá az alábbi kódot ez alá, hogy importáljon néhány szükséges könyvtárat, beleértve a CounterFit soros port könyvtárát:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Ez a kód importálja a `serial` modult a `counterfit_shims_serial` Pip csomagból. Ezután csatlakozik a `/dev/ttyAMA0` soros porthoz - ez az a cím, amelyet a virtuális GPS-érzékelő használ az UART portjához.

1. Adja hozzá az alábbi kódot ez alá, hogy olvasson a soros portról, és kiírja az értékeket a konzolra:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Egy `print_gps_data` nevű függvény van definiálva, amely kiírja a konzolra a neki átadott sort.

    Ezután a kód végtelen ciklust indít, amely minden ciklusban annyi szövegsort olvas be a soros portról, amennyit csak tud. Minden sorhoz meghívja a `print_gps_data` függvényt.

    Miután az összes adatot beolvasta, a ciklus 1 másodpercig várakozik, majd újra próbálkozik.

1. Futtassa ezt a kódot, ügyelve arra, hogy egy másik terminált használjon, mint amelyiken a CounterFit alkalmazás fut, hogy a CounterFit alkalmazás továbbra is működjön.

1. A CounterFit alkalmazásból változtassa meg a GPS-érzékelő értékét. Ezt az alábbi módokon teheti meg:

    * Állítsa a **Source** mezőt `Lat/Lon` értékre, és adjon meg egy konkrét szélességi, hosszúsági fokot, valamint a GPS-jel rögzítéséhez használt műholdak számát. Ez az érték csak egyszer kerül elküldésre, ezért jelölje be a **Repeat** mezőt, hogy az adat minden másodpercben ismétlődjön.

      ![A GPS-érzékelő lat/lon beállítással](../../../../../translated_images/hu/counterfit-gps-sensor-latlon.008c867d75464fbe.webp)

    * Állítsa a **Source** mezőt `NMEA` értékre, és adjon hozzá néhány NMEA mondatot a szövegdobozba. Ezek az értékek mind elküldésre kerülnek, 1 másodperces késleltetéssel minden új GGA (pozíció rögzítési) mondat előtt.

      ![A GPS-érzékelő NMEA mondatokkal](../../../../../translated_images/hu/counterfit-gps-sensor-nmea.c62eea442171e17e.webp)

      Használhat olyan eszközt, mint például a [nmeagen.org](https://www.nmeagen.org), hogy ezeket a mondatokat térképen rajzolva generálja. Ezek az értékek csak egyszer kerülnek elküldésre, ezért jelölje be a **Repeat** mezőt, hogy az adatok egy másodperccel az elküldésük után ismétlődjenek.

    * Állítsa a **Source** mezőt GPX fájlra, és töltsön fel egy GPX fájlt nyomvonal helyszínekkel. GPX fájlokat letölthet számos népszerű térképes és túrázós weboldalról, például az [AllTrails](https://www.alltrails.com/) oldalról. Ezek a fájlok több GPS-helyszínt tartalmaznak egy útvonal formájában, és a GPS-érzékelő minden új helyszínt 1 másodperces időközönként ad vissza.

      ![A GPS-érzékelő GPX fájllal](../../../../../translated_images/hu/counterfit-gps-sensor-gpxfile.8310b063ce8a425c.webp)

      Ezek az értékek csak egyszer kerülnek elküldésre, ezért jelölje be a **Repeat** mezőt, hogy az adatok egy másodperccel az elküldésük után ismétlődjenek.

    Miután beállította a GPS-beállításokat, válassza ki a **Set** gombot, hogy ezeket az értékeket elmentse az érzékelőhöz.

1. Látni fogja a GPS-érzékelő nyers kimenetét, valami ilyesmit:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Ezt a kódot megtalálja a [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device) mappában.

😀 A GPS-érzékelő programja sikeresen működik!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.