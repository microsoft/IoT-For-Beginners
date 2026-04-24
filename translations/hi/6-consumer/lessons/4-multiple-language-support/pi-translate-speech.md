# भाषण का अनुवाद करें - रास्पबेरी पाई

इस पाठ के इस भाग में, आप अनुवादक सेवा का उपयोग करके टेक्स्ट का अनुवाद करने के लिए कोड लिखेंगे।

## अनुवादक सेवा का उपयोग करके टेक्स्ट को भाषण में बदलें

स्पीच सर्विस REST API सीधे अनुवाद का समर्थन नहीं करता है, इसके बजाय आप स्पीच टू टेक्स्ट सर्विस द्वारा उत्पन्न टेक्स्ट और बोले गए उत्तर के टेक्स्ट को अनुवाद करने के लिए अनुवादक सेवा का उपयोग कर सकते हैं। इस सेवा में एक REST API है जिसे आप टेक्स्ट का अनुवाद करने के लिए उपयोग कर सकते हैं।

### कार्य - अनुवादक संसाधन का उपयोग करके टेक्स्ट का अनुवाद करें

1. आपके स्मार्ट टाइमर में 2 भाषाएं सेट होंगी - सर्वर की भाषा जिसका उपयोग LUIS को प्रशिक्षित करने के लिए किया गया था (यह भाषा उपयोगकर्ता से बात करने के लिए संदेश बनाने के लिए भी उपयोग की जाती है), और उपयोगकर्ता द्वारा बोली जाने वाली भाषा। `language` वेरिएबल को अपडेट करें ताकि यह उपयोगकर्ता द्वारा बोली जाने वाली भाषा हो, और एक नया वेरिएबल `server_language` जोड़ें जो LUIS को प्रशिक्षित करने के लिए उपयोग की गई भाषा को दर्शाए:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` को उस भाषा के लोकेल नाम से बदलें जिसमें आप बोलेंगे, उदाहरण के लिए फ्रेंच के लिए `fr-FR`, या कैंटोनीज़ के लिए `zn-HK`।

    `<server language>` को उस भाषा के लोकेल नाम से बदलें जिसका उपयोग LUIS को प्रशिक्षित करने के लिए किया गया था।

    आप समर्थित भाषाओं और उनके लोकेल नामों की सूची [Microsoft Docs पर भाषा और आवाज़ समर्थन दस्तावेज़](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) में पा सकते हैं।

    > 💁 यदि आप कई भाषाएं नहीं बोलते हैं, तो आप [Bing Translate](https://www.bing.com/translator) या [Google Translate](https://translate.google.com) जैसे सेवा का उपयोग अपनी पसंदीदा भाषा से किसी अन्य भाषा में अनुवाद करने के लिए कर सकते हैं। ये सेवाएं अनुवादित टेक्स्ट का ऑडियो भी चला सकती हैं।
    >
    > उदाहरण के लिए, यदि आप LUIS को अंग्रेजी में प्रशिक्षित करते हैं, लेकिन उपयोगकर्ता भाषा के रूप में फ्रेंच का उपयोग करना चाहते हैं, तो आप "set a 2 minute and 27 second timer" जैसे वाक्य को Bing Translate का उपयोग करके अंग्रेजी से फ्रेंच में अनुवाद कर सकते हैं, फिर **Listen translation** बटन का उपयोग करके अनुवाद को अपने माइक्रोफोन में बोल सकते हैं।
    >
    > ![Bing Translate पर Listen translation बटन](../../../../../translated_images/hi/bing-translate.348aa796d6efe2a9.webp)

1. `speech_api_key` के नीचे अनुवादक API कुंजी जोड़ें:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` को अपने अनुवादक सेवा संसाधन के API कुंजी से बदलें।

1. `say` फ़ंक्शन के ऊपर, एक `translate_text` फ़ंक्शन परिभाषित करें जो सर्वर भाषा से उपयोगकर्ता भाषा में टेक्स्ट का अनुवाद करेगा:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    इस फ़ंक्शन में `from` और `to` भाषाएं पास की जाती हैं - आपका ऐप उपयोगकर्ता भाषा से सर्वर भाषा में भाषण को पहचानने के लिए और सर्वर भाषा से उपयोगकर्ता भाषा में बोले गए फीडबैक प्रदान करने के लिए अनुवाद करेगा।

1. इस फ़ंक्शन के अंदर, REST API कॉल के लिए URL और हेडर परिभाषित करें:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    इस API का URL स्थान-विशिष्ट नहीं है, इसके बजाय स्थान को हेडर के रूप में पास किया जाता है। API कुंजी सीधे उपयोग की जाती है, इसलिए स्पीच सर्विस के विपरीत, टोकन जारीकर्ता API से एक्सेस टोकन प्राप्त करने की आवश्यकता नहीं है।

1. इसके नीचे कॉल के लिए पैरामीटर और बॉडी परिभाषित करें:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API कॉल को पास करने के लिए पैरामीटर को परिभाषित करता है, जिसमें `from` और `to` भाषाएं पास की जाती हैं। यह कॉल `from` भाषा में टेक्स्ट को `to` भाषा में अनुवाद करेगा।

    `body` में अनुवाद करने के लिए टेक्स्ट होता है। यह एक ऐरे है, क्योंकि एक ही कॉल में कई टेक्स्ट ब्लॉक का अनुवाद किया जा सकता है।

1. REST API को कॉल करें और प्रतिक्रिया प्राप्त करें:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    प्रतिक्रिया जो वापस आती है वह एक JSON ऐरे है, जिसमें एक आइटम होता है जो अनुवादों को शामिल करता है। इस आइटम में उन सभी आइटमों के अनुवादों के लिए एक ऐरे होता है जो बॉडी में पास किए गए हैं।

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

1. ऐरे में पहले आइटम से पहले अनुवाद से `test` प्रॉपर्टी को रिटर्न करें:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` लूप को अपडेट करें ताकि उपयोगकर्ता भाषा से सर्वर भाषा में `convert_speech_to_text` कॉल से टेक्स्ट का अनुवाद किया जा सके:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    यह कोड मूल और अनुवादित टेक्स्ट को कंसोल में भी प्रिंट करता है।

1. `say` फ़ंक्शन को अपडेट करें ताकि सर्वर भाषा से उपयोगकर्ता भाषा में कहने के लिए टेक्स्ट का अनुवाद किया जा सके:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    यह कोड मूल और अनुवादित टेक्स्ट को कंसोल में भी प्रिंट करता है।

1. अपना कोड चलाएं। सुनिश्चित करें कि आपका फ़ंक्शन ऐप चल रहा है, और उपयोगकर्ता भाषा में टाइमर का अनुरोध करें, चाहे वह भाषा आप स्वयं बोलें या अनुवाद ऐप का उपयोग करें।

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

    > 💁 विभिन्न भाषाओं में कुछ कहने के अलग-अलग तरीकों के कारण, आपको ऐसे अनुवाद मिल सकते हैं जो आपके द्वारा LUIS को दिए गए उदाहरणों से थोड़ा अलग हैं। यदि ऐसा है, तो LUIS में अधिक उदाहरण जोड़ें, फिर मॉडल को पुनः प्रशिक्षित करें और पुनः प्रकाशित करें।

> 💁 आप इस कोड को [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) फ़ोल्डर में पा सकते हैं।

😀 आपका बहुभाषी टाइमर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।