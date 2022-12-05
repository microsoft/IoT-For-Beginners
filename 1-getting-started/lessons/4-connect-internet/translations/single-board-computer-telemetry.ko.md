# 인터넷을 통해 야간 조명 제어하기 - 가상 IoT 하드웨어 및 Raspberry Pi

이 단원에서는 Rasberry Pi나 가상 IoT 장치로 부터 MQTT 브로커로 조명 레벨을 포함한 telemetry를 전송합니다.

## telemetry 게시

다음 단계는 telemetry를 포함한 JSON 문서를 생성하고 MQTT 브로커에게 전송하는 것입니다.

### 작업

MQTT 브로커에게 telemetry를 게시합니다.

1. VS Code에서 야간 조명 프로젝트를 엽니다.

1. 가상 IoT 기기를 사용한다면 터미널이 가상 환경에서 돌아가는지 확인합니다. Raspberry Pi를 사용한다면 가상 환경을 사용하지 않습니다.

1. `app.py` 파일의 상단에 다음을 추가합니다:

   ```python
   import json
   ```

   `json` 라이브러리는 telemetry를 JSON 문서로 인코딩 하는데 사용됩니다.

1. `client_name`의 선언 뒷부분에 다음을 추가합니다:

   ```python
   client_telemetry_topic = id + '/telemetry'
   ```

   `client_telemetry_topic`은 장치가 조명 레벨을 게시할 MQTT 항목입니다.

1. 파일 끝에 있는 `while True:` loop의 내용을 다음으로 바꿉니다:

   ```python
   while True:
       light = light_sensor.light
       telemetry = json.dumps({'light' : light})

       print("Sending telemetry ", telemetry)

       mqtt_client.publish(client_telemetry_topic, telemetry)

       time.sleep(5)
   ```

   이 코드는 조명 레벨을 JSON 문서로 패키지하고 MQTT 브로커에 게시합니다. 그런 다음 메시지를 보내는 빈도를 줄이기 위해 sleep 합니다.

1. 과제의 이전 부분에서 돌렸던 것과 동일한 방법으로 코드를 실행합니다. 가상 IoT 장치를 사용한다면 CounterFit 앱이 실행 중이고 올바른 핀에 광 센서와 LED가 생성되었는지 확인하십시오.

   ```output
   (.venv) ➜  nightlight python app.py
   MQTT connected!
   Sending telemetry  {"light": 0}
   Sending telemetry  {"light": 0}
   ```

> 💁 해당 코드는 [code-telemetry/virtual-device](../code-telemetry/virtual-device) 폴더 또는 [code-telemetry/pi](../code-telemetry/pi) 폴더에서 찾으실 수 있습니다.

😀 장치에서 성공적으로 telemetry를 전송했습니다.
