<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-24T21:47:20+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "ko"
}
-->
# IoT Edge 기반 이미지 분류기를 사용하여 이미지 분류하기 - Wio Terminal

이 수업의 이 부분에서는 IoT Edge 장치에서 실행되는 이미지 분류기를 사용하게 됩니다.

## IoT Edge 분류기 사용하기

IoT 장치는 IoT Edge 이미지 분류기를 사용하도록 재설정할 수 있습니다. 이미지 분류기의 URL은 `http://<IP 주소 또는 이름>/image`이며, `<IP 주소 또는 이름>`을 IoT Edge를 실행 중인 컴퓨터의 IP 주소 또는 호스트 이름으로 대체합니다.

### 작업 - IoT Edge 분류기 사용하기

1. `fruit-quality-detector` 앱 프로젝트가 아직 열려 있지 않다면 열어주세요.

1. 이미지 분류기는 HTTPS가 아닌 HTTP를 사용하는 REST API로 실행되므로, HTTP 호출만 가능한 WiFi 클라이언트를 사용해야 합니다. 따라서 인증서가 필요하지 않습니다. `config.h` 파일에서 `CERTIFICATE`를 삭제하세요.

1. `config.h` 파일의 예측 URL을 새 URL로 업데이트해야 합니다. 또한 `PREDICTION_KEY`는 필요하지 않으므로 삭제할 수 있습니다.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>`을 분류기의 URL로 대체하세요.

1. `main.cpp`에서 WiFi Client Secure에 대한 포함 지시문을 표준 HTTP 버전으로 변경하세요:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient` 선언을 HTTP 버전으로 변경하세요:

    ```cpp
    WiFiClient client;
    ```

1. WiFi 클라이언트에서 인증서를 설정하는 줄을 선택하세요. `connectWiFi` 함수에서 `client.setCACert(CERTIFICATE);` 줄을 제거하세요.

1. `classifyImage` 함수에서 헤더에 예측 키를 설정하는 `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` 줄을 제거하세요.

1. 코드를 업로드하고 실행하세요. 카메라를 과일에 맞추고 C 버튼을 누르세요. 시리얼 모니터에서 출력 결과를 확인할 수 있습니다:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 이 코드는 [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 과일 품질 분류기 프로그램이 성공적으로 실행되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.