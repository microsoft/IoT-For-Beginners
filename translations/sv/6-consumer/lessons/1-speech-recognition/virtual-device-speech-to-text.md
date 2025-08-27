<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T21:05:09+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "sv"
}
-->
# Tal till text - Virtuell IoT-enhet

I den här delen av lektionen kommer du att skriva kod för att omvandla tal som fångas från din mikrofon till text med hjälp av tal-tjänsten.

## Omvandla tal till text

På Windows, Linux och macOS kan Python SDK för tal-tjänster användas för att lyssna på din mikrofon och omvandla detekterat tal till text. Den lyssnar kontinuerligt, detekterar ljudnivåer och skickar talet för omvandling till text när ljudnivån sjunker, till exempel i slutet av ett talblock.

### Uppgift - omvandla tal till text

1. Skapa en ny Python-app på din dator i en mapp som heter `smart-timer` med en enda fil som heter `app.py` och en virtuell Python-miljö.

1. Installera Pip-paketet för tal-tjänster. Se till att du installerar detta från en terminal där den virtuella miljön är aktiverad.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Om du får följande fel:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Behöver du uppdatera Pip. Gör detta med följande kommando och försök sedan installera paketet igen:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Lägg till följande imports i filen `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Detta importerar några klasser som används för att känna igen tal.

1. Lägg till följande kod för att deklarera viss konfiguration:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Ersätt `<key>` med API-nyckeln för din tal-tjänst. Ersätt `<location>` med platsen du använde när du skapade resursen för tal-tjänsten.

    Ersätt `<language>` med lokalnamnet för det språk du kommer att tala, till exempel `en-GB` för engelska eller `zn-HK` för kantonesiska. Du kan hitta en lista över de språk som stöds och deras lokalnamn i [dokumentationen om språk- och röststöd på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Denna konfiguration används sedan för att skapa ett `SpeechConfig`-objekt som kommer att användas för att konfigurera tal-tjänsterna.

1. Lägg till följande kod för att skapa en taligenkännare:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Taligenkännaren körs på en bakgrundstråd, lyssnar efter ljud och omvandlar allt tal i det till text. Du kan få texten med hjälp av en callback-funktion - en funktion som du definierar och skickar till igenkännaren. Varje gång tal detekteras anropas callback-funktionen. Lägg till följande kod för att definiera en callback och skicka denna callback till igenkännaren, samt definiera en funktion för att bearbeta texten och skriva ut den i konsolen:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Igenkännaren börjar bara lyssna när du uttryckligen startar den. Lägg till följande kod för att starta igenkänningen. Detta körs i bakgrunden, så din applikation behöver också en oändlig loop som sover för att hålla applikationen igång.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Kör denna app. Tala in i din mikrofon och det ljud som omvandlas till text kommer att skrivas ut i konsolen.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Testa olika typer av meningar, tillsammans med meningar där ord låter lika men har olika betydelser. Till exempel, om du talar engelska, säg "I want to buy two bananas and an apple too", och notera hur den använder rätt "to", "two" och "too" baserat på ordets kontext, inte bara dess ljud.

> 💁 Du kan hitta denna kod i mappen [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Ditt tal-till-text-program blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.