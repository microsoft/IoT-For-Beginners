<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T19:57:43+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "en"
}
-->
# Control your nightlight over the Internet - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will subscribe to commands sent from an MQTT broker to your Raspberry Pi or virtual IoT device.

## Subscribe to commands

The next step is to subscribe to the commands sent from the MQTT broker and respond to them.

### Task

Subscribe to commands.

1. Open the nightlight project in VS Code.

1. If you are using a virtual IoT device, ensure the terminal is running the virtual environment. If you are using a Raspberry Pi, you won't be using a virtual environment.

1. Add the following code after the definitions of the `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    The `server_command_topic` is the MQTT topic the device will subscribe to in order to receive LED commands.

1. Add the following code just above the main loop, after the `mqtt_client.loop_start()` line:

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

    This code defines a function, `handle_command`, that reads a message as a JSON document and looks for the value of the `led_on` property. If it is set to `True`, the LED is turned on; otherwise, it is turned off.

    The MQTT client subscribes to the topic where the server will send messages and sets the `handle_command` function to be called when a message is received.

    > 💁 The `on_message` handler is called for all topics subscribed to. If you later write code that listens to multiple topics, you can get the topic that the message was sent to from the `message` object passed to the handler function.

1. Run the code in the same way as you ran the code from the previous part of the assignment. If you are using a virtual IoT device, make sure the CounterFit app is running and the light sensor and LED have been created on the correct pins.

1. Adjust the light levels detected by your physical or virtual device. Messages being received and commands being sent will be written to the terminal. The LED will also turn on and off depending on the light level.

> 💁 You can find this code in the [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) folder or the [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) folder.

😀 You have successfully coded your device to respond to commands from an MQTT broker.

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.