# छवि वर्गीकरण गर्नुहोस् - भर्चुअल IoT हार्डवेयर र रास्पबेरी पाई

यस पाठको यस भागमा, तपाईंले क्यामेराले खिचेको छवि Custom Vision सेवामा पठाएर वर्गीकरण गर्नुहुनेछ।

## Custom Vision मा छविहरू पठाउनुहोस्

Custom Vision सेवामा छविहरू वर्गीकरण गर्न Python SDK उपलब्ध छ, जसलाई तपाईं प्रयोग गर्न सक्नुहुन्छ।

### कार्य - Custom Vision मा छविहरू पठाउनुहोस्

1. VS Code मा `fruit-quality-detector` फोल्डर खोल्नुहोस्। यदि तपाईं भर्चुअल IoT उपकरण प्रयोग गर्दै हुनुहुन्छ भने, टर्मिनलमा भर्चुअल वातावरण चलिरहेको छ भनेर सुनिश्चित गर्नुहोस्।

1. Custom Vision मा छविहरू पठाउन Python SDK Pip प्याकेजको रूपमा उपलब्ध छ। यसलाई निम्न आदेश प्रयोग गरेर इन्स्टल गर्नुहोस्:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` फाइलको माथिल्लो भागमा निम्न इम्पोर्ट स्टेटमेन्टहरू थप्नुहोस्:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    यसले Custom Vision पुस्तकालयका केही मोड्युलहरू ल्याउँछ, जसमा भविष्यवाणी कुञ्जीको साथ प्रमाणिकरण गर्न र Custom Vision कल गर्न सक्ने भविष्यवाणी क्लाइन्ट वर्ग प्रदान गर्न समावेश छ।

1. फाइलको अन्त्यमा निम्न कोड थप्नुहोस्:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>` लाई यस पाठको पहिलेको *Prediction URL* संवादबाट प्रतिलिपि गरिएको URL ले प्रतिस्थापन गर्नुहोस्। `<prediction key>` लाई सोही संवादबाट प्रतिलिपि गरिएको भविष्यवाणी कुञ्जीले प्रतिस्थापन गर्नुहोस्।

1. *Prediction URL* संवादले प्रदान गरेको भविष्यवाणी URL सिधै REST अन्तर्क्रियामा कल गर्दा प्रयोग गर्न डिजाइन गरिएको हो। Python SDK ले URL का केही भागहरू फरक ठाउँमा प्रयोग गर्दछ। यो URL टुक्र्याउन निम्न कोड थप्नुहोस्:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    यसले URL लाई टुक्र्याउँछ, `https://<location>.api.cognitive.microsoft.com` को अन्तर्क्रियालाई, प्रोजेक्ट ID, र प्रकाशित संस्करणको नाम निकाल्छ।

1. भविष्यवाणी गर्न predictor वस्तु निम्न कोड प्रयोग गरेर सिर्जना गर्नुहोस्:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` ले भविष्यवाणी कुञ्जीलाई समेट्छ। यी अन्तर्क्रियामा संकेत गर्ने भविष्यवाणी क्लाइन्ट वस्तु सिर्जना गर्न प्रयोग गरिन्छ।

1. निम्न कोड प्रयोग गरेर छवि Custom Vision मा पठाउनुहोस्:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    यसले छविलाई सुरुमा फर्काउँछ, त्यसपछि भविष्यवाणी क्लाइन्टमा पठाउँछ।

1. अन्ततः, परिणामहरू निम्न कोड प्रयोग गरेर देखाउनुहोस्:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    यसले फर्काइएका सबै भविष्यवाणीहरूमा लूप गर्छ र टर्मिनलमा देखाउँछ। फर्काइएका सम्भावनाहरू 0-1 को फ्लोटिङ पोइन्ट नम्बरहरू हुन्छन्, जहाँ 0 ले 0% सम्भावना जनाउँछ र 1 ले 100% सम्भावना जनाउँछ।

    > 💁 छवि वर्गीकरणकर्ताहरूले प्रयोग गरिएका सबै ट्यागहरूको प्रतिशत फर्काउँछन्। प्रत्येक ट्यागसँग छविले सो ट्यागसँग मेल खाने सम्भावना हुन्छ।

1. आफ्नो कोड चलाउनुहोस्, क्यामेरा फलतिर संकेत गर्दै, वा उपयुक्त छवि सेट, वा भर्चुअल IoT हार्डवेयर प्रयोग गर्दा वेबक्याममा देखिने फल। तपाईंले कन्सोलमा आउटपुट देख्नुहुनेछ:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    तपाईंले खिचिएको छवि देख्न सक्नुहुनेछ, र यी मानहरू Custom Vision को **Predictions** ट्याबमा देख्न सक्नुहुनेछ।

    ![Custom Vision मा एउटा केरा, 56.8% मा पाको र 43.1% मा काँचो भविष्यवाणी गरिएको](../../../../../translated_images/ne/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 तपाईंले यो कोड [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) वा [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंको फल गुणस्तर वर्गीकरणकर्ता कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।