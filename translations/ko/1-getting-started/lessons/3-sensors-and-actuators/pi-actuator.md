<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-24T23:21:18+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "ko"
}
-->
# 나이트라이트 만들기 - Raspberry Pi

이 수업의 이 부분에서는 Raspberry Pi에 LED를 추가하고 이를 사용하여 나이트라이트를 만들어 봅니다.

## 하드웨어

나이트라이트에는 이제 액추에이터가 필요합니다.

액추에이터는 **LED**입니다. [발광 다이오드](https://wikipedia.org/wiki/Light-emitting_diode)는 전류가 흐를 때 빛을 방출합니다. 이는 디지털 액추에이터로, 두 가지 상태(켜짐과 꺼짐)를 가집니다. 값 1을 보내면 LED가 켜지고, 값 0을 보내면 꺼집니다. LED는 외부 Grove 액추에이터이며 Raspberry Pi에 연결된 Grove Base hat에 연결해야 합니다.

나이트라이트의 논리적 흐름을 의사 코드로 표현하면 다음과 같습니다:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### LED 연결하기

Grove LED는 여러 색상의 LED를 선택할 수 있는 모듈 형태로 제공됩니다.

#### 작업 - LED 연결하기

LED를 연결하세요.

![Grove LED](../../../../../translated_images/ko/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. 원하는 LED를 선택하고 LED 모듈의 두 구멍에 다리를 삽입하세요.

    LED는 발광 다이오드이며, 다이오드는 전류를 한 방향으로만 흐르게 하는 전자 장치입니다. 따라서 LED는 올바른 방향으로 연결해야 작동합니다.

    LED의 다리 중 하나는 양극 핀이고, 다른 하나는 음극 핀입니다. LED는 완전히 둥글지 않고 한쪽이 약간 평평합니다. 약간 평평한 쪽이 음극 핀입니다. LED를 모듈에 연결할 때 둥근 쪽의 핀이 모듈 외부에 **+**로 표시된 소켓에 연결되도록 하고, 평평한 쪽이 모듈 중앙에 가까운 소켓에 연결되도록 하세요.

1. LED 모듈에는 밝기를 조절할 수 있는 회전 버튼이 있습니다. 작은 십자 드라이버를 사용하여 버튼을 최대 밝기로 설정하려면 반시계 방향으로 끝까지 돌리세요.

1. Grove 케이블의 한쪽 끝을 LED 모듈의 소켓에 삽입하세요. 케이블은 한 방향으로만 삽입됩니다.

1. Raspberry Pi의 전원을 끈 상태에서 Grove 케이블의 다른 끝을 Pi에 부착된 Grove Base hat의 **D5**로 표시된 디지털 소켓에 연결하세요. 이 소켓은 GPIO 핀 옆에 있는 소켓 행에서 왼쪽에서 두 번째입니다.

![D5 소켓에 연결된 Grove LED](../../../../../translated_images/ko/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## 나이트라이트 프로그래밍하기

이제 Grove 광 센서와 Grove LED를 사용하여 나이트라이트를 프로그래밍할 수 있습니다.

### 작업 - 나이트라이트 프로그래밍하기

나이트라이트를 프로그래밍하세요.

1. Pi의 전원을 켜고 부팅이 완료될 때까지 기다리세요.

1. 이전 과제의 일부에서 생성한 나이트라이트 프로젝트를 VS Code에서 열어 Pi에서 직접 실행하거나 Remote SSH 확장을 사용하여 연결하세요.

1. `app.py` 파일 상단의 다른 `import` 줄 아래에 필요한 라이브러리를 가져오는 다음 코드를 추가하세요.

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed` 문은 Grove Python 라이브러리에서 `GroveLed`를 가져옵니다. 이 라이브러리는 Grove LED와 상호작용하는 코드를 포함하고 있습니다.

1. `light_sensor` 선언 뒤에 LED를 관리하는 클래스의 인스턴스를 생성하는 다음 코드를 추가하세요.

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` 줄은 **D5** 핀에 연결된 Grove LED 클래스의 인스턴스를 생성합니다. D5는 LED가 연결된 디지털 Grove 핀입니다.

    > 💁 모든 소켓에는 고유한 핀 번호가 있습니다. 핀 0, 2, 4, 6은 아날로그 핀이고, 핀 5, 16, 18, 22, 24, 26은 디지털 핀입니다.

1. `while` 루프 내부에서 `time.sleep` 이전에 광 수준을 확인하고 LED를 켜거나 끄는 체크를 추가하세요.

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    이 코드는 `light` 값을 확인합니다. 값이 300보다 작으면 `GroveLed` 클래스의 `on` 메서드를 호출하여 LED에 디지털 값 1을 보내고 LED를 켭니다. 값이 300 이상이면 `off` 메서드를 호출하여 디지털 값 0을 보내고 LED를 끕니다.

    > 💁 이 코드는 `print('Light level:', light)` 줄과 동일한 들여쓰기 수준으로 설정되어 while 루프 내부에 있어야 합니다!

    > 💁 액추에이터에 디지털 값을 보낼 때 값 0은 0V이고, 값 1은 장치의 최대 전압입니다. Raspberry Pi와 Grove 센서 및 액추에이터의 경우 값 1의 전압은 3.3V입니다.

1. VS Code 터미널에서 다음 명령을 실행하여 Python 앱을 실행하세요.

    ```sh
    python3 app.py
    ```

    광 수준 값이 콘솔에 출력됩니다.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. 광 센서를 덮거나 드러내세요. 광 수준이 300 이하일 때 LED가 켜지고, 광 수준이 300 이상일 때 LED가 꺼지는 것을 확인하세요.

    > 💁 LED가 켜지지 않으면 올바른 방향으로 연결되었는지 확인하고 회전 버튼이 최대 밝기로 설정되었는지 확인하세요.

![광 수준 변화에 따라 켜지고 꺼지는 Pi에 연결된 LED](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 이 코드는 [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi) 폴더에서 찾을 수 있습니다.

😀 나이트라이트 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.