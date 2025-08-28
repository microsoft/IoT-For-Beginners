<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T19:57:23+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "en"
}
-->
# Control your nightlight over the Internet - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will send telemetry data with light levels from your Raspberry Pi or virtual IoT device to an MQTT broker.

## Publish telemetry

The next step is to create a JSON document containing telemetry data and send it to the MQTT broker.

### Task

Send telemetry data to the MQTT broker.

1. Open the nightlight project in VS Code.

1. If you are using a virtual IoT device, ensure the terminal is running the virtual environment. If you are using a Raspberry Pi, you won't need a virtual environment.

1. Add the following import at the top of the `app.py` file:

    ```python
    import json
    ```

    The `json` library is used to encode the telemetry data into a JSON document.

1. Add the following line after the `client_name` declaration:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    The `client_telemetry_topic` is the MQTT topic where the device will publish the light levels.

1. Replace the contents of the `while True:` loop at the end of the file with the following:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    This code packages the light level into a JSON document and publishes it to the MQTT broker. It then pauses to reduce the frequency of messages being sent.

1. Run the code in the same way you ran the code in the previous part of the assignment. If you are using a virtual IoT device, ensure the CounterFit app is running and that the light sensor and LED have been created on the correct pins.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 You can find this code in the [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) folder or the [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) folder.

😀 You have successfully sent telemetry data from your device.

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.