<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-24T23:12:09+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "ko"
}
-->
# 인터넷을 통해 야간등 제어하기 - Wio Terminal

IoT 장치는 *test.mosquitto.org*와 MQTT를 사용하여 통신하도록 코딩되어야 합니다. 이를 통해 조도 센서의 읽기값을 포함한 원격 측정 데이터를 전송하고, LED를 제어하는 명령을 수신할 수 있습니다.

이 학습의 이번 단계에서는 Wio Terminal을 MQTT 브로커에 연결합니다.

## WiFi 및 MQTT Arduino 라이브러리 설치

MQTT 브로커와 통신하려면 Wio Terminal의 WiFi 칩을 사용하고 MQTT와 통신할 수 있는 Arduino 라이브러리를 설치해야 합니다. Arduino 장치 개발 시, 오픈 소스 코드가 포함된 다양한 라이브러리를 사용할 수 있으며, 이를 통해 광범위한 기능을 구현할 수 있습니다. Seeed는 Wio Terminal이 WiFi를 통해 통신할 수 있도록 하는 라이브러리를 제공합니다. 다른 개발자들은 MQTT 브로커와 통신할 수 있는 라이브러리를 공개했으며, 이를 장치와 함께 사용할 것입니다.

이 라이브러리들은 소스 코드 형태로 제공되며, PlatformIO에 자동으로 가져와 장치에 맞게 컴파일할 수 있습니다. 이를 통해 Arduino 프레임워크를 지원하는 모든 장치에서 라이브러리를 사용할 수 있으며, 해당 라이브러리가 필요로 하는 특정 하드웨어가 장치에 있는 경우에만 가능합니다. 일부 라이브러리, 예를 들어 Seeed WiFi 라이브러리는 특정 하드웨어에만 사용 가능합니다.

라이브러리는 전역적으로 설치되어 필요 시 컴파일하거나 특정 프로젝트에 설치할 수 있습니다. 이번 과제에서는 프로젝트에 라이브러리를 설치합니다.

✅ 라이브러리 관리 및 라이브러리 검색 및 설치 방법에 대한 자세한 내용은 [PlatformIO 라이브러리 문서](https://docs.platformio.org/en/latest/librarymanager/index.html)를 참조하세요.

### 작업 - WiFi 및 MQTT Arduino 라이브러리 설치

Arduino 라이브러리를 설치하세요.

1. VS Code에서 야간등 프로젝트를 엽니다.

1. `platformio.ini` 파일 끝에 다음을 추가하세요:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    이는 Seeed WiFi 라이브러리를 가져옵니다. `@ <number>` 구문은 라이브러리의 특정 버전을 나타냅니다.

    > 💁 `@ <number>`를 제거하면 항상 최신 버전의 라이브러리를 사용할 수 있지만, 이후 버전이 아래 코드와 호환된다는 보장은 없습니다. 여기의 코드는 해당 버전의 라이브러리로 테스트되었습니다.

    라이브러리를 추가하기 위해 필요한 작업은 이것뿐입니다. PlatformIO가 프로젝트를 빌드할 때 라이브러리의 소스 코드를 다운로드하고 프로젝트에 컴파일합니다.

1. `lib_deps`에 다음을 추가하세요:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    이는 [PubSubClient](https://github.com/knolleary/pubsubclient), Arduino MQTT 클라이언트를 가져옵니다.

## WiFi 연결

이제 Wio Terminal을 WiFi에 연결할 수 있습니다.

### 작업 - WiFi 연결

Wio Terminal을 WiFi에 연결하세요.

1. `src` 폴더에 `config.h`라는 새 파일을 만드세요. 이를 위해 `src` 폴더 또는 그 안의 `main.cpp` 파일을 선택한 후 탐색기에서 **새 파일** 버튼을 선택하세요. 이 버튼은 탐색기 위에 커서를 올려놓았을 때만 나타납니다.

    ![새 파일 버튼](../../../../../translated_images/ko/vscode-new-file-button.182702340fe6723c.webp)

1. WiFi 자격 증명을 위한 상수를 정의하는 다음 코드를 이 파일에 추가하세요:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>`를 WiFi의 SSID로 바꾸세요. `<PASSWORD>`를 WiFi 비밀번호로 바꾸세요.

1. `main.cpp` 파일을 엽니다.

1. 파일 상단에 다음 `#include` 지시문을 추가하세요:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    이는 이전에 추가한 라이브러리의 헤더 파일과 config 헤더 파일을 포함합니다. 이러한 헤더 파일은 PlatformIO가 라이브러리의 코드를 가져오도록 지시하는 데 필요합니다. 헤더 파일을 명시적으로 포함하지 않으면 일부 코드가 컴파일되지 않아 컴파일러 오류가 발생할 수 있습니다.

1. `setup` 함수 위에 다음 코드를 추가하세요:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    이 코드는 장치가 WiFi에 연결되지 않은 동안 루프를 돌며, config 헤더 파일에서 가져온 SSID와 비밀번호를 사용하여 연결을 시도합니다.

1. 핀이 구성된 후 `setup` 함수 하단에 이 함수를 호출하세요.

    ```cpp
    connectWiFi();
    ```

1. 이 코드를 장치에 업로드하여 WiFi 연결이 작동하는지 확인하세요. 시리얼 모니터에서 이를 확인할 수 있습니다.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT 연결

Wio Terminal이 WiFi에 연결되면 MQTT 브로커에 연결할 수 있습니다.

### 작업 - MQTT 연결

MQTT 브로커에 연결하세요.

1. MQTT 브로커의 연결 세부 정보를 정의하기 위해 `config.h` 파일 하단에 다음 코드를 추가하세요:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>`를 이 장치 클라이언트의 이름으로 사용될 고유 ID로 바꾸세요. 이 ID는 이후 이 장치가 게시하고 구독하는 토픽 이름에도 사용됩니다. *test.mosquitto.org* 브로커는 공개적으로 사용되며, 이 과제를 진행하는 다른 학생들도 사용합니다. 고유한 MQTT 클라이언트 이름과 토픽 이름을 사용하면 코드가 다른 사람의 코드와 충돌하지 않도록 보장할 수 있습니다. 이 ID는 이후 서버 코드를 작성할 때도 필요합니다.

    > 💁 [GUIDGen](https://www.guidgen.com)과 같은 웹사이트를 사용하여 고유 ID를 생성할 수 있습니다.

    `BROKER`는 MQTT 브로커의 URL입니다.

    `CLIENT_NAME`은 브로커에서 이 MQTT 클라이언트의 고유 이름입니다.

1. `main.cpp` 파일을 열고, `connectWiFi` 함수 아래 및 `setup` 함수 위에 다음 코드를 추가하세요:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    이 코드는 Wio Terminal WiFi 라이브러리를 사용하여 WiFi 클라이언트를 생성하고 이를 사용하여 MQTT 클라이언트를 생성합니다.

1. 이 코드 아래에 다음을 추가하세요:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    이 함수는 MQTT 브로커와의 연결을 테스트하고 연결되지 않은 경우 다시 연결합니다. 연결되지 않은 동안 루프를 돌며 config 헤더 파일에서 정의된 고유 클라이언트 이름을 사용하여 연결을 시도합니다.

    연결이 실패하면 5초 후에 다시 시도합니다.

1. `reconnectMQTTClient` 함수 아래에 다음 코드를 추가하세요:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    이 코드는 클라이언트에 MQTT 브로커를 설정하고 메시지가 수신될 때 호출되는 콜백을 설정합니다. 그런 다음 브로커에 연결을 시도합니다.

1. WiFi가 연결된 후 `setup` 함수에서 `createMQTTClient` 함수를 호출하세요.

1. `loop` 함수 전체를 다음 코드로 교체하세요:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    이 코드는 MQTT 브로커에 다시 연결하는 것으로 시작합니다. 이러한 연결은 쉽게 끊어질 수 있으므로 정기적으로 확인하고 필요 시 다시 연결하는 것이 좋습니다. 그런 다음 MQTT 클라이언트의 `loop` 메서드를 호출하여 구독된 토픽에서 들어오는 메시지를 처리합니다. 이 앱은 단일 스레드로 작동하므로 메시지를 백그라운드 스레드에서 받을 수 없으며, 네트워크 연결에서 대기 중인 메시지를 처리하기 위해 메인 스레드에서 시간을 할당해야 합니다.

    마지막으로 2초의 지연은 조도 수준이 너무 자주 전송되지 않도록 하고 장치의 전력 소비를 줄여줍니다.

1. 코드를 Wio Terminal에 업로드하고, 시리얼 모니터를 사용하여 장치가 WiFi 및 MQTT에 연결되는 것을 확인하세요.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 이 코드는 [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 장치를 MQTT 브로커에 성공적으로 연결했습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보에 대해서는 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.