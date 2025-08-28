<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T19:56:08+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "en"
}
-->
# Control your nightlight over the Internet - Wio Terminal

In this part of the lesson, you will configure your Wio Terminal to receive and respond to commands sent from an MQTT broker.

## Subscribe to commands

The next step is to set up your device to subscribe to commands sent from the MQTT broker and act on them.

### Task

Subscribe to commands.

1. Open the nightlight project in VS Code.

1. Add the following code at the end of the `config.h` file to define the topic name for the commands:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    The `SERVER_COMMAND_TOPIC` is the topic your device will subscribe to in order to receive LED control commands.

1. Add the following line at the end of the `reconnectMQTTClient` function to subscribe to the command topic whenever the MQTT client reconnects:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Insert the following code below the `reconnectMQTTClient` function:

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

    This function serves as the callback that the MQTT client will invoke when it receives a message from the server.

    Since the message is received as an array of unsigned 8-bit integers, it needs to be converted into a character array to process it as text.

    The message contains a JSON document, which is decoded using the ArduinoJson library. The `led_on` property in the JSON document is read, and based on its value, the LED is either turned on or off.

1. Add the following code to the `createMQTTClient` function:

    ```cpp
    client.setCallback(clientCallback);
    ```

    This code sets `clientCallback` as the function to be called whenever a message is received from the MQTT broker.

    > 💁 The `clientCallback` function is triggered for all subscribed topics. If you later add code to listen to multiple topics, you can use the `topic` parameter passed to the callback function to identify which topic the message belongs to.

1. Upload the code to your Wio Terminal, and use the Serial Monitor to observe the light levels being sent to the MQTT broker.

1. Adjust the light levels detected by your physical or virtual device. You will see messages being received and commands being sent in the terminal. The LED will turn on or off based on the detected light level.

> 💁 You can find this code in the [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) folder.

😀 Congratulations! Your device is now successfully programmed to respond to commands from an MQTT broker.

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.