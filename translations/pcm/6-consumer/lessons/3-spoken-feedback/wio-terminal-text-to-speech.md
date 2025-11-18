<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-11-18T19:12:30+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "pcm"
}
-->
# Text to speech - Wio Terminal

For dis part of di lesson, you go change text to speech so e go fit give spoken feedback.

## Text to speech

Di speech services SDK wey you use for di last lesson to change speech to text fit also change text back to speech.

## Get list of voices

When you dey request speech, you go need provide di voice wey you wan use because speech fit dey generate with different voices. Each language get different voices wey e support, and you fit get di list of voices wey dey available for each language from di speech services SDK. But di microcontroller get limitation - di call wey go get di list of voices wey text to speech services support na JSON document wey big reach 77KB, e too big to process for Wio Terminal. As at di time wey dem write dis, di full list get 215 voices, each one dey define with JSON document like dis:

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

Dis JSON na for di **Aria** voice, wey get plenty voice styles. Wetin you need when you dey change text to speech na di shortname, `en-US-AriaNeural`.

Instead make you download and decode di whole list for your microcontroller, you go need write serverless code wey go retrieve di list of voices for di language wey you dey use, and call am from your Wio Terminal. Your code fit then pick di correct voice from di list, like di first one wey e see.

### Task - create serverless function to get list of voices

1. Open your `smart-timer-trigger` project for VS Code, and open di terminal make sure say di virtual environment dey activated. If e no dey, kill di terminal and create am again.

1. Open di `local.settings.json` file and add di settings for di speech API key and location:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Replace `<key>` with di API key for your speech service resource. Replace `<location>` with di location wey you use when you create di speech service resource.

1. Add new HTTP trigger to dis app wey dem call `get-voices` using dis command from inside di VS Code terminal for di root folder of di functions app project:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Dis one go create HTTP trigger wey dem call `get-voices`.

1. Replace di content of di `__init__.py` file for di `get-voices` folder with dis:

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

    Dis code dey make HTTP request to di endpoint wey go get di voices. Di voices list na big JSON block wey get voices for all languages, so di voices for di language wey dem pass for di request body go dey filter out, then di shortname go dey extract and return as JSON list. Di shortname na di value wey you need to change text to speech, so na only dis value dem go return.

    > 💁 You fit change di filter as you like to select di voices wey you want.

    Dis one go reduce di size of di data from 77KB (as at di time wey dem write am), to smaller JSON document. Example, for US voices na 408 bytes.

1. Run your function app locally. You fit then call am using tool like curl di same way wey you test your `text-to-timer` HTTP trigger. Make sure say you pass your language as JSON body:

    ```json
    {
        "language":"<language>"
    }
    ```

    Replace `<language>` with your language, like `en-GB`, or `zh-CN`.

> 💁 You fit find dis code for di [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) folder.

### Task - retrieve di voice from your Wio Terminal

1. Open di `smart-timer` project for VS Code if e never open.

1. Open di `config.h` header file and add di URL for your function app:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Replace `<URL>` with di URL for di `get-voices` HTTP trigger for your function app. Dis one go be di same as di value for `TEXT_TO_TIMER_FUNCTION_URL`, but di function name go be `get-voices` instead of `text-to-timer`.

1. Create new file for di `src` folder wey dem call `text_to_speech.h`. Dis one go dey use to define class wey go change text to speech.

1. Add di following include directives to di top of di new `text_to_speech.h` file:

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

1. Add di following code below dis to declare di `TextToSpeech` class, along with instance wey fit dey use for di rest of di application:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. To call your functions app, you go need declare WiFi client. Add dis one to di `private` section of di class:

    ```cpp
    WiFiClient _client;
    ```

1. For di `private` section, add field for di selected voice:

    ```cpp
    String _voice;
    ```

1. For di `public` section, add `init` function wey go get di first voice:

    ```cpp
    void init()
    {
    }
    ```

1. To get di voices, JSON document go need dey send to di function app with di language. Add dis code to di `init` function to create dis JSON document:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Next create `HTTPClient`, then use am call di functions app to get di voices, post di JSON document:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Below dis add code to check di response code, and if e be 200 (success), then extract di list of voices, retrieve di first one from di list:

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

1. After dis, end di HTTP client connection:

    ```cpp
    httpClient.end();
    ```

1. Open di `main.cpp` file, and add di following include directive for di top to include dis new header file:

    ```cpp
    #include "text_to_speech.h"
    ```

1. For di `setup` function, under di call to `speechToText.init();`, add dis one to initialize di `TextToSpeech` class:

    ```cpp
    textToSpeech.init();
    ```

1. Build dis code, upload am to your Wio Terminal and test am through di serial monitor. Make sure say your function app dey run.

    You go see di list of available voices wey di function app return, along with di selected voice.

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

## Change text to speech

Once you get voice wey you wan use, e fit dey use to change text to speech. Di same memory limitation wey dey with voices also dey apply when you dey change speech to text, so you go need write di speech to SD card make e ready to play over di ReSpeaker.

> 💁 For di earlier lessons for dis project, you use flash memory to store speech wey microphone capture. Dis lesson dey use SD card because e dey easier to play audio from am using di Seeed audio libraries.

Another limitation dey wey you go need consider, na di available audio data from di speech service, and di formats wey di Wio Terminal dey support. Unlike full computers, audio libraries for microcontrollers fit dey very limited for di audio formats wey dem dey support. Example, di Seeed Arduino Audio library wey fit play sound over di ReSpeaker only dey support audio wey get 44.1KHz sample rate. Di Azure speech services fit provide audio for plenty formats, but none of dem dey use dis sample rate, dem only dey provide 8KHz, 16KHz, 24KHz and 48KHz. Dis mean say di audio go need re-sample to 44.1KHz, something wey go need more resources wey di Wio Terminal no get, especially memory.

When you need manipulate data like dis, e better make you use serverless code, especially if di data dey come through web call. Di Wio Terminal fit call serverless function, pass di text wey e wan change, and di serverless function fit call di speech service to change text to speech, as well as re-sample di audio to di sample rate wey e need. E fit then return di audio for di form wey di Wio Terminal need to store am for di SD card and play am over di ReSpeaker.

### Task - create serverless function to change text to speech

1. Open your `smart-timer-trigger` project for VS Code, and open di terminal make sure say di virtual environment dey activated. If e no dey, kill di terminal and create am again.

1. Add new HTTP trigger to dis app wey dem call `text-to-speech` using dis command from inside di VS Code terminal for di root folder of di functions app project:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Dis one go create HTTP trigger wey dem call `text-to-speech`.

1. Di [librosa](https://librosa.org) Pip package get functions to re-sample audio, so add dis one to di `requirements.txt` file:

    ```sh
    librosa
    ```

    Once you don add am, install di Pip packages using dis command from di VS Code terminal:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ If you dey use Linux, including Raspberry Pi OS, you fit need install `libsndfile` with dis command:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. To change text to speech, you no fit use di speech API key directly, instead you go need request access token, use di API key to authenticate di access token request. Open di `__init__.py` file from di `text-to-speech` folder and replace all di code inside am with dis:

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

    Dis one dey define constants for di location and speech key wey dem go read from di settings. E then dey define di `get_access_token` function wey go retrieve access token for di speech service.

1. Below dis code, add di following:

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

    Dis one dey define di HTTP trigger wey dey change di text to speech. E dey extract di text wey e wan change, di language and di voice from di JSON body wey dem set for di request, build some SSML to request di speech, then call di REST API wey dey authenticate using di access token. Dis REST API call dey return di audio wey dem encode as 16-bit, 48KHz mono WAV file, wey di value of `playback_format` dey define, wey dem send to di REST API call.

    Dis one then dey re-sample by `librosa` from sample rate of 48KHz to sample rate of 44.1KHz, then dis audio dey save to binary buffer wey dem go return.

1. Run your function app locally, or deploy am to di cloud. You fit then call am using tool like curl di same way wey you test your `text-to-timer` HTTP trigger. Make sure say you pass di language, voice and text as di JSON body:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Replace `<language>` with your language, like `en-GB`, or `zh-CN`. Replace `<voice>` with di voice wey you wan use. Replace `<text>` with di text wey you wan change to speech. You fit save di output to file and play am with any audio player wey fit play WAV files.

    Example, to change "Hello" to speech using US English with di Jenny Neural voice, with di function app wey dey run locally, you fit use dis curl command:

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

    Dis one go save di audio to `hello.wav` for di current directory.

> 💁 You fit find dis code for di [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) folder.

### Task - retrieve di speech from your Wio Terminal

1. Open di `smart-timer` project for VS Code if e never open.

1. Open di `config.h` header file and add di URL for your function app:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Replace `<URL>` with di URL for di `text-to-speech` HTTP trigger for your function app. Dis one go be di same as di value for `TEXT_TO_TIMER_FUNCTION_URL`, but di function name go be `text-to-speech` instead of `text-to-timer`.

1. Open di `text_to_speech.h` header file, and add di following method to di `public` section of di `TextToSpeech` class:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. To di `convertTextToSpeech` method, add di following code to create di JSON wey go send to di function app:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dis one dey write di language, voice and text to di JSON document, then serialize am to string.

1. Below dis, add di following code to call di function app:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dis one dey create HTTPClient, then make POST request using di JSON document to di text to speech HTTP trigger.

1. If di call work, di raw binary data wey di function app call return fit dey stream to file for di SD card. Add dis code to do dis:

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

    Dis code dey check di response, and if e be 200 (success), di binary data dey stream to file for di root of di SD Card wey dem call `SPEECH.WAV`.

1. For di end of dis method, close di HTTP connection:

    ```cpp
    httpClient.end();
    ```

1. Di text wey you wan talk fit now turn to audio. For di `main.cpp` file, add dis line for di end of di `say` function to turn di text wey you wan talk to audio:

    ```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Task - play audio from your Wio Terminal

**E go soon ready**

## How to carry your functions app go cloud

Di reason why we dey run di functions app for local na because di `librosa` Pip package for linux get one dependency wey dey need one library wey no dey install by default, and you go need install am before di function app fit run. Function apps no dey use server - you no fit manage server by yourself, so you no fit install dis library before di app go run.

Di way to do am na to carry your functions app go cloud by using Docker container. Dis container go dey deploy by di cloud anytime e need to start new instance of your function app (like if di demand don pass di resources wey dey available, or if di function app never dey use for some time and dem don close am).

You fit find di instructions to set up function app and deploy am with Docker for di [create a function on Linux using a custom container documentation on Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Once you don deploy am, you fit move your Wio Terminal code to fit access dis function:

1. Add di Azure Functions certificate to `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Change all di `<WiFiClient.h>` to `<WiFiClientSecure.h>`.

1. Change all di `WiFiClient` fields to `WiFiClientSecure`.

1. For every class wey get `WiFiClientSecure` field, add one constructor and set di certificate for dat constructor:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don translate wit AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). Even though we dey try make am accurate, abeg make you sabi say machine translation fit get mistake or no dey correct well. Di original dokyument for di language wey dem write am first na di main source wey you go trust. For important information, e better make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->