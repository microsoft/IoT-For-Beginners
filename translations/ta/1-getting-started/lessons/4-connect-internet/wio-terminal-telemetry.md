<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-10-11T11:20:02+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "ta"
}
-->
# உங்கள் இரவுக்கால விளக்கை இணையத்தின் மூலம் கட்டுப்படுத்துங்கள் - Wio Terminal

இந்த பாடத்தின் இந்த பகுதியில், உங்கள் Wio Terminal-இல் இருந்து ஒளி நிலைகளை கொண்ட டெலிமெட்ரியை MQTT broker-க்கு அனுப்புவீர்கள்.

## JSON Arduino நூலகங்களை நிறுவவும்

MQTT மூலம் செய்திகளை அனுப்புவதற்கான பிரபலமான வழி JSON ஆகும். JSON ஆவணங்களை படிக்கவும் எழுதவும் எளிதாக்கும் Arduino நூலகம் ஒன்று உள்ளது.

### பணிகள்

Arduino JSON நூலகத்தை நிறுவவும்.

1. VS Code-ல் இரவுக்கால விளக்கு திட்டத்தை திறக்கவும்.

1. `platformio.ini` கோப்பில் உள்ள `lib_deps` பட்டியலில் கூடுதல் வரியாக பின்வரும் வரியை சேர்க்கவும்:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    இது [ArduinoJson](https://arduinojson.org), ஒரு Arduino JSON நூலகத்தை இறக்குமதி செய்கிறது.

## டெலிமெட்ரியை வெளியிடவும்

அடுத்த படியாக, டெலிமெட்ரியுடன் ஒரு JSON ஆவணத்தை உருவாக்கி, அதை MQTT broker-க்கு அனுப்ப வேண்டும்.

### பணி - டெலிமெட்ரியை வெளியிடவும்

MQTT broker-க்கு டெலிமெட்ரியை வெளியிடவும்.

1. MQTT broker-க்கான டெலிமெட்ரி தலைப்பின் பெயரை வரையறுக்க `config.h` கோப்பின் கீழே பின்வரும் குறியீட்டை சேர்க்கவும்:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` என்பது சாதனம் ஒளி நிலைகளை வெளியிடும் தலைப்பு ஆகும்.

1. `main.cpp` கோப்பை திறக்கவும்.

1. கோப்பின் மேல் பின்வரும் `#include` இயக்கத்தை சேர்க்கவும்:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` செயல்பாட்டின் உள்ளே, `delay`க்கு முன் பின்வரும் குறியீட்டை சேர்க்கவும்:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    இந்த குறியீடு ஒளி நிலையை படித்து, இந்த நிலையை கொண்ட ArduinoJson மூலம் ஒரு JSON ஆவணத்தை உருவாக்குகிறது. பின்னர் இது ஒரு சரியாக மாற்றப்பட்டு, MQTT கிளையண்ட் மூலம் டெலிமெட்ரி MQTT தலைப்பில் வெளியிடப்படுகிறது.

1. உங்கள் Wio Terminal-க்கு குறியீட்டை பதிவேற்றவும், மற்றும் Serial Monitor-ஐ பயன்படுத்தி ஒளி நிலைகள் MQTT broker-க்கு அனுப்பப்படுவதைப் பாருங்கள்.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 இந்த குறியீட்டை [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) கோப்புறையில் காணலாம்.

😀 நீங்கள் உங்கள் சாதனத்திலிருந்து வெற்றிகரமாக டெலிமெட்ரியை அனுப்பியுள்ளீர்கள்.

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. எங்கள் தரச்சிறப்பிற்காக முயற்சிப்பதுடன், தானியக்க மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை கவனத்தில் கொள்ளவும். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.