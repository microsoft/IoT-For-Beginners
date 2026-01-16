<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-24T23:57:03+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "ko"
}
-->
# 음성 번역 - 가상 IoT 디바이스

이 강의의 이 부분에서는 음성 서비스를 사용하여 음성을 텍스트로 변환할 때 번역하는 코드를 작성한 후, 번역기 서비스를 사용하여 텍스트를 번역하고 음성 응답을 생성합니다.

## 음성 서비스를 사용하여 음성을 번역하기

음성 서비스는 음성을 동일한 언어로 텍스트로 변환할 뿐만 아니라, 출력 텍스트를 다른 언어로 번역할 수도 있습니다.

### 작업 - 음성 서비스를 사용하여 음성을 번역하기

1. VS Code에서 `smart-timer` 프로젝트를 열고, 터미널에서 가상 환경이 로드되었는지 확인합니다.

1. 기존 import 문 아래에 다음 import 문을 추가합니다:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    이는 음성을 번역하는 데 사용되는 클래스와, 이후 강의에서 번역기 서비스 호출에 사용될 `requests` 라이브러리를 가져옵니다.

1. 스마트 타이머에는 두 개의 언어가 설정됩니다 - LUIS를 학습시키는 데 사용된 서버 언어(사용자와 대화할 메시지를 생성하는 데도 사용됨)와 사용자가 말하는 언어입니다. `language` 변수를 사용자가 말할 언어로 업데이트하고, LUIS를 학습시키는 데 사용된 언어를 위한 `server_language`라는 새 변수를 추가합니다:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>`를 사용자가 말할 언어의 로케일 이름으로 바꿉니다. 예를 들어, 프랑스어는 `fr-FR`, 광둥어는 `zn-HK`입니다.

    `<server language>`를 LUIS를 학습시키는 데 사용된 언어의 로케일 이름으로 바꿉니다.

    지원되는 언어와 로케일 이름 목록은 [Microsoft 문서의 언어 및 음성 지원 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)에서 확인할 수 있습니다.

    > 💁 여러 언어를 구사하지 못하는 경우, [Bing 번역기](https://www.bing.com/translator)나 [Google 번역기](https://translate.google.com)와 같은 서비스를 사용하여 선호하는 언어에서 원하는 언어로 번역할 수 있습니다. 이 서비스들은 번역된 텍스트의 오디오를 재생할 수도 있습니다. 음성 인식기가 디바이스의 일부 오디오 출력을 무시할 수 있으므로, 번역된 텍스트를 재생하려면 추가 디바이스가 필요할 수 있습니다.
    >
    > 예를 들어, LUIS를 영어로 학습시키고, 사용자 언어로 프랑스어를 사용하려는 경우, Bing 번역기를 사용하여 "set a 2 minute and 27 second timer"와 같은 문장을 영어에서 프랑스어로 번역한 다음, **번역 듣기** 버튼을 사용하여 번역된 문장을 마이크에 말할 수 있습니다.
    >
    > ![Bing 번역기의 번역 듣기 버튼](../../../../../translated_images/ko/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `recognizer_config`와 `recognizer` 선언을 다음으로 교체합니다:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    이는 사용자 언어로 음성을 인식하고, 사용자 언어와 서버 언어로 번역을 생성하는 번역 구성을 만듭니다. 그런 다음 이 구성을 사용하여 번역 인식기를 생성합니다. 이는 음성 인식 결과를 여러 언어로 번역할 수 있는 음성 인식기입니다.

    > 💁 원래 언어는 `target_languages`에 지정되어야 하며, 그렇지 않으면 번역이 생성되지 않습니다.

1. `recognized` 함수를 업데이트하고, 함수의 전체 내용을 다음으로 교체합니다:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    이 코드는 인식된 이벤트가 음성이 번역되었기 때문에 발생했는지 확인합니다(이 이벤트는 음성이 인식되었지만 번역되지 않은 경우 등 다른 상황에서도 발생할 수 있습니다). 음성이 번역된 경우, `args.result.translations` 딕셔너리에서 서버 언어와 일치하는 번역을 찾습니다.

    `args.result.translations` 딕셔너리는 로케일 설정의 전체가 아닌 언어 부분을 키로 사용합니다. 예를 들어, 프랑스어에 대해 `fr-FR`로 번역을 요청하면, 딕셔너리에는 `fr` 항목이 포함되며, `fr-FR`은 포함되지 않습니다.

    번역된 텍스트는 IoT Hub로 전송됩니다.

1. 이 코드를 실행하여 번역을 테스트합니다. 함수 앱이 실행 중인지 확인하고, 사용자 언어로 타이머를 요청합니다. 직접 해당 언어를 말하거나 번역 앱을 사용할 수 있습니다.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## 번역기 서비스를 사용하여 텍스트 번역하기

음성 서비스는 텍스트를 다시 음성으로 번역하는 것을 지원하지 않습니다. 대신 번역기 서비스를 사용하여 텍스트를 번역할 수 있습니다. 이 서비스는 텍스트를 번역하는 데 사용할 수 있는 REST API를 제공합니다.

### 작업 - 번역기 리소스를 사용하여 텍스트 번역하기

1. `speech_api_key` 아래에 번역기 API 키를 추가합니다:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>`를 번역기 서비스 리소스의 API 키로 바꿉니다.

1. `say` 함수 위에 서버 언어에서 사용자 언어로 텍스트를 번역하는 `translate_text` 함수를 정의합니다:

    ```python
    def translate_text(text):
    ```

1. 이 함수 내부에 REST API 호출을 위한 URL과 헤더를 정의합니다:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    이 API의 URL은 위치에 따라 달라지지 않으며, 대신 위치는 헤더로 전달됩니다. API 키는 직접 사용되므로, 음성 서비스와 달리 토큰 발급 API에서 액세스 토큰을 가져올 필요가 없습니다.

1. 아래에 호출을 위한 매개변수와 본문을 정의합니다:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params`는 API 호출에 전달할 매개변수를 정의하며, `from` 언어에서 `to` 언어로 텍스트를 번역합니다.

    `body`는 번역할 텍스트를 포함합니다. 이는 배열로, 본문에 전달된 여러 텍스트 블록을 한 번에 번역할 수 있습니다.

1. REST API를 호출하고 응답을 가져옵니다:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    반환된 응답은 JSON 배열로, 번역을 포함하는 항목이 하나 있습니다. 이 항목에는 본문에 전달된 모든 항목의 번역이 포함된 배열이 있습니다.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. 배열의 첫 번째 항목에서 첫 번째 번역의 `text` 속성을 반환합니다:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `say` 함수에서 SSML이 생성되기 전에 말할 텍스트를 번역하도록 업데이트합니다:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    이 코드는 원본 텍스트와 번역된 텍스트를 콘솔에 출력하기도 합니다.

1. 코드를 실행합니다. 함수 앱이 실행 중인지 확인하고, 사용자 언어로 타이머를 요청합니다. 직접 해당 언어를 말하거나 번역 앱을 사용할 수 있습니다.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 언어마다 표현 방식이 다르기 때문에, LUIS에 제공한 예제와 약간 다른 번역이 나올 수 있습니다. 이 경우, LUIS에 더 많은 예제를 추가하고 다시 학습한 후 모델을 다시 게시하세요.

> 💁 이 코드는 [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) 폴더에서 확인할 수 있습니다.

😀 다국어 타이머 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.