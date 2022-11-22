# 음성을 텍스트로 변환하기 - Raspberry Pi

이 단원에서는 음성 서비스를 사용하여 캡처한 오디오의 음성을 텍스트로 변환하는 코드를 작성합니다.

## 음성 서비스로 오디오 보내기

REST API를 사용하여 음성 서비스를 오디오로 보낼 수 있습니다. 음성 서비스를 사용하려면, 먼저 접근 토큰을 요청한 다음, 해당 토큰을 사용하여 REST API에 접근합니다. 이러한 접근 토큰은 10분 후에 만료되므로, 항상 최신의 상태인지 확인하기 위해 코드에서 정기적으로 요청해야 합니다.

### 작업 - 접근 토큰 가져오기

1. Pi에서 `smart-timer` 프로젝트를 엽니다.

2. `play_audio` 함수를 제거합니다. 스마트 타이머가 당신이 말한 것을 다시 반복하는 것을 원하지 않기 때문에 더이상 필요하지 않습니다.

3. `app.py` 파일의 맨 위에 다음 import 를 추가합니다:

   ```python
   import requests
   ```

4. 음성 서비스에 대한 일부 설정을 위해 `while True` 루프 위에 다음 코드를 추가합니다:

   ```python
   speech_api_key = '<key>'
   location = '<location>'
   language = '<language>'
   ```

   `<key>` 를 음성 서비스 리소스의 API 키로 바꿉니다. `<location>` 를 음성 서비스 리소스를 만들 때 사용한 위치로 바꿉니다.

   `<language>` 를 당신이 사용할 언어의 지역 이름으로 바꿉니다. 예를 들어 영어는 `en-GB`, 광둥어는 `zn-HK`로 표기합니다. 지원되는 언어 목록과 해당 지역 이름은 [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 에서 찾을 수 있습니다.

5. 이 아래에, 다음 함수를 추가하여 접근 토큰을 가져옵니다:

   ```python
   def get_access_token():
       headers = {
           'Ocp-Apim-Subscription-Key': speech_api_key
       }

       token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
       response = requests.post(token_endpoint, headers=headers)
       return str(response.text)
   ```

   이것은 토큰 isuuing endpoint 를 호출해, API 키를 헤더처럼 전달합니다. 이 호출은 음성 서비스를 호출하는데 사용되는 접근 토큰을 반환합니다.

6. 이 아래에, REST API를 사용해 캡쳐된 오디오의 음성을 텍스트로 변환하는 함수를 선언합니다:

   ```python
   def convert_speech_to_text(buffer):
   ```

7. 이 함수 내에서, REST API URL과 헤더를 설정합니다:

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

   이것은 음성 서비스 리소스의 위치를 사용하여 URL을 빌드합니다. 그런 다음 `get_access_token` 함수의 접근 토큰과 오디오 캡처에 사용되는 샘플 rate으로 헤더를 채웁니다. 마지막으로 URL과 함께 전달할 오디오의 언어가 포함된 일부 매개변수를 정의합니다.

8. 이 아래에, 다음 코드를 추가하여 REST API를 호출하고 텍스트를 다시 가져옵니다:

   ```python
   response = requests.post(url, headers=headers, params=params, data=buffer)
   response_json = response.json()

   if response_json['RecognitionStatus'] == 'Success':
       return response_json['DisplayText']
   else:
       return ''
   ```

   이는 URL을 호출하고 응답으로 들어오는 JSON 값을 디코딩합니다. 응답의 `RecognitionStatus` 값은 호출이 성공적으로 음성을 텍스트로 추출할 수 있는지 나타냅니다. `Success`인 경우 함수는 텍스트를 반환하고 아닌 경우, 빈 문자열이 반환됩니다.

9. `while True:` 루프 위에, 음성을 텍스트로 변환하는 서비스에서 반환되는 텍스트를 처리하는 함수를 정의합니다. 이 함수는 콘솔에 텍스트를 텍스트를 콘솔에 출력합니다.

   ```python
   def process_text(text):
       print(text)
   ```

10. 마지막으로 `while True` 루프 안의 호출을 `play_audio`를 `convert_speech_to_text` 함수로 바꾸고, 텍스트를 `process_text` 함수에 전달합니다:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

11. 코드를 실행합니다. 버튼을 누르고 마이크에 대고 말합니다. 완료되면 버튼을 놓고, 오디오가 텍스트로 변환되어 콘솔에 출력될 것입니다.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    동음이의어를 포함한, 다른 유형의 문장을 시도합니다. 예를 들어, 영어로 말할 때, 'I want to buy two bananas and an apple too' 라고 말하고, 어떻게 올바르게 사용되는지 주목하세요. two 와 too 는 소리 뿐만 아니라, 단어의 문맥에 기반합니다.

> 💁 이 코드는 [code-speech-to-text/pi](code-speech-to-text/pi) 폴더에서 찾을 수 있습니다.

😀 음성을 텍스트로 변환하는 프로그램이 성공적으로 완료되었습니다!
