<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T22:43:17+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "nl"
}
-->
# Spraak naar tekst - Raspberry Pi

In dit deel van de les schrijf je code om spraak in de opgenomen audio om te zetten naar tekst met behulp van de spraakservice.

## Verstuur de audio naar de spraakservice

De audio kan naar de spraakservice worden gestuurd via de REST API. Om de spraakservice te gebruiken, moet je eerst een toegangstoken aanvragen en dat token gebruiken om toegang te krijgen tot de REST API. Deze toegangstokens verlopen na 10 minuten, dus je code moet ze regelmatig aanvragen om ervoor te zorgen dat ze altijd up-to-date zijn.

### Taak - verkrijg een toegangstoken

1. Open het `smart-timer`-project op je Pi.

1. Verwijder de functie `play_audio`. Deze is niet langer nodig, omdat je niet wilt dat een slimme timer herhaalt wat je hebt gezegd.

1. Voeg de volgende import toe aan de bovenkant van het bestand `app.py`:

    ```python
    import requests
    ```

1. Voeg de volgende code toe boven de `while True`-lus om enkele instellingen voor de spraakservice te declareren:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Vervang `<key>` door de API-sleutel voor je spraakservicebron. Vervang `<location>` door de locatie die je hebt gebruikt bij het aanmaken van de spraakservicebron.

    Vervang `<language>` door de locale naam van de taal waarin je zult spreken, bijvoorbeeld `en-GB` voor Engels, of `zn-HK` voor Kantonees. Je kunt een lijst met ondersteunde talen en hun locale namen vinden in de [Documentatie over taal- en stemondersteuning op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Voeg hieronder de volgende functie toe om een toegangstoken te verkrijgen:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Deze functie roept een endpoint aan dat tokens uitgeeft, waarbij de API-sleutel als header wordt meegegeven. Deze oproep retourneert een toegangstoken dat kan worden gebruikt om de spraakservices aan te roepen.

1. Declareer hieronder een functie om spraak in de opgenomen audio om te zetten naar tekst met behulp van de REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Stel binnen deze functie de REST API-URL en headers in:

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

    Dit bouwt een URL op met behulp van de locatie van de spraakservicebron. Vervolgens worden de headers gevuld met het toegangstoken van de functie `get_access_token`, evenals de sample rate die is gebruikt om de audio op te nemen. Ten slotte worden enkele parameters gedefinieerd die met de URL worden meegegeven en de taal in de audio bevatten.

1. Voeg hieronder de volgende code toe om de REST API aan te roepen en de tekst terug te krijgen:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Deze code roept de URL aan en decodeert de JSON-waarde die in de respons wordt meegeleverd. De waarde `RecognitionStatus` in de respons geeft aan of de oproep succesvol spraak naar tekst heeft kunnen omzetten. Als dit `Success` is, wordt de tekst geretourneerd door de functie, anders wordt een lege string geretourneerd.

1. Definieer boven de `while True:`-lus een functie om de tekst te verwerken die is geretourneerd door de spraak-naar-tekstservice. Deze functie zal de tekst voorlopig alleen naar de console printen.

    ```python
    def process_text(text):
        print(text)
    ```

1. Vervang ten slotte de oproep naar `play_audio` in de `while True`-lus door een oproep naar de functie `convert_speech_to_text`, waarbij de tekst wordt doorgegeven aan de functie `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Voer de code uit. Druk op de knop en spreek in de microfoon. Laat de knop los wanneer je klaar bent, en de audio wordt omgezet naar tekst en naar de console geprint.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Probeer verschillende soorten zinnen, samen met zinnen waarin woorden hetzelfde klinken maar verschillende betekenissen hebben. Bijvoorbeeld, als je in het Engels spreekt, zeg dan 'I want to buy two bananas and an apple too', en merk op hoe het de juiste to, two en too gebruikt op basis van de context van het woord, niet alleen op basis van de klank.

> 💁 Je kunt deze code vinden in de [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) map.

😀 Je spraak-naar-tekstprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.