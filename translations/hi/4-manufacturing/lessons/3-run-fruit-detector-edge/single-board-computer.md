<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-25T16:38:26+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "hi"
}
-->
# IoT Edge आधारित इमेज क्लासिफायर का उपयोग करके एक छवि को वर्गीकृत करें - वर्चुअल IoT हार्डवेयर और रास्पबेरी पाई

इस पाठ के इस भाग में, आप IoT Edge डिवाइस पर चल रहे इमेज क्लासिफायर का उपयोग करेंगे।

## IoT Edge क्लासिफायर का उपयोग करें

IoT डिवाइस को IoT Edge इमेज क्लासिफायर का उपयोग करने के लिए पुनर्निर्देशित किया जा सकता है। इमेज क्लासिफायर के लिए URL है `http://<IP address or name>/image`, जहां `<IP address or name>` को IoT Edge चला रहे कंप्यूटर के IP एड्रेस या होस्ट नाम से बदलें।

Custom Vision के लिए Python लाइब्रेरी केवल क्लाउड-होस्टेड मॉडल्स के साथ काम करती है, IoT Edge पर होस्ट किए गए मॉडल्स के साथ नहीं। इसका मतलब है कि आपको क्लासिफायर को कॉल करने के लिए REST API का उपयोग करना होगा।

### कार्य - IoT Edge क्लासिफायर का उपयोग करें

1. यदि `fruit-quality-detector` प्रोजेक्ट पहले से VS Code में खुला नहीं है, तो इसे खोलें। यदि आप वर्चुअल IoT डिवाइस का उपयोग कर रहे हैं, तो सुनिश्चित करें कि वर्चुअल एनवायरनमेंट सक्रिय है।

1. `app.py` फाइल खोलें, और `azure.cognitiveservices.vision.customvision.prediction` और `msrest.authentication` से आयात किए गए स्टेटमेंट्स को हटा दें।

1. फाइल के शीर्ष पर निम्नलिखित आयात जोड़ें:

    ```python
    import requests
    ```

1. इमेज को फाइल में सेव करने के बाद के सभी कोड को हटा दें, `image_file.write(image.read())` से लेकर फाइल के अंत तक।

1. फाइल के अंत में निम्नलिखित कोड जोड़ें:

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

    `<URL>` को अपने क्लासिफायर के URL से बदलें।

    यह कोड क्लासिफायर को REST POST अनुरोध भेजता है, जिसमें इमेज को अनुरोध के बॉडी के रूप में भेजा जाता है। परिणाम JSON के रूप में वापस आते हैं, और इसे डिकोड करके संभावनाओं को प्रिंट किया जाता है।

1. अपना कोड चलाएं, अपने कैमरे को किसी फल की ओर इंगित करें, या उपयुक्त इमेज सेट का उपयोग करें, या यदि वर्चुअल IoT हार्डवेयर का उपयोग कर रहे हैं तो अपने वेबकैम पर फल को दिखाएं। आप कंसोल में आउटपुट देखेंगे:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 आप इस कोड को [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) या [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) फोल्डर में पा सकते हैं।

😀 आपका फल गुणवत्ता क्लासिफायर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।