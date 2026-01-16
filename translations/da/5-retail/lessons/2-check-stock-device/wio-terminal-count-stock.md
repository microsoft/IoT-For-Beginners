<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T22:19:52+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "da"
}
-->
# Tæl lager fra din IoT-enhed - Wio Terminal

En kombination af forudsigelserne og deres afgrænsningsbokse kan bruges til at tælle lager på et billede.

## Tæl lager

![4 dåser tomatpuré med afgrænsningsbokse omkring hver dåse](../../../../../translated_images/da/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

På billedet ovenfor har afgrænsningsboksene en lille overlapning. Hvis denne overlapning var meget større, kunne afgrænsningsboksene indikere det samme objekt. For at tælle objekterne korrekt skal du ignorere bokse med en betydelig overlapning.

### Opgave - tæl lager og ignorer overlapning

1. Åbn dit `stock-counter`-projekt, hvis det ikke allerede er åbent.

1. Over funktionen `processPredictions`, tilføj følgende kode:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Dette definerer den procentvise overlapning, der er tilladt, før afgrænsningsboksene betragtes som det samme objekt. 0.20 definerer en 20% overlapning.

1. Under dette, og over funktionen `processPredictions`, tilføj følgende kode for at beregne overlapningen mellem to rektangler:

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

    Denne kode definerer en `Point`-struktur til at gemme punkter på billedet og en `Rect`-struktur til at definere et rektangel ved hjælp af en øverste venstre og nederste højre koordinat. Den definerer derefter en `area`-funktion, der beregner arealet af et rektangel ud fra en øverste venstre og nederste højre koordinat.

    Derefter definerer den en `overlappingArea`-funktion, der beregner det overlappende areal af 2 rektangler. Hvis de ikke overlapper, returnerer den 0.

1. Under funktionen `overlappingArea`, deklarer en funktion til at konvertere en afgrænsningsboks til en `Rect`:

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

    Denne funktion tager en forudsigelse fra objektgenkendelsen, udtrækker afgrænsningsboksen og bruger værdierne fra afgrænsningsboksen til at definere et rektangel. Den højre side beregnes som venstre plus bredden. Den nederste beregnes som toppen plus højden.

1. Forudsigelserne skal sammenlignes med hinanden, og hvis 2 forudsigelser har en overlapning, der overstiger tærsklen, skal en af dem slettes. Overlapningstærsklen er en procentdel, så den skal multipliceres med størrelsen af den mindste afgrænsningsboks for at kontrollere, om overlapningen overstiger den angivne procentdel af afgrænsningsboksen, ikke den angivne procentdel af hele billedet. Start med at slette indholdet af funktionen `processPredictions`.

1. Tilføj følgende til den tomme `processPredictions`-funktion:

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

    Denne kode deklarerer en vektor til at gemme de forudsigelser, der ikke overlapper. Den gennemløber derefter alle forudsigelserne og opretter en `Rect` fra afgrænsningsboksen.

    Derefter gennemløber denne kode de resterende forudsigelser, startende med den, der kommer efter den aktuelle forudsigelse. Dette forhindrer, at forudsigelser sammenlignes mere end én gang - når 1 og 2 er blevet sammenlignet, er der ikke behov for at sammenligne 2 med 1, kun med 3, 4 osv.

    For hvert par af forudsigelser beregnes det overlappende areal. Dette sammenlignes derefter med arealet af den mindste afgrænsningsboks - hvis overlapningen overstiger tærskelprocenten af den mindste afgrænsningsboks, markeres forudsigelsen som ikke bestået. Hvis forudsigelsen efter at have sammenlignet alle overlapninger består kontrollen, tilføjes den til samlingen `passed_predictions`.

    > 💁 Dette er en meget simpel måde at fjerne overlapninger på, hvor kun den første i et overlappende par fjernes. For produktionskode vil du sandsynligvis tilføje mere logik her, såsom at tage højde for overlapninger mellem flere objekter eller hvis én afgrænsningsboks er indeholdt i en anden.

1. Efter dette, tilføj følgende kode for at sende detaljer om de beståede forudsigelser til den serielle monitor:

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

    Denne kode gennemløber de beståede forudsigelser og udskriver deres detaljer til den serielle monitor.

1. Under dette, tilføj kode for at udskrive antallet af optalte objekter til den serielle monitor:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Dette kunne derefter sendes til en IoT-tjeneste for at advare, hvis lagerbeholdningen er lav.

1. Upload og kør din kode. Peg kameraet mod objekter på en hylde og tryk på C-knappen. Prøv at justere værdien `overlap_threshold` for at se forudsigelser blive ignoreret.

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

> 💁 Du kan finde denne kode i mappen [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Dit lageroptællingsprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.