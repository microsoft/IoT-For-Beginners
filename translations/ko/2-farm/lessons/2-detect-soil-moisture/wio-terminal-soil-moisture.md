<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-24T22:37:53+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "ko"
}
-->
# 토양 수분 측정 - Wio Terminal

이 수업의 이 부분에서는 Wio Terminal에 정전식 토양 수분 센서를 추가하고, 센서로부터 값을 읽는 방법을 배웁니다.

## 하드웨어

Wio Terminal에는 정전식 토양 수분 센서가 필요합니다.

사용할 센서는 [정전식 토양 수분 센서](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)로, 토양의 정전 용량을 감지하여 토양 수분을 측정합니다. 토양 수분이 변하면 정전 용량도 변합니다. 토양 수분이 증가하면 전압은 감소합니다.

이 센서는 아날로그 센서로, Wio Terminal의 아날로그 핀에 연결되며, 온보드 ADC를 사용하여 0-1,023 범위의 값을 생성합니다.

### 토양 수분 센서 연결하기

Grove 토양 수분 센서는 Wio Terminal의 설정 가능한 아날로그/디지털 포트에 연결할 수 있습니다.

#### 작업 - 토양 수분 센서 연결하기

토양 수분 센서를 연결하세요.

![Grove 토양 수분 센서](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.ko.png)

1. Grove 케이블의 한쪽 끝을 토양 수분 센서의 소켓에 삽입합니다. 케이블은 한 방향으로만 삽입됩니다.

1. Wio Terminal을 컴퓨터나 다른 전원 공급 장치에서 분리한 상태에서, Grove 케이블의 다른 쪽 끝을 Wio Terminal 화면 기준 오른쪽에 있는 Grove 소켓에 연결합니다. 이 소켓은 전원 버튼에서 가장 먼 소켓입니다.

![오른쪽 소켓에 연결된 Grove 토양 수분 센서](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb74.ko.png)

1. 토양 수분 센서를 흙에 삽입합니다. 센서에는 '최대 삽입 위치 선'이 있습니다. 센서에 그려진 흰 선까지 삽입하되, 그 선을 넘지 않도록 합니다.

![흙에 삽입된 Grove 토양 수분 센서](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.ko.png)

1. 이제 Wio Terminal을 컴퓨터에 연결할 수 있습니다.

## 토양 수분 센서 프로그래밍

이제 Wio Terminal을 연결된 토양 수분 센서를 사용할 수 있도록 프로그래밍할 수 있습니다.

### 작업 - 토양 수분 센서 프로그래밍하기

장치를 프로그래밍하세요.

1. PlatformIO를 사용하여 새로운 Wio Terminal 프로젝트를 만드세요. 이 프로젝트의 이름을 `soil-moisture-sensor`로 설정합니다. `setup` 함수에 직렬 포트를 설정하는 코드를 추가하세요.

    > ⚠️ [프로젝트 1, 수업 1에서 PlatformIO 프로젝트를 생성하는 방법](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)을 참고할 수 있습니다.

1. 이 센서를 위한 라이브러리는 없으므로, 내장된 Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) 함수를 사용하여 아날로그 핀에서 값을 읽을 수 있습니다. 먼저 `setup` 함수에 아날로그 핀을 입력으로 설정하는 코드를 추가하여 값을 읽을 수 있도록 합니다.

    ```cpp
    pinMode(A0, INPUT);
    ```

    이 코드는 `A0` 핀(아날로그/디지털 핀)을 입력 핀으로 설정하여 전압을 읽을 수 있도록 합니다.

1. `loop` 함수에 다음 코드를 추가하여 이 핀에서 전압을 읽으세요:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. 이 코드 아래에 직렬 포트에 값을 출력하는 다음 코드를 추가하세요:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. 마지막으로 10초의 지연을 추가하세요:

    ```cpp
    delay(10000);
    ```

1. 코드를 빌드하고 Wio Terminal에 업로드하세요.

    > ⚠️ [프로젝트 1, 수업 1에서 PlatformIO 프로젝트를 생성하는 방법](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)을 참고할 수 있습니다.

1. 업로드가 완료되면 직렬 모니터를 사용하여 토양 수분을 모니터링할 수 있습니다. 흙에 물을 추가하거나 센서를 흙에서 제거하여 값이 변하는 것을 확인하세요.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    위의 예제 출력에서 물을 추가하면 전압이 감소하는 것을 볼 수 있습니다.

> 💁 이 코드는 [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) 폴더에서 확인할 수 있습니다.

😀 토양 수분 센서 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.