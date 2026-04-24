# Kald din objektdetektor fra din IoT-enhed - Wio Terminal

Når din objektdetektor er blevet offentliggjort, kan den bruges fra din IoT-enhed.

## Kopiér billedklassifikationsprojektet

Størstedelen af din lagerdetektor er den samme som billedklassifikatoren, du oprettede i en tidligere lektion.

### Opgave - kopiér billedklassifikationsprojektet

1. Tilslut din ArduCam til din Wio Terminal ved at følge trinnene fra [lektion 2 i produktionsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Du kan også vælge at fastgøre kameraet i en fast position, for eksempel ved at hænge kablet over en kasse eller dåse, eller ved at fastgøre kameraet til en kasse med dobbeltklæbende tape.

1. Opret et helt nyt Wio Terminal-projekt ved hjælp af PlatformIO. Kald dette projekt `stock-counter`.

1. Gentag trinnene fra [lektion 2 i produktionsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) for at tage billeder med kameraet.

1. Gentag trinnene fra [lektion 2 i produktionsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) for at kalde billedklassifikatoren. Størstedelen af denne kode vil blive genbrugt til at detektere objekter.

## Ændr koden fra en klassifikator til en billeddetektor

Den kode, du brugte til at klassificere billeder, ligner meget koden til at detektere objekter. Den største forskel er URL'en, der kaldes, som du fik fra Custom Vision, og resultaterne af kaldet.

### Opgave - ændr koden fra en klassifikator til en billeddetektor

1. Tilføj følgende include-direktiv øverst i `main.cpp`-filen:

    ```cpp
    #include <vector>
    ```

1. Omdøb funktionen `classifyImage` til `detectStock`, både navnet på funktionen og kaldet i funktionen `buttonPressed`.

1. Over funktionen `detectStock`, deklarer en tærskelværdi for at filtrere eventuelle detektioner med lav sandsynlighed:

    ```cpp
    const float threshold = 0.3f;
    ```

    I modsætning til en billedklassifikator, der kun returnerer ét resultat pr. tag, vil objektdetektoren returnere flere resultater, så dem med lav sandsynlighed skal filtreres fra.

1. Over funktionen `detectStock`, deklarer en funktion til at behandle forudsigelserne:

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

    Denne funktion tager en liste over forudsigelser og udskriver dem til den serielle monitor.

1. I funktionen `detectStock`, erstat indholdet af `for`-løkken, der gennemgår forudsigelserne, med følgende:

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

    Denne løkke gennemgår forudsigelserne og sammenligner sandsynligheden med tærskelværdien. Alle forudsigelser med en sandsynlighed højere end tærskelværdien tilføjes til en `list` og sendes til funktionen `processPredictions`.

1. Upload og kør din kode. Peg kameraet mod objekter på en hylde og tryk på C-knappen. Du vil se outputtet i den serielle monitor:

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

    > 💁 Du kan være nødt til at justere `threshold` til en passende værdi for dine billeder.

    Du vil kunne se det billede, der blev taget, og disse værdier i **Predictions**-fanen i Custom Vision.

    ![4 dåser tomatpuré på en hylde med forudsigelser for de 4 detektioner på 35,8%, 33,5%, 25,7% og 16,6%](../../../../../translated_images/da/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Du kan finde denne kode i mappen [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Dit lageroptællingsprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.