<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T12:30:19+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "mr"
}
-->
# इंटरनेटद्वारे तुमचा नाईटलाइट नियंत्रित करा - Wio Terminal

या धड्याच्या या भागात, तुम्ही Wio Terminal वरून प्रकाश पातळीचे टेलीमेट्री MQTT ब्रोकर्सोबत पाठवाल.

## JSON Arduino लायब्ररी इंस्टॉल करा

MQTT वर संदेश पाठवण्याचा एक लोकप्रिय मार्ग म्हणजे JSON वापरणे. JSON वाचणे आणि लिहिणे सोपे करण्यासाठी Arduino साठी एक JSON लायब्ररी उपलब्ध आहे.

### कार्य

Arduino JSON लायब्ररी इंस्टॉल करा.

1. VS Code मध्ये नाईटलाइट प्रकल्प उघडा.

1. `platformio.ini` फाइलमधील `lib_deps` यादीत खालील ओळ अतिरिक्त म्हणून जोडा:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    हे [ArduinoJson](https://arduinojson.org), एक Arduino JSON लायब्ररी आयात करते.

## टेलीमेट्री प्रकाशित करा

पुढील पाऊल म्हणजे टेलीमेट्रीसाठी JSON दस्तऐवज तयार करणे आणि तो MQTT ब्रोकर्सोबत पाठवणे.

### कार्य - टेलीमेट्री प्रकाशित करा

MQTT ब्रोकर्सोबत टेलीमेट्री प्रकाशित करा.

1. MQTT ब्रोकर्ससाठी टेलीमेट्री टॉपिक नाव परिभाषित करण्यासाठी `config.h` फाइलच्या तळाशी खालील कोड जोडा:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` हा टॉपिक आहे ज्यावर डिव्हाइस प्रकाश पातळी प्रकाशित करेल.

1. `main.cpp` फाइल उघडा.

1. फाइलच्या शीर्षस्थानी खालील `#include` निर्देश जोडा:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` फंक्शनमध्ये, `delay` च्या अगोदर खालील कोड जोडा:

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

    हा कोड प्रकाश पातळी वाचतो आणि ArduinoJson वापरून या पातळीचा समावेश असलेला JSON दस्तऐवज तयार करतो. नंतर हा दस्तऐवज स्ट्रिंगमध्ये रूपांतरित केला जातो आणि MQTT क्लायंटद्वारे टेलीमेट्री MQTT टॉपिकवर प्रकाशित केला जातो.

1. कोड Wio Terminal वर अपलोड करा आणि Serial Monitor वापरून प्रकाश पातळी MQTT ब्रोकर्सोबत पाठवली जात असल्याचे पाहा.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 तुम्हाला हा कोड [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) फोल्डरमध्ये सापडेल.

😀 तुम्ही तुमच्या डिव्हाइसवरून यशस्वीरित्या टेलीमेट्री पाठवली आहे.

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरे त्रुटी किंवा अचूकतेच्या अभावाने युक्त असू शकतात. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.