<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-24T23:08:55+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "ko"
}
-->
# 인터넷을 통해 야간등 제어하기 - Wio Terminal

이 수업의 이 부분에서는 Wio Terminal에서 빛의 수준에 대한 텔레메트리를 MQTT 브로커로 전송합니다.

## JSON Arduino 라이브러리 설치하기

MQTT를 통해 메시지를 보내는 일반적인 방법은 JSON을 사용하는 것입니다. JSON 문서를 읽고 쓰는 작업을 더 쉽게 만들어주는 Arduino용 JSON 라이브러리가 있습니다.

### 작업

Arduino JSON 라이브러리를 설치하세요.

1. VS Code에서 야간등 프로젝트를 엽니다.

1. `platformio.ini` 파일의 `lib_deps` 목록에 다음 줄을 추가합니다:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    이는 [ArduinoJson](https://arduinojson.org)이라는 Arduino JSON 라이브러리를 가져옵니다.

## 텔레메트리 발행하기

다음 단계는 텔레메트리를 포함한 JSON 문서를 생성하고 이를 MQTT 브로커로 전송하는 것입니다.

### 작업 - 텔레메트리 발행하기

MQTT 브로커로 텔레메트리를 발행하세요.

1. MQTT 브로커를 위한 텔레메트리 토픽 이름을 정의하기 위해 `config.h` 파일 하단에 다음 코드를 추가하세요:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC`은 장치가 빛의 수준을 발행할 토픽입니다.

1. `main.cpp` 파일을 엽니다.

1. 파일 상단에 다음 `#include` 지시문을 추가하세요:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` 함수 내부에서 `delay` 바로 전에 다음 코드를 추가하세요:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    이 코드는 빛의 수준을 읽고, ArduinoJson을 사용하여 이 수준을 포함하는 JSON 문서를 생성합니다. 그런 다음 이를 문자열로 직렬화하고 MQTT 클라이언트를 통해 텔레메트리 MQTT 토픽에 발행합니다.

1. 코드를 Wio Terminal에 업로드하고, Serial Monitor를 사용하여 빛의 수준이 MQTT 브로커로 전송되는 것을 확인하세요.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 이 코드는 [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 장치에서 텔레메트리를 성공적으로 전송했습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.