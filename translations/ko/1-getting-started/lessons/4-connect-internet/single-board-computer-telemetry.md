<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-24T23:01:18+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "ko"
}
-->
# 인터넷을 통해 야간등 제어하기 - 가상 IoT 하드웨어와 Raspberry Pi

이 수업의 이 부분에서는 Raspberry Pi 또는 가상 IoT 장치에서 조도 데이터를 MQTT 브로커로 전송합니다.

## 원격 데이터 전송

다음 단계는 원격 데이터를 포함한 JSON 문서를 생성하고 이를 MQTT 브로커로 전송하는 것입니다.

### 작업

MQTT 브로커로 원격 데이터를 전송하세요.

1. VS Code에서 야간등 프로젝트를 엽니다.

1. 가상 IoT 장치를 사용하는 경우, 터미널이 가상 환경을 실행 중인지 확인하세요. Raspberry Pi를 사용하는 경우 가상 환경을 사용하지 않습니다.

1. `app.py` 파일 상단에 다음 임포트를 추가하세요:

    ```python
    import json
    ```

    `json` 라이브러리는 원격 데이터를 JSON 문서로 인코딩하는 데 사용됩니다.

1. `client_name` 선언 바로 아래에 다음을 추가하세요:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic`은 장치가 조도 데이터를 게시할 MQTT 주제(topic)입니다.

1. 파일 끝부분의 `while True:` 루프 내용을 다음으로 교체하세요:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    이 코드는 조도 데이터를 JSON 문서로 패키징하고 이를 MQTT 브로커로 게시합니다. 그런 다음 메시지 전송 빈도를 줄이기 위해 잠시 대기합니다.

1. 이전 과제의 코드를 실행했던 것과 동일한 방식으로 코드를 실행하세요. 가상 IoT 장치를 사용하는 경우, CounterFit 앱이 실행 중이며 조도 센서와 LED가 올바른 핀에 생성되었는지 확인하세요.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 이 코드는 [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) 폴더 또는 [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) 폴더에서 찾을 수 있습니다.

😀 장치에서 원격 데이터를 성공적으로 전송했습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.