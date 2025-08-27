<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T21:07:59+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "da"
}
-->
# Tale til tekst - Raspberry Pi

I denne del af lektionen skal du skrive kode for at konvertere tale i den optagede lyd til tekst ved hjælp af tale-tjenesten.

## Send lyden til tale-tjenesten

Lyden kan sendes til tale-tjenesten ved hjælp af REST API'et. For at bruge tale-tjenesten skal du først anmode om en adgangstoken og derefter bruge denne token til at få adgang til REST API'et. Disse adgangstokens udløber efter 10 minutter, så din kode skal regelmæssigt anmode om dem for at sikre, at de altid er opdaterede.

### Opgave - få en adgangstoken

1. Åbn `smart-timer`-projektet på din Pi.

1. Fjern funktionen `play_audio`. Denne er ikke længere nødvendig, da du ikke ønsker, at en smart timer gentager, hvad du sagde.

1. Tilføj følgende import øverst i filen `app.py`:

    ```python
    import requests
    ```

1. Tilføj følgende kode over `while True`-løkken for at erklære nogle indstillinger for tale-tjenesten:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Erstat `<key>` med API-nøglen til din tale-tjeneste-ressource. Erstat `<location>` med den placering, du brugte, da du oprettede tale-tjeneste-ressourcen.

    Erstat `<language>` med lokalitetsnavnet for det sprog, du vil tale på, for eksempel `en-GB` for engelsk eller `zn-HK` for kantonesisk. Du kan finde en liste over de understøttede sprog og deres lokalitetsnavne i [dokumentationen om sprog- og stemmestøtte på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Tilføj nedenunder følgende funktion for at få en adgangstoken:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Denne funktion kalder et token-udstedelses-endpoint og sender API-nøglen som en header. Kaldet returnerer en adgangstoken, der kan bruges til at kalde tale-tjenesterne.

1. Tilføj nedenunder en funktion til at konvertere tale i den optagede lyd til tekst ved hjælp af REST API'et:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Inde i denne funktion skal du opsætte REST API URL'en og headers:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Dette bygger en URL ved hjælp af placeringen af tale-tjeneste-ressourcen. Derefter udfyldes headers med adgangstoken fra funktionen `get_access_token` samt samplingsfrekvensen, der blev brugt til at optage lyden. Endelig defineres nogle parametre, der skal sendes med URL'en, og som indeholder sproget i lyden.

1. Tilføj nedenunder følgende kode for at kalde REST API'et og få teksten tilbage:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Dette kalder URL'en og dekoder JSON-værdien, der kommer i svaret. Værdien `RecognitionStatus` i svaret angiver, om kaldet kunne udtrække tale til tekst med succes, og hvis denne er `Success`, returneres teksten fra funktionen, ellers returneres en tom streng.

1. Over `while True:`-løkken skal du definere en funktion til at behandle teksten, der returneres fra tale-til-tekst-tjenesten. Denne funktion vil blot udskrive teksten til konsollen for nu.

    ```python
    def process_text(text):
        print(text)
    ```

1. Erstat til sidst kaldet til `play_audio` i `while True`-løkken med et kald til funktionen `convert_speech_to_text`, og send teksten til funktionen `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Kør koden. Tryk på knappen og tal ind i mikrofonen. Slip knappen, når du er færdig, og lyden vil blive konverteret til tekst og udskrevet til konsollen.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Prøv forskellige typer sætninger samt sætninger, hvor ord lyder ens, men har forskellige betydninger. For eksempel, hvis du taler engelsk, kan du sige "I want to buy two bananas and an apple too" og bemærke, hvordan den bruger den korrekte "to", "two" og "too" baseret på konteksten af ordet, ikke kun dets lyd.

> 💁 Du kan finde denne kode i [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi)-mappen.

😀 Dit tale-til-tekst-program var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.