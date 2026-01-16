<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-24T23:25:09+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "ko"
}
-->
# 야간등 만들기 - 가상 IoT 하드웨어

이 수업의 이 부분에서는 가상 IoT 장치에 조도 센서를 추가할 것입니다.

## 가상 하드웨어

야간등에는 CounterFit 앱에서 생성된 하나의 센서가 필요합니다.

이 센서는 **조도 센서**입니다. 실제 IoT 장치에서는 빛을 전기 신호로 변환하는 [포토다이오드](https://wikipedia.org/wiki/Photodiode)가 될 것입니다. 조도 센서는 아날로그 센서로, 특정 단위(예: [럭스](https://wikipedia.org/wiki/Lux))에 매핑되지 않는 상대적인 빛의 양을 나타내는 정수 값을 보냅니다.

### CounterFit에 센서 추가하기

가상 조도 센서를 사용하려면 CounterFit 앱에 센서를 추가해야 합니다.

#### 작업 - CounterFit에 센서 추가하기

CounterFit 앱에 조도 센서를 추가하세요.

1. 이 과제의 이전 부분에서 실행했던 CounterFit 웹 앱이 실행 중인지 확인하세요. 실행 중이 아니라면 시작하세요.

1. 조도 센서를 생성하세요:

    1. *Sensors* 창의 *Create sensor* 상자에서 *Sensor type* 드롭다운 메뉴를 열고 *Light*를 선택하세요.

    1. *Units*는 *NoUnits*로 그대로 둡니다.

    1. *Pin*이 *0*으로 설정되어 있는지 확인하세요.

    1. **Add** 버튼을 선택하여 Pin 0에 조도 센서를 생성하세요.

    ![조도 센서 설정](../../../../../translated_images/ko/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    조도 센서가 생성되어 센서 목록에 나타납니다.

    ![생성된 조도 센서](../../../../../translated_images/ko/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## 조도 센서 프로그래밍

이제 장치를 프로그래밍하여 내장된 조도 센서를 사용할 수 있습니다.

### 작업 - 조도 센서 프로그래밍

장치를 프로그래밍하세요.

1. 이 과제의 이전 부분에서 생성한 야간등 프로젝트를 VS Code에서 엽니다. 필요하다면 터미널을 종료하고 다시 생성하여 가상 환경이 실행 중인지 확인하세요.

1. `app.py` 파일을 엽니다.

1. `import` 문과 함께 `app.py` 파일 상단에 다음 코드를 추가하여 필요한 라이브러리를 가져옵니다:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` 문은 이후 과제에서 사용할 Python `time` 모듈을 가져옵니다.

    `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` 문은 CounterFit Grove shim Python 라이브러리에서 `GroveLightSensor`를 가져옵니다. 이 라이브러리는 CounterFit 앱에서 생성된 조도 센서와 상호작용하는 코드를 포함하고 있습니다.

1. 파일 하단에 다음 코드를 추가하여 조도 센서를 관리하는 클래스의 인스턴스를 생성합니다:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)` 줄은 **0번 핀**에 연결된 `GroveLightSensor` 클래스의 인스턴스를 생성합니다. 이 핀은 CounterFit Grove에서 조도 센서가 연결된 핀입니다.

1. 위 코드 아래에 무한 루프를 추가하여 조도 센서 값을 폴링하고 콘솔에 출력합니다:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    이는 `GroveLightSensor` 클래스의 `light` 속성을 사용하여 현재 조도 수준을 읽습니다. 이 속성은 핀에서 아날로그 값을 읽습니다. 이 값은 콘솔에 출력됩니다.

1. `while` 루프 끝에 1초의 짧은 대기 시간을 추가하여 조도 수준을 계속 확인할 필요가 없도록 합니다. 대기 시간은 장치의 전력 소비를 줄여줍니다.

    ```python
    time.sleep(1)
    ```

1. VS Code 터미널에서 다음 명령을 실행하여 Python 앱을 실행합니다:

    ```sh
    python3 app.py
    ```

    조도 값이 콘솔에 출력됩니다. 초기 값은 0일 것입니다.

1. CounterFit 앱에서 앱이 읽을 조도 센서 값을 변경하세요. 다음 두 가지 방법 중 하나를 사용할 수 있습니다:

    * 조도 센서의 *Value* 상자에 숫자를 입력한 다음 **Set** 버튼을 선택하세요. 입력한 숫자가 센서가 반환하는 값이 됩니다.

    * *Random* 체크박스를 선택하고 *Min* 및 *Max* 값을 입력한 다음 **Set** 버튼을 선택하세요. 센서가 값을 읽을 때마다 *Min*과 *Max* 사이의 임의의 숫자를 읽습니다.

    설정한 값이 콘솔에 출력됩니다. *Value* 또는 *Random* 설정을 변경하여 값을 변경하세요.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 이 코드는 [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device) 폴더에서 확인할 수 있습니다.

😀 야간등 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.