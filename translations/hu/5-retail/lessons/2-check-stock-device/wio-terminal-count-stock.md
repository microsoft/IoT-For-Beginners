<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T22:45:48+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "hu"
}
-->
# Számolja meg a készletet IoT eszközével - Wio Terminal

Az előrejelzések és a körülöttük lévő határoló dobozok kombinációja felhasználható a készlet megszámlálására egy képen.

## Készlet számlálása

![4 paradicsompüré konzerv határoló dobozokkal körülvéve](../../../../../translated_images/hu/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

A fenti képen a határoló dobozok kissé átfedik egymást. Ha ez az átfedés sokkal nagyobb lenne, akkor a határoló dobozok ugyanarra az objektumra utalhatnának. Az objektumok helyes megszámlálásához figyelmen kívül kell hagyni azokat a dobozokat, amelyek jelentős átfedéssel rendelkeznek.

### Feladat - készlet számlálása az átfedés figyelmen kívül hagyásával

1. Nyissa meg a `stock-counter` projektjét, ha még nincs megnyitva.

1. A `processPredictions` függvény fölé adja hozzá a következő kódot:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Ez meghatározza az átfedés százalékos mértékét, amelyet még megengedettnek tekintünk, mielőtt a határoló dobozokat ugyanannak az objektumnak tekintenénk. A 0.20 érték 20%-os átfedést jelent.

1. Ezután, a `processPredictions` függvény fölé adja hozzá a következő kódot, amely kiszámítja két téglalap átfedését:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Ez a kód egy `Point` struktúrát definiál, amely a képen lévő pontokat tárolja, valamint egy `Rect` struktúrát, amely egy téglalapot határoz meg a bal felső és jobb alsó koordináták alapján. Ezután egy `area` függvényt definiál, amely kiszámítja egy téglalap területét a bal felső és jobb alsó koordináták alapján.

    Ezután egy `overlappingArea` függvényt definiál, amely kiszámítja két téglalap átfedési területét. Ha nincs átfedés, akkor 0-t ad vissza.

1. Az `overlappingArea` függvény alá deklaráljon egy függvényt, amely egy határoló dobozt `Rect`-té alakít:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Ez a függvény az objektumdetektor egy előrejelzését veszi, kinyeri belőle a határoló dobozt, és a határoló doboz értékeit felhasználva meghatároz egy téglalapot. A jobb oldalt a bal oldal plusz a szélesség alapján számítja ki. Az alsó részt pedig a felső plusz a magasság alapján.

1. Az előrejelzéseket össze kell hasonlítani egymással, és ha két előrejelzés átfedése meghaladja a küszöbértéket, az egyiket törölni kell. Az átfedési küszöb egy százalékos érték, ezért meg kell szorozni a legkisebb határoló doboz méretével, hogy ellenőrizze, az átfedés meghaladja-e a határoló doboz adott százalékát, nem pedig az egész kép adott százalékát. Kezdje azzal, hogy törli a `processPredictions` függvény tartalmát.

1. Adja hozzá a következőt az üres `processPredictions` függvényhez:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Ez a kód egy vektort deklarál, amely azokat az előrejelzéseket tárolja, amelyek nem fedik át egymást. Ezután végigmegy az összes előrejelzésen, és egy `Rect`-et hoz létre a határoló dobozból.

    Ezután a kód végigmegy a fennmaradó előrejelzéseken, kezdve az aktuális előrejelzés utáni elemmel. Ez megakadályozza, hogy az előrejelzéseket többször hasonlítsák össze - ha az 1-est és a 2-est már összehasonlították, nincs szükség a 2-est az 1-essel összehasonlítani, csak a 3-assal, 4-essel stb.

    Minden előrejelzés-pár esetében kiszámítja az átfedési területet. Ezt összehasonlítja a legkisebb határoló doboz területével - ha az átfedés meghaladja a legkisebb határoló doboz küszöbértékének százalékát, az előrejelzést nem teljesítettnek jelöli. Ha az összes átfedés összehasonlítása után az előrejelzés megfelel az ellenőrzéseknek, hozzáadja a `passed_predictions` gyűjteményhez.

    > 💁 Ez egy nagyon egyszerű módja az átfedések eltávolításának, egyszerűen eltávolítva az átfedő pár első elemét. A termelési kódhoz érdemes lenne több logikát hozzáadni, például figyelembe venni a több objektum közötti átfedéseket, vagy ha egy határoló doboz egy másikban található.

1. Ezután adja hozzá a következő kódot, hogy az elfogadott előrejelzések részleteit elküldje a soros monitorra:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Ez a kód végigmegy az elfogadott előrejelzéseken, és kiírja azok részleteit a soros monitorra.

1. Ezután adjon hozzá kódot, amely kiírja a megszámolt elemek számát a soros monitorra:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Ezután elküldhető egy IoT szolgáltatásnak, hogy figyelmeztessen, ha a készletszint alacsony.

1. Töltse fel és futtassa a kódját. Irányítsa a kamerát a polcon lévő tárgyakra, és nyomja meg a C gombot. Próbálja meg módosítani az `overlap_threshold` értékét, hogy lássa, hogyan hagyja figyelmen kívül az előrejelzéseket.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Ezt a kódot megtalálja a [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) mappában.

😀 A készletszámláló programja sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.