<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T20:54:39+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "sv"
}
-->
# Text till tal - Wio Terminal

I den här delen av lektionen kommer du att konvertera text till tal för att ge muntlig feedback.

## Text till tal

Den SDK för tal-tjänster som du använde i den senaste lektionen för att konvertera tal till text kan också användas för att konvertera text tillbaka till tal.

## Hämta en lista över röster

När du begär tal måste du ange vilken röst som ska användas, eftersom tal kan genereras med olika röster. Varje språk stöder en rad olika röster, och du kan få en lista över stödda röster för varje språk från SDK för tal-tjänster. Här kommer mikrocontrollerbegränsningarna in i bilden - anropet för att hämta listan över röster som stöds av text-till-tal-tjänsterna är ett JSON-dokument på över 77KB, vilket är alldeles för stort för att bearbetas av Wio Terminal. Vid skrivande stund innehåller den fullständiga listan 215 röster, var och en definierad av ett JSON-dokument som det följande:

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

Detta JSON är för rösten **Aria**, som har flera röststilar. Det enda som behövs när text konverteras till tal är kortnamnet, `en-US-AriaNeural`.

Istället för att ladda ner och avkoda hela denna lista på din mikrocontroller, behöver du skriva lite mer serverlös kod för att hämta listan över röster för det språk du använder och anropa detta från din Wio Terminal. Din kod kan sedan välja en lämplig röst från listan, till exempel den första den hittar.

### Uppgift - skapa en serverlös funktion för att hämta en lista över röster

1. Öppna ditt `smart-timer-trigger`-projekt i VS Code och öppna terminalen, se till att den virtuella miljön är aktiverad. Om inte, avsluta och återskapa terminalen.

1. Öppna filen `local.settings.json` och lägg till inställningar för API-nyckeln och platsen för tal-tjänsten:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Ersätt `<key>` med API-nyckeln för din tal-tjänstresurs. Ersätt `<location>` med platsen du använde när du skapade tal-tjänstresursen.

1. Lägg till en ny HTTP-trigger till denna app kallad `get-voices` med följande kommando från terminalen i rotmappen för funktionsapp-projektet:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Detta skapar en HTTP-trigger kallad `get-voices`.

1. Ersätt innehållet i filen `__init__.py` i mappen `get-voices` med följande:

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

    Denna kod gör ett HTTP-anrop till slutpunkten för att hämta rösterna. Denna röstlista är ett stort JSON-block med röster för alla språk, så rösterna för det språk som skickas i begäran filtreras ut, och kortnamnet extraheras och returneras som en JSON-lista. Kortnamnet är värdet som behövs för att konvertera text till tal, så endast detta värde returneras.

    > 💁 Du kan ändra filtret vid behov för att välja endast de röster du vill ha.

    Detta minskar storleken på data från 77KB (vid skrivande stund) till ett mycket mindre JSON-dokument. Till exempel, för amerikanska röster är detta 408 byte.

1. Kör din funktionsapp lokalt. Du kan sedan anropa detta med ett verktyg som curl på samma sätt som du testade din `text-to-timer` HTTP-trigger. Se till att skicka ditt språk som en JSON-kropp:

    ```json
    {
        "language":"<language>"
    }
    ```

    Ersätt `<language>` med ditt språk, till exempel `en-GB` eller `zh-CN`.

> 💁 Du kan hitta denna kod i mappen [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Uppgift - hämta rösten från din Wio Terminal

1. Öppna projektet `smart-timer` i VS Code om det inte redan är öppet.

1. Öppna header-filen `config.h` och lägg till URL:en för din funktionsapp:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Ersätt `<URL>` med URL:en för HTTP-triggern `get-voices` i din funktionsapp. Detta kommer att vara samma som värdet för `TEXT_TO_TIMER_FUNCTION_URL`, förutom med funktionsnamnet `get-voices` istället för `text-to-timer`.

1. Skapa en ny fil i mappen `src` kallad `text_to_speech.h`. Denna kommer att användas för att definiera en klass för att konvertera från text till tal.

1. Lägg till följande inkluderingsdirektiv högst upp i den nya filen `text_to_speech.h`:

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

1. Lägg till följande kod nedanför detta för att deklarera klassen `TextToSpeech`, tillsammans med en instans som kan användas i resten av applikationen:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. För att anropa din funktionsapp behöver du deklarera en WiFi-klient. Lägg till följande i den privata sektionen av klassen:

    ```cpp
    WiFiClient _client;
    ```

1. I den privata sektionen, lägg till ett fält för den valda rösten:

    ```cpp
    String _voice;
    ```

1. I den publika sektionen, lägg till en `init`-funktion som kommer att hämta den första rösten:

    ```cpp
    void init()
    {
    }
    ```

1. För att hämta rösterna behöver ett JSON-dokument skickas till funktionsappen med språket. Lägg till följande kod i `init`-funktionen för att skapa detta JSON-dokument:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Skapa sedan en `HTTPClient` och använd den för att anropa funktionsappen för att hämta rösterna, genom att skicka JSON-dokumentet:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Nedanför detta, lägg till kod för att kontrollera svarskoden, och om den är 200 (framgång), extrahera listan över röster och hämta den första från listan:

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

1. Efter detta, avsluta HTTP-klientanslutningen:

    ```cpp
    httpClient.end();
    ```

1. Öppna filen `main.cpp` och lägg till följande inkluderingsdirektiv högst upp för att inkludera denna nya header-fil:

    ```cpp
    #include "text_to_speech.h"
    ```

1. I funktionen `setup`, under anropet till `speechToText.init();`, lägg till följande för att initiera klassen `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Bygg denna kod, ladda upp den till din Wio Terminal och testa den via seriell monitor. Se till att din funktionsapp körs.

    Du kommer att se listan över tillgängliga röster som returneras från funktionsappen, tillsammans med den valda rösten.

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

## Konvertera text till tal

När du har en röst att använda kan den användas för att konvertera text till tal. Samma minnesbegränsningar med röster gäller också när tal konverteras till text, så du måste skriva talet till ett SD-kort för att kunna spelas upp via ReSpeaker.

> 💁 I tidigare lektioner i detta projekt använde du flashminne för att lagra tal som fångats från mikrofonen. Denna lektion använder ett SD-kort eftersom det är enklare att spela upp ljud från det med hjälp av Seeed-ljudbiblioteken.

Det finns också en annan begränsning att ta hänsyn till, tillgängliga ljuddata från tal-tjänsten och de format som Wio Terminal stöder. Till skillnad från fullständiga datorer kan ljudbibliotek för mikrocontrollers vara mycket begränsade i de ljudformat de stöder. Till exempel stöder Seeed Arduino Audio-biblioteket som kan spela ljud via ReSpeaker endast ljud med en samplingsfrekvens på 44,1KHz. Azure tal-tjänster kan tillhandahålla ljud i flera format, men inget av dem använder denna samplingsfrekvens, de tillhandahåller endast 8KHz, 16KHz, 24KHz och 48KHz. Detta innebär att ljudet måste om-samplas till 44,1KHz, något som skulle kräva mer resurser än vad Wio Terminal har, särskilt minne.

När det behövs att manipulera data som detta är det ofta bättre att använda serverlös kod, särskilt om data hämtas via ett webb-anrop. Wio Terminal kan anropa en serverlös funktion, skicka in texten som ska konverteras, och den serverlösa funktionen kan både anropa tal-tjänsten för att konvertera text till tal, samt om-sampla ljudet till den erforderliga samplingsfrekvensen. Den kan sedan returnera ljudet i det format som Wio Terminal behöver för att lagras på SD-kortet och spelas upp via ReSpeaker.

### Uppgift - skapa en serverlös funktion för att konvertera text till tal

1. Öppna ditt `smart-timer-trigger`-projekt i VS Code och öppna terminalen, se till att den virtuella miljön är aktiverad. Om inte, avsluta och återskapa terminalen.

1. Lägg till en ny HTTP-trigger till denna app kallad `text-to-speech` med följande kommando från terminalen i rotmappen för funktionsapp-projektet:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Detta skapar en HTTP-trigger kallad `text-to-speech`.

1. Pip-paketet [librosa](https://librosa.org) har funktioner för att om-sampla ljud, så lägg till detta i filen `requirements.txt`:

    ```sh
    librosa
    ```

    När detta har lagts till, installera Pip-paketen med följande kommando från VS Code-terminalen:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Om du använder Linux, inklusive Raspberry Pi OS, kan du behöva installera `libsndfile` med följande kommando:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. För att konvertera text till tal kan du inte använda API-nyckeln direkt, istället måste du begära en åtkomsttoken, med hjälp av API-nyckeln för att autentisera åtkomsttoken-begäran. Öppna filen `__init__.py` från mappen `text-to-speech` och ersätt all kod i den med följande:

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

    Detta definierar konstanter för platsen och tal-nyckeln som kommer att läsas från inställningarna. Det definierar sedan funktionen `get_access_token` som kommer att hämta en åtkomsttoken för tal-tjänsten.

1. Nedanför denna kod, lägg till följande:

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

    Detta definierar HTTP-triggern som konverterar text till tal. Den extraherar texten som ska konverteras, språket och rösten från JSON-kroppen som skickas med begäran, bygger lite SSML för att begära talet, och anropar sedan relevant REST-API med autentisering via åtkomsttoken. Detta REST-API-anrop returnerar ljudet kodad som en 16-bitars, 48KHz mono WAV-fil, definierad av värdet `playback_format`, som skickas till REST-API-anropet.

    Detta om-samplas sedan av `librosa` från en samplingsfrekvens på 48KHz till en samplingsfrekvens på 44,1KHz, och detta ljud sparas sedan till en binär buffert som sedan returneras.

1. Kör din funktionsapp lokalt, eller distribuera den till molnet. Du kan sedan anropa detta med ett verktyg som curl på samma sätt som du testade din `text-to-timer` HTTP-trigger. Se till att skicka språket, rösten och texten som JSON-kropp:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Ersätt `<language>` med ditt språk, till exempel `en-GB` eller `zh-CN`. Ersätt `<voice>` med rösten du vill använda. Ersätt `<text>` med texten du vill konvertera till tal. Du kan spara utdata till en fil och spela upp den med vilken ljudspelare som helst som kan spela WAV-filer.

    Till exempel, för att konvertera "Hello" till tal med amerikansk engelska och rösten Jenny Neural, med funktionsappen som körs lokalt, kan du använda följande curl-kommando:

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

    Detta kommer att spara ljudet till `hello.wav` i den aktuella katalogen.

> 💁 Du kan hitta denna kod i mappen [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Uppgift - hämta talet från din Wio Terminal

1. Öppna projektet `smart-timer` i VS Code om det inte redan är öppet.

1. Öppna header-filen `config.h` och lägg till URL:en för din funktionsapp:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Ersätt `<URL>` med URL:en för HTTP-triggern `text-to-speech` i din funktionsapp. Detta kommer att vara samma som värdet för `TEXT_TO_TIMER_FUNCTION_URL`, förutom med funktionsnamnet `text-to-speech` istället för `text-to-timer`.

1. Öppna header-filen `text_to_speech.h` och lägg till följande metod i den publika sektionen av klassen `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Till metoden `convertTextToSpeech`, lägg till följande kod för att skapa JSON som ska skickas till funktionsappen:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Detta skriver språket, rösten och texten till JSON-dokumentet och serialiserar det till en sträng.

1. Nedanför detta, lägg till följande kod för att anropa funktionsappen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Detta skapar en HTTPClient och gör en POST-begäran med JSON-dokumentet till HTTP-triggern för text-till-tal.

1. Om anropet fungerar kan de råa binära data som returneras från funktionsapp-anropet strömmas till en fil på SD-kortet. Lägg till följande kod för att göra detta:

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

    Denna kod kontrollerar svaret, och om det är 200 (framgång), strömmas de binära data till en fil i roten av SD-kortet kallad `SPEECH.WAV`.

1. I slutet av denna metod, stäng HTTP-anslutningen:

    ```cpp
    httpClient.end();
    ```

1. Texten som ska talas kan nu konverteras till ljud. I filen `main.cpp`, lägg till följande rad i slutet av funktionen `say` för att konvertera texten som ska sägas till ljud:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Uppgift - spela upp ljud från din Wio Terminal

**Kommer snart**

## Distribuera din functions-app till molnet

Anledningen till att köra functions-appen lokalt är att `librosa`-paketet för Pip på Linux har ett beroende av ett bibliotek som inte är installerat som standard och som måste installeras innan functions-appen kan köras. Functions-appar är serverlösa - det finns inga servrar som du kan hantera själv, så det finns inget sätt att installera detta bibliotek i förväg.

Lösningen är istället att distribuera din functions-app med hjälp av en Docker-container. Denna container distribueras av molnet varje gång det behöver starta en ny instans av din functions-app (till exempel när efterfrågan överstiger de tillgängliga resurserna, eller om functions-appen inte har använts på ett tag och stängs ner).

Du kan hitta instruktioner för att skapa en functions-app och distribuera via Docker i [dokumentationen för att skapa en funktion på Linux med en anpassad container på Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

När detta har distribuerats kan du anpassa din Wio Terminal-kod för att komma åt denna funktion:

1. Lägg till Azure Functions-certifikatet i `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Ändra alla inkluderade filer från `<WiFiClient.h>` till `<WiFiClientSecure.h>`.

1. Ändra alla `WiFiClient`-fält till `WiFiClientSecure`.

1. I varje klass som har ett `WiFiClientSecure`-fält, lägg till en konstruktor och sätt certifikatet i den konstruktorn:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.