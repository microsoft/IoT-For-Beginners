# भाषण अनुवाद गर्नुहोस् - भर्चुअल IoT उपकरण

यस पाठको यस भागमा, तपाईंले भाषण सेवाको प्रयोग गरेर भाषणलाई पाठमा रूपान्तरण गर्दा अनुवाद गर्ने कोड लेख्नुहुनेछ, त्यसपछि अनुवादक सेवाको प्रयोग गरेर पाठ अनुवाद गर्नुहोस् र अन्ततः बोलेको प्रतिक्रिया उत्पन्न गर्नुहोस्।

## भाषण सेवाको प्रयोग गरेर भाषण अनुवाद गर्नुहोस्

भाषण सेवा भाषणलाई पाठमा रूपान्तरण मात्र गर्दैन, तर यसले अन्य भाषाहरूमा पनि अनुवाद गर्न सक्छ।

### कार्य - भाषण सेवाको प्रयोग गरेर भाषण अनुवाद गर्नुहोस्

1. VS Code मा `smart-timer` प्रोजेक्ट खोल्नुहोस्, र टर्मिनलमा भर्चुअल वातावरण लोड भएको सुनिश्चित गर्नुहोस्।

1. तल दिइएको इम्पोर्ट स्टेटमेन्टहरू हाल्नुहोस्:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    यसले भाषण अनुवाद गर्न प्रयोग गरिने कक्षाहरू र `requests` लाइब्रेरीलाई इम्पोर्ट गर्दछ, जुन यस पाठमा पछि अनुवादक सेवामा कल गर्न प्रयोग गरिनेछ।

1. तपाईंको स्मार्ट टाइमरमा २ वटा भाषा सेट हुनेछ - LUIS लाई प्रशिक्षण दिन प्रयोग गरिएको सर्भरको भाषा (उही भाषा प्रयोगकर्तासँग बोल्नका लागि सन्देश बनाउन प्रयोग गरिन्छ), र प्रयोगकर्ताले बोलेको भाषा। `language` भेरिएबललाई प्रयोगकर्ताले बोल्ने भाषामा अपडेट गर्नुहोस्, र `server_language` नामक नयाँ भेरिएबल थप्नुहोस्, जुन LUIS लाई प्रशिक्षण दिन प्रयोग गरिएको भाषाको लागि हुनेछ:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` लाई तपाईंले बोल्ने भाषाको लोकेल नामले प्रतिस्थापन गर्नुहोस्, जस्तै फ्रेन्चको लागि `fr-FR`, वा क्यान्टोनिजको लागि `zn-HK`।

    `<server language>` लाई LUIS लाई प्रशिक्षण दिन प्रयोग गरिएको भाषाको लोकेल नामले प्रतिस्थापन गर्नुहोस्।

    तपाईं समर्थित भाषाहरू र तिनका लोकेल नामहरूको सूची [Microsoft Docs मा भाषा र आवाज समर्थन डकुमेन्टेसन](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मा पाउन सक्नुहुन्छ।

    > 💁 यदि तपाईंले धेरै भाषा बोल्नुहुन्न भने, तपाईं [Bing Translate](https://www.bing.com/translator) वा [Google Translate](https://translate.google.com) जस्ता सेवाहरू प्रयोग गर्न सक्नुहुन्छ। यी सेवाहरूले अनुवादित पाठको अडियो पनि बजाउन सक्छन्। ध्यान दिनुहोस् कि भाषण मान्यता प्रणालीले तपाईंको उपकरणबाट आउने केही अडियोलाई बेवास्ता गर्न सक्छ, त्यसैले अनुवादित पाठ बजाउन अर्को उपकरण प्रयोग गर्न आवश्यक पर्न सक्छ।
    >
    > उदाहरणका लागि, यदि तपाईंले LUIS लाई अंग्रेजीमा प्रशिक्षण दिनुभएको छ, तर प्रयोगकर्ता भाषाको रूपमा फ्रेन्च प्रयोग गर्न चाहनुहुन्छ भने, तपाईं "set a 2 minute and 27 second timer" जस्ता वाक्यहरूलाई Bing Translate प्रयोग गरेर अंग्रेजीबाट फ्रेन्चमा अनुवाद गर्न सक्नुहुन्छ, त्यसपछि **Listen translation** बटन प्रयोग गरेर अनुवादलाई तपाईंको माइक्रोफोनमा बोल्न सक्नुहुन्छ।
    >
    > ![Bing Translate मा Listen translation बटन](../../../../../translated_images/ne/bing-translate.348aa796d6efe2a9.webp)

1. `recognizer_config` र `recognizer` घोषणाहरूलाई निम्नसँग प्रतिस्थापन गर्नुहोस्:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    यसले प्रयोगकर्ता भाषामा भाषण चिन्न र प्रयोगकर्ता र सर्भर भाषामा अनुवाद सिर्जना गर्न अनुवाद कन्फिग बनाउँछ। त्यसपछि यो कन्फिग प्रयोग गरेर अनुवाद मान्यता प्रणाली बनाउँछ - यस्तो भाषण मान्यता प्रणाली जसले भाषण मान्यता प्रणालीको आउटपुटलाई धेरै भाषाहरूमा अनुवाद गर्न सक्छ।

    > 💁 मूल भाषा `target_languages` मा निर्दिष्ट गर्न आवश्यक छ, अन्यथा तपाईंले कुनै अनुवाद प्राप्त गर्नुहुनेछैन।

1. `recognized` फंक्शनलाई अपडेट गर्नुहोस्, फंक्शनको सम्पूर्ण सामग्रीलाई निम्नसँग प्रतिस्थापन गर्नुहोस्:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    यो कोडले जाँच गर्दछ कि मान्यता प्राप्त इभेन्ट भाषण अनुवाद गरिएको कारणले फायर भएको हो कि होइन (यो इभेन्ट अन्य समयमा पनि फायर हुन सक्छ, जस्तै भाषण मान्यता प्राप्त भए पनि अनुवाद नगरिएको अवस्थामा)। यदि भाषण अनुवाद गरिएको छ भने, यो `args.result.translations` डिक्सनरीमा सर्भर भाषासँग मेल खाने अनुवाद फेला पार्छ।

    `args.result.translations` डिक्सनरी लोकेल सेटिङको सम्पूर्ण भाग होइन, भाषाको भागमा आधारित हुन्छ। उदाहरणका लागि, यदि तपाईंले फ्रेन्चको लागि `fr-FR` मा अनुवाद अनुरोध गर्नुभयो भने, डिक्सनरीमा `fr` को लागि इन्ट्री हुनेछ, `fr-FR` को लागि होइन।

    अनुवादित पाठलाई IoT हबमा पठाइन्छ।

1. यो कोड चलाउनुहोस् र अनुवाद परीक्षण गर्नुहोस्। सुनिश्चित गर्नुहोस् कि तपाईंको फंक्शन एप चलिरहेको छ, र प्रयोगकर्ता भाषामा टाइमर अनुरोध गर्नुहोस्, चाहे आफैंले त्यो भाषा बोलेर, वा अनुवाद एप प्रयोग गरेर।

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## अनुवादक सेवाको प्रयोग गरेर पाठ अनुवाद गर्नुहोस्

भाषण सेवाले पाठलाई पुनः भाषणमा अनुवाद गर्न समर्थन गर्दैन, यसको सट्टा तपाईं अनुवादक सेवाको प्रयोग गरेर पाठ अनुवाद गर्न सक्नुहुन्छ। यस सेवाको REST API प्रयोग गरेर पाठ अनुवाद गर्न सकिन्छ।

### कार्य - अनुवादक स्रोतको प्रयोग गरेर पाठ अनुवाद गर्नुहोस्

1. `speech_api_key` को तल अनुवादक API कुञ्जी थप्नुहोस्:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` लाई तपाईंको अनुवादक सेवा स्रोतको API कुञ्जीले प्रतिस्थापन गर्नुहोस्।

1. `say` फंक्शनको माथि, `translate_text` नामक फंक्शन परिभाषित गर्नुहोस्, जसले सर्भर भाषाबाट प्रयोगकर्ता भाषामा पाठ अनुवाद गर्नेछ:

    ```python
    def translate_text(text):
    ```

1. यस फंक्शनभित्र, REST API कलको लागि URL र हेडरहरू परिभाषित गर्नुहोस्:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    यस API को URL स्थान-विशिष्ट छैन, यसको सट्टा स्थान हेडरको रूपमा पास गरिन्छ। API कुञ्जी सिधै प्रयोग गरिन्छ, त्यसैले भाषण सेवाको जस्तो टोकन जारीकर्ता API बाट पहुँच टोकन प्राप्त गर्न आवश्यक छैन।

1. यसको तल, कलको लागि प्यारामिटर र बडी परिभाषित गर्नुहोस्:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` ले API कलमा पास गरिने प्यारामिटरहरू परिभाषित गर्दछ, जसले `from` र `to` भाषाहरू पास गर्दछ। यो कलले `from` भाषामा रहेको पाठलाई `to` भाषामा अनुवाद गर्नेछ।

    `body` ले अनुवाद गर्नुपर्ने पाठ समावेश गर्दछ। यो एरे हो, किनभने एउटै कलमा धेरै पाठ ब्लकहरू अनुवाद गर्न सकिन्छ।

1. REST API कल गर्नुहोस्, र प्रतिक्रिया प्राप्त गर्नुहोस्:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    प्रतिक्रिया JSON एरेको रूपमा फर्किन्छ, जसमा एउटा वस्तु हुन्छ जसले अनुवादहरू समावेश गर्दछ। यस वस्तुमा बडीमा पास गरिएका सबै वस्तुहरूको अनुवादहरूको लागि एरे हुन्छ।

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. पहिलो वस्तुमा पहिलो अनुवादको `text` प्रोपर्टी फर्काउनुहोस्:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `say` फंक्शनलाई अपडेट गर्नुहोस्, SSML उत्पन्न गर्नु अघि भन्नुपर्ने पाठ अनुवाद गर्न:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    यस कोडले कन्सोलमा मूल र अनुवादित पाठको संस्करण पनि प्रिन्ट गर्दछ।

1. तपाईंको कोड चलाउनुहोस्। सुनिश्चित गर्नुहोस् कि तपाईंको फंक्शन एप चलिरहेको छ, र प्रयोगकर्ता भाषामा टाइमर अनुरोध गर्नुहोस्, चाहे आफैंले त्यो भाषा बोलेर, वा अनुवाद एप प्रयोग गरेर।

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 विभिन्न भाषाहरूमा केही कुरा भन्नका लागि फरक तरिकाहरू हुने भएकाले, तपाईंले LUIS लाई दिएको उदाहरणहरूसँग अलिक फरक अनुवादहरू प्राप्त गर्न सक्नुहुन्छ। यदि यस्तो छ भने, LUIS मा थप उदाहरणहरू थप्नुहोस्, पुनः प्रशिक्षण गर्नुहोस्, र मोडेल पुनः प्रकाशित गर्नुहोस्।

> 💁 तपाईं यो कोड [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको बहुभाषिक टाइमर कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।