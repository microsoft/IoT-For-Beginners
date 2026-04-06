# जवळीक ओळखणे - Wio Terminal

या धड्याच्या भागात, तुम्ही Wio Terminal मध्ये एक proximity sensor जोडाल आणि त्यातून अंतर वाचाल.

## हार्डवेअर

Wio Terminal साठी proximity sensor आवश्यक आहे.

तुम्ही वापरणार असलेला सेन्सर [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html) आहे. हा सेन्सर लेसर रेंजिंग मॉड्यूल वापरून अंतर शोधतो. या सेन्सरची श्रेणी 10mm ते 2000mm (1cm - 2m) आहे आणि तो या श्रेणीतले मूल्य अचूकपणे रिपोर्ट करतो. 1000mm पेक्षा जास्त अंतर 8109mm म्हणून रिपोर्ट केले जाते.

लेसर रेंजफाइंडर सेन्सरच्या मागील बाजूस आहे, Grove सॉकेटच्या विरुद्ध बाजूस.

हा एक I²C सेन्सर आहे.

### टाइम ऑफ फ्लाइट सेन्सर कनेक्ट करा

Grove टाइम ऑफ फ्लाइट सेन्सर Wio Terminal शी जोडता येतो.

#### कार्य - टाइम ऑफ फ्लाइट सेन्सर कनेक्ट करा

टाइम ऑफ फ्लाइट सेन्सर कनेक्ट करा.

![Grove टाइम ऑफ फ्लाइट सेन्सर](../../../../../translated_images/mr/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Grove केबलचा एक टोक टाइम ऑफ फ्लाइट सेन्सरच्या सॉकेटमध्ये घाला. ती केवळ एका बाजूनेच जाईल.

1. Wio Terminal तुमच्या संगणकापासून किंवा इतर पॉवर सप्लायपासून डिस्कनेक्ट केलेला असताना, Grove केबलचे दुसरे टोक Wio Terminal च्या स्क्रीनकडे पाहताना डाव्या बाजूच्या Grove सॉकेटमध्ये कनेक्ट करा. हे सॉकेट पॉवर बटणाजवळ आहे. हे एक संयुक्त डिजिटल आणि I²C सॉकेट आहे.

![डाव्या बाजूच्या सॉकेटमध्ये कनेक्ट केलेला Grove टाइम ऑफ फ्लाइट सेन्सर](../../../../../translated_images/mr/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. आता तुम्ही Wio Terminal तुमच्या संगणकाला कनेक्ट करू शकता.

## टाइम ऑफ फ्लाइट सेन्सर प्रोग्राम करा

आता Wio Terminal जोडलेल्या टाइम ऑफ फ्लाइट सेन्सरचा वापर करण्यासाठी प्रोग्राम केला जाऊ शकतो.

### कार्य - टाइम ऑफ फ्लाइट सेन्सर प्रोग्राम करा

1. PlatformIO वापरून एक नवीन Wio Terminal प्रोजेक्ट तयार करा. या प्रोजेक्टचे नाव `distance-sensor` ठेवा. `setup` फंक्शनमध्ये सीरियल पोर्ट कॉन्फिगर करण्यासाठी कोड जोडा.

1. प्रोजेक्टच्या `platformio.ini` फाइलमध्ये Seeed Grove टाइम ऑफ फ्लाइट डिस्टन्स सेन्सर लायब्ररीसाठी एक लायब्ररी dependency जोडा:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. `main.cpp` मध्ये, विद्यमान include directives खाली खालील कोड जोडा, ज्यामुळे टाइम ऑफ फ्लाइट सेन्सरशी संवाद साधण्यासाठी `Seeed_vl53l0x` क्लासची instance घोषित केली जाईल:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. `setup` फंक्शनच्या शेवटी खालील कोड जोडा, ज्यामुळे सेन्सर initialize होईल:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. `loop` फंक्शनमध्ये, सेन्सरमधून एक मूल्य वाचा:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    हा कोड डेटा वाचण्यासाठी एक डेटा स्ट्रक्चर initialize करतो आणि नंतर `PerformSingleRangingMeasurement` मेथडमध्ये पास करतो, जिथे ते अंतर मोजण्याच्या डेटाने भरले जाते.

1. याखाली, अंतर मोजण्याचे मूल्य लिहा आणि नंतर 1 सेकंदासाठी विलंब करा:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. हा कोड बिल्ड, अपलोड आणि चालवा. तुम्ही सीरियल मॉनिटरवर अंतर मोजमाप पाहू शकाल. सेन्सरजवळ वस्तू ठेवा आणि तुम्हाला अंतर मोजमाप दिसेल:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    रेंजफाइंडर सेन्सरच्या मागील बाजूस आहे, त्यामुळे अंतर मोजताना योग्य बाजू वापरा.

    ![टाइम ऑफ फ्लाइट सेन्सरच्या मागील बाजूस रेंजफाइंडर एका केळीकडे निर्देश करत आहे](../../../../../translated_images/mr/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 तुम्हाला हा कोड [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) फोल्डरमध्ये सापडेल.

😀 तुमचा proximity sensor प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील मूळ दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.