<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:39:09+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "da"
}
-->
# Klassificér et billede ved hjælp af en IoT Edge-baseret billedklassificering - Virtuel IoT-hardware og Raspberry Pi

I denne del af lektionen vil du bruge billedklassificeringen, der kører på IoT Edge-enheden.

## Brug IoT Edge-klassificeringen

IoT-enheden kan omdirigeres til at bruge IoT Edge-billedklassificeringen. URL'en til billedklassificeringen er `http://<IP address or name>/image`, hvor `<IP address or name>` erstattes med IP-adressen eller værtsnavnet på computeren, der kører IoT Edge.

Python-biblioteket til Custom Vision fungerer kun med modeller, der er hostet i skyen, ikke med modeller hostet på IoT Edge. Det betyder, at du skal bruge REST API'en til at kalde klassificeringen.

### Opgave - brug IoT Edge-klassificeringen

1. Åbn projektet `fruit-quality-detector` i VS Code, hvis det ikke allerede er åbent. Hvis du bruger en virtuel IoT-enhed, skal du sørge for, at det virtuelle miljø er aktiveret.

1. Åbn filen `app.py`, og fjern import-udsagnene fra `azure.cognitiveservices.vision.customvision.prediction` og `msrest.authentication`.

1. Tilføj følgende import øverst i filen:

    ```python
    import requests
    ```

1. Slet al koden efter, at billedet er gemt i en fil, fra `image_file.write(image.read())` til slutningen af filen.

1. Tilføj følgende kode til slutningen af filen:

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

    Erstat `<URL>` med URL'en til din klassificering.

    Denne kode laver en REST POST-anmodning til klassificeringen og sender billedet som body i anmodningen. Resultaterne kommer tilbage som JSON, og dette dekodes for at udskrive sandsynlighederne.

1. Kør din kode, mens dit kamera peger på noget frugt, et passende billedsæt eller frugt, der er synligt på dit webcam, hvis du bruger virtuel IoT-hardware. Du vil se outputtet i konsollen:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Du kan finde denne kode i mappen [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) eller [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Dit program til klassificering af frugtkvalitet var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.