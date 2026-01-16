<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-24T22:09:07+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "ko"
}
-->
# 온도 측정 - Raspberry Pi

이 수업의 이 부분에서는 Raspberry Pi에 온도 센서를 추가합니다.

## 하드웨어

사용할 센서는 [DHT11 습도 및 온도 센서](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)로, 하나의 패키지에 두 개의 센서를 결합한 것입니다. 이 센서는 비교적 널리 사용되며, 온도, 습도, 때로는 대기압을 결합한 상용 센서들이 많이 있습니다. 온도 센서 구성 요소는 음의 온도 계수(NTC) 서미스터로, 온도가 증가함에 따라 저항이 감소하는 서미스터입니다.

이 센서는 디지털 센서로, 온도와 습도 데이터를 포함한 디지털 신호를 생성하는 온보드 ADC를 가지고 있어 마이크로컨트롤러가 읽을 수 있습니다.

### 온도 센서 연결하기

Grove 온도 센서를 Raspberry Pi에 연결할 수 있습니다.

#### 작업

온도 센서를 연결하세요.

![Grove 온도 센서](../../../../../translated_images/ko/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Grove 케이블의 한쪽 끝을 습도 및 온도 센서의 소켓에 삽입합니다. 케이블은 한 방향으로만 들어갑니다.

1. Raspberry Pi의 전원을 끈 상태에서, Grove 케이블의 다른 끝을 Pi에 부착된 Grove Base Hat의 **D5**로 표시된 디지털 소켓에 연결합니다. 이 소켓은 GPIO 핀 옆에 있는 소켓 행에서 왼쪽에서 두 번째입니다.

![소켓 A0에 연결된 Grove 온도 센서](../../../../../translated_images/ko/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## 온도 센서 프로그래밍하기

이제 장치를 프로그래밍하여 연결된 온도 센서를 사용할 수 있습니다.

### 작업

장치를 프로그래밍하세요.

1. Pi의 전원을 켜고 부팅을 기다립니다.

1. VS Code를 실행합니다. Pi에서 직접 실행하거나 Remote SSH 확장을 통해 연결합니다.

    > ⚠️ 필요하면 [1단원에서 VS Code 설정 및 실행 지침을 참조하세요](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. 터미널에서 `pi` 사용자 홈 디렉토리에 `temperature-sensor`라는 새 폴더를 만듭니다. 이 폴더에 `app.py`라는 파일을 만듭니다:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. VS Code에서 이 폴더를 엽니다.

1. 온도 및 습도 센서를 사용하려면 추가 Pip 패키지를 설치해야 합니다. VS Code의 터미널에서 다음 명령을 실행하여 Pi에 이 Pip 패키지를 설치합니다:

    ```sh
    pip3 install seeed-python-dht
    ```

1. `app.py` 파일에 다음 코드를 추가하여 필요한 라이브러리를 가져옵니다:

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT` 문은 `seeed_dht` 모듈에서 Grove 온도 센서를 제어하기 위한 `DHT` 센서 클래스를 가져옵니다.

1. 위 코드 아래에 다음 코드를 추가하여 온도 센서를 관리하는 클래스의 인스턴스를 생성합니다:

    ```python
    sensor = DHT("11", 5)
    ```

    이는 **D**igital **H**umidity 및 **T**emperature 센서를 관리하는 `DHT` 클래스의 인스턴스를 선언합니다. 첫 번째 매개변수는 사용 중인 센서가 *DHT11* 센서임을 코드에 알립니다. 사용 중인 라이브러리는 이 센서의 다른 변형도 지원합니다. 두 번째 매개변수는 센서가 Grove Base Hat의 디지털 포트 `D5`에 연결되어 있음을 코드에 알립니다.

    > ✅ 모든 소켓에는 고유한 핀 번호가 있습니다. 핀 0, 2, 4, 6은 아날로그 핀이고, 핀 5, 16, 18, 22, 24, 26은 디지털 핀입니다.

1. 위 코드 아래에 무한 루프를 추가하여 온도 센서 값을 폴링하고 콘솔에 출력합니다:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    `sensor.read()` 호출은 습도와 온도의 튜플을 반환합니다. 온도 값만 필요하므로 습도는 무시됩니다. 그런 다음 온도 값이 콘솔에 출력됩니다.

1. 루프 끝에 10초의 짧은 대기 시간을 추가하여 온도 수준을 지속적으로 확인할 필요가 없도록 합니다. 대기 시간은 장치의 전력 소비를 줄여줍니다.

    ```python
    time.sleep(10)
    ```

1. VS Code 터미널에서 다음 명령을 실행하여 Python 앱을 실행합니다:

    ```sh
    python3 app.py
    ```

    콘솔에 온도 값이 출력되는 것을 볼 수 있습니다. 센서를 따뜻하게 하기 위해 엄지손가락으로 눌러보거나 팬을 사용하여 값이 변하는 것을 확인하세요:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 이 코드는 [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) 폴더에서 찾을 수 있습니다.

😀 온도 센서 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.