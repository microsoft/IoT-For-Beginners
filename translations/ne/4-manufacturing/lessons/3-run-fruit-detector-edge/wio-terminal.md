<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T10:43:40+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "ne"
}
-->
# IoT Edge आधारित छवि वर्गीकरणकर्ता प्रयोग गरेर छवि वर्गीकरण गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं IoT Edge उपकरणमा चलिरहेको छवि वर्गीकरणकर्ता प्रयोग गर्नुहुनेछ।

## IoT Edge वर्गीकरणकर्ता प्रयोग गर्नुहोस्

IoT उपकरणलाई IoT Edge छवि वर्गीकरणकर्ता प्रयोग गर्न पुनः निर्देशित गर्न सकिन्छ। छवि वर्गीकरणकर्ताको URL `http://<IP address or name>/image` हो, जहाँ `<IP address or name>` लाई IoT Edge चलिरहेको कम्प्युटरको IP ठेगाना वा होस्ट नामले प्रतिस्थापन गर्नुपर्छ।

### कार्य - IoT Edge वर्गीकरणकर्ता प्रयोग गर्नुहोस्

1. यदि `fruit-quality-detector` एप परियोजना खुला छैन भने यसलाई खोल्नुहोस्।

1. छवि वर्गीकरणकर्ता HTTP प्रयोग गरेर REST API को रूपमा चलिरहेको छ, HTTPS होइन, त्यसैले कलले HTTP कलहरूसँग मात्र काम गर्ने WiFi क्लाइन्ट प्रयोग गर्नुपर्छ। यसको मतलब प्रमाणपत्र आवश्यक छैन। `config.h` फाइलबाट `CERTIFICATE` मेटाउनुहोस्।

1. `config.h` फाइलमा भविष्यवाणी URL नयाँ URL मा अद्यावधिक गर्नुपर्छ। तपाईं `PREDICTION_KEY` पनि मेटाउन सक्नुहुन्छ किनभने यो आवश्यक छैन।

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>` लाई तपाईंको वर्गीकरणकर्ताको URL ले प्रतिस्थापन गर्नुहोस्।

1. `main.cpp` मा, WiFi Client Secure को समावेश निर्देशनलाई मानक HTTP संस्करण आयात गर्न परिवर्तन गर्नुहोस्:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient` को घोषणा HTTP संस्करणमा परिवर्तन गर्नुहोस्:

    ```cpp
    WiFiClient client;
    ```

1. WiFi क्लाइन्टमा प्रमाणपत्र सेट गर्ने लाइन चयन गर्नुहोस्। `connectWiFi` कार्यबाट `client.setCACert(CERTIFICATE);` लाइन मेटाउनुहोस्।

1. `classifyImage` कार्यमा, हेडरमा भविष्यवाणी कुञ्जी सेट गर्ने `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` लाइन मेटाउनुहोस्।

1. तपाईंको कोड अपलोड गर्नुहोस् र चलाउनुहोस्। क्यामेरालाई केही फलफूलतर्फ सोझ्याउनुहोस् र C बटन थिच्नुहोस्। तपाईंले सिरियल मोनिटरमा नतिजा देख्नुहुनेछ:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 तपाईं यो कोड [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंको फलफूल गुणस्तर वर्गीकरणकर्ता कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको हो। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।