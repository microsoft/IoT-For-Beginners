<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-24T23:23:55+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "ko"
}
-->
# 나이트라이트 만들기 - 가상 IoT 하드웨어

이 수업의 이번 부분에서는 가상 IoT 장치에 LED를 추가하고 이를 사용해 나이트라이트를 만들어 보겠습니다.

## 가상 하드웨어

나이트라이트에는 CounterFit 앱에서 생성된 하나의 액추에이터가 필요합니다.

액추에이터는 **LED**입니다. 실제 IoT 장치에서는 [발광 다이오드](https://wikipedia.org/wiki/Light-emitting_diode)로, 전류가 흐를 때 빛을 방출합니다. 이 디지털 액추에이터는 켜짐과 꺼짐의 두 가지 상태를 가지며, 값 1을 보내면 LED가 켜지고, 값 0을 보내면 꺼집니다.

나이트라이트 로직의 의사 코드는 다음과 같습니다:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### CounterFit에 액추에이터 추가하기

가상 LED를 사용하려면 CounterFit 앱에 추가해야 합니다.

#### 작업 - CounterFit에 액추에이터 추가하기

CounterFit 앱에 LED를 추가하세요.

1. 이 과제의 이전 부분에서 실행했던 CounterFit 웹 앱이 실행 중인지 확인하세요. 실행 중이 아니라면 앱을 시작하고 조도 센서를 다시 추가하세요.

1. LED를 생성하세요:

    1. *Actuator* 창의 *Create actuator* 상자에서 *Actuator type* 드롭다운 메뉴를 열고 *LED*를 선택하세요.

    1. *Pin*을 *5*로 설정하세요.

    1. **Add** 버튼을 선택하여 핀 5에 LED를 생성하세요.

    ![LED 설정](../../../../../translated_images/ko/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED가 생성되어 액추에이터 목록에 나타납니다.

    ![생성된 LED](../../../../../translated_images/ko/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    LED가 생성된 후에는 *Color* 선택기를 사용해 색상을 변경할 수 있습니다. 색상을 선택한 후 **Set** 버튼을 눌러 색상을 변경하세요.

### 나이트라이트 프로그래밍하기

이제 CounterFit 조도 센서와 LED를 사용해 나이트라이트를 프로그래밍할 수 있습니다.

#### 작업 - 나이트라이트 프로그래밍하기

나이트라이트를 프로그래밍하세요.

1. 이 과제의 이전 부분에서 생성한 나이트라이트 프로젝트를 VS Code에서 여세요. 필요하다면 터미널을 종료하고 다시 생성하여 가상 환경이 실행 중인지 확인하세요.

1. `app.py` 파일을 여세요.

1. 필요한 라이브러리를 가져오기 위해 `app.py` 파일 상단의 다른 `import` 줄 아래에 다음 코드를 추가하세요.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed` 문은 CounterFit Grove shim Python 라이브러리에서 `GroveLed`를 가져옵니다. 이 라이브러리는 CounterFit 앱에서 생성된 LED와 상호작용하는 코드를 포함하고 있습니다.

1. `light_sensor` 선언 아래에 다음 코드를 추가하여 LED를 관리하는 클래스의 인스턴스를 생성하세요:

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` 줄은 핀 **5**에 연결된 `GroveLed` 클래스의 인스턴스를 생성합니다. 이 핀은 CounterFit Grove 핀에서 LED가 연결된 핀입니다.

1. `while` 루프 내부, `time.sleep` 이전에 체크를 추가하여 조도 수준을 확인하고 LED를 켜거나 끄세요:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    이 코드는 `light` 값을 확인합니다. 값이 300 미만이면 `GroveLed` 클래스의 `on` 메서드를 호출하여 LED에 디지털 값 1을 보내고, 이를 켭니다. 값이 300 이상이면 `off` 메서드를 호출하여 디지털 값 0을 보내고, 이를 끕니다.

    > 💁 이 코드는 `print('Light level:', light)` 줄과 동일한 들여쓰기 수준으로 작성되어야 `while` 루프 내부에 포함됩니다!

1. VS Code 터미널에서 다음 명령어를 실행하여 Python 앱을 실행하세요:

    ```sh
    python3 app.py
    ```

    조도 값이 콘솔에 출력됩니다.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. *Value* 또는 *Random* 설정을 변경하여 조도 수준을 300 이상 또는 이하로 조정하세요. LED가 켜졌다 꺼졌다 할 것입니다.

![조도 수준 변화에 따라 CounterFit 앱에서 켜지고 꺼지는 LED](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 이 코드는 [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) 폴더에서 확인할 수 있습니다.

😀 나이트라이트 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.