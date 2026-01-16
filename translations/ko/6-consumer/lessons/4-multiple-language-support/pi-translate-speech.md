<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-24T23:55:29+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "ko"
}
-->
# 음성 번역 - Raspberry Pi

이 수업의 이 부분에서는 번역 서비스를 사용하여 텍스트를 번역하는 코드를 작성합니다.

## 번역 서비스를 사용하여 텍스트를 음성으로 변환하기

음성 서비스 REST API는 직접 번역을 지원하지 않습니다. 대신, 음성을 텍스트로 변환하는 서비스에서 생성된 텍스트와 응답으로 말할 텍스트를 번역하기 위해 번역 서비스를 사용할 수 있습니다. 이 서비스는 텍스트를 번역하는 데 사용할 수 있는 REST API를 제공합니다.

### 작업 - 번역 리소스를 사용하여 텍스트 번역하기

1. 스마트 타이머에는 두 개의 언어가 설정됩니다. 하나는 LUIS를 훈련시킬 때 사용된 서버 언어(사용자에게 말할 메시지를 작성하는 데도 사용됨)이고, 다른 하나는 사용자가 말하는 언어입니다. `language` 변수를 사용자가 말할 언어로 업데이트하고, LUIS를 훈련시킬 때 사용된 언어를 나타내는 새로운 변수 `server_language`를 추가하세요:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>`를 사용자가 말할 언어의 로케일 이름으로 바꾸세요. 예를 들어, 프랑스어는 `fr-FR`, 광둥어는 `zn-HK`입니다.

    `<server language>`를 LUIS를 훈련시킬 때 사용된 언어의 로케일 이름으로 바꾸세요.

    지원되는 언어와 로케일 이름 목록은 [Microsoft 문서의 언어 및 음성 지원 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)에서 확인할 수 있습니다.

    > 💁 여러 언어를 구사하지 않는 경우, [Bing Translate](https://www.bing.com/translator) 또는 [Google Translate](https://translate.google.com)와 같은 서비스를 사용하여 선호하는 언어에서 다른 언어로 번역할 수 있습니다. 이러한 서비스는 번역된 텍스트의 오디오를 재생할 수도 있습니다.
    >
    > 예를 들어, LUIS를 영어로 훈련시키고 사용자 언어로 프랑스어를 사용하고 싶다면, Bing Translate을 사용하여 "2분 27초 타이머 설정"과 같은 문장을 영어에서 프랑스어로 번역한 다음, **번역 듣기** 버튼을 사용하여 번역된 내용을 마이크에 말할 수 있습니다.
    >
    > ![Bing Translate의 번역 듣기 버튼](../../../../../translated_images/ko/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `speech_api_key` 아래에 번역 API 키를 추가하세요:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>`를 번역 서비스 리소스의 API 키로 바꾸세요.

1. `say` 함수 위에 서버 언어에서 사용자 언어로 텍스트를 번역하는 `translate_text` 함수를 정의하세요:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    이 함수에는 변환할 언어가 전달됩니다. 앱은 음성을 인식할 때 사용자 언어에서 서버 언어로, 사용자에게 말할 때 서버 언어에서 사용자 언어로 변환해야 합니다.

1. 이 함수 내부에서 REST API 호출을 위한 URL과 헤더를 정의하세요:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    이 API의 URL은 위치에 따라 달라지지 않으며, 대신 위치는 헤더로 전달됩니다. API 키는 직접 사용되므로, 음성 서비스와 달리 토큰 발급 API에서 액세스 토큰을 가져올 필요가 없습니다.

1. 그 아래에 호출을 위한 매개변수와 본문을 정의하세요:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params`는 API 호출에 전달할 매개변수를 정의하며, `from` 언어에서 `to` 언어로 텍스트를 번역합니다.

    `body`는 번역할 텍스트를 포함합니다. 이는 배열 형태로, 한 번의 호출에서 여러 텍스트 블록을 번역할 수 있습니다.

1. REST API를 호출하고 응답을 가져오세요:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    반환된 응답은 JSON 배열이며, 번역을 포함한 항목이 하나 있습니다. 이 항목은 본문에 전달된 모든 항목의 번역을 포함하는 배열을 가지고 있습니다.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. 배열의 첫 번째 항목에서 첫 번째 번역의 `test` 속성을 반환하세요:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` 루프를 업데이트하여 사용자 언어에서 서버 언어로 `convert_speech_to_text` 호출의 텍스트를 번역하세요:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    이 코드는 원본 텍스트와 번역된 텍스트를 콘솔에 출력합니다.

1. `say` 함수를 업데이트하여 서버 언어에서 사용자 언어로 말할 텍스트를 번역하세요:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    이 코드는 원본 텍스트와 번역된 텍스트를 콘솔에 출력합니다.

1. 코드를 실행하세요. 함수 앱이 실행 중인지 확인하고, 사용자 언어로 타이머를 요청하세요. 직접 해당 언어를 말하거나 번역 앱을 사용하여 요청할 수 있습니다.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 언어마다 표현 방식이 다르기 때문에, LUIS에 제공한 예제와 약간 다른 번역이 나올 수 있습니다. 이 경우, LUIS에 더 많은 예제를 추가하고 다시 훈련한 후 모델을 다시 게시하세요.

> 💁 이 코드는 [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) 폴더에서 찾을 수 있습니다.

😀 다국어 타이머 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.