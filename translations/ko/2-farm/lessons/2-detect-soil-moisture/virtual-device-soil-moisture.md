<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-24T22:40:12+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "ko"
}
-->
# 토양 수분 측정 - 가상 IoT 하드웨어

이 수업의 이 부분에서는 가상 IoT 장치에 정전식 토양 수분 센서를 추가하고 값을 읽는 방법을 배웁니다.

## 가상 하드웨어

가상 IoT 장치는 시뮬레이션된 Grove 정전식 토양 수분 센서를 사용합니다. 이는 실제 Grove 정전식 토양 수분 센서를 사용하는 Raspberry Pi와 동일한 방식으로 실습을 진행할 수 있게 합니다.

실제 IoT 장치에서 토양 수분 센서는 정전식 센서로, 토양의 정전 용량을 감지하여 토양 수분을 측정합니다. 토양의 수분이 증가하면 전압이 감소합니다.

이 센서는 아날로그 센서로, 10비트 ADC를 시뮬레이션하여 1에서 1,023 사이의 값을 보고합니다.

### CounterFit에 토양 수분 센서 추가하기

가상 토양 수분 센서를 사용하려면 CounterFit 앱에 센서를 추가해야 합니다.

#### 작업 - CounterFit에 토양 수분 센서 추가하기

CounterFit 앱에 토양 수분 센서를 추가하세요.

1. `soil-moisture-sensor`라는 폴더에 `app.py`라는 단일 파일과 Python 가상 환경을 포함한 새 Python 앱을 컴퓨터에 만드세요. 그리고 CounterFit pip 패키지를 추가하세요.

    > ⚠️ 필요하다면 [1단원에서 CounterFit Python 프로젝트를 생성하고 설정하는 방법에 대한 지침](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)을 참조하세요.

1. CounterFit 웹 앱이 실행 중인지 확인하세요.

1. 토양 수분 센서를 생성하세요:

    1. *Sensors* 패널의 *Create sensor* 상자에서 *Sensor type* 드롭다운을 열고 *Soil Moisture*를 선택하세요.

    1. *Units*는 *NoUnits*로 그대로 두세요.

    1. *Pin*이 *0*으로 설정되어 있는지 확인하세요.

    1. **Add** 버튼을 선택하여 Pin 0에 *Soil Moisture* 센서를 생성하세요.

    ![토양 수분 센서 설정](../../../../../translated_images/ko/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    토양 수분 센서가 생성되어 센서 목록에 나타납니다.

    ![생성된 토양 수분 센서](../../../../../translated_images/ko/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## 토양 수분 센서 앱 프로그래밍

이제 CounterFit 센서를 사용하여 토양 수분 센서 앱을 프로그래밍할 수 있습니다.

### 작업 - 토양 수분 센서 앱 프로그래밍

토양 수분 센서 앱을 프로그래밍하세요.

1. VS Code에서 `soil-moisture-sensor` 앱이 열려 있는지 확인하세요.

1. `app.py` 파일을 여세요.

1. CounterFit에 앱을 연결하기 위해 `app.py` 상단에 다음 코드를 추가하세요:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 필요한 라이브러리를 가져오기 위해 `app.py` 파일에 다음 코드를 추가하세요:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    `import time` 문은 이후에 사용할 `time` 모듈을 가져옵니다.

    `from counterfit_shims_grove.adc import ADC` 문은 CounterFit 센서에 연결할 수 있는 가상 아날로그-디지털 변환기와 상호작용하기 위해 `ADC` 클래스를 가져옵니다.

1. 아래에 `ADC` 클래스의 인스턴스를 생성하는 코드를 추가하세요:

    ```python
    adc = ADC()
    ```

1. Pin 0에서 이 ADC를 읽고 결과를 콘솔에 출력하는 무한 루프를 추가하세요. 이 루프는 읽기 사이에 10초 동안 대기할 수 있습니다.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. CounterFit 앱에서 앱이 읽을 토양 수분 센서 값을 변경하세요. 다음 두 가지 방법 중 하나를 사용할 수 있습니다:

    * 토양 수분 센서의 *Value* 상자에 숫자를 입력한 다음 **Set** 버튼을 선택하세요. 입력한 숫자가 센서가 반환하는 값이 됩니다.

    * *Random* 체크박스를 선택하고 *Min* 및 *Max* 값을 입력한 다음 **Set** 버튼을 선택하세요. 센서가 값을 읽을 때마다 *Min*과 *Max* 사이의 임의의 숫자를 읽습니다.

1. Python 앱을 실행하세요. 콘솔에 토양 수분 측정값이 표시됩니다. *Value* 또는 *Random* 설정을 변경하여 값이 변하는 것을 확인하세요.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 이 코드는 [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device) 폴더에서 확인할 수 있습니다.

😀 토양 수분 센서 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.