<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-25T00:31:21+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "ko"
}
-->
# 라즈베리 파이 - 마이크와 스피커 설정하기

이 수업의 이 부분에서는 라즈베리 파이에 마이크와 스피커를 추가합니다.

## 하드웨어

라즈베리 파이에는 마이크가 필요합니다.

라즈베리 파이에는 내장 마이크가 없으므로 외부 마이크를 추가해야 합니다. 이를 위한 여러 방법이 있습니다:

* USB 마이크
* USB 헤드셋
* USB 일체형 스피커폰
* USB 오디오 어댑터와 3.5mm 잭이 있는 마이크
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 블루투스 마이크는 라즈베리 파이에서 모두 지원되지 않을 수 있습니다. 따라서 블루투스 마이크나 헤드셋을 사용하는 경우 페어링 또는 오디오 캡처에 문제가 발생할 수 있습니다.

라즈베리 파이에는 3.5mm 헤드폰 잭이 내장되어 있습니다. 이를 사용하여 헤드폰, 헤드셋 또는 스피커를 연결할 수 있습니다. 또한 다음 방법으로 스피커를 추가할 수 있습니다:

* 모니터나 TV를 통한 HDMI 오디오
* USB 스피커
* USB 헤드셋
* USB 일체형 스피커폰
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)에 스피커를 연결 (3.5mm 잭 또는 JST 포트를 통해)

## 마이크와 스피커 연결 및 설정

마이크와 스피커를 연결하고 설정해야 합니다.

### 작업 - 마이크 연결 및 설정

1. 적절한 방법으로 마이크를 연결합니다. 예를 들어, USB 포트를 통해 연결합니다.

1. ReSpeaker 2-Mics Pi HAT을 사용하는 경우, Grove 베이스 HAT을 제거한 후 ReSpeaker HAT을 그 자리에 장착합니다.

    ![ReSpeaker HAT이 장착된 라즈베리 파이](../../../../../translated_images/ko/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    이 수업의 나중 단계에서 Grove 버튼이 필요하지만, 이 HAT에는 버튼이 내장되어 있으므로 Grove 베이스 HAT은 필요하지 않습니다.

    HAT을 장착한 후 드라이버를 설치해야 합니다. 드라이버 설치에 대한 지침은 [Seeed 시작 가이드](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started)를 참조하세요.

    > ⚠️ 지침에서는 `git`을 사용하여 리포지토리를 클론합니다. 라즈베리 파이에 `git`이 설치되어 있지 않다면, 다음 명령어를 실행하여 설치할 수 있습니다:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. 터미널에서 다음 명령어를 실행하여 연결된 마이크에 대한 정보를 확인합니다. 이 작업은 라즈베리 파이에서 직접 실행하거나 VS Code와 원격 SSH 세션을 통해 실행할 수 있습니다:

    ```sh
    arecord -l
    ```

    연결된 마이크 목록이 표시됩니다. 예시는 다음과 같습니다:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    마이크가 하나만 연결되어 있다면, 하나의 항목만 표시됩니다. 리눅스에서 마이크 설정은 까다로울 수 있으므로, 하나의 마이크만 사용하고 다른 마이크는 분리하는 것이 가장 간단합니다.

    카드 번호를 기록해 두세요. 나중에 필요합니다. 위 출력 예시에서는 카드 번호가 1입니다.

### 작업 - 스피커 연결 및 설정

1. 적절한 방법으로 스피커를 연결합니다.

1. 터미널에서 다음 명령어를 실행하여 연결된 스피커에 대한 정보를 확인합니다. 이 작업은 라즈베리 파이에서 직접 실행하거나 VS Code와 원격 SSH 세션을 통해 실행할 수 있습니다:

    ```sh
    aplay -l
    ```

    연결된 스피커 목록이 표시됩니다. 예시는 다음과 같습니다:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    항상 `card 0: Headphones`가 표시됩니다. 이는 내장 헤드폰 잭입니다. 추가 스피커를 연결한 경우, 예를 들어 USB 스피커, 해당 항목도 목록에 표시됩니다.

1. 내장 헤드폰 잭에 연결된 스피커나 헤드폰이 아닌 추가 스피커를 사용하는 경우, 이를 기본값으로 설정해야 합니다. 이를 위해 다음 명령어를 실행합니다:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    이 명령어는 `nano`라는 터미널 기반 텍스트 편집기에서 구성 파일을 엽니다. 키보드의 화살표 키를 사용하여 아래로 스크롤하여 다음 줄을 찾습니다:

    ```output
    defaults.pcm.card 0
    ```

    값을 `0`에서 `aplay -l` 명령어 출력에서 확인한 카드 번호로 변경합니다. 예를 들어, 위 출력에서 `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`라는 두 번째 사운드 카드가 있습니다. 카드 1을 사용하려면 다음과 같이 줄을 업데이트합니다:

    ```output
    defaults.pcm.card 1
    ```

    적절한 카드 번호로 값을 설정합니다. 화살표 키를 사용하여 해당 번호로 이동한 후, 텍스트 파일을 편집할 때처럼 기존 번호를 삭제하고 새 번호를 입력합니다.

1. 변경 사항을 저장하고 파일을 닫으려면 `Ctrl+x`를 누릅니다. 저장 여부를 묻는 메시지가 나타나면 `y`를 누르고, 파일 이름을 선택하려면 `return`을 누릅니다.

### 작업 - 마이크와 스피커 테스트

1. 다음 명령어를 실행하여 마이크를 통해 5초 동안 오디오를 녹음합니다:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    이 명령어가 실행되는 동안 마이크에 소리를 내보세요. 예를 들어, 말하기, 노래 부르기, 비트박스, 악기 연주 등 원하는 것을 해보세요.

1. 5초 후 녹음이 중지됩니다. 다음 명령어를 실행하여 오디오를 재생합니다:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    스피커를 통해 오디오가 재생되는 것을 들을 수 있습니다. 필요에 따라 스피커의 출력 볼륨을 조정하세요.

1. 내장 마이크 포트의 볼륨을 조정하거나 마이크의 게인을 조정해야 하는 경우, `alsamixer` 유틸리티를 사용할 수 있습니다. 이 유틸리티에 대한 자세한 내용은 [Linux alsamixer 매뉴얼 페이지](https://linux.die.net/man/1/alsamixer)를 참조하세요.

1. 오디오 재생 중 오류가 발생하면, `alsa.conf` 파일에서 `defaults.pcm.card`로 설정한 카드를 확인하세요.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.