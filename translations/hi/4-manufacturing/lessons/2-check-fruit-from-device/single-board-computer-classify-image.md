# छवि को वर्गीकृत करें - वर्चुअल IoT हार्डवेयर और रास्पबेरी पाई

इस पाठ के इस भाग में, आप कैमरे द्वारा कैप्चर की गई छवि को कस्टम विजन सेवा में भेजेंगे ताकि इसे वर्गीकृत किया जा सके।

## कस्टम विजन को छवियां भेजें

कस्टम विजन सेवा में एक Python SDK है जिसका उपयोग आप छवियों को वर्गीकृत करने के लिए कर सकते हैं।

### कार्य - कस्टम विजन को छवियां भेजें

1. `fruit-quality-detector` फ़ोल्डर को VS Code में खोलें। यदि आप वर्चुअल IoT डिवाइस का उपयोग कर रहे हैं, तो सुनिश्चित करें कि वर्चुअल वातावरण टर्मिनल में चल रहा है।

1. कस्टम विजन को छवियां भेजने के लिए Python SDK एक Pip पैकेज के रूप में उपलब्ध है। इसे निम्नलिखित कमांड के साथ इंस्टॉल करें:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` फ़ाइल के शीर्ष पर निम्नलिखित इम्पोर्ट स्टेटमेंट जोड़ें:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    यह कस्टम विजन लाइब्रेरी से कुछ मॉड्यूल लाता है, एक प्रेडिक्शन कुंजी के साथ प्रमाणित करने के लिए, और एक प्रेडिक्शन क्लाइंट क्लास प्रदान करने के लिए जो कस्टम विजन को कॉल कर सकता है।

1. फ़ाइल के अंत में निम्नलिखित कोड जोड़ें:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>` को उस URL से बदलें जिसे आपने इस पाठ के पहले *Prediction URL* डायलॉग से कॉपी किया था। `<prediction key>` को उसी डायलॉग से कॉपी की गई प्रेडिक्शन कुंजी से बदलें।

1. *Prediction URL* डायलॉग द्वारा प्रदान किया गया प्रेडिक्शन URL REST एंडपॉइंट को सीधे कॉल करने के लिए डिज़ाइन किया गया है। Python SDK URL के भागों का उपयोग विभिन्न स्थानों पर करता है। इस URL को आवश्यक भागों में विभाजित करने के लिए निम्नलिखित कोड जोड़ें:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    यह URL को विभाजित करता है, `https://<location>.api.cognitive.microsoft.com` का एंडपॉइंट, प्रोजेक्ट ID, और प्रकाशित संस्करण का नाम निकालता है।

1. प्रेडिक्शन करने के लिए एक प्रेडिक्टर ऑब्जेक्ट बनाएं निम्नलिखित कोड के साथ:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` प्रेडिक्शन कुंजी को रैप करता है। इन्हें फिर एंडपॉइंट पर इंगित करने वाले प्रेडिक्शन क्लाइंट ऑब्जेक्ट बनाने के लिए उपयोग किया जाता है।

1. कस्टम विजन को छवि भेजें निम्नलिखित कोड का उपयोग करके:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    यह छवि को शुरुआत में वापस ले जाता है, फिर इसे प्रेडिक्शन क्लाइंट को भेजता है।

1. अंत में, परिणाम दिखाएं निम्नलिखित कोड के साथ:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    यह सभी प्रेडिक्शन के माध्यम से लूप करेगा जो वापस किए गए हैं और उन्हें टर्मिनल पर दिखाएगा। लौटाए गए संभावनाएं 0-1 के फ्लोटिंग पॉइंट नंबर हैं, जहां 0 का मतलब टैग से मेल खाने की 0% संभावना है, और 1 का मतलब 100% संभावना है।

    > 💁 छवि वर्गीकरणकर्ता उन सभी टैग के लिए प्रतिशत लौटाएंगे जिनका उपयोग किया गया है। प्रत्येक टैग के लिए यह संभावना होगी कि छवि उस टैग से मेल खाती है।

1. अपना कोड चलाएं, अपने कैमरे को कुछ फल की ओर इंगित करें, या उपयुक्त छवि सेट का उपयोग करें, या यदि वर्चुअल IoT हार्डवेयर का उपयोग कर रहे हैं तो अपने वेबकैम पर फल दिखाएं। आप कंसोल में आउटपुट देखेंगे:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    आप देख पाएंगे कि ली गई छवि और ये मान **Predictions** टैब में कस्टम विजन में दिखाई देंगे।

    ![कस्टम विजन में एक केला, 56.8% पर पका हुआ और 43.1% पर कच्चा भविष्यवाणी की गई](../../../../../translated_images/hi/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 आप इस कोड को [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) या [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) फ़ोल्डर में पा सकते हैं।

😀 आपका फल गुणवत्ता वर्गीकरण प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।