<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-25T16:47:09+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "hi"
}
-->
# तापमान प्रकाशित करें - Wio Terminal

इस पाठ के इस भाग में, आप Wio Terminal द्वारा पता किए गए तापमान मानों को MQTT के माध्यम से प्रकाशित करेंगे ताकि उनका उपयोग बाद में GDD की गणना के लिए किया जा सके।

## तापमान प्रकाशित करें

एक बार तापमान पढ़ लिया जाए, इसे MQTT के माध्यम से 'सर्वर' कोड पर प्रकाशित किया जा सकता है, जो इन मानों को पढ़ेगा और उन्हें GDD गणना के लिए तैयार रखेगा। माइक्रोकंट्रोलर इंटरनेट से समय नहीं पढ़ते और बॉक्स से बाहर रियल-टाइम क्लॉक के साथ समय को ट्रैक नहीं करते हैं। डिवाइस को ऐसा करने के लिए प्रोग्राम करना पड़ता है, यह मानते हुए कि इसमें आवश्यक हार्डवेयर है।

इस पाठ को सरल बनाने के लिए, समय को सेंसर डेटा के साथ नहीं भेजा जाएगा। इसके बजाय, जब सर्वर कोड संदेश प्राप्त करेगा, तो वह समय जोड़ सकता है।

### कार्य

डिवाइस को तापमान डेटा प्रकाशित करने के लिए प्रोग्राम करें।

1. `temperature-sensor` Wio Terminal प्रोजेक्ट खोलें।

1. MQTT से कनेक्ट करने और टेलीमेट्री भेजने के लिए आपने पाठ 4 में जो कदम उठाए थे, उन्हें दोहराएं। आप वही सार्वजनिक Mosquitto ब्रॉकर का उपयोग करेंगे।

    इसके लिए कदम हैं:

    - `.ini` फ़ाइल में Seeed WiFi और MQTT लाइब्रेरी जोड़ें।
    - WiFi से कनेक्ट करने के लिए कॉन्फ़िगरेशन फ़ाइल और कोड जोड़ें।
    - MQTT ब्रॉकर से कनेक्ट करने के लिए कोड जोड़ें।
    - टेलीमेट्री प्रकाशित करने के लिए कोड जोड़ें।

    > ⚠️ यदि आवश्यक हो, तो [MQTT से कनेक्ट करने के निर्देश](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) और [टेलीमेट्री भेजने के निर्देश](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) पाठ 4 से देखें।

1. सुनिश्चित करें कि `config.h` हेडर फ़ाइल में `CLIENT_NAME` इस प्रोजेक्ट को दर्शाता है:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. टेलीमेट्री के लिए, लाइट मान भेजने के बजाय, DHT सेंसर से पढ़े गए तापमान मान को JSON दस्तावेज़ में `temperature` नामक एक प्रॉपर्टी में भेजें। इसके लिए `main.cpp` में `loop` फ़ंक्शन बदलें:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. तापमान मान को बार-बार पढ़ने की आवश्यकता नहीं है - यह थोड़े समय में ज्यादा नहीं बदलेगा। इसलिए `loop` फ़ंक्शन में `delay` को 10 मिनट पर सेट करें:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` फ़ंक्शन समय को मिलीसेकंड में लेता है, इसलिए इसे पढ़ने में आसान बनाने के लिए मान को एक गणना के परिणाम के रूप में पास किया गया है। 1,000ms एक सेकंड में, 60s एक मिनट में, तो 10 x (60s एक मिनट में) x (1000ms एक सेकंड में) 10 मिनट की देरी देता है।

1. इसे अपने Wio Terminal पर अपलोड करें और सीरियल मॉनिटर का उपयोग करके देखें कि तापमान MQTT ब्रॉकर को भेजा जा रहा है।

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

> 💁 आप इस कोड को [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) फ़ोल्डर में पा सकते हैं।

😀 आपने सफलतापूर्वक अपने डिवाइस से टेलीमेट्री के रूप में तापमान प्रकाशित कर दिया है।

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता के लिए प्रयासरत हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।