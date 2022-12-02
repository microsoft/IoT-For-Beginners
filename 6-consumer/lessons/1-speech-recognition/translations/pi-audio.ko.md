# 오디오 캡처 - Raspberry Pi

이 단원에서는 Raspberry Pi로 오디오를 캡처하는 코드를 작성합니다. 오디오 캡처는 버튼으로 제어됩니다.

## 하드웨어

Raspberry Pi는 오디오 캡처를 조절하는 버튼을 필요로 합니다.

사용할 버튼은 Grove 버튼입니다. 이것은 신호를 켜고 끄는 디지털 센서입니다. 버튼이 눌리면 높은 값의 신호를 보내고 누르지 않으면 낮은 값의 신호를 보내도록 구성됩니다. 또는 눌렀을 때 낮은 값, 누르지 않았을 때 높은 값으로도 구성할 수 있습니다.

ReSpeaker 2-Mics Pi HAT을 마이크로 이용한다면 여기에 이미 장착이 되어있기 때문에 버튼을 연결할 필요가 없습니다. 다음 섹션으로 넘어가십시오.

### 버튼 연결

버튼은 Grove base hat에 연결될 수 있습니다.

#### 작업 - 버튼 연결

![A grove button](../../../../images/grove-button.png)

1. Grove 케이블의 한 쪽 끝을 버튼 모듈의 소켓에 삽입합니다. 한 방향으로만 이루어집니다.

1. Raspberry Pi의 전원을 끈 상태에서 Grove 케이블의 다른 쪽 끝을 Pi에 부착된 Grove Base hat의 **D5**가 적힌 디지털 소켓에 연결합니다. 이 소켓은 GPIO 핀 옆의 소켓 행에서 왼쪽 두 번째입니다.

![소켓 D5에 grove 버튼을 연결합니다.](../../../../images/pi-button.png)

## 오디오 캡처

Python 코드를 이용해서 마이크로부터 오디오를 캡처할 수 있습니다.

### 작업 - 오디오 캡처

1. Pi의 전원을 켜고 부팅될 때까지 기다립니다.

1. Pi에서 직접 VS Code를 실행하거나 원격 SSH 확장을 통해 연결합니다.

1. PyAudio Pip 패키지에는 음성을 녹음하고 재생하는 함수들이 있습니다. 이 패키지는 먼저 설치해야 하는 일부 오디오 라이브러리에 따라 다릅니다. 터미널에서 아래의 명령을 실행하여 이를 설치합니다.

   ```sh
   sudo apt update
   sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes
   ```

1. PyAudio Pip 패키지를 설치합니다.

   ```sh
   pip3 install pyaudio
   ```

1. `smart-timer` 이름의 새 폴더를 생성하고 새로운 파일 `app.py`를 이 폴더에 추가합니다.

1. 이 파일의 상단에 다음의 import문들을 추가합니다.

   ```python
   import io
   import pyaudio
   import time
   import wave

   from grove.factory import Factory
   ```

   이것은 `pyaudio` 모듈, 웨이브 파일을 처리하는 일부 표준 Python 모듈과 버튼 클래스를 생성하기 위해 `Factory`를 import 하는 `grove.factory` 모듈을 가져옵니다.

1. 아래와 같이 코드를 추가하여 Grove 버튼을 추가합니다.

   ReSpeaker 2-Mics Pi HAT를 사용한다면, 다음 코드를 사용하십시오:

   ```python
   # The button on the ReSpeaker 2-Mics Pi HAT
   button = Factory.getButton("GPIO-LOW", 17)
   ```

   이렇게 하면 ReSpeaker 2-Mics Pi HAT의 버튼이 연결된 포트 **D17**에 버튼이 생성됩니다. 이 버튼은 누르면 낮은 신호를 보내도록 설정되었습니다.

   ReSpeaker 2-Mics Pi HAT를 사용하지 않고 Grove 버튼을 base hat에 연결하는 데 사용하는 경우 이 코드를 사용합니다.

   ```python
   button = Factory.getButton("GPIO-HIGH", 5)
   ```

   이는 **D5** 포트에 눌렀을 때 높은 신호를 전송하는 버튼을 생성합니다.

1. 아래와 같이 오디오를 처리할 PyAudio 클래스의 인스턴스를 생성합니다.

   ```python
   audio = pyaudio.PyAudio()
   ```

1. 마이크와 스피커의 하드웨어 카드 번호를 선언합니다. 이는 이 수업의 앞부분에서 `arecord -l` 와 `aplay -l` 를 실행하여 찾은 카드 번호입니다.

   ```python
   microphone_card_number = <microphone card number>
   speaker_card_number = <speaker card number>
   ```

   `<microphone card number>` 부분을 마이크 카드 번호로 수정합니다.

   `<speaker card number>` 를 `alsa.conf` 파일에서 설정한 숫자와 동일한 스피커 카드 번호로 바꿉니다.

1. 아래와 같이 오디오를 캡처하고 다시 재생하는 샘플 속도를 선언합니다. 실제로 사용하는 하드웨어에 따라 변경할 수 있습니다.

   ```python
   rate = 48000 #48KHz
   ```

   이 코드를 실행하면서 샘플 속도 에러가 발생한다면, 이 값을 `44100` 또는 `16000`로 변경하십시오. 값을 높일 수록 더 좋은 음질을 얻을 수 있습니다.

1. 아래와 같이 `capture_audio`의 이름을 가진 새 함수를 생성합니다. 이 함수는 마이크에서 오디오를 캡처할 때 호출됩니다:

   ```python
   def capture_audio():
   ```

1. 이 함수 안에 다음과 같은 오디오를 캡처하는 부분을 추가합니다:

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

   이 코드는 PyAudio 객체를 사용해 오디오 입력 스트림을 엽니다. 이 스트림은 16KHz에서 마이크의 오디오를 캡처하여 4096바이트 크기의 버퍼에서 캡처합니다.

   그 다음 코드는 버튼이 눌린 동안 4096 바이트의 버퍼를 배열로 읽어들입니다.

   > 💁 `open` 메서드에 전달된 옵션들에 대해서는 [PyAudio documentation](https://people.csail.mit.edu/hubert/pyaudio/docs/)에서 확인할 수 있습니다.

   버튼을 놓으면 스트림은 중지되고 close합니다.

1. 이 함수의 끝에 다음을 추가합니다:

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

   이 코드는 바이너리 버퍼를 생성하고 캡처한 오디오를 [WAV file](https://wikipedia.org/wiki/WAV)로 작성합니다. 이는 압축되지 않은 오디오를 파일로 저장하는 표준적인 방법입니다. 이 버퍼는 이후 리턴합니다.

1. 오디오 버퍼를 재생하기 위해 다음과 같은 `play_audio` 함수를 추가합니다.

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

   이 함수는 이번에는 출력을 위해 오디오를 재생하는 다른 오디오 스트림을 엽니다. 입력 스트림과 같은 방식으로 세팅합니다. 그런 다음 버퍼가 웨이브 파일로 열리고 4096바이트 단위로 출력 스트림에 기록되어 오디오를 재생합니다. 이후 스트림을 close합니다.

1. `capture_audio` 함수에 버튼을 누를 때까지 loop를 돌도록 아래의 코드를 추가합니다. 버튼이 한 번 눌리면 오디오가 캡처되고 재생됩니다.

   ```python
   while True:
      while not button.is_pressed():
          time.sleep(.1)

      buffer = capture_audio()
      play_audio(buffer)
   ```

1. 코드를 실행합니다. 버튼을 누르고 마이크에 대고 말합니다. 끝나면 버튼에서 손을 떼고 녹음된 내용을 듣습니다.

   PyAudio 인스턴스가 생성될 때 ALSA 오류가 발생할 수 있습니다. 이는 가지고 있지 않은 오디오 장치에 대한 Pi의 구성 때문입니다. 이러한 오류는 무시해도 됩니다.

   ```output
   pi@raspberrypi:~/smart-timer $ python3 app.py
   ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
   ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
   ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
   ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
   ```

   만약 다음의 오류가 발생하는 경우:

   ```output
   OSError: [Errno -9997] Invalid sample rate
   ```

   44100 또는 16000으로 `rate` 값을 변경합니다.

> 💁 이 코드는 [code-record/pi](../code-record/pi) 폴더에서 찾을 수 있습니다.

😀 오디오 녹음 프로그램이 성공적으로 끝났습니다!
