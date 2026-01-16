<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T09:55:31+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "mr"
}
-->
# आपल्या IoT डिव्हाइसवरून स्टॉक मोजा - Wio Terminal

भाकीत आणि त्यांचे बॉक्सिंग बॉक्सेस यांचे संयोजन प्रतिमेमध्ये स्टॉक मोजण्यासाठी वापरले जाऊ शकते.

## स्टॉक मोजा

![4 टोमॅटो पेस्टचे कॅन, प्रत्येक कॅनभोवती बॉक्सिंग बॉक्सेस](../../../../../translated_images/mr/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

वर दाखवलेल्या प्रतिमेमध्ये बॉक्सिंग बॉक्सेस थोडेसे ओव्हरलॅप झाले आहेत. जर हे ओव्हरलॅप खूप मोठे असते, तर बॉक्सिंग बॉक्सेस एकाच वस्तूला सूचित करू शकतात. वस्तू योग्य प्रकारे मोजण्यासाठी, तुम्हाला महत्त्वपूर्ण ओव्हरलॅप असलेल्या बॉक्सेसकडे दुर्लक्ष करणे आवश्यक आहे.

### कार्य - ओव्हरलॅप दुर्लक्षित करून स्टॉक मोजा

1. तुमचा `stock-counter` प्रकल्प उघडा, जर तो आधीच उघडलेला नसेल.

1. `processPredictions` फंक्शनच्या वर खालील कोड जोडा:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    हे बॉक्सिंग बॉक्सेस एकाच वस्तू मानले जाण्यापूर्वी परवानगी दिलेल्या टक्केवारी ओव्हरलॅपची व्याख्या करते. 0.20 म्हणजे 20% ओव्हरलॅप.

1. याखाली, आणि `processPredictions` फंक्शनच्या वर, दोन आयतांमधील ओव्हरलॅपची गणना करण्यासाठी खालील कोड जोडा:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    हा कोड प्रतिमेवरील पॉइंट्स साठवण्यासाठी `Point` स्ट्रक्ट परिभाषित करतो आणि वरच्या डाव्या आणि खालच्या उजव्या समन्वयाचा वापर करून आयत परिभाषित करण्यासाठी `Rect` स्ट्रक्ट परिभाषित करतो. त्यानंतर `area` फंक्शन परिभाषित करते जे वरच्या डाव्या आणि खालच्या उजव्या समन्वयावरून आयताचे क्षेत्रफळ गणना करते.

    पुढे, `overlappingArea` फंक्शन परिभाषित करते जे 2 आयतांचे ओव्हरलॅपिंग क्षेत्रफळ गणना करते. जर ते ओव्हरलॅप करत नसतील, तर ते 0 परत करते.

1. `overlappingArea` फंक्शनच्या खाली, बॉक्सिंग बॉक्सला `Rect` मध्ये रूपांतरित करण्यासाठी एक फंक्शन घोषित करा:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    हे ऑब्जेक्ट डिटेक्टरमधून भाकीत घेतो, बॉक्सिंग बॉक्स काढतो आणि बॉक्सिंग बॉक्सवरील मूल्यांचा वापर करून आयत परिभाषित करतो. उजव्या बाजूची गणना डावीकडून रुंदी जोडून केली जाते. तळाची गणना वरून उंची जोडून केली जाते.

1. भाकीत एकमेकांशी तुलना करणे आवश्यक आहे, आणि जर 2 भाकीतांमध्ये दिलेल्या टक्केवारीपेक्षा जास्त ओव्हरलॅप असेल, तर त्यापैकी एक हटवले पाहिजे. ओव्हरलॅप थ्रेशोल्ड टक्केवारी आहे, त्यामुळे बॉक्सिंग बॉक्सच्या सर्वात लहान आकाराच्या टक्केवारीने गुणाकार करणे आवश्यक आहे, जेणेकरून ओव्हरलॅप दिलेल्या टक्केवारीपेक्षा जास्त आहे का हे तपासता येईल. `processPredictions` फंक्शनची सामग्री हटवून सुरुवात करा.

1. रिकाम्या `processPredictions` फंक्शनमध्ये खालील कोड जोडा:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    हा कोड ओव्हरलॅप न करणाऱ्या भाकीत साठवण्यासाठी एक व्हेक्टर घोषित करतो. त्यानंतर सर्व भाकीतांमधून लूप करतो, बॉक्सिंग बॉक्समधून `Rect` तयार करतो.

    पुढे, हा कोड उर्वरित भाकीतांमधून लूप करतो, सध्याच्या भाकीतानंतर सुरू होतो. यामुळे भाकीत एकापेक्षा जास्त वेळा तुलना होण्यापासून थांबते - एकदा 1 आणि 2 ची तुलना झाली की, 2 ची 1 सोबत तुलना करण्याची गरज नाही, फक्त 3, 4, इत्यादींसोबत.

    प्रत्येक भाकीत जोडीत ओव्हरलॅपिंग क्षेत्रफळ गणना केली जाते. त्यानंतर हे सर्वात लहान बॉक्सिंग बॉक्सच्या क्षेत्रफळाशी तुलना केले जाते - जर ओव्हरलॅप बॉक्सिंग बॉक्सच्या दिलेल्या टक्केवारीपेक्षा जास्त असेल, तर भाकीत पास झालेले नाही असे चिन्हांकित केले जाते. जर सर्व ओव्हरलॅप्सची तुलना केल्यानंतर भाकीत तपास पास करत असेल, तर ते `passed_predictions` संग्रहात जोडले जाते.

    > 💁 हे ओव्हरलॅप्स काढून टाकण्याचा अतिशय साधा मार्ग आहे, फक्त ओव्हरलॅपिंग जोडीत पहिला काढून टाकणे. उत्पादन कोडसाठी, तुम्हाला येथे अधिक लॉजिक ठेवायचे असेल, जसे की अनेक वस्तूंच्या ओव्हरलॅप्सचा विचार करणे, किंवा एक बॉक्सिंग बॉक्स दुसऱ्याने समाविष्ट केला असल्यास.

1. यानंतर, पास झालेल्या भाकीतांचा तपशील सीरियल मॉनिटरवर पाठवण्यासाठी खालील कोड जोडा:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    हा कोड पास झालेल्या भाकीतांमधून लूप करतो आणि त्यांचा तपशील सीरियल मॉनिटरवर प्रिंट करतो.

1. याखाली, मोजलेल्या वस्तूंची संख्या सीरियल मॉनिटरवर प्रिंट करण्यासाठी कोड जोडा:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    हे नंतर IoT सेवेला पाठवले जाऊ शकते, जेणेकरून स्टॉक स्तर कमी असल्यास अलर्ट पाठवता येईल.

1. तुमचा कोड अपलोड करा आणि चालवा. शेल्फवरील वस्तूंवर कॅमेरा पॉइंट करा आणि C बटण दाबा. `overlap_threshold` मूल्य समायोजित करून भाकीत दुर्लक्षित होत असल्याचे पहा.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 तुम्ही हा कोड [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुमचा स्टॉक काउंटर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील मूळ दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.