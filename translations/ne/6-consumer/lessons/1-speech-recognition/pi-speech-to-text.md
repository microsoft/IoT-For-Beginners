<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T14:23:16+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "ne"
}
-->
# भाषणलाई पाठमा रूपान्तरण - रास्पबेरी पाई

यस पाठको यस भागमा, तपाईंले कब्जा गरिएको अडियोमा रहेको भाषणलाई पाठमा रूपान्तरण गर्न कोड लेख्नुहुनेछ, भाषण सेवाको प्रयोग गरेर।

## अडियोलाई भाषण सेवामा पठाउनुहोस्

अडियोलाई भाषण सेवामा REST API प्रयोग गरेर पठाउन सकिन्छ। भाषण सेवा प्रयोग गर्नको लागि, पहिलो चरणमा तपाईंले पहुँच टोकन अनुरोध गर्नुपर्छ, त्यसपछि उक्त टोकन प्रयोग गरेर REST API पहुँच गर्न सकिन्छ। यी पहुँच टोकनहरू १० मिनेटपछि समाप्त हुन्छन्, त्यसैले तपाईंको कोडले नियमित रूपमा टोकन अनुरोध गर्नुपर्छ ताकि टोकन सधैं अद्यावधिक रहोस्।

### कार्य - पहुँच टोकन प्राप्त गर्नुहोस्

1. आफ्नो पाईमा `smart-timer` प्रोजेक्ट खोल्नुहोस्।

1. `play_audio` फङ्सन हटाउनुहोस्। यो अब आवश्यक छैन किनभने तपाईं चाहनुहुन्न कि स्मार्ट टाइमरले तपाईंले भनेको कुरा दोहोर्याओस्।

1. `app.py` फाइलको माथि निम्न इम्पोर्ट थप्नुहोस्:

    ```python
    import requests
    ```

1. `while True` लूपको माथि निम्न कोड थप्नुहोस्, भाषण सेवाको सेटिङहरू घोषणा गर्न:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>` लाई आफ्नो भाषण सेवा स्रोतको API कुञ्जीले प्रतिस्थापन गर्नुहोस्। `<location>` लाई तपाईंले भाषण सेवा स्रोत सिर्जना गर्दा प्रयोग गरेको स्थानले प्रतिस्थापन गर्नुहोस्।

    `<language>` लाई तपाईंले बोल्ने भाषाको लोकेल नामले प्रतिस्थापन गर्नुहोस्, जस्तै अंग्रेजीको लागि `en-GB`, वा क्यान्टोनिजको लागि `zn-HK`। समर्थित भाषाहरू र तिनका लोकेल नामहरूको सूची [Microsoft Docs मा भाषा र आवाज समर्थन दस्तावेज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मा पाउन सकिन्छ।

1. यसको तल, पहुँच टोकन प्राप्त गर्न निम्न फङ्सन थप्नुहोस्:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    यो टोकन जारी गर्ने अन्त बिन्दुलाई कल गर्दछ, API कुञ्जीलाई हेडरको रूपमा पास गर्दै। यो कलले पहुँच टोकन फर्काउँछ, जुन भाषण सेवाहरू कल गर्न प्रयोग गर्न सकिन्छ।

1. यसको तल, REST API प्रयोग गरेर कब्जा गरिएको अडियोमा रहेको भाषणलाई पाठमा रूपान्तरण गर्न फङ्सन घोषणा गर्नुहोस्:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. यस फङ्सनभित्र, REST API URL र हेडर सेट गर्नुहोस्:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    यो URL निर्माण गर्दछ, भाषण सेवाको स्रोतको स्थान प्रयोग गरेर। त्यसपछि यो हेडरहरू `get_access_token` फङ्सनबाट प्राप्त गरिएको पहुँच टोकन, अडियो कब्जा गर्न प्रयोग गरिएको स्याम्पल दर, र URL सँग पास गरिने भाषाको विवरणले भरिन्छ।

1. यसको तल, REST API कल गर्न र पाठ फिर्ता प्राप्त गर्न निम्न कोड थप्नुहोस्:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    यो URL कल गर्दछ र प्रतिक्रिया भित्र आएको JSON मानलाई डिकोड गर्दछ। प्रतिक्रिया भित्रको `RecognitionStatus` मानले कलले भाषणलाई सफलतापूर्वक पाठमा रूपान्तरण गर्न सकेको छ कि छैन भन्ने संकेत गर्दछ। यदि यो `Success` हो भने पाठ फङ्सनबाट फिर्ता हुन्छ, अन्यथा खाली स्ट्रिङ फिर्ता हुन्छ।

1. `while True:` लूपको माथि, भाषणलाई पाठ सेवाबाट फिर्ता आएको पाठलाई प्रक्रिया गर्न फङ्सन परिभाषित गर्नुहोस्। यो फङ्सनले हाललाई पाठलाई कन्सोलमा प्रिन्ट मात्र गर्नेछ।

    ```python
    def process_text(text):
        print(text)
    ```

1. अन्ततः `while True` लूपमा `play_audio` कललाई `convert_speech_to_text` फङ्सनको कलले प्रतिस्थापन गर्नुहोस्, पाठलाई `process_text` फङ्सनमा पास गर्दै:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. कोड चलाउनुहोस्। बटन थिच्नुहोस् र माइक्रोफोनमा बोल्नुहोस्। तपाईं सकिएपछि बटन छोड्नुहोस्, र अडियो पाठमा रूपान्तरण हुनेछ र कन्सोलमा प्रिन्ट हुनेछ।

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    विभिन्न प्रकारका वाक्यहरू प्रयास गर्नुहोस्, साथै त्यस्ता वाक्यहरू जहाँ शब्दहरू उस्तै सुनिन्छ तर अर्थ फरक हुन्छ। उदाहरणका लागि, यदि तपाईं अंग्रेजीमा बोल्दै हुनुहुन्छ भने, 'I want to buy two bananas and an apple too' भन्नुहोस्, र यसले शब्दको ध्वनिमा मात्र होइन, सन्दर्भको आधारमा सही to, two, र too प्रयोग गरेको देख्नुहोस्।

> 💁 तपाईं यो कोड [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको भाषणलाई पाठमा रूपान्तरण गर्ने प्रोग्राम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।