<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T10:51:45+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "sk"
}
-->
# Počítanie zásob pomocou IoT zariadenia - Wio Terminal

Kombinácia predpovedí a ich ohraničujúcich rámčekov môže byť použitá na počítanie zásob na obrázku.

## Počítanie zásob

![4 konzervy paradajkového pretlaku s ohraničujúcimi rámčekmi okolo každej konzervy](../../../../../translated_images/sk/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

Na obrázku vyššie majú ohraničujúce rámčeky malý presah. Ak by bol tento presah oveľa väčší, rámčeky by mohli označovať ten istý objekt. Aby ste objekty spočítali správne, musíte ignorovať rámčeky s výrazným presahom.

### Úloha - počítanie zásob ignorovaním presahu

1. Otvorte svoj projekt `stock-counter`, ak už nie je otvorený.

1. Nad funkciu `processPredictions` pridajte nasledujúci kód:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Tento kód definuje percentuálny presah, ktorý je povolený predtým, než sa ohraničujúce rámčeky považujú za ten istý objekt. Hodnota 0.20 definuje 20% presah.

1. Pod tento kód, a nad funkciu `processPredictions`, pridajte nasledujúci kód na výpočet presahu medzi dvoma obdĺžnikmi:

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

    Tento kód definuje štruktúru `Point` na uloženie bodov na obrázku a štruktúru `Rect` na definovanie obdĺžnika pomocou súradníc horného ľavého a dolného pravého rohu. Potom definuje funkciu `area`, ktorá vypočíta plochu obdĺžnika zo súradníc horného ľavého a dolného pravého rohu.

    Ďalej definuje funkciu `overlappingArea`, ktorá vypočíta plochu presahu dvoch obdĺžnikov. Ak sa neprekrývajú, vráti hodnotu 0.

1. Pod funkciu `overlappingArea` deklarujte funkciu na konverziu ohraničujúceho rámčeka na `Rect`:

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

    Táto funkcia vezme predpoveď z detektora objektov, extrahuje ohraničujúci rámček a použije hodnoty z rámčeka na definovanie obdĺžnika. Pravá strana sa vypočíta ako ľavá plus šírka. Spodná strana sa vypočíta ako horná plus výška.

1. Predpovede musia byť porovnané medzi sebou, a ak majú dve predpovede presah väčší ako prahovú hodnotu, jedna z nich musí byť odstránená. Prahová hodnota presahu je percentuálna, takže musí byť vynásobená veľkosťou najmenšieho ohraničujúceho rámčeka, aby sa skontrolovalo, či presah presahuje dané percento rámčeka, nie dané percento celého obrázka. Začnite tým, že vymažete obsah funkcie `processPredictions`.

1. Do prázdnej funkcie `processPredictions` pridajte nasledujúci kód:

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

    Tento kód deklaruje vektor na uloženie predpovedí, ktoré sa neprekrývajú. Potom prechádza všetky predpovede a vytvára `Rect` z ohraničujúceho rámčeka.

    Ďalej tento kód prechádza zostávajúce predpovede, začínajúc od tej, ktorá nasleduje po aktuálnej predpovedi. Tým sa zabráni tomu, aby sa predpovede porovnávali viackrát - keď sa porovnajú predpovede 1 a 2, nie je potrebné porovnávať 2 s 1, iba s 3, 4, atď.

    Pre každú dvojicu predpovedí sa vypočíta plocha presahu. Tá sa potom porovná s plochou najmenšieho ohraničujúceho rámčeka - ak presah presahuje prahové percento najmenšieho rámčeka, predpoveď sa označí ako neprešla. Ak po porovnaní všetkých presahov predpoveď prejde kontrolami, pridá sa do kolekcie `passed_predictions`.

    > 💁 Toto je veľmi jednoduchý spôsob odstránenia presahov, jednoducho odstránením prvej predpovede v dvojici s presahom. Pre produkčný kód by ste chceli pridať viac logiky, napríklad zohľadnenie presahov medzi viacerými objektmi alebo ak je jeden ohraničujúci rámček obsiahnutý v druhom.

1. Po tomto pridajte nasledujúci kód na odoslanie detailov predpovedí, ktoré prešli, do sériového monitora:

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

    Tento kód prechádza predpovede, ktoré prešli, a vypisuje ich detaily do sériového monitora.

1. Pod tento kód pridajte kód na vypísanie počtu spočítaných položiek do sériového monitora:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Tento počet môže byť následne odoslaný do IoT služby na upozornenie, ak sú zásoby nízke.

1. Nahrajte a spustite svoj kód. Namierte kameru na objekty na polici a stlačte tlačidlo C. Skúste upraviť hodnotu `overlap_threshold`, aby ste videli, ako sa predpovede ignorujú.

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

> 💁 Tento kód nájdete v priečinku [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Váš program na počítanie zásob bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.