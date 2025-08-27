<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:52:39+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "nl"
}
-->
# Classificeer een afbeelding met een IoT Edge-gebaseerde afbeeldingsclassifier - Virtuele IoT-hardware en Raspberry Pi

In dit deel van de les ga je de Image Classifier gebruiken die draait op het IoT Edge-apparaat.

## Gebruik de IoT Edge-classifier

Het IoT-apparaat kan worden omgeleid om de IoT Edge-afbeeldingsclassifier te gebruiken. De URL voor de Image Classifier is `http://<IP adres of naam>/image`, waarbij `<IP adres of naam>` wordt vervangen door het IP-adres of de hostnaam van de computer waarop IoT Edge draait.

De Python-bibliotheek voor Custom Vision werkt alleen met cloud-gehoste modellen, niet met modellen die op IoT Edge worden gehost. Dit betekent dat je de REST API moet gebruiken om de classifier aan te roepen.

### Taak - gebruik de IoT Edge-classifier

1. Open het `fruit-quality-detector`-project in VS Code als het nog niet geopend is. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de virtuele omgeving is geactiveerd.

1. Open het bestand `app.py` en verwijder de importverklaringen van `azure.cognitiveservices.vision.customvision.prediction` en `msrest.authentication`.

1. Voeg de volgende import toe aan de bovenkant van het bestand:

    ```python
    import requests
    ```

1. Verwijder alle code na het opslaan van de afbeelding in een bestand, vanaf `image_file.write(image.read())` tot het einde van het bestand.

1. Voeg de volgende code toe aan het einde van het bestand:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Vervang `<URL>` door de URL van je classifier.

    Deze code maakt een REST POST-verzoek naar de classifier, waarbij de afbeelding wordt verzonden als de body van het verzoek. De resultaten komen terug als JSON, en deze worden gedecodeerd om de waarschijnlijkheden af te drukken.

1. Voer je code uit, met je camera gericht op wat fruit, een geschikte afbeeldingsset, of fruit zichtbaar op je webcam als je virtuele IoT-hardware gebruikt. Je ziet de uitvoer in de console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Je kunt deze code vinden in de map [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) of [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Je fruitkwaliteitsclassifierprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.