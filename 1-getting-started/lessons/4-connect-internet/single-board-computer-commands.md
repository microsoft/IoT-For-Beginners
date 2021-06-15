# Control your nightlight over the Internet - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will subscribe to commands sent from an MQTT broker to your Raspberry Pi or virtual IoT device.

## Subscribe to commands

The next step is to subscribe to the commands sent from the MQTT broker and respond to them.

### Task

Subscribe to commands.

1. Open the nightlight project in VS Code.

1. If you are using a virtual IoT device, ensure the terminal is running the virtual environment

1. Add the following code after the definitions of the `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    The `server_command_topic` is the MQTT topic the device will subscribe to receive LED commands.

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

    This code defines a function, `handle_command`, that reads a message as a JSON document and looks for the value of the `led_on` property. If it is set to `True` the LED is turned on, otherwise it is turned off.

    The MQTT client subscribes on the topic that the server will send messages on and sets the `handle_command` function to be called when a message is received.

    > 💁 The `on_message` handler is called for all topics subscribed to. If you later write code that listens to multiple topics, you can get the topic that the message was sent to from the `message` object passed to the handler function.

1. Run the code in the same way as you ran the code from the previous part of the assignment. If you are using a virtual IoT device, then make sure the CounterFit app is running and the light sensor and LED have been created on the correct pins.

1. Adjust the light levels detected by your physical or virtual device. You will see messages being received and commands being sent in the terminal. You will also see the LED is being turned on and off depending on the light level.

> 💁 You can find this code in the [code-commands/virtual-device](code-commands/virtual-device) folder or the [code-commands/pi](code-commands/pi) folder.

😀 You have successfully coded your device to respond to commands from an MQTT broker.
