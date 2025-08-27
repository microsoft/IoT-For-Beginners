<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T20:56:10+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "no"
}
-->
# Tekst til tale - Wio Terminal

I denne delen av leksjonen skal du konvertere tekst til tale for å gi muntlig tilbakemelding.

## Tekst til tale

SDK-en for tale-tjenester som du brukte i forrige leksjon for å konvertere tale til tekst, kan også brukes til å konvertere tekst tilbake til tale.

## Hent en liste over stemmer

Når du ber om tale, må du spesifisere hvilken stemme som skal brukes, siden tale kan genereres med en rekke forskjellige stemmer. Hvert språk støtter et utvalg av ulike stemmer, og du kan få en liste over støttede stemmer for hvert språk fra tale-tjenestenes SDK. Her kommer begrensningene til mikrokontrollere inn i bildet – kallet for å hente listen over stemmer som støttes av tekst-til-tale-tjenestene er et JSON-dokument på over 77KB, altfor stort til å behandles av Wio Terminal. På tidspunktet for skriving inneholder hele listen 215 stemmer, hver definert av et JSON-dokument som dette:

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

Dette JSON-dokumentet er for stemmen **Aria**, som har flere stemmestiler. Alt som trengs for å konvertere tekst til tale er kortnavnet, `en-US-AriaNeural`.

I stedet for å laste ned og dekode hele denne listen på mikrokontrolleren, må du skrive litt mer serverløs kode for å hente listen over stemmer for språket du bruker, og kalle denne fra Wio Terminal. Koden din kan deretter velge en passende stemme fra listen, for eksempel den første den finner.

### Oppgave - opprett en serverløs funksjon for å hente en liste over stemmer

1. Åpne prosjektet ditt `smart-timer-trigger` i VS Code, og åpne terminalen, og sørg for at det virtuelle miljøet er aktivert. Hvis ikke, avslutt og opprett terminalen på nytt.

1. Åpne filen `local.settings.json` og legg til innstillinger for tale-API-nøkkelen og plasseringen:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Erstatt `<key>` med API-nøkkelen for tale-tjenesten din. Erstatt `<location>` med plasseringen du brukte da du opprettet tale-tjenesten.

1. Legg til en ny HTTP-trigger i denne appen kalt `get-voices` ved å bruke følgende kommando fra terminalen i rotmappen til funksjonsapp-prosjektet:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Dette vil opprette en HTTP-trigger kalt `get-voices`.

1. Erstatt innholdet i filen `__init__.py` i mappen `get-voices` med følgende:

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

    Denne koden gjør et HTTP-kall til endepunktet for å hente stemmene. Listen over stemmer er en stor JSON-blokk med stemmer for alle språk, så stemmene for språket som sendes i forespørselens kropp blir filtrert ut, og deretter blir kortnavnet hentet ut og returnert som en JSON-liste. Kortnavnet er verdien som trengs for å konvertere tekst til tale, så bare denne verdien returneres.

    > 💁 Du kan endre filteret etter behov for å velge bare de stemmene du ønsker.

    Dette reduserer datastørrelsen fra 77KB (på tidspunktet for skriving) til et mye mindre JSON-dokument. For eksempel, for amerikanske stemmer er dette 408 byte.

1. Kjør funksjonsappen din lokalt. Du kan deretter kalle denne ved å bruke et verktøy som curl på samme måte som du testet HTTP-triggeren `text-to-timer`. Sørg for å sende språket som en JSON-kropp:

    ```json
    {
        "language":"<language>"
    }
    ```

    Erstatt `<language>` med språket ditt, for eksempel `en-GB` eller `zh-CN`.

> 💁 Du finner denne koden i mappen [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Oppgave - hent stemmen fra Wio Terminal

1. Åpne prosjektet `smart-timer` i VS Code hvis det ikke allerede er åpent.

1. Åpne header-filen `config.h` og legg til URL-en for funksjonsappen din:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Erstatt `<URL>` med URL-en for HTTP-triggeren `get-voices` i funksjonsappen din. Dette vil være det samme som verdien for `TEXT_TO_TIMER_FUNCTION_URL`, bortsett fra at funksjonsnavnet er `get-voices` i stedet for `text-to-timer`.

1. Opprett en ny fil i mappen `src` kalt `text_to_speech.h`. Denne vil bli brukt til å definere en klasse for å konvertere fra tekst til tale.

1. Legg til følgende include-direktiver øverst i den nye filen `text_to_speech.h`:

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

1. Legg til følgende kode under dette for å erklære klassen `TextToSpeech`, sammen med en instans som kan brukes i resten av applikasjonen:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. For å kalle funksjonsappen din, må du erklære en WiFi-klient. Legg til følgende i den private delen av klassen:

    ```cpp
    WiFiClient _client;
    ```

1. I den private delen, legg til et felt for den valgte stemmen:

    ```cpp
    String _voice;
    ```

1. I den offentlige delen, legg til en `init`-funksjon som vil hente den første stemmen:

    ```cpp
    void init()
    {
    }
    ```

1. For å hente stemmene, må et JSON-dokument sendes til funksjonsappen med språket. Legg til følgende kode i `init`-funksjonen for å opprette dette JSON-dokumentet:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Opprett deretter en `HTTPClient`, og bruk den til å kalle funksjonsappen for å hente stemmene, ved å sende JSON-dokumentet:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Under dette, legg til kode for å sjekke svarskoden, og hvis den er 200 (suksess), hent listen over stemmer og velg den første fra listen:

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

1. Etter dette, avslutt HTTP-klienttilkoblingen:

    ```cpp
    httpClient.end();
    ```

1. Åpne filen `main.cpp`, og legg til følgende include-direktiv øverst for å inkludere denne nye header-filen:

    ```cpp
    #include "text_to_speech.h"
    ```

1. I `setup`-funksjonen, under kallet til `speechToText.init();`, legg til følgende for å initialisere klassen `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Bygg denne koden, last den opp til Wio Terminal og test den gjennom seriemonitoren. Sørg for at funksjonsappen din kjører.

    Du vil se listen over tilgjengelige stemmer returnert fra funksjonsappen, sammen med den valgte stemmen.

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

Når du har en stemme å bruke, kan den brukes til å konvertere tekst til tale. De samme minnebegrensningene med stemmer gjelder også når du konverterer tekst til tale, så du må skrive talen til et SD-kort for å kunne spille den av via ReSpeaker.

> 💁 I tidligere leksjoner i dette prosjektet brukte du flashminne for å lagre tale fanget fra mikrofonen. Denne leksjonen bruker et SD-kort, da det er enklere å spille av lyd fra det ved hjelp av Seeed-lydbibliotekene.

Det er også en annen begrensning å vurdere, nemlig tilgjengelige lyddata fra tale-tjenesten og formatene som Wio Terminal støtter. I motsetning til fullverdige datamaskiner, kan lydbiblioteker for mikrokontrollere være svært begrenset i lydformatene de støtter. For eksempel støtter Seeed Arduino Audio-biblioteket som kan spille lyd via ReSpeaker kun lyd med en samplingsfrekvens på 44,1 kHz. Azure tale-tjenester kan levere lyd i flere formater, men ingen av dem bruker denne samplingsfrekvensen; de tilbyr kun 8 kHz, 16 kHz, 24 kHz og 48 kHz. Dette betyr at lyden må re-samples til 44,1 kHz, noe som krever mer ressurser enn det Wio Terminal har, spesielt minne.

Når det er behov for å manipulere data som dette, er det ofte bedre å bruke serverløs kode, spesielt hvis dataene hentes via et webkall. Wio Terminal kan kalle en serverløs funksjon, sende inn teksten som skal konverteres, og den serverløse funksjonen kan både kalle tale-tjenesten for å konvertere tekst til tale, samt re-sample lyden til den nødvendige samplingsfrekvensen. Den kan deretter returnere lyden i det formatet Wio Terminal trenger for å lagres på SD-kortet og spilles av via ReSpeaker.

### Oppgave - opprett en serverløs funksjon for å konvertere tekst til tale

1. Åpne prosjektet ditt `smart-timer-trigger` i VS Code, og åpne terminalen, og sørg for at det virtuelle miljøet er aktivert. Hvis ikke, avslutt og opprett terminalen på nytt.

1. Legg til en ny HTTP-trigger i denne appen kalt `text-to-speech` ved å bruke følgende kommando fra terminalen i rotmappen til funksjonsapp-prosjektet:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Dette vil opprette en HTTP-trigger kalt `text-to-speech`.

1. Pip-pakken [librosa](https://librosa.org) har funksjoner for å re-sample lyd, så legg denne til i filen `requirements.txt`:

    ```sh
    librosa
    ```

    Når dette er lagt til, installer Pip-pakkene ved å bruke følgende kommando fra VS Code-terminalen:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Hvis du bruker Linux, inkludert Raspberry Pi OS, må du kanskje installere `libsndfile` med følgende kommando:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. For å konvertere tekst til tale kan du ikke bruke tale-API-nøkkelen direkte, i stedet må du be om en tilgangstoken, ved å bruke API-nøkkelen for å autentisere forespørselen om tilgangstoken. Åpne filen `__init__.py` fra mappen `text-to-speech` og erstatt all koden i den med følgende:

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

    Dette definerer konstanter for plasseringen og tale-nøkkelen som vil bli lest fra innstillingene. Det definerer deretter funksjonen `get_access_token` som vil hente en tilgangstoken for tale-tjenesten.

1. Under denne koden, legg til følgende:

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

    Dette definerer HTTP-triggeren som konverterer tekst til tale. Den henter teksten som skal konverteres, språket og stemmen fra JSON-kroppen sendt til forespørselen, bygger litt SSML for å be om talen, og kaller deretter den relevante REST-API-en ved å autentisere med tilgangstokenet. Dette REST-API-kallet returnerer lyden kodet som en 16-bit, 48 kHz mono WAV-fil, definert av verdien av `playback_format`, som sendes til REST-API-kallet.

    Dette blir deretter re-samplet av `librosa` fra en samplingsfrekvens på 48 kHz til en samplingsfrekvens på 44,1 kHz, og denne lyden lagres deretter i en binær buffer som returneres.

1. Kjør funksjonsappen din lokalt, eller distribuer den til skyen. Du kan deretter kalle denne ved å bruke et verktøy som curl på samme måte som du testet HTTP-triggeren `text-to-timer`. Sørg for å sende språket, stemmen og teksten som JSON-kropp:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Erstatt `<language>` med språket ditt, for eksempel `en-GB` eller `zh-CN`. Erstatt `<voice>` med stemmen du vil bruke. Erstatt `<text>` med teksten du vil konvertere til tale. Du kan lagre utdataene til en fil og spille den av med en hvilken som helst lydspiller som kan spille WAV-filer.

    For eksempel, for å konvertere "Hello" til tale ved bruk av amerikansk engelsk med stemmen Jenny Neural, med funksjonsappen kjørende lokalt, kan du bruke følgende curl-kommando:

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

    Dette vil lagre lyden til `hello.wav` i den gjeldende katalogen.

> 💁 Du finner denne koden i mappen [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Oppgave - hent talen fra Wio Terminal

1. Åpne prosjektet `smart-timer` i VS Code hvis det ikke allerede er åpent.

1. Åpne header-filen `config.h` og legg til URL-en for funksjonsappen din:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Erstatt `<URL>` med URL-en for HTTP-triggeren `text-to-speech` i funksjonsappen din. Dette vil være det samme som verdien for `TEXT_TO_TIMER_FUNCTION_URL`, bortsett fra at funksjonsnavnet er `text-to-speech` i stedet for `text-to-timer`.

1. Åpne header-filen `text_to_speech.h`, og legg til følgende metode i den offentlige delen av klassen `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. I metoden `convertTextToSpeech`, legg til følgende kode for å opprette JSON som skal sendes til funksjonsappen:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dette skriver språket, stemmen og teksten til JSON-dokumentet, og serialiserer det deretter til en streng.

1. Under dette, legg til følgende kode for å kalle funksjonsappen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dette oppretter en HTTPClient, og gjør deretter en POST-forespørsel med JSON-dokumentet til HTTP-triggeren for tekst til tale.

1. Hvis kallet fungerer, kan de rå binære dataene som returneres fra funksjonsapp-kallet streames til en fil på SD-kortet. Legg til følgende kode for å gjøre dette:

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

    Denne koden sjekker svaret, og hvis det er 200 (suksess), streames de binære dataene til en fil i roten av SD-kortet kalt `SPEECH.WAV`.

1. På slutten av denne metoden, lukk HTTP-tilkoblingen:

    ```cpp
    httpClient.end();
    ```

1. Teksten som skal sies kan nå konverteres til lyd. I filen `main.cpp`, legg til følgende linje på slutten av funksjonen `say` for å konvertere teksten som skal sies til lyd:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Oppgave - spille av lyd fra din Wio Terminal

**Kommer snart**

## Distribuere funksjonsappen din til skyen

Grunnen til at funksjonsappen kjøres lokalt er fordi `librosa` Pip-pakken på Linux har en avhengighet til et bibliotek som ikke er installert som standard, og dette må installeres før funksjonsappen kan kjøre. Funksjonsapper er serverløse - det finnes ingen servere du kan administrere selv, så det er ingen måte å installere dette biblioteket på forhånd.

Løsningen er å distribuere funksjonsappen din ved hjelp av en Docker-container. Denne containeren distribueres av skyen når det er behov for å starte en ny instans av funksjonsappen din (for eksempel når etterspørselen overstiger tilgjengelige ressurser, eller hvis funksjonsappen ikke har vært brukt på en stund og er stengt ned).

Du finner instruksjoner for å sette opp en funksjonsapp og distribuere via Docker i [dokumentasjonen for å opprette en funksjon på Linux ved hjelp av en tilpasset container på Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Når dette er distribuert, kan du overføre koden for din Wio Terminal for å få tilgang til denne funksjonen:

1. Legg til Azure Functions-sertifikatet i `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Endre alle inkluder av `
<WiFiClient.h>` til `<WiFiClientSecure.h>`.

1. Endre alle `WiFiClient`-felt til `WiFiClientSecure`.

1. I hver klasse som har et `WiFiClientSecure`-felt, legg til en konstruktør og sett sertifikatet i den konstruktøren:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.