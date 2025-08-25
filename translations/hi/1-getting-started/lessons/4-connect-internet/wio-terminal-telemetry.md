<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-25T17:17:08+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "hi"
}
-->
# इंटरनेट के माध्यम से अपनी नाइटलाइट को नियंत्रित करें - Wio Terminal

इस पाठ के इस भाग में, आप अपने Wio Terminal से प्रकाश स्तरों के साथ टेलीमेट्री को MQTT ब्रोकर्स पर भेजेंगे।

## JSON Arduino लाइब्रेरीज़ इंस्टॉल करें

MQTT पर संदेश भेजने का एक लोकप्रिय तरीका JSON का उपयोग करना है। JSON के लिए एक Arduino लाइब्रेरी है जो JSON दस्तावेज़ों को पढ़ने और लिखने को आसान बनाती है।

### कार्य

Arduino JSON लाइब्रेरी इंस्टॉल करें।

1. VS Code में नाइटलाइट प्रोजेक्ट खोलें।

1. `platformio.ini` फाइल में `lib_deps` सूची में निम्नलिखित को एक अतिरिक्त लाइन के रूप में जोड़ें:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    यह [ArduinoJson](https://arduinojson.org) को इंपोर्ट करता है, जो एक Arduino JSON लाइब्रेरी है।

## टेलीमेट्री प्रकाशित करें

अगला कदम टेलीमेट्री के साथ एक JSON दस्तावेज़ बनाना और इसे MQTT ब्रोकर्स पर भेजना है।

### कार्य - टेलीमेट्री प्रकाशित करें

MQTT ब्रोकर्स पर टेलीमेट्री प्रकाशित करें।

1. MQTT ब्रोकर्स के लिए टेलीमेट्री टॉपिक नाम को परिभाषित करने के लिए `config.h` फाइल के नीचे निम्नलिखित कोड जोड़ें:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` वह टॉपिक है जिस पर डिवाइस प्रकाश स्तरों को प्रकाशित करेगा।

1. `main.cpp` फाइल खोलें।

1. फाइल के शीर्ष पर निम्नलिखित `#include` निर्देश जोड़ें:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` फंक्शन के अंदर, `delay` से ठीक पहले निम्नलिखित कोड जोड़ें:

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

    यह कोड प्रकाश स्तर को पढ़ता है और ArduinoJson का उपयोग करके इस स्तर के साथ एक JSON दस्तावेज़ बनाता है। फिर इसे एक स्ट्रिंग में सीरियलाइज़ किया जाता है और MQTT क्लाइंट द्वारा टेलीमेट्री MQTT टॉपिक पर प्रकाशित किया जाता है।

1. कोड को अपने Wio Terminal पर अपलोड करें और सीरियल मॉनिटर का उपयोग करके देखें कि प्रकाश स्तर MQTT ब्रोकर्स पर भेजे जा रहे हैं:

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 आप इस कोड को [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपने सफलतापूर्वक अपने डिवाइस से टेलीमेट्री भेज दी है।

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।