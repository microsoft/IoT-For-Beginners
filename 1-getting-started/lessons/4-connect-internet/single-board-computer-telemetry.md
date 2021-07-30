# Control your nightlight over the Internet - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will send telemetry with light levels from your Raspberry Pi or virtual IoT device to an MQTT broker.

## Publish telemetry

The next step is to create a JSON document with telemetry and send it to the MQTT broker.

### Task

Publish telemetry to the MQTT broker.

1. Open the nightlight project in VS Code.

1. If you are using a virtual IoT device, ensure the terminal is running the virtual environment. If you are using a Raspberry Pi you won't be using a virtual environment.

1. Add the following import to the top of the `app.py` file:

    ```python
    import json
    ```

    The `json` library is used to encode the telemetry as a JSON document.

1. Add the following after the `client_name` declaration:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    The `client_telemetry_topic` is the MQTT topic the device will publish light levels to.

1. Replace the contents of the `while True:` loop at the end of the file with the following:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    This code packages the light level into a JSON document and publishes it to the MQTT broker. It then sleeps to reduce the frequency that messages are sent.

1. Run the code in the same way as you ran the code from the previous part of the assignment. If you are using a virtual IoT device, then make sure the CounterFit app is running and the light sensor and LED have been created on the correct pins.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 You can find this code in the [code-telemetry/virtual-device](code-telemetry/virtual-device) folder or the [code-telemetry/pi](code-telemetry/pi) folder.

😀 You have successfully sent telemetry from your device.
