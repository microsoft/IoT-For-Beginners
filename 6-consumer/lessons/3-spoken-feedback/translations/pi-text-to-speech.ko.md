# 텍스트 음성 변환 - Raspberry Pi

이 단원에서는 음성 서비스를 사용하여 텍스트를 음성으로 변환하는 코드를 작성합니다.

## 음성 서비스를 사용하여 텍스트를 음성으로 변환 해봅시다.

텍스트는 REST API를 사용하여 음성 서비스로 전송되어 IoT 장치에서 재생할 수 있는 오디오 파일로 음성을 얻을 수 있습니다. 음성을 요청할 때 다양한 음성을 사용하여 변환된 음성을 생성할 수 있으므로 사용할 voice를 제공해야 합니다. 

각 언어는 다양한 voice를 지원하며, 음성 서비스에 대해 REST를 요청하여 각 언어에 대해 지원되는 voice 목록을 얻을 수 있습니다.

### 작업 - voice를 얻어 봅시다.

1. VS Code에서 `smart-timer` 프로젝트를 열어주세요.

1. 언어에 대한 voice 목록을 요청하려면 `say`함수 뒤에 아래 코드를 추가하십시오.

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

    이 코드는 음성 서비스를 사용하여 voice 리스트를 가져오는 `get_voice`라는 함수를 정의합니다. 이후 사용중인 언어와 일치하는 첫 번째 voice를 찾습니다.
    
    이후 이 기능을 호출하여 첫 번째 voice를 저장하면 음성 이름이 console에 출력됩니다. 이 voice는 한 번 요청할 수 있으며 텍스트를 음성으로 변환하기 위해 모든 호출에 사용되는 값입니다.
    
    > 💁 지원되는 voice의 전체 목록은 [Microsoft Docs 언어 및 음성 지원 설명서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech)에서 확인할 수 있습니다. 특정 voice를 사용하려면 이 기능을 제거하고 설명서에서 voice를 해당 voice의 명칭으로 하드코딩 할 수 있습니다. 
    > 예시 : 
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### 작업 - 텍스트를 음성으로 변환

1. 아래에서 음성 서비스에서 검색할 오디오 형식에 대한 상수를 정의합니다. 오디오를 요청할 때 다양한 형식으로 요청할 수 있습니다.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    하드웨어에 따라 사용할 수 있는 형식이 다릅니다. 오디오를 재생할 때 `Invalid sample rate`오류가 발생하면 이 값을 다른 값으로 변경하면 됩니다. 지원되는 목록은 [Microsoft Docs의 Text to speech REST API 설명서](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) 에서 확인할 수 있습니다. `riff` 형식의 오디오를 사용해야 하며, 시도할 값은 `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` 그리고 `riff-48khz-16bit-mono-pcm`입니다.
    
1.  아래 코드를 통해 음성 서비스 REST API를 사용하여 텍스트를 음성으로 변환하는 `get_speech`함수를 선언합니다.

    ```python
    def get_speech(text):
    ```

1. `get_speech` 함수에서 호출할 URL과 전달할 헤더를 정의합니다.

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    생성된 액세스 토큰을 사용하도록 헤더를 설정하고 콘텐츠를 SSML로 설정하며 필요한 오디오 형식을 정의합니다.
    
1. 아래 코드를 통해 REST API로 보낼 SSML을 정의합니다.

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    이 SSML은 변환할 텍스트와 함께 사용할 언어와 voice를 설정합니다.

1. 마지막으로 REST를 요청하고 이진 오디오 데이터를 반환하는 코드를 이 함수에 추가합니다.

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### 작업 - 오디오를 재생해봅시다

1. `get_speech` 함수 아래에 REST API 호출에 의해 반환된 오디오를 재생하는 새 함수를 정의합니다.

    ```python
    def play_speech(speech):
    ```

1. 이 함수에 전달되는 `speech`는 REST API에서 반환되는 이진 오디오 데이터입니다. 다음 코드를 사용하여 이를 파형 파일로 열고 PyAudio로 전달하여 오디오를 재생합니다
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

    이 코드는 오디오를 캡처하는 것과 동일한 PyAudio 스트림을 사용합니다. 여기서 차이점은 오디오 데이터에서 데이터가 읽혀지고 출력 스트림으로 설정 된 스트림으로 푸시된다는 것입니다.
    
    샘플링 정도와 같은 스트림 세부 사항을 하드 코딩하는 대신 오디오 데이터로부터 읽다.

1. `say` 함수의 내용을 다음과 같이 바꿉니다.

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    이 코드는 텍스트를 이진 오디오 데이터로 음성으로 변환하고 오디오를 재생합니다.

1. 앱을 실행하고 function 앱도 실행 중인지 확인합니다. 타이머를 설정하면 타이머가 설정되었다는 음성 응답이 들리고, 타이머의 시간이 완료되면 다른 음성 응답이 들립니다.
    `Invalid sample rate` 오류가 발생하면 위에서 설명한 대로 `playback_format`을 변경하십시오.

> 💁  [code-spoken-response/pi](code-spoken-response/pi) 폴더에서 코드를 확인할 수 있습니다.

😀 타이머를 만들었어요! 야호!
