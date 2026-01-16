<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T22:20:07+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "no"
}
-->
# Tell antall varer fra din IoT-enhet - Wio Terminal

En kombinasjon av prediksjonene og deres avgrensningsbokser kan brukes til å telle varer i et bilde.

## Tell varer

![4 bokser med tomatpuré med avgrensningsbokser rundt hver boks](../../../../../translated_images/no/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

I bildet vist ovenfor har avgrensningsboksene en liten overlapping. Hvis denne overlappingen var mye større, kunne avgrensningsboksene indikert det samme objektet. For å telle objektene riktig, må du ignorere bokser med betydelig overlapping.

### Oppgave - tell varer og ignorer overlapping

1. Åpne prosjektet ditt `stock-counter` hvis det ikke allerede er åpent.

1. Over funksjonen `processPredictions`, legg til følgende kode:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Dette definerer prosentandelen overlapping som er tillatt før avgrensningsboksene anses som det samme objektet. 0.20 definerer en 20% overlapping.

1. Under dette, og over funksjonen `processPredictions`, legg til følgende kode for å beregne overlappingen mellom to rektangler:

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

    Denne koden definerer en `Point`-struktur for å lagre punkter på bildet, og en `Rect`-struktur for å definere et rektangel ved hjelp av en øvre venstre og nedre høyre koordinat. Deretter defineres en `area`-funksjon som beregner arealet av et rektangel fra en øvre venstre og nedre høyre koordinat.

    Deretter defineres en `overlappingArea`-funksjon som beregner det overlappende arealet av 2 rektangler. Hvis de ikke overlapper, returnerer den 0.

1. Under funksjonen `overlappingArea`, deklarer en funksjon for å konvertere en avgrensningsboks til en `Rect`:

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

    Denne tar en prediksjon fra objektgjenkjenneren, henter ut avgrensningsboksen og bruker verdiene fra avgrensningsboksen til å definere et rektangel. Høyre side beregnes fra venstre pluss bredden. Bunnen beregnes som toppen pluss høyden.

1. Prediksjonene må sammenlignes med hverandre, og hvis 2 prediksjoner har en overlapping som overstiger terskelen, må en av dem fjernes. Overlappingsterskelen er en prosentandel, så den må multipliseres med størrelsen på den minste avgrensningsboksen for å sjekke at overlappingen overstiger den gitte prosentandelen av avgrensningsboksen, ikke den gitte prosentandelen av hele bildet. Start med å slette innholdet i funksjonen `processPredictions`.

1. Legg til følgende i den tomme funksjonen `processPredictions`:

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

    Denne koden deklarerer en vektor for å lagre prediksjonene som ikke overlapper. Den går deretter gjennom alle prediksjonene og oppretter en `Rect` fra avgrensningsboksen.

    Deretter går denne koden gjennom de gjenværende prediksjonene, og starter med den som kommer etter den nåværende prediksjonen. Dette hindrer at prediksjoner sammenlignes mer enn én gang - når 1 og 2 er sammenlignet, er det ikke nødvendig å sammenligne 2 med 1, bare med 3, 4, osv.

    For hvert par av prediksjoner beregnes det overlappende arealet. Dette sammenlignes deretter med arealet av den minste avgrensningsboksen - hvis overlappingen overstiger terskelprosenten av den minste avgrensningsboksen, markeres prediksjonen som ikke bestått. Hvis prediksjonen består sjekkene etter å ha sammenlignet all overlapping, legges den til i samlingen `passed_predictions`.

    > 💁 Dette er en veldig enkel måte å fjerne overlappinger på, ved bare å fjerne den første i et overlappende par. For produksjonskode bør du legge til mer logikk her, som å vurdere overlappinger mellom flere objekter, eller om én avgrensningsboks er inneholdt av en annen.

1. Etter dette, legg til følgende kode for å sende detaljer om de beståtte prediksjonene til den serielle monitoren:

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

    Denne koden går gjennom de beståtte prediksjonene og skriver ut detaljene deres til den serielle monitoren.

1. Under dette, legg til kode for å skrive ut antall tellte objekter til den serielle monitoren:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Dette kan deretter sendes til en IoT-tjeneste for å varsle hvis lagerbeholdningen er lav.

1. Last opp og kjør koden din. Rett kameraet mot objekter på en hylle og trykk på C-knappen. Prøv å justere verdien `overlap_threshold` for å se prediksjoner bli ignorert.

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

> 💁 Du finner denne koden i mappen [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Programmet ditt for telling av varer var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.