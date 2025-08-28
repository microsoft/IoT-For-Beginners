<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T23:16:29+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "tl"
}
-->
# Text to Speech - Wio Terminal

Sa bahaging ito ng aralin, gagamitin mo ang text-to-speech upang makapagbigay ng pasalitang feedback.

## Text to Speech

Ang speech services SDK na ginamit mo sa nakaraang aralin para i-convert ang speech sa text ay maaari ring gamitin upang i-convert ang text pabalik sa speech.

## Kumuha ng Listahan ng mga Boses

Kapag humihiling ng speech, kailangan mong tukuyin ang boses na gagamitin dahil maaaring magawa ang speech gamit ang iba't ibang boses. Ang bawat wika ay may suporta para sa iba't ibang boses, at maaari mong makuha ang listahan ng mga suportadong boses para sa bawat wika mula sa speech services SDK. Dito papasok ang mga limitasyon ng microcontrollers - ang tawag upang makuha ang listahan ng mga boses na suportado ng text-to-speech services ay isang JSON document na higit sa 77KB ang laki, masyadong malaki upang ma-proseso ng Wio Terminal. Sa kasalukuyang panahon ng pagsulat, ang buong listahan ay naglalaman ng 215 boses, bawat isa ay tinukoy ng isang JSON document tulad ng sumusunod:

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

Ang JSON na ito ay para sa boses na **Aria**, na may iba't ibang estilo ng boses. Ang kailangan lamang kapag nagko-convert ng text sa speech ay ang shortname, `en-US-AriaNeural`.

Sa halip na i-download at i-decode ang buong listahan na ito sa iyong microcontroller, kailangan mong magsulat ng karagdagang serverless code upang makuha ang listahan ng mga boses para sa wikang ginagamit mo, at tawagin ito mula sa iyong Wio Terminal. Ang iyong code ay maaaring pumili ng angkop na boses mula sa listahan, tulad ng unang makita nito.

### Gawain - Gumawa ng Serverless Function para Kumuha ng Listahan ng mga Boses

1. Buksan ang iyong `smart-timer-trigger` na proyekto sa VS Code, at buksan ang terminal na siguraduhing naka-activate ang virtual environment. Kung hindi, patayin at muling likhain ang terminal.

1. Buksan ang file na `local.settings.json` at magdagdag ng mga setting para sa speech API key at lokasyon:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Palitan ang `<key>` ng API key para sa iyong speech service resource. Palitan ang `<location>` ng lokasyon na ginamit mo nang likhain ang speech service resource.

1. Magdagdag ng bagong HTTP trigger sa app na ito na tinatawag na `get-voices` gamit ang sumusunod na command mula sa loob ng VS Code terminal sa root folder ng functions app project:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Ito ay lilikha ng isang HTTP trigger na tinatawag na `get-voices`.

1. Palitan ang nilalaman ng file na `__init__.py` sa folder na `get-voices` ng sumusunod:

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

    Ang code na ito ay gumagawa ng HTTP request sa endpoint upang makuha ang mga boses. Ang listahan ng mga boses ay isang malaking bloke ng JSON na may mga boses para sa lahat ng wika, kaya ang mga boses para sa wikang ipinasa sa request body ay na-filter, pagkatapos ay kinuha ang shortname at ibinalik bilang isang JSON list. Ang shortname ang halaga na kailangan upang i-convert ang text sa speech, kaya ito lamang ang ibinabalik.

    > 💁 Maaari mong baguhin ang filter kung kinakailangan upang piliin lamang ang mga boses na gusto mo.

    Binabawasan nito ang laki ng data mula 77KB (sa panahon ng pagsulat), sa mas maliit na JSON document. Halimbawa, para sa mga US voices, ito ay 408 bytes.

1. Patakbuhin ang iyong function app nang lokal. Maaari mo itong tawagin gamit ang tool tulad ng curl sa parehong paraan na sinubukan mo ang iyong `text-to-timer` HTTP trigger. Siguraduhing ipasa ang iyong wika bilang JSON body:

    ```json
    {
        "language":"<language>"
    }
    ```

    Palitan ang `<language>` ng iyong wika, tulad ng `en-GB`, o `zh-CN`.

> 💁 Maaari mong makita ang code na ito sa [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) folder.

### Gawain - Kunin ang Boses mula sa Iyong Wio Terminal

1. Buksan ang proyekto na `smart-timer` sa VS Code kung hindi pa ito bukas.

1. Buksan ang header file na `config.h` at idagdag ang URL para sa iyong function app:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Palitan ang `<URL>` ng URL para sa `get-voices` HTTP trigger sa iyong function app. Ito ay magiging kapareho ng halaga para sa `TEXT_TO_TIMER_FUNCTION_URL`, maliban sa pangalan ng function na `get-voices` sa halip na `text-to-timer`.

1. Gumawa ng bagong file sa folder na `src` na tinatawag na `text_to_speech.h`. Ito ay gagamitin upang tukuyin ang isang klase para i-convert mula text sa speech.

1. Idagdag ang sumusunod na include directives sa itaas ng bagong file na `text_to_speech.h`:

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

1. Idagdag ang sumusunod na code sa ibaba nito upang ideklara ang klase na `TextToSpeech`, kasama ang isang instance na maaaring gamitin sa natitirang bahagi ng application:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Upang tawagin ang iyong functions app, kailangan mong ideklara ang isang WiFi client. Idagdag ang sumusunod sa `private` na seksyon ng klase:

    ```cpp
    WiFiClient _client;
    ```

1. Sa `private` na seksyon, magdagdag ng field para sa napiling boses:

    ```cpp
    String _voice;
    ```

1. Sa `public` na seksyon, magdagdag ng `init` function na kukuha ng unang boses:

    ```cpp
    void init()
    {
    }
    ```

1. Upang makuha ang mga boses, kailangang magpadala ng JSON document sa function app na may wika. Idagdag ang sumusunod na code sa `init` function upang lumikha ng JSON document na ito:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Susunod, gumawa ng `HTTPClient`, pagkatapos ay gamitin ito upang tawagin ang functions app upang makuha ang mga boses, na nagpo-post ng JSON document:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Sa ibaba nito, magdagdag ng code upang suriin ang response code, at kung ito ay 200 (tagumpay), kunin ang listahan ng mga boses, at kunin ang una mula sa listahan:

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

1. Pagkatapos nito, tapusin ang HTTP client connection:

    ```cpp
    httpClient.end();
    ```

1. Buksan ang file na `main.cpp`, at idagdag ang sumusunod na include directive sa itaas upang isama ang bagong header file na ito:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Sa `setup` function, sa ilalim ng tawag sa `speechToText.init();`, idagdag ang sumusunod upang i-initialize ang klase na `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. I-build ang code na ito, i-upload ito sa iyong Wio Terminal at subukan ito sa pamamagitan ng serial monitor. Siguraduhing tumatakbo ang iyong function app.

    Makikita mo ang listahan ng mga available na boses na ibinalik mula sa function app, kasama ang napiling boses.

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

## I-convert ang Text sa Speech

Kapag mayroon ka nang boses na gagamitin, maaari itong gamitin upang i-convert ang text sa speech. Ang parehong mga limitasyon sa memorya na may mga boses ay nalalapat din kapag nagko-convert ng speech sa text, kaya kailangan mong isulat ang speech sa isang SD card upang ma-play ito gamit ang ReSpeaker.

> 💁 Sa mga naunang aralin sa proyektong ito, gumamit ka ng flash memory upang mag-imbak ng speech na na-capture mula sa mikropono. Ang araling ito ay gumagamit ng SD card dahil mas madaling magpatugtog ng audio mula rito gamit ang Seeed audio libraries.

Mayroon ding isa pang limitasyon na dapat isaalang-alang, ang available na audio data mula sa speech service, at ang mga format na sinusuportahan ng Wio Terminal. Hindi tulad ng mga full computer, ang mga audio library para sa microcontrollers ay maaaring limitado sa mga audio format na sinusuportahan nila. Halimbawa, ang Seeed Arduino Audio library na maaaring magpatugtog ng tunog gamit ang ReSpeaker ay sumusuporta lamang sa audio na may 44.1KHz sample rate. Ang Azure speech services ay maaaring magbigay ng audio sa iba't ibang format, ngunit wala sa mga ito ang gumagamit ng sample rate na ito, nagbibigay lamang sila ng 8KHz, 16KHz, 24KHz, at 48KHz. Nangangahulugan ito na kailangang i-re-sample ang audio sa 44.1KHz, isang bagay na mangangailangan ng mas maraming resources kaysa sa mayroon ang Wio Terminal, lalo na ang memorya.

Kapag kailangang manipulahin ang data tulad nito, mas mainam na gumamit ng serverless code, lalo na kung ang data ay nagmumula sa isang web call. Ang Wio Terminal ay maaaring tumawag sa isang serverless function, na ipinapasa ang text na iko-convert, at ang serverless function ay maaaring parehong tumawag sa speech service upang i-convert ang text sa speech, pati na rin i-re-sample ang audio sa kinakailangang sample rate. Maaari nitong ibalik ang audio sa anyo na kailangan ng Wio Terminal upang maimbak sa SD card at ma-play gamit ang ReSpeaker.

### Gawain - Gumawa ng Serverless Function para I-convert ang Text sa Speech

1. Buksan ang iyong `smart-timer-trigger` na proyekto sa VS Code, at buksan ang terminal na siguraduhing naka-activate ang virtual environment. Kung hindi, patayin at muling likhain ang terminal.

1. Magdagdag ng bagong HTTP trigger sa app na ito na tinatawag na `text-to-speech` gamit ang sumusunod na command mula sa loob ng VS Code terminal sa root folder ng functions app project:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Ito ay lilikha ng isang HTTP trigger na tinatawag na `text-to-speech`.

1. Ang [librosa](https://librosa.org) Pip package ay may mga function upang i-re-sample ang audio, kaya idagdag ito sa `requirements.txt` file:

    ```sh
    librosa
    ```

    Kapag naidagdag na ito, i-install ang mga Pip package gamit ang sumusunod na command mula sa VS Code terminal:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Kung gumagamit ka ng Linux, kabilang ang Raspberry Pi OS, maaaring kailanganin mong i-install ang `libsndfile` gamit ang sumusunod na command:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Upang i-convert ang text sa speech, hindi mo maaaring direktang gamitin ang speech API key, sa halip kailangan mong humiling ng access token, gamit ang API key upang i-authenticate ang access token request. Buksan ang file na `__init__.py` mula sa folder na `text-to-speech` at palitan ang lahat ng code dito ng sumusunod:

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

    Ito ay nagde-define ng mga constant para sa lokasyon at speech key na babasahin mula sa mga setting. Pagkatapos ay ide-define ang `get_access_token` function na kukuha ng access token para sa speech service.

1. Sa ibaba ng code na ito, idagdag ang sumusunod:

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

    Ito ay nagde-define ng HTTP trigger na nagko-convert ng text sa speech. Kinukuha nito ang text na iko-convert, ang wika, at ang boses mula sa JSON body na ipinasa sa request, bumubuo ng SSML upang humiling ng speech, pagkatapos ay tinatawag ang kaukulang REST API na nag-a-authenticate gamit ang access token. Ang REST API call na ito ay nagbabalik ng audio na naka-encode bilang 16-bit, 48KHz mono WAV file, na tinukoy ng halaga ng `playback_format`, na ipinapadala sa REST API call.

    Ang audio na ito ay i-re-sample ng `librosa` mula sa sample rate na 48KHz patungo sa sample rate na 44.1KHz, pagkatapos ang audio na ito ay sine-save sa isang binary buffer na pagkatapos ay ibinabalik.

1. Patakbuhin ang iyong function app nang lokal, o i-deploy ito sa cloud. Maaari mo itong tawagin gamit ang tool tulad ng curl sa parehong paraan na sinubukan mo ang iyong `text-to-timer` HTTP trigger. Siguraduhing ipasa ang wika, boses, at text bilang JSON body:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Palitan ang `<language>` ng iyong wika, tulad ng `en-GB`, o `zh-CN`. Palitan ang `<voice>` ng boses na gusto mong gamitin. Palitan ang `<text>` ng text na gusto mong i-convert sa speech. Maaari mong i-save ang output sa isang file at i-play ito gamit ang anumang audio player na maaaring magpatugtog ng WAV files.

    Halimbawa, upang i-convert ang "Hello" sa speech gamit ang US English na may Jenny Neural voice, na tumatakbo nang lokal ang function app, maaari mong gamitin ang sumusunod na curl command:

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

    Ito ay magse-save ng audio sa `hello.wav` sa kasalukuyang direktoryo.

> 💁 Maaari mong makita ang code na ito sa [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) folder.

### Gawain - Kunin ang Speech mula sa Iyong Wio Terminal

1. Buksan ang proyekto na `smart-timer` sa VS Code kung hindi pa ito bukas.

1. Buksan ang header file na `config.h` at idagdag ang URL para sa iyong function app:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Palitan ang `<URL>` ng URL para sa `text-to-speech` HTTP trigger sa iyong function app. Ito ay magiging kapareho ng halaga para sa `TEXT_TO_TIMER_FUNCTION_URL`, maliban sa pangalan ng function na `text-to-speech` sa halip na `text-to-timer`.

1. Buksan ang header file na `text_to_speech.h`, at idagdag ang sumusunod na method sa `public` na seksyon ng klase na `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Sa `convertTextToSpeech` method, idagdag ang sumusunod na code upang lumikha ng JSON na ipapadala sa function app:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Isinusulat nito ang wika, boses, at text sa JSON document, pagkatapos ay sine-serialize ito sa isang string.

1. Sa ibaba nito, idagdag ang sumusunod na code upang tawagin ang function app:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Gumagawa ito ng isang HTTPClient, pagkatapos ay gumagawa ng POST request gamit ang JSON document sa text-to-speech HTTP trigger.

1. Kung gumana ang tawag, ang raw binary data na ibinalik mula sa function app call ay maaaring i-stream sa isang file sa SD card. Idagdag ang sumusunod na code upang gawin ito:

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

    Sinusuri ng code na ito ang response, at kung ito ay 200 (tagumpay), ang binary data ay i-stream sa isang file sa root ng SD Card na tinatawag na `SPEECH.WAV`.

1. Sa dulo ng method na ito, isara ang HTTP connection:

    ```cpp
    httpClient.end();
    ```

1. Ang text na kailangang sabihin ay maaari nang i-convert sa audio. Sa file na `main.cpp`, idagdag ang sumusunod na linya sa dulo ng `say` function upang i-convert ang text na sasabihin sa audio:
### Gawain - magpatugtog ng audio mula sa iyong Wio Terminal

**Malapit na**

## Pag-deploy ng iyong functions app sa cloud

Ang dahilan kung bakit pinapatakbo ang functions app nang lokal ay dahil ang `librosa` Pip package sa Linux ay may dependency sa isang library na hindi naka-install nang default, at kailangang i-install bago tumakbo ang function app. Ang function apps ay serverless - walang mga server na maaari mong pamahalaan mismo, kaya walang paraan upang i-install ang library na ito nang maaga.

Ang paraan upang gawin ito ay i-deploy ang iyong functions app gamit ang isang Docker container. Ang container na ito ay ide-deploy ng cloud tuwing kailangan nitong mag-spin up ng bagong instance ng iyong function app (halimbawa, kapag ang demand ay lumampas sa available na resources, o kung ang function app ay hindi nagamit nang matagal at isinara).

Makikita mo ang mga tagubilin para mag-set up ng function app at mag-deploy gamit ang Docker sa [create a function on Linux using a custom container documentation on Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Kapag na-deploy na ito, maaari mong i-port ang iyong Wio Terminal code upang ma-access ang function na ito:

1. Idagdag ang Azure Functions certificate sa `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Palitan ang lahat ng pag-include ng `<WiFiClient.h>` sa `<WiFiClientSecure.h>`.

1. Palitan ang lahat ng `WiFiClient` fields sa `WiFiClientSecure`.

1. Sa bawat klase na may `WiFiClientSecure` field, magdagdag ng constructor at itakda ang certificate sa constructor na iyon:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.