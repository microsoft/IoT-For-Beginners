<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-27T22:43:45+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "hu"
}
-->
# Hívd meg az objektumdetektorodat az IoT eszközödről - Wio Terminal

Miután az objektumdetektorodat közzétetted, használhatod az IoT eszközödről.

## Másold az képosztályozó projektet

Az objektumdetektorod nagy része megegyezik azzal a képosztályozóval, amelyet egy korábbi leckében készítettél.

### Feladat - másold az képosztályozó projektet

1. Csatlakoztasd az ArduCam kamerát a Wio Terminalhoz, a [gyártási projekt 2. leckéjében](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) leírt lépések szerint.

    Érdemes lehet a kamerát egy fix pozícióba rögzíteni, például úgy, hogy a kábelt egy doboz vagy konzerv fölé akasztod, vagy a kamerát kétoldalas ragasztóval egy dobozhoz rögzíted.

1. Hozz létre egy teljesen új Wio Terminal projektet a PlatformIO segítségével. Nevezd el a projektet `stock-counter`-nek.

1. Ismételd meg a lépéseket a [gyártási projekt 2. leckéjéből](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device), hogy képeket készíts a kamerával.

1. Ismételd meg a lépéseket a [gyártási projekt 2. leckéjéből](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device), hogy meghívd a képosztályozót. Ennek a kódnak a nagy része újra felhasználható az objektumok detektálásához.

## Módosítsd a kódot osztályozóról objektumdetektorra

A képek osztályozására használt kód nagyon hasonló az objektumok detektálására használt kódhoz. A fő különbség az URL, amelyet a Custom Vision-től kaptál, és a hívás eredményei.

### Feladat - módosítsd a kódot osztályozóról objektumdetektorra

1. Add hozzá a következő include direktívát a `main.cpp` fájl tetejéhez:

    ```cpp
    #include <vector>
    ```

1. Nevezd át a `classifyImage` függvényt `detectStock`-ra, mind a függvény nevét, mind a `buttonPressed` függvényben lévő hívást.

1. A `detectStock` függvény fölött deklarálj egy küszöbértéket, hogy kiszűrd az alacsony valószínűségű detektálásokat:

    ```cpp
    const float threshold = 0.3f;
    ```

    Ellentétben a képosztályozóval, amely csak egy eredményt ad vissza címkénként, az objektumdetektor több eredményt ad vissza, így az alacsony valószínűségűeket ki kell szűrni.

1. A `detectStock` függvény fölött deklarálj egy függvényt a predikciók feldolgozására:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Ez egy predikciók listáját veszi át, és kiírja őket a soros monitorra.

1. A `detectStock` függvényben cseréld ki a predikciókat végigjáró `for` ciklus tartalmát a következőre:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Ez végigmegy a predikciókon, összehasonlítja a valószínűséget a küszöbértékkel. Az összes olyan predikció, amelynek valószínűsége magasabb a küszöbértéknél, hozzáadódik egy `list`-hez, és átadódik a `processPredictions` függvénynek.

1. Töltsd fel és futtasd a kódot. Irányítsd a kamerát a polcon lévő tárgyakra, és nyomd meg a C gombot. Az eredményt a soros monitoron fogod látni:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Lehet, hogy a `threshold` értékét hozzá kell igazítanod a képeidhez.

    Látni fogod a készített képet, és ezeket az értékeket a **Predictions** fülön a Custom Vision-ben.

    ![4 paradicsompüré konzerv egy polcon, a 4 detektálás predikcióival: 35.8%, 33.5%, 25.7% és 16.6%](../../../../../translated_images/hu/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Ezt a kódot megtalálod a [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) mappában.

😀 A készlet számláló programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.