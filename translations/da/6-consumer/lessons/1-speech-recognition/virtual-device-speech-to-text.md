<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T21:05:25+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "da"
}
-->
# Tale til tekst - Virtuel IoT-enhed

I denne del af lektionen vil du skrive kode til at konvertere tale, der er optaget fra din mikrofon, til tekst ved hjælp af tale-tjenesten.

## Konverter tale til tekst

På Windows, Linux og macOS kan Python SDK for tale-tjenester bruges til at lytte til din mikrofon og konvertere enhver registreret tale til tekst. Den lytter kontinuerligt, registrerer lydniveauer og sender talen til konvertering til tekst, når lydniveauet falder, f.eks. ved afslutningen af en taleblok.

### Opgave - konverter tale til tekst

1. Opret en ny Python-app på din computer i en mappe kaldet `smart-timer` med en enkelt fil kaldet `app.py` og et Python-virtuelt miljø.

1. Installer Pip-pakken for tale-tjenester. Sørg for, at du installerer dette fra en terminal med det virtuelle miljø aktiveret.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Hvis du får følgende fejl:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Du skal opdatere Pip. Gør dette med følgende kommando, og prøv derefter at installere pakken igen:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Tilføj følgende imports til filen `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Dette importerer nogle klasser, der bruges til at genkende tale.

1. Tilføj følgende kode for at deklarere noget konfiguration:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Erstat `<key>` med API-nøglen til din tale-tjeneste. Erstat `<location>` med den placering, du brugte, da du oprettede tale-tjeneste-ressourcen.

    Erstat `<language>` med lokalitetsnavnet for det sprog, du vil tale på, f.eks. `en-GB` for engelsk eller `zn-HK` for kantonesisk. Du kan finde en liste over de understøttede sprog og deres lokalitetsnavne i [Language and voice support-dokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Denne konfiguration bruges derefter til at oprette et `SpeechConfig`-objekt, der vil blive brugt til at konfigurere tale-tjenesterne.

1. Tilføj følgende kode for at oprette en talegenkender:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Talegenkenderen kører på en baggrundstråd, lytter efter lyd og konverterer enhver tale i den til tekst. Du kan få teksten ved hjælp af en callback-funktion - en funktion, du definerer og sender til genkenderen. Hver gang tale registreres, kaldes callback-funktionen. Tilføj følgende kode for at definere en callback og sende denne callback til genkenderen, samt definere en funktion til at behandle teksten og skrive den til konsollen:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Genkenderen begynder kun at lytte, når du eksplicit starter den. Tilføj følgende kode for at starte genkendelsen. Dette kører i baggrunden, så din applikation skal også have en uendelig løkke, der sover for at holde applikationen kørende.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Kør denne app. Tal ind i din mikrofon, og den lyd, der konverteres til tekst, vil blive vist i konsollen.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Prøv forskellige typer sætninger, sammen med sætninger hvor ord lyder ens, men har forskellige betydninger. For eksempel, hvis du taler engelsk, sig 'I want to buy two bananas and an apple too', og bemærk hvordan den bruger det korrekte to, two og too baseret på ordets kontekst, ikke kun dets lyd.

> 💁 Du kan finde denne kode i [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device)-mappen.

😀 Dit tale-til-tekst-program var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.