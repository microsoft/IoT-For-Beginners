<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-25T00:05:24+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "ko"
}
-->
# 타이머 설정 - 가상 IoT 하드웨어와 Raspberry Pi

이 수업의 이 부분에서는 서버리스 코드를 호출하여 음성을 이해하고, 결과를 바탕으로 가상 IoT 장치나 Raspberry Pi에서 타이머를 설정합니다.

## 타이머 설정

음성 인식 호출에서 반환된 텍스트는 서버리스 코드로 전송되어 LUIS에서 처리되어야 하며, 타이머를 위한 초 단위 숫자를 반환받습니다. 이 초 단위 숫자를 사용하여 타이머를 설정할 수 있습니다.

타이머는 Python의 `threading.Timer` 클래스를 사용하여 설정할 수 있습니다. 이 클래스는 지연 시간과 함수를 받아들여, 지연 시간이 지난 후 해당 함수를 실행합니다.

### 작업 - 텍스트를 서버리스 함수로 전송하기

1. VS Code에서 `smart-timer` 프로젝트를 열고, 가상 IoT 장치를 사용하는 경우 터미널에서 가상 환경이 로드되었는지 확인합니다.

1. `process_text` 함수 위에, REST 엔드포인트를 호출하는 `get_timer_time`이라는 함수를 선언합니다:

    ```python
    def get_timer_time(text):
    ```

1. 이 함수에 다음 코드를 추가하여 호출할 URL을 정의합니다:

    ```python
    url = '<URL>'
    ```

    `<URL>`을 이전 수업에서 만든 REST 엔드포인트의 URL로 바꿉니다. 이 URL은 컴퓨터나 클라우드에 있을 수 있습니다.

1. 호출에 JSON으로 전달될 속성으로 텍스트를 설정하는 코드를 추가합니다:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. 그 아래에 응답 페이로드에서 `seconds`를 가져오고, 호출이 실패한 경우 0을 반환하는 코드를 추가합니다:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    성공적인 HTTP 호출은 200 범위의 상태 코드를 반환하며, 서버리스 코드는 텍스트가 처리되고 타이머 설정 의도로 인식되었을 때 200을 반환합니다.

### 작업 - 백그라운드 스레드에서 타이머 설정하기

1. 파일 상단에 Python의 threading 라이브러리를 가져오기 위한 import 문을 추가합니다:

    ```python
    import threading
    ```

1. `process_text` 함수 위에 응답을 말하는 함수를 추가합니다. 지금은 단순히 콘솔에 출력하지만, 이후 수업에서는 이 텍스트를 음성으로 출력할 것입니다.

    ```python
    def say(text):
        print(text)
    ```

1. 그 아래에 타이머가 완료되었음을 알리는 타이머 호출용 함수를 추가합니다:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    이 함수는 타이머의 분과 초를 받아 문장을 생성하여 타이머가 완료되었음을 알립니다. 분과 초를 확인하여 숫자가 있는 시간 단위만 포함합니다. 예를 들어, 분이 0이면 초만 메시지에 포함됩니다. 이 문장은 `say` 함수로 전달됩니다.

1. 그 아래에 타이머를 생성하는 `create_timer` 함수를 추가합니다:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    이 함수는 명령에서 전달된 타이머의 총 초를 받아 분과 초로 변환합니다. 그런 다음, 총 초를 사용하여 타이머 객체를 생성하고 시작합니다. 이때 `announce_timer` 함수와 분과 초를 포함한 리스트를 전달합니다. 타이머가 만료되면 `announce_timer` 함수가 호출되고, 이 리스트의 내용이 매개변수로 전달됩니다. 리스트의 첫 번째 항목은 `minutes` 매개변수로, 두 번째 항목은 `seconds` 매개변수로 전달됩니다.

1. `create_timer` 함수 끝에 사용자에게 타이머가 시작되었음을 알리는 메시지를 생성하는 코드를 추가합니다:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    이 메시지도 값이 있는 시간 단위만 포함합니다. 이 문장은 `say` 함수로 전달됩니다.

1. `process_text` 함수 끝에 텍스트에서 타이머 시간을 가져오고 타이머를 생성하는 코드를 추가합니다:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    초 단위 숫자가 0보다 클 때만 타이머가 생성됩니다.

1. 앱을 실행하고, 함수 앱도 실행 중인지 확인합니다. 타이머를 설정하고, 출력에서 타이머가 설정되고 만료되었을 때의 메시지를 확인합니다:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 이 코드는 [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) 또는 [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) 폴더에서 확인할 수 있습니다.

😀 타이머 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문 번역가에 의한 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.