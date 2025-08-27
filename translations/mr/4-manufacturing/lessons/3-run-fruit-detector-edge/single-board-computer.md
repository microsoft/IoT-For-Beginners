<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T10:44:21+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "mr"
}
-->
# IoT Edge आधारित इमेज क्लासिफायर वापरून प्रतिमा वर्गीकृत करा - व्हर्च्युअल IoT हार्डवेअर आणि रास्पबेरी पाय

या धड्याच्या भागामध्ये, तुम्ही IoT Edge डिव्हाइसवर चालणाऱ्या इमेज क्लासिफायरचा वापर कराल.

## IoT Edge क्लासिफायर वापरा

IoT डिव्हाइसला IoT Edge इमेज क्लासिफायर वापरण्यासाठी पुनर्निर्देशित करता येते. इमेज क्लासिफायरसाठी URL `http://<IP address or name>/image` आहे, जिथे `<IP address or name>` च्या जागी IoT Edge चालवणाऱ्या संगणकाचा IP पत्ता किंवा होस्ट नाव टाकावे.

Custom Vision साठी Python लायब्ररी केवळ क्लाउड-होस्टेड मॉडेल्ससाठी कार्य करते, IoT Edge वर होस्ट केलेल्या मॉडेल्ससाठी नाही. याचा अर्थ तुम्हाला क्लासिफायरला कॉल करण्यासाठी REST API वापरावे लागेल.

### कार्य - IoT Edge क्लासिफायर वापरा

1. जर `fruit-quality-detector` प्रकल्प VS Code मध्ये उघडलेला नसेल, तर तो उघडा. जर तुम्ही व्हर्च्युअल IoT डिव्हाइस वापरत असाल, तर व्हर्च्युअल वातावरण सक्रिय असल्याची खात्री करा.

1. `app.py` फाइल उघडा आणि `azure.cognitiveservices.vision.customvision.prediction` आणि `msrest.authentication` मधील आयात स्टेटमेंट्स काढून टाका.

1. फाइलच्या वरच्या भागात खालील आयात जोडा:

    ```python
    import requests
    ```

1. प्रतिमा फाइलमध्ये सेव्ह केल्यानंतरच्या सर्व कोडला काढून टाका, `image_file.write(image.read())` पासून फाइलच्या शेवटापर्यंत.

1. फाइलच्या शेवटी खालील कोड जोडा:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    `<URL>` च्या जागी तुमच्या क्लासिफायरसाठी URL टाका.

    हा कोड क्लासिफायरला REST POST विनंती पाठवतो, ज्यामध्ये प्रतिमा विनंतीच्या बॉडीमध्ये पाठवली जाते. परिणाम JSON स्वरूपात परत येतात, आणि हे डिकोड करून संभाव्यता प्रिंट केल्या जातात.

1. तुमचा कोड चालवा, तुमचा कॅमेरा काही फळांकडे किंवा योग्य प्रतिमांकडे निर्देशित करून, किंवा जर तुम्ही व्हर्च्युअल IoT हार्डवेअर वापरत असाल तर तुमच्या वेबकॅमवर फळे दिसत असल्याची खात्री करा. तुम्हाला कन्सोलमध्ये आउटपुट दिसेल:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 तुम्ही हा कोड [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) किंवा [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) फोल्डरमध्ये शोधू शकता.

😀 तुमचा फळ गुणवत्ता क्लासिफायर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी, व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.