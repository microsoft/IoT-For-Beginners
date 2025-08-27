<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T14:10:20+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "mr"
}
-->
# स्पीच टू टेक्स्ट - वर्च्युअल IoT डिव्हाइस

या धड्याच्या या भागात, तुम्ही तुमच्या मायक्रोफोनमधून कॅप्चर केलेले भाषण स्पीच सर्व्हिसचा वापर करून टेक्स्टमध्ये रूपांतरित करण्यासाठी कोड लिहाल.

## भाषणाचे टेक्स्टमध्ये रूपांतर करा

Windows, Linux, आणि macOS वर, स्पीच सर्व्हिसेससाठी Python SDK चा वापर करून तुमच्या मायक्रोफोनमधून भाषण ऐकले जाऊ शकते आणि ओळखलेले भाषण टेक्स्टमध्ये रूपांतरित केले जाऊ शकते. हे सतत ऐकते, ऑडिओ पातळी शोधते आणि भाषण संपल्यावर, जसे की भाषणाच्या ब्लॉकच्या शेवटी, ऑडिओ पातळी कमी झाल्यावर, भाषणाचे टेक्स्टमध्ये रूपांतर करण्यासाठी पाठवते.

### कार्य - भाषणाचे टेक्स्टमध्ये रूपांतर करा

1. `smart-timer` नावाच्या फोल्डरमध्ये `app.py` नावाची एक फाईल आणि Python वर्च्युअल एन्व्हायर्नमेंटसह तुमच्या संगणकावर एक नवीन Python अॅप तयार करा.

1. स्पीच सर्व्हिसेससाठी Pip पॅकेज इन्स्टॉल करा. हे वर्च्युअल एन्व्हायर्नमेंट सक्रिय असलेल्या टर्मिनलमधून इन्स्टॉल करत असल्याची खात्री करा.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ जर तुम्हाला खालील त्रुटी आली:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > तुम्हाला Pip अपडेट करावे लागेल. हे खालील कमांडसह करा आणि नंतर पुन्हा पॅकेज इन्स्टॉल करण्याचा प्रयत्न करा.
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py` फाईलमध्ये खालील इम्पोर्ट्स जोडा:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    हे भाषण ओळखण्यासाठी वापरल्या जाणाऱ्या काही क्लासेस इम्पोर्ट करते.

1. काही कॉन्फिगरेशन जाहीर करण्यासाठी खालील कोड जोडा:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>` ला तुमच्या स्पीच सर्व्हिससाठीच्या API कीने बदला. `<location>` ला तुम्ही स्पीच सर्व्हिस रिसोर्स तयार करताना वापरलेल्या स्थानाने बदला.

    `<language>` ला तुम्ही ज्या भाषेत बोलणार आहात त्या भाषेच्या स्थानिक नावाने बदला, उदाहरणार्थ इंग्रजीसाठी `en-GB`, किंवा कॅन्टोनीजसाठी `zn-HK`. समर्थित भाषांची आणि त्यांच्या स्थानिक नावांची यादी तुम्ही [Microsoft Docs वरील भाषा आणि आवाज समर्थन दस्तऐवज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मध्ये पाहू शकता.

    ही कॉन्फिगरेशन नंतर `SpeechConfig` ऑब्जेक्ट तयार करण्यासाठी वापरली जाते, जी स्पीच सर्व्हिसेस कॉन्फिगर करण्यासाठी वापरली जाईल.

1. स्पीच रेकग्नायझर तयार करण्यासाठी खालील कोड जोडा:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. स्पीच रेकग्नायझर बॅकग्राउंड थ्रेडवर चालतो, ऑडिओ ऐकतो आणि त्यातील भाषणाचे टेक्स्टमध्ये रूपांतर करतो. तुम्ही टेक्स्ट एका कॉलबॅक फंक्शनद्वारे मिळवू शकता - एक फंक्शन जे तुम्ही परिभाषित करता आणि रेकग्नायझरला पास करता. प्रत्येक वेळी भाषण ओळखले जाते, तेव्हा कॉलबॅक कॉल केला जातो. खालील कोड जोडा, कॉलबॅक परिभाषित करण्यासाठी आणि रेकग्नायझरला पास करण्यासाठी, तसेच टेक्स्ट प्रक्रिया करण्यासाठी एक फंक्शन परिभाषित करा, जे कन्सोलवर लिहिते:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. रेकग्नायझर फक्त तेव्हा ऐकायला सुरुवात करतो जेव्हा तुम्ही स्पष्टपणे ते सुरू करता. ओळख सुरू करण्यासाठी खालील कोड जोडा. हे बॅकग्राउंडमध्ये चालते, त्यामुळे तुमच्या अॅप्लिकेशनला चालू ठेवण्यासाठी एक अनंत लूप आवश्यक असेल जो झोपतो.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. हे अॅप चालवा. तुमच्या मायक्रोफोनमध्ये बोला आणि ऑडिओ टेक्स्टमध्ये रूपांतरित होऊन कन्सोलवर दिसेल.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    वेगवेगळ्या प्रकारच्या वाक्यांचा प्रयत्न करा, तसेच ज्या वाक्यांमध्ये शब्द सारखेच वाटतात पण त्यांचे अर्थ वेगळे असतात. उदाहरणार्थ, जर तुम्ही इंग्रजीत बोलत असाल, तर 'I want to buy two bananas and an apple too' असे म्हणा आणि लक्षात घ्या की ते योग्य to, two आणि too वापरेल, फक्त त्याच्या ध्वनीवर नाही तर शब्दाच्या संदर्भावर आधारित.

> 💁 तुम्ही हा कोड [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) फोल्डरमध्ये शोधू शकता.

😀 तुमचा स्पीच टू टेक्स्ट प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील मूळ दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.