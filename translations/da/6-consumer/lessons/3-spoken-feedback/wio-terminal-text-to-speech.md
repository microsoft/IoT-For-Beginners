<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T20:55:19+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "da"
}
-->
# Tekst til tale - Wio Terminal

I denne del af lektionen vil du konvertere tekst til tale for at give talte tilbagemeldinger.

## Tekst til tale

Den tale-tjeneste SDK, som du brugte i den sidste lektion til at konvertere tale til tekst, kan også bruges til at konvertere tekst tilbage til tale.

## Få en liste over stemmer

Når du anmoder om tale, skal du angive den stemme, der skal bruges, da tale kan genereres med en række forskellige stemmer. Hvert sprog understøtter en række forskellige stemmer, og du kan få listen over understøttede stemmer for hvert sprog fra tale-tjeneste SDK'en. Her kommer mikrocontrollerens begrænsninger i spil - kaldet for at få listen over stemmer, der understøttes af tekst-til-tale-tjenesterne, er et JSON-dokument på over 77KB i størrelse, hvilket er alt for stort til at blive behandlet af Wio Terminal. På tidspunktet for skrivningen indeholder den fulde liste 215 stemmer, hver defineret af et JSON-dokument som det følgende:

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

Dette JSON er for **Aria**-stemmen, som har flere stemmestilarter. Alt, hvad der er nødvendigt, når man konverterer tekst til tale, er kortnavnet, `en-US-AriaNeural`.

I stedet for at downloade og afkode hele denne liste på din mikrocontroller, skal du skrive noget serverløst kode for at hente listen over stemmer for det sprog, du bruger, og kalde dette fra din Wio Terminal. Din kode kan derefter vælge en passende stemme fra listen, såsom den første den finder.

### Opgave - opret en serverløs funktion til at få en liste over stemmer

1. Åbn dit `smart-timer-trigger` projekt i VS Code, og åbn terminalen, og sørg for, at det virtuelle miljø er aktiveret. Hvis ikke, afslut og genskab terminalen.

1. Åbn filen `local.settings.json` og tilføj indstillinger for tale-API-nøglen og placeringen:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Erstat `<key>` med API-nøglen til din tale-tjeneste-ressource. Erstat `<location>` med den placering, du brugte, da du oprettede tale-tjeneste-ressourcen.

1. Tilføj en ny HTTP-trigger til denne app kaldet `get-voices` ved at bruge følgende kommando fra terminalen i VS Code i rodmappen af funktionsapp-projektet:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Dette vil oprette en HTTP-trigger kaldet `get-voices`.

1. Erstat indholdet af filen `__init__.py` i mappen `get-voices` med følgende:

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

    Denne kode laver en HTTP-anmodning til endpointet for at få stemmerne. Denne stemmeliste er en stor blok af JSON med stemmer for alle sprog, så stemmerne for det sprog, der sendes i anmodningens body, filtreres ud, og derefter udtrækkes kortnavnet og returneres som en JSON-liste. Kortnavnet er den værdi, der er nødvendig for at konvertere tekst til tale, så kun denne værdi returneres.

    > 💁 Du kan ændre filteret efter behov for at vælge kun de stemmer, du ønsker.

    Dette reducerer datastørrelsen fra 77KB (på tidspunktet for skrivningen) til et meget mindre JSON-dokument. For eksempel, for amerikanske stemmer er dette 408 bytes.

1. Kør din funktionsapp lokalt. Du kan derefter kalde dette ved hjælp af et værktøj som curl på samme måde, som du testede din `text-to-timer` HTTP-trigger. Sørg for at sende dit sprog som en JSON-body:

    ```json
    {
        "language":"<language>"
    }
    ```

    Erstat `<language>` med dit sprog, såsom `en-GB` eller `zh-CN`.

> 💁 Du kan finde denne kode i mappen [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Opgave - hent stemmen fra din Wio Terminal

1. Åbn projektet `smart-timer` i VS Code, hvis det ikke allerede er åbent.

1. Åbn header-filen `config.h` og tilføj URL'en til din funktionsapp:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Erstat `<URL>` med URL'en til `get-voices` HTTP-triggeren på din funktionsapp. Dette vil være det samme som værdien for `TEXT_TO_TIMER_FUNCTION_URL`, bortset fra at funktionsnavnet er `get-voices` i stedet for `text-to-timer`.

1. Opret en ny fil i mappen `src` kaldet `text_to_speech.h`. Denne vil blive brugt til at definere en klasse til at konvertere fra tekst til tale.

1. Tilføj følgende include-direktiver øverst i den nye fil `text_to_speech.h`:

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

1. Tilføj følgende kode nedenfor for at erklære klassen `TextToSpeech` sammen med en instans, der kan bruges i resten af applikationen:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. For at kalde din funktionsapp skal du erklære en WiFi-klient. Tilføj følgende til den private sektion af klassen:

    ```cpp
    WiFiClient _client;
    ```

1. I den private sektion skal du tilføje et felt til den valgte stemme:

    ```cpp
    String _voice;
    ```

1. Til den offentlige sektion skal du tilføje en `init`-funktion, der vil hente den første stemme:

    ```cpp
    void init()
    {
    }
    ```

1. For at få stemmerne skal et JSON-dokument sendes til funktionsappen med sproget. Tilføj følgende kode til `init`-funktionen for at oprette dette JSON-dokument:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Opret derefter en `HTTPClient`, og brug den til at kalde funktionsappen for at få stemmerne ved at sende JSON-dokumentet:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Tilføj nedenfor dette kode for at kontrollere svar-koden, og hvis det er 200 (succes), så udtræk listen over stemmer og hent den første fra listen:

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

1. Efter dette skal du afslutte HTTP-klientforbindelsen:

    ```cpp
    httpClient.end();
    ```

1. Åbn filen `main.cpp`, og tilføj følgende include-direktiv øverst for at inkludere denne nye header-fil:

    ```cpp
    #include "text_to_speech.h"
    ```

1. I `setup`-funktionen, under kaldet til `speechToText.init();`, tilføj følgende for at initialisere klassen `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Byg denne kode, upload den til din Wio Terminal, og test den gennem den serielle monitor. Sørg for, at din funktionsapp kører.

    Du vil se listen over tilgængelige stemmer returneret fra funktionsappen sammen med den valgte stemme.

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

## Konverter tekst til tale

Når du har en stemme at bruge, kan den bruges til at konvertere tekst til tale. De samme hukommelsesbegrænsninger med stemmer gælder også, når man konverterer tale til tekst, så du skal skrive talen til et SD-kort, så det kan afspilles via ReSpeaker.

> 💁 I tidligere lektioner i dette projekt brugte du flash-hukommelse til at gemme tale optaget fra mikrofonen. Denne lektion bruger et SD-kort, da det er lettere at afspille lyd fra det ved hjælp af Seeed-lydbibliotekerne.

Der er også en anden begrænsning at overveje, nemlig de tilgængelige lyddata fra tale-tjenesten og de formater, som Wio Terminal understøtter. I modsætning til fulde computere kan lydbiblioteker til mikrocontrollere være meget begrænsede i de lydformater, de understøtter. For eksempel understøtter Seeed Arduino Audio-biblioteket, der kan afspille lyd via ReSpeaker, kun lyd med en samplingsfrekvens på 44,1KHz. Azure tale-tjenester kan levere lyd i en række formater, men ingen af dem bruger denne samplingsfrekvens; de leverer kun 8KHz, 16KHz, 24KHz og 48KHz. Dette betyder, at lyden skal gen-samples til 44,1KHz, hvilket kræver flere ressourcer, end Wio Terminal har, især hukommelse.

Når man har brug for at manipulere data som dette, er det ofte bedre at bruge serverløs kode, især hvis dataene hentes via et webkald. Wio Terminal kan kalde en serverløs funktion, sende teksten, der skal konverteres, og den serverløse funktion kan både kalde tale-tjenesten for at konvertere tekst til tale samt gen-sample lyden til den nødvendige samplingsfrekvens. Den kan derefter returnere lyden i det format, Wio Terminal har brug for, så det kan gemmes på SD-kortet og afspilles via ReSpeaker.

### Opgave - opret en serverløs funktion til at konvertere tekst til tale

1. Åbn dit `smart-timer-trigger` projekt i VS Code, og åbn terminalen, og sørg for, at det virtuelle miljø er aktiveret. Hvis ikke, afslut og genskab terminalen.

1. Tilføj en ny HTTP-trigger til denne app kaldet `text-to-speech` ved at bruge følgende kommando fra terminalen i VS Code i rodmappen af funktionsapp-projektet:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Dette vil oprette en HTTP-trigger kaldet `text-to-speech`.

1. Pip-pakken [librosa](https://librosa.org) har funktioner til at gen-sample lyd, så tilføj denne til filen `requirements.txt`:

    ```sh
    librosa
    ```

    Når dette er tilføjet, skal du installere Pip-pakkerne ved hjælp af følgende kommando fra terminalen i VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Hvis du bruger Linux, inklusive Raspberry Pi OS, skal du muligvis installere `libsndfile` med følgende kommando:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. For at konvertere tekst til tale kan du ikke bruge tale-API-nøglen direkte. I stedet skal du anmode om en adgangstoken ved at bruge API-nøglen til at godkende adgangstoken-anmodningen. Åbn filen `__init__.py` fra mappen `text-to-speech` og erstat al koden i den med følgende:

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

    Dette definerer konstanter for placeringen og tale-nøglen, der vil blive læst fra indstillingerne. Det definerer derefter funktionen `get_access_token`, der vil hente en adgangstoken til tale-tjenesten.

1. Tilføj følgende kode nedenfor:

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

    Dette definerer HTTP-triggeren, der konverterer teksten til tale. Den udtrækker teksten, der skal konverteres, sproget og stemmen fra JSON-body'en sendt til anmodningen, bygger noget SSML for at anmode om talen og kalder derefter det relevante REST API ved at godkende med adgangstokenet. Dette REST API-kald returnerer lyden kodet som en 16-bit, 48KHz mono WAV-fil, defineret af værdien af `playback_format`, som sendes til REST API-kaldet.

    Dette gen-samples derefter af `librosa` fra en samplingsfrekvens på 48KHz til en samplingsfrekvens på 44,1KHz, og denne lyd gemmes derefter i en binær buffer, der returneres.

1. Kør din funktionsapp lokalt, eller deploy den til skyen. Du kan derefter kalde dette ved hjælp af et værktøj som curl på samme måde, som du testede din `text-to-timer` HTTP-trigger. Sørg for at sende sproget, stemmen og teksten som JSON-body:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Erstat `<language>` med dit sprog, såsom `en-GB` eller `zh-CN`. Erstat `<voice>` med den stemme, du vil bruge. Erstat `<text>` med den tekst, du vil konvertere til tale. Du kan gemme outputtet til en fil og afspille det med enhver lydafspiller, der kan afspille WAV-filer.

    For eksempel, for at konvertere "Hello" til tale ved hjælp af amerikansk engelsk med Jenny Neural-stemmen, med funktionsappen kørende lokalt, kan du bruge følgende curl-kommando:

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

    Dette vil gemme lyden til `hello.wav` i den aktuelle mappe.

> 💁 Du kan finde denne kode i mappen [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Opgave - hent talen fra din Wio Terminal

1. Åbn projektet `smart-timer` i VS Code, hvis det ikke allerede er åbent.

1. Åbn header-filen `config.h` og tilføj URL'en til din funktionsapp:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Erstat `<URL>` med URL'en til `text-to-speech` HTTP-triggeren på din funktionsapp. Dette vil være det samme som værdien for `TEXT_TO_TIMER_FUNCTION_URL`, bortset fra at funktionsnavnet er `text-to-speech` i stedet for `text-to-timer`.

1. Åbn header-filen `text_to_speech.h`, og tilføj følgende metode til den offentlige sektion af klassen `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Til metoden `convertTextToSpeech` skal du tilføje følgende kode for at oprette JSON, der skal sendes til funktionsappen:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dette skriver sproget, stemmen og teksten til JSON-dokumentet og serialiserer det derefter til en streng.

1. Tilføj nedenfor dette kode for at kalde funktionsappen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dette opretter en HTTPClient og laver derefter en POST-anmodning ved hjælp af JSON-dokumentet til tekst-til-tale HTTP-triggeren.

1. Hvis kaldet lykkes, kan de rå binære data, der returneres fra funktionsapp-kaldet, streames til en fil på SD-kortet. Tilføj følgende kode for at gøre dette:

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

    Denne kode kontrollerer svaret, og hvis det er 200 (succes), streames de binære data til en fil i roden af SD-kortet kaldet `SPEECH.WAV`.

1. I slutningen af denne metode skal du lukke HTTP-forbindelsen:

    ```cpp
    httpClient.end();
    ```

1. Teksten, der skal tales, kan nu konverteres til lyd. I filen `main.cpp` skal du tilføje følgende linje til slutningen af funktionen `say` for at konvertere teksten til tale:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Opgave - afspil lyd fra din Wio Terminal

**Kommer snart**

## Udrulning af din functions-app til skyen

Årsagen til at køre functions-appen lokalt er, at `librosa` Pip-pakken på Linux har en afhængighed af et bibliotek, der ikke er installeret som standard, og det skal installeres, før functions-appen kan køre. Functions-apps er serverløse - der er ingen servere, du selv kan administrere, så der er ingen måde at installere dette bibliotek på forhånd.

Måden at gøre dette på er i stedet at udrulle din functions-app ved hjælp af en Docker-container. Denne container udrulles af skyen, når det er nødvendigt at oprette en ny instans af din functions-app (f.eks. når efterspørgslen overstiger de tilgængelige ressourcer, eller hvis functions-appen ikke har været brugt i et stykke tid og er lukket ned).

Du kan finde instruktionerne til at oprette en functions-app og udrulle via Docker i [dokumentationen om at oprette en funktion på Linux ved hjælp af en brugerdefineret container på Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Når dette er udrullet, kan du overføre din Wio Terminal-kode for at få adgang til denne funktion:

1. Tilføj Azure Functions-certifikatet til `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Ændr alle inkluder af `<WiFiClient.h>` til `<WiFiClientSecure.h>`.

1. Ændr alle `WiFiClient`-felter til `WiFiClientSecure`.

1. I hver klasse, der har et `WiFiClientSecure`-felt, tilføj en konstruktør og sæt certifikatet i den konstruktør:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.