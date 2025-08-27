<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:38:59+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "sv"
}
-->
# Klassificera en bild med en IoT Edge-baserad bildklassificerare - Virtuell IoT-hårdvara och Raspberry Pi

I den här delen av lektionen kommer du att använda bildklassificeraren som körs på IoT Edge-enheten.

## Använd IoT Edge-klassificeraren

IoT-enheten kan omdirigeras för att använda IoT Edge-bildklassificeraren. URL:en för bildklassificeraren är `http://<IP address or name>/image`, där `<IP address or name>` ersätts med IP-adressen eller värdnamnet för datorn som kör IoT Edge.

Python-biblioteket för Custom Vision fungerar endast med molnhostade modeller, inte med modeller som är hostade på IoT Edge. Detta innebär att du måste använda REST API för att anropa klassificeraren.

### Uppgift - använd IoT Edge-klassificeraren

1. Öppna projektet `fruit-quality-detector` i VS Code om det inte redan är öppet. Om du använder en virtuell IoT-enhet, se till att den virtuella miljön är aktiverad.

1. Öppna filen `app.py` och ta bort import-satserna från `azure.cognitiveservices.vision.customvision.prediction` och `msrest.authentication`.

1. Lägg till följande import högst upp i filen:

    ```python
    import requests
    ```

1. Ta bort all kod efter att bilden sparas till en fil, från `image_file.write(image.read())` till slutet av filen.

1. Lägg till följande kod i slutet av filen:

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

    Ersätt `<URL>` med URL:en för din klassificerare.

    Den här koden gör en REST POST-förfrågan till klassificeraren och skickar bilden som kropp i förfrågan. Resultaten kommer tillbaka som JSON, och detta avkodas för att skriva ut sannolikheterna.

1. Kör din kod, med kameran riktad mot någon frukt, en lämplig bilduppsättning, eller frukt som är synlig på din webbkamera om du använder virtuell IoT-hårdvara. Du kommer att se resultatet i konsolen:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Du kan hitta denna kod i mappen [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) eller [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Ditt program för att klassificera fruktkvalitet blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.