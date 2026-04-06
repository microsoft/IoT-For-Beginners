# भाषण का अनुवाद करें - वर्चुअल IoT डिवाइस

इस पाठ के इस भाग में, आप कोड लिखेंगे जो भाषण को टेक्स्ट में बदलते समय उसका अनुवाद करेगा, फिर टेक्स्ट का अनुवाद Translator सेवा का उपयोग करके करेगा और अंत में एक बोले गए उत्तर को उत्पन्न करेगा।

## भाषण सेवा का उपयोग करके भाषण का अनुवाद करें

भाषण सेवा न केवल भाषण को उसी भाषा में टेक्स्ट में बदल सकती है, बल्कि आउटपुट को अन्य भाषाओं में भी अनुवाद कर सकती है।

### कार्य - भाषण सेवा का उपयोग करके भाषण का अनुवाद करें

1. VS Code में `smart-timer` प्रोजेक्ट खोलें, और सुनिश्चित करें कि वर्चुअल वातावरण टर्मिनल में लोड हो गया है।

1. मौजूदा इम्पोर्ट्स के नीचे निम्नलिखित इम्पोर्ट स्टेटमेंट्स जोड़ें:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    यह उन क्लासेस को इम्पोर्ट करता है जो भाषण का अनुवाद करने के लिए उपयोग की जाती हैं, और एक `requests` लाइब्रेरी जो इस पाठ में बाद में Translator सेवा को कॉल करने के लिए उपयोग की जाएगी।

1. आपका स्मार्ट टाइमर 2 भाषाओं के लिए सेट होगा - सर्वर की भाषा जिसका उपयोग LUIS को प्रशिक्षित करने के लिए किया गया था (यही भाषा उपयोगकर्ता से बात करने के लिए संदेश बनाने में भी उपयोग की जाती है), और उपयोगकर्ता द्वारा बोली जाने वाली भाषा। `language` वेरिएबल को उस भाषा में अपडेट करें जो उपयोगकर्ता बोलेगा, और `server_language` नामक एक नया वेरिएबल जोड़ें जो LUIS को प्रशिक्षित करने के लिए उपयोग की गई भाषा को दर्शाएगा:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` को उस भाषा के लोकल नाम से बदलें जिसमें आप बोलेंगे, जैसे `fr-FR` फ्रेंच के लिए, या `zn-HK` कैंटोनीज़ के लिए।

    `<server language>` को उस भाषा के लोकल नाम से बदलें जिसका उपयोग LUIS को प्रशिक्षित करने के लिए किया गया था।

    समर्थित भाषाओं और उनके लोकल नामों की सूची [Microsoft Docs पर भाषा और आवाज़ समर्थन दस्तावेज़](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) में पाई जा सकती है।

    > 💁 यदि आप कई भाषाएं नहीं बोलते हैं, तो आप [Bing Translate](https://www.bing.com/translator) या [Google Translate](https://translate.google.com) जैसी सेवा का उपयोग अपनी पसंदीदा भाषा से किसी अन्य भाषा में अनुवाद करने के लिए कर सकते हैं। ये सेवाएं अनुवादित टेक्स्ट का ऑडियो भी चला सकती हैं। ध्यान दें कि स्पीच रिकग्नाइज़र आपके डिवाइस से कुछ ऑडियो आउटपुट को अनदेखा कर सकता है, इसलिए आपको अनुवादित टेक्स्ट चलाने के लिए एक अतिरिक्त डिवाइस की आवश्यकता हो सकती है।
    >
    > उदाहरण के लिए, यदि आप LUIS को अंग्रेजी में प्रशिक्षित करते हैं, लेकिन उपयोगकर्ता भाषा के रूप में फ्रेंच का उपयोग करना चाहते हैं, तो आप "set a 2 minute and 27 second timer" जैसे वाक्यों को Bing Translate का उपयोग करके अंग्रेजी से फ्रेंच में अनुवाद कर सकते हैं, फिर **Listen translation** बटन का उपयोग करके अनुवाद को अपने माइक्रोफोन में बोल सकते हैं।
    >
    > ![Bing Translate पर Listen translation बटन](../../../../../translated_images/hi/bing-translate.348aa796d6efe2a9.webp)

1. `recognizer_config` और `recognizer` घोषणाओं को निम्नलिखित से बदलें:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    यह एक अनुवाद कॉन्फ़िग बनाता है जो उपयोगकर्ता की भाषा में भाषण को पहचानता है, और उपयोगकर्ता और सर्वर भाषा में अनुवाद बनाता है। फिर यह इस कॉन्फ़िग का उपयोग करके एक अनुवाद रिकग्नाइज़र बनाता है - एक स्पीच रिकग्नाइज़र जो स्पीच रिकग्निशन के आउटपुट को कई भाषाओं में अनुवाद कर सकता है।

    > 💁 मूल भाषा को `target_languages` में निर्दिष्ट करना आवश्यक है, अन्यथा आपको कोई अनुवाद नहीं मिलेगा।

1. `recognized` फ़ंक्शन को अपडेट करें, और फ़ंक्शन की पूरी सामग्री को निम्नलिखित से बदलें:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    यह कोड जांचता है कि क्या `recognized` इवेंट भाषण के अनुवाद के कारण फायर हुआ था (यह इवेंट अन्य समय पर भी फायर हो सकता है, जैसे जब भाषण को पहचाना गया हो लेकिन अनुवादित न किया गया हो)। यदि भाषण का अनुवाद किया गया था, तो यह `args.result.translations` डिक्शनरी में उस अनुवाद को ढूंढता है जो सर्वर भाषा से मेल खाता है।

    `args.result.translations` डिक्शनरी लोकल सेटिंग के पूरे नाम के बजाय भाषा भाग पर आधारित होती है। उदाहरण के लिए, यदि आप फ्रेंच के लिए `fr-FR` में अनुवाद का अनुरोध करते हैं, तो डिक्शनरी में `fr` के लिए एक एंट्री होगी, न कि `fr-FR` के लिए।

    अनुवादित टेक्स्ट को फिर IoT हब पर भेजा जाता है।

1. इस कोड को चलाएं और अनुवादों का परीक्षण करें। सुनिश्चित करें कि आपका फ़ंक्शन ऐप चल रहा है, और उपयोगकर्ता की भाषा में एक टाइमर का अनुरोध करें, या तो स्वयं उस भाषा में बोलकर, या एक अनुवाद ऐप का उपयोग करके।

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Translator सेवा का उपयोग करके टेक्स्ट का अनुवाद करें

भाषण सेवा टेक्स्ट को वापस भाषण में अनुवादित करने का समर्थन नहीं करती है, इसके बजाय आप Translator सेवा का उपयोग टेक्स्ट का अनुवाद करने के लिए कर सकते हैं। इस सेवा में एक REST API है जिसका उपयोग आप टेक्स्ट का अनुवाद करने के लिए कर सकते हैं।

### कार्य - Translator संसाधन का उपयोग करके टेक्स्ट का अनुवाद करें

1. `speech_api_key` के नीचे Translator API कुंजी जोड़ें:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` को अपने Translator सेवा संसाधन की API कुंजी से बदलें।

1. `say` फ़ंक्शन के ऊपर एक `translate_text` फ़ंक्शन परिभाषित करें जो सर्वर भाषा से उपयोगकर्ता भाषा में टेक्स्ट का अनुवाद करेगा:

    ```python
    def translate_text(text):
    ```

1. इस फ़ंक्शन के अंदर, REST API कॉल के लिए URL और हेडर परिभाषित करें:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    इस API का URL स्थान-विशिष्ट नहीं है, इसके बजाय स्थान को एक हेडर के रूप में पास किया जाता है। API कुंजी का सीधे उपयोग किया जाता है, इसलिए भाषण सेवा के विपरीत, टोकन जारीकर्ता API से एक्सेस टोकन प्राप्त करने की आवश्यकता नहीं है।

1. इसके नीचे कॉल के लिए पैरामीटर और बॉडी परिभाषित करें:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API कॉल को पास करने के लिए पैरामीटर को परिभाषित करता है, जिसमें `from` और `to` भाषाएं पास की जाती हैं। यह कॉल `from` भाषा में टेक्स्ट को `to` भाषा में अनुवादित करेगा।

    `body` अनुवाद करने के लिए टेक्स्ट को रखता है। यह एक ऐरे है, क्योंकि एक ही कॉल में कई टेक्स्ट ब्लॉक्स का अनुवाद किया जा सकता है।

1. REST API को कॉल करें, और प्रतिक्रिया प्राप्त करें:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    प्रतिक्रिया जो वापस आती है वह एक JSON ऐरे है, जिसमें एक आइटम होता है जो अनुवादों को रखता है। इस आइटम में उन सभी आइटम्स के अनुवादों के लिए एक ऐरे होता है जो बॉडी में पास किए गए थे।

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

1. ऐरे के पहले आइटम से पहले अनुवाद के `text` प्रॉपर्टी को रिटर्न करें:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `say` फ़ंक्शन को अपडेट करें ताकि SSML उत्पन्न करने से पहले कहने के लिए टेक्स्ट का अनुवाद किया जा सके:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    यह कोड मूल और अनुवादित टेक्स्ट को कंसोल में भी प्रिंट करता है।

1. अपना कोड चलाएं। सुनिश्चित करें कि आपका फ़ंक्शन ऐप चल रहा है, और उपयोगकर्ता की भाषा में एक टाइमर का अनुरोध करें, या तो स्वयं उस भाषा में बोलकर, या एक अनुवाद ऐप का उपयोग करके।

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

    > 💁 विभिन्न भाषाओं में कुछ कहने के अलग-अलग तरीकों के कारण, आपको ऐसे अनुवाद मिल सकते हैं जो आपके द्वारा LUIS को दिए गए उदाहरणों से थोड़ा अलग हों। यदि ऐसा है, तो LUIS में और उदाहरण जोड़ें, फिर मॉडल को पुनः प्रशिक्षित करें और पुनः प्रकाशित करें।

> 💁 आप इस कोड को [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) फ़ोल्डर में पा सकते हैं।

😀 आपका बहुभाषी टाइमर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।