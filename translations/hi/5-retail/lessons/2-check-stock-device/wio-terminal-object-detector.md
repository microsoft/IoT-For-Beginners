# अपने IoT डिवाइस से ऑब्जेक्ट डिटेक्टर को कॉल करें - Wio Terminal

एक बार आपका ऑब्जेक्ट डिटेक्टर प्रकाशित हो जाए, तो इसे आपके IoT डिवाइस से उपयोग किया जा सकता है।

## इमेज क्लासिफायर प्रोजेक्ट कॉपी करें

आपका स्टॉक डिटेक्टर ज्यादातर उसी तरह का है जैसा आपने पिछले पाठ में इमेज क्लासिफायर बनाया था।

### कार्य - इमेज क्लासिफायर प्रोजेक्ट कॉपी करें

1. अपने ArduCam को Wio Terminal से कनेक्ट करें, [मैन्युफैक्चरिंग प्रोजेक्ट के पाठ 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) में दिए गए चरणों का पालन करते हुए।

    आप कैमरे को एक स्थिर स्थिति में भी सेट कर सकते हैं, जैसे कि केबल को किसी बॉक्स या कैन के ऊपर लटकाकर, या डबल-साइडेड टेप का उपयोग करके कैमरे को बॉक्स पर फिक्स करके।

1. PlatformIO का उपयोग करके एक नया Wio Terminal प्रोजेक्ट बनाएं। इस प्रोजेक्ट का नाम `stock-counter` रखें।

1. [मैन्युफैक्चरिंग प्रोजेक्ट के पाठ 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) से चरणों को दोहराएं ताकि कैमरे से इमेज कैप्चर की जा सके।

1. [मैन्युफैक्चरिंग प्रोजेक्ट के पाठ 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) से चरणों को दोहराएं ताकि इमेज क्लासिफायर को कॉल किया जा सके। इस कोड का अधिकांश हिस्सा ऑब्जेक्ट्स को डिटेक्ट करने के लिए पुनः उपयोग किया जाएगा।

## कोड को क्लासिफायर से इमेज डिटेक्टर में बदलें

आपने इमेज क्लासिफाई करने के लिए जो कोड उपयोग किया था, वह ऑब्जेक्ट्स को डिटेक्ट करने के कोड से बहुत मिलता-जुलता है। मुख्य अंतर वह URL है जिसे Custom Vision से प्राप्त किया गया है, और कॉल के परिणाम हैं।

### कार्य - कोड को क्लासिफायर से इमेज डिटेक्टर में बदलें

1. `main.cpp` फाइल के शीर्ष पर निम्नलिखित इनक्लूड डायरेक्टिव जोड़ें:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` फंक्शन का नाम बदलकर `detectStock` रखें, फंक्शन के नाम और `buttonPressed` फंक्शन में कॉल दोनों में।

1. `detectStock` फंक्शन के ऊपर एक थ्रेशहोल्ड घोषित करें ताकि कम संभावना वाले किसी भी डिटेक्शन को फ़िल्टर किया जा सके:

    ```cpp
    const float threshold = 0.3f;
    ```

    इमेज क्लासिफायर केवल एक टैग के लिए एक परिणाम लौटाता है, लेकिन ऑब्जेक्ट डिटेक्टर कई परिणाम लौटाता है, इसलिए कम संभावना वाले किसी भी परिणाम को फ़िल्टर करना आवश्यक है।

1. `detectStock` फंक्शन के ऊपर एक फंक्शन घोषित करें जो प्रेडिक्शन्स को प्रोसेस करे:

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

    यह प्रेडिक्शन्स की सूची लेता है और उन्हें सीरियल मॉनिटर पर प्रिंट करता है।

1. `detectStock` फंक्शन में, प्रेडिक्शन्स के माध्यम से लूप करने वाले `for` लूप की सामग्री को निम्नलिखित से बदलें:

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

    यह प्रेडिक्शन्स के माध्यम से लूप करता है, संभावना को थ्रेशहोल्ड से तुलना करता है। सभी प्रेडिक्शन्स जिनकी संभावना थ्रेशहोल्ड से अधिक होती है, उन्हें एक `list` में जोड़ा जाता है और `processPredictions` फंक्शन को पास किया जाता है।

1. अपना कोड अपलोड करें और चलाएं। कैमरे को शेल्फ पर रखे ऑब्जेक्ट्स की ओर पॉइंट करें और C बटन दबाएं। आप सीरियल मॉनिटर में आउटपुट देखेंगे:

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

    > 💁 आपको अपने इमेज के लिए उपयुक्त थ्रेशहोल्ड को समायोजित करने की आवश्यकता हो सकती है।

    आप ली गई इमेज और इन मानों को Custom Vision के **Predictions** टैब में देख पाएंगे।

    ![शेल्फ पर रखे टमाटर पेस्ट के 4 कैन और उनके 4 डिटेक्शन के लिए 35.8%, 33.5%, 25.7% और 16.6% की संभावना](../../../../../translated_images/hi/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 आप इस कोड को [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपका स्टॉक काउंटर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।