# आफ्नो वस्तु डिटेक्टरलाई आफ्नो IoT उपकरणबाट प्रयोग गर्नुहोस् - Wio Terminal

एक पटक तपाईंको वस्तु डिटेक्टर प्रकाशित भएपछि, यसलाई तपाईंको IoT उपकरणबाट प्रयोग गर्न सकिन्छ।

## छवि वर्गीकरण परियोजना प्रतिलिपि गर्नुहोस्

तपाईंको स्टक डिटेक्टरको अधिकांश भाग तपाईंले अघिल्लो पाठमा बनाएको छवि वर्गीकरण परियोजनासँग समान छ।

### कार्य - छवि वर्गीकरण परियोजना प्रतिलिपि गर्नुहोस्

1. आफ्नो Wio Terminal मा ArduCam जडान गर्नुहोस्, [निर्माण परियोजनाको पाठ २](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) का चरणहरू अनुसरण गर्दै।

    तपाईंले क्यामेरालाई एकै स्थानमा स्थिर गर्न चाहन सक्नुहुन्छ, उदाहरणका लागि, केबललाई बक्स वा क्यानमाथि झुण्ड्याएर, वा क्यामेरालाई डबल-साइड टेपको प्रयोग गरेर बक्समा टाँसेर।

1. PlatformIO प्रयोग गरेर नयाँ Wio Terminal परियोजना सिर्जना गर्नुहोस्। यस परियोजनालाई `stock-counter` नाम दिनुहोस्।

1. [निर्माण परियोजनाको पाठ २](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) का चरणहरू दोहोर्याएर क्यामेराबाट छविहरू कैद गर्नुहोस्।

1. [निर्माण परियोजनाको पाठ २](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) का चरणहरू दोहोर्याएर छविहरू वर्गीकृत गर्न कोड प्रयोग गर्नुहोस्। यो कोडको अधिकांश भाग वस्तु पत्ता लगाउन पुन: प्रयोग गरिनेछ।

## कोडलाई वर्गीकरणबाट छवि डिटेक्टरमा परिवर्तन गर्नुहोस्

तपाईंले छविहरू वर्गीकृत गर्न प्रयोग गरेको कोड वस्तु पत्ता लगाउन प्रयोग हुने कोडसँग धेरै मिल्दोजुल्दो छ। मुख्य भिन्नता भनेको Custom Vision बाट प्राप्त गरिएको URL र कलको परिणाम हो।

### कार्य - कोडलाई वर्गीकरणबाट छवि डिटेक्टरमा परिवर्तन गर्नुहोस्

1. `main.cpp` फाइलको माथिल्लो भागमा निम्न include directive थप्नुहोस्:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` कार्यको नामलाई `detectStock` मा परिवर्तन गर्नुहोस्, कार्यको नाम र `buttonPressed` कार्यमा गरिएको कल दुवैमा।

1. `detectStock` कार्यको माथि, कुनै पनि कम सम्भावना भएका पत्ता लगाउनेहरूलाई फिल्टर गर्न थ्रेसहोल्ड घोषणा गर्नुहोस्:

    ```cpp
    const float threshold = 0.3f;
    ```

    छवि वर्गीकर्ताले प्रत्येक ट्यागका लागि केवल एक परिणाम फर्काउँछ, तर वस्तु डिटेक्टरले धेरै परिणामहरू फर्काउँछ, त्यसैले कम सम्भावना भएका कुनै पनि फिल्टर गर्न आवश्यक छ।

1. `detectStock` कार्यको माथि, भविष्यवाणीहरू प्रक्रिया गर्न कार्य घोषणा गर्नुहोस्:

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

    यसले भविष्यवाणीहरूको सूची लिन्छ र तिनीहरूलाई सिरियल मोनिटरमा प्रिन्ट गर्दछ।

1. `detectStock` कार्यमा, भविष्यवाणीहरूमा लुप गर्ने `for` लूपको सामग्रीलाई निम्नसँग प्रतिस्थापन गर्नुहोस्:

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

    यसले भविष्यवाणीहरूमा लुप गर्छ, सम्भावनालाई थ्रेसहोल्डसँग तुलना गर्छ। थ्रेसहोल्डभन्दा उच्च सम्भावना भएका सबै भविष्यवाणीहरूलाई `list` मा थपेर `processPredictions` कार्यमा पठाइन्छ।

1. आफ्नो कोड अपलोड र चलाउनुहोस्। क्यामेरालाई शेल्फमा रहेका वस्तुहरूतर्फ सोझ्याउनुहोस् र C बटन थिच्नुहोस्। तपाईंले सिरियल मोनिटरमा आउटपुट देख्नुहुनेछ:

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

    > 💁 तपाईंले आफ्नो छविहरूका लागि उपयुक्त थ्रेसहोल्ड समायोजन गर्न आवश्यक पर्न सक्छ।

    तपाईंले लिइएको छवि र यी मानहरू Custom Vision को **Predictions** ट्याबमा देख्न सक्नुहुनेछ।

    ![शेल्फमा ४ वटा टमाटर पेस्टका क्यानहरू, जसमा ३५.८%, ३३.५%, २५.७% र १६.६% का भविष्यवाणीहरू छन्](../../../../../translated_images/ne/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 तपाईंले यो कोड [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंको स्टक काउन्टर कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।