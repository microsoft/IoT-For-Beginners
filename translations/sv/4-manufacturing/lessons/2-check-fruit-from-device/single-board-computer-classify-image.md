<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T20:46:03+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "sv"
}
-->
# Klassificera en bild - Virtuell IoT-hårdvara och Raspberry Pi

I den här delen av lektionen kommer du att skicka bilden som kameran har tagit till Custom Vision-tjänsten för att klassificera den.

## Skicka bilder till Custom Vision

Custom Vision-tjänsten har ett Python SDK som du kan använda för att klassificera bilder.

### Uppgift - skicka bilder till Custom Vision

1. Öppna mappen `fruit-quality-detector` i VS Code. Om du använder en virtuell IoT-enhet, se till att den virtuella miljön körs i terminalen.

1. Python SDK för att skicka bilder till Custom Vision finns som ett Pip-paket. Installera det med följande kommando:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Lägg till följande import-satser högst upp i filen `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Detta importerar några moduler från Custom Vision-biblioteken, en för att autentisera med prediktionsnyckeln och en för att tillhandahålla en klientklass för prediktion som kan anropa Custom Vision.

1. Lägg till följande kod i slutet av filen:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Ersätt `<prediction_url>` med URL:en du kopierade från dialogrutan *Prediction URL* tidigare i lektionen. Ersätt `<prediction key>` med prediktionsnyckeln du kopierade från samma dialogruta.

1. Prediktions-URL:en som tillhandahölls av dialogrutan *Prediction URL* är utformad för att användas när REST-slutpunkten anropas direkt. Python SDK använder delar av URL:en på olika platser. Lägg till följande kod för att dela upp denna URL i de delar som behövs:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Detta delar upp URL:en och extraherar slutpunkten `https://<location>.api.cognitive.microsoft.com`, projekt-ID och namnet på den publicerade iterationen.

1. Skapa ett predictor-objekt för att utföra prediktionen med följande kod:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` omsluter prediktionsnyckeln. Dessa används sedan för att skapa ett klientobjekt för prediktion som pekar på slutpunkten.

1. Skicka bilden till Custom Vision med följande kod:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Detta spolar tillbaka bilden till början och skickar den sedan till prediktionsklienten.

1. Visa slutligen resultaten med följande kod:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Detta kommer att loopa igenom alla prediktioner som har returnerats och visa dem i terminalen. De sannolikheter som returneras är flyttal mellan 0-1, där 0 motsvarar 0% chans att matcha taggen och 1 motsvarar 100% chans.

    > 💁 Bildklassificerare kommer att returnera procentandelar för alla taggar som har använts. Varje tagg kommer att ha en sannolikhet att bilden matchar den taggen.

1. Kör din kod, med kameran riktad mot någon frukt, eller en lämplig bilduppsättning, eller frukt som är synlig på din webbkamera om du använder virtuell IoT-hårdvara. Du kommer att se resultatet i konsolen:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Du kommer att kunna se bilden som togs, och dessa värden i fliken **Predictions** i Custom Vision.

    ![En banan i Custom Vision förutspådd som mogen med 56,8% och omogen med 43,1%](../../../../../translated_images/sv/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Du kan hitta denna kod i mappen [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) eller [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Ditt program för att klassificera fruktkvalitet blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.