<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T20:30:03+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "nl"
}
-->
# Tel voorraad met je IoT-apparaat - Wio Terminal

Een combinatie van de voorspellingen en hun begrenzingskaders kan worden gebruikt om voorraad in een afbeelding te tellen.

## Voorraad tellen

![4 blikken tomatenpuree met begrenzingskaders rond elk blik](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.nl.jpg)

In de afbeelding hierboven hebben de begrenzingskaders een kleine overlap. Als deze overlap veel groter was, zouden de begrenzingskaders mogelijk hetzelfde object aangeven. Om de objecten correct te tellen, moet je kaders met een significante overlap negeren.

### Taak - voorraad tellen met negeren van overlap

1. Open je `stock-counter` project als het nog niet geopend is.

1. Voeg boven de functie `processPredictions` de volgende code toe:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Dit definieert het percentage overlap dat is toegestaan voordat de begrenzingskaders als hetzelfde object worden beschouwd. 0.20 definieert een overlap van 20%.

1. Voeg hieronder, en boven de functie `processPredictions`, de volgende code toe om de overlap tussen twee rechthoeken te berekenen:

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

    Deze code definieert een `Point` struct om punten op de afbeelding op te slaan, en een `Rect` struct om een rechthoek te definiëren met behulp van een bovenlinker en onderrechter coördinaat. Vervolgens definieert het een `area` functie die het gebied van een rechthoek berekent op basis van een bovenlinker en onderrechter coördinaat.

    Daarna definieert het een `overlappingArea` functie die het overlappende gebied van 2 rechthoeken berekent. Als ze niet overlappen, retourneert het 0.

1. Onder de functie `overlappingArea`, declareer een functie om een begrenzingskader om te zetten naar een `Rect`:

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

    Dit neemt een voorspelling van de objectdetector, haalt het begrenzingskader op en gebruikt de waarden van het begrenzingskader om een rechthoek te definiëren. De rechterkant wordt berekend door de linkerzijde plus de breedte. De onderkant wordt berekend als de bovenkant plus de hoogte.

1. De voorspellingen moeten met elkaar worden vergeleken, en als 2 voorspellingen een overlap hebben die groter is dan de drempelwaarde, moet een van hen worden verwijderd. De overlapdrempel is een percentage, dus moet worden vermenigvuldigd met de grootte van het kleinste begrenzingskader om te controleren of de overlap groter is dan het gegeven percentage van het begrenzingskader, niet het gegeven percentage van de hele afbeelding. Begin met het verwijderen van de inhoud van de functie `processPredictions`.

1. Voeg het volgende toe aan de lege functie `processPredictions`:

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

    Deze code declareert een vector om de voorspellingen op te slaan die niet overlappen. Vervolgens doorloopt het alle voorspellingen en maakt een `Rect` van het begrenzingskader.

    Daarna doorloopt deze code de resterende voorspellingen, beginnend bij degene na de huidige voorspelling. Dit voorkomt dat voorspellingen meer dan één keer worden vergeleken - zodra 1 en 2 zijn vergeleken, is het niet nodig om 2 met 1 te vergelijken, alleen met 3, 4, enz.

    Voor elk paar voorspellingen wordt het overlappende gebied berekend. Dit wordt vervolgens vergeleken met het gebied van het kleinste begrenzingskader - als de overlap groter is dan het drempelpercentage van het kleinste begrenzingskader, wordt de voorspelling gemarkeerd als niet geslaagd. Als de voorspelling na het vergelijken van alle overlap de controles doorstaat, wordt deze toegevoegd aan de collectie `passed_predictions`.

    > 💁 Dit is een zeer eenvoudige manier om overlap te verwijderen, waarbij alleen de eerste in een overlappend paar wordt verwijderd. Voor productiecode zou je hier meer logica willen toevoegen, zoals het overwegen van de overlap tussen meerdere objecten, of als één begrenzingskader volledig binnen een ander valt.

1. Voeg hierna de volgende code toe om details van de geslaagde voorspellingen naar de seriële monitor te sturen:

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

    Deze code doorloopt de geslaagde voorspellingen en print hun details naar de seriële monitor.

1. Voeg hieronder code toe om het aantal getelde items naar de seriële monitor te printen:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Dit kan vervolgens naar een IoT-service worden gestuurd om te waarschuwen als de voorraadniveaus laag zijn.

1. Upload en voer je code uit. Richt de camera op objecten op een plank en druk op de C-knop. Probeer de waarde van `overlap_threshold` aan te passen om te zien dat voorspellingen worden genegeerd.

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

> 💁 Je kunt deze code vinden in de [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) map.

😀 Je voorraad-telprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.