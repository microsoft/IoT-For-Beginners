<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-24T23:22:38+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "ko"
}
-->
# 야간등 만들기 - Wio Terminal

이 수업의 이번 부분에서는 Wio Terminal에 LED를 추가하고 이를 사용하여 야간등을 만들 것입니다.

## 하드웨어

야간등에는 이제 액추에이터가 필요합니다.

액추에이터는 **LED**입니다. [발광 다이오드](https://wikipedia.org/wiki/Light-emitting_diode)는 전류가 흐를 때 빛을 방출합니다. 이는 디지털 액추에이터로, 두 가지 상태(켜짐과 꺼짐)를 가집니다. 값 1을 보내면 LED가 켜지고, 값 0을 보내면 꺼집니다. 이는 외부 Grove 액추에이터로 Wio Terminal에 연결해야 합니다.

야간등의 논리를 의사 코드로 표현하면 다음과 같습니다:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### LED 연결하기

Grove LED는 여러 색상의 LED를 선택할 수 있는 모듈로 제공됩니다.

#### 작업 - LED 연결하기

LED를 연결하세요.

![Grove LED](../../../../../translated_images/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.ko.png)

1. 좋아하는 LED를 선택하여 LED 모듈의 두 구멍에 다리를 삽입하세요.

    LED는 발광 다이오드이며, 다이오드는 전류를 한 방향으로만 흐르게 할 수 있는 전자 장치입니다. 즉, LED는 올바른 방향으로 연결해야 작동합니다.

    LED의 다리 중 하나는 양극 핀이고, 다른 하나는 음극 핀입니다. LED는 완전히 둥글지 않고 한쪽이 약간 평평합니다. 약간 평평한 쪽이 음극 핀입니다. LED를 모듈에 연결할 때, 둥근 쪽의 핀이 모듈 외부에 **+**로 표시된 소켓에 연결되도록 하고, 평평한 쪽이 모듈 중앙에 가까운 소켓에 연결되도록 하세요.

1. LED 모듈에는 밝기를 조절할 수 있는 회전 버튼이 있습니다. 작은 십자 드라이버를 사용하여 버튼을 최대한 반시계 방향으로 돌려 처음에는 밝기를 최대로 설정하세요.

1. Grove 케이블의 한쪽 끝을 LED 모듈의 소켓에 삽입하세요. 케이블은 한 방향으로만 삽입됩니다.

1. Wio Terminal을 컴퓨터 또는 다른 전원 공급 장치에서 분리한 상태에서, Grove 케이블의 다른 끝을 Wio Terminal 화면을 기준으로 오른쪽에 있는 Grove 소켓에 연결하세요. 이 소켓은 전원 버튼에서 가장 멀리 떨어져 있는 소켓입니다.

    > 💁 오른쪽 Grove 소켓은 아날로그 또는 디지털 센서와 액추에이터에 사용할 수 있습니다. 왼쪽 소켓은 디지털 센서와 액추에이터 전용입니다.

![오른쪽 소켓에 연결된 Grove LED](../../../../../translated_images/wio-led.265a1897e72d7f21.ko.png)

## 야간등 프로그래밍하기

이제 내장된 광 센서와 Grove LED를 사용하여 야간등을 프로그래밍할 수 있습니다.

### 작업 - 야간등 프로그래밍하기

야간등을 프로그래밍하세요.

1. 이전 과제의 일부에서 생성한 야간등 프로젝트를 VS Code에서 엽니다.

1. `setup` 함수의 맨 아래에 다음 줄을 추가하세요:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    이 줄은 Grove 포트를 통해 LED와 통신하는 데 사용되는 핀을 설정합니다.

    `D0` 핀은 오른쪽 Grove 소켓의 디지털 핀입니다. 이 핀은 `OUTPUT`으로 설정되어 액추에이터에 연결되며 핀에 데이터를 기록합니다.

1. 루프 함수의 `delay` 바로 앞에 다음 코드를 추가하세요:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    이 코드는 `light` 값을 확인합니다. 값이 300보다 작으면 `D0` 디지털 핀에 `HIGH` 값을 보냅니다. 이 `HIGH` 값은 1로, LED를 켭니다. 빛이 300 이상이면 `LOW` 값 0을 핀에 보내 LED를 끕니다.

    > 💁 액추에이터에 디지털 값을 보낼 때, LOW 값은 0v이고 HIGH 값은 장치의 최대 전압입니다. Wio Terminal의 경우 HIGH 전압은 3.3V입니다.

1. Wio Terminal을 컴퓨터에 다시 연결하고 이전과 같이 새 코드를 업로드하세요.

1. 시리얼 모니터를 연결하세요. 빛 값이 터미널에 출력됩니다.

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

1. 광 센서를 덮거나 드러내세요. 빛 수준이 300 이하일 때 LED가 켜지고, 빛 수준이 300 이상일 때 LED가 꺼지는 것을 확인하세요.

![빛 수준 변화에 따라 켜지고 꺼지는 WIO에 연결된 LED](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 이 코드는 [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 야간등 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.