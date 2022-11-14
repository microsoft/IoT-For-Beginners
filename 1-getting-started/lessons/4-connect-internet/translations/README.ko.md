# 인터넷에 장치 연결하기

![A sketchnote overview of this lesson](../../../../sketchnotes/lesson-4.jpg)

> Nitya Narasimhan의 스케치 노트. 더 큰 버전을 보려면 이미지를 클릭하세요.

이 수업은 [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn)의 [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) 의 일부로 진행되었습니다. 이 수업은 2개의 비디오 - 1 시간의 수업, 1시간의 강의에 대한 집중 탐구 및 질의 응답으로 구성되어 있습니다.

![https://img.youtube.com/vi/O4dd172mZhs/0.jpg](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)

![https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)

> 🎥 상단의 이미지를 클릭하여 비디오를 시청할 수 있습니다.

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## 개요

IoT에서 **I**는 **인터넷**을 의미합니다. - 장치에 연결된 센서에서 측정값 수집, 액추에이터 제어를 위한 메세지 전송과 같은 IoT의 많은 기능을 가능하게 하는 클라우드 연결 및 서비스를 의미합니다. IoT 장치는 일반적으로 표준 통신 프로토콜을 사용하여 단일 클라우드 IoT 서비스에 연결되며 해당 서비스는 데이터에 대한 현명한 결정을 내리는 AI 서비스에 제어 또는 보고를 위한 웹 앱에 이르기까지 나머지 IoT 어플리케이션에 연결됩니다.

> 🎓 센서에서 수집되어 클라우드로 전송되는 데이터를 telemetry라고 합니다.

IoT 장치는 클라우드에서 메시지를 수신할 수 있습니다. 종종 메시지에는 다음 명령들이 포함되어 있습니다. - 내부적으로 작업 수행하기(예: 재부팅 또는 펌웨어 업데이트) 또는 엑추에이터 사용하기(예: 조명 켜기).

이 강의에서는 IoT 장치가 클라우드에 연결하는데 사용할 수 있는 몇가지 통신 프로토콜과 송수신할 수 있는 데이터 유형을 소개합니다. 또한 야간 조명에 인터넷 제어를 추가하고, LED 제어 논리를 로컬에서 실행되는 ‘서버’ 코드로 이동하는 실습을 하게 됩니다.

이 강의에서 다룰 내용은 다음과 같습니다:

- [통신 프로토콜](#communication-protocols)
- [메시지 큐 원격 분석 전송(MQTT)](##message-queueing-telemetry-transport-mqtt)
- [텔레메트리(원격 측정)](#telemetry)
- [명령](#commands)

## 통신 프로토콜

IoT 장치가 인터넷과 통신하는 데 널리 사용하는 통신 프로토콜이 많이 있습니다. 가장 인기있는 것은 일종의 브로커 형태의 발행/구독 메시징을 기반으로 합니다. IoT 장치는 브로커에 연결하고 원격 측정을 게시하고 명령을 구독합니다. 또한 클라우드 서비스는 브로커에 연결하고 모든 원격 측정 메시지를 구독하고 특정 장치, 장치 그룹에 명령을 게시합니다.

![IoT devices connect to a broker and publish telemetry and subscribe to commands. Cloud services connect to the broker and subscribe to all telemetry and send commands to specific devices.](../../../../images/pub-sub.png)

MQTT는 IoT 장치에 가장 널리 사용되는 통신 프로토콜이며 이 강의에서 다룹니다. 다른 프로토콜에는 AMQP와 HTTP/HTTPS가 있습니다.

## 메시지 큐 원격 분석 전송 (MQTT)

[MQTT](http://mqtt.org/) 는 장치 간에 메시지를 보낼 수 있는 가벼운 개방형 표준 메시징 프로토콜 입니다. 1999년에 송유관을 모니터링하도록 설계되었으며 15년 후 IBM에서 공개 표준으로 발표했습니다.

MQTT 에는 단일 브로커와 여러 클라이언트가 있습니다. 모든 클라이언트는 브로커에 연결되고, 브로커는 메시지를 관련 클라이언트에게 라우팅합니다. 메시지는 개별 클라이언트에게 직접 전송되지 않고 명명된 주제를 사용하여 라우팅됩니다. 클라이언트는 주제를 게시할 수 있으며 해당 주제를 구독하는 모든 클라이언트는 메시지를 받습니다.

![IoT device publishing telemetry on the /telemetry topic, and the cloud service subscribing to that topic](../../../../images/mqtt.png)

✅ 조사를 해보십시오. IoT 장치가 많은 경우, MQTT 브로커가 모든 메시지를 처리하려면 어떻게 해야 합니까?

### IoT장치를 MQTT에 연결하기

야간 조명에 인터넷 제어를 추가하는 첫 번째 단계는 이를 MQTT 브로커에 연결하는 것입니다.

### 작업

장치를 MQTT 브로커에 연결합니다.

이 수업에서는 IoT 야간 조명을 인터넷에 연결하여 원격으로 제어할 수 있도록 합니다. 수업의 뒷부분에서, IoT 장치는 MQTT를 통해 가벼운 수준의 공용 MQTT 브로커로 원격 분석 메시지를 보내고, 당신이 작성할 서버 코드에 의해 선택될 것입니다.

이러한 설정의 실제 사용 사례는 경기장과 같이 조명이 많은 위치에서 조명 키는 것을 결정하기 전에 여러 광 센서에서 데이터를 수집하는 것이 있습니다. 이렇게 하면 구름이나 새가 한 센서를 가려도, 다른 센서에서 충분한 빛을 감지한 경우 조명이 켜지지 않을 수 있습니다.

✅ 명령을 보내기 전에 여러 센서의 데이터를 평가해야 하는 다른 상황은 무엇입니까?

이 과제의 일부로 MQTT 브로커를 설정하는 복잡성을 처리하는 대신 오픈 소스 MQTT 브로커인 [Eclipse Mosquitto](https://www.mosquitto.org/) 를 실행하는 공개 테스트 서버를 사용할 수 있습니다. 이 테스트 브로커는 [test.mosquitto.org](https://test.mosquitto.org/)에서 공개적으로 사용할 수 있으며, 계정을 설정할 필요가 없으므로 MQTT 클라이언트와 서버를 테스트에 훌륭한 도구 입니다.

> 💁 이 테스트 브로커는 공개되어 있으며 안전하지 않습니다. 누구나 귀하가 게시한 내용을 들을 수 있으므로, 비공개로 유지해야 하는 데이터와 함께 사용해서는 안됩니다.

![../../../images/assignment-1-internet-flow.png](../../../../images/assignment-1-internet-flow.png)

아래 단계에 따라 장치를 MQTT 브로커에 연결하십시오:

- [Arduino - Wio Terminal](notion://www.notion.so/wio-terminal-mqtt.md) 아두이노 - Wio 터미널
- [Single-board computer - Raspberry Pi/Virtual IoT device](notion://www.notion.so/single-board-computer-mqtt.md) 싱글-보드 컴퓨터 - Raspberry Pi/가상 IoT 장치

### MQTT 자세히 알아보기

주제에는 계층이 있을 수 있으며, 클라이언트는 와일드카드를 사용하여 다른 수준의 계층에 가입할 수 있습니다. 예를 들어, `/telemetry/temperature` 주제에 온도 원격 측정 메시지를 보내고 , `/telemetry/humidity` 주제에 습도 메시지를 보낸 뒤, 클라우드 앱에서 `/telemetry/*` 주제를 구독하여 온도 와 습도 원격 측정 메시지를 모두 수신할 수 있습니다.

메시지는 수신되는 메시지의 보장을 결정하는 서비스의 품질(QoS)과 함께 보낼 수 있습니다.

- 최대 한 번 - 메세지는 한 번만 전송되고 클라이언트와 브로커는 전송을 확인하기 위해 추가 단계를 수행하지 않습니다(실행 후 잊어버림).
- 최소 한 번 - 확인 메시지가 수신될 때까지 보낸 사람이 여러번 다시 시도합니다.(전송 보장).
- 정확히 한 번 - 보낸 사람과 받는 사람이 2 단계의 핸드셰이크에 참여하여 메시지 사본을 하나만 수신하도록 합니다(전달 보장).

✅ 어떤 상황에서 실행 후 잊어버림 메시지보다 전달 보장 메시지가 필요할 수 있습니까?

이름은 메시지 큐잉(MQTT의 이니셜)이지만, 실제로는 메시지 큐를 지원하지 않습니다. 클라이언트가 연결을 끊었다가, 다시 연결하면 QoS 프로세스를 사용하여 이미 처리를 시작한 메시지를 제외하고 연결이 끊긴 동안 보낸 메시지를 받지 않는다는 의미입니다. 메시지에는 보유 플래그가 설정되어 있을 수 있습니다. 이것이 설정되면 MQTT 브로커는 이 플래그를 사용하여 주제에 대해 보낸 마지막 메시지를 저장하고 나중에 주제를 구독하는 모든 클라이언트에게 이를 보냅니다. 이런 식으로 클라이언트는 항상 최신 메시지를 받습니다.

또한 MQTT는 메시지 간의 긴 간격 동안 연결이 여젼히 활성 상태인지 확인하는 연결 유지 기능을 지원합니다.

> 🦟 [Mosquitto from the Eclipse Foundation](https://mosquitto.org/) 에는 [test.mosquitto.org](https://test.mosquitto.org/)에서 호스팅되는 코드 테스트에 사용할 수 있는 공개 MQTT 브로커와 함께 MQTT를 실험하기 위해 직접 실행할 수 있는 무료 MQTT 브로커가 있습니다.

MQTT 연결은 공개되고 공개되거나 사용자의 이름과 암호 또는 인증서를 사용하여 암호화되고 보호될 수 있습니다.

> 💁 MQTT 는 HTTP와 동일한 기본 네트워크 프로토콜 이지만 다른 포트에서 TCP/IP를 통해 통신합니다. 또한 웹소켓을 통한 MQTT 를 사용하여 브라우저에서 실행되는 웹 앱과 통신하거나, 방화벽이나 기타 네트워크 규칙이 표준 MQTT 연결을 차단하는 상황에서도 사용할 수 있습니다.

## 텔레메트리(원격 측정)

텔레메트리(Telemetry)는 원격 측정이라는 그리스어에서 파생되었습니다. 원격 측정은 센서에서 데이터를 수집하여 클라우드로 보내는 행위입니다..

> 💁 최초의 원격 측정 장치 중 하나는 1874년 프랑스에서 발명되었으며 실시간으로 날씨와 눈 깊이를 몽블랑에서 파리로 보냈습니다. 당시에는 무선 기술을 사용할 수 없었기 때문에 물리적 와이어를 사용했습니다.

수업 1의 예시 스마트 온도 조절기를 다시 살펴보겠습니다.

![../../../images/telemetry.png](../../../../images/telemetry.png)

온도 조절 장치에는 원격 측정을 수집하는 온도 센서가 있습니다. 하나의 온도 센서가 내장되어 있을 가능성이 높으며 BLE([Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy))와 같은 무선 프로토콜을 통해 여러 외부 온도 센서에 연결할 수 있습니다.

전송할 원격 측정 데이터의 예는 다음과 같습니다:

| Name                     | Value | Description                                                            |
| ------------------------ | ----- | ---------------------------------------------------------------------- |
| `thermostat_temperature` | 18°C  | 온도 조절 장치에 내장된 온도 센서로 측정된 온도                        |
| `livingroom_temperature` | 19°C  | `livingroom` 이라고 명명된 방에 있는 원격 온도 센서에 의해 측정된 온도 |
| `bedroom_temperature`    | 21°C  | `bedroom`이라고 명명된 방에 있는 원격 온도 센서에 의해 측정된 온도     |

클라우드 서비스는 이 원격 측정 데이터를 사용하여 난방을 제어하기 위해 보낼 명령을 결정할 수 있습니다.

### IoT 장치에서 원격 분석 보내기

야간 조명에 인터넷 제어를 추가하는 다음 과정은 조명 수준 원격 분석을 MQTT 브로커의 텔레메트리 주제를 보내는 것입니다.

### 작업 - IoT 장치에서 원격 분석 보내기

MQTT 브로커에게 가벼운 수준의 원격 분석을 보냅니다.

데이터는 키/값 쌍을 사용해 텍스트로 데이터를 인코딩하는 표준인 JSON(JavaScriopt Object Notation의 약자)으로 인코딩되어 전송됩니다.

✅ 이전에 JSON을 접한 적이 없다면, [JSON.org documentation](https://www.json.org/)에서 더 자세히 알아볼 수 있습니다.

장치에서 MQTT 브로커로 원격 분석을 보내려면 아래 단계를 따르십시오:

- [아두이노 - Wio 터미널](wio-terminal-telemetry.md)
- [싱글 보드 컴퓨터 - Raspberry Pi/가상 IoT 장치](single-board-computer-telemetry.md)

### MQTT 브로커로부터 텔레메트리 수신

다른 쪽 끝에 수신할 것이 없으면 원격 분석을 보낼 의미가 없습니다. 광도 원격 측정은 데이터를 처리하기 위해 이를 수신하는 무언가가 필요합니다. 이 '서버' 코드는 더 큰 IoT 애플리케이션의 일부로 클라우드 서비스에 배포할 코드 유형이지만, 여기에서는 이 코드를 컴퓨터에서 로컬로(또는 직접 코딩하는 경우 Pi에서 실행할 것입니다). 서버 코드는 가벼운 수준의 MQTT를 통해 원격 분석 메시지를 수신하는 Python 앱으로 구성됩니다. 이 수업의 뒷부분에서 LED를 켜거나 끄도록 지시하는 명령 메시지로 응답하게 할 것입니다.

✅ 조사해보기: 리스너가 없으면 MQTT 메시지는 어떻게 됩니까?

### Python 과 VS Code 설치

Python 및 VS Code를 로컬에 설치하지 않은 경우 서버를 코딩하려면 둘 다 설치해야 합니다. 가상 IoT 장치를 사용 중이거나 Raspberry Pi에서 작업하는 경우 이미 설치 및 구성되어 있어야 하므로 이 단계를 건너뛸 수 있습니다.

### 작업 - Python 과 VS Code 설치

Python 과 VS Code 를 설치합니다.

1. Python을 설치합니다. 최신 버전의 Python 설치에 대한 지침은 [Python downloads page](https://www.python.org/downloads/) 를 참조하십시오.
2. Visual Studio Code (VS Code)를 설치합니다. 이것은 Python으로 가상 장치 코드를 작성하는데 사용할 편집기입니다. VS Code 설치에 대한 지침은 [VS Code documentation](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) 를 참조하십시오.

   > 💁 선호하는 편집기가 있는 경우 이 수업에 IDE 또는 편집기를 자유롭게 사용할 수 있지만, 수업에서는 VS Code 사용을 기반으로 지침을 제공합니다.

3. VS Code Pylance 확장을 설치합니다. 이것은 Python 언어 지원을 제공하는 VS Code 의 확장입니다. VS Code에서 이 확장을 설치하는 방법은 [Pylance extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) 를 참조하십시오.

### Python 가상 환경 구성

Python의 강력한 기능 중 하나는 [pip packages](https://pypi.org/)를 설치하는 것입니다. - 이는 다른 사람이 작성하여 인터넷에 게시한 코드 패키지입니다. 하나의 명령으로 컴퓨터에 pip 패키지를 설치한 다음, 코드에서 해당 패키지를 사용할 수 있습니다. pip를 사용하여 MQTT를 통해 통신하는 패키지를 설치합니다.

기본적으로 패키지를 설치하면 컴퓨터의 모든 곳에서 사용할 수 있으며, 이것은 패키지 버전에 문제를 발생시킬 수 있습니다 - 예를 들어, 패키지의 한 버전에 따라 하나의 응용 프로그램이 다른 응용 프로그램의 새 버전을 설치할 때 중단되는 경우. 이 문제를 해결하기 위해, [Python 가상 환경](https://docs.python.org/3/library/venv.html)을 사용할 수 있습니다, 기본적으로 전용 폴더에 있는 폴더에 있는 Python의 복사본이며 pip 패키지를 설치하면 해당 폴더에만 설치됩니다.

### 작업 - Python 가상 환경 구성

Python 가상 환경을 구성하고 MQTT pip 패키지를 설치합니다.

1. 터미널 또는 명령줄에서 원하는 위치에서 다음을 실행하여 새 디렉터리를 만들고 탐색합니다:

   ```
   mkdir nightlight-server
   cd nightlight-server

   ```

2. 이제 다음을 실행하여 `.venv` 폴더에 가상 환경을 만듭니다.

   ```
   python3 -m venv .venv

   ```

   > 💁 Python 3 (최신 버전) 외에 Python2가 설치된 경우에만 가상 환경을 생성하기 위해 명시적으로 호출해야 합니다. Python2 가 설치된 경우 python 호출 시 Python 3 대신 Python 2 가 사용됩니다.

3. 가상 환경 활성화:

   - On Windows:

     - 명령 프롬프트 또는 Windows 터미널을 통한 명령 프롬프트를 사용하는 경우 다음을 실행합니다:

       ```
       .venv\\Scripts\\activate.bat

       ```

     - PowerShell을 사용하는 경우 다음을 실행합니다:

       ```
       .\\.venv\\Scripts\\Activate.ps1

       ```

   - macOS 또는 Linux에서 다음을 실행합니다:

     ```
     source ./.venv/bin/activate

     ```

   > 💁 이러한 명령은 가상 환경을 만들기 위해 명령을 실행한 동일한 위치에서 실행해야 합니다. .venv 폴더를 탐색할 필요가 없으며, 항상 activate 명령과 아무 명령을 실행하여 패키지를 설치하거나 가상 환경을 만들 때 있떤 폴더에서 코드를 실행해야 합니다.

4. 가상 환경이 활성화 되면, 기본 `python` 명령은 가상 환경을 만드는 데 사용된 Python 버전을 실행합니다. 다음을 실행하여 버전을 가져옵니다:

   ```
   python --version

   ```

   출력은 다음과 유사합니다:

   ```
   (.venv) ➜  nightlight-server python --version
   Python 3.9.1

   ```

   > 💁 Python 버전은 다를 수 있습니다 - 버전 3.6 이상이면 좋습니다. 그렇지 않은 경우, 이 폴더를 삭제하고, 최신 버전의 Python을 설치한 후 다시 시도하십시오.

5. 다음 영령을 실행하여 널리 사용되는 MQTT 라이브러리인 [Paho-MQTT](https://pypi.org/project/paho-mqtt/)용 pip 패키지를 설치하십시오.

   ```
   pip install paho-mqtt

   ```

   이 pip 패키지는 가상 환경에만 설치되며 외부에서는 사용할 수 없습니다.

### 서버 코드 작성

이제 서버 코드를 Python으로 작성할 수 있습니다.

### 작업 - 서버 코드 작성

서버 코드를 작성합니다.

1. 터미널 또는 명령줄에서, 가상 환경 내에서 다음을 실행하여 `app.py`라는 Python 파일을 만듭니다:

   - Windows에서 다음을 실행합니다:

     ```
     type nul > app.py

     ```

   - macOS 또는 Linux에서 다음을 실행합니다:

     ```
     touch app.py

     ```

2. VS Code에서 현재 폴더를 엽니다:

   ```
   code .

   ```

3. VS Code가 시작되면 Python 가상 환경이 활성화됩니다. 이것은 하단 상태 표시줄에 보고됩니다.:

   ![../../../images/vscode-virtual-env.png](../../../../images/vscode-virtual-env.png)

4. VS Code가 시작될 때 VS Code 터미널이 이미 실행 중이면 가상 환경이 활성화되지 않습니다. 가장 쉬운 방법은 **활성 터미널 인스턴스 종료** 버튼을 사용하여 터미널을 종료하는 것입니다.:

   ![../../../images/vscode-kill-terminal.png](../../../../images/vscode-kill-terminal.png)

5. \*Terminal -> New Terminal을 선택하거나, `` CTRL+` ``를 눌러 새 VS Code 터미널을 시작합니다. 새 터미널은 가상 환경을 로드하고 이를 활성화하라는 호출이 터미널에 표시됩니다. 가상 환경의 이름(`.venv`)도 프롬프트에 표시됩니다:

   ```
   ➜  nightlight-server source .venv/bin/activate
   (.venv) ➜  nightlight

   ```

6. VS Code 탐색기에서 `app.py`파일을 열고 다음 코드를 추가합니다:

   ```
   import json
   import time

   import paho.mqtt.client as mqtt

   id = '<ID>'

   client_telemetry_topic = id + '/telemetry'
   client_name = id + 'nightlight_server'

   mqtt_client = mqtt.Client(client_name)
   mqtt_client.connect('test.mosquitto.org')

   mqtt_client.loop_start()

   def handle_telemetry(client, userdata, message):
       payload = json.loads(message.payload.decode())
       print("Message received:", payload)

   mqtt_client.subscribe(client_telemetry_topic)
   mqtt_client.on_message = handle_telemetry

   while True:
       time.sleep(2)

   ```

   6행에서 `<ID>`를 기기 코드를 생성할 때 사용한 고유 ID로 바꿉니다.

   ⚠️ 이것은 **반드시** 장치에서 사용한 것과 동일한 ID 여야 합니다, 그렇지 않으면 서버 코드가 올바른 주제를 구독하거나 게시하지 않습니다.

   이 코드는 고유한 이름으로 MQTT 클라이언트를 생성하고 _[test.mosquitto.org](http://test.mosquitto.org/)_ 브로커에 연결합니다. 그런 다음 구독된 주제에 대한 메시지를 수신하는 백그라운드 스레드에서 실행되는 처리 루프를 시작합니다.

   그런 다음 클라이언트는 원격 분석 주제에 대한 메시지를 구독하고, 메시지가 수신될 때 호출되는 함수를 정의합니다. 원격 측정 메시지가 수신되면, `handle_telemetry` 함수가 호출되어, 수신된 메시지를 콘솔에 인쇄합니다.

   마지막으로 무한 루프는 응용 프로그램이 계속 실행되도록 합니다. MQTT 클라이언트는 백그라운드 스레드에서 메시지를 수신하고 있으며 기본 애플리케이션이 실행 중인 동안 항상 실행됩니다.

7. VS Code 터미널에서, 다음을 실행하여 Python 앱을 실행합니다:

   ```
   python app.py

   ```

   앱이 IoT 장치의 메시지 수신을 시작합니다.

8. 장치가 실행 중이고 원격 분석 메시지를 보내고 있는지 확인하십시오. 물리적 또는 가상 장치에서 감지한 조명 수준을 조정합니다. 수신 중인 메시지가 터미널에 인쇄됩니다.

   ```
   (.venv) ➜  nightlight-server python app.py
   Message received: {'light': 0}
   Message received: {'light': 400}

   ```

nightlight-server 가상 환경의 app.py 파일이 전송되는 메시지를 수신하려면 nightlight 가상 환경의 app.py 파일이 실행 중이어야 합니다.

> 💁 이 코드는 [code-server/server](code-server/server) 폴더에서 찾을 수 있습니다.

### 얼마나 자주 원격 분석을 보내야 합니까?

원격 분석에서 중요한 고려 사항 중 하나는 얼마나 자주 데이터를 측정하고 보내는가? 입니다. 대답은 - 상황에 따라 다르다 입니다. 자주 측정하면 측정 변화에 더 빠르게 대응할 수 있지만, 더 많은 전력, 더 많은 대역폭을 사용하고 더 많은 데이터를 생성하고 처리할 더 많은 클라우드 리소스가 필요합니다. 충분히 자주 측정해야 하지만 너무 자주 측정해서는 안 됩니다.

온도 조절기의 경우, 온도가 자주 변하지 않기 때문에 몇 분마다 측정하는 것으로 충분합니다. If you only measure once a day then you could end up heating your house for nighttime temperatures in the middle of a sunny day, whereas if you measure every second you will have thousands of unnecessarily duplicated temperature measurements that will eat into the users' Internet speed and bandwidth (a problem for people with limited bandwidth plans), use more power which can be a problem for battery powered devices like remote sensors, and increase the cost of the providers cloud computing resources processing and storing them.

공장에서 기계가 고장나면 치명적인 피해를 입히고 수백만 달러의 수익 손실을 초래할 수 있는 기계 주변의 데이터를 모니터링하는 경우, 초당 여러 번 측정해야 할 수 있습니다. 기계가 고장나기 전에 중지하고 수정해야 함을 나타내는 원격 측정을 놓치는 것보다 대역폭을 낭비하는 것이 좋습니다.

> 💁 이 상황에서는, 인터넷에 대한 의존도를 줄이기 위해 원격 분석을 먼저 처리하는 에지 장치를 고려할 수 있습니다.

### 연결 끊김

인터넷 연결은 불안정할 수 있으며 일반적으로 중단됩니다. 이러한 상황에서 IoT 장치는 무엇을 해야 합니까 - 데이터가 손실되어야 합니까, 아니면 연결이 복원될 때까지 저장해야 합니까? 다시 말하지만, 대답은 상황에 따라 다릅니다.

온도 조절기의 경우 새 온도 측정이 수행되자마자 데이터가 손실될 수 있습니다. 난방 시스템은 20분 전에 온도가 19°C인 경우 20.5°C였던 것을 신경 쓰지 않습니다. 난방을 켜야 하는지 여부를 결정하는 것은 지금 온도입니다.

기계류의 경우 특히 추세를 찾는 데 사용되는 경우 데이터를 유지해야 할 수 있습니다. 정의된 기간(예들 들어, 지난 1시간)의 데이터를 살펴보고 비정상적인 데이터를 찾아냄으로써 데이터 스트림의 이상을 감지할 수 있는 기계 학습 모델이 있습니다. 이것은 종종 예측 유지보수에 사용되며, 곧 고장날 수 있다는 표시를 찾아 그 전에 수리하거나 교체할 수 있습니다. 시스템에 대한 모든 원격 분석을 전송하여 이상 감지를 위해 처리할 수 있기를 원할 수 있으므로, IoT 장치가 다시 연결되면 인터넷 중단 중에 생성된 모든 원격 분석이 전송됩니다.

IoT 장치 설계자는 인터넷 중단 또는 위치로 인한 신호 손실 중에 IoT 장치를 사용할 수 있는지도 고려해야 합니다. 스마트 온도 조절기는 정전으로 인해 클라우드에 원격 측정을 보낼 수 없는 경우 난방을 제어하기 위해 몇 가지 제한된 결정을 내릴 수 있어야 합니다.

![../../../images/bricked-car.png](../../../../images/bricked-car.png)

MQTT가 연결 손실을 처리하려면, 장치 및 서버 코드가 필요한 경우 메시지 전달을 보장해야 합니다. 예를 들어 전송된 모든 메시지가 응답 주제에 대한 추가 메시지로 응답되도록 요구하고, 그렇지 않은 경우 나중에 재생할 수 있도록 수동으로 대기열에 추가됩니다.

## 명령

명령은 클라우드에서 장치로 보내는 메시지로, 작업을 수행하도록 지시합니다. 대부분의 경우 이것은 액츄에이터를 통해 일종의 출력을 제공하는 것과 관련이 있지만, 재부팅하거나 추가 원격 측정을 수집하여 명령에 대한 응답으로 반환하는 것과 같은 장치 자체에 대한 명령일 수 있습니다.

![An Internet connected thermostat receiving a command to turn on the heating](../../../../images/commands.png)

온도 조절기는 클라우드에서 난방을 켜라는 명령을 받을 수 있습니다. 모든 센서의 원격 측정 데이터를 기반으로 클라우드 서비스가 난방을 켜야 한다고 결정한 경우 관련 명령을 보냅니다.

### MQTT 브로커에 명령 보내기

인터넷 제어 야간 조명의 다음 단계는 서버 코드가 감지하는 조명 수준에 따라 조명을 제어하기 위해 IoT 장치에 명령을 다시 보내는 것입니다

1. VS Code에서 서버 코드 열기
2. `client_telemetry_topic` 명령을 보낼 주제를 정의하는 선언 뒤에 다음 줄을 추가힙니다:

   ```
   server_command_topic = id + '/commands'

   ```

3. `handle_telemetry` 함수 끝에 다음 코드를 추가합니다:

   ```
   command = { 'led_on' : payload['light'] < 300 }
   print("Sending message:", command)

   client.publish(server_command_topic, json.dumps(command))

   ```

   이것은 명령 주제에 조명이 300 미만인지 여부에 따라 `led_on` 값이 ture나 false로 설정되도록 JSON 메시지를 보냅니다. 조명이 300보다 작으면, LED를 켜도록 장치에 지시하기 위해 true 가 전송됩니다.

4. 이전과 같이 코드를 실행
5. 물리적 또는 가상 장치에서 감지한 조명 수준을 조정합니다. 수신 중인 메시지와 전송 중인 명령이 터미널에 기록됩니다.:

   ```
   (.venv) ➜  nightlight-server python app.py
   Message received: {'light': 0}
   Sending message: {'led_on': True}
   Message received: {'light': 400}
   Sending message: {'led_on': False}

   ```

> 💁 원격 측정과 명령은 각각 단일 주제에 대해 전송됩니다. 여러 장치의 원격 분석은 동일한 원격 분석 항목에 표시되고 여러 장치에 대한 명령은 동일한 명령 항목에 나타남을 의미합니다. 특정 장치에 명령을 보내려면, `/commands/device1`, `/commands/device2`와 같은 고유한 장치 id같은 여러 주제를 사용할 수 있습니다. 그런 식으로 장치는 해당 장치에 대한 메시지를 수신할 수 있습니다.

> 💁 이 코드는 [code-commands/server](code-commands/server) 폴더에서 찾을 수 있습니다.

### IoT 장치에서 명령 처리

이제 서버에서 명령이 전송되므로, IoT 장치에 코드를 추가하여 명령을 처리하고 LED를 제어할 수 있습니다.

MQTT 브로커의 명령을 수신하려면 아래 단계를 따르십시오:

- [아두이노 - Wio 터미널](notion://www.notion.so/wio-terminal-commands.md)
- [싱글 보드 컴퓨터 - Raspberry Pi/가상 IoT 장치](notion://www.notion.so/single-board-computer-commands.md)

이 코드가 작성되고 실행되면 조명 수준을 변경하는 실험을 하십시오. 서버 및 장치의 출력을 관찰하고 조명 수준을 변경할 때 LED를 관찰합니다.

### 연결 끊김

오프라인인 IoT 장치에 명령을 보내야 하는 경우 클라우드 서비스는 어떻게 해야 합니까? 다시 말하지만, 대답은 상황에 따라 다릅니다.

최신 명령이 이전 명령보다 우선하면 이전 명령은 무시할 수 있습니다. 클라우드 서비스가 난방을 켜라는 명령을 보낸 다음, 난방을 끄라는 명령을 보내면, 온 명령을 무시하고 재전송하지 않을 수 있습니다.

만약 명령을 순서대로 처리해야 하는 경우, 예를 들어 로봇 팔을 위로 이동한 다음 그래버를 닫는 경우, 연결이 복원되면 순서대로 전송해야 합니다.

✅ 장치 또는 서버 코드가 필요한 경우 MQTT를 통해 명령이 항상 순서대로 전송되고 처리되도록 하려면 어떻게 해야 합니까?

---

## 🚀 도전

지난 세 수업의 과제는 집, 학교 또는 직장에 있는 IoT 장치를 최대한 많이 나열하고 마이크로컨트롤러 또는 단일 보드 컴퓨터 또는 이 둘을 혼합하여 구축되었는지 여부를 결정하고 어떤 센서와 액추에이터를 사용하고 있는지 생각해 보는 것이었습니다.

이러한 장치의 경우, 어떤 메시지를 보내거나 받을 수 있는지 생각해 보십시오. 어떤 원격 측정을 보내나요? 어떤 메시지나 명령을 받을 수 있습니까? 이것이 안전하다고 생각합니까?

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## 복습 & 독학

[MQTT Wikipedia page](https://wikipedia.org/wiki/MQTT)에서 MQTT에 대해 자세히 알아보세요.

[Mosquitto](https://www.mosquitto.org/) 를 사용하여 MQTT 브로커를 직접 실행하고 IoT 장치와 서버 코드를 연결해보세요.

> 💁 팁 - 기본적으로 Mosquitto는 익명 연결(즉, 사용자 이름과 암호 없이 연결)을 허용하지 않으며, 실행중인 컴퓨터 외부에서 연결을 허용하지 않습니다.
> [`mosquitto.conf` 구성 파일](https://www.mosquitto.org/man/mosquitto-conf-5.html)로 이 문제를 해결할 수 있습니다:
>
> ```
> listener 1883 0.0.0.0
> allow_anonymous true
>
> ```

## 과제

[MQTT를 다른 통신 프로토콜과 비교 및 대조](assignment.ko.md)
