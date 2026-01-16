<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-24T21:33:16+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "ko"
}
-->
# 이미지 분류하기 - Wio Terminal

이 수업의 이 부분에서는 카메라로 촬영한 이미지를 Custom Vision 서비스로 보내 분류합니다.

## 이미지 분류하기

Custom Vision 서비스는 이미지를 분류하기 위해 Wio Terminal에서 호출할 수 있는 REST API를 제공합니다. 이 REST API는 HTTPS 연결을 통해 접근할 수 있으며, 이는 보안 HTTP 연결입니다.

HTTPS 엔드포인트와 상호작용할 때, 클라이언트 코드는 접근하려는 서버로부터 공개 키 인증서를 요청하고 이를 사용해 전송 데이터를 암호화해야 합니다. 웹 브라우저는 이를 자동으로 처리하지만, 마이크로컨트롤러는 그렇지 않습니다. 인증서를 수동으로 요청하고 이를 사용해 REST API와의 보안 연결을 설정해야 합니다. 이러한 인증서는 변경되지 않으므로, 한 번 인증서를 얻으면 애플리케이션에 하드코딩할 수 있습니다.

이 인증서는 공개 키를 포함하고 있으며, 보안이 필요하지 않습니다. 소스 코드에서 사용할 수 있으며 GitHub과 같은 공개 장소에서 공유할 수 있습니다.

### 작업 - SSL 클라이언트 설정하기

1. `fruit-quality-detector` 앱 프로젝트를 열지 않았다면 열어주세요.

1. `config.h` 헤더 파일을 열고 다음을 추가하세요:

    ```cpp
    const char *CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    이것은 *Microsoft Azure DigiCert Global Root G2 인증서*입니다. 이는 전 세계적으로 많은 Azure 서비스에서 사용되는 인증서 중 하나입니다.

    > 💁 이 인증서를 사용해야 한다는 것을 확인하려면 macOS 또는 Linux에서 다음 명령을 실행하세요. Windows를 사용하는 경우 [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn)을 사용해 이 명령을 실행할 수 있습니다:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > 출력 결과는 DigiCert Global Root G2 인증서를 나열합니다.

1. `main.cpp`를 열고 다음 포함 지시문을 추가하세요:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. 포함 지시문 아래에 `WifiClientSecure` 인스턴스를 선언하세요:

    ```cpp
    WiFiClientSecure client;
    ```

    이 클래스는 HTTPS를 통해 웹 엔드포인트와 통신하는 코드를 포함합니다.

1. `connectWiFi` 메서드에서 `WifiClientSecure`를 DigiCert Global Root G2 인증서를 사용하도록 설정하세요:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### 작업 - 이미지 분류하기

1. `platformio.ini` 파일의 `lib_deps` 목록에 다음을 추가하세요:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    이는 [ArduinoJson](https://arduinojson.org)이라는 Arduino JSON 라이브러리를 가져오며, REST API의 JSON 응답을 디코딩하는 데 사용됩니다.

1. `config.h`에서 Custom Vision 서비스의 예측 URL과 키에 대한 상수를 추가하세요:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>`을 Custom Vision의 예측 URL로 바꾸세요. `<PREDICTION_KEY>`를 예측 키로 바꾸세요.

1. `main.cpp`에서 ArduinoJson 라이브러리에 대한 포함 지시문을 추가하세요:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp`에서 `buttonPressed` 함수 위에 다음 함수를 추가하세요:

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    이 코드는 먼저 REST API와 상호작용하는 메서드를 포함한 `HTTPClient`를 선언합니다. 그런 다음 Azure 공개 키를 설정한 `WiFiClientSecure` 인스턴스를 사용해 클라이언트를 예측 URL에 연결합니다.

    연결 후, 헤더를 보냅니다. 이는 REST API에 대해 수행될 요청에 대한 정보를 전달합니다. `Content-Type` 헤더는 API 호출이 원시 바이너리 데이터를 보낼 것임을 나타내고, `Prediction-Key` 헤더는 Custom Vision 예측 키를 전달합니다.

    이후 HTTP 클라이언트에 POST 요청을 보내며, 이는 카메라로 촬영한 JPEG 이미지를 포함한 바이트 배열을 업로드합니다.

    > 💁 POST 요청은 데이터를 보내고 응답을 받는 데 사용됩니다. GET 요청과 같은 다른 요청 유형은 데이터를 검색하는 데 사용됩니다. GET 요청은 웹 브라우저가 웹 페이지를 로드할 때 사용됩니다.

    POST 요청은 응답 상태 코드를 반환합니다. 이는 잘 정의된 값으로, 200은 **OK**를 의미하며 POST 요청이 성공했음을 나타냅니다.

    > 💁 모든 응답 상태 코드는 [Wikipedia의 HTTP 상태 코드 목록 페이지](https://wikipedia.org/wiki/List_of_HTTP_status_codes)에서 확인할 수 있습니다.

    200이 반환되면 HTTP 클라이언트에서 결과를 읽습니다. 이는 REST API로부터 예측 결과를 포함한 JSON 문서 형태의 텍스트 응답입니다. JSON은 다음 형식입니다:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    여기서 중요한 부분은 `predictions` 배열입니다. 이 배열은 각 태그에 대한 태그 이름과 확률을 포함한 예측을 담고 있습니다. 반환된 확률은 0-1 사이의 부동 소수점 숫자로, 0은 해당 태그와 일치할 확률이 0%임을, 1은 100%임을 나타냅니다.

    > 💁 이미지 분류기는 사용된 모든 태그에 대한 백분율을 반환합니다. 각 태그는 이미지가 해당 태그와 일치할 확률을 가집니다.

    이 JSON은 디코딩되며, 각 태그의 확률이 시리얼 모니터로 전송됩니다.

1. `buttonPressed` 함수에서 SD 카드에 저장하는 코드를 `classifyImage` 호출로 대체하거나, 이미지를 작성한 후 **버퍼를 삭제하기 전에** 추가하세요:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 SD 카드에 저장하는 코드를 대체한 경우 `setupSDCard`와 `saveToSDCard` 함수를 제거하여 코드를 정리할 수 있습니다.

1. 코드를 업로드하고 실행하세요. 카메라를 과일에 맞추고 C 버튼을 누르세요. 시리얼 모니터에서 출력 결과를 확인할 수 있습니다:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    촬영된 이미지를 확인할 수 있으며, Custom Vision의 **Predictions** 탭에서 이러한 값을 볼 수 있습니다.

    ![Custom Vision에서 익은 상태가 56.8%, 익지 않은 상태가 43.1%로 예측된 바나나](../../../../../translated_images/ko/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 이 코드는 [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 과일 품질 분류 프로그램이 성공적으로 완료되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.