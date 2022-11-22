# 인터넷을 통해 야간 조명을 제어 해봅시다. - 가상 IoT와 Raspberry Pi

IoT 장치는 MQTT를 사용하여 *test.mosquitto.org*와 통신하도록 코딩됩니다. 이는 광센서 판독값과 함께 원격 측정값을 전송하고 LED를 제어하는 명령을 수신하기 위함입니다.

이 강의에서는 여러분의  Raspberry Pi나 가상 IoT 장치에 MQTT broker를 연결하고자 합니다.

## MQTT 사용자 패키지를 설치합니다.

MQTT broker와 통신하기 위해서, 여러분은 MQTT 라이브러리 pip 패키지를 Pi 혹은 사용하시는 가상환경에 설치합니다.

### 작업

pip 패키지를 설치합니다.

1. 야간조명 프로젝트를 VS code에서 열어줍니다.

1. 만약 여러분이 가상 IoT device를 사용하고 있다면 가상환경 터미널이 실행중인지 확인해주세요. 여러분이 Raspberry Pi를 사용하고 있다면 가상환경은 사용하지 않습니다.

1. 아래 코드를 실행하여 MQTT pip 패키지를 설치 해 주세요:

    ```sh
    pip3 install paho-mqtt
    ```

## 코딩을 진행합니다.

이제 코딩을 진행할 준비가 되었습니다.

### 작업

코드를 작성 해 주세요

1. 아래 코드를 `app.py` 맨 위에 import합니다:

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client` 라이브를 사용하여 MQTT와 통신할 수 있습니다.

1. 광센서 및 LED 정의 뒤에 아래 코드를 추가합니다.

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    `<ID>`를 고유 ID로 교체합니다. 이는 장치 사용자의 이름으로 사용 될 것이며 이후에 이 장치가 publish하고 subscribe하는 항목에 사용됩니다. *test.mosquitto.org*는 public 이며 이 과제를 수행하는 다른 학생들을 포함한 많은 사람들에게 사용됨니다. 고유한 MQTT 사용자 이름과 주제를 사용하면 다른 사용자와 충돌하지 않습니다. 이 ID는 이번 과제 이후에 서버 코드를 생성할 때 또한 필요합니다.

    > 💁 고유한ID를 생성하기 위해 [GUIDGen](https://www.guidgen.com) 사이트를 이용할 수 있습니다..

    `client_name` 는 broker에서의 MQTT 사용자의 고유한 이름입니다.

1. 아래 코드를 이 새로운 코드 아래에 추가하여 MQTT 사용자 객체를 생성하고 MQTT broker에 연결합니다.:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    이 코드는 사용자 객체를 생성하고, public MQTT broker에 연결하며, subscribe된 topic에 대한 메세지를 수신하는 백그라운드 스레드에서 처리 루프를 실행합니다.
    
1. 이전 과제에서 실행한 것 과 동일한 방법으로 코드를 실행합니다. 가상 IoT 장치를 사용하는 경우 CouterFit 앱이 실행중인지, 관센서와 LED가 올바른 핀에 생성되었는지 확인해주세요.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 [code-mqtt/virtual-device](code-mqtt/virtual-device) 폴더나 [code-mqtt/pi](code-mqtt/pi) 폴더에서 코드를 찾을 수 있습니다.

😀 여러분은 여러분의 장치와 MQTT broker를 성공적으로 연결하였습니다.
