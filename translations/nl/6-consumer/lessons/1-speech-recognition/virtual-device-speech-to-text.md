<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T22:36:39+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "nl"
}
-->
# Spraak naar tekst - Virtueel IoT-apparaat

In dit deel van de les schrijf je code om spraak die via je microfoon wordt opgevangen om te zetten naar tekst met behulp van de spraakservice.

## Zet spraak om naar tekst

Op Windows, Linux en macOS kun je de Python SDK van de spraakservices gebruiken om naar je microfoon te luisteren en gedetecteerde spraak om te zetten naar tekst. De SDK luistert continu, detecteert het geluidsniveau en stuurt de spraak voor conversie naar tekst zodra het geluidsniveau daalt, bijvoorbeeld aan het einde van een spraakblok.

### Taak - spraak omzetten naar tekst

1. Maak een nieuwe Python-app op je computer in een map genaamd `smart-timer` met een enkel bestand genaamd `app.py` en een Python virtuele omgeving.

1. Installeer het Pip-pakket voor de spraakservices. Zorg ervoor dat je dit doet vanuit een terminal met de virtuele omgeving geactiveerd.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Als je de volgende foutmelding krijgt:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Dan moet je Pip updaten. Doe dit met het volgende commando en probeer het pakket opnieuw te installeren:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Voeg de volgende imports toe aan het bestand `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Hiermee importeer je enkele klassen die worden gebruikt om spraak te herkennen.

1. Voeg de volgende code toe om enkele configuraties te declareren:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Vervang `<key>` door de API-sleutel van je spraakservice. Vervang `<location>` door de locatie die je hebt gebruikt bij het aanmaken van de spraakserviceresource.

    Vervang `<language>` door de taalcode van de taal waarin je zult spreken, bijvoorbeeld `en-GB` voor Engels of `zn-HK` voor Kantonees. Je kunt een lijst met ondersteunde talen en hun taalcodes vinden in de [documentatie over taal- en stemondersteuning op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Deze configuratie wordt vervolgens gebruikt om een `SpeechConfig`-object te maken dat de spraakservices configureert.

1. Voeg de volgende code toe om een spraakherkenner te maken:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. De spraakherkenner draait op een achtergrondthread, luistert naar audio en zet gedetecteerde spraak om in tekst. Je kunt de tekst ophalen met een callbackfunctie - een functie die je definieert en doorgeeft aan de herkenner. Elke keer dat spraak wordt gedetecteerd, wordt de callback aangeroepen. Voeg de volgende code toe om een callback te definiëren en deze door te geven aan de herkenner, evenals een functie om de tekst te verwerken en deze naar de console te schrijven:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. De herkenner begint pas met luisteren wanneer je deze expliciet start. Voeg de volgende code toe om de herkenning te starten. Dit draait op de achtergrond, dus je applicatie heeft ook een oneindige lus nodig die slaapt om de applicatie draaiende te houden.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Voer deze app uit. Spreek in je microfoon en de audio die wordt omgezet naar tekst wordt weergegeven in de console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Probeer verschillende soorten zinnen, evenals zinnen waarin woorden hetzelfde klinken maar verschillende betekenissen hebben. Bijvoorbeeld, als je in het Engels spreekt, zeg dan 'I want to buy two bananas and an apple too', en merk op hoe het de juiste to, two en too gebruikt op basis van de context van het woord, niet alleen op basis van hoe het klinkt.

> 💁 Je kunt deze code vinden in de map [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Je spraak-naar-tekst-programma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, willen we u erop wijzen dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.