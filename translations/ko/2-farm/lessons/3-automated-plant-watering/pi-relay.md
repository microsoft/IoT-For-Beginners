<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-24T22:18:34+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "ko"
}
-->
# 릴레이 제어하기 - Raspberry Pi

이 수업의 이번 부분에서는 토양 수분 센서에 더해 Raspberry Pi에 릴레이를 추가하고, 토양 수분 수준에 따라 이를 제어하는 방법을 배웁니다.

## 하드웨어

Raspberry Pi에는 릴레이가 필요합니다.

사용할 릴레이는 [Grove 릴레이](https://www.seeedstudio.com/Grove-Relay.html)로, 기본적으로 열려 있는 릴레이입니다(즉, 릴레이에 신호가 전달되지 않을 때 출력 회로가 열려 있거나 연결이 끊어져 있음). 이 릴레이는 최대 250V, 10A의 출력 회로를 처리할 수 있습니다.

이 릴레이는 디지털 액추에이터이므로 Grove Base Hat의 디지털 핀에 연결됩니다.

### 릴레이 연결하기

Grove 릴레이를 Raspberry Pi에 연결할 수 있습니다.

#### 작업

릴레이를 연결하세요.

![Grove 릴레이](../../../../../translated_images/ko/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Grove 케이블의 한쪽 끝을 릴레이 소켓에 삽입하세요. 케이블은 한 방향으로만 들어갑니다.

1. Raspberry Pi의 전원을 끈 상태에서, Grove 케이블의 다른 쪽 끝을 Pi에 부착된 Grove Base Hat의 **D5**로 표시된 디지털 소켓에 연결하세요. 이 소켓은 GPIO 핀 옆에 있는 소켓 줄에서 왼쪽에서 두 번째입니다. 토양 수분 센서는 **A0** 소켓에 계속 연결된 상태로 둡니다.

![D5 소켓에 연결된 Grove 릴레이와 A0 소켓에 연결된 토양 수분 센서](../../../../../translated_images/ko/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. 이전 수업에서 이미 토양에 삽입하지 않았다면, 토양 수분 센서를 토양에 삽입하세요.

## 릴레이 프로그래밍하기

이제 Raspberry Pi를 프로그래밍하여 연결된 릴레이를 사용할 수 있습니다.

### 작업

장치를 프로그래밍하세요.

1. Raspberry Pi의 전원을 켜고 부팅이 완료될 때까지 기다리세요.

1. VS Code에서 이전 수업의 `soil-moisture-sensor` 프로젝트를 열어둡니다. 이 프로젝트에 코드를 추가할 것입니다.

1. 기존의 import 문 아래에 다음 코드를 `app.py` 파일에 추가하세요:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    이 코드는 Grove Python 라이브러리에서 `GroveRelay`를 가져와 Grove 릴레이와 상호작용할 수 있도록 합니다.

1. `ADC` 클래스 선언 아래에 다음 코드를 추가하여 `GroveRelay` 인스턴스를 생성하세요:

    ```python
    relay = GroveRelay(5)
    ```

    이 코드는 **D5** 핀(릴레이를 연결한 디지털 핀)을 사용하는 릴레이를 생성합니다.

1. 릴레이가 작동하는지 테스트하려면, `while True:` 루프에 다음 코드를 추가하세요:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    이 코드는 릴레이를 켠 후 0.5초 동안 대기하고, 릴레이를 끕니다.

1. Python 앱을 실행하세요. 릴레이는 10초마다 켜지고 꺼지며, 켜지고 꺼지는 사이에 0.5초의 지연이 있습니다. 릴레이가 켜질 때 클릭 소리가 나고, 꺼질 때 다시 클릭 소리가 납니다. 릴레이가 켜지면 Grove 보드의 LED가 켜지고, 꺼지면 LED가 꺼집니다.

    ![릴레이가 켜지고 꺼지는 모습](../../../../../images/relay-turn-on-off.gif)

## 토양 수분에 따라 릴레이 제어하기

이제 릴레이가 작동하므로, 토양 수분 센서의 읽기 값에 따라 릴레이를 제어할 수 있습니다.

### 작업

릴레이를 제어하세요.

1. 릴레이를 테스트하기 위해 추가했던 3줄의 코드를 삭제하세요. 대신 다음 코드를 추가하세요:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    이 코드는 토양 수분 센서에서 토양 수분 수준을 확인합니다. 값이 450을 초과하면 릴레이를 켜고, 450 미만이면 릴레이를 끕니다.

    > 💁 정전용량식 토양 수분 센서는 읽기 값이 낮을수록 토양에 수분이 많고, 값이 높을수록 토양에 수분이 적다는 것을 기억하세요.

1. Python 앱을 실행하세요. 토양 수분 수준에 따라 릴레이가 켜지거나 꺼지는 것을 볼 수 있습니다. 건조한 토양에서 테스트한 후, 물을 추가해 보세요.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 이 코드는 [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi) 폴더에서 찾을 수 있습니다.

😀 토양 수분 센서로 릴레이를 제어하는 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.