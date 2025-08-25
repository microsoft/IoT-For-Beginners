<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-25T00:29:42+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "ko"
}
-->
# 음성을 텍스트로 변환 - Wio Terminal

이 수업의 이 부분에서는 음성 서비스를 사용하여 캡처된 오디오의 음성을 텍스트로 변환하는 코드를 작성합니다.

## 음성을 음성 서비스로 전송하기

오디오는 REST API를 사용하여 음성 서비스로 전송할 수 있습니다. 음성 서비스를 사용하려면 먼저 액세스 토큰을 요청한 후 해당 토큰을 사용하여 REST API에 액세스해야 합니다. 이러한 액세스 토큰은 10분 후에 만료되므로 항상 최신 상태를 유지하기 위해 정기적으로 토큰을 요청해야 합니다.

### 작업 - 액세스 토큰 가져오기

1. `smart-timer` 프로젝트를 열지 않았다면 열어주세요.

1. `platformio.ini` 파일에 WiFi에 액세스하고 JSON을 처리하기 위한 다음 라이브러리 종속성을 추가하세요:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. `config.h` 헤더 파일에 다음 코드를 추가하세요:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>`와 `<PASSWORD>`를 WiFi에 대한 관련 값으로 바꿉니다.

    `<API_KEY>`를 음성 서비스 리소스에 대한 API 키로 바꿉니다. `<LOCATION>`을 음성 서비스 리소스를 생성할 때 사용한 위치로 바꿉니다.

    `<LANGUAGE>`를 사용할 언어의 로케일 이름으로 바꿉니다. 예를 들어 영어의 경우 `en-GB`, 광둥어의 경우 `zn-HK`를 사용합니다. 지원되는 언어와 로케일 이름 목록은 [Microsoft 문서의 언어 및 음성 지원 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)에서 확인할 수 있습니다.

    `TOKEN_URL` 상수는 위치를 제외한 토큰 발급자의 URL입니다. 이는 나중에 위치와 결합하여 전체 URL을 생성합니다.

1. Custom Vision에 연결하는 것과 마찬가지로, 토큰 발급 서비스에 연결하려면 HTTPS 연결을 사용해야 합니다. `config.h` 끝에 다음 코드를 추가하세요:

    ```cpp
    const char *TOKEN_CERTIFICATE =
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

    이는 Custom Vision에 연결할 때 사용한 것과 동일한 인증서입니다.

1. `main.cpp` 파일 상단에 WiFi 헤더 파일과 config 헤더 파일을 포함하세요:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `setup` 함수 위에 `main.cpp`에 WiFi에 연결하는 코드를 추가하세요:

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

1. 직렬 연결이 설정된 후 `setup` 함수에서 이 함수를 호출하세요:

    ```cpp
    connectWiFi();
    ```

1. `src` 폴더에 `speech_to_text.h`라는 새 헤더 파일을 생성하세요. 이 헤더 파일에 다음 코드를 추가하세요:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    이는 HTTP 연결, 구성 및 `mic.h` 헤더 파일에 필요한 헤더 파일을 포함하며, `SpeechToText`라는 클래스를 정의한 후 나중에 사용할 수 있는 해당 클래스의 인스턴스를 선언합니다.

1. 이 클래스의 `private` 섹션에 다음 두 필드를 추가하세요:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client`는 HTTPS를 사용하는 WiFi 클라이언트로, 액세스 토큰을 가져오는 데 사용됩니다. 이 토큰은 `_access_token`에 저장됩니다.

1. `private` 섹션에 다음 메서드를 추가하세요:

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    이 코드는 음성 리소스의 위치를 사용하여 토큰 발급 API의 URL을 생성합니다. 그런 다음 인증서를 사용하여 구성된 WiFi 클라이언트를 사용하여 웹 요청을 수행하는 `HTTPClient`를 생성합니다. API 키를 호출 헤더로 설정합니다. 그런 다음 인증서를 가져오기 위해 POST 요청을 수행하며, 오류가 발생하면 재시도합니다. 마지막으로 액세스 토큰이 반환됩니다.

1. `public` 섹션에 액세스 토큰을 가져오는 메서드를 추가하세요. 이는 이후 수업에서 텍스트를 음성으로 변환하는 데 필요합니다.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` 섹션에 토큰 클라이언트를 설정하는 `init` 메서드를 추가하세요:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    이는 WiFi 클라이언트에 인증서를 설정한 후 액세스 토큰을 가져옵니다.

1. `main.cpp`에 이 새 헤더 파일을 포함 지시문에 추가하세요:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup` 함수 끝에서 `mic.init` 호출 후 직렬 모니터에 `Ready`가 쓰여지기 전에 `SpeechToText` 클래스를 초기화하세요:

    ```cpp
    speechToText.init();
    ```

### 작업 - 플래시 메모리에서 오디오 읽기

1. 이전 수업에서 오디오는 플래시 메모리에 기록되었습니다. 이 오디오는 Speech Services REST API로 전송되어야 하므로 플래시 메모리에서 읽어야 합니다. 메모리 내 버퍼에 로드할 수 없으므로 너무 큽니다. REST 호출을 수행하는 `HTTPClient` 클래스는 Arduino Stream을 사용하여 데이터를 스트리밍할 수 있습니다. 이는 데이터를 작은 청크로 로드하여 요청의 일부로 한 번에 하나씩 전송할 수 있는 클래스입니다. 스트림에서 `read`를 호출할 때마다 다음 데이터 블록이 반환됩니다. Arduino 스트림을 생성하여 플래시 메모리에서 데이터를 읽을 수 있습니다. `src` 폴더에 `flash_stream.h`라는 새 파일을 생성하고 다음 코드를 추가하세요:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    이는 Arduino `Stream` 클래스를 상속받는 `FlashStream` 클래스를 선언합니다. 이는 추상 클래스이며, 파생 클래스는 인스턴스화되기 전에 몇 가지 메서드를 구현해야 하며, 이러한 메서드는 이 클래스에서 정의됩니다.

    ✅ Arduino Streams에 대한 자세한 내용은 [Arduino Stream 문서](https://www.arduino.cc/reference/en/language/functions/communication/stream/)를 참조하세요.

1. `private` 섹션에 다음 필드를 추가하세요:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    이는 플래시 메모리에서 읽은 데이터를 저장하기 위한 임시 버퍼와 플래시 메모리에서 읽을 현재 주소 및 플래시 메모리 장치를 저장하기 위한 필드를 정의합니다.

1. `private` 섹션에 다음 메서드를 추가하세요:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    이 코드는 현재 주소에서 플래시 메모리를 읽고 데이터를 버퍼에 저장합니다. 그런 다음 주소를 증가시켜 다음 호출이 메모리의 다음 블록을 읽습니다. 버퍼는 REST API에 한 번에 전송할 HTTPClient의 가장 큰 청크 크기를 기준으로 크기가 설정됩니다.

    > 💁 플래시 메모리를 지우는 작업은 그레인 크기를 사용해야 하지만, 읽는 작업은 그렇지 않습니다.

1. 이 클래스의 `public` 섹션에 생성자를 추가하세요:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    이 생성자는 플래시 메모리 블록의 시작부터 읽기를 시작하도록 모든 필드를 설정하고 첫 번째 데이터 청크를 버퍼에 로드합니다.

1. `write` 메서드를 구현하세요. 이 스트림은 데이터만 읽으므로 아무 작업도 수행하지 않고 0을 반환할 수 있습니다:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek` 메서드를 구현하세요. 이는 스트림을 이동하지 않고 현재 위치의 데이터를 반환합니다. 스트림에서 데이터를 읽지 않는 한 `peek`를 여러 번 호출해도 항상 동일한 데이터를 반환합니다.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available` 함수를 구현하세요. 이는 스트림에서 읽을 수 있는 바이트 수를 반환하거나 스트림이 완료되면 -1을 반환합니다. 이 클래스의 경우 최대 사용 가능 크기는 HTTPClient의 청크 크기를 초과하지 않습니다. 이 스트림이 HTTP 클라이언트에서 사용되면 HTTP 클라이언트는 이 함수를 호출하여 사용 가능한 데이터 양을 확인한 다음 해당 데이터를 요청하여 REST API로 전송합니다. 각 청크가 HTTP 클라이언트의 청크 크기를 초과하지 않도록 해야 하므로 사용 가능한 데이터가 청크 크기보다 많으면 청크 크기가 반환됩니다. 적으면 사용 가능한 데이터가 반환됩니다. 모든 데이터가 스트리밍되면 -1이 반환됩니다.

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. `read` 메서드를 구현하여 버퍼에서 다음 바이트를 반환하고 위치를 증가시킵니다. 위치가 버퍼 크기를 초과하면 플래시 메모리에서 다음 블록으로 버퍼를 채우고 위치를 재설정합니다.

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. `speech_to_text.h` 헤더 파일에 이 새 헤더 파일에 대한 포함 지시문을 추가하세요:

    ```cpp
    #include "flash_stream.h"
    ```

### 작업 - 음성을 텍스트로 변환하기

1. 음성은 REST API를 통해 음성 서비스로 오디오를 전송하여 텍스트로 변환할 수 있습니다. 이 REST API는 토큰 발급자와 다른 인증서를 사용하므로 `config.h` 헤더 파일에 다음 코드를 추가하여 이 인증서를 정의하세요:

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. 이 파일에 위치를 제외한 음성 URL에 대한 상수를 추가하세요. 이는 나중에 위치와 언어와 결합하여 전체 URL을 생성합니다.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` 헤더 파일에서 `SpeechToText` 클래스의 `private` 섹션에 음성 인증서를 사용하는 WiFi 클라이언트에 대한 필드를 정의하세요:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` 메서드에서 이 WiFi 클라이언트에 인증서를 설정하세요:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText` 클래스의 `public` 섹션에 음성을 텍스트로 변환하는 메서드를 정의하는 다음 코드를 추가하세요:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. 이 메서드에 음성 인증서로 구성된 WiFi 클라이언트를 사용하여 HTTP 클라이언트를 생성하고 위치와 언어로 설정된 음성 URL을 사용하는 다음 코드를 추가하세요:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. 연결에 대한 몇 가지 헤더를 설정해야 합니다:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    이는 액세스 토큰을 사용한 인증, 샘플 속도를 사용한 오디오 형식, 클라이언트가 결과를 JSON으로 기대한다는 설정을 헤더로 설정합니다.

1. 이 후 REST API 호출을 수행하는 다음 코드를 추가하세요:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    이는 `FlashStream`을 생성하고 이를 사용하여 데이터를 REST API로 스트리밍합니다.

1. 아래에 다음 코드를 추가하세요:

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    이 코드는 응답 코드를 확인합니다.

    응답 코드가 성공을 나타내는 200인 경우 결과를 가져와 JSON에서 디코딩하고 `DisplayText` 속성을 `text` 변수에 설정합니다. 이 속성은 음성의 텍스트 버전이 반환되는 속성입니다.

    응답 코드가 401인 경우 액세스 토큰이 만료된 것입니다(이 토큰은 10분 동안만 유효). 새 액세스 토큰을 요청하고 호출을 다시 수행합니다.

    그렇지 않으면 직렬 모니터에 오류를 보내고 `text`는 비어 있는 상태로 유지됩니다.

1. 이 메서드 끝에 HTTP 클라이언트를 닫고 텍스트를 반환하는 다음 코드를 추가하세요:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp`에서 새 `convertSpeechToText` 메서드를 `processAudio` 함수에서 호출한 후 직렬 모니터에 음성을 로그로 출력하세요:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. 이 코드를 빌드하고 Wio Terminal에 업로드한 후 직렬 모니터를 통해 테스트하세요. 직렬 모니터에서 `Ready`를 확인한 후 C 버튼(왼쪽에 있는 버튼, 전원 스위치에 가장 가까운 버튼)을 누르고 말하세요. 4초 동안 오디오가 캡처된 후 텍스트로 변환됩니다.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    ```

> 💁 이 코드는 [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 음성을 텍스트로 변환하는 프로그램이 성공적으로 완료되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.