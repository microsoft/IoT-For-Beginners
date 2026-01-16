<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-24T22:05:04+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "ko"
}
-->
# 온도 측정 - Wio Terminal

이 수업의 이 부분에서는 Wio Terminal에 온도 센서를 추가하고, 센서로부터 온도 값을 읽는 방법을 배웁니다.

## 하드웨어

Wio Terminal에는 온도 센서가 필요합니다.

사용할 센서는 [DHT11 습도 및 온도 센서](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)로, 하나의 패키지에 두 개의 센서를 결합한 것입니다. 이 센서는 상업적으로 널리 사용되며, 온도, 습도, 때로는 대기압을 결합한 센서들이 많이 있습니다. 온도 센서 구성 요소는 음의 온도 계수(NTC) 서미스터로, 온도가 증가함에 따라 저항이 감소하는 특성을 가지고 있습니다.

이 센서는 디지털 센서로, 온도와 습도 데이터를 포함하는 디지털 신호를 생성하는 온보드 ADC를 가지고 있어 마이크로컨트롤러가 이를 읽을 수 있습니다.

### 온도 센서 연결하기

Grove 온도 센서는 Wio Terminal의 디지털 포트에 연결할 수 있습니다.

#### 작업 - 온도 센서 연결하기

온도 센서를 연결하세요.

![Grove 온도 센서](../../../../../translated_images/ko/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Grove 케이블의 한쪽 끝을 습도 및 온도 센서의 소켓에 삽입하세요. 케이블은 한 방향으로만 삽입됩니다.

1. Wio Terminal이 컴퓨터 또는 다른 전원 공급 장치와 연결되지 않은 상태에서, Grove 케이블의 다른 끝을 Wio Terminal 화면을 바라보았을 때 오른쪽에 있는 Grove 소켓에 연결하세요. 이 소켓은 전원 버튼에서 가장 멀리 떨어진 소켓입니다.

![오른쪽 소켓에 연결된 Grove 온도 센서](../../../../../translated_images/ko/wio-temperature-sensor.2934928f38c7f79a.webp)

## 온도 센서 프로그래밍하기

이제 Wio Terminal을 연결된 온도 센서를 사용할 수 있도록 프로그래밍할 수 있습니다.

### 작업 - 온도 센서 프로그래밍하기

장치를 프로그래밍하세요.

1. PlatformIO를 사용하여 새로운 Wio Terminal 프로젝트를 생성하세요. 이 프로젝트의 이름을 `temperature-sensor`로 설정하세요. `setup` 함수에 시리얼 포트를 설정하는 코드를 추가하세요.

    > ⚠️ 필요하다면 [프로젝트 1, 수업 1에서 PlatformIO 프로젝트를 생성하는 방법에 대한 지침](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)을 참조하세요.

1. 프로젝트의 `platformio.ini` 파일에 Seeed Grove 습도 및 온도 센서 라이브러리 의존성을 추가하세요:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ 필요하다면 [프로젝트 1, 수업 4에서 PlatformIO 프로젝트에 라이브러리를 추가하는 방법에 대한 지침](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries)을 참조하세요.

1. 기존의 `#include <Arduino.h>` 아래에 다음 `#include` 지시문을 파일 상단에 추가하세요:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    이는 센서와 상호작용하는 데 필요한 파일을 가져옵니다. `DHT.h` 헤더 파일은 센서 자체의 코드를 포함하며, `SPI.h` 헤더를 추가하면 앱이 컴파일될 때 센서와 통신하는 데 필요한 코드가 링크됩니다.

1. `setup` 함수 이전에 DHT 센서를 선언하세요:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    이는 **D**igital **H**umidity 및 **T**emperature 센서를 관리하는 `DHT` 클래스의 인스턴스를 선언합니다. 이 센서는 Wio Terminal의 오른쪽 Grove 소켓인 포트 `D0`에 연결됩니다. 두 번째 매개변수는 사용 중인 센서가 *DHT11* 센서임을 코드에 알려줍니다. 사용 중인 라이브러리는 이 센서의 다른 변형도 지원합니다.

1. `setup` 함수에서 시리얼 연결을 설정하는 코드를 추가하세요:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. 마지막 `delay` 이후, `setup` 함수 끝에 DHT 센서를 시작하는 호출을 추가하세요:

    ```cpp
    dht.begin();
    ```

1. `loop` 함수에서 센서를 호출하고 온도를 시리얼 포트에 출력하는 코드를 추가하세요:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    이 코드는 2개의 float로 이루어진 빈 배열을 선언하고, 이를 `DHT` 인스턴스의 `readTempAndHumidity` 호출에 전달합니다. 이 호출은 배열에 두 개의 값을 채웁니다. 습도는 배열의 0번째 항목에 저장되고(참고로 C++ 배열은 0부터 시작하므로 배열의 '첫 번째' 항목은 0번째 항목입니다), 온도는 1번째 항목에 저장됩니다.

    온도는 배열의 1번째 항목에서 읽어와 시리얼 포트에 출력됩니다.

    > 🇺🇸 온도는 섭씨로 읽어옵니다. 미국에서는 섭씨 값을 화씨로 변환하려면 섭씨 값을 5로 나눈 후 9를 곱하고 32를 더하세요. 예를 들어, 섭씨 20°C는 ((20/5)*9) + 32 = 68°F가 됩니다.

1. 코드를 빌드하고 Wio Terminal에 업로드하세요.

    > ⚠️ 필요하다면 [프로젝트 1, 수업 1에서 PlatformIO 프로젝트를 생성하는 방법에 대한 지침](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)을 참조하세요.

1. 업로드가 완료되면 시리얼 모니터를 사용하여 온도를 확인할 수 있습니다:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 이 코드는 [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 온도 센서 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.