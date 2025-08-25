<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-24T22:02:47+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "ko"
}
-->
# 온도 게시 - 가상 IoT 하드웨어와 Raspberry Pi

이 수업의 이 부분에서는 Raspberry Pi 또는 가상 IoT 장치가 감지한 온도 값을 MQTT를 통해 게시하여 나중에 GDD를 계산하는 데 사용할 수 있도록 합니다.

## 온도 게시하기

온도가 읽힌 후에는 MQTT를 통해 '서버' 코드로 게시할 수 있습니다. 이 서버 코드는 값을 읽고 GDD 계산에 사용할 준비를 합니다.

### 작업 - 온도 게시하기

장치를 프로그래밍하여 온도 데이터를 게시하세요.

1. `temperature-sensor` 앱 프로젝트가 열려 있지 않다면 열어주세요.

1. MQTT에 연결하고 텔레메트리를 보내는 4번째 수업에서 했던 단계를 반복하세요. 동일한 공개 Mosquitto 브로커를 사용할 것입니다.

    이 단계는 다음과 같습니다:

    - MQTT pip 패키지 추가
    - MQTT 브로커에 연결하는 코드 추가
    - 텔레메트리를 게시하는 코드 추가

    > ⚠️ 필요하다면 [MQTT 연결 지침](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md)과 [텔레메트리 전송 지침](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md)을 참조하세요.

1. `client_name`이 이 프로젝트의 이름을 반영하는지 확인하세요:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. 텔레메트리의 경우, 조도 값을 보내는 대신 DHT 센서에서 읽은 온도 값을 JSON 문서의 `temperature`라는 속성으로 보내세요:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. 온도 값은 자주 읽을 필요가 없습니다. 짧은 시간 안에 크게 변하지 않으므로 `time.sleep`을 10분으로 설정하세요:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 `sleep` 함수는 시간을 초 단위로 받습니다. 읽기 쉽게 하기 위해 값은 계산 결과로 전달됩니다. 1분은 60초이므로 10 x (1분의 60초)로 10분 지연을 설정합니다.

1. 이전 과제의 코드 실행 방식과 동일하게 코드를 실행하세요. 가상 IoT 장치를 사용하는 경우 CounterFit 앱이 실행 중인지 확인하고 습도 및 온도 센서가 올바른 핀에 생성되었는지 확인하세요.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 이 코드는 [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) 폴더 또는 [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) 폴더에서 찾을 수 있습니다.

😀 장치에서 텔레메트리로 온도를 성공적으로 게시했습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.