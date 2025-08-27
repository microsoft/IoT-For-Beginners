<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T14:10:39+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "ne"
}
-->
# भाषणलाई पाठमा रूपान्तरण गर्ने - भर्चुअल IoT उपकरण

यस पाठको यस भागमा, तपाईंले आफ्नो माइक्रोफोनबाट क्याप्चर गरिएको भाषणलाई भाषण सेवाको प्रयोग गरेर पाठमा रूपान्तरण गर्न कोड लेख्नुहुनेछ।

## भाषणलाई पाठमा रूपान्तरण गर्नुहोस्

Windows, Linux, र macOS मा, भाषण सेवाहरूको Python SDK प्रयोग गरेर तपाईंको माइक्रोफोन सुन्न र पत्ता लागेको भाषणलाई पाठमा रूपान्तरण गर्न सकिन्छ। यो निरन्तर सुन्छ, अडियो स्तरहरू पत्ता लगाउँछ र जब अडियो स्तर घट्छ, जस्तै भाषणको ब्लकको अन्त्यमा, भाषणलाई पाठमा रूपान्तरण गर्न पठाउँछ।

### कार्य - भाषणलाई पाठमा रूपान्तरण गर्नुहोस्

1. `smart-timer` नामको फोल्डरमा आफ्नो कम्प्युटरमा नयाँ Python एप बनाउनुहोस्, जसमा `app.py` नामको एकल फाइल र Python भर्चुअल वातावरण हुनेछ।

1. भाषण सेवाहरूको लागि Pip प्याकेज स्थापना गर्नुहोस्। सुनिश्चित गर्नुहोस् कि तपाईंले यो भर्चुअल वातावरण सक्रिय भएको टर्मिनलबाट स्थापना गर्दै हुनुहुन्छ।

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ यदि तपाईंले निम्न त्रुटि पाउनुभयो:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > तपाईंले Pip अपडेट गर्न आवश्यक छ। निम्न कमाण्ड प्रयोग गरेर यो गर्नुहोस्, त्यसपछि प्याकेज पुन: स्थापना प्रयास गर्नुहोस्।
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py` फाइलमा निम्न इम्पोर्टहरू थप्नुहोस्:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    यसले भाषण पहिचान गर्न प्रयोग गरिने केही कक्षहरू इम्पोर्ट गर्दछ।

1. केही कन्फिगरेसन घोषणा गर्न निम्न कोड थप्नुहोस्:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>` लाई तपाईंको भाषण सेवाको API कुञ्जीले प्रतिस्थापन गर्नुहोस्। `<location>` लाई तपाईंले भाषण सेवा स्रोत सिर्जना गर्दा प्रयोग गरेको स्थानले प्रतिस्थापन गर्नुहोस्।

    `<language>` लाई तपाईं बोल्ने भाषाको लोकेल नामले प्रतिस्थापन गर्नुहोस्, जस्तै अंग्रेजीको लागि `en-GB`, वा क्यान्टोनिजको लागि `zn-HK`। Microsoft Docs मा [भाषा र आवाज समर्थनको दस्तावेज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मा समर्थित भाषाहरू र तिनीहरूको लोकेल नामहरूको सूची पाउन सकिन्छ।

    यो कन्फिगरेसनले `SpeechConfig` वस्तु सिर्जना गर्न प्रयोग गरिन्छ, जसले भाषण सेवाहरूलाई कन्फिगर गर्दछ।

1. भाषण पहिचानकर्ता सिर्जना गर्न निम्न कोड थप्नुहोस्:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. भाषण पहिचानकर्ता पृष्ठभूमि थ्रेडमा चल्छ, अडियो सुन्छ र त्यसमा रहेको भाषणलाई पाठमा रूपान्तरण गर्दछ। तपाईंले पाठलाई एक कलब्याक फङ्क्शन प्रयोग गरेर प्राप्त गर्न सक्नुहुन्छ - एक फङ्क्शन जुन तपाईं परिभाषित गर्नुहुन्छ र पहिचानकर्तालाई पास गर्नुहुन्छ। हरेक पटक भाषण पत्ता लाग्दा, कलब्याकलाई बोलाइन्छ। निम्न कोड थप्नुहोस् कलब्याक परिभाषित गर्न, र यसलाई पहिचानकर्तामा पास गर्न, साथै पाठलाई प्रक्रिया गर्न एक फङ्क्शन परिभाषित गर्न, जसले कन्सोलमा लेख्छ:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. पहिचानकर्ता केवल तपाईंले स्पष्ट रूपमा सुरु गर्दा सुन्न सुरु गर्दछ। पहिचान सुरु गर्न निम्न कोड थप्नुहोस्। यो पृष्ठभूमिमा चल्छ, त्यसैले तपाईंको एप्लिकेसनलाई चलिराख्नको लागि सुत्ने अनन्त लूप पनि आवश्यक हुनेछ।

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. यो एप चलाउनुहोस्। आफ्नो माइक्रोफोनमा बोल्नुहोस् र अडियो पाठमा रूपान्तरण भएर कन्सोलमा आउटपुट हुनेछ।

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    विभिन्न प्रकारका वाक्यहरू प्रयास गर्नुहोस्, साथै त्यस्ता वाक्यहरू जहाँ शब्दहरू उस्तै सुनिन्छ तर तिनीहरूको अर्थ फरक हुन्छ। उदाहरणका लागि, यदि तपाईं अंग्रेजीमा बोल्दै हुनुहुन्छ भने, 'I want to buy two bananas and an apple too' भन्नुहोस्, र यसले शब्दको ध्वनिमा मात्र होइन, सन्दर्भको आधारमा सही to, two, र too प्रयोग गरेको देख्नुहोस्।

> 💁 तपाईंले यो कोड [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको भाषणलाई पाठमा रूपान्तरण गर्ने कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषामा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।