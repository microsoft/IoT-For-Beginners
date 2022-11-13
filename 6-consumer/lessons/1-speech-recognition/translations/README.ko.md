# IoT 장치로 음성 인식

![A sketchnote overview of this lesson](../../../../sketchnotes/lesson-21.jpg)

> [Nitya Narasimhan](https://github.com/nitya)의 스케치 노트. 크게 보려면 클릭하세요.

이 비디오는 이 수업에서 다룰 주제인 Azure 음성 서비스에 대한 개요를 제공합니다.

[![Microsoft Azure YouTube 채널의 Cognitive Services Speech 리소스를 사용하는 방법](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 상단의 이미지를 클릭하여 비디오를 시청합니다.

## 수업 전 퀴즈

[수업 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## 개요

'Alexa, 타이머 12분으로 맞춰줘'

'Alexa, 타이머 상태'

'Alexa, 스팀 브로콜리 타이머 8분으로 맞춰줘'

스마트 기기는 점점 더 보편화되고 있습니다. HomePods이나 Echos, Google Homes와 같은 스마트 스피커 뿐만 아니라 휴대폰, 워치, 조명 장치 및 온도 조절 장치에도 내장되어 있습니다.

> 💁 I have at least 19 devices in my home that have voice assistants, and that's just the ones I know about!
> 💁 저희집에는 최소 19개의 음성 비서가 있는 장치가 있습니다. 제가 아는 것만 해도요!

음성 제어는 움직임이 제한된 사람들이 장치와 상호 작용할 수 있도록 하여 접근성을 높입니다. 팔이 없이 태어난 선천적인 장애든, 팔이 부러지는 것과 같이 일시적인 장애든, 장바구니나 아이의 손을 잡느라 손이 없든간에 우리의 손이 아닌 목소리로 집을 제어할 수 있다는 것은 접근의 세상을 열어줍니다. 아이의 변화와 다루기 힘든 유아를 돌보는 동안 'Hey Siri, 차고 문 좀 닫아줘'를 외치는 것은 작지만 효과적인 삶의 개선이 될 수 있습니다.

음성 비서의 가장 인기있는 용도 중 하나는 특히나 주방 타이머 같은 타이머 설정입니다. 목소리만으로 여러개의 타이머를 설정할 수 있는 것은 주방에서 큰 도움이 됩니다. 물리적 타이머를 설정하기 위해 반죽을 하거나 수프를 저어주거나 만두 속을 채우던 손을 멈출 필요가 없습니다.

이 수업에서는 음성 인식을 IoT에 구축하는 것을 배웁니다. 센서로서의 마이크, IoT 기기에 부착된 마이크로 부터 어떻게 오디오를 캡처하는지, 어떻게 인공지능이 들은 내용을 텍스트로 변환하는 지에 대해 배웁니다. 이 프로젝트의 나머지 부분에서 여러 언어로 음성을 사용하여 타이머를 설정할 수 있는 스마트 주방 타이머를 구축할 예정입니다.

이 강의에서 다룰 내용은 다음과 같습니다:

- [마이크](#마이크)
- [IoT 장치에서 오디오 캡처하기](#IoT-장치에서-오디오-캡처하기)
- [음성 대 텍스트](#음성-대-텍스트)
- [음성을 텍스트로 변환](#음성을-텍스트로-변환)

## IoT 장치에서 오디오 캡처하기

IoT 장치를 마이크와 연결하여 텍스트로 변환할 준비가 된 오디오를 캡처할 수 있습니다. 스피커를 연결하여 오디오 출력을 할 수도 있습니다. 이후 강의에서 이것은 오디오 피드백을 제공하는 데 사용되지만 마이크를 테스트 하기 위해 지금 스피커를 설정하는 것이 유용합니다.

### 작업 - 마이크 및 스피커 구성

관련 가이드를 통해 IoT 장치용 마이크와 스피커를 구성하십시오:

- [Arduino - Wio Terminal](../wio-terminal-microphone.md)
- [단일 보드 컴퓨터 - Raspberry Pi](pi-microphone.ko.md)
- [단일 보드 컴퓨터 - 가상 장치](../virtual-device-microphone.md)

### 작업 - 오디오 캡처

관련 가이드를 통해 IoT 장치에서 오디오를 캡처합니다:

- [Arduino - Wio Terminal](../wio-terminal-audio.md)
- [단일 보드 컴퓨터 - Raspberry Pi](pi-audio.ko.md)
- [단일 보드 컴퓨터 - 가상 장치](../virtual-device-audio.md)

## 🚀 도전

음성 인식은 오랜 시간동안 사용되어 왔고, 지속적으로 개선되고 있습니다. 현재의 역량을 연구하고 기계가 작성한 필사본이 인간과 비교하여 얼마나 정확한 지를 포함하여 시간이 지남에 따라 어떻게 발전했는지 비교하십시오.

음성 인식의 미래는 어떻게 될 것이라고 생각합니까?

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## 복습 & 독학

- 다른 마이크 타입과 그들이 어떻게 동작하는 지에 대해 [Musician's HQ의 다이나믹 마이크와 콘덴서 마이크의 차이점](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/)에서 읽어보세요.
- [Microsoft Docs의 음성 서비스 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn)에서 Cognitive Sevices의 음성 서비스에 대해 자세히 읽어보세요.
- [Microsoft Docs의 키워드 인식 설명서](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn)에서 키워드 지정에 대해 읽어보세요.

## 과제

[](assignment.md)
