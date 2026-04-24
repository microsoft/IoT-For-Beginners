# प्रतिमा वर्गीकृत करा - व्हर्च्युअल IoT हार्डवेअर आणि रास्पबेरी पाय

या धड्याच्या या भागात, तुम्ही कॅमेऱ्याने कॅप्चर केलेली प्रतिमा वर्गीकृत करण्यासाठी Custom Vision सेवेकडे पाठवाल.

## Custom Vision कडे प्रतिमा पाठवा

Custom Vision सेवेसाठी एक Python SDK उपलब्ध आहे, ज्याचा वापर प्रतिमा वर्गीकृत करण्यासाठी केला जाऊ शकतो.

### कार्य - Custom Vision कडे प्रतिमा पाठवा

1. VS Code मध्ये `fruit-quality-detector` फोल्डर उघडा. जर तुम्ही व्हर्च्युअल IoT डिव्हाइस वापरत असाल, तर टर्मिनलमध्ये व्हर्च्युअल वातावरण चालू असल्याची खात्री करा.

1. Custom Vision कडे प्रतिमा पाठवण्यासाठी Python SDK Pip पॅकेज म्हणून उपलब्ध आहे. ते खालील कमांडसह इन्स्टॉल करा:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` फाइलच्या शीर्षस्थानी खालील आयात स्टेटमेंट्स जोडा:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    हे Custom Vision लायब्ररीमधील काही मॉड्यूल्स आणते, ज्यामध्ये प्रेडिक्शन कीसह प्रमाणीकरण करण्यासाठी एक मॉड्यूल आणि Custom Vision कॉल करण्यासाठी प्रेडिक्शन क्लायंट क्लास समाविष्ट आहे.

1. फाइलच्या शेवटी खालील कोड जोडा:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>` च्या जागी या धड्यातील *Prediction URL* डायलॉगमधून कॉपी केलेला URL ठेवा. `<prediction key>` च्या जागी त्याच डायलॉगमधून कॉपी केलेली प्रेडिक्शन की ठेवा.

1. *Prediction URL* डायलॉगने दिलेला प्रेडिक्शन URL थेट REST एन्डपॉइंट कॉल करताना वापरण्यासाठी डिझाइन केलेला आहे. Python SDK URL चे भाग वेगवेगळ्या ठिकाणी वापरतो. URL चे भाग वेगळे करण्यासाठी खालील कोड जोडा:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    हा कोड URL विभाजित करतो, ज्यामध्ये `https://<location>.api.cognitive.microsoft.com` हा एन्डपॉइंट, प्रोजेक्ट ID, आणि प्रकाशित आवृत्तीचे नाव काढले जाते.

1. प्रेडिक्शन करण्यासाठी खालील कोडसह एक प्रेडिक्टर ऑब्जेक्ट तयार करा:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` प्रेडिक्शन कीला रॅप करतो. याचा वापर एन्डपॉइंटकडे पॉइंट करणारा प्रेडिक्शन क्लायंट ऑब्जेक्ट तयार करण्यासाठी केला जातो.

1. खालील कोडसह प्रतिमा Custom Vision कडे पाठवा:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    हा कोड प्रतिमेला सुरुवातीला परत नेतो आणि नंतर ती प्रेडिक्शन क्लायंटकडे पाठवतो.

1. शेवटी, खालील कोडसह परिणाम दाखवा:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    हा कोड परत आलेल्या सर्व प्रेडिक्शन्समधून लूप करतो आणि ते टर्मिनलवर दाखवतो. परत आलेल्या संभाव्यता 0-1 दरम्यान फ्लोटिंग पॉइंट नंबर असतात, जिथे 0 म्हणजे 0% शक्यता आणि 1 म्हणजे 100% शक्यता.

    > 💁 प्रतिमा वर्गीकर्ते वापरलेल्या सर्व टॅग्ससाठी टक्केवारी परत करतात. प्रत्येक टॅगसाठी प्रतिमेने त्या टॅगशी जुळण्याची शक्यता असते.

1. तुमचा कोड चालवा, तुमचा कॅमेरा फळांकडे किंवा योग्य प्रतिमासेटकडे किंवा व्हर्च्युअल IoT हार्डवेअर वापरत असल्यास वेबकॅमवर दिसणाऱ्या फळांकडे निर्देशित करा. तुम्हाला कन्सोलमध्ये आउटपुट दिसेल:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    तुम्ही घेतलेली प्रतिमा आणि **Predictions** टॅबमध्ये हे मूल्ये Custom Vision मध्ये पाहू शकाल.

    ![Custom Vision मध्ये एक केळे, 56.8% पिकलेले आणि 43.1% न पिकलेले म्हणून प्रेडिक्ट केलेले](../../../../../translated_images/mr/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 तुम्हाला हा कोड [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) किंवा [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) फोल्डरमध्ये सापडेल.

😀 तुमचा फळ गुणवत्ता वर्गीकर्ता प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.