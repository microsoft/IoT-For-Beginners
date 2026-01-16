<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-24T22:19:55+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "ko"
}
-->
# 릴레이 제어하기 - 가상 IoT 하드웨어

이 수업의 이번 부분에서는 토양 수분 센서에 더해 가상 IoT 장치에 릴레이를 추가하고, 토양 수분 수준에 따라 이를 제어하는 방법을 배웁니다.

## 가상 하드웨어

가상 IoT 장치는 시뮬레이션된 Grove 릴레이를 사용합니다. 이는 실제 Grove 릴레이를 사용하는 Raspberry Pi와 동일한 방식으로 실습을 진행할 수 있게 합니다.

실제 IoT 장치에서 릴레이는 일반적으로 열려 있는 릴레이(즉, 릴레이에 신호가 보내지지 않을 때 출력 회로가 열려 있거나 연결이 끊어진 상태)입니다. 이러한 릴레이는 최대 250V와 10A의 출력 회로를 처리할 수 있습니다.

### CounterFit에 릴레이 추가하기

가상 릴레이를 사용하려면 CounterFit 앱에 릴레이를 추가해야 합니다.

#### 작업

CounterFit 앱에 릴레이를 추가하세요.

1. VS Code에서 이전 수업의 `soil-moisture-sensor` 프로젝트를 열어둡니다. 이 프로젝트에 추가 작업을 진행할 것입니다.

1. CounterFit 웹 앱이 실행 중인지 확인하세요.

1. 릴레이를 생성하세요:

    1. *Actuators* 창의 *Create actuator* 상자에서 *Actuator type* 드롭다운을 열고 *Relay*를 선택합니다.

    1. *Pin*을 *5*로 설정합니다.

    1. **Add** 버튼을 선택하여 Pin 5에 릴레이를 생성합니다.

    ![릴레이 설정](../../../../../translated_images/ko/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    릴레이가 생성되어 액추에이터 목록에 나타납니다.

    ![생성된 릴레이](../../../../../translated_images/ko/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## 릴레이 프로그래밍하기

이제 토양 수분 센서 앱을 가상 릴레이를 사용하도록 프로그래밍할 수 있습니다.

### 작업

가상 장치를 프로그래밍하세요.

1. VS Code에서 이전 수업의 `soil-moisture-sensor` 프로젝트를 열어둡니다. 이 프로젝트에 추가 작업을 진행할 것입니다.

1. 기존의 import 아래에 다음 코드를 `app.py` 파일에 추가하세요:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    이 코드는 Grove Python shim 라이브러리에서 `GroveRelay`를 가져와 가상 Grove 릴레이와 상호작용할 수 있도록 합니다.

1. `ADC` 클래스 선언 아래에 다음 코드를 추가하여 `GroveRelay` 인스턴스를 생성하세요:

    ```python
    relay = GroveRelay(5)
    ```

    이는 Pin **5**를 사용하여 릴레이를 생성합니다. 이 핀은 릴레이를 연결한 핀입니다.

1. 릴레이가 작동하는지 테스트하려면 `while True:` 루프에 다음 코드를 추가하세요:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    이 코드는 릴레이를 켜고 0.5초 동안 대기한 후 릴레이를 끕니다.

1. Python 앱을 실행하세요. 릴레이는 10초마다 켜지고 꺼지며, 켜지고 꺼지는 사이에 0.5초의 지연이 있습니다. CounterFit 앱에서 가상 릴레이가 켜지고 꺼지는 모습을 확인할 수 있습니다.

    ![가상 릴레이가 켜지고 꺼지는 모습](../../../../../images/virtual-relay-turn-on-off.gif)

## 토양 수분에 따라 릴레이 제어하기

이제 릴레이가 작동하므로 토양 수분 센서의 읽기값에 따라 릴레이를 제어할 수 있습니다.

### 작업

릴레이를 제어하세요.

1. 릴레이를 테스트하기 위해 추가했던 3줄의 코드를 삭제하세요. 대신 다음 코드를 해당 위치에 추가하세요:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    이 코드는 토양 수분 센서에서 읽은 값을 확인합니다. 값이 450을 초과하면 릴레이를 켜고, 450 미만이면 릴레이를 끕니다.

    > 💁 용량성 토양 수분 센서는 읽기값이 낮을수록 토양에 수분이 많고, 읽기값이 높을수록 토양에 수분이 적다는 것을 기억하세요.

1. Python 앱을 실행하세요. 토양 수분 수준에 따라 릴레이가 켜지거나 꺼지는 모습을 확인할 수 있습니다. 토양 수분 센서의 *Value* 또는 *Random* 설정을 변경하여 값을 확인하세요.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 이 코드는 [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) 폴더에서 찾을 수 있습니다.

😀 가상 토양 수분 센서가 릴레이를 제어하는 프로그램을 성공적으로 완료했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.