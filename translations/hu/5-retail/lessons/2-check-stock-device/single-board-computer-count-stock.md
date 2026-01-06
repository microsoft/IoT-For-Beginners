<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T22:44:35+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "hu"
}
-->
# Számold meg a készletet IoT eszközöddel - Virtuális IoT hardver és Raspberry Pi

Az előrejelzések és a hozzájuk tartozó határoló dobozok kombinációja felhasználható a készlet megszámlálására egy képen.

## Határoló dobozok megjelenítése

Egy hasznos hibakeresési lépésként nemcsak kiírhatod a határoló dobozokat, hanem rá is rajzolhatod azokat a képre, amelyet a rendszer a kép rögzítésekor mentett el.

### Feladat - határoló dobozok kiírása

1. Győződj meg arról, hogy a `stock-counter` projekt meg van nyitva a VS Code-ban, és ha virtuális IoT eszközt használsz, a virtuális környezet aktiválva van.

1. Módosítsd a `for` ciklusban található `print` utasítást az alábbira, hogy a határoló dobozokat a konzolra írd ki:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Futtasd az alkalmazást úgy, hogy a kamera egy polcon lévő készletre mutat. A határoló dobozok kiírásra kerülnek a konzolra, a bal, felső, szélesség és magasság értékekkel 0 és 1 között.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Feladat - határoló dobozok rajzolása a képre

1. A [Pillow](https://pypi.org/project/Pillow/) Pip csomag használható képek szerkesztésére. Telepítsd a következő paranccsal:

    ```sh
    pip3 install pillow
    ```

    Ha virtuális IoT eszközt használsz, győződj meg róla, hogy ezt az aktivált virtuális környezetben futtatod.

1. Add hozzá a következő import utasítást az `app.py` fájl tetejéhez:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Ez a kód szükséges a kép szerkesztéséhez.

1. Add hozzá a következő kódot az `app.py` fájl végéhez:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Ez a kód megnyitja a korábban mentett képet szerkesztésre. Ezután végigmegy az előrejelzéseken, lekéri a határoló dobozokat, és kiszámítja az alsó jobb koordinátát a 0-1 közötti határoló doboz értékek alapján. Ezeket az értékeket a kép megfelelő dimenziójával szorozva alakítja át képi koordinátákká. Például, ha a bal érték 0,5 egy 600 pixel széles képen, akkor ez 300-ra alakul (0,5 x 600 = 300).

    Minden határoló doboz piros vonallal kerül a képre. Végül a szerkesztett kép mentésre kerül, felülírva az eredeti képet.

1. Futtasd az alkalmazást úgy, hogy a kamera egy polcon lévő készletre mutat. A VS Code fájlkezelőjében megjelenik az `image.jpg` fájl, amelyet kiválasztva láthatod a határoló dobozokat.

    ![4 paradicsompüré konzerv, mindegyik körül határoló dobozokkal](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.hu.jpg)

## Készlet megszámlálása

A fent látható képen a határoló dobozok kissé átfedik egymást. Ha ez az átfedés sokkal nagyobb lenne, akkor a határoló dobozok ugyanarra az objektumra utalhatnának. Az objektumok helyes megszámlálásához figyelmen kívül kell hagyni azokat a dobozokat, amelyek jelentős átfedéssel rendelkeznek.

### Feladat - készlet megszámlálása átfedések figyelmen kívül hagyásával

1. A [Shapely](https://pypi.org/project/Shapely/) Pip csomag használható az átfedések kiszámítására. Ha Raspberry Pi-t használsz, először telepítened kell egy könyvtárfüggőséget:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Telepítsd a Shapely Pip csomagot:

    ```sh
    pip3 install shapely
    ```

    Ha virtuális IoT eszközt használsz, győződj meg róla, hogy ezt az aktivált virtuális környezetben futtatod.

1. Add hozzá a következő import utasítást az `app.py` fájl tetejéhez:

    ```python
    from shapely.geometry import Polygon
    ```

    Ez a kód szükséges a poligonok létrehozásához az átfedések kiszámításához.

1. Add hozzá a következő kódot a határoló dobozok rajzolása előtti részhez:

    ```python
    overlap_threshold = 0.20
    ```

    Ez meghatározza az átfedési százalékot, amelyet a határoló dobozok ugyanazon objektumnak tekintése előtt megengedett. A 0,20 érték 20%-os átfedést jelent.

1. Az átfedés kiszámításához a Shapely segítségével a határoló dobozokat Shapely poligonokká kell alakítani. Add hozzá a következő függvényt ehhez:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Ez egy poligont hoz létre egy előrejelzés határoló dobozából.

1. Az átfedő objektumok eltávolításának logikája az összes határoló doboz összehasonlítását jelenti. Ha bármelyik előrejelzési pár határoló dobozai az átfedési küszöbértéket meghaladják, az egyik előrejelzést törölni kell. Az összes előrejelzés összehasonlításához az 1. előrejelzést összehasonlítjuk a 2., 3., 4., stb.-vel, majd a 2.-at a 3., 4., stb.-vel. Az alábbi kód ezt végzi el:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    Az átfedést a Shapely `Polygon.intersection` metódusa számítja ki, amely visszaad egy poligont, amely az átfedést tartalmazza. Az átfedés területe ezután ebből a poligonból kerül kiszámításra. Ez az átfedési küszöb nem abszolút érték, hanem a határoló doboz százalékában kell kifejezni, ezért a legkisebb határoló doboz kerül meghatározásra, és az átfedési küszöb alapján kiszámítjuk, hogy mekkora terület lehet az átfedés, hogy ne haladja meg a legkisebb határoló doboz százalékos átfedési küszöbét. Ha az átfedés ezt meghaladja, az előrejelzés törlésre kerül.

    Miután egy előrejelzés törlésre került, azt már nem kell újra ellenőrizni, így a belső ciklus kilép, hogy a következő előrejelzést ellenőrizze. Nem lehet elemeket törölni egy listából, miközben azon iterálunk, ezért az átfedési küszöböt meghaladó határoló dobozok hozzáadódnak a `to_delete` listához, majd a végén törlésre kerülnek.

    Végül a készlet száma kiírásra kerül a konzolra. Ezután ez az adat elküldhető egy IoT szolgáltatásnak, hogy figyelmeztessen, ha a készletszint alacsony. Mindez a kód a határoló dobozok rajzolása előtt van, így a generált képeken az átfedések nélküli készlet-előrejelzéseket fogod látni.

    > 💁 Ez egy nagyon egyszerű módszer az átfedések eltávolítására, amely egyszerűen eltávolítja az elsőt egy átfedő párból. Produkciós kód esetén érdemes lenne több logikát beépíteni, például figyelembe venni az átfedéseket több objektum között, vagy ha egy határoló doboz egy másikban található.

1. Futtasd az alkalmazást úgy, hogy a kamera egy polcon lévő készletre mutat. A kimenet jelezni fogja az átfedési küszöböt meghaladó átfedések nélküli határoló dobozok számát. Próbáld meg módosítani az `overlap_threshold` értékét, hogy lásd, hogyan hagyja figyelmen kívül az előrejelzéseket.

> 💁 Ezt a kódot megtalálod a [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) vagy a [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device) mappában.

😀 A készletszámláló programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az [Co-op Translator](https://github.com/Azure/co-op-translator) AI fordítási szolgáltatás segítségével került lefordításra. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.