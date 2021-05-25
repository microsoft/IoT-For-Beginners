# Control your nightlight over the Internet - Wio Terminal

In this part of the lesson, you will subscribe to commands sent from an MQTT broker to your Wio Terminal.

## Subscribe to commands

The next step is to subscribe to the commands sent from the MQTT broker, and respond to them.

### Task

Subscribe to commands.

1. Open the nightlight project in VS Code.

1. Add the following code to the bottom of the `config.h` file to define the topic name for the commands:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    The `SERVER_COMMAND_TOPIC` is the topic the device will subscribe to to receive LED commands.

1. Add the following line to the end of the `reconnectMQTTClient` function to subscribe to the command topic when the MQTT client is reconnected:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Add the following code below the `reconnectMQTTClient` function.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    This function will be the callback that the MQTT client will call when it receives a message from the server.

    The message is received as an array of unsigned 8-bit integers, so needs to be converted to a character array to be treated as text.

    The message contains a JSON document, and is decoded using the ArduinoJson library. The `led_on` property of the JSON document is read, and depending on the value the LED is turned on or off.

1. Add the following code to the `createMQTTClient` function:

    ```cpp
    client.setCallback(clientCallback);
    ```

    This code sets the `clientCallback` as the callback to be called when a message is received from the MQTT broker.

    > 💁 The `clientCallback` handler is called for all topics subscribed to. If you later write code that listens to multiple topics, you can get the topic that the message was sent to from the `topic` parameter passed to the callback function.

1. Upload the code to your Wio Terminal, and use the Serial Monitor to see the light levels being sent to the MQTT broker.

1. Adjust the light levels detected by your physical or virtual device. You will see messages being received and commands being sent in the terminal. You will also see the LED being turned on and off depending on the light level.

> 💁 You can find this code in the [code-commands/wio-terminal](code-commands/wio-terminal) folder.

😀 You have successfully coded your device to respond to commands from an MQTT broker.
