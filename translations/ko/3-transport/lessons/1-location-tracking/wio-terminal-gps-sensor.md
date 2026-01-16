<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-25T00:45:05+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "ko"
}
-->
# GPS 데이터 읽기 - Wio Terminal

이 강의의 이 부분에서는 Wio Terminal에 GPS 센서를 추가하고 데이터를 읽는 방법을 배웁니다.

## 하드웨어

Wio Terminal에는 GPS 센서가 필요합니다.

사용할 센서는 [Grove GPS Air530 센서](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)입니다. 이 센서는 여러 GPS 시스템에 연결하여 빠르고 정확한 위치를 제공합니다. 센서는 두 부분으로 구성되어 있습니다 - 센서의 핵심 전자 부품과 얇은 선으로 연결된 외부 안테나로, 위성에서 오는 전파를 수신합니다.

이 센서는 UART 센서로, UART를 통해 GPS 데이터를 전송합니다.

### GPS 센서 연결하기

Grove GPS 센서를 Wio Terminal에 연결할 수 있습니다.

#### 작업 - GPS 센서 연결하기

GPS 센서를 연결하세요.

![Grove GPS 센서](../../../../../translated_images/ko/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Grove 케이블의 한쪽 끝을 GPS 센서의 소켓에 삽입하세요. 케이블은 한 방향으로만 들어갑니다.

1. Wio Terminal이 컴퓨터나 다른 전원 공급 장치에 연결되지 않은 상태에서, Grove 케이블의 다른 쪽 끝을 Wio Terminal 화면을 기준으로 왼쪽에 있는 Grove 소켓에 연결하세요. 이 소켓은 전원 버튼에 가장 가까운 소켓입니다.

    ![왼쪽 소켓에 연결된 Grove GPS 센서](../../../../../translated_images/ko/wio-gps-sensor.19fd52b81ce58095.webp)

1. GPS 센서를 배치할 때, 연결된 안테나가 하늘을 볼 수 있는 위치에 두세요. 이상적으로는 창문 옆이나 야외에 두는 것이 좋습니다. 안테나에 장애물이 없을수록 신호가 더 잘 잡힙니다.

1. 이제 Wio Terminal을 컴퓨터에 연결할 수 있습니다.

1. GPS 센서에는 두 개의 LED가 있습니다 - 데이터가 전송될 때 깜박이는 파란색 LED와 위성에서 데이터를 수신할 때 매초 깜박이는 녹색 LED입니다. Wio Terminal에 전원을 켰을 때 파란색 LED가 깜박이는지 확인하세요. 몇 분 후 녹색 LED가 깜박이기 시작합니다. 그렇지 않다면 안테나의 위치를 조정해야 할 수 있습니다.

## GPS 센서 프로그래밍

이제 Wio Terminal을 프로그래밍하여 연결된 GPS 센서를 사용할 수 있습니다.

### 작업 - GPS 센서 프로그래밍

장치를 프로그래밍하세요.

1. PlatformIO를 사용하여 새로운 Wio Terminal 프로젝트를 생성하세요. 이 프로젝트의 이름을 `gps-sensor`로 지정하세요. `setup` 함수에 직렬 포트를 설정하는 코드를 추가하세요.

1. `main.cpp` 파일 상단에 다음 포함 지시문을 추가하세요. 이 코드는 UART용 왼쪽 Grove 포트를 설정하는 함수가 포함된 헤더 파일을 포함합니다.

    ```cpp
    #include <wiring_private.h>
    ```

1. 그 아래에 UART 포트와의 직렬 포트 연결을 선언하는 다음 코드를 추가하세요:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. 내부 신호 핸들러를 이 직렬 포트로 리디렉션하는 코드를 추가해야 합니다. `Serial3` 선언 아래에 다음 코드를 추가하세요:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. `setup` 함수에서 `Serial` 포트를 설정한 아래에, UART 직렬 포트를 설정하는 다음 코드를 추가하세요:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. `setup` 함수에서 이 코드 아래에 Grove 핀을 직렬 포트에 연결하는 다음 코드를 추가하세요:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. `loop` 함수 전에 GPS 데이터를 직렬 모니터로 전송하는 다음 함수를 추가하세요:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. `loop` 함수에서 UART 직렬 포트에서 데이터를 읽고 이를 직렬 모니터에 출력하는 다음 코드를 추가하세요:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    이 코드는 UART 직렬 포트에서 데이터를 읽습니다. `readStringUntil` 함수는 종료 문자(이 경우 새 줄 문자)까지 읽습니다. 이는 전체 NMEA 문장을 읽습니다(NMEA 문장은 새 줄 문자로 종료됩니다). UART 직렬 포트에서 데이터를 읽을 수 있는 동안 데이터를 읽고 `printGPSData` 함수를 통해 직렬 모니터로 전송합니다. 더 이상 읽을 데이터가 없으면 `loop`는 1초(1,000ms) 동안 대기합니다.

1. 코드를 빌드하고 Wio Terminal에 업로드하세요.

1. 업로드가 완료되면 직렬 모니터를 사용하여 GPS 데이터를 확인할 수 있습니다.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 이 코드는 [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 GPS 센서 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.