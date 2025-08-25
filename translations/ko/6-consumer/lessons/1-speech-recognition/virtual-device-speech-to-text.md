<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-25T00:24:09+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "ko"
}
-->
# 음성을 텍스트로 변환 - 가상 IoT 디바이스

이 수업의 이 부분에서는 마이크로폰에서 캡처된 음성을 음성 서비스를 사용하여 텍스트로 변환하는 코드를 작성합니다.

## 음성을 텍스트로 변환하기

Windows, Linux, macOS에서 음성 서비스 Python SDK를 사용하여 마이크로폰을 통해 음성을 듣고 감지된 음성을 텍스트로 변환할 수 있습니다. 이 SDK는 지속적으로 청취하며, 오디오 레벨이 떨어질 때(예: 음성 블록이 끝날 때) 오디오를 감지하여 텍스트로 변환합니다.

### 작업 - 음성을 텍스트로 변환하기

1. `smart-timer`라는 폴더에 `app.py`라는 단일 파일과 Python 가상 환경을 포함한 새로운 Python 앱을 컴퓨터에 만드세요.

1. 음성 서비스용 Pip 패키지를 설치하세요. 가상 환경이 활성화된 터미널에서 설치해야 합니다.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ 다음과 같은 오류가 발생할 경우:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Pip을 업데이트해야 합니다. 아래 명령어를 사용하여 업데이트한 후 다시 패키지를 설치해 보세요.
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py` 파일에 다음 import를 추가하세요:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    이는 음성을 인식하는 데 사용되는 몇 가지 클래스를 가져옵니다.

1. 다음 코드를 추가하여 일부 설정을 선언하세요:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>`를 음성 서비스의 API 키로 바꾸세요. `<location>`을 음성 서비스 리소스를 생성할 때 사용한 위치로 바꾸세요.

    `<language>`를 사용할 언어의 로케일 이름으로 바꾸세요. 예를 들어 영어의 경우 `en-GB`, 광둥어의 경우 `zn-HK`를 사용합니다. 지원되는 언어와 로케일 이름 목록은 [Microsoft 문서의 언어 및 음성 지원 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)에서 확인할 수 있습니다.

    이 설정은 음성 서비스를 구성하는 데 사용되는 `SpeechConfig` 객체를 생성하는 데 사용됩니다.

1. 음성 인식기를 생성하는 다음 코드를 추가하세요:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. 음성 인식기는 백그라운드 스레드에서 실행되며, 오디오를 청취하고 감지된 음성을 텍스트로 변환합니다. 텍스트를 가져오려면 콜백 함수를 정의하고 이를 인식기에 전달해야 합니다. 음성이 감지될 때마다 콜백이 호출됩니다. 콜백을 정의하고 이를 인식기에 전달하며, 텍스트를 처리하여 콘솔에 출력하는 함수를 정의하는 다음 코드를 추가하세요:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. 인식기는 명시적으로 시작해야만 청취를 시작합니다. 인식을 시작하는 다음 코드를 추가하세요. 이는 백그라운드에서 실행되므로 애플리케이션을 계속 실행하기 위해 무한 루프와 sleep을 추가해야 합니다.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. 이 앱을 실행하세요. 마이크로폰에 대고 말하면 변환된 텍스트가 콘솔에 출력됩니다.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    다양한 유형의 문장과 단어의 소리는 같지만 의미가 다른 문장을 시도해 보세요. 예를 들어, 영어로 말할 경우 'I want to buy two bananas and an apple too'라고 말해 보세요. 그러면 단어의 소리뿐만 아니라 문맥에 따라 적절한 'to', 'two', 'too'를 사용합니다.

> 💁 이 코드는 [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) 폴더에서 확인할 수 있습니다.

😀 음성을 텍스트로 변환하는 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.