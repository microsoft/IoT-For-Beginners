<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T22:29:00+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "nl"
}
-->
# Tekst naar spraak - Wio Terminal

In dit deel van de les ga je tekst omzetten naar spraak om gesproken feedback te geven.

## Tekst naar spraak

De spraakservices SDK die je in de vorige les hebt gebruikt om spraak naar tekst om te zetten, kan ook worden gebruikt om tekst terug om te zetten naar spraak.

## Een lijst met stemmen ophalen

Bij het aanvragen van spraak moet je de stem opgeven die gebruikt moet worden, omdat spraak kan worden gegenereerd met verschillende stemmen. Elke taal ondersteunt een reeks verschillende stemmen, en je kunt de lijst met ondersteunde stemmen voor elke taal ophalen via de spraakservices SDK. Hier komen de beperkingen van microcontrollers om de hoek kijken - de oproep om de lijst met stemmen op te halen die door de tekst-naar-spraakservices wordt ondersteund, is een JSON-document van meer dan 77KB groot, veel te groot om door de Wio Terminal te worden verwerkt. Op het moment van schrijven bevat de volledige lijst 215 stemmen, elk gedefinieerd door een JSON-document zoals het volgende:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

Deze JSON is voor de **Aria**-stem, die meerdere stemstijlen heeft. Het enige dat nodig is bij het omzetten van tekst naar spraak is de shortname, `en-US-AriaNeural`.

In plaats van deze hele lijst te downloaden en te decoderen op je microcontroller, moet je wat extra serverloze code schrijven om de lijst met stemmen voor de taal die je gebruikt op te halen en deze aanroepen vanaf je Wio Terminal. Je code kan dan een geschikte stem uit de lijst kiezen, zoals de eerste die wordt gevonden.

### Taak - maak een serverloze functie om een lijst met stemmen op te halen

1. Open je `smart-timer-trigger`-project in VS Code en open de terminal, zorg ervoor dat de virtuele omgeving is geactiveerd. Zo niet, sluit en herstart de terminal.

1. Open het bestand `local.settings.json` en voeg instellingen toe voor de spraak-API-sleutel en locatie:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Vervang `<key>` door de API-sleutel voor je spraakservicebron. Vervang `<location>` door de locatie die je hebt gebruikt bij het aanmaken van de spraakservicebron.

1. Voeg een nieuwe HTTP-trigger toe aan deze app genaamd `get-voices` met behulp van het volgende commando in de VS Code-terminal in de hoofdmap van het functies-app-project:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Dit maakt een HTTP-trigger genaamd `get-voices`.

1. Vervang de inhoud van het bestand `__init__.py` in de map `get-voices` door het volgende:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Deze code maakt een HTTP-verzoek naar het eindpunt om de stemmen op te halen. Deze lijst met stemmen is een groot JSON-blok met stemmen voor alle talen, dus de stemmen voor de taal die in de request body wordt doorgegeven, worden eruit gefilterd, waarna de shortname wordt geëxtraheerd en als een JSON-lijst wordt geretourneerd. De shortname is de waarde die nodig is om tekst naar spraak om te zetten, dus alleen deze waarde wordt geretourneerd.

    > 💁 Je kunt het filter indien nodig aanpassen om alleen de stemmen te selecteren die je wilt.

    Dit verkleint de grootte van de gegevens van 77KB (op het moment van schrijven) naar een veel kleiner JSON-document. Voor bijvoorbeeld Amerikaanse stemmen is dit 408 bytes.

1. Voer je functies-app lokaal uit. Je kunt dit vervolgens aanroepen met een tool zoals curl, op dezelfde manier als je de `text-to-timer` HTTP-trigger hebt getest. Zorg ervoor dat je je taal doorgeeft als een JSON-body:

    ```json
    {
        "language":"<language>"
    }
    ```

    Vervang `<language>` door je taal, zoals `en-GB` of `zh-CN`.

> 💁 Je kunt deze code vinden in de map [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Taak - haal de stem op vanaf je Wio Terminal

1. Open het `smart-timer`-project in VS Code als het nog niet open is.

1. Open het headerbestand `config.h` en voeg de URL toe voor je functies-app:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Vervang `<URL>` door de URL voor de `get-voices` HTTP-trigger van je functies-app. Dit zal hetzelfde zijn als de waarde voor `TEXT_TO_TIMER_FUNCTION_URL`, behalve dat de functienaam `get-voices` is in plaats van `text-to-timer`.

1. Maak een nieuw bestand in de map `src` genaamd `text_to_speech.h`. Dit wordt gebruikt om een klasse te definiëren die tekst naar spraak converteert.

1. Voeg de volgende include-directieven toe aan de bovenkant van het nieuwe bestand `text_to_speech.h`:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Voeg hieronder de volgende code toe om de `TextToSpeech`-klasse te declareren, samen met een instantie die in de rest van de applicatie kan worden gebruikt:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Om je functies-app aan te roepen, moet je een WiFi-client declareren. Voeg het volgende toe aan het `private`-gedeelte van de klasse:

    ```cpp
    WiFiClient _client;
    ```

1. Voeg in het `private`-gedeelte een veld toe voor de geselecteerde stem:

    ```cpp
    String _voice;
    ```

1. Voeg aan het `public`-gedeelte een `init`-functie toe die de eerste stem ophaalt:

    ```cpp
    void init()
    {
    }
    ```

1. Om de stemmen op te halen, moet een JSON-document naar de functies-app worden verzonden met de taal. Voeg de volgende code toe aan de `init`-functie om dit JSON-document te maken:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Maak vervolgens een `HTTPClient` en gebruik deze om de functies-app aan te roepen om de stemmen op te halen, waarbij je het JSON-document post:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Voeg hieronder code toe om de response code te controleren, en als deze 200 (succes) is, de lijst met stemmen te extraheren en de eerste uit de lijst op te halen:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Sluit na dit alles de HTTP-clientverbinding:

    ```cpp
    httpClient.end();
    ```

1. Open het bestand `main.cpp` en voeg de volgende include-directive toe aan de bovenkant om dit nieuwe headerbestand op te nemen:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Voeg in de `setup`-functie, onder de aanroep van `speechToText.init();`, het volgende toe om de `TextToSpeech`-klasse te initialiseren:

    ```cpp
    textToSpeech.init();
    ```

1. Bouw deze code, upload deze naar je Wio Terminal en test het via de seriële monitor. Zorg ervoor dat je functies-app actief is.

    Je ziet de lijst met beschikbare stemmen die door de functies-app wordt geretourneerd, samen met de geselecteerde stem.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Tekst omzetten naar spraak

Zodra je een stem hebt om te gebruiken, kan deze worden gebruikt om tekst om te zetten naar spraak. Dezelfde geheugenbeperkingen met stemmen gelden ook bij het omzetten van spraak naar tekst, dus je moet de spraak opslaan op een SD-kaart om deze af te spelen via de ReSpeaker.

> 💁 In eerdere lessen in dit project heb je flashgeheugen gebruikt om spraak op te slaan die is vastgelegd met de microfoon. Deze les gebruikt een SD-kaart omdat het eenvoudiger is om audio ervan af te spelen met behulp van de Seeed-audiobibliotheken.

Er is ook een andere beperking om rekening mee te houden: de beschikbare audiogegevens van de spraakservice en de formaten die de Wio Terminal ondersteunt. In tegenstelling tot volledige computers kunnen audiobibliotheken voor microcontrollers zeer beperkt zijn in de audioformaten die ze ondersteunen. Bijvoorbeeld, de Seeed Arduino Audio-bibliotheek die geluid kan afspelen via de ReSpeaker ondersteunt alleen audio met een samplefrequentie van 44,1 kHz. De Azure-spraakservices kunnen audio leveren in een aantal formaten, maar geen van deze gebruikt deze samplefrequentie; ze bieden alleen 8 kHz, 16 kHz, 24 kHz en 48 kHz. Dit betekent dat de audio opnieuw moet worden gesampled naar 44,1 kHz, iets wat meer middelen vereist dan de Wio Terminal heeft, vooral qua geheugen.

Wanneer je gegevens zoals deze moet manipuleren, is het vaak beter om serverloze code te gebruiken, vooral als de gegevens via een weboproep worden verkregen. De Wio Terminal kan een serverloze functie aanroepen, de tekst doorgeven om te converteren, en de serverloze functie kan zowel de spraakservice aanroepen om tekst naar spraak om te zetten als de audio opnieuw samplen naar de vereiste samplefrequentie. Vervolgens kan het de audio teruggeven in de vorm die de Wio Terminal nodig heeft om op de SD-kaart op te slaan en af te spelen via de ReSpeaker.

### Taak - maak een serverloze functie om tekst naar spraak te converteren

1. Open je `smart-timer-trigger`-project in VS Code en open de terminal, zorg ervoor dat de virtuele omgeving is geactiveerd. Zo niet, sluit en herstart de terminal.

1. Voeg een nieuwe HTTP-trigger toe aan deze app genaamd `text-to-speech` met behulp van het volgende commando in de VS Code-terminal in de hoofdmap van het functies-app-project:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Dit maakt een HTTP-trigger genaamd `text-to-speech`.

1. Het [librosa](https://librosa.org) Pip-pakket heeft functies om audio opnieuw te samplen, dus voeg dit toe aan het bestand `requirements.txt`:

    ```sh
    librosa
    ```

    Zodra dit is toegevoegd, installeer je de Pip-pakketten met het volgende commando in de VS Code-terminal:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Als je Linux gebruikt, inclusief Raspberry Pi OS, moet je mogelijk `libsndfile` installeren met het volgende commando:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Om tekst naar spraak te converteren, kun je de spraak-API-sleutel niet direct gebruiken. In plaats daarvan moet je een toegangstoken aanvragen, waarbij je de API-sleutel gebruikt om de toegangstokenaanvraag te verifiëren. Open het bestand `__init__.py` uit de map `text-to-speech` en vervang alle code erin door het volgende:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Dit definieert constanten voor de locatie en spraaksleutel die worden gelezen uit de instellingen. Vervolgens definieert het de functie `get_access_token` die een toegangstoken voor de spraakservice ophaalt.

1. Voeg onder deze code het volgende toe:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Dit definieert de HTTP-trigger die tekst naar spraak converteert. Het haalt de tekst op om te converteren, de taal en de stem uit de JSON-body die naar het verzoek is verzonden, bouwt wat SSML om de spraak aan te vragen, en roept vervolgens de relevante REST API aan waarbij het toegangstoken wordt gebruikt voor authenticatie. Deze REST API-aanroep retourneert de audio gecodeerd als een 16-bit, 48 kHz mono WAV-bestand, gedefinieerd door de waarde van `playback_format`, die wordt verzonden naar de REST API-aanroep.

    Vervolgens wordt deze audio opnieuw gesampled door `librosa` van een samplefrequentie van 48 kHz naar een samplefrequentie van 44,1 kHz. Daarna wordt deze audio opgeslagen in een binair buffer dat vervolgens wordt geretourneerd.

1. Voer je functies-app lokaal uit of implementeer deze in de cloud. Je kunt dit vervolgens aanroepen met een tool zoals curl, op dezelfde manier als je de `text-to-timer` HTTP-trigger hebt getest. Zorg ervoor dat je de taal, stem en tekst doorgeeft als de JSON-body:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Vervang `<language>` door je taal, zoals `en-GB` of `zh-CN`. Vervang `<voice>` door de stem die je wilt gebruiken. Vervang `<text>` door de tekst die je wilt omzetten naar spraak. Je kunt de uitvoer opslaan in een bestand en afspelen met elke audioplayer die WAV-bestanden kan afspelen.

    Bijvoorbeeld, om "Hello" om te zetten naar spraak in het Amerikaans-Engels met de Jenny Neural-stem, met de functies-app lokaal draaiend, kun je het volgende curl-commando gebruiken:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Dit slaat de audio op als `hello.wav` in de huidige map.

> 💁 Je kunt deze code vinden in de map [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Taak - haal de spraak op vanaf je Wio Terminal

1. Open het `smart-timer`-project in VS Code als het nog niet open is.

1. Open het headerbestand `config.h` en voeg de URL toe voor je functies-app:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Vervang `<URL>` door de URL voor de `text-to-speech` HTTP-trigger van je functies-app. Dit zal hetzelfde zijn als de waarde voor `TEXT_TO_TIMER_FUNCTION_URL`, behalve dat de functienaam `text-to-speech` is in plaats van `text-to-timer`.

1. Open het headerbestand `text_to_speech.h` en voeg de volgende methode toe aan het `public`-gedeelte van de `TextToSpeech`-klasse:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Voeg aan de methode `convertTextToSpeech` de volgende code toe om de JSON te maken die naar de functies-app wordt verzonden:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dit schrijft de taal, stem en tekst naar het JSON-document en serialiseert het vervolgens naar een string.

1. Voeg hieronder de volgende code toe om de functies-app aan te roepen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dit maakt een HTTPClient en doet een POST-verzoek met het JSON-document naar de tekst-naar-spraak HTTP-trigger.

1. Als de oproep werkt, kunnen de ruwe binaire gegevens die door de functies-app worden geretourneerd, worden gestreamd naar een bestand op de SD-kaart. Voeg de volgende code toe om dit te doen:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Deze code controleert de response, en als deze 200 (succes) is, worden de binaire gegevens gestreamd naar een bestand in de root van de SD-kaart genaamd `SPEECH.WAV`.

1. Sluit aan het einde van deze methode de HTTP-verbinding:

    ```cpp
    httpClient.end();
    ```

1. De tekst die moet worden uitgesproken, kan nu worden omgezet in audio. Voeg in het bestand `main.cpp` de volgende regel toe aan het einde van de `say`-functie om de tekst om te zetten naar audio:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Taak - audio afspelen met je Wio Terminal

**Binnenkort beschikbaar**

## Je functions-app naar de cloud implementeren

De reden om de functions-app lokaal uit te voeren, is dat het `librosa` Pip-pakket op Linux een afhankelijkheid heeft van een bibliotheek die niet standaard is geïnstalleerd en die moet worden geïnstalleerd voordat de functions-app kan draaien. Functions-apps zijn serverloos - er zijn geen servers die je zelf kunt beheren, dus er is geen manier om deze bibliotheek vooraf te installeren.

De manier om dit te doen is door je functions-app te implementeren met behulp van een Docker-container. Deze container wordt door de cloud ingezet telkens wanneer een nieuwe instantie van je functions-app moet worden opgestart (bijvoorbeeld wanneer de vraag groter is dan de beschikbare middelen, of als de functions-app een tijdje niet is gebruikt en is afgesloten).

Je kunt de instructies vinden om een functions-app in te stellen en te implementeren via Docker in de [documentatie over het maken van een functie op Linux met een aangepaste container op Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Zodra dit is geïmplementeerd, kun je je Wio Terminal-code aanpassen om toegang te krijgen tot deze functie:

1. Voeg het Azure Functions-certificaat toe aan `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Vervang alle vermeldingen van `<WiFiClient.h>` door `<WiFiClientSecure.h>`.

1. Vervang alle `WiFiClient`-velden door `WiFiClientSecure`.

1. Voeg in elke klasse met een `WiFiClientSecure`-veld een constructor toe en stel het certificaat in die constructor in:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.