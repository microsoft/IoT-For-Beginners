<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-24T21:56:30+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "ko"
}
-->
# 근접 감지 - 가상 IoT 하드웨어

이 강의의 이 부분에서는 가상 IoT 장치에 근접 센서를 추가하고, 거리 데이터를 읽는 방법을 배웁니다.

## 하드웨어

가상 IoT 장치는 시뮬레이션된 거리 센서를 사용합니다.

물리적인 IoT 장치에서는 레이저 거리 측정 모듈이 있는 센서를 사용하여 거리를 감지합니다.

### CounterFit에 거리 센서 추가하기

가상 거리 센서를 사용하려면 CounterFit 앱에 센서를 추가해야 합니다.

#### 작업 - CounterFit에 거리 센서 추가하기

CounterFit 앱에 거리 센서를 추가하세요.

1. VS Code에서 `fruit-quality-detector` 코드를 열고 가상 환경이 활성화되어 있는지 확인하세요.

1. 추가 Pip 패키지를 설치하여 거리 센서를 시뮬레이션하는 CounterFit shim을 설치합니다. 이 shim은 [rpi-vl53l0x Pip 패키지](https://pypi.org/project/rpi-vl53l0x/)를 시뮬레이션하며, 이는 [VL53L0X 비행 시간 거리 센서](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/)와 상호작용하는 Python 패키지입니다. 가상 환경이 활성화된 터미널에서 설치해야 합니다.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. CounterFit 웹 앱이 실행 중인지 확인하세요.

1. 거리 센서를 생성하세요:

    1. *Sensors* 창의 *Create sensor* 상자에서 *Sensor type* 드롭다운을 열고 *Distance*를 선택하세요.

    1. *Units*는 `Millimeter`로 그대로 두세요.

    1. 이 센서는 I²C 센서이므로 주소를 `0x29`로 설정하세요. 물리적인 VL53L0X 센서를 사용할 경우 이 주소로 고정됩니다.

    1. **Add** 버튼을 선택하여 거리 센서를 생성하세요.

    ![거리 센서 설정](../../../../../translated_images/ko/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    거리 센서가 생성되어 센서 목록에 나타납니다.

    ![생성된 거리 센서](../../../../../translated_images/ko/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## 거리 센서 프로그래밍

이제 가상 IoT 장치가 시뮬레이션된 거리 센서를 사용할 수 있도록 프로그래밍할 수 있습니다.

### 작업 - 비행 시간 센서 프로그래밍

1. `fruit-quality-detector` 프로젝트에 `distance-sensor.py`라는 새 파일을 만드세요.

    > 💁 여러 IoT 장치를 시뮬레이션하는 쉬운 방법은 각 장치를 다른 Python 파일에 작성한 후 동시에 실행하는 것입니다.

1. 다음 코드를 사용하여 CounterFit에 연결을 시작하세요:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 아래 코드를 추가하세요:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    이는 VL53L0X 비행 시간 센서를 위한 센서 라이브러리 shim을 가져옵니다.

1. 그 아래에 다음 코드를 추가하여 센서에 접근하세요:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    이 코드는 거리 센서를 선언한 후 센서를 시작합니다.

1. 마지막으로, 거리를 읽는 무한 루프를 추가하세요:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    이 코드는 센서에서 값을 읽을 준비가 될 때까지 기다린 후, 값을 콘솔에 출력합니다.

1. 이 코드를 실행하세요.

    > 💁 이 파일의 이름은 `distance-sensor.py`입니다! `app.py`가 아니라 Python으로 실행해야 합니다.

1. 콘솔에 거리 측정값이 나타나는 것을 볼 수 있습니다. CounterFit에서 값을 변경하거나 랜덤 값을 사용하여 이 값이 변경되는 것을 확인하세요.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 이 코드는 [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) 폴더에서 찾을 수 있습니다.

😀 근접 센서 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.