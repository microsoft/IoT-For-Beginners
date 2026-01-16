<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T22:46:10+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "cs"
}
-->
# Počítání zásob z vašeho IoT zařízení - Wio Terminal

Kombinace předpovědí a jejich ohraničujících rámečků může být použita k počítání zásob na obrázku.

## Počítání zásob

![4 plechovky rajčatového protlaku s ohraničujícími rámečky kolem každé plechovky](../../../../../translated_images/cs/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

Na obrázku výše mají ohraničující rámečky malý překryv. Pokud by tento překryv byl mnohem větší, rámečky by mohly označovat stejný objekt. Aby bylo možné objekty správně spočítat, je třeba ignorovat rámečky s významným překryvem.

### Úkol - počítání zásob s ignorováním překryvu

1. Otevřete svůj projekt `stock-counter`, pokud již není otevřený.

1. Nad funkcí `processPredictions` přidejte následující kód:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Tento kód definuje procentuální překryv, který je povolen, než jsou ohraničující rámečky považovány za stejný objekt. Hodnota 0.20 definuje 20% překryv.

1. Pod tento kód, a nad funkci `processPredictions`, přidejte následující kód pro výpočet překryvu mezi dvěma obdélníky:

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

    Tento kód definuje strukturu `Point` pro uložení bodů na obrázku a strukturu `Rect` pro definování obdélníku pomocí souřadnic levého horního a pravého dolního rohu. Poté definuje funkci `area`, která vypočítá plochu obdélníku z těchto souřadnic.

    Dále definuje funkci `overlappingArea`, která vypočítá překrytou plochu dvou obdélníků. Pokud se nepřekrývají, vrátí hodnotu 0.

1. Pod funkci `overlappingArea` deklarujte funkci pro převod ohraničujícího rámečku na `Rect`:

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

    Tato funkce vezme předpověď z detektoru objektů, extrahuje ohraničující rámeček a použije hodnoty z rámečku k definování obdélníku. Pravá strana se vypočítá jako levá plus šířka. Spodní strana se vypočítá jako horní plus výška.

1. Předpovědi je třeba porovnat mezi sebou, a pokud mají dvě předpovědi překryv větší než stanovený práh, jedna z nich musí být odstraněna. Práh překryvu je procentuální hodnota, takže je třeba ji vynásobit velikostí nejmenšího ohraničujícího rámečku, aby se ověřilo, že překryv přesahuje dané procento rámečku, nikoli celé obrázku. Začněte odstraněním obsahu funkce `processPredictions`.

1. Do prázdné funkce `processPredictions` přidejte následující kód:

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

    Tento kód deklaruje vektor pro uložení předpovědí, které se nepřekrývají. Poté prochází všechny předpovědi a vytváří z ohraničujícího rámečku `Rect`.

    Dále tento kód prochází zbývající předpovědi, počínaje tou, která následuje po aktuální předpovědi. Tím se zabrání opakovanému porovnávání předpovědí - jakmile byly porovnány předpovědi 1 a 2, není třeba porovnávat 2 s 1, pouze s 3, 4 atd.

    Pro každou dvojici předpovědí se vypočítá překrytá plocha. Ta se poté porovná s plochou nejmenšího ohraničujícího rámečku - pokud překryv přesahuje stanovené procento nejmenšího rámečku, předpověď je označena jako neprošlá. Pokud po porovnání všech překryvů předpověď projde kontrolou, je přidána do kolekce `passed_predictions`.

    > 💁 Toto je velmi jednoduchý způsob, jak odstranit překryvy, pouze odstraněním první předpovědi v překrývající se dvojici. Pro produkční kód byste zde chtěli přidat více logiky, například zohlednění překryvů mezi více objekty nebo pokud je jeden ohraničující rámeček obsažen v jiném.

1. Poté přidejte následující kód pro odeslání podrobností o prošlých předpovědích do sériového monitoru:

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

    Tento kód prochází prošlé předpovědi a tiskne jejich podrobnosti do sériového monitoru.

1. Pod tento kód přidejte kód pro tisk počtu spočítaných položek do sériového monitoru:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Tento počet by pak mohl být odeslán do IoT služby, aby upozornil na nízké zásoby.

1. Nahrajte a spusťte svůj kód. Namiřte kameru na objekty na polici a stiskněte tlačítko C. Zkuste upravit hodnotu `overlap_threshold`, abyste viděli, jak jsou předpovědi ignorovány.

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

> 💁 Tento kód najdete ve složce [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Váš program pro počítání zásob byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o co největší přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Za autoritativní zdroj by měl být považován původní dokument v jeho původním jazyce. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné výklady vyplývající z použití tohoto překladu.