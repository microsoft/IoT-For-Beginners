<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-24T22:49:26+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "ko"
}
-->
# IoT 디바이스를 클라우드에 연결하기 - 가상 IoT 하드웨어와 Raspberry Pi

이 수업의 이번 부분에서는 가상 IoT 디바이스 또는 Raspberry Pi를 IoT Hub에 연결하여 텔레메트리를 전송하고 명령을 수신합니다.

## 디바이스를 IoT Hub에 연결하기

다음 단계는 디바이스를 IoT Hub에 연결하는 것입니다.

### 작업 - IoT Hub에 연결하기

1. VS Code에서 `soil-moisture-sensor` 폴더를 엽니다. 가상 IoT 디바이스를 사용하는 경우 터미널에서 가상 환경이 실행 중인지 확인하세요.

1. 추가 Pip 패키지를 설치합니다:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device`는 IoT Hub와 통신하기 위한 라이브러리입니다.

1. 기존 import 아래에 `app.py` 파일 상단에 다음 import를 추가하세요:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    이 코드는 IoT Hub와 통신하기 위한 SDK를 가져옵니다.

1. 더 이상 필요하지 않은 `import paho.mqtt.client as mqtt` 줄을 제거하세요. MQTT 코드 전체를 제거하며, 여기에는 토픽 이름, `mqtt_client`를 사용하는 모든 코드, 그리고 `handle_command`가 포함됩니다. `while True:` 루프는 유지하되, 이 루프에서 `mqtt_client.publish` 줄만 삭제하세요.

1. import 문 아래에 다음 코드를 추가하세요:

    ```python
    connection_string = "<connection string>"
    ```

    `<connection string>`을 이전 수업에서 디바이스를 위해 가져온 연결 문자열로 바꾸세요.

    > 💁 이것은 최선의 방법이 아닙니다. 연결 문자열은 소스 코드에 저장되어서는 안 됩니다. 이는 소스 코드 관리에 체크인될 수 있으며 누구나 찾을 수 있습니다. 여기서는 간단함을 위해 이렇게 하고 있습니다. 이상적으로는 환경 변수와 [`python-dotenv`](https://pypi.org/project/python-dotenv/) 같은 도구를 사용하는 것이 좋습니다. 다음 수업에서 이에 대해 더 배우게 될 것입니다.

1. 이 코드 아래에 IoT Hub와 통신할 수 있는 디바이스 클라이언트 객체를 생성하고 연결하는 다음 코드를 추가하세요:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. 이 코드를 실행하세요. 디바이스가 연결되는 것을 볼 수 있습니다.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## 텔레메트리 전송하기

디바이스가 연결되었으니 이제 MQTT 브로커 대신 IoT Hub로 텔레메트리를 전송할 수 있습니다.

### 작업 - 텔레메트리 전송하기

1. `while True` 루프 안에서 sleep 바로 전에 다음 코드를 추가하세요:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    이 코드는 토양 습도 읽기를 JSON 문자열로 포함하는 IoT Hub `Message`를 생성하고, 이를 디바이스에서 클라우드로 메시지로 IoT Hub에 전송합니다.

## 명령 처리하기

디바이스는 서버 코드에서 릴레이를 제어하기 위한 명령을 처리해야 합니다. 이는 직접 메서드 요청으로 전송됩니다.

## 작업 - 직접 메서드 요청 처리하기

1. `while True` 루프 전에 다음 코드를 추가하세요:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    이 코드는 IoT Hub에서 직접 메서드가 호출될 때 호출되는 `handle_method_request` 메서드를 정의합니다. 각 직접 메서드에는 이름이 있으며, 이 코드는 릴레이를 켜기 위한 `relay_on` 메서드와 릴레이를 끄기 위한 `relay_off` 메서드를 기대합니다.

    > 💁 이는 단일 직접 메서드 요청으로도 구현할 수 있습니다. 요청 객체에서 사용할 수 있는 페이로드에 릴레이의 원하는 상태를 전달할 수 있습니다.

1. 직접 메서드는 호출 코드에 요청이 처리되었음을 알리는 응답이 필요합니다. `handle_method_request` 함수 끝에 다음 코드를 추가하여 요청에 대한 응답을 생성하세요:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    이 코드는 HTTP 상태 코드 200을 포함한 직접 메서드 요청에 대한 응답을 생성하여 IoT Hub로 다시 전송합니다.

1. 이 함수 정의 아래에 다음 코드를 추가하세요:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    이 코드는 직접 메서드가 호출될 때 IoT Hub 클라이언트가 `handle_method_request` 함수를 호출하도록 지시합니다.

> 💁 이 코드는 [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) 또는 [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) 폴더에서 찾을 수 있습니다.

😀 이제 토양 습도 센서 프로그램이 IoT Hub에 연결되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.