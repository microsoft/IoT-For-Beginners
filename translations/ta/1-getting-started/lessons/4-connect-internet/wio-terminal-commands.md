<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-10-11T11:18:59+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "ta"
}
-->
# உங்கள் இரவுத்தீபத்தை இணையத்தில் கட்டுப்படுத்துங்கள் - Wio Terminal

இந்த பாடத்தின் இந்த பகுதியில், நீங்கள் Wio Terminal-க்கு MQTT broker-ல் இருந்து அனுப்பப்படும் கட்டளைகளை சந்திக்கப் போகிறீர்கள்.

## கட்டளைகளை சந்திக்கவும்

அடுத்த படியாக, MQTT broker-ல் இருந்து அனுப்பப்படும் கட்டளைகளை சந்திக்கவும், அவற்றுக்கு பதிலளிக்கவும்.

### பணிகள்

கட்டளைகளை சந்திக்கவும்.

1. VS Code-ல் nightlight திட்டத்தை திறக்கவும்.

1. `config.h` கோப்பின் கீழ் பின்வரும் குறியீட்டை சேர்த்து, கட்டளைகளுக்கான தலைப்பின் பெயரை வரையறுக்கவும்:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

   `SERVER_COMMAND_TOPIC` என்பது சாதனம் LED கட்டளைகளை பெறுவதற்காக சந்திக்கப்படும் தலைப்பு.

1. MQTT client மீண்டும் இணைக்கப்படும் போது, command topic-ஐ சந்திக்க `reconnectMQTTClient` செயல்பாட்டின் இறுதியில் பின்வரும் வரியை சேர்க்கவும்:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. `reconnectMQTTClient` செயல்பாட்டின் கீழ் பின்வரும் குறியீட்டை சேர்க்கவும்:

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

   இந்த செயல்பாடு MQTT client server-ல் இருந்து ஒரு செய்தியைப் பெறும் போது அழைக்கப்படும் callback ஆக இருக்கும்.

   செய்தி unsigned 8-bit integer களின் வரிசையாக பெறப்படுகிறது, எனவே அதை உரை வடிவமாக நடத்த character array ஆக மாற்ற வேண்டும்.

   செய்தி JSON ஆவணத்தை கொண்டுள்ளது, மேலும் ArduinoJson library-யை பயன்படுத்தி டிகோடு செய்யப்படுகிறது. JSON ஆவணத்தின் `led_on` பண்பை படிக்கிறது, மேலும் அதன் மதிப்பின் அடிப்படையில் LED ஐ ஆன் அல்லது ஆஃப் செய்கிறது.

1. `createMQTTClient` செயல்பாட்டில் பின்வரும் குறியீட்டை சேர்க்கவும்:

    ```cpp
    client.setCallback(clientCallback);
    ```

   இந்த குறியீடு MQTT broker-ல் இருந்து ஒரு செய்தி பெறப்படும் போது அழைக்கப்படும் callback ஆக `clientCallback` ஐ அமைக்கிறது.

   > 💁 `clientCallback` ஹேண்ட்லர் சந்திக்கப்படும் அனைத்து தலைப்புகளுக்கும் அழைக்கப்படுகிறது. நீங்கள் பின்னர் பல தலைப்புகளை கேட்கும் குறியீட்டை எழுதினால், callback செயல்பாட்டிற்கு அனுப்பப்படும் `topic` அளவுருவில் இருந்து செய்தி அனுப்பப்பட்ட தலைப்பை பெறலாம்.

1. உங்கள் Wio Terminal-க்கு குறியீட்டை பதிவேற்றவும், மற்றும் Serial Monitor-ஐ பயன்படுத்தி MQTT broker-க்கு அனுப்பப்படும் ஒளி நிலைகளைப் பாருங்கள்.

1. உங்கள் உடல் அல்லது மெய்நிகர் சாதனத்தால் கண்டறியப்படும் ஒளி நிலைகளை சரிசெய்யவும். நீங்கள் டெர்மினலில் செய்திகளைப் பெறுவதையும், கட்டளைகளை அனுப்புவதையும் காண்பீர்கள். ஒளி நிலையின் அடிப்படையில் LED ஆன் மற்றும் ஆஃப் ஆகும்.

> 💁 இந்த குறியீட்டை [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) கோப்புறையில் காணலாம்.

😀 நீங்கள் MQTT broker-ல் இருந்து அனுப்பப்படும் கட்டளைகளுக்கு பதிலளிக்க உங்கள் சாதனத்தை வெற்றிகரமாக குறியீடு செய்துள்ளீர்கள்.

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை கவனத்தில் கொள்ளவும். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாகக் கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.