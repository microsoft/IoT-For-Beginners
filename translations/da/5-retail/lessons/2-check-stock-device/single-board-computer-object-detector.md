# Kald din objektdetektor fra din IoT-enhed - Virtuel IoT-hardware og Raspberry Pi

Når din objektdetektor er blevet publiceret, kan den bruges fra din IoT-enhed.

## Kopiér billedklassificeringsprojektet

Størstedelen af din lagerdetektor er den samme som billedklassificeringen, du oprettede i en tidligere lektion.

### Opgave - kopiér billedklassificeringsprojektet

1. Opret en mappe kaldet `stock-counter` enten på din computer, hvis du bruger en virtuel IoT-enhed, eller på din Raspberry Pi. Hvis du bruger en virtuel IoT-enhed, skal du sørge for at opsætte et virtuelt miljø.

1. Opsæt kamera-hardwaren.

    * Hvis du bruger en Raspberry Pi, skal du montere PiCamera. Du vil måske også fastgøre kameraet i en fast position, for eksempel ved at hænge kablet over en kasse eller dåse, eller fastgøre kameraet til en kasse med dobbeltklæbende tape.
    * Hvis du bruger en virtuel IoT-enhed, skal du installere CounterFit og CounterFit PyCamera shim. Hvis du planlægger at bruge stillbilleder, skal du tage nogle billeder, som din objektdetektor ikke har set før. Hvis du planlægger at bruge dit webkamera, skal du sørge for, at det er placeret, så det kan se det lager, du vil detektere.

1. Gentag trinnene fra [lektion 2 i produktionsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) for at tage billeder med kameraet.

1. Gentag trinnene fra [lektion 2 i produktionsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) for at kalde billedklassificeringen. Størstedelen af denne kode vil blive genbrugt til at detektere objekter.

## Ændr koden fra en klassificering til en billeddetektor

Koden, du brugte til at klassificere billeder, ligner meget koden til at detektere objekter. Den største forskel er metoden, der kaldes på Custom Vision SDK, og resultaterne af kaldet.

### Opgave - ændr koden fra en klassificering til en billeddetektor

1. Slet de tre linjer kode, der klassificerer billedet og behandler forudsigelserne:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Fjern disse tre linjer.

1. Tilføj følgende kode for at detektere objekter i billedet:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Denne kode kalder `detect_image`-metoden på prediktoren for at køre objektdetektoren. Den samler derefter alle forudsigelser med en sandsynlighed over en tærskelværdi og udskriver dem til konsollen.

    I modsætning til en billedklassificering, der kun returnerer ét resultat pr. tag, vil objektdetektoren returnere flere resultater, så dem med en lav sandsynlighed skal filtreres fra.

1. Kør denne kode, og den vil tage et billede, sende det til objektdetektoren og udskrive de detekterede objekter. Hvis du bruger en virtuel IoT-enhed, skal du sikre dig, at du har et passende billede indstillet i CounterFit, eller at dit webkamera er valgt. Hvis du bruger en Raspberry Pi, skal du sørge for, at dit kamera peger på objekter på en hylde.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Du skal muligvis justere `threshold` til en passende værdi for dine billeder.

    Du vil kunne se det billede, der blev taget, og disse værdier i **Predictions**-fanen i Custom Vision.

    ![4 dåser tomatpuré på en hylde med forudsigelser for de 4 detektioner på 35,8%, 33,5%, 25,7% og 16,6%](../../../../../translated_images/da/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Du kan finde denne kode i mappen [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) eller [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Dit lageroptællingsprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.