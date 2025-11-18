<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-11-18T19:39:31+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "pcm"
}
-->
# Publish temperature - Virtual IoT Hardware and Raspberry Pi

For dis part of di lesson, you go publish di temperature wey di Raspberry Pi or Virtual IoT Device detect through MQTT so dem fit use am later calculate GDD.

## Publish di temperature

Once you don read di temperature, you fit publish am through MQTT go one 'server' code wey go read di values, store dem, and prepare dem to use for GDD calculation.

### Task - publish di temperature

Program di device make e publish di temperature data.

1. Open di `temperature-sensor` app project if e no dey open already.

1. Repeat di steps wey you do for lesson 4 to connect to MQTT and send telemetry. You go still use di same public Mosquitto broker.

    Di steps be:

    - Add di MQTT pip package
    - Add di code to connect to di MQTT broker
    - Add di code to publish telemetry

    > ⚠️ Check di [instructions for connecting to MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) and di [instructions for sending telemetry](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) from lesson 4 if you need am.

1. Make sure say di `client_name` match di name of dis project:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. For di telemetry, instead of sending light value, send di temperature value wey you read from di DHT sensor inside one property for di JSON document wey dem call `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Di temperature value no need to dey read too often - e no go change much for short time, so set di `time.sleep` to 10 minutes:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Di `sleep` function dey take di time for seconds, so to make am easy to read, di value dey pass as di result of one calculation. 60s dey inside one minute, so 10 x (60s for one minute) go give 10 minutes delay.

1. Run di code di same way wey you take run di code for di previous part of di assignment. If you dey use virtual IoT device, make sure say di CounterFit app dey run and di humidity and temperature sensors don dey create for di correct pins.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 You fit find dis code for di [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) folder or di [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) folder.

😀 You don successfully publish di temperature as telemetry from your device.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transleshion service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transleshion. Even as we dey try make am accurate, abeg make you sabi say automatik transleshion fit get mistake or no correct well. Di original dokyument wey dey for im native language na di one wey you go take as di correct source. For important mata, e good make you use professional human transleshion. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transleshion.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->