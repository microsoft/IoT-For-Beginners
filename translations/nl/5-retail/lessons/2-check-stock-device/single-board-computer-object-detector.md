<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T20:26:57+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "nl"
}
-->
# Roep je objectdetector aan vanaf je IoT-apparaat - Virtuele IoT-hardware en Raspberry Pi

Zodra je objectdetector is gepubliceerd, kan deze worden gebruikt vanaf je IoT-apparaat.

## Kopieer het beeldclassificatieproject

Het grootste deel van je voorraaddetector is hetzelfde als de beeldclassificator die je in een eerdere les hebt gemaakt.

### Taak - kopieer het beeldclassificatieproject

1. Maak een map genaamd `stock-counter` op je computer als je een virtueel IoT-apparaat gebruikt, of op je Raspberry Pi. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat je een virtuele omgeving instelt.

1. Stel de camerahardware in.

    * Als je een Raspberry Pi gebruikt, moet je de PiCamera aansluiten. Je wilt de camera mogelijk ook in een vaste positie plaatsen, bijvoorbeeld door de kabel over een doos of blik te hangen, of de camera met dubbelzijdige tape aan een doos te bevestigen.
    * Als je een virtueel IoT-apparaat gebruikt, moet je CounterFit en de CounterFit PyCamera shim installeren. Als je stilstaande beelden gaat gebruiken, maak dan enkele foto's die je objectdetector nog niet heeft gezien. Als je een webcam gaat gebruiken, zorg er dan voor dat deze zo is gepositioneerd dat hij de voorraad kan zien die je wilt detecteren.

1. Herhaal de stappen uit [les 2 van het productieproject](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) om beelden vast te leggen met de camera.

1. Herhaal de stappen uit [les 2 van het productieproject](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) om de beeldclassificator aan te roepen. Het grootste deel van deze code zal worden hergebruikt om objecten te detecteren.

## Wijzig de code van een classificator naar een objectdetector

De code die je gebruikte om beelden te classificeren lijkt sterk op de code om objecten te detecteren. Het belangrijkste verschil is de methode die wordt aangeroepen in de Custom Vision SDK en de resultaten van de aanroep.

### Taak - wijzig de code van een classificator naar een objectdetector

1. Verwijder de drie regels code die het beeld classificeert en de voorspellingen verwerkt:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Verwijder deze drie regels.

1. Voeg de volgende code toe om objecten in het beeld te detecteren:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Deze code roept de methode `detect_image` aan op de predictor om de objectdetector uit te voeren. Vervolgens verzamelt het alle voorspellingen met een waarschijnlijkheid boven een bepaalde drempel en print deze naar de console.

    In tegenstelling tot een beeldclassificator, die slechts één resultaat per tag retourneert, geeft de objectdetector meerdere resultaten terug. Voorspellingen met een lage waarschijnlijkheid moeten daarom worden gefilterd.

1. Voer deze code uit. Het zal een beeld vastleggen, dit naar de objectdetector sturen en de gedetecteerde objecten afdrukken. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat je een geschikt beeld hebt ingesteld in CounterFit, of dat je webcam is geselecteerd. Als je een Raspberry Pi gebruikt, zorg er dan voor dat je camera gericht is op objecten op een plank.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Mogelijk moet je de `threshold` aanpassen aan een geschikte waarde voor jouw beelden.

    Je kunt het vastgelegde beeld en deze waarden bekijken in het tabblad **Predictions** in Custom Vision.

    ![4 blikken tomatenpuree op een plank met voorspellingen voor de 4 detecties van 35,8%, 33,5%, 25,7% en 16,6%](../../../../../translated_images/nl/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Je kunt deze code vinden in de map [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) of [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Je voorraadtelprogramma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.