<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-24T22:57:54+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "ko"
}
-->
# X.509 인증서를 사용하여 디바이스 코드 연결 - 가상 IoT 하드웨어 및 Raspberry Pi

이 강의의 이 부분에서는 가상 IoT 디바이스 또는 Raspberry Pi를 X.509 인증서를 사용하여 IoT Hub에 연결합니다.

## 디바이스를 IoT Hub에 연결하기

다음 단계는 X.509 인증서를 사용하여 디바이스를 IoT Hub에 연결하는 것입니다.

### 작업 - IoT Hub에 연결하기

1. 키와 인증서 파일을 IoT 디바이스 코드가 포함된 폴더에 복사합니다. VS Code Remote SSH를 통해 Raspberry Pi를 사용하고 PC나 Mac에서 키를 생성한 경우, 파일을 VS Code의 탐색기에 드래그 앤 드롭하여 복사할 수 있습니다.

1. `app.py` 파일을 엽니다.

1. X.509 인증서를 사용하여 연결하려면 IoT Hub의 호스트 이름과 X.509 인증서가 필요합니다. 디바이스 클라이언트를 생성하기 전에 다음 코드를 추가하여 호스트 이름을 포함하는 변수를 생성하세요:

    ```python
    host_name = "<host_name>"
    ```

    `<host_name>`을 IoT Hub의 호스트 이름으로 바꿉니다. 이는 `connection_string`의 `HostName` 섹션에서 확인할 수 있습니다. IoT Hub의 이름이며 `.azure-devices.net`으로 끝납니다.

1. 이 아래에 디바이스 ID를 포함하는 변수를 선언하세요:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. X.509 파일을 포함하는 `X509` 클래스의 인스턴스가 필요합니다. `azure.iot.device` 모듈에서 가져오는 클래스 목록에 `X509`를 추가하세요:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. 인증서와 키 파일을 사용하여 `X509` 클래스 인스턴스를 생성합니다. 이를 위해 `host_name` 선언 아래에 다음 코드를 추가하세요:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    이는 이전에 생성한 `soil-moisture-sensor-x509-cert.pem` 및 `soil-moisture-sensor-x509-key.pem` 파일을 사용하여 `X509` 클래스를 생성합니다.

1. 연결 문자열에서 `device_client`를 생성하는 코드를 다음 코드로 교체하세요:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    이는 연결 문자열 대신 X.509 인증서를 사용하여 연결합니다.

1. `connection_string` 변수를 포함한 줄을 삭제하세요.

1. 코드를 실행하세요. IoT Hub로 전송된 메시지를 모니터링하고 이전과 같이 직접 메서드 요청을 전송하세요. 디바이스가 연결되고 토양 수분 데이터를 전송하며 직접 메서드 요청을 수신하는 것을 확인할 수 있습니다.

> 💁 이 코드는 [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) 또는 [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) 폴더에서 확인할 수 있습니다.

😀 이제 토양 수분 센서 프로그램이 X.509 인증서를 사용하여 IoT Hub에 연결되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서(원어로 작성된 문서)를 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생할 수 있는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.  