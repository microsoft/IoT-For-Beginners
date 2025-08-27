<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T10:44:35+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "ne"
}
-->
# IoT Edge आधारित छवि वर्गीकरणकर्ता प्रयोग गरेर छवि वर्गीकरण गर्नुहोस् - भर्चुअल IoT हार्डवेयर र रास्पबेरी पाई

यस पाठको यस भागमा, तपाईं IoT Edge उपकरणमा चलिरहेको छवि वर्गीकरणकर्ता प्रयोग गर्नुहुनेछ।

## IoT Edge वर्गीकरणकर्ता प्रयोग गर्नुहोस्

IoT उपकरणलाई IoT Edge छवि वर्गीकरणकर्ता प्रयोग गर्न पुनःनिर्देशित गर्न सकिन्छ। छवि वर्गीकरणकर्ताको URL `http://<IP address or name>/image` हो, जहाँ `<IP address or name>` लाई IoT Edge चलिरहेको कम्प्युटरको IP ठेगाना वा होस्ट नामले प्रतिस्थापन गर्नुपर्छ।

Custom Vision को लागि Python लाइब्रेरी केवल क्लाउड-होस्ट गरिएको मोडेलहरूसँग काम गर्दछ, IoT Edge मा होस्ट गरिएको मोडेलहरूसँग काम गर्दैन। यसको मतलब तपाईंले वर्गीकरणकर्तालाई कल गर्न REST API प्रयोग गर्नुपर्नेछ।

### कार्य - IoT Edge वर्गीकरणकर्ता प्रयोग गर्नुहोस्

1. यदि `fruit-quality-detector` परियोजना VS Code मा खुला छैन भने यसलाई खोल्नुहोस्। यदि तपाईं भर्चुअल IoT उपकरण प्रयोग गर्दै हुनुहुन्छ भने, सुनिश्चित गर्नुहोस् कि भर्चुअल वातावरण सक्रिय छ।

1. `app.py` फाइल खोल्नुहोस्, र `azure.cognitiveservices.vision.customvision.prediction` र `msrest.authentication` बाट आयात कथनहरू हटाउनुहोस्।

1. फाइलको माथि निम्न आयात थप्नुहोस्:

    ```python
    import requests
    ```

1. छवि फाइलमा सुरक्षित भएपछि, `image_file.write(image.read())` बाट फाइलको अन्त्यसम्मको सबै कोड हटाउनुहोस्।

1. फाइलको अन्त्यमा निम्न कोड थप्नुहोस्:

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

    `<URL>` लाई तपाईंको वर्गीकरणकर्ताको URL ले प्रतिस्थापन गर्नुहोस्।

    यो कोडले वर्गीकरणकर्तालाई REST POST अनुरोध पठाउँछ, अनुरोधको शरीरको रूपमा छवि पठाउँदै। परिणामहरू JSON को रूपमा फर्किन्छन्, र यसलाई डिकोड गरेर सम्भावनाहरू प्रिन्ट गरिन्छ।

1. तपाईंको कोड चलाउनुहोस्, तपाईंको क्यामेरा फलफूलतर्फ देखाउँदै, उपयुक्त छवि सेट, वा भर्चुअल IoT हार्डवेयर प्रयोग गर्दा वेबक्याममा देखिने फलफूल। तपाईंले कन्सोलमा आउटपुट देख्नुहुनेछ:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 तपाईं यो कोड [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) वा [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको फलफूल गुणस्तर वर्गीकरणकर्ता कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।