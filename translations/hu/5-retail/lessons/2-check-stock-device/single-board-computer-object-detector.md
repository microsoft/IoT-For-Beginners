<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T22:47:02+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "hu"
}
-->
# Hívd meg az objektumdetektorodat az IoT eszközödről - Virtuális IoT hardver és Raspberry Pi

Miután az objektumdetektorod publikálva lett, használhatod az IoT eszközödről.

## Másold le a képosztályozó projektet

Az árukészlet-detektorod nagy része megegyezik azzal a képosztályozóval, amit egy korábbi leckében készítettél.

### Feladat - másold le a képosztályozó projektet

1. Hozz létre egy `stock-counter` nevű mappát a számítógépeden, ha virtuális IoT eszközt használsz, vagy a Raspberry Pi-n. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy beállítottál egy virtuális környezetet.

1. Állítsd be a kamera hardvert.

    * Ha Raspberry Pi-t használsz, szereld fel a PiCamera-t. Érdemes lehet a kamerát egy fix pozícióba rögzíteni, például úgy, hogy a kábelt egy doboz vagy konzerv fölé akasztod, vagy a kamerát kétoldalas ragasztószalaggal egy dobozhoz rögzíted.
    * Ha virtuális IoT eszközt használsz, telepítened kell a CounterFit-et és a CounterFit PyCamera shim-et. Ha állóképeket fogsz használni, készíts néhány olyan képet, amit az objektumdetektorod még nem látott. Ha webkamerát használsz, győződj meg róla, hogy úgy van elhelyezve, hogy lássa az észlelni kívánt árukészletet.

1. Ismételd meg a [gyártási projekt 2. leckéjének](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) lépéseit, hogy képeket rögzíts a kamerával.

1. Ismételd meg a [gyártási projekt 2. leckéjének](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) lépéseit, hogy meghívd a képosztályozót. Ennek a kódnak a nagy része újrahasznosítható az objektumok észleléséhez.

## Módosítsd a kódot osztályozóról objektumdetektorra

A képek osztályozására használt kód nagyon hasonló az objektumok észlelésére használt kódhoz. A fő különbség a Custom Vision SDK-n meghívott metódusban és a hívás eredményeiben rejlik.

### Feladat - módosítsd a kódot osztályozóról objektumdetektorra

1. Töröld ki azt a három kódsort, amely a képet osztályozza és feldolgozza az előrejelzéseket:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Távolítsd el ezt a három sort.

1. Add hozzá a következő kódot, hogy objektumokat észlelj a képen:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ez a kód a `detect_image` metódust hívja meg a prediktoron, hogy futtassa az objektumdetektort. Ezután összegyűjti az összes előrejelzést, amely egy küszöbérték felett van, és kiírja őket a konzolra.

    Ellentétben a képosztályozóval, amely csak egy eredményt ad vissza címkénként, az objektumdetektor több eredményt is visszaad, így az alacsony valószínűségűeket ki kell szűrni.

1. Futtasd a kódot, amely rögzít egy képet, elküldi az objektumdetektornak, és kiírja az észlelt objektumokat. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy megfelelő kép van beállítva a CounterFit-ben, vagy a webkamerád ki van választva. Ha Raspberry Pi-t használsz, győződj meg róla, hogy a kamerád a polcon lévő tárgyakra irányul.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Lehet, hogy a `threshold` értékét a képeidhez megfelelő szintre kell állítanod.

    Meg fogod tudni nézni a készített képet, és ezeket az értékeket a **Predictions** fülön a Custom Vision-ben.

    ![4 paradicsompüré konzerv egy polcon, az észlelések előrejelzéseivel: 35.8%, 33.5%, 25.7% és 16.6%](../../../../../translated_images/hu/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Ezt a kódot megtalálod a [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) vagy a [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) mappában.

😀 Az árukészlet-számláló programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.