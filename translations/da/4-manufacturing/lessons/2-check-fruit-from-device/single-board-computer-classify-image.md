<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T20:46:19+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "da"
}
-->
# Klassificér et billede - Virtuel IoT-hardware og Raspberry Pi

I denne del af lektionen vil du sende det billede, som kameraet har taget, til Custom Vision-tjenesten for at klassificere det.

## Send billeder til Custom Vision

Custom Vision-tjenesten har et Python SDK, som du kan bruge til at klassificere billeder.

### Opgave - send billeder til Custom Vision

1. Åbn mappen `fruit-quality-detector` i VS Code. Hvis du bruger en virtuel IoT-enhed, skal du sikre dig, at det virtuelle miljø kører i terminalen.

1. Python SDK'et til at sende billeder til Custom Vision er tilgængeligt som en Pip-pakke. Installer det med følgende kommando:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Tilføj følgende import-udsagn øverst i filen `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Dette importerer nogle moduler fra Custom Vision-bibliotekerne, et til at autentificere med predictions-nøglen, og et til at levere en predictions-klientklasse, der kan kalde Custom Vision.

1. Tilføj følgende kode til slutningen af filen:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Erstat `<prediction_url>` med den URL, du kopierede fra dialogboksen *Prediction URL* tidligere i denne lektion. Erstat `<prediction key>` med predictions-nøglen, du kopierede fra samme dialog.

1. Den predictions-URL, der blev leveret af dialogboksen *Prediction URL*, er designet til at blive brugt, når REST-endpointet kaldes direkte. Python SDK'et bruger dele af URL'en forskellige steder. Tilføj følgende kode for at opdele denne URL i de nødvendige dele:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Dette opdeler URL'en og udtrækker endpointet `https://<location>.api.cognitive.microsoft.com`, projekt-ID'et og navnet på den publicerede iteration.

1. Opret et predictor-objekt til at udføre predictions med følgende kode:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` indkapsler predictions-nøglen. Disse bruges derefter til at oprette et predictions-klientobjekt, der peger på endpointet.

1. Send billedet til Custom Vision ved hjælp af følgende kode:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Dette spoler billedet tilbage til starten og sender det derefter til predictions-klienten.

1. Vis til sidst resultaterne med følgende kode:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Dette vil gennemløbe alle de predictions, der er blevet returneret, og vise dem i terminalen. De sandsynligheder, der returneres, er flydende tal fra 0-1, hvor 0 er 0% chance for at matche tagget, og 1 er 100% chance.

    > 💁 Billedklassifikatorer vil returnere procentdelene for alle tags, der er blevet brugt. Hvert tag vil have en sandsynlighed for, at billedet matcher det tag.

1. Kør din kode, med dit kamera pegende på noget frugt, eller et passende billedsæt, eller frugt synligt på dit webcam, hvis du bruger virtuel IoT-hardware. Du vil se outputtet i konsollen:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Du vil kunne se det billede, der blev taget, og disse værdier i fanen **Predictions** i Custom Vision.

    ![En banan i Custom Vision forudsagt som moden med 56,8% og umoden med 43,1%](../../../../../translated_images/da/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Du kan finde denne kode i mappen [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) eller [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Dit program til klassificering af frugtkvalitet var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.