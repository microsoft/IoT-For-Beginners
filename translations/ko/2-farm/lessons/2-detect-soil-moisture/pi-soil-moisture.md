<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-24T22:41:31+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "ko"
}
-->
# 토양 수분 측정 - Raspberry Pi

이 수업의 이번 부분에서는 Raspberry Pi에 정전식 토양 수분 센서를 추가하고 센서로부터 값을 읽는 방법을 배웁니다.

## 하드웨어

Raspberry Pi에는 정전식 토양 수분 센서가 필요합니다.

사용할 센서는 [정전식 토양 수분 센서](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)로, 토양의 정전 용량을 감지하여 토양 수분을 측정합니다. 토양의 수분이 변하면 정전 용량도 변합니다. 토양 수분이 증가하면 전압이 감소합니다.

이 센서는 아날로그 센서로, 아날로그 핀을 사용하며, Pi의 Grove Base Hat에 있는 10비트 ADC를 통해 전압을 디지털 신호(1-1,023)로 변환합니다. 변환된 신호는 Pi의 GPIO 핀을 통해 I2C로 전송됩니다.

### 토양 수분 센서 연결하기

Grove 토양 수분 센서를 Raspberry Pi에 연결할 수 있습니다.

#### 작업 - 토양 수분 센서 연결하기

토양 수분 센서를 연결하세요.

![Grove 토양 수분 센서](../../../../../translated_images/ko/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Grove 케이블의 한쪽 끝을 토양 수분 센서의 소켓에 삽입합니다. 케이블은 한 방향으로만 삽입됩니다.

1. Raspberry Pi의 전원을 끈 상태에서, Grove 케이블의 다른 쪽 끝을 Pi에 부착된 Grove Base Hat의 **A0**로 표시된 아날로그 소켓에 연결합니다. 이 소켓은 GPIO 핀 옆에 있는 소켓 행에서 오른쪽에서 두 번째입니다.

![A0 소켓에 연결된 Grove 토양 수분 센서](../../../../../translated_images/ko/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.png)

1. 토양에 토양 수분 센서를 삽입합니다. 센서에는 '최고 위치 라인'이라는 흰색 선이 있습니다. 이 선까지 센서를 삽입하되, 선을 넘지 않도록 합니다.

![토양에 삽입된 Grove 토양 수분 센서](../../../../../translated_images/ko/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## 토양 수분 센서 프로그래밍하기

이제 Raspberry Pi를 프로그래밍하여 연결된 토양 수분 센서를 사용할 수 있습니다.

### 작업 - 토양 수분 센서 프로그래밍하기

장치를 프로그래밍하세요.

1. Pi의 전원을 켜고 부팅이 완료될 때까지 기다립니다.

1. VS Code를 실행합니다. Pi에서 직접 실행하거나 Remote SSH 확장을 통해 연결할 수 있습니다.

    > ⚠️ 필요하면 [야간 조명 - 수업 1에서 VS Code 설정 및 실행 방법](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)을 참조하세요.

1. 터미널에서 `pi` 사용자 홈 디렉토리에 `soil-moisture-sensor`라는 새 폴더를 만듭니다. 이 폴더에 `app.py`라는 파일을 생성합니다.

1. VS Code에서 이 폴더를 엽니다.

1. `app.py` 파일에 다음 코드를 추가하여 필요한 라이브러리를 가져옵니다:

    ```python
    import time
    from grove.adc import ADC
    ```

    `import time` 문은 나중에 이 과제에서 사용할 `time` 모듈을 가져옵니다.

    `from grove.adc import ADC` 문은 Grove Python 라이브러리에서 ADC를 가져옵니다. 이 라이브러리는 Pi Base Hat의 아날로그-디지털 변환기와 상호작용하고 아날로그 센서에서 전압을 읽는 코드를 포함하고 있습니다.

1. 아래에 다음 코드를 추가하여 `ADC` 클래스의 인스턴스를 생성합니다:

    ```python
    adc = ADC()
    ```

1. A0 핀에서 ADC를 읽고 결과를 콘솔에 출력하는 무한 루프를 추가합니다. 이 루프는 읽기 사이에 10초 동안 대기할 수 있습니다.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Python 앱을 실행합니다. 콘솔에 토양 수분 측정값이 출력됩니다. 토양에 물을 추가하거나 센서를 토양에서 제거하여 값이 변하는 것을 확인하세요.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    위의 예제 출력에서 물을 추가하면 전압이 감소하는 것을 볼 수 있습니다.

> 💁 이 코드는 [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi) 폴더에서 찾을 수 있습니다.

😀 토양 수분 센서 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.