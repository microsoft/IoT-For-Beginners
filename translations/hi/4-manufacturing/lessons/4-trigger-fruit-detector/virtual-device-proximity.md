<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-25T16:42:12+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "hi"
}
-->
# निकटता का पता लगाना - वर्चुअल IoT हार्डवेयर

इस पाठ के इस भाग में, आप अपने वर्चुअल IoT डिवाइस में एक निकटता सेंसर जोड़ेंगे और इससे दूरी पढ़ेंगे।

## हार्डवेयर

वर्चुअल IoT डिवाइस एक सिम्युलेटेड दूरी सेंसर का उपयोग करेगा।

एक भौतिक IoT डिवाइस में, आप दूरी का पता लगाने के लिए लेजर रेंजिंग मॉड्यूल वाले सेंसर का उपयोग करेंगे।

### CounterFit में दूरी सेंसर जोड़ें

वर्चुअल दूरी सेंसर का उपयोग करने के लिए, आपको इसे CounterFit ऐप में जोड़ना होगा।

#### कार्य - CounterFit में दूरी सेंसर जोड़ें

CounterFit ऐप में दूरी सेंसर जोड़ें।

1. VS Code में `fruit-quality-detector` कोड खोलें और सुनिश्चित करें कि वर्चुअल वातावरण सक्रिय है।

1. एक अतिरिक्त Pip पैकेज इंस्टॉल करें ताकि एक CounterFit शिम इंस्टॉल किया जा सके जो दूरी सेंसर से बात कर सके। यह [rpi-vl53l0x Pip पैकेज](https://pypi.org/project/rpi-vl53l0x/) को सिम्युलेट करता है, जो [VL53L0X टाइम-ऑफ-फ्लाइट दूरी सेंसर](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) के साथ इंटरैक्ट करता है। सुनिश्चित करें कि आप इसे उस टर्मिनल से इंस्टॉल कर रहे हैं जिसमें वर्चुअल वातावरण सक्रिय है।

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. सुनिश्चित करें कि CounterFit वेब ऐप चल रहा है।

1. एक दूरी सेंसर बनाएं:

    1. *Sensors* पैन में *Create sensor* बॉक्स में जाएं, *Sensor type* ड्रॉपडाउन करें और *Distance* चुनें।

    1. *Units* को `Millimeter` पर छोड़ दें।

    1. यह सेंसर एक I²C सेंसर है, इसलिए इसका पता `0x29` पर सेट करें। यदि आप एक भौतिक VL53L0X सेंसर का उपयोग करते हैं, तो यह पता हार्डकोडेड होता।

    1. दूरी सेंसर बनाने के लिए **Add** बटन चुनें।

    ![दूरी सेंसर सेटिंग्स](../../../../../translated_images/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.hi.png)

    दूरी सेंसर बनाया जाएगा और सेंसर सूची में दिखाई देगा।

    ![दूरी सेंसर बनाया गया](../../../../../translated_images/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.hi.png)

## दूरी सेंसर प्रोग्राम करें

अब वर्चुअल IoT डिवाइस को सिम्युलेटेड दूरी सेंसर का उपयोग करने के लिए प्रोग्राम किया जा सकता है।

### कार्य - टाइम ऑफ फ्लाइट सेंसर प्रोग्राम करें

1. `fruit-quality-detector` प्रोजेक्ट में एक नया फाइल बनाएं जिसका नाम `distance-sensor.py` हो।

    > 💁 कई IoT डिवाइस को सिम्युलेट करने का आसान तरीका है कि प्रत्येक को अलग-अलग Python फाइल में करें और फिर उन्हें एक साथ चलाएं।

1. CounterFit से कनेक्शन शुरू करने के लिए निम्न कोड जोड़ें:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. इसके नीचे निम्न कोड जोड़ें:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    यह VL53L0X टाइम ऑफ फ्लाइट सेंसर के लिए सेंसर लाइब्रेरी शिम को इंपोर्ट करता है।

1. इसके नीचे सेंसर तक पहुंचने के लिए निम्न कोड जोड़ें:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    यह कोड एक दूरी सेंसर घोषित करता है और फिर सेंसर को शुरू करता है।

1. अंत में, दूरी पढ़ने के लिए एक अनंत लूप जोड़ें:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    यह कोड सेंसर से पढ़ने के लिए तैयार मान की प्रतीक्षा करता है और फिर इसे कंसोल में प्रिंट करता है।

1. इस कोड को चलाएं।

    > 💁 ध्यान दें कि यह फाइल `distance-sensor.py` कहलाती है! इसे Python के माध्यम से चलाना सुनिश्चित करें, न कि `app.py`।

1. आप कंसोल में दूरी माप देखेंगे। CounterFit में मान बदलें या रैंडम मान का उपयोग करें और इस बदलाव को देखें।

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 आप इस कोड को [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) फोल्डर में पा सकते हैं।

😀 आपका निकटता सेंसर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।