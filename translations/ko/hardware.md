<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-24T21:03:29+00:00",
  "source_file": "hardware.md",
  "language_code": "ko"
}
-->
# 하드웨어

IoT에서 **T**는 **사물(Things)**을 의미하며, 우리 주변 환경과 상호작용하는 장치를 나타냅니다. 각 프로젝트는 학생과 취미로 즐기는 사람들이 사용할 수 있는 실제 하드웨어를 기반으로 합니다. 개인의 선호도, 프로그래밍 언어 지식 또는 선호도, 학습 목표 및 가용성에 따라 사용할 수 있는 IoT 하드웨어를 두 가지로 나누었습니다. 하드웨어에 접근할 수 없거나 구매를 결정하기 전에 더 배우고 싶은 사람들을 위해 '가상 하드웨어' 버전도 제공했습니다.

> 💁 과제를 완료하기 위해 IoT 하드웨어를 구매할 필요는 없습니다. 모든 작업을 가상 IoT 하드웨어를 사용하여 수행할 수 있습니다.

물리적 하드웨어 선택지는 Arduino와 Raspberry Pi입니다. 각 플랫폼은 고유한 장점과 단점이 있으며, 초기 수업 중 하나에서 모두 다룹니다. 아직 하드웨어 플랫폼을 결정하지 않았다면, [첫 번째 프로젝트의 두 번째 수업](./1-getting-started/lessons/2-deeper-dive/README.md)을 검토하여 어떤 하드웨어 플랫폼을 배우고 싶은지 결정할 수 있습니다.

특정 하드웨어는 수업과 과제의 복잡성을 줄이기 위해 선택되었습니다. 다른 하드웨어도 작동할 수 있지만, 추가 하드웨어 없이는 모든 과제가 지원된다고 보장할 수 없습니다. 예를 들어, 많은 Arduino 장치에는 클라우드에 연결하는 데 필요한 WiFi가 없으며, Wio 터미널은 WiFi가 내장되어 있기 때문에 선택되었습니다.

또한 흙이나 화분 식물, 과일 또는 채소와 같은 몇 가지 비기술적인 아이템도 필요합니다.

## 키트 구매하기

![Seeed Studios 로고](../../translated_images/ko/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios는 모든 하드웨어를 쉽게 구매할 수 있는 키트로 제공해 주었습니다:

### Arduino - Wio 터미널

**[Seeed와 Microsoft가 함께하는 초보자를 위한 IoT - Wio 터미널 스타터 키트](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio 터미널 하드웨어 키트](../../translated_images/ko/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[Seeed와 Microsoft가 함께하는 초보자를 위한 IoT - Raspberry Pi 4 스타터 키트](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi 터미널 하드웨어 키트](../../translated_images/ko/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Arduino의 모든 장치 코드는 C++로 작성됩니다. 모든 과제를 완료하려면 다음이 필요합니다:

### Arduino 하드웨어

* [Wio 터미널](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *선택 사항* - USB-C 케이블 또는 USB-A to USB-C 어댑터. Wio 터미널에는 USB-C 포트가 있으며 USB-C to USB-A 케이블이 포함되어 있습니다. PC나 Mac에 USB-C 포트만 있는 경우 USB-C 케이블 또는 USB-A to USB-C 어댑터가 필요합니다.

### Arduino 전용 센서 및 액추에이터

이들은 Wio 터미널 Arduino 장치에서 사용되며 Raspberry Pi에서는 관련이 없습니다.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [브레드보드 점퍼 와이어](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* 헤드폰 또는 3.5mm 잭이 있는 다른 스피커, 또는 JST 스피커:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD 카드 16GB 이하, 컴퓨터에 SD 카드를 사용할 수 있는 커넥터가 없는 경우 커넥터 필요. **참고** - Wio 터미널은 최대 16GB의 SD 카드만 지원하며, 더 높은 용량은 지원하지 않습니다.

## Raspberry Pi

Raspberry Pi의 모든 장치 코드는 Python으로 작성됩니다. 모든 과제를 완료하려면 다음이 필요합니다:

### Raspberry Pi 하드웨어

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B 이상의 버전은 이 수업의 과제에서 작동합니다. Pi에서 VS Code를 직접 실행하려면 2GB 이상의 RAM이 있는 Pi 4가 필요합니다. Pi에 원격으로 접근하려면 Pi 2B 이상의 버전이 작동합니다.
* microSD 카드 (Raspberry Pi 키트에는 microSD 카드가 포함될 수 있음), 컴퓨터에 SD 카드를 사용할 수 있는 커넥터가 없는 경우 커넥터 필요.
* USB 전원 공급 장치 (Raspberry Pi 4 키트에는 전원 공급 장치가 포함될 수 있음). Raspberry Pi 4를 사용하는 경우 USB-C 전원 공급 장치가 필요하며, 이전 장치는 micro-USB 전원 공급 장치가 필요합니다.

### Raspberry Pi 전용 센서 및 액추에이터

이들은 Raspberry Pi에서 사용되며 Arduino 장치에서는 관련이 없습니다.

* [Grove Pi 베이스 HAT](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi 카메라 모듈](https://www.raspberrypi.org/products/camera-module-v2/)
* 마이크와 스피커:

  다음 중 하나를 사용 (또는 동등한 장치):
  * USB 마이크와 USB 스피커, 또는 3.5mm 잭 케이블이 있는 스피커, 또는 Raspberry Pi가 스피커가 있는 모니터나 TV에 연결된 경우 HDMI 오디오 출력 사용
  * 내장 마이크가 있는 USB 헤드셋
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)와 함께
    * 헤드폰 또는 3.5mm 잭이 있는 다른 스피커, 또는 JST 스피커:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB 스피커폰](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove 광 센서](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove 버튼](https://www.seeedstudio.com/Grove-Button.html)

## 센서 및 액추에이터

필요한 대부분의 센서와 액추에이터는 Arduino와 Raspberry Pi 학습 경로에서 모두 사용됩니다:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove 습도 및 온도 센서](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove 정전식 토양 수분 센서](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove 릴레이](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove 비행 거리 센서](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## 선택적 하드웨어

자동 급수에 대한 수업은 릴레이를 사용하여 작동합니다. 선택적으로, 아래에 나열된 하드웨어를 사용하여 USB로 전원을 공급받는 물 펌프에 이 릴레이를 연결할 수 있습니다.

* [6V 물 펌프](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB 터미널](https://www.adafruit.com/product/3628)
* 실리콘 파이프
* 빨간색 및 검은색 와이어
* 작은 일자 드라이버

## 가상 하드웨어

가상 하드웨어 경로는 Python으로 구현된 센서와 액추에이터의 시뮬레이터를 제공합니다. 하드웨어 가용성에 따라 Mac, PC와 같은 일반 개발 장치에서 실행하거나 Raspberry Pi에서 실행하여 없는 하드웨어만 시뮬레이션할 수 있습니다. 예를 들어, Raspberry Pi 카메라는 있지만 Grove 센서가 없는 경우, Pi에서 가상 장치 코드를 실행하여 Grove 센서를 시뮬레이션하고 실제 카메라를 사용할 수 있습니다.

가상 하드웨어는 [CounterFit 프로젝트](https://github.com/CounterFit-IoT/CounterFit)를 사용할 것입니다.

이 수업을 완료하려면 웹캠, 마이크 및 스피커 또는 헤드폰과 같은 오디오 출력이 필요합니다. 이들은 내장형 또는 외부형일 수 있으며, 운영 체제에서 작동하도록 구성되어 모든 애플리케이션에서 사용할 수 있어야 합니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.