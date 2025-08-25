<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-24T23:00:35+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "ko"
}
-->
# 인터넷을 통해 야간등 제어하기 - 가상 IoT 하드웨어와 Raspberry Pi

이 수업의 이번 부분에서는 MQTT 브로커에서 Raspberry Pi 또는 가상 IoT 장치로 전송된 명령을 구독하게 됩니다.

## 명령 구독하기

다음 단계는 MQTT 브로커에서 전송된 명령을 구독하고 이에 응답하는 것입니다.

### 작업

명령을 구독하세요.

1. VS Code에서 야간등 프로젝트를 엽니다.

1. 가상 IoT 장치를 사용하는 경우, 터미널이 가상 환경을 실행 중인지 확인하세요. Raspberry Pi를 사용하는 경우에는 가상 환경을 사용하지 않습니다.

1. `client_telemetry_topic` 정의 이후에 다음 코드를 추가하세요:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic`은 장치가 LED 명령을 받기 위해 구독할 MQTT 토픽입니다.

1. `mqtt_client.loop_start()` 줄 바로 아래, 메인 루프 위에 다음 코드를 추가하세요:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    이 코드는 메시지를 JSON 문서로 읽고 `led_on` 속성의 값을 찾는 `handle_command`라는 함수를 정의합니다. 값이 `True`로 설정되어 있으면 LED가 켜지고, 그렇지 않으면 꺼집니다.

    MQTT 클라이언트는 서버가 메시지를 보낼 토픽을 구독하고, 메시지가 수신될 때 호출될 `handle_command` 함수를 설정합니다.

    > 💁 `on_message` 핸들러는 구독된 모든 토픽에 대해 호출됩니다. 나중에 여러 토픽을 듣는 코드를 작성할 경우, 핸들러 함수에 전달된 `message` 객체에서 메시지가 전송된 토픽을 가져올 수 있습니다.

1. 이전 과제의 코드 실행 방식과 동일하게 코드를 실행하세요. 가상 IoT 장치를 사용하는 경우, CounterFit 앱이 실행 중이며 올바른 핀에 광 센서와 LED가 생성되었는지 확인하세요.

1. 물리적 또는 가상 장치에서 감지된 광 수준을 조정하세요. 수신된 메시지와 전송된 명령이 터미널에 기록됩니다. 또한 광 수준에 따라 LED가 켜지고 꺼질 것입니다.

> 💁 이 코드는 [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) 폴더 또는 [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) 폴더에서 찾을 수 있습니다.

😀 MQTT 브로커에서 전송된 명령에 응답하도록 장치를 성공적으로 코딩했습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.