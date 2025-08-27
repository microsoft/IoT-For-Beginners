<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T11:07:41+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "ne"
}
-->
# तापक्रम प्रकाशित गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईंले Wio Terminal द्वारा पत्ता लगाइएको तापक्रम मानहरू MQTT मार्फत प्रकाशित गर्नुहुनेछ ताकि पछि GDD गणना गर्न प्रयोग गर्न सकियोस्।

## तापक्रम प्रकाशित गर्नुहोस्

एकपटक तापक्रम पढिसकेपछि, यसलाई MQTT मार्फत 'सर्भर' कोडमा प्रकाशित गर्न सकिन्छ जसले मानहरू पढ्नेछ र GDD गणनाको लागि प्रयोग गर्न तयार राख्नेछ। माइक्रोकन्ट्रोलरहरूले इन्टरनेटबाट समय पढ्दैनन् र वास्तविक-समय घडीको साथ समय ट्र्याक गर्दैनन्। उपकरणलाई यो गर्न प्रोग्राम गर्न आवश्यक छ, यदि यससँग आवश्यक हार्डवेयर छ भने।

यस पाठलाई सरल बनाउनको लागि, सेन्सर डेटा संग समय पठाइने छैन। यसको सट्टा, सर्भर कोडले सन्देश प्राप्त गर्दा पछि समय थप्न सक्छ।

### कार्य

उपकरणलाई तापक्रम डेटा प्रकाशित गर्न प्रोग्राम गर्नुहोस्।

1. `temperature-sensor` Wio Terminal प्रोजेक्ट खोल्नुहोस्।

1. पाठ 4 मा तपाईंले गरेको चरणहरू दोहोर्याउनुहोस् ताकि MQTT मा जडान गर्न र टेलिमेट्री पठाउन सकियोस्। तपाईंले उही सार्वजनिक Mosquitto broker प्रयोग गर्नेछ।

    यसका चरणहरू:

    - `.ini` फाइलमा Seeed WiFi र MQTT लाइब्रेरीहरू थप्नुहोस्।
    - WiFi मा जडान गर्नको लागि कन्फिग फाइल र कोड थप्नुहोस्।
    - MQTT broker मा जडान गर्नको लागि कोड थप्नुहोस्।
    - टेलिमेट्री प्रकाशित गर्नको लागि कोड थप्नुहोस्।

    > ⚠️ यदि आवश्यक छ भने [MQTT मा जडान गर्ने निर्देशनहरू](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) र [टेलिमेट्री पठाउने निर्देशनहरू](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) पाठ 4 बाट हेर्नुहोस्।

1. सुनिश्चित गर्नुहोस् कि `config.h` हेडर फाइलमा `CLIENT_NAME` यस प्रोजेक्टलाई प्रतिबिम्बित गर्दछ:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. टेलिमेट्रीको लागि, प्रकाश मान पठाउने सट्टा, DHT सेन्सरबाट पढिएको तापक्रम मानलाई JSON डकुमेन्टको `temperature` नामक प्रोपर्टीमा पठाउनुहोस्। यसका लागि `main.cpp` मा `loop` फंक्शन परिवर्तन गर्नुहोस्:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. तापक्रम मानलाई बारम्बार पढ्न आवश्यक छैन - यो छोटो समयमा धेरै परिवर्तन हुँदैन। त्यसैले `loop` फंक्शनमा `delay` लाई 10 मिनेटमा सेट गर्नुहोस्:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` फंक्शनले समयलाई मिलिसेकेन्डमा लिन्छ। यसलाई पढ्न सजिलो बनाउन, मानलाई गणनाको परिणामको रूपमा पास गरिएको छ। 1,000ms एक सेकेन्डमा, 60s एक मिनेटमा, त्यसैले 10 x (60s एक मिनेटमा) x (1000ms एक सेकेन्डमा) ले 10 मिनेटको विलम्ब दिन्छ।

1. यसलाई Wio Terminal मा अपलोड गर्नुहोस्, र तापक्रम MQTT broker मा पठाइएको हेर्नको लागि सिरियल मोनिटर प्रयोग गर्नुहोस्।

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 तपाईंले यो कोड [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंले सफलतापूर्वक आफ्नो उपकरणबाट टेलिमेट्रीको रूपमा तापक्रम प्रकाशित गर्नुभएको छ।

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।