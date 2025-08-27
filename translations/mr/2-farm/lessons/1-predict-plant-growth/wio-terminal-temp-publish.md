<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T11:07:26+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "mr"
}
-->
# तापमान प्रकाशित करा - Wio Terminal

या धड्याच्या भागात, तुम्ही Wio Terminal द्वारे शोधलेले तापमान MQTT वर प्रकाशित कराल जेणेकरून ते नंतर GDD गणनेकरता वापरता येईल.

## तापमान प्रकाशित करा

तापमान वाचल्यानंतर, ते MQTT वर प्रकाशित केले जाऊ शकते, जिथे 'server' कोड ते वाचेल आणि GDD गणनेसाठी तयार ठेवेल. मायक्रोकंट्रोलर्स इंटरनेटवरून वेळ वाचत नाहीत आणि बाहेरून रिअल-टाइम क्लॉकसह वेळ ट्रॅक करत नाहीत, त्यामुळे डिव्हाइसला हे करण्यासाठी प्रोग्राम करणे आवश्यक आहे, जर त्याच्याकडे आवश्यक हार्डवेअर असेल.

या धड्याकरता गोष्टी सोप्या करण्यासाठी, सेन्सर डेटा पाठवताना वेळ पाठवला जाणार नाही, त्याऐवजी तो नंतर सर्व्हर कोडद्वारे जोडला जाईल जेव्हा ते संदेश प्राप्त करतील.

### कार्य

डिव्हाइसला तापमान डेटा प्रकाशित करण्यासाठी प्रोग्राम करा.

1. `temperature-sensor` Wio Terminal प्रोजेक्ट उघडा.

1. MQTT शी कनेक्ट होऊन टेलिमेट्री पाठवण्यासाठी तुम्ही धडा 4 मध्ये केलेले पायऱ्या पुन्हा करा. तुम्ही त्याच सार्वजनिक Mosquitto ब्रोकर्सचा वापर करणार आहात.

    यासाठी पायऱ्या:

    - `.ini` फाइलमध्ये Seeed WiFi आणि MQTT लायब्ररी जोडा.
    - WiFi शी कनेक्ट होण्यासाठी कॉन्फिग फाइल आणि कोड जोडा.
    - MQTT ब्रोकर्सशी कनेक्ट होण्यासाठी कोड जोडा.
    - टेलिमेट्री प्रकाशित करण्यासाठी कोड जोडा.

    > ⚠️ MQTT शी कनेक्ट होण्यासाठी [सूचना](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) आणि टेलिमेट्री पाठवण्यासाठी [सूचना](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) धडा 4 मधून आवश्यक असल्यास पहा.

1. `config.h` हेडर फाइलमधील `CLIENT_NAME` या प्रोजेक्टशी जुळत असल्याची खात्री करा:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. टेलिमेट्रीसाठी, लाइट व्हॅल्यू पाठवण्याऐवजी, DHT सेन्सरद्वारे वाचलेले तापमान JSON डॉक्युमेंटमधील `temperature` प्रॉपर्टीमध्ये पाठवा, यासाठी `main.cpp` मधील `loop` फंक्शन बदला:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. तापमान वारंवार वाचण्याची गरज नाही - ते अल्प कालावधीत फारसे बदलत नाही, त्यामुळे `loop` फंक्शनमधील `delay` 10 मिनिटे सेट करा:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` फंक्शन वेळ मिलिसेकंडमध्ये घेतो, त्यामुळे वाचणे सोपे करण्यासाठी मूल्य गणनेचा परिणाम म्हणून पास केले जाते. 1,000ms एका सेकंदात, 60s एका मिनिटात, त्यामुळे 10 x (60s एका मिनिटात) x (1000ms एका सेकंदात) 10 मिनिटांचा विलंब देतो.

1. हे तुमच्या Wio Terminal वर अपलोड करा आणि MQTT ब्रोकर्सकडे पाठवलेले तापमान पाहण्यासाठी सीरियल मॉनिटर वापरा.

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

> 💁 तुम्ही हे कोड [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुम्ही यशस्वीरित्या तुमच्या डिव्हाइसवरून टेलिमेट्री म्हणून तापमान प्रकाशित केले आहे.

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.