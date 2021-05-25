# Publish temperature - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will publish the temperature values detected by the Raspberry Pi or Virtual IoT Device over MQTT so they can be used later to calculate GDD.

## Publish the temperature

Once the temperature has been read, it can be published over MQTT to some 'server' code that will read the values, and store them ready to be used for a GDD calculation.

### Task - publish the temperature

Program the device to publish the temperature data.

1. Open the `temperature-sensor` app project if it's not already open

1. Repeat the steps you did in lesson 4 to connect to MQTT and send telemetry, You will be using the same public Mosquitto broker.

    The steps for this are:

    - Add the MQTT pip package
    - Add the code to connect to the MQTT broker
    - Add the code to publish telemetry

    > ⚠️ Refer to the [instructions for connecting to MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) and the [instructions for sending telemetry](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) from lesson 4 if needed.

1. Make sure the `client_name` reflects this projects name:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. For the telemetry, instead of sending a light value, send the temperature value read from the DHT sensor in a property on the JSON document called `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. The temperature value doesn't need to be read very often - it won't change much in a short space of time, so set the `time.sleep` to 10 minutes:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 The `sleep` function takes the time in seconds, so to make it easier to read the value is passed as the result of a calculation. 60s in a minute, so 10 x (60s in a minute) gives a 10 minute delay.

1. Run the code in the same way as you ran the code from the previous part of the assignment. If you are using a virtual IoT device, then make sure the CounterFit app is running and the humidity and temperature sensors have been created on the correct pins.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 You can find this code in the [code-publish-temperature/virtual-device](code-publish-temperature/virtual-device) folder or the [code-publish-temperature/pi](code-publish-temperature/pi) folder.

😀 You have successfully published the temperature as telemetry from your device.
