<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T21:10:15+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "sw"
}
-->
# Uandishi wa maandishi hadi sauti - Wio Terminal

Katika sehemu hii ya somo, utabadilisha maandishi kuwa sauti ili kutoa maoni ya sauti.

## Uandishi wa maandishi hadi sauti

SDK ya huduma za sauti uliyotumia katika somo lililopita kubadilisha sauti kuwa maandishi inaweza pia kutumika kubadilisha maandishi kuwa sauti.

## Kupata orodha ya sauti

Unapoomba sauti, unahitaji kutoa sauti itakayotumika kwa kuwa sauti inaweza kuzalishwa kwa kutumia sauti mbalimbali. Kila lugha inaunga mkono aina mbalimbali za sauti, na unaweza kupata orodha ya sauti zinazoungwa mkono kwa kila lugha kutoka kwa SDK ya huduma za sauti. Hapa ndipo vikwazo vya microcontrollers vinapokuja - ombi la kupata orodha ya sauti zinazoungwa mkono na huduma za maandishi hadi sauti ni hati ya JSON yenye ukubwa wa zaidi ya 77KB, ambayo ni kubwa sana kushughulikiwa na Wio Terminal. Wakati wa kuandika, orodha kamili ina sauti 215, kila moja ikifafanuliwa na hati ya JSON kama ifuatavyo:

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

Hii ni JSON ya sauti ya **Aria**, ambayo ina mitindo mbalimbali ya sauti. Kinachohitajika tu wakati wa kubadilisha maandishi kuwa sauti ni jina fupi, `en-US-AriaNeural`.

Badala ya kupakua na kufafanua orodha hii yote kwenye microcontroller yako, utahitaji kuandika msimbo wa serverless ili kupata orodha ya sauti kwa lugha unayotumia, na kuita hii kutoka kwa Wio Terminal yako. Msimbo wako unaweza kisha kuchagua sauti inayofaa kutoka kwenye orodha, kama vile ya kwanza inayopatikana.

### Kazi - unda kazi ya serverless kupata orodha ya sauti

1. Fungua mradi wako wa `smart-timer-trigger` kwenye VS Code, na fungua terminal ukihakikisha mazingira ya virtual yamewashwa. Ikiwa sivyo, zima na uunde upya terminal.

1. Fungua faili ya `local.settings.json` na ongeza mipangilio ya API key ya sauti na eneo:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Badilisha `<key>` na API key ya rasilimali yako ya huduma za sauti. Badilisha `<location>` na eneo ulilotumia ulipounda rasilimali ya huduma za sauti.

1. Ongeza trigger mpya ya HTTP kwenye programu hii inayoitwa `get-voices` kwa kutumia amri ifuatayo kutoka ndani ya terminal ya VS Code kwenye folda kuu ya mradi wa programu za functions:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Hii itaunda trigger ya HTTP inayoitwa `get-voices`.

1. Badilisha yaliyomo ya faili ya `__init__.py` kwenye folda ya `get-voices` na yafuatayo:

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

    Msimbo huu hufanya ombi la HTTP kwa endpoint ili kupata sauti. Orodha hii ya sauti ni block kubwa ya JSON yenye sauti kwa lugha zote, kwa hivyo sauti za lugha iliyotumwa kwenye mwili wa ombi huchujwa, kisha jina fupi linatolewa na kurudishwa kama orodha ya JSON. Jina fupi ndilo thamani inayohitajika kubadilisha maandishi kuwa sauti, kwa hivyo ni thamani hii pekee inayorudishwa.

    > 💁 Unaweza kubadilisha kichujio kama inavyohitajika kuchagua tu sauti unazotaka.

    Hii inapunguza ukubwa wa data kutoka 77KB (wakati wa kuandika), hadi hati ndogo zaidi ya JSON. Kwa mfano, kwa sauti za Marekani hii ni bytes 408.

1. Endesha programu yako ya functions kwa ndani. Unaweza kisha kuita hii kwa kutumia zana kama curl kwa njia ile ile ulivyopima trigger ya HTTP ya `text-to-timer`. Hakikisha unapita lugha yako kama mwili wa JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Badilisha `<language>` na lugha yako, kama `en-GB`, au `zh-CN`.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Kazi - pata sauti kutoka kwa Wio Terminal yako

1. Fungua mradi wa `smart-timer` kwenye VS Code ikiwa haujafunguliwa tayari.

1. Fungua faili ya kichwa `config.h` na ongeza URL ya programu yako ya functions:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Badilisha `<URL>` na URL ya trigger ya HTTP ya `get-voices` kwenye programu yako ya functions. Hii itakuwa sawa na thamani ya `TEXT_TO_TIMER_FUNCTION_URL`, isipokuwa na jina la function `get-voices` badala ya `text-to-timer`.

1. Unda faili mpya kwenye folda ya `src` inayoitwa `text_to_speech.h`. Hii itatumika kufafanua darasa la kubadilisha kutoka maandishi hadi sauti.

1. Ongeza maagizo ya kujumuisha yafuatayo juu ya faili mpya ya `text_to_speech.h`:

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

1. Ongeza msimbo ufuatao chini ya haya ili kutangaza darasa la `TextToSpeech`, pamoja na mfano ambao unaweza kutumika katika programu nzima:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Ili kuita programu yako ya functions, unahitaji kutangaza mteja wa WiFi. Ongeza yafuatayo kwenye sehemu ya `private` ya darasa:

    ```cpp
    WiFiClient _client;
    ```

1. Katika sehemu ya `private`, ongeza uwanja wa sauti iliyochaguliwa:

    ```cpp
    String _voice;
    ```

1. Kwa sehemu ya `public`, ongeza kazi ya `init` ambayo itapata sauti ya kwanza:

    ```cpp
    void init()
    {
    }
    ```

1. Ili kupata sauti, hati ya JSON inahitaji kutumwa kwa programu ya functions na lugha. Ongeza msimbo ufuatao kwenye kazi ya `init` ili kuunda hati hii ya JSON:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Kisha unda `HTTPClient`, kisha uitumie kuita programu ya functions ili kupata sauti, ukituma hati ya JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Chini ya hii, ongeza msimbo wa kuangalia msimbo wa majibu, na ikiwa ni 200 (mafanikio), toa orodha ya sauti, ukipata ya kwanza kutoka kwenye orodha:

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

1. Baada ya hii, maliza muunganisho wa mteja wa HTTP:

    ```cpp
    httpClient.end();
    ```

1. Fungua faili ya `main.cpp`, na ongeza maagizo ya kujumuisha yafuatayo juu ili kujumuisha faili hii mpya ya kichwa:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Katika kazi ya `setup`, chini ya wito wa `speechToText.init();`, ongeza yafuatayo ili kuanzisha darasa la `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Jenga msimbo huu, upakie kwenye Wio Terminal yako na ujaribu kupitia serial monitor. Hakikisha programu yako ya functions inaendeshwa.

    Utaona orodha ya sauti zinazopatikana zikirudishwa kutoka kwa programu ya functions, pamoja na sauti iliyochaguliwa.

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

## Badilisha maandishi kuwa sauti

Mara unapokuwa na sauti ya kutumia, inaweza kutumika kubadilisha maandishi kuwa sauti. Vikwazo sawa vya kumbukumbu na sauti pia vinatumika wakati wa kubadilisha sauti kuwa maandishi, kwa hivyo utahitaji kuandika sauti kwenye kadi ya SD tayari kuchezwa kupitia ReSpeaker.

> 💁 Katika masomo ya awali ya mradi huu ulitumia kumbukumbu ya flash kuhifadhi sauti iliyorekodiwa kutoka kwa kipaza sauti. Somo hili linatumia kadi ya SD kwa kuwa ni rahisi kucheza sauti kutoka kwake kwa kutumia maktaba za sauti za Seeed.

Kuna pia kikwazo kingine cha kuzingatia, data ya sauti inayopatikana kutoka kwa huduma za sauti, na miundo ambayo Wio Terminal inasaidia. Tofauti na kompyuta kamili, maktaba za sauti kwa microcontrollers zinaweza kuwa na mipaka sana katika miundo ya sauti wanayounga mkono. Kwa mfano, maktaba ya Seeed Arduino Audio inayoweza kucheza sauti kupitia ReSpeaker inaunga mkono tu sauti kwa kiwango cha sampuli cha 44.1KHz. Huduma za sauti za Azure zinaweza kutoa sauti katika miundo kadhaa, lakini hakuna hata moja inayotumia kiwango hiki cha sampuli, zinatoa tu 8KHz, 16KHz, 24KHz na 48KHz. Hii inamaanisha sauti inahitaji kubadilishwa kuwa 44.1KHz, jambo ambalo lingehitaji rasilimali zaidi kuliko Wio Terminal inavyoweza, hasa kumbukumbu.

Unapohitaji kudhibiti data kama hii, mara nyingi ni bora kutumia msimbo wa serverless, hasa ikiwa data inatolewa kupitia wito wa wavuti. Wio Terminal inaweza kuita kazi ya serverless, ikipitisha maandishi ya kubadilisha, na kazi ya serverless inaweza kuita huduma ya sauti kubadilisha maandishi kuwa sauti, pamoja na kubadilisha sampuli ya sauti kwa kiwango kinachohitajika. Inaweza kisha kurudisha sauti katika fomu ambayo Wio Terminal inahitaji kuhifadhi kwenye kadi ya SD na kucheza kupitia ReSpeaker.

### Kazi - unda kazi ya serverless kubadilisha maandishi kuwa sauti

1. Fungua mradi wako wa `smart-timer-trigger` kwenye VS Code, na fungua terminal ukihakikisha mazingira ya virtual yamewashwa. Ikiwa sivyo, zima na uunde upya terminal.

1. Ongeza trigger mpya ya HTTP kwenye programu hii inayoitwa `text-to-speech` kwa kutumia amri ifuatayo kutoka ndani ya terminal ya VS Code kwenye folda kuu ya mradi wa programu za functions:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Hii itaunda trigger ya HTTP inayoitwa `text-to-speech`.

1. Pakiti ya Pip ya [librosa](https://librosa.org) ina kazi za kubadilisha sampuli ya sauti, kwa hivyo ongeza hii kwenye faili ya `requirements.txt`:

    ```sh
    librosa
    ```

    Mara hii imeongezwa, sakinisha pakiti za Pip kwa kutumia amri ifuatayo kutoka terminal ya VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Ikiwa unatumia Linux, ikiwa ni pamoja na Raspberry Pi OS, unaweza kuhitaji kusakinisha `libsndfile` kwa amri ifuatayo:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Ili kubadilisha maandishi kuwa sauti, huwezi kutumia API key ya sauti moja kwa moja, badala yake unahitaji kuomba tokeni ya ufikiaji, ukitumia API key kuthibitisha ombi la tokeni ya ufikiaji. Fungua faili ya `__init__.py` kutoka folda ya `text-to-speech` na badilisha msimbo wote ndani yake na yafuatayo:

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

    Hii inafafanua constants za eneo na API key ya sauti ambayo itasomwa kutoka mipangilio. Kisha inafafanua kazi ya `get_access_token` ambayo itapata tokeni ya ufikiaji kwa huduma ya sauti.

1. Chini ya msimbo huu, ongeza yafuatayo:

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

    Hii inafafanua trigger ya HTTP inayobadilisha maandishi kuwa sauti. Inatoa maandishi ya kubadilisha, lugha na sauti kutoka mwili wa JSON uliowekwa kwenye ombi, inajenga SSML kuomba sauti, kisha inaita REST API husika ikithibitisha kwa kutumia tokeni ya ufikiaji. Wito huu wa REST API unarudisha sauti iliyosimbwa kama faili ya WAV ya mono ya 16-bit, 48KHz, iliyofafanuliwa na thamani ya `playback_format`, ambayo inatumwa kwa wito wa REST API.

    Hii kisha inabadilishwa sampuli na `librosa` kutoka kiwango cha sampuli cha 48KHz hadi kiwango cha sampuli cha 44.1KHz, kisha sauti hii inaokolewa kwenye buffer ya binary ambayo kisha inarudishwa.

1. Endesha programu yako ya functions kwa ndani, au ipeleke kwenye wingu. Unaweza kisha kuita hii kwa kutumia zana kama curl kwa njia ile ile ulivyopima trigger ya HTTP ya `text-to-timer`. Hakikisha unapita lugha, sauti na maandishi kama mwili wa JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Badilisha `<language>` na lugha yako, kama `en-GB`, au `zh-CN`. Badilisha `<voice>` na sauti unayotaka kutumia. Badilisha `<text>` na maandishi unayotaka kubadilisha kuwa sauti. Unaweza kuhifadhi matokeo kwenye faili na kuyacheza kwa mchezaji wowote wa sauti anayeweza kucheza faili za WAV.

    Kwa mfano, kubadilisha "Hello" kuwa sauti kwa kutumia Kiingereza cha Marekani na sauti ya Jenny Neural, na programu ya functions ikiendeshwa kwa ndani, unaweza kutumia amri ya curl ifuatayo:

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

    Hii itaokoa sauti kwenye `hello.wav` kwenye saraka ya sasa.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Kazi - pata sauti kutoka kwa Wio Terminal yako

1. Fungua mradi wa `smart-timer` kwenye VS Code ikiwa haujafunguliwa tayari.

1. Fungua faili ya kichwa `config.h` na ongeza URL ya programu yako ya functions:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Badilisha `<URL>` na URL ya trigger ya HTTP ya `text-to-speech` kwenye programu yako ya functions. Hii itakuwa sawa na thamani ya `TEXT_TO_TIMER_FUNCTION_URL`, isipokuwa na jina la function `text-to-speech` badala ya `text-to-timer`.

1. Fungua faili ya kichwa `text_to_speech.h`, na ongeza njia ifuatayo kwenye sehemu ya `public` ya darasa la `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Kwa njia ya `convertTextToSpeech`, ongeza msimbo ufuatao kuunda JSON ya kutuma kwa programu ya functions:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Hii inaandika lugha, sauti na maandishi kwenye hati ya JSON, kisha inaiandika kama kamba.

1. Chini ya hii, ongeza msimbo ufuatao kuita programu ya functions:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Hii inaunda `HTTPClient`, kisha inafanya ombi la POST kwa kutumia hati ya JSON kwa trigger ya HTTP ya maandishi hadi sauti.

1. Ikiwa wito unafanikiwa, data ya binary mbichi inayorudishwa kutoka kwa wito wa programu ya functions inaweza kufululizwa kwenye faili kwenye kadi ya SD. Ongeza msimbo ufuatao kufanya hivi:

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

    Msimbo huu unakagua majibu, na ikiwa ni 200 (mafanikio), data ya binary inafululizwa kwenye faili kwenye mzizi wa Kadi ya SD inayoitwa `SPEECH.WAV`.

1. Mwishoni mwa njia hii, funga muunganisho wa HTTP:

    ```cpp
    httpClient.end();
    ```

1. Maandishi ya kusema sasa yanaweza kubadilishwa kuwa sauti. Katika faili ya `main.cpp`, ongeza mstari ufuatao mwishoni mwa kazi ya `say` kubadilisha maandishi ya kusema kuwa sauti:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Kazi - kucheza sauti kutoka kwa Wio Terminal yako

**Inakuja hivi karibuni**

## Kuweka programu yako ya kazi kwenye wingu

Sababu ya kuendesha programu ya kazi kwa ndani ni kwamba kifurushi cha Pip `librosa` kwenye Linux kina utegemezi wa maktaba ambayo haijasakinishwa kwa chaguo-msingi, na itahitaji kusakinishwa kabla ya programu ya kazi kuweza kuendeshwa. Programu za kazi ni bila seva - hakuna seva unazoweza kudhibiti mwenyewe, kwa hivyo hakuna njia ya kusakinisha maktaba hii mapema.

Njia ya kufanya hili ni badala yake kuweka programu yako ya kazi kwa kutumia kontena la Docker. Kontena hili linawekwa na wingu kila wakati linapohitaji kuanzisha mfano mpya wa programu yako ya kazi (kama vile wakati mahitaji yanazidi rasilimali zilizopo, au ikiwa programu ya kazi haijatumika kwa muda na imefungwa).

Unaweza kupata maelekezo ya kuanzisha programu ya kazi na kuweka kupitia Docker katika [undaa kazi kwenye Linux kwa kutumia nyaraka za kontena maalum kwenye Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Baada ya hii kuwekwa, unaweza kuhamisha msimbo wa Wio Terminal yako ili kufikia kazi hii:

1. Ongeza cheti cha Azure Functions kwenye `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Badilisha viingizo vyote vya `
<WiFiClient.h>` kuwa `<WiFiClientSecure.h>`.

1. Badilisha sehemu zote za `WiFiClient` kuwa `WiFiClientSecure`.

1. Katika kila darasa lenye sehemu ya `WiFiClientSecure`, ongeza konstrukta na weka cheti katika konstrukta hiyo:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kwa usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, inashauriwa kutumia huduma ya mtafsiri wa kibinadamu mtaalamu. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.