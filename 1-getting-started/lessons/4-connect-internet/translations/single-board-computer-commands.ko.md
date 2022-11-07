# 인터넷을 통해 야간 조명 제어하기 - 가상 IoT 하드웨어 및 Raspberry Pi

강의에서 MQTT 브로커에서 Raspberry Pi 또는 가상 IoT 장치로 전송된 명령을 실행하게 됩니다.

## 명령 실행하기

다음 단계는 MQTT 브로커에서 보낸 명령을 실행하고 이에 응답하는 것입니다.

### 작업

명령을 실행합니다.

1. VS Code에서 야간 조명 프로젝트를 엽니다.

2. 가상 IoT 장치를 사용하는 경우, 터미널이 가상 환경을 실행 중인지 확인하십시오. Raspberry Pi 를 사용하는 경우 가상 환경을 사용하지 않습니다.

3. `client_telemetry_topic`의 정위 뒤에 다음 코드를 추가합니다.:

   ```python
   server_command_topic = id + '/commands'
   ```

   `server_command_topic` 는 장치가 LED 명령을 수신하기 위해 실행될 MQTT 주제입니다.

4. main loop 바로 위의 `mqtt_client.loop_start()` 라인 뒤에 다음 코드를 추가합니다:

   ```python
   def handle_command(client, userdata, message):
       payload = json.loads(message.payload.decode())
       print("Message received:", payload)

       if payload['led_on']:
           led.on()
       else:
           led.off()

   mqtt_client.subscribe(server_command_topic)
   mqtt_client.on_message = handle_command
   ```

   이 코드는 `handle_command` 함수를 정의합니다, 이는 메시지를 JSON 문서로 읽고 `led_on` 속성 값을 찾는 함수입니다. `True` 로 설정되면 LED가 켜지고, 그렇지 않다면 LED는 꺼집니다.

   MQTT 클라이언트는 서버가 메시지를 보낼 주제를 실행하고 메시지가 수신될 때 `handle_command` 함수가 호출되도록 설정합니다.

   > 💁 `on_message` 핸들러는 실행된 모든 주제에 대해 호출됩니다. 나중에 여러 주제를 수신하는 코드를 작성하면, 핸들러 함수를 거쳐 보내진 `message` 객체의 주제를 얻을 수 있습니다.

5. 과제의 이전 부분과 동일한 방식으로 코드를 실행합니다. 가상 IoT 장치를 사용하는 경우, CounterFit 앱이 실행중이고 LED가 올바른 핀에 생성되었는지 확인하십시오.

6. 물리적 또는 가상 장치에서 감지한 조명 수준을 조정합니다. 수신 중인 메시지와 전송 중인 명령이 터미널에 기록됩니다. LED도 조명 수준에 따라 켜지고 꺼질 것입니다.

> 💁 이 코드는 [code-commands/virtual-device](../code-commands/virtual-device) 폴더 또는 [code-commands/pi](../code-commands/pi) 폴더에서 찾을 수 있습니다.

😀 장치가 MQTT 브로커의 명령에 응답하도록 성공적으로 코딩했습니다.
