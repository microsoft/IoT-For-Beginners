<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-24T23:13:10+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "ko"
}
-->
# 인터넷을 통해 야간등 제어하기 - Wio Terminal

이 수업의 이 부분에서는 MQTT 브로커에서 Wio Terminal로 전송된 명령을 구독하게 됩니다.

## 명령 구독하기

다음 단계는 MQTT 브로커에서 전송된 명령을 구독하고 이에 응답하는 것입니다.

### 작업

명령을 구독하세요.

1. VS Code에서 야간등 프로젝트를 엽니다.

1. `config.h` 파일의 맨 아래에 다음 코드를 추가하여 명령에 대한 토픽 이름을 정의합니다:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC`은 장치가 LED 명령을 받기 위해 구독할 토픽입니다.

1. MQTT 클라이언트가 다시 연결될 때 명령 토픽을 구독하도록 `reconnectMQTTClient` 함수 끝에 다음 줄을 추가합니다:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. `reconnectMQTTClient` 함수 아래에 다음 코드를 추가합니다:

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    이 함수는 MQTT 클라이언트가 서버로부터 메시지를 받을 때 호출되는 콜백 함수입니다.

    메시지는 부호 없는 8비트 정수 배열로 수신되며, 텍스트로 처리하기 위해 문자 배열로 변환해야 합니다.

    메시지에는 JSON 문서가 포함되어 있으며, ArduinoJson 라이브러리를 사용하여 디코딩됩니다. JSON 문서의 `led_on` 속성을 읽고, 값에 따라 LED를 켜거나 끕니다.

1. `createMQTTClient` 함수에 다음 코드를 추가합니다:

    ```cpp
    client.setCallback(clientCallback);
    ```

    이 코드는 MQTT 브로커에서 메시지를 받을 때 호출될 콜백으로 `clientCallback`을 설정합니다.

    > 💁 `clientCallback` 핸들러는 구독된 모든 토픽에 대해 호출됩니다. 나중에 여러 토픽을 듣는 코드를 작성할 경우, 콜백 함수에 전달된 `topic` 매개변수를 통해 메시지가 전송된 토픽을 확인할 수 있습니다.

1. 코드를 Wio Terminal에 업로드하고, Serial Monitor를 사용하여 MQTT 브로커로 전송되는 조도 수준을 확인하세요.

1. 물리적 또는 가상 장치에서 감지된 조도 수준을 조정하세요. 터미널에서 메시지가 수신되고 명령이 전송되는 것을 볼 수 있습니다. 또한 조도 수준에 따라 LED가 켜지고 꺼지는 것을 확인할 수 있습니다.

> 💁 이 코드는 [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 MQTT 브로커에서 전송된 명령에 응답하도록 장치를 성공적으로 코딩했습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.