<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-24T23:14:10+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "ko"
}
-->
# 나이트라이트 만들기 - Raspberry Pi

이 수업의 이번 부분에서는 Raspberry Pi에 조도 센서를 추가할 것입니다.

## 하드웨어

이번 수업에서 사용할 센서는 **조도 센서**로, [포토다이오드](https://wikipedia.org/wiki/Photodiode)를 사용하여 빛을 전기 신호로 변환합니다. 이 센서는 아날로그 센서로, 0에서 1,000 사이의 정수 값을 보내며, 이는 [럭스](https://wikipedia.org/wiki/Lux)와 같은 표준 측정 단위와는 매핑되지 않는 상대적인 빛의 양을 나타냅니다.

조도 센서는 외부 Grove 센서이며, Raspberry Pi의 Grove Base Hat에 연결해야 합니다.

### 조도 센서 연결하기

빛의 양을 감지하는 데 사용되는 Grove 조도 센서를 Raspberry Pi에 연결해야 합니다.

#### 작업 - 조도 센서 연결하기

조도 센서를 연결하세요.

![Grove 조도 센서](../../../../../translated_images/ko/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Grove 케이블의 한쪽 끝을 조도 센서 모듈의 소켓에 삽입합니다. 케이블은 한 방향으로만 들어갑니다.

1. Raspberry Pi의 전원을 끈 상태에서, Grove 케이블의 다른 쪽 끝을 Pi에 부착된 Grove Base Hat의 **A0**로 표시된 아날로그 소켓에 연결합니다. 이 소켓은 GPIO 핀 옆의 소켓 줄에서 오른쪽에서 두 번째에 위치합니다.

![A0 소켓에 연결된 Grove 조도 센서](../../../../../translated_images/ko/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## 조도 센서 프로그래밍하기

이제 Grove 조도 센서를 사용하여 장치를 프로그래밍할 수 있습니다.

### 작업 - 조도 센서 프로그래밍하기

장치를 프로그래밍하세요.

1. Raspberry Pi의 전원을 켜고 부팅이 완료될 때까지 기다립니다.

1. 이전 과제에서 생성한 나이트라이트 프로젝트를 VS Code에서 엽니다. 이 작업은 Pi에서 직접 실행하거나 Remote SSH 확장을 사용하여 연결하여 수행할 수 있습니다.

1. `app.py` 파일을 열고 모든 코드를 삭제합니다.

1. 다음 코드를 `app.py` 파일에 추가하여 필요한 라이브러리를 가져옵니다:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` 문은 이 과제에서 나중에 사용할 `time` 모듈을 가져옵니다.

    `from grove.grove_light_sensor_v1_2 import GroveLightSensor` 문은 Grove Python 라이브러리에서 `GroveLightSensor`를 가져옵니다. 이 라이브러리는 Grove 조도 센서와 상호작용하는 코드를 포함하며, Pi 설정 중에 전역적으로 설치되었습니다.

1. 위 코드 아래에 다음 코드를 추가하여 조도 센서를 관리하는 클래스의 인스턴스를 생성합니다:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)` 줄은 **A0** 핀에 연결된 `GroveLightSensor` 클래스의 인스턴스를 생성합니다. 이 핀은 조도 센서가 연결된 아날로그 Grove 핀입니다.

1. 위 코드 아래에 무한 루프를 추가하여 조도 센서 값을 폴링하고 콘솔에 출력합니다:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    이는 `GroveLightSensor` 클래스의 `light` 속성을 사용하여 0-1,023 범위의 현재 조도 값을 읽습니다. 이 속성은 핀에서 아날로그 값을 읽습니다. 그런 다음 이 값이 콘솔에 출력됩니다.

1. 루프 끝에 1초의 짧은 대기 시간을 추가합니다. 조도 값은 지속적으로 확인할 필요가 없으므로, 대기 시간을 추가하면 장치의 전력 소비를 줄일 수 있습니다.

    ```python
    time.sleep(1)
    ```

1. VS Code 터미널에서 다음 명령을 실행하여 Python 앱을 실행합니다:

    ```sh
    python3 app.py
    ```

    조도 값이 콘솔에 출력됩니다. 조도 센서를 가리거나 드러내면 값이 변경됩니다:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 이 코드는 [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi) 폴더에서 확인할 수 있습니다.

😀 나이트라이트 프로그램에 센서를 추가하는 데 성공했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.