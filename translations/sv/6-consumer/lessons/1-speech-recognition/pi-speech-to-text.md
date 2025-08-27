<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T21:07:46+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "sv"
}
-->
# Tal till text - Raspberry Pi

I den här delen av lektionen kommer du att skriva kod för att konvertera tal i det inspelade ljudet till text med hjälp av tal-tjänsten.

## Skicka ljudet till tal-tjänsten

Ljudet kan skickas till tal-tjänsten med hjälp av REST API. För att använda tal-tjänsten måste du först begära en åtkomsttoken och sedan använda den token för att komma åt REST API. Dessa åtkomsttoken går ut efter 10 minuter, så din kod bör regelbundet begära nya för att säkerställa att de alltid är aktuella.

### Uppgift - hämta en åtkomsttoken

1. Öppna projektet `smart-timer` på din Pi.

1. Ta bort funktionen `play_audio`. Den behövs inte längre eftersom du inte vill att en smart timer ska upprepa vad du sa.

1. Lägg till följande import högst upp i filen `app.py`:

    ```python
    import requests
    ```

1. Lägg till följande kod ovanför `while True`-loopen för att deklarera några inställningar för tal-tjänsten:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Ersätt `<key>` med API-nyckeln för din tal-tjänstresurs. Ersätt `<location>` med platsen du använde när du skapade tal-tjänstresursen.

    Ersätt `<language>` med lokalnamnet för språket du kommer att tala, till exempel `en-GB` för engelska eller `zn-HK` för kantonesiska. Du kan hitta en lista över de stödda språken och deras lokalnamn i [Language and voice support-dokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Nedanför detta, lägg till följande funktion för att hämta en åtkomsttoken:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Denna funktion anropar en token-utgivande endpoint och skickar API-nyckeln som en header. Anropet returnerar en åtkomsttoken som kan användas för att anropa tal-tjänsterna.

1. Nedanför detta, deklarera en funktion för att konvertera tal i det inspelade ljudet till text med hjälp av REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Inuti denna funktion, ställ in REST API-URL och headers:

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

    Detta bygger en URL med platsen för tal-tjänstresursen. Sedan fyller det headers med åtkomsttoken från funktionen `get_access_token`, samt samplingsfrekvensen som används för att spela in ljudet. Slutligen definierar det några parametrar som ska skickas med URL:en och innehåller språket i ljudet.

1. Nedanför detta, lägg till följande kod för att anropa REST API och få tillbaka texten:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Detta anropar URL:en och dekodar JSON-värdet som kommer i svaret. Värdet `RecognitionStatus` i svaret indikerar om anropet lyckades extrahera tal till text, och om detta är `Success` returneras texten från funktionen, annars returneras en tom sträng.

1. Ovanför `while True:`-loopen, definiera en funktion för att bearbeta texten som returneras från tal-till-text-tjänsten. Denna funktion kommer bara att skriva ut texten till konsolen för tillfället.

    ```python
    def process_text(text):
        print(text)
    ```

1. Slutligen, ersätt anropet till `play_audio` i `while True`-loopen med ett anrop till funktionen `convert_speech_to_text`, och skicka texten till funktionen `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Kör koden. Tryck på knappen och tala in i mikrofonen. Släpp knappen när du är klar, och ljudet kommer att konverteras till text och skrivas ut till konsolen.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Testa olika typer av meningar, tillsammans med meningar där ord låter lika men har olika betydelser. Till exempel, om du talar engelska, säg "I want to buy two bananas and an apple too", och lägg märke till hur det använder rätt "to", "two" och "too" baserat på ordets kontext, inte bara dess ljud.

> 💁 Du kan hitta denna kod i [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi)-mappen.

😀 Ditt tal-till-text-program blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.