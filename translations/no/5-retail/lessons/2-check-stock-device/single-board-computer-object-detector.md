<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T22:21:09+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "no"
}
-->
# Kall objekt-detektoren fra IoT-enheten din - Virtuell IoT-maskinvare og Raspberry Pi

Når objekt-detektoren din er publisert, kan den brukes fra IoT-enheten din.

## Kopier bildekategoriseringsprosjektet

Hoveddelen av lagerdetektoren din er den samme som bildekategoriseringen du opprettet i en tidligere leksjon.

### Oppgave - kopier bildekategoriseringsprosjektet

1. Opprett en mappe kalt `stock-counter` enten på datamaskinen din hvis du bruker en virtuell IoT-enhet, eller på din Raspberry Pi. Hvis du bruker en virtuell IoT-enhet, sørg for å sette opp et virtuelt miljø.

1. Sett opp kameramaskinvaren.

    * Hvis du bruker en Raspberry Pi, må du montere PiCamera. Du kan også ønske å feste kameraet i en fast posisjon, for eksempel ved å henge kabelen over en boks eller en boks, eller feste kameraet til en boks med dobbeltsidig tape.
    * Hvis du bruker en virtuell IoT-enhet, må du installere CounterFit og CounterFit PyCamera shim. Hvis du skal bruke stillbilder, ta noen bilder som objekt-detektoren din ikke har sett før. Hvis du skal bruke webkameraet ditt, sørg for at det er plassert slik at det kan se lageret du skal detektere.

1. Gjenta trinnene fra [leksjon 2 i produksjonsprosjektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) for å ta bilder med kameraet.

1. Gjenta trinnene fra [leksjon 2 i produksjonsprosjektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) for å kalle bildekategoriseringen. Mesteparten av denne koden vil bli gjenbrukt for å detektere objekter.

## Endre koden fra en kategorisering til en objekt-detektor

Koden du brukte for å kategorisere bilder er veldig lik koden for å detektere objekter. Den største forskjellen er metoden som kalles på Custom Vision SDK, og resultatene av kallet.

### Oppgave - endre koden fra en kategorisering til en objekt-detektor

1. Slett de tre linjene med kode som kategoriserer bildet og behandler prediksjonene:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Fjern disse tre linjene.

1. Legg til følgende kode for å detektere objekter i bildet:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Denne koden kaller `detect_image`-metoden på prediktoren for å kjøre objekt-detektoren. Den samler deretter alle prediksjonene med en sannsynlighet over en terskelverdi og skriver dem ut til konsollen.

    I motsetning til en bildekategorisering som bare returnerer ett resultat per tag, vil objekt-detektoren returnere flere resultater, så de med lav sannsynlighet må filtreres ut.

1. Kjør denne koden, og den vil ta et bilde, sende det til objekt-detektoren, og skrive ut de detekterte objektene. Hvis du bruker en virtuell IoT-enhet, sørg for at du har et passende bilde satt i CounterFit, eller at webkameraet ditt er valgt. Hvis du bruker en Raspberry Pi, sørg for at kameraet ditt peker mot objekter på en hylle.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Du må kanskje justere `threshold` til en passende verdi for bildene dine.

    Du vil kunne se bildet som ble tatt, og disse verdiene i **Predictions**-fanen i Custom Vision.

    ![4 bokser med tomatpuré på en hylle med prediksjoner for de 4 deteksjonene på 35.8%, 33.5%, 25.7% og 16.6%](../../../../../translated_images/no/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Du finner denne koden i [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) eller [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device)-mappen.

😀 Lager-teller-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vennligst vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.