<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T09:55:52+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ne"
}
-->
# तपाईंको IoT उपकरणबाट स्टक गणना गर्नुहोस् - Wio Terminal

पूर्वानुमानहरू र तिनका bounding boxes को संयोजन प्रयोग गरेर छविमा स्टक गणना गर्न सकिन्छ।

## स्टक गणना गर्नुहोस्

![टमाटर पेस्टका ४ क्यानहरू, प्रत्येक क्यान वरिपरि bounding boxes सहित](../../../../../translated_images/ne/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

माथिको छविमा देखाइएको छ, bounding boxes साना ओभरल्याप भएका छन्। यदि यो ओभरल्याप धेरै ठूलो हुन्थ्यो भने, bounding boxes ले एउटै वस्तु संकेत गर्न सक्थे। वस्तुहरू सही रूपमा गणना गर्न, तपाईंले महत्त्वपूर्ण ओभरल्याप भएका बक्सहरूलाई बेवास्ता गर्नुपर्छ।

### कार्य - ओभरल्याप बेवास्ता गर्दै स्टक गणना गर्नुहोस्

1. यदि तपाईंको `stock-counter` प्रोजेक्ट खुला छैन भने यसलाई खोल्नुहोस्।

1. `processPredictions` function भन्दा माथि, निम्न कोड थप्नुहोस्:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    यसले bounding boxes लाई एउटै वस्तु मान्नुअघि अनुमति दिइने ओभरल्यापको प्रतिशत परिभाषित गर्दछ। 0.20 ले 20% ओभरल्यापलाई परिभाषित गर्दछ।

1. यसको तल, र `processPredictions` function भन्दा माथि, दुई आयतहरू बीचको ओभरल्याप गणना गर्न निम्न कोड थप्नुहोस्:

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

    यो कोडले छविमा बिन्दुहरू भण्डारण गर्न `Point` struct परिभाषित गर्दछ, र शीर्ष बायाँ र तल्लो दायाँ निर्देशांक प्रयोग गरेर आयत परिभाषित गर्न `Rect` struct परिभाषित गर्दछ। त्यसपछि यसले शीर्ष बायाँ र तल्लो दायाँ निर्देशांकबाट आयतको क्षेत्रफल गणना गर्ने `area` function परिभाषित गर्दछ।

    त्यसपछि यसले २ आयतहरूको ओभरल्याप क्षेत्रफल गणना गर्ने `overlappingArea` function परिभाषित गर्दछ। यदि तिनीहरू ओभरल्याप गर्दैनन् भने, यो 0 फिर्ता गर्छ।

1. `overlappingArea` function को तल, bounding box लाई `Rect` मा रूपान्तरण गर्न function घोषणा गर्नुहोस्:

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

    यसले object detector बाट पूर्वानुमान लिन्छ, bounding box निकाल्छ र आयत परिभाषित गर्न bounding box का मानहरू प्रयोग गर्दछ। दायाँ पक्ष बायाँ प्लस चौडाइबाट गणना गरिन्छ। तल्लो भाग माथि प्लस उचाइबाट गणना गरिन्छ।

1. पूर्वानुमानहरू एकअर्कासँग तुलना गर्न आवश्यक छ, र यदि २ पूर्वानुमानहरूको ओभरल्याप threshold भन्दा बढी छ भने, तिनीहरूमध्ये एकलाई हटाउन आवश्यक छ। ओभरल्याप threshold प्रतिशत हो, त्यसैले यो सानो bounding box को आकारसँग गुणा गर्न आवश्यक छ ताकि ओभरल्यापले सम्पूर्ण छविको प्रतिशत होइन, bounding box को दिइएको प्रतिशत नाघेको छ कि छैन जाँच्न सकियोस्। `processPredictions` function को सामग्री मेटेर सुरु गर्नुहोस्।

1. खाली `processPredictions` function मा निम्न थप्नुहोस्:

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

    यो कोडले ओभरल्याप नगर्ने पूर्वानुमानहरू भण्डारण गर्न vector घोषणा गर्दछ। त्यसपछि यो सबै पूर्वानुमानहरूमा लुप्स गर्छ, bounding box बाट `Rect` सिर्जना गर्दै।

    त्यसपछि यो बाँकी पूर्वानुमानहरूमा लुप्स गर्छ, हालको पूर्वानुमानपछि सुरु गर्दै। यसले पूर्वानुमानहरूलाई एकपटकभन्दा बढी तुलना गर्न रोक्छ - एकपटक १ र २ तुलना भएपछि, २ लाई १ सँग तुलना गर्न आवश्यक छैन, केवल ३, ४, आदि सँग।

    प्रत्येक जोडीको पूर्वानुमानहरूको लागि ओभरल्याप क्षेत्रफल गणना गरिन्छ। त्यसपछि यो सानो bounding box को क्षेत्रफलसँग तुलना गरिन्छ - यदि ओभरल्यापले सानो bounding box को threshold प्रतिशत नाघ्छ भने, पूर्वानुमानलाई पास नगरेको रूपमा चिन्ह लगाइन्छ। यदि सबै ओभरल्याप तुलना गरेपछि, पूर्वानुमानले जाँचहरू पास गर्छ भने, यो `passed_predictions` संग्रहमा थपिन्छ।

    > 💁 यो ओभरल्याप हटाउने धेरै सरल तरिका हो, ओभरल्याप भएको जोडीमा पहिलोलाई मात्र हटाउने। उत्पादन कोडको लागि, तपाईंले यहाँ थप तर्क राख्न चाहनुहुनेछ, जस्तै धेरै वस्तुहरू बीचको ओभरल्याप विचार गर्नु, वा यदि एउटा bounding box अर्कोमा समावेश छ भने।

1. यसको पछि, serial monitor मा पास भएका पूर्वानुमानहरूको विवरण पठाउन निम्न कोड थप्नुहोस्:

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

    यो कोडले पास भएका पूर्वानुमानहरूमा लुप्स गर्छ र तिनका विवरणहरू serial monitor मा प्रिन्ट गर्छ।

1. यसको तल, serial monitor मा गणना गरिएका वस्तुहरूको संख्या प्रिन्ट गर्न कोड थप्नुहोस्:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    यसलाई IoT सेवामा पठाएर स्टक स्तर कम भएमा सतर्क गराउन सकिन्छ।

1. आफ्नो कोड अपलोड र चलाउनुहोस्। क्यामेरालाई शेल्फमा रहेका वस्तुहरूतर्फ सोझ्याउनुहोस् र C बटन थिच्नुहोस्। `overlap_threshold` मान समायोजन गरेर पूर्वानुमानहरू बेवास्ता भइरहेको हेर्न प्रयास गर्नुहोस्।

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

> 💁 तपाईंले यो कोड [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंको स्टक काउन्टर प्रोग्राम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।