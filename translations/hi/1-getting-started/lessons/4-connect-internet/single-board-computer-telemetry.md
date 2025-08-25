<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-25T17:13:36+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "hi"
}
-->
# इंटरनेट के माध्यम से अपनी नाइटलाइट को नियंत्रित करें - वर्चुअल IoT हार्डवेयर और रास्पबेरी पाई

इस पाठ के इस भाग में, आप अपने रास्पबेरी पाई या वर्चुअल IoT डिवाइस से प्रकाश स्तर के साथ टेलीमेट्री को एक MQTT ब्रोकर्स को भेजेंगे।

## टेलीमेट्री प्रकाशित करें

अगला कदम टेलीमेट्री के साथ एक JSON दस्तावेज़ बनाना और इसे MQTT ब्रोकर्स को भेजना है।

### कार्य

MQTT ब्रोकर्स को टेलीमेट्री प्रकाशित करें।

1. VS Code में नाइटलाइट प्रोजेक्ट खोलें।

1. यदि आप वर्चुअल IoT डिवाइस का उपयोग कर रहे हैं, तो सुनिश्चित करें कि टर्मिनल वर्चुअल वातावरण चला रहा है। यदि आप रास्पबेरी पाई का उपयोग कर रहे हैं, तो आप वर्चुअल वातावरण का उपयोग नहीं करेंगे।

1. `app.py` फ़ाइल के शीर्ष पर निम्नलिखित इम्पोर्ट जोड़ें:

    ```python
    import json
    ```

    `json` लाइब्रेरी का उपयोग टेलीमेट्री को JSON दस्तावेज़ के रूप में एन्कोड करने के लिए किया जाता है।

1. `client_name` घोषणा के बाद निम्नलिखित जोड़ें:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` वह MQTT टॉपिक है जिस पर डिवाइस प्रकाश स्तर को प्रकाशित करेगा।

1. फ़ाइल के अंत में `while True:` लूप की सामग्री को निम्नलिखित से बदलें:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    यह कोड प्रकाश स्तर को एक JSON दस्तावेज़ में पैक करता है और इसे MQTT ब्रोकर्स को प्रकाशित करता है। इसके बाद यह संदेश भेजने की आवृत्ति को कम करने के लिए रुकता है।

1. उसी तरह कोड चलाएं जैसे आपने असाइनमेंट के पिछले भाग से कोड चलाया था। यदि आप वर्चुअल IoT डिवाइस का उपयोग कर रहे हैं, तो सुनिश्चित करें कि CounterFit ऐप चल रहा है और लाइट सेंसर और LED को सही पिन पर बनाया गया है।

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 आप इस कोड को [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) फ़ोल्डर या [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) फ़ोल्डर में पा सकते हैं।

😀 आपने सफलतापूर्वक अपने डिवाइस से टेलीमेट्री भेज दी है।

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।