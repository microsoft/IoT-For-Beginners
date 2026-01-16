<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-24T21:54:20+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "ko"
}
-->
# 근접 감지 - Raspberry Pi

이 수업의 이 부분에서는 Raspberry Pi에 근접 센서를 추가하고 센서로부터 거리를 읽는 방법을 배웁니다.

## 하드웨어

Raspberry Pi에는 근접 센서가 필요합니다.

사용할 센서는 [Grove Time of Flight 거리 센서](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)입니다. 이 센서는 레이저 측정 모듈을 사용하여 거리를 감지합니다. 이 센서는 10mm에서 2000mm(1cm - 2m) 범위의 거리를 감지하며, 1000mm 이상의 거리는 8109mm로 보고됩니다.

레이저 거리 측정기는 센서의 뒷면, Grove 소켓의 반대쪽에 있습니다.

이 센서는 I²C 센서입니다.

### Time of Flight 센서 연결하기

Grove Time of Flight 센서를 Raspberry Pi에 연결할 수 있습니다.

#### 작업 - Time of Flight 센서 연결하기

Time of Flight 센서를 연결하세요.

![Grove Time of Flight 센서](../../../../../translated_images/ko/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Grove 케이블의 한쪽 끝을 Time of Flight 센서의 소켓에 삽입합니다. 케이블은 한 방향으로만 삽입됩니다.

1. Raspberry Pi의 전원을 끈 상태에서 Grove 케이블의 다른 끝을 Pi에 부착된 Grove Base Hat의 **I²C**로 표시된 소켓 중 하나에 연결합니다. 이 소켓은 하단 행에 있으며, GPIO 핀의 반대쪽 끝과 카메라 케이블 슬롯 옆에 위치합니다.

![I²C 소켓에 연결된 Grove Time of Flight 센서](../../../../../translated_images/ko/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Time of Flight 센서 프로그래밍하기

이제 Raspberry Pi를 프로그래밍하여 연결된 Time of Flight 센서를 사용할 수 있습니다.

### 작업 - Time of Flight 센서 프로그래밍하기

장치를 프로그래밍하세요.

1. Pi의 전원을 켜고 부팅이 완료될 때까지 기다립니다.

1. VS Code에서 `fruit-quality-detector` 코드를 엽니다. Pi에서 직접 열거나 Remote SSH 확장을 통해 연결합니다.

1. VL53L0X Time of Flight 거리 센서와 상호작용하는 Python 패키지인 rpi-vl53l0x Pip 패키지를 설치합니다. 다음 pip 명령을 사용하여 설치하세요:

    ```sh
    pip install rpi-vl53l0x
    ```

1. 이 프로젝트에 `distance-sensor.py`라는 새 파일을 만듭니다.

    > 💁 여러 IoT 장치를 시뮬레이션하는 쉬운 방법은 각각을 다른 Python 파일에 작성한 후 동시에 실행하는 것입니다.

1. 이 파일에 다음 코드를 추가하세요:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    이는 Grove I²C 버스 라이브러리와 Grove Time of Flight 센서에 내장된 핵심 센서 하드웨어를 위한 센서 라이브러리를 가져옵니다.

1. 그 아래에 센서를 액세스하기 위한 다음 코드를 추가하세요:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    이 코드는 Grove I²C 버스를 사용하여 거리 센서를 선언한 후 센서를 시작합니다.

1. 마지막으로, 거리를 읽기 위한 무한 루프를 추가하세요:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    이 코드는 센서에서 값을 읽을 준비가 될 때까지 기다린 후 콘솔에 값을 출력합니다.

1. 이 코드를 실행하세요.

    > 💁 이 파일의 이름은 `distance-sensor.py`입니다! `app.py`가 아닌 Python을 통해 실행해야 합니다.

1. 콘솔에 거리 측정값이 나타나는 것을 볼 수 있습니다. 센서 근처에 물체를 배치하면 거리 측정값이 표시됩니다:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    거리 측정기는 센서의 뒷면에 있으므로 거리를 측정할 때 올바른 쪽을 사용해야 합니다.

    ![Time of Flight 센서의 뒷면에서 바나나를 측정하는 모습](../../../../../translated_images/ko/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 이 코드는 [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) 폴더에서 찾을 수 있습니다.

😀 근접 센서 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.