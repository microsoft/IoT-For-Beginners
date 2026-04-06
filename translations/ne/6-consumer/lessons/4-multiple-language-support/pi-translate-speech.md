# भाषण अनुवाद गर्नुहोस् - रास्पबेरी पाई

यस पाठको यस भागमा, तपाईं अनुवादक सेवाको प्रयोग गरेर पाठ अनुवाद गर्न कोड लेख्नुहुनेछ।

## अनुवादक सेवाको प्रयोग गरेर पाठलाई भाषणमा रूपान्तरण गर्नुहोस्

स्पीच सेवा REST API ले प्रत्यक्ष अनुवादलाई समर्थन गर्दैन, यसको सट्टा तपाईंले स्पीच टु टेक्स्ट सेवाबाट उत्पन्न पाठ र बोलेको प्रतिक्रियाको पाठ अनुवाद गर्न अनुवादक सेवाको प्रयोग गर्न सक्नुहुन्छ। यो सेवाले पाठ अनुवाद गर्न प्रयोग गर्न सकिने REST API प्रदान गर्दछ।

### कार्य - अनुवादक स्रोत प्रयोग गरेर पाठ अनुवाद गर्नुहोस्

1. तपाईंको स्मार्ट टाइमरमा २ भाषा सेट हुनेछ - LUIS लाई प्रशिक्षण दिन प्रयोग गरिएको सर्भरको भाषा (उही भाषा प्रयोगकर्तासँग बोल्नका लागि सन्देश निर्माण गर्न पनि प्रयोग गरिन्छ), र प्रयोगकर्ताले बोलेको भाषा। `language` भेरिएबललाई प्रयोगकर्ताले बोल्ने भाषामा अपडेट गर्नुहोस्, र LUIS लाई प्रशिक्षण दिन प्रयोग गरिएको भाषाका लागि `server_language` नामक नयाँ भेरिएबल थप्नुहोस्:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` लाई तपाईं बोल्ने भाषाको लोकेल नामले प्रतिस्थापन गर्नुहोस्, जस्तै फ्रेन्चका लागि `fr-FR`, वा क्यान्टोनिजका लागि `zn-HK`।

    `<server language>` लाई LUIS लाई प्रशिक्षण दिन प्रयोग गरिएको भाषाको लोकेल नामले प्रतिस्थापन गर्नुहोस्।

    तपाईं समर्थित भाषाहरू र तिनीहरूको लोकेल नामहरूको सूची [Microsoft Docs मा भाषा र आवाज समर्थन दस्तावेज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मा पाउन सक्नुहुन्छ।

    > 💁 यदि तपाईं बहुभाषी हुनुहुन्न भने, तपाईं आफ्नो मनपर्ने भाषाबाट कुनै पनि भाषामा अनुवाद गर्न [Bing Translate](https://www.bing.com/translator) वा [Google Translate](https://translate.google.com) जस्ता सेवाहरू प्रयोग गर्न सक्नुहुन्छ। यी सेवाहरूले अनुवाद गरिएको पाठको अडियो पनि बजाउन सक्छन्।
    >
    > उदाहरणका लागि, यदि तपाईंले LUIS लाई अंग्रेजीमा प्रशिक्षण दिनुभयो भने, तर प्रयोगकर्ता भाषाको रूपमा फ्रेन्च प्रयोग गर्न चाहनुहुन्छ भने, तपाईं "set a 2 minute and 27 second timer" जस्ता वाक्यहरूलाई Bing Translate प्रयोग गरेर अंग्रेजीबाट फ्रेन्चमा अनुवाद गर्न सक्नुहुन्छ, त्यसपछि **Listen translation** बटन प्रयोग गरेर अनुवादलाई आफ्नो माइक्रोफोनमा बोल्न सक्नुहुन्छ।
    >
    > ![Bing Translate मा Listen translation बटन](../../../../../translated_images/ne/bing-translate.348aa796d6efe2a9.webp)

1. `speech_api_key` को तल अनुवादक API कुञ्जी थप्नुहोस्:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` लाई तपाईंको अनुवादक सेवा स्रोतको API कुञ्जीले प्रतिस्थापन गर्नुहोस्।

1. `say` फङ्सनको माथि, `translate_text` नामक फङ्सन परिभाषित गर्नुहोस्, जसले सर्भर भाषाबाट प्रयोगकर्ता भाषामा पाठ अनुवाद गर्नेछ:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    यो फङ्सनमा `from` र `to` भाषाहरू पास गरिन्छ - तपाईंको एपले भाषण चिन्न प्रयोगकर्ता भाषाबाट सर्भर भाषामा रूपान्तरण गर्नुपर्छ, र बोलेको प्रतिक्रिया प्रदान गर्दा सर्भर भाषाबाट प्रयोगकर्ता भाषामा रूपान्तरण गर्नुपर्छ।

1. यो फङ्सनभित्र, REST API कलको लागि URL र हेडरहरू परिभाषित गर्नुहोस्:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    यो API को URL स्थान-विशिष्ट छैन, यसको सट्टा स्थान हेडरको रूपमा पास गरिन्छ। API कुञ्जी सिधै प्रयोग गरिन्छ, त्यसैले स्पीच सेवाको विपरीत, टोकन जारीकर्ता API बाट पहुँच टोकन प्राप्त गर्न आवश्यक छैन।

1. यसको तल, कलको लागि प्यारामिटर र बडी परिभाषित गर्नुहोस्:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` ले API कलमा पास गर्नुपर्ने प्यारामिटरहरू परिभाषित गर्दछ, `from` र `to` भाषाहरू पास गर्दै। यो कलले `from` भाषामा रहेको पाठलाई `to` भाषामा अनुवाद गर्नेछ।

    `body` ले अनुवाद गर्नुपर्ने पाठ समावेश गर्दछ। यो एउटा एरे हो, किनभने एउटै कलमा धेरै पाठ ब्लकहरू अनुवाद गर्न सकिन्छ।

1. REST API कल गर्नुहोस्, र प्रतिक्रिया प्राप्त गर्नुहोस्:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    फर्किएको प्रतिक्रिया एउटा JSON एरे हो, जसमा एउटा वस्तु हुन्छ जसले अनुवादहरू समावेश गर्दछ। यस वस्तुमा बडीमा पास गरिएका सबै वस्तुहरूको अनुवादहरूको लागि एउटा एरे हुन्छ।

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. एरेको पहिलो वस्तुबाट पहिलो अनुवादको `test` प्रोपर्टी फर्काउनुहोस्:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` लूपलाई प्रयोगकर्ता भाषाबाट सर्भर भाषामा `convert_speech_to_text` कलको पाठ अनुवाद गर्न अपडेट गर्नुहोस्:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    यस कोडले मूल र अनुवादित पाठलाई कन्सोलमा पनि प्रिन्ट गर्दछ।

1. `say` फङ्सनलाई सर्भर भाषाबाट प्रयोगकर्ता भाषामा भन्नुपर्ने पाठ अनुवाद गर्न अपडेट गर्नुहोस्:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    यस कोडले मूल र अनुवादित पाठलाई कन्सोलमा पनि प्रिन्ट गर्दछ।

1. तपाईंको कोड चलाउनुहोस्। सुनिश्चित गर्नुहोस् कि तपाईंको फङ्सन एप चलिरहेको छ, र प्रयोगकर्ता भाषामा टाइमर अनुरोध गर्नुहोस्, चाहे आफैंले त्यो भाषा बोल्दै, वा अनुवाद एप प्रयोग गरेर।

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 विभिन्न भाषाहरूमा केही कुरा भन्नका लागि फरक तरिकाहरू भएका कारण, तपाईंले LUIS लाई दिएको उदाहरणहरू भन्दा अलि फरक अनुवादहरू प्राप्त गर्न सक्नुहुन्छ। यदि यस्तो छ भने, LUIS मा थप उदाहरणहरू थप्नुहोस्, पुन: प्रशिक्षण गर्नुहोस्, र मोडेल पुन: प्रकाशित गर्नुहोस्।

> 💁 तपाईं यो कोड [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको बहुभाषी टाइमर कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको हो। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।