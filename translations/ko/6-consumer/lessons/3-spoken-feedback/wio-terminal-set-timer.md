<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-25T00:10:01+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "ko"
}
-->
# 타이머 설정 - Wio Terminal

이 수업의 이 부분에서는 서버리스 코드를 호출하여 음성을 이해하고, 결과를 기반으로 Wio Terminal에 타이머를 설정합니다.

## 타이머 설정

음성을 텍스트로 변환한 결과 텍스트는 서버리스 코드로 전송되어 LUIS로 처리되어야 하며, 타이머를 위한 초 단위 숫자를 반환받습니다. 이 초 단위 숫자를 사용하여 타이머를 설정할 수 있습니다.

마이크로컨트롤러는 Arduino에서 기본적으로 멀티스레드를 지원하지 않으므로, Python이나 다른 고급 언어에서 찾을 수 있는 표준 타이머 클래스가 없습니다. 대신 `loop` 함수에서 경과 시간을 측정하고 시간이 다 되었을 때 함수를 호출하는 방식으로 작동하는 타이머 라이브러리를 사용할 수 있습니다.

### 작업 - 텍스트를 서버리스 함수로 전송하기

1. VS Code에서 `smart-timer` 프로젝트를 열어둡니다. 열려 있지 않다면 프로젝트를 엽니다.

1. `config.h` 헤더 파일을 열고 함수 앱의 URL을 추가합니다:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>`을 이전 수업의 마지막 단계에서 얻은 함수 앱의 URL로 바꿉니다. 이는 함수 앱을 실행 중인 로컬 머신의 IP 주소를 가리킵니다.

1. `src` 폴더에 `language_understanding.h`라는 새 파일을 만듭니다. 이 파일은 인식된 음성을 함수 앱으로 전송하여 LUIS를 사용해 초 단위로 변환하는 클래스를 정의하는 데 사용됩니다.

1. 이 파일 상단에 다음을 추가합니다:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    필요한 헤더 파일을 포함합니다.

1. `LanguageUnderstanding`라는 클래스를 정의하고 이 클래스의 인스턴스를 선언합니다:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. 함수 앱을 호출하려면 WiFi 클라이언트를 선언해야 합니다. 클래스의 `private` 섹션에 다음을 추가합니다:

    ```cpp
    WiFiClient _client;
    ```

1. `public` 섹션에 함수 앱을 호출하는 `GetTimerDuration`이라는 메서드를 선언합니다:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` 메서드에서 함수 앱으로 보낼 JSON을 생성하는 다음 코드를 추가합니다:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    이 코드는 `GetTimerDuration` 메서드에 전달된 텍스트를 다음 JSON으로 변환합니다:

    ```json
    {
        "text" : "<text>"
    }
    ```

    여기서 `<text>`는 함수에 전달된 텍스트입니다.

1. 이 아래에 함수 앱 호출을 수행하는 다음 코드를 추가합니다:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    이 코드는 함수 앱에 POST 요청을 보내 JSON 본문을 전달하고 응답 코드를 받습니다.

1. 이 아래에 다음 코드를 추가합니다:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    이 코드는 응답 코드를 확인합니다. 응답 코드가 200(성공)인 경우 응답 본문에서 타이머 시간을 초 단위로 가져옵니다. 그렇지 않으면 오류가 시리얼 모니터에 출력되고 초 단위 시간이 0으로 설정됩니다.

1. 이 메서드 끝에 HTTP 연결을 닫고 초 단위 시간을 반환하는 다음 코드를 추가합니다:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` 파일에서 이 새 헤더를 포함합니다:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` 함수 끝에서 `GetTimerDuration` 메서드를 호출하여 타이머 시간을 가져옵니다:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    이 코드는 `SpeechToText` 클래스 호출에서 반환된 텍스트를 타이머 시간을 초 단위로 변환합니다.

### 작업 - 타이머 설정

초 단위 시간은 타이머를 설정하는 데 사용할 수 있습니다.

1. 타이머를 설정하기 위한 라이브러리를 추가하려면 `platformio.ini` 파일에 다음 라이브러리 종속성을 추가합니다:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. 이 라이브러리를 포함하기 위한 include 지시문을 `main.cpp` 파일에 추가합니다:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` 함수 위에 다음 코드를 추가합니다:

    ```cpp
    auto timer = timer_create_default();
    ```

    이 코드는 `timer`라는 타이머를 선언합니다.

1. 이 아래에 다음 코드를 추가합니다:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    이 `say` 함수는 나중에 텍스트를 음성으로 변환하지만, 지금은 전달된 텍스트를 시리얼 모니터에 출력합니다.

1. `say` 함수 아래에 다음 코드를 추가합니다:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    이 콜백 함수는 타이머가 만료되었을 때 호출됩니다. 타이머가 만료되었을 때 출력할 메시지가 전달됩니다. 타이머는 반복될 수 있으며, 이 콜백의 반환 값으로 이를 제어할 수 있습니다. 여기서는 `false`를 반환하여 타이머가 다시 실행되지 않도록 합니다.

1. `processAudio` 함수 끝에 다음 코드를 추가합니다:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    이 코드는 총 초 단위 시간을 확인하고, 0이면 함수 호출을 종료하여 타이머가 설정되지 않도록 합니다. 그런 다음 총 초 단위 시간을 분과 초로 변환합니다.

1. 이 코드 아래에 타이머가 시작될 때 출력할 메시지를 생성하는 다음 코드를 추가합니다:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. 이 아래에 타이머가 만료되었을 때 출력할 메시지를 생성하는 유사한 코드를 추가합니다:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. 이 후에 타이머 시작 메시지를 출력합니다:

    ```cpp
    say(begin_message);
    ```

1. 이 함수 끝에 타이머를 시작합니다:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    이 코드는 타이머를 트리거합니다. 타이머는 밀리초 단위로 설정되므로 총 초 단위 시간을 1,000으로 곱해 밀리초로 변환합니다. `timerExpired` 함수가 콜백으로 전달되며, `end_message`가 콜백에 전달할 인수로 전달됩니다. 이 콜백은 `void *` 인수만 받으므로 문자열이 적절히 변환됩니다.

1. 마지막으로, 타이머는 *tick*해야 하며, 이는 `loop` 함수에서 수행됩니다. `loop` 함수 끝에 다음 코드를 추가합니다:

    ```cpp
    timer.tick();
    ```

1. 이 코드를 빌드하고 Wio Terminal에 업로드한 후 시리얼 모니터를 통해 테스트합니다. 시리얼 모니터에서 `Ready`가 표시되면 C 버튼(왼쪽에 있는 전원 스위치에 가장 가까운 버튼)을 누르고 말합니다. 4초 동안의 오디오가 캡처되어 텍스트로 변환된 후 함수 앱으로 전송되고 타이머가 설정됩니다. 함수 앱이 로컬에서 실행 중인지 확인하세요.

    타이머가 시작되고 종료되는 시점을 확인할 수 있습니다.

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
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 이 코드는 [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 타이머 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.