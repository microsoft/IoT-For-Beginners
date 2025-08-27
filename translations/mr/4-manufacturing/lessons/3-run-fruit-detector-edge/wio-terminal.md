<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T10:43:29+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "mr"
}
-->
# IoT Edge आधारित इमेज क्लासिफायर वापरून प्रतिमा वर्गीकृत करा - Wio Terminal

या धड्याच्या भागात, तुम्ही IoT Edge डिव्हाइसवर चालणाऱ्या इमेज क्लासिफायरचा वापर कराल.

## IoT Edge क्लासिफायर वापरा

IoT डिव्हाइसला IoT Edge इमेज क्लासिफायरकडे पुनर्निर्देशित करता येते. इमेज क्लासिफायरसाठी URL `http://<IP address or name>/image` आहे, ज्यामध्ये `<IP address or name>` च्या जागी IoT Edge चालवणाऱ्या संगणकाचा IP पत्ता किंवा होस्ट नाव टाकावे.

### कार्य - IoT Edge क्लासिफायर वापरा

1. `fruit-quality-detector` अॅप प्रोजेक्ट उघडा, जर ते आधीच उघडले नसेल.

1. इमेज क्लासिफायर HTTP वापरून REST API म्हणून चालत आहे, HTTPS नाही, त्यामुळे कॉल फक्त HTTP कॉलसाठी कार्य करणाऱ्या WiFi क्लायंटचा वापर करतो. याचा अर्थ प्रमाणपत्र आवश्यक नाही. `config.h` फाइलमधून `CERTIFICATE` हटवा.

1. `config.h` फाइलमधील प्रेडिक्शन URL नवीन URL मध्ये अपडेट करणे आवश्यक आहे. तुम्ही `PREDICTION_KEY` देखील हटवू शकता कारण ते आवश्यक नाही.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>` च्या जागी तुमच्या क्लासिफायरसाठी URL टाका.

1. `main.cpp` मध्ये, WiFi Client Secure साठीचा include directive बदलून स्टँडर्ड HTTP आवृत्ती आयात करा:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient` ची घोषणा HTTP आवृत्तीमध्ये बदला:

    ```cpp
    WiFiClient client;
    ```

1. WiFi क्लायंटवर प्रमाणपत्र सेट करणारी ओळ निवडा. `connectWiFi` फंक्शनमधून `client.setCACert(CERTIFICATE);` ओळ हटवा.

1. `classifyImage` फंक्शनमध्ये, हेडरमध्ये प्रेडिक्शन की सेट करणारी `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` ओळ हटवा.

1. तुमचा कोड अपलोड करा आणि चालवा. कॅमेरा फळांकडे निर्देशित करा आणि C बटण दाबा. तुम्हाला सीरियल मॉनिटरमध्ये आउटपुट दिसेल:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 तुम्ही हा कोड [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुमचा फळ गुणवत्ता क्लासिफायर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.