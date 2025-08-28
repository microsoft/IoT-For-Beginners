<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T19:18:54+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "en"
}
-->
# Text to Speech - Wio Terminal

In this section of the lesson, you'll transform text into speech to provide spoken feedback.

## Text to Speech

The speech services SDK you used in the previous lesson to convert speech into text can also be utilized to convert text back into speech.

## Retrieve a List of Voices

When generating speech, you need to specify the voice to use, as speech can be created using various voices. Each language supports multiple voices, and you can retrieve the list of supported voices for each language using the speech services SDK. However, microcontroller limitations come into play here—the call to fetch the list of voices supported by the text-to-speech service results in a JSON document over 77KB in size, which is far too large for the Wio Terminal to process. At the time of writing, the full list includes 215 voices, each described by a JSON document like this:

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

This JSON represents the **Aria** voice, which offers multiple voice styles. To convert text to speech, all you need is the shortname, `en-US-AriaNeural`.

Instead of downloading and decoding the entire list on your microcontroller, you'll write serverless code to retrieve the list of voices for the language you're using and call this from your Wio Terminal. Your code can then select an appropriate voice from the list, such as the first one available.

### Task - Create a Serverless Function to Retrieve Voices

1. Open your `smart-timer-trigger` project in VS Code, and ensure the terminal is active with the virtual environment enabled. If not, restart the terminal.

1. Open the `local.settings.json` file and add settings for the speech API key and location:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Replace `<key>` with your speech service resource's API key. Replace `<location>` with the location you used when creating the speech service resource.

1. Add a new HTTP trigger to this app called `get-voices` using the following command in the VS Code terminal, from the root folder of the functions app project:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    This will create an HTTP trigger named `get-voices`.

1. Replace the contents of the `__init__.py` file in the `get-voices` folder with the following:

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

    This code makes an HTTP request to the endpoint to fetch the voices. The voices list is a large JSON block containing voices for all languages, so the code filters out voices for the language specified in the request body, extracts the shortname, and returns it as a JSON list. The shortname is the value required to convert text to speech, so only this value is returned.

    > 💁 You can modify the filter as needed to select specific voices.

    This reduces the data size from 77KB (at the time of writing) to a much smaller JSON document. For example, for US voices, this is 408 bytes.

1. Run your function app locally. You can test it using a tool like curl, similar to how you tested the `text-to-timer` HTTP trigger. Ensure you pass your language as a JSON body:

    ```json
    {
        "language":"<language>"
    }
    ```

    Replace `<language>` with your language, such as `en-GB` or `zh-CN`.

> 💁 You can find this code in the [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) folder.

### Task - Retrieve the Voice from Your Wio Terminal

1. Open the `smart-timer` project in VS Code if it isn't already open.

1. Open the `config.h` header file and add the URL for your function app:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Replace `<URL>` with the URL for the `get-voices` HTTP trigger in your function app. This URL will be similar to the value for `TEXT_TO_TIMER_FUNCTION_URL`, but with the function name `get-voices` instead of `text-to-timer`.

1. Create a new file in the `src` folder called `text_to_speech.h`. This file will define a class for converting text to speech.

1. Add the following include directives at the top of the new `text_to_speech.h` file:

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

1. Add the following code below this to declare the `TextToSpeech` class, along with an instance that can be used throughout the application:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. To call your function app, declare a WiFi client. Add the following to the `private` section of the class:

    ```cpp
    WiFiClient _client;
    ```

1. In the `private` section, add a field for the selected voice:

    ```cpp
    String _voice;
    ```

1. In the `public` section, add an `init` function to retrieve the first voice:

    ```cpp
    void init()
    {
    }
    ```

1. To fetch the voices, create a JSON document with the language. Add the following code to the `init` function:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Next, create an `HTTPClient` and use it to call the function app to retrieve the voices, posting the JSON document:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Add code to check the response code, and if it's 200 (success), extract the list of voices and retrieve the first one:

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

1. After this, close the HTTP client connection:

    ```cpp
    httpClient.end();
    ```

1. Open the `main.cpp` file, and add the following include directive at the top to include the new header file:

    ```cpp
    #include "text_to_speech.h"
    ```

1. In the `setup` function, below the call to `speechToText.init();`, add the following to initialize the `TextToSpeech` class:

    ```cpp
    textToSpeech.init();
    ```

1. Build the code, upload it to your Wio Terminal, and test it through the serial monitor. Ensure your function app is running.

    You will see the list of available voices returned from the function app, along with the selected voice.

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

## Convert Text to Speech

Once you have a voice, it can be used to convert text into speech. The same memory limitations for voices apply when converting text to speech, so you'll need to save the speech to an SD card to play it through the ReSpeaker.

> 💁 In earlier lessons, you used flash memory to store speech captured from the microphone. This lesson uses an SD card because it's easier to play audio from it using the Seeed audio libraries.

Another limitation to consider is the available audio formats from the speech service and the formats supported by the Wio Terminal. Unlike full computers, microcontroller audio libraries are often limited in the formats they support. For example, the Seeed Arduino Audio library for playing sound through the ReSpeaker only supports audio at a 44.1KHz sample rate. Azure speech services provide audio in several formats, but none use this sample rate—they only offer 8KHz, 16KHz, 24KHz, and 48KHz. This means the audio must be re-sampled to 44.1KHz, which requires more resources than the Wio Terminal has, especially memory.

When manipulating data like this, it's often better to use serverless code, especially if the data is sourced via a web call. The Wio Terminal can call a serverless function, passing in the text to convert, and the serverless function can handle both the text-to-speech conversion and the audio re-sampling. It can then return the audio in a format the Wio Terminal can store on the SD card and play through the ReSpeaker.

### Task - Create a Serverless Function to Convert Text to Speech

1. Open your `smart-timer-trigger` project in VS Code, and ensure the terminal is active with the virtual environment enabled. If not, restart the terminal.

1. Add a new HTTP trigger to this app called `text-to-speech` using the following command in the VS Code terminal, from the root folder of the functions app project:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    This will create an HTTP trigger named `text-to-speech`.

1. The [librosa](https://librosa.org) Python package includes functions for re-sampling audio. Add this to the `requirements.txt` file:

    ```sh
    librosa
    ```

    After adding it, install the Pip packages using the following command in the VS Code terminal:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ If you're using Linux, including Raspberry Pi OS, you may need to install `libsndfile` with the following command:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. To convert text to speech, you can't use the speech API key directly. Instead, you need to request an access token using the API key for authentication. Open the `__init__.py` file in the `text-to-speech` folder and replace its contents with the following:

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

    This defines constants for the location and speech key, which are read from the settings. It also defines the `get_access_token` function to retrieve an access token for the speech service.

1. Below this code, add the following:

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

    This defines the HTTP trigger for converting text to speech. It extracts the text, language, and voice from the JSON body of the request, builds SSML to request the speech, and calls the relevant REST API, authenticating with the access token. The REST API call returns audio encoded as a 16-bit, 48KHz mono WAV file, as specified by the `playback_format` value sent in the REST API call.

    The audio is then re-sampled by `librosa` from 48KHz to 44.1KHz, saved to a binary buffer, and returned.

1. Run your function app locally or deploy it to the cloud. You can test it using a tool like curl, similar to how you tested the `text-to-timer` HTTP trigger. Ensure you pass the language, voice, and text as the JSON body:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Replace `<language>` with your language, such as `en-GB` or `zh-CN`. Replace `<voice>` with the voice you want to use. Replace `<text>` with the text you want to convert to speech. You can save the output to a file and play it with any audio player that supports WAV files.

    For example, to convert "Hello" to speech using US English with the Jenny Neural voice, with the function app running locally, you can use the following curl command:

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

    This will save the audio to `hello.wav` in the current directory.

> 💁 You can find this code in the [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) folder.

### Task - Retrieve the Speech from Your Wio Terminal

1. Open the `smart-timer` project in VS Code if it isn't already open.

1. Open the `config.h` header file and add the URL for your function app:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Replace `<URL>` with the URL for the `text-to-speech` HTTP trigger in your function app. This URL will be similar to the value for `TEXT_TO_TIMER_FUNCTION_URL`, but with the function name `text-to-speech` instead of `text-to-timer`.

1. Open the `text_to_speech.h` header file, and add the following method to the `public` section of the `TextToSpeech` class:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. In the `convertTextToSpeech` method, add the following code to create the JSON to send to the function app:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    This writes the language, voice, and text to the JSON document, then serializes it into a string.

1. Below this, add the following code to call the function app:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    This creates an HTTPClient and makes a POST request using the JSON document to the text-to-speech HTTP trigger.

1. If the call succeeds, the raw binary data returned from the function app can be streamed to a file on the SD card. Add the following code to do this:

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

    This code checks the response, and if it's 200 (success), streams the binary data to a file named `SPEECH.WAV` in the root of the SD card.

1. At the end of this method, close the HTTP connection:

    ```cpp
    httpClient.end();
    ```

1. The text to be spoken can now be converted into audio. In the `main.cpp` file, add the following line to the end of the `say` function to convert the text into audio:
### Task - play audio from your Wio Terminal

**Coming soon**

## Deploying your functions app to the cloud

The reason for running the functions app locally is that the `librosa` Pip package on Linux depends on a library that isn't installed by default. This library needs to be installed before the function app can run. Function apps are serverless, meaning there are no servers you can manage directly, so you can't pre-install this library.

To address this, you can deploy your functions app using a Docker container. This container is used by the cloud to spin up new instances of your function app whenever needed (for example, when demand exceeds available resources or when the function app has been idle for a while and is shut down).

Instructions for setting up a function app and deploying it via Docker can be found in the [create a function on Linux using a custom container documentation on Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Once deployed, you can adapt your Wio Terminal code to interact with this function:

1. Add the Azure Functions certificate to `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Replace all instances of `<WiFiClient.h>` with `<WiFiClientSecure.h>`.

1. Update all `WiFiClient` fields to `WiFiClientSecure`.

1. For every class that includes a `WiFiClientSecure` field, add a constructor and set the certificate within that constructor:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may contain errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is recommended. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.