<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-24T23:26:06+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "ko"
}
-->
# 센서 추가하기 - Wio Terminal

이 수업의 이번 부분에서는 Wio Terminal의 광 센서를 사용하게 됩니다.

## 하드웨어

이번 수업에서 사용할 센서는 **광 센서**로, [포토다이오드](https://wikipedia.org/wiki/Photodiode)를 사용하여 빛을 전기 신호로 변환합니다. 이 센서는 아날로그 센서로, 0에서 1,023 사이의 정수 값을 보내며, 이는 [럭스](https://wikipedia.org/wiki/Lux)와 같은 표준 측정 단위로 매핑되지 않는 상대적인 빛의 양을 나타냅니다.

광 센서는 Wio Terminal에 내장되어 있으며, 뒷면의 투명한 플라스틱 창을 통해 볼 수 있습니다.

![Wio Terminal 뒷면의 광 센서](../../../../../translated_images/ko/wio-light-sensor.b1f529f3c95f5165.webp)

## 광 센서 프로그래밍하기

이제 내장된 광 센서를 사용하도록 장치를 프로그래밍할 수 있습니다.

### 작업

장치를 프로그래밍하세요.

1. 이전 과제의 일부에서 생성한 VS Code의 야간 조명 프로젝트를 엽니다.

1. `setup` 함수의 맨 아래에 다음 줄을 추가하세요:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    이 줄은 센서 하드웨어와 통신하는 데 사용되는 핀을 설정합니다.

    `WIO_LIGHT` 핀은 온보드 광 센서에 연결된 GPIO 핀 번호입니다. 이 핀은 `INPUT`으로 설정되며, 이는 센서에 연결되어 데이터를 핀에서 읽게 된다는 것을 의미합니다.

1. `loop` 함수의 내용을 삭제하세요.

1. 이제 비어 있는 `loop` 함수에 다음 코드를 추가하세요.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    이 코드는 `WIO_LIGHT` 핀에서 아날로그 값을 읽습니다. 이는 온보드 광 센서에서 0-1,023 사이의 값을 읽습니다. 이 값은 직렬 포트로 전송되어 코드가 실행 중일 때 Serial Monitor에서 읽을 수 있습니다. `Serial.print`는 끝에 새 줄 없이 텍스트를 작성하므로 각 줄은 `Light value:`로 시작하고 실제 광 값으로 끝납니다.

1. `loop`의 끝에 1초(1,000ms)의 짧은 지연을 추가하세요. 광 수준을 지속적으로 확인할 필요는 없으므로 지연을 추가하면 장치의 전력 소비가 줄어듭니다.

    ```cpp
    delay(1000);
    ```

1. Wio Terminal을 컴퓨터에 다시 연결하고 이전과 같이 새 코드를 업로드하세요.

1. Serial Monitor를 연결하세요. 광 값이 터미널에 출력됩니다. Wio Terminal 뒷면의 광 센서를 가리거나 드러내면 값이 변경됩니다.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 이 코드는 [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 야간 조명 프로그램에 센서를 추가하는 데 성공했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.