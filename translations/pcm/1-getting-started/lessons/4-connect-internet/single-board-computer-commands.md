<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-11-18T18:28:46+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "pcm"
}
-->
# Control your nightlight over the Internet - Virtual IoT Hardware and Raspberry Pi

For dis part of di lesson, you go subscribe to commands wey dem send from one MQTT broker go your Raspberry Pi or virtual IoT device.

## Subscribe to commands

Di next step na to subscribe to di commands wey dem send from di MQTT broker and respond to dem.

### Task

Subscribe to commands.

1. Open di nightlight project for VS Code.

1. If you dey use virtual IoT device, make sure say di terminal dey run di virtual environment. If na Raspberry Pi you dey use, you no go need virtual environment.

1. Add dis code after di definitions of di `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

   Di `server_command_topic` na di MQTT topic wey di device go subscribe to take receive LED commands.

1. Add dis code just above di main loop, after di `mqtt_client.loop_start()` line:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

   Dis code dey define one function, `handle_command`, wey go read message as JSON document and go find di value of di `led_on` property. If dem set am to `True`, di LED go turn on, but if no be so, e go turn off.

   Di MQTT client go subscribe to di topic wey di server go dey send messages on, and e go set di `handle_command` function to run anytime message enter.

   > 💁 Di `on_message` handler dey run for all di topics wey you subscribe to. If later you write code wey dey listen to plenty topics, you fit use di `message` object wey dem pass to di handler function to know di topic wey di message come from.

1. Run di code di same way wey you take run di code for di previous part of di assignment. If you dey use virtual IoT device, make sure say di CounterFit app dey run and say you don create di light sensor and LED for di correct pins.

1. Adjust di light levels wey your physical or virtual device dey detect. Messages wey dem dey receive and commands wey dem dey send go show for di terminal. Di LED go dey turn on and off based on di light level.

> 💁 You fit find dis code for di [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) folder or di [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) folder.

😀 You don successfully code your device to dey respond to commands from one MQTT broker.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis document don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) take translate am. Even though we dey try make e accurate, abeg sabi say automated translations fit get mistake or no dey 100% correct. Di original document for di language wey dem write am first na di main correct source. For important information, e better make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->