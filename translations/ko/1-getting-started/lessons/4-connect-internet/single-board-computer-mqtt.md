<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-24T23:10:25+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "ko"
}
-->
# 인터넷을 통해 야간등 제어하기 - 가상 IoT 하드웨어와 Raspberry Pi

IoT 장치는 *test.mosquitto.org*와 MQTT를 사용하여 통신하도록 코딩되어야 합니다. 이를 통해 조도 센서의 읽기값을 포함한 원격 측정 데이터를 전송하고, LED를 제어하기 위한 명령을 수신합니다.

이 수업의 이 부분에서는 Raspberry Pi 또는 가상 IoT 장치를 MQTT 브로커에 연결합니다.

## MQTT 클라이언트 패키지 설치

MQTT 브로커와 통신하려면 Pi 또는 가상 장치의 가상 환경에 MQTT 라이브러리 pip 패키지를 설치해야 합니다.

### 작업

pip 패키지 설치

1. VS Code에서 야간등 프로젝트를 엽니다.

1. 가상 IoT 장치를 사용하는 경우, 터미널이 가상 환경을 실행 중인지 확인합니다. Raspberry Pi를 사용하는 경우 가상 환경을 사용하지 않습니다.

1. 다음 명령어를 실행하여 MQTT pip 패키지를 설치합니다:

    ```sh
    pip3 install paho-mqtt
    ```

## 장치 코딩하기

장치를 코딩할 준비가 되었습니다.

### 작업

장치 코드를 작성합니다.

1. `app.py` 파일 상단에 다음 import를 추가합니다:

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client` 라이브러리는 앱이 MQTT를 통해 통신할 수 있도록 합니다.

1. 조도 센서와 LED 정의 뒤에 다음 코드를 추가합니다:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    `<ID>`를 이 장치 클라이언트의 이름으로 사용할 고유 ID로 바꿉니다. 이 ID는 나중에 이 장치가 게시하고 구독하는 토픽 이름에도 사용됩니다. *test.mosquitto.org* 브로커는 공개적으로 사용되며, 이 과제를 진행 중인 다른 학생들을 포함한 많은 사람들이 사용합니다. 고유한 MQTT 클라이언트 이름과 토픽 이름을 사용하면 다른 사람의 코드와 충돌하지 않도록 할 수 있습니다. 이 ID는 나중에 이 과제에서 서버 코드를 작성할 때도 필요합니다.

    > 💁 [GUIDGen](https://www.guidgen.com) 같은 웹사이트를 사용하여 고유 ID를 생성할 수 있습니다.

    `client_name`은 브로커에서 이 MQTT 클라이언트를 위한 고유 이름입니다.

1. MQTT 클라이언트 객체를 생성하고 MQTT 브로커에 연결하기 위해 새 코드 아래에 다음 코드를 추가합니다:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    이 코드는 클라이언트 객체를 생성하고, 공개 MQTT 브로커에 연결하며, 백그라운드 스레드에서 메시지를 수신하는 처리 루프를 시작합니다.

1. 이전 과제의 코드를 실행했던 것과 동일한 방식으로 코드를 실행합니다. 가상 IoT 장치를 사용하는 경우, CounterFit 앱이 실행 중이고 조도 센서와 LED가 올바른 핀에 생성되었는지 확인하세요.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 이 코드는 [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) 폴더 또는 [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) 폴더에서 찾을 수 있습니다.

😀 장치를 MQTT 브로커에 성공적으로 연결했습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.