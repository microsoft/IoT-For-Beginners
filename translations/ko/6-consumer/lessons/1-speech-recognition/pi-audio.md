<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-25T00:18:06+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "ko"
}
-->
# 오디오 캡처 - Raspberry Pi

이 수업의 이 부분에서는 Raspberry Pi에서 오디오를 캡처하는 코드를 작성합니다. 오디오 캡처는 버튼으로 제어됩니다.

## 하드웨어

Raspberry Pi는 오디오 캡처를 제어하기 위해 버튼이 필요합니다.

사용할 버튼은 Grove 버튼입니다. 이 버튼은 신호를 켜거나 끄는 디지털 센서입니다. 버튼을 눌렀을 때 높은 신호를 보내고, 누르지 않았을 때 낮은 신호를 보내도록 설정할 수 있으며, 반대로 눌렀을 때 낮은 신호를 보내고 누르지 않았을 때 높은 신호를 보내도록 설정할 수도 있습니다.

ReSpeaker 2-Mics Pi HAT을 마이크로폰으로 사용하는 경우, 이 HAT에 이미 버튼이 장착되어 있으므로 버튼을 연결할 필요가 없습니다. 다음 섹션으로 넘어가세요.

### 버튼 연결하기

버튼은 Grove 베이스 HAT에 연결할 수 있습니다.

#### 작업 - 버튼 연결하기

![Grove 버튼](../../../../../translated_images/ko/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Grove 케이블의 한쪽 끝을 버튼 모듈의 소켓에 삽입하세요. 케이블은 한 방향으로만 들어갑니다.

1. Raspberry Pi의 전원을 끈 상태에서, Grove 케이블의 다른 쪽 끝을 Pi에 부착된 Grove 베이스 HAT의 **D5**로 표시된 디지털 소켓에 연결하세요. 이 소켓은 GPIO 핀 옆에 있는 소켓 줄에서 왼쪽에서 두 번째에 위치합니다.

![D5 소켓에 연결된 Grove 버튼](../../../../../translated_images/ko/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## 오디오 캡처

Python 코드를 사용하여 마이크로폰에서 오디오를 캡처할 수 있습니다.

### 작업 - 오디오 캡처하기

1. Pi의 전원을 켜고 부팅이 완료될 때까지 기다리세요.

1. VS Code를 실행하세요. Pi에서 직접 실행하거나 Remote SSH 확장을 통해 연결할 수 있습니다.

1. PyAudio Pip 패키지는 오디오를 녹음하고 재생하는 기능을 제공합니다. 이 패키지는 몇 가지 오디오 라이브러리에 의존하므로, 먼저 다음 명령어를 터미널에서 실행하여 설치하세요:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pip 패키지를 설치하세요.

    ```sh
    pip3 install pyaudio
    ```

1. `smart-timer`라는 새 폴더를 만들고, 이 폴더에 `app.py`라는 파일을 추가하세요.

1. 이 파일의 맨 위에 다음 임포트를 추가하세요:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    이는 `pyaudio` 모듈, 웨이브 파일을 처리하기 위한 표준 Python 모듈, 그리고 버튼 클래스를 생성하기 위해 `grove.factory` 모듈을 임포트합니다.

1. 그 아래에 Grove 버튼을 생성하는 코드를 추가하세요.

    ReSpeaker 2-Mics Pi HAT을 사용하는 경우, 다음 코드를 사용하세요:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    이는 ReSpeaker 2-Mics Pi HAT에 연결된 버튼이 있는 **D17** 포트에 버튼을 생성합니다. 이 버튼은 눌렸을 때 낮은 신호를 보내도록 설정됩니다.

    ReSpeaker 2-Mics Pi HAT을 사용하지 않고, Grove 베이스 HAT에 연결된 Grove 버튼을 사용하는 경우, 다음 코드를 사용하세요.

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    이는 **D5** 포트에 버튼을 생성하며, 이 버튼은 눌렸을 때 높은 신호를 보내도록 설정됩니다.

1. 그 아래에 오디오를 처리하기 위한 PyAudio 클래스의 인스턴스를 생성하세요:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. 마이크와 스피커의 하드웨어 카드 번호를 선언하세요. 이는 이 수업의 이전 단계에서 `arecord -l` 및 `aplay -l` 명령어를 실행하여 찾은 카드 번호입니다.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>`를 마이크 카드 번호로 바꾸세요.

    `<speaker card number>`를 스피커 카드 번호로 바꾸세요. 이는 `alsa.conf` 파일에서 설정한 번호와 동일합니다.

1. 그 아래에 오디오 캡처 및 재생에 사용할 샘플 레이트를 선언하세요. 사용하는 하드웨어에 따라 이 값을 변경해야 할 수도 있습니다.

    ```python
    rate = 48000 #48KHz
    ```

    나중에 이 코드를 실행할 때 샘플 레이트 오류가 발생하면, 이 값을 `44100` 또는 `16000`으로 변경하세요. 값이 높을수록 음질이 좋아집니다.

1. 그 아래에 `capture_audio`라는 새 함수를 생성하세요. 이 함수는 마이크로폰에서 오디오를 캡처하는 데 사용됩니다:

    ```python
    def capture_audio():
    ```

1. 이 함수 내부에 다음 코드를 추가하여 오디오를 캡처하세요:

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    이 코드는 PyAudio 객체를 사용하여 오디오 입력 스트림을 엽니다. 이 스트림은 마이크로폰에서 16KHz로 오디오를 캡처하며, 4096 바이트 크기의 버퍼로 캡처합니다.

    코드는 Grove 버튼이 눌려 있는 동안 루프를 돌며, 매번 4096 바이트 버퍼를 배열에 읽어옵니다.

    > 💁 `open` 메서드에 전달된 옵션에 대한 자세한 내용은 [PyAudio 문서](https://people.csail.mit.edu/hubert/pyaudio/docs/)를 참조하세요.

    버튼이 해제되면 스트림이 중지되고 닫힙니다.

1. 이 함수의 끝에 다음 코드를 추가하세요:

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    이 코드는 바이너리 버퍼를 생성하고, 캡처된 모든 오디오를 [WAV 파일](https://wikipedia.org/wiki/WAV)로 작성합니다. WAV 파일은 비압축 오디오를 파일로 저장하는 표준 방식입니다. 그런 다음 이 버퍼가 반환됩니다.

1. 오디오 버퍼를 재생하기 위한 `play_audio` 함수를 추가하세요:

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    이 함수는 오디오 출력을 위한 또 다른 오디오 스트림을 엽니다. 이 스트림은 입력 스트림과 동일한 설정을 사용합니다. 그런 다음 버퍼를 웨이브 파일로 열고, 4096 바이트 청크로 출력 스트림에 작성하여 오디오를 재생합니다. 스트림은 이후 닫힙니다.

1. `capture_audio` 함수 아래에 다음 코드를 추가하여 버튼이 눌릴 때까지 루프를 실행하세요. 버튼이 눌리면 오디오를 캡처한 후 재생합니다.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. 코드를 실행하세요. 버튼을 누르고 마이크에 대고 말하세요. 버튼을 놓으면 녹음된 소리를 들을 수 있습니다.

    PyAudio 인스턴스가 생성될 때 ALSA 오류가 발생할 수 있습니다. 이는 Pi의 오디오 장치 설정 때문이며, 무시해도 됩니다.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    다음과 같은 오류가 발생하면:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    `rate`를 `44100` 또는 `16000`으로 변경하세요.

> 💁 이 코드는 [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) 폴더에서 확인할 수 있습니다.

😀 오디오 녹음 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.