<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-24T22:51:12+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "ko"
}
-->
# IoT 디바이스를 클라우드에 연결하기 - Wio Terminal

이 강의의 이번 단계에서는 Wio Terminal을 IoT Hub에 연결하여 텔레메트리를 전송하고 명령을 수신하는 방법을 배웁니다.

## 디바이스를 IoT Hub에 연결하기

다음 단계는 디바이스를 IoT Hub에 연결하는 것입니다.

### 작업 - IoT Hub에 연결하기

1. VS Code에서 `soil-moisture-sensor` 프로젝트를 엽니다.

1. `platformio.ini` 파일을 열고, `knolleary/PubSubClient` 라이브러리 의존성을 제거합니다. 이 라이브러리는 공용 MQTT 브로커에 연결하기 위해 사용되었으며, IoT Hub에 연결하는 데는 필요하지 않습니다.

1. 다음 라이브러리 의존성을 추가합니다:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` 라이브러리는 Wio Terminal의 실시간 시계를 제어하는 코드를 제공합니다. 나머지 라이브러리는 IoT 디바이스가 IoT Hub에 연결할 수 있도록 합니다.

1. `platformio.ini` 파일 하단에 다음을 추가합니다:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    이는 Arduino IoT Hub 코드를 컴파일할 때 필요한 컴파일러 플래그를 설정합니다.

1. `config.h` 헤더 파일을 열고, 모든 MQTT 설정을 제거한 뒤 디바이스 연결 문자열에 대한 다음 상수를 추가합니다:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>`을 이전에 복사한 디바이스의 연결 문자열로 대체하세요.

1. IoT Hub에 연결하려면 시간 기반 토큰이 필요합니다. 따라서 IoT 디바이스는 현재 시간을 알아야 합니다. Windows, macOS, Linux와 같은 운영 체제와 달리, 마이크로컨트롤러는 인터넷을 통해 자동으로 현재 시간을 동기화하지 않습니다. 따라서 [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) 서버에서 현재 시간을 가져오는 코드를 추가해야 합니다. 가져온 시간은 Wio Terminal의 실시간 시계에 저장되어, 디바이스가 전원을 잃지 않는 한 나중에 올바른 시간을 요청할 수 있습니다. `ntp.h`라는 새 파일을 생성하고 다음 코드를 추가하세요:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    이 코드는 강의 범위를 벗어납니다. NTP 서버에서 현재 시간을 가져와 Wio Terminal의 시계를 설정하는 `initTime`이라는 함수를 정의합니다.

1. `main.cpp` 파일을 열고, `PubSubClient.h` 헤더 파일, `PubSubClient` 변수 선언, `reconnectMQTTClient` 및 `createMQTTClient` 메서드, 그리고 이 변수와 메서드에 대한 모든 호출을 포함한 모든 MQTT 코드를 제거합니다. 이 파일에는 WiFi에 연결하고, 토양 습도를 가져오고, 이를 JSON 문서로 생성하는 코드만 포함되어야 합니다.

1. IoT Hub 라이브러리와 시간을 설정하기 위한 헤더 파일을 포함하려면, `main.cpp` 파일 상단에 다음 `#include` 지시문을 추가하세요:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. 현재 시간을 설정하려면 `setup` 함수 끝에 다음 호출을 추가하세요:

    ```cpp
    initTime();
    ```

1. 파일 상단의 include 지시문 바로 아래에 다음 변수 선언을 추가하세요:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    이는 IoT Hub에 대한 연결 핸들인 `IOTHUB_DEVICE_CLIENT_LL_HANDLE`을 선언합니다.

1. 그 아래에 다음 코드를 추가하세요:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    이는 IoT Hub에 연결 상태가 변경될 때 호출되는 콜백 함수를 선언합니다. 연결 상태는 시리얼 포트로 전송됩니다.

1. 그 아래에 IoT Hub에 연결하는 함수를 추가하세요:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    이 코드는 IoT Hub 라이브러리 코드를 초기화한 다음, `config.h` 헤더 파일의 연결 문자열을 사용하여 연결을 생성합니다. 이 연결은 MQTT를 기반으로 합니다. 연결이 실패하면 시리얼 포트로 전송됩니다. 출력에서 이를 확인하면 연결 문자열을 확인하세요. 마지막으로 연결 상태 콜백이 설정됩니다.

1. 이 함수를 `setup` 함수에서 `initTime` 호출 아래에 추가하세요:

    ```cpp
    connectIoTHub();
    ```

1. MQTT 클라이언트와 마찬가지로, 이 코드는 단일 스레드에서 실행되므로 허브에서 보내고 허브로 보내는 메시지를 처리할 시간이 필요합니다. 이를 위해 `loop` 함수 상단에 다음을 추가하세요:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. 코드를 빌드하고 업로드하세요. 시리얼 모니터에서 연결을 확인할 수 있습니다:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    출력에서 NTP 시간이 가져온 후 디바이스 클라이언트가 연결되는 것을 볼 수 있습니다. 연결에는 몇 초가 걸릴 수 있으므로, 디바이스가 연결되는 동안 출력에서 토양 습도를 볼 수 있습니다.

    > 💁 NTP의 UNIX 시간을 [unixtimestamp.com](https://www.unixtimestamp.com)과 같은 웹사이트를 사용하여 더 읽기 쉬운 형식으로 변환할 수 있습니다.

## 텔레메트리 전송

이제 디바이스가 연결되었으므로, MQTT 브로커 대신 IoT Hub로 텔레메트리를 전송할 수 있습니다.

### 작업 - 텔레메트리 전송

1. `setup` 함수 위에 다음 함수를 추가하세요:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    이 코드는 전달된 문자열을 기반으로 IoT Hub 메시지를 생성하고, 이를 허브로 전송한 뒤 메시지 객체를 정리합니다.

1. 이 코드를 `loop` 함수에서 텔레메트리를 시리얼 포트로 전송하는 줄 바로 뒤에 호출하세요:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## 명령 처리

디바이스는 서버 코드에서 릴레이를 제어하기 위한 명령을 처리해야 합니다. 이는 직접 메서드 요청으로 전송됩니다.

### 작업 - 직접 메서드 요청 처리

1. `connectIoTHub` 함수 앞에 다음 코드를 추가하세요:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    이 코드는 IoT Hub 라이브러리가 직접 메서드 요청을 받을 때 호출할 수 있는 콜백 메서드를 정의합니다. 요청된 메서드는 `method_name` 매개변수로 전달됩니다. 이 함수는 호출된 메서드를 시리얼 포트에 출력한 뒤, 메서드 이름에 따라 릴레이를 켜거나 끕니다.

    > 💁 이 작업은 단일 직접 메서드 요청으로 구현할 수도 있으며, 요청과 함께 전달되는 페이로드를 사용하여 릴레이의 원하는 상태를 전달할 수 있습니다. 이 페이로드는 `payload` 매개변수에서 사용할 수 있습니다.

1. `directMethodCallback` 함수 끝에 다음 코드를 추가하세요:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    직접 메서드 요청은 텍스트로 된 응답과 반환 코드를 포함한 응답이 필요합니다. 이 코드는 다음 JSON 문서로 결과를 생성합니다:

    ```JSON
    {
        "Result": ""
    }
    ```

    그런 다음 이 결과를 `response` 매개변수에 복사하고, 응답 크기를 `response_size` 매개변수에 설정합니다. 이 코드는 메서드가 올바르게 처리되었음을 나타내기 위해 `IOTHUB_CLIENT_OK`를 반환합니다.

1. 다음 코드를 `connectIoTHub` 함수 끝에 추가하여 콜백을 연결하세요:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` 함수는 IoT Hub에서 전송한 이벤트를 처리하기 위해 `IoTHubDeviceClient_LL_DoWork` 함수를 호출합니다. 이는 `delay`로 인해 10초마다 한 번만 호출되므로, 직접 메서드는 10초마다 한 번만 처리됩니다. 이를 더 효율적으로 만들기 위해, 10초 지연을 더 짧은 지연으로 나누고, 각 지연마다 `IoTHubDeviceClient_LL_DoWork`를 호출할 수 있습니다. 이를 위해 `loop` 함수 위에 다음 코드를 추가하세요:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    이 코드는 반복적으로 루프를 실행하며, 매번 `IoTHubDeviceClient_LL_DoWork`를 호출하고 100ms 동안 지연합니다. 이는 주어진 `delay_time` 매개변수만큼 지연하기 위해 필요한 만큼 반복됩니다. 이로 인해 디바이스는 직접 메서드 요청을 처리하기 위해 최대 100ms만 대기합니다.

1. `loop` 함수에서 `IoTHubDeviceClient_LL_DoWork` 호출을 제거하고, `delay(10000)` 호출을 다음 코드로 대체하세요:

    ```cpp
    work_delay(10000);
    ```

> 💁 이 코드는 [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) 폴더에서 확인할 수 있습니다.

😀 이제 토양 습도 센서 프로그램이 IoT Hub에 연결되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.