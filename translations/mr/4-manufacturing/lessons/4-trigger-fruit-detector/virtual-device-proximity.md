<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-27T10:54:14+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "mr"
}
-->
# जवळीक शोधा - आभासी IoT हार्डवेअर

या धड्याच्या भागात, तुम्ही तुमच्या आभासी IoT डिव्हाइसला एक जवळीक सेन्सर जोडाल आणि त्यातून अंतर वाचाल.

## हार्डवेअर

आभासी IoT डिव्हाइस एक अनुकरण केलेला अंतर सेन्सर वापरेल.

भौतिक IoT डिव्हाइससाठी, तुम्ही अंतर शोधण्यासाठी लेसर रेंजिंग मॉड्यूल असलेला सेन्सर वापराल.

### CounterFit मध्ये अंतर सेन्सर जोडा

आभासी अंतर सेन्सर वापरण्यासाठी, तुम्हाला CounterFit अॅपमध्ये एक सेन्सर जोडावा लागेल.

#### कार्य - CounterFit मध्ये अंतर सेन्सर जोडा

CounterFit अॅपमध्ये अंतर सेन्सर जोडा.

1. VS Code मध्ये `fruit-quality-detector` कोड उघडा आणि खात्री करा की आभासी वातावरण सक्रिय आहे.

1. CounterFit shim स्थापित करण्यासाठी एक अतिरिक्त Pip पॅकेज स्थापित करा, जे [rpi-vl53l0x Pip पॅकेज](https://pypi.org/project/rpi-vl53l0x/) चे अनुकरण करून अंतर सेन्सरशी संवाद साधू शकते. हे Python पॅकेज [VL53L0X टाइम-ऑफ-फ्लाइट डिस्टन्स सेन्सर](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) शी संवाद साधते. खात्री करा की तुम्ही हे आभासी वातावरण सक्रिय असलेल्या टर्मिनलमधून स्थापित करत आहात.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. खात्री करा की CounterFit वेब अॅप चालू आहे.

1. अंतर सेन्सर तयार करा:

    1. *Sensors* पॅनमधील *Create sensor* बॉक्समध्ये, *Sensor type* ड्रॉपडाउन करा आणि *Distance* निवडा.

    1. *Units* `Millimeter` म्हणून ठेवा.

    1. हा सेन्सर I²C सेन्सर आहे, त्यामुळे पत्ता `0x29` सेट करा. जर तुम्ही भौतिक VL53L0X सेन्सर वापरला असता तर तो या पत्त्यावर हार्डकोड केलेला असता.

    1. अंतर सेन्सर तयार करण्यासाठी **Add** बटण निवडा.

    ![अंतर सेन्सर सेटिंग्ज](../../../../../translated_images/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.mr.png)

    अंतर सेन्सर तयार केला जाईल आणि सेन्सर यादीत दिसेल.

    ![अंतर सेन्सर तयार केला](../../../../../translated_images/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.mr.png)

## अंतर सेन्सर प्रोग्राम करा

आता आभासी IoT डिव्हाइस अनुकरण केलेल्या अंतर सेन्सरचा वापर करण्यासाठी प्रोग्राम केला जाऊ शकतो.

### कार्य - टाइम ऑफ फ्लाइट सेन्सर प्रोग्राम करा

1. `fruit-quality-detector` प्रोजेक्टमध्ये `distance-sensor.py` नावाची नवीन फाइल तयार करा.

    > 💁 अनेक IoT डिव्हाइस अनुकरण करण्याचा सोपा मार्ग म्हणजे प्रत्येक डिव्हाइससाठी वेगवेगळ्या Python फाइलमध्ये कोड लिहा आणि त्यांना एकाच वेळी चालवा.

1. खालील कोडसह CounterFit शी कनेक्शन सुरू करा:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. याखाली खालील कोड जोडा:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    हे VL53L0X टाइम ऑफ फ्लाइट सेन्सरसाठी सेन्सर लायब्ररी शिम आयात करते.

1. याखाली, सेन्सरमध्ये प्रवेश करण्यासाठी खालील कोड जोडा:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    हा कोड एक अंतर सेन्सर घोषित करतो आणि नंतर सेन्सर सुरू करतो.

1. शेवटी, अंतर वाचण्यासाठी एक अनंत लूप जोडा:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    हा कोड सेन्सरमधून वाचण्यासाठी मूल्य तयार होण्याची वाट पाहतो आणि नंतर ते कन्सोलवर प्रिंट करतो.

1. हा कोड चालवा.

    > 💁 लक्षात ठेवा की ही फाइल `distance-sensor.py` नावाची आहे! हे Python द्वारे चालवा, `app.py` द्वारे नाही.

1. तुम्हाला कन्सोलमध्ये अंतर मोजमाप दिसेल. CounterFit मध्ये मूल्य बदला किंवा यादृच्छिक मूल्ये वापरा आणि बदल पहा.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 तुम्ही हा कोड [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) फोल्डरमध्ये शोधू शकता.

😀 तुमचा जवळीक सेन्सर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरे त्रुटी किंवा अचूकतेच्या अभावाने ग्रस्त असू शकतात. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.