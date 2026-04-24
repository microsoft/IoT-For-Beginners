# भाषण अनुवाद - आभासी IoT डिव्हाइस

या धड्याच्या भागामध्ये, तुम्ही भाषण सेवा वापरून भाषणाचे मजकूरात रूपांतर करताना अनुवाद करण्यासाठी कोड लिहाल, नंतर Translator सेवा वापरून मजकूराचा अनुवाद करून बोलण्याचा प्रतिसाद तयार कराल.

## भाषण सेवा वापरून भाषणाचा अनुवाद करा

भाषण सेवा भाषणाचे रूपांतर केवळ त्याच भाषेतील मजकूरातच नाही तर इतर भाषांमध्ये अनुवादित आउटपुट तयार करण्यासाठी देखील करू शकते.

### कार्य - भाषण सेवा वापरून भाषणाचा अनुवाद करा

1. VS Code मध्ये `smart-timer` प्रकल्प उघडा आणि टर्मिनलमध्ये आभासी वातावरण लोड असल्याची खात्री करा.

1. विद्यमान आयातांखालील खालील आयात विधान जोडा:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    हे भाषण अनुवाद करण्यासाठी वापरल्या जाणाऱ्या वर्गांचे आयात करते आणि `requests` लायब्ररी आयात करते जी नंतर या धड्यात Translator सेवेला कॉल करण्यासाठी वापरली जाईल.

1. तुमच्या स्मार्ट टाइमरमध्ये 2 भाषा सेट असतील - LUIS प्रशिक्षणासाठी वापरलेली सर्व्हर भाषा (सर्व्हर भाषाच वापरून वापरकर्त्याशी संवाद साधण्यासाठी संदेश तयार केले जातात) आणि वापरकर्त्याने बोललेली भाषा. `language` व्हेरिएबलला वापरकर्त्याने बोलल्या जाणाऱ्या भाषेसाठी अपडेट करा आणि LUIS प्रशिक्षणासाठी वापरलेल्या भाषेसाठी `server_language` नावाचा नवीन व्हेरिएबल जोडा:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` ला तुम्ही बोलत असलेल्या भाषेसाठी स्थानिक नावाने बदला, उदाहरणार्थ फ्रेंचसाठी `fr-FR`, किंवा कॅंटोनीजसाठी `zn-HK`.

    `<server language>` ला LUIS प्रशिक्षणासाठी वापरलेल्या भाषेच्या स्थानिक नावाने बदला.

    Microsoft Docs वर [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मध्ये समर्थित भाषांची यादी आणि त्यांची स्थानिक नावे शोधू शकता.

    > 💁 जर तुम्हाला अनेक भाषा बोलता येत नसतील तर तुम्ही [Bing Translate](https://www.bing.com/translator) किंवा [Google Translate](https://translate.google.com) सारख्या सेवांचा वापर करून तुमच्या पसंतीच्या भाषेतून दुसऱ्या भाषेत अनुवाद करू शकता. या सेवा अनुवादित मजकूराचे ऑडिओ देखील प्ले करू शकतात. लक्षात ठेवा की भाषण ओळखणारा तुमच्या डिव्हाइसवरून काही ऑडिओ आउटपुट दुर्लक्षित करू शकतो, त्यामुळे तुम्हाला अनुवादित मजकूर प्ले करण्यासाठी अतिरिक्त डिव्हाइसची आवश्यकता असू शकते.
    >
    > उदाहरणार्थ, जर तुम्ही LUIS इंग्रजीत प्रशिक्षण दिले असेल, पण वापरकर्त्याची भाषा म्हणून फ्रेंच वापरायची असेल, तर तुम्ही Bing Translate वापरून "set a 2 minute and 27 second timer" सारख्या वाक्यांचे इंग्रजीतून फ्रेंचमध्ये अनुवाद करू शकता, नंतर **Listen translation** बटण वापरून अनुवादित मजकूर तुमच्या मायक्रोफोनमध्ये बोलू शकता.
    >
    > ![Bing Translate वर Listen translation बटण](../../../../../translated_images/mr/bing-translate.348aa796d6efe2a9.webp)

1. `recognizer_config` आणि `recognizer` घोषणांना खालीलप्रमाणे बदला:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    हे वापरकर्त्याच्या भाषेत भाषण ओळखण्यासाठी अनुवाद कॉन्फिग तयार करते आणि वापरकर्ता आणि सर्व्हर भाषेत अनुवाद तयार करते. नंतर हे कॉन्फिग वापरून भाषण ओळखणारा तयार केला जातो - भाषण ओळखणारा जो भाषण ओळखण्याच्या आउटपुटचा अनेक भाषांमध्ये अनुवाद करू शकतो.

    > 💁 मूळ भाषा `target_languages` मध्ये निर्दिष्ट करणे आवश्यक आहे, अन्यथा तुम्हाला कोणतेही अनुवाद मिळणार नाहीत.

1. `recognized` फंक्शन अपडेट करा, फंक्शनच्या संपूर्ण सामग्रीला खालीलप्रमाणे बदला:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    हे कोड तपासते की ओळखलेले इव्हेंट भाषण अनुवादित झाल्यामुळे फायर झाले आहे का (हे इव्हेंट इतर वेळी देखील फायर होऊ शकते, जसे की भाषण ओळखले गेले पण अनुवादित झाले नाही). जर भाषण अनुवादित झाले असेल, तर ते `args.result.translations` डिक्शनरीमध्ये सर्व्हर भाषेशी जुळणारा अनुवाद शोधते.

    `args.result.translations` डिक्शनरी स्थानिक सेटिंगच्या संपूर्ण सेटिंगऐवजी भाषेच्या भागावर आधारित असते. उदाहरणार्थ, जर तुम्ही फ्रेंचसाठी `fr-FR` मध्ये अनुवादाची विनंती केली, तर डिक्शनरीमध्ये `fr` साठी एक एंट्री असेल, `fr-FR` साठी नाही.

    अनुवादित मजकूर IoT Hub ला पाठवला जातो.

1. हा कोड चालवा आणि अनुवादांची चाचणी करा. तुमचे फंक्शन अॅप चालू असल्याची खात्री करा आणि वापरकर्त्याच्या भाषेत टाइमरची विनंती करा, स्वतः ती भाषा बोलून किंवा अनुवाद अॅप वापरून.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Translator सेवा वापरून मजकूराचा अनुवाद करा

भाषण सेवा मजकूराचा पुन्हा भाषणात अनुवाद करण्यास समर्थन देत नाही, त्याऐवजी तुम्ही Translator सेवा वापरून मजकूराचा अनुवाद करू शकता. या सेवेसाठी REST API आहे ज्याचा वापर तुम्ही मजकूर अनुवाद करण्यासाठी करू शकता.

### कार्य - Translator संसाधन वापरून मजकूराचा अनुवाद करा

1. `speech_api_key` खाली Translator API की जोडा:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` ला तुमच्या Translator सेवा संसाधनासाठी API कीने बदला.

1. `say` फंक्शनच्या वर, `translate_text` नावाचे फंक्शन परिभाषित करा जे सर्व्हर भाषेतून वापरकर्त्याच्या भाषेत मजकूर अनुवादित करेल:

    ```python
    def translate_text(text):
    ```

1. या फंक्शनमध्ये REST API कॉलसाठी URL आणि हेडर्स परिभाषित करा:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    या API साठी URL स्थान-विशिष्ट नाही, त्याऐवजी स्थान हेडर म्हणून पास केले जाते. API की थेट वापरली जाते, त्यामुळे भाषण सेवेसारखे टोकन जारी करणाऱ्या API कडून प्रवेश टोकन मिळवण्याची गरज नाही.

1. याखाली कॉलसाठी पॅरामीटर्स आणि बॉडी परिभाषित करा:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API कॉलसाठी पास करायचे पॅरामीटर्स परिभाषित करते, `from` आणि `to` भाषा पास करते. हा कॉल `from` भाषेतील मजकूर `to` भाषेत अनुवादित करेल.

    `body` अनुवाद करण्यासाठी मजकूर ठेवते. हे एक अॅरे आहे, कारण एका कॉलमध्ये अनेक मजकूर ब्लॉक्स अनुवादित केले जाऊ शकतात.

1. REST API ला कॉल करा आणि प्रतिसाद मिळवा:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    परत आलेला प्रतिसाद JSON अॅरे आहे, ज्यामध्ये एक आयटम आहे ज्यामध्ये अनुवाद आहेत. या आयटममध्ये बॉडीमध्ये पास केलेल्या सर्व आयटम्सच्या अनुवादांसाठी अॅरे आहे.

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

1. अॅरेमधील पहिल्या आयटममधील पहिल्या अनुवादातून `text` प्रॉपर्टी परत करा:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. SSML तयार होण्यापूर्वी `say` फंक्शनमध्ये बोलायचा मजकूर अनुवादित करण्यासाठी अपडेट करा:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    हे कोड मूळ आणि अनुवादित मजकूर कन्सोलवर प्रिंट करते.

1. तुमचा कोड चालवा. तुमचे फंक्शन अॅप चालू असल्याची खात्री करा आणि वापरकर्त्याच्या भाषेत टाइमरची विनंती करा, स्वतः ती भाषा बोलून किंवा अनुवाद अॅप वापरून.

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

    > 💁 वेगवेगळ्या भाषांमध्ये काहीतरी सांगण्याच्या वेगवेगळ्या पद्धतींमुळे, तुम्हाला दिलेल्या उदाहरणांपेक्षा थोडे वेगळे अनुवाद मिळू शकतात. जर असे झाले तर LUIS मध्ये अधिक उदाहरणे जोडा, पुन्हा प्रशिक्षण द्या आणि नंतर मॉडेल पुन्हा प्रकाशित करा.

> 💁 तुम्हाला हा कोड [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) फोल्डरमध्ये सापडेल.

😀 तुमचा बहुभाषिक टाइमर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात ठेवा की स्वयंचलित भाषांतरे त्रुटी किंवा अचूकतेच्या अभावाने युक्त असू शकतात. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी, व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.