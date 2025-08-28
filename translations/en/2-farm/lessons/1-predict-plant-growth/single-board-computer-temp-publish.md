<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T20:39:20+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "en"
}
-->
# Publish temperature - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will send the temperature values detected by the Raspberry Pi or Virtual IoT Device via MQTT so they can later be used to calculate GDD.

## Publish the temperature

After reading the temperature, it can be sent via MQTT to some 'server' code that will process the values and store them for GDD calculations.

### Task - publish the temperature

Program the device to send the temperature data.

1. Open the `temperature-sensor` app project if it’s not already open.

1. Repeat the steps you followed in lesson 4 to connect to MQTT and send telemetry. You will use the same public Mosquitto broker.

    The steps are:

    - Add the MQTT pip package.
    - Add the code to connect to the MQTT broker.
    - Add the code to send telemetry.

    > ⚠️ Refer to the [instructions for connecting to MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) and the [instructions for sending telemetry](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) from lesson 4 if needed.

1. Ensure the `client_name` matches the name of this project:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. For telemetry, instead of sending a light value, send the temperature value read from the DHT sensor as a property in the JSON document called `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. The temperature doesn’t need to be read frequently—it won’t change much in a short period. Set the `time.sleep` to 10 minutes:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 The `sleep` function takes the time in seconds, so to make it easier to understand, the value is passed as the result of a calculation. Since there are 60 seconds in a minute, 10 x (60 seconds per minute) results in a 10-minute delay.

1. Run the code the same way you ran the code in the previous part of the assignment. If you’re using a virtual IoT device, ensure the CounterFit app is running and the humidity and temperature sensors are set up on the correct pins.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 You can find this code in the [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) folder or the [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) folder.

😀 You’ve successfully sent the temperature as telemetry from your device.

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.