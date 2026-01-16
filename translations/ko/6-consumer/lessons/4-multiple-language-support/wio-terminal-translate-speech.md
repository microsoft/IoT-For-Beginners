<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-24T23:50:16+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "ko"
}
-->
# 음성 번역 - Wio Terminal

이 수업의 이 부분에서는 번역 서비스로 텍스트를 번역하는 코드를 작성합니다.

## 번역 서비스를 사용하여 텍스트를 음성으로 변환하기

음성 서비스 REST API는 직접 번역을 지원하지 않습니다. 대신, 음성을 텍스트로 변환한 결과와 응답 텍스트를 번역하기 위해 번역 서비스를 사용할 수 있습니다. 이 서비스는 텍스트를 번역하기 위한 REST API를 제공하며, 이를 더 쉽게 사용하기 위해 함수 앱에서 또 다른 HTTP 트리거로 감쌀 것입니다.

### 작업 - 텍스트를 번역하는 서버리스 함수 생성하기

1. VS Code에서 `smart-timer-trigger` 프로젝트를 열고, 가상 환경이 활성화되어 있는지 확인한 후 터미널을 엽니다. 활성화되지 않았다면 터미널을 종료하고 다시 생성하세요.

1. `local.settings.json` 파일을 열고 번역 API 키와 위치에 대한 설정을 추가하세요:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>`를 번역 서비스 리소스의 API 키로 바꾸세요. `<location>`을 번역 서비스 리소스를 생성할 때 사용한 위치로 바꾸세요.

1. 다음 명령어를 사용하여 이 앱에 `translate-text`라는 새 HTTP 트리거를 추가하세요. 이 명령어는 VS Code 터미널에서 함수 앱 프로젝트의 루트 폴더에서 실행해야 합니다:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    이 명령어는 `translate-text`라는 HTTP 트리거를 생성합니다.

1. `translate-text` 폴더의 `__init__.py` 파일 내용을 다음으로 교체하세요:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    이 코드는 HTTP 요청에서 텍스트와 언어를 추출합니다. 그런 다음 번역 REST API에 요청을 보내 URL의 매개변수로 언어를 전달하고, 번역할 텍스트를 본문으로 보냅니다. 마지막으로 번역된 텍스트를 반환합니다.

1. 로컬에서 함수 앱을 실행하세요. 그런 다음 curl과 같은 도구를 사용하여 `text-to-timer` HTTP 트리거를 테스트했던 것과 동일한 방식으로 호출할 수 있습니다. 번역할 텍스트와 언어를 JSON 본문으로 전달하세요:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    이 예제는 프랑스어로 된 *Définir une minuterie de 30 secondes*를 미국 영어로 번역합니다. 결과는 *Set a 30-second timer*가 됩니다.

> 💁 이 코드는 [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) 폴더에서 찾을 수 있습니다.

### 작업 - 번역 함수를 사용하여 텍스트 번역하기

1. `smart-timer` 프로젝트가 열려 있지 않다면 VS Code에서 엽니다.

1. 스마트 타이머에는 두 가지 언어가 설정됩니다. 하나는 LUIS를 학습시킬 때 사용된 서버 언어(사용자에게 말할 메시지를 생성하는 데도 사용됨)이고, 다른 하나는 사용자가 말하는 언어입니다. `config.h` 헤더 파일의 `LANGUAGE` 상수를 사용자가 말할 언어로 업데이트하고, LUIS를 학습시킬 때 사용된 언어를 위한 `SERVER_LANGUAGE`라는 새 상수를 추가하세요:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>`를 사용자가 말할 언어의 로케일 이름으로 바꾸세요. 예를 들어 프랑스어는 `fr-FR`, 광둥어는 `zn-HK`입니다.

    `<server language>`를 LUIS를 학습시킬 때 사용된 언어의 로케일 이름으로 바꾸세요.

    지원되는 언어와 로케일 이름 목록은 [Microsoft 문서의 언어 및 음성 지원 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)에서 확인할 수 있습니다.

    > 💁 여러 언어를 구사하지 못하는 경우 [Bing 번역기](https://www.bing.com/translator)나 [Google 번역기](https://translate.google.com)와 같은 서비스를 사용하여 선호하는 언어에서 원하는 언어로 번역할 수 있습니다. 이 서비스들은 번역된 텍스트의 오디오를 재생할 수도 있습니다.
    >
    > 예를 들어, LUIS를 영어로 학습시키고 사용자 언어로 프랑스어를 사용하고 싶다면, Bing 번역기를 사용하여 "set a 2 minute and 27 second timer"와 같은 문장을 영어에서 프랑스어로 번역한 후 **번역 듣기** 버튼을 사용하여 번역된 문장을 마이크에 말할 수 있습니다.
    >
    > ![Bing 번역기의 번역 듣기 버튼](../../../../../translated_images/ko/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `SPEECH_LOCATION` 아래에 번역 API 키와 위치를 추가하세요:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>`를 번역 서비스 리소스의 API 키로 바꾸세요. `<LOCATION>`을 번역 서비스 리소스를 생성할 때 사용한 위치로 바꾸세요.

1. `VOICE_URL` 아래에 번역 트리거 URL을 추가하세요:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>`을 함수 앱의 `translate-text` HTTP 트리거 URL로 바꾸세요. 이 값은 `TEXT_TO_TIMER_FUNCTION_URL`의 값과 동일하지만, 함수 이름이 `text-to-timer` 대신 `translate-text`입니다.

1. `src` 폴더에 `text_translator.h`라는 새 파일을 추가하세요.

1. 이 새로운 `text_translator.h` 헤더 파일은 텍스트를 번역하는 클래스를 포함합니다. 이 파일에 다음 내용을 추가하여 클래스를 선언하세요:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    이는 `TextTranslator` 클래스를 선언하며, 이 클래스의 인스턴스를 포함합니다. 클래스는 WiFi 클라이언트를 위한 단일 필드를 가집니다.

1. 이 클래스의 `public` 섹션에 텍스트를 번역하는 메서드를 추가하세요:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    이 메서드는 번역할 언어와 번역될 언어를 받습니다. 음성을 처리할 때는 사용자 언어에서 LUIS 서버 언어로 번역하고, 응답을 제공할 때는 LUIS 서버 언어에서 사용자 언어로 번역합니다.

1. 이 메서드에 번역할 텍스트와 언어를 포함하는 JSON 본문을 생성하는 코드를 추가하세요:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. 그 아래에 서버리스 함수 앱으로 본문을 보내는 코드를 추가하세요:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. 다음으로, 응답을 가져오는 코드를 추가하세요:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. 마지막으로 연결을 닫고 번역된 텍스트를 반환하는 코드를 추가하세요:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### 작업 - 인식된 음성과 응답 번역하기

1. `main.cpp` 파일을 엽니다.

1. 파일 상단에 `TextTranslator` 클래스 헤더 파일에 대한 include 지시문을 추가하세요:

    ```cpp
    #include "text_translator.h"
    ```

1. 타이머가 설정되거나 만료될 때 말하는 텍스트를 번역해야 합니다. 이를 위해 `say` 함수의 첫 번째 줄로 다음을 추가하세요:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    이는 텍스트를 사용자 언어로 번역합니다.

1. `processAudio` 함수에서 `String text = speechToText.convertSpeechToText();` 호출로 캡처된 오디오에서 텍스트를 가져옵니다. 이 호출 후 텍스트를 번역하세요:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    이는 텍스트를 사용자 언어에서 서버에서 사용된 언어로 번역합니다.

1. 이 코드를 빌드하고 Wio Terminal에 업로드한 후 시리얼 모니터를 통해 테스트하세요. 시리얼 모니터에서 `Ready`가 표시되면 C 버튼(왼쪽에 있는 버튼으로 전원 스위치에 가장 가까운 버튼)을 누르고 말하세요. 함수 앱이 실행 중인지 확인하고, 사용자 언어로 타이머를 요청하세요. 직접 해당 언어로 말하거나 번역 앱을 사용해도 됩니다.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 이 코드는 [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 다국어 타이머 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.