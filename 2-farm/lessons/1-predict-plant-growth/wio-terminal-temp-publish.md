# Publish temperature - Wio Terminal

In this part of the lesson, you will publish the temperature values detected by the Wio Terminal over MQTT so they can be used later to calculate GDD.

## Publish the temperature

Once the temperature has been read, it can be published over MQTT to some 'server' code that will read the values, and store them ready to be used for a GDD calculation. Microcontrollers don't read the time from the Internet and track the time with a real-time clock out of the box, the device needs to be programmed to do this, assuming it has the necessary hardware.

To simplify things for this lesson, the time won't be sent with the sensor data, instead it can be added by the server code later when it receives the messages.

### Task

Program the device to publish the temperature data.

1. Open the `temperature-sensor` Wio Terminal project

1. Repeat the steps you did in lesson 4 to connect to MQTT and send telemetry, You will be using the same public Mosquitto broker.

    The steps for this are:

    - Add the Seeed WiFi and MQTT libraries to the `.ini` file
    - Add the config file and code to connect to WiFi
    - Add the code to connect to the MQTT broker
    - Add the code to publish telemetry

    > ⚠️ Refer to the [instructions for connecting to MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) and the [instructions for sending telemetry](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) from lesson 4 if needed.

1. Make sure the `CLIENT_NAME` in the `config.h` header file reflects this project:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. For the telemetry, instead of sending a light value, send the temperature value read from the DHT sensor in a property on the JSON document called `temperature` by changing the `loop` function in `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. The temperature value doesn't need to be read very often - it won't change much in a short space of time, so set the `delay` in the `loop` function to 10 minutes:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 The `delay` function takes the time in milliseconds, so to make it easier to read the value is passed as the result of a calculation. 1,000ms in a second, 60s in a minute, so 10 x (60s in a minute) x (1000ms in a second) gives a 10 minute delay.

1. Upload this to your Wio Terminal, and use the serial monitor to see the temperature being sent to the MQTT broker.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 You can find this code in the [code-publish-temperature/wio-terminal](code-publish-temperature/wio-terminal) folder.

😀 You have successfully published the temperature as telemetry from your device.
