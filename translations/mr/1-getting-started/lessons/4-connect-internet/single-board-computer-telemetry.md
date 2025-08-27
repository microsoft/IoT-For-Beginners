<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T12:19:49+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "mr"
}
-->
# इंटरनेटद्वारे तुमचा नाईटलाइट नियंत्रित करा - व्हर्च्युअल IoT हार्डवेअर आणि रास्पबेरी पाय

या धड्याच्या या भागात, तुम्ही तुमच्या रास्पबेरी पाय किंवा व्हर्च्युअल IoT डिव्हाइसवरून प्रकाश पातळीसह टेलीमेट्री MQTT ब्रोकरकडे पाठवाल.

## टेलीमेट्री प्रकाशित करा

पुढील पायरी म्हणजे टेलीमेट्रीसह JSON दस्तऐवज तयार करणे आणि ते MQTT ब्रोकरकडे पाठवणे.

### कार्य

MQTT ब्रोकरकडे टेलीमेट्री प्रकाशित करा.

1. VS Code मध्ये नाईटलाइट प्रोजेक्ट उघडा.

1. जर तुम्ही व्हर्च्युअल IoT डिव्हाइस वापरत असाल, तर टर्मिनल व्हर्च्युअल वातावरण चालू असल्याची खात्री करा. जर तुम्ही रास्पबेरी पाय वापरत असाल तर तुम्ही व्हर्च्युअल वातावरण वापरणार नाही.

1. `app.py` फाइलच्या शीर्षस्थानी खालील आयात जोडा:

    ```python
    import json
    ```

    `json` लायब्ररी टेलीमेट्रीला JSON दस्तऐवज म्हणून एन्कोड करण्यासाठी वापरली जाते.

1. `client_name` घोषणेनंतर खालील जोडा:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` हा MQTT टॉपिक आहे ज्यावर डिव्हाइस प्रकाश पातळी प्रकाशित करेल.

1. फाइलच्या शेवटी असलेल्या `while True:` लूपची सामग्री खालीलप्रमाणे बदला:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    हा कोड प्रकाश पातळीला JSON दस्तऐवजामध्ये पॅकेज करतो आणि ते MQTT ब्रोकरकडे प्रकाशित करतो. त्यानंतर संदेश पाठवण्याची वारंवारता कमी करण्यासाठी कोड थांबतो.

1. मागील भागातील कोड चालवला तसाच कोड चालवा. जर तुम्ही व्हर्च्युअल IoT डिव्हाइस वापरत असाल, तर CounterFit अॅप चालू असल्याची खात्री करा आणि लाइट सेन्सर आणि LED योग्य पिनवर तयार केले आहेत.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 तुम्हाला हा कोड [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) फोल्डरमध्ये किंवा [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) फोल्डरमध्ये सापडेल.

😀 तुम्ही तुमच्या डिव्हाइसवरून यशस्वीरित्या टेलीमेट्री पाठवली आहे.

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरे त्रुटी किंवा अचूकतेच्या अभावाने युक्त असू शकतात. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.