<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-11-18T18:30:43+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "pcm"
}
-->
# Control your nightlight for Internet - Virtual IoT Hardware and Raspberry Pi

Di IoT device go need code wey go fit connect wit *test.mosquitto.org* using MQTT to send telemetry values wit di light sensor reading, and receive commands to control di LED.

For dis part of di lesson, you go connect your Raspberry Pi or virtual IoT device to one MQTT broker.

## Install di MQTT client package

To fit communicate wit di MQTT broker, you go need install one MQTT library pip package either for your Pi, or for your virtual environment if you dey use virtual device.

### Task

Install di pip package

1. Open di nightlight project for VS Code.

1. If you dey use virtual IoT device, make sure say di terminal dey run di virtual environment. If you dey use Raspberry Pi, you no go dey use virtual environment.

1. Run dis command to install di MQTT pip package:

    ```sh
    pip3 install paho-mqtt
    ```

## Code di device

Di device don ready to code.

### Task

Write di device code.

1. Add dis import for di top of di `app.py` file:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Di `paho.mqtt.client` library go allow your app to communicate wit MQTT.

1. Add dis code after di definitions of di light sensor and LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Replace `<ID>` wit one unique ID wey go be di name of dis device client, and later for di topics wey dis device dey publish and subscribe to. Di *test.mosquitto.org* broker na public and e dey used by many people, including other students wey dey work on dis assignment. To get unique MQTT client name and topic names go make sure say your code no go clash wit anybody own. You go also need dis ID when you dey create di server code later for dis assignment.

    > 💁 You fit use one website like [GUIDGen](https://www.guidgen.com) to generate one unique ID.

    Di `client_name` na unique name for dis MQTT client for di broker.

1. Add dis code below dis new code to create one MQTT client object and connect to di MQTT broker:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Dis code dey create di client object, connect to di public MQTT broker, and e dey start one processing loop wey dey run for background thread dey listen for messages for any subscribed topics.

1. Run di code di same way wey you run di code from di previous part of di assignment. If you dey use virtual IoT device, make sure say di CounterFit app dey run and di light sensor and LED don dey created for di correct pins.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 You fit find dis code for di [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) folder or di [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) folder.

😀 You don successfully connect your device to one MQTT broker.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis docu don dey translate wit AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). Even though we dey try make am accurate, abeg sabi say automatic translation fit get mistake or no dey 100% correct. Di original docu for di language wey dem write am first na di main correct one. For important information, e go beta make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->