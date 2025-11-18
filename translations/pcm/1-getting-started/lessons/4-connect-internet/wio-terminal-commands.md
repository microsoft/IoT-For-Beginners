<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-11-18T18:26:50+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "pcm"
}
-->
# Control your nightlight for Internet - Wio Terminal

For dis part of di lesson, you go subscribe to commands wey dem send from MQTT broker go your Wio Terminal.

## Subscribe to commands

Di next step na to subscribe to di commands wey dem send from di MQTT broker, and respond to dem.

### Task

Subscribe to commands.

1. Open di nightlight project for VS Code.

1. Add dis code for di bottom of di `config.h` file to define di topic name for di commands:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    Di `SERVER_COMMAND_TOPIC` na di topic wey di device go subscribe to so e fit receive LED commands.

1. Add dis line for di end of di `reconnectMQTTClient` function to subscribe to di command topic when di MQTT client reconnect:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Add dis code below di `reconnectMQTTClient` function.

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

    Dis function na di callback wey di MQTT client go call when e receive message from di server.

    Di message dey come as array of unsigned 8-bit integers, so e need to change am to character array so e fit treat am as text.

    Di message get JSON document inside, and e dey decode am using di ArduinoJson library. Di `led_on` property for di JSON document go dey read, and based on di value, di LED go turn on or off.

1. Add dis code to di `createMQTTClient` function:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Dis code go set di `clientCallback` as di callback wey dem go call when message dey received from di MQTT broker.

    > 💁 Di `clientCallback` handler dey call for all topics wey you subscribe to. If later you write code wey dey listen to plenty topics, you fit get di topic wey dem send di message to from di `topic` parameter wey dem pass to di callback function.

1. Upload di code go your Wio Terminal, and use di Serial Monitor to see di light levels wey dem dey send go di MQTT broker.

1. Adjust di light levels wey your physical or virtual device dey detect. You go see messages wey dem dey receive and commands wey dem dey send for di terminal. You go also see di LED dey turn on and off based on di light level.

> 💁 You fit find dis code for di [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) folder.

😀 You don successfully code your device to respond to commands from one MQTT broker.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) take translate am. Even though we dey try make sure say e correct, abeg sabi say automated translation fit get mistake or no dey accurate well. Di original dokyument for im native language na di main correct source. For important information, e go beta make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->