<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-11-18T19:38:15+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "pcm"
}
-->
# Publish temperature - Wio Terminal

For dis part of di lesson, you go publish di temperature wey di Wio Terminal detect through MQTT so dem fit use am later to calculate GDD.

## Publish di temperature

Once you don read di temperature, you fit publish am through MQTT go one 'server' code wey go read di values, and keep dem ready to use for GDD calculation. Microcontrollers no dey read time from Internet or track time with real-time clock by default, di device go need make you program am to do dis, if e get di hardware wey fit do am.

To make di lesson easy, di time no go dey sent with di sensor data, instead di server code go add am later when e receive di messages.

### Task

Program di device to publish di temperature data.

1. Open di `temperature-sensor` Wio Terminal project

1. Repeat di steps wey you do for lesson 4 to connect to MQTT and send telemetry. You go use di same public Mosquitto broker.

    Di steps be:

    - Add di Seeed WiFi and MQTT libraries to di `.ini` file
    - Add di config file and code to connect to WiFi
    - Add di code to connect to di MQTT broker
    - Add di code to publish telemetry

    > ⚠️ Check di [instructions for connecting to MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) and di [instructions for sending telemetry](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) from lesson 4 if you need am.

1. Make sure say di `CLIENT_NAME` for di `config.h` header file match dis project:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. For di telemetry, instead of sending light value, send di temperature value wey you read from di DHT sensor inside one property for di JSON document wey dem call `temperature` by changing di `loop` function for `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Di temperature value no need to dey read too often - e no go change much for short time, so set di `delay` for di `loop` function to 10 minutes:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Di `delay` function dey take di time for milliseconds, so to make am easy to read, di value go dey passed as di result of one calculation. 1,000ms dey inside one second, 60s dey inside one minute, so 10 x (60s for one minute) x (1000ms for one second) go give 10 minute delay.

1. Upload dis go your Wio Terminal, and use di serial monitor to see di temperature wey dem dey send go di MQTT broker.

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

> 💁 You fit find dis code for di [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) folder.

😀 You don successfully publish di temperature as telemetry from your device.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis docu wey you dey see don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) take translate am. Even though we dey try make sure say e correct, make you sabi say translation wey machine do fit get mistake or no too accurate. Di original docu for di language wey dem first write am na di main correct one. If na important information, e go better make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->