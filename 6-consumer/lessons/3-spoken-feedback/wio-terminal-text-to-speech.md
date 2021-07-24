# Text to speech - Wio Terminal

In this part of the lesson, you will convert text to speech to provide spoken feedback.

## Text to speech

The speech services SDK that you used in the last lesson to convert speech to text can be used to convert text back to speech.

## Get a list of voices

When requesting speech, you need to provide the voice to use as speech can be generated using a variety of different voices. Each language supports a range of different voices, and you can get the list of supported voices for each language from the speech services SDK. The limitations of microcontrollers come into play here - the call to get the list of voices supported by the text to speech services is a JSON document of over 77KB in size, far to large to be processed by the Wio Terminal. At the time of writing, the full list contains 215 voices, each defined by a JSON document like the following:

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

This JSON is for the **Aria** voice, which has multiple voice styles. All that is needed when converting text to speech is the shortname, `en-US-AriaNeural`.

Instead of downloading and decoding this entire list on your microcontroller, you will need to write some more serverless code to retrieve the list of voices for the language you are using, and call this from your Wio Terminal. Your code can then pick an appropriate voice from the list, such as the first one it finds.

### Task - create a serverless function to get a list of voices

1. Open your `smart-timer-trigger` project in VS Code, and open the terminal ensuring the virtual environment is activated. If not, kill and re-create the terminal.

1. Open the `local.settings.json` file and add settings for the speech API key and location:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Replace `<key>` with the API key for your speech service resource. Replace `<location>` with the location you used when you created the speech service resource.

1. Add a new HTTP trigger to this app called `get-voices` using the following command from inside the VS Code terminal in the root folder of the functions app project:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    This will create an HTTP trigger called `get-voices`.

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

    This code makes an HTTP request to the endpoint to get the voices. This voices list is a large block of JSON with voices for all languages, so the voices for the language passed in the request body are filtered out, then the shortname is extracted and returned as a JSON list. The shortname is the value needed to convert text to speech, so only this value is returned.

    > 💁 You can change the filter as necessary to select just the voices you want.

    This reduces the size of the data from 77KB (at the time of writing), to a much smaller JSON document. For example, for US voices this is 408 bytes.

1. Run your function app locally. You can then call this using a tool like curl in the same way that you tested your `text-to-timer` HTTP trigger. Make sure to pass your language as a JSON body:

    ```json
    {
        "language":"<language>"
    }
    ```

    Replace `<language>` with your language, such as `en-GB`, or `zh-CN`.

> 💁 You can find this code in the [code-spoken-response/functions](code-spoken-response/functions) folder.

### Task - retrieve the voice from your Wio Terminal

1. Open the `smart-timer` project in VS Code if it is not already open.

1. Open the `config.h` header file and add the URL for your function app:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Replace `<URL>` with the URL for the `get-voices` HTTP trigger on your function app. This will be the same as the value for `TEXT_TO_TIMER_FUNCTION_URL`, except with a function name of `get-voices` instead of `text-to-timer`.

1. Create a new file in the `src` folder called `text_to_speech.h`. This will be used to define a class to convert from text to speech.

1. Add the following include directives to the top of the new `text_to_speech.h` file:

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

1. Add the following code below this to declare the `TextToSpeech` class, along with an instance that can be used in the rest of the application:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. To call your functions app, you need to declare a WiFi client. Add the following to the `private` section of the class:

    ```cpp
    WiFiClient _client;
    ```

1. In the `private` section, add a field for the selected voice:

    ```cpp
    String _voice;
    ```

1. To the `public` section, add an `init` function that will get the first voice:

    ```cpp
    void init()
    {
    }
    ```

1. To get the voices, a JSON document needs to be sent to the function app with the language. Add the following code to the `init` function to create this JSON document:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Next create an `HTTPClient`, then use it to call the functions app to get the voices, posting the JSON document:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Below this add code to check the response code, and if it is 200 (success), then extract the list of voices, retrieving the first one from the list:

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

1. After this, end the HTTP client connection:

    ```cpp
    httpClient.end();
    ```

1. Open the `main.cpp` file, and add the following include directive at the top to include this new header file:

    ```cpp
    #include "text_to_speech.h"
    ```

1. In the `setup` function, underneath the call to `speechToText.init();`, add the following to initialize the `TextToSpeech` class:

    ```cpp
    textToSpeech.init();
    ```

1. Build this code, upload it to your Wio Terminal and test it out through the serial monitor. Make sure your function app is running.

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

## Convert text to speech

Once you have a voice to use, it can be used to convert text to speech. The same memory limitations with voices also apply when converting speech to text, so you will need to write the speech to an SD card ready to be played over the ReSpeaker.

> 💁 In earlier lessons in this project you used flash memory to store speech captured from the microphone. This lesson uses an SD card as is it easier to play audio from it using the Seeed audio libraries.

There is also another limitation to consider, the available audio data from the speech service, and the formats that the Wio Terminal supports. Unlike full computers, audio libraries for microcontrollers can be very limited in the audio formats they support. For example, the Seeed Arduino Audio library that can play sound over the ReSpeaker only supports audio at a 44.1KHz sample rate. The Azure speech services can provide audio in a number of formats, but none of them use this sample rate, they only provide 8KHz, 16KHz, 24KHz and 48KHz. This means the audio needs to be re-sampled to 44.1KHz, something that would need more resources that the Wio Terminal has, especially memory.

When needing to manipulate data like this, it is often better to use serverless code, especially if the data is sourced via a web call. The Wio Terminal can call a serverless function, passing in the text to convert, and the serverless function can both call the speech service to convert text to speech, as well as re-sample the audio to the required sample rate. It can then return the audio in the form the Wio Terminal needs to be stored on the SD card and played over the ReSpeaker.

### Task - create a serverless function to convert text to speech

1. Open your `smart-timer-trigger` project in VS Code, and open the terminal ensuring the virtual environment is activated. If not, kill and re-create the terminal.

1. Add a new HTTP trigger to this app called `text-to-speech` using the following command from inside the VS Code terminal in the root folder of the functions app project:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    This will create an HTTP trigger called `text-to-speech`.

1. The [librosa](https://librosa.org) Pip package has functions to re-sample audio, so add this to the `requirements.txt` file:

    ```sh
    librosa
    ```

    Once this has been added, install the Pip packages using the following command from the VS Code terminal:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ If you are using Linux, including Raspberry Pi OS, you may need to install `libsndfile` with the following command:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. To convert text to speech, you cannot use the speech API key directly, instead you need to request an access token, using the API key to authenticate the access token request. Open the `__init__.py` file from the `text-to-speech` folder and replace all the code in it with the following:

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

    This defines constants for the location and speech key that will be read from the settings. It then defines the `get_access_token` function that will retrieve an access token for the speech service.

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

    This defines the HTTP trigger that converts the text to speech. It extracts the text to convert, the language and the voice from the JSON body set to the request, builds some SSML to request the speech, then calls the relevant REST API authenticating using the access token. This REST API call returns the audio encoded as 16-bit, 48KHz mono WAV file, defined by the value of `playback_format`, which is sent to the REST API call.

    This is then re-sampled by `librosa` from a sample rate of 48KHz to a sample rate of 44.1KHz, then this audio is saved to a binary buffer that is then returned.

1. Run your function app locally, or deploy it to the cloud. You can then call this using a tool like curl in the same way that you tested your `text-to-timer` HTTP trigger. Make sure to pass the language, voice and text as the JSON body:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Replace `<language>` with your language, such as `en-GB`, or `zh-CN`. Replace `<voice>` with the voice you want to use. Replace `<text>` with the text you want to convert to speech. You can save the output to a file and play it with any audio player that can play WAV files.

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

> 💁 You can find this code in the [code-spoken-response/functions](code-spoken-response/functions) folder.

### Task - retrieve the speech from your Wio Terminal

1. Open the `smart-timer` project in VS Code if it is not already open.

1. Open the `config.h` header file and add the URL for your function app:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Replace `<URL>` with the URL for the `text-to-speech` HTTP trigger on your function app. This will be the same as the value for `TEXT_TO_TIMER_FUNCTION_URL`, except with a function name of `text-to-speech` instead of `text-to-timer`.

1. Open the `text_to_speech.h` header file, and add the following method to the `public` section of the `TextToSpeech` class:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. To the `convertTextToSpeech` method, add the following code to create the JSON to send to the function app:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    This writes the language, voice and text to the JSON document, then serializes it to a string.

1. Below this, add the following code to call the function app:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    This creates an HTTPClient, then makes a POST request using the JSON document to the text to speech HTTP trigger.

1. If the call works, the raw binary data returned from the function app call can be streamed to a file on the SD card. Add the following code to do this:

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

    This code checks the response, and if it is 200 (success), the binary data is streamed to a file in the root of the SD Card called `SPEECH.WAV`.

1. At the end of this method, close the HTTP connection:

    ```cpp
    httpClient.end();
    ```

1. The text to be spoken can now be converted to audio. In the `main.cpp` file, add the following line to the end of the `say` function to convert the text to say into audio:

    ```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Task - play audio from your Wio Terminal

**Coming soon**

## Deploying your functions app to the cloud

The reason for running the functions app locally is because the `librosa` Pip package on linux has a dependency on a library that is not installed by default, and will need to be installed before the function app can run. Function apps are serverless - there are no servers you can manage yourself, so no way to install this library up front.

The way to do this is instead to deploy your functions app using a Docker container. This container is deployed by the cloud whenever it needs to spin up a new instance of your function app (such as when the demand exceeds the available resources, or if the function app hasn't been used for a while and is closed down).

You can find the instructions to set up a function app and deploy via Docker in the [create a function on Linux using a custom container documentation on Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?tabs=bash%2Cazurecli&pivots=programming-language-python&WT.mc_id=academic-17441-jabenn).

Once this has been deployed, you can port your Wio Terminal code to access this function:

1. Add the Azure Functions certificate to `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Change all includes of `<WiFiClient.h>` to `<WiFiClientSecure.h>`.

1. Change all `WiFiClient` fields to `WiFiClientSecure`.

1. In every class that has a `WiFiClientSecure` field, add a constructor and set the certificate in that constructor:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```
