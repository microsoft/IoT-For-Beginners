<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T20:42:19+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "nl"
}
-->
# Classificeer een afbeelding - Virtuele IoT-hardware en Raspberry Pi

In dit deel van de les stuur je de afbeelding die door de camera is vastgelegd naar de Custom Vision-service om deze te classificeren.

## Afbeeldingen verzenden naar Custom Vision

De Custom Vision-service heeft een Python SDK die je kunt gebruiken om afbeeldingen te classificeren.

### Taak - afbeeldingen verzenden naar Custom Vision

1. Open de map `fruit-quality-detector` in VS Code. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de virtuele omgeving actief is in de terminal.

1. De Python SDK om afbeeldingen naar Custom Vision te verzenden is beschikbaar als een Pip-pakket. Installeer het met de volgende opdracht:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Voeg de volgende importverklaringen toe bovenaan het bestand `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Hiermee worden enkele modules uit de Custom Vision-bibliotheken geïmporteerd, één om te authenticeren met de voorspellingssleutel, en één om een voorspelling-clientklasse te bieden die Custom Vision kan aanroepen.

1. Voeg de volgende code toe aan het einde van het bestand:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Vervang `<prediction_url>` door de URL die je eerder in deze les hebt gekopieerd uit het *Prediction URL*-dialoogvenster. Vervang `<prediction key>` door de voorspellingssleutel die je uit hetzelfde dialoogvenster hebt gekopieerd.

1. De voorspellings-URL die werd verstrekt door het *Prediction URL*-dialoogvenster is ontworpen om rechtstreeks te worden gebruikt bij het aanroepen van de REST-endpoint. De Python SDK gebruikt delen van de URL op verschillende plaatsen. Voeg de volgende code toe om deze URL op te splitsen in de benodigde delen:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Hiermee wordt de URL opgesplitst, waarbij de endpoint `https://<location>.api.cognitive.microsoft.com`, het project-ID en de naam van de gepubliceerde iteratie worden geëxtraheerd.

1. Maak een predictor-object om de voorspelling uit te voeren met de volgende code:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    De `prediction_credentials` omhullen de voorspellingssleutel. Deze worden vervolgens gebruikt om een voorspelling-clientobject te maken dat naar de endpoint wijst.

1. Verstuur de afbeelding naar Custom Vision met de volgende code:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Hiermee wordt de afbeelding teruggespoeld naar het begin en vervolgens naar de voorspelling-client verzonden.

1. Toon ten slotte de resultaten met de volgende code:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Hiermee wordt door alle voorspellingen gelopen die zijn geretourneerd en worden ze weergegeven in de terminal. De geretourneerde waarschijnlijkheden zijn drijvende getallen van 0-1, waarbij 0 een kans van 0% aangeeft dat de tag overeenkomt, en 1 een kans van 100%.

    > 💁 Afbeeldingsclassificeerders retourneren de percentages voor alle tags die zijn gebruikt. Elke tag heeft een waarschijnlijkheid dat de afbeelding overeenkomt met die tag.

1. Voer je code uit, met je camera gericht op wat fruit, of een geschikte afbeeldingsset, of fruit zichtbaar op je webcam als je virtuele IoT-hardware gebruikt. Je ziet de uitvoer in de console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Je kunt de afbeelding zien die is gemaakt, en deze waarden in het tabblad **Predictions** in Custom Vision.

    ![Een banaan in Custom Vision voorspeld rijp met 56,8% en onrijp met 43,1%](../../../../../translated_images/nl/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Je kunt deze code vinden in de map [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) of [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Je fruitkwaliteitsclassificatieprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.