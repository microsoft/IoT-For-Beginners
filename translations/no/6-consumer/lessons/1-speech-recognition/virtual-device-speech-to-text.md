<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T21:05:37+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "no"
}
-->
# Tale til tekst - Virtuell IoT-enhet

I denne delen av leksjonen skal du skrive kode for å konvertere tale fra mikrofonen din til tekst ved hjelp av taleservicen.

## Konverter tale til tekst

På Windows, Linux og macOS kan Python SDK for taleservicen brukes til å lytte til mikrofonen din og konvertere oppdaget tale til tekst. Den lytter kontinuerlig, registrerer lydnivåene og sender talen for konvertering til tekst når lydnivået faller, for eksempel ved slutten av en taleperiode.

### Oppgave - konverter tale til tekst

1. Opprett en ny Python-app på datamaskinen din i en mappe kalt `smart-timer` med en enkelt fil kalt `app.py` og et Python-virtuelt miljø.

1. Installer Pip-pakken for taleservicen. Sørg for at du installerer dette fra en terminal med det virtuelle miljøet aktivert.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Hvis du får følgende feil:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Du må oppdatere Pip. Gjør dette med følgende kommando, og prøv deretter å installere pakken på nytt:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Legg til følgende imports i `app.py`-filen:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Dette importerer noen klasser som brukes til å gjenkjenne tale.

1. Legg til følgende kode for å deklarere noe konfigurasjon:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Erstatt `<key>` med API-nøkkelen for taleservicen din. Erstatt `<location>` med plasseringen du brukte da du opprettet taleserviceressursen.

    Erstatt `<language>` med lokalitetsnavnet for språket du skal snakke, for eksempel `en-GB` for engelsk eller `zn-HK` for kantonesisk. Du finner en liste over støttede språk og deres lokalitetsnavn i [dokumentasjonen for språk- og stemmestøtte på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Denne konfigurasjonen brukes deretter til å opprette et `SpeechConfig`-objekt som vil bli brukt til å konfigurere taleservicen.

1. Legg til følgende kode for å opprette en talegjenkjenner:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Talegjenkjenneren kjører på en bakgrunnstråd, lytter etter lyd og konverterer eventuell tale til tekst. Du kan hente teksten ved hjelp av en callback-funksjon - en funksjon du definerer og sender til gjenkjenneren. Hver gang tale oppdages, kalles callback-funksjonen. Legg til følgende kode for å definere en callback og sende denne til gjenkjenneren, samt definere en funksjon for å behandle teksten og skrive den til konsollen:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Gjenkjenneren begynner bare å lytte når du eksplisitt starter den. Legg til følgende kode for å starte gjenkjenningen. Dette kjører i bakgrunnen, så applikasjonen din trenger også en uendelig løkke som sover for å holde applikasjonen i gang.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Kjør denne appen. Snakk inn i mikrofonen din, og lyden som konverteres til tekst vil bli skrevet ut i konsollen.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Prøv forskjellige typer setninger, sammen med setninger der ord høres like ut, men har forskjellige betydninger. For eksempel, hvis du snakker engelsk, si "I want to buy two bananas and an apple too", og legg merke til hvordan den bruker riktig "to", "two" og "too" basert på konteksten til ordet, ikke bare lyden.

> 💁 Du finner denne koden i [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device)-mappen.

😀 Programmet ditt for tale til tekst var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.