<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T12:35:16+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "mr"
}
-->
# इंटरनेटवरून तुमचा नाईटलाइट नियंत्रित करा - Wio Terminal

या धड्याच्या या भागात, तुम्ही MQTT ब्रोकर्सकडून पाठवलेल्या आदेशांना Wio Terminal वर सबस्क्राइब कराल.

## आदेशांना सबस्क्राइब करा

पुढील पायरी म्हणजे MQTT ब्रोकर्सकडून पाठवलेल्या आदेशांना सबस्क्राइब करणे आणि त्यांना प्रतिसाद देणे.

### कार्य

आदेशांना सबस्क्राइब करा.

1. VS Code मध्ये नाईटलाइट प्रोजेक्ट उघडा.

1. `config.h` फाइलच्या शेवटी खालील कोड जोडा, ज्यामुळे आदेशांसाठी टॉपिकचे नाव निश्चित केले जाईल:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` हे टॉपिक आहे ज्यावर डिव्हाइस LED आदेश प्राप्त करण्यासाठी सबस्क्राइब करेल.

1. `reconnectMQTTClient` फंक्शनच्या शेवटी खालील ओळ जोडा, ज्यामुळे MQTT क्लायंट पुन्हा कनेक्ट झाल्यावर आदेश टॉपिकला सबस्क्राइब केले जाईल:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. `reconnectMQTTClient` फंक्शनच्या खालील कोड जोडा:

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

    हे फंक्शन MQTT क्लायंटला सर्व्हरकडून संदेश प्राप्त झाल्यावर कॉल करण्यासाठी वापरले जाईल.

    संदेश unsigned 8-bit integers च्या स्वरूपात प्राप्त होतो, त्यामुळे त्याला टेक्स्ट म्हणून वागवण्यासाठी character array मध्ये रूपांतरित करावे लागते.

    संदेशामध्ये JSON डॉक्युमेंट असते, आणि ते ArduinoJson लायब्ररी वापरून डिकोड केले जाते. JSON डॉक्युमेंटमधील `led_on` प्रॉपर्टी वाचली जाते, आणि त्याच्या मूल्यावर आधारित LED चालू किंवा बंद केले जाते.

1. `createMQTTClient` फंक्शनमध्ये खालील कोड जोडा:

    ```cpp
    client.setCallback(clientCallback);
    ```

    हा कोड `clientCallback` ला MQTT ब्रोकर्सकडून संदेश प्राप्त झाल्यावर कॉल करण्यासाठी सेट करतो.

    > 💁 `clientCallback` हँडलर सर्व सबस्क्राइब केलेल्या टॉपिक्ससाठी कॉल केला जातो. जर तुम्ही नंतर अनेक टॉपिक्ससाठी कोड लिहिला, तर तुम्ही `topic` पॅरामीटरमधून संदेश पाठवले गेलेले टॉपिक मिळवू शकता.

1. कोड Wio Terminal वर अपलोड करा आणि Serial Monitor वापरून प्रकाश पातळी MQTT ब्रोकर्सकडे पाठवली जात असल्याचे पहा.

1. तुमच्या भौतिक किंवा आभासी डिव्हाइसद्वारे शोधल्या जाणाऱ्या प्रकाश पातळी समायोजित करा. तुम्हाला टर्मिनलमध्ये संदेश प्राप्त होताना आणि आदेश पाठवले जाताना दिसतील. प्रकाश पातळीवर आधारित LED चालू आणि बंद होताना देखील तुम्हाला दिसेल.

> 💁 तुम्ही हा कोड [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुम्ही यशस्वीरित्या तुमच्या डिव्हाइसला MQTT ब्रोकर्सकडून आदेशांना प्रतिसाद देण्यासाठी कोड केले आहे.

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात ठेवा की स्वयंचलित भाषांतरे त्रुटी किंवा अचूकतेच्या अभावाने युक्त असू शकतात. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी, व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.