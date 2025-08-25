<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T00:14:52+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "ko"
}
-->
# 텍스트 음성 변환 - Wio Terminal

이 수업의 이 부분에서는 텍스트를 음성으로 변환하여 음성 피드백을 제공하게 됩니다.

## 텍스트 음성 변환

지난 수업에서 음성을 텍스트로 변환하기 위해 사용했던 음성 서비스 SDK는 텍스트를 다시 음성으로 변환하는 데에도 사용할 수 있습니다.

## 음성 목록 가져오기

음성을 요청할 때는 사용할 음성을 제공해야 합니다. 다양한 음성을 사용하여 음성을 생성할 수 있기 때문입니다. 각 언어는 다양한 음성을 지원하며, 음성 서비스 SDK를 통해 각 언어에 대해 지원되는 음성 목록을 얻을 수 있습니다. 여기서 마이크로컨트롤러의 한계가 드러납니다. 텍스트 음성 변환 서비스에서 지원하는 음성 목록을 가져오는 호출은 77KB 이상의 JSON 문서로, Wio Terminal에서 처리하기에는 너무 큽니다. 작성 시점 기준으로 전체 목록에는 215개의 음성이 포함되어 있으며, 각 음성은 다음과 같은 JSON 문서로 정의됩니다:

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

이 JSON은 **Aria** 음성에 대한 것으로, 여러 음성 스타일을 가지고 있습니다. 텍스트를 음성으로 변환할 때 필요한 것은 `en-US-AriaNeural`과 같은 짧은 이름(shortname)뿐입니다.

마이크로컨트롤러에서 이 전체 목록을 다운로드하고 디코딩하는 대신, 사용 중인 언어에 대한 음성 목록을 검색하고 이를 Wio Terminal에서 호출할 수 있는 서버리스 코드를 작성해야 합니다. 그런 다음 코드에서 적절한 음성을 선택할 수 있습니다. 예를 들어, 목록에서 첫 번째 음성을 선택할 수 있습니다.

### 작업 - 음성 목록을 가져오는 서버리스 함수 생성

1. VS Code에서 `smart-timer-trigger` 프로젝트를 열고, 가상 환경이 활성화되어 있는지 확인한 후 터미널을 엽니다. 활성화되지 않았다면 터미널을 종료하고 다시 생성하세요.

1. `local.settings.json` 파일을 열고 음성 API 키와 위치에 대한 설정을 추가하세요:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>`를 음성 서비스 리소스의 API 키로 바꾸세요. `<location>`을 음성 서비스 리소스를 생성할 때 사용한 위치로 바꾸세요.

1. 이 앱에 `get-voices`라는 새 HTTP 트리거를 추가하세요. VS Code 터미널에서 함수 앱 프로젝트의 루트 폴더에서 다음 명령을 실행하세요:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    이렇게 하면 `get-voices`라는 HTTP 트리거가 생성됩니다.

1. `get-voices` 폴더의 `__init__.py` 파일 내용을 다음 코드로 교체하세요:

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

    이 코드는 음성 목록을 가져오기 위해 엔드포인트에 HTTP 요청을 보냅니다. 이 음성 목록은 모든 언어에 대한 음성을 포함하는 큰 JSON 블록입니다. 요청 본문에 전달된 언어에 대한 음성만 필터링한 후, 짧은 이름(shortname)을 추출하여 JSON 목록으로 반환합니다. 텍스트를 음성으로 변환하는 데 필요한 값은 짧은 이름뿐이므로 이 값만 반환됩니다.

    > 💁 필요한 경우 필터를 변경하여 원하는 음성만 선택할 수 있습니다.

    이렇게 하면 데이터 크기가 작성 시점 기준으로 77KB에서 훨씬 작은 JSON 문서로 줄어듭니다. 예를 들어, 미국 음성의 경우 408바이트입니다.

1. 로컬에서 함수 앱을 실행하세요. 그런 다음 `text-to-timer` HTTP 트리거를 테스트했던 것과 동일한 방식으로 curl과 같은 도구를 사용하여 호출할 수 있습니다. 요청 본문에 JSON 형식으로 언어를 전달하세요:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>`를 `en-GB` 또는 `zh-CN`과 같은 언어로 바꾸세요.

> 💁 이 코드는 [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) 폴더에서 찾을 수 있습니다.

### 작업 - Wio Terminal에서 음성 가져오기

1. VS Code에서 `smart-timer` 프로젝트를 열어두세요.

1. `config.h` 헤더 파일을 열고 함수 앱의 URL을 추가하세요:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>`을 함수 앱의 `get-voices` HTTP 트리거 URL로 바꾸세요. 이 URL은 `TEXT_TO_TIMER_FUNCTION_URL` 값과 동일하지만 함수 이름이 `text-to-timer` 대신 `get-voices`입니다.

1. `src` 폴더에 `text_to_speech.h`라는 새 파일을 생성하세요. 이 파일은 텍스트를 음성으로 변환하는 클래스를 정의하는 데 사용됩니다.

1. 새 `text_to_speech.h` 파일 상단에 다음 포함 지시문을 추가하세요:

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

1. 아래에 `TextToSpeech` 클래스를 선언하고, 애플리케이션의 나머지 부분에서 사용할 수 있는 인스턴스를 추가하세요:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. 함수 앱을 호출하려면 WiFi 클라이언트를 선언해야 합니다. 클래스의 `private` 섹션에 다음을 추가하세요:

    ```cpp
    WiFiClient _client;
    ```

1. `private` 섹션에 선택된 음성을 위한 필드를 추가하세요:

    ```cpp
    String _voice;
    ```

1. `public` 섹션에 첫 번째 음성을 가져오는 `init` 함수를 추가하세요:

    ```cpp
    void init()
    {
    }
    ```

1. 음성을 가져오기 위해 JSON 문서를 생성해야 합니다. `init` 함수에 다음 코드를 추가하여 JSON 문서를 생성하세요:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. 그런 다음 `HTTPClient`를 생성하고, 이를 사용하여 함수 앱을 호출하여 음성을 가져오세요. JSON 문서를 POST 요청으로 보냅니다:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. 아래에 응답 코드를 확인하는 코드를 추가하고, 응답 코드가 200(성공)인 경우 음성 목록을 추출하여 목록에서 첫 번째 음성을 가져옵니다:

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

1. 이후 HTTP 클라이언트 연결을 종료하세요:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` 파일을 열고, 새 헤더 파일을 포함하기 위해 상단에 다음 포함 지시문을 추가하세요:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` 함수에서 `speechToText.init();` 호출 아래에 `TextToSpeech` 클래스를 초기화하는 다음 코드를 추가하세요:

    ```cpp
    textToSpeech.init();
    ```

1. 이 코드를 빌드하고 Wio Terminal에 업로드한 후, 시리얼 모니터를 통해 테스트하세요. 함수 앱이 실행 중인지 확인하세요.

    함수 앱에서 반환된 사용 가능한 음성 목록과 선택된 음성을 확인할 수 있습니다.

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

## 텍스트를 음성으로 변환

사용할 음성을 확보한 후, 이를 사용하여 텍스트를 음성으로 변환할 수 있습니다. 음성을 텍스트로 변환할 때와 동일한 메모리 제한이 음성을 텍스트로 변환할 때에도 적용되므로, 음성을 SD 카드에 저장한 후 ReSpeaker를 통해 재생해야 합니다.

> 💁 이 프로젝트의 이전 수업에서는 마이크로폰에서 캡처한 음성을 플래시 메모리에 저장했습니다. 이번 수업에서는 Seeed 오디오 라이브러리를 사용하여 SD 카드에서 오디오를 재생하는 것이 더 쉽기 때문에 SD 카드를 사용합니다.

또한 고려해야 할 또 다른 제한 사항은 음성 서비스에서 제공하는 오디오 데이터와 Wio Terminal이 지원하는 형식입니다. 일반 컴퓨터와 달리, 마이크로컨트롤러용 오디오 라이브러리는 지원하는 오디오 형식이 매우 제한적일 수 있습니다. 예를 들어, ReSpeaker를 통해 소리를 재생할 수 있는 Seeed Arduino Audio 라이브러리는 44.1KHz 샘플 속도의 오디오만 지원합니다. Azure 음성 서비스는 여러 형식으로 오디오를 제공할 수 있지만, 이들 중 어느 것도 44.1KHz 샘플 속도를 사용하지 않습니다. 대신 8KHz, 16KHz, 24KHz 및 48KHz만 제공합니다. 따라서 오디오를 44.1KHz로 다시 샘플링해야 하며, 이는 특히 메모리 측면에서 Wio Terminal이 가진 리소스보다 더 많은 리소스를 필요로 합니다.

이와 같은 데이터를 조작해야 할 때는, 특히 데이터가 웹 호출을 통해 제공되는 경우 서버리스 코드를 사용하는 것이 종종 더 좋습니다. Wio Terminal은 서버리스 함수를 호출하여 변환할 텍스트를 전달하고, 서버리스 함수는 텍스트를 음성으로 변환하는 동시에 오디오를 필요한 샘플 속도로 다시 샘플링할 수 있습니다. 그런 다음 Wio Terminal이 SD 카드에 저장하고 ReSpeaker를 통해 재생할 수 있는 형식으로 오디오를 반환할 수 있습니다.

### 작업 - 텍스트를 음성으로 변환하는 서버리스 함수 생성

1. VS Code에서 `smart-timer-trigger` 프로젝트를 열고, 가상 환경이 활성화되어 있는지 확인한 후 터미널을 엽니다. 활성화되지 않았다면 터미널을 종료하고 다시 생성하세요.

1. 이 앱에 `text-to-speech`라는 새 HTTP 트리거를 추가하세요. VS Code 터미널에서 함수 앱 프로젝트의 루트 폴더에서 다음 명령을 실행하세요:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    이렇게 하면 `text-to-speech`라는 HTTP 트리거가 생성됩니다.

1. [librosa](https://librosa.org) Pip 패키지는 오디오를 다시 샘플링하는 기능을 제공합니다. 이를 `requirements.txt` 파일에 추가하세요:

    ```sh
    librosa
    ```

    추가한 후, VS Code 터미널에서 다음 명령을 사용하여 Pip 패키지를 설치하세요:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Linux(예: Raspberry Pi OS)를 사용하는 경우, 다음 명령으로 `libsndfile`을 설치해야 할 수 있습니다:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. 텍스트를 음성으로 변환하려면 음성 API 키를 직접 사용할 수 없으며, 대신 액세스 토큰을 요청해야 합니다. 액세스 토큰 요청을 인증하기 위해 API 키를 사용합니다. `text-to-speech` 폴더의 `__init__.py` 파일을 열고 모든 코드를 다음으로 교체하세요:

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

    이는 설정에서 읽을 위치와 음성 키에 대한 상수를 정의합니다. 그런 다음 음성 서비스에 대한 액세스 토큰을 검색하는 `get_access_token` 함수를 정의합니다.

1. 이 코드 아래에 다음을 추가하세요:

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

    이는 텍스트를 음성으로 변환하는 HTTP 트리거를 정의합니다. 변환할 텍스트, 언어 및 음성을 요청 본문에서 추출하고, 음성을 요청하기 위해 SSML을 생성한 다음, 액세스 토큰을 사용하여 REST API를 호출합니다. 이 REST API 호출은 16비트, 48KHz 모노 WAV 파일로 인코딩된 오디오를 반환하며, 이는 `playback_format` 값에 의해 정의됩니다.

    그런 다음 `librosa`를 사용하여 샘플 속도를 48KHz에서 44.1KHz로 다시 샘플링하고, 이 오디오를 바이너리 버퍼에 저장한 후 반환합니다.

1. 로컬에서 함수 앱을 실행하거나 클라우드에 배포하세요. 그런 다음 `text-to-timer` HTTP 트리거를 테스트했던 것과 동일한 방식으로 curl과 같은 도구를 사용하여 호출할 수 있습니다. JSON 본문에 언어, 음성 및 텍스트를 전달하세요:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>`를 `en-GB` 또는 `zh-CN`과 같은 언어로 바꾸세요. `<voice>`를 사용하려는 음성으로 바꾸세요. `<text>`를 음성으로 변환하려는 텍스트로 바꾸세요. 출력 결과를 파일로 저장한 후, WAV 파일을 재생할 수 있는 오디오 플레이어로 재생할 수 있습니다.

    예를 들어, "Hello"를 US English의 Jenny Neural 음성을 사용하여 음성으로 변환하려면, 함수 앱이 로컬에서 실행 중일 때 다음 curl 명령을 사용할 수 있습니다:

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

    이렇게 하면 현재 디렉토리에 `hello.wav`라는 이름으로 오디오가 저장됩니다.

> 💁 이 코드는 [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) 폴더에서 찾을 수 있습니다.

### 작업 - Wio Terminal에서 음성 가져오기

1. VS Code에서 `smart-timer` 프로젝트를 열어두세요.

1. `config.h` 헤더 파일을 열고 함수 앱의 URL을 추가하세요:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>`을 함수 앱의 `text-to-speech` HTTP 트리거 URL로 바꾸세요. 이 URL은 `TEXT_TO_TIMER_FUNCTION_URL` 값과 동일하지만 함수 이름이 `text-to-timer` 대신 `text-to-speech`입니다.

1. `text_to_speech.h` 헤더 파일을 열고, `TextToSpeech` 클래스의 `public` 섹션에 다음 메서드를 추가하세요:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` 메서드에 함수 앱으로 보낼 JSON을 생성하는 다음 코드를 추가하세요:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    이는 언어, 음성 및 텍스트를 JSON 문서에 작성한 후 문자열로 직렬화합니다.

1. 아래에 함수 앱을 호출하는 다음 코드를 추가하세요:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    이는 HTTPClient를 생성한 후, JSON 문서를 사용하여 텍스트 음성 변환 HTTP 트리거에 POST 요청을 보냅니다.

1. 호출이 성공하면, 함수 앱 호출에서 반환된 원시 바이너리 데이터를 SD 카드의 파일로 스트리밍할 수 있습니다. 이를 수행하는 다음 코드를 추가하세요:

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

    이 코드는 응답을 확인하고, 응답이 200(성공)인 경우 바이너리 데이터를 SD 카드의 루트에 `SPEECH.WAV`라는 이름으로 저장합니다.

1. 이 메서드 끝에서 HTTP 연결을 닫으세요:

    ```cpp
    httpClient.end();
    ```

1. 이제 말할 텍스트를 오디오로 변환할 수 있습니다. `main.cpp` 파일에서 `say` 함수 끝에 다음 줄을 추가하여 말할 텍스트를 오디오로 변환하세요:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### 작업 - Wio Terminal에서 오디오 재생하기

**곧 제공됩니다**

## 함수 앱을 클라우드에 배포하기

함수 앱을 로컬에서 실행하는 이유는 리눅스에서 `librosa` Pip 패키지가 기본적으로 설치되지 않은 라이브러리에 의존하기 때문입니다. 이 라이브러리는 함수 앱이 실행되기 전에 설치되어야 합니다. 함수 앱은 서버리스이므로, 사용자가 직접 관리할 수 있는 서버가 없으며, 이 라이브러리를 사전에 설치할 방법도 없습니다.

이를 해결하는 방법은 Docker 컨테이너를 사용하여 함수 앱을 배포하는 것입니다. 이 컨테이너는 클라우드가 새로운 함수 앱 인스턴스를 실행해야 할 때(예: 수요가 가용 자원을 초과하거나, 함수 앱이 한동안 사용되지 않아 종료된 경우) 배포됩니다.

Linux에서 사용자 지정 컨테이너를 사용하여 함수 앱을 생성하고 Docker를 통해 배포하는 방법에 대한 지침은 [Microsoft Docs의 관련 문서](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python)를 참조하세요.

배포가 완료되면, Wio Terminal 코드를 포팅하여 이 함수를 호출할 수 있습니다:

1. Azure Functions 인증서를 `config.h`에 추가하세요:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. 모든 `<WiFiClient.h>` 포함을 `<WiFiClientSecure.h>`로 변경하세요.

1. 모든 `WiFiClient` 필드를 `WiFiClientSecure`로 변경하세요.

1. `WiFiClientSecure` 필드를 가진 모든 클래스에 생성자를 추가하고, 해당 생성자에서 인증서를 설정하세요:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.