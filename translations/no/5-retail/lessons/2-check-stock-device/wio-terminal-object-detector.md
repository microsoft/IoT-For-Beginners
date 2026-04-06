# Kall objektgjenkjenneren fra IoT-enheten din - Wio Terminal

Når objektgjenkjenneren din er publisert, kan den brukes fra IoT-enheten din.

## Kopier bildegjenkjenner-prosjektet

Hoveddelen av lagerdetektoren din er den samme som bildegjenkjenneren du opprettet i en tidligere leksjon.

### Oppgave - kopier bildegjenkjenner-prosjektet

1. Koble ArduCam til Wio Terminal, ved å følge trinnene fra [leksjon 2 i produksjonsprosjektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Du kan også feste kameraet i en fast posisjon, for eksempel ved å henge kabelen over en boks eller en boks, eller feste kameraet til en boks med dobbeltsidig tape.

1. Opprett et helt nytt Wio Terminal-prosjekt ved hjelp av PlatformIO. Kall dette prosjektet `stock-counter`.

1. Gjenta trinnene fra [leksjon 2 i produksjonsprosjektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) for å ta bilder med kameraet.

1. Gjenta trinnene fra [leksjon 2 i produksjonsprosjektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) for å kalle bildegjenkjenneren. Hoveddelen av denne koden vil bli gjenbrukt for å oppdage objekter.

## Endre koden fra en gjenkjenner til en objektgjenkjenner

Koden du brukte for å klassifisere bilder er veldig lik koden for å oppdage objekter. Den største forskjellen er URL-en som kalles, som du fikk fra Custom Vision, og resultatene av kallet.

### Oppgave - endre koden fra en gjenkjenner til en objektgjenkjenner

1. Legg til følgende include-direktiv øverst i `main.cpp`-filen:

    ```cpp
    #include <vector>
    ```

1. Endre navnet på funksjonen `classifyImage` til `detectStock`, både navnet på funksjonen og kallet i funksjonen `buttonPressed`.

1. Over funksjonen `detectStock`, deklarer en terskelverdi for å filtrere ut deteksjoner med lav sannsynlighet:

    ```cpp
    const float threshold = 0.3f;
    ```

    I motsetning til en bildegjenkjenner som kun returnerer ett resultat per tag, vil objektgjenkjenneren returnere flere resultater, så de med lav sannsynlighet må filtreres ut.

1. Over funksjonen `detectStock`, deklarer en funksjon for å behandle prediksjonene:

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

    Denne tar en liste med prediksjoner og skriver dem ut til seriellmonitoren.

1. I funksjonen `detectStock`, erstatt innholdet i `for`-løkka som går gjennom prediksjonene med følgende:

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

    Denne løkker gjennom prediksjonene og sammenligner sannsynligheten med terskelverdien. Alle prediksjoner med en sannsynlighet høyere enn terskelverdien legges til en `list` og sendes til funksjonen `processPredictions`.

1. Last opp og kjør koden din. Rett kameraet mot objekter på en hylle og trykk på C-knappen. Du vil se resultatene i seriellmonitoren:

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

    > 💁 Du kan trenge å justere `threshold` til en passende verdi for bildene dine.

    Du vil kunne se bildet som ble tatt, og disse verdiene i **Predictions**-fanen i Custom Vision.

    ![4 bokser med tomatpuré på en hylle med prediksjoner for de 4 deteksjonene på 35,8 %, 33,5 %, 25,7 % og 16,6 %](../../../../../translated_images/no/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Du finner denne koden i [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal)-mappen.

😀 Lagerdetektor-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.