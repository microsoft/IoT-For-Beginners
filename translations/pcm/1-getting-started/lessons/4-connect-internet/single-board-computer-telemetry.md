<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-11-18T18:26:22+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "pcm"
}
-->
# Control your nightlight for Internet - Virtual IoT Hardware and Raspberry Pi

For dis part of di lesson, you go send telemetry wey get light levels from your Raspberry Pi or virtual IoT device go one MQTT broker.

## Publish telemetry

Di next step na to create one JSON document wey get telemetry and send am go di MQTT broker.

### Task

Publish telemetry go di MQTT broker.

1. Open di nightlight project for VS Code.

1. If you dey use virtual IoT device, make sure say di terminal dey run di virtual environment. If na Raspberry Pi you dey use, you no go need virtual environment.

1. Add dis import for di top of di `app.py` file:

    ```python
    import json
    ```

   Di `json` library na im dem dey use to encode di telemetry as JSON document.

1. Add dis one after di `client_name` declaration:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

   Di `client_telemetry_topic` na di MQTT topic wey di device go dey publish di light levels put.

1. Change wetin dey inside di `while True:` loop for di end of di file to dis one:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

   Dis code go package di light level inside JSON document and publish am go di MQTT broker. E go then sleep small to reduce how often e dey send message.

1. Run di code di same way wey you take run di code for di previous part of di assignment. If you dey use virtual IoT device, make sure say di CounterFit app dey run and di light sensor and LED don dey set for di correct pins.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 You fit find dis code for di [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) folder or di [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) folder.

😀 You don successfully send telemetry from your device.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis document don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) take translate am. Even though we dey try make e accurate, abeg sabi say automated translations fit get mistake or no dey 100% correct. Di original document for di native language na di main correct source. For important information, e better make una use professional human translation. We no go fit take responsibility for any misunderstanding or wrong interpretation wey fit happen because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->