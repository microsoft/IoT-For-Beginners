# आपल्या IoT डिव्हाइसवरून ऑब्जेक्ट डिटेक्टर कॉल करा - Wio Terminal

एकदा तुमचा ऑब्जेक्ट डिटेक्टर प्रकाशित झाल्यावर, तो तुमच्या IoT डिव्हाइसवरून वापरता येईल.

## इमेज क्लासिफायर प्रोजेक्ट कॉपी करा

तुमचा स्टॉक डिटेक्टर मुख्यतः त्या इमेज क्लासिफायरसारखाच आहे जो तुम्ही मागील धड्यात तयार केला होता.

### कार्य - इमेज क्लासिफायर प्रोजेक्ट कॉपी करा

1. तुमचा ArduCam Wio Terminal शी कनेक्ट करा, [मॅन्युफॅक्चरिंग प्रोजेक्टच्या धडा 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) मधील स्टेप्स फॉलो करा.

    तुम्हाला कॅमेरा एका स्थिर स्थितीत ठेवायचा असेल, उदाहरणार्थ, केबल बॉक्स किंवा कॅनवर टांगून ठेवणे किंवा डबल-साइड टेपने कॅमेरा बॉक्सला जोडणे.

1. PlatformIO वापरून एक नवीन Wio Terminal प्रोजेक्ट तयार करा. या प्रोजेक्टचे नाव `stock-counter` ठेवा.

1. [मॅन्युफॅक्चरिंग प्रोजेक्टच्या धडा 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) मधील स्टेप्स कॉपी करा, ज्यामुळे कॅमेरामधून इमेजेस कॅप्चर करता येतील.

1. [मॅन्युफॅक्चरिंग प्रोजेक्टच्या धडा 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) मधील स्टेप्स कॉपी करा, ज्यामुळे इमेज क्लासिफायर कॉल करता येईल. या कोडचा मोठा भाग ऑब्जेक्ट्स डिटेक्ट करण्यासाठी पुन्हा वापरला जाईल.

## कोड क्लासिफायरवरून इमेज डिटेक्टरमध्ये बदला

तुम्ही इमेजेस क्लासिफाय करण्यासाठी वापरलेला कोड ऑब्जेक्ट्स डिटेक्ट करण्यासाठी वापरल्या जाणाऱ्या कोडसारखाच आहे. मुख्य फरक म्हणजे Custom Vision कडून मिळालेला URL आणि कॉलचे परिणाम.

### कार्य - कोड क्लासिफायरवरून इमेज डिटेक्टरमध्ये बदला

1. `main.cpp` फाईलच्या वरच्या भागात खालील include directive जोडा:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` फंक्शनचे नाव बदलून `detectStock` करा, फंक्शनचे नाव आणि `buttonPressed` फंक्शनमधील कॉल दोन्ही.

1. `detectStock` फंक्शनच्या वर एक threshold डिक्लेअर करा, ज्यामुळे कमी probability असलेल्या डिटेक्शन्स फिल्टर करता येतील:

    ```cpp
    const float threshold = 0.3f;
    ```

    इमेज क्लासिफायर फक्त प्रत्येक टॅगसाठी एकच परिणाम परत करतो, परंतु ऑब्जेक्ट डिटेक्टर अनेक परिणाम परत करतो, त्यामुळे कमी probability असलेले परिणाम फिल्टर करणे आवश्यक आहे.

1. `detectStock` फंक्शनच्या वर एक फंक्शन डिक्लेअर करा, ज्यामुळे predictions process करता येतील:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    हे predictions ची यादी घेते आणि ती serial monitor वर प्रिंट करते.

1. `detectStock` फंक्शनमध्ये, predictions वर लूप करणाऱ्या `for` लूपच्या कंटेंटला खालील कोडने बदला:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    हे predictions वर लूप करते, probability threshold शी तुलना करते. ज्या predictions ची probability threshold पेक्षा जास्त आहे, त्या `list` मध्ये जोडल्या जातात आणि `processPredictions` फंक्शनला पास केल्या जातात.

1. तुमचा कोड अपलोड करा आणि चालवा. कॅमेरा शेल्फवरील वस्तूंवर पॉइंट करा आणि C बटण दाबा. तुम्हाला serial monitor मध्ये आउटपुट दिसेल:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 तुम्हाला तुमच्या इमेजेससाठी योग्य threshold सेट करावा लागेल.

    तुम्ही घेतलेली इमेज आणि **Predictions** टॅबमध्ये Custom Vision मध्ये हे मूल्ये पाहू शकता.

    ![शेल्फवर ठेवलेल्या टोमॅटो पेस्टच्या 4 कॅन्ससाठी 35.8%, 33.5%, 25.7% आणि 16.6% च्या डिटेक्शनसाठी predictions](../../../../../translated_images/mr/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 तुम्ही हा कोड [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुमचा स्टॉक काउंटर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.