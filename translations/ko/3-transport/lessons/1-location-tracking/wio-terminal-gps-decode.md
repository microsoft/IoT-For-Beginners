<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T00:55:08+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "ko"
}
-->
# GPS 데이터 디코딩 - Wio Terminal

이 수업의 이번 부분에서는 Wio Terminal의 GPS 센서에서 읽은 NMEA 메시지를 디코딩하고 위도와 경도를 추출합니다.

## GPS 데이터 디코딩

시리얼 포트에서 원시 NMEA 데이터를 읽은 후, 오픈 소스 NMEA 라이브러리를 사용하여 디코딩할 수 있습니다.

### 작업 - GPS 데이터 디코딩

장치를 프로그래밍하여 GPS 데이터를 디코딩하세요.

1. `gps-sensor` 앱 프로젝트가 열려 있지 않다면 열어주세요.

1. 프로젝트의 `platformio.ini` 파일에 [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) 라이브러리 의존성을 추가하세요. 이 라이브러리는 NMEA 데이터를 디코딩하는 코드를 포함하고 있습니다.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` 파일에 TinyGPSPlus 라이브러리를 포함하는 지시문을 추가하세요:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` 선언 아래에 NMEA 문장을 처리하기 위한 TinyGPSPlus 객체를 선언하세요:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` 함수의 내용을 다음으로 변경하세요:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    이 코드는 UART 시리얼 포트에서 다음 문자를 읽어 `gps` NMEA 디코더로 전달합니다. 각 문자마다 디코더가 유효한 문장을 읽었는지 확인한 후, 유효한 위치를 읽었는지 확인합니다. 위치가 유효하다면, 이를 시리얼 모니터에 전송하며, 이 위치를 계산하는 데 기여한 위성의 수를 함께 출력합니다.

1. 코드를 빌드하고 Wio Terminal에 업로드하세요.

1. 업로드가 완료되면 시리얼 모니터를 사용하여 GPS 위치 데이터를 확인할 수 있습니다.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 이 코드는 [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 GPS 센서 프로그램과 데이터 디코딩이 성공적으로 완료되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.