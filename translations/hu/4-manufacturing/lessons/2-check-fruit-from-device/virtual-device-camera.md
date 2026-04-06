# Kép rögzítése - Virtuális IoT Hardver

Ebben a leckében hozzáad egy kameraérzékelőt a virtuális IoT eszközéhez, és képeket olvas be róla.

## Hardver

A virtuális IoT eszköz egy szimulált kamerát fog használni, amely vagy fájlokból, vagy a webkamerájáról küld képeket.

### Kamera hozzáadása a CounterFit-hez

Ahhoz, hogy virtuális kamerát használjon, hozzá kell adnia egyet a CounterFit alkalmazáshoz.

#### Feladat - kamera hozzáadása a CounterFit-hez

Adja hozzá a kamerát a CounterFit alkalmazáshoz.

1. Hozzon létre egy új Python alkalmazást a számítógépén egy `fruit-quality-detector` nevű mappában, amely egyetlen `app.py` fájlt és egy Python virtuális környezetet tartalmaz, majd adja hozzá a CounterFit pip csomagokat.

    > ⚠️ Ha szükséges, hivatkozhat [az 1. leckében található utasításokra a CounterFit Python projekt létrehozásához és beállításához](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Telepítsen egy további Pip csomagot, amely egy CounterFit shim-et telepít, amely képes kommunikálni a kameraérzékelőkkel, szimulálva a [Picamera Pip csomag](https://pypi.org/project/picamera/) egyes funkcióit. Győződjön meg róla, hogy ezt egy olyan terminálból telepíti, amelyben a virtuális környezet aktiválva van.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Győződjön meg róla, hogy a CounterFit webalkalmazás fut.

1. Hozzon létre egy kamerát:

    1. A *Create sensor* mezőben, a *Sensors* panelen, nyissa le a *Sensor type* mezőt, és válassza a *Camera* lehetőséget.

    1. Állítsa a *Name* mezőt `Picamera` értékre.

    1. Válassza ki az **Add** gombot a kamera létrehozásához.

    ![A kamera beállításai](../../../../../translated_images/hu/counterfit-create-camera.a5de97f59c0bd3cb.webp)

    A kamera létrejön, és megjelenik az érzékelők listájában.

    ![A létrehozott kamera](../../../../../translated_images/hu/counterfit-camera.001ec52194c8ee5d.webp)

## Kamera programozása

A virtuális IoT eszköz most már programozható a virtuális kamera használatára.

### Feladat - kamera programozása

Programozza az eszközt.

1. Győződjön meg róla, hogy a `fruit-quality-detector` alkalmazás meg van nyitva a VS Code-ban.

1. Nyissa meg az `app.py` fájlt.

1. Adja hozzá a következő kódot az `app.py` tetejére, hogy az alkalmazást csatlakoztassa a CounterFit-hez:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Adja hozzá a következő kódot az `app.py` fájlhoz:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Ez a kód importál néhány szükséges könyvtárat, beleértve a `PiCamera` osztályt a counterfit_shims_picamera könyvtárból.

1. Adja hozzá az alábbi kódot, hogy inicializálja a kamerát:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Ez a kód létrehoz egy PiCamera objektumot, és beállítja a felbontást 640x480-ra. Bár magasabb felbontások is támogatottak, a képosztályozó sokkal kisebb képeken (227x227) működik, így nincs szükség nagyobb képek rögzítésére és küldésére.

    A `camera.rotation = 0` sor beállítja a kép forgatását fokokban. Ha forgatni kell a webkameráról vagy a fájlból származó képet, állítsa be ennek megfelelően. Például, ha egy banán képét egy fekvő módban lévő webkameráról álló módba szeretné forgatni, állítsa a `camera.rotation = 90` értékre.

1. Adja hozzá az alábbi kódot, hogy a képet bináris adatként rögzítse:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Ez a kód létrehoz egy `BytesIO` objektumot a bináris adatok tárolására. A képet a kamera JPEG fájlként olvassa be, és ebben az objektumban tárolja. Ez az objektum tartalmaz egy pozíciójelzőt, amely megmutatja, hol tart az adatokban, hogy további adatokat lehessen hozzáírni a végéhez, ha szükséges, így a `image.seek(0)` sor visszaállítja ezt a pozíciót az elejére, hogy később az összes adatot el lehessen olvasni.

1. Ezután adja hozzá az alábbi kódot, hogy a képet fájlba mentse:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Ez a kód megnyit egy `image.jpg` nevű fájlt írásra, majd az összes adatot beolvassa a `BytesIO` objektumból, és azt a fájlba írja.

    > 💁 A képet közvetlenül egy fájlba is rögzítheti a `camera.capture` hívásnak átadott fájlnévvel. Azért használjuk a `BytesIO` objektumot, hogy a lecke későbbi részében elküldhessük a képet a képosztályozónak.

1. Állítsa be a képet, amelyet a CounterFit kamerája rögzíteni fog. Beállíthatja a *Source*-t *File*-ra, majd feltölthet egy képfájlt, vagy beállíthatja a *Source*-t *WebCam*-ra, és a képek a webkameráról lesznek rögzítve. Győződjön meg róla, hogy a **Set** gombot kiválasztja, miután kiválasztott egy képet vagy a webkamerát.

    ![CounterFit fájllal beállítva képforrásként, és webkamerával, amely egy banánt tartó személyt mutat a webkamera előnézetében](../../../../../translated_images/hu/counterfit-camera-options.eb3bd5150a8e7dff.webp)

1. Egy kép rögzítésre kerül, és `image.jpg` néven mentésre kerül az aktuális mappába. Ezt a fájlt látni fogja a VS Code felfedezőjében. Válassza ki a fájlt a kép megtekintéséhez. Ha forgatásra van szükség, frissítse a `camera.rotation = 0` sort szükség szerint, és készítsen egy újabb képet.

> 💁 Ezt a kódot megtalálja a [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) mappában.

😀 A kamera programja sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.