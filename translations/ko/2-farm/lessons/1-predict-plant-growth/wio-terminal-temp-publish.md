<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-24T22:06:06+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "ko"
}
-->
# 온도 게시 - Wio Terminal

이 수업의 이 부분에서는 Wio Terminal이 감지한 온도 값을 MQTT를 통해 게시하여 나중에 GDD를 계산하는 데 사용할 수 있도록 합니다.

## 온도 게시하기

온도가 읽히면, MQTT를 통해 '서버' 코드로 게시할 수 있습니다. 이 서버 코드는 값을 읽고 저장하여 GDD 계산에 사용할 준비를 합니다. 마이크로컨트롤러는 기본적으로 인터넷에서 시간을 읽거나 실시간 시계를 사용해 시간을 추적하지 않으므로, 필요한 하드웨어가 있다고 가정하고 이를 수행하도록 프로그래밍해야 합니다.

이 수업에서는 간단히 하기 위해, 센서 데이터와 함께 시간을 보내지 않고, 메시지를 받을 때 서버 코드에서 시간을 추가하도록 합니다.

### 작업

장치를 프로그래밍하여 온도 데이터를 게시하세요.

1. `temperature-sensor` Wio Terminal 프로젝트를 엽니다.

1. 4강에서 했던 단계를 반복하여 MQTT에 연결하고 텔레메트리를 전송합니다. 동일한 공개 Mosquitto 브로커를 사용할 것입니다.

    이 단계는 다음과 같습니다:

    - `.ini` 파일에 Seeed WiFi 및 MQTT 라이브러리를 추가합니다.
    - WiFi에 연결하기 위한 구성 파일과 코드를 추가합니다.
    - MQTT 브로커에 연결하기 위한 코드를 추가합니다.
    - 텔레메트리를 게시하기 위한 코드를 추가합니다.

    > ⚠️ 필요하면 [MQTT 연결 지침](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md)과 [텔레메트리 전송 지침](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md)을 4강에서 참고하세요.

1. `config.h` 헤더 파일의 `CLIENT_NAME`이 이 프로젝트를 반영하는지 확인합니다:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. 텔레메트리의 경우, 조도 값을 보내는 대신 DHT 센서에서 읽은 온도 값을 JSON 문서의 `temperature`라는 속성으로 보냅니다. 이를 위해 `main.cpp`의 `loop` 함수를 변경합니다:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. 온도 값은 자주 읽을 필요가 없습니다. 짧은 시간 안에 크게 변하지 않으므로, `loop` 함수의 `delay`를 10분으로 설정합니다:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` 함수는 시간을 밀리초 단위로 받습니다. 읽기 쉽게 하기 위해 값은 계산 결과로 전달됩니다. 1초는 1,000ms, 1분은 60초이므로, 10 x (1분의 60초) x (1초의 1000ms)로 10분 지연을 설정합니다.

1. 이를 Wio Terminal에 업로드하고, 직렬 모니터를 사용하여 MQTT 브로커로 전송되는 온도를 확인합니다.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 이 코드는 [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 장치에서 텔레메트리로 온도를 성공적으로 게시했습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.