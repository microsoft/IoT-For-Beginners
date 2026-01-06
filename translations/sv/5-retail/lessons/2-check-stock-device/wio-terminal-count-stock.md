<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T22:19:35+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "sv"
}
-->
# Räkna lager från din IoT-enhet - Wio Terminal

En kombination av förutsägelser och deras begränsningsramar kan användas för att räkna lager i en bild.

## Räkna lager

![4 burkar tomatpuré med begränsningsramar runt varje burk](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.sv.jpg)

I bilden ovan har begränsningsramarna en liten överlappning. Om denna överlappning var mycket större, kan begränsningsramarna indikera samma objekt. För att räkna objekten korrekt behöver du ignorera ramar med en betydande överlappning.

### Uppgift - räkna lager och ignorera överlappning

1. Öppna ditt `stock-counter`-projekt om det inte redan är öppet.

1. Ovanför funktionen `processPredictions`, lägg till följande kod:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Detta definierar den procentuella överlappning som är tillåten innan begränsningsramarna anses vara samma objekt. 0.20 definierar en 20% överlappning.

1. Nedanför detta, och ovanför funktionen `processPredictions`, lägg till följande kod för att beräkna överlappningen mellan två rektanglar:

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

    Denna kod definierar en `Point`-struktur för att lagra punkter på bilden och en `Rect`-struktur för att definiera en rektangel med hjälp av en övre vänster och nedre höger koordinat. Den definierar sedan en `area`-funktion som beräknar arean av en rektangel från en övre vänster och nedre höger koordinat.

    Därefter definierar den en `overlappingArea`-funktion som beräknar överlappningsarean mellan två rektanglar. Om de inte överlappar returnerar den 0.

1. Nedanför funktionen `overlappingArea`, deklarera en funktion för att konvertera en begränsningsram till en `Rect`:

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

    Denna funktion tar en förutsägelse från objektidentifieraren, extraherar begränsningsramen och använder värdena från begränsningsramen för att definiera en rektangel. Den högra sidan beräknas från vänster plus bredden. Den nedre sidan beräknas som toppen plus höjden.

1. Förutsägelserna behöver jämföras med varandra, och om två förutsägelser har en överlappning som överstiger tröskelvärdet, måste en av dem tas bort. Överlappningströskeln är en procentandel, så den måste multipliceras med storleken på den minsta begränsningsramen för att kontrollera att överlappningen överstiger den angivna procentandelen av begränsningsramen, inte den angivna procentandelen av hela bilden. Börja med att ta bort innehållet i funktionen `processPredictions`.

1. Lägg till följande i den tomma funktionen `processPredictions`:

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

    Denna kod deklarerar en vektor för att lagra förutsägelser som inte överlappar. Den loopar sedan igenom alla förutsägelser och skapar en `Rect` från begränsningsramen.

    Därefter loopar denna kod igenom de återstående förutsägelserna, med start från den som kommer efter den aktuella förutsägelsen. Detta förhindrar att förutsägelser jämförs mer än en gång - när 1 och 2 har jämförts, finns det ingen anledning att jämföra 2 med 1, bara med 3, 4, etc.

    För varje par av förutsägelser beräknas överlappningsarean. Detta jämförs sedan med arean av den minsta begränsningsramen - om överlappningen överstiger tröskelvärdet för procentandelen av den minsta begränsningsramen, markeras förutsägelsen som inte godkänd. Om förutsägelsen klarar kontrollerna efter att alla överlappningar har jämförts, läggs den till i samlingen `passed_predictions`.

    > 💁 Detta är ett mycket enkelt sätt att ta bort överlappningar, där endast den första i ett överlappande par tas bort. För produktionskod skulle du vilja lägga till mer logik här, såsom att överväga överlappningar mellan flera objekt eller om en begränsningsram är helt innesluten av en annan.

1. Efter detta, lägg till följande kod för att skicka detaljer om de godkända förutsägelserna till den seriella monitorn:

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

    Denna kod loopar igenom de godkända förutsägelserna och skriver ut deras detaljer till den seriella monitorn.

1. Nedanför detta, lägg till kod för att skriva ut antalet räknade objekt till den seriella monitorn:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Detta kan sedan skickas till en IoT-tjänst för att varna om lagernivåerna är låga.

1. Ladda upp och kör din kod. Rikta kameran mot objekt på en hylla och tryck på C-knappen. Prova att justera värdet för `overlap_threshold` för att se förutsägelser ignoreras.

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

> 💁 Du kan hitta denna kod i mappen [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Ditt lagerräknarprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.