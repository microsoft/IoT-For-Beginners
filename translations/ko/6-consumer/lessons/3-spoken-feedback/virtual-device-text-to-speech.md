<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-25T00:16:25+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "ko"
}
-->
# 텍스트 음성 변환 - 가상 IoT 디바이스

이 수업의 이 부분에서는 음성 서비스를 사용하여 텍스트를 음성으로 변환하는 코드를 작성하게 됩니다.

## 텍스트를 음성으로 변환하기

지난 수업에서 음성을 텍스트로 변환하기 위해 사용했던 음성 서비스 SDK는 텍스트를 다시 음성으로 변환하는 데에도 사용할 수 있습니다. 음성을 요청할 때는 사용할 음성을 지정해야 하며, 다양한 음성을 사용하여 음성을 생성할 수 있습니다.

각 언어는 여러 가지 음성을 지원하며, 음성 서비스 SDK를 통해 각 언어에 대해 지원되는 음성 목록을 확인할 수 있습니다.

### 작업 - 텍스트를 음성으로 변환하기

1. VS Code에서 `smart-timer` 프로젝트를 열고, 터미널에서 가상 환경이 로드되어 있는지 확인하세요.

1. 기존의 import 구문에 `azure.cognitiveservices.speech` 패키지에서 `SpeechSynthesizer`를 추가하세요:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say` 함수 위에 음성 합성기에서 사용할 음성 구성을 생성하세요:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    이는 인식기에 사용된 것과 동일한 API 키, 위치 및 언어를 사용합니다.

1. 그 아래에 다음 코드를 추가하여 음성을 가져오고 이를 음성 구성에 설정하세요:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    이 코드는 사용 가능한 모든 음성 목록을 가져온 다음, 사용 중인 언어와 일치하는 첫 번째 음성을 찾습니다.

    > 💁 Microsoft Docs의 [언어 및 음성 지원 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech)에서 지원되는 음성의 전체 목록을 확인할 수 있습니다. 특정 음성을 사용하려면 이 함수를 제거하고 해당 문서에서 음성 이름을 하드코딩하여 사용할 수 있습니다. 예를 들어:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say` 함수의 내용을 업데이트하여 응답에 대한 SSML을 생성하세요:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. 그 아래에 음성 인식을 중지하고, SSML을 읽은 후, 다시 인식을 시작하는 코드를 추가하세요:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    텍스트가 음성으로 출력되는 동안 타이머 시작 알림이 감지되어 LUIS로 전송되고, 새로운 타이머 설정 요청으로 해석되는 것을 방지하기 위해 음성 인식을 중지합니다.

    > 💁 음성 인식을 중지하고 다시 시작하는 코드를 주석 처리하여 테스트해볼 수 있습니다. 타이머를 하나 설정하면, 알림이 새로운 타이머를 설정하게 되고, 이로 인해 새로운 알림이 발생하며, 무한히 반복될 수 있습니다!

1. 앱을 실행하고, 함수 앱도 실행 중인지 확인하세요. 타이머를 설정하면 타이머가 설정되었다는 음성 응답을 들을 수 있으며, 타이머가 완료되면 또 다른 음성 응답이 출력됩니다.

> 💁 이 코드는 [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) 폴더에서 확인할 수 있습니다.

😀 타이머 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.