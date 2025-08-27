<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T12:30:30+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "ne"
}
-->
# आफ्नो नाइटलाइटलाई इन्टरनेटमार्फत नियन्त्रण गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं आफ्नो Wio Terminal बाट प्रकाश स्तरको टेलिमेट्री MQTT ब्रोकरमा पठाउनुहुनेछ।

## JSON Arduino लाइब्रेरीहरू स्थापना गर्नुहोस्

MQTT मार्फत सन्देश पठाउने लोकप्रिय तरिका JSON प्रयोग गर्नु हो। JSON पढ्न र लेख्न सजिलो बनाउने Arduino को लागि JSON लाइब्रेरी उपलब्ध छ।

### कार्य

Arduino JSON लाइब्रेरी स्थापना गर्नुहोस्।

1. VS Code मा नाइटलाइट प्रोजेक्ट खोल्नुहोस्।

1. `platformio.ini` फाइलको `lib_deps` सूचीमा निम्न लाइन थप्नुहोस्:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    यसले [ArduinoJson](https://arduinojson.org), Arduino JSON लाइब्रेरी आयात गर्दछ।

## टेलिमेट्री प्रकाशित गर्नुहोस्

अर्को चरण भनेको टेलिमेट्रीको साथ JSON डकुमेन्ट सिर्जना गर्नु र यसलाई MQTT ब्रोकरमा पठाउनु हो।

### कार्य - टेलिमेट्री प्रकाशित गर्नुहोस्

MQTT ब्रोकरमा टेलिमेट्री प्रकाशित गर्नुहोस्।

1. `config.h` फाइलको तल निम्न कोड थप्नुहोस् ताकि MQTT ब्रोकरको लागि टेलिमेट्री टपिक नाम परिभाषित गर्न सकियोस्:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` भनेको उपकरणले प्रकाश स्तर प्रकाशित गर्ने टपिक हो।

1. `main.cpp` फाइल खोल्नुहोस्।

1. फाइलको माथि निम्न `#include` निर्देशन थप्नुहोस्:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` फङ्सनभित्र, `delay` भन्दा ठीक अघि निम्न कोड थप्नुहोस्:

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

    यो कोडले प्रकाश स्तर पढ्छ, र ArduinoJson प्रयोग गरेर यस स्तरको साथ JSON डकुमेन्ट सिर्जना गर्छ। त्यसपछि यसलाई स्ट्रिङमा सिरियलाइज गरिन्छ र MQTT क्लाइन्टद्वारा टेलिमेट्री MQTT टपिकमा प्रकाशित गरिन्छ।

1. कोडलाई आफ्नो Wio Terminal मा अपलोड गर्नुहोस्, र Serial Monitor प्रयोग गरेर प्रकाश स्तरहरू MQTT ब्रोकरमा पठाइएको हेर्नुहोस्।

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 तपाईं यो कोड [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंले सफलतापूर्वक आफ्नो उपकरणबाट टेलिमेट्री पठाउनुभएको छ।

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरी अनुवाद गरिएको हो। हामी यथासम्भव सटीकता सुनिश्चित गर्न प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषामा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्त्वपूर्ण जानकारीका लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।