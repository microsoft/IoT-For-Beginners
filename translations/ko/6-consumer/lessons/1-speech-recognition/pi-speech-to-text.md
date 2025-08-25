<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-25T00:34:09+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "ko"
}
-->
# 음성을 텍스트로 변환 - Raspberry Pi

이 수업의 이 부분에서는 캡처된 오디오의 음성을 텍스트로 변환하는 코드를 작성합니다. 이를 위해 음성 서비스를 사용합니다.

## 오디오를 음성 서비스로 전송하기

오디오는 REST API를 사용하여 음성 서비스로 전송할 수 있습니다. 음성 서비스를 사용하려면 먼저 액세스 토큰을 요청한 다음, 해당 토큰을 사용하여 REST API에 접근해야 합니다. 이 액세스 토큰은 10분 후에 만료되므로, 항상 최신 상태를 유지하기 위해 코드는 정기적으로 토큰을 요청해야 합니다.

### 작업 - 액세스 토큰 가져오기

1. Raspberry Pi에서 `smart-timer` 프로젝트를 엽니다.

1. `play_audio` 함수를 제거합니다. 스마트 타이머가 사용자가 말한 내용을 반복하지 않도록 이 함수는 더 이상 필요하지 않습니다.

1. `app.py` 파일 상단에 다음 import를 추가합니다:

    ```python
    import requests
    ```

1. `while True` 루프 위에 다음 코드를 추가하여 음성 서비스 설정을 선언합니다:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>`를 음성 서비스 리소스의 API 키로 교체하세요. `<location>`은 음성 서비스 리소스를 생성할 때 사용한 위치로 교체하세요.

    `<language>`는 사용자가 말할 언어의 로케일 이름으로 교체하세요. 예를 들어, 영어는 `en-GB`, 광둥어는 `zn-HK`입니다. 지원되는 언어와 로케일 이름 목록은 [Microsoft 문서의 언어 및 음성 지원 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)에서 확인할 수 있습니다.

1. 그 아래에 액세스 토큰을 가져오는 다음 함수를 추가합니다:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    이 함수는 API 키를 헤더로 전달하여 토큰 발급 엔드포인트를 호출합니다. 이 호출은 음성 서비스를 호출하는 데 사용할 수 있는 액세스 토큰을 반환합니다.

1. 그 아래에 REST API를 사용하여 캡처된 오디오의 음성을 텍스트로 변환하는 함수를 선언합니다:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. 이 함수 내부에서 REST API URL과 헤더를 설정합니다:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    이 코드는 음성 서비스 리소스의 위치를 사용하여 URL을 생성합니다. 그런 다음 `get_access_token` 함수에서 가져온 액세스 토큰과 오디오 캡처에 사용된 샘플 속도를 헤더에 추가합니다. 마지막으로, 오디오 언어를 포함하는 URL 매개변수를 정의합니다.

1. 그 아래에 REST API를 호출하고 텍스트를 반환받는 다음 코드를 추가합니다:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    이 코드는 URL을 호출하고 응답으로 들어오는 JSON 값을 디코딩합니다. 응답의 `RecognitionStatus` 값이 음성을 성공적으로 텍스트로 변환했는지 나타냅니다. 이 값이 `Success`인 경우 텍스트가 함수에서 반환되고, 그렇지 않으면 빈 문자열이 반환됩니다.

1. `while True:` 루프 위에 음성을 텍스트로 변환한 결과를 처리하는 함수를 정의합니다. 이 함수는 현재 텍스트를 콘솔에 출력하는 역할만 합니다.

    ```python
    def process_text(text):
        print(text)
    ```

1. 마지막으로, `while True` 루프에서 `play_audio` 호출을 `convert_speech_to_text` 함수 호출로 교체하고, 텍스트를 `process_text` 함수에 전달합니다:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. 코드를 실행합니다. 버튼을 누르고 마이크에 대고 말하세요. 완료되면 버튼을 놓으세요. 오디오가 텍스트로 변환되어 콘솔에 출력됩니다.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    다양한 유형의 문장을 시도해 보세요. 단어의 소리는 같지만 의미가 다른 문장도 시도해 보세요. 예를 들어, 영어로 "I want to buy two bananas and an apple too"라고 말하면, 문맥에 따라 to, two, too를 올바르게 사용한다는 것을 확인할 수 있습니다.

> 💁 이 코드는 [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) 폴더에서 확인할 수 있습니다.

😀 음성을 텍스트로 변환하는 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.