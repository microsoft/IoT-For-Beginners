<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-25T00:11:34+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "ko"
}
-->
# 텍스트를 음성으로 변환 - Raspberry Pi

이 수업의 이 부분에서는 음성 서비스를 사용하여 텍스트를 음성으로 변환하는 코드를 작성하게 됩니다.

## 음성 서비스를 사용하여 텍스트를 음성으로 변환하기

텍스트는 REST API를 통해 음성 서비스로 전송되어 IoT 장치에서 재생할 수 있는 오디오 파일로 변환됩니다. 음성을 요청할 때는 사용할 음성을 제공해야 하며, 다양한 음성을 사용하여 음성을 생성할 수 있습니다.

각 언어는 다양한 음성을 지원하며, 음성 서비스에 REST 요청을 보내 각 언어에 대해 지원되는 음성 목록을 얻을 수 있습니다.

### 작업 - 음성 가져오기

1. VS Code에서 `smart-timer` 프로젝트를 엽니다.

1. 언어에 대한 음성 목록을 요청하기 위해 `say` 함수 위에 다음 코드를 추가합니다:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    이 코드는 `get_voice`라는 함수를 정의하며, 이 함수는 음성 서비스를 사용하여 음성 목록을 가져옵니다. 그런 다음 사용 중인 언어와 일치하는 첫 번째 음성을 찾습니다.

    이 함수는 첫 번째 음성을 저장하고 음성 이름을 콘솔에 출력하도록 호출됩니다. 이 음성은 한 번 요청한 후 모든 텍스트를 음성으로 변환하는 호출에서 사용할 수 있습니다.

    > 💁 Microsoft Docs의 [언어 및 음성 지원 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech)에서 지원되는 음성의 전체 목록을 확인할 수 있습니다. 특정 음성을 사용하려면 이 함수를 제거하고 문서에서 제공된 음성 이름으로 음성을 하드코딩할 수 있습니다. 예를 들어:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### 작업 - 텍스트를 음성으로 변환하기

1. 이 아래에, 음성 서비스에서 가져올 오디오 형식을 정의하는 상수를 선언합니다. 오디오를 요청할 때 다양한 형식으로 요청할 수 있습니다.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    사용할 수 있는 형식은 하드웨어에 따라 다릅니다. 오디오를 재생할 때 `Invalid sample rate` 오류가 발생하면 다른 값으로 변경하십시오. 지원되는 값 목록은 Microsoft Docs의 [텍스트를 음성으로 변환 REST API 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs)에서 확인할 수 있습니다. `riff` 형식의 오디오를 사용해야 하며, 시도할 값은 `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm`, `riff-48khz-16bit-mono-pcm`입니다.

1. 이 아래에, 텍스트를 음성으로 변환하기 위해 음성 서비스 REST API를 사용하는 `get_speech`라는 함수를 선언합니다:

    ```python
    def get_speech(text):
    ```

1. `get_speech` 함수에서 호출할 URL과 전달할 헤더를 정의합니다:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    이 코드는 생성된 액세스 토큰을 사용하고, 콘텐츠를 SSML로 설정하며 필요한 오디오 형식을 정의합니다.

1. 이 아래에, REST API에 보낼 SSML을 정의합니다:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    이 SSML은 사용할 언어와 음성을 설정하고 변환할 텍스트를 포함합니다.

1. 마지막으로, 이 함수에 REST 요청을 수행하고 바이너리 오디오 데이터를 반환하는 코드를 추가합니다:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### 작업 - 오디오 재생하기

1. `get_speech` 함수 아래에, REST API 호출로 반환된 오디오를 재생하는 새 함수를 정의합니다:

    ```python
    def play_speech(speech):
    ```

1. 이 함수에 전달된 `speech`는 REST API에서 반환된 바이너리 오디오 데이터입니다. 다음 코드를 사용하여 이를 웨이브 파일로 열고 PyAudio를 사용하여 오디오를 재생합니다:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    이 코드는 PyAudio 스트림을 사용하며, 오디오 캡처와 동일합니다. 여기서 차이점은 스트림이 출력 스트림으로 설정되고, 오디오 데이터에서 읽은 데이터를 스트림으로 푸시한다는 점입니다.

    스트림 세부 사항(예: 샘플 속도)을 하드코딩하는 대신 오디오 데이터에서 읽습니다.

1. `say` 함수의 내용을 다음으로 교체합니다:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    이 코드는 텍스트를 바이너리 오디오 데이터로 변환하고 오디오를 재생합니다.

1. 앱을 실행하고 함수 앱도 실행 중인지 확인합니다. 타이머를 설정하면 타이머가 설정되었다는 음성 응답을 들을 수 있으며, 타이머가 완료되면 또 다른 음성 응답이 들립니다.

    `Invalid sample rate` 오류가 발생하면 위에서 설명한 대로 `playback_format`을 변경하십시오.

> 💁 이 코드는 [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) 폴더에서 찾을 수 있습니다.

😀 타이머 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.