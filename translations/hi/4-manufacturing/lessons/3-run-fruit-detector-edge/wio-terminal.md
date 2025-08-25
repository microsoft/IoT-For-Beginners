<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-25T16:38:03+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "hi"
}
-->
# IoT Edge आधारित इमेज क्लासिफायर का उपयोग करके एक इमेज को वर्गीकृत करें - Wio Terminal

इस पाठ के इस भाग में, आप IoT Edge डिवाइस पर चल रहे इमेज क्लासिफायर का उपयोग करेंगे।

## IoT Edge क्लासिफायर का उपयोग करें

IoT डिवाइस को IoT Edge इमेज क्लासिफायर का उपयोग करने के लिए पुनः निर्देशित किया जा सकता है। इमेज क्लासिफायर के लिए URL `http://<IP address or name>/image` है, जहाँ `<IP address or name>` को IoT Edge चलाने वाले कंप्यूटर के IP एड्रेस या होस्ट नाम से बदलें।

### कार्य - IoT Edge क्लासिफायर का उपयोग करें

1. यदि `fruit-quality-detector` ऐप प्रोजेक्ट पहले से खुला नहीं है, तो इसे खोलें।

1. इमेज क्लासिफायर HTTP का उपयोग करके एक REST API के रूप में चल रहा है, HTTPS का नहीं। इसलिए कॉल को केवल HTTP कॉल के साथ काम करने वाले WiFi क्लाइंट का उपयोग करना होगा। इसका मतलब है कि सर्टिफिकेट की आवश्यकता नहीं है। `config.h` फाइल से `CERTIFICATE` को हटा दें।

1. `config.h` फाइल में प्रेडिक्शन URL को नए URL से अपडेट करना होगा। आप `PREDICTION_KEY` को भी हटा सकते हैं क्योंकि इसकी आवश्यकता नहीं है।

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>` को अपने क्लासिफायर के URL से बदलें।

1. `main.cpp` में, WiFi Client Secure के लिए शामिल निर्देश को मानक HTTP संस्करण आयात करने के लिए बदलें:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient` की घोषणा को HTTP संस्करण में बदलें:

    ```cpp
    WiFiClient client;
    ```

1. WiFi क्लाइंट पर सर्टिफिकेट सेट करने वाली लाइन का चयन करें। `connectWiFi` फंक्शन से `client.setCACert(CERTIFICATE);` लाइन को हटा दें।

1. `classifyImage` फंक्शन में, हेडर में प्रेडिक्शन की सेट करने वाली लाइन `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` को हटा दें।

1. अपना कोड अपलोड करें और चलाएं। कैमरे को किसी फल की ओर इंगित करें और C बटन दबाएं। आप सीरियल मॉनिटर में आउटपुट देखेंगे:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 आप इस कोड को [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपका फल गुणवत्ता क्लासिफायर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।